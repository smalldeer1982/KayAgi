# [JOIG 2025] 修学旅行 / School Trip

## 题目描述

JOIG 高中有 $3^N$ 名学生，编号从 $1$ 到 $3^N$。

JOIG 高中决定举行一场学校旅行，有两个可能的旅行目的地：阿拉斯加（记为“方案 $\texttt{A}$”）和玻利维亚（记为“方案 $\texttt{B}$”）。学生们决定使用以下的流程确定最终的旅行方案：

- 考虑一个长度为 $3^N$ 的字符串 $S$：如果学生 $i\left(1\le i\le 3^N\right)$ 选择方案 $\texttt{A}$，那么 $S_i$ 为 $\texttt{A}$，否则为 $\texttt{B}$；
- 执行以下操作 $N$ 次：
  - 假设当前 $S$ 的长度为 $X$，考虑一个长度为 $\frac{X}{3}$ 的字符串 $S'$，满足 $S'_j\left(1\le j\le\frac{X}{3}\right)$ 为 $S_{3j-2},S_{3j-1},S_{3j}$ 中出现次数较多的字符（$\texttt{A}$ 或 $\texttt{B}$）；接着将 $S$ 替换为 $S'$；
- 所有操作结束之后，$S$ 将成为一个长度为 $1$ 的字符串（要么为 $\texttt{A}$ 要么为 $\texttt{B}$）；如果 $S$ 为 $\texttt{A}$，那么学校最终选取方案 $\texttt{A}$，否则选取方案 $\texttt{B}$。

初始时，我们使用一个字符串 $T$ 表示每名学生选择哪个方案：如果学生 $i\left(1\le i\le 3^N\right)$ 选择方案 $\texttt{A}$，那么 $T_i$ 为 $\texttt{A}$，否则为 $\texttt{B}$。

之后依次发生了 $Q$ 次事件，第 $k(1\le k\le Q)$ 次事件中，学生 $p_k\left(1\le p_k\le 3^N\right)$ 改变了其选择的方案，即若原来他 / 她选择方案 $\texttt{A}$，那么现在他 / 她选择的方案变为 $\texttt{B}$，反之亦然。

对于 $k=1,2,\ldots,Q$，求出第 $k$ 次事件发生后，按照上述流程，学校会选择哪个旅行方案。

## 说明/提示

#### 【样例解释 #1】

- 在第 $1$ 次事件发生后，确定方案流程中，$S$ 的变化为 $\texttt{ABBBBAABB}\to\texttt{BBB}\to\texttt{B}$，最终选取方案 $\texttt{B}$；
- 在第 $2$ 次事件发生后，确定方案流程中，$S$ 的变化为 $\texttt{ABBBBAAAB}\to\texttt{BBA}\to\texttt{B}$，最终选取方案 $\texttt{B}$；
- 在第 $3$ 次事件发生后，确定方案流程中，$S$ 的变化为 $\texttt{ABBABAAAB}\to\texttt{BAA}\to\texttt{A}$，最终选取方案 $\texttt{A}$。

该样例满足子任务 $2,5$ 的限制。

#### 【样例解释 #2】

该样例满足子任务 $2,4,5$ 的限制。

#### 【样例解释 #3】

该样例满足子任务 $1,2,3,5$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $2,5$ 的限制。

#### 【数据范围】

- $1\le N\le 12$；
- $1\le Q\le 2\times 10^5$；
- $T$ 是长度为 $N$ 且仅包含大写字母 $\texttt{A}$ 和 $\texttt{B}$ 的字符串；
- $1\le p_k\le 3^N(1\le k\le Q)$。

#### 【子任务】

1. （$8$ 分）$N=1$；
2. （$17$ 分）$Q\le 10$；
3. （$22$ 分）$p_k\le 5(1\le k\le Q)$；
4. （$28$ 分）$T$ 中所有字符均为 $\texttt{A}$ 且之后的修改均满足 $p_k\ne p_l(1\le k<l\le Q)$；
5. （$25$ 分）无附加限制。

## 样例 #1

### 输入

```
2 3
ABABBAABB
3
8
4```

### 输出

```
B
B
A```

## 样例 #2

### 输入

```
2 5
AAAAAAAAA
1
2
7
8
5```

### 输出

```
A
A
A
B
B```

## 样例 #3

### 输入

```
1 4
AAB
3
1
2
3```

### 输出

```
A
A
B
B```

## 样例 #4

### 输入

```
3 6
AABABABBABAABABBBBBBAABABAA
4
1
9
3
8
9```

### 输出

```
B
B
B
B
B
A```

# 题解

## 作者：SwiftFlash (赞：2)

## 题意解析

给定一个长度为 $3 ^ N$ 的字符串，需要支持一下两种操作:

- 修改一个字符(`A` 改为 `B`，`B` 改为 `A`)
- 将字符串三位一截，每节替换为出现字符次数较多的字符,直到剩下一个字符,输出这个字符

## 思路

我们注意到，操作 $2$ 中我们将每一次操作的结果画出，可以得出下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/51fjq9ry.png)

~~鼠标画的，勿喷~~

看到它，我想起了一种数据结构：线段树。

我们可以使用线段树来维护每个区间的较多出现的字符，利用线段树进行单点修改和区间查询。

## 具体实现

我们使用一颗三叉树形线段树，我们假设一个节点 $x$ 代表区间$[l,r]$，那么 $x$ 有 $3$ 个子节点,分别是 $3x$，$3x + 1$，$3x + 2$，代表区间$[l,l + \frac{r-l+1}{3} )$，$[l + \frac{r-l+1}{3},l + \frac{2 \times (r-l+1)}{3})$，$[l+\frac{2 \times (r-l+1)}{3},r)$。

其他和线段树的实现一样.

---

## 作者：_Deer_Peach_ (赞：2)

看到这么复杂的题目吓了一跳。

题意简述：

长度为 $3^n$ 的字符串，每 $3$ 个字符为一组，每次把一组改成出现次数较多的字符，知道长度为 $1$ 结束。

思路：

很明显可以用线段树，只不过分成三段维护，只需要把板子改一改就好了（虽然作者调了半天才过样例）。

要改的没多少，说先是节点编号，画图不难发现，节点 $x$ 的三个孩子编号从左到右分别是 $3 \times x - 1$，$3 \times x$，$3 \times x + 1$。

其次就是区间的左右端点，这并不难算。

最后答案就记录在最顶端的节点。

其实没什么好想的，不会线段树可以先看[模版](https://www.luogu.com.cn/problem/P3372)。如果会了应该就没什么问题了。

代码：
```
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
const int N=6e5+5;
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res*=x;
		y>>=1;x*=x;
	}return res;
}
int n,q;
string t;
bool ans[N*4];//1表示B，0表示A
int ls(int x){return x*3-1;}//求左孩子
int ms(int x){return x*3;}//求中间的孩子
int rs(int x){return x*3+1;}//求右孩子
void push_up(int x){ans[x]=(ans[ls(x)]+ans[ms(x)]+ans[rs(x)]>=2);}
void build(int x,int l,int r){//建树
	if(l==r){ans[x]=t[l]-'A';return;}//赋值
	int mid=(r-l+1)/3;//区间长度
	build(ls(x),l,l+mid-1);//左区间
	build(ms(x),l+mid,l+mid*2-1);//中间区间
	build(rs(x),l+mid*2,r);//右区间
	push_up(x);//传递上去
}
void update(int x,int k,int nowl,int nowr){//更新
	if(nowl==nowr){ans[x]=!ans[x];return;}//更新
	int mid=(nowr-nowl+1)/3;//同上
	if(k<=nowl+mid-1)update(ls(x),k,nowl,nowl+mid-	1);
	else if(nowl+mid*2<=k)update(rs(x),k,nowl+mid*2,nowr);
	else update(ms(x),k,nowl+mid,nowl+mid*2-1);
	push_up(x);
}
signed main(){
	IOS;cin>>n>>q;
	n=Pow(3,n);
	cin>>t;t=" "+t; 
	build(1,1,n);
	for(int i=1,x;i<=q;i++){
		cin>>x;
		update(1,x,1,n);
		cout<<(ans[1]?'B':'A')<<endl;
	}
	return 0;
}
```

---

## 作者：Tachibana27 (赞：2)

需要一篇线段树题解！

---

我们发现它的结构于线段树是类似的，于是我们大胆猜想，直接写一个“三叉线段树”上去！

我们知道普通的线段树共有 $\log_2n$ 层，每一个节点维护其下一层两个子节点的信息。那么在本题中，我们同样定义“三叉线段树”为：共有 $\log_3n$ 层，每一个节点维护其三个子节点的信息。

然后我们注意一下子节点的编号。参考普通的线段树：对于节点 $x$，子节点的编号分别为 $2x$ 和 $2x+1$。“三叉线段树”中，对于节点 $x$，子节点分别为 $3x-1$，$3x$ 和 $3x+1$。下面分别简称为“左子”，“中子”和“右子”。

考虑当前节点管辖的区间为 $[l,r]$，那么“左子”的管辖范围为 $[l,l+\frac{r-l}{3}]$，“中子”的管辖范围为 $[l+\frac{r-l}{3}+1,l+\frac{2(r-l)}{3}+1]$，“右子”的管辖范围为 $[l+\frac{2(r-l)}{3}+2,r]$。自己在草稿纸上画一下就好了。

```pushup``` 是朴素的，这里不讲了。

```cpp
#define ls (x*3-1)
//左子
#define ms (x*3)
//中子
#define rs (x*3+1)
//右子
#define lmid (l+((r-l)/3))
#define rmid (l+((r-l)/3*2)+1)
//管辖区间
int n,q;
inline int qpow(int b,int p){
	int ans=1;
	while(p){
		if(p bitand 1)
			ans=ans*b;
		b=b*b;
		p>>=1;
	}
	return ans;
}
bool a[1000086];
bool tr[1000086];
inline void pu(int x){
	int cnt=0;
	if(tr[ls])
		cnt++;
	if(tr[ms])
		cnt++;
	if(tr[rs])
		cnt++;
	tr[x]=(cnt>=2);
	return;
}
void bid(int x,int l,int r){
	if(l==r){
		tr[x]=a[l];
		return;
	}
	bid(ls,l,lmid);
	bid(ms,lmid+1,rmid);
	bid(rs,rmid+1,r);
	pu(x);
	return;
}
void cg(int x,int l,int r,int p){
	if(l>p or r<p)
		return;
	if(l==r){
		tr[x]=not tr[x];
		a[l]=not a[l];
		return;
	}
	cg(ls,l,lmid,p);
	cg(ms,lmid+1,rmid,p);
	cg(rs,rmid+1,r,p);
	pu(x);
	return;
}
int main(){
	std::cin>>n>>q;
	n=qpow(3,n);
	for(int i=1;i<=n;i++){
		char ch;
		std::cin>>ch;
		if(ch=='A')
			a[i]=true;
	}
	bid(1,1,n);//建树
	while(q--){
		int x;
		std::cin>>x;
		cg(1,1,n,x);//修改
		if(tr[1])
			puts("A");
		else
			puts("B");
	}
	return 0;
}
```

---

## 作者：wuenzi (赞：1)

### 建树
我们可以将过程转化成一棵三叉树。

我们对样例进行建树（自下而上）。


![](https://cdn.luogu.com.cn/upload/image_hosting/u172vslt.png)

让后建第二层。

![](https://cdn.luogu.com.cn/upload/image_hosting/pxma5exk.png)

最后确定根。
![](https://cdn.luogu.com.cn/upload/image_hosting/hslaeew2.png)

我们易知**不进行任何事件**时的答案为根。

我们就可以写出建树。
```cpp
char build(int u,int d){
	if(d==n){
		w[cnt]=u;//第 cnt 个人的选择在树中的下标
		return a[u].v=l[cnt++];
	}
	a[u].l=3*u;//左
	a[u].mid=3*u+1;//中
	a[u].r=3*u+2;//右
	map<char,int> v;
	v.clear();
	v[build(3*u,d+1)]++;
	v[build(3*u+1,d+1)]++;
	v[build(3*u+2,d+1)]++;
	if(v['A']>v['B'])return a[u].v='A';
	else return a[u].v='B';
}
```
### 修改
利用上面的 $w$ 数组，我们可以**直接**修改树中结点。

我们先来计算一下样例 $1$ 中的第 $3$ 个询问。
![](https://cdn.luogu.com.cn/upload/image_hosting/ypf88q5w.png)
所以我们直接修改这个节点以及这个节点的所有祖先即可。

最后答案仍然是根节点。

修改的代码如下。
```cpp
char qz(int u){
	map<char,int> v;
	v.clear();
	v[a[3*u].v]++;
	v[a[3*u+1].v]++;
	v[a[3*u+2].v]++;
	if(v['A']>v['B']){
		a[u].v='A';
	}else{
		a[u].v='B';
	}
	if(u==1)return a[u].v;//如果为根，直接返回
	return qz(u/3);
}
```
完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optsize(2)
using namespace std;
int n,Q;
string l;
struct WZOI{
	int l,mid,r;
	char v;
}a[10000005];
int cnt=1;
int w[10000005];
char build(int u,int d){
	if(d==n){
		w[cnt]=u;
		return a[u].v=l[cnt++];
	}
	a[u].l=3*u;
	a[u].mid=3*u+1;
	a[u].r=3*u+2;
	map<char,int> v;
	v.clear();
	v[build(3*u,d+1)]++;
	v[build(3*u+1,d+1)]++;
	v[build(3*u+2,d+1)]++;
	if(v['A']>v['B'])return a[u].v='A';
	else return a[u].v='B';
}
char qz(int u){
	map<char,int> v;
	v.clear();
	v[a[3*u].v]++;
	v[a[3*u+1].v]++;
	v[a[3*u+2].v]++;
	if(v['A']>v['B']){
		a[u].v='A';
	}else{
		a[u].v='B';
	}
	if(u==1)return a[u].v;
	return qz(u/3);
}
signed main(){
	cin>>n>>Q>>l;
	int n3=l.size();
	l=' '+l;
	build(1,0);
	while(Q--){
		int x;
		cin>>x;
		a[w[x]].v=(a[w[x]].v=='A'?'B':'A');
		cout<<qz(w[x]/3)<<endl;
	}
	return 0;
}
```
### 时间复杂度
首先是建树，每个节点遍历 $1$ 次，一共 $3^N$ 个节点，建树复杂度 $\Theta(3^N)$。

然后是修改，修改一共遍历 $N$ 个节点，一共修改 $Q$ 次，修改复杂度 $\Theta(N \times Q)$

所以总复杂度 $\Theta(3 ^ N + N \times Q)$

---

## 作者：XiaoHongChong (赞：1)

### 前置知识
- 线段树（不会的可以做一下[模板题](https://www.luogu.com.cn/problem/P3372)）。
### 正文
这里的操作可以理解成：  
把字符串的每三个字符分为一组，再按照每组的 `A` 和 `B` 的数量决定是哪个字符，每次操作长度缩小 $3$ 倍。  
众所周知，线段树只有两个节点，但是我们可以把它变成 $3$ 个节点。  
首先，需要观察节点的编号：

```
            1
  2         3          4
5 6 7     8 9 10     11 12 13
```
可以发现，节点 $u$ 的左中右节点分别为： $u \times 2 - 1$、$u \times 2$、$u \times 2 + 1$。  
区间的左右断点可以自己算，这里直接给出答案：  
令 $mid = \frac{r - l + 1}3$。  
左区间：$[l, l + mid - 1]$。  
中区间：$[l + mid, l + mid \times  2 - 1]$。  
右区间：$[l + mid \times  2, r]$。  
然后就可以开始写代码了。
### 代码
注意数组大小，不要开小了！
```cpp
//f数组为1表示这个字符是A, 为0表示是B
#include <iostream>
using namespace std;
const int MAX = 8e5 + 5;
int n = 1, nn, q, x, maxx, len;
bool f[MAX];
char a[600000];
void build(int u, int l, int r)
{
	if (l == r)
	{
		f[u] = (a[l] == 'A');
		maxx = max(maxx, u);
		return ;
	}
	int mid = (r - l + 1) / 3;
	build(u * 3 - 1, l, l + mid - 1);
	build(u * 3, l + mid, l + mid * 2 - 1);
	build(u * 3 + 1, l + mid * 2, r);
	f[u] = (f[u * 3 - 1] + f[u * 3] + f[u * 3 + 1] >= 2);
}
void update(int u, int l, int r, int x)
{
	if (l == r)
	{
		f[u] = 1 - f[u];
		return ;
	}
	int mid = (r - l + 1) / 3;
	if (x <= l + mid - 1)
		update(u * 3 - 1, l, l + mid - 1, x);
	else if (l + mid * 2 <= x)
		update(u * 3 + 1, l + mid * 2, r, x);
	else
		update(u * 3, l + mid, l + mid * 2 - 1, x);
	f[u] = (f[u * 3 - 1] + f[u * 3] + f[u * 3 + 1] >= 2);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> nn >> q;
	for (int i = 1; i <= nn; i++)
		n *= 3;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);
	while (q--)
	{
		cin >> x;
		update(1, 1, n, x);
		cout << (f[1] ? 'A' : 'B') << endl;
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

好像最近有次 ABC 出了很相似的问题，感觉很奇怪。

这个看起来很像线段树，所以直接用类似线段树的方法，单点修改全局查询就可以了。可能不同的一点就是三叉线段树，只能按 dfs/bfs 序标号了。

```cpp
#include<iostream>
using namespace std;
int n,m,len;
char a[600010];
int pl[1000010],pr[1000010],cnta[1000010],cntb[1000010],cur;
int c1[1000010],c2[1000010],c3[1000010];
void pushup(int x){
    int ca=0,cb=0;
    if(cnta[c1[x]]>cntb[c1[x]])ca++;
    else cb++;
    if(cnta[c2[x]]>cntb[c2[x]])ca++;
    else cb++;
    if(cnta[c3[x]]>cntb[c3[x]])ca++;
    else cb++;
    cnta[x]=ca,cntb[x]=cb;
}
void build(int x,int l,int r)
{
    pl[x]=l,pr[x]=r;
    if(l==r)
    {
        if(a[l]=='A')cnta[x]=1;
        else cntb[x]=1;
        return;
    }
    int mid1=l+(r-l+1)/3-1;
    int mid2=l+(r-l+1)/3*2-1;
    c1[x]=++cur,build(cur,l,mid1);
    c2[x]=++cur,build(cur,mid1+1,mid2);
    c3[x]=++cur,build(cur,mid2+1,r);
    pushup(x);
}
void change(int x,int p)
{
    if(!x)return;
    int l=pl[x],r=pr[x];
    if(l==p&&r==p)
    {
        cnta[x]^=1,cntb[x]^=1;
        return;
    }
    int mid1=l+(r-l+1)/3-1;
    int mid2=l+(r-l+1)/3*2-1;
    if(p<=mid1)change(c1[x],p);
    else if(p<=mid2)change(c2[x],p);
    else change(c3[x],p);
    pushup(x);
}
int main()
{
    cin>>n>>m;
    len=1;
    for(int i=1;i<=n;i++)len*=3;
    for(int i=1;i<=len;i++)cin>>a[i];
    cur=1;
    build(1,1,len);
    while(m--)
    {
        int x;
        cin>>x;
        change(1,x);
        if(cnta[1]>cntb[1])cout<<'A'<<endl;
        else cout<<'B'<<endl;
    }
    return 0;
}
```

---

## 作者：JZJR_A_0 (赞：1)

## 前置知识

* 线段树

## 题意

现在给你一个 $3^N$ 长的序列，每三个相邻数合成为另一个数，你要动态维护最后的数，要求单点修改。

## 思路

考虑线段树，但是因为我们发现父节点是由三个子节点合并而来的，考虑三叉线段树。

## 实现

按照线段树的方式建树，向上合并即可。

### AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e6+5;
int cnt=0;
struct node{
	int l,r,ls,ms,rs,sum;
}t[N];
int a[N],n,q;
inline void back(int p){
	int as=t[t[p].ls].sum+t[t[p].rs].sum+t[t[p].ms].sum;
	if(as>1)t[p].sum=1;
	else t[p].sum=0;
}
inline int add(){return ++cnt;}
inline void biuld(int l,int r,int p){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].sum=a[l];return ;
	}
	int len=r-l+1;
	t[p].ls=add();
	t[p].ms=add();
	t[p].rs=add();
	biuld(l,l+len/3-1,t[p].ls);
	biuld(l+len/3,l+len/3*2-1,t[p].ms);
	biuld(l+len/3*2,r,t[p].rs);
	back(p);
}
inline void change(int x,int p){
	if(t[p].l==t[p].r){t[p].sum^=1;return ;}
	int len=(t[p].r-t[p].l+1);
	if(x<t[p].l+len/3)change(x,t[p].ls);
	else if(x>=t[p].l+len/3*2)change(x,t[p].rs);
	else change(x,t[p].ms);
	back(p);
}
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	n=pow(3,n);
	for(int i=1;i<=n;i++){
		char s;cin>>s;
		a[i]=s-'A';
	}
	t[1].l=add();
	biuld(1,n,1);
	while(q--){
		int x;cin>>x;
		change(x,1);
		char ans='A'+t[1].sum;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：xuchuhan (赞：1)

一道中等模拟题。下面讲一下我的赛时做法。

首先显然不能对于每次操作，暴力重新算一遍答案，这样总的时间复杂度大约是 $O(3^NQ)$ 的，不能通过。

所以我们换一种思路。我们先定义一层的答案为当前操作得出的 $S'$，然后处理出初始时每一层的答案。举个例子，对于样例 $\texttt{ABABBAABB}$，每一层的答案依次是：

- 第一层：$\texttt{ABABBAABB}$。
- 第二层：$\texttt{ABB}$。
- 第三层：$\texttt{B}$。

同时，存储第 $2$ 到 $N+1$ 层的另外一个信息：对于第 $i$ 层的第 $j$ 个字符 $T_{i,j}$，它在上一层所对应的 $3$ 个字符 $T_{i-1,3j-2},T_{i-1,3j-1},T_{i-1,3j}$ 中，有多少个 $\texttt{A}$，多少个 $\texttt{B}$。用二元组 `pair<int,int>` 存储。

处理完这些信息，我们考虑如何利用这些信息降低 $Q$ 次事件的复杂度。我们发现，一个学生想法的改变，最多影响每一层对应他的字母，大多数字母是不会发生改变的。举个例子。若对于样例 $\texttt{ABABBAABB}$，$S_4$ 发生改变，最多影响 $T_{1,4},T_{2,2},T_{3,1}$ 这 $3$ 个字符。推广来说，一次事件最多影响 $N+1$ 个字符。这启发我们使用单次 $O(N)$ 的复杂度求解每次事件。

具体的，对于每次事件，先修改第一层的答案，从第二层开始，修改当前字符对应的 $\texttt{A}$ 和 $\texttt{B}$ 的数量（即前文的二元组存储的信息），如果 $\texttt{A}$ 和 $\texttt{B}$ 的数量的相对关系没有发生改变，那么不会影响下一层的答案，退出循环；否则会影响下一层的答案，进入到下一层的循环。这样模拟下来可以在 $O(N)$ 的时间内完成单次事件的操作。

仍然利用样例进行举例，若若对于样例 $\texttt{ABABBAABB}$，$S_4$ 发生改变：

- 第一层 $T_{1,4}$ 发生改变，第一层变为 $\texttt{ABAABAABB}$。
- 对应的第二层 $T_{2,2}$ 对应的 $\texttt{A}$ 和 $\texttt{B}$ 的数量从 $1,2$ 变为 $2,1$，相对关系发生改变，$T_{2,2}$ 的值变为 $\texttt{A}$，第二层变为 $\texttt{AAB}$ 进入到下一层。
- 对应的第三层 $T_{3,1}$ 对应的 $\texttt{A}$ 和 $\texttt{B}$ 的数量从 $1,2$ 变为 $2,1$，相对关系发生改变，$T_{3,1}$ 的值变为 $\texttt{A}$，第三层变为 $\texttt{A}$。当前已是最后一层，结束循环。
- 综上，答案从 $\texttt{B}$ 变化为 $\texttt{A}$。

使用代码模拟该过程即可，复杂度 $O(NQ)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=1e6,M=15;
int n,q,len,tlen;
string s;
char st[M][N];
pii in[M][N];
int calc(int x){return (x+2)/3;}//计算x在下一层对应的下标,即为x/3向上取整 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>q>>s;
	len=tlen=s.size(),s=' '+s;
	for(int i=1;i<=len;i++)st[1][i]=s[i];
	for(int T=2;T<=n+1;T++){
		for(int i=1;i<=tlen/3;i++){
			int a=0,b=0;
			if(st[T-1][i*3-2]=='A')a++;else b++;
			if(st[T-1][i*3-1]=='A')a++;else b++;
			if(st[T-1][i*3]=='A')a++;else b++;
			st[T][i]=(a>1?'A':'B'),in[T][i]={a,b};
		}
		tlen/=3;
	}
	//以上为预处理初始信息的操作
	while(q--){
		int id,now=2,flg=0,cun;
		cin>>id,cun=id;
		char tmp=s[id];
		while(now<=n+1){//循环每一层,并修改当前层的信息
			if(tmp=='A'){
				in[now][calc(id)].first--,in[now][calc(id)].second++;
				if(in[now][calc(id)].first==1)st[now][calc(id)]='B';//改变A,B数量的相对关系,修改下一层答案 
				else break;//未改变,退出修改 
			}
			else{//过程同上 
				in[now][calc(id)].first++,in[now][calc(id)].second--;
				if(in[now][calc(id)].first==2)st[now][calc(id)]='A';
				else break;
			}
			now++,id=calc(id);
		}
		cout<<st[n+1][1]<<"\n"; 
		if(s[cun]=='A')s[cun]='B';
		else s[cun]='A';
	}
	return 0;
}
```

---

## 作者：yaoyuchen2021 (赞：1)

# 题目大意
给定一个由 `AB` 组成的长度为 $3^n$ 的字符串，以及 $q$ 次改变，求每次改变后按给定规则生成的字符是 `A` 还是 `B`。

生成规则：每次生成一个长度为原长 $\frac{1}{3}$ 的新字符串，第 $i$ 位是 $S_{3i-2},S_{3i-1},S_{3i}$ 中出现次数较多的字符。容易发现，生成 $n$ 此后长度为 $3^n$ 的字符串变为单个字符。

# 解题思路
暴力的思路就是每次修改后按照规则处理一次字符串，很明显会 T，考虑优化。

可以发现，每次修改一个字符，对旁边一组三个字符不会产生影响（见下图），由此提出优化方法：每次只检查当前字符能影响到的地方，时间复杂度 $O(nq)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/wzyzrtk9.png)

（图片较丑请见谅）

# AC Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
int n,q,x,p[15]={1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441};
string s[15];
char check(int i,int j)//判断当前这格该填什么
{
    int A=0,B=0;
    if(s[i-1][j*3-2]=='A')A++;else B++;
    if(s[i-1][j*3-1]=='A')A++;else B++;
    if(s[i-1][j*3-0]=='A')A++;else B++;
    if(A<2)return 'B';return 'A';
}
signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>n>>q>>s[0];s[0]=' '+s[0];//我选择下标从1开始，与题目相同
    for(int i=1;i<=n;i++)
    {
        s[i]+=' ';
        for(int j=1;j<=p[n-i];j++)
        {
            s[i]+=check(i,j);
        }
    }
    while(q--)
    {
        cin>>x;s[0][x]=131-s[0][x];//131是A+B的ASCII码
        for(int i=1;i<=n;i++)//一层层改上去
        {
            x=(x+2)/3;s[i][x]=check(i,x);
        }
        cout<<s[n][1]<<"\n";//输出
    }
    return 0;
}
```

---

## 作者：DeepSeekR1 (赞：1)

```
     B
  A  B  B
ABA BBA ABB
```

拿一个样例，把它的合成过程画个图，发现它是一个满三叉树。再模拟一下它的修改，发现修改这个叶子只会影响它的祖先，这很像线段树的单点修改。

于是我们现场发明一个三叉线段树，单点修改，区间查询，然后就做完了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
int t[5000006];
int a[600005];
void pushup (int pos) {
    int sum = t[3 * pos - 1] + t[3 * pos] + t[3 * pos + 1];
    if (sum >= 2) {
        t[pos] = 1;
    } else {
        t[pos] = 0;
    }
    return;
}
void build (int l,int r,int pos) {
    if (l == r) {
        t[pos] = a[l];
        return;
    }
    int m1 = l + (r - l + 1) / 3,m2 = l + (r - l + 1) * 2 / 3;
    build(l,m1 - 1,3 * pos - 1);
    build(m1,m2 - 1,3 * pos);
    build(m2,r,3 * pos + 1);
    pushup(pos);
    return;
}
void update (int l,int r,int pos,int q) {
    if (l == r) {
        t[pos] ^= 1;
        return;
    }
    int m1 = l + (r - l + 1) / 3,m2 = l + (r - l + 1) / 3 * 2;
    if (l <= q && q < m1) {
        update(l,m1 - 1,3 * pos - 1,q);
    } else if (m1 <= q && q < m2) {
        update(m1,m2 - 1,3 * pos,q);
    } else {
        update(m2,r,3 * pos + 1,q);
    }
    pushup(pos);
    return;
}
signed main () {
    cin >> n >> q;
    int N = pow(3,n);
    for (int i = 1;i <= N;i++) {
        char c;
        cin >> c;
        a[i] = c - 'A';
    }
    build(1,N,1);
    while (q--) {
        int x;
        cin >> x;
        update(1,N,1,x);
        cout << (char)('A' + t[1]) << endl;
    }
    return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

一道超典分治题（可借用树形数据结构维护）。

根据题意，我们先模拟一下如何决策，不难发现，这就像比赛的淘汰赛一样一层一层进行，且后面的修改是单点的。注意数据范围，序列长 $3^{12}$ 约为 $5×10^5$，于是我们考虑预处理时采用分治或树形数据结构维护，单点修改时向上调整即可。

Code（在此借用树形数据结构维护一下~~本人对线段树比较熟~~）:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
struct Node{
 char c;int l,r;
}a[5000010];
void build(int l,int r,int id)
{a[id].l=l;a[id].r=r;
 if(l==r) 
 {cin>>a[id].c;
  return;
 }
 int m1=l+(r-l+1)/3-1,m2=l+(r-l+1)*2/3-1;
 build(l,m1,id*3-1);build(m1+1,m2,id*3);build(m2+1,r,id*3+1);
 if(a[id*3-1].c==a[id*3].c) a[id].c=a[id*3-1].c;
 else if(a[id*3-1].c==a[id*3+1].c) a[id].c=a[id*3-1].c;
 else a[id].c=a[id*3+1].c;
}
int found(int pl,int id)
{if(a[id].l==a[id].r) return id;
 int m1=a[id].l+(a[id].r-a[id].l+1)/3-1,m2=a[id].l+(a[id].r-a[id].l+1)*2/3-1;
 if(pl<=m1) return found(pl,id*3-1);
 else if(pl<=m2) return found(pl,id*3);
 return found(pl,id*3+1); 
}
void up(int id)
{if(a[id*3-1].c==a[id*3].c) a[id].c=a[id*3-1].c;
 else if(a[id*3-1].c==a[id*3+1].c) a[id].c=a[id*3-1].c;
 else a[id].c=a[id*3+1].c;
 if(id!=1) up((id+1)/3);
}
int main()
{ios::sync_with_stdio(0);cin.tie(0);
 cin>>n>>q;
 build(1,pow(3,n),1);
 while(q--)
 {int pl;cin>>pl;
  int id=found(pl,1);
  a[id].c='B'-a[id].c+'A';
  up((id+1)/3);
  cout<<a[1].c<<'\n';
 }
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11725)

# 题目分析

首先观察到 $1 \le N \le 12$。这样，我们完全可以将每次操作得到的字符串 $S'$ 全部存下来。然后不难看出，修改 $S$ 中的一个字符，最多只会影响到 $S'$ 中的一个字符。因此，我们可以这样做：

首先建一个结构体数组 $st$ 存储每次操作后的字符串 $S$，其中 $st_i$ 存储第 $i$ 次操作前的字符串及相关数据。结构体中包含这个字符串 $S$ 和将原字符串按 $S_j,S_{j+1},S_{j+2}$（其中 $0\le j\le x-3$，$x$ 为 $S$ 的长度）的方式分组后每组 ```A``` 和 ```B``` 的数量。这里定义第 $j$ 组为组内元素为 $S_{3j},S_{3j+1},S_{3j+2}$ 的一组。显然，$st_{i+1}$ 的字符串可以按以下方式构造。设 $S'$ 为 $st_{i+1}$ 的字符串，$S'_i$ 为 $S'$ 的第 $i$ 个字符（从 $0$ 开始），设 $num_{j,A}$ 和 $num_{j,B}$ 分别表示在 $S$ 分组后的第 $j$ 组中 ```A``` 和 ```B``` 的个数，则：

$$ S'_j=\begin{cases}
    A&\text{if }num_{j,A}>num_{j,B}\\
    B&\text{if }num_{j,B}>num_{j,A}
  \end{cases}$$

对于修改操作，设修改 $st_i$ 的字符串 $S$ 的第 $k$ 个位置，那么它一定位于 $st_i$ 的字符串 $S$ 的第 $\lceil \frac{k}{3} \rceil$ 组中。相应地，在 $st_{i+1}$ 的字符串中唯一可能被修改的是第 $\lceil \frac{k}{3} \rceil$ 个位置。具体地，如果修改 $st_i$ 的字符串 $S$ 的第 $k$ 个位置，使得 $st_i$ 的字符串 $S$ 的第 $\lceil \frac{k}{3} \rceil$ 组中 ```A``` 和 ```B``` 数量的大小关系发生了变化，那么 $st_{i+1}$ 的字符串中的第 $\lceil \frac{k}{3} \rceil$ 个位置就要修改，否则不修改并退出循环。若没退出，那么将 $i$ 变成 $i+1$，将 $k$ 变成 $\lceil \frac{k}{3} \rceil$，循环执行即可。

# 代码


```cpp
#include<bits/stdc++.h>
#define N 15
#define M 1000001
using namespace std;
struct area{
	int na,nb;
};
struct str{
	char s[M];
	vector<area>ar;
}st[N];
int main(){
	int n,q,m=1;
	cin>>n>>q>>st[1].s;
	for(int i=0;i<n;i++){
		m*=3;
	}
	int m2=m,t=1;
	while(m2>1){
		int k=0;
		area temp;
		while(k+3<=m2){
			temp.na=temp.nb=0;
			for(int i=k;i<k+3;i++){
				if(st[t].s[i]=='A'){
					temp.na++;
				}
				else{
					temp.nb++;
				}
			}
			st[t].ar.push_back(temp);
			if(temp.na>temp.nb){
				st[t+1].s[k/3]='A';
			}
			else{
				st[t+1].s[k/3]='B';
			}
			k+=3;
		}
		m2/=3;
		t++;
	}
	while(q--){
		int x;
		char change;
		cin>>x;
		if(st[1].s[x-1]=='A'){
			change='B';
		}
		else{
			change='A';
		}
		int arwz=ceil((double)x/3.0),d1,d2;
		if(st[1].ar[arwz-1].na>st[1].ar[arwz-1].nb){
			d1=1;
		}
		else{
			d1=2;
		}
		if(change=='A'){
			st[1].ar[arwz-1].na++;
			st[1].ar[arwz-1].nb--;
		}
		else{
			st[1].ar[arwz-1].nb++;
			st[1].ar[arwz-1].na--;
		}
		st[1].s[x-1]=change;
		for(int i=2;i<=t;i++){
			if(st[i-1].ar[arwz-1].na>st[i-1].ar[arwz-1].nb){
				d2=1;
			}
			else{
				d2=2;
			}
			if(d1==d2){
				break;
			}
			if(st[i].s[arwz-1]=='A'){
				change='B';
			}
			else{
				change='A';
			}
			st[i].s[arwz-1]=change;
			if(i==t){
				break;
			}
			arwz=ceil((double)arwz/3.0);
			if(st[i].ar[arwz-1].na>st[i].ar[arwz-1].nb){
				d1=1;
			}
			else{
				d1=2;
			}
			if(change=='A'){
				st[i].ar[arwz-1].na++;
				st[i].ar[arwz-1].nb--;
			}
			else{
				st[i].ar[arwz-1].nb++;
				st[i].ar[arwz-1].na--;
			}
		}
		cout<<st[t].s[0]<<endl;
	}
	return 0;
}
```

---

## 作者：lilong (赞：0)

读题可以发现，一个大的区间的答案是由三个小的区间的答案决定的。同时又要支持单点修改，因此可以用一个数据结构维护，比如线段树。在这个线段树中，每个非叶子节点有三个子节点。先建好原始的树，修改时定位到叶子节点，再向上更新答案即可，与普通线段树的操作类似。

时间复杂度 $O(n+q\log n)$。


```cpp
#include <iostream>
#include <cstdio>
#define N 5000001

using namespace std;

struct T
{
	int s1,s2,s3,v;
}t[N];

int n = 1,a[N],tot = 1;

void pushup( int u )
{
	int cnt[2] = {0};
	cnt[t[t[u].s1].v] ++,cnt[t[t[u].s2].v] ++,cnt[t[t[u].s3].v] ++;
	if( cnt[0] > cnt[1] ) t[u].v = 0;
	else t[u].v = 1;
}

void build( int u , int l , int r )
{
	if( l == r )
	{
		t[u].v = a[l];
		return;
	}
	t[u].s1 = ++ tot;t[u].s2 = ++ tot,t[u].s3 = ++ tot;
	int len = ( r - l + 1 ) / 3;
	build( t[u].s1 , l , l + len - 1 );
	build( t[u].s2 , l + len , r - len );
	build( t[u].s3 , r - len + 1 , r );
	pushup( u );
}

void update( int u , int l , int r , int p , int v )
{
	if( l == r )
	{
		t[u].v = v;
		return;
	}
	int len = ( r - l + 1 ) / 3;
	if( p <= l + len - 1 ) update( t[u].s1 , l , l + len - 1 , p , v );
	else if( p >= r - len + 1 ) update( t[u].s3 , r - len + 1 , r , p , v );
	else update( t[u].s2 , l + len , r - len , p , v );
	pushup( u );
	return;
}

int main()
{
	int T,ti,k;
	string s;
	cin >> ti >> T;
	cin >> s;
	while( ti -- )
		n *= 3;
	for( int i = 1 ; i <= n ; i ++ )
		a[i] = s[i - 1] - 'A';
	build( 1 , 1 , n );
	while( T -- )
	{
		cin >> k;
		update( 1 , 1 , n , k , 1 - a[k] );
		a[k] = 1 - a[k];
		putchar( t[1].v + 'A' );putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：MathCore (赞：0)

## 题目理解
需要根据学生的选择确定学校的修学旅行方案。

开始时，所有学生的选择形成一个字符串，每次操作将字符串每三个一组，取多数作为新字符，经过 $N$ 次操作后得到最终结果。

每次修改一个学生的选择后，需要立即输出新的结果。

## 解题思路

把整个投票过程看成树状结构：
- 第 $0$ 层：原始选择字符串，共 $3^N$ 个节点。
- 第 $k$ 层：由第 $k-1$ 层每三个节点合并为一个节点，表示该组的多数结果，共 $3^{N-k}$ 个节点。
- 第 $N$ 层：根节点，最终选择的方案。

每次修改底层节点后，只需更新其到根节点的路径上的父节点即可，这样就避免了大量修改。

所以我们可以先预处理（所有层的节点值）：
- 初始化第 $0$ 层：就是原始字符串。
- 计算更高层：第 $k$ 层的每个节点 $i$，统计第 $k-1$ 层中三个子节点（$3i$, $3i+1$, $3i+2$）的多数结果，存入现在的这一层的节点 $i$ 就可以了。

接下来就来看更新了，每次修改后，从下往上更新路径：
- 修改底层节点值。
- 计算当前父节点的新值。
- 若新值与旧值相同，停止更新；否则，就得继续处理更高层。

## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=12+5, SIZE=531441+5;
int n,q;
string t;
char val[N][SIZE];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>q;
	cin>>t;
	for(int i=0;i<pow(3,n);++i){
		val[0][i]=t[i];
	}
	for(int k=1;k<=n;++k){
		for(int i=0;i<SIZE;++i){
			int cnt=0;
			if(val[k-1][3*i]=='A')cnt++;
			if(val[k-1][3*i+1]=='A')cnt++;
			if(val[k-1][3*i+2]=='A')cnt++;
			val[k][i]=(cnt>=2)?'A':'B';
		}
	}
	while(q--){
		int p;
		cin >> p;
		p--;
		val[0][p]=(val[0][p]=='A')? 'B' : 'A';
		int pos=p;
		for(int k=0;k<n;++k){
			int fa=pos/3;
			int cnt=0;
			if(val[k][3*fa]=='A')cnt++;
			if(val[k][3*fa+1]=='A')cnt++;
			if(val[k][3*fa+2]=='A')cnt++;
			char c=(cnt>=2)?'A':'B';
			if(val[k+1][fa]==c){
				break;
			}
			val[k+1][fa]=c;
			pos=fa;
		}
		cout<<val[n][0]<<'\n';
	}
	return 0;
}
```

## 复杂度

时间复杂度：$O(n \times 3^n + N \times Q)$。
- $\text{val}$ 数组初始化。
- $Q$ 次询问与更新。

---

## 作者：andycode (赞：0)

看没有题解，交一发。

[题目传送门](https://www.luogu.com.cn/problem/P11725)
## 思路
看到题面容易想到用线段树做，但是这道题要用一个形状为满三叉树的线段树，这样才方便统计答案。

首先来看节点的编号，从上到下，从左到右依次给树上的节点进行编号，容易发现，设一个非叶子节点的编号为 $x$，则它的三个儿子节点的编号为 $3x-1,3x,3x+1$，配一张图方便大家理解（图微丑，轻喷）。
![](https://cdn.luogu.com.cn/upload/image_hosting/l5gcxix2.png)
所以在建树和修改时，就可以直接算出子节点的编号。

剩下的就和线段树差不多了，直接上代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e6+6;//数组开大一点
int n,q;
bool t[N];
char s[N];
void build(int cur,int l,int r){//建树
    if(l==r){
        t[cur]=s[l]-'A';//0表示A,1表示B
        return;
    }
    int mid1=l+(r-l+1)/3-1,mid2=l+2*(r-l+1)/3-1;
    //将区间平均分成三部分
    build(cur*3-1,l,mid1);
    build(cur*3,mid1+1,mid2);
    build(cur*3+1,mid2+1,r);
    t[cur]=(t[cur*3-1]+t[cur*3]+t[cur*3+1]>1);
    //如果1的个数大于1，则B多，否则A多
}
void modify(int cur,int l,int r,int x){//单点修改
    if(l==r && l==x){
        t[cur]^=1;//修改
        return;
    }
    int mid1=l+(r-l+1)/3-1,mid2=l+2*(r-l+1)/3-1;
    if(x<=mid1)
        modify(cur*3-1,l,mid1,x);
    else if(x<=mid2)
        modify(cur*3,mid1+1,mid2,x);
    else
        modify(cur*3+1,mid2+1,r,x);
    t[cur]=(t[cur*3-1]+t[cur*3]+t[cur*3+1]>1);
    //重新统计答案
}
int main(){
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    n=strlen(s+1);
    build(1,1,n);
    while(q--){
        int p;
        scanf("%d",&p);
        modify(1,1,n,p);
        printf("%c\n",t[1]+'A');//t[1]为最终的结果输出
    }
    return 0;
}
```

---

## 作者：Luogu_916767 (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/P11725)

### 题目

JOIG 高中有 $3^N$ 名学生，编号从 $1$ 到 $3^N$。

会给你一个长度为 $3^N$ 的字符串，每次操作将此字符串 $3$ 位一截，每节替换为这 $3$ 位中出现次数较多的那个字符，重复此操作，直到只剩下 $1$ 位。

### 思路分析

通过类似线段树的方式，记录一个字符串，比如样例 $1$：

### 输入 #1

```
2 3
ABABBAABB
3
8
4
```

我们将这个字符串利用类似线段树的方式存起来，只不过是 $3$ 位一截。大概长这样：![1](https://cdn.luogu.com.cn/upload/image_hosting/bz97hkif.png)

然后我们每次改变一个值，就只需要改变其上方的值。

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;


int n,q;
string s;
int sum;
int x;
char ch[531445];

char fun(int sum){
    int a=0,b=0;
    if(ch[sum*3-1] == 'A'){
        a ++ ;
    }else{
        b ++ ;
    }
    if(ch[sum*3] == 'A'){
        a ++ ;
    }else{
        b ++ ;
    }
    if(ch[sum*3+1] == 'A'){
        a ++ ;
    }else{
        b ++ ;
    }
    if(a > b)return 'A';
    else return 'B';
}

int p(int u){
    if(u%3==1){
        return u/3;
    }else if(u%3==2){
        return u/3+1;
    }else{
        return u/3;
    }
}

void work(int u){
    if(u == 0)return ;
    ch[u] = fun(u);
    work(p(u));
}

int main(){
    cin>>n>>q;
    cin>>s;
    n = s.size();
    while(n){
        n/=3;
        sum += n;
    }
    for(int i = 1; i <= sum; i ++ )ch[i] = ' ';
    for(int i = 1; i <= s.size(); i ++ ){
        ch[sum+i] = s[i-1];
    }
    for(int i = sum; i >= 1; i -- ){
        ch[i] = fun(i);
    }
    // for(int i = 1; i <= sum+s.size(); i ++ ){
    //     cout<<ch[i];
    // }
    // cout<<"|\n";
    for(int i = 1; i <= q; i ++ ){
        cin>>x;
        x = x + sum;
        if(ch[x] == 'A')ch[x] = 'B';
        else ch[x] = 'A';
        x = p(x);
        work(x);
        cout<<ch[1]<<"\n";
        // cout<<sum;
        // for(int i = 1; i <= sum+s.size(); i ++ ){
        //     cout<<ch[i];
        // }
        // cout<<"|\n";
    }
}
```

---

## 作者：shuqiang (赞：0)

这题其实就是实现线段树的单点修改和整体查询，只不过是用三叉树实现，而不是二叉树。

首先，我们要构建这棵树。

这里由于是三叉树，所以我们设 $u$ 代表区间 $[l,r]$，的左儿子为 $3u$，中儿子是 $3u+1$，右儿子是 $3u+2$，然后区间长度就是 $r-l+1$，所以三个儿子分别代表区间的长度为 $\frac{r-l+1}{3}$，所以可以求出左儿子代表的区间是 $[l,l+\frac{r-l+1}{3})$，中儿子代表的区间是 $[l+\frac{r-l+1}{3},l+\frac{2(r-l+1)}{3})$，右儿子代表的区间是 $[l+\frac{2(r-l+1)}{3},r]$。

```cpp
void merge(int u){
	int cnt1 = 0, cnt2 = 0;
	if(a[u*3]) cnt1++;
	else cnt2++;
	if(a[u*3+1]) cnt1++;
	else cnt2++;
	if(a[u*3+2]) cnt1++;
	else cnt2++;
	a[u] = (cnt1 > cnt2);
}

void build(int u, int l, int r){
	if(l == r){
		a[u] = s[l-1] - 'A';
		return;
	}
	int mid1 = l+(r-l+1)/3-1, mid2 = l+((r-l+1)/3)*2-1;
	build(u*3, l, mid1);
	build(u*3+1, mid1+1, mid2);
	build(u*3+2, mid2+1, r);
	merge(u);
}
```

这里，merge 函数是合并三个儿子，build 函数是建树。

然后，我们要实现单点修改。

单点修改只需要先判断修改点在哪个区间内，然后如果区间长度为 1，就修改。

```cpp
void update(int u, int l, int r, int x){
	if(l == r){
		a[u] ^= 1;
		return;
	}
	int mid1 = l+(r-l+1)/3-1, mid2 = l+((r-l+1)/3)*2-1;
	if(x <= mid1) update(u*3, l, mid1, x);
	else if(x <= mid2) update(u*3+1, mid1+1, mid2, x);
	else update(u*3+2, mid2+1, r, x);
	merge(u);
}
```

最后是主程序，因为线段树的根节点就代表所有区间合并的结果，所以查询时直接输出根节点即可，时间复杂度 $\mathcal{O}(nq)$，可以通过。

```cpp
#include<iostream>
#include<string>

using namespace std;

const int N = 2e6 + 10;
int n, q, p; bool a[N];
string s;

void merge(int u){
	int cnt1 = 0, cnt2 = 0;
	if(a[u*3]) cnt1++;
	else cnt2++;
	if(a[u*3+1]) cnt1++;
	else cnt2++;
	if(a[u*3+2]) cnt1++;
	else cnt2++;
	a[u] = (cnt1 > cnt2);
}

void build(int u, int l, int r){
	if(l == r){
		a[u] = s[l-1] - 'A';
		return;
	}
	int mid1 = l+(r-l+1)/3-1, mid2 = l+((r-l+1)/3)*2-1;
	build(u*3, l, mid1);
	build(u*3+1, mid1+1, mid2);
	build(u*3+2, mid2+1, r);
	merge(u);
}

void update(int u, int l, int r, int x){
	if(l == r){
		a[u] ^= 1;
		return;
	}
	int mid1 = l+(r-l+1)/3-1, mid2 = l+((r-l+1)/3)*2-1;
	if(x <= mid1) update(u*3, l, mid1, x);
	else if(x <= mid2) update(u*3+1, mid1+1, mid2, x);
	else update(u*3+2, mid2+1, r, x);
	merge(u);
}

int main(){
	cin >> n >> q >> s;
	build(1, 1, s.size());
	while(q--){
		cin >> p;
		update(1, 1, s.size(), p);
		cout << (char)('A' + a[1]) << '\n';
	}
	return 0;
}

```

---

