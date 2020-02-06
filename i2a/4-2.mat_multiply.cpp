#include "../playground/common.hpp"

using namespace std;
using playground::Color;

typedef vector<vector<int>> matrix;

matrix generateRandomMatrix(int row, int col = 0) {
    if (col == 0) {
        col = row;
    }
    matrix mat(row, vector<int>(col));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mat[i][j] = playground::randint(-10, 10);
        }
    }
    return mat;
}

void display(matrix m) {
    for (const auto &row : m) {
        cout << row << endl;
    }
    cout << endl;
}

matrix &operator+=(matrix &S, const matrix &A) {
    int size = S.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            S[i][j] += A[i][j];
        }
    }
    return S;
}
matrix &operator-=(matrix &S, const matrix &A) {
    int size = S.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            S[i][j] -= A[i][j];
        }
    }
    return S;
}

matrix Strassen(const matrix &A, const matrix &B) {
    if (!A.size() || !B.size() || A.size() != A[0].size() || B.size() != B[0].size() || A.size() != B.size()) {
        return {};
    }
    int size = A.size();
    if (size == 1) {
        return {{A[0][0] * B[0][0]}};
    }
    int half = (size + 1) / 2;

    matrix A11(half, vector<int>(half, 0));
    matrix A12(half, vector<int>(half, 0));
    matrix A21(half, vector<int>(half, 0));
    matrix A22(half, vector<int>(half, 0));
    matrix B11(half, vector<int>(half, 0));
    matrix B12(half, vector<int>(half, 0));
    matrix B21(half, vector<int>(half, 0));
    matrix B22(half, vector<int>(half, 0));
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            B11[i][j] = B[i][j];
        }
    }
    for (int i = 0; i < half; i++) {
        for (int j = half; j < size; j++) {
            A12[i][j - half] = A[i][j];
            B12[i][j - half] = B[i][j];
        }
    }
    for (int i = half; i < size; i++) {
        for (int j = 0; j < half; j++) {
            A21[i - half][j] = A[i][j];
            B21[i - half][j] = B[i][j];
        }
    }
    for (int i = half; i < size; i++) {
        for (int j = half; j < size; j++) {
            A22[i - half][j - half] = A[i][j];
            B22[i - half][j - half] = B[i][j];
        }
    }
    // display(A11);
    // display(A12);
    // display(A21);
    // display(A22);
    // display(B11);
    // display(B12);
    // display(B21);
    // display(B22);
    matrix S1(half, vector<int>(half, 0));
    matrix S2(half, vector<int>(half, 0));
    matrix S3(half, vector<int>(half, 0));
    matrix S4(half, vector<int>(half, 0));
    matrix S5(half, vector<int>(half, 0));
    matrix S6(half, vector<int>(half, 0));
    matrix S7(half, vector<int>(half, 0));
    matrix S8(half, vector<int>(half, 0));
    matrix S9(half, vector<int>(half, 0));
    matrix S10(half, vector<int>(half, 0));
    S1 += B12, S1 -= B22;
    S2 += A11, S2 += A12;
    S3 += A21, S3 += A22;
    S4 += B21, S4 -= B11;
    S5 += A11, S5 += A22;
    S6 += B11, S6 += B22;
    S7 += A12, S7 -= A22;
    S8 += B21, S8 += B22;
    S9 += A11, S9 -= A21;
    S10 += B11, S10 += B12;
    auto P1 = Strassen(A11, S1);
    auto P2 = Strassen(S2, B22);
    auto P3 = Strassen(S3, B11);
    auto P4 = Strassen(A22, S4);
    auto P5 = Strassen(S5, S6);
    auto P6 = Strassen(S7, S8);
    auto P7 = Strassen(S9, S10);
    matrix C11(half, vector<int>(half, 0));
    matrix C12(half, vector<int>(half, 0));
    matrix C21(half, vector<int>(half, 0));
    matrix C22(half, vector<int>(half, 0));
    C11 += P5, C11 += P4, C11 -= P2, C11 += P6;
    C12 += P1, C12 += P2;
    C21 += P3, C21 += P4;
    C22 += P5, C22 += P1, C22 -= P3, C22 -= P7;

    matrix C(size, vector<int>(size, 0));

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
        }
    }
    for (int i = 0; i < half; i++) {
        for (int j = half; j < size; j++) {
            C[i][j] = C12[i][j - half];
        }
    }
    for (int i = half; i < size; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C21[i - half][j];
        }
    }
    for (int i = half; i < size; i++) {
        for (int j = half; j < size; j++) {
            C[i][j] = C22[i - half][j - half];
        }
    }
    return C;
    if (size % 2) {
        for (int i = 0; i < size - 1; i++) {
            int tmp = 0;
            for (int k = 0; k < size; k++) {
                tmp += A[i][k] * B[k][size - 1];
            }
            C[i][size - 1] = tmp;
        }
        for (int j = 0; j < size; j++) {
            int tmp = 0;
            for (int k = 0; k < size; k++) {
                tmp += A[size - 1][k] * B[k][j];
            }
            C[size - 1][j] = tmp;
        }
    }
}

matrix force(const matrix &A, const matrix &B) {
    if (!A.size() || !B.size() || A.size() != A[0].size() || B.size() != B[0].size() || A.size() != B.size()) {
        return {};
    }
    int size = A.size();
    matrix C(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int tmp = 0;
            for (int k = 0; k < size; k++) {
                tmp += A[i][k] * B[k][j];
            }
            C[i][j] = tmp;
        }
    }
    return C;
}

int main(int argc, char **argv) {
    int size = argc > 1 ? stoi(argv[1]) : 50;
    auto A = generateRandomMatrix(size);
    auto B = generateRandomMatrix(size);
    cout << Color().fore(Color::F::Red).style(Color::S::Bold);
    cout << "size: " << size << endl;
    // display(A);
    // display(B);
    playground::timer.start();
    auto C1 = Strassen(A, B);
    playground::timer.stop();
    cout << Color().fore(Color::F::Green).style(Color::S::Bold);
    cout << "Strassen: " << playground::timer.cast_microseconds() << "us" << endl;
    // display(C1);
    playground::timer.start();
    auto C2 = force(A, B);
    playground::timer.stop();
    cout << Color().fore(Color::F::Cyan).style(Color::S::Bold);
    cout << "force: " << playground::timer.cast_microseconds() << "us" << endl;
    // display(C2);
    bool correct = true;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (C1[i][j] != C2[i][j]) {
                correct = false;
                break;
            }
        }
        if (!correct) {
            break;
        }
    }
    cout << Color().fore(Color::F::Magenta).style(Color::S::Bold);
    cout << (correct ? "correct" : "incorrect") << endl;
}
