// sort algorithm example
#include <iostream>     // std::cout
#include <fstream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <random>

const int length = 8192;

struct Point {
    uintmax_t pos;
    size_t len;
};


std::vector<Point> collect_points(FILE * infile, size_t * max_line_len){
    char * buffer = new char [length];

    std::vector<Point> points;
    size_t read,i = 0;
    uintmax_t pos = 0;
    Point * p = new Point{0,0};
    uintmax_t last_from = 0;

    while(1){
        read = fread(buffer,1,length,infile);
        for(i =0; i< read; i ++){
            if (buffer[i] == '\n'){

                p->len = (pos + i) - last_from;
                if( p->len>*max_line_len){
                    *max_line_len = p->len;
                }
                points.push_back(*p);
                last_from = (pos + i + 1);
                p = new Point{last_from, 0 };
            }
        }

        pos += read;
        if(read < length){
            break;
        }
    }
    delete[] buffer;
    return points;
}


void print_lines(FILE * infile, size_t max_line_len, std::vector<Point> * v){
     auto buffer = new char[max_line_len];

     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

     std::shuffle (v->begin(), v->end(),std::default_random_engine(seed));

     for(std::vector<Point>::iterator it = v->begin(); it != v->end(); ++it) {
        fseek(infile,it->pos,SEEK_SET);
        fread(buffer,it->len,1,infile);
        buffer[it->len] = '\n';
        std::cout.write(buffer, it->len + 1);
     }

}


int main (int argc, char *argv[]) {
    if(argc > 1){
        FILE * infile = fopen(argv[1],"r");
        if(infile != NULL ){
            size_t max_line_len = 0;
            auto v = collect_points(infile,&max_line_len);
            print_lines(infile, max_line_len, &v);
            fclose(infile);
            return 0;
        } else {
            printf("Error opening input file");
            return 1;
        }
    } else {
        printf("Usage: \nqshuf [input file] \nor\nqshuf [input file] > [output file] \n");
        return 1; 
    }
}
