//
//  main.cpp
//  ExampleProject
//
//  Created by eric.tarr on 1/8/26.
//
//

#include <iostream>


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
    }
    
    // insert code here...
    std::cout << "c: " << c << std::endl;
    //c; // c = c + 1;
    //c += 5; // c = c + 5;
    std::cout << "++c: " << ++c << std::endl;
    std::cout << "c: " << c << std::endl;
    return 0;
}
