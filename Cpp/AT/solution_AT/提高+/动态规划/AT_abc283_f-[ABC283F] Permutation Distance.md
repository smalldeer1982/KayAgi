# [ABC283F] Permutation Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc283/tasks/abc283_f

$ (1,2,\ldots,N) $ の順列 $ P=(P\ _\ 1,P\ _\ 2,\ldots,P\ _\ N) $ が与えられます。

すべての $ i\ (1\leq\ i\leq\ N) $ に対して、以下の値を求めてください。

- $ D\ _\ i=\displaystyle\min_{j\neq\ i}\left\lparen\left\lvert\ P\ _\ i-P\ _\ j\right\rvert+\left\lvert\ i-j\right\rvert\right\rparen $
 
 順列とは $ (1,2,\ldots,N) $ の順列とは、$ (1,2,\ldots,N) $ を並べ替えて得られる数列のことをいいます。 つまり、長さ $ N $ の数列 $ A $ は $ i\ (1\leq\ i\leq\ N) $ がその中にちょうど $ 1 $ 回だけ現れるとき、かつそのときに限り$ (1,2,\ldots,N) $ の順列です。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times10^5 $
- $ 1\ \leq\ P\ _\ i\ \leq\ N\ (1\leq\ i\leq\ N) $
- $ i\neq\ j\implies\ P\ _\ i\neq\ P\ _\ j $
- 入力はすべて整数
 
### Sample Explanation 1

たとえば、$ i=1 $ について - $ j=2 $ のとき、$ \left\lvert\ P\ _\ i-P\ _\ j\right\rvert=1,\left\lvert\ i-j\right\rvert=1 $ です。 - $ j=3 $ のとき、$ \left\lvert\ P\ _\ i-P\ _\ j\right\rvert=1,\left\lvert\ i-j\right\rvert=2 $ です。 - $ j=4 $ のとき、$ \left\lvert\ P\ _\ i-P\ _\ j\right\rvert=2,\left\lvert\ i-j\right\rvert=3 $ です。 よって、$ j=2 $ のとき $ \left\lvert\ P\ _\ i-P\ _\ j\right\rvert+\left\lvert\ i-j\right\rvert=2 $ で最小となるので、$ D\ _\ 1=2 $ です。

## 样例 #1

### 输入

```
4
3 2 4 1```

### 输出

```
2 2 3 3```

## 样例 #2

### 输入

```
7
1 2 3 4 5 6 7```

### 输出

```
2 2 2 2 2 2 2```

## 样例 #3

### 输入

```
16
12 10 7 14 8 3 11 13 2 5 6 16 4 1 15 9```

### 输出

```
3 3 3 5 3 4 3 3 4 2 2 4 4 4 4 7```

# 题解

## 作者：ppip (赞：23)

一个很暴力的做法：对于每个点，向两边暴力枚举更新答案，如果下标太远不可能更新（设答案为 $D_i$，即 $|i-j|\geq D_i$）则 `break`。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N(2e5);
int P[N+5];
int dis(int x,int y) {return abs(x-y)+abs(P[x]-P[y]);}
int main() {
    int n;cin>>n;
    for (int i{1};i<=n;++i) scanf("%d",P+i);
    for (int i{1};i<=n;++i) {
        int D{n};
        for (int j{i+1};j-i<D&&j<=n;++j)
            D=min(D,dis(i,j));
        for (int j{i-1};i-j<D&&j>=1;--j)
            D=min(D,dis(i,j));
        printf("%d ",D);
    }
    return 0;
}
```

复杂度证明：显然一个点向两边最多跑 $O(D_i)$ 次就会停止。所以复杂度为 $O(\sum D_i)$。

而每个点取离它最近的一个点连边，这个显然能构成一个基环树森林。

同时，在最小生成基环树森林中，每个点都必须要有一个出边，
所以给每个点钦定最短的那个出边是一定能构成最小生成基环树森林的。

而平面曼哈顿距离最小生成基环树（森林）在点的横纵坐标范围均是 $[1,n]$ 的整数时，上界是 $O(n\sqrt n)$ 的。

于是整个做法的复杂度就是 $O(n\sqrt n)$。

---

## 作者：__Aha (赞：4)

####  [题目传送门](https://www.luogu.com.cn/problem/AT_abc283_f) 

_~~来一发树状数组~~_ ，不会的可以先学一下树状数组

# Description
- 给定一个长度为 $ N$ 的序列 $P_i$ ~ $P_N$，令 $D_i=\min\limits_{i \neq j} \left(\left|P_i-P_j\right|+\left|i-j\right|\right)$，求$D_1$ ~ $D_N$。
- $ 2\ \leq\ N\ \leq\ 2\times10^5 $
- $ 1\ \leq\ P\ _\ i\ \leq\ N\ (1\leq\ i\leq\ N) $
- $ i\neq\ j\implies\ P\ _\ i\neq\ P\ _\ j $

# Solution
可以把这个序列装换成平面直角坐标系中的 $N$ 个点 $\left(i,P_i\right)$ ，则 $D_i$ 转换为求离第 $i$ 个点的曼哈顿距离最小值。

对于第 $i$ 个点，设距离其曼哈顿距离最小的点编号为 $j$ ，对点 $j$ 的位置分类讨论：

- $j$ 在 $i$ 的左上方，则：$P_j>P_i$，$j<i$ $\Rightarrow \left|P_i-P_j\right|+\left|i-j\right|={\color{red}P_j-j}-P_i+i$

- $j$ 在 $i$ 的左下方，则：$P_j<P_i$，$j<i$ $\Rightarrow \left|P_i-P_j\right|+\left|i-j\right|={\color{red}-P_j-j}+P_i+i$

- $j$ 在 $i$ 的右上方，则：$P_j>P_i$，$j>i$ $\Rightarrow \left|P_i-P_j\right|+\left|i-j\right|={\color{red}P_j+j}-P_i-i$

- $j$ 在 $i$ 的右下方，则：$P_j<P_i$，$j>i$ $\Rightarrow \left|P_i-P_j\right|+\left|i-j\right|={\color{red}-P_j+j}+P_i-i$

记红色部分为 $\Delta$，我们只需要让 $\Delta$ 的值最小即可，考虑维护四个个树状数组求最小值（实际上只写了一个，可以重复利用）。具体如下：

- 考虑到 $j$ 在 $i$ 的左上方时，依次遍历 $P_1$ ~ $P_N$。对于每个 $i$，$\Delta$ 即为 $j<i,P_j\in\left[P_i+1,N\right]$ 最小的 $P_j-j$，然后更新 $D_i$ 的值，再将 $P_i$ 作为下标，$P_i-i$ 为权值，丢入树状数组中。

- 考虑到 $j$ 在 $i$ 的左下方时，依次遍历 $P_1$ ~ $P_N$。对于每个 $i$，$\Delta$ 即为 $j<i,P_j\in\left[1,P_i-1\right]$ 最小的 $-P_j-j$，然后更新 $D_i$ 的值，再将 $P_i$ 作为下标，$-P_i-i$ 为权值，丢入树状数组中。

- 考虑到 $j$ 在 $i$ 的右上方时，依次遍历 $P_N$ ~ $P_1$。对于每个 $i$，$\Delta$ 即为 $j>i,P_j\in\left[P_i+1,N\right]$ 最小的 $P_j+j$，然后更新 $D_i$ 的值，再将 $P_i$ 作为下标，$P_i+i$ 为权值，丢入树状数组中。

- 考虑到 $j$ 在 $i$ 的右下方时，依次遍历 $P_N$ ~ $P_1$。对于每个 $i$，$\Delta$ 即为 $j>i,P_j\in\left[1,P_i-1\right]$ 最小的 $-P_j+j$，然后更新 $D_i$ 的值，再将 $P_i$ 作为下标，$-P_i+i$ 为权值，丢入树状数组中。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long //不开long long见祖宗 
#define inf 0x3f3f3f3f//定义正无穷 
using namespace std;
int n,p[200001],c[200001],d[200001];//p为给定序列，c为树状数组，d为答案 
int lowbit(int a) //lowbit操作学过树状数组的懂得都懂 
{
	return a&-a;
}
void add(int a,int b) //树状数组的修改操作，a 为下标，b为 权值 
{
	for(;a<=n;a+=lowbit(a)) c[a]=min(c[a],b);
}
int query(int a) //查询操作，求 P[1]~P[a] 的最小值 
{
	int ret=inf;
	for(;a;a-=lowbit(a)) ret=min(ret,c[a]);
	return ret;
}
signed main()
{
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	memset(d,inf,sizeof d);
	memset(c,inf,sizeof c);
	for(int i=1;i<=n;i++) //左上方 
	{ 
		d[i]=min(d[i],query(n-p[i]+1)-p[i]+i);//query(n-p[i]+1)即为Delta最小值 
		add(n-p[i]+1,p[i]-i); /*这里添加的下标原本因为 P[i],但由于对于左上方的查询操作，是在 p[i]~n 中进行的，
		可是树状数组的查询操作是从1开始，所以这里转化一下，只要维持下标间相对大小不变即可*/
	}
	
	memset(c,inf,sizeof c);
	for(int i=1;i<=n;i++) //左下方 
	{
		d[i]=min(d[i],query(p[i])+p[i]+i);
		add(p[i],-p[i]-i);
	}
	
	memset(c,inf,sizeof c);
	for(int i=n;i>=1;i--) //右上方 
	{
		d[i]=min(d[i],query(n-p[i]+1)-p[i]-i);
		add(n-p[i]+1,p[i]+i);//这里使用 n-p[i]+1原因同上 
	}
	
	memset(c,inf,sizeof c);
	for(int i=n;i>=1;i--) //右下方 
	{
		d[i]=min(d[i],query(p[i])+p[i]-i);
		add(p[i],-p[i]+i);
	}
	
	for(int i=1;i<=n;i++) cout<<d[i]<<" ";
	return 0;
}
```


---

## 作者：POYE (赞：2)

因为一个数的绝对值只可能是它本身或它的相反数，所以题目中的式子可以分成四种类别。

- $i>j$，$P_i>P_j$，则 $|P_i-P_j|+|i-j|=(P_i+i)+(-P_j-j)$。
- $i>j$，$P_i<P_j$，则 $|P_i-P_j|+|i-j|=(i-P_i)+(P_j-j)$。
- $i<j$，$P_i>P_j$，则 $|P_i-P_j|+|i-j|=(P_i-i)+(j-P_j)$。
- $i<j$，$P_i<P_j$，则 $|P_i-P_j|+|i-j|=(-P_i-i)+(P_j+j)$。

不难观察到，这四种情况中前一个括号里都是定值，只需后一个括号的值尽量小即可，可用线段树维护。再观察大小关系，前两种正序循坏，后两种倒序循坏，边算边加便可满足下标的大小关系。因为是个排列，所有数值在 $[1,n]$ 范围内，且不重复，即可作为线段树的下标。最后，随时更新每一位的答案即可。

### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=1000000000;
int n,p[200005],ans[200005],mn[200005],mx[200005];
struct Tree {int l,r,min;} t[800005];
inline void build(int k,int l,int r)
{
	t[k].l=l,t[k].r=r;
	if(l==r)
	{
		t[k].min=M;
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	t[k].min=min(t[k<<1].min,t[k<<1|1].min);
}

inline void add(int k,int x,int v)
{
	if(t[k].l>x||t[k].r<x) return;
	if(t[k].l==t[k].r&&t[k].l==x)
	{
		t[k].min=v;
		return;
	}
	add(k<<1,x,v);
	add(k<<1|1,x,v);
	t[k].min=min(t[k<<1].min,t[k<<1|1].min);
}

inline int ask(int k,int x,int y)
{
	if(t[k].l>y||t[k].r<x) return M;
	if(x<=t[k].l&&t[k].r<=y) return t[k].min;
	return min(ask(k<<1,x,y),ask(k<<1|1,x,y));
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",p+i);
	for(int i=1;i<=n;i++) ans[i]=M;
	build(1,1,n);
	add(1,p[1],-p[1]-1);
	for(int i=2;i<=n;i++)
	{
		if(p[i]>1)
		{
			int minn=ask(1,1,p[i]-1);
			if(minn!=M) ans[i]=min(ans[i],p[i]+i+minn);
		}
		add(1,p[i],-p[i]-i);
	}
	memset(t,0,sizeof(t));
	build(1,1,n);
	add(1,p[1],p[1]-1);
	for(int i=2;i<=n;i++)
	{
		if(p[i]<n)
		{
			int minn=ask(1,p[i]+1,n);
			if(minn!=M) ans[i]=min(ans[i],i-p[i]+minn);
		}
		add(1,p[i],p[i]-i);
	}
	memset(t,0,sizeof(t));
	build(1,1,n);
	add(1,p[n],n-p[n]);
	for(int i=n-1;i>=1;i--)
	{
		if(p[i]>1)
		{
			int minn=ask(1,1,p[i]-1);
			if(minn!=M) ans[i]=min(ans[i],p[i]-i+minn);
		}
		add(1,p[i],i-p[i]);
	}
	memset(t,0,sizeof(t));
	build(1,1,n);
	add(1,p[n],p[n]+n);
	for(int i=n-1;i>=1;i--)
	{
		if(p[i]<n)
		{
			int minn=ask(1,p[i]+1,n);
			if(minn!=M) ans[i]=min(ans[i],-p[i]-i+minn);
		}
		add(1,p[i],p[i]+i);
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);

	return 0;
}
```


---

## 作者：SoyTony (赞：1)

把题意转化一下，看作是平面直角坐标系上点 $(i,P_i)$，要求对于每个点来说据其曼哈顿距离最短的值。

绝对值符号非常不方便处理，如果已知大小关系的话就可以拆开来。

例如当前枚举 $i$，对于 $j<i,P_j<P_i$ 而言，原式就是 $P_i-P_j+i-j=(P_i+i)-(P_j+j)$。求这个式子最小值，也就是求 $P_j+j$ 的最大值，相当于是一个二维偏序问题。

正序枚举 $i$，先查询树状数组中 $[1,P_i-1]$ 的最大值，用 $P_i+i$ 减去后更新答案，同时在树状数组中 $P_i$ 位置赋值为 $P_i+i$。

同理，对于 $i>j$ 的情况，实际上就是把 $i$ 变成 $n-i$，起到翻转的效果而保证偏序。

强化版：[天使玩偶（增加了一维时间，是三维偏序）](https://www.luogu.com.cn/problem/P4169)

---

## 作者：lzyqwq (赞：1)

~~赛时想到了线段树但是没想到值域线段树。~~

# $\texttt{Description}$

- 给出一个 $1\sim n$ 的排列 $a_1\sim a_n$，令 $d_i=\min\limits_{j\ne i} (|a_i-a_j|+|i-j|)$，求 $d_1\sim d_n$。

- $2\le n\le 2\times 10^5$，$1\le a_i\le n$。

# $\texttt{Solution}$

首先看到这个 $|i-j|$，可以考虑正着和倒着各扫一遍，就可以把 $d_i$ 分别表示成 $\min\limits_{j\ne i}(|a_i-a_j|+i-j)$ 和 $\min\limits_{j\ne i}(|a_i-a_j|+j-i)$。然后再拆前面的绝对值：

$$|a_i-a_j|=\begin{cases}a_i-a_j,a_i>a_j\\a_j-a_i,a_i<a_j\end{cases}$$

不用讨论等于的情况，因为给出的是一个排列。

以第一种情况为例，可以把式子化简成 $a_i-a_j+i-j$ 和 $a_j-a_i+i-j$，由于 $i$ 是定值，所以需要求的是求 $1\sim a_i-1$ 范围内 $-a_j-j$ 的最小值和 $a_i+1\sim n$ 范围内 $a_j-j$ 的最小值，然后求完之后把 $i$ 的对应信息更新到线段树 $a_i$ 的下标上。

第二种情况同理推一下即可。

注意一开始所有值都要初始化成无穷大，以舍去这个位置上没有数情况的不存在贡献。

时间复杂度 $\mathcal{O(n\log_2n)}$，空间复杂度 $\mathcal{O(n)}$。

# $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define ls x*2
#define rs x*2+1
int n,a[N],d[N];
struct sgt{
    int minn[N<<2];
    void change(int x,int l,int r,int k,int v){
        if(l>k||r<k){
            return;
        }
        if(l==k&&l==r){
            minn[x]=v;
            return;
        }
        int m=l+r>>1;
        change(ls,l,m,k,v);
        change(rs,m+1,r,k,v);
        minn[x]=min(minn[ls],minn[rs]);
    }
    int query(int x,int l,int r,int ql,int qr){
        if(qr<l||ql>r){
            return 1e9;
        }
        if(ql<=l&&qr>=r){
            return minn[x];
        }
        int m=l+r>>1;
        return min(query(ls,l,m,ql,qr),query(rs,m+1,r,ql,qr));
    }
}t1,t2,t3,t4;
int main(){
    memset(d,0x3f,sizeof d);
    memset(t1.minn,0x3f,sizeof t1.minn);
    memset(t2.minn,0x3f,sizeof t2.minn);
    memset(t3.minn,0x3f,sizeof t3.minn);
    memset(t4.minn,0x3f,sizeof t4.minn);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        d[i]=min({d[i],i+a[i]+t1.query(1,1,n,1,a[i]-1),-a[i]+i+t2.query(1,1,n,a[i]+1,n)});
        t1.change(1,1,n,a[i],-a[i]-i);
        t2.change(1,1,n,a[i],a[i]-i);
    }
    for(int i=n;i;--i){
        d[i]=min({d[i],a[i]-i+t3.query(1,1,n,1,a[i]-1),-a[i]-i+t4.query(1,1,n,a[i]+1,n)});
        t3.change(1,1,n,a[i],i-a[i]);
        t4.change(1,1,n,a[i],i+a[i]);
    }
    for(int i=1;i<=n;++i){
        cout<<d[i]<<' ';
    }
}
```


---

## 作者：harmis_yz (赞：0)

## 分析

分类讨论。

对 $|p_i-p_j|+|i-j|$ 分类讨论，有：

1. $(p_i+i)-(p_j+j)$，$p_i>p_j \land i>j$。
2.  $-(p_i-i)+(p_j-j)$，$p_i<p_j \land i>j$。
3. $(p_i-i)-(p_j-j)$，$p_i>p_j \land i<j$。
4. $-(p_i+i)+(p_j+j)$，$p_i<p_j \land i<j$。

然后用树状数组跑取最小值就行了。可以开两个树状数组，$1,3$ 情况一个;$2,4$ 情况一个。因为要使 $d_i$ 小，而在式子的左半部分一定时，$1,3$ 情况的右半部分都是减一个值，所以第一个树状数组维护最大值；$2,4$ 情况的右半部分都是加一个值，所以第二个树状数组维护最小值。最后 $1,2$ 情况正着枚举 $i$，$2,4$ 情况倒着枚举 $i$ 即可。复杂度 $O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=2e5+10;
int n,p[N],d[N],s[N];
int tr1[N],tr2[N];

il void add1(int x,int y){
	while(x<=n) tr1[x]=max(tr1[x],y),x+=x&(-x);
	return ;
}
int query1(int x){
	int Max=-1e18;
	while(x) Max=max(Max,tr1[x]),x-=x&(-x);
	return Max;
}
il void add2(int x,int y){
	while(x) tr2[x]=min(tr2[x],y),x-=x&(-x);
	return ;
}
int query2(int x){
	int Min=1e18;
	while(x<=n) Min=min(Min,tr2[x]),x+=x&(-x);
	return Min;
}
il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i) p[i]=rd,d[i]=1e18;
	for(re int i=1;i<=n;++i) tr1[i]=-1e18,tr2[i]=1e18;
	for(re int i=1;i<=n;++i){
		d[i]=min(d[i],(p[i]+i)-query1(p[i]));
		add1(p[i],p[i]+i);
		d[i]=min(d[i],-(p[i]-i)+query2(p[i]));
		add2(p[i],p[i]-i);	
	}
	for(re int i=1;i<=n;++i) tr1[i]=-1e18,tr2[i]=1e18;
	for(re int i=n;i>=1;--i){
		d[i]=min(d[i],(p[i]-i)-query1(p[i]));
		add1(p[i],p[i]-i);
		d[i]=min(d[i],-(p[i]+i)+query2(p[i]));
		add2(p[i],p[i]+i);
	}
	for(re int i=1;i<=n;++i) printf("%lld ",d[i]);
	return ;
}

signed main(){
	int t=1;while(t--)
	solve();
	return 0;
}
/*
1. (p[i]+i)-(p[j]+j) p[i]>p[j]^i>j
2. -(p[i]-i)+(p[j]-j) p[i]<p[j]^i>j
3. (p[i]-i)-(p[j]-j) p[i]>p[j]^i<j
4. -(p[i]+i)+(p[j]+j) p[i]<p[j]^i<j
*/
```


---

## 作者：Your_Name (赞：0)

## 题意
给定一个 $1 \sim n$ 的排列 $p$，对每个 $i$ 求得：
$$D_i = \min_{j \neq i} \left\{ \lvert p_i - p_j\rvert + \lvert i - j\rvert \right\} $$

## 题解
发现可以把绝对值拆开，即：

当 $p_i>p_j,i>j$ 时：$D_i=p_i-p_j+i-j$，即 $D_i=(p_i+i)-(p_j+j)$。

当 $p_i>p_j,i<j$ 时：$D_i=p_i-p_j+j-i$，即 $D_i=(p_i-i)-(p_j-j)$。

当 $p_i<p_j,i>j$ 时：$D_i=p_j-p_i+i-j$，即 $D_i=(-p_i+i)+(p_j-j)$。

当 $p_i<p_j,i<j$ 时：$D_i=p_j-p_i+j-i$，即 $D_i=(-p_i-i)+(p_j+j)$。

发现第一个括号内的是定值，只要维护第二个括号内的值即可。

又发现，要最后结果最小，那么就要减最大，加最小。

于是我们直接建一颗线段树维护区间最值，这样下标的条件便很好满足。

然而如果我们从前往后扫的话并不是很好维护 $p_i>p_j$ 这种条件，于是，我们按大小排序，按值的大小遍历就可以满足前面扫过的一定比我当前小或大这种条件。

最后注意细节，具体看代码。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define xx first
#define yy second
const int N = 2e5 + 10;
vector<pair<int, int> > v;
int n, a[N], ans[N];
struct node{
    int l, r, mx1, mi1, mx2, mi2;//表示什么下面修改哪里有
}tr[N * 4];
void pushup(int k){
    int lc = k * 2, rc = k * 2 + 1;
    tr[k].mi1 = min(tr[lc].mi1, tr[rc].mi1);
	tr[k].mi2 = min(tr[lc].mi2, tr[rc].mi2);
	tr[k].mx1 = max(tr[lc].mx1, tr[rc].mx1);
	tr[k].mx2 = max(tr[lc].mx2, tr[rc].mx2);
}
void build(int k, int l, int r){
    tr[k].l = l, tr[k].r = r;
    if(l == r){
		tr[k].mx2 = tr[k].mx1 = -1e9;
		tr[k].mi1 = tr[k].mi2 = 1e9;//这里一定要注意，他的最大值也可能为负。
		return;
	}
    int lc = k * 2, rc = k * 2 + 1, mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
	pushup(k);
}
void update(int k, int pos){
    if(tr[k].l == tr[k].r){
		tr[k].mi1 = tr[k].mx1 = a[pos] - pos;
		tr[k].mi2 = tr[k].mx2 = a[pos] + pos;//加上这个点。
        return;
    }
    int lc = k * 2, rc = k * 2 + 1, mid = tr[k].l + tr[k].r >> 1;
    if(pos <= mid){
        update(lc, pos);
    }else{
        update(rc, pos);
    }
    pushup(k);
}
int askmi1(int k, int l, int r){
	if(tr[k].l >= l && tr[k].r <= r){
		return tr[k].mi1;
	}
	int lc = k * 2, rc = k * 2 + 1, mid = tr[k].l + tr[k].r >> 1;
	if(r <= mid){
		return askmi1(lc, l, r);
	}else if(l > mid){
		return askmi1(rc, l, r);
	}else{
		return min(askmi1(lc, l, mid), askmi1(rc, mid + 1, r));
	}
}
int askmi2(int k, int l, int r){
	if(tr[k].l >= l && tr[k].r <= r){
		return tr[k].mi2;
	}
	int lc = k * 2, rc = k * 2 + 1, mid = tr[k].l + tr[k].r >> 1;
	if(r <= mid){
		return askmi2(lc, l, r);
	}else if(l > mid){
		return askmi2(rc, l, r);
	}else{
		return min(askmi2(lc, l, mid), askmi2(rc, mid + 1, r));
	}
}
int askmx1(int k, int l, int r){
	if(tr[k].l >= l && tr[k].r <= r){
		return tr[k].mx1;
	}
	int lc = k * 2, rc = k * 2 + 1, mid = tr[k].l + tr[k].r >> 1;
	if(r <= mid){
		return askmx1(lc, l, r);
	}else if(l > mid){
		return askmx1(rc, l, r);
	}else{
		return max(askmx1(lc, l, mid), askmx1(rc, mid + 1, r));
	}
}
int askmx2(int k, int l, int r){
	if(tr[k].l >= l && tr[k].r <= r){
		return tr[k].mx2;
	}
	int lc = k * 2, rc = k * 2 + 1, mid = tr[k].l + tr[k].r >> 1;
	if(r <= mid){
		return askmx2(lc, l, r);
	}else if(l > mid){
		return askmx2(rc, l, r);
	}else{
		return max(askmx2(lc, l, mid), askmx2(rc, mid + 1, r));
	}
}//一通查。
bool cmp(pair<int, int> p1, pair<int, int> p2){
	return p1.xx > p2.xx;
}//从大到小
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		v.push_back({a[i], i});
		ans[i] = 1e9;
	}
	
	sort(v.begin(), v.end());
	build(1, 1, n);
	for(auto i : v){
		ans[i.yy] = min(ans[i.yy], a[i.yy] + i.yy - askmx2(1, 1, i.yy));//i>j。
		ans[i.yy] = min(ans[i.yy], a[i.yy] - i.yy - askmx1(1, i.yy, n));//i<j,注意不要越界。
		update(1, i.yy);
	}//p_i>p_j的两种情况。

	sort(v.begin(), v.end(), cmp);
	build(1, 1, n);
	for(auto i : v){
		ans[i.yy] = min(ans[i.yy], -a[i.yy] + i.yy + askmi1(1, 1, i.yy));//i>j
		ans[i.yy] = min(ans[i.yy], -a[i.yy] - i.yy + askmi2(1, i.yy, n));//i<j
		update(1, i.yy);
	}//p_i<p_j的两种情况。
	for(int i = 1; i <= n; i ++){
		cout << ans[i] << ' ';
	}
	return 0;
}
```
  _完结撒花。_

---

