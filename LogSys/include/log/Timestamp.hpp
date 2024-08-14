#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP
#include <ctime>
#include <string>

namespace LOG {
    class Timestamp {
    private:
        std::int64_t microsec_;

    public:
        Timestamp();

        Timestamp(std::int64_t m);

        ~Timestamp();

    public:
        void swap(Timestamp& other);

        std::string toString() const;

        std::string toFormattedString(bool showmicro = true) const;

        std::string toFormattedFile() const;

        bool valid() const;

        std::int64_t getMicro() const;

        std::int64_t getSecond() const;

        const Timestamp& now();

    public:
        static Timestamp Now(); //HuoQuShiJianChuo

        static Timestamp Invalid();

        static const int KMicroPerSeconds = 1000 * 1000;


    };

    inline std::int64_t timeMicroc(const Timestamp& a, const Timestamp& b) {
        return a.getMicro() - b.getMicro();
    }

    inline std::int64_t timeSeconds(const Timestamp& a, const Timestamp& b) {
        return a.getSecond() - b.getSecond();
    }


}

#endif