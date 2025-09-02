# Yet Another Subarray Problem

## 题目描述

给定一个数组 $a_1, a_2, \dots, a_n$ 和两个整数 $m$ 与 $k$。

你可以选择数组的某个子数组 $a_l, a_{l+1}, \dots, a_{r-1}, a_r$。

该子数组的代价定义为 $ \sum\limits_{i=l}^{r} a_i - k \lceil \frac{r - l + 1}{m} \rceil $，其中 $\lceil x \rceil$ 表示大于等于 $x$ 的最小整数。

空子数组的代价为 $0$。

例如，若 $m = 3$，$k = 10$，$a = [2, -4, 15, -3, 4, 8, 3]$，则部分子数组的代价如下：

- $a_3 \dots a_3: 15 - k \lceil \frac{1}{3} \rceil = 15 - 10 = 5$；
- $a_3 \dots a_4: (15 - 3) - k \lceil \frac{2}{3} \rceil = 12 - 10 = 2$；
- $a_3 \dots a_5: (15 - 3 + 4) - k \lceil \frac{3}{3} \rceil = 16 - 10 = 6$；
- $a_3 \dots a_6: (15 - 3 + 4 + 8) - k \lceil \frac{4}{3} \rceil = 24 - 20 = 4$；
- $a_3 \dots a_7: (15 - 3 + 4 + 8 + 3) - k \lceil \frac{5}{3} \rceil = 27 - 20 = 7$。

你的任务是求出数组 $a$ 的某个（可能为空）子数组的最大代价。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 3 10
2 -4 15 -3 4 8 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 2 1000
-13 -4 -9 -20 -11
```

### 输出

```
0
```

# 题解

## 作者：橙子汁 (赞：10)

### 前言  
这好像是个比较快的做法  
(又好像是一个会被hack的做法  
但它确实是严格O(nm)的昂  
推了半天，推出来了  
调了半天，调出来了  
原来是初始化的锅啊  

------
### 比赛历程
当很多大佬都做出来时，我其实还挺着急的(还在调C)  
调完C马上去看D，在某些巨佬的翻一下顺利的理解了题意  
然而，由于我太菜了，半点思路都莫得QAQ  
抓瞎中，突然出现一只口胡巨佬  
(突然给我发口胡弄得我一脸懵逼  
![](https://cdn.luogu.com.cn/upload/pic/65357.png)   
但是，我并不理解(ta讲的挺好的，但我脑子不好使)  
只知道复杂度应该是O(nm)的  
只是觉得 i%m 是个十分有用的信息就往这方面想了  

------
咳咳咳，下面引入正题
### 思路
这是一个比较灵异的思路(不知道为什么用这个形容词QAQ)  
~~应该是贪心吧~~  
巨佬都用 分治/DP 什么的，慌的鸭批  
讲讲这个神奇的思路:(我觉得我讲不懂qwq  
因为是
$\sum\limits_{i=l}^r a_i-k\lceil \frac{r-l+1}{m}\rceil$  
其中$\lceil \frac{r-l+1}{m}\rceil$提醒我们可以将n分成m个一组m个一组  
(重点)于是乎我就想到弄一个长度为m的数组记录一扫到过的i%m的前缀和最大值，   
从后往前扫每次找出数组0~m-1前缀和减去当前位置的前缀和，统计最大的即使答案(更新)   
不难得到，做完一次i%m到下一个数值相同的i'%m之前上一个数值相同的i''%m肯定过时了(即绝对超过m，区间长度多了1~m)需要多减去一个k    
所以，每次更新完ans要记得将i%m更新一下，在 原来i%m的位置的数减k 与 当前前缀和 中取个较大的数  

举个例子吧(手写的，希望看得懂，字丑勿嫌):
![](https://cdn.luogu.com.cn/upload/pic/65367.png)

------
### 注意事项
1. 开long long不开pretest都过不去  
2. 初始化: 数组和中间一定要记得清为-$\infty$,ans初始化为0(因为要最大，ans最小为0)  
3. 什么时候要-k，推清楚(建议有兴趣的人自行去推一推)

------  
### 代码  
如下便是蒟蒻改了半天的比赛代码  
具体还是理解代码的(有点难讲QAQ)
```cpp
#include<bits/stdc++.h>
#define N 300005
#define ll long long
using namespace std;
ll n, m, k;
ll ans = 0, a[N], dt[15], sum[N];

inline ll read() {
	ll red = 0, f_f = 1; char ch = getchar();
	while(ch>'9'||ch<'0') {if(ch == '-') f_f = -1; ch = getchar();}
	while(ch>='0'&&ch<='9') red = red * 10+ch-'0', ch = getchar();
	return red * f_f;
}

int main() {
	memset(dt, 192, sizeof(dt));
	n = read(), m = read(), k = read();
	for(int i = 1; i <= n; i++) a[i] = read(), sum[i] = sum[i-1] + a[i];
	for(int i = n; i >= 0; i--) {
		ll nw = dt[10];
		for(int j = 0; j < m; j++) nw = max(nw, dt[j]);
		ans = max(ans, nw-sum[i]-k);
		dt[i%m] = max(dt[i%m]-k, sum[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
```
------ 
### 关于Hack 
由于和别的神仙方法不一样  
赛后特别担心被hack，但是和他们对拍并没有发现任何毛病  
(据了解好多人都被叉了，是惨案没错了)  
如有叉点欢迎hack

------
By 蒟蒻橙子汁 (打本场CF号:Orange_JuiCE)

---

## 作者：Aria_Math (赞：6)

感觉大家的实现都有些繁琐了。

考虑从左到右枚举右端点 $r$，维护每个左端点 $l$ 的答案。

当右端点 $r$ 加 $1$ 时：

- 所有 $l$ 处的答案加上 $a_r$。
- 当且仅当 $l \equiv r \pmod m$ 时，$\lceil \frac{r-l+1}{m} \rceil$ 的值会加 $1$。

那么把所有数分成 $m$ 组，把 $l$ 分到第 $l \bmod m$ 个组中，维护每个组的最大值。每次把所有组的最大值加上 $a_r$，单独把第 $r \bmod m$ 个组减去 $k$ 即可。易于 $\mathcal{O(nm)}$ 实现，如果 $m$ 很大的话也可以 $\mathcal{O(n \log n)}$ 做到。

#### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 3e5 + 10;
int n, m, k; ll sum[10];
int main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	ll ans = 0;
	for(int i = 0; i < m; ++i) sum[i] = -1e18;
	for(int i = 1; i <= n; ++i) {
		int x; scanf("%d", &x);
		for(int j = 0; j < m; ++j) sum[j] += x;
		sum[i % m] = max(sum[i % m], 1ll * x) - k;
		for(int j = 0; j < m; ++j) ans = max(ans, sum[j]);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：gary2005 (赞：5)

DP 

dp[i][j]表示以第i个结尾拿了的个数%m=j

一般情况下dp[i][j]=dp[i-1][j-1]+a[i]

特殊情况 m=1时 就从前到后扫一下~~没什么好说的~~

当j=1时 就应该是dp[i][j]=dp[i-1][0]-**k**+a[i]

当j==0时 dp[i][j]=max(dp[i-1][m-1]+a[i],0)

这样就非常简单了！

```cpp
//核心代码
rb(i,1,n){
		rb(j,0,m-1){
			if(i<j) break;
			if(j==1){
				dp[i][j]=dp[i-1][0]-k+a[i];
			}
			else{
				if(j==0){
					dp[i][j]=max(dp[i-1][m-1]+a[i],0);
				} 
				else
				dp[i][j]=dp[i-1][j-1]+a[i];
			}
			max_cost=max(max_cost,dp[i][j]);
		}
	}
```


---

## 作者：redegg (赞：3)

这题的突破口在如何利用好$m\le10$上。

可以想到，我们如果单纯地用前缀和暴力枚举，复杂度是$n^2$的。

那么我们想一下，如果$m=1$，该怎么做呢？

很明显，只要前面的$sum>0$就加上（$sum+=a[i]$），否则新开一档（$sum=a[i]$），复杂度为$n$，同时，每一格都要减去$k$。

如果$m=2$呢？我们把情况分成两种，一种是我选取区间的右端点$i$满足$i\%2=1$，还有一种则是$i\%2=0$。

为什么要这么分？因为我们需要进行分块，我们单独处理这两种情况。第一种情况下我们把分块的区间列出来$[1,1][2,3][4,5]...$，第二种则是$[1,2][3,4][5,6]...$，我们可以发现，因为第一种的区间右端点满足$i%2=1$，左端点$j$，假设右端点在第$id_i$块分块，左端点在$id_j$块分块，那么我们答案需要的代价就是$(id_i-id_j+1)\times k$，也就是说，右端点与左端点之间（包括左右）的总块数就是文中说的向上取整的答案也就是$[\frac{r-l+1}{m}]\times k$。

那么我们均摊一下，给每个块的值都整体减去$k$，处理出分块的里面的值的总和$sum_i$和最大值$maxn_i$和分块的最大后缀值$r_i$。

转移就是$maxn_i=max(maxn_{i-1}+sum_i,r_i)$。

因为对于$m=2$的情况有两种分块方式，所以我们需要做两次，但是每次的复杂度都是$O(n)$，总体就是$O(2\times n)$。

那么对于$10\ge m$的所有情况来说，我们同样只是有了$m$种分块方式而已，那么最大复杂度$O(10\times n)$

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int n,k,m;
long long a[300005];
long long sum[300005];
long long r[300005];
long long ans;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    for(int f=1;f<=m;f++)
    {
        long long maxn=0;
        for(int i=f;i>=1;i--)
        {
            sum[1]+=a[i];
            r[1]=max(sum[1],r[1]);
 
        }
        r[1]-=k;
        sum[1]-=k;
        for(int K=1;K<=(n-f)/m;K++)
        {
            for(int i=K*m+f;i>(K-1)*m+f;i--)
            {
                sum[K+1]+=a[i];
                r[K+1]=max(sum[K+1],r[K+1]);
            }
            sum[K+1]-=k;
            r[K+1]-=k;
        }
        for(int i=1;i<=(n-f)/m+1;i++)
        {
            maxn=max(maxn+sum[i],r[i]);
            ans=max(maxn,ans);
            sum[i]=0;
            r[i]=0;
        }
    }
    printf("%lld\n",ans);
}

```


---

## 作者：abc1856896 (赞：2)

# Solution

注意到 $m \le 10$，考虑分块。

对块长对 $m$ 取模分类，维护每个组的最大值。每次把每组的最大值加上 $a_r$，单独把第 $r \bmod m$ 组 $-k$ 即可。时间复杂度 $O(nm)$，可以通过。

---

## 作者：Heartlessly (赞：2)

## Description

给定长度为 $n$ 的数组 $\{a\}$ 和 $m,k$，定义子区间 $[l,r]$ 的价值为 $\sum\limits_{i = l}^{r}a_i - k\left \lceil \frac{r-l+1}{m} \right \rceil$，空区间的价值为 $0$，求所有子区间的价值最大是多少。

$(1 \leq n \leq 3 \times 10^5,1 \leq m \leq 10,1 \leq k \leq 10^9,-10^9 \leq a_i \leq 10^9)$

## Solution

很容易发现一个性质：若我们所选子区间的左端点为 $l$，则可以把 $a_l,a_{l + m},a_{l + 2m},\ldots$ 的值全部减去 $k$，因为每当选到这些数时 $\left \lceil \frac{r-l+1}{m} \right \rceil$ 的值会增加 $1$（总和减去 $1$ 个 $k$）。而 $m$ 的数据范围很小，我们不妨枚举 $x = [0,m)$，对于 $1 \sim n$ 中的某个数 $i$，如果 $i \bmod m$ 的值为 $x$，就把 $a_i$ 减去 $k$ 。接着枚举左端点 $l =x + ym\ (y \in {\rm Z})$，计算左端点在该位置上的最大价值，判断能否更新答案即可。怎么求最大价值呢？我们只需要维护前缀和 $pre_i = \sum\limits_{j=1}^i a_j$ 以及后缀 $\max$ 值 $maxn_i = \max\limits_{j = i}^n pre_j$，最大价值即为 $maxn_l - pre_{l - 1}$ 。时间复杂度为 $O(nm)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
 
template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}
 
template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}
 
const int MAXN = 3e5;
const LL INF = 1e16;
int n, m, k, a[MAXN + 5];
LL ans, pre[MAXN + 5], maxn[MAXN + 5];
 
inline LL solve(int x) {
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i];//预处理前缀和 
        if (i % m == x) pre[i] -= k;//从第 x 个数开始，每隔 m 个数就要减去 k 
    }
    for (int i = n; i; --i) maxn[i] = max(maxn[i + 1], pre[i]);
    //预处理后缀 max 值 
    LL res = 0;
    for (int i = x; i <= n; i += m) {//枚举左端点 
        if (!i) continue;//l = 0 时不合法，跳过
        res = max(res, maxn[i] - pre[i - 1]);//求最大值 
    }
    return res;
}
 
int main() {
    read(n), read(m), read(k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    maxn[n + 1] = -INF;//可能有负数，所以要初始化为 -∞
    for (int i = 0; i < m; ++i) ans = max(ans, solve(i));
    write(ans);
    putchar('\n');
    return 0;
}
```



---

## 作者：xiazha (赞：1)

非常简单题。

定义 $dp_{i,j}$ 为选到第 $i$ 个数，目前选的序列长度对 $m$ 取模为 $j$ 的最大值。

进行小分讨，

- $j=0$，对于这种情况，则有可能再重新从 $i$ 开始选，也有可能继承上一个添到区间中，所以 $dp_{i,j}=\max(dp_{i-1,m-1}+a_i,0)$。

- $j\ge 2$，必须将目前数加入区间，否则不满足定义，$dp_{i,j}=dp_{i-1,j-1}+a_i$。

- $j=1$，思路大致与 $j\ge 2$ 相同，但是考虑到这相当于新开了一块，将题目的式子拆开，你会发现这里要减一个 $k$，所以 $dp_{i,j}=dp_{i-1,j-1}+a_i-k$。

~~然后我就这么高高兴兴地交上去了。~~

你会发现这样不对，为什么呢？

考虑 $m=1$，这个 $dp$ 会出错，这时你只需要跑个最大字段和的板子，顺手把 $a_i=a_i-k$ 就行了。

---

## 作者：shao0320 (赞：0)

观察到 $m \leq 10$ ，考虑按段长对 $m$ 取余分类，每一类做最大子段和，当且仅当新添一个项后段的长度对 $m$ 取余为 $1$ 时（若 $m$ 为 $1$ 则是对所有长度）， $\lceil \frac{len}{m} \rceil$ 的值才会有变化，因此我们每次在这个位置减去 $k$  即可。

code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
#define N 300005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f;
}
int n,m,k,a[N],f[15],g[15];
signed main()
{
    #ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    n=read();m=read();k=read();
    for(int i=1;i<=n;i++)a[i]=read();
    int ans=0;
    for(int j=1;j<m;j++)f[j]=-1e15;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<m;j++)g[(j+1)%m]=f[j%m]+a[i];
        g[1%m]=max(g[1%m],a[i]);
        g[1%m]-=k;
        for(int j=0;j<m;j++)f[j]=g[j];
        for(int j=0;j<m;j++)ans=max(ans,f[j]);
    }
    printf("%lld\n",ans);
}

```

---

## 作者：orson111 (赞：0)

## 前言
真水！

[Codeforces 原题链接](https://codeforces.com/problemset/problem/1197/D)
## 正片开始
一看题目发现 $m \le 10$，太好了！根据我多年的在刷题经验~~虽说刷的是 Atcoder~~，这里我们应该利用除以 $m$ 向上取整的性质，分开处理 $l \mod m$ 不同的 $l$。

我们首先把 $s_r-s_{l-1}-k\lceil \frac{r-l+1}{m}\rceil$ 分一下组，变成 $(s_r-k\lceil\frac{r-l+1}{m}\rceil)-s_{l-1}$，前面部分一起算。

怎么算呢？我们求一个 $mx$ 数组，$mx_i=\max_{j=i}^{i+m-1}s_j$，那么显而易见~~才怪~~对于一个固定的 $l$，$\max_{r=l}^{n}(s_r-k\lceil\frac{r-l+1}{m}\rceil)=\max_{i=0}^{\lfloor\frac{n-l}{m}\rfloor}(mx_{l+im}-(i-1)k)$

等号后面的东西可以增量式优化计算，所以。。。

![](https://cdn.luogu.com.cn/upload/image_hosting/hwf5jjcj.png)

## 上代码！
直接复制会受到评测机的惩罚！
```cpp
#include<bit/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=3e5+9;
ll n,m,k,a[N],s[N],x[N],ans,mx;
int mian(){
    cin>>n>>m>>k;
    for(ll i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];
    if(n<m){
        for(ll i=1;i<=n;i++)
            for(ll j=i;j<=n;j++)
                ans=max(ans,s[j]-s[i-1]-k*((j-i+m)/m));
        cout<<ans<<endl;
        return 0;
    }
    memset(x,0xcf,sizeof(x));
    for(ll i=1;i<=n;i++)
        for(ll j=i;j<=i+m-1&&j<=n;j++)
            x[i]=max(x[i],s[j]);
    for(ll i=0;i<m;i++){
        mx=x[0];
        ll j=n;
        while(j%m!=i) j--;
        for(;j>=1;j-=m){
            mx=max(mx,x[j]);
            mx-=k;
            ans=max(ans,mx-s[j-1]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1197D)

先做前缀和。

设左右端点为 $l,r$，考虑答案式子 $s_r-s_l-k\lceil\frac{r-l}{m}\rceil$，尝试把它拆开成 $s_r-s_l-k\lfloor\frac{r}{m}\rfloor+k\lfloor\frac{l}{m}\rfloor-k[r\bmod m>l\bmod m]$。

若 $r=i$，则

维护 $m$ 个最小值 $p_1,p_2,\dots p_m$。具体地，$p_t$ 表示对于所有 $l\bmod m=t,l<r$，$s_l-k\lfloor\frac{l}{m}\rfloor$ 的最小值。

* 当 $r\bmod m\le t$，答案为 $s_r-k\lfloor\frac{r}{m}\rfloor-p_t$。
* 当 $r\bmod m>t$，答案为 $s_r-k\lfloor\frac{r}{m}\rfloor-p_t-k$。

模拟取最大值即可，复杂度 $\Theta(nm)$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m,k;
long long ans,a[N],p[10];
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]),a[i]+=a[i-1];
    for(int i=0;i<10;i++)p[i]=1e18;
    for(int i=0;i<=n;i++){
        int w=i%m;
        for(int j=w;j<m;j++)ans=max(ans,a[i]-1ll*i/m*k-p[j]);
        for(int j=0;j<w;j++)ans=max(ans,a[i]-1ll*i/m*k-p[j]-k);
        p[w]=min(p[w],a[i]-1ll*i/m*k);
        // for(int j=0;j<10;j++)printf("%d ",p[j]);puts("");
    }
    printf("%lld\n",ans);
    return 0;
}
```

[record](https://www.luogu.com.cn/record/140394986)

---

