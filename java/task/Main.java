package task;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args)
    {
        ArrayList<Student> list1 = new ArrayList<>();
        list1.add(new Student(38529417, "Иван", 5, 4.5));
        list1.add(new Student(72015683, "Мария", 5, 9.8));
        list1.add(new Student(49163825, "Петр", 6, 7.8));
        list1.add(new Student(86401295, "Анна", 6, 9.2));
        
        ArrayList<Student> list2 = new ArrayList<>();
        list2.add(new Student(23756940, "Сергей", 5, 6.1));
        list2.add(new Student(72015683, "Мария", 5, 9.8));
        list2.add(new Student(61587342, "Ольга", 7, 8.7));
        list2.add(new Student(86401295, "Анна", 6, 9.2));
        
        Students.Sort(list1);
        Students.Sort(list2);
        
        System.out.println("Первый список студентов:");
        printStudents(list1);
        
        System.out.println("\nВторой список студентов:");
        printStudents(list2);
        
        System.out.println("\nОбъединение списков:");
        printStudents(Students.unification(list1, list2));

        System.out.println("\nПересечение списков:");
        printStudents(Students.intersection(list1, list2));
        
        System.out.println("\nРазность:");
        printStudents(Students.difference(list1, list2));
    }

    private static void printStudents(ArrayList<Student> students) 
    {
        for (Student student : students) {
            System.out.println("№ " + student.m_ID + ", " + student.m_name + ", " 
                               + student.m_group + " группа, " + student.m_grade);
        }
    }
}
