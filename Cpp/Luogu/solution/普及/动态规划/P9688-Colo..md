# Colo.

## 题目描述

小 F 和小 Y 经常在一起玩耍，因为小 F 是一个画家，他喜欢在一个长度为 $n$，宽度为 $1$ 的网格图上画画，从左往右第 $i$ 个方格被涂成了一种颜色 $a_i$。

你觉得他的随意涂鸦太难看了，想要保留恰好 $k$ 种颜色（**你不能保留没在网格图上出现的颜色**），使得网格图上没被涂成任何一种你喜欢的颜色的网格都被剪掉，最后会剩下一些网格，你希望这些网格从左到右颜色的编号是单调不下降的。

此外，小 Y 使用的第 $i$ 种颜色有一个价值 $b_i$，小 Y 看到了你裁剪后的网格图很是高兴，于是决定付给你你选择的颜色的价值总和。

你需要求出你能够获得的最大的价值是多少。

## 说明/提示

#### 【样例解释 #1】

对于第一组样例，我们可以选择 $1$ 号和 $3$ 号颜色保留，剩下的网格图即为 $[1,1,3]$，满足单调不下降这一个限制，获得的价值即为 $b_1+b_3=5+1=6$，可以证明这是最优的办法。

#### 【数据范围】

对于所有测试数据，满足 $1 \le n \le 500$，$1 \le k \le 500$，$1 \le a_i \le n$，$1 \le b_i \le 10^9$。

**本题开启捆绑测试，所有数据范围均相同的测试点捆绑为一个 $\text{Subtask}$。**

各测试点的附加限制如下表所示。

| 测试点 | $n,k \le $ | 特殊性质 |
| :-----------: | :-----------: | :-----------: |
| $1 \sim 3$ | $10$ | 无 |
| $4 \sim 5$ | $100$ | 无 |
| $6 \sim 10$ | $500$ | 不同的颜色不超过 $10$ 种 |
| $11 \sim 15$ | $500$ | 每种颜色出现的次数不超过 $2$ 次 |
| $16 \sim 20$ | $500$ | 无 |


## 样例 #1

### 输入

```
5 2
1 2 1 3 2
5 3 1 100 100```

### 输出

```
6```

## 样例 #2

### 输入

```
10 3
1 3 4 2 9 3 4 2 5 1
1 5 2 3 9 8 1 2 3 10```

### 输出

```
-1```

# 题解

## 作者：卷王 (赞：27)

## 题意转化

[原题](https://www.luogu.com.cn/problem/P9688)

别看题目说的那么繁琐，又剪又拼的，其实概括一下就是一句话：

> 一个有 $n$ 个格子的长纸条，第 $i$ 个格子颜色为 $a_i$，价值为 $b_i$，现在要任选 $k$ 种颜色，使得 **所有颜色是较大编号** 的格子都在 **较小编号** 的后面，求最大价值。

## 大体思路

阅读题目可以发现 $O(n^3)$ 是可以过的（洛谷评测机 $10^9$ 开 O2 都能过，$10^8$ 显然是可以的），那么我们可以想到使用 dp。不像某些题解的代码那么长，其实只需要处理一下题目中额外的要求就行了。

设 $dp_{i,j}$ 表示考虑前 $i$ 种颜色并选用第 $i$ 种颜色，一共选择了 $j$ 种颜色的方案数（经典的 **问啥设啥**）。

转移方程为 $dp_{i,j}= \max(dp_{i,j}, dp_{m,j-1}) + b_{a_i}$，$m$ 是在前面选中的颜色下标（即 $0 \leq m < i$）。

我们还要定义两个数组 $l,r$ 分别表示一种颜色第一次出现的位置和最后一次出现的位置，便于在 dp 中判断。这个题目就做完了。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, k; ll ans = -1;
int a[507], b[507];
int l[507], r[507]; //这两个数组记录颜色为 i 的区间
ll dp[507][507];
//dp[i][j] 表示考虑前 i 种颜色并选用第 i 种颜色，一共选择了 j 种颜色的方案数

int main() {
	n = read(), k = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read();
		if(l[a[i]] == 0) l[a[i]] = i;
		r[a[i]] = i;
	}
	for(int i = 1; i <= n; i++) b[i] = read();
	memset(dp, -0x3f, sizeof(dp)); dp[0][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= k; j++)
			for(int m = 0; m < i; m++)
				if(a[i] > a[m] && l[a[i]] > r[a[m]]) //如果满足“单调不下降”这一要求
					if(dp[m][j - 1] >= 0)
						dp[i][j] = max(dp[i][j], dp[m][j - 1] + b[a[i]]);
	for(int i = 1; i <= n; i++)
		ans = max(ans, dp[i][k]);
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：zaochen (赞：14)

提供一个不需要背包的做法，类似于最长上升子序列的线性 DP。  

题意可转化为：从 $1$ 到 $n$ 中选出一个长度为 $k$ 的颜色序列，其中颜色都在 $a$ 中出现，且在 $a$ 中删去选出除了序列内的颜色之外所剩下的所有颜色编号单调不下降。容易发现选出的序列一定单调递增。  

使用线性动态规划来解决这个问题。  

状态定义：$dp[i][0/1][j]$ 表示 *所有* 由前 $i$ 种颜色中选出 $j$ 种颜色组成的序列，其颜色价值总和的最大值，第二维表示第 $i$ 种颜色选或不选。无法选出则记 $dp[i][0/1][j] = -1$。  

状态计算：  
对情况进行分类：  
1. 初始状态：$dp[i][1][1] = b[i]$，只选第 $i$ 种颜色，构成的序列在 $a$ 中必然单调不下降，其价值总和即 $b[i]$。  
2. 当不选第 $i$ 种颜色时，从前 $i$ 种颜色中选就是从前 $i-1$ 种颜色中选，则 $dp[i][0][j]=\max(dp[i-1][0][j],dp[i-1][1][j])$。  
3. 当选第 $i$ 种颜色，且序列长度 $j$ 大于 $1$ 时，考虑选出的第 $j-1$ 种颜色 $c$ 需要满足的条件：
	- 条件一：$c$ 在 $a$ 中出现过。
   - 条件二：$dp[c][1][j - 1] \neq -1$，即可以从前 $k$ 种颜色中选出长度为 $j-1$，且选择第 $k$ 种颜色的序列。
   - 条件三：所有第 $c$ 种颜色出现在 $a$ 中的位置在所有第 $i$ 种颜色的前面。  
   所有由前 $i$ 种颜色中选出 $j$ 种颜色且选择 $i$ 组成的序列，都可以表示为在从前 $c$ 种颜色中选出 $j-1$ 种颜色且选择 $c$ 组成的序列最后添加一个 $i$。根据状态定义，可以算出 $dp[i][1][j]=\max(dp[k][i][j-1]+b[i])$，其中 $k$ 要满足上面三个条件。
   
考虑如何判断条件三：在读入 $a$ 时可以求出每种颜色第一次出现和最后一次出现的位置，记作 $L[i]$ 和 $R[i]$，则条件三等价于 $R[c] < L[i]$。 

最终答案为所有第一维在 $a$ 中出现过，第三维为 $k$ 的状态的最大值，代码实现如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 505;
int n, k;
int dp[N][2][N];
int a[N], b[N];
int l[N], r[N];

signed main()
{
    ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    clock_t t0 = clock();
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    // Don't stop. Don't hide. Follow the light, and you'll find tomorrow.

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        r[a[i]] = i;
        if (l[a[i]] == 0)
            l[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    memset(dp, -1, sizeof dp);
    for (int i = 1; i <= n; i++)
        dp[i][1][1] = b[i];
    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            dp[i][0][j] = max(dp[i - 1][0][j], dp[i - 1][1][j]);
            for (int c = 1; c < i; c++)
            {
                if (l[c] && r[c] < l[i] && dp[c][1][j - 1] != -1)
                {
                    dp[i][1][j] = max(dp[i][1][j], dp[c][1][j - 1] + b[i]);
                }
            }
        }
    }
    int ans = -1;
    for (int i = 1; i <= n; i++)
        if (l[i])
        {
            ans = max(ans, dp[i][1][k]);
            ans = max(ans, dp[i][0][k]);
        }
    cout << ans << endl;

#ifndef ONLINE_JUDGE
    cerr << "Time used:" << clock() - t0 << "ms" << endl;
#endif
    return 0;
}
```

观察代码可以发现：计算答案时所有 $dp[i][0][k]$ 表示的序列都被 一个第二维为 $1$ 的状态所表示的序列包含。所以可以只求 $dp[i][1][k]$ 的最大值即可。然后计算 $dp[i][1][j]$ 时并不涉及第二维为 $0$ 的状态，所以第二维为 $0$ 的状态可以直接不计算，第二维可以直接删去，代码实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 505;
int n, k;
int dp[N][N];
int a[N], b[N];
int l[N], r[N];

signed main()
{
    ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    clock_t t0 = clock();
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    // Don't stop. Don't hide. Follow the light, and you'll find tomorrow.

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        r[a[i]] = i;
        if (l[a[i]] == 0)
            l[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    memset(dp, -1, sizeof dp);
    for (int i = 1; i <= n; i++)
        dp[i][1] = b[i];
    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int c = 1; c < i; c++)
            {
                if (l[c] && r[c] < l[i] && dp[c][j - 1] != -1)
                {
                    dp[i][j] = max(dp[i][j], dp[c][j - 1] + b[i]);
                }
            }
        }
    }
    int ans = -1;
    for (int i = 1; i <= n; i++)
        if (l[i])
        {
            ans = max(ans, dp[i][k]);
        }
    cout << ans << endl;

#ifndef ONLINE_JUDGE
    cerr << "Time used:" << clock() - t0 << "ms" << endl;
#endif
    return 0;
}
```

此时，状态被定义为：$dp[i][j]$ 表示 *所有* 从前 $i$ 种颜色中选出的以第 $i$ 种颜色结尾的长度为 $j$ 的颜色序列的价值总和的最大值。

事实上，可以在一开始就思考这种状态定义方式，或许可以简化代码，并优化一倍空间。

代码写完后，个人认为这题很像去年普及组的 T4：[P8816 [CSP-J 2022] 上升点列](https://www.luogu.com.cn/problem/P8816)。

---

## 作者：TridentDeer (赞：12)

首先观察到，最终留下的颜色序列**相同颜色一定连续**，否则不可能满足颜色序列单调不降。

那么有个比较自然的思路，就是处理出每个颜色前面可能接着的颜色，然后直接 dp。

怎么处理呢？首先得满足相同颜色连续这个性质。那么假设一种颜色左右端点为 $x_1,y_1$，另一种为 $x_2,y_2$，如果前一种能接在后一种前面，那么一定有 $y_1<x_2$。接下来只要判断前一个颜色编号是否比后一个颜色编号小就行了。

然后设 $f_{i,j}$ 表示当前选择颜色 $i$，选了 $j$ 个颜色的最大价值。则有 $f_{i,j}=\max(f_{i,j},f_{k,j-1}+b_i)$，$k$ 是符合条件的颜色。至此，本题已全部解决。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=505;
int n,k,a[N],b[N],l[N],r[N],w[N],dp[N][N];//前n，取k 
vector<int>e[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(!l[a[i]])l[a[i]]=i;
		r[a[i]]=i;
	}
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=0;i<=n;i++){
		for(int j=1;j<=k;j++)dp[i][j]=-1e18;
	}
	for(int i=1;i<=n;i++){e[a[i]].push_back(0);
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			if(r[a[j]]<l[a[i]]&&a[i]>a[j])e[a[i]].push_back(a[j]);//,cout<<a[i]<<" "<<a[j]<<endl;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<e[a[i]].size();j++){
			int v=e[a[i]][j];
			for(int p=1;p<=k;p++){
				dp[a[i]][p]=max(dp[a[i]][p],dp[v][p-1]+w[a[i]]);
			}
		}
	}
	int mx=-1;
	for(int i=1;i<=n;i++)mx=max(mx,dp[i][k]);//,cout<<dp[i][k]<<endl;;
	cout<<mx;
	return 0;
}

```


---

## 作者：liangjindong0504 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P9688)

~~普及难度、出现位置、题目标签，都说明了这题是 dp。~~

这一片题解较长，主要是花了较长篇幅说明 dp 转移式。如有需要，可以择重点看。

### 主要思路
首先，简单说明一个结论：相同颜色一定靠在一起（根据题意所得）。

于是，一个初步的想法出现：对于两种颜色，当且仅当编号小的颜色最后出现的位置在编号大的颜色最先出现的位置之前。

为了实现上面这一个想法，可以用两个数组 $l,r$ 来表示。具体地讲，$l_i,r_i$ 分别表示第 $i$ 种颜色最先出现的位置以及最后出现的位置。若颜色 $c_1,c_2$ 可以一前一后（$c_1 < c_2$），则必有 $r_{c_1} < l_{c_2}$。

好了，正片开始。

先考虑几种~~不切实际的~~算法（即普及组 T3 算法）：搜索、dp、二分、贪心、图。后三者不切实际，不考虑。至于搜索，$n \le 500$ 肯定要炸。所以，只剩下了 dp。

~~俗话说得好~~，dp 分三步。

第一步：确定 dp 数组表示什么（不然你都不知道在干什么）

普及组难度的 dp，一般不会太复杂。根据最后求得的答案，不难设 $dp_i$ 为前 $i$ 种颜色的最优解。显然，只设一维很难推，因为不知道当前的颜色是什么，自然无法判断大小（即第 i 种颜色与第 i-1 种颜色编号大小）。

于是，第二维就呼之欲出了。既然不知道颜色是什么，再设一维颜色就行了！因此，可得出 $dp_{i,j}$ 表示表示已选前 $i$ 种颜色，最后一种颜色为 $j$ 的最优解。

空间复杂度为 $O(nk)$，不会超。

第二步：建立转移式

这一步名字十分高大上，其实就是列举所有可能得到 $dp_{i,j}$ 的所有情况。现在，使用了 $i$ 种颜色，最后一种颜色是 $j$，那它之前是什么情况呢？很明显就是使用 $i-1$ 种颜色，最后一种颜色为 $k$ 的情况啊（当然 $k<j$，而且 $r_k > l_j$，都是最前面提到的）！当然，颜色 $j,k$ 都是出现了的。

综上，转移式即为：$dp_{i,j}=\max (dp_{i,j},dp_{i-1,k}+b_j)$。当然，$j,k$ 都要满足前文中的条件。

第三步：初始值

设立初始值，一定是最重要的一关。如果不设，轻则丢部分分，重则直接爆零。

这题的初始值还是十分好设的，一眼就能看出来：$dp_{1,i}=b_i$。对，初始值就是这么好设，只需要设最简单的情况。

时间复杂度 $O(n^2k)$，可以通过本题。
### 代码实现

重要的事情说三遍：

**不开 long long 见祖宗!**

**不开 long long 见祖宗!**

**不开 long long 见祖宗!**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//这里除了题目和思路中的东西，还有表示最终答案的 maxn 和判断该颜色是否出现的数组 co 
int n,k,a[510],b[510],dp[510][510],l[510],r[510],maxn;
bool co[510];
signed main(){
	//初始化 l 数组都是 inf 
	memset(l,127,sizeof(l));
	//输入不讲 
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		l[a[i]]=min(l[a[i]],i),r[a[i]]=max(r[a[i]],i);
		co[a[i]]=1;
	}
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	//初始化 
	for(int i=1;i<=n;i++){
		if(co[i]) dp[1][i]=b[i];
	}
	//dp
	for(int i=2;i<=k;i++){
		for(int j=1;j<=n;j++){
			if(!co[j]) continue;
			for(int k=1;k<j;k++){
				if(!co[k]||r[k]>l[j]||!dp[i-1][k]) continue;//注意，如果前一种情况无解，则不能转移 
				dp[i][j]=max(dp[i][j],dp[i-1][k]+b[j]);//转移 
			}
		}
	}
	//统计答案 
	for(int i=1;i<=n;i++){
		maxn=max(maxn,dp[k][i]);
	}
	//输出 
	if(maxn) printf("%lld",maxn);
	else printf("-1");
	return 0;
	//功德圆满 
} 
```


---

## 作者：Pengzt (赞：6)

[P9688](https://www.luogu.com.cn/problem/P9688)

由于要求单调，肯定满足对于所有选择的颜色 $(x,y)$ 使得其最左边出现的位置 $L$ 和最右边出现的位置 $R$，满足 $[L_x,R_x]\bigcap[L_y,R_y]=\varnothing$。不然的话肯定不会单调。

直接枚举出现过的颜色，无交的按 $L$ 从小到大连边，且要满足颜色编号从小到大连边，容易发现是一个 DAG，直接在 DAG 上 dp 即可。令 $f_{i,j}$ 表示考虑到 $i$ 区间时，选了 $j$ 个的最大价值，转移显然。边数是 $\mathcal{O}(n^2)$ 的，单次转移 $\mathcal{O}(k)$。

时间复杂度：$\mathcal{O}(n^2k)$。实际上远远跑不满。

赛时在连边时没判颜色编号调了很久。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define pb push_back

const int N=510;
const ll inf=1e18;
int n,m,k;
int a[N],b[N],L[N],R[N],deg[N];
ll f[N][N];
vector<int> e[N];
struct node{
	int l,r,id;
	friend bool operator<(node a,node b){
		return a.l<b.l;
	}
};
vector<node> vec;
queue<int> q;

void work(int x,int y){
	if(vec[x].id<vec[y].id&&vec[x].r<vec[y].l)e[x].pb(y),deg[y]++;
}

int main(){
	for(int i=0;i<N;i++)for(int j=1;j<N;j++)f[i][j]=-inf;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(!L[a[i]])L[a[i]]=i;
		R[a[i]]=i;
	}
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)if(L[i])vec.pb((node){L[i],R[i],i});
	sort(vec.begin(),vec.end());
	m=vec.size();
	for(int i=0;i<m;i++)for(int j=i+1;j<m;j++)work(i,j);
	for(int i=0;i<m;i++)if(!deg[i])q.push(i),f[i][1]=b[vec[i].id];
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u]){
			for(int i=1;i<=k;i++)f[v][i]=max(f[v][i],f[u][i-1]+b[vec[v].id]);
			if(!--deg[v])q.push(v);
		}
	}
	ll ans=-inf;
	for(int i=0;i<m;i++)ans=max(ans,f[i][k]);
	cout<<(ans>=k?ans:-1)<<"\n";
	return 0;
}
```

---

## 作者：流光萤影 (赞：6)

## 前言：

**本题解使用语言：C++14 (GCC 9)，开不开 O2 随意**

## 正文：

**思路：动态规划。我们可以将同一个颜色最左边的方格和最右边的方格“连结”，即视为一个整体。用 $first _ i$ 维护颜色 $i$ 最右边的位置，用 $last _ i$ 维护颜色 $i$ 最右边的位置，用 $num _ i$ 维护颜色 $i$ 出现的次数。**

设 $dp _ {i,j}$ 表示恰好保留 $i$ 种颜色，以颜色 $j$ 做最右端可得到的最大价值。

观察题目性质，可以得到**对于所以 $i \in (1,k],j \in [1,n],x \in [1,j)$，若 $last _ x < first _ j$，且满足 $num _ j$ 和 $num _ x$ 和 $dp _ {i-1,x}$ 的值均合法，则有 $dp _ {i,j} = max(dp _ {i,j},dp _ {i-1,x}+b _ j)$。**

那么，核心代码便可以得到了：

```cpp
for(int i(2);i <= k;++i)
{
	for(int j(1);j <= n;++j)
	{
		if(!num[j]) continue;
		for(int x(1);x < j;++x)
		{
			if(last[x] < first[j] && num[x] && dp[i-1][x])
			{
				dp[i][j] = max(dp[i][j],dp[i-1][x]+b[j]);
			}
		}
	}
}
```

最后，取 $dp _ {k,i \in [1,n]}$ 的最大值即可。

若得到的答案为 $0$，则说明无法满足要求。

------------

**AC 代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;int n,k,a[505],b[505],last[505],first[505],num[505];long long dp[505][505],ans;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin >> n >> k;
	for(int i(1);i <= n;++i) cin >> a[i],last[a[i]] = i,++num[a[i]],first[a[i]] = (num[a[i]] == 1?i:first[a[i]]);
	for(int i(1);i <= n;++i) cin >> b[i],dp[1][i] = b[i];
	for(int i(2);i <= k;++i)
	{
		for(int j(1);j <= n;++j)
		{
			if(!num[j]) continue;
			for(int x(1);x < j;++x)
			{
				if(last[x] < first[j] && num[x] && dp[i-1][x])
				{
					dp[i][j] = max(dp[i][j],dp[i-1][x]+b[j]);
				}
			}
		}
	}
	for(int i(1);i <= n;++i) ans = max(ans,dp[k][i]);
	cout << (ans?ans:-1);
}
```

---

## 作者：CultReborn (赞：5)

最朴素易懂的动态规划做法，时间复杂度为 $O(n^2k)$，空间复杂度为 $O(nk)$。

[原题链接](https://www.luogu.com.cn/problem/P9688)

# 题意
在一个长度为 $n$，宽度为 $1$ 的网格图上，保留恰好 $k$ 种颜色，每种颜色有编号和权值。最后会剩下一些网格，在这些网格从左到右颜色的编号是**单调不下降**的情况下，保证权值和最大。

# 思路
为了方便，我们必须转化一下题意。

我们定义一种颜色编号所**“管辖的区间”**，以其**最初出现**的地方为头部，以其**最后出现**的地方为尾部（可以想像成一条线段）。比如：

坐标：1 2 3 4 5 6 7 8

编号：1 1 2 2 1 1 1 2

颜色 $1$ **管辖区间**的坐标是 $1$ 到 $7$，颜色 $2$ 管辖的范围是 $3$ 到 $8$。然而，这是一段不合法的序列，因为其中两个颜色管辖的区间**有重叠、有冲突**，所以不合法。

当所取颜色各自管辖区间**没有重叠**，且**编号单调不下降时**，我们说这是一个合法序列，比如：

坐标：1 2 3 4 5 6 7 8

编号：1 1 1 2 2 3 3 4

# 爆搜 40pts

[评测记录](https://www.luogu.com.cn/record/127181825)：2.96s /   808.00KB /  1.44KB C++14 (GCC 9)

爆搜程序就可以写出来了，解决了 40pts：

```cpp
void dfs(int dep, int lst, int val, int rgt) {
    if (dep == k) {
        ans = max(ans, val);
        return;
    }
    if (val + p[n] - p[lst] < ans) return;
    if (k - dep > n - lst) return;
    if ((double)clock() / CLOCKS_PER_SEC > 0.98) return;
    for (int i = lst + 1; i <= n; ++i) {
        if (!available[i]) continue;
        if (l[i] < rgt) continue;
        bool flag = true;
        for (int j = l[i]; j <= r[i]; ++j) {
            if (visited[j]) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        for (int j = l[i]; j <= r[i]; ++j) {
            visited[j] = true;
        }
        dfs(dep + 1, i, val + b[i], max(rgt, r[i]));
        for (int j = l[i]; j <= r[i]; ++j) {
            visited[j] = false;
        }
    }
}

int main() {
    memset(l, 0x3f, sizeof(l));
    n = read(); k = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        visited[a[i]] = true;
        l[a[i]] = min(l[a[i]], i);
        r[a[i]] = max(r[a[i]], i);
    }
    for (int i = 1; i <= n; ++i) {
        b[i] = read();
    }
    for (int i = 1; i <= n; ++i) {
        p[i] = p[i - 1] + b[i];
    }
    dfs(0, 0, 0, 0);
    write(ans);
    return 0;
}
```

# 动态规划 AC

[评测记录](https://www.luogu.com.cn/record/127180275)：58ms /   2.36MB /  1.23KB C++14 (GCC 9) O2

时间复杂度为 $O(n^2k)$，空间复杂度为 $O(nk)$。

并不带任何优化，入门组的题要优化它干嘛（逃）。

$dp[i][k]$ 表示在坐标为 $i$，目前已经选择颜色数量为 $k$ 时的最大价值和。

我们开三重循环，第一重用来遍历所有区间的右端点，第二重用来遍历该点前的所有合法颜色编号，第三重用来遍历颜色，一旦找到一个合法编号，就用它更新答案。

最终答案就是每个坐标选 $k$ 种颜色的最大值。

详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 502;
int n,k,a[maxn],b[maxn];//如题
long long dp[maxn][maxn];//如上
int l[maxn],r[maxn];//每个颜色的左边界，右边界
inline int read(){
	char c = getchar();
	int x = 0,f = 1;
	while(c < '0' || c > '9'){
		if(c == '-')
			f = -1;
		c = getchar();
	}
	while(c >= '0'&& c<= '9'){
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
inline void write(long long x){
	if(x < 0) putchar('-'),x = - x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int main(){
	n = read(); k = read();
	for(register int i = 1;i <= n;++i){
		a[i] = read();
		if(l[a[i]] == 0){
			l[a[i]] = i;
			r[a[i]] = i;
			continue;
		}
		r[a[i]] = i;//更新左右边界
	}
	memset(dp,-1,sizeof(dp));
	for(register int i = 1;i <= n;++i){
		b[i] = read();
		dp[i][1] = b[i];//初值为 b 数组内容
	}
	for(register int i = 1;i <= n;++i){
		if(i != r[a[i]])//不可以更新
			continue;
		for(register int j = 1;j < i;++j){
			if(a[i] > a[j] && l[a[i]] >= r[a[j]]){
            //是否有冲突（1.单调性；2.是否重合）
				for(register int u = 1;u < k;++u){
					if(dp[a[j]][u] < 0)
						continue;
					dp[a[i]][u + 1] = 
                    max(dp[a[j]][u] + b[a[i]],
                    	dp[a[i]][u + 1]);	
                    //更新答案				
				}
			}
		}
	}
	long long ans = -1;
	for(register int i = 1;i <= n;++i) 
		ans = max(ans,dp[a[i]][k]);  
	write(ans);
	return 0;
}
```

![Page Views Count](https://badges.toozhao.com/badges/01HBRFXP9BD0YXQB23BA3ZDFYW/green.svg)

特别鸣谢：@[cxpluogu](https://www.luogu.com.cn/user/713419)

码字不易，点赞有益。

---

## 作者：二叉苹果树 (赞：5)

由于不能加入未出现在给定颜色序列中的新颜色，我们只需要考虑对原序列进行统计即可。

类似于最长不下降子序列，只不过这题多了关于颜色种类的限制。那么我们定义状态 $f_{i, j}$ 为以第 $i$ 个颜色结尾，已经选定 $j$ 种颜色的最大价值。

对于选定的每种颜色，我们必须全部保留。所以对于 $f_{i, j}$ 的转移时，我们需要判断接的颜色 $a_j$ 不大于当前的颜色 $a_i$ 且任何接的颜色 $a_j$ 不会出现在任何当前颜色 $a_j$ 前。

对于后者，我们只需提前预处理即可。

状态转移方程也很显然。

$$ f_{i, k}=\left\{
\begin{aligned}

&f_{j, k},\  a_i = a_j \\

&f_{j, k - 1} + b_{a_i},\ a_i > a_j
\end{aligned}
\right.$$

时间复杂度 $\mathcal{O} \left(n^2k \right)$，在本题跑得飞快。

```cpp
#include <iostream>
#include <cstdio>
#define maxn 510

int a[maxn], b[maxn];
int p[maxn][maxn];
long long f[maxn][maxn];
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= n; i++)
        std::cin >> b[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (a[i] > a[j] && i < j)
                p[a[i]][a[j]] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i][1] = b[a[i]];
        for (int j = 1; j <= i - 1; j++)
            if (a[i] > a[j] && p[a[i]][a[j]] == 0)
                for (int t = 1; t <= k - 1; t++)
                    if (f[j][t] != 0)
                        f[i][t + 1] = std::max(f[i][t + 1], f[j][t] + b[a[i]]);
            else if (a[i] == a[j])
                for (int t = 1; t <= k; t++)
                    if (f[j][t] != 0)
                        f[i][t] = std::max(f[i][t], f[j][t]);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans = std::max(ans, f[i][k]);
    if (ans != 0)
        std::cout << ans << std::endl;
    else
        std::cout << -1 << std::endl;
    return 0;
}
```


---

## 作者：Dws_t7760 (赞：4)

我们将 $n$ 种颜色第一次出现的位置和最后一次出现的位置记录，并以第一次出现的位置作为第一关键字，以最后一次出现的位置作为第二关键字，进行排序，这样问题就简化成了求 $k$ 个互不相同并编号依次递增的颜色，并且每个颜色第一次出现的位置和最后一次出现的位置之间的区间互不交叉，使每个颜色的价值之和最大。这时问题变成了一道动态规划题，不难写出代码。

注意如果不同颜色的种类数小于 $k$，那么问题肯定无解，输出 `-1`。

AC 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
struct colo{
	int c,b=114514,l=114514; 
}ys[555];
int n,k,a[555],m[555],s,ans,dp[555][555];
bool cmp(const colo &x,const colo &y) {
	if(x.b!=y.b) return x.b<y.b;
	return x.l<y.l;
}
signed main() {
	cin>>n>>k;
	for(int i=1;i<=n;i++) {
		cin>>a[i],ys[a[i]].l=i,ys[a[i]].c=a[i];
		if(ys[a[i]].b==114514) ys[a[i]].b=i,s++;
	}
	for(int i=1;i<=n;i++) cin>>m[i];
	if(s<k) {
		cout<<-1;
		return 0;
	}
	sort(ys+1,ys+n+1,cmp);
	for(int i=1;i<=s;i++) dp[i][1]=m[ys[i].c];
	for(int i=2;i<=s;i++) {
		for(int j=1;j<i;j++) {
			if(ys[j].l<ys[i].b&&ys[j].c<ys[i].c) {
				for(int kk=1;dp[j][kk];kk++) {
					if(dp[j][kk]+m[ys[i].c]>dp[i][kk+1]) dp[i][kk+1]=dp[j][kk]+m[ys[i].c];
				}
			}
		}
	}
	for(int i=k;i<=s;i++) {
		if(dp[i][k]>ans) ans=dp[i][k];
	}
	if(ans) cout<<ans;
	else cout<<-1;
	return 0;
}
```

---

## 作者：Penguin_Chen (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P9688)
## 思路
首先，应该不难看出这是一道 DP 吧，确定是 DP 以后，我们来考虑设计状态。看一眼数据范围，最大 $500$，算法的复杂度可以达到 $n^3$ 级别，但状态不需要，为什么呢？因为我们是不是只需要维护**当前遍历到了第几位**以及**现在选了多少个**就行了，那就只需要二维。我们设 `dp[i][j]` 表示当现已经遍历到第 $i$ 位，已经选择了 $j$ 种颜色的最大值。

接下来考虑如何转移，显然 $i$ 是从颜色编号比自己小的位置转移来的（颜色编号单调不减），那转移的限制是什么？设 $j<i$，那么 $j$ **最后一次**出现的位置一定小于 $i$ **第一次**出现现的位置（还是为了满足单调不减）。代码如下：

```cpp
	if(r[j]<l[i])
   		maxx=max(maxx,dp[j][k-1])//因为之转移了一步，所以是从k-1转移来的（k为当前步骤）
```

最后，通过题目要求（又双是颜色编号单调不减）我们可以得知遍历的顺序是颜色种类（从小到大），然后第二层循环枚举已选择的颜色种数（优先维护状态），最后一层是枚举可能可以转移到 $i$ 来的颜色 $j$。判无解代码里有解释。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e2+1;
int n,k,ans=-1;
int l[maxn],r[maxn];
int dp[maxn][maxn];//dpi,j代表到第i种颜色，已选中了j种颜色的最大值 
signed main()
{
	std::ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1,a;i<=n;++i)
	{
		cin>>a;
		if(!l[a])l[a]=i;
		r[a]=i;
	}
	for(int i=1;i<=n;++i)cin>>dp[i][1];//以第i种颜色为开头 
	for(int i=1;i<=n;++i)
	{
		if(l[i])//有无这种颜色 
		{
			for(int kk=2;kk<=k;++kk)
			{
				int maxx=-1145141919810;//判无解
				for(int j=1;j<i;++j)
				{
					if(l[j])//有无这种颜色 
						if(r[j]<l[i])maxx=max(maxx,dp[j][kk-1]);
				}//不要直接把dp[i][kk]放进来取最大，可能这种颜色就没有，然后就会出现错误
				dp[i][kk]=dp[i][1]+maxx;
			}
			ans=max(ans,dp[i][k]);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：菲斯斯夫斯基 (赞：3)

## P9688 Colo. 题解

很好的一道 dp 题。

**思路**

注意到 $n\le500$，所以首先可以 $O(n^2)$ 暴力求出 $i$ 和 $j$ 两种颜色是否可以同时选。

然后开始 dp，定义 $dp_{i,j}$ 为第 $i$ 种颜色选了 $j$。

**动态转移方程**很好想，枚举当前第 $i$ 种颜色选了 $j$，再枚举一层 $p$，表示上一种颜色选了 $p$。注意要保证 $p<j$，否则可能会有重复的情况。

转换成代码，就是 $dp_{i,j}=\max\{dp_{i,j},dp_{i-1,p}+b_j\}$。

当然，两种颜色能转移当且仅当**这两种颜色都在 $a$ 中出现过**、**这两种颜色能够同时选**以及**上一层的转移是合法的**（即不为零）。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510;
int n,k,ans;
int a[N],b[N],c[N];
int f[N][N],dp[N][N];
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i],c[a[i]]=1;//c数组表示是否在a中出现过
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
			if(a[j]>a[i])
				f[a[i]][a[j]]=f[a[j]][a[i]]=1;//不能同时选
	}
	for(int i=1;i<=n;i++)
		dp[1][i]=b[i];//初始化
	for(int i=2;i<=k;i++)
	{
		for(int j=1;j<=n;j++)
			for(int p=1;p<j;p++)
				if(!f[j][p]&&c[j]&&c[p]&&dp[i-1][p])//能够转移
					dp[i][j]=max(dp[i][j],dp[i-1][p]+b[j]);//从上一层转移来
	}
	for(int i=1;i<=n;i++)
		if(c[i])ans=max(ans,dp[k][i]);//在a中出现过才能选
	ans==0?cout<<-1:cout<<ans;//ans=0时表示没有合法方案
	return 0;
}

```

---

## 作者：Yun_Mengxi (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9688)

## 题意

给定一个序列 $a_i$，留下 $k$ 种颜色，使留下的子序列单调不减，每种颜色有一个价值 $b_i$，求最大价值和。

## 分析

不难一眼顶针，发现是 dp。

设 $i$ 为当前选了多少颜色，$j$ 为选第 $i$ 种颜色时选第 $j$ 个颜色，$p$ 为选第 $i+1$ 种颜色时选第 $p$ 个颜色。根据题意，$p > j$ 肯定成立，假设加入 $p$ 这个颜色之后序列仍单调不减，那么有转移方程 $dp_{i,p}=\max(dp_{i,p}, dp_{i-1,j}+b_p)$。

如何判断加入 $p$ 后序列仍单调递减可以维护两个数组 $first_i$ 和 $last_i$，$first_i$ 表示第 $i$ 种颜色第一次出现的位置，$last_i$ 表示第 $i$ 种颜色最后一次出现的位置，只需要判断 $first_j < last_p \And last_j<first_p$ 就行了。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int kMaxN = 5e2 + 5, kMod = 1e9 + 7;

int n, k;
int a[kMaxN];
int b[kMaxN];
int dp[kMaxN][kMaxN];
int fst[kMaxN], lst[kMaxN];
int ans;

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  fill(lst + 1, lst + n + 1, n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (!fst[a[i]])  // 求第一次出现的和最后一次出现的位置
      fst[a[i]] = i;
    lst[a[i]] = i;
  }
  memset(dp, -1, sizeof(dp));  // 初始化极小值
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    dp[i][1] = b[i];  // 只选 i 这种颜色的最大值肯定是自身
  }
  for (int i = 2; i <= k; i++) {                                         // 选第 i 种颜色
    for (int j = 1; j <= n; j++) {                                       // 从第 j 种颜色转移过来
      for (int p = j + 1; p <= n; p++) {                                 // p 需要大于 j
        if (lst[j] > fst[p] || lst[p] < fst[j] || dp[j][i - 1] == -1) {  // 如果加入 p 后序列不满足单调不减，则直接跳过。
          continue;
        }
        dp[p][i] = max(dp[p][i], dp[j][i - 1] + b[p]);  // 否则更新一下最大值
      }
    }
  }
  ans = -1;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, dp[i][k]);  // 求个最大值
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：haokee (赞：1)

## 思路

首先我们看到数据范围：$n\le 500$，因此我们很容易想到序列型 dp。看完题目，可以知道每次选择必定会向后多选一个，这拓扑序不就出来了吗？如果设 $dp_i$ 为状态，很明显，这样是错误的，我们没法知道当前我们已经选择了多少种颜色。怎么办？很简单，加一维状态呗！因此，我们设 $dp_{(i,j)}$ 表示当前选到了第 $i$ 种颜色，其中保留了 $j$ 种颜色所能获得的最大收益。因此，我们可以推出状态转移方程：

$$dp_{(i,j)}=max(dp_{(i,j)},dp_{(l,j - 1)} + b_i)$$

其中，$i$ 表示当前的颜色，$j$ 表示当前已经选择了的颜色数量，$l$ 表示上一个颜色。注意一个细节，选择了一个颜色就必须在序列里加上所有的同颜色格子，因此我们可以直接使用结构体记录每一种颜色的起始位置与终止位置。

## 代码

```cpp
#include <iostream>

using namespace std;
using ll = long long;

const ll kMaxN = 505;

struct Color {  // 每一种颜色
  ll st = 1e9, ed;  // 每一种颜色的起始位置与终止位置
} c[kMaxN];  // n 种颜色
ll a[kMaxN], b[kMaxN], f[kMaxN], dp[kMaxN][kMaxN], n, k, ans = -1e9;

int main() {
  fill(dp[0], dp[0] + kMaxN * kMaxN, -1e9);  // 由于取最大值，所以我们初始化为极小值
  cin >> n >> k;
  for (ll i = 1; i <= n; i++) {
    cin >> a[i], f[a[i]] = 1;  // f[i] 表示 i 颜色是否出现
    c[a[i]].st = min(c[a[i]].st, i);  // 起始位置取min
    c[a[i]].ed = max(c[a[i]].ed, i);  // 终止位置取max
  }
  for (ll i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (ll i = 1; i <= n; i++) {  // 边界处理
    if (f[i]) {  // 如果当前颜色存在
      dp[i][1] = b[i];  // 当前为第 i 种颜色，选择了 1 种颜色
    }
  }
  for (ll i = 1; i <= n; i++) {  // 枚举当前的颜色
    for (ll j = 2; j <= k; j++) {  // 枚举当前已经选择了 j 个物品
      for (ll l = 1; l < i; l++) {  // 枚举上一种颜色
        if (dp[l][j - 1] != -1e9 && f[i] && f[l] && c[l].ed < c[i].st) {  // 如果状态存在，并且两种颜色也存在，并且当前颜色在后面
          dp[i][j] = max(dp[i][j], dp[l][j - 1] + b[i]);  // 取max进行转移
        }
      }
    }
  }
  for (ll i = 1; i <= n; i++) {  // 枚举最后一种颜色的位置
    ans = max(ans, dp[i][k]);  // 必须全部选完
  }
  cout << (ans == -1e9 ? -1 : ans) << '\n';  // 输出
  return 0;
}
```

---

## 作者：Dream__Sky (赞：1)

小清新 dp 题。 

我们发现如果要取一格，需要把所有该颜色的各个格子都取了。那么为了满足单调不降，所有颜色必须是连续一段出现。那么我们可以预处理出所有颜色出现的第一个位置与最后一个位置，设为 $l_i$ 与 $r_i$。转移时，在比当前颜色 $i$ 小的颜色 $j$ 里去寻找那些可以满足与 $i$ 位置单调不降的颜色，进行转移。即 $l_i < r_j$,即小的颜色的最右端要在大的颜色的左边。

知道了这个，那我们可以设计 dp 数组了。设 $dp(i,k)$ 为 $i$ 颜色结尾，选了 $k$ 种颜色时的答案。

那么转移方程为:
$$dp(i,k)=\max dp(j,k-1)+b_i$$

其中 $j<i$。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,kk,a[1000],b[1001],l[1000],r[1000],v[1000],dp[1001][1001],daan;
signed main()
{
	cin>>n>>kk;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
		if(!l[a[i]]) l[a[i]]=i;
		r[a[i]]=i;
	}//记录起终位置
	for(int i=1;i<=n;i++) cin>>b[i];
	
	for(int i=1;i<=n;i++) v[i]=b[i];
	//dp i,j为颜色i作为末尾,取k个颜色的答案 
	 for(int i=1;i<=n;i++) dp[i][1]=v[i];//只取一个当然就是自己
	
	
	for(int i=2;i<=n;i++)
	{
		if(!l[i]) continue;//如果没有这个颜色，那就不需要转移
		for(int j=1;j<i;j++)
		{
			if(!r[j]) continue;//同上
			if(r[j]<l[i]) //需要满足单调不降
			{
				for(int k=2;k<=kk;k++)
				{
					if(!dp[j][k-1])break;//如果这个点之前没有被转移，那么转移是无意义的，反而还会把之前那个点认为是选了个，实际应为没有转移，所以并没有选
					dp[i][k]=max(dp[i][k],dp[j][k-1]+v[i]);//转移
				}
			}
		}
	}

	for(int i=1;i<=n;i++)
	{
		if(!l[i]) continue;
		daan=max(daan,dp[i][kk]);//记录最大答案
	}
	if(!daan) cout<<-1;
	else cout<<daan;
	return 0;
}

```



---

## 作者：what_could_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/P9688)

就一 dp 题。

先设计状态，开二维，其中第一维表示选到第 $i$ 个方格，第二维表示选了 $j$ 种颜色。

接下来确定转移方程。对于第 $i$ 个方格，先用一个循环枚举前 $i-1$ 个方格，如果该方格的颜色编号大于第 $i$ 个方格的，那么就不能转移。如果该方格的颜色之前就被枚举到了，那么就不用转移了。如果该格子的颜色最后出现位置比第 $i$ 个格子的颜色最早出现的位置来得晚，那么就说明同时选取这两个会导致该序列不满足单调不下降，不能转移。

贴个转移方程：如果 $a_i=a_j$，$dp_{i,l}=\max(dp_{i,l},dp_{j,l})$，否则 $dp_{i,l}=\max(\max(dp_{j,l-1}+b_{a_j}),dp_{i,l})$，很好理解吧，如果颜色相同直接转移，颜色不同就多增加一种颜色数量，从 $l-1$ 处转移。

初始状态是 $dp_{i,1}=b_{a_i}$，答案是 $\max(dp_{i,k})$。

如果答案为 $0$，说明压根就没有办法使选取 $k$ 种颜色后序列为单调不下降的序列，无解，输出 `-1`。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[510];
long long b[510];
long long dp[510][510];
int zz[510],zw[510];
long long ans=0;
int main()
{
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;i++) scanf("%d",&a[i]),zw[a[i]]=i;
	for(register int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(register int i=n;i>=1;i--) zz[a[i]]=i;
	for(register int i=1;i<=n;i++)
	{
		bool t[510]={0};
		dp[i][1]=b[a[i]];
		for(register int j=1;j<=i-1;j++)
		{
			if(a[i]<a[j]) continue;
			if(t[a[j]]) continue;
			t[a[j]]=1;
			if(zw[a[j]]>zz[a[i]]) continue;
			for(register int l=2;l<=k;l++)
			{
				if(a[i]==a[j]) dp[i][l]=max(dp[i][l],dp[j][l]);
				else if(dp[j][l-1]!=0) dp[i][l]=max(dp[i][l],dp[j][l-1]+b[a[i]]);
			}
		}
	}
	for(register int i=1;i<=n;i++) ans=max(ans,dp[i][k]);
	if(ans==0) printf("-1");
	else printf("%lld",ans);
	return 0;
}
```

---

## 作者：LCat90 (赞：1)

首先我们可以预处理出 $i$ 是否能接在 $j$ 的后面。即当最右边的 $j$ 的下标小于最左边的 $i$ 的下标。

存在传递性：当 $j$ 可以接在 $k$ 的后面，$i$ 可以接在 $j$ 的后面时，$i,j,k$ 一定可以同时被选。

于是可以 dp。设 $dp_{i,j}$ 表示前 $i$ 种颜色选了 $j$ 个，要选第 $i$ 个的最大价值，则有转移方程：

$$dp_{i,j}=a_i + \max _ {k<i} ^{k \text{ can go to i}} dp_{k,j-1}$$

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 505;
int n, K, a[N], ans = -1, dp[N][N], b[N];
vector <int> G[N];
bool f[N][N];
signed main() {
	cin >> n >> K;
	for(int i = 1;i <= n; ++i) {
		cin >> a[i];
		G[a[i]].pb(i);
	}
	for(int i = 1;i <= n; ++i) cin >> b[i]; 
	for(int i = 1;i <= n; ++i) sort(G[i].begin(), G[i].end());
	for(int i = 1;i <= n; ++i)
		for(int j = i + 1;j <= n; ++j) {
			if(!G[i].size() or !G[j].size()) continue ;
			int x = G[i][G[i].size() - 1], y = G[j][0];
			if(y > x) f[i][j] = 1;
		}
	for(int i = 1;i <= n; ++i) // 到了第 i 个颜色
		if(G[i].size())
		for(int k = 1;k <= K; ++k) {
			for(int j = 1;j < i; ++j)
				if(f[j][i] and G[j].size())
				dp[i][k] = max(dp[i][k], dp[j][k - 1]);
			if(k != 1 and dp[i][k] == 0) continue ;
			dp[i][k] += b[i]; 
			if(k == K) ans = max(ans, dp[i][k]);
		}
	cout << ans;
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑搜索。

根据 $a_i \le n,1\le n \le 500$ 的范围，用最笨的不难想到建图。若对于两种颜色 $i,j$，有 $i+1 \le j$ 且 $r_i+1 \le l_j$ 则颜色 $i,j$ 一定能同时选择。这里 $r_i$ 表示颜色 $i$ 最后一次出现的位置，$l_i$ 表示颜色 $i$ 第一次出现的位置。

然后枚举路径起点，记搜实现走 $k$ 步经过点权（$b_i$）最大值即可。

注：在某种颜色 $i$ 不存在的时候，我们是不需要对其进行搜索的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=500+10,M=N*N/2,inf=-1e14;
int n,k;
int a[N],b[N];
int ne[M],e[M],h[M],idx;
int l[N],r[N],f[N][N];
int ans=-1;
il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il int dfs(int s,int st){
	if(~f[s][st]) return f[s][st];
	else if(st==k) return f[s][st]=b[s];
	int now_ans=inf;
	for(re int i=h[s];i;i=ne[i]) now_ans=max(now_ans,dfs(e[i],st+1)+b[s]);
	return f[s][st]=now_ans;
}
void solve(){
	cin>>n>>k;
	memset(f,-1,sizeof(f));
	for(re int i=1;i<=n;++i) scanf("%lld",&a[i]);
	for(re int i=1;i<=n;++i) scanf("%lld",&b[i]);
	for(re int i=1;i<=n;++i)
		if(!l[a[i]]) l[a[i]]=r[a[i]]=i;
		else r[a[i]]=i;
	for(re int i=1;i<=n;++i)
		for(re int j=i+1;j<=n;++j)
			if(r[i]<l[j]) add(i,j);
	for(re int i=1;i<=n;++i) if(l[i]) ans=max(ans,dfs(i,1));
	printf("%lld",ans);return ;
}
signed main(){
	solve();return 0;
}
```


---

## 作者：zbk233 (赞：0)

做法：建图与记忆化搜索。

## 算法概括

考虑先从编号不下降的条件把题目简化。

我们注意到对于一种颜色，假如网格之后的颜色有一种是比这个颜色小的，那么就说明这两种颜色不能共存。因为如果这两种颜色共存的话，编号就不会是不下降的了。

那么我们就可以求出选择了一种颜色后，哪些颜色可以选择，哪些则不可以。

我们考虑如果在一种颜色之后可以选择另一种颜色，那么就把这两种颜色连边。

注意这里说的是之后，也就是说一种颜色只能与出现位置在这种颜色之后的颜色连边，这样就保证了每条边都是单向边。

并且，这个图是不会出现环的。

考虑使用反证法，假设这个图会出现环。那么就会有一条从 $u$ 到 $v$ 的路径，且有一条从 $v$ 到 $u$ 的路径。

根据上述定义，如果两个点相连，那么前一个点必然比后一个点小。有一条路径也是同理。因此，得到 $u < v$ 且 $u > v$，显然矛盾，假设不成立，所以这个图不会出现环。

我们证明了构成的图是有向无环图，那么求答案就有很多方法了，我这里用的是记忆化搜索。

注意将记忆化数组初始赋为极小值，这样就避免了搜不到 $k$ 个点的情况。

## 解题代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long

using namespace std;

struct Edge {
	int to, nxt;
}edge[500005];
ll a[505], b[505], head[505], tot, ans;
ll f[505][505];
int n, p;
bool v[505][505], vis[505];

void add_edge (int u, int v) {
	edge[++tot].to = v;
	edge[tot].nxt = head[u];
	head[u] = tot;
}

ll dfs (int pos, int k) {
	if (f[pos][k] != -1145141919810) return f[pos][k];
	for (int i = head[pos]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if (f[v][k - 1] == -1145141919810) {
			f[v][k - 1] = dfs(v, k - 1);
		}
		f[pos][k] = max(f[pos][k], f[v][k - 1] + b[pos]);
	}
	return f[pos][k];
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> p;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (a[i] > a[j]) v[a[i]][a[j]] = v[a[j]][a[i]] = 1;
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (a[i] == a[j]) continue;
			if (!v[a[i]][a[j]]) {
				add_edge(a[i], a[j]);
				v[a[i]][a[j]] = 1;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			f[i][j] = -1145141919810;
		}
		f[a[i]][1] = b[a[i]];
	}
	for (int i = 1; i <= n; i++) {
		f[a[i]][p] = dfs(a[i], p);
		ans = max(ans, f[a[i]][p]);
	}
	if (ans == 0) ans = -1;
	cout << ans;
	return 0;
}
```


---

## 作者：sbno333 (赞：0)

## 前言

这道题比赛的时候寄了，猜猜为什么。

众所周知，本题最坏时间复杂度为 $O(n^2k)$，带入题目，$500^2\times500=1.25\times10^8$，超了，因此我认为算法不够优秀。

后来才发现不知为什么，竟然没超。

于是就有了下面的题解：

## 题解

显然，这道题要用 DP ~~，因为那种一看就不会做的题都普遍要用 DP~~。

因此这道题我们要找状态转移方程。

由于数据量为 $500$，因此八成是两维。

不难推出，其中一维为当前选了 $j$ 个颜色，毕竟不是这样很难构造出刚好选 $k$ 个颜色。

另外一维有两种选择：网格前 $i$ 格，前 $i$ 种颜色。

显然，两种方法都有可能正确，我们可以推方程了。

当然，我们不难发现最后的结果肯定不存在穿插，比如设最后一个颜色 $x$ 的最大坐标为 $r_x$，最小坐标为 $l_x$，最后保留颜色为 $s_i$，则有 $l_{s_i}>r_{s_{i-1}}$。

因此需要先统计 $l,r$。

```cpp
for(long long i=1;i<=n;i++){
	cin>>a[i];
	if(!l[a[i]]){
		l[a[i]]=i;
	}
	r[a[i]]=i;
	vis[a[i]]=1;
}
```

对于第一种情况，

对于 $f_{i,j}$，枚举 $1$ 到 $i-1$，记作 $p$，如果 $a_p<a_i$，而且 $l_{a_i}>r_{a_p}$，则有 $f_{i,j}=\max(f_{i,j},f_{r_{a_p},j-1}+b_{a_i})$。

因此代码如下（代码中 $b_i$ 用 $w_i$ 代替，$vis_i=1$ 表示原先的画中有颜色 $i$）：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[509];
bool vis[509];
long long w[509];
long long f[509][509];
long long l[509];
long long r[509];
int main(){
	vis[0]=1;
	for(long long i=0;i<509;i++){
		for(long long j=1;j<509;j++){
			f[i][j]=-1e9;
		}
	}
	long long n,k;
	cin>>n>>k;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
		if(!l[a[i]]){
			l[a[i]]=i;
		}
		r[a[i]]=i;
		vis[a[i]]=1;
	}
	for(long long i=1;i<=n;i++){
		cin>>w[i];
	}
	for(long long i=1;i<=n;i++){
		for(long long j=1;j<=k;j++){
			for(long long ii=0;a[ii]!=a[i];ii++)
				if(a[ii]<a[i]&&r[a[ii]]<l[a[i]]&&f[r[a[ii]]][j-1]>=0)
					f[i][j]=max(f[i][j],f[r[a[ii]]][j-1]+w[a[i]]);
		}
	}		
	long long ma;
	ma=-1;
	for(long long i=1;i<=n;i++){
	    if(f[i][k])
		    ma=max(ma,f[i][k]);
	}
	cout<<ma;
	return 0;
}
```

码风丑陋，请见谅。

对于第二种情况：

~~由于本题其它题解~~显然能发现，也是对的。

对于 $r_p<l_i,p<i$，则有 $f_{i,j}=\max(f_{i,j},f_{p,j-1}+b_i)$。

部分代码如下：
```cpp
	for(long long i=1;i<=n;i++){
		if(!vis[i])
			continue;
		f[i][1]=w[i];
		for(long long j=1;j<=k;j++){
			for(long long ii=1;ii<i;ii++)
				if(r[ii]<l[i]&&vis[ii]&&f[ii][j-1]>=0)
					f[i][j]=max(f[i][j],f[ii][j-1]+w[i]);
		}
	}		
	long long ma;
	ma=-1;
	for(long long i=1;i<=n;i++){
	    if(vis[i]&&f[i][k]>0)
		    ma=max(ma,f[i][k]);
	}
	cout<<ma;
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

一眼 LIS 变种。

首先颜色编号是严格不降的。我们选颜色的时候，考虑把所有颜色的位置的左端点右端点找出来变成区间。

如果上一个颜色的区间不是严格在我左边而是和我有交，那么颜色编号可以降过，所以我们的颜色要保证区间不交。

我们设 $f_{i,j}$ 表示已经选了 $i$ 个颜色，最后一个是 $j$。

直接枚举合法的上一个颜色，转移时加上颜色的贡献 $b_i$。

方程：

$$
f_{i,j}=\min_{k=1}^{j-1}{f_{i-1,k}}+b_i[R_k<L_j]
$$

其中 $L_i,R_i$ 表示颜色 $i$ 的左端点，右端点。

```cpp
#include<bits/stdc++.h>
#define LL long long
const LL N=505;
using namespace std;
LL n,k,a[N],b[N],l[N],r[N],cnt[N],f[N][N];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		l[i]=1e9;
	}
	for(LL i=1;i<=n;i++)
	{
		cin>>b[i];
		l[a[i]]=min(l[a[i]],i);
		r[a[i]]=max(r[a[i]],i);
		cnt[a[i]]++;
	}
	memset(f,-127,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		if(cnt[i])f[1][i]=b[i];
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<j;k++)
			{
				if(f[i-1][k]==0)continue;
				if(r[k]<l[j]&&j!=k&&cnt[j]&&cnt[k])f[i][j]=max(f[i][j],f[i-1][k]+b[j]);
			}
		}
	}
	LL mx=-1;
	for(int i=1;i<=n;i++)
	{
		mx=max(f[k][i],mx);
	}
	if(mx==-1)
	{
		puts("-1");
	}
	else
	{
		printf("%lld",mx);
	}
}
```

---

## 作者：codwarm (赞：0)

[题目传送门~](https://www.luogu.com.cn/problem/P9688)

## 题目分析
我们发现“从左到右颜色的编号是**单调不下降**的”，可以联想到经典 DP 问题：最长单调不下降子序列。因此这一题可以参考最长不降序列的写法。

注：本人思路并非最好，但个人认为较好理解。

设计状态转移方程：$dp_{n,m}$ 表示前 $n$ 个选择 $k$ 种颜色获得的最大价值。
由最长不降序列的 DP 写法，可以类比得到：
$$dp_{i,k} = \max (dp_{j,k-1}+v)$$

推出转移式子后，只剩下判断每个 $j$ 是否可以转移。

这里除了要判断 $i$ 和 $j$ 单调不降，还需要判断 $j$ 的颜色的最后出现的下标是否大于 $i$ 的颜色的最前出现的下标，若大于，即出现了上升的情况，矛盾。

具体见代码实现。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
#define INF 0x3f3f3f3f
#define re register
#define il inline
#define gc getchar
#define int ll //记得开long long！

const int N = 505;
int n,k,a[N],b[N],dp[N][N],from[N],bk[N],pre[N];

signed main()
{
	
	memset(bk,-1,sizeof bk);
	memset(pre,-1,sizeof pre);
	cin >> n >> k;
	for (int i = 1;i <= n;i++) scanf("%lld",&a[i]);
	for (int j = 1;j <= n;j++) scanf("%lld",&b[j]);
	for (int i = 1;i <= n;i++) dp[i][1] = b[a[i]];
	//预处理出每个颜色最前和最后所在位置
	for (int i = 1;i <= n;i++)
		if (pre[a[i]] == -1) pre[a[i]] = i;
	for (int i =n;i >= 1;i--)
		if (bk[a[i]] == -1) bk[a[i]] = i;
		
	for (int e = 1;e <= k;e++) //枚举保留k个
		for (int i = 1;i <= n;i++) //枚举以第i个结尾
			for (int j = 1;j < i;j++) // 用第j个转移
				if (a[j] < a[i] && bk[a[j]] < pre[a[i]] && dp[j][e-1])
				{
					//状态转移
					dp[i][e] = max(dp[i][e],dp[j][e-1]+b[a[i]]);
				}
		
	int res = 0;
	for (int i = 1;i <= n;i++) res = max(res,dp[i][k]);
	if (!res) puts("-1");
	else cout << res << endl;
	return 0;
}
```



---

## 作者：HEIMOFA (赞：0)

每当我们保留一个颜色时，夹在这个颜色中间的肯定都不能要了，这样很容易把问题变成一个比较熟悉的问题，有 $n$ 个区间，要求取 $k$ 个区间，使得区间权值和最大，且互不相交，单调不减。

也就是维护一个这样的结构体：

```
struct Line{
    int l=inf,r=0;
    int val;//权值与编号
};
```

想到 DP，$f_{i,j}$ 表示前 $i$ 个区间取 $j$ 个区间的权值最大值（满足上述条件）。

然后就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n,k,mx;
const int N=505,inf=-0x8f8f8f8f;
struct Line{
    int l=inf,r=0;
    int val;
}a[N];
ll f[N][N];

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        a[x].l=min(a[x].l,i);
        a[x].r=max(a[x].r,i);
        mx=max(mx,x);
    }
    for(int i=1;i<=n;i++) scanf("%d",&a[i].val);
    memset(f,0x8f,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        f[i][0]=0;
        if(a[i].l==inf) continue;
        for(int j=1;j<=k;j++){
            for(int l=i-1;l>=0;l--){
                if(a[l].r>a[i].l) continue;
                if(f[l][j-1]==-inf) continue;
                f[i][j]=max(f[i][j],f[l][j-1]+a[i].val);
            }
        }
    }
    ll ans=-inf;
    for(int i=1;i<=n;i++){
        if(f[i][k]==-inf) continue;
        ans=max(ans,f[i][k]);
    }
    printf("%lld",(ans==-inf)?-1:ans);
    return 0;
}
```

---

## 作者：MoonCake2011 (赞：0)

我们可以记录一个颜色第一次出现的位置与最后一次。

设为 `first[]` 与 `last[]`。

我们考虑每一种颜色。

颜色 `y` 能成为颜色 `x`的后面的颜色，仅当 `x<y` 并且 `last[x]<first[y]`。

我们考虑没有 `k` 限制的情况。

我们先枚举 `y`，再枚举 `x`。

因为 `x<y` 这个可以直接在 `for` 里面判断。

后面直接再套个 `if` 判断 `last[x]<first[y]`。

状态转移方程是 `dp[i]=max(dp[i],dp[j]+b[i]);`。

我们可以在 $dp$ 数组加一维，表示选了几个颜色。

我们从小到大枚举选了几个颜色。

状态转移方程是 `dp[i][p]=max(dp[i][p],dp[j][p-1]+b[i]);`。

状态转移代码。
```cpp
for(long long i=1;i<=n;i++){
		dp[i][1]=b[i];
		for(long long j=1;j<i;j++)
			for(long long p=2;p<=k;p++)
				if(last[j]<first[i])
					dp[i][p]=max(dp[i][p],dp[j][p-1]+b[i]);
	}
```

最后来比较判断选 $k$ 个中，哪个为结尾的数最大。
但是，这代码是错的。

来看这一组数据。

```cpp
5 1
1 1 1 1 1
1 2 3 4 5
```

以上代码运行结果为 `5`。

因为 `dp[5][1]=5`。

但是 `5` 没有出现。

设 `h[i]` 为颜色 `i` 出没出现。

出现为 `true`，没出现为 `false`。

加上判断就行。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
long long a[510],b[510];
long long last[510],first[510];
long long dp[510][510];
bool h[510];
int main() {
	memset(dp,-0x3f,sizeof dp);
	cin>>n>>k;
	for(long long i=1;i<=n;i++) cin>>a[i],last[a[i]]=i,h[a[i]]=1;
	for(long long i=n;i>=1;i--) first[a[i]]=i;
	for(long long i=1;i<=n;i++) cin>>b[i];
	for(long long i=1;i<=n;i++){
		if(!h[i]) continue;
		dp[i][1]=b[i];
		for(long long j=1;j<i;j++)
			for(long long p=2;p<=k;p++)
				if(last[j]<first[i] && h[j])
					dp[i][p]=max(dp[i][p],dp[j][p-1]+b[i]);
	}
	long long ans=-1;
	for(long long i=1;i<=n;i++){
		ans=max(ans,dp[i][k]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：HEzzz (赞：0)

### [题目跳转键](https://www.luogu.com.cn/problem/P9688)

### 思路引导

不难发现，如果你选择了一个数字 $e$，那么数字 $e$ 最先出现的位置到最后出现的位置之间的任何数字都不能选了。根据这个特性，我们定义 $pre_i$ 表示 $i$ 这个数字最先出现的位置，$suf_i$ 表示 $i$ 这个数字最后出现的位置。

根据以上内容，我们又知道 $pre_i$ 到 $suf_i$ 这个区间内数字 $i$ 对答案产生的贡献为 $b_i$。这很能让我们想到动态规划，而题目抽象变成了以下。

> 给你 $n$ 个区间，每个区间有 $b_i$ 的价值，让你选择其中的 $k$ 个区间，并且必须满足这 $k$ 个区间中，没有重叠的位置。答案就是这 $k$ 个区间的价值之和的最大值。

明显这就是 $01$ 背包的小变形。

### 解析

我们定义状态 $dp[i][j]$ 表示以数字 $i$ 为末尾，前面已经使用 $j$ 个区间的最大价值。初始化除 $dp[0][0]$ 外其余为 $-1$，$dp[0][0]$ 为 $0$，为什么是 $-1$ 呢？其实就是方便以后处理不能选择 $k$ 个区间的情况。

然后我们知道要想前一个区间和当前区间没有重叠，那么前一个区间 $j$ 的 $suf_j$ 要小于当前区间 $i$ 的 $pre_i$，并且 $dp[j][p-1]$ 必须是非 $-1$，即前一个区间不能为空，因为只有在选择的第一个区间的前一个区间才能是空的，这里 $dp[0][0]$ 就起到了关键作用，而 $p$ 就是枚举的已经选择的区间的个数。

最后我们就可以推出状态转移方程

```cpp
dp[i][p]=max(dp[i][p],dp[j][p-1]+b[i]);
```
最后的最后，我们亲爱的答案就是所以 $dp[i][k]$ 的最大值(有点像最长上升子序列
### code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(lxl i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(lxl i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl;
const lxl N=5e2+5; 
lxl n,k,a[N],b[N],cnt[N],pre[N],suf[N],dp[N][N],ans=-1;
int main()
{  
	scanf("%lld%lld",&n,&k);
	_rep(i,1,n) scanf("%lld",a+i);
	_rep(i,1,n) scanf("%lld",b+i); 
	_rep(i,1,n) if(pre[a[i]]==0) pre[a[i]]=i; //求出i最先出现的位置 
	_antirep(i,n,1) if(suf[a[i]]==0) suf[a[i]]=i;//求出i最后出现的位置 
	memset(dp,-1,sizeof dp);//初始化 
	dp[0][0]=0; 
	_rep(i,1,n)//枚举最后选择的区间 
	{  
		_rep(j,0,i-1)//枚举最后选择的前一个区间 
		{
			_rep(p,1,k)//枚举前面已经选择的区间个数 
			{
				if(pre[i]>suf[j]&&dp[j][p-1]!=-1)//并没有重叠的部分，并且非空 
				{
					dp[i][p]=max(dp[i][p],dp[j][p-1]+b[i]);//状态转移 
				}
			} 
		}
	}
	_rep(i,1,n) ans=max(ans,dp[i][k]);//记得求最大值 
	printf("%lld",ans);
    return 0;
}
```


---

## 作者：koobee (赞：0)

先分析一下数据。$n \le 500$ 说明，这道题只支持 $n^3$ 算法，还要有一定优化，因此想到了动态规划。

状态：$dp[i][j]$ 表示前 $i$ 钟颜色，保留 $j$ 个的最大收益。

转移：要事先预处理哪些颜色可以互相选，转移时枚举可以和这种颜色一起选的颜色，顺推。

答案：$\max(dp[i][k])$

初值：由于可以从任意点开始，设置一个万能点，要保证万能点和其他所有的点都能互相选。因此将所有点初始化为负无穷，只留 $dp[0][0]=0$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 505, M = 1e5+5;
int n, k, a[N], b[N], c[N], d[N], head[M], cnt;
long long dp[N][N], ans; //不开long long见祖宗
struct node{
	int to, nxt;
} e[M];
void add(int x, int y){
	e[++cnt] = {y, head[x]}, head[x] = cnt;
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n>>k;
	for(int i = 1; i <= n; i++){
		cin>>a[i];
		c[a[i]] = i;
		if(d[a[i]] == 0) d[a[i]] = i;
	}
	for(int i = 1; i <= n; i++) cin>>b[i];
	c[0] = 1;//这个错我查了半个小时，警钟敲烂
	for(int i = 1; i <= n; i++){
		if(c[i] == 0) continue;
		for(int j = i+1; j <= n; j++){
			if(c[j] == 0) continue;
			if(c[i] < d[j]) add(i, j);//i出现的最后一次要早于j出现的第一次，不然就不符合题目所说的单调性。
		}
	}
	for(int i = 1; i <= n; i++) add(0, i); //预处理
	memset(dp, 0xc0, sizeof(dp));
	dp[0][0] = 0;
	for(int j = 0; j < k; j++){
		for(int i = 0; i <= n; i++){
			if(c[i] == 0) continue;//只枚举出现过的颜色
			for(int y = head[i]; y; y = e[y].nxt){
				int x = e[y].to;
				dp[x][j+1] = max(dp[x][j+1], dp[i][j] + b[x]);//转移
			}
		}
	}
	for(int i = 1; i <= n; i++) ans = max(ans, dp[i][k]);
	if(ans) cout<<ans;
	else cout<<-1;
	return 0;
}
```


---

## 作者：fuwei123 (赞：0)

算法：dp。

先记录一下某种颜色 $i$ 第一次出现的位置 $l_i$ 和最后一次出现的位置 $r_i$。为了方便，我们将 $i$ 这种颜色看作一段区间 $[l_i,r_i]$。

接着我们会发现，对于每一种合法的保留颜色的方案 $x$（从小到大排列），都有 $r_{x_{i-1}}<l_{x_{i}}(1<i\le k)$，也就是每个颜色的**最后一次出现**，都要在下一种颜色的**第一次**出现**之前**。那么我们就可以把所有颜色按照右端点排序，然后开始 dp。

我们用一种类似最长不降子序列的 dp 方式：$dp_{i,j}$ 表示前 $i$ 种颜色，保留 $j$ 种的最大收益。可得转移方程：
$$dp_{i,j}=\max(dp_{p,j-1}+b_i)(1\le p<i\le n,1<j\le k)$$
注意这里需要判断 $p$ **是否合法**：只有在 $r_p\le l_i$，且 $dp_{p,j-1}$ 合法时才能转移。

如何**判断合法**呢？
我们可以把 $dp$ 数组初始化为 $-1$，判断 $dp_{p,j-1}$ 是否等于 $-1$ 即可，顺便还能判断无解的情况。此外还要将 $dp_{i,1}$ 初始化为 $b_i$。

但是还有一点没有考虑。

转移时，必须满足 $i$ 这种颜色实际的编号在 $p$ 实际的编号之后，才能转移，因为我们进行了排序，所以编号是乱的，**不满足**单调性。

## AC 代码

使用了结构体代替了 $l$ 和 $r$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
    int l, r, v, id;//左端点，右端点，收益，编号
}a[505];
int n, k, x[505], dp[505][505], vis[505];
bool cmp(node x, node y){
    return x.r < y.r;
}
signed main(){
    cin >> n >> k;
    for(int i = 1;i <= n;i++)cin >> x[i];//处理时只处理颜色的左右端点，初始位置不重要
    for(int i = 1;i <= n;i++)cin >> a[i].v;
    for(int i = 1;i <= n;i++)a[i].id = i;//初始化颜色编号
    for(int i = 1;i <= n;i++)a[x[i]].r = i;
    for(int i = n;i >= 1;i--)a[x[i]].l = i;找左右端点
    sort(a + 1, a + n + 1, cmp);
    memset(dp, -1, sizeof dp);
    int ed = 0;
    for(int i = 1;i <= n;i++){
        if(a[i].l && a[i].r){
            ed = i;
            break;
        }
    }//由于排序之后所有没出现过的颜色都被排在前面，所以要找到第一个不为0的位置
    for(int i = ed;i <= n;i++){
        dp[i][1] = a[i].v;//初始化
        for(int p = 2;p <= k;p++){
            for(int j = ed;j < i;j++){
                if(a[j].r < a[i].l && a[j].id < a[i].id){
                    if(dp[j][p - 1] == -1)continue;//判断是否合法
                    dp[i][p] = max(dp[j][p - 1] + a[i].v, dp[i][p]);//转移
                }
            }
        }
    }
    int ans = -1;
    for(int i = ed;i <= n;i++){
        ans = max(ans, dp[i][k]);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：lraM41 (赞：0)

官方题解是背包？提供一种非背包的 dp 做法。~~怎么感觉大家都是这么做的？~~



```dp[i][len]``` 表示保留第 ```i``` 种颜色且这是第  ```len``` 个保留的颜色时的最大价值。

#### 思路：
1. 记下每个颜色第一次出现的下标及最后一次出现的下标。
  
1.  dp 部分：
	1. 先初始化，很明显取第一个颜色的最大价值为这个颜色本身的价值。即 ```dp[i][1]=b[i];```
    2. 枚举当前取的颜色和上一个取的颜色，如果上一个取的颜色的最后出现下标大于等于当前取的颜色的第一个出现下标或枚举的上一次取的颜色未画过，则不符合条件，结束当前循环。否则枚举上一次取颜色时共取的颜色类型并且取过枚举的上一次取的颜色，进行转移。即 ```dp[i][len+1]=max(dp[i][len+1],dp[j][len]+b[i]);```

1.枚举保留每种颜色的最大价值。

#### 代码 & 注释：

```
#include<bits/stdc++.h>
using namespace std;
long long dp[505][505],ans;
int n,k,a[505],b[505],fxb[505],lxb[505];
bool flag[505];
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!flag[a[i]]){//未出现过的颜色。
            flag[a[i]]=1;//标记。
            fxb[a[i]]=i;//第一次出现的下标。
        }
        lxb[a[i]]=i;//每次都会替换，最后存的值便是最后一次出现的下标。
    }
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++){
        dp[i][1]=b[i];//初始化。
        for(int j=1;j<i;j++){
            if(fxb[i]<=lxb[j]||!flag[j]) continue;//不符合条件。
            for(int len=1;len<k;len++){//枚举所取颜色种类和。
            	if(dp[j][len])
	                dp[i][len+1]=max(dp[i][len+1],dp[j][len]+b[i]);//转移。
            }
        }
    }
    for(int i=1;i<=n;i++) ans=max(ans,dp[i][k]);//找最大。
    if(!ans) puts("-1");//无解。
    else cout<<ans;
    return 0;
}

---

## 作者：哈哈人生 (赞：0)

## 题外话
其实这题比较难。我的这篇题解是一个比较特殊和玄学的动态规划，和其它动态规划完全不同，非常有趣。

## 思路
类似求最长单调不降子序列的动态规划，用 $dp_i$ 表示以 $a_i$ 结尾的最长单调不降子序列的长度，这里因为每个数字还有权值，所以另外设一个 $w_i$ 表示以 $a_i$ 结尾的权值最大的单调不降子序列的权值。于是，处理数组 $dp$ 和 $w$ 之间的取舍就成了难点（因为长度如果小于 $k$ 权值再大也不会成为答案）。

我在这里的处理有一点赌的成分，具体来说就是设一个参数，当长度足够大时注意权值，否则先更新长度。

由于最后的子序列的长度有可能大于 $k$，那样的话 $w$ 数组的值也不是正确答案，所以我们设一个向量数组存储可能是答案的子序列，最后直接重新算权值，选取最大值，具体的状态转移方程和代码细节请参考代码实现。

## 代码实现
代码比较复杂，码风不好请见谅。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[505],b[505],dp[505];
int wzl[505],wzr[505],w[505],m=-1,cnt=0;
vector<int> v[505];
priority_queue<int> q;
signed main() {
    srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		if(wzl[a[i]]==0)wzl[a[i]]=i,wzr[a[i]]=i,cnt++;
		else wzr[a[i]]=i;
	}
	for(int i=1; i<=n; i++)cin>>b[i],m=max(m,b[i]);
	for(int i=1; i<=n; i++) {
		dp[i]=1;
		v[i].push_back(a[i]);
		w[i]=b[a[i]];
		for(int j=1; j<i; j++) {//状态转移，分类讨论
			if(a[j]<a[i]&&wzl[a[i]]>=wzr[a[j]]&&wzr[a[i]]>=wzr[a[j]]) {
				if(dp[i]+(n-i)-cnt/4>=k&&cnt>10||!(rand()%4)) {
					if(w[i]<w[j]+b[a[i]]) {
						dp[i]=dp[j]+1;
						w[i]=w[j]+b[a[i]];
						v[i].clear();
						for(int k=0; k<v[j].size(); k++)v[i].push_back(v[j][k]);
						v[i].push_back(a[i]);
					}
				} else {
					if(dp[i]<dp[j]+1) {
						dp[i]=dp[j]+1;
						w[i]=w[j]+b[a[i]];
						v[i].clear();
						for(int k=0; k<v[j].size(); k++)v[i].push_back(v[j][k]);
						v[i].push_back(a[i]);
					} else if(dp[i]==dp[j]+1) {
						if(w[i]<w[j]+b[a[i]]) {
							v[i].clear();
							for(int k=0; k<v[j].size(); k++)v[i].push_back(v[j][k]);
							v[i].push_back(a[i]);
						}
					}
				}
			}
		}
	}
	int ans=-1;
	for(int i=1; i<=n; i++) {
		if(dp[i]<k)continue;
		int tmp=0;
		for(int j=0; j<v[i].size(); j++)q.push(b[v[i][j]]);
		for(int i=1; i<=k; i++) {
			tmp+=q.top();
			q.pop();
		}
		ans=max(ans,tmp);
		while(!q.empty())q.pop();
	}
	cout<<ans;
	return 0;
}
```

## 后记
我的这个思路不是正解，但在一定强度的数据下是比较正确的（很难被卡），时间复杂度也是二维的，算是一种“奇技淫巧”。

站长曾经说过，不抄袭题解代码，只借鉴题解思路，但应该给题解点个赞。

---

