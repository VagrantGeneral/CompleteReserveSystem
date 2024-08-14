
#include "AppendFile.hpp"
#include <assert.h>
#include <string.h>
#include <error.h>

namespace LOG {
    size_t AppendFile::write(const char* info, const size_t len) {
        return fwrite_unlocked(info, sizeof(char), len, fp_);
    }

    AppendFile::AppendFile(const std::string& filename) 
        : fp_{nullptr}
        , buffer_{new char[FILEBUFFSIZE]}
        , writenBytes_{0} {
        //create
        fp_ = fopen(filename.c_str(), "a");//"w"
        assert(fp_ != nullptr);
        
        setbuffer(fp_, buffer_.get(), FILEBUFFSIZE);    //edit MoRen buffer
        
    }

    AppendFile::~AppendFile() {
        fclose(fp_);
        fp_ = nullptr;
        buffer_.reset();
    }

    void AppendFile::append(const std::string& info) {
        append(info.c_str(), info.size());
    }

    void AppendFile::append(const char* info, const size_t len) {
        size_t n = write(info, len);
        size_t remain = len - n;
        while (remain > 0) {
            size_t x = write(info + n, remain);
            if (x == 0) {
                //write err
                int err = ferror(fp_);
                if (err) {
                    fprintf(stderr, "appendFile::append() failed %s\n", strerror(err));
                }
                break;
            }
            n += x;
            remain = len - n;
        }
        writenBytes_ += n;
    }

    void AppendFile::flush() {
        fflush(fp_);
    }

    //return n for write
    size_t AppendFile::writenBytes() const {
        return this->writenBytes_;
    }




}