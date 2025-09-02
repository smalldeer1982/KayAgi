# [ABC282G] Similar Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc282/tasks/abc282_g

$ (1,2,\ldots,N) $ の順列を、以下では単に順列と呼びます。

二つの順列 $ A=(A_1,A_2,\ldots,A_N),B=(B_1,B_2,\ldots,B_N) $ にたいして、**類似度** を以下の条件を満たす $ 1 $ 以上 $ N-1 $ 以下の整数 $ i $ の個数で定めます。

- $ (A_{i+1}-A_i)(B_{i+1}-B_i)\ >\ 0 $

二つの順列の組 $ (A,B) $ であって、類似度が $ K $ であるものの個数を素数 $ P $ で割ったあまりを答えてください。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 100 $
- $ 0\leq\ K\ \leq\ N-1 $
- $ 10^8\ \leq\ P\ \leq\ 10^9 $
- $ P $ は素数
- 入力は全て整数である

### Sample Explanation 1

例えば条件を満たす順列の組の一つとして、以下のものが考えられます。 - $ A=(1,2,3) $ - $ B=(1,3,2) $ この例では、$ (A_2\ -\ A_1)(B_2\ -B_1)\ >\ 0,\ (A_3\ -\ A_2)(B_3\ -B_2)\ <\ 0 $ であることから、$ A $ と $ B $ の類似度は $ 1 $ だとわかります。

### Sample Explanation 2

個数を $ P $ で割ったあまりを答えてください。

## 样例 #1

### 输入

```
3 1 282282277```

### 输出

```
16```

## 样例 #2

### 输入

```
50 25 998244353```

### 输出

```
131276976```

# 题解

## 作者：ktq_cpp (赞：6)

这道题相当于 [AT_dp_T](https://www.luogu.com.cn/problem/AT_dp_t) 的强化版，如果没做过的话可以先去看一看那道题。

首先我们不难可以列出方程 $dp[i][j][a][b]$ 表示在排列 $A$ 中第 $i$ 个数的排排名从小到大为 $a$ 以及在排列 $B$ 中第 $i$ 个数的排名从小到大为 $b$ 此时相似度为 $j$ 的方案数。

不难能想出转移方程：

$dp[i][j][a][b]=\sum^{i-1}_{x=a}\sum^{b-1}_{y=1} dp[i-1][j][x][y]+\sum^{a-1}_{x=1}\sum^{i-1}_{y=b} dp[i-1][j][x][y]$

$dp[i][j][a][b]=\sum^{a-1}_{x=1}\sum^{b-1}_{y=1}dp[i-1][j-1][x][y]+\sum^{i-1}_{x=a}\sum^{i-1}_{y=a}dp[i-1][j-1][x][y]$

二维前缀和优化即可

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
const int N=105;
int dp[N][N][N][N],n,m,P;
int sum[N][N],ans;
signed main(){
	n=read(),m=read(),P=read();
	dp[1][0][1][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<i-1;j++){
			memset(sum,0,sizeof(sum));
			for(int a=1;a<i;a++){
				for(int b=1;b<i;b++){
					sum[a][b]=(sum[a][b-1]+sum[a-1][b]-sum[a-1][b-1]+dp[i-1][j][a][b])%P;
					sum[a][b]=(sum[a][b]+P)%P;
				}
			}
			for(int a=1;a<=i;a++){
				for(int b=1;b<=i;b++){
					dp[i][j][a][b]=(dp[i][j][a][b]+sum[i-1][b-1]-sum[a-1][b-1]+sum[a-1][i-1]-sum[a-1][b-1])%P;
					dp[i][j][a][b]=(dp[i][j][a][b]+P)%P;
				}
			}
			for(int a=1;a<=i;a++){
				for(int b=1;b<=i;b++){
					dp[i][j+1][a][b]=(dp[i][j+1][a][b]+sum[a-1][b-1]+sum[i-1][i-1]-sum[a-1][i-1]-sum[i-1][b-1]+sum[a-1][b-1])%P;
					dp[i][j+1][a][b]=(dp[i][j+1][a][b]+P)%P;
				}
			}
		}
	}
	rep(i,n){
		rep(j,n){
			ans=(ans+dp[n][m][i][j])%P;
		}
	}
	out(ans);
	return 0;
}

```


---

## 作者：lottle1212__ (赞：4)

# [Similar Permutation](https://www.luogu.com.cn/problem/AT_abc282_g)

观察题面，这是一道有关排列计数的问题。而对于排列问题，可以按照位置或值的具体值或相对值来 dp。而此题需要知道相邻位置两项的大小关系，则可以对每一个位置依次考虑其值在序列中的排名，即其相对的值。假设当前 dp 到位置 $i$，观察整个排列中的位置 $[1, i]$ 的部分离散化后的结果，就是一个 $[1, i]$ 的排列，而离散化后的值也就是其原先从小到大的排名。此时从排列 $[1, i-1]$（相对位置，即离散化后的）转移过来。通过加入位置 $i$ 的数，把 $[1, i-1]$ 的排列扩充到 $[1, i]$。按照大小顺序，把位置 $i$ 的数插在排列 $[1, i-1]$ 的 $i$ 个空隙中的任意一个。此时，如果事先记录下了位置 $i-1$ 的数在排列 $[1, i-1]$ 的相对位置，就容易知道两者的大小关系。而题中问了两个排列，则可以记录两者的相对位置。设 $dp_{i, j, k, l}$ 表示做到位置 $i$，$a_i$ 在 $[1, i]$ 的相对位置为 $j$，$b_i$ 在 $[1, i]$ 的相对位置为 $k$，相似度为 $l$ 的方案数。则有转移 $dp_{i, j, k, l}=\sum_{1\leq j'<j, 1\leq k'<k} dp_{i-1, j', k', l-1}+\sum_{1\leq j'<j, k\leq k'\leq i} dp_{i-1, j', k
', l}+\sum_{j\leq j'\leq i, 1\leq k'<k} dp_{i-1, j', k', l}+\sum_{j\leq j'\leq i, k\leq k'\leq i} dp_{i-1, j', k', l-1}$。这个式子再使用前缀和优化即可。时间复杂度 $O(n^3k)$。

```cpp
#define L(i, j, k) for (int i=(j); i<=(k); ++i)
const int N=110;
int n, kn, mod, dp[N][N][N][N];
signed main() {
	rd(n, kn, mod);
	dp[1][1][1][0]=1;
	L(i, 2, n) {
		L(j, 1, i) L(k, 1, i) L(l, 0, i-1) {
			if (l) dp[i][j][k][l]=((ll)dp[i][j][k][l]+dp[i-1][j-1][k-1][l-1]+dp[i-1][i-1][i-1][l-1]-dp[i-1][j-1][i-1][l-1]-dp[i-1][i-1][k-1][l-1]+dp[i-1][j-1][k-1][l-1])%mod;
			dp[i][j][k][l]=((ll)dp[i][j][k][l]+dp[i-1][j-1][i-1][l]-dp[i-1][j-1][k-1][l]+dp[i-1][i-1][k-1][l]-dp[i-1][j-1][k-1][l])%mod;
		}
		L(j, 1, i) L(k, 1, i) L(l, 0, i-1) dp[i][j][k][l]=(dp[i][j][k][l]+dp[i][j][k-1][l])%mod;
		L(j, 1, i) L(k, 1, i) L(l, 0, i-1) dp[i][j][k][l]=(dp[i][j][k][l]+dp[i][j-1][k][l])%mod;
	}
	printf("%d\n", (dp[n][n][n][kn]+mod)%mod);
	return 0;
}
```

---

## 作者：JWRuixi (赞：2)

~~/bx /bx /bx ?~~

### 题意

给定 $n,k,p$，求有多少排列对 $(A,B)$ 满足：恰有 $k$ 个 $i$，使得 $(A_{i+1}-A_i)(B_{i+1}-B_i)>0$；答案对 $p$ 取模。

### 分析

考虑我们要满足的是大小关系的限制，钦定一个点在全局的大小是复杂的，但是只关心它与当前存在的点的关系是 trivial 的，所以我们考虑插入式 dp。

设 $f_{i,j,x,y}$ 表示考虑到第 $i$ 个点，$A_i$ 在 $A_{1 \dots i}$ 中的排名为 $x$，$B_i$ 在 $B_{1 \dots i}$ 中的排名为 $y$，有 $j$ 个满足上述条件的点。转移就枚举下一个点是满足条件，还是不满足条件，那么就可以枚举它要插在哪儿，有：

$$f_{i,j,x,y}=\sum\limits_{(dx<x,dy<y)\lor (dx\ge x,dy\ge y)}f_{i-1,j-1,dx,dy}$$

$$f_{i,j,x,y}=\sum\limits_{(dx<x,dy\ge y)\lor (dx\ge x,dy<y)}f_{i-1,j,dx,dy}$$

显然的优化是二维前缀和、滚动数组，考虑到这样 dp 常数很小，且时限较宽，所以复杂度 $\mathcal O(n^4)$ 可过。

### Code

提交记录：<https://atcoder.jp/contests/abc282/submissions/43535866>。

---

## 作者：ask_silently (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc282_g)

# 状态分析

呃，先根据 ~~题目难度与题目标签~~ 数据范围判断出这是一道 DP，于是开始思考状态。

- 题目让我们自己构造排列，所以当前枚举的位置 $i$ 肯定不能少。

- 题目给出条件 $(A_{i+1}-A_i)(B_{i+1}-B_i)>0$，所以我们要知道两个排列相邻两数的大小关系，于是我们要知道两个排列当前位置填了什么数，所以再增加两维 $a,b$。

- 题目中还有一个条件是相似度必须为 $K$，所以第四维就是相似度 $k$。

至此，我们得到了 $dp$ 数组的状态，$dp_{i,k,a,b}$ 为当前已经构造了前 $i$ 个数的排列，相似度为 $k$，其中 $A$ 排列与 $B$ 排列的第 $i$ 位分别为 $a,b$。

# 转移分析

根据 $(A_{i+1}-A_i)(B_{i+1}-B_i)>0$ 可知，如果要使当前位置 $i$ 能造成贡献的话，则 $A,B$ 两个排列中后一个位置都大于前一个位置，或都小于前一个位置。为了确保我们得到的是排列，我们将 $A$ 排列前 $i-1$ 位大于等于 $a$ 的数都加上 $1$，对 $B$ 数组也执行此操作。于是可以得到：

$$dp_{i,k,a_1,b_1}=\sum\limits_{a_2=1}^{a_1-1} \sum\limits_{b_2=1}^{b_2-1} dp_{i-1,k-1,a_2,b_2}+\sum\limits_{a_2=a_1}^{i-1} \sum\limits_{b_2=b_1}^{i-1} dp_{i-1,k-1,a_2,b_2}$$

而如果要使当前位置 $i$ 不能造成贡献的话，则 $A,B$ 两个排列的前后关系不同，所以我们可以得到：

$$dp_{i,k,a_1,b_1}=\sum\limits_{a_2=1}^{a_1-1} \sum\limits_{b_2=b_1}^{i-1} dp_{i-1,k-1,a_2,b_2}+\sum\limits_{a_2=a_1}^{i-1} \sum\limits_{b_2=1}^{b_1-1} dp_{i-1,k-1,a_2,b_2}$$

所以我们就可以得到一个 $O(n^6)$ 的做法，此做法不难优化，只需要 ~~再次观看题目标签~~ 使用二维前缀和优化即可。

# ACcode
一定要注意取模啊，大前缀和减去小前缀和有可能是负数，所以要再次加上 $mod$，我就因为这个调了好久【手动无奈】


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=102;

int n,k,mod;
int sum[N][N][N][N],dp[N][N][N][N];

inline int read(){
	int t=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9') f=(c=='-')?(-1):(f);
	while(c>='0'&&c<='9') t=(t<<3)+(t<<1)+(c^48),c=getchar();
	return t*f;
}

signed main(){
	n=read(),k=read(),mod=read();
	dp[1][0][1][1]=sum[1][0][1][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=k;j++){
			for(int a=1;a<=i;a++){
				for(int b=1;b<=i;b++){
					dp[i][j][a][b]=((dp[i][j][a][b]+sum[i-1][j-1][a-1][b-1])%mod+mod)%mod;
					dp[i][j][a][b]=((dp[i][j][a][b]+sum[i-1][j][a-1][i-1]-sum[i-1][j][a-1][b-1])%mod+mod)%mod;
					dp[i][j][a][b]=((dp[i][j][a][b]+sum[i-1][j][i-1][b-1]-sum[i-1][j][a-1][b-1])%mod+mod)%mod;
					dp[i][j][a][b]=(((dp[i][j][a][b]+sum[i-1][j-1][i-1][i-1]-sum[i-1][j-1][a-1][i-1]-sum[i-1][j-1][i-1][b-1])%mod+sum[i-1][j-1][a-1][b-1])%mod+mod)%mod;
					sum[i][j][a][b]=(((sum[i][j][a-1][b]+sum[i][j][a][b-1]-sum[i][j][a-1][b-1])%mod+mod)%mod+dp[i][j][a][b])%mod;
				}
			}
		}
	}
	cout<<sum[n][k][n][n];
	return 0;
}

```

---

