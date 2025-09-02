# Maximum Weight Subset

## 题目描述

You are given a tree, which consists of $ n $ vertices. Recall that a tree is a connected undirected graph without cycles.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1249F/0b019d9da08990633b2a6779b2699db8afb883d7.png)Example of a tree.Vertices are numbered from $ 1 $ to $ n $ . All vertices have weights, the weight of the vertex $ v $ is $ a_v $ .

Recall that the distance between two vertices in the tree is the number of edges on a simple path between them.

Your task is to find the subset of vertices with the maximum total weight (the weight of the subset is the sum of weights of all vertices in it) such that there is no pair of vertices with the distance $ k $ or less between them in this subset.

## 样例 #1

### 输入

```
5 1
1 2 3 4 5
1 2
2 3
3 4
3 5
```

### 输出

```
11
```

## 样例 #2

### 输入

```
7 2
2 1 2 1 2 1 1
6 4
1 5
3 1
2 3
7 5
7 4
```

### 输出

```
4
```

# 题解

## 作者：Kelin (赞：45)

## **[题意](https://blog.csdn.net/BeNoble_/article/details/102722530)**

求一棵树的最大点权和子树，且子树里任意两点的距离大于$K$

---

## 题解
树上$DP$（默认$1$为树根）

为了方便把将题目要求的大于$K$改成大于等于$K+1$，即一开始$K=K+1$

### 算法一

设$f[u][k]$表示以$u$为根的子树里离$u$最近的点距离$u$为$k$的答案

那么对于$u$的子节点$v$

$$
f[u][k]=
\begin{cases}
\max\{f[v_0][k-1]+\sum_{v\neq v_0}\max_{j\ge k-1}f[v][j]\}&k\ge1\\
a[u]&k=0
\end{cases}
$$

可以发现这个算法复杂度是$O(n^4)$，而且答案也不好统计

### 算法二
设$f[u][k]$表示以$u$为根的子树里离$u$最近的点与$u$的距离大于等于$k$的答案

显然$f[u][k]=\max_{j\ge k} f[u][j];f[u][0]$初值为$a[u]$

考虑将$u$的子节点$v$的答案合并到$u$的答案上去

$$
f[u][k]=\max_{0\le k\le n}\begin{cases}
f[u][k]+f[v][\max(k,K-k)-1]\\
f[u][\max(k,K-k)]+f[v][k-1]
\end{cases}
$$

实现时用一个临时数组将答案存下，枚举完后再更新$f[u][k]$，最后再求一遍后缀最大值

最后答案即为$f[1][0]$

时间复杂度为$O(n^3)$

### 算法三

考虑对算法二进行优化，设$Len_u$表示$u$子树里的点离$u$最远的距离

那么上面$k$的枚举范围就可以缩小到$0\le k\le Len_v$，因为$k$大了之后$f[v]$的值就不存在了

时间复杂度$O(\sum$长链长$)=O(n^2)$

### 算法四
为了方便将$f[v]$往后整体挪一位，根据定义新的$f[v][0]=f[v][1]$，那么

$$
f[u][k]=\max\begin{cases}
f[u][k]+f[v][\max(k,K-k)]\\
f[u][\max(k,K-k)]+f[v][k]
\end{cases}
$$

可以发现这样$f[u]$与$f[v]$就是对偶的了

然后可以注意到，$DP$只会影响到$0\le k\le \min(Len_u,Len_v)$（因为长了就一定会有一个没有值了）

于是就可以考虑长链剖分，每次将短链合并到长链上

时间复杂度$O(n)$

```cpp
void Merge(deque<int>&f,deque<int>&g){//启发式合并
	if(f.size()<g.size())
		swap(f,g);
	vector<int>Tmp=vector<int>(g.begin(),g.end());//复制短链
	for(int k=0;k<(int)g.size();++k){
		int Res=max(k,K-k);
		if(Res<(int)f.size())
			Tmp[k]=max(Tmp[k],f[Res]+g[k]);
		if(Res<(int)g.size())
			Tmp[k]=max(Tmp[k],f[k]+g[Res]);
	}
	int Max=0;
	for(int k=g.size()-1;k>=0;--k){
		Max=max(Max,Tmp[k]);
		f[k]=max(f[k],Max);
	}//更新后缀最大值
}
deque<int> dsu(int u,int p){
	deque<int>Now={a[u]};
	for(auto v:G[u])if(v!=p){
		deque<int>Son=dfs(v,u);
		Son.push_front(Son.front());//整体向后移一位
		Merge(Now,Son);
	}
	return Now;
}
```

### 算法五
考虑选了一个点$u$就加上他的权值$a_u$，那么他周围与之距离小于$K$的点都不能选

考虑把这些点的权值都减去$a_u$，相当于造成不选的影响

如果有的点点权变成了负数，那么这个点一定不会选

如果有的点点权还是正数，那就再加上这个点的权值进行“补差”，就相当于选了这个点而没有选$u$

然后就是选点顺序的问题，一种可行的方案就是从叶子节点开始，因为叶子节点没有儿子了，不会有后效性

时间复杂度$O(n^2)$

```cpp
void dfs(int u,int p,int dis){
    if(dis>=K)return;
    a[u]-=Val;
    for(auto v:G[u])if(v!=p)
    	dfs(v,u,dis+1);
}
inline void Bfs(){
	int h=1,t=1;
    q[1]=vis[1]=1;
    while(h<=t){
        int u=q[h++];
        for(auto v:G[u])
        	if(!vis[v]){
        		vis[v]=1;
        		q[++t]=v;
        	}
    }
}
inline int sol(){
	int Ans=0;
	Bfs();
    for(int i=n;i>=1;--i){
        int u=q[i];Val=a[u];
        if(Val<=0)continue;
        Ans+=Val;
        dfs(u,0,0);
    }
    return Ans;
}
```

---

## 作者：Otomachi_Una_ (赞：10)

树形 dp 好喵题。

## 题目简述

- 给定树，子点集满足任意两点距离 $\geq k+1$。
- 求点集权值最大值。
- $n,k\leq200$。

## 解题思路

一眼可以看出来是树形 $\text{dp}$。

假设 $f_{i,j}$ 是 $i$ 子树中满足选中点集到 $i$ 距离最小值**恰**为 $j$ 的最大点权和。那么，可以得到转移方程：

$$f_{u,\min(i,j+1)}=\max( f_{u,\min(i,j+1)},f_{u,i}+f_{v,j})$$

这里：

- $i+j\leq k$。
- $v$ 为 $u$ 的儿子。

但是这里 $\min(i,j+1)$ 的变化比较玄乎，不能直接在原式上面搞，所以我们对于每轮转移要搞另外一个数组（这里是 $\text{tmp}$）来记录转移结果。

```cpp
#include<iostream>
#include<vector>
using namespace std;
const int MAXN=205;
int f[MAXN][MAXN];
int n,k;int a[MAXN];
vector<int> ve[MAXN];
int tmp[MAXN];
void dfs(int u,int fa){
	f[u][0]=a[u];
	for(int i=0;i<ve[u].size();i++){
		int v=ve[u][i];
		if(v==fa) continue;
		dfs(v,u);
		for(int j=0;j<=n;j++)
			tmp[j]=f[u][j];
		for(int j=0;j<=n;j++)
			for(int t=max(0,k-j);t<=n;t++)
				tmp[min(j,t+1)]=max(tmp[min(j,t+1)],f[u][j]+f[v][t]);
		for(int j=0;j<=n;j++)
			f[u][j]=tmp[j];
	}
	return;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	dfs(1,0);int ans=0;
	for(int i=0;i<=n;i++)
		ans=max(ans,f[1][i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：littleseven (赞：10)

# CF 1249F Maximum Weight Subset

**题目链接：**[CF 1249F Maximum Weight Subset](https://www.luogu.org/problem/CF1249F)		[CF 1249F Maximum Weight Subset](https://codeforces.com/problemset/problem/1249/F)

**算法标签:**  `树`、`深搜`、`树形DP`

## 题目描述：

给定一棵含 $n$ 个节点的树，每个节点含一个点权 $a[i]$ 。现在请你选出一些节点，使得这些节点的权值和最大并且这些节点中任意两个节点的距离都 $>k$ 。并输出这个最大的权值。

输入第一行含两个整数 $n,k$ ，之后是 $n$ 个整数 $a[i]$ ，之后是 $n-1$ 行，每行两个整数，描述树的每条边。

## 题解：

**树形DP**

（CF div3最后一题很喜欢DP？？？？？   逃~）

感觉上挺神仙的一道题，这个考场上应该是真的想不到………………

也是研究了小半天官方题解搞明白了。

下面开始正题：

------

我们设这棵树有根并且根是$1$ ，之后来考虑以什么状态完成DP：

设$dp[pos][dep]$表示在$pos$的子树中符合条件的最大权值点集的权值和，并且保证这个最大权值点集中深度最小的点的深度$\ge dep$。（不太好理解…………）

之后的思路就是：我们需要计算 $pos$ 的所有子节点的 $dp[~][~]$，以此来更新 $dp[pos][0\sim n]$。

考虑当前的深度是 $dep$ ，就有以下的两种想法：

- 如果 $dep == 0$，我们可以得到

  $dp[pos][dep] = val[pos]+\sum_{to \in children(pos)}dp[to][max(0, k - dep - 1)]$，

- 如果 $dep!=0$，则可以得到 ($to \in children(pos)~~~to \neq now$)

  $dp[pos][dep]=max\{dp[pos][dep],dp[to][dep-1]+\sum_{now \in children(pos)}dp[now][max(dep-1,k-dep-1)]\}$

之后我们要明确一个问题，在这其中我们包含着 $k-dep-1$ 的计算，其实这里的 $k = k_{初始}+1$ ，原因就是这里的计算保证的是每一个选择到的点都要与当前点的距离 $\gt k$，而不是 $\ge k$。

上图理解一下：

![CF 1249F Maximum Weight Subset p1.png](https://i.loli.net/2019/10/23/tdRzEroMG8aAbP9.png)

 扔到整棵树里边：

![CF 1249F Maximum Weight Subset p2.png](https://i.loli.net/2019/10/23/g8dkJFU7apWVN9x.png)

下面看代码：

## AC代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 210;

vector <int> e[N];

int n, k, val[N];

int dp[N][N];

void add(int x, int y) {
	e[x].push_back(y);
	e[y].push_back(x);
}

void dfs(int pos, int pre) {
	dp[pos][0] = val[pos];
	for (int i = 0; i < (int)e[pos].size(); i ++ ) {
		int to = e[pos][i];
		if (to != pre) {
			dfs(to, pos);
		}
	}
	for (int dep = 0; dep < N; dep ++ ) {
		if (dep == 0) {
			for (int i = 0; i < (int)e[pos].size(); i ++ ) {
				int to = e[pos][i];
				if (to != pre) {
					dp[pos][dep] += dp[to][max(0, k - dep - 1)];
				}
			}
		}
		else {
			for (int i = 0; i < (int)e[pos].size(); i ++ ) {
				int to = e[pos][i];
				if (to == pre) {
					continue ;
				}
				int dis = dp[to][dep - 1];
				for (int i = 0; i < (int)e[pos].size(); i ++ ) {

					int now = e[pos][i];
					if (now == to || now == pre) {
						continue ;
					}
					dis += dp[now][max(dep - 1, k - dep - 1)];
				}
				dp[pos][dep] = max(dp[pos][dep], dis);
			}
		}
	}
	for (int dep = N - 1; dep > 0; dep -- ) {
		dp[pos][dep - 1] = max(dp[pos][dep - 1], dp[pos][dep]);
	}
}

int main() {
	scanf("%d%d", &n, &k);
	k ++ ;
	for (int i = 1; i <= n; i ++ ) {
		scanf("%d", &val[i]);
	}
	for (int i = 1; i <= n - 1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
	}
	dfs(1, 0);
	cout << dp[1][0] << endl;
	return 0;
}

```

---

## 作者：qcwlmqy (赞：4)

## CF1249F Maximum Weight Subset

### 题意

给出一个树，每个点有权值

求最大权值子集，且子集任意一对点的距离大于$k$

------

### 思路

- 明显的树上 $dp$
- 令 $dp[i][j]$ 表示以 $i$ 为根的子树，最小深度为 $j$ 的最大符合条件的子集

- ![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1249F/0b019d9da08990633b2a6779b2699db8afb883d7.png)

- 对于一个点，以 $1$ 为根，以 $4$ 为子树为根，显然有两种情况

  - 子集包含 $4$ 那么只需要加上 $4$ 的每个子树深度为 $k$ 的最大子集即可

  - ```cpp
    for (auto it : E[now]) {
        if (it == fa)
            continue;
        dp[now][0] += dp[it][k]; //与it距离为k，与now距离k+1
    }
    ```

    

  - 若不取 $4$ 则需要枚举深度为 $j$ 的点所在的子树，其他子树上的子集与该点距离应大于 $k$

  - ```cpp
    for (int i = 1; i < n; i++) {
        for (auto it : E[now]) {//枚举距离为j的点
            if (it == fa)
                continue;
            int cnt = dp[it][i - 1];
            for (auto other : E[now]) {
                if (other == it || other == fa)
                    continue;
                cnt += dp[other][max(i - 1, k - i)];//至少距离为i-1
            }
            dp[now][i] = max(dp[now][i], cnt);
        }
    }
    ```



- 复杂度
- 这个算法很容易估算为 $O(n^4)$ ，但其实是 $O(n^3)$
- 因为在算复杂度时，大家往往会**忽略 $dfs$ 在枚举子树的过程是 $O(n)$ 的，因为一棵树是只有$n-1$条边**

------

### 代码

```cpp
#include <bits\stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 205;
int a[maxn];
vector<int> E[maxn];
int n, k;
int dp[maxn][maxn];
void dfs(int now, int fa)
{
    dp[now][0] = a[now];
    for (auto it : E[now]) {
        if (it == fa)
            continue;
        dfs(it, now);
    }
    for (auto it : E[now]) {
        if (it == fa)
            continue;
        dp[now][0] += dp[it][k];
    }
    for (int i = 1; i < n; i++) {
        for (auto it : E[now]) {
            if (it == fa)
                continue;
            int cnt = dp[it][i - 1];
            for (auto other : E[now]) {
                if (other == it || other == fa)
                    continue;
                cnt += dp[other][max(i - 1, k - i)];
            }
            dp[now][i] = max(dp[now][i], cnt);
        }
    }
    for (int i = n - 1; i >= 0; i--)
        dp[now][i - 1] = max(dp[now][i - 1], dp[now][i]);
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1, 0);
    printf("%d\n", dp[1][0]);
    return 0;
}
```



---

## 作者：igAC (赞：3)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1249F)

[CFlink](https://codeforces.com/problemset/problem/1249/F)

简要题意：

给定一棵树，每个点有点权，你需要选出一些点，使得两两距离 $>k$，最大化选出点的点权和，并输出。

# $\text{Solution}$

2200？1200！

考虑树形 dp。

设 $f_{i,j}$ 表示以 $i$ 为根的子树内选取的点中的最小深度**不小于** $j$ 的最大点权和。

转移很好做：

先考虑如何转移最小深度**恰好为** $j$ 的情况。

- 若 $j=dep_i$

> $f_{i,j}=a_i + \sum_{u \in son_i} f_{u,j+k+1}$。

- 若 $j \neq dep_i$

> 可以枚举儿子 $u$，钦定这个点的子树内选取的最小深度的点的深度为 $j$。
> 
> 那其他儿子的子树内选取的最小深度为 $\max(j,2 \times dep_i - j + k + 1)$。
>
>即 $f_{i,j}=\max_{u \in son_i}\{f_{u,j}+\sum_{v \in son_u,v \neq u}f_{v,\max(j,2 \times dep_i - j + k + 1)}\}$。
>
>这是 $O(n^3)$ 的，很容易可以优化为 $O(n^2)$，虽然 $O(n^3)$ 也能过。

第一个状态其实就是第二个状态的后缀 $\max$，转移完后处理即可。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define N 205
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,k,a[N],head[N],tot,f[N][N<<1],deep[N];//dp 数组开两倍可以避免边界问题
struct Edge{
	int to,nxt;
}e[N<<1];
void add_edge(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
void dfs1(int x,int fa){
	deep[x]=deep[fa]+1;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa) continue;
		dfs1(y,x);
	}
}
void dfs2(int x,int fa){
	f[x][deep[x]]=a[x];
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa) continue;
		dfs2(y,x);
	}
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa) continue;
		f[x][deep[x]]+=f[y][deep[x]+k];
	}
	for(int i=deep[x]+1;i<=n;++i){
		int sum=0;
		for(int t1=head[x];t1;t1=e[t1].nxt){
			int y=e[t1].to;
			if(y==fa) continue;
			int j=max(i,deep[x]+k-i+deep[x]);
			sum+=f[y][j];
		}
		for(int t1=head[x];t1;t1=e[t1].nxt){
			int y=e[t1].to;
			if(y==fa) continue;
			int j=max(i,deep[x]+k-i+deep[x]);
			f[x][i]=max(f[x][i],sum-f[y][j]+f[y][i]);
		}
	}
	for(int i=n;i>=deep[x];--i) f[x][i]=max(f[x][i],f[x][i+1]);
}
int main(){
	n=read(),k=read()+1;
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(1,0),dfs2(1,0);
	printf("%d",f[1][1]);
	return 0;
}
```

---

## 作者：傅思维666 (赞：2)


## 题解：

~~题目翻译过来发第一篇题解（英语巨菜无所谓）~~

来讲一下正解：树上DP。

我们从0开始为节点编号，并设置0为根节点。

* DP的状态是这样的：设$dp[x][dep]$为以$x$为根节点的**子树**中所有选中节点中深度最小的节点深度为$dep$时的最大价值（有点绕...请好好理解）

  这里要注意，我们定义的深度并不是整棵树的深度。因为动态规划是利用状态转移，所以我们定义的这个$dep$是在当前状态下的深度。通俗地讲，就是这棵子树的深度（子树根节点深度为0）。

那么我们开始考虑状态转移。这道题的一个限定条件（比较难搞）还有一个任意两点的距离都大于$k$。我们的状态转移（包括状态设置）都是考虑这个而进行的。

可以看出，对于每一个节点，它既统计了它自己的答案，又对它的合法的祖宗们（滑稽.jpg）的答案有贡献。所以，据此，我们考虑**两种情况**：第一种，当前的节点是子树的根，这个时候它是它的小家族的最大的祖宗，开始统计它的答案。第二种，当前的节点是儿子或孙儿或...这个时候它要对它上面的祖宗们贡献答案。

根据我们对状态的定义，在第一种情况下，当前节点的深度为0，那么当前节点的答案
$$
dp[x][dep]=a[x]+\sum_{to\in children(x)}dp[to][max(0,k-dep)].
$$
在第二种情况下，我们则需要遍历$x$节点的所有儿子，然后挑出对答案贡献最大的儿子来更新答案。转移方程就是：
$$
dp[x][dep]=max(dp[x][dep],dp[x][dep-1]+\sum_{to\in children(x)}dp[to][max(dep-1,k-dep)]).
$$
这个时候就能比较容易地想到用深搜解决问题。因为深搜的性质恰好满足：从上搜到低，在从低到上更新答案的过程。所以，我们把答案再从$n-1$号点跑回$0$号点即可。最终的答案就是$dp[0][0]$。



代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=210;
int n,k;
int a[maxn],d[maxn],dp[maxn][maxn],tmp[maxn];
int tot,head[maxn],nxt[maxn<<1],to[maxn<<1];
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int f)
{
	dp[x][0]=a[x];
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y!=f)
			dfs(y,x);
	}
	for(int i=0;i<n;i++)
	{
		if(!i)
		{
			for(int l=head[x];l;l=nxt[l])
			{
				int y=to[l];
				if(y==f)
					continue;
				dp[x][0]+=dp[y][k];
			}
		}
		else
		{
			for(int l=head[x];l;l=nxt[l])
			{
				int y=to[l];
				if(y==f)
					continue;
				int now=dp[y][i-1];
				for(int j=head[x];j;j=nxt[j])
				{
					int yy=to[j];
					if(yy==f || yy==y)
						continue;
					now+=dp[yy][max(i-1,k-i)];
				}
				dp[x][i]=max(dp[x][i],now);
			}
		}
	}
	for(int i=n;i>=1;i--)
		dp[x][i-1]=max(dp[x][i-1],dp[x][i]);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<n-1;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		u--,v--;
		add(u,v);
		add(v,u);
	}
	dfs(0,-1);
	printf("%d",dp[0][0]);
	return 0;
}
```



---

## 作者：E1_de5truct0r (赞：1)

由于我太菜了不会长剖，所以只能给这个题写个暴力 DP 做法了。

---

首先这个 $>k$ 我们可以转化为 $\geq k+1$。后文的 $k$ 默认已经 $+1$。

我们考虑以 $u$ 为根的子树。不难发现，我们只需要知道 $u$ 子树内距离 $u$ 最近的点距离为 $i$ 即可按照题目限制进行转移了。

所以令 $dp_{u,i}$ 表示以 $u$ 为根的子树内，距离 $u$ 最近的点的距离 $\geq i$ 的时候，答案的最大值。

转移的话，按照树形背包的常用套路，我们考虑从 $u$ 的儿子 $v$ 向上转移。

由于不考虑重复贡献的话，我们选定的强制对距离做出贡献的点只会有一个，我们每次转移的添加过程中可以决策当前的 $v$ 是否强制做出贡献，进而分类讨论。

$dp_{u,i}=\max\begin{cases}dp_{u,i}+dp_{v,\max(i-1,k-i-1)}\\dp_{u,\max(i,k-i)}+dp_{v,i-1}\end{cases}$

由于每次 dfs 之后得到的 dp 数组中，$dp_{u,i}$ 只考虑了恰好为 $i$ 的情况，所以要跑一遍后缀最大值使 dp 数组记录的数是符合我们的定义的。

最终的答案为 $dp_{1,0}$。复杂度 $O(n^2)$。

[Code & Submission](https://codeforces.com/contest/1249/submission/211250455)

---

## 作者：Jsxts_ (赞：1)

感觉思路挺直接的。

考虑设 $f_{x,k}$ 表示 $x$ 子树内，距 $x$ 最近的被选中点距 $x$ 为 $k$，$x$ 子树答案的最大值。

转移的话，考虑枚举之前最近的距离是 $j$，现在这个儿子 $v$ 最近的距离是 $k$，转移方程为：

$$f_{x,\min(j,k)}=\max_{v\in son(x)}\{tmp_j+f_{v,k-1}\}$$

这里的 $tmp$ 其实就是 $f_x$，只是转移时避免重复设的临时数组。

然后还有一种情况，就是前面没有选，只在这个儿子选，直接将儿子的 $f$ 值继承过来即可：

$$f_{x,k}=\max_{v\in son(x)}\{f_{x,k},f_{v,k-1}\}$$

注意枚举时的上下界，最后答案就是 $\max_{i=1}^{dep_1}f_{1,i}$。其中 $dep_i$ 表示 $i$ 子树的最大深度。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 2e9;
int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return s*f;
}
void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
struct edge {
	int v,nxt;
}ed[410];
int head[210],cnt;
void add(int u,int v) {
	ed[++cnt] = {v,head[u]};
	head[u] = cnt;
}
//f[x][k]:子树内距x最近的选中点距离为k，x子树内的最大值
int n,K,f[210][210],a[210],dep[210],tmp[210];
void dfs1(int x,int fa) {
	f[x][0] = a[x];
	dep[x] = 1;
	for (int i = head[x];i;i = ed[i].nxt) {
		int v = ed[i].v;
		if (v == fa) continue;
		dfs1(v,x);
		for (int j = 0;j <= dep[x];j ++ ) tmp[j] = f[x][j];
		for (int j = 0;j <= dep[x];j ++ )
			for (int k = max(1,K - j);k <= dep[v];k ++ )
				f[x][min(j,k)] = max(f[x][min(j,k)],tmp[j] + f[v][k - 1]);
		for (int j = 1;j <= dep[v] + 1;j ++ ) f[x][j] = max(f[x][j],f[v][j - 1]);
		dep[x] = max(dep[x],dep[v] + 1);
	}
//	cout << x << ":" << endl;
//	for (int i = 0;i <= dep[x];i ++ )
//		cout << f[x][i] << ' ';puts("");
}
int main() {
	n = read(), K = read() + 1;
	for (int i = 1;i <= n;i ++ ) a[i] = read();
	for (int i = 1;i < n;i ++ ) {
		int u = read(),v = read();
		add(u,v), add(v,u);
	}
	dfs1(1,0);
	int ans = 0;
	for (int i = 0;i <= dep[1];i ++ ) ans = max(ans,f[1][i]);
	cout << ans;
	return 0;
}
```


---

## 作者：Sorato_ (赞：0)

# CF1249F Maximum Weight Subset 题解

## 题目大意

给定一个 $n$ 个节点的树，每个节点有点权 $a_i$。从中选出若干节点，要求这些点两两之间距离大于给定常数 $k$，使得点权和最大。

## Solve

给出一种线性做法。前置知识：长链剖分优化 DP。

考虑一个 DP：设 $f(u,d)$ 表示在 $u$ 的子树里选点，选出的点距离 $u$ 号点的最短距离为 $d$，这种情况下的最大点权和。暴力转移是简单的：
$$
f(u,\min(j,i+1))\longleftarrow f(u,j)+f(v,i)
$$
总复杂度为 $O(n^3)$。

第二维和深度（距离）有关，容易长链剖分优化到 $O(n^2)$，即 $u$ 号节点直接继承其重儿子的 $f$ 值，对于轻儿子，枚举上式种的 $i,j$ 转移。复杂度约为 $O(n^2)$。这部分的代码如下，用指针实现：

```c++
void dp(int u,int fa)
{
	if(son[u])	dp(son[u],u);//先遍历重儿子
	f[u][0]=a[u];
	for(int i=k+1;i<h[u];i=-~i)
		f[u][0]=max(f[u][0],f[u][i]+a[u]);
	for(int v:e[u])
		if(v!=fa&&v!=son[u])
		{
			dp(v,u);
			for(int i=0;i<h[u];i=-~i)	now[i]=f[u][i];//用上个版本的
			for(int i=0;i<h[v];i=-~i)//h[v] 为 v 节点的链长
			{
				f[u][i+1]=max(f[u][i+1],f[v][i]);
				for(int j=max(k-i,0ll);j<h[u];j=-~j)
					f[u][min(i+1,j)]=max(f[u][min(i+1,j)],now[j]+f[v][i]);
			}
		}
}
```

瓶颈在于对 $u$ 所在链长的枚举。所以我们考虑对 $\min(i+1,j)$ 讨论，因为它的最大值为 $v$ 所在链长，均摊是 $n$ 级别的。

- 若 $j\leq i$，$\min(i+1,j)=j$，此时 $1\leq j\leq h(v)$，可以暴力枚举 $j$，那么可以对这个 $j$ 贡献的 $i$ 需要满足 $j\leq i<h(v),i+j+1>k\iff i\geq k-j$，这是一段后缀，所以我们可以维护 $g(v)$ 为 $f(v)$ 的后缀最大值，就有转移：

$$
f(u,j)\longleftarrow f(u,j)+g(v,\max(j,k-j))
$$

- 若 $j>i$，$\min(i+1,j)=i+1$，由于本身就有 $0\leq i<h(v)$，此时我们可以枚举 $i$，那么可以对这个 $i$ 贡献的 $j$ 需要满足 $i<j<h(u),i+j+1>k\iff j\geq k-i$，有转移：

$$
f(u,i+1)\longleftarrow g(u,\max(i+1,k-i))+f(v,i)
$$

至此，总复杂度为 $O(\sum链长)=O(n)$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=2e5+10;
int n,k,a[N];
vector<int>e[N];
int mem[2][N]/*内存池*/,*f[N],*g[N],h[N],son[N],tim;
void get_son(int u,int fa)
{
	h[u]=1;
	for(int i:e[u])
		if(i!=fa)
			get_son(i,u),h[u]=max(h[u],h[i]+1);
	if(h[u]>h[son[fa]])	son[fa]=u;
}
void get_chain(int u,int fa)//分配内存
{
	tim=-~tim;
	f[u]=mem[0]+tim;g[u]=mem[1]+tim;
	if(son[u])	get_chain(son[u],u);
	for(int i:e[u])
		if(i!=fa&&i!=son[u])	get_chain(i,u);
}
void dp(int u,int fa)
{
	if(son[u])	dp(son[u],u);
	f[u][0]=a[u]+(k+1<h[u]?g[u][k+1]:0);
	g[u][0]=max(f[u][0],h[u]>1?g[u][1]:0);
	for(int v:e[u])
		if(v!=fa&&v!=son[u])
		{
			dp(v,u);
			for(int i=0;i<h[v];i=-~i)
				if(max(i,k-i)<h[v])
					f[u][i]=max(f[u][i],f[u][i]+g[v][max(i,k-i)]);
			for(int i=0;i<h[v];i=-~i)
			{
				f[u][i+1]=max(f[u][i+1],f[v][i]);
				if(max(i+1,k-i)<h[u])
					f[u][i+1]=max(f[u][i+1],f[v][i]+g[u][max(i+1,k-i)]);
			}
			for(int i=h[v];i>=0;i=~-i)
				g[u][i]=max(i+1<h[u]?g[u][i+1]:0,f[u][i]);
		}
}
signed main()
{
	n=read();k=read();
	for(int i=1;i<=n;i=-~i)	a[i]=read();
	for(int i=1,u,v;i<n;i=-~i)
		u=read(),v=read(),
		e[u].push_back(v),e[v].push_back(u);
	get_son(1,0);get_chain(1,0);dp(1,0);
	return printf("%lld",*max_element(f[1],f[1]+h[1])),0;
}
```

---

## 作者：Planetary_system (赞：0)

## 题面解释：
一棵有 $n$ 个节点的树，点权分别为 $a[i]$。选出一些任意两个节点的距离都 $>k$ 的节点，求权值和最大值。

## 思路分析：
树形`dp`，$dp_{i,j}$ 表示距离 $i$ 选择的最近的节点距离为 $j$。 

在遍历树的过程中转移状态，首先 $dp_{u,0}$ 赋初始值为 $val_u$，表示只选取 $u$ 这个节点。

确定一个节点为根，向下递归，优先合并子树，从下往上转移，从子节点 $v$ 转移到 $u$ 可得出转移方程为 $dp_{u,\min (i,j+1)}=\max dp_{u,i}+dp_{v,j}$。

注意不能直接在 $dp$ 数组上转移，需要转移完再赋值。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e2+10;
int n,k,dp[N][N],val[N],ndp[N];
vector<int>g[N];
void merge(int u,int v){
	for(int i=0;i<=n;i++)
		ndp[i]=dp[u][i];
	for(int i=0;i<=n;i++)
		for(int j=max(0ll,k-i);j<=n;j++)
			ndp[min(i,j+1)]=max(ndp[min(i,j+1)],dp[u][i]+dp[v][j]);
	for(int i=0;i<=n;i++)
		dp[u][i]=ndp[i];
	return;
}
void dfs(int u,int p){
	dp[u][0]=val[u];
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v!=p)dfs(v,u),merge(u,v);
	}
	return;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld",&val[i]);
	for(int i=1,x,y;i<n;i++){
		scanf("%lld%lld",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0);
	int mx=0;
	for(int i=0;i<=n;i++)
		mx=max(mx,dp[1][i]);
	printf("%lld",mx);
	return 0;
}
```

谢谢！

---

