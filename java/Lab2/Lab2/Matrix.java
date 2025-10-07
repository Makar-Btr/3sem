package Lab2;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class Matrix {

    Matrix()
    {
        m_size = 0;
        m_matrix = null;
    }

    Matrix(int size)
    {
        m_size = size;
        m_matrix = new int[m_size][m_size];
    }

    Matrix(Matrix objMatrix)
    {
        m_size = objMatrix.m_size;
        m_matrix = new int[m_size][m_size];
        for(int i = 0; i < m_size; i++)
        {
            for(int j = 0; j < m_size; j++)
            {
                m_matrix[i][j] = objMatrix.m_matrix[i][j];
            }
        }
    }

    void ScanMatrix(Scanner in)
    {
        m_matrix = null;
        m_size = in.nextInt();
        m_matrix = new int[m_size][m_size];
        System.out.println("Введенная матрица:");
        for (int i = 0; i < m_size; i++)
        {
            for(int j = 0; j < m_size; j++)
            {
                m_matrix[i][j] = in.nextInt();
                System.out.print(m_matrix[i][j] + "\t");
            }
            System.out.println();
        }
    }

    void PrintMatrix()
    {
        for (int i = 0; i < m_size; i++)
        {
            for(int j = 0; j < m_size; j++)
            {
                System.out.print(m_matrix[i][j] + "\t");
            }
            System.out.println();
        }
    }

    void Simetr()
    {
        for (int i = 0; i < m_size - 1; i++)
        {
            for (int j = i + 1; j < m_size; j++)
            {
                if(m_matrix[i][j] != m_matrix[j][i])
                {
                    System.out.println("Матрица не симметричная");
                    return;
                }
            }
        }
        System.out.println("Матрица симметричная");
    }
    
    void MaxElement()
    {
        int iMax = 0, jMax = 0;
        for (int i = 0; i < m_size; i++)
        {
            if(m_matrix[iMax][jMax] < m_matrix[i][i])
            {
                iMax = i;
                jMax = i;
            }
        }
        for (int i = 0, j = m_size - 1; i < m_size; i++, j--)
        {
            if(m_matrix[iMax][jMax] < m_matrix[i][j])
            {
                iMax = i;
                jMax = j;
            }
        }
        switch (m_size % 2) 
        {
            case 0:
            {
                System.out.println("Нет элемента на пересечении диагоналей");
                PrintMatrix();
                break;
            }
            case 1:
            {
                int centralInd = m_size / 2,
                    centralEl = m_matrix[centralInd][centralInd],
                    maxEl = m_matrix[iMax][jMax];

                m_matrix[centralInd][centralInd] = maxEl;
                m_matrix[iMax][jMax] = centralEl;

                PrintMatrix();
                break;
            }
        
            default:
                break;
        }
    }

    void MaxSum()
    {
        Map<Integer, Integer> diagSums = new HashMap<>();

        for (int i = 0; i < m_size; i++) 
        {
            for (int j = 0; j < m_size; j++) 
            {
                int key = j - i;
                diagSums.put(key, diagSums.getOrDefault(key, 0) + m_matrix[i][j]);
            }
        }

        int maxSum = Integer.MIN_VALUE;
        for(int sum : diagSums.values())
        {
            if(sum > maxSum)
            {
                maxSum = sum;
            }
        }

        System.out.println("Максимальная сумма диагонали: " + maxSum);
    }

    void SortByFirstEl()
    {
        int temp[];
        for(int i = 1; i < m_size; i++)
        {
		    for(int k = i - 1; k >= 0 && m_matrix[k][0] > m_matrix[k + 1][0]; k--) 
            {
                temp = m_matrix[k];
                m_matrix[k] = m_matrix[k + 1];
                m_matrix[k + 1] = temp;
		    }
	    }

        PrintMatrix();
    }

    private
    int[][] m_matrix;
    int m_size;
}
