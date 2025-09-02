# [ARC150D] Removing Gacha

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc150/tasks/arc150_d

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点の根付き木があります。頂点 $ 1 $ はこの木の根であり、頂点 $ i\ (2\leq\ i) $ の親頂点は頂点 $ p_i $ です。

各頂点は白、黒の色を持っています。はじめすべて頂点の色は白です。

根付き木において、頂点 $ 1,\ i $ を結ぶ唯一の単純パス上の頂点 (頂点 $ 1,\ i $ 含む) の色がすべて黒であるとき、頂点 $ i $ を「よい頂点」といいます。また、「よい頂点」ではない頂点を「わるい頂点」といいます。

すべての頂点の色が黒になるまで「『わるい頂点』から一様ランダムに頂点を $ 1 $ つ選び、その頂点を黒色で上塗りする」という操作を行います。

操作を行う回数の期待値を $ \bmod\ 998244353 $ で求めてください。

 期待値 $ \text{mod\ }{998244353} $ の定義 求める期待値は必ず有理数になることが証明できます。 また、この問題の制約のもとでは、その値を既約分数 $ \frac{P}{Q} $ で表した時、$ Q\ \not\ \equiv\ 0\ \pmod{998244353} $ となることも証明できます。 よって、$ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\ &amp;lt\ 998244353 $ を満たす整数 $ R $ が一意に定まります。 この $ R $ を答えてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ p_i\ <\ i $
- 入力される値はすべて整数

### Sample Explanation 1

例えば $ 1,\ 2,\ 3 $ 回目の操作で順に頂点 $ 1,\ 2,\ 4 $ が選ばれた場合を考えます。このとき、頂点 $ 1,\ 2 $ は「よい頂点」ですが、頂点 $ 4 $ は祖先である頂点 $ 3 $ が白色であるため「わるい頂点」です。よって $ 4 $ 回目の操作で頂点を選ぶ際は頂点 $ 3,\ 4 $ の中から一様ランダムに選びます。 操作を行う回数の期待値は $ \displaystyle\ \frac{35}{6} $ になります。

## 样例 #1

### 输入

```
4
1 1 3```

### 输出

```
831870300```

## 样例 #2

### 输入

```
15
1 2 1 1 4 5 3 3 5 10 3 6 3 13```

### 输出

```
515759610```

# 题解

## 作者：hgzxwzf (赞：39)

### [arc150D](https://atcoder.jp/contests/arc150/tasks/arc150_d)

设 $E(X_i)$ 为 $i$ 点期望被选中的次数，那么 $ans=\sum_{i=1}^nE(X_i)$。

设 $i$ 点的深度为 $d_i$。

如果一次操作选中了除 $1$ 到 $i$ 路径以外的的点，那么对 $i$ 没有影响，所以只需要考虑选 $1$ 到 $i$ 路径上的点的情况。

允许选中好点，但不算选中好点的贡献，这和原问题是等价的。

所以问题可以转化为，$d_i$ 个点，每次等概率抽取一个点，抽到第 $d_i$ 个点时贡献加 $1$，一直抽直到所有点都被抽到过。

假设已经被抽到过的点有 $k$ 个，那么再抽一次抽到未被抽到的点的概率为 $\frac{d_i-k}{d_i}$，期望 $\frac{d_i}{d_i-k}$ 抽到下一个未被抽到的点（做某件事情成功的概率为 $p$，期望做 $\frac{1}{p}$ 次成功）。

所以把所有点都抽到的期望次数为 $\sum_{k=0}^{d_i-1}\frac{d_i}{d_i-k}=d_i\sum_{k=1}^{d_i}\frac{1}{k}$，每次抽到第 $d_i$ 个点的概率都是 $\frac{1}{d_i}$，所以第 $d_i$ 个点期望被抽到 $\sum_{k=1}^{d_i}\frac{1}{k}$。

所以 $ans=\sum_{i=1}^n\sum_{j=1}^{d_i}\frac{1}{j}$。

---

## 作者：william555 (赞：15)

### 题意
给定一个 $n$ 个点的树，$1$ 是根。每个点初始都是白色的，如果一个点 $x$ 到根的链上存在白色点，则称这个点是 "bad" 的。每一次操作会在所有 "bad" 的点中随意选择一个点，将其染成黑色，问期望多少次会把整棵树染成黑色？

### 题解
考虑每一个点被操作了几次。对于每一个点 $x$，假设其深度为 $d$（$1$ 的深度为 $1$）有两种情况。  
1. 在 $x$ 染黑前，其所有祖先都被染过色。  
2. 存在一个祖先，在 $x$ 被染黑之后才被染黑。 

第一种情况，$x$ 一定被只操作了一次，将其染黑，而这种情况出现的概率为 $\frac1d$（$x$ 是它到根的路径上 $d$ 个点中最后一个被染黑的）。

第二种情况，先考虑 $x$ 在其第一个被染黑的祖先被染黑之前期望的被操作次数，$x$ 被操作，当且仅当 $x$ 是这 $d$ 个点中第一个染黑的，所以出现一次的概率是 $\frac 1 d$，出现两次的概率是 $\frac 1 {d^2} $……于是总的期望是:
$$ \sum _{i=1}^ \infty \frac 1 {d^i}= \frac 1 {d-1}$$
同理，$x$ 在其第二个被染黑的祖先染黑之前被操作的期望此数就为 $ \frac 1 {d-2} $。以此类推，所以总的期望就是 : 
$$ \sum _{i=1}^{d-1} \frac 1 i$$ 


将这两种情况汇总，$x$ 被操作的期望次数就是:
$$ \sum _{i=1}^d \frac 1 i$$

于是算出每个点的深度，然后对每个点操作的期望求和，就能得出答案。

```c++
#include<bits/stdc++.h>
using namespace std;
inline int in(){
	int x;
	scanf("%d",&x);
	return x;
}
const int N=2e5+5,mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int mul(int a,int b){return (long long)a*b%mod;}
inline int qpow(int a,int b){
	int c=1;
	for(;b;b>>=1,a=mul(a,a))if(b&1)c=mul(c,a);
	return c;
}
int n,p[N],dep[N],sum[N];
int main(){
	n=in();
	dep[1]=1;
	for(int i=2;i<=n;i++)dep[i]=dep[in()]+1;
	for(int i=1;i<=n;i++)sum[i]=add(sum[i-1],qpow(i,mod-2));
	int ans=0;
	for(int i=1;i<=n;i++)ans=add(ans,sum[dep[i]]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：bai_tang (赞：10)

只要有信念，就一定能成功！

在考试结束前 5 分钟发现的性质，虽然可惜，但不正说明我的思维能力和代码能力有待提升吗？

### [题意](https://atcoder.jp/contests/arc150/tasks/arc150_d)
给定一棵 $n$ 个节点的有根树，一开始所有的点都是白的，每次会等概率选择一个除了“包含根的最大连通黑点”以外的点（可以是黑点）涂黑，求到达无法操作地步的期望步数，$n\le 10^5$。

### 赛时思路
对于链上的情况写一份暴力，[代码](https://www.luogu.com.cn/paste/pruxyy3f)。

容易发现前几个数分别是 $1,5/2,13/3,77/12,87/10,223/20$。

对数字稍微有点敏感的话就可以发现链上的答案就是调和数的前缀和：
$$\sum_{i=1}^n\sum_{j=1}^i\frac1j=(n+1)(H_{n+1}-1)$$

然后如果你再敏感一点容易发现：
$$5/2+13/3-1=35/6$$
 而这恰好是样例 $1$ 的答案！所以我们就有了一个线性的乱搞，但是它能够通过此题，[代码](https://www.luogu.com.cn/paste/ub3btd3q)。
 
### 分析
由于期望具有线性性，我们考虑每个节点 $u$ 期望被选了多少次，这样就可以完全忽略不在链上的贡献。

那么现在问题变成了链上的情况，最后一个点期望被选了多少次。

然后我们发现这个时候我们可以看作在涂满之前随便选择，而不必考虑链上的最长涂黑前缀是多少（因为在涂满之前，最后一个点总是坏的）。
- 选择一个非链上的最长涂黑前缀部分涂黑。
- 考虑你手动执行这个操作 。
- 但是操作不够精确，导致你每次有可能涂黑一个链上的最长涂黑前缀。
- 于是你必须每次手动撤回它，当然这不会影响期望次数。
- 然后你发现，你涂黑一个链上的最长涂黑前缀，撤回不撤回没什么两样，也不会对期望次数产生影响，于是你干脆不撤回，但是也不会影响期望次数。

那么在涂满之前随便选择的期望涂满步数是多少呢？这是[经典问题](https://www.luogu.com.cn/problem/SP1026)，答案是：
$$n\sum_{i=1}^n1/i=nH_n$$

但是在这个模型，每个点是等效的，所以我们最终得到了这个点被涂黑的期望次数：$H_n$。

---

## 作者：Mini_PEKKA (赞：9)

> 给定一颗 $n$ 个点的树，根节点为 $1$。每个点都有黑或白两种颜色。最初所有点都是白色。称一个点是坏的当且仅当它到根的路径上存在白点。每次操作从当前的坏点集合中均匀随机选择一个点染黑（每个点可以被多次染黑）直到所有点都被染黑。求期望进行多少次操作。保证 $1\le n\le 2\times10^5$。

根据 **期望的线性性**，把所有点染黑的期望操作次数等于每个点被染黑的期望次数之和。

1. 扩集：把 **在坏点集合中选** 转化为 **在全集中选**，如果选到坏点就将其染黑并将其被染黑次数加一，否则继续在全集中选，这与原问题等价。

2. 缩集：对于染黑过程中任意一个时刻和任意一个点 $u$，$u$ 在接下来的过程中被染黑的期望次数只与这个时刻 $u$ 到根的路径上所有点的颜色状态有关。所以此时选到一个不在 $u$ 到根路径上的点对 $u$ 在接下来的过程中被染黑的期望次数没有影响。于是可以把 **在全集中选** 转化为 **在 $\boldsymbol{u}$ 到根的路径上选**。

对于任意一个点 $u$，因为 $u$ 在 **$\boldsymbol{u}$ 到根的路径上所有点都被染黑** 前一直都是坏点，所以每次选到 $u$ 都会使得 $u$ 被染黑的次数加一。因此计算 $u$ 被染黑的期望次数时，原问题可以转化为如下问题：
> 有 $d_u$ 个点，最初所有点都是白色。每次操作从 $d_u$ 个点中均匀随机选择一个点染黑直到所有点都被染黑，求第 $d_u$ 个点被染黑的期望次数。

其中 $d_u$ 表示 $u$ 到根的路径上的点数。

**接下来请只考虑转化后的问题，不要与原问题联系。**

可以发现这个问题中每个点是等价的。于是只需要求出每个点被染黑的期望次数之和，即把所有点染黑的期望操作次数，再除以 $d_u$ 即可得到第 $d_u$ 个点被染黑的期望次数。

根据 **期望的线性性**，把所有点染黑的期望操作次数等于 $\sum\limits_{i=0}^{d_u-1}{f_i}$。其中 $f_i$ 表示当前有 $i$ 个黑点，期望操作多少次后黑点个数变为 $i+1$。因为有 $i$ 个黑点时，选到一个白点的概率为 $\frac{d_u-i}{d_u}$，所以 $f_i=\frac{d_u}{d_u-i}$。
于是把所有点染黑的期望操作次数为 $\sum\limits_{i=1}^{d_u}{\frac{d_u}{i}}$，第 $d_u$ 个点被染黑的期望次数为 $\sum\limits_{i=1}^{d_u}{\frac{1}{i}}$。

所以原问题答案为 $\sum\limits_{i=1}^{n}{\sum\limits_{j=1}^{d_i}{\frac{1}{j}}}$。

---

## 作者：DengDuck (赞：5)

我觉得这题就是一道期望 Trick 题，我自己不会纯属技不如人。

大家都好会期望转换技巧啊，我来以原教旨主义简单代数技巧证明一下犇犇口中“显然”的东西。

首先这是一个复杂的问题，每个点是否选中的概率取决于当前有多少好点，好点的定义是复杂的，你难以在期望 DP 的过程中将其表示和维护出来，所以考虑转换。

不难发现，你可以把原问题转换为，选择所有的点都是等概率的，只是选择坏点才算贡献，这样至少从数值上看是十分美丽的。

证明这个转换的正确性，我们假设好点数量为 $x$，设原局面为 $S$，选择好点显然局面不变，否则进入一种新局面（可能还是 $S$，但是你得算贡献），得：
$$
f(S)=\frac x nf(S)+  \frac {1}n (\text{All of situations})+\frac{n-x}n
$$
稍微变变形：
$$
f(S)=\frac x nf(S)+  \frac {n-x}n (\frac 1 {n-x}(\text{All of situations})+1)
$$


转换前是：
$$
f(S)=\frac 1 {n-x}(\text{All of situations})+1
$$
代入一下，发现这个转换本质是 $f(S)=f(S)$，所以显然是没有问题的。

接下来我们感觉对于整棵树计算贡献也是一个非常复杂的事情，所以考虑把贡献下放到点上，$ans=\sum\limits_{i=1}^n E(i)$，其中 $E(i)$ 表示在整个染色过程中，$i$ 这个点自己期望被选中的次数。

咋求呢，我们可以证明 $E(i)$ 只和 $dep_i$ 有关，因为染色只和 $1\to i$ 的这些点有关，证明方法和上面没有本质区别，一个是放大一个是缩小。

我们设 $f_{i,0/1}$ 表示目标点是第 $i$ 层的，当前是否被染色，边界是 $f_{1,1}=f_{0,0}=1$。

考虑转移，我们发现除了我们这个点得：
$$
\begin{aligned}
f_{i,0}&=\frac {dep_i-1}{dep_i}f_{i-1,0}+\frac 1{dep_i}(f_{i,1}+1)\\
f_{i,1}&=\frac {dep_i-1}{dep_i}f_{i-1,1}+\frac 1{dep_i}(f_{i,1}+1)
\end{aligned}
$$
变形一下：
$$
\begin{aligned}
f_{i,0}&=\frac {dep_i-1}{dep_i}f_{i-1,0}+\frac 1{dep_i}f_{i,1}+\frac 1{dep_i}\\
f_{i,1}&=f_{i-1,1}+\frac 1{dep_i-1}
\end{aligned}
$$
显然，$f_{i,1}=h_{i-1}$，其中 $h$ 表示调和级数，也就是 $h_i=\sum\limits_{j=1}^i\dfrac 1 j$，然后数学归纳法得到 $f_{i,0}=h_i$。

综上所述，$E(i)=f_{i,0}=h_i$，预处理调和级数加到答案里就行。

时间复杂度显然是 $\mathcal O(n)$。

唉，不会期望技巧导致的。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=2e5+5;
//const LL M;
const LL mod=998244353;
//const LF eps;
//const LL P;
LL n,dep[N],inv[N],h[N],ans=1;
int main()
{
	scanf("%lld",&n);
	dep[1]=h[1]=inv[1]=1;
	for(int i=2;i<=n;i++)
	{
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;
		h[i]=(h[i-1]+inv[i])%mod;
	}
	for(int i=2;i<=n;i++)
	{
		LL x;
		scanf("%lld",&x);
		dep[i]=dep[x]+1;
		ans=(ans+h[dep[i]])%mod;
	}
	printf("%lld",ans);
	return 0;
}
//RP++
```



---

## 作者：白简 (赞：3)

## [ARC150D] Removing Gacha

### 题目大意

给定一棵以 $1$ 为根的树，初始每个点都是白色的。

某个点到根结点路径上所有点中存在白色的点时，这个点可以被选中。当某个点被选中且这个点仍是白色时，它将被染黑。

求所有结点被染黑的期望次数，答案对 $998244353$ 取模。

（$2 \leq n \leq 2 \times 10^5$

### 思路

由于期望的线性性，可以考虑分开求每个结点被染黑的期望次数，然后求和得到答案。

考虑计算想要将结点 $u$ 染黑在 $1 \sim u$ 路径上选择的期望次数，这个问题与 [Favorite Dice](https://www.luogu.com.cn/problem/SP1026) 相同。

> 给定一个 $n$ 面的骰子，求期望掷几次能使得每一面都被掷到。

记 $f_i$ 表示已经掷到了 $i$ 个面，期望掷到所有面的期望次数。

对于下一次掷骰子，有 $\dfrac{n-i}{n}$ 的概率掷到新的面，那么掷到新的面的期望次数为 $\dfrac{n}{n-i}$。

那么答案为 

$$\sum^{n-1}_{i=0}\dfrac{n}{n-i}=n\sum^n_{i=1}\dfrac{1}{i}$$

同理，有

$$\frac{1}{\operatorname{dep_u}} \times \operatorname{dep_u} \times \sum^{\operatorname{dep_u}}_{i=1}\dfrac{1}{i}= \sum^{\operatorname{dep_u}}_{i=1}\dfrac{1}{i}$$

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 200500;
const int Mod = 998244353;

int n;

template <typename Type>
Type Pow(Type x, Type y) {
    Type res = 1;

    x %= Mod;
    y %= (Mod - 1);

    while(y > 0) {
        if(y & 1)
            res = res * x % Mod;
    
        x = x * x % Mod;
        y >>= 1;
    }

    return res;
}

template <typename Type>
Type Inv(Type x) {
    return Pow(x,Mod - 2);
}

struct Edge{
    int next,to;
}e[N << 1];

int cnt,h[N];

void Add(int u,int v) {
    cnt ++;
    e[cnt].next = h[u];
    h[u] = cnt;
    e[cnt].to = v;
}

int dep[N];

void dfs(int x,int fa) {
    dep[x] = dep[fa] + 1;

    for (int i = h[x];i; i = e[i].next) {
        int to = e[i].to;

        if(to == fa)
            continue;
        
        dfs(to,x);
    }
}

int H[N],sum[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;
    for (int i = 2,x;i <= n; i++) {
        cin >> x;

        Add(i,x);
        Add(x,i);
    }

    dfs(1,0);

    for (int i = 1;i <= n; i++) {
        H[i] = (H[i - 1] + Inv(i)) % Mod;
        sum[i] = sum[i - 1] + H[i];
    }

    int ans = 0;
    for (int i = 1;i <= n; i++) 
        ans = (ans + H[dep[i]]) % Mod;

    cout << ans << endl;
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：2)

想了至少半个小时还是没有什么结果。纪念一下。

考虑如果一个点是坏点才计入贡献。这样子每次随机选一个点即可。

对于一个点 $i$ 计算其被选中的期望次数。求和即为答案。

考虑 $1\to i$ 具有 $d$ 个点的情况。其相当于每个点独立，则如果选到了其他 $n-d$ 个点则不会对这个点的答案造成影响。

我们可以看成在这 $d$ 个点里等概率随机选择。而对于选到了非 $i$ 的点而 $1\to i$ 没有选完的情况，前面的点在选择过程中是否是好点也不对 $i$ 的答案造成影响。

接下来考虑 $d$ 个点选完所有点的期望次数。一开始有 $1$ 的概率选到一个新点，接下来每次有 $\dfrac{d-1}d$ 的概率选到新点。以此类推，第 $i$ 个阶段选到下一个新点的期望次数是 $\dfrac{d}{d-i+1}$。则答案为 $dH_d$，其中 $\displaystyle H_d=\sum_{i=1}^d \dfrac{1}{i}$ 调和级数。

$1\to i$ 的 $d$ 个点选完所有点的期望次数是 $dH_d$，选到 $i$ 的期望次数是 $H_d$。则本题答案为 $\displaystyle \sum_{i=1}^n H_{d_i}$。

---

## 作者：happybob (赞：1)

根据期望线性性，只需要对于每个 $i$ 求 $E(x_i)$，$x_i$ 表示操作过程中点 $i$ 被选到的次数。

对于每个点 $i$，保留从根到 $i$ 的点的这条链计算答案就是对的，原因是考虑当且仅当点 $i$ 到根都被选后这个点不再有贡献，所以可以假设每次选的点都是在这条链上的，其他情况不影响答案。

考虑这条链的答案，则初始时没有好的点，假设点 $i$ 深度为 $d$，容易推出式子是关于 $d$ 的一个调和级数的形式，直接计算并对所有点求和即可。

---

## 作者：mskqwq (赞：1)

类似 [CF280C](https://codeforces.com/problemset/problem/280/C) 利用期望的线性性，我们只需考虑每个点被操作的次数的期望，然后这个同样只和它的深度有关。

现在我们只需要考虑一条链的情况，并且只要求出最后面那个点的操作次数。发现题目要求的 “它或它的任意一个祖先未被选中” 非常难刻画，因为一次操作后可能导致很多点到根的链上的点都被选中。

不过我们只需要求最后的点的操作次数，这个事情很重要。接下来需要注意到一件事情：如果一个到根的链上的点都被选中的点，还能被重复选中的话，并不会影响到最后那个点的操作次数的期望。

然后就能做了，问题变成给定一条链，每次任意染黑一个点，问最后那个点被操作的次数期望。发现每个点的期望相等，于是变成求期望几次全部染黑。设链长为 $n$，已经染黑了 $k$ 个点，那么期望 $\frac n {n-k}$ 次之后才能再染一个点，所以答案为 $\sum_{i=1}^n \frac n i$，那么一个点的答案就是 $\sum_{i=1}^n \frac 1 i$。

---

## 作者：出言不逊王子 (赞：1)

为什么自己不会经典套路啊。

我们写出 $n!$ 个操作序列，对于每个操作序列上的点，如果能操作就操作，不能操作就放在一边直接开摆。

由期望的线性性，我们把贡献拆到点上，则 $ans=\sum E(i)$。

考虑对于每个深度为 $d_u$ 的点，我们只关心它到根节点的 $d_u$ 个点。

对于这 $d_u$ 个点，因为**只要这整条链没被抽完，最下面那个点就可能被抽到**，所以我们要算抽完整条链的期望。

假设当前抽了 $i$ 个点，每次抽到一个新点的概率是 $\dfrac{d_u-i}{d_u}$，期望是 $\dfrac{d_u}{d_u-i}$，相加得 $\sum_{i=0}^{d_u-1} \dfrac{d_u}{d_u-i}=\sum_{i=1}^{d_u} \dfrac{d_u}{i}$。

每次抽到最下面那个点的概率是 $\frac 1{d_u}$，所以每个点最终的期望是 $\sum_{i=1}^{d_u} \dfrac{1}{i}$。

那这里不会算入其他点的贡献吗？其他点的贡献不加上去不就好了？

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=300001,inf=998244353;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int ksm(int x,int y){
	int r=1;while(y){
		if(y&1) r=r*x%inf;
		x=x*x%inf;y>>=1;
	}return r;
}vector<int> e[N];
int dep[N],n,fa[N],inv[N],res;
void dfs(int now){
	dep[now]=dep[fa[now]]+1;
	for(auto v:e[now]) if(v!=fa[now]) dfs(v);
}
signed main(){
	n=read();fs(i,2,n,1){
		fa[i]=read();
		e[fa[i]].push_back(i);
	}dfs(1);
	fs(i,1,n,1) inv[i]=(ksm(i,inf-2)+inv[i-1])%inf;
	fs(i,1,n,1) (res+=inv[dep[i]])%=inf;
	cout<<res;
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：1)

## 题意

给定一棵由 $N$ 个节点组成的树，每个节点有黑白两种颜色。定义一个节点 $u$ 为好的当且仅当路径 $1 \leftrightarrow u$ 上的节点均为黑色的，反之为坏的。初始情况下所有点均为白色。

定义一次操作为选取一个坏的节点并将其染黑，求将全部节点均染为黑色的期望操作次数，对 $998244353$ 取模。

（$2 \le N \le 2 \times 10^5$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ARC150D.html)

发现所有节点均为黑色是所有节点均是好的的充要条件。所以我们可以将问题转化为求将所有节点变为好的的期望次数。

设 $E(X_i)$ 代表直至第 $i$ 期望变为好的，第 $i$ 个点期望被选中的次数，那么我们要求的所有节点的该值的和。

下面考虑如何计算该值，我们可以考虑先计算将第 $i$ 个点变为好的的期望选择路径 $1 \leftrightarrow u$ 上的节点的次数。可以发现该问题与如下问题等价：

> 有 $n$ 种无限个的物品，每次随机等概率选择一种物品，求使得所有物品均被选择的期望次数。

可以考虑设当前选择了 $k$ 种物品，那么下一次选择到新物品的概率为 $\dfrac{n - k}{n}$，那么选择到新物品的期望次数即为 $\dfrac{n}{n - k}$，那么总的期望次数即为

$$\sum\limits_{k = 0}^{n - 1}\dfrac{n}{n - k} = n\sum\limits_{i = 1}^{n}\dfrac{1}{i}$$

发现在这个问题中不同种类的物品等价，那么我们可以得出 

$$E(X_i) = \dfrac{\operatorname{depth}_u\sum\limits_{i = 1}^{\operatorname{depth}_u}\dfrac{1}{i}}{\operatorname{depth}_u} = \sum\limits_{i = 1}^{\operatorname{depth}_u}\dfrac{1}{i}$$

$\mathcal{O}(N)$ 求出即可。值得一提，由于本题规定每个节点的父亲节点编号小于该节点编号，所以无需显式建树。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;

typedef std::vector<valueType> ValueVector;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

class Inverse {
private:
    valueType N;
    ValueVector data;

public:
    explicit Inverse(valueType n = 0) : N(n), data(n + 1) {
        data[1] = 1;

        for (valueType i = 2; i <= N; ++i)
            data[i] = mul(MOD - MOD / i, data[MOD % i]);
    }

    valueType operator()(valueType n) const {
        return data[n];
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    Inverse const Inv(N);

    ValueVector depth(N + 1);

    depth[1] = 1;

    ValueVector H(N + 1, 0);

    for (valueType i = 1; i <= N; ++i)
        H[i] = sum(H[i - 1], Inv(i));

    valueType ans = H[1];

    for (valueType i = 2; i <= N; ++i) {
        valueType father;

        std::cin >> father;

        depth[i] = depth[father] + 1;

        Inc(ans, H[depth[i]]);
    }

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：demonlover923 (赞：1)

首先原问题的期望，与好点也可以选，但选到好点不算次数，这两个问题的期望相同，然后拆开对于每个点分别考虑。

设 $\mathbb{E}(x)$ 为点 $x$ 被选的期望次数，$p_k$ 为点 $x$ 在第 $k$ 次操作被选到并且这次选到时点 $x$ 还是坏点的概率，那么 $\mathbb{E}(x)=\sum\limits_{k\geqslant 1}{p_k}$，设 $x$ 的深度为 $d$，考虑容斥计算 $p_k$。

$$
p_k=\frac{1}{n}\sum_{i\geqslant 1}{\binom{d}{i}(-1)^i\left(\frac{n-i}{n}\right)^{k-1}}
$$
$$
\mathbb{E}(x) = \sum_{k\geqslant 1}{p_k}=\sum_{i\geqslant 1}{\binom{d}{i}(-1)^i\frac{1}{i}}=H_d
$$

其中 $H_d$ 为调和级数，证明可以做差或者积分。

时间复杂度 $\mathcal{O}(n)$。

```cpp
/************************************************
*Author        :  demonlover
*Created Time  :  2022.10.12.15:47
*Problem       :  ARC150D
************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair <int,int> pii;
template <typename T>
inline bool read(T &x) {
	int f = 1,c = getchar();x = 0;
	while (!isdigit(c)) {if (c == 45)f = -1;c = getchar();}
	while (isdigit(c))x = (x<<3)+(x<<1)+(c^48),c = getchar();
	return x *= f,true;
}
template <typename T,typename... Args>
inline bool read(T &x,Args &...args) {
	return read(x) && read(args...);
}

namespace run {
	const int maxn = 2e5+10;
	const int mod = 998244353;
	inline int power(int a,int b) {
		int res = 1;
		while (b) {
			if (b&1)res = 1ll*res*a%mod;
			a = 1ll*a*a%mod;
			b >>= 1;
		}
		return res;
	}
	int dep[maxn];
	vector <int> g[maxn];
	inline void dfs(int x,int fa) {
		dep[x] = dep[fa]+1;
		for (auto y : g[x])dfs(y,x);
		return;
	}
	int inv[maxn],h[maxn];
	int n,ans;
	inline bool main() {
		read(n);
		for (int i = (inv[0] = inv[1] = 1)+1;i <= n;++i)inv[i] = 1ll*(mod-mod/i)*inv[mod%i]%mod;
		for (int i = 1;i <= n;++i)h[i] = (h[i-1]+inv[i])%mod;
		for (int i = 2,x;i <= n;++i)read(x),g[x].push_back(i);
		dfs(1,0);
		for (int i = 1;i <= n;++i)ans = (ans+h[dep[i]])%mod;
		printf("%d\n",ans);
		return 0;
	}
}

int main() {
#ifdef demonlover
	freopen("ARC150D.in","r",stdin);
	freopen("ARC150D.out","w",stdout);
#endif
	return run :: main();
}

```

---

## 作者：win114514 (赞：0)

技巧题，如果不会一些技巧确实可能做不出来。

### 思路

由于每一次待选的点的条件非常苛刻。

所以我们不妨把待选的点看作所有的点，但是只有在选到真正可能被选的点的时候才计算贡献。

我们可以考虑每一个点的期望被选择次数。

答案为所有点的期望被选择次数之和。

对于一个点 $i$，它的深度为 $d_i$。

那么我们只需考虑它和它的所有祖先的选择情况，因为选择到其它点的时候对它没有影响。

在它还有 $k$ 个祖先的时候，我们期望 $\frac{d_i}{k}$ 次会再次选择到一个没有被选择过的祖先。

而每一次都有 $\frac{1}{d_i}$ 的概率选择到点 $i$。

所以总的期望次数为：

$$
\sum_{k=1}^{d_i} \frac{1}{d_i}\frac{d_i}{k}=\sum_{k=1}^{d_i}\frac{1}{k}
$$

时间复杂度：$O(n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 998244353;

int n;
int a[200010];
int d[200010];
int v[200010];

inline int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod, y >>= 1;
  }
  return res;
}

signed main() {
  cin >> n, d[1] = 1;
  for (int i = 2; i <= n; i++) cin >> a[i];
  for (int i = 2; i <= n; i++) d[i] = d[a[i]] + 1;
  for (int i = 1; i <= n; i++) v[i] = power(i, mod - 2);
  for (int i = 1; i <= n; i++) if ((v[i] += v[i - 1]) >= mod) v[i] -= mod;
  int ans = 0;
  for (int i = 1; i <= n; i++) if ((ans += v[d[i]]) >= mod) ans -= mod;
  cout << ans << "\n";
  return 0;
}
```

---

## 作者：Fesdrer (赞：0)

考虑把原问题看作是：每次随机选择一个点，如果这个点到祖先的链上存在点没有选择则产生 $1$ 的贡献，求总的贡献期望。

设一个深度为 $d$ 的点（根节点深度为 $1$）在第 $v$ 步被选择并产生贡献的概率是 $g(d,v)$，只需要计算出前 $v-1$ 步祖先链上存在点没有被选择的概率即可。考虑容斥，得到
$$
\begin{aligned}
g(d,v)&=\dfrac 1n\left[1-\dfrac{\left(\sum\limits_{i=0}^d(-1)^i(n-i)^{v-1}\dbinom di\right)}{n^{v-1}}\right]\\
&=-\dfrac 1n\sum_{i=1}^d\binom di(-1)^i\left(\dfrac {n-i}n\right)^{v-1}
\end{aligned}
$$

设 $f(d)$ 为深度为 $d$ 的点（根节点深度为 $1$）期望产生的贡献，只要把所有的 $g(d,v)$ 加起来即可，即

$$
\begin{aligned}
f(d)&=\sum_{v=1}^{+\infty}g(d,v)\\
&=\sum_{v=1}^{+\infty}-\dfrac 1n\sum_{i=1}^d\binom di(-1)^i\left(\dfrac {n-i}n\right)^{v-1}\\
&=-\dfrac 1n\sum_{i=1}^d\binom di(-1)^i\sum_{v=1}^{+\infty}\left(\dfrac {n-i}n\right)^{v-1}\\
&=-\dfrac 1n\sum_{i=1}^d\binom di(-1)^i\dfrac 1{1-\dfrac{n-i}n}\\
&=-\dfrac 1n\sum_{i=1}^d\binom di(-1)^i\dfrac ni\\
&=-\sum_{i=1}^d\binom di(-1)^i\dfrac 1i\\
\end{aligned}
$$

尝试计算 $f(d)-f(d-1)$ 来继续化简这一式子，可得
$$
\begin{aligned}
f(d)-f(d-1)&=-\sum_{i=1}^{d-1}(-1)^i\left(\binom di-\binom{d-1}i\right)\dfrac 1i-(-1)^d\dfrac 1d\\
&=-\sum_{i=1}^{d-1}(-1)^i\binom {d-1}{i-1}\dfrac 1i-(-1)^d\dfrac 1d\\
&=-\sum_{i=1}^{d-1}(-1)^i\dfrac 1d\binom di-(-1)^d\dfrac 1d\\
&=-\sum_{i=1}^{d}(-1)^i\dfrac 1d\binom di\\
&=-\dfrac 1d\sum_{i=1}^{d}(-1)^i\binom di\\
&=\dfrac 1d
\end{aligned}
$$

因此我们得到
$$
f(d)=\sum_{i=1}^d\dfrac 1i
$$

只要把所有点的 $f(d)$ 加起来即可。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,P=998244353;
int n,fa[N],dep[N],ans,inv[N],sum[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	dep[1]=1;
	for(int i=2;i<=n;i++)	cin>>fa[i],dep[i]=dep[fa[i]]+1;
	inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++)	inv[i]=1ll*(P-P/i)*inv[P%i]%P;
	for(int i=1;i<=n;i++)	sum[i]=(sum[i-1]+inv[i])%P;
	for(int i=1;i<=n;i++)	ans=(ans+sum[dep[i]])%P;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：0x3F (赞：0)

典题。

我们认为每次选的点没有限制，但是选到好点不计算贡献，容易发现和原问题是等价的。

根据期望的线性性，我们分别计算每个点产生贡献的期望次数。

设点 $x$ 的深度为 $d$，每次操作等概率从这 $d$ 个点中选择一个染成黑色，若选了点 $x$ 则产生一次贡献，直到这 $d$ 个点都染成黑色为止。

由于在此过程中，每个点被选择的期望次数是一样的，只需算出总的期望执行次数并除以 $d$。

我们发现染黑第 $i$ 个点时，有 $d-i+1$ 种选择，期望需要 $\frac{d}{d-i+1}$ 次操作，总和为 $\sum_{i=1}^{d}\frac{d}{d-i+1}=dH_{d}$。

除以 $d$ 便得到点 $x$ 产生的贡献为 $H_{d}$，其中 $H$ 表示调和数。

综上所述，答案为 $\sum_{i=1}^{n}H_{d_{i}}$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int _ = 2e5 + 10;
int n, r[_], d[_], h[_], ans;
int main() {
    cin >> n;
    r[1] = h[1] = d[1] = ans = 1;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        d[i] = d[p] + 1;
        r[i] = mod - (long long) (mod / i) * r[mod % i] % mod;
        h[i] = (h[i-1] + r[i]) % mod;
        ans = (ans + h[d[i]]) % mod;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：jijidawang (赞：0)

来点大力做法。


首先，根据期望线性性可以得到答案就是 $\displaystyle\sum_i\mathbb E[x_i]$，其中 $\mathbb E[x_i]$ 为第 $i$ 个点被染黑的期望次数。

然后问题就变成如何求 $\mathbb E[x_i]$ 了，考虑一个随机过程的期望其实就是任何一个合法的过程前缀 $S_i$ 下，元素被选中的概率之和。

于是令
$$\mathbb E[x_i]=\sum_{k=0}^m\mathbb P(S_k(k)=u)$$
注意到如果如果 $u$ 能被染，则要么 $u$ 的父亲能被染，要么 $u$ 的父亲不能被染但是在前缀中还没有出现过。

令 $u$ 父亲的深度为 $d$，于是答案是 $\dfrac 1n(P_1+P_2)$，其中
$$\begin{aligned}P_1&=\sum_{k=1}^d(-1)^{k-1}\binom{d}{k}\frac{n}{k}\\P_2&=\sum_{k=0}^d(-1)^k\binom{d}{k}\frac{n}{k+1}\end{aligned}$$
注意到 $\dfrac{1}{k+1}=\left.(\mathsf E^kx^{\underline{-1}})\right|_{x=0}$，来个 $d$ 阶差分把组合数干掉即可得到
$$\begin{aligned}P_2&=(-1)^dn\left.\left(\Delta^dx^{\underline {-1}}\right)\right|_{x=0}\\&=\frac{nd!}{(d+1)!}\\&=\frac{n}{d+1}\end{aligned}$$

$P_1$ 相对就有点麻烦，因为不能补上 $k=0$ 项，考虑用恒等式 $\displaystyle \binom{d}{k}=\sum_{r=k-1}^{d-1}\binom{r}{k-1}$ 降下指标以规约到 $P_2$，则
$$\begin{aligned}P_1&=\sum_{k=1}^d(-1)^{k-1}\sum_{r=k-1}^{d-1}\binom{r}{k-1}\frac{n}{k}\\&=\sum_{k=0}^{d-1}\sum_{r=k}^{d-1}(-1)^k\dbinom rk\dfrac n{k+1}\\&=\sum_{r=0}^{d-1}\sum_{k=0}^r(-1)^k\dbinom rk\dfrac n{k+1}\\&=\sum_{r=0}^{d-1}\dfrac n{r+1}\\&=nH_d\end{aligned}$$
其中 $H$ 是调和级数。倒数第二个等号是用的 $P_2$ 的表达式。

最后深度为 $d$ 的点的答案就是 $\dfrac 1n(P_1+P_2)=H_d$，那么直接暴力算就好了。

---

