# [USACO02FEB] Cow Cycling

## 题目描述

奶牛自行车队由 $N$ 名队员组成，他们正准备参加一个比赛，这场比赛的路程共有 $D$ 圈。车队在比赛时会排成一条直线，由于存在空气阻力，当骑车速度达到每分钟 $x$ 圈时，领头的奶牛每分钟消耗的体力为 $x^2$，其它奶牛每分钟消耗的体力为 $x$。每头奶牛的初始体力值都是相同的，记作 $E$。如果有些奶牛在比赛过程中的体力不支，就会掉队，掉队的奶牛不能继续参加比赛。每支队伍最后只要有一头奶牛能到终点就可以了。

比赛规定，最小的计时单位是分钟，在每分钟开始的时候，车队要哪头奶牛负责领头，领头奶牛不能在这分钟内掉队，每分钟骑过的圈数也必须是整数。

请帮忙计划一下，采用什么样的策略才能让车队以最快的时间到达终点？

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/spwg7uf6.png)

## 样例 #1

### 输入

```
3 30 20```

### 输出

```
7```

# 题解

## 作者：caeious (赞：13)

这里给大家提供一个**二维dp**的做法。  
观察到必有至少一种最优解，使得每头牛领头的时间都是是一整段。可以用反证法证明如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/wakqxen5.png)

又观察到牛与牛之间没有区别。所以可以用 $dp[i][j]$ 表示一头剩余体力为 $i$ 的牛一连领头 $j$ 圈最少要几分钟，枚举第一分钟速度 $k$ 可得
$$dp[i][j] = \min \{ dp[i - k^2][j-k] + 1 \mid 1 \leq k \leq j,k^2 \leq i\}$$  
边界条件：$dp[0...E][0] = 0$

再用 $f[i][j]$ 表示还剩 $i$ 头牛没 ~~AFO~~ 体力不支，还有 $j$ 圈要骑，最少需要几分钟。枚举第一头牛领头圈数 $k$ 可得
$$f[i][j] = \min\{f[i - 1][j - k] + dp[E - (D - j)][k] \mid 0 \leq k \leq j\}$$

边界条件：$f[0][0] = 0, f[0][1...D] = \infty$  

最后的答案就是 $f[n][D]$ 的值。

复杂度是 $O(E^{1.5}D + nD^2)$，本题中约为 $10^5$，~~可以加强数据~~可以轻松跑到最优解（2019 年 1 月及之前）。

### Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <utility>
#include <set>
//#define LOCAL
#define maxe 105
#define maxd 105
#define maxn 25
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,E,D;
int dp[maxe][maxd],f[maxn][maxd];
int main(){
	#ifdef LOCAL
	freopen("sample.in","r",stdin);
	freopen("sample.out","w",stdout);
	#endif
	scanf("%d%d%d",&n,&E,&D);
	if(E < D){
		puts("0");
		return 0;
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<=E;i++) dp[i][0] = 0;
	for(int i=1;i<=E;i++){
		for(int j=1;j<=D;j++){
			for(int k=1;k <= j && k * k <= i;k++){
				dp[i][j] = min(dp[i][j],dp[i - k * k][j - k] + 1);
			}
		}
	}
	memset(f,0x3f,sizeof(f));
	f[0][0] = 0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=D;j++){
			int p = D - j;
			for(int k=0;k<=j;k++){
				f[i][j] = min(f[i][j],f[i - 1][j - k] + dp[E - p][k]);
			}
		}
	}
	printf("%d\n",f[n][D]);
	return 0;
}

```

---

## 作者：cff_0102 (赞：8)

考虑 dp。设 $dp_{i,j,k}$ 表示要到达还剩 $i$ 个奶牛，领头的体力剩 $j$，且其它牛体力剩 $k$ 的状态，最少需要的时间。

从后往前 dp，每次枚举这一分钟要骑的圈数，然后分要不要换一个领队的情况讨论并转移即可。

具体的，这一分钟骑 $c$ 圈时，若不换一个领队，那么 $dp_{i,j-c^2,k-c}=dp_{i,j,k}+1$，否则 $dp_{i-1,k-c^2,k-c}=dp_{i,j,k}+1$，这里要取最小值。

最后需要令 $k=e-d$，枚举所有的 $i$ 和 $j$，然后选出最小的那个答案，因为总共骑 $d$ 圈的话后面的奶牛剩余体力一定是 $e-d$。如果 $i=1$ 或 $0$ 也没关系，同样可以直接用 $dp_{i,j,k}$。

时间复杂度 $O(NE^2D)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define chmin(x,y) x=min(x,y)
using namespace std;
const int N=101;
int dp[N][N][N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,e,d;cin>>n>>e>>d;
	if(e<d)return cout<<0,0;
	memset(dp,0x3f,sizeof dp);
	dp[n][e][e]=0;
	for(int i=n;i>=1;i--){
		for(int j=e;j>=0;j--)for(int k=e;k>=0;k--){
			for(int ci=1;ci<=d;ci++){
				if(j-ci*ci>=0&&k-ci>=0)chmin(dp[i][j-ci*ci][k-ci],dp[i][j][k]+1);
				if(k-ci*ci>=0&&k-ci>=0)chmin(dp[i-1][k-ci*ci][k-ci],dp[i][j][k]+1);
			}
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=e;j++){
			ans=min(ans,dp[i][j][e-d]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ZZJ__ (赞：7)

看到这玩意没有题解，我来发一波。这也是蒟蒻第一篇发的题解，写的不好见谅。

首先题目大意就是n名队员，消耗体力值x，初始体力为e，求最先到达终点的奶牛的时间是多少。

明显我们知道用动态规划，那么怎么做呢？
首先我们可以用f[i][j][k]记录当前还有i头牛，领头的还有j点体力，其余的还有k点体力，用了多长时间。 
至于处理答案，每一头牛都有他的体力值，那么f[i][j][k]，每一头牛假设都可以当领头，那么他消耗的体力就是跑的圈数是多少，所以e-d就是终点，所以只要求出f[i][j][e-d]就可以了

代码如下：请勿复制，小心粽名哦！！

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,e,d,f[110][110][110],ans=2147483647;//数组开大了不介意，因为一般我都是n个一然后补零都是两个两个补的。
int main()
{
    scanf("%d%d%d",&n,&e,&d);
    memset(f,127,sizeof(f));//一开始初始化，因为求最小值，我们弄到最大
    f[n][e][e]=0;//开始n头牛，领头的都有e体力，一共体力满的
    for(int i=n;i>=1;i--)
    {
        for(int j=e;j>=0;j--)
        {
            for(int k=e;k>=0;k--)
            {
                for(int x=1;x<=10;x++)//
                {
                    if(j-x*x>=0&&k-x>=0) f[i][j-x*x][k-x]=min(f[i][j-x*x][k-x],f[i][j][k]+1);
                    if(k-x*x>=0) f[i-1][k-x*x][k-x]=min(f[i-1][k-x*x][k-x],f[i][j][k]+1);
                    
                    //这里考虑特殊情况。如果当前的体力本来就足，否则根本跑不了。
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=e;j++) ans=min(ans,f[i][j][e-d]);//最后和之前说的一样只要求出f[i][j][终点]就行了
    }
    printf("%d",ans);
    return 0;//程序再见
}
```

---

## 作者：devout (赞：5)

一道比较好想代码也非常好写的一道dp题

因为牛都一样，所以我们可以考虑让一只牛领头，一直领到他累死。

用 $f[i][j][k]$ 表示现在已经死了 $i$ 只牛，现在领头的牛有 $j$ 的体力，已经跑了 $k$ 圈时的最快用时。

显然转移分为两种情况，一种是领头的牛继续领头，另一种是领头的牛不再领头，相当于累死了，这个时候我们就需要换一头新的牛来领头。

注意转移的方向，$j$ 应当从大往小枚举

复杂度大概是 $O(ne\sqrt ed)$ 这个级别的（

```cpp
# include <bits/stdc++.h>

using namespace std;

# define Rep(i,a,b) for(register int i=a;i<=b;i++)
# define _Rep(i,a,b) for(register int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=3e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,e,d;
int f[25][105][105];
int ans=INT_MAX; 

int main()
{
	memset(f,0x3f,sizeof(f));
	read(n),read(e),read(d);
	f[0][e][0]=0;
	Rep(i,0,n)
		_Rep(j,e,0)
			Rep(k,0,d){
				int q=1;
				while(q*q<=j&&k+q<=d){
					f[i][j-q*q][k+q]=min(f[i][j-q*q][k+q],f[i][j][k]+1);
					f[i+1][e-k-q][k+q]=min(f[i+1][e-k-q][k+q],f[i][j][k]+1);
					q++;	
				}
			}
	Rep(i,0,n-1)
		Rep(j,0,e)
			ans=min(ans,f[i][j][d]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：CznTree (赞：3)

这道题看着紫题，看着很唬人，但是我们使用伟大的 *** 的分析方法，就能轻而易举的分析出**暴力**的 DP 方法。

参考 Lqy 的题解。

### 题解


对于每只牛领头的速度，进行讨论。有 $N$ 头牛，它们均有 $E$ 点体力，要跑 $D$ 圈。速度使用情况为 $T$， 而 $T = \{s_1, s_2, s_3,..., s_k\}$，奶牛的使用顺序是 $1$ 到 $n$。

当 $s_k = i$，并且使用奶牛为 $e$ 时。剩下的奶牛能组成 $e$ 头奶牛，第 $e$ 头奶牛的体力就是 $E - i^2$，除此之外的奶牛的体力就是 $E - i$ ，跑 $D - i$ 圈。此时的 $e$ 只能是 $n$。为什么呢？因为本身他就只剩下 $N$ 头牛了，体力还是一样的，那 $e$ 肯定只能为 $n$ 了。

设  $T_{i,j,k,l} = \{s_1, s_2, s_3, ... s_k\}$，意思就是剩余 $i$ 头奶牛，第 $i$ 头奶牛的体力为 $j$，其他奶牛的体力为 $k$，跑 $l$ 圈为最佳速度使用情况，$dp_{i,j,k,l}$ 为最小使用时间。

此时的 $e$ 可能是 $i$，也有可能是 $i - 1$。

我们讨论一下：

- 当 $s_k = x$，且奶牛为 $i$ 的时候，$dp_{i,j,k,l} = dp_{i,j-x^2,k-x,l-x} + 1$。

- 当 $s_k = x$，且奶牛为 $i - 1$ 的时候，$dp_{i,j,k,l} = dp_{i-1,k-x^2,k-x,l-x} + 1$。

给出暴力 DP 代码：

```cpp
#include <bits/stdc++.h> 
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr) 
#define rep(i, a, b) for (int i = a; i <= b; i++) 
#define per(i, a, b) for (int i = a; i >= b; i--)
#define lc(x) x << 1ll 
#define rc(x) x << 1ll | 1ll
#define lowbit(x) ((x) & (-x))
#define LEN_LC (tree[lc(i)].r - tree[lc(i)].l + 1) 
#define LEN_RC (tree[rc(i)].r - tree[rc(i)].l + 1) 
#define LEN (tree[i].r - tree[i].l + 1)  
#define int long long
const int N = 20 + 7; 
const int E = 100 + 7; 
const int inf = INT_MAX; 
template<typename T>inline void read(T &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
int dp[N][E][E][E];
void solve() {
	int n, e, d; 
	read(n), read(e), read(d);
	memset(dp, 0x3f, sizeof dp); 
	rep(i, 0, n) {
		rep(j, 0, e) {
			rep(k, 0, e) {
				dp[i][j][k][0] = 0; 
			}
		}
	} 

	rep(i, 1, n) {
		rep(j, 0, e) {
			rep(k, 0, e) {
				rep(l, 0, d) {
					rep(s, 1, 10) {
						if(j - s * s >= 0 && k - s >= 0 && l - s >= 0) {
							dp[i][j][k][l] = std::min(dp[i][j][k][l], dp[i][j - s * s][k - s][l - s] + 1); 
						}

						if(i > 1 && k - s * s >= 0 && l - s >= 0) {
							dp[i][j][k][l] = std::min(dp[i][j][k][l], dp[i - 1][k - s * s][k - s][l - s] + 1);
						} 
					}
				}
			}
		}
	}

	int min = inf; 
	rep(i, 0, e) {
		rep(j, 0, e) {
			min = std::min(min, dp[n][i][j][d]);
		}
	}

	if(min > inf / 2) std::cout << 0 << std::endl; 
	else std::cout << min << std::endl;
}
signed main() {
	solve(); 
	return 0; 
}
```

时间复杂度为 $O(ne^2d)$，空间复杂度高达 $O(ne^2d)$，显然这个空间复杂度完全无法通过本题，只能通过如空间限制较大的情况。


怎么优化呢？

其实这个 $l$ 完全可以省略，那么就变成了剩余 $i$ 头奶牛，第 $i$ 头奶牛的体力为 $j$，其他奶牛的体力为 $k$。不难发现，消耗的体力就是跑的圈数。

对于循环，可以进行反向迭代，那么则初始化应为 `dp[n][e][e] = 0`，因为体力是满的。而因为消耗的体力就是跑的圈数，所以 $e-d$ 就是终点。

代码：

```cpp
#include <bits/stdc++.h> 
#define IOS std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr) 
#define rep(i, a, b) for (int i = a; i <= b; i++) 
#define per(i, a, b) for (int i = a; i >= b; i--)
#define lc(x) x << 1ll 
#define rc(x) x << 1ll | 1ll
#define lowbit(x) ((x) & (-x))
#define LEN_LC (tree[lc(i)].r - tree[lc(i)].l + 1) 
#define LEN_RC (tree[rc(i)].r - tree[rc(i)].l + 1) 
#define LEN (tree[i].r - tree[i].l + 1)  
#define int long long
const int N = 20 + 7; 
const int E = 100 + 7; 
const int inf = INT_MAX; 
template<typename T>inline void read(T &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
int dp[N][E][E];
void solve() {
	int n, e, d; 
	read(n), read(e), read(d);
	memset(dp, 0x3f, sizeof dp); 
	/* rep(i, 0, n) {
		rep(j, 0, e) {
			rep(k, 0, e) {
				dp[i][j][k][0] = 0; 
			}
		}
	} */ 
    dp[n][e][e] = 0; 
	per(i, n, 1) {
		per(j, e, 0) {
			per(k, e, 0) {
					rep(s, 1, 10) {
						if(j - s * s >= 0 && k - s >= 0) {
							dp[i][j - s * s][k - s] = std::min(dp[i][j][k] + 1, dp[i][j - s * s][k - s]); 
						}

						if(k - s * s >= 0) {
                            dp[i - 1][k - s * s][k - s] = std::min(dp[i][j][k] + 1, dp[i - 1][k - s * s][k - s]);
						} 
					}
			}
		}
	}

	int min = inf; 
	rep(i, 1, n) {
		rep(j, 0, e) {
			min = std::min(min, dp[i][j][e - d]);
		}
	}

	if(min > inf / 2) std::cout << 0 << std::endl; 
	else std::cout << min << std::endl;
}
signed main() {
	solve(); 
	return 0; 
}
```

时间复杂度应该是 $O(n \times e^2)$

---

## 作者：huhangqi (赞：1)

一眼动态规划。

但是我们状态怎么设置？

我们分析题目，可以发现一个领头一定要开到最后，不再成为领头。

原因很简单，如果你把这只领队重新放回队尾，那么它在其它奶牛领队后跑了几圈，它最后能跑的圈数比其他没有跑过的少得更多，自然是希望在前面跑完以后就不再领跑。

这样我们就简化了题目，目前需要记录已经领跑了的奶牛数量以及跑了的圈数和目前领队的电量。

那么状态设计完成了，方程怎么转移？

三个状态分析起来对于我这种蒟蒻来说还是太难了，所以我选择无脑记搜。

只需要考虑是选择继续作为领队还是换一个领队和跑的圈数即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,dp[25][105][105];
bool vis[25][105][105];
int dfs(int p,int x,int z){
	if(x>=s)return 0;
	if(p>n)return 1e9;
	if(vis[p][x][z])return dp[p][x][z];
	vis[p][x][z]=1;
	int &res=dp[p][x][z];
	for(int i=1;i*i<=z&&x+i<=s;i++){
		res=min(res,dfs(p,x+i,z-i*i)+1);
		res=min(res,dfs(p+1,x+i,m-x-i)+1);
	}
	return res;
}
signed main(){
	memset(dp,0x3f,sizeof(dp));
	cin>>n>>m>>s;
	cout<<dfs(1,0,m);
	return 0;
}
``````

所以这怎么有紫？

---

## 作者：Modulus998244353 (赞：1)

### 解题思路

---

不难发现一个结论：每头奶牛领头的时间为一段连续的时间。（具体证明见楼上）

从这里可以推出，每头牛领头的时候，最优方案是直接让他~~凉~~。因为一头牛对车队的贡献为其在领头的时候，若其在领头之后每~~凉~~，则其在后面的时间只能跟着跑（由上述结论推出其不可能在一次领头），对车队无贡献。换句话说，就是一头牛在领头之后就对车队没有贡献。所以最优的方案就是直接让它~~凉~~。



又因为牛之间没有区别，所以可以设 $g_{i,j}$ 代表领头牛剩 $i$ 的体力，需要跑 $j$ 圈。则 $g$ 的递推式为：
$$
g_{i,j}=\sum_{k\le i \; k^2\le i}  \min(g_{i-k^2,j-k}+1)
$$
用 $f_{i,j}$ 代表还有 $i$ 头牛没凉，还要跑 $j$ 圈所需要的时间。递推式为：
$$
f_{i,j}=\sum_{0 \le k\le j} f_{i-1,j-k}+g_{e-(D-j),k}
$$
答案即为 $f_{n,D}$。

### 部分代码

---

~~~c++
for(int i=0;i<=e;i++) g[i][0]=0;
    for(int i=1;i<=e;i++){
        for(int j=1;j<=d;j++){
            for(int k=1;k<=j && k*k<=i;k++){
                g[i][j]=min(g[i][j],g[i-k*k][j-k]+1);
            }
        }
    }
    memset(f,inf,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=d;j++){
            int p=d-j;
            for(int k=0;k<=j;k++) f[i][j]=min(f[i][j],f[i-1][j-k]+g[e-p][k]);
        }
    }
~~~

---

## 作者：Dovе (赞：1)

### 【[题目](https://www.luogu.com.cn/problem/P4953)概述】
***

&#8195;有 $N$ 只牛，每只牛有 $E$ 的体力，需要绕 $D$ 圈

&#8195;绕圈有一只领头牛，其以 $X$圈$/min$ 的速度绕圈需要消耗 $X^2$ 的体力值，在其后方的牛需要消耗 $X$ 的体力

&#8195;问最快到达时间，如果不行，则输出 $0$

### 【大致分析】
***

&#8195;**明显**的 $Dp$ 题

&#8195;我们考虑一个**三维** $Dp$   

&#8195;用 $Dp[i][j][k]$ 表示：**还有 $i$ 头牛 领头还有 $j$ 点体力 其余还有 $k$ 点体力 时 花费的最小时间**

***

&#8195;**初始化**：全员 $INF$ ; $dp[n][E][E] = 0$ 

&#8195;**解释**：$dp[n][E][E]$ 表示 **刚刚出发的时的状态** , 则初始化为 $0$ 

***

&#8195;**转移方程的来源** (其中 $x$ 为 领头牛 的 速度 )：

* $Way1.$领头牛不换

  **条件：**$j-x*x >= 0$ **And** $k-x >= 0$ 
  
  **转移：**$dp[i][j-x*x][k-x] = min ( dp[i][j-x*x][k-x] , dp[i][j][k] + 1 ) $
  
* $Way2.$更换领头牛

  **条件：** $k-x*x >= 0$ **And** $k-x >= 0$[略] 
  
  **转移：** $dp[i-1][k-x*x][k-x] = min ( dp[i-1][k-x*x][k-x] , dp[i][j][k] + 1 )$ 
  
***
&#8195;**最终答案**

* $Q1.$**无解情况**

  **满足：** $E<D$ 时
  
  **解释：** 牛只有在每时每刻都以 $1$圈$/mi$n 的速度行进时才能够达到最远点。因为如果以更高的的速度 $X$圈$/min$ 进行时，消耗的体力 $X^2$ 远大于 $X$。所以当 $E<D$ 时 无解
  
* $Q2.$**正常情况**
   
  **答案：** 为 $min(dp[i][j][E-D])$ 
  
  **解释：** 不妨假设当前这头牛没有一次当过领队，及其消耗的体力值就为跑过的圈数$(E-D)$，所以最短的时间应为 $min(dp[i][j][E-D])$
  
### 【Code】
##### （仅供参考）
***
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=20+5;
const int maxe=100+5;
const int maxd=100+5;  //数据范围

const int INF=2147483647;  //定义最值（虽然没有用到）

int n,E,D; 

int dp[maxn][maxe][maxd];

int main()
{
	scanf("%d%d%d",&n,&E,&D);
	
	if(E<D) 
	{
		printf("0\n"); //处理无解情况
		return 0;
	}
	
	memset(dp,127,sizeof(dp));
	dp[n][E][E]=0;         //初始化
	
	for(register int i=n;i>=1;--i)
	  for(register int j=E;j>=0;--j)
	    for(register int k=E;k>=0;--k)  //三层循环枚举状态
	      for(register int x=1;x<=10;++x) //循环枚举领头速度
	        {
		      if(j-x*x>=0&&k-x>=0) dp[i][j-x*x][k-x]=min(dp[i][j-x*x][k-x],dp[i][j][k]+1);
		      if(k-x*x>=0) dp[i-1][k-x*x][k-x]=min(dp[i-1][k-x*x][k-x],dp[i][j][k]+1); 
			}
 
	int Ans_=INF;
    for(register int i=1;i<=n;++i)
      for(register int j=0;j<=E;++j)
        Ans_=min(Ans_,dp[i][j][E-D]);  //正常情况，统计结果
	
	printf("%d\n",Ans_); 
	return 0;
 } 
```

### 【总结】

* 观察题目信息，针对题目写 $Dp$ 状态

* 注意初始化信息，**通常来说**都需要 $INF$ 还有 $0$

* **转移方程**考虑从几个方面转来或转出




---

## 作者：Expert_Dream (赞：0)

一眼肯定是 DP 题，并且数据范围比较小，随便做。

首先，肯定是每一头领跑奶牛用尽了，才会出队，然后换下一个奶牛来领跑。

设 $dp_{i,j}$ 表示第 $i$ 头奶牛领队跑完之后的圈数为 $j$ 时，最小的速度。

设 $cost(d,e)$ 表示需要跑 $d$ 圈且领头奶牛耗费 $e$ 体力需要的最快时间。


所以可以得到转移方程：$dp_{i,j} = \min_{k=0}^{j-1} dp[i-1][k] + cost(j-k,E-k)$。

求 $cost(d,e)$：我们发现答案满足单调性，即可二分答案求解。

设 $cost(d,e) = t$，此领头奶牛跑第 $p$ 分钟可以跑 $x_p$ 圈。

所以得到 $\sum_{p=1}^t x_p= d$ 和 $\sum_{p=1}^t x_p^2 \leqslant e$。

那么此时，在确定了 $d$ 圈数和 $t$ 时间，我们尽可能让他们凑出一个较少的体力，从而满足 $\sum_{p=1}^t x_p^2 \leqslant e$。

显然，尽可能平均的将 $t$ 平均分给各个 $x_p$ 会使得体力较小。

例如 $e=22$，那么我们可以分配一个 $x=[5,5,6,6]$。此时最优解。

所以构造 $x$ 时，有 $d \mod t$ 个 $x_p = \left\lfloor\dfrac{d}{t}\right\rfloor + 1$ 和 $t - d \bmod t $ 个 $x_p = \left\lfloor\dfrac{d}{t}\right\rfloor $。

所以时间复杂度为 $O(ND^2 \log D)$。

```cpp
int n,e,d;
int dp[N][N];
bool check(int d,int e,int t){
    int cnt = d % t;
    return ((d/t)*(d/t)*(t-cnt) + (d/t+1)*(d/t+1)*(cnt)) <= e;
}
int f(int d,int e){
    int l=1,r=d,mid;
    while(l+5<r){
        mid = (l+r) >> 1;
        if(check(d,e,mid)){
            r=mid;
        }else{
            l=mid;
        }
    }
    For(i,l,r) if(check(d,e,i))return i;
}
void solve(	){
    cin >> n >> e >> d;
    mem(dp,0x3f);
    dp[0][0] = 0;
    For(i,1,n){
        For(j,1,d){
            For(k,0,j-1){
                dp[i][j] = min(dp[i][j],dp[i-1][k] + f(j-k,e-k));
            }
        }
    }
    int ans = 0x3f3f3f3f3f3f3f3f;
    For(i,1,n) ans=min(ans,dp[i][d]);
    if(ans == 0x3f3f3f3f3f3f3f3f) cout << 0;
    else cout<<ans;
}
```

---

## 作者：内拉组里 (赞：0)

水紫，最多只有绿的难度。

# Thoughts：

这种奶牛 **dp** 应该很容易看出来。

令 $ dp[i][j][k] $ 表示还剩 $ i $ 头奶牛在玩，领队的奶牛还有 $ j $ 格体力，

其余的最多还有 $ k $ 格体力，最小时间。

初始状态 $ dp[n][e][e] = 0 $，其余 $ dp[i][j][k] = \infin $。

决策点就是领队换与不换，一个显而易见的策略就是每次让领队跑死再换掉，

若最后一头奶牛都没有了，那就无法到达终点。~~话说好像没有这个点~~。

否则除领队以外其他的奶牛在最后一分钟冲刺时还有 $ e - d $ 格体力，因为没当过领队。

即 $ ans = \max \{ dp[i][j][e - d] \} $。

转移的话填表有点难写，所以采用刷表。

枚举速度 $ x $。

若更换领队，则有 $ dp[i][j - x^2][k - x] \le dp[i][j][k] + 1 $。

若不换领队，则有 $ dp[i - 1][k - x^2][k - x] \le dp[i][j][k] + 1 $。

转移的时候注意一下下标越界问题即可。

# Analyses：

> 总时间复杂度 $ \Theta (NE^2 \sqrt{E}) $。
>
> 总空间复杂度 $ \Theta (NE^2) $。

# Code：

```cpp
/* reference : @Luogu.ZZJ__ (118248) */
/* strategy : lead in turn and then drop out */
#include	<iostream>
#include	<cstring>
using namespace std;
constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 24;
constexpr int maxe = 104;

int n, e, d;
int dp[maxn][maxe][maxe];
/* dp[i][j][k] means the minimal time when are only [i] cows,the leader has [j] power left,while others have [k] */

signed main (void)
{
	cin >> n >> e >> d;
	memset (dp, 0x3f, sizeof dp);
	dp[n][e][e] = 0;
	int ans = inf;
	for (int i = n; i; i--)
	{
		for (int j = e; ~j; j--)
		{
			for (int k = e; ~k; k--)
			{
				for (int x = 1; x <= 10; x++)
				{
					if (j >= x * x && k >= x) dp[i][j - x * x][k - x] = min (dp[i][j - x * x][k - x], dp[i][j][k] + 1);	/* keep on leading */
					if (k >= x * x) dp[i - 1][k - x * x][k - x] = min (dp[i - 1][k - x * x][k - x], dp[i][j][k] + 1);	/* handover the position of leader */
				}
			}
			ans = min (ans, dp[i][j][e - d]);
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：qwer6 (赞：0)

数据范围十分小，我们不妨直接考虑记忆化解决。  
我们可以简单判断领队就是个一次性用品，只要从领队的位置上退下来，我们就不再考虑这只奶牛是否可以到达终点了。  
所以我们记录三个参数，表示现在是第 $p$ 头奶牛当领队（前面的奶牛已经被扔掉了），领队的奶牛还剩 $rem$ 体力，以及现在跑了 $now$ 圈。  
决策就是这一分钟跑几圈，注意要保证领队可以跑完，也就说最多可以跑 $\sqrt {rem}$ 圈，总状态数 $n\times m\times s$，每一次转移都是 $\sqrt m$ 的，所以最后的时间复杂度为 $O(nms\sqrt m)$，显然可以通过，并且代码简短无比。
```c++
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("------------------------------")
namespace FastIO{
	int write_top,read_f,read_x;
	char read_char;
	int write_st[20];
	inline int read(int &a){
		read_char=getchar();
		read_f=1;
		a=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			a=(a<<1)+(a<<3)+(read_char^48);
			read_char=getchar();
		}
		return a=a*read_f;
	}
	inline int read(){
		read_char=getchar();
		read_f=1;
		read_x=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			read_x=(read_x<<1)+(read_x<<3)+(read_char^48);
			read_char=getchar();
		}
		return read_x*read_f;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		write_top=0;
		do{
		   write_st[++write_top]=x%10;
		   x/=10;
		}while(x);
		while(write_top)putchar(write_st[write_top--]+'0');
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int inf=0x3f3f3f3f;
int n,m,s;
int dp[25][105][105];
bool vis[25][105][105];
int dfs(int p,int now,int rem){
	if(now>=s)return 0;
	if(!rem)return inf;
	if(p>n)return inf;
	if(vis[p][now][rem])return dp[p][now][rem];
	vis[p][now][rem]=1;
	int res=inf;
	for(int i=1;i*i<=rem;i++){//枚举这一分钟要跑几圈 
		tomin(res,dfs(p,now+i,rem-i*i)+1);//不换领队
		tomin(res,dfs(p+1,now+i,m-now-i)+1);
	}
	return dp[p][now][rem]=res;
} 
signed main(){
	read(n),read(m),read(s);
	dfs(1,0,m);
	write(dp[1][0][m]);
}
```

---

## 作者：lraM41 (赞：0)

借鉴了 [devout](https://www.luogu.com.cn/user/97344) 大佬。

记 $dp[i][j][k]$ 表示当前已经有 $i$ 头牛来领队，当前领队牛体力为 $j$ 及已经跑 $k$ 圈时的最短用时。显然每一时刻都有两种情况：继续领队 or 换一头牛领队。换牛领队时它的体力即为初始体力减去当前已跑圈数（因为体力一直在消耗）和每分钟消耗体力。时间复杂度显然可过。


~~码风是史，凑合着看。~~
```
#include<bits/stdc++.h>
using namespace std;
int n,e,d,dp[25][105][105],mi=20220517;
signed main(){
    for(int i=0;i<=20;i++)
        for(int j=0;j<=100;j++)
            for(int k=0;k<=100;k++)
                dp[i][j][k]=20220517;
    cin>>n>>e>>d;
    dp[0][e][0]=0;
    for(int i=0;i<n;i++)//共领头牛数
        for(int j=e;j>=0;j--)//领头牛体力
            for(int k=0;k<=d;k++){//已跑圈数
                int x=1;//题中x
                while(x*x<=j&&k+x<=d){//能跑 & 不超过跑道
                    dp[i][j-x*x][k+x]=min(dp[i][j-x*x][k+x],dp[i][j][k]+1);//继续领跑
                    dp[i+1][e-x-k][k+x]=min(dp[i+1][e-x-k][k+x],dp[i][j][k]+1);//换新领队
                    x++;
                }
            }
    for(int i=0;i<n;i++)
        for(int j=0;j<=e;j++)
            mi=min(mi,dp[i][j][d]);
    cout<<mi;
    return 0;
}

---

## 作者：fight_for_humanity (赞：0)

### [题目](https://www.luogu.com.cn/problem/P4953)

首先这题最重要的是贪心，否则直接想会很困难。简述贪心：如果一辆车是队首开了 $x$ 又回到后面开了 $y$，等价于前面一辆开了 $y$，自己再开 $x$。所以到一辆车时直接跑完即可。

那么状态就不难了，$f[i][j][k]$ 表示第 $i$ 辆车，走了 $j$ 圈，车头电力剩余为 $k$ 时的最小时间。

$$f[i][j][k] + 1\to f[i][j+x][k-x^2]$$

$$f[i][j][k] \to f[i+1][j][m-j]$$

这里的阶段是第几辆车。

这样是能过了的，但是可以优化。对于贪心本身：将一定电量的头车跑完若干圈，是可以预处理的，那么有状态： 

$g[i][j]$ 表示剩余电量为 $i$ 的头车走 $j$ 圈的最小时间。 

$$g[i][j] \gets min( g[i-x^2][j-x] + 1 )$$

那么原来的 $f$ 就优化成了：$f[i][j]$ 表示当前头车为第 $i$ 辆车，走了 $j$ 圈的最小时间。

$$f[i][j] \gets f[i-1][j-x] + g[m-(j-x)][x]$$

### CODE
```
memset(f,0x3f,sizeof f),memset(g,0x3f,sizeof g);
f[0][0] = 0;
for(int i = 0;i<=m;++i)g[i][0] = 0;
for(int i = 1;i<=m;++i)
	for(int j = 1;j<=s;++j)
		for(int x = 1;x*x<=i && x <= j;++x)
			g[i][j] = min(g[i][j],g[i-x*x][j-x]+1);
for(int i = 1;i<=n;++i)
	for(int j = 1;j<=s;++j)
		for(int x = 0;x<=j;++x)
			f[i][j] = min(f[i][j],f[i-1][j-x] + g[m-j+x][x]);
for(int i = 1;i<=n;++i)ans = min(ans,f[i][s]);
printf("%d",ans);
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15978512.html)

# 题目大意

奶牛自行车队由 $n$ 名队员组成，他们正准备参加一个比赛，这场比赛的路程共有 $d$ 圈。 车队在比赛时会排成一条直线，由于存在空气阻力，当骑车速度达到每分钟 $x$ 圈时，领头的 奶牛每分钟消耗的体力为 $x^2$，其它奶牛每分钟消耗的体力为 $x$。

每头奶牛的初始体力值都是相同的，记作 $e$。如果有些奶牛在比赛过程中的体力不支，就会掉队，掉队的奶牛不能继续参加比赛。每支队伍最后只要有一头奶牛能到终点就可以了。

比赛规定，最小的计时单位是分钟，在每分钟开始的时候，车队要哪头奶牛负责领头，领头奶牛不能在这分数中内掉队，每分钟骑过的圈数也必须是整数。

请帮忙计划一下，采用什么样的策略才能让车队以最快的时间到达终点？

$n\le 20,e,d\le 100$。

# 题目分析

令 $dp_{i,j,k}$ 表示有 $i$ 头牛掉队了,领头的牛体力为 $j$,已经跑了 $k$ 圈的最快时间。

根据定义，初始化 $dp_{0,e,0}=0$。

采用刷表法来做。当前状态会延伸出两个状态：领头牛掉队了、领头牛接着跑。

领头牛接着跑时，掉队的牛数量不变，体力减少，圈数变多。

领头牛掉队时，掉队的牛数量加 $1$，体力是最初的体力减去已跑圈数花费的体力，圈数也变多。

即去更新 $dp_{i,j-speed^2,k+speed}$ 和 $dp_{i+1,e-k-speed,k+speed}$。

# 代码

```cpp
//2022/3/7
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int INF = 0x3f3f3f3f;
const int ma1 = 25,ma2 = 105;
int dp[ma1][ma2][ma2];//dp[i][j][k]:有 i 头牛掉队了,领头的牛体力为 j,已经跑了 k 圈的最快时间 
int n,e,d;
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n = read(),e = read(),d = read();
	mst(dp,0x3f);
	dp[0][e][0] = 0;
	for (register int i = 0;i <= n; ++ i) {
		for (register int j = e;j >= 0; -- j) {
			for (register int k = 0;k <= d; ++ k) {
				int now = 1;//每分钟 now 圈
				while (now * now <= j && k + now <= d) {
					dp[i][j - now * now][k + now] = min(dp[i][j - now * now][k + now],dp[i][j][k] + 1);
					dp[i + 1][e - k - now][k + now] = min(dp[i + 1][e - (k + now)][k + now],dp[i][j][k] + 1);
					now ++;
				}
			}
		}
	}
	int ans = INF;
	for (register int i = 0;i < n; ++ i) {
		for (register int j = 0;j <= e; ++ j) {
			ans = min(ans,dp[i][j][d]);
		}
	}
	printf("%d\n",ans == INF ? 0 : ans);

	return 0;
}
```

---

