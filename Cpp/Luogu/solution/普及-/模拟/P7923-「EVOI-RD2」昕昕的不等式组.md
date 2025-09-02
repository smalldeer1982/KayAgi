# 「EVOI-RD2」昕昕的不等式组

## 题目描述

昕昕做到了一道解一元一次不等式组的数学题。

这个一元一次不等式组共有 $n$ 个一元一次不等式。她分别求出了每个不等式的解集，而她需要把它们合并为该不等式组的解集。

每个不等式解集都化简为了最简形式，都形如 $x<t_i$（或 $x>t_i$ 等），其中 $t_i$ 为常数项，$x$ 为未知数。未知数为一个小写英文字母，会在不等号左侧；常数项为一个整数，会在不等号右侧。

所有不等式使用的不等号只有 $<,>,\le,\ge$ 四种。在本题的输入输出中，$\le$ 和 $\ge$ 则分别用 $<=$ 和 $>=$ 代替。

现在昕昕需要你求出该不等式组的解集。

## 说明/提示

**【样例 $1$ 说明】**

如图，为数轴上各个不等式解集的公共部分，即为该不等式组的解集，$-3 < x \le 1$。注意 $\le$ 在输出中用 $<=$ 替换。

![](https://cdn.luogu.com.cn/upload/image_hosting/i9de5dub.png)

**【数据规模与约定】**

**本题采用捆绑测试。** 

+ Subtask 1（5 pts）：$n=1$。
+ Subtask 2（25 pts）：$n=2$。
+ Subtask 3（10 pts）：$n \le 3$，$-4 \times 10^4 \le t_i \le 4 \times 10^4$。
+ Subtask 4（20 pts）：$n \le 10^4$，$-10^5 \le t_i \le 10^5$。
+ Subtask 5（10 pts）：$n \le 2 \times 10^4$。
+ Subtask 6（20 pts）：$n \le 5 \times 10^4$。
+ Subtask 7（10 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 6 \times 10^4$，$-10^6 \le t_i \le 10^6$，每个不等式中的未知数都是一个小写英文字母。

**【提示】**

以下为涉及到题目的一些数学知识。

+ 不等式：用不等号联系的关系式。  
+ 不等式的解：在含有未知数的不等式中，能使不等式成立的未知数的值。  
+ 不等式的解集：不等式的解的全体。   
+ 不等式组的解集：不等式组中所有不等式的解集的公共部分。  
+ 解不等式组：求不等式组的解集的过程。

## 样例 #1

### 输入

```
2 x
x>-3
x<=1```

### 输出

```
-3<x<=1```

## 样例 #2

### 输入

```
3 y
y>=5
y>4
y>=-2```

### 输出

```
y>=5```

## 样例 #3

### 输入

```
4 q
q>=114514
q>-200810
q<-1022
q<=-23333```

### 输出

```
No Answer!```

# 题解

## 作者：昒昕 (赞：9)

凉心出题人，模拟，给出每个不等式的解集，让你求出这个不等式组的解集。

需要用四个变量，$lt,le,gt,ge$ ，分别存储小于号的常数项最小值，小于等于号的常数项最小值，以此类推。

最后输出的时候，按照格式输出即可。因为前面已经将每个符号的最小或最大值存储了，所以直接按照该数对应的符号输出即可。

最重要的是，记得特判输出等号的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e5+5,inf=1e9+5;

string s;
int n;
char ch;

int main()
{
//	freopen ( "equation.in" , "r" , stdin ) ;
//	freopen ( "equation.out" , "w" , stdout ) ;
	cin>>n>>ch; //ch其实在本做法中没用
	int lt=inf,le=inf,gt=-inf,ge=-inf; // with the meaning of Latex
   //lt:<  le:<=  gt:>  ge:>=
	
	for (int i=1;i<=n;i++) {
		cin>>s; //读入该行的不等式
		if(s[2]=='='){ //s.size() always >= 3
			int x=atoi(s.substr(3,s.size()-3).c_str()); //字符串转数字
			if(s[1]=='<') le=min(le,x); //小于等于
			else ge=max(ge,x); //大于等于 s[1]=='>'
		} else{
			int x=atoi(s.substr(2,s.size()-2).c_str());
			if(s[1]=='<') lt=min(lt,x); //小于
			else gt=max(gt,x); //大于 s[1]=='>'
		}
	}
	
	int l,l0,g,g0;
   //l代表小于或小于等于的最小值
   //g代表大于或大于等于的最大值
	
	if(lt<=le) {l=lt;l0=0;} // <
	else {l=le;l0=1;} // <=
	if(gt>=ge) {g=gt;g0=0;} // >
	else {g=ge;g0=1;} // >=
	
	// g op ch op l
	
	if(l<g){ //未知数左边的数比右边的数还大
		puts("No Answer!"); //无解
	} else if(l==g){ //特判等号情况
		if(l0==0||g0==0) puts("No Answer!"); //有小于号或大于号的情况
		else printf("%c=%d\n",ch,l); //ch>=x&&ch<=x，输出的是ch=x
	} else{
		if(g>-inf&&l<inf){ //a op1 x op2 b的情况
			cout<<g; //最左侧的常数项，也就是小于或小于等于储存的数
            
			if(g0==0) cout<<"<"; //小于号
			else cout<<"<=";
            
			cout<<ch; //未知数
            
			if(l0==0) cout<<"<";
			else cout<<"<=";
            
			cout<<l<<endl; //最右侧常数
		} else if(l<inf){ //大于或大于等于
      	  //存储的是 a > or >= x的情况，但输出规定要把未知数放左侧，所以需要把符号翻转为 < or <= 
			cout<<ch;
			
			if(l0==0) cout<<"<";
			else cout<<"<="; //a < or <= x
			
			cout<<l<<endl;
		} else{ // g>-inf，同上，因未知数需放在左侧，所以也需将符号翻转
			cout<<ch;
			
			if(g0==0) cout<<">";
			else cout<<">="; //a > or >= x
			
			cout<<g<<endl;
		}
	}
	return 0;
}

```

---

## 作者：whatismyname0 (赞：8)

这道橙模拟通过率出奇的低，可能说明大家对于细节的处理有一定疏漏。

![](https://cdn.luogu.com.cn/upload/image_hosting/kzzpwq15.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

先来读题，这是一道模拟题，要给你 $n$ 个关于 $x$ 的最简不等式，求出它们的交集并用最简不等式的形式输出。

我们用一个结构体 $ine$ 来存储不等式的信息：
```cpp
struct ine
{
	int val;//不等式右侧常数的值
	bool isg;//符号是否为>或≥
	bool eq;//符号是否为≥或≤
};
```
并且定义一个 $ine$ 类型的并以 $val$ 为关键字的结构体优先队列，比较函数部分代码如下：
```cpp
struct cmp
{
	bool operator()(ine x,ine y)
	{
		if (x.val!=y.val)return x.val>y.val;
		//下面是常数相等时的情况
		if (x.isg!=y.isg)return !x.isg;//>、≥排在<、≤前
		if (x.isg)return !x.eq;//≥排在>前
		return x.eq;//<排在≤前
	}
};
```
这样我们可以保证在分析不等关系时从队头抽取不等关系改变永远不会使原先确定的交集边界产生错误，并保证上界条件与第一次出现的小于（等于）关系条件相同。

再定义几个用于描述交集的变量：
```cpp
int sval;//交集下界
int gval;//交集上界
bool seq;//下界是否能取等
bool geq;//上界是否能取等
```

然后我们在主程序中每次取出优先队列队头的不等关系并分情况讨论，伪代码如下（个人认为伪代码比自然语言讲解更有条理）：
```plain
if 是小于关系 且 未出现过小于关系
	上界条件=当前不等关系条件
            
if 出现过小于关系 且 当前是大于（等于）关系
	输出 "No Answer!" 并结束程序
    
if 当前是大于关系 且 未出现过小于关系
	下界条件=当前不等关系条件
```
由于我们前面对每个关系排序的第一关键字是 $val$，~~而老师又教过我们大大小小解没了~~，所以易知若有任何大于关系在优先队列中排在小于关系后面就一定无解。

而输出时也要分情况讨论，伪代码如下：
```plain
if sval==gval
{
	if seq==geq==1
		输出 x=sval 并结束程序
	else
		输出 "No Answer!" 并结束程序
}

if 上界无限定条件
	输出 x>(≥)sval 并结束程序
    
if 下界无限定条件
	输出 x<(≤)gval 并结束程序
    
其他情况
	输出 sval<(≤)x<(≤)gval 并结束程序
```

这样就喜提AC了。模拟题最重要的是细节和各种状况的处理，一定要仔细考虑所有的状况如何处理、所有的细节如何判断。另外一些模拟题的输入和（或）输出也很难缠。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct ine
{
	int val;
	bool isg,eq;
};
struct cmp
{
	bool operator()(ine x,ine y)
	{
		if (x.val!=y.val)return x.val>y.val;
		if (x.isg!=y.isg)return !x.isg;
		if (x.isg)return !x.eq;
		return x.eq;
	}
};
priority_queue<ine,vector<ine>,cmp >q;
int n,sval,gval;
bool seq,geq;
char c;
string s;
int main()
{
	cin>>n>>c;
	for (int i=0;i<n;i++)
	{
		ine t;
		t.val=0;
		cin>>s;
		int sz=s.size(),now=2;
		bool negative=0;
		if (s[1]=='>')t.isg=1;
		else t.isg=0;
		if (s[2]=='=')
		{
			t.eq=1;
			now=3;
		}
		else t.eq=0;
		if (s[now]=='-')
		{
			now++;
			negative=1;
		}
		for (;now<sz;now++)t.val=t.val*10+s[now]-'0';
		if (negative)t.val*=-1;
		q.push(t);
	}
	bool smaller=0,isg=0;
	while (!q.empty())
	{
		ine t=q.top();
		q.pop();
		if (!t.isg)
		{
			if (!smaller)
			{
				if (t.eq)geq=1;
				gval=t.val;
			}
			smaller=1;
		}
		else if (smaller)
		{
			cout<<"No Answer!";
			return 0;
		}
		else
		{
			isg=1;
			if (t.eq)seq=1;
			else seq=0;
			sval=t.val;
		}
	}
	if (sval==gval)
	{
		if (seq&&geq)cout<<c<<'='<<sval;
		else cout<<"No Answer!";
		return 0;
	}
	if (!isg)
	{
		cout<<c<<'<';
		if (geq)cout<<'=';
		cout<<gval;
		return 0;
	}
	if (!smaller)
	{
		cout<<c<<'>';
		if (seq)cout<<'=';
		cout<<sval;
		return 0;
	}
	cout<<sval<<'<';
	if (seq)cout<<'=';
	cout<<c;
	cout<<'<';
	if (geq)cout<<'=';
	cout<<gval;
}
```
推荐模拟题：[P4711 「化学」相对分子质量](https://www.luogu.com.cn/problem/P4711)、[P1928 外星密码](https://www.luogu.com.cn/problem/P1928)

---

## 作者：__凉皮__ (赞：5)

~~貌似是本题代码**最短**题解。~~

废话不多说，先从**不等式**讲起：

**同大取大，同小取小，优先选择不带等于的。**

如：
```
x>2
x>1
x>=2
同为大于，取最大值，若相同则优先取不带等于的，则x>2。
x<=5
x<3
x<8
同为小于，取最小值，则x<3
```
接下来就是**代码实现**部分：

首先，我们定义四个变量：
```cpp
int s=-1e7;//x的最小值
int sd=-1e7;//x的最小值(含等于)
int b=1e7;//x的最大值
int bd=1e7;//x的最大值(含等于) 
则s<x<b,sd<=x<=bd
```
接下来对输入的不等式进行处理，分别求出以上4个变量。
```cpp
int si(string a){//注意负号的处理
	int num=0;
	for(int i=0;i<a.length();i++)if(a[i]!='-')num*=10,num+=a[i]-'0';
	if(a[0]=='-')num=-num;
	return num;
}
cin>>str;
if(str[1]=='>'){
	if(str[2]=='=')sd=max(sd,si(str.substr(3)));
	else s=max(s,si(str.substr(2)));
}
else{
	if(str[2]=='=')bd=min(bd,si(str.substr(3)));
	else b=min(b,si(str.substr(2)));
}
//str.substr(3)为获得字符串从位置3到最后的字符串。
//如str="x>=123"，则str.substr(3)获得的字符串为"123"。
```
最后就是**分情况讨论**进行输出：
```cpp
string fs="",fb="";//由于char貌似不能赋值为空，就用了string...
if(sd>s)s=sd,fs='='; if(bd<b)b=bd,fb='=';
//最后确认最大值与最小值，以及是否带等号。
if(s>b||s==b&&(!fs[0]||!fb[0])){cout<<"No Answer!";return 0;}
//如果最小值比最大值还大，自然得输出No Answer；
//而当最大值等于最小值时，有且只有一种情况满足条件：s<=x<=b。
if(s==b)cout<<c<<"="<<s;//注意，当s<=x<=b时，应输出x=s或x=b。
else if(s==-1e7)cout<<c<<'<'<<fb<<b;//如果输入的不等式中没有>,>=。
else if(b==1e7)cout<<c<<'>'<<fs<<s;//如果输入的不等式中没有<,<=。
else cout<<s<<'<'<<fs<<c<<'<'<<fb<<b;
```
###  _Code_ （码风清奇+压行）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int si(string a){
	int num=0;
	for(int i=0;i<a.length();i++)if(a[i]!='-')num*=10,num+=a[i]-'0';
	if(a[0]=='-')num=-num;
	return num;
}
int main(){
	int n;
	int s=-1e7,sd=-1e7,b=1e7,bd=1e7;
	char c;
	string str,fs="",fb="";
	cin>>n>>c;
	while(n--){
		cin>>str;
		if(str[1]=='>'){
			if(str[2]=='=')sd=max(sd,si(str.substr(3)));
			else s=max(s,si(str.substr(2)));
		}
		else{
			if(str[2]=='=')bd=min(bd,si(str.substr(3)));
			else b=min(b,si(str.substr(2)));
		}
	}
	if(sd>s)s=sd,fs='='; if(bd<b)b=bd,fb='=';
	if(s>b||s==b&&(!fs[0]||!fb[0])){cout<<"No Answer!";return 0;}
	if(s==b)cout<<c<<"="<<s;
    else if(s==-1e7)cout<<c<<'<'<<fb<<b;
    else if(b==1e7)cout<<c<<'>'<<fs<<s;
    else cout<<s<<'<'<<fs<<c<<'<'<<fb<<b;
	return 0;
}
```
 _**In the end:**_ 
 
**NOIP 2021 RP++ ！！！**

---

## 作者：封禁用户 (赞：3)

[这道题目](https://www.luogu.com.cn/problem/P7923)作为比赛的T1还算比较简单，赞美良心出题人(但是仍然有不少坑点，我在比赛[交了4发才过......](https://www.luogu.com.cn/record/list?user=334146&pid=P7923&page=1))。

这道题直接模拟即可，可以用初中的[数轴](https://baike.baidu.com/item/数轴/10021993)来理解[本题](https://www.luogu.com.cn/problem/P7923)，具体内容见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int zuo = -1e7, you = 1e7;//
bool deng1 = false, deng2 = false;
int num;
char x;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);//用来加速 cin 和 cout 的速度
  cin >> num >> x;//输入 num 个已化简的一元一次不等式和一个小写英文字母
  while (num--) {
    string str;
    cin >> str;//用字符串输入已化简的一元一次不等式
               //第一个字符为一个小写英文字母，所以从第二个字符串判断
    if (str[1] == '>') {//如果第二个字符为大于号
      if (str[2] == '=') {//如果第三个字符为等于号（即可以取到等）
        if (str[3] == '-') {//如果解集为负数
          int zhuan = 0;
          for (int i = 4; i < str.size(); i++)//从第五个字符开始转换
            zhuan = zhuan * 10 + str[i] - '0';
          zhuan *= -1;//因为解集为负数，所以乘上 -1 变号
          if (zhuan > zuo) {//更新大于解集范围
            zuo = zhuan;//更新左端点取值
            deng1 = true;//标记能取等
          }
        } else {//解集范围不为负数
          int zhuan = 0;
          for (int i = 3; i < str.size(); i++)//从第四个字符开始转化
            zhuan = zhuan * 10 + str[i] - '0';
          if (zhuan > zuo) {//更新大于解集范围
            zuo = zhuan;//更新左端点取值
            deng1 = true;//标记能取等
          }
        }
      } else {//如果第三个字符不为等于号，此时无法取等
        if (str[2] == '-') {//如果解集为负数
          int zhuan = 0;
          for (int i = 3; i < str.size(); i++)//从第四个字符开始转换
            zhuan = zhuan * 10 + str[i] - '0';
          zhuan *= -1;//因为解集为负数，所以乘上 -1 变号
          if (zhuan >= zuo) {//如果该不等式解集等于原来标记的左端点时，此时无法取到等号
            zuo = zhuan;//更新左端点取值
            deng1 = false;//标记无法取等
          }
        } else {//如果解集不为负数
          int zhuan = 0;
          for (int i = 2; i < str.size(); i++)//从第三个字符开始转换
            zhuan = zhuan * 10 + str[i] - '0';
          if (zhuan >= zuo) {//如果该不等式解集等于原来标记的左端点时，此时无法取到等号
            zuo = zhuan;//更新左端点取值
            deng1 = false;//标记无法取等
          }
        }
      }
    } else {//如果第二个字符为小于号
      if (str[2] == '=') {//如果第三个字符为等于号
        if (str[3] == '-') {//如果解集为负数
          int zhuan = 0;
          for (int i = 4; i < str.size(); i++)//从第五个字符开始转换
            zhuan = zhuan * 10 + str[i] - '0';
          zhuan *= -1;//因为解集为负数，因为乘上 -1 变号
          if (zhuan < you) {//更新小于解集范围
            you = zhuan;//更新右端点取值
            deng2 = true;//标记能取等
          }
        } else {//如果解集不为负数
          int zhuan = 0;
          for (int i = 3; i < str.size(); i++)//从第四个字符开始转换
            zhuan = zhuan * 10 + str[i] - '0';
          if (zhuan < you) {//更新右端点取值
            you = zhuan;//更新右端点取值
            deng2 = true;//标记能取等
          }
        }
      } else {//如果第三个字符不为等于号，此时无法取等
        if (str[2] == '-'){//如果解集为负数
          int zhuan = 0;
          for (int i = 3; i < str.size(); i++)//从第四个字符开始转换
            zhuan = zhuan * 10 + str[i] - '0';
          zhuan *= -1;//因为解集为负数，因为乘上 -1 变号
          if (zhuan <= you) {//如果该不等式解集等于原来标记的右端点时，此时无法取到等号
            you = zhuan;//更新右端点取值
            deng2 = false;//标记无法取等
          }
        } else {//如果解集不为负数
          int zhuan = 0;
          for (int i = 2; i < str.size(); i++)//从第三个字符开始转换
            zhuan = zhuan * 10 + str[i] - '0';
          if (zhuan <= you) {//如果该不等式解集等于原来标记的右端点时，此时无法取到等号
            you = zhuan;//更新右端点取值
            deng2 = false;//标记无法取等
          }
        }
      }
    }
  }
  //开始处理输出
  if (zuo > you || (zuo == you && (deng1 == false || deng2 == false)))//如果左端点取值大于右端点或者左端点等于右端点时无法取等
    cout << "No Answer!\n";//输出无解
  //其余情况均为有解
  else if (zuo == you && deng1 == true && deng2 == true)//当左端点取值等于右端点且均能取到等号
    cout << x << "=" << you << endl;
  else {//其他情况
    if (deng1 == true && deng2 == false && you != 1e7) {
      cout << zuo << "<=" << x << "<" << you << endl;
    }
    if (deng1 == true && deng2 == false && you == 1e7) {
      cout << x << ">=" << zuo << endl;
    }
    if (deng1 == false && deng2 == true && zuo != -1e7) {
      cout << zuo << "<" << x << "<=" << you << endl;
    }
    if (deng1 == false && deng2 == true && zuo == -1e7) {
      cout << x << "<=" << you << endl;
    }
    if (deng1 == true && deng2 == true) {
      cout << zuo << "<=" << x << "<=" << you << endl;
    }
    if (deng1 == false && deng2 == false) {//如果两段均无法取等
      if (zuo != -1e7 && you != 1e7) {
        cout << zuo << "<" << x << "<" << you << endl;
      }
      if (zuo != -1e7 && you == 1e7) {
        cout << x << ">" << zuo << endl;
      }
      if (zuo == -1e7 && you != 1e7) {
        cout << x << "<" << you << endl;
      }
    }
  }
  return 0;
}
```


---

## 作者：剑鞘承天 (赞：1)

本人的第六篇题解（如果算上没通过的话），作为一个萌新，所写的题解可能会有些许~~格式~~问题，但应该可以做到最易理解。

阅读题目，我们不难发现，本体的算法难度~~ywwuyi~~无疑是一道红题，故在此简单带过：

主题程序分为两大块，一块为判断不等式的解最终为多少，另一块是将最终答案输出。

关于计算不等式的解，我们将大于和小于的操作分开为两类，并将大于等于和小于等于分别记录，找出需要大于或大于等于的最大值还有需要小于或小于等于的最小值并输出即可。

输出组块则分为三类：只需大于某值、只需小于某值和需要同时满足左右两端的值，同时考虑输出的范围需不需要带等号即可完成解答。

就这样一个简单的小学数学为什么可以成为橙题？个人认为是因为题目藏了一个将字符串转化为数字的要求，笔者查了好久百度最后找出一种可供参考的方式，下贴出：


```cpp
atoi(s.substr(/*开始截取的位置*/,/*截取的位数*/).c_str());
```

具体解释一下，atoi 是我们转换操作的主体，~~因为我用的是万能头所以忘了是哪个库的~~需调用<stdlib.h>；s 是我们的字符串；而 substr 很明显是用来选取需转换的字符的；c_str()的意思好像是说生成一个 const char 指针，指向以空字符终止的数组。

举个离子，我们有一段字符串 s 的内容是 kkksc114514，我想把 kkksc 不要掉，那么我们就可以这么写：


```cpp
int a;

string kkk;

a=atoi(kkk.substr(5,kkk.size()-5).c_str());
```

运行后我们的 a 就是 114514 啦！

回到本题中的话，需要截取关系运算符后的数字，所以将四种不同的关系运算符分别判断即可。

最后附上 AC 代码（轻喷）：

```cpp
#include<bits/stdc++.h>
using namespace std;

int a,dy=-2e9,dd=-2e9,xy=2e9,xd=2e9,w,x,d,ad,ax;
string q;
char cc;

int main()
{
    cin>>a>>cc;
    for(int i=1;i<=a;i++)
    {
        cin>>q;
        if(q[1]=='<')
        {
            if(q[2]=='=')
            {
                w=atoi(q.substr(3,q.size()-3).c_str());
                xd=min(xd,w);
            }
            else
            {
                w=atoi(q.substr(2,q.size()-2).c_str());
                xy=min(xy,w);
            }
        }
        else
        {
            if(q[2]=='=')
            {
                w=atoi(q.substr(3,q.size()-3).c_str());
                dd=max(dd,w);
            }
            else
            {
                w=atoi((q.substr(2,q.size())).c_str());
                dy=max(dy,w);
            }
        }
    }
    ax=min(xd,xy);
    ad=max(dd,dy);
    if(xy<=xd)
    {
        x=1;
    }
    if(dy>=dd)
    {
        d=1;
    }
    if(ad>ax)
    {
        cout<<"No Answer!"<<endl;
        return 0;
    }
    if(ad==ax)
    {
        if(x==1||d==1)
        {
            cout<<"No Answer!"<<endl;
            return 0;
        }
        else
        {
            cout<<cc<<"="<<ax<<endl;
            return 0;
        }
    }
    if(ad==-2e9)
    {
        cout<<cc;
        if(x==0)
        {
            cout<<"<=";
        }
        else
        {
            cout<<"<";
        }
        cout<<ax<<endl;
    }
    else if(ax==2e9)
    {
        cout<<cc;
        if(d==0)
        {
            cout<<">=";
        }
        else
        {
            cout<<">";
        }
        cout<<ad<<endl;
    }
    else
    {   
        cout<<ad;
        if(d==0)
        {
            cout<<"<=";
        }
        else
        {
            cout<<"<";
        }
        cout<<cc;
        if(x==0)
        {
            cout<<"<=";
        }
        else
        {
            cout<<"<";
        }
        cout<<ax<<endl;
    }
    return 0;
}
```
---
上一篇题解因为格式的原因给审核带来了很多麻烦……希望本篇能过吧……

---

## 作者：Buried_Dream (赞：1)

~~这道题是信心赛中最简单的一道题，虽然我就会这一道~~

## 题意：

给你 $n$ 个方程的解集，去求这个方程组的总解集，也就是求所有解集的交集,如果不存在解集就输出 `No Answer`。

## 思路：

先了解不等式的性质， 同大取大，同小取小。

比如:

`a` $>10$ 同时 `a` >$15$ ,那么解集为  `a` $>15$;

所以说我们只需用将 $>$ 的分解集求出来，$<$ 的分解集求出来，最后将他们求一个总解集就可以了；

## 代码解析：


### 变量：
```cpp
string s,t;//s没用，t是子解集
int flag_1 = 0, flag_2 = 0; //flag = 1表示没有标记过，说明没有大于号或没有小于号，将大于等于和大于用1 2 标记，小于等于和小于也用1 和 2 标记 
int maxx = -inf, minn = inf;//分解集的数，从正无穷到负无穷 
```
### 取数：

```cpp
int qushu(int x) {//取数的函数，将数字从字符串中取出 
    int sum = 0;
    int F = 1;
    for (int i = x; i < t.size(); i++) {//x是从第几位开始取 
        if (t[i] == '-') F = -1;//如果是负数的话 
        else sum = sum * 10 + (t[i] ^ 48);.//字符转数字 
    }
    sum *= F;//是正数就乘1，负数就乘-1 
    return sum;
}
```
### 找最大最小值：注意字符串下标从0开始

```cpp
for(int i = 1; i <= n; i++) {
		cin >> t;
		int sum = 0;
			if(t[1] == '>' && t[2] == '=') {//如果是>=的话，从第三位开始取数 
				sum = qushu(3);
				if(maxx < sum ) {//找最大值 
					maxx = sum;
					flag_1 = 2;//标记最大值是由大于等于得到的 
				}
			}
			else if(t[1] == '<' && t[2] == '=') {//小于等于，同上 
				sum = qushu(3);
				if(minn > sum ) {
					minn = sum;
					flag_2 = 2;
				}
			}
			else if(t[1] == '>') {//如果是>的话，从第二位取数 
				sum = qushu(2); 
				if(maxx < sum ) {//找最大值 
					maxx = sum;
					flag_1 = 1;//标记 
				}
			}
			else if(t[1] == '<') {//同上 
				sum = qushu(2);
				if(minn > sum) {
					minn = sum;
					flag_2 = 1;
				}
			}
	}
```

### 判断无解：
```cpp
if(minn == maxx) {//当两个值相等的时候只有两边都是等号才能成立，否则输出No Answer！ 
		if(flag_1 == 2 && flag_2 == 2) {
		cout << ch << "="  << maxx;
		return 0;
		}
		cout << "No Answer!";
	}
	 else if(minn < maxx) {//如果最小值大于最大值，输出无解 
		cout << "No Answer!";
		return 0;  
	} 
```

### 输出：

```cpp
else {//如果不相等的话 
		if(flag_1 == 1 && flag_2 == 1) { //左右两边都是大于小于 
			cout << maxx << "<" << ch << "<" << minn;
			return 0;
		} else if(flag_2 == 1 && flag_1 == 2) {//左边大于等于，右边小于 
			cout << maxx << "<=" << ch << "<" << minn;
			return 0;
		} else if(flag_2 == 2 && flag_1 == 1) {//左边大于，右边小于等于 
			cout << maxx << "<" << ch << "<=" << minn;
			return 0;
		} else if(flag_1 == 2 && flag_2 == 2) {//左右两边都是大于等于和小于等于 
			cout << maxx << "<=" << ch << "<=" << minn;
			return 0;
		}
		else if(flag_1 == 0 && flag_2 == 0) {//如果都没标记过输出无解 
			cout << "No Answer!";
			return 0;	
		}
		else if(flag_1 == 0 && flag_2 == 1) {//大于号没有标记过，右边为小于号 
			cout << ch << "<" << minn;
			return 0;
		} 
		else if(flag_1 == 0 && flag_2 == 2) {//大于号没有标记过，右边是小于等于 
			cout << ch << "<=" << minn;
			return 0;
		}
		else if(flag_1 == 1 && flag_2 == 0) {//大于标记过，小于没有标记过 
			cout << ch << ">" << maxx;
			return 0;
		}
		else if(flag_1 == 2 && flag_2 == 0) {//大于等于标记过，小于没有标记过 
			cout << ch << ">="<< maxx;
			return 0; 
		}
	}
```

### AC Code：

```cpp
/*
Work by: 看我后面——
goal： Cheat points
algorithm：？？？
thinking support：？？？
*/
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<queue>
#include<stack>
#include<cmath>
#include<cstring>
#define LL long long
#define il inline
#define re register
#define inf 0x3f3f3f3f
#define FJH 1314
#define flase false
using namespace std;

const int maxn = 5e6 + FJH;
const int MAXN = 2e6 + 32;


inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') {
			w = -1;
		}
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s*w;
}
inline void print(int x) {
	if(x < 0) putchar( '-' ),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
int qushu(int x) {//取数的函数，将数字从字符串中取出 
    int sum = 0;
    int F = 1;
    for (int i = x; i < t.size(); i++) {//x是从第几位开始取 
        if (t[i] == '-') F = -1;//如果是负数的话 
        else sum = sum * 10 + (t[i] ^ 48);.//字符转数字 
    }
    sum *= F;//是正数就乘1，负数就乘-1 
    return sum;
}
string s,t;//s是输入的第一个解集，t是输入的2~n个解集 
int flag_1 = 0, flag_2 = 0; //flag = 1表示没有标记过，说明没有大于号或没有小于号，将大于等于和大于用1 2 标记，小于等于和小于也用1 和 2 标记 
int maxx = -inf, minn = inf;//分解集的数，从正无穷到负无穷 

signed main() {
	int n = read();
	char ch = getchar();
	for(int i = 1; i <= n; i++) {
		cin >> t;
		int sum = 0;
			if(t[1] == '>' && t[2] == '=') {//如果是>=的话，从第三位开始取数 
				sum = qushu(3);
				if(maxx < sum ) {//找最大值 
					maxx = sum;
					flag_1 = 2;//标记最大值是由大于等于得到的 
				}
			}
			else if(t[1] == '<' && t[2] == '=') {//小于等于，同上 
				sum = qushu(3);
				if(minn > sum ) {
					minn = sum;
					flag_2 = 2;
				}
			}
			else if(t[1] == '>') {//如果是>的话，从第二位取数 
				sum = qushu(2); 
				if(maxx < sum ) {//找最大值 
					maxx = sum;
					flag_1 = 1;//标记 
				}
			}
			else if(t[1] == '<') {//同上 
				sum = qushu(2);
				if(minn > sum) {
					minn = sum;
					flag_2 = 1;
				}
			}
	}
	if(minn == maxx) {//当两个值相等的时候只有两边都是等号才能成立，否则输出No Answer！ 
		if(flag_1 == 2 && flag_2 == 2) {
		cout << ch << "="  << maxx;
		return 0;
		}
		cout << "No Answer!";
	}
	 else if(minn < maxx) {//如果最小值大于最大值，输出无解 
		cout << "No Answer!";
		return 0;  
	} 
	else {//如果不相等的话 
		if(flag_1 == 1 && flag_2 == 1) { //左右两边都是大于小于 
			cout << maxx << "<" << ch << "<" << minn;
			return 0;
		} else if(flag_2 == 1 && flag_1 == 2) {//左边大于等于，右边小于 
			cout << maxx << "<=" << ch << "<" << minn;
			return 0;
		} else if(flag_2 == 2 && flag_1 == 1) {//左边大于，右边小于等于 
			cout << maxx << "<" << ch << "<=" << minn;
			return 0;
		} else if(flag_1 == 2 && flag_2 == 2) {//左右两边都是大于等于和小于等于 
			cout << maxx << "<=" << ch << "<=" << minn;
			return 0;
		}
		else if(flag_1 == 0 && flag_2 == 0) {//如果都没标记过输出无解 
			cout << "No Answer!";
			return 0;	
		}
		else if(flag_1 == 0 && flag_2 == 1) {//大于号没有标记过，右边为小于号 
			cout << ch << "<" << minn;
			return 0;
		} 
		else if(flag_1 == 0 && flag_2 == 2) {//大于号没有标记过，右边是小于等于 
			cout << ch << "<=" << minn;
			return 0;
		}
		else if(flag_1 == 1 && flag_2 == 0) {//大于标记过，小于没有标记过 
			cout << ch << ">" << maxx;
			return 0;
		}
		else if(flag_1 == 2 && flag_2 == 0) {//大于等于标记过，小于没有标记过 
			cout << ch << ">="<< maxx;
			return 0; 
		}
	}
	return 0;
}
```

---

## 作者：_Z_Y_X_ (赞：0)

题面显然是个大模拟。

可以存每个不等式的边界 $[l,r]$ （其实可能取不到等）。

最开始设成正无穷和负无穷。

然后每个不等式修改一个端点开一个数组判断是否取等。

最后遍历符合所有的左端点和右端点。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,ls[60005],rs[60005],maxl=-1e8,maxr=1e8;
char s,c,a,unknow;
string l,r,un[60005],caonm;
inline int read(){
  char c=getchar();
  int x=0,f=1;
  while(c<'0'||c>'9') {
    if(c=='-') f=-1;
    c=getchar();
  }
  while(c>='0'&&c<= '9') {
    x=x*10+c-'0';
    c=getchar();
  }
  return x*f;
}
int main(){
    cin >>n;
    cin >>s;
    unknow=s;
    l=" ",r=" ";
    for(int i=1;i<=60003;i++){
    	ls[i]=-1e8;
    	rs[i]=1e8;
    }
    for(int i=1;i<=n;i++){
    	cin >>s>>c;
    	cin >>caonm;
    	int qwq=0,f=1;
    	if(caonm[0]=='='){
    		un[i]="=";
    		for(int i=1;i<=caonm.size();i++){
    			if(caonm[i]<'0'||caonm[i]>'9'){
    				if(caonm[i]=='-') f=-1;
    			}
    			else{
    				qwq=qwq*10+caonm[i]-'0';
    			}
    		}
    	}
    	else{
    		un[i]=" ";
    		for(int i=0;i<caonm.size();i++){
    			if(caonm[i]<'0'||caonm[i]>'9'){
    				if(caonm[i]=='-') f=-1;
    			}
    			else{
    				qwq=qwq*10+caonm[i]-'0';
    			}
    		}
    	}
    	qwq=qwq*f;
    	if(c=='>') ls[i]=qwq;
    	else rs[i]=qwq;
    	//cout<<qwq<<endl;
    }
    
    for(int i=1;i<=n;i++){
    	if(maxl<=ls[i]){
    		l=un[i];
    		maxl=ls[i];
    	}
    	if(maxr>=rs[i]){
    		maxr=rs[i];
    		r=un[i];
    	}
    }
    if(maxl>maxr) cout <<"No Answer!";
    else if(maxl==maxr&&(l!="="||r!="=")) cout <<"No Answer!";
    else{
    	if(maxl==-1e8){
    		cout <<unknow<<"<";
    		if(r=="=") cout <<r;
    		cout<<maxr;
    	}
    	else if(maxr==1e8){
    		cout<<unknow<<">";
    		if(l=="=") cout<<l;
    		cout<<maxl;
    	}
    	else if(maxl==maxr){
    		cout <<unknow<<"="<<maxl;
    	} 
    	else{
    		cout <<maxl<<"<";
    		if(l=="=") cout <<l;
    		cout <<unknow<<"<";
    		if(r=="=") cout <<r;
    		cout <<maxr;
    	}
    }
	return 0;
}
```


---

## 作者：雨伞CKY (赞：0)

# 题意简述
给定 $n$ 个不等式的解集，求出该不等式组的解集。

# 题目分析
这是一道模拟题。

不等式组的解集是所有不等式的解集的公共部分，即在数轴（如下图）上表示的公共部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/b0y03vcq.png)

因此，不难发现，不等式组 $\begin{cases} x&\leq a\\ x&\leq b \end{cases}$ 的解为 $x\leq \min(a,b)$；不等式组 $\begin{cases} x&\geq a\\ x&\geq b \end{cases}$ 的解为 $x\geq \max(a,b)$。此外，$\begin{cases} x&\geq a\\ x&\leq b \end{cases}$ 的解为 $\begin{cases} a\leq x\leq b&\text{if } a\lt b\\ x=a&\text{if } a=b\\ \emptyset &\text{if } a\gt b\end{cases}$（$\emptyset$ 表示无解）。

而对于一个不等式，其包含未知数、符号和数值。所以，我们只需要求出某一时刻是否有极值、是否能取到极值、最大值和最小值。并在最后求出其公共解集即可。

# 代码
```cpp
#include <cctype>
#include <climits>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

int n,tmp;
char x;
string line;
pair<bool,int> maxn(true,INT_MAX),minn(true,INT_MIN);
bool negative,maxn_appear = false,minn_appear = false;

void record(){
	negative = false;
    tmp = 0;
    getline(cin,line);
    int j;
    if (line[2] == '=') j = 3;
    else j = 2;
    while (j < line.length()){
        if (line[j] == '-') negative = true;
        else if (isdigit(line[j])) tmp = 10 * tmp + line[j] - '0';
        j++;
	}
	if (negative) tmp *= -1;
    if (line[1] == '<'){
        maxn_appear = true;
        if (line[2] == '=' && tmp < maxn.second) maxn = make_pair(true,tmp);
        else if (line[2] != '=' && tmp <= maxn.second) maxn = make_pair(false,tmp);
    }
    else if (line[1] == '>'){
        minn_appear = true;
        if (line[2] == '=' && tmp > minn.second) minn = make_pair(true,tmp);
        else if (line[2] != '=' && tmp >= minn.second) minn = make_pair(false,tmp);
    }
}

void answer(){
    if (minn_appear && maxn_appear){
    	if (minn.second > maxn.second){
    		cout << "No Answer!";
		}
		else if (minn.second == maxn.second){
			if (minn.first && maxn.first) cout << x << '=' << minn.second;
			else cout << "No Answer!";
		}
		else{
			cout << minn.second << '<';
    		if (minn.first) cout << '=';
    		cout << x << '<';
    		if (maxn.first) cout << '=';
    		cout << maxn.second;
		}
	}
	else if (minn_appear){
		cout << x << '>';
		if (minn.first) cout << '=';
		cout << minn.second;
	}
	else if (maxn_appear){
		cout << x << '<';
		if (maxn.first) cout << '=';
		cout << maxn.second;
	}
}

int main(){
    cin >> n >> x;
    getline(cin,line);//第一行末有一个换行符，需要用 getline “消耗”
    for (int i = 1;i <= n;i++) record();
    answer();
    return 0;
}
```

---

## 作者：HohleFeuerwerke (赞：0)

## 题目大意

给定 $n$ 行字符串，每行是一个关于未知数（给定的一个 `char` $x$，$x$ 满足是一个小写字母）的一个不等式。这个不等式的形式满足 `x op t`。其中 $op\in\{\text{<,<=,>,>=}\}$。求这 $n$ 个不等式组成的不等式组的解集。

$1\leq n\leq 6\times10^4$，不等式中 $|t|\leq 10^6$。

## 分析

由于每一个字符串的形式都是 `x op t` 的形式，那么显然这个字符串不会长。我们不妨构造一个使其最长的字符串：`x<=-1000000`。显然不存在另外一个字符串比这个字符串更长。

观察这个字符串，我们发现一个性质：这 $6\times 10^4$ 个字符串中，每一个都满足其长度是 $\leq 11$ 的。

从这里开始，这道题的性质就变了，可以随便来做了。在处理单个字符串时所允许的复杂度蹭蹭蹭往上涨。

我们不妨进行一个估算：大概在 $\Theta(m^3)$ 以内的复杂度都是可以接受的（这里 $m$ 指单个字符串的长度）。也就是说，只要不乱搞，每一个字符串可以任由你操作。

接下来我们才开始思考这道题所需要维护的具体内容。回想解一个不等式组时，我们所维护的所有内容：**上限的最小值以及下限的最大值**。这是非常显然的，因为不等式组中所有不等式关系是“且”。也就是说，你需要求出所有解得区间的交集。

对于每一个不等式，其必然只能提供上限和下限其中之一的信息。那么我们对其进行分类，分别打上 tag，对于每一种 tag 内，我们分别维护其中所给定的 limit 的最大值和最小值即可。

接下来是取最终答案的一些细节问题：

1. 上限与下限相等且均可取时，只打一个 `=`。如果上限和下限相等，但其中有不可取的时，必然是无解的。
2. 上限小于下限，必然无解。
3. 没有上限/下限时，只有半边有限制，必然有解。如果只有上限，那么打一个 `<` 或者 `<=` 即可；如果只有下限，那么打一个 `>` 或者 `>=` 即可。
4. 其余情况就都是两边有限制的了。先把下限打出来，打一个 `<` 或者 `<=`，输出一遍未知数，再打一个 `<` 或者 `<=`，再把上限打出来即可。

## 代码

代码里不加注释了，这里会把代码里的一些 trick 和细节讲清楚。

`lim` 结构体是一个存储单个不等式所给定的限制是否为上界（如果不是上界那必然是下界，程序中体现为 `bool upper`）、是否允许取等（程序中体现为 `bool equal`），以及它所允许的上限/下限（即使不能取等，维护的也是那个数，程序中体现为 `int limit`）。

ansd 和 ansu 分别维护不等式组的下界与上界。

大致流程：
- 由于初始时没有限制，所以不妨认为其上下界分别为正无穷和负无穷。
- 接下来依次读入每一个字符串，扫一遍每一个字符。对于其为 `<`，`>`，`=`，`-` 以及数字分类讨论。如果是 `<` 或者 `>` 那么首先打上 upper 标记（也就是维护当前不等式给定限制是上界还是下界），然后从当前位置开始往后再扫一遍，如果找到了 `=`，那么把 equal 标记打成 true。
- 扫字符串初始时将 flag 设为 $1$。如果遇到 `-` 那么将 flag 打成 $-1$。接下来计算读到数字的话直接乘上 flag 就可以得到确切值。
- 如果是数字，从当前位开始，如果下一位仍然是数字，那么将当前已经存到了的数字乘上 $10$，并加上下一位，并把扫字符串的这根指针后移。
- 计算最终答案的一些细节前文已经提到，这里不多赘述。

这里处理单个字符串的复杂度是 $\Theta(n)$ 的。疑问在于处理 `<` 和 `>` 时向后扫的一遍，但每个字符串只包含了一个 `<` 或者 `>`。

```cpp
const int MAXN=1e6+5;
int T,n; char x;
char str[MAXN];
struct lim{
	bool upper,equal;
	int limit;
}a[MAXN],ansd,ansu;
signed main()
{
	T=read(),x=get(); ansd.limit=-0x7f7f7f7f,ansu.limit=0x7f7f7f7f;
	for(int t=1;t<=T;t++){
		scanf("%s",str+1); n=strlen(str+1);
		int flag=1;
		for(int i=1;i<=n;i++){
			if(str[i]=='<'||str[i]=='>'){
				for(int j=i;j<=n;j++) if(str[j]=='=') a[t].equal=true;
				if(str[i]=='<') a[t].upper=true;
				else if(str[i]=='>') a[t].upper=false;
			}
			else if(str[i]=='-') flag=-1;
			else if(isdigit(str[i])){
				int cnt=0;
				while(isdigit(str[i])) cnt=cnt*10+str[i]-'0',i++;
				a[t].limit=cnt*flag;
			}
		}
	}
	for(int i=1;i<=T;i++){
		if(a[i].upper){
			if(a[i].limit<ansu.limit) ansu=a[i];
			if(a[i].limit==ansu.limit){
				if(ansu.equal&&a[i].equal) ansu=a[i];
			}
		}
		else{
			if(a[i].limit>ansd.limit) ansd=a[i];
			if(a[i].limit==ansd.limit){
				if(ansd.equal&&a[i].equal) ansd=a[i];
			}
		}
	}
	if(ansu.limit<ansd.limit&&ansu.limit!=-0x7f7f7f7f) puts("No Answer!");
	else if(ansu.limit==ansd.limit){
		if(ansu.equal&&ansd.equal)
			putchar(x),putchar('='),write(ansu.limit),puts("");
		else puts("No Answer!");
	}
	else{
		if(ansd.limit==-0x7f7f7f7f){
			putchar(x),putchar('<');
			if(ansu.equal) putchar('=');
			write(ansu.limit),puts("");
		}
		else if(ansu.limit==0x7f7f7f7f){
			putchar(x),putchar('>');
			if(ansd.equal) putchar('=');
			write(ansd.limit),puts("");
		}
		else{
			write(ansd.limit),putchar('<');
			if(ansd.equal) putchar('=');
			putchar(x),putchar('<');
			if(ansu.equal) putchar('=');
			write(ansu.limit),puts("");
		}
	}
	return 0;
}
```

---

