# [ABC153E] Crested Ibis vs Monster

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc153/tasks/abc153_e

トキはモンスターと戦っています。

モンスターの体力は $ H $ です。

トキは $ N $ 種類の魔法が使え、$ i $ 番目の魔法を使うと、モンスターの体力を $ A_i $ 減らすことができますが、トキの魔力を $ B_i $ 消耗します。

同じ魔法は何度でも使うことができます。魔法以外の方法でモンスターの体力を減らすことはできません。

モンスターの体力を $ 0 $ 以下にすればトキの勝ちです。

トキがモンスターに勝つまでに消耗する魔力の合計の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 10^4 $
- $ 1\ \leq\ N\ \leq\ 10^3 $
- $ 1\ \leq\ A_i\ \leq\ 10^4 $
- $ 1\ \leq\ B_i\ \leq\ 10^4 $
- 入力中のすべての値は整数である。

### Sample Explanation 1

最初に $ 1 $ 番目の魔法を使い、トキの魔力を $ 3 $ 消耗して、モンスターの体力を $ 8 $ 減らします。モンスターの体力は $ 1 $ になります。 次に $ 3 $ 番目の魔法を使い、トキの魔力を $ 1 $ 消耗して、モンスターの体力を $ 2 $ 減らします。モンスターの体力は $ -1 $ になります。 これにより、トキが消耗した魔力の合計は $ 4 $ になります。

### Sample Explanation 2

$ 1 $ 番目の魔法を $ 100 $ 回使うのが最適です。

## 样例 #1

### 输入

```
9 3
8 3
4 2
2 1```

### 输出

```
4```

## 样例 #2

### 输入

```
100 6
1 1
2 3
3 9
4 27
5 81
6 243```

### 输出

```
100```

## 样例 #3

### 输入

```
9999 10
540 7550
691 9680
700 9790
510 7150
415 5818
551 7712
587 8227
619 8671
588 8228
176 2461```

### 输出

```
139815```

# 题解

## 作者：CQ_Bab (赞：3)

## 思路
这道题其实就是一道完全背包模板，状态为 $dp_i$ 是伤害为 $i$ 时消耗的魔法点数的最小值，但是这道题的 $dp_0=0$ 代表伤害为 $0$ 时需要 $0$ 点法力值。并且最大值枚举到 $20000$，而且最开始时要将 $dp_i$ 赋值成最大值（因为答案要最小值），最后从 $h$ 往上枚举最小值。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int h,n,f[101010],a[10101],b[101001],res=0x3f3f3f3f3f; // 赋值成一个很大的数 
const int Max=2e4+10;
int main(){
	cin>>h>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	memset(f,0x3f,sizeof f); // 最大值 
	f[0]=0; // 代表伤害为0时需要0点法力值
	for(int i=1;i<=n;i++){
		for(int j=a[i];j<=Max;j++) f[j]=min(f[j],f[j-a[i]]+b[i]); // 完全背包模板 
	}
	for(int i=h;i<=Max;i++) res=min(res,f[i]); // 往上取最小值 
	printf("%d\n",res); // 输出 
	return false; // 完结散花 
}
```


---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

考录完全背包，第 $i$ 物品价值为 $A_i$，体积为 $B_i$。这个背包是无限大的，但是装的物品体积和至少为 $H$。发现在最坏情况 ($H=10^4, A_1=10^4-1$) 背包装的体积只用计算到 $19998$，做个普通“必须装满背包”多重背包记录 DP 数组，最终输出 $\max\{DP_H, DP_{H+1}, \dots, DP_{19998}\}$。

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

ll DP[20004];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int H, N; cin >> H >> N;
	memset(DP, 15, sizeof DP);
	DP[0] = 0;
	while(N--) {
		int dam, cos; cin >> dam >> cos;
		iter(i, dam, 20000) DP[i] = min(DP[i], DP[i-dam]+cos);
	}
	ll mi = DP[20000];
	iter(v, H, 20000) mi = min(mi, DP[v]);
	cout << mi << endl;
}


```


---

## 作者：Chinese_zjc_ (赞：1)

考虑 $DP$ .

$DP[i]$ 表示对怪兽造成 $i$ 点伤害最少需要的法力值.

显然这是一个简单的背包问题,有以下状态转移方程:
$$
DP[i]=
\begin{cases}
0 &(i=0)\\
\min_{A_j\geq i}\{DP[i-A_j]+B_j\} &(i>0)
\end{cases}
$$
最后再求出:
$$
\min_{H\leq i<H+\max_{1\leq j\leq n}A_j}DP[i]
$$
注意 $DP[i]$ 的初值.

$Code$:

```cpp
//This code was made by Chinese_zjc_.
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#define int long long
#define INF 0x3fffffffffffffff
using namespace std;
int h,n,a[1001],b[1001],dp[20001],ans=INF;
signed main()
{
	std::ios::sync_with_stdio(false);
	cin>>h>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=h+10000;++i)
	{
		dp[i]=INF;
		for(int j=1;j<=n;++j)
		{
			if(i-a[j]<0)
			{
				continue;
			}
			dp[i]=min(dp[i],dp[i-a[j]]+b[j]);
		}
	}
	for(int i=h;i<=h+10000;++i)
	{
		ans=min(ans,dp[i]);
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：wyb0412 (赞：1)

先给个传送门：[E - Crested Ibis vs Monster](https://atcoder.jp/contests/abc153/tasks/abc153_e)

接下来我们进入正文

我相信只要学习过背包的大佬们，看到这道题应该立刻想到用完全背包。设dp[i]为**打掉怪兽i点血时需要消耗的最小魔法点数**，每行输入的伤害与魔法点数分别为x和y。

然后列状态转移方程，由于N<=2*10^5，所以可以挨个尝试，即：
```cpp
for(j=0;j+x<N;j++)
dp[j+x]=min(dp[j+x],dp[j]+y);
```

总结：本题十分简单，一道十分地道的DP题目，23行代码就结束了，早知道先做E题，~~就1500分了~~。

上代码！！！
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2*10000+5;  //宏定义，偷懒
const int maxn=0x3f3f3f3f;  //继续偷懒
int dp[N];

int main(){
	int h,n,x,y,i,j;
	cin>>h>>n;
   	memset(dp,maxn,sizeof(dp));
    //先将值调大，因为要用min函数 
   
	dp[0]=0;   //DP边界
	
	for(i=0;i<n;i++){
		cin>>x>>y;
		for(j=0;j+x<N;j++)  //状态转移方程
		dp[j+x]=min(dp[j+x],dp[j]+y);
    }
	sort(dp+h,dp+N-1);  //排序
	
	cout<<dp[h];  //打印
	return 0;
}
```
本文到此结束，请各位大佬交流指正！


---

## 作者：AlicX (赞：0)

#### 此题是一道完全背包的练习题，适合刚学完全背包的同学练手

没学过完全背包的同学看这里->[完全背包](https://blog.csdn.net/weixin_46503238/article/details/115096267?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166297005216782412576936%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166297005216782412576936&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-115096267-null-null.142^v47^body_digest,201^v3^add_ask&utm_term=%E5%AE%8C%E5%85%A8%E8%83%8C%E5%8C%85&spm=1018.2226.3001.4187)

### 具体思路：
首先对于每一个 $dp$，都要设立一个状态，对于此题我们可以令  $f_i$ 表示对怪物用造成 $i$ 这么大的伤害最少用的法力值。
那么我可以推出动态转移方程：$f_j=\min(f_j,f_{j-a_i}+b_i)$ 
其中 $a_i$ 表示第 $i$ 种咒语对怪兽造成的伤害，$b_i$ 表示第 $i$ 种咒语所耗用的魔力值。范围：$1 \leq i \leq n,a_i     \leq j \leq  N $

### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=2e4+10;
int n,m;//m 表示怪物的血量  n表示咒语的数量 
int f[N];
int a[N],b[N];
signed main(){
	memset(f,0x3f,sizeof f);//付初始值，因为要求最小值，所以付为正无穷 
	cin>>m>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];//a[i]表示对怪物造成的的伤害  b[i]表示消耗的法力 
	f[0]=0;//边界 
	for(int i=1;i<=n;i++){ 
		for(int j=a[i];j<N;j++){
			f[j]=min(f[j],f[j-a[i]]+b[i]);//对怪物造成a[i]的伤害消耗b[i]的法力值，取min 
		}
	}
	int res=1e9+7;
	for(int i=m;i<N;i++) res=min(res,f[i]);//从m开始，因为怪物血量为m，枚举最小法力值 
	cout<<res<<endl;
	return 0;//bye~ 
}
```

---

## 作者：LCat90 (赞：0)

很简单的完全背包问题，只是要求的不是 $dp[H]$，因为背包容量可以大于 $H$。所以就在 $[H,Maxn]$ 中取最小值即可。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int Maxn = 1e3 + 5, Maxm = 2e4 + 5;
int h, n, a[Maxn], b[Maxn], ans = 0x3f3f3f3f, dp[Maxm];
int main() {
	memset(dp, 0x3f, sizeof dp);
	scanf("%d %d", &h, &n);
	for(int i = 1;i <= n; ++i) scanf("%d %d", &a[i], &b[i]);
	dp[0] = 0;
	for(int i = 1;i <= n; ++i)
		for(int j = a[i];j < Maxm; ++j) dp[j] = min(dp[j], dp[j - a[i]] + b[i]);
	for(int i = h;i < Maxm; ++i) 
		ans = min(dp[i], ans);
	printf("%d", ans);
	return 0; 
}
```


---

## 作者：StarPatrick (赞：0)

这是一道完全背包问题，但定义的时候要善于转变。

（我写的是记忆化搜索）定义 $dfs(i, u)$ 表示正在选第 $i$ 个物品，已经打了 $u$ 点血量。

边界为如果打的血大于 $h$ 就返回 $0$，否则如果当物品选完了就返回极大值。

接下来的操作就非常简单了，只需要根据每个物品，选或不选就可以了。

献上我丑陋的代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int h, n, dp[1005][15005];
struct e
{
	int a, b;
}mon[1005];
int dfs(int i, int u)
{
	if (dp[i][u]!=-1)
	{
		return dp[i][u];
	}
	if (i==n+1)
	{
		if (u<h)
		{
			return dp[i][u]=1000000000;
		}
		return dp[i][u]=0;
	}
	if (u>=h)
	{
		return dp[i][u]=0;
	}
	return dp[i][u]=min(dfs(i+1, u), dfs(i, u+mon[i].a)+mon[i].b);
}
int main()
{
	memset(dp, -1, sizeof(dp));
	cin>>h>>n;
	for (int p=1;p<=n;p++)
	{
		cin>>mon[p].a>>mon[p].b;
	}
	cout<<dfs(1, 0);
	return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：0)

不难看出，这一题是标准的完全背包，对于每一个 $a$ , $b$ 转移方程如下：

$$f_i=\min(f_i,f_{i-a}+b)$$

这个算法的时间复杂度是 $O(\sum_{i=1}^na_i \times n )$ 的，故可以考虑不用加任何优化。

## _Code_

```cpp
#include<iostream>
#include<queue>
using namespace std;
#define ll long long
const int MAXN=2e4+5;
int h,n,a,b;
int ans=1e9;
int f[MAXN];
int main(){
	for(int i=1;i<MAXN;i++)
		f[i]=1e9;
	cin>>h>>n;
	while(n--){
		cin>>a>>b;
		for(int i=a;i<MAXN;i++)
			f[i]=min(f[i],f[i-a]+b);
	}
	for(int i=h;i<MAXN;i++)
		ans=min(ans,f[i]);
	cout<<ans;
}
```


---

