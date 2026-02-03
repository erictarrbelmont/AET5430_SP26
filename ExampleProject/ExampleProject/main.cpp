//
//  main.cpp
//  ExampleProject
//
//  Created by eric.tarr on 1/8/26.
//
//

#include <iostream>
#include <vector>

// FUNCTIONS
// Declare here for "global" scope
// Just do the function signature
float myAddFunction(float a , float b);

void myOtherFunction(int i){
    
    bool bypassed = true;
    
    if (bypassed)
        return;
    
    for (int c = 0 ; c < 100 ; ++c){
        int result = i + c;
    }
    
}


int main(int argc, const char * argv[]) {
    
    // MATLAB
    //x = 100;
    //y = 1000;
    
    // C++
    // Declare
    //int x;
    // Define
    //x = 10;
    
    //int y = 100;
    
    float x = 10; //.0f;
    float y = 2;
    
    auto a = powf(x,y);
    
    double z = 10.0;
    
    std::string u = "This is my text";
    
    // Primitive array
    int array[3]; // declare
    
    int stereoSig[32][2];
    
    stereoSig [12][1] = 10;
    
    std::vector<int> vec {5,4,3};
    vec[0] = 8;
    vec[1] = 9;
    
    int szVec = vec.size();
    
    std::vector<std::vector<int>> vec2D (2,std::vector<int> (3));
    
    
    
    
    int r = vec.at(0) + vec.at(1);
    
    
    int myArray[3] = {50,51,52};
    
    
    
    int m[] = {55,56};
    
    int w = myArray[5]; // watch out for this
    
    // MATLAB LOOP
    // for n = 1:N
    //      CODE
    // end
    int N = 3; // size of "myArray"
    int c;
    for (int n = 0; n < N; ++n ){
        c = myArray[n];
        for (int w = 0; w < 5; ++w){
            
        }
    }
    
    // Conditional Statements
    if (N > 5){
        std::cout << "N: " << N << std::endl;
    }
    else if (N < 5){
        
    }
    else {
        
    }
    
    
    // Calling the function
    auto q = myAddFunction(x, y);
    
    myOtherFunction(5);
    
    // insert code here...
    std::cout << "c: " << c << std::endl;
    //c; // c = c + 1;
    //c += 5; // c = c + 5;
    std::cout << "++c: " << ++c << std::endl;
    std::cout << "c: " << c << std::endl;
    return 0;
}


float myAddFunction(float a, float b){
    //float c = a + b;
    
    return a+b;
}
