# Teleporters

## 题目描述

在一条直线上有 $n+1$ 个传送机，位于点 $0,a_1,a_2,a_3,...,a_n$. 如果在 $x$ 点和 $y$ 点都有传送机，那么可以从 $x$ 点传送到 $y$ 点，能量开销为 $(x-y)^2$.

你想安装一些额外的传送机，这样就可以从 $0$ 点传送到 $a_n$ 点（可能是通过其他传送机）且总共花费的能量不超过 $m$。**你安装的每个传送机必须位于整数点。**

现在你需要知道至少需要安装的传送机数量是多少。

## 样例 #1

### 输入

```
2
1 5
7```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 5
6```

### 输出

```
3```

## 样例 #3

### 输入

```
1
5
5```

### 输出

```
4```

## 样例 #4

### 输入

```
1
1000000000
1000000043```

### 输出

```
999999978```

# 题解

## 作者：UltiMadow (赞：10)

显然我们可以把 $a$ 所分成的每段距离分开来考虑

设 $f(len,x)$ 表示长度为 $len$ 的区间额外放 $x$ 个传送器的代价

显然平均分配每段距离是最优的，于是有 $f(len,x)=(x-(len\bmod (x+1)))(\lfloor \frac {len}{x+1}\rfloor)^2+(len\bmod (x+1))(\lceil \frac{len}{x+1}\rceil)^2$

观察一下这个式子，我们可以得到一个结论：$f(len,x)-f(len,x+1)$ 是单调不增的（不太会证，但可以理解一下（

也就是说每一段每增加一个传送器代价减少的变化量单调不增

我们考虑二分一个最少减小量 $d$，对于每一段距离二分求出 $f(len,x-1)-f(len,x)\ge d$ 的最大的一个 $x$，并在这一段放 $x$ 个传送器，设这样的总代价为 $g(d)$，显然我们要求出 $g(d)\le m$ 的最大的一个 $d$

假设这个 $d$ 已经求出来了，但我们会发现 $d$ 其实不一定是最优解，也就是说可以在 $d+1$ 的基础上加若干个传送器满足总代价 $\le m$，而不一定要把 $d$ 的全部加进去

我们可以先把 $g(d+1)$ 算出来，由于每增加一个传送器代价必定减少 $d$，那么我们就可以把最少增加的传送器个数算出来了：$\lceil\frac{g(d+1)-m}{d}\rceil$

时间复杂度 $\mathcal O(n\log^2a)$

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 200010
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
int n,m,a[MAXN];
int f(int len,int x){
	int cr=len%(x+1),cl=x+1-cr;
	int vr=(len+x)/(x+1),vl=len/(x+1);
	return vr*vr*cr+vl*vl*cl;
}
pii calc(int len,int del){
	int l=1,r=len-1,ret=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(f(len,mid-1)-f(len,mid)>=del)
			ret=mid,l=mid+1;
		else r=mid-1;
	}return mp(f(len,ret),ret);
}
pii check(int del){
	pii ret=mp(0,0);
	for(int i=1;i<=n;i++){
		auto now=calc(a[i],del);
		ret.fi+=now.fi;ret.se+=now.se;
	}return ret;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=n;i;i--)a[i]-=a[i-1];
	scanf("%lld",&m);
	int l=0,r=inf,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid).fi<=m)l=mid+1,ans=mid;
		else r=mid-1;
	}
	auto R=check(ans+1);
	printf("%lld",R.se+(R.fi-m+ans-1)/ans);
	return 0;
}
```

---

## 作者：樱雪喵 (赞：7)

题中给出的 $a_i$ 已经将序列分成了若干段，我们只需要依次考虑每一段的最优策略。

设 $f(x,y)$ 表示把一个初始长度为 $x$ 的段分成 $y$ 小段，这一部分所要花费的最少能量。根据均值不等式，我们希望分成的 $y$ 段长度尽可能均匀。那么可以得到式子
$$
f(x,y)=\left(\left\lfloor\frac{x}{y}\right\rfloor\right)^2\times(y-x\bmod y)+\left(\left\lfloor\frac{x}{y}\right\rfloor+1\right)^2\times (x\bmod y)
$$

发现 $f(x,y)$ 是凸的，也就是说当 $x$ 一定时，$f(x,y)-f(x,y+1)$ 的值随 $y$ 的增大单调递减。所以我们可以得到这样的暴力做法：

维护一个大根堆和每段已经安装的传送机数 $c_i$，每次选择 $f(a_i,c_i)-f(a_i,c_i+1)$ 最大的段安装。

考虑优化这个暴力，由于大根堆的堆顶值单调不增，我们可以二分最后结束时的堆顶 $k$。  
那么最终的 $c_i$ 就是令 $f(a_i,x)-f(a_i,x+1)\ge k$ 的最大的 $x$。这个同样可以二分，这样我们已经知道在大根堆顶为 $k$ 时结束整个过程时的答案，把它与 $m$ 比较即可。

而这样做不一定是最优的，因为我们要在 $k$ 不变且答案不大于 $m$ 的情况下最小化 $c_i$ 的和。每个 $c_i$ 减 $1$ 会令总代价增加 $k$，设当前的总代价为 $sum$，则答案为 $(\sum c_i)-\lfloor\frac{m-sum}{k}\rfloor$。

时间复杂度是 $O(n\log^2 V)$，$V$ 为值域。

```cpp
#define int long long 
const int N=2e5+5;
int n,m,a[N],c[N],ans;
il int get(int x,int y)
{
    if(!y) return 1e9;
    int len=x/y,cnt=x%y;
    return len*len*(y-cnt)+(len+1)*(len+1)*cnt;
}
il bool check(int k)
{
    for(int i=1;i<=n;i++)
    {
        int l=1,r=a[i];
        while(l<r)
        {
            int mid=(l+r+1)>>1;
            if(get(a[i],mid-1)-get(a[i],mid)>=k) l=mid;
            else r=mid-1;
        }
        c[i]=l;
    }
    int res=0;
    for(int i=1;i<=n;i++) res+=get(a[i],c[i]);
    return res<=m;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=n;i;i--) a[i]-=a[i-1];
    m=read();
    int l=0,r=1e18;
    while(l<r)
    {
        int mid=(l+r+1)>>1;
        if(check(mid)) l=mid;
        else r=mid-1;
    }
    check(l);
    int ans=0,sum=0;
    for(int i=1;i<=n;i++) ans+=c[i]-1,sum+=get(a[i],c[i]);
    printf("%lld\n",ans-(l?((m-sum)/l):0));
    return 0;
}
```

---

## 作者：james1BadCreeper (赞：4)

可以将原问题划分成几段，然后对于每一段放置传送器的话分的约均匀越好，全局的最小两相邻传送机距离应该是一个（尽可能满足平均），这样就可以用 $f(x,k)$ 来表示 $0\rightarrow x$ 中额外插入 $k$ 个的最小代价，显然是好求的。

直接二分需要安装的传送机数量？我们好像没有办法 `check`，只知道最多传送机数量的话没有一个合适的贪心策略。我们对另一个条件——总花费进行考虑。因为花费越大直接意味着传送机数量越少。

注意到 $f(x,k-1)-f(x,k)$ 随着 $k$ 的增大单调不增，这样可以在外层二分其值 $v$ 来代表一个段内的最小传送机距离（类似 wqs 的思想），找出一个 $f(x,k-1)-f(x,k)\ge v$ 的最大 $k$，而 $k$ 越大花费越小，直接利用 $k$ 来进行贪心求出每一段的最小代价，与 $m$ 比较来确定二分的答案。

设二分出来的答案是 $k$，选完之后 $m$ 的值还有剩余，我们尽可能多的值选择 $k+1$ 来榨干 $m$ 的剩余价值。

时间复杂度 $O(n\log^2 V)$。

```cpp
#include <bits/stdc++.h>
#define i64 long long
#define pii pair<i64, int> 
#define fi first
#define se second
using namespace std;
const i64 INF = 1e18 + 500; 

int n; i64 m; 
int a[200005]; 

inline i64 f(int x, int k) { // 0->x 放 k 
    i64 va = (x + k) / (k + 1), vb = x / (k + 1); 
    int ra = x % (k + 1), rb = k + 1 - ra; 
    return ra * va * va + rb * vb * vb; 
}

int calc(int len, i64 v) { // f(len, x - 1) - f(len, x) >= v 的最大 x
    int L = 0, R = len; 
    while (L + 1 != R) {
        int mid = L + R >> 1; 
        if (f(len, mid - 1) - f(len, mid) >= v) L = mid; 
        else R = mid; 
    }
    return L; 
}

pii check(i64 v) {
    pii ans(0, 0); 
    for (int i = 1; i <= n; ++i) {
        int x = calc(a[i], v); 
        ans.fi += f(a[i], x), ans.se += x; 
    }
    return ans; 
}

int main(void) {
    scanf("%d", &n); for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
    for (int i = n; i >= 1; --i) a[i] -= a[i - 1]; scanf("%lld", &m); 
    i64 L = -1, R = INF + 1; 
    while (L + 1 != R) {
        i64 mid = L + R >> 1; 
        if (check(mid).fi <= m) L = mid; 
        else R = mid; 
    }
    pii res = check(L + 1); 
    
    printf("%lld\n", res.se + (res.fi - m + L - 1) / L); 
    return 0;
}
```

---

## 作者：dead_X (赞：3)

## 前言
对标普及组 T3。
## 思路
首先每两个相邻的点之间是可以独立考虑的。

我们记 $F(x,y)$ 为将一个长度为 $x$ 的段分成 $y$ 段后的最小代价。

不难证明在 $y\leq x$ 时， $F(x,y)$ 是凸的，这也意味着 $G(x,y)=F(x,y)-F(x,y+1)$ 是递减的。

这就可以用个堆贪心了，时间复杂度 $O(a\log n)$。

然后我们又能发现 $F(x,y)$ 一定是尽可能平均地划分的，即分成 $x\bmod y$ 个 $\lfloor\frac{x}{y}\rfloor+1$ 和 $y-(x\bmod y)$ 个 $\lfloor\frac{x}{y}\rfloor$。

显然在 $\lfloor\frac{x}{y}\rfloor$ 固定的时候， $G(x,y)$ 也是固定的，因此一个 $x$ 只有 $O(\sqrt x)$ 段不同的 $G(x,y)$。

于是我们只需要在之前的堆贪心基础上快速执行一段的决策即可，时间复杂度 $O(\sqrt{na}\log n)$。
## 代码
```cpp
// Problem: F. Teleporters
// Contest: Codeforces - Educational Codeforces Round 126 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1661/problem/F
// Memory Limit: 512 MB
// Time Limit: 7000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//And in that light,I find deliverance.
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
struct node
{
	int x,d,g;
	bool operator<(const node&t)const{return g<t.g;}
};
priority_queue<node> q;
inline int F(int x,int y)
{
	int v0=x/y,v1=v0+1,k1=x-v0*y,k0=y-k1;
	return v1*v1*k1+v0*v0*k0;
}
int a[1000003];
signed main()
{
	int n=read(),ans=0,sum=0;
	for(int i=1; i<=n; ++i) a[i]=read();
	for(int i=n; i>=1; --i) a[i]-=a[i-1],sum+=a[i]*a[i];
	for(int i=1; i<=n; ++i) if(a[i]>1)
		q.push((node){a[i],1,F(a[i],1)-F(a[i],2)});
	sum-=read();
	while(sum>0)
	{
		node t=q.top();q.pop();
		if(t.x/t.d!=t.x/(t.d+1))
		{
			sum-=t.g,++ans,++t.d,
			t.g=F(t.x,t.d)-F(t.x,t.d+1);
			if(t.g) q.push(t);
			continue;
		}
		int tmp=t.x/(t.x/t.d);
		if(t.g*(tmp-t.d)>=sum)
		{
			ans+=(sum-1)/t.g+1;
			break;
		}
		else sum-=t.g*(tmp-t.d),ans+=tmp-t.d,
		t.d=tmp,t.g=F(t.x,t.d)-F(t.x,t.d+1);
		if(t.g) q.push(t);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：chzhc (赞：2)

### 题意

直线上有 $n + 1$ 个传送器，分别位于 $0, a_1, a_2, \cdots, a_n$，如果两个点都有传送器，则可以从点 $x$ 传送到 $y$，并且花费 $(y - x)^2$，你想要安装一些额外的传送器（只能在整点上安装），使得可以从 $0$ 传送到 $a_n$ 且花费少于 $m$。你要最小化这个安装数量。

数据范围：$1 \leq n \leq 2 \times 10^5$，$1 \leq a \leq 10^9$，$a_n \leq m \leq 10^{18}$。

### 做法

首先可以发现每一段中安装传送器与其他段是互不干扰的。我们设 $f(x, k)$ 表示将长度为 $x$ 的段分为 $k$ 段（即安装 $k - 1$ 个传送器）所需的最小费用。$f(x, k)$ 的计算是很容易的，显然，这 $k$ 段的长度两两顶多差 $1$（如果有两段长度相差大于 $1$，调整这两段的大小一定能更小化费用），具体的，我们设长度为 $w$ 的段有 $b$ 个，长度为 $w + 1$ 的段有 $c$ 个，可以列出方程组：
$$
\begin{cases}
wb + (w + 1)c = x \\
 b + c = k
\end{cases}
$$
可以得到：$wk + c = x$，我们要最小化 $c$，故可以得到：$c = x \bmod k$，$b = k - c$，$w = \frac{(x - c)}{k}$。

故 $f(x, k) = w^2\times b + (w + 1)^2 \times c$。

引理 1. $\forall k\in[1, x]$，都有 $f(x, k - 1) - f(x, k) \geq f(x, k) - f(k + 1)$。

看起来就感觉很正确，感性理解一下，具体证明可以见 [Link](https://codeforces.com/blog/entry/101790)。

现在有了引理 1，我们考虑怎么做。

我们可以转换一下思路，原先花费为 $c = \sum_{i = 1}^n (a_i - a_{i - 1})^2$（$a_0 = 0$），差异为 $c - m$，现在有 $n$ 个升级列表，假设第 $i$ 段升级了 $j$ 次，每次升级都可以理解为将差异减小了 $f(a_i - a_{i - 1}, j - 1) - f(a_i - a_{i - 1}, j)$，比如将第 $i$ 段升级了 $2$ 次，则总减小量为 $f(a_i - a_{i - 1}, 0) - f(a_i - a_{i - 1}, 1) + f(a_i - a_{i - 1}, 1) - f(a_i - a_{i - 1}, 2) = f(a_i - a_{i - 1}, 0) - f(a_i - a_{i - 1}, 2)$，我们发现这正好符合差异减小的定义。因此，问题转化为最少升级几次可以使得总减小量不小于 $c - m$。

容易发现，我们每次都选择最大差异量的进行升级最优秀，根据引理 1，这么选择一定满足选取某一段连续升级 $k$ 次最优，这也正好符合上文总减小量的含义。

显然最后一次升级的差异量 $\Delta$ 是有单调性的，我们考虑二分这个差异量 $\Delta$，判断升级所有差异量大于等于 $\Delta$ 时是否能满足总花费小于等于 $m$（对应着总减小量是否小于 $c - m$），判断时对于每一段再次进行二分，找到最大的 $k$ 使得 $f(a_i - a_{i - 1}, k - 1) - f(a_i - a_{i - 1}, k) \geq \Delta$，对应的也就能判断出当前差异量下是否能满足花费小于等于 $m$。

我们找到了这个满足条件且最大的 $\Delta$，设 $g(\Delta)$ 为该情况下的总花费，$h(\Delta)$ 为该情况下的安装数量。那么答案就是 $h(\Delta)$ 吗？并不，我们注意到只有某些段的差异量要取到 $\Delta$，有 $\left \lfloor \frac{m - g(\Delta)}{\Delta} \right \rfloor$ 段是无需更新到 $\Delta$ 的，故答案便为 $h(\Delta) - \left \lfloor \frac{m - g(\Delta)}{\Delta} \right \rfloor$。

时间复杂度 $\mathcal O(n \log^2 A)$ $A$ 大约为值域级别。

[评测链接](https://codeforces.com/contest/1661/submission/153469116)。

---

## 作者：Gorenstein (赞：1)

根据均值不等式，显然点排得越均匀越优。

这句话包含两个关键点，第一个是若要在输入的每两个相邻传送机之间插入若干个新的传输机，那么这些安插的传输机需要尽量均匀；第二个是从整体上看，整个轴上所有传输机需要尽量均匀。

若不考虑位置需为整数的限制，对于每一段，假设长度为 $l_i$，设安插了 $x$ 个后的花费为 $f_i(x)$，那么：

$$
f_i(x)=\left(\frac{l_i}{x+1}\right)^2(x+1)=\frac{l_i^2}{x+1}
$$

因为整体上也要尽量均匀，那么我们不妨设 $\frac{l_i}{x_i+1}=k$，得到 $x=\frac{l_i-k}{k}$。

考虑 $f_i(x)$ 的一阶导：

$$
f_i'(x)=\frac{-l_i^2}{(x+1)^2}
$$

由 $x$ 与 $l$ 在最优时的关系我们可以得到 $f'_i(\frac{l_i-k}{k})=-k^2$，是定值。

现在加上了位置为整数的限制，那么相应的求导就变为了差分，含义为 $f_i(x)-f_i(x-1)$，即传送机从 $x$ 个减少一个后总花费的增加量，设其为 $-d$。我们二分这个 $d$，求出每一段的相应的 $x_i$，即给每一段都增加 $x_i$，设和为 $S$。二分找到最大的 $d$ 使得 $S\leqslant m$。

由于上面得到用解出的 $x$ 代回 $f'_i(x)$ 后是定值，从而给每一段都按插 $x_i$ 个能够使整体均匀，达到最优。

位置为整数，那么 $x$ 不能由上面的过程直接解出来。考虑 $f_i(x)$ 的二阶导：

$$
f''_i(x)=\frac{2l^2}{(x+1)^3}
$$

肉眼观察可得在 $x>0$ 时 $f''_i(x)>0$，所以 $f_i(x)$ 下凸。斜率已知，那么二分去求即可。

由于位置为整数，所以不能保证这么下来是最优解。那么求出 $d$ 之后先按 $d+1$ 算，因加一个就会减少 $d$，从而直接把需要额外加的传送机个数算上去即可。

---

