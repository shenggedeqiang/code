//////////////////////////////////////////////////////////////////
///                                                            ///
///                            数组                             ///
///                                                            ///
////////////////////////////////////////////////////////////////// 
//Remove Duplicates from Sorted Array  有序数组中去除重复项
class solution{
public:
	int removeDuplicates(vector<int>& nums){
		if (nums.empty()) return 0;
		int index=0;
		for (int i=1;i<nums.size();i++){
			if (nums[index]!=nums[i])
				nums[++index]=nums[i];
		}
		return index+1;
	}
}
那么这道题的解题思路是，我们使用快慢指针来记录遍历的坐标，最开始时两个指针都指向第一个数字，如果两个指针指的
数字相同，则快指针向前走一步，如果不同，则两个指针都向前走一步，这样当快指针走完整个数组后，慢指针当前的坐标
加1就是数组中不同数字的个数，代码如下：
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int pre = 0, cur = 0, n = nums.size();
        while (cur < n) {
            if (nums[pre] == nums[cur]) ++cur;
            else nums[++pre] = nums[cur++];
        }
        return pre + 1;
    }
};

//Remove Duplicates from Sorted Array II 有序数组中去除重复项之二
这道题是之前那道 Remove Duplicates from Sorted Array 有序数组中去除重复项 的延续，这里允许最多重复的
次数是两次，那么我们就需要用一个变量count来记录还允许有几次重复，count初始化为1，如果出现过一次重复，则
count递减1，那么下次再出现重复，快指针直接前进一步，如果这时候不是重复的，则count恢复1，由于整个数组是有序的，
所以一旦出现不重复的数，则一定比这个数大，此数之后不会再有重复项。理清了上面的思路，则代码很好写了：
class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n <= 2) return n;
        int pre = 0, cur = 1, count = 1;
        while (cur < n) {
            if (A[pre] == A[cur] && count == 0) ++cur;
            else {
                if (A[pre] == A[cur]) --count;
                else count = 1;
                A[++pre] = A[cur++];
            }
        }
        return pre + 1;
    }
};
//Trapping Rain Water 收集雨水
class solution{
public:
	int trap(vector<int>& height){
		int res=0,mx=0,n=height.size();
		vector<int> dp(n,0);
		for(int i=0;i<n;++i){
			dp[i]=mx;
			mx=max(mx,height[i]);
		}
		mx=0;
		for(int i=n-1;i>=0;--i){
			dp[i]=min(dp[i],mx);
			mx=max(mx,height[i]);
			if(dp[i]>height)
				res+=dp[i]-height[i];
		}
		return res
	}
}

//旋转数组
class solution{
public:
	void rotatearray(vector<vector<int>>& martrix){
		const int n=martrix.size();
		for(int i=0;i<n;++i)
			for(int j=0;j<n-j;++j)
				swap(martrix[i][j],martrix[n-1-j][n-1-i]);
	    for(int i=0;i<n/2;++j)
	    	for(intj=0;j<n;++j)
	    		swap(martrix[i][j],martrix[n-1-i][j]);
	}
}

//gasstation
这道转圈加油问题不算很难，只要想通其中的原理就很简单。
我们首先要知道能走完整个环的前提是gas的总量要大于cost的总量，
这样才会有起点的存在。假设开始设置起点start = 0, 并从这里出发，
如果当前的gas值大于cost值，就可以继续前进，此时到下一个站点，
剩余的gas加上当前的gas再减去cost，看是否大于0，若大于0，则继续前进。
当到达某一站点时，若这个值小于0了，则说明从起点到这个点中间的任何一个点都不能作为起点，
则把起点设为下一个点，继续遍历。当遍历完整个环时，当前保存的起点即为所求。代码如下：
class solution{
public:
	int canCompleteCircuit(vector<int>& gas,vector<int> &cost){
		int total=0;
		int j=-1;
		for(int i=0;sum=0;i<gas.size();++i){
			sum+=gas[i]-cost[i];
			total+=gas[i]-cost[i];
			if(sum<0){
				j=i;
				sum=0;
			}
		}
		return total>=0?j+1:-1;
	}
}
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0, sum = 0, start = 0;
        for (int i = 0; i < gas.size(); ++i) {
            total += gas[i] - cost[i];
            sum += gas[i] - cost[i];
            if (sum < 0) {
                start = i + 1;
                sum = 0;
            }
        }
        return (total < 0) ? -1 : start;
    }
}

//Candy
这道题看起来很难，其实解法并没有那么复杂，当然我也是看了别人的解法才做出来的，
先来看看两遍遍历的解法，首先初始化每个人一个糖果，然后这个算法需要遍历两遍，
第一遍从左向右遍历，如果右边的小盆友的等级高，等加一个糖果，
这样保证了一个方向上高等级的糖果多。然后再从右向左遍历一遍，
如果相邻两个左边的等级高，而左边的糖果又少的话，则左边糖果数为右边糖果数加一。
最后再把所有小盆友的糖果数都加起来返回即可。代码如下：
class solution{
public:
	int candy(vector<int>& ratings){
		int res=0;n=ratings.size();
		vector<int>nums(n,1);
		for(int =0;i<n-1;++i){
			if(ratings[i+1]>ratings[i]) nums[i+1]=nums[i]+1;
		}
		for(int i=n-1;i>0;i--){
			if(ratings[i-1]>ratings[i]) nums[i-1]=max(nums[i-1],nums[i]+1);
		}
		for(int num:nums)res+=num;
		return res;
	}
}
下面来看一次遍历的方法，相比于遍历两次的思路简单明了，这种只遍历一次的解法就稍有些复杂了。
首先我们给第一个同学一个糖果，那么对于接下来的一个同学就有三种情况：

1. 接下来的同学的rating等于前一个同学，那么给接下来的同学一个糖果就行。

2. 接下来的同学的rating大于前一个同学，那么给接下来的同学的糖果数要比前一个同学糖果数加1。

3.接下来的同学的rating小于前一个同学，那么我们此时不知道应该给这个同学多少个糖果，需要看后面的情况。
对于第三种情况，我们不确定要给几个，因为要是只给1个的话，那么有可能接下来还有rating更小的同学，
总不能一个都不给吧。也不能直接给前一个同学的糖果数减1，有可能给多了，
因为如果后面再没人了的话，其实只要给一个就行了。还有就是，如果后面好几个rating越来越小的同学，
那么前一个同学的糖果数可能还得追加，以保证最后面的同学至少能有1个糖果。
来一个例子吧，四个同学，他们的rating如下：1 3 2 1
先给第一个rating为1的同学一个糖果，然后从第二个同学开始遍历，第二个同学rating为3，比1大，
所以多给一个糖果，第二个同学得到两个糖果。下面第三个同学，他的rating为2，比前一个同学的rating小，
如果我们此时给1个糖果的话，那么rating更小的第四个同学就得不到糖果了，所以我们要给第四个同学1个糖果，
而给第三个同学2个糖果，此时要给第二个同学追加1个糖果，使其能够比第三个同学的糖果数多至少一个。
那么我们就需要统计出多有个连着的同学的rating变小，用变量cnt来记录，找出了最后一个减小的同学，
那么就可以往前推，每往前一个加一个糖果，这就是个等差数列，
我们可以直接利用求和公式算出这些rating减小的同学的糖果之和。
然后我们还要看第一个开始减小的同学的前一个同学需不需要追加糖果，
只要比较cnt和pre的大小，pre是之前同学得到的最大糖果数，二者做差加1就是需要追加的糖果数，
加到结果res中即可，参见代码如下：
class Solution {
public:
    int candy(vector<int>& ratings) {
        if (ratings.empty()) return 0;
        int res = 1, pre = 1, cnt = 0;
        for (int i = 1; i < ratings.size(); ++i) {
            if (ratings[i] >= ratings[i - 1]) {
                if (cnt > 0) {
                    res += cnt * (cnt + 1) / 2;
                    if (cnt >= pre) res += cnt - pre + 1;
                    cnt = 0;
                    pre = 1;
                }
                pre = (ratings[i] == ratings[i - 1]) ? 1 : pre + 1;
                res += pre;
            } else {
                ++cnt;
            }
        }     
        if (cnt > 0) {
            res += cnt * (cnt + 1) / 2;
            if (cnt >= pre) res += cnt - pre + 1;
        }
        return res;
    }
};
//single number异或是相同为0，不同为1
class Solution{
public:
	int singleNumber(vector<int>& nums){
		int x=0;
		for(auto i:nums){
			x^=i;
		}
		return x;
	}
}

//single numberII
class Solution{
public:
	int singleNumberII(vector<int>& nums){
		const int w=sizeof(int)*8;
		int count[w];
		fill_n(&count[0],w,0);
		for(int i=0;i<nums.size();i++){
			for(int j=0;j<w;j++){
				count[j]+=(nums[i]>>j)&1;
				count[j]%=3;
			}
		}
		int result=0;
		for(int i=0;i<w;i++){
			result+=(count[i]<<i);
		}
		return result;
	}
}
//add two numbers
class Solution{
public:
	ListNode *addTwoNumbers(ListNode *l1,ListNode *l2){
		ListNode dummpy(-1);
		int carry;
		ListNode *prev=&dummpy;
		for(ListNode *pa=lq,ListNode *pb=l2;
			pa!=nullptr||pb!=nullptr;
			pa=pa==nullptr?nullptr:pa->next,
			pb=pb==nullptr?nullptr:pb->next,
			prev=prev->next){
			const int ai=pa==nullptr? 0: pa->val;
			const int bi=pb==nullptr? 0: pb->val;
			const int value=(ai+bi+carry)%10;
			carry=(ai+bi+carry)/10;
			prev->next=new ListNode(value);
		}
		if (carry>0)
			prev->next=new ListNode(carry);
		return dummpy.next;
	}
}