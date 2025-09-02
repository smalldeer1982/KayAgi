# [ABC200E] Patisserie ABC 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc200/tasks/abc200_e

「ABC洋菓子店」で働くパティシエである高橋君は、ケーキを作って AtCoder Beginner Contest 200 を祝うことにしました。

高橋君の作るケーキは、「綺麗さ」「おいしさ」「人気度」の $ 3 $ つのパラメータをもち、それぞれのパラメータは $ 1 $ 以上 $ N $ 以下の整数で表されます。

高橋君は、「綺麗さ」が $ i $ 、「おいしさ」が $ j $ 、「人気度」が $ k $ であるケーキを、全ての組 $ (i,j,k)\ (1\ \le\ i,j,k\ \le\ N) $ に対して $ 1 $ つずつ作りました。  
 その後、高橋君は、できた $ N^3 $ 個のケーキを以下の順序で並べました。

- 「綺麗さ」+「おいしさ」+「人気度」が小さいものを、より左に並べる。
- ここまでで順序がつかなければ、「綺麗さ」が小さいものを、より左に並べる。
- ここまでで順序がつかなければ、「おいしさ」が小さいものを、より左に並べる。

このとき、左から $ K $ 番目にあるケーキの各パラメータの値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 10^6 $
- $ 1\ \le\ K\ \le\ N^3 $

### Sample Explanation 1

各ケーキの各パラメータの値を (「綺麗さ」,「おいしさ」,「人気度」) と書くと、ケーキは左から以下の順に並びます。 $ (1,1,1),(1,1,2),(1,2,1),(2,1,1),(1,2,2),(2,1,2),(2,2,1),(2,2,2) $

### Sample Explanation 2

入力される値が大きくなることもあります。

## 样例 #1

### 输入

```
2 5```

### 输出

```
1 2 2```

## 样例 #2

### 输入

```
1000000 1000000000000000000```

### 输出

```
1000000 1000000 1000000```

## 样例 #3

### 输入

```
9 47```

### 输出

```
3 1 4```

# 题解

## 作者：QianRan_GG (赞：8)

首先申明：本题解参考了 @symbolce 的[这篇题解](https://www.luogu.com.cn/blog/K-Y/solution-at-abc200-e)的思路，写本篇题解的目的就是为了让你们更好地理解那篇题解，所以那篇题解中未讲到的点本篇题解中会有补充。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc200_e)

## 解题思路

### 暴力思路

我们设 $i + j + k$ 的值为 $s$。

因为本题按照 $s$ 为第一关键字，$i$ 为第二关键字，$j$ 为第三关键字排序，所以我们只要列举 $i, j, k$ 的全排列，然后 ```sort``` 一遍，直接找第 $K$ 个就好了。时间复杂度和空间复杂度都是 $\mathcal O(n^3)$。

### 正解

上述暴力的瓶颈在于如何优化排序的时间和存储的空间。

首先易得 $i, j, k$ 不同时 $s$ 可能相同，所以一个 $s$ 对应一段区间，$i, j$ 同理，只有确定 $k$ 后才是唯一的，还有，$s, i, j$ 都确定了，$k$ 就确定了。

我们发现只要先枚举 $s$，在枚举 $i$，最后枚举 $j$，就可以枚举到每一种情况，不用把所有情况存下来了，空间优化完成。

对于时间优化，我们想，$i, j, k, s$ 都是定值，所以我们在枚举 $i$ 时先确定 $s$ 的值，这样就只用枚举一遍 $i$，不用在每个 $s$ 不同时都枚举一遍 $i$。对于 $j$ 的枚举同理，要先确定 $i$ 的值。  
但是要怎么确定 $s$ 和 $i$ 的值呢？

因为 $s$ 为第一关键字，所以 $s$ 小的一定在 $s$ 大的前面。我们枚举 $s$，设现在枚举到了 $x$，只要确定了 $s = x$ 在整个排序中的位置就可以了，而小的 $s$ 确定了，大的 $s$ 的位置就是比他小的所有 $s$ 的区间长度加上它自己的区间长度。所以我们只要知道每个 $s$ 的区间长度就好了。

对于一个 $s$，我们把它看成 $s$ 个 $1$ 相加，利用隔板法，我们用两个隔板将 $s$ 分成 $3$ 部分，分别表示 $i, j, k$。因为有 $s$ 个 $1$，所以有 $s - 1$ 个间隔，所以第一个隔板有 $s - 1$ 个位置。  
因为插入隔板后会减少一个间隔，所以第二个隔板有 $s - 2$ 个位置。  
这时我们注意到：设一隔板位置为 $i$，二隔板位置为 $j$，还有一种情况是一隔板位置为 $j$，二隔板位置为 $i$，这本应属于同一种情况，而我们算了两遍，所以我们再除以 $2$ 就可以了。

隔板法代码：
```cpp
int geban(int x)
{
	if(x <= 2) return 0;
	return (x - 1) * (x - 2) / 2;
}
```

但是我们发现，$i, j, k$ 的取值范围只有 $1 \sim N$，任意一值大于 $N$ 都不能取，此时我们使用容斥原理。

我们已经算出所有方案数（简称原方案），只要减去有**至少**一个值大于 $N$ 的方案数就好了。  
我们又可以把大于 $N$ 的方案分成 $3$ 类：一个值大于 $N$（简称一方案），两个值大于 $N$（简称二方案），三个值大于 $N$（简称三方案）。

我们易知一方案中包含了二方案和三方案，二方案中也包含了三方案，所以我们要求出**原方案，减一方案，加二方案，减三方案的数量**。

对于一方案，我们设 $i$ 大于 $N$，所以我们把一个 $N$ 提出来，再利用隔板法求出方案数，就是 ```geban(s - n)```。  
但是我们发现 $j, k$ 也可以大于 $N$，所以我们把方案数乘三，再用原方案一减，就能消掉一方案数。

对于二方案，我们同样拿出两个 $N$ 来，就是 ```geban(s - n * 2)```。  
然后我们发现两个值大于 $N$ 的种类有 $ij, jk, ik$ 这 $3$ 种。所以我们要加回 $3$ 倍。

对于三方案，同理就是 ```geban(s - n * 3)```。  
而三个值大于 $N$ 的种类都只有 $i, j, k$ 一种，所以我们只用减三方案的一倍就能抵消。

综上：设 $t$ 为合法的所有方案，则 ```t = geban(s) - 3 * geban(s - n) + 3 * geban(s - n * 2) - geban(s - n * 3)```。

所以我们枚举时只要算出每个 $t$，若 $t < K$，则使 $K - t$（因为每次 $t$ 都从 $1$ 开始，用减法利于计算），只要有一次 $t \leq K$，就找到了我们想要的 $s$ 了。

然后我们枚举 $i$，对于每个 $i$，我们可以算出 $j$ 的最大值和最小值。  
因为 $j$ 是每次加 $1$ 的，所以我们可以根据最大最小值算出 $j$ 的个数，也就是当前 $i$ 的区间长度。  
与 $s$ 同理，我们处理 $i$，只要找到第一个 $K < $ 区间长度，就找到了想要的 $i$。

此时我们也不需要枚举 $j$ 了，因为此时 $K$ 为当前的 $i$ 的区间中我们要求的那一个，所以 $j$ 就是 $minj + K$。  
确定了 $j$，我们就确定了整个 $i, j, k$，直接输出就好了。

## 代码

因为是仿照别人的，所以仅供参考。

```cpp
#include <cstdio>
#include <algorithm>

#define int long long

using namespace std;

int geban(int x)
{
	if(x <= 2) return 0;
	return (x - 1) * (x - 2) / 2;
}


signed main()
{
	int n, k;
	scanf("%lld%lld", &n, &k);
	for(int s = 3; s <= n * 3; ++ s)
	{
		int t = geban(s) - 3 * geban(s - n) + 3 * geban(s - n * 2) - geban(s - n * 3);
		if(k > t)
		{
			k -= t;
			continue;
		}
		for(int i = 1; i <= n; ++ i)
		{
			int mij = max(s - i - n, 1ll), maj = min(s - i - 1, n);
			if(mij > maj) continue;
			int num = maj - mij + 1;
			if(k > num)
			{
				k -= num;
				continue;
			}
			int j = mij + k - 1;
			printf("%lld %lld %lld", i, j, s - i - j);
			return 0;
		}
	}
}
```

---

## 作者：Symbolize (赞：7)

# 思路
这题并没有想象中那么复杂，首先，不难想到，我们可以通过枚举 $i+j+k$ 来锁定第 $k$ 个蛋糕所处在的范围，因为 $i+j+k$ 是排序的第一关键字。

锁定范围的具体方法：

首先把 $i+j+k$ 的和 $sum$ 拆分成 $sum$ 个 $1$，那么合为 $sum$ 的三元组的个数（先抛开 $n$ 的限制）就在 $sum$ 个 $1$ 中插入两个隔板，将其分为 $3$ 份的方案数，排列组合即可。

用函数 $get(x)$ 来表示合为 $x$ 的三元组排列个数，代码如下：

```cpp
int get(int x)
{
	if(x<=2) return 0;//若小于2，没有合法方案
	return (x-1)*(x-2)/2;//隔板法的排列组合
}
```

再来考虑 $n$ 的限制，这里可以使用容斥原理，将合为 $sum$ 的三元组分为四部分：没有一个超过 $n$、有且仅有一个超过 $n$、有且仅有两个超过 $n$ 与全部都超过了 $n$。那么首先要在 $get(x)$ 的基础上减去有且仅有一个超过 $n$ 的排列数量，我们可以先取 $n$ 个出来，再进行排列组合，这样求到的就是至少有一个超过 $n$ 的情况。所以减掉 $3$ 倍的 $get(x-n)$，但是减掉过后又把至少有两个超过 $n$ 的情况多减了 $3$ 份，所以再加上 $3$ 倍的 $get(x-2\times n)$，最后，有因为全部超过的被抵消了，所以再减去 $get(x-3\times n)$。

最后的形式就是 `int num=get(s)-3*get(s-n)+3*get(s-2*n)-get(s-3*n);`

紧接着就是在这个范围内找了，我们可以枚举 $i$，因为合一定，所以对于每个 $j$ 都只有一个与其对应的 $k$。所以直接减掉即可。

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=2e5+10;
using namespace std;
int n,k;
int get(int x)//隔板法
{
	if(x<=2) return 0;
	return (x-1)*(x-2)/2;
}
signed main()
{
	cin>>n>>k;
	rep1(s,3,3*n)//合的范围是3~3*n
	{
		int num=get(s)-3*get(s-n)+3*get(s-2*n)-get(s-3*n);
		if(k>num/*还不够*/)
		{
			k-=num;
			continue;
		}
		rep1(i,1,n)
		{
			int Min=max(s-i-n,1ll);//最小的j
			int Max=min(s-i-1,n);//最大的j
			if(Min>Max) continue;
			int sum=Max-Min+1;//有多少个
			if(k>sum/*还不够*/)
			{
				k-=sum;
				continue;
			}
			int j=Min+k-1;
			cout<<i<<' '<<j<<' '<<s-i-j<<endl;//输出
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：i_wzy (赞：6)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc200_e)

---

# 解题思路

首先应该考虑如何计算已知 $i+j+k$ 的和 $s$ 时，如何计算有几个蛋糕。

相当于对 $s$ 个小球中间放入两个隔板分成三部分，这三部分依次是 $i$，$j$，$x$。这样就可以算出来是 $\frac{(s-1)\times (s-2)}{2}$ 。

但是这上面的算法还有**问题**：因为挡板分成三部分是不保证每部分一定**小于等于** $n$ 的。怎么办呢？利用**容斥原理**，假设 $i$ 超过了 $n$，那么相当于一定要给 $i$ 分走 $n$ 个小球，接下来考虑剩余的 $s-n$ 个小球放挡板。$j$，$k$ 同理。这样是减去了至少有一个超过了 $n$ 的。再加上至少有两个超过了 $n$ 的方案再去掉全部都超过了 $n$ 的方案即可。

具体来说，记 $\operatorname{get}(x)=\frac {(x-1) \times (x-2)}{2}$，则和为 $x$ 的方案共有 $\operatorname{get}(x) - 3 \times \operatorname{get}(x-n) + 3 \times \operatorname{get}(x - 2 \times n) - \operatorname{get}(x - 3 \times n)$ 种。

---

有了以上做法后前缀和可以线性处理出和为 $s$ 的蛋糕所在的编号范围。做出这个范围后就可以枚举 $i$，具体地确定在 $i$ 下有多少蛋糕是合法的，线性地求解出 $j$ 和 $k$。

最后附上 AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 3e6 + 10;

int n; ll k, sum[maxn];

ll get(ll x) {
    if(x <= 2) return 0;
    return (x - 1) * (x - 2) / 2;
}

int main() {
    cin >> n >> k;
    for(int i = 1;i <= 3 * n; ++i) {
        sum[i] = get(i) - 3 * get(i - n) + 3 * get(i - 2 * n) - get(i - 3 * n);
        sum[i] += sum[i - 1];
    }
    for(int s = 1;s <= 3 * n; ++s) {
        if(sum[s] >= k) {
            ll ret = sum[s - 1];
            for(int i = max(1, s - 2 * n);i <= n; ++i) {
                int jmin = max(1, s - i - n);
                int jmax = min(n, s - i - 1);
                if(ret + jmax - jmin + 1 >= k) {
                    cout << i << ' ' << jmin + (k - ret - 1) << ' ' << s - i - (jmin + (k - ret - 1)) << '\n';
                    return 0;
                }
                ret += jmax - jmin + 1;
            }
        }
    }

    return 0;
}
```

---

## 作者：ktq_cpp (赞：4)

## [Problem E](https://atcoder.jp/contests/abc200/tasks/abc200_e)

对于这道题目，我们可以先算出第 $k$ 个蛋糕是在和为多少的序列中，然后再算出是在美丽值的值，最后确定美味程度。

我们可以令 $dp[i][j]$ 表示在和为 $i$ 的情况下确定 $j$ 个元素的方案数，不难想出，我们要确定第 $k$ 个蛋糕所在的三元组之和，要找到的就是第一个 $sum$ 使得 $\sum_{i=1}^{sum}dp[i][3]>k$ 第一个数等后面的同理。

这道题目整个的思路都是顺其自然的，写代码时需要注意些细节即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define repe(i,l,r) for(int (i)=l;(i)<=r;(i)++)
#define rep(i,n) for(int (i)=1;(i)<=n;(i)++)
#define FOR(i,r,l) for(int (i)=r;(i)>=l;(i)--)
#define INF 0x3f3f3f
#define pii pair<int,int>
#define mpr make_pair
#define pb push_back
#define ALL(v) (v).begin(),(v).end()
#define rsort(v) sort(ALL(v),greater<int>())
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
using namespace std;
int read(){int sum=0,f=1;char c;c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){sum=(sum<<1)+(sum<<3)+(c-'0');c=getchar();}return sum*f;}
void out(int x){if(x<0){x=-x;putchar('-');}if(x>=10)out(x/10);putchar(x%10+'0');}
template <typename T>void die(T s){cout<<s<<endl;exit(0);}
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
template <typename T>void chkmax(T& a,T b){if(a<b)a=b;return;}
template <typename T>void chkmin(T& a,T b){if(a>b)a=b;return;}
int dp[3000005][4];
int sum[3000005][4];
int n,k,num,fi,se;
signed main(){
	n=read(),k=read();
	rep(i,n)dp[i][1]=1,sum[i][1]=i;
	repe(i,2,2*n){
		dp[i][2]=sum[min(i-1,n)][1]-sum[max(i-n,1ll)-1][1];
		sum[i][2]=sum[i-1][2]+dp[i][2];
	}
	repe(i,3,3*n){
		dp[i][3]=sum[min(i-1,2*n)][2]-sum[max(i-n,2ll)-1][2];
		sum[i][3]=sum[i-1][3]+dp[i][3];
	}
	for(num=3;num<=3*n;num++){
		if(k>dp[num][3])k-=dp[num][3];
		else break;
	}
	for(fi=1;fi<=num-2;fi++){
		if(k>dp[num-fi][2])k-=dp[num-fi][2];
		else break;
	}
	for(se=1;se<=num-1-fi;se++){
		if(num-fi-se>=1&&num-fi-se<=n&&k)--k;
		if(!k)break;
	}
	cout<<fi<<' '<<se<<' '<<num-fi-se<<endl;
	return 0;
}
```

---

## 作者：cdxxx04 (赞：3)

**[题目传送门](https://www.luogu.com.cn/problem/AT_abc200_e)**

---

## 题目思路

### 暴力：
把 $n^3$ 个蛋糕全部生成，然后按照要求排序。

**时间复杂度：$\operatorname{\Theta(n^3)}$**。

### 正解：
因为题目中说蛋糕是在先按照三个属性值的和进行排序的，所以我们可以很容易想到枚举三个属性值的和（$sum$），把它们的方案数加起来，超过 $K$ 时就是答案的属性值的和。那如何求方案数呢？我们可以用容斥原理加隔板法求解：
>如果要把 $sum$ 分成不为 $0$ 的三份，则要在其中插 $2$ 块板，而又有 $sum-1$ 个空位，所以答案有 $\binom{2}{sum-1}$。\
>其中有一些分法是不合理的（$\scriptsize{\text{如当} N=2,sum=5 \text{时分成了} (3,1,1)}$），我们要用[容斥原理](https://baike.baidu.com/item/%E5%AE%B9%E6%96%A5%E5%8E%9F%E7%90%86/10146840?fr=ge_ala)排除掉。这里有三个不合理的集合，关系如下图。
>![](https://s3.bmp.ovh/imgs/2024/10/04/c9c664353750ccb6.png)\
>根据容斥原理的公式（$\scriptsize{\lvert \bigcup^n_{i=1} a_i \rvert= \sum^{n}_{i=1} (-1)^{i-1} \lvert\ \sum_{1\leq b_1 < b_2 < \dots <b_i\leq i} \lvert \bigcap_{j=1}^i a_{b_i} \rvert \ \lvert} $）可以得知这几个集合的总数量为$3\cdot \binom{2}{sum-n}+3\cdot \binom{2}{sum-2n}-\binom{2}{sum-3n}$。
>
>整合得方案数为 $\binom{2}{sum-1}-(\ 3\cdot \binom{2}{sum-n}+3\cdot \binom{2}{sum-2n}-\binom{2}{sum-3n}\ )=\binom{2}{sum-1}-3\cdot \binom{2}{sum-n}-3\cdot \binom{2}{sum-2n}+\binom{2}{sum-3n}$。

这时，我们得知了答案的属性值的和与它在和为 $sum$ 时排在第几。然后我们暴力枚举美丽程度（$first$），把枚举到的美丽程度的方案数加起来，超过排名时就是答案。还是老问题，如何求方案数呢？
>很明显的一条信息是当我们知道了答案的属性值的和以及美丽程度和美味程度（$second$）后，人气（$third$）就是固定的了。所以美味程度的取值范围就是总方案数。\
>因为美味程度的取值范围是 $\max(sum-first-n,1)$ 到 $min(sum-first-1,n)$。所以方案数是 $\max(0,\min(sum-first-1,n)-\max(sum-first-n,1)+1)$。

之后我们直接枚举美味程度，统计合法的数量就可以求出答案。

**时间复杂度：$\operatorname{\Theta(n)}$**。
## 代码

### 暴力：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int x,y,z;
};
node a[10000000];
bool cmp(node x,node y){
	if(x.x+x.y+x.z!=y.x+y.y+y.z)	return x.x+x.y+x.z<y.x+y.y+y.z;
	if(x.x!=y.x)	return x.x<y.x;
	if(x.y!=y.y)	return x.y<y.y;
}
int t=-1,n,k;
signed main(){
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
	cin>>n>>k;	k--;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				a[++t]={i,j,k};
	sort(a,a+n*n*n,cmp);
	cout<<a[k].x<<' '<<a[k].y<<' '<<a[k].z<<'\n';
	return 0;
}
```

### 正解：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define IF_ON_ONLINEOJ true
#define IF_ON_LUOGU false
#define JIAO_HU_TI false
namespace fast{
#if IF_ON_LUOGU == false
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#endif
#if JIAO_HU_TI == false
#define endl '\n'
#endif
#define il inline
#define re register
#define ri register int
#define ll long long
#if IF_ON_ONLINEOJ == true
    static char buf[100000],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
#endif
    il void fast_out(){ios::sync_with_stdio(false);cout.tie(nullptr);}
    il int read(){
    	re int f=1;    re int x(0);    re char c=getchar();
        while(c>'9'||c<'0')	{if(c=='-')f=-f;c=getchar();}
        while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+(c^48),c=getchar();
        x*=f;	return x;
    }
	istream& operator >>(istream& in,string& x){
	char ch=getchar();
	while(ch!=' '&&ch!='\n')	x+=ch,ch=getchar();
	return in;}
	istream& operator >>(istream& in,char& x){x=getchar();return in;}
}
#define int long long
using namespace fast;
int n,k;
il int C2x(int x){return x<3?0:(x-1)*(x-2)/2;}
il int tsumsum(int sum){return C2x(sum)-3*C2x(sum-n)+3*C2x(sum-2*n)-C2x(sum-3*n);}
il int tfirstsumsum(int first,int sum){
	return max(0ll,min(sum-first-1,n)-max(sum-first-n,1ll)+1);
}
signed main(){
	freopen("cake.in","r",stdin);
	freopen("cake.out","w",stdout);
	fast_out();	cin>>n>>k;
	ri sum;	for(sum=3;k>0;sum++)	k-=tsumsum(sum);
	k+=tsumsum(--sum);
	ri first;	for(first=1;k>0;first++)	k-=tfirstsumsum(first,sum);
	k+=tfirstsumsum(--first,sum);	sum-=first;	
	ri second;	for(second=1;k>0;second++)	k-=(sum-second<=n);	second--;
	cout<<first<<' '<<second<<' '<<sum-second<<endl;
	return 0;
}
```

---

## 作者：FreedomKing (赞：2)

[Atcoder Beginning Contest Virtual Participation 计划](https://www.luogu.com.cn/blog/FreedomKing/ABCVP)。

挺妙的容斥做法。

### 思路

一开始读错题想了个假做法，没考虑 $i+j+k$ 和的问题，做法大概类似于对于每个 $(i,j,k)$ 之一直接选最多的，然后跟 $K$ 判。

容斥做法的主要思路很像，考虑枚举 $i+j+k$ 的值，然后利用插板法计算当 $i+j+k=x$ 时最多的方案数：分四种情况讨论，第一种为 $i,j,k$ 均小于等于 $n$，第二种为 $i,j,k$ 中有且仅有一个大于 $n$，第三种为 $i,j,k$ 中有且仅有两个大于 $n$，第四种为 $ij,k$ 均大于 $n$，设 $P(x)$ 为插两个板情况下 $x$ 个元素的方案数，有

$$sum=P(x)-3\times P(\max(0,x-n))+3\times P(\max(0,x-2\times n))-P(\max(0,x-3\times n))$$

$sum$ 即为当 $i+j+k=x$ 时的总方案数，然后我们贪心地让 $K$ 减去这些方案数，直到 $K=0$ 时得到答案。

代码变量名命名有点怪，实在理解不了可以看看，真的很抽象。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,xN=1e7+5,mN=1e4+5,mod=200;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){x/=gcd(x,y);return (x*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abs(int x){return (x>0?x:-x);}
}
int a[N],n,m,t,k,ans;
inline int P(int x){
	return (x<=2?0:((x-1)*(x-2)>>1));
}
signed main(){
	n=qr;k=qr;
	int _3n=3*n;
	for(int i=3;i<=_3n;i++){
		int tmp=P(i)-3*P(i-n)+3*P(i-2*n)-P(i-3*n);//方案总数
		if(k>tmp) k-=tmp;//直接贪心减去
		else{
			for(int j=1;j<=n;j++){//枚举 i
				int minn=max(i-j-n,1ll);//j 的取值下界
				int maxn=min(i-j-1,n);//j 的取值上界
				if(minn>maxn) continue;
				int tmp=maxn-minn+1;//k 的方案数
				if(k>tmp){//如果 K 还有，那还得继续往下找
					k-=tmp;
					continue;
				}
				int _j=minn+k-1;//k 为取值下界加上 K 剩的
				qws(j);qws(_j);qws(i-j-_j);
				return 0;
			}
		}
	}
	return  0;
}
```

---

## 作者：Delete_error (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc200_e)

~~教练讲了写篇题解纪念一下~~

申明：本篇题解优点为详细，且有图解释容斥过程，若觉得自己思维能力较高，可以移步更为简洁的题解，本人写题解经验较少不喜勿喷，有问题可以私信我。

写于：$2024/8/26$

---

# 题目大意
做了一批蛋糕，每块蛋糕都可以对应一个三元组 $(i,j,k)$ ，给定一个 $N$ 与 $K$ ，其中 $1 ≤ i,j,k ≤ N $ ，对这些蛋糕按照下面的顺序进行对比，重新排序，求第 $K$ 个蛋糕的三个参数。

1.   $i+j+k$ 小的蛋糕优先放在左边。
2.  若 $i+j+k$ 相同，$i$ 小的蛋糕优先放在左边。
3.  若 $i$ 也相同，$j$ 小的蛋糕优先放在左边。

- $1 ≤ N ≤ 10^6 $

- $1 ≤ K ≤ N^3$

---

# 正文
为了方便起见，下文 $sum=i+j+k$ 。
## 初步暴力引进
看到三元组与排序想到，我们可以直接枚举出所有合法的三元组，分别按 $sum,i,j$ 为第一，二，三关键字进行排序,由于一共有 $N^3$ 个三元组,然后再排序一遍，所以时间复杂度为 $O(N^3\log N^3)$ 。

## 思考优化推导正解

###  第一部分
思考一下能够发现，暴力中我们做了许多不必要的排序，因为第 $K$ 个蛋糕的 $sum$ 是一定的，所以对于其他 $sum$ 我们不需要将其对应的三元组进行排序。

然后再想到，我们只需对每个 $sum$ 求一下合法的方案数。若 $K$ 大于此方案数，则不为该范围的三元组，减去即可；若小于或等于，就求出第 $K$ 个蛋糕的 $sum$ 了。

对于每个 $i,j,k$ ,相当于将 $sum$ 拆成三个部分，直接考虑插板法求方案。由于 $1 ≤ i,j,k ≤ N $ ，则考虑到需要减去非法状态，容斥一下就好。

##### 插板法部分
这个问题等价于有两块板子插入 $sum$ 中,第一个板子可以插入 $sum-1$ 个空位，第二给板子就只能插 $sum-2$ 个空位，由于两板交换位置为同种方案，最后方案数就为  $(sum-1)\times(sum-2)/2$ 。

##### 容斥部分
这个容斥不复杂，主要是要想清楚非法状态。

大概是这样的图，其中有颜色为非法：

![](https://cdn.luogu.com.cn/upload/image_hosting/k7s47zuq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

总方案先减去红色部分，多减了绿色再加回来，又多加了黄色再减去。

再考虑插板，对于只有一个条件非法，我们提出一个 $N$ 再插板则必定有一个部分加上提出来的部分大于 $N$ ，两个条件则提出两个 $N$ ，三个条件则提出三个 $N$ 。最后对于每个 $sum$ 对应的三元组方案就求完了。

###  第二部分
此时 $K$ 对应的 $sum$ 已知，我们可以枚举 $i$ ，像上面一样再算出方案数，此时 $k=sum-i-j$ 对应 $j$ ,所以方案数也就是 $j$ 的范围，得以解出 $K$ 对应的三元组。


---


## 代码部分

部分细节若没有看懂注释中也有解释。


```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,k,sum;
ll f(ll x){//隔板方案数 
	if(x<=2) return 0;//防负数 
	return (x-1)*(x-2)/2;
}
int main(){
	cin>>n>>k;
	for(ll sum_i=3;sum_i<=3*n;sum_i++){
		ll now=f(sum_i)-3*f(sum_i-n)+3*f(sum_i-2*n)-f(sum_i-3*n);//容斥方案
		if(k>now) k-=now;//找第K个排列的sum为多少 
		else{
			sum=sum_i;
			break;
		}
	}
	//cout<<sum;
	for(ll i=1;i<=n;i++){
		ll minj=max(sum-n-i,1ll),maxj=min(sum-i-1,n);//算合法的j的最值范围
		ll now=maxj-minj+1;//i已知求方案数，i 已知，j 已知，sum 已知则 k为 sum-i-j，所以求j个数即可
		if(now<=0) continue;//无合法方案 
		if(k>now) k-=now;//找第K个排列的i为多少 
		else{//找到i算范围
			ll j=minj+k-1;//求出第K个排列的j为多少 
			cout<<i<<" "<<j<<" "<<sum-i-j; 
			return 0;
		}
	} 
	return 0;
}
```


---

## 后言
还有看讨论区有人问为什么不是 $now≤K$ 而是 $now<K$  因为当两者相等时已经找到了 $sum$ 的范围，不应减去了。

---

## 作者：Mirasycle (赞：1)

第一眼发现答案具有单调性，想的是套几个二分就解决了。写的时候发现如果二分的话 check 函数似乎需要 $O(n)$ 的复杂度，但是 check 函数重复计算了好多。于是考虑线性递推出来再二分查找或者拼凑出了。利用插板法算满足个数即可。逐一确定 $i+j+k$，$i$，$j$ 然后推导出 $k$ 就可以了。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=3e6+10;
long long f[maxn],k;
int n,sum,ansi,ansj,ansk;
long long F(int i){
	if(i<=2) return 0; 
	return (long long)(i-1)*(i-2)/2; 
}
int G(int i){
	if(i>0) return i;
	else return 0;
}
void calc1(){
	f[1]=f[2]=0;
	for(int i=3;i<=3*n;i++) f[i]=f[i-1]+F(i)-3*F(i-n)+3*F(i-2*n)-F(i-3*n);
	sum=lower_bound(f+1,f+1+3*n,k)-f;
	k-=f[sum-1];
}
int calc2(){
	long long cnt=0; int i;
	for(i=1;i+2<=sum&&i<=n;i++){
		int num=sum-i-1;
		cnt+=G(num)-2*G(num-n)+G(num-2*n);
		if(cnt>=k) break;
	}
	int num=sum-i-1;
	cnt-=G(num)-2*G(num-n)+G(num-2*n); k-=cnt;
	return i;
}
int calc3(){
	int b=1;
	while(b+n<sum) b++;
	return b+k-1;
}
int main(){
	cin>>n>>k;
	calc1();
	ansi=calc2(); sum-=ansi;
	ansj=calc3(); ansk=sum-ansj;
	cout<<ansi<<" "<<ansj<<" "<<ansk<<endl;
	return 0;
}
```

---

## 作者：Leaper_lyc (赞：1)

## 题目简意

对于所有的 $1\le i,j,k\le N$ 组成的 $N^3$ 个三元组，按照总和为第一关键字，$i$ 为第二关键字，$j$ 为第三关键字从小到大排序，询问从左到右排在第 $K$ 位的元素的 $i,j,k$ 分别是多少。

$1\le N\le10^6,1\le K\le N^3$。

## 分析

### 暴力

暴力做法就是直接生成这 $N^3$ 个三元组，然后排序。

### 优化

分别考虑每一个关键字。

对于第一个关键字总和，设为 $s$。每个 $s$ 都对应一个区间，这个区间可能很大（换言之 $s$ 增长很快）。不考虑 $i,j,k$ 的范围，根据隔板法，$s$ 对应的三元组组数为 $(s-1)(s-2)\over 2$，记作 $f(s)$，现在规定 $i,j,k \in [1,n]$，所以还要容斥掉至少有一个大于 $n$，至少有两个大于 $n$ 以及三个都大于 $n$ 的情况。

所以 $s$ 对应的组数 $g(x)=f(s)-3f(s-n)+3f(s-2n)-f(s-3n)$。

于是可以枚举每一个 $s$，如果 $K>g(x)$，那么就跳过 $s=x$ 的情况，并且 $K\leftarrow K-g(x)$。否则答案一定满足 $s=x$。

由于 $s$ 增长很快，且 $s\in[3,3n]$ 范围很小。于是第一关键字高效地找到了。

现在考虑第二关键字。那么确定了 $i,j$，也就确定了 $k$。用刚才的跳区间的思想，不难发现，每一个 $i$ 所对应的三元组也组成了区间。$j$ 的最小取值为 $l=\max(s-i-n,1)$，最大值取 $r=\min(s-i-1,n)$，那么 $i$ 对应的区间长度 $len=r-l+1$。

于是可以枚举每一个 $i$，如果 $K>len$，那么就枚举下一个 $i$，并且 $K\leftarrow K-len$。否则答案的 $i$ 就是当前枚举到的 $i$，那么答案的 $j$ 也就是 $i+K-1$ 了。

问题就解决了。

时间复杂度 $O(n)$，很优秀。

## $\tt Code$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, k, N;
inline int f(int x) {
    return x < 3 ? 0 : (x - 1) * (x - 2) / 2ll;
}
signed main() {
	cin >> n >> k;
	N = n * 3;
	for (int sum = 3, t; sum <= N; sum++) {
	    t = f(sum) - 3ll * f(sum - n) + 3ll * f(sum - 2 * n) - f(sum - 3 * n);
	    if (k > t) { k -= t; continue; }
        for (int i = 1, j; i <= n; i++) {
            int l = max(sum - i - n, 1ll), r = min(sum - i - 1, n);
            if (l > r) continue;
            t = r - l + 1;
            if (k > t) { k -= t; continue; }
            j = l + k - 1;
            cout << i << ' ' << j << ' ' << sum - i - j;
            return 0;
        }
    }
}
```

如果您发现这篇题解有误，请私信我，我会及时改正，服务 OIer。如果您觉得这篇题解写得好，请您留下宝贵的赞，让这篇题解在上面，服务更多 OIer。

---

## 作者：_Kenma_ (赞：0)

# AT_abc200_e 解题报告

## 前言

感觉不应该放在 E。有点困难其实。

## 思路分析

这种大范围查找题应该有一个固定的套路：逐个确定。

具体地，可以先计算出 $i+j+k$ 的值，再依次计算出 $i,j,k$ 的值。

### 计算 $i+j+k$

考虑怎样快速计算 $i+j+k$ 的值。

设 $f_d$ 表示满足 $i+j+k=d$ 的三元组 $(i,j,k)$ 的个数。

只要能快速计算 $f$ 的值，就可以在 $O(n)$ 的复杂度内计算出任何一个三元组的 $i+j+k$ 的值。扫一遍 $f$ 就行。

考虑怎样快速计算 $f$。

先不考虑 $i\le n,j\le n,k\le n$ 的限制，用插板法解决，答案显然为$f_d=\binom{d-1}{2}$。

再考虑限制，发现限制可以容斥解决。

具体地：

$$f_d=\binom{d-1}{2}-3 \cdot \binom{d-n-1}{2}+3 \cdot \binom{d-2n-1}{2}-\binom{d-3n-1}{2}$$

解释就是全集 - 有一个超出限制 + 有两个超出限制 - 有三个超出限制。

需要熟练应用插板法。

### 计算 $i,j,k$

仿照上例，可以枚举 $i$，统计合法三元组 $(i,j,k)$ 的个数，这样做也是 $O(n)$ 的。

对于每一个 $i$ 和之前求出的 $sum=i+j+k$，有：

$$j\in [\max(1,sum-1-n),min(n,sum-1-i)]$$

~~都来切蓝了，应该会解不等式组吧。~~

然后对于每一个 $i$，三元组的数量就是合法的 $j$ 的数量，因为 $k$ 此时是唯一确定的。

然后就做完了。

整体复杂度为 $O(n)$。

## 代码实现

注意容斥时出现负数的情况，判掉就行。

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,num,ans_sum,ansi,ansj,ansk; 
int f[3000005];
void get_sum(){
	for(int i=3;i<=3*n;i++){
		if(k>f[i]) k-=f[i];
		else{
			ans_sum=i;
			break;
		}
	}
}
void get_ijk(){
	for(int i=1;i<=ans_sum-2;i++){
		int l=max(1ll,ans_sum-i-n),r=min(n,ans_sum-i-1);
		if(l>r) continue;
		if(k>r-l+1){
			k-=r-l+1;
		}else{
			ansi=i;
			ansj=l+k-1;
			ansk=ans_sum-ansi-ansj;
			break;
		}
	}
}
int c(int x){
	if(x<=2) return 0;
	return (x-1)*(x-2)/2;
}
signed main(){
	cin>>n>>k;
	for(int i=3;i<=3*n;i++){
		f[i]=c(i)-3*c(i-n)+3*c(i-2*n)-3*c(i-3*n);
	}
	get_sum();
	get_ijk();
	cout<<ansi<<' '<<ansj<<' '<<ansk;
	return 0;
}

```

---

## 作者：MMXIandCCXXII (赞：0)

## 题目大意
有 $N^3$ 个三元组 $(i,j,k)$ 且 $1 \leq i,j,k \leq N$，按 $i,j,k$ 的和从小到大排序，和相同时按 $i$ 排序，$i$ 相同时按 $j$ 排序，求排完序后的第 $M$ 个三元组。

## 思路
这道题是容斥原理，我们可以用正难则反的思想，算出当前总和情况下的情况数，减去不符合要求的，就是当前总和的情况数，这一步可以用隔板法。用 $M$ 比较，如果 $M$ 比情况数大，说明总和不足，用 $M$ 减去当前情况数，枚举下一种总和的情况。

如果 $M$，小于了当前总和的情况数，那么枚举 $i$ 的情况，算出当前情况下有多少种情况，如果少了，继续枚举下一种，如何多了，算出 $j$ 和 $k$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int c2(int x)
{
    if (x <= 0) return 0;
    return x  * (x - 1) / 2;
}

signed main()
{
    int n, m;
    cin >> n >> m;
    for (int s = 3; s <= 3 * n; s++)
    {
        int cnt = c2 (s - 1) - 3 * c2 (s - n - 1) + 3 * c2 (s - 2 * n - 1);
        if (m > cnt)
        {
        	m -= cnt;
        	continue;
		}
        for (int i = 1; i <= n; i++)
        {
        	int r=s-i;
            int maxn = min (n, r - 1);
            int minn = max (1ll, r - n);
            if (maxn < minn) continue;
            int k = maxn - minn + 1;
            if (m > k) 
			{
				m -= k;
				continue;
			}
			int j = minn + m - 1;
            cout << i << " " << j << " " << r - j << endl;
            return 0;
        }
    }
    return 0;
}
```

---

