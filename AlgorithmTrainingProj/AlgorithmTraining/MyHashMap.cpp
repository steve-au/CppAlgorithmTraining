#include <vector>

using namespace std;

//A simple implementation to demonstrate how the hash map works. The key points for hash-map are:
//1. Hash function
//2. Collision solution.

//Keep in mind:
//. Always initialise pointer. 
//. Remember to release resource.
//. 0 or null can't be passed as string.
//. Reserve a head might be a good idea, but with extra checking head==null can make logic easier.
//. Copy Constructor can be added to polish
//. Consider the testing case: duplicated has? duplicated key-value pair?
namespace MyHashMap
{
	template<typename K, typename V>
	class Node
	{
	public:
		K k;
		V v;
		Node<K, V>* next;
		Node(K k)
		{
			this->k = k;
			next = NULL;
		}
	};

	template<typename K, typename V>
	class MyHashMap
	{
	private:
		Node<K, V> *data[8];
		unsigned char hash(string k)
		{
			auto c = k[0];
			for (int i = 1; i < k.size(); i++)
			{
				c = c^k[i];
			}

			return hash(c);
		}

		unsigned char hash(int k)
		{
			return (unsigned char)(k - k / 8 * 8);

		}
	public:
		MyHashMap()
		{
			for (int i = 0; i < 8; i++)
			{
				data[i] = NULL;
			}
		}

		~MyHashMap()
		{
			for (int i = 0; i < 8; i++)
			{
				auto head = data[i];
				while (head != NULL)
				{
					auto temp = head;
					head = head->next;
					delete temp;
				}
			}
		}

		V& operator[](K key)
		{
			auto idx = hash(key);
			auto head = data[idx];
			if (head == NULL)
			{
				auto n = new Node<K, V>(key);
				data[idx] = n;
				return n->v;
			}

			Node<K, V>*tail = head;
			while (head != NULL)
			{
				if (head->k == key)
				{
					return head->v;
				}
				tail = head;
				head = head->next;
			}

			auto n = new Node<K, V>(key);
			tail->next = n;
			return n->v;
		}
	};


}