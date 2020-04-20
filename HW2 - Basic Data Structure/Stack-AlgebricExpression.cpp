#include <iostream>
#include "string"

using namespace std;

int sum(int a, int b, int p){
    int out = (int)(((long long int) a + (long long int) b) % p);
    return out;
}

int diff(int a, int b, int p){
    int out = (int)(((long long int) a - (long long int) b) % p);
    return out;
}

int mult(int a, int b, int p){
    int out = (int)(((long long int) a *(long long int) b) % p);
    return out;
}

int main() {

    string expression;

    getline(cin, expression);

    size_t n = expression.length();
    expression = '(' + expression + "+0)";

    int* operands = new int[n];
    char* operators = new char[n];

    size_t pos = 0, prev = 0, start, pos1, next;
    int s1head = 0, s2head = 0, p = 1000000007, value, valid;
    char sign = '+' , opCurr, tS;


    while ((pos = expression.find_first_of("+-*()",prev)) < (n+2)){

        if (pos && (expression[pos] == '(')){
            operators[s2head++] = '(';
        }

        else if (expression[pos] == ')'){
                tS = operators[s2head - 1];
                switch (tS) {
                    case '(':{
                        s2head--; // pop
                        break;
                    }
                    case '+' : {
                        s1head--;
                        operands[s1head - 1] = sum(operands[s1head] , operands[s1head - 1], p);  // push operands
                        s2head = s2head - 2; // pop operators
                        break;
                    }
                    case '-' : {
                        s1head--;
                        operands[s1head - 1] = diff(operands[s1head - 1], operands[s1head], p); // push operands
                        s2head = s2head - 2; // pop operators
                        break;
                    }
                    case '*' : {
                        s1head--;
                        operands[s1head - 1] = mult(operands[s1head - 1] , operands[s1head],p); s2head--;
                        if (s2head > 0){
                            if (operators[s2head - 1] == '+'){
                                s2head--; s1head--;
                                operands[s1head - 1] = sum(operands[s1head - 1] , operands[s1head], p);
                            }
                            else if (operators[s2head - 1] == '-'){
                                s2head--; s1head--;
                                operands[s1head - 1] = diff(operands[s1head - 1] , operands[s1head], p);
                            }
                        }
                        s2head--;
                        break;
                    }
                    default:
                        break;
                }
        } else {
            switch (expression[pos]) {
                case '*': {
                    if (s2head == 0) {
                        operators[s2head++] = '*';
                    } else if (s2head > 0) {
                        tS = operators[s2head - 1];
                        if (tS == '*') {
                            s1head--;
                            operands[s1head - 1] = mult(operands[s1head - 1], operands[s1head], p);
                        } else {
                            operators[s2head++] = '*';
                        }
                    }
                    break;
                }
                case '+' : {
                    if (s2head == 0) {
                        operators[s2head++] = '+';
                    } else if (s2head > 0) {
                        tS = operators[s2head - 1];
                        if (tS == '+') {
                            s1head--;
                            operands[s1head - 1] = sum(operands[s1head - 1], operands[s1head], p);
                        } else if (tS == '-') {
                            s1head--;
                            operands[s1head - 1] = diff(operands[s1head - 1], operands[s1head], p);
                            operators[s2head - 1] = '+';
                        } else if (tS == '*') {
                            s1head--;
                            operands[s1head - 1] = mult(operands[s1head - 1], operands[s1head], p);
                            if (s2head > 1) {
                                if (operators[s2head - 2] == '+') {
                                    s2head--; s1head--;
                                    operands[s1head - 1] = sum(operands[s1head - 1], operands[s1head], p);
                                }
                                else if (operators[s2head - 2] == '-') {
                                    s2head--; s1head--;
                                    operands[s1head - 1] = diff(operands[s1head - 1], operands[s1head], p);
                                }
                            }
                            operators[s2head - 1] = '+';
                        } else {
                            operators[s2head++] = '+';
                        }
                    }
                    break;
                }
                case '-' : {
                    if (s2head == 0) {
                        operators[s2head++] = '-';
                    } else if (s2head > 0) {
                        tS = operators[s2head - 1];
                        if (tS == '-') {
                            s1head--;
                            operands[s1head - 1] = diff(operands[s1head - 1], operands[s1head], p);
                        } else if (tS == '+') {
                            s1head--;
                            operands[s1head - 1] = sum(operands[s1head - 1], operands[s1head], p);
                            operators[s2head - 1] = '-';
                        } else if (tS == '*') {
                            s1head--;
                            operands[s1head - 1] = mult(operands[s1head - 1], operands[s1head], p);
                            if (s2head > 1) {
                                if (operators[s2head - 2] == '+') {
                                    s2head--; s1head--;
                                    operands[s1head - 1] = sum(operands[s1head - 1], operands[s1head], p);
                                }
                                else if (operators[s2head - 2] == '-') {
                                    s2head--; s1head--;
                                    operands[s1head - 1] = diff(operands[s1head - 1], operands[s1head], p);
                                }
                            }
                            operators[s2head - 1] = '-';
                        } else {
                            operators[s2head++] = '-';
                        }
                    }
                    break;
                }
            }
        }

        start = pos + 1;
        if (start > 0 && (expression[start-1] == ')')){
            next = expression.find_first_of("*-()+", start);
            value = 0;
            valid = 3;
        } else {
            while ((pos1 = expression.find_first_of("+-", start)) == start) {
                opCurr = expression[pos1];
                if (opCurr == '+' & sign == '+') {
                    start++;
                } else if (opCurr == '+' & sign == '-') {
                    start++;
                    sign = '-';
                } else if (opCurr == '-' & sign == '+') {
                    start++;
                    sign = '-';
                } else if (opCurr == '-' & sign == '-') {
                    start++;
                    sign = '+';
                }
            }
            next = expression.find_first_of("*-()+", start);
            value = sign == '-';
            valid = 0;
            if (next != start) {
                valid = 1;
                if (sign == '+') {
                    value = stoi(expression.substr(start, next - start));
                } else {
                    value = -1 * stoi(expression.substr(start, next - start));
                }
            }
        }
        if (valid == 1){
            operands[s1head++] = value;

        }
        prev = next;
        if (valid == 0){
            if (value == 1){
                if (operators[s2head - 1] == '+')
                    operators[s2head - 1] = '-';
                else
                    operators[s2head - 1] = '+';
            }
        }

    }

    if (operands[0] < 0)
        cout << operands[0] + p;
    else
        cout << operands[0];
    cout << endl;

}