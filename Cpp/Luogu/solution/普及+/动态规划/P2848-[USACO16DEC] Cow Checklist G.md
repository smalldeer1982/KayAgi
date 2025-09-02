# [USACO16DEC] Cow Checklist G

## 题目描述

每天，Farmer John 都会穿过他的牧场，检查每头奶牛的健康状况。他的农场里有两类奶牛：荷斯坦牛和根西牛。他的 $H$ 头荷斯坦牛被方便地编号为 $1 \ldots H$，而他的 $G$ 头根西牛被方便地编号为 $1 \ldots G$（$1 \leq H \leq 1000, 1 \leq G \leq 1000$）。每头奶牛都位于二维平面中的一个点（不一定不同）。

Farmer John 从荷斯坦牛 1 开始他的巡视，并在荷斯坦牛 $H$ 结束。他希望沿途访问每头奶牛，并且为了方便维护他已经访问过的奶牛清单，他希望按照编号顺序访问荷斯坦牛和根西牛。在他访问的所有 $H+G$ 头奶牛的序列中，编号为 $1 \ldots H$ 的荷斯坦牛应作为一个（不一定连续的）子序列出现，同样地，编号为 $1 \ldots G$ 的根西牛也应如此。换句话说，所有 $H+G$ 头奶牛的序列应通过将编号为 $1 \ldots H$ 的荷斯坦牛列表与编号为 $1 \ldots G$ 的根西牛列表交错排列而成。

当 Farmer John 从一头奶牛移动到另一头奶牛，移动距离为 $D$ 时，他会消耗 $D^2$ 的能量。请帮助他确定按照上述巡视方式访问所有奶牛所需的最小能量。

## 样例 #1

### 输入

```
3 2
0 0
1 0
2 0
0 3
1 3```

### 输出

```
20```

# 题解

## 作者：kara20 (赞：17)

# 思路：

很明显这是一道 DP，首先我们先来分析一下这道题：
### 题目让我做什么：
---
穷举所有行走路线。


#### 以什么为对象划分顺序，分几步完成，每一步做什么（决策）：
---
以步数划分顺序，分成 $H+G$ 步，决策是在 $H$ 序列走一步还是在 $G$ 序列走一步。

#### 状态是什么，状态就是整个问题的描述：
---
这里不需要时间，因为时间一定等于 $i+j$（因为每一时刻肯定有一个人走一步），所以此时的状态就是 $f_{i,j}$,但是还有一个问题，就是如果这么写就没法算最后一步的花费。

现在的方程 $f_{i,j}$表示 $H$ 序列走到了 $i$，$G$ 序列走到了 $j$，此时我们最后一次访问（走到）的是 $H$ 序列还是 $G$ 序列我们不知道，所以就不能求最后一步的花费。

可以考虑往状态里增加一维，就是 $f_{i,j,0}$ 和 $f_{i,j,1}$。

- $f_{i,j,0}$ 表示 $H$ 序列的前 $i$ 个（访问）走完了，$G$ 序列的前 $j$ 个走完了，最后我们位于 $H$ 序列的最后一个位置。

- $f_{i,j,1}$ 就是最后我们位于 $G$ 序列的最后一个位置（前面一样后面改一下）。

#### 状态转移方程：
---
我们来想一下最后的方程，有了方程就很好写代码啦，我觉得方程就是去掉最后一步的状态+最后一步的状态（大多数啊），想一想这两个状态上一步是由谁推出来的，先来看 $f_{i,j,0}$ 的方程,因为我们这里省略了一个 $x$ 时刻（若 $x=i+j$，则 $x$ 时刻状态为 $f_{i,j,0}$），那么我们想 $x-1$ 时刻状态是什么，是 $f_{i-1,j,0}$ 和 $f_{i-1,j,1}$（一个时刻只能走一步哦）然后再找到最后一步的状态，这两个方程的最后一步状态会用到 $dis$ 数组（感觉用这个会直观一点，当然你也可以用函数），$f_{i,j,1}$ 去掉最后一步的状态是：$f_{i,j-1,0}$ 和 $f_{i,j-1,1}$。

### 小知识：

ok，现在就差两个方程的最后一步状态了，我们需要知道一个原理，运用勾股定理可知：在平面直角坐标系中两个点的距离的平方 $=$ 两个点横坐标差的平方 $+$ 两个点纵坐标差的平方，所以这里我定义了 $3$ 个 $dis$ 数组，如下：

- $dis1$：$dis1$ 表示在 $H$ 序列里第 $i$ 个点和第 $i+1$ 个点距离的平方（也就是消耗的能量）。

```cpp
dis1[i]=pow(H[i].x-H[i+1].x,2)+pow(H[i].y-H[i+1].y,2);
```

- $dis2$：$dis2$ 表示在 $H$ 序列里第 $i$ 个点和 $G$ 序列的第 $j$ 个点距离的平方（也就是消耗的能量）。

```cpp
dis2[i][j]=pow(H[i].x-G[j].x,2)+pow(H[i].y-G[j].y,2);
```

- $dis3$：$dis3$ 表示在 $G$ 序列里第 $i$ 个点和第 $i+1$ 个点距离的平方（也就是消耗的能量）。

```cpp
dis3[i]=pow(G[i].x-G[i+1].x,2)+pow(G[i].y-G[i+1].y,2);
```

现在我觉得方程你就能看懂啦ヾ(❀^ω^)ノﾞ。

```cpp
f[i][j][0]=min(f[i][j][0],min(f[i-1][j][0]+dis1[i-1],f[i-1][j][1]+dis2[i][j]));

f[i][j][1]=min(f[i][j][1],min(f[i][j-1][1]+dis3[j-1],f[i][j-1][0]+dis2[i][j]));
```

# Code：

```cpp
#include<bits/stdc++.h>//可爱的懒人头文件
using namespace std;
int n,m;
long long f[1009][1009][2],dis1[1009],dis3[1009],dis2[1009][1009];
struct node
{
    int x,y;
}H[1009],G[1009];//写一个结构体
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>H[i].x>>H[i].y;//读入H第i个点的坐标
    }
    for(int i=1;i<=m;i++)
    {
        cin>>G[i].x>>G[i].y;//读入G第i个点的坐标
    }
    for(int i=1;i<n;i++)
    {
        dis1[i]=pow(H[i].x-H[i+1].x,2)+pow(H[i].y-H[i+1].y,2);
    }
    for(int i=1;i<m;i++)
    {
        dis3[i]=pow(G[i].x-G[i+1].x,2)+pow(G[i].y-G[i+1].y,2);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            dis2[i][j]=pow(H[i].x-G[j].x,2)+pow(H[i].y-G[j].y,2);

        }
    }
    memset(f,0x7f,sizeof(f));//初始化无穷大
    f[1][0][0]=0;//从题目可以看出农夫约翰最开始位于H序列的第一个点，所以第一维数组就是1，G序列一个点也没走所以第二维就是0，题目说农夫约翰在H结束所以第三维就是0
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            f[i][j][0]=min(f[i][j][0],min(f[i-1][j][0]+dis1[i-1],f[i-1][j][1]+dis2[i][j]));
            if(j>0)f[i][j][1]=min(f[i][j][1],min(f[i][j-1][1]+dis3[j-1],f[i][j-1][0]+dis2[i][j]));//DP方程
        }
    }
    cout<<f[n][m][0];
    return 0;
}
```


---

## 作者：IceFox (赞：12)

简单的DP,用dp[i][j][2]表示，dp[i][j]表示第一组匹配到了第i个，第二组匹配到了第j个，


[0]表示停在第一组，[1]表示停在第二组；转移方程详见代码

```cpp
#include <cstdio>
#include <cstring>
#define ll long long 
#define inf 2000000000
int const N=1000+5;
struct node{
    int x,y;
}a[N<<1];
int n,m,d[N<<1][N<<1];
ll dp[N][N][2];
ll min(ll x,ll y){return x<y?x:y;}
int main(){
//    freopen("a.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n+m;++i) scanf("%d%d",&a[i].x,&a[i].y);
    for(int i=1;i<=n+m;++i)
        for(int j=i+1;j<=n+m;++j)
            d[i][j]=(a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y);
    for(int i=0;i<=n;++i)
        for(int j=0;j<=m;++j)
            for(int k=0;k<=1;++k)
                dp[i][j][k]=inf;
    dp[1][0][0]=0;
    for(int i=1;i<=n;++i)
        for(int j=0;j<=m;++j){
            dp[i][j][0]=min(dp[i][j][0],min(dp[i-1][j][0]+d[i-1][i],dp[i-1][j][1]+d[i][n+j]));
            if(j) dp[i][j][1]=min(dp[i][j][1],min(dp[i][j-1][0]+d[i][n+j],dp[i][j-1][1]+d[n+j-1][n+j]));
        }    
    printf("%lld",dp[n][m][0]);
    return 0;
}
```

---

## 作者：lnwhl (赞：2)

## Solution
考虑 dp，状态 $f_{i,j,0/1}$ 表示 $H$ 牛取到了第 $i$ 个，$G$ 牛取到了第$j$ 个，$0/1$ 表示这一步取 $H$ 牛还是 $G$ 牛，$f$ 内存的是最小的代价。

设 $\operatorname{dis}(i,j)$ 表示从第 $i$ 头牛走到第 $j$ 头牛的代价（设 $H$ 牛编号从 $1$ 到 $H$，$G$ 牛编号从 $H+1$ 到 $H+G$），可以得到转移方程如下：

$$f_{i,j,0}=\min(f_{i,j,0},f_{i-1,j,0}+\operatorname{dis}(i-1,i),f_{i-1,j,1}+\operatorname{dis}(i,n+j))$$
$$f_{i,j,1}=\min(f_{i,j,1},f_{i,j-1,1}+\operatorname{dis}(n+j,n+j-1),f_{i,j-1,0}+\operatorname{dis}(i,n+j))$$

初值 $f_{1,0,0}=0$，答案即为 $f_{n,m,0}$。记得开 ```long long```。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1005;
int n,m,x[N<<1],y[N<<1];
ll f[N][N][2];
inline int dis(int i,int j)//算出代价
{
	return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n+m;++i)
		cin>>x[i]>>y[i];
	memset(f,0x7f,sizeof(f));
	f[1][0][0]=0;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=m;++j)
		{
			f[i][j][0]=min(f[i][j][0],min(f[i-1][j][0]+dis(i-1,i),f[i-1][j][1]+dis(i,n+j)));
			if(j)f[i][j][1]=min(f[i][j][1],min(f[i][j-1][1]+dis(n+j,n+j-1),f[i][j-1][0]+dis(i,n+j)));//转移
		}
	cout<<f[n][m][0];
	return 0;
}
```

---

## 作者：ccjjxx (赞：1)

# P2848 [USACO16DEC] Cow Checklist G


这道题的题面很糊。大概就是说有 $n$ 个 $H$，$m$ 个 $G$，每个点都在同一平面坐标系第一象限内。让你访问所有的点，访问顺序满足：

- 开始是 $H_1$ 点，结束是 $H_n$ 点；

- 两个序列分别按字典序访问。

每次走过的权值是两点欧几里得距离的平方。

那么我们可以这样设状态：

设 $dp_{i,j,0}$ 表示 $H$ 走过 $i$ 个而 $G$ 走过 $j$ 个，现在处在 $H$。

$dp_{i,j,1}$ 同理。

那么每个 $H$ 都是从 $i-1$ 状态而来，每个 $G$ 都是从 $j-1$ 状态而来，那么就有转移：

$$
dp_{i,j,0}=\min(dp_{i,j,0},dp_{i-1,j,0}+dis(i,i-1),dp_{i-1,j,1}+dis(i,n+j))
$$

$$
dp_{i,j,1}=\min(dp_{i,j,1},dp_{i,j-1,0}+dis(j+n,i),dp_{i,j-1,1}+dis(j+n,j+n-1))
$$

初始是 $dp_{1,0,0}$，结束是 $dp_{n,m,0}$。

然后就做出来了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
const int N=2e3+2;
int x[N],y[N];
long long dp[N>>1][N>>1][2];
inline int dis(int x,int y,int xx,int yy)
{
	int res=abs(x-xx)*abs(x-xx)+abs(y-yy)*abs(y-yy);
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n+m;i++) cin>>x[i]>>y[i];
	for(int i=0;i<=n;i++)
	for(int j=0;j<=m;j++) dp[i][j][0]=dp[i][j][1]=1e18;
	dp[1][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			dp[i][j][0]=min(dp[i][j][0],min(dp[i-1][j][0]+dis(x[i],y[i],x[i-1],y[i-1]),dp[i-1][j][1]+dis(x[i],y[i],x[j+n],y[j+n])));
			if(j)
			dp[i][j][1]=min(dp[i][j][1],min(dp[i][j-1][0]+dis(x[j+n],y[j+n],x[i],y[i]),dp[i][j-1][1]+dis(x[j+n],y[j+n],x[j+n-1],y[j+n-1])));
		}
	}
	cout<<dp[n][m][0];
	return 0;
}
```

---

## 作者：wangkelin123 (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/P2848)

这道题我认为题目是挺难读懂的，但思路却是容易理解的。

## 题意
约翰有两种牛，$n$ 头 H 牛与 $m$ 头 G 牛（简写）。每天，约翰都要交错询问每一头牛，也就是说不一定要先询问所有 H 牛再询问 G 牛。但是**第一次询问的一定是 $H _ {1}$ 号牛，最后询问的一定是 $H _ {n}$ 号牛**。如果两头牛间的距离是 $D$，那么约翰就需要消耗 $D^2$ 的能量。

现在约翰告诉你每头牛的坐标，请问访问完约翰最少需要消耗多少能量。

## 思路
这明显是道 DP（动态规划）求 min。


首先我们要准备一个 $f _ {i,j}$ 数组，表示已经访问过前 $i$ 头
 H 牛与前 $j$ 头 G 牛所需要消耗的最少能量。但是我们还需要知道最后访问的是哪种牛，所以不如开个**三维数组** $f[1005][1005][2]$（最后一维表示最后访问的是哪种牛——$0$ 是 H 牛，$1$ 是 G 牛）。


接着是**预处理**。为了后面能更简便地做转移方程，所以可以**先算出所有牛之间的距离**，也就是走过需要消耗的能量。

距离如何求呢？运用勾股定理可知：平面直角坐标系中两个点的距离的平方 $=$ 横坐标差的平方 $+$ 纵坐标差的平方。

然后就很好求了。我定义了 $3$ 个数组。

$d1 _ {i}$ 表示 $H _ {i}$ 与 $H _ {i+1}$ 间的距离。

$d1 _ {i}=(h _ {i}.x-h _ {i+1}.x)\times(h _ {i}.x-h _ {i+1}.x)+(h _ {i}.y-h _ {i+1}.y)\times(h _ {i}.y-h _ {i+1}.y);$

$d3 _ {i}$ 表示 $G _ {i}$ 与 $G _ {i+1}$ 间的距离。

$d3 _ {i}=(g _ {i}.x-g _ {i+1}.x)\times(g _ {i}.x-g _ {i+1}.x)+(g _ {i}.y-g _ {i+1}.y)\times(g _ {i}.y-g _ {i+1}.y);$

$d2 _ {i,j}$ 表示 $H _ {i}$ 与 $G _ {j}$ 间的距离。

$d2 _ {i,j}=(h _ {i}.x-g _ {j}.x)\times(h _ {i}.x-g _ {j}.x)+(h _ {i}.y-g _ {j}.y)\times(h _ {i}.y-g _ {j}.y);$


然后**转移方程**最为重要。怎么写呢？这里需要的方法俗称“**曲线救国**”，也就是先找到访问上一头牛及访问 $i,j$ 以前所有的牛共需要的最小能量花费，最后再加上前一头牛到当前牛的**所有种距离求 min** 就可以了。当然两种牛都得算所有种距离求 min。

$ f _ {i,j,0}=\min(f _ {i,j,0},\min(f _ {i-1,j,0}+d1 _ {i-1},f _ {i-1,j,0}+d2 _ {i,j}));$
$$f _ {i,j,1} = \begin{cases} \min(f _ {i,j,1},\min(f _ {i,j-1,1}+d3 _ {j-1},f _ {i,j-1,0}+d2 _ {i,j})); & j>0 \\ 0 & j=0  \end{cases}$$

注意：因为是取 min，所以要先把 $f[1005][1005][2]$ 数组的所有位置初始为正无穷，除了 $f _ {1,0,0}$ 是约翰初始站的位置，所以初始为 $0$。


最后 `cout<<f[n][m][0]` 就可以了，因为**最后访问的一定是 H 牛**。

## 代码
[code](https://www.luogu.com.cn/paste/lbelp8th)

---

## 作者：dutianchen1 (赞：0)

# P2848 [USACO16DEC] Cow Checklist G

### 思路简析

显然，我们只需要保证前 $n$ 头奶牛与后 $m$ 头奶牛之间的移动顺序有序即可。

那么 `dp` 状态就很好想了：设 $dp_{i,j}$ 表示从 $H$ 奶牛的第 $i$ 头走到 $G$ 奶牛的第 $j$ 头的状态下所消耗的最小能量。

但是本题要求我们必须从 $H_{1}$ 出发，到 $H_{n}$ 结束。所以我们需要再加一维表示当前所到的奶牛属于哪一种。

于是状态转移方程也就很好想到了：
$$
\left \{ \begin{matrix}
dp_{i,j,0}=\min(dp_{i-1,j,0}+dis_{i-1,j},dp_{i-1,j,1}+dis_{i,n+j})  \\
dp_{i,j,1}=\min(dp_{i,j-1,0}+dis_{i,n+j},dp_{i,j-1,1}+dis_{n+i-1,n+j}) \\
\end{matrix} \right.
$$
只需要再预处理以下每个点之间的 `dis` 数组即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e3+5;
const ll inf = 1e18+7; 
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}
struct node{
	ll x,y;
}num[N];
ll dp[N][N][2];
ll dis[N][N];
ll T;
ll n,m;
void clear(){
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j][0]=inf;dp[i][j][1]=inf;
		}
	}
}
void solve(){
	n=read();m=read();
	for(int i=1;i<=n+m;i++){
		num[i].x=read();num[i].y=read();
	}
	for(int i=1;i<=n+m;i++){
		for(int j=i+1;j<=n+m;j++){
			dis[i][j]=(num[i].x-num[j].x)*(num[i].x-num[j].x)+(num[i].y-num[j].y)*(num[i].y-num[j].y);
		}
	}
	clear();
	dp[1][0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j][0]=min({dp[i][j][0],dp[i-1][j][0]+dis[i-1][i],dp[i-1][j][1]+dis[i][n+j]});
			if(j)dp[i][j][1]=min({dp[i][j][1],dp[i][j-1][0]+dis[i][n+j],dp[i][j-1][1]+dis[n+j-1][n+j]});
		}
	}
	cout<<dp[n][m][0]<<'\n';
}
int main()
{
	T=1;
	while(T--){
		
		solve();
	}
	return 0;
}
```

---

## 作者：sssscy_free_stdio (赞：0)

这道题非常简单，不知道为啥是蓝题。

就是一道 DP。

我们设 $dp_{i,j,0}$ 为第一组看到了第 $i$ 个，第二组看到了第 $j$ 个，现在在第一组的最小花费，$dp_{i,j,1}$ 为第一组看到了第 $i$ 个，第二组看到了第 $j$ 个，现在在第二组的最小花费。

那么我们就能列出方程：

$dp_{i,j,0}=\min \left(dp_{i,j,0},dp_{i-1,j,0}+cost \left(i-1,i\right),dp_{i-1,j,1}+cost\left(i,n+j\right)\right)$。

$dp_{i,j,1}=\min \left(dp_{i,j,1},dp_{i,j-1,0}+cost \left(i,n+j\right),dp_{i,j-1,1}+cost\left(n+j-1,n+j\right)\right)$。

然后就可以写代码了，记得要开 `long long`。

### CODE:

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[2010],b[2010];
long long dp[1010][1010][10];
int cost(int i,int j){
	return (a[i]-a[j])*(a[i]-a[j])+(b[i]-b[j])*(b[i]-b[j]);
}int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+m;i++){
		scanf("%d%d",&a[i],&b[i]);
	}memset(dp,0x3f,sizeof dp);
	dp[1][0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j][0]=min(dp[i][j][0],min(dp[i-1][j][0]+cost(i-1,i),dp[i-1][j][1]+cost(i,n+j)));
			if(j!=0){
				dp[i][j][1]=min(dp[i][j][1],min(dp[i][j-1][0]+cost(i,n+j),dp[i][j-1][1]+cost(n+j-1,n+j)));
			}
		}
	}printf("%lld",dp[n][m][0]);
	return 0; 
}
```

---

## 作者：nzcnnr (赞：0)

# 递推公式
很明显，这道题是一个 dp，所以说首当其冲的是想出递推公式，建立变量 $d_{i,j,k}$ 用来表示目前已经表示出了第一组第 $i$ 个，第二组第 $j$ 个，目前在第 $j+1$ 组中（其实这个变量就是用来表示在第几组的），很容易想出 在 $k=1$ 时有：
$$d_{i,j,1}=d_{i,j-1,0}\times dis_{i,j}+dis_{i,j-1,1}\times dis_{j-1,j}$$
同理可得，在 $k=0$ 时，有：
$$d_{i,j,0}=d_{i-1,j,0}\times dis_{i-1,i}+dis_{i-1,j,1}\times dis_{j,i}$$

说明一下，$dis$ 用来存储两点之间的距离平方

所以说，~~这道题已经解决了~~
# 一些问题
$1$ 不开 longlong 见祖宗。

$2$ 注意存储边与边的距离时，尽量不要分两个数组，可以把第二组的存储续在第一组之后，也就是开一个 $dis_{n+m,n+m}$ 会方便一些（~~谨防 RE~~）

$3$ 题目里规定了首项为第一组第一个末项为第一组最后一个，所以dp 过程中，代表第二组的循环要从 $0$ 开始，

话不多说，上代码。

# CODE
```c
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
long long d[2005][2005][2];
long long dis[2005][2005];
struct node{
	int x,y;
}a[2005];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int xf,yf;
		scanf("%d%d",&xf,&yf);
		a[i]={xf,yf};
	}
	for(int i=n+1;i<=m+n;i++){
		int xf,yf;
		scanf("%d%d",&xf,&yf);
		a[i]={xf,yf}; 
	}
	for(int i=1;i<=n+m;i++){
		for(int j=i+1;j<=m+n;j++){
			dis[i][j]=(a[j].x-a[i].x)*(a[j].x-a[i].x)+(a[j].y-a[i].y)*(a[j].y-a[i].y);//两点坐标公式平方
		}
	}
	memset(d,0x7f,sizeof(d));//不要忘了初始化
	d[1][0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(j) d[i][j][1]=min(d[i][j][1],min(d[i][j-1][1]+dis[j-1+n][j+n],d[i][j-1][0]+dis[i][j+n]));//如果j为0，那么就会越界
			d[i][j][0]=min(d[i][j][0],min(d[i-1][j][1]+dis[i][j+n],d[i-1][j][0]+dis[i-1][i]));
		}
	}
	printf("%lld",d[n][m][0]);//末项必须是第一组最后一个
	return 0;
} 
```

---

