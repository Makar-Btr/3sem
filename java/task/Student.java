package task;

public class Student 
{
    int m_ID;
    String m_name;
    int m_group;
    double m_grade;

    public Student() 
    {
        m_ID = m_group = 0;
        m_name = "";
        m_grade = 0.0;
    }
    
    public Student(int id, String name, int group, double grade) 
    {
        this.m_ID = id;
        this.m_name = name;
        this.m_group = group;
        this.m_grade = grade;
    }

    int getID()
    {
        return m_ID;
    }

}
