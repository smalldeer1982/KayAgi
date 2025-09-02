# Counting-out Rhyme

## 题目描述

 $ n $ children are standing in a circle and playing the counting-out game. Children are numbered clockwise from $ 1 $ to $ n $ . In the beginning, the first child is considered the leader. The game is played in $ k $ steps. In the $ i $ -th step the leader counts out $ a_{i} $ people in clockwise order, starting from the next person. The last one to be pointed at by the leader is eliminated, and the next player after him becomes the new leader.

For example, if there are children with numbers $ [8,10,13,14,16] $ currently in the circle, the leader is child $ 13 $ and $ a_{i}=12 $ , then counting-out rhyme ends on child $ 16 $ , who is eliminated. Child $ 8 $ becomes the leader.

You have to write a program which prints the number of the child to be eliminated on every step.

## 说明/提示

Let's consider first example:

- In the first step child $ 4 $ is eliminated, child $ 5 $ becomes the leader.
- In the second step child $ 2 $ is eliminated, child $ 3 $ becomes the leader.
- In the third step child $ 5 $ is eliminated, child $ 6 $ becomes the leader.
- In the fourth step child $ 6 $ is eliminated, child $ 7 $ becomes the leader.
- In the final step child $ 1 $ is eliminated, child $ 3 $ becomes the leader.

## 样例 #1

### 输入

```
7 5
10 4 11 4 1
```

### 输出

```
4 2 5 6 1 
```

## 样例 #2

### 输入

```
3 2
2 5
```

### 输出

```
3 2 
```

# 题解

## 作者：Alex_Wei (赞：6)

水题…

用$vector$模拟即可

这里用到了它的成员函数$erase$

#### $erase(pos)$：删除$pos$位置的数据，返回下一个数据的位置

#### 值得注意的是，这题的数据范围有$10^{9}$，不能直接模拟，需要取模

主要思路就是边读入边输出，计算出这一次需要删掉哪个位置上的人

具体细节见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> s;
int n,k,a,p;//p:将要删除第p个位置上的人
int main()
{
	cin>>n>>k;
	for(int x=1;x<=n;x++)s.push_back(x);//把小朋友按顺序push进去
	while(k--){
		cin>>a,p=(p+a)%s.size();//输入，计算出将要删除哪个位置上的人
		//因为是先计算出p，再取模，所以不会有错误
		cout<<s[p]<<" ",s.erase(s.begin()+p);//输出并删除
	}
	return 0;
}
```

#### 珍爱生命，远离抄袭！

如果有错误或意见欢迎在评论区留言或私信给我

求赞QWQ

---

## 作者：guozhetao (赞：3)

## 翻译


给两个数 $n$  和 $k$ 。

接下来有 $k$ 个数，表示要往下数几个小孩

每次从当领导的人往下数若干次，被数到的人出局，再由出局的下一个人当领导。

输出前 $k$ 个出局的人的编号。
## 思路
刚看到这道题第一反应是有点像 [P1996约瑟夫问题](https://www.luogu.com.cn/problem/P1996)。可以运用队列来解决这道题。先取膜，再循环。
## 知识点
```cpp
#include<queue>
//头文件
  
queue<int>a;//定义一个叫a的int队列
  
a.push(1)//1进队
  
a.pop()//弹出队首
  
a.front()//a队首的项

a.size()//a的长度
```

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k; 
int main() {
	scanf("%d%d",&n,&k);
	int p[101];
	for(int i = 1;i <= k;i++) {
		scanf("%d",&p[i]);
	}
	queue<int>child;
	for(int i = 1;i <= n;i++) {
		child.push(i);//全部进列 
	}
	for(int i = 1;i <= k;i++) {
		p[i] %= child.size();//避免循环次数过多 
		for(int j = 1;j <= p[i];j++) {
			child.push(child.front());
			child.pop();
		}
		printf("%d ",child.front());
		child.pop();//出列
	}
}

```


---

## 作者：CYOI666 (赞：1)

## 翻译


给两个数 $n$  和 $k$ 。

接下来有 $k$ 个数，表示要往下数几个小孩

每次从当领导的人往下数若干次，被数到的人出局，再由出局的下一个人当领导。

输出前 $k$ 个出局的人的编号。
## 思路
可以运用队列来解决这道题。先取膜，再循环。将每个循环到的孩子编号弹出在压入队列，出局的孩子编号输出

## 代码
```cpp
#include<iostream>
using namespace std;
int n,k; 
int main() {
	cin>>n>>k;
	int p[101];
	for(int i = 1;i <= k;i++) {
		cin>>p[i];
	}
	queue<int>c;
	for(int i = 1;i <= n;i++) {
		c.push(i);//进列 
	}
	for(int i = 1;i <= k;i++) {
		p[i] %= c.size();//取膜
		for(int j = 1;j <= p[i];j++) {
			c.push(c.front());//压入队尾
			c.pop();//弹出
		}
		cout<<child.front();
		c.pop();//出列
	}
}

```


---

## 作者：Sternenlicht (赞：1)

思路：

考虑到程序中会有删除操作，用 vector 可以较为便捷地解题。先将 $n$ 个孩子的编号存入 vector 中，边读入数据模拟。

模拟过程如下：

1. 用变量 pos 记录要删除的孩子的位置。

2. 因 $1 \le a_i \le 10^9$，所以要对 $pos+a_i$ 进行取模，模 vector 的大小，保证 pos 在 vector 的范围中。

3. 输出 vector 中第 pos 个位置的编号。

4. 用 vector 自带函数 erase 删除位置 pos。

```cpp
#include <bits/stdc++.h>
#define LL long long
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

vector<int> ve;//用vector模拟 
int main(){
	int n=read(),k=read(),pos=0;//读入，pos为要删除的孩子的位置 
	for (int i=1;i<=n;i++)ve.push_back(i);//存入小孩子编号
	for (int i=1;i<=k;i++){//开始模拟 
		int x=read();//向下一个孩子开始数x个孩子
		pos=(pos+x)%ve.size();//注意x<=10^9，要取模
		write(ve[pos],' ');//输出位置pos的孩子的编号
		ve.erase(ve.begin()+pos);//删除位置pos的孩子 
	}
    return 0;
}

---

## 作者：xmkevin (赞：0)

## 题目大意：

有 $n$ 个孩子在玩游戏，第一次以开头的人作为领导，第 $i$ 次往下数 $a_i$ 个人，最后那个人出局，由这个人的下一个人当领导，直到 $k$ 轮结束。

## 思路：

这题可以使用队列，一开始把 $n$ 个孩子的编号全部入队列，然后每次先取模，再循环 $a_i$ 个孩子，每次往后数的操作就是把队头塞到队尾去。
然后输出最后一个孩子并将它出局。

## 代码：

```cpp
#include <iostream>
#include <queue>
using namespace std;
int n, k, a[105];
queue<int>q;

int main() {
	cin >> n >> k;
	for(int i = 1; i <= k; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++) {
		q.push(i);
	}
	for(int i = 1; i <= k; i++) {
		a[i] %= q.size(); //防止次数过多，造成TLE
		for(int j = 1; j <= a[i]; j++) {
			q.push(q.front());
			q.pop();
		}
		cout << q.front() << ' ';
		q.pop();
	}
	return 0;
}
```

---

## 作者：wangyi_c (赞：0)

这道题其实也是水题……

由于题目中有涉及到“删除”这种操作，所以我们要用 stl 库中的“万金油”动态数组 vector 来实现。

首先先来看看 vector 如何实现删除一个数,要先介绍一个函数 : 
```cpp
v.begin()
```
该函数的作用是返回数组中第一个数字的下标。然后要介绍一个操作：漂移。给一个下标，加或减一个数，即可到那个数的下标，搭配 erase 函数，简直完美！

举个例子：

```cpp
vector <int> v;
v.push_back(1);
v.push_back(2);
v.erase(v.begin()+1);//此时删除的是2
```

忘讲一个点了，由于 $1$ $\leq$ $a_i$ $\leq$ $10^9$，所以 $ t+will $ 要被 vector 的大小取模，保证 $ will$ 的值在数组范围内，否则会运行错误。

### 上 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> v;
int n,k,will; 
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) v.push_back(i);//先把每个小朋友都存入v中
	for(int i=1;i<=k;i++){
		int t;
		cin>>t;
		will=(t+will)%(v.size());//利用%进行优化
		cout<<v[will]<<" ";//输出
		v.erase(v.begin()+will);//删除元素
	}
    return 0;
}
```
谢谢观看

_THE END_

By wangyi

---

## 作者：kirky_wang (赞：0)

## 题意
乍一看，不就是约瑟夫环吗？

#### 实际上是这样的

一群编号为 $1 \sim N$ 的人按顺时针围成一个圈。开始位置为 $1$， 然后给出 $K$ 个数字 $a_1 \sim a_i$，分成 $K$ 次执行，执行第 $i$ 次时，从开始位置顺时针数 $a_i$ 个数，输出且删除数到的最后一个数，然后开始位置变为被删除的数的下一个数。

## 普通版本

用一个数组标记数是否已经被删除，若被删除，扫的时候直接跳过。

要注意的是：因为测试数据给出的数是比较大的，所以要先进行求余，如果不这样做，就会超时

自己用的是数组实现，其实这样并不好，处理的时候很麻烦，看下面代码就知道了。......强烈建议用 STL。


### 代码

```cpp

#include<iostream>
#include<string>
#include<algorithm>
#include<math.h>
#include<string.h>
using namespace std;
#define MAXN 105
bool del[MAXN];
int main()
{
	int n,m;
	int a;
	int p;
	while(cin>>n>>m)
	{
		p=2;//起点是1,所以从2开始数
		int nn=n;
		memset(del,false,sizeof(del));
		while(m--)
		{
			cin>>a;
			if(a%nn)a%=nn;//余数不为0时,求余 
			else if(a>nn)//余数为0且a>nn时,直接等于nn;
			{
				a=nn;
			}
			nn--;
			while(1)
			{
				if(!del[p])
				{
					a--;
					if(a==0)
					{
						del[p]=true;
						break;
					}
				}
				p++;
				if(p>n)p=1;
			}
			if(m!=0)cout<<p<<" ";
			else cout<<p;
			while(del[p])//找起点
			{
				p++;
				if(p>n)p=1;
			}
			//找起点的下一个数，因为是从起点的下一个数开始数的
                        p++;
			if(p>n)p=1;
			while(del[p])
			{
				p++;
				if(p>n)p=1;
			} 
		}
		cout<<endl;
	}
}
```
## STL 版本

前置芝士：deque

 deque 是 STL 的一个容器，全名为双端队列容器，具体定义方式和 vector 相似。

有两个重要函数，`push_back()`，`pop_front()`，前者可以向队尾插入元素，后者可以弹出（删除）队头元素。

我们可以通过向队尾插入队头元素后弹出（删除）队头元素，从而实现换一个人，即将这个‘圈’转一格。

用 deque 代码实现就是：

```cpp
a.push_back(a.front());
a.pop_front();
```

这个弄好之后，其他就都好办了。直接看有没有出列，一个一个人旋转。

### 代码

```cpp
#include<iostream>
#include<deque>
using namespace std;
deque<int> a;
int n,k;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{ 
		a.push_back(i);
	}//输入 
	for(int i=0;i<k;i++)
	{		
		int s;
		cin>>s;
		s%=a.size();//注意要取模 
		while(s--)//一个一个旋转 
		{
			a.push_back(a.front());//插入队首项 
			a.pop_front(); //弹出 
		}
		int val=a.front();
		a.pop_front();//out直接弹出
		cout<<val<<" ";//输出 
	}
	return 0;
}
```

---

## 作者：_lfxxx_ (赞：0)

简单模拟题。

可以用 `vector` 模拟删除操作，$n\le100$，所以并不担心会超时。

注意 $a_i\le10^9$，别真直接模拟，需要模人数。

### 代码：
```cpp
namespace solution{
	int main(){
		int n,k,a,p=0;
		cin>>n>>k;
		vector<int>v(n);//扩容到 n
		for(int i=0;i<n;++i)
			v[i]=i+1;
		while(k--){
			cin>>a;
			cout<<v[p=(p+a)%v.size()]<<' ';
			v.erase(v.begin()+p);
		}
		return 0;
	}
}
```


---

## 作者：happybob (赞：0)

**update: 5.15 修改错误**


和第一篇题解类似，用 `vector` 模拟，其实队列等等都可以，`vector` 的迭代器可以与 `int` 相加然后用 `erase`。

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> vec;

int main()
{
	ios::sync_with_stdio(false);
	int n, k, l = 0;
	cin >> n >> k;
	for (register int i = 1; i <= n; i++)
	{
		vec.push_back(i);
	}
	vector<int>::iterator it = vec.begin();
	for (register int i = 1; i <= k; i++)
	{
		int p;
		cin >> p;
		l += p;
		l %= vec.size();
		cout << vec[l] << ' ';
		vec.erase(it + l);
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

水题。
## 前置芝士：deque
deque 是 STL 的一个容器，全名为**双端队列容器**，具体定义方式和 vector 等相似。

有两个重要函数，
```cpp
push_ back() , pop_ front()
```
前者可以向队尾插入元素，后者可以弹出（删除）队头元素。

## 正题
我们可以通过向队尾插入队头元素后弹出（删除）队头元素，从而实现换一个人，即将这个‘圈’转一格。
用 deque 代码实现就是：
```cpp
a.push_back(a.front());
a.pop_front(); 
```
这个弄好之后，其他就都好办了。直接看有没有 out ，一个一个人旋转。
代码（无注释）：
```cpp
#include<iostream>
#include<deque>
using namespace std;
deque<int> a;
int n,k;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		a.push_back(i);
	}
	for(int i=0;i<k;i++)
	{		
		int s;
		cin>>s;
		s%=a.size();
		while(s--)
		{
			a.push_back(a.front());
			a.pop_front(); 
		}
		int val=a.front();
		a.pop_front();
		cout<<val<<" ";
	}
	return 0;
}

```
有注释：
```cpp
#include<iostream>
#include<deque>
using namespace std;
deque<int> a;
int n,k;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{ 
		a.push_back(i);
	}//输入 
	for(int i=0;i<k;i++)
	{		
		int s;
		cin>>s;
		s%=a.size();//注意要取模 
		while(s--)//一个一个旋转 
		{
			a.push_back(a.front());//插入队首项 
			a.pop_front(); //弹出 
		}
		int val=a.front();
		a.pop_front();//out直接弹出
		cout<<val<<" ";//输出 
	}
	return 0;
}

```
**莫抄题解。**

the end.



---

## 作者：WanderingTrader (赞：0)

这题其实和约瑟夫环非常像，也就是一个队列模拟题。  
### 题目分析
循环k次，每次循环a[i]次，将队头放入队尾，然后弹出队头。  
循环完以后将当前的队头输出并弹出，不再压回
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 105
int a[N];
queue <int> Q;
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;++i)
		Q.push(i);
	for(int i = 1;i <= k;++i)
		scanf("%d",a+i);
	for(int i = 1;i <= k;++i)
	{
		a[i] %= Q.size();
		for(int j=1;j<=a[i];++j)
		{
			Q.push(Q.front());
			Q.pop();
		}
		printf("%d ",Q.front());
		Q.pop();
	}
	return 0;
} 
```
纯模拟，无特别技术含量。  
唯一需要注意的是两点：
1. 由于题目中孩子们是环形，所以可以把a[i]取个模，提高效率
2. 取的模数是当前队列的长度（也就是Q.size()）而不是n

$$\texttt{The End.}$$

---

## 作者：oimaster (赞：0)

## 前言
期末考试后窝又来写题解了！
## 题面
$n$ 个孩子在玩一个游戏。 孩子们站成一圈，按照顺时针顺序分别被标号为 $1$ 到 $n$。开始游戏时，第一个孩子成为领导。 游戏进行 $k$ 轮。 在第 $i$ 轮中，领导会从他顺时针方向下一个孩子开始数 $a_i$ 个孩子。最后数到的那个孩子出局，再下一个孩子成为新的领导。

举个例子， 现在圈内还剩 $[8, 10, 13, 14, 16]$ $5$个孩子，领导编号为 $13$ ， $a_i = 12$。那么出局的孩子为 $16$ 。$8$ 孩子成为下一个领导。

你需要写一个代码模拟这个过程，求出每轮比赛出局的孩子。

第一行包含两个整数 $n$ 和 $k$ $(2 \leq n \leq 100, 1 \leq k \leq n - 1)$。

第二行包含 $k$ 个整数 $a_1, a_2, ..., a_k$ $(1 \leq a_i \leq 10^9)$。

输出 $k$ 个整数，第 $i$ 个整数表示第 $i$ 轮出局的孩子。
## 思路
模拟。
题目中最显眼的就是那个 $(2 \leq n \leq 100, 1 \leq k \leq n - 1)$。很明显，$n$ 只有 $100$，可以直接暴力。

这个暴力可以接受 $\operatorname{O}\left(n^3\right)$ 的超高复杂度，所以做这道题的时候就放下心来。除非你太暴力否则就不会超时。

模拟题，按照我的习惯，我就带着大家讲代码。
```cpp
/* Generated by powerful Codeforces Tool
 * You can download the binary file in here https://github.com/xalanq/cf-tool
 * Author: OI-Master
 * Time: 2020-07-20 14:08:59
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k;
    cin>>n>>k;
    int a[k+1];
    for(int i=1;i<=k;++i)
    	cin>>a[i];
```
这里是输入、头文件，和我的一大堆注释。这里说一下一个小要点，如果使用 `#define int long long` 的话，`int main()` 就会被替换成 `long long main()`。可是在标准 C++ 中，`main()` 只能是 `int` 类型。这时候就需要使用与 `int` 同义的 `signed` 才可以避免 CE。
```cpp
int now=1;  
set<int>out;
```
这两行代码是定义两个重要的东西。相信读过题面的同学都可以猜到，$now$ 是现在谁是领导，而 $out$ 是目前谁被淘汰了。
```cpp
for(int i=1;i<=k;++i){       
	int p=now;               
	a[i]%=n-out.size();      
	while(a[i]--){           
		++p;                 
		if(p>n)              
			p=1;             
		while(out.count(p)){ 
			++p;             
			if(p>n)          
				p=1;         
		}                    
	}
```
首先注意一下，这里大的 `for` 循环还没有结束。我们暂时亮出来的只是一部分。

这一部分的意思也是比较明显的。只是把下一个被淘汰的人找出来，存在 $p$ 里面。

要注意一点，$(1 \leq a_i \leq 10^9)$，所以如果你直接一个一个 `next` 肯定爆掉，我们先要把环都 `mod` 一下，这样才能水过这一部分。
```cpp
out.insert(p);        
cout<<p<<' ';         
now=p+1;              
if(now>n)             
	now=1;            
while(out.count(now)){
	++now;            
	if(now>n)         
		now=1;
}
```
这一段话指的是求出下一位领导是谁。在这位淘汰的人后面，可能紧跟的几位同学也被淘汰了，要使用 `while` 跳过。

这一段和上一段均用了一个 `set` 里面的函数 `count()`。它的返回值是 $0$ 或 $1$，表示 `set` 里有没有。与 `s.find(x)!=s.end()` 类似。

搬上 <http://cplusplus.com/> 的解释：

---
**std::set::count**
```cpp
size_type count (const value_type& val) const;
```
*Count elements with a specific value*

Searches the container for elements equivalent to *val* and returns the number of matches.
 Because all elements in a [set](http://cplusplus.com/set) container are unique, the function can only return *1* (if the element is found) or zero (otherwise).
 
 Two elements of a [set](http://cplusplus.com/set) are considered equivalent if the container's [comparison object](http://cplusplus.com/set::key_comp) returns `false` reflexively (i.e., no matter the order in which the elements are passed as arguments).

**Parameters**
- val
  Value to search for.  Member type `value_type` is the type of the elements in the container, defined in [set](http://cplusplus.com/set) as an alias of its first template parameter (`T`).

**Return value**

`1` if the container contains an element equivalent to *val*, or zero otherwise.
 Member type `size_type` is an unsigned integral type.

**Example**
```cpp
// set::count
#include <iostream>
#include <set>

int main ()
{
  std::set<int> myset;

  // set some initial values:
  for (int i=1; i<5; ++i) myset.insert(i*3);    // set: 3 6 9 12

  for (int i=0; i<10; ++i)
  {
    std::cout << i;
    if (myset.count(i)!=0)
      std::cout << " is an element of myset.\n";
    else
      std::cout << " is not an element of myset.\n";
  }

  return 0;
}
```
**Output**
```
0 is not an element of myset. 
1 is not an element of myset. 
2 is not an element of myset. 
3 is an element of myset. 
4 is not an element of myset. 
5 is not an element of myset. 
6 is an element of myset. 
7 is not an element of myset. 
8 is not an element of myset. 
9 is an element of myset. 
```

---
接下来，您已经不知不觉完成了本题！
所以写这道题要以下知识点：
1. 有熟练的代码能力
2. 复杂度分析
3. 调试代码
4. STL 基本运用

## 代码
```cpp
/* Generated by powerful Codeforces Tool
 * You can download the binary file in here https://github.com/xalanq/cf-tool
 * Author: OI-Master
 * Time: 2020-07-20 14:08:59
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,k;
    cin>>n>>k;
    int a[k+1];
    for(int i=1;i<=k;++i)
    	cin>>a[i];
    int now=1;
    set<int>out;
    for(int i=1;i<=k;++i){
    	int p=now;
    	a[i]%=n-out.size();
    	while(a[i]--){
    		++p;
    		if(p>n)
    			p=1;
    		while(out.count(p)){
    			++p;
    			if(p>n)
    				p=1;
    		}
    	}
    	out.insert(p);
    	cout<<p<<' ';
    	now=p+1;
    	if(now>n)
    		now=1;
    	while(out.count(now)){
    		++now;
    		if(now>n)
    			now=1;
    	}                     
    	/*
    	cout<<' '<<now<<endl;
    	for(int i=1;i<=n;++i)
    		if(!out.count(i))
    			cout<<i<<' ';
    	cout<<endl;
        这一段是我调试的，请忽略。
    	*/
    }
    return 0;
}
```
## 结语
自己 WA 了不少次，结果居然是低级错误呜呜呜。

现在看来，还真的挺简单呢！

---

## 作者：Juanzhang (赞：0)

**思路**

- 模拟

因为$a_i$可以达到$10^9$，所以不能直接暴力$next$，需要通过模运算找到出队人。

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 110;
int n, k, a[maxn], s[maxn];

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= n; i++) {
		s[i] = i;
	}
	int lead = 1, now = n;
	for (int i = 1; i <= k; i++) {
		int k = (lead + a[i]) % now;
		if (!k) {
			k = now;
		}
		printf("%d ", s[k]);
		for (int j = k + 1; j <= n; j++) {
			s[j - 1] = s[j];
		}
		lead = k == now ? 1 : k;
		now--;
	}
	return 0;
}
```

---

