1.字符串最后一个单词的长度
2.计算字符个数
3.明明的随机数
4.字符串分隔
5.进制转换
6.质数因子
7.取近似值
8.合并表记录
9.提取不重复整数
10.字符个数统计
11.数字颠倒
12.字符串翻转
13.句子逆序
14.字串的连接最长路径查找
15.求int型正整数在内存中存储时1的个数
16.购物单
17.坐标移动
18.识别有效的IP地址和掩码并进行分类统计
19.简单错误记录
20.密码验证合格程序
===================================================================
1.字符串最后一个单词的长度
一段英文字符串中最后一个单词的长度。 题目比较简单，做法有很多： 比如， 
可以放到stringstream里面split，拿到最后一个单词 也可以从后往前数到第一个空格为止。
让我觉得麻烦是第一次做这种要自己写输入的题， 
C++用cin是遇到空格停止的，因此要用getline读入一行
#include <iostream>
#include <string>
using namespace std;
int main(){
	string str;
	getline(cin,str);
	int i=str.size()-1;
	int count=0;
	while(str[i]!=' ' && i>0){
		++count;
		--i;
	}
	cout<<count<<endl;
	return 0;
}
=================================================================
2.计算字符个数
输入一个字符串和一个字符，统计该字符在该字符串中出现的次数。 
for循环比较即可，没什么好说的
#include <iostream>
#include <string>
using namespace std;
int main(int argc,char**argv){
	string str;
	char c;
	getline(cin,str);
	int count=0;
	cin>>c;
	int l=str.size();
	for(int i=0;i<l;i++){
		if(tolower(str[i])==tolower(c)) count++;
	}
	cout<<count<<endl;
	return 0;
}
==================================================================
3.明明的随机数
说是随机数，其实跟随机数没有半毛钱关系， 
就是输入一串整数，整数去重，输出排好序的结果， 
C++使用std::sort、std::unique、vector::erase可以轻易做到
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
int main(){
	int n;
	while(cin>>n){
		vector<int> v;
		v.reserve(1024);
		int j;
		for(int i=0;i<n;++i){
			cin>>j;
			v.push_back(j);
		}
		sort(v.begin(),v.end());
		v.erase(unique(v.begin(),v.end()),v,end());
		if(v.capacity()<1024)
			vector<int>(v).swap(v);
		for(int i=0;i<v,size();++i)
			cout<<v[i]<<endl;
	}
	return 0;
}
========================================================================
4.字符串分隔
给定一个字符串，对其等距（长度8）分隔，最后不足的补0 
例如，123456789将分割成:12345678和90000000

方法也很多，比如可以用string::substr，考虑到最后如果不足8个字符，需要补0， 
这里我先创建一个00000000然后用std::copy来做

#include<iostream>
#include<string>
using namespace std;

int main(){
    string str1;
    string str2;
    cin>>str1>>str2;
    
    for(int i=0;i<str1.size();i+=8){
        string output("00000000");
        int l=(i+8)<str1.size()?8:(str1.size()-i);
        std::copy(str1.begin()+i,str1.begin()+i+l,output.begin());
        cout<<output<<endl;
    }
    for(int i=0;i<str2.size();i+=8){
        string output("00000000");
        int l=(i+8)<str2.size()?8:(str2.size()-i);
        std::copy(str2.begin()+i,str2.begin()+i+l,output.begin());
        cout<<output<<endl;
    }
    return 0;
}

=============================================================
5.进制转换
16进制转成10进制，基础题没啥好说的， 
做一个map把0~F映射进去，比较方便，或者写个if-else判断当前字符是数字还是字母
#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
using namespace std;
int main(){
	unordered_map<char,int> mmap;
	mmap['0']=0;
	mmap['1']=1;
	mmap['2']=2;
	mmap['3']=3;
	mmap['4']=4;
	mmap['5']=5;
	mmap['6']=6;
	mmap['7']=7;
	mmap['8']=8;
	mmap['9']=9;
	mmap['a']=10;
	mmap['A']=10;
	mmap['b']=11;
	mmap['B']=11;
	mmap['c']=12;
	mmap['C']=12;
	mmap['d']=13;
	mmap['D']=13;
	mmap['e']=14;
	mmap['E']=14;
	mmap['f']=15;
	mmap['F']=15;
	string str;
	while(cin>>str){
		str=str.substr(2);
		long sum=0;
		for(int i=0;i<str.size();++i){
			sum*=16;
			sum+=mmap[str[i]];
		}
		cout<<sum<<endl;
	}
	return 0;
}
=========================================================================
6.质数因子
不知道有没有更高端的方法，我的理解就是，对于一个数来说，比如180 从2开始遍历，
如果能被2整除，那么180/=2，并且输出2，之后再拿90重复上述操作,直到变成1为止
#include <iostream>
#include <cmath>
using namespace std;
int main(){
	long input;
	while(cin>>input){
		while(input>static_cast<int>(1)){
			for(int i=2;i<=input;++i){
				if(input%i==0){
					input/=i;
					cout<<i<<" ";
					break;
				}
			}
		}
		cout<<endl;
	}
	return 0;
}

另一种做法
#include <iostream>
using namespace std;
int main()
{
    long num;
    cin>>num;    
    for(int i=2;i<=num;)
    {
        if(num%i==0)
        {
            cout<<i<<" ";
            num/=i;
        }
        else i++;
    }
    return 0;
}
=========================================================================
7.取近似值
输出一个浮点数四舍五入的值，C++标准库也有round``floor``ceil这样的函数， 
我的办法比较土，转成string以后提出小数点第一位然后再判断：
#include <iostream>
using namespace std;
int main(){
	double f;
	while(cin>>f){
		string str(std::to_string(f));
		int pos=str.find('.');
		int v1=std::stoi(str.substr(0,pos));
		int v2=str[pos+1]-'0';
		cout<<(v2>4?(v1+1):v1)<<endl;
	}
	return 0;
}
=======================================================================
8.合并表记录
这题不复杂，就是麻烦，大概意思就是输入(key-value)对， key相同的要合并，
合并就是将value加起来，最后将这些(key-value)对升序排行.我的做法定义一个结构体，
然后重写operator==和std::sort的比较函数，实际上定义一个unordered_map<int,int>
会更简单吧。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct pair_{
	int key;
	int value;

	bool operator==(const struct pair_&x){
		return x.key==this->key;
	}
};
typedef vector<pair_> Pairs;
class comp{
public:
	bool operator()(const pair_&a,const pair_&b){
		return a.key<b.key;
	}
};
int main(int argc,char**argv){
	int N;
	Pairs pairs;
	pairs.reserve(1024);
	while(cin>>N){
		Pairs::iterator it;
		for(int i=0;i<N;++i){
			pair_ tmp;
			cin>>tmp.key>>tmp.value;
//#if 1
			if((it=find(pairs.begin(),pairs.end(),tmp))!=pairs.end())
				it->value+=tmp.value;
			else
				pairs.push_back(tmp);
//#endif
		}
		sort(pairs.begin(),pairs.end(),comp());
		for(int i=0;i<pairs.size();++i){
			cout<<pairs[i].key<<" "<<pairs[i].value<<endl;
		}
	}
	return 0;
}
================================================================
9.提取不重复整数
简单粗暴的做法，定义一个unordered_set把出现过的放进去,从后往前迭代一次就可以了
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main(){
	int n;
	while(cin>>n){
		string str=to_string(n);
		unordered_set<char> s;
		int sum=0;
		for(int i=str.size()-1;i>=0;--i){
			if(s.find(str[i])==s.end()){
				sum*=10;
				sum+=(str[i]-'0');
				s.insert(str[i]);
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}

==================================================================
10.字符个数统计
统计ACSII码范围（0-127）的字符，重复的字符只统计一次,比如aaa只统计为1
我的做法依然简单粗暴，用一个unordered_set,其实只需要一个127大小的char数组，
出现就赋值1，最后统计即可
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main(){
	string str;
	unordered_set<char> s;
	getline(cin,str);   //std::getline(cin,str);
	int count=0;
	for(int i=0;i<str.size();++i){
		if(str[i]<128 && str[i]>=0){
			if(s.find(str[i])==s.end()){
				++count;
				s.insert(str[i]);
			}
		}
	}
	cout<<count<<endl;
	return 0;
}

==================================================================
11.数字颠倒
颠倒就是逆序，可以把数字to_string一下然后再reserve,按数字的方式处理，模10除10
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n;
	while(cin>>n){
		string str;
		while(n){
			str+=to_string(n%10);
			n/=10;
		}
		cout<<str<<endl;
	}
	return 0;
}

=======================================================================
12.字符串翻转
利用STL逆向迭代器和构造函数搞定
#include <iostream>
#include <string>
using namespace std;

int main(){
	string n;
	while(getline(cin,n)){
		string str(n.rbegin(),n.rend());  //为啥用rbegin和rend
		cout<<str<<endl;
	}
	return 0;
}
======================================================================
13.句子逆序
"hello world"变成"world hello" 
这个要逆转两次，先对整个句子进行逆序 
"dlrow olleh" 
再逐个单词逆序 
"world hello"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main(){
	string line;
	while(getline(cin,line)){
		string tmp(line.rbegin(),line.rend());
		stringstream ss(tmp);
		string word;
		vector<string> words;
		while(ss>>word){
			words.push_back(string(word.rbegin(),word.rend()));
			words.push_back(" ");
		}
		for(int i=0;i<words.size();++i){
			if(i==words.size()-1)
				words[i].pop_back();
			cout<<words[i];
		}
		cout<<endl;
	}
	return 0;
}

=======================================================================
14.字串的连接最长路径查找
看完题目才知道是字符串字典序排序，直接上std::sort也行 
不过我用了优先级队列，这样的话复杂度应该低一些,std::priority_queue需要注意的是模板参数
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int main(){
	int n;
	priority_queue<string,vector<string>,greater<string>> q;
	string str;
	while(cin>>n){
		for(int i=0;i<n;++i){
			cin>>str;
			q.push(str);
		}
		while(!q.empty()){
			cout<<q.top()<<endl;
			q.pop();
		}
	}
	return 0;
}

========================================================================
15.求int型正整数在内存中存储时1的个数
剑指offer上的题，有一个小小的trick吧，当然直接按位比较也行的
#include <iostream>
using namespace std;

int main(){
	int n;
	while(cin>>n){
		int count=0;
		while(n){
			n&=(n-1);
			++count;
		}
		cout<<count<<endl;
	}
}

========================================================================
16.购物单
这应该是前20题里面最耗费我时间的一题了。 
改进的0-1背包，先回顾一下0-1背包： 最朴素的0-1背包问题里面，只有拿和不拿两个选项 
因此动规方程可以如下写： 
dp(i,j)=max(dp(i−1,j),dp(i−1,j−w(i))+v(i))
其中dp(i,j)dp(i,j)表示在前i件物品，在j容量的前提下可以获得的最大价值 
w(i)表示第i件物品的容量,v(i)表示第i件物品的价值
这题复杂在于要分情况讨论（主组件还是次要组件）,然后套一下0-1背包即可
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int n,m;
	while(cin>>n>>m){
		vector<int> v(m+1);//value
		vector<int> p(m+1);//importance
		vector<int> q(m+1);//major or minor
		vector<vector<int>> dp(m+1,vector<int>(n+1));//dp
        //input
		for(int i=1;i<=m;++i)
			cin>>v[i]>>p[i]>>q[i];
		for(int i=1;i<=m;++i){
			for(int j=1;j<=n;++j){
				if(!q[i]){  //major
					if(v[i]<=j)
						dp[i][j]=max(dp[i-1][j],dp[i-1][j-v[i]]+v[i]*p[i]);
				}
				else{       //minor
					if(v[i]+v[q[i]]<=j)
						dp[i][j]=max(dp[i-1][j],dp[i-1][j-v[i]]+v[i]*p[i]);
				}
			}			
		}  //end for
		cout<<dp[m][n]<<endl;
	}
}

========================================================================
17.坐标移动
坐标移动有几个要素： 
1.将输入的数据分割成一个个的命令，可以用stringstream 
2.判断每个命令是否合法 
3.对命令进行编码（方向和移动的数值）
本题的坑在于不要盲目使用std::stoi，比如说遇到A10A这样的非法输入， 
std::stoi会尽可能的转换，也就是说stoi("10A")将得到10，因此，
使用时需要判断，stoi是否全部转换：
size_t index=0;
auto res=std::stoi(response,&index);
if(index==response.size())
	op=res;
else
	return false;

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool is_valid(string s,int& op,int &pointer){
	if(s.size()<2 || s.size()>3)
		return false;
	char point=s[0];
	if(point!='W' && point!='S' && point!='A' && point!='D')
		return false;
	else if(point=='W')
		pointer=2;
	else if(point=='A')
		pointer=0;
	else if(point=='S')
		pointer=3;
	else  //D
		pointer=1;

	string response=s.substr(1);
	size_t index=0;
	auto res=std::stoi(response,&index);
	if(index==response.size())
		op=res;
	else
		return false;
	return true;
}

int main(int argc, char **argv){
	string input;
	while(getline(cin,input)){
		stringstream ss(input);
		vector<string> steps;
		int x=0;
		int y=0;
		while(ss.good()){
			string step;
			int op=-1;
			int pointer=-1;
			getline(ss,step,';');
			if(is_valid(step,op,pointer)){
				if(pointer==0)
					x-=op;
				else if(pointer==1)
					x+=op;
				else if (pointer==2)
					y+=op;
				else
					y-=op;
			}
		}
		cout<<x<<','<<y<<endl;
	}
	return 0;
}

=========================================================================
18.识别有效的IP地址和掩码并进行分类统计
这题可以说是相当麻烦了，以至于我拿出了我压箱底的网络编程的技能。
每组数据表示一个IP和mask，比如192.168.1.1~255.255.255.0
题目要求堆这一组数据进行分类： A、B、C、D、E、不合法的IP或者mask、私有IP
几个要考虑的地方： 
1.判断IP和mask是否合法直接交给inet_pton了，这里只是从物理角度判断是否合法。
  排除类似192.1..1或者255…这种情况
2.判断mask是否合法，mask有个特点就是高地址全为1，低地址都是0，例如
  11111111000000000000000000000000 
  网上有人通过计算出二进制形式再去判断是挺麻烦的，我有更好的办法： 
  对于一个mask来说，判断是否为合法的mask，可以这样做： 
  a. 取反 tmp=~mask 
  b. 取反+1 tmp2=tmp+1 
  c. 相与，如果为0，则说明mask合法 
  这个算法很容易验证。
3.在使用socket函数注意大小端存储问题
4.只有mask和ip都合法之后，才能统计ip的类型，这是个体力活，一堆if-else
5.一个IP既可以是A类也可以是private
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

bool judgemask(string mask,vector<int>&result){
	struct sockaddr_in ss;
	{
		
	};
}



=========================================================================
19.简单错误记录
题目的几个描述： 
1.记录最多8条记录，意思就是，如果有很多错误记录，只打印最后8条
2.输出的时候如果文件名超过16个字符则只要16个字符
3.输入的文件名有路径，输出不带路径
另外只比较文件名，不考虑路径，也就是/tmp/zx.c和/opt/zx.c认为是同一个文件

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

struct record{
	string num;
	string file;
	mutable int count;
	record(string n,string f):num(n),file(f),count(1){}
};

bool operator==(const struct record & X,const struct record & Y){
	return (Y.num==X.num) && (Y.file==X.file);
}

bool operator!=(const struct record & X,const struct record & Y){
	return !(X==Y);
}

string getFileName(const string &input){
	std::size_t found=input.find_last_of("/\\");
	string file=input.substr(found+1);

	if(file.size()>16)
		file=file.substr(file.size()-16);
	return file;
}

void outFile(string &file){
	if(file.size()>16)
		file=file.substr(file.size()-16);
}

int main(int argc,char **argv){
	string input1;
	string input2;
	vector<record> records;
	while(cin>>input1>>input2){
		string file=getFileName(input1);
		struct record r(input2,getFileName(input1));
		auto it=find(records.begin(),records.end(),r);
		if(it!=records.end())
			it->count++;
		else
			records.push_back(r);
	}
	int idx=(records.size()>8)?(records.size()-8):0;
	for(int i=idx;i<records.size();++i){
		outFile(records[i].file);
		cout<<records[i].file<<" "<<records[i].num<<" "<<records[i].count<<endl;
	}
	return 0;
}

======================================================================
20.密码验证合格程序
三个条件，前两个简单，第三个的意思就是,如果字符串中有重复子串，那么他们重复的数目不能超过2 
也就是说"abcxxxabc"这样的字符是不合法的
第三个条件我的做法比较蠢，从0开始每次挑长度为3的子串，然后在剩下的部分查找子串，复杂度比较高，
网上看到有正则表达式的解法，不是很熟。

#include <iostream>
#include <string>
using namespace std;

bool condition1(const string& s){
	if(s.size()>8)
		return true;
	else
		return false;
}

bool condition2(const string& s){
	int upper=0;
	int lower=0;
	int digit=0;
	int symbol=0;
	int cnt=0;
	for(int i=0;i<s.size();++i){
		if(s[i]>='0' && s[i]<='9')
			digit=1;
		else if(s[i]>='a' && s[i]<='z')
			lower=1;
		else if(s[i]>='A' && s[i]<='Z')
			upper=1;
		else
			symbol=1;
	}
	cnt=upper+lower+digit+symbol;
	return cnt>2?true:false;
}

bool condition3(const string& s){
	for(int i=0;i<s.size()-2;++i){
		string tmp=s.substr(i,3);
		string ss=s.substr(i+1);
		if(ss.find(tmp)!=string::npos)
			return false;
	}
	return true;
}

int main(){
	string s;
	while(cin>>s){
		if(condition1(s) && condition2(s) && condition3(s))
			cout<<"OK"<<endl;
		else
			cout<<"NG"<<endl;
	}
	return 0;
}



