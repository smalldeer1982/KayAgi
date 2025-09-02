# [NWRRC 2013] Heavy Chain Clusterization

## 题目描述

一组生物学家正在寻找一种治疗病毒性疾病的方法。他们尝试了多种可能对抗病毒抗原的抗体，并选出了在实验中效果最好的 $n$ 种抗体。  

每种抗体通过其重链（由氨基酸序列组成）进行识别。  

如果满足以下至少一个条件，则这些抗体形成一个相似簇：  

- 所有重链的 k 前缀（前 $k$ 个氨基酸）相同；  
- 所有重链的 k 后缀（后 $k$ 个氨基酸）相同。  

为了简化未来的研究，生物学家希望将抗体分组为相似簇。  

你需要将给定的抗体划分为最少数量的相似簇。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 1
AA
AB
BB
BA
```

### 输出

```
2
2 1 2
2 3 4
```

## 样例 #2

### 输入

```
3 2
ABA
BAB
XY
```

### 输出

```
3
1 1
1 2
1 3
```

# 题解

## 作者：_Ch1F4N_ (赞：8)

考虑把每个字符串的前 $k$ 位和后 $k$ 位看成点，字符串看成边，那么一个字符串前缀后缀至少有一个是相似群体的前缀后缀，看成这条边的两个端点至少有一个被选中。

那么这就变成了一个最小点覆盖问题。

考虑匈牙利算法算出答案，然后考虑如何构造答案。

考虑右边没有被匹配的点，选中这些点向左边连的点，因此这个点本身就不用被选中，考虑左边刚刚被选中的点，它们在右边匹配的点就不用选了，那么它们在右边匹配的点就进入右边没有被匹配的点相同的流程，如此递归下去，那么左边便利到的点就会被选中，右边被遍历到的点就不会被选中。

如此便可以构造出选中的点，然后再分配字符串到集合即可。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

const int maxn = 1e6+114;
const int base = 1145141;
int vis[maxn],match[maxn];
vector<int> edge[maxn],fedge[maxn];
map<int,int> road[2][maxn];
int ans;
int fm[maxn];
bool hungary(int u){
	for(int v:edge[u]){
		if(vis[v]==1) continue;
		vis[v]=1;
		if(match[v]==0||hungary(match[v])==true){
			match[v]=u;
			fm[u]=v;
			return true;
		}
	}
	return false;
}

int pre[maxn],suf[maxn];

int n,k,cnt;
map<int,int> f;
map<int,int> p[2];
vector<int> chifan[2];
int use[maxn][2];

vector<int> answer[2];
map<int,int> pos[2];

int op[maxn][2];
vector<int> OUT[maxn][2];
void dfs(int u,int type){
	if(op[u][type]==1) return ;
	op[u][type]=1;
	if(type==0){
		dfs(fm[u],1);
	}
	else{
		for(int nxt:fedge[u]){
			if(nxt!=match[u]){
				dfs(nxt,0);
			}
		}
	}
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=0;j<k;j++){
			pre[i]=pre[i]*base+s[j];
		}
		for(int j=s.size()-1;j>=s.size()-k&&j<s.size();j--){
			suf[i]=suf[i]*base+s[j];
		}
		if(f[pre[i]]==0){
			f[pre[i]]=++cnt;
		}
		if(p[0][f[pre[i]]]==0)
			chifan[0].push_back(f[pre[i]]),p[0][f[pre[i]]]=1;
		if(f[suf[i]]==0){
			f[suf[i]]=++cnt;
		}
		if(p[1][f[suf[i]]]==0)
			chifan[1].push_back(f[suf[i]]),p[1][f[suf[i]]]=1;
		edge[f[pre[i]]].push_back(f[suf[i]]),fedge[f[suf[i]]].push_back(f[pre[i]]);
	}
	for(int i:chifan[0]){
		memset(vis,0,sizeof(vis));
		if(hungary(i)==true) ans++;
	}
	for(int i:chifan[1]){
		if(match[i]==0){
			dfs(i,1);
		}
	}
	for(int i=1;i<=n;i++){
		if(op[f[pre[i]]][0]==1){
			OUT[f[pre[i]]][0].push_back(i);
		}
		else if(op[f[suf[i]]][1]==0){
			OUT[f[suf[i]]][1].push_back(i);
		}
	}
	cout<<ans<<'\n';
	for(int i:chifan[0]){
		if(op[i][0]==1){
			cout<<OUT[i][0].size()<<' ';
			for(int j:OUT[i][0]) cout<<j<<' ';
			cout<<'\n';
		}
	}
	for(int i:chifan[1]){
		if(op[i][1]==0){
			cout<<OUT[i][1].size()<<' ';
			for(int j:OUT[i][1]) cout<<j<<' ';
			cout<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：vzcx_host (赞：3)

## 题目简述
$n$ 个字符串，一些字符串能被归为同一类当且仅当这些字符串的最长公共前缀或最长公共后缀至少为 $k$，求至少能归几类。
## 题解
下面指的前缀和后缀长度均为 $k$。

容易想到二分图匹配。

给出现过的不同前缀各建立一个起点，出现过的不同后缀各建立一个终点，一个字符串连接它对应的前缀和后缀，跑二分图最小点覆盖。由于最小点覆盖的定义，每一条边的两端至少有一个点被选中，因此每个字符串都能被归进去。

然后就是二分图最小点覆盖找方案，也是板子。

code：
```
vector<int>kt[MAXV];
//当i是起点，kt[i]为前缀相同的所有点
//当i是终点，kt[i]为后缀相同的所有点
map<string,int>ss,tt;
//ss[str]为前缀为str表示的点
//tt[str]为后缀为str表示的点
int n,k,t,cnt=0,aa,bb;string s,as,bs;
n=read();k=read();
for(int i=1;i<=n;i++){
	cin>>s;t=s.size();
	as=bs="";
	for(int j=0;j<k;j++)
		as+=s[j];
	for(int j=t-k;j<t;j++)
		bs+=s[j];
	aa=ss[as];bb=tt[bs];
	if(aa==0)aa=ss[as]=++cnt,add(S,cnt,1),add(cnt,S,0);
	if(bb==0)bb=tt[bs]=++cnt,add(cnt,T,1),add(T,cnt,0);
	add(aa,bb,1);add(bb,aa,0);
	kt[aa].push_back(i);
	kt[bb].push_back(i);
}
//然后跑一遍Dinic，然后是二分图最小点覆盖找方案
```

---

## 作者：伊地知虹夏 (赞：2)

## 1.建模

题目要你求最小的相似群体数量覆盖所有基因序列，很像二分图最小点覆盖。

我们把每个基因序列看作一条边，前后缀看作点，跑二分图最小点覆盖即可。

## 2.输出

如果只要求最小点覆盖数量还好，但它要输出方案，难度飙升。

我们考虑没有匹配上的右部点 $x$，有 $x \rightarrow y$ 这条边，既然 $x$ 未被匹配，那么就要求 $y$ 一定在最小点覆盖点集中。

我们把所有右边未匹配上的点 $x$，将所有的 $y$ 都标记。然后从标记的点 $y$ 开始寻找出点 $z$，由于 $y$ 可覆盖这条边，故 $z$ 必须不在点集中。最后由每个点集中的点访问出边编号并去重输出即可。

**$\Large{\texttt{But,it can't Accept!}}$**

根本原因是在这张图中，从 $5$ 出发求解会使得 $1,2$ 状态未定，所以，我们需要 $\texttt{dfs}$，对于左部点，我们往匹配点走，右部点往非匹配点走，并标记。

![](https://cdn.luogu.com.cn/upload/image_hosting/uczf7yfv.png)

[代码](https://www.luogu.com.cn/paste/8q5h9bo4)就放剪贴板了，~~为了造福苍生~~，还有几组 $\texttt{Hack}$ 数据也附在剪贴板上。


---

## 作者：Inter12 (赞：1)

[食用博客体验感更佳](https://www.luogu.com.cn/article/krk30lwe)~~其实并没有~~。

## 题目大意

给定 $n$ 个字符串，求能够分成几份字符串集合，每份中的所有字符串都存在长度为 $k$ 的前缀或后缀相同。

## 题目变形

- 由字符串变图论：

1. 我们根据观察发现，一个字符串被分到某一个字符串集合中有三种可能，其中，单独成一个集合我们可以认为他被**孤立**了，等到时候再做特殊处理。题目特别说明没有相同字符串，加上 $k$ 是一个定值，也就是任何字符串的长度为 $k$ 的前后缀恒定。

2. 因而，我们可以将字符串抽象成一条边，而对应的两种可能便以前后缀的点权形式在其两端，而具有相同前缀或后缀的字符串共点，整个问题就成了一个**无向图的问题**。

- 由普通图变二分图：

由于一条无向边只会连接前后缀，因而我们很容易就将整个图划分为两部分：前缀和后缀，而因为不会有边连接前缀和前缀或者后缀和后缀，因而整张图的这两部分各自内部**无连边**，也就是整幅图为二分图。

- 由二分图和题目本身明晰解决方案：

1. 题目要我们划分集合，集合内的字符串（**无向边**）都共点，且都共前缀或者后缀。

2. 站在一条边的角度，他要么加入前缀的集合，要么加入后缀的集合，**单独成一组可以理解为他可以加入任意一个集合，或者两者都加入，将其平常化**。

3. 这时，就出现了**至少二选一**的特性，结合本图是一张二分图，因而，题目要求的就是**二分图最小点覆盖**。

### 引申

二分图最小点覆盖等于二分图最大匹配的证明，这里不再赘述，如有不知道或者感兴趣的，请移步[这里](https://www.luogu.com.cn/article/6rd1l7p1)。

## 重点做法

### 寻找方案

这道题的难点之一就是如何输出二分图最小点覆盖的边的方案，如下图（我这里特意分了左右部，方便查看）：

![](https://cdn.luogu.com.cn/upload/image_hosting/828zapbh.png)

假设二分图最大匹配匹配了 $1 \to 4,3 \to 2,5 \to 6$ 三条。

步骤如下：

1. 先从右部的一个没有匹配的点 $x$ 出发，由于二分图最大匹配中，此点所连的边没有拿下匹配边的资格，因而选择 $x$ 为二分图最大点覆盖显然不值。

2. 但是，这一条边又必须覆盖到，因而他所连的边的端点 $y$ 必须选入（可能不止一个 $y$ 点）。

3. 而因为 $y$ 点被选入了，因而他所连的边的 $z$ 点无需选入（同样可能不止一个也可能没有）。

4. 重复 $1 \to 3$ 步骤，直至被选完为止。

但是，像上图中由 $5,6,7$ 三点组成的连通块并未算入，是因为右部 $6$ 号点已经有匹配点了，但是整个连通块只有他一个右部点（不一定所有图出现这种情况右部都只有一个点，重点是“都有匹配点”）。

在这种情况之下，我们要清楚以下几点：

1. 右部点一定小于等于左部点，因为右部点都已经都有匹配点了，说明左部点至少有右部点那么多个点来做匹配点。

2. 由于右部点都已经有匹配点了，因而选择左部的点不一定最优，但是全选右部的点一定最优，并且能覆盖所有的边，而且，右部点数量小于等于左部点数量。

因而，我们可以再扫一遍，寻找已经匹配了但是又未按上述步骤找到的右部点，将其纳入二分图最小点覆盖的选点中。

### 输出方案

根据二分图最小点覆盖的定义，只要输出与其相邻的边就可以了。

由于无向边一定是连接着前缀和后缀，所以与一个点接壤的所有边一定能在一个集合内。

同时，这样做根据定义，也不会遗漏任何一条边。

但是，如果遇上下面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/aa127o91.png)

此时选的是 $3,4$ 两点，正好是同一条边的两个端点，因而按照上述做法，需要判重。

## 部分代码

```cpp
cin >> n >> k;
for(int i = 1; i <= n; i++)
{
	cin >> s[i];
	string st = s[i].substr(0, k);
	if(!Mapst[st])
		Mapst[st] = ++cntst; // 前缀 
}
cnted = cntst; // 错开编号，因为是双向边，同时防止编号冲突 
for(int i = 1; i <= n; i++)
{
	string st = s[i].substr(0, k), ed = s[i].substr(s[i].size() - k);
	if(!Maped[ed])
		Maped[ed] = ++cnted; // 后缀 
	nbr[Mapst[st]].push_back((node){Maped[ed], i});	 // 双向边 
	nbr[Maped[ed]].push_back((node){Mapst[st], i});	
}
for(int i = 1; i <= cntst; i++) // 匈牙利 
	if(hungary(i, ++tim))
		ans++;
for(int i = cntst + 1; i <= cnted; i++) // 第一遍找寻答案 
	if(!mth[i] && !vis[i])
		dfs(i, 1, tim);
for(int i =  1; i <= cnted; i++) // 第二遍扫描 
	if(mth[i] && !vis[i])
		Tsn[i] = 1; // Tsn[i]表示第i个点有没有被选上 
```

内容较为通俗，可能并不严谨，望众位指出错误，谢谢！

---

## 作者：wangyibo201026 (赞：1)

## 思路

首先不难发现，对于一个字符串而言，要不就加入它前缀 $k$ 位的集合，要不就加入它后缀 $k$ 位的集合，而且可以两个都加入（我们只要再输出方案时去一下重即可），所以着明显是一个最小点覆盖问题，发现可以将一个字符串所在前缀 $k$ 位向后缀 $k$ 位连边。这样问题就变成了二分图求最小点覆盖问题，而我们又知道二分图的最小点覆盖等于二分图的最大匹配，所以就可以用**匈牙利算法**求了。

但是我们发现要输出一组方案，而我们求的又是最大匹配而不是最小点覆盖。于是我们思考怎么输出方案。

我们先开一个标记数组 $p$，不难想到一个事情，就是如果我们枚举右部点（后缀结点），如果它没打上标记且 $match = 0$，那么给这个点连向的左部点都打上标记，表示可以加入最小点覆盖的点集中，然后枚举这些左部点，把它们连向的右部点打上标记，表示是不能加入点集的。这个应该很好理解，但是一下这组数据可以卡掉它：

```
1 3
1 4
2 4
2 5
```

其中我们发现，$1$ 和 $4$ 竟然没有打标记！所以我们采用 DFS 来实现这一过程，具体步骤如下：

- 枚举右部点，如果这个点 $match_x = 0$，那么进行 DFS。
- DFS 内部，给遍历到的结点 $x$ 打上标记。
- DFS 内部，如果这个点是右部点，那么通过**非匹配边**，也就是不是最大匹配的边走向左部点（注意左部点应该是没有打过标记的）。
- DFS 内部，如果这个点是左部点，那么通过**匹配边**，也就是最大匹配的边走向右部点。

然后输出方案就完成了！

接下来我们解决一些小问题：

- 字符串前缀后缀用 map 和 substr 函数处理。
- 注意右部点打了标记的不能加入点集，左部点没打标记的不能进入点集。
- 最后输出时，可能两个点集里的点覆盖的字符串时一样的，需要去重，但一定不会全部去掉，否则答案就应该少 $1$。

## 代码

接下来上的是作者跳了一个半（~~为什么不是两个半~~）的代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define fir first
#define sec second
#define int long long 

char _c; bool _f; template < class T > inline void read ( T &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit (_c) ){
		if ( _c == '-' ) { _f = 1; }
	}
	while ( isdigit (_c) ){
		x = x * 10 + _c - '0', _c = getchar ();
		if (_f) { x = -x; }
	}
}

const int N = 1e4 + 5;
const int M = 2e6 + 5;

int n, k;
int match[N], m2[N];
bool vis[N];

int head[N], tot;

struct Node {
	int to, next;
} edges[M << 1];

void add ( int u, int v ) {
	tot ++;
	edges[tot].to = v;
	edges[tot].next = head[u];
	head[u] = tot;
}

bool hungary ( int x ) { // 匈牙利
	for ( int i = head[x]; i; i = edges[i].next ) {
		if ( !vis[edges[i].to] ) {
			vis[edges[i].to] = true;
			if ( !match[edges[i].to] || hungary ( match[edges[i].to] ) ) {
				match[edges[i].to] = x;
				m2[x] = edges[i].to; // 表示左部点连向的右部点，在 DFS 中有用
				return true;
			}
		}
	}
	return false;
}

int cnt;
int a[N], b[N];
vector < int > f[N], g[N];
unordered_map < string, int > mp, mp2;

int getid ( string t ) {
	if ( mp[t] ) {
		return mp[t];
	}
	mp[t] = ++ cnt;
	return cnt;
}

int getid2 ( string t ) {  // 注意我是分两个 getid 写的，否则可能会存在一个编号 x，使得 x 即是前缀又是后缀，就不好搞了
	if ( mp2[t] ) {
		return mp2[t];
	}
	mp2[t] = ++ cnt;
	return cnt;
}

bool p[N], used[N]; // p 用来打标记，used 用来输出去重

vector < int > e[N];

void dfs ( int x, int op ) {
	p[x] = true;
	if ( op == 0 ) {
		dfs ( m2[x], 1 );
	}
	else {
		for ( int i = 0; i < e[x].size (); i ++ ) {
			int v = e[x][i];
			if ( v != match[i] && !p[v] ) { // 打了标记才能遍历
				dfs ( v, 0 );
			}
		}
	}
}

string s;

void Solve () {
	cin >> n >> k;
	for ( int i = 1; i <= n; i ++ ) {
		cin >> s;
		f[getid ( s.substr ( 0, k ) )].push_back ( i );
		reverse ( s.begin (), s.end () );
		g[getid2 ( s.substr ( 0, k ) )].push_back ( i ); // f 标记一个相同前缀所包含的字符串，g 标记一个相同后缀所包含的字符串
	}
	for ( int i = 1; i <= cnt; i ++ ) {
		if ( f[i].size () ) {
			for ( int j = 0; j < f[i].size (); j ++ ) {
				a[f[i][j]] = i;
			}
		}
		if ( g[i].size () ) {
			for ( int j = 0; j < g[i].size (); j ++ ) {
				b[g[i][j]] = i;
			}
		}
	}
	for ( int i = 1; i <= n; i ++ ) {
		add ( a[i], b[i] );
		e[b[i]].push_back ( a[i] );  // 记一下反边
	}
	int ans = 0;
	for ( int i = 1; i <= cnt; i ++ ) {
		if ( f[i].size () ) { // f[i].size 表示是左部点，g[i].size 表示是右部点
			memset ( vis, false, sizeof ( vis ) );
			ans += hungary ( i );
		}
	}
	cout << ans << '\n';
	for ( int i = 1; i <= cnt; i ++ ) {
		if ( g[i].size () && !match[i] ) { // DFS 打标记
			dfs ( i, 1 );
		}
	}
	for ( int i = 1; i <= cnt; i ++ ) {
		if ( f[i].size () ) {
			if ( p[i] ) {
				int siz = 0;
				for ( int j = 0; j < f[i].size (); j ++ ) {
					if ( !used[f[i][j]] ) {
						siz ++;
					}
				}
				cout << siz << " ";
				for ( int j = 0; j < f[i].size (); j ++ ) {
					if ( !used[f[i][j]] ) { // 表示没有重复
						cout << f[i][j] << " ";
						used[f[i][j]] = true;
					}
				}
				cout << '\n';
			}
		}
		if ( g[i].size () ) {
			if ( !p[i] ) {
				int siz = 0;
				for ( int j = 0; j < g[i].size (); j ++ ) {
					if ( !used[g[i][j]] ) {
						siz ++;
					}
				}
				cout << siz << " ";
				for ( int j = 0; j < g[i].size (); j ++ ) {
					if ( !used[g[i][j]] ) {
						cout << g[i][j] << " ";
						used[g[i][j]] = true;
					}
				}
				cout << '\n';
			}
		}
	}
}

signed main () {
	Solve ();
	return 0;
}
```

---

