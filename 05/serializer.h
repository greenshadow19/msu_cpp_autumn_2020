//
// Created by kirill on 08.11.2020.
//
#ifndef MSU_CPP_AUTUMN_2020_SERIALIZER_H
#define MSU_CPP_AUTUMN_2020_SERIALIZER_H

#include <sstream>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
private:
    static constexpr char Separator = ' ';

    std::ostream &outStream;

    void handler(bool expression);

    void handler(uint64_t number);

    template<class T, class... ArgsT>
    Error process(T &&firstArg, ArgsT &&... argsT) {
        handler(firstArg);
        return process(std::forward<ArgsT>(argsT)...);
    }

    template<class T>
    Error process(T &&lastArg) {
        handler(lastArg);
        return Error::NoError;
    }

public:
    explicit Serializer(std::ostream &out)
            : outStream(out) {}

    template<class T>
    Error save(T &object) {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT... args) {
        return process(std::forward<ArgsT>(args)...);
    }
};

class Deserializer {
private:
    static constexpr char Separator = ' ';

    std::istream &inStream;

    Error handler(bool &expression);

    Error handler(uint64_t &number);

    template<class T, class ... ArgsT>
    Error process(T &&firstArg, ArgsT &&... argsT) {
        if (handler(firstArg) == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return process(std::forward<ArgsT>(argsT)...);
    }

    template<class T>
    Error process(T &&lastArg) {
        return handler(lastArg);
    }

public:
    explicit Deserializer(std::istream &in) : inStream(in) {}

    template<class T>
    Error load(T &object) {
        return object.deserialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT &&... args) {
        return process(std::forward<ArgsT>(args)...);
    }
};

#endif //MSU_CPP_AUTUMN_2020_SERIALIZER_H
