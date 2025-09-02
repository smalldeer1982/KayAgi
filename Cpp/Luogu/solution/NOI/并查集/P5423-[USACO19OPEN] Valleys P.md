# [USACO19OPEN] Valleys P

## 题目描述

Bessie 喜欢观光，而今天她正在寻找景色优美的山谷。

她感兴趣的是一个 $ N \times N $ 的方阵，其中每个格子都有一个高度。所有在此正方形方阵之外的格子的高度可以被看作是无限大。

山谷指的是一块连续、不含洞的一块区域，并且每个相邻的包围该区域的格子都高于这块区域中的所有格子。

更形式化地说：

* 一组格子被称作是“沿边相邻的”，如果可以从其中任意一个格子出发，经过一些沿上、下、左、右方向的移动，到达其中所有其他格子。
* 一组格子被称作是“沿点相邻的”，如果可以从其中任意一个格子出发，经过一些沿上、下、左、右、对角线方向的移动，到达其中所有其他格子。
* 一个“区域”指的是一组非空并且沿边相邻的格子。
* 一个区域被称作是“有洞的”，如果这个区域的补集（包括在 $ N \times N $ 方阵之外的无限高格子）不是沿点相邻的。
* 区域的“边界”指的是所有与该区域内的某个格子正交相邻（上、下、左、右），但本身不在该区域内的格子。
* 一个“山谷”指的是某个非有洞区域，满足区域内的任意格子的高度低于该区域边界上任意格子的高度。

Bessie 的目标是求出所有山谷的大小之和。

### 一些例子

这是一个区域：

```
oo.
ooo
..o
```

这不是一个区域（中间的格子和右下角的格子不沿边相邻）：

```
oo.
oo.
..o
```

这是一个非有洞区域：

```
ooo
o..
o..
```

这是一个有洞的区域（“甜甜圈”中间的格子与区域外的格子不沿点相邻）：

```
ooo
o.o
ooo
```

这是另一个非有洞区域（中间的格子与右下角的格子沿点相邻）：

```
ooo
o.o
oo.
```

## 说明/提示

在这个例子中，有三个大小为1的山谷：

```
o.o
...
o..
```

一个大小为2的山谷：

```
...
...
oo.
```

一个大小为3的山谷：

```
ooo
...
...
```

一个大小为6的山谷：

```
ooo
o..
oo.
```

一个大小为7的山谷：

```
ooo
o.o
oo.
```

以及一个大小为9的山谷：

```
ooo
ooo
ooo
```

所以，答案为1 + 1 + 1 + 2 + 3 + 6 + 7 + 9 = 30。

### 子任务

对于至少19%的测试数据， $ N \leq 100 $ 。

## 样例 #1

### 输入

```
3
1 10 2
20 100 30
3 11 50```

### 输出

```
30```

# 题解

## 作者：picha (赞：6)

[P5423 [USACO19OPEN]Valleys P](https://www.luogu.com.cn/problem/P5423)

作为一个蒟蒻，自己的做法可能会有些地方比较傻，欢迎大佬们指出并改进~~并嘲讽我这个蒟蒻~~。

# Solution

首先，容易想到将所有的方格按照 $b[i][j]$ 从小到大进行排序，并依次遍历。

为方便叙述，将满足区域内的任意格子的高度低于该区域边界上任意格子的高度的区域叫做“弱山谷”。

设遍历到的方格是 $(i,j)$ ，将 $(i,j)$ 和与它**有边相连**的方格中，$b$ 值比 $b[i][j]$ 小的合并到同一个集合内。

容易发现每次合并后的集合都是弱山谷。

所以只用判断该区域是否有洞即可。

首先计算将 $(i,j)$ 加入弱山谷后，该弱山谷会增加多少个洞。

维护另一个并查集，将里面每一个方格都和与它**有点相连**的方格连边（这里的方格包括在 $N \times N$ 方阵之外的无限高格子）。

将并查集中这个方格所连的边删去后，设与它**有点相连**的方格存在于 $x$ 个不同的连通块中。

显然，这个问题的答案就是 $\max(0, x - 1)$。

但是从并查集中删边不好维护，考虑使用可撤销并查集。

按照把边删去的顺序反过来的顺序加边，删边直接撤销上一次操作即可。

再考虑将 $(i,j)$ 加入弱山谷后，该弱山谷是否会减少洞。

维护 $f[i][j]$ 表示与 $(i,j)$ **有点相连**的方格中，已经加入弱山谷的数量。

显然，如果 $f[i][j] = 8$，那么将 $(i,j)$ 加入弱山谷后，该弱山谷的洞的数量会减少 $1$。

否则就不会减少。

每次操作后判断当前的弱山谷是否有洞，没有洞的话就加入答案。

说的可能有点难以理解，请大佬们原谅，把我的垃圾代码贴到下面。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 750;
const ll N = maxn + 10;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
ll n, m, l, cnt, ans, a[N][N], f[N][N], fa[N * N], g[N * N], sz[N * N], fa1[N * N], sz1[N * N];
bool c[N][N];
ll dx[5] = {0, 1, -1, 0, 0};
ll dy[5] = {0, 0, 0, 1, -1};
struct nde{
    ll x, y, w;
}b[N * N];
bool cmp(nde p, nde q) {
    return p.w < q.w;
}
ll get_fa(ll x){
    if (fa[x] == x) {
        return x;
    }
    else {
        fa[x] = get_fa(fa[x]);
        return fa[x];
    }
}
void mrge(ll x, ll y) {
    ll p = get_fa(x), q = get_fa(y);
    if (p == q) {
        return;
    }
    fa[q] = p;
    g[p] += g[q];
    g[q] = 0;
    sz[p] += sz[q];
    sz[q] = 0;
}
ll slve(ll x, ll y) {
    return (x - 1) * n + y;
}
struct nde1 {
    ll x, y, u, v;
}B[N * N * 8];
ll slve1(ll x, ll y) {
    return x * (n + 2) + y + 1;
}
ll get_fa1(ll x) {
    if (fa1[x] == x) {
        return x;
    }
    else {
        return get_fa1(fa1[x]);
    }
}
void mrge1(ll x, ll y, ll u, ll v) {
    ll p = get_fa1(x), q = get_fa1(y);
    if (p == q) {
        return;
    }
    if (sz1[p] < sz1[q]) {
        swap(p, q);
    }
    ++cnt;
    B[cnt].x = q;
    B[cnt].y = fa1[q];
    B[cnt].u = u;
    B[cnt].v = v;
    fa1[q] = p;
    sz1[p] += sz1[q];
    sz1[q] = 0;
}
void re_mrge1() {
    fa1[B[cnt].x] = B[cnt].y;
    --cnt;
}
set<ll> st;
int main() {
    scanf("%lld", &n);
    l = 0;
    for (ll i = 1; i <= n; ++i) {
        for (ll j = 1; j <= n; ++j) {
            scanf("%lld", &a[i][j]);
            ++l;
            b[l].x = i;
            b[l].y = j;
            b[l].w = a[i][j];
        }
    }
    for (ll i = 1; i <= n; ++i) {
        for (ll j = 1; j <= n; ++j) {
            f[i][j] = 0;
            c[i][j] = 0;
        }
    }
    for (ll i = 1; i <= l; ++i) {
        fa[i] = i;
        g[i] = 0;
        sz[i] = 1;
    }
    for (ll i = 0; i <= n + 1; ++i) {
        a[0][i] = INF;
        a[n + 1][i] = INF;
    }
    for (ll i = 0; i <= n + 1; ++i) {
        a[i][0] = INF;
        a[i][n + 1] = INF;
    }
    // 预处理可撤销并查集
    for (ll i = 1; i <= (n + 2) * (n + 2); ++i) {
        fa1[i] = i;
        sz1[i] = 1;
    }
    for (ll i = 0; i <= n; ++i) {
        mrge1(slve1(0, i), slve1(0, i + 1), 0, 0);
        mrge1(slve1(n + 1, i), slve1(n + 1, i + 1), 0, 0);
    }
    for (ll i = 0; i <= n; ++i) {
        mrge1(slve1(i, 0), slve1(i + 1, 0), 0, 0);
        mrge1(slve1(i, n + 1), slve1(i + 1, n + 1), 0, 0);
    }
    sort(b + 1, b + l + 1, cmp);
    cnt = 0;
    for (ll p = l; p >= 1; --p) {
        ll x = b[p].x, y = b[p].y, w = b[p].w;
        for (ll i = -1; i <= 1; ++i) {
            for (ll j = -1; j <= 1; ++j) {
                ll xx = x + i, yy = y + j;
                if (!(xx == x && yy == y)) {
                    if (a[xx][yy] > a[x][y]) {
                        mrge1(slve1(x, y), slve1(xx, yy), x, y);
                    }
                }
            }
        }
    }
    ans = 0;
    for (ll p = 1; p <= l; ++p) {
        ll x = b[p].x, y = b[p].y, w = b[p].w;
        // 将该方格和与它有边相连的且高度小于它的合并到同一个集合
        for (ll i = 1; i <= 4; ++i) {
            ll xx = x + dx[i], yy = y + dy[i];
            if (xx >= 1 && xx <= n && yy >= 1 && yy <= n) {
                if (a[xx][yy] < a[x][y]) {
                    mrge(slve(x, y), slve(xx, yy));
                }
            }
        }
        ll u = get_fa(slve(x, y));
        // 删除洞
        if (f[x][y] >= 8) {
            --g[u];
        }
        // 更新f值
        f[x][y] = 0;
        c[x][y] = 1;
        for (ll i = -1; i <= 1; ++i) {
            for (ll j = -1; j <= 1; ++j) {
                ll xx = x + i, yy = y + j;
                if (xx >= 1 && xx <= n && yy >= 1 && yy <= n) {
                    if (!(xx == x && yy == y)) {
                        if (!c[xx][yy]) {
                            ++f[xx][yy];
                        }
                    }
                }
            }
        }
        // 统计增加了多少个洞
        while (cnt > 0 && (B[cnt].u == x && B[cnt].v == y)) {
            re_mrge1();
        }
        st.clear();
        for (ll i = -1; i <= 1; ++i) {
            for (ll j = -1; j <= 1; ++j) {
                ll xx = x + i, yy = y + j;
                if (!(xx == x && yy == y)) {
                    if (!c[xx][yy]) {
                        ll q = get_fa1(slve1(xx, yy));
                        st.insert(q);
                    }
                }
            }
        }
        if (ll(st.size()) >= 1) {
            g[u] += (ll(st.size()) - 1);
        }
        if (g[u] == 0) {
            ans += sz[u];
        }
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：Aleph1022 (赞：4)

现有的那篇题解看起来有点费劲，这里给出一个更直接的做法。

如果不需要没有洞，那我们从小到大加点并用并查集维护连通块大小即可。因此，只需要考虑如何判断洞是否存在。

我们注意到洞的判定是八连通的。考虑以每个格子为点，连边，变成平面图。则洞就是一个在图形内部的区域。  
那么我们根据欧拉公式 $V-E+F=2$，可得 $F = E - V + 2$。而这样得到的 $F$ 实际上包括外围的一个区域和所有四个已访问点构成的正方形。额外维护之即可。

时间复杂度 $O(N^2 \alpha(N^2))$。

---

## 作者：dAniel_lele (赞：2)

首先我们先从小到大加入点，这样每次加入之后这个可能有洞的山谷就满足小于周围的条件了。

接下来考虑一个连通块非有洞的条件如何处理。对于一个平面图，显然连通块数为 $V-E+C$，即点数减去边数加上环数。我们已经知道他们形成一个连通块，于是 $V-E+C=1$。非有洞等价于所有环都是形如 $(i,j),(i+1,j),(i,j+1),(i+1,j+1)$ 的，否则其他环一定会包含空白点，也就是有洞。所以我们考虑维护 $V,E$ 以及形如上面所述的环，如果算出来连通块数为 $1$ 那么就是非有洞的，合法的山谷，否则不合法。

总复杂度 $O(n^2\log n)$，其中 $\log$ 来自并查集。

```cpp
#include <bits/stdc++.h>
#define int long long
#define s(i,j) ((i-1)*n+j)
#define mid ((l+r)>>1)
#define add(i,j) ((i+j)>=mod?i+j-mod:i+j)
using namespace std;
int f[1000005],siz[1000005],tot[1000005],a[755][755];
vector<pair<int,pair<int,int>>> vc;
int find(int i){
	return f[i]==i?f[i]:f[i]=find(f[i]);
}
signed main(){
	int n,ans=0; cin>>n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j],vc.push_back(make_pair(a[i][j],make_pair(i,j)));
	sort(vc.begin(),vc.end());
	for(auto v:vc){
		int i=v.second.first,j=v.second.second;
		f[s(i,j)]=s(i,j),siz[s(i,j)]=tot[s(i,j)]=1;
		if(i>1&&f[s(i-1,j)]&&find(s(i-1,j))!=s(i,j)) tot[s(i,j)]+=tot[find(s(i-1,j))],siz[s(i,j)]+=siz[find(s(i-1,j))]-1,f[find(s(i-1,j))]=s(i,j); else if(i>1&&f[s(i-1,j)]) siz[s(i,j)]--;
		if(i<n&&f[s(i+1,j)]&&find(s(i+1,j))!=s(i,j)) tot[s(i,j)]+=tot[find(s(i+1,j))],siz[s(i,j)]+=siz[find(s(i+1,j))]-1,f[find(s(i+1,j))]=s(i,j); else if(i<n&&f[s(i+1,j)]) siz[s(i,j)]--;
		if(j>1&&f[s(i,j-1)]&&find(s(i,j-1))!=s(i,j)) tot[s(i,j)]+=tot[find(s(i,j-1))],siz[s(i,j)]+=siz[find(s(i,j-1))]-1,f[find(s(i,j-1))]=s(i,j); else if(j>1&&f[s(i,j-1)]) siz[s(i,j)]--;
		if(j<n&&f[s(i,j+1)]&&find(s(i,j+1))!=s(i,j)) tot[s(i,j)]+=tot[find(s(i,j+1))],siz[s(i,j)]+=siz[find(s(i,j+1))]-1,f[find(s(i,j+1))]=s(i,j); else if(j<n&&f[s(i,j+1)]) siz[s(i,j)]--;
		if(i>1&&j>1&&f[s(i-1,j)]&&f[s(i,j-1)]&&f[s(i-1,j-1)]) siz[s(i,j)]++;
		if(i<n&&j>1&&f[s(i+1,j)]&&f[s(i,j-1)]&&f[s(i+1,j-1)]) siz[s(i,j)]++;
		if(i>1&&j<n&&f[s(i-1,j)]&&f[s(i,j+1)]&&f[s(i-1,j+1)]) siz[s(i,j)]++;
		if(i<n&&j<n&&f[s(i+1,j)]&&f[s(i,j+1)]&&f[s(i+1,j+1)]) siz[s(i,j)]++;
		if(siz[s(i,j)]==1){
			ans+=tot[s(i,j)];
		}
	}
	cout<<ans;
	return 0; 
}
```

---

## 作者：Talaodi (赞：2)

为了方便，我们把在山谷内的点称为黑点，其他点称为白点，黑连通块内部不与外部联通的白点为空腔。

性质一：以每个点为最大值的山谷如果存在是唯一的。因为从这个点开始，相邻的比他小的点一定选，比他大的点一定不选。

性质二：两个不同的黑连通块除了它们内部以外不会形成空腔。这是由题目性质决定的，我们在考虑黑连通块时是四联通，而白连通块是八联通。简单画一画可以发现无论这两个黑连通块挨得再近都一定可以被八联通的白点分开（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/bc90agai.png)

那么我们可以考虑从小到大加入黑点，发现加入了一个黑点后可能会把若干个黑连通块连起来。发现这样可以形成一棵树的结构，类似于克鲁斯卡尔重构树。

这棵树有什么用呢？由于我们要看白点是否全部联通，如果是加入黑点则需要删边，不好处理。而如果是加边，我们就可以用并查集动态维护连通块个数了。而这棵树就是我们要进行的加边顺序。

那么我们遍历到了一个点，我们把它变成白点，连一圈边，维护出了连通块个数。现在我们要以此考虑它的子树是不是合法的山谷，也就是没有空腔。

如果是全局没有空腔，条件显然是连通块个数为 $1$。但是其他子树内部也可能有空腔，会造成影响。但由于性质二，我们不需要考虑子树两两之间会形成空腔。

发现如果一棵子树内部没有空腔的话，把这棵子树全部变成白点后连通块个数是不变的。于是我们在进入一棵子树时记录下当前的连通块个数，递归完后判断一下和当前的是否相等即可。

除了并查集外复杂度 $O(N^2)$。

---

## 作者：shijiahao123 (赞：0)

[P5423 [USACO19OPEN] Valleys P](https://www.luogu.com.cn/problem/P5423)

#### 先整理一下题目。

一个 $n\times n$ 的矩阵，每一点有一个高度，所有高度都不相同。

山谷是一个不能有环，**低于两边**（所有高度都不相同），**沿上下左右四个方向相邻**的连通块。

未列入山谷（包括界外）的区域是**沿上下左右左上……八个方向相邻**的连通块。

一个洞是指“**伪**山谷”中八个方向都**无法**与外界连通的连通块。

求所有山谷的总长。

---
#### 再理一理思路。

山谷是低于两边的，那就按高度从小到大升序排序，一个个加入（类似于 kruskal 的思想）。

当一个点加进来，与四面与它小的点连接（并查集）。

最后把 size 相加……

不对，少了一个条件。

---
### 接下来是程序的重点——洞。

一个洞的产生：

1. 并查集时一个点与其相邻的两个或更多山谷（指那个点加入之前的山谷与伪山谷，下同）连起来时累积。（第一点比较好理解，是并查集的基本操作。）
1. 加入一个点时，因为在特殊的卡点。即一加入便可把山谷内分为多段。（第二点难理解。）

_以下高能且并不严谨，建议联系代码理解。_

在一次次的**加点**过程中，洞**只**会在加上一点时增加或减少，而洞的形成一定是这个点是原来一整条的**重要节点**，它能把一条切为两段或更多。这是洞就产生了。要产生洞，必要**至少两个方向**脱离这个点。经过归纳总结，洞的主要形态必定为“对立边阻挡并两方空”，“L 形阻挡并两方空”。

若是对立，只能使用一次并产生一个洞。

若是“L”字，能使用多次且消耗一个空位并产生一个洞。

一个洞的消失：

你可以自己去模拟一个洞的消失，你会发现要消失的最后一步是这个点八方相邻都有点。应该可以证明。

### 接下来就是代码啦。

| 变量 | 用处 |
| :----------: | :----------: |
|  int Map | 读入时用于记录坐标及高度 |
| int fa | 并查集 father 数组 |
| int size | 并查集大小数组 |
| bool a | 记录此点是否被记录 |
| int cnt1 | 记录此点正对存在的点 |
| int cnt2 | 记录此点斜对存在的点 |
| int cnt | 记录此点周围空位 |
| int dx,dy,p | 帮助记录周围 |
| bool h | 记录周围是否存在 |
| int f | 记录周围并查集 |
| int g | 记录周围临时是否同一连通块 |
| int flag | 记录并查集洞个数数组 |

## Code
### 不开 longlong 见祖宗！！！
时间复杂度 $O(n^2\log n^2)$。
```cpp
#include<bits/stdc++.h>
#define int long long //long long
using namespace std; 
const int N = 750; 
int n, m, aa, d, f[8], g[8], cnt1, cnt2, cnt, cnt3, sum, ans, size[N * N + 1], flag[N * N + 1], fa[N * N + 1], tot, x, y, xx, yy, xx1, yy1, xx2, yy2, xx3, yy3, xx4, yy4;
bool a[N + 1][N + 1], op, h[8];// 重要的已介绍
struct info{int x, y, w;}Map[N * N + 1];
bool cmp(info x, info y){return x.w < y.w;}
int dx[] = {1, 0, -1, 0, 1, -1, -1, 1};
int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};
int p[] = {0, 4, 1, 5, 2, 6, 3, 7};
bool InSide(int x, int y){return (x) && (x <= n) && (y) && (y <= n);}
int getfa(int k){return (fa[k] == k) ? k : fa[k] = getfa(fa[k]);}
int xy(int x, int y){return (x - 1) * n + y;}
void work2(){// 以下顺序别搞反
	if (cnt1 + cnt2 == 8){flag[d] --;return;}// 满了消洞
	for (int i = 0;i <= 3;i ++)
		if (g[i] && g[(i + 1) % 4] && ! g[i + 4] && cnt > 1)
			flag[d] ++,cnt --,g[i + 4] = 1;//“L”字形
	for (int i = 0;i <= 1;i ++)
		if (g[i] && g[i + 2] && !( g[i + 4] && g[i + 5] && g[i + 1]) && !(g[i + 6] && g[(i + 3) % 4 + 4] && g[(i + 3) % 4]) && cnt > 1){
			flag[d] ++;
			break;
		}// 对立边
}
void work(int x, int y){
	cnt1 = cnt2 = sum = 0;cnt = 8;
	for (int i = 0;i <= 7;i ++){
		xx = x + dx[i];yy = y + dy[i];
		if (InSide(xx, yy) && a[xx][yy])
			h[i] = 1,f[i] = getfa(xy(xx, yy));
		else h[i] = 0, f[i] = 0;
	}// 记录
	cnt = 0;
	for (int i = 0;i <= 7;i ++){
		xx = x + dx[p[i]];yy = y + dy[p[i]];
		xx1 = x + dx[p[(i + 1) % 8]];
		yy1 = y + dy[p[(i + 1) % 8]];
		if ((InSide(xx, yy) && a[xx][yy]) && ! (InSide(xx1, yy1) && a[xx1][yy1]))
			cnt ++;
	}// 记录空位
	d = xy(x, y); 
	for (int i = 0;i <= 3;i ++)
		if (h[i] && getfa(f[i]) != d){
			cnt1 = cnt2 = 0;
			for (int j = i;j <= 7;j ++)
				if (h[j] && f[j] == f[i]){
					if (j <= 3)cnt1 ++;
					else cnt2 ++;
					g[j] = 1;
				}// 找到同连通块的相邻点
			work2();
			size[d] += size[getfa(f[i])];// 点的合并
			flag[d] += flag[getfa(f[i])];// 洞的合并
			for (int j = 0;j <= 7;j ++)
				if(g[j])
					g[j] = 0,fa[f[i]] = d;// 爹的合并
		}
	if (!flag[d])ans += size[d];// 记录答案
}
signed main(){
	cin >> n;
	for (int i = 1;i <= n;i ++)
		for (int j = 1;j <= n;j ++){
			cin >> aa;
			Map[++ tot] = info{i, j, aa};
		}// 读入
	sort(Map + 1, Map + 1 + tot, cmp);// 排序
	for (int i = 1;i <= tot;i ++)fa[i] = i, size[i] = 1;// 初始化
	for (int i = 1;i <= tot;i ++){
		x = Map[i].x , y = Map[i].y;
		a[x][y] = 1;// 标记
		work(x, y);// 开干
	}
	cout << ans;// 输出
}
```

---

