package task;

import java.util.ArrayList;
import java.util.Comparator;



public class Students {

    public static void Sort(ArrayList<Student> x)
    {
        x.sort(Comparator.comparingInt(Student::getID));
    }
    
    public static ArrayList<Student> unification(ArrayList<Student> x, ArrayList<Student> y)
    {
        int i = 0, j = 0;
        ArrayList<Student> z = new ArrayList<>(x.size() + y.size());
        while(i < x.size() && j < y.size())
        {
            if(x.get(i).m_ID < y.get(j).m_ID)
            {
                z.add(x.get(i++));
            }
            else if(x.get(i).m_ID > y.get(j).m_ID)
            {
                z.add(y.get(j++));
            }
            else
            {
                z.add(y.get(j++));
                i++;
            }
        }
        while(i < x.size())
        {
            z.add(x.get(i++));
        }
        while(j < y.size())
        {
            z.add(y.get(j++));
        }
        z.trimToSize();;
        return z;
    }

    public static ArrayList<Student> intersection(ArrayList<Student> x, ArrayList<Student> y)
    {
        int i = 0, j = 0;
        ArrayList<Student> z = new ArrayList<>(Math.min(x.size(), y.size()));
        while(i < x.size() && j < y.size())
        {
            if(x.get(i).m_ID < y.get(j).m_ID)
            {
                i++;
            }
            else if(x.get(i).m_ID > y.get(j).m_ID)
            {
                j++;
            }
            else
            {
                z.add(y.get(j++));
                i++;
            }
        }
        z.trimToSize();
        return z;
    }

    public static ArrayList<Student> difference(ArrayList<Student> x, ArrayList<Student> y)
    {
        int i = 0, j = 0;
        ArrayList<Student> z = new ArrayList<>(x.size());
        while(i < x.size() && j < y.size())
        {
            if(x.get(i).m_ID < y.get(j).m_ID)
            {
                z.add(x.get(i++));
            }
            else if(x.get(i).m_ID > y.get(j).m_ID)
            {
                j++;
            }
            else
            {
                j++;
                i++;
            }
        }
        while(i < x.size())
        {
            z.add(x.get(i++));
        }
        z.trimToSize();;
        return z;
    }
}
