# Split a Number

## 题目描述

Dima worked all day and wrote down on a long paper strip his favorite number $ n $ consisting of $ l $ digits. Unfortunately, the strip turned out to be so long that it didn't fit in the Dima's bookshelf.

To solve the issue, Dima decided to split the strip into two non-empty parts so that each of them contains a positive integer without leading zeros. After that he will compute the sum of the two integers and write it down on a new strip.

Dima wants the resulting integer to be as small as possible, because it increases the chances that the sum will fit it in the bookshelf. Help Dima decide what is the minimum sum he can obtain.

## 说明/提示

In the first example Dima can split the number $ 1234567 $ into integers $ 1234 $ and $ 567 $ . Their sum is $ 1801 $ .

In the second example Dima can split the number $ 101 $ into integers $ 10 $ and $ 1 $ . Their sum is $ 11 $ . Note that it is impossible to split the strip into "1" and "01" since the numbers can't start with zeros.

## 样例 #1

### 输入

```
7
1234567
```

### 输出

```
1801
```

## 样例 #2

### 输入

```
3
101
```

### 输出

```
11
```

# 题解

## 作者：RE_Prince (赞：4)

# CF1181B Split a Number

[link](https://www.luogu.com.cn/problem/CF1181B)


## Sol


来一发 Python 题解。


具体思路是取这个数的中间，因为不管位数有 $l-1$ 的数有多大，它都比位数为 $l$ 的数小。

但是，如果中间的数有前导 $0$，我们就要另处理这个数，考虑是往左分割还是往右分割的和较小。这个看具体情况分类讨论。

首先取两个指针，$i,j$，一个指向 $(l+1)/2$，另一个指向 $(l+1)/2-1$。为了去除前导 $0$，$i$ 向高位搜索第一个不是 $0$ 的地方，$j$ 向低位搜索第一个不是 $0$ 的地方。

用一个变量存储这整个数的值（因为可能遇到像 $\overline{ abcd00000\cdots}$ 这样的数），再进行判断，是 $(0\rightarrow i)+(i+1\rightarrow l)$ 这一段小，还是 $(0\rightarrow j)+(j+1\rightarrow l)$ 这一段小。




整体代码：

```python
m=int(input())
n=input()
j=(m+1)//2 #左右端点
i=j-1
while i>0 and n[i]=='0':# 前导0
    i-=1
while j<m and n[j]=='0':
    j+=1
l=0
r=0
ans=int(n) #取最小
if i>0:
    ans=min(int(n[:i])+int(n[i:]),ans)
if j<m:
    ans=min(int(n[:j])+int(n[j:]),ans)
print(ans) 
```

---

## 作者：封禁用户 (赞：4)

# 0.前言
[CF题目链接](http://codeforces.com/contest/1181/problem/B)

 **题目大意：**
 有一个字符串 str，表示一个数字，现在需要把这个数字分成两个合法的数字，并且希望和尽可能的小。

# 1.解析
 若不想复杂度，对于每个位置 $pos$，只要 $str[pos]$ 不是字符 $0$，那么就可以切分成两个字符串 $[0, pos)$ 和 $[pos, n)$两部分。
 
 那么可以枚举每一个位置，计算一遍数字的和，最终得到一个最小的数字和。
 枚举复杂度是 $O(N)$，分割数字和计算数字和是 $(N)$，总的复杂度是 $O(N^2)$；
 因为 $n$ 最大可以为 $10^5$，那么这个复杂度是不可以接受的。
 
 容易知道，很多位置的分割，是不可能成为最小和的值。比如说字符串 $1234567$，如果分割成 $12+34567$ 或者 $1+234567$ 是明显重复的计算。

 由贪心可以知道，分割出来的字符串 $a,b$ 的长度应该尽可能接近。
 对于长度为 $n$ 字符串，分割成长度为 $n/2$ 和 $n-n/2$，或者 $(n+1)/2$ 和 $n-(n+1)/2$ 的组合是最好的。
 
 那么是否枚举这个情况即可？
 
 Nope！因为存在一个数字 $0$ 的情况。比如说数字 $123000321$，中间的位置都是 $0$。
 
 综合上面的考虑，我们可以将 $n/2$ 向左延伸，直到找到一个不为零的数字，作为分割点；
 同样的，将 $(n+1)/2$ 向右延伸，知道找到一个不为零的数字，作为分割点。
 
 然后从上面的两个可能，选择一个最小的值。
 
 
 时间复杂度为 $O(N)$。

# 2.code
三个函数部分放上：~~你要想抄题解就直接加个头文件然后把这三个代码连起来就行。~~

1. get min
```cpp
string getMinStr(string a, string b) {
    if (a.length() < b.length()) return a;
    else if (a.length() > b.length()) return b;
    else {
        for (int i = 0; i < a.length(); ++i) {
            if (a[i] < b[i]) return a;
            else if (a[i] > b[i]) return b;
        }
        return b;
    }
}
```
2. get sum
```cpp
string getSumStr(string a, string b) {
    string ret;
    int add = 0;
    int indexA = a.length() - 1, indexB = b.length() - 1;
    while (indexA >= 0 || indexB >= 0) {
        int tmp = add;
        if (indexA >= 0) {
            tmp += a[indexA] - '0';
            --indexA;
        }
        if (indexB >= 0) {
            tmp += b[indexB] - '0';
            --indexB;
        }
        if (tmp >= 10) {
            tmp -= 10;
            add = 1;
        }
        else add = 0;
        ret.push_back('0' + tmp);
    }
    if (add) ret.push_back('1');
    reverse(ret.begin(), ret.end());//翻转 
    return ret;
}
string getSplitSum(string str, int pos) {
    string a(str.begin(), str.begin() + pos), b(str.begin() + pos, str.begin() + str.length());
    return getSumStr(a, b);
}
```

3. main
```cpp
int main(){
    int n;
    cin >> n;
    string str;
    cin >> str;
    int x = (n + 1) / 2, y = n / 2;
    string ansX = str, ansY = str;
    while (x < str.length() && str[x] == '0') ++x;
    if (x < str.length()) ansX = getSplitSum(str, x);
    while (y >= 0 && str[y] == '0') --y;
    if (y >= 0) ansY = getSplitSum(str, y);
    cout << getMinStr(ansX, ansY) << endl;
    return 0;
}
```
参考资料：程序员算法进阶练习。

---

## 作者：Macesuted (赞：2)

[题面](https://www.luogu.org/problemnew/show/CF1181B)

## 主要思想
很明显，题面就是让你将一串数割开，使得隔开后的两数总和最小。

稍微分析一下后我们会想到：对于这里隔开后的两个数，他们的总位数一定，显然他们的位数越相近，总和就有机会越小。所以我们尝试从这串数的正中央着手割开，使用高精度进行操作。

我们从这串数的最中央开始分割，先尝试向左移动，找到该过程中第一个符合题意要求的方案，记录结果。然后再尝试向右移动，再找到该过程中第一个符合题意要求的方案，记录下来。最后比较两结果，取较小者。

本文中使用双端队列模拟高精度，使用较为便利。

## 代码

```cpp
#pragma GCC optimize ("O2")
#pragma G++ optimize ("O2")
#include <bits/stdc++.h>
using namespace std;

#define QUICK

#ifdef QUICK
	#define R register
#else
	#define R 
#endif

//定义输出deque高精度的方法
ostream& operator << (ostream &out,deque<int>& x)
{
	for (R deque<int>::iterator it=x.begin();it!=x.end();it++)
	{
		out<<char(*it+'0');
	}
	out<<std::endl;
	return out;
};


int main()
{
#ifdef QUICK
	ios::sync_with_stdio(false);//流加速
#endif
	deque<int> a,b,s,c,d,n;
   	//a,b存放第一次割法的前后者情况
   	//c,d存放第二次割法的前后者情况
   	//s,n分别存放两次割法的和
	int l;
	cin>>l;
	for (R int point=1;point<=l;point++)
	{
		char t;
		cin>>t;
		if(point<=l/2)
		{
			a.push_back(t-'0');
			c.push_back(t-'0');
		}//前半段数
		else
		{
			b.push_back(t-'0');
			d.push_back(t-'0');
		}//后半段数
	}
	a.push_back(b.front());
	b.pop_front();
	a.push_back(b.front());
	b.pop_front();
	d.push_front(c.back());
	c.pop_back();
    	//向左搜索
	while(!a.empty())
	{
		b.push_front(a.back());
		a.pop_back();
		if(a.empty()||b.empty()||a.front()==0||b.front()==0)
		{//判断为空或是前缀0
			continue;
		}
		deque<int>::reverse_iterator pa=a.rbegin(),pb=b.rbegin();
     		//反向迭代器
		int g=0;
       		//相加
		for(;pa!=a.rend()&&pb!=b.rend();++pa,++pb)
		{
			s.push_front((*pa+*pb+g)%10);
			g=(*pa+*pb+g)/10;
		}
		while(pa!=a.rend())
		{
			s.push_front((*pa+g)%10);
			g=(*pa+g)/10;
			pa++;
		}
		while(pb!=b.rend())
		{
			s.push_front((*pb+g)%10);
			g=(*pb+g)/10;
			pb++;
		}
		if(g!=0)
		{
			s.push_front(g);
		}
		break;
	}	
    	//向右搜索
	while(!d.empty())
	{
		c.push_back(d.front());
		d.pop_front();
		if(c.empty()||d.empty()||c.front()==0||d.front()==0)
		{
			continue;
		}
		deque<int>::reverse_iterator pc=c.rbegin(),pd=d.rbegin();
		int g=0;
		for(;pc!=c.rend()&&pd!=d.rend();++pc,++pd)
		{
			n.push_front((*pc+*pd+g)%10);
			g=(*pc+*pd+g)/10;
		}
		while(pc!=c.rend())
		{
			n.push_front((*pc+g)%10);
			g=(*pc+g)/10;
			pc++;
		}
		while(pd!=d.rend())
		{
			n.push_front((*pd+g)%10);
			g=(*pd+g)/10;
			pd++;
		} 
		if(g!=0)
		{
			n.push_front(g);
		}
		break;
	}
//	cout<<a<<b<<c<<d<<s<<n;
	//判断s与n的大小，取小者输出
	if(s.size()==0) 
	{
		cout<<n<<std::endl;
		return 0;
	}
	if(n.size()==0)
	{
		cout<<s<<std::endl;
		return 0;
	}
	if(s.size()!=n.size())
	{
		if(s.size()<n.size())
		{
			cout<<s<<std::endl;
		} 
		else
		{
			cout<<n<<std::endl;
		}
		return 0;
	}
	else
	{//逐位判断
		deque<int>::iterator ps=s.begin(),pn=n.begin();
		for(;ps!=s.end()&&pn!=n.end();ps++,pn++)
		{
			if(*pn!=*ps)
			{
				if(*ps<*pn)
				{
					cout<<s<<std::endl;
				} 
				else
				{
					cout<<n<<std::endl;
				}
				return 0;
			} 
		}
	}
	cout<<n<<std::endl;
	return 0;
}
```

---

## 作者：wenge (赞：2)

题意简述：给你一个$l(2<=l<=100000)$位正整数$n$，将其划分成没有前导0的非空的两段，使这两段表示的正整数之和最小。数据保证至少有一个合法的划分。

这道题要用到高精度。

首先我们会想到暴力枚举所有可能的组合。但是这是$O(n^2)$的，显然会T。

但是这题可以贪心。注意到最小和一般是在中间划分的。我们可以证明其正确性。

设原数是$\overline{abcd}$，则：

1. 若$\overline{abc}+\overline {d}<\overline{ab}+\overline{cd}$，有$90a+9b<9c$。显然，除非$a=0$，不等式才可能成立，但因为没有前导0，$a\neq0$。

1. 若$\overline{a}+\overline {bcd}<\overline{ab}+\overline{cd}$，有$99b<9a$。显然，除非$b=0$，不等式才可能成立，但因为没有前导0，$b\neq0$。

这样我们就证明了从中间划分的最优性。所以，接下来我们要做的就是从中间开始，向两端查找解，然后将左半端和右半端的最优解比大小，输出更小的解，这样就优化成了$O(n)$。需要注意的是，遇到前导0和空串要跳过。

AC代码：
```cpp
#pragma GCC optimize(2) 
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>
using namespace std;
typedef long long ll;
//typedef __int128 lll;
ll n,m,k;
ll ans;
string s,t,w,x,y;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	cin>>s;
	n=s.size();
	reverse(s.begin(),s.end());
   //x和y分别是左半端和右半端的最优解
	for(int i=n/2;i>=0;i--){
		x="";
		t=s.substr(0,i);
		w=s.substr(i,n-i);
		if(w[w.size()-1]=='0'||t[t.size()-1]=='0'||t.empty()||w.empty())continue;//跳过前导0和空串
		x=w;
		for(int i=0;i<t.size();i++){//高精加法
			x[i]+=t[i]-'0';
		}
		for(int i=0;i<w.size()-1;i++){
			while(x[i]>'9')x[i]-=10,x[i+1]++;//进位
		}
		if(x[x.size()-1]>'9')x[x.size()-1]-=10,x+='1';//进位
		//cout<<t<<" "<<w<<" "<<x<<"\n";
		break;//因为找到一个解以后，它就是最优解，所以直接break
	}
	for(int i=(n+1)/2;i<n;i++){
		y="";
		t=s.substr(i,n-i);
		w=s.substr(0,i);
		if(w[w.size()-1]=='0'||t[t.size()-1]=='0'||t.empty()||w.empty())continue;
		y=w;
		for(int i=0;i<t.size();i++){
			y[i]+=t[i]-'0';
		}
		for(int i=0;i<w.size()-1;i++){
			while(y[i]>'9')y[i]-=10,y[i+1]++;
		}
		if(y[y.size()-1]>'9')y[y.size()-1]-=10,y+='1';
		//cout<<t<<" "<<w<<" "<<y<<"\n";
		break;
	}
   //比较
	reverse(x.begin(),x.end());
	reverse(y.begin(),y.end());
	if(x.empty()){
		cout<<y;
		return 0;
	}
	if(y.empty()){
		cout<<x;
		return 0;
	}
	if(x.size()!=y.size()){cout<<(x.size()<y.size()?x:y);return 0;}
	else{
		for(int i=0;i<x.size();i++){
			if(x[i]!=y[i]){
				cout<<(x[i]<y[i]?x:y);
				return 0;
			}
			
		}//cout<<x<<" "<<y<<"\n";
		cout<<x;
	}
    return 0;
}
```

---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
调了三个多小时才过，最后发现是细节问题，~~我太菜了~~。  
首先毋庸置疑，这道题绝对要用高精度，~~不会高精度你还来做这道题~~，然后再加上一些贪心思路就可以了。
## 2. 题目做法
做一道题通常先考虑暴力怎么写，在这道题中，我们要把一个长数分成无前导零的两个数，并比较这两个数加起来的和，取最小值，暴力的话只需要从头到尾依次分割就行，若有前导零就直接跳过。  
看数据范围，暴力的时间复杂度绝对过不了题，接下来我们加上一些贪心思想。  
接下来我们要证明一个东西，从数的中间分割一定比从中间的两边分割所分的两个整数的和更小。  
比如说有一个四位数待分割，它的千位数是 $a$，百位数是 $b$，十位数是 $c$，个位数是 $d$。第一次从中间将前两位和后两位分开，得到的两整数和为 $a \times 10 + b + c \times 10 + d$，第二次将将前三位和后一位分开，得到的两整数和为 $a \times 100 + b \times 10 + c + d$。由于可分割，所以 $a$ 不为零，每个位上的数又小于等于 $9$，故化简一下可得 $a \times 90 + b \times 9$ 一定大于 $c \times 9$。证明完毕。  
故我们可以从中间向两边分割，一旦有答案便可终止分割。如此便可完成此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300010;
inline long long read()
{
	long long x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int n;
int a[N],l,r;
int b[N],c[N],lb,lc,ans[N],ls;
void add()//高精度 
{
	lb=max(lb,lc);
	for(int i=1;i<=lb;i++)
	{
		b[i]=b[i]+c[i];
		if(b[i]>9)
		{
			b[i]-=10;
			b[i+1]++;
		}
	}
	if(b[lb+1])
		lb++;
	for(int i=1,j=lb;i<=lb;i++,j--)
		c[i]=b[j];
}
void change()
{
	if(!ans[1])
	{
		ls=lb;
		for(int i=1;i<=lb;i++)
			ans[i]=c[i];
		return ;
	}
	if(lb<ls)
	{
	    ls=lb;
		for(int i=1;i<=lb;i++)
			ans[i]=c[i];
		return ;
	}
	if(lb>ls)
		return ;
	bool p=0;
	for(int i=1;i<=lb;i++)
	{
		if(ans[i]>c[i])
		{
			p=1;
			break;
		}
		else if(ans[i]<c[i])
		    break;
	}
	if(p)
	{
		ls=lb;
		for(int i=1;i<=lb;i++)
			ans[i]=c[i];
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		char c=getchar();
		a[i]=c-'0';
	}
	l=n/2,r=l;
	if(n%2)
		r++;
	while(!ans[1])
	{
		if(a[l+1])
		{
			lb=l,lc=n-l;
			for(int i=1,j=lb;i<=lb;i++,j--)
				b[i]=a[j];
			for(int i=1,j=n;i<=lc;i++,j--)
				c[i]=a[j];
			for(int i=lb+1;i<=n+1;i++)
				b[i]=0;
			for(int i=lc+1;i<=n+1;i++)
				c[i]=0;
			add();
			change();
		}
		if(a[r+1])
		{
			lb=r,lc=n-r;
			for(int i=1,j=lb;i<=lb;i++,j--)
				b[i]=a[j];
			for(int i=1,j=n;i<=lc;i++,j--)
				c[i]=a[j];
			for(int i=lb+1;i<=n+1;i++)
				b[i]=0;
			for(int i=lc+1;i<=n+1;i++)
				c[i]=0;
			add();
			change();
		}
		l--,r++;
	}
	for(int i=1;i<=ls;i++)
		printf("%d",ans[i]);
	return 0;
}
```

---

## 作者：liJason (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1181B)

虽然我看到楼上已经有 dalao 发了 Python 题解，但我和他的思路略有不同，求管理通过。

~~因为此题数据范围过大（$1\times10^5$)，C++ 要开高精度，所以本人选择了 Python（当然也是因为 Python 有方便的字符串切片）。~~

## 题目大意
将一个串 $s$ 分割成两个不含前导零的子串 $s_1$ 和 $s_2$，使得 $s_1+s_2$ 最小。

## 打暴力
这一题我首先想到打暴力，即把串 $s$ 从头遍历到尾，依次分割求和，再在结果中取最小。

code
```python
l=input()
n=input()
ans=-1
for i in range(1,int(l)):
    a=n[:i]
    b=n[i:]
    if b[0]=='0':
        continue
    if ans==-1:
        ans=int(a)+int(b)
    else:
        ans=min(ans,int(a)+int(b))

print(ans)
```

**但是 TLE on #6**
![](https://cdn.luogu.com.cn/upload/image_hosting/vt9obffv.png)
这是为什么呢？

## 优化
笔者思考甚久，终于发现了分割子串和最小的秘诀：**从中间向两边！**\
为了使分割子串和最小，我们应当使两子串长度相近。因为子串和的长度是由两子串长度中更长的那一段决定的，而我们知道，一个串的长度越长，他的大小就越大。因此，我们可以从中间向两边分割，一找到符合条件的两子串就 `break`。

code
```python
l=input()
n=input()
ans1=-1
ans2=-1
mid=int(l)//2
for i in range(mid+1,int(l)):
    a=n[:i]
    b=n[i:]
    if b[0]=='0':
        continue
    ans1=int(a)+int(b)
    break

for i in range(mid,0,-1):
    a=n[:i]
    b=n[i:]
    if b[0]=='0':
        continue
    ans2=int(a)+int(b)
    break

if ans1!=-1 and ans2!=-1:
    print(min(ans1,ans2))
elif ans1==-1 and ans2==-1:
    print(n)
elif ans1==-1:
    print(ans2)
elif ans2==-1:
    print(ans1)
```

**终于 AC 了！**
![](https://cdn.luogu.com.cn/upload/image_hosting/assznbl1.png)

---

## 作者：_zqh_ (赞：1)

### 思路简述
因为我们要使最终答案最小，那么第一个条件就是位数最小。

因此考虑将原数对半分开，在不考虑前导零的情况下这样分得出的答案最小。

那么问题的关键就是避开前导零。

而将分割线往左、右移就可以得到比目前答案稍逊的答案。

最后统计一下即可得出答案。

**注意**，加法要用高精度。

详情见代码。

[code](https://codeforces.com/contest/1181/submission/259972758)。

---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1181B)

学校信息社团的题，没想到还能写题解，赶紧来一发。

一道黄题我好几天才 AC……

## 思路

题目要求将一串数划分为两段，使得划分后的两数总和最小。容易想到：对于这里分隔后的两个数，它们的总位数一定，显然它们的位数越相近，总和就越小。所以可尝试从这串数的正中央着手划分，分割时先尝试向左移动，找到该过程中第一个符合题意要求的方案，记录结果，再尝试向右移动，再找到该过程中第一个符合题意要求的方案，记录下来。最后比较两结果，取较小者即可。

高精度处理时候，可以使用双端队列模拟高精度运算。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n, a[maxn], b[maxn], len, len1, c[maxn], a1[maxn], a2[maxn];
void getsum(int mid) {
	int len2 = mid - 1, len3 = n - mid + 1;
	memset(a1, 0, sizeof a1);
    memset(a2, 0, sizeof a2);
	for (int i = 1; i <= len2; i++) a1[i] = a[i];
	for (int i = 1; i <= len3; i++) a2[i] = a[i + len2];
	for (int i = 1; i <= len2 / 2; i++) swap(a1[i], a1[len2 - i + 1]);
	for (int i = 1; i <= len3 / 2; i++) swap(a2[i], a2[len3 - i + 1]);
	len = max(len2, len3);
    memset(b, 0, sizeof b);
	for (int i = 1; i <= len; i++) {
		b[i + 1] += (b[i] + a1[i] + a2[i]) / 10;
		b[i] = (b[i] + a1[i] + a2[i]) % 10;
	}
	if (b[len + 1]) len++;
	for (int i = 1; i <= len / 2; i++) swap(b[i], b[len - i + 1]);
}
bool check() {
	if (len < len1) return 0;
    if (len1 < len) return 1;
	for (int i = 1; i <= len; i++) {
		if (b[i] > c[i]) return 1;
		else if (b[i] < c[i]) return 0;
    }
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%1d", &a[i]);
	int i = (n + 1) / 2;
	while (!a[i]) i--;
    getsum(i);
	for (int j = 1; j <= len; j++) c[j] = b[j];
	len1 = len;
    i = (n + 1) / 2 + 1;
	while (!a[i]) i++;
    getsum(i);
	if (check()) {
        for (int i = 1; i <= len1; i++)
            cout << c[i];
    }
	else {
        for (int i = 1; i <= len; i++)
            cout << b[i];
    }
	return 0;
}
```

---

## 作者：ChrisWangZi (赞：1)

# CF1181B Split a Number 题解

## [题目传送门](https://www.luogu.com.cn/problem/CF1181B)

## 思路分析

我们知道，**数的数位越少，不管字典序如何，它总会很小**。

所以，我们就能尽量取中间，这样它们的和就能保证尽量小。

但如果中间取不了（第二段有前导零），我们就将取得中间下标左右调整，直到合法。并将左右调整取个最小值。

## 代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
string jia(string a,string b){
	string ans="";
	int len=max(a.length(),b.length());
	int c=0;
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	for(int i=0;i<len||c!=0;i++){
		int x=0,y=0;		
		if(i<a.length()){
			x=a[i]-'0';
		}
		if(i<b.length()){
			y=b[i]-'0';
		}
		ans+=(c+x+y)%10+'0';
		c=(c+x+y)/10;
	}
	reverse(ans.begin(),ans.end());
	return ans;
}
string minn(string a,string b){
	if(a.size()!=b.size()){
		return a.size()>b.size()?b:a;
	}
	else{
		return a>b?b:a;
	}
}
int main(){
	int len;
	cin>>len;
	string a;
	cin>>a;
	int i,j;
	if(len%2==0){
		i=len/2-1,j=len/2-1;
		while(i>=0&&a[i+1]=='0'){
			i--;
		}
		while(j<=len&&a[j+1]=='0'){
			j++;
		}
		cout<<minn(jia(a.substr(0,i+1),a.substr(i+1,len-i-1)),jia(a.substr(0,j+1),a.substr(j+1,len-j-1)));
	}
	else{
		i=len/2-1,j=len/2;
		while(i>=0&&a[i+1]=='0'){
			i--;
		}
		while(j<=len&&a[j+1]=='0'){
			j++;
		}
		cout<<minn(jia(a.substr(0,i+1),a.substr(i+1,len-i-1)),jia(a.substr(0,j+1),a.substr(j+1,len-j-1)));
	}
	return 0;
}
```

---

## 作者：shengxr (赞：0)

## CF1181B Split a Number
[题目传送门](https://www.luogu.com.cn/problem/CF1181B)

### 题意简述

将一个正整数分割成两部分，将两部分相加，求和的最小值。


------------


### 题目分析

这题我一看到就写了一个无任何优化的暴力代码。

主要思路：先从第一位和第二位中间开始分割，枚举到分割第 $l-1$ 位和第 $l$ 位中间。每次枚举先将第零位到第 $i-1$ 位倒序存入 $ans1$ 数组并计算 $ans1$ 数组的长度 $len1$，再将第 $i$ 位到第 $l-1$ 位倒序存入 $ans2$ 数组并计算 $ans2$ 数组的长度 $len2$，第 $i$ 位如果是 $0$，就跳到下一个循环。
之后将 $ans1$ 和 $ans2$ 用高精度相加，答案存入 $cnt$ 数组中，将 $cnt$ 与 $minn$ 倒序比较，将 $minn$ 更新为更小值。

最后倒序输出 $minn$ 数组。

显而易见，TLE 了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e6+1;
ll i,j,k,len1,len2,len_minn,x=1,y=0;
ll l,ans1[MAXN],ans2[MAXN],cnt[MAXN],minn[MAXN];
string s; 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	for(i=1;i<MAXN;i++)minn[i]=9;
	len_minn=MAXN-1;
	cin>>l>>s;
	for(i=1;i<l;i++){
		memset(ans1,0,sizeof(ans1));
		memset(ans2,0,sizeof(ans2));
		memset(cnt,0,sizeof(cnt));
		len1=len2=0;
		for(j=i-1;j>=0;j--){
			ans1[i-j]=s[j]-'0';
			len1++;
		}
		if(s[i]=='0')continue;
		else{
			for(k=l-1;k>=i;k--){
				ans2[l-k]=s[k]-'0';
				len2++;
			}
		}
		while(x<=len1||x<=len2){

			cnt[x]=ans1[x]+ans2[x]+y;
			y=cnt[x]/10;
			cnt[x]%=10;
			x++;
		}
		cnt[x]=y;
		if(cnt[x]==0)x--;
		if(x<len_minn){
			for(int m=1;m<=len_minn;m++)minn[m]=cnt[m];
			len_minn=x;
		}else if(x==len_minn){
			for(int n=x;n>=1;n--){
				if(minn[n]>cnt[n]){
					for(int m=1;m<=x;m++)minn[m]=cnt[m];
					len_minn=x;
					break;
				}
			}
		}
		x=1,y=0;
	}
	for(int m=len_minn;m>=1;m--)cout<<minn[m];
	return 0;
}
```
------------
之后，我看了 dalao 们的题解，我来说一下我的理解。如果要使和的值最小，那就要让它们的位数尽量小，但因为位数的和已经固定了，所以分割出的两个数的位数尽量相等，所以最小值肯定是 $\lfloor n / 2 \rfloor$ 和 $\lfloor n / 2 \rfloor+1$ 两种情况之一，但因为不能有前导 $0$，所以若第 $\lfloor n / 2 \rfloor$ 位为 $0$，减小到不为 $0$ 为止；若第 $\lfloor n / 2 \rfloor+1$ 位为 $0$，增加到不为 $0$ 为止。

最后将两种的和比较，然后输出较小值，这个值肯定是最小值。
### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e6+1;
int n,len[5],x=1,y=0,p=1,q=0,l,r,a[MAXN];
int ans1[MAXN],ans2[MAXN],ans3[MAXN],ans4[MAXN],cnt1[MAXN],cnt2[MAXN];
string c;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);//给cin cout加速 
	cin>>n>>c;
	for(int i=0;i<n;i++){
		a[i+1]=c[i]-'0';
	}
	l=n/2,r=n/2+1;//从n/2和n/2+1开始 
	while(a[l+1]==0)l--;
	while(a[r+1]==0)r++;//避免前导0 
	for(int i=l;i>=1;i--)ans1[i]=a[l-i+1];
	for(int i=n;i>=l+1;i--)ans2[i-l]=a[n-i+1+l];//倒序存入ans1,ans2 
	for(int i=r;i>=1;i--)ans3[i]=a[r-i+1];
	for(int i=n;i>=r+1;i--)ans4[i-r]=a[n-i+1+r];//倒序存入ans3,ans4 
	len[1]=l,len[2]=n-l;
	while(x<=len[1]||x<=len[2]){
		cnt1[x]=ans1[x]+ans2[x]+y;
		y=cnt1[x]/10;
		cnt1[x]%=10;
		x++;
	}
	cnt1[x]=y;
	if(cnt1[x]==0)x--;//用高精度加法,计算ans1+ans2,存入cnt1
	len[3]=r,len[4]=n-r;
	while(p<=len[3]||p<=len[4]){
		cnt2[p]=ans3[p]+ans4[p]+q;
		q=cnt2[p]/10;
		cnt2[p]%=10;
		p++;
	}
	cnt2[p]=q;
	if(cnt2[p]==0)p--;//用高精度加法,计算ans3+ans4,存入cnt2
	if(x>p){//cnt1的位数小于cnt2的位数
		for(int i=p;i>=1;i--)cout<<cnt2[i];
		return 0;
	}else if(x<p){//cnt1的位数大于cnt2的位数 
		for(int i=x;i>=1;i--)cout<<cnt1[i];
		return 0;
	}else if(x==p){ //cnt1的位数等于cnt2的位数 
		for(int i=x;i>=1;i--){
				if(cnt1[i]>cnt2[i]){
					for(int j=p;j>=1;j--)cout<<cnt2[j];
					return 0;
				}else if(cnt1[i]<cnt2[i]){
					for(int j=x;j>=1;j--)cout<<cnt1[j];
					return 0;
				}
			}
	}//比较cnt1与cnt2 
	return 0;
}
```

---

## 作者：louhao088 (赞：0)

这一道题十分简单的题，~~感觉是黄题，有点恶评~~，

## 题意

把一个数切成两段，是两个数没有前导零，并且使两数和最小

## 思路

本题主要难点就是前导零的处理。

若没有前导零，易得只要在$n/2$个处 或 $n/2+1$处断，就能最小

而有零我们只要分别把他向前向后枚举，直至无$0$。

```cpp
	t=n/2+1;w=n/2;
	while(a[t+1]==0)t++;
	while(a[w+1]==0)w--;
```


------------

而加只要使用高精度加法即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x; 
}
char x;
int n,t,f,a[100005],b[100005],c[100005],b1[100005],c1[100005],d[100005],d1[100005],w;
int main()
{
//	freopen("split.in","r",stdin);
	//freopen("split.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		scanf("%c",&x);a[i]=x-'0';
	}
	t=n/2+1;w=n/2;
	while(a[t+1]==0)t++;
	while(a[w+1]==0)w--;
	for(int i=1;i<=t;i++)
		b[t-i+1]=a[i];
	for(int i=t+1;i<=n;i++)
		c[n-i+1]=a[i];
	for(int i=1;i<=w;i++)
		b1[w-i+1]=a[i];
	for(int i=w+1;i<=n;i++)
		c1[n-i+1]=a[i];
	int len1=t,len2=n-t,len3=0;
	for(int i=1;i<=max(len1,len2);i++)
	{
		d[i]=d[i]+c[i]+b[i];
		if(d[i]>=10)d[i]-=10,d[i+1]=1,len3=max(len3,i+1);
		len3=max(i,len3);
	}
	int len4=w,len5=n-w,len6=0;
	for(int i=1;i<=max(len4,len5);i++)
	{
		d1[i]=d1[i]+c1[i]+b1[i];
		if(d1[i]>=10)d1[i]-=10,d1[i+1]=1,len6=max(len6,i+1);
		len6=max(i,len6);
	}
	if(len3<len6)
	{
		for(int i=len3;i>=1;i--)
		{
			cout<<d[i];
		}exit(0);
	}
	else if(len3>len6)
	{
		for(int i=len6;i>=1;i--)
		{
			cout<<d1[i];
		}exit(0);
	}
	else 
	{
		for(int i=len6;i>=1;i--)
		{
			if(d[i]<d1[i])
			{
				for(int j=i;j>=1;j--)
				{
					cout<<d[j];
				}exit(0);
			}
			else if(d[i]>d1[i])
			{
				for(int j=i;j>=1;j--)
				{
					cout<<d1[j];
				}exit(0);
			}
			cout<<d1[i];
		}
	}
	return 0;
}
```




---

## 作者：jun头吉吉 (赞：0)

## 题意
给定一个长度为$x$位的正整数$n$，把其分割成没有前导$0$的非空的两段，使这两段表示的正整数之和最小。
## 题解
~~打CF主要靠猜~~

我们知道，我们希望两段的长度尽可能相近。如果不考虑前导零，那么就一定是从$\lfloor \frac x 2\rfloor$或$x-\lfloor \frac x 2\rfloor$进行分割。

那么现在加入了前导零的限制，我们只需要用两个指针$s,t$分别指向$\lfloor \frac x 2\rfloor$与$x-\lfloor \frac x 2\rfloor$，假如当前有一段没有前导零，那么就把两种方案（以$a$或$b$进行分割）取最大值或者取两者中可行的一种（如果另一段有前导零）

如果都有前导零，那么`s--,t++`
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+100;
int x,num[2][maxn];
char n[maxn];
void print(int k){
	bool flag=false;
	for(int i=maxn-1;i>=1;i--){
		if(num[k][i])flag=true;
		if(flag)putchar(num[k][i]+'0');
	}
}
signed main(){
	//freopen("split.in","r",stdin);
	//freopen("split.out","w",stdout);
	cin>>x>>n+1;
	int s=x/2,t=x-x/2;
	while(n[s+1]=='0'&&n[t+1]=='0')s--,t++;
	if(n[s+1]!='0'){
		for(int i=s,j=1;i>=1;i--,j++)
			num[0][j]+=n[i]-'0';
		for(int i=x,j=1;i>s;i--,j++)
			num[0][j]+=n[i]-'0';
		for(int i=1;i<maxn-1;i++)
			num[0][i+1]+=num[0][i]/10,num[0][i]%=10;
	}if(n[t+1]!='0'){
		for(int i=t,j=1;i>=1;i--,j++)
			num[1][j]+=n[i]-'0';
		for(int i=x,j=1;i>t;i--,j++)
			num[1][j]+=n[i]-'0';
		for(int i=1;i<maxn-1;i++)
			num[1][i+1]+=num[1][i]/10,num[1][i]%=10;
	}
	if(n[s+1]=='0')print(1);
	else if(n[t+1]=='0')print(0);
	else{
		int nnn=0;
		for(int i=maxn-1;i>=1;i--)
			if(num[0][i]!=num[1][i]){
				if(num[0][i]<num[1][i]){break;}
				if(num[0][i]>num[1][i]){nnn=1;break;}
			}
		print(nnn);
	}
}
``

---

