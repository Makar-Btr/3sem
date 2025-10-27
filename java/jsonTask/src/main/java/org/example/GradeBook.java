package org.example;

import java.text.NumberFormat;
import java.util.*;

public class GradeBook
{
    private final String m_surname;
    private final String m_name;
    private final String m_patronymic;
    private final int m_course;
    private final int m_group;
    private final List<Session> m_sessions;

    public GradeBook() 
    {
        m_surname = m_name = m_patronymic = "";
        m_course = m_group = 0;
        m_sessions = new ArrayList<>();
    }

    public GradeBook(String surname, String name, String patronymic, int course, int group) 
    {
        m_surname = surname;
        m_name = name;
        m_patronymic = patronymic;
        m_course = course;
        m_group = group;
        m_sessions = new ArrayList<>(); 
    }

    public GradeBook(GradeBook obj) 
    {
        m_surname = obj.m_surname;
        m_name = obj.m_name;
        m_patronymic = obj.m_patronymic;
        m_course = obj.m_course;
        m_group = obj.m_group;
        m_sessions = new ArrayList<>(obj.m_sessions);
    }

    public static class Session
    {
        private final int m_number;
        private final List<Exam> m_exams;

        public Session() 
        {
            m_number = 0;
            m_exams = new ArrayList<>();
        }

        public Session(int number) 
        {
            m_number = number;
            m_exams = new ArrayList<>();
        }

        public Session(Session obj) 
        {
            m_number = obj.m_number;
            m_exams = new ArrayList<>(obj.m_exams);
        }

        public void addExam(String subject, int grade) 
        {
            m_exams.add(new Exam(subject, grade));
        }

        public boolean isAllPassed() 
        {
            for(Exam exam : m_exams) 
            {
                if(exam.getGrade() < 4) 
                {
                    return false;
                }
            }
            return true;
        }

        public boolean isAllExcellent() 
        {
            for(Exam exam : m_exams) {
                if(exam.getGrade() < 9) 
                {
                    return false;
                }
            }
            return true;
        }

        public int getSessionNumber() 
        {
            return m_number;
        }
        
        public List<Exam> getExams() 
        {
            return m_exams;
        }
    }

    public static class Exam
    {
        private final String m_subject;
        private final int m_grade;

        public Exam() 
        {
            m_subject = "";
            m_grade = 0;
        }

        public Exam(String subject, int grade) 
        {
            m_subject = subject; 
            m_grade = grade;
        }

        public Exam(Exam obj)
        {
            m_subject = obj.m_subject;
            m_grade = obj.m_grade;
        }

        public String getSubject() 
        {
            return m_subject;
        }

        public int getGrade() 
        {
            return m_grade;
        }
    }

    public Session createSession(int sessionNumber) 
    {
        Session session = new Session(sessionNumber);
        m_sessions.add(session);
        return session;
    }

    public String getSurname() 
    {
        return m_surname;
    }

    public String getName() 
    {
        return m_name;
    }

    public String getPatronymic() 
    {
        return m_patronymic;
    }

    public int getGroup() 
    {
        return m_group;
    }

    public double getAverageGrade() 
    {
        if(m_sessions.isEmpty()) 
        {
            return 0.0;
        }
        
        int totalGrade = 0;
        int examCount = 0;
        
        for(Session session : m_sessions) 
        {
            for(Exam exam : session.getExams()) 
            {
                totalGrade += exam.getGrade();
                examCount++;
            }
        }
        
        return examCount > 0 ? (double) totalGrade / examCount : 0.0;
    }

    public String getStudentInfo() 
    {
        return m_surname + " " + m_name + " " + m_patronymic + " " + m_course + " курс, " + m_group + " группа";
    }

    public String getStudentResults() 
    {
        NumberFormat formatter = NumberFormat.getNumberInstance();
        formatter.setMaximumFractionDigits(1);

        StringBuilder result = new StringBuilder();
        result.append(getStudentInfo()).append("\n");

        for(Session session : m_sessions)
        {
            result.append("  Сессия ").append(session.getSessionNumber()).append(":\n");

            for(Exam exam : session.getExams())
            {
                result.append("    ")
                        .append(exam.getSubject())
                        .append(" - ")
                        .append(exam.getGrade())
                        .append("\n");
            }
        }

        if(this.isExcellentStudent())
        {
            result.append("Отличник, средний балл: ").append(formatter.format(this.getAverageGrade())).append("\n");
        }
        else if (this.isBadStudent())
        {
            result.append("Есть задолженности, средний балл: ").append(formatter.format(this.getAverageGrade())).append("\n");
        }
        else
        {
            result.append("Успевающий, средний балл: ").append(formatter.format(this.getAverageGrade())).append("\n");
        }

        return result.toString();
    }

    public boolean isExcellentStudent() 
    {
        for(Session session : m_sessions) 
        {
            if(!session.isAllExcellent()) 
            {
                return false;
            }
        }
        return true;
    }

    public boolean isBadStudent()
    {
        for(Session session : m_sessions)
        {
            if(!session.isAllPassed())
            {
                return true;
            }
        }
        return false;
    }
}