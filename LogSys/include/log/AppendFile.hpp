#ifndef APPENDFILE_HPP
#define APPENDFILE_HPP
#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>

namespace LOG {
    class AppendFile {
    private:
        static const size_t FILEBUFFSIZE = 64 * 1024;   //64K

    private:
        FILE* fp_;

        std::unique_ptr<char[]> buffer_;

        size_t writenBytes_;

    private:
        size_t write(const char* info, const size_t len);

    public:
        AppendFile(const std::string& filename);

        ~AppendFile();

        void append(const std::string& info);

        void append(const char* info, const size_t len);

        void flush();

        size_t writenBytes() const;


    };


}





#endif