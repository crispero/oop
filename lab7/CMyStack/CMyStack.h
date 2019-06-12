#pragma once
#include <memory>

template <typename T>
class CMyStack
{
public:
	CMyStack();
	CMyStack(CMyStack<T> const& stack); // конструктор копирования
	~CMyStack();

	void Push(T const& value);
	void Pop();
	T GetTop() const;
	bool IsEmpty() const;
	void Clear();
	size_t GetSize() const;

private:
	struct Node
	{
		T value;
		std::shared_ptr<Node> next = nullptr;
	};

	size_t m_size = 0;
	std::shared_ptr<Node> m_top = nullptr;
};

template <typename T>
CMyStack<T>::CMyStack()
{
}

template <typename T>
CMyStack<T>::~CMyStack()
{
	Clear();
}

template <typename T>
void CMyStack<T>::Push(T const& value)
{
	auto newNode = std::make_shared<Node>();
	newNode->value = value;

	if (m_top != nullptr)
	{
		newNode->next = m_top;
	}

	m_top = newNode;
	m_size++;
}

template <typename T>
void CMyStack<T>::Pop()
{
	if (IsEmpty())
	{
		throw std::logic_error("Can't delete element because stack is empty");
	}

	m_top = m_top->next;
	m_size--;
}

template <typename T>
T CMyStack<T>::GetTop() const
{
	if (IsEmpty())
	{
		throw std::logic_error("Can't return top because stack is empty");
	}

	return m_top->value;
}

template <typename T>
bool CMyStack<T>::IsEmpty() const
{
	return m_size == 0;
}

template <typename T>
void CMyStack<T>::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

template <typename T>
size_t CMyStack<T>::GetSize() const
{
	return m_size;
}
