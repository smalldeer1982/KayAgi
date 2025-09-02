# [Kubic] Pyramid

## 题目背景

容易发现，F 题出题人不是 lxl。

![](https://cdn.luogu.com.cn/upload/image_hosting/icp2j1gj.png)

## 题目描述

给定一个初始长度为 $n$ 的序列 $p$。

设当前 $p$ 的长度为 $L$，有以下两种操作：

- A 操作先构造长度为 $L-1$ 的序列 $p'$ 满足 $p_i'=\min\{p_i,p_{i+1}\},i\in [1,L)$。然后用 $p'$ 代替 $p$。

- B 操作先构造长度为 $L-1$ 的序列 $p'$ 满足 $p_i'=\max\{p_i,p_{i+1}\},i\in [1,L)$。然后用 $p'$ 代替 $p$。

再给定一个长度为 $m$ 的序列 $a$，表示一共进行 $m$ 组操作，第 $i$ 组中先进行 $a_i$ 次 A 操作，再进行 $a_i$ 次 B 操作。保证 $2\sum a_i=n-1$。

最后给定 $q$ 次询问，每次给出参数 $x,l,r$，你需要求出进行前 $x$ 个操作之后 $\sum\limits_{i=l}^r p_i$ 的值。

**注意：询问中的 $x$ 指的是前 $x$ 个操作而不是前 $x$ 组操作，即有可能在某一组操作进行一部分时询问。**

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m,q\le 1.5\times 10^5,1\le x<n,1\le l\le r\le n-x,1\le p_i\le 10^9,2\sum a_i=n-1$。

||分值|时限 $(\operatorname{s})$|$n$|$m$|$q$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$5$|$1$|$\le 100$|$\le 100$|$\le 100$|无|
|$\operatorname{Subtask}2$|$10$|$1$|无特殊限制|无特殊限制|无特殊限制|AB|
|$\operatorname{Subtask}3$|$15$|$5$|无特殊限制|无特殊限制|无特殊限制|B|
|$\operatorname{Subtask}4$|$15$|$1$|无特殊限制|$=1$|无特殊限制|C|
|$\operatorname{Subtask}5$|$15$|$1$|无特殊限制|$=1$|无特殊限制|无|
|$\operatorname{Subtask}6$|$20$|$4$|无特殊限制|$\le 50$|无特殊限制|无|
|$\operatorname{Subtask}7$|$20$|$5$|无特殊限制|无特殊限制|无特殊限制|无|

特殊性质 A：$\forall i,a_i=1$

特殊性质 B：$l=r$。

特殊性质 C：$l=1,r=n-x$。

### 样例解释

给定的操作过程如下：

`6 2 4 1 3`

`2 2 1 1`

`2 2 1`

`2 1`

`2`

~~特殊性质单独拉出来写只是为了表格好看一点...~~

感谢 $\operatorname{A\color{red}lfalfa\_w}$ 对本题的贡献！

## 样例 #1

### 输入

```
5 2 3
6 2 4 1 3
1 1
1 1 4
2 2 3
4 1 1```

### 输出

```
6
3
2```

# 题解

## 作者：_lbw_ (赞：9)

爆标做法。

观察题目，发现这个又是最小值又是最大值非常难搞，每次 AB 操作次数相等看起来也没什么用。

我们考虑通过枚举 $w$，将 $\geq w$ 转为 1，剩下的为 0，这里复杂度看起来全错，但是等一下就对了。

这个东西怎么计算答案呢？我们知道 $A=\sum_{i}(w_i-w_{i-1})[A\geq w_i]$ 于是把每个 $w_i$ 对询问时的贡献即为最终序列中 1 个数乘上 $w_i-w_{i-1}$。

取出初始序列中所有极长 1 连续段，模拟可知：

- 每次 A 操作会使 1 连续段右端点左移一位
- 每次 B 操作会使 1 连续段左端点左移一位

因此，做完一个**整段**操作后，会使所有段往左移动 $a_i$ 位，并且长度小于 $a_i$ 的段会被删除。

这个形式的性质非常好！同时，它启发我们找出所有初始序列中所有极长 1 连续段。

每一次 $w_i$ 增加的时候，会变化的极长 1 连续段是 $\mathcal{O}(1)$ 的，我们把相同的极长 1 连续段缩起来，这样最多只会有 $\mathcal{O}(n)$ 个段 $(l_i,r_i,v_i)$，记段长为 $L_i$。

这一段的代码如下：


```cpp
IV add(i64 l,i64 r,i64 v){
	tot++;
	L[tot]=l;R[tot]=r;V[tot]=v;
}
int main(){
	n=read();m=read();q=read();
	FL(i,1,n)pi[i]=make_pair(b[i]=read(),i);
	F(i,1,m)a[i]=read();sort(pi+1,pi+1+n);
	add(1,n,0);
	st.insert({1,n});
	F(i,1,n){
		i64 v=pi[i].first,pos=pi[i].second;
		auto p=prev(st.upper_bound({pos}));
		auto[l,r]=*p;add(l,r,v);st.erase(p);
		if(l<pos)st.insert({l,pos-1}),add(l,pos-1,-v);
		if(pos<r)st.insert({pos+1,r}),add(pos+1,r,-v);
	}
}

```


如果只会在整段处询问，问题即为每次给定 $w,\Delta_l,\Delta_r,ql,qr$ 求：

$$\sum_{L_i\geq w}v_i\left|[l_i-\Delta_l ,r_i-\Delta_r]\cap[ql,qr]\right|$$

这里 $\Delta_l=\Delta_r$，所以我们可以直接把 $[ql,qr]$ 往后平移。

于是，此问题可以通过直接从小到大枚举 $L_i$ 同时维护 区间加-区间查询 的数据结构做到 $n\log n$。

若查询不在整段，我们仍然可以计算一个 $w$ 表示区间最小可能长度，而 $\Delta_l$ 和 $\Delta_r$ 不一定相等。

注意到分类讨论一堆大小关系多维偏序就可以做到 $\textsf{polylog}$ 了，考虑优化 $\log$ 数量。

首先有 $\Delta_l\leq \Delta_r$，平移区间，问题转化为：

$$\sum_{L_i\geq w}v_i|[l_i ,r_i-k]\cap[ql_i,qr_i]|$$

拆分左右端点贡献，枚举左/右端点取值，列出区间长度 $\geq 0$ 的不等式，为三维偏序，时间复杂度 $\mathcal{O}((n+q)\log ^2n)$。

[代码](https://www.luogu.com.cn/paste/1ig125jw)。

进一步，考虑容斥，有：

$$|[l_i ,r_i-k]\cap[ql_i,qr_i]|=|[l_i,r_i]\cap[ql_i,qr_i]|-|[r_i-k+1,r_i]\cap[ql_i,qr_i]|$$

前半部分与查询不在整段一致，容易解决。

容易发现后半部分不同位置 $r_i$ 的贡献为分段一次函数，可以用树状数组维护单点加，区间查询 $\sum v$ 和 $\sum v\times pos$。

时间复杂度 $\mathcal{O}((n+q)\log n)$，代码如下。


```cpp
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<cstdio>
#include<vector>
#include<random>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
#define her1 20081214
#define cht 998244353
#define I i64
#define IV void
#define ull unsigned long long
#define mem(x,val) memset(x,val,sizeof x)
#define F(i,j,n)for(register int i=j;i<=n;i++)
#define D(i,j,n)for(register int i=j;i>=n;i--)
#define E(i,now)for(register int i=first[now];i;i=e[i].nxt)
#define FL(i,j,n)for(register i64 i=j;i<=n;i++)
#define DL(i,j,n)for(register i64 i=j;i>=n;i--)
#define EL(i,now)for(register i64 i=first[now];i;i=e[i].nxt)
ll read(){
	ll ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')ans=ans*10+c-'0',c=getchar();
	return ans*f;
}
#undef ll
#include "assert.h"
mt19937_64 rnd(her1);
#include "functional"
using i64 = long long;
const int maxn = 1.5e5+5;
i64 n,m,q,b[maxn],a[maxn];char s[maxn];
struct sg{
	i64 l,r;
	bool operator<(const sg&V)const{
		return l<V.l;
	}
};
set<sg>st;pair<i64,i64>pi[maxn];
i64 L[maxn],R[maxn],V[maxn],tot,all;
struct node{
	i64 l,r,len,v,K,id;
}qwq[maxn*5];
IV add(i64 l,i64 r,i64 v){
	tot++;
	// L[tot]=l;R[tot]=r;V[tot]=v;
	qwq[tot]={l,r,r-l+1,v,0,0};
}
i64 sa[maxn],mx[maxn],sl[maxn],sr[maxn];

long long Ans[maxn];
struct BIT{
	long long c[maxn],qwq[maxn],tot,ans;bool vis[maxn];
	IV clr(){F(i,1,tot)vis[qwq[i]]=c[qwq[i]]=0;tot=0;}
	IV add(i64 p,long long v){
		for(;p<=n;p+=p&-p){
			if(!vis[p])vis[qwq[++tot]=p]=1;
			c[p]+=v;
		}
	}
	i64 Q(i64 p){
		if(p<1)return 0;p=min(p,n);
		ans=0;for(;p;p-=p&-p)ans+=c[p];return ans;
	}
	i64 Q(i64 l,i64 r){
		if(r<1||l>n)return 0;
		return Q(r)-Q(l-1);
	}
};

struct DS{
	#define ls (o<<1)
	#define rs (o<<1|1)
	i64 len[4*maxn],sum[4*maxn],tag[4*maxn];
	IV upd(i64 o){sum[o]=sum[ls]+sum[rs];}
	IV givet(i64 o,i64 v){sum[o]+=len[o]*v;tag[o]+=v;}
	IV pd(i64 o){if(!tag[o])return;givet(ls,tag[o]);givet(rs,tag[o]);tag[o]=0;}
	IV M(i64 o,i64 l,i64 r,i64 x,i64 y,i64 v){
		if(x<=l&&r<=y)return givet(o,v);if(r<x||l>y)return;pd(o);
		i64 mid=l+r>>1;M(ls,l,mid,x,y,v);M(rs,mid+1,r,x,y,v);upd(o);
	}
	i64 Q(i64 o,i64 l,i64 r,i64 x,i64 y){
		if(x<=l&&r<=y)return sum[o];if(r<x||l>y)return 0;pd(o);
		i64 mid=l+r>>1;return Q(ls,l,mid,x,y)+Q(rs,mid+1,r,x,y);
	}
	IV Build(i64 o,i64 l,i64 r){
		len[o]=r-l+1;if(l==r)return;i64 mid=l+r>>1;
		Build(ls,l,mid);Build(rs,mid+1,r);
	}
}ds;
struct DS2{
	BIT b1,b2;
	IV add(i64 p,i64 v){
		b1.add(p,v);
		b2.add(p,p*v);
	}
	i64 Q(i64 ql,i64 qr,i64 k){
		i64 sum=0;
		if(qr-ql+1>=k){
			sum+=b2.Q(ql,ql+k-1)-(ql-1)*b1.Q(ql,ql+k-1);
			sum+=(qr+k)*b1.Q(qr+1,qr+k-1)-b2.Q(qr+1,qr+k-1);
			sum+=k*b1.Q(ql+k,qr);
		}
		else{
			sum+=b2.Q(ql,qr)-(ql-1)*b1.Q(ql,qr);
			sum+=b1.Q(qr+1,ql+k-1)*(qr-ql+1);
			sum+=(qr+k)*b1.Q(ql+k,qr+k-1)-b2.Q(ql+k,qr+k-1);
		}
		return sum;
	}
}ds2;
int main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);

	n=read();m=read();q=read();
	FL(i,1,n)pi[i]=make_pair(b[i]=read(),i);
	F(i,1,m)a[i]=read();sort(pi+1,pi+1+n);

	F(i,1,m){
		F(j,1,a[i])s[++all]='A';
		F(j,1,a[i])s[++all]='B';
	}
	F(i,1,all){
		sr[i]=sr[i-1]+(s[i]=='A');
		sl[i]=sl[i-1]+(s[i]=='B');
	}
	F(i,1,m){
		mx[i]=max(mx[i-1],a[i]);
		sa[i]=sa[i-1]+2*a[i];
	}
	add(1,n,0);
	st.insert({1,n});
	F(i,1,n){
		i64 v=pi[i].first,pos=pi[i].second;
		auto p=prev(st.upper_bound({pos}));
		auto[l,r]=*p;add(l,r,v);st.erase(p);
		if(l<pos)st.insert({l,pos-1}),add(l,pos-1,-v);
		if(pos<r)st.insert({pos+1,r}),add(pos+1,r,-v);
	}
	F(i,1,q){
		i64 x=read(),ql=read(),qr=read(),ans=0;
		i64 pos=lower_bound(sa+1,sa+1+m,x)-sa-1;
		i64 nd=max(mx[pos],min(x-sa[pos],a[pos+1]));
		i64 dl=sl[x],dr=sr[x],K=dr-dl;ql+=dl;qr+=dl;
		qwq[++tot]={ql,qr,nd,0,K,i};
	}
	sort(qwq+1,qwq+1+tot,[](node A,node B){
		return A.len==B.len?A.id>B.id:A.len>B.len;
	});
	ds.Build(1,1,n);
	F(i,1,tot){
		if(!qwq[i].id){
			ds.M(1,1,n,qwq[i].l,qwq[i].r,qwq[i].v);
			ds2.add(qwq[i].r,qwq[i].v);
		}
		else{
			Ans[qwq[i].id]+=ds.Q(1,1,n,qwq[i].l,qwq[i].r);
			Ans[qwq[i].id]-=ds2.Q(qwq[i].l,qwq[i].r,qwq[i].K);
		}
	}
	F(i,1,q)printf("%lld\n",Ans[i]);
	return 0;
}
```

---

## 作者：Kubic (赞：3)

## $\operatorname{Subtask} 1$

暴力。

期望得分 $5$ 分。

## $\operatorname{Subtask} 2$

与正解关系不大但是有趣的做法。

先考虑 $x$ 为奇数的情况。我们取出 $w_1=p_{l+\lfloor\frac{x}{2}\rfloor},w_2=p_{l+\lfloor\frac{x}{2}\rfloor+1}$。

这个问题相当于有两个人在进行博弈，他们轮流操作，每次往左下或右下一格。

先手目标使得最终到达的位置的值**最小**，后手目标使得最终到达的位置的值**最大**。

对于后手，每次走与先手相反的方向就可以保证最后的值 $\ge\min\{w_1,w_2\}$。

对于先手，如果 $w_1<w_2$，那么第一步往左下走，否则第一步往右下走 ，然后每次走与后手相反的方向就可以保证最后的值 $\le\min\{w_1,w_2\}$。

因此答案就是 $\min\{w_1,w_2\}$。

对于 $x$ 为偶数的情况只需要手动模拟一层然后就可以转化为 $x$ 为奇数的情况。

期望得分 $10$ 分。

## $\operatorname{Subtask} 3$

先考虑 $a_1>a_i(i\in(1,m])$ 情况。

我们用单调队列模拟先做 $a_1$ 次 $\min$ 操作再做 $a_1$ 次 $\max$ 操作，得到的结果分别称为 $p_1$ 和 $p_2$。

如果 $x$ 位于 $a_1$ 之中，那么直接使用 RMQ 处理即可。

否则先考虑 $01$ 序列怎么做。

可以看出，做完 $a_1$ 操作之后，$01$ 段之间不会再发生合并的情况。

令 $s_i=\sum\limits_{j=1}^{i} a_i$。

如果 $x$ 在 $a_i$ 刚好结束的位置，那么答案就是 $p_2$ 中的第 $y+s_i-a_1$ 个元素。

如果 $x$ 在 $a_i$ 的 $\min$ 中，那么答案就是 $p_2$ 中 $[y+s_{i-1}-a_1,x+y-s_{i-1}-a_1]$ 中的最小值。

如果 $x$ 在 $a_i$ 的 $\max$ 中，那么答案就是 $p_2$ 中 $[x+y-s_i-a_1,y+s_i-a_1]$ 中的最小值。

容易发现，把 $01$ 序列变回一般序列做法也是一样的。

于是所有询问都可以用 RMQ 处理。



再考虑任意 $a$ 怎么做。

那么我们按照 $a$ 的前缀最大值分块，每一块都用上面的方法处理。

因为 $\sum a_i=\dfrac{n-1}{2}$，所以最多只有 $O(\sqrt{n})$ 个块。

时间复杂度 $O(n\sqrt{n}+q)$，期望得分 $25$ 分。

这一部分也可以做到 $O(n\log n+q\log^2n)$，请读者自行思考（

## $\operatorname{Subtask} 4$

设 $f_k=\sum\limits_{i=k}^n\min\limits_{j=i-k+1}^ia_j$，我们就是要求出所有 $f_k$。

对原序列跑单调栈，对于每一个 $i$ 维护以它为**右端点**的所有区间的 $\min$ 值。

对于每一个**左端点**，我们计算它对于答案序列的贡献，当它首次被加入单调栈的时候，我们对 $f$ 执行后缀加​。

接下来每一次它的值可能会被更新，那么我们再执行后缀减。

但我们显然不能每次都对每一个左端点暴力做，但可以发现，单调栈中的同一个区间中的当前值都是一样的，而且左端点位置都是连续的，那么我们实际上要做的就是对于一个固定的区间的每一个位置执行一个后缀减操作。可以使用二阶差分维护。

时间复杂度 $O(n+q)$。期望得分 $15$ 分。

## $\operatorname{Subtask} 5$

首先显然可以转化成求出两个前缀的答案。设 $f_{t,k}=\sum\limits_{i=k}^t\min\limits_{j=i-k+1}^ia_j$。

对于一个区间 $[l,r]$，以及 $t\in [r,n]$，这个区间可以贡献到 $f_{t,r-l+1\dots t-l+1}$。

只需要维护一个数据结构，支持：

- 对于一个 $1\times k$ 的矩形中的每个数 $+w$。
- 求一个斜边斜率为 $1$ 的直角梯形中的所有数的和。

其中所有修改均在询问前面。

可以用树状数组维护。时间复杂度 $O((n+q)\log n)$。期望得分 $30$ 分。

## $\operatorname{Subtask} 6\sim 7$

由 $\operatorname{Subtask} 4$，每个点值都已经是一个区间最大值或最小值的形式，并且同一行的点所代表的区间的左右端点都是公差为 $1$ 的等差数列。

那么我们可以直接套用 $\operatorname{Subtask} 6$ 的算法来解决这个问题。

时间复杂度 $O(n\sqrt{n}\log n+q\log n)$。$\operatorname{Subtask} 6$ 中 $m$ 比较小，可以通过，期望得分 $65$ 分。

但这样太慢了，我们有 $O(n\sqrt{n})$ 次修改和 $O(q)$ 次询问，所以可以用分块 $O(1)$ 修改，$O(\sqrt{n})$ 查询来平衡一下。

时间复杂度 $O((n+q)\sqrt{n})$。期望得分 $100$ 分。

---

## 作者：Mine_King (赞：2)

[在我得博客获得更好的阅读体验。](https://caijimk.netlify.app/post/luogup7922-sol)

# 洛谷 P7922 [Kubic] Pyramid 题解

[题目链接](https://www.luogu.com.cn/problem/P7922)

> 给定一个初始长度为 $n$ 的序列 $p$。
>
> 设当前 $p$ 的长度为 $L$，有以下两种操作：
>
> - A 操作先构造长度为 $L-1$ 的序列 $p'$ 满足 $p_i'=\min\{p_i,p_{i+1}\},i\in [1,L)$。然后用 $p'$ 代替 $p$。
>
> - B 操作先构造长度为 $L-1$ 的序列 $p'$ 满足 $p_i'=\max\{p_i,p_{i+1}\},i\in [1,L)$。然后用 $p'$ 代替 $p$。
>
> 再给定一个长度为 $m$ 的序列 $a$，表示一共进行 $m$ 组操作，第 $i$ 组中先进行 $a_i$ 次 A 操作，再进行 $a_i$ 次 B 操作。保证 $2\sum a_i=n-1$。
>
> 最后给定 $q$ 次询问，每次给出参数 $x,l,r$，你需要求出进行前 $x$ 个操作之后 $\sum\limits_{i=l}^r p_i$ 的值。
>
> **注意：询问中的 $x$ 指的是前 $x$ 个操作而不是前 $x$ 组操作，即有可能在某一组操作进行一部分时询问。**

## Subtask 1

暴力按题意模拟即可。

## Subtask 2

考虑连续的四个数 $a, b, c, d$，在两次操作后会留下两个数。

分讨 $a, b, c$ 的大小关系：

- 若 $a > b, b < c$，则一次操作后剩下 $b, b, \min\{c, d\}$，两次操作后剩下 $b, \max\{b, \min\{c, d\}\}$。
- 若 $a < b < c$，则一次操作后剩下 $a, b, \min\{c, d\}$，两次操作后剩下 $b, \max\{b, \min\{c, d\}\}$。
- 若 $a > b > c$，则一次操作后剩下 $b, c, \min\{c, d\}$，两次操作后剩下 $b, \max\{c, \min\{c, d\}\}$，即 $b, c$。
- 若 $a < b, b > c$，则一次操作后剩下 $a, c, \min\{c, d\}$，两次操作后剩下 $\max\{a, c\}, \max\{c, \min\{c, d\}\}$，即 $\max\{a, c\}, c$。

可以发现所有情况都会留下 $\min\{b, c\}$ 和一个大于 $\min\{b, c\}$ 的数，因此扩展到长度为 $2k$ 的序列后，经过 $2k - 2$ 次操作剩下的两个数一定是中间两个数的最小值和一个比它大的数，因此最后留下的就是中间两个数的最小值。

则当 $x$ 为奇数时，答案为 $\min\{p_{l + \lfloor\frac{x}{2}\rfloor}, p_{l + \lceil\frac{x}{2}\rceil}\}$；当 $x$ 为偶数时，手动模拟第一步即可转化为 $x$​ 为奇数的情况。

```cpp
namespace Subtask2 {
	int pp[150005];

	void main() {
		for (int i = 1; i < n; i++) pp[i] = min(p[i], p[i + 1]);
		while (q--) {
			int x, l, r;
			scanf("%d%d%d", &x, &l, &r);
			if (x % 2) printf("%d\n", min(p[l + x / 2], p[l + x / 2 + 1]));
			else printf("%d\n", max(pp[l + x / 2 - 1], pp[l + x / 2]));
		}
		return ;
	}
}
```

## Subtask 3

先考虑 $a_1 \ge a_i (i \in (1, m])$ 的情况。

考虑 01 序列。先把前 $2a_1$ 次操作做掉，在做前 $a_1$ 次操作时，每次操作每个不在首尾的极长的 $0$ 连续段长度都会增加至少 $1$，因此做完前 $a_1$ 次操作后，所有不在首尾的极长的 $0$ 连续段的长度都至少为 $a_1 + 1$。同理，做完后 $a_1$ 次操作后，所有不在首尾的极长的 $1$ 连续段的长度都至少为 $a_1 + 1$。由于 $a_i \le a_1$，且每次都是先做 $a_i$ 次 A 操作再做 $a_i$ 次 B 操作，因此之后的操作都不会出现合并两个连续段的情况。

然后分析之后的每个 $a_i$，发现对于不在首尾的极长连续段，其长度变化量为 $0$，而首尾的连续段的长度则会 $-a_i$，因此之后的每个 $a_i$ 等价于删去首尾各 $a_i$ 个数。

令 $s_i = \sum_{j = 1}^i a_j$，找到最小的 $i$ 使得 $x \le 2s_i$。

对于 $x \le 2a_1$ 的情况特殊处理。设做完前 $2a_1$ 个操作后得到的序列为 $p_2$。

- 若 $x = s_i$，则答案为 $p_2$ 中第 $l + s_i - a_1$ 个元素。
- 若 $x \le 2s_{i - 1} + a_i$，则答案为 $p_2$ 中 $[l + s_{i - 1} - a_1, l + x - s_{i - 1} - a_1]$ 中的最小值。
- 若 $x > 2s_{i - 1} + a_i$，考虑做完 $2s_i$ 次操作后时光倒流，这样又变成了取 $\min$ 操作，答案为 $p_2$ 中 $[l + x - s_i - a_1, l + s_i - a_1]$ 中的最小值。

容易发现以上分析对一般序列也成立。

再考虑任意 $a$ 怎么做，按 $a$ 的前缀最大值分块，每一块都按以上方法处理。因为 $\sum a_i = \frac{n - 1}{2}$，因此只会分成 $O(\sqrt{n})$ 段。

```cpp
int tmp[150005];

void updatemin(int len) {
	deque<int> q;
	for (int i = n; i >= 1; i--) {
		while (!q.empty() && p[q.back()] > p[i]) q.pop_back();
		q.push_back(i);
		if (q.front() > i + len) q.pop_front();
		tmp[i] = p[q.front()];
	}
	n -= len;
	for (int i = 1; i <= n; i++) p[i] = tmp[i];
	return ;
}
void updatemax(int len) {
	deque<int> q;
	for (int i = n; i >= 1; i--) {
		while (!q.empty() && p[q.back()] < p[i]) q.pop_back();
		q.push_back(i);
		if (q.front() > i + len) q.pop_front();
		tmp[i] = p[q.front()];
	}
	n -= len;
	for (int i = 1; i <= n; i++) p[i] = tmp[i];
	return ;
}

namespace Subtask3 {
	int s[150005];
	struct query {int x, l, r, ans;} qry[150005];
	vector<int> vec[150005];
	struct SegmentTree {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)

		int w[600005], l[600005], r[600005];

		void build(int ll, int rr, int now = 1) {
			l[now] = ll, r[now] = rr;
			if (ll == rr) {w[now] = p[ll]; return ;}
			int mid = (ll + rr) / 2;
			build(ll, mid, ls(now)), build(mid + 1, rr, rs(now));
			w[now] = min(w[ls(now)], w[rs(now)]);
			return ;
		}
		int query(int ll, int rr, int now = 1) {
			if (ll <= l[now] && r[now] <= rr) return w[now];
			int mid = (l[now] + r[now]) / 2, res = 0x3f3f3f3f;
			if (ll <= mid) res = min(res, query(ll, rr, ls(now)));
			if (mid < rr) res = min(res, query(ll, rr, rs(now)));
			return res;
		}

#undef ls
#undef rs
	} tr;
	struct SegmentTree2 {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)

		int w[600005], l[600005], r[600005];

		void build(int ll, int rr, int now = 1) {
			l[now] = ll, r[now] = rr;
			if (ll == rr) {w[now] = p[ll]; return ;}
			int mid = (ll + rr) / 2;
			build(ll, mid, ls(now)), build(mid + 1, rr, rs(now));
			w[now] = max(w[ls(now)], w[rs(now)]);
			return ;
		}
		int query(int ll, int rr, int now = 1) {
			if (ll <= l[now] && r[now] <= rr) return w[now];
			int mid = (l[now] + r[now]) / 2, res = 0;
			if (ll <= mid) res = max(res, query(ll, rr, ls(now)));
			if (mid < rr) res = max(res, query(ll, rr, rs(now)));
			return res;
		}

#undef ls
#undef rs
	} tr2;

	void main() {
		for (int i = 1; i <= m; i++) s[i] = s[i - 1] + 2 * a[i];
		for (int i = 1; i <= q; i++) {
			scanf("%d%d%d", &qry[i].x, &qry[i].l, &qry[i].r);
			int pos = lower_bound(s + 1, s + m + 1, qry[i].x) - s;
			vec[pos].push_back(i);
		}
		for (int i = 1, mx = 0, lstsum = 0; i <= n; i++) {
			if (mx < a[i]) {
				n -= 2 * (s[i - 1] - mx);
				for (int j = 1; j <= n; j++) p[j] = p[j + s[i - 1] - mx];
				s[i] = a[i], mx = a[i], lstsum += s[i - 1];
				tr.build(1, n);
				for (int j : vec[i]) {
					qry[j].x -= lstsum * 2;
					if (qry[j].x <= a[i]) qry[j].ans = tr.query(qry[j].l, qry[j].l + qry[j].x);
				}
				updatemin(a[i]);
				tr2.build(1, n);
				for (int j : vec[i])
					if (qry[j].x > a[i]) qry[j].ans = tr2.query(qry[j].l, qry[j].l + qry[j].x - a[i]);
				updatemax(a[i]);
				tr.build(1, n);
				continue;
			}
			s[i] = s[i - 1] + a[i];
			for (int j : vec[i]) {
				qry[j].x -= lstsum * 2;
				if (qry[j].x == 2 * s[i]) qry[j].ans = p[qry[j].l + s[i] - mx];
				else if (qry[j].x <= 2 * s[i - 1] + a[i])
					qry[j].ans = tr.query(qry[j].l + s[i - 1] - mx, qry[j].l + qry[j].x - s[i - 1] - mx);
				else qry[j].ans = tr.query(qry[j].l + qry[j].x - s[i] - mx, qry[j].l + s[i] - mx);
			}
		}
		for (int i = 1; i <= q; i++) printf("%d\n", qry[i].ans);
		return ;
	}
}
```

## Subtask 4

只需求 $f_k = \sum_{i = k}^n\min_{j = i - k + 1}^i a_j$。

从前往后扫描线，维护以当前点为右端点的区间产生的贡献。设当前右端点为 $r$，不妨认为 $p_{r + 1}$ 到 $p_n$ 均为 $+\infty$，这样每次加一个点 $r$ 就会使 $f_1, f_2, \ldots, f_{n - r + 1}$ 增加 $a_r$。用单调栈维护后缀最小值，每次维护单调栈会使左端点在一个区间内的区间的答案加上一个值。具体地，设在区间 $[l', r']$ 中的左端点 $l$ 满足 $\min_{i = l}^{r - 1} a_i = a_{r'}$ 且 $a_{r'} > a_r$，则所有左端点在 $[l', r']$ 内，右端点在 $[r, n]$ 内的区间的答案都要加上 $a_i - a_{r'}$。每个左端点对 $f$ 的贡献是一段区间，相邻两个左端点对应的区间是连续的（即两个区间的左端点的差等于右端点的差等于 $1$），用二阶差分维护即可。

## Subtask 5

考虑把 Subtask 4 的做法升维，只需求 $f_{t, k} = \sum_{i = k}^t \min_{j = i - k + 1}^i a_j$。

依然考虑扫描线，此时区间 $[l, r]$ 会对所有的 $t \in [r, n]$ 的 $f_{t, r - l + 1}, f_{t, r - l + 2}, \ldots, f_{t, t - l + 1}$ 产生贡献，这是一个直角梯形。

因此每次产生的贡献就是若干个连续的直角梯形，这里连续是指上一个梯形向右平移一格得到下一个梯形。

对 $f$ 的每一行进行差分，这样一个梯形就变成了一条直线和一条斜率为 $1$ 的斜线，多个梯形的贡献就是一个矩形和一个平行四边形。

把两个分开来算，矩形直接扫描线树状数组维护，然后变换坐标系，将 $(x, y)$ 变成 $(x, y - x)$，这样平行四边形也变成了矩形。

```cpp
namespace Subtask5 {
	struct BIT {
		long long w[150005];

		void update(int pos, long long val) {
			for (; pos < 150005; pos += pos & -pos) w[pos] += val;
			return ;
		}
		long long query(int pos) {
			long long res = 0;
			for (; pos >= 1; pos -= pos & -pos) res += w[pos];
			return res;
		}
	} bit1, bit2;
	struct query {int x, l, r;} qq[150005];
	long long ans[150005];
	vector<pair<int, int>> qry[150005];
	vector<tuple<int, int, int>> vec[150005];
	
	void update(int l, int r, long long val) {
		bit1.update(l, val), bit1.update(r + 1, -val);
		bit2.update(l, val * l), bit2.update(r + 1, -val * (r + 1));
		return ;
	}
	long long query(int r) {return bit1.query(r) * (r + 1) - bit2.query(r);}
	void solve(int op) {
		memset(bit1.w, 0, sizeof(bit1.w));
		memset(bit2.w, 0, sizeof(bit2.w));
		for (int i = 1; i <= n; i++) {
			for (auto j : vec[i]) update(get<0>(j), get<1>(j), get<2>(j));
			for (auto j : qry[i])
				if (j.second > 0) ans[j.second] += query(j.first + op * (n - i));
				else ans[-j.second] -= query(j.first + op * (n - i));
		}
		return ;
	}

	void main() {
		for (int i = 1; i <= q; i++) {
			scanf("%d%d%d", &qq[i].x, &qq[i].l, &qq[i].r);
			if (qq[i].x > a[1]) continue;
			qq[i].l += qq[i].x, qq[i].r += qq[i].x;
			qry[qq[i].r].emplace_back(qq[i].x + 1, i);
			qry[qq[i].l - 1].emplace_back(qq[i].x + 1, -i);
		}
		vector<int> stk;
		for (int i = 1; i <= n; i++) {
			while (!stk.empty() && p[stk.back()] >= p[i]) {
				int r = stk.back();
				stk.pop_back();
				int l = (!stk.empty() ? stk.back() : 0) + 1;
				// t in [i, n], k in [i - ll + 1, t - ll + 1] (tips: ll in [l, r])
				vec[i].emplace_back(i - r + 1, i - l + 1, p[i] - p[r]);
			}
			// t in [i, n], k in [1, t - i + 1]
			vec[i].emplace_back(1, 1, p[i]);
			stk.push_back(i);
		}
		solve(0);
		for (int i = 1; i <= n; i++) vector<tuple<int, int, int>>().swap(vec[i]);
		vector<int>().swap(stk);
		for (int i = 1; i <= n; i++) {
			while (!stk.empty() && p[stk.back()] >= p[i]) {
				int r = stk.back();
				stk.pop_back();
				int l = (!stk.empty() ? stk.back() : 0) + 1;
				// t in [i, n], k in [i - ll + 1, t - ll + 1] (tips: ll in [l, r])
				vec[i].emplace_back(n - r + 2, n - l + 2, p[r] - p[i]);
			}
			// t in [i, n], k in [1, t - i + 1]
			vec[i].emplace_back(n - i + 2, n - i + 2, -p[i]);
			stk.push_back(i);
		}
		solve(1);
		updatemin(a[1]);
		for (int i = 1; i <= n; i++) vector<pair<int, int>>().swap(qry[i]);
		for (int i = 1; i <= q; i++) {
			if (qq[i].x <= a[1]) continue;
			qq[i].x -= a[1];
			qq[i].l += qq[i].x, qq[i].r += qq[i].x;
			qry[qq[i].r].emplace_back(qq[i].x + 1, i);
			qry[qq[i].l - 1].emplace_back(qq[i].x + 1, -i);
		}
		for (int i = 1; i <= n; i++) vector<tuple<int, int, int>>().swap(vec[i]);
		vector<int>().swap(stk);
		for (int i = 1; i <= n; i++) {
			while (!stk.empty() && p[stk.back()] <= p[i]) {
				int r = stk.back();
				stk.pop_back();
				int l = (!stk.empty() ? stk.back() : 0) + 1;
				// t in [i, n], k in [i - ll + 1, t - ll + 1] (tips: ll in [l, r])
				vec[i].emplace_back(i - r + 1, i - l + 1, p[i] - p[r]);
			}
			// t in [i, n], k in [1, t - i + 1]
			vec[i].emplace_back(1, 1, p[i]);
			stk.push_back(i);
		}
		solve(0);
		for (int i = 1; i <= n; i++) vector<tuple<int, int, int>>().swap(vec[i]);
		vector<int>().swap(stk);
		for (int i = 1; i <= n; i++) {
			while (!stk.empty() && p[stk.back()] <= p[i]) {
				int r = stk.back();
				stk.pop_back();
				int l = (!stk.empty() ? stk.back() : 0) + 1;
				// t in [i, n], k in [i - ll + 1, t - ll + 1] (tips: ll in [l, r])
				vec[i].emplace_back(n - r + 2, n - l + 2, p[r] - p[i]);
			}
			// t in [i, n], k in [1, t - i + 1]
			vec[i].emplace_back(n - i + 2, n - i + 2, -p[i]);
			stk.push_back(i);
		}
		solve(1);
		for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
		return ;
	}
}
```

## Subtask 6

按 Subtask3 的方法分块后，每个点的值就变成了一个区间最值，区间的和就是若干个连续的区间的最值的和，发现这个形式和 Subtask 5 的形式一模一样，直接用 Subtask 5 的方法做即可，时间复杂度为 $O(n\sqrt{n}\log n + q\log n)$。

## Subtask 7

平衡一下复杂度，用 $O(1)$ 修改 $O(\sqrt{n})$ 查询的分块代替树状数组即可做到 $O((n + q)\sqrt{n})$​。

**Subtask 6 和 Subtask 7 均需注意常数优化。**

```cpp
// 長い夜の終わりを信じながら
// Think twice, code once.
#include <tuple>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

int n, m, q, p[150005], a[150005];
int tmp[150005];

void updatemin(int len) {
	deque<int> q;
	for (int i = n; i >= 1; i--) {
		while (!q.empty() && p[q.back()] > p[i]) q.pop_back();
		q.push_back(i);
		if (q.front() > i + len) q.pop_front();
		tmp[i] = p[q.front()];
	}
	n -= len;
	for (int i = 1; i <= n; i++) p[i] = tmp[i];
	return ;
}
void updatemax(int len) {
	deque<int> q;
	for (int i = n; i >= 1; i--) {
		while (!q.empty() && p[q.back()] < p[i]) q.pop_back();
		q.push_back(i);
		if (q.front() > i + len) q.pop_front();
		tmp[i] = p[q.front()];
	}
	n -= len;
	for (int i = 1; i <= n; i++) p[i] = tmp[i];
	return ;
}

namespace Subtask7 {
	const int B = 387;

	struct decompose {
		long long w[150005], sum[B + 5];

		void clear() {memset(w, 0, sizeof(w)); memset(sum, 0, sizeof(sum)); return ;}
		void update(int pos, long long val) {w[pos] += val, sum[(pos - 1) / B + 1] += val; return ;}
		long long query(int pos) {
			long long res = 0;
			int limit = (pos - 1) / B;
			for (int i = 1; i <= limit; i++) res += sum[i];
			for (int i = limit * B + 1; i <= pos; i++) res += w[i];
			return res;
		}
	} dc1, dc2;
	int s[150005];
	struct query {int x, l, r; long long ans;} qry[150005];
	vector<int> id[150005];
	vector<pair<int, int>> qq[150005];

	void update(int l, int r, long long val) {
		dc1.update(l, val), dc1.update(r + 1, -val);
		dc2.update(l, val * l), dc2.update(r + 1, -val * (r + 1));
		return ;
	}
	long long query(int r) {return dc1.query(r) * (r + 1) - dc2.query(r);}
	void solve(int op) {
		dc1.clear(), dc2.clear();
		vector<int> stk;
		for (int i = 1; i <= n; i++) {
			while (!stk.empty() && (!op ? p[stk.back()] >= p[i] : p[stk.back()] <= p[i])) {
				int r = stk.back();
				stk.pop_back();
				int l = (!stk.empty() ? stk.back() : 0) + 1;
				// t in [i, n], k in [i - ll + 1, t - ll + 1] (tips: ll in [l, r])
				update(i - r + 1, i - l + 1, p[i] - p[r]);
			}
			// t in [i, n], k in [1, t - i + 1]
			update(1, 1, p[i]);
			stk.push_back(i);
			for (auto j : qq[i])
				if (j.second > 0) qry[j.second].ans += query(j.first);
				else qry[-j.second].ans -= query(j.first);
		}
		dc1.clear(), dc2.clear();
		stk.clear();
		for (int i = 1; i <= n; i++) {
			while (!stk.empty() && (!op ? p[stk.back()] >= p[i] : p[stk.back()] <= p[i])) {
				int r = stk.back();
				stk.pop_back();
				int l = (!stk.empty() ? stk.back() : 0) + 1;
				// t in [i, n], k in [i - ll + 1, t - ll + 1] (tips: ll in [l, r])
				update(n - r + 2, n - l + 2, p[r] - p[i]);
			}
			// t in [i, n], k in [1, t - i + 1]
			update(n - i + 2, n - i + 2, -p[i]);
			stk.push_back(i);
			for (auto j : qq[i])
				if (j.second > 0) qry[j.second].ans += query(j.first + n - i);
				else qry[-j.second].ans -= query(j.first + n - i);
		}
		return ;
	}

	void main() {
		for (int i = 1; i <= m; i++) s[i] = s[i - 1] + 2 * a[i];
		for (int i = 1; i <= q; i++) {
			scanf("%d%d%d", &qry[i].x, &qry[i].l, &qry[i].r);
			int pos = lower_bound(s + 1, s + m + 1, qry[i].x) - s;
			id[pos].push_back(i);
		}
		for (int l = 1, r, lstsum = 0, lst = 0; l <= m; lst = l, l = r + 1) {
			r = l;
			while (r < m && a[r + 1] <= a[l]) r++;
			n -= 2 * (s[l - 1] - a[lst]);
			for (int i = 1; i <= n; i++) p[i] = p[i + s[l - 1] - a[lst]];
			lstsum += s[l - 1];
			for (auto i : id[l]) {
				qry[i].x -= lstsum * 2;
				if (qry[i].x <= a[l]) {
					int x = qry[i].x, ll = qry[i].l + x, rr = qry[i].r + x;
					qq[rr].emplace_back(x + 1, i);
					qq[ll - 1].emplace_back(x + 1, -i);
				}
			}
			solve(0);
			for (int i = 1; i <= n; i++) qq[i].clear();
			updatemin(a[l]);
			for (int i : id[l])
				if (qry[i].x > a[l]) {
					int x = qry[i].x - a[l], ll = qry[i].l + x, rr = qry[i].r + x;
					qq[rr].emplace_back(x + 1, i);
					qq[ll - 1].emplace_back(x + 1, -i);
				}
			solve(1);
			for (int i = 1; i <= n; i++) qq[i].clear();
			updatemax(a[l]);
			s[l] = a[l];
			for (int i = l + 1; i <= r; i++) {
				s[i] = s[i - 1] + a[i];
				for (int j : id[i]) {
					qry[j].x -= lstsum * 2;
					int x, ll, rr;
					if (qry[j].x == 2 * s[i]) {
						x = 0;
						ll = qry[j].l + s[i] - a[l];
						rr = qry[j].r + s[i] - a[l];
					} else if (qry[j].x <= 2 * s[i - 1] + a[i]) {
						x = qry[j].x - 2 * s[i - 1];
						ll = qry[j].l + qry[j].x - s[i - 1] - a[l];
						rr = qry[j].r + qry[j].x - s[i - 1] - a[l];
					} else {
						x = 2 * s[i] - qry[j].x;
						ll = qry[j].l + s[i] - a[l];
						rr = qry[j].r + s[i] - a[l];
					}
					qq[rr].emplace_back(x + 1, j);
					qq[ll - 1].emplace_back(x + 1, -j);
				}
			}
			solve(0);
			for (int i = 1; i <= n; i++) qq[i].clear();
		}
		for (int i = 1; i <= q; i++) printf("%lld\n", qry[i].ans);
		return ;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	Subtask7::main();
	return 0;
}
```

---

