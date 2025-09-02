# Zublicanes and Mumocrates

## 题目描述

It's election time in Berland. The favorites are of course parties of zublicanes and mumocrates. The election campaigns of both parties include numerous demonstrations on $ n $ main squares of the capital of Berland. Each of the $ n $ squares certainly can have demonstrations of only one party, otherwise it could lead to riots. On the other hand, both parties have applied to host a huge number of demonstrations, so that on all squares demonstrations must be held. Now the capital management will distribute the area between the two parties.

Some pairs of squares are connected by $ (n-1) $ bidirectional roads such that between any pair of squares there is a unique way to get from one square to another. Some squares are on the outskirts of the capital meaning that they are connected by a road with only one other square, such squares are called dead end squares.

The mayor of the capital instructed to distribute all the squares between the parties so that the dead end squares had the same number of demonstrations of the first and the second party. It is guaranteed that the number of dead end squares of the city is even.

To prevent possible conflicts between the zublicanes and the mumocrates it was decided to minimize the number of roads connecting the squares with the distinct parties. You, as a developer of the department of distributing squares, should determine this smallest number.

## 样例 #1

### 输入

```
8
1 4
2 4
3 4
6 5
7 5
8 5
4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
1 5
```

### 输出

```
2
```

# 题解

## 作者：lgswdn_SA (赞：8)

不难且显然的树形 $dp$.

既然 $n\le 5000$，我们可以放心大胆地设二维状态。$f(u,i)$ 表示以 $u$ 为根的子树中有 $i$ 个叶节点染黑色（即 zublicanes）。最终黑色数量要到达 $\frac{leaf}{2}$。如果黑色节点到达了，那么白色节点也一定会满足要求。

又因为相邻只有可能是父子关系，计算 $f(u)$ 需要用到 $v$ 的颜色，所以记录 $f(u,i,0/1)$ 代表 $u$ 染白色（mumocrates）或白色（zublicanes）。

转移方程很好推，用一个类似于树形背包的转移。

$$
f(u,i+j,0)=f(u,i,0)+\min \{f(v,j,0),f(v,j,1)+1\}
$$
$$
f(u,i+j,1)=f(u,i,1)+\min \{f(v,j,0)+1,f(v,j,1)\}
$$

如果 $u$ 是叶节点，那么 $f(u,0,0)=f(u,1,1)=0$

套上一个树形 DP 模板即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5009;

struct edge {int to,nxt;}e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]}; hd[u]=tot;}

int n,leaf,lcnt[N],l[N];
void dfs1(int u,int fa) { //get leaves
	for(int i=hd[u],v;i;i=e[i].nxt) {
		l[u]++;
		if((v=e[i].to)==fa) continue;
		dfs1(v,u);
	}
	leaf+=(l[u]==1);
}

int f[N][N][2],g[N][2];
void dfs2(int u,int fa) { //tree bag dp
	if(l[u]==1) {
		f[u][0][0]=f[u][1][1]=0; lcnt[u]=1;
		return;
	}
	bool vst=0;
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		dfs2(v,u);
		if(!vst) {
			for(int k=0;k<=lcnt[v];k++)
				f[u][k][0]=min(f[v][k][0],f[v][k][1]+1),
				f[u][k][1]=min(f[v][k][0]+1,f[v][k][1]);
		}
		else {
			for(int j=0;j<=min(lcnt[u],leaf/2);j++)
				for(int k=0;k<2;k++)
					g[j][k]=f[u][j][k],f[u][j][k]=0x3f3f3f3f;
			for(int j=0;j<=min(lcnt[u],leaf/2);j++) {
				for(int k=0;k<=min(lcnt[v],leaf/2-j);k++) {
					f[u][j+k][0]=min(f[u][j+k][0],g[j][0]+min(f[v][k][0],f[v][k][1]+1));
					f[u][j+k][1]=min(f[u][j+k][1],g[j][1]+min(f[v][k][1],f[v][k][0]+1));
				}
			}
		}
		vst=1; lcnt[u]+=lcnt[v];
	}
}

int main() {
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v), add(u,v), add(v,u);
	dfs1(1,0);
	memset(f,0x3f,sizeof(f));
	int root=1;
	while(l[root]==1) root++;
	dfs2(root,0);
	printf("%d",min(f[root][leaf/2][0],f[root][leaf/2][1]));
	return 0;
}
```

---

**UPDATE**  

经过 Isaunoya 巨佬的提醒，这组数据确实可以 Hack 掉这个代码，但是反 Hack 也很简单。

```
2
1 2
```

出问题的原因是这组数据没有任何一个满足的 `root`。但是，可以证明，出现这种情况当且仅当 $n=2$，所以特判一下即可。

```
if(n==2) return puts("1"), 0;
```

~~所以为啥 CF 没有这种情况的 Hack 数据啊~~

---

## 作者：gesong (赞：3)

题目传送门：[CF581F Zublicanes and Mumocrates](https://www.luogu.com.cn/problem/CF581F)。

# 思路

一眼类似背包的树形 dp。

设 $f_{i,j,0/1}$ 表示以 $i$ 为根的节点其中有 $j$ 个叶子的颜色为黑色且 $i$ 的颜色为黑色或白色。

转移类似树形背包。

$$f_{u,i+j,0}=\min_{v\in son_u}(f_{u,i,0}+f_{v,j,0},f_{u,i,0}+f_{v,j,1}+1)\\
f_{u,i+j,1}=\min_{v\in son_u}(f_{u,i,1}+f_{v,j,1},f_{u,i,1}+f_{v,j,0}+1)
$$

按照方程转移即可，注意根节点要选择一个度数不为 $1$ 节点，然后特判 $n=2$ 的情况。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N=5010;
int f[N][N][2],n,d[N],sz[N],tmp[N][2];
vector<int>a[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
inline int min(int a,int b,int c){
	return min(min(a,b),c);
}
void dfs(int u,int fa){
	if (d[u]==1){
		f[u][1][1]=1e18;
		f[u][0][0]=1e18;
		f[u][1][0]=f[u][0][1]=0;
		sz[u]=1;
		return ;
	}
	sz[u]=0;
	int cnt=0;
	for (auto v:a[u]) if (v^fa){
		dfs(v,u);
		for (int i=0;i<=sz[u]+sz[v];i++) tmp[i][0]=tmp[i][1]=1e18;
		cnt++;
		if (cnt==1){
			for (int i=0;i<=sz[v];i++) f[u][i][0]=min(f[v][i][0],f[v][i][1]+1),f[u][i][1]=min(f[v][i][0]+1,f[v][i][1]);
			sz[u]+=sz[v];
			continue;
		}
		for (int i=0;i<=sz[u];i++)
			for (int j=0;j<=sz[v];j++){
				tmp[i+j][0]=min(tmp[i+j][0],f[u][i][0]+f[v][j][1]+1,f[u][i][0]+f[v][j][0]);
				tmp[i+j][1]=min(tmp[i+j][1],f[u][i][1]+f[v][j][0]+1,f[u][i][1]+f[v][j][1]);
			}
		sz[u]+=sz[v];
		for (int i=0;i<=sz[u];i++) f[u][i][0]=tmp[i][0],f[u][i][1]=tmp[i][1];
	}
}
main(){
	memset(f,0x3f,sizeof(f));
	n=read();
	if (n==2){
		puts("1");
		return 0;
	}
	for (int i=1;i<n;i++){
		int u=read(),v=read();
		a[u].push_back(v);
		a[v].push_back(u);
		d[u]++,d[v]++;
	}
	int ans=0;
	for (int i=1;i<=n;i++) ans+=d[i]==1;
	int x=1;
	while(d[x]==1) x++;
	dfs(x,0);
	cout <<min(f[x][ans/2][0],f[x][ans/2][1]);
    return 0;
}
```

---

## 作者：ZeroOf149 (赞：1)

# [CF581F Zublicanes and Mumocrates](https://www.luogu.com.cn/problem/CF581F)

## 题目描述

给一棵无根树，恰当地为节点染上黑白两种颜色，使得恰有一半数量的叶子节点是黑色，且两个端点不同色的边数最少。  
保证叶子节点数量为偶数。$2 \leq n \leq 5\times 10^3$。

## 解法说明

考虑树形 dp。

由于将树上所有节点反色后答案不变，不妨钦点根为黑色。  
记 $cnt_u$ 表示在 $u$ 的子树内的叶子节点个数，若我们再记 $dp_{u,i}(0\leq i\leq cnt_u)$ 表示在**黑色点** $u$ 的子树内选中 $i$ 个**黑色**叶子节点时的答案，则对于 $u$ 的一个孩子 $v$，我们可以仿照树形背包的方法转移。   
记当前 $u$ 子树内选中 $i$ 个黑色叶子节点，而 $v$ 子树内选中 $j$ 个。转移分两种情况：
  - $u, v$ 同色，此时答案为 $dp_{u,i}+dp_{v,j}$；
  - $u, v$ 不同色，此时我们应将 $v$ 的子树反色，那么 $v$ 的子树内应恰有 $(cnt_v-j)$ 个白色点，答案为 $dp_{u,i}+dp_{v,cnt_v-j}$。

因此，我们有以下转移式：  
$$$
dp'_{u,i+j} \gets \min\{dp_{u,i}+dp_{v,j}, dp_{u,i}+dp_{v,cnt_v-j}\}(0\leq i\leq cnt_u, 0\leq j \leq cnt_v)
$$$

注意当 $u$ 为叶子节点时，子树内不能没有黑色叶子节点，因此这时有 $dp_{u,0} = +\infty$；非叶子节点则保持不变即可。

直接转移，有时间复杂度 $O(n^2)$，可以通过本题。

## [代码实现](https://codeforces.com/contest/581/submission/319865779)

为了初始化的方便，以下代码求了两端颜色相同的边的最大值。转移与上文类似。

```cpp
#include <algorithm>
#include <cstdio>
#include <vector>

constexpr int N = 5e3 + 5, Inf = 0x3f3f3f3f;

int n, d[N], cnt[N], dp[N][N], tmp[N];
std::vector<int> g[N];

void dfs(int u, int f) {
  cnt[u] = (d[u] == 1);
  if (d[u] == 1) dp[u][0] = -Inf;
  for (auto&& v : g[u]) {
    if (v == f) continue;
    dfs(v, u);
    std::fill(tmp, tmp + cnt[u] + cnt[v] + 1, 0);
    for (int i = 0; i <= cnt[u]; ++i)
      for (int j = 0; j <= cnt[v]; ++j) {
        tmp[i + j] = std::max(tmp[i + j], dp[u][i] + dp[v][j] + 1);
        tmp[i + j] = std::max(tmp[i + j], dp[u][i] + dp[v][cnt[v] - j]);
      }
    std::copy(tmp, tmp + cnt[u] + cnt[v] + 1, dp[u]);
    cnt[u] += cnt[v];
  }
}

int main() {
  scanf("%d", &n);
  if (n == 2) return printf("1"), 0;
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    ++d[u];
    ++d[v];
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int rt = 1; rt <= n; ++rt)
    if (d[rt] != 1) {
      dfs(rt, 0);
      printf("%d", n - 1 - dp[rt][cnt[rt] >> 1]);
      break;
    }
}
```

---

## 作者：Sky_Maths (赞：1)

# 前言
其实这道题也不是我自己做出来的。

因为我以为自己的算法会超时，但其实没有，后来经 yhh 学长提醒，算了一下**效率**，$n=5000$ 竟然只需要 $10^7$ 左右。

然后我的写法也与其他人不一样，可以说是进行了常数优化，故来写一篇题解。

# 正文
首先，只要确定了所有叶子节点的颜色，最终答案一定确定。

其次，对于一棵确定了颜色的树，若其中有 $i$ 个黑色叶子且根颜色为黑，设答案为 $f_{u,i}$ ，若有两棵树的 $f_{u,i}$ 都相等，则可以视为等价，同时若其中有 $i$ 个白色叶子且根颜色为白，答案必定也为 $f_{u,i}$。

于是可以想到设 $f_{u,i,0/1}$ 代表以 $u$ 为根的子树，有 $i$ 个叶子节点为黑色，且根节点为白/黑色的最小不相同边数。

于是可以利用树上背包进行转移。

但是又发现 $f_{u,i,0/1}=f_{u,leaf_{u}-i,1/0}$ 那为什么我们要多一维呢？

于是设 $f_{u,i,0/1}$ 代表以 $u$ 为根的子树，有 $i$ 个叶子节点为黑色，且根节点为黑色的最小不相同边数。

然后在每棵树遍历完后别忘了使 $f_{u,i}=\min\{f_{u,i},f_{u,leaf_u-i}+1\}$

# 提示
然后对于时间效率的问题，可以这样：
$$T(n)=\max\limits_{i}\{T(i)+T(n-i)+i\cdot(n-i)\}$$

所以这样是 $O(n^2)$ 的？有没有人知道？

# 代码
加了优化，所以跑的比较快
```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(register int i(l),i##end(r);i<=i##end;++i)
#define per(i,r,l) for(register int i(r),i##end(l);i>=i##end;--i)
#define nex(i,u) for(int i(e.head[u]);i;i=e.nxt[i])
using namespace std;
#define gc getchar
#define pc putchar
#define be begin
#define ed end
#define ci const int
inline void rd(int &x) {
	x=0; char ch=gc(); bool f=0;
	while((ch<'0'||ch>'9')&&ch!='-') ch=gc();
	if(ch=='-') f=true,ch=gc();
	while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
	if(f) x=-x;
}
ci N = 5009;
ci M = N << 1;
int n,start,sum;
int ind[N],siz[N];
int f[N][N];
struct EDGES {
	int el=0;
	int head[N]={0},nxt[M],v[M];
	void add(int &x,int &y) {
		nxt[++el]=head[x];
		head[x]=el;
		v[el]=y;
	}
}e;
inline void cmin(int &a,int b) {if(a>b) a=b;}
inline void dfs(int &u,int la) {
	if(ind[u]==1) {
		siz[u]=1;
		f[u][1]=0;
		f[u][0]=1;
		return ;
	}
	nex(i,u) {
		int v=e.v[i];
		if(v==la) continue;
		dfs(v,u);
		if(siz[u]) {
			rep(j,siz[u]+1,siz[u]+siz[v]) f[u][j]=n;
			siz[u]+=siz[v];
			per(j,siz[u],0) {
				f[u][j]+=f[v][0];
				rep(k,1,min(siz[v],j)) {
					cmin(f[u][j],f[u][j-k]+f[v][k]);
				}
			}
		}
		else {
			siz[u]=siz[v];
			rep(j,0,siz[u]) {
				f[u][j]=f[v][j];
			}
		}
	}
	int j=siz[u];
	rep(i,0,siz[u]) cmin(f[u][i],f[u][j]+1),--j;
}
main() {
	rd(n);
	if(n==2) return printf("1\n"),0;
	int u,v; rep(i,2,n) {
		rd(u); rd(v);
		e.add(u,v);
		e.add(v,u);
		++ind[u];
		++ind[v];
	}
	rep(i,1,n) if(ind[i]>1) {
		start=i;
		break;
	}
	dfs(start,0);
	printf("%d\n",f[start][siz[start]/2]);
	return 0;
}
```

---

## 作者：littlesnake (赞：0)

- 前言

竟然还能交题解！这题不是板子题吗？虽然我觉得很难。来源于某市某老师。

- 思路

考虑树形 DP。因为树上所有点反色后答案不变，所以我们钦定 $f_{i,j}$ 表示钦定 $i$ 为黑色，有 $j$ 个节点是黑色的。

在考虑 $x$ 的子树时，每次考虑一个 $y$ 的子树，用背包的形式把这个子树合并起来。

$$f_{x,i+j}=f_{x,i}+f_{y,j}$$

$$f_{x,i+j}=f_{x,i}+f_{y,cnt_y-j}+1$$

注意当 $x$ 为叶子节点时，子树内不能没有黑色叶子节点，因此这是有 $dp_{x,0}$ 等于无穷。

---

## 作者：Zwb0106 (赞：0)

**[原题链接](https://codeforces.com/contest/581/problem/F)**


------------

简单树形 DP，写这篇题解是想对其他题解做一个补充。

------------
## 思路

先设计状态，首先第一维肯定是子树 $u$，而 $n\le 5000$ 可以让我们放心地在第二维记子树内的叶子数目，于是我们记 $f_{u,i}$ 表示将子树 $u$ 内的节点全部染色，且其中的 $i$ 个叶子染为黑色，能够最小化的两端颜色不同的边数。

如果进行转移，会发现我们合并子节点 $v$ 为根的子树需要用到 $v$ 的颜色，这样才能确定边 $(u,v)$ 是否对答案有贡献。略作修改，记 $f_{u,i,0/1}$，表示将 $u$ 染为黑色 / 白色的答案，$0$ 表示黑色，$1$ 表示白色。

于是，对于叶子节点，边界为 $f_{u,1,0}=f_{u,0,1}=1$；对于非叶子节点，边界为 $f_{u,0,0}=f_{u,0,1}=0$，这是由于合并子节点 $v$ 的答案前，将 $u$ 看作孤点。

现在考虑转移，容易得到：

$$f_{u,i,0} \leftarrow \min \limits_{j=0}^{\min\{i,s_v\}} \left ( f_{u,i-j,0}+ \min \{ f_{v,j,0},f_{v,j,1}+1 \} \right )$$

$$f_{u,i,1} \leftarrow \min \limits_{j=0}^{\min\{i,s_v\}} \left ( f_{u,i-j,1}+ \min \{ f_{v,j,1},f_{v,j,0}+1 \} \right )$$

其中 $s$ 表示子树内叶子个数。

然而 $f$ 会重复用到，事实上右式我们用于转移的 $f$ 表示的是合并当前 $v$ 之前的答案，避免覆盖，实际实现时用一个 $g$ 将 $f$ 存下来，将 $f$ 清空，再继续转移。

我们发现，这样初始化边界并没有限制根是否为一个叶子，因此就避免了对于 $n=2$ 这种情况的讨论，写起来也更加简洁明了。

------------
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define gc getchar
#define pc putchar
#define fs first
#define sc second
using namespace std;

ll read()
{
	ll x=0,f=1;
	char ch=gc();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc();
	}
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=gc();
	return x*f;
}
void print(ll x)
{
	if(x<0)pc('-'),x=-x;
	if(x>9)print(x/10);
	pc(x%10+48);
}

const int N=5005,INF=1e9;
int n,m,s[N],f[N][N][2],g[N][N];
vector<int>e[N];

void dfs(int u,int fa)
{
	if(e[u].size()==1)f[u][1][0]=f[u][0][1]=0,s[u]=1;
	else f[u][0][0]=f[u][0][1]=0,s[u]=0;
	for(int v:e[u])
	{
		if(v==fa)continue;
		
		dfs(v,u),s[u]+=s[v];
		
		for(int i=0;i<=s[u];i++)
		{
			g[i][0]=f[u][i][0],f[u][i][0]=INF;
			g[i][1]=f[u][i][1],f[u][i][1]=INF;
		}
		
		for(int i=0;i<=s[u];i++)
			for(int j=0;j<=min(i,s[v]);j++)
			{
				f[u][i][0]=min(f[u][i][0],g[i-j][0]+min(f[v][j][0],f[v][j][1]+1));
				f[u][i][1]=min(f[u][i][1],g[i-j][1]+min(f[v][j][1],f[v][j][0]+1));
			}
	}
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	
	memset(f,0x3f,sizeof(f));
	dfs(1,0);
	
	print(min(f[1][s[1]/2][0],f[1][s[1]/2][1]));
	
	return 0;
}
```

---

## 作者：Powerless233 (赞：0)

## Notice
题目的要求是 **叶子节点** 的颜色必须一半为黑、一半为白。

题目并没有保证 $1$ 不是叶子节点，因此，你需要先找到一个非叶子节点作为根，再进行后续的操作。

## Analysis
读完题，显然树形 dp。  

考虑什么状态可以进行转移：当我们进行子树合并的时候，**子节点与当前节点的颜色** 会影响花费，子树中 **叶子节点颜色的数量** 受到限制，因此我们只需要将这两个信息加入状态即可。

为方便讨论，我们定义黑色为 $1$ ，白色为 $0$ 。

$f_{x,j,p}$ 表示在点 $x$ 及其子树中 **叶子节点** 为 $1$ 的数量为 $j$ ，点 $x$ 的颜色为 $p$ $\big(  p \in \{0,1\} \big)$ 的最小花费。

至此，问题已经被转化成了一般的树上背包问题，接下来考虑对于当前节点 $x$ ，**已经合并的部分子树** 和 **下一棵等待合并的子树** 如何合并。

设当前节点为 $x$ ，等待合并的子树节点 $y$ ， $si_{x}$ 表示在 $x$ 及其子树中叶子节点的**总数**，枚举已经合并的子树中叶子节点为 $1$ 的个数 $j$ ，和等待合并的子树中叶子节点为 $1$ 的个数 $k$ 。

根据题意，若 $x$ 的颜色与 $y$ 不同，$x$ 的花费为 $y$ 的花费 $+1$ ，否则就为 $y$ 的花费。
有转移方程：

$$f_{x,j+k,0}=f_{x,j,0}+\min \{ f_{y,k,0},f_{y,k,1}+1\}$$
$$f_{x,j+k,1}=f_{x,j,1}+\min \{ f_{y,k,1},f_{y,k,0}+1\}$$

边界条件：

当 $x$ 为叶子节点时，在两种颜色下花费均为 $0$ ：

$$f_{x,0,0}=f_{x,1,1}=0$$

当 $x$ 为非叶子节点时，边界条件的意义是 **一颗空树（还未进行合并操作）**，因此有：

$$f_{x,0,0}=f_{x,0,1}=0$$

设叶子节点总数为 $cnt$ ，则答案即求：

$$\min \{ f_{root,cnt/2,0} f_{root,cnt/2,1}\}$$

## Code
```cpp
#include<bits/stdc++.h>
#define LL long long
#define inf 0x3f3f3f3f
using namespace std;
inline LL read(){
	LL res=0,fl=1;
	char ch=getchar();
	while(!(ch>='0' && ch<='9')){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0' && ch<='9')res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return res*fl;
}
inline LL max(LL a,LL b){return a>b?a:b;}
inline LL min(LL a,LL b){return a<b?a:b;}
inline void swap(int &a,int &b){int c;c=a;a=b;b=c;}
const int MAXN=5e3+5;
int n,rt,cnt=0,si[MAXN],g[MAXN][2],f[MAXN][MAXN][2];
vector<int> e[MAXN];
inline void Tree_dp(int x,int fa){
	for(int i=0;i<=cnt/2;i++)f[x][i][0]=f[x][i][1]=inf;
	
	if(e[x].size()>1)si[x]=f[x][0][0]=f[x][0][1]=0;
	else f[x][1][1]=f[x][0][0]=0,si[x]=1;//si[x] 的意义是叶子节点的数量，因此只在叶子结点统计 
	
	for(int i=0;i<e[x].size();i++){
		int y=e[x][i];
		if(y!=fa){
			Tree_dp(y,x);
			int up1=min(si[x],cnt/2),up2;
			for(int j=0;j<=up1;j++)
				for(int k=0;k<=1;k++)g[j][k]=f[x][j][k],f[x][j][k]=inf;
			//需要开一个临时数组存先前已经合并的子树信息，因为在合并的时候 j+k 可能与 j 的下标重复 
            
			for(int j=0;j<=up1;j++){
				up2=min(si[y],cnt/2-j);
				for(int k=0;k<=up2;k++){
					f[x][j+k][0]=min(f[x][j+k][0],g[j][0]+min(f[y][k][0],f[y][k][1]+1));
					f[x][j+k][1]=min(f[x][j+k][1],g[j][1]+min(f[y][k][1],f[y][k][0]+1));
				}
			}
			si[x]+=si[y];
			//先前枚举的是已经合并的子树，因此大小要在更新后再加上 
		}
	}
}
int main() {
	int x,y;
	n=read();
	for(int i=1;i<n;i++){
		x=read(),y=read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	if(n==2){
		cout<<1;
		return 0;
		//有可能根本找不到合法的根 
		//翻了别的题解发现好像 CF 并没有卡这一点 
	}
	for(int i=1;i<=n;i++)
		if(e[i].size()>1)rt=i;
		else cnt++;//统计叶子结点个数
	 
	Tree_dp(rt,0);
	cout<<min(f[rt][cnt/2][1],f[rt][cnt/2][0])<<'\n';
	return 0;
}
```


---

