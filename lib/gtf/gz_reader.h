/*
Author: Hossein Asghari
*/

#ifndef __GZ_READER_FILE_H__
#define __GZ_READER_FILE_H__

#include <string>
#include <zlib.h>

#define BUFFSIZE 10000000

using namespace std;

class gz_reader {
private:
    gzFile gzinput;
    char *zbuffer;
    int32_t buff_pos;
    int32_t buff_size;

    void read_buffer(uint32_t size);

public:
    gz_reader();
    ~gz_reader();

    int open_gz(const string &file);
    void close_gz();
    
    uint32_t getline(char *line, uint32_t size, char delim);
};

#endif