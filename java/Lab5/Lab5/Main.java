package Lab5.Lab5;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main 
{
    private static final String inputFile = "d:\\3sem\\java\\Lab5\\Lab5\\input.txt";
    private static final String outputFile = "d:\\3sem\\java\\Lab5\\Lab5\\output.txt";

    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        int width = 0;
        boolean validInput = false;

        while (!validInput) 
        {
            System.out.print("Введите ширину строки: ");
            if (scanner.hasNextInt()) 
            {
                width = scanner.nextInt();
                if (width > 0) 
                {
                    validInput = true;
                } 
                else 
                {
                    System.out.println("Ширина должна быть положительным числом.");
                }
            } 
            else 
            {
                System.out.println("Некорректный ввод. Введите целое число.");
                scanner.next();
            }
        }
        scanner.close();

        TextHandler textHandler = new TextHandler(width);

        try 
        {
            String inputText = readFile();
            
            String handledText = textHandler.handleText(inputText);
            
            writeFile(handledText);
        } 
        catch (IOException e) 
        {
            System.err.println("Ошибка при работе с файлами");
        }
    }

    public static String readFile() throws IOException 
    {
        StringBuilder content = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile))) 
        {
            String line;
            while ((line = reader.readLine()) != null) 
            {
                content.append(line).append('\n');
            }
        }
        return content.toString();
    }

    public static void writeFile(String content) throws IOException 
    {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) 
        {
            writer.write(content);
        }
    }
}