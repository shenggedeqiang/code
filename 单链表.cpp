//////////////////////////////////////////////////////////////////
///                                                            ///
///                          单链表                             ///
///                                                            ///
//////////////////////////////////////////////////////////////////
//reverse the linked list II
class Solution{
public:
	ListNode *reverseBetween(ListNode *head,int m,int n){
		ListNode dummpy(-1);
		dummpy.next=head;

		ListNode *prev=&dummpy;
		for(int i=0;i<m-1;++i)    //先让指针向前遍历m-1个距离
			prev=prev->next;
		ListNode *const head2=prev;
		prev=head2->next;
		ListNode *cur=prev->next;
		for(int i=m;i<n;++i){     //逆序的操作
			prev->next=cur->next;
			cur->next=head2->next;
			head2->next=cur;
			cur=prev->next;
		}
		return dummpy.next;
	}
}
//partition list
class Solution{
public:
	ListNode* partition(ListNode *head,int x){
		ListNode *left_dummy(-1);
		ListNode *right_dummy(-1);

		auto left_cur=&left_dummy;
		auto right_cur=&right_dummy;

		for(ListNode *cur=head;cur;cur=cur->next){
			if(cur->val<x){
				left_cur->next=cur;
				left_cur=cur;
			}else{
				right_cur->next=cur;
				right_cur=cur;
			}
		}
		left_cur->next=right_dummy.next;
		right_cur->next=nullptr;
		return left_dummy.next;
	}
}
//rotate list
class Solution{
public:
	ListNode* rotate(ListNode*head,in k){
		if(head==nullptr||k==0) return head;
		int len=1;
		ListNode* p=head;
		while(p->next){//求链表长度
			len++;
			p=p->next;
		}
		k=len-k%len;

		p->next=head;  //首尾相连
		for(int step=0;step<k;step++){
			p=p->next; //接着往后跑
		}  
		head=p->next;  //新的首节点
		p->next=nullptr; //断开环
		return head;
	}
}
///////////////////求链表长度
while(p->next){ ///
	len++;      ///
	p=p->next;  ///
}               ///
///////////////////
//Remove Nth Node From End of List 移除链表倒数第N个节点
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head->next) return NULL;
        ListNode *pre = head, *cur = head;
        for (int i = 0; i < n; ++i) cur = cur->next;
        if (!cur) return head->next;
        while (cur->next) {
            cur = cur->next;
            pre = pre->next;
        }
        pre->next = pre->next->next;
        return head;
    }
};

//swap Nodes in pairs
class Solution{
public:
	ListNode* swapNode(ListNode* head){
		if(head==nullptr||head->next==nullptr) return head;
		ListNode dummy(-1);
		dummy.next=head;

		for(ListNode *prev=&dummy,*cur=prev->next,*next=cur->next;
			next;
			pre)
	}
}



//linked list cycle 判断链表是否有环
class Soultion{
public:
	bool hascircle(ListNode *head){
		ListNode *slow=head;
		ListNode *fast=head;
		while(fast&&fast->next){
			slow=slow->next;
			fast=fast->nums->next;
			if (slow==fast) return true;
		}
		return false;
	}
}
//linked list cycle II 一个有环的链表，返回该环的入口节点
class Solution{
public:
	ListNode *returncyclenode(ListNode *head){
		ListNode *slow=head,*fast=head;
		while(fast&&fast->next){
			slow=slow->next;
			fast=fast->next->next;
			if(slow==fast){
				ListNode *slow2=head;
				while(slow2!=slow){
					slow2=slow2->next;
					slow=slow->next;
				}
				return slow2;
			}
		}
		return nullptr;
	}
}

//reorder list
class Solution{
public:
	ListNode *reorderList(ListNode *head){
		if(head==nullptr||head->next==nullptr)
			return;
		ListNode *slow=head,*fast=head,*prev=nullptr;
		while(fast&&fast->next){
			prev=slow;
			slow=slow2->next;
			fast=fast->next->next;
		}
		prev->next=nullptr;  //从中间切断链表
		slow=reverse(slow);  //将后半部分链表翻转
		//合并两个链表
		ListNode *curr=head;
		while(curr->next){
			ListNode *tmp=curr->next;
			curr->next=slow;
			slow=slow->next;
			curr->next->next=tmp;
			curr=tmp;
		}
		curr->next=slow;

	}
	//翻转链表函数
	ListNode *reverse(ListNode *head){
		if(head==nullptr||head->next==nullptr)
			return head;
		ListNode *prev=head;
		for(ListNode *curr=head->next,*next=curr->next;curr;
			prev=curr,curr=next,next=next?next->next:nullptr){
			curr->next=prev;
		}
		head->next=nullptr;
		return prev;
	}
}

//LRU cache
class LRUcache{
private:
	struct CacheNode{
		int key;
		int value;
		CacheNode(int k,int v):key(k),value(v){}	
	};
public:
	LRUcache(int capacity){
		this->capacity=capacity;
	}
	int get(int key){
		if (cacheMap.find(key)==cacheMap.end())
			return -1;
		cacheList.splice(cacheList.begin(),cacheList,cacheMap[key]);
		cacheMap[key]=cacheList.begin();
		return cacheMap[key]->value;
	}
	void set(int key,int value){
		if 
	}
}





//Copy List with Random Pointer链表的深度拷贝


