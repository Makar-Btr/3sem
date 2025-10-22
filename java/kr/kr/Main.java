package kr;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args)
    {
        Hotels hotels = new Hotels();
        try(Scanner in = new Scanner(new File("d:\\3sem\\java\\kr\\kr\\hotel.txt")))
        {
            hotels.fileInput(in);
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        
        hotels.sort();

        hotels.write();

        Scanner cin = new Scanner(System.in);
        System.out.println("Введите город для поиска отелей:");
        String city = cin.nextLine();
        ArrayList<Hotel> foundHotels = hotels.findHotels(city);
        if (foundHotels.isEmpty()) 
        {
            System.out.println("Нет отелей в этом городе.");
        }
        else
        {
            for(Hotel hotel : foundHotels)
            {
                hotel.write();
            }
        }

        System.out.println("Введите имя отеля для поиска городов:");
        String hotelName = cin.nextLine();
        ArrayList<String> foundCities = hotels.findCities(hotelName);
        if (!foundCities.isEmpty()) 
        {
            for(String cityName : foundCities)
            {
                System.out.println(cityName);
            }
        }
        else 
        {
            System.out.println("Нет отелей с таким именем.");
        }
        

        cin.close();
    }
}