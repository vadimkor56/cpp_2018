#include <fstream>

using namespace std;

ifstream cin("../input.txt");
ofstream cout("../output.txt");

class Matrix {
public:
    Matrix(int n_, int m_) : n(n_), m(m_), data(new double[n * m]) {}

    ~Matrix() {}

    Matrix(const Matrix &other) {
        //if (n != 0 && m != 0) delete [] data;
        n = other.n;
        m = other.m;
        data = new double[n * m];
        for (int i = 0; i < n * m; ++i)
            data[i] = other.data[i];
    }

    Matrix& operator=(const Matrix &other) {
        if (this != &other) {
            delete [] data;
            n = other.n;
            m = other.m;
            data = new double[n * m];
            for (int i = 0; i < n * m; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    Matrix& operator+=(Matrix &table1) {
        for (int i = 0; i < n * m; ++i) {
            data[i] += table1.data[i];
        }
        return *this;
    }

    Matrix& operator+=(double &d) {
        for (int i = 0; i < n * m; ++i) {
            data[i] = data[i] + d;
        }
        return *this;
    }

    Matrix& operator-=(Matrix &table1) {
        for (int i = 0; i < n * m; ++i) {
            data[i] = data[i] - table1.data[i];
        }
        return *this;
    }

    Matrix& operator-=(double &d) {
        for (int i = 0; i < n * m; ++i) {
            data[i] = data[i] - d;
        }
        return *this;
    }


    Matrix& operator*=(double &d) {
        for (int i = 0; i < n * m; ++i) {
            data[i] *= d;
        }
        return *this;
    }

    Matrix& operator*=(Matrix &table1) {
        Matrix res(n, table1.m);
        for (int i = 0; i < n * table1.m; ++i) {
            for (int j = 0; j < table1.m; ++j)
                res.data[i] += data[(i / table1.m) * n + j] * table1.data[i % n + j * n];
        }
        for (int i = 0; i < n * m; ++i)
            data[i] = res.data[i];
        return *this;
    }

    Matrix operator+(Matrix &table1) const {
        Matrix res = *this;
        res += table1;
        return res;
    }

    Matrix operator+(double &d) const {
        Matrix res = *this;
        res -= d;
        return res;
    }

    Matrix operator-(Matrix &table1) const {
        Matrix res = *this;
        res -= table1;
        return res;
    }

    Matrix operator-(double d) const {
        Matrix res = *this;
        res -= d;
        return res;
    }

    Matrix operator*(double d) const{
        Matrix res = *this;
        res *= d;
        return res;
    }

    Matrix operator*(Matrix &table1) const{
        Matrix res = *this;
        res *= table1;
        return res;
    }


    Matrix& operator-() {
        for (int i = 0; i < n * m; ++i)
            data[i] = -data[i];
        return *this;
    }

    double& operator()(int i, int j) {
        return data[i * n + j];
    }

    double operator()(int i, int j) const {
        return data[i * n + j];
    }


    Matrix& transpose() {
        auto *B = new double[m * n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                B[i * n + j] = data[j * m + i];

        for (int i = 0; i < n * m; i++)
            data[i] = B[i];
        delete[] B;
        swap(n, m);
        return *this;
    }

    Matrix& dot(Matrix &table1) {
        Matrix res(n, table1.m);
        for (int i = 0; i < n * table1.m; ++i) {
            for (int j = 0; j < table1.m; ++j)
                res.data[i] += data[(i / table1.m) * n + j] * table1.data[i % n + j * n];
        }
        for (int i = 0; i < n * table1.m; ++i)
            data[i] = res.data[i];
        return *this;
    }

    int n = 0;
    int m = 0;
    double *data;

};

ofstream &operator<<(ofstream &os, const Matrix &table) {
    for (int i = 0; i < table.n; ++i) {
        for (int j = 0; j < table.m; ++j)
            os << table.data[i * table.n + j] << ' ';
        os << endl;
    }
    os << endl;
    return os;
}

ifstream &operator>>(ifstream &is, const Matrix &table) {
    for (int i = 0; i < table.n * table.m; ++i)
        is >> table.data[i];
    return is;
}

int main() {

    int n, m;
    double d = 2;
    cin >> n >> m;
    Matrix table1(n, m);
    Matrix table2(n, m);


    cin >> table1;
    cin >> table2;

    cout << "Tables:\n";
    cout << table1;
    cout << table2;

    Matrix table3 = table1;
    Matrix table4 = table1;
    Matrix table5 = table2;
    Matrix table6 = table2;

    cout << "Operator +:\n";
    table1 = table1 + table2;
    cout << table1;

    cout << "Operator -:\n";
    table1 = table1 - table2;
    cout << table1;

    cout << "Operator * (tab1 * 2):\n";
    table1 = table1 * d;
    cout << table1;

    cout << "Method dot (tab1 tab2):\n";
    Matrix tabb = table3.dot(table2);
    cout << tabb;


    cout << "Operator +=:\n";
    table1 += table2;
    cout << table1;

    cout << "Operator -=:\n";
    table1 -= table2;
    cout << table1;

    cout << "Operator *=:\n";
    table3 *= d;
    cout << table3;

    cout << "Operator -(unary):\n";
    table3 = -table3;
    cout << table3;

    cout << "Operator ():\n";
    cout << table3(1, 1) << endl << endl;

    cout << "Method transpose:\n";
    table3.transpose();
    cout << table3;

    table3(1, 1) = 1024;
    cout << table3;
    cout << (table3 * 3);
    cout << table3;

    return 0;
}