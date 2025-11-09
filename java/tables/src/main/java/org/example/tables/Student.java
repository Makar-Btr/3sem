package org.example.tables;

public class Student
{
    private final String surname;
    private final String name;
    private final String patronymic;
    private final String group;
    private final int ID;

    public Student(String surname, String name, String patronymic, String group, int ID)
    {
        this.surname = surname;
        this.name = name;
        this.patronymic = patronymic;
        this.group = group;
        this.ID = ID;
    }

    public String getSurname()
    {
        return surname;
    }

    public String getName()
    {
        return name;
    }

    public String getPatronymic()
    {
        return patronymic;
    }

    public String getGroup()
    {
        return group;
    }

    public int getID()
    {
        return ID;
    }

    public String getFullName()
    {
        return surname + " " + name + " " + patronymic;
    }
}