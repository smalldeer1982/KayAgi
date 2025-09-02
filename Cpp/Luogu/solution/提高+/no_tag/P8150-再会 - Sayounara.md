# 再会 | Sayounara

## 题目背景

「过去的都已经无所谓了吗？」

“还没有达到那种地步。”

「想做的事都已经完成了吗？」

“如今的自己，也好像只能在取舍中前行。”

「道过再会了吗？」

“… 还没有，但我正尝试着。”

> I have
>
> 我仍有
>
> plenty want to say
>
> 无数未道尽的言语
>
> Before
>
> 在离开之前
>
> I leave this world
>
> 在再会之前

## 题目描述

「这是…？」

“啊… 我自己写的日记管理程序。”

「噗… ‘正常人谁写日记啊’，平时的你应该会这样说吧？」

“… 别拿我说笑。”

「好吧好吧。不过看上去你不记得密码了呢？」

“…… 我自有手段。”

「咦…？这什么，恢复软件吗？」

“嗯… 密码可以被表示为一个长为 $n$ 的非负整数序列，**其中每个元素都互不相同** 。这个软件可以执行两种操作：一是，询问一个连续区间的总和减去这个区间最小值的结果；二是，询问一个位置的值。现在我需要找回密码的话…”

「欸？为什么不直接用 $n$ 次第二种操作呢？」

“这是试用版… 所以第二种操作只有两次使用的体验权限… 而且第一种操作似乎也有一定的限制，所以…”

「这… 话说为什么恢复个密码这么麻烦啊？不应该会有‘找回密码’之类方便的机制吗？」

“… 多半还是那个人的安排吧。”

### 简要题意

有一个元素互不相同的非负整数序列 $a$，其长度为 $n$。你可以多次进行以下两种询问之一：

- 给出 $l,r$，得到 $\left(\sum_{k=l}^r a_k\right)-\left(\min_{k=l}^r a_k\right)$。

- 给出 $k$，得到 $a_k$ 的值。这种询问最多只能进行两次。

你需要在尽可能少的询问次数内推断出该序列的内容。

**本题询问均以 $1$ 为初始下标，但你返回答案时需要返回以 $0$ 为初始下标的 `vector`，请留意。**

### 交互说明

本题仅限 C++11 / C++17 提交。你需要实现以下的函数：

```cpp
#include <cstdint>
#include <vector>

std::vector<uint32_t> recover(int n);
```

该函数接收密码长度 $n$，返回还原的密码（返回值应该是一个大小为 $n$ 的 `vector`）。你可以使用以下两个函数

```cpp
#include <cstdint>

uint64_t query(int l, int r);
uint32_t get(int x);
```

其中 `query` 对应题目中的第一种操作，`get` 对应题目中的第二种操作。

下面是一个示例程序（仅演示交互库操作）：

```cpp
#include <cstdint>
#include <vector>

uint64_t query(int l, int r);
uint32_t get(int x);

std::vector<uint32_t> recover(int n) {
	std::vector<uint32_t> ans(n);
	int what = query(1, n), hey = get(1);
	for (int i = 0; i < n; ++i) ans[i] = i + 1;
	return ans;
}
```

题目提供了示例交互库 `lib.cpp`（并非交互库真实实现）。你可以在本地使用命令 `g++ -o code code.cpp lib.cpp` 来编译运行。

## 说明/提示

### 得分细则

本题没有子任务。所有测试点保证 $n=10^6$。

如果你在任何一个测试点中答案错误或超出询问限制，则本题你会得到 0 分的好成绩。

如果你成功通过了所有测试点，记你在所有数据中调用操作一最多一次的次数为 $x$，则你本题的分数为：

$$
\begin{cases}
\frac{60}{e^7-1}\left(e^{10-\max\left\{\frac{x-10^6}{100},3\right\}}-1\right)+40,&x\le 1001000\\
25,&\mathrm{otherwise.}
\end{cases}
$$

# 题解

## 作者：Purslane (赞：9)

# Solution

感觉难点在于如何想到三分。

很明显，如果我们确定了最小值的位置（显然，必须确定最小值的位置，然后找到其具体值），就可以往左右两端拓展，用 $n-1$ 次 `get` 操作即可确定整个数列。

一个自然的想法是用二分，每次看最小值在左区间内还是在右区间内。但是我们很容易察觉到，我们找不到判断最小值在哪个区间内的方法。

于是考虑三分。我们取区间 $[l,r]$ 的两个三等分点 $p_1$ 和 $p_2$，这个区间被分成了 $[l,p_1]$，$[p_1+1,p_2-1]$，$[p_2,r]$ 三个区间。

然后又有一个我感觉想不到的操作。考虑 $\text{query}(l,p_2-1)-\text{query}(l,p_1)$ 和 $\text{query}(p_1+1,r)-\text{query}(p_2,r)$。

很明显，他们的 $\sum$ 项最终结果都是相同的，为 $\sum_{i=p_1+1}^{p_2-1} a_i$。因此如果我们比较两个值的相对关系，我们只需要比较 $\min_{i=l}^{p_2-1} a_i-\min_{i=l}^{p_1} a_i$ 和 $\min_{i=p_1+1}^{r} a_i - \min_{i=p_2}^{r} a_i$。

由于所有数互不相同，我们取三个区间的最小值分别是 $x$，$y$，$z$。他们之间的相对值无非六种情况，作为新时代的 OIer 应该具有坚实的分类讨论基础。于是我们要比较 $\min\{x,y\}-x$ 和 $\min\{y,z\} - z$。

- $x < y < z$，前者为 $0$，后者为 $y-z < 0$。
- $x < z < y$，前者为 $0$，后者为 $0 = 0$。
- $y < x < z$，前者为 $y-x$，后者为 $y-z < y-x$。
- $y < z < x$，前者为 $y-x$，后者为 $y-z > y-x$。
- $z < x < y$，前者为 $0$，后者为 $0 = 0$。
- $z < y < x$，前者为 $y-x$，后者为 $0 > y-x$。

所以考虑最小值在三个区间内的所有情况：

- 在最左边的区间中，必有前者不大于后者。
- 在中间的区间中，必有前者不等于后者。
- 在最右边的区间中，必有前者不小于后者。

然后你发现有一个很头疼的问题：如果我们找到的两个值并不相同，那么我们很容易舍掉最左边或者最右边的一个区间。

但是如果两个值相同，我们如何舍去最中间那个区间呢？

答曰：直接把他们删掉。因为最小值一定不在这里面，所以我们可以忽略不计，把左右区间拼起来即可。

实现的时候考虑搞一个双向链表，然后暴力找三等分点。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
uint64_t query(int l, int r);
uint32_t get(int x);
const int MAXN=1e6+10;
uint32_t nxt[MAXN],pre[MAXN],hd,tl,len;
void del(uint32_t pos) {
	len--;
	uint32_t u=pre[pos],v=nxt[pos];
	nxt[u]=v,pre[v]=u;
	return ;
}
uint32_t get_kth(uint32_t k) {
	uint32_t ans=0;
	ffor(i,1,k) ans=nxt[ans];
	return ans;	
}
void dele(uint32_t l,uint32_t r) {
	vector<uint32_t> aim;
	uint32_t ans=0;
	while(ans<l) ans=nxt[ans];
	while(ans<=r) aim.push_back(ans),ans=nxt[ans];
	for(auto id:aim) del(id);
	return ;	
}

std::vector<uint32_t> recover(int n) {
	vector<uint32_t> ans(n);
	hd=0,tl=n+1,len=n;
	ffor(i,1,n) nxt[i]=i+1,pre[i]=i-1;
	nxt[0]=1,pre[n+1]=n;
	while(len>2) {
		uint32_t l=nxt[hd],r=pre[tl],p1=get_kth(len/3),p2=get_kth(len-len/3+1);
		uint64_t val1=query(l,p2-1)-query(l,p1),val2=query(p1+1,r)-query(p2,r);
		if(val1<val2) dele(p2,r);
		else if(val1>val2) dele(l,p1);
		else dele(nxt[p1],pre[p2]);
	}
	uint32_t mnpos;
	if(len==1) mnpos=nxt[hd],ans[mnpos-1]=get(mnpos);
	else {
		uint32_t pos1=nxt[hd],pos2=pre[tl],val1=get(pos1),val2=get(pos2);
		if(val1<val2) mnpos=pos1,ans[mnpos-1]=val1;	
		else mnpos=pos2,ans[mnpos-1]=val2;
	}
	uint64_t lst=ans[mnpos-1];
	ffor(i,mnpos+1,n) {
		uint64_t val=query(mnpos,i)+ans[mnpos-1];
		ans[i-1]=val-lst,lst=val;	
	}
	lst=ans[mnpos-1];
	roff(i,mnpos-1,1) {
		uint64_t val=query(i,mnpos)+ans[mnpos-1];
		ans[i-1]=val-lst,lst=val;	
	}
	return ans;
}
```

不得不说，交互题属实有点。

---

## 作者：Corzica (赞：3)

如果我们获得了整个串的最小值及其位置，我们显然可以通过 $n$ 次询问得到整个串。

我们现在的问题就是要找到这个最小值。

假设我们的最小值在 $[l,r]$ 这个区间内。如果它的大小在 $2$ 及以下，我们可以直接得到。

否则，我们把这个区间分成三段，分别为 $[l,u],[u+1,v],[v+1,r]$。

设这三个区间的区间和分别为 $a,b,c$，最小值分别为 $x,y,z$。

我们询问 $query(l,v)-query(l,u)$ 和 $query(u+1,r)-query(v+1,r)$。

若 $x$ 为最小值，则两数分别为 $b$ 和 $b+z-min(y,z)$。此时前一个数一定不大于后一个数。

若 $y$ 为最小值，则两数分别为 $b-y+x$ 和 $b-y+z$。两数一定不等。

当 $z$ 为最小值的时候情况和 $x$ 最小时类似，后一个数不小于前一个数。

我们发现，每一次操作一定能排除掉一个区间，反复操作即可得到答案。

询问区间可能不连续，但是不会影响到每一个区间的最小值，所以其实无关大雅。

代码：

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ui unsigned int
using namespace std;
ull query(int l, int r);
ui get(int x);
ui a[1000005];
ull b[1000005];
bool vis[1000006];
inline int solve(int n) {
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) b[++cnt] = i;
	}
	if (cnt == 1) {
		a[b[1]] = get(b[1]);
		return b[1];
	}
	if (cnt == 2) {

		a[b[1]] = get(b[1]), a[b[2]] = get(b[2]);
		if (a[b[1]] < a[b[2]]) return b[1];
		return b[2];
	}
	ui s = cnt / 3, ss = cnt * 2 / 3 ;
	ull u = query(b[1], b[ss]) - query(b[1], b[s]), v = query(b[s] + 1, b[cnt]) - query(b[ss] + 1, b[cnt]);
	if (u == v) {
		for (int i = s + 1; i <= ss; i++) vis[b[i]] = 1;
	} else if (u < v) {
		for (int i = ss + 1; i <= cnt; i++) vis[b[i]] = 1;
	} else {
		for (int i = 1; i <= s; i++) vis[b[i]] = 1;
	}
	return solve(n);
}
vector<ui> recover(int n) {
	vector<ui> ans(n);
	int x = solve(n);
	for (int i = 1; i <= n; i++) {
		if (i < x) b[i] = query(i, x);
		else if (i >= x) b[i] = query(x, i);
	}
	for (int i = 1; i <= n; i++) {
		if (a[i]) {
			ans[i - 1] = a[i];
			continue;
		}
		if (i < x) ans[i - 1] = b[i] - b[i + 1];
		else ans[i - 1] = b[i] - b[i - 1];
	}
	return ans;
}

```

---

## 作者：€€£ (赞：2)

~~作为利用我非故意搞出来的 bug 得到 O(n) 爆标算法的sb觉得写一发这道题题解很重要~~

我们首先考虑这道题的代价计算方式，通过简单化简可得其实我们只要保证总次数 $\le n+300$ 即可得到 $100$ 分的差成绩。

进一步分析发现，如果我们能求出最小值及其所在的位置，那么我们将可以用 $n$ 次操作得到整个序列。

顺着这个方向，我们考虑用 $300$ 次操作得出这个位置。

我们分析 $300$ 的意义，发现是 $\log n \sim \log^2 n$ 之间；由于我们仅需要找出一个位置，这很适合我们学过的二分/三分算法；

于是我们考虑改版三分：

假设有一段区间 $[l,r]$，其三分点是 $s1,s2$，那么我们通过比较 `query(l,s2)-query(l,s1-1)` 与 `query(s1,r)-query(s2+1,r)` 的大小，我们可以得到：

- 如果最小值在 $[s1,s2]$ 中，那么这两个值必定不可能相等；

- 如果最小值在 $[l,s1)$ 中，那么第一个值必定不可能比第二个值大；

- 如果最小值在 $(s2,r]$ 中，那么第二个值必定不可能比第一个值大；

这样，我们可以通过这两个值的关系，排除掉当前约 $\frac{1}{3}$ 的答案；

当最后只剩下 $1 \sim 2$ 个值时，我们直接用 `get` 得到他们的值即可，然后问一遍 `query(i,x)/query(x,i)`，做一遍差分即可（$x$ 是最小值位置）；

「欸，你说这题一开始有什么 bug 能让你O(n)过啊」

“emm……就是你可以询问 `query(0,i)` ，然后差分就可以迅速解决啦”

「欸，那你说出题人是不小心还是故意的啊」

“…多半还是出题人的安排吧。”

~~梦幻联动~~（大雾

Code：

```cpp
# include <cstdint>
# include <vector>
# include <algorithm>
# include <stdio.h>
# define ui uint32_t
# define ull uint64_t
ui ok1[1000010],ok2[1000010],f[1000010],totf;
ui a[1000010];
ull an[1000010];
ull q[1000010];
ui remain=301;
int m,tot=0;
ull query(int l,int r);
ui get(int x);
int sr()
{
	int i,j;
	totf=0;
	tot++;
	int bj=0;
	for(i=1;i<=m;i++)
	{
		if(!ok1[i])
		{
			totf++;
			f[totf]=i;
		}
	}
	if(totf<=2)
	{
		for(i=1;i<=totf;i++)
		{
			a[i]=get(f[i]);
			an[f[i]]=(ull)a[i];
		}
		std::sort(a+1,a+totf+1);
		for(i=1;i<=totf;i++)
		{
			if(an[f[i]]==(ull)a[1])
				return f[i];
		}
		return 0;
	}
	else
	{
		int mi=totf/3;
		int s1=1+mi;
		int s2=totf-mi;
		ull an1=query(1,f[s2])-query(1,f[s1]-1);
		ull an2=query(f[s1],m)-query(f[s2]+1,m);
		remain-=4;
		if(an1==an2)
		{
			for(i=s1;i<=s2;i++)
				ok1[f[i]]=1;
			return sr();
		}
		if(an1>an2)
		{
			for(i=1;i<s1;i++)
				ok1[f[i]]=1;
			return sr();
		}
		if(an1<an2)
		{
			for(i=s2+1;i<=totf;i++)
				ok1[f[i]]=1;
			return sr();
		}
	}
	return sr();
}
std::vector< ui > recover(int n)
{
	m=n;
	int i,j,x,y;
	x=sr();
	for(i=x+1;i<=n;i++)
	{
		q[i]=query(x,i);
		an[i]=q[i]-q[i-1];
	}
	for(i=x-1;i>=1;i--)
	{
		q[i]=query(i,x);
		an[i]=q[i]-q[i+1];
	}
	std::vector< ui > vec;
	for(i=1;i<=n;i++)
		vec.push_back((ui)an[i]);
	return vec;
}

```



---

## 作者：Mirasycle (赞：1)

可以发现由于交互库只能返回 $\sum a_i-\min a_i$ 的结果，最小值被减去了。所以对于区间 $[l,r]$ 其**最小值是一个隐藏信息**，不管再怎么用区间内的数去组合询问，都无法得到最小值。

将上述思想扩展至全局，全局最小值更是不可能由操作一得到。所以我们的有一次询问操作二的机会肯定是留给全局最小值的。同时可以发现，一旦我们得到了全局最小值就一定可以在 $n-1$ 次操作一之后还原整个数组。

所以现在的任务就是用 $301$ 次操作一和 $1$ 次操作二确定序列最小值的位置。

试了很久之后，想起来 [P9721 [EC Final 2022] Inversion](https://www.luogu.com.cn/problem/P9721)，那一题中是通过 $(l,r),(l,r+1),(l-1,r),(l-1,r+1)$ 四个区间的返回值异或在一起得到两个端点的大小关系，这启发我们不一定是要独立地分析每个询问的返回值，可以考虑将询问的返回值通过运算组合在一起。可以**通过类似差分/减法运算使得某个信息暴露出来**。

于是我们考虑试一下 $query(l-1,r)-query(l,r+1)$，看看能否得到 $a_{l-1}$ 和 $a_{r+1}$ 的大小关系。

设 $(l-1,r)$ 和 $(l,r+1)$ 的最小值分别为 $p,q$。如果两者返回值相等，根据元素互不相等，可以得到 $a_{l-1}=p$，$a_{r+1}=q$。如果前者返回值大，可以得出 $p=q$，$a_{l-1}>a_{r+1}$。

我们可以惊奇地发现我们基本得到了 $a_{l-1}$ 和 $a_{r+1}$ 的大小关系，虽然在有的情况不能准确得出。同时可以得到一个更有用的情况，也就是**最小值的分布位置**。第一种情况可以得到最小值在两个端点，第二种情况可以得到最小值在 $[l,r]$。这启发我们不断缩小可能区间来得到最后的最小值位置。

所以我们可以 $\operatorname{solve(l,r)}$ 来找到 $[l,r]$ 的最小值，我们把序列平均分为三段，$[l,s],[s+1,t],[t+1,r]$。然后比较 

$$L=\operatorname{query(l,t)}-\operatorname{query(l,s)}$$
$$R=\operatorname{query(s+1,r)}-\operatorname{query(s+1,t)}$$
列式子分析一下，记录中间区间的和为 $sum$，三个区间的最小值分别为 $m_1,m_2,m_3$。

- $m_1$ 为区间最小值，那么 $L=s$，$R=s+m_3-\min(m_2,m_3)$，故此时 $L\le R$。

- $m_2$ 为区间最小值，那么 $L=s-m_2+m_1$，$R=s-m_2+m_3$，故此时 $L\neq R$。

- $m_3$ 为区间最小值，同理分析可得 $L\ge R$。

我们每次根据 $L,R$ 的大小关系可以舍弃一个区间。当 $L=R$ 的时候，我们舍弃中间区间。当 $L<R$ 的时候我们舍去最右边区间。当 $L>R$ 的时候，我们舍弃最左边区间。
 

因为存在舍弃中间区间的可能，这样子可能会造成序列不连续，但是经过讨论可以发现，中间区间如果在上一步被舍弃，代表最小值不在其中，那么后面的询问带上这个区间也不会造成影响。

如果区间长度等于 $2$，可以用一次操作一和一次操作二来解决。

需要的操作 $1$ 次数大概是 $4\log_{\frac{3}{2}}10^6=136$ 次，符合题目要求。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
typedef long long ll;
uint64_t query(int l, int r);
uint32_t get(int x);
int a[maxn],b[maxn];
vector<uint32_t > ans;
int solve(int cnt){
	if(cnt==1){ ans[a[1]-1]=get(a[1]); return a[1]; }
	if(cnt==2){
		int l=a[1],r=a[2];
		ans[l-1]=get(l),ans[r-1]=get(r);
		return ans[l-1]<ans[r-1]?l:r;
	}
	//[l,s] [s+1,t] [t+1,r]
	int s=cnt/3,t=2*cnt/3;
	ll p=query(a[1],a[t])-query(a[1],a[s]),q=query(a[s]+1,a[cnt])-query(a[t]+1,a[cnt]);
	if(p==q){
		int tot=0;
		for(int i=1;i<=s;i++) b[++tot]=a[i];
		for(int i=t+1;i<=cnt;i++) b[++tot]=a[i];
		for(int i=1;i<=tot;i++) a[i]=b[i];
		return solve(tot);
	}else if(p<q) return solve(t);
	else{
		for(int i=s+1;i<=cnt;i++) a[i-s]=a[i];
		return solve(cnt-s);
	}
}
vector<uint32_t > recover(int n){
	for(int i=1;i<=n;i++) a[i]=i; ans.resize(n);
	int p=solve(n); ll s1=0,s2;
	for(int i=p-1;i>=1;i--){
		s2=query(i,p);
		ans[i-1]=s2-s1; s1=s2;
	} s1=0;
	for(int i=p+1;i<=n;i++){
		s2=query(p,i);
		ans[i-1]=s2-s1; s1=s2;
	}
	return ans;
}
```

---

