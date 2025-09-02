# The Child and Zoo

## 题目描述

Of course our child likes walking in a zoo. The zoo has $ n $ areas, that are numbered from $ 1 $ to $ n $ . The $ i $ -th area contains $ a_{i} $ animals in it. Also there are $ m $ roads in the zoo, and each road connects two distinct areas. Naturally the zoo is connected, so you can reach any area of the zoo from any other area using the roads.

Our child is very smart. Imagine the child want to go from area $ p $ to area $ q $ . Firstly he considers all the simple routes from $ p $ to $ q $ . For each route the child writes down the number, that is equal to the minimum number of animals among the route areas. Let's denote the largest of the written numbers as $ f(p,q) $ . Finally, the child chooses one of the routes for which he writes down the value $ f(p,q) $ .

After the child has visited the zoo, he thinks about the question: what is the average value of $ f(p,q) $ for all pairs $ p,q $ $ (p≠q) $ ? Can you answer his question?

## 说明/提示

Consider the first sample. There are $ 12 $ possible situations:

- $ p=1,q=3,f(p,q)=10 $ .
- $ p=2,q=3,f(p,q)=20 $ .
- $ p=4,q=3,f(p,q)=30 $ .
- $ p=1,q=2,f(p,q)=10 $ .
- $ p=2,q=4,f(p,q)=20 $ .
- $ p=4,q=1,f(p,q)=10 $ .

Another $ 6 $ cases are symmetrical to the above. The average is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/58ce2a366aa42eff918fbf0b8467c9ccbcf9601e.png).

Consider the second sample. There are $ 6 $ possible situations:

- $ p=1,q=2,f(p,q)=10 $ .
- $ p=2,q=3,f(p,q)=20 $ .
- $ p=1,q=3,f(p,q)=10 $ .

Another $ 3 $ cases are symmetrical to the above. The average is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF437D/ecc6155982485fab22801f99d7326020bda06f7b.png).

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 3
2 3
4 3
```

### 输出

```
16.666667
```

## 样例 #2

### 输入

```
3 3
10 20 30
1 2
2 3
3 1
```

### 输出

```
13.333333
```

## 样例 #3

### 输入

```
7 8
40 20 10 30 20 50 40
1 2
2 3
3 4
4 5
5 6
6 7
1 4
5 7
```

### 输出

```
18.571429
```

# 题解

## 作者：hs_black (赞：5)

模拟赛上出了此题， 大概是本蒟蒻唯一ac的题了

考场上第一眼康到这道题时， 因为只涉及路径上最小值最大的问题， 所以想到了货车运输， 跑出它的最大生成树，由最大生成树的性质可知， f(p, q） 必定在新建的树上的路径上

题目中让求所有点对的f值之和， 好像不太好求， 所以我们分别考虑每条边对答案的贡献。 先将树上的边按边权从大到小排序，使用并查集维护联通块的大小， 一个一个加边， 它对答案的贡献就是两端点联通块大小的乘积再乘上新边边权.

何哉？ 因为边权是从大到小排序的， 所以两联通块中的边权值均大于新边。 它的权值是最小的， 所以左端点所在联通块的点集到右端点所在联通块的点集的f值均为新边的边权。

最后， 发现最大生成树的过程和算答案的过程可以合并，详情见代码,还是很好理解的

 _talk is cheap, show me the code_   
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<algorithm>
using namespace std;
template <typename T> 
void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	x *= f;
}
const int N = 100500;
const int M = 1005000;

struct node{
	int x, y;
	int w;
	bool operator < (const node &i) const {
		return w > i.w;
	}
}e[M];

long long n, m;


int f[N], a[N];
long long ans = 0;
int siz[N];
int find(int x) {
	if (x == f[x]) return x;
	return f[x] = find(f[x]);
}


int main() {
	read(n), read(m);
	for (int i = 1;i <= n; i++) f[i] = i, siz[i] = 1;
	for (int i = 1;i <= n; i++) read(a[i]);
	for (int i = 1;i <= m; i++) {
		int x, y;
		read(x), read(y);
		e[i] = (node){x, y, min(a[x], a[y])};
	}
	sort(e + 1,e + m + 1);
	for (int i = 1;i <= m; i++) {
		int fx = find(e[i].x), fy = find(e[i].y);
		if (fx == fy) continue;
		f[fx] = fy;
		ans += (long long)siz[fx] * siz[fy] * e[i].w;
		siz[fy] += siz[fx];
	}
	cout << setprecision(6) << (long double) ans * 2  / (long double)(n * (n-1)) << endl;
	return 0;
}

```

---

## 作者：Star_Cried (赞：3)

## CF437D The Child and Zoo

### 题意

给定一个无向图，求所有点对间所有简单路径上最小点权的最大值的平均值。

### 思路

1. 首先，我们可以将点权转移到边权上，边权为两端点点权的较小值。正确性显然。
2. 然后，对于任意两个点之间的贡献，只有路径上含最大点权的简单路径有贡献，于是就可以把无向图转变为最大生成树。任意两个点间的贡献显然是在最大生成树上路径的最大边权。
3. 考虑对于一条边的贡献，其实就是对于当前两端点连通块的大小相乘再乘该边边权。计算后合并两个连通块。

完了，一个最大生成树即可。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10;
	int n,m,siz[maxn],fa[maxn],a[maxn];
	double ans;
	struct edge{
		int u,v,d;
		inline bool operator < (const edge &zp) const{return d>zp.d;}
	}e[maxn];
	inline void onion(int x,int y,int k){
		if(siz[x]<siz[y])swap(x,y);
		ans+=1.0*siz[x]*siz[y]*k;
		fa[y]=x,siz[x]+=siz[y];
	}
	int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
	inline void work(){
		n=read(),m=read();
		for(int i=1;i<=n;i++) a[i]=read(),fa[i]=i,siz[i]=1;
		for(int u,v,i=1;i<=m;i++) u=read(),v=read(),e[i]=(edge){u,v,min(a[u],a[v])};
		sort(e+1,e+1+m);
		for(int cnt=0,i=1;i<=m and cnt<=n-1;i++){
			int u=find(e[i].u),v=find(e[i].v);
			if(u!=v)
				onion(u,v,e[i].d),cnt++;
		}
		printf("%.5lf\n",ans/n/(n-1)*2);
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：Doveqise (赞：1)

 ~~我在怀疑这道题的颜色~~  
 来补一下模拟赛的T1  
 我就按着模拟赛的数据范围给出一步一步的做法。  
 把模拟赛数据范围贴上来（  
 	
   对于10%的测试数据，满足$2 \leq n \leq 10 , n - 1 \leq m \leq 20$  
   对于30%的测试数据，满足$2 \leq n \leq 200 , n - 1 \leq m \leq 1000$  
   对于50%的测试数据，满足$2 \leq n \leq 1000 , n - 1 \leq m \leq 20000$  
   对于100%的测试数据，满足$2 \leq n \leq 100000 , n - 1 \leq m \leq 1000000$   
   $ 0 \leq a_i \leq 100000 ,1 \leq x_i,y_i \leq n,(x_i \neq y_i)$，保证是连通图且没有重边。  
   
 解法1：  
 暴力枚举点跑n遍$Floyd$  
 分数：10pts（这时间复杂度有点惨 
 
 解法2：  
 随便想想珂以暴力枚举两点枚举所有路径  
 分数：30pts  
 
 解法3：  
 从每个点跑$BFS$  
 分数：50pts  
 
 解法4：  
 并查集  
 通过观察可得所有的路径必在最大生成树上。  
 证明：若有一条满足题意的连接$x$与$y$的路径，且不在最大生成树上，那么由于这条路径不在最大生成树上，必定至少有一条边的边权$ \leq $最大生成树上的边权，那么选择最大生成树上的路径不会更劣  
 $Q.E.D.$  
 然后$Kruskal$跑最大生成树统计答案即可。  
 分数：100pts  
 
 细节见代码。  
 ```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 1e6 + 5;
typedef long long ll;
ll n, m, ans;
int val[maxn], s[maxn], fa[maxn], siz[maxn];
int hd[maxn], tot, vis[maxn];
struct edge
{
    int nxt, to;
} ed[maxm << 1];
int findfa(int x)
{
    return fa[x] == x ? x : fa[x] = findfa(fa[x]);
}
bool cmp(int a, int b)
{
    return val[a] > val[b];
}
void addedge(int x, int y)
{
    ed[++tot] = (edge){hd[x], y};
    hd[x] = tot;
}
signed main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; siz[i] = 1, i++)
        scanf("%d", &val[s[i] = fa[i] = i]);
    sort(s + 1, s + n + 1, cmp);
    for (int i = 1, a, b; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        addedge(a, b);
        addedge(b, a);
    }
    for (int u = 1; u <= n; u++)
    {
        ll res = 0;
        for (int i = hd[s[u]]; i; i = ed[i].nxt)
        {
            int v = ed[i].to;
            if (!vis[v])
                continue;
            int p = findfa(s[u]), q = findfa(v);
            if (p == q)
                continue;
            res += 1ll * siz[p] * siz[q];
            fa[p] = q;
            siz[q] += siz[p];
        }
        ans += 1ll * res * val[s[u]];
        vis[s[u]] = 1;
    }
    printf("%lf\n", ans * 2.0 / (n * (n - 1)));
    return 0;
}
```


---

## 作者：DrAlfred (赞：0)

摘要：差分，并查集，数学

[传送门：https://www.luogu.com.cn/problem/CF437D](https://www.luogu.com.cn/problem/CF437D)

## 题意

给定一张 $n$ 个点 $m$ 条边的无向图，点有点权。定义 $f(p,q)$ 为所有 $p$ 到 $q$ 的简单路径的最小值的最大值，求 $\frac{\sum_{p, q, p\ne q}f(p, q)}{n(n - 1)}$。

## 分析思路

来补充一个和同学 duel 想到的差分做法。

考虑对点权从大到小排序。如果我们能统计出大于等于某个值 $w$ 的 $f(p, q)$ 的对数 $cnt_w$，那么就可以做到差分统计答案，即为 $\sum_{w = 1}^{\max a - 1} (cnt_{w + 1} - cnt_w) \cdot w$。

考虑怎么算出 $cnt$。把所有点按照点权离线下来，枚举 $w$ 的时候顺便加入所有点权小于等于 $w$ 的点之间的临边，用并查集维护连通性。可以发现有 $cnt_w = \sum siz_u^2$，其中 $u$ 是每个连通块的根。合并的同时维护 $cnt$ 即可。

时间复杂度 $O(n + m)$，可以通过。这类题目可以把两个点的点权 merge 转化为边权做也可以单独对于点权考虑，[相似例题链接](https://codeforces.com/gym/105692/problem/F)。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int N = 100010;
std::vector<int> G[N];
long long lst, tot, ans;
int n, m, a[N], b[N], fa[N], siz[N];
inline int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline i64 comb(i64 x) { return x * x; }
inline void merge(int u, int v) {
    int fu = find(u), fv = find(v);
    if (fu == fv) return;
    tot -= comb(siz[fu]) + comb(siz[fv]);
    fa[fu] = fv, siz[fv] += siz[fu];
    tot += comb(siz[fv]);
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    deque<array<i64, 2>> Q;
    optimizeIO(), cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], b[i] = a[i];
        Q.push_back({a[i], i});
        fa[i] = i, siz[i] = 1;
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    tot = lst = n;
    sort(Q.begin(), Q.end(), greater<>());
    sort(b + 1, b + 1 + n, greater<>());
    for (int i = 1; i <= n; i++) {
        while (!Q.empty() && Q.front()[0] >= b[i]) {
            for (auto &v : G[Q.front()[1]]) {
                // 不用担心漏连，如果这次没连证明 a[v] < b[i], 
                // 枚举到较小的 i 之后总会会从 v 连接到 Q.front()[1] 的
                if (a[v] < b[i]) continue; 
                merge(v, Q.front()[1]);
            }
            Q.pop_front();
        }
        ans += (tot - lst) * b[i], lst = tot;
    }
    cout << fixed << setprecision(6);
    cout << 1.0 * ans / n / (n - 1) << endl;
    return 0;
}

```

---

## 作者：Milmon (赞：0)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF438B) & [Problem](//www.luogu.com.cn/problem/CF437D)

## 题目大意

- 给定一个 $n$ 个点，$m$ 条边的无向图，编号为 $i$ 的点的点权为 $a_i$。

- 设 $f(u,\ v)$（$1\leq u,\ v\leq n,\ u\not=v$）表示 **一条 $u$ 到 $v$ 路径上最小点权** 的最大值。

- 求所有点对 $u,\ v$ 的 $f(u,\ v)$ 值的平均数。

- $2\leq n\leq 10^5$，$0\leq m,\ a_i\leq 10^5$

## 解题思路

假设本题给定的是每条边的边权而不是每个点的点权，则对于任意两个点 $u\not=v$，当 $u$ 到 $v$ 的一条路径上的最小边权最大时，易得这条路径在该图的最大生成树上。

**如何将点权转化成边权？** 为了转化后等价于点权的情况，对于任意一条路径，路径上点的最小权值必须与路径上边的最小权值。考虑特殊情况，若一条路径上只有一条边，设端点为 $u$ 和 $v$，边权为 $val$，则由上面得到的结论，有 $w=\min(a_u,\ a_v)$。易证路径长度为其他值时也符合条件。

最后考虑答案。分析每条边对答案的贡献。使用并查集，边两边的节点中各选一个点，故贡献为两边集合大小之积再乘上边权所得的值。由于求的是平均数，所以最后记得除以 $\dbinom n2$。

时间复杂度 $\Theta(n+m\log n)$。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int n,m,a[100001];
struct Edge{
    int u,v,val;
    inline bool operator<(Edge tmp)const{
        return val>tmp.val;
    }
}edge[100001];

int father[100001],size[100001];
int find(int x){
    if(father[x]!=x)father[x]=find(father[x]);
    return father[x];
}

long long answer;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),father[i]=i,size[i]=1;
    for(int i=1;i<=m;i++){
        int x,y; scanf("%d%d",&x,&y);
        edge[i]={x,y,min(a[x],a[y])};
    }
    sort(edge+1,edge+1+m);
    for(int i=1;i<=m;i++){
        int u=find(edge[i].u),v=find(edge[i].v);
        if(u!=v){
            answer+=(long long)edge[i].val*size[u]*size[v];
            father[u]=v,size[v]+=size[u];
        }
    }
    printf("%.4lf\n",answer/(n*(n-1ll)/2.0));
    return 0;
}
```

---

## 作者：enyyyyyyy (赞：0)

并查集。先给一段模板并查集：
```cpp
ll find(ll x) {
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
```
用函数调用的。再加上分析，得知是最大生成树。[P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)，双倍经验！再把路权值从大到小排序，修改最小生成树代码，最终可得：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll n,m,w[1000005],W[1000005],f[1000005];
db ans;
struct node {
	ll x,y,w;
		bool operator<(const node &_)const{
		return w> _.w;
	}
} e[1000005];
ll find(ll x) {
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
int main() {
	n=read(),m=read();
	for(ll i=1; i<=n; i++) w[i]=read();
	for(ll i=1; i<=m; i++) e[i].x=read(),e[i].y=read(),e[i].w=min(w[e[i].x],w[e[i].y]);
	sort(e+1,e+1+m);
	for(ll i=1; i<=n; i++) W[i]=1,f[i]=i;
	for(ll i=1; i<=m; i++) {
		ll fx=find(e[i].x),fy=find(e[i].y);
		if(fx==fy) continue;
		ans+=(db)W[fx]*W[fy]*e[i].w;
		W[fx]+=W[fy],f[fy]=fx;
	}
	printf("%.6lf",(db)ans*1.0*2/n/(n-1));//注意6位小数
	return 0;
}
```


---

