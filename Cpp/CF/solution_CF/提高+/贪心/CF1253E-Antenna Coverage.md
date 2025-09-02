# Antenna Coverage

## 题目描述

The mayor of the Central Town wants to modernize Central Street, represented in this problem by the $ (Ox) $ axis.

On this street, there are $ n $ antennas, numbered from $ 1 $ to $ n $ . The $ i $ -th antenna lies on the position $ x_i $ and has an initial scope of $ s_i $ : it covers all integer positions inside the interval $ [x_i - s_i; x_i + s_i] $ .

It is possible to increment the scope of any antenna by $ 1 $ , this operation costs $ 1 $ coin. We can do this operation as much as we want (multiple times on the same antenna if we want).

To modernize the street, we need to make all integer positions from $ 1 $ to $ m $ inclusive covered by at least one antenna. Note that it is authorized to cover positions outside $ [1; m] $ , even if it's not required.

What is the minimum amount of coins needed to achieve this modernization?

## 说明/提示

In the first example, here is a possible strategy:

- Increase the scope of the first antenna by $ 40 $ , so that it becomes $ 2 + 40 = 42 $ . This antenna will cover interval $ [43 - 42; 43 + 42] $ which is $ [1; 85] $
- Increase the scope of the second antenna by $ 210 $ , so that it becomes $ 4 + 210 = 214 $ . This antenna will cover interval $ [300 - 214; 300 + 214] $ , which is $ [86; 514] $
- Increase the scope of the third antenna by $ 31 $ , so that it becomes $ 10 + 31 = 41 $ . This antenna will cover interval $ [554 - 41; 554 + 41] $ , which is $ [513; 595] $

Total cost is $ 40 + 210 + 31 = 281 $ . We can prove that it's the minimum cost required to make all positions from $ 1 $ to $ 595 $ covered by at least one antenna.

Note that positions $ 513 $ and $ 514 $ are in this solution covered by two different antennas, but it's not important.

—

In the second example, the first antenna already covers an interval $ [0; 2] $ so we have nothing to do.

Note that the only position that we needed to cover was position $ 1 $ ; positions $ 0 $ and $ 2 $ are covered, but it's not important.

## 样例 #1

### 输入

```
3 595
43 2
300 4
554 10
```

### 输出

```
281
```

## 样例 #2

### 输入

```
1 1
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 50
20 0
3 1
```

### 输出

```
30
```

## 样例 #4

### 输入

```
5 240
13 0
50 25
60 5
155 70
165 70
```

### 输出

```
26
```

# 题解

## 作者：AThousandSuns (赞：7)

在我的博客园看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/11919065.html)

本题难点在正确性证明，所以写个~~我尽力写出的~~证明严谨（？）的题解。

令 $f_i$ 表示 $[1,i]$ 被全部覆盖的最小花费。答案为 $f_m$。

首先发现，添加一个区间 $[0,0]$ 不会影响答案。所以 $f_i$ 的初值可以设为 $i$。（这个很重要，没了就不对了！）

转移，如果 $i$ 已经被某个初始区间完全覆盖了，那么可以从 $f_{i-1}$ 转移来。

然后枚举每个区间，如果区间的右端点在 $i$ 左边，计算把这个区间扩张到能恰好覆盖到 $i$ 后的左端点。也就是从 $f_{\max(0,l[j]-(i-r[j]))}+i-r[j]$ 转移来。

记下每个区间被扩张成什么样会炸状态，所以直接从初始的区间开始扩张。

时间复杂度 $O(nm)$。

开始证明正确性。

首先证明只用考虑被左边的区间覆盖，不需要考虑右边的。

其实被右边的区间覆盖也被考虑过了，不过转移的时候就直接跳过了这些点（在这个被扩张后的区间中）。所以不用管。

接下来证明直接从初始的区间开始扩张就是最优解。

如果需要在被扩张的区间的基础上继续扩张，说明这次扩张到的点 $i$ 一定在上次扩张到的点 $j$ 的右边，扩张到 $i$ 后的区间的左端点一定跳过了 $j$。而我们最后要用到的是 $i$ 的状态（因为需要继续扩张），所以中间这第一次扩张是没有必要的。

所以这种情况不可能发生。

接下来证明恰好扩张到能覆盖 $i$ 就是最优解，也就是最优解不需要扩张到覆盖超过 $i$ 一点点。

如果需要扩张更多，一定是因为可以覆盖左边的更多点，让左边的区间更短（不然覆盖到超过 $i$ 的位置在 $f_i$ 是完全没有必要的）。

但是由于添加了区间 $[0,0]$（没错，它的作用就在这），一定有 $f_{i+1}\le f_i+1$（因为覆盖到 $i$ 的区间可以再扩展一格）。

所以跳过区间后的转移点应该是越右越好。也就是不需要扩展到 $i$ 右边。

于是这个就是对的了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=100010;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,m,x[maxn],s[maxn],f[maxn]; 
int main(){
	n=read();m=read();
	FOR(i,1,n) x[i]=read(),s[i]=read();
	f[0]=0;
	FOR(i,1,m){
		f[i]=i;
		bool flag=false;
		FOR(j,1,n) if(x[j]+s[j]>=i && x[j]-s[j]<=i) flag=true;
		if(flag) f[i]=f[i-1];
		FOR(j,1,n) if(x[j]+s[j]<i) f[i]=min(f[i],f[max(0,2*x[j]-i-1)]+i-(x[j]+s[j]));
	}
	printf("%d\n",f[m]);
}
```

---

## 作者：youngk (赞：7)

作为一个官方正解为DP的题，我来一个神奇的做法，将这个问题转化成一个图论问题，变成一个最短路的问题。

我们不妨认为在图当作从$i$到$i+1$代表着将位置i给覆盖了。

首先我们我们知道覆盖一个一个地方至少需要$1$的代价，所以我们先建边，从$i$到$i+1$，代表覆盖位置$i$，距离为$1$。同时对于每个天线，我们不妨可以考虑一下从每个天线的L到R开始逐渐往两边扩张，每往外扩张一个单位需要加$1$的代价，知道碰到两端$1$或者$m+1$停止。同时我们也要注意到可能会有天线有重复覆盖的情况，因此还要建从$i+1$到$i$距离为0的边。

算法的复杂度为及为跑Dijkstra的复杂度，为 $O(mlogm)$。

代码:

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
#include<map>
#include<unordered_map>
#include<iomanip>
#include<bitset>
typedef long long ll;
#pragma GCC optimize(2)
#define maxm 8001000
#define maxn 200020
#define lowbit(x) x & -x
#define endl '\n'
using namespace std;
int n, m, s, t, cnt;
int head[maxn], to[maxm], Next[maxm], val[maxm], dis[maxn], a[maxn], b[maxn];
bool vis[maxn];
void add(int u, int v, int w)
{
	to[++cnt] = v;
	val[cnt] = w;
	Next[cnt] = head[u];
	head[u] = cnt;
}
void dijkstra()
{
	priority_queue<pair<int,int> > q;
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[s] = 0;
	q.push(make_pair(0, s));
	while (q.size())
	{
		auto u = q.top().second;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (int i = head[u]; i; i = Next[i])
		{
			int v = to[i];
			if (dis[v] > dis[u] + val[i])
			{
				dis[v] = dis[u] + val[i];
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	s = 1, t = m + 1;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
	}
	for (int i = 1; i <= m; i++)
		add(i, i + 1, 1), add(i + 1, i, 0);
	for (int i = 0; i < n; i++)
	{
		int k = 0;
		int l = max(1, a[i] - b[i]), r = min(a[i] + b[i] + 1, m + 1);
		int flag = 0;
		while (1)
		{
			l = max(1, l);
			r = min(r, m + 1);
			add(l, r, k);
			k++;
			if (l == 1 || r == m + 1)
				break;
			flag = 1;
			l--;
			r++;
		}
	}
	dijkstra();
	cout << dis[t] << endl;
	return 0;
}

```


---

## 作者：Qiaoqia (赞：2)

题解里的其它做法都好精妙啊，我来一种好想的 $O(n^2m)$ 做法吧（3 秒的时限不慌）。

看着 $n$ 那么小，考虑把 $n$ 放进状态里。$f(i, j)$ 表示覆盖到 $i$，$i$ 被第 $j$ 个覆盖缩需要的最小代价。然后分成两种情况，第一种是 $a_j \le i$，即第 $j$ 个天线在 $i$ 之前，另一种是在其后面。

对于后面的情况，如果前面也是用天线 $j$ 来覆盖，那么就不需要再加了，因为一定已经覆盖到当前了。否则枚举之前使用的天线 $k$，有转移 $f(i, j) \leftarrow f(i-1, k) + a_j - i - s_j$，即把天线 $j$ 操作到可以覆盖当前的位置。

对于前面的情况，我们就不能这样去转移了，因为往后拓展的时候可能会多覆盖到前面，花费会变得更小，所以得从当前点关于 $a_j$ 的对称点转移过来。即 $f(i, j) \leftarrow f(2a_j-i-1, k) + i - a_j - s_i$。

但是还有一种特殊情况要考虑（感谢样例四，不然我还真发现不了），天线为了覆盖到一个点，是可以多覆盖一点东西的。对于第二种情况，这表现为 $a_j$ 更接近 $i$ 而不是更接近 $1$ 时可能是直接把 $1 \to 2a_j-1$ 整段盖过。对于前面一种情况，不存在需要特殊照顾的情况，前面已经覆盖到了，而往后多的后面会考虑。所以只要加一个特判即可。

~~这个做法其实跑得挺快，最优解第四十九页。~~


```cpp
void main() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) std::cin >> a[i] >> s[i];
	memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= m; i++)
	    for (int j = 1; j <= n; j++)
	        if (a[j] <= i) 
	            for (int k = 1; k <= n; k++) {
    	            int w = std::max(i - a[j] - s[j], 0);
    	            if (2 * a[j] - i - 1 > 0) w += f[2 * a[j] - i - 1][k];
    	            f[i][j] = std::min(f[i][j], w);	            
    	            if (i - a[j] < a[j]) // 那个特判
        	            f[i][j] = std::min(f[i][j], std::max(0, a[j]-s[j]-1));
    	        }
    	    else {
    	        if (i != 1) f[i][j] = std::min(f[i][j], f[i-1][j]);
    	        for (int k = 1; k <= n; k++)
    	            f[i][j] = std::min(f[i][j], 
    	            ((i-1) ? f[i-1][k] : 0) + std::max(a[j]-i-s[j], 0));
    	    }
    std::cout << *std::min_element(f[m] + 1, f[m] + 1 + n); 
}
```

---

## 作者：Vsinger_洛天依 (赞：0)

#### 题目大意：

你现在有 $n$ 个天线，第 $i$ 个天线的位置为 $x_i$，每个天线的覆盖范围是 $[x_i-s_i,x_i+s_i]$，每次操作都可以花费 $1$ 的代价使覆盖范围 $s_i$ 增加 $i$ 问最少花费多少代价让 $[1,m]$ 被全部覆盖。

#### 做法：

$f(i,j)$ 表示覆盖到 $i，i$ 被第 $j$ 个覆盖缩需要的最小代价。然后分成两种情况。

如果  $a_j >i$，枚举之前使用的天线 $k$，可以知道 $f(i,j)=f(i−1,k)+a_j−i−s_j$，把天线 $j$ 操作到可以覆盖当前的位置。

如果  $a_j \le i$ 那就不太友善了，因为往后拓展的时候可能会多覆盖到前面，花费会变得更小，所以得从当前点关于 $a_j$ 的对称点转移过来。即 $f(i,j)=f(2a_j−i−1,k)+i−a_j−s_i$。

然后就可以直接做了，复杂度 $O(n^2m)$。

---

## 作者：lfxxx (赞：0)

先把所有天线按照 $x_i$ 排序。

对于一个前缀的天线选择方案，假若没有覆盖一个编号前缀，那么其中一定存在无用天线，因为后面的天线来填补前面的空时会让空后面的天线变得无用。

因此设计状态 $dp_{i,j}$ 表示考虑前 $i$ 个天线，覆盖了 $[1,j]$ 的最小花费，转移考虑从小往大枚举天线的覆盖半径，依次加入 $dp_{i-1,k}$ 的决策点即可做到 $O(n \times m)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxm = 1e5+114;
const int maxn = 100;
int dp[maxn][maxm];
int n,m;
pair<int,int> S[maxn];//(x_i,s_i)
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>S[i].first>>S[i].second;
	sort(S+1,S+n+1);
	memset(dp,0x3f3f3f3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		int mi=0x3f3f3f3f;
		for(int j=0;j<=m;j++){
			dp[i][min(m,S[i].first+j)]=min(dp[i][min(m,S[i].first+j)],max(0,max(S[i].first-1,j)-S[i].second));
		}
		for(int j=0;j<=m;j++){
			mi=min(mi,min(dp[i-1][max(1,S[i].first-j-1)],dp[i-1][min(m,S[i].first+j)]));
			dp[i][min(m,S[i].first+j)]=min(dp[i][min(m,S[i].first+j)],mi+max(0,j-S[i].second));
		}
		for(int j=1;j<=m;j++) dp[i][j]=min(dp[i][j],dp[i-1][j]);
		for(int j=1;j<m;j++) dp[i][j]=min(dp[i][j],dp[i][j+1]);
	}	
	cout<<dp[n][m]<<"\n";
	return 0;
}

```

---

## 作者：IAWNA (赞：0)

这题我采用一种时间复杂度为 $O(nm)$ 的 dp 方法。

我们设 $dp(i)$ 为前 i 个点均被覆盖的最小花费。

由于这题 n 很小，我们可以枚举每根天线并且枚举在这根天线上花费的钱数，记为 j 。（ j 从 1 到 m ）

则此时第 i 根天线能覆盖的范围为 $[x_i-s_i-j,x_i+s_i+j]$ 。

可以得到转移方程：

$$dp[x_i+s_i+j]=\min(dp[x_i+s_i+j],dp[x_i-s_i-j-1]+j)$$

注意 $x_i-s_i-j-1$ 可能小于 0 ，$x_i+s_i+j$ 可能大于 m 。

但是我们观察发现，对于两个位置 i 和 j ，如果 dp[i] < dp[j] 且 i > j ，那么 dp[j] 其实应该是等于 dp[i] 的，因为前 j 个全部被覆盖了前 i 个也一定全部被覆盖了。这种情况要考虑。

最后输出 $dp[m]$ 。

因为 $dp$ 数组要从小到大处理（不然 $dp[x_i+s_i+j]$ 可能有更好的方案没有被处理），所以我们首先要对所有天线按 $s_i$ 从小到大排序。

# 代码

是我在老师模拟赛上写的，数据范围不同，请见谅。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
inline void in(int &x)
{
	char c=getchar(),f=1;
	while((c<'0'||c>'9')&&c!='-')c=getchar();
	if(c=='-')c=getchar(),f=-1;
	for(x=0;c>='0'&&c<='9';c=getchar())
	x=x*10+c-'0';
	return ;
}
inline void fre()
{
	freopen("lamp.in","r",stdin);
	freopen("lamp.out","w",stdout);
	return ;
}
class N{
	public:
		int x,c;
		inline bool operator <(const N a)const{
			return x<a.x;
		}
		inline void _in()
		{
			in(x);in(c);
			return ;
		}
}a[105];
int dp[500005];
int main()
{
//	fre();
	memset(dp,0x7f,sizeof(dp));
	int n,m;
	in(n);in(m);
	for(int i=0;i<n;++i)a[i]._in();
	std::sort(a,a+n);
	dp[0]=0;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)
		{
			if(a[i].x-a[i].c-j<0&&a[i].x+a[i].c+j>m)break;//小优化，就是当这个天线将所有位置覆盖了的时候就可以跳过（花更多钱一定不优）
			dp[std::min(a[i].x+a[i].c+j,m)]=std::min(dp[std::min(a[i].x+a[i].c+j,m)],j+dp[std::max(a[i].x-a[i].c-j-1,0)]);
		}
		for(int j=m-1;j>=0;--j)dp[j]=std::min(dp[j],dp[j+1]);//处理 i>j 且 dp[i]<dp[j] 的情况
	}
	printf("%d\n",dp[m]);
	return 0;
}
```


---

