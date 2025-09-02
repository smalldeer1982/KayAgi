# Gripping Story

## 题目描述

One day Qwerty the Ranger witnessed two transport ships collide with each other. As a result, all contents of their cargo holds scattered around the space. And now Qwerty wants to pick as many lost items as possible to sell them later.

The thing is, both ships had lots of new gravitational grippers, transported to sale. A gripper is a device that can be installed on a spaceship and than draw items in space to itself ("grip") and transport them to the ship's cargo hold.

Overall the crashed ships lost $ n $ gravitational grippers: the $ i $ -th gripper is located at a point with coordinates $ (x_{i},y_{i}) $ . Each gripper has two features — $ p_{i} $ (the power) and $ r_{i} $ (the action radius) and can grip any items with mass of no more than $ p_{i} $ at distance no more than $ r_{i} $ . A gripper itself is an item, too and it has its mass of $ m_{i} $ .

Qwerty's ship is located at point $ (x,y) $ and has an old magnetic gripper installed, its characteristics are $ p $ and $ r $ . There are no other grippers in the ship's cargo holds.

Find the largest number of grippers Qwerty can get hold of. As he picks the items, he can arbitrarily install any gripper in the cargo hold of the ship, including the gripper he has just picked. At any moment of time the ship can have only one active gripper installed. We consider all items and the Qwerty's ship immobile when the ranger picks the items, except for when the gripper moves an item — then the item moves to the cargo holds and the ship still remains immobile. We can assume that the ship's cargo holds have enough room for all grippers. Qwerty can use any gripper he finds or the initial gripper an arbitrary number of times.

## 说明/提示

In the first sample you should get the second gripper, then use the second gripper to get the first one, then use the first gripper to get the fourth one. You cannot get neither the third gripper as it is too heavy, nor the fifth one as it is too far away.

## 样例 #1

### 输入

```
0 0 5 10 5
5 4 7 11 5
-7 1 4 7 8
0 2 13 5 6
2 -3 9 3 4
13 5 1 9 9
```

### 输出

```
3
```

# 题解

## 作者：AbsMatt (赞：1)

### [题目传送器](https://www.luogu.com.cn/problem/CF198E)

### [更爽的阅读体验](https://yaohaoyou.github.io/post/CF198E-solution/)

### CF 2400

## 前言

好题啊，但是为什么题解区没有单 log 做法。

[双倍经验](https://www.luogu.com.cn/problem/P10590)

## 做法

首先不难想出 $O(n^2)$ 的 bfs 做法。

思考一个机械臂能抓住哪些新的机械臂，即 $dis(i)\le r \land m_i \le p$ 的所有 $i$，这是一个较为明显的二维偏序，应该可以直接使用线段树套线段树优化建图解决（不知道会不会 MLE）。

回顾[弹跳](https://www.luogu.com.cn/problem/P5471)的 Trick，对于一个点向一个坐标轴中的左下角矩阵连边，可以先使用排序后离线一维，再使用数据结构维护剩下一维。

具体的，对每个机械臂按照 $m_i$ 排序，将 $dis(i)$ 离散化后挂在线段树上。线段树上每个节点记录一个``queue``表示 $dis_i$ 在当前区间的 $i$ 集合，由于提前按照 $m_i$ 排序了，所以当前队列中的 $m_i$ 是单调不减的。利用这一条性质就可以类似于双指针，每次队首加入 bfs 后退队，如果当前队首不满足 $m_i \le p$ 则后面的必然也不满足。

实现时``queue``的空间常数非常大，会直接 MLE，可以使用``vector``并记录队头的位置。每个机械臂会在线段树中被加入 $O(\log_2n)$ 次，也只会被删除 $O(\log_2n)$ 次，所以时空复杂度都是 $O(n\times \log_2n)$。

[AC Code](https://codeforces.com/contest/198/submission/291406094)

---

## 作者：CNS_5t0_0r2 (赞：1)

没有人用分块做法？我来交一篇。

首先考虑暴力做法，初始只有一个机械臂，我们暴力的把所有能抓过来的机械臂都抓过来，再分别尝试抓过来的机械臂。

这显然是一个 bfs 的过程，复杂度为 $O(n ^ 2)$，无法通过题目。

分块本身就是一个优雅的暴力，所以我们考虑本题使用分块优化。

不妨先取块长为 $\sqrt{n}$。

我们接下来分析：暴力有什么问题？

我们发现，暴力法每次都要把所有机械臂遍历一遍，无论其是否被抓走，这导致很多已经被抓走的机械臂被重复遍历了很多次，考虑从这个角度优化。

可以发现这么一个性质：设第 $i$ 个机械臂到 $(x,y)$ 的距离为 $dis_i$，如果 $dis$ 和 $m$ 都是单调不减的，我们显然可以维护一个指针，每次向右移动指针抓取机械臂直到不能抓为止。

在本例中，指针是不用向左移的，即每个机械臂都只会遍历一次，所以总复杂度是 $O(n)$ 的。

~~但出题人会这么良心吗？不会的！~~

不过，这给我们一个启发：我们可以让每个块内都有类似的性质，即我们对每个块维护一个上例中的指针，使这个指针不用左移。

上例中 $dis$ 和 $m$ 是严格单调的，但是我们无法通过排序使 $dis$ 和 $m$ 都单调。

本题关键来了：

## 我们可以通过“整体” $m$ 单调，“块内” $dis$ 单调！

形式化来讲，记 $belong_i$ 为第 $i$ 个机械臂所在块的编号，对于任意 $i < j$，若 $belong_i < belong_j$，则 $m_i \leq m_j$；若 $belong_i = belong_j$，则 $dis_i \leq dis_j$。

这个思路巧妙在哪？

分块遵循的都是整体维护，块内暴力原则，那本题中的整体是什么？

很显然，有了整体的 $m$ 单调，我们可以确定我们需要查询哪些块，不查询哪些块。

具体来说，我们可以对每个块维护一个 $Max$ 表示最重的机械臂重量。我们从左往右暴力查找（也可以二分，但只起到优化常数的效果），当查找到第一个 $Max_k > p$ 时，说明 $1 \sim k - 1$ 块中所有机械臂的 $m$ 都满足要求，第 $k + 1 \sim n$ 块中所有机械臂的 $m$ 都不满足要求，第 $k$ 块无法确定，需要暴力 $O(\sqrt{n})$ 查询。

对于前 $k - 1$ 块，就可以用上述移动指针的方式查询，每个块均摊是 $O(1)$ 的，所以这部分查询复杂度也是 $O(\sqrt{n})$ 的。

综上，我们得到了一个 $O(n\sqrt{n})$ 的算法。

很奇怪的是我的代码中常量 $N$ 的大小需要比题目中的 $n$ 开大 $4$ 倍，否则会 RE，有大佬可以解释的欢迎留言！

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
const int N = 1e6 + 9,SqrtN = 1e6 + 9;
int n;
struct Data{
    int x,y,m,p;
	ll r,dis;//dis存的是真实距离的平方，所以将读入的 r 也全部平方
} a[N];
struct block{//存储块的结构体
    int l,r;//块的左右边界，注意本代码中直接将 l 当作文中提到的指针使用
} b[SqrtN];
int belong[N];
int block_cnt,block_len;
int Max[SqrtN];
bool vis[N];
ll sq(int k){
    return (ll)k * k;
}
ll dist(Data m1,Data m2){
    int x1 = m1.x,y1 = m1.y,x2 = m2.x,y2 = m2.y;
    return sq(x1 - x2) + sq(y1 - y2);
}
bool cmp1(Data m1,Data m2){
    return m1.m < m2.m;
}
bool cmp2(Data m1,Data m2){
    return m1.dis < m2.dis;
}
void block_sort(int block_id){//块内按dis排序
    int l = b[block_id].l,r = b[block_id].r;
    sort(a + l,a + r + 1,cmp2);
}
void build_block(){
    block_cnt = block_len = (int)sqrt(n);
    for(int i = 1;i <= block_cnt;i++){
        b[i].l = b[i - 1].r + 1;
        b[i].r = block_len * i;
    }
    b[block_cnt].r = n;
    for(int i = 1;i <= block_cnt;i++){
        block_sort(i);
        for(int j = b[i].l;j <= b[i].r;j++){
            Max[i] = max(Max[i],a[j].m);
            belong[j] = i;
        }
    }
}
queue<Data>q;
int ans;
void attract(Data u){
    int pos = n + 1;
    for(int i = 1;i <= block_cnt;i++)
        if(Max[i] > u.p){
            pos = i;
            break;
        }
    for(int i = 1;i <= pos - 1;i++){
        while(b[i].l <= b[i].r && dist(a[0],a[b[i].l]) <= u.r){
            int j = b[i].l;
            if(!vis[j]){            
                ans++;
                q.push(a[j]);
                vis[j] = true;//这个加不加无所谓
            }
            b[i].l++;//移动指针
        }
    }
    if(pos == n + 1)
        return;
    for(int i = b[pos].l;i <= b[pos].r;i++)
        if(a[i].m <= u.p && dist(a[0],a[i]) <= u.r && !vis[i]){
            ans++;
            vis[i] = true;//暴力取走的必须标记，否则可能会在移动指针时被重复计算
            q.push(a[i]);
        }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> a[0].x >> a[0].y >> a[0].p >> a[0].r >> n;
    for(int i = 1;i <= n;i++)
        cin >> a[i].x >> a[i].y >> a[i].m >> a[i].p >> a[i].r;
    for(int i = 0;i <= n;i++){
        a[i].r = sq(a[i].r);
        a[i].dis = dist(a[0],a[i]);
    }
    sort(a + 1,a + n + 1,cmp1);//整体满足m单调
    build_block();
    vis[0] = true;
    q.push(a[0]);
    while(!q.empty() && ans < n){
        Data u = q.front();
        q.pop();
        attract(u);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Lvlinxi2010 (赞：1)

可以发现，坐标并没有用，有用的是和 $(x,y)$ 的直线距离，记为每个机械臂的距离 $dis$。

我们可以很容易写出一个 $O(n^2)$ 的 bfs，每次尝试用捕获的机械臂捕获新的机械臂。

但 $n\le2.5\times10^5$，很明显无法通过此题，考虑优化。

可以发现一个机械臂 $j$ 可以被机械臂 $i$ 捕获当且仅当同时满足 $dis_j\le r_i$，$m_j\le p_i$，是一个二维偏序。

考虑优化拓展时寻找可拓展机械臂的复杂度。我们先按 $dis$ 排序消掉一维，然后分块，块内按照质量排序，记录块内最大质量 $mx_i$。

记当前拓展的机械臂的机械臂编号为 $u$。当 $r_u\ge mx_i$ 的时候，整个块都满足 $dis$ 的要求，块内起始端点 $L_i$ 单调右移（因为如果前面 $i$ 的不满足要求，后面的 $j$ 满足 $m_j\ge m_i$，一定不满足要求），均摊 $O(1)$，找到 $r_u<mx_i$ 的第一个块，暴力 $O(\sqrt{n})$ 查询这个块中 $dis_i\le r_u$ 且 $m_i\le p_u$ 的机械臂的数量，并将被捕获的机械臂标记（不然在后续拓展中可能会重复计算），总复杂度 $O(n\sqrt{n})$。

另：数组一定要开 $10^6$，不然会 TLE 或者 RE。双倍经验：[P10590](https://www.luogu.com.cn/problem/P10590)

附上代码：

```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(ll i=(a);i<=(b);i++)
#define FR(i,a,b) for(ll i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const ll MAXN = 1e6 + 10;
const ll MR = 1e3 + 10;
//按距离排序，分块，块内按质量排序 
struct node{
	ll d,m,p,r;
}a[MAXN];
ll n,nx,ny,S,num=0,ans=0;
ll id[MAXN];
ll L[MR],R[MR],mx[MR];
bool vis[MAXN];
inline ll read(){
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}
bool cmp(node p,node q){
	return p.d<q.d;
}
bool cmp1(node p,node q){
	return p.m<q.m;
}
void init(){
	sort(a+1,a+n+1,cmp);
	S=sqrt(n),num=(n-1)/S+1;
	FL(i,1,n) id[i]=(i-1)/S+1,mx[id[i]]=max(mx[id[i]],a[i].d);
	FL(i,1,num) L[i]=(i-1)*S+1,R[i]=i*S;
	R[num]=n;
	FL(i,1,num) sort(a+L[i],a+R[i]+1,cmp1); 
}
signed main(){
	nx=read(),ny=read(),a[0].p=read(),a[0].r=read(),n=read();
	a[0].r*=a[0].r;
	FL(i,1,n){
		ll x,y;
		x=read(),y=read(),a[i].m=read(),a[i].p=read(),a[i].r=read();
		a[i].r*=a[i].r;
		a[i].d=(nx-x)*(nx-x)+(ny-y)*(ny-y);
	}
	init();
	queue<ll>q;
	q.push(0);
	while(!q.empty()){
		ll u=q.front();
		q.pop();
		FL(i,1,num){
			if(mx[i]>a[u].r){
				FL(j,L[i],R[i]){
					if(!vis[j]&&a[j].d<=a[u].r&&a[j].m<=a[u].p){
						vis[j]=1,q.push(j),ans++;
					}
				}
				break;
			}
			while(L[i]<=R[i]&&a[L[i]].m<=a[u].p){
				if(!vis[L[i]]) q.push(L[i]),ans++;
				L[i]++;
			}
		}
	}
	printf("%lld\n",ans);
}
```

---

## 作者：forever_nope (赞：0)

题目：[P10590 磁力块](https://www.luogu.com.cn/problem/P10590)，[CF198E Gripping Story](https://www.luogu.com.cn/problem/CF198E)。

~~说句闲话：这道题收录到了一本通里面啊（样例都不变的）。~~

贪心的考虑，我们希望对于已有的每一个磁石都吸引一遍。

那么直接类似 BFS 的做，复杂度是 $\mathcal O(n^2)$ 的。

考虑 BFS + 分块。

我们记 $d_i$ 表示第 $i$ 个磁石到 $(x_0,y_0)$ 的距离。

先将所有的点按照到 $d_i$ 升序排序，按照 $\sqrt n$ 大小分块。

块内再开一个数组，将所有的点按照质量升序排序。

分别考虑每一个磁石 $R,P$，将没有被吸引过的磁石的块分为以下三类：

1. 这一块的 $d_i$ 全都 $\le R$。

2. 这一块的 $d_i$ 全都 $>R$。

3. 这一块的 $d_i$ 包括了 $\le,> R$ 的。

考虑如何处理：

+ 对于第一类，我们直接暴力从头遍历直到 $m_i>P$。

+ 对于第二类，我们不管。

+ 对于第三类，我们暴力的遍历，可以吸引的加入并标记为删除。

考虑复杂度：

+ 对于第一类，每个点最多被遍历一次（然后就入队了），因此是 $\mathcal O(n)$ 的。

+ 对于第三类，每次最多处理 $1$ 个这样的块，每次复杂度是 $\mathcal O(\sqrt n)$ 的。

因此，时间复杂度为 $\mathcal O(n\sqrt n)$。

实现细节：

+ 我们并不需要实际删除节点，可以打标记表示删除。

+ 代码：

```cpp
#ifndef M_DEBUG
#define NDEBUG 1
#define FAST_IO 1
#define D(x) ({ void(0); })
#else
#define D(x) ({ auto t = (x); cerr << "| DEBUG #" << __LINE__ << " IN " << __FUNCTION__ << "() \t| \t" << #x << " = \t[" << t << "]\n"; void(0); })
#endif

#include <bits/stdc++.h>

#ifdef FAST_IO
#define endl "\n"
#endif

using namespace std;

// -----------------------------------------------------------------------------

using ll = long long;

constexpr int N = 3e5 + 10;

namespace solev {
    int n;
    int p0, r0;
    int x0, y0;

    struct query {
        int p;
        ll r2;
        query() = default;
        query(int p, int r): p(p), r2(1ll * r * r) {}
    };

    // -------------------------------------------------------------------------

    struct magic {
        int m, p, r;
        ll dis2;
        magic() = default;
        magic(int x, int y, int m, int p, int r): m(m), p(p), r(r), dis2(1ll * (x - x0) * (x - x0) + 1ll * (y - y0) * (y - y0)) {}
    } a[N];

    bool cmp_d(const magic &a, const magic &b) {
        return a.dis2 < b.dis2;
    }

    bool cmp_m(const magic &a, const magic &b) {
        return a.m < b.m;
    }

    int block, cnt;
    int belong[N];
    int L[N], R[N];
    ll mind[N], maxd[N];

    int beg[N];

    void init() {
        sort(a + 1, a + n + 1, cmp_d);
        block = sqrt(n);
        for (int i = 1; i <= n; ++i)
            belong[i] = (i - 1) / block + 1;
        cnt = (n - 1) / block + 1;
        for (int i = 1; i <= cnt; ++i) {
            L[i] = (i - 1) * block + 1;
            R[i] = min(L[i] + block - 1, n);
            beg[i] = L[i];
            mind[i] = a[L[i]].dis2;
            maxd[i] = a[R[i]].dis2;
            sort(a + L[i], a + R[i] + 1, cmp_m);
        }
        R[cnt] = n;
    }

    queue<query> q;

    bool del[N];

    void m_push(const query &u) {
        int p = u.p;
        ll r2 = u.r2;
        for (int j = 1; j <= cnt; ++j) {
            if (mind[j] > r2)
                break;
            if (maxd[j] <= r2) {
                for (int i = beg[j]; i <= R[j]; ++i) {
                    if (del[i]) continue;
                    if (a[i].m > p) break;
                    q.emplace(a[i].p, a[i].r);
                    beg[j] = i + 1;
                }
            }
            else {
                for (int i = beg[j]; i <= R[j]; ++i) {
                    if (del[i]) continue;
                    if (a[i].m > p) continue;
                    if (a[i].dis2 > r2) continue;
                    q.emplace(a[i].p, a[i].r);
                    del[i] = true;
                }
            }
        }
    }

    // -------------------------------------------------------------------------

    int Main() {
        cin >> x0 >> y0 >> p0 >> r0 >> n;
        for (int i = 1; i <= n; ++i) {
            int x, y, m, p, r;
            cin >> x >> y >> m >> p >> r;
            a[i] = magic(x, y, m, p, r);
        }
        init();
        q.emplace(p0, r0);
        int ans = 0;
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            m_push(u);
            ++ans;
        }
        return ans - 1;
    }
}

// -----------------------------------------------------------------------------

signed main() {
    #ifdef FAST_IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    #endif
    cout << solev::Main() << endl;
    return 0;
}
```

END.

---

## 作者：Sampson_YW (赞：0)

三年前见到这题的时候完全不会，看题解都看不明白。现在看这题觉得非常简单啊。不过现在的我跟三年前的我比起来，只是多会了几个数据结构和常见套路而已吧，就连思维都僵化了。

不说多了，讲下这题咋做。

由于船是固定的，那么每个机械臂需要的距离都是固定的，不妨设为 $d_i$。

假如我们现在有个机械臂力量为 $p$，长度为 $r$，那么它可以拿起第 $i$ 个机械臂，当且仅当 $d_i\leq r$ 且 $m_i\leq p$。假如第 $i$ 个机械臂能拿到第 $j$ 个机械臂，那么就连一条 $i\to j$ 的有向边，然后从起始的机械臂 BFS 一遍就可以得到所有能拿到的机械臂。

这样做是 $O(n^2)$ 的。这个 BFS 做法并不需要建边，假设当前 BFS 到了 $x$，那么只要枚举所有**现在还没有被拿到**的机械臂 $y$ 判断一下 $x$ 是否能拿到 $y$ 就行。现在只需要优化找这个 $y$ 的过程。

考虑一个套路：每次都找到一个 $y$，并将这个 $y$ 删除，一直到没有符合要求的 $y$ 才停止。

容易发现判断条件是一个二维偏序的形式。由于机械臂的排列顺序不会影响答案，那么不妨先将机械臂按照 $d_i$ 从小到大排序，那么满足 $d_i\leq r$ 的机械臂就是一段前缀区间，这样就可以利用线段树解决了。

然后就是要满足第二个 $m_i\leq p$ 的条件。由于 $y$ 的取出顺序也不会影响答案，那么只需要每次取出区间中 $m_i$ 最小的机械臂就行了。于是这个线段树只需要维护区间最小值。

不过我的做法是对线段树上每个节点对区间内的所有机械臂维护一个 $m_i$ 单调不增的栈，记录机械臂的编号。查询到一个节点上时，如果栈顶已经被拿过了就弹出。如果当前栈顶的 $m_i$ 满足条件就取它，否则这个区间内的机械臂都拿不走。

[code](https://codeforces.com/contest/198/submission/235856889)

---

