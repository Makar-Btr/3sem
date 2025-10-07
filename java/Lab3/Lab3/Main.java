package Lab3.Lab3;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        
        System.out.println("Введите текст (для завершения введите пустую строку):");
        
        StringBuilder textBuilder = new StringBuilder();
        String line;
        while (!(line = in.nextLine()).isEmpty()) {
            textBuilder.append(line).append(" ");
        }

        String text = textBuilder.toString().trim();
        
        if (text.isEmpty()) {
            System.out.println("Текст не был введен.");
            in.close();
            return;
        }

        StringBuilder letters = new StringBuilder();
        StringBuilder numbers = new StringBuilder();
        processText(text, letters, numbers);

        in.close();
    }

    private static void processText(String textString, StringBuilder letters, StringBuilder numbers)
    {
        char letter;
        int number;

        for (char c : textString.toCharArray()) 
        {
            letter = Character.toLowerCase(c);
            if (Character.isAlphabetic(c) && letter >= 'a' && letter <= 'z') 
            {
                number = letter - 'a' + 1;
                
                letters.append(c).append("  ");
                numbers.append(number).append(number < 10 ? "  " : " ");
            } 
            else 
            {
                letters.append(c).append("  ");
                numbers.append("   ");
            }
        }

        System.out.println(letters);
        System.out.println(numbers);
        System.out.println();
    }
}