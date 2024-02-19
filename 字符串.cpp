//////////////////////////////////////////////////////////////////
///                                                            ///
///                          字符串                             ///
///                                                            ///
//////////////////////////////////////////////////////////////////
//valid palindrome
验证回文字符串是比较常见的问题，所谓回文，就是一个正读和反读都一样的字符串，
比如“level”或者“noon”等等就是回文串。但是这里，加入了空格和非字母数字的字符，
增加了些难度，但其实原理还是很简单：只需要建立两个指针，left和right, 
分别从字符的开头和结尾处开始遍历整个字符串，如果遇到非字母数字的字符就跳过，
继续往下找，直到找到下一个字母数字或者结束遍历，如果遇到大写字母，就将其转为小写。
等左右指针都找到字母数字时，比较这两个字符，若相等，则继续比较下面两个分别找到的字母数字，
若不相等，直接返回false. 
class Solution{
public:
	bool ispalindrome(string s){
		transform(s.begin,s.end)
	}
}

class Solution{
public:
	bool isPalindrome(string s){
		int left=0,right=s.size-1;
		while(left<right){
			if(!isAlphaNum(s[left]))
				++left;
			else if(!isAlphaNum(s[right]))
				--right;
			else if((s[left]+32-'a')%32 !=(s[right]+32-'a')%32)
				return false;
			else{
				++left;
				--right;
			}
		}
		return true;
	}
	bool isAlphaNum(char &ch){
		if(ch>='a'&&ch<='z') return true;
		if(ch>='A'&&ch<='Z') return true;
		if(ch>='0'&&ch<='9') return true;
		return false;
	}
}

//implement strStr()
strstr(str1,str2) 函数用于判断字符串str2是否是str1的子串。
如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL。

思路一：直接采用两层循环的暴力法来做，逐个比较每个字符haystack[i]和needle[0]，
如果对应字符有任何一个不相等，就跳过，继续比较haystack[i+1]，
如果对应字符相等就继续比较haystack[i+1]和needle[1]，一直比较到needle的最后节点，
如果needle[j]中的j等于needle的长度，说明找到了一个答案，直接返回i。
如果外层遍历完还没有找到答案就返回-1。

class Solution{
public:
	int strStr(const string& haystack,const string& needle){
		if(needle.empty()) return 0;

		const int N=haystack.size()-needle.size()+1;;
		for(int i=0;i<N;i++){
			int j=i;
			int k=0;
			while(j<haystack.size() && k<needle.size() && haystack[j]==needle[k]){
				j++;
				k++;
			}
			if(k=needle.size()) return i;
		}
		return -1;
	}
}

思路二：Knuth-Morris-Pratt算法,kmp,时间复杂度O(N+M)，空间复杂度O(M)
class Solution{
public:
	int strStr(const string& haystack,const string& needle){
		return kmp(haystack.c_str(),needle.c_str());
	}
private:
	static void compute_predix(const *pattern,int next[]){
		int i;
		int j=-1;
		const int m=strlen(pattern);
		next[0]=j;
		for(i=1;i<m;i++){
			while(j>-1 && pattern[j+1]!=pattern[i])
				j=next[j];
			if(pattern[i]==pattern[j+1])
				j++;
			next[i]=j;
		}
	}
	static int kmp(const *text,const char *pattern){
		int i;
		int j=-1;
		const int n=strlen(text);
		const int m=strlen(pattern);
		if(n==0 && m==0) 
			return 0;
		if(m==0)
			return0 0;
		int *next=(int*)malloc(sizeof(int)*m);

		compute_predix(pattern,next);

		for(i=0;i<n;i++){
			while(j>-1 && pattern[j+1]!=text[i])
				j=next[j];
			if(text[i]==pattern[j+1])
				j++;
			if(j==m-1){
				free(next);
				return i-j;
			}
		}
		free(next);
		return -1;
	}
}

//string to integer(atoi)
class Solution{
public:
	int myAtoi(const string &str){
		int num=0;
		int sign=1;
		const int n=str.length();
		int i=0;

		while(str[i]==' ' && i<n) 
			i++;
		if(str[i]=='+'){
			i++;
		}
		else if(str[i]=='-'){
			sign=-1;
			i++;
		}
		for (;i<n;i++){
			if(str[i]<'0' || str[i]>'9')
				break;
			if(num>INT_MAX/10 ||(num==INT_MAX/10 &&(str[i]-'0')>INT_MAX%10)){
				return sign=-1?INT_MIN:INT_MAX;
			}
			num=num*10+str[i]-'0';
		}
		return num*sign;
	}
}

//valid number
首先，从题目中给的一些例子可以分析出来，我们所需要关注的除了数字以外的特殊字符有空格 ‘ ’， 小数点 '.', 
自然数 'e/E', 还要加上正负号 '+/-"， 除了这些字符需要考虑意外，出现了任何其他的字符，可以马上判定不是数字。
下面我们来一一分析这些出现了也可能是数字的特殊字符：
1. 空格 ‘ ’： 空格分为两种情况需要考虑，一种是出现在开头和末尾的空格，一种是出现在中间的字符。
  出现在开头和末尾的空格不影响数字，而一旦中间出现了空格，则立马不是数字。解决方法：预处理时去掉字符的首位空格，
  中间再检测到空格，则判定不是数字。
2. 小数点 '.'：小数点需要分的情况较多，首先的是小数点只能出现一次，但是小数点可以出现在任何位置，
  开头(".3"), 中间("1.e2"), 以及结尾("1." ), 而且需要注意的是，小数点不能出现在自然数 'e/E' 之后，
  如 "1e.1" false, "1e1.1" false。还有，当小数点位于末尾时，前面必须是数字，如 "1."  true，" -." false。
  解决方法：开头中间结尾三个位置分开讨论情况。
3. 自然数 'e/E'：自然数的前后必须有数字，即自然数不能出现在开头和结尾，如 "e" false,  ".e1" false, "3.e" false, 
  "3.e1" true。而且小数点只能出现在自然数之前，还有就是自然数前面不能是符号，如 "+e1" false, "1+e" false. 
  解决方法：开头中间结尾三个位置分开讨论情况。
4. 正负号 '+/-"，正负号可以再开头出现，可以再自然数e之后出现，但不能是最后一个字符，后面得有数字，如  "+1.e+5" true。
  解决方法：开头中间结尾三个位置分开讨论情况。

下面我们开始正式分开头中间结尾三个位置来讨论情况：
1. 在讨论三个位置之前做预处理，去掉字符串首尾的空格，可以采用两个指针分别指向开头和结尾，遇到空格则跳过，
  分别指向开头结尾非空格的字符。
2. 对首字符处理，首字符只能为数字或者正负号 '+/-"，我们需要定义三个flag在标示我们是否之前检测到过小数点，
   自然数和正负号。首字符如为数字或正负号，则标记对应的flag，若不是，直接返回false。
3. 对中间字符的处理，中间字符会出现五种情况，数字，小数点，自然数，正负号和其他字符。
  若是数字，标记flag并通过。
  若是自然数，则必须是第一次出现自然数，并且前一个字符不能是正负号，而且之前一定要出现过数字，才能标记flag通过。
  若是正负号，则之前的字符必须是自然数e，才能标记flag通过。
  若是小数点，则必须是第一次出现小数点并且自然数没有出现过，才能标记flag通过。
  若是其他，返回false。
4. 对尾字符处理，最后一个字符只能是数字或小数点，其他字符都返回false。
  若是数字，返回true。
  若是小数点，则必须是第一次出现小数点并且自然数e没有出现过，还有前面必须是数字，才能返回true。
class Soultion{
public:
	bool isvaild(string s){
		int len=s.size();
		int left=0,right=len-1;
		bool eExisted=false;
		bool dotExisted=false;
		bool digitExisted=false;
		//如果字符串首尾有空格，删除它们
		while(s[left]==' ') ++left;
		while(s[right]==' ') --right;
		//如果字符串只有一个字符而且没有数字，返回false
		if(left>=right && (s[left]<'0' || s[left]>'9'))
			return false;
		//处理第一个字符
		if(s[left]=='.') 
			dotExisted=true;
		else if(s[left]>='0' && s[left]<='9')
			digitExisted=true;
		else if(s[left]!='+' && s[left]!='-')
			return false;
		//处理中间部分的字符
		for(int i=left+1;i<right-1;++i){
			if(s[i]>='0' && s[i]<='9')
				digitExisted=true;
			else if(s[i]=='e' || s[i]=='E'){  //e/E不能follw+/-，必须接上一个数字
				if(!eExisted && s[i-1]!='+' && s[i-1]!='-' && digitExisted)
					eExisted=true;
				else return false;
			}
			else if(s[i]=='+' || s[i]=='-'){  //+/-只能follow e/E
				if(s[i-1]!='e' && s[i-1]!='E')
					return false;
			}
			else if(s[i]=='.'){               //点只能出现一次且只能在e/E之后出现
				if(!dotExisted && !eExisted)
					dotExisted=true;
				else  return false;
			}
			else return false;
		}
		//Process the last char, it can only be digit or dot, when is dot, 
		//there should be no dot and e/E before and must follow a digit
		//处理最后一个字符，它只能是数字或者点，当它是点的时候...
		if(s[right]>='0' && s[right]<='9')
			return true;
		else if(s[right]=='.' && !dotExisted && !eExisted && digitExisted)
			return true;
		else return false;
	}
}

//Integer to roman
class Solution{
public:
	string integerToRoman(int num){
		const int radix[]={1000,900,500,400,100,90,50,40,10,9,5,4,1};
		const string symbol[]={"M","CM","D","CD","C","XC","L",
		                       "XL","X","IX","V","IV","I"};
		string roman;
		for(size_t i=0;num>0;++i){
			int count=num/radix[i];
			num%=radix[i];
			for(;count>0;--count)
				roman+=symbol[i];
		}
		return roman;
	}
}
//另一种写法
class Solution {
public:
    string intToRoman(int num) {
        string res = "";
        vector<int> val{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> str{"M", "CM", "D", "CD", "C", "XC", "L", 
                           "XL", "X", "IX", "V", "IV", "I"};
        for (int i = 0; i < val.size(); ++i) {
            while (num >= val[i]) {
                num -= val[i];
                res += str[i];
            }
        }
        return res;
    }
};

//Roman to Integer
我们也可以每次跟前面的数字比较，如果小于等于前面的数字，我们先加上当前的数字，比如 "VI"，
第二个字母 'I' 小于第一个字母 'V'，所以要加1。如果大于的前面的数字，我们加上当前的数字减去二倍前面的数字，
这样可以把在上一个循环多加数减掉，比如 "IX"，我们在 i=0 时，加上了第一个字母 'I' 的值，此时结果res为1。
当 i=1 时，我们发现字母 'X' 大于前一个字母 'I'，这说明前面的1是要减去的，而由于我们前一步不但没减，
还多加了个1，所以此时要减去2倍的1，就是减2，所以才能得到9，整个过程是 res = 1 + 10 - 2 = 9，
参见代码如下:

class Solution{
public:
	inline int map(const char c){
		switch(c){
			case 'I':return 1;
			case 'V':return 5;
			case 'X':return 10;
			case 'L':return 50;
			case 'C':return 100;
			case 'D':return 500;
			case 'M':return 1000;
			default:return 0;
		}
	}
	int romanToInt(const string& s){
		int result=0;
		for(size_t i=0;i<s.size;i++){
			if(i>0 && map(s[i])>map(s[i-1])){
				result+=(map(s[i])-2*map(s[i-1]));
			}
			else{
				result+=map(s[i]);
			}
		}
		return result;
	}
}

//

//count and say
class Solution{
public:
	string countAndSay(int n){
		string s("1");
		while(--n)
			s=getNext(s);
		return s;
	}
	string getNext(const string &s){
		stringstream ss;
		for(auto i=s.begin();i!=s.end();){
			auto j=find_if(i,s.end(),bind1st(not_equal_to<char>(),*i));
			ss<<distance(i,j)<<*i;
			i=j;
		}
		return ss.str();
	}
}
这道计数和读法问题还是第一次遇到，看似挺复杂，其实仔细一看，算法很简单，就是对于前一个数，
找出相同元素的个数，把个数和该元素存到新的string里。代码如下：
class Solution{
public:
	string countAndSay(int n){
		if(n<=0) return "";
		string res="1";
		while(--n){
			string cur="";
			for(int i=0;i<res.size();++i){
				int cnt=1;
				while(i+1<res.size() &&res[i]==res[i+1]){
					++cnt;
					++i;
				}
				cur+=to_string(cnt)+res[i];
			}
			res=cur;
		}
		return res;
	}
}

//Anagrams
class Solution{
public:
	vector<string> anagrams(vector<string> &strs){
		unordered_map<string,vector<string>> group;
		for(const auto &s:strs){
			atring key=s;
			sort(key.begin(),key.end());
			group[key].push_back(s);
		}
		vector<strings> result;
		for(auto it=group.cbegin();it!=group.cend();it++){
			if(it->second.size()>1)
				result.insert(result.end(),it->second.begin(),it->second.end())
		}
		return result;
	}

}
由于错位词重新排序后都会得到相同的字符串，我们以此作为key，将所有错位词都保存到字符串数组中，
建立key和字符串数组之间的映射，最后再存入结果res中即可，擦巾代码如下：
class Solution{
public:
	vector<string> anagrams(vector<string> &strs){
		vector<vector<string>> res;
		unordered_map<string,vector<string>> m;
		for(string str:strs){
			string t=str;
			sort(t.begin(),t.end());
			m[t].push_back(str);
		}
		for(auto a:m){
			res.push_back(a.second);
		}
		return res;
	}
}
//Simpplify Path
class Solution{
public:
	string SimpplifyPath(const stirngs& path){
		vector<string> dirs;

		for(auto i=path.begin();i!=path.end();){
			++i;
			auto j=find(i,path.end(),'/');
			auto dir=string(i,j);
			if(!dir.empty() && dir!="."){
				if(dir==".."){
					if(!dirs.empty())
						dirs.pop_back();
				}
				else
					dirs.push_back(dirs);
			}
			i=j;
		}
		stringstream out;
		if(dirs.empty()){
			out<<"/";
		}
		else{
			for(auto dir:dirs)
				out<<'/'<<dirs;
		}
		return out.str();
	}
}

这道题让简化给定的路径，光根据题目中给的那一个例子还真不太好总结出规律，应该再加上两个例子
 path = "/a/./b/../c/", => "/a/c"和path = "/a/./b/c/", => "/a/b/c"， 
 这样我们就可以知道中间是"."的情况直接去掉，是".."时删掉它上面挨着的一个路径，
 而下面的边界条件给的一些情况中可以得知，如果是空的话返回"/"，如果有多个"/"只保留一个。
 那么我们可以把路径看做是由一个或多个"/"分割开的众多子字符串，把它们分别提取出来一一处理即可.
 代码如下：

class Solution{
public:
	string SimpplifyPath(string path){
		vector<string> v;
		int i=0;
		while(i<path.size()){
			while(path[i]=='/' && i<path.size())
				++i;
			if(i==path.size())
				break;
			int start=i;
			while(path[i]!='/' && i<path.size())
				++i;
			int end=i-1;
			string s=path.substr(start,end-start+1);
			if(s==".."){
				if(!v.empty()) v.pop_back();

			}
			else if(s!="."){
				v.push_back(s);
			}
		}
		if(v.empty()) 
			return "/";
		string res;
		for(int i=0;i<v.size();++i){
			res+='/'+v[i];
		}
		return res;
	}
}





//length of last word
class Solution{
public:
	int lengthOfLastWord(string s){
		int count=0;
		int len=strlen(s);
		int left=0;
		int right=len-1;
		while(s[left]==' ') ++left;
		while(s[right]==' ') --right;
		for(int i=left;i<=right;i++){
			if(s[i]==' ') count=0;
			else ++count;
		}
		return count;
	}
}

class Solution {
public:
	int lengthOfLastWord(const string& s) {
		return lengthOfLastWord(s.c_str());
	}
private:
	int lengthOfLastWord(const char *s) {
		int len = 0;
		while (*s) {
			if (*s++ != ' ')
				++len;
			else if (*s && *s != ' ')
				len = 0;
		}
		return len;
	}
};