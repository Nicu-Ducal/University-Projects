#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;


class Complex {
    private:
        double re, im;

        friend class Complex_Matrix;
        friend Complex operator /(const double& lhs, const Complex& rhs);
        friend ostream &operator <<(ostream &os, const Complex &rhs);
        friend istream &operator >>(istream &in, Complex &rhs);

    public:
        Complex(double re_val = 0, double im_val = 0) : re (re_val), im (im_val) {};
        Complex(const Complex &source) = default;
        ~Complex() = default;
        Complex& operator=(const Complex&) = default;

        double get_re() const { return re; }
        double get_im() const { return im; }
        void set_re(double num){ re = num; }
        void set_im(double num){ im = num; }
        void set_complex(double num1, double num2){ re = num1; im = num2; }
        double modul() const { return std::sqrt(re * re + im * im); }
        Complex sqrt() const {
            Complex temp = Complex(re + this -> modul(), im);
            return (temp / temp.modul()) * std::sqrt(this -> modul());
        }


        //Operatii intre numere complexe
        Complex operator +(const Complex &z){
            return Complex(re + z.re, im + z.im);
        }

        Complex operator -(const Complex &z){
            return Complex(re - z.re, im - z.im);
        }

        Complex operator *(const Complex &z){
            return Complex(re * z.re - im * z.im, re * z.im + im * z.re);
        }

        Complex operator /(const Complex &z){
            return Complex(
                (re * z.re + im * z.im) / (z.re * z.re + z.im * z.im),
                (im * z.re - re * z.im) / (z.re * z.re + z.im * z.im)
                );
        }

        //Operatii dintre complexe si numere reale
        Complex operator +(const double num){
            return Complex(re + num, im);
        }

        Complex operator -(){
            return Complex(-re, -im);
        }

        Complex operator -(const double num){
            return Complex(re - num, im);
        }

        Complex operator *(const double num){
            return Complex(re * num, im * num);
        }

        Complex operator /(const double num){
            return Complex(re / num, im / num);
        }

        Complex operator =(const double rhs){
            re = rhs; im = 0;
            return *this;
        }
};

///Pentru clasa Complex
Complex operator +(const double& lhs, Complex& rhs){
    return rhs + lhs;
}
Complex operator *(const double& lhs, Complex& rhs){
    return rhs * lhs;
}
Complex operator -(const double& lhs, Complex& rhs){
    return -(rhs - lhs);
}
Complex operator /(const double& lhs, const Complex& rhs){
    return Complex((lhs * rhs.re) / rhs.modul(), -(lhs * rhs.im) / rhs.modul());
}

ostream &operator <<(ostream &out, const Complex &rhs){
    if (rhs.im == 0)
        out << rhs.re;
    else if (rhs.re == 0 && rhs.im != 0)
        out << rhs.im << "i";
    else if (rhs.re != 0 && rhs.im > 0)
        out << rhs.re <<  "+" << rhs.im << "i";
    else if (rhs.re != 0 && rhs.im < 0)
        out << rhs.re << rhs.im << "i";
    return out;
}

istream &operator >>(istream &in, Complex &rhs){
    string temp;
    in >> temp;
    int pos1 = -1, pos2 = -1, op = 1;
    string re_num, im_num;
    for (unsigned int i = 0; i < temp.length(); i++)
        if (temp[i] == '+' || temp[i] == '-'){
            pos1 = i;
            op = (temp[i] == '-') ? -1 : 1;
        }
        else if (temp[i] == 'i')
            pos2 = i;
    if ((pos1 == -1 || pos1 == 0) && pos2 == -1){
        rhs.re = stod(temp);
        rhs.im = 0;
    }
    else if (pos2 - pos1 == 1){
        if (pos1 == -1 || pos1 == 0)
            rhs.re = 0;
        else rhs.re = stod(temp.substr(0, pos1));
        rhs.im = op;
    }
    else if ((pos1 == -1 || pos1 == 0) && pos2 != -1){
        rhs.re = 0;
        rhs.im = op * stod(temp.substr(pos1 + 1, pos2 - pos1 - 1));
    }
    else{
        rhs.re = stod(temp.substr(0, pos1));
        rhs.im = op * stod(temp.substr(pos1 + 1, pos2 - pos1 - 1));
    }
    return in;
}

class Complex_Matrix {
private:
    int row, col;
    Complex **matrix;
    friend ostream &operator <<(ostream &out, const Complex_Matrix &rhs);
    friend istream &operator >>(istream &in, Complex_Matrix &rhs);
public:
    Complex_Matrix(int row_val = 2, int col_val = 2, Complex val = 0);
    Complex_Matrix(const Complex_Matrix &source);
    ~Complex_Matrix();
    Complex_Matrix& operator=(const Complex_Matrix &source);

    //Operatii
    Complex_Matrix operator +(const Complex_Matrix &rhs);
    Complex_Matrix operator *(const Complex_Matrix &rhs);
};

///Pentru clasa Complex_Matrix
Complex_Matrix::Complex_Matrix(int row_val, int col_val, Complex val) : row(row_val), col(col_val) {
    matrix = new Complex* [row];
    for (int i = 0; i < row; i++)
        matrix[i] = new Complex[col];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = val;
}

Complex_Matrix::Complex_Matrix(const Complex_Matrix &source){
    col = source.col;
    row = source.row;
    matrix = new Complex* [row];
    for (int i = 0; i < row; i++)
        matrix[i] = new Complex[col];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = source.matrix[i][j];
}

Complex_Matrix::~Complex_Matrix(){
    for (int i = 0; i < row; i++)
        delete [] matrix[i];
    delete [] matrix;
    row = 0;
    col = 0;
}

Complex_Matrix &Complex_Matrix::operator=(const Complex_Matrix &source){
    if (this == &source)
        return *this;
    for(int i = 0; i < row; i++)
        delete [] matrix[i];
    delete [] matrix;
    col = source.col;
    row = source.row;
    matrix = new Complex* [row];
    for (int i = 0; i < row; i++)
        matrix[i] = new Complex[col];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = source.matrix[i][j];
    return *this;
}

Complex_Matrix Complex_Matrix::operator +(const Complex_Matrix &rhs){
        if (row != rhs.row || col != rhs.col) throw -1;
        Complex_Matrix ans = Complex_Matrix(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                ans.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
        return ans;
    }

Complex_Matrix Complex_Matrix::operator *(const Complex_Matrix &rhs) {
        if (col != rhs.row) throw -1;
        Complex_Matrix ans = Complex_Matrix(row, rhs.col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < rhs.col; j++)
                for (int k = 0; k < col; k++)
                    ans.matrix[i][j] = ans.matrix[i][j] + this->matrix[i][k] * rhs.matrix[k][j];
        return ans;
    }

ostream &operator <<(ostream &out, const Complex_Matrix &rhs){
    for (int i = 0; i < rhs.row; i++){
        for (int j = 0; j < rhs.col; j++)
            out << rhs.matrix[i][j] << "\t\t";
        out << "\n";
    }
    return out;
}

istream &operator >>(istream &in, Complex_Matrix &rhs){
    for (int i = 0; i < rhs.row; i++)
        for (int j = 0; j < rhs.col; j++)
            in >> rhs.matrix[i][j];
    return in;
}

void testare(){
    ifstream fin("tester.in");
    cout << "Testarea clasei de numere complexe:\n";
    Complex z1, z2;
    fin >> z1 >> z2;

    cout << "Initial\nz1 = ";
    cout << z1 << endl << "z2 = " << z2 << endl;

    cout << "Verificare operatii cu numere reale:\n";
    cout << "Adunare cu 5:\n";
    cout << z1 + 5 << endl << 5 + z2 << endl;

    cout << "Scadere cu 10:\n";
    cout << z1 - 10 << endl << z2 - 10 << endl;

    cout << "10 - z1(z2):\n";
    cout << 10 - z1 << endl << 10 - z2 << endl;

    cout << "Inmultire cu 5 si cu 6:\n";
    cout << z1 * 5 << endl << 6 * z2 << endl;

    cout << "Impartire la 10 si la 2:\n";
    cout << z1 / 10 << endl << z2 / 2 << endl;

    cout << endl;

    //Verificare operatii cu complexe
    cout << "Operatii cu numere complexe:\n";
    cout << "z1 + z2 = " << z1 + z2 << endl;

    cout << "z1 - z2 = " << z1 - z2 << endl;

    cout << "z1 * z2 = " << z1 * z2 << endl;

    cout << "z1 / z2 = " << z1 / z2 << endl;

    cout << "|z1| = " << z1.modul() << endl;

    cout << "|z2| = " << z2.modul() << endl;

    cout << "sqrt(z1) = " << z1.sqrt() << endl;
    cout << "sqrt(z2) = " << z2.sqrt() << endl;
    cout << endl;

    cout << "Testarea clasei de matrici de numere complexe:\n";

    int k, t; // k - randuri, t - coloane
    fin >> k;
    fin >> t;
    Complex_Matrix A = Complex_Matrix(k, t);
    fin >> A;

    fin >> k;
    fin >> t;
    Complex_Matrix B = Complex_Matrix(k, t);
    fin >> B;

    Complex_Matrix M = Complex_Matrix(2, 2, 3);
    Complex_Matrix N = Complex_Matrix(2, 2, 4);
    cout << "Matricea A:\n" << A << "Matricea B:\n" << B << endl;
    cout << "A + B:\n" << A + B << endl;
    cout << "A * B:\n" << A * B << endl;
    cout << "M * N:\n" << M * N << endl;

    Complex_Matrix P;
    P = B;
    cout << "P = B:\n" << P << endl;

    Complex_Matrix X = Complex_Matrix(B);
    cout << "Constructor de copiere - X = B:\n" << X << endl;

    fin.close();
}

int main(){

    testare();

    return 0;
}


