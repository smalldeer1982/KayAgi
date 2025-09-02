# [USACO22OPEN] Apple Catching G

## 题目描述

天上下苹果了！在某些时刻，一定数量的苹果会落到数轴上。在某些时刻，Farmer John 的一些奶牛将到达数轴并开始接苹果。

如果一个苹果在没有奶牛接住的情况下落到数轴上，它就会永远消失。如果一头奶牛和一个苹果同时到达，奶牛就会接住苹果。每头奶牛每秒可以移动一单位距离。一旦一头奶牛接住了一个苹果，她就会离开数轴。

如果 FJ 的奶牛以最优方式合作，她们总共能接住多少个苹果？

## 说明/提示

【样例解释 1】

在这个例子中，在 $t=5$ 时刻落地的 $100$ 个苹果均不能被接住。以下是一种接住 $10$ 个苹果的方式：

- FJ 的所有六头 $t=4$ 时刻到达的奶牛各接一个 $t=8$ 时刻落地的苹果。
- FJ 的一头 $t=2$ 时刻到达的奶牛接一个 $t=8$ 时刻落地的苹果。
- 余下三头 $t=2$ 时刻到达的奶牛各接一个 $t=6$ 时刻落地的苹果。

【样例解释 2】

再一次地，在 $t=5$ 时刻落地的苹果均不能被接住。除此之外，在 $t=2$ 时刻到达的奶牛均不能接住 $t=8$ 时刻落地的苹果。以下是一种接住 $9$ 个苹果的方式：

- FJ 的所有六头 $t=4$ 时刻到达的奶牛各接一个 $t=8$ 时刻落地的苹果。
- 余下三头 $t=2$ 时刻到达的奶牛各接一个 $t=6$ 时刻落地的苹果。

## 样例 #1

### 输入

```
5
2 5 10 100
2 6 0 3
2 8 10 7
1 2 4 5
1 4 7 6```

### 输出

```
10```

## 样例 #2

### 输入

```
5
2 5 10 100
2 6 0 3
2 8 11 7
1 2 4 5
1 4 7 6```

### 输出

```
9```

# 题解

## 作者：I_am_Accepted (赞：11)

### Analysis

设一奶牛的位置、时间为 $x',t'$，则苹果 $(x,t)$ 能被她接到当且仅当

$$\begin{cases}
t+x\ge t'+x'
\\
t-x\ge t'-x'
\end{cases}$$

所以对于每一个苹果或奶牛，其坐标为 $(t+x,t-x)$，这样就转化成二维数点问题了。

↓以下绿点表示苹果，红半平面交为奶牛。

![](https://cdn.luogu.com.cn/upload/image_hosting/b4zf2ysw.png)

我们有以下贪心策略（建议做一下 [P5894 [IOI2013]robots 机器人](https://www.luogu.com.cn/problem/P5894)，一样的做法）：

先按照 $x$ 降序排序奶牛，$x$ 相同的 $y$ 大的靠前。图中排序为 ABC。

再用 `std::set` 维护苹果，每次优先取 $x$ 坐标小的苹果。

这样 A 奶牛就会优先选区域 2 中的苹果，不会和 B 抢。

B 在 C 之前拿苹果，所以 C 不会先把 B 能拿的先抢走。

时间带 $\log$。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 200010

struct node{
	bool q;
	int x,y;
	mutable int cnt;
	friend bool operator<(node x,node y){return x.x<y.x;}
}a[N];
int n;
multiset<node> s;
multiset<node>::iterator it;
bool cmp(node x,node y){
	if(x.y!=y.y) return x.y>y.y;
	else return x.x>y.x;
}
signed main(){IOS;
	cin>>n;
	int opt,x,t;
	For(i,1,n){
		cin>>opt>>t>>x>>a[i].cnt;
		a[i].q=opt-1;
		a[i].x=t+x;
		a[i].y=t-x;
	}
	sort(a+1,a+1+n,cmp);
	int ans=0;
	For(i,1,n){
		if(!a[i].q){//cow
			while(a[i].cnt){
				it=s.lower_bound((node){0,a[i].x,0,0});
				if(it==s.end()) break;
				if(it->cnt>a[i].cnt){
					ans+=a[i].cnt;
					it->cnt-=a[i].cnt;
					break;
				}
				ans+=it->cnt;
				a[i].cnt-=it->cnt;
				s.erase(it);
			}
		}else{//apple
			s.insert(a[i]);
		}
	}
	cout<<ans<<endl;
return 0;}
```



---

## 作者：yaoxi (赞：10)

[或许会更好的阅读体验](https://yaoxi-std.github.io/2022/03/27/sol-p8272/)

### 题面

[题目链接](https://www.luogu.com.cn/problem/P8272)

### 解法

~~同届的巨佬们已经都通关了 USACO，只有我还在做 Gold 组的蓝题~~

看完样例，不难发现一头奶牛能够接到的苹果的区域如下图所示。

（横坐标为位置，纵坐标为时间，区域就是两条直线上方部分的半平面交）

![img1](https://cdn.luogu.com.cn/upload/image_hosting/61opx2yh.png)

假设第 $i$ 群奶牛能够接到的苹果集合为 $S_i$。

考虑现在有 $2$ 群奶牛 $i$ 和 $j$，可能 $S_i$ 被 $S_j$ 包含，也可能不互相包含。

如果 $S_i \subset S_j$，那么一定要先考虑 $S_i$ 能够取到的，否则可能 $j$ 取了 $S_i$ 集合中的而导致 $i$ 没有取满。

否则，就让 $i$ 贪心地优先取没有被 $S_j$ 包含的部分。

于是让所有奶牛集合按照 $(x_i - t_i, -x_i)$ 的二元组排序以保证被包含的集合先被考虑。用一个 `set` 维护苹果的集合，优先让奶牛匹配 $t_i + x_i$ 更小的苹果，暴力跳 `set` 即可。

至于复杂度，由于每次访问 `set` 中的元素都会使得要么删除一些苹果，要么删除一群奶牛，总的访问次数是 $O(n)$ 的，时间复杂度就是 $O(n \log n)$。

### AC代码

```cpp
/**
 * @file:           T1.cpp
 * @author:         yaoxi-std
 * @url:            
*/
// #pragma GCC optimize ("O2")
// #pragma GCC optimize ("Ofast", "inline", "-ffast-math")
// #pragma GCC target ("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
using namespace std;
#define resetIO(x) \
    freopen(#x ".in", "r", stdin), freopen(#x ".out", "w", stdout)
#define debug(fmt, ...) \
    fprintf(stderr, "[%s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
template <class _Tp>
inline _Tp& read(_Tp& x) {
    bool sign = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) sign |= (ch == '-');
    for (x = 0; isdigit(ch); ch = getchar()) x = x * 10 + (ch ^ 48);
    return sign ? (x = -x) : x;
}
template <class _Tp>
inline void write(_Tp x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar((x % 10) ^ 48);
}
bool m_be;
using ll = long long;
using pii = pair<int, int>;
#define fi first
#define se second
const int MAXN = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n;
struct Node {
    int q, t, x, n;
    bool operator<(const Node& o) const {
        return x - t < o.x - o.t || (x - t == o.x - o.t && x > o.x);
    }
} a[MAXN];
bool m_ed;
signed main() {
    // debug("Mem %.5lfMB.", fabs(&m_ed - &m_be) / 1048576);
    read(n);
    for (int i = 1; i <= n; ++i)
        read(a[i].q), read(a[i].t), read(a[i].x), read(a[i].n);
    sort(a + 1, a + n + 1);
    multiset<pii> st; ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i].q == 1) {
            auto it = st.lower_bound({a[i].t + a[i].x, 0});
            while (a[i].n && it != st.end()) {
                int tmp = min(a[i].n, it->se);
                ans += tmp, a[i].n -= tmp;
                if (it->se == tmp) st.erase(it++);
                else st.insert({it->fi, it->se - tmp}), st.erase(it);
            }
        } else {
            if (a[i].n) st.insert({a[i].t + a[i].x, a[i].n});
        }
    }
    write(ans), putchar('\n');
    return 0;
}
```

---

## 作者：Plozia (赞：5)

宣传博客 $\to$ [link](https://www.cnblogs.com/Plozia/p/16286463.html)

列出一头牛 $j$ 能够接到一个苹果 $i$ 的式子：$t_j-t_i\ge |x_j-x_i|$。

然后将所有牛和苹果以坐标 $(t_i,x_i)$ 形式画到坐标系内，注意到牛能够抓到的苹果在坐标系内画出来就是个往 $t$ 轴正方向，倾斜角分别为 45 度和 135 度的两条线中间那块部分。

因此我们将坐标系顺时针转 45 度，就变成了往右上角统计，每个点的新坐标为 $(t_i+x_i,t_i-x_i)$。注意这里本应除以 $\sqrt{2}$，但是这道题我们只关心坐标相对大小因此略去了 $\sqrt{2}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/sdtgrp3m.png)

假设我们转换坐标系后变成了这样，有三头牛 A,B,C，一种正确的贪心方式如下：

先排序，横坐标为第一关键字降序，纵坐标为第二关键字降序，那么图中的点排序为 B,A,C。

然后依次选择苹果，对于每一个点而言，选择纵坐标最低的若干苹果，比如 B 点就会选 3 空间内的。

正确性就是因为 B 先选了 3 空间所以不会和 A 冲突，而 B 又在 C 前选所以保证 B 能选的尽量多，能匹配的就尽量多。

以上只是一种贪心方式，实际上还有几种方式也都是对的，比如排序调换关键字顺序后让 A 尽量选 1 空间之类的。

实现时用一个 multiset 维护即可，但是注意 multiset 删除值的时候会将所有与该值相等的键全删了，删迭代器就不会了。

---

## 作者：namelessgugugu (赞：3)

受不了了，一拳被 overkill 打爆。

#### 题意

有一个数轴，接下来会出现 $n$ 个事件，分别是：

- $t_i$ 时刻，$n_i$ 只奶牛出现在数轴的 $x_i$ 位置上。

- $t_i$ 时刻，$n_i$ 颗苹果落在数轴的 $x_i$ 位置上。

奶牛可以以最高 $1$ 的速度移动，一只奶牛如果在苹果落下的瞬间处在其落下的位置，则与苹果一同消失。苹果未被接住会直接消失。

问最多有多少只奶牛能接住苹果。

$1 \leq n \leq 2 \cdot 10^5$。

#### 题解

首先把问题放到二维平面上，$y$ 轴表示时间，把苹果和奶牛对应到一个点上，则每个奶牛可以接住一个往上的斜着的平面的 $\frac{1}{4}$，把平面逆时针旋转 $45\degree$，则每个奶牛 $(x, y)$ 可以接住苹果 $(z, w)$ 当且仅当 $z \leq x, w \geq y$。

此时其实可以直接开始贪心，但是我的做法是网络流建模，对于一个奶牛，从汇点连一条向它的流量为 $n_i$ 的点，一个苹果连向汇点流量为 $n_i$ 的边，如果一个奶牛可以接到苹果，则它们之间连一条流量 $+ \infty$ 的边，答案即为最大流。

尝试求最小割，首先我们肯定不会去割流量 $+\infty$ 的边，所以每次都是割掉一个奶牛或者苹果，因此我们需要求解这样一个问题：删去一些奶牛或苹果，代价为 $n_i$，使得任意一个奶牛都接不到任意一个苹果。

考虑剩下来的奶牛能接到的苹果的那个 $\frac{1}{4}$ 平面并起来长什么样，一定是一条从左下到右上的折线。苹果能被奶牛接到的 $\frac{1}{4}$ 平面并起来也同理。一个方案合法当且仅当这两个折线没有交，换言之我们能找到一条折线把这两个折线区分开，就是说所有奶牛都在这个折线的左上方，而苹果都在右下方。

先对坐标离散化，然后使用 DP 求解，设 $f_{i, j}$ 表示当前折线终点在 $(i, j)$ 并且合法时需要的最小代价，转移是 $f_{i, j} = \min\{f_{i - 1, j} + C(i, j), f_{i, j - 1}\}$，其中 $C(i, j)$ 表示将处在 $x = i$ 这条直线上，$y > j$ 的苹果和 $y \leq j$ 的奶牛全部删掉的代价。

这个 DP 怎么想都过不去，于是考虑优化，首先发现由于总点数只有 $n$ 个，所以 $i$ 固定时，$C(i, j)$ 分成的段数总和是 $O(n)$ 的，而另一个转移相当于前缀取 $\min$，所以我们要想从 $f_{i - 1}$ 整体转移到 $f_i$，只需要实现两个操作：区间加，前缀取 $\min$。

这个用线段树其实并不难维护，但是标记有点多，我没写。我写的是维护 $f$ 的差分数组，每次区间加都是单点修改，而对于前缀取 $\min$ 操作，我们从后往前（这个顺序其实应该无所谓的，只是我的写法是这样）找到差分数组中每个为正的地方，把它推平，并找到差分数组中下一个不是 $0$ 的位置，继续推平。

注意到导致复杂度增加的操作有两个，一个是找到所有为正数的地方，另一个是暴力推平，第一个操作只会出现在区间加修改过的单点上，而由于每次推平都会导致差分数组中非 $0$ 的个数变少，而能使这个势能增加的是区间加操作。由于区间加只有 $O(n)$ 次，所以两个操作的次数都是 $O(n)$ 的。

用两个 `set` 分别维护差分数组中大于 $0$ 的位置和不为 $0$ 的位置即可，但是代码实现中，我没有使用 `set`，而是使用 `priority_queue` 去存大于 $0$ 的位置，在线段树上二分来找到下一个不为 $0$ 的位置。当然不管怎么实现，最后复杂度都是 $O(n \log n)$。

#### 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long ll;
typedef unsigned long long ull;
const int N = 200005;
int n;
struct node
{
    int typ, x, y, val;
} p[N];
int hh[N << 1], cnt;
std::vector<int> vec[N << 1];
ll f[N << 1];
struct SgT
{
    ll mn[N << 3];
    inline int ls(int x)
    {
        return x << 1;
    }
    inline int rs(int x)
    {
        return x << 1 | 1;
    }
    inline void pushup(int x)
    {
        mn[x] = std::min(mn[ls(x)], mn[rs(x)]);
        return;
    }
    void insert(int x, int l, int r, int p, ll v)
    {
        if(l == r)
            return mn[x] += v, void(0);
        int mid = (l + r) >> 1;
        if(p <= mid)
            insert(ls(x), l, mid, p, v);
        else
            insert(rs(x), mid + 1, r, p, v);
        pushup(x);
        return;
    }
    int get(int x, int l, int r, int ql, int qr)
    {
        if(ql > qr)
            return -1;
        if (l >= ql && r <= qr)
        {
            if (mn[x] == 0)
                return -1;
            if(l == r)
                return l;
            int mid = (l + r) >> 1;
            if(mn[ls(x)] < 0)
                return get(ls(x), l, mid, ql, qr);
            return get(rs(x), mid + 1, r, ql, qr);
        }
        int mid = (l + r) >> 1;
        int res = -1;
        if(ql <= mid && (res = get(ls(x), l, mid, ql, qr)) != -1)
            return res;
        if(qr > mid && (res = get(rs(x), mid + 1, r, ql, qr)) != -1)
            return res;
        return -1;
    }
} T;
std::priority_queue<int> que;
inline void add(int pos, ll v)
{
    if(pos == cnt + 1)
        return;
    f[pos] += v, T.insert(1, 1, cnt, pos, v);
    if(f[pos] > 0)
        que.push(pos);
    return;
}
int main(void)
{
    scanf("%d", &n);
    for(int i = 1, ty, t, x, v;i <= n;++i)
    {
        scanf("%d%d%d%d", &ty, &t, &x, &v);
        p[i] = {ty, x - t, x + t, v};
        hh[++cnt] = p[i].x, hh[++cnt] = p[i].y;
    }
    std::sort(hh + 1, hh + 1 + cnt), cnt = std::unique(hh + 1, hh + 1 + cnt) - hh - 1;
    for(int i = 1;i <= n;++i)
    {
        p[i].x = std::lower_bound(hh + 1, hh + 1 + cnt, p[i].x) - hh;
        p[i].y = std::lower_bound(hh + 1, hh + 1 + cnt, p[i].y) - hh;
        vec[p[i].x].push_back(i);
    }
    p[0] = {0, 0, cnt + 1, 0};
    ll bas = 0;
    for (int i = 1; i <= cnt; ++i)
    {
        std::sort(vec[i].begin(), vec[i].end(), [&](int x, int y) -> bool
                  { return p[x].y < p[y].y; });
        vec[i].push_back(0);
        ll sum = 0;
        for(int j : vec[i])
            if(p[j].typ == 2)
                sum += p[j].val;
        bas += sum;
        add(p[vec[i].front()].y, -sum);
        for (int j = 0; j < (signed)vec[i].size() - 1; ++j)
        {
            int x = vec[i][j], y = vec[i][j + 1];
            if (p[x].typ == 2)
                sum -= p[x].val;
            else
                sum += p[x].val;
            if (p[x].y == p[y].y)
                continue;
            add(p[x].y, sum), add(p[y].y, -sum);
        }
        while(!que.empty())
        {
            int x = que.top();
            que.pop();
            if(f[x] <= 0)
                continue;
            int now = x;
            ll val = f[x];
            add(x, -val);
            while(1)
            {
                int to = T.get(1, 1, cnt, now + 1, cnt);
                if(to == -1)
                    break;
                if(f[to] + val <= 0)
                {
                    add(to, val);
                    break;
                }
                ll nval = f[to] + val;
                add(to, -f[to]);
                now = to, val = nval;
            }
        }
    }
    for (int i = 1; i <= cnt; ++i)
        f[i] += f[i - 1];
    printf("%lld\n", f[cnt] + bas);
    return 0;
}
```

---

## 作者：pengyule (赞：1)

怪不得做不出来，题目理解错了——原来奶牛可以停停走走啊（没看到样例解释）。

题目在谈奶牛接苹果的事情，很明显我们需要考察奶牛能接到苹果的充要条件，发现必须满足 $t'-t\ge |x'-x|$，其中 $x',t'$ 为苹果、$x,t$ 为奶牛；绝对值考虑拆为 $t'-t\ge \max(x'-x,x-x')$，也即同时满足 $t'-x'\ge t-x,t'+x'\ge t+x$ 两个条件，并由不等式结构将 $(t-x,t+x)$ 看成整体。  
考虑这个式子的含义，它是一个二维偏序，那也就是二维数点，考虑以奶牛为主，则它能够接到的苹果应该满足 $(\mathfrak X',\mathfrak Y')\in [\mathfrak X,+\infty)\times [\mathfrak Y,+\infty)$；希望接到的点总数最多。这是经典的贪心问题，先把所有点都按 $y$ 递减排序，$y$ 相同按 $x$ 递减排序，根据题目约束不可能存在两个相同的点，那么顺次枚举，如果是苹果就加入 `multiset`，如果是奶牛就 `lower_bound` 当前的 `multiset` 中最小的横坐标 $\ge \mathfrak X$ 的点。不难发现总复杂度是 $O(n\log n)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	register char ch=getchar();register int x=0;
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
const int N=2e5+5;
int n,ans;
struct P {int q,x,y,n;}op[N];
bool operator<(P a,P b){
	return a.x<b.x;
}
bool operator==(P a,P b){
	return a.x==b.x;
}
multiset<P>apple;
multiset<P>::iterator it;
bool cmp(P a,P b){
	return a.y==b.y?a.x>b.x:a.y>b.y;
}
int main(){
	n=read();
	for(int i=1,t,x;i<=n;i++){
		op[i].q=read(),t=read(),x=read(),op[i].n=read();
		op[i].x=t-x,op[i].y=t+x;
	}
	sort(op+1,op+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(op[i].q==1){
			while(op[i].n){
				it=apple.lower_bound(op[i]);
				if(it==apple.end())break;
				ans+=min(op[i].n,it->n);
				if(op[i].n<it->n){
					P tmp=*it;
					apple.erase(it);
					tmp.n-=op[i].n;
					apple.insert(tmp);
					op[i].n=0;
				}
				else if(op[i].n==it->n){
					op[i].n=0;
					apple.erase(it);
				}
				else {
					op[i].n-=it->n;
					apple.erase(it);
				}
			}
		}
		else {
			apple.insert(op[i]);
		}
	}
	cout<<ans;
}
```

---

## 作者：EricQian (赞：1)

[P8272 [USACO22OPEN] Apple Catching G](https://www.luogu.com.cn/problem/P8272)

### 题解

假设在 $a(a_x,a_t)$ 点有奶牛，在 $b(b_x,b_t)$ 有苹果 $(a_t\le b_t)$，$a$ 可以借助 $b$ 的充要条件为：
$$
a_x-(b_t-a_t)\le b_x\le a_x+(b_t-a_t)\\
\Downarrow\\
\begin{cases}
a_x+a_t\le b_x+b_t\\
a_x-a_t\ge b_x-b_t
\end{cases}
$$
第二个式子直接 $x-t$ 从小到大的顺序搞定（注意如果值相同 $t$ 大的优先），这样只要每个数匹配在它之前的点就都是合法的，接下来只用满足第一个式子。

考虑两头奶牛 $a_1,a_2(a_x-a_t<b_x-b_t)$ 一起匹配苹果，我们会让 $a_1$ **优先匹配苹果中 $b_x+b_t$ 最小的**，把剩下的留给 $a_2$。

为什么这样是对的呢？

显然 $b_x+b_t$ 越小越难被匹配，那么如果可以被匹配，直接匹配一定最优。

而且如果 $a_1$ 与 $a_2$ 都能够匹配同一个 $b$，让他们任何一个去匹配是相同的。

那么就这样被简单地证明了。

实际操作中可以用 `multiset` 来支持查询比 $a_x+a_t$ 大的数即可。

### 代码

```cpp
// Author:A weak man named EricQian
#include<bits/stdc++.h>
using namespace std;
#define infll 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define Maxn 200005
#define pb push_back
#define pa pair<int,int>
#define fi first
#define se second
typedef long long ll;
inline int rd()
{
	int x=0;
	char ch,t=0;
	while(!isdigit(ch = getchar())) t|=ch=='-';
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x=t?-x:x;
}
inline ll maxll(ll x,ll y){ return x>y?x:y; }
inline ll minll(ll x,ll y){ return x<y?x:y; }
inline ll absll(ll x){ return x>0ll?x:-x; }
inline ll gcd(ll x,ll y){ return (y==0)?x:gcd(y,x%y); }
int m,ans;
struct OPT
{
	int opt,t,x,num;
	bool friend operator < (OPT a,OPT b)
		{ return (a.x-a.t!=b.x-b.t)?(a.x-a.t<b.x-b.t):(a.x>b.x); }
}c[Maxn];
multiset<pa> Left;
int main()
{
	//ios::sync_with_stdio(false); cin.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	m=rd();
	for(int i=1;i<=m;i++) c[i]=(OPT){rd(),rd(),rd(),rd()};
	sort(c+1,c+m+1);
	for(int i=1;i<=m;i++)
	{
		if(c[i].opt==1)
		{
			auto it=Left.lower_bound(pa(c[i].x+c[i].t,0));
			while(c[i].num && it!=Left.end())
			{
				int tmp=min(it->se,c[i].num);
				c[i].num-=tmp,ans+=tmp;
				if(tmp==(it->se)) Left.erase(it++);
				else Left.insert(pa(it->fi,(it->se)-tmp)),Left.erase(it);
			}
		}
		else Left.insert(pa(c[i].x+c[i].t,c[i].num));
	}
	printf("%d\n",ans);
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
```

---

## 作者：huhangqi (赞：0)

先考虑推导式子。

设我们选择的奶牛为 $i$,选择的苹果是 $j$。

那么可以得到式子：

$$
|x_i-x_j|\le t_j-t_i
$$

直接拆掉绝对值，因为绝对值会取较大的值，所以不需要考虑二者大小关系的影响，然后即可推得两式：

$$
x_i+t_i\le t_j+x_j
$$

$$
t_i-x_i\le t_j-x_j
$$

仅在满足以上条件时可以拿到苹果。

那么此时我们就有了一个统一的衡量标准，经典的贪心思路是，对于每一个奶牛，我们去选择可以拿到，且最不容易被其它奶牛拿到的苹果。

因为苹果和奶牛在本质上没有区别，所以也可以让苹果去找奶牛。

我们将其中的一个量设置为一维，通过排序解决，另外一个量设为第二维，可以二分答案，为了方便插入删除以及二分查找，比较容易想到用一个 set 维护第二维。

那么我们就贪心的去选择接的苹果即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
struct P{
	int op,x,y,n;
}a[200005];
bool cmp(P a,P b){
	if(a.x!=b.x)return a.x>b.x;
	return a.y>b.y;
}
set<pair<int,int>> s;
signed main(){
	cin>>n;
	for(int i=1,t,x;i<=n;i++){
		cin>>a[i].op>>t>>x>>a[i].n;
		a[i].x=t+x,a[i].y=t-x;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].op==2)s.insert({a[i].y,i});
		else {
			while(a[i].n){
				auto it=s.lower_bound({a[i].y,0});
				if(s.end()==it)break;
				pair<int,int> tmp=*it;
				int id=tmp.second;
				int res=min(a[id].n,a[i].n);
				a[id].n-=res;
				a[i].n-=res;
				ans+=res;
				if(!a[id].n)s.erase(it);
			}
		}
	}
	cout<<ans;
	return 0;
}

``````

---

## 作者：Mirasycle (赞：0)

列出奶牛可以接到苹果的条件，假如一头 $(t,x)$ 的奶牛可以接到 $(t',x')$ 掉落的苹果必须满足 $ \lvert x-x' \rvert \le t'-t$。得到 $ t+x \le t'+x' $ 且 $t-x \le t'-x'$。注意有这两个式子后必然满足 $t \le t'$。

然后似乎不太好去分配奶牛的去接什么苹果。此时我们不妨大胆地贪心匹配。将约束条件画在二维平面中，发现每个奶牛能接到的范围就是一个倾斜的正方形。斜着不太好看，我们可以先旋转 $45$ 度，发现越往左下角的正方形包括的区域越大肯定是更优的，于是我们可以贪心将右上角的不优的矩形去先匹配靠右上角的苹果，也就是横纵坐标之和更大的苹果。我们再旋转回来，对应的也就是纵坐标更大的苹果应该被靠上的矩形先匹配到。于是用一个 set 维护即可。

---

