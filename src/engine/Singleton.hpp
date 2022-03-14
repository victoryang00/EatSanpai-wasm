#pragma once

template <class T> class Singleton {
public:
    Singleton(const Singleton &) = default;;
    static T *handle() {
        static T instance;
        return &instance;
    }
    Singleton &operator=(const Singleton &) = default;

protected:
    Singleton() = default;
};
