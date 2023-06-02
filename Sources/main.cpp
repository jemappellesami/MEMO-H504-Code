#include <Xoofff.h>
#include <transformations.h>
#include <iostream>
#include <fstream>

using namespace std ;

void testRollWeakness(){
XoodooExpansionRollingFunction roll_e ;

    BitString Si("This is a test value for the rolling stateThis is a test value for the rolling state");
    XoodooState initialState(Si.array()) ;

    BitString Siii = roll_e(Si, 3) ;
    XoodooState rotatedState(Siii.array()) ;

    int xSize = 4 ;
    int ySize = 3 ;
    cout << "Initial state" << endl ;
    for (int i = 0; i < ySize; i++)
    {
        for (int j = 0; j < xSize; j++)
        {
            cout << "0x" << hex << initialState[i][j] ;
            if (j < xSize - 1) cout << "," ;
        }
        cout << endl ;
    }
    cout << endl ;
    cout << "Rotated state" << endl ;
    for (int i = 0; i < ySize; i++)
    {
        for (int j = 0; j < xSize; j++)
        {
            cout << "0x" << hex << rotatedState[i][j] ;
            if (j < xSize - 1) cout << "," ;
        }
        cout << endl ;
    }
    

    // Verify the distinguisher relation

    cout << endl ;
    cout << "Verification that sheet x=0 is replaced by sheet x=1" << endl ;
    cout << "x=1 (initial) \t\t x=0 (final) " << endl ;
    // cout << "|-------------------------------|" << endl ;
    for (int y = 0; y < ySize; y++)
    {
        cout << "0x" << hex << initialState[y][1] << "\t=\t " <<  "0x" << hex << rotatedState[y][0] << endl ;
    }
    cout << endl ;
    
    cout << "Verification that sheet x=1 is replaced by sheet x=2" << endl ;
    cout << "x=1 (initial) \t\t x=0 (final) " << endl ;
    // cout << "|-------------------------------|" << endl ;
    for (int y = 0; y < ySize; y++)
    {
        cout << "0x" << hex << initialState[y][2] << "\t=\t " <<  "0x" << hex << rotatedState[y][1] << endl ;
    }
    cout << endl ;

    cout << "Verification that sheet x=2 is replaced by sheet x=3" << endl ;
    cout << "x=1 (initial) \t\t x=0 (final) " << endl ;
    // cout << "|-------------------------------|" << endl ;
    for (int y = 0; y < ySize; y++)
    {
        cout << "0x" << hex << initialState[y][3] << "\t=\t " <<  "0x" << hex << rotatedState[y][2] << endl ;
    }
    
}


void compareStates(XoodooState A, XoodooState B, std::ostream &os){
    for (int i = 0; i <= 2; i++)
    for (int j = 0; j <= 3; j++)
    {
        Lane lane(A[i][j]) ;
        for (int k = 0; k <= 2; k++)
        for (int l = 0; l <= 3; l++)
        {
            Lane possibleLane(B[k][l]) ;
            if (lane == possibleLane)
                os << "Si["<<j<<"]["<<i<<"] = Siii["<< l <<"]["<< k <<"]" << endl ;
        }
            
        
    }
            
}

void testOneRoundXoodoo(){
    XoodooExpansionRollingFunction roll_e ;
    
    BitString Si("This is a test value for the rolling stateThis is a test value for the rolling stateThis is a test value for the rolling stateThis is a test value for the rolling state");
    BitString Siii = roll_e(Si, 3) ;

    XoodooState initialState(Si.array()) ;
    XoodooState rotatedState(Siii.array()) ;
    
    Xoodoo xoodooPermutation(384, 1) ;
    xoodooPermutation(Si.array());
    xoodooPermutation(Siii.array());
    
    initialState = XoodooState(Si.array()) ;
    rotatedState = XoodooState(Siii.array()) ;
    
    compareStates(initialState, rotatedState, cout) ;
    
    cout << "1 round of Xoodoo" << endl ;
    initialState.dump(cout) ;
    rotatedState.dump(cout) ;
}




int main(int argc, char const *argv[])
{
    testOneRoundXoodoo() ;
    
    return 0;
}
