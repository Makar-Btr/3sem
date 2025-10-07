package task;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args)
    {
        ArrayList<Student> list1 = new ArrayList<>();
        list1.add(new Student(1, "Иван", 101, 4.5));
        list1.add(new Student(3, "Мария", 101, 4.8));
        list1.add(new Student(5, "Петр", 102, 3.9));
        list1.add(new Student(7, "Анна", 102, 4.2));
        
        ArrayList<Student> list2 = new ArrayList<>();
        list2.add(new Student(2, "Сергей", 101, 4.1));
        list2.add(new Student(3, "Мария", 101, 4.8));
        list2.add(new Student(6, "Ольга", 103, 4.7));
        list2.add(new Student(7, "Анна", 102, 4.2));
        
        Students.Sort(list1);
        Students.Sort(list2);
        
        System.out.println("Первый список студентов:");
        printStudents(list1);
        
        System.out.println("\nВторой список студентов:");
        printStudents(list2);
        
        ArrayList<Student> union = Students.unification(list1, list2);
        System.out.println("\nОбъединение списков:");
        printStudents(union);

        ArrayList<Student> intersect = Students.intersection(list1, list2);
        System.out.println("\nПересечение списков:");
        printStudents(intersect);
        
        
        ArrayList<Student> diff = Students.difference(list1, list2);
        System.out.println("\nРазность (list1 - list2):");
        printStudents(diff);
    }

    private static void printStudents(ArrayList<Student> students) 
    {
        for (Student student : students) {
            System.out.println(student);
        }
    }
}
