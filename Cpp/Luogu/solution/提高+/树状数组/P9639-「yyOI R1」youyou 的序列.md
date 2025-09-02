# 「yyOI R1」youyou 的序列

## 题目描述

给定一个长度为 $n$ 的序列 $a_{1\dots n}$，以及 $q$ 次操作。

定义一次操作为：交换 $a_k$ 与 $a_{k+1}$ 的值，并**立即**询问所有以 $a_i \;( i\in [1,n])$ 为峰的[子序列](https://oi-wiki.org/string/basic/#%E5%AD%90%E5%BA%8F%E5%88%97)数量之和，对 $4294967296$ 取模。**这里的交换是暂时的，也就是说，它仅在下一次操作前有效。**

在此我们认为，一个长度至少为 $1$ 的序列 $[a_1,a_2 ,\cdots,a_{s-1},a_s,a_{s+1},\cdots,a_{n-1},a_n ]$，满足 $a_1<a_2<\cdots<a_{s-1}<a_s>a_{s+1}>\cdots >a_{n-1}>a_n$，则称此序列为以 $a_s$ 为峰的序列。

你的任务是回答出所有操作的答案。


## 说明/提示

### 样例解释 #1

第一次操作的 $k$ 为 $1$。

此时序列为 $[5,1,7,3]$。

峰为 $a_1$：$[5]$，$[5,1]$，$[5,3]$。

峰为 $a_2$：$[1]$。

峰为 $a_3$：$[7]$，$[5,7]$，$[1,7]$，$[7,3]$，$[5,7,3]$，$[1,7,3]$。

峰为 $a_4$：$[3]$，$[1,3]$。

共计 $12$ 个不同的子序列，答案输出 $12$。

第二次和第三次操作的 $k$ 均为 $3$ ，此时有 $13$ 个不同的序列满足条件。

### 样例解释 #2

第一次操作的 $k$ 为 $1$。

此时序列为 $[7,7,7,7,6]$。

峰为 $a_1$：$[7]$，$[7,6]$。

峰为 $a_2$：$[7]$，$[7,6]$。

峰为 $a_3$：$[7]$，$[7,6]$。

峰为 $a_4$：$[7]$，$[7,6]$。

峰为 $a_5$：$[6]$。

共计 $9$ 个不同的子序列，答案输出 $9$。

后四次操作同理。

---

### 数据范围

**本题采用捆绑测试。**

| 子任务编号 | $n$ | $q$ | 分数 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $\le 500$ | $\le 100 $ |$10$ |
| $2$ | $\le2\times10^3$|$ \le 5\times10^3$ | $20$ |
| $3$ | $\le3\times10^4$ |$\le 10^4$ | $30$ |
| $4$ | $\le10^6$|$ \le10^6$ | $40$ |

对于 $100\%$ 的数据，$2\le n\le10^6$，$1\le q\le10^6$，$1\le a_i\le10^4$。


## 样例 #1

### 输入

```
4 3
1 5 7 3
1
```

### 输出

```
12
13
13
```

## 样例 #2

### 输入

```
5 5
7 7 7 7 6
1```

### 输出

```
9
9
9
9
9```

# 题解

## 作者：uid_310801 (赞：2)

首先考虑不进行任何操作的答案怎么算。

记 $ l_i $  为以第 $ i $ 个数结尾的单调递增子序列的个数，$ r_i $ 为以第 $ i $ 个数开始的单调递减子序列个数，则最终的答案就是 $ \sum^{n}_{i=1}l_i\times r_i $。

考虑 $ l_i $ 的递推方程：$ l_i=\sum^{i-1}_{j=1}([a_j<a_i]\times l_j)+1 $，即在 $ i $ 左边所有 $ a_j $ 比 $ a_i $ 小的 $ j $ 的 $ l_j $ 都能贡献到 $ l_i $ 上。这个东西可以从左到右扫一遍，建立一棵值域树状数组，单点修改、区间查询就好了。$ r_i $ 也能用类似的方法得出，不再赘述。

我们还需要求出 $ ld_i $ 表示以第 $ i $ 个数结尾的、以第 $ j $ 个数 $ (j\le i) $ 为峰的子序列个数，还是列一下递推方程：$ ld_i=\sum^{i-1}_{j=1}([a_j<a_i]\times l_j+[a_j>a_i]\times ld_j)+1 $，即在 $ i $ 之前比 $ a_i $ 小的数 $ a_j $ 以 $ i $ 为峰贡献到 $ ld_i $ 中，比 $ i $ 大的数 $ a_j $ 以 $ j $ 以及之前的数为峰贡献到 $ ld_i $ 中。

这个东西也能用值域树状数组求出来。$ rd_i $ 同理。

最后还有 $ ld2_i $ 我们要求出来。这个 $ ld2_i $ 就是表示当 $ a_i=a_{i+1} $ 时 $ ld_i $ 的值，求法跟上面一样，另外 $ rd2_i $ 表示当 $ a_i=a_{i-1} $ 时 $ rd_i $ 的值。

有了这些就可以开始计算了。

一次操作只会交换相邻两个数，我们的思路是删去被破坏的子序列的数量再加上新增加的子序列的数量。假设交换的位置为 $ x $。

1. $ a_x=a_{x+1} $。

数列没变化，输出原答案。

2. $ a_x>a_{x+1} $。

答案减去以 $ x $ 结尾的峰序列乘上以 $ x+1 $ 开头的下降序列，加上以 $ x+1 $ 结尾的上升序列乘上在 $ x+1 $ 位置以 $ x $ 开头的峰序列。

减去的部分很好理解，说说加上的部分：

交换后，原来在 $ x+1 $ 位置的数变成了 $ a_x $，而在 $ x $ 位置的数变成了 $ a_{x+1} $，所以本来前一项应该是在 $ x $ 位置以 $ x+1 $ 结尾的上升序列。然而由于 $ a_x>a_{x+1} $，所以这两个值是一样的，不用单独算一遍了。

写成公式就是：

 $$ ans-=r_{k+1}\times ld_k-rd2_{k+1}\times l_{k+1} $$

3.  $ a_x<a_{x+1} $。

跟上面一样，写成公式就是：

 $$ ans-=l_k\times rd_{k+1}-ld2_{k}\times r_{k} $$ 

可能有点绕，建议自己画图理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define deb(x) cerr<<"Line: "<<__LINE__<<", val= "<<x<<"; \n"
typedef unsigned ll;
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=1e6+10;
inline ll read(){
	ll a=0,x=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	x=-x;
		c=getchar();
	}
	while(isdigit(c)){
		a=a*10+c-'0';
		c=getchar();
	}
	return a*x;
}
void write(ll x){
	if(x<=9){
		putchar(x+'0');
		return;
	}
	write(x/10);
	putchar(x%10+'0');
}
ll n,q;
inline int Answer(unsigned int ans)
{
    unsigned int BASE=998244353ll*ans+ans*ans+ans/9991+ans%2159;
    BASE^=9810;
    BASE^=51971;
    BASE=BASE>>7;
    BASE=BASE<<11;
    BASE^=751669;
    BASE^=23465695622566ll;
    return BASE%(n-1)+1;
}
struct BIT{
	ll t[10086];
	inline ll lb(ll x){
		return x&(-x);
	}
	void update(ll x,ll k){
		while(x<=10010){
			t[x]+=k;
			x+=lb(x);
		}
	}
	inline ll query(ll x){
		ll ans=0;
		while(x){
			ans+=t[x];
			x-=lb(x);
		}
		return ans;
	}
}T1,T2,T3,T4,T5,T6;
ll l[N],r[N],a[N],ld[N],rd[N],ans,k;
ll ld2[N],rd2[N];
signed main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=n;i++){
		l[i]=1+T1.query(a[i]-1);
		T1.update(a[i],l[i]);
	}
	for(int i=n;i>=1;i--){
		r[i]=1+T2.query(a[i]-1);
		T2.update(a[i],r[i]);
	}
	for(int i=1;i<=n;i++){
		ans+=l[i]*r[i];
	}
	r[n+1]=1;
	ll sumd=0; 
	for(int i=1;i<=n;i++){
		ld[i]=T3.query(a[i]-1)+sumd-T4.query(a[i])+1;
		if(i!=n)	ld2[i]=T3.query(a[i+1]-1)+sumd-T4.query(a[i+1])+1;
		T3.update(a[i],l[i]);T4.update(a[i],ld[i]);
		sumd+=ld[i];
	}
	sumd=0;
	for(int i=n;i>=1;i--){
		rd[i]=T5.query(a[i]-1)+sumd-T6.query(a[i])+1;
		if(i!=1)	rd2[i]=T5.query(a[i-1]-1)+sumd-T6.query(a[i-1])+1;
		T5.update(a[i],r[i]);T6.update(a[i],rd[i]);
		sumd+=rd[i];
	}
	ll lastans=0;
	for(int T=1;T<=q;T++){
		if(T==1)	
			k=read();
		else{
			k=Answer(lastans);
		}
		lastans=ans;
		if(a[k]==a[k+1]){
			lastans=ans;
		}
		else if(a[k]<a[k+1]){
			lastans-=l[k]*rd[k+1];
			lastans+=ld2[k]*r[k];
		}
		else{
			lastans-=r[k+1]*ld[k];
			lastans+=rd2[k+1]*l[k+1];
		}
		write(lastans);
		putchar('\n');
	}
	return 0;
}
```

btw，这个强制在线有点傻。

---

## 作者：Heptagon18 (赞：2)

## Description
[原题链接](https://www.luogu.com.cn/problem/P9639)。

[更好的浏览体验](https://www.luogu.com.cn/blog/fyc090118/sequence-problem-ti-xie)。

-----

## Solution 

### Part 0 - 一些提示

“对 $4294967296$ 取模”本质上其实就是 $\text {unsigned int}$ 自然溢出。

“以...为峰的序列”看上去性质很难发掘，尝试将它分解成多个简单条件？

操作没有修改数之间的相对关系。预处理的可能性？

然后，就没有然后了。


### Part 0.5 - 写在前面

主要算法：方案数 DP，树状数组优化前缀和。

感谢 @youyou2007 @英雄趁年少6 帮忙验题！


### Part 1 - 发掘题面信息

题面首先给出了“峰”的定义。

考虑将“峰”的定义拆解为“以 $a_s$ 结尾的严格单调递增序列”与“以 $a_s$ 开头的严格单调递减序列”，$a_s$ 处的答案即为这两种序列方案数的乘积。

以“以 $a_s$ 结尾的严格单调递增序列”为例，考虑 DP 转移。

设 $pre_s$ 表示以 $a_s$ 结尾的严格单调递增序列

容易得到：$pre_s=\sum\limits_{i=1}^{s-1} pre_i \;(a_s>a_i)$。

直接使用该方程转移复杂度是 $O(n^2)$ 的。

基于此，我们可以对于每次询问暴力求解，总时间复杂度 $O(qn^2)$，获得 $10\%$ 的分数。

考虑优化。

观察条件“$a_s>a_i$”，发现其本质是一个值域上的前缀和。

于是可以用树状数组优化。

严格单调递减序列同理。

至此，我们完成了预处理的全部工作，时间复杂度 $O(n\log a_{\max}))$。


### Part 2 - 观察操作性质

经过预处理后，我们得到了 $pre$ 数组（存严格单调递增序列方案数）与 $nxt$ 数组（存严格单调递减序列方案数），考虑一次交换操作对两个数组的影响。

我们先考虑对 $pre$ 数组的影响。

（这里的影响都是考虑不相等的两个数，两个相等的数交换后对答案没有产生任何影响。)

观察交换操作中的两个数，可以发现，较小数的 $pre$ 并没有改变。

感性理解一下，无论较大数处于什么位置，较小数的 $pre$ 都不可能由较大数的 $pre$ 转移而来。

现在我们知道了较小数的 $pre$ 不变，较大数的 $pre$ 就好处理了。

如果 $a_k<a_{k+1}$，那么在预处理时，$pre_{k+1}$ 由 $pre_k$ 转移过来了，而交换后不能转移，需要将 $pre_{k+1}$ 减去 $pre_k$。

$a_k>a_{k+1}$ 同理，将 $pre_k$ 加上 $pre_{k+1}$ 即可。

考虑剩下的数。

发现在交换过程中仅有较大数的 $pre$ 发生变化，则仅有从较大数转移 $pre$ 值的数会发生变化，即为 $i>k+1,a_i>\max(a_k,a_{k+1})$ 的所有数。

$nxt$ 修改同理。

于是可以用预处理的思路暴力修改 + 转移，时间复杂度 $O(qn)$，可以通过 $30\%$ 的数据。

发现值域较小，可以在值域上修改 + 转移，时间复杂度 $O(qa_{\max})$，跑不满，可以通过 $60\%$ 的数据。

### Part 3 - 优化

观察最后一个部分分，发现 $q$ 达到了 $10^6$ 的级别， $O(q\times???)$ 必然会超时。

考虑在询问前预处理出全部答案。

回顾操作性质，发现转移仅和两个要素有关：元素值、位置。

进一步发现位置仅分为两部分：$[1,k-1]$ 和 $[k+2,n]$。

使用扫描线的思想，动态维护这两个区间。

接着思考，在区间中需要维护什么信息。

还是以 $pre$ 数组为例，考虑一次交换操作的贡献。

首先考虑其它数不互相影响的情况。

设较大数的 $pre$ 最后加上了 $g_1$，$nxt$ 最后加上了 $g_2$，满足 $i\in[k+2,n],a_i>\max(a_k,a_{k+1})$ 的集合为 $f\;(|f|=m)$，满足 $i\in[1,k-1],a_i>\max(a_k,a_{k+1})$ 的集合为 $p\;(|p|=o)$。

则 $g_1$ 最终对答案的贡献为 $g_1\times nxt_{f_1}+g_1\times nxt_{f_2}+\cdots+g_1\times nxt_{f_m} = g_1\times(nxt_{f_1}+nxt_{f_2}+\cdots+nxt_{f_m}) = g_1\times \sum\limits_{i=1}^m nxt_{f_i}$。

再结合上 $f_i>\max(a_k,a_{k+1})$，容易发现，维护的是 $[k+2,n]$ 范围内值域上的 $nxt$ 后缀和。

同理可得，$nxt$ 数组需要维护的是 $[1,k-1]$ 范围内值域上的 $pre$ 后缀和。

接着考虑其它数相互影响的情况。

发现刚才的做法有个致命的缺陷：由于区间内仍然存在大小关系，一个数减去的不一定是 $g$，而可能是 $2g,3g$ 等。

举个例子，假如当前 $[k+2,n]$ 区间内的数为 $[5,8,3,9]$，当前的 $\max(a_k,a_{k+1})=4$。

则因为 $5>4$，$5$ 的 $pre$ 需要减去 $g$。

又因为 $8>5,4$，$8$ 的 $pre$ 需要减去 $2g$。

以此类推。

观察可以得知，在每个数加进区间时，比它大的所有数均需要多减去一个 $g$。

那么我们定义带权权值数组 $prey$ 和 $nxty$，$prey_d,nxty_d$ 分别表示当取 $a_d$ 这个数时，总共在两个区间内分别需要减的 $pre,nxt$ 之和。

可以发现，带权权值对应的即为两个区间内值域上的 $pre$ 后缀和与 $nxt$ 后缀和。

那么总共需要减去的就是 $g_1\times\sum\limits_{i=1}^m nxty_{f_i}+g_2\times\sum\limits_{j=1}^o prey_{p_j}$。

用树状数组动态更新即可。

时间复杂度 $O(n\log a_{\max})$，总时间复杂度 $O(n\log a_{\max}+q)$，可以通过本题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

inline ll read()
{
    ll x=0,r=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') r=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*r;
}

void write(long long t)
{
    if(t<0)
    {
        putchar('-');
        t=-t;
    }
    if(t>=10)write(t/10);
    putchar(t%10+'0');
}

long long n,q;
long long a[1000005];
unsigned int tree[10005][15];
unsigned int pre[1000005];
unsigned int nxt[1000005];
unsigned int prey[1000005];
unsigned int nxty[1000005];
unsigned int del[1000005];
unsigned int ans[1000005];

long long lowbit(long long t)
{
    return t&(-t);
}

void update(long long x,long long k,long long n,long long op)
{
    for(long long i=x;i<=n;i+=lowbit(i)) 
        tree[i][op]+=k;
}

unsigned int query(long long t,long long k)
{
    long long ans=0;
    for(long long i=t;i>=1;i-=lowbit(i)) ans+=tree[i][k];
    return ans;
}

int Answer(unsigned int ans)
{
    unsigned int BASE=998244353ll*ans+ans*ans+ans/9991+ans%2159;
    BASE^=9810;
    BASE^=51971;
    BASE=BASE>>7;
    BASE=BASE<<11;
    BASE^=751669;
    BASE^=23465695622566ll;
    return BASE%(n-1)+1;
}

signed main()
{
    n=read();
    q=read();
    long long maxx=0;
    for(long long i=1;i<=n;i++)
    {
        a[i]=read();
        maxx=max(maxx,a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        pre[i]=1;
        pre[i]+=query(a[i]-1,0);
        update(a[i],pre[i],maxx,0);
    }
    unsigned int prey_cnt=0;
    unsigned int nxty_cnt=0;
    unsigned int cnt=0;
    for(int i=n;i>=1;i--)
    {
        nxt[i]=1;
        nxt[i]+=query(a[i]-1,1);
        update(a[i],nxt[i],maxx,1);
        cnt+=nxt[i]*pre[i];
    }
    for(int i=1;i<=n;i++)
    {
        ans[i]=cnt;
        prey[i]=prey_cnt-query(a[i],2)+pre[i];
        prey_cnt+=prey[i];
        update(a[i],prey[i],maxx,2);
    }
    for(int i=n;i>=1;i--)
    {
        nxty[i]=nxty_cnt-query(a[i],3)+nxt[i];
        nxty_cnt+=nxty[i];
        update(a[i],nxty[i],maxx,3);
    }
    for(int i=1;i<n;i++)
    {
        if(a[i]<a[i+1])
        {
            del[i]=-query(a[i]-1,4)-1;
            ans[i]+=del[i]*(nxty[i+1]-nxt[i+1]);
        }
        else if(a[i]>a[i+1])
        {
            del[i]=query(a[i+1]-1,4)+1;
            ans[i]+=del[i]*(nxty[i]-nxt[i]);
        }
        update(a[i],pre[i],maxx,4);
    }
    for(int i=n-1;i>=1;i--)
    {
        if(a[i]<a[i+1])
        {
            unsigned int op=query(a[i]-1,5)+1;
            ans[i]+=op*(prey[i+1]-pre[i+1]);
            ans[i]-=pre[i+1]*nxt[i+1]-(pre[i+1]+del[i])*(nxt[i+1]+op);
        }
        else if(a[i]>a[i+1])
        {
            unsigned int op=-query(a[i+1]-1,5)-1;
            ans[i]+=op*(prey[i]-pre[i]);
            ans[i]-=pre[i]*nxt[i]-(pre[i]+del[i])*(nxt[i]+op);
        }
        update(a[i+1],nxt[i+1],maxx,5);
    }
    int k;
    k=read();
    for(int i=1;i<=q;i++)
    {
        write(ans[k]);
        putchar('\n');
        k=Answer(ans[k]);
    }
    return 0;
}

```

---

