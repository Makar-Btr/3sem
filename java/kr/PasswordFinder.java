import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class PasswordFinder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String p = scanner.next();
        scanner.close();
        
        List<String> results = new ArrayList<>();
        char[] digits = p.toCharArray();
        
        for (int i = 0; i < digits.length; i++) {
            char originalDigit = digits[i];
            
            for (char newDigit = '0'; newDigit <= '9'; newDigit++) {
                if (newDigit == originalDigit) continue;
                
                if (i == 0 && newDigit == '0') continue;
                
                digits[i] = newDigit;
                String candidate = new String(digits);
                
                if (isDivisibleBy9(candidate)) {
                    results.add(candidate);
                }
                digits[i] = originalDigit;
            }
        }
        Collections.sort(results);
        for (String result : results) {
            System.out.println(result);
        }
    }
    
    private static boolean isDivisibleBy9(String number) {
        int sum = 0;
        for (char c : number.toCharArray()) {
            sum += (c - '0');
        }
        return sum % 9 == 0;
    }
}