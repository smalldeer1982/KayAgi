# 「RdOI R3」学习算法

## 题目背景

暑假中，MLE 决定学习一下 OI 算法。


## 题目描述

暑假一共有 $n$ 天，我们假设 MLE 每天都有足够的时间学 OI。MLE 列出了可供选择的 $m$ 个算法。MLE 每天只能且必须学习一个算法。

而且，MLE 长时间学同一种算法会厌倦，所以每一种算法不能连续学习太多天，第 $i$ 种算法最多可以连续学习 $a_i$ 天。**MLE 没有必要学习全部的算法。**

MLE 想知道，自己有多少种不同的学习安排来度过这 $n$ 天。两种学习安排不同仅当这两种安排中有至少一天学习的算法不同。因为方法可能过多，你只需要输出方案数对 $10^9+7$ 取模即可。

## 说明/提示

### 样例解释

#### 样例 \#1

第一种算法最多连续学习一天，第二种最多连续学习两天。故共有如下四种学习方式：

- $1,2,2$。
- $2,1,2$。
- $2,2,1$。
- $1,2,1$。

#### 样例 \#2

由于唯一的一种算法最多只能连续学习一天，所以没有合法的方案可以度过 $2$ 天。

---

### 数据范围

**本题采用捆绑测试，若无特殊说明，测试点的内存限制为 256MB。**

对于所有数据，$1\le a_i \le n\le 7 \times 10^3$，$1\le m \le 7\times 10^3$。

| subtask | 分值 | $n,m\le$ | 特殊限制            |
| ------- | ---- | -------- | ------------------- |
| $1$     | $5$  | $5$      | 无                 |
| $2$     | $10$ | $100$    | 无                 |
| $3$     | $15$ | $500$    | 无                 |
| $4$     | $20$ | $7\times 10^3$   | $a_i=1$             |
| $5$     | $20$ | $7\times 10^3$   | 内存限制为 $500$ MB |
| $6$     | $30$ | $7\times 10^3$   | 无                 |

## 样例 #1

### 输入

```
3 2
1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
2 1
1```

### 输出

```
0```

## 样例 #3

### 输入

```
8 5
4 2 3 4 2```

### 输出

```
356314```

# 题解

## 作者：SfumatoCannon_ (赞：23)

### 0.吐槽

赛事想出来的做法，当时觉得这题挺简单的（倒是代码实现上调了好久）

比完赛一看题解，？？怎么个个都这么复杂，又是压维又是滚动数组的（甚至让我一度怀疑数据过水）

下面，我就介绍一种做法，理解起来很自然，优化起来也很容易。

### 1.题意解释

有一个长度为 $n$ 的序列，其中包含的数字范围为从 $1$ 到 $m$.

规定数字 $i$ 最多只能连续出现 $a_i$ 次。

求满足上述要求的序列一共有多少中，答案对 $10^9+7$ 取模。

### 2.解题思路

我们发现，这道题目的核心在于 “规定数字 $i$ 最多只能连续出现 $a_i$ 次” 这个限制条件。

我们不妨思考一下：如果我们按照线性动态规划的方式，一个一个地往表格里填数字，当我填到第 $i$ 个数字的时候，和它关系最大的是什么？没错，是第 $i-1$ 个数字。

如果第 $i-1$ 个数字和第 $i$ 个数字不一样的话，那么第 $i$ 个数字填下去，一定是合法的。

否则呢？设当时填的数字为 $j$ ，如果第 $i-1$ 个数字和第 $i$ 个数字是一样的，且 $a_j> i-1$ 的话，我们仍然可以放心大胆地填下去，因为填下去之后，连续出现的数字是不可能超过 $a_j$ 个的（因为本身就只有 $a_j$ 个数字啊）。

那么，如果第 $i-1$ 个数字和第 $i$ 个数字是一样的，且 $a_j\leq i-1$ 的时候呢？那么在前面 $i-1$ 个数字构成的组合里，就不可避免地会出现一种情况，它由**恰好** $a_j$ 个 $j$ 结尾，当且仅当这种情况时，第 $i$ 个数字不能填成 $j$.那么，我们怎么计算这种非法情况的方案数呢？

我们知道，在这种情况下，我们要填的数是第 $i$ 个数，而且从第 $i-a_j$ 个数到第 $i-1$ 个数全部都是 $j$. 那么问题来了：第 $i-a_j-1$ 个数是几呢？没错，只要不是 $j$ 就行了！

而且我们还可以知道，这种情况下，第 $i-a_j$ 个数到第 $i-1$ 个数全都是固定死的，真正对非法方案数产生贡献的，只有前面的 $i-a_j-1$ 个数。**也就是说，“填到第 $i-a_j-1$ 个数且不是以 $j$ 结尾” 的方案数总和，等于 “填到第 $i-1$ 个数，且从 $i-a_j$ 到 $i-1$ 全部都是 $j$ 的方案数”**。好好思考一下上面这句话！

所以，第 $i-1$ 个数字等于第 $i$ 个数字时的合法方案总数 

$=$ (前面 $i-1$ 个数字构成的合法方案总数) $-$ (从 $i-a_j$ 到 $i-1$ 全部都是 $j$ 的方案数)

$=$ (前面 $i-1$ 个数字构成的合法方案总数) $-$ (前面 $i-a_j-1$ 个数字构成的不是以 $j$ 结尾的方案数总和).

现在我们知道了第 $i-1$ 个数字不等于第 $i$ 个数字时的合法方案总数，也知道了他们相等时的合法方案总数，那么把它们加起来，就知道了我们要求的方案数。

想到了以上这些，状态转移式子就很好推了。我们设 $dp[i][j]$ 表示当前填到第 $i$ 个数，且结尾数字是 $j$ 的合法方案总数，那么必然有：

$$dp[i][j]=\sum_{k=1,k\not=j}^{m}dp[i-1][k]+(dp[i-1][j]-\sum_{k=1,k\not=j}^{m}dp[i-a[j]-1][k])$$

$$=\sum_{k=1}^{m}dp[i-1][k]-\sum_{k=1,k\not=j}^{m}dp[i-a[j]-1][k].$$

这种做法是 $O(n^3)$ 的，拿不到满分，但我们可以很容易观察出，式子里面的 $\sum_{k=1}^{m}$ 是可以预处理出来的。

设 $sum[i]=\sum\limits_{k=1}^{m}dp[i][k]$ ,于是式子转化为：

$$dp[i][j]=sum[i-1]-(sum[i-a[j]-1]-dp[i-a[j]-1][j]).$$

转化成了 $O(n^2)$ 的，于是这道题就可做了。

至于滚动数组什么的？不需要！只要不用 ```long long``` 就可以卡过去。

另外在代码实现上，我们还需要注意之前说过的 $a_j>i-1$ 的情况，并予以特判。

还有一个地方需要特判：那就是当 $m=1$ 且唯一的 $a[1]<n$ 的时候，这种情况下是不可能填完的，应输出```0```。（对于其余的情况，可以证明是肯定存在解的，```12121212...```地填即可）

***

### 3.Code

```cpp
#include <cstdio>
typedef long long ll;
#define MODNUM 1000000007
#define MAXN 7001
ll n, m;
unsigned int dp[MAXN][MAXN];
ll sum[MAXN];
ll a[MAXN];
int main()
{
    ll i, j, k;
    scanf("%lld%lld", &n, &m);
    for (i = 1; i <= m; i++)
        scanf("%lld", &a[i]);
    if (m == 1 && a[1] < n)
    {
        printf("0");
        return 0;
    }
    for (i = 1; i <= m; i++)
        dp[1][i] = 1;
    sum[1] = m;
    for (i = 2; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            dp[i][j] = sum[i - 1];
            if (i > a[j])
            {
                if (i == a[j] + 1)
                    dp[i][j] = (dp[i][j] - 1 + MODNUM) % MODNUM;
                else
                    dp[i][j] = (dp[i][j] - (sum[i - a[j] - 1] - dp[i - a[j] - 1][j]) + MODNUM) % MODNUM;
            }
        }
        for (j = 1; j <= m; j++)
            sum[i] = (sum[i] + dp[i][j]) % MODNUM;
    }
    printf("%lld", sum[n]);
    return 0;
}
```


---

## 作者：yzy1 (赞：16)

## Subtask 2

朴素 DP，设 $f(i,j,k)$ 为第 $i$ 天，最后学的是第 $j$ 种算法，连续学了 $k$ 天。
$$
\begin{aligned}
f(i,c,1)&=\sum_{j\in\complement_{[1,m]}\{i\}} \sum_{k=1}^{a_j} f(i-1,j,k)\\
f(i,c,k)&=f(i-1,c,k-1)\\
\end{aligned}
$$

时空复杂度 $O(n^2m^2),O(n^2m)$。

```cpp
re(i, m) f[1][i][1] = 1;
rep(i, 2, n) {
  re(c, m) {
    re(j, m) {
      if (j == c) continue;
      re(k, a[j]) f[i][c][1] += f[i - 1][j][k], umod(f[i][c][1]);
    }
    rep(k, 2, a[c]) f[i][c][k] = f[i - 1][c][k - 1];
  }
}
re(i, n) { re(j, a[i]) ans += f[n][i][j], umod(ans); }
```

## Subtask 3

试着把第三维压掉：
$$
f(i,c)=\sum_{j\in\complement_{[1,m]}\{i\}} \sum_{k=\max\{1,i-a_j\}}^{i-1} f(k,j)
$$

时空复杂度 $O(n^2m^2),O(nm)$。

```cpp
re(i, m) f[1][i] = 1;
rep(i, 2, n) {
  re(c, m) {
    re(j, m) {
      if (j == c) continue;
      rep(k, max(1, i - a[j]), i - 1) f[i][c] += f[k][j], umod(f[i][c]);
    }
  }
}
re(i, m) {
  rep(j, n - a[i] + 1, n) { ans += f[j][i], umod(ans); }
}
```

再加一个用来辅助 $f$ 的 $g$：
$$
\begin{aligned}
g(i,c)&=\sum_{j=\max\{1,i-a_c\}}^{i-1}f(j,c)=g(i-1,c)+f(i-1,c)-f(i-a_c-1,c)\\
f(i,c)&=\sum_{j\in\complement_{[1,m]}\{i\}} g(i,j)
\end{aligned}
$$

时空复杂度 $O(nm^2),O(nm)$。

```cpp
re(i, m) f[1][i] = 1;
rep(i, 2, n + 1) {
  re(c, m) {
    g[i][c] = g[i - 1][c] + f[i - 1][c], umod(g[i][c]);
    if (i - a[c] - 1 >= 1) g[i][c] -= f[i - a[c] - 1][c], dmod(g[i][c]);
  }
  if (i != n + 1) {
    re(c, m) {
      re(j, m) {
        if (j == c) continue;
        f[i][c] += g[i][j], umod(f[i][c]);
      }
    }
  }
}
re(i, m) ans += g[n + 1][i], umod(ans);
```

## Subtask 5

在 subtask 3 的基础上再加一个 $h$：
$$
\begin{aligned}
g(i,c)&=g(i-1,c)+f(i-1,c)-f(i-a_c-1,c)\\
h(i)&=\sum_{j=1}^m g(i,j)\\
f(i,c)&=h(i)- g(i,c)
\end{aligned}
$$
时空复杂度 $O(nm),O(nm)$。

```cpp
re(i, m) f[1][i] = 1;
rep(i, 2, n + 1) {
  re(c, m) {
    g[i][c] = g[i - 1][c] + f[i - 1][c], umod(g[i][c]);
    if (i - a[c] - 1 >= 1) g[i][c] -= f[i - a[c] - 1][c], dmod(g[i][c]);
    h[i] += g[i][c], umod(h[i]);
  }
  if (i != n + 1) {
    re(c, m) f[i][c] = h[i] - g[i][c], dmod(f[i][c]);
  }
}
out(h[n + 1])('\n');
```

## Subtask 6

在 subtask 5 的基础上利用滚动数组稍微压一下内存：
$$
\begin{aligned}
g(i\bmod 2,c)&=g((i\bmod 2) \oplus 1,c)+f(i-1,c)-f(i-a_c-1,c)\\
h&=\sum_{j=1}^m g(i\bmod 2,j)\\
f(i,c)&=h- g(i\bmod 2,c)
\end{aligned}
$$

时空复杂度 $O(nm),O(nm)$。

```cpp
re (i, m)
  f[1][i] = 1;
rep (i, 2, n + 1) {
  int h = 0;
  re (c, m) {
    g[i & 1][c] = g[(i & 1) ^ 1][c] + f[i - 1][c], umod(g[i & 1][c]);
    if (i - a[c] - 1 >= 1) g[i & 1][c] -= f[i - a[c] - 1][c], dmod(g[i & 1][c]);
    h += g[i & 1][c], umod(h);
  }
  if (i == n + 1) {
    out(h)('\n');
  } else {
    re (c, m)
      f[i][c] = h - g[i & 1][c], dmod(f[i][c]);
  }
}
```

---

## 作者：VioletIsMyLove (赞：7)

拿到题目一看数据范围就知道这题肯定是要 $O(n\times m)$ 的。

首先定义 $f_{i,j}$ 表示第 $i$ 天学习第 $j$ 个算法所累积的总方案（其中 $i-1$ 天学习的算法不为 $j$。
  
那么 $f_{i,j}=\sum_{a=1}^{i-1}\sum_{b=1,b\not= j}^{m}f_{a,b}$。 

而这题的关键就是处理这个 $\sum_{a=1}^{i-1}\sum_{b=1,b\not= j}^{m}f_{a,b}$。

只需要构造出每一个 $f_{i,j}$ 关于 $j$ 的前缀和，在每次使用时累加一下，在整合到 $f_{i,j}$ 时减掉由  $f_{i,j}$ 关于自身 $j$ 的前缀和即可。

但是这题由个坑点就是当一个负数去模一个正数时，需要先加上该正数再模。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,S,ans;
int a[7005],s[7005];
int f[7005][7005];//表示第i天学习第j个算法所累积的总方案（其中i-1天不为j） 
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main(){
	n=read();m=read();
	if(n==1){printf("%d\n",m);return 0;}
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=m;i++)f[1][i]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
		S=S-s[j];
		if(S<0)S+=1000000007;
		S%=1000000007;
		s[j]=s[j]+f[i-1][j]-f[max(0,i-a[j]-1)][j];
		if(s[j]<0)s[j]+=1000000007;
		s[j]%=1000000007;
		S=S+s[j];
		if(S<0)S+=1000000007;
		S%=1000000007;
		}
		for(int j=1;j<=m;j++){
			f[i][j]=S-s[j];
			if(f[i][j]<0)f[i][j]+=1000000007;
			f[i][j]%=1000000007;
		}
	}
	for(int i=1;i<=m;i++)for(int j=0;j<min(n,a[i]);j++)ans=(ans+f[n-j][i])%1000000007;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：徐天乾 (赞：6)

## 前言
比赛时我做出了这题，因为我做过的[这题](https://www.luogu.com.cn/problem/solution/AT685)与本题思路相似（没做过的同学我建议做一下）。
## 思路
根据题目的数据规模，我们不难想到写一个二维的动态规划，也就可以列出 $f_{i,j}$，表示的是第 $i$ 天学习 $j$ 算法的方案数。

首先，如果不考虑题目中的 $a_{i}$,那么

$f_{i,j}=\sum\limits_{k=1}^mf_{i-1,k}$,

但是，我们还需减去那些不合法，也就是连续学习多于 $a_{i}$ 的那些方案数，也就可得

$f_{i,j}=\sum\limits_{k=1}^mf_{i-1,k}-\sum\limits_{k=1}^mf_{i-a_{i}-1,k}+f_{i-a_{i}-1,j}$

这样的时间复杂度为 $O(nm^2)$，但是我们发现 $\sum\limits_{k=1}^mf_{i-1,k}$ 可以用一个数组记录，也就把时间复杂度降为 $O(nm)$，也就可以 A 了这题。

注意：这题数组全开 long long 要见祖宗的！（MLE 等着你）
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,n,m,a[7070],e[7070],f[7070][7070];
int const mod=(1e9)+7; 
int main(){
	scanf("%d %d",&n,&m);e[0]=1; //第0天默认为1
	for (i=1;i<=m;i++) scanf("%d",&a[i]);
	for (i=1;i<=n;i++){
		for (j=1;j<=m;j++) f[i][j]=(f[i][j]+e[i-1])%mod;  //先加上所有的方案数
		for (j=1;j<=m;j++)
			if (i>a[j]) f[i][j]=((f[i][j]-e[i-a[j]-1]+mod)%mod+f[i-a[j]-1][j])%mod;  //减去那些重复的方案数
		for (j=1;j<=m;j++) e[i]=(e[i]+f[i][j])%mod; //累加和，使时间变快
	}
	printf("%d\n",e[n]); //输出
	return 0;
}
```


---

## 作者：PengDave (赞：2)

# 思路一
十分朴素的做法，设 $f_{i,j,k}$ 表示第 $i$ 天学习第 $j$ 种算法 $k$ 天的方案数。那么对于 $f_{i,j,1}$，自然就可得：
$$f_{i,j,1}=\sum_{x=1(x\ne j)}^{m}\sum_{y=1}^{a_x}f_{i-1,x,y}$$
对于 $f_{i,j,k}$（$k>1$），可得：
$$f_{i,j,k}=f_{i-1,j,k-1}$$
显然，$i$ 那一维可以省去，再加上前缀和优化，时间复杂度 $O(n^{2}m)$，空间复杂度 $O(n^{2})$。
```cpp
#include<iostream>
#include<vector>
using namespace std;
int a[7005];
int n,m;
int pre[7005];
const int mod=1000000007;
int main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int maxn=0;
    for(int i=1;i<=m;i++){
        cin>>a[i];
        maxn=max(maxn,a[i]);
    }
    vector<vector<int> > dp(m+5,vector<int>(maxn+5));
    for(int i=1;i<=m;i++){
        dp[i][1]=1;pre[i]=1;
    }
    int cnt=m;
    for(int i=2;i<=n;i++){
        int tmp=0;
        for(int j=1;j<=m;j++){
            int temp=0;
            for(int k=a[j];k>=1;k--){
                if(k==1){
                    dp[j][k]=(cnt-pre[j]+mod)%mod;
                }else{
                    dp[j][k]=(dp[j][k-1])%mod;
                }
                temp=(temp+dp[j][k])%mod;
                tmp=(tmp+dp[j][k])%mod;
            }
            pre[j]=temp;
        }
        cnt=tmp;
    }
    int ans=0;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=a[i];j++){
            ans=(ans+dp[i][j])%mod;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
得分：50pts。
# 思路二
AC 代码，设 $f_{i,j}$ 表示第 $i$ 天学习第 $j$ 种算法的方案数，接着，枚举学习的天数，得：
$$f_{i,j}=\sum_{x=i-a_j}^{i-1}\sum_{y=1(y\ne j)}^{m}f_{x,y}$$
接着，我们进行优化，用 $pre_{i}$ 表示 $\sum_{x=1}^{i}\sum_{y=1}^{m}f_{x,y}$，用 $cnt_{j,i}$ 表示 $\sum_{x=1}^{i}f_{x,j}$，边 dp 边计算这两个，于是可得 $f_{i,j}=(pre_{i-1}-pre_{i-a_j-1})-(cnt_{j,i-1}-cnt_{j,i-a_j-1})$。最后，我们可以把 $i$ 这一维压掉，注意，取模时减法要加上模数再取模。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const int N=7005;
int a[N];
int dp[N];
int pre[N];
int cnt[N][N];
int main(){
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
		dp[i]=1;
		cnt[i][1]=1;
	}
	pre[1]=m;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i>=a[j]+1){
				dp[j]=((pre[i-1]-pre[i-a[j]-1]+mod)%mod-(cnt[j][i-1]-cnt[j][i-a[j]-1]+mod)%mod+mod)%mod;
			}else{
				dp[j]=((pre[i-1])%mod-(cnt[j][i-1])%mod+mod+1)%mod;
			}
			cnt[j][i]=(cnt[j][i-1]+dp[j])%mod;
			pre[i]=(pre[i]+dp[j])%mod;
		}
		pre[i]=(pre[i]+pre[i-1])%mod;
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		ans=(ans+dp[i])%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Eraine (赞：2)

## 做法一

5分做法：暴力，代码自己可以打出来。

## 做法二

15分做法：朴素的 DP ，无外加优化。这道题我们可以把 $n$ 天看做 $n$ 个阶段，然后进行动态规划。因为第 $i$ 个算法无论在哪一个时刻都不能学习连续超过 $a_{i}$ 天，所以动态规划转移方程为：

 $dp_{i_{j}}=\sum_{k=\max(0,i-a_{j})}^{i-1}\sum_{l=1}^mdp_{k_{l}}|j\neq l$ 

其中， $dp_{i_{j}}$ 表示第 $i$ 天学习第 $j$ 种算法的方案数。

## 做法三

30分做法：在做法二基础上考虑前缀和优化。注意到上述方程 $k$ 的取值是连续的，所以将 DP 方程做个稍稍改动：

 $dp_{i_{j}}=\sum_{l=1}^mdp_{i-1_{l}}-\sum_{l=1}^mdp_{\max(0,i-a_{j})-1_{l}}|j\neq l$ 

其中， $dp_{i_{j}}$ 表示第 $i$ 天及以前学习第 $j$ 种算法的方案数。 

## 做法四

30分做法：在做法二基础上考虑容斥原理优化。我们可以先想一个问题。已知 $n$ 个元素，现在要你用 $O(1)$ 在线求出除了下标为 $x$ 的元素的和。这问题想必很简单，只需预处理求出 $n$ 个元素的和在减去 $a_{x}$ 即可。我们可以建立一个 $f$ 数组，然后 DP 方程改为：

 $f_{i}=\sum_{j=1}^{m}dp_{i_{j}}$ 

 $dp_{i_{j}}=\sum_{k=\max(0,i-a_{j})}^{i-1}f_{k}-dp_{k_{j}}$ 

其中， $dp_{i_{j}}$ 表示第 $i$ 天学习第 $j$ 种算法的方案数， $f_{i}$ 表示第 $i$ 天学习 $m$ 种算法的方案总数。 

## 做法五

100分做法：在做法三基础上加上考虑做法四的优化：

 $f_{i}=\sum_{j=1}^{i}\sum_{k=1}^{m}dp_{j_{k}}$ 

 $(f_{i-1}-dp_{i-1_{j}})-(f_{\max(0,i-a_{j})-1_{j}}-dp_{i-\max(0,i-a_{j})-1})$ 

其中， $dp_{i_{j}}$ 表示第 $i$ 天及以前学习第 $j$ 种算法的方案总数， $f_{i}$ 表示第 $i$ 天及以前学习 $m$ 种算法的方案总数。 $f$ 数组可以用递推求得。 

## 代码

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int n,m,dp[7005][7005],dp2[7005],a[7005];//这里的dp2数组就是题解中的f数组 
const int MOD=1000000007;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		dp2[i]=(dp2[i]+dp2[i-1])%MOD;//前缀和处理 
		for(int j=1;j<=m;j++){
			int ans;
			if(i-a[j]>0)//以防越界 
				ans=((dp2[i-1]-dp2[i-a[j]-1])%MOD-(dp[i-1][j]-dp[i-a[j]-1][j])%MOD)%MOD; 
			else
				ans=((dp2[i-1]-dp2[0])%MOD-(dp[i-1][j]-dp[0][j])%MOD+1)%MOD;
			while(ans<0)
				ans+=MOD;//值不能为负 
			ans%=MOD;
			dp2[i]=(dp2[i]+ans)%MOD;
			dp[i][j]=(dp[i-1][j]+ans)%MOD;
		}
	}
	int ans=(dp2[n]-dp2[n-1])%MOD;//注意必须为n天 
	while(ans<0)
		ans+=MOD;
	printf("%d",ans);
	return 0;
}
```


## PS：

（此题解时间复杂度 $m$ 用 $n$ 表示）

（代码很丑，请见谅，但是不要抄袭）

（一个初二党，请多多指教）

（写本篇代码时要注意初始条件）

---

## 作者：白鲟 (赞：2)

### 分析
朴素的 DP 想法是设 $f_{i,j}$ 为第 $i$ 天选算法 $j$ 进行学习的方案数，枚举学 $j$ 算法的连续天数进行转移。式子是 $f_{i,j}=\sum_{k=i-a_j}^{i-1}\sum_{l\not=j}f_{k,l}$。时间复杂度暴力转移为 $\operatorname{O}(n^2m)$。

发现这个式子可以补集转化后前缀和优化。具体地，将式子写成 $\sum_{k=i-a_j}^{i-1}(\sum_lf_{k,l}-f_{k,j})$，分别作 $\sum_lf_{k,l}$ 与 $f_{k,j}$ 的前缀和即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define loop(i,from,to) for(int i=(from);i<=(to);++i)
using namespace std;
const int maxn=7e3,mod=1e9+7;
int n,m,a[maxn+1],f[maxn+1],sumone[maxn+1][maxn+1],sumall[maxn+1];
int main(){
	scanf("%d%d",&n,&m);
	loop(i,1,m)scanf("%d",&a[i]);
	sumall[0]=1;
	loop(i,1,n){
		sumall[i]=sumall[i-1];
		loop(j,1,m)
			f[j]=((long long)sumall[i-1]-(i-a[j]-1>=0?sumall[i-a[j]-1]:0)+mod-sumone[i-1][j]+(i-a[j]-1>=0?sumone[i-a[j]-1][j]:0))%mod,
			sumall[i]=(sumall[i]+f[j])%mod,sumone[i][j]=(sumone[i-1][j]+f[j])%mod;
	}
	printf("%d\n",(mod+sumall[n]-sumall[n-1])%mod);
	return 0;
}
```

---

## 作者：Louis_lxy (赞：0)

挺简单的前缀和优化 dp，感觉就是个板子。

考虑 dp，设 $f(i,j)$ 表示第 $i$ 天学习完第 $j$ 个算法的方案数，朴素转移就是 $f(i,j)=\sum_{k=i-a_j}^{i-1}\sum_{p=1}^mf(k,p)\times[p\ne j]$，复杂度 $O(n^2m^2)$。

考虑优化，显然可以发现这个式子可以前缀和。我们直接记 $sum(i,j)=\sum_{k=1}^if(k,j)$，然后优化上述式子变成 $f(i,j)=\sum_{p=1}^m(sum(i-1,p)-sum(i-a_j-1,p))\times[p\ne j]$，复杂度 $O(nm^2)$。

然后这样仍然无法接受，于是记 $s(i)=\sum_{j=1}^msum(i,j)$，然后 dp 方程就变成了 $f(i,j)=s(i-1)-s(i-a_j-1)-sum(i-1,j)+sum(i-a_j-1,j)$，复杂度 $O(nm)$，注意到这样空间复杂度在 $n\times m$ 级别，常数很大，会爆空间，然而 $s$ 无法滚动。但是我们发现 $f$ 压根没用，于是开个变量或者一维数组就可以了，别开 `long long` 就能过。

---

## 作者：Talkative (赞：0)

第 42 篇题解寄！

个人认为是一道 dp 好题。

动态规划：我们可以使用动态规划来解决这个问题。定义一个数组 $dp_{i,j}$，其中 $i$ 表示当前是第几天，$j$ 表示当前学习的算法编号。$dp_{i,j}$ 表示在第 $i$ 天学习算法 $j$ 的方案数。

接着状态转移：对于每一天 $i$ 和每种算法 $j$，我们需要考虑前一天学习的算法是否与当前算法相同。如果相同，则需要满足连续学习的限制；如果不相同，则可以任意选择一种算法。

初始条件：第一天可以选择任意一种算法，因此 $dp_{1,j} = 1$ 对于所有 $j$ 都成立。

最终结果：我们需要计算在第 $n$ 天结束时，所有算法的总方案数之和。

然后就结束了，感谢阅读！

---

## 作者：篮网总冠军 (赞：0)

我自己苦想半小时，做出来了。忽然觉得好简单。点开题解一看，感觉和下面这位大佬思路差不多，但小蒟蒻我还是决定写一下我的思路。

首先，读题。这是一道很标准的动态规划。我们设 $dp[i][j]$ 代表在第 $i$ 天学第 $j$ 个算法在可能的方案数。

在这里，我们思考一下，是不是如果前一天不学第 $j$ 个算法，或者 $i \le a[j]$，那就对今天的方案数没有影响。

那么我们继续，如果对今天有影响，那么前 $a[j]$ 天必须学的全都是第 $j$ 种算法。那么我们只需要将 $i-a[j]$ 至 第 $i-1$ 天都学第 $j$ 种算法的方案数去掉即可。那么我们反过来思考，这是不是就等于第 $i-a[j]-1$ 天不学第 $j$ 种算法的方案数呢？

我们为了简化时间复杂度，可以求出第 $i$ 天的方案总数，再在需要时直接带入即可。

算法复杂度 $O(nm)$。

在这里提醒几点：

+ 记得，$dp$ 数组千万不要开 ```long long ```。

+ 记得，一定要特判 ``` i==j+1 ``` 的情况。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;

long long a[7007],s[7005];
int dp[7005][7005];
long long mod=1e9+7;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	} 
	for(int i=1;i<=m;i++) dp[1][i]=1;
	s[1]=m;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			dp[i][j]=s[i-1];
			if (i==a[j]+1) dp[i][j]=s[i-1]-1;
			else if (i>a[j]){
				dp[i][j]=(dp[i][j]-(s[i-a[j]-1]-dp[i-a[j]-1][j])+mod)%mod;
			}
		}
		for(int j=1;j<=m;j++) s[i]+=dp[i][j];
		s[i]%=mod;
	}
	cout<<s[n]<<endl;
	return 0;
}

```

---

## 作者：keepwatcher_kensap (赞：0)

## Part 1 题意

暑假一共有 $n$ 天，我们假设 MLE 每天都有足够的时间学 OI。MLE 列出了可供选择的 $m$ 个算法。MLE 每天只能且必须学习一个算法。

而且，MLE 长时间学同一种算法会厌倦，所以每一种算法不能连续学习太多天，第 $i$ 种算法最多可以连续学习 $a_i$ 天。MLE 没有必要学习全部的算法。

MLE 想知道，自己有多少种不同的学习安排来度过这 $n$ 天。两种学习安排不同仅当这两种安排中有至少一天学习的算法不同。因为方法可能过多，你只需要输出方案数对 $10^9+7$ 取模即可。

## Part 2 思路

由于 $1 \leq a_i,n,m \leq 7 \times 10^3$，所以我们可以使用 $O(nm)$ 的做法通过此题。很自然的就想到算法**动态规划**，和我们要考虑的两个变量：目前天数和今天学习的算法。

不难发现，考虑每一天的时候，我们都会用到一个变量：昨天的总方案数。我们假设第 $i$ 天学习算法 $j$，此时的方案数为 $f_{i,j}$，则该变量 $g$ 就是 $f_{i-1,1 \dots m}$ 的总和。我们可以定义 $g_i$ 为第 $i$ 天学习各种算法的总方案数，$g_i$ 在考虑完 $f_{i,1 \dots m}$ 后计算，在考虑明天的时候就可以直接调用了。

不难发现，$f_{i,j}$ 的最小值是 $g_{i-1}$，因为怎么说也是从昨天所有方案转移过来的。因此每次考虑 $f_{i,j}$ 的时候就可以先 $f_{i,j} \leftarrow g_{i-1}$。

由于每种算法最多连续学习 $a_i$ 天，而在考虑每种算法的时候都考虑前 $a_i$ 天的情况会导致超时。所以，对于第 $i$ 天学习的算法 $j$，我们就只考虑 $g_{i-a_j-1}$ 和 $f_{i-a_j-1,j}$ 即可，因为这就涵盖了每一天都所有情况。

然而，当 $i \leq a_j$，也就是目前根本不会到达该算法的学习上限的时候，我们就可以放心考虑。但当 $i = a_j+1$，也就是在你发现已经超过了该算法的学习上限的时候，而你之前又将此重复计算，我们要 $f_{i,j} \leftarrow f_{i,j}-1$，扣去不可能的存在。

因此，我们就得出状态转移方程：

- $f_{i,j} \leftarrow g_{i-1}$。

- 若 $i \leq a_j$，不考虑以下下两条转移方程。

- 若 $i=a_j+1$，$f_{i,j} \leftarrow f_{i,j}-1$。

- 若上一条不成立，$f_{i,j} \leftarrow f_{i,j}-g_{i-a_j-1}+f_{i-a_j-1,j}$。

当然，别忘了将 $g_i$ 更新一下。

## Part 3 代码

```
#include <bits/stdc++.h>
#define ll long long
const ll maxn=7e3+5,mod=1e9+7;
ll n,m,a[maxn],g[maxn];
int f[maxn][maxn];
inline ll read()
{
	ll x=0,y=1;
	char ch=getchar();
	while (ch<'0' || ch>'9')
	{
		if (ch=='-') y=-1;ch=getchar();
	}
	while (ch>='0' && ch<='9')
	{
		x=x*10+int(ch-'0');ch=getchar();
	}
	return x*y;
}
int main()
{
	n=read(),m=read();
	for (int i=1;i<=m;i++) a[i]=read();
	for (int i=1;i<=m;i++) f[1][i]=1;g[1]=m;
	for (int i=2;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			f[i][j]=g[i-1];
			if (i<=a[j]) continue;
			if (i==a[j]+1) f[i][j]=(f[i][j]-1+mod)%mod;
			else f[i][j]=(f[i][j]-g[i-a[j]-1]+f[i-a[j]-1][j]+mod)%mod;
		}
		for (int j=1;j<=m;j++) g[i]=(g[i]+f[i][j])%mod;
	}
	printf("%lld",g[n]);
	return 0;
}
```

---

## 作者：CyberPrisoner (赞：0)

典型的线性 DP，看一眼数据范围，大概可以确定应该用 $n^2$ 的时间空间。接下来考虑设计状态，考虑所有因素，DP 方程中需要三个状态，分别为第几天，这一天学什么算法，连续学了多少天。这样转移非常方便，但是需要 $n^3$ 的空间，必须优化掉一维。天数必须作为转移状态，优化掉当天学的算法不好转移，那么考虑优化掉连续学了多少天。

设 $dp_{i,j}$ 为到了第 $i$ 天，这一天学的算法为 $j$ 的方案数，上来我们先不考虑 $a_{j}$ 的限制让 $dp_{i,j}=\sum_{k=1}^m dp_{i-1,k}$，相当于上一天的所有方案数，这个时候我们还要减去连续 $a_{j}$ 天学相同算法的情况，对于从 $i$ 开始，往前 $a_{j}$ 天都是 $j$，有 
$$\sum_{k=1}^m dp_{i-a_{j},k}-dp_{i-a_j,j}$$
因为我们只要连续 $a_{j}$ 个，多了不要，所以还要减去 $dp_{i-a_j,j}$，我们对于每一个 $i$ 可以计算这一天学所有算法的总方案，省去每次的求和操作。最后要注意空间限制，不能全开 long long。

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=7005,mod=1e9+7;
ll n,m,a[N];
ll f[N];//最后的总和 
int g[N][N];//前i天结尾为j的方案 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
		a[i]++;
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			g[i][j]=f[i-1]%mod;
			if(i>=a[j])	g[i][j]=(g[i][j]-(f[i-a[j]]-g[i-a[j]][j])+mod)%mod;
			f[i]=(f[i]+g[i][j])%mod;
		}
	}
	cout<<f[n]%mod;
} 
```

~~个人认为这题可以评个绿~~

---

## 作者：Frictional (赞：0)

## 题意
给你 $m$ 个整数,为 $a_1,a_2,\cdots,a_m$ 将 $1\sim m$ 填入一个长度为 $n$ 的序列（可以重复），但是数字 $i$ 最多只能连续出现 $a_i$ 次。问这样的序列有多少种可行的方案。
## 思路
这道题可以用动态规划来写。定义 $dp[i][j]$ 为到第 $i$ 个位置填 $j$ 的可行的方案数。
我们可以分两种情况来讨论。

第一种情况是 $a[j] \geqslant i$ 也就是不管你怎么填，都不可能非法，所以这样的话填任何数都是合法的。

第二种情况就是如果 $a[j] < i$ 这就有可能会有非法的序列了。那怎么办呢？我们就用全部的减掉非法的就可以了，那什么样的序列在填 $i-1$ 个数的时候是合法的，但填 $i$ 个数就非法的序列呢，就是当 $i-a[j]$ 到 $i$ 都等于 $j$，且第 $i-a[j]-1$ 个数不是 $j$ 那这个序列就是符合我们的要求的。而这个序列的方案数其实就等于第 $i-a[j]-1$ 不是 $j$ 的方案数，因为既然那些位都是相等的，那就没有新的方案产生，就不用计算了；而当前这一位，与前一位不相等时，那就等于前一位不选 $j$ 的方案数。

至此，我们就可以得出转移方程了。当 $a[j] \geqslant i$ 时，$dp[i][j]=\sum\limits_{l=1}^mdp[i-1][l]$
当 $a[j] < i$ 时，$dp[i][j]=\sum\limits_{l=1 ,l!=j}^mdp[i-1][l]+(dp[i-1][j]-\sum\limits_{l=1,l!=j}^mdp[i-a[j]-1][l])$ 

但只是这样是过不了的，这时间肯定是爆掉的，所以我们可以用前缀和优化，使 $sum[i]=\sum\limits_{l=1}^mdp[i][l]$。

不要忘记初始化和取余。因为在第一个位置填任何数方案都只有一个，所以 $dp[1][j]=1$。而且数组开 int 就可以，因为会与 $1e9+7$ 取模，是不可能爆 int 的，而且开 long long 会 MIE。
## AC code
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second

// #define int long long
#define ll long long
using namespace std;
inline int rd(){
    int x=0,f=1; 
    char ch=gc;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;
    }
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
    return x*f;
}
inline void wr(int x){
    if(x<0) x=-x;
    if(x>9) wr(x/10);
    pc((x%10)^48);
}
const int mod=1e9+7;
const int N=7e3+5;
ll n,m;
ll a[N];
int dp[N][N];
ll sum[N];
signed main(){
    cin>>n>>m;
    FOR(i,1,m) cin>>a[i];
    if(m==1&&a[1]<n){
        cout<<"0";
        return 0;
    }
    FOR(i,1,m) dp[1][i]=1;
    sum[1]=m;
    FOR(i,2,n){
        // if(i==1) continue;
        FOR(j,1,m){
            dp[i][j]=sum[i-1];
            if(i>a[j]){
                if(i==a[j]+1) dp[i][j]=(dp[i][j]-1+mod)%mod;
                dp[i][j]=(dp[i][j]-sum[i-a[j]-1]+dp[i-a[j]-1][j]+mod)%mod;
            }
            sum[i]+=dp[i][j];
            sum[i]%=mod;
        }
    }
    cout<<sum[n]%mod;
    return 0;
}
```


---

