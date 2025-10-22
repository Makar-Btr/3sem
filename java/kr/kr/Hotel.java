package kr;

public class Hotel 
{
    private String m_city;
    private String m_name;
    private int m_stars;

    public Hotel()
    {
        m_city = m_name = "";
        m_stars = 0;
    }

    public Hotel(String city, String name, int stars)
    {
        m_city = city;
        m_name = name;
        m_stars = stars;
    }

    public void write()
    {
        System.out.println(m_city + " " + m_name + " " + m_stars + " звезды");
    }

    public String getCity()
    {
        return m_city;
    }

    public String getName()
    {
        return m_name;
    }

    public int getStars()
    {
        return m_stars;
    }
}