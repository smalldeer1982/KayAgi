# Mister B and Astronomers

## 题目描述

外星球每隔 $T$ 秒中只有一秒可以被观测到，其它 $T-1$ 秒无法被观测。  

$n$ 个天文学家（分别编号为 $1,\ldots,n$）轮流观测天空 $1$ 秒，且第 $i+1$ 个科学家在第 $i$ 个天文学家后 $a_i+1$ 秒后才执行观测，而第一个天文学家则在第 $n$ 个天文学家后 $a_1$ 秒后才执行观测，且第一个天文学家在 $0$ 秒时执行第一次观测（即第一个天文学家观测的时间是 $[0,1)$ ，第二个科学家在 $[a_2,a_2+1)$ 时观测，而最后一个天文学家在 $[\sum^{n-1}_{i=2}a_i,1 + \sum^{n-1}_{i=2}a_i)$ 时观测，之后再过 $a_1$ 秒后第一个天文学家继续观测）。  

由于外星球具体在首次观测之后的 $T$ 秒中的哪一秒出现是不确定的，若外星球在 $[i,i+1)$ 时出现（$0\le i<T-1$），且天文学家 $j$ 是首个观测到星球的人，则称 $j$ 抢占了 $[i,i+1)$ 时间片段。也就是说,如果把所有的观测时间模 $T$ 之后,最先观测到时间片段 $[i,i+1)$ 将占有这个时间片段。 问每个天文学家所占有的时间片段各是多少。

## 说明/提示

$1\leq T\le10^9$，$2\leq n\le2\times10^5$，$1\leq a_i\le10^9$。

#### 样例 1 解释

$T=4$，$n=2$，$a_1=2$，$a_2=3$。   

第一个天文学家观测的时间点是 $t=0,5,10,\ldots$，第二个天文学家是 $t=3,8,13,\ldots$。  

第一个天文学家在 $t=0$ 时占有 $[0,1)$，在 $t=5$ 时占有 $[1,2)$, 在 $t=10$ 时占有 $[2,3)$，第二个天文学家在 $t=3$ 时占有 $[3,4)$。

## 样例 #1

### 输入

```
4 2
2 3
```

### 输出

```
3 1 
```

## 样例 #2

### 输入

```
5 4
1 1 1 1
```

### 输出

```
2 1 1 1 
```

# 题解

## 作者：Tsawke (赞：4)

# [CF819D Mister B and Astronomers](https://www.luogu.com.cn/problem/CF819D) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=CF819D-Solution)

### 题面

存在一个星星每 $ T $ 秒闪烁一次，存在 $ n $ 个科学家围成一圈循环观测星星，第一个在 $ 0 $ 秒观测，第二个在 $ a_2 $ 秒观测，第三个在 $ a_2 + a_3 $ 秒观测，$ \cdots $ 第一个科学家在 $ a_1 + a_2 + a_3 + \cdots + a_n $ 观测，$ \cdots $。对于 $ t \in [0, T) $，若星星第一次闪烁在 $ t $ 秒，那么第一次观测到这个星星的科学家将会获得 $ 1 $ 的贡献，求每个科学家的贡献。

### Solution

首先不难想到，令 $ S = \sum a_i $，第 $ i $ 个科学家观测时间为 $ \sum_{j = 2}^i a_j + kS, k \in \mathbb{N} $，令 $ t_i = \sum_{j = 2}^i a_j $，同时对于 $ T $，假设本次初始时间为 $ \xi $，那么可以认为需要找到第一个满足 $ t_i + kS \equiv \xi \pmod{T} $。

对于后者式子不难发现其为经典的**群论**套路，即我们发现对于某个科学家的初始点 $ t_i $，可以认为每次模意义下步进 $ S $，此时会构成 $ \gcd(S, T) $ 个环，环长均为 $ \dfrac{T}{\gcd(S, T)} $，或者说每连续 $ \gcd(S, T) $ 个数均属于不同的环。关于这个性质似乎特别显然，不过这里我们也简单证明一下：

显然我们要证明的即为如下式子：
$$
\forall i \in [0, T), i \equiv i + \gcd(S, T) \pmod{\gcd(S, T)}
$$

$$
\forall i \in [0, T), t \in (0, \gcd(S, T)), i + t \not\equiv i \pmod{\gcd(S, T)}
$$

证明均显然。

此时我们考虑，对于一个环内的所有科学家，$ \xi $ 为环上某一点的贡献，我们要找到的就是第一个，或者说其减少最少个 $ S $ 遇到的 $ t_i $，这个东西不难想到，对于两个同环科学家 $ t_i, t_j $，且 $ t_j $ 在 $ t_i $ 之后，两者之间模意义下距离了多少个 $ S $ 就代表 $ i $ 的答案由多少。而对于不同环中显然互相无交无关联。

所以我们可以考虑对于一个环内的所有科学家 $ t_1, t_2, \cdots $，我们如果能够按照其在环内的遍历顺序排序，或者说满足 $ t_i $ 之后的 $ t_j $ 一定是 $ t_i $ 经过最小次模意义下加 $ S $ 的操作得到的（这里如何做我们后文再叙），然后遍历一遍，此时对于相邻的 $ t_i \lt t_j $（注意此时的 $ \lt $ 意义是我们重载过的小于号，且两者相邻或 $ i $ 为末尾 $ j $ 为初始）存在：
$$
t_i + xS \equiv t_j \pmod{T}
$$
转化后得到：
$$
Sx + Ty = t_j - t_i
$$
并且显然满足 $ \gcd(S, T) \mid t_j - t_i $，满足 exgcd 的限制，注意此时 $ y $ 是任意的，所以仅需求出 $ x $ 的最小非负整数解，其即代表了 $ t_i $ 对应科学家的总贡献，也就是答案。同时注意若环内仅有一个科学家则其贡献直接为 $ \dfrac{T}{\gcd(S, T)} $。

现在我们在将目光移回上文所述的排序过程，考虑发现该限制对应到上述方程的意义就是 $ x $ 最小的解，如果满足 $ S \perp T $ 那么我们是可以通过乘逆元转换为 $ t_i \times S^{-1} \bmod{T} $ 的偏序关系，但本题显然不满足，于是不难想到若其初始时位置为 $ p_i = t_i \bmod{\gcd(S, T)} $，那么一定存在 $ p_i + kS \equiv t_i \pmod{T} $，发现此方程亦为 exgcd 形式，转换为 $ Sx + Ty = t_i - p_i $，求出 $ x $ 的最小非负整数解即可得到其在环中对应的位置，以其为关键字进行排序则一定满足我们上述的偏序关系。而解相同的，即同环模意义下同位置的，不难想到我们优先保留 $ t_i $ 较小的即可，较后的一定为 $ 0 $。

最终复杂度卡在排序和两次 exgcd 上，为 $ O(n \log n) $。

Tips：还有些小细节，观察所有式子发现，对于所有 $ S $ 和 $ t_i $ 都可以并需要进行 $ S \leftarrow S \bmod{T}, t_i \leftarrow t_i \bmod{T} $，这是对答案无影响的。对于在 `set` 中排除同环模意义下同位置的，可以考虑利用 C++ 特性，重载小于号，使得只保留相同第一关键字中最先加入的，可以证明最先加入的一定最小。

附：好久没写 exgcd 了，简单重推一下吧：

要求 $ ax + by = \gcd(a, b) $。

显然存在 $ bx' + (a \bmod{b})y' = \gcd(b, a \bmod{b}) $。

又 $ \gcd(a, b) = \gcd(b, a \bmod{b}) $。

整理并展开 $ a \bmod b $ 得到 $ ax + by = bx' + (a - \lfloor \dfrac{a}{b} \rfloor \times b)y' $。

则显然有 $ x = y', y = x' - \lfloor \dfrac{a}{b} \rfloor \times y $。

问题规模缩减，不断递归，直到最终 $ \gcd = 0 $ 则回溯 $ x = 1, y = 0 $ 即可。

此时得到任意解，令 $ d = \dfrac{t_j - t_i}{\gcd(S, T)} $，显然整除，则 $ x \leftarrow x \times d, y \leftarrow y \times d $ 即可，同时注意我们想要求得 $ x $ 得最小非负解，发现方程通解为 $ x + k\dfrac{T}{\gcd(S, T)}, y - k\dfrac{S}{\gcd(S, T)} $，以 $ \dfrac{T}{\gcd(S, T)} $ 为模数对 $ x $ 取模转正后求出对应的 $ y $ 即可找到 $ x $ 的最小非负解。

### Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}
#define ROPNEW_NODE void* Node::operator new(size_t){static Node* P = nd; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N;
ll S, T;
int A[210000];
int ans[210000];
int gcdv(-1);
struct Node{
    ll v; ll origin; int idx;
    friend const bool operator < (const Node &a, const Node &b){
        return a.v < b.v;
    }
};
unordered_map < int, set < Node > > loops;

void exgcd(ll a, ll b, ll &x, ll &y){
    if(!b)return x = 1, y = 0, void();
    exgcd(b, a % b, x, y);
    int tmp(x);
    x = y, y = tmp - a / b * y;
}
ll CalMnX(ll ti, ll tj){
    ll x, y; ll d = (tj - ti) / gcdv;
    exgcd(S, T, x, y);
    x *= d, y *= d;
    ll P = T / gcdv;
    x = (x % P + P) % P;
    y = (tj - ti - S * x) / T;
    return x;
}

int main(){
    T = read(), N = read();
    for(int i = 1; i <= N; ++i)(S += (A[i] = read())) %= T;
    gcdv = __gcd(S, T);
    loops[0].insert({Node{0, 0, 1}});
    ll cur(0);
    for(int i = 2; i <= N; ++i)
        (cur += A[i]) %= T,
        loops[cur % gcdv].insert(Node{CalMnX(cur % gcdv, cur), cur, i});
    for(auto loop : loops){
        if((int)loop.second.size() == 1){ans[loop.second.begin()->idx] = T / gcdv; continue;}
        for(auto it = loop.second.begin(); it != loop.second.end(); advance(it, 1)){
            auto nxit = it == prev(loop.second.end()) ? loop.second.begin() : next(it);
            ans[it->idx] = CalMnX(it->origin, nxit->origin);
        }
    }
    for(int i = 1; i <= N; ++i)printf("%d%c", ans[i], i == N ? '\n' : ' ');
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_02_13 初稿

---

## 作者：Saliеri (赞：4)

复读一遍 CF 题解。的确是一种非常妙的理解方式。

___

考虑同一个天文学家会在那些 $\text{mod} \ T$ 的时间下观测。

显然，如果设 $st_i =(\sum_{j=2}^ia_j)\bmod T,S = \sum_{j=1}^na_j$，那么 $i$ 这位天文学家只会在 $(st_i+kS)\bmod T,k\in N$ 这些时间时观测。

接下来考虑如何统计答案，我们考虑每一位天文学家会第一次“到达”哪些余数。

考虑挖掘一点性质，我们来将每一个天文学家的路径转化到图上。

如果我们把每一个余数  $x$ 看做图上的一个点，向 $(x+S)\bmod T$ 连边的话，通过剩余系那套理论不难证明：

- 图是由 $\gcd(S,T)$ 个大小为 $\dfrac{T}{\gcd(S,T)}$ 的环组成的。

- 每一个环内的数都 $\text{mod} \gcd(S,T)$ 同余。

既然被划成了若干个环，那我们来考虑多个天文学家在同一个环中的答案情况。

首先，如果有多个天文学家的 $st_i$ 相等，显然除了最前面那位答案都是零。

图画出来也不难发现，每一个天文学家的答案就是它沿着环的方向到环上的下一个天文学家的距离（如果环内只有一个点就是环的大小）。

现在的问题在于，如何求出上面所说的那个距离。

我们考虑给每个环定义一个起始点，下标为 $0$，其他的点这样顺次编号过去，这样距离就被转化成了编号之差。

很明显，每个环的起始点选 $t,0\le t<\gcd(S,T)$ 是非常靠谱的，因为这样其他所有环内的点都可以被表示为 $(t+kS)\bmod T,k\in N$。

如何求出某个余数 $x$ 在环内的编号？使用上面写出的形式，即得到 

$$(x\bmod \gcd(S,T))+kS\equiv x (\bmod\  T)$$

的最小自然数解，用 exgcd 求解这个同余方程即可。

最后遍历每一个环，对每一个天文学家求出答案就完了。

___
代码：

注意特判一个环中只有一个天文学家的情况。

```cpp
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>
typedef long long ll;
const int maxn = 2e5+5;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll st[maxn],S,d,x,y;
int n,T,a[maxn],ans[maxn];
struct pair{
	int pos,id;
	pair(int X=0,int Y=0):pos(X),id(Y){};
	bool operator <(pair b)const{return pos<b.pos;}
};
std :: map<int,bool> vis;
std :: map<int,std::vector<pair>> cys;
void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b)return x=1,y=0,void();
	exgcd(b,a%b,x,y);ll t = x;
	x = y,y = t-y*(a/b);
}
int main(){
	scanf("%d %d",&T,&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	st[1] = 0;for(int i=2;i<=n;++i)st[i] = (st[i-1]+a[i])%T;
	S = (st[n]+a[1])%T,d = gcd(S,T);
	for(int i=1;i<=n;++i){
		if(!vis[st[i]]){
			vis[st[i]] = 1;
			exgcd(S,T,x,y),x *= (st[i]-st[i]%d)/d,y *= (st[i]-st[i]%d)/d;
			x = (x%(T/d)+T/d)%(T/d),cys[st[i]%d].push_back(pair(x,i));
		}
	}
	std :: map<int,std::vector<pair>> :: iterator it = cys.begin();
	for(;it != cys.end();++it){
		std :: sort(it->second.begin(),it->second.end());
		std :: vector <pair> :: iterator It = it->second.begin(),nxt = It;
		while(++nxt,nxt != it->second.end())ans[It->id] = nxt->pos-It->pos,It = nxt;
		--nxt,ans[nxt->id] = (it->second.size()==1?T/d:(it->second.begin()->pos-nxt->pos+(T/d))%(T/d));
	}
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：柳易辰 (赞：2)

## 暴力

左闭右开的区间不好描述，不如就取区间的左端点，按时间点来描述。本文下标由 0 开始。称宇航员 $0\sim n-1$ 都完成一次观测为一轮。

设 $v=(\sum a_i\bmod t)$，设第 $i$ 个宇航员首次观测的时间点为 $b_i$，那么下一次他就会观测到时间点 $(b_i+v)\bmod t$，如果宇航员 $p$ 在观测时间点 $i$，我们不妨直接说宇航员 $p$ 在时间点 $i$。

显然地，如果存在 $b_i=b_j(i<j)$，我们可以保留宇航员 $i$，扔掉宇航员 $j$，因为 $j$ 相当于跟在宇航员 $i$ 后面，永远无法到达新的时间点。

于是我们可以写个[暴力](https://codeforces.com/contest/819/submission/278324731)，用 `queue` 模拟这个过程，另开数组 $c_i$ 表示时间点 $i$ 首次被哪个宇航员观测到。`queue<pair<int, int>>` 记录宇航员和它所在的时间点。每次取出队首，设是宇航员 $p$，他所在的时间点为 $i$。

+ 如果 $c_i=-1$，说明时间点 $i$ 还没被观测到。令 $c_i=p$，再把 $(p,(i+v)\bmod t)$ 放入队尾。

+ 如果 $c_i=q\neq-1$，说明时间点 $i$ 先被宇航员 $q$ 观测到，此时 $p$ 就不用重新入队了。因为如果 $q$ 先到时间点 $i$，那么 $q$ 到 $(i+v)\bmod t$ 的时间必然早于 $p$ 下次到达 $i+v$，故 $p$ 必然无法更新 $c_{(i+v)\bmod t}$，对于 $(i+kv)\bmod t$ 可以依次类推，$p$ 没有更新价值了，就不用再入队了。

所以每个 $c_i$ 至多被更新一次，最后数一下有多少 $c_i=p$ 就是宇航员的 $p$ 的答案，时间复杂度 $O(n+t)$。

从这个暴力可以得到的启示：

+ 由暴力发现，满足 $c_i=p$ 的 $i$ 必然是由 $b_p$ 开始连续的一段，也就是说一个宇航员只能在前若干轮找到属于自己的时间点。我们求出这个轮数就是宇航员 $p$ 的答案。形式化地说，$c_{(b_i+jv)\bmod v}$ 在 $j$ 的一段从 0 开始的前缀均满足 $c_{(b_i+jv)\bmod v}=p$，我们要求出最大的 $j$，$p$ 的答案就是 $j+1$。
+ 根据暴力 $c_i=q\neq-1$ 的情况我们又可以发现，这个 $i$ 必然是 $b_q$，也就是宇航员 $q$ 的起点。不然 $q$ 也会在上一轮先到达 $(i-v)\bmod t$，宇航员 $p$ 在上一轮就应该退出 `queue`。

&nbsp;
## 正解

我们考虑优化暴力的过程。假设我们要求宇航员 $p$ 的答案，我们可以尝试求出每个宇航员 $q\neq p$，宇航员 $p$ 要进过多少轮才能到达 $b_q$，记轮数是 $d_q$。前文提到求出最大的 $j$，这里的 $j=\min_{p\neq q}d_q-1$，就是说在第 $j$ 轮后宇航员 $p$ 不再能更新 $c_i$，会存在一个 $q$，满足 $b_q\equiv b_p+jv\bmod t$，于是宇航员 $p$ 的答案就是 $\min_{p\neq q}d_q$。

尝试求出每个 $d_q$，也就是一个形如 $b_p+vd_q\equiv b_q\bmod t$ 的方程，我们要求 $v$ 的最小整数解。

不妨用 $x$ 表示 $d_q$，引入 $y$ 表示 $\frac{b_p+vd_p-((b_p+vd_p)\bmod t)}t$，表示取模了几次，那么方程就变成了 $b_p+vx=b_q+ty$，我们要求一个最小的 $x$，同时必须满足 $y$ 非负。

移项得到 $vx-ty=b_q-b_p$。我们知道 `exgcd(a, b, x, y)` 可以求解方程 $ax+by=\gcd(a,b)$ 的一组解，进而得到 $c\mid\gcd(a,b)$ 的方程 $ax+by=c$ 的解。注意到这个前提条件，也就是说宇航员 $p$ 不能到某些宇航员 $q$。

记 $g=\gcd(t,v)$，我们可以把宇航员按照 $b_p\bmod g$ 分类（等价类），两类之间的宇航员无法相互到达。于是我们成功把问题拆成了子问题，每个子问题内的宇航员都可以相互到达。

考虑处理每类之内的答案，如果类内只有一个点，那么答案是 $\frac tg$。

多个点的话，也就是说不定方程 $vx-ty=b_q-b_p$ 由于 $g\mid(b_q-b_p)$ 肯定存在整数解 $x,y$。用`exgcd(v, t, x0, y0)`解出方程 $vx_0+ty_0=g$ 的一组可行解之后，显然我们也可以得到方程 $vx-ty=b_q-b_p$ 的一组解：
$$
\begin{cases}
x=\dfrac {x_0}g(b_q-b_p)\\
y=\dfrac {y_0}g(b_p-b_q)
\end{cases}
$$
现在我们要通过调整使 $x,y$ 都非负，并且 $x$ 最小。容易发现只要 $x$ 非负，$y$ 也非负。可行且幅度最小的调整方式是：$x\gets x+\frac{kt}g$。于是我们可以先把 $x$ 调整成正的，再调整成最小的（就是令 $k=-\lfloor\frac{xg}{kt}\rfloor$ 并进行调整）。这样我们就算出 $d_p$ 了。取个 $\min$ 就可以得到 $p$ 的答案，单次时间复杂度 $O(n)$，总时间复杂度 $O(n^2)$。

我们再看看如何优化。对于一类而言，我们重新记 $d_{p,q}$ 是宇航员 $p$ 达到宇航员 $q$ 的最小轮数（后文 $q$ 是指任意宇航员）。求 $p$ 的答案时，对所有 $q$，我们已经求出了所有 $d_{p,q}$。那么我们求 $q$ 的答案时，我们难道要把所有 $d_{q,k}$ 重新求一遍吗？答案是不用的。我们可以充分利用 $d_{p,q}$，如果 $d_{p,q}<d_{p,k}$，$d_{p,q}=d_{p,k}-d_{p,q}$，否则 $d_{p,q}=\frac tg+d_{p,k}-d_{p,q}$。如果把求 $d$ 的过程看作求**最短路**，那么由单向环形最短路的性质可以轻松证明。

也就是说我们只有求一次 $d_{p,q}$ 相当于得到了类内任意两点 $x,y$ 的 $d_{x,y}$。注意我们要求的是 $\min$，我们实际上不用把每个 $d_{x,y}$ 求出来。我们只要把 $d_{p,q}$ 求出来之后从小到大排一遍序，那么要求一个宇航员的答案，只要看他在排序后数组里的位置，他的下一位宇航员与他的 $d_{p,q}$ 之差就是答案。他的下一位宇航员的实际含义就是他不断跳的过程中访问到的第一个起点是哪个宇航员的起点。

对于最后一位宇航员 $q$，显然他的下一位就是 $p$，答案就是 $\frac tg-d_{p,q}$。

时间复杂度 $O(n\log n+\log t)$，[代码](https://codeforces.com/contest/819/submission/278333577)。

---

