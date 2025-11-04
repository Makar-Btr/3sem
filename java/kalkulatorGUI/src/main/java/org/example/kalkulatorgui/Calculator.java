package org.example.kalkulatorgui;

import java.util.Stack;

public class Calculator {

    private final String infix;
    private String postfix;
    private double result;

    public Calculator(String _infix)
    {
        this.infix = _infix.replaceAll("\\s+", "");
        this.postfix = "";
        this.result = 0.0;
    }

    private int priority(char op)
    {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    private boolean isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    public void convertToPostfix()
    {
        StringBuilder pf = new StringBuilder();
        Stack<Character> operators = new Stack<>();

        for (int i = 0; i < infix.length(); i++)
        {
            char c = infix.charAt(i);

            if (Character.isDigit(c) || c == '.')
            {
                StringBuilder num = new StringBuilder();
                while (i < infix.length() && (Character.isDigit(infix.charAt(i)) || infix.charAt(i) == '.'))
                {
                    num.append(infix.charAt(i));
                    i++;
                }
                i--;
                pf.append(num.toString()).append(" ");
            }
            else if (c == '(')
            {
                operators.push(c);
            }
            else if (c == ')')
            {
                while (!operators.empty() && operators.peek() != '(')
                {
                    pf.append(operators.pop()).append(" ");
                }
                if (operators.empty())
                {
                    throw new IllegalArgumentException("Ошибка: нет '(' для ')'");
                }
                operators.pop();
            }
            else if (isOperator(c))
            {
                while (!operators.empty() && priority(operators.peek()) >= priority(c))
                {
                    pf.append(operators.pop()).append(" ");
                }
                operators.push(c);
            }
        }

        while (!operators.empty())
        {
            char op = operators.pop();
            if (op == '(')
            {
                throw new IllegalArgumentException("Ошибка: нет ')' для '('");
            }
            pf.append(op).append(" ");
        }
        this.postfix = pf.toString().trim();
    }

    public void calculateResult()
    {
        if (this.postfix.isEmpty())
        {
            convertToPostfix();
        }

        Stack<Double> values = new Stack<>();
        String[] tokens = this.postfix.split("\\s+");

        if (tokens.length == 1 && tokens[0].isEmpty())
        {
            if (!values.empty()) this.result = values.pop();
            return;
        }

        for (String token : tokens)
        {
            if (token.length() == 1 && isOperator(token.charAt(0)))
            {
                if (values.size() < 2)
                {
                    throw new IllegalArgumentException("Ошибка: не хватает операндов");
                }
                double val2 = values.pop();
                double val1 = values.pop();

                switch (token.charAt(0))
                {
                    case '+': values.push(val1 + val2); break;
                    case '-': values.push(val1 - val2); break;
                    case '*': values.push(val1 * val2); break;
                    case '/':
                        if (val2 == 0)
                            throw new ArithmeticException("Деление на ноль!");
                        values.push(val1 / val2);
                        break;
                }
            }
            else
            {
                try
                {
                    values.push(Double.parseDouble(token));
                }
                catch (NumberFormatException e)
                {
                    throw new IllegalArgumentException("Ошибка: неверный символ '" + token + "'");
                }
            }
        }

        if (values.size() != 1)
        {
            throw new IllegalArgumentException("Ошибка: выражение составлено неверно");
        }
        this.result = values.pop();
    }

    public String getInfix()
    {
        return this.infix;
    }

    public String getPostfix()
    {
        return postfix;
    }

    public double getResult()
    {
        return result;
    }
}