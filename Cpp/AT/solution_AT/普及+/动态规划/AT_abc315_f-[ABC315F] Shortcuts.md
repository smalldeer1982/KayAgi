# [ABC315F] Shortcuts

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc315/tasks/abc315_f

座標平面上でチェックポイント $ 1,2,\dots,N $ をこの順に通るレースが行われます。  
チェックポイント $ i $ の座標は $ (X_i,Y_i) $ であり、すべてのチェックポイントの座標は異なります。

チェックポイント $ 1,N $ 以外のチェックポイントは、通過を省略することもできます。  
ただし、通らなかったチェックポイントの個数を $ C $ として、以下の通りペナルティが課せられます。

- $ C\ >\ 0 $ なら $ \displaystyle\ 2^{C−1} $
- $ C=0 $ なら $ 0 $

チェックポイント $ 1 $ からチェックポイント $ N $ までの総移動距離（ユークリッド距離）とペナルティの和を $ s $ とします。  
このとき、 $ s $ として達成可能な最小の値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \le\ N\ \le\ 10^4 $
- $ 0\ \le\ X_i,Y_i\ \le\ 10^4 $
- $ i\ \neq\ j $ ならば $ (X_i,Y_i)\ \neq\ (X_j,Y_j) $

### Sample Explanation 1

チェックポイント $ 1,2,5,6 $ を通過し、 $ 3,4 $ の通過を省略することを考えます。 - チェックポイント $ 1\ \rightarrow\ 2 $ に移動する。 $ 2 $ 点間の距離は $ \sqrt{2} $ である。 - チェックポイント $ 2\ \rightarrow\ 5 $ に移動する。 $ 2 $ 点間の距離は $ 1 $ である。 - チェックポイント $ 5\ \rightarrow\ 6 $ に移動する。 $ 2 $ 点間の距離は $ \sqrt{2} $ である。 - 通らなかったチェックポイントは $ 2 $ つであり、このとき科せられるペナルティは $ 2 $ である。 以上のようにして、 $ s\ =\ 3\ +\ 2\sqrt{2}\ \approx\ 5.828427 $ を達成できます。 $ s $ をこの値より小さくすることはできません。

## 样例 #1

### 输入

```
6
0 0
1 1
2 0
0 1
1 0
2 1```

### 输出

```
5.82842712474619009753```

## 样例 #2

### 输入

```
10
1 8
3 7
9 4
4 9
6 1
7 5
0 0
1 3
6 8
6 4```

### 输出

```
24.63441361516795872523```

## 样例 #3

### 输入

```
10
34 24
47 60
30 31
12 97
87 93
64 46
82 50
14 7
17 24
3 78```

### 输出

```
110.61238353245736230207```

# 题解

## 作者：LiaoYF (赞：9)

2023/9/6 换上了更简洁的做法

# 题意
有 $N$ 个点，你从第一个点出发，要按顺序经过他们，最终到达第 $N$ 个点。你可以跳过一些点，但是如果你一共跳过了 $C$ 个点，那么你将受到 $2^{C-1}$ 的惩罚。设 $s$ 为你走过的距离加上跳过点的惩罚，问 $s$ 最小为多少。

# 做法
考虑 dp。设 $f_{i,k}$ 表示当前到达了第 $i$ 个点，一共跳过了 $k$ 个点。则直接走的状态转移方程为：

$$
f_{i,k}=f_{i-1,k}+dis(i,i-1)
$$

从第 $j$ 个点跳过中间的点，到达第 $i$ 个点的状态转移方程为：

$$
f_{i,k}=f_{j,k-(i-j-1)}+dis(i,j)
$$

然后统计答案时计算跳过的点对答案的贡献，即 $f_{i,k}+2^{k-1}$ 的最小值。

因为点的坐标 $0 \leq X_i,Y_i \leq 10^4$，所以直接走的路程不超过 $\sqrt{2} \times 10^8$。而 $2^{30} > 10^8$，所以我们最多只能跳过 $30$ 个点。（其实因为点不能重合，所以直接走的最大路程小于 $\sqrt{2} \times 10^8$，我们只计算跳过 $25$ 个点也可以通过。时间复杂度为 $O(n^2)$，可以通过。

# 代码
[赛时版本](https://www.luogu.com.cn/paste/mpo5rgi8)

赛后更简洁的做法：

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int n,x[10005],y[10005];
double f[10005][30];
double dis(int i,int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        for(int j=0;j<=25;j++)f[i][j]=1e9;
    }
    f[1][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<min(i,25);j++)f[i][j]=min(f[i][j],f[i-1][j]+dis(i,i-1));
        for(int j=1;j<i-1;j++){
            for(int k=i-j-1;k<=25;k++){
                f[i][k]=min(f[i][k],f[j][k-(i-j-1)]+dis(i,j));
            }
        }
    }
    double ans=f[n][0];
    for(int i=1;i<=25;i++){
        ans=min(ans,f[n][i]+pow(2,i-1));
    }
    printf("%.6lf",ans);
    return 0;
}
```

---

## 作者：CarroT1212 (赞：1)

赛时被 D 和 G 创死了没仔细看，血亏。

注意到跳过的检查点个数最大也就在 $30$ 左右（不然光罚时都有几十亿还不如不跳），所以直接设 $dp_{i,j}$ 为目前在第 $i$ 个检查点，跳过了 $j$ 个时的最小距离，枚举上一个没跳过的检查点和到这个检查点时跳过的检查点个数，简单转移即可，答案取 $dp_{n,i}$ 加上罚时的最小值。一套下来也就是个千倍常数（？）的 $O(n)$，能过。

最近遇到的这种牵扯到答案范围性质的题目还挺多的，以后多注意一下。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vo void()
using namespace std;
const ll N=1e4+7,M=47;
ll n;
ld x[N],y[N],dp[N][M],ans=1e18;
ld dist(ld xa,ld ya,ld xb,ld yb) { return sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)); }
int main() {
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++) scanf("%Lf%Lf",&x[i],&y[i]);
	for (ll i=0;i<N;i++) for (ll j=0;j<M;j++) dp[i][j]=1e18;
	dp[1][0]=0;
	for (ll i=2;i<=n;i++) for (ll j=0;j<min(i,M-1);j++) for (ll k=0;k<min(i-j,M-1);k++)
		if (k+j<M) dp[i][k+j]=min(dp[i][k+j],dp[i-j-1][k]+dist(x[i-j-1],y[i-j-1],x[i],y[i]));
	for (ll i=0;i<M;i++) ans=min(ans,dp[n][i]+(i?1ll<<i-1:0));
	printf("%.15Lf",ans);
	return 0;
}
```

---

## 作者：robertuu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc315_f)

比较简单的一道 dp，赛时居然没弄出来……

很显然可以想到 $dp[i][j]$ 表示到达 $i$ 点，进行了 $j$ 次罚时的最短路径，答案就是 $\min(dp[n][j]+2^{j-1})$，转移方程也很容易想到：$dp[i][j] = \min(dp[k][j-(i-k-1)]+\operatorname{dist}(i,k)$，$\operatorname{dist}$ 为欧几里得距离。

但是这个转移方程是 $O(n^3)$ 的，不能 AC。

我们可以发现，罚时是指数增长的，考虑不进行罚时的最长情况，每两个点的距离最大时 $\sqrt2 \times10^4$，总距离最长是 $10^8 \times \sqrt2$，将其看成 $10^9$ 肯定不会错。这表示，如果你跳过了超过 $30$ 个点，哪怕距离为 $0$，也要一定不是答案。因此可以将 $j$ 的枚举限制在 $0 \le j \le 30$，$k$ 的枚举限制在 $i-30 \le k < i$，总复杂度为 $O(nlog^2n)$，可以 AC

AC code：
```cpp
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
struct point {int x,y;} a[10001];
double dis(point x,point y) {return sqrt(1.0*(x.x-y.x)*(x.x-y.x)+1.0*(x.y-y.y)*(x.y-y.y));}
double dp[10001][40];
int main()
{
	int n; scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(int i = 1;i <= n;i++)
		for(int j = 0;j <= 30;j++)
			dp[i][j] = 1e10;
	dp[1][0] = 0;
	for(int i = 2;i <= n;i++)
		for(int j = max(1,i-30);j < i;j++)
			for(int k = 0;k <= min(30,i-1);k++)
			{
				if(k-i+j+1 < 0) continue;
				dp[i][k] = min(dp[i][k],dp[j][k-i+j+1]+dis(a[i],a[j]));
			}
	double ans = dp[n][0];
	for(int i = 1;i <= 30;i++)
		ans = min(ans,dp[n][i]+pow(2,i-1));
	printf("%.7f\n",ans);
	return 0;
}
```


---

## 作者：Nwayy (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Nwayy/p/17646900.html)

题意：给定 $n$ 个点在平面上的位置，你需要从 $1$ 号点走到 $n$ 号点，两点间距离为欧几里得距离，你可以走的过程中你可以跳过某些点（即不用到达这个点）直接跳到下一个点，记你总共有 $k$ 个点选择跳过，那么总答案要加上 $2^{k-1}$，若 $k=0$ 则不用加。最小化总的欧几里得距离和额外答案之和。$1 \le n \le 10^4$，值域 $1 \le x_{i},y_{i} \le 10^4$。

这看第一眼很 dp 啊。

首先指数增长趋势非常快，题目又没要求取模，我们需要先考虑 $k$ 的大致范围。

假设我们全都不跳过，额外惩罚为 $0$，那么最大欧几里得距离即不断在地图两个边界跳，最大可能为 $\sqrt{(10^8+10^8)} \times n$，大概也就 $10^8$ 左右，那你的 $k$ 一旦超过 $\log(10^8)$ 必然不优。我们 $k$ 上界取到 $40$ 也无所谓。

那么就可以直接上 dp 了，由于我是 dp 菜狗所以写了记搜。设 $f_{i,j}$ 表示跳到第 $i-1$ 个点一共跳过了 $j$ 个点的最小代价，$\mathrm{dist}(i,j)$ 表示 $i$ 点和 $j$ 点的欧几里得距离。则有转移：

$$f_{k,j}=\min_{i=1}^{\min{(n-k,30)}} \mathrm{dfs}(i+k,j+i-1)+\mathrm{dist}(k,i+k)$$

是不是这样写公式啊（逃

当跳过的点数超过了限制记得及时剪枝，设钦定的剪枝边界为 $V$，那么总复杂度为 $O(nV^2)$，可以通过。

```
#include<bits/stdc++.h>
using namespace std;
#define N 10005
int n,m,i,j;
long double dis[N],a[N],b[N],ans=1000000000.00,qp[65],f[N][65];
long double solve(int x,int y){
	return sqrt((a[x]-a[y])*(a[x]-a[y])+(b[x]-b[y])*(b[x]-b[y]));
}
long double dfs(int k,int cnt){
	if(k==n){
		if(cnt==0) return 0.0;
		return qp[cnt-1];
	}
	if(f[k][cnt]!=-1.0) return f[k][cnt];
	long double Mx=1000000000000000.0;
	for(int i=1;i+k<=n;i++){
		if(cnt+(i-1)>30) break;
		Mx=min(Mx,dfs(i+k,cnt+i-1)+solve(k,k+i));
	}
	return f[k][cnt]=Mx;
} 
int main(){
	qp[0]=1.0;for(i=1;i<=60;i++) qp[i]=qp[i-1]*2.0;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%Lf%Lf",&a[i],&b[i]);
	for(i=1;i<=n;i++){
		for(j=0;j<=60;j++) f[i][j]=-1.0;
	}
	ans=dfs(1,0);
	printf("%.20Lf",ans);
	return 0;
}
```

---

## 作者：刘辰雨 (赞：1)

# 0x00 译

对于平面坐标上 $n$ 个点，输出从 $1$ 走到 $n$ 的**代价**。两点直线距离为欧几里得距离。

正常来讲，你的路径应该为 $1 \to 2\to 3 \to \dots \to (n-1)\to n $，你的代价即为你走过的距离。

但是你**被允许跳过一些点**，使路径变为 $1\to 2\to \dots \to (x-1) \to (x+1) \to \dots \to (n-1) \to n$，跳过的点数不限，但 $1$ 号点和 $n$ 号点不能被跳过。

跳过操作需要花费，此时你的**代价**为你走过的距离加跳过产生的花费。

跳过的花费如下定义：

对于整个旅途，如果你跳过 $c$ 个点，设花费为 $S$，

- $c=0\;\;\;\;S=0$
- $c>0\;\;\;\;S=2^{c-1}$

输出从 $1$ 走到 $n$ 的最小**代价**。 

___

$\textit{Translate by Rain.}$

# 0x01 解

定义 $\text{DP}$ 状态 $dp_{i, k}$ 表示从 $1$ 到 $i$，保证不跳过 $1$ 和 $i$，目前跳过 $k$ 个的最小代价，转移 $\mathcal{O}(n)$， 时间复杂度 $\mathcal{O}(n^2)$。

考虑性质，不难发现最多跳过 $30$ 个左右，否则不优。转移时不再枚举 $1$ 到 $i-1$，仅枚举 $i$ 的前 $30$ 个左右转移，常数转移，时间复杂度 $\mathcal{O}(n)$。

# 0x02 码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

namespace code_namespace {
	int n;
	double x[10004], y[10004];
	double dp[10004][34];
	double dis(int a, int b) {
		return sqrt((x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]));
	}
	long long w(int k) {
		if(k < 0) return 0;
		else return 1ll << k;
	}
	
	int main() {
		scanf("%d", &n);
		for(int i = 1 ; i<= n ; i++) {
			scanf("%lf%lf", &x[i], &y[i]);
		}
		for(int i = 1 ; i<= n ; i++) {
			for(int j = 0 ; j < 34 ; j++)
				dp[i][j] = 1e12;
		}
		dp[1][0] = 0;
		for(int i = 2 ; i <= n ; i++) {
			for(int k1 = 0 ; k1 < 34; k1++) {
				for(int k2 = 0 ; k2 < 34 ; k2++) {
					int j = i-k2-1;
					if(j <= 0 || k1+k2 > 33) continue;
					dp[i][k1+k2] = min(dp[i][k1+k2], dp[j][k1] + dis(i, j));
				}
			}
		}
		double ans = 1e12;
		for(int k = 0 ; k < 34 ; k++) {
			ans = min(ans, dp[n][k] + w(k-1));
		}
		printf("%.20lf", ans);
		return 0;
	}
}

int main() {
	return code_namespace::main();
}
```

[Atcoder AC记录](https://atcoder.jp/contests/abc315/submissions/44777441)

---

## 作者：Y2y7m (赞：0)

发现 $2$ 的次幂增长迅速，所以我们可以知道跳过的点不超过某一定值，如果超过某定值就会大于一个不跳过，保守起见，我设定这个定值为 $60$。

然后就可以 $\text{dp}$ 了，设状态 $f_{i,j}$ 为到第 $i$ 个点，跳过了 $j$ 个点所需的最小费用，转移则为： 

$$f_{i,j}=\min_{k=1}^{k\leq j,k\leq60}{\{f_{i-k-1,j-k}+dis(i-k-1,i)\}}$$

$dis_{i,j}$ 为点 $i$ 到点 $j$ 的距离。

注意要单独计算 $f_{i,0}$。

---

## 作者：Hellsing_Alucard (赞：0)

## 题意：

>有 $N$ 个点，你从第一个点出发，要按顺序经过他们，最终到达第 $N$ 个点。你可以跳过一些点，但是如果你一共跳过了 $C$ 个点，那么你将受到  $2^{C-1}$ 的罚时，求最少的时间。


## solve：

因为 $2^{14}> N$，所以最多跳过 $15$ 个点。

考虑 DP，令 $f_{i,j}$ 表示到第 $i$ 个点，一共跳过了 $j$ 个点的用时（不用加上罚时，因为罚时可以在最后进行统计）。

则有

$$f_{i,j}=\min(f_{i-k,j-k+1}+dis(i-k,i))$$

最后再求出最小值就行了。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define ull unsigned long long
#define ldb long double
#define db double
#define i128 __int128
#define up(a,b,c) for(int a=b;a<=c;a++)
#define dn(a,b,c) for(int a=b;a>=c;a--)
#define pii pair<int,int>
#define pdd pair<db,db>
#define lc k<<1
#define rc k<<1|1
#define fi first
#define se second
#define i16 short

const int N=3e5+100,M=2e6+100;
const int mod=998244353;
const int inf=1e17;

namespace IO{
	inline int read(){
		char c=getchar();int x=0,fh=0;
        while(c<'0'||c>'9'){fh|=c=='-';c=getchar();}
        while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
        return fh?-x:x;
	}
	inline void wt(int x){
		if(x<0){x=-x;putchar('-');}
		if(x>9)wt(x/10);
		putchar((x%10)^48);
	}
	inline void write(int x,bool op){
		wt(x);
		putchar(op?'\n':' ');
	}
}using namespace IO;
int n;
pdd p[N];
inline db dis(pdd a,pdd b){
    return (db)sqrt((db)(a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}
db dp[13050][25];
signed main(){
    n=read();
    int x,y;
    up(i,1,n){
        x=read();y=read();
        p[i]={x,y};
    }
    db sum=0;
    int c=0;
    memset(dp,0x42,sizeof dp);
    up(i,0,20)dp[1][i]=0;
    up(i,2,n){
        up(j,0,20){
            up(k,1,min(j+1,i-1)){
                dp[i][j]=min(dp[i][j],dp[i-k][j-k+1]+dis(p[i],p[i-k]));
            }
        }
    }
    db minl=inf;
    up(i,1,20){
        minl=min(dp[n][i]+pow(2,i-1),minl);
    }
    minl=min(minl,dp[n][0]);
    printf("%.9lf",minl);
    return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路

可以很简单的写出来一个暴力的 $O(n^2)$ 的暴力 dp。

这里简单放一下暴力的方程，设 $dp_{i,j}$ 表示走到里第 $i$ 个点然后跳过 $j$ 个不算跳过代价的答案。

$$dp_{i,j}=dp_{i-1,j}+\operatorname{dis}(i,j)$$

$$dp_{i,j}=\min(dp_{k,j-(i-k-1)}+\operatorname{dis}(i,k))$$

最后统计答案的时候加上 $2^j$。

然后发现路径最大不会超过 $2^{29}$，那么向回找的时候就可以只找 $29$ 个以内的。

复杂度就变成了 $O(\log V\log V n)$ 的了。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000, K = 30;
int x[maxn], y[maxn];
double dp[maxn][32];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = 1e10;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = i + 1; k < n && j + k - i - 1 < K; k++) {
                int d = j + k - i -  1;
                dp[k][d] = min(dp[k][d], dp[i][j] + sqrt((x[i] - x[k]) * (x[i] - x[k]) + (y[i] - y[k]) * (y[i] - y[k])));
            }
        }
    }
    double ans = 1e10;
    for (int i = 0; i < K; i++) {
        ans = min(ans, dp[n - 1][i] + (i == 0 ? 0 : 1 << (i - 1)));
    }
    cout << fixed << ans << "\n";
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

给定 $n$ 个点的坐标 $(x_i,y_i)$，你需要从第一个点到达第 $n$ 个点，如果有 $k$ 个点没有经过，定义 $f(k)$ 为：

$$f(k)=\begin{cases}0&k=0\\2^{k-1}&k \ne 0\end{cases}$$

那么你的得分将会是从第 $1$ 点走到第 $n$ 个点的欧几里得距离加上 $f(k)$，求出你的最小得分。

### 思路：

看到这个数据范围，于是考虑动态规划，但是我们发现，直接定义 $dp_{i,j}$ 表示从 $i$ 个走到第 $j$ 个点的最小得分，计算的时间复杂的是 $O(n^3)$ 的。

于是我们需要考虑优化，我们发现 $f(k)$ 的值未免太大了，如果 $k$ 是个成百上千的话，$2$ 的这么多次幂得分你将会拿到特别高，于是我们计算一下 $k$ 在什么范围以内会对答案产生贡献，大概是 $30$ 左右，毕竟我们的得分最高大概是 $10^9$ 次方差不多。

所以我们考虑重新定义状态，设 $dp_{i,j}$ 表示从第一个点到第 $i$ 个点中我们有 $j$ 个点没有经过的最小得分，这样第一维是 $n$ 级别，第二维只是只是 $30$ 左右，而且因为是最小得分，我们初始要全部赋值为极大值。

现在考虑计算状态转移方程，初始肯定是 $dp_{1,0}=0$，我们发现，对于每一个点，我们需要根据它前面的 $30$ 个点来转移，太多的话会导致得分太大，然后枚举一个 $k$，表示到从 $1$ 号点到这个点有 $k$ 个点不经过。

那么很容易得到状态转移方程：

$$dp_{i,k}=\min(dp_{i,k},dp_{j,k-(i-j-1)}+dist(i,j))$$

其中 $dist(i,j)$ 表示直接从第 $i$ 个点走到第 $j$ 个点的欧几里得距离，其中 $k$ 的下界为 $i-j-1$（就是 $i$ 号点到 $j$ 号点之间点的数量），上界就是 $30$。

最后我们取 $\min\limits_{i=0}^{30}(dp_{n,i}+\begin{cases}0&i=0\\2^{i-1}&i \ne 0\end{cases})$ 作为最终的答案。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100,M=40;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n;
db Min=LONG_LONG_MAX;
ll x[N],y[N];
db dp[N][M];
db f(db x1,db y1,db x2,db y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)
		  ans*=a;
		a*=a;
		b>>=1; 
	}
	return ans;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
	  for(int j=0;j<M;j++)
	    dp[i][j]=1145141919810;
	for(int i=1;i<=n;i++){
		x[i]=read();
		y[i]=read();
	}
	dp[1][0]=0;
	for(int i=1;i<=n;i++)
	  for(int j=max(i-31,1);j<i;j++)
	    for(int k=(i-j-1);k<=30;k++)
		  dp[i][k]=min(dp[i][k],dp[j][k-(i-j-1)]+f(x[i],y[i],x[j],y[j]));
	Min=dp[n][0];
	for(int i=1;i<=30;i++)
	  Min=min(Min,dp[n][i]+qpow(2,i-1));
	printf("%.10lf\n",Min);
	return 0;
}
```

---

