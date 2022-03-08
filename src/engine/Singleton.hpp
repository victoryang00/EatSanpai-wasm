#pragma once

template <class T> class Singleton {
public:
    Singleton(const Singleton &) = delete;
    static T *handle() {
        static T instance;
        return &instance;
    }
    Singleton &operator=(const Singleton &) = delete;

protected:
    Singleton() = default;
};
