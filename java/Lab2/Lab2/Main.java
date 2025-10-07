package Lab2;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) 
    {
        Matrix matrix = new Matrix();

        Scanner in = null;
        try
        {
            in = new Scanner(new File("d:\\java\\Lab2\\Lab2\\input2.txt"));
        }
        catch(FileNotFoundException e)
        {
            System.out.println("Файл не найден");
        }
        matrix.ScanMatrix(in);
        in.close();

        System.out.println();

        matrix.Simetr();
        matrix.MaxElement();

        System.out.println();

        matrix.MaxSum();

        System.out.println();

        matrix.SortByFirstEl();

    }
}