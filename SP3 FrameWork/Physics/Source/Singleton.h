#pragma once

template<typename T>
class Singleton
{
public:
	static T * getInstance()
	{
		if (!_instance)
			_instance = new T();  // <-- Create instance pointing to address of Type T
		                          //  new T()  is  calling the constructor of derived class

		return _instance;
	}


protected:
	Singleton() {};
	virtual	~Singleton()
	{
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	static T * _instance;
};

template <typename T>
T* Singleton<T> ::_instance = nullptr;