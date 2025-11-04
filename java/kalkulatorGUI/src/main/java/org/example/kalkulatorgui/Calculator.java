package org.example.kalkulatorgui;

import java.util.Stack;

// Это прямой перенос логики из вашего C++ файла
public class Calculator
{

    private final String infix;
    private String postfix;
    private int result;

    public Calculator(String _infix)
    {
        this.infix = _infix.replaceAll("\\s+", ""); // Убираем пробелы
        this.postfix = "";
        this.result = 0;
    }

    private int priority(char op)
    {
        if (op == '+' || op == '-')
        {
            return 1;
        }
        if (op == '*' || op == '/')
        {
            return 2;
        }
        return 0;
    }

    private boolean isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    public void convertToPostfix()
    {
        Stack<Character> operators = new Stack<>();
        StringBuilder pf = new StringBuilder();

        for (char c : infix.toCharArray())
        {
            if (Character.isDigit(c))
            {
                pf.append(c);
            }
            else if (c == '(')
            {
                operators.push(c);
            }
            else if (c == ')')
            {
                while (!operators.empty() && operators.peek() != '(')
                {
                    pf.append(operators.pop());
                }
                if (!operators.empty())
                {
                    operators.pop();
                }
            }
            else if (isOperator(c))
            {
                while (!operators.empty() && priority(operators.peek()) >= priority(c))
                {
                    pf.append(operators.pop());
                }
                operators.push(c);
            }
        }

        while (!operators.empty())
        {
            pf.append(operators.pop());
        }
        this.postfix = pf.toString();
    }

    public void calculateResult()
    {
        if (this.postfix.isEmpty())
        {
            convertToPostfix();
        }

        Stack<Integer> values = new Stack<>();

        for (char c : this.postfix.toCharArray())
        {
            if (Character.isDigit(c))
            {
                values.push(c - '0');
            }
            else
            {
                int val2 = values.pop();
                int val1 = values.pop();

                switch (c)
                {
                    case '+':
                        values.push(val1 + val2);
                        break;
                    case '-':
                        values.push(val1 - val2);
                        break;
                    case '*':
                        values.push(val1 * val2);
                        break;
                    case '/':
                        if (val2 == 0)
                            throw new ArithmeticException("Деление на ноль!");
                        values.push(val1 / val2);
                        break;
                }
            }
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

    public int getResult()
    {
        return result;
    }
}