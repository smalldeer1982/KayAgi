# [ABC390E] Vitamin Balance

## 题目描述

有 $N$ 种食物，每种食物恰好含有维生素 $1$、$2$、$3$ 中的一种。  
具体来说，吃第 $i$ 种食物时，可以摄取维生素 $V_i$ 的量为 $A_i$，同时摄入卡路里 $C_i$。

高桥君可以选择吃其中的若干种食物（包括 $0$ 种），使得总摄入卡路里不超过 $X$。  
请计算在此条件下，「维生素 $1$、$2$、$3$ 中摄入量最少的那种维生素的摄入量」可能达到的最大值。

## 说明/提示

### 约束条件

- $1 \leq N \leq 5000$
- $1 \leq X \leq 5000$
- $1 \leq V_i \leq 3$
- $1 \leq A_i \leq 2 \times 10^5$
- $1 \leq C_i \leq X$
- 输入均为整数

### 样例解释 1

各食物的摄入效果如下：  
- 吃第 $1$ 种食物：摄入维生素 $1$ 的量为 $8$，卡路里为 $5$  
- 吃第 $2$ 种食物：摄入维生素 $2$ 的量为 $3$，卡路里为 $5$  
- 吃第 $3$ 种食物：摄入维生素 $2$ 的量为 $7$，卡路里为 $10$  
- 吃第 $4$ 种食物：摄入维生素 $3$ 的量为 $2$，卡路里为 $5$  
- 吃第 $5$ 种食物：摄入维生素 $3$ 的量为 $3$，卡路里为 $10$  

若选择吃第 $1$、$2$、$4$、$5$ 种食物，总卡路里为 $5+5+5+10=25$，维生素摄入量分别为 $8$（维生素 $1$）、$3$（维生素 $2$）、$5$（维生素 $3$）。此时最小值是维生素 $2$ 的 $3$。  
无法在总卡路里 $\leq 25$ 的条件下使三种维生素的摄入量均达到 $4$ 或以上，因此输出 $3$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5 25
1 8 5
2 3 5
2 7 10
3 2 5
3 3 10```

### 输出

```
3```

## 样例 #2

### 输入

```
2 5000
1 200000 1
2 200000 1```

### 输出

```
0```

# 题解

## 作者：gavinliu266 (赞：8)

# 思路
我们把三种维生素分类，跑三次 01 背包，然后枚举两个维生素分配的卡路里数，另一个的卡路里数量也就确定了，然后做完了。

时间复杂度 $O(NX+X^2)$。

# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5005;
int n, x;
int v[N], a[N], c[N];
ll dp1[N], dp2[N], dp3[N];
void solve(ll *dp, int op) {
    for(int i = 1; i <= n; ++i) {
        if(v[i] != op) continue;
        for(int j = x; j >= c[i]; --j)
            dp[j] = max(dp[j], dp[j - c[i]] + a[i]);
    }
}
int main() {
    scanf("%d%d", &n, &x);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d%d", &v[i], &a[i], &c[i]);
    solve(dp1, 1);
    solve(dp2, 2);
    solve(dp3, 3);
    ll ans = 0;
    for(int i = 1; i <= x; ++i)
        for(int j = 1; j <= x - i; ++j) {
            int k = x - i - j;
            ans = max(ans, min(min(dp1[i], dp2[j]), dp3[k]));
        }
    printf("%lld\n", ans);
}
```

---

## 作者：YBJ1006 (赞：4)

我们看到**让最小值最大**考虑二分，当然也可以优化成指针，这里就说二分 。二分 $mid$ 。让三种维生素的数量都超过  $mid$ 即可。二分的右边界是三种维生素，最少一种的数量。

我们得首先预处理出花费  $x$ 代价最多有多少维生素。三种分开，也就是三个背包。

下面是赛时代码，比较丑陋

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 10;
//num单位的维生素v
struct node
{
    int num, v, c;
}a[5050];
int n, x;
int dp1[5050][5050];
int dp2[5050][5050];
int dp3[5050][5050];
bool c(int mid)
{
    ll p1 = 1e9;
    for (int j = 0; j <= x; j++)
    {
        if (dp1[n][j] >= mid)
        {
            p1 = j;
            break;
        }
    }
    if (p1 > x)
        return false;
    ll p2 = 1e9;
    for (int j = 0; j <= x; j++)
    {
        if (dp2[n][j] >= mid)
        {
            p2 = j;
            break;
        }
    }
    if (p1+p2 > x)
        return false;
    ll p3 = 1e9;
    for (int j = 0; j <= x; j++)
    {
        if (dp3[n][j] >= mid)
        {
            p3 = j;
            break;
        }
    }
    if (p3+p1+p2 > x)
        return false;
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].v >> a[i].num >> a[i].c;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= x; j++)
        {
            dp2[i][j] = max(dp2[i - 1][j], dp2[i][j]);
            if (a[i].v != 2)
                continue;
            if (a[i].c <= j)
            {
                dp2[i][j] = max(dp2[i][j], dp2[i - 1][j - a[i].c] + a[i].num);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {

        for (int j = 0; j <= x; j++)
        {
            dp1[i][j] = max(dp1[i - 1][j], dp1[i][j]);
            if (a[i].v != 1)
                continue;
            if (a[i].c <= j)
            {
                dp1[i][j] = max(dp1[i][j], dp1[i - 1][j - a[i].c] + a[i].num);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= x; j++)
        {
            dp3[i][j] = max(dp3[i - 1][j], dp3[i][j]);
            if (a[i].v != 3)
                continue;
            if (a[i].c <= j)
            {
                dp3[i][j] = max(dp3[i][j], dp3[i - 1][j - a[i].c] + a[i].num);
            }
        }
    }
    int l = 0, r = 1e9, best = -1;
    while (l <= r)
    {
        int mid = (1ll * l + r) >> 1;
        if (c(mid))
        {
            best = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    cout << best;

    return 0;
}
```

---

## 作者：ARIS2_0 (赞：3)

### 前言

ABC 特有的乱序排题。

我迫切的想问候 ABC390 的出题人。

### 思路

设 $dp_{val,j}$ 为在只吃含有第 $val$ 种维生素的食物情况下，恰好吃 $j$ 卡路里能得到的最大维生素总量（省略阶段变量）。

这是可以用背包 $O(nx)$ 求出的。

然后对 $dp$ 数组做一个前缀 $\max$，则其定义变为：

$dp_{val,j}$ 为在只吃含有第 $val$ 种维生素的食物情况下，吃不超过 $j$ 卡路里能得到的最大维生素总量。

我们考虑二分答案。

对于一个答案 $p$，其是合法的，当且仅当买不少于 $p$ 个 $1$ 维生素的价钱加买不少于 $p$ 个 $2$ 维生素的价钱加买不少于 $p$ 个 $3$ 维生素的价钱不大于 $x$。

对于“买不少于 $p$ 个 $val$ 维生素的价钱”，其等价于一个最小的 $j$ 使得 $dp_{val,j}\ge p$，这个又可以通过二分求出，于是就做完了。

时间复杂度 $O(nx+\log n\log (n\times a_i))$，快到飞起。

### Code

```cpp
#include<algorithm>
#include<bitset>
#include<deque>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector> 
#include<chrono>
#include<random>
#include<tuple>
#include<unordered_map>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,maxn=5010;
int n,x;
int dp[5][3][maxn+1000],pos[5];
struct node{
    int v,a,c;
}a[maxn];
void solve(){
    for(int val:{1,2,3}){
        int tot=0;
        for(int i=1;i<=n;i++){
            if(a[i].v!=val)continue;
            tot++;
            for(int j=0;j<=x;j++){
                dp[val][tot&1][j]=dp[val][(tot&1)^1][j];
                if(j>=a[i].c){
                    dp[val][tot&1][j]=max(dp[val][tot&1][j],dp[val][(tot&1)^1][j-a[i].c]+a[i].a);
                    if(val==1 and j==5){
                        //cout<<dp[val][tot&1][5]<<"fgsgsdh\n";
                    }
                }
                if(val==1){
                    //cout<<dp[val][tot&1][j]<<"\n";
                }
            }
        }
        pos[val]=tot&1;
        if(val==1){
            //cout<<dp[val][tot&1][5]<<"\n\n\n";

        }
        for(int j=1;j<maxn;j++){
            dp[val][tot&1][j]=max(dp[val][tot&1][j],dp[val][tot&1][j-1]);
            if(j==5 and val==1){
                //cout<<dp[val][tot&1][5]<<"\n\n\n";
            }
            //cout<<val<<" "<<(tot&1)<<" "<<j<<"\n";
        }
        
    }
    //cout<<dp[1][pos[1]&1][5]<<"\n";
}
int check(int x){
    int res[5];
    for(int i:{1,2,3}){
        res[i]=lower_bound(dp[i][pos[i]&1],dp[i][pos[i]&1]+maxn,x)-dp[i][pos[i]&1];
    }
    return res[1]+res[2]+res[3];
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>x;
    for(int i=1;i<=n;i++)cin>>a[i].v>>a[i].a>>a[i].c;
    solve();
    //cout<<dp[1][pos[1]&1][5]<<"\n";
    int l=0,r=min({dp[1][pos[1]&1][maxn-1],dp[2][pos[2]&1][maxn-1],dp[3][pos[3]&1][maxn-1]});
    int ans=0;
    //cout<<r<<"\n";
    //cout<<"3 "<<(pos[3]&1)<<" "<<maxn-1<<"\n";
    //cout<<dp[1][pos[1]&1][1]<<"\n";
    while(l<=r){
        int mid=(l+r)>>1;
        //cout<<mid<<" "<<check(mid)<<"\n";
        if(check(mid)<=x){
            ans=mid,l=mid+1;
        }
        else r=mid-1;
    }
    cout<<ans<<"\n";
	return 0;
}
/*
clang++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,-stack_size -Wl,512000000
*/
```

---

## 作者：xiaoyin2011 (赞：2)

## AT_abc390_e [ABC390E] 维生素均衡 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc390_e)

场上功亏一篑呜呜呜。

### 题目大意

有 $N$ 种食物，每种限吃一份，而且总卡路里摄入不得超过 $X$。每份食物除了 $C_i$ 份卡路里外，提供 $A_i$ 单位的 $V_i$ 型维生素。

总共有三种维生素，设一种吃法三种维生素摄入量的最小值为这种吃法的得分。问最大得分。

### 思路

一眼可以看出其中有背包 DP 的成分，但是它每个状态的代价评估不是很简单，它是从三个值当中选取最小值。如果我们以最小值作为评价标准进行选择，那么我们喜提 WA。

于是我们可以先考虑我们能求出什么。同时维护三种维生素并不简单，但是我们只关注一种维生素和所有提供这种维生素的食物时，这就变成了 01 背包板子。我们可以输入时根据 $V_i$ 对食物进行分类，分入三种维生素，然后对于每种维生素进行 DP。

通过 `dp[v][i][j]` 表示 $v$ 型维生素在前 $i$ 种食物存在的情况下摄入不超过 $j$ 卡路里最多获取的单位数，我们可以在 $O(NX)$ 的时间内得知我们投入 $P$ 卡路里在这种维生素中得到的最大汇报为 `dp[v][N][P]`，为了简化，我们下文将 `dp[v][N][P]` 写作 $M_{v,P}$。

假设对于三种维生素，我们投入 $P_1, P_2, P_3$ 份卡路里，并且保证 $P_1 + P_2 + P_3 \le X$，我们想知道此时 $\min(M_{1,P_1}, M_{2,P_2}, M_{3,P_3})$ 的最大值。

很朴素的想法是暴力 $P_1, P_2, P_3 \le X$，但是这样复杂度瞬间爆炸。

注意到，我们需要的是三个回报的最小值，也就是最小的那个回报对应的维生素投入限制了我们的总价值。所以我们可以将 $X$ 份投入都认为是待分配，而 $P_1 = P_2 = P_3 = 0$，然后进行 $X$ 次分配：

- 找到最小的回报 $M_{v,P_v}$，和它对应的维生素种类 $v$ 和投入 $P_v$。
- 尝试将投入 $P_v$ 增加 $1$，消耗一个待分配。
- 重新更新回报，此时 $M_{v,P_v}$ 可能会增加。

此处最小的回报如果有很多个，任选一个。有前面的预处理，这里的复杂度不超过 $O(X)$。

---

为什么这个想法是正确的？

首先，最小的回报限制了我们，所以如果不让这个维生素的投入更大，我们投入其他维生素也不会让最终答案变大。

其次，如果有一些维生素它们的数量都是最小值，我们为什么可以任意选择一个最小值。

假设此时维生素 $2$ 和 $3$ 的回报都是最小值，而 $1$ 不是瓶颈。如果我们把剩下的投入 $2$ 导致 $2$ 的回报增加，我们并不亏，因为我们减少了一个限制因素。反之如果全部投入也不能让 $2$ 提升，那么 $2$ 就已经是一个永远的限制因素，不论 $3$ 怎么提升，$2$ 也会把最终答案卡在这个值。因此任选一个没有问题。

### 实现

```cpp
// 声明变量部分
vector<pair<ll, ll> > T[4];
ll dp[4][5005][5005]; // dp[v][i][j]: 对于 v 型维生素，考虑前 i 个菜，摄入 j 卡路里及以下，最多获取多少单位
ll M[4][5005], P[4];

// 输入并分类部分
for (int i = 1; i <= N; i++)
{
    scanf("%lld%lld%lld", &V, &A, &C);
    T[V].push_back({A, C});
}

// 01背包部分
for (int t = 1; t <= 3; t++)
{
    for (int i = 0; i < T[t].size(); i++)
    {
        for (int j = 0; j <= X; j++)
        {
            if (j < T[t][i].second)
                dp[t][i + 1][j] = dp[t][i][j];
            else
                dp[t][i + 1][j] = max(dp[t][i][j], dp[t][i][j - T[t][i].second] + T[t][i].first);
        }
    }
    for (int j = 0; j <= X; j++)
        M[t][j] = dp[t][T[t].size()][j];
}

// 贪心部分
P[1] = P[2] = P[3] = 0;
for (int i = 1; i <= X; i++)
{
    ll minx = 9e18, minp = 0;
    for (int j = 1; j <= 3; j++)
    {
        if (M[j][P[j]] < minx)
        {
            minx = M[j][P[j]];
            minp = j;
        }
    }
    P[minp]++;
}
```

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, X, V, A, C;
vector<pair<ll, ll> > T[4];
ll dp[4][5005][5005];
ll M[4][5005], P[4];
int main()
{
	scanf("%lld%lld", &N, &X);
	for (int i = 1; i <= N; i++)
	{
		scanf("%lld%lld%lld", &V, &A, &C);
		T[V].push_back({A, C});
	}
	for (int t = 1; t <= 3; t++)
	{
		for (int i = 0; i < T[t].size(); i++)
		{
			for (int j = 0; j <= X; j++)
			{
				if (j < T[t][i].second)
					dp[t][i + 1][j] = dp[t][i][j];
				else
					dp[t][i + 1][j] = max(dp[t][i][j], dp[t][i][j - T[t][i].second] + T[t][i].first);
			}
		}
		for (int j = 0; j <= X; j++)
			M[t][j] = dp[t][T[t].size()][j];
	}
	P[1] = P[2] = P[3] = 0;
	for (int i = 1; i <= X; i++)
	{
		ll minx = 9e18, minp = 0;
		for (int j = 1; j <= 3; j++)
		{
			if (M[j][P[j]] < minx)
			{
				minx = M[j][P[j]];
				minp = j;
			}
		}
		P[minp]++;
	}
	printf("%lld\n", min(min(M[1][P[1]], M[2][P[2]]), M[3][P[3]]));
	return 0;
}
```

---

## 作者：vorDeal (赞：1)

逆风翻盘。

背包问题，每个物品有重量和价值，而价值又分三类。在给定背包容量下，最大化获得的这三类价值中的最小值。

观察到三种价值是独立的，不妨将三种物品分开处理，分别求解占用某容量下所获得最大价值，转化为三次 0-1 背包。最后，再枚举对于三类物品的空间占用划分，取得答案。

时间复杂度 $O(nx+x^2)$，足以通过本题。

[Code.](https://atcoder.jp/contests/abc390/submissions/62079566)

祝各位新年快乐！

---

## 作者：_Trangle_ (赞：1)

先将 $3$ 种维生素分开处理。对于每种维生素，跑一遍背包，求 $dp_v$ 表示有 $v$ 点热量，最多能获得多少维生素。

最后再枚举三种维生素对应热量消耗，找出答案。

时间复杂度为 $O(X(X+N))$。

```cpp
#include <bits/stdc++.h>
#define range(i, b, e) for (auto i(b); i != (e); i++)
#define rep(i, b, e) for (auto i(b); i <= (e); i++)
#define req(i, b, e) for (auto i(b); i >= (e); i--)
using namespace std;
typedef long long LL;

const int N = 5e3, V = 5e3;
int n, v;
LL DP[3][V+5];
LL ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> v;
	for (int i = 1, vit, typ, ka; i <= n; i++) {
		cin >> typ >> vit >> ka;
		typ--; //原编号为 1 2 3，变为 0 1 2。
		req(k, v, ka) DP[typ][k] = max(DP[typ][k], DP[typ][k-ka] + vit); //分开处理。
	}
	rep(i, 1, v) rep(j, 1, v-i) {
		int k = v-i-j; //确定了其中两个的热量，剩下的一个的热量也能确定。
		ans = max(ans, min({DP[0][i], DP[1][j], DP[2][k]}));
	}
	cout << ans;
	return 0;
}
```

---

## 作者：xiaofu15191 (赞：1)

对于 $V_i=1$ 的食物，设 $f_{1,i}$ 表示热量之和最高为 $i$ 时可选择的最多的维生素单位数。这就是 01 背包板子。然后对于 $V_i=2$ 或 $V_i=3$ 同理。

然后由于 $X \le 5000$，所以我们可以枚举 $C_1$ 表示 $V_i=1$ 的食物占到的总热量，$C_2$ 表示 $V_i=2$ 的，$C_3=X-C_1-C_2$ 表示 $V_i=3$ 的。此时直接更新答案即可。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long n,x,v[5010],a[5010],c[5010],f1[5010],f2[5010],f3[5010];
int main()
{
	scanf("%lld%lld",&n,&x);
	for(long long i=1;i<=n;i++) scanf("%lld%lld%lld",&v[i],&a[i],&c[i]);
	for(long long i=1;i<=n;i++)
	{
		if(v[i]!=1) continue;
		for(long long j=x;j>=c[i];j--)
			f1[j]=max(f1[j],f1[j-c[i]]+a[i]);
	}
	for(long long i=1;i<=n;i++)
	{
		if(v[i]!=2) continue;
		for(long long j=x;j>=c[i];j--)
			f2[j]=max(f2[j],f2[j-c[i]]+a[i]);
	}
	for(long long i=1;i<=n;i++)
	{
		if(v[i]!=3) continue;
		for(long long j=x;j>=c[i];j--)
			f3[j]=max(f3[j],f3[j-c[i]]+a[i]);
	}
	long long ans=0;
	for(long long c1=0;c1<=x;c1++)
		for(long long c2=0;c1+c2<=x;c2++)
		{
			long long c3=x-c1-c2;
			ans=max(ans,min(f1[c1],min(f2[c2],f3[c3])));
		}
	printf("%lld\n",ans);
}
```

---

## 作者：c_legg (赞：1)

## 题意

有 $n$ 种水果，每种水果提供 $a_i$ 个单位的维生素 $v_i$ 和 $c_i$ 卡路里，其中 $v_i\in[1,2,3]$，现在最多摄入 $x$ 卡路里，在每种水果最多吃一个的情况下，求三种维生素中摄入最少量的最大值。

## 思路

对每种维生素都进行一次背包 DP，我们用 $\text{dp}_{i,j}$ 表示最多摄入 $i$ 卡路里时，维生素 $j$ 摄入量的最大值。

然后枚举整数 $i\in[0,x],j\in[0,x-i]$，令 $k=x-i-j$，就可以找到 $\max\{\min(dp_{i,1},dp_{j,2},dp_{k,3})\}$，可以发现，这就是我们要求的值。因为 $i+j+k=x$，$i,j,k$ 分别表示我们分配给三种维生素的卡路里。

时间复杂度 $\Theta(xn+x^2)$，空间复杂度 $\Theta(n+x)$

----

[又双叒叕不放代码](https://atcoder.jp/contests/abc390/submissions/62117588)

---

## 作者：Tairitempest (赞：1)

## [ABC390E] Vitamin Balance
最小值的状态记录比较困难，但是考虑到每种食物最多提供一种维生素，所以我们完全可以为三种含维生素食物手动分配卡路里空间。并且可以得知相同卡路里空间内某种维生素含量的最大值是固定的。因此我们将物品按维生素种类分成三类，对三种维生素分别做背包，计算对于含某种维生素的食品，其卡路里不超过某个限制时其维生素的总和。然后，枚举其中两种维生素所给的卡路里空间，就可以得到第三种食物的卡路里空间，这样该分配空间的结果就可以通过前面的背包结果求到。对所有分配的结果取最大值即可。

复杂度 $O(NX+X^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll f[5010][4];
ll n,x,ans;
struct F{
	ll v,a,c;
} p[5010];
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++)
		cin>>p[i].v>>p[i].a>>p[i].c;
	for(int i=1;i<=n;i++){
		for(int j=x;j>=p[i].c;j--){
			ll tp=p[i].v;
			f[j][tp]=max(f[j][tp],f[j-p[i].c][tp]+p[i].a);
		}
	}
	for(int i=0;i<=x;i++)
		for(int j=0;i+j<=x;j++)
			ans=max(ans,min({f[i][1],f[j][2],f[x-i-j][3]}));
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：lfxxx_ (赞：1)

我们对每个维生素求出在卡路里不超过 $j$ 时最大单位个数。

不难发现这是一个背包问题，于是套用背包模板。

然后我们枚举每个维生素占用多少卡路里，对所有最小值求最大即可。

时间复杂度 $O(nm+m^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005;
int dp[4][N];
int tp[N],v[N],w[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>tp[i]>>v[i]>>w[i];
        for(int j=m;j>=w[i];--j)
            dp[tp[i]][j]=max(dp[tp[i]][j],dp[tp[i]][j-w[i]]+v[i]);
    }
    int ans=0;
    for(int i=1;i<=m;++i)
        for(int j=1;i+j<=m;++j)
        {
            int k=m-i-j;
            ans=max(ans,min({dp[1][i],dp[2][j],dp[3][k]}));
        }
    cout<<ans;
}
```

---

## 作者：high_sky (赞：1)

## 思路
一开始想到了答案的单调性，考虑了二分答案，写 `check()` 的时候，发现可以直接利用背包得出。

我们设 $f_{p,j}$ 表示第 $p$ 个维生素若用 $j$ 个卡路里所能得到的最多维生素。

转移是简单的，这是一个普通的选或不选的背包问题。

转移如下：
$$
f_{p,j}=\max\{f_{p,j},f_{p,j-C_i}+A_i\}
$$

最后分别枚举前两个维生素所需要的卡路里，得出最后一个维生素所需要的卡路里。

最后直接利用状态取最小并在答案中取最大即可，但是还是有些细节。

因为题目中的卡路里不能用完，所以我们得总体上取最大值。什么意思呢？就是把状态改为**用前 $j$ 个卡路里**所得到的最多维生素。

题目不难，代码如下：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stdlib.h>
#include <vector>
#define N 5005
#define int long long
using namespace std;
int n,X;
struct node{
	int num,c;
};
vector<node> a[4];
int sum[4],f[4][N];
int check() {
	for (int p = 1;p <= 3;p ++)
		for (int i = 0;i <= X + 1;i ++)
			f[p][i] = 0;
	//use i energy to buy the best.
	for (int p = 1;p <= 3;p ++) {
//		f[p][0] = 0;
		for (int i = 1;i < a[p].size();i ++)	
			for (int j = X;j >= a[p][i].c;j --)
				f[p][j] = max(f[p][j - a[p][i].c] + a[p][i].num,f[p][j]);
		for (int j = 1;j <= X;j ++) f[p][j] = max(f[p][j],f[p][j - 1]);//前j个
	}
	int ans = 0;
	for (int i = 0;i <= X;i ++)
		for (int j = 0;j <= X - i;j ++) {
			
			int k = X - i - j;
//			cout << i << ' ' << j << ' ' << k << ' ' << f[1][i] << ' ' << f[2][j] << ' ' << f[3][k] << endl;
			ans = max(ans,min({f[1][i],f[2][j],f[3][k]})); 
		}
	return ans;
}
signed main(){
	cin >> n >> X;
	a[3].push_back({0,0});
	a[1].push_back({0,0});
	a[2].push_back({0,0});
	for (int i = 1,type;i <= n;i ++) {
		cin >> type;
		int x,y;
		cin >> x >> y;
		a[type].push_back({x,y});
		sum[type] += x;
	}
//	int l = 1,r = n,res = 0;
//	while(l <= r) {
//		int mid = l + r >> 1;
//		if (check(mid)) l = mid + 1,res = mid;
//		else r = mid - 1; 
//	}
	cout << check();
	return 0;
}
```

---

## 作者：Cosine_Func (赞：1)

并不很难的背包问题。把 $C_i$ 视为质量，$A_i$ 视为价值，对每个 $V_i$ 分别跑一次 01 背包，由此得到 $dp_{i,j}$ 表示用 $i$ 的质量可以得到的最大第 $j$ 类价值，接着就可以枚举前两种物品，第三种物品就可以用式子表示出来。即答案为：
$$
\max_{i+j\leq X}\min{dp_{i,1},dp_{j,2},dp_{X-i-j,3}}
$$
设 $N$ 与 $X$ 同阶，时间复杂度显然为 $O(N^2)$。

[参考代码](https://atcoder.jp/contests/abc390/submissions/62081889)

---

## 作者：Swirl (赞：1)

二分 + 背包

---

我们先不考虑哪一种维生素摄入量最少，只二分摄入量的最小值，其他的事情交给 check。

在 check 里，对每一种维生素食品都做一次背包。

接着我们找到最小的产生的卡路里值，使得该种维生素摄取量 $\gt mid$（如果没有显然就不满足条件），求和统计一下。

因为每种食物都只会涉及到一种维生素，所以每种食品只会被考虑一遍，那么最后统计到的和就是使得每种维生素摄取量的最小值 $\gt mid$ 的最小卡路里消耗量，与 $X$ 比较一下即可。

注意：

- 二分的起点是 $l = 0, r = 10^{18}$，不要弄错了。
- 背包是 01 背包，不要打成别的背包了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define FRE(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define ALL(x) x.begin(), x.end()
using namespace std;

int _test_ = 1;

const int N = 5005, X = 5005;

struct node {
	int A[3];
} a[N];
int n, t;
int dp[N];

bool check(int x) {
	int ans = 0;
	for (int op = 1; op <= 3; op++) {
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			if (a[i].A[0] != op) continue;
			for (int j = N - 5; j >= a[i].A[2]; j--) {
				dp[j] = max(dp[j], dp[j - a[i].A[2]] + a[i].A[1]);
			}
		}
		if (dp[N - 5] < x) return false;
		for (int i = 1; i <= N - 5; i++) {
			if (dp[i] < x) continue;
			ans += i;
			break;
		}
	}
	return ans <= t;
}

void init() {}

void clear() {}

void solve() {
	cin >> n >> t;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].A[0] >> a[i].A[1] >> a[i].A[2];
	}
	int l = 0, r = 1e18, ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	cout << ans;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
//	cin >> _test_;
	init();
	while (_test_--) {
		clear();
		solve();
	}
	return 0;
}
```

---

## 作者：Yuexingfei_qwq (赞：1)

很板的 DP 题，可惜赛时没看。
## 思路  
看到数据范围 $1 \le N,X \le 5000$ ，容易想到 $O(NX)$ 的 DP。  

下文中的变量，除了有特殊说明，其他均是题目中给的变量。

设 $f_{i,j}$ 表示吃了前 $i$ 个食物时，维生素 $j$ 的最大摄入量，则对于每个食物，有 $\displaystyle f_{j,v} = max(f_{j,v}, f_{j - c,v} + a)$，其中 $X \ge j \ge c$。  

接着对于每个 $1 \le i \le X, 1 \le j \le 3$，有 $\displaystyle f_{i,j}=max(f_{i,j},f_{i-1,j})$。

最后，用 $d_i$ 表示获得维生素 $i$ 最大值所需吃的食物个数，将 $\displaystyle d_i(1 \le i \le 3)$ 处理出来后，答案就是 $\displaystyle min(f_{d_1,1}, f_{d_2,2}, f_{d_3,3})$。
## AC CODE
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int n, x;
int v, a, c;
int f[5100][5];
int d[5];

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	F(i, 1, 5000, 1) {
		F(j, 1, 3, 1) {
			f[i][j] = -inf;
		}
	}
	cin >> n >> x;
	F(i, 1, n, 1) {
		cin >> v >> a >> c;
		for (int j = x; j >= c; j--) {
			f[j][v] = std::max(f[j][v], f[j - c][v] + a);
		}
	}
	F(i, 1, x, 1) {
		F(j, 1, 3, 1) {
			f[i][j] = std::max(f[i][j], f[i - 1][j]);
		}
	}
	while (x--) {
		if (f[d[1]][1] <= f[d[2]][2] && f[d[1]][1] <= f[d[3]][3]) {
			d[1]++;
		} else {
			if (f[d[2]][2] <= f[d[1]][1] && f[d[2]][2] <= f[d[3]][3]) {
				d[2]++;
			} else {
				d[3]++;
			}
		}
	}
	cout << std::min({f[d[1]][1], f[d[2]][2], f[d[3]][3]}) << el;
	r0;
}
```

[AC 记录](https://atcoder.jp/contests/abc390/submissions/62112885)

---
这题难度居然比D低，没看真是可惜了。  
完结~~不~~散花。

---
P.S.：经 @[SUNCHAOYI](https://www.luogu.com.cn/user/183603) 提醒，已将贴错的代码重新粘贴，对不起咩。

---

## 作者：_wsq_ (赞：0)

三种维生素要取最小值，而维生素所对应的值域很大，因此我们的动态规划中不可能以任何维生素为状态。所以我们只能先二分答案，然后就可以将每种维生素分开处理，对于每种维生素直接进行 01 背包求出对于每个热量能达到的最大维生素，最后直接 `lower_bound` 即可求出达到对应维生素需要的最小热量。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
int n,x,v[5005],a[5005],c[5005],dp[5][5005],l,r=1000000005;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>v[i]>>a[i]>>c[i];
        for(int j=x;j>=c[i];j--){
            dp[v[i]][j]=max(dp[v[i]][j],dp[v[i]][j-c[i]]+a[i]);
        }
    }
    while(l<r){
        int mid=(l+r+1)>>1;
        if(lower_bound(dp[1],dp[1]+x+1,mid)-dp[1]+lower_bound(dp[2],dp[2]+x+1,mid)-dp[2]+lower_bound(dp[3],dp[3]+x+1,mid)-dp[3]>x){
            r=mid-1;
        }
        else{
            l=mid;
        }
    }
    cout<<l;
    return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/AT_abc390_e)

没啥质量的简单题。

你注意到要求最大值最小，先二分答案最大值，然后就确定了三种维他命的下界。

然后很自然考虑 dp，观察数据范围，我们只能把热量设到状态里面，设 $dp_{i,j}$ 表示第 $i$ 种维他命，产生 $j$ 热量的最大维他命数量。

至于这样设的原因，是你希望产生维他命数量尽可能大，然后产生的位置 $j$ 尽量小，满足三种热量 $\le X$ 这个限制。

然后这个 dp 是简单背包。然后没了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =5001;
#define int long long
#define DEBUG cout<<"when can get npy"<<endl;
int dp[5][N],v[N],n,X,a[N],c[N];
void DP(){
	for(int i=1;i<=n;i++){
		for(int j=5000;j>=c[i];j--){
			dp[v[i]][j]=max(dp[v[i]][j],dp[v[i]][j-c[i]]+a[i]);
		}
	}
}
bool check(int pre){
	int preans=0;
	for(int i=1;i<=3;i++){
		bool f=false;
		for(int j=0;j<=5000;j++){
			if(dp[i][j]>=pre){
				preans+=j; f=true; break;
			}
		}
		if(f==false)	return false;
	}
	if(preans<=X)	return  true;
	return false;
}
void Slove(){
	int l=-1,r=1e15;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(check(mid))	l=mid;
		else	r=mid;
	}
	cout<<l<<endl;
}
signed main(){
	cin>>n>>X;
	for(int i=1;i<=n;i++)	cin>>v[i]>>a[i]>>c[i];
	DP(),Slove();
	return 0;
}

```

---

## 作者：ZHR100102 (赞：0)

比较板的背包。

# 思路

一个 dp 数组里同时存三种食物的最大维他命显然不可行，因为一种食物维他命最多不代表其他维他命也同样多，而最终的价值取决于维他命最少的那个，所以这种思路不可行。

因此我们考虑对每一种食物计算给它 $x$ 的体积下最大的维他命数量，这个显然可以背包去做。然后因为要求三个里的最小值最大，所以这个最小值显然有单调性，考虑二分最小值，在二分 check 的内部再套一个二分，找出第一个维他命大于等于这个维他命最小值的体积，然后全部加在一起，判断是否小于等于总体积即可完成 check。

时间复杂度 $O(nx+\log V \log x)$。其中 $V$ 为答案的值域。

# 代码

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
#define eb(x) emplace_back(x)
#define pb(x) push_back(x)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using pi=pair<int,int>;
int n,m;
ll dp[5][5005];
vector<pi>a[5];
void do_dp(int id)
{
    for(auto x:a[id])
    {
        int w=x.fi,v=x.se;
        for(int j=m;j-v>=0;j--)
        {
            dp[id][j]=max(dp[id][j],dp[id][j-v]+w);
        }
    }
}
bool check(ll mn)
{
    int ans1=(lower_bound(dp[1]+1,dp[1]+m+1,mn)-dp[1]);
    int ans2=(lower_bound(dp[2]+1,dp[2]+m+1,mn)-dp[2]);
    int ans3=(lower_bound(dp[3]+1,dp[3]+m+1,mn)-dp[3]);
    if(ans1+ans2+ans3<=m)return 1;
    return 0;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int v,ax,c;
        cin>>v>>ax>>c;
        a[v].push_back({ax,c});
    }
    do_dp(1);
    do_dp(2);
    do_dp(3);
    ll l=0,r=2e9,mid;
    while(l<r)
    {
        mid=(l+r+1)>>1;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    cout<<l;
    return 0;
}
```

---

## 作者：Ybw0731 (赞：0)

没时间打 ABC 了 QWQ。


这一题几乎就是一个背包模板题，对于每一个类型的食物进行 01 背包，最后分摊这些卡路里，取其中最小值的最大值即可。


AC 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define PII pair<int,int>
using namespace std;
const int N=5e3+5;
const ll INF=0x3f3f3f3f3f3f;
const double EPS=1e-6;
ll n,m,a[N],dp[N][3],v[N],c[N],ans;
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>v[i]>>a[i]>>c[i];
	for(int k=1;k<=3;k++){
		for(int i=1;i<=n;i++){
			if(v[i]!=k)continue;
			for(int j=m;j>=c[i];j--)dp[j][k]=max(dp[j][k],dp[j-c[i]][k]+a[i]);
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m-i;j++){
			int k=m-i-j;
			ans=max(ans,min(dp[i][1],min(dp[j][2],dp[k][3])));
		}
	}
	cout<<ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

