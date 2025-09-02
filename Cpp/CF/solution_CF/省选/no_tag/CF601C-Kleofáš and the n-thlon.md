# Kleofáš and the n-thlon

## 题目描述

Kleofáš is participating in an $ n $ -thlon - a tournament consisting of $ n $ different competitions in $ n $ different disciplines (numbered $ 1 $ through $ n $ ). There are $ m $ participants in the $ n $ -thlon and each of them participates in all competitions.

In each of these $ n $ competitions, the participants are given ranks from $ 1 $ to $ m $ in such a way that no two participants are given the same rank - in other words, the ranks in each competition form a permutation of numbers from $ 1 $ to $ m $ . The score of a participant in a competition is equal to his/her rank in it.

The overall score of each participant is computed as the sum of that participant's scores in all competitions.

The overall rank of each participant is equal to $ 1+k $ , where $ k $ is the number of participants with strictly smaller overall score.

The $ n $ -thlon is over now, but the results haven't been published yet. Kleofáš still remembers his ranks in each particular competition; however, he doesn't remember anything about how well the other participants did. Therefore, Kleofáš would like to know his expected overall rank.

All competitors are equally good at each discipline, so all rankings (permutations of ranks of everyone except Kleofáš) in each competition are equiprobable.

## 说明/提示

In the first sample, Kleofáš has overall score $ 6 $ . Nobody else can have overall score less than $ 6 $ (but it's possible for one other person to have overall score $ 6 $ as well), so his overall rank must be $ 1 $ .

## 样例 #1

### 输入

```
4 10
2
1
2
1
```

### 输出

```
1.0000000000000000
```

## 样例 #2

### 输入

```
5 5
1
2
3
4
5
```

### 输出

```
2.7500000000000000
```

## 样例 #3

### 输入

```
3 6
2
4
2
```

### 输出

```
1.6799999999999999
```

# 题解

## 作者：EuphoricStar (赞：8)

## 思路

期望 dp。

设 $f_{i,j}$ 为前 $i$ 项比赛中获得总分为 $j$ 的期望人数。

那么转移方程显而易见：

$$ f_{i,j} = \dfrac{\sum\limits_{k=1}^m{f_{i-1,j-k}\ (k \ne c_i)}}{m-1} $$

意思是因为同一场比赛得分互不相同，因此从 $1$ 到 $m$ 的所有分数必然有且仅有一人取得，因此直接求和。因为有 $m - 1$ 种得分（除掉 $a_i$），所以每种得分被取到的概率为 $\dfrac{1}{m - 1}$。

最后的答案为 $1 + \sum\limits_{i=1}^{sum - 1} f_{n,i}$，其中 $sum$ 为所有 $c_i$ 的总和。$\sum\limits_{i=1}^{sum - 1} f_{n,i}$ 是得分严格比那个人低的期望人数，$+1$ 是根据排名的定义。

初值为 $f_{1,i} = 1\ (i \ne a_1)$.

注意到如果直接转移是 $O(nm^2)$ 的，很可能会炸，因此可以加一个前缀和优化，使复杂度降到 $O(nm)$。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 110;
const int maxm = 100100;

int n, m, a[maxn];
long double f[maxn][maxm], g[maxm];

void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		if (i != a[1]) {
			f[1][i] = 1;
		}
	}
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= i * m; ++j) {
			g[j] = g[j - 1] + f[i - 1][j];
			f[i][j] = (j >= i ? (g[j - 1] - (j >= m + 1 ? g[j - m - 1] : 0) - (j >= a[i] ? f[i - 1][j - a[i]] : 0)) / (m - 1) : 0);
		}
	}
	long double ans = 1;
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		sum += a[i];
	}
	for (int i = 1; i < sum; ++i) {
		ans += f[n][i];
	}
	printf("%.12Lf", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：Yaha (赞：2)

### 概率DP

 $f[i][j]$ 表示前 $i$ 项比赛，总得分 $j$ 的期望人数。
 
最后的答案，即期望排名，就是 $f[n][1\sim C-1]+1$ 。其中 $C=\sum_{i=1}^n c[i]$。

转移：$f[i][j]=\frac {1}{m-1} \sum f[i-1][j-k]$。其中 $k\in [1,m]$ 且 $k\ne c[i]$。

上面的式子中，前 $i$ 场得分 $j$ 的人们第 $i$ 场可能得 $k$ 分，又因为有一个人的分数已经确定，所以得 $k$ 分的概率为 $\frac{1}{m-1}$ 。

注意数组大小，这个我大概就 $WA$ 了一万次吧。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int c[1100];
double f[110][110*1100],sum[110*1100];

int main(){
	int n,m,s=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		s+=c[i];
	}
	for(int j=1;j<=m;j++) if(j!=c[1]) f[1][j]=1;//初始化
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=i*m;j++)
			sum[j]=sum[j-1]+f[i-1][j];
		for(int j=i;j<=m*i;j++)
		{
			if(j<=m+1) f[i][j]=sum[j-1]-(1<=j-c[i])*f[i-1][j-c[i]];
			else f[i][j]=sum[j-1]-sum[j-m-1]-(j-m<=j-c[i])*f[i-1][j-c[i]];
			f[i][j]/=m-1;
		}
	}
	double ans=0;
	for(int i=1;i<=s-1;i++) ans+=f[n][i];
	printf("%.16lf",ans+1.0);

	return 0;
}
```


---

## 作者：yingyudou (赞：2)

#### Description
$m$ 个人参加 $n$ 项比赛。
每场比赛有一个分值，在 $[1,m]$ 之间，且同一场比赛得分两两不同。总分为每场比赛得分之和。

有一个人，给出他每场比赛的得分 $c_i$ ，求这个人总分排名（第几小）的期望值。

$1\le n\le100,1\le m\le1000$

----
#### Solution
- 概率dp
- 设 $f_{i,j}$ 表示第 $i$ 场比赛得分为 $j$ 的概率
- $f_{i,j}=\frac{1}{m-1}\sum_{k=j-m}^{k\le j-1,k\ne c_i}{f_{i-1,k}}$
- 得分比这个人小的概率为 $\sum_{t=1}^{S-1}{f_{n,t}}$ ( $S$ 为这个人总分)
- 答案即 $1+(m-1)\sum_{t=1}^{S-1}{f_{n,t}}$ （人数乘上概率加本身）

- 本题可以使用滚动数组，其实不滚空间也够
- $O(n^2m)$
----
#### Code 1

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    int N=0,C=0;char tf=getchar();
    for(;!isdigit(tf);tf=getchar())C|=tf=='-';
    for(;isdigit(tf);tf=getchar())N=(N<<1)+(N<<3)+(tf^48);
    return C?-N:N;
}

const int N=110,M=1010;
int n,m,c[N],skr,L,R;
double d,ans;
double f[N][N*M],sum[N*M];//前缀和优化dp

int main()
{
	n=read(),m=read(),d=1.0/(m-1);//除自己外m-1个人
	for(int i=1;i<=n;++i)skr+=c[i]=read();
	
	f[0][0]=sum[0]=1;
	for(int i=1;i<=n;++i)
	{
		for(int j=i;j<=i*m;++j)
		{
			L=max(i-1,j-m),R=min((i-1)*m,j-1);//上一场比赛合法最大/小得分
			f[i][j]=d*sum[R];
			if(L)f[i][j]-=d*sum[L-1];
			if(L<=j-c[i]&&j-c[i]<=R)//减去自己
				f[i][j]-=d*f[i-1][j-c[i]];
		}
		for(int j=1;j<=i*m;++j)sum[j]=sum[j-1]+f[i][j];
	}
	
	for(int j=n;j<skr;++j)ans+=f[n][j];
	printf("%.16lf",ans*(m-1)+1);//概率乘人数加自己
	
    return 0;
}
```
---

#### Code 2
```cpp
//滚动数组
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    int N=0,C=0;char tf=getchar();
    for(;!isdigit(tf);tf=getchar())C|=tf=='-';
    for(;isdigit(tf);tf=getchar())N=(N<<1)+(N<<3)+(tf^48);
    return C?-N:N;
}

const int N=110,M=1010;
int n,m,c[N],skr,L,R,pre,now=1;
double d,ans;
double f[2][N*M],sum[N*M];//前缀和优化dp

int main()
{
	n=read(),m=read(),d=1.0/(m-1);//除自己外m-1个人
	for(int i=1;i<=n;++i)skr+=c[i]=read();
	
	f[0][0]=sum[0]=1;
	for(int i=1;i<=n;++i)
	{
		for(int j=i;j<=i*m;++j)
		{
			L=max(i-1,j-m),R=min((i-1)*m,j-1);//上一场比赛合法最大/小得分
			f[now][j]=d*sum[R];
			if(L)f[now][j]-=d*sum[L-1];
			if(L<=j-c[i]&&j-c[i]<=R)//减去自己
				f[now][j]-=d*f[pre][j-c[i]];
		}
		for(int j=1;j<=i*m;++j)sum[j]=sum[j-1]+f[now][j];
		swap(now,pre);//滚
	}
	
	for(int j=n;j<skr;++j)ans+=f[pre][j];
	printf("%.16lf",ans*(m-1)+1);//概率乘人数加自己
	
    return 0;
}
```

---

## 作者：do_it_tomorrow (赞：1)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf601c-kleofas-and-the-n-thlon/)

根据全概率公式，期望就是概率和权值的乘积，所以只需要算出 $n$ 场总分小于 $\sum\limits_{i=1}^n c_i$ 的概率最后乘以 $m-1$ 就可以了。

需要注意因为每一个得分只出现一次，所以计算是与 $c_i$ 有关的。

容易发现，我们需要求的概率就是所有得分为小于 $\sum\limits_{i=1}^n c_i$ 的概率之和，所以这个题目就转换为了求出每一个得分的概率了。

设 $f_{i,j}$ 表示前 $i$ 场比赛得分为 $j$ 的概率，那么显然有：

$$f_{i,j}=\sum\limits_{k=1\wedge k\ne c_i}^{\min(m,j)}\dfrac{f_{i-1,j-k}}{m-1}$$

考虑把 $f_{i,j}$ 做一个前缀和优化，那么复杂度就是 $O(n^2m)$。

[Submission #285664602 - Codeforces](https://codeforces.com/contest/601/submission/285664602)

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF601C)

期望 dp 好恶心……

设 $dp[i][j]$ 表示前 $i$ 场比赛得分为 $j$ 的期望人数，那么对于第 $i$ 场得分为 $k$ 的情况都可以从 $dp[i-1][j-k]$ 转移过来，那么显然有转移如下：

$dp[i][j]=\dfrac{1}{m-1}\sum\limits_{k=1}^mdp[i-1][j-k](k≠c_i)$。

这个转移方程需要枚举 $i,j,k$，复杂度是 $O(n^3m^2)$ 的。考虑对这个丑陋的式子进行优化。

可以使用前缀和优化掉 $k$。考虑设 $s[j]$ 代表前 $i-1$ 场比赛得分为 $1 \sim j$ 的期望人数之和。

显然对于前 $i$ 场比赛，得分 $j \in [i,i\times m]$。

那么对于 $j \le m+1$ 的情况，有 $dp[i][j]=\dfrac{1}{m-1}(s[j-1]-dp[i-1][j-c_i])$。（注意数组不要越界）

对于 $m+1<j \le i \times m$ 的情况，有 $dp[i][j]=\dfrac{1}{m-1}(s[j-1]-s[j-m-1]-dp[i-1][j-c_i])$。（即期望得分在 $[j-m,j-1]$ 中的人数）

这样压掉一维之后，时间复杂度优化为 $O(n^2m)$，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
using namespace std;
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
ll n,m,c[105],sum;
long double dp[105][100005],s[100005],ans;
int main()
{
	n=read(),m=read();
	for(ri i=1;i<=n;i++)
		c[i]=read(),sum+=c[i];
	for(ri i=1;i<=m;i++)
		if(i!=c[1])
			dp[1][i]=1;		
	for(ri i=2;i<=n;i++)
	{
		for(ri j=1;j<=i*m;j++)
			s[j]=s[j-1]+dp[i-1][j];
		for(ri j=i;j<=i*m;j++)
		{
			if(j<=m+1)
			{
				if(j>=c[i])
					dp[i][j]=s[j-1]-dp[i-1][j-c[i]];
				else
					dp[i][j]=s[j-1];
			}
			else
				dp[i][j]=s[j-1]-s[j-m-1]-dp[i-1][j-c[i]];
			dp[i][j]/=(m-1);
		}
	}
	for(ri i=1;i<=sum-1;i++)
		ans+=dp[n][i];
	cout<<fixed<<setprecision(10)<<ans+1<<"\n";
	back 0;
}
```

---

## 作者：Link_Space (赞：1)

比较水的一道期望DP，考虑定义状态的问题：由于要求的是一人的期望排名，可以把每个分数段的期望人数求出来，然后答案即为比他总分低的所有分数段的期望人数之和再+1。那么状态定义即为：$dp[i][j]$ 表示一共进行了i场比赛时总分为j的期望人数。

这个状态如何转移呢？对于每一场比赛来说，由于询问者本人的此轮比赛分数已经确定，所以对于剩下的 $m-1$ 种得分，每一种得分都有 $m-1$ 的概率。

那么状态转移方程即为：$dp[i][j]=\frac{1}{m-1} \sum_{k=1}^{m} dp[i-1][j-k](k \ne c[i])$

最后的答案即为 $\sum_{i=1}^{C-1}dp[n][i] + 1$

其中 $C=\sum_{i=1}^{n}c [i]$
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 1e5 + 5;
int c[N];
double sum[105 * 1005];
double dp[105][105 * 1005];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int C = 0;
    for (int i = 1; i <= n;i++)
        scanf("%d", &c[i]), C += c[i];
    for (int i = 1; i <= m;i++)
        if(i!=c[1])
            dp[1][i] = 1;
    for (int i = 2; i <= n;i++)
    {
        for (int j = 1; j <= i * m; j++)
            sum[j] = sum[j - 1] + dp[i - 1][j];
        for (int j = i; j <= i * m;j++)
        {
            if(j<=m+1)
                dp[i][j] = sum[j - 1] - (1 <= j - c[i]) * dp[i - 1][j - c[i]];
            else
                dp[i][j] = sum[j - 1] - sum[j - m - 1] - dp[i - 1][j - c[i]];
            dp[i][j] /= m - 1;
        }
    }
    double ans = 0;
    for (int i = 1; i <= C - 1;i++)
        ans += dp[n][i];
    printf("%.16lf\n", ans + 1);
}
```


---

## 作者：Ghosty_Neutrino (赞：0)

就是个dp，不难，《真》不难。

## 题意
$m$ 个人参加 $n$ 场比赛，每场比赛这 $m$ 个人的排名都是一个 $1$ 到 $m$ 的排列，且各种得分情况概率相同，现在某个人知道其 $n$ 场比赛的排名，问其最终排名的期望。

## 分析
设 $s=a_1+a_2,\cdots,+a_n$，想知道这个人的最终排名，只需要知道 $n$ 场比赛后另外 $m-1$ 个人中总排名低于s的期望人数即可，因为每场比赛所有排名情况出现概率相同，所以另外 $m-1$ 个人都是一样的，算一个人即可，以 $dp_{i,j}$ 示 $i$ 场比赛后这 $m-1$ 个中总排名是j的期望人数，$dp_{0,0}=m-1$ 表示还没比赛时排名是 $0$ 的期望人数就是这 $m-1$ 个人，在第 $i$ 场比赛这 $m-1$ 个人的排名都等概率取 $1$ 到 $n$ 中除 $a_i$ 的 $m-1$ 个数，故有转移方程:
$$
dp_{i,j}=sum_{dp_{i-1,j-k}}\div(m-1)
$$
用前缀和优化下该转移，$dp_{i-1,k}$ 对区间 $[dp_{i,k+1},dp_{i,k+m}]$ 扣去 $dp_{i,k+a_i}$ 点的贡献都是 $dp_{i-1,k}\div(m-1)$，所以每次在端点处更新最后来一遍前缀和即完成一步转移，最终答案就是 $dp_{n,1}+,\cdots,+dp_{n,s-1}+1$，因为该人的排名要在这些总排名靠前的人后面一名。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f
#define maxn 101
int n,m,s,a[maxn];
double dp[111111],dpp[111111];
int main(){
    while(~scanf("%d%d",&n,&m)){
        s=0;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),s+=a[i];
        if(m==1){
            printf("1\n");
            continue;
        }
        memset(dp,0,sizeof(dp));
        dp[0]=m-1;
        for(int i=1;i<=n;i++){
            memset(dpp,0,sizeof(dpp));
            for(int j=0;j<=n*m;j++){
                double p=dp[j]/(m-1);
                dpp[j+1]+=p,dpp[j+m+1]-=p;
                dpp[j+a[i]]-=p,dpp[j+a[i]+1]+=p;
            }
            dp[0]=dpp[0];
            for(int j=1;j<=n*m;j++)dpp[j]+=dpp[j-1],dp[j]=dpp[j];
        }
        double ans=0;
        for(int j=0;j<s;j++)ans+=dp[j];
        printf("%.12f\n",ans+1.0);
    }
    return 0;
}                                              
```

---

## 作者：AxDea (赞：0)

概率DP（应该是小于等于蓝题的难度

设 $f(i,j)$ 表示前 $i$ 项比赛除此人外得分为 $j$ 的期望人数

有转移：

$f(i,j)= \frac{1}{m-1} \sum_{k=j-m}^{j-1}f(i-1,k)\times[k\neq j-c_i]$

很显然的前缀和

设 $s_k = \sum_{j=1}^{k} f(i-1,j)$

转移：

$f(i,j)=\frac{1}{m-1} (s_{j-1}-s_{j-m-1}-f(i-1,j-c_i)\times[j-m\leq j-c_i \leq j-1])$

答案即为 $1+\sum_{i=1}^{c-1}f(n,i)$

Code:

```
#include<bits/stdc++.h>
using namespace std;
const int N = 110,M = (int)1e3+7;
int n,m,c[N],C;
double f[N][N*M],s[N*M],g[N*M];
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&c[i]),C += c[i];
	for(int i=1;i<=m;++i) if(i!=c[1]) f[1][i] = 1.0;
	for(int i=2;i<=n;++i) {
		for(int j=1;j<=i*m;++j) s[j] = s[j-1]+f[i-1][j];
		for(int j=i;j<=i*m;++j) 
			if(j<=m+1) g[j] = s[j-1] - f[i-1][j-c[i]] * (1<=j-c[i]);
			else g[j] = s[j-1] - s[j-m-1] - f[i-1][j-c[i]] * (j-m<=j-c[i]);
		for(int j=i;j<=i*m;++j) f[i][j] = g[j]/(m-1);
	}
	double ans = 0.0;
	for(int i=1;i<=C-1;++i) ans += f[n][i];
	printf("%.16lf",ans+1.0);
	return 0;
}
```

---

