# Couple Cover

## 题目描述

Couple Cover, a wildly popular luck-based game, is about to begin! Two players must work together to construct a rectangle. A bag with $ n $ balls, each with an integer written on it, is placed on the table. The first player reaches in and grabs a ball randomly (all balls have equal probability of being chosen) — the number written on this ball is the rectangle's width in meters. This ball is not returned to the bag, and the second player reaches into the bag and grabs another ball — the number written on this ball is the rectangle's height in meters. If the area of the rectangle is greater than or equal some threshold $ p $ square meters, the players win. Otherwise, they lose.

The organizers of the game are trying to select an appropriate value for $ p $ so that the probability of a couple winning is not too high and not too low, but they are slow at counting, so they have hired you to answer some questions for them. You are given a list of the numbers written on the balls, the organizers would like to know how many winning pairs of balls exist for different values of $ p $ . Note that two pairs are different if either the first or the second ball is different between the two in pair, and two different balls with the same number are considered different.

## 样例 #1

### 输入

```
5
4 2 6 1 3
4
1 3 5 8
```

### 输出

```
20
18
14
10
```

## 样例 #2

### 输入

```
2
5 6
2
30 31
```

### 输出

```
2
0
```

# 题解

## 作者：世末OIer (赞：2)

题目大意:

有n个数:a[1]....a[n]

有m个询问:

每一次有一个数p

问你有对少对(a[i],a[j] (i!=j))使得a[i]*a[j]>p

n,m $\le 10^6$ a[i]$\le 3*10^6$

题解:

dp。

先预处理出每一个数的个数(因为才$10^6$种数)。

然后dp

dp[i]表示a[i]*b[j]=i的个数。

我们可以先累加

ans[i]=ans[i-1]+dp[i]

再输出n*(n-1)-ans[p-1]即可。

```cpp

#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
#define ll long long
#define mp make_pair
using namespace std;
ll cnt[3000006],ans[3000006],n,m;
int main(){
	int i,j,x;
	scanf("%d",&n);
	for(i=1;i<=n;++i) scanf("%I64d",&x),++cnt[x];
	for(i=1;i<3000001;++i) if(cnt[i]) for(j=i;j<3000001;j+=i) ans[j]+=cnt[i]*(cnt[j/i]-(i==j/i));
	for(i=1;i<=3000000;++i) ans[i]+=ans[i-1];
	scanf("%d",&m);
	for(i=1;i<=m;++i) scanf("%d",&x),printf("%I64d\n",n*(n-1)-ans[x-1]);
	return 0;
}

```

---

## 作者：skyskyCCC (赞：0)

## 前言。
暴力卡常题。
## 分析。
取到球不放回，那么就是组合计数了。显然我们如果每次都进行直接暴力横扫，对于每个数进行统计，然后乘起来，加起来，输出答案。那么时间复杂度极高，但是我们发现这道题的 $p$ 给到了 $3\times10^6$ 不算太大，而且给了我们 $3$ 秒的时间，所以我们可以优化暴力。我们采用类似前缀和的思路，我们预处理出来所以的组合，然后每次询问中直接暴力乘起来输出即可。

预处理我们可以采用两种思路。一种是预处理当前序列中不大于当前值的数对有多少，然后用总数减去它的前一个数据所对应的组合数就是答案。另一种比较直接。我们统计每个数出现了几次，因为 $a_i$ 最大就是 $3\times10^6$ 所以如果一旦比它还大了，直接终止查询即可。这样可以统计出数对的个数，再做一个累加，然后就可以预处理出乘积小于等于某个 $a_i$ 的数对有多少个。此时的答案就是总数减去乘积小于 $p$ 的数量。

注意因为 $i$ 和 $j$ 可能很大，所以对于这种暴力要注意数据范围。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m,a;
long long t[3000005],c[3000005];
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
int main(){
    while(~scanf("%d",&n)){
        memset(t,0,sizeof(t));
        memset(c,0,sizeof(c));
        for(int i=0;i<n;i++){
            read(a);
            t[a]++;
        }
        for(int i=1;i<=3e6;i++){
            for(int j=1;j<=3e6;j++){
                if((long long)i*j>(long long)3e6){
                    break;
                }
                if(i==j){
                    c[i*j]-=t[i];
                }
                c[i*j]+=t[i]*t[j];
            }
        }
        for(int i=1;i<=3e6;i++){
            c[i]+=c[i-1];
        }
        read(m);
        while(m--){
            read(a);
            write((long long)(n-1)*n-c[a-1]);
            printf("\n");
        }
    }
    return 0;
}
```
## 后记。
最大的点跑了 $1.39$ 秒，所以可以证明这是一个正确解法。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_edge_ (赞：0)

来看这篇题解之前，请思考一下，如果 $a_i \le 10^3$ 怎么做。

这个子问题对整一个问题的解决有着至关重要的作用，如果缩成这样，那么就可以直接枚举值域，然后后缀和一下询问。

然而，这题的 $a_i$ 并不是这样，这个时候，我们发现这个询问的 $p_i$ 非常非常小，至少相较于 $a_i^2$ 来说是这样的。

于是我们也可以尝试枚举值域，但是发现这个 TLE 很严重。

一条有用的性质就是对于 $x \times y > 3 \times 10^6$，那么如果 $z>y$ 必然有 $x \times z > 3 \times 10^6$，因为询问的最大值只到 $3 \times 10^6$ 因此，我们可以把大于它的值都看成和它一样，这里只需要统计大于某个数的数量即可。

那如果不大于它的呢？那就暴力做，这样的话是调和级数也就是 $O(n \log n)$ 的复杂度。

注意这里要特别判断两个球相等的情况。

另外，本题卡常严重，请注意使用 fread，快读快写。

```cpp
#include <iostream>
#include <cstdio>
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define int long long 
using namespace std;
const int INF=3e6+5;
int n,a[INF],b[INF],f[INF],m,bb[INF];
signed main()
{
//	ios::sync_with_stdio(false);
	n=read();
	for (int i=1;i<=n;i++) 
		a[i]=read(),b[a[i]]++;
	int N=3e6;
	for (int i=N;i>=1;i--) bb[i]=bb[i+1]+b[i];
	for (int i=1;i<=N;i++) {
		for (int j=1;j<=N/i;j++) {
			int fl=(i==j);
			f[i*j]+=b[i]*(b[j]-fl);
		}
		// N~N/i+1
		f[N]+=b[i]*bb[N/i+1];
		if (i>=N/i+1) f[N]-=b[i]*b[i],f[N]+=b[i]*(b[i]-1);
	}
	for (int i=N;i>=1;i--) f[i]+=f[i+1];
	m=read();
	for (int i=1;i<=m;i++) {
		int x=0;x=read();
		cout<<f[x]<<"\n";
	}
	return 0;
}
```


---

## 作者：RainFestival (赞：0)

我们先统计每一种球的数量 $c_i$。

把 $a_i\times a_j\ge p$ 转化为 $a_i\times a_j\le p-1$。

这个时候，我们发现，我们要求的就是
$n\times (n-1)-\sum\limits_{i=1}^{p}\sum\limits_{j=1}^{\frac{p-1}{i}}a_ia_j$

现在这个是 $\mathcal{O(nm)}$ 的。

我们考虑 $s_n=\sum\limits_{d|n}a_da_\frac{n}{d}$。

只要求出 $s$ 就可以了。

然后通过枚举倍数求出 $s$。

代码：

```cpp
#include<cstdio>
int n,q;
long long f[3000005],p[3000005],s[3000005];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&f[i]),p[f[i]]++;
	for (int i=1;i<=3000000;i++)
	    for (int j=i;j<=3000000/i;j++)
			s[i*j]=s[i*j]+(i==j?p[i]*(p[i]-1):2*p[i]*p[j]);
	for (int i=1;i<=3000000;i++) s[i]=s[i-1]+s[i];
	scanf("%d",&q);
	while (q--)
	{
		int x;
		scanf("%d",&x);
		printf("%lld\n",1ll*n*(n-1)-s[x-1]);
	}
}
```

---

