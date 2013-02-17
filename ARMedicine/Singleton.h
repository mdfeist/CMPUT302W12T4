#pragma once

template <class T>
class Singleton
{
public:
    static T* getInstance(void) 
	{
		if(!m_pInstance) m_pInstance = new T;
		assert(m_pInstance !=NULL);
		return m_pInstance;
	}

protected:
    Singleton<T>(void) {};
	~Singleton<T>(void) {};
private:
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
    static T* m_pInstance;
};

template <class T>
T* Singleton<T>::m_pInstance = 0;

