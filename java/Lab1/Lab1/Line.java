package Lab1;

class Line {

    public static double Exp(int k, double x)
    {
        double eps = Math.pow(0.1, k), n = 1.0, res = 1.0;
        for(int i = 1; Math.abs(n) >= eps; i++)
        {
            n *= x / i;
            res += n;
        }
        return res;
    }

    public static double Sin(int k, double x)
    {
        double eps = Math.pow(10, -k)/100, n = x%(2 * Math.PI), res = 0, i = 1, y = n;
        while (Math.abs(n) >= eps)
        {
            res += n;
            n *=  (-y) * y / (2 * i) / (2 * i + 1);
            i++;
        }
        return res;
    }
}