package Lab4.Lab4;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;

public class Main 
{
    public static void main(String[] args)
    {
        ArrayList<GradeBook> books = new ArrayList<>();

        readFromFile("d:\\3sem\\java\\Lab4\\Lab4\\input.txt", books);

        books.sort(Comparator
            .comparingInt(GradeBook::getGroup)
            .thenComparing(book -> book.getSurname() + book.getName() + book.getPatronymic())
        );

        try(PrintWriter writer = new PrintWriter(new FileWriter("d:\\3sem\\java\\Lab4\\Lab4\\output.txt"));)
        {
            for(GradeBook book : books)
            {
                writer.println(book.getStudentResults());
            }
            writer.close();
        }
        catch(IOException e)
        {
            System.out.println("Ошибка записи в файл");
        }
    }

    public static void readFromFile(String filename, ArrayList<GradeBook> gradeBooks) 
    {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            String line;
            GradeBook currentBook = null;
            GradeBook.Session currentSession = null;
            
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty()) continue;
                
                if (line.startsWith("Студент:")) {
                    // Формат: Student: Иванов Иван Иванович, 2, 101
                    String studentData = line.substring(8).trim();
                    String[] parts = studentData.split(",");
                    if (parts.length >= 3) {
                        String[] nameParts = parts[0].trim().split(" ");
                        String surname = nameParts[0];
                        String name = nameParts[1];
                        String patronymic = nameParts[2];
                        int course = Integer.parseInt(parts[1].trim());
                        int group = Integer.parseInt(parts[2].trim());
                        
                        currentBook = new GradeBook(surname, name, patronymic, course, group);
                        gradeBooks.add(currentBook);
                    }
                } else if (line.startsWith("Сессия:")) {
                    // Формат: Session: 1
                    int sessionNumber = Integer.parseInt(line.substring(7).trim());
                    if (currentBook != null) {
                        currentSession = currentBook.createSession(sessionNumber);
                    }
                } else if (line.startsWith("Экзамен:")) {
                    // Формат: Exam: Математика, 9
                    String examData = line.substring(8).trim();
                    String[] parts = examData.split(",");
                    if (parts.length >= 2 && currentSession != null) {
                        String subject = parts[0].trim();
                        int grade = Integer.parseInt(parts[1].trim());
                        currentSession.addExam(subject, grade);
                    }
                }
            }
        } 
        catch (IOException e) 
        {
            System.out.println("Ошибка чтения файла");
        }
    }
}
