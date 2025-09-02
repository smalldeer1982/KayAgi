# Recover the Tree

## 题目描述

Rhodoks 有一棵包含 $n$ 个顶点的树，但他已经不记得这棵树的结构了。顶点编号从 $1$ 到 $n$。

如果区间 $[l, r]$（$1 \leq l \leq r \leq n$）中的顶点 $l, l+1, \ldots, r$ 在 Rhodoks 的树中构成一个连通块，则称该区间是好的，否则称为坏的。

例如，如果树的结构如图所示，则只有区间 $[3,4]$ 是坏的，其余所有区间都是好的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/4fd7c832e9131d61a7e54d528e57f32ae63951c2.png)

对于每一个 $\frac{n(n+1)}{2}$ 个区间，Rhodoks 都记得它是好还是坏。你能帮他还原这棵树吗？如果有多种方案，输出任意一种即可。

保证至少存在一棵树满足 Rhodoks 的描述。

## 说明/提示

第一个测试点的解释见题面。

第二个测试点，一种可能的树结构如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/5e8ee8c45791f0ab519d49ee3373b652d0c902bd.png)

第三个测试点，一种可能的树结构如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710D/e951e91b803c38b61a8bd56acc10554d42a981b3.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
4
1111
111
10
1
6
111111
11111
1111
111
11
1
12
100100000001
11100000001
1000000000
100000000
10010001
1110000
100000
10000
1001
111
10
1```

### 输出

```
1 2
2 3
2 4
1 2
2 3
3 4
4 5
5 6
2 3
6 7
10 11
2 4
6 8
10 12
1 4
5 8
9 12
5 12
2 12```

# 题解

## 作者：xcyle (赞：25)

从小到大考虑每个好的区间。

用并查集维护当前树的连通状态，显然任何时刻每个连通块都是区间。

设我们考虑到了好区间 $[l,r]$，$l$ 所在连通块为 $[l',x_1]$，$r$ 所在连通块为 $[x_k+1,r']$，它们之间还有 $k-1$ 个连通块 $[x_i+1,x_{i+1}]$。满足 $l'\le l\le x_1<...<x_k\le r \le r'$且 $k\ge 1$。

容易发现 $k=2$ 时无解。$k=1$ 时直接连 $(l,r)$ 即可。$k>2$ 时一种构造是连 $(l,r),(l,x_k)$ 以及 $(x_i,r)(2\le i<k)$。

```cpp
#include <bits/stdc++.h>
#define ru(i, l, r) for (int i = (l); i <= (r); i++)
#define rd(i, r, l) for (int i = (r); i >= (l); i--)
#define maxn 2005
using namespace std;
char s[maxn][maxn];
int T, n, fa[maxn];
void solve()
{
	scanf("%d", &n);
	ru(i, 1, n) fa[i] = i, scanf("%s", s[i] + i);
	ru(i, 1, n) rd(j, i - 1, 1) if(s[j][i] == '1' && fa[i] > j)
	{
		printf("%d %d\n", j, i);
		if(fa[fa[i] - 1] > j)
		{
			printf("%d %d\n", j, fa[i] - 1);
			rd(k, fa[fa[i] - 1] - 1, j + 1) if(fa[k] == k) printf("%d %d\n", k, i);
		}
		ru(k, j, i) fa[k] = fa[j];
	}
}
int main() {scanf("%d", &T); while(T--) solve();}
```

---

## 作者：周子衡 (赞：10)

好题。可惜了……

------------------

注意到树上连通块一个直观的性质：

**性质** 两个树上连通块的交若不空，则这两个连通块的交、并都是树上连通块。

接下来我们将反复用到这个性质。

------------------

这类构造题目一般有三个可以着手的方向：自下而上还原、自上而下还原、按 DFS 序还原。尝试一番可以发现，本题中自上而下还原比较方便。

设我们知道区间 $I$ 是好区间，现在要还原 $I$ 内的连边方式。考虑找出 $I$ 内部的一些比较大的好区间 $I_1,...,I_k$，这些区间应该满足：

- 对每个 $i$，不存在一个好区间严格包含 $I_i$ 且严格被 $I$ 包含。

这是因为，如果一个好区间被另一个完全包含，我们完全可以在递归下去的时候再处理。显见 $I_1\sim I_k$ 中不能存在左端点相同的两个区间，我们不妨按左端点大小将这些区间排序。另外可以注意到，每个 $I$ 内的位置都至少出现在了一个 $I_i$ 中。

如果 $I_1\sim I_k$ 两两不交，那么我们可以递归地处理这些区间，然后把这些区间看成单点，在这些点之间连边，使得不存在连续的若干区间自行构成连通块。$k=2$ 时，直接从 $I_1$ 左端点向 $I_2$ 右端点连边即可。$k\geq 4$ 时，一种可行的策略是：从 $I_1$ 左端点向 $I_3,...,I_k$ 右端点连边，$I_2$ 左端点向 $I_k$ 右端点连边。同时可以注意到 $k=3$ 是无解的。以上的结论可以自己画画图找出来。

----------------

如果 $I_1\sim I_k$ 有区间相交怎么办呢？可以观察到：

**性质** 若 $I_1\sim I_k$ 中有区间相交，则 $k=2$。

**证明** 若有区间 $X,Y$ 相交，那么 $X,Y$ 的并也应该是好区间，这个好区间包含了 $X,Y$，按理来说 $X,Y$ 不应该出现在 $I_1\sim I_k$ 中。唯一的例外是，$X,Y$ 的并恰好就是整个大区间 $I$。此时可以注意到，不可能再有其他的区间出现在 $I_1\sim I_k$ 中了，故 $k=2$。

------------------

有了这个结论，问题就大大简化了。不妨令 $I=[l,r]$，$I_1=[l,y]$，$I_2=[x,r]$（$l<x\leq y<r$）。则 $I_1,I_2$ 的交 $[x,y]$ 必然也是一个好区间，我们先递归地把这个区间内的连边情况处理了。一些可以注意到的性质：

- 不存在某个好区间 $[a,b]$ 满足 $a\leq y$ 且 $y < b < r$。（否则 $[l,b]$ 也是好区间且完全覆盖了 $[l,y]$。）
- 不存在某个好区间 $[a,r]$ 满足 $l<a<x$。（否则完全覆盖 $[x,r]$。）
- 另一侧同理。

此时可以注意到 $[l,x-1]$ 和 $[y+1,r]$ 是互相独立的。我们接下来只讨论 $[y+1,r]$ 一边。

- 如果某个 $[a,r]$ 是好区间，且 $x\leq a\leq y$，那么 $[a,y]$ 是好区间。
- 进一步地，如果某个 $[a,r]$ 是好区间，且 $x\leq a\leq y$，那么对 $x\leq a'\leq a$，$[a',r]$ 的好坏情况必须与 $[a',y]$ 的好坏情况一致。

上面两个结论非常重要，建议读者先仔细想想再往下看。

考虑找到一个最大的 $a\leq y$，使得 $[a,r]$ 是好区间。（这样的 $a$ 一定大于等于 $x$。）考虑这样一个策略：每次我们需要把某个 $[y+1,r]$ 内的连通块和 $[x,y]$ 连通时，都往 $a$ 上连。这样的好处是：只要 $[x,y]$ 内的安排符合输入的数组，那么所有跨过 $[y,y+1]$ 的区间的安排就会自动符合输入的数组。

接下来我们考虑对 $[y+1,r]$ 进行递归。如果它本身就是一个好区间，我们则可以直接递归，并在结束后连边 $(a,r)$ 即可。否则我们如法炮制，找到它的极大好子区间 $J_1,...,J_t$。这里的 $J_1,...,J_t$ 一定两两不交且覆盖整个 $[y+1,r]$。简单讨论一下可知：

- $t=2$：一定无解。
- $t\geq 3$：一种可行的策略为：$J_{t-1},J_t$ 右端点连 $a$，$J_{1},...,J_{t-2}$ 左端点连 $J_t$ 右端点。

$J_1,...,J_t$ 递归下去做即可。综上我们便解决了此题。

如何 $O(n^2)$ 实现：注意到我们递归到的区间两两要么不交要么包含，因而形成一个树形结构，从而每个点至多被包含在 $O(n)$ 个区间内，区间总长度在 $O(n^2)$ 量级。因而暴力扫描即可。下面的代码里为了加速，维护了两个数组 `lp[l][r]` 和 `rp[l][r]`，其中 `lp[l][r]` 表示最大的 $x\in [l,r]$ 使得 $[l,x]$ 是好区间，`rp[l][r]` 则与其对称。

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

bool good[2100][2100];int lp[2100][2100],rp[2100][2100];
vector<pair<int,int> > E;

void Solve(int l,int r)
{
    if(l==r)return;
    int x=rp[l+1][r],y=lp[l][r-1];
    
    if(y<x)
    {
        vector<pair<int,int> > I;
        I.push_back(make_pair(l,y));
        while(y<r)
        {
            I.push_back(make_pair(y+1,lp[y+1][r]));y=lp[y+1][r];
        }
        for(int i=0;i<I.size();i++)Solve(I[i].first,I[i].second);
        E.push_back(make_pair(I[0].first,I.back().second));
        if(I.size()>3)
        {
            E.push_back(make_pair(I[1].first,I.back().second));
            for(int i=2;i<I.size()-1;i++)E.push_back(make_pair(I[0].first,I[i].second));
        }
    }
    else
    {
        Solve(x,y);
        vector<pair<int,int> > I;
        int p=y;while(p<r){I.push_back(make_pair(p+1,lp[p+1][r]));p=lp[p+1][r];}
        for(int i=0;i<I.size();i++)Solve(I[i].first,I[i].second);
        int pos=y;while(!good[pos][r])pos--;
        E.push_back(make_pair(r,pos));//if(r==pos)puts("A");
        if(I.size()>=3)
        {
            E.push_back(make_pair(I[0].first,r));//if(I[0].first==r)puts("B");
            for(int i=1;i<I.size()-1;i++)
            {
                E.push_back(make_pair(I[i].second,pos));//if(I[i].second==pos)puts("C");
            }
        }

        I.clear();p=x;while(p>l){I.push_back(make_pair(rp[l][p-1],p-1));p=rp[l][p-1];}
        reverse(I.begin(),I.end());
        for(int i=0;i<I.size();i++)Solve(I[i].first,I[i].second);
        pos=x;while(!good[l][pos])pos++;
        E.push_back(make_pair(l,pos));//if(l==pos)puts("D");
        if(I.size()>=3)
        {
            E.push_back(make_pair(I.back().second,l));//if(I.back())
            for(int i=1;i<I.size()-1;i++)E.push_back(make_pair(I[i].first,pos));
        }
    }
}

int main()
{
    int TT=0;scanf("%d",&TT);
    while(TT--)
    {
        int n=0;scanf("%d",&n);
        E.clear();
        for(int i=1;i<=n;i++)
        {
            for(int j=i;j<=n;j++)
            {
                char ch='\0';scanf(" %c",&ch);
                good[i][j]=ch=='1';
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=i;j<=n;j++)lp[i][j]=good[i][j]?j:lp[i][j-1];
            for(int j=i;j>=1;j--)rp[j][i]=good[j][i]?j:rp[j+1][i];
        }
        Solve(1,n);
        for(int i=0;i<E.size();i++)printf("%d %d\n",E[i].first,E[i].second);
    }
}
```

---

## 作者：james1BadCreeper (赞：6)

如果有一个比较强的样例，那么这道题就一文不值。但很可惜，这是白日做梦。

所以这是一道很有趣的题。

---

首先观察有没有能直接得出的边，比如说区间 $[i,i+1]$ 是连通的，那么 $(i,i+1)$ 这条边就必定存在。由此不难想到按照区间长度进行枚举，如果要求连通且当前的连边不能让它们连通，那么就连边。

然后会 [RE on 3](https://codeforces.com/contest/1710/submission/267302227)，因为我们找不到足够的边，比如下面这个东西：

![](https://cdn.luogu.com.cn/upload/image_hosting/uy75gl43.png)

我们只能连出来两条边，因为其只有 $[5,6],[1,6]$ 两个连通的区间。

由此发现解其实个能不止一个，中间的点如果只有一个没连的话是没法满足条件的（必然会造成 $[i,i+1]$ 的相邻合法区间），因此要么没有要么两个及以上。假设不合法区间是 $[i,i+k]$，那么可以连 $(i,i+k-1),(i+k,i+1),(i,i+2),\cdots,(i+k,i+k-2)$。

但如果它们中已经有一些连通了，则不能连它们。否则还是会 [RE on 3](https://codeforces.com/contest/1710/submission/267991452)（会连出环）。

由于新建区间只有 $O(n)$ 个，因此时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const int N = 2e3 + 5; 

int n; 
char a[N][N]; 
int fa[N]; 
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void solve(void) {
    cin >> n; 
    for (int i = 1; i <= n; ++i) cin >> a[i] + 1, fa[i] = i; 

    int cnt = 0; 
    for (int j = 1; j <= n; ++j)
        for (int i = 1; i + j - 1 <= n; ++i) if (a[i][j] == '1') {
            int x = j + i - 1; 
            if (find(i) != find(x)) {
                cout << i << " " << x << "\n"; ++cnt; 
                fa[find(i)] = find(x); 
                vector<int> tmp; 
                for (int k = i + 1; k < x; ++k)
                    if (find(k) != find(i)) tmp.push_back(k); 
                assert(tmp.size() != 1); 
                if (tmp.size()) {
                    cout << i << " " << tmp.back() << "\n"; fa[find(i)] = find(tmp.back()); ++cnt; 
                    tmp.pop_back(); 
                    for (int k : tmp) if (find(x) != find(k)) cout << x << " " << k << "\n", fa[find(x)] = find(k), ++cnt; 
                }
            }
        }
    assert(cnt == n - 1); 
}

int main(void) {
    ios::sync_with_stdio(0); 
    int T = 1; cin >> T; 
    while (T--) solve();
    return 0;
}

/*
100001
10000
1000
100
11
1
*/
```

---

## 作者：zac2010 (赞：4)

一个比较显然的思路就是：我们按照右端点从小到大的顺序（右端点相同按左端点从大到小）去考虑每个好的区间。

由于是连通性问题，不难想到用并查集去实时维护连通性。

根据定义，一个好的区间必定对应了一个连通块；我们考虑的是好的区间，所以当前并查集中的每个连通块必定都是一个区间。而在加入某个点前，这个连通块可能是好几个更小的连通块。换句话说，是区间中的某个点，串联起了其它连通块。

有了上述思维方向的转化，正解也就比较自然了。一个区间由好几个子区间组成，假设它们为 $[l_1,r_1],[l_2,r_2],\dots,[l_m,r_m]$。不妨采取分类讨论进行构造（假设当前的区间为 $[l,r]$）：

1. $m=1$

   当前区间已经连通，不作处理。

2. $m=2$

   连接 $(l,r)$。

3. $m=3$

   此时无解。必须得放到更大的区间里去处理才会有解。

4. $m>3$

   连接 $(l,r),(l,r_{m-1})$，以及 $(r_{2},r),(r_{3},r),\dots,(r_{m-2},r)$。

   注意区间拆分中的 $l_1$ 就是 $l$，$r_m$ 即为 $r$。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); ++i)
#define FR(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
const int N = 2010;
int n, t, fa[N]; char e[N][N];
void solve(){
    scanf("%d", &n);
    FL(i, 1, n) scanf("%s", e[i] + (fa[i] = i));
    FL(j, 1, n) FR(i, j - 1, 1){
        if(fa[j] <= i || e[i][j] == '0') continue;
        printf("%d %d\n", i, j);
        if((t = fa[fa[j] - 1]) > i){
            printf("%d %d\n", i, fa[j] - 1);
            for(int u = t - 1; fa[u] > i; u = fa[u] - 1)
                printf("%d %d\n", fa[u], j);
        }
        FR(k, j, i){
            if(fa[k] == i) break;
            fa[k] = fa[i];
        }
    }
}
int main(){
    int T; scanf("%d", &T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：Chen_jr (赞：4)

一个比较容易想到的假做法是按照长度枚举每一个区间，如果两个端点所在的联通块不是一个那么就加端点到端点的边。

然而这样会被下面的东西卡掉：

![](https://cdn.luogu.com.cn/upload/image_hosting/fco41oaq.png)

于是我们发现当两个端点所在的联通块在值域上不连续的时候需要特殊处理。

具体做法可以在并查集中维护最小值与最大值,这样我们就能方便的判断是否需要特殊处理。

特殊处理的过程，我们对两个端点之间的若干联通块选出一个代表元，然后按照类似上面的方法构造：

（这里按照联通块在值域上从小到大的顺序编号）

$1$ 与 $n$ 连边；

$2$ 与 $n$ 连边；

剩下的点在 $1$ 那边造菊花。

因为数据保证有解，所以我们默认这里的 $n$ 是大于等于 $4$ 的。

值得一提的是在选择代表元时，第一个联通块必须选最小元素，最后一个必须选最大元素，如果不这样做，那么会导致不应该联通的区间变的联通，即端点向内移动。

其他区间的代表元是任意的。

```cpp
#include<bits/stdc++.h>


using namespace std;

typedef long long ll;
typedef unsigned long long ull;

inline int read(){
	int x = 0; char c = getchar();
	while(c < '0' || c > '9')c = getchar();
	do{x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}while(c >= '0' && c <='9');
	return x;
}

const int maxn = 2005;
int n;
int f[maxn], mi[maxn], mx[maxn];
char c[maxn];
int fa(int x){return f[x] == x ? x : f[x] = fa(f[x]);}
bool mp[maxn][maxn];
void merge(int x, int y){
	x = fa(x); y = fa(y);
	if(x != y){
		f[y] = x;
		mi[x] = min(mi[x], mi[y]);
		mx[x] = max(mx[x], mx[y]);
	}
}
vector<int>v;
void solve(int l, int r){
	for(int i = l; i <= r; i = mx[fa(i)] + 1)v.push_back(i);
	v.back() = r;
	int ls = v.back(), s = v.size();
	for(int i = 0; i < s - 1; ++i)merge(v[i], ls);
	if(v.size() > 1){
		printf("%d %d\n",v[0], v.back());
		printf("%d %d\n",v[1], v.back());
		v.pop_back();
		for(int i = 2; i < v.size(); ++i)printf("%d %d\n",v[i], v[0]);
	}
	v.clear();
}
void solve(){
	scanf("%d",&n);
	for(int i = 1; i <= n; ++i){
		scanf("%s",c);
		for(int j = i; j <= n; ++j)mp[i][j] = (c[j - i] == '1');
	}
	for(int i = 1; i <= n; ++i)f[i] = mx[i] = mi[i] = i;
	for(int i = 2; i <= n; ++i){
		for(int j = 1; j + i - 1 <= n; ++j){
			int l = j, r = j + i - 1;
			if(mp[l][r] == 0)continue;
			if(fa(l) != fa(r)){
				if(mx[fa(l)] + 1 == mi[fa(r)]){ 
					printf("%d %d\n",l, r);
					merge(l, r);
				}else solve(l, r);
			}
		}
	}
	
}
int main(){
	int q; scanf("%d",&q);
	for(int i = 1; i <= q; ++i)solve();
	return 0;
}

```

$latex$ 已修改

---

## 作者：FutaRimeWoawaSete (赞：4)

**CF1710D sol**

好强的题。

学习的是 @[xcyle](https://www.luogu.com.cn/user/46817) 的题解。

先考虑一种特殊情况：假设联通的区间只有 $l = r$ 和 $l = 1,r = n$ 两种，一种合法的构造是将 $1$ 连到 $3,4,5, \dots, n$，而 $2$ 连到 $n$ 去。

考虑普通的构造，我们发现我们从小的区间往大的区间构造顺序一定是正确的。

若当前枚举到一个区间 $[l,r]$，假设这个区间内暂时还没有连在一起，显然由于枚举的区间从小到大，区间内的连通块肯定也是区间的形式。

我们假设 $l$ 所在区间连通块 $[l',x_1]$，$r$ 所在区间连通块是 $[x_k + 1,r']$，且中间有 $k - 1$ 个连通块。从 $l$ 所在连通块数起，第 $i$ 个连通块形如 $[x_{i - 1} + 1 , x_i]$。

由于当前连通块之间不能互相联通，否则我们在之前枚举小区间时就会合并两两连通块了。

我们尝试这样的构造：

- 对于 $k = 1$，显然连接 $(l,r)$ 是合法的；

- 对于 $k = 2$，无解。我也不知道怎么理性证明~~至少我也没构造出来；~~

- 对于 $k > 2$，将 $(l,r),(l,x_k)$ 以及 $(x_i,r),i \in [2,k)$ 连边。

对于 $k > 2$ 的情况把图展开成这个样子：

[![xlOuVI.png](https://s1.ax1x.com/2022/10/05/xlOuVI.png)](https://imgse.com/i/xlOuVI)

其中三角形就是子树。比较丑陋的图。

可以发现，对于区间上非 $l$ 和 $r$，所处于中间的连通块区间想要和左/右的连通块区间联通必须要经过 $r$，而经过 $r$ 还想联通就必须要经过 $x_k$，从而经过 $l$，而对于 $l$ 和 $r$ 如果想要跨块连也会导致必须要经过互相。

从而解决了这个比较冗杂的问题，巧妙地构造。



---

## 作者：OtoriEmu (赞：2)

这题是在模拟赛上遇到的，有一些不太显然的思路从部分分得到。

首先有一些比较显然的观察（比如直接搞出一条边的条件一类杂而无用的结论），从这些冗杂的结论中看不出任何的可能性，先研究一下样例。

注意到最后一个样例的构造的边，$v-u$ 的值是不减的。出题人故意调整成这个样子显然说不过去……不如往这方面思考。具体的，我们猜测构造方法是从小到大枚举 $v-u$ 的差值构造方案。实际上还能有另一个发现，也即 $(u,v)$ 这个点对应的 $a_{u,v}=1$。

但是仍然不好构造，观察部分分：只有 $n+1$ 个点值为 $1$。这 $n+1$ 个点指的当然是 $n$ 个 $(i,i)$ 以及 $(1,n)$。用手模拟出一个通用的构造方案是：以 $n$ 为根，$1,2$ 为 $n$ 的儿子，其他点为 $1$ 的儿子。容易发现这显然满足条件。

那么再回到这个问题。那么对于一个单独的满足上述限制的包含的结点编号连续的连通块，我们可以使用上面的方法单独构造了。

那么现在整个序列使用上面的方法之后，被拆成了很多个相邻的连通块（当然，$n=3$ 的时候只可能会被拆成两个连通块，但并不影响），现在需要对连通块进行合并。使用之前的发现，从小到大枚举 $v-u$ 的差值进行构造，并且在 $a_{u,v}=1$ 的时候进行一些处理。

如果此时 $u,v$ 不属于同一个连通块，先证明两个连通块 $A,B$ 之间没有其他的连通块。可以形象的理解，假设中间还有另外一个连通块 $C$，那么 $C$ 一定在 $A,B$ 两者间选一个连边。注意到我们是从小到大枚举的差值，那么 $C$ 已经被合并到两者中的一个了。因此 $A,B$ 之间不存在连通块。

再提出一个引论是，对于两个连通块 $A,B$，若 $A \cap B \neq \varnothing$，则 $A \cap B, A \cup B$ 均为合法的连通块，这个结论证明并不困难，不再赘述。这同时引出了我们接下来的构造方法。

假设 $u$ 所在的连通块为 $[l_u,r_u]$，$v$ 所在的连通块为 $[l_v,r_v]$，同时满足 $[u,v]$ 也是连通块。首先可得 $[u,r_u],[l_v,v]$ 是两个合法的连通块，连接 $u,v$ 符合条件，充分性可得。

然后是必要性，不妨先固定边的一个端点为 $u$，另一个端点为 $v'$，若 $v'>v$，则不满足条件；$v'<v$，则会在差值更小的时候 $A,B$ 合并，不符条件。不固定 $u$ 固定 $v$ 的情况同理，同时需要证明两个端点都不在 $u,v$ 上的情况，这个假的比较离谱，就不再多说了。

那么问题就解决了。可能比较突兀，总结一下具体的思路：

- 从小到大枚举边两个端点的差值，判断是否需要建边；   
- 如果需要合并两个连通块：
  - 如果中间有其他的连通块：一定满足一开始说的一种特殊情况，属于边界，可以采取上面的方法构造；   
  - 如果中间没有其他的连通块：连接 $u,v$ 即可。

[测评链接](https://codeforces.com/contest/1710/submission/174689957)。

```cpp
vector<P> Ans;
int a[2005][2005];
int n;
int L[2005],R[2005];
void Solve()
{
	Ans.clear();
	n=read();
	for(int i=1;i<=n;++i)
	{
		for(int j=i;j<=n;++j)
		{
			char c=getchar();
			while(c<'0' || c>'9')	c=getchar();
			a[i][j]=c^'0';
		}
	}
	for(int i=1;i<=n;++i)	L[i]=R[i]=i;
	for(int d=1;d<n;++d)
	{
		for(int u=1;u+d<=n;++u)
		{
			int v=u+d;
			if(a[u][v] && L[u]!=L[v])
			{
				Ans.push_back(mp(u,v));
				bool f=false;
				for(int i=R[u]+1;i<L[v];++i)
				{
					if(L[i]==i)
					{
						if(f)	Ans.push_back(mp(u,i));
						else	Ans.push_back(mp(v,i));
						f=true;
					}
				}
				int l=L[u],r=R[v];
				for(int i=l;i<=r;++i)	L[i]=l,R[i]=r; 
			}
		}
	}
	for(P st:Ans)	write(st.first),putchar(' '),write(st.second),puts("");
}
```


---

## 作者：Liuxizai (赞：2)

[My Blog](https://liuxizai.ac.cn/archives/solution-cf1710d.html)

## Description

根据以下信息构造一棵树：

- 树的节点个数为 $n$，编号为 $1\sim n$。
- 对于每个编号区间 $[l,r]$ 给出是否构成连通块。

$n\le 2000$

## Solution

难得做出了 3400 的构造，很有意思的题目。

从小到大考虑每个好区间。

当 $r=l+1$ 时，如果构成连通块，则必然有 $l\to l+1$ 的连边。

对于长度为 $d$ 的好区间 $[l,r]$，此时所有长度 $<d$ 的好区间都已经满足题意，首先由于我们的构造方式，所有的连通块都是区间。假如 $l,r$ 处于不同的连通块，我们会连一条 $l\to r$ 的边将两个连通块合并，注意此时在 $l,r$ 所在的连通块之间还可能存在一些散块，我断言散块的数量不可能为 $1$，否则显然无解，既然散块的数量大于 $1$，容易想到构造左往右连、右往左连这样的交叉连边，这样如果不同时包含 $l,r$，任取若干散块，他们仍然不连通，于是就保证了不会破坏较小区间的正确性。

实现细节略去，代码十分易懂。

值得一提的是，枚举所有好区间的复杂度是 $\mathcal O(n^2)$，而对于每个尚未连通的好区间，我们都暴力遍历了区间中的每个点检查连通性，尽管如此，由于每次暴力遍历都至少会连一条边，而树上的总边数是 $n-1$，故总复杂度是正确的 $\mathcal O(n^2)$。

## Code

```cpp
namespace Main{
	const int N = 2005;
	int t, n, fa[N];
	char con[N][N];
	int get(int x){
		if(fa[x] == x) return x;
		return fa[x] = get(fa[x]);
	}
	void unite(int x, int y){
		fa[get(x)] = get(y);
	}
	void Main(){
		input(t);
		while(t--){
			input(n);
			for(int i = 1; i <= n; i++) scanf("%s", con[i] + 1);
			for(int i = 1; i <= n; i++) fa[i] = i;
			for(int i = 2; i <= n; i++){
				for(int j = 1; j + i - 1 <= n; j++){
					int k = j + i - 1;
					if(con[j][i] != '1' || get(j) == get(k)) continue;
					unite(j, k);
					write(j), putchar(' '), write(k), puts("");
					bool fir = true;
					for(int p = j + 1; p < k; p++){
						if(get(p) != get(j)){
							if(fir){
								write(p), putchar(' '), write(k), puts("");
								unite(p, k);
								fir = false;
							}
							else{
								write(p), putchar(' '), write(j), puts("");
								unite(p, j);
							}
						}
					}
				}
			}
		}
		return;
	}
}
```



---

## 作者：liyixin0514 (赞：1)

# [CF1710D Recover the Tree](https://www.luogu.com.cn/problem/CF1710D)

[更好的阅读体验](https://www.cnblogs.com/wingheart/p/18719695)

## 题意

根据题意构造出一棵合法的树。

有 $n$ 个点。$a_{i,j}=\{0,1\},i \le j$ 表示编号在 $[i,j]$ 的点是否连通。

$n \le 2000$。

保证有解。

## 思路

显然是先考虑小区间，然后合并到大区间。

思考只有 $a_{1,n}=1$ 的情况怎么做。

$i,i+1$ 不能连边。$i,i+k(k>1)$ 可以连边。但是不可以有更小的区间连通。

一种构造方案是连 $(2,n),(1,i),3 \le i \le n-1$。

当 $n=3$ 时无解。

----------

考虑一般情况。

考虑按顺序一个一个加点。现在加到点 $n$。

由于树的连通块形式，如果 $[l_1,r_1],[l_2,r_2]$ 连通。且 $l_2 \le r_1$，那么 $[l_2,r_1],[l_1,r_2]$ 也是连通的。即交和并都是连通的。

那么此时 $[1,n-1]$ 已经有了若干个极大的连通区间。

假设 $a_{i,n}=1$，如何合并连通块。

参考之前的构造，首先连 $(i,n)$，如果中间还有多个连通块，然后连 $n$ 和第二块连通块的头，然后连 $i$ 和其他连通块的尾。

小到大枚举 $n$，从大到小枚举 $i$ 容易证明是对的。怎么想到的我就不知道了。

时间复杂度 $O(n^2)$。

## code

好写的。

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace wing_heart {
	constexpr int N=2e3+7;
	#define gc getchar
	typedef pair<int,int> pii;
	#define fi first 
	#define se second
	int t;
	int n;
	char a;
	vector<int> vec[N];
	bool cmp (int a,int b) { return a>b; }
    void main() {
		sf("%d",&t);
		while(t--) {
			sf("%d",&n);
			rep(i,1,n) vec[i].clear();
			rep(i,1,n) rep(j,i,n) {
				a=gc();
				while(a!='1' && a!='0') a=gc();
				if(a=='1' && j!=i) vec[j].push_back(i);
			}
			rep(i,1,n) sort(vec[i].begin(),vec[i].end(),cmp);
			stack<pii> que;
			rep(r,1,n) {
				que.push({r,r});
				for(int x : vec[r]) {
					vector<pii> tmp;
					if(que.top().fi<=x) continue;
					while(que.size() && que.top().se>=x) tmp.push_back(que.top()), que.pop();
					pf("%d %d\n",x,r);
					if(tmp.size()>2) pf("%d %d\n",r,tmp[tmp.size()-2].fi);
					rep(i,1,(int)tmp.size()-3) pf("%d %d\n",x,tmp[i].se);
					que.push({tmp.back().fi,r});
				}
			}
		}
    }
}
int main() {
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif
    wing_heart :: main();
}
```

---

## 作者：Otomachi_Una_ (赞：1)

**[D. Recover the Tree](https://www.luogu.com.cn/problem/CF1710D)（8）**

神仙构造。

考虑从小往大枚举每个好的区间，用并查集维护每个元素所在区间，那么一个好的区间 $[l,r]$ 经过枚举后应该把 $l,r$ 之间的元素全部合并。设 $l,r$ 不在一个集合，假设 $[l,r]$ 之间的元素分别属于连通块 $S_1,S_2,\dots,S_k$。

- 如果 $k=2$，直接连 $l,r$ 即可。
- 如果 $k=3$，我们发现无论 $S_2$ 连向 $l,r$ 都会出现一个更小的好的区间，也就是不会出现这样的情况。
- 否则，我们可以让 $S_2$ 连 $r$，$S_3,S_4,\dots,S_{k-1}$ 连 $l$，再连 $l,r$。

正确性感性理解。

[submission](https://codeforces.com/contest/1710/submission/220871680)

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1710D)

**题目大意**

> 你需要构造一棵 $n$ 个点的树，使得对于每个子区间 $[l,r]$，这些点在树上的连通性和输入的 $a_{l,r}$ 一致。
>
> 数据范围：$n\le 2000$，保证有解。

**思路分析**

考虑逐步加点，那么加入 $[1,n-1]$ 后会形成一个森林。

那么考虑所有 $a_{x,n}=1$ 的区间 $[x,n]$，按 $x$ 从大到小依次加入即可。

首先 $[x,n-1]$ 的点构成若干个连通块，我们要求将他们连通，且任何一个子区间都不连通。

如果 $[x,n-1]$ 中只有一个点，那么直接和 $n$ 相连，否则设这些连通块排序后为 $b_1\sim b_q$。

那么 $q=2$ 时无解，否则 $b_1,b_2$ 和 $n$ 相连，$b_{3}\sim b_q$ 和 $b_1$ 相连即可。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2005;
int n,p[MAXN];
char f[MAXN][MAXN];
void solve() {
	cin>>n,iota(p+1,p+n+1,1);
	for(int i=1;i<=n;++i) for(int j=i;j<=n;++j) cin>>f[i][j];
	for(int r=1;r<=n;++r) for(int l=r-1;l;--l) if(f[l][r]=='1'&&l<p[r]) {
		cout<<l<<" "<<r<<"\n";
		if(p[p[r]-1]>l) {
			cout<<p[r]-1<<" "<<l<<"\n";
			for(int i=p[p[r]-1]-1;p[i]>l;i=p[i]-1) cout<<i<<" "<<r<<"\n";
		}
		for(int i=r;i>l;--i) p[i]=p[l];
	}
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

容易想到按照区间大小合并，因为 $[l,r-1]$ 的限制显然比 $[l,r]$ 的限制更严格，参考 $l$ 到 $r-2$ 的链后接上 $r$ 再接上 $r-1$，此时不满足 $[l,r-1]$ 但是满足 $[l,r]$。

**容易发现，在任意时刻，所有的连通块一定呈区间的形式。**

于是我们先求出 $l,r$ 所在的区间。

如果它们在同一个区间里，那么它们就已经在一个连通块里了，此时不操作即可。

否则我们我们假设 $l$ 在区间 $i_1$，$r$ 在区间 $i_k$，区间 $i$ 为 $[L_i,R_i]$。

若 $k=2$，那么只需要向 $l,r$ 连边即可，否则无论怎么连，$[l,r]$ 都会少元素。

先考虑一个简单的情况，只有 $[1,n]$ 为联通块（单元素区间不考虑），那么我们只需要让 $1$ 向 $3,\cdots,n$ 连边，$2$ 向 $n$ 连边即可。

那么类似地，我们只需要让 $l$ 向 $r$ 连边，$R_{i_2}$ 向 $r$ 连边，$R_{i_3,\cdots,i_{k-1}}$ 向 $l$ 连边即可。

注意单次操作完之后区间会合并，上述操作只涉及到了 $R$，那么相当于我们要维护一个能支持动态删除 $R$ 的数据结构，`vector` 即可，因为每个元素只会删除一次，单次删除最多 $O(n)$，所以总的复杂度为 $O(n^2)$。然后你的所有的迭代器在遍历过一次之后都会删除，所以这里是 $O(n)$ 的。

其实你会发现讨论了那么多，代码其实很简单。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=2005;
int T,n;
char c[N][N];
vector<int> v;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int l=1;l<=n;++l) for(int r=l;r<=n;++r) cin>>c[l][r];
		v.clear(),v.shrink_to_fit(),v.emplace_back(0);
		for(int i=1;i<=n;++i) v.emplace_back(i);
		for(int len=1;len<=n;++len) for(int l=1,r=len;r<=n;++l,++r){
			if(c[l][r]=='1'){
				auto itl=lower_bound(v.begin(),v.end(),l),itr=lower_bound(v.begin(),v.end(),r);
				for(auto it=itl;it<itr;++it){
					if(it==itl) cout<<l<<' '<<r<<endl;
					else if(it==itl+1) cout<<r<<' '<<(*it)<<endl;
					else cout<<l<<' '<<(*it)<<endl;
				}
				v.erase(itl,itr);
			}
		}
	}
	return 0;
}
```

---

