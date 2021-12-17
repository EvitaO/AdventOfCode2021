#include <iostream>
#include <stdio.h>

int         main(int argc,char **argv){
    FILE*    f;
    f= fopen(argv[1], "r");    
    int x0,x1,y0,y1;
    fscanf(f, "target area: x=%i..%i, y=%i..%i", &x0,&x1,&y0,&y1);
    std::cout << y0 * (y0+1)/2 << std::endl;
}