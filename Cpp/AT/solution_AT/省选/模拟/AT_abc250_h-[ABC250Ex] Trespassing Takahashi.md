# [ABC250Ex] Trespassing Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc250/tasks/abc250_h

$ 1 $ から $ N $ までの番号がついた $ N $ 個の地点と $ M $ 本の道があります。 $ i\ \,\ (1\ \leq\ i\ \leq\ M) $ 番目の道は地点 $ a_i $ と地点 $ b_i $ を双方向に結んでいて、通過に $ c_i $ 分かかります。すべての地点同士は道を何本か通って行き来出来ます。また、地点 $ 1,\ldots,\ K $ には家があります。

$ i=1,\ldots,Q $ に対し、次の問題を解いてください。

> 地点 $ x_i $ の家にいる高橋君が地点 $ y_i $ の家に移動しようとしている。  
>  高橋君は最後に睡眠を取ってから道の移動にかかった時間が $ t_i $ 分を超えると移動が出来なくなる。  
>  睡眠を取れる場所は家がある地点のみであるが、回数に制限は無い。  
>  高橋君が地点 $ x_i $ から地点 $ y_i $ まで移動出来るならば `Yes` と、出来ないならば `No` と出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ K\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min\ (2\ \times\ 10^5,\ \frac{N(N-1)}{2}) $
- $ 1\ \leq\ a_i\ \lt\ b_i\ \leq\ N $
- $ i\ \neq\ j $ ならば $ (a_i,b_i)\ \neq\ (a_j,b_j) $
- $ 1\ \leq\ c_i\ \leq\ 10^9 $
- すべての地点同士は道を何本か通って行き来出来る
- $ 1\ \leq\ Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ x_i\ \lt\ y_i\ \leq\ K $
- $ 1\ \leq\ t_1\ \leq\ \ldots\ \leq\ t_Q\ \leq\ 10^{15} $
- 入力は全て整数

### Sample Explanation 1

$ 3 $ 番目の問題において、地点 $ 1 $ から地点 $ 3 $ に直接向かうと $ 13 $ 分以上かかります。しかし、 $ 12 $ 分かけて地点 $ 2 $ に移動し、そこにある家で睡眠を取ってから地点 $ 3 $ に移動することが出来ます。よって、答えは `Yes` となります。

## 样例 #1

### 输入

```
6 6 3
1 4 1
4 6 4
2 5 2
3 5 3
5 6 5
1 2 15
3
2 3 4
2 3 5
1 3 12```

### 输出

```
No
Yes
Yes```

# 题解

## 作者：Tsawke (赞：7)

# [[ABC250Ex] Trespassing Takahashi](https://www.luogu.com.cn/problem/AT_abc250_h) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC250Ex)

## 题面

给定一张 $ n $ 个点 $ m $ 条边的无向连通简单图。每条边存在 $ a_i, b_i, c_i $，表示 $ a_i \rightarrow b_i $ 或 $ b_i \rightarrow a_i $ 耗时 $ c_i $。给定 $ k $，定义 $ n $ 个点中只有前 $ k $ 个点有房子，$ q $ 次询问，每次给定 $ x, y, t $，求从 $ x $ 到 $ y $ **连续的不在房子中的时间**是否一定会超过 $ t $，超过输出 `No`，反之输出 `Yes`。保证询问中 $ t $ 满足升序。

## Solution

考虑维护对于走每条边时需要多长时间才能连通最近的两个房子，换句话说，满足这个时间的时候这条边就一定可以被走。具体维护可以考虑建一个超级源点并向所有房子连个边，然后跑个 Dijk 即可，当然直接往队列里把所有房子点都塞进去也行。然后我们可以令 $ c_i \leftarrow c_i + dis_{a_i} + dis_{b_i} $ 即可，然后显然可以用并查集维护。

具体地，每次询问将边集里所有新的 $ c_i $ 满足 $ c_i \le t $ 的边加上，用并查集维护，然后查询一下 $ x, y $ 是否连通即可，这个复杂度是 $ O(mq) $ 的，当然发现 $ t $ 符合升序，所以给边排个序跑一边即可，最终复杂度应该是卡在排序和 Dijk 上，也就是 $ O(n \log n + m \log m) $。

同时不难想到即使 $ t $ 不符合升序也可以离线排个序再跑，复杂度多个 $ O(q \log q) $ 而已。至此本题已经结束，下面是一道加强版的双倍经验。

存在一道双倍经验 [CF1253F Cheap Robot](https://www.luogu.com.cn/problem/CF1253F)，略有区别，这里简单说一下：这道题的区别就在于询问的是最小的 $ t $，这样的话实际上是不太好用刚才的思路离线下来维护的，有一个复杂度不太正确但能过的思路，就是将每个询问的 $ a, b $ 分别挂在两个点上，然后将 $ c_i $ 排序，从小到大依次加边，同时更新所有挂在连通块根上的答案，再对应的把询问合上去。但是这个的并查集一定需要按秩合并，否则如果 `clear()` 之后 `shrink_to_fit()` 就会 TLE，否则会 MLE，按秩合并会保证合并询问的时候不会复制太多次以保证空间。这个东西的复杂度理论上似乎可以被卡到 $ O(mq) $，但是本题没卡。当然还有一个我口糊的剪枝，就是挂在点上的询问我们用链表维护，然后贪心地取第一次更新这个点时的答案，显然不劣，于是更新后 $ O(1) $ 删除即可，但是这个东西理论上也能被卡到 $ O(mq) $，不过需要精细设计数据。当然正确的做法最后应该是建出最小生成树然后树剖或者倍增之类的实现。

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

struct Edge{
    Edge* nxt;
    int to;
    ll val;
    OPNEW;
}ed[410000];
ROPNEW(ed);
Edge* head[210000];

int N, M, K;
bitset < 210000 > vis;
ll dis[210000];
priority_queue < tuple < ll, int, int >, vector < tuple < ll, int, int > >, greater < tuple < ll, int, int > > > edgs;

class UnionFind{
private:
    int fa[210000];
public:
    UnionFind(void){for(int i = 1; i <= 201000; ++i)fa[i] = i;}
    int Find(int x){return x == fa[x] ? x : fa[x] = Find(fa[x]);}
    void Union(int origin, int son){fa[Find(son)] = Find(origin);}
}uf;

void Dijk(void){
    memset(dis, 0x3f, sizeof dis);
    priority_queue < pair < ll, int >, vector < pair < ll, int > >, greater < pair < ll, int > > > cur;
    for(int i = 1; i <= K; ++i)cur.push({dis[i] = 0, i});
    while(!cur.empty()){
        int p = cur.top().second; cur.pop();
        if(vis[p])continue;
        vis[p] = true;
        for(auto i = head[p]; i; i = i->nxt)
            if(dis[p] + i->val < dis[SON])
                dis[SON] = dis[p] + i->val, cur.push({dis[SON], SON});
    }
}
int main(){
    N = read(), M = read(), K = read();
    for(int i = 1; i <= M; ++i){
        int s = read(), t = read(), v = read();
        head[s] = new Edge{head[s], t, v};
        head[t] = new Edge{head[t], s, v};
    }Dijk();
    for(int p = 1; p <= N; ++p)
        for(auto i = head[p]; i; i = i->nxt)
            edgs.push({i->val + dis[p] + dis[SON], p, SON});
    int Q = read();
    while(Q--){
        int s = read(), t = read(); ll lim = read < ll >();
        while(!edgs.empty() && get < 0 >(edgs.top()) <= lim)
            uf.Union(get < 1 >(edgs.top()), get < 2 >(edgs.top())), edgs.pop();
        printf("%s\n", uf.Find(s) == uf.Find(t) ? "Yes" : "No");
    }
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

update-2022_12_20 初稿

---

