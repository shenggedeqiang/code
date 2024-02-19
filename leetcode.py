def reverse(x):#反转数
        """
        :type x: int
        :rtype: int
        """
        #sign=x<0 and -1 or 1
        x=abs(x)
        ans=0
        while x:
            ans=ans*10+x%10
            x/=10
        return ans 
print(reverse(123))
######################################################
def longest(strs):#最长公共前缀
    if len(strs)==0:
        return ""
    i=0
    j=0
    end=0
    while j<len(strs) and i<len(strs[j]):
        if j==0:
            char=strs[j][i]
        else:
            if strs[j][i]!=char:
                break 
        if j==len(strs)-1:
            i+=1
            j=0
            end+=1
        else:
            j+=1
    return strs[j][:end]
##################################################
def isvalied(s):#有效的括号
    stack=[]
    d=["()","[]","{}"]
    for i in range(0,len(s)):
        stack.append(s[i])
        if len(stack)>=2 and stack[-2]+stack[-1] in d:
            stack.pop()
            stack.pop()
    return len(stack)==0
l="{[]}"
#print(isvalied(l))
print(l[-1])
###############################################
class ListNode:
    def __init__(self,x):
        self.val=x
        self.next=0

def mergeTwoLists(l1,l2):#合并两个链表
    """
    type l1:Listnode
    type l2:Listnode
    rtype:Listnode
    """
    head=dummy=ListNode(-1)
    while l1 and l2:
        if l1.val<l2.val:
            head.next=l1
            l1=l1.next
        else:
            head.next=l2
            l2=l2.next
        head=head.next
    if l1:
        head.next=l1
    if l2:
        head.next=l2
    return dummy.next
###########################################
def removeDuplicates(nums):
    """
    type nums:List[int]
    rtpye:int
    """
    if len(nums)<=1:
        return len(nums)
    slow=0
    for i in range(1,len(nums)):
        if nums[i]!=nums[slow]:
            slow+=1
            nums[slow]=nums[i]
    return slow+1
print(removeDuplicates([0,0,1,1,1,3,5,5,6]))
#############################################
def removeElements(nums,val):
    """
    type nums:List[int]
    type val:int
    rtype:int
    """
    slow=-1
    for i in range(0,len(nums)):
        if nums[i]!=val:
            slow+=1
            nums[slow]=nums[i]
    return slow+1
print(removeElements([0,0,1,1,1,3,5,5,6],1))
#############################################
def strStr(haystack,needle):
    """
    type:str
    type:str
    rtype:int
    """
    if len(haystack)==len(needle):
        if haysatck==needle:
            return 0
        else:
            return -1
    for i in range(0,len(haystack)):
        k=i
        j=0
        while j<len(needle) and k<len(haystack) and haystack[k]==needle[j]:
            j+=1
            k+=1
        if j==len(needle):
            return i
    return -1 if needle else 0
a="hello"
b="ll"
print(strStr(a,b))
##########################
def lengthoflastword(s):
    """
    type:str
    rtype:int
    """
    l=len(s)
    w=0
    if s[l-1]==' ':
        return 0
    else:
        while(s[l-1]!=' '):
            l-=1
            w+=1
        return w
print(lengthoflastword("Hello ertioj"))
#######################################
    java代码
public class ListNode{
    int val;
    ListNode next;
    ListNode(int x){val=x;}
}
class Solution{
    public ListNode deleteDuplicates(ListNode){
        ListNode current=head;
        while(current!=null&&current.next!=null){
            if (current.next.val==current.val){
                current.next=current.next.next;
            }
            else current=current.next;
        }
        return head;
    }
}

