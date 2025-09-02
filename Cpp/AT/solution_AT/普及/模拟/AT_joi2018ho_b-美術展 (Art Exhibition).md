# 美術展 (Art Exhibition)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2018ho/tasks/joi2018ho_b

JOI 国で美術展が行われることになった．美術展では，国中から集まった様々な美術品が展示される予定である．

展示される美術品の候補として，$ N $ 点の美術品が集まった．これらの美術品には $ 1,\ 2,\ \ldots,\ N $ の番号が付けられている．それぞれの美術品には大きさと価値と呼ばれる値が定まっている．美術品 $ i $ ($ 1\ \leqq\ i\ \leqq\ N $) の大きさは $ A_i $，価値は $ B_i $ である．

美術展では，これらの美術品のうちから $ 1 $ 点以上を選んで展示する．美術展の会場は十分に広く，$ N $ 点の美術品すべてを展示することも可能である．しかし，JOI 国の人々の美的感覚のため，美術品の間で大きさの差があまり大きくならないように展示する美術品を選びたい．一方，できるだけ価値の大きい美術品を多く展示したい．そのため，次の条件を満たすように展示する美術品を選ぶことにした：

- 選んだ美術品の中で，大きさが最大のものの大きさを $ A_{\mathrm{max}} $，最小のものの大きさを $ A_{\mathrm{min}} $ とする．また，選んだ美術品の価値の総和を $ S $ とする．
- このとき，$ S\ -\ (A_{\mathrm{max}}\ -\ A_{\mathrm{min}} $) を最大化する．

## 说明/提示

### 課題

展示される美術品の候補の個数と，それぞれの美術品の大きさと価値が与えられたとき，$ S\ -\ (A_{\mathrm{max}}\ -\ A_{\mathrm{min}}) $ の最大値を求めよ．

- - - - - -

### 制限

すべての入力データは以下の条件を満たす．

- $ 2\ \leqq\ N\ \leqq\ 500\,000 $．
- $ 1\ \leqq\ A_i\ \leqq\ 1\,000\,000\,000\,000\,000\ =\ 10^{15} $ ($ 1\ \leqq\ i\ \leqq\ N $)．
- $ 1\ \leqq\ B_i\ \leqq\ 1\,000\,000\,000 $ ($ 1\ \leqq\ i\ \leqq\ N $)．

### 小課題

#### 小課題 1 \[10 点\]

- $ N\ \leqq\ 16 $ を満たす．

#### 小課題 2 \[20 点\]

- $ N\ \leqq\ 300 $ を満たす．

#### 小課題 3 \[20 点\]

- $ N\ \leqq\ 5\,000 $ を満たす．

#### 小課題 4 \[50 点\]

- 追加の制限はない．

- - - - - -

### Sample Explanation 1

この入力例では，展示される美術品の候補が $ 3 $ 点ある．それぞれの美術品の大きさ，価値は次の通りである． - 美術品 $ 1 $ の大きさは $ 2 $，価値は $ 3 $ である． - 美術品 $ 2 $ の大きさは $ 11 $，価値は $ 2 $ である． - 美術品 $ 3 $ の大きさは $ 4 $，価値は $ 5 $ である． この場合，美術品 $ 1 $ と美術品 $ 3 $ を展示するために選ぶと，次のようにして $ S\ -\ (A_{\mathrm{max}}\ -\ A_{\mathrm{min}})\ =\ 6 $ となる． - 選んだ中で大きさが最大の美術品は，美術品 $ 3 $ である．よって，$ A_{max}\ =\ 4 $ である． - 選んだ中で大きさが最小の美術品は，美術品 $ 1 $ である．よって，$ A_{min}\ =\ 2 $ である． - 選んだ美術品の価値の総和は $ 3\ +\ 5\ =\ 8 $ であるから，$ S\ =\ 8 $ である． $ S\ -\ (A_{max}\ -\ A_{min}) $ を $ 7 $ 以上にすることは不可能なので，$ 6 $ を出力する． - - - - - -

### Sample Explanation 2

\- - - - - -

## 样例 #1

### 输入

```
3
2 3
11 2
4 5```

### 输出

```
6```

## 样例 #2

### 输入

```
6
4 1
1 5
10 3
9 1
4 2
5 3```

### 输出

```
7```

## 样例 #3

### 输入

```
15
1543361732 260774320
2089759661 257198921
1555665663 389548466
4133306295 296394520
2596448427 301103944
1701413087 274491541
2347488426 912791996
2133012079 444074242
2659886224 656957044
1345396764 259870638
2671164286 233246973
2791812672 585862344
2996614635 91065315
971304780 488995617
1523452673 988137562```

### 输出

```
4232545716```

# 题解

## 作者：Kano_zyc (赞：4)


~~蒟蒻第一篇题解，管理大大求过~~

## 题意简述

给定 $N$ 个物品，要在里面选取若干个物品，使他们的价值总和减去其中大小最大值与大小最小值的差最大。

## 思路

看到题目以及这个数据量很容易就能想到贪心，这里提供一个贪心思路：

因为题目要求价值总和减去其中大小最大值与大小最小值的差最大，所以只需要尽可能多选物品使价值总和最大即可，但同时我们又要使大小最大值与大小最小值的差最小。这里就需要排序了，排序方法如下：

首先我们应尽可能让尺寸越小的商品越靠前，对于尺寸相同的物品，我们应该使尺寸越大越靠前。

排完序后又应该怎么办呢？不难想到，我们应该再开一个前缀和数组 $sum$ 来记录当前所选物品价值。

最后，我们从 $1$ 至 $N$ 正序枚举最大的 $sum$ ，因为尺寸最小的此时已经包含其中了，所以此时用 $sum$ 减去最大尺寸物品即可得出答案。

## 注意事项

- 此题数据范围较大，记得开 long long

- 其他细节详见代码

## 代码君

```cpp

#include<iostream>
#include<algorithm>

using namespace std;

typedef long long LL;

//快读 
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
char *p1,*p2,buf[1<<20+5];
inline LL read()
{
	LL x=0;
	char c=gc();
	while(!isdigit(c)){
		c=gc();
	}while(isdigit(c)){
		x=x*10+(c^48);
		c=gc();
	}
	return x;
}
inline void print(LL x)
{
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

const int N=5e5+1;
LL n;//记得开 long long 
LL sum[N];
LL ans=-1e9,now;
struct Kano{
	LL x,y;
}a[N];

bool cmp(Kano a,Kano b)
{
	if(a.x!=b.x)
	   return a.x<b.x;
	return a.y>b.y;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	  a[i].x=read(),a[i].y=read();
	
	sort(a+1,a+n+1,cmp);
	
	for(int i=1;i<=n;i++)
	   sum[i]=sum[i-1]+a[i].y;
	   
	for(int i=1;i<=n;i++)
	{
		now=1ll*max(now,a[i].x-sum[i-1]);//枚举此时的最大值 
		ans=1ll*max(ans,now+sum[i]-a[i].x);
	}
	
    print(ans);//华丽结束 
    printf("\n");
    
	return 0;
}

```


---

## 作者：banned_wanyb (赞：2)

[AT_joi2018ho_b](https://www.luogu.com.cn/problem/AT_joi2018ho_b)

题目所求的量 $S-(A_{\max}-A_{\min})$ 可以分为两个部分，即 $S$ 和 $A_{\max}-A_{\min}$。

我们希望 $S$ 尽量大，希望 $A_{\max}-A_{\min}$ 尽量小。

对于两个看似矛盾的两个维度的处理方式一般为 dp 或者先固定一个维度。

dp 似乎没戏，来看第二种。

这里可以先固定差，也就是固定大小的最小值和最大值，也就是其中不能出现更小和更大，这里可以用一下排序，按照大小从小到大，这样固定大小的最小值和最大值之后只需让 $S$ 尽量大，把中间全部选上即可。

但是这样又冒出来两个维度，就是最大值和最小值，我们分别记为 $r$ 和 $l$，前缀和为 $\{sum_i\}$。

如果直接枚举是 $O(n^2)$ 的，不行。

我们继续固定维度，把 $r$ 固定之后，先把表达式写出来。

$$sum_r-sum_l-(A_r-A_l)
=(sum_r-A_r)+(A_l-sum_l)
$$

固定 $r$ 之后那么 $sum_r-A_r$ 是固定的，只需找到 $A_l-sum_l$ 最大，这里可以用前缀最大值维护。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,maxn,ans=LONG_LONG_MIN,s;
struct T{
	int a,b;
}a[500005];
bool cmp(T a1,T b1){
	if(a1.a==b1.a){//如果大小一样就按照价值排
		return a1.b>b1.b;
	}
	return a1.a<b1.a;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
	}sort(a+1,a+n+1,cmp);
	maxn=a[1].a;
	s=a[1].b;
	for(int i=2;i<=n;i++){
		maxn=max(maxn,a[i].a-s);//前缀最大值
		s+=a[i].b;//前缀和
		ans=max(ans,s-a[i].a+maxn);
	}
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：Silence_World (赞：2)

[题面](https://www.luogu.com.cn/problem/AT_joi2018ho_b)

### 题意

美术馆中有 $n$ 个物品，每个物品有自己的大小和价值，
我们要在其中选取若干个物品，使他们的价值总和减去其中大小最大值与大小最小值的差最大。

### 思路

一开始看到价值以为是背包，仔细审了审题发现很明显是道贪心，因为很明显这个最大值和最小值是可以分开处理的，开个结构体，以大小更大的放后面，用前缀和记录前面所有的价值（这个比较关键，因为大小已经排序，所以前面的大小都是不可能比后面的大小大的，所以可以放心大胆用前缀和，最小值也一样）。

然后可以开始处理最大最小值，逆序循环遍历 $n$，最大值就是以当前情况为最大值所得的值和上一个的最大值中最大的，这样我们就可以处理出在 $i$ 时的最大值的最优情况。

最小值也相同，顺序循环遍历 $n$，判断以当前这个为最小值和上一个的最小值中的最大的（因为题目中所要求的是加上最小值，所以我们取更优情况），再加上我们以求的最大值最优情况，就能得到一个以 $i$ 时的最优情况，用一个变量记录这些最优的最大的输出变量，结束！

不懂得可以借助代码理解：下面为本题代码:

``` cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
    int x, y;
} a[1000005];
bool cmp(node b, node c) {
    if (b.x != c.x) return b.x < c.x;
    return b.y < c.y;
}
int b[1000005];
int sum[10000005];
signed main() {
    int n;
    cin >> n;
    for (int i=1; i<=n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a+1, a+n+1, cmp);
    for (int i=1; i<=n; i++) {
        sum[i] = sum[i-1] + a[i].y; // 排序之后前缀和
    }
    b[n+1] = -1000000000000000000;
    int max1 = -10000000000000000; // 你觉得我会告诉你因为我max1开太大了wa了五六次吗QAQ
    for (int j=n; j>=1; j--) {
        b[j] = max(b[j+1], sum[j]-a[j].x);//求最大值的最优情况
    }
    for (int j=1; j<=n; j++) {
        max1 = max(max1, a[j].x-sum[j-1]+b[j]);//求最小值的最优情况，加上之前求的最大值最优情况就变成了本题要求的。
        // cout << max1 << " ";
    }
    cout << max1 << endl;
    return 0;
}

```

---

## 作者：banned_gutongxing (赞：1)

# 题目
[题目传送门](https://www.luogu.com.cn/problem/AT_joi2018ho_b)

题目大意：题目中有 $n$ 个物品，物品 $i(1\le i\le n)$ 的尺寸为 $A_i$，价值为 $B_i$。选择一些物品，记 $A_{\max}$ 为所选作品中最大的尺寸，$A_{\min}$ 为所选作品中最小的尺寸。设 $S$ 为所选艺术品的总价值。求 $S-(A_{\max}-A_{\min})$ 最大值。

# 思路
## 暴力思路
我们枚举 $i$，$j$ 表示从第 $i$ 个物品到第 $j$ 个物品的价值，然后再求最大值。时间复杂度：$O(n^2)$。
## 优化
因为与 $A_i$ 有很大的关系，考虑按照 $A_i$ 从小到大排序。因为要枚举两头，我们使用**定一求一**法。

我们固定最大的作品为第 $i$ 个物品，则我们确定的值为 $B_i-A_{\max}$，则我们要求 $S-B_i+A_{\min}$ 的最大值。此时我们使用前缀和，记 $P_i=\sum_{j=1}^{i}A_i$，则我们确定 $P_i-A_i$，我们只需要 $-P_{k-1}+A_k(k\in[1,i])$ 尽量大，使用递推。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int X = 6e5+10;
struct art{
	int a,b;
}a[X];
bool cmp(art a,art b){
	return a.a==b.a?a.b>b.b:a.a<b.a;
}
int sum[X],maxx[X],n,ans,now;
signed main(){
	scanf("%lld",&n);
	for(int i = 1;i<=n;i++){
		scanf("%lld%lld",&a[i].a,&a[i].b);
	}
	sort(a+1,a+1+n,cmp); //排序
	for(int i = 1;i<=n;i++){
		sum[i] = sum[i-1]+a[i].b; //前缀和
	}
	now = LLONG_MIN; //将now赋值为负无穷
	for(int i = 1;i<=n;i++){
		now = max(now,-sum[i-1]+a[i].a); //递推now
		ans = max(ans,now+sum[i]-a[i].a); //求答案
	}
	printf("%lld\n",ans); //Atcoder远古题的bug
	return 0;
}
```

---

## 作者：yzx3195 (赞：0)

# 题目大意

美术馆中有 $n$ 个物品，每个物品有自己的大小和价值，我们要在其中选取若干个物品，使他们的价值总和减去其中大小最大值与大小最小值的差最大。

# 思路

我们可以通过手玩样例发现，这题是个 ~~DP~~ 贪心，套路地，我们按照它的 $w$ 来给它排个序，然后，通过简单的模拟发现，我们可以设一个 $now$ 来表示现在可以获取的利润的最大值（不懂的可以看代码然后模拟一下），最后用 $now$ 来更新 $ans$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e05 * 5 + 7;

#define int long long

int n;

int sum[MAXN];

struct AEX {
    int val, w;
} a[MAXN];

template <typename T> int mymax(T x, T y)
{
    return x > y ? x : y;
}

template <typename T> int mymin(T x, T y)
{
    return x < y ? x : y;
}

bool cmp(AEX x, AEX y)
{
    return x.w < y.w;
}

signed main()
{
    scanf("%lld", &n);

    for(int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a[i].w, &a[i].val);
    }

    sort(a + 1, a + n + 1, cmp);

    for(int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + a[i].val;
    }

    int ans = -1e18;

    int now = -1e18;

    for(int i = 1; i <= n; i++)
    {
        now = mymax(now, a[i].w - sum[i - 1]);
        ans = mymax(ans, now + sum[i] - a[i].w);
    }

    printf("%lld\n", ans);

    return 0;
}
```

---

## 作者：florrygg (赞：0)

# AT_joi2018ho_b 美術展 (Art Exhibition) 题解

[题目传送门~~给我自己准备的~~](https://www.luogu.com.cn/problem/AT_joi2018ho_b)

## 思路

### $10\%$

直接暴力（~~shui~~）。

### $30\%$

剪枝即可（~~shui+1~~）。

### $50\%$

因为转移和 $a_i$ 的关系比较难处理，所以考虑按 $a_i$ 从小到大排序。

排序之后在枚举左端点和右端点用前缀和维护 $b_i$ 求答案。

### $100\%$

在 $50\%$ 的基础上考虑优化。

我们固定尺寸最大的作品为 $i$，大小为 $b_i$，我们要求 $(\sum_{j=l}^{r}a_j) -(b_i-b_l)$ 的最大值。记 $sum_i=\sum^{i}_{j=1}a_j$，我们确定 $sum_i-a_i$。我们需要 $a_k-sum_{k-1}$ 尽量大，使用递推求解。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int maxn=5e5+1;
int n;
int ans,now;
int sum[maxn];

struct Node{
	int a,b;
	bool operator<(const Node _a)
	{
		if(a==_a.a)
		{
			return b>_a.b;
		}
		return a<_a.a;
	}
}a[maxn];

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].a>>a[i].b;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i].b;
	}
	now=-9e18;
	for(int i=1;i<=n;i++)
	{
		now=max(now,a[i].a-sum[i-1]);
		ans=max(ans,now+sum[i]-a[i].a);
	}
	cout<<ans<<endl;
	return 0;
}
```

## 警告

这道题 $a_i \le 10^{15},n\le 5 \times 10^5$ 。

$(\sum_{i=1}^{n}a_i)\le 5 \times 10^{20}$ 理论上需要开高精或 `__int128` 但是数据比较水，所以只需要开 `long long` 即可。

---

## 作者：qscisQJing (赞：0)

发现大小与价值相互独立，所以考虑分开处理。由于物品大小涉及到极值，显然可以排个序，这样最优时必然只能选一个连续的区间。

然后发现问题变成了静态区间求和，可以对价值处理一个前缀和 $ w $， 表示前 $ i $ 个物品的价值和。那么，对于我们选的区间 $ [l,r] $，它们的和就是 $ w_r-w_{l-1}-A_r+A_l $。我们只需要预处理出 $ w_r-A_r $ 的最大值，然后扫一遍就可以了。

时间复杂度 $ O(N\log N) $，瓶颈在排序上。

---

