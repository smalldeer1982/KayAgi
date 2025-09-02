# Shovels Shop

## 题目描述

There are $ n $ shovels in the nearby shop. The $ i $ -th shovel costs $ a_i $ bourles.

Misha has to buy exactly $ k $ shovels. Each shovel can be bought no more than once.

Misha can buy shovels by several purchases. During one purchase he can choose any subset of remaining (non-bought) shovels and buy this subset.

There are also $ m $ special offers in the shop. The $ j $ -th of them is given as a pair $ (x_j, y_j) $ , and it means that if Misha buys exactly $ x_j $ shovels during one purchase then $ y_j $ most cheapest of them are for free (i.e. he will not pay for $ y_j $ most cheapest shovels during the current purchase).

Misha can use any offer any (possibly, zero) number of times, but he cannot use more than one offer during one purchase (but he can buy shovels without using any offers).

Your task is to calculate the minimum cost of buying $ k $ shovels, if Misha buys them optimally.

## 说明/提示

In the first example Misha can buy shovels on positions $ 1 $ and $ 4 $ (both with costs $ 2 $ ) during the first purchase and get one of them for free using the first or the third special offer. And then he can buy shovels on positions $ 3 $ and $ 6 $ (with costs $ 4 $ and $ 3 $ ) during the second purchase and get the second one for free using the first or the third special offer. Then he can buy the shovel on a position $ 7 $ with cost $ 1 $ . So the total cost is $ 4 + 2 + 1 = 7 $ .

In the second example Misha can buy shovels on positions $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 8 $ (costs are $ 6 $ , $ 8 $ , $ 5 $ , $ 1 $ and $ 2 $ ) and get three cheapest (with costs $ 5 $ , $ 1 $ and $ 2 $ ) for free. And then he can buy shovels on positions $ 6 $ , $ 7 $ and $ 9 $ (all with costs $ 1 $ ) without using any special offers. So the total cost is $ 6 + 8 + 1 + 1 + 1 = 17 $ .

In the third example Misha can buy four cheapest shovels without using any special offers and get the total cost $ 17 $ .

## 样例 #1

### 输入

```
7 4 5
2 5 4 2 6 3 1
2 1
6 5
2 1
3 1
```

### 输出

```
7
```

## 样例 #2

### 输入

```
9 4 8
6 8 5 1 8 1 1 2 1
9 2
8 4
5 3
9 7
```

### 输出

```
17
```

## 样例 #3

### 输入

```
5 1 4
2 5 7 4 6
5 4
```

### 输出

```
17
```

# 题解

## 作者：字如其人 (赞：8)

引理1：选的 $k$ 双一定是价格最低的 $k$ 双。

对于一种方案中的一个物品 $i$ ，若存在一个不在方案中的 $j$ 使得 $val[j]<val[i]$ ，那么存在两种情况：

1、$i$ 在方案中被免费，那么替换后总价格不变。

2、$i$ 在方案中不免费，那么替换后总价格降低。

所以将 $i$ 替换为 $j$ 后总花费不会增多，所以引理1得证。

考虑 $dp$ ，$f[i]$ 表示前 $i$ 双所需的最小价格。

外层循环枚举物品 $i$ ，内层枚举 $j$（表示$i-j$ 内选择最好的套餐）,$dp$ 方程为 $f[i]=f[j]+sum[i]-sum[j+cal[i-j]]$ ,$sum[i]$ 为前 $i$ 个物品价格之和，$cal[i]$ 表示 $i$ 个物品能选择最划算的套餐。

贴代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005;
int n,m,k,a[N],cal[N],f[N];
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)a[i]+=a[i-1];
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		cal[x]=max(cal[x],y);
	}
	memset(f,0x7f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=k;i++){
		for(int j=0;j<=i-1;j++)
			f[i]=min(f[i],f[j]+a[i]-a[j+cal[i-j]]); 
	}
	printf("%lld",f[k]);
	return 0;
}
```


---

## 作者：一扶苏一 (赞：3)

[本场比赛题解](https://www.cnblogs.com/yifusuyi/p/10727303.html)

# F

## Description

商店里有 $n$ 双鞋，每双鞋都有一个价格。你要买其中的严格 $k$ 双。每双鞋只能被买一次。

你每次购买可以挑选剩余鞋中的任意一个子集来购买集合中所有的鞋。

有 $m$ 种套餐，第 $i$ 种套餐代表如果一次性购买 $x_i$ 双鞋则其中最便宜的 $y_i$ 双免费。

这 $m$ 种套餐每种都可以用任意次。

现在请求出买严格 $k$ 双鞋的最小化费。

## Limitation

$1~\leq~n,~m\leq~2~\times~10^5$

$1~\leq~k~\leq~\min(n, 2000)$

$1~\leq~a_i~\leq~2~\times~10^5$

## Solution

这tm是个假数据范围……

我们考虑鞋子是无序的，于是我们将他们按照升序排序。

考虑如果要最小化花费，那么只可能买最便宜的前 $k$ 双鞋。证明上考虑调整法，将某一双鞋换成另外的一双，如果这双鞋在最终方案中是需要花钱购买的，则答案更劣，否则答案不变，于是证明了换成更贵的不会使答案更优

在考虑对于 $x$ 相同的套餐，显然免费数量 $y$ 越高越高，于是我们对每个 $x$ 记录一个最大的 $y$，即为 $c_x$

接下来考虑我们买鞋可以分为两个部分，第一部分是按照原价买的，第二部分是套餐部分。由于套餐部分有一些鞋子是免费的，我们当然希望被免费的价格越高越好，于是我们要贪心的将套餐往后放，那么我们只会用原价购买最便宜的一部分鞋子，即从 $1$ 开始连续到某个位置的鞋子是原价购买的。剩下的全部使用套餐购买。

现在考虑如果将最后的 $i$ 双鞋子使用套餐购买，如何最小化答案：

这个东西可以使用DP完成，设 $f_i$ 为最后 $i$ 双鞋使用套餐购买的最小值，转移可以枚举使用 $x$ 为多大的套餐，于是状态转移方程为

$$f_i~=~\max_{j = 0}^{i - 1}\{f_j ~+~calc(i,j)\}$$

其中 $calc(i,j)$ 代表区间 $[k - i, k - j]$ 的鞋使用的套餐购买的最小花费，计算方法为

$calc(i, j)~=~\sum_{s = k - i}^{k - j}~a_s - \sum_{s = k - i}^{k - i + c_{j - i}} a_s$

也就是这段区间的价格和减去最大的优惠值。

通过求 $a$ 的前缀和，$calc$ 可以 $O(1)$ 计算。于是DP的总时间复杂度 $O(k^2)$。

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif

typedef long long int ll;

namespace IPT {
  const int L = 1000000;
  char buf[L], *front=buf, *end=buf;
  char GetChar() {
    if (front == end) {
      end = buf + fread(front = buf, 1, L, stdin);
      if (front == end) return -1;
    }
    return *(front++);
  }
}

template <typename T>
inline void qr(T &x) {
  char ch = IPT::GetChar(), lst = ' ';
  while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
  while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
  if (lst == '-') x = -x;
}

namespace OPT {
  char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
  if (x < 0) {x = -x, putchar('-');}
  int top=0;
  do {OPT::buf[++top] = static_cast<char>(x % 10 + '0');} while (x /= 10);
  while (top) putchar(OPT::buf[top--]);
  if (pt) putchar(aft);
}

const int maxn = 200009;
const int maxt = 2005;

int n, m, k;
ll ans;
int MU[maxn], CU[maxn];
ll frog[maxn], presum[maxn];

int main() {
  freopen("1.in", "r", stdin);
  qr(n); qr(m); qr(k);
  for (int i = 1; i <= n; ++i) qr(MU[i]);
  std::sort(MU + 1, MU + 1 + n);
  for (int i = 1, a, b; i <= m; ++i) {
    a = b = 0; qr(a); qr(b); CU[a] = std::max(CU[a], b);
  }
  memset(frog, 0x3f, sizeof frog); frog[0] = 0;
  for (int i = 1; i <= k; ++i) presum[i] = presum[i - 1] + MU[i];
  ans = presum[k];
  for (int i = 1; i <= k; ++i) {
    for (int j = i - 1; ~j; --j) {
      int s = i - j;
      frog[i] = std::min(frog[i], frog[j] + presum[k - j] - presum[k - i + CU[s]]);
    }
    ans = std::min(ans, frog[i] + presum[k - i]);
  }
  qw(ans, '\n', true);
  return 0;
}
```

---

## 作者：1saunoya (赞：2)

咋这种题都 2100 啊。。。


考虑从小到大排序只选前 $k$ 个。

我们考虑 $f_x$  为买 $x$ 个物品最多能免单多少个。

然后 $dp_x$ 表示买了 $1$~$x$ 的最小代价，$k^2$ 转移即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
using namespace std;
using ll=long long;
void cmax(int&x,const int&y){x=x>y?x:y;}
void cmin(int&x,const int&y){x=x<y?x:y;}

int n,m,k;
const int N=2e5+2;
int a[N];
int f[N];
int dp[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>m>>k;
	rep(i,1,n){cin>>a[i];}sort(a+1,a+n+1);rep(i,1,k){a[i]+=a[i-1];}
	while(m--){int x,y;cin>>x>>y;cmax(f[x],y);}
	memset(dp,0x7f,sizeof(dp));
	dp[0]=0;
	rep(i,1,k){rep(j,0,i-1){cmin(dp[i],dp[j]+a[i]-a[j+f[i-j]]);}}
	cout<<dp[k]<<'\n';
	return 0;
}

```

---

## 作者：I_have_been_here (赞：1)

# 题目分析

首先，读完题后我们可以明晰一个东西，这道题明显所求是最小花费，那么对于这一类最优解问题我们可以用到贪心或者是动态规划一类的算法解决，而用于这道题上，我的第一个想法就是结合贪心思想再使用 DP 进行解决

# 思路解析

那么题目中给出的问题是求买 $k$ 双鞋子所需要的最少的钱，那么~~傻子~~我们都知道要想钱最少，我们肯定在单价最少的前 $k$ 双鞋上做文章，也就是我们可以对原数据进行一个排序处理，这里就用到了贪心的思想；接着，我们可以对排好序的数组做一个前缀和的处理，从而可以通过简单计算得到区间和，方便我们之后的计算。

接下来是重点，有了我们预处理所得到的材料，那么我们怎么进行 DP 的转移呢？首先，我们考虑最基本的前 $k$ 双鞋子需要的钱，也就是不用任何优惠劵，那么就是前 $k$ 个数的前缀和，这里我们用 $pre_{k}$ 来表示，对于我们的状态数组可以定义为: $\mathit{dp}_{i}$ 表示前 $i$ 双鞋子我们利用优惠劵所得的最大优惠价格。那么有了这个状态，我们的答案无疑就存储在 $\mathit{pre}_{k} - dp_{k}$ 中。

有了最基本的状态，接下来我们需要解决的是如何进行状态转移，因为每一张优惠券可以重复使用，这里我们可以定义一个  $\mathit{buy}_{x} = y$ 的形式，表示买 $x$ 双鞋我们最多有 $y$ 双鞋可以不用付钱，其根本目的是过滤掉不是最优的优惠券，这样可以保证我们所取的优惠券都是 **当前状态下最优的**。

接下来我们的转移也就迎刃而解了，对于我们的 $\mathit{dp}_{i}$ 我们可以不断枚举 $j$ 来更新它，每一个 $\mathit{dp}_{j}$ 加上  $\mathit{pre}_{j + \mathit{buy}_{i - j}}$ 再减去 $pre_{j}$ 所得的值就是我们当前状态下的优惠值，那么为什么 $\mathit{pre}_{j + \mathit{buy}_{i - j}} - pre_{j}$ 就是我们这一 $i - j$ 段的所得优惠呢？我们可以明晰, $\mathit{buy}_{i - j}$ 的实际意义是买 $i - j$ 双鞋可得的最多不用付钱的鞋的数量，$i - j$ 也就是 $i$ 比 $j$ 多出来的那一段鞋的数量,那么对于本身的 $j$ ,加上这一段后再减去 $\mathit{pre}_{j}$ 所得及是多出来的那一部分不用付钱的鞋的钱的总数，再结合我们 DP 的状态，应该直接累加。

# AC CODE

```cpp
#include <bits/stdc++.h>
#define maxn 200005
using namespace std;
int dp[maxn], pre[maxn], buy[maxn], a[maxn];
int n, m, k;
int main() {
	//memset(buy, -0x3f3f3f3f, sizeof(buy));
	cin >> n >> m >> k;
	for (int i = 1, x; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= k; i++)
		pre[i] = pre[i - 1] + a[i];
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		buy[x] = max(buy[x], y);
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 0; j < i; j++) { // j不能比i大或者等于i
			dp[i] = max(dp[i], dp[j] + pre[j + buy[i - j]] - pre[j]); // 转移
		}
	}
	cout << pre[k] - dp[k] << endl;
}
```


---

## 作者：きりと (赞：0)

### 题目大意

见中文翻译

### 解题思路

贪心+dp，首先，肯定是买的越便宜越好，可以 `sort` 实现，其次，对于 $x[i]$ 相同的套餐， 肯定选 $y[i]$ 最大的。

我们可以用 $s[x]=y$ 表示套餐需求为 $x$ ，对应的最大白嫖数 $y$ 。

然后由于我们在dp的过程中要快速计算某一段鞋子的价值，所以考虑前缀和优化。

dp部分： $f[i]$ 表示买 $i$ 双鞋子所需的最小价值。

然后暴力转移即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define forr(i,l,r) for(int i=l;i<=r;i++)
#define ffor(i,r,l) for(int i=r;i>=l;i--)
#define int long long
const int N=2e5+2;
int a[N],f[N],s[N];
signed main()
{
	memset(f,0x3f,sizeof(f));
	int n,m,k;
	cin>>n>>m>>k;
	forr(i,1,n)
	{
		cin>>a[i];
	}
	forr(i,1,m)
	{
		int x,y;
		cin>>x>>y;
		s[x]=max(s[x],y);
	}
	sort(a+1,a+n+1);
	forr(i,1,k)
	{
		a[i]+=a[i-1];
	}
	f[0]=0;
	forr(i,1,k)
	{
		forr(j,0,i-1)   //之前买了的鞋子数量
		{
			f[i]=min(f[i],f[j]+a[i]-a[j+s[i-j]]);
		}
	}
	cout<<f[k]<<endl;
	return 0;
}

```

---

## 作者：漠寒 (赞：0)

## 分析

题意就是在 n 双鞋里买 k 双，有一些优惠方式可以使你少付一些鞋子的钱，计算最少的花费。

我们发现 k 很小，因此建立在它上面思考，我们又发现买入的鞋子为严格的 k 双，因此这道题就得到了极大的简化。鞋子数我们只需要留下最便宜的 k 双，优惠方案我们只需要留下 x 范围在 k 之内的最优的 y。

因此，n 和 m 都被我们缩到了 k 的范围，因此我们外层枚举剩余需要买的鞋子数，然后内层枚举优惠方案，$k^2$ 转移解决此题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int v[2005],n,m,k,a[200005],f[2001],b[2005];
inline int min(int aa,int bb){return aa<bb?aa:bb;}
inline int max(int aa,int bb){return aa>bb?aa:bb;}
inline void read(int &res){
	res=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
}

int main()
{
	read(n);read(m);read(k);
	memset(f,127,sizeof(f));
	f[k]=0;//初始化 
	for(int i=1;i<=n;i++)read(a[i]);
	sort(a+1,a+n+1);//找出前n小的方案 
	for(int i=1;i<=k;i++)b[i]=b[i-1]+a[i];//前缀处理转移 
	for(int i=1;i<=m;i++){
		int x,y;
		read(x);read(y);
		if(x>k)continue;
		v[x]=max(v[x],y);//存储在买x双的情况下最多能省多少双 
	}
	for(int i=k-1;i>=0;i--){
		for(int j=1;j<=k-i;j++){
			f[i]=min(f[i],f[j+i]+b[i+j]-b[i+v[j]]);//转移 
		}
	}
	cout<<f[0]<<endl;
	return 0;
}
```


---

## 作者：_Clown_ (赞：0)

[更好的阅读体验！！！](https://www.cnblogs.com/Xsmyy/p/13634935.html)
$$\huge\mathcal{Solution}$$
这道题目我们可以用$Dp$来解决。

我们容易想到这道题目的一个贪心：买最便宜的那几双鞋。

这应该是不难想的。

$Dp$题，我们就得设状态。

我们也不难想到，可以设$Dp_i$表示前$i$双鞋的$Cost_{Min}$。

然后应该就比较好转移了。

首先，我们的$Dp_i$一定是从前面的一个$Dp_j$转移过来。

然后略加思考，用一个前缀和，算出$Dp_i$比$Dp_j$要多付的钱，转一下即可。

转移方程就是：

$$
Dp_i=\min_{j=0}^{i-1}\{Dp_j+Prefix_i-Prefix_{j+Free_{i-j}}\};
$$
```cpp
#include<bits/stdc++.h>
using namespace std;
int Total,Sale,Buy;
int Array[200001];
int Prefix[200001];
int Free[200001];
int Dp[200001];
int main(void)
{
	register int i,j;
	cin>>Total>>Sale>>Buy;
	for(i=1;i<=Total;i++)
	{
		cin>>Array[i];
	}
	sort(Array+1,Array+Total+1);
	for(i=1;i<=Total;i++)
	{
		Prefix[i]=Prefix[i-1]+Array[i];
	}
	for(i=1;i<=Sale;i++)
	{
		register int X,Y;
		cin>>X>>Y;
		Free[X]=max(Free[X],Y);
	}
	for(i=1;i<=Buy;i++)
	{
		Dp[i]=0x7ffffff;
	}
	Dp[0]=0;
	for(i=1;i<=Buy;i++)
	{
		for(j=0;j<i;j++)
		{
			Dp[i]=min(Dp[i],Dp[j]+Prefix[i]-Prefix[j+Free[i-j]]);
		}
	}
	cout<<Dp[Buy]<<endl;
	return 0;
}
```

---

## 作者：da32s1da (赞：0)

考虑DP。

设$f[i]$为买$i$双鞋的最小花费，$g[i]$表示买$i$双鞋最多能免费多少双鞋。

显然只会买最便宜的$k$双鞋。

排序后，做一个前缀和。则有

$$f[i]=\min_{j=0}^{i-1}(f[j]+a[i]-a[j+g[i-j]])$$

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+50;
int n,m,k,a[N],g[N],f[N],x,y;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);//排序
	for(int i=1;i<=n;i++)a[i]+=a[i-1];//前缀和
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		g[x]=max(g[x],y);
	}
	for(int i=1;i<=k;i++){
		f[i]=0x3f3f3f3f;
		for(int j=0;j<i;j++)
		f[i]=min(f[i],f[j]+a[i]-a[j+g[i-j]]);
	}
	printf("%d\n",f[k]);
}
```

---

