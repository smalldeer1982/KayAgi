# [ABC298G] Strawberry War

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc298/tasks/abc298_g

長方形のケーキがあります。このケーキは $ H $ 行 $ W $ 列に並ぶ区画に分かれていて、上から $ i $ 行目、左から $ j $ 列目の区画にはイチゴが $ s_{i,j} $ 個載っています。

あなたは $ T $ 回の切断を行ってケーキを $ T+1 $ 切れに分割することにしました。各回の切断は、次のいずれかの方法で行います。

- 現存するケーキであって、区画の行の数が $ 2 $ 以上であるものを選ぶ。さらに、そのケーキから隣接する $ 2 $ 行を選び、その境界でケーキを切断してより小さなケーキ $ 2 $ 切れに分割する。
- 現存するケーキであって、区画の列の数が $ 2 $ 以上であるものを選ぶ。さらに、そのケーキから隣接する $ 2 $ 列を選び、その境界でケーキを切断してより小さなケーキ $ 2 $ 切れに分割する。
 
あなたの目標は、分割後のケーキに載ったイチゴの数をできるだけ均等にすることです。  
 分割後の $ T+1 $ 切れのケーキに載ったイチゴの個数を $ x_1,x_2,\ldots,x_{T+1} $ として、そのうち最大のものを $ M $、最小のものを $ m $ とするとき、$ M－m $ がとりうる最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 6 $
- $ 1\ \leq\ T\ \leq\ HW-1 $
- $ 0\ \leq\ s_{i,j}\ \leq\ 10^{16} $
- 入力はすべて整数
 
### Sample Explanation 1

下のように切り分けると左上のケーキに $ 2 $ 個、左下のケーキに $ 4 $ 個、中央のケーキに $ 4 $ 個、右上のケーキに $ 4 $ 個、右下のケーキに $ 3 $ 個のイチゴが載った状態になり、イチゴの個数の最大値と最小値の差は $ 4-2=2 $ となります。差をこれよりも小さくすることは出来ないため、$ 2 $ が答えとなります。 !\[\](https://img.atcoder.jp/abc298/6d6a4c5fc7ac2723af8e8b30e48957da.png)

## 样例 #1

### 输入

```
2 3 4
2 3 4
4 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2 2 3
0 0
0 0```

### 输出

```
0```

# 题解

## 作者：_•́へ•́╬_ (赞：8)

## 思路

枚举最小值。

然后做 dp，`f[i][j][k][l][p]` 表示左上角为 $(i,j)$，右下角为 $(k,l)$，切 $p$ 刀的最大值最小是多少。

转移枚举刀切哪以及两边的刀数如何分配。

直接做是 $\mathcal O(n^{13})$ 的，但是因为 $\frac 1 2$ 甚至是 $\frac 1 4$ 的常数随地捡，可以通过。

## code

3.6s。

```cpp
#include<stdio.h>
#include<string.h>
#define int long long
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
int n,m,p,a[7][7],s[7][7],ans[7][7][7][7][36],minn,qwq=1ll<<61;
inline void min(int&x,const int&y){if(x>y)x=y;}
inline int max(const int&x,const int&y){return x>y?x:y;}
inline int dfs(const int&i,const int&j,const int&k,const int&l,const int&p)
{
	if(p>(k-i+1)*(l-j+1)-1)return 1ll<<61;
	int&wr=ans[i][j][k][l][p];
	if(~wr)return wr;
	wr=1ll<<61;
	if(!p)
	{
		if(s[k][l]-s[i-1][l]-s[k][j-1]+s[i-1][j-1]>=minn)
			wr=s[k][l]-s[i-1][l]-s[k][j-1]+s[i-1][j-1];
		return wr;
	}
	for(int o=i;o<k;++o)for(int q=0;q<=p-1;++q)
		min(wr,max(dfs(i,j,o,l,q),dfs(o+1,j,k,l,p-1-q)));
	for(int o=j;o<l;++o)for(int q=0;q<=p-1;++q)
		min(wr,max(dfs(i,j,k,o,q),dfs(i,o+1,k,l,p-1-q)));
	return wr;
}
main()
{
	read(n);read(m);read(p);
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)
		read(a[i][j]),s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
	for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)
		for(int k=i;k<=n;++k)for(int l=j;l<=m;++l)
		{
			minn=s[k][l]-s[i-1][l]-s[k][j-1]+s[i-1][j-1];
			memset(ans,-1,sizeof(ans));
			if(dfs(1,1,n,m,p)>=0)min(qwq,dfs(1,1,n,m,p)-minn);
		}
	printf("%lld",qwq);
}
```

## 剪枝

题解提到了以下剪枝：

数据范围中提到了 $1\leq T\leq HW-1$，依此添加剪枝 $p\leq(k-i+1)\times(l-j+1)-1$，可加速至 0.6s。

---

## 作者：EXODUS (赞：3)

# Part 1：前言
简单的 dp 题，很难想象我场上在想什么。下文中令 $n,m$ 分别代表原题面中的 $h,w$。

$n,m\leq 6$ 很容易让人感觉是个指数级算法，但是这题是高贵的 $O(n^{13})$。

# Part 2：正文

首先注意到切一刀以后会变成两个子矩形，因此不难现有基础的五维状态 $f(u,d,l,r,t)$ 表示对于子矩形 $(u,d,l,r)$，切 $t$ 刀后的极差最小是多少。但这样显然没法转移，因为 dp 的东西同时涉及到最大值和最小值两个量，不妨拉出一个到状态里，因此有基本状态 $f(u,d,l,r,t,v)$ 表示对于子矩形 $(u,d,l,r)$，切 $t$ 刀后最小值是 $v$，最大值最小是多少。

看起来最后一维和值域相关，但是因为 $v$ 一定是某个子矩形的元素和，因此本质不同的只有不超过 $\frac{nm(n+1)(m+1)}{4}$ 个，所以最后一维离散化以后会变成一个 $n^4$ 量级的东西。这个状态看起来非常吓人，大概是 $O(n^{10})$ 量级的，开的时候要精打细算一点，尤其是最后一维不要直接开 $n^4$。

然后考虑转移，枚举切了哪一刀，切完这一刀左边矩形要切多少次，递归到左右子矩形去做。最后想想统计答案，即为 $f(u,d,l,r,t,v)-v$。

分析一下时间复杂度，状态数是 $O(n^{10})$，转移要枚举行或者列，以及切的次数，因此总复杂度是 $O(n^{13})$。但是考虑到最后一维的 $\frac{1}{4}$ 常数，子矩形本身自带的 $\frac{1}{4}$ 常数等，因此可以通过本题。

# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
    int ans=0,flag=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
    while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
    return ans*flag;
}
template<typename T>
void read(T &x){
    x=0;T flag=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')flag=-1;ch=getchar();}
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x*=flag;
}
 
const int N=6+2,N2=6*6+2,N4=5e2+2;
int n,m,t;
ll pre[N][N];
ll val[N*N*N*N],cnt;
 
ll f[N][N][N][N][N2][N4];
bool vis[N][N][N][N];
 
void chk(ll &x,ll y){if(x>y)x=y;}
 
void dfs(int u,int d,int l,int r){
    if(vis[u][d][l][r])return;
    ll sum=pre[d][r]-pre[d][l-1]-pre[u-1][r]+pre[u-1][l-1];
    for(int i=1;i<=cnt;i++)if(sum>=val[i])f[u][d][l][r][0][i]=sum;
    for(int i=1;i<=t&&i<=(r-l+1)*(d-u+1)-1;i++){
        for(int j=u;j<d;j++){
            dfs(u,j,l,r),dfs(j+1,d,l,r);
            for(int k=0;k<i;k++)for(int p=1;p<=cnt;p++)
                chk(f[u][d][l][r][i][p],max(f[u][j][l][r][k][p],f[j+1][d][l][r][i-k-1][p]));
        }
        for(int j=l;j<r;j++){
            dfs(u,d,l,j),dfs(u,d,j+1,r);
            for(int k=0;k<i;k++)for(int p=1;p<=cnt;p++)
                chk(f[u][d][l][r][i][p],max(f[u][d][l][j][k][p],f[u][d][j+1][r][i-k-1][p]));
        }
    }
    vis[u][d][l][r]=1;
    return;
 
}
 
int main(){
    read(n),read(m),read(t);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            read(pre[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            pre[i][j]=pre[i][j]+pre[i][j-1];
    for(int j=1;j<=m;j++)
        for(int i=1;i<=n;i++)
            pre[i][j]=pre[i][j]+pre[i-1][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=i;k<=n;k++)
                for(int l=j;l<=m;l++)
                    val[++cnt]=pre[k][l]-pre[i-1][l]-pre[k][j-1]+pre[i-1][j-1];
    sort(val+1,val+cnt+1);
    memset(f,0x3f,sizeof(f));
    dfs(1,n,1,m);
    ll ans=2e18+7;
    for(int i=1;i<=cnt;i++)chk(ans,f[1][n][1][m][t][i]-val[i]);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：igAC (赞：2)

闲话写在前面，因为 $O(n^{13})$ 跑 93ms 太抽象了，于是写一篇题解。

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc298_g)

[AT link](https://atcoder.jp/contests/abc298/tasks/abc298_g)

简要题意：

$n \times m$ 的网格，每次将一个部分竖着或横着切为两个部分，每个部分的权值定义为所有元素的和，最小化最大权值减最小权值的值，并输出。

# $\text{Solution}$

首先一个经典的 trick 就是在每个部分权值有下限的情况下最小化最大值。

然后我们发现 $n,m$ 非常非常小，所以我们可以暴力枚举最小值，只有 $\binom{n}{2} \times \binom{m}{2}$ 种（所有子矩阵）。

然后因为要最小化最大值于是考虑 dp。

设 $f_{x_1,y_1,x_2,y_2,p}$ 表示 $(x_1,y_1)$ $(x_2,y_2)$ 这个矩阵中分为 $p$ 个部分的最小最大值。

转移是十分显然的，枚举横切线、竖切线、分成的部分数。

最后的理论时间复杂度为 $O(n^{13})$，但是完全跑不满，于是 93ms 过了这道题（目前洛谷 rk1）。

# $\text{Code}$

代码很好理解，个人觉得码风还能看。

```cpp
#include<bits/stdc++.h>
#define LLINF 1e18
#define int long long
#define N 10
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,t,a[N][N],buc[N*N*N*N],tot,f[N][N][N][N][N*N],ans=LLINF,sum[N][N];
int gt(int x1,int y1,int x2,int y2){return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];}
signed main(){
	n=read(),m=read(),t=read();
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) a[i][j]=read();
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
	for(int x1=1;x1<=n;++x1) for(int x2=x1;x2<=n;++x2) for(int y1=1;y1<=m;++y1) for(int y2=y1;y2<=m;++y2) buc[++tot]=gt(x1,y1,x2,y2);
	sort(buc+1,buc+tot+1),tot=unique(buc+1,buc+tot+1)-(buc+1);
	for(int i=1;i<=tot;++i){
//		printf("When the Minimum number is %lld\n",buc[i]);
		for(int x1=1;x1<=n;++x1){
			for(int y1=1;y1<=m;++y1){
				for(int x2=x1;x2<=n;++x2){
					for(int y2=y1;y2<=m;++y2){
						for(int p=1;p<=n*m;++p) f[x1][y1][x2][y2][p]=LLINF;
						if(gt(x1,y1,x2,y2)>=buc[i]) f[x1][y1][x2][y2][1]=gt(x1,y1,x2,y2);
					}
				}
			}
		}
		for(int len1=1;len1<=n;++len1){
			for(int len2=1;len2<=m;++len2){
				if(len1==1 && len2==1) continue;
				for(int x1=1;x1+len1-1<=n;++x1){
					for(int y1=1;y1+len2-1<=m;++y1){
						int x2=x1+len1-1,y2=y1+len2-1;
//						printf("When (%lld,%lld),(%lld,%lld)\n",x1,y1,x2,y2);
						for(int p=1;p<=(x2-x1+1)*(y2-y1+1);++p){
							for(int k=x1;k<x2;++k) for(int q=1;q<p && q<=(k-x1+1)*(y2-y1+1);++q) f[x1][y1][x2][y2][p]=min(f[x1][y1][x2][y2][p],max(f[x1][y1][k][y2][q],f[k+1][y1][x2][y2][p-q]));
							for(int k=y1;k<y2;++k) for(int q=1;q<p && q<=(x2-x1+1)*(k-y1+1);++q) f[x1][y1][x2][y2][p]=min(f[x1][y1][x2][y2][p],max(f[x1][y1][x2][k][q],f[x1][k+1][x2][y2][p-q]));
//							printf("%lld ",f[x1][y1][x2][y2][p]);
						}
//						puts("");
					}
				}
			}
		}
		ans=min(ans,f[1][1][n][m][t+1]-buc[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：0x3F (赞：1)

~~NOIP 考前写题解涨 rp~~

题目大意：给一个 $n\times m(n,m\le6)$ 的矩阵 $A$，分为 $t+1$ 个子矩阵，求这些子矩阵元素和的极差的最小值，解法与值域无关。

考虑 DP。以下认为 $n,m$ 同阶。

首先枚举矩阵的最小值 $M$，由于 $M$ 一定对应一个子矩阵，这样是 $O(n^4)$ 的。

然后记 $dp_{u,d,l,r,k}$ 表示将矩阵 $[u,d]\times[l,r]$ 切为 $k$ 块，且最小的一块 $\ge M$ 时，最大的一块最小是多少。这样，$u,d,l,r$ 的范围分别是 $O(n)$，$k$ 的范围是 $O(n^2)$，总状态数为 $O(n^6)$。

我们考虑是横着切还是竖着切，以及枚举切在哪个位置，然后枚举这两块分别又分为 $i$ 和 $k-i$ 块，于是我们可以得到转移方程：

$$dp_{u,d,l,r,c}=\min\begin{cases}\min_{1\le i<k,u\le x<d}\max(dp_{u,x,l,r,i},dp_{x+1,d,l,r,k-i})\\\min_{1\le i<k,l\le x<r}\max(dp_{u,d,l,x,i},dp_{u,d,x+1,r,k-i})\end{cases}$$

边界条件为：$dp_{u,d,l,r,1}=\sum_{i=u}^{d}\sum_{j=l}^{r}A_{i,j}$，当且仅当 $\sum_{i=u}^{d}\sum_{j=l}^{r}A_{i,j}\ge M$。

由于 $M$ 的总数为 $O(n^4)$，状态数为 $O(n^6)$，$i$ 为 $O(n^2)$，$x$ 为 $O(n)$，总时间复杂度为 $O(n^{13})$。这大约是 $1.3\times10^{10}$，怎么能过呢？

因为对于 $M$ 显然有 $\frac{1}{4}$ 的常数，对于状态的 $u,d,l,r$ 显然又有 $\frac{1}{4}$ 的常数，这样就变成了 $8.2\times 10^8$，暂且不考虑其他的常数，以 AtCoder 的少爷机的速度，$6$ 秒的时限，已经绰绰有余。事实上，最大的一个测试点只用了 $\texttt{810ms}$。

我们还可以考虑一个优化：显然 $(d-u+1)(r-l+1)<c$ 时，状态没有意义，这样就优化为了 $\texttt{143ms}$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, t, w;
long long cnt[8][8], sum[8][8][8][8], arr[450], dp[8][8][8][8][40], ans = 0x3F3F3F3F3F3F3F3Fll;
int main() {
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> cnt[i][j];
		}
	}
	for (int li = 1; li <= n; li++) {
		for (int ri = li; ri <= n; ri++) {
			for (int lj = 1; lj <= m; lj++) {
				for (int rj = lj; rj <= m; rj++) {
					for (int i = li; i <= ri; i++) {
						for (int j = lj; j <= rj; j++) {
							sum[li][ri][lj][rj] += cnt[i][j];
						}
					}
					arr[++w] = sum[li][ri][lj][rj];
				}
			}
		}
	}
	sort(arr+1, arr+w+1);
	w = unique(arr+1, arr+w+1) - arr - 1;
	for (int id = 1; id <= w; id++) {
		memset(dp, 0x3F, sizeof(dp));
		long long M = arr[id];
		for (int li = 1; li <= n; li++) {
			for (int ri = li; ri <= n; ri++) {
				for (int lj = 1; lj <= m; lj++) {
					for (int rj = lj; rj <= m; rj++) {
						if (sum[li][ri][lj][rj] >= M) {
							dp[li][ri][lj][rj][1] = sum[li][ri][lj][rj];
						}
					}
				}
			}
		}
		for (int c = 2; c <= t+1; c++) {
			for (int li = 1; li <= n; li++) {
				for (int ri = li; ri <= n; ri++) {
					for (int lj = 1; lj <= m; lj++) {
						for (int rj = lj; rj <= m; rj++) {
							if ((ri - li + 1) * (rj - lj + 1) < c) continue;
							for (int xi = li; xi < ri; xi++) {
								for (int d = 1; d < c; d++) {
									dp[li][ri][lj][rj][c] = min(dp[li][ri][lj][rj][c], max(dp[li][xi][lj][rj][d], dp[xi+1][ri][lj][rj][c-d]));
								}
							}
							for (int xj = lj; xj < rj; xj++) {
								for (int d = 1; d < c; d++) {
									dp[li][ri][lj][rj][c] = min(dp[li][ri][lj][rj][c], max(dp[li][ri][lj][xj][d], dp[li][ri][xj+1][rj][c-d]));
								}
							}
						}
					}
				}
			}
		}
		ans = min(ans, dp[1][n][1][m][t+1] - M);
	}
	cout << ans << endl;
}
```

---

## 作者：JWRuixi (赞：1)

~~/bx /bx /bx ?~~

### 题意

给定一个 $N \times M$ 的矩阵，对于每一个部分，你可以挑选相邻的行或列并将其切成两半。求切 $T$ 刀，所有部分内元素和的极差的最小值。

$n,m \le 6,s_{i,j} \le 10^{16}$。

### 分析

既然 $n,m$ 极小，那么可以考虑一些比较极端的做法，比如暴力 dp 。考虑到值域很大，但实际上最小值和最大值仅有 $\mathcal O((nm)^2)$ 中取值，我们不妨枚举最小值，再最小化最大值。

我们设 $f_{i,j,x,y,t}$ 表示矩形 $((i,j),(x,y))$ 切 $t$ 刀，每一部分都大于等于 $B$ 的前提下，所有部分最大值的最小值。转移枚举切哪里，左右切几刀。

$B$ 共 $(nm)^2$ 种有用的取值，状态数 $\mathcal O((nm)^2T)$，转移 $\mathcal O((n+m)T)$，那么总复杂度 $\mathcal O((n+m)(nm)^4T^2)$，但是发现略微剪枝后合转移和状态数都很少，所以可过。

### Code

提交记录：<https://atcoder.jp/contests/abc298/submissions/43495954>

---

## 作者：ダ月 (赞：1)

### 题意概要：

给定一个 $H\times W$ 的矩阵，对于每一部分，我们可以挑选相邻的行或列中间切一道，变成两个部分。将这个矩阵分成 $T+1$ 个部分，对于每个部分，权值为部分内元素的和。要求最小化最大值减最小值的差。

### 题目分析：

考虑动态规划。从题面来看，这道题要求切割。那么从反方向来想，就是将 $H\times W$ 个小矩形合并成 $T+1$ 个矩形。变成了区间合并问题，考虑区间动规。

我们钦定每次计算钦定一部分算做最小值，为 $R$。$f_{l_1,r_1,l_2,r_2,p}$ 为当前从 $(l_1,r_1)$ 到 $(l_2,r_2)$ 中所有矩形已经合并成 $p$ 个矩阵时，在满足大于等于最小值的情况下最小的和。

记 $s_{l_1,r_1,l_2,r_2}$ 为从 $(l_1,r_1)$ 到 $(l_2,r_2)$ 的和。先考虑边界情况，即

$\begin{aligned}f_{l_1,r_1,l_2,r_2,0}=\left\{
	\begin{array}{l}
    	+\infty&,s_{l_1,r_1,l_2,r_2}<R\\
      s_{l_1,r_1,l_2,r_2} &,s_{l_1,r_1,l_2,r_2} \ge R
    \end{array}
  \right.
 \end{aligned}
 $

考虑转移：

$\begin{aligned}f_{l_1,r_1,l_2,r_2,p}=\min_{i=0}^{p-1}\{\max\{f_{l_1,x,l_2,r_2,i},f_{x+1,r_1,l_2,r_2,p-i-1}\},\max\{f_{l_1,r_1,l_2,y,i},f_{l_1,r_1,y+1,r,p-i-1}\}\}\end{aligned}$

其中 $x\in[l_1,r_1),y\in[l_2,r_2)$。

代码太丑，就不放了。

---

