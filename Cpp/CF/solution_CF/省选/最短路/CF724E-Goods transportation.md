# Goods transportation

## 题目描述

There are $ n $ cities located along the one-way road. Cities are numbered from $ 1 $ to $ n $ in the direction of the road.

The $ i $ -th city had produced $ p_{i} $ units of goods. No more than $ s_{i} $ units of goods can be sold in the $ i $ -th city.

For each pair of cities $ i $ and $ j $ such that  $ 1<=i&lt;j<=n $  you can no more than once transport no more than $ c $ units of goods from the city $ i $ to the city $ j $ . Note that goods can only be transported from a city with a lesser index to the city with a larger index. You can transport goods between cities in any order.

Determine the maximum number of produced goods that can be sold in total in all the cities after a sequence of transportations.

## 样例 #1

### 输入

```
3 0
1 2 3
3 2 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 1
7 4 2 1 0
1 2 3 4 5
```

### 输出

```
12
```

## 样例 #3

### 输入

```
4 3
13 10 7 4
4 7 10 13
```

### 输出

```
34
```

# 题解

## 作者：panyf (赞：24)

$O(n\log n)$ 的解法

首先，很显然的网络流做法就是从源点 $S$ 向 $i$ 连权值为 $p_i$ 的边，从 $i$ 向汇点 $T$ 连权值为 $s_i$ 的边，对于任意 $i<j$ 从 $i$ 向 $j$ 连权值为 $c$ 的边，求最大流即可。

本题最重要的一点就是将最大流转化为最小割，用 dp 求出。令 $f_{i,j}$ 表示 dp 到点 $i$ ，有 $j$ 个点到 $S$ 的边未割掉。若割掉 $i$ 到 $S$ 的边，则还需割掉 $i$ 到那 $j$ 个点的边，即 $f_{i,j}=f_{i-1,j}+p_i+c\times j$ 。若割掉 $i$ 到 $T$ 的边，则 $f_{i,j}=f_{i-1,j-1}+s_i$ 。注意 $i$ 这一维要滚掉，时间复杂度 $O(n^2)$ ，已经能够通过本题。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=10003;
ll u[N],v[N],p[N];
int main(){
	int i,j,n;
	ll*f=u,*g=v,w=1e18,c,q;
	cin>>n>>c;
	for(i=1;i<=n;++i)cin>>p[i];
	for(i=1;i<=n;++i){
		swap(f,g),cin>>q,f[0]=g[0]+p[i],f[i]=g[i-1]+q;
		for(j=1;j<i;++j)f[j]=min(g[j-1]+q,g[j]+p[i]+c*j);
	}
	cout<<*min_element(f,f+n+1);
	return 0;
}
```
考虑贪心优化。令 $a_i=c\times(n-i)+s_i-p_i$ ，并将 $a$ 数组从小到大排序。开始先割掉所有到 $S$ 的边，之后按顺序依次割掉到 $T$ 的边并恢复到 $S$ 的边。当割掉 $a_i$ 代表的点到 $T$ 的边时，答案加上 $a_i-c_i\times(i-1)$ 。减去 $c_i\times(i-1)$ 是因为之前的 $i-1$ 个点到当前点的权值为 $c$ 的边已经被割掉了，就不用再加上了。

至此，贪心的正确性也很显然了。考虑任意 $i<j$ ，若 $a_i$ 代表的点割掉了到 $S$ 的边，而 $a_j$ 代表的点割掉了到 $T$ 的边，那么我们让 $a_i$ 割掉到 $T$ 的边， $a_j$ 割掉到 $S$ 的边，答案就会增加 $a_i-a_j$ ，而 $a_i-a_j<0$ ，所以答案更优。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int p[10003];
ll a[10003]; 
int main(){
	int n,s,i;
	ll w,c,o=0;
	cin>>n>>c;
	for(i=1;i<=n;++i)cin>>p[i],o+=p[i];
	for(i=1;i<=n;++i)cin>>s,a[i]=c*(n-i)+s-p[i];
	w=o,sort(a+1,a+n+1);
	for(i=1;i<=n;++i)w=min(w,o+=a[i]-c*(i-1));
	cout<<w;
	return 0;
}
```


---

## 作者：Zimse (赞：8)

网络流做法:
就是从源点 $S$ 向每个城市 $i$ 连权值为 $p_i$ 的边，从城市 $i$ 向汇点 $T$ 连权值为 $s_i$ 	的边，当$i<j$时从城市 $i$ 向城市 $j$ 连权值为 $c$ 的边，求最大流即可

![样例2建图](https://cdn.luogu.com.cn/upload/image_hosting/zxbwmuyb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因为[最大流等于最小割](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E6%B5%81%E6%9C%80%E5%B0%8F%E5%89%B2%E5%AE%9A%E7%90%86/3851799),所以考虑如何找最小割

断开一个点连接原点和汇点的路径

方案一:断开与原点 $S$ 的边，同时也要断开连接其他编号比 $i$ 小且与 $S$ 连接的点的边

方案二:断开与汇点 $T$ 的边

考虑使用dp, $f_{i,j}$ 表示前 $i$ 个点已经断开,但是编号比 $i$ 小的有 $j$ 个点与 $S$ 连接

使用方案一: $f_{i,j}=f_{i-1,j}+p_i+c*j$

使用方案二: $f_{i,j}=f_{i-1,j-1}+s_i$


------------

核心代码:

注意开long long

```cpp
signed main(){
	n=read(),c=read();
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<=n;i++)s[i]=read();
	for(int i=1;i<=n;i++){
		f[i]=f[i-1]+s[i];
		for(int j=i-1;j>=1;j--)f[j]=min(f[j-1]+s[i],f[j]+p[i]+c*j);
		f[0]+=p[i];}
	for(int i=0;i<=n;i++)ans=min(ans,f[i]);
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：zhoukangyang (赞：7)

# CF724E Goods transportation
## 蒟蒻译
题目就是说，有 $n$ 个城市，$1 ... n$ 编号，每个城市生产 $p_i$ 个货物，最多可卖掉 $s_i$ 个货物。城市之间可以从编号小的往编号大的运输货物并卖出。求最大能卖出多少货物。

## 蒟蒻语
这是蒟蒻的第一道模拟费用流。

写个题解纪念以下吧。
## 蒟蒻解
首先是一个显然的网络流模型:

先建立一个超级源点与一个超级汇点。

然后把每一个点连向编号比它大的节点，流量为 $c$。从超级源点向 $i$ 连一条流量为 $p_i$ 的边，从 $i$ 向超级汇点连一条流量为 $s_i$ 的边。最后求网络最大流。

这样显然不行，在见图方面就 $\rm GG$ 了。考虑到 **最大流 = 最小割**，可以考虑到求解最小割。

显然可以把整张图分为两个集合，第一个集合包含超级源点 $S$，向外输出流量；第二个集合包含超级汇点 $T$，接受向该点流出的流量。

考虑到题目中说的**从编号小的连向编号大的**，说明了这是无后效性的。

所以可以考虑使用 $dp$。$dp_{i,j}$ 表示前 $i$ 个节点中有 $j$ 个节点是在第一个集合中的。

考虑 $dp$ 转移方程：如果点 $i$ 在第一个集合中，只要把该点到超级汇点 $T$ 的边割掉即可；如果点 $i$ 在第二个集合中，要把超级源点 $S$ 到该店的边割掉，还要把之前向外输出流量的点 (就是在第一个集合中的点)到该点的边割掉。

不难得到 $dp$ 方程：
$$dp_{i,j} = \max(dp_{i-1,j-1} + s_i, dp_{i-1}{j} + c * j + p_i)$$
然而这样空间复杂度爆炸，只要把 $dp$ 数组改称滚动数组即可
## 蒟蒻码
```cpp
#include<bits/stdc++.h>
#define N 110000
using namespace std;
int n;
long long dp[2][N], c, s[N], t[N], Ans = 1e18;
int main() {
    scanf("%d%lld",&n,&c);
    for(int i = 1; i <= n; i++) scanf("%lld",&s[i]);
    for(int i = 1; i <= n; i++) scanf("%lld",&t[i]);
    for(int i = 1; i <= n; i++) dp[1][i] = 5e17;
    for(int i = 1; i <= n; i++) {
        dp[0][0] = dp[1][0] + s[i];
        for(int j = 1; j <= i; j++) dp[0][j] = min(dp[1][j-1] + t[i], dp[1][j] + s[i] + c * j); 
        for(int j = 0; j <= i; j++) dp[1][j] = dp[0][j];
    }
    for(int i = 0; i <= n; i++) Ans = min(Ans, dp[1][i]);
    printf("%lld\n", Ans);
    return 0;
}
```
---
祝大家学习愉快！

---

## 作者：UperFicial (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF724E)

同步发表于我的 [$\texttt{cnblog}$](https://www.cnblogs.com/UperFicial/p/16159175.html)。

### $\texttt{Solution}$

有 $n$ 个城市，若 $i<j$，则 $i$ 向 $j$ 最多运送 $c$ 个货物。

第 $i$ 个城市初始有 $p_i$ 个货物，最多卖 $s_i$ 个货物。

求最多卖掉的货物的数量。

$1\le n\le 10^4$。

### $\texttt{Description}$

好神的题啊/se，但可能我理解太弱了，感觉楼下的 DP 讲的太模糊了

考虑一个非常显然的网络流：

- $s$ 向每一个城市 $i$，连一条容量为 $p_i$ 的边。

- 每一个城市 $i$ 向 $t$，连一条容量为 $s_i$ 的边。

- 对于 $i<j$ 的两个城市 $i,j$，从 $i$ 向 $j$ 连一条容量为 $c$ 的边。

这样建图的边数是 $n^2$ 级别的，跑网络流直接炸飞。

这时候就用到一个小 $\texttt{trick}$：最大流 $=$ 最小割。我们可以通过求最小割来求出最大流。

考虑 DP，设 $f_{i,j}$ 表示，到了第 $i$ 个点，有 $j$ 个和 $s$ 的边未被割掉。

为什么这个东西可以 DP 呢？因为题目中有一个重要条件：$i<j$，说明边不会形成环，也就是说，没有后效性。

回到正题，考虑转移。

一个点 $i$ 有两种选择，断掉它于 $s$ 的边，或断掉与 $t$ 的边。

若断掉与 $s$ 的边，不光需要断掉与 $s$ 之间，容量为 $p_i$ 的边，还需要断掉，和 $s$ 之间没有断掉边的，那 $j$ 个点之间的边，每一条边的容量都是 $c$，一共需要断 $j$ 条，所以需要断掉的容量是 $c\times j$。

这只是 $i$ 一个点的花费，它还需要加上前 $i-1$ 个点的花费。

此时 $i$ 是不算在 $j$ 个节点内的，所以前 $i-1$ 个节点中，一共有 $j$ 个是与 $s$ 直接相连。 

所以此时，$f_{i,j}=f_{i-1,j}+p_i+c\times j$。

同理，如果断掉与 $t$ 的边，则只需要断掉 $s_i$ 那条边，但是此时，$i$ 已经算在 $j$ 个点内了，所以前 $i-1$ 个只有 $j-1$ 个与 $s$ 直接相连。

所以此时，$f_{i,j}=f_{i-1,j-1}+s_i$。

两者取 $\min$，得到转移方程：

$$f_{i,j}=\min(f_{i-1,j}+p_i+c\times j,f_{i-1,j-1}+s_i)$$

最终答案为 $\min_{0\le i\le n}\{f_{n,i}\}$。

但是空间会爆炸，所以直接将第一维滚动数组滚掉就好了。

最终时间复杂度 $\Theta(n^2)$，空间复杂度 $\Theta(n)$，可以通过本题。

代码就不放了，核心也就 $\texttt{5,6}$ 行的样子，需要者私信。

[$\texttt{AC}$ 链接](https://www.luogu.com.cn/record/74172599)。

$$\texttt{The End.by UF}$$


---

## 作者：FatOldEight (赞：2)


[题目描述](https://www.luogu.com.cn/problem/CF724E)

### 做法

首先晃眼一看：这不是网络流傻子题吗？

于是立刻建了个图跑最大流：

1. 建立源点 $S$，向第 $i$ 个点建立一条容量为 $p_i$ 的边；

2. 建立汇点 $T$，第 $i$ 个点向 $T$ 建立一条容量为 $s_i$ 的边；

3. 对于所有的 $i<j$，由 $i$ 向 $j$ 建立一条容量为 $c$ 的边。

正当建完图打算教的时候，定睛一看：$n\le10000$，这不明摆着 TLE？

于是就需要另外一个方法：模拟网络流。

首先因为最大流等于最小割，于是原问题就变成了求原网络的最小割。

显然对于一种最小割，每个点要么属于 $S$ 所在的集合，要么属于 $T$ 所在的集合。

并且是由小的连向大的，所以无后效性。

于是令 $f_{i,j}$ 表示前 $i$ 个点中，有 $j$ 个点属于 $S$ 集合的最小割。

于是对于点 $i$，有两种方案：

1. $i$ 属于 $S$ 集合，则割掉 $i$ 连向 $T$ 的边

2. $i$ 属于 $T$ 集合，则割掉 $i$ 连向 $S$ 的边和连向下标小于 $i$ 的边。

故转移方程为：$f_{i,j}=\min(f_{i-1,j}+p_i+j\times c,f_{i-1,j-1}+s_i)$

空间开不下，要使用滚动数组。

### 代码

``` cpp
#include<cstring>
#include<iostream>
#define int long long
using namespace std;
int f[2][10005],n,a[10005],s[10005],c;
signed main()
{
    scanf("%lld%lld",&n,&c);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&s[i]);
    for(int i=1;i<=n;i++)
    {
        memset(f[i&1],0x7f,sizeof(f[i&1]));
        f[i&1][0]=f[(i-1)&1][0]+a[i];
        for(int j=1;j<=i;j++)f[i&1][j]=min(f[(i-1)&1][j-1]+s[i],f[(i-1)&1][j]+a[i]+j*c);
    }
    int ans=2e18;
    for(int i=0;i<=n;i++)ans=min(ans,f[n&1][i]);
    printf("%lld",ans);
}
```




---

## 作者：EternalAlexander (赞：2)

有一个显然的最大流做法，超级源向城市连边，城市向编号更大的城市连边，然后向超级汇连边，跑最大流即可。   
然后因为数据范围比较大这样是跑不过去的。  

因为最大流等于最小割，考虑用dp来求这个最小割。dp[i][j]表示考虑前i个节点，有j个节点和超级源相连，然后如果当前节点和汇相连的话就要把它和之前所有和源相连的节点之间的边都割掉，还要把它和源之间的边割掉；如果和源相连就割掉和汇相连的边就行了。这样就可以转移了。

然后因为空间问题第一维要滚掉。

```cpp
#include <bits/stdc++.h>
#define ll long long
const ll inf=(ll)1<<(ll)50;
ll dp[2][10005]={0},ans=inf;
int n,c,s[10005],t[10005];

int main() {
	scanf("%d%d",&n,&c);
	for (int i=1;i<=n;++i) scanf("%d",&s[i]);
	for (int i=1;i<=n;++i) scanf("%d",&t[i]);
	for (int i=1;i<=n;++i) {
		int x=i%2; std::memset(dp[x],0,sizeof(dp[x]));
		dp[x][0]=dp[x^1][0]+s[i];dp[x][i+1]=inf;
		for (int j=i;j>=1;--j) dp[x][j]=std::min(dp[x^1][j]+c*j+s[i],dp[x^1][j-1]+t[i]);
	} for (int i=0;i<=n;++i) ans=std::min(ans,dp[n%2][i]);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：tai_chi (赞：1)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18445458) 中阅读。

### 题意

有 $n$ 座城市，第 $i$ 座城市生产了 $p_i$ 件货物，最多可以出售 $s_i$ 件货物，编号小的城市可以向编号大的城市运输至多 $c$ 件货物，问最多能出售多少货物。

$n \le 10^4$。

### 分析

乍一看是一个网络流问题，可以这样建图，令 $S$ 为源点 $T$ 为汇点：

$$S \xrightarrow{p_i} i \xrightarrow{s_i} T$$

$$i \xrightarrow{c} j (i < j)$$

然后跑一个最大流就可以。但这样建边第二类就会有 $O(n^2)$ 条边，寄。

模拟费用流就是应对这样的情况的。我们把最大流问题转换为最小割问题，然后考虑使用 DP 求解。

令 $f(i,j)$ 表示前 $i$ 个点，$j$ 个点与 $S$ 的连边未断开，注意到 $(S,i)$ 与 $(i,T)$ 必断其一，则有转移：

$$f(i,j) = \min 
\begin{cases}
	f(i-1,j) + p_i + c \times j \\
	f(i-1,j-1) + s_i
\end{cases}$$

分别表示：

1. 断开 $(S,i)$ 需要断开与前面所有未断开与 $S$ 连边的点的连边；
2. 断开 $(i,T)$。

时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

const int N=1e5+5;
int n,c;
int s[N],p[N];
int f[N];

signed main()
{
	IOS;
	cin>>n>>c;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++)
	{
		f[i]=f[i-1]+s[i];
		for(int j=i-1;j>=1;j--)
			f[j]=min(f[j]+c*j+p[i],f[j-1]+s[i]);
		f[0]+=p[i];
	}
	int ans=1e16;
	for(int i=0;i<=n;i++) ans=min(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Filberte (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF724E)

## 思路

有一种显然的网络流建图方法，点数 $O(n)$，边数 $O(n^2)$，无法通过此题。考虑把最大流问题转为最小割问题，可以把原问题进行等价转化：给定 $1 \sim n$ 一共 $n$ 个点，每个点要么向源点连边，代价为 $p_i$；要么向汇点连边，代价为 $s_i$。对于每对 $(i,j)$，如果满足 $i < j$，$i$ 向源点连边且 $j$ 向汇点连边，则额外需要 $c$ 的代价。求一种连边方式使得代价和最小。

$O(n^2)$ 的动态规划是显然的，别的题解已经讲得很明白了，这里不再赘述。

再提供一种 $O(n\log n)$ 的贪心解法。我们先假定所有的点都向汇点连边，考虑把第 $i$ 个点改为连向源点时答案的变化量。定义 $w(i)$：首先对于所有编号比 $i$ 小且连向源点的点，其代价减少 $c$；其次对于所有编号比 $i$ 大且连向汇点的点，其代价增加 $c$。最后别忘了加上 $s_i - p_i$。令 $f(i)$ 表示编号比 $i$ 小且连向源点的点有多少个，$g(i)$ 表示编号比 $i$ 大且连向汇点的点有多少个， $w(i) = c(g(i) - f(i)) +s_i - p_i$。

观察到有一个很好的性质：当 $i$ 改向连向汇点时，其它每个点的 $w$ 值恒定减少 $c$。这是因为对于编号比 $i$ 小的点 $x$ 而言，编号比 $x$ 大且连向汇点的点少了一个，$g(x)$ 减少了 $1$；而对于编号比 $i$ 大的点 $x’$ 而言，编号小于 $x'$ 且连向源点的点多了一个，$f(i)$ 增加了 $1$。无论是二者中哪一种，$w(i)$ 都会相应减少 $c$。由此得出一个重要推论：无论你按什么顺序选，对于 $x,y$ 这两个目前连向源点的点，它们 $w$ 值的**大小关系不会改变**。

按照 $w$ 从小到大排序，刚开始假设全部点都连向汇点，目前的答案是 $\sum\limits_{i = 1}^n p_i$。每次贪心的选择当前 $w$ 值最小的出来改为连向源点。但因为选的点越多，后边 $w$ 的值就会越小，所以并不是选到 $w$ 为正的时候就停止了，而是应该记录选 $k$ 个点连向汇点时，答案的最小值 $r_k$，最终的答案是 $\min\limits_{i\in[1,n]} r_i$。过程详见代码。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 10050;
int p[N], s[N];
int ans, cur;
priority_queue<int, vector<int>, greater<int>> q;
int32_t main(){
    int n, c;
    cin >> n >> c;
    for(int i = 1;i <= n;i++) cin >> p[i];
    for(int i = 1;i <= n;i++) cin >> s[i];
    for(int i = 1;i <= n;i++){
        cur += p[i];
        q.push(s[i] - p[i] + c * (n - i));
    }
    ans = cur;
    for(int i = 1;i <= n;i++){
        cur += q.top() - (i - 1) * c;
        q.pop();
        ans = min(ans, cur);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：BF_AlphaShoot (赞：1)

[题目传送门](http://codeforces.com/problemset/problem/724/E)。

有显然的**网络流**模型：选定源点与汇点，从源点向每一个点 $i$ 连一条流量为 $p_i$ 的边，从每个点 $i$ 向汇点连一条流量为 $s_i$ 的边，每一个点连向编号比它大的节点，流量为 $c$，之后求最大流即可。

可惜的是由于数据范围过大这样的最大流解法会被卡掉。想到最大流可以转化为最小割，所以转化为 **DP** 解决。设 $f_{i,j}$ 为前 $i$ 个节点中有 $j$​​​ 个与源点相连。

如果点 $i$ 与源点相连，要割掉该点到汇点的边；如果点 $i$​ 与汇点相连，不仅要割掉源点到该点的边，还要把之前向外输出流量的点到该点的边割掉。

因此有状态转移方程：
$$
f_{i,j}=\min(f_{i-1,j-1}+s_i,f_{i-1,j}+p_i+c\times j)
$$
空间复杂度过高，在实现中应当使用滚动数组。

View code：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ri register int
#define il inline

const ll INF=0x7fffffffffff,N=1e5+10;
ll n,c,ans=INF;
ll p[N],s[N];
ll f[N][2];

il ll read(){
    ll x=0,y=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}

signed main(){
    n=read(),c=read();
    for(ri i=1;i<=n;i++)
        p[i]=read();
	for(ri i=1;i<=n;i++)
        s[i]=read();
    for(ri i=1;i<=n;i++)
        f[i][1]=INF;
    for(ri i=1;i<=n;i++){
        f[0][0]=f[0][1]+p[i];
        for(ri j=1;j<=i;j++)
            f[j][0]=min(f[j-1][1]+s[i],f[j][1]+p[i]+c*j);
        for(ri j=0;j<=i;j++)
            f[j][1]=f[j][0];
    }
    for(ri i=0;i<=n;i++)
        ans=min(ans,f[i][1]);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：lhm_ (赞：1)

先考虑一种网络流解法，从源点 $S$ 向每个点连容量为 $p_i$ 的边，每个点向汇点连容量为 $s_i$ 的边，每个点向编号比其大的点连容量为 $c$ 的边，该图的最大流即为答案。

但是复杂度无法接受，考虑换一种思路，观察建出的图：

![](https://s1.ax1x.com/2020/08/24/drBcXF.png)

发现这张图比较特殊，像最小割的模型，考虑将求最大流转为求最小割，用考虑 $DP$ 来解决。设 $f_{i,j}$ 为考虑了前 $i$ 个点，有 $j$ 个点与源点相连的最小割花费，得转移方程为：
$$
\large f_{i,j}=\min\left(f_{i-1,j-1}+s_i,f_{i-1,j}+p_i+jc\right)
$$
即转移为点 $i$ 是和源点相连还是和汇点相连。$DP$ 数组开不下，需要用滚动数组。

```cpp
#include<bits/stdc++.h>
#define maxn 10010
#define inf 10000000000000000
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
ll n,c,x,ans=inf;
ll p[maxn],s[maxn],f[2][maxn];
int main()
{
    read(n),read(c);
    for(int i=1;i<=n;++i) read(p[i]);
    for(int i=1;i<=n;++i) read(s[i]);
    for(int i=1;i<=n;++i,x^=1)
    {
        f[x][0]=f[x^1][0]+p[i];
        for(int j=1;j<=n;++j) f[x][j]=inf;
        for(int j=1;j<=i;++j)
            f[x][j]=min(f[x^1][j-1]+s[i],f[x^1][j]+p[i]+j*c);
    }
    for(int i=0;i<=n;++i) ans=min(ans,f[x^1][i]);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：D2T1 (赞：0)

[Luogu Link](https://www.luogu.com.cn/problem/CF724E)

## CF724E $O(n^2)$ 做法题解

看到题面考虑网络流。新建超级源点 $S$，超级汇点 $T$，连边：

- $(S,i,p_i) ,1\leq i\leq n$；
- $(i,T,s_i) ,1\leq i\leq n$；
- $(i,j,c),1\leq i <j\leq n$。

对于样例 $3$，建出的图如下所示：

![graph.png](https://s2.loli.net/2022/06/10/dtjQADGc7auZkW9.png)

然后求得 $S$ 到 $T$ 的最大流，即为答案。

------------

但是这样做图上的边数是 $n^2$ 级别的，显然过不了。

怎么办呢？把最大流转为最小割，考虑 DP，设 $f_{i,j}$ 表示前 $i$ 个点中有 $j$ 个点与源点 $S$ 的边未割掉。答案即为 $\min\limits_{i=0}^n f_{n,i}$。

接下来考虑状态转移方程。枚举**当前节点 $i$，有 $j$ 个点与源点 $S$ 的边未割掉**。对于节点 $i$，肯定要断掉它与 $S$ 的连边，或它与 $T$ 的连边。

- 若删除 $i$ 与 $S$ 的连边，则还需删除 $i$ 与**编号比 $i$ 小的那些节点中与 $S$ 的边未割掉的那些节点（个数为 $j$）**的连边，割掉的总边权为 $p_i+c*j$。
- 若删除 $i$ 与 $T$ 的连边，则只需删除边 $(i,T,s_i)$ 即可。（因为 $i$ 流到编号更大的节点再流到 $T$ 的路径这里还不需要考虑）

因此状态转移方程为：

$$f_{i,j}=\min(f_{i-1,j}+p_i+c*j,f_{i-1,j-1}+s_i)$$

接下来考虑边界：

枚举的时候，$i$ 肯定从 $1$ 到 $n$，$j$ 从 $0$ 到 $n$（注意 $j$ 的值为 $0$ 的时候，状态转移方程的变化，代码中体现了这一点）。

因为是求最小值，$f$ 数组最开始全设为正无穷，$f_{0,0}$ 设为 $0$。（但其实没有必要）

```cpp
//CF724E
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 1e3 + 10; 
long long c, p[N], s[N], f[N][N], ans = 1e17;
int n;

int main(){
	scanf("%d%lld", &n, &c);
	for(int i = 1; i <= n; ++ i) scanf("%lld", &p[i]);
	for(int i = 1; i <= n; ++ i) scanf("%lld", &s[i]);
	memset(f, 0x3f, sizeof(f));f[0][0] = 0;
	for(int i = 1; i <= n; ++ i){
		f[i][0] = f[i-1][0] + p[i];
		for(int j = 1; j <= i; ++ j)
			f[i][j] = min(f[i-1][j] + p[i] + c * j, f[i-1][j-1] + s[i]);
	} 
	for(int i = 0; i <= n; ++ i) ans = min(ans, f[n][i]);
	printf("%lld\n", ans);
	return 0;
}
```

这样空间复杂度是 $O(n^2)$ 不能通过。可以考虑滚动数组。

```cpp
//CF724E
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 1e4 + 10; 
long long c, p[N], s[N], f[2][N], ans = 1e17;
int n;

int main(){
	scanf("%d%lld", &n, &c);
	for(int i = 1; i <= n; ++ i) scanf("%lld", &p[i]);
	for(int i = 1; i <= n; ++ i) scanf("%lld", &s[i]);
	for(int i = 1; i <= n; ++ i) f[0][i] = 1e17;
	for(int i = 1; i <= n; ++ i){
		f[1][0] = f[0][0] + p[i];
		//这一句拿出来，原因见上
		for(int j = 1; j <= i; ++ j)
			f[1][j] = min(f[0][j] + p[i] + c * j, f[0][j-1] + s[i]);
		for(int j = 0; j <= i; ++ j) f[0][j] = f[1][j];
		//这里j<=i，所以f[0][i+1]后面的还是无穷大
	} 
	for(int i = 0; i <= n; ++ i) ans = min(ans, f[0][i]);
	printf("%lld\n", ans);
	return 0;
}
```

这里将 $f$ 数组初始为正无穷的意义是什么？可以发现在状态转移时出现了 $f_{i-1,j}$ 一项，这时 $i-1$ 有可能小于 $j$。再回想状态定义，这种情况是不合法的。如果这样初始化，这种不合法的情况就不会被考虑；反之如果初始化全为 $0$，就会出现错误。滚动数组的代码里的初始化也能起到这个效果。

所以你也可以这么初始化：

```cpp
//for(int i = 1; i <= n; ++ i) f[0][i] = 1e17;
for(int i = 1; i <= n; ++ i){
	for(int j = i+1; j <= n; ++ j) f[0][j] = 1e17;
	f[1][0] = f[0][0] + p[i];
	for(int j = 1; j <= i; ++ j)
		f[1][j] = min(f[0][j] + p[i] + c * j, f[0][j-1] + s[i]);
	for(int j = 0; j <= i; ++ j) f[0][j] = f[1][j];
} 
```

甚至：

```cpp
//for(int i = 1; i <= n; ++ i) f[0][i] = 1e17;
for(int i = 1; i <= n; ++ i){
	f[0][i+1] = 1e17;
	f[1][0] = f[0][0] + p[i];
	for(int j = 1; j <= i; ++ j)
		f[1][j] = min(f[0][j] + p[i] + c * j, f[0][j-1] + s[i]);
	for(int j = 0; j <= i; ++ j) f[0][j] = f[1][j];
} 
```

---

## 作者：小木虫 (赞：0)

### Preface  
特殊建模网络流模拟 dp。
### Problem  
有 $n$ 个点，最多从 $i$ 点流进 $p_i$ 的流量，流出 $s_i$ 的流量。并且每对 $i,j(i\leq j)$ 可以从 $i$ 流向 $j$ 点 $c$的流量。求最大流。  
### Solution  
一看数据范围那网络流指定是有点悬，至少对于我这种只会 DINIC 的蒟蒻来说直接用网络流求解不太可能。但是我们可以看到这个图是有特殊性质的：  

额外边仅仅会从小流到大。  

哎？那这不是一只 DAG 吗？  
一般来说 DAG 图会有一些神奇的 dp 相关解法。  
但是很显然最大流的决策 dp 没办法直接做，但是！dp 可以做最小割决策呀！最小割等于最大流，不是吗？  
那对于每个点有两种选择：割掉源边或汇边。  
如果割掉源边的话，那么那些小于这个点并且割掉了汇边的点会通过这个点流过去。  
很显然我们要把这些点连向当前点的边全部割掉。  
如果割掉汇边的话，那么不会有额外的代价，但是会使后面选择的点付出代价。  
于是我们可以设计 dp 状态：$dp_{i,j}$ 为选到 $i$ 点，有 $j$ 个点割掉了汇边的最小代价。  
那么可以设计出转移方程：  
$dp_{i,j}=\min(dp_{i-1,j}+p_i+c×j,dp_{i-1,j-1}+s_i)$  
套个滚动数组这题就做完了。  
code：  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=10010;
ll dp[2][N];ll n,c;
ll p[N],s[N];int cur;
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>c;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++){
		fill(dp[cur],dp[cur]+n+1,1e15);
		for(int j=0;j<=i;j++){
			dp[cur][j]=min(dp[cur^1][j]+j*c+p[i],dp[cur][j]);
			if(j>0)dp[cur][j]=min(dp[cur^1][j-1]+s[i],dp[cur][j]);
		}
		cur^=1;
	} 
	ll res=1e15;cur^=1;
	for(int i=0;i<=n;i++)res=min(res,dp[cur][i]);
	cout<<res;
	return 0;
}
```


---

## 作者：PosVII (赞：0)

**前言**

------------

第一个一遍过的黑，开心。

做网络流的时候偶然看到，结果是模拟网络流。

**正文**

------------

网络流的建边方式很简单，就是源点向每个城市连边，每个城市向汇点连边，再对后面的所有城市连边即可。可是这明显会 TLE。这个图很清奇，不难发现可以直接用动态规划转化成最小割。滚动优化即可。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
template<typename G>inline void read(G&x){x=0;G f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();x*=f;}
const int MAXN=1e4+5;
long long p[MAXN],s[MAXN],n,c;
long long ans=LONG_LONG_MAX,dp[MAXN];
int main() {
	read(n),read(c);
	for(int i=1;i<=n;++i) read(p[i]);
	for(int i=1;i<=n;++i) read(s[i]);
	for(int i=1;i<=n;++i) {
		dp[i]=dp[i-1]+s[i];
		for(int j=i-1;j>=0;--j) {
			dp[j]=dp[j]+p[i]+c*j;
			if(j>=1) dp[j]=min(dp[j],dp[j-1]+s[i]);
		}
	}
	for(int i=0;i<=n;i++) ans=min(ans,dp[i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：JiaY19 (赞：0)

萌新蒟蒻第一次写模拟网络流。

首先思考如何用网络流做掉这一题。

建立超级原点向每一个点连边，再建立超级汇点，让每一个点向超级汇点连边。

边权分别为 $p_{i}$ 和 $s_{i}$。

我们发现最大流不好求，转化为求最小割。

因为最大流=最小割，所以直接求就行了。

考虑dp来求这个最小割。

我们发现，当前情况下有两种割断的方法。

1. 直接割断连接汇点的边。

2. 割断与原点的边和与比它小的边。

我们发现可以直接滚掉一维，让 $dp[i]$ 表示当前割断整个图的最小代价。

因此，转化为动规式就是这个东西：

$$dp_{i} \gets \min(dp_{j - 1} + s_{i} , dp_{j} + c \times j + p_{i})$$

我们发现这个动态规划可以直接 $O(n^2)$ 来求。

至于其他大佬的 $O(n\log{n})$ 的方法，我肯定是不会的了(萌新怎么会这种东西)。

#### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n , c , ans , p[10010] , s[10010] , dp[10010];

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();   
    return asd * qwe;
}

signed main()
{
    n = read() , c = read() , ans = 1e15;
    for(int i = 1;i <= n;i++) p[i] = read();
    for(int i = 1;i <= n;i++) s[i] = read();

    for(int i = 1;i <= n;i++)
    {
        dp[i] = dp[i - 1] + s[i];
        for(int j = i - 1;j >= 1;j--)
            dp[j] = min(dp[j - 1] + s[i] , dp[j] + c * j + p[i]);
        dp[0] += p[i];
    }

    for(int i = 0;i <= n;i++)
        ans = min(ans , dp[i]);
    cout << ans;
    return 0;
}

```

---

