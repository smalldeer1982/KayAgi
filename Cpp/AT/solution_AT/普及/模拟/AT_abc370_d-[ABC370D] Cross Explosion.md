# [ABC370D] Cross Explosion

## 题目描述

有一个网格，网格中有 $H$ 行和 $W$ 列。让 $(i, j)$ 表示从上往下第 $i$ 行，从左往上第 $j$ 列的单元格。  
最初，每个单元格中都有一面墙。  
按照下面给出的顺序处理 $Q$ 个查询后，求剩余墙的数量。

在第 $q$ 次查询中，我们给出了两个整数 $R_q$ 和 $C_q$ 。  
您在 $(R_q, C_q)$ 处放置了一枚炸弹来摧毁墙壁。结果会发生以下过程。

- 如果在 $(R_q, C_q)$ 处有一堵墙，则摧毁这堵墙并结束进程。
- 如果 $(R_q, C_q)$ 处没有墙壁，则摧毁从 $(R_q, C_q)$ 向上、向下、向左、向右观察时出现的第一面墙壁。更确切地说，以下四个过程是同时进行的：
    - 如果存在一个 $i \lt R_q$ ，使得在 $(i, C_q)$ 处有一堵墙，而在所有 $i \lt k \lt R_q$ 的 $(k, C_q)$ 处都没有墙，则摧毁 $(i, C_q)$ 处的墙。
    - 如果存在一个 $i \gt R_q$ ，使得在 $(i, C_q)$ 处有一堵墙，而在所有 $R_q \lt k \lt i$ 的 $(k, C_q)$ 处都没有墙，则破坏 $(i, C_q)$ 处的墙。
    - 如果存在一个 $j \lt C_q$ ，使得在所有 $j \lt k \lt C_q$ 中， $(R_q, j)$ 处有一堵墙，而 $(R_q, k)$ 处没有墙，则破坏 $(R_q, j)$ 处的墙。
    - 如果存在一个 $j \gt C_q$ ，使得在 $(R_q, j)$ 处有一堵墙，而在所有 $C_q \lt k \lt j$ 的 $(R_q, k)$ 处没有墙，则破坏 $(R_q, j)$ 处的墙。

## 说明/提示

- $1 \leq H, W$
- $H \times W \leq 4 \times 10^5$
- $1 \leq Q \leq 2 \times 10^5$
- $1 \leq R_q \leq H$
- $1 \leq C_q \leq W$
- 所有输入值均为整数。

Translate by DeepL,Manually verified.

## 样例 #1

### 输入

```
2 4 3
1 2
1 2
1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5 5 5
3 3
3 3
3 2
2 2
1 2```

### 输出

```
10```

## 样例 #3

### 输入

```
4 3 10
2 2
4 1
1 1
4 2
2 1
3 1
1 3
1 2
4 3
4 2```

### 输出

```
2```

# 题解

## 作者：沉石鱼惊旋 (赞：17)

# 题目翻译

给定 $h\times w$ 的网格，初始每个格子上都有一堵墙，给出 $q$ 个操作，每次给出 $(r,c)$ 表示操作位置，若 $(r,c)$ 位置上有墙就破坏掉这个墙。如果没有，破坏掉这堵墙上、下、左、右四个方向各看到的第一堵墙。

操作之后给出目前剩下的墙的个数。

$1\leq h,w,h\times w\leq 4\times 10^5$，$1\leq q\leq  2\times 10^5$，$1\leq r\leq h$，$1\leq c\leq w$。

# 题目思路

考虑到每一次至多影响 $4$ 堵墙，变化量很少，总数也只有 $4\times 10^5$ 个，可以直接模拟这个删除的过程。

直接往前找第一个没被删除的墙显然是有问题的。

考虑加速这个查找墙和删除墙的过程。

`std::set` 支持 $\mathcal O(\log n)$ 时间在集合内二分和删除。

维护 $sr_i$ 和 $sc_j$ 表示第 $i$ 行剩余的列的集合以及第 $j$ 列剩余的行的集合。

先判断是否 $(r,c)$ 位置上有墙，有的话直接删除掉。记得同时更新 $sr$ 和 $sc$。

如果没有就在集合内二分，使用提供的 `upper_bound` 函数找到第一个比自己大的位置。之后往前走一个就可以得到比自己小的位置。

每一次尝试删除元素都要判断迭代器是否合法。

最后把所有 $sr_i$ 内的元素个数加起来就是答案。

---

还有一种链表的做法，不依赖 STL。

先把这些二维坐标重新编号成一维的，编号方式是 $(x,y)$ 为 $(x-1)\times w+y$。

以样例 $2$ 为例，这是初始棋盘。

设 $faU_{i}$ 表示 $\tt U$ 方向上，编号为 $i$ 的，最近的一个没有被删除的位置。别的同理。一开始每个人都指向了自己。
$$
\def\arraystretch{1.5}
\begin{array} {|c|c|c|c|c|}
\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
\end{array}
$$

通过打的标记我们可以知道 $(3,3)$ 上有墙，那就只需要删除 $(3,3)$。
$$
\def\arraystretch{1.5}
\begin{array} {|c|c|c|c|c|}
\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{.} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
\end{array}
$$
那么 $(3,3)$ 删除之后影响了 $(2,3)$ 位置上的 $\tt D$ 等位置。

把自己的链表改掉。比如 $\tt U$ 属性的链，$(3,3)$ 这个点挂到 $(2,3)$ 上。

同理别的四个方向自己也要挂到下一个上面。

这就是删除一个点。第二种如果标记了删除，例如样例中第二次操作 $(3,3)$ 的时候。

那么我们就跳这个链，跳到第一个没有被标记删除的位置。比如这一次如果查询 $(3,3)$ 的 $\tt U$ 属性，我们会跳到 $(2,3)$ 上。$(2,3)$ 没有被标记删除，那么就取 $(2,3)$ 作为我们的目标。之后删除掉 $(2,3)$，同理修改掉 $(2,3)$ 在 $4$ 种方向上指向的对象。

所以经过第二次操作之后，图一共被删掉了 $5$ 堵墙。
$$
\def\arraystretch{1.5}
\begin{array} {|c|c|c|c|c|}
\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{.} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{.} & \tt{.} & \tt{.} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{.} & \tt{*} & \tt{*}  \cr\hline
   \tt{*} & \tt{*} & \tt{*} & \tt{*} & \tt{*}  \cr\hline
\end{array}
$$
那么这时候忽略掉那些自己指向自己的部分，$\tt{U,D,L,R}$ 四个属性的链有如下形式：

$\texttt{U}:(4,3)\to (3,3)\to(2,3)\to (1,3)$

$\texttt{D}:(2,3)\to (3,3)\to(4,3)\to (5,3)$

$\texttt{L}:(2,3)\to (2,2) \ \ \ /\ \ \  (3,4)\to (3,3) \to(3,2)\to (3,1)\ \ \ /\ \ \ (4,3)\to (4,2)$

$\texttt{R}:(2,3) \to (2,4)\ \ \ /\ \ \  (3,2) \to (3,3) \to (3,4)\to (3,5) \ \ \ /\ \ \  (4,3)\to (4,4)$

当然直接写链表维护这个过程是会 TLE 的。每一次都可能会跳很多步。

这时候如果我们跳的过程中有已经被删除的点，可以直接把自己指向最头上的没有被删除的。

这个过程就是并查集中的路径压缩。

并查集就可以看成是一个森林，每棵树都可以看成是若干条链拼在一起，每个点都挂到自己的父亲节点。本题的父亲节点，意义就是最近的一个没有被删除的位置。每一次跳父亲，然后路径压缩全部挂到最高的祖先上。

# 完整代码

[AT submission 57560468](https://atcoder.jp/contests/abc370/submissions/57560468)

```cpp
#include <bits/stdc++.h>
using namespace std;
int h, w, q;
set<int> sr[400020];
set<int> sc[400020];
void del(int r, int c)
{
    sr[r].erase(c);
    sc[c].erase(r);
}
int ans;
int main()
{
    cin >> h >> w >> q;
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            sr[i].insert(j);
            sc[j].insert(i);
        }
    }
    while (q--)
    {
        int r, c;
        cin >> r >> c;
        if (sr[r].count(c))
        {
            del(r, c);
            continue;
        }
        if (!sr[r].empty())
        {
            auto it = sr[r].upper_bound(c);
            if (it != sr[r].end())
                del(r, *it);
            if (!sr[r].empty())
            {
                it = sr[r].upper_bound(c);
                if (it != sr[r].begin())
                    it--, del(r, *it);
            }
        }
        if (!sc[c].empty())
        {
            auto it = sc[c].upper_bound(r);
            if (it != sc[c].end())
                del(*it, c);
            if (!sc[c].empty())
            {
                it = sc[c].upper_bound(r);
                if (it != sc[c].begin())
                    it--, del(*it, c);
            }
        }
    }
    for (int i = 1; i <= h; i++)
        ans += sr[i].size();
    cout << ans << endl;
    return 0;
}
```

[AT submission 57574774](https://atcoder.jp/contests/abc370/submissions/57574774)

```cpp
#include <bits/stdc++.h>
using namespace std;
int h, w, q;
int faU[400020];
int faD[400020];
int faL[400020];
int faR[400020];
int F(int u, int *fa) { return fa[u] ^ u ? fa[u] = F(fa[u], fa) : u; }
void U(int u, int v, int *fa) { fa[F(u, fa)] = F(v, fa); }
bool in(int x, int y) { return 1 <= x && x <= h && 1 <= y && y <= w; }
int id(int x, int y) { return in(x, y) ? (x - 1) * w + y : 0; }
bool del[400020];
int ans;
void ers(int r, int c)
{
    if (!in(r, c))
        return;
    ans--;
    del[id(r, c)] = 1;
    U(id(r, c), id(r - 1, c), faU);
    U(id(r, c), id(r + 1, c), faD);
    U(id(r, c), id(r, c - 1), faL);
    U(id(r, c), id(r, c + 1), faR);
}
int main()
{
    cin >> h >> w >> q;
    for (int i = 1; i <= h * w; i++)
        faU[i] = i;
    for (int i = 1; i <= h * w; i++)
        faD[i] = i;
    for (int i = 1; i <= h * w; i++)
        faL[i] = i;
    for (int i = 1; i <= h * w; i++)
        faR[i] = i;
    ans = h * w;
    while (q--)
    {
        int r, c;
        cin >> r >> c;
        if (!del[id(r, c)])
        {
            ers(r, c);
            continue;
        }
        int t;
        t = F(id(r, c), faU);
        if (t)
            ers(t % w == 0 ? t / w : t / w + 1, c);
        t = F(id(r, c), faD);
        if (t)
            ers(t % w == 0 ? t / w : t / w + 1, c);
        t = F(id(r, c), faL);
        if (t)
            ers(r, t % w == 0 ? w : t % w);
        t = F(id(r, c), faR);
        if (t)
            ers(r, t % w == 0 ? w : t % w);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：PineappleSummer (赞：7)

[[ABC370D] Cross Explosion](https://www.luogu.com.cn/problem/AT_abc370_d)

简单题。

首先题目保证 $h\times w\le 4\times 10^5$，所以可以将所有点都存起来。

可以考虑对每一行和每一列开一个 `set`，存储这一行或这一列中墙的位置。用 $h_i$ 表示第 $i$ 行的 `set`，用 $w_i$ 表示第 $i$ 列的 `set`。

对于每次询问，可以查找 $h_x$ 中是否有存在 $y$，如果有 $y$，删掉 $h_x$ 中的 $y$，删掉 $w_y$ 中的 $x$。

如果没有 $y$，找到 $h_x$ 中第一个大于 $y$ 的数，删去这个数并删掉这个数前面的那个数。

同理，找到 $w_y$ 中第一个大于 $x$ 的数，删去这个数并删掉这个数前面的那个数。

最后剩下的墙的数量就是每一行 `set` 的大小之和。

```cpp
set <int> h[N], w[N];
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            h[i].insert (j), w[j].insert (i);
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        if (h[x].find (y) != h[x].end ()) {
            h[x].erase (y);
            w[y].erase (x);
        }
        else {
            auto i = h[x].lower_bound (y);
            vector <int> v;
            if (i != h[x].end ()) v.push_back (*i);
            if (i != h[x].begin ()) v.push_back (*(--i));
            for (auto j : v) h[x].erase (j), w[j].erase (x);

            v.clear ();
            i = w[y].lower_bound (x);
            if (i != w[y].end ()) v.push_back (*i);
            if (i != w[y].begin ()) v.push_back (*(--i));
            for (auto j : v) w[y].erase (j), h[j].erase (y);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += h[i].size ();
    cout << ans;
    return 0;
}
```

---

## 作者：天使宝贝 (赞：4)

[题面传送门](https://www.luogu.com.cn/problem/AT_abc370_d)

吐槽：为啥很多大佬说 D 卡常，但是蒟蒻觉得不卡啊。

### 题目大意
给你一个 $H \times W$ 的网格，初始网格上全是墙壁。
现有 $q$ 次操作，对于每次操作，给你两个整数 $R_q$ 和 $C_q$，然后会发生以下过程：
* 如果在 $(R_q, C_q)$ 处有墙，则摧毁该面墙，并结束本次操作。
* 如果在 $(R_q, C_q)$ 处没有墙，则摧毁在该位置上下左右出现的第一面墙。

请你输出这 $q$ 次操作后剩余墙的数量。

### 思路&分析
不妨先想想暴力，暴力很简单，只需要判断一下当前位置是否有墙，如果有就摧毁这面墙，否则就朝上下左右四个方向遍历，找到第一面墙摧毁即可。

考虑优化，我们可以开一个数组来记录这个点被重复炸了几次，记为 $v_{i, j}$，然后对于每次操作，我们只需要从 $x + v_{i, j}$，$x - v_{i, j}$，$y + v_{i, j}$，$y - v_{i, j}$ 开始找寻第一次出现的墙即可。

于是我们就愉快的解决了此题。

### CODE
[赛时代码](https://atcoder.jp/contests/abc370/submissions/57539441)

---

## 作者：zzhbpyy (赞：3)

### [D - Cross Explosion](https://atcoder.jp/contests/abc370/tasks/abc370_d)

## 分析

暴力查找出现的第一个墙显然是 $O(HW)$ 的，不能通过此题。考虑用  `std::set` 维护每一行每一列连续的墙。每次修改时用 `upper_bound` 函数找到离给定点最近的连续段。删除一个点时就先删去该点所在的连续段，然后插入该段的剩余部分即可，注意行列都要维护好。复杂度 $O(Q\log (HW))$。

## Code

```c++
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using pii=pair<int,int>;
int h,w,q,ans;
vector<int>d[410005];//维护墙是否已经被拆掉
set<pii>x[410005],y[410005];//x维护每行的信息，y维护每列的信息
//pair的两个值对应连续段的起点和终点
void del(int a,int b){
	d[a][b]=true;ans--;
	auto g=--x[a].upper_bound((pii){b,1145141});
	int l=g->fi,r=g->se;
	x[a].erase(g);
	if(l!=b)x[a].insert({l,b-1});
	if(r!=b)x[a].insert({b+1,r});
	g=--y[b].upper_bound((pii){a,1145141});
	l=g->fi,r=g->se;y[b].erase(g);
	if(l!=a)y[b].insert({l,a-1});
	if(r!=a)y[b].insert({a+1,r});
}
signed main(){
	cin>>h>>w>>q;ans=h*w;
	for(int i=1;i<=h;i++)d[i].resize(w+10),x[i].insert({1,w});
	for(int i=1;i<=w;i++)y[i].insert({1,h});
	int xx,yy;
	while(q--){
		cin>>xx>>yy;
		if(!d[xx][yy])del(xx,yy);//没有被删过则直接删去
		else{
			auto g=x[xx].upper_bound({yy,1145141});
			if(g!=x[xx].end())del(xx,g->fi);
			g=x[xx].upper_bound({yy,1145141});
			if(g!=x[xx].begin())--g,del(xx,g->se);
			g=y[yy].upper_bound({xx,1145141});
			if(g!=y[yy].end())del(g->fi,yy);
			g=y[yy].upper_bound({xx,1145141});
			if(g!=y[yy].begin())--g,del(g->se,yy);
		}
	}cout<<ans<<'\n';
}
```

---

## 作者：xixisuper (赞：3)

# AT_abc370_d [ABC370D] Cross Explosion 题解

这是一道没有思维难度，只有实现难度的题。

## 思路

题目描述很清晰了，其实直接模拟就好了，但是要考虑怎么维护。

首先发现题目只限定了 $H\times W\le4\times10^5$，却没有对 $H$ 和 $W$ 进行限制，所以开二维数组的时候须使用动态存储的方式，也就是开 `vector` 存。

同样也是因为这个限制，所以说每放一个炸弹，我们不能暴力一个一个找离它最近的墙，这样时间复杂度会飙升至 $O(Q\times\min(H,W))$，过不了，我们可以考虑对每个点维护四个方向的并查集，并查集中存的是对应方向离其最近的点坐标，然后套上路径压缩，这个题就过了。

总时间复杂度可以视为 $O(Q\log HW)$ 量级，据说有人靠二分过的，但恕我没想到怎么二分。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
const ll N=4e5+10;
inline ll read(){
	register ll x=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
ll H,W,Q;
vector<bool> You[N];
vector<pair<ll,ll> > up[N],dn[N],lft[N],rgt[N];
pair<ll,ll> get_up(ll x,ll y){
	if(up[x][y]==make_pair(x,y)) return make_pair(x,y);
	return up[x][y]=get_up(up[x][y].first,up[x][y].second);
}
pair<ll,ll> get_dn(ll x,ll y){
	if(dn[x][y]==make_pair(x,y)) return make_pair(x,y);
	return dn[x][y]=get_dn(dn[x][y].first,dn[x][y].second);
}
pair<ll,ll> get_lft(ll x,ll y){
	if(lft[x][y]==make_pair(x,y)) return make_pair(x,y);
	return lft[x][y]=get_lft(lft[x][y].first,lft[x][y].second);
}
pair<ll,ll> get_rgt(ll x,ll y){
	if(rgt[x][y]==make_pair(x,y)) return make_pair(x,y);
	return rgt[x][y]=get_rgt(rgt[x][y].first,rgt[x][y].second);
}
void DES(ll x,ll y){
	up[x][y]=up[x-1][y];
	dn[x][y]=dn[x+1][y];
	lft[x][y]=lft[x][y-1];
	rgt[x][y]=rgt[x][y+1];
}
int main(){
	H=read(),W=read(),Q=read();
	for(ll i=0;i<=H+1;i++){
		You[i].push_back(0);
		for(ll j=0;j<=W+1;j++){
			You[i].push_back(0);
			up[i].push_back(make_pair(i,j));
			dn[i].push_back(make_pair(i,j));
			lft[i].push_back(make_pair(i,j));
			rgt[i].push_back(make_pair(i,j));
		}
	}
	ll ans=H*W;
	while(Q--){
		ll x,y;
		x=read(),y=read();
		if(up[x][y]==make_pair(x,y)){
			ans-=1;
			DES(x,y);
		}
		else{
			if(get_up(x,y)!=make_pair(0LL,y)){
				ans--;
				DES(up[x][y].first,up[x][y].second); 
			}
			if(get_dn(x,y)!=make_pair(H+1,y)){
				ans--;
				DES(dn[x][y].first,dn[x][y].second); 
			}
			if(get_lft(x,y)!=make_pair(x,0LL)){
				ans--;
				DES(lft[x][y].first,lft[x][y].second);
			}
			if(get_rgt(x,y)!=make_pair(x,W+1)){
				ans--;
				DES(rgt[x][y].first,rgt[x][y].second);
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：3)

# AT_abc370_d [ABC370D](https://www.luogu.com.cn/problem/AT_abc370_d) Cross Explosion 题解

## 思路

~~奆佬都写的 STL，树状数组，二分，蒟蒻不才，写篇路径压缩吧。~~

首先看数据范围，$1 \le n,m$ 且 $1 \le n \times m \le 4 \times 10^5$，$1 \le q \le 2 \times 10^5$。

显然暴力无法通过。

其次对于 $1 \le n \times m \le 4 \times 10^5$，无法开数组（实际上开 main 里是可以的），可以使用 vector。

然后就是如何快速寻找 $(x,y)$ 上下左右第一堵墙。

以向左找为例。

我们可以开一个数组（vector）记为 $t$，$t_{x,y}$ 表示坐标 $(x,y)$ 向左第一堵墙的坐标。

对于查找显然可以路径压缩，以快速找到向左第一堵墙。

其余方向同理。

这种方法的时间复杂度优秀。

## Code

~~马蜂不好，凑合着看吧。~~

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,q,ans;
vector<pair<int,int> > init_;
vector<bool> init__;//初始化用的，凑合着看吧。
vector<vector<bool> > vis;//有没有被拆过。
vector<vector<pair<int,int> > > t[4];
//t[d][x][y] 表示 (x,y) 向 d 方向第一堵墙的坐标。
//关于 d，在代码结尾可以看到。
bool check(pair<int,int> pos)
{
	int x=pos.first,y=pos.second;
	return x>=1&&x<=n&&y>=1&&y<=m;
}//坐标是否合法
pair<int,int> find(int d,int x,int y)
{
	if(!vis[x][y]||!check({x,y})) return {x,y};
	int nx=t[d][x][y].first,ny=t[d][x][y].second;
    //(nx,ny) 是 (x,y) 向 d 方向的下一堵墙的坐标。
	return t[d][x][y]=find(d,nx,ny);//路径压缩。
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	ans=n*m;
	for(int i=0;i<=m+1;i++) init__.push_back(0),init_.push_back({0,0});
	for(int i=0;i<=n+1;i++)
		vis.push_back(init__);
	for(int i=0;i<=n+1;i++)
		for(int j=0;j<4;j++)
			t[j].push_back(init_);
    //以上为初始化。
	for(int i=0;i<=n+1;i++)
		for(int j=0;j<=m+1;j++)
		{
			if(1<=i&&i<=n&&1<=j&&j<=m)//check({i,j})
			{
				t[0][i][j]={i-1,j};
				t[1][i][j]={i+1,j};
				t[2][i][j]={i,j-1};
				t[3][i][j]={i,j+1};
				continue;
			}
			for(int k=0;k<4;k++)
				t[k][i][j]={i,j};//让它指向其自己，防止出事。
		}
	while(q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(!vis[x][y])//这里有一堵墙。
		{
			vis[x][y]=1;//Boom!
			ans--;
			continue;
		}
		pair<int,int> pos0=find(0,x,y);
		pair<int,int> pos1=find(1,x,y);
		pair<int,int> pos2=find(2,x,y);
		pair<int,int> pos3=find(3,x,y);
        ///分别找到四个方向的第一堵墙。
		if(check(pos0)) ans--,vis[pos0.first][pos0.second]=1;
		if(check(pos1)) ans--,vis[pos1.first][pos1.second]=1;
		if(check(pos2)) ans--,vis[pos2.first][pos2.second]=1;
		if(check(pos3)) ans--,vis[pos3.first][pos3.second]=1;
        //如果有就爆破。
	}
	printf("%d\n",ans);
	return 0;
}
//0 (i-1,j) up
//1 (i+1,j) down
//2 (i,j-1) left
//3 (i,j+1) right
```

---

## 作者：_H17_ (赞：3)

## 题外话

感觉是个超级有意思的题，我的方法比较独特。

## 题目分析

考虑到炸一个点，会扩散出去，考虑维护：当前点是否被炸、上下左右第一个没被炸的点。

考虑使用链表来维护（原因是可以任意删除）。

但是注意到一个问题：我们炸的点可能是删除过的，所以需要同时维护删除过的点的上下左右，这看似不太符合链表性质。

因为没去掉一个点，需要更新它左边一整段、右边一整段（上下同理），所以更新复杂度变为 $O(n)$，整体 $O(nq)$。

（此处的 $n$ 默认为 $H,W$）

## 暴力代码

```cpp
#include<bits/stdc++.h>
#define right sojdjfoas
#define left oahsdfipas
#define up idphfas9fjas
#define down odhfpoasas
using namespace std;
int h,w,q,r,c,ans;
map<pair<int,int>,int>mp,up,down,left,right;
void bomb(int r,int c){
    if(r==-1||c==-1)
        return;
    mp[{r,c}]=0;
    int tmp=max(up[{r,c}],1);
    for(int i=tmp;i<r;i++)
        down[{i,c}]=down[{r,c}];//更新
    tmp=down[{r,c}];
    if(tmp==-1)
        tmp=h;
    for(int i=r+1;i<=tmp;i++)
        up[{i,c}]=up[{r,c}];//更新
    tmp=max(left[{r,c}],1);
    for(int i=tmp;i<c;i++)
        right[{r,i}]=right[{r,c}];//更新
    tmp=right[{r,c}];
    if(tmp==-1)
        tmp=w;
    for(int i=c+1;i<=tmp;i++)
        left[{r,i}]=left[{r,c}];//更新
    return;
}
int main(){
    cin>>h>>w;
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            mp[{i,j}]=1;
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++){
            if(i==1)
                up[{i,j}]=-1;
            else
                up[{i,j}]=i-1;
            if(i==h)
                down[{i,j}]=-1;
            else
                down[{i,j}]=i+1;
            if(j==1)
                left[{i,j}]=-1;
            else
                left[{i,j}]=j-1;
            if(j==w)
                right[{i,j}]=-1;
            else
                right[{i,j}]=j+1;
        }//初始化，没有用 -1 表示
    for(cin>>q;q;--q){
        cin>>r>>c;
        if(mp[{r,c}])
            bomb(r,c);
        else{
            bomb(up[{r,c}],c);
            bomb(down[{r,c}],c);
            bomb(r,left[{r,c}]);
            bomb(r,right[{r,c}]);//全方位爆炸
        }
    }
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            ans+=mp[{i,j}];
    cout<<ans;
    return 0;
}
```

## 优化

> 山重水复疑无路，柳暗花明又一村。

看似已经无解，但是经过思考发现其实并不用每次对上下左右修改到底。

只需要更新上下左右的时候更新最近的一个，但是这样会有一个问题：中间墙被炸了就错了。

考虑进行路径压缩优化（其实也类似于线段树的 lazy tag，用到再更新）。

这样可以控制住时间复杂度：$O(q)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define right sojdjfoas
#define left oahsdfipas
#define up idphfas9fjas
#define down odhfpoasas
using namespace std;
int h,w,q,r,c,ans;
map<pair<int,int>,int>mp,up,down,left,right;
int get_up(int r,int c){
    if(!mp[{r,c}]&&r!=-1)
        return up[{r,c}]=get_up(up[{r,c}],c);
    else
        return r;
}
int get_down(int r,int c){
    if(!mp[{r,c}]&&r!=-1)
        return down[{r,c}]=get_down(down[{r,c}],c);
    else
        return r;
}
int get_left(int r,int c){
    if(!mp[{r,c}]&&c!=-1)
        return left[{r,c}]=get_left(r,left[{r,c}]);
    else
        return c;
}
int get_right(int r,int c){
    if(!mp[{r,c}]&&c!=-1)
        return right[{r,c}]=get_right(r,right[{r,c}]);
    else
        return c;
}//路径压缩
void bomb(int r,int c){
    if(r==-1||c==-1)
        return;
    if(mp[{r,c}]){
        mp[{r,c}]=0;
        return;
    }
    bomb(get_down(r,c),c);
    bomb(get_up(r,c),c),
    bomb(r,get_left(r,c)),
    bomb(r,get_right(r,c));//四边炸
    return;
}
int main(){
    cin>>h>>w;
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            mp[{i,j}]=1;
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++){
            if(i==1)
                up[{i,j}]=-1;
            else
                up[{i,j}]=i-1;
            if(i==h)
                down[{i,j}]=-1;
            else
                down[{i,j}]=i+1;
            if(j==1)
                left[{i,j}]=-1;
            else
                left[{i,j}]=j-1;
            if(j==w)
                right[{i,j}]=-1;
            else
                right[{i,j}]=j+1;
        }
    for(cin>>q;q;--q){
        cin>>r>>c;
        bomb(r,c);//炸
    }
    for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
            ans+=mp[{i,j}];
    cout<<ans;
    return 0;
}
```

---

## 作者：DWBbobo (赞：2)

### 思路

可以非常快地想到一个暴力的解法：对于每个询问，如果$(Rq,Cq)$ 有墙，就炸毁它，否则执行以下操作：

- 向上：从 $(Rq,Cq)$ 向上遍历，找到第一个有墙的方格，并炸毁它。
- 向下：从 $(Rq,Cq)$ 向下遍历，找到第一个有墙的方格，并炸毁它。
- 向左：从 $(Rq,Cq)$ 向左遍历，找到第一个有墙的方格，并炸毁它。
- 向右：从 $(Rq,Cq)$ 向右遍历，找到第一个有墙的方格，并炸毁它。

但是，这么做会 TLE ，所以我们要想一想怎么优化。

我们可以用 $row$ 和 $col$ 两个数组分别存储每行、每列的有墙方格下标，在我们对 $(Rq,Cq)$ 引爆炸弹时对其所在行和列进行二分查找，找到会被炸掉的墙，并在 $row$ 和 $col$ 数组中清除该点。

可是怎么实现 $row$ 和 $col$ 两个数组呢？？？

要求：可以二分以及快速插入、删除。

答案：STL set！！！

### CODE


```cpp
#include <bits/stdc++.h>
using namespace std;

int h,w,q,ans;
set <int> row[400011];
set <int> col[400011];

int main() {
    scanf("%d%d%d",&h,&w,&q);
	ans = h * w;
    for(int i=1;i<=h;i++) {
        for(int j=1;j<=w;j++) {
            row[i].insert(j);
            col[j].insert(i);
        }
    }
    while (q--) {
        int x,y;
        scanf("%d%d",&x,&y);
        if (row[x].find(y) != row[x].end()) {
            row[x].erase(y);
			col[y].erase(x);
			ans--;
			continue;
        }
		set <int> ::iterator i,j;
		i = row[x].lower_bound(y);
		j = i;
		if (i != row[x].begin()) {
			i--;
			col[*i].erase(x);
			row[x].erase(i);
			ans--;
		}
		if (j != row[x].end()) {
			col[*j].erase(x);
			row[x].erase(j);
			ans--;
		}
		set <int> ::iterator k,l;
		k = col[y].lower_bound(x);
		l = k;
		if (k != col[y].begin()) {
			k--;
			row[*k].erase(y);
			col[y].erase(k);
			ans--;
		}
		if (l != col[y].end()) {
			row[*l].erase(y);
			col[y].erase(l);
			ans--;
		}
    }
	printf("%d",ans);
    return 0;
}
```

---

## 作者：卷王 (赞：2)

定义两个 set。$row_i$ 记录第 $i$ 行的所有墙壁的列坐标，$col_i$ 记录第 $i$ 列的所有墙壁的行坐标。由于题目保证了 $H\times W \le 4\times 10^5$，所以空间是不会爆的。

对于每一次操作，使用 set 自带的 `lower_bound` 函数进行查找，暴力删除即可，具体见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
int a[1000007];
multiset<int>row[400007],col[400007];
signed main() {
	n=read(),m=read(),Q=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			row[i].insert(j);
			col[j].insert(i);
		}
	while(Q--){
		int x=read(),y=read();
		if(row[x].find(y)!=row[x].end()){
			row[x].erase(y);
			col[y].erase(x);
			continue;
		}
		auto pos=row[x].lower_bound(y);
		if(pos!=row[x].begin()){
			pos--;
			col[*pos].erase(x);
			row[x].erase(pos);
		}
		
		pos=row[x].lower_bound(y);
		if(pos!=row[x].end()){
			col[*pos].erase(x);
			row[x].erase(pos);
		}
		
		pos=col[y].lower_bound(x);
		if(pos!=col[y].begin()){
			pos--;
			row[*pos].erase(y);
			col[y].erase(pos);
		}
		
		pos=col[y].lower_bound(x);
		if(pos!=col[y].end()){
			row[*pos].erase(y);
			col[y].erase(pos);
		}
	}
	for(int i=1;i<=400000;i++)ans+=(int)row[i].size();
	cout<<ans;
	return 0;
}
```

---

## 作者：zhoumurui (赞：2)

### 题面展示

有一个网格，网格中有 $H$ 行和 $W$ 列。让 $(i,j)$ 表示从上往下数第 $i$ 行和从左往上数第 $j$ 列的单元格。  
最初，每个单元格都是实心的。

接下来要进行 $Q$ 次操作，每次操作给出两个整数 $R_i$ 和 $C_i$。

- 如果在 $(R_i, C_i)$ 处的格子是实心的，将它变为空心。
- 如果 $(R_i, C_i)$ 处是空心的，则将从 $(R_i, C_i)$ 向上、向下、向左、向右观察时出现的第一个实心的格子变为空心。

求所有操作结束后，实心格子的总数。

### 题目思路

建议评绿。

这里假设大家都会写~~一分都没有的~~大暴力。

我们思考大暴力的时间缺陷在哪里。显然，在于检索 $(R_i, C_i)$ 向上、向下、向左、向右观察时出现的第一个实心的格子。

我们只要优化这个瓶颈就可以 AC 此题。

我们以向右检索为例，注意到观察的格子在 $(R_i,C_i)$ 到 $(R_i,W)$ 之间，我们要找到“最后一个与 $(R_i,C_i)$ 之间没有实心格子的点”。

我们于是想到了二分，而且这个例子也确实满足单调性。

但是，这样做需要维护两个同一行的点之间的实心格子数，这我们也熟，使用树状数组就可以了。

### 核心代码展示

注意：在我的代码中，为了避免初始化，实心格子设为了 $0$，空心格子是 $1$。

这里我使用了一种用树状数组存储网格的方式：

```cpp
struct szsz{
    unordered_map<int,int> c;
    
    int sum(int k){//O(logN)
        int ans=0;
        for (int i=k;i;i-=lowbit(i))ans+=c[i];
        return ans;
    }
    void add(int k,int x){//O(logN)
        for (int i=k;i<=400000;i+=lowbit(i)){
            c[i]+=x;
        }
    }
}hang[400005],lie[400005];
int ask(int r,int c){//O(logN)
    return hang[r].sum(c)-hang[r].sum(c-1);
}
void sett(int r,int c,int x){//O(logN)
    int k=ask(r,c);
    hang[r].add(c,x-k);
    lie[c].add(r,x-k);
}
```

进行操作的代码长这样：

```
void op(int rr,int cc){
    if (!ask(rr,cc)){
        sett(rr,cc,1);
        return;
    }
    int l,r,mid;
    //清除左侧
    l=1,r=cc,mid=(l+r)/2;
    while (l<r){
        mid=(l+r)/2;
        if (hang[rr].sum(cc)-hang[rr].sum(mid-1)==cc-mid+1)r=mid;
        else l=mid+1;
    }
    if (r>1)sett(rr,r-1,1);
    //清除右侧
    l=cc,r=w,mid=(l+r+1)/2;
    //cout<<"rightfinding"<<l<<" "<<r<<endl;
    while (l<r){
        //cout<<"rightfinding"<<l<<" "<<r<<endl;
        mid=(l+r+1)/2;
        if (hang[rr].sum(mid)-hang[rr].sum(cc-1)==mid-cc+1)l=mid;
        else r=mid-1;
    }
    if (l<w)sett(rr,l+1,1);
    //清除上侧
    l=1,r=rr,mid=(l+r)/2;
    while (l<r){
        mid=(l+r)/2;
        if (lie[cc].sum(rr)-lie[cc].sum(mid-1)==rr-mid+1)r=mid;
        else l=mid+1;
    }
    if (r>1)sett(r-1,cc,1);
    l=rr,r=h,mid=(l+r+1)/2;
    while (l<r){
        mid=(l+r+1)/2;
        if (lie[cc].sum(mid)-lie[cc].sum(rr-1)==mid-rr+1)l=mid;
        else r=mid-1;
    }
    if (l<h)sett(l+1,cc,1);
}
```

所有操作进行完后这样统计答案就可以了。

```cpp
int ans=0;
for (int i=1;i<=h;i++){
    ans+=hang[i].sum(w);
}
cout<<h*w-ans;
```

---

