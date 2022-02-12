#pragma once

template<class T>
class Singleton {
public:
	static T* handle() {
		static T instance;
		return &instance;
	}
protected:
	Singleton() {}
private:
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
};
