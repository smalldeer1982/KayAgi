# [ARC097F] Monochrome Cat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc097/tasks/arc097_d

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点からなる木があります。 $ i $ 番目の辺は頂点 $ x_i $ と $ y_i $ を結んでいます。 各頂点は、白か黒のいずれかの色で塗られています。 初期状態では、頂点 $ i $ の色は $ c_i $ で表されます。 $ c_i $ $ = $ `W` のとき 頂点が白いことを、$ c_i $ $ = $ `B` のとき 頂点が黒いことを表します。

この木の頂点の上を猫が移動していきます。 具体的には、$ 1 $ 秒間に次の動作のどちらかを行なうことを繰り返します。

- 現在いる頂点と隣接した頂点をひとつ選びその頂点に移動する。その後、移動先の頂点の色を反転する。
- 現在いる頂点の色を反転する。

猫の目標はすべての頂点を黒で塗ることです。どの頂点から動作をはじめても、どの頂点で動作を終えてもかまいません。 最短何秒で目標を達成できるでしょうか?

## 说明/提示

### 制約

- $ 1 $ $ <\ = $ $ N $ $ <\ = $ $ 10^5 $
- $ 1 $ $ <\ = $ $ x_i,y_i $ $ <\ = $ $ N $ ($ 1 $ $ <\ = $ $ i $ $ <\ = $ $ N-1 $)
- 与えられるグラフは木
- $ c_i $ $ = $ `W` または $ c_i $ $ = $ `B`

### Sample Explanation 1

例えば、次のように行動すると $ 5 $ 秒で達成できます。 - 頂点 $ 1 $ からはじめる。 頂点 $ 1 $ の色を黒に変更する。 - 頂点 $ 2 $ に移動し、頂点 $ 2 $ の色を白に変更する。 - 頂点 $ 2 $ の色を黒に変更する。 - 頂点 $ 4 $ に移動し、頂点 $ 4 $ の色を黒に変更する。 - 頂点 $ 5 $ に移動し、頂点 $ 5 $ の色を黒に変更する。

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
4 5
WBBWW```

### 输出

```
5```

## 样例 #2

### 输入

```
6
3 1
4 5
2 6
6 1
3 4
WWBWBB```

### 输出

```
7```

## 样例 #3

### 输入

```
1
B```

### 输出

```
0```

## 样例 #4

### 输入

```
20
2 19
5 13
6 4
15 6
12 19
13 19
3 11
8 3
3 20
16 13
7 14
3 17
7 8
10 20
11 9
8 18
8 2
10 1
6 13
WBWBWBBWWWBBWWBBBBBW```

### 输出

```
21```

# 题解

## 作者：installb (赞：8)

## ARC097D  

一个细节调一天系列。  

首先如果一个叶子节点是黑色的，我们就不需要去经过那个点（当然这个点还是可以作为起点的）在树中删去这个点对答案没用影响，我们不断重复这个过程（删去一个点后可能有新的黑色叶子节点）。  

然后得到一棵叶子节点都为白色的树，我们需要经过每一个叶子节点。这个路径比较难做，我们**先考虑回路**，也就是猫从 $u$ 出发，遍历所有点后必须回到 $u$，这样一定是**每条边正向反向各走一次**，每一个点也由于进入这个点反转了**这个点的度数次数**次颜色，因此每一个点的最终颜色决定于它的入度和初始颜色数，前者等于删点后的树上这个点的度数。对翻转后还是白色的点做个标记，我们到达这些点的时候需要每个点额外翻转一次。  

然后考虑从 $u$ 到 $v$ 的路径，我们发现这其实就是回路减去了这两点之间的所有边，相当于这中间的点除了 $u$ 都少经过了一次，即经过恰好一次。  
- 对于没被标记的点，少经过一次但同时要多翻转一次颜色。
- 对于标记了的点，少经过一次还少翻转一次颜色。  

前者对答案的贡献为 $0$，后者对答案的贡献为 $-2$。  
所以我们要找到一条路径，经过尽可能多的被标记了的点。  

这不就是树的直径吗？  
最后一个问题，这样 $u$ 点本来不应该统计进去，答案不会多吗？  
并不会！因为叶子节点的权值必定是 $0$，一定存在不包含叶子节点的直径，然后我们取叶子节点作为 $u$。  

最后树形 DP 求直径，记得这里一定要找到一个没被删掉的点当根，再跑。  

答案为删完剩余边数乘二加标记的点数减去直径长度。  

扔个代码：  
头文件有 `queue`。
```cpp
using namespace std;
typedef long long LL;
const LL N = 100005;
 
LL ec = 0,to[N << 1],nxt[N << 1],hed[N],deg[N];
LL cnt = 0;
void add_edge(LL f,LL t){
	++ ec; to[ec] = t; nxt[ec] = hed[f]; hed[f] = ec;
	deg[t] ++;
}
 
LL vis[N] = {0},val[N],dis[N];
LL eu[N],ev[N],n;
string s;
 
void solve(){
	queue <LL> q;
	for(LL i = 1;i <= n;i ++) if(deg[i] == 1 && s[i] == 'B') q.push(i);
	while(!q.empty()){
		LL u = q.front(); q.pop();
		vis[u] = 1;
		for(LL i = hed[u];i;i = nxt[i]){
			LL v = to[i];
			if(!vis[v]){
				deg[v] --;
				if(deg[v] == 1 && s[v] == 'B') q.push(v);
			}
		}
	}
    // 删黑叶子
	memset(deg,0,sizeof(deg));
	memset(hed,0,sizeof(hed)); ec = 0;
	for(LL i = 1;i < n;i ++){
		if(vis[eu[i]] || vis[ev[i]]) continue;
		add_edge(eu[i],ev[i]);
		add_edge(ev[i],eu[i]);
	}
	for(LL i = 1;i <= n;i ++){
		val[i] = 0;
		if(vis[i]) continue;
		if((s[i] == 'B' && deg[i] % 2 == 1) || (s[i] == 'W' && deg[i] % 2 == 0)){
			val[i] = 2;
			cnt ++;
		}
	}
    // 打标记
}
 
LL td = 0;
LL d[N];
void dfs(LL u,LL f){
	d[u] = val[u];
	for(LL i = hed[u];i;i = nxt[i]){
		LL v = to[i];
		if(v == f) continue;
		dfs(v,u);
		td = max(td,d[u] + d[v]);
		d[u] = max(d[u],d[v] + val[u]);
	}
    // 求直径
}
 
int main(){
	ios::sync_with_stdio(false);
	cin >> n;
	for(LL i = 1;i < n;i ++){
		cin >> eu[i] >> ev[i];
		add_edge(eu[i],ev[i]);
		add_edge(ev[i],eu[i]);
	}
	cin >> s; s = ' ' + s;
	solve();
	LL trt = 1,ans;
	for(LL i = 1;i <= n;i ++) if(!vis[i]) trt = i;
	dfs(trt,0);
	ans = ec + cnt - td;
	cout << ans << '\n';
	return 0;
} 
```

感觉这题挺有意思。

---

## 作者：D_F_S (赞：5)

	不知从哪里听来了 树上插头DP，可以处理树上跑路径的问题，正好在这道题上练手。

## Solution：

钦定以 1 为根，对于一个点 $p$，我们想要求出 将 $p$ 子树内所有节点变黑 的最小操作次数。可以知道一条边至多会被遍历两遍，因此考虑按 $p$ 到其父亲的边（简称父亲边）的遍历情况分类讨论：

1. 其父亲边未被遍历，要么子树内没有白点，要么子树外没有白点。

2. 遍历的方向为从父亲到儿子，则路径的起点在子树外，终点在子树内。

3. 遍历的方向为从儿子到父亲，则路径的起点在子树内，终点在子树外。

4. 遍历是双向的，且路径的起点与终点都在子树外。

5. 遍历是双向的，且路径的起点与终点都在子树内。

![](https://cdn.luogu.com.cn/upload/image_hosting/g5bo35sr.png)

这些情况涵盖了所有 $p$ 与其父亲在路径上的关系，再记录 $s$ 表示 $p$ 的 *子树内有白点的儿子* 的数量（相当于 $p$ 需要往儿子走的次数），就可以根据上面的情况求得 $p$ 会被遍历的次数，结合 $p$ 的初始颜色知道是否须在 $p$ 进行操作 2。

至此就可以设出状态 $f[[p][0/1/2/3/4]$ 分别对应上面 5 种情况时 $p$ 子树内所有点都变黑的最少操作数（涵盖了 $p$ 的父亲边），当 $s\ge2$ 时最多只有 2 个儿子不取 $f[][3]$，所有状态均可分类讨论进行转移。

*p.s. 不得不说感觉比 换根DP 难写太多了。*
## Code：
```cpp
#include<bits/stdc++.h>
#define inl inline
using namespace std;
const int N=1e5+5;
struct E {int ne,to; }e[N*2];
int n,ec,h[N],a[N],f[N][5];
inl int Read()
{
	int s=0; char c;
	while(!isdigit(c=getchar()));
	for(;isdigit(c);c=getchar()) s=s*10+c-'0';
	return s;
}
inl bool Readc()
{
	for(char c=getchar();;c=getchar())
		if(isalpha(c)) return c=='W';
}
inl void Add(int x,int y)
{
	e[++ec]=(E){h[x],y}; h[x]=ec;
	e[++ec]=(E){h[y],x}; h[y]=ec;
}
inl void DFS(int p,int fr)
{
	int s=0;
	for(int i=h[p];i;i=e[i].ne)
	{
		int v=e[i].to; if(v==fr) continue;
		DFS(v,p); if(f[v][0]) ++s;
	}
	if(!s)
	{
		f[p][0]=a[p];		// 父亲边没被遍历，自己没变色 
		f[p][1]=2-a[p];		// 父亲边被遍历一次，自己变色
		f[p][2]=1+a[p];		// 父亲边被遍历一次，自己没变色
		f[p][3]=3-a[p];		// 父亲边被遍历两次，自己变色
		f[p][4]=3-a[p];		// 父亲边被遍历两次，自己变色
	}
	else if(s==1)
		for(int i=h[p];i;i=e[i].ne)
		{
			int v=e[i].to;
			if(v==fr||!f[v][0]) continue;
			if(a[p]) f[p][0]=min(1+f[v][1],min(f[v][2],f[v][4]));
					// 除了自身作为起点（即取 f[v][1]）外其它情况自己都已变色 
			else f[p][0]=f[v][0];
			f[p][1]=2-a[p]+f[v][1];		// 自身仅被遍历一次 
			f[p][2]=2-a[p]+f[v][2];
			f[p][3]=2+a[p]+f[v][3];		//自己被遍历两次，相当于没变色 
			f[p][4]=2+a[p]+f[v][4];
		}
	else
	{
		int t=0,t1=0,t2=0,t3=0,t4=0;
		for(int i=h[p];i;i=e[i].ne)
		{
			int v=e[i].to;
			if(v==fr||!f[v][0]) continue;
			t+=f[v][3];						// 假设所有儿子都取 f[][3] 的最少操作数 
			t3=min(t3,min(t1+f[v][2]-f[v][3],t2+f[v][1]-f[v][3]));
					// 起点在一个儿子的子树内，终点在另一个儿子的子树内 
			t1=min(t1,f[v][1]-f[v][3]);		// 终点在一个儿子的子树内 
			t2=min(t2,f[v][2]-f[v][3]);		// 起点在一个儿子的子树内 
			t4=min(t4,f[v][4]-f[v][3]);		// 起点终点在同一个儿子的子树内 
		}
		f[p][0]=t+min(t3+(((s-1)&1)^a[p]),t4+((s&1)^a[p]));	
		// 若终点在一个儿子的子树内且起点不在其子树内，则 从儿子遍历到 p 有 s-1 次，否则有 s 次 
		f[p][1]=1+t+t1+((s&1)^a[p]);
		f[p][2]=1+t+t2+((s&1)^a[p]);
		f[p][3]=2+t+(((s+1)&1)^a[p]);	// 从父亲还会遍历到 p 一次 
		f[p][4]=2+t+min(t3+((s&1)^a[p]),t4+(((s+1)&1)^a[p]));
	}
}
int main()
{
	n=Read();
	for(int i=1;i<n;++i) Add(Read(),Read());
	for(int i=1;i<=n;++i) a[i]=Readc();
	DFS(1,0); printf("%d\n",f[1][0]);
	return 0;
}
```


---

## 作者：关怀他人 (赞：4)

### ARC 097F
#### Solution
首先把所有黑色的叶子去掉，因为它们是没用的。然后考虑一种最简单的遍历，从某个节点出发按$dfs$序遍历每个节点，这样每条边会被经过恰好$2$次，每个点会被经过$deg_i$次，然后对于每个点再单独考虑这样操作之后是否变成了黑色，如果不是的话还需要一次额外的操作，记这种情况下的总次数为$sum$。

然后考虑如何确定起点$S$和终点$T$，不难发现从$S$到$T$的最少游走次数就是在上面$dfs$的基础上，$S$到$T$路径上的每条边都少走一次，路径上的每个点（不包括$S$和$T$）也都少走一次。那么我们可以去掉$S$和$T$，考虑中间那条链最长能减少多少贡献。中间那条路径删掉之后的贡献就是点数$+1−$黑点个数$+$白点个数（这里的颜色为$dfs$之后的颜色），那么可以看做黑点贡献$0$，白点贡献$2$，求一条两端点不在叶子上的最长链的长度$d$，其实就是求带权直径的长度，dp即可，最后的答案就是$sum−d−1+1=sum-d$。
#### Code
```cpp
int n,len,sum,root,dia,cnt;
int head[MAXN],vis[MAXN],f[MAXN],w[MAXN],deg[MAXN];
char s[MAXN];

struct Edge{
    int to,next;
} e[MAXN << 1];

void add_edge(int u,int v){
    e[++len] = (Edge){v,head[u]};
    head[u] = len;
}

void dfs(int u,int fa){
    vis[u] = (s[u] == 'W');
    for(int i = head[u];i != -1;i = e[i].next){
        int v = e[i].to;
        if(v == fa) continue;
        dfs(v,u);
        vis[u] |= vis[v];
        if(vis[v]) deg[u] += 1;
    }
    if(u != root) deg[u] += 1;
    if(!vis[u]) return;
    sum += 2;
    if((deg[u] & 1) && s[u] == 'B') sum += 1, w[u] = 2;
    if(!(deg[u] & 1) && s[u] == 'W') sum += 1, w[u] = 2;
    f[u] = w[u];
    for(int i = head[u];i != -1;i = e[i].next){
        int v = e[i].to;
        if(v == fa) continue;
        checkMax(dia,f[u] + f[v]);
        checkMax(f[u],f[v] + w[u]);
    }
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i = 1,u,v;i < n;i++){
        scanf("%d%d",&u,&v);
        add_edge(u,v); add_edge(v,u);
    }
    scanf("%s",s + 1);
    for(int i = 1;i <= n;i++){
        cnt += (s[i] == 'W');
        if(s[i] == 'W') root = i;
    }
    if(cnt <= 1) return printf("%d\n",cnt),0; 
    dfs(root,0);
    printf("%d\n",sum - dia - 2);
    return 0;
}
```

---

## 作者：xht (赞：2)

> [ARC097F Monochrome Cat](https://atcoder.jp/contests/arc097/tasks/arc097_d)

## 题意

- 给定一棵 $n$ 个点的树，每个点要么是白色要么是黑色。
- 你可以从任何一个顶点出发，每秒执行下列操作中的一个：
  - 走到一个相邻的节点，反转到达的节点颜色。
  - 反转所在的节点颜色。
- 问至少需要多少秒可以使所有节点变黑。
- $n \le 10^5$。

## 题解

首先肯定先把纯黑的子树剪掉。

假设我们要求必须回到起点，则我们一定会走一条欧拉回路。

$d_i$ 为 $i$ 的度数，在只进行第一个操作的情况下，花费的时间为 $2n - 2$ 秒，同时点 $i$ 的颜色会反转 $d_i$ 次，因此总花费时间还要加上反转后颜色为白色的点数。

考虑不要求回到起点有什么变化，此时实际去掉的路径就是从终点到起点的这一条链，除了终点都少被反转了一次。

考虑只走一遍欧拉回路后两种颜色的点的贡献变化：

- 对于黑色的点，如果少翻转一次，这个点即为白色，还是需要额外花费一次操作，因此操作数不变。
- 对于白色的点，如果少翻转一次，这个点即为黑色，省掉了额外将其反转的操作，因此操作数减二。

由于叶子节点一定是黑色的，问题可以简单的转化为求出一条包含白色点最多的路径，那么求个直径即可，时间复杂度 $\mathcal O(n)$。

要注意特判 $n=1$ 的情况，此时叶子节点是白色的。

## 代码

```cpp
const int N = 1e5 + 7;
int n, ans, d[N];
vi e[N];
char s[N];
bool a[N], c[N], b[N];

void dfs1(int x, int fa) {
	b[x] = c[x];
	for (int y : e[x])
		if (y != fa)
			dfs1(y, x), b[x] |= b[y];
	ans += b[x];
	if (!b[x]) a[fa] ^= 1;
}

void dfs2(int x, int fa) {
	d[x] = d[fa] + c[x];
	for (int y : e[x])
		if (b[y] && y != fa)
			dfs2(y, x);
}

int main() {
	rd(n);
	for (int i = 1, x, y; i < n; i++)
		rd(x, y), e[x].pb(y), e[y].pb(x), a[x] ^= 1, a[y] ^= 1;
	rds(s, n);
	int rt = 0;
	for (int i = 1; i <= n; i++) {
		c[i] = s[i] == 'W';
		if (s[i] == 'W') rt = i;
	}
	if (!rt) return prints("0"), 0;
	dfs1(rt, 0);
	ans = ans * 2 - 2;
	if (!ans) return prints("1"), 0;
	for (int i = 1; i <= n; i++)
		if (b[i]) ans += c[i] ^= a[i];
	dfs2(rt, 0);
	for (int i = 1; i <= n; i++)
		if (b[i] && d[i] > d[rt]) rt = i;
	d[rt] = 0, dfs2(rt, 0);
	for (int i = 1; i <= n; i++)
		if (b[i] && d[i] > d[rt]) rt = i;
	print(ans - d[rt] * 2);
	return 0;
}
```

---

## 作者：Ihave4oranges (赞：1)

首先显然是树形 dp。注意到黑色的叶子节点是没有必要经过的，可以把它们删除。删除之后增加的黑色叶子也需要删除。这样就可以强制路径经过树的每一个点至少一次。

树形 dp 最常见的就是记录子树的信息。一个子树有这么几种情况：

1. 从父亲进来，遍历子树，从父亲出去
2. 子树外遍历完，进入子树，遍历子树
3. 子树内遍历完，离开子树，遍历剩余节点
4. 从子树出去，遍历子树外节点，再回到子树遍历完剩余节点

所以用 $dp_{i,0/1/2/3}$ 记录。这里我是记录了**包含子树根确定颜色但不包含父亲边**的最小代价。转移需要分类讨论。定义 $b_i$ 表示节点 $i$ 翻色它的度数次之后需不需要额外翻色，$son_i$ 表示节点 $i$ 的儿子数量。

### $dp_{i,0}$

只有一种情况。所有儿子取 $0$，代价增加 $2son_i+b_i$。

### $dp_{i,1}$

两种情况。

1. 路径终点不在根。一个儿子取 $1$，其它儿子取 $0$。代价增加 $2son_i-1+(b_i\oplus1)$。(这里和 $1-b_i$ 是一样的。)
2. 路径终点在根。所有儿子取 $0$。代价增加 $2son_i+b_i$。

### $dp_{i,2}$

类似上一个，两种情况。

1. 路径起点不在根。一个儿子取 $2$，其它儿子取 $0$。代价增加 $2son_i-1+(b_i\oplus1)$。
2. 路径起点在根。所有儿子取 $0$。代价增加 $2son_i+(b_i\oplus1)$。

### $dp_{i,3}$

五种情况。

1. 起点终点在不同儿子下面。一个儿子取 $1$，一个儿子取 $2$，其它儿子取 $0$。代价增加 $2son_i-2+(b_i\oplus1)$。
2. 起点终点在同一个儿子下面。一个儿子取 $3$，其它儿子取 $0$。代价增加 $2son_i+b_i$。
3. 起点在根。一个儿子取 $1$，其它儿子取 $0$。代价增加 $2son_i-1+(b_i\oplus1)$。
4. 终点在根。一个儿子取 $2$，其它儿子取 $0$。代价增加 $2son_i-1+b_i$。
5. 起点终点都在根。所有儿子取 $0$。代价增加 $2son_i+b_i$。

提供一个比较方便的写法。注意到以上的 $10$ 种情况中，儿子的取值有相同或相似的地方。在 dfs 的过程中，记录五个变量 $tmp_{0/1/2/3/4}$。其中，$tmp_{i=0\sim3}$ 表示一个儿子取 $i$，其它儿子取 $0$ 的最小代价，从自己和 $0$ 转移。$tmp_4$ 表示两个儿子取 $1$ 和 $2$ 的最小代价，从自己和 $0,1,2$ 转移。最后再统计根的 dp 信息。

给 dfs 部分的代码。

```cpp
void dfs(int v,int fa){
	int tmp[5],cnt=0;//cnt就是上面题解中的son_i 
	tmp[0]=0;
	tmp[1]=tmp[2]=tmp[3]=tmp[4]=0x3f3f3f3f;
	for(auto to:g[v])
		if(to!=fa&&!vis[to]){//vis=1表示不需要访问的节点 
			dfs(to,v);
			++cnt;
			//这里倒过来，因为同一个儿子不能转移多次，有点类似 0/1 背包的想法。 
			tmp[4]=min(tmp[4]+dp[to][0],min(tmp[1]+dp[to][2],tmp[2]+dp[to][1]));
			tmp[3]=min(tmp[3]+dp[to][0],tmp[0]+dp[to][3]);
			tmp[2]=min(tmp[2]+dp[to][0],tmp[0]+dp[to][2]);
			tmp[1]=min(tmp[1]+dp[to][0],tmp[0]+dp[to][1]);
			tmp[0]+=dp[to][0];
		}
	//最后统计答案 
	dp[v][0]=tmp[0]+b[v]+cnt+cnt;
	dp[v][1]=min(tmp[1]+(b[v]^1)+cnt+cnt-1,tmp[0]+b[v]+cnt+cnt);
	dp[v][2]=min(tmp[2]+(b[v]^1)+cnt+cnt-1,tmp[0]+(b[v]^1)+cnt+cnt);
	dp[v][3]=
	min(tmp[4]+(b[v]^1)+cnt+cnt-2,
	min(min(tmp[3]+b[v]+cnt+cnt,
	tmp[1]+(b[v]^1)+cnt+cnt-1),
	min(tmp[2]+b[v]+cnt+cnt-1,
	tmp[0]+b[v]+cnt+cnt)));
}
```
最后给一道有类似想法的题目：（这道题在学校的模拟赛里，原题题号好像是 JZOJ5819，但是这个 OJ 好像需要会员）

你到外国游学 $T$ 天，可以从其中的任何国家开始、到任何国家为止，经过某 $n$ 个国家中的一些，这些国家和它们之间的道路可以被当作一棵树上的顶点和边。

已知在第 $i$ 个国家学习所得到的收获为 $w_i$（可以为 $0$，无论经过多少次都只一次），无论是否学习，都需要花费 $t_i$ 天来隔离（可以为 $0$，无论经过多少次都只隔离一次）；第 $i$ 个道路连接 $a_i$ 和 $b_i$ 两个国家，通过这条道路所花的时间为 $c_i$ 天。

求 $T$ 天内他总收获的最大值（可以花费不到 $T$ 天）。

数据范围：$1\le a_i,b_i\le n\le 500,0\le t_i,c_i\le T\le 1000,w_i\le 1000000$。

时间复杂度：$O(nT^2)$。

---

## 作者：lzk5627 (赞：1)

申请管理员添加简要题意(被禁言了)
### 简要题意
给出一棵树,树上每个节点有一个初始颜色每个时刻你可以有两种操作

* 翻转该节点颜色
* 前往与该节点相邻的节点,并将目标节点翻转

初始点你自己选,求将所有点变为黑色的最小步数

似乎好像还挺简单的,orz yyxmy

### sol

首先考虑简化问题,对于为黑色的叶子节点,我们可以直接删掉,这样树就变成了叶子结点全都是白色的一棵树

首先我们肯定是沿着树上的一条路径走,然后进入附近的支路再出来,我们先不考虑路径到底是什么,那么总贡献就是 $\sum b_i +check(i,b_i)$ , $b_i$ 表示 $i$
点的度数,因为不考虑路径上的点的话,每个点显然要遍历 $b_i$ 次, $check(i,x)$ 表示的是经过 $x$ 次翻转之后 $i$ 点是否还需要翻转

然后考虑减去路径上节点的贡献,也就是要找出一条路径,将路径上点的贡献变为 $d_i-1+check(i,d_i-1)$ 这个直接 $dp$ 即可,方式类似于求树上直径

---

## 作者：yyxmy (赞：0)

首先有一个比较显然的性质， 要遍历的点只可能在最小的包含所有白点的联通块内，我们可以把这个联通块找出来。

然后我们假定这个白色联通块内所有的边都被经过两遍， 也就是跑出了一条回路。 可以把这个答案算出来。 但是所有的边不一定都被经过两次， 可能有只被经过一次的边， 很显然只被经过一次的边一定是某条路径， 那么我们要找的是一条路径，其经过一次的代价与经过两次的代价差最大。 这个树形$dp$就可以实现了。
```cpp
#include<bits/stdc++.h>
#define reg register
#define maxn 200001
using namespace std;
int nt[maxn << 1], fi[maxn], go[maxn], d[maxn], rt;
int dp[maxn], n, sum, sumx, siz[maxn], ans, cnt;
char s[maxn];
vector<int> Q[maxn];
inline int  read() {
    reg int s = 0, t = 0; reg char ch = getchar();
    while(ch > '9' || ch < '0') t |= ch == '-', ch = getchar();
    while(ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
    return t ? -s : s;
}
void add(int u, int v){
	nt[++cnt] = fi[u]; fi[u] = cnt; go[cnt] = v;
}
void dfs(int u, int fa){
	siz[u] = (s[u] == 'W'); 
	for(int i = fi[u]; i; i = nt[i]){
		int v = go[i]; if(v == fa) continue;
		dfs(v, u); siz[u] += siz[v];
		if(siz[v] != ans && siz[v] != 0){
			Q[u].push_back(v); Q[v].push_back(u);
		}
	}
}
void find(int x, int fa){
	sum += 2;  d[x] = 0;
	if(s[x] == 'W' && Q[x].size() % 2 == 0) sum += 1, d[x] = 2;
	if(s[x] == 'B' && Q[x].size() % 2 == 1) sum += 1, d[x] = 2;
	for(int i = 0; i < Q[x].size(); i++){
		int v = Q[x][i]; if(v == fa) continue;
		find(v, x);
	}
}
void solve(int x, int fa){
	dp[x] = d[x]; int maxx = 0, cmaxx = 0;
	for(int i = 0; i < Q[x].size(); i++){
		int v = Q[x][i]; if(v == fa) continue;
		solve(v, x); 
		if(dp[v] > maxx) cmaxx = maxx, maxx = dp[v];
		else if(dp[v] > cmaxx) cmaxx = dp[v];
		
	}
	sumx = max(sumx, maxx + cmaxx + d[x]);
	dp[x] += maxx;
}
int main()
{
	n = read();
	for(int i = 1; i < n; i++){
		int x = read(), y = read();
		add(x, y); add(y, x);
	}
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i++) {
		ans += ((s[i] == 'W') ? 1 : 0);
		if(s[i] == 'W') rt = i;
	}
	if(ans == 0) {puts("0\n"); return 0;}
	if(ans == 1) {printf("1\n"); return 0;}
	dfs(1, 0);  find(rt, 0);
	sum = sum - 2; 	solve(rt, 0);
	cout << sum - sumx << endl;
	return 0;
}
```


---

