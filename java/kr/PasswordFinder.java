/*  Задача №111513. Шпионские штучки
Алиса и Боб — очень опытные шпионы. Лучше всего им удается находить пароли для 
доступа к различным секретным данным. Вот и в этот раз Алиса получила от Боба 
сообщение, в котором говорилось, что ключом является число и далее шло само это 
число. Также Боб писал, что число-ключ должно делиться на 9. Когда Алиса 
попробовала ввести полученный пароль, то оказалось, что он не подходит. Алиса 
очень доверяет Бобу, и поэтому она решила, что Боб мог ошибиться только в одной 
цифре пароля. Поскольку у Алисы не так много времени, она решила не выяснять у 
Боба правильный ответ, а перебрать все числа, которые могли бы быть паролем, т.е. 
все такие числа, которые могут быть получены из того числа, которое прислал Боб, 
заменой ровно одной из его цифр и делятся на 9. За помощью Алиса обратилась к вам. 
Напишите программу, которая предложит Алисе все возможные варианты пароля.

Входные данные
Во входных данных содержится единственное число P (1 ≤ P ≤ 109) — то число, которая 
Алиса получила в сообщении от Боба. Гарантируется, что оно не начинается с нуля.

Выходные данные
Выведите в столбик все возможные варианты паролей, которые нужно перебрать Алисе, 
в произвольном порядке. Ни одно из полученных вами чисел не должно начинаться с 
нуля. Все возможные варианты паролей должны содержать столько же цифр, сколько и 
исходное число, полученное Алисой. */

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