/*
Author: Hossein Asghari
*/

#include <string>
#include <zlib.h>
#include <stdexcept>
#include "gz_reader.h"

gz_reader::gz_reader()
{
    gzinput = Z_NULL;
    zbuffer = (char *) malloc(BUFFSIZE);

    buff_pos = 0;
    buff_size = 0;
}

gz_reader::~gz_reader() 
{
    close_gz();
    free(zbuffer);
}

int gz_reader::open_gz(const string &file) 
{
    gzinput = gzopen(file.c_str(), "r");
    
    if (gzinput == Z_NULL) {
        printf("Error: Could not open gzip file %s\n", file.c_str());
        return 1;
    }

    return 0;
}

void gz_reader::close_gz() 
{
    if (gzinput != Z_NULL) {
        gzclose(gzinput);
    }
    gzinput = Z_NULL;
}

void gz_reader::read_buffer(uint32_t size) {
    buff_size = gzread(gzinput, zbuffer, size);
    buff_pos = 0;

    if (buff_size == 0 and gzeof(gzinput) == 0) {
        buff_size = -1;
    }
    if (buff_size < 0) {
        int err;
        fprintf(stderr, "gzread error: %s\n", gzerror(gzinput, &err));
        throw std::runtime_error("Runtime Error: error in reading gzip file above!");
    }
}

uint32_t gz_reader::getline(char *line, uint32_t size, char delim) {
    char cur;

    uint32_t i = 0;
    while (true) {
        if (buff_pos >= buff_size) {
            try {
                read_buffer(size);
                if (buff_size == 0)
                    return 0;
            } catch(const std::runtime_error& rte) {
                fprintf(stderr, "%s\n", rte.what());
                return 0; 
            }
        }

        cur = zbuffer[buff_pos++];
        if (cur == delim) {
            line[i] = '\0';
            return i;
        }

        line[i++] = cur;
    }
}
