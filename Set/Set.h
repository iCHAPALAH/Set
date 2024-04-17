#pragma once
#include <iostream>

template <class key>
class Set
{
	class Node
	{
	public:
		key* info;
		Node* next;
		Node()
		{
			info = nullptr;
			next = nullptr;
		}
		Node(key info, Node* next) : info(new key(info)), next(next) {}
		~Node()
		{
			next = nullptr;
			delete info;
		}
	};
	Node* head;
	Node* pos(const key& x) const
	{
		Node* i = head;
		while (i->next && *(i->next->info) < x)
			i = i->next;
		return i;
	}
public:
	Set()
	{
		head = new Node;
	}
	Set(std::istream& stream)
	{
		head = new Node;
		key tmp{};
		while (stream >> tmp)
			insert(tmp);
	}
	~Set()
	{
		while (head)
		{
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
		head = nullptr;
	}
	bool insert(const key& x)
	{
		bool result = true;
		Node* i = pos(x);
		if (i->next && *(i->next->info) == x)
			result = false;
		else
			i->next = new Node(x, i->next);
		return result;
	}
	bool find(const key& x) const
	{
		bool result = false;
		Node* i = pos(x);
		if (i->next && *(i->next->info) == x)
			result = true;
		return result;
	}
	bool erase(const key& x)
	{
		bool result = false;
		Node* i = pos(x);
		if (i->next && *(i->next->info) == x)
		{
			result = true;
			Node* tmp = i->next;
			i->next = i->next->next;
			delete tmp;
		}
		return result;
	}
	friend Set<key> operator+(const Set<key>& lhs, const Set<key>& rhs)
	{
		Set<key> result;
		Node* i = lhs.head->next;
		while (i)
		{
			result.insert(*(i->info));
			i = i->next;
		}
		i = rhs.head->next;
		while (i)
		{
			result.insert(*(i->info));
			i = i->next;
		}
		return result;
	}
	friend Set<key> operator*(const Set<key>& lhs, const Set<key>& rhs)
	{
		Set<key> result;
		Node* i = lhs.head->next;
		while (i)
		{
			Node* tmp = rhs.pos(*(i->info));
			if (tmp->next && *(i->info) == *(tmp->next->info))
				result.insert(*(i->info));
			i = i->next;
		}
		return result;
	}
	friend Set<key> operator-(const Set<key>& lhs, const Set<key>& rhs)
	{
		Set<key> result;
		Node* i = lhs.head->next;
		while (i)
		{
			Node* tmp = rhs.pos(*(i->info));
			if (!tmp->next || (tmp->next && !(*(i->info) == *(tmp->next->info))))
				result.insert(*(i->info));
			i = i->next;
		}
		return result;
	}
	friend std::ostream& operator<<(std::ostream& stream, const Set<key>& x)
	{
		Node* i = x.head->next;
		while (i)
		{
			stream << *(i->info) << (i->next ? " " : "");
			i = i->next;
		}
		return stream;
	}
};