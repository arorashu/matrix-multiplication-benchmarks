#include<iostream>
#include<random>
// #include<vector>
// #include<algorithm>
#include <time.h>
#define STRASSEN_THRESHOLD 20
#include "sys/types.h"
#include "sys/sysinfo.h"

struct sysinfo memInfo;



using namespace std;

vector<vector<int>> createRandomMatrix(int size);
void printMatrix(vector<vector<int>> &matrix);
// all these return a new matrix
vector<vector<int>> multiplySquareMatricesNaive(vector<vector<int>> const &matrix1, vector<vector<int>> const &matrix2);
vector<vector<int>> multiplySquareMatricesStrassen(vector<vector<int>> const &matrix1, vector<vector<int>> const &matrix2);
vector<vector<int>> addSquareMatrices(vector<vector<int>> const &matrix1, vector<vector<int>> const &matrix2, bool isNegativeMatrix2=false);
bool checkMatrixEqual(vector<vector<int>> const &matrix1, vector<vector<int>> const &matrix2);


int main() {

    double timeDifference;
    clock_t startt, endt;

    int size;
    cout<<"Enter mat size: ";
    cin>>size;

    vector<vector<int>> matrix1 = createRandomMatrix(size);
    vector<vector<int>> matrix2 = createRandomMatrix(size);
    // cout<<"matrix1\n";
    // printMatrix(matrix1);
    // cout<<"matrix2\n";
    // printMatrix(matrix2);

    startt = clock();
    vector<vector<int>> matrix3 = multiplySquareMatricesNaive(matrix1, matrix2);
    endt = clock();
    timeDifference = (double)(endt-startt)/CLOCKS_PER_SEC;
    cout<<"Naive multiplied result matrix3\n";
    // printMatrix(matrix3);
    printf("NAIVE FINISHED --- TOTAL CPU TIME %f SECS \n",(float)timeDifference);

    startt = clock();
    vector<vector<int>> matrix4 = multiplySquareMatricesStrassen(matrix1, matrix2);
    endt = clock();
    timeDifference = (double)(endt-startt)/CLOCKS_PER_SEC;
    cout<<"Strassen multiplied result matrix4\n";
    // printMatrix(matrix4);
    printf("STRASSEN FINISHED --- TOTAL CPU TIME %f SECS \n",(float)timeDifference);


    // sysinfo (&memInfo);
    // long long totalVirtualMem = memInfo.totalram;
    // //Add other values in next statement to avoid int overflow on right hand side...
    // totalVirtualMem += memInfo.totalswap;
    // totalVirtualMem *= memInfo.mem_unit;
    // printf("total virtual memory %ld \n",totalVirtualMem);

    // long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
    // //Add other values in next statement to avoid int overflow on right hand side...
    // virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
    // virtualMemUsed *= memInfo.mem_unit;
    // printf("virtual memory used:  %ld \n",virtualMemUsed);


    checkMatrixEqual(matrix3, matrix4);
    return 0;
}
/**
 * create a square matrix filled with random integers in range (0, 100)
 */
vector<vector<int>> createRandomMatrix(int size) {

    vector<vector<int>> matrix;
    // if(size > 100) {
    //     cout<<"Size greater than 100 not supported\n";
    //     return matrix;
    // }

    matrix.resize(size);

    std::random_device rseed;
    std::mt19937 rgen(rseed()); // mersenne_twister
    std::uniform_int_distribution<int> idist(0,10); // [0,100]

    // std::cout << idist(rgen) << std::endl;

    for(int i=0; i<size; i++) {
        matrix[i].resize(size);
        for(int j=0; j<size; j++) {
            matrix[i][j] = idist(rgen);
        }
    }

    return matrix;
}

/**
 * Print a matrix to console out
 */ 
void printMatrix(vector<vector<int>> &matrix) {
    // int numRows = matrix.size();

    for (auto &&rowIterator : matrix)
    {
        for (auto &&colIterator : rowIterator) 
        {
            cout<<colIterator<<" ";
        }
        cout<<endl;
    }
}

/**
 * Assume multiply square matrices of same size
 */ 
vector<vector<int>> multiplySquareMatricesNaive(vector<vector<int>> const &matrix1, vector<vector<int>> const &matrix2) {
    
    // verify if matrices can be multiplied

    /**
     * if can be multiplied
     * let c = a * b
     * c[i][j] = sum (k) ( a[i][k] * b[k][j] )
     */ 

    int matrixSize = matrix1.size();
    vector<vector<int>> resultMatrix(matrixSize);

    for (int i = 0; i < matrixSize; i++)
    {
        resultMatrix[i].resize(matrixSize);
        for (int j = 0; j < matrixSize; j++)
        {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < matrixSize; k++)
            {
                resultMatrix[i][j] += matrix1[i][k]*matrix2[k][j];
            }   
        }
        
    }

    // printf("I multiplied size: %d \n", matrixSize);
    
    return resultMatrix;
}



vector<vector<int>> multiplySquareMatricesStrassen(vector<vector<int>> const &matrix1, vector<vector<int>> const &matrix2) {
    // verify if matrices can be multiplied
    // assume even size square matrices
    /**
     * if can be multiplied
     * let c = a * b
     * partition matrix1 ->
     * a11 a12
     * a21 a22
     * partition matrix2 ->
     * b11 b12
     * b21 b22
     */

    int matrixSize = matrix1.size();
    
    if(matrixSize < STRASSEN_THRESHOLD) {
        return multiplySquareMatricesNaive(matrix1, matrix2);
    }

    // printf("matrix size: %d \n", matrixSize);
    
    int partitionSize = matrixSize/2;
    vector<vector<int>> a11(partitionSize), a12(partitionSize), a21(partitionSize), a22(partitionSize);
    vector<vector<int>> b11(partitionSize), b12(partitionSize), b21(partitionSize), b22(partitionSize);


    for (int rowId = 0; rowId < partitionSize; rowId++)
    {
        a11[rowId].assign(matrix1[rowId].begin(), matrix1[rowId].begin()+partitionSize);
        a12[rowId].assign(matrix1[rowId].begin()+partitionSize, matrix1[rowId].end());

        a21[rowId].assign(matrix1[rowId+partitionSize].begin(), matrix1[rowId+partitionSize].begin()+partitionSize);
        a22[rowId].assign(matrix1[rowId+partitionSize].begin()+partitionSize, matrix1[rowId+partitionSize].end());

        b11[rowId].assign(matrix2[rowId].begin(), matrix2[rowId].begin()+partitionSize);
        b12[rowId].assign(matrix2[rowId].begin()+partitionSize, matrix2[rowId].end());

        b21[rowId].assign(matrix2[rowId+partitionSize].begin(), matrix2[rowId+partitionSize].begin()+partitionSize);
        b22[rowId].assign(matrix2[rowId+partitionSize].begin()+partitionSize, matrix2[rowId+partitionSize].end());
    }

    // cout<<"broken matrix1 \n";
    // printMatrix(a11);
    // cout<<endl;
    // printMatrix(a12);
    // cout<<endl;
    // printMatrix(a21);
    // cout<<endl;
    // printMatrix(a22);
    // cout<<endl;

    // create parts of final matrix
    vector<vector<int>> m1(partitionSize), m2(partitionSize),
        m3(partitionSize), m4(partitionSize), m5(partitionSize),
        m6(partitionSize), m7(partitionSize);

    m1 = multiplySquareMatricesStrassen(addSquareMatrices(a11, a22), addSquareMatrices(b11, b22));
    m2 = multiplySquareMatricesStrassen(addSquareMatrices(a21, a22), b11);
    m3 = multiplySquareMatricesStrassen (a11, addSquareMatrices(b12, b22, true));
    m4 = multiplySquareMatricesStrassen(a22, addSquareMatrices(b21, b11, true));
    m5 = multiplySquareMatricesStrassen(addSquareMatrices(a11, a12), b22);
    m6 = multiplySquareMatricesStrassen(addSquareMatrices(a21, a11, true), addSquareMatrices(b11, b12));
    m7 = multiplySquareMatricesStrassen(addSquareMatrices(a12, a22, true), addSquareMatrices(b21, b22));
    // printf("matrix m7\n");
    // printMatrix(m7);

    // printf("components made for size %d\n", matrixSize);

    vector<vector<int>> c11(partitionSize), c12(partitionSize),
        c21(partitionSize), c22(partitionSize);

    
    
    // printf("matrix m3: size: %lu\n", m3.size());
    // printMatrix(m3);
    // printf("matrix m5: size: %lu\n", m5.size());
    // printMatrix(m5);

    c11 = addSquareMatrices(m1, addSquareMatrices(m4, addSquareMatrices(m7, m5, true)));
    c12 = addSquareMatrices(m3, m5);
    c21 = addSquareMatrices(m2, m4);
    c22 = addSquareMatrices(m1, addSquareMatrices(m3, addSquareMatrices(m6, m2, true)));

    vector<vector<int>> resultMatrix(matrixSize);

    // put together c11, c12, c21, c22 into result matrix

    // dont know why seg fault happening also
    // too big an input?
    // printf("reconstructing result size: %d \n", matrixSize);
    for (int rowId = 0; rowId < partitionSize; rowId++)
    {
        resultMatrix[rowId].resize(matrixSize);
        resultMatrix[rowId+partitionSize].resize(matrixSize);

        for(int colId=0; colId<partitionSize; colId++) {
            resultMatrix[rowId][colId]                             = c11[rowId][colId];
            resultMatrix[rowId][colId+partitionSize]               = c12[rowId][colId];
            resultMatrix[rowId+partitionSize][colId]               = c21[rowId][colId];
            resultMatrix[rowId+partitionSize][colId+partitionSize] = c22[rowId][colId];
        }
    }

    return resultMatrix;
}

vector<vector<int>> addSquareMatrices(vector<vector<int>> const &matrix1, vector<vector<int>> const &matrix2, bool isNegativeMatrix2) {
    // verify if matrices can be multiplied

    /**
     * if can be multiplied
     */ 

    if(matrix1.size() != matrix2.size()){
        cout<<"size mismatch \n";
    }

    int matrixSize = matrix1.size();
    vector<vector<int>> resultMatrix(matrixSize);

    for (int i = 0; i < matrixSize; i++)
    {
        resultMatrix[i].resize(matrixSize);
        for (int j = 0; j < matrixSize; j++)
        {
            if(isNegativeMatrix2) {
                resultMatrix[i][j] = matrix1[i][j] - matrix2[i][j];    
            }
            else {
                resultMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        
    }    
    return resultMatrix;
}

bool checkMatrixEqual(vector<vector<int>> const &matrix1, vector<vector<int>> const &matrix2) {
    // verify if matrices can be multiplied

    /**
     * if can be multiplied
     */ 

    if(matrix1.size() != matrix2.size()){
        cout<<"size mismatch \n";
    }

    int matrixSize = matrix1.size();
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if(matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
        
    }

    cout<<"matrices are equal\n";
    return true;
}