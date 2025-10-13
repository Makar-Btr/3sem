package Lab3.Lab3;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        
        System.out.println("Введите текст (для завершения введите пустую строку):");
        
        List<String> text = new ArrayList<>();
        String line;
        while (!(line = in.nextLine()).isEmpty()) {
            text.add(line);
        }

        if (text.isEmpty()) {
            System.out.println("Текст не был введен.");
            in.close();
            return;
        }

        processText(text);
        in.close();
    }

    private static void processText(List<String> text) {
        char lowerChar;
        for (String line : text) 
        {
            StringBuilder letters = new StringBuilder();
            StringBuilder numbers = new StringBuilder();

            for (char c : line.toCharArray()) 
            {
                lowerChar = Character.toLowerCase(c);
                if (Character.isAlphabetic(c) && lowerChar >= 'a' && lowerChar <= 'z') 
                {
                    int number = lowerChar - 'a' + 1;
                    
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
}

/*
Pack my box with five dozen liquor jugs!
How vexingly quick daft zebras jump!
Waltz, bad nymph, for quick jigs vex.
Mr. Jock, TV quiz PhD, bags few lynx.
Sphinx of black quartz, judge my vow.
Bright vixens jump; dozy fowl quack.
Jackdaws love my big sphinx of quartz.
The five boxing wizards jump quickly. 
*/