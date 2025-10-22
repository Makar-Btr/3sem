package kr;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class Hotels {
    private ArrayList<Hotel> m_hotels;

    public Hotels()
    {
        m_hotels = new ArrayList<>();
    }

    public Hotels(int size)
    {
        m_hotels = new ArrayList<>(size);
    }

    public void fileInput(Scanner in)
    {
        while(in.hasNextLine()) {
            String city = in.nextLine();
            String name = in.nextLine();
            int stars = Integer.parseInt(in.nextLine());

            Hotel a = new Hotel(city, name, stars);
            m_hotels.add(a);
        }
    }

    public void sort()
    {
        m_hotels.sort(new Comparator<Hotel>() {
            public int compare(Hotel h1, Hotel h2) {
                int cityCompare = h1.getCity().compareTo(h2.getCity());
                if (cityCompare != 0) {
                    return cityCompare;
                }
                return Integer.compare(h2.getStars(), h1.getStars());
            }
        });
    }

    public ArrayList<Hotel> findHotels(String city)
    {
        ArrayList<Hotel> hotelsOfCity = new ArrayList<>();
        for(Hotel hotel : m_hotels)
        {
            if(hotel.getCity().equals(city))
            {
                hotelsOfCity.add(hotel);
            }
        }

        return hotelsOfCity;
    }

    public ArrayList<String> findCities(String hotelName)
    {
        ArrayList<String> citiesOfHotel = new ArrayList<>();
        for(Hotel hotel : m_hotels)
        {
            if(hotel.getName().equals(hotelName))
            {
                citiesOfHotel.add(hotel.getCity());
            }
        }

        return citiesOfHotel;
    }

    public void write()
    {
        for(Hotel hotel : m_hotels)
        {
            hotel.write();
        }
        System.out.println();
    }
}