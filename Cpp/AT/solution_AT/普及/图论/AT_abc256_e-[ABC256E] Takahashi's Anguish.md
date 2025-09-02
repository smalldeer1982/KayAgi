# [ABC256E] Takahashi's Anguish

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc256/tasks/abc256_e

$ 1 $ から $ N $ の番号がついた $ N $ 人の人がいます。  
 高橋君は $ 1 $ から $ N $ までの整数を並び替えた列 $ P\ =\ (P_1,\ P_2,\ \dots,\ P_N) $ を $ 1 $ つ選んで、 人 $ P_1 $, 人 $ P_2 $, $ \dots $, 人 $ P_N $ の順番に $ 1 $ 人ずつキャンディを配ることにしました。  
 人 $ i $ は人 $ X_i $ のことが嫌いなので、高橋君が人 $ i $ より先に人 $ X_i $ にキャンディを配った場合、人 $ i $ に不満度 $ C_i $ がたまります。そうでない場合の人 $ i $ の不満度は $ 0 $ です。  
 高橋君が $ P $ を自由に選べるとき、全員の不満度の和の最小値はいくつになりますか？

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ X_i\ \leq\ N $
- $ X_i\ \neq\ i $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- 入力される値はすべて整数

### Sample Explanation 1

$ P\ =\ (1,\ 3,\ 2) $ とすれば不満度が正になるのは人 $ 2 $ だけで、この時全員の不満度の和は $ 10 $ になります。 これより不満度の和を小さくすることはできないので、答えは $ 10 $ です。

## 样例 #1

### 输入

```
3
2 3 2
1 10 100```

### 输出

```
10```

## 样例 #2

### 输入

```
8
7 3 5 5 8 4 1 2
36 49 73 38 30 85 27 45```

### 输出

```
57```

# 题解

## 作者：Tmbcan (赞：3)

# [[ABC256E] Takahashi's Anguish](https://www.luogu.com.cn/problem/AT_abc256_e)
### 题目描述
需要确定一个序列 $P_N$，已知当 $x_i$ 排在 $i$ 之前时，会产生 $c_i$ 的贡献。求总贡献的最小值。
### 思路
建图后，对于每个子图中的结点，如果其所在的块中没有环，则对答案没有贡献；如果其所在的块中有环，就贪心的选择其中最小的边。  
其实就是实现最大生成树，总贡献减去连边时的代价就是最小贡献。
### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T&x){
	int w=0;x=0;
	char ch = getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=1;
		ch = getchar();
	}
	while(ch>='0'&&ch<='9'){
		x = (x<<1)+(x<<3)+(ch^48);
		ch = getchar();
	}
	if(w) x=-x;
}
template <typename T,typename...Args>
inline void read(T&t,Args&...args){
	read(t);read(args...);
}
const int N = 2e5+10;
int n;
int a[N],fa[N];
struct node{
	int to,nex,from,w;
	const bool operator < (const node&G) const{
		return w > G.w;
	}
}edge[N<<1];
int head[N<<1],edge_num;
inline void add(int x,int y,int w){
	edge[++edge_num].to = y;
	edge[edge_num].nex = head[x];
	head[x] = edge_num;
	edge[edge_num].from = x;
	edge[edge_num].w = w;
}
inline int find(int x){
	if(fa[x]==x) return x;
	return fa[x] = find(fa[x]);
}
inline int merge(int x,int y){
	int tx = find(x);
	int ty = find(y);
	if(tx!=ty){
		fa[ty] = tx;
		return 1;
	}
	return 0;
}
ll ans,sum;
inline void krscul(){
	sort(edge+1,edge+1+edge_num);
	for(int i=1;i<=edge_num;++i){
		if(merge(edge[i].from,edge[i].to)) ans+=1ll*edge[i].w;
	}
}
int main(){
	read(n);
	for(int i=1;i<=n;++i) fa[i] = i;
	for(int i=1;i<=n;++i) read(a[i]);
	for(int i=1,x;i<=n;++i){
		read(x);
		sum += x;
		add(a[i],i,x);
	}
	krscul();
	printf("%lld",sum-ans);
	return 0;
}
```

---

## 作者：coding_goat (赞：3)

还能交，水一发。

原题链接：

[LG](https://www.luogu.com.cn/problem/AT_abc256_e)

[AT](https://atcoder.jp/contests/abc256/tasks/abc256_e)

# 题目分析

在观察样例过后，我们可以尝试建图。

将不希望站在他前面的人指一条有向边，我们可以在样例 $2$ 得到这个图：

![我是图片啦啦啦](https://cdn.luogu.com.cn/upload/image_hosting/x8k0otv4.png)

观察图片我们发现图中有两个环，分别是 `1 -> 7 -> 1` 和 `5 -> 8 -> 2 -> 3 -> 5`。

因为有环，那么一定会有人不开心，找到环里面不开心值最小的加起来即可。

注意因为 $1 \le c_i \le 10^9$ 且 $2 \le n \le 2 \times 10^5$，所以 `ans` 记得开 `long long`。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
template <typename T>inline void read(T &xx){
	xx=0;int f=1;
    char c = getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        xx = (xx<<1)+(xx<<3)+(c^48);
        c = getchar();
    }
    xx*=f;
}
#define maxn 200050
int n,un[maxn],tmp,to[maxn];
bool vis[maxn];
int stk[maxn],top;
long long ans;
void serch(int xx){
	top=0;
	memset(stk,0,sizeof(stk));
	stk[++top]=xx;
	vis[xx]=1;
	while(top){
		//cout<<1<<'\n';
		int now=stk[top];
		int nxt=to[now];
		if(vis[nxt]){
			long long minn=un[nxt];
			while(stk[top]!=nxt&&top){
				minn=min(minn,(long long)un[stk[top--]]);
			}
			if(top!=0)ans+=minn;
			return ;
		}
		stk[++top]=nxt;
		vis[nxt]=1;
	}
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(tmp);
		to[i]=tmp;
	}
	for(int i=1;i<=n;i++) read(un[i]);
	for(int i=1;i<=n;i++)
		if(!vis[i])
			serch(i);
	cout<<ans;
	return 0;
}
```

---

## 作者：ChenZQ (赞：2)

其实我们可以将每一对讨厌的人看成在图上的一条边。

那么如果图上没有环，那么一定就存在一种排列，为什么？

我们假设 $1$ 讨厌 $2$，$2$ 讨厌 $3$。

那么我们直接就可以按 $321$ 来排列，其他图同理，我们可以反着推。

所以我们的任务就是让图不存在环。

接下来来说怎么找到环并且删最小的边。

首先用深度优先搜索，让 $f$ 为标记数组，如果 $f[i] = 1$，说明当前点已被访问并且**正在所遍历的环里**，如果 $f[i] = 2$ 就说明当前点已被访问并且不在所遍历的环里，$f[i] = 0$ 说明没访问过。

然后我们用一个数组来保存**我们正在遍历的环的所有边权**，用回溯来枚举所有图的形态，然后我们就可以通过这题了！

### AC CODE
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1000010;
int c[1000010];
struct node
{
	int u,dist;
};
int n,a[N],f[N],num[N],tot; 
vector<node> v[N];
int ans;

void dfs(int u) 
{
  if (f[u])
  {
    if (f[u]==1)
	{ 
      int sum = 1e9 + 10;
      for(int i=1;i<=tot;i++) sum=min(sum,num[i]);//找出环中最小的边权并加上他。
      ans+=sum;
    }
    return;
  }
  f[u]=1;
  for(int i=0;i<v[u].size();i++)
  {
    num[++tot]=v[u][i].dist;//回溯遍历图。
    dfs(v[u][i].u);
    tot--; 
  }
  f[u]=2;
}

signed main ()
{
  scanf("%lld",&n);
  for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
  for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
  for(int i=1;i<=n;i++) v[a[i]].push_back({i,c[i]});//建图。
  for(int i=1;i<=n;i++) dfs(i);
  printf("%lld",ans);
  return 0;
}
```

---

## 作者：So_noSlack (赞：1)

## 题目简述

对于数列 $\{a_n\}$ 的一种排列，$a_i$ 有且仅有一个 $j$，若 $a_j$ 排列在 $a_i$ 的前面则会产生 $c_i$ 的贡献值，求贡献的最小值。

## 思路

首先由“若 $a_j$ 排列在 $a_i$ 的前面则会产生 $c_i$ 的贡献值”可以考虑到建图解决此题。

我们连边 $j \to i$，边权为 $c_i$，如题中样例二的建图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/wk1jatuu.png)

我们考虑到如果有环则无法找到没有贡献值的排列方式，故我们必须选择某条边删除它，从而消除环。

很容易考虑到破坏每个环最小边权的环，那么如何找到环并删除最小边权的边呢，我们考虑到这种操作难以实现故相反考虑，只需要找到图的最大生成树即可，答案即为图变成最大生成树的过程中消失边的边权和。

那么如何求最大生成树的边权和呢，我们考虑到使用 $\text{Kruscal}$ 算法变相求图的最大生成树。

至此这道题就迎刃而解了，代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 200005

struct node { long long u, v, w; } e[MAXN];
long long n, a[MAXN], fa[MAXN], p = 0, tot = 0;

void add(int u, int v, int w) {
	e[++ p].u = u; e[p].v = v; e[p].w = w;
	return;
}

bool cmp(node l, node r) { return l.w > r.w; }

long long getf(long long x) {
	while(x != fa[x]) x = fa[x] = fa[fa[x]];
	return x;
}

long long Kruscal(long long n, long long m) {
	long long ans = 0;
	sort(e + 1, e + m + 1, cmp);
	for(int i = 1, x, y, w; i <= m; i ++) {
		x = getf(e[i].u); y = getf(e[i].v); w = e[i].w;
		if(x == y)  continue;
		ans += w; fa[y] = x; 
	} 
	return ans;
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	for(int i = 1, x; i <= n; i ++) { cin >> x; tot += x; add(a[i], i, x); }
	for(int i = 1; i <= n; i ++) fa[i] = i;
	long long tmp = Kruscal(n, p);
	cout << tot - tmp << "\n";
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/163699327)

---

## 作者：zhr2021 (赞：1)

# [AT_abc256_e [ABC256E] Takahashi's Anguish](https://www.luogu.com.cn/problem/AT_abc256_e) 题解
提供一种题解区还没有的~~神金~~奇妙做法

## solution
将每个人和他讨厌的那个人之间连一条有向边，注意是 $x_i \rightarrow i$ ，表示 $x_i$ 应该站在 $i$ 的前面，不愉悦值当作边权。  
样例 $2$ 建图如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/d76xkx13.png)

发现当几个点成环之后，必然要断掉一条边才能排成队列。所以我们贪心地选边权最小的那条边断开。由于每个点只有一条入边，所以每个点最多只能属于一个简单环，即不会出现如下图所示的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/cz9habte.png)

现在问题转化为找环，我~~神金地~~想到了强连通分量（本人学艺不精，不会找环）。

为什么强连通分量求解是正确的呢？由于每个点有且仅有一条入边，所以每个强连通分量必然是一个简单环（自行理解）。

代码就很好写啦！（不过，用强连通分量写黄题是真的神金）。
## AC code
[AC记录（跑得真的很快！！！）](https://www.luogu.com.cn/record/160017417)
```cpp
#include<bits/stdc++.h>
#define L long long
using namespace std;
inline L read(){
	L x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return w?-x:x;
}
const L N=1e6+10;
L n,a[N],minn[N],w[N],ans;
struct edges{
	L to,next;
}edge[N];
L head[N],idx;
void addedge(L u,L v){
	idx++;
	edge[idx]={v,head[u]};
	head[u]=idx;
}
L stk[N],top,dfn[N],low[N];
L cnt,blg[N],dt;
void tarjan(L u){
	stk[++top]=u;
	dfn[u]=low[u]=++dt;
	for(L i=head[u];i;i=edge[i].next){
		L v=edge[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!blg[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		++cnt;
		do{
			blg[stk[top]]=cnt;
		}while(stk[top--]!=u);
	}
}
int main(){
	memset(minn,0x3f,sizeof(minn));
	n=read();
	for(L i=1;i<=n;i++){
		a[i]=read();
		addedge(a[i],i);
	}
	for(L i=1;i<=n;i++){
		w[i]=read();
	}
	for(L i=1;i<=n;i++){
		if(!dfn[i]){
			dt=0;
			tarjan(i);
		}
	}
	for(L i=1;i<=n;i++){
		if(blg[a[i]]==blg[i]){
			minn[blg[i]]=min(minn[blg[i]],w[i]);
		}
	}
	for(L i=1;i<=cnt;i++){
		if(minn[i]<1e10)
		ans+=minn[i];
	}
	cout<<ans;
	return 0;
}
```
不知道是否有人和我一样是写了强连通分量的呢？

---

## 作者：Antiluna (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc256_e)

貌似是题解里少有的最大生成树解法。

看到“若 $x_i$ 站在 $i$ 的前面会产生 $c_i$ 的不愉悦值”容易想到建图。

不难发现，这个图不一定联通，每个子图对应的人显然互不干涉，并且每个子图一定是边比点多一，所以我们只需要去掉每个子图的环中的一条最小的边即可，也就是最大生成树。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ct,f[200010];
long long ans;
struct node
{
	int x,y,z;
}tr[400010];
bool cmp(node a,node b)
{
	return a.z>b.z;
}
int find(int x)
{
	if(f[x]==x)return x;
	else return f[x]=find(f[x]);
}
signed main()
{
	scanf("%d",bitand n);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++)scanf("%d",bitand tr[i].x),tr[i].y=i;
	for(int i=1;i<=n;i++)scanf("%d",bitand tr[i].z);
	sort(tr+1,tr+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		int x=tr[i].x,y=tr[i].y;
		int a=find(x),b=find(y);
		if(a!=b)f[a]=b;
		else ans+=tr[i].z;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：__YSC__ (赞：1)

# 题目描述

有 $N$ 个人，按照 $(P_1,P_2,\dots,P_N)$ 的顺序发糖。如果第 $X_i$ 个人在 $i$ 之前拿到了糖，那么沮丧度加 $C_i$。现在可一按任意顺序发糖，求最小沮丧度总和。

# 思路

将题意转换为一个 $N$ 个点 $N$ 条边的有向图，其中所有点出度为 $1$。很明显就是一个[基环内向森林](https://oi-wiki.org/graph/concept/)。对于每一颗基环内向树，我们可以找到环上边权最小的边，让边的起点沮丧。最终累计答案即可。

时空复杂度均为 $O(N)$。

## 细节

注意找环上最小边权时不要把进入环的那条边计入。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

struct Node {
  int u, fw;
}stk[MAXN];

struct Edge {
  int v, w;
};

int n, x[MAXN], vis[MAXN], top;
long long ans;
vector<Edge> e[MAXN];

void dfs(int u, int fw) {
  if(vis[u]) {
    if(vis[u] == 1) {
      int i = top, res = fw;
      for(; stk[i].u != u; res = min(res, stk[i].fw), --i) {
      }
      ans += res;
    }
    return;
  }
  vis[u] = 1, stk[++top] = {u, fw};
  for(Edge g : e[u]) {
    int v = g.v, w = g.w;
    dfs(v, w);
  }
  vis[u] = -1, top--;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i <= n; ++i) {
    cin >> x[i];
  }
  for(int i = 1, w; i <= n; ++i) {
    cin >> w;
    e[i].push_back({x[i], w});
  }
  for(int i = 1; i <= n; ++i) {
    if(!vis[i]) {
      dfs(i, INT_MIN);
    }
  }
  cout << ans;
  return 0;
}

```

---

## 作者：_shine_ (赞：1)

把题目转化一下即是在一张图中每个环的最小边权和是多少。

很容易想到搜索，但有点麻烦，思考有没有更为简洁的方法。

如果用并查集存储，每次把不喜欢的人拉入并查集，不难发现只要还没添加就是同一代表，必然成了环。

有环则必然要牺牲一个，则最优性价比就是牺牲那个代价最小的 $i$，所以遍历所有环中的人即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2e5+10;
int n;
int f[maxn],x[maxn],c[maxn];
ll ans;
int find(int x){
    if(f[x]==x)return x;
    else return f[x]=find(f[x]);
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",x+i);
    for(int i=1;i<=n;++i)scanf("%d",c+i);
    for(int i=1;i<=n;++i)f[i]=i;
    for(int i=1;i<=n;++i){
        if(find(i)!=find(x[i])){f[find(i)]=find(x[i]);continue;}
        int cnt=c[i],num=i;
        do{num=x[num];cnt=min(cnt,c[num]);}while(i!=num);
        ans+=cnt;
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：WhisperingWillow (赞：1)

对于一个有向图，且每个点出度为 $1$，则这个图为一个基环树森林。

如果一个连通块不存在环，则一定有一种方案能使它们互不影响。

否则我们选取影响值最小的点，肯定是最优的。

对每个连通块都进行找环和取 $\min$ 值，将他们的 $\min$ 值加起来就是答案。

代码太丑，就不放了。

---

## 作者：wnsyou (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc256_e)

## 题意

有 $n$ 个人，每个人都有一个看不惯的人，第 $i$ 个人看不惯 $x_i$，如果 $x_i$ 站在 $i$ 的前面，则会产生 $c_i$ 的不愉悦值。

求一个排列顺序，使得产生的不愉悦值最小，求最小值。

## 思路

> 做题之前先推样例。——鲁迅

其实带点模板的意味，每次建立一条从 $x_i$ 到 $i$ 的边，边权为 $c_i$，那么样例就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/lysvwifo.png)

能够发现，样例的答案来源于那条用红笔圈出来的边，思路也很明显了，对于不构成环的一些边来说，必然存在一种排列方法使得这些人不会不愉悦；而对于一个环呢？它必然会使得某个人不愉悦，只要把那个边权最小的加到答案即可。

## Code

```cpp
#include <iostream>
#include <vector>

using namespace std;
using pr = pair<int, int>;
using ll = long long;

const int N = 2e5 + 10;

int n, a[N], c, f[N], stk[N], top; // stack 维护环上边的权值
vector<pr> v[N];
ll ans;

void dfs (int x) {
  if (f[x]) {
    if (f[x] == 1) { // 判断构成环
      int sum = 1e9 + 10;
      for (int i = 0; i < top; i++) {
        sum = min(sum, stk[i]); // 选择边权最小值，加入答案
      }
      ans += sum;
    }
    return ;
  }
  f[x] = 1; // 标记在环上
  for (pr i : v[x]) {
    stk[top++] = i.second; // 将边权压入栈
    dfs(i.first);
    top--; // 弹出栈顶
  }
  f[x] = 2; // 标记不在环上但走过这个点
}

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> c;
    v[a[i]].push_back({i, c}); // 建图
  }
  for (int i = 1; i <= n; i++) {
    dfs(i); // 对每个点都要经行遍历
  }
  cout << ans;
  return 0;
}
```



---

## 作者：Melo_DDD (赞：0)

这个有且仅有一个 $x_i$ 是一个很强的限制条件啊。

考虑转化为图上问题，对于每个点，我们将 $i$ 向 $x_i$ 连边权是 $c_i$ 的边，表示 $i$ 要在 $x_i$ 前面。最终最好的情况当然是（若干个）链，这样我们一定可以给出一个合法排列。图不需要联通，因为不同连通块之间没有任何限制关系。

不好的情况是出现了环，这样就会出现矛盾，所以我们考虑把他断成链，显然至多需要删除一条边。

这个操作的实际意义是什么呢？想一想，删除一条边等于不承认 $i$ 在 $x_i$ 前面，也就是不符合限制条件，那么自然会耗费 $c_i$ 也就是边权的花费。

那么断开的最小花费就是环上的最小边权。

不要用 dfs，会有各种各样的问题需要处理（也可能是我太菜了）。

这种判环的问题用并查集最好了，只要这条边的两端在同一个连通块里面就出现了环。

代码：


```cpp
inline int find (int x) {
	return x == fa[x] ? x : fa[x] = find (fa[x]) ; 
}
signed main () {
	read (n) ;
	f (i ,1 ,n ,1) {
		fa[i] = i ;
		read (x[i]) ;
	}
	f (i ,1 ,n ,1) 
		read (c[i]) ;
	f (i ,1 ,n ,1) {
		if (find (i) != find (x[i])) {
			fa[find (x[i])] = find (i) ;
			continue ;
		}
		int mn = c[i] ,cur = i ;
		do {
			cur = x[cur] ;
			mn = min (mn ,c[cur]) ;
		} while (cur != i) ; // 不能用 while
		ans += mn ;
	} 
	cout << ans << '\n' ;
	return 0 ;
}
```

---

## 作者：_WF_ (赞：0)

## 题目分析
可以将每一个人视作图上的一个点，即第 $i$ 个人就是第 $i$ 号节点，每个人向其他人连接一条有权值的有向边。如果这个人不在环上，则可以通过调换位置来避免产生不愉快的值。

我们就会发现这个图至少会产生一个环，那么我们找出这个图中所有的环的有哪些点，我们只要找出每个环中最小的嫉妒值，再相加就是我们的答案。
## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 

using namespace std;


int h[200100], idx, n;
int x[200100], c[200100];
bool st[200100], st2[200100];
int st1[200100];
map<int, int> mp;
struct node{//链式前向星
	int u, v;
}e[200100];

void add(int u, int v){
	e[++idx].v = v;
	e[idx].u = h[u];
	h[u] = idx;
}

vector<int> v1, v2;
int ans;
void dfs2(int u){
	if (st2[u]){
		int res = v2.size();
		int re = 1e9 + 10;
		int cnt = 0;
		for (int i = 0; i < v2.size(); i++)
			re = min(re, c[v2[i]]);
		ans += re;
		return;
	}
	st2[u] = 1;
	v2.push_back(u);
	for (int i = h[u]; i; i = e[i].u){
		int v = e[i].v;
		dfs2(v);
	}
	v2.pop_back();
}

void dfs(int u, int cnt){
	if (st[u]){
		dfs2(u);//找环
		return;
	}
	st[u] = 1;
	mp[u] = cnt;
	v1.push_back(u);
	for (int i = h[u]; i; i = e[i].u){
		int v = e[i].v;
		if (mp.count(v))
			if (mp[v] != cnt) 
				return;
		mp[v] = cnt;
		dfs(v, cnt);
	}
	v1.pop_back();
}
signed main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		int x;
		cin >> x;
		add(i, x);
	}
	for (int i = 1; i <= n; i++) cin >> c[i];
	int cnt = 0;
	for (int i = 1; i <= n; i++){
		if (!st[i]){
			cnt++;
			dfs(i, cnt);
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：_qingshu_ (赞：0)

# 思路：

考虑建图，将所有的 $i$ 与 $p_i$ 之间连接一条权值为 $c_i$ 的边，表示 $i$ 与 $p_i$ 的关系。

考虑打破条件，发现只要图中出现环，我们就会满足不了其中的至少一对关系，这个时候我们可以选择割掉某条边（无视某一条关系），增加我们的费用，直到图中无环时所有人关系成立。也就是说，我们把这个问题转换成了最小花费使其变成一个无环图。

对于本题图中任意一个点，它有且仅有一条出边。而当任意一个环想要变成环套环的时候，环中至少存在一点会有两条出边，两者显然冲突，所以不需要考虑是否有边会割掉之后产生多倍收益导致当前贪心失效，得证后这个题就很简单了。

考虑开一个栈记录走过的点，每次重复时就弹出路径，割掉最小的一条边。正常回溯时判断顶部是否为自己再弹出就好了。

# Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[5200010],val[5200010];
long long ans;
bool flag[5200010],in[5200010];
stack<pair<int,long long> >ton;
inline void dfs(int id){
	flag[id]=1;
	if(!flag[p[id]]){
		ton.push({p[id],val[id]});in[p[id]]=1;
		dfs(p[id]);
		if(ton.top().first==p[id])ton.pop();
		in[p[id]]=0;
	}
	else if(in[p[id]]){
		long long minn=val[id];
		while(ton.top().first!=p[id]){
			minn=min(minn,ton.top().second);
			in[ton.top().first]=0;
			ton.pop();
		}
		ans+=minn;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1,x;i<=n;i++)cin>>val[i];
	for(int i=1;i<=n;i++){
		if(!flag[i]){
			in[i]=1;
			ton.push({i,INT_MAX});
			dfs(i);
			in[i]=0;
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：lichenxi111 (赞：0)

## 题意

有 $n$ 个人，标号为 $1$ 到 $n$，对于标号 $i$ 的人，给定 $a_i$ 和 $c_i$，你需要确定一个排列，在这个排列中，如果把标号 $a_i$ 的人排在标号 $i$ 的人前面，则需要花费 $c_i$，求最小花费。

## 思路

考虑可以用连边 $i \rightarrow j$ 来表示 $i$ 在 $j$ 前面，那么为了减少花费，最开始一定会让 $i \rightarrow a_i$，即 $i$ 站在 $a_i$ 前面。

这里有人要说了：你的图不一定是联通的。这没影响，对于一个无环的联通块其实是一个链表的关系，比如 $i \rightarrow j \rightarrow k$，可以直接在排列中表现为三个连续的数 $i,j,k$。所以每个连通块都可以在排列里表现为连续的一段数，最后凑出整个排列。

上文连通块定义为：存在一点 $i$，使得从点 $i$ 出发可以遍历整个连通块。

考虑什么时候这样做是不行的，当出现环时，这是需要删去一条边来破除环，当删去 $i \rightarrow a_i$ 这条边时，意味着 $i$ 不能站在 $a_i$ 的前面，即 $a_i$ 会站在 $i$ 的前面，这时需要花费 $c_i$，那么删去环上花费最少的边即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int cost[210000],v[210000];
bool f[210000];
int ans;
void solve(int x)
{
	stack<int> s;
	s.push(x);
	f[x] = 1;
	while(s.size())
	{
		int y = s.top();
		int z = v[y];
		if(f[z])
		{
			int minn = cost[z];
			while(s.size() && s.top() != z)
			{
				minn = min(minn,cost[s.top()]);
				s.pop();
			}
			if(s.size())
			{
				ans += minn;
			}
			return;
		}
		s.push(z);
		f[z] = 1;
	}
}
signed main()
{
	int n;
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		int x;
		cin >> x;
		v[i] = x;
	}
	for(int i = 1;i <= n;i++)
	{
		cin >> cost[i];
	}
	for(int i = 1;i <= n;i++)
	{
		if(!f[i])
		{
			solve(i);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Tsawke (赞：0)

# [[ABC256E] Takahashi's Anguish](https://www.luogu.com.cn/problem/AT_abc256_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC256E)

## 题面

存在 $ n $ 个人，你需要确定一个序列 $ P_n $ 表示这 $ n $ 个人的排列，对于每个人，第 $ i $ 个人有且仅有一个 $ x_i $，表示不喜欢 $ x_i $ 站在 $ i $ 的前面，若 $ x_i $ 站在 $ i $ 的前面则会产生 $ c_i $ 的不愉悦值，你需要确定排列以最小化不愉悦值之和，求最小值。

## Solution

这道题想到方法之后就很简单了，是一道图论建模题。考虑将不喜欢的关系抽象成一条有向边，不难发现每个点都有且仅有一条出边，则最后形成的图在形态上一定类似一个基环树森林，或者说在形成的图中每一个连通块内最多含有一个环。

不难想到对于无环的一定有合法方案使得每一个点都不会有不喜欢的在其之前，对于环上的则一定至少需要破坏一条环上的边。于是我们跑一个类似拓朴排序的东西即可，对于无环的直接丢弃，有环的在环上找到边权最小的一条边保留即可。

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
    Edge *nxt;
    int to;
    int val;
    OPNEW;
}ed[210000];
ROPNEW(ed);
Edge* head[210000];

int N;
bitset < 210000 > vis;
int ind[210000];
ll ans(0);

int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        int s = i, t = read();
        head[s] = new Edge{head[s], t};
        ++ind[t];
    }for(int i = 1; i <= N; ++i)head[i]->val = read();
    queue < int > cur;
    for(int i = 1; i <= N; ++i)if(!ind[i])vis[i] = true, cur.push(i);
    while(!cur.empty()){
        int tp = cur.front(); cur.pop();
        for(auto i = head[tp]; i; i = i->nxt){
            --ind[SON];
            if(!ind[SON])vis[SON] = true, cur.push(SON);
        }
    }
    for(int i = 1; i <= N; ++i){
        if(!vis[i]){
            int mn(INT_MAX);
            vis[i] = true;
            auto cur = head[i];
            while(cur->to != i){
                vis[cur->to] = true;
                mn = min(mn, cur->val);
                cur = head[cur->to];
            }mn = min(mn, cur->val);
            ans += mn;
        }
    }printf("%lld\n", ans);
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

update-2022_12_08 初稿

---

