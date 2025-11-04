package org.example.kalkulatorgui;

import javafx.fxml.FXML;
import javafx.scene.control.TextField;

public class Controller
{

    private Calculator calculator;

    @FXML
    private TextField infixField;

    @FXML
    private TextField postfixField;

    @FXML
    private TextField resultField;

    @FXML
    protected void onConvertToPostfixClick()
    {
        String expression = infixField.getText();
        if (expression.isEmpty())
        {
            postfixField.setText("Ошибка: введите выражение");
            return;
        }

        try
        {
            this.calculator = new Calculator(expression);
            this.calculator.convertToPostfix();

            postfixField.setText(this.calculator.getPostfix());
            resultField.clear();
        }
        // Изменено: теперь здесь общее сообщение
        catch (IllegalArgumentException e)
        {
            postfixField.setText("Ошибка: некорректное выражение");
        }
        catch (Exception e)
        {
            postfixField.setText("Неизвестная ошибка");
        }
    }

    @FXML
    protected void onCalculateClick()
    {
        String currentExpression = infixField.getText();
        if (currentExpression.isEmpty())
        {
            resultField.setText("Ошибка: введите выражение");
            return;
        }

        try
        {
            if (this.calculator == null || !this.calculator.getInfix().equals(currentExpression))
            {
                this.calculator = new Calculator(currentExpression);
                this.calculator.convertToPostfix();
                postfixField.setText(this.calculator.getPostfix());
            }

            this.calculator.calculateResult();
            resultField.setText(String.valueOf(this.calculator.getResult()));

        }
        catch (ArithmeticException e)
        {
            resultField.setText("Деление на ноль!");
        }
        catch (IllegalArgumentException e)
        {
            resultField.setText("Ошибка: некорректное выражение");
        }
        catch (Exception e)
        {
            resultField.setText("Ошибка: некорректное выражение");
        }
    }
}