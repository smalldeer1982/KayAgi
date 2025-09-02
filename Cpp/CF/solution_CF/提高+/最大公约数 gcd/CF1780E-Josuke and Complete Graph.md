# Josuke and Complete Graph

## 题目描述

Josuke 收到了一个巨大的无向带权完全图 $G$ 作为他祖父的礼物。该图形包含$10^{18}$ 个顶点。

这个礼物的特点是不同顶点 $u$ 和 $v$ 之间的边的权重等于 $\gcd(u,v)$ 。

Josuke 决定制作一个新的图 $G'$。为此，他选择两个整数 $l\le r$ ，并删除除 $l\le v\le r$ 的顶点 $v$ 之外的所有顶点以及与其相连的边。

现在 Josuke 想知道 $G'$ 中有的边多少种不同的权重。

## 样例 #1

### 输入

```
7
2 4
16 24
2 6
1 10
3 3
2562 2568
125 100090```

### 输出

```
2
6
3
5
0
5
50045```

# 题解

## 作者：MSqwq (赞：7)

虽然这题出没有啥水平，但是可以复习整除分块，所以写了一下。  
首先你看到 $l$ 的范围非常不正常，然后还是多测，不难推测到这题要么预处理，要么每次询问复杂度很低，首先对于前者预处理 $10^{18}$，肯定不可能所以考虑后者，然后大差不差你猜到了整除分块（数论分块）。  
但是没有出现 $\lfloor \frac{n}{i} \rfloor$ 的东西，那怎么思考呢。首先把整个问题分为两类，一类是 $\gcd < l$ ，另一类是 $l\le \gcd \le r$，对于后面很显然总数是 $\lfloor \frac{r}{2} \rfloor-(l-1)$，因为你要满足这个数落在区间内，并且这个数的两倍以上也要在这个区间内。  
对于第一类，可以考虑整除分块，你整除分块得到的是 $\lfloor \frac{n}{i} \rfloor$ 的东西，那么是不是相当于在这某一块内每个数都满足乘上这个数就是小于 $l$ 且最接近 $l$ 的数，那么设 $\lfloor \frac{n}{i} \rfloor$ 为 $k$ 只要满足这个数乘上 $k+1$ 和 $k+2$ 都落在 $l$ 到 $r$ 内是不是就可以了，那么每一块满足的个数就可以算了，复杂度是 $O(T\sqrt l)$。  
代码：  
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}

void solve()
{
	ll l=read(),r=read();
	ll ans=0,n=l-1;
	for(ll L=1,R;L<=n;L=R+1)
	{
		R=n/(n/L);
		ans+=max(0ll,min(R,r/(n/L+2))-L+1);
	}
	cout<<ans+max(0ll,r/2-n)<<endl;
}

int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}

```


---

## 作者：whdywjd (赞：6)

前置知识：整除分块。

先分析题目性质。

首先，根据题意，保存下来的边权中有 $x$ 当且仅当存在两个数 $l\leq i<j\leq r,\gcd(i,j)=x$。

如果存在一组解 $(i,j)$，则 $(i,i+x)$ 必然也是一组解。因为 $x|i,x|j,x|i+x$，可得 $l\leq i<i+x\leq j\leq r$；类似于 $\gcd(i,i+1)=1$，$x|i$ 时可得 $\gcd(i,i+x)=x$。

另外，$x|i$ 不仅是 $\gcd(i,i+x)=x$ 的充分条件，也是必要条件，可以简单地通过反证法证明。

所以，保存下来的边权中有 $x$ 当且仅当存在 $l\leq i<i+x\leq r,x|i$ 。

也就是说，$[l,r]$ 间存在至少两个 $x$ 的倍数。

即： $\lfloor \frac{r}{x}\rfloor\geq\lfloor \frac{l-1}{x}\rfloor+2$。

注意到 $l\leq10^9$，考虑对 $x\leq l-1$ 的情况整除分块。

（$x\geq l$ 的情况不是不行，但是我们稍后再说。）

设 $[a,b]$ 是一个极大区间，满足 $\lfloor \frac{l-1}{a}\rfloor=\lfloor \frac{l-1}{b}\rfloor=d$ 。

则要求出 $[a,b]$ 范围内的满足 $\lfloor \frac{r}{x}\rfloor\geq d+2$ 的 $x$ 数量。

$\lfloor \frac{r}{x}\rfloor\geq d+2$，即 $\frac{r}{x}\geq d+2$；

可得 $\frac{r}{d+2}\geq x$，
即$x\leq\lfloor\frac{r}{d+2}\rfloor$。

所以 $x$ 的上界为 $\min(b,\lfloor\frac{r}{d+2}\rfloor)$。

这部分的代码如下：

```cpp
ll l, r;
scanf("%lld %lld", &l, &r);
l--; // 方便处理l-1
ll ans = 0;
for(ll a = 1, b; a <= l; a = b + 1)
{
    ll d = l / a;
    b = l / d;
    ans += max(min(b, r / (d + 2)) - a + 1, 0ll);
}
```

再说 $x\geq l$ 的情况。

此时 $\lfloor \frac{l-1}{x}\rfloor=0$，故 $\lfloor\frac{r}{x}\rfloor\geq2$

可得 $x\leq\lfloor\frac{r}{2}\rfloor$。

这部分的代码：

```cpp
l++; // 把l-1还原成l
ans += max(r / 2 - l + 1, 0ll);
```

完整代码：

```cpp
#include <cstdio>
#include <algorithm>
#define ll long long

using namespace std;

void MAIN()
{
    ll l, r;
    scanf("%lld %lld", &l, &r);
    l--; // 方便处理l-1
    ll ans = 0;
    for(ll a = 1, b; a <= l; a = b + 1)
    {
        ll d = l / a;
        b = l / d;
        ans += max(min(b, r / (d + 2)) - a + 1, 0ll);
    }
    l++; // 把l-1还原成l
    ans += max(r / 2 - l + 1, 0ll);
    printf("%lld\n", ans);
}

int main()
{
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while(T--)
        MAIN();
    return 0;
}
```


---

## 作者：Kreado (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1780E)。

没打比赛，但感觉挺简单的。

#### 思路

将每个问题分成两个子问题，也就是 $\gcd(u,v)< L$ 和 $L\le \gcd(u,v)\le R$。第一个子问题，判断 $[L,R]$ 内是否有两个以上的 $d$ 的倍数，可以写成这样

$$\sum_{d=1}^{L-1}[\lfloor\frac{R}{d}\rfloor -\lfloor\frac{L-1}{d}\rfloor\ge2]$$

显然可以整除分块，当然 $R>3L$ 时，答案是 $R\div2$，时间复杂度 $O(T\sqrt L)$。

对于第二个子问题，我们只用判断 $2\times\gcd(u,v)$ 是否在区间内，显然答案为 $\lfloor \frac{R}{2}\rfloor-(L-1)$。

#### 贴贴代码

```cpp
inline void solve(){
	scanf("%lld%lld",&L,&R);ll res=0;
	if(R>3*L+100) return printf("%lld\n",R/2),void();
	for(ll l=1,r;l<=L-1;l=r+1){
		r=min((L-1)/((L-1)/l),R/(R/l));
		res+=((R/l-(L-1)/l)>=2)*(r-l+1);
	}
	printf("%lld\n",max(0ll,R/2-(L-1))+res);
}
```


---

## 作者：DaiRuiChen007 (赞：2)

# CF1780E 题解



## 思路分析

把条件转化成统计所有 $k$ 使得存在 $l\le x,y\le r$ 且 $\gcd(x,y)=k,x\ne y$ 的 $k$ 的数量。

注意到只要 $[l,r]$ 中有至少 $2$ 个 $k$ 的倍数，那么 $k$ 就满足要求。

因此等价于统计所有 $\left\lfloor \dfrac rk\right\rfloor-\left\lceil \dfrac lk\right\rceil+1\ge 2$ 的 $k$ 的数量即可，这又可以等价于 $\left\lfloor\dfrac rk\right\rfloor -\left\lfloor\dfrac{l-1}k\right\rfloor \ge 2$ 的 $k$ 的数量。

显然对 $l-1$ 整除分块：

- 对于所有 $k\le\sqrt{l-1}$ 的 $k$，暴力枚举并统计即可。

- 对于所有 $k>\sqrt{l-1}$ 的 $k$，枚举 $\left\lfloor\dfrac {l-1}k\right\rfloor=i$，显然 $i$ 的值域也是 $\Theta(\sqrt l)$ 这一级别的。

  那么我们要求：$\left\lfloor\dfrac {l-1}k\right\rfloor=i,\left\lfloor\dfrac rk\right\rfloor\ge i+2$，简单拆开变形一下即可得到 $\left\lceil\dfrac l{i+1}\right\rceil\le k\le\min\left\{\left\lfloor\dfrac{l-1}i\right\rfloor,\left\lfloor\dfrac r{i+2}\right\rfloor\right\}$，特判 $i=0$ 的情况即可。

注意特判 $l=1$ 的情况，此时答案为 $\left\lfloor\dfrac r2\right\rfloor$。

时间复杂度 $\Theta(t\sqrt l)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=1e18;
inline void solve() {
	int l,r;
	scanf("%lld%lld",&l,&r);
	--l;
	if(l==0) {
		printf("%lld\n",r/2);
		return ;
	}
	int ans=0,d=0;
	for(int k=1;k*k<=l;++k) {
		d=(l/k);
		if((r/k)-(l/k)>=2) ++ans;
	}
	for(int i=0;i<d;++i) {
		int L=(l+i+1)/(i+1);
		int R=r/(i+2);
		if(i>0) R=min(R,l/i);
		if(L<=R) ans+=R-L+1;
	}
	printf("%lld\n",ans);
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：Miraik (赞：2)

我们把题意转化一下，就是求 $[l,r]$ 间所有不同数对的 $\gcd$ 种类数。

考虑对于一个 $\gcd$ 的值 $g$，我们判定它是否存在，实际上只需要判定 **第二小的不小于 $l$ 的 $g$ 的倍数是否 $\le r$ 即可**。

把这个东西写出来，实际上就是 $ \lfloor \frac{l-1}{g} \rfloor +2 \le \lfloor \frac{r}{g} \rfloor$。

而且题目告诉你 $l\le10^9$，不难想到整除分块处理，容易发现在每段 $ \lfloor \frac{l-1}{g} \rfloor$ 相同的区间上，答案必然是一段前缀，算一下答案区间的右端点即可。

特殊处理一下 $g \ge l$ 的情况，此时相当于 $\lfloor \frac{r}{g} \rfloor \ge 2$，那么此时的答案贡献区间即为 $[l,\lfloor \frac{r}{2} \rfloor]$。

```cpp
inline void solve(){
	l=read()-1,r=read(),ans=max(0ll,r/2-l);
	for(int L=1,R=0;L<=l;L=R+1){
		R=l/(l/L);
		int pos=min(R,r/(l/L+2));
		if(pos>=L) ans+=pos-L+1;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：masonpop (赞：0)

这题也是套路了，但凡数论模型掌握熟练一点的都能做。

注意到存在 $i,j\in[l,r]$，使得 $\gcd(i,j)=k$ 等价于区间内至少有两个 $k$ 的倍数。这一点不难证明。

前缀和一下，等价于 $\lfloor\frac{l-1}{k}\rfloor+2\leq \lfloor\frac{r}{k}\rfloor$。

先考虑 $k\leq l-1$ 的情况。对左边这个式子整除分块。设 $\lfloor\frac{l-1}{k}\rfloor=t$，此时 $k$ 的范围区间为 $[p,q]$。又由于 $\lfloor\frac{r}{k}\rfloor\geq t+2$，则容易求出 $k\leq \lfloor\frac{r}{t+2}\rfloor$。此时就可以求出，$k\in [p,\min\{q,\lfloor\frac{r}{t+2}\rfloor\}]$。不难求出这样 $k$ 的个数。

再考虑 $k\ge l$ 的情况。此时 $\lfloor\frac{r}{k}\rfloor\ge 2$，故 $k\in [l,\lfloor\frac{r}{2}\rfloor]$。不难求个数。

最后相加即可。时间复杂度 $O(\sqrt l)$。[代码](https://codeforces.com/contest/1780/my)。

---

## 作者：Feyn (赞：0)

显然一个数 $t$ 合法当且仅当存在 $x$，使得 $xt$ 和 $(x+1)t$ 都在 $[l,r]$ 之中，然后就可以把限制转化成 $\lfloor\dfrac{r}{t}\rfloor-\lfloor\dfrac{l-1}{t}\rfloor\ge 2$ 的形式，而题目中保证了 $l\le 10^9$，这提示我们可以进行数论分块。对于每一块相当于是 $n=\lfloor\dfrac{l-1}{t}\rfloor$ 已经确定了，我们要找的其实就是有多少 $t$ 满足 $\lfloor\dfrac{r}{t}\rfloor\ge n+2$，这个问题就非常简单了。这个方法的复杂度是 $\sum\sqrt{l}$。

```cpp
void solve(){
	int l,r,ans=0;read(l);l--;read(r);
	for(int ll=1,rr;ll<=l;ll=rr+1){
		rr=l/(l/ll);
		int lim=min(rr,r/(l/ll+2));
		ans+=max(lim-ll+1,0ll);
	}
	ans+=max(r/2-l,0ll);
	printf("%lld\n",ans);
}

signed main(){
	
	int test;read(test);
	while(test--)solve();
	
	return 0;
}
```

---

