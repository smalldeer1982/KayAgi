# [POI 2010] MOT-Monotonicity 2

## 题目描述

本题是来自 POI 2010 第三阶段的[单调性](https://www.luogu.com.cn/problem/P3541)一题的加强版，但并没有在那次比赛中被使用。

**译自 POI 2010 「[Monotonicity 2](https://szkopul.edu.pl/problemset/problem/0_pcwjQ6no8LDss0IWNLbb2_/site/?key=statement)」**

对于一个整数序列 $a_1, a_2, ..., a_n$，我们定义其“单调序列"为一个由 $<$，$>$ 和 $=$ 组成的符号序列 $s_1, s_2, ... s_{n-1}$，其中符号 $s_i$ 表示 $a_i$ 和 $a_{i+1}$ 之间的关系。例如，数列 $2, 4, 3, 3, 5, 3$ 的单调序列为 $<, >, =, <, >$。

对于整数序列 $b_1, b_2, ..., b_{n+1}$ 以及其单调序列 $s_1, s_2, ..., s_n$，如果符号序列 $s_1', s_2', ..., s_k'$ 满足对所有 $1 \le i \le n$ 有 $s_i = s_{((i - 1) \bmod n) + 1}'$，我们就说序列 $s_1, s_2, ..., s_n$ 「实现」了序列 $s_1', s_2', ..., s_k'$。也就是说，序列 $s_1, s_2, ..., s_n$ 可以通过重复多次 $s_1', s_2', ..., s_k'$ 序列并删除一个后缀得到。例如，整数数列 $2, 4, 3, 3, 5, 3$ 至少实现了以下符号序列：
* $<, >, =$
* $<, >, =, <, >$
* $<, >, =, <, >, <, <, =$
* $<, >, =, <, >, =, >, >$

给定一个整数序列 $a_1, a_2, ..., a_n$ 以及一个单调序列 $s_1, s_2, ..., s_k$，求出原整数序列最长的子序列 $a_{i_1}, a_{i_2}, ..., a_{i_m} (1 \le i_1 \lt i_2 \lt ... \lt i_m \le n)$ 使得前者的单调序列实现后者的符号序列。

## 说明/提示

对于 $100\%$ 的数据， $1 \le n \le 500000,1 \le k \le 500000 , 1 \le a_i \le 1000000 , s_j \in \{<, >, =\}$ 。

感谢 [本帖](https://www.luogu.com.cn/discuss/67056) 提供的 SPJ。翻译来自于 [LibreOJ](https://loj.ac/p/3009)。

## 样例 #1

### 输入

```
7 3
2 4 3 1 3 5 3
< > =```

### 输出

```
6
2 4 3 3 5 3```

# 题解

## 作者：q234rty (赞：8)

安利窝的[博客](https://www.q234rty.top/2019/02/10/loj3009/)

相信很多人看到这道题的第一反应和窝一样：这不是水题吗，只要记 $f(i)$ 表示下标以 $i$ 结尾的最长合法子序列长度，转移树状数组优化一下就行了。

还有一些人可能觉得这道题需要在状态中记录长度 $\bmod k$，于是得到了优秀的 $O(nk\log n)$ 或 $O(nk)$ 做法。

第一反应觉得这道题是水题之后可能会觉得不对劲，DP 需要最优子结构，而这个 DP 看起来并不满足呀。

然而，这个 DP 确实是满足最优子结构的，为什么呢？

（网上的题解大都没写证明，[neither_nor](https://blog.csdn.net/neither_nor/article/details/52557379) 写了证明但窝看不懂，于是窝决定写一下用谷歌翻译看[波兰文官方题解](https://oi.edu.pl/static/attachment/20110704/oi17.pdf)（在 P152）的成果）

就是要证下标以 $i$ 结尾的最长合法子序列，一定可以由某个下标以 $j<i$ 结尾的最长合法子序列接上 $i$ 得到。

不失一般性，设下标以 $n$ 结尾的最长合法子序列第一个不满足这个条件，再设 $m$ 为这个子序列的上一个下标。

设 $b_1,b_2,\cdots,b_{f(m)}$ 为下标以 $m$ 结尾的最长合法子序列对应的下标序列，显然 $b_{f(m)}=m$，设 $k=f(n)$。

因为 $n$ 继承的不是 $m$ 的最优解，所以 $k-1<f(m)$，即 $f(m)\geq k$。

讨论：

- $a_m=a_n$，这时 $b_1,b_2,\cdots,b_{f(m)-1},n$ 长度为 $f(m) \geq k$，显然为一个不会更劣的解。
- $a_m<a_n$，这就是说 $s_{k-1}=``<"$，继续讨论：
  - $a_{b_{k-1}}<a_n$，那么 $b_1,b_2,\cdots,b_{k-1},n$ 长度为 $k$，不会更劣。
  - $a_{b_{k-1}}\geq a_n$，我们有 $a_{b_{k-1}}<a_{b_k}$，但是 $a_{b_{k-1}}\geq a_n>a_m$，也即一定存在一个 $w\geq k$ 满足 $a_{b_w}>a_{b_{w+1}}$，也即 $s_{w}=``>"$，我们取第一个这样的 $w$，于是 $\forall i \in [k,w), a_{b_i}\leq a_{b_{i+1}}$，又 $a_{b_{k-1}}<a_{b_k}$，于是 $a_{b_w}>a_{b_{k-1}}\geq a_n$，于是 $b_1,b_2,\cdots,b_{w},n$ 长度为 $w+1>k$，更优。
- $a_m>a_n$，同理得证。

这样就证完啦。

使用两个树状数组分别维护下一个是大于和小于的情况，等于直接用数组维护。

时间复杂度 $O(n\log n)$。

[Code](https://github.com/q234rty/OJ-Codes/blob/master/LibreOJ/3009.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAXSIZE=10000020;
int bufpos;
char buf[MAXSIZE];
#define NEG 0
void init(){
	#ifdef LOCAL
		freopen("3009.txt","r",stdin);
	#endif
	buf[fread(buf,1,MAXSIZE,stdin)]='\0';
	bufpos=0;
}
#if NEG
int readint(){
	bool isneg;
	int val=0;
	for(;!isdigit(buf[bufpos]) && buf[bufpos]!='-';bufpos++);
	bufpos+=(isneg=buf[bufpos]=='-');
	for(;isdigit(buf[bufpos]);bufpos++)
		val=val*10+buf[bufpos]-'0';
	return isneg?-val:val;
}
#else
int readint(){
	int val=0;
	for(;!isdigit(buf[bufpos]);bufpos++);
	for(;isdigit(buf[bufpos]);bufpos++)
		val=val*10+buf[bufpos]-'0';
	return val;
}
#endif
char readchar(){
	for(;isspace(buf[bufpos]);bufpos++);
	return buf[bufpos++];
}
int readstr(char* s){
	int cur=0;
	for(;isspace(buf[bufpos]);bufpos++);
	for(;!isspace(buf[bufpos]);bufpos++)
		s[cur++]=buf[bufpos];
	s[cur]='\0';
	return cur;
}
const int maxn=1000002;
inline void tense(pii &x,pii y){
	if (x<y)
		x=y;
}
struct bit{
	int n;
	pii t[maxn];
	void add(int p,pii v){
		for(;p<=n;p+=p&-p)
			tense(t[p],v);
	}
	pii query(int p){
		pii ans;
		for(;p;p-=p&-p)
			tense(ans,t[p]);
		return ans;
	}
}b1;
struct tib{
	int n;
	pii t[maxn];
	void add(int p,pii v){
		for(;p;p-=p&-p)
			tense(t[p],v);
	}
	pii query(int p){
		pii ans;
		for(;p<=n;p+=p&-p)
			tense(ans,t[p]);
		return ans;
	}
}b2;
inline pii inc(pii x){
	x.first++;
	return x;
}
int a[maxn],dp[maxn],lst[maxn],stk[maxn];
pii qwq[maxn];
char s[maxn];
int main(){
	init();
	int n=readint(),k=readint();
	for(int i=1;i<=n;i++)
		a[i]=readint();
	for(int i=1;i<=k;i++)
		s[i]=readchar();
	b1.n=b2.n=maxn-1;
	int ans=0;
	for(int i=1;i<=n;i++){
		pii lol;
		tense(lol,inc(b1.query(a[i]-1)));
		tense(lol,inc(b2.query(a[i]+1)));
		tense(lol,inc(qwq[a[i]]));
		dp[i]=lol.first,lst[i]=lol.second;
		// printf("dp[%d]=%d lst[%d]=%d\n",i,dp[i],i,lst[i]);
		lol.second=i;
		char now=s[(dp[i]-1)%k+1];
		if (now=='=')
			tense(qwq[a[i]],lol);
		else if (now=='<')
			b1.add(a[i],lol);
		else b2.add(a[i],lol);
		// printf("dp[%d]=%d lst[%d]=%d\n",i,dp[i],i,lst[i]);
		if (dp[i]>dp[ans])
			ans=i;
	}
	printf("%d\n",dp[ans]);
	int cur=0;
	while(ans){
		stk[++cur]=ans;
		ans=lst[ans];
	}
	for(int i=cur;i;i--)
		printf("%d ",a[stk[i]]);
}
```

---

## 作者：A_Sunny_Day (赞：6)

## POI 2010 MOT-Monotonicity 2

​	题目链接：[POI2010 MOT-Monotonicity 2](https://www.luogu.com.cn/problem/P3506)

---

​	考虑 dp，二维 dp 十分好想，但是二维 dp 无论怎么优化最快也只能达到 $O(n\times k\times\log(n))$，那么二维 dp 的想法只能被舍弃，我们肯定立马想到不用二维，设 $f_i$ 表示以  $i$ 为结尾的，所能形成满足条件的最长子序列的长度。可是这么定义状态能不能满足**最优子结构**这个性质呢。

​	如果满足**最优子结构**这个性质，就说明**从最优解转移一定不比非最优解转移劣**。

​	下面我们证明这个状态满足**最优子结构**：

​	我们采取反证法，假设现在我们正在求 $f_i$。$\forall j\in[1,i-1]$，我们假设 $f_j=x$，和一个比 $x$ 短，以 $j$ 为结尾的序列结尾再添上一个 $i$ 就构成了长度为 $f_i$ 的序列。即 $f_i$ 不是由 $f_j$ 这个最优解添上一个 $i$ 获得的，而是由一个长度为 $y$ 的非最优解序列获得的。那么根据我们的假设，有 $x>y$。我们设 $\text{long}$ 序列为长度为 $x$ 的，以 $j$ 为结尾的最优解序列，$\text{short}$ 序列为长度为 $y$ 的，以 $j$ 为结尾的非最优解序列，那么假设就是 $f_i$ 是由 $i$ 继承 $\text{short}$ 序列得到序列的长度 ，而且 $f_i$ 从某个最优解转移来的答案劣于由 $\text{short}$ 转移来的答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/l284n7i8.png)

​	那么根据假设我们有 $f_i=y+1,x>y$。同时还有以下推论：

 + 位置 $x$ 与 位置 $y$ 的符号不同。

   如果他们相同的话，由于两个位置上的数值同为 $a_j$ 那么 $\text{long}$ 序列可以替代 $\text{short}$ 序列，因为如果 $a_i$ 能接在 $\text{short}$ 后面就一定能接在 $\text{long}$ 后面，而 $x+1>y+1$ 显然，使用 $\text{long}$ 序列更优，所以如果我们要满足我们的假设，$a_i,a_j$ 就只能满足 $y$ 后的符号而不满足 $x$ 后的符号。

+ $a_i$ 与 $a_j$ 不相等。

  如果相等，我们继续分类讨论，若 $x$ 后符号为 $\text{=}$ 则选 $\text{long}$ 序列转移。若 $x$ 后符号不为 $\text{=}$ 由于 $a_i=a_j$ 那么我们可以用 $a_i$ 代替 $a_j$ 得到一个长度为 $x$ 的序列，即通过 $\text{long}$ 里 $j$ 的前一个转移过来，而 $x\ge y+1$ 所以 $a_i=a_j$ 时，从最优解转移一定不劣。

+ 位置 $y$ 的位置不是 $\text{=}$。

  根据上述两推论得到。

那么不满足上述推论的情况就可以从最优解转移，我们继续探讨满足上述三种推论的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/k13x3it6.png)

由于 $x>y$ 所以在 $\text{long}$ 序列里，我们可以找到一个节点 $k$ 使得 $f_k=y$。这样我们又有结论：

+ $a_i,a_k$ 不能满足 $y$ 位置后符号的关系。

  如果满足，那么从 $f_k$ 转移过来的答案不劣于 $\text{short}$  转移过来的答案，这与我们的假设不符。

+ 如果 $x$ 位置的符号是 $\text{<}$，那么 $y$ 位置的符号只能是 $\text{>}$。

  因为根据之前的推论 $x,y$ 位置符号不同，且 $y$ 位置的符号不能是 $\text{=}$ 号。

  然后我们顺着这种情形推下去，得到 $a_k<a_i<a_j$ （$a_k,a_i$ 不满足符号而 $a_i,a_j$ 满足），又因为位置 $y$ 的符号是 $\text{>}$。那么存在一个 $a_l(k<l\le j)$ 且 $l$ 后的符号一定是 $\text{<}$，如果没有一个 $l$ 后的符号是  $\text{<}$ 那么 $a_k,a_j$ 的关系应该是 $a_k\ge a_i$。这与上述情况相违背。那么既然存在这样的 $l$，那我们取第一次出现的 $l$ 就能保证 $l$ 前的符号都是 $\text{>},\text{=}$,就有 $a_k\ge a_l<a_j$ 即 $a_l<a_k<a_i<a_j$，又 $l$ 后的符号为 $\text{<}$ 那么 $f_i$ 可以由 $f_l$ 转移来，而 $f_l\ge f_k+1=y+1$，所以 $f_i\ge y+2>y+1$。因此在这种情况中，$f_i$ 从某个最优解转移过来反而更优。

+ 如果 $x$ 位置的符号是 $\text{=}$，那么 $y$ 位置的符号只能是 $\text{>},\text{<}$。

  先看 $y$ 位置为 $\text{>}$ 的情况。发现这种情况于上述情况相同（因为在上面那种情况的推导中 $x$ 位置的符号没有出现）。

  再看 $y$ 位置为 $\text{<}$ 的情况（其实这里与上面那个情况刚好相反，将上述推导符号反一反就可以得到，这里有兴趣的读者可以看，因为过程雷同也可以跳过）

  有 $a_k>a_i>a_j$ （$a_k,a_i$ 不满足而 $a_i,a_j$ 满足），又 $y$ 位置的符号是 $\text{<}$ 那么一定存在 $a_l(k<l\le j)$ 满足 $l$ 位置后的符号为 $\text{>}$，否则 $a_k,a_j$ 的关系应该是 $a_k\le a_j$ 这与上述情况不符。所以 $l$ 一定存在，我们取第一次出现的 $l$，就能满足 $l$ 前的符号全是 $\text{<},\text{=}$ 那么有 $a_k\le a_l>a_i$，又 $l$ 后的符号是 $\text{>}$，那么 $f_i$ 可以由 $f_l$ 转移而来，而 $f_l\ge f_k+1\ge y+1$，则 $f_i\ge y+2>y+1$ ，那么这种情况下也是用最优解转移过来更优。

+ 如果 $x$ 位置的符号是 $\text{>}$ 那么 $y$ 位置的符号只能是 $\text{<}$  这与上述情况一致（因为 $x$ 位置的符号没有在推导出现，也就没有影响）

​    综上所述，$f_i$ 从之前的最优解转移过来的答案一定不劣，甚至更优。那么有一个显然的 $O(n^2)$ 的 dp。转移式为：
$$
dp_i=\left\{
\begin{aligned}
&dp_j+1(temp[dp_j]='\text{<}',a_i<a_j)\\
&dp_j+1(temp[dp_j]='\text{>}',a_i>a_j)\\
&dp_j+1(temp[dp_j]='\text{=}',a_i=a_j)\\
\end{aligned}
\right.
$$
​	然后取个极值就好了。那么优化也是显然的，我们开两个树状数组，分别记录前缀最大值和后缀最大值，然后用数组记录一下相等的权值的 $dp_i$ 的最大值。这题的主要难点就是想到一维 dp 的可行性。

代码如下：

```cpp
#include<bits/stdc++.h>
#define lowbit(i) (i&(-i))
using namespace std;
const int MAXN = 5e5+5;
const int MX = 1e6;
int n,k,a[MAXN],b[MAXN];
int t1[MX+5],t2[MX+5],dp[MAXN],val[MX+5];
void upd(int *t,int pos,int x){for(int i=pos;i<=MX;i+=lowbit(i))t[i]=max(t[i],x);}
int query(int *t,int pos){int ans=0;for(int i=pos;i;i-=lowbit(i))ans=max(ans,t[i]);return ans;}
stack <int> st;
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=k;++i)//1 = ,0 < , 2 >
	{
		char s[4];
		scanf("%s",s+1);
		if(s[1]=='<') b[i]=0;
		else if(s[1]=='=') b[i]=1;
		else b[i]=2;
	}
	for(int i=k+1;i<=n;++i)
		b[i]=b[i-k];
	int ans=0,res=0;
	for(int i=1;i<=n;++i)
	{
		dp[i]=max(val[a[i]],max(query(t1,a[i]-1),query(t2,MX-a[i])))+1;
		if(b[dp[i]]==0)upd(t1,a[i],dp[i]);
		if(b[dp[i]]==2)upd(t2,MX-a[i]+1,dp[i]);
		if(b[dp[i]]==1)val[a[i]]=max(dp[i],val[a[i]]);
	}
	int ind=0;
	for(int i=1;i<=n;++i)
		if(dp[i]>ans) ans=dp[i],res=a[i],ind=i;
	printf("%d\n",ans);--ans;st.push(res);
	for(int i=ind-1;i>=1;--i)//输出，从尾部往前遍历数组，利用栈的特性。
	{
		if(ans==0) break;
		if(b[ans]==1)
		{
			if(res==a[i]&&dp[i]==ans)
			{
				st.push(a[i]);
				--ans;
				res=a[i];
			}
		}
		else if(b[ans]==0)
		{
			if(res>a[i]&&dp[i]==ans)
			{
				st.push(a[i]);
				--ans;
				res=a[i];
			}
		}
		else if(b[ans]==2)
		{
			if(res<a[i]&&dp[i]==ans)
			{
				st.push(a[i]);
				--ans;
				res=a[i];
			}
		}
	}
	while(!st.empty())
	{
		printf("%d ",st.top());
		st.pop();
	}
	return 0;
}
```



总结：太折磨了，鬼知道我考试被这个苟证明卡了多久，最后还是看题解才会的。。。

---

## 作者：Shawk (赞：6)

可以用树状数组完成的题，为什么要用线段树呢？

~~希丰展？看[博客](https://www.cnblogs.com/Z8875/p/13379107.html)~~
* 先简化一下题意：

就是将 s 序列复制几次展开，让 a 的子序列的符号是 s 序列的前缀。

就像 <,>,= 可以写成 <,>,=,<,>,=,<,>,=,... a 序列的一个子序列 2,4,3,3,5,3 的符号序列 <,>,=,<,> 就是上面展开的那个序列的前缀，所以合法。
* 分析

根据题目可以想到$O(n^2)$的写法
定义$f_i$为以$a_i$为结尾的最长合法序列。（有些类似最长上升子序列）


第一维枚举状态 i，第二维选取决策 j，就是在 1 到 i-1 中选取一个 j 使得$a_i$可以接在 $a_j$ 后面且 $f_j$ 最大。（在类比一下最长上升子序列）

这里考虑$a_i$可以接在 $a_j$ 后面条件，因为$f_j$是最长长度，这样它后面的符号其实就确定了，就是$s[f_i]$（预处理是先把 s 序列按我描述的题意展开），是如果要接到$a_j$的后面，必须要满足$a_j s[f_i]a_i,s[f_i]\in \{<,>,=\}$

$n^2$的解法是跑不了n的范围是$5\times 10^5$的数据的，考虑优化。

关于DP的优化，什么单调队列优化，斜率优化其实都是在选决策 j 的时侯进行优化，这里的决策也可以进行优化。

每次都只有三种情况，而且是选取的最大值，其实决策 j 的取值也有三种：
1. $a_j<a_i$中 f 值最大的j
2. $a_j>a_i$中 f 值最大的j
3. $a_j=a_i$中 f 值最大的j

都是取最大值而且小于号情况是前缀最大值，大于号情况是后缀最大值，这两个用开在 0-1e6 树状数组维护，等于号的其实开个数组就够了，因为它相当与单点操作，不需要树状数组或线段树维护

关于树状数组如何维护后缀最大值，我们想，维护前缀最大值的时候是向后更新，向前查询，那维护后缀最大值就可以向前更新，向后查询，其实是一个道理的。

我的代码也不是很长，还有不理解的地方可以看一看代码
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e5 + 5, M = 1e6 + 5;
char c[N];
int n, k, a[N], f[N], t1[M], t2[M], t[M], p[N], ans, last;
int low(int x) {//lowbit函数
	return x & -x;
}
void Change1(int x) {前缀最大值向后更新
	for (int i = a[x]; i <= 1e6; i += low(i))
		if (f[x] > f[t1[i]]) t1[i] = x;
}
int Ask1(int x) {前缀最大值向前查询
	int b = 0;
	for (int i = a[x] - 1; i; i -= low(i))
		if (f[b] < f[t1[i]]) b = t1[i];
	return b;
}
void Change2(int x) {后缀最大值向前更新
	for (int i = a[x]; i; i -= low(i))
		if (f[x] > f[t2[i]]) t2[i] = x;
}
int Ask2(int x) {后缀最大值向后查询
	int b = 0;
	for (int i = a[x] + 1; i <= 1e6; i += low(i))
		if (f[b] < f[t2[i]]) b = t2[i];
	return b;
}
void Print(int x) {//递归输出方案
	if (!x) return;
	Print(p[x]);
	printf("%d ", a[x]);
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
	 	scanf("%d", &a[i]), f[i] = 1;//f初始化为1
	for (int i = 1; i <= k; ++i)
		scanf(" %c", &c[i]);
	for (int i = k + 1; i < n; ++i)
		c[i] = c[(i-1)%k+1];//展开
	for (int i = 1, j; i <= n; ++i) {
		if (f[i] < f[j=Ask1(i)] + 1)//查询小于号
			f[i] = f[j] + 1, p[i] = j;
		if (f[i] < f[j=Ask2(i)] + 1)//查询大于号
			f[i] = f[j] + 1, p[i] = j;
		if (f[i] < f[j=t[a[i]]] + 1)//查询等于号
			f[i] = f[j] + 1, p[i] = j;
		if (ans < f[i]) ans = f[i], last = i;//更新答案
		if (c[f[i]] == '<') Change1(i);//更新小于号
		if (c[f[i]] == '>') Change2(i);//更新大于号
		if (c[f[i]] == '=' && f[i] > f[t[a[i]]]) //更新等于号
			t[a[i]] = i;
	}
	printf("%d\n", ans);
	Print(last);//输出方案
	return 0;
}
```


---

## 作者：y2823774827y (赞：6)

### 安利博客$\Longrightarrow\Longrightarrow\Longrightarrow$[更好的阅读体验](https://www.cnblogs.com/y2823774827y/p/10259020.html)

第一次切掉没题解的题$qwq$

首先确定$a_i$的位置后显然就能确定$a_{i+1}$的位置，建一棵权值线段树，维护$<,=,>$三种情况

考虑确定$a_{i}$的位置
1. 在$[min,a_{i}-1]$中找$<$的最大值

1. 在$[a_{i}+1,max]$中找$>$的最大值

1. 找$[a_{i},a_{i}]$的$=$的值(其实不用线段树，开个数组就能维护)

1. 比较三个值，假定最大值为$val$，则更新$[a_{i},a_{i}]$中$s[(val-1)\%k+1]$的值（想一想为什么只更新一个符号的值就能保证正确性？）

这题的难点解决了，至于输出方案，如果你做多了这样的题自然能想到开个数组存**每次**的状态，然后再开个数组存前驱

代码写得比较乱，重载这些大家自己加吧

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef int LL;
const LL maxn=1500009;
inline LL Read(){
	LL x(0),f(1); char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1; c=getchar();
	}
	while(c>='0'&&c<='9')
	    x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}
struct node{
	LL mx,mxi,tot;
};
struct Tree{
	node t[4];
	LL son[2];
}tree[maxn];
LL nod;
node Query(LL now,LL l,LL r,LL lt,LL rt,LL opt){
	if(!now||lt>rt)
	    return (node){0,0,0};
	if(lt<=l&&rt>=r)
	    return tree[now].t[opt];
	node ans=(node){0,0,0};
	LL mid=(l+r)>>1;
	if(lt<=mid)
		ans=Query(tree[now].son[0],l,mid,lt,rt,opt);
	if(rt>mid){
		node tmp=Query(tree[now].son[1],mid+1,r,lt,rt,opt);
	    if(ans.mx<tmp.mx)
		    ans=tmp;
	}
	return ans;
}
inline void Update(LL now,LL opt){
	LL son0(tree[now].son[0]),son1(tree[now].son[1]);
	if(tree[son0].t[opt].mx>tree[son1].t[opt].mx)
		tree[now].t[opt]=tree[son0].t[opt];
	else
		tree[now].t[opt]=tree[son1].t[opt];
}
inline void Change(LL &now,LL l,LL r,LL opt,LL goal,LL val,LL tot){
	if(!now){
		now=++nod;
		if(l==r)
	        for(LL i=1;i<=3;++i)
		        tree[now].t[i]=(node){0,l,0};
	}
	if(l==r){
		if(tree[now].t[opt].mx<val)
		    tree[now].t[opt].mx=val,
			tree[now].t[opt].tot=tot;
		return;
	}
	LL mid=(l+r)>>1;
	if(goal<=mid)
	    Change(tree[now].son[0],l,mid,opt,goal,val,tot);
	else
	    Change(tree[now].son[1],mid+1,r,opt,goal,val,tot);
	Update(now,opt);
}
LL n,k,root,ans,last,_min,_max;
LL pre[maxn],a[maxn],c[maxn],ch[maxn],w[maxn];
void Write(LL now){
	if(!now)
	    return;
	Write(pre[now]);
	printf("%d ",w[now]);
}
struct LS{
	LL id,val;
}b[maxn];
inline bool cmp1(LS x,LS y){
	return x.val<y.val;
}
int main(){
	n=Read(),k=Read();
	for(LL i=1;i<=n;++i)
	    b[i]=(LS){i,Read()},
		c[i]=b[i].val;
	sort(b+1,b+1+n,cmp1);
	LL num(0);
	for(LL i=1,last=-1;i<=n;++i){
		if(last!=b[i].val)
		    last=b[i].val,
			++num;
		a[b[i].id]=num;
	}
	_min=1,_max=num;
	
	for(LL i=1;i<=k;++i){
	    char c;
	    scanf(" %c",&c);
	    if(c=='<')
	        ch[i]=1;
	    else if(c=='>')
	        ch[i]=3;
	    else
	        ch[i]=2;
	}
	LL tot(0),last;
	for(LL i=1;i<=n;++i){
		node ans1=Query(root,_min,_max, _min,a[i]-1,1),
		     ans2=Query(root,_min,_max, a[i],a[i]  ,2),
		     ans3=Query(root,_min,_max, a[i]+1,_max,3);
		++ans1.mx,++ans2.mx,++ans3.mx;
		
		if(ans1.mx<ans2.mx) ans1=ans2;
		if(ans1.mx<ans3.mx) ans1=ans3;
		
		LL sum(ans1.mx);
		w[++tot]=c[i],
		pre[tot]=ans1.tot,
		Change(root,_min,_max,ch[(sum-1)%k+1],a[i],sum,tot);
		if(sum>ans)
		    ans=sum,
		    last=tot;
	}
	printf("%d\n",ans);
	Write(last);
	return 0;
}/*
20 5
2 4 3 1 3 5 3 8 9 2 1 20 3 5 9 1 2 4 5 3
< > = < >

11
2 4 3 3 5 3 9 1 1 4 3
*/
```

---

## 作者：sodak (赞：4)

小渣渣来分享一下本人的思路
## 思路

定义f[i]为处理到第i位，所得匹配的最长长度，根据f[i]我们可以求出它后面要跟的符号（可以用符号填满，避免一些取模运算），对于i，我们枚举每一个i前面的j，判断是否合法，那么$n^2$的做法就很容易能写出来了
### $n^2$做法

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=20000+10;
int f[maxn],a[maxn];
char op[100+10];
int sta[maxn],top,ans,id;
int path[maxn];
void print(int id){
    if(id==0)return;
    print(path[id]);
    printf("%d ",a[id]);
}
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=k;i++){
        scanf(" %c",&op[i]);
    }
    f[1]=ans=id=1;
    for(int i=2;i<=n;i++){
        f[i]=1;
        for(int j=1;j<i;j++){
            char ch=op[(f[j]-1)%k+1];
            if((ch=='>'&&a[j]>a[i])||(ch=='<'&&a[j]<a[i])||(ch=='='&&a[j]==a[i])){
                if(f[i]<f[j]+1){
                    f[i]=f[j]+1;
                    path[i]=j;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(ans<f[i]){
            ans=f[i];
            id=i;
        }
    }
    printf("%d\n",ans);
    print(id);
}

```
### 优化
不过根据这道题的数据，$n^2$显然是过不了的，那么我们就考虑优化，所以就有了下面的线段树优化做法

* 维护三棵线段树（貌似两棵也可以），分别维护后面该接 =（root1为根），<（root2为根）, >（root3为根） 的位置

* insert 根据当前的f[i]求出下一个符号该接什么，然后放到相应的线段树里面

--->后面接”=“, insert(root1,1,1e6,i,f[i]);

--->后面接“<”, insert(root2,1,1e6,i,f[i]);

--->后面接“>”, insert(root3,1,1e6,i,f[i]);

* query  分别在三棵线段树中找一个符合符号的的最大f[j]，比如在小于的树中找区间[1,a[i]-1]]中的f最大值，并返回位置（这里就是优化所在，在查找最优j时变成了$log$级别），因为要记录路径，所以我们返回值为位置（有了位置搞啥不行），但是要以f值为标准，决定返回的是哪个位置

--->在等于的树中取f值最大对应的位置 query(root1,1,1e6,a[i],a[i]);

--->在小于的树中取f值最大对应的位置 query(root2,1,1e6,1,a[i]-1);

--->在大于的树中取f值最大对应的位置 query(root3,1,1e6,a[i]+1,1e6);

对于树上的每一个节点，我们维护tree[i]（f值），pos[i] (在数组中对应的位置)，ls[i] (左儿子)，rs[i] (右儿子),线段树开值域应该比较好维护。


## 附上代（丑）码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
int f[maxn * 21], a[maxn];
int nodecnt, root1, root2, root3, ans, id, poss;
int path[maxn], ls[maxn * 21], rs[maxn * 21], tree[maxn * 21], pos[maxn * 21];
char op[maxn];
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

void print(int id) {
    if (id == 0)
        return;
    print(path[id]);
    printf("%d ", a[id]);
}
void up(int rt) {
    if (tree[ls[rt]] < tree[rs[rt]]) {
        tree[rt] = tree[rs[rt]];
        pos[rt] = pos[rs[rt]];
    } else {
        tree[rt] = tree[ls[rt]];
        pos[rt] = pos[ls[rt]];
    }
}
void insert(int &rt, int l, int r, int val, int p) {
    if (rt == 0)
        rt = ++nodecnt;
    if (l == r) {
        if (tree[rt] < val) {
            pos[rt] = p;
            tree[rt] = val;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (a[p] <= mid)
        insert(ls[rt], l, mid, val, p);
    else
        insert(rs[rt], mid + 1, r, val, p);
    up(rt);
    return;
}
int query(int rt, int l, int r, int s, int t) {
    if (l >= s && r <= t)
        return pos[rt];
    if (s > t || !rt)
        return 0;
    int mid = (l + r) >> 1;
    int ans = 0, poss = 0;
    if (s <= mid) {
        int lpos = query(ls[rt], l, mid, s, t);
        if (ans < f[lpos]) {
            ans = f[lpos];
            poss = lpos;
        }
    }
    if (t > mid) {
        int rpos = query(rs[rt], mid + 1, r, s, t);
        if (ans < f[rpos]) {
            ans = f[rpos];
            poss = rpos;
        }
    }
    return poss;
}
int main() {
    int n, k;
    n = read(), k = read();
    for (int i = 1; i <= n; ++i) a[i] = read(), f[i] = 1;
    for (int i = 1; i <= k; ++i) scanf(" %c", &op[i]);
    for (int i = k + 1; i < n; ++i) op[i] = op[(i - 1) % k + 1];
    for (int i = 1, poss; i <= n; ++i) {
        poss = query(root1, 1, 1e6, a[i], a[i]);
        if (f[i] < f[poss] + 1) {
            f[i] = f[poss] + 1;
            path[i] = poss;
        }
        poss = query(root2, 1, 1e6, 1, a[i] - 1);
        if (f[i] < f[poss] + 1) {
            f[i] = f[poss] + 1;
            path[i] = poss;
        }
        poss = query(root3, 1, 1e6, a[i] + 1, 1e6);
        if (f[i] < f[poss] + 1) {
            f[i] = f[poss] + 1;
            path[i] = poss;
        }
        if (ans < f[i]) {
            ans = f[i];
            id = i;
        }
        if (op[f[i]] == '=')
            insert(root1, 1, 1e6, f[i], i);
        else if (op[f[i]] == '<')
            insert(root2, 1, 1e6, f[i], i);
        else if (op[f[i]] == '>')
            insert(root3, 1, 1e6, f[i], i);
    }
    printf("%d\n", ans);
    print(id);
    return 0;
}


```
（求管理员大大审核通过）

---

## 作者：Planetary_system (赞：0)

## 题面解释：
在给定的序列中找出长度最长并相邻两项直接关系满足给定条件的子序列。

## 思路分析：
$f_i$ 表示最后一位在 $i$ 的最长子序列长度，那么知道 $f$ 的值就能求出下一位满足的数量关系，只要在前面的找出满足条件的中 $f_i$ 的最大值直接转移就好。

然后这时我们就可以考虑到用三颗权值线段树维护三种符号，直接转移就好。

最后输出序列只需要倒着扫一遍即可，每次找出最后面一个满足条件的。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10; 
int n,k,tot,ans,dp[N],a[N],num[N],rt[10],tr[N<<4],ls[N<<4],rs[N<<4];
char s[N];
inline int Max(int x,int y){
	if(x>y)return x;
	return y;
}
inline void push_up(int p){
	tr[p]=max(tr[ls[p]],tr[rs[p]]);
	return;
}
inline void upd(int &p,int l,int r,int x,int y){
	if(!p)p=++tot;
	if(l==r){
		tr[p]=max(tr[p],y);
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)upd(ls[p],l,mid,x,y);
	else upd(rs[p],mid+1,r,x,y);
	push_up(p);
	return; 
}
inline int qry(int p,int l,int r,int pl,int pr){
	if(l<=pl&&pr<=r)return tr[p];
	int res=0;
	int mid=pl+pr>>1;
	if(ls[p]&&l<=mid)res=max(res,qry(ls[p],l,r,pl,mid));
	if(rs[p]&&mid<r)res=max(res,qry(rs[p],l,r,mid+1,pr));
	return res;
} 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(register int i=1;i<=n;i++)
		cin>>a[i];
	for(register int i=1;i<=k;i++)
		cin>>s[i];
	for(register int i=1;i<=n;i++){
		dp[i]=Max(qry(rt[0],a[i],a[i],0,1e6),
		      Max(qry(rt[2],0,a[i]-1,0,1e6),
			  	  qry(rt[1],a[i]+1,1e6,0,1e6)))+1;
		char ch=s[(dp[i]-1)%k+1];
		if(ch=='=')upd(rt[0],0,1e6,a[i],dp[i]);
		if(ch=='>')upd(rt[1],0,1e6,a[i],dp[i]);
		if(ch=='<')upd(rt[2],0,1e6,a[i],dp[i]);
		ans=Max(ans,dp[i]);
	}
	cout<<ans<<'\n';
	for(int i=n,j=ans;j>0;i--){
		char ch=s[(j-1)%k+1];
		if(dp[i]==j&&(j==ans||ch=='='&&a[i]==num[j+1]||ch=='>'&&a[i]>num[j+1]||ch=='<'&&a[i]<num[j+1]))
			num[j--]=a[i];
	}
	for(int i=1;i<=ans;i++)
		cout<<num[i]<<' ';	
	return 0;
} 
```

谢谢！

---

