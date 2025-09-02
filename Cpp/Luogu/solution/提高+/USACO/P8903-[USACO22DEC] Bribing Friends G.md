# [USACO22DEC] Bribing Friends G

## 题目描述

Bessie 想要观看纪录片：奶牛基因组学，但她不想一个人去。不幸的是，她的朋友们没有足够的热情和她一起去！于是，Bessie 需要贿赂她的朋友们陪她去电影院。她的贿赂武器库中有两种工具：**哞尼**和**冰激凌甜筒**。

Bessie 有 $N(1 \le N \le 2000)$ 个朋友。然而，并非所有的朋友都是生而平等的！朋友 $i$ 有受欢迎度 $P_i(1 \le P_i \le 2000)$，Bessie 想最大化陪她的朋友们的受欢迎度之和。朋友 $i$ 只有当 Bessie 给了她 $C_i(1 \le C_i \le 2000)$ 哞尼才愿意陪她。如果 Bessie 给她 $X_i(1 \le X_i \le 2000)$ 个冰激凌甜筒，她还可以给 Bessie $1$ 哞尼的折扣。Bessie 可以从朋友那里得到任意整数数量的折扣，只要这些折扣不会使得朋友倒给她哞尼。 

Bessie 有 $A$ 哞尼和 $B$ 个冰激凌甜筒可供使用（$0 \le A,B \le 2000$）。请帮助她求出如果她以最优方案花费她的哞尼和冰激凌甜筒，她可以达到的最大受欢迎度之和。 

## 说明/提示

### 样例 1 解释

Bessie 可以将 $4$ 哞尼和 $4$ 个冰激凌甜筒给奶牛 $1$，将 $6$ 哞尼和 $3$ 个冰激凌甜筒给奶牛 $3$，这样奶牛 $1$ 和 $3$ 就可以陪她，得到 $5+10=15$ 的受欢迎度。

### 测试点性质

 - 测试点 $2-4$ 满足 $N \le 5$ 以及 $C_i=1$。
 - 测试点 $5-7$ 满足 $B=0$。
 - 测试点 $8-10$ 满足 $N,A,B,P_i,C_i,X_i \le 50$。
 - 测试点 $11-15$ 满足 $N,A,B,P_i,C_i,X_i \le 200$。
 - 测试点 $16-20$ 没有额外限制。

## 样例 #1

### 输入

```
3 10 8
5 5 4
6 7 3
10 6 3```

### 输出

```
15```

# 题解

## 作者：Mikefeng (赞：15)

# [USACO22DEC] Bribing Friends G

## 题目描述

Bessie 想要观看纪录片：奶牛基因组学，但她不想一个人去。不幸的是，她的朋友们没有足够的热情和她一起去！于是，Bessie 需要贿赂她的朋友们陪她去电影院。她的贿赂武器库中有两种工具：**哞尼**和**冰激凌甜筒**。

Bessie 有 $N(1 \le N \le 2000)$ 个朋友。然而，并非所有的朋友都是生而平等的！朋友 $i$ 有受欢迎度 $P_i(1 \le P_i \le 2000)$，Bessie 想最大化陪她的朋友们的受欢迎度之和。朋友 $i$ 只有当 Bessie 给了她 $C_i(1 \le C_i \le 2000)$ 哞尼才愿意陪她。如果 Bessie 给她 $X_i(1 \le X_i \le 2000)$ 个冰激凌甜筒，她还可以给 Bessie $1$ 哞尼的折扣。Bessie 可以从朋友那里得到任意整数数量的折扣，只要这些折扣不会使得朋友倒给她哞尼。 

Bessie 有 $A$ 哞尼和 $B$ 个冰激凌甜筒可供使用（$0 \le A,B \le 2000$）。请帮助她求出如果她以最优方案花费她的哞尼和冰激凌甜筒，她可以达到的最大受欢迎度之和。

## 做法

既然每个朋友每次都只给 $1$ 元钱的折扣，那我只要给要冰激凌最少的那个不就行了。

很可惜，并不行。就像捆绑销售，朋友只是给 Bessie 折扣，而不是直接给她钱，所以给要冰激凌最少的那个不一定是最优的。

但这为我们打开了一个思路：假设我们已经确定了最后要选哪几位朋友，那么优先给需要冰激凌最少的那位是最划算的。

所以我们先将朋友按 $X_i$ 升序排序，然后倒着做一遍01背包，就可以知道如果现在有 $a$ 个哞尼，从后往前找到第 $i$ 个朋友，最大的受欢迎度是多少。

然后再从后往前进行一次dp，枚举有 $b$ 个冰激凌，最大的受欢迎度是多少。

假设 $b$ 个冰激凌完全能收买这个朋友，那么我们还剩 $b'$ 个冰激凌继续去收买先前枚举过的朋友。假设 $b$ 个冰激凌不能完全收买这个朋友，那么之前枚举过的朋友也一定不能再用冰激凌收买，这时就利用第一次的dp，得到最大的受欢迎度是多少。

## 代码

不太理解的部分可以看代码。

```cpp

const ll N=205;
const ll M=2005;
const ll inf=0x3f3f3f3f;
ll n,m,k,ans;
struct node{
	ll a,c,x;
}a[M];
ll dp[M][M],f[M][M];
inline bool cmp(node a,node b){
	return a.x<b.x;
}
inline void pre_solve(){
	UF(i,n,1){
		F(j,0,m) dp[i][j]=dp[i+1][j];
		F(j,a[i].c,m) dp[i][j]=max(dp[i][j],dp[i+1][j-a[i].c]+a[i].a);
	}
}
int main(){
	n=read();m=read();k=read();
	F(i,1,n) a[i].a=read(),a[i].c=read(),a[i].x=read();
	sort(a+1,a+n+1,cmp);
	pre_solve();
	UF(i,n,1){
		F(j,0,k){
			f[i][j]=f[i+1][j];
			ll num=min(a[i].c,j/a[i].x);
			ll lst=j-num*a[i].x;
			if(num==a[i].c) f[i][j]=max(f[i][j],f[i+1][lst]+a[i].a);
			else f[i][j]=max(f[i][j],dp[i+1][m-(a[i].c-num)]+a[i].a);
			ans=max(ans,f[i][j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}

```



---

## 作者：zac2010 (赞：8)

### 思路

 $O(N^4)$ 的动态规划朴素做法这里就不再赘述。
 
我们考虑正解。看数据规模，正解的时间复杂度很有可能是 $O(N^2)$ 的。不难发现，我们这道题比较可能的两种算法是贪心和动态规划。可贪心少个策略，因为去评价一头奶牛有三个指标（受欢迎度、哞尼数以及多少个冰激凌可以化成一个哞尼）。

那么我们考虑继续思考动态规划。怎么优化呢？不难想到排序或者用某种策略以 **消掉一维** 。可该消哪一维呢？我们发现在固定选哪些奶牛的时候我们的冰激凌会优先用到 $X_i$ 小的奶牛身上。

所以我们发现，按照 $X_i$ 从小到大排序，对每个前缀做动态规划（即从前往后做动态规划），状态 $dp[i][j]$ 表示前 $i$ 头奶牛，共用 $j$ 个冰激凌可以获得的最大人气；相反，我们再从后往前做一遍动态规划，状态 $dp[i][j]$ 表示 $n$ 到 $i$ 这些奶牛，共用 $j$ 个哞尼可以获得的最大人气。那么我们只要枚举中断点，那个中断点哞尼和冰激凌都可以用，然后把两边和中断点相加再取最大值就可以获得最优的方案。

#### 证明

1. 会不会有多个中断点呢？
不会。我们考虑把中断点中靠后的点的冰激凌拿去给靠前的，一定不会亏。
2. 全选冰激凌和不选冰激凌的区间一定以前后缀的形式分别出现吗？
当然。原因是我们一定会把选的点中 $X_i$ 较大的给 $X_i$ 较小的，这样一定不会比之前的方案差，故为前缀。而后缀是因为都给前面的了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2010;
struct A{
	int p,c,x;
	friend bool operator < (const A a,const A b){//x从小到大排序 
		return a.x<b.x;
	}
}a[N];
int n,m[2],ans,dp[2][N][N],mx[2][N][N]; 
void Init_dp(int t){//dp初始化 
	memset(dp[t],0xf3,sizeof(dp[t]));
	memset(mx[t],0xf3,sizeof(mx[t]));
	dp[t][!t?0:n+1][0]=0;
	for(int i=0;i<=m[t^1];i++){
		mx[t][!t?0:n+1][i]=0;
	}
}
void DP(int t){
	Init_dp(t);
	if(!t){
		for(int i=1;i<=n;i++){
			int v=a[i].c*a[i].x,w=a[i].p;
			for(int j=0;j<=m[t^1];j++){
				if(j>=v){
					dp[t][i][j]=max(dp[t][i][j],dp[t][i-1][j-v]+w);
				}
				dp[t][i][j]=max(dp[t][i][j],dp[t][i-1][j]);
				mx[t][i][j]=max(mx[t][i][j-1],dp[t][i][j]);
			}
		}
	}
	else{
		for(int i=n;i>=1;i--){
			int v=a[i].c,w=a[i].p;
			for(int j=0;j<=m[t^1];j++){
				if(j>=v){
					dp[t][i][j]=max(dp[t][i][j],dp[t][i+1][j-v]+w);
				}
				dp[t][i][j]=max(dp[t][i][j],dp[t][i+1][j]);
				mx[t][i][j]=max(mx[t][i][j-1],dp[t][i][j]);
			}
		}
	}
} 
int main(){
	scanf("%d%d%d",&n,&m[0],&m[1]);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&a[i].p,&a[i].c,&a[i].x);
	}
	sort(a+1,a+n+1);
	DP(0),DP(1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=a[i].c&&j*a[i].x<=m[1];j++){
			ans=max(ans,mx[0][i-1][m[1]-a[i].x*j]+a[i].p+mx[1][i+1][m[0]-(a[i].c-j)]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：EXODUS (赞：7)


# Part 1：前言
好玩的 DP 题，感觉还是偏套路的。

下文称哞尼为钱，冰激凌甜筒为~~津巴布韦币~~甜筒。

# Part 2：正文

首先不难想到 $n^4$ 的 dp，设 $f_{i,j,k}$ 表示考虑到第 $i$ 头奶牛，有 $j$ 块钱，$k$ 个甜筒能取得的最大受欢迎度，不难写出 dp 转移如下
$$
f_{i,j,k}=\min(f_{i-1,j,k},f_{i-1,j-c_i+t,k-tx_i})
$$
其中 $t$ 是一个自然数，且 $t\leq c_i,tx_i\leq k$。

注意到这个 dp 是没有太大的优化空间的，我们发现比较烦人的是对 $t$ 的确定，不妨考虑什么时候会把甜筒换成钱。

假如我们现在已经确定了一个方案，不妨将所有选中的奶牛的 $x_i$ 按照升序排序为 $x_1',x_2',\ldots,x_n'$，那么我们一定会先把所有甜筒给 $x_1'$ 对应的奶牛，然后是 $x_2'$，$x_3'$（这意味着你的甜筒更值钱了，或者说在消耗同等甜筒，拉过来同等奶牛的情况下，你剩下的钱变多了）。因此，在对所有奶牛排序后，最优方案一定形如对前 $a-1$ 头奶牛用甜筒付，后 $n-a$ 头奶牛用钱付，第 $a$ 头奶牛混合付。

故而，设 $f(i,j)$ 表示排序后从前向后考虑第 $i$ 头奶牛，剩 $j$ 个甜筒的最大欢迎程度，$g(i,j)$ 表示排序后从后向前考虑第 $i$ 头奶牛，剩 $j$ 块钱的最大欢迎程度，答案即为枚举 $a$，枚举多少钱花在第 $a$ 头奶牛上，将对应的 $f$ 和 $g$ 合并即可，复杂度 $O(n^2)$（视 $A,B$ 与 $n$ 同阶）。

# Part 3：代码
```cpp
const int N=2e3+7;
int n,a,b;
ll f[N][N],g[N][N]; 
struct Cow{int c,x,p;}p[N];
bool cmp(Cow x,Cow y){return x.x<y.x;}
void Main(){
	n=read(),a=read(),b=read();
	for(int i=1;i<=n;i++){
		p[i].p=read();
		p[i].c=read();
		p[i].x=read();
	}sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=b;j++)f[i][j]=f[i-1][j];
		for(int j=0;j+p[i].x*p[i].c<=b;j++){
			f[i][j+p[i].x*p[i].c]=max(f[i][j+p[i].x*p[i].c],f[i-1][j]+p[i].p);
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=0;j<=a;j++)g[i][j]=g[i+1][j];
		for(int j=0;j+p[i].c<=a;j++){
			g[i][j+p[i].c]=max(g[i][j+p[i].c],g[i+1][j]+p[i].p);
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,f[i][b]+g[i+1][a]);
		ans=max(ans,f[i-1][b]+g[i][a]);
		for(int j=0;j<=min(a,p[i].c);j++){
			if(p[i].x*(p[i].c-j)>b)continue;
			ans=max(ans,f[i-1][b-p[i].x*(p[i].c-j)]+g[i+1][a-j]+p[i].p);
		}
	}
	printf("%lld\n",ans);
	return;
}
```

---

## 作者：DengDuck (赞：3)

首先我们设 $f(i,j,k)$ 表示前 $i$ 项还剩 $j$ 元和 $k$ 个冰淇淋的最大受欢迎程度，简单分析，这样做时间复杂度为 $O(n^4)$ 级别的，无法通过本题。

我们可以感性理解一手，~~其实是因为我也没理解透~~，不难发现冰淇淋并不是另外一个需要考虑的量，而是一个可以代替钱的优惠券。

彬彬跟我聊天的时候给出了一个比喻：我们换钱的时候，总是考虑去汇率更大的银行换钱。

因此，这道题我们可以考虑以“贿赂”所需的冰淇淋的数量从小到大排序，前面的朋友等同于汇率更大的银行。

我们在前面用冰淇淋肯定比在后面用好。

简单证明一下，如果我们在后面用了冰淇淋，前面用了钱，可以将后面的冰淇淋换成钱，把前面的钱换成冰淇淋，这样钱数不变，花费的冰淇淋变少。

我们考虑枚举一个中间点，中间点以上全部使用冰淇淋，中间点以下全部使用钱，中间点两者皆可，求出最大受欢迎程度即可。

这就拆成了两个背包。

时间复杂度降为 $O(n^2)$。

```c++
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e3+5;
struct node
{
	LL p,c,x;
}a[N];
LL n,m,k,f[N][N],g[N][N],ans;
bool cmp(node x,node y)
{
	return x.x<y.x;
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&a[i].p,&a[i].c,&a[i].x);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		LL p=a[i].p,c=a[i].c*a[i].x;
		for(int j=0;j<=c-1&&j<=k;j++)
		{
			f[i][j]=f[i-1][j];
		}
		for(int j=c;j<=k;j++)
		{
			f[i][j]=max(f[i-1][j],f[i-1][j-c]+p);
		}
	}
	for(int i=n;i>=1;i--)
	{
		LL p=a[i].p,c=a[i].c;
		for(int j=0;j<=c-1;j++)
		{
			g[i][j]=g[i+1][j];
		}
		for(int j=c;j<=m;j++)
		{
			g[i][j]=max(g[i+1][j],g[i+1][j-c]+p);
		}		
	}
	for(LL i=1;i<=n;i++)
	{
		for(LL j=0;j<=a[i].c&&j<=m;j++)
		{
			if((a[i].c-j)*a[i].x>k)continue;
			ans=max(ans,f[i-1][k-(a[i].c-j)*a[i].x]+a[i].p+g[i+1][m-j]);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：VictorChen (赞：3)

容易观察到，本题很像传统的背包问题；唯一的差别就是加入了第二种货币；因此我们考虑能否用 dp 来解决这道题。

其次我们来思考本题两种货币的性质；对于给定的决策方案，在使用甜筒时必然尽可能选择 $X_i$ 更小的牛。

因此，我们可以得出一个最合理地使用甜筒的方法：

> 对于前一部分 $X_i$ 较小的牛，全部使用甜筒来进行结算；
>
> 对于后一部分 $X_i$ 较大的牛，全部使用钱来结算；
>
> 此外，中间可能会有一头牛使用剩余甜筒获取折扣，同时使用钱来结算。

由此性质，我们可以设计出本题的 dp 方案：

- 定义 $dp_{i,j,1}$ 表示进行到第 $i$ 头牛，同时已经花费了 $j$ 个甜筒（未使用钱）进行购买的最大收益；
- 定义 $dp_{i,j,0}$ 表示进行到第 $i$ 头牛，同时已经用光了甜筒并使用了 $j$ 单位钱进行购买的最大收益。

转移上，我们考虑几种不同的情况（$c_1$ 表示所需钱，$c_2$ 表示获取 $1$ 折扣所需的甜筒）：

- 不选择购买第 $i$ 头牛

  此时有 $dp_{i,j,1} \gets dp_{i-1,j,1}$ 且 $dp_{i,j,0} \gets dp_{i-1,j,0}$；

- 全部使用甜筒结算

  此时有 $dp_{i,j,1} \gets dp_{i-1,j-c_1c_2,1}+v$；

- 全部使用钱结算

  此时有 $dp_{i,j,0} \gets dp_{i-1,j-c_1,0}+v$；

- 部分使用甜筒获取折扣，同时使用钱结算（两部分之间的转移）

  此时有 $dp_{i,c_1-j,0} \gets dp_{i-1,b-j\times c_2,1}+v\{j\leq c_1, j\times c_2\leq b\}$；
  
  这里我们遍历甜筒抵扣的钱的数额 $j$，所需的甜筒为 $j\times c_2$，所需的钱为 $c_1-j$。

核心代码如下：

```cpp
int cst = p[i].cst2 * p[i].cst1;

// 考虑如果不购买
for(int j=0; j<=a; j++) dp[i][j][0] = dp[i-1][j][0];
for(int j=0; j<=b; j++) dp[i][j][1] = dp[i-1][j][1];

// 考虑全部使用cst2结算
for(int j=cst; j<=b; j++)
{
    dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-cst][1] + p[i].val);
    // assert(false);
}

// 考虑使用cst2抵扣j，随后用cst1结算
// 抵扣的限额为cst1
for(int j=0; j<=p[i].cst1&&j*p[i].cst2<=b; j++)
{
    if(p[i].cst1-j > a) continue;
    dp[i][p[i].cst1-j][0] = max(dp[i][p[i].cst1-j][0], dp[i-1][b-j*p[i].cst2][1] + p[i].val);

    // assert(j == 0);
}

// 考虑全部使用cst1结算
for(int j=p[i].cst1; j<=a; j++)
    dp[i][j][0] = max(dp[i][j][0], dp[i-1][j-p[i].cst1][0] + p[i].val);
```

---

## 作者：_lqs_ (赞：3)

历经千辛万苦终于过了......

# solution



- 对于本题而言，每个人都可以有选或不选两种情况，因此很明显这是个背包题。


### solution搜索
- 老规矩，深搜找找规律。定义四个维度分别为 $k$，$s1$，$s2$，$s$，分别表示当前搜到第 $k$ 个人，花费了 $s1$ 个哞尼和 $s2$ 个冰淇淋，得到了 $s$ 的价值。

- 这里有一个小陷阱，就是每个人可以**多次用冰淇淋来换 $1$ 的哞尼**，这样的话就变得棘手了许多。

- 每一层的搜索分支就会很多：首先是不选，那么递归下一层，剩下三个变量都不变。如果选呢？换不换哞尼呢？换几个哞尼？这样需要枚举一遍可能的情况，枚举 $i$ 为换哞尼的数量，则 $i$ 从 $0$ 开始枚举，我们定义第 $k$ 位朋友要 $c_{k}$ 个哞尼，$x_{k}$ 个冰淇淋换一个哞尼，共有 $b$ 个冰淇淋，由于不能让朋友倒贴哞尼，因此最多换的哞尼数量是：
$$\min(c_{k},(b-s2) \div x_{k})$$

- 这样的暴搜可以拿到 $30pts$，贴上核心代码：

```cpp
void dfs(int k,int s1,int s2,int s){
	if(s1>a) return;//可行性剪枝
	if(k>n){
		ans=max(ans,s);
		return;
	}
	dfs(k+1,s1,s2,s);
	for(int i=0;i<=min(c[k],(b-s2)/x[k]);i++){
		dfs(k+1,s1+c[k]-i,s2+i*x[k],s+p[k]);
	}
}
```

- 在此基础上我们加上最优性剪枝就变成了 $40pts$：

```cpp
if(f[k][s1][s2]>=s) return;
	f[k][s1][s2]=s;
```

- 最后我们把能优化的全部优化，变成 $60pts$：

```cpp
int dfs(int k,int s1,int s2){
	if(s1>a) return -1e9;
	if(f[k][s1][s2]!=-1) return f[k][s1][s2];
	if(k>n) return 0;
	int p1,q=-1e9;
	q=dfs(k+1,s1,s2);
	for(int i=0;i<=min(c[k],(b-s2)/x[k]);i++){
		p1=dfs(k+1,s1+c[k]-i,s2+i*x[k])+p[k];
		q=max(q,p1);
	}
	return f[k][s1][s2]=q;
}
```

### solution背包

- 此时我们观察数据范围，注意到有 $B=0$ 的数据，所以特判一下这种情况，然后跑一边裸的背包，就变成了 $75pts$，这应该正解之外能拿到的最高分数，大家可以检测一下在很难想到正解的情况下能否把该拿的分都拿到。

- ~~正解我也没怎么想到，还参考了网上的一些想法。~~

- 定义两个数组 $f1$ 和 $f2$，**$f1_{i,j}$ 表示前 $i$ 个人只花 $j$ 个冰淇淋作代价所有的最大价值，$f2_{i,j}$ 表示后 $i$ 个人只花 $j$ 个哞尼所有的最大价值**。

- 这样在跑 $f1$ 数组时有个贪心策略，就是对 $c$ 进行排序，花费小的排在前面，这样我们能最大化价值，因此需要结构体。

- 以下是全部用冰淇淋的核心代码，有注释：

```cpp
for(i=1;i<=n;i++){
		for(j=0;j<=b;j++){
			f1[i][j]=f1[i-1][j];//全用冰淇淋即d[i].c*d[i].x
			if(j>=d[i].c*d[i].x) f1[i][j]=max(f1[i][j],f1[i-1][j-d[i].c*d[i].x]+d[i].p);//标准背包
		}
	}
```

- 其次全部不用冰淇淋跟 $B=0$ 的代码一致，是裸的背包。

- 定义结构体 $d$，$d_{i}.c$ 表示第 $i$ 个人需要的哞尼，$d_{i}.p$ 表示价值，$d_{i}.x$ 表示换 $1$ 个哞尼需要的冰淇淋数量。

- 那么两个混合用怎么处理呢？定义 $i$ 为当前枚举到第 $i$ 位朋友，$j$ 为对于当前朋友而言我花 $j$ 个哞尼，那么剩下的需要花费 $(d_{i}.c-j) \times d_{i}.x$ 个冰淇淋，那么需要满足 $(d_{i}.c-j) \times d_{i}.x \le b$ 才可以进行 $\max$ 的比较。

- 在满足情况的条件下，设 $ans$ 为最终答案，则有以下式子：

$$ans=\max(ans,f1_{i-1,b-(d_{i}.c-j) \times d_{i}.x}+f2_{i+1,a-j}+d_{i}.p$$

- 这里要提一下，$f2$ 数组要从后往前推，这是为了得到以上式子时价值不重复，即如果两个都从前往后推很可能同一状态下两个数组中记录的价值会有重复。而两个数组不同方向推就不会重复。

- 依旧是提供核心代码：

```cpp
for(i=1;i<=n;i++){
		for(j=0;j<=d[i].c;j++){
			if((d[i].c-j)*d[i].x<=b && j<=a){
				ans=max(ans,f1[i-1][b-((d[i].c-j)*d[i].x)]+f2[i+1][a-j]+d[i].p);
			}
		}
	}
```

- 结束了这道毒瘤题目，写的好像有点长。

---

## 作者：hzx360 (赞：2)

### 提供一种更为简单的理解方式

有价值，有容量，那就是个背包。

不过和普通背包又不一样，多了个可以优惠的条件。

那么我们先不管选的方式就假设最优解选了哪几个人，然后用那 $B$ 个冰淇淋去考虑最多能优惠多少，对于第 $i$ 个人只要给他/她 $X_i $ 个冰淇淋我们就可以优惠一块钱，那就尽量先给这些人中 $X_i$ 小的。

于是给着给着，可以发现，用冰淇淋可以直接把前面的人收买了，然后剩下一些不足以完全收买这个人，但可以在这个人身上得到一些优惠。
 
 于是我们得出这么一个结论：**对于收买的人群中一定是 $X_i$ 值小的先被被冰淇淋完全收买，然后一个人用冰淇淋和钱混合收买，后面的人只用钱收买。**
 
 那我们就先对其以 $X$ 值升序排序。
 
 之后设:
 
 $f(i,j)$ 表示 $1\sim i$ 人完全被 $j$ 个冰淇淋（只用冰淇淋）收买的最大最大受欢迎度，这是一个前缀的 DP。
 
 $dp(i,j)$ 表示 $i\sim n$ 人完全被 $j$ 块钱（只用钱）收买的最大最大受欢迎度，这是一个后缀的 DP。
 
 对于 DP 用背包求（这个都会吧 qaq）。
 
 最后枚举混合收买的是哪个人即可。
 
 **Tip：有些细节和临界情况，具体见代码。**
 
 code：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e3+100;
int n,A,B,f[N][N],dp[N][N];
struct node{int val,w,x,cost;}a[N];
bool cmp(node aa,node bb){return aa.x<bb.x;}
signed main(){
	cin>>n>>A>>B;
	for(int i=1;i<=n;i++) scanf("%lld%lld%lld",&a[i].val,&a[i].w,&a[i].x),a[i].cost=a[i].w*a[i].x;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=B;j++) f[i][j]=f[i-1][j];
		for(int j=B;j>=a[i].cost;j--) f[i][j]=max(f[i][j],f[i-1][j-a[i].cost]+a[i].val);
	}
	for(int i=n;i>=1;i--){
		for(int j=0;j<=A;j++) dp[i][j]=dp[i+1][j];
		for(int j=A;j>=a[i].w;j--) dp[i][j]=max(dp[i][j],dp[i+1][j-a[i].w]+a[i].val);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,f[i][B]+dp[i+1][A]);
		ans=max(ans,f[i-1][B]+dp[i][A]);
      //这里是临界情况，枚举的这个人也可以不是混合收买
		for(int j=1;j*a[i].x<=min(B,a[i].cost);j++){ //枚举优惠几块钱（当然也有个上界）
			if(A-a[i].w+j<0) continue;
			ans=max(ans,f[i-1][B-j*a[i].x]+dp[i+1][A-a[i].w+j]+a[i].val);
		}
	}
	cout<<ans;
}

---

## 作者：vectorwyx (赞：1)

按 $x_i$ 排序后，整个方案一定形如：一段前缀全折扣，物品变为 $(p_i,0,c_i x_i)$。一段后缀全零折扣，物品变为 $(p_i,c_i,0)$。中间一个点不一定。对前一种物品做前缀背包 $f(i,j)$ 表示考虑完 $[1,i]$ 的物品 $B$ 花去了 $j$ 的最大价值，对后一种物品做后缀背包 $g(i,j)$ 表示考虑完 $[i,n]$ 的物品 $A$ 花去了 $j$ 的最大价值，然后枚举中转点 $i$，以及折扣数 $j$，用 $p_i+f(i-1,k\le B-jx_i)+g(i+1,k\le A-(C_i-j))$ 更新答案。

代码如下：
```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

//17:24~17:33,17:33~17:33

const int N=2005;
struct Node{
	int p,c,x;
	bool operator<(const Node &y){re x<y.x;}
}a[N];
int n,A,B,f[N][N],g[N][N],ans;

signed main(){
	cin>>n>>A>>B;
	fo(i,1,n) a[i].p=read(),a[i].c=read(),a[i].x=read();
	sort(a+1,a+1+n);
	fo(i,1,n) fo(j,0,B){
		f[i][j]=f[i-1][j];
		if(j>=a[i].c*a[i].x) big(f[i][j],f[i-1][j-a[i].c*a[i].x]+a[i].p);
	}
	go(i,n,1) fo(j,0,A){
		g[i][j]=g[i+1][j];
		if(j>=a[i].c) big(g[i][j],g[i+1][j-a[i].c]+a[i].p);
	}
	fo(i,1,n)
		fo(j,0,min(a[i].c,B/a[i].x)){
			big(ans,a[i].p+f[i-1][B-j*a[i].x]+g[i+1][A-(a[i].c-j)]);
		}
	cout<<ans;
	return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：LJ07 (赞：1)

朴素做是 $O(n^3)$ 的，考虑找个性质优化掉一维状态。

日常贪心思想：发现答案序列操作肯定是用 $x$ 更小的去折扣。那么操作序列应该是这样：折扣折扣折扣...给 mooney 给 mooney。

那么就显然了，先按照 $x$ 升序排序，正着背包冰淇淋个数，倒着背包 mooney 个数。

最后枚举这个分界点统计答案即可。时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define U(i,a,b) for(int i(a),i##e(b);i<=i##e;++i)
#define D(i,b,a) for(int i(b),i##e(a);i>=i##e;--i)
using namespace std;
const int N(2000);
int n,a,b,dp[N+5][N+5],pd[N+5][N+5],ans;
struct P {int p,c,x;} A[N+5];
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>a>>b;
	U(i,1,n) cin>>A[i].p>>A[i].c>>A[i].x;
	stable_sort(A+1,A+1+n,[](P a,P b){return a.x<b.x;});
	U(i,1,n)
	{
		int tmp(A[i].c*A[i].x);
		U(j,0,b) 
			if (dp[i][j]=dp[i-1][j],j>=tmp) 
				dp[i][j]=max(dp[i][j],dp[i-1][j-tmp]+A[i].p);
	}
	D(i,n,1) U(j,0,a)
		if (pd[i][j]=pd[i+1][j],j>=A[i].c)
			pd[i][j]=max(pd[i][j],pd[i+1][j-A[i].c]+A[i].p);
	U(i,1,n) U(j,0,A[i].c)
	{
		int t1(j*A[i].x),t2(A[i].c-j);
		if (t1>b||t2>a) continue;
		ans=max(ans,dp[i-1][b-t1]+pd[i+1][a-t2]+A[i].p);
	}return cout<<ans,0;
}
```

---

## 作者：CmsMartin (赞：0)

[更好的阅读体验](http://www.cmsblog.top/archives/usaco22decbribingfriendsg)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/P8903)

## 思路

有显然的三维 dp。

设 $f_{i,j,k}$ 表示前 $i$ 个朋友用了 $j$ 个哞尼和 $k$ 个冰激凌甜筒能得到的最大价值。

那么有：

$$
f_{i,j,k} = \max_{w > c_i,w \times x_i > k}\{f_{i-1,j,k}, f_{i-1,j-c_i+w,k-w\times x_i} + p_i\}
$$

时间复杂度 $\Theta(n ^ 3)$，空间复杂度可以用滚动数组优化至 $\Theta(n ^ 2)$。

没有前途的 75pts。

考虑先对 $x_i$ 从大到小排个序，然后对冰淇淋和哞尼分别进行 dp。

设 $f_{i,j}$ 表示前 $i$ 个用了 $j$ 个哞尼的最大价值。这个 dp 很简单，时间复杂度 $\Theta(n^2)$。

接下来考虑上冰淇淋，设 $f_{i,j}$ 表示前 $i$ 个用了 $j$ 个冰淇淋的最大价值。

如果我们确定了要选择几个朋友，现在手上有 $b$ 个冰激凌，那我们完全可以完全收买这个朋友后再去收买其他朋友，这里的转移可以利用 $f$。时间复杂度 $\Theta(n^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2010;

int f[3][MAXN][MAXN];
int n, A, B, Ans;

struct _ {
	int p, c, x;
} o[MAXN];

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> A >> B;
	for (int i = 1; i <= n; i++)
		cin >> o[i].p >> o[i].c >> o[i].x;
	sort(o + 1, o + 1 + n, [](_ a, _ b) {
		return a.x < b.x;
	});
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j <= A; j++) f[1][i][j] = f[1][i + 1][j];
		for (int j = o[i].c; j <= A; j++) f[1][i][j] = max(f[1][i][j], f[1][i + 1][j - o[i].c] + o[i].p);
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j <= B; j++) {
			f[2][i][j] = f[2][i + 1][j];
			if (o[i].c <= j / o[i].x) f[2][i][j] = max(f[2][i][j], f[2][i + 1][j - o[i].c * o[i].x] + o[i].p);
			else f[2][i][j] = max(f[2][i][j], f[1][i + 1][A - (o[i].c - j / o[i].x)] + o[i].p);
			Ans = max(Ans, f[2][i][j]);
		}
	}
	cout << Ans << endl;
	return 0;
}

---

## 作者：hh__hh (赞：0)

我们可以使用动态规划来解决这个问题。

首先，我们定义一个状态 $dp_{i,j,k}$，表示在前 $i$ 个朋友中，使用 $j$ 个哞尼和 $k$ 个冰激凌甜筒的情况下，能够获得的最大受欢迎度之和。

对于每个朋友 $i$，我们有两种选择：要么给她哞尼，要么给她冰激凌甜筒。

如果我们选择给她哞尼，那么我们的状态转移方程为：

$$ dp_{i,j,k} = \max(dp_{i-1,j,k}, dp_{i-1,j-C_{i},k} + P_{i}) $$

如果我们选择给她冰激凌甜筒，那么我们的状态转移方程为：

$$ dp_{i,j,k} = \max(dp_{i-1,j,k}, dp_{i-1,j,k-X_{i}} + P_{i}) $$

最终的答案就是 $dp_{N,A,B}$。

根据状态转移方程，我们可以使用一个三维数组来存储状态 $dp$。其中 $dp_{i,j,k}$ 表示在前 $i$ 个朋友中，使用 $j$ 个哞尼和 $k$ 个冰激凌甜筒的情况下，能够获得的最大受欢迎度之和。

---

