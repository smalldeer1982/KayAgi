# Colored Balls

## 题目描述

There are balls of $ n $ different colors; the number of balls of the $ i $ -th color is $ a_i $ .

The balls can be combined into groups. Each group should contain at most $ 2 $ balls, and no more than $ 1 $ ball of each color.

Consider all $ 2^n $ sets of colors. For a set of colors, let's denote its value as the minimum number of groups the balls of those colors can be distributed into. For example, if there are three colors with $ 3 $ , $ 1 $ and $ 7 $ balls respectively, they can be combined into $ 7 $ groups (and not less than $ 7 $ ), so the value of that set of colors is $ 7 $ .

Your task is to calculate the sum of values over all $ 2^n $ possible sets of colors. Since the answer may be too large, print it modulo $ 998\,244\,353 $ .

## 说明/提示

Consider the first example. There are $ 8 $ sets of colors:

- for the empty set, its value is $ 0 $ ;
- for the set $ \{1\} $ , its value is $ 1 $ ;
- for the set $ \{2\} $ , its value is $ 1 $ ;
- for the set $ \{3\} $ , its value is $ 2 $ ;
- for the set $ \{1,2\} $ , its value is $ 1 $ ;
- for the set $ \{1,3\} $ , its value is $ 2 $ ;
- for the set $ \{2,3\} $ , its value is $ 2 $ ;
- for the set $ \{1,2,3\} $ , its value is $ 2 $ .

So, the sum of values over all $ 2^n $ sets of colors is $ 11 $ .

## 样例 #1

### 输入

```
3
1 1 2```

### 输出

```
11```

## 样例 #2

### 输入

```
1
5```

### 输出

```
5```

## 样例 #3

### 输入

```
4
1 3 3 7```

### 输出

```
76```

# 题解

## 作者：Zelotz (赞：15)

考虑枚举选出来颜色的数量最大值 $a_i$，可以发现若已经选出来的集合中，$\sum a_j \le a_i$，则当前集合的答案是 $a_i$，否则是 $\lceil \dfrac{(\sum a_j) + a_i}{2} \rceil$。排序后记背包，$f_k$ 表示前面 $i-1$ 种颜色的数量和为 $k$ 的方案数即可。

```
const int N = 5005, M = 5000, P = 998244353;
int n, a[N], f[N] = {1}, ans;
signed main() 
{
    cin >> n; R(i, 1, n) cin >> a[i]; sort(a + 1, a + n + 1);
    R(i, 1, n)
    {
        R(j, 0, a[i]) (ans += 1ll * f[j] * a[i] % P) %= P;
        R(j, a[i] + 1, M) (ans += 1ll * f[j] * ((j + a[i] + 1) / 2) % P) %= P;
        for (int j = M; j >= a[i]; --j) (f[j] += f[j - a[i]]) %= P;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Shunpower (赞：11)

赛时脑子抽筋没调出来……

## Statement

有 $n$ 种颜色的小球，第 $i$ 种颜色有 $a_i$ 个。你可以把选择两个不同颜色的小球捆成一组，或者把一个小球单独成一组。对于一个颜色集，取出这些颜色的所有小球，这个颜色集的值就是这些小球的最少分组数。

你需要求出 $n$ 种颜色的每一个子集的值。

$1\leq n,a_i\leq 5000$。特别地，$1\leq \sum a_i\leq 5000$。

## Solution

注意到将不同颜色的捆成一组这个操作非常像摩尔投票，所以我们直接考虑主元素，也就是球数量最多的颜色。下面我们认为主元素是出现次数**严格大于**集合大小一半的元素。

### 不存在主元素

设颜色集中颜色的小球总数是 $s$。特别地，如果 $s$ 是奇数，先扔掉小球数最多那种颜色的一个小球（必然不可能配完而扔掉它最优）把 $s$ 变成偶数。

考虑答案下界 $l=\frac{s}{2}$。

如果我们可以把这些小球分成长为 $l$ 的两段，并且每一段的同个位置上的小球颜色都不相同，那就取到了答案下界。考虑我们把每种颜色按照球数从多到少地往段里面塞，塞完第一段塞第二段。那么违背要求当且仅当某种颜色在第一段末尾没能塞完，塞到第二段开头结果重叠了，然而此时这个颜色的出现次数一定 $>\frac{s}{2}$，说明存在主元素，不符合预设条件。

所以我们证明了在不存在主元素的情况下，颜色集能取到它的答案下界，也说明了在 $s$ 为奇数的情况下丢掉小球数最多颜色的一个小球是最优的（丢了之后还是没有主元素，答案还可以取到下界）。综上，此类情况对总答案的贡献为 $\left\lfloor\frac{s+1}{2}\right\rfloor$。

### 存在主元素

此时我们可以把所有非主元素的颜色都去和主元素的颜色配完，然后主元素颜色里面可能还会剩一些小球，这些小球就只能一个一组。很容易可以发现这个分组方案是最优的。

考虑此时的组数。还是设颜色集中颜色的小球总数是 $s$，再设主元素颜色的小球数是 $m$，那么组数就是：

$$
s-m+m-(s-m)=m
$$

amazing 啊！也就是说这种情况对总答案的贡献就是主元素颜色的小球数。

那么整个做法就呼之欲出了。我们考虑把 $a$ 从小到大排序，显然随便编号颜色而不影响答案，所以我们让排序后的 $a$ 中第 $i$ 位表示颜色 $i$ 的小球存在 $a_i$ 个。

然后枚举颜色 $i$，钦定 $i$ 在颜色集中且是球数最多的颜色，也就是只考虑 $[1,i]$ 这些颜色加入颜色集且 $i$ 必须加入。则两种情况的贡献：

1. 对于所有总球数 $s\geq 2\times a_i$ 的情况，说明不存在主元素，于是每种情况贡献 $\left\lfloor\frac{s+1}{2}\right\rfloor$。
2. 对于所有总球数 $s< 2\times a_i$ 的情况，说明存在主元素，于是每种情况贡献 $a_i$。

显然这样统计是不重不漏的。下面考虑怎么数。

### 对于存在主元素

我们只需要数出来有多少种情况，直接用情况数乘 $a_i$ 就完事了。

设计一个背包。$g_{i,j}$ 表示前 $i$ 项总球数为 $j$ 的取颜色方案数，那么转移显然：

$$
g_{i,j+a_i}\gets g_{i-1,j}
$$

那么 $i$ 对总答案的贡献就是 $\sum\limits_{j=0}^{a_i-1} g_{i-1,j}\times a_i$，这里选择 $g_{i-1}$ 来统计答案的原因是钦定了必须选择颜色 $i$，但 $g_i$ 里面同时包括了选择与不选择两种可能，所以要选择用 $g_{i-1}$ 统计答案并改变枚举下标的范围。

### 对于不存在主元素

设计一个背包。$f_{i,j}$ 表示前 $i$ 项，选出的颜色集的总球数为 $j$ 个时所有的取颜色情况的 $\left\lfloor\frac{j+1}{2}\right\rfloor$ 的和。

容易通过分类讨论 $a_i,j$ 的奇偶性并使用 $g$ 辅助转移。

$$
f_{i,j+a_i}=\begin{cases}
f_{i-1,j}+g_{i-1,j}\times \left\lfloor\frac{a_i+[j \text{ is odd}]}{2}\right\rfloor,&a_i\text{ is odd}\\
f_{i-1,j}+g_{i-1,j}\times \left\lfloor\frac{a_i}{2}\right\rfloor,&a_i\text{ is even}\\
\end{cases}
$$

转移中的 $[]$ 是艾佛森括号。

那么 $i$ 对总答案的贡献就是 $\sum\limits_{j=2\times a_i}^{\infty} (f_{i,j}-f_{i-1,j})$。这里做减法的原因是钦定了必须选择颜色 $i$，从 $[1,i]$ 的所有情况里扣除 $[1,i-1]$ 的所有情况才能剩下一定选择了颜色 $i$ 的情况。

然后就做完了，想清楚了才好写。注意 $f$ 数组第二维要开到 $10^4$，因为下标要使用到 $2\times a_i$。

## Code

```cpp
const ll mod=998244353;
int n;
int a[N];
ll dp[2][N<<1];
ll cnt[2][N<<1];
ll tmp[N<<1];
ll tmp2[N<<1];
ll ans=0;
int main(){
#ifdef Griffin
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n;
    fr1(i,1,n) cin>>a[i];
    sort(a+1,a+n+1);
    dp[0][0]=1;
    int op=1;
    fr1(i,1,n){
        fr1(j,0,10000) tmp[j]=dp[op^1][j];
        fr1(j,0,10000){
            int x=j+a[i];
            (tmp[x]+=dp[op^1][j])%=mod;
        }
        fr1(j,0,10000) dp[op][j]=tmp[j];
        fr1(j,0,10000) tmp[j]=cnt[op^1][j]*(!(j&1)),tmp2[j]=cnt[op^1][j]*(j&1);
        fr1(j,0,10000){
            int x=j+a[i];
            if(a[i]&1){
                if(j&1) (tmp[x]+=cnt[op^1][j]+1ll*dp[op^1][j]*(a[i]/2)%mod)%=mod;
                else (tmp2[x]+=cnt[op^1][j]+1ll*dp[op^1][j]*((a[i]+1)/2)%mod)%=mod;
            }
            else{
                if(j&1) (tmp2[x]+=cnt[op^1][j]+1ll*dp[op^1][j]*(a[i]/2)%mod)%=mod;
                else (tmp[x]+=cnt[op^1][j]+1ll*dp[op^1][j]*(a[i]/2)%mod)%=mod;
            }
        }
        fr1(j,0,10000) cnt[op][j]=tmp[j]*(!(j&1)),cnt[op][j]+=tmp2[j]*(j&1);
        fr1(j,a[i]*2,10000) (ans+=(cnt[op][j]-cnt[op^1][j])%mod)%=mod;
        fr1(j,0,a[i]-1) (ans+=1ll*dp[op^1][j]*a[i]%mod)%=mod;
        op^=1;
    }
    cout<<ans<<'\n';
    ET;
}
```

---

## 作者：UniGravity (赞：4)

## Solution CF1954D Colored Balls
### 题意简述
你有 $n$ 种颜色的球，颜色 $i$ 有 $a_i$ 个。

定义放球的代价为将所有球放进袋子里的最少需要袋子数量。每个袋子最多放 $2$ 个球，同时每个球的颜色需要不同。

现在你要求出对于所有可能的 $2^n$ 个颜色集合 $S$，只将颜色在 $S$ 内的球放入的代价之和。

------------

### 思路
不考虑颜色的限制，假设有 $sum$ 个球，显然需要 $\lceil\frac{sum}{2}\rceil$ 个袋子。

对于颜色的限制，我们发现代价只与**出现最多的相同颜色球的数量**有关。令其为 $cnt$，答案即为 $\max(\lceil\frac{sum}{2}\rceil,cnt)$

------------

考虑 dp，设 $f_{i,j,k}$ 表示选到第 $i$ 种颜色，$j$ 个球，出现最多的球的数量为 $k$ 的代价总和。

发现可以对 $a_i$ 排序，把 $k$ 这一位省略掉。重新定义 $f_{i,j}$ 表示第 $i$ 个颜色，$j$ 个球，**且选中了当前颜色**的代价总和。此时 $k$ 就是 $a_i$。

那么 dp 式子就能很快写出：
$$f_{i,j}=\sum_{k=0}^{i-1}f_{k,j-a_i}$$

这玩意是个前缀和的形式，直接优化即可。

------------

### 代码
```cpp
#include <bits/stdc++.h>
#define rnt register long long
#define int long long
#define for1(i, a, b) for (rnt i = a; i <= b; i++)
using namespace std;

const int P = 998244353;

int n, a[5005], cnt[5005];
int f[5005][5005]; // get j in i
int sum[5005][5005]; // sum[i][j] of f[0~i][j]

inline void upd(rnt &x, rnt y) {x = (x + y) % P;}

signed main() {
    scanf("%lld", &n);
    for1(i, 1, n) scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1);
    memset(f, 0, sizeof(f));
    f[0][0] = sum[0][0] = 1;
    for1(i, 1, n) {
        for1(k, 0, 5000) {
            if (k >= a[i]) upd(f[i][k], sum[i - 1][k - a[i]]);
            sum[i][k] = sum[i - 1][k] + f[i][k];
        }
    }
    int ans = 0;
    for1(i, 1, n) {
        for1(k, 1, 5000) {
            upd(ans, f[i][k] * max((k - 1) / 2 + 1, a[i]));
            //if (f[i][k]) printf("%lld %lld: %lld\n", i, k, f[i][k]);
        }
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：___Furina___ (赞：3)

### 题意简述：
无。

但是有个重点（在输入格式里）：所有球的数量和**小于等于** $5000$ 。
### 题解：
解法一：暴力枚举每一个是否被选中，时间爆炸！

解法二（正解）：

考虑 dp，我们记录一个数组 $p$，来维护当所有选取方案中球的数量总和为 $sum$ 时的方案数。

再考虑枚举两维，第一维枚举球 $i$，第二维枚举球的数量的总和 $j$，假设 $i$ 球出现的数量为 $a_i$，考虑以下两种情况：
- 如果 $j\le a_i$，即原有球的总和小于等于这种球的数量，仔细思考，可以发现需要分成 $a_i$ 组。
- 否则，可以分成 $\lceil\frac {a_i+j}{2}\rceil$ 组（可以自己推导一下为什么）。

那么 dp 方程很好想到：
```cpp
if(j+x<=M)p[j+x]=(p[j+x]+p[j])%mod;
```
我们只要倒序枚举（因为这是一个类似于普通背包问题的动态规划），并且统计答案就好了。

注意：
- 记得取模；
- 也需要开 longlong？
### 代码如下：
```cpp
#include<bits/stdc++.h>
#define N 5010
#define M 5000
#define mod 998244353//取模
#define I_love_Furina return //发电+放抄袭
#define forever 0
#define int long long
using namespace std;
int n,ans,a[N],p[N];//如题解
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);//排序一下
	p[0]=1;//初始赋值
	for(int i=1;i<=n;i++){
		int x=a[i],fl=x%2;
		for(int j=M;j>=x+1;j--){//倒续
			ans=(((j+x)/2+(j+x)%2)*p[j]%mod+ans)%mod;//统计答案，第二情况
			if(j+x<=M)p[j+x]=(p[j+x]+p[j])%mod;//状态转移
		}
		for(int j=x;j>=0;j--){//倒序
			ans=(p[j]*x%mod+ans)%mod;//统计答案，第一情况
			if(j+x<=M)p[j+x]=(p[j+x]+p[j])%mod;//状态转移
		}
	}
	cout<<ans;
	I_love_Furina forever;//完结撒花
}
```

---

## 作者：__Floze3__ (赞：2)

## 思路简介

对于一组可能的小球组合，设数量和为 $sum$，最大值为 $a$，那么能分成的最小组数即为 $\min(a, \lceil \frac{sum}{2}\rceil)$。观察到 $sum$ 的值不会大于 $5000$，我们可以用一个 $cnt$ 数组记录每一种数量和的出现次数，将数量从小到大排序后一边通过遍历 $cnt$ 数组分情况来统计答案，一边更新 $cnt$ 数组即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define read std::cin
#define write std::cout
typedef long long ll;

const int N = 5005;
const int mod = 998244353;

int n, a[N];
ll dp[N], res;

int main() {
    std::ios::sync_with_stdio(false);
    read.tie(0), write.tie(0);
    read >> n;
    for (int i = 1; i <= n; ++i) read >> a[i];
    std::sort(a + 1, a + 1 + n);
    dp[0] = 1ll; // 0 的出现次数为 1
    for (int i = 1; i <= n; ++i) {
        for (int j = 5000; j >= a[i] + 1; --j) {
            // 每一组对答案的贡献为 (j + a[i] + 1) / 2
            res = (res + (j + a[i] + 1) / 2 * dp[j] % mod) % mod;
            if (j + a[i] <= 5000) dp[j + a[i]] = (dp[j + a[i]] + dp[j]) % mod; // 更新 cnt 数组
        }
        for (int j = a[i]; j >= 0; --j) {
            // 每一组对答案的贡献为 a[i]
            res = (res + dp[j] * a[i] % mod) % mod;
            if (j + a[i] <= 5000) dp[j + a[i]] = (dp[j + a[i]] + dp[j]) % mod;
        }
    }
    write << res;
    return 0;
}
```

---

## 作者：kimidonatsu (赞：1)

读懂题意花了不少时间，建议结合样例解释食用。

定义“主颜色”为出现次数 **大于** 所有颜色出现次数之和一半的颜色。

显然有解：设球总数有 $s$ 个，那么集合的数量就是 $\lceil \dfrac{s}{2} \rceil$。非常明显，当有一种颜色的球多于 $\lceil \dfrac{s}{2} \rceil$ 的时候其值为这种颜色的球数。

**答案取决于是否有一种颜色的球的数量比其他所有球的总和还多。**

那么就出现了新的做法，遍历集合中球的总数 $x$，在每个颜色子集中增加 $\lceil \dfrac{x}{2} \rceil$ 个球。通过背包可以简单地求出子集数量。

但是对于上述定义的“主颜色”子集需要多加注意，设“主颜色”为 $i$，其他所有颜色之和为 $j$，由定义有 $a_i \gt j$。对于每个包含有 $j$ 个球的颜色子集，答案再加上 $a_i - \lceil \dfrac{a_i + j}{2} \rceil$ 以补偿新做法中添加上的错值 $- \lceil \dfrac{a_i + j}{2} \rceil$，再跑 DP 即可。

注意到如果只考虑 $a_i \gt j$，就不必考虑“主颜色”已经包含在子集中的可能性。

[Submission](https://codeforces.com/contest/1954/submission/257963174)

---

## 作者：lfxxx (赞：1)

又是结论题做不出，我是小丑。

假设没有不同颜色不能一组的限制，答案就是数量除以 $2$ 上取整。

假设颜色最多的数量为 $x$ 那么答案就要和 $x$ 取 $\max$。

为什么呢？

注意到假若 $x$ 比数量除以 $2$ 上取整大，那么 $x$ 所代表的颜色就是绝对众数，显然绝对众数只有一个，因此不同的数就要放到不同组，自然至少要这么多组，剩下的其他颜色一次放进去即可。

假若 $x$ 比数量除以 $2$ 要小，那么直接从大到小摩尔投票就可以消除到答案下界。

将 $a_i$ 从小往大排序并在必选 $a_i$ 处计算方案数贡献即可设计出两维 dp 也就是 $f_{i,j}$ 表示考虑前 $i$ 个球选了 $j$ 个且第 $i$ 个必选的方案数，转移过程中再开一个 $dp_{i,j}$ 表示考虑前 $i$ 个球选了 $j$ 个的方案数辅助转移即可。

复杂度 $O(n \times V + n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
const int maxn = 5001;
int dp[maxn],f[maxn];
int a[maxn],n,ans;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    dp[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<maxn;j++) f[j]=0;
        for(int j=0;j<maxn-a[i];j++){
            f[j+a[i]]=(f[j+a[i]]+dp[j])%mod;
        }
        for(int j=0;j<maxn;j++){
            ans=(ans+max((j+1)/2,a[i])*f[j]%mod)%mod;
            dp[j]=(dp[j]+f[j])%mod;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：ifffer_2137 (赞：1)

### 题意
有 $n$ 种球，每种 $a_i$ 个。定义一个子集的权值为满足 **每组球个数 $\leq2$ 且每组球中种类互不相同** 的最小分组数量，求 $n$ 种球的 $2^n$ 个子集的权值之和。
### 分析
有一个显然的结论，对于一个子集 $S$，其贡献等于
$$\max\{\lceil \frac{\sum_{i\in S}a_i}2 \rceil ,\max_{i\in S}a_i\}$$
感性理解一下就好了，应该是比较一眼的，因为 $a_i$ 个同色球至少要放进 $a_i$ 个组里，而正常情况下两个一组拼起来就好了，取个较大值。

然后就简单了，数据范围较小，直接暴力DP求出总和为 $i$ 的子集数量 $f_i$，总和除以二取上整的贡献先加起来，再考虑存在一个种球数量非常多的情况，看代码好理解。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=5e3+5;
const int mod=998244353;
int n,m;
int ans;
int a[maxn],f[maxn];
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		m+=a[i];
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=m;j>=a[i];j--){
			f[j]=(f[j]+f[j-a[i]])%mod;
		}
	}
	for(int i=1;i<=m;i++){
		ans=(ans+(i+1)/2*f[i]%mod)%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<a[i];j++){
			ans=(ans+(a[i]-(a[i]+j+1)/2)*f[j]%mod)%mod;
		}
	}
	cout<<(ans+mod)%mod<<endl;
	return 0;
}
```

---

## 作者：Moeebius (赞：1)

根据 [POI 2015 LOG](https://www.luogu.com.cn/problem/P3586) 的经典结论：

对于一个序列 $\{a\}$，其最多分成的组数为 $(\sum a_i)-s$，其中 $s$ 为满足 $\sum{\min(a_i,s)} \ge 2s$ 的最大整数。

将 $a$ 从小到大排序，令 $a$ 中所有数的和为 $W$，最大数为 $x$，非严格次大数为 $y$（如果 $a$ 中仅有一个数，则令 $y=0$）。

容易发现 $s\ge y$。接下来简单讨论：

- 如果 $s \le x$，则有 $W-x+s \ge 2s$，解得 $s\le W-x$。
- 否则，有 $W \ge 2s$，即 $s \le \lfloor \dfrac{W}{2} \rfloor$。

综上可知，如果 $2x \ge W$，最多的组数就是 $x$，否则是 $\lceil \dfrac{W}{2} \rceil$。

数数的话跑个背包就行了，对原数组排个序，转移时在最后一个数处更新答案。

```cpp
read(n);
For(i, 1, n) read(a[i]);
sort(a + 1, a + 1 + n);
f[0][0] = 1;
a[n + 1] = 5001;
ll ans = 0;
For(i, 1, n) {
  copy(f[i - 1], f[i - 1] + 5001, f[i]);
  For(j, 0, 5000) if (j + a[i] <= 5000) {
    (f[i][j + a[i]] += f[i - 1][j]) %= mod;
    if (a[i] >= j)
      (ans += f[i - 1][j] * a[i]) %= mod;
    else
      (ans += f[i - 1][j] * ((j + a[i] + 1) / 2)) %= mod;
  }
}
cout << ans << '\n';
```

---

## 作者：Silvestorm (赞：0)

### 题目大意

有 $n$ 种不同颜色的球，第 $i$ 种颜色的球的数量是 $a_i$。

球可以被组合成组。每个组最多包含 $2$ 个球，且每种颜色的球不能超过 $1$ 个。

考虑所有 $2^n$ 种颜色集合。对于一个颜色集合，我们将其权值定义为这些颜色的球可以分布到的最少组数。例如，如果有 $3$ 种颜色，分别有 $3$、$1$ 和 $7$ 个球，它们可以组合成至少 $7$ 个组，所以那个颜色集合的权值是 $7$。

你的任务是计算所有 $2^n$ 种可能的颜色集合的权值的总和。由于答案可能非常大，所以结果需要 $998244353$ 取模后再输出。

小球的总数不超过 $5000$。

### 题目类型

排序，dp。

### 解题思路

对于一个集合，它的权值考虑两个因素：集合里的小球数量总数除以 $2$ 和最多相同颜色的小球数，哪个多哪个就是权值。

如果往某个集合加一种小球，但数量小于等于集合最大值，那么其权值就不好计算。为了方便计算，我们就保证每次添加的小球数总是最多的。

因此先进行升序排序，之后做一个简单的背包即可。

赛时代码有点唐，将就看一下吧。

### code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, k, tem, num[1000300], arr[1001000], dp[1100000], mod = 998244353;
ll ans;
void solve()
{
	ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> num[i];
	sort(num + 1, num + n + 1);
	dp[0] = 1;
	for (ll i = 1; i <= n; i++)
	{
		for (ll j = 5000; j >= 0; j--)
		{
			if (dp[j] > 0)
				arr[j + num[i]] = max(arr[j + num[i]], num[i]);
			tem = max(arr[j + num[i]], (j + 1 + num[i]) / 2);
			ans += tem * dp[j];
			ans = ans % mod;
			dp[j + num[i]] += dp[j];
			dp[j + num[i]] = dp[j + num[i]] % mod;
		}
	}
	ans = ans % mod;
	cout << ans << '\n';
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：0)

## 思路

所求权值就是，出现次数最大的数的出现次数，如果超过总数的一半，那么权值就是这个最大的出现次数；否则，权值就是总数除以 $2$ 上取整。

两种情况分开做。

背包求出 $f[i]$ 表示总数为 $i$ 的方案数。

枚举哪个数字出现的最多，再枚举其他数字出现次数之和，统计第一种情况。由于其他出现次数小于这个最多的次数，直接使用 $f[i]$ 就是对的，不需要特殊处理。

去除第一种情况的方案数，剩下直接统计第二种情况。

## code

```cpp
#include<stdio.h>
#define N 5009
#define mod 998244353
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,a[N],f[N],g[N],ans;
main()
{
	read(n);for(int i=1;i<=n;read(a[i++]));
	f[0]=1;
	for(int i=1;i<=n;++i)for(int j=N-1;j>=a[i];--j)
		f[j]+=f[j-a[i]]-mod,f[j]>>31&&(f[j]+=mod);
	for(int i=1;i<=n;++i)for(int j=0;j<a[i];++j)
		ans=(ans+(long long)(a[i])*f[j])%mod,
		g[a[i]+j]+=f[j]-mod,g[a[i]+j]>>31&&(g[a[i]+j]+=mod);
	for(int i=0;i<N;++i)ans=(ans+(long long)(i+1>>1)*(f[i]-g[i]+mod))%mod;
	printf("%d",ans);
}
```

---

