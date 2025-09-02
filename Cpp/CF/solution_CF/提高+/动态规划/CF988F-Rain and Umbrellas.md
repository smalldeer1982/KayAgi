# Rain and Umbrellas

## 题目描述

Polycarp lives on a coordinate line at the point $ x = 0 $ . He goes to his friend that lives at the point $ x = a $ . Polycarp can move only from left to right, he can pass one unit of length each second.

Now it's raining, so some segments of his way are in the rain. Formally, it's raining on $ n $ non-intersecting segments, the $ i $ -th segment which is in the rain is represented as $ [l_i, r_i] $ ( $ 0 \le l_i < r_i \le a $ ).

There are $ m $ umbrellas lying on the line, the $ i $ -th umbrella is located at point $ x_i $ ( $ 0 \le x_i \le a $ ) and has weight $ p_i $ . When Polycarp begins his journey, he doesn't have any umbrellas.

During his journey from $ x = 0 $ to $ x = a $ Polycarp can pick up and throw away umbrellas. Polycarp picks up and throws down any umbrella instantly. He can carry any number of umbrellas at any moment of time. Because Polycarp doesn't want to get wet, he must carry at least one umbrella while he moves from $ x $ to $ x + 1 $ if a segment $ [x, x + 1] $ is in the rain (i.e. if there exists some $ i $ such that $ l_i \le x $ and $ x + 1 \le r_i $ ).

The condition above is the only requirement. For example, it is possible to go without any umbrellas to a point where some rain segment starts, pick up an umbrella at this point and move along with an umbrella. Polycarp can swap umbrellas while he is in the rain.

Each unit of length passed increases Polycarp's fatigue by the sum of the weights of umbrellas he carries while moving.

Can Polycarp make his way from point $ x = 0 $ to point $ x = a $ ? If yes, find the minimum total fatigue after reaching $ x = a $ , if Polycarp picks up and throws away umbrellas optimally.

## 说明/提示

In the first example the only possible strategy is to take the fourth umbrella at the point $ x = 1 $ , keep it till the point $ x = 7 $ (the total fatigue at $ x = 7 $ will be equal to $ 12 $ ), throw it away, move on from $ x = 7 $ to $ x = 8 $ without an umbrella, take the third umbrella at $ x = 8 $ and keep it till the end (the total fatigue at $ x = 10 $ will be equal to $ 14 $ ).

In the second example the only possible strategy is to take the first umbrella, move with it till the point $ x = 9 $ , throw it away and proceed without an umbrella till the end.

## 样例 #1

### 输入

```
10 2 4
3 7
8 10
0 10
3 4
8 1
1 2
```

### 输出

```
14
```

## 样例 #2

### 输入

```
10 1 1
0 9
0 5
```

### 输出

```
45
```

## 样例 #3

### 输入

```
10 1 1
0 9
1 5
```

### 输出

```
-1
```

# 题解

## 作者：go_deeper (赞：8)

这里应该是本题目写法最简单，且最容易理解的题解。  

## 题目分析  
从点 $0$ 走到点 $a$，其中有 $n$ 个不相交地区间下雨，在 $m$ 个点上有重量分别为 $p_i$ 的伞，在任何一个下雨的区间内你都必须持有至少一把伞，并且你每移动一格产生的代价是你身上伞的质量和，问走到点 $a$ 产生的代价最少是多少。

首先，可能你第一眼看到这个题，和我的想法一样，就是贪心，尽量使得自己身上伞的质量比较轻，那么很显然：**在任意时刻你的身上至多有一把伞** 。这个结论应该是显然的，那么接下来，**捡起轻的伞总是好的吗**？ 

这个问题的答案显然是否定的，因为不仅要考虑伞的质量，还要考虑携带伞移动的距离，应为代价是质量乘以距离，但是有一个点是明确的，那就是**到达第$i$个点时如果知道携带的是第$j$把伞，那么最小的代价是可以算出来的**。

想象一下，你在点 $x_1$ 捡起了一把重量为 $p$ 的伞，并且到达 $x_2$ 是你仍然携带着这把伞，那么可以肯定，你一定在携带这把伞的途中付出了 $(x_2-x_1)\times p$ 的代价，但是这并不会影响你后面的换伞。

同时考虑到最小代价的确定性，这里即满足动态规划的**最优子结构与无后效性**原则，所以使用动态规划解决这个问题。

## 动态规划

根据上面的分析，我们已经成功定义了状态，我们使用 $dp(i,j)$ 表示到达点 $i$ 且仍然持有从点 $j$ 捡起的伞的最小代价，并且约定当 $j=0$ 时表示手中没有持有伞，那接下来，让我们考虑如何转移。

在转移的过程中，显然只有三种可能，那就是**扔伞、换伞和保持伞不变**。考虑完转移的可能后，接下来需要考虑转移的条件：其实只有一个限制，那就是：**如果正在下雨，你不能扔伞**。

最后,我们让 $umb(j)$ 表示在点 $j$ 的伞的质量，$mn(i)$ 表示所有的 $dp(i,j)$ 的最小值,那么显然有以下转移：
- $dp(i,0)=mn(i)$ 如果点 $i$ 没有下雨。
- $dp(i,i)=\min(umb(i)+mn(i))$ 相当于换了点 $i$ 的伞。
- $dp(i,j)=\min(dp(i-1,j)+umb(j))$ 相当于保持持有点 $j$ 的伞。

显然,时间复杂度为 $O(am)$。

但是，直接考虑每把伞的实现比较难写，所以我们进行一个简化，假如在某一个点 $j$ 没有伞，那么我们可以假装这个点有伞并且正常转移，只是把 $umb(j)$ 设置成正无穷。

最终答案即为 $dp(a,j)$ 中的最小值，如果答案为正无穷，那么就没有解。

## 代码实现
代码如下：
```cpp
#define fer(i,a,n) for (int i=(a);i<=(n);++i)
template<class T1, class T2>
void cmin(T1 &a, T2 b) {
	a = min<T1>(a, b);
}
void solve() {
	ll a,n,m;
	cin>>a>>n>>m;
	vector<ll>umb(a+2,(ll)1e14),israin(a+2);
	fer(i,1,n)
	{
		ll l,r;
		cin>>l>>r;
		++l;
		fer(j,l,r)israin[j]=1;
	}
	fer(i,1,m)
	{
		ll x,p;
		cin>>x>>p;
		++x;
		cmin(umb[x],p);
	}
	umb[0]=0;
	vector<vector<ll>>dp(a+2,vector<ll>(a+2,(ll)1e14));
	vector<ll>mn(a+2,(ll)1e14);
	dp[0][0]=0,mn[0]=0;
	fer(i,1,a+1)
	{
		fer(j,0,i-1)
		{
			if(israin[i])
			{
				if(j==0)continue;
				cmin(dp[i][j],dp[i-1][j]+umb[j]);
			}
			else 
			{
				if(j==0)cmin(dp[i][j],mn[i-1]);
				else cmin(dp[i][j],dp[i-1][j]+umb[j]);
			}
		}
		cmin(dp[i][i],mn[i-1]+umb[i]);
		fer(j,0,i)cmin(mn[i],dp[i][j]);
	}
	cout<<(dp[a+1][0]<(ll)1e14?dp[a+1][0]:-1);	
}

---

## 作者：guanyf (赞：4)

### 题意
有一个长度为 $a$ 的区间，给定 $n$ 个有雨的区间和 $m$ 把伞的位置与重量，每次可以向右移动一个单位，代价是携带伞的总重量。在经过有雨的单位时（**注意是边而不是点，因此区间两端不算**），必须携带伞才能通过。求最小的通过区间的代价之和。


### 分析
为了能更清楚的表现出当前的局面，因此不妨考虑状态为 $i,j,v$ 分别表示前 $i$ 个单位用到了第 $j$ 把伞最小花费的代价 $v$，结果是 $i=x$ 时的任何合法状态。当状态转移不到结果时，则输出 ```-1```。

对于每一个点，有三种操作：捡伞、丢伞、换伞。每个状态可以分两次转移，分别是:（$k$ 是当前位置拥有的伞，$k$ 等于零表示没伞，$k$ 等于 $j$ 表示不变，$0 \le i \le a$，$0 \le$ 当前位置伞的数量，$w_i$ 表示第 $i$ 个伞的重量。）
$$i,j,v \rightarrow i,k,v$$
$$i,k,v \rightarrow i+1,k,v+w_k$$
第一个转移是将当前伞换成当前位置的其他伞，第二个转移是向右走一个单位。

答案就是从 $0,0,0$ 到 $a,j,v$ 花费最小代价的一条路径。

对于每一个相同的 $i,j,v$，它们对答案的贡献完全相同，只有选择的方案不同，因此可以只保留一个。

对于答案来说，我们不需要知道它每次选择的方案，只需要知道它的代价，因此我们只需要保留单个状态 $i,j,v$。

时间复杂度:$\mathit{O}(am^2)$。


### 思路
接下来就是考虑优化一下状态了，考虑状态分组。可以发现，对于每一个 $i,j$，只要它的状态最优，那么它作最优的转移之后就不会比其他状态更劣。因此我们就可以将 $i,j$ 分在一起，$v$ 作为附带属性。对于每个 $i,j$ 相等的状态，只需要保留 $v$ 最优的那个就行了。这样的话，每次转移只需要作最优的就行了。在这种情况下，就可以考虑剪枝，每次当当前状态更优时，则更新最优值，否则放弃。

虽然可以优化代码时间，但是并不会改变它的时间复杂度。当值是按照从劣到优排序时，则时间复杂度依旧是：$\mathit{O}(am^2)$。


状态优化完了，就可以优化转移了。实际上，每次转移的时间复杂度是：$\mathit{O}(m)$，而状态的数量又是：$\mathit{O}(am)$。因此只能将转移优化到：$\mathit{O}(1)$。

按照优化状态的思路，我们只需要保留最优的转移就行了。换言之，一个位置上有多把伞，我们只需要转移到重量最小的那把就行了，因为最优的状态作最优的转移，一定不会转移到比它更劣的状态上，所以优化是正确的。

时间复杂度：$\mathit{O}(am)$


### 延伸
至此，我依旧没有讲动态规划，因为从这个状态图中，$i$ 虽然具有拓扑序，但是 $j$ 没有。因为同一位置上的任意两把伞都可以互换，这样显然不具有拓扑序。但是根据搜索的解决思路：**对于每一个相同的 $i,j,v$，它们对答案的贡献完全相同，只有选择的方案不同，因此可以只保留一个**，再加上**同一个位置，无论换多少次伞，都不会增加代价**，因此我们只需要换一次伞就行了。这样的话 $j$ 就非常神奇的变得有拓扑序了。

上述思路如果没理解，可以想象成将拓扑序拉伸出来了：将 $j$ 这一维看成换之前与换之后。每次 $i,j,v$ 可以转移成 $i,k,v$（$k$ 表示当前位置拥有伞的数量）。

再根据搜索优化转移的方法，可以将没有伞的位置设为当前位置最优的状态，在由没有伞的位置去更新当前位置所拥有的伞。如果当前位置下雨，那么就将没有伞的状态设为一个极劣值。

状态转移方程：

$$1 \leq i \leq a$$
$$1 \leq j \leq m$$
$$dp_{i,0}=\min(dp_{i,j},dp_{i,0})$$
$$dp_{i,j}=\min(dp_{i,j},dp_{i,0})$$
$$dp_{i+1,j}=\min(dp_{i+1,j},dp_{i,j}+w_j)$$


### 代码
```cpp
// 状态转移方程 ：(1 <= i <= x) (1 <= j <= m) dp[i][0]=min(dp[i][j],dp[i][0])  dp[i][j]=min(dp[i][j],dp[i][0]) dp[i+1][j] = min(dp[i+1][j], dp[i][j] + a[j].second)
#include <iostream>
using namespace std;
using LL = long long;
const LL MAXN = 2005;
LL x, n, m, dp[MAXN][MAXN], ans = INT_MAX;
bool vis[MAXN];
pair<LL, LL> a[MAXN];
signed main() {
  ios::sync_with_stdio(0);
  cin >> x >> n >> m;
  fill(dp[0], dp[x] + m + 1, INT_MAX);
  dp[0][0] = 0;
  for (LL i = 1, l, r; i <= n; i++) {
    cin >> l >> r;
    fill(vis + l, vis + r, 1);//标记下雨
  }
  for (LL i = 1; i <= m; i++) {
    cin >> a[i].first >> a[i].second;
  }
  for (LL i = 0; i <= x; i++) {
    for (LL j = 1; j <= m; j++) {
      dp[i][0] = min(dp[i][0], dp[i][j]);//更新最优
    }
    for (LL j = 0; j <= m; j++) {
      a[j].first == i && (dp[i][j] = min(dp[i][j], dp[i][0]));//更新当前位置的所有状态
      dp[i + 1][j] = min(dp[i + 1][j], (!j && vis[i] ? INT_MAX : dp[i][j] + a[j].second));//向右走一步
      i == x && (ans = min(ans, dp[i][j]));//更新最终答案
    }
    vis[i] && (dp[i][0] = INT_MAX);//标为不合法
  }
  cout << (ans == INT_MAX ? -1 : ans);
  return 0;
}
```


---

## 作者：大菜鸡fks (赞：3)

dp[i][j]表示在第i点，有第j把伞

决策分三种

1.扔掉伞 （要求i点不下雨）

2.撑伞前进（要求i-1点手中有伞）

3.换伞（要求i-1点有雨伞提供）

随便转移

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2005,INF=1e9;
int A,n,m,rain[N],w[N],cho[N]; 
inline void init(){
    scanf("%d%d%d",&A,&n,&m);
    for (int i=1;i<=n;i++){
        int l,r; 
        scanf("%d%d",&l,&r);
        for (int j=l+1;j<=r;j++){
            rain[j]=1;
        }
    }
    w[0]=INF;
    for (int i=1;i<=m;i++){
        int p;
        scanf("%d%d",&p,&w[i]);
        if (w[i]<w[cho[p]]){
            cho[p]=i;
        }
    }
}
int dp[N][N];
inline void solve(){
    memset(dp[0],127/3,sizeof(dp[0]));
    dp[0][0]=0;
    for (int i=1;i<=A;i++){
        memset(dp[i],127/3,sizeof(dp[i]));
        for (int j=0;j<=m;j++){
            if (!rain[i]){
                dp[i][0]=min(dp[i][0],dp[i-1][j]);
            }
            if (j) {
                dp[i][j]=min(dp[i][j],dp[i-1][j]+w[j]);
            }
            if (cho[i-1]){
                dp[i][cho[i-1]]=min(dp[i][cho[i-1]],dp[i-1][j]+w[cho[i-1]]);
            }
        }
    }
    int ans=INF;
    for (int i=0;i<=m;i++){
        ans=min(ans,dp[A][i]);
    }
    if (ans==dp[0][1]) puts("-1");
        else printf("%d\n",ans);
}
int main(){
    init();
    solve();
    return 0;
} 
```

---

## 作者：Position (赞：3)

首先很明显的一个地方就是:在任意时刻人只要拿一把伞就行了

考虑设dp[i][j]表示在第i个点拿着第j把伞所付出最小代价(j=0时代表不拿伞)

再让r[i]表示:r[i]=1,第i-1个点到第i个点之间下雨，否则不下雨

注意一个地方可能有多把伞

具体转移方程见代码

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N=2005;
int dp[N][N],r[N],u[N],p[N];
int main(){
	int a=read(),n=read(),m=read();
	for(int i=1;i<=n;i++){
		int L=read(),R=read();
		for(int j=L+1;j<=R;j++) r[j]=1;
	}
	p[0]=1e9;
	for(int i=1;i<=m;i++){
		int x=read();p[i]=read();
		if(p[i]<p[u[x]]) u[x]=i;
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=dp[0][u[0]]=0;
	int mn1=inf,mn2=inf;
	if(u[0]!=0) mn1=0,mn2=p[u[0]];
	for(int i=1;i<=a;i++){
		if(r[i]==0)
			dp[i][0]=min(dp[i][0],min(dp[i-1][0],mn1));
		else if(r[i+1]==0)
			dp[i][0]=min(dp[i][0],mn2);
		for(int j=1;j<=m;j++){
			dp[i][j]=min(dp[i][j],dp[i-1][j]+p[j]);
			if(u[i]==j){
				if(r[i]==0) dp[i][j]=min(dp[i][j],min(dp[i-1][0],mn1));
				else dp[i][j]=min(dp[i][j],mn2);
			}
		} 
		mn1=mn2=inf;
		for(int j=1;j<=m;j++){
			if(mn1>dp[i][j]) mn1=dp[i][j];
			if(mn2>dp[i][j]+p[j]) mn2=dp[i][j]+p[j];
		}
	}
	int ans=inf;
	for(int j=0;j<=m;j++) ans=min(ans,dp[a][j]);
	if(ans==inf) cout<<-1;
	else cout<<ans;
}

```

---

## 作者：__LZH__ (赞：1)

# Rain and Umbrellas

## 题意：
 在一条长为 $a$ 的路上有 $m$ 把伞，$n$ 个不相交的雨段，要从 $0$ 走到 $a$，不能淋到雨，每把伞都能捡起、放下，且自身有重量 $p_i$ 和位置 $x_i$（从零开始），持第 $i$ 把伞时走一单位距离会耗费 $p_i$ 的体力，求从 $0$ 走到 $a$ 所需的最小体力值。
 
## 思路：
数据范围是 $(1 \le a, m \le 2000, 1 \le n \le \lceil \frac{a}{2} \rceil)$，可以看出其他方法都不太好写，但是 DP 似乎可以过的，而且暂时看不出其他方法，所以考虑 DP 。


### 首先考虑搜索：
#### 先提一个问题：怎么拿伞？
 - 最多拿一把伞。
 - 错误的贪心策略：拿最轻的伞。
 - 在下雨的地方时，必须拿伞。
 - 在无雨的地方时，可能拿伞。
 - 如果手里有伞，走到有伞的地方，可以考虑换伞。

#### 接下来考虑状态和转移： 
状态： $(x, w, cost)$，人停在的位置 $x$，伞的重量 $w$，疲劳度之和为 $cost$。$w$ 为 $0$ 时不带伞。
转移：令 $p_x$ 表示位置 $x$ 处的伞的最小重量，$x=p_x$，$w'$ 为位置 $x$ 之前的某把伞的重量：
- $(x, 0, cost)$ ：$[x, x + 1]$ 一定无雨
  - $(x - 1, 0, cost) \to (x, 0, cost)$，$(x - 1, w', cost - w') \to (x, 0, cost)$
- $(x, w, cost)$ ：$[x, x + 1]$ 可以有雨可以无雨。
  - $(x - 1, w', cost - w') \to (x, w, cost)$
  - $(x - 1, 0, cost) \to (x, w, cost)$
  - $(x - 1, w', cost - w') \to (x, w', cost)$ ，不换伞。
 
不难发现拓扑序：$x$ 从 $0$ 到 $a + 1$。
### 再来考虑 DP ：
令 $X = 2000 ，V = 10^5 , M = 2000$。
状态：令 $dp_{x, w}$ 表示走到位置 $x$ 处、手上的伞的重量为 $w$ 的最小代价。
转移：
- $[x, x + 1]$ 有雨时：
  - 不换伞，$dp_{x, w} = \min(dp_{x, w}, dp_{x - 1, w} + w)$，单个状态转移时间 $O(1)$，一共 $M$ 个状态。
  - 换伞，$dp_{x, p_x} = \min(dp_{x, p_x}, dp_{x - 1, w'} + w')$，单个状态转移时间 $O(M)$，一共 $1$ 个状态。
  - 当 $x$ 确定时，转移时间 $O(V)$。
- $[x, x + 1]$ 无雨时：
  - 不换伞和换伞与有雨时相同。
  - 丢伞，$dp_{i, 0}=\min(dp_{i, 0}, dp_{i-1, j})$，单个状态转移时间 $O(1)$，一共 $M$ 个状态。
  - 转移时间 $O(V)$。

空间：$O(XV)$。

时间：$O(XV)$。

#### 优化：
因为时间 $XV = 2 \times 10^8$ 过不了，所以考虑优化。
可以发现状态里的 $w$ 可以用 $p_x$ 代替，这样 $O(XV)$ 就能转化为 $O(XM)$。

优化状态为 $dp_{x, j}$ 表示走到位置 $x$ 处，伞的编号（伞的位置）为 $j$ 时的最小代价。

最后空间 $O(XM)$，时间 $O(XM)$。

code：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2010;

struct node{
  int x, p;
}a[N];

int l, n, m, dp[N][N], f[N], s[N], x, y;

int main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> l >> n >> m;
  for(int i = 1; i <= n; i++){
    cin >> x >> y; x++, y++;
    for(int j = x; j < y; j++){
      s[j] = 1;
    }
  }
  for(int i = 1; i <= l; i++){
    f[i] = 1e9;
  }
  for(int i = 1; i <= m; i++){
    cin >> a[i].x >> a[i].p; a[i].x++;
    f[a[i].x] = min(f[a[i].x], a[i].p);
  }
  for(int i = 0; i <= l + 1; i++){
    for(int j = 0; j <= l + 1; j++){
      dp[i][j] = 1e9;
    }
  }
  dp[0][0] = 0;
  for(int i = 1; i <= l + 1; i++){
    if(f[i] != 1e9){
      for(int j = 0; j < i; j++){
        dp[i][i] = min(dp[i][i], dp[i - 1][j] + f[i]);
      }
    }
    for(int j = 1; j < i; j++){
      dp[i][j] = min(dp[i][j], dp[i - 1][j] + f[j]);
    }
    if(!s[i]){
      for(int j = 0; j < i; j++){
        dp[i][0] = min(dp[i - 1][j], dp[i][0]);
      }
    }
  }
  int k = *min_element(dp[l + 1], dp[l + 1] + 1 + l);
  cout << ((k == 1e9) ? -1 : k);
  return 0;
}
//
```

---

## 作者：O_v_O (赞：1)

# CF988F Rain and Umbrellas  题解

## 题意

给定路程长度 $a$，$n$ 个下雨阶段，和 $m$ 个放置伞的位置，要求在途中不能淋雨，求出到达终点携带的伞的重量之和最小，如果不行，请输出 $-1$（注：一个点可能有多把伞）。

## 思路

这道题我们首先要明白以几个点：

1. 最多拿一把伞。

    虽然题目中说可以拿许多把伞，但我们从贪心角度来看，如果你拿多把伞，但你在下雨时只使用了一把伞，而导致另外一把你带在身上的伞则没有任何用处。

2. 错误的贪心策略：拿最轻的伞。

    这个非常好想，下面提供一组 hack 数据：
    ```
    100 1 2
    80 100
    0 5
    80 20
    ```
    如果按以上的贪心策略，那就是从 $0$ 号点开始拿起重量为 $5$ 的伞，很显然，这样并不是最优的，因为我们可以在 $80$ 号点拿起重量为 $20$ 的伞，然后走到终点。

3. 在下雨的地方时，必须拿伞。

    此要求已在题目中所说。

4. 在无雨的地方时，可能拿伞。

    下面提供一组 hack 数据解释：
    ```
    5 1 1
    0 20
    4 5
    ```
    这组样例中只有一把伞，即便只有一小段会下雨，但我们也是能从头到尾都带着这把伞。

5. 如果手里有伞，走到有伞的地方，可以考虑换伞。

    下面提供一组 hack 数据解释：
    ```
    10 2 2
    1 3
    4 5
    0 5
    3 2
    ```
    我们可以先从 $0$ 号点拿起伞，然后再到 $3$ 号点换成另一把伞，最后到 $5$ 号点放下伞，这样是最优的。

### 状态和转移

令 $p_x$ 表示位置 $x$ 处的伞的最小重量，$p_x = 0$ 时表示位置 $x$ 处没伞。

状态：$(x, w, cost)$，人停在的位置 $x$，伞的重量 $w$，疲劳度之和为 $cost$。$w$ 为 $0$ 时不带伞。

转移：令 $w = p_x$，$w'$  为位置 $x$ 之前的某把伞的重量。

- $(x, 0, cost)$：$[x, x + 1]$ 条件：一定无雨
    - $(x - 1, 0, cost) \to (x, 0, cost)$ 表示前面的状态没有伞，到这个点依然不拿伞。
    - $(x - 1, w', cost - w') \to (x, 0, cost)$ 表示前面的状态有伞，到这个点将前面的伞丢掉。
- $(x, w, cost)$：$[x, x + 1]$ 条件：可以有雨可以无雨。
    - $(x - 1, w', cost - w') \to (x, w, cost)$ 表示前面的状态有伞，到这个点换上这个点的伞。
    - $(x - 1, 0, cost) \to (x, w, cost)$ 表示前面的状态没有伞，到这个点有雨，换上这个点的雨伞。
    - $(x - 1, w', cost - w') \to (x, w', cost)$ 表示之前就拿着伞，到这个点有雨，但不换伞。

$(x, w)$ 一定时，$cost$​ 越小越好。

拓扑序：$x$ 从 $0$ 到 $a + 1$。

最优化属性：$w$。

### DP 设计

令 $X = 2000$，$V = 10^5, M = 2000$。

状态：令 $dp_{x, w}$ 表示走到位置 $x$ 处、手上的伞的重量为 $w$ 的最小代价。

转移：

- $[x, x + 1]$ 有雨时：
  $$
  \begin{cases}
  dp_{x, w} = \min(dp_{x, w}, dp_{x - 1, w} + w) \\
  dp_{x, p_x} = \min(dp_{x, p_x}, dp_{x - 1, w'} + w')
  \end{cases}
  $$
  当 $x$ 确定时，转移时间 $O(V)$​。
- $[x, x + 1]$ 无雨时：
  $$
  \begin{cases}
  dp_{x, w} = \min(dp_{x, w}, dp_{x - 1, w} + w) \\
  dp_{x, p_x} = \min(dp_{x, p_x}, dp_{x - 1, w'} + w') \\
  dp_{x, 0} = \min(dp_{x, 0}, dp_{x - 1, w'})
  \end{cases}
  $$
  转移时间 $O(V)$。

### 时空复杂度

空间：$O(XV)$。

因为我们的 $dp$ 设计是 $dp_{x, w}$，$w$ 就是 $p_i$ ，这里用 $V$ 来表示。

时间：$O(XV)$。

我们看以上三种状态：

1. 不换伞

    单个状态转移时间 $O(1)$，一共 $M$ 个状态。

2. 换伞

    单个状态转移时间 $O(M)$，一共 $1$ 个状态。

3. 丢伞

    单个状态转移时间 $O(1)$，一共 $M$ 个状态。

#### 优化

如果我们按照上面的时空复杂来写的话，我们就炸了，所以我们要优化状态，优化如下：

- 优化状态为 $dp_{x, j}$ 表示走到位置 $x$ 处，伞的编号（伞的位置）为 $j$​ 时的最小代价。

时空优化为：

- 空间 $O(XM)$，时间 $O(XM)$。

---

## 作者：1234567890sjx (赞：0)

简单 dp，~~但是调了一个小时~~。不去重见【】。

其实是一个很简单的小 dp。设 $f_{i,j}$ 表示当前位于点 $i$ 雨伞从点 $j$ 拿来的最小方案。这个地方你需要处理一下点 $j$ 位置雨伞中最轻的那一个重量是多少。

然后暴力覆盖出有雨的区间。令 $X_i$ 表示 $i$ 是否有雨，$U_i$ 表示 $i$ 点最轻的雨伞的重量。

令 $j=0$ 表示当前没有雨伞。则显然有转移：

+ $f_{i,i}\leftarrow U_i+\min f_{i-1,j}$。
+ $f_{i,j}\leftarrow f_{i-1,j}+U_j$（$j\neq 0$ 且当前没有雨）。
+ $f_{i,j}\leftarrow \min a_{i-1,k}$（$j=0$ 且当前没有雨）。
+ $f_{i,j}\leftarrow f_{i-1,j}+U_j$（$j\neq 0$ 且当前有雨）。

最终答案即为 $f_{a,0}$。记录 $g_i$ 表示 $\min f_{i,j}$ 然后每一次转移的时候更新就可以做到 $O(n^2)$。

```cpp
++a;g[0]=0;
    for(int i=1;i<=a;++i){
        for(int j=0;j<i;++j){
            if(vis[i]){if(j)f[i][j]=min(f[i][j],f[i-1][j]+px[j]);}
            else if(j)f[i][j]=min(f[i][j],f[i-1][j]+px[j]);
            else f[i][j]=min(f[i][j],g[i-1]);
        }
        f[i][i]=min(f[i][i],g[i-1]+px[i]);
        g[i]=1e18;for(int j=0;j<=i;++j)g[i]=min(g[i],f[i][j]);
    }
```

---

## 作者：__HHX__ (赞：0)

# 思路
考虑动态规划。

首先我们很容易得知，一直拿最轻的伞不一定最优，就像长时间拿最轻的，有可能比短时间拿更重的劣。

所以我们不能将拿没拿伞，或前缀最小值当作状态。

更进一步的说我们要将所有伞都考虑一遍。

即我们可以**设计状态** $(x, p, val)$ 指在位置 $[x - 1, x]$ 我拿了伞 $p$ 且疲劳值为 $val$。

我们设 $q_i$ 代表第 $i$ 把伞的重量，特别的 $i = 0$ 时代表没拿伞，即 $q_i = 0$。

若 $[x - 1, x]$ 处有雨，此时状态 $q_p \neq 0$。

好了现在我们可以开始抽象转移了。

很明显我们只要满足放伞、换伞和撑伞。

放伞，即把所有在 $x - 1$ 下**合法状态** $p$ 转换成 $0$，抽象下得 $(x - 1, p, val) \to (x, 0, val + q_p)$，时间 $O(m)$。

换伞，即把所有在 $x - 1$ 下**合法状态** $p$ 转换成 $p'$ 即当前位置的伞，抽象下得 $(x - 1, p, val) \to (x, p', val + q_p)$，时间 $O(m)$。

撑伞，即继续带着伞，即把所有在 $x - 1$ 下**合法状态** $p$ 转换成 $p$ 即不变，抽象下得 $(x - 1, p, val) \to (x, p, val + q_p)$，时间 $O(m)$。

时间复杂度 $O(am)$。

---

## 作者：编程小贝壳 (赞：0)

发现现存的题解都是dp，那么本蒟蒻来提供一种非dp的，类似于贪心的写法。

题意详见 [原题](https://www.luogu.com.cn/problem/CF988F) 中的题意翻译。

### 输入格式

第一行三个整数 $a$，$n$ 和 $m$，分别指要走的路的长度，有雨的区间数量和伞的数量。接下来 $n$ 行，每行两个整数表示下雨的区间；加下来 $m$ 行，每行两个整数表示雨伞的位置和重量。

### 分析

看完题一眼顶针，发现最优的情况手里**至多一把伞**，那么只需要考虑什么时候拿、什么时候换即可。为了方便，我们先将整个 $[0,a]$ 中下雨的区段染色，然后分开讨论：

- 在没有下雨的区间，我们需要尽量晚的拿起尽量轻的伞，即**对答案贡献最小**的那一把。

- 在下雨的区间，我们需要在遇见新的伞的时候考虑**是否要换伞**，以及在走出下雨区域时是否要把伞扔掉。

为了得到这些东西，我们预处理出：

1. 对于每个处于不下雨的区间的伞，求出其到**自身最近的处于其右侧一个下雨区间内的，重量小于自己的伞**的距离和贡献。若没有满足条件的伞，距离为自身到下一个不下雨的区间的距离（即自己到自身所处区间右侧距离加上右侧一个下雨的区间的长度）。

2. 对于每个处于下雨区间的伞，求出其到**自身右侧最近的与自身处于相同下雨区间内的，重量小于自己的伞**的距离和贡献。若没有满足条件的伞，距离为自身到右侧不下雨的区间的距离。

以及为了更快求出这两个东西的若干条件。

接下来从起点开始模拟：

1. 在不下雨的区间，找到区间内计算出的贡献最小的一把伞并累加答案；

2. 在下雨的区间，只要遇到重量小于当前伞的重量的伞就换掉，并累加答案。

对吗？显然是错的。

考虑图示的情况，蓝色区域为下雨区域，$x_i$，$w_i$ 分别表示伞的位置和重量。

![graph](https://cdn.luogu.com.cn/upload/image_hosting/zy2t5bj9.png)

当 $w_1<w_4<w_2$ 时，可能会出现局部最优并非全局最优的情况，即 

$w_1\times(x_4-x_1) + w_1\times(r-x_4)>w_2\times(x_4-x_1)$ 但 

$w_1\times(x_4-x_1) + w_1\times(r-x_4)<w_2\times(x_4-x_1)+w_4\times(r-x_4)$ 的时候，以上算法会选择拿 $w_2$ 从而导致算法出错。但也很好解决此问题，只需要在初始化的时候对于每个在雨中的伞找出按照最优策略（见到轻的伞就换掉）能拿到的下一把伞的位置和贡献，并在选择伞的时候加上这部分的贡献。

最后，在模拟时每进入一个新的不下雨区间，对手上拿的这把伞按照上述方法计算一次贡献，如果有更优的选择直接将伞扔掉即可。

若第一把伞位于下雨区间，则无解。

预处理的复杂度最差为 $O(m^2)$，模拟的复杂度为 $O(m)$。如果对上述算法理解不清楚，可以结合时间复杂度进一步理解。

### 正确性

考虑将相邻的一个不下雨区间和一个下雨区间划分为一个子区间进行处理。若每个这样的子区间都为最优解，那么显然整个问题也是最优解。因为在进入一个新的子区间时，从上一个子区间继承下来的决策仅有手上拿的这把伞，而这部分贡献是被我们纳入新的子区间考虑了的。

---

