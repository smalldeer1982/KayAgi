# [ABC394F] Alkane

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc394/tasks/abc394_f

给定一棵包含 $N$ 个顶点的无向树 $T$。顶点编号为 $1, 2, \ldots, N$，第 $i$ 条边连接顶点 $A_i$ 和顶点 $B_i$。

定义满足以下两个条件的图为**烷烃**：
- 该图是一棵无向树
- 所有顶点的度数为 $1$ 或 $4$，且至少存在一个度数为 $4$ 的顶点

请判断 $T$ 中是否存在满足烷烃定义的子图。若存在，求此类子图的顶点数的最大值；否则输出 $-1$。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq N$
- 输入的图是一棵无向树
- 所有输入值为整数

### 样例解释 1

选取顶点 $1, 2, 3, 4, 6, 7, 8, 9$ 及边 $(1,2)$、$(2,3)$、$(3,4)$、$(2,6)$、$(2,7)$、$(3,8)$、$(3,9)$ 构成的子图满足烷烃条件。其中顶点 $2$ 和顶点 $3$ 的度数为 $4$，其余顶点度数为 $1$，因此顶点数的最大值为 $8$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
1 2
2 3
3 4
4 5
2 6
2 7
3 8
3 9```

### 输出

```
8```

## 样例 #2

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
-1```

## 样例 #3

### 输入

```
15
8 5
2 9
1 12
6 11
9 3
15 1
7 12
7 13
10 5
6 9
5 1
1 9
4 5
6 14```

### 输出

```
11```

# 题解

## 作者：chenxi2009 (赞：6)

## 思路
树形 DP，考虑我们转移时需要什么信息：
- 当前子树根节点（当前结点）的度数；
- 子树里是否有度为 $4$ 的点。

所以可令 $f_{i,j,0/1}$ 表示以 $i$ 为根，$i$ 的度数为 $j$，选择的树内有无度数为 $4$ 的点时，这棵树最大的大小。

转移设计：初始 $f_{u,0,0}\leftarrow1$（一个点当一棵树）；

$f_{u,i,0}\leftarrow\max(f_{u,i-1,0}+1)(\text{card}(\text{son\ of}\ u)>0)$（$u$ 有儿子，这个儿子接到 $u$ 的下面）

$f_{u,i,1}\leftarrow\max(f_{u,i-1,1}+1)(\text{card}(\text{son\ of}\ u)>0)$（同上）

$f_{u,i,1}\leftarrow\max(f_{u,i-1,0},f_{u,i-1,1})+\max(f_{v,3,0},f_{v,3,1})(v\in\text{son\ of}\ u)$（$v$ 作为一个儿子，原先度为 $3$，接上 $u$ 之后变成 $4$）

$\text{answer}=\max(f_{u,1,1},f_{u,4,0},f_{u,4,1})$（需要保证有度数为 $4$ 的点）

搜一遍就好了，时间复杂度 $O(N)$。转移时要判断值不为零，免得出现虚空儿子充当度数的情况。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,u,v,ans,f[300000][5][2];
vector<int>e[300000];
inline int max(int a,int b,int c,int d){return max(max(a,b),max(c,d));}
void sch(int u,int fa){
	f[u][0][0] = 1;
	for(auto v : e[u]){
		if(v == fa) continue;
		sch(v,u);
		for(int i = 4;i;i --){//倒序转移，防止需要的值被覆盖 
			if(f[u][i - 1][0]) f[u][i][0] = max(f[u][i][0],f[u][i - 1][0] + 1);
			if(f[u][i - 1][1]) f[u][i][1] = max(f[u][i][1],f[u][i - 1][1] + 1);
			if((f[u][i - 1][0] || f[u][i - 1][1]) && (f[v][3][0] || f[v][3][1])){
				f[u][i][1] = max(f[u][i][1],max(f[u][i - 1][0],f[u][i - 1][1]) + max(f[v][3][0],f[v][3][1]));
			}
		} 
	}
	ans = max(ans,f[u][1][1],f[u][4][0],f[u][4][1]);
	return;
}
int main(){
	read(n);
	for(int i = 1;i < n;i ++){
		read(u,v);
		e[u].push_back(v),e[v].push_back(u);
	}
	sch(1,0);
	printf("%d",ans ? ans : -1);
	return 0; 
}
```

---

## 作者：wuzebang2009 (赞：5)

~~跨学科题目~~，题目意思是让你在一颗无向树中找节点数最大的烷烃的节点数——一颗节点度数只有 $1$ 或 $4$ 的树并且必须至少有一个节点度数为 $4$ ，我们用树形 dp 来做这题，设 $dp[i,j]$ 表示以 $i$ 为根的烷烃节点数为 $j$ ，那么我们知道烷烃是什么后，我们就可以知道一个根节点只能连一个度数为 $0$ 或度数为 $3$ 的节点 状态转移方程如下:
$$
  dp[x,i]_{1\le{x}\le4}=\max{dp[x,i-1]+\max{dp[v,y]_{y\in{1,3}}}}
$$ 

$v$ 为 $x$ 的子节点，则某个根节点的 $ans$ 就是原本的答案和这个节点舍弃一条边后转接另一合法节点边后的答案。

没结束 
$$
  ans=\max dp[x,i]_{i\in{1,4}}
$$

至此我们以有了完整的状态转移方程，题目就简单了。

## CODE:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[1000010][5];//当x有y个子节点时子树的大小 
int n,ans=-1;
vector<int> g[1000010];

void dfs(int x,int fa){
	dp[x][1]=dp[x][2]=dp[x][3]=dp[x][4]=-1e9;
	dp[x][0]=1;
	for(auto v:g[x]){
		if(v==fa) continue;
		dfs(v,x);
		for(int i=4;i>=1;i--) dp[x][i]=max(dp[x][i],dp[x][i-1]+max(dp[v][0],dp[v][3]));
	} 
	if(dp[x][1]>2) ans=max(dp[x][1],ans);
	ans=max(dp[x][4],ans);
}

signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1,0);
	cout<<ans;
}
```

---

## 作者：Mr_Az (赞：4)

# [AT_abc394_f [ABC394F] Alkane](https://www.luogu.com.cn/problem/AT_abc394_f)

### Algorithm:

树形 DP。

### Solution:

无解是好判断的，直接记录每个点的度数，看有没有至少一个点的度数大于等于 $4$ 即可。

考虑通过树形 DP 解决这个问题，需要注意与**父亲连接的边也算一个度数**，所以我们可以设计出一下状态：

$f_{u,x,0/1}$ 表示当前 $u$ 的度数为 $x$，在 $u$ 的子树内是否已经有了度数为 $4$ 的点时，拥有的最多的点的数量。

考虑如何转移（笔者想了半天，结果是个简单的 DP）。

注意到加粗部分，所以从下转移上来的儿子的度数只能是 $0$ 或者 $3$ 。我们额外记一个 $g_{x,0/1}$ 代表我们当前的度数为 $x$ ，子树中是否已经出现过度数为 $4$ 的点。转移类似背包。

### Code:

```cpp
const int N=2e5+8;
int n,ans;
int f[N][6][3],deg[N],g[6][3];
vector<int> e[N];
void dfs(int u,int fa){
    for(rint i=0;i<=4;i++) f[u][i][0]=f[u][i][1]=-inf;
    f[u][0][0]=1;f[u][0][1]=0;
    for(auto v:e[u]){
        if(v==fa) continue;
        dfs(v,u);
        for(rint i=0;i<=4;i++) g[i][0]=f[u][i][0],g[i][1]=f[u][i][1];
        for(rint i=1;i<=4;i++){
            for(rint j=0;j<=4;j++){
                if(j==0||j==3){
                    g[i][0]=max(g[i][0],f[u][i-1][0]+f[v][j][0]);
                    g[i][1]=max(g[i][1],f[u][i-1][0]+f[v][j][1]);
                    g[i][1]=max(g[i][1],f[u][i-1][1]+f[v][j][0]);
                    g[i][1]=max(g[i][1],f[u][i-1][1]+f[v][j][1]);
                    if(j==3||i==4) g[i][1]=max(g[i][1],f[u][i-1][0]+f[v][j][0]);
                }
            }
        }
        for(rint i=0;i<=4;i++) f[u][i][0]=g[i][0],f[u][i][1]=g[i][1];
    }
    ans=max({ans,f[u][1][1],f[u][4][1]});
    return ;
}
inline void solve(){
    read(n);
    bool valid=0;
    for(rint i=1,u,v;i<n;i++){
        read(u,v);
        e[u].pb(v),e[v].pb(u),deg[v]++,deg[u]++;
        valid|=(deg[v]>=4||deg[u]>=4);
    }
    if(!valid) puts("-1"),exit(0);
    dfs(1,0);
    printf("%lld\n",ans);
}
```

---

## 作者：__hjyakioi__ (赞：3)

简单树形dp。
## 思路
每个顶点的度数为 $1$ 或 $4$ 有点难处理，这意味着我们可以**对可能的根节点分别特殊处理**。

设 $dp_i$ 表示子树 $i$ 中，满足 **顶点被选中的子树数为 $0$ 或 $3$ , 且不为根节点** 或 **顶点被选中的子树数为 $4$ , 且为根节点**的子树的大小；
\
$sum_{i,j}$ 表示点 $i$ 的子树中， $dp$ 值前 $j$ 大的值的和；
\
$siz_i$ 表示点 $i$ 的边数。

假设点 $j$ 为根节点,可列 $dp$ 式：

当 $i \ne j$，且 $siz_i \ge 4 $ 时，$dp_{i}=sum_{i,3}+1$ （**因为父节点占了$1$个度数**）。
\
当 $i = j$，且 $siz_i \ge 4 $ 时，$dp_{i}=sum_{i,4}+1$ 。
\
否则，$dp_i=1$

由于可能有多个满足$siz_i \ge 4$的根，因此我们用`map`存储对于每个节点，父亲节点不同时 $dp$ 的值。

具体细节见代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
vector<int> a[N];
map<int,int>dp[N];
void dfs(int u, int fa)//dp
{
   //记忆化
    if (dp[u][fa] != 0)
        return;
    int need = 3 + (fa == 0);// 根节点需要4个子节点，非根需要3个

    vector<int> ls;
    for (auto i : a[u])//遍历所有子树
    {
        if (i != fa)
        {
            dfs(i, u);
            ls.push_back(dp[i][u]);
            sort(ls.begin(), ls.end(), greater<int>());
            if ((long long)ls.size() > need)
                ls.pop_back();// 存储前need大值
        }
    }
  //求dp值
    int sum = 0;
    for (auto i : ls)
        sum += i;
    dp[u][fa] = ((long long)ls.size() == need ? sum : 0) + 1;
}
int main()
{

    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);//邻接表存图
    }
    // 枚举所有可能的根节点（即度数>=4），并记录最大值
    int maxn = -1;
    for (int i = 1; i <= n; i++)
    {
        if (a[i].size() >= 4)
        {
            dfs(i, 0);
            maxn = max(maxn, dp[i][0]);
        }
    }
    cout << maxn;
}
```

---

## 作者：CLydq (赞：2)

# 题目

## 翻译

给你一棵有 $N$ 个节点的**无向树**，求这个**无向树**是否有 alkane（烷烃）子图。

alkane（烷烃）图的定义如下：
- 这张图是一棵**无向树**
- 这张图所有点的度数为 $1$ 或 $4$，但至少包含一个度数为 $4$ 的点。

## 提示

这里**树**和**无向树**不是一个东西。

主要区别在于，**树**计算度数时计算的是它的儿子的数量，而**无向树**计算度数时考虑的是它所连出去的边的数量。

可以认为，**无向树**中非根节点相对同一棵**树**中的对应节点而言，它的度数会多 $1$，因为有一条边连的是它的父节点。

# 思路

## 数据结构/算法

和树有关，还和度有关，不难联想到树形 dp。

既然是树形 dp，就先来设个状态：  
令 $dp_i$ 表示表示以 $i$ 为根的子树的答案最大值

## 过程

然后考虑转移：

$dp_i$ 应为它的所有儿子中 $dp_i$ 前 $4$ 大的，此时 $i$ 的度数为 $4$。

如果没有 $4$ 个儿子就只选最大的，此时 $i$ 的度数为 $1$。

如果还没有就是 $0$，因为在 $1$ 为根的树中它没有儿子，这意味着将它作为根截出子图的时候它的度数为 $0$。

然后我们发现一个问题：

令当前点为 $i$，它的一个儿子是 $j$。

$dp_i$ 的定义为：
$dp_i$ 表示表示以 $i$ 为根的子树的答案最大值

如果直接转移 $dp_i$，会发生如下情况：  
若 $dp_j$ 不为 $0$，那么转移时 $j$ 的度数要么是 $1$，要么是 $4$。  
无论哪种情况，只要让它往父节点连一条边，就会使得答案不满足要求。

所以这里不能直接用 $dp_j$ 来更新 $dp_i$。

这样的话我们可以新开一个数组 $a$，令 $a$ 定义为：  
$a_i$ 表示表示以 $i$ 为根的子树的答案最大值。

然后转换 $dp$ 的定义为：  
$dp_i$ 表示以 $i$ 为根且 $i$ 节点差一条边即可满足度数为 $1$ 或 $4$ 的条件。

这时 $dp$ 就可以向上转移了，答案即为 $a$ 数组的最大值。

浅写下分讨转移：

对于 $dp$ 而言：

1. 若 $i$ 有 $\ge 3$ 个儿子，则 $dp_i$ 取 $i$ 儿子前三大的 $dp$ 求和转移。
2. 否则，$i$ 不能再连任何一个儿子来满足条件，此时 $dp_i = 1$。

对于 $a$ 而言：

1. 若 $i$ 有 $\ge 4$ 个儿子，则 $a_i$ 取 $i$ 儿子前四大 $dp$ 求和转移。
2. 否则，若 $i$ 有 $\ge 1$ 个儿子，则 $a_i$ 取 $i$ 儿子中最大的 $dp$ 值。
3. 否则，$a_i = 0$。

如果数组是通过转移求得的，别忘了 +1。

## 细节

注意无解情况，即所有点都是 $1$ 度。

此时答案只可能是 $2$。

特判就行。

不过答案变量要考虑为 $0$ 情况，同时，因为显然答案不能是 $1$，所以认 $ans \le 2$ 为无解就行。

不过我的写法需要把 $dp_0$ 初始化为极小值，否则会 WA 一个点。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, u, v, dp[N], a[N], ans = -1;
/*
dp[i] 表示以 i 为根的子树的答案最大值，可以向上转移
a[i]  定义同 dp[i]，但是不能向上转移
*/
vector<int> g[N];
inline bool cmp(const int& a, const int& b) { return dp[a] > dp[b]; }
void dfs(int u, int fa) {
    int sum = 0;
    for (int& v : g[u])
        if (v != fa)
            dfs(v, u), sum++;
        else
            v = 0;
    sort(g[u].begin(), g[u].end(), cmp);
    if (sum >= 4)
        a[u] = dp[g[u][0]] + dp[g[u][1]] + dp[g[u][2]] + dp[g[u][3]] + 1;
    else if (sum >= 1)
        a[u] = dp[g[u][0]] + 1;
    else
        a[u] = 0;
    if (sum >= 3)
        dp[u] = dp[g[u][0]] + dp[g[u][1]] + dp[g[u][2]] + 1;
    else
        dp[u] = 1;
    ans = max(ans, a[u]);
}
signed main() {
    scanf("%d", &n), dp[0] = INT_MIN;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1, 1);
    printf("%d", ans <= 2 ? -1 : ans);
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：2)

树形 dp。记 $f_i$ 为以 $i$ 为根的答案。但是发现转移的时候 $i$ 和 $i$ 的父亲也有一条边，那么 $i$ 的度数就是 $5$，这就难办了。因此考虑修改一下状态定义，定义 $f_i$ 为以 $i$ 为根的答案，但是 $i$ 的度数为 $3$。

然后转移就是选 $i$ 孩子 $j$ 中 $f_j$ 的前三大值之和加 $1$，加 $1$ 是因为要算上 $i$ 本身。

接下来就是统计以 $i$ 为根答案。这时 $i$ 不需要连接自己的父亲，因此就是孩子 $f_j$ 的前四大值之和加 $1$。

但是以 $i$ 为根的答案要求是 $i$ 的度数为 $4$，因此在 dfs 最开始的时候要选择一个度数为 $4$ 的点为根。

```cpp
#include<bits/stdc++.h>
#define N 200005
#pragma GCC optimize("O3")
using namespace std;
int n,ans=-1,f[N];
vector<int>v[N];
void dfs(int k,int fa)
{
	vector<int>tmp;
	for(int now:v[k]) if(now!=fa) dfs(now,k),tmp.push_back(f[now]);
	sort(tmp.begin(),tmp.end(),greater<int>());
	if(tmp.size()>=3) f[k]=tmp[0]+tmp[1]+tmp[2]+1;
	else f[k]=1;
	if(tmp.size()>=4) ans=max(ans,tmp[0]+tmp[1]+tmp[2]+tmp[3]+1);
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i=1;i<=n;i++) if(v[i].size()>=4) {dfs(i,0);break;}
	cout<<ans;
	return 0;
}
```

---

## 作者：Zyj6 (赞：2)

裸的树形 dp，赛时切了

## 正文

设 $dp[x][0/1]$ 为以 $x$ 为根的子数下，不选或选 $x$ 的父亲就可以造成烷烃图的最大数。

$Q:$ 为什么与状态与 $x$ 的父亲有关？

$A:$ 我们要考虑将状态传回去，但如果 $x$ 已经选了 $4$ 或 $1$ 个儿子，即有了 $4$ 或 $1$ 个入度，再让父亲节点去连它，就变成了 $5$ 或 $2$ 个入度，肯定是不行的，所以分成不选或选 $x$ 的父亲，分别计算贡献。

在有 $3$ 个儿子及以上的节点中，选多个节点的贡献肯定比一个大。

## Code
```
#include<bits/stdc++.h>
using namespace std;
vector<int> v[200005];
int dp[200005][3];
void dfs(int x,int fa)
{
	dp[x][1]=-2e9,dp[x][2]=-2e9;
	priority_queue<int> q;
	for(int i=0;i<v[x].size();i++)
	{
		int u=v[x][i];
		if(u==fa) continue;
		dfs(u,x);
		if(v[x].size()<4)
		{
			if(dp[u][1]!=2e9) dp[x][2]=max(dp[x][2],dp[u][1]+1);
		}
		else
		{
			q.push(max(1,dp[u][1]));
		}
	}
	if(v[x].size()<4) return;
	int u=0;
	dp[x][1]=1;
	while(++u<=3)
	{
		dp[x][1]+=q.top();
		q.pop();
	}
	if(!q.empty())
	{
		dp[x][2]=dp[x][1]+q.top();
		q.pop();
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	int ans=-1;
	for(int i=1;i<=n;i++) ans=max(ans,dp[i][2]);
	printf("%d",ans);
}

```

---

## 作者：Inzaghi_Luo (赞：1)

这个题要最大化可以选择的节点数量，因此我们可以设 $f_u$ 代表点 $u$ 的子树内最多可以选择几个点。由于度数最多是四，因此我们只需要在子树内部记录前四大的值，如果它有足够多的儿子就可以选择四个，否则就只能选择一个。然后由于父亲方向也会占用度数，因此只需要在方程后面多记录一维代表选不选父亲方向即可。注意判断无解，因为至少存在一个度数为四的点，那么如果 $ans\le4$ 就无解。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int head[MAXN], CNT;
struct edge{
	int next, to;
}ed[MAXN << 1];
void add_edge(int u, int v){
	ed[++CNT] = (edge){head[u], v};
	head[u] = CNT;
}
int f[MAXN][2];
void dfs(int u, int fa){
	int deg = 0;
	int fir = 0, sec = 0, thi = 0, fou = 0;
	for(int i = head[u];i;i = ed[i].next){
		int v = ed[i].to;
		if(v == fa) continue;
		deg++;
		dfs(v, u);
		if(f[v][1] > fir){
			fou = thi;
			thi = sec;
			sec = fir;
			fir = f[v][1];
		}
		else if(f[v][1] > sec){
			fou = thi;
			thi = sec;
			sec = f[v][1];
		}
		else if(f[v][1] > thi){
			fou = thi;
			thi = f[v][1];
		}
		else fou = max(fou, f[v][1]);
	}
	if(deg >= 4) f[u][0] = fir + sec + thi + fou + 1;
	else f[u][0] = fir + 1;
	if(deg >= 3) f[u][1] = fir + sec + thi + 1;
	else f[u][1] = 1;
}
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1, u, v;i < n;i++){
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
	int ans = 0;
	for(int i = 1;i <= n;i++){
		ans = max(ans, f[i][0]);
	}
	if(ans < 5) printf("-1");
	else printf("%d", ans);
	return 0;
}
```

---

## 作者：__FL__ (赞：1)

## 题意
给定一棵无向树，询问是否存在它的一个子图，使其满足如下性质：

- 图是一棵无向树。
- 这棵树的每个顶点的度数都为 $1$ 或 $4$，且至少一个顶点的度数为 $4$。

如果有，输出可能的子图中顶点的最大数量；否则输出 $-1$。
## 思路
我们先枚举每一个点 $u$，如果它没有被访问过，就对其进行 DFS，每轮 DFS 求出它的所有子节点可以贡献的答案，取其中最大的 $3$ 或 $4$ 个值的和再加 $1$ （即自己本身）返回（如果当前节点是最开始的节点就需要 $4$ 个值，因为除它以外的节点都有一个父亲），细节可以参考代码。

于是我们求出了一些含有节点 $u$ 的组合的答案，但如果我们的正确答案不包含节点 $u$ 呢？

答案很简单，因为我们已经知道了每个节点的子节点最多能贡献的值，那么以它为根，取其子节点中 $4$ 个最多的值加 $1$（显然不会包含搜索时它的父亲），就得到了其他可能为答案的值。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u,v;
bool vis[200005];
vector<int>vec[200005],beg,p[200005];
int dfs(int u,int f,bool t)
{
	vis[u] = 1;
	if (vec[u].size() < 4) return 1;
	for (int v: vec[u])
	{
		if (v != f)
		{
			p[u].push_back(dfs(v,u,0));
		}
	}
	sort(p[u].begin(),p[u].end());
	reverse(p[u].begin(),p[u].end());
	return p[u][0]+p[u][1]+p[u][2]+1+(t? p[u][3]: 0);
}
int main()
{
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> n;
	if (n == 1)
	{
		cout << -1;
		return 0;
	}
	for (int i = 1; i < n; i++)
	{
		cin >> u >> v;
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (!vis[i]) ans = max(ans,dfs(i,i,1));
	for (int i = 1; i <= n; i++)
	{
		if (p[i].size() >= 4) ans = max(p[i][0]+p[i][1]+p[i][2]+p[i][3]+1,ans);
	}
	if (ans <= 4) cout << -1;
	else cout << ans;
	return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：1)

$\Large{\text{Solution}}$

树形 DP 妙妙题。

如果往树形 DP 的方面想，考虑如何从儿子转移给父亲。

第一维肯定是节点，除了节点我们还要考虑当前连了几个儿子，也就是度数。同时，我们需要知道当前有没有其他节点满足了度数为 $4$ 的要求，再开一维 $0/1$。

转移时，枚举父亲 $u$ 如果连了这个儿子 $j$ 度为 $i$，这个儿子连父亲前度为 $k$ 的情况。

第三维为 $0$ 时，只能是 $f_{u,i-1,0}+f_{j,0,0}$。
第三维为 $1$ 时，则有四种情况取 $\max$。

1. $f_{u,i-1,1}+f_{j,0,0}$；
2. $f_{u,i-1,1}+f_{j,3,1}$；
3. $f_{u,i-1,0}+f_{j,3,1}$；
4. $f_{u,i-1,0}+f_{j,3,0}$。

答案只要对于每一个节点看他度数为 $4$ 或他下面有满足条件的点时的答案最大值取 $\max$。

$\Large{\text{Code}}$

```cpp
#include <bits/stdc++.h>
//#define int long long
#define x first
#define y second
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef complex <double> cd;
const double PI = acos (-1);
const double eps = 1e-10;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
//const int mod = 998244353;

vector <int> v[N];
int f[N][5][2];
void dfs(int u, int fa)
{
    f[u][0][0] = 1;
    for (int j : v[u])
    {
        if (j == fa) continue;
        dfs (j, u);
        for (int i = 4; i >= 1; i--)
            for (int k = 0; k <= 3; k++)
            {
                if (k == 0) f[u][i][0] = max (f[u][i][0], f[u][i - 1][0] + f[j][k][0]);
                if (k == 0 || k == 3)
                    f[u][i][1] = max (f[u][i][1], max (f[u][i - 1][1] + max (f[j][k][1], f[j][k][0]), f[u][i - 1][0] + f[j][k][1]));
                if (k == 3) f[u][i][1] = max (f[u][i][1], f[u][i - 1][0] + f[j][k][0]);
            }
    }
}

signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].push_back (b);
        v[b].push_back (a);
    }
    memset (f, -0x3f, sizeof f);
    dfs (1, 0);
    int ans = -1;
    // for (int i = 1; i <= n; i++)
    //     for (int j = 0; j <= 4; j++)
    //         for (int k = 0; k <= 1; k++)
    //             printf ("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k]);
    for (int i = 1; i <= n; i++)
        ans = max (ans, max (f[i][1][1], max (f[i][4][0], f[i][4][1])));
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Conan15 (赞：1)

容易想到树形 DP。\
考虑设 $dp_{u,i,j}$ 表示 $u$ 子树内，$u$ 的度数（不包括它和它父亲那条边）为 $i$，目前是否出现过度数为 $4$ 的点，能构造出的最多节点数量。

显然这是一个类似于树形背包的东西，但由于每个节点的度数必须是 $1$ 或 $4$，所以儿子转移上来的度数必须是 $0$ 或 $3$（加上父亲这条边就满足条件了）。\
另外当 $i=3$ 的时候，只有它与父亲连上边才可以产生贡献，所以可以直接 $\max(dp_{u,3,1},dp_{u,3,0}) \to dp_{u,3,1}$，因为加上这条边它就是 $4$ 了。

最后 Corner Case 需要特判，$n=1$ 是无解。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 15, M = N << 1, INF = 0x3f3f3f3f;
int n, h[N], e[M], ne[M], idx = 0;
void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

int dp[N][5][2], g[5][2];
void dfs(int u, int father) {
    dp[u][0][0] = 1, dp[u][0][1] = 0;
    for (int p = h[u]; ~p; p = ne[p]) {
        int v = e[p];
        if (v == father) continue;
        dfs(v, u);
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 1; j++) g[i][j] = dp[u][i][j];
        for (int i = 0; i <= 3; i++) {  // u 的度数为 i
            //只能从 0 或 3 转移来
            //0->1   3->4
            g[i + 1][0] = max(g[i + 1][0], dp[u][i][0] + dp[v][0][0]);
            g[i + 1][1] = max({g[i + 1][1], dp[u][i][0] + dp[v][0][1], dp[u][i][1] + dp[v][0][0], dp[u][i][1] + dp[v][0][1]});

            g[i + 1][0] = max(g[i + 1][0], dp[u][i][0] + dp[v][3][0]);
            g[i + 1][1] = max({g[i + 1][1], dp[u][i][0] + dp[v][3][1], dp[u][i][1] + dp[v][3][0], dp[u][i][1] + dp[v][3][1]});
        }
        g[3][1] = max(g[3][1], g[3][0]);
        g[4][1] = max(g[4][1], g[4][0]);
        for (int i = 0; i <= 4; i++)
            for (int j = 0; j <= 1; j++) dp[u][i][j] = g[i][j];
    }
}

int main() {
    memset(dp, -INF, sizeof dp);
    scanf("%d", &n);
    if (n == 1) return puts("-1"), 0;
    for (int i = 1; i <= n; i++) h[i] = -1;
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = max({ans, dp[i][1][1], dp[i][4][1]});
    printf("%d\n", ans == 1 ? -1 : ans);
    return 0;
}
```

---

## 作者：Tairitempest (赞：1)

## [ABC394F] Alkane
这样的一颗子图，要么是叶子结点，要么是有 $4$ 个节点连着的节点。

对于一个节点，如果这个节点在子图当中，并且不是叶子结点，那么遍历到这个节点的时候，要么其连接了四个子节点的分支，要么其连接了三个子节点的分支和一个父节点的分支。对于连接了三个子节点的分支和一个父节点的分支的节点，如果父节点并非叶子结点，那么该子图会在父节点被统计。因此只需要统计图中的非叶子节点其连接了四个子节点的分支的情况，和其连接了三个子节点的分支和一个父节点的分支，且父节点是叶子结点的情况，就可以覆盖所有子图。

考虑通过树形 DP 来解决。如果子节点的数量小于 $4$，那么只能做叶子结点，其对上方节点的贡献是 $1$；否则其对上方节点的贡献是该节点贡献最大的三个子节点的贡献之和加一。如果子节点的数量大于等于 $4$，枚举这个节点所有子节点的贡献，统计以下两种情况：

- 图中的非叶子节点其连接了四个子节点的分支的情况——此时该子图的节点数为该节点贡献最大的四个子节点的贡献之和加一。

- 其连接了三个子节点的分支和一个父节点的分支，且父节点是叶子结点的情况——此时该子图的节点数为该节点贡献最大的三个子节点的贡献之和加二。
在 DP 过程中得到最大值输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,maxsum3[200010],ans=-1,u,v;
vector<ll> E[200010];
priority_queue<ll> maxnum[200010];
void dfs(int p,int fa){
	int sz=E[p].size();
	for(int i=0;i<sz;i++){
		int nxt=E[p][i];
		if(nxt==fa) continue;
		dfs(nxt,p);
		maxnum[p].push(maxsum3[nxt]);
	}
	maxsum3[p]=1;
	if(E[p].size()>=4){
		for(int i=1;i<=3;i++){
			maxsum3[p]+=maxnum[p].top();
			maxnum[p].pop();
		}
		if(maxnum[p].size()>0){
			ll tmp=maxsum3[p]+maxnum[p].top();
			ans=max(tmp,ans);
		}else if(p!=1) ans=max(maxsum3[p]+1,ans);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(1,0);
	cout<<ans<<endl;
}
```

---

## 作者：nr0728 (赞：1)

DP，设 $\texttt{dfs}(u,f)$ 表示根节点为 $u$，$u$ 父亲为 $f$，且 $u$ 度数为 $4$ 的 alkane 的最大边数。

如果 $u$ 有父亲，那么添加三条边就可以有度数为 $4$；否则要加四条边。设要加的边数为 $k$。

转移：枚举不是父亲的邻居节点，取 $\texttt{dfs}$ 值最大的 $k$ 个。如果不足 $k$ 个返回 $-\infty$。

记忆化，对于每个点跑 $\texttt{dfs}$ 即可。时间复杂度 $\mathcal O(n\log n)$，瓶颈在于排序 / map 记忆化，精细实现可以 $\mathcal O(n)$。

---

## 作者：Redshift_Shine (赞：1)

根据题面，一个 Alkane 由若干个核心和若干个叶子组成。考虑拓扑排序。

从叶子开始考虑。设 $f_i$ 为以 $i$ 作为核心的**非完整 Alkane** 的最大节点数量**减一**。此处，非完整指使得 $i$ 的度数为 $3$ 而不是 $4$。

按照拓扑序，走到一个节点 $i$ 时，若其邻接节点中有至少 $4$ 个已经被访问过，那么可以直接提取出其中最大的 $4$ 个尝试更新答案。接下来，去掉最小的一个，计算 $f_i$，对剩下的节点重复该过程。

时间复杂度 $O(n)$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, deg[N], idx, q[N], res = -1, va[N];
vector<int> road[N];
bool vis[N];
priority_queue<int, vector<int>, greater<int>> qr;
void run()
{
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++)
	{
		scanf("%d%d", &x, &y);
		road[x].emplace_back(y);
		road[y].emplace_back(x);
		deg[x]++, deg[y]++;
	}
	for (int i = 1; i <= n; i++)
	{
		if (deg[i] > 1)
			continue;
		q[++idx] = i;
	}
	for (int j = 1, i, tmp, flg; j <= n; j++)
	{
		i = q[j];
		vis[i] = true;
		while (qr.size())
			qr.pop();
		tmp = flg = 0;
		for (auto &k : road[i])
		{
			if (!vis[k])
			{
				flg = 1;
				deg[k]--;
				if (deg[k] == 1)
					q[++idx] = k;
				continue;
			}
			qr.emplace(va[k] + 1);
			tmp += va[k] + 1;
			if (qr.size() > 4)
				tmp -= qr.top(), qr.pop();
		}
		if (qr.size() == 4)
			res = max(res, tmp + 1), tmp -= qr.top(), qr.pop();
		if (qr.size() == 3)
			va[i] = tmp;
		if (qr.size() == 3 and flg)
			res = max(res, tmp + 2);
	}
	printf("%d\n", res);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
[不爱看题的赶紧给我去看！！](https://www.luogu.com.cn/problem/AT_abc394_f)

定义简单，这里不再赘述。

# 思路
通过题目我们可以发现如下规律。

- 只有根结点的度数为 $4$。
- 其余结点要不儿子数量为 $0$，要不儿子数量为 $3$。
- 要求最多有多少个结点，所以对于每个结点我们尽量保留结点多的儿子结点。

这样，我们就可以用`dfs`遍历每个结点的儿子，考虑是否要保留这个儿子。

最后再判断是否能成为它儿子节点的儿子，也就是儿子为根，或自己成为根节点。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,u,v,dp[1000005][5];
vector<int> vec[1000005]; 
int ans=-1;
void dfs(int u,int father){
	dp[u][1]=dp[u][2]=dp[u][3]=dp[u][4]=-1e9;
	dp[u][0]=1;
	for(int i=0;i<vec[u].size();i++){
		int v=vec[u][i];
		if(v==father)continue;
		dfs(v,u);
		for(int j=4;j>=1;j--){
			dp[u][j]=max(dp[u][j],dp[u][j-1]+max(dp[v][0],dp[v][3]));
		}
	}
	if(dp[u][1]>=3)ans=max(ans,dp[u][1]);
	ans=max(ans,dp[u][4]);
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs(1,0);
	cout<<ans;
 	return 0;
}

```
### 谢谢！

---

## 作者：lw393 (赞：0)

题意：求树的一个最大节点数子图，满足任意节点度数均为 $1$ 或者 $4$。

考虑 dp。我们很容易想到树上背包的套路。我们令 $dp_{i,j}$ 表示节点 $i$ 度数为 $j$ 时的答案。

根据题意写出转移方程：（有点难用markdown表示，用代码代替一下）

```cpp
//v is the son of the vertex u
//Suppose we hav gotten the answer of v
for(int j = 4; j >= 1; j--){
    int k = max(dp[v][0], dp[v][3]);
    if(dp[u][j - 1]) dp[u][j] = max(dp[u][j - 1] + k, dp[u][j]);
}
```

其实上面就是核心代码了。答案就是 $\max_{i=1}^n(dp_{i,1}, dp_{i,4})$ 注意判断答案是否大于等于 $5$，若小于则没有度数为 $4$ 的节点了，不满足题意。

---

## 作者：chenzhiyou12 (赞：0)

挺板子的，考虑到所有情况就行。

按照树形 DP 的套路，我们设 $dp_{u}$ 表示 $u$ 下面接 $3$ 个子树时它包含的节点节点数最大值。之所以这样定义是因为对于 $u$ 来说，如果它要给他的祖先贡献，它必须只有三颗子树（它除了向子树连接的三条边还要向父节点连一条，一共四条边）。

对于一个节点来说，除了考虑它向父节点贡献的情况，我们还要考虑它作为那个有四个子树的根节点的情况。无非就是两种情况：

- 它自己最大的四颗子树
- 它自己最大的三颗子树加上父节点

之所以要考虑第二种情况，是为了防止我们在遇到一个四度节点的其中一个节点是它的父亲的时候，它不贡献。比如下图钦定 $1$ 为根节点的时候：

![插图](https://cdn.luogu.com.cn/upload/image_hosting/9zph5mds.png)

[AC 记录，代码](https://atcoder.jp/contests/abc394/submissions/63172349)

评级的话，个人感觉是中下位绿。

---

## 作者：WuMin4 (赞：0)

## [[ABC394F] Alkane](https://atcoder.jp/contests/abc394/tasks/abc394_f)

## 思路

先忽略至少存在一个度数为 $4$ 的顶点的限制，当忽略限制后得到的最大答案为 $1$ 时，该树无解。

从任意一个未被访问过的点开始 dfs，对每个点统计该点的子树能贡献的最大值以及能对父亲节点贡献的最大值，设点 $i$ 对父亲贡献的值为 $w_i$。对于每个点 $i$ 进行如下考虑：

1. 点 $i$ 的儿子数量 $<3$。

不能从该点继续往下扩展，此时该点答案为 $1$，$w_i=1$。

2. 该点的儿子数量 $=3$。

此时该点答案为 $1$（因为这棵子树内该点度数小于 $4$），但是能对父亲节点产生贡献（因为包含父亲节点后度数等于 $4$），设该点的儿子分别为 $v_1,v_2,v_3$，则 $w_i=w_{v_1}+w_{v_2}+w_{v_3}+1$。

3. 该点的儿子数量 $\ge 4$。

设 $w$ 中前 $4$ 大的点分别为 $v_1,v_2,v_3,v_4$，则该点答案为 $w_{v_1}+w_{v_2}+w_{v_3}+w_{v_4}+1$，对父亲的贡献 $w_i=w_{v_1}+w_{v_2}+w_{v_3}+1$。

最终答案即为每个点对答案贡献的最大值。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,ans;
vector<int> t[200005];
bool vis[200005];
int dfs(int x,int fa){
	vis[x]=true;
	if(t[x].size()<4) return 1;
	multiset<int> mx;
	for(int v:t[x]){
		if(v!=fa){
			mx.insert(dfs(v,x));
			if(mx.size()>=5) mx.erase(mx.begin());
		}
	}
	int tot=0;
	for(int v:mx)
		tot+=v;
	if(mx.size()==4){
		ans=max(ans,tot);
		return tot+1-*mx.begin();
	}
	else return tot+1;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int x,y,i=1;i<n;i++){
		cin>>x>>y;
		t[x].push_back(y);
		t[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
			dfs(i,0);
	cout<<(ans==0?-1:ans+1);
	return 0;
}
```

---

## 作者：Inv_day_in_R (赞：0)

首先不难看出题目要求的每个烷烃是一颗树，那么这种求子树最值的问题很容易想到树上 DP。但是有氢原子的存在非常难受，不妨把度数小于 $4$ 的点全都删掉，只算碳原子数量最大值。用 $\text{dp}_{i,0}$ 表示选 $i$ 且不为根的子树答案最大值，而 $\text{dp}_{i,1}$ 表示以 $i$ 为根的子树答案最大值。不难想到，假如 $i$ 不为子树根节点，那么 $i$ 的子节点最多选三个，如果为子树根节点，那么可以选四个子节点，很显然选最大的几个即可。最终枚举每一个点作为根节点，求最大值。但这样求出的只是碳原子的最大个数，需要再乘三加二。

而我在考场上则是用了一种更巧妙的写法，思路是一样的，只是令所有满足 $i$ 的度数小于 $4$ 的 $\text{dp}_{i,0}=1$ 且 $\text{dp}_{i,1}=0$，每次 DFS 到这样的 $i$ 时直接返回。

代码：
```cpp
namespace AC{
vector<int>gra[200010];
int cnt,vis[200010],dp[200010][2];
void dfs(int u){
	if(gra[u].size()<4){dp[u][0]=1;return;}
	if(vis[u])return;
	vis[u]=1;
	cnt++;
	priority_queue<int>st;
	for(auto v:gra[u]){
		dfs(v);
		st.push(dp[v][0]);
	}
	dp[u][0]=1;
	for(int i=0;i<3;i++)dp[u][0]+=st.top(),st.pop();
	dp[u][1]=dp[u][0]+st.top();
	st.pop();
}
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		gra[u].push_back(v);
		gra[v].push_back(u);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(gra[i].size()<4||vis[i])continue;
		cnt=0;
		dfs(i);
	}
	for(int i=1;i<=n;i++)ans=max(ans,dp[i][1]);
	if(ans<5)cout<<-1;
	else cout<<ans<<endl;
}
}
```

---

## 作者：xiaofu15191 (赞：0)

在一棵树上寻找满足条件的子图，并且限制条件只有顶点度数，我们想到树形 DP。

设 $f_{i,j}$ 表示当前在节点 $i$，当前点的种类为 $j \in {0,1,2}$ 的最大答案。其中，$j=0$ 表示当前节点 $i$ 为叶子节点，$j=1$ 表示当前为非根非叶子节点，$j=2$ 表示当前为根节点。

显然当 $j>0$ 时可以从深度更深的 $f_{son,0/1}$ 转移而来。当 $j=1$ 时取最大的 $3$ 个 $f_{son,0/1}$ 转移，当 $j=2$ 时取最大的 $4$ 个。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
long long n,f[200010][3],ans=-1;
vector<long long>graph[200010];
void DP(long long now,long long fa)
{
	f[now][0]=f[now][1]=1;
	vector<long long>tmp;
	for(auto to:graph[now])
	{
		if(to==fa) continue;
		DP(to,now);
		tmp.push_back(f[to][0]);
		tmp.push_back(f[to][1]);
	}
	if(graph[now].size()<4) return;
	sort(tmp.begin(),tmp.end(),greater<long long>());
	for(long long i=0;i<3;i++) f[now][1]+=tmp[i];
	for(long long i=0;i<4;i++) f[now][2]+=tmp[i];
	ans=max(ans,f[now][2]+1);
}
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<n;i++)
	{
		long long u,v;
		scanf("%lld%lld",&u,&v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	DP(1,0);
	printf("%lld\n",ans);
}
```

---

## 作者：Ivan422 (赞：0)

注意到这是一道化学题。

~~但是初一不学化学，所以不做。~~

考虑开局记录一下每个点的度数。

设 $f_p$ 为以一个点为起点而扩展出的最大点数。

直接深搜。

当 $p$ 的儿子 $v$ 的度数超过 $4$，就有可能成为一个新的 Alkane 子树，我们把 $f_v$ 加入一个 vector 里面。

接着我们考虑枚举。

先统计 $f_p$，初始自己为 $f_p=1$，即这个点本事。

在子树内选择 $3$ 个作为 Alkane 子树。

> 为什么不是 $4$ 个呢？因为有父节点。

我们就可以简单的把 $f_v$ 中前 $3$ 大的加入 $f_p$。

再统计答案。

注意这次是选择 $4$ 个，因为答案 $ans$ 是把四个子树的答案加起来，并非转移到 $p$。

所以我们的 $ans$ 就是把 $f_v$ 中前 $4$ 大的加和加上 $1$（节点本身） 求出 $ans$，取最大值即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ivan422{
	#define ll long long
	#define ld long double 
	#define il __int128
	#define fl __float128
	#define x0 x_0
	#define x1 x_1
	#define y0 y_0
	#define y1 y_1
	#define yn y_n
	#define j0 j_0
	#define j1 j_1
	#define k0 k_0
	#define k1 k_1
	#define d0 d_0
	#define d1 d_1
	#define pb push_back
	#define pf push_front
	#define mp make_pair
	#define ar array<int,3>
	#define us unsigned
	#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
};
using namespace ivan422;
const int N=2e5+10,M=1e3+10;
const int P1=1e9+7,P9=998244353;
const double pi=3.1415926535,eps=1e-7;
int n,U,V,f[N],deg[N],res,ans,cnt,su;
vector<int>e[N],g[N];
bool vis[N];
void dfs(int p,int fa){
	for(auto v:e[p]){
		if(v!=fa){
			dfs(v,p);
			if(deg[p]>=4)g[p].push_back(f[v]);
		}
	}
	sort(g[p].begin(),g[p].end(),greater<int>());
	cnt=0,su=0;
	f[p]=1;	
	for(auto v:g[p])if((++cnt)<=3)f[p]+=v;
	ans=max(ans,f[p]+1);
	cnt=0;
	for(auto v:g[p])if((++cnt)<=4)su+=v;
	ans=max(ans,su+1);
}
signed main(){
	io;
	cin>>n;
	for(int i=1;i<n;i++){
		cin>>U>>V;
		deg[U]++,deg[V]++;
		e[U].push_back(V);
		e[V].push_back(U);
	}
	ans=-1;
	dfs(1,0);
	cout<<(ans<5?-1:ans);
	return 0;
}
```

---

## 作者：lilong (赞：0)

在同一棵树中，选择任意一个点作为根，效果都是相同的。不妨以 $1$ 为树根，考虑树上 dp，记 $f_u$ 为以 $u$ 为根的子树的点数最大值。注意到**根节点度数可为 $1$ 可为 $4$，而非根非叶子节点度数必须为 $4$**。由此可以分两类转移。

- 假设子树中 $u$ 度数为 $1$，则这条边连接的是 $u$ 与其父节点，故 $f_u=1$。

- 假设子树中 $u$ 度数为 $4$，则从 $u$ 的子节点中 $v$ 寻找三个最大的 $f_v$，即 $g_1,g_2,g_3$，故 $f_u=g_1+g_2+g_3+1$。**需要注意这种情况只在有不少于三个子节点时才能转移**。

在每个点处求答案，大体相近，强制取 $u$ 为选定子树的根节点。

- 假设 $u$ 的度数为 $1$，那么从 $u$ 的子节点 $v$ 中找到最大的 $f_v$ 即可，故 $ans=f_v+1$。

- 假设 $u$ 的度数为 $4$，则从 $u$ 的子节点中 $v$ 寻找四个最大的 $f_v$，即 $g_1,g_2,g_3,g_4$，故 $ans=g_1+g_2+g_3+g_4+1$。

总时间复杂度 $O(n)$。


```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define N 1000001

using namespace std;

vector<int> G[N];
int n,f[N],ans = -1;

void dfs( int u , int fa )
{
    int g[5] = { -1 , -1 , -1 , -1 , -1 };
    for( auto v : G[u] )
    {
        if( v == fa ) continue;
        dfs( v , u );
        if( f[v] >= g[1] )
            g[4] = g[3],g[3] = g[2],g[2] = g[1],g[1] = f[v];
        else if( f[v] >= g[2] )
            g[4] = g[3],g[3] = g[2],g[2] = f[v];
        else if( f[v] >= g[3] )
            g[4] = g[3],g[3] = f[v];
        else if( f[v] >= g[4] )
            g[4] = f[v];
    }
    f[u] = 1;
    if( g[3] >= 0 )
    {
        f[u] += g[1] + g[2] + g[3];
        if( g[4] >= 0 )
            ans = max( ans , f[u] + g[4] );
    }
    if( g[1] > 1 )
        ans = max( ans , g[1] + 1 );
    return;
}

int main()
{
    int u,v;
    cin >> n;
    for( int i = 1 ; i < n ; i ++ )
    {
        cin >> u >> v;
        G[u].push_back( v );
        G[v].push_back( u );
    }
    dfs( 1 , 0 );
    cout << ans;
    return 0;
}
```

---

## 作者：Union_Find (赞：0)

注意到最终子图的点度数只能是 $1$ **或** $4$（加粗**或**是因为我赛时看成**到**了），所以考虑图的结构是什么。很明显，度数为 $1$ 的点只能是叶子节点（默认度数为 $4$ 的是根），而剩下的点就是度数为 $4$ 的，在子图的中间，所以我们只要考虑度数为 $4$ 的连通块大小的最大值，即可求出子图的大小。

----

> 在确定度数为 $4$ 的点的数量时，如何求出总点数？

这个问题要从边数入手。设有 $n$ 个度数为 $4$ 的点，那么每个点出去 $4$ 条边，就会有 $4n$ 条边。但是度数为 $4$ 的点之间要连通，就会有 $n-1$ 条边重复计算，所以边数就是 $4n - (n-1) = 3n + 1$。所以总共有 $3n + 2$ 个点。

----

综上所述，我们只要知道度数为 $4$ 的点组成的最大连通块大小即可。

注意到这个问题有一个隐含条件，就是选出来的点在原图上一定是度数大于等于 $4$ 的。所以我们可以先在原图中选出来这些点存好，在新的森林（因为这些点不一定连通）上求解。这问题就很好 dp 了。

设 $f_{i,j}$ 表示在以 $i$ 为根的子树内，$i$ 这个点选了 $j$ 个儿子的最大点数。转移就很简单了，如下。

$$f_{i,j} = \max (f_{i,j},f_{i,j-1}+\max_{k=0}^3\{f_{v,k}\})$$

为了方便转移，我们设 $h_i = \max_{j=0}^3 f_{i,j}$。最后的答案就是 $3 \times \max_{i \in [1,n],j\in[0,4]}f_{i,j} + 2$。代码中的 $ans$ 就是指 $\max_{i \in [1,n],j\in[0,4]}f_{i,j}$。

----
> 为什么转移和取答案时不直接用 $f_{i,3},f_{i,4}$，而是用所有的呢？

这个问题可以在样例 $3$ 中体现，如下图，红色点表示选择的度数为 $4$ 的点，蓝色点表示选择的度数为 $1$ 的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/i2891ba8.png)

我们发现，在 $1$ 号点，虽然度数为 $4$，但是与他相邻的度数为 $4$ 的点只有两个，如果取答案时只取 $f_{i,3}$ 或 $f_{i,4}$ 会导致错误。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), u, v, du[N], vis[N], f[N][5], h[N], ans = -1;
vector <ll> e[N], g[N];
void dfs(ll u, ll fa){
	f[u][0] = 1, vis[u] = 1;
	for (int v : g[u]){
		if (v == fa) continue;
		dfs(v, u);
		for (int j = 4; j >= 1; j--) f[u][j] = max(f[u][j], f[u][j - 1] + h[v]);
	}for (int j = 0; j <= 3; j++) h[u] = max(h[u], f[u][j]);
	ans = max(ans, max(h[u], f[u][4]));
}
int main(){
	for (int i = 1; i < n; i++) u = rd(), v = rd(), e[u].push_back(v), e[v].push_back(u), du[u]++, du[v]++; 
	for (int i = 1; i <= n; i++) if (du[i] >= 4) for (int j : e[i]) if (du[j] >= 4) g[i].push_back(j);
	for (int i = 1; i <= n; i++) if (!vis[i] && du[i] >= 4) dfs(i, 0);
	printf ("%lld\n", 3 * ans + 2);
	return 0;
}

```

---

## 作者：zhangzheng2026 (赞：0)

树形 DP。  
设 $dp_i$ 表示以 $i$ 为根的子树中，点数最多的烷烃子图中度数为四的节点个数且必须选择 $i$。  
那么有：  
$$dp_i=mx_1+mx_2+mx_3+mx_4+1$$  
其中 $mx_j$ 表示 $i$ 的子节点 $dp_{son_i}$ 第 $j$ 大的 $dp_{son_i}$ 的值，如果该节点度数小于四则为零。注意，不是子节点个数小于四。  
如果答案要贡献到父亲节点，$dp_i$ 需要减去 $mx_4$。因为 $i$ 到父亲节点的边也算一度。  
设 $dp_i$ 的最大值为 $x$，答案即为 $x\times3+2$，$x=0$ 时答案也为 $0$。   
代码：  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,h[N],cnt,mx[N],ans=-1,rd[N];
struct node{int next,to;}a[N<<1];
void add(int x,int y){a[++cnt].to=y,a[cnt].next=h[x],rd[x]++,h[x]=cnt;}
void dfs(int x,int y)
{
	int mxx=0,mx2=0,mx3=0,mx4=0;
	for(int i=h[x];i;i=a[i].next)
	{
		int k=a[i].to;
		if(k==y) continue;
		dfs(k,x);
		if(mx[k]>mx4)
		{
			mx4=mx[k];
			if(mx3<mx4)
			{
				swap(mx3,mx4);
				if(mx2<mx3)
				{
					swap(mx2,mx3);
					if(mxx<mx2) swap(mxx,mx2);
				}
			}
		}
	}
	if(rd[x]>3) mx[x]=mxx+mx2+mx3+1,ans=max(ans,(mx[x]+mx4)*3+2);
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int x,y,i=1;i<n;i++) cin>>x>>y,add(x,y),add(y,x);
	dfs(1,0),cout<<ans;
	return 0;
}
```

---

## 作者：_Linver_ (赞：0)

### 定义

对每个非根节点 $v$，$dp_v$ 表示以 $v$ 为根的子树中，添加 $v$ 后形成烷的最大顶点数。

### 转移

若 $v$ 度数大于等于 $1$，则 $dp_v = 1$（仅包含 $v$ 和其父节点）。

若 $v$ 度数大于等于 $4$，需要 $3$ 个子节点：选 $3$ 个 $dp_u$ 最大的子节点 $u_1, u_2, u_3$，用 $dp_{u_1} + dp_{u_2} + dp_{u_3} + 1$ 更新。

枚举每个顶点 $v$ 作为最深顶点：若 $v$ 度数为 $1$，用 $dp_u + 1$（$u$ 是 $v$ 的父节点）更新。

若 $v$ 度数大于等于 $4$，用 $dp_{u_1} + dp_{u_2} + dp_{u_3} + dp_{u_4} + 1$（$u_1, u_2, u_3, u_4$ 是 $v$ 的子节点）更新。

取所有情况的最大值。

```cpp
#include <bits/stdc++.h>
// #include <atcoder/all>
// #define int long long
using namespace std;
inline int read()
{
    int f = 0, ans = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return f ? -ans : ans;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
constexpr int N = 2e5 + 5;
int n, ans, f[N];
vector<int> g[N];
vector<pair<int, int>> sub_f[N];
void dfs(int u, int fa)
{
    f[u] = 1;
    for (int &v : g[u])
        if (v != fa)
        {
            dfs(v, u);
            sub_f[u].emplace_back(v, f[v]);
        }
    sort(begin(sub_f[u]), end(sub_f[u]), [](auto &x, auto &y)
         { return x.second > y.second; });
    if (size(sub_f[u]) >= 3)
    {
        f[u] += f[sub_f[u][0].first] + f[sub_f[u][1].first] + f[sub_f[u][2].first];
        if (fa)
            ans = max(ans, f[u] + 1);
    }
    if (size(sub_f[u]) >= 4)
    {
        ans = max(ans, 1 + f[sub_f[u][0].first] + f[sub_f[u][1].first] + f[sub_f[u][2].first] + f[sub_f[u][3].first]);
    }
}
void resolve(int u, int fa, int from_fa)
{
    if (fa && f[u] != 1)
        ans = max(ans, f[u] + from_fa);
    if (fa)
        sub_f[u].emplace_back(0, from_fa);
    sort(begin(sub_f[u]), end(sub_f[u]), [](auto &x, auto &y)
         { return x.second > y.second; });
    for (int &v : g[u])
        if (v != fa)
        {
            int sum = 0, cnt = 0;
            for (auto &[i, w] : sub_f[u])
                if (i != v)
                {
                    sum += max(f[i], w);
                    if (++cnt == 3)
                        break;
                }
            if (cnt == 3)
                resolve(v, u, sum + 1);
        }
}
signed main()
{
    // freopen("in.in", "r", stdin);
    // freopen(".out", "w", stdout);
    cin >> n;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    ans = -1;
    dfs(1, 0);
    resolve(1, 0, 0);
    write(ans);
    return 0;
}
```

---

## 作者：zengziqvan (赞：0)

一个很麻烦的树形 $\operatorname{dp}$。

设 $f_{i,0/1,j}$ 表示以 $i$ 为根的子树，钦定选择 $i$ ，是否出现过度为 $4$ 的点，且 $i$ **不考虑** 父亲的度数为 $j$ 的最大点数。

转移类似树形背包，具体代码里说（转移可能有点乱）。

$O(n)$．

```c++
const int N=2e5+10;
vector<int>e[N];
int n,f[N][2][5];
void dfs(int x,int fa) {
	f[x][0][0]=1;//一个没选，只选他自己，大小为1。
	for(int y:e[x]) {
		if(y==fa) continue;
		dfs(y,x);
	}
	for(int y:e[x]) {
		if(y==fa) continue;
		ROF(i,4,1) {//01背包倒序枚举
			f[x][0][i]=max(f[x][0][i]/*自身*/,f[x][0][i-1]+max(f[y][0][0]/*只选y一个*/,f[y][0][3]/*y选3个儿子后加上父亲正好度数为4*/));
			f[x][1][i]=max({f[x][1][i],f[x][1][i-1]+max({f[y][0][3],f[y][0][0],f[y][1][3],f[y][1][0]}),f[x][0][i-1]+max({f[y][0][3],f[y][1][0],f[y][1][3]})});
            //第一项：自身 
			//第二项：已经有一个度数为4的点了，只要是度数为1或4怎么选都行
			//第三项：没有度数为4的点，需要选一个 
			if(i==4) cmax(f[x][1][i],f[x][0][i]);//已经有了。 
		}
	}
}
bool __ed;
main() { cerr<<"used:"<<((&__st-&__ed)/1024.0/1024)<<"MB \n";
	cin>>n;
	FOR(i,1,n-1) {
		int u=read(),v=read();
		e[u].eb(v),e[v].eb(u);
	}
	int flg=0;
	FOR(i,1,n) if(e[i].size()>=4) flg=1;
	if(!flg) {
		puts("-1");
		return 0;
	}
	memset(f,-0x3f3f3f3f,sizeof f);
	dfs(1,0);
	int ans=0;
	FOR(i,1,n) cmax(ans,max({f[i][1][4],f[i][0][4],f[i][1][1]}));
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

虽然有烷，但是这题是树形 dp 不是化学啊喂。

## Solution AT_abc394_f

### Problem

给你一个树，定义一个烷指一个连通块，当且仅当这个连通块中只含有度数为 $1$ 或 $4$ 的点。问树中最大的烷有多大。

### Idea

一眼就是树形 dp，但是这里状态设计与众不同。

我们设 $dp_i$ 表示以 $i$ 为根的子树中，形如以下连通块的最大点数：

![](https://cdn.luogu.com.cn/upload/image_hosting/8wtrwxti.png)

或

![](https://cdn.luogu.com.cn/upload/image_hosting/htrvy14b.png)

原因是什么？我们发现 $dp_v$ 需要向 $dp_{fa}$ 传递信息，这是 $dp$ 最核心的一点。为了保证子节点的状态可以转移到父节点上，我们对每一个子节点，都保留一个接往父节点的接口，保证可持续转移。

但是这时有人就会问了：如何转移？

我们把转移和统计答案放在一起。

我们设 $maxx1$ 为 $u$ 的所有儿子节点 $v$ 的 $dp_v$ 的最大值，$maxx2$ 为次大值，以此类推。

首先对于转移来说，如果这个点 $u$ 有大于等于 $3$ 个儿子节点，那么肯定让这个点度数为 $4$ 最优。所以此时，$dp_u=maxx1+maxx2+maxx3+1$，注意加 $1$ 算上自身。

如果这个点 $u$ 连 $3$ 个儿子都没有，那它只能孤零零一个点了，$dp_u=1$。

那么统计答案呢？我们如果把这个点当做顶点（不再往父亲连边），当它至少有 $4$ 个儿子时，这个点是顶点的最大答案就是 $maxx1+maxx2+maxx3+maxx4+1$。反之，它最多连 $1$ 个儿子，答案是 $maxx1$。

然后你就做完了。不过判断无解时要注意：一个烷最小都得有 $5$ 个点，所以你算出来答案小于 $5$ 的，直接否掉。

### Code

```
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
struct node
{
    int u, v, nxt;
} e[N << 1];
int head[N], cnt;
void add(int u, int v)
{
    e[++cnt].u = u;
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int dp[N], ans, n;
void dfs(int now, int fa)
{
    dp[now] = 1;
    int u=now,son=0;
    int maxx1 = 0, maxx2 = 0, maxx3 = 0, maxx4 = 0;
    for (int i = head[now], v; i; i = e[i].nxt)
    {
        v = e[i].v;
        if (v == fa)
            continue;
        dfs(v, now);
        son++;
        if (dp[v] > maxx1)
        {
            maxx4 = maxx3;
            maxx3 = maxx2;
            maxx2 = maxx1;
            maxx1 = dp[v];
        }
        else if (dp[v] > maxx2)
        {
            maxx4 = maxx3;
            maxx3 = maxx2;
            maxx2 = dp[v];
        }
        else if (dp[v] > maxx3)
        {
            maxx4 = maxx3;
            maxx3 = dp[v];
        }
        else if (dp[v] > maxx4)
        {
            maxx4 = dp[v];
        }
    }
    if(son>=3)dp[u]=dp[u]+maxx1+maxx2+maxx3;
    if(son>=4)ans=max(ans,maxx1+maxx2+maxx3+maxx4+1);
    else if(son>=1)ans=max(ans,maxx1+1);
}
int main(){
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);
    if(ans>=5)printf("%d",ans);
    else printf("-1");
}
```

---

