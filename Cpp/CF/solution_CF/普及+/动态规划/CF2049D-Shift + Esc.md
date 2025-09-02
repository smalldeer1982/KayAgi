# Shift + Esc

## 题目描述

对于被某个装置捉弄之后，龙 Evirir 决定利用他的魔法技能来改变现实以迅速逃脱。

你得到一个 $n$ 行 $m$ 列的非负整数网格，以及一个整数 $k$。我们用 $(i, j)$ 表示从上到下第 $i$ 行、从左到右第 $j$ 列的单元格（$1 \le i \le n$，$1 \le j \le m$）。在每个单元格 $(i, j)$ 上都有一个整数 $a_{i, j}$。

你起始位于 $(1, 1)$，目标是走到 $(n, m)$。在移动过程中，你只能向下或向右移动——也就是说，如果你在 $(i, j)$，只能移动到 $(i+1, j)$ 或 $(i, j+1)$，当然，前提是这些目标单元格必须存在。

在开始移动之前，你可以进行以下操作任意多次：

- 从 $1$ 到 $n$ 中选择一个整数 $i$，然后将第 $i$ 行的元素循环左移一位。这个操作的效果是，将每个 $a_{i,j}$ 更新为 $a_{i,(j \bmod m) + 1}$。

请注意，一旦你开始移动，就不能再进行行移操作。从 $(1, 1)$ 到 $(n, m)$ 之后，令 $x$ 是你在开始移动之前进行的操作次数，而 $y$ 是你经过的所有单元格上的整数之和（包括起始和目标位置）。最终成本被定义为 $kx + y$。

你的任务是计算出以最小成本从 $(1, 1)$ 移动到 $(n, m)$ 所需的操作次数。

## 说明/提示

在第一个测试用例中，最低成本是 $113$，可以通过以下步骤实现：

1. 将第 3 行循环左移一次。网格变成：
   $$
   \begin{bmatrix}
   3 & 4 & 9 \\
   5 & 2 & 4 \\
   101 & 101 & 0
   \end{bmatrix}.
   $$
2. 按以下路径行进：$(1, 1) \to (1, 2) \to (2, 2) \to (2, 3) \to (3, 3)$。

进行了一次操作，访问的路径上整数之和为 $y = 3 + 4 + 2 + 4 + 0 = 13$。因此，总成本为 $kx + y = 100 \cdot 1 + 13 = 113$。

在第二个测试用例中，你可以将第 1 行左移一次，第 2 行左移两次，第 3 行左移三次。最终网格变成：
$$
\begin{bmatrix}
0 & 0 & 10 & 10 \\
10 & 0 & 0 & 0 \\
10 & 10 & 10 & 0
\end{bmatrix}.
$$

共进行了 $x = 6$ 次操作，并且经过的路径上整数之和为 $y = 0$。因此，总成本为 $6 \cdot 1 + 0 = 6$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
3 3 100
3 4 9
5 2 4
0 101 101
3 4 1
10 0 0 10
0 0 10 0
10 10 0 10
1 1 3
4
3 2 3
1 2
3 6
5 4
10 10 14
58 49 25 12 89 69 8 49 71 23
45 27 65 59 36 100 73 23 5 84
82 91 54 92 53 15 43 46 11 65
61 69 71 87 67 72 51 42 55 80
1 64 8 54 61 70 47 100 84 50
86 93 43 51 47 35 56 20 33 61
100 59 5 68 15 55 69 8 8 60
33 61 20 79 69 51 23 24 56 28
67 76 3 69 58 79 75 10 65 63
6 64 73 79 17 62 55 53 61 58```

### 输出

```
113
6
4
13
618```

# 题解

## 作者：Hanggoash (赞：4)

# CF2049D 题解

## 题意

给定一个 $n\times m$  的数字矩阵和常数 $K$，初始位于 $(1,1)$ 点，只能通过向下或者向右走来到达 $(n,m)$ 点。

存在某种操作，可以选择任意一行 ，将其所有列元素逆时针旋转 $1$ 个单位，这个操作可以对任意行进行任意次（下面称这个操作为“旋转”）。

设最后总操作次数为 $x$，经过的所有元素和为 $S$，最后的代价就是 $K\times x+ S$，求出这个代价可能的最小值。

**注意**：所有“旋转”操作需要在出发之前确定，或者等效来讲，不可以在某一行上移动时，对该行进行“旋转”操作。

## 分析

这个问题很明显可以 DP，并且有两个显然的观察：

1. 每一行的旋转与否、旋转的次数是彼此之间独立的。
2. 任意一行的旋转次数不会超过 $m-1$ 次，否则就是无用功。

那么就可以很自然的得到 DP 的定义：$dp[i][j][k],k\in[0,m-1]$ 为 到达 $(i,j)$ 点，当前行旋转了 $k$ 次的最小代价。

那么对于某个点 $(i,j)$，其只会从 $(i-1,j)$ 和 $(i,j-1)$ 转移。

从 $(i-1,j)$ 转移的时候，完全可以不用关心 $i-1$ 行旋转了多少次，正如上文 “1” 所说，行与行之间的旋转操作是独立的，我只需要知道到达 $(i-1,j)$ 这个点的最小代价即可。这一过程可以通过在 DP 过程中随手记录下最小值实现。

从 $(i,j-1)$ 转移的时候，$dp[i][j][k]$ 仅可从 $dp[i][j-1][k]$ 转移，这一点在 “注意” 中已经指出。

那么这样一来整个流程就明了了，唯一需要再额外注意的地方在于可能会有 int 溢出的情况。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k;
const int N=2e5+10;
typedef long long ll;
const ll INF=1e15+1;
ll a[300][300];
inline ll get(int i,int j,int add)
{
    int tmp=(j+add)%m;
    return tmp==0?a[i][m]:a[i][tmp];
}
inline void solve()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i) 
        for(int j=1;j<=m;++j)
            cin>>a[i][j];

    vector<vector<vector<ll>>> dp(n+1,vector<vector<ll>>(m+1,vector<ll>(m+1,INF)));
    vector<vector<ll>>mdp(n+1,vector<ll>(m+1,INF));
    mdp[0][1]=mdp[1][0]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            for(int x=0;x<=m-1;++x)
            {
                dp[i][j][x]=min(dp[i][j][x],mdp[i-1][j]+get(i,j,x)+1ll*x*k);//防止溢出
                dp[i][j][x]=min(dp[i][j][x],dp[i][j-1][x]+get(i,j,x));
                mdp[i][j]=min(mdp[i][j],dp[i][j][x]);
            }
        }
    }
    cout<<mdp[n][m]<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--)
    {
        solve();
    }
}
```

---

## 作者：ARIS2_0 (赞：4)

### 前言

赛时用 dijkstra 水过去的，我也是无敌了。

### 题目大意

给定 $n,m,k$ 与一个 $n\times m$ 的矩阵 $a$，定义格子 $(i,j)$ 的权值为 $a_{i,j}$。你要从 $(1,1)$ 走到 $(n,m)$。**开始移动之前**，你可以进行任意次操作，一次操作可将矩阵的任意一行**循环左移一格**。设你进行操作的次数为 $x$，从 $(1,1)$ 走到 $(n,m)$ 经过的格子权值和为 $y$，则总代价为 $kx+y$。求可能的最小的总代价。多测。

为了避免后文的变量名冲突，将原题中的 $k$ 称作 $p$。

### 思路

题面关于代价的描述等价于：

> 操作一次需要 $p$ 代价，走到格子 $(i,j)$ 上需要代价 $a_{i,j}$。

考虑一种非常暴力的建图：

设 $dist_{i,j,k}$  为走到格子 $(i,j)$，格子 $(i,j)$ 经过平移后**在第 $k$ 列**的最小代价。

则 $dist_{i,j,k}$ 可以向以下点建边：

- $dist_{i,j\bmod m+1,k+1}(k<m)$，代价为 $a_{i,j\bmod m+1}$。

- $dist_{i+1,u,k}(i<n,1\le u\le m)$，代价为 $(p\times(u+m-k)\bmod m)+a_{i+1,u}$。

初始状态为：$\forall j\in[1,m],dist_{1,j,1}=(p\times(j+m-1)\bmod m)+a_{1,j}$，其他为 $\inf$。

答案为：$\sum\limits_{j=1}^m \min(dist_{n,j,m})$。

但考虑到每个点都与其他点连了 $m$ 条边，总边数为 $nm^2$，复杂度即为 $O(nm^2\log(nm^2))$，会 TLE。

[TLE record](https://codeforces.com/contest/2049/submission/297521092)

考虑第 $i-1$ 行与第 $i$ 行有什么关联。

发现对于一个 $dist_{i,j,k}$，它与第 $i-1$ 行的关联**有且只有**$dist_{i,j,k}=\sum\limits_{u=1}^m \min(dist_{i-1,u,k}+(p\times(j+m-k)\bmod m))+a_{i,j}$。若 $dist_{i,j,k}$ 比这个式子的值更小，那么**能且只能**是从第 $i$ 行转移而来。

那么，我们完全不必将第 $i-1$ 行与第 $i$ 行之间进行建边，只需要将 $i-1$ 行的 $dist$ 处理出来后，对于 $\forall k\in[1,m]$，计算 $\sum\limits_{u=1}^m \min(dist_{i-1,u,k}+(p\times(j+m-k)\bmod m))$，记为 $mins_k$，再对于 $\forall j\in[1,m]$，使用 $dist_{i,j,k}=mins_k+a_{i,j}$ 进行更新，再对第 $i$ 行跑最短路即可。以此类推，直到计算出第 $n$ 行的 $dist$。

对于每一行，由于边有 $m^2$ 条，跑 dijkstra 的复杂度为 $O(m^2\log m^2)$，而转移的复杂度为 $O(m^2)$，则一行操作的复杂度近似于 $O(m^2\log m^2)$。而一共要操作 $n$ 行，则总复杂度即为 $O(nm^2\log m^2)$，可以通过本题 ~~，但是常数大的不得了~~。 

Update：写完题解才发现，这样建的图一定是 **DAG 图**，既然是 DAG 图直接 DP 转移就完事了，要什么最短路。果然赛时脑子还是进水了。

### 实现细节

为了减小常数，可以不用建图，而是在 dijkstra 转移的时候再确定终点。

### AC Code

赛时代码，很丑，见谅。

最大点 1546ms，常数拉满了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int inf=1e16,maxn=210;
int a[maxn][maxn];
struct node{
	int x,y,k,val;
};
bool operator < (node a,node b){
	return a.val>b.val;
}
priority_queue<node>q;
int n,m,cost;
int dist[maxn][maxn][maxn],mins[maxn];
bool b[maxn][maxn][maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n>>m>>cost;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				for(int k=1;k<=m;k++){
					dist[i][j][k]=inf;
					b[i][j][k]=0;
				}
				
			}
		}
		while(q.size())q.pop();
		for(int i=1;i<=m;i++)dist[1][i][1]=(i-1)*cost+a[1][i],q.push(node{1,i,1,dist[1][i][1]});
		for(int id=1;id<=n;id++){
			if(id!=1){
				for(int k=1;k<=m;k++)mins[k]=inf;
				for(int k=1;k<=m;k++){
					for(int j=1;j<=m;j++){
						mins[k]=min(mins[k],dist[id-1][j][k]);
					}
					//cout<<mins[k]<<" ";
				}
				//cout<<"\n";
				for(int j=1;j<=m;j++){
					for(int k=1;k<=m;k++){
						dist[id][j][k]=mins[k]+a[id][j]+cost*((j+m-k)%m);
						q.push(node{id,j,k,dist[id][j][k]});
					}
				}
			}
			while(q.size()){
				int x=q.top().x,y=q.top().y,k=q.top().k;
				q.pop();
	//			if(x==2 and y==1 and k==3)cout<<"sgsgsedg\n";
				if(b[x][y][k])continue;
				b[x][y][k]=1;
	//			if(x==2 and y==1 and k==3)cout<<"sgsgsedg\n";
				if(k!=m){
	//				if(x==2 and y==1 and k==3)cout<<"sgsgsedg\n";
					if(!b[x][y%m+1][k+1] and dist[x][y%m+1][k+1]>dist[x][y][k]+a[x][y%m+1]){
						dist[x][y%m+1][k+1]=dist[x][y][k]+a[x][y%m+1];
						q.push(node{x,y%m+1,k+1,dist[x][y%m+1][k+1]});
					}
				}
			}
		}
		int ans=inf;
		for(int i=1;i<=m;i++)ans=min(ans,dist[n][i][m]);
		cout<<ans<<"\n";
		//cout<<dist[3][3][4];
	}
	return 0;
}
/*
1
3 4 1
10 0 0 10
0 0 10 0
10 10 0 10
200*200+200*200*200
*/
```

---

## 作者：Eddie08012025 (赞：2)

## 普通思路
显然，这题可以使用 dp 来做，定义 $dp_{i,j,kk}$ 为以该点为终点，第 $i$ 行做循环操作 $kk$ 次的最小成本，$m=kk$ 时会回到原状态，所以 $kk<m$ 才能更优。

定义 $te$ 为循环 $kk$ 次后点 $(i,j)$ 对应的值在 $a_i$ 中的实际下标。一般的，$te=j+kk$，但考虑到 $j+kk$ 可能大于 $m$，因此 $te=(j+kk-1)\%m+1$ 可以考虑到两种情况。 

$i=1,j=1$ 时，不用转移，易得：
$$dp_{i,j}=kk\times k+a_{i,te}$$

考虑 $(i,j)$ 从左向右转移，因为 $dp_{i,1,kk}$ 已经加上了循环的花费，因此不用再加一次循环花费，当 $j=1$ 时，左边没有可转移的方程。当 $j\ne 1$ 时，易得:

$$dp_{i,j,kk}=dp_{i,j-1,kk}+a_{i,te}$$

考虑从上往下转移，$dp_{i,j,kk}$ 一定由 $dp_{i-1,j}$ 转移而来，而第 $i-1$ 行循环操作次数不定，再加上循环操作花费与经过花费，当 $i=1$ 时，上面没有可转移的方程。当 $i\ne 1$ 时：
$$dp_{i,j,kk}=\min_{o=0}^{o<m}dp_{i-1,j,o}+a_{i,te}+kk\times k$$

答案是 $\min_{o=0}^{o\le m} dp_{n,m,o}$。

这种做法是 $O(nm^3)$ 的，面临着 TLE 的风险，考虑优化。

## 优化
可以优化枚举 $o$ 的过程。

提前处理 $\min_{o=1}^{o<m}dp_{i-1,j,o}$ 的值即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char buf[1 << 20], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20,stdin),p1 == p2) ? EOF : *p1++)
inline int rd() {
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x*f;
}char obuf[1 << 20], *p3 = obuf;
#define putchar(x) (p3 - obuf < 1 << 20) ? (*p3++ = x) : (fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3++ = x)
inline void write(long long x) {
    if(!x){
        putchar('0');
        return;
    }long long len=0,k1=x,c[40];
	if(k1<0)k1=-k1,putchar('-');
	while(k1)c[len++]=k1%10^48,k1/=10;
	while(len--)putchar(c[len]);
}int t,n,m,k,z[301][301],dp[301][301][301],maxn[301][301];
signed main(){
	t=rd();
	while(t--){
		n=rd();
		m=rd();
		k=rd();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				z[i][j]=rd();
				for(int kk=0;kk<m;kk++)dp[i][j][kk]=4e18;
				maxn[i][j]=4e18;
			}
		}int ans=4e18;
		dp[1][1][0]=z[1][1];
		maxn[1][1]=z[1][1];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int kk=0;kk<m;kk++){
					int te=(j+kk-1)%m+1;
					if(j==1&&i==1){
						dp[i][j][kk]=kk*k+z[i][te];
					}if(j!=1){
						dp[i][j][kk]=dp[i][j-1][kk]+z[i][te];
					}if(i!=1){
						dp[i][j][kk]=min(dp[i][j][kk],maxn[i-1][j]+z[i][te]+kk*k);
					}if(i==n&&m==j)ans=min(ans,dp[i][j][kk]);
					maxn[i][j]=min(maxn[i][j],dp[i][j][kk]);//处理dp[i][j][kk]的最小值
				}
			}
		}write(ans);
		putchar(10);
	}fwrite(obuf, p3 - obuf, 1, stdout);
	p3 = obuf;
	return 0;
}
```

---

## 作者：hgcnxn (赞：2)

## CF2049D Shift + Esc题解

### 题目大意

给定一个 $n$ 行 $m$ 列的网格，第 $i$ 行第 $j$ 列的格子的权值为 $a_{i,j}$。你可以进行以下操作任意次：

- 选择一行，将该行的每一格向左移动一格，最左边的一格移到最右边。

在所有操作结束后，你要从 $(1,1)$ 移动到 $(n,m)$。如果你当前在 $(i,j)$，那你只能移动到 $(i,j+1)$ 或 $(i+1,j)$。如果你操作了 $x$ 次，经过的所有格子的权值之和为 $y$，那么你的花费为 $kx+y$。最小化你的花费并输出这个值。

### 思路

为避免混淆，将上文的 $k$ 改为 $w$。

如果去掉操作这个条件，那么这就是一个非常普通的动态规划题目。所以，我们考虑在此基础上增设状态，达到此题的目的。

设 $dp_{i,j,k}$ 为到达 $(i,j)$ 且在第 $j$ 行操作了 $k$ 次的最小花费，$f_{i,j}$ 为到达 $(i,j)$ 的最小花费。

我们题目条件改变一下，使题意不变但方便我们实现：我们初始时在 $(0,1)$。我们可以在移动过程中操作，但只能对下一行操作，且在对下一行操作若干次后必须向下移动。

对于 $(i,j)$，他可以由 $(i-1,j)$ 或 $(i,j-1)$ 走到。如果他是从 $(i-1,j)$ 走到，并且第 $j$ 行被操作了 $k$ 次，那么 $f_{i-1,j}+kw+a_{i,((j+k-1)\bmod m)+1}$ 为到达 $(i,j)$ 的所需的花费；如果从 $(i,j-1)$ 走过来，那么我们就不用考虑操作所带来的花费了，那么 $dp_{i,j-1,k}+a_{i,((j+k-1)\bmod m)+1}$ 即为此时的花费。

那么我们就有
$$dp_{i,j,k}=\min(f_{i-1,j}+kw,dp_{i,j-1,k})+a_{i,((j+k-1)\bmod m)+1}$$

在转移 $dp_{i,j,k}$ 的同时，我们将 $f_{i,j}$ 也进行更新。由于对同一行操作 $m$ 次和不操作等价，所以每一行的操作次数小于 $m$。此时，该算法在单词询问中的时间复杂度为 $O(nm^2)$，总时间复杂度为 $O(\sum(nm^2))<200^3=8\times 10^6$，不会超时。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,w,a[205][205];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>w;
		int dp[n+1][m+1][m+1],f[n+1][m+1];
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
		memset(dp,0,sizeof(dp));
		memset(f,0,sizeof(f));
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				f[i][j]=1e18;
				for(int k=0;k<=m;k++)dp[i][j][k]=1e18;
			}
		}
		f[0][1]=0;
		//初始化 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int k=0;k<m;k++){
					dp[i][j][k]=min(f[i-1][j]+w*k,dp[i][j-1][k])+a[i][(j+k-1)%m+1];
					f[i][j]=min(f[i][j],dp[i][j][k]);
				}
			}
		}
		cout<<f[n][m]<<"\n";
	}
	return 0;
}
```

---

## 作者：Ambrose0321 (赞：1)

一明显的 dp 题。


思路：
---

就像前面说的，这道题就是一道用 dp 解决的题。后面为了避免混淆，题目中的 $k$ 用 $w$ 表示。

**状态：**

用 $f_{i,j,k}$ 表示第 $i$ 行 $j$ 列移动了 $k$ 次的最小成本，$g_{i,j}$ 表示第 $i$ 行 $j$ 列的格子的最小成本，我们把移动 $k$ 次后的格子叫做 $a_{i,x}$，那我们就有转移式：

$$f_{i,j,k}=\min(f_{i,j-1,k}+a_{i,x},g_{i-1,j}+a_{i,x})$$

复杂度 $O(nm^2)$，不会超时。


AC code:
---

别忘了更新 $g$ 数组。
```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
int _, n, m, w, a[201][201];
ll g[201][201], f[201][201][201];
int main() {
	scanf("%d", &_);
	for (; _--; ) {
		scanf("%d%d%d", &n, &m, &w);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &a[i][j]);
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++) {
				g[i][j] = 9e18;
				for (int k = 0; k < m; k++)
					f[i][j][k] = 9e18;
			}
		g[0][1] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				for (int k = 0; k < m; k++) {
					int x = (j + k) % m;
					if (!x)
						x = m;
					g[i][j] = min(g[i][j], f[i][j][k] = min(g[i - 1][j] + 1LL * w * k, f[i][j - 1][k]) + a[i][x]);
				}
		printf("%lld\n", g[n][m]);
	}
}
```
求过审 qwq。

---

## 作者：MrPython (赞：1)

以下内容从 $0$ 开始标号。

一股浓烈的 ABC 味扑面而来。类似最小化 $kx+y$ 的形式已经在 ABC 的 F 题中欧出现好多次了。

我们不关心最终答案里具体进行了多少次旋转操作，状态仅需设置 $f_{i,j}$ 表示当前位于第 $i$ 行第 $j$ 列的最小代价。

我们以行为单位进行转移。对于单独的一行，我们需要考虑进行多少次旋转操作。因此，可以设 $g_{i,j,t}$ 表示当前位于第 $i$ 行第 $j$ 列，第 $i$ 行进行了 $k$ 次旋转操作。

转移时，我们可以选择从上方过来，也可以选择从左侧过来。对第 $i$ 列进行 $t$ 次旋转后，格子 $(i,j)$ 上的数变成了 $(i,(j+t\bmod m))$，同时会导致代价增加 $t\times k$。于是我们有转移方程：
$$
g_{i,j,k}=\min(g_{i,j-1,k},f_{i,j}+k\times t)+a_{i,(j+t)\bmod m}
$$

完成一整行后，我们接着更新该行的 $f$。显然每列的答案为所有位移方案中该列的最小者。
$$
f_{i,j}=\min_{t=0}^{m-1} f_{i,j,t}
$$

时间复杂度 $O(nm^2)$。

```cpp
#include <cstddef>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    size_t n, m;
    ui k;
    fin >> n >> m >> k;
    vector<uli> f(m, numeric_limits<uli>::max() / 2);
    f[0] = 0;
    for (size_t c = 0; c < n; ++c) {
      vector<uli> a(m);
      for (uli& i : a) fin >> i;
      vector g(m, vector<uli>(m));
      for (size_t t = 0; t < m; ++t) {
        g[t][0] = f[0] + (uli)k * t + a[(t + 0) % m];
        for (size_t i = 1; i < m; ++i)
          g[t][i] = min(g[t][i - 1], f[i] + (uli)k * t) + a[(t + i) % m];
      }
      f = vector<uli>(m, numeric_limits<uli>::max() / 2);
      for (auto const& i : g)
        for (size_t j = 0; j < m; ++j) f[j] = min(f[j], i[j]);
    }
    fout << f.back() << '\n';
  }
  return 0;
}
```

---

## 作者：Toorean (赞：1)

题意：给出 $n\times m$ 的矩阵 $A$ 以及 $Q$。可以任意选中任意一行向左**循环移动**任意个单位，设移动一个单位为一次操作，共进行 $x$ 次操作。从 $(1,1)$ 到 $(n,m)$，每次可向下或向右走，$y$ 为所有经过的 $(i,j)$ 的权值之和。最小化 $Q\cdot x+y$。

分析：显然，一行最多操作 $m-1$ 次，因为循环操作呈周期性，操作超过 $m-1$ 次会与更少的操作重复，答案不是最优。故考虑 dp，设 $f(i,j,k)$ 表示第 $i$ 行操作了 $k$ 次，从 $(1,1)$ 走到 $(i,j)$ 的最优解。

若当前从第 $i-1$ 行走到第 $i$ 行，则 $f(i,j,k)=\min\limits_{l=0}^{m-1}\{f(i-1,j,l)+{\mathrm {val}}(i,j,k)+k\times Q\}$。其中 $\mathrm{val}(i,j,k)$ 表示第 $i$ 行循环操作 $k$ 次后，$(i,j)$ 的权值。

若当前从同一行的上一列走来，则 $f(i,j,k)=f(i,j-1,k)+\mathrm {val}(i,j,k)$。由于题设中必须在走前操作，故只可从同一个操作次数状态转移，故也无需额外添加 $Q\times k$。

综上，有 $f(i,j,k)=\min\begin{cases}\min\limits_{l=0}^{m-1}\{f(i-1,j,l)+{\mathrm {val}}(i,j,k)+k\times Q\}，& i\not=1 \\ f(i,j-1,k)+\mathrm {val}(i,j,k) & j\not=1\end{cases}$。

其中，$f(1,1,k)=\mathrm{val}(1,1,k)+k\times Q$。

时间复杂度 $\mathcal O(nm^3)$，略带卡常，能过。


Code:
```cpp
for (int i = 0; i <= n; i ++)
    for (int j = 0; j <= m; j ++)
        for (int l = 0; l <= m; l ++)
            f[i][j][l] = INF;
for (int j = 0; j <= m; j ++)  f[1][1][j] = cacl (1, 1, j) + j * kk;

for (int i = 1; i <= n; i ++) {
    for (int j = 1; j <= m; j ++) {
        if (i == 1 && j == 1) continue; 
        for (int k = 0; k <= m; k ++) {
            if (j != 1) 
                f[i][j][k] = min (f[i][j][k], f[i][j - 1][k] + cacl (i, j, k) );
            if (i != 1) for (int l = 0; l <= m; l ++) 
                f[i][j][k] = min (f[i][j][k], f[i - 1][j][l] + cacl (i, j, k) + kk * k);
        }   
    }
}
ll ans = INF;
for (int i = 0; i <= m; i ++) ans = min (ans, f[n][m][i]);
```

---

## 作者：OIer_Hhy (赞：0)

看到数据范围可知复杂度为 $O(n^3)$。

尝试暴力 DP。

令 $dp_{i,j,cnt}$ 表示走到 $a_{i,j}$ 时 shift 了第 $i$ 行 $cnt$ 次时最小代价。

初始：$dp_{1,1,cnt}=a_{i,(j+cnt) \bmod m}+cnt \times k$。

转移：

- 从 $(i-1,j)$ 转移过来：这一行 shift 次数得重新算。$dp_{i,j,cnt}=dp_{i-1,j,cnt'(0 \le cnt' < m)}+a_{i,(j+cnt) \bmod m} + cnt \times k$。
- 从 $(i,j-1)$ 转移过来：由于一行中 shift 次数相同，因此不需要加上 shift 的代价。$dp_{i,j,cnt}=dp_{i,j-1,cnt}+a_{i,(j+cnt) \bmod m}$。

时间复杂度：$O(n^4)$，如何优化？

令 $g_{i,j}= \min \{dp_{i,j,cnt(0 \le cnt <m)}\}$，则第一种转移可重写成 $dp_{i,j,cnt}=g_{i,j}+a_{i,(j+cnt) \bmod m} + cnt \times k$，时间复杂度降低为 $O(n^3)$，足以通过此题。


```cpp
#include<bits/stdc++.h>
#define int long long
//#define I_love_wxq_4ever
using namespace std;
const int N=2e2+10;
int n,m,k,a[N][N],f[N][N][N],g[N][N];
void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			g[i][j]=1e18;
			for(int cnt=0;cnt<m;cnt++) f[i][j][cnt]=1e18;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int cnt=0;cnt<m;cnt++){
				int j_=(j+cnt)%m;
				if(j_==0) j_=m;
				if(i==1&&j==1) f[i][j][cnt]=min(f[i][j][cnt],a[i][j_]+cnt*k);
				if(i>1) f[i][j][cnt]=min(f[i][j][cnt],g[i-1][j]+a[i][j_]+cnt*k);
				if(j>1) f[i][j][cnt]=min(f[i][j][cnt],f[i][j-1][cnt]+a[i][j_]);
				g[i][j]=min(g[i][j],f[i][j][cnt]);
				#ifdef I_love_wxq_4ever
				cout<<i<<" "<<j<<' '<<cnt<<" "<<f[i][j][cnt]<<"\n";
				#endif
			}
		}
	}
	int ans=1e18;
	#ifdef I_love_wxq_4ever
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int res=1e18;
			for(int cnt=0;cnt<m;cnt++)
				res=min(res,f[i][j][cnt]);
			cout<<res<<' ';
		}
		cout<<'\n';
	}
	#endif
	for(int i=0;i<m;i++) ans=min(ans,f[n][m][i]);
	cout<<ans<<'\n';
}
signed main(){
	#ifndef I_love_wxq_4ever
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	#endif
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}

```

---

## 作者：wfc284 (赞：0)

定义 $f_{i,j}$ 为走到第 $(i,j)$ 的最小代价，包括 operation 带来的。  
我们可以暴力枚举每一行 operate 了多少次，记为 $k$，并真的去操作。将 operate 了 $k$ 次的第 $i$ 行数组记为 $v^{i, k}$。  
于是就有：
$$ f_{i,j}=\min_{k=0}^{m-1} \{\min(f_{i,j-1}, f_{i-1, j}) + v^k[j]\} $$
做完了，时间复杂度 $O(nm^2)$。
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define int long long
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 202;
	
	int n, m, k, a[N][N];
	int f[N], g[N], h[N];
	
	void roll(int *a) {
		for(int i = 0; i < m; ++i) a[i] = a[i+1];
		a[m] = a[0];
	}
	
	void main() {
		cin >> n >> m >> k;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				scanf("%lld", &a[i][j]);
		
		memset(f, 0x3f, sizeof(f));
		f[1] = 0;
		for(int i = 1; i <= n; ++i) {
			memcpy(g, f, sizeof(g));
			memset(f, 0x3f, sizeof(f));
			for(int x = 0; x < m; ++x) {
				memset(h, 0x3f, sizeof(h));
				for(int j = 1; j <= m; ++j)
					h[j] = min(h[j-1], g[j]) + a[i][j];
				for(int j = 1; j <= m; ++j)
					f[j] = min(f[j], h[j] + x*k);
				roll(a[i]);
			}
		}
		cout << f[m] << '\n';
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}


```#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define int long long
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 202;
	
	int n, m, k, a[N][N];
	int f[N], g[N], h[N];
	
	void roll(int *a) {
		for(int i = 0; i < m; ++i) a[i] = a[i+1];
		a[m] = a[0];
	}
	
	void main() {
		cin >> n >> m >> k;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				scanf("%lld", &a[i][j]);
		
		memset(f, 0x3f, sizeof(f));
		f[1] = 0;
		for(int i = 1; i <= n; ++i) {
			memcpy(g, f, sizeof(g));
			memset(f, 0x3f, sizeof(f));
			for(int x = 0; x < m; ++x) {
				memset(h, 0x3f, sizeof(h));
				for(int j = 1; j <= m; ++j)
					h[j] = min(h[j-1], g[j]) + a[i][j];
				for(int j = 1; j <= m; ++j)
					f[j] = min(f[j], h[j] + x*k);
				roll(a[i]);
			}
		}
		cout << f[m] << '\n';
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}

---

## 作者：postpone (赞：0)

又要走又要操作，看上去很复杂，可以尝试先看看弱化版的问题。

如果没有魔法移动，就是非常简单的一个转移：一个位置，可以来自上面，也可以来自左边，那么把这俩拿过来比较一下就行了。

回看该问题，和简化版的相同之处在于，在左右的转移中，不用考虑魔法移动——因为在行动之前就要完成操作。不同之处在于上下是会受到魔法移动的影响的。

设 $g_{i, j, x}$ 表示走到 $(i, j)$，**第 $i$ 行操作 $x$ 次**的最优，$f_{i, j}$ 表示走到 $(i, j)$ 的最优。

以下的说明中，为了简洁，将 $(j+x) \bmod m$ 简写为 $j+x$。

分别来看，每个格子 $(i, j)$，从左到右的转移中，对每个魔法移动的情况，记 $A_{x} \leftarrow \min \left\{g_{i, j - 1, x} + a_{i, j + x}\right\}$。

而在从上到下的转移中，由于对这行操作的次数与最后的位置是对应的，记 $B_{x} \leftarrow \min\left\{f_{i - 1, j} + a_{i, j + x}\right\}$。

那么 $g_{i, j, x} \leftarrow \min \left(A_x, B_x\right)$，更新完所有 $x$ 后，再有 $f_{i, j} = \min \left\{g_{i, j, x}\right\}$。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll inf = 1e18;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    vector dp(n + 1, vector(m, inf));
    vector g(n + 1, vector(m, vector(m, inf)));

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = 0; x < m; x++) {
                g[i][j][x] = min(g[i][j][x],
                                 dp[i - 1][j] + 1ll * k * x + a[i - 1][(j + x) % m]);
            }
            for (int x = 0; x < m and j; x++) {
                g[i][j][x] = min(g[i][j][x],
                                 g[i][j - 1][x] + a[i - 1][(j + x) % m]);
            }
            for (int x = 0; x < m; x++) {
                dp[i][j] = min(dp[i][j], g[i][j][x]);
            }
        }
    }

    cout << dp[n][m - 1] << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    for (cin >> T; T--;) {
        solve();
    }

    return 0;
}
```

---

## 作者：Louis_lxy (赞：0)

定义 $f(i,j,k)$ 表示走到 $(i,j)$，第 $i$ 行执行 $k$ 次操作的最小代价，于是有：

$f(i,j,k)=\min((\min_{l=0}^{m-1}f(i-1,j,l))+k\times dis+a(i,(j+k-1)\bmod m+1),f(i,j-1,k) + a(i,(j+k-1)\bmod m+1))$。

然后弄个数组存 $\min_{l=0}^{m-1}f(i-1,j,l)$ 就好了，复杂度 $O(nm^2)$。

---

## 作者：Austin0116 (赞：0)

# 分析

求最小成本，决策性问题。贪心不好做，考虑 DP。

先设计状态，很容易设出状态 $f[i][j][k]$ 表示走到第 $i$ 行第 $j$ 列 向左循环移动 $k$ 格的最小代价。直接暴力从上边的最小值和左边转移答案，时间复杂度为 $O(n^4)$。

考虑优化，由于上边的最小值可以在算完后处理，直接转移，所以可以设 $mn[i][j]$ 表示走到第 $i$ 行第 $j$ 列的最小代价，最后答案就为 $mn[n][m]$。时间复杂度 $O(n^3)$。

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
long long f[305][305][305],mn[305][305];
int n,m,k,a[305][305],t;
char ch;
inline void read(int &x){
	x=0;
	while(ch<48||ch>57) ch=getchar();
	while(ch>=48&&ch<=57){
		x=x*10+(ch^48);
		ch=getchar(); 
	}
}
void write(long long x){
	if(x>9) write(x/10);
	putchar((x%10)^48);
}
int main(){
	read(t);
	while(t--){
		read(n);read(m);read(k);
		for(int i=0;i<=n;i++) for(int j=0;j<=m;j++){//初始化 
			mn[i][j]=2e18;
			for(int k=0;k<=m;k++) f[i][j][k]=2e18;
		} 
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) read(a[i][j]);
		for(int i=0;i<m;i++){//预处理(1,1) 
			f[1][1][i]=a[1][(1+i==m)?m:((1+i)%m)]+1ll*k*i;
			mn[1][1]=min(mn[1][1],f[1][1][i]);
		} 
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(!(i==1&&j==1)) for(int l=0;l<m;l++){
			f[i][j][l]=min(f[i][j-1][l]+a[i][(j+l==m)?m:((j+l)%m)],mn[i-1][j]+a[i][(j+l==m)?m:((j+l)%m)]+1ll*k*l);//从左边和下边转移答案 
			mn[i][j]=min(mn[i][j],f[i][j][l]);//处理最小值 
		}
		write(mn[n][m]);putchar('\n');//答案 
	}
	return 0;
}
```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF2049D)

## 前言

第一次赛时过 D，助我一场上蓝！

## 思路

显然考虑 dp。

令 $dp_{i,k,j}$ 为第 $i$ 行第 $j$ 个**格子**在第 $i$ 行右移 $k$ 次后的最小代价，$f_{i,j}$ 为第 $i$ 行第 $j$ 个**格子**的最小代价。

显然 $dp_{i,k,j}$ 只能从上一行的 $f_{i-1,j}$ 和 $dp_{i,k,j-1}$ 转移来。$f_{i-1,j}$ 很好理解，因为各行的右移是独立的。又因为一次右移是对于整行来说的，所以只能从 $dp_{i,k,j-1}$ 转移来。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using DB = double;

const int kMaxN = 2e2 + 5;

LL t, n, m, K, a[kMaxN][kMaxN << 1], ans = 1e18, f[kMaxN][kMaxN], dp[kMaxN][kMaxN][kMaxN];

void pr(bool pr) { cout << (pr ? "YES" : "NO") << '\n'; }

int main() {
  for (cin >> t; t; t--, ans = 1e18) {
    cin >> n >> m >> K;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j], a[i][j + m] = a[i][j];
      }
    }
    fill(f[0], f[n + 2], 1e18);
    for (int i = 0; i <= n + 1; i++) {
      for (int j = 0; j <= m + 1; j++) {
        for (int k = 0; k <= m + 1; k++) {
          dp[i][j][k] = 0;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 1; k <= m; k++) {
          dp[i][j][k] = 1e18;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < m; j++) {
        for (int k = 0; k < m; k++) {
          dp[i][j][1] = min(dp[i][j][1], dp[i - 1][k][1] + a[i][j + 1] + K * j);
        }
        for (int k = 2; k <= m; k++) {
          dp[i][j][k] = min({dp[i][j][k], f[i - 1][k] + a[i][j + k] + K * j, dp[i][j][k - 1] + a[i][j + k]});
        }
      }
      for (int j = 1; j <= m; j++) {
        for (int k = 0; k < m; k++) {
          f[i][j] = min(f[i][j], dp[i][k][j]);
        }
      }
    }
    cout << f[n][m] << '\n';
  }
  return 0;
}
```

---

