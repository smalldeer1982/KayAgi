# Road Optimization

## 题目描述

The Government of Mars is not only interested in optimizing space flights, but also wants to improve the road system of the planet.

One of the most important highways of Mars connects Olymp City and Kstolop, the capital of Cydonia. In this problem, we only consider the way from Kstolop to Olymp City, but not the reverse path (i. e. the path from Olymp City to Kstolop).

The road from Kstolop to Olymp City is $ \ell $ kilometers long. Each point of the road has a coordinate $ x $ ( $ 0 \le x \le \ell $ ), which is equal to the distance from Kstolop in kilometers. So, Kstolop is located in the point with coordinate $ 0 $ , and Olymp City is located in the point with coordinate $ \ell $ .

There are $ n $ signs along the road, $ i $ -th of which sets a speed limit $ a_i $ . This limit means that the next kilometer must be passed in $ a_i $ minutes and is active until you encounter the next along the road. There is a road sign at the start of the road (i. e. in the point with coordinate $ 0 $ ), which sets the initial speed limit.

If you know the location of all the signs, it's not hard to calculate how much time it takes to drive from Kstolop to Olymp City. Consider an example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1625C/ced979ea5e93d9eaaf40c701d26a878fb490113f.png)Here, you need to drive the first three kilometers in five minutes each, then one kilometer in eight minutes, then four kilometers in three minutes each, and finally the last two kilometers must be passed in six minutes each. Total time is $ 3\cdot 5 + 1\cdot 8 + 4\cdot 3 + 2\cdot 6 = 47 $ minutes.

To optimize the road traffic, the Government of Mars decided to remove no more than $ k $ road signs. It cannot remove the sign at the start of the road, otherwise, there will be no limit at the start. By removing these signs, the Government also wants to make the time needed to drive from Kstolop to Olymp City as small as possible.

The largest industrial enterprises are located in Cydonia, so it's the priority task to optimize the road traffic from Olymp City. So, the Government of Mars wants you to remove the signs in the way described above.

## 说明/提示

In the first example, you cannot remove the signs. So the answer is $ 47 $ , as it's said in the statements above.

In the second example, you may remove the second and the fourth sign. In this case, you need to drive four kilometers in $ 4\cdot5 = 20 $ minutes, and then six kilometers in $ 6\cdot3 = 18 $ , so the total time is $ 4\cdot5 + 6\cdot3 = 38 $ minutes.

## 样例 #1

### 输入

```
4 10 0
0 3 4 8
5 8 3 6```

### 输出

```
47```

## 样例 #2

### 输入

```
4 10 2
0 3 4 8
5 8 3 6```

### 输出

```
38```

# 题解

## 作者：yeshubo_qwq (赞：12)

## 思路：DP
三维 DP 需要滚动数组，但二维 DP 不需要。

设 $dp_{i,j}$ 表示在第 $i$ 个限速标志的时候删掉了 $j$ 个限速标志的最小花费的时间。

我们枚举 $i$ 和 $j$，再枚举 $c$ **连续**删几个限速标志，就像这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/0o3aqnfq.png?x-oss-process=image/resize,m_lfit,h_2500,w_3050)

关于为什么不需要有间隔的删：

比如：要删第 $1$ 个限速标志，第 $2$ 个限速标志和第 $4$ 个限速标志。

删第 $1$ 个限速标志，第 $2$ 个限速标志已经在做第 $2$ 个限速标志就做过了，会被包含的，所以不需要。

之后，就可以推出状态转移方程了：$dp_{i,j}=\min\left(dp_{i,j},dp_{i-c-1,j-c}+\left(d_{i}-d_{i-c-1}\right)\times a_{i-c-1}\right)$。

$d$ 数组表示位置，$a$ 数组表示限速。

注意：为了保证能到达终点，$d$ 数组最后要加上终点的位置。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,k,i,j,c,d[505],a[505],dp[505][505],mi;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>l>>k;
	for(i=1;i<=n;i++)cin>>d[i];
	for(i=1;i<=n;i++)cin>>a[i];
	d[n+1]=l;
	memset(dp,0x3f,sizeof(dp));
	for(i=0;i<=k;i++)dp[1][i]=0;
	for(i=2;i<=n+1;i++)
		for(j=0;j<=min(i-1,k);j++)
			for(c=0;c<=j;c++)
				dp[i][j]=min(dp[i][j],dp[i-c-1][j-c]+(d[i]-d[i-c-1])*a[i-c-1]);
	mi=2e9;
	for(i=0;i<=k;i++)
	    mi=min(mi,dp[n+1][i]);
	return cout<<mi,0;
}
```


---

## 作者：yanghanyv (赞：7)

## 思路

本蒟蒻的思路好像和大佬们不太一样。

### 状态函数

- 看到这个题目描述和数据范围，容易想到是 DP。所以我们先设 $f_{i,j}$ 表示在前 $i$ 个路牌中移除 $j$ 个时，走到第 $i$ 个路牌花费的总时间。
- 然后发现每一段通过的时间为 $a_p \times (d_i-d_{i-1}) (1 \leq p \leq i-1)$。式子中，$d_i-d_{i-1}$ 可以直接求，但 $a_p$ 与最后一个未移除的路牌有关，即与前面的路牌的具体移除情况有关，所以要加上一维，表示最后一个未移除的路牌。
- 最终设出状态，$f_{i,j,p}$ 表示在前 $i$ 个路牌中移除 $j$ 个，且最后一个未移除的路牌限速 $a_p$ 时，走到第 $i$ 个路牌花费的总时间。

### 状态转移方程

- 我们可以对每个路牌分类讨论：
1. 不删除 $i$ 号路牌：
$$f_{i,j,i}= \min\limits_{0 \leq j \leq \min(i-1,k),1 \leq p \leq i-1} f_{i-1,j,p}+a_p \times (d_i-d_{i-1})$$
2. 删除 $i$ 号路牌：
$$f_{i,j,p}= \min\limits_{1 \leq j \leq \min(i-1,k),1 \leq p \leq i-1} f_{i-1,j-1,p}+a_p \times (d_i-d_{i-1})$$

### 递推起点

- $f_{1,0,1}=0$。

### 答案

- 我们可以设终点为第 $n+1$ 个路牌，令 $d_{n+1}=l$，$a_{n+1}=0$，则有 
$$ans= \min\limits_{0 \leq j \leq k,1 \leq p \leq n+1}{f_{n+1,j,p}}$$

## 优化

由状态转移方程可以看出，推出 $f_i$ 时，只会用到 $f_{i-1}$，因此可以用滚动数组优化空间，滚掉数组第一维。

## 代码

时间复杂度 $O(n^3)$，可以通过本题。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e2+5;
const int INF=0x3f3f3f3f;
int n,l,k,d[N],a[N],f[2][N][N],ans=INF;
int main(){
	scanf("%d%d%d",&n,&l,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&d[i]);
	}
	d[n+1]=l;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	memset(f[1],0x3f,sizeof(f[1]));
	f[1][0][1]=0;//递推起点
	for(int i=2;i<=n+1;i++){
		memset(f[i%2],0x3f,sizeof(f[i%2]));//因为用了滚动数组，所以每次都要清空
		for(int p=1;p<i;p++){
			for(int j=0;j<=min(i-1,k);j++){
				f[i%2][j][i]=min(f[i%2][j][i],f[(i-1)%2][j][p]+a[p]*(d[i]-d[i-1]));//不删除i号路牌
			}
			for(int j=1;j<=min(i-1,k);j++){
				f[i%2][j][p]=min(f[i%2][j][p],f[(i-1)%2][j-1][p]+a[p]*(d[i]-d[i-1]));//删除i号路牌
			}
		}
	}
	for(int j=0;j<=k;j++){
		for(int p=1;p<=n+1;p++){
			ans=min(ans,f[(n+1)%2][j][p]);//答案
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：励珈玥 (赞：4)

**思路：**

使用二维dp解决。

$dp_{i,j}$ 表示看到第 $i$ 个路标时已经移除了 $j$ 个路标时，花费的最少时间。

可以发现，每一个路标能够由第 $(i - k - 1)$ 个到第 $(i - 1)$ 个路标转移过来，只需要把在它们之间的所有路标都删去即可。

所以需要三重循环枚举，$i$ 枚举看到第几个路灯，$j$ 枚举当前已经移除了几个，$kk$ 枚举此时连续删去了几个路标，能够用来计算从之前的哪一个路标转移过来。

**状态转移方程：**

对于每个路标都有两个可能：

1.前一个的路灯被删去过，导致部分路程限速变化，对当前产生了影响；

2.当前的路灯直接由 $(i - 1)$ 个路灯转移过来，对现在的计算不产生影响。

因此得出：

```c
dp[i][j] = min(dp[i][j], dp[i - c - 1][j - c] + d[i - c - 1] * (a[i] - a[i - c - 1])); //产生了影响

dp[i][j] = min(dp[i][j], dp[i - 1][j] + d[i - 1] * (a[i] - a[i - 1])); //不产生影响
```


**代码：**
```c
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k, a[510], d[510], dp[510][510];
signed main() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	a[n] = m;//由于我们要知道的是终点的最少时间，所以此时还需要添加终点
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = 1e18;//为了防止结果求min时出错，将所有除了初始点dp[0][0]的值都设成一个较大的数
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= min(i - 1, k); j++) {//如果i<k时最多只能删去i-1个路灯，所以要求min
			for (int c = 0; c <= j; kk++) {
				if (i - c - 1 >= 0) {//防止访问越界
					dp[i][j] = min(dp[i][j], dp[i - kk - 1][j - kk] + d[i - kk - 1] * (a[i] - a[i - c - 1]));
				}
			}
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + d[i - 1] * (a[i] - a[i - 1]));
		}
	}
	int ans = 1e18;
	for (int i = 0; i <= k; i++) {
		ans = min(ans, dp[n][i]);
	}
	cout << ans << endl;
}
```


---

## 作者：Argon_Cube (赞：3)

* **【题目链接】**

[Link:CF1625C](https://www.luogu.com.cn/problem/CF1625C)

* **【解题思路】**

我们设 $d_{i,j}$ 为在第 $i$ 个路牌前共移除了 $j$ 个路牌且未移除第 $i$ 个路牌（转移式会保证没有移除起点处的路牌），行驶到第 $i$ 个路牌的位置时所耗的最短时间。为了方便，我们设起点处的路牌为第 $0$ 个，在终点处设一个虚拟路牌方便处理边界，它为第 $n$ 个路牌；第 $i$ 个路牌的位置为 $t_i$，限制为 $s_i$。

我们对于每一个路牌，枚举它的前一个未被移除的路牌 $k$。转移式为

$$d_{i,j}=\min_{k\geq i-j-1}\{d_{k,j-(i-k-1)}+s_k\times(t_i-t_k)\}(1\leq i\leq n,0\leq j\leq \min(i-1,k_{\max}))$$

其中 $k_{\max}$ 为最多可移除的路牌数。意义为：上一个未移除的路牌为 $k$，则 $i$ 与 $k$ 间移除了 $i-k-1$ 个路牌。总时间为到达 $k$ 所要的时间再加上这两个路牌间需要的时间。

边界：$d_{0,0}=0,d_{0,i}(i>0)=\infty$（确保任何状态除 $d_{0,0}$ 外不能从 $d_{0,i}(i>0)$ 转移过来）

答案即为

$$\max_{0\leq k\leq k_{\max}}\{d_{n,k}\}$$

意义为枚举移除了几个路牌。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

array<array<long long,501>,501> DP_arr;
array<long long,501> tmpoint,spdlim;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt,len,max_rmv;
	cin>>cnt>>len>>max_rmv;
	for(int i=0;i<cnt;i++)
		cin>>tmpoint[i];
	for(int i=0;i<cnt;i++)
		cin>>spdlim[i];
	tmpoint[cnt]=len,spdlim[cnt]=0;
	for(int i=0;i<=500;i++)
		DP_arr[i].fill(1099511627776ll);
	DP_arr[0][0]=0;
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<i&&j<=max_rmv;j++)
			for(int k=i-1;j-(i-k-1)>=0;k--)
				DP_arr[i][j]=min(DP_arr[i][j],DP_arr[k][j-(i-k-1)]+spdlim[k]*(tmpoint[i]-tmpoint[k]));
	long long ans=1099511627776ll;
	for(int i=0;i<=max_rmv;i++)
		ans=min(ans,DP_arr[cnt][i]);
	cout<<ans;
	return 0;
}

```

---

## 作者：BigSmall_En (赞：2)

## 题意描述

给定 $i$ 个路牌的位置 $d_i$ ，以及通过第 $i$ 到第 $i+1$ 个路牌必须的速度 $a_i$ 。则通过这段路的花费为 $a_i\times(d_{i+1}-d_i)$ 。现在可以搬掉 $k$ 个路牌，要求给出最小的通过花费。特别的，对于终点的路牌编号，可以认定为是 $n+1$ 。 

## 思路

这种问题显然贪心很难解决，发现答案满足无后效性，可以考虑使用动态规划。

但是因为我动态规划很烂，于是考虑建图跑一些图上的算法来解决。

对于第 $i$ 个点和第 $j$ 个点建边，那么他将对答案产生 $a_i\times (d_j-d_i)$ 的贡献，而这需要拆除 $j-i-1$ 个路牌。

然后从 $1$ 号节点到 $n+1$ 号节点只需要在满足路径上拆除的路牌数 $\leq k$ 且路程最小即可。

## 具体实现

直接 $n^2$ 建边，因为要满足无后效性，所以要使用拓扑排序。对于每个点，枚举它的出边，然后转移到它可以转移的地方。 

更具体地，定义 $dis_{i,j}$ 表示第 $i$ 个点还可以拆除 $j$ 个路标的最小路程。

则假设现在的起点是 $u$ ，转移到的点是 $v$ ，路程是 $w$ ，需要拆除的路牌数是 $c$ 。则：

$$
dis_{v,i}=dis_{u,i+c}+w
$$

## 代码

这样子的话就不难实现了

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=505,INF=0x3f3f3f3f;
struct chainstar{
	int next,to,weight,cost;
}edge[(N*N)<<2];int head[N],cnt;
inline void addline(int u,int v,int w,int c){
	//printf("addline:%d %d %d %d\n",u,v,w,c);
	edge[++cnt].to=v;
	edge[cnt].weight=w;
	edge[cnt].cost=c;
	edge[cnt].next=head[u];
	head[u]=cnt;
}
int n,all,k,len[N],loc[N],lim[N],ind[N],dis[N][N];
queue<int>q;
int main(){
	n=read(),loc[n+1]=read(),k=read();
	for(int i=1;i<=n;++i)loc[i]=read();
	for(int i=1;i<=n;++i)lim[i]=read();
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n+1;++j){
			if(j-i-1>k)continue;
			addline(i,j,(loc[j]-loc[i])*lim[i],j-i-1);
			++ind[j];
		}
	}
	memset(dis,0x3f,sizeof(dis));
	q.push(1);dis[1][0]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to,w=edge[i].weight,c=edge[i].cost;
			for(int j=0;j<=k-c;++j)
				dis[v][j+c]=min(dis[v][j+c],dis[u][j]+w);
			--ind[v];
			if(!ind[v])q.push(v);
		}
	}int ans=INF;
	for(int i=0;i<=k;++i)
		ans=min(ans,dis[n+1][i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：MYiFR (赞：1)

### 题目大意
一条长为 $l$ 千米 的公路上有 $n$ 个限速标志，相对于公路起点的坐标和限速分别为 $d_i$ 和 $a_i$，其中 $a_i$ 表示在遇到下一个限速标识之前，每行驶 $1$ 千米 用时 $a_i$ 分钟。特别的，$d_1=0$。

现在你至多可以去掉 $k$ 个除第一个标识以外的标识（可以不去），问走完这条公路至少用时多少分钟。

### 解题思路
这个题还是比较一眼的，很容易想到 dp。看了一眼以前的题解，基本上都是二维的，现在提供一个模拟赛上想出来的三维 dp 解法。

设 $dp_{i,j,k}$ 表示已经到达第 $i$ 个标识，去掉了 $j$ 个标识，上一个没去掉的标识是 $i$ 时的最小用时。根据题意，初始状态是 $dp_{1,0,1}=0$。

先想一想能从哪转移到哪，根据题意有 $dp_{i,j,k}\rightarrow dp_{i+1,j+1,k}$ 和 $dp_{i,j,k}\rightarrow dp_{i+1,j,i+1}$。再根据题意给出限制，写出美丽的转移代码：

```
for(int j=0;j<min(i,k);++j){
	for(int l=1;l<=i;++l){
		int tmp=dp[i&1][j][l]+(d[i+1]-d[i])*a[l];
		chmin(dp[(i+1)&1][j+1][l],tmp);
		chmin(dp[(i+1)&1][j][i+1],tmp);
	}
}
if(k<i){
	for(int l=1;l<=i;++l){
		int tmp=dp[i&1][k][l]+(d[i+1]-d[i])*a[l];
		chmin(dp[(i+1)&1][k][i+1],tmp);
	}
}
```

最后统计答案就好了。

### AC 代码
```
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<db,db>
#define F first
#define S second
using namespace std;
const int N=5e2+5;
int n,l,k,d[N],a[N],dp[2][N][N],ans=0x3f3f3f3f;
void chmin(int &x,int y){
	if(y<x) x=y;
}
int main(){
	memset(dp,0x3f,sizeof dp);
	scanf("%d%d%d",&n,&l,&k);
	for(int i=1;i<=n;++i) scanf("%d",&d[i]);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	d[n+1]=l;
	dp[1][0][1]=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=k;++j) for(int l=1;l<=n+1;++l) dp[(i+1)&1][j][l]=0x3f3f3f3f;
		for(int j=0;j<min(i,k);++j){
			for(int l=1;l<=i;++l){
				int tmp=dp[i&1][j][l]+(d[i+1]-d[i])*a[l];
				chmin(dp[(i+1)&1][j+1][l],tmp);
				chmin(dp[(i+1)&1][j][i+1],tmp);
			}
		}
		if(k<i){
			for(int l=1;l<=i;++l){
				int tmp=dp[i&1][k][l]+(d[i+1]-d[i])*a[l];
				chmin(dp[(i+1)&1][k][i+1],tmp);
			}
		}
	}
	for(int i=0;i<=k;++i) for(int j=1;j<=n+1;++j) chmin(ans,dp[(n+1)&1][i][j]);
	printf("%d",ans);
	return 0;
}
//Ltwcfm.
```

---

## 作者：daniEl_lElE (赞：1)

## 思路

考虑二维 $dp_{i,j}$，状态的含义是看到第 $i$ 个路牌，**保留** $j$ 个路牌最快需要多长时间到达。虽然状态设计是二维的，但是由于我们需要考虑原来从哪个路牌调过两个之间的过来，需要 $O(n^3)$ 转移。

具体来讲，$dp_{i,j}=\min_{m=1}^{i-1}dp_{m,j-1}a_k\times(d_i-d_m)$。

然后最后输出对于所有 $i,j$ 大于等于 $n-k$，$\min(dp_{i,j}+a_i\times(l-d_i))$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[505][505];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int n,l,k;
	cin>>n>>l>>k;
	int a[n+1],b[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			dp[i][j]=1145141919810;//赋给变量一个很大的初值~~114514泛指一个数很大~~。
		}
	}
	dp[1][1]=0;
	for(int i=2;i<=n;i++){
		for(int j=2;j<=n;j++){//推荐 i,j 从 2 开始循环。
			for(int l=1;l<i;l++){//注意小于 i 而不是小于等于
				dp[i][j]=min(dp[i][j],dp[l][j-1]+b[l]*(a[i]-a[l]));//状态转移方程。
			}
		}
	}
	int minv=1145141919810;
	for(int i=1;i<=n;i++){
		for(int j=n-k;j<=n;j++){//我们是变换过的，所以把题目中的删除小于等于 k 个转换成了保留大于等于 n-k。
			minv=min(minv,dp[i][j]+b[i]*(l-a[i]));//结尾部分统计
		}
	}
	cout<<minv;
	return 0;
}
/* things to check
1.  int overflow or long long memory need
2.  recursion/array/binary search/dp/loop bounds
3.  precision
4.  special cases(n=1,bounds)
5.  delete debug statements
6.  initialize(especially multi-tests)
7.  = or == , n or m ,++ or -- , i or j , > or >= , < or <= , - or =
8.  keep it simple and stupid
9.  do not delete, use // instead
10. operator priority
11. is there anything extra to output?
12. if you don't know where the bug is , try to clear some parts of the code
 and check each part seperately.
13. ...
*/

```

---

## 作者：GeXiaoWei (赞：0)

# CF1625C Road Optimization
## 解析
通过数据 $1\le n \le500，1\le L\le10^5,0\le k\le n-1$ 可知，直接搜索会超时，应使用动态规划。

在本题中，如果我们令 $dp_{i,j}$ 表示前 $i$ 个限速牌删掉了 $j$ 个，那么你就会发现推不出来任何公式。

如果设 $dp_{i,j}$ 表示前 $i$ 个限速牌**连续**删掉了 $j$ 个，那么可得公式 $dp_{i,j}=\min(dp_{i,j},dp_{i-t-1,j-t}+(a_i-a_{i-t-1})\times b_{i-t-1})$，其中 $a_i$ 表示第 $i$ 个限速标志在离首都 $d_i$ 公里的位置，$b_i$ 表示每公里行驶时间不能小于 $a_i$ 分钟，$t$ 表示连续删除 $t$ 个，这样就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l,k,a[505],b[505],dp[505][505],ans=0x3f3f3f3f;
int main(){
    scanf("%lld %lld %lld",&n,&l,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
    memset(dp,0x3f3f3f3f,sizeof(dp));a[n+1]=l;
    for(int i=0;i<=k;i++) dp[1][i]=0;
    for(long long i=2;i<=n+1;i++){
        for(long long j=0;j<=min(i-1,k);j++){
            for(int t=0;t<=j;t++){
                dp[i][j]=min(dp[i][j],dp[i-t-1][j-t]+(a[i]-a[i-t-1])*b[i-t-1]);
            }
        }
    }
    for(int i=0;i<=k;i++) ans=min(ans,dp[n+1][i]);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：I_AK_IOI_6645 (赞：0)

### [CF1625C](https://www.luogu.com.cn/problem/CF1625C)
不难看出是一道动规，既然是动规那就会有状态转移方程，这里直接讲二维形式的动规，这就涉及到一个很有用但不是常见的设状态方法了，这里的 $f$ 表示到达第 $i$ 个限速牌时连续删掉了 $j$ 个，假设在删 $j$ 个之前我们要可以从 $i-2,j-1$ 转移来的所以可以设从删除了 $t$ 个的地方转移来，那么状态转移方程就来了
$$f_{i,j} = \min( { f_{i,j}},{f_{i-t-1,j-t}+(d_i-d_{i-t-1}) \times a_{i-t-1}) }$$
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,L,k;
int a[505],d[505];
int f[505][505];
int main(){
	memset(f,0x3f,sizeof f);//因为要求最小所以赋个特大的
	cin>>n>>L>>k;
	for(int i = 1;i<=n;i++){
		cin>>d[i];
	}
	for(int i = 1;i<=n;i++){
		cin>>a[i];
	}
	d[n+1] = L;//存储终点
	for(int i = 0;i<=k;i++){
		f[1][i] = 0;//赋初始值，因为在第一个限速牌就算全拆了也没用
	}
	for(int i = 2;i<=n+1;i++){//枚举当前位置
		for(int j = 0;j<=min(k,i-1);j++){//枚举拆牌的数量
			for(int t = 0;t<=j;t++){//开始准备转移
				f[i][j] = min(f[i][j],f[i-t-1][j-t]+(d[i]-d[i-t-1])*a[i-t-1]);
			}
		}
	}
	int ans = 1e9+7;
	for(int i = 0;i<=k;i++){
		ans = min(ans,f[n+1][i]);//因为不一定全都拆完所以可以求一下最小的时间
	}
	cout<<ans;//输出
}

---

## 作者：Graph_Theory (赞：0)

#### 0.题意

一条长度为 $l$ 的路上，有 $n$ 个限速指示牌分别距离起点 $b$，限速 $a$。求去掉**不多于** $k$ 个指示牌后通过这条路要多长时间。

#### 1.设状态 

我们设置 $dp_{i,j}$ 表示在第 $i$ 个指示牌**连续**拆掉**不多于** $j$ 个指示牌后从起点到当前指示牌最快的时间。

#### 2.列转移方程
为了成功的跑到终点，那么我们需要在 $d_{n+1}$ 的位置添加整个路的长度，此时 $a_{n+1}$ 与取值无关，可以取任意值。

因为是不多于 $k$，所以我们通过枚举 $p(0\to j)$ 表示删除从 $i$ 到 $(i-p-1)$ 的路牌此时每一次计算路程 $dp_{i,j}$ 取最小值后当 $dp_{i,j}$ 下一次作为被转移的使用时，就做到了间隔的效果。也就是下一步的 $dp_{i-p-1,j-p}$ 是包含删除与不删除的路牌计算的时间。

这里说明一下，计算 $i$ 和 $i-p-1$ 两点的距离是 $(d_{i}-d_{i-p-1})$ 乘上速度 $a_{i-p-1}$ 就得出了删除从 $i$ 到 $i-p-1$ 两点所有路牌时走完这段路需要的时间。

所需时间就是 $dp_{i-p-1,j-p}+(d_{i}-d_{i-p-1})\times a_{i-p-1}$。

接着在每一次枚举 $p(0\to j)$ 取最小值，就得到了状态转移方程 $dp_{i,j}=\min(dp_{i,j},dp_{i-p-1,j-p}+(d_{i}-d_{i-p-1})\times a_{i-p-1})$

代码：
```cpp
for(int i=2;i<=n+1;i++)
	for(int j=0;j<=min(i-1,k);j++)
		for(int p=0;p<=j;p++)
			dp[i][j]=min(dp[i][j],dp[i-p-1][j-p]+(d[i]-d[i-p-1])*a[i-p-1]);

```
#### 3.最终状态
最终状态是 $\min(dp_{n+1,1\to k})$ 表示在终点拆掉不多余 $k$ 个指示牌后从起点到终点最快的时间。

代码
```cpp
ans=MAX_INT;
for(int i=0;i<=k;i++)
		ans=min(dp[n+1][i],ans);
```

---

## 作者：Xiphi (赞：0)

dp 好题。考虑暴力 dp，设 $dp_{i,j,k}$ 表示，以 $i$ 为结尾，已删除 $j$ 个限速牌，以 $i$ 为结尾以删除 $k$ 个路牌的最小时间。至于为什么要加第三维，是因为如果是连续删除的话，速度就不是 $a_{i-1}$ 了，而是 $a_{i-k-1}$。

这样会 MLE，发现最后一位是冗余的，对后续转移毫无作用，于是优化成 $dp_{i,j}$ 表示以 $i$ 为结尾，已删除 $j$ 个限速牌的最小时间。然后转移时枚举连续删除了几个路牌即可。转移见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[505][505],n,l,k,a[505],d[505];
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>l>>k;
    memset(dp,0x3f,sizeof dp);
    for(int i=1;i<=n;++i) cin>>d[i];
    for(int i=1;i<=n;++i) cin>>a[i];
    d[n+1]=l;
    int ans=2e9;
    for(int i=0;i<=k;i++) dp[1][i]=0;
    for(int i=2;i<=n+1;++i){
		for(int j=0;j<=min(i-1,k);++j){
			for(int k=0;k<=j;++k){
				dp[i][j]=min(dp[i-k-1][j-k]+(d[i]-d[i-k-1])*(a[i-k-1]),dp[i][j]);
				if(i==n+1) ans=min(ans,dp[i][j]);
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

我们定义 $v_i=\frac{1}{a_i}$，那么我们知道只有 $v$ 单调下降的点才有效，所以我们可以抛弃那些上升的点 $i$（即 $v_i>v_j$）作为一个小小的优化，当然本题 $n$ 显然不需要这种优化。

我们设置 dp 状态 $dp_{i,j}$ 表示考虑到第 $i$ 个路标，选择 $j$ 个路标时的花费的最少时间（**仅记录到第 $i$ 个路标的用时**）。这是一种很常用的 dp 状态。那么我们怎么样去转移呢？我们可以从那些地方转移呢？

很显然的是我们的 $i$ 可以从 $i-k-1\sim i-1$ 转移过来。所以在转移时我们需要 $3$ 层循环。

- $i$ 枚举当前考虑的路标

- $j$ 枚举选择了的路标数目

- $l$ 枚举以 $i$ 为结尾我们连续选择几个路标，即我们从哪里转移过来。

转移时我们有两种可能：选择一些路标导致产生了影响，或者选择路标/不选择路标而没有影响。

- 产生了影响 $dp_{i,j}←dp_{i-l-1,j-l}+a_{i-l-1}\times (d_i-d_{i-l-1})$。

- 没有产生影响 $dp_{i,j}←dp_{i-1,j}+a_{i-1}\times (d_i-d_{i-1})$，这种情况我们让 $l=0$ 即可。

然后我们就可以愉快的写代码力。

## 代码

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long


#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


const int N=5e2+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;

int q;
int t,ans,a[M],mn=INF,mx;
int l,r;
int dp[N][N];
int d[M];

bool f2;


signed main(){
	// freopen("xor.in","r",stdin);
	// freopen("xor.out","w",stdout);
	n=rd,l=rd,k=rd;
	for(int i=0;i<n;i++){
		d[i]=rd;
	}
	d[n]=l;
	for(int i=0;i<n;i++){
		a[i]=rd;
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=min(i-1,k);j++){
			for(int l=0;l<=j;l++){
				dp[i][j]=min(dp[i][j],dp[i-l-1][j-l]+a[i-l-1]*(d[i]-d[i-l-1]));
			}
		}
	}
	ans=INF;
	for(int i=0;i<=k;i++)ans=min(ans,dp[n][i]);
	cout<<ans<<endl;

	return 0;
}

/*
2
3 2 3 6
*/

```




---

## 作者：yandbby (赞：0)

## Road Optimization

 [CodeForces - 1625C ](https://vjudge.net/problem/CodeForces-1625C/origin)

看到本题题解并不多，激动地写下本蒟蒻第一篇题解（卡了三天了，虽然这几天都在摸鱼）。

### 思路

用 $dp[i][j]$ 数组表示前 $i$ 段路去掉 $j$ 个路牌之后通过路的最短时间（注意题意是**至多**去 $j$ 个牌子，实际上会存在去一个牌子导致总时间反而增加的情况，出答案的时候记得计算 $dp[n][k_0], 0 \le k_0 \le k$ 的最小值），$lim[i]$ 表示第  $i$ 段路的速度限制，$d[i]$ 表示第 $i$ 个路标距离起点的距离。

从 $i = 1$ 开始 dp，状态转移的过程可以看做是往这条路上依次添加**去牌子路段**或**不去牌子路段**。

我一开始得出的状态转移方程是：

$dp[i][j] = min(dp[i - 1][j] + lim[i] * (d[i + 1] - d[i]), dp[i - 1][j - 1] + lim[i - 1] * (d[i + 1] - d[i]))$

其意义是，已知前 $i - 1$ 段路的 dp 结果，考虑该段路前的牌子去和不去两种情况，取两种情况的最小值。

然鹅这个方程式错的。

原因是当第i段路前有去掉的牌子，导致产生**连续**去掉牌子的情况，$dp[i - 1][j - 1] + lim[i - 1] * (d[i + 1] - d[i]))$ 中的 $lim[i - 1]$ 就不适用了。

解决方法我看大佬们有增加一维滚动数组的，我自己也想过引入 $pre[i][j]$ 数组记录最近一个没被去掉的牌子的方法。

但我有另一个思路：

既然要在去牌子的后边继续添加去牌子路段很麻烦，我们不如**一次性把去牌子路段加完**，并且**不再往去牌子路段后面再加去牌子路段**。

先上核心代码：

```c++
memset(dp, 0x3f, sizeof(dp));
dp[0][0] = 0;
for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i && j <= k; ++j) {
        //此时dp[i][j]已经是结尾为去牌路段的最小值,还要考虑最后一段路不去牌的情况  
        if (dp[i][j] > dp[i - 1][j] + lim[i] * (d[i + 1] - d[i])) {
            dp[i][j] = dp[i - 1][j] + lim[i] * (d[i + 1] - d[i]);
            for (int l = 1; l + j <= k && l + i <= n; ++l) {//添上长度为l的连续去牌路段
                dp[i + l][j + l] = min(dp[i + l][j + l], dp[i][j] + lim[i] * (d[i + l + 1] - d[i + 1]));
            }
        }
    } 
}
```

分析：

1. 最外层 `for` 循环模拟从 $1$ 到 $n$ 向整体中加路段。

2. 第二层对于路段 $i$ 遍历每个 $dp[i][j]$。

3. 第三层遍历**添加的去牌子路段长度**，向 $dp[i + l][j + l]$ 进行状态转移。

4. 每个第二层循环开始的时候，$dp[i][j]$ 已经是**任意以不去牌子路段结尾的路段**加上**连续几段去牌子路段**的**组合**的最小值，

   还差了一种情况：**以不去牌子路段结尾**，于是加入到最小值的计算中。

   我们之前提到**不再往去牌子路段后面再加去牌子路段**也就是说**只往不去牌子路段后面加去牌子路段**所以加了个 `if` 判断。

另外，注意 $i + l$ 和 $j + l$ 的范围限制，避免数组越界和算力浪费。

### 完整AC代码

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int MAXN = 550, INF = 0x3f3f3f3f;
int dp[MAXN][MAXN], ans;//前n段去k个牌子后通过所用的最短时间
int n, l, k;//管道价格，柱子价格
int d[MAXN], lim[MAXN];//距离，限制时间

inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    n = read(), l = read(), k = read();
    for (int i = 1; i <= n; ++i) {
        d[i] = read();
    }
    d[n + 1] = l;
    for (int i = 1; i <= n; ++i) {
        lim[i] = read();
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i && j <= k; ++j) {
            //此时dp[i][j]已经是结尾为去牌路段的最小值,还要考虑最后一段路不去牌的情况  
            if (dp[i][j] > dp[i - 1][j] + lim[i] * (d[i + 1] - d[i])) {
                dp[i][j] = dp[i - 1][j] + lim[i] * (d[i + 1] - d[i]);
                for (int l = 1; l + j <= k && l + i <= n; ++l) {//添上长度为l的连续去牌路段
                    dp[i + l][j + l] = min(dp[i + l][j + l], dp[i][j] + lim[i] * (d[i + l + 1] - d[i + 1]));
                }
            }
        } 
    }
    ans = dp[n][0];
    for (int j = 1; j <= k; ++j) ans = min(ans, dp[n][j]);
    cout << ans << endl;
    return 0;
}
```

大一蒟蒻一枚，如有错误请大佬指正(明天就校赛了我还在这里写题解=-=)。

---

## 作者：mcDinic (赞：0)

真要被气死，第一次审题错误，看了原文后重新打代码，第二次又发现自己审题错了，然后总共一个小时才搞定······

讲下思路吧，这题算是较为简单的动态规划，令 $dp_{i,j,k}$ 表示到第 $i+1$ 个标志，以第 $j$ 个标志为限速标准，移除 $k$ 个标志花的最少时间。但是我们发现这样空间会炸，就把第一维压掉，状态转移方程很简单，看代码吧。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,L,K,dp[505][505],d[505],a[505],ans=0x3f3f3f3f;
signed main(){
	memset(dp,0x3f3f3f3f,sizeof(dp));
	scanf("%lld%lld%lld",&n,&L,&K),d[n+1]=L;
	for(int i=1;i<=n;i++)scanf("%lld",&d[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	dp[1][0]=a[1]*(d[2]-d[1]);
	for(int i=2;i<=n;i++){
		for(int j=n;j>=1;j--){
			for(int k=K;k>=0;k--){
				if(j==i){
					for(int l=0;l<i;l++)dp[j][k]=min(dp[j][k],dp[l][k]+(d[i+1]-d[i])*a[i]);
					continue;
				}
				if(k==0||a[j]>a[i]||j>i){dp[j][k]=0x3f3f3f3f;continue;}
				dp[j][k]=dp[j][k-1]+a[j]*(d[i+1]-d[i]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=K;j++)
			ans=min(ans,dp[i][j]);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Ishy (赞：0)

## Road Optimization

### Solution 1

设 $f_{i,j,k}$ 表示考虑前 $i$ 个位置，移除了 $j$ 个路标，$i$ 位置时速度为 $a_k$ 的最短时间。

则 $f_{i,j,k}$ 可以推至 $f_{i+1,j,?}$ 和 $f_{i+1,j+1,?}$。

令 $d_i=pos_{i+1}-pos_i$。

- $f_{i,j,k} \to f_{i+1,j,i+1}: f_{i+1,j,i+1}=f_{i,j,k}+d_{i+1}\times a_{i+1}$，速度改变。
- $f_{i,j,k} \to f_{i+1,j+1,k}: f_{i+1,j+1,k}=f_{i,j,k}+d_{i+1} \times k$，速度不变。

边界为 $f_{1,0,1}=0$。

答案为 $\min\limits_{0\leq j\leq K,1 \leq k\leq n}f_{n,j,k}$。第一维可用滚动数组进行优化。

### Solution 2

正难则反。设 $f_{i,j}$ 表示考虑前 $i$ 个位置，其中有 $j$ 个未被移除的最短时间。(指走完前 $i$ 段路)

- $f_{i,j}\to f_{x,j+1}:f_{x,j+1}=f_{i,j}+(pos_{x+1}-pos_{i+1}\times a_{i+1})$，其中转移实质为第 $i$ 个位置时变速，一直到位置 $x$ 时速度都保持不变。由题可知，变速的位置不会被移除掉。

边界为 $f_{0,0}=0$。

由于最多只能移除 $k$ 个位置，所以至少要有 $n-k$ 个位置被保留下来。

答案为 $\min\limits_{n-k\leq i\leq n}f_{n,i}$。已经够优了。  

现在给出第二种解法的代码。至于第一种解法，大家可以自行思考并实现。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,l,k;
int pos[N],a[N];
int f[N][N],ans;
//f[i][j]:考虑前i个位置 保留j个位置 的最短时间 
int main()
{
	scanf("%d%d%d",&n,&l,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&pos[i]);
	pos[n+1]=l;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			for(int x=i+1;x<=n;x++)
				f[x][j+1]=min(f[x][j+1],f[i][j]+(pos[x+1]-pos[i+1])*a[i+1]); 
	ans=INT_MAX; 
	for(int i=n-k;i<=n;i++)
		ans=min(ans,f[n][i]);
	printf("%d\n",ans);
	return 0;
}
```



---

