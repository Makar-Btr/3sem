package Lab1;

import java.util.Scanner;
import java.text.NumberFormat;



public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.println("Введите показатель степени для экспоненты (x) и точность (k)");
        double x = in.nextDouble();
        int k = in.nextInt();


        NumberFormat formatter = NumberFormat.getNumberInstance();
        formatter.setMaximumFractionDigits(k);

        System.out.println("Значение экспоненты:");
        System.out.println(formatter.format(Math.exp(x)));
        System.out.println("Значение ряда Тейлора экспоненты:");
        System.out.println(formatter.format(Line.Exp(k, x)));

        System.out.println("Значение синуса:");
        System.out.println(formatter.format(Math.sin(x)));
        System.out.println("Значение ряда Тейлора синуса:");
        System.out.println(formatter.format(Line.Sin(k, x)));

        in.close();
    }

    
}

