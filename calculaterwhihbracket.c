#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_EXPR_SIZE 100

char expr[MAX_EXPR_SIZE];
int pos = 0;
double getNumber();
double expression();
double power();
double factor();
double term();
double calculate();
int main() {
    printf("Enter an expression: ");
    scanf("%99s", expr);
    double result = calculate();
    printf("Result: %lf\n", result);
    return 0;
}

double getNumber() {
    double number = 0.0;
    int decimal = 0;
    int divisor = 1;
    int sign = 1;

    if (expr[pos] == '-') {
        sign = -1;
        pos++;
    } else if (expr[pos] == '+') {
        pos++;
    }

    while (isdigit(expr[pos]) || expr[pos] == '.') {
        if (expr[pos] == '.') {
            decimal = 1;
        } else if (decimal == 0) {
            number = number * 10 + (expr[pos] - '0');
        } else {
            divisor *= 10;
            number = number + (double)(expr[pos] - '0') / divisor;
        }
        pos++;
    }

    return sign * number;
}

double power() {
    double result = factor();

    while (expr[pos] == '^') {
        pos++;
        double nextFactor = factor();
        result = pow(result, nextFactor);
    }

    return result;
}

double factor() {
    if (expr[pos] == '(') {
        pos++;
        double result = expression();
        if (expr[pos] == ')') {
            pos++;
            return result;
        } else {
            printf("Error: Missing closing bracket\n");
            return 0.0;
        }
    }
    return getNumber();
}

double term() {
    double result = power();

    while (expr[pos] == '*' || expr[pos] == '/') {
        char op = expr[pos];
        pos++;
        double nextFactor = power();
        if (op == '*') {
            result *= nextFactor;
        } else {
            result /= nextFactor;
        }
    }

    return result;
}

double expression() {
    double result = term();

    while (expr[pos] == '+' || expr[pos] == '-') {
        char op = expr[pos];
        pos++;
        double nextTerm = term();
        if (op == '+') {
            result += nextTerm;
        } else {
            result -= nextTerm;
        }
    }

    return result;
}

double calculate() {
    pos = 0;
    return expression();
}
