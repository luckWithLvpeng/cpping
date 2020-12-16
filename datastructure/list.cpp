
#include <iostream>

/// @brief 单向链表
class ListForward
{
private:
	struct ListNode
	{
		int value;
		ListNode* next;
		ListNode(int n) :value(n), next(nullptr) {};
	};
	int n_size;
	ListNode* head;
public:
	ListForward() :n_size(0), head(new ListNode(0)) {};
	~ListForward() {
		ListNode* willDel = head;
		while (head->next)
		{
			head = head->next;
			delete willDel;
			willDel = head;
		}
		delete willDel;
	};

	/// @brief 在头部插入节点
	/// @param n 节点的值
	void addAtHead(int n)
	{
		ListNode* node = new ListNode(n);
		node->next = head->next;
		head->next = node;
		++n_size;
	};

	/// @brief 在尾部插入节点
	/// @param n 节点的值
	void addAtTail(int n)
	{
		ListNode* node = new ListNode(n);
		ListNode* tmp = head;

		while (tmp->next)
		{
			tmp = tmp->next;
		}

		tmp->next = node;
		++n_size;
	};

	/// @brief 在指定索引处添加节点
	/// @param index 索引值
	/// @param n 节点值
	void addAtIndex(int index, int n)
	{
		if (index < 0) return;
		ListNode* tmp = head;
		int i = 0;
		while (i < index)
		{
			i++;
			if (tmp->next)
			{
				tmp = tmp->next;
			}
			else
			{
				//超出链表长度
				return;
			}
		}
		ListNode* node = new ListNode(n);
		if (tmp->next) {
			node->next = tmp->next;
		}
		tmp->next = node;
	}
	/// @brief 删除指定索引的节点
	/// @return 返回删除的值
	int deleteAtIndex(int index)
	{
		ListNode* tmp = head;
		int i = 0;
		while (i <index)
		{
			++i;
			if (tmp->next)
			{
				tmp = tmp->next;
			}
			else
			{
				// 索引值超过列表长度
				return -1;
			}
		}
		ListNode* res = tmp->next;
		if (res) {
			if (res->next) {
				tmp->next = res->next;
			}
			else
			{
				tmp->next = NULL;
			}
			int n = res->value;
			delete res;
			return n;
			
		}
		else 
		{
			return  -1;
		}
	}
	/// @brief 获取索引节点的值
	/// @param index 
	/// @return 节点值
	int get(int index)
	{
		int i = 0;
		ListNode* tmp = head->next;
		while (tmp) {
			if (i++ == index) break;
			tmp = tmp->next;
		}
		if (tmp) return tmp->value;
		return -1;
	};
	/// @brief 获取链表长度
	/// @return 
	int size()
	{
		return n_size;
	};

	/// @brief 循环打印
	void forEachPrint() 
	{
		ListNode* tmp = head;
		while (tmp->next)
		{
			std::cout << tmp->next->value << std::endl;
			tmp = tmp->next;
		}
	}
};


int main()
{
	ListForward li;
	li.addAtHead(1);
	li.addAtIndex(0, 2);
	li.addAtIndex(2, 3);
	li.addAtIndex(3, 4);
	li.forEachPrint();
	return 0;
}