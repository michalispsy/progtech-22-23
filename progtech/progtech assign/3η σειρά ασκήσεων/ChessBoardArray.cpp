#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

#define throw(out_of_range);

class ChessBoardArray {
protected:
    class Row {
    public:

        Row(ChessBoardArray &a, int i) : Board(a), row(i) {}
        
        int & operator [] (int i) const {return Board.select(row,i);}
    
    private:
        ChessBoardArray &Board;
        int row;
    };

    class ConstRow {
    public:
        ConstRow(const ChessBoardArray &a, int i) : Board(a), row(i) {}

        int operator [] (int i) const {return Board.select(row,i);}

    private:
        const ChessBoardArray &Board;
        int row;
    };

public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0);
    ChessBoardArray(const ChessBoardArray &a);
    ~ChessBoardArray() {delete [] board;} 
                
    ChessBoardArray & operator = (const ChessBoardArray &a);

    int & select(int i, int j);
    int select(int i, int j) const;

    const Row operator [] (int i) 
    {
        return Row(*this, i);
    }

    const ConstRow operator [] (int i) const
    {
        return ConstRow(*this, i);
    }
            
    friend ostream & operator << (ostream &out, const ChessBoardArray &a)
    {
        for(int i = 0; i < a.dimensions; i++){
            for(int j = 0 ; j < a.dimensions; j++){
                cout << setw(4);
                if((i + j)%2 == 1) cout << 0;
                else cout << a[i+a.base_num][j+a.base_num];
            }
            cout << endl;
        }
        return out;
    }  

private:
    unsigned dimensions;
    unsigned base_num;
    unsigned usefll_sze;
    int *board = nullptr;
    unsigned int loc(int i, int j) const throw(out_of_range);
};

ChessBoardArray::ChessBoardArray(unsigned size, unsigned base) : dimensions(size), base_num(base)
{
    usefll_sze = dimensions*dimensions/2 + dimensions*dimensions%2;
    board = new int [usefll_sze];
    for(int i=0; i < usefll_sze; i++)
    {
        board[i] = 0;
    }
}

ChessBoardArray::ChessBoardArray(const ChessBoardArray &a) : dimensions(a.dimensions), base_num(a.base_num) 
{
    usefll_sze = dimensions*dimensions/2 + dimensions*dimensions%2;
    board = new int [usefll_sze];
    for(int i = 0; i < usefll_sze; i++)
    {
        board[i] = a.board[i];
    }
}

ChessBoardArray & ChessBoardArray::operator = (const ChessBoardArray &a)
{
    delete [] board; //xreiazetai []
    dimensions = a.dimensions;
    base_num = a.base_num;
    usefll_sze = a.usefll_sze;
    board = new int [usefll_sze];
    for(int i = 0; i < usefll_sze; i++)
    {
        board[i] = a.board[i];
    } 
    return *this; //simantiko
}

int & ChessBoardArray::select(int i, int j) 
{
    return board[loc(i,j)];
}

int ChessBoardArray::select(int i, int j) const 
{
    return board[loc(i,j)];
}

unsigned int ChessBoardArray::loc(int i, int j) const throw(out_of_range)
{
    int di = i - base_num;
    int dj = j - base_num;
    if((di < 0 || di >= dimensions) || (dj < 0 || dj >= dimensions)) {throw out_of_range("");}
    if((di + dj) % 2 == 1) {throw out_of_range("");}

    return (di*dimensions + dj)/2;
}

/*
int main() 
{
    ChessBoardArray a(4, 1);
    a[5][3] = 14;
    a[3][1] = 42;
    a[4][4] = 17;
    //try { a[2][1] = 7; }
    //catch(out_of_range &e) { cout << "a[2][1] is black"<< endl; }
    cout << a;
}*/