# [USACO25JAN] DFS Order P

## 题目描述

Bessie 有一个无向简单图，结点编号为 $1\dots N$（$2\le N\le 750$）。她通过调用函数 $\texttt{dfs}(1)$ 生成该图的一个深度优先搜索（depth-first search，DFS）序，函数由以下 C++ 代码定义。各邻接表（对于所有 $1\le i\le N$ 的 $\texttt{adj}[i]$）在开始深度优先搜索之前可以任意排列，因此一个图可以有多个可能的 DFS 序。

```cpp
vector<bool> vis(N + 1);
vector<vector<int>> adj(N + 1);  // 邻接表
vector<int> dfs_order;

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    dfs_order.push_back(x);
    for (int y : adj[x]) dfs(y);
}
```

给定图的初始状态以及修改每条边状态的代价。具体地说，对于每对满足 $1\le i<j\le N$ 的结点 $(i,j)$，给定一个整数 $a_{i,j}$（$0<|a_{i,j}|\le 1000$），其中

- 如果 $a_{i,j}>0$，则边 $(i,j)$ 当前不在图中，可以以代价 $a_{i,j}$ 添加。
- 如果 $a_{i,j}<0$，则边 $(i,j)$ 当前在图中，可以以代价 $-a_{i,j}$ 移除。

求使得 $[1,2\dots,N]$ 成为一个可能的 DFS 序的最小总代价。

## 说明/提示

样例 1 解释：

初始时，图中没有边。可以添加边 $(1,2),(2,3),(2,4)$ 可以得到总代价 $1+3+6$。现在图有两个可能的 DFS 序：$[1,2,3,4],[1,2,4,3]$。

样例 2 解释：

初始时，图中包含边 $(1,2),(2,3),(2,4),(1,5),(2,5),(3,5)$。移除边 $(3,5)$ 可以得到总代价 $5$。

样例 3 解释：

初始时，图中包含边 $(1,2),(1,3),(2,4)$。移除边 $(2,4)$ 并且添加边 $(1,4)$ 可以得到总代价 $5+4=9$。

- 测试点 $4\sim 9$：所有 $a_{i,j}>0$。
- 测试点 $10\sim 16$：$N\le 50$。
- 测试点 $17\sim 23$：没有额外限制。



## 样例 #1

### 输入

```
4
1
2 3
40 6 11```

### 输出

```
10```

## 样例 #2

### 输入

```
5
-1
10 -2
10 -7 10
-6 -4 -5 10```

### 输出

```
5```

## 样例 #3

### 输入

```
4
-1
-2 300
4 -5 6```

### 输出

```
9```

# 题解

## 作者：sunkuangzheng (赞：8)

> 给定一张 $n(1 \le n \le 750)$ 个点的无向图，可以花费 $a_{i,j}(a_{i,j} \ge 0)$ 的代价修改边 $(i,j)$ 的存在状态，求让 $[1,2,\ldots,n]$ 变成原图一个 DFS 序的最小代价。

首先考虑原图里没有边的部分分，此时最后图的形态一定是一棵树。

注意到 dfs 树的结构是很好的，一个子树内的点集一定是一个连续区间，且没有向外连边。每个子树内部的决策实际上是独立的。令 $f_{l,r}$ 表示以 $l$ 为根的子树包含区间 $[l,r]$ 的最小代价，转移时枚举新加进来的子树 $[k+1,r]$，有 $f_{l,r} \gets f_{l,k} + f_{k+1,r} + a_{l,k+1}$。时间复杂度 $\mathcal O(n^3)$。

考虑现在原图有一些边，我们可以直接将它们全删除，然后将加这条边的代价改成 $-a_{i,j}$。由于存在负边，最终图的形态可能会包含一些返祖边，但是不会包含横插边。 继续使用上述 DP，注意到在把子树 $[k+1,r]$ 加入 $[l,k]$ 时只会增加返祖边 $(l,k+1),(l,k+2),\ldots,(l,r)$，我们把代价是负的加进来即可。前缀和预处理后总复杂度仍然是 $\mathcal O(n^3)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 28.01.2025 13:37:41
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 751;
using namespace std;
int T,n,a[N][N],f[N][N],sm[N][N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin >> n; int c = 0;
	for(int j = 2;j <= n;j ++) for(int i = 1;i < j;i ++) cin >> a[i][j],
		c += a[i][j] < 0 ? -a[i][j] : 0;
	for(int i = 1;i <= n;i ++) f[i][i] = 0;
	for(int i = 1;i <= n;i ++) for(int j = i + 1;j <= n;j ++)
		sm[i][j] = sm[i][j-1] + (a[i][j] < 0 ? a[i][j] : 0);
	for(int l = 2;l <= n;l ++) for(int i = 1;i + l - 1 <= n;i ++){
		int j = i + l - 1; f[i][j] = 1e9;
		for(int k = i;k < j;k ++)
			f[i][j] = min(f[i][j],f[i][k] + f[k + 1][j] + sm[i][j] - sm[i][k+1] + a[i][k+1]);
	}cout << f[1][n] + c << "\n"; 	
}
```

---

## 作者：Le0Chan (赞：3)

感觉是很优美的题。

先看部分分：所有 $a_{i,j}>0$，这意味着图初始时无边。那贪心地想肯定是要建出一棵树出来。如何保证一棵树存在一个拓扑序为 $[1,n]$ 呢？如果给出树，想要 check 是好办的，按照顺序能走就走即可。但是这一方向不利于我们构造。

从构造的角度来说，首先要考虑到 dfs 序的一些基本性质，诸如第一个元素为 dfs 树的根，最后一个元素一定是叶子等等。那么这棵树的根首先需要是 $1$，$1$ 的下面需要下挂一些儿子，因为一棵子树的 dfs 序是连续的，所以将儿子们的 dfs 序依次排开就是 $[2,p_1],[p_1+1,p_2],\cdots, [p_{k-1}+1,p_k]$，可以拼成 $[2,n]$。这样的段式结构启发我们进行 dp。

设 $f_{l,r}$ 为建出 dfs 序区间 $[l,r]$ 的一棵树的最小代价，类比上述过程，$l$ 一定是根，枚举最后一个儿子的分界点 $j=p_{k-1}+1$，对 $f_{l,r}$ 的贡献是 $f_{l,j-1}+f_{j,r}+a_{l,j}$，最后一项即将根和这个儿子连接起来的代价。复杂度 $O(n^3)$，可以通过该部分分。

现在图上多了一些边出来，也就是 dfs 树上有些边已经存在了，这时不用算贡献。还有情况是多了一些非树边。我们需要保证他还是一棵 dfs 树，众所周知这一条件等价于不存在横插边，或者说非树边都是返祖边。在 dp 的时候我们要删去横插边。但是这些边的贡献不好统计。不妨容斥一下计算返祖边，返祖边端点一定存在祖先关系，我们将其挂在深度较小处统计。怎么在 dp 时计算呢？考虑点 $x$ 伸出去的边 $(x,z)$ 满足 $z$ 不是 $x$ 儿子的都是返祖边，$x$ 为根时在枚举每个儿子的同时可以得到子树内非儿子的点，形成了一些区间，也就是上面所说的 $(p_i+1,p_i]$。预处理时做前缀和即可 $O(1)$ 计算，复杂度是 $O(n^3)$，可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Le0{
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db double
#define _int __int128
#define vi vector<int>
#define tii tuple<int,int,int>
const int N=755,inf=0x3f3f3f3f;
const ll lnf=1e18;
int n;
int a[N][N],f[N][N],sm[N][N];
bool vis[N][N];
int sol(int l,int r){
    if(vis[l][r]) return f[l][r];
    vis[l][r]=1;
    if(l==r) return f[l][r]=0;
    if(l>r) return f[l][r]=inf;
    f[l][r]=inf;
    for(int k=l;k<r;k++){
        f[l][r]=min(f[l][r],sol(l,k)+sol(k+1,r)+a[l][k+1]-(sm[l][r]-sm[l][k+1]));
    }
    return f[l][r];
}
void sv(){
    cin>>n;
    int tot=0;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            cin>>a[j][i];
            a[i][j]=a[j][i];
            if(a[i][j]<0) tot-=a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sm[i][j]=sm[i][j-1]+(a[i][j]<0?-a[i][j]:0);
        }
    }
    int v=sol(1,n);
    cout<<v+tot<<'\n';
}
int main(){
    // int _T;cin>>_T;
    // while(_T--){
        sv();
    // }
    return 0;
}
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    return Le0::main();
}
```

---

## 作者：ZHR100102 (赞：2)

考虑 **DFS 序的性质**，不难发现我们在 DFS 的过程中相当于遍历了一棵树，得出的序列是 DFS 序，而每个树又可以递归地分解成根节点的各个子树，所以我们可以尝试**把子树的结构放在一个区间上刻画**，即利用 DFS 序上子树的区间结构进行 DP。一个父区间由多个子区间，也就是树上的多个儿子组成。

我们先考虑原图没有任何边的情况，此时代价只出现在父亲向儿子连边的时候。所以定义 $dp_{l,r}$ 表示形成 DFS 序 $[l,r]$ 的子树所需要的最小代价。至于合并操作，我们套路地考虑往区间后面加一个区间该如何合并信息。不难发现，**一个区间是由最左侧的单个元素（根节点）与右边追加的多个子树对应的区间拼成的**。于是合并信息的时候我们只需要考虑根节点与新加进来的区间的根节点之间连边的代价即可。转移也是套路的枚举分割点即可。

现在考虑原有的会导致我们 DFS 序无法形成的边怎么删去，观察可知，对于形成的 DFS 树而言，**前向边、返祖边是不会影响 DFS 序的形成的**，因为我们可以先不走前向边，让前向边在后面走的时候失效；返祖边在遍历到的时候就不会有任何作用。所以**只有横叉边会对 DFS 序有影响**。

再次考虑如何合并横叉边的影响，我们可以把横叉边的贡献在合并区间（子树）的时候就处理掉。具体地，我们在枚举分割点的时候，找到左区间除去根节点外，和右区间节点之间的边，就是横叉边，计算它们的删除代价即可。

实现上，我们可以在邻接矩阵上做一个**二维前缀和**来快速计算删除横叉边的代价。

时间复杂度 $O(n^3)$，因为要枚举合并时的分割点。


```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
#define lc(x) (tr[x].ls)
#define rc(x) (tr[x].rs)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
const int N=805;
int n,a[N][N],dp[N][N],b[N][N];
int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=i-1;j++)
        {
            cin>>a[j][i];
            if(a[j][i]<0)b[j][i]=-a[j][i];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
        }
    }
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;i++)dp[i][i]=0;
    for(int len=2;len<=n;len++)
    {
        for(int i=1;i+len-1<=n;i++)
        {
            int j=i+len-1;
            for(int k=i;k<j;k++)
            {
                int c=dp[i][k]+dp[k+1][j];
                if(a[i][k+1]>0)c+=a[i][k+1];
                if(i!=k)c+=b[k][j]-b[i][j]-b[k][k]+b[i][k];
                dp[i][j]=min(dp[i][j],c);
            }
        }
    }
    cout<<dp[1][n];
    return 0;
}
```

---

## 作者：qnqfff (赞：1)

### 思路

考虑区间 dp，设 $dp_{i,j}$ 表示以 $i$ 为起点使得 $[i,i+1\dots,j]$ 成为一个可能的 DFS 序的最小总代价。

考虑如何转移，对于两个区间 $[l,k]$ 和 $[k+1,r]$，只需将 $k+1$ 接到 $l$ 后面即可，于是总价为断掉所有 $u\in[l+1,k],v\in[k+1,r]$ 的边并接上 $(l,k+1)$，二维前缀和即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,a[755][755],b[755][755],dp[755][755];
signed main(){
	n=read();for(int i=2;i<=n;i++) for(int j=1;j<i;j++){int x=read();if(x>0) a[j][i]=x;else b[j][i]=-x;}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];
	for(int len=2;len<=n;len++) for(int i=1,j=len;j<=n;i++,j++){
		dp[i][j]=1e18;auto calc=[&](int x,int _x,int y,int _y){if(x>_x||y>_y) return 0ll;return b[_x][_y]-b[x-1][_y]-b[_x][y-1]+b[x-1][y-1];};
		for(int k=i;k<j;k++) dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+calc(i+1,k,k+1,j)+a[i][k+1]);
	}cout<<dp[1][n];
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

好题。

考察走出 $[1,2,\ldots,n]$ 时 dfs 树的形态。发现任意一个子树的节点编号必然是一段连续的区间。考虑将这个区间作为状态进行 dp。

设 $f_{l,r}$ 表示在 dfs 树中以 $l$ 为根的子树，其管辖的编号范围为 $[l,r]$，构造出这样一颗子树所需的最小代价。考虑 $a_{i,j}>0$，此时直接构造一棵满足上述条件的树即可。考虑每次将一颗合法子树接入 $l$ 的子树中，则 $f_{l,k}+f_{k+1,r}+a_{l,k+1}\to f_{l,r}$。

考虑存在 $a_{i,j}<0$ 的情况。此时接入会出现横叉边，需要删除。需要删除的横叉边形如 $(u,v)$ 其中 $u\isin [l+1,k],v\isin [k+1,r]$。发现 $k$ 自增 $1$ 时，增减量分别为 $a_{k+1}$ 中的两段区间，前缀和即可快速修改。

时间复杂度：$\mathcal{O}(n^3)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair 
#define pob pop_back
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=757,ee=3e18;
ll n,a[maxn][maxn],s[maxn][maxn],f[maxn][maxn];
inline void ups(ll &a,ll b){a=min(a,b);}
int main(void){
	//freopen("data.in","r",stdin); 
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=2;i<=n;i++)for(int j=1;j<i;j++){
		cin>>a[i][j],a[j][i]=a[i][j];
		if(a[i][j]<0) s[i][j]=s[j][i]=-a[i][j];
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++) s[i][j]+=s[i][j-1];
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++) f[i][i]=0;
	for(ll l=n;l>=1;l--)for(ll r=l+1;r<=n;r++){
		for(ll k=l,cur=0;k<r;k++){
			ups(f[l][r],f[l][k]+f[k+1][r]+max(a[l][k+1],0ll)+cur);
			cur=cur+s[k+1][r]-s[k+1][k+1]-(s[k+1][k]-s[k+1][l]);
		}
	}
	cout<<f[1][n]<<"\n";
	return 0;
}
```

---

## 作者：Lijiangjun4 (赞：0)

# P11676 题解
## 解题思路
先观察部分分，发现有一档的部分分满足 $a_{i,j}>0$ 均成立，即所有边都没有被加入。为了使答案最小，加入的边应尽量少，那么构造一棵树肯定是最优的。

考虑 DFS 序为 $[1,2,\dots,n]$ 的子树的性质，会发现每一棵子树内的节点编号是**连续的**，所以考虑区间 DP。

定义 $f_{i,j}$ 表示节点编号为 $[i,j]$ 这段连续区间的子树代价最小值，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/xlunjbmd.png)

将子树 $[k,j]$ 合并到子树 $[i,k-1]$ 上，代价为 $f_{i,k-1}+f_{k,j}+a_{i,k}$，所以，我们得到转移方程如下：
$$
f_{i,j}=\displaystyle\max^{j}_{k=i+1}f_{i,k-1}+f_{k,j}+a_{i,k}
$$

现在考虑正解，即图上之前有边的情况。
发现：原 DFS 树上可以存在返祖边，但不能存在横插边。即：将子树 $[i,k]$ 和子树 $[k+1,j]$ 合并时，$(i,k+1),(i,k+2),\dots,(i,j)$ 这些边是允许存在的。我们可以先将所有在图上存在的边删去，并记录删去的代价，将这条边重新加入图的代价设为负的（由于最开始这样的边的边权就是负的，所以不用处理）在 DP 时，$(i,k+1),(i,k+2),\dots,(i,j)$ 这些边中边权为负数的边也加入 DFS 树中。可以用前缀和维护。

设 $c_{i,j}$ 表示 $(i,i),(i,k+2),\dots,(i,j)$ 这些边中边权为负数的边边权之和，那么得到 DP 转移式：

$$
c_{i,j}=
\left\{
\begin{array}{ll}
0&,i>j\\
c_{i,j-1}+[a_{i,j}<0]\times a_{i,j}&,i\leq j
\end{array}
\right.\\

f_{i,j}=
\left\{
\begin{array}{ll}
0&,i\geq j\\
\displaystyle\max^{j}_{k=i+1}f_{i,k-1}+f_{k,j}+a_{i,k}+c_{i,j}-c{i,k}&,i<j
\end{array}
\right.
$$

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
namespace io{
	long long read()
	{
		long long res=0,neg=1;
		char c;
		while((c=getchar())<48||c>57)
		{
			if(c==45) neg=-1;
		}
		while(c>=48&&c<=57)
		{
			res=(res<<1)+(res<<3)+c-48;
			c=getchar();
		}
		return res*neg;
	}
	void uwrite(long long x)
	{
		if(!x) return;
		uwrite(x/10);
		putchar(x%10+48);
		return;
	}
	void write(long long x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x==0)
		{
			putchar('0');
			return;
		}
		uwrite(x);
		return;
	}
	void writes(long long x)
	{
		write(x);
		putchar(32);
	}
	void writel(long long x)
	{
		write(x);
		putchar(10);
	}
	char getChar()
	{
		char ch='\0';
		while(!((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))) ch=getchar();
		return ch;
	}
}using namespace io;
int n,a[800][800];
int f[800][800];
int c[800][800];
int ans;
int main()
{
	n=read();
	memset(f,0x7f,sizeof(f));
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=i-1;j++)
		{
			a[i][j]=a[j][i]=read();
			if(a[j][i]<0) ans-=a[j][i];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			c[i][j]=c[i][j-1]+(a[i][j]<0)*a[i][j];
		}
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=i;j<=n;j++)
		{
			if(i==j) f[i][j]=0;
			else for(int k=i+1;k<=j;k++)
			{
				f[i][j]=min(f[i][j],f[i][k-1]+f[k][j]+c[i][j]-c[i][k]+a[i][k]);
			}
		}
	}
	writel(ans+f[1][n]);
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/206168619)

---

## 作者：Erine (赞：0)

考虑 dfs 序为 $1\sim n$ 的必要条件为 dfs 树的所有子树都构成一个编号连续段。

区间 dp，$f_{l,r}$ 表示只考虑 $[l, r]$ 区间内的点和边，使得存在从 $l$ 开始的 dfs 序为 $l\sim r$ 的最少代价。

转移枚举 $l$ 的最后一个儿子 $p$，然后这个时候要求：

- 存在 $ (l,p)$
- $[l+1,p-1]$ 中不能与 $[p,r]$ 中有边

可以简单计算。时间复杂度三方。

---

## 作者：rlc202204 (赞：0)

# [P11676 [USACO25JAN] DFS Order P](https://www.luogu.com.cn/problem/P11676)

**题意：**

有一个 $n$ 个点的无向图和一个 $n \times n$ 的矩阵 $a$，$a_{i,j} > 0$ 说明这条边当前不在，加入的代价是 $a_{i,j}$，$a_{i,j} < 0$ 说明这条边当前在，删除的代价是 $-a_{i,j}$。

可以增删一些边，使得存在一个 dfs 序是 $1,2,3,\dots,n$。

$n \le 750$。

**思路：**

这个数据范围不是网络流就是 dp，经过尝试会发现网络流不太好做，考虑 dp。

如果我们当前搜到了 $i$，则我们要求除了走过来的这条边，$i$ 不能和前面的点有任何连边。

我们考虑区间 dp：设 $f(i,j)$ 表示进入 $i$ 的子树中，最后一个搜完的是 $j$。

首先，有 $\sum_{k=j+1}^n \max\{0,-a_{i,k}\}$ 的代价，因为如果 $j$ 之后 $i$ 回溯了那么是不能和后面有边的。

我们先不考虑这个代价，我们类似树形 $dp$ 考虑一个子树一个子树的加入。

枚举一个 $j$，考虑能转移到哪些状态。

我们枚举下一个子树到 $k$，则转移就是：

$$
f(i,j) + f(j+1,j+k) + \max\{0,a_{i,j+1}\} \to f(i,j+k)
$$

这样就能 $O(n^2)$ 求出所有 $f_i(j)$，总的时间复杂度就是 $O(n^3)$。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 755;
const int inf = 0x3f3f3f3f;

int n;
int a[N][N] = {{0}};

int f[N][N] = {{0}}, g[N][N] = {{0}};
void cmn(int &x, int y) {
	x = min(x, y);
}

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++)
		for (int j = 1; j < i; j++)
			scanf("%d", &a[j][i]);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++)
			g[i][j] = max(0, -a[i][j]);
		for (int j = n - 1; j >= i + 1; j--)
			g[i][j] += g[i][j + 1];
	}
	memset(f, 0x3f, sizeof f);
	for (int i = n; i >= 1; i--) {
		f[i][i] = 0;
		for (int j = i; j <= n; j++) {
			if (f[i][j] != inf) {
				for (int k = 1; j + k <= n; k++) {
					cmn(f[i][j + k], f[i][j] + f[j + 1][j + k] + max(0, a[i][j + 1]));
				}
			}
		}
		for (int j = i; j <= n; j++)
			f[i][j] += g[i][j + 1];
	}
	cout << f[1][n] << endl;
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：0)

先考察充要，即存在一个生成树作为 DFS 树，且非树边都为返祖边。

大家熟知的 DFS 的性质：一个子树的 DFS 序组成连续的一段区间。

据此可以想到区间 DP，设 $f_{l,r}$ 表示标号在 $[l,r]$ 中的点（其 DFS 序也是 $[l,r]$）组成一棵子树的最大价值，枚举根结点 $l$ 的最末棵子树标号最小的点 $j$，那么 $[j,r]$ 中的点可以选择是否与 $l$ 连边。就有如下的转移式。初始时 $f_{i,i}=0$。枚举 $j$ 直接转移就是 $O(n^3)$。

$$
f_{l,r}=\max_{j=l+1}^rf_{l,j-1}+f_{j,r}+\sum_{k=j}^r\max(w_{l,k},0)
$$

---

