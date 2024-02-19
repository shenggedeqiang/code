//////////////////////////////////////////////////////////////////
///                                                            ///
///                           二叉树                            ///
///                                                            ///
//////////////////////////////////////////////////////////////////
//Binary Tree preorder Traversal
一般我们提到树的遍历，最常见的有先序遍历，中序遍历，后序遍历和层序遍历，
它们用递归实现起来都非常的简单。而题目的要求是不能使用递归求解，
于是只能考虑到用非递归的方法，这就要用到stack来辅助运算。
由于先序遍历的顺序是"根-左-右", 算法为：
1. 把根节点push到栈中
2. 循环检测栈是否为空，若不空，则取出栈顶元素，保存其值，然后看其右子节点是否存在，
   若存在则push到栈中。再看其左子节点，若存在，则push到栈中。
代码如下：
class Solution{
public:
	vector<int> preorderTraversal(TreeNode *root){
		if(!root) return {};
		vector<int> res;
		stack<TreeNode*> s;
		while(!s.empty()){
			TreeNode *t=s.top();s.pop();
			res.push_back(t->val);
			if(t->right) s.push(t->right);
			if(t->left) s.push(t->left);
		}
		return res;
	}
}

======================================================================
//Binary Tree inorder Traversal
二叉树的中序遍历顺序为左-根-右，可以有递归和非递归来解，其中非递归解法又分为两种，
一种是使用栈来接，另一种不需要使用栈。我们先来看递归方法，十分直接，对左子结点调用递归函数，
根节点访问值，右子节点再调用递归函数，代码如下：
// Recursion(递归)
class Solution{
public:
	vector<int> inorderTraversal(TreeNode *root){
		vector<int> res;
		inorder(root,res);
		return res;
	}
	void inorder(TreeNode *root,vector<int> &res){
		if(!root) return;
		if(root->left) inorder(root->left,res);
		res.push_back(root->val);
		if(root->right) inorder(root->right,res);
	}
}
下面我们再来看非递归使用栈的解法，也是符合本题要求使用的解法之一，需要用栈来做，
思路是从根节点开始，先将根节点压入栈，然后再将其所有左子结点压入栈，然后取出栈顶节点，
保存节点值，再将当前指针移到其右子节点上，若存在右子节点，则在下次循环时又可将其所有
左子结点压入栈中。这样就保证了访问顺序为左-根-右，代码如下：
//使用栈
class Solution{
public:
	vector<int> inorderTraversal(TreeNode *root){
		vector<int> res;
		stack<TreeNode*> s;
		TreeNode *p=root;
		while(p || !s.empty()){
			while(p){
				s.push(p);
				p=p->left;
			}
			p=s.top(); s.pop();
			res.push_back(p->val);
			p=p->right;
		}
		return res;
	}
}

=====================================================================
//Binary Tree Postorder Traversal
class Solution{
public:

}

=====================================================================

//is same Tree 递归版本
class Solution{
public:
	bool isSameTree(TreeNode *p,TreeNode *q){
		if(!p && !q) return true;  //都为空树
		if((p && !q) || (!p && q) || (p->val!=q->val)) //其中一个为空或者值不一样
			return false;
		return isSameTree(p->left,q->left) && isSameTree(p->right,q->right);

	}
}
这道题还有非递归的解法，因为二叉树的四种遍历(层序，先序，中序，后序)均有各自的迭代和递归的写法，
这里我们先来看先序的迭代写法，相当于同时遍历两个数，然后每个节点都进行比较，
参见代码如下:
class Solution{
public:
	bool isSameTree(TreeNode *p,TreeNode *q){
		stack<TreeNode*>s1,s2;
		if(p) s1.push(p);
		if(q) s2.push(q);
		while(!s1.empty() && !s2.empty()){
			TreeNode *t1=s1.top();s1.pop();
			TreeNode *t2=s2.top();s2.pop();
			if(t1->val!=t2->val) return false;
			if(t1->left) s1.push(t1->left);
			if(t2->left) s2.push(t2->left);
			if(s1.szie()!=s2.size()) return false;
			if(t1->right) s1.push(t1->right);
			if(t2->right) s2.push(t2->right);
			if(s1.size()!=s2.size()) return false;
		}
		return s1.size()==s2.size();
	}
}

======================================================================
//symmentric Tree
判断二叉树是否是平衡树，比如有两个节点n1, n2，我们需要比较n1的左子节点的值和n2的右子节点的值
是否相等，同时还要比较n1的右子节点的值和n2的左子结点的值是否相等，以此类推比较完所有的左右两个
节点。我们可以用递归和迭代两种方法来实现，写法不同，但是算法核心都一样。
解法一递归：








========================================================================
//Balanced Binary Tree 平衡二叉树
求二叉树是否平衡，根据题目中的定义，高度平衡二叉树是每一个结点的两个子树的深度差不能超过1，
那么我们肯定需要一个求各个点深度的函数，然后对每个节点的两个子树来比较深度差，时间复杂度
为O(NlgN)，代码如下：
class Solution{
public:
	bool isBlancedBinary(TreeNode *root){
		if(!root) return true;
		if(abs(getDepth(root->left)-getDepth(root->right))>1) return false;
		return isBlancedBinary(root->left) && isBlancedBinary(root->right);
	}
	int getDepth(TreeNode *root){
		if(!root) return 0;
		return 1+max(getDepth(root->left),getDepth(root->right));
	}
}


class Solution{
public:
	bool isBlancedBinary(TreeNode *root){
		if(checkDepth(root)==-1) return false;
		else return true;
	}
	int checkDepth(TreeNode *root){
		if(!root) return 0;
		int left=checkDepth(root->left);
		if(left==-1) return -1;
		int right=checkDepth(root->right);
		if(right==-1) return -1;
		int diff=abs(left-right);
		if(diff>1)return -1;
		else return 1+max(left,right);
	}
}

========================================================================
//Search for a Range 搜索一个范围
O(logn)的算法
使用两次二分查找法，第一次找到左边界，第二次调用找到右边界即可，具体代码如下：
class Solution{
public:
	vector<int> searchRange(vector<int>& nums,int target){
		vector<int> res(2,-1);
		int left=0,right=nums.size()-1;
		while(left<right){
			int mid=left+(right-left)/2;
			if(nums[mid] < target) left=mid+1;
			else right=mid;
		}
		if(nums[right]!=target)return res;
		res[0]=right;
		right=nums.size();
		while(left<right){
			int mid=left+(right-left)/2;
			if(nums[mid]<=target)left=mid+1;
			else right=mid;
		}
		res[1]=left-1;
		return res;
	}
}
================================================
//将二叉树展开成链表
先利用DFS的思路找到最左子节点，然后回到其父节点，把其父节点和右子节点断开，将原左子结点连上
父节点的右子节点上，然后再把原右子节点连到新右子节点的右子节点上，然后再回到上一父节点做
相同操作。代码如下：
class Solution
{
public:
	void falatten(TreeNode *root){
		if(!root) return;
		if(root->left) falatten(root->left);
		if(root->right) falatten(root->right);
		TreeNode *tmp=root->right;
		root->right=root->left;
		root->left=NULL;
		while(root->right) root=root->right;
		root->right=tmp;
	}
	
};

=============================================================
//Construct Binary Tree from Preorder and Inorder Traversal
//由先序和中序遍历建立二叉树
针对这道题，由于先序的顺序的第一个肯定是根，所以原二叉树的根节点可以知道，题目中给了一个
很关键的条件就是树中没有相同元素，有了这个条件我们就可以在中序遍历中也定位出根节点的位置，
并以根节点的位置将中序遍历拆分为左右两个部分，分别对其递归调用原函数。代码如下：
 /**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
    TreeNode *buildTree(vector<int> &preorder, int pLeft, int pRight, vector<int> &inorder, int iLeft, int iRight) {
        if (pLeft > pRight || iLeft > iRight) return NULL;
        int i = 0;
        for (i = iLeft; i <= iRight; ++i) {
            if (preorder[pLeft] == inorder[i]) break;
        }
        TreeNode *cur = new TreeNode(preorder[pLeft]);
        cur->left = buildTree(preorder, pLeft + 1, pLeft + i - iLeft, inorder, iLeft, i - 1);
        cur->right = buildTree(preorder, pLeft + i - iLeft + 1, pRight, inorder, i + 1, iRight);
        return cur;
    }
};

=======================================================
//Unique Binary Search Trees 独一无二的二叉搜索树  动态规划
class Solution{
public:
	int numTrees(int n){
		vector<int> dp(n+1,0);
		dp[0]=0;
		dp[1]=0;
		for(int i=2;j<i;++j){
		    for(int i=2;i<=n;++i){
		    	dp[i]+=dp[j]*dp[i-j-1];
		    }
		}
		return dp[n];
	}
}

//Unique Binary Search Trees II
这道题是之前的 Unique Binary Search Trees 独一无二的二叉搜索树的延伸，之前那个只要求
算出所有不同的二叉搜索树的个数，这道题让把那些二叉树都建立出来。这种建树问题一般来说都是用
递归来解，这道题也不例外，划分左右子树，递归构造。至于递归函数中为啥都用的是指针，是参考了
网友水中的鱼的博客，若不用指针，全部实例化的话会存在大量的对象拷贝，要调用拷贝构造函数，
具体我也不太懂，反正感觉挺有道理的，不明觉厉啊

class Solution{
public:
	vector<TreeNode *> generateTrees(int n){
		if (n==0) return{};
		return *generateTreesDFS(1,n);
	} 
	vector< TreeNode *> *generateTreesDFS(int start,int end){
		vector<TreeNode*> *subTree=new vector<TreeNode *>;
		if(start>end) subTree->push_back(NULL);
		else{
			for(int i=start;i<=end;++i){
				vector<TreeNode*> *leftSubTree=generateTreesDFS(start,i-1);
				vector<TreeNode*> *rightSubTree=generateTreesDFS(i+1,end);
				for(int j=0,j<leftSubTree->size();++j){
					for(int k=0,k<rightSubTree->size();++k){
						TreeNode *node=new TreeNode(i);
						node->left=(*leftSubTree)[j];
						node->right=(*rightSubTree)[k];
						subTree->push_back(node);
					}
				}
			}
		}
		return subTree;
	}
}

=======================================================================
/*Validate Binary Search Tree验证二叉搜索树
这道验证二叉搜索树有很多种解法，可以利用它本身的性质来做，即左<根<右，也可以通过利用
中序遍历结果为有序数列来做，下面我们先来看最简单的一种，就是利用其本身性质来做，初始化时
带入系统最大值和最小值，在递归过程中换成它们自己的节点值，用long代替int就是为了包括int
的边界条件，代码如下：
*/


class Solution{
public:
	bool isValidBTS(TreeNode* root){
		return isValidBTS(root,LONG_MIN,LONG_MAX);
	}
	bool isValidBTS(TreeNode* root,long mn,long mx){
		if(!root) return true;
		if(root->val < mn || root->val >= mx)return false;
		return isValidBTS(root->left,mn,root->val) && isValidBTS(root->right,root->val,mx);
	}

}
=====================================================================
/*Convert Sorted Array to Binary Search Tree将有序数组转为二叉搜索树
这道题是要将有序数组转为二叉搜索树，所谓二叉搜索树，是一种始终满足左<根<右的特性，
如果将二叉搜索树按中序遍历的话，得到的就是一个有序数组了。那么反过来，我们可以得知，
根节点应该是有序数组的中间点，从中间点分开为左右两个有序数组，在分别找出其中间点作为
原中间点的左右两个子节点，这不就是是二分查找法的核心思想么。所以这道题考的就是二分查找法，
代码如下：
*/

class Solution{
public:
	TreeNode* sortedArrayToBST(vector<int>& nums){
		return helper(nums,0,(int)nums.size()-1);
	}
	TreeNode* helper(vector<int>& nums,int left,int right){
		if(left>right)return NULL;
		int mid=left+(right-left)/2;
		TreeNode *cur=new TreeNode(nums[mid]);
		cur->left=helper(nums,left,mid-1);
		cur->right=helper(nums,mid+1,right);
		return cur;
	}
}

我们也可以不使用额外的递归函数，而是在原函数中完成递归，由于原函数的参数是一个数组，
所以当把输入数组的中间数字取出来后，需要把所有两端的数组组成一个新的数组，并且分别
调用递归函数，并且连到新创建的cur结点的左右子结点上面，参见代码如下


class Solution{
public:
	TreeNode* sortedArrayToBST(vector<int>& nums){
		if(nums.empty()) return NULL;
		int mid=nums.szie()/2;
		TreeNode *cur=new TreeNode(nums[mid]);
		vector<int> left(nums.begin(),nums.begin()+end),right(nums.begin()+mid+1,nums.end());
		cur->left=sortedArrayToBST(left);
		cur->right=sortedArrayToBST(right);
		return cur;
	}
}

====================================================================
//Convert Sorted List to Binary Search Tree 将有序链表转为二叉搜索树
这道题是要求把有序链表转为二叉搜索树，和之前那道 Convert Sorted Array to Binary 
Search Tree 思路完全一样，只不过是操作的数据类型有所差别，一个是数组，一个是链表。
数组方便就方便在可以通过index直接访问任意一个元素，而链表不行。由于二分查找法每次需要
找到中点，而链表的查找中间点可以通过快慢指针来操作，可参见之前的两篇博客 Reorder List
 和 Linked List Cycle II 有关快慢指针的应用。找到中点后，要以中点的值建立一个数的根节点，
 然后需要把原链表断开，分为前后两个链表，都不能包含原中节点，然后再分别对这两个链表递归
 调用原函数，分别连上左右子节点即可。代码如下：

 class Solution{
 public:
 	TreeNode *sortedListToBST(ListNode* head){
 		if(!head) return NULL;
 		if(!head->neat) return new TreeNode(head->val);
 		ListNode *slow=head,*fast=head,*last=slow;
 		while(fast->neat && fast->next->next){
 			last=slow;
 			slow=slow->next;
 			fast=fast->next->next;
 		}
 		fast=slow->next;
 		last->next=NULL;
 		TreeNode* cur=new TreeNode(slow->val);
 		if(head!=slow) cur->left=sortedListToBST(head);
 		cur->right=sortedListToBST(fast);
 		return cur;
 	}
 }
我们也可以采用如下的递归方法，重写一个递归函数，有两个输入参数，子链表的起点和终点，
因为知道了这两个点，链表的范围就可以确定了，而直接将中间部分转换为二叉搜索树即可，
递归函数中的内容跟上面解法中的极其相似，参见代码如下：

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return NULL;
        return helper(head, NULL);
    }
    TreeNode* helper(ListNode* head, ListNode* tail) {
        if (head == tail) return NULL;
        ListNode *slow = head, *fast = head;
        while (fast != tail && fast->next != tail) {
            slow = slow->next;
            fast = fast->next->next;
        }
        TreeNode *cur = new TreeNode(slow->val);
        cur->left = helper(head, slow);
        cur->right = helper(slow->next, tail);
        return cur;
    }
}


======================================================================
//Minimum Depth of Binary Tree二叉树的最小深度
二叉树的经典问题之最小深度问题就是就最短路径的节点个数，还是用深度优先搜索DFS来完成，
万能的递归啊。首先判空，若当前结点不存在，直接返回0。然后看若左子结点不存在，那么对右子结点
调用递归函数，并加1返回。反之，若右子结点不存在，那么对左子结点调用递归函数，并加1返回。
若左右子结点都存在，则分别对左右子结点调用递归函数，将二者中的较小值加1返回即可，参见代码如下：

class Solution{
public:
	int minDepth(TreeNode* root){
		if(!root) return 0;
		if(!root->left) return 1+minDepth(root->right);
		if(!root->right) return 1+minDepth(root->left);
		return 1+min(minDepth(root->left),minDepth(root->right));
	}
}
我们也可以是迭代来做，层序遍历，记录遍历的层数，一旦我们遍历到第一个叶结点，就将当前层数返回，
即为二叉树的最小深度，参见代码如下：

class Solution{
public:
	int minDepth(TreeNode* root){
		if(!root) return 0;
		int res=0;
		queue<TreeNode*>q{{root}};
		while(!q.empty()){
			++res;
			for(int i=q.size();i>0;--i){
				auto t=q.front();q.pop();
				if(!t->left && !t->right) return res;
				if(t->left ) q.push(t->left);
				if(t->right) q.push(t->right);

			}
		}
		return -1;
	}
}

======================================================================
//Maximum Depth of Binary Tree二叉树的最大深度
求二叉树的最大深度问题用到深度优先搜索DFS，递归的完美应用，跟求二叉树的最小深度问题原理相同。
代码如下：

class Solution{
public:
	int maxDepth(TreeNode* root){
		if(!root) return 0;
		return 1+max(maxDepth(root->left),maxDepth(root->right));
	}

}

我们也可以使用层序遍历二叉树，然后计数总层数，即为二叉树的最大深度，参见代码如下：

class Solution{
public:
	int maxDepth(TreeNode* root){
		if(!root) return 0;
		int res=0;
		queue<TreeNode*> q{{root}};
		while(!q.empty()){
			++res;
			for(int i=q.size();i>0;--i){
				TreeNode *t=q.front();q.pop();
				if(t->left) q.push(t->left);
				if(t->right) q.push(t->right);
			}
		}
		return res;
	}
}

======================================================================
//Path Sum 二叉树的路径和
这道求二叉树的路径需要用深度优先算法DFS的思想来遍历每一条完整的路径，也就是利用递归不停
找子节点的左右子节点，而调用递归函数的参数只有当前节点和sum值。首先，如果输入的是一个空节点，
则直接返回false，如果如果输入的只有一个根节点，则比较当前根节点的值和参数sum值是否相同，
若相同，返回true，否则false。 这个条件也是递归的终止条件。下面我们就要开始递归了，
由于函数的返回值是Ture/False，我们可以同时两个方向一起递归，中间用或||连接，只要有一个
是True，整个结果就是True。递归左右节点时，这时候的sum值应该是原sum值减去当前节点的值。
代码如下：
class Solution{
public:
	bool hasPathSum(TreeNode* root,int sum){
		if(!root) return false;
		if(!root->left && !root->right && root->val==sum) return true;
		return hasPathSum(root->left,sum-root->val) || hasPathSum(root->right,sum-root->val);	
	}
}

我们也可以使用迭代的写法，这里用的也是先序遍历的迭代写法，我们先序遍历二叉树，左右子结点
都需要加上其父结点值，这样当遍历到叶结点时，如果和sum相等了，那么就说明一定有一条从root
过来的路径。注意这里我们不必一定要先处理右子结点，调换下顺序也是可以的，因为不论是先序遍历
的根-左-右，还是根-右-左，并不会影响到我们找路径，参见代码如下：

class Solution{
public:
	bool hasPathSum(TreeNode* root,int sum){
		if(!root) return false;
		stack<TreeNode*> st{{root}};
		while(!st.empty()){
			TreeNode *t=st.pop();st.pop();
			if(!t->left && !t->right){
				if(t->val==sum) return true; 
			}
			if(t->right){
				t->right->val+=t->val;
				st.push(t->right);
			}
			if(t->left){
				t->left->val+=t->val;
				st.push(t->left);
			}
		}
		return false;
	}
}

=============================================================
//Path Sum II 二叉树路径之和之二
这道二叉树路径之和在之前的基础上又需要找出路径，但是基本思想都一样，还是需要用
深度优先搜索DFS，只不过数据结构相对复杂一点，需要用到二维的vector，而且
每当DFS搜索到新节点时，都要保存该节点。而且每当找出一条路径之后，都将这个保存为
一维vector的路径保存到最终结果二位vector中。并且，每当DFS搜索到子节点，发现
不是路径和时，返回上一个结点时，需要把该节点从一维vector中移除。代码如下：
class Solution{
public:
	vector<vector<int>> pathSum(TreeNode *root,int sum){
		vector<vector<int>> res;
		vector<int> out;
		helper(root,sum,out,res);
		return res;
	}
	void helper(TreeNode* node,int sum,vector<int>&out,vector<vector<int>>& res){
		if(!node) return;
		out.push_back(node->val);
		if(sum==node->val && !node->left && !node->right){
			res.push_back(out);
		}
		helper(node->left,sum-node->val,out,res);
		helper(node->right,sum-node->val,out,res);
		out.pop_back();
	}
}

下面这种方法是迭代的写法，用的是中序遍历的顺序，参考之前那道Binary Tree Inorder 
Traversal，中序遍历本来是要用栈来辅助运算的，由于我们要取出路径上的节点值，所以我们
用一个vector来代替stack，首先利用while循环找到最左子节点，在找的过程中，把路径中的节点值
都加起来，这时候我们取出vector中的尾元素，如果其左右子节点都不存在且当前累加值正好等于sum了，
我们将这条路径取出来存入结果res中，下面的部分是和一般的迭代中序写法有所不同的地方，因为如果
当前最左节点已经是个叶节点了，我们要转移到其他的节点上时需要把当前的节点值减去，而如果当前
最左节点不是叶节点，下面还有一个右子节点，这时候移动指针时就不能减去当前节点值，为了区分
这两种情况，我们需要用一个额外指针pre来指向前一个节点，如果右子节点存在且不等于pre，我们
直接将指针移到右子节点，反之我们更新pre为cur，cur重置为空，val减去当前节点，s删掉最后
一个节点，参见代码如下：

class Solution {
public:
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int>> res;
        vector<TreeNode*> s;
        TreeNode *cur = root, *pre = NULL;
        int val = 0;
        while (cur || !s.empty()) {
            while (cur) {
                s.push_back(cur);
                val += cur->val;
                cur = cur->left;
            }
            cur = s.back(); 
            if (!cur->left && !cur->right && val == sum) {
                vector<int> v;
                for (auto it : s) {
                    v.push_back(it->val);
                }
                res.push_back(v);
            }
            if (cur->right && cur->right != pre) cur = cur->right;
            else {
                pre = cur;
                val -= cur->val;
                s.pop_back();
                cur = NULL;
            }
        }
        return res;
    }
}

====================================================================
//Binary Tree Maximum Path Sum 求二叉树的最大路径和
这道求二叉树的最大路径和是一道蛮有难度的题，难就难在起始位置和结束位置可以为任意位置，
我当然是又不会了，于是上网看看大神们的解法，像这种类似数的遍历的题，一般来说都需要用DFS
来求解，我们先来看一个简单的例子：
    4
   / \
  11 13
 / \
7   2
由于这是一个很简单的例子，我们很容易就能找到最长路径为7-11-4-13，那么怎么用递归来找出
正确的路径和呢？根据以往的经验，树的递归解法一般都是递归到叶节点，然后开始边处理边回溯到
根节点。那么我们就假设此时已经递归到结点7了，那么其没有左右子节点，所以如果以结点7为根结点
的子树最大路径和就是7。然后回溯到结点11，如果以结点11为根结点的子树，我们知道最大路径和为
7+11+2=20。但是当回溯到结点4的时候，对于结点11来说，就不能同时取两条路径了，只能取左路径，
或者是右路径，所以当根结点是4的时候，那么结点11只能取其左子结点7，因为7大于2。所以，对于
每个结点来说，我们要知道经过其左子结点的path之和大还是经过右子节点的path之和大。那么我们
的递归函数返回值就可以定义为以当前结点为根结点，到叶节点的最大路径之和，然后全局路径最大值
放在参数中，用结果res来表示。
在递归函数中，如果当前结点不存在，那么直接返回0。否则就分别对其左右子节点调用递归函数，由于
路径和有可能为负数，而我们当然不希望加上负的路径和，所以我们和0相比，取较大的那个，就是要么
不加，加就要加正数。然后我们来更新全局最大值结果res，就是以左子结点为终点的最大path之和加
上以右子结点为终点的最大path之和，还要加上当前结点值，这样就组成了一个条完整的路径。而我们
返回值是取left和right中的较大值加上当前结点值，因为我们返回值的定义是以当前结点为终点的
path之和，所以只能取left和right中较大的那个值，而不是两个都要，参见代码如下：
