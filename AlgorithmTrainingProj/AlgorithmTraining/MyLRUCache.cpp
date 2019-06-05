#include <unordered_map>
#include <algorithm>
using namespace std;

namespace MyLRUCache
{

	template<typename K, typename V>
	class node
	{
	public:
		K key;
		V value;
		node* next;
		node* pre;
	};

	class LRUCache {
	public:
		LRUCache(int capacity) {
			this->capacity = capacity;
			head.next = &tail;
			tail.pre = &head;
			count = 0;

		}

		~LRUCache()
		{
			ReleaseResouces();
		}

		int get(int key)
		{
			auto found = map.find(key);
			if (found != map.end())
			{
				node<int, int> *pn = found->second;
				pn->pre->next = pn->next;
				pn->next->pre = pn->pre;

				pn->pre = &head;
				pn->next = head.next;
				pn->next->pre = pn;
				head.next = pn;

				return pn->value;
			}
			else
				return -1;
		}

		void put(int key, int value)
		{

			auto found = map.find(key);
			if (found != map.end())
			{
				//put back to top
				node<int, int> *pn = found->second;
				pn->pre->next = pn->next;
				pn->next->pre = pn->pre;

				pn->pre = &head;
				pn->next = head.next;
				pn->next->pre = pn;
				pn->value = value;
				head.next = pn;

			}
			else
			{
				node<int, int> *pn;
				if (count == capacity)
				{
					pn = tail.pre;
					tail.pre = pn->pre;
					pn->pre->next = &tail;
					map.erase(pn->key);
				}
				else
				{
					pn = new node<int, int>();
					count++;
				}
				pn->value = value;
				pn->key = key;

				pn->pre = &head;
				pn->next = head.next;
				pn->next->pre = pn;
				head.next = pn;
				map[key] = pn;
			}
		}

	private:
		node<int, int> head;
		node<int, int> tail;
		int capacity;
		int count;
		unordered_map<int, node<int, int>*> map;


		void ReleaseResouces()
		{
			node<int, int>* d = head.next;
			while (d != &tail)
			{
				node<int, int>* t = d;
				d = d->next;
				delete t;
			}
			head.next = &tail;
			tail.pre = &head;
		}
	};
}