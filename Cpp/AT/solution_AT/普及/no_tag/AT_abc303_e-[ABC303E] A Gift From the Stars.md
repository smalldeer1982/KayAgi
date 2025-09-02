# [ABC303E] A Gift From the Stars

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc303/tasks/abc303_e

以下の条件を満たす $ k+1 $ 頂点 $ k $ 辺のグラフをレベル $ k\ (k\geq\ 2) $ の星と呼びます。

- ある $ 1 $ つの頂点が、他の $ k $ 個の頂点と $ 1 $ 本ずつ辺で結ばれている。それ以外の辺は存在しない。
 
高橋君は、はじめ何個かの星からなるグラフを持っていました。そして、以下の手続きを全てのグラフの頂点が連結になるまでくり返し行いました。

- 持っているグラフの頂点から二つの頂点を選ぶ。このとき、選んだ二つの頂点の次数は共に $ 1 $ であり、かつ選んだ二つの頂点は非連結である必要がある。選んだ二つの頂点を結ぶ辺を張る。
 
その後、高橋君は手続きが終了した後のグラフの頂点に、適当に $ 1 $ から $ N $ の番号を付けました。このグラフは木となっており、これを $ T $ と呼びます。$ T $ には $ N-1 $ 本の辺があり、 $ i $ 番目の辺は $ u_i $ と $ v_i $ を結んでいました。

その後高橋君は、はじめ持っていた星の個数とレベルを忘れてしまいました。$ T $ の情報からはじめ持っていた星の個数とレベルを求めてください。

## 说明/提示

### 制約

- $ 3\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ u_i,\ v_i\leq\ N $
- 与えられるグラフは、問題文中の手続きによって得られる $ N $ 頂点の木
- 入力は全て整数
 
### Sample Explanation 1

以下の図のように、$ 2 $ つのレベル $ 2 $ の星から $ T $ は得られます。 !\[\](https://img.atcoder.jp/abc303/59ab8e04c23d5f727300be7544b1df7e.png)

## 样例 #1

### 输入

```
6
1 2
2 3
3 4
4 5
5 6```

### 输出

```
2 2```

## 样例 #2

### 输入

```
9
3 9
7 8
8 6
4 6
4 1
5 9
7 3
5 2```

### 输出

```
2 2 2```

## 样例 #3

### 输入

```
20
8 3
8 18
2 19
8 20
9 17
19 7
8 7
14 12
2 15
14 10
2 13
2 16
2 1
9 5
10 15
14 6
2 4
2 11
5 12```

### 输出

```
2 3 4 7```

# 题解

## 作者：0xyz (赞：8)

我觉得这一题甚至比 D 题好想。这里的星星其实就是菊花图，一个 $k$ 级的星星就是一个度数为 $k$ 的点，向 $k$ 个度数为 $1$ 的点各连了一条边。我们发现，这个人在连接 $2$ 个星星时，只会连接度数为 $1$ 的点，那么，新连接的点度数一定不会超过 $2$。

所以我们可以得出结论：对于最后的图中度数大于 $2$ 的点，如果它度数为 $k$，那么它一定是原本就有的一个 $k$ 级星星的中心。所以我们将所有这样的点以及与它们直接相邻的点归入到 $k\ge 3$ 级的星星后，剩下的所有点都属于一些 $2$ 级星星。注意到 $2$ 级星星有 $3$ 个点，所以最后我们再往答案数组里放进剩下的点数除以 $3$ 个 $2$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,s,d[200010],c=0,a[200010];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;s=n;
	for(ll i=1,x,y;i<n;i++){
		cin>>x>>y;
		d[x]++;d[y]++;
	}
	for(ll i=1;i<=n;i++)
		if(d[i]>=3)a[++c]=d[i],s-=d[i]+1;
	for(ll i=1;i<=s/3;i++)a[++c]=2;
	sort(a+1,a+c+1);
	for(ll i=1;i<=c;i++)cout<<a[i]<<' ';
	return 0;
}
```

---

## 作者：MYiFR (赞：3)

### 题目大意
首先定义星：

$n$ 阶的星就是由一个点，向外连出 $n$ 条无向边所形成的图形，其中 $n\geq2$。

[![p9Xml1x.png](https://s1.ax1x.com/2023/05/29/p9Xml1x.png)](https://imgse.com/i/p9Xml1x)

这是 $6$ 阶的星。

Tak 有若干颗星，每次他会选择两个度为 $1$ 且不连通的点，用无向边连接这两个点，直到整个图成为一个连通图，确切地说是一颗树。

给你一棵树，Tak 用若干颗星按照上述的方法连接成给定的树，求出每一颗星的大小，升序输出。

### 解题思路
首先可以注意到这棵树它一定有叶子节点，而叶子节点在原图中一定是某个星星边上那一圈的点之一，那么这个点所连向的点一定就是这颗星星的中心，中心所连向的点都属于这颗星星。

找出一颗星星之后就是与它相邻的星星。对于一颗星星周围的点之一，它一定连向中心，除此之外，还**有可能**连向另一颗星星的边缘，然后又回到了第一步……。

### AC 代码
``` cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<db,db>
#define F first
#define S second
using namespace std;
const int N=3e5+5;
int n,u,v,fa[N],ans,pos1,pos2,cnt[N];
vector<int> e[N],fn;
void dfs1(int cur){
	for(int to:e[cur]){
		if(to!=fa[cur]){
			fa[to]=cur;
			dfs1(to);
		}
	}
}
void dfs2(int cur,int f,int flg){
	cnt[cur]=flg;
	for(int to:e[cur]){
		if(to!=f){
			dfs2(to,cur,(flg+1)%3);
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;++i){
		if(e[i].size()==1){
			pos1=i;
		}
		else{
			pos2=i;
		}
		if(pos1 && pos2) break;
	}
	dfs1(pos2);
	dfs2(pos1,0,0);
	for(int i=1;i<=n;++i){
		if(cnt[i]==1){
			fn.push_back(e[i].size());
		}
	}
	sort(fn.begin(),fn.end());
	for(int to:fn) printf("%d ",to);
	return 0;
}
//Ltwcfm.
```

---

## 作者：Z_X_D_ (赞：2)

由于菊花图的等级 $k\ge2$ 的，连接结点只会连度数为 $1$ 的结点，所以每个菊花图只有叶结点能连到其它菊花图的叶结点上，且每个非中心结点的度最多是 $2$，而每个菊花图中心结点的度，也就是等级 $k$，都是大于等于 $2$ 的，所以度大于 $2$ 的结点可以确定一定是菊花图中心，而这个结点的度就是菊花图的等级 $k$。

因此可以对所有 $n$ 个节点的度进行统计并从大到小排序，然后从大到小记录并让结点总数 $n$ 一直减去当前最大度数 $+1$ 也就是 $k+1$ 个结点直到 $n=0$，如果 $n$ 有剩余就用 $2$ 补齐结点数，最后对记录的度数从小到大输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010],b[100010],s;
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	int n,i,x,y;
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		a[x]++;
		a[y]++;//统计结点的度
	}
	sort(a+1,a+n+1,cmp);//从大到小对所有度的结点排序
	for(i=1;n>0;i++)
	{
		n-=a[i]+1;//减结点数防止多记
		b[s++]=a[i];//记录等级k
	}
	s--;
	for(i=s;i>=0;i--)//逆序输出
		printf("%d ",b[i]);
	return 0;
}
```

---

## 作者：Register_int (赞：1)

个人认为思维量最小且最好写的做法。

两个菊花间的距离都为 $2$，所以从一个度数为 $1$ 的点对原树进行 $0/1/2$ 染色（也可以理解为每个点的深度 $\bmod\:3$），为 $1$ 的点就是所有菊花的中心。桶排即可做到 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct edge {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], deg[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot, deg[u]++;
}

int dep[MAXN], cnt[MAXN];

inline 
void dfs(int u, int f) {
	if (dep[u] == 1) cnt[deg[u]]++;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (v == f) continue;
		dep[v] = (dep[u] + 1) % 3, dfs(v, u);
	}
}

int n;

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	for (int i = 1; i <= n; i++) if (deg[i] == 1) { dfs(i, 0); break; }
	for (int i = 1; i < n; i++) for (; cnt[i]--; ) printf("%d ", i);
}
```

---

## 作者：wizardMarshall (赞：1)

[$Link$](https://atcoder.jp/contests/abc303/tasks/abc303_e)

23.5.29：感谢@tangguochao 提醒，将 $1$ 的特判放进标记父亲的位置（之前可能因为由于数据没有 $1$ 为中心点的阶数大于 $2$ 的花而水过去了）。

## $Start$

题意简述为：一棵树由若干个花组成，$n$ 阶的花表示有 $n$ 个点直接连向中心点。如，$5$ 阶的花即为下图：

![5阶](https://cdn.luogu.com.cn/upload/image_hosting/z4aoxcvv.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

若干个花由他们叶节点相连，需要求出这些花的阶数（从小到大排序）。易证答案是唯一的。

## $Tack$

根据对数据与图的观察，我们可以得出一个结论：对于所有的叶节点，它的度数一定小于等于 $2$。

因为对于一个叶节点，它最多只有两条边，一条是连向中心点的，一条是连接其他花的。

因此我们可以得出一个初步的结论：对于度数大于 $2$ 的点，它一定是花的中心点。于是我们就可以存储它的度数为花的阶数，同时将它与所有跟它有直接连边的点打上标记，意为当前点已经包含在某一个花内。

但是，这个方法有着局限性：对于阶数为 $2$ 的花，它没有办法判定。例如第一个样例：

```
6
1 2
2 3
3 4
4 5
5 6
```

其图构建出来后是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/dczpp02l.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

我们可以看出，它是两个二阶的花连在一起，形成了一条链。但目前这个方法还不能判定这些二阶的花。

幸好，这个题里给定的图都是符合条件的，不会有违法情况出现，因此剩下的这些点一定都是在二阶花内的点。

由于二阶花的点数为 $3$，因此我们将剩下的点的个数除以 $3$，得到的就是二阶花的个数。

## $Code$

```
#include <bits/stdc++.h>
using namespace std;
int v[200005];//标记数组
int fr[200005];//当前点在树上的父亲
vector <int> edge[200005];
int E;
int sum;
int ans[200005];//存储阶数
void dfs(int x) {
    int op = 0;
    if (edge[x].size() > 2) {//一定为花的中心
        ans[++E] = edge[x].size();
        op = 1;
        v[x] = op;
        if (x != 1)v[fr[x]] = op;
        sum += ans[E] + 1;
    }
    for (auto i : edge[x]) {
        if (i != fr[x]) {
            v[i] = op;
            fr[i] = x;
            dfs(i);
        }
    }
    return;
}
signed main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        edge[a].push_back(b);
        edge[b].push_back(a);
    }fr[1] = -1;
    E = 0;
    sum = 0;
    dfs(1);
    sort(ans + 1, ans + E + 1);//题目要求从小到大输出
    for (int i = 1; i <= (n - sum) / 3; i++) {//剩下n-sum个点，因此有(n - sum)/3个二阶花
        printf("2 ");
    }
    for (int i = 1; i <= E; i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}
```

## 致谢：

[CS Academy](https://csacademy.com/)，助我完成了画图部分。

[@tangguochao](https://www.luogu.com.cn/user/591428)，指出了特判错误。

---

## 作者：chlchl (赞：0)

这场 ABC 也就这题值得写个题解了（~~F、G、Ex 没做出来~~）。

注：本文称菊花图的中心节点为中心点，周围的点称为侧节点。

## Sol 1：模拟！

这种解法较容易想到，但是代码量大，且实现麻烦、容易超时。

首先观察到叶子节点必定作为菊花图的侧节点出现。所以我们每次从叶子节点出发，找到它的父亲 $fa$，那么 $fa$ 必定是某个菊花图的中心点。

每次删掉 $fa$ 及其周围的点（等于将整个菊花图从树中“抹掉”），再重复这个过程，直到已经没有点为止。

这个过程我们可以用 `set` 维护。由于需要保证复杂度，所以不仅要用 `set` 存图，还需要存下当前还在树中的节点，动态删除掉已经被去掉的点。

但是估计是我写法上的缺陷，这份代码一直 TLE 一个点，但是确实是有大佬用 `set` 维护过了的，在这里表示膜拜，Orz。

放一手代码，如果大家有更好的写法记得在评论区留言哦！

```cpp
//你不会觉得这份代码能编译吧
#include<bits/stdc++.h>
using namespace std;
 
const int N = 2e5 + 10;
int n, a[N];
set<int> g[N], ins;

int main(){
	n = read();
	for(int i=1,u,v;i<n;i++){
		u = read(), v = read();
		g[u].insert(v);
		g[v].insert(u);
	}
	for(int i=1;i<=n;i++)
		ins.insert(i);
	int len = 0;
	while(!ins.empty()){//只要还有点就继续找菊花 
		set<int> ss = ins;
		for(set<int>::iterator u=ins.begin();u!=ins.end();u++){//遍历所有点 
			int v = *u;
			if(g[v].size() == 1){//是叶子节点 
				int fa = *g[v].begin();//由于度为 1，所以唯一的连边必定是父亲 
				a[++len] = g[fa].size();//加入菊花等级 
				for(set<int>::iterator k=g[fa].begin();k!=g[fa].end();k++){//遍历父亲的所有节点 
					int kk = *k;
					if(g[kk].size() > 1){//侧节点还有其他边 
						for(set<int>::iterator r=g[kk].begin();r!=g[kk].end();r++){//与它相连的节点除了它父亲都要把它删掉 
							if(*r == fa)
								continue;
							g[*r].erase(g[*r].find(kk));//需要删除掉其它边 
						}
					}
					g[*k].clear();//清除这个点 
					ss.erase(ss.find(*k));
				}
				g[fa].clear();//中心节点也要清除 
				ss.erase(ss.find(fa));
			}
		}
		ins = ss;//因为 set 不支持边遍历边删除，所以需要另外开一个（这可能也是导致 TLE 的主要原因吧） 
	}
	sort(a + 1, a + 1 + len);
	for(int i=1;i<=len;i++){
		write(a[i]);
		putchar(' ');
	}
	return 0;
}
```

## Sol 2：结论！
赛后，我痛定思痛，思考了一下，发现一些惊人的规律。

保证答案唯一，所以度 $\ge 3$ 的点必定是中心点！

so 我们只要找到所有度 $\ge 3$ 的点，剩下的必定只能是 $2$ 阶菊花，直接输出即可。

注意，$n$ 阶菊花一共有 $n+1$ 个点，不要搞错了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n;
vector<int> g[N], ans;

int main(){
	cin >> n;
	for(int i=1,u,v;i<n;i++){
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int tot = n;//统计最后还剩多少个节点
	for(int i=1;i<=n;i++)
		if(g[i].size() >= 3)
			ans.push_back(g[i].size()), tot -= g[i].size() + 1;//+1！+1！+1！
	for(int i=1;i<=tot/3;i++)//2 阶菊花三个点！
		printf("2 ");
	sort(ans.begin(), ans.end());//从小到大！
	for(int v: ans)
		printf("%d ", v);
	return 0;
}
```



---

## 作者：jr_zch (赞：0)

# [A Gift From the Stars](https://www.luogu.com.cn/problem/AT_abc303_e)
## by [jr_zch](https://www.luogu.com.cn/blog/jr-zch-code-garden/) 博客食用更佳喵~
## Part 1：题目大意及其格式

***来自星的礼物***

### 题目描述：

星的定义：在一个有 $k + 1$ 个顶点和 $k$（$k \geq 2$）条边的图中有一个顶点与其它 $k$ 个顶点都有一条边相连，并且**没有其它的边**，那么这个图被称为 $k$ 级星。其实就是我们俗称的**菊花图**。

给你一颗树，要求删除一些边使得这棵树分成若干颗星星。

### 输入格式：

输入共 $n$ 行，第一行给出一个整数 $n$，接下来 $n - 1$ 行每行有两个整数 $u_i$ 和 $v_i$ 表示在 $u_i$ 和 $v_i$ 之间有一条边相连。

### 输出格式：

输出共 $1$ 行，把所有星的等级按升序输出即可，每两个数之间用空格分隔。

### 数据范围：

* $3 \leq n \leq 2 \times 10^5$
* $1 \leq u_i , v_i \leq n$

## Part 2：解题思路

因为星只能是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/zk830fpc.png)

而不能是这样

![](https://cdn.luogu.com.cn/upload/image_hosting/3ng9cdqy.png)

这在思路上给了我极大的帮助
### $O(n)$：正解如下
根据上图，容易发现任意两个星的中心点之间一定会间隔另外两个点。

那么，我们可以选一个点为起点，然后每次跳过两个点，一直到根节点就停止。

起点怎么确定？因为叶子结点的度数为 $1$ 而题目要求星的等级最低为 $2$ 所以叶子结点不能选，则它的父亲一定会被选。

最后用 $vis$ 记录这个点有没有被选过，如果被选过了，直接退出循环，因为它上面的点也一定被选过。

#### tips：
* 输入并没有说先输入儿子还是父亲，所以要先跑一遍 `dfs` 确定父亲和度。

## Part 3：Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e5+7;
int n,u,v,now;
int f[maxn],d[maxn];
bool vis[maxn];
vector<int> e[maxn],l;
//dfs确定每个点的父亲和度 
void dfs(int u,int fa){
	f[u]=fa;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v!=fa) d[u]++,dfs(v,u);
	}
	return ;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		e[u].push_back(v),e[v].push_back(u); //存图 
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		//找叶子节点 
		if(!d[i]){
			now=f[i];
			while(now&&!vis[now]){
				l.push_back(f[now]?d[now]+1:d[now]),vis[now]=1;
				now=f[f[f[now]]]; //往上跳跃两个节点 
			}
		} 
	}
	sort(l.begin(),l.end()); //升序排序 
	for(int i=0;i<l.size();i++) printf("%d ",l[i]);
	return 0;
}
```
## Thanks for your reading

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc303_e)
### 题解
相信大家不难发现，度为 $1$ 的点所连接的唯一节点一定是菊花图中的中心节点。

我们要保证菊花图中间没有重合的点和边，所以我们可以一次往下扩展 $3$ 层，若第 $2$ 到第三层只有一条边，那么第三层的节点也是答案的一部分。

考虑到要删边，所以我们可以用 set 存图。

具体可以看看代码。
### 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair <int,int> PII;
const int N = 200010,M = 2 * N;
int n;
set <int> g[N];
int d[N],backup_d[N];
void add_edge (int a,int b) {
	g[a].insert (b);
}
vector <int> v;
void bfs (int u) {
	queue <int> q;
	q.push (u);
	while (q.size ()) {
		int t = q.front ();
//		cout << t << "==================" << backup_d[t] << endl;
		q.pop ();
		v.push_back (backup_d[t]);
		for (int x : g[t]) {
			if (!g[x].count (t)) continue;
			g[x].erase (t);
			if (--d[x] == 1) {
				for (int y : g[*g[x].begin ()]) {
					if (y != x) q.push (y);
				}
			}
		}
	}
}
int main () {
	cin >> n;
	for (int i = 1;i <= n - 1;i++) {
		int a,b;
		cin >> a >> b;
		add_edge (a,b),add_edge (b,a);
		d[a]++,d[b]++;
	}
	memcpy (backup_d,d,sizeof (d));
	for (int i = 1;i <= n;i++) {
		if (d[i] == 1) {
			bfs (*g[i].begin ());
			sort (v.begin (),v.end ());
			for (int x : v) cout << x << ' ';
			return 0;
		}
	}
	puts ("-1");
    return 0;
}
```

---

## 作者：TernaryTree (赞：0)

考虑按度数从大到小排序。

菊花的中心度数一定 $\ge 2$。而 $\gt 2$ 的一定是菊花的中心（$=2$ 有可能是连上的）。

所以我们把 $\gt 2$ 的先选出来，然后剩下的用大小 $=2$ 的菊花填满，最终等于 $1$ 即可。需要从小到大输出。


```cpp
std::sort(d+1,d+1+n,std::greater<int>());
for(int i=1;i<=n;i++)t+=d[i]+1,s[++c]=d[i],t==n?i=n+1:0;
```

---

