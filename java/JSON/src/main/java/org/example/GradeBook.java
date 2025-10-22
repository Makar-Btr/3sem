package org.example;

import java.text.NumberFormat;
import java.util.*;

class GradeBook 
{
    private String m_surname;
    private String m_name;
    private String m_patronymic;
    private int m_course;
    private int m_group;
    private List<Session> m_sessions;

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

    public class Session 
    {
        private int m_number;
        private List<Exam> m_exams;

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

    public class Exam 
    {
        private String m_subject;
        private int m_grade;

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

    public void addSession(Session session) 
    {
        m_sessions.add(new Session(session));
    }

    public Session createSession(int sessionNumber) 
    {
        Session session = new Session(sessionNumber);
        m_sessions.add(session);
        return session;
    }

    public List<Session> getSessions() 
    {
        return m_sessions;
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

    public int getCourse() 
    {
        return m_course;
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
        String result = getStudentInfo() + "\n";
        for(Session session : m_sessions) 
        {
            result += "  Сессия " + session.getSessionNumber() + ":\n";
            for(Exam exam : session.getExams()) 
            {
                result += "    " + exam.getSubject() + " - " + exam.getGrade() + "\n";
            }
        }
        if(this.isExcellentStudent())
        {
            result += "Отличник, средний балл: " + formatter.format(this.getAverageGrade()) + "\n";
        }
        else if (this.isBadStudent()) 
        {
            result += "Есть задолженности, средний балл: " + formatter.format(this.getAverageGrade()) + "\n";
        }
        else
        {
            result += "Успевающий, средний балл: " + formatter.format(this.getAverageGrade()) + "\n";
        }
        return result;
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