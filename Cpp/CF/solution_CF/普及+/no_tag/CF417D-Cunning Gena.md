# Cunning Gena

## 题目描述

Gena非常想参加“俄罗斯code cup”的决赛，或是至少得到一件T恤。 但是比赛的题目太复杂了，所以他安排他的n个朋友帮他解决这些问题。

在比赛中会有m道题目提供给参赛者。对于每个朋友，Gena知道他能解决什么问题。 但是Gena的朋友不会无偿的去帮助Gena的， 第i个朋友会因为帮助Gena解决所有他会的问题而向Gena索要x卢布。 并且，只有在Gena的电脑连接到至少k台显示器时，这个朋友才会去帮助Gena写代码。 且每台显示器需要花费b卢布。

Gena很节约用钱，所以他希望尽可能少的花钱去解决所有问题。 请你帮助Gena，告诉他怎样花费最少的钱。 最初，Gena的电脑没有连接任何显示器。

## 样例 #1

### 输入

```
2 2 1
100 1 1
2
100 2 1
1
```

### 输出

```
202
```

## 样例 #2

### 输入

```
3 2 5
100 1 1
1
100 1 1
2
200 1 2
1 2
```

### 输出

```
205
```

## 样例 #3

### 输入

```
1 2 1
1 1 1
1
```

### 输出

```
-1
```

# 题解

## 作者：lenlen (赞：15)

### Problem

题目大意：一共有 $m$ 道题目你有 $n$ 个好友，第 $i$ 个好友可以解决一些题目，但是需要 $w_i$ 的代价，并且需要你有 $k_i$ 台显示器，每台显示器 $b$ 元，你需要求出做完所有题目的最小代价。

数据范围： $n \leq 100,m \leq 20,w_i,k_i \leq 10^9$。

### Solution

看到数据范围，是状压 DP 无疑，我们需要设计一下状态。

设 $f_{i,j}$ 表示前 $i$ 个人完成了 $j$ 状态的题目的最小价值。

我们可以发现，因为显示器的存在，导致我们不好判断要加多少台显示器的价值，所以我们可以想到按显示器的所需数量进行排序，这样的话我们可以发现，当我们访问到 $f_{i,2^m-1}$ 时，若我们选了 $i$，那么显示器就是需要 $k_i$ 个；而我们不选第 $i$ 个，那么显然前面会存在一个 $j$ 使得满足条件的情况下 $f_{j,2^m-1}+k_j \times b \leq f_{i,2^m-1}+k_i \times b$，所以最优情况一定不是 $i$，也就不会有影响。

这个题，不好从**后面的状态来查询前面的状态进行更新**，因为可能更新的题目数有重复。比如我们假设有一个人会 $2,3$ 题，那么我们就不仅仅要从只会 $1$ 题进行转移，我们还需要从 $1,2$ 和 $1,3$ 进行转移，比较麻烦，所以我们采用**推出目前状态来更新后面的状态**的方式。

我们假设第 $i$ 个人会的题目状态是 $a_i$。

1. 选第 $i$ 个人： $f_{i+1,j \mid a_{i+1}}=f_{i,j}+w_{i+1}$。

2. 不选第 $i$ 个人： $f_{i+1,j}=f_{i,j}$。

最终求出 $\max\limits_{i=1}^n f_{i,2^m-1}+k_i \times b$ 就可以了。

我们还需要考虑一下空间，我们需要开 $n \times 2^m \times 8>8\times 10^8$ 的空间，会超，所以我们需要用滚动数组，因为 $f_{i+1,j}$ 只与 $f_{i,j}$ 有关，所以只需要存 $2 \times 2^m \times 8$ 的空间即可。

还有一个小问题，就是关于初始最大值的问题，我一开始 $inf=10^{18}$，结果发现答案中竟然还有比 $10^{18}$ 更大的，好家伙......

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=732,inf=2e18+7;//开大一点
long long f[2][1<<21];
int n,m,x,y;
long long ans=inf,b;
struct hl{
    int a;
    long long w,k;
}t[N];
bool cmp(hl x,hl y)
{
    return x.k<y.k;
}
long long mi(long long x,long long y)
{
    return x>y?y:x;
}
int main()
{
    scanf("%d%d%lld",&n,&m,&b);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld%d",&t[i].w,&t[i].k,&x);
        while(x--) scanf("%d",&y),t[i].a|=(1<<y-1);
    }
    sort(t+1,t+n+1,cmp);
    for(int i=1;i<(1<<m);i++) f[0][i]=inf; 
    for(int j=0;j<n;j++)
    {
        for(int i=0;i<(1<<m);i++) f[j+1&1][i]=inf;
        for(int i=0;i<(1<<m);i++)
        {
            if(f[j&1][i]==inf) continue;//节省时间
            f[j+1&1][i|t[j+1].a]=mi(f[j+1&1][i|t[j+1].a],f[j&1][i]+t[j+1].w);
            f[j+1&1][i]=mi(f[j+1&1][i],f[j&1][i]);
        }
        ans=mi(ans,f[j+1&1][(1<<m)-1]+t[j+1].k*b);//滚动数组中只能在程序内进行计算ans
    }
    printf("%lld\n",ans!=inf?ans:-1);
}
```


---

## 作者：aRenBigFather (赞：6)

## 整体思路
### 状态压缩DP
考虑到题目中,m<=20,很容易想到状态压缩做了哪些题目

----------
## DP设立

用 dp[sta] 表示做题状态为sta状态下 **不加显示器的花费**

即先不管每个人是否需要显示器,单纯让这些人做完题,能得到的最小花费值

----------

## 转移方程

### 思路取舍

状态压缩dp题转移一般有两个思路,一个是 **(1)后面的状态引用前面已经得到的状态的结果,实现转移**, 另一个是 **(2)前面的状态计算完毕后主动更新后面的结果**

这里考虑到如果后面的状态引用前面已经得到的状态,会使复杂度提高,所以采用第二种思路,降低复杂度

### 方程

$$dp[j | Frds[i].prob] = min(dp[j | Frds[i].prob],dp[j] + Frds[i].x);$$

其中

Frds[i].prob 表示 **压缩过后每个朋友能做题目的状态**

Frds[i].x 表示 **每个朋友完成题目过后需要的报酬**

j 表示 **当前枚举的状态**

这个就是用前面的状态 **j** 去更新后面状态 **j | Frds[i].prob** 的思想

---------

## 关于显示器价格

本来如果时间复杂度允许的情况下,可以枚举每个朋友需要的显示器个数再统计一下答案,但是由于这里如果再花一维n去枚举显示器个数的话,明显 **O(n * 2^m * n)** 会超时

所以考虑把朋友按照需要的显示器数量排序,因为每个显示器价格是固定的,也就保证了我们需要的显示器总价格(显示器数量*显示器价格)是递增的,保证dp正确

----------

## 坑点

### 这一题有点坑的是数据范围,最大值INF开到1e18还不够,要开成1e19,但是1e19又超过long long范围了,所以我用的unsigned long long,之前这个数据范围问题让我 WA 了好多次...

----------

## AC代码
```cpp
#include <bits/stdc++.h>
typedef unsigned long long ll;
using namespace std;
const ll inf = 1e19;
const int maxn = 110;
ll n,m,b;
struct Frd{
    ll x,k,prob;
}Frds[maxn];
ll dp[(1 << 20)+10];
inline bool cmp(const Frd &_a,const Frd &_b) { return _a.k < _b.k; }
int main(){
    scanf("%lld%lld%lld",&n,&m,&b);
    for(int i=0;i<maxn;i++) Frds[i].prob = 0;
    for(int i=1;i<=n;i++){
        int mm;
        scanf("%lld%lld%d",&Frds[i].x,&Frds[i].k,&mm);
        for(int j=0;j<mm;j++){
            int pid;
            scanf("%d",&pid);
            Frds[i].prob |= (1 << (pid-1));
        }
    }
    sort(Frds+1,Frds+1+n,cmp);
    for(int i=0;i<1048586;i++) dp[i] = inf;
    dp[0] = 0;
    ll dpans = inf;
    for(int i=1;i<=n;i++){
        for(int j=0;j<(1<<m);j++){
            if(dp[j] == inf) continue; //状态未更新,不能更新其他状态
            dp[j | Frds[i].prob] = min(1ll * dp[j | Frds[i].prob],dp[j] + Frds[i].x);
        }
        if(dp[(1<<m)-1] != inf) dpans = min(1ll*dpans,dp[(1 << m) - 1] + Frds[i].k * b); //显示器钱加上
    }
    ll ans;
    if(dpans == inf) ans = -1;
    else ans = dpans;
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

[$\texttt{Problem Link}$](https://codeforces.com/contest/417/problem/D)

#  简要题意

有 $n$ 个人，有 $m$ 道题目，可以花费 $b$ 元买一台显示器。现在可以让一些人给你打工，第 $i$ 个人打工要 $x_i$ 的工资还有 $k_i$ 台显示器（第 $i$ 个人用的显示器，其他人也可以用），让他打工能完成 $s_i$ 这个题目集合，问完成所有题目最少花多少钱。

# 思路

记 $x_i$ 表示第 $i$ 个人的花费，$s_i$ 表示第 $i$ 个人做题集合，$k_i$ 表示第 $i$ 个人需要的显示器。

$m \le 20$ 且不是计数，考虑 ```dp```，发现确实可以做。

可以设 $f_i$ 表示做题集合为 $i$ 时最小花费。

易得状态转移：

$$
f_{i\cup s_i} = \min\{f_j +x _i + t \times b\}
$$

$t$ 表示需要新买的显示器。特别的，不需要购买时 $t = 0$

但是直接这样做显然不对，因为对于 $x_i + k _ i \times b = x_j +k_j \times b$ 时，可能会选择 $k_i$ 更小的那个人导致之后需要的显示器费用增加，那么就要再将 $k$ 从大到小排序，因为这样能让后面花费在显示器上的钱尽量小。


[$\texttt{Code}$](https://codeforces.com/contest/417/submission/256121322)

---

## 作者：Light_Star_RPmax_AFO (赞：1)

# CF417D Cunning Gena 题解

$\mathcal{Update\ 2023.1.14} $ 发现自己贴错代码 qwq。

### 前言

[传送门](https://www.luogu.com.cn/problem/CF417D)

## 思路

由题知，我们需要解决所有问题，不妨把这个问题的状态设为一个全 $1$ 串，第 $i$ 个位置上的 $01$ 值表示这个问题是否解决。设 $dp_{i, j}$ 表示已经选了 $i$ 个人，问题解决状态为 $j$ 时的最小花费，状压 dp 模板。

注意，此处我们需要用滚动数组优化。

# AC Code

```cpp
#include <bits/stdc++.h>
#define rint register int
#define ll long long
using namespace std;

const ll MAX = 2e18;

inline int read(){
  int f = 1,x = 0;
  char ch = getchar();
  while(!isdigit(ch)){
	if(ch == '-')f = -1;
  	ch = getchar();
  }
  while(isdigit(ch)){
  	x = (x << 1) + (x << 3) + (ch ^ 48);
  	ch = getchar();
  }
  return x * f;
}
inline void print(int x){
  if(x > 9)print(x / 10);
  putchar(x % 10 + '0');
}

int n, m, b;

struct information{
    int a;
	ll x, k;
	bool operator < (const information &a){return k < a.k;}
}t[110];

long long dp[2][1 << 21], ans = MAX;

signed main(){
	n = read(), m = read(), b = read();
	for(rint i = 1; i <= n; i++){
		t[i].x = read(), t[i].k = read();
		rint mm = read();
		while(mm--){
			rint id = read();
			t[i].a |= (1 << id - 1);
		}
	}	
	sort(t + 1, t + 1 + n);
	for(rint i = 1; i < (1 << m); i++)
		dp[0][i] = MAX;
	for(rint j = 1; j <= n; j++){
		for(rint i = 0; i < (1 << m); i++)dp[j & 1][i] = MAX;
		for(rint i = 0; i < (1 << m); i++){
			if(dp[j + 1 & 1][i] == MAX)continue;
			dp[j & 1][i | t[j].a] = min(dp[j & 1][i | t[j].a], dp[j + 1 & 1][i] + t[j].x);
			dp[j & 1][i] = min(dp[j & 1][i], dp[j + 1 & 1][i]);
		}
		ans = min(ans, dp[j & 1][(1 << m) - 1] + t[j].k * b);
	}
	cout << (ans != MAX ? ans : -1);
  return 0;
}
```

---

## 作者：CQ_Alice (赞：1)

题目大意：你有 $m$ 个问题以及 $n$ 个友好的朋友，每位朋友都可以帮助你解决一些问题，但是要收费 $x_i$ 元，并且要求你拥有的显示屏数量大于等于 $k_i$ 个，每个显示屏 $b$ 元。

首先这道题其实是在 $n$ 个朋友中选取若干个，使得每个问题都 **至少** 被其中一位朋友所解决，求最小花费。但是 $k_i$ 的贡献我们应该如何计算呢？首先这个问题很明显是在构造集合解，所以选择朋友的顺序是不影响答案的，那么我们直接将这 $n$ 个朋友按照 $k_i$ 值递增排序，这样排完后，我们选择的朋友中的最后一位即是 $k_i$ 值最大的那一个，则贡献就是 $k$ 的贡献就是 $k_i \times b$。接下来考虑如何记录每个问题的解决状态，注意看题目中明确说明了 $m\le20$，这就意味着我们可以用二进制下的 $0/1$ 来表示每个问题的解决情况，即状态压缩，那么这道题就成为了一道简单的 $01$ 背包问题。

$f_{j}$：题目解决状态为 $j$ 的最小花费（**不** 包括买显示屏的花费）。

若第 $i$ 个朋友能解决的题目状态为 $a_i$，请他帮忙需要花费 $x_i$ 元则 $f_{j|a_i}=\min(f_j+x_i,f_{j | a_i})$。

$j|a_i$ 一定大于 $j$，所以倒序遍历 $j$ 就不会有后效性了。

答案就是 $f_{2^n-1}$ + $k_i \times b$ 的最小值。 

```cpp
#include<bits/stdc++.h>
using namespace std ;
const int Max = 110 , Nax = ( 1 << 20 ) ;
int n , m , x ; 
long long b ; 
struct Node {
	long long k ;
	int x , s , m ; 
} tr[Max] ;
long long f[Nax] , Ans ;
bool Prn( Node a , Node b ) {
	return a.k < b.k ; 
}
int main( ) {  Ans = 2e18 + 7 ;
	scanf("%d%d%lld" , &n , &m , &b ) ; 
	for(int i = 1 ; i <= n ; i ++ ) {
		scanf("%d%lld%d" , &tr[i].x , &tr[i].k , &tr[i].m ) ; 
		for(int l = 1 ; l <= tr[i].m ; l ++ ) {
			scanf("%d" , &x ) ; 
			tr[i].s |= ( 1 << ( x - 1 ) ) ; 
		}
	}
	sort( tr + 1 , tr + n + 1 , Prn ) ;
	for(int S = 0 ; S <= ( 1 << m ) - 1 ; S ++ ) f[S] = 2e18 + 7 ;  
	f[0] = 0 ; 
	for(int i = 1 ; i <= n ; i ++ ) {
		for(int S = ( 1 << m ) - 1 ; S >= 0 ; S -- ) 
			f[S | tr[i].s] = min( f[S] + tr[i].x , f[S | tr[i].s] ) ; 
		Ans = min( Ans , f[( 1 << m ) - 1] + tr[i].k * b ) ; 
	}
	if( Ans == 2e18 + 7 ) Ans = - 1 ; 
	printf("%lld\n" , Ans ) ;  
	return false ; 
}

```


---

## 作者：jasonliujiahua (赞：1)

# CF417D

[题目传送门](https://www.luogu.com.cn/problem/CF417D)
## 题意简述：
你需要请 $n$ 个朋友解决 $m$ 个问题，给出每个显示器的价格 $b$、每个朋友解决若干问题所需代价 $x_i$、每个朋友所需显示器数目 $k_i$、每个朋友能解决的问题数 $num_i$ 以及这 $num_i$ 个问题的具体编号，输出解决所有 $m$ 个问题所需的最小的代价。

$ 1 \le n \le 100,1\le m \le 20,1 \le b\le 10^9$。
## 题目分析：
### Step 1：最初想法
考虑到显示器数目是听所选朋友中的最大值的，我们不得不想办法知道每个状态下 $k_i$ 的最大值，因此考虑一劳永逸地对 $k_i$ 排序以方便知道实时的 $k_i$ 最大值。

由 $m$ 的数据范围可以联想到状压 dp。设 $dp_{i,s}$ 表示**选前 $i$ 个朋友帮忙解决状态为 $s$ 的题目所需除显示器外的代价**（由于定义我们不方便知道 $i$ 之前选的朋友 $j$ 在哪个位置，因此没法对 $k_i$ 和 $k_j$ 做差，因此考虑将显示器的代价在统计 $ans$ 时顺便统计）。

因为每位同学能解决的题目不一定全选，因此若从其他 $dp_{i-1,t}$ 的值去推 $dp_{i,s}$ 还需要枚举同学 $i$ 选择的题目，所以考虑由 $dp_{i-1,s}$ 推出其他 $dp_{i,t}$。设 $t_i$ 表示同学 $i$ 可做的题压成的二进制状态，可以得到转移方程：
$$dp_{i,s|t_i}=\min(dp_{i,s|t_i},dp_{i-1,s}+x_i)$$
注意这里的 $s|t_i$ 值得仔细品味，它简洁地实现了**同学 $i$ 所选题目为 $t_i$ 子集**的条件。

### Step 2：优化空间

但是如果你的 $dp$ 数组真的开了 $2$ 维，你大概会 MLE。当看到 $dp_i$ 只与 $dp_{i-1}$ 有关时，考虑滚动数组优化：
$$dp_{s|t_i}=\min(dp_{s|t_i},dp_s+x_i)$$
### Step 3：与背包问题
我在忘记调整 $dp$ 顺序下提交了代码并且 AC 了，后在 [sbj](https://www.luogu.com.cn/user/575363) 同学的提醒下才开始反思为什么我 $s$ 从小到大枚举竟然没有影响结果。

考虑到 $dp_{i,s}$ 一定不会比 $dp_{i-1,s}$ 差，因为“前 $i$ 个”是包含“前 $i-1$ 个”的，而且多了同学 $i$ 可能更新答案的可能性。因此，$dp_{i,s}\le dp_{i-1,s}$。

我们进行分类讨论：
- **情况一**：$dp_{i,s} < dp_{i-1,s}$
    当前的 $dp_s$ 被同学 $i$ 更新过（$t_i$ 被 $s$ 包含），即原来的 $dp_{i,s}$。此时 $s|t_i=s$，$dp_{s|t_i}=\min(dp_{s|t_i},dp_s+x_i)$ 就相当于 $dp_{i,s}=\min(dp_{i,s},dp_{i-1,s}+x_i)=dp_{i,s}$（$dp_{i-1,s}>dp_{i,s},x_i>0$，所以$dp_{i,s}<dp_{i-1,s}+x_i$）。而我的程序其实算的是 $dp_{i,s}=\min(dp_{i,s},dp_{i,s}+x_i)=dp_{i,s}$，不变。因此当 $dp_s$ 被同学 $i$ 更新过时不会影响结果。
- **情况二**：$dp_{i,s} = dp_{i-1,s}$
    当前的 $dp_s$ 没被同学 $i$ 更新过，即原来的 $dp_{i-1,s}$。此时其实是符合本来应该的顺序的。

我们接下来思考：为什么普通的背包 dp 需要倒序循环，而此程序并不需要？原因是 $dp_{i,s}$ 中 $i$ 与 $s$ 有特殊的、固定的关系，而普通背包中 $f_{i,j}$ 里的 $i$ 与 $j$ 其实没有什么关系。举个例子：$dp_{5}$ 只能代表 $4+1$，而 $f_{5}$ 不仅可以对应 $4+1$，还可以对应 $3+2$ 等。
## 注意事项：
滚动数组压缩时必须要 $\LARGE\text{{倒序循环！}}$
## 参考代码：
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=101;
const int inf=2e18;
int n,m,mm,b,ans=inf,dp[1<<21];
struct node
{
    int x,k,num,t;
}a[maxn];
bool cmp(node x,node y)
{
    return x.k<y.k;
}
void init()
{
    cin>>n>>m>>b;
    mm=((1<<m)-1)<<1;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x>>a[i].k>>a[i].num;
        for(int j=1;j<=a[i].num;j++)
        {
            int x;
            cin>>x;
            a[i].t|=(1<<x);
        }
    }
    a[0].k=0;
}
void DP()
{
    sort(a+1,a+n+1,cmp);
    for(int s=0;s<=mm;s++)
        dp[s]=inf;
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int s=0;s<=mm;s++)
        {
            dp[s|a[i].t]=min(dp[s|a[i].t],dp[s]+a[i].x);
        }
        ans=min(ans,dp[mm]+a[i].k*b);
    }
    if(ans>=inf) ans=-1;
    cout<<ans<<endl;
}
signed main()
{
    init();
    DP();
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

简单题。

首先假设没有显示器的限制直接状压跑个背包就完事了。

考虑把所有朋友按照需要的显示器数量从小到大排序，并钦定我们我们在某个朋友考虑完后选的答案一定选了这个朋友，那么方案中的显示器数量就确定了，因此排序后背包即可。

时间复杂度 $O(n \times 2^m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxv = (1ll<<20)+114;
const int maxn = 114;
const int inf = 2e18+114;
int dp[maxv];
struct Node{
    int x,k,v1;
}a[maxn];
bool cmp(Node x,Node y){
    return x.k<y.k;
}
int b;
int n,m;
signed main(){
    //freopen("Bbig.in","r",stdin);
    //freopen("Bbig.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>b;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].k;
        a[i].v1=0;
        int m1;
        cin>>m1;
        for(int j=1;j<=m1;j++){
            int pos;
            cin>>pos;
            a[i].v1+=(1ll<<(pos-1));
        }
    }
    sort(a+1,a+n+1,cmp);
    for(int i=0;i<maxv;i++) dp[i]=inf;
    dp[0]=0;
    int ans=inf;
    for(int i=1;i<=n;i++){
        for(int j=(1ll<<m)-1;j>=0;j--){
            dp[j|a[i].v1]=min(dp[j|a[i].v1],dp[j]+a[i].x);
        }
        ans=min(ans,dp[(1ll<<m)-1]+a[i].k*b);
    }
    if(ans>=inf) cout<<"-1\n";
    else cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：carp_oier (赞：0)

## advertisement

这位，靓仔你都来看我的题解了，为什么不来我的[博客](https://www.cnblogs.com/carp-oier/p/17770796.html)看看呢。

## analysis

首先我们看到数据范围，这个题目中的 $m$ 给定的很小，所以我们可以考虑用状压 dp 解决这个题目。当然这个题目貌似用背包也是可以的，有神犇是拿背包做的我看见好像。

我们压缩的状态就是我们可以用来解决的题目编号。

状态表示：$f_{i, j}$ 表示选择了前 $i$ 个人中，解决了的问题为 $j$ 的**最小花费**。

状态计算：

$$f_{i, j | s_i} \gets \min(f_{i - 1, j} + x_i, f_{i, j | s_i})$$

空间复杂度 $O(n2^m)$ 会炸，所以我们考虑优化：

由于每一次的转移只和上一层的有关，考虑滚动数组优化。

空间复杂度 $O(2^{m + 1})$，时间复杂度 $O(n2^m)$。（想写 $O(能过)$ 来着）

## code time

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll
#define foa(i, a, b) for(rl i=a; i < b; ++ i)
#define fos(i, a, b) for(rl i=a; i <= b; ++ i)
#define fop(i, a, b) for(rl i=a; i >= b; -- i)
#define ws putchar(' ')
#define wl putchar('\n')

template <class T> inline void waw(T x)
{
    if(x > 9) waw(x / 10);
    putchar(x % 10 ^ 48);
}

template <class T> inline void ww(T x)
{
    if(x < 0) x = ~x + 1, putchar('-');
    waw(x);
}

template <class T> inline void read(T &res)
{
    char ch = getchar(); bool f = 0; res = 0;
    for(; !isdigit(ch); ch = getchar()) f |= ch == '-';
    for(; isdigit(ch); ch = getchar()) res = (res << 1) + (res << 3) + (ch ^ 48);
    res = f ? ~res + 1 : res;
}

const ll N = 2100000, M = 110;

ll n, m, b, f[2][N], minn = 2e18;

struct node
{
    ll x, k, q;
    bool operator <(const node &x) const
    {
        return k < x.k;
    }
} a[M];

int main()
{
    read(n), read(m), read(b);

    fos(i, 1, n) 
    {
        ll cnt;
        read(a[i].x), read(a[i].k), read(cnt);
        while(cnt -- )
        {
            ll x; read(x);
            a[i].q |= 1 << x - 1;
        }
    }

    sort(a + 1, a + 1 + n);

    foa(i, 1, (1 << m)) f[0][i] = 2e18;

    fos(i, 1, n)
    {
        memcpy(f[i & 1], f[(i - 1) & 1], sizeof f[(i - 1) & 1]);
        foa(j, 0, (1 << m)) f[i & 1][j | a[i].q] = min(f[i & 1][j | a[i].q], f[(i - 1) & 1][j] + a[i].x);
        minn = min(minn, f[i & 1][(1 << m) - 1] + a[i].k * b);
    }

    if(minn == 2e18) minn = -1;

    ww(minn), wl;
    return 0;
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：0)

$m\le 20$，状压 DP。

首先可以根据每个人的 $k$ 从小到大排序。

定义 $f_{i,j}$ 表示考虑到第 $i$ 个人，完成了 $j$ 状态的题目，不考虑显示器所需的最小价格。

转移显然为 $f_{i,j|s_i}=\min(f_{i-1,j}+x_i)$。

最终答案为 $ans=\min\limits_{i=1}^{n}f_{i,S}+b\cdot k_i$。

考虑到当前状态只与上一个有关，滚动数组。

复杂度 $O(n2^m)$。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e6,N2=100+5,inf=LLONG_MAX>>1;
ll n,m,b,f[2][N],minn=inf;
struct node{ll x,k,m,s;}a[N2];
bool cmp(node x,node y){return x.k<y.k;}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m>>b;
  for(int i=1;i<=n;++i){
    cin>>a[i].x>>a[i].k>>a[i].m;
    int x;
    for(int j=1;j<=a[i].m;++j){
      cin>>x;
      a[i].s|=(1<<(x-1));
    }
  }
  sort(a+1,a+n+1,cmp);
  for(int i=1;i<(1<<m);++i)f[0][i]=inf;
  int t=1;
  for(int i=1;i<=n;++i){
    for(int j=0;j<(1<<m);++j)f[t][j]=f[t^1][j];
    for(int j=0;j<(1<<m);++j)f[t][j|a[i].s]=min(f[t][j|a[i].s],f[t^1][j]+a[i].x);
    minn=min(minn,f[t][(1<<m)-1]+b*a[i].k);
    t^=1;
  }
  if(minn==inf)cout<<-1<<endl;
  else cout<<minn<<endl;
  return 0;
}

```


---

## 作者：shyr (赞：0)

### 一句话题意
---
给 $n$ 个集合，有 $m$ 个元素的全集，每个集合最多有 $m_i$ 个元素，对于每个集合还有两个值 $a_i,b_i$，对于选出的所有集合，其费用为 $\max(b_i)\times B+\sum a_i$，求最小值并要求选出的集合并集为全集。

### 思路
---
考虑这题，由于集合**本来的编号**不好设置状态，我们可以以 $b_i$ 的**增长**为**阶段**，也就是说先转移 $b_i$ 更小的集合再转移 $b_i$ 更大的集合，所以很容易设计出状态 $dp_{i,s}$ 表示前 $i$ 个数选出集合 $s$ 的最小花费，由于每个元素只有选和不选两种可能，所以采用**二进制法**表示集合，这时转移方程如下：

$$dp_{i,s}=\min(dp_{i,s},dp_{j,s\cup c_i}+(b_i-b_j)\times B+a_i),j<i$$ 

其中 $c_i$ 表示第 $i$ 个集合，此时时间复杂度是 $\mathrm{O}(n^22^m)$ 的，空间复杂度是 $\mathrm{O}(n2^m)$ 的，无论是时间还是空间都难以承受。

考虑优化这个状态，容易发现，由于我们只考虑**最大**的 $b_i$，且数组已经按照 $b_i$ **递增排序**，所以我们只要在统计答案时考虑 $b_i$ 即可，此时状态为 $dp_{i,s}$ 为前 $i$ 个数**不考虑** $b_i$ 花费的最小值。此时转移如下：

$$dp_{i+1,s}=\min(dp_{i,s},dp_{i+1,s}),dp_{i+1,s|c_i}=\min(dp_{i+1,s|c_i},dp_{i,s|c_i}+a_i)$$

滚动数组优化即可，答案即为 $\min(dp_{i,2^m-1})+b_i\times B$。

时间复杂度 $\mathrm{O}(n2^m)$，空间复杂度 $\mathrm{O}(2^m)$。

```cpp
/*Author:luogu uid 357163 Respons_*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
typedef unsigned long long ULL;
template<typename t> t &read(t &x){
	char c;int f=1;
	while(!isdigit(c=getchar()))f=(c=='-')?-1:1;
	x=c^'0';
	while(isdigit(c=getchar()))x=x*10+(c^'0');
	return x*=f;
}
int n,m,b;
LL dp[2][1<<20];
struct Friends{
	int x,k,m,a;
	bool operator <(const Friends &a) const{
		return k<a.k;
	}
}d[105];
signed main(){
	#ifdef LOCAL
		freopen("out.txt","w",stdout);
	#endif
	read(n),read(m),read(b);
	for(int i=1;i<=n;++i){
		read(d[i].x),read(d[i].k),read(d[i].m);
		for(int j=1;j<=d[i].m;++j){
			int x;read(x);
			x--;d[i].a|=(1<<x);
		}
	}
	sort(d+1,d+1+n);
	memset(dp,0x3f,sizeof(dp));
	LL lim=dp[0][0],minn=dp[0][0];
	dp[0][0]=0;int t=0;
	for(int i=0;i<n;++i,t^=1){
		memset(dp[t^1],0x3f,sizeof(dp[t^1]));
		for(int j=0;j<(1<<m);++j){
			dp[t^1][j|d[i+1].a]=min(dp[t][j]+d[i+1].x,dp[t^1][j|d[i+1].a]);
			dp[t^1][j]=min(dp[t^1][j],dp[t][j]);
		}
		minn=min(minn,dp[t][(1<<m)-1]+(LL)b*d[i].k);
	} 
	minn=min(minn,dp[t][(1<<m)-1]+(LL)b*d[n].k);
	if(minn==lim)puts("-1");
	else printf("%lld\n",minn);
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

显示器的数量为所有选择的人的最大值，我们不妨对所有人按照 $k$ 排序方便计算。

首先这道题很明显的状压。 $f(i,s): $ 前 $i$ 个人，能处理的问题的集合为 $s$ 的最小花费。转移的时候考虑枚举上一个选择的人是谁，这样就能确定第 $i$ 个人在显示器上给总代价贡献了多少。

但是这样是没必要的。因为在计算显示器贡献的时候，唯一有用的是 $k$ 最大的人。也就是说，在计算 $f(i,s)$ 的时候，如果 $i$ 被选了，对于计算显示屏的贡献，前面的人选不选是没有任何用处的。如果 $i$ 不选，那么这个结果一定在 $i$ 更小的时候就被统计过了（在统计答案时）。所以是没有必要把显示器的贡献扔到 DP 中去的。

所以我们设 $f$ 表示除去显示器的价值贡献的最小值。

有转移

$$
f(i+1,s \cup t_{i+1}) \leftarrow f(i,s)+x_{i+1}
$$
$$
f(i+1,s) \leftarrow f(i,s)
$$

初始值

$$
f(0,0)=0
$$

答案

$$
ans=\min f(i,U)+k_ib
$$

既然空间要炸，那么滚动数组即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=109,inf=0x3f3f3f3f3f3f3f3f;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,m,b,f[2][1<<22];
struct node {int x,k,t;} a[N];
bool cmp(const node &a,const node &b) {return a.k<b.k;}

void upd(int &x,int y) {x=min(x,y);}

signed main() {
	n=read(), m=read(), b=read();
	rep(i,1,n) {
		a[i].x=read(), a[i].k=read(); int m=read();
		rep(j,1,m) a[i].t+=(1ll<<read()-1);
	}
	sort(a+1,a+n+1,cmp);
	int S=(1ll<<m)-1,d=0,ans=inf;
	rep(s,1,S) f[0][s]=inf;
	rep(i,0,n-1) {
		rep(s,0,S) f[d^1][s]=inf;
		rep(s,0,S) if(f[d][s]<inf) {
			upd(f[d^1][s|a[i+1].t],f[d][s]+a[i+1].x);
			upd(f[d^1][s],f[d][s]);
		}
		if(f[d^1][S]<inf) ans=min(ans,f[d^1][S]+a[i+1].k*b);
		d^=1;
	}
	printf("%lld\n",ans==inf?-1ll:ans);
	return 0;
}
```

---

