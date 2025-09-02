# 主菜と副菜

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-relay/tasks/cf_2015_relay_g

$ N $ 種類の主菜と $ M $ 種類の副菜から料理を選んでコースを作ります。 主菜は $ 1 $ 種類しか選ぶことができませんが、副菜は何種類でも選ぶことができます。 また、副菜は $ 1 $ つも選ばなくても構いません。 主菜・副菜ともにコースに入れられるのは $ 1 $ 種類につき $ 1 $ つまでです。

- $ i $ 番目の主菜は値段が $ A_i $ で、お客さんの評価が $ B_i $ です。
- $ i $ 番目の副菜は値段が $ C_i $ で、お客さんの評価が $ D_i $ です。

コース全体の値段と評価は、主菜と副菜の合計で決まります。 コースの値段を $ L $ 以下にする時、コースの評価は最大でいくつになるか求めてください。

## 样例 #1

### 输入

```
2 2 10
2 3
3 6
3 5
5 5```

### 输出

```
13```

## 样例 #2

### 输入

```
3 3 10
1 1
2 3
3 5
4 8
5 10
6 12```

### 输出

```
19```

## 样例 #3

### 输入

```
3 3 10
1 1
11 11
11 11
11 11
11 11
11 11```

### 输出

```
1```

# 题解

## 作者：Samhu07 (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/AT_cf_2015_relay_g)&[ATcoder链接](https://atcoder.jp/contests/code-festival-2015-relay/tasks/cf_2015_relay_g)

## 题目翻译：


您将从 $n$ 种主菜和 $m$ 种副菜中选择菜品来创建一道套餐。您只能选择一种主菜，但可以选择任意数量的副菜。此外，也可以选择不选任何副菜。无论是主菜还是副菜，每种菜品只能选择一道。

## 题意简述：

首先明确一下这道题是 $01$ 背包，即每个物品只能选一次，题目中所说的 $m$ **种**物品和 $n$ **种**物品其实是 $m$ **个**物品和 $n$ **个**物品。并且主菜必须选且只能选一个。

## 思路分析：

可以先用 $01$ 背包维护副菜，$dp[i][j]$ 表示到第 $i$ 个物品为止，花费 $j$ 元钱可以得到的最大美味度。其中 $1\le i \le m$，$0\le j\le l-\min(a_k)(1\le k\le n)$。然后，枚举所有主菜，比较并更新美味度最大值。

## 代码：

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fo(i,x,y) for(int i = x;i<=y;i++)
#define go(i,x,y) for(int i = x;i>=y;i--)
const int inf = 2147483647;
using namespace std;
int n,m,l,dp[1010][10010],ans;//ans记录答案
int minn = inf;
struct node{
	int w,v;//w价钱，v美味度
}main_course[10010],side_dish[1010];//main_course主菜，side_dish副菜
int main(){
	scanf("%d%d%d",&n,&m,&l);
	fo(i,1,n){
		scanf("%d%d",&main_course[i].w,&main_course[i].v);
		minn=min(minn,main_course[i].w);//求主材价格最小值
	}
	fo(i,1,m)
		scanf("%d%d",&side_dish[i].w,&side_dish[i].v);
	//01背包维护副菜
	fo(i,1,m)
		fo(j,0,l-minn)//优化：至少要给最便宜的主菜留出钱
			if(j >= side_dish[i].w) //判断越界 (是否可以买)
				dp[i][j] = max(dp[i-1][j],dp[i-1][j-side_dish[i].w]+side_dish[i].v);//状态转移 (01背包)
			else dp[i][j]=dp[i-1][j];
	fo(i,1,n)//枚举主菜
		if(l >= main_course[i].w)//判断越界 (是否可以买)
			ans = max(ans,dp[m][l-main_course[i].w]+main_course[i].v);//更新答案最大值
	printf("%d\n",ans);//输出答案 换行好习惯
}
```


---

## 作者：虫洞吞噬者 (赞：1)

~~本蒟蒻竟能够为你谷第一个AC此题的人？？？~~

第一次做这个题是在初赛后的一个晚自习。当时十分自闭，并没有马上解决此题。现在马上复赛开始了，谨以此题振奋精神。

首先指正一下翻译的错误。此题的题面是说，共有$N$种主菜和$M$种副菜，每一次点餐只能选一种主菜，但是可以选择多种副菜。然而对于每一种主菜和副菜都只能挑选一次，不能挑选多次。并且每一次可以只选主菜，不选副菜。现在你的手头有$L$元，问你最多可以得到最大的美味值总和是多少。

纠正完题面后，再看一下题面，不难发现这是一道01背包的变形。对于主菜，由于必须选，我们可以挨个枚举判断。对于副菜，这就是一个比较裸的01背包模板。为了降低复杂度，我们先用01背包处理副菜在每一个价值时的最优解，然后再去考虑添加哪一个主菜会得到最优解。由此可将时间复杂度由$O(N^{3})$降低到$O(N^2)$，完美。

其实读一下数据范围便可知道，如果枚举完主菜后再用01背包处理副菜，超时是肯定的。这也是我前几次失败的原因之一(还有被题面翻译折磨的缘由)

分析到此，代码的框架大概就清晰了，附上代码仅供大家参考。

code:
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
ll n,m,s;
ll c1[10010],c2[10010],v1[10010],v2[10010];
ll f[100100];
int main()
{
	scanf("%lld%lld%lld",&n,&s,&m);
	for(int i=1;i<=n;++i)
		scanf("%lld%lld",&c1[i],&v1[i]);
	for(int i=1;i<=s;++i)
		scanf("%lld%lld",&c2[i],&v2[i]);
	for(int i=1;i<=s;++i)
		for(int j=m;j>=c2[i];--j)
			f[j]=max(f[j],f[j-c2[i]]+v2[i]);
	ll ans=0;
	for(int i=1;i<=n;++i)
		if(m>=c1[i])ans=max(ans,f[m-c1[i]]+v1[i]);//在枚举主菜的时候直接记录ans,想一想，为什么qwq
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Berd__ (赞：0)

## 题目简述
这道题就是 **0-1 背包**，即每个物品只能选一次，并且主菜必须选且只能选一个。
### 0-1 背包
什么是 0-1 背包？简单地说，就是在若干具有价值 $m$ 和体积 $v$ 的物品放在容量为 $L$ 的背包里，每件物品最多选一次，使所装物品价值最大。所以题目中的“价格”就是体积，“美味值”就是价值。

求解将哪些物品装入背包可使价值总和最大。

有一种暴力的做法，枚举每件物品是否选，复杂度 $O(2^n)$。

但是如果 $n$ 太大了，这个复杂度无法通过此题。

我们选取如下的 $dp$ 思路，$dp_{i_j}$ 表示前i件物品选j体积的物品最多的价值

则状态转移方程：$dp_{i_j}= \max(dp_{i-1_j},dp_{i-1_{j-w_j}} + v_i)$
```
//伪代码
for i := 1 to n:
  for j := m downto w[i]:
    dp[j] := max(dp[j], dp[j - w[i]] + v[i])
```
就解决了副菜的问题。

主菜由于只能选一个，所以只需要枚举找出最大值就行了。

---

## 作者：sz_wsy (赞：0)


#### [AT_cf_2015_relay_g 题目传送门](https://www.luogu.com.cn/problem/AT_cf_2015_relay_g)

## 题目大意
- 有 $n$ 个主菜，只能选 $1$ 个；有 $m$ 个配菜，可以选若干个，且每个菜**最多选一次**。
- 每个菜都有**价格** $c_i$ 和**美味值** $w_i$，求用 $L$ 元所能得到的最大美味值。
- 数据范围：$1\leq n\leq 10000$，$1\leq m\leq 1000$，$1\leq L\leq 10000$。

## 思路分析

对于每个菜，要么选，要么不选。不难发现这是一道 01 背包的变形题。什么是 01 背包？简单地说，就是在若干具有价值和体积的物品放在容量为 $L$ 的背包里，每件物品最多选一次，使所装物品价值最大。相对应地，题目中的“价格”就是体积，“美味值”就是价值。

我们可以定义 $dp_j$ 表示当背包的容量为 $j$ 时，所能装下的最大价值。
所以，状态转移方程就是：

$$dp_j=\max(dp_j,dp_{j-c_i}+w_i)$$

其中，$dp_{j-c_i}+w_i$ 和 $dp_j$ 分别表示选或不选这件物品的情况，再取最大值。

所以，最基本的 01 背包模板就是：

```cpp
for(int i=1;i<=n;i++){    //遍历n件物体
	for(int j=L;j>=c[i];j--){  //注意遍历顺序，j从背包容量L到c_i递减
		dp[j]=max(dp[j],dp[j-c[i]]+w[i]);  //状态转移方程
	}
}
```

而这道题则是 01 背包的变形。我们可以用以上的代码处理题中的配菜部分，接下来就要考虑主菜如何选择。对于每一件主菜，只要当满足 $c_i\leq L$ 时，都有可能选择该主菜。
最终代码如下：

```cpp
#include <iostream>
using namespace std;
int n,m,L;
int c1[10007],w1[10007];
int c2[1007],w2[1007];
int dp[10007];
int main(){
	cin>>n>>m>>L;
	for(int i=1;i<=n;i++){
		cin>>c1[i]>>w1[i];
	}
	for(int i=1;i<=m;i++){
		cin>>c2[i]>>w2[i];
	}	
	for(int i=1;i<=m;i++)
		for(int j=L;j>=c2[i];j--)
		    dp[j]=max(dp[j],dp[j-c2[i]]+w2[i]);
	int ans=-1;
	for(int i=1;i<=n;i++){
		if(c1[i]<=L) ans=max(ans,dp[L-c1[i]]+w1[i]);
	}
	cout<<ans<<"\n"; //岛国题一定要换行
    return 0;
}
```



---

## 作者：Mu_leaf (赞：0)

## [思路]
发现题目给出美味值与需要的钱数，一眼模板 01 背包。

01 背包是什么？

```
01背包是在 N 件具有体积与价值的物品取出若干件放在空间为M的背包里，
使得所装物品价值最大
                                        ----百度百科
```

这里我们可以定义 $f_{i,j}$ 为背包容量为 $j$，枚举到第 $i$ 道菜时所获得的的最大价值。

那么我们就可以从 $f_{i-1,j-w_i}$ 转移过来于是就有状态转移方程。

$$f_{i,j}=f_{i-1,j-w_i}+v_i$$

有个问题是，如果选这个菜并不是我们的最优解怎么办？也就是说 
$$f_{i-1,j-w_i}+v_i \leq f_{i,j}$$ 
的时候就需要比较两者大小选最大的即可。

## 优化：

我们又发现状态只与当前菜品和上一次的最优解有关，所以可以将 $f$ 数组压成一维的。

于是状态就变成了：

$$f_{j}=f_{j-w_{i}}+v_i$$

本题就做完了，完结撒花 (^3^)。

~~代码就不放了，毕竟模板题还是需要自己的理解与实践。~~

---

## 作者：ZHANGyutao123 (赞：0)

## [ AT_cf_2015_relay_g 主菜と副菜](https://www.luogu.com.cn/problem/AT_cf_2015_relay_g)
# 题目大意

在这道题目中，我们有 $n$ 种主菜和 $m$ 种副菜，我们需要从其中选择一个主菜和任意个（也可以不选）副菜来制作套餐。每道菜品都有一个价格和美味值，且每种菜品在套餐中仅能出现一次。现在我们有 $L$ 元钱，需要使得套餐的总价格不超过 $L$，同时套餐的总美味值最大。

# 过程分析

为了使得套餐的总美味值最大，我们需要让主菜和副菜的美味值之和尽可能大。而为了使得套餐的总价格不超过 $L$，我们需要控制副菜的数量并选择价格较低的主菜。

因此，我们可以使用背包问题的思路来解决这个问题。首先，我们可以使用一个 $dp$ 数组来记录当前预算下能够获得的最大美味值，其中 $dp[i]$ 表示在预算为 $i$ 的情况下能够获得的最大美味值。对于每个副菜而言，我们都可以选择或不选择它，因此我们可以使用 01 背包问题的思路对每个副菜进行更新：

$$ dp[j] = \max\{dp[j], dp[j - side\_dishes[i]] + side\_dishes\_values[i]\} $$

其中 $side\_dishes[i]$ 表示第 $i$ 种副菜的价格，$side\_dishes\_values[i]$ 表示第 $i$ 种副菜的美味值。这个更新过程意味着在选择当前副菜时，我们可以选择不选它或将它选入套餐中。

接下来，对于每个主菜，我们只需要计算当前预算减去这个主菜的价格后能够获得的最大美味值，与这个主菜本身的美味值相加即可：

$$ \max\{dp[budget - main\_dishes[i]] + main\_dishes\_values[i] | budget \geq main\_dishes[i]\} $$

其中 $main\_dishes[i]$ 表示第 $i$ 种主菜的价格，$main\_dishes\_values[i]$ 表示第 $i$ 种主菜的美味值。

最后，我们可以直接输出最终的最大美味值。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 10002;
const int MAX_M = 1002;
long long main_dishes[MAX_N], main_dishes_values[MAX_N]; // 主菜的价格和美味值
long long side_dishes[MAX_M], side_dishes_values[MAX_M]; // 副菜的价格和美味值
long long dp[MAX_N]; // dp数组，记录预算下能够获得的最大美味值

int main() {
	int n, m,budget; // n表示主菜数量，m表示副菜数量，budget表示预算
	cin >> n >> m >> budget;
	for (int i = 1; i <= n; i++)
		cin >> main_dishes[i] >> main_dishes_values[i]; // 读入主菜的价格和美味值
	for (int i = 1; i <= m; i++)
		cin >> side_dishes[i] >> side_dishes_values[i]; // 读入副菜的价格和美味值

	// 对每个副菜进行更新
	for (int i = 1; i <= m; i++)
		for (int j = budget; j >= side_dishes[i]; j--)
			dp[j] = max(dp[j - side_dishes[i]] + side_dishes_values[i], dp[j]);

	long long max_taste = 0; // 最大美味值
	// 对每个主菜进行计算
	for (int i = 1; i <= n; i++)
		if (budget >= main_dishes[i])
			max_taste = max(max_taste, dp[budget - main_dishes[i]] + main_dishes_values[i]);
	// 输出最大美味值
	cout << max_taste ;
	return 0;
}

```


---

## 作者：happy_zero (赞：0)

`01` 背包的题。

我们令 $n$ 为主菜个数，$m$ 为副菜个数，$l$ 为总金钱；$ww_i$ 和 $vv_i$ 为第 $i$ 道主菜的价值和美味度，$w_i$ 和 $v_i$ 为副菜的价值和美味度。

首先一下子就可以想到最直接的方法：先枚举选哪道主菜，接着对于 $1\le i\le n$，每次做一个容量为 $l-ww_i$ 的 `01` 背包。但很明显，这样的时间复杂度是 $O(nml)$，会超时，我们思考如何优化。

观察到，对于每个主菜的背包，由于副菜是固定的，所以每个容量的背包价值均为固定的，我们就可以先对所有的副菜预处理出所有容量的背包价值，接下来再枚举选哪一道主菜，若选第 $i$ 道主菜，则获得的价值为 $dp_{l-ww_i}+vv_i$（$ww_i\le l$）。因为主菜只能选一道，所以枚举的过程中不能更新 $dp$ 数组的值。

# Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 10005;
const int M = 1005;
int w[M], v[M];
int ww[N], vv[N];
int dp[N];
signed main()
{
    int n, m, l;
    cin >> n >> m >> l;
    for (int i = 1; i <= n; i++)
        cin >> ww[i] >> vv[i];
    for (int i = 1; i <= m; i++)
        cin >> w[i] >> v[i];
    for (int i = 1; i <= m; i++)
        for (int j = l; j >= w[i]; j--)
            dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (l >= ww[i]) ans = max(ans, dp[l - ww[i]] + vv[i]);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

翻译见题目。

首先我们先不考虑主菜，那显然就是一个 01 背包问题。

首先，01 背包问题是什么？

> 你有 $n$ 个物品，和一个容量为 $m$ 的背包，每个物品有两个属性，体积 $w_i$ 和价值 $v_i$，选择一些物品撞到背包，使得价值和最大。

首先，我们可以设 $dp_{i, j}$ 表示在前 $i$ 个物品中选出一些，放到容量为 $j$ 的背包中，最大的价值和。

那可以列出状态转移方程：

$$dp_{i,j} = \max(dp_{i - 1, j},dp_{i - 1, j - w_i} + v_i)$$

当然，若选第 $i$ 个物品，需要保证 $j\ge w_i$，因为如果容量小于它的体积的话，就不能选第 $i$ 个。

答案即为 $dp_{n, j}$ 的最大值。

观察这个状态转移方程，我们可以发现 $dp_{i, j}$ 只与 $dp_{i - 1, j}$ 有关，所以我们可以将 $dp$ 数组优化到一维，状态转移方程是：

$$dp_j = \max(dp_j, dp_{j - w_i} + v_i)$$

01 背包的伪代码如下：

```
for i := 1 to n:
  for j := m downto w[i]:
    dp[j] := max(dp[j], dp[j - w[i]] + v[i])
```

那么我们就解决了副菜的问题，那主菜怎么办呢？

可以直接用 $\mathcal O(n)$ 的时间复杂度枚举每一个主菜，找到最终答案的最大值即可。

最终代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)
#define per(i, r, l) for(auto i = (r); i >= (l); i --)

int n, m, l;

const int N = 100010;

int a[N], b[N], c[N], d[N];
int dp[N];

int main() {
  cin >> n >> m >> l;
  rep (i, 1, n) cin >> a[i] >> b[i];
  rep (i, 1, m) cin >> c[i] >> d[i];
  rep (i, 1, m) per (j, l, c[i]) 
    dp[j] = max(dp[j], dp[j - c[i]] + d[i]);
  int ans = 0;
  rep (i, 1, n) 
    if (a[i] <= l && dp[l - a[i]] + b[i] >= ans) ans = dp[l - a[i]] + b[i];
  cout << ans << endl;
}
```

---

## 作者：_7Mr (赞：0)

# 思路
**为初学者写的一片题解，再详细不过了。**
 
题目要求从给定的主菜和副菜中选择菜品，使得所选菜品的总价格不超过 $L$，并且获得的总评价值最大化。

首先，我们需要定义一个结构体 ```Dish``` 来表示菜品，其中包括菜品的价格和评价值。

然后，我们读取输入，包括主菜的种类数 $N$，副菜的种类数 $M$，以及限制的总价格 $L$。接下来，我们依次读取 $N$ 行主菜的价格和评价值，再读取 $M$ 行副菜的价格和评价值。这样，我们就得到了主菜和副菜的列表。

为了方便处理，我们将主菜和副菜分别按价格进行排序。

接下来，我们使用动态规划的思想来解决这个问题。我们使用两个循环来遍历所有可能的主菜和副菜的组合。对于每一种组合，我们计算当前菜品的总价格和总评价值。

在计算过程中，我们需要注意以下几点。 

- 如果当前的总价格已经超过了限制 $L$，我们停止添加副菜，因为再添加副菜只会使总价格进一步增加，而无法得到更好的评价值。
- 我们使用一个变量 $maxRating$ 来记录最大的评价值，每次计算得到的总评价值与 $maxRating$ 进行比较，并更新 $maxRating$。
- 最后，我们输出 $maxRating$，即所能获得的最大评价值。
# ACcode
太丑了，就不放出来丢人现眼了

---

