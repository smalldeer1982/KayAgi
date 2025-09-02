# [ABC322E] Product Development

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc322/tasks/abc322_e

AtCoder 社はある商品の開発をしようとしています。この商品には $ K $ 個のパラメーターがあり、現段階ではすべてのパラメーターの値が $ 0 $ です。AtCoder 社の目標は、パラメーターの値を全て $ P $ 以上にすることです。

ここで、$ N $ 個の開発案があります。$ i(1\ \le\ i\ \le\ N) $ 個目の開発案を実行すると、$ 1\ \le\ j\ \le\ K $ を満たす整数 $ j $ 全てに対して $ j $ 個目のパラメーターが $ A_{i,j} $ 上がりますが、この開発案を実行するにはコストが $ C_i $ かかります。

同じ開発案を $ 2 $ 回以上実行することは出来ません。AtCoder 社が目標を達成出来るか判定し、出来る場合は目標を達成するのに必要なコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 100 $
- $ 1\ \le\ K,P\ \le\ 5 $
- $ 0\ \le\ A_{i,j}\ \le\ P(1\ \le\ i\ \le\ N,1\ \le\ j\ \le\ K) $
- $ 1\ \le\ C_i\ \le\ 10^9(1\ \le\ i\ \le\ N) $
- 入力は全て整数
 
### Sample Explanation 1

$ 1 $ 個目と $ 3 $ 個目と $ 4 $ 個目の開発案を実行すると、それぞれのパラメーターが $ 3+2+0=5,0+4+1=5,2+0+4=6 $ で全て $ 5 $ 以上となるため目標を達成できます。この場合コストの総和は $ 5\ +\ 3\ +\ 1\ =\ 9 $ となります。 コストの総和 $ 8 $ 以下で目標を達成することは出来ません。よって答えは $ 9 $ です。

### Sample Explanation 2

どのようにしても目標を達成することは出来ません。よって `-1` を出力します。

## 样例 #1

### 输入

```
4 3 5
5 3 0 2
3 1 2 3
3 2 4 0
1 0 1 4```

### 输出

```
9```

## 样例 #2

### 输入

```
7 3 5
85 1 0 1
37 1 1 0
38 2 0 0
45 0 2 2
67 1 1 0
12 2 2 0
94 2 2 1```

### 输出

```
-1```

# 题解

## 作者：Genius_Star (赞：14)

### 题意：

``AtCoder`` 公司计划开发一种产品，该产品有 $K$ 个参数，目前参数值均为零，公司的目标是将所有参数值至少提高到 $P$。

有 $N$ 个发展计划。执行第 $i$ 个发展计划会使第 $j$ 个参数的值增加 $A_{i,j}$ 个参数 ，即 $1 \le j \le K$，代价是 $C_i$。

一个开发计划不能执行多次。

确定公司能否实现其目标，如果能，求实现目标所需的最小总成本，否则输出 $-1$。

### 思路：

~~考场去写 F 了，没写出来，呜呜呜……~~

仔细看一下数据范围，除了 $c_i$ 外，其他的数据都在 $5$ 以内。

这说明什么呢？对于这 $K$ 个参数，总共的状态就只有 $5^5=3125$，即我们可以状压或者开一个五维的数组（我个人选择后者）。

那么我们的状态就出来了，设 $f_{x_1,x2,x3,x4,x5}$ 表示第 $i$ 个参数的参数值为 $x_i$ 的情况下，最小的代价是什么。

这是很好转移的，类似背包问题，对于每第 $x$ 个项目，从后往前暴力每一种状态，设我们暴力枚举的状态为 $(a1,a2,a3,a4,a5)$，则定义 $x_i=\min(h_i,a_i+A_{x,i})$，就是加上我们当前项目之后的参数值，其中 $h_i$ 表示第 $i$ 个参数的目标值是多少。

得出状态转移方程：

$$f_{x1,x2,x3,x4,x5}=\min(f_{x1,x2,x3,x4,x5},f_{a1,a2,a3,a4,a5}+c_x)$$

最后我们的答案就是 $f_{h_1,h_2,h_3,h_4,h_5}$。

时间复杂度：$O(n \times p^k)$。

**注意，$f$ 初始化为无穷大。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=105,M=15,INF=1e16;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,k,p;
ll c[N],h[M];
ll a[N][M];
ll f[6][6][6][6][6]={0};
void init(){
	for(int a1=0;a1<6;a1++)
	  for(int a2=0;a2<6;a2++)
	    for(int a3=0;a3<6;a3++)
	      for(int a4=0;a4<6;a4++)
	        for(int a5=0;a5<6;a5++)
	          f[a1][a2][a3][a4][a5]=INF;
}
int main(){
	init();
	f[0][0][0][0][0]=0;
	n=read(),k=read(),p=read();
	for(int i=1;i<=k;i++)
	  h[i]=p;
	for(int i=1;i<=n;i++){
		c[i]=read();
		for(int j=1;j<=k;j++)
		  a[i][j]=read();
	    for(ll a1=h[1];a1>=0;a1--){
	        for(ll a2=h[2];a2>=0;a2--){
		        for(ll a3=h[3];a3>=0;a3--){
			        for(ll a4=h[4];a4>=0;a4--){
				        for(ll a5=h[5];a5>=0;a5--){
				        	ll x1=min(h[1],a1+a[i][1]),x2=min(h[2],a2+a[i][2]),x3=min(h[3],a3+a[i][3]),x4=min(h[4],a4+a[i][4]),x5=min(h[5],a5+a[i][5]);
				            f[x1][x2][x3][x4][x5]=min(f[x1][x2][x3][x4][x5],f[a1][a2][a3][a4][a5]+c[i]);
				    	}
					}
				}
			}
		}
	}
	write((f[h[1]][h[2]][h[3]][h[4]][h[5]]==INF?-1:f[h[1]][h[2]][h[3]][h[4]][h[5]]));
	return 0;
}
```


---

## 作者：ケロシ (赞：5)

看题意，是一个01背包问题。  
但是发现限制非常的多，用一个多维数组看上去不是很好写，   
那么可以通过进制的方式将多维的数组存储到一个一位数组里面，   
其余的就是普通的01背包。  
```cpp
const int V = 2e4 + 5;
const int N = 1e2 + 5;
int n, k, p;
ll f[V], g[V];
int c[N], a[N][N];
int b[N], d[N];
int gp() { // 将多维转换到一维
	int res = 0;
	FOR(i, 1, k) {
		res = res * 6 + b[i];
	}
	return res;
}
void calc(int x) { // 01背包转移
	FOR(i, 1, k) b[i] = d[i];
	int p1 = gp();
	FOR(i, 1, k) b[i] = min(p, b[i] + a[x][i]);
	int p2 = gp();
	chmin(g[p2], f[p1] + c[x]);	
}
void dfs(int u, int x) { // dfs枚举所有的状态
	if(u == k + 1) {
		calc(x);
		return;
	}
	FOR(i, 0, p) {
		d[u] = i;
		dfs(u + 1, x);
	}
}
void solve() {
	cin >> n >> k >> p;
	FOR(i, 1, n) {
		cin >> c[i];
		FOR(j, 1, k) {
			cin >> a[i][j];
		}
	}
	memset(f, 0x3f, sizeof(f));
	f[gp()] = 0;
	FOR(i, 1, n) { // 滚动数组
		memcpy(g, f, sizeof(f));
		dfs(1, i);
		memcpy(f, g, sizeof(f));
	}
	ll ans = LINF;
	FOR(i, 1, k) b[i] = p;
	chmin(ans, f[gp()]);
	cout << (ans == LINF ? -1 : ans) << endl;
}
```


---

## 作者：Tang_poetry_syndrome (赞：3)

## [ABC322E] Product Development 
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc322_e) [Atcoder 题面](https://atcoder.jp/contests/abc322/tasks/abc322_e)  

省流：最暴力的一集（捂脸）。
### 题目大意
AtCoder 公司计划开发一款产品。该产品有 $K$ 个参数，其值当前均为 $0$。公司的目标是将所有参数值提升至至少 $P$。  
有 $N$ 个开发计划。执行第 $i$ 个开发计划 $(1 \leq i \leq N)$ 会使得每个整数 $j(1 \leq j \leq K)$ 对应的第 $j$ 个参数的值增加 $A_{i,j}$，代价为 $C_i$ 。  
每个开发计划只能执行一次。确定公司是否能够达到目标，如果可以，找出实现目标所需的最小总成本。
### 思路
看到题目很容易想到动态规划，但多个值似乎让这题难了很多，仔细一看数据范围 $1 \leq K,P \leq 5$，发现是道水题。  
采用大分讨+动态规划的方法。  
1. $k=1$  

就是普通的背包问题嘛qwq。  

2. $k\ge2$  

这里我们先拿 $k=2$ 举栗子。  
设 $dp_{i,j}$ 为属性达到 $i,j$ 的最小花费，$k$ 为实行第 $k$ 个计划。则 $dp_{i,j}=dp_{i-a_{k,1},j-a_{k,2}}+c_i$，答案即为 $dp_{p,p}$。  
然鹅这里看似正确的式子其实是错误的，再举个栗子：
```
3 2 2
1 2 0
1145 0 0
3 1 2
```  
结果为`-1`，可以看出，是第一个属性超出了 $p$，导致实际上 $dp_{2,2}$ 为极大值。于是我们采用一个“属性可以少拿，但是不能多拿的思路”，即 $dp_{i,j}=dp_{i-I,j-J}+c_i (0 \le I \le a_{k,1},0 \le J \le a_{k,2})$。  
在 $k\ge3$ 时，思路也一样，下标由 $2$ 层逐步增加到 $5$ 层。循环也会达到惊人的 $10$ 层（汗）。  
因为太蒻想不到其它写法了，具体看代码吧。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define ll long long
const int N=1e2+10,INF=INT_MAX,Mod=998244353;
struct data
{
	int k[6];
}a[N];
ll n,k,p,c[N];
int main()
{
   ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
   cin>>n>>k>>p;
   f(i,1,n)
    {
      cin>>c[i];
    	f(j,1,k)cin>>a[i].k[j];
    }
	if(k==1)
	{
		ll dp[10];
		memset(dp,0x3f,sizeof(dp));
		dp[0]=0;
		f(i,1,n)
			g(j,p,a[i].k[1])
				dp[j]=min(dp[j],dp[j-a[i].k[1]]+c[i]);
		if(dp[p]!=4557430888798830399)cout<<dp[p];
		else cout<<-1;
	}
	else if(k==2)
	{
		ll dp[10][10];
		memset(dp,0x3f,sizeof(dp));
		dp[0][0]=0;
		f(i,1,n)
			g(j,p,a[i].k[1])
				f(qwq1,0,a[i].k[1])
					g(k,p,a[i].k[2])
						f(qwq2,0,a[i].k[2])
							dp[j][k]=min(dp[j][k],dp[j-qwq1][k-qwq2]+c[i]);
		if(dp[p][p]!=4557430888798830399)cout<<dp[p][p];
		else cout<<-1;
	}
	else if(k==3)
	{
		ll dp[10][10][10];
		memset(dp,0x3f,sizeof(dp));
		dp[0][0][0]=0;
		f(i,1,n)
			g(j,p,a[i].k[1])
				f(qwq1,0,a[i].k[1])
					g(k,p,a[i].k[2])
						f(qwq2,0,a[i].k[2])
							g(l,p,a[i].k[3])
								f(qwq3,0,a[i].k[3])
									dp[j][k][l]=min(dp[j][k][l],dp[j-qwq1][k-qwq2][l-qwq3]+c[i]);
		if(dp[p][p][p]!=4557430888798830399)cout<<dp[p][p][p];
		else cout<<-1;	
	}
	else if(k==4)
	{
		ll dp[10][10][10][10];
		memset(dp,0x3f,sizeof(dp));
		dp[0][0][0][0]=0;
		f(i,1,n)
			g(j,p,a[i].k[1])
				f(qwq1,0,a[i].k[1])
					g(k,p,a[i].k[2])
						f(qwq2,0,a[i].k[2])
							g(l,p,a[i].k[3])
								f(qwq3,0,a[i].k[3])
									g(Q,p,a[i].k[4])
										f(qwq4,0,a[i].k[4])
											dp[j][k][l][Q]=min(dp[j][k][l][Q],dp[j-qwq1][k-qwq2][l-qwq3][Q-qwq4]+c[i]);
		if(dp[p][p][p][p]!=4557430888798830399)cout<<dp[p][p][p][p];
		else cout<<-1;
	}
	else
	{
		ll dp[10][10][10][10][10];
		memset(dp,0x3f,sizeof(dp));
		dp[0][0][0][0][0]=0;
		f(i,1,n)
			g(j,p,a[i].k[1])
				f(qwq1,0,a[i].k[1])
					g(k,p,a[i].k[2])
						f(qwq2,0,a[i].k[2])
							g(l,p,a[i].k[3])
								f(qwq3,0,a[i].k[3])
									g(Q,p,a[i].k[4])
										f(qwq4,0,a[i].k[4])
											g(P,p,a[i].k[5])
												f(qwq5,0,a[i].k[5])
													dp[j][k][l][Q][P]=min(dp[j][k][l][Q][P],dp[j-qwq1][k-qwq2][l-qwq3][Q-qwq4][P-qwq5]+c[i]);
		if(dp[p][p][p][p][p]!=4557430888798830399)cout<<dp[p][p][p][p][p];
		else cout<<-1;
	} 
	return 0;
}
```
[提交记录](https://atcoder.jp/contests/abc322/submissions/46119888)

---

## 作者：Mingrui_Yang (赞：2)

## 题意

公司开发了一个产品，该产品具有 $K$ 个参数，初始参数均为 $0$，该公司的目标就是将该产品的所有参数至少提高到 $P$。    
共有 $N$ 个计划，执行第 $i$ 个计划需花费 $C_{i}$ 的代价将该产品的所有参数提高 $A_{i,j}$。一个计划只能执行一次。   
求该公司实现其目标至少需要花费多少代价，如果无法达到则输出 `-1`。

## 思路

本题有点像 01 背包。

观察数据，除 $c_i$ 外，都在 $5$ 以内。   
所以开一个五维数组 $f$ 对应参数的状态，再开一个一维数组 $h$ 控制参数的个数。

状态转移与 01 背包相似。  
考虑到参数状态可能超过该参数的限制 $h_i$，为了方便答案输出，将超过 $h_i$ 的状态计为 $h_i$。  
所以定义枚举的状态为 $a_1,a_2,a_3,a_4,a_5$，再定义 $x_i =\min(h_i, a_i+A_{x, i})$，$x$ 为当前的计划编号。  
得到状态转移方程：
$$
f_{x_1,x_2,x_3,x_4,x_5} = \min(f_{x_1,x_2,x_3,x_4,x_5}, f_{a_1,a_2,a_3,a_4,a_5} + c_x)
$$

$f$ 应初始化为无穷大，$f_{0,0,0,0,0} = 0$。  
答案为 $f_{h_1, h_2, h_3, h_4, h_5}$。  
如果 $f_{h_1, h_2, h_3, h_4, h_5}$ 为无穷大，则说明无解，输出 `-1`。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 110;
int n, k, p;
int h[6];
int c[N], a[N][6];
int f[6][6][6][6][6];
signed main() {
	memset(f, 0x3f, sizeof f); // 初始化为0x3f3f3f3f3f3f3f3f 
	f[0][0][0][0][0] = 0; // 递推起点 
	cin >> n >> k >> p;
	for (int i = 1; i <= k; i ++ ) h[i] = p; // 控制维度 
	for (int i = 1; i <= n; i ++ ) {
		cin >> c[i];
		for (int j = 1; j <= k; j ++ )
			cin >> a[i][j];
		for (int a1 = h[1]; a1 >= 0; a1 -- ) // 倒着更新 
		for (int a2 = h[2]; a2 >= 0; a2 -- )
		for (int a3 = h[3]; a3 >= 0; a3 -- )
		for (int a4 = h[4]; a4 >= 0; a4 -- )
		for (int a5 = h[5]; a5 >= 0; a5 -- ) {
			int x1 = min(h[1], a1 + a[i][1]); // 便于统计，超过限制的记作h[i] 
			int x2 = min(h[2], a2 + a[i][2]);
			int x3 = min(h[3], a3 + a[i][3]);
			int x4 = min(h[4], a4 + a[i][4]);
			int x5 = min(h[5], a5 + a[i][5]);
			f[x1][x2][x3][x4][x5] = min(f[x1][x2][x3][x4][x5], f[a1][a2][a3][a4][a5] + c[i]); 
		}
	} 
	cout << (f[h[1]][h[2]][h[3]][h[4]][h[5]] == 0x3f3f3f3f3f3f3f3f ? -1 : f[h[1]][h[2]][h[3]][h[4]][h[5]]) << endl;
	return 0;
}
```

---

## 作者：BYR_KKK (赞：2)

# E.Product Development 

[Here](https://atcoder.jp/contests/abc322/tasks/abc322_e)

## 题目大意

有 $N$ 个方案，第 $i$ 个方案可以对第 $j$ 个参数增长 $A_{i,j}$ ，但每选择一个方案都会花费 $c_i$ 的代价。求在一共 $K$ 个参数的情况下，使每个参数都达到 $P$ 的最小代价。

## 思路

明显，每种方案只有选或不选两种情况，所以我们考虑**背包**。

定义 $dp[i][j]$ 表示已经考虑好了前 $i$ 个方案，达到状态 $j$ 的最小代价。

至于状态 $j$ 如何表示，可以采用 ```map``` 等方式，也可以选择状压。这里我们选择状压。

当然，状压也可以采用不同的进制。由于每个参数都有至少五种状态，所以我们必须选择五进制或更高的进制。为了方便，我们选择最方便的十进制。状态 $j$ 十进制下的第 $k$ 位表示此时第 $k$ 个参数的值。

我们对于每一种方案枚举每一种状态，定义 $new$ 为新的状态，于是就有了转移方程：

$$dp_{i,new}=\min (dp_{i,new},dp_{i-1,j}+c_i)$$

至于如何求出状态 $new$ ，我们可以通过 $O(k)$ 的复杂度来求出每一位（每一个参数）的新值，并将其替换。

由于数据范围的特殊性，新状态的某个参数可能达到 $10$ ，这样就会有错误的表示。我们想到如果有一个参数超过 $P$ ，那其实和等于 $P$ 没有什么区别，所以我们更改状态时可以将参数的新状态与 $P$ 取最小值后放入新状态。

同时，我们遍历状态时会有很多之前没有出现过的冗余状态（这是由于我们是拿旧状态来更新新状态，如果用新状态来更新旧状态，就不会有这个问题），我们可以记录一下这些冗余状态是否在前面出现过，以减少运行次数。

由于存在 $P$ 的限制，我们最多就有 $55555$ 种状态，设有 $X$ 种状态，所以最坏的时间复杂度是 $O(X  NK)$ 。

## code

```cpp

#include<bits/stdc++.h>
#define int long long

const int maxn=110;

int dp[maxn][66666];

int a[maxn][10];

int shi[7];

bool vis[maxn][55560];

signed main(){
	shi[0]=1,shi[1]=10,shi[2]=100,shi[3]=1000,shi[4]=10000,shi[5]=100000;//预处理 
	int n,k,p;
	std::cin>>n>>k>>p;
	for(int i=1;i<=n;i++) {
		std::cin>>a[i][0];//a[i][0] 表示第 i 中方案的代价 
		for(int j=1;j<=k;j++) std::cin>>a[i][j];
	}
	std::memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	vis[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=55555;j++){
			if(!vis[i-1][j]) continue;
			int dpz=j;
			for(int l=1;l<=k;l++){
				int ddpz=(dpz%shi[l])/shi[l-1];
				int las=ddpz;
				ddpz=std::min(ddpz+a[i][l],p);
				dpz=dpz-las*shi[l-1]+ddpz*shi[l-1];;
			} 
			vis[i][dpz]=vis[i][j]=1;
			dp[i][dpz]=std::min(dp[i][dpz],dp[i-1][j]+a[i][0]);
			dp[i][j]=std::min(dp[i][j],dp[i-1][j]);
		}
	}
	int dpz=0;
	for(int i=1;i<=k;i++) dpz+=p*shi[i-1];
	if(!vis[n][dpz]) {
		std::cout<<-1;
		return 0;
	}
	std::cout<<dp[n][dpz];
	return 0;
}

```

```end```

---

## 作者：linxuanrui (赞：1)

### 思路

本题的突破口就在于 $K$ 和 $P$ 的范围特别小。

我用的是六维 DP。

设 `dp[i][j][k][l][m][n]` 为前 $i$ 个开发计划使参数分别至少达到 $j,k,l,m,n$ 的最小代价。

那么可以分两种情况：选 $a_i$ 和不选 $a_i$。

因此可以得出状态转移方程：

$$
dp_{i,j,k,l,m,n}=\min\begin{cases}
\min\limits_{t_1=1}^{\min{0,j-a_{i,1}}}\min\limits_{t_2=1}^{\min{0,k-a_{i,2}}}\min\limits_{t_3=1}^{\min{0,l-a_{i,3}}}\min\limits_{t_4=1}^{\min{0,m-a_{i,4}}}\min\limits_{t_5=1}^{\min{0,n-a_{i,5}}}dp_{i-1,t_1,t_2,t_3,t_4,t_5}\\
dp_{i-1,j,k,l,m,n}
\end{cases}
$$

这样，你就得到了一个六维 DP，十一重循环，运行超过 100ms 的程序了。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
typedef long long ll;
using namespace std;
int N,M,P,c[105],a[105][10],dp[105][10][10][10][10][10];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> P;
	for(int i = 1;i <= N;i++){
		cin >> c[i];
		for(int j = 1;j <= M;j++)cin >> a[i][j];
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0][0][0][0][0] = 0;
	for(int i = 1;i <= N;i++){
		for(int j = 0;j <= (M >= 1 ? P : 0ll);j++){
			for(int k = 0;k <= (M >= 2 ? P : 0ll);k++){
				for(int l = 0;l <= (M >= 3 ? P : 0ll);l++){
					for(int m = 0;m <= (M >= 4 ? P : 0ll);m++){
						for(int n = 0;n <= (M >= 5 ? P : 0ll);n++){
							dp[i][j][k][l][m][n] = min(dp[i][j][k][l][m][n],dp[i - 1][j][k][l][m][n]);
							for(int o = max(0ll,j - a[i][1]);o <= j;o++){
								for(int p = max(0ll,k - a[i][2]);p <= k;p++){
									for(int q = max(0ll,l - a[i][3]);q <= l;q++){
										for(int r = max(0ll,m - a[i][4]);r <= m;r++){
											for(int s = max(0ll,n - a[i][5]);s <= n;s++){
												dp[i][j][k][l][m][n] = min(dp[i][j][k][l][m][n],dp[i - 1][o][p][q][r][s] + c[i]);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	int t = dp[N][(M >= 1 ? P : 0)][(M >= 2 ? P : 0)][(M >= 3 ? P : 0)][(M >= 4 ? P : 0)][(M >= 5 ? P : 0)];
	cout << (t == 0x3f3f3f3f3f3f3f3f ? -1 : t);
}
```

---

## 作者：rainygame (赞：1)

比较水的一道 DP，但是我居然用了半个小时，看来还是我太菜了。

首先，这道题状态显然，可以令 $f_{i,k_1,k_2,\dots,k_K}$ 为前 $i$ 个开发方案且当前进度为 $\min\{k_1,P\},\min\{k_2,P\},\dots,\min\{k_K,P\}$ 的最小费用。（因为大于 $P$ 的状态和 $P$ 的状态是等价的，所以一律看成 $P$）

状态转移方程也非常显然：

$$
f_{i,k_1,k_2,\dots,k_K}=\min\limits_{g_1=0}^P\min\limits_{g_2=0}^P\dots\min\limits_{g_K=0}^Pf_{i-1,\min\{g_1+A_{i,1},P\},f_{i-1,\min\{g_2+A_{i,2},P\}},\dots,f_{i-1,\min\{g_K+A_{i,K},P\}}}+C_i
$$

边界条件有 $f_{0,0,0\dots,0}=0$。

可是现在有一个问题：如何实现？

对于状态转移方程 $k_1\sim k_K$ 的枚举，我们可以直接 DFS 枚举 $g_1\sim g_K$，然后就可以直接求出 $k_1\sim k_K$ 以转移。

但是数组是定长的，所以有两条路：状压或 STL。在这里我使用 STL。

考虑使用一个 `map<vector<int>, int> f[MAXN]` 来作为前面的 $f$ 数组，其中 `MAXN` 就是 $i$ 那一维，然后 `vector<int>` 就是 $k_1,k_2,\dots,k_K$ 那一维。

最后的答案就是 $f_{n,P,P,\dots,P}$，注意处理转移不到的情况。

时间复杂度 $O(nK^P)$。优于十进制状压。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 101

int n, k, p, c, i;
vector<int> a, b, g;
map<vector<int>, int> f[MAXN];

void dfs(int x){
	if (x == k){
		if (!f[i-1].count(b)) return;
		vector<int> vec(k);
		for (int j(0); j<k; ++j) vec[j] = min(a[j]+b[j], p);
		if (f[i].count(vec)) f[i][vec] = min(f[i][vec], f[i-1][b]+c);
		else f[i][vec] = f[i-1][b] + c;
		return;
	}
	
	for (int i(0); i<=p; ++i){
		b[x] = i;
		dfs(x+1);
	}
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> k >> p;
    for (i=1; i<=k; ++i){
    	a.push_back(0);
    	b.push_back(0);
    	g.push_back(p);
	}
	f[0][b] = 0;
    for (i=1; i<=n; ++i){
    	cin >> c;
    	for (int j(0); j<k; ++j) cin >> a[j];
    	f[i] = f[i-1];
    	dfs(0);
	}
	if (f[n].count(g)) cout << f[n][g];
	else cout << -1;

    return 0;
}

```


---

## 作者：WilliamFranklin (赞：1)

一道很水但又很暴力的动态规划。

### 主要思路

我们设 $f_{i, j, k, l, r, s}$ 表示使用前 $i$ 种计划，第 $1$ 个参数值为 $j$，第 $2$ 个参数值为 $k$，第 $3$ 个参数值为 $l$，第 $4$ 个参数值为 $r$，第 $5$ 个参数值为 $s$ 的最小代价。

但是考虑到参数值是小于等于 $5$ 个的，所以说，我们再设定每一个参数值的上界 $h$ 即可：前 $K$ 个的参数值上界全为 $P$，其余的都为 $0$。

然后我们发现，如果一个参数值的值超过了上界，我们其实是可以按照当前参数值为上界算的，因为他无论怎么样，后面这个参数值的值都一定大于上界。

在此，我认为用前面的推后面的更方便，所以转移方程如下：

我们用 $x$ 代替一下 $f_{i, \min(h_1, j + A_{i - 1, 1}), \min(h_2, k + A_{i - 1, 2}), \min(h_3, l + A_{i - 1, 3}), \min(h_4, r + A_{i - 1, 4}), \min(h_5, s + A_{i - 1, 5})}$ 。

$$
x = \min(x, f_{i - 1, j, k, l, r, s} + C_{i - 1})
$$

然后我们发现，这个第一维可以滚掉。

代码如下：

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 105, K = 6;
long long f[K][K][K][K][K];
int tot[K];
int n, k, p;
long long c[N];
int a[N][K];
void get(long long &x, long long y) {
	x = min(x, y);
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> k >> p;
	For(i, 1, k) tot[i] = p;
	For(i, 1, n) {
		cin >> c[i];
		For(j, 1, k) cin >> a[i][j];
	}
	For(j, 0, K - 1) For(k, 0, K - 1) For(l, 0, K - 1) For(r, 0, K - 1) For(s, 0, K - 1) f[j][k][l][r][s] = 1e18;
	f[0][0][0][0][0] = 0;
	For(i, 1, n) {
		Dec(j, tot[1], 0) {
			Dec(k, tot[2], 0) {
				Dec(l, tot[3], 0) {
					Dec(r, tot[4], 0) {
						Dec(s, tot[5], 0) {
							get(f[min(j + a[i][1], tot[1])][min(k + a[i][2], tot[2])][min(l + a[i][3], tot[3])][min(r + a[i][4], tot[4])][min(s + a[i][5], tot[5])], f[j][k][l][r][s] + c[i]);
						}
					}
				}
			}
		}
	}
	if (f[tot[1]][tot[2]][tot[3]][tot[4]][tot[5]] == 1e18) {
		cout << -1;
		return 0;
	}
	cout << f[tot[1]][tot[2]][tot[3]][tot[4]][tot[5]];
	return 0;
} 
```

### 谢谢观看

---

## 作者：Halberd_Cease (赞：1)

我觉得比 D 简单。

### 大意：

一个物品有 $K$ 个属性且初始均为 $0$，有 $N$ 种方案可以提升属性的值，花费 $C_i(1\le i\le N)$ 元可以将产品第 $j(1\le j\le K)$ 个属性的值提升 $A_{i,j}$，每种方案最多使用一次。求将物品所有属性全部提升到 $P$ 及以上的最小花费

### 思路：

数据范围有：

-   $1 \le N \le 100$
-   $1 \le K,P \le 5$

可以想到在 $K,P$ 上做文章。

因为 $P$ 和 $K$ 的值非常小，我们考虑设状态 $dp_{i1,i2,i3,i4,i5}$，表示将产品的属性分别提升到 $i1,i2,i3,i4,i5$ 所需要的花费。特殊的，对于 $i$ 值等于 $5$ 的情况，代表该属性大于等于 $5$；

考虑转移，枚举 $n$ 个物品，再枚举所有 $i1,i2,i3,i4,i5$ 可能的状态，然后得到了这个鬼式子：

```dp[min(p, i1 + a[i][1])][min(p, i2 + a[i][2])][min(p, i3 + a[i][3])][min(p, i4 + a[i][4])][min(p, i5 + a[i][5])] = min(dp[min(p, i1 + a[i][1])][min(p, i2 + a[i][2])][min(p, i3 + a[i][3])][min(p, i4 + a[i][4])][min(p, i5 + a[i][5])], dp[i1][i2][i3][i4][i5] + x);```

意思是在 $dp_{i1,i2,i3,i4,i5}$ 的地方转移到如果买了这个方案的属性去，然后选优。这样子转移所有的方案都可以被枚举到，因此不会丢失答案。

有一个小技巧，就是 $K$ 不足 $5$ 时，可以强行把 $K$ 补成 $5$，方案中补的属性的提升值设成 $P$，其实就是只要选了一个方案就可以满足补上的那几个属性的要求。

然后就没有了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[10][10][10][10][10];
int a[110][10];
int n, k, p;
signed main()
{
    for (int i1 = 0; i1 <= 5; i1++)
        for (int i2 = 0; i2 <= 5; i2++)
            for (int i3 = 0; i3 <= 5; i3++)
                for (int i4 = 0; i4 <= 5; i4++)
                    for (int i5 = 0; i5 <= 5; i5++)
                        dp[i1][i2][i3][i4][i5] = 1145141919810;
    dp[0][0][0][0][0] = 0;
    cin >> n >> k >> p;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        for (int j = 1; j <= k; j++)
        {
            cin >> a[i][j];
        }
        for (int j = k + 1; j <= 5; j++)
        {
            a[i][j] = p;
        }
        for (int i1 = p; i1 >=0 ; i1--)
            for (int i2 = p; i2 >=0 ; i2--)
                for (int i3 = p; i3 >=0 ; i3--)
                    for (int i4 = p; i4 >=0 ; i4--)
                        for (int i5 = p; i5 >=0 ; i5--)
                        {
                            dp[min(p, i1 + a[i][1])][min(p, i2 + a[i][2])][min(p, i3 + a[i][3])][min(p, i4 + a[i][4])][min(p, i5 + a[i][5])] = min(dp[min(p, i1 + a[i][1])][min(p, i2 + a[i][2])][min(p, i3 + a[i][3])][min(p, i4 + a[i][4])][min(p, i5 + a[i][5])], dp[i1][i2][i3][i4][i5] + x);
                        }
    }
    if (dp[p][p][p][p][p] == 1145141919810)
        cout << -1;
    else
        cout << dp[p][p][p][p][p];
}
```

---

## 作者：incra (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc322_e)
### 前言
纪念一下第一次通过前 $6$ 题。
### 题意
略。
### 题解
注意到 $k\le5$，所以考虑 $k$ 维 DP。

为了方便，这里仅举 $k=5$ 的例子。

由于题目要求加起来的结果不小于 $p$，所以我们用当前决策来更新其他决策的方法，而不是用其他决策来更新当前决策（这个代码中有很好的体现）。

设 $f_{i,a,b,c,d,e}$ 为在前 $i$ 个物品中选，$5$ 个和分别是 $a,b,c,d,e$，且第 $i$ 个物品的 $k$ 个指标分别是 $p_{i,1},p_{i,2},p_{i,3},p_{i,4},p_{i,5}$，不难得到 $f_{i+1,\min(a+p_{i,1},p),\min(b+p_{i,2},p),\min(c+p_{i,3},p),\min(d+p_{i,4},p),\min(e+p_{i,5},p)}$ 可以用当前决策更新（此处即为取 $\min$）。

同时我们可以用类似 01 背包的方式把第一维去掉，注意循环顺序。

其他的请读者自己完成推导（说实话也不难）。
### 代码
```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
const int N = 110;
int n,k,p;
int c[N];
int a[N][N];
int main () {
	cin >> n >> k >> p;
	if (k == 1) {
		vector <LL> f (6,1e18);
		f[0] = 0;
		for (int i = 1;i <= n;i++) {
			int c,x1;
			cin >> c >> x1;
			for (int j = p;j >= 0;j--) f[min (j + x1,p)] = min (f[min (j + x1,p)],f[j] + c);
		}
		if (f[p] == 1e18) f[p] = -1;
		cout << f[p] << endl;
	}
	else if (k == 2) {
		vector <vector <LL> > f (6,vector <LL> (6,1e18));
		f[0][0] = 0;
		for (int i = 1;i <= n;i++) {
			int c,x1,x2;
			cin >> c >> x1 >> x2;
			for (int j1 = p;j1 >= 0;j1--) {
				for (int j2 = p;j2 >= 0;j2--) f[min (j1 + x1,p)][min (j2 + x2,p)] = min (f[min (j1 + x1,p)][min (j2 + x2,p)],f[j1][j2] + c);
			}
		}
		if (f[p][p] == 1e18) f[p][p] = -1;
		cout << f[p][p] << endl;
	}
	else if (k == 3) {
		vector <vector <vector <LL> > > f (6,vector <vector <LL> > (6,vector <LL> (6,1e18)));
		f[0][0][0] = 0;
		for (int i = 1;i <= n;i++) {
			int c,x1,x2,x3;
			cin >> c >> x1 >> x2 >> x3;
			for (int j1 = p;j1 >= 0;j1--) {
				for (int j2 = p;j2 >= 0;j2--) {
					for (int j3 = p;j3 >= 0;j3--) f[min (j1 + x1,p)][min (j2 + x2,p)][min (j3 + x3,p)] = min (f[min (j1 + x1,p)][min (j2 + x2,p)][min (j3 + x3,p)],f[j1][j2][j3] + c);
				}
			}
		}
		if (f[p][p][p] == 1e18) f[p][p][p] = -1;
		cout << f[p][p][p] << endl;
	}
	else if (k == 4) {
		vector <vector <vector <vector <LL> > > > f (6,vector <vector <vector <LL> > > (6,vector <vector <LL> > (6,vector <LL> (6,1e18))));
		f[0][0][0][0] = 0;
		for (int i = 1;i <= n;i++) {
			int c,x1,x2,x3,x4;
			cin >> c >> x1 >> x2 >> x3 >> x4;
			for (int j1 = p;j1 >= 0;j1--) {
				for (int j2 = p;j2 >= 0;j2--) {
					for (int j3 = p;j3 >= 0;j3--) {
						for (int j4 = p;j4 >= 0;j4--) f[min (j1 + x1,p)][min (j2 + x2,p)][min (j3 + x3,p)][min (j4 + x4,p)] = min (f[min (j1 + x1,p)][min (j2 + x2,p)][min (j3 + x3,p)][min (j4 + x4,p)],f[j1][j2][j3][j4] + c);
					}
				}
			}
		}
		if (f[p][p][p][p] == 1e18) f[p][p][p][p] = -1;
		cout << f[p][p][p][p] << endl;
	}
	else if (k == 5) {
		vector <vector <vector <vector <vector <LL> > > > > f (6,vector <vector <vector <vector <LL> > > > (6,vector <vector <vector <LL> > > (6,vector <vector <LL> > (6,vector <LL> (6,1e18)))));
		f[0][0][0][0][0] = 0;
		for (int i = 1;i <= n;i++) {
			int c,x1,x2,x3,x4,x5;
			cin >> c >> x1 >> x2 >> x3 >> x4 >> x5;
			for (int j1 = p;j1 >= 0;j1--) {
				for (int j2 = p;j2 >= 0;j2--) {
					for (int j3 = p;j3 >= 0;j3--) {
						for (int j4 = p;j4 >= 0;j4--) {
							for (int j5 = p;j5 >= 0;j5--) f[min (j1 + x1,p)][min (j2 + x2,p)][min (j3 + x3,p)][min (j4 + x4,p)][min (j5 + x5,p)] = min (f[min (j1 + x1,p)][min (j2 + x2,p)][min (j3 + x3,p)][min (j4 + x4,p)][min (j5 + x5,p)],f[j1][j2][j3][j4][j5] + c);
						}
					}
				}
			}
		}
		if (f[p][p][p][p][p] == 1e18) f[p][p][p][p][p] = -1;
		cout << f[p][p][p][p][p] << endl;
	}
	else exit (-1);
	return 0;
}
```

---

## 作者：Mr_Biantainne (赞：1)

## 题外话
**本题解较长，请做好心理准备。**

~~这题真的好难啊！看我提交了多少遍。~~

![](https://cdn.luogu.com.cn/upload/image_hosting/jsu0yf47.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/onzyhecv.png)
## 题意简述
现在要开发一个产品，产品有 $k$ 个指标。有 $n$ 个开发计划，每个开发计划执行需要支付 $c_i$ 的开发费用，选第 $i$ 个计划，产品的第 $j$ 个指标就会增加 $A_{i,j}$。求使得所有 $k$ 个指标的值都 $\ge p$ 的最小花费。
## 思路
### 第一次尝试
参考[这个帖子](https://www.luogu.com.cn/discuss/697279)，用了一个暴力搜索去做，但是没有理解[这位大佬](https://www.luogu.com.cn/user/743048)的提示，写挂了，TLE 了。

~~普通爆搜，不爆时间就奇怪了。~~
### 第一份代码
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;
ll n, k, p, c[105], a[105][6], v[105], rec[6], tot, ans = 1e18;
void dfs(ll now)
{
    if (tot > ans || now > n + 1) return; //剪枝
    if (rec[1] >= p && (k < 2 || rec[2] >= p) && (k < 3 || rec[3] >= p) && (k < 4 || rec[4] >= p) && (k < 5 || rec[5] >= p)) //满足要求
    {
        ans = tot;
        return;
    }
    for (ll i = 1; i <= k; i++) rec[i] += a[now][i];
    tot += c[now]; 
    dfs(now + 1); //选的情况
    tot -= c[now];
    for (ll i = 1; i <= k; i++) rec[i] -= a[now][i];
    dfs(now + 1); //不选的情况
}
int main()
{
    cin >> n >> k >> p;
    for (ll i = 1; i <= n; i++)
    {
        cin >> c[i];
        for (ll j = 1; j <= k; j++) cin >> a[i][j];
    }
    dfs(1);
    if (ans != 1e18) cout << ans; //有解的情况
    else cout << -1; //无解的情况
}
```
### 第二次尝试
后来又去参考[这个帖子](https://www.luogu.com.cn/discuss/697285)，用 dp 来做，根据[这位](https://www.luogu.com.cn/user/378126)的提示，把[楼主](https://www.luogu.com.cn/user/780539)的代码改了一改，循环范围扩大一下，过了。

这其实就是一个多维背包。
### 第二份代码
```cpp
#include<bits/stdc++.h>
#define qm(a,b) a=min(a,b)
#define ull unsigned long long
#define int long long
#define fo(i,l,r) for(int i=l;i<=r;i++)
#define fd(i,l,r) for(int i=r+5;i>=l;i--)
using namespace std;
int n, k, p, c[105], a[105][16], dp[16][16][16][16][16], ans = LLONG_MAX;
signed main()
{
    cin >> n >> k >> p;
    fd(j, 0, 10)fd(pk, 0, 10)fd(kk, 0, 10)fd(kkk, 0, 10)fd(l, 0, 10)dp[j][pk][kk][kkk][l] = LLONG_MAX - 1000000000000ll; //初始化
    if (k == 1)dp[0][p][p][p][p] = 0; //多余的维度用 p 来表示
    if (k == 2)dp[0][0][p][p][p] = 0;
    if (k == 3)dp[0][0][0][p][p] = 0;
    if (k == 4)dp[0][0][0][0][p] = 0;
    if (k == 5)dp[0][0][0][0][0] = 0;
    fo(i, 1, n) {
        cin >> c[i];
        fo(j, 1, k)cin >> a[i][j];
        if (k == 1) {
            fd(i1, a[i][1], p + 5)qm(dp[i1][p][p][p][p], dp[i1 - a[i][1]][p][p][p][p] + c[i]); //从上一个的价格递推
        }
        if (k == 2) {
            fd(i1, a[i][1], p + 5)fd(i2, a[i][2], p + 5)
                qm(dp[i1][i2][p][p][p], dp[i1 - a[i][1]][i2 - a[i][2]][p][p][p] + c[i]);
        }
        if (k == 3) {
            fd(i1, a[i][1], p + 5)fd(i2, a[i][2], p + 5)fd(i3, a[i][3], p + 5)
                qm(dp[i1][i2][i3][p][p],
                    dp[i1 - a[i][1]][i2 - a[i][2]][i3 - a[i][3]][p][p] + c[i]);
        }
        if (k == 4) {
            fd(i1, a[i][1], p + 5)fd(i2, a[i][2], p + 5)fd(i3, a[i][3], p + 5)fd(i4, a[i][4], p + 5)
                qm(dp[i1][i2][i3][i4][p],
                    dp[i1 - a[i][1]][i2 - a[i][2]][i3 - a[i][3]][i4 - a[i][4]][p] + c[i]);
        }
        if (k == 5) {
            fd(i1, a[i][1], p + 5)fd(i2, a[i][2], p + 5)fd(i3, a[i][3], p + 5)fd(i4, a[i][4], p + 5)fd(i5, a[i][5], p + 5)
                qm(dp[i1][i2][i3][i4][i5],
                    dp[i1 - a[i][1]][i2 - a[i][2]][i3 - a[i][3]][i4 - a[i][4]][i5 - a[i][5]] + c[i]);
        }
    }
    fd(i1, p, p + 5)fd(i2, p, p + 5)fd(i3, p, p + 5)fd(i4, p, p + 5)fd(i5, p, p + 5)ans = min(ans, dp[i1][i2][i3][i4][i5]); //求满足要求的答案
    cout << (ans != LLONG_MAX - 1000000000000ll ? ans : -1);
    return 0;
}
```
### 但这是歪解！！！
**原因**：原来的代码中数组只开到了 $10$，循环也只到 $10$，现在把它们都扩大到 $15$ 就过了？显然没那么简单。只是题目的数据水，让你到 $15$ 就过了。我们自己都可以轻轻松松出几组~~毒瘤~~数据把代码 hack 掉。
### 第三次尝试
~~看顶上的图片，我那么多次 WA 都是在调这个！~~

我使用了 set 和 map 来做。定义结构体 pik 记录当前指标的情况。每遇到一个计划就把它与 set 中的所有其他元素合并一下（列举所有情况），然后把它本身放入 set。显然如果指标已经满足要求就不用放入 set。

为了方便计算答案，使用一个 map，记录达到一个目标所需要的最少费用。
### 第三份代码
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <set>
#include <map>
#define ll long long
using namespace std;
ll n, k, p, c[105], a[105][6],  ans = 1e18;
struct pik
{
    ll a, b, c, d, e;
}tmp;
set <pik> s;
map <pik, ll> mp;
vector <pik> vt;
bool operator <(pik ta, pik tb) //排序
{
    if (ta.a == tb.a)
    {
        if (ta.b == tb.b)
        {
            if (ta.c == tb.c)
            {
                if (ta.d == tb.d) return ta.e < tb.e;
                return ta.d < tb.d;
            }
            return ta.c < tb.c;
        }
        return ta.b < tb.b;
    }
    return ta.a < tb.a;
}
int main()
{
    cin >> n >> k >> p;
    for (ll i = 1; i <= n; i++)
    {
        cin >> c[i];
        for (ll j = 1; j <= k; j++) cin >> a[i][j];
        for (ll j = k + 1; j <= 5; j++) a[i][j] = p; //初始化
        if (ans != 1e18 && c[i] >= ans) continue;
        vt.clear();
        for (auto &j : s)
        {
            if (ans != 1e18 && mp[j] + c[i] >= ans) continue;
            tmp = j;
            tmp.a = j.a+a[i][1];
            tmp.b = j.b+a[i][2];
            tmp.c = j.c+a[i][3];
            tmp.d = j.d+a[i][4];
            tmp.e = j.e+a[i][5]; //合并情况
            if ((tmp.a >= p) + (tmp.b >= p) + (tmp.c >= p) + (tmp.d >= p) + (tmp.e >= p)==5) //满足要求
            {
                ans = min(ans, mp[j] + c[i]);
                continue; //更新答案
            }
            if (mp.count(tmp)) mp[tmp] = min(mp[tmp], mp[j] + c[i]); //已经有了，不需要再放入 set
            else
            {
                mp[tmp] = mp[j] + c[i];
                vt.push_back(tmp);
            } //更新 map
        }
        for (auto &j : vt) s.insert(j);
        tmp.a = a[i][1];
        tmp.b = a[i][2];
        tmp.c = a[i][3];
        tmp.d = a[i][4];
        tmp.e = a[i][5]; //把自己放入
        if ((tmp.a >= p) + (tmp.b >= p) + (tmp.c >= p) + (tmp.d >= p) + (tmp.e >= p) == 5) //满足要求
        {
            ans = min(ans, c[i]);
            continue; //更新答案
        }
        if (mp.count(tmp)) mp[tmp] = min(mp[tmp], c[i]);//已经有了，不需要再放入 set
        else
        {
            mp[tmp] = c[i];
            s.insert(tmp);
        }//更新 map和set
    }
    if (ans != 1e18) cout << ans;
    else cout << -1;
}

```
### 为什么会 WA 呢？
原因：~~调了好久才发现~~ set 和 map 处理自定义的 struct 的状态似乎有点异常。
### 第四次尝试（正解）
**终于讲到正解了！**

set 和 map 有些异常？那保险起见就不用它们了。

改为使用五维数组动态规划，将指标 $> p$ 的数值改为 $p$，因为再高的指标没有意义。答案即为 $f_{p,p,p,p,p}$。

有人可能会问：为什么动态规划递推时要从大到小？

那是因为一个状态递推时会用到前一轮的状态，如果从小到大递推会使用到刚更新的状态，从而导致错误。这和状压 01 背包的递推是差不多的。
### 第四份代码（正解代码）
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <set>
#include <map>
#define ll long long
using namespace std;

ll n, k, p, f[6][6][6][6][6], a[105][6], c[105], mod = 0x3f3f3f3f3f3f3f, istart[6];
int main()
{
	for (ll i1 = 0; i1 <= 5; i1++) for (ll i2 = 0; i2 <= 5; i2++) for (ll i3 = 0; i3 <= 5; i3++)
		for (ll i4 = 0; i4 <= 5; i4++) for (ll i5 = 0; i5 <= 5; i5++) f[i1][i2][i3][i4][i5] = mod; //初始化为最大值
	cin >> n >> k >> p;
	cin >> c[1];
	for (ll j = 1; j <= k; j++) cin >> a[1][j];
	for (ll j = k + 1; j <= 5; j++) { a[1][j] = istart[j] = p; } //istart 是多出来的维度
	f[a[1][1]][a[1][2]][a[1][3]][a[1][4]][a[1][5]] = c[1]; //第一组数据特殊处理
	
	for (ll i = 2; i <= n; i++)
	{
		cin >> c[i];
		for (ll j = 1; j <= k; j++) cin >> a[i][j];
		for (ll j = k + 1; j <= 5; j++) a[i][j] = p;
		for (ll i1 = p; i1 >= 0; i1--) for (ll i2 = p; i2 >= istart[2]; i2--) for (ll i3 = p; i3 >= istart[3]; i3--)
			for (ll i4 = p; i4 >= istart[4]; i4--) for (ll i5 = p; i5 >= istart[5]; i5--) //可以看到，多出来的维度直接是从 p 到 p 循环
			{
				if (f[i1][i2][i3][i4][i5] != mod) // 能达到这个状态
				{
					f[min(i1 + a[i][1], p)][min(i2 + a[i][2], p)][min(i3 + a[i][3], p)][min(i4 + a[i][4], p)][min(i5 + a[i][5], p)] =
						min(f[min(i1 + a[i][1], p)][min(i2 + a[i][2], p)][min(i3 + a[i][3], p)][min(i4 + a[i][4], p)][min(i5 + a[i][5], p)], f[i1][i2][i3][i4][i5] + c[i]); // 背包
				}
			}
		f[a[i][1]][a[i][2]][a[i][3]][a[i][4]][a[i][5]] = min(c[i], f[a[i][1]][a[i][2]][a[i][3]][a[i][4]][a[i][5]]); //自己放进去
	}
	if (f[p][p][p][p][p] != mod) cout << f[p][p][p][p][p]; //答案
		else cout << -1;
}
```
实测 **Max Exec Time = 2ms**，应该是全谷最优解。
## 结语
**感谢本题解中提到的几位大佬。**

~~打字不易，点个赞再走吧。~~

---

## 作者：DerrickLo (赞：1)

注意到 $1\le K\le5$，我们可以把 $K$ 的取值分五种情况讨论。

当 $K=1$ 时，就是一个普通背包。

当 $K=2$ 时，设 $dp[i][j]$ 表示第一项参数最终是 $i$，第二项参数最终是 $j$ 时，花费最小是多少。可以得到转移方程

$$dp[i][j]=\displaystyle{\min_{k\le n,i\ge a[k][1],j\ge a[k][2]}dp[i-a[k][1]][j-a[k][2]]+c[k]}$$

显然其他的情况都是类似的，写 $5$ 次 $dp$ 就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,p,c[155],a[155][5],f1[20],f2[20][20],f3[20][20][20],f4[20][20][20][20],f5[20][20][20][20][20],ans=1e18;
signed main(){
	cin>>n>>k>>p;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		for(int j=1;j<=k;j++)cin>>a[i][j];
	}
	if(k==1){
		for(int i1=0;i1<=15;i1++)f1[i1]=1e18;
		f1[0]=0;
		for(int jj=1;jj<=n;jj++){
			for(int i=15;i>=a[jj][1];i--)f1[i]=min(f1[i],f1[i-a[jj][1]]+c[jj]);
		}
		for(int i=p;i<=15;i++)ans=min(ans,f1[i]);
		if(ans==1e18)cout<<-1;
		else cout<<ans;
		return 0;
	}
	if(k==2){
		for(int i1=0;i1<=15;i1++)for(int i2=0;i2<=15;i2++)f2[i1][i2]=1e18;
		f2[0][0]=0;
		for(int jj=1;jj<=n;jj++){
			for(int i=15;i>=0;i--)for(int j=15;j>=0;j--){
				if(i==0&&j==0)continue;
				if(i>=a[jj][1]&&j>=a[jj][2])f2[i][j]=min(f2[i][j],f2[i-a[jj][1]][j-a[jj][2]]+c[jj]);
			}
		} 
		for(int i=p;i<=15;i++)for(int j=p;j<=15;j++)ans=min(ans,f2[i][j]);
		if(ans==1e18)cout<<-1;
		else cout<<ans;
		return 0;
	}
	if(k==3){
		for(int i1=0;i1<=15;i1++)for(int i2=0;i2<=15;i2++)for(int i3=0;i3<=15;i3++)f3[i1][i2][i3]=1e18;
		f3[0][0][0]=0;
		for(int jj=1;jj<=n;jj++){
			for(int i=15;i>=0;i--)for(int j=15;j>=0;j--)for(int k=15;k>=0;k--){
				if(i==0&&j==0&&k==0)continue;
				if(i>=a[jj][1]&&j>=a[jj][2]&&k>=a[jj][3])f3[i][j][k]=min(f3[i][j][k],f3[i-a[jj][1]][j-a[jj][2]][k-a[jj][3]]+c[jj]);
			}
		}
		for(int i=p;i<=15;i++)for(int j=p;j<=15;j++)for(int k=p;k<=15;k++)ans=min(ans,f3[i][j][k]);
		if(ans==1e18)cout<<-1;
		else cout<<ans;
		return 0;
	}
	if(k==4){
		for(int i1=0;i1<=15;i1++)for(int i2=0;i2<=15;i2++)for(int i3=0;i3<=15;i3++)for(int i4=0;i4<=15;i4++)f4[i1][i2][i3][i4]=1e18;
		f4[0][0][0][0]=0;
		for(int jj=1;jj<=n;jj++){
			for(int i1=15;i1>=0;i1--)for(int i2=15;i2>=0;i2--)for(int i3=15;i3>=0;i3--)for(int i4=15;i4>=0;i4--){
				if(i1>=a[jj][1]&&i2>=a[jj][2]&&i3>=a[jj][3]&&i4>=a[jj][4])f4[i1][i2][i3][i4]=min(f4[i1][i2][i3][i4],f4[i1-a[jj][1]][i2-a[jj][2]][i3-a[jj][3]][i4-a[jj][4]]+c[jj]);
			}
		}
		for(int i1=p;i1<=15;i1++)for(int i2=p;i2<=15;i2++)for(int i3=p;i3<=15;i3++)for(int i4=p;i4<=15;i4++)ans=min(ans,f4[i1][i2][i3][i4]);
		if(ans==1e18)cout<<-1;
		else cout<<ans;
		return 0;
	}
	if(k==5){
		for(int i1=0;i1<=15;i1++)for(int i2=0;i2<=15;i2++)for(int i3=0;i3<=15;i3++)for(int i4=0;i4<=15;i4++)for(int i5=0;i5<=15;i5++)f5[i1][i2][i3][i4][i5]=1e18;
		f5[0][0][0][0][0]=0;
		for(int jj=1;jj<=n;jj++){
			for(int i1=15;i1>=0;i1--)for(int i2=15;i2>=0;i2--)for(int i3=15;i3>=0;i3--)for(int i4=15;i4>=0;i4--)for(int i5=15;i5>=0;i5--){
				if(i1>=a[jj][1]&&i2>=a[jj][2]&&i3>=a[jj][3]&&i4>=a[jj][4]&&i5>=a[jj][5])f5[i1][i2][i3][i4][i5]=min(f5[i1][i2][i3][i4][i5],f5[i1-a[jj][1]][i2-a[jj][2]][i3-a[jj][3]][i4-a[jj][4]][i5-a[jj][5]]+c[jj]);
			}
		}
		for(int i1=p;i1<=15;i1++)for(int i2=p;i2<=15;i2++)for(int i3=p;i3<=15;i3++)for(int i4=p;i4<=15;i4++)for(int i5=p;i5<=15;i5++)ans=min(ans,f5[i1][i2][i3][i4][i5]);
		if(ans==1e18)cout<<-1;
		else cout<<ans;
		return 0;
	} 
}
```

---

