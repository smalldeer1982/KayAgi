# Nephren gives a riddle

## 题目描述

奈芙莲有一个字符串数组 $f_{0\dots\infty}$。

$f_0$ 为 `What are you doing at the end of the world? Are you busy? Will you save us?`。

她想让更多人了解这个数组，所以她定义：

$$
\forall i\ge 1,f_i=\texttt{What are you doing while sending "}+f_{i-1}\\
+\texttt{"? Are you busy? Will you send "}+f_{i-1}+\texttt{"?}
$$

**注意其中的引号。**

奈芙莲会询问 $q$ 次，第 $i$ 次给定 $n,k$，你需要求出 $f_{n,k}$ 的值。**注意字符串从 $1$ 开始。**

## 说明/提示

对于所有数据，$1\le q\le 10,1\le n\le 10^5,1\le k\le 10^{18}$。

## 样例 #1

### 输入

```
3
1 1
1 2
1 111111111111
```

### 输出

```
Wh.```

## 样例 #2

### 输入

```
5
0 69
1 194
1 139
0 47
1 66
```

### 输出

```
abdef```

## 样例 #3

### 输入

```
10
4 1825
3 75
3 530
4 1829
4 1651
3 187
4 584
4 255
4 774
2 474
```

### 输出

```
Areyoubusy```

# 题解

## 作者：Fuko_Ibuki (赞：7)

这道题也是CF上比较不错的一道题了,比赛的时候我花了两个小时才推出了标算,然后用6分钟的时间打跪了.
首先判断'.',可以推出f[i].size()=f[i-1].size()×2+68,∵k<=1e18,可以看出当n>=55(差不多这个数字)时就不可能出现'.'了.
然后将每一个字符串分为五段,通过不断递归往下寻找第k个字符究竟是在前面的哪一个字符串里.
```cpp
#include<bits/stdc++.h>
#define boss 100000
#define r1 34 //a1.size()
#define r2 32 //a2.size()
#define r3 2  //a3.size()
#define da 9223372036854775807 //max_long long
using namespace std;
typedef long long ll;

int t,n;ll k;
char f0[]={"What are you doing at the end of the world? Are you busy? Will you save us?"},//f0
     f1[]={"What are you doing while sending ?Are you busy? Will you send ?"},
     f2[]={"What are you doing while sending \"What are you doing at the end of the world? Are you busy? Will you save us?\"? Are you busy? Will you send \"What are you doing at the end of the world? Are you busy? Will you save us?\"?"};
string f[boss+10]={f0,f2},
       a1="What are you doing while sending \"",//递归所用的三个字符串
       a2="\"? Are you busy? Will you send \"",//在字符串里要想出现双引号要先打一个反斜杠
       a3="\"?";
ll changdu[boss+10]={75};//字符串的长度

char work(int n,ll k)
{
if (k>changdu[n]) return '.';
if (n==0) return f0[k];//n=0,直接输出
if (k<r1) return a1[k];//增加的字符串的第一段
k-=r1;
if (k<changdu[n-1]) return work(n-1,k);//说明在f[i-1]中
k-=changdu[n-1];
if (k<r2) return a2[k];//第二段
k-=r2;
if (k<changdu[n-1]) return work(n-1,k);//也说明在f[i-1]中
k-=changdu[n-1];
if (k<r3) return a3[k];//第三段
return '.';
}

int main()
{
int i;string ans="";
for (i=1;i<=55;++i) changdu[i]=2*changdu[i-1]+68;
for (i=56;i<=boss;++i) changdu[i]=da;//后面全部赋成max_long long
for (scanf("%d",&t);t--;) 
  {
  scanf("%d%lld",&n,&k);
  ans.push_back(work(n,k-1));
  }
cout<<ans;
}
```
哦对了我博客上有这个题的题解.
http://blog.csdn.net/qq_31908675/article/details/78704537

---

## 作者：LYqwq (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF896A)

# 题目大意

有一个字符串数组，定义如下：

- $n=0$：`What are you doing at the end of the world? Are you busy? Will you save us?`；
- $n \neq 0$：`What are you doing while sending "` $+f_{n-1}+$ `"? Are you busy? Will you send "` $+f_{n-1}+$ `"?`

给出 $q$ 次询问，每次询问给出两个整数 $n,k$，输出 $f_n$ 的第 $k$ 个字符。如果 $f_n$ 的第 $k$ 个字符不存在，则输出 `.`。

数据范围：$1 \leq q \leq 10,0 \leq n \leq 10^5,1 \leq k \leq 10^{18}$

# 思路

数据范围好大...

如果试图按题意模拟，那么是存不下字符串的。

于是我们要分情况来看。

先来从 $f_n$ 入手，它是这样的：

`What are you doing while sending "` +$f_{n-1}$+ `"? Are you busy? Will you send "` +$f_{n-1}$+ `"?`

我们把它分成多部分：

![](https://cdn.luogu.com.cn/upload/image_hosting/g7pvxv65.png)

我们写一个 dfs 函数，每次寻找 $f_n$ 的第 $k$ 个字符。函数内分别对各种情况做了处理，包括 $n=0$。首先要初始化一个长度数组，能够通过 $f_0$ 的长度推出来，然后每次 dfs 时都有很大用处。

具体见代码，注释应该够详细了吧？

**记得开 long long！**

# 代码

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
int q,n;
ll k;
// f就是f0，照搬；fn表示后面用来递归的原串，不包含递归串。
string f=" What are you doing at the end of the world? Are you busy? Will you save us?";
string fn=" What are you doing while sending \"\"? Are you busy? Will you send \"\"?";
// len[i]表示f[i]项的长度，先初始化好长度再进行操作。
ll len[100005]; // 注意开long long

inline ll read(){
	ll X=0; bool flag=1; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
	if(flag) return X;
	return ~(X-1);
}

void init(){ // 初始化长度
	len[0]=75; // 第一项的长度通过计算是75
	for(int i=1; i<=100000; i++){
		len[i]=len[i-1]*2+68; // 包含两个前一项的长度，68是其他的字符总长度
		if(len[i-1]<0 || len[i]>1e18){
			len[i]=-1;
		}
	}
}

void dfs(int n,ll k){
	if(n==0){ // f[0]的情况
		putchar(f[k]);
		// 直接输出，就完事了
		return;
	}
	if(k<35){ // 在第一个区间，也就是红色区间
		putchar(fn[k]);
		// 可直接输出
		return;
	}
	/*
	橙色区间情况，如果在红色区间外而且橙色区间长度，也就是f[n-1]的长度，比1e18大那就是橙色区间
	还有一种情况，也就是刚好在橙色区间中，k比34大，且小于上一个长度加上35(因为有引号)，也是橙色区间
	*/
	if(len[n-1]==-1 || k>34 && k<len[n-1]+35){
		dfs(n-1,k-34);
		// 很好理解，不是红色区间的情况，k要减去前面的字符个数，再递归。
		// 绿色区间情况也一样
		return;
	}
	// 黄色区间情况
	// 在橙色区间后面且在绿色区间前面
	if(k>len[n-1]+34 && k<len[n-1]+67){
		putchar(fn[k-len[n-1]]);
		return;
	}
	// 绿色区间
	if(k>len[n-1]+66 && k<len[n-1]*2+67){
		dfs(n-1,k-len[n-1]-66);
		return;
	}
	// 否则就是蓝色区间
	putchar(fn[k-len[n-1]*2]);
}

int main(){
	init();
	q=read();
	while(q--){
		n=read(),k=read();
		if(k>len[n] && len[n]!=-1){ // k超出长度，输出'.'
			putchar('.');
			continue;
		}
		dfs(n,k); // 否则就去找！
	}
	return 0;
}
```

---

## 作者：GossWandering (赞：2)

$Update 2020/7/16$
- 改了一个错别字。
- 修了 $\LaTeX$ 的锅。

上一篇题解咋没有看懂捏/fad，我来讲一个比较通俗易懂的解法吧。

首先简述一下题面的意思：

$f_0=\text{What are you doing at the end of the world? Are you busy? Will you save us?}$

$f_i=\text{What are you doing while sending "}f_{i-1}\text{"? Are you busy? Will you send "}f_{i-1}"?$

给出 $n,k$，求 $f_n$ 的第 $k$ 个字符。

解法 $1$:

直接计算就好啦，用 $\text{string}$ 求出每个$f_i$。

代码：
```
string f[10010];
char ans[11];
int q=read(),tot=0;
f[0]="What are you doing at the end of the world? Are you busy? Will you save us?";
for(int i=1;i<=10;i++){
    f[i]+="What are you doing while sending ";
    f[i]+='\"';
    f[i]+=f[i-1];
    f[i]+='\"';
    f[i]+="? Are you busy? Will you send ";
    f[i]+='\"';
    f[i]+=f[i-1];
	f[i]+='\"';
	f[i]+='?';
}
for(int i=1;i<=q;i++){
	int n=read(),k=read();
	if(f[n].size()<=k-1) ans[++tot]='.';
	else ans[++tot]=f[n][k-1];
}
for(int i=1;i<=q;i++) cout<<ans[i];
```

然鹅，这只对小范围的 $n$ 奏效，原因显然： $f_i$ 的长度呈指数级增长，对于 $n\le10^5$ 的数据显然 $\text{string}$ 存不下。

解法 $2$:

考虑优化。我们发现算法 $1$ 中将 $f_n$ 的每一个字符都求了出来，但题目只求第 $k$ 个字符，所以算法一不优。

发现 $f_i$ 由这么几部分组成：

- $part\ 1:\text{What are you doing while sending "}$
- $part\ 2:f_{i-1}$
- $part\ 3:\text{"? Are you busy? Will you send "}$
- $part\ 4:f_{i-1}$
- $part\ 5:"?$

于是递归求解即可。

总体来说，程序分为以下几步：
- 求出 $f_i$ 的长度（注意只需求到 $f_{53}$ 即可，因为 $f_{53}$ 的长度已经大于 $k$ 了）
- 算出 $f_n$ 的第 $k$ 个字符在第几部分。
- 递归求解。

下面是递归的代码：
```
char a[110]=" What are you doing at the end of the world? Are you busy? Will you save us?";  
char b[110]=" What are you doing while sending !!? Are you busy? Will you send !!?";
char dfs(int n,long long k){
    if(n>53){
        if(k<=34) return b[k];  
        else return dfs(n-1,k-34); 		
    }
    if(n==0) return a[(int)k];
    if(k<=34) return b[(int)k];
    else if(k<=34+len[n-1]) return dfs(n-1,k-34);
    else if(k<=66+len[n-1]) return b[(int)(k-len[n-1])];
    else if(k<=66+2*len[n-1]) return dfs(n-1,k-66-len[n-1]);
    else return b[(int)(k-len[n-1]*2)];
}
```

---

## 作者：Leap_Frog (赞：2)

### P.S.
![](https://cdn.luogu.com.cn/upload/image_hosting/1pfui5kg.png)  
我奈芙莲永远滴神！  
有Nephren登场的题目都是好题！  
不接受任何反驳！（破音  

这题封顶黄题，应该没有绿题吧。  

### Description.
给定一个构造一连串字符串的方法（见翻译），求第 $n$ 个字符串的第 $k$ 个字符是多少，多组询问。  

### Solution.
其实还是挺好想的吧。  
设第 $i$ 个字符串的长度为 $f(i)$。  
则根据字符串构造方式，我们有 $f(i)=f(i-1)\times2+z$，其中 $z$ 是一段字符串的长度。  
我们就可以 $O(n)$ 递推出所有字符串的长度了。  

然后，我们发现每个字符串可以由五部分组成。分别为：  
1. `What are you doing while sending "`
2. 第 $i-1$ 项
3. `"? Are you busy? Will you send "`
4. 第 $i-1$ 项
5. `"?`

我们直接对当前所要查询的这个字符找到它属于哪部分。  
如果是 1、3、5 部分的话直接输出答案，否则递归处理。  
这样时间复杂度是对的，应该是 $O(\min(\log_2K,N))$ 级别的。  

### Code.
```cpp
//一定，每个人都没有责任，都没有错，每个人都拼尽了全力。——Nephren
#include<bits/stdc++.h>
using namespace std;
const string A="What are you doing at the end of the world? Are you busy? Will you save us?";//打出来的表
const string Z1="What are you doing while sending \"",Z2="\"? Are you busy? Will you send \"",Z3="\"?";
const int deta=Z1.size()+Z2.size()+Z3.size();long long f[100005],k;int Q,n;
inline char dfs(int n,long long k)//递归处理
{//注意，如果n=0的话需要直接返回答案，因为已经无法递归了。
	if(k>f[n]) return '.';else if(n==0) return A[k];
	if(k<(int)Z1.size()) return Z1[k];else k-=Z1.size();
	if(k<f[n-1]) return dfs(n-1,k);else k-=f[n-1];
	if(k<(int)Z2.size()) return Z2[k];else k-=Z2.size();
	if(k<f[n-1]) return dfs(n-1,k);else k-=f[n-1];
	if(k<(int)Z3.size()) return Z3[k];else k-=Z3.size();
	return '.';//暴力枚举是那一部分
}
int main()
{
	memset(f,0x3f,sizeof(f)),f[0]=A.size();for(int i=1;i<=55;i++) f[i]=(f[i-1]<<1)+deta;//上面的递推式
	for(scanf("%d",&Q);Q--;) scanf("%d%lld",&n,&k),k--,putchar(dfs(n,k));
	return 0;
}
```
完结撒花

---

## 作者：__delta_epsilon__ (赞：0)

### 题目大意

$f_0=\texttt{What are you doing at the end of the world? Are you busy? Will you save us?}$。

$f_n=\texttt{What are you doing while sending "}+f_{n-1}+\texttt{"? Are you busy? Will you send "}+f_{n-1}+\texttt{"?}$。

求 $f_n$ 的第 $l$ 个字符，共 $q$ 组数据。若 $l$ 超过字符串范围，输出 `.`。

### 思路分析

这是道典型的递归题，分情况讨论即可。

我们先把这几段字符串存下来。

令 $f_0=\texttt{What are you doing at the end of the world? Are you busy? Will you save us?}$，$s_1=\texttt{What are you doing while sending "}$，$s_2=\texttt{"? Are you busy? Will you send "}$，$s_3=\texttt{"?}$。

所以递推式为，$f_n=s_1+f_{n-1}+s_2+f_{n-1}+s_{3}$。

那么我们可以看到，

- 第 $1\sim|s_1|$ 个字符在 $s_1$ 里，可以直接输出。
- 第 $|s_1|+1\sim|s_1|+|f_{n-1}|$ 个字符在 $f_{n-1}$ 里，可以递归求解。
- 第 $|s_1|+|f_{n-1}|+1\sim|s_1|+|s_2|+|f_{n-1}|$ 个字符在 $s_2$ 里，可以直接输出。
- 第 $|s_1|+|s_2|+|f_{n-1}|+1\sim|s_1|+|s_2|+2|f_{n-1}|$ 个字符在 $f_{n-1}$ 里，可以递归求解。
- 第 $|s_1|+|s_2|+2|f_{n-1}|+1\sim|s_1|+|s_2|+|s_3|+2|f_{n-1}|$ 个字符在 $s_3$ 里，直接输出。

那么可以如下设计递归函数（下用 $s[i]$ 表示字符串 $s$  中的第 $i$ 个字符，下标从 $0$ 开始；$\operatorname{calc}(n,l)$ 表示第 $n$ 个字符串的第 $l$ 个字符，下标从 $1$ 开始。之所以下标起始位置不一样，是因为 string 从 $0$ 开始，而题目要求从 $1$ 开始）：

$$\operatorname{calc}(n,l)=\left\{
\begin{array}{ll}
f_0[l-1]&n=0,l\le|f_0|\\
\texttt{.}&n=0,l>|f_0|\\
s_1[l-1]&n>0,l\le|s_1|\\
\operatorname{calc}(n-1,l-|s_1|)&n>0,l\in(|s_1|,|s_1|+|f_{n-1}|]\\
s_2[l-|s_1|-|f_{n-1}|-1]&n>0,l\in(|s_1|+|f_{n-1}|,|s_1|+|s_2|+|f_{n-1}|]\\
\operatorname{calc}(n-1,l-|s_1|-|s_2|-|f_{n-1}|)&n>0,l\in(|s_1]+|s_2|+|f_{n-1}|,|s_1|+|s_2|+2|f_{n-1}|]\\
s_3[l-|s_1|-|s_2|-2|f_{n-1}|-1]&n>0,l\in(|s_1|+|s_2|+2|f_{n-1}|, |s_1|+|s_2|+|s_3|+2|f_{n-1}|]\\
\texttt{.}&\rm others\end{array}\right.$$

最后一个问题，怎么样计算 $|f_i|$？

显然有 $|f_n|=2|f_{n-1}|+|s_1|+|s_2|+|s_3|$。对于 $|f_i|>2^{63}-1$ 的值，直接赋值为 $2^{63}-1$ 即可，因为输入无法输入超过这个范围的值。

稍微估算一下可以得到 $|f_{55}|<2^{63}-1,|f_{56}|>2^{63}-1$。

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string f0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
string f1 = "What are you doing while sending \"";
string f2 = "\"? Are you busy? Will you send \"";
string f3 = "\"?";
int q, n, l;
int len[100001];
char calc(int n, int l) {
    if(n == 0) {
        if(l > len[0]) return '.';
        return f0[l - 1];
    }
    if(l <= f1.size()) return f1[l - 1];
    else if(l <= f1.size() + len[n - 1]) return calc(n - 1, l - f1.size());
    else if(l <= f1.size() + f2.size() + len[n - 1]) return f2[l - f1.size() - len[n - 1] - 1];
    else if(l <= f1.size() + f2.size() + 2 * len[n - 1]) return calc(n - 1, l - f1.size() - len[n - 1] - f2.size());
    else if(l <= f1.size() + f2.size() + f3.size() + 2 * len[n - 1]) return f3[l - f1.size() - f2.size() - 2 * len[n - 1] - 1];
    else return '.';
}
void init() {
    len[0] = f0.size();
    for(int i = 1; i <= 55; i++) len[i] = 2 * len[i - 1] + f1.size() + f2.size() + f3.size();
    for(int i = 56; i <= 100000; i++) len[i] = INT64_MAX;
}
signed main(){
    init();
    cin >> q;
    while(q--) {
        cin >> n >> l;
        cout << calc(n, l);
    }
    return 0;
}
```

---

## 作者：流光萤影 (赞：0)

**前言：本题解编程语言：C++14 (GCC 9)。**

------------

**正文：**

**温馨提醒**：字符串中有引号，不加引号两行泪

这道题思路其实很简单，直接**递归 & 分类讨论 $f _ {n}$** 就行。

我们可以**把 $f _ {n}$ 分段**，部分情况特殊判定。那么，每次递归遇到的的可能性无非就是下面几种情况：

注：#2、#4 和 #6 确实有引号，你没看错

1. $n = 0$。

2. $f _ {n,k}$ 在 $\texttt{What are you doing while sending "}$ 内。

3. $f _ {n,k}$ 在 $f _ {n-1}$ 内。

4. $f _ {n,k}$ 在 $\texttt{? Are you busy? Will you send "}$ 内。

5. $f _ {n.k}$ 在 $f _ {n-1}$ 内。

6. $f _ {n,k}$ 在 $\texttt{"?}$ 内。

7. $k > |f _ {n}|$。

知道了所有情况，只要**针对每种情况去处理**便可以了。每种情况对应的执行方案如下：

1. 直接输出。

2. 直接输出。

3. 递归。

4. 直接输出。

5. 递归。

6. 直接输出。

7. 直接输出。

------------

递归思路已经明确了，但怎么判断 $f _ {n,k}$ 属于哪个区间呢？

首先，先建立题目中已知的字符串：

```cpp
const string s1 = "What are you doing at the end of the world? Are you busy? Will you save us?";
const string s2 = "What are you doing while sending \"";
const string s3 = "\"? Are you busy? Will you send \"";
```

再建立一个用于储存长度的数组 $len$，$len _ {n}$ 表示 $f _ {n}$ 的长度：

```cpp
unsigned long long len[100005];
```

**由题意得 $len _ {i} = 2 \cdot len _ {i-1} + |s2| + |s3| + 2(1 \le  i)$。**

列出了等式，程序中只要用循环递推即可：

```cpp
for(int i = 1;i <= 100000;i++) len[i] = len[i-1]*2+s2.length()+s3.length()+2;
```

于是核心的递归代码便推出了：

```cpp
char print(int a,unsigned long long b) //a→n，b→k
{
	if(a == 0)
	{
		if(b > s1.length()) return '.';
		return s1[b-1];
	}
	if(b <= s2.length()) return s2[b-1];
	if(b <= s2.length()+len[a-1]) return print(a-1,b-s2.length());
	if(b <= s2.length()+len[a-1]+s3.length()) return s3[b-1-s2.length()-len[a-1]];
	if(b == len[a]) return '?';
	if(b == len[a]-1) return '"';
	if(b > len[a]) return '.';
	return print(a-1,b-s2.length()-len[a-1]-s3.length());
}
```


------------

**AC代码：**

```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
unsigned long long k,len[100005];
int t,n;
const string s1 = "What are you doing at the end of the world? Are you busy? Will you save us?";
const string s2 = "What are you doing while sending \"";
const string s3 = "\"? Are you busy? Will you send \"";
char print(int a,unsigned long long b)
{
	if(a == 0)
	{
		if(b > s1.length()) return '.';
		return s1[b-1];
	}
	if(b <= s2.length()) return s2[b-1];
	if(b <= s2.length()+len[a-1]) return print(a-1,b-s2.length());
	if(b <= s2.length()+len[a-1]+s3.length()) return s3[b-1-s2.length()-len[a-1]];
	if(b == len[a]) return '?';
	if(b == len[a]-1) return '"';
	if(b > len[a]) return '.';
	return print(a-1,b-s2.length()-len[a-1]-s3.length());
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	len[0] = s1.length();
	for(int i = 1;i <= 100000;i++) len[i] = len[i-1]*2+s2.length()+s3.length()+2;
	cin >> t;
	for(;t;t--)
	{
		cin >> n >> k;
		cout << print(n,k);
	}
	return 0;
}
```


---

## 作者：Mistybranch (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF896A)

题目大概意思是：

- 对于以下生成字符串规则：

1. $ f_0 = \texttt{What are you doing at the end of the world? Are you busy? Will you save us?}$

2. $ f_n = \texttt{What are you doing while sending "} f_{n - 1} \texttt{"? Are you busy? Will you send "} f_{n - 1}? \texttt{"?}$ 注意：$n \geq 1$

- 输出第 $n$ 个字符串中的第 $k$ 个字符。

我们发现，$f_n$ 的字符串无非由四个部分按特定顺序组成：

- $s_0$ = $f_0$

- $s_1$ = $\texttt{What are you doing while sending "}$

- $s_2$ = $\texttt{"? Are you busy? Will you send "}$

- $s_3$ = $\texttt{"?}$

通过字符串生成规则可知： $f_n$ 的长度为 $f_{n - 1}$ 的长度乘上 $2$ 再加上 $s_1$， $s_2$， $s_3$ 的长度。

下面就有了一个思路：

- 当 $n = 0$ 时，可直接判断第 $k$ 个字符。

- 对于其余的 $n$（$n \geq 1$），当 $k \leq s_1$ 的长度时，$f_n$ 的第 $k$ 个字符为 $s_1[k - 1]$

- 对于剩下的情况，就需要用到递归了。但是我们发现本题 $n \leq 10^5$，数据范围巨大，什么数据结构也存不下整个字符串，咋办？

- 我们注意到 $k$ 的最大值为 $10^{18}$，而我们发现 $f_{53}$ 的长度 已经大于了 $10^{18}$，这就说明 $n \geq 54$ 时，可以直接减小到 $53$ 再处理，然后再不断减小问题规模，具体情况可看代码：

```cpp


#include <iostream>
 
using namespace std;

int q, n;
long long k, l[59];
string res;

string s[] = {
	"What are you doing at the end of the world? Are you busy? Will you save us?", 
	"What are you doing while sending \"",
	"\"? Are you busy? Will you send \"",
	"\"?"
};

char F (int cn, long long ck) {
	long long e1, e2, e3;
	
	if (!cn) {
		if (ck <= s[0].size()) {
			return s[0][ck - 1];
		}
		
		return '.';
	}
	
	if (ck <= s[1].size()) {
		return s[1][ck - 1];
	}
	
	if (cn >= 54) {
		return F(cn - 1, ck - s[1].size());
	}
	
	e1 = s[1].size() + l[cn - 1];
	e2 = e1 + s[2].size();
	e3 = e2 + l[cn - 1];//将整个字符串分成 5 个部分，看第 k 个字符属于哪一部分。
	
	if (ck <= e1) {
		return F(cn - 1, ck - s[1].size());
	}
	
	if (ck <= e2) {
		return s[2][ck - e1 - 1];
	}
	
	if (ck <= e3) {
		return F(cn - 1, ck - e2);
	}
	
	if (ck - e3 <= s[3].size()) {
		return s[3][ck - e3 - 1];
	}
	
	return '.';
}

int main () {
	l[0] = s[0].size();
	
	for (int i = 1; i <= 54; i++) {
		l[i] = 2 * l[i - 1] + s[1].size() + s[2].size() + s[3].size();
	}
	
	cin >> q;
	
	while (q--) {
		cin >> n >> k;
		res += F(n, k);
	}
	
	cout << res << endl;
	
	return 0;
}
```


---

## 作者：lyxeason (赞：0)

### 题意
这道题的题义是说，有一个非常长的字符串数组 $f$，字符串数组的递推公式是：

- $f_0= \texttt{What are you doing at the end of the world? Are you busy? Will you save us?}$
- $f_n= \texttt{What are you doing while sending "}+f_{n-1}+ \texttt{"? Are you busy? Will you send "}+f_{n-1}+\texttt{"?}$

现在给出 $q$ 次询问，每个询问形如 ```n k```，要求输出 $f_n$ 的第 $k$ 个字符，如果 $f_n$ 不存在第 $k$ 个字符则输出字符 $\texttt{.}$。

数据范围：$1\le q \le 10,\ 0 \le n \le 10^5,\ 1 \le k \le 10^{18}$

------------
### 算法

拿到这题后，看到 $k$ 的数据范围极大，$n$ 也达到 $1e5$，肯定不能模拟，那么我们就可以采用求 [汉诺塔第 k 步](https://www.luogu.com.cn/problem/U156054) 的思想来做。

首先来画图列举一下在 $f_n$ 中，$k$ 的位置可能有哪几种情况。
![情况](https://cdn.luogu.com.cn/upload/image_hosting/0d24u17t.png)
如图，$k$ 所在的位置可以属于红色、橙色、黄色、绿色、蓝色 $5$ 个区间。

于是，我们就可以用递归的方式求出答案。但要注意的是，如果直接用递推的方式计算 $f_n$ 的长度，$n$ 只要稍微大一点就会爆 long long。不过这题出题人比较良心，虽然长度有可能会爆，但是要求的位置 $k$ 最大只有 $10^{18}$，可以判断只要当前递归中的位置处在红色区间外，且 $f_{n-1}$ 的长度 $>10^{18}$ 就肯定处在橙色区间内，具体见代码。

------------
### 代码
###### 代码里有注释

```cpp


#include <iostream>
#define ll long long

using namespace std;

int Q;
int N;
ll K;
string f0 = " What are you doing at the end of the world? Are you busy? Will you save us?";
string fn = " What are you doing while sending \"\"? Are you busy? Will you send \"\"?";
ll f[100009];  //题目中 f[n] 的长度

void Gen () {  //计算长度
  f[0] = 75;

  for (int i = 1; i < 100001; i++) {
    f[i] = 2 * f[i - 1] + 68;

    if (f[i - 1] < 0 || f[i] > 1e18) {  //如果长度>10^18，就把值设为-1
      f[i] = -1;
    }
  }
}

void Dfs (int n, ll k) {  //求 f[n] 的第 k 位是那个字符
  if (n == 0) {  //f[0]
    cout << f0[k];
    return;
  }

  if (k < 35) {  //红色区间
    cout << fn[k];
    return;
  }
  
  if (f[n - 1] < 0) {  //位置处在红色区间外，且 f[n-1]>1e18 就肯定处在橙色区间内
    Dfs(n - 1, k - 34);
    return;
  }

  if (k > 34 && k < 35 + f[n - 1]) {  //正常橙色区间，继续递归，k 的位置减去在前面的字符数
    Dfs(n - 1, k - 34);
    return;
  }

  if (k > 34 + f[n - 1] && k < 67 + f[n - 1]) {  //黄色区间已知
    cout << fn[k - f[n - 1]];
    return;
  }

  if (k > 66 + f[n - 1] && k < 67 + 2 * f[n - 1]) {  //绿色区间，继续递归，k 的位置减去在前面的字符数
    Dfs(n - 1, k - 66 - f[n - 1]);
    return;
  }

  cout << fn[k - 2 * f[n - 1]];  //蓝色区间已知
}

void In_Solve_Out () {
  Gen();

  cin >> Q;

  while (Q--) {
    cin >> N >> K;
    
    if (K > f[N] && f[N] != -1) {  //不存在第 K 个字符
      cout << ".";
      continue;
    }
    
    Dfs(N, K);
  }

  cout << endl;
}

int main () {
  
  In_Solve_Out();
  
  return 0;
}
```

---

