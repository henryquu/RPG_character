#include <time.h>
#include <fstream>
#include "utils.h"


void remove_from_file(string name, string file_path){
    std::ifstream reading(file_path);
    std::ofstream writing_tmp(PATH_TMP);

    string line;

    while(reading.good()){
        std::getline(reading, line);

        if (line.length() < 1)
            break;

        if (name.compare(line.substr(0, line.find(" "))) == 0)
            continue;

        writing_tmp << line << '\n';
    }

    reading.close();
    writing_tmp.close();

    std::ofstream writing(file_path);
    std::ifstream reading_tmp(PATH_TMP);

    while(reading_tmp.good()){
        std::getline(reading_tmp, line);
        
        if (line.length() < 1)
            break;

        writing << line << '\n';
    }

    writing.close();
    reading_tmp.close();
    remove(PATH_TMP);
}
