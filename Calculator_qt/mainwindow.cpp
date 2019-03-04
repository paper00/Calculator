#include <bits/stdc++.h>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

Calculator::Calculator(string exp) {
    exp = '#' + exp + '#';
    this->exp = exp;
    symbol.push('#');
    state = 0;
}
bool Calculator::error1() {
    if (state==1) {
        state = 404;
        return true;
    }
    return false;
}
bool Calculator::error2() {
    if (state==0) {
        state = 404;
        return true;
    }
    return false;
}
void Calculator::operate() {
    if (symbol.top()=='!') {
        double n = num.top();
        num.pop();
        if (n)
            num.push(0);
        else
            num.push(1);
        state = 1;
        symbol.pop();
        return;
    }
    double a, b;
    a = num.top();
    num.pop();
    b = num.top();
    num.pop();
    switch(symbol.top()) {
        case '+': num.push(b+a); break;
        case '-': num.push(b-a); break;
        case '*': num.push(b*a); break;
        case '/': num.push(b/a); break;
        case '&': {
            if (a && b)
                num.push(1);
            else
                num.push(0);
            symbol.pop();
        }; break;
        case '|': {
            if (a || b)
                num.push(1);
            else
                num.push(0);
            symbol.pop();
        }; break;
    }
    state = 1;
    symbol.pop();
}
double Calculator::getResult() {
    for (int i=1; i < exp.size(); i++) {
        // Operate double type (ex: '.' symbol)
        if (isdigit(exp[i]) || exp[i]=='.') {
            if (error1()) return 0;
            // If omitted the 0 in front of '.'
            bool jud = false;
            int j = -1;
            if (exp[i]=='.') {
                j = (i++)-1;
                jud = true;
            }
            double n = exp[i] - '0';
            while (isdigit(exp[i+1]) || exp[i+1]=='.') {
                if (exp[i+1]=='.') {
                    if (jud) {
                        // If reappear '.'
                        state = 404;
                        return 0;
                    }
                    j = (i++);
                    jud = true; continue;
                }
                n = n*10 + exp[(i++)+1] - '0';
            }
            if (j!=-1 || jud)
                for (int k=0; k<(i-j-1); k++)
                    n *= 0.1;
            num.push(n);
            state = 1;
        }
        // Process space (ex: ' ' space)
        else if (exp[i]==' ') continue;
        else if (exp[i]=='&' || exp[i]=='|') {
            if (exp[i+1]!=exp[i]) {
                state = 404;
                return 0;
            }
            if (error2()) return 0;
            while ((symbol.top()=='|' && exp[i]!='&') || (symbol.top()!='#' && symbol.top()!='(' && symbol.top()!='|'))
                operate();
            symbol.push(exp[i++]);
            symbol.push((exp[i]));
            state = 0;
        }
        else if (exp[i]=='!' || exp[i]=='(') {
            if (num.size())
                if (error1()) return 0;
            symbol.push(exp[i]);
            state = 0;
        }
        else if (exp[i]=='+' || exp[i]=='-') {
            if (error2()) return 0;
            while (symbol.top()!='#' && symbol.top()!='(' && symbol.top()!='&' && symbol.top()!='|')
                operate();
            symbol.push(exp[i]);
            state = 0;
        }
        else if (exp[i]=='*' || exp[i]=='/') {
            if (error2()) return 0;
            while (symbol.top()=='*' || symbol.top()=='/' || symbol.top()=='!')
                operate();
            symbol.push(exp[i]);
            state = 0;
        }
        else if (exp[i]==')') {
            while (symbol.top()!='(' && num.size()>1)
                operate();
            symbol.pop();
            if (symbol.empty()) {
                state = 404;
                return 0;
            }
        }
        else if (i==(exp.size()-1)) {
            while(symbol.size()!=1 && num.size()>1 || symbol.top()=='!' && num.size()>0)
                operate();
            symbol.pop();
            if (!symbol.empty()) {
                state = 404;
                return 0;
            }
            return num.top();
        }
        else {
            state = 404;
            return 0;
        }
    }
}
int Calculator::getState() {
    return state;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->lineEdit->setAlignment(Qt::AlignRight);
    ui->lineEdit_2->setAlignment(Qt::AlignRight);
}
MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::on_pushButton_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"0");
}

void MainWindow::on_pushButton_23_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"1");
}

void MainWindow::on_pushButton_2_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"2");
}

void MainWindow::on_pushButton_3_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"3");
}

void MainWindow::on_pushButton_4_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"4");
}

void MainWindow::on_pushButton_5_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"5");
}

void MainWindow::on_pushButton_6_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"6");
}

void MainWindow::on_pushButton_7_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"7");
}

void MainWindow::on_pushButton_8_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"8");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text()+"9");
}

void MainWindow::on_pushButton_10_clicked() {
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}

void MainWindow::on_pushButton_11_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+".");
}

void MainWindow::on_pushButton_12_clicked() {
    Calculator c(ui->lineEdit->text().toStdString());
    ui->lineEdit_2->setText(ui->lineEdit->text());
    ui->lineEdit->setText(QString::number(c.getResult()));
    if (c.getState()==404) {
        ui->lineEdit->setText("error");
    }
}

void MainWindow::on_pushButton_13_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"+");
}

void MainWindow::on_pushButton_14_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"-");
}

void MainWindow::on_pushButton_15_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"*");
}

void MainWindow::on_pushButton_16_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"/");
}

void MainWindow::on_pushButton_17_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text().left(ui->lineEdit->text().length()-1));
}

void MainWindow::on_pushButton_18_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"!");
}

void MainWindow::on_pushButton_19_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"&");
}

void MainWindow::on_pushButton_20_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"|");
}

void MainWindow::on_pushButton_21_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+"(");
}

void MainWindow::on_pushButton_22_clicked() {
    ui->lineEdit->setText(ui->lineEdit->text()+")");
}
