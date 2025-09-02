# [ABC255G] Constrained Nim

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc255/tasks/abc255_g

高橋君と青木君が、いくつかの石からなる $ N $ 個の山を用いて石とりゲームで対戦します。

はじめ、$ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 番目の山は $ A_i $ 個の石からなります。 高橋君からはじめ、$ 2 $ 人は交互に次の行動をくりかえします。

> 石が $ 1 $ 個以上残っている山を $ 1 $ つ選び、その山から $ 1 $ 個以上の石を取り除く。

ただし、このゲームには $ M $ 種類の禁じ手があり、禁じ手に該当する行動を行うことはできません。  
 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 種類目の禁じ手は「ちょうど $ X_i $ 個の石からなる山からちょうど $ Y_i $ 個の石を取り除くこと」です。

先に行動を行うことができなくなった方のプレイヤーの負けとなり、負けなかった方のプレイヤーの勝ちとなります。 両者が自身が勝つために最適な戦略をとるとき、どちらのプレイヤーが勝つかを答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^{18} $
- $ 1\ \leq\ Y_i\ \leq\ X_i\ \leq\ 10^{18} $
- $ i\ \neq\ j\ \Rightarrow\ (X_i,\ Y_i)\ \neq\ (X_j,\ Y_j) $
- 入力はすべて整数

### Sample Explanation 1

$ i\ =\ 1,\ 2,\ 3 $ について、$ i $ 番目の山にある石の個数を $ A'_i $ とし、 それぞれの山にある石の個数を数列 $ A'\ =\ (A'_1,\ A'_2,\ A'_3) $ を用いて表すことにします。 ゲームが始まる前の時点では、$ A'\ =\ (1,\ 2,\ 4) $ です。ゲームの進行の一例として次のものがあります。 - まず、高橋君が $ 3 $ 番目の山から石を $ 1 $ 個取り除く。その結果、$ A'\ =\ (1,\ 2,\ 3) $ となる。 - 次に、青木君が $ 2 $ 番目の山から石を $ 2 $ 個取り除く。その結果、$ A'\ =\ (1,\ 0,\ 3) $ となる。 - さらに、高橋君が $ 3 $ 番目の山から石を $ 2 $ 個取り除く。その結果、$ A'\ =\ (1,\ 0,\ 1) $ となる。 その後の時点で、$ 1 $ 番目と $ 3 $ 番目の山にはまだ石が $ 1 $ 個ずつ残っていますが、ちょうど $ 1 $ 個の石からなる山からちょうど $ 1 $ 個の石を取り除くことは $ 4 $ 種類目の禁じ手に該当するため、青木君は行動を行うことができません。したがって、高橋君の勝ちとなります。

## 样例 #1

### 输入

```
3 4
1 2 4
2 1
3 3
3 1
1 1```

### 输出

```
Takahashi```

## 样例 #2

### 输入

```
1 5
5
5 1
5 2
5 3
5 4
5 5```

### 输出

```
Aoki```

# 题解

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc255_g)

**题目大意**

> 给定 $n$ 堆石子的 Nim 游戏，有 $m$ 个限制表示：当前堆大小为 $x$ 时不能取 $y$ 个石子，求最终谁必胜。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

考虑算 SG 函数，我们需要特殊处理 $\mathcal O(m)$ 个有特殊限制的点的 $SG(x)$。

首先如果一个 $x$ 没有限制，那么他的 SG 函数值就是 $1+\max_{i\le x} SG(i)$，因此 $SG$ 函数可以看成若干段斜率为 $1$ 的一次函数，在所有有特殊限制的点处取值突变，因此对于突变点 $x$ ，由 $SG(x+1)$ 的值即可确定该段函数。

因此用 `map` 存每个突变点 $x$ 和 $x+1$ 的 SG 函数值，二分即可得到任意 $x$ 的 SG 函数值。

然后考虑突变点，我们要在 $SG(1)\sim SG(x-1)$ 中找到所有 $SG(x-y)$ 并删掉，统计每种删掉的函数值的出现个数，我们只要求某个 SG 函数值 $w$ 的出现总次数。

观察一下函数图像可以发现，对于所有非突变点，他们的 SG 函数值单调递增（这是显然的），且中间不存在断点：可以证明每个突变点取值一定严格变小，即 $SG(x)<SG(x-1)+1$ 推出 $SG(x+1)=SG(x-1)+1$。

因此 $w$ 一定在非突变点中出现恰好一次，而在突变点中的出现次数可以用 `map` 维护。

时间复杂度 $\mathcal O(m\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5;
map <ll,vector<ll>> lim;
map <ll,ll> F,c,q;
ll a[MAXN];
ll sg(ll x) {
	auto it=*--F.upper_bound(x);
	return it.second+x-it.first;
}
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(int i=1;i<=m;++i) {
		ll x,y; scanf("%lld%lld",&x,&y);
		lim[x].push_back(x-y);
	}
	ll mx=0; F[0]=0;
	for(auto &I:lim) {
		ll x=I.first;
		mx=max(mx,sg(x-1));
		q.clear();
		for(ll y:I.second) ++q[sg(y)];
		for(auto it:q) {
			if(it.second>=c[it.first]+1) {
				++c[F[x]=it.first]; break;
			}
		}
		mx=max(mx,sg(x)),F[x+1]=mx+1;
	}
	ll ans=0;
	for(int i=1;i<=n;++i) ans^=sg(a[i]);
	puts(ans?"Takahashi":"Aoki");
	return 0;
}
```

---

## 作者：Tsawke (赞：0)

# [[ABC255G] Constrained Nim](https://www.luogu.com.cn/problem/AT_abc255_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC255G)

## 题面

一般 Nim 游戏基础上增加 $ m $ 条限制，限制当石子数为 $ x_i $ 时不能拿走其中的 $ y_i $ 个。

## Solution

显然博弈论，考虑 SG函数。Nim 游戏标准套路，对于多个石子堆求出每个石子堆石子数 $ a_i $ 的 $ SG(a_i) $，若 $ \bigoplus_{i = 1}^n SG(a_i) = 0 $ 则先手必输，反之必胜。关于 SG函数 的详解：[SG函数学习笔记](http://blog.tsawke.com?t=SG)。

本题的区别即为 $ m $ 条限制，考虑如何处理。显然一般 Nim 游戏的 SG 函数有转移 $ SG(i) = \operatorname{mex}\{SG(j) \mid j \in [1, i - 1]\} $，本题的区别不难想到就是在一般的 SG函数 基础上，在求 $ \operatorname{mex} $ 的时候需要从中去掉一些值，也就是去掉 $ SG(x_i) $ 转移中的 $ SG(x_i - y_i) $。严谨点叙述就是 $ SG(i) = \operatorname{mex}\{SG(j) \mid j \in [1, i - 1] \land (i, j) \neq (x_k, x_k - y_k), k \in[1, m] \} $。考虑维护，显然值域过大无法硬做。发现每次从中去掉一些值后，$ \operatorname{mex} $ 的值就会变为最小的被全部删除的元素。然后在这个位置以后，下一条限制以前，每次的 $ SG(i) = SG(i - 1) + 1 $。发现整个值的分布实际上就是一些特殊点和很多条斜率为 $ 1 $ 的线段。所以我们对于答案，考虑开个 `map` 记录转折点，每次查询对应的所在位置然后增加对应数量的 $ 1 $ 即可。

具体实现过程也不难理解，开个 `map` 里套 `basic_string` 维护对应 $ x_i $ 的所有 $ x_i - y_i $，然后遍历，显然升序遍历过程中 $ x_i $ 以内的 $ SG $ 均已确定。然后考虑如何确定当前的 $ SG(i) $，不难发现对于没有限制的 $ SG $ 值即为其之前的所有 $ SG $ 的最大值，也就是前缀最大值 $ +1 $。对于有限制的，我们枚举其所有限制，找到最小的一个被删没的值（注意这里比较的时候要 $ +1 $，原因是遍历到此时的时候一般情况下会有一个 $ SG(i) = i $），将其设为这个。此为特殊点，然后在其之后的点依然按照一般的斜率为 $ 1 $ 地增长，用前缀最大值更新，记录一下即可。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

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

int N, M;
ll A[210000];
ll oplus(0);
map < ll, basic_string < ll > > rest;
map < ll, ll > SG, repeat;

ll CalSG(ll x){
    auto sp = *prev(SG.upper_bound(x));
    return sp.second + (x - sp.first);
}

int main(){
    N = read(), M = read(); SG.insert({0, 0});
    for(int i = 1; i <= N; ++i)A[i] = read < ll >();
    for(int i = 1; i <= M; ++i){
        ll p = read < ll >(), v = read < ll >();
        rest[p] += p - v;
    }
    ll preMx(-1);
    for(auto &mp : rest){
        preMx = max(preMx, CalSG(mp.first - 1));
        map < ll, ll > tmp;
        for(auto val : mp.second)tmp[CalSG(val)]++;
        for(auto cur : tmp){
            if(cur.second >= repeat[cur.first] + 1){
                repeat[cur.first]++;
                SG[mp.first] = cur.first;
                break;
            }
        }preMx = max(preMx, CalSG(mp.first));
        SG[mp.first + 1] = preMx + 1;
    }
    for(int i = 1; i <= N; ++i)oplus ^= CalSG(A[i]);
    printf("%s\n", oplus ? "Takahashi" : "Aoki");
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

update-2022_12_07 初稿

---

## 作者：fireinice (赞：0)

> $n$ 堆石子的nim游戏,有 $m$ 个限制,第 $i$ 个限制 $x_i,y_i$ 表示若一个石子堆剩余石子为 $x_i$ ,你就不能从其中拿走 $y_i$ 个.问先手必胜/必负.
> 
> $n,m\le 2\times 10^5,a_i\le 10^{18}$

公平组合游戏,只需要考虑求一个石子堆的 SG 值,最后异或起来判断即可.

没有限制的时候显然是 $SG(x)=x$ ,那么加上限制之后会有若干个特殊点和若干段 $y=x+k$ 的一次函数.没有限制的点的值显然是前面的最大值加1,而有限制的点可以考虑维护每个 $SG(x)$ 的出现次数,不断删掉被禁止的 $x$ ,找到最小的删没了的 $SG(x)$ 就是当前的SG值.

但是直接维护 $SG(x)$ 会爆炸,但发现只维护特殊点的就行,其他的位置的次数就是一个默认的 $1$.

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

const int N = 2e5 + 500, M = 2e5 + 500;
int n, m;
ll a[N];
map<ll, vector<ll>> lim;
map<ll, ll> sg;
map<ll, ll> cnt;

ll getsg(ll x) {
    auto iter = --sg.upper_bound(x);
    return (x - iter->first) + iter->second;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= m; i++) {
        ll x, y;
        cin >> x >> y;
        lim[x].push_back(x - y);
    }

    sg[0] = 0;
    ll mx = 0;
    for (auto& it : lim) {
        vector<ll>& ls = it.second;
        ll x = it.first;
        mx = max(mx, getsg(x - 1));
        sort(ls.begin(), ls.end());
        map<ll, ll> tmp;
        for (ll y : ls) 
            tmp[getsg(y)]++;
        ll v = 5e18;
        for (auto tp : tmp) {
            if (cnt[tp.first] + 1 <= tp.second) {
                v = tp.first;
                break;
            }
        }
        if (v < 5e18) {
            cnt[v]++;
            sg[x] = v;
        }
        mx = max(getsg(x), mx);
        sg[x + 1] = mx + 1;
    }
    
    ll res = 0;
    for (int i = 1; i <= n; i++)
        res ^= getsg(a[i]);
    cout << (res ? "Takahashi" : "Aoki");
    return 0;
}

// 0 1 1
```

---

