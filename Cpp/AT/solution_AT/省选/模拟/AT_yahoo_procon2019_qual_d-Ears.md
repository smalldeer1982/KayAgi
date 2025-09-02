# Ears

## 题目描述

在一个数轴上，有 $L$ 堆石头，第 $i$ 堆石头的坐标是 $i-0.5$。 刚开始石头堆数为 $0$。

- 你可以从任何地方出发，在任何地方结束移动。（坐标为整数）

- 你每次只能向左或右移动 $1$。

- 你在经过一堆石头时会向其添加一块石头。

- 若坐标为 $x$，那么你必须保证 $0 \leq x \leq L$。

给定 $L,A_1,A_2,A_3,\cdots,A_L$，假设最后第 $i$ 堆石头数量为 $H_i$，求 ：

   $$ \min(\sum_{i=1}^{L} |A_i-H_i| )$$

---

## 说明/提示

- $1 \leqslant L \leqslant 2\times 10^5$

- $0 \leqslant A_i \leqslant 10^9(1 \leqslant i \leqslant L)$

- 输入均为整数

---

$\textsf{Translate by @\color{5EB95E}nr0728}.$

## 样例 #1

### 输入

```
4
1
0
2
3```

### 输出

```
1```

## 样例 #2

### 输入

```
8
2
0
0
2
1
3
4
1```

### 输出

```
3```

## 样例 #3

### 输入

```
7
314159265
358979323
846264338
327950288
419716939
937510582
0```

### 输出

```
1```

# 题解

## 作者：int233 (赞：3)

- $*1998,32\%$ ，本题解中的题目有关概念均源自洛谷上的题面翻译。

- 神秘奇偶性 DP 。

- 令 $a_i$ 表示 $i-0.5$ 坐标上的石头数量。

- 考虑走一个 $l\to r$ 或者 $r\to l$ 的路径 $(0\le l < r\le L)$ 的贡献： $a[l+1\cdots r]$ 均加 $1$ ，如果走 $l\to r\to l$ 那么对 $a[l+1\cdots r]$ 的奇偶性没有贡献。

- 如果咱们顺着讨论 $a_i$ 奇偶性的思路做下去，那么咱们一定要考虑分析 `Snuke` 走的路径对 $a_i$ 奇偶性影响情况的性质。

- 对于数轴/坐标系路径性质分析题，分析时需要用一个 trick （ AT_exawizards2019_f 也要用），就是考虑固定主人公初始的行走方向（比如最开始必须向右），推出性质后类比出主人公初始行走方向是其他方向时的性质。

- 对于这个题，考虑让主人公强制向右走推满足该条件的路径性质，令主人公的初始坐标为 $x$ ，不难发现主人公向右走过一定距离后一定会在一个比 $x$ 位置更靠右的位置 $y$ 向左转或者彻底终止行走，第 $2$ 中情况对 $a$ 中元素奇偶性的影响是显然的，那么 $a$ 的形态必然是一段0+一段奇数+一段0。

- 考虑分析上一段中的第 $1$ 种情况：假设往左走走到 $z$ 时主人公开始向右走或者停止行走。如果停止行走的话，那么 $a$ 的形态必然是一段 0 + 一段奇数 + 一段偶数 + 一段 0 。考虑从 $z$ 开始又开始往右走的情况，若 $z$ 在 $x$ 的右边，那么 $x\to y\to z\to ???$ 的路径对 $a_i$ 奇偶性的影响必然是和 $x\to z\to ???$ 的路径对 $a_i$ 奇偶性的影响等价的，另一种情况也是采用类似的方式进行分析，最终可以得出结论：任何路径内中转点个数 $\ge 3$ 的路径均可与一个中转点个数 $=2$ 的路径对 $a_i$ 的奇偶性的影响等价。

- 因此 $a$ 的形态一定为一段 0 + 一段偶数 + 一段奇数 + 一段偶数 + 一段 0 ，每一段均可以有 $0$ 个数，直接 DP 就好了。

---

## 作者：封禁用户 (赞：2)

分析：

　　转化一下题意，将一段序列分成 $5$ 段，空 偶 奇 偶 空，然后 ```dp``` 一下，$f[i][j]$ 表示到第 $i$ 个数，当前在第 $j$ 段内的最小花费。

　　空段中的花费是数字大小，偶数段中奇数花费 $1$，奇数段中偶数花费 $1$。
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
#include<cctype>
#include<set>
#include<queue>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;

inline int read() {
    int x=0,f=1;char ch=getchar();for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar())x=x*10+ch-'0';return x*f;
}

const int N = 200005;
int a[N];
LL f[N][5];

int main() {
    int n = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 1; i <= n; ++i) {
        f[i][0] = f[i - 1][0];
        for (int j = 1; j <= 4; ++j) f[i][j] = min(f[i - 1][j], f[i][j - 1]);
        f[i][0] += a[i];
        f[i][1] += (a[i] == 0) ? 2 : (a[i] & 1);
        f[i][2] += !(a[i] & 1);
        f[i][3] += (a[i] == 0) ? 2 : (a[i] & 1);
        f[i][4] += a[i];
    }
    LL ans = f[n][0];
    for (int i = 1; i <= 4; ++i) ans = min(ans, f[n][i]);
    cout << ans;
    return 0;
}
```


---

## 作者：hanzhongtlx (赞：2)

 这个题好巨啊 Orz  

我们先来考虑什么时候可以构造出完整的路线。 

一个比较显然的结论是中间不能有 $0$。 

容易猜到和数字奇偶性有关。  

考虑一个偶数，他的性质的从一侧进，从同侧出；奇数相反。  

于是考虑经过偶数的走法  

如果一股劲走完这些，显然不能去另一边了。 

如果走不完，那得保证最左边是偶数，然后才能实现转向回来走完。  

我们发现如果是多个奇偶块交错，那么显然奇数一侧进另一侧出的性质只能用一次，不能支持回来了，所以合法的序列一定是：  

$0$，奇数，偶数，奇数，$0$  

或者是他的子序列。

这里的这些数可能是一段，现在如果你在想 $\mathcal O(n^4)$ dp（谔谔，好像是暴力），那只能像我一样坐以待毙了/kk  

我们设 $dp_{i,j}$ 为到第 $i$ 个点，已经是第 $j$ 段的最小步数，转移就比较显然了。  

```
#include"iostream"
#include"cstdio"
#include"cmath"
using namespace std;

#define read(x) scanf("%lld",&x)
#define int long long
#define MAXN 200005

int n;
int dp[MAXN][6],a[MAXN];

signed main()
{
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=0;i<=4;i++) dp[0][i]=0;
	for(int i=1;i<=n;i++) for(int j=0;j<=4;j++) dp[i][j]=1ll<<62;
	for(int i=1;i<=n;i++)
	{
		if(!a[i])
		{
			dp[i][0]=dp[i-1][0];
			for(int k=0;k<=4;k++) dp[i][4]=min(dp[i][4],dp[i-1][k]);
			for(int k=0;k<=1;k++) dp[i][1]=min(dp[i][1],dp[i-1][k]+2);
			for(int k=0;k<=3;k++) dp[i][3]=min(dp[i][3],dp[i-1][k]+2);
			for(int k=0;k<=2;k++) dp[i][2]=min(dp[i][2],dp[i-1][k]+1);
		}
		else if(a[i]&1)
		{
			dp[i][0]=dp[i-1][0]+a[i];
			for(int k=0;k<=4;k++) dp[i][4]=min(dp[i][4],dp[i-1][k]+a[i]);
			for(int k=0;k<=1;k++) dp[i][1]=min(dp[i][1],dp[i-1][k]+1);
			for(int k=0;k<=3;k++) dp[i][3]=min(dp[i][3],dp[i-1][k]+1);
			for(int k=0;k<=2;k++) dp[i][2]=min(dp[i][2],dp[i-1][k]);
		}
		else
		{
			dp[i][0]=dp[i-1][0]+a[i];
			for(int k=0;k<=4;k++) dp[i][4]=min(dp[i][4],dp[i-1][k]+a[i]);
			for(int k=0;k<=1;k++) dp[i][1]=min(dp[i][1],dp[i-1][k]);
			for(int k=0;k<=3;k++) dp[i][3]=min(dp[i][3],dp[i-1][k]);
			for(int k=0;k<=2;k++) dp[i][2]=min(dp[i][2],dp[i-1][k]+1);
		}
	}
	int ans=1ll<<62;
	for(int i=0;i<=4;i++) ans=min(ans,dp[n][i]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：SamHJD (赞：1)

考虑最终每位上的石子的奇偶性。若有一段子路径从 $s$ 出发，走到 $x$ 后折返回到 $t$，可以发现模 $2$ 下等价于直接从 $s$ 走到 $t$。因此最终的石子数只有起点 $s$ 到终点 $t$ 这段区间中的石子数为奇数，$[s,t]$ 之外也可能被经过，由于经过 $[s,t]$ 之外的路径均由 $[s,t]$ 中出发而回到 $[s,t]$，因此石子数为偶数。故最终 $H_i$ 可被分为空、偶数、奇数、偶数、空五部分，每个部分可以为空。

题目允许在一堆石子上反复横跳，因此奇数部分可以为任意奇数，偶数部分可以为任意非零偶数，设 $f_{i,j}$ 表示第 $i$ 堆石头属于上面的第 $j$ 个部分时 $[1,i]$ 的答案，其中 $j\in\{0,1,2,3,4\}$，有转移：
$$
\begin{cases}
f_{i,0}=f_{i-1,0}+a_i\\
f_{i,1}=\min\{f_{i,0/1}\}+[a_i\equiv1\pmod 2]+2\times[a_i=0]\\
f_{i,2}=\min\{f_{i,0/1/2}\}+[a_i\equiv0\pmod 2]\\
f_{i,3}=\min\{f_{i,0/1/2/3}\}+[a_i\equiv1\pmod 2]+2\times[a_i=0]\\
f_{i,4}=\min\{f_{i,0/1/2/3/4}\}+a_i
\end{cases}
$$
答案即为 $\min\{f_{n,0/1/2/3/4}\}$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,k,n) for(int i=k;i<=n;++i)
#define per(i,n,k) for(int i=n;i>=k;--i)
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c-'0');
	x*=f;
}
const int N=2e5+10;
int n,a[N],sumodd[N],sumeven[N];
int f[N][5];
signed main(){
    read(n);
    rep(i,1,n) read(a[i]);
    rep(i,1,n){
        f[i][0]=f[i-1][0]+a[i];
        f[i][1]=min(f[i-1][1],f[i-1][0])+(a[i]%2)+(a[i]==0?2:0);
        f[i][2]=min({f[i-1][2],f[i-1][0],f[i-1][1]})+1-(a[i]%2);
        f[i][3]=min({f[i-1][3],f[i-1][0],f[i-1][1],f[i-1][2]})+(a[i]%2)+(a[i]==0?2:0);
        f[i][4]=min({f[i-1][4],f[i-1][0],f[i-1][1],f[i-1][2],f[i-1][3]})+a[i];
    }
    printf("%lld\n",min({f[n][0],f[n][1],f[n][2],f[n][3],f[n][4]}));
	return 0;
}
```

---

## 作者：Acheron_RBM (赞：1)

显然，完整的序列中间不可以有空，那么合法的完整序列应该是这样的：空 偶 奇 偶 空。

令 $dp_{i,j}$ 为表示到第 $i$ 个数，当前在第 $j$ 段内的最小花费。

那转移方程就很显然了：空段中的花费是数字大小，偶段中奇数花费 $1$，奇段中偶数花费 $1$。

目标：$\sum_{i=1}^{i \le n} \min(dp_{n,i})$

代码：

```cpp
signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
    for(int i=1;i<=n;i++)
	{
        dp[i][0]=dp[i-1][0];
        for(int j=1;j<=4;j++)
		{
			dp[i][j]=min(dp[i-1][j],dp[i][j-1]);
		}
        dp[i][0]+=a[i];
        if(a[i]==0)
        {
        	dp[i][1]+=2;
		}
		if(a[i]!=0)
		{
			dp[i][1]+=(check(a[i]));
		}
        dp[i][2]+=!(check(a[i]));
        if(a[i]==0)
        {
        	dp[i][3]+=2;
		}
        if(a[i]==0)
		{
			dp[i][3]+=(check(a[i]));
		}
        dp[i][4]+=a[i];
    }
    int ret=LONG_LONG_MAX;
    for(int i=1;i<=4;i++)
	{
		ret=min(ret,dp[n][i]);
	}
    cout<<ret;
    return 0;
}
```

---

