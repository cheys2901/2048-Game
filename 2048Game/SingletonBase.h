#pragma once

template<class T>
class SingletonBase
{
protected:
	static T* _single;
public:
	SingletonBase() {}
	virtual ~SingletonBase() {}

	inline static T* getSingleton()
	{
		if (!_single) _single = new T;
		return _single;
	}
	inline void releaseSingleton()
	{
		if (_single)
		{
			delete _single;
			_single = nullptr;
		}
	}

};

template<class T>
T* SingletonBase<T>::_single = 0;