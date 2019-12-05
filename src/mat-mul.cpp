#include<iostream>
#include<random>
// #include<vector>
// #include<algorithm>

using namespace std;

vector<vector<int>> createRandomMatrix(int size);
void printMatrix(vector<vector<int>> &matrix);

int main() {
    int size;
    cout<<"Enter mat size: ";
    cin>>size;

    vector<vector<int>> matrix = createRandomMatrix(size);
    printMatrix(matrix);

    return 0;
}
/**
 * create a square matrix filled with random integers in range (0, 100)
 */
vector<vector<int>> createRandomMatrix(int size) {

    vector<vector<int>> matrix;
    if(size > 100) {
        cout<<"Size greater than 100 not supported\n";
        return matrix;
    }

    matrix.resize(size);

    std::random_device rseed;
    std::mt19937 rgen(rseed()); // mersenne_twister
    std::uniform_int_distribution<int> idist(0,100); // [0,100]

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

    // for (size_t i = 0; i < matrix.size(); i++)
    // {
    //     for (size_t j = 0; j < matrix[i].size(); j++)
    //     {
    //         cout<<matrix[i][j]<<' ';
    //     }
    //     cout<<endl;
    // }
    
    
}