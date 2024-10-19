#include <iostream>
using namespace std;
#include "stackc.cpp"
#include "stacki.cpp"

int converttoint(char (&number)[10], int size) {
    int result=0;
    for (int i = 0; i < size; ++i) {
        result = result * 10 + (number[i] - '0');
    }
    return result;
}

int getmax(int minmax[10000], int minmaxcount) {
    int max=minmax[0];
    for (int p=1;p<minmaxcount;p++) {
        if (minmax[p]>max) max=minmax[p];
    }
    return max;
}

int getmin(int minmax[10000], int minmaxcount) {
    int min=minmax[0];
    for (int p=1;p<minmaxcount;p++) {
        if (minmax[p]<min) min=minmax[p];
    }
    return min;
}

int calculate(bool *err, char token, int arg1, int arg2) {
    if (token=='+') {
        return arg1+arg2;
    }
    else if (token=='-') {
        return arg1-arg2;
    }
    else if (token=='*') {
        return arg1*arg2;
    }
    else if (token=='/') {
        if (arg2==0) {
            *err=true;
            return 0;
        }
        return arg1/arg2;
    }
    else return 0;
}

int isnumber(char c) {
    if (c >= '0' && c <= '9') return 1;
    else return 0;
}

void printONP(char onp[10000], int ONPindex) {
    for (int i=0;i<ONPindex;i++) {
        cout<<onp[i];
    }
}

void calculateONP(char (&onp)[10000], int ONPindex) {
    StackI numbers;
    char token, longtoken[3]={' '}, number[10]={' '};
    bool err=false;
    int arg1=0, arg2=0, arg3=0, result, longtokencount=0, minmax[10000]={0}, minmaxcount=0, min, max, numcount=0;

    for(int i=0;(i<ONPindex-1) && (err==false);i++) {
        token = onp[i];
        if ((token=='I')||(token=='F')||(token=='M')||(token=='I')||(token=='N')||(token=='A')||(token=='X')) {
            longtoken[longtokencount] = token;
            longtokencount++;
        }
        if ((isnumber(token))&&(onp[i-1]!='X')&&(onp[i-1]!='N')) {
            number[numcount]=token;
            numcount++;
        }
        if ((token==' ')&&(number[0]!=' ')) {
            numbers.push(converttoint(number, numcount));
            for (int p=0;p<10;p++) {
                number[p]= ' ';
            }
            numcount=0;
        }
        if ((isnumber(token))&&((onp[i-1]=='X')||(onp[i-1]=='N'))) {
            minmaxcount=token-'0';
        }
        if (longtoken[0]=='N'){
            cout<<token<<" ";
            numbers.print();
            cout<<endl;
            arg1 = numbers.pop();
            result = arg1*(-1);
            numbers.push(result);
            longtoken[0]=' ';
            longtoken[1]=' ';
            longtoken[2]=' ';
            longtokencount=0;
        }
        if ((token=='+')||(token=='-')||(token=='*')||(token=='/')) {
            cout<<token<<" ";
            numbers.print();
            cout<<endl;
            arg2 = numbers.pop();
            arg1 = numbers.pop();
            result = calculate(&err, token, arg1, arg2);
            if ((result==0)&&(err==true)) {
                cout<<"ERROR"<<endl;
            }
            else numbers.push(result);
        }
        if ((longtoken[0]=='I')&&(longtoken[1]=='F')) {
            cout<<"IF ";
            numbers.print();
            cout<<endl;
            arg3 = numbers.pop();
            arg2 = numbers.pop();
            arg1 = numbers.pop();
            if (arg1>0) numbers.push(arg2);
            else if (arg1<=0) numbers.push(arg3);
            longtoken[0]=' ';
            longtoken[1]=' ';
            longtokencount=0;
        }
        if ((longtoken[0]=='M')&&(longtoken[1]=='A')&&(longtoken[2]=='X')&&(minmaxcount!=0)) {
            cout<<"MAX"<<minmaxcount<<" ";
            numbers.print();
            cout<<endl;
            for (int k=0; k<minmaxcount;k++) {
                minmax[k]=numbers.pop();
            }
            max = getmax(minmax, minmaxcount);
            numbers.push(max);
            longtoken[0]=' ';
            longtoken[1]=' ';
            longtoken[2]=' ';
            longtokencount=0;
            minmaxcount=0;
        }
        if ((longtoken[0]=='M')&&(longtoken[1]=='I')&&(longtoken[2]=='N')&&(minmaxcount!=0)) {
            cout<<"MIN"<<minmaxcount<<" ";
            numbers.print();
            cout<<endl;
            for (int k=0; k<minmaxcount;k++) {
                minmax[k]=numbers.pop();
            }
            min = getmin(minmax, minmaxcount);
            numbers.push(min);
            longtoken[0]=' ';
            longtoken[1]=' ';
            longtoken[2]=' ';
            longtokencount=0;
            minmaxcount=0;
        }
    }
    if (err==false) cout<<numbers.pop();
}

char convert_to_read(char arg) {

    if (arg=='n') return 'N';
    else return arg;
}
int check_priority(char op1, char op2) {
    if ((op1=='N')||(op1=='X')) return 1;
    if ((op1==op2)&&(op1!='n')) return 1;
    if ((op1=='n')&&((op2=='F')||(op2=='*')||(op2=='/')||(op2=='+')||(op2=='-'))) return 1;
    if ((op1=='F')&&((op2=='*')||(op2=='/')||(op2=='+')||(op2=='-'))) return 1;
    if (((op1=='*')||(op1=='/'))&&((op2=='*')||(op2=='/')||(op2=='+')||(op2=='-'))) return 1;
    if (((op1=='+')||(op1=='-'))&&((op2=='+')||(op2=='-'))) return 1;
    return 0;
}

int main() {

    StackC tokenstack;
    StackI argumentstack;

    char c, temp, onp[10000]={' '}, fun[3];
    int num, funcount = 0, rows, i, ONPindex=0, coma=0, openbracket=0, Mfuns=0;
    bool Ifun=false;

    cin>>rows;

    for(i=0;i<rows;i++) {

        while (c = getchar()) {

            if ((c=='I')||(c=='F')||(c=='N')||(c=='M')||(c=='A')||(c=='X')) {
                fun[funcount] = c;
                funcount++;
            }
            if ((c >= '0' && c <= '9')) {
                onp[ONPindex++] = c;
            }
            if ((c == ' ')&&(onp[ONPindex-1]!=' ')&&(ONPindex!=0)) {
                onp[ONPindex++] = c;
            }
            if (c =='(') {
                tokenstack.push(c);
            }
            if ((c =='+')||(c=='-'||(c=='/')||(c=='*'))) {
                while (check_priority(tokenstack.top(), c)) {
                    temp = tokenstack.pop();
                    temp = convert_to_read(temp);
                    onp[ONPindex]=temp;
                    onp[++ONPindex]=' ';
                    ONPindex++;
                }
                if (!check_priority(tokenstack.top(), c)) tokenstack.push(c);
            }
            if (fun[0]=='N') {
                while (check_priority(tokenstack.top(), 'n')) {
                    temp = tokenstack.pop();
                    temp = convert_to_read(temp);
                    onp[ONPindex]=temp;
                    onp[++ONPindex]=' ';
                    ++ONPindex;
                }
                if (!check_priority(tokenstack.top(), 'n')) tokenstack.push('n');
                fun[0] = ' ';
                fun[1] = ' ';
                fun[2] = ' ';
                funcount = 0;
            }
            if ((fun[0]=='I')&&(fun[1]=='F')) {
                Ifun = true;
                tokenstack.push('F');
                fun[0] = ' ';
                fun[1] = ' ';
                funcount = 0;
            }
            if ((fun[0]=='M')&&(fun[1]=='I')&&(fun[2]=='N')) {
                Mfuns++;
                tokenstack.push('N');
                fun[0] = ' ';
                fun[1] = ' ';
                fun[2] = ' ';
                funcount = 0;
            }
            if ((fun[0]=='M')&&(fun[1]=='A')&&(fun[2]=='X')) {
                Mfuns++;
                tokenstack.push('X');
                fun[0] = ' ';
                fun[1] = ' ';
                fun[2] = ' ';
                funcount = 0;
            }
            if (c=='.') {
                while (tokenstack.top()!=0) {
                    temp = tokenstack.pop();
                    if (temp=='F') {
                        onp[ONPindex] = 'I';
                        onp[++ONPindex] = 'F';
                    }
                    else {
                        temp = convert_to_read(temp);
                        onp[ONPindex] = temp;
                    }
                    onp[++ONPindex]=' ';
                    ++ONPindex;
                }
                break;
            }
            if (c==')') {
                while (tokenstack.top()!='(') {
                    temp = tokenstack.pop();
                    if (temp=='F') {
                        onp[ONPindex] = 'I';
                        onp[++ONPindex] = 'F';
                    }
                    else {
                        temp = convert_to_read(temp);
                        onp[ONPindex] = temp;
                    }
                    onp[++ONPindex]=' ';
                    ++ONPindex;
                }
                if (tokenstack.top()=='(') {tokenstack.pop();}
            }
            if (Ifun==true) {
                if (c==',') {
                    while (tokenstack.top()!='(') {
                        temp = tokenstack.pop();
                        temp = convert_to_read(temp);
                        onp[ONPindex] = temp;
                        onp[++ONPindex]=' ';
                        ++ONPindex;
                    }
                    if (tokenstack.top()=='(') {tokenstack.pop();}
                    tokenstack.push('(');
                }
                if (c=='(') { 
                    tokenstack.push('(');
                }
                if (c==')') {
                    if (tokenstack.top()=='(') tokenstack.pop();
                    if (tokenstack.top()=='F') {
                        tokenstack.pop();
                        onp[ONPindex] = 'I';
                        onp[++ONPindex] = 'F';
                        ++ONPindex;
                    }
                }
            }
            if (Mfuns) {
                if (c==',') {
                    while (tokenstack.top()!='(') {
                        temp = tokenstack.pop();
                        temp = convert_to_read(temp);
                        onp[ONPindex] = temp;
                        onp[++ONPindex]=' ';
                        ++ONPindex;
                    }
                    if (tokenstack.top()=='(') {tokenstack.pop();}
                    tokenstack.push('(');
                    coma++;
                }
                if (c=='(') { 
                    openbracket++; 
                    tokenstack.push('(');
                }
                if ((c=='(')&&(openbracket>1)) {
                    argumentstack.push(coma);
                    coma=0;
                }
                if (c==')') {
                    if (tokenstack.top()=='(') tokenstack.pop();
                    if (tokenstack.top()=='X') {
                        tokenstack.pop();
                        onp[ONPindex] = 'M';
                        onp[++ONPindex] = 'A';
                        onp[++ONPindex] = 'X';
                        num = coma+1;
                        onp[++ONPindex] = num + '0';
                        ++ONPindex;
                        Mfuns--;
                    }
                    else if (tokenstack.top()=='N') {
                        tokenstack.pop();
                        onp[ONPindex] = 'M';
                        onp[++ONPindex] = 'I';
                        onp[++ONPindex] = 'N';
                        num = coma+1;
                        onp[++ONPindex] = num + '0';
                        ++ONPindex;
                        Mfuns--;
                    }
                    else if (tokenstack.top()=='F') {
                        tokenstack.pop();
                        onp[ONPindex] = 'I';
                        onp[++ONPindex] = 'F';
                        ++ONPindex;
                    }
                    if (tokenstack.top()!=0) coma = argumentstack.pop();
                }
            }
        }
        cout<<endl;
        printONP(onp, ONPindex);
        cout<<endl;
        calculateONP(onp, ONPindex);
        cout<<endl;
        cout<<endl;
        ONPindex=0;
        coma=0;
        openbracket=0;
        Mfuns=0;
    }  
return 0;
}