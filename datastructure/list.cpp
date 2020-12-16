
#include <iostream>

/// @brief ��������
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

	/// @brief ��ͷ������ڵ�
	/// @param n �ڵ��ֵ
	void addAtHead(int n)
	{
		ListNode* node = new ListNode(n);
		node->next = head->next;
		head->next = node;
		++n_size;
	};

	/// @brief ��β������ڵ�
	/// @param n �ڵ��ֵ
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

	/// @brief ��ָ����������ӽڵ�
	/// @param index ����ֵ
	/// @param n �ڵ�ֵ
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
				//����������
				return;
			}
		}
		ListNode* node = new ListNode(n);
		if (tmp->next) {
			node->next = tmp->next;
		}
		tmp->next = node;
	}
	/// @brief ɾ��ָ�������Ľڵ�
	/// @return ����ɾ����ֵ
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
				// ����ֵ�����б���
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
	/// @brief ��ȡ�����ڵ��ֵ
	/// @param index 
	/// @return �ڵ�ֵ
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
	/// @brief ��ȡ������
	/// @return 
	int size()
	{
		return n_size;
	};

	/// @brief ѭ����ӡ
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