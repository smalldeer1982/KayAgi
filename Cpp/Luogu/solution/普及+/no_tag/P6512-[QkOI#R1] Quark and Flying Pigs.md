# [QkOI#R1] Quark and Flying Pigs

## 题目描述

给定一个 $n$ 个点 $m$ 条边的边带权简单连通无向图，在 $0$ 时刻你在点 $1$ 上。

假设当前是 $t$ 时刻，你在点 $v$ 上，你可以选择两种操作：

- 仍停留在点 $v$ 上，操作后到 $t+1$ 时刻。
- 选择一条边 $(a,b,w)$ 满足 $a=v$ 或 $b=v$，则你到这条边连接的另一个点上，操作后到 $t+w$ 时刻。

有 $k$ 条信息，每一条信息形如 $(t_i,v_i)$ 表示在 $t_i$ 时刻，点 $v_i$ 上会出现一只飞猪，其编号为 $i$，若该时刻你在 $v_i$ 上，则你捕获到了 $i$ 号飞猪。

现在你需要求出你能捕获到的飞猪数量的最大值。



## 说明/提示

### 样例解释

最优方案如下：

$0$ 时刻，选择移动到节点 $2$，时间来到 $2$ 时刻。  
$2$ 时刻，捕获到第 $2$ 只飞猪，选择停留在节点 $2$，时间来到 $3$ 时刻。  
$3$ 时刻，捕获到第 $3$ 只飞猪，选择移动到节点 $1$，时间来到 $5$ 时刻。  
$5$ 时刻，捕获到第 $4$ 只飞猪，选择移动到节点 $2$，时间来到 $7$ 时刻。  
$7$ 时刻，捕获到第 $5$ 只飞猪。

### 数据范围

对于 $20\%$ 的数据，$n,m,k\le 7$。  
对于 $100\%$ 的数据，$2\le n\le 200$，$1\le m\le \frac{n(n-1)}{2}$，$1\le k\le 5000$，$1\le a_i,b_i,v_i\le n$，$1\le w_i\le 1000$，$1\le t_i\le 10^9$。

## 样例 #1

### 输入

```
2 1 5
1 2 2
1 2
2 2
3 2
5 1
7 2
```

### 输出

```
4```

# 题解

## 作者：Utilokasteinn (赞：20)

### [P6512 [QkOI#R1] Quark and Flying Pigs](https://www.luogu.com.cn/problem/P6512)

简单 DP。

设 $dis_{u,v}$ 表示从 $u$ 到 $v$ 的最短路径，这可以用 Floyd 在 $\mathcal{O}(n^3)$ 的复杂度内预处理出。

对于第 $i$ 只飞猪和第 $j$ 只飞猪，因为可以在一个点上停留，容易发现若 $t_i+dis_{pos_i,pos_j}\le t_j$，那么人就可以在抓到 $i$ 之后到 $j$ 的位置去抓 $j$。

那么就容易想到 DP。

设 $f_i$ 表示抓住第 $i$ 只飞猪的前提下，前 $i$ 只飞猪最多可以抓几只。

那么转移方程便容易写出，枚举 $j$（$j<i$），看是否可以从 $j$ 到 $i$，来更新答案。

具体转移方程见代码，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0;char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s;
}
int n,m,s;
int dis[205][205],f[5005],ans;
struct node
{
    int t,pos;
}a[5001];
bool cmp(node x,node y){return x.t<y.t;}
int main()
{
    n=read(),m=read(),s=read();
	memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read(),w=read();
		dis[u][v]=dis[v][u]=w;
    }
	for(int i=1;i<=n;i++)
		dis[i][i]=0;
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=1;i<=s;i++)
		a[i].t=read(),a[i].pos=read();
    sort(a+1,a+s+1,cmp);
    a[0].pos=1;//时刻为0的时候，人在位置1
    for(int i=1;i<=s;i++)
        for(int j=0;j<i;j++)
            if(dis[a[i].pos][a[j].pos]+a[j].t<=a[i].t)
                f[i]=max(f[i],f[j]+1);
	for(int i=1;i<=s;i++)
		ans=max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Warriors_Cat (赞：7)

### $Solution:$

一道最短路和 DP 的结合题。

首先，用 Floyd 求出全源最短路~~当然用 Johnson 也可以~~，时间复杂度为 $O(n^3)$

接着，把所有 Flying Pigs 按照 $t_i$ 大小排序，然后进行 DP。

定义 $f_i$ 表示前 $i$ 只猪中最多能取多少只猪，其中第 $i$ 只必须取。

定义 $dis(i, j)$ 表示节点 $i$ 和 $j$ 之间的距离。

那么可得转移方程：

$$f_i = \max_{j<i}\{[t_j + dis(j, i) \le t_i](f_j+1)\}$$

最后取一下所有的最大值就行了，时间复杂度为 $O(k^2)$。

总时间复杂度为 $O(n^3+k^2)$。

注意 $O(k\log_2k+k+n^3)$ 的贪心是错误的。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
struct node{
    int t, v;
    bool operator < (const node&rhs)const{
        return t < rhs.t;
    }
}a[5010];
int n, m, K, mp[210][210], x, y, z, t[5010], v[5010], ans, idx, lst, f[5010];
int main(){
    n = read(); m = read(); K = read(); memset(mp, 63, sizeof(mp));
    for(int i = 1; i <= m; ++i){
        x = read(); y = read(); z = read();
        mp[x][y] = min(mp[x][y], z);
        mp[y][x] = min(mp[y][x], z);
    }
    for(int i = 1; i <= n; ++i) mp[i][i] = 0;
    for(int k = 1; k <= n; ++k){
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
            }
        }
    }//Floyd 模板
    for(int i = 1; i <= K; ++i){
        a[i].t = read(); a[i].v = read();
    }
    sort(a + 1, a + K + 1); a[0].t = 0; a[0].v = 1;
    for(int i = 1; i <= K; ++i){
    	for(int j = 0; j < i; ++j){
    		if(a[j].t + mp[a[j].v][a[i].v] <= a[i].t) f[i] = max(f[i], f[j] + 1);
		}
		ans = max(ans, f[i]);
	}//DP 部分
    printf("%d", ans);
}
```

---

## 作者：Inui_Sana (赞：3)

提供一种复杂度更劣但是仍然正确的写法。

先处理出两点之间距离，用 `Floyd` 即可。

接下来的操作就不太一样了。状态定义为 $dp_{i,j}$ 表示处理到第 $i$ 只飞猪，最后停在 $j$ 点能抓到的最多飞猪数。

飞猪按 $t_i$ 排序后，枚举每只飞猪，再枚举终点和起点。对于每个起点，枚举之前每只飞猪 $i$，如果在 $t_i$ 从起点出发，能在当前时间到达终点，就更新 `dp` 值。

但是这样时间复杂度是 $O(n^3+n^2k^2)$ 的，明显过不了。考虑优化。因为可以停留在原地，所以 $dp_{i,j}$ 在 $j$ 确定时是单调递增的。故可以二分。但是时间复杂度仍是 $O(n^3+n^2k\log k)$，[无法通过](https://www.luogu.com.cn/record/100846321)。再分析一下，发现确定起点和终点（同上文）后，决策具有单调性。所以可以对于每对起点和终点记录决策点。时间复杂度 $O(n^3+n^2k)$，[开 `O2` 可过](https://www.luogu.com.cn/record/100847467)。

code：

```cpp
#include<bits/stdc++.h>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
typedef long long ll;
const int N=207,M=5e3+7,V=-1;
const int inf=0x3f3f3f3f;
const int mod=0;
namespace fast_io{
	template<typename Tp>
	inline void read(Tp &ret){
		Tp x=0,f=1;
		char c=getchar();
		while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
		while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-0x30;c=getchar();}
		ret=x*f;
	}
	template<typename Tp>
	inline void write(Tp x){
		static char buf[40];
		static int len=-1;
		if(x<0)putchar('-'),x=-x;
		do buf[++len]=x%10,x/=10;while(x);
		while(len>=0)putchar(buf[len--]+0x30);
	}
}
int n,m,k;
int dis[N][N];
int dp[M][N],pre[N][N];
struct node{
	int t,val;
	bool operator<(const node &tmp)const{
		return t<tmp.t;
	}
}e[M];
void solve(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=inf/3;
		}
		dis[i][i]=0;
	}
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		dis[u][v]=dis[v][u]=w;
	}
	for(int p=1;p<=n;p++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][p]+dis[p][j]);
			}
		}
	}//Floyd
	for(int i=1;i<=k;i++){
		scanf("%d%d",&e[i].t,&e[i].val);
	}
	sort(e+1,e+k+1);
	mems(dp,0x80);
	dp[0][1]=0;
	mems(pre,-1);
	for(int p=1;p<=k;p++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				while(e[pre[i][j]+1].t<=e[p].t-dis[i][j]&&pre[i][j]<p-1){
					pre[i][j]++;
				}//找到决策点
				if(~pre[i][j]){
					dp[p][i]=max(dp[p][i],dp[pre[i][j]][j]);
				}
			}
		}
		dp[p][e[p].val]++;//捉到就++
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[k][i]);
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：LCuter (赞：3)

## B - Quark and Flying Pigs

##### $\text{Description}$

给定一个 $n$ 个点 $m$ 条边的边带权无向图，在 $0$ 时刻你在点 $1$ 上。

假设当前是 $t$ 时刻，你在点 $v$ 上，你可以选择两种操作：

- 仍停留在点 $v$ 上，操作后到 $t+1$ 时刻。
- 选择一条边 $(a,b,w)$ 满足 $a=v$ 或 $b=v$，则你到这条边连接的另一个点上，操作后到 $t+w$ 时刻。

有 $k$ 条信息，每一条信息形如 $(t_i,v_i)$ 表示在 $t_i$ 时刻，点 $v_i$ 上会出现一只飞猪，其编号为 $i$，若该时刻你在 $v_i$ 上，则你捕获到了 $i$ 号飞猪。

现在你需要求出你能捕获到的飞猪数量的最大值。

$2\le n\le 200$，$1\le m\le \frac{n(n-1)}{2}$，$1\le k\le 5000$，$1\le a_i,b_i,v_i\le n$，$1\le w_i\le 1000$，$1\le t_i\le 10^9$。

##### $\text{Solution}$

先跑一遍 Floyd 求出任意点对间最短路。

接下来将每条信息按 $t_i$ 从小到大排序，设 $f_i$ 表示在只考虑前 $i$ 个信息时能捉到的飞猪数量，则有：

$$f_i=\max_{0\le j<i}\{[\operatorname{dis}(i,j)\le t_i-t_j](f_j+1)\}$$

时间复杂度 $O(k^2+n^3)$。

好像和 P2285 撞题了。

~~Flying Pig 就是（数据删除）~~

---

## 作者：封禁用户 (赞：2)

这题很简单，但我在考场上想了半天。

发现$n<=200,k<=5000$,所以可能$O(n^3+k^2)$

好吧，$O(n^3)$是什么呢？

$Floyd$！！！

我们先跑一遍$Floyd$，就知道了每两个点之间的最短路。

然后由于要捕捉到最多，~~很自然的~~想到$dp$。

设$dp[i]$为捕捉第$i$头牛，最多可以捕捉多少牛。

转移就是如果第$j$头牛到第$i$头牛的距离小于等于他们的时间差，就$dp[i]=max(dp[i],dp[j]+1)$

## 注意！如果别人都走不到你，那这个点的$dp$值就要算$0$。
因为他根本就不会被捕捉到。。。所以如果算$1$，凉之。

这显然满足无后效性，因为我走到这个牛就要等到它出现，所以一定后一头牛要等到这个牛出现的时间才能他那边走过去。

然后也满足最优子结构，因为前面的只要最优，中间都是走到这头牛，如果不同的方案只要记最优的就行了。

由上可知证毕（大雾

开始还要把所有猪猪按时间排个序，就可以保证从前往后走

然后从每个点中选最优就可以了。

$code$ $time$：
```cpp
/*      西江月·证明
	即得易见平凡，仿照上例显然。
   留作习题答案略， 读者自证不难。

	反之亦然同理，推论自然成立。
	略去过程QED，由上可知证毕。*/
#define mod 10
#include<iostream>
#include<algorithm>
#include<cstdio>
#define kkk register
#define ll long long
#define inf 2147098934832ll
using namespace std;
int read(){int ans=0,f=1;char a=getchar();while(a>'9'||a<'0')f|=a=='-',a=getchar();while(a>='0'&&a<='9')ans=(ans<<3)+(ans<<1)+a-'0',a=getchar();return ans*f;}
//一条long long的黄金分割线-----------------------------------------------------------------------------------------------------------------------------------
int n,m,s,maxt,dp[205][205],ddp[20005];
struct node{
	int t,v;
}fz[100005];
bool cmp(node a,node b){return a.t<b.t;}
int main(){
    n=read();m=read();s=read();
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++)
    		dp[i][j]=10903333;
    for(int i=1;i<=n;i++)dp[i][i]=0;
    for(int i=1;i<=m;i++){
    	int u=read(),v=read(),w=read();
    	dp[u][v]=dp[v][u]=min(dp[u][v],w);
	}
	for(int i=1;i<=s;i++)fz[i].t=read(),fz[i].v=read();
	sort(fz+1,fz+1+s,cmp);
	for(int j=1;j<=n;j++)
		for(int i=1;i<=n;i++)
			for(int k=1;k<=n;k++)
				dp[i][k]=min(dp[i][k],dp[i][j]+dp[j][k]);
	ddp[0]=0;fz[0].t=0;fz[0].v=1;
	int ans=0;
	for(int i=1;i<=s;i++){
		ddp[i]=0;
		for(int j=0;j<i;j++)
			if(fz[i].t-fz[j].t>=dp[fz[i].v][fz[j].v])
				ddp[i]=max(ddp[i],ddp[j]+1);
		ans=max(ans,ddp[i]);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Tony2 (赞：1)

##### 不知道能不能抢到第一

首先这肯定是一道动态规划。。。

我们考虑状态。

我们肯定是要捕获一只飞猪然后到另一只飞猪出现的位置等待一会（可能不用等）然后再捕获它。

所以我们设计状态$f_{i}$，表示考虑到第$i$头飞猪，肯定要捕获的最多捕获的飞猪数量。特别的，我们设$f_0=0,v_0=1,t_0=0$，$f_{i}(i>0)$为负无限。

考虑转移，我们先要把飞猪按出现的时间排序，这样能保证转移不出错。要捕获第$i$头飞猪，我们可以从$v_{j}$出发到$v_{i}$，满足$t_{i}-dis_{v_{i},v_{j}}\le t_{j}$。

那这样。。。这道题就做完了！上代码！

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 205, M = 5005;
int n, m, p;
int dis[N][N];
pair<int, int> pig[M];
int f[M], ans=0;
int main(){
	std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	freopen("test_file/in.txt", "r", stdin);
//	freopen("test_file/out.out", "w", stdout);
	memset(dis, 0x3f, sizeof(dis));
	memset(f, -0x3f, sizeof(f));
	cin >> n >> m >> p;
	for (int i = 0; i < m; i++){
		int u, v, w;
		cin >> u >> v >> w;
		dis[u][v] = dis[v][u] = min(dis[u][v], w);
	}
	for (int i = 1; i <= p; i++) cin >> pig[i].first >> pig[i].second;
	sort(pig+1, pig+1+p);
    //floyd求最短路
	for (int i = 1; i <= n; i++) dis[i][i] = 0;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][k]+dis[k][j], dis[i][j]);
    f[0] = 0;
    pig[0] = {0, 1};//特例f[0],pig[0]
	for (int i = 1; i <= p; i++)
		for (int j = 0; j <= p; j++)
			if (pig[i].first-dis[pig[i].second][pig[j].second] >= pig[j].first && j != i)//考虑能不能赶过来
			    f[i] = max(f[j]+1, f[i]);
	for (int i = 1; i <= p; i++) ans = max(f[i], ans);
	cout << ans;
	return 0;
}
```
### 完结散花！

---

## 作者：dead_X (赞：0)

## 思路简述
典型的二合一水题。

Floyd最短路 + 动态规划。

### Step1 求最短路
不会 Floyd 请自行学习。

直接 $O(n^3)$ 就能水过去。

然后我们就知道从图上一点到另一点的最短距离。
### Step2 求最多能接到几只猪
考虑动态规划。

首先，我们记$t_k$ 为第 $k$ 只猪出现的时间，记 $dis_{ij}$ 为第 $i,j$ 只猪所在的位置之间的距离， $f_k$ 为前 $k$ 只猪中接到第 $k$ 只猪时最多能接到的猪的数量，那么不难写出状态转移方程:

$$f_x=max\{f_y+1\}(t_y+dis_{xy}\leq t_x,0\leq y<x)$$

显然如果预处理了图上两点最短距离是可以 $O(k^2)$ 的，那么直接算就好了。
## 代码
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
long long dis[503][503];
struct pig
{
	long long t;
	int p;
}p[10003];
inline bool cmp(pig x,pig y)
{
	return x.t<y.t;
}
using namespace std;
int Mx[10003];
int main()
{
	int n=read(),m=read(),k=read(),u,v,w;
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) dis[i][j]=100000000007LL;
	for(int i=1; i<=n; i++) dis[i][i]=0;
	while(m--) u=read(),v=read(),w=read(),dis[u][v]=min(dis[u][v],(long long)w),dis[v][u]=min(dis[v][u],(long long)w);
	for(int i=1; i<=k; i++) p[i].t=read(),p[i].p=read();
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) for(int k=1; k<=n; k++) dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
	sort(p+1,p+k+1,cmp);
	p[0].p=1,p[0].t=0;
	int ans=0;
	for(int i=1; i<=k; i++) 
	{
		for(int j=0; j<i; j++) if(p[j].t+dis[p[j].p][p[i].p]<=p[i].t) Mx[i]=max(Mx[j]+1,Mx[i]);
		ans=max(ans,Mx[i]);
	}
	printf("%d",ans);
	return 0;
}
//人傻常数大
```

复杂度 $O(n^3+k^2)$

---

