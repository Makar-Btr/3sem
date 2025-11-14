#include "gtest/gtest.h"
#include "../main/MarkerSystem.h"
#include <numeric>

//1.1
TEST(MarkerTests, Test_1_1_CorrectMarkingOneThread) 
{
    const int arraySize = 10;
    const int threadCount = 1;
    
    MarkerSystem system(arraySize, threadCount);
    system.startAll();
    
    system.waitForAllToStop();
    
    auto arrayState = system.getArrayState();
    
    for (int val : arrayState) 
    {
        EXPECT_EQ(val, 1);
    }

    system.terminateThread(1);
    EXPECT_EQ(system.getActiveThreadCount(), 0);
}

//1.2
TEST(MarkerTests, Test_1_2_CorrectCleanup) 
{
    const int arraySize = 10;
    const int threadCount = 1;
    
    MarkerSystem system(arraySize, threadCount);
    system.startAll();
    system.waitForAllToStop();
    
    system.terminateThread(1);
    
    auto arrayState = system.getArrayState();
    
    for (int val : arrayState) 
    {
        EXPECT_EQ(val, 0);
    }
    EXPECT_EQ(system.getActiveThreadCount(), 0);
}

//2.1
TEST(MarkerTests, Test_2_1_NoRaceCondition) 
{
    const int arraySize = 20;
    const int threadCount = 10;
    
    MarkerSystem system(arraySize, threadCount);
    system.startAll();
    
    system.waitForAllToStop();
    
    auto arrayState = system.getArrayState();
    int markedCells = 0;

    for (int val : arrayState) 
    {
        EXPECT_GE(val, 0);
        EXPECT_LE(val, threadCount);
        if (val > 0) 
        {
            markedCells++;
        }
    }
    
    EXPECT_GT(markedCells, 0);
}

//2.2
TEST(MarkerTests, Test_2_2_SequentialTermination) 
{
    const int arraySize = 30;
    const int threadCount = 5;
    
    MarkerSystem system(arraySize, threadCount);
    system.startAll();
    
    system.waitForAllToStop();

    for (int id_to_term = threadCount; id_to_term >= 1; --id_to_term) 
    {
        auto stateBefore = system.getArrayState();
        
        system.terminateThread(id_to_term);
        
        auto stateAfter = system.getArrayState();

        for (int i = 0; i < arraySize; ++i) 
        {
            if (stateBefore[i] == id_to_term) 
            {
                EXPECT_EQ(stateAfter[i], 0);
            } 
            else 
            {
                EXPECT_EQ(stateAfter[i], stateBefore[i]);
            }
        }

        if (system.getActiveThreadCount() > 0) 
        {
            system.continueAll();
            system.waitForAllToStop();
        }
    }
    
    EXPECT_EQ(system.getActiveThreadCount(), 0);
    auto finalState = system.getArrayState();
    for (int val : finalState) 
    {
        EXPECT_EQ(val, 0);
    }
}