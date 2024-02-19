//////////////////////////////////////////////////////////////////
///                                                            ///
///                         排序和查找                           ///
///                                                            ///
//////////////////////////////////////////////////////////////////
//Merge Sorted Array合并两个有序数组
class Solution{
public:
	void merge(vector<int>& A,int m,vector<int>& B,int n){
		int ia=m-1,ib=n-1,icur=m+n-1;
		while(ia>=0 && ib>=0){
			A[icur--]=A[ia]>=B[ib--]?A[ia--]:B[ib--];
		}
		while(ib>=0){
			A[icur--]=B[ib--];
		}
	}
}
题目中说了nums1数组有足够大的空间，说明我们不用resize数组，又给了我们m和n，
那就知道了混合之后的数组的大小，这样我们就从nums1和nums2数组的末尾开始一个一个比较，
把较大的数，按顺序从后往前加入混合之后的数组末尾。需要三个变量i，j，k，分别指向nums1，
nums2，和混合数组的末尾。进行while循环，如果i和j都大于0，再看如果nums1[i] > nums2[j]，
说明要先把nums1[i]加入混合数组的末尾，加入后k和i都要自减1；反之就把nums2[j]加入混合数组
的末尾，加入后k和j都要自减1。循环结束后，有可能i或者j还大于等于0，若j大于0，那么我们还需要
继续循环，将nums2中的数字继续拷入nums1。若是i大于等于0，那么就不用管，因为混合数组本身就
放在nums1中，参见代码如下：

class Solution{
public:
	void merge(vector<int>& nums1,int m,vector<int>& nums2,int n){
		int i=m-1,j=n-1,k=m+n-1;
		while(i>=0 && j>=0){
			if(nums1[i]>nums2) nums1[k--]=nums1[i--];
			else nums1[k--]=nums2[j--];
		}
		while(j>=0) nums1[k--]=nums2[j--];
	}
}

//Merge Two Sorted Lists合并两个有序链表
新建一个链表，然后比较两个链表中的元素值，把较小的那个链到新链表中，由于两个输入链表的长度可
能不同，所以最终会有一个链表先完成插入所有元素，则直接另一个未完成的链表直接链入新链表的末尾。
代码如下：
class Solution{
public:
	ListNode* mergeTwoLists(ListNode* l1,ListNode* l2){
		ListNode *dummy=new ListNode(-1),*cur=dummy;
		while(l1 && l2){
			if(l1->val < l2->val){
				cur->next=l1;
				l1=l1->next;
			}
			else{
				cur->next=l2;
				l2=l2->next;
			}
			cur=cur->next;
		}
		cur->next=l1?l1:l2;
		return dummy->next;
	}
}

//Merge k Sorted Lists 合并k个有序链表
这里就需要用到分治法。简单来说就是不停的对半划分，比如k个链表先划分为合并两个k/2个链表的任务，
再不停的往下划分，直到划分成只有一个或两个链表的任务，开始合并。举个例子来说比如合并6个链表，
那么按照分治法，我们首先分别合并0和3，1和4，2和5。这样下一次只需合并3个链表，我们再合并1和3，
最后和2合并就可以了。代码中的k是通过 (n+1)/2 计算的，这里为啥要加1呢，这是为了当n为奇数的
时候，k能始终从后半段开始，比如当n=5时，那么此时k=3，则0和3合并，1和4合并，最中间的2空出来。
当n是偶数的时候，加1也不会有影响，比如当n=4时，此时k=2，那么0和2合并，1和3合并，完美解决问题，
参见代码如下：
class Solution{
public:
	ListNode* mergeKLists(vector<ListNode*>& lists){
		if(lists.empty()) return null;
		int n=lists.size();
		while(n>1){
			int k=(n+1)/2;
			for(int i=0;i<n/2;++i){
				lists[i]=mergeTwoLists(lists[i];lists[i+k]);
			}
			n=k;
		}
		return lists[0];
	}
	ListNode* mergeTwoLists(ListNode* l1,ListNode* l2){
		ListNode *dummy=new ListNode(-1),*cur=dummy;
		while(l1 && l2){
			if(l1->val < l2->val){
				cur->next=l1;
				l1=l1->next;
			}
			else{
				cur->next=l2;
				l2=l2->next;
			}
			cur=cur->next;
		}
		if(l1) cur->next=l1;
		if(l2) cur->next=l2;
		return dummy->next;
	}
}

//Insertion Sort List链表插入排序
class Solution{
public:
	ListNode *InsertionSortList(ListNode* head){
		ListNode *dummy=new ListNode(-1),*cur=dummy;
		while(head){
			ListNode *t=head->next;
			cur=dummy;
			while(cur->next && cur->next->val <= head->val){
				cur=cur->next;
			}
			head->next=cur->next;
			cur->next=head;
			head=t;
		}
		return dummy->next;
	}
}

