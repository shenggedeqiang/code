//////////////////////////////////////////////////////////////////
///                                                            ///
///                          栈和队列                            ///
///                                                            ///
//////////////////////////////////////////////////////////////////
//valid parenthese验证括号
我们需要用一个栈，我们开始遍历输入字符串，如果当前字符为左半边括号时，则将其压入栈中，
如果遇到右半边括号时，若此时栈为空，则直接返回false，如不为空，则取出栈顶元素，
若为对应的左半边括号，则继续循环，反之返回false，代码如下：

class Solution{
public:
	bool isValid(string const& s){
		stack<char> parenthese;
		for(int i=0;i<s.size();++i){
			if(s[i]=='(' || s[i]=='[' ||s[i]=='{')
				parenthese.push(s[i])
			else{
				if(parenthese.empty()) 
					return false;
				if(s[i]==')' && parenthese.top()!='(')
					return false;
				if(s[i]==']' && parenthese.top()!='[')
					return false;
				if(s[i]=='}' && parenthese.top()!='{')
					return false;
				parenthese.pop();
			}
		}
		return parenthese.empty();
	}

}

//Longest Vaild Parenthese最长有效括号
这道求最长有效括号比之前那道 Valid Parentheses 难度要大一些，这里我们还是借助栈来求解，
需要定义个start变量来记录合法括号串的起始位置，我们遍历字符串，如果遇到左括号，
则将当前下标压入栈，如果遇到右括号，如果当前栈为空，则将下一个坐标位置记录到start，
如果栈不为空，则将栈顶元素取出，此时若栈为空，则更新结果和i - start + 1中的较大值，
否则更新结果和i - 栈顶元素中的较大值，代码如下：
class Solution{
public:
	int longesValidParenthese(string s){
		int res=0,start=0;
		stack<int> m;
		for(int i=0;i<s.size();++i){
			if(s[i]=='(') m.push(i);
			else if(s[i]==')'){
				if(m.empty()) start=i+1;
				else{
					m.pop();
					res=m.empty()?max(res,i-start+1):max(res,i-m.pop());
				}
			}
		}
		return res;
	}

}
//Largest Rectangle in Histogram
class Solution{
public:
	int largestRectangleArea(vector<int> &height){
		int res;
		for(int i;i<height.size();++i){
			if(i+1<heght.size() && height[i]<=heght[i+1]){
				continue;
			}
			int minH=height[i];
			for(int j=i;j>=0;--j){
				minH=min(minH,height[j]);
				int area=minH*(i-j+1);
				res=max(res,area);
			}
		}
		return res;
	}
}

//Evaluate Reverse Polish Notation
class Solution{
public:
	int EvaluateRPN(vector<string>& tokens){
		if(tokens.size()==1) stoi(tokens[0]);
		stack<int> st;
		for(int i=0;i<tokens.size();++i){
			if(tokens[i]!="+" && tokens[i]!="-" && tokens[i]!="*" && tokens[i]!="/"){
				st.push(stoi(tokens[i]));
			} 
			else{
				int num1=st.top();st.pop();
				int num2=st.top();st.pop();
				if(tokens[i]=="+") st.push(num2+num1);
				if(tokens[i]=="-") st.push(num2-num1);
				if(tokens[i]=="*") st.push(num2*num1);
				if(tokens[i]=="/") st.push(num2/num1);
			}
		}
		return st.top();
	}
}
//队列实现栈






//栈实现队列





//包含min函数的栈



//合法出栈序列


//数组中第K大的数



//寻找中位数