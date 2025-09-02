# Neko Rules the Catniverse (Small Version)

## 题目描述

本题与下一题相同，但数据范围更小。

Aki 正在玩一款新的视频游戏。在游戏中，他将操控巨猫 Neko 在 Catniverse（猫宇宙）中的各个星球之间飞行。

Catniverse 中有 $n$ 个星球，编号从 $1$ 到 $n$。游戏开始时，Aki 选择 Neko 的初始所在星球。然后，Aki 进行 $k-1$ 次移动，每次移动时，Neko 会从当前星球 $x$ 移动到另一个星球 $y$，并且满足以下条件：

- 星球 $y$ 尚未被访问过。
- $1 \leq y \leq x + m$（其中 $m$ 是输入中给定的一个常数）。

这样，Neko 将恰好访问 $k$ 个不同的星球。如果存在某个下标 $i$，使得第一种访问方式的第 $i$ 个访问星球与第二种方式的第 $i$ 个访问星球不同，则这两种访问方式被认为是不同的。

问以这种方式访问恰好 $k$ 个星球的不同方案总数是多少？由于答案可能很大，请输出答案对 $10^9 + 7$ 取模后的结果。

## 说明/提示

在第一个样例中，Neko 有 $4$ 种方式访问所有星球：

- $1 \rightarrow 2 \rightarrow 3$
- $2 \rightarrow 3 \rightarrow 1$
- $3 \rightarrow 1 \rightarrow 2$
- $3 \rightarrow 2 \rightarrow 1$

在第二个样例中，Neko 有 $9$ 种方式访问恰好 $2$ 个星球：

- $1 \rightarrow 2$
- $2 \rightarrow 1$
- $2 \rightarrow 3$
- $3 \rightarrow 1$
- $3 \rightarrow 2$
- $3 \rightarrow 4$
- $4 \rightarrow 1$
- $4 \rightarrow 2$
- $4 \rightarrow 3$

在第三个样例中，当 $m = 4$ 时，Neko 可以以任意顺序访问所有星球，因此方案数为 $5! = 120$。

在第四个样例中，Neko 只访问恰好 $1$ 个星球（即初始所在星球），因此有 $100$ 种选择起始星球的方式。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 2 1
```

### 输出

```
9
```

## 样例 #3

### 输入

```
5 5 4
```

### 输出

```
120
```

## 样例 #4

### 输入

```
100 1 2
```

### 输出

```
100
```

# 题解

## 作者：快斗游鹿 (赞：3)

## 思路

直接按下标做不好做，考虑枚举当前插入的值，从 $1$ 到 $n$，这样可以满足第一和第二个条件。考虑怎么满足第三个条件，因为枚举的是值，假设当前插入值 $i$，那么它一定可以插在最前面，也可以插在 $[i-m,i-1]$ 后面。因为 $m$ 很小，所以可以直接记录 $[i-m,i-1]$ 内的数是否存在，一共只有 $2^4$ 种可能。

所以设 $f_{i,j,s}$ 表示前 $i$ 个数，选了 $j$ 个，前 $m$ 个数存在状态为 $s$ 的方案数。那么可以用 $f_{i,j,s}$ 转移到 $f_{i+1,j,q}$ 和 $f_{i+1,j+1,p}$。$q$ 表示当前数不选所产生的新状态，$p$ 表示当前数选所产生的新状态。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
const int mod=1e9+7;
int n,K,m,f[N][15][20];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int calc(int x){
	int aaa=0;
	while(x){
		aaa+=(x&1);x>>=1;
	}
	return aaa;
}
signed main(){
	n=read();K=read();m=read();
	f[0][0][0]=1;
	int s=(1<<m)-1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=K;j++){
			for(int k=0;k<=s;k++){
				f[i+1][j][(k<<1)&s]+=f[i][j][k];f[i+1][j][(k<<1)&s]%=mod;
				if(j<K)f[i+1][j+1][((k<<1)&s)|1]+=(f[i][j][k]*(calc(k)+1)),f[i+1][j+1][((k<<1)&s)|1]%=mod;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=s;i++)ans+=f[n][K][i],ans%=mod;
	cout<<ans; 
}

```


---

## 作者：LinkyChristian (赞：3)

**转自12-26多校联考题解**

由于要求元素互不相同，所以我们希望记录元素是否被选择的状态。

观察数据范围，我们应该需要记录与 $m$ 相关的信息。

我们考虑怎么构造出这个序列，如果直接在序列末尾插入的话，那么需要记录与 $n$ 相关的信息。

但是如果我们可以在任意位置插入，并且强制要求它插在一个比它小的元素后，那么此时就只需要记录与 $m$ 相关的信息。

容易发现，只要我们从小到大依次插入元素，那么插入的元素一定会让它的后继元素比它小，同样也满足条件。

我们考虑 DP，令 $F(i,j,S)$ 表示考虑前 $i$ 个数，插入了 $j$ 个数，$[i-m+1,i]$ 内的元素的状态，转移只需考虑第 $i+1$ 个数是否被插入。

这样复杂度过高，但是我们总是从 $i$ 转移至 $i+1$，而且 $F(i,*,*)$ 到 $F(i+1,*,*)$ 的转移可以用一个固定的矩阵刻画，于是可以使用矩阵快速幂计算。

时间复杂度 $O((k2^m)^3 \log n)$。


---

## 作者：2021hych (赞：2)

## 前置芝士
状压 dp。
## 思路
其实就是从 $1$ 到 $n$ 这 $n$ 个数，选择 $k$ 个数。那么按照经典状态设计，令 $dp_{i,j}$ 为前 $i$ 个数选择其中 $j$ 个数的方案数。但是很明显，对于选择 $i$ 是无法直接转移的。

我们现在想要 $dp_{i,j}$ 转移到 $dp_{i+1,j+1}$。可以发现因为条件 $3$ 的限制，导致只有在 $[i-m+1,i]$ 的选择情况会参与到方案统计，所以我们就可以增设一个新的维度 $dp_{i,j,l}$ 表示前 $i$ 个数选择其中 $j$ 个数，$[i-m+1,i]$ 的选择状态为 $l$。此时，状态转移方程显而易见，暴力转移时间复杂度 $O(n \times k \times 2^m)$ 足够通过本题。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=1e9+7;
int n,k,m,ans;
int dp[N][13][16];
int cal(int x) {
	int num=0;
	while(x) {
		if(x&1) num++;
		x>>=1;
	}
	return num;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>m;
	dp[0][0][0]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<=k;j++)
			for(int l=0;l<(1<<m);l++) {
				dp[i+1][j][(l<<1)&((1<<m)-1)]=(dp[i+1][j][(l<<1)&((1<<m)-1)]+dp[i][j][l])%mod;
				if(j<k) dp[i+1][j+1][((l<<1)&((1<<m)-1))|1]=((dp[i+1][j+1][((l<<1)&((1<<m)-1))|1])+dp[i][j][l]*(cal(l)+1))%mod;//一个小细节，这题的方案有顺序，所以把 i+1 插入的位置是有多种的。
			}
	for(int i=0;i<(1<<m);i++) ans=(ans+dp[n][k][i])%mod;
	cout<<ans;
	return 0;
}
```


---

## 作者：do_it_tomorrow (赞：1)

[更差的阅读体验](https://www.doittomorrow.xyz/post/cf1152f1-neko-rules-the-catniverse-de-ti-jie/)

按照一般得思路，我们应该记录那些元素被选择了。可是 $n$ 太大了，考虑转化一下。

$m$ 很小只有 $4$，这启发我们从 $1$ 开始到 $n$ 一个一个考虑，思考一下填入需要满足什么要求：

具体的，我们考虑在一个序列中插入一些数，使这个序列一直满足题目的要求。

首先第 $1,2$ 个要求是肯定满足得，因为我们就是在枚举要填入什么元素，所以肯定不会出现填入的数大于 $n$ 或者有重复的情况。

因为插入的顺序是递增的，所以一定有 $a_i<a_{i-1}$，也就一定满足 $a_i\le a_{i+1}+m$。

所以新填入的数与后面的关系一定是满足题目要求的，只需要考虑与前面的关系就行了。

注意这里有一个细节就是第 $1$ 个位置可以随便填，因为它根本就没有前面的元素。

考虑会影响填入 $x$ 的有什么，显然 $x$ 只有插入到 $[x-m,x)$ 这些数后面才行，那么暴力的考虑，直接状压记录这 $m$ 个位置都填的什么。

在考虑了上面之后，状态就很好想出来了。

设 $f_{i,j,S}$ 表示现在考虑到了填 $i$，已经填了 $j$ 个数，$[x-i,i)$ 这个区间内都用了 $S$ 的数，那么有转移方程：

$$f_{i+1,j+1,(2S+1)\bmod(2^m)}\gets f_{i,j,S}\times (\operatorname{popcount}(S)+1)$$

$$f_{i+1,j,(2S)\bmod (2^m)}\gets f_{i,j,S}$$

这样的时间复杂度为 $O(n\times k\times 2^m)$ 的。

---

## 作者：complete_binary_tree (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF1152F1)

考虑 dp。

令 $f(i,j)$ 为前 $i$ 个数，使用 $j$ 个数的方案数。

那么不难得到，$f(i+1,j)$（不添加新数的情况）可以直接从 $f(i,j)$ 推得。

但是 $f(i+1,j+1)$ 呢？

注意到题目还有一个限制条件，$m\le4$，且 $a_{i}\le a_{i-1}+m(1\le i\le k)$。

也就是说，要是 $i+1$ 这个数要加入，那么它可以：

- 放在第一个数（因为之前选的数一定小于 $i+1$，即必然小于 $i+1+m$）

- 放在一个已选的数 $j$ 后面，那么 $j$ 必须满足 $i\le j+m$。

前者很好满足，而后者考虑到 $m\le4$，可以直接状态压缩。这样状压后每一个 $1$ 后面都就可以放 $i+1$。两个合起来一共是 $\text{popcount(状态)+1}$ 的可放置位置。

于是记 $f(i,j,l)$ 为前 $i$ 个数选择 $j$ 个最后 $m$ 位状态为 $l$ 的情况。

显然，对于不选的递推，只需要在 $l$ 后面加上一个 $0$ 再保留后 $m$ 位即可，即 ```f[i + 1][j][(l << 1) & ((1 << m) - 1)] += f[i][j][l]```。

对于选的递推，同理，也只需要在 $l$ 后面加上一个 $1$ 再保留后 $m$ 位，即 ```f[i + 1][j + 1][((l << 1) & ((1 << m) - 1)) + 1] += f[i][j][l] * (popcount(l) + 1)```。

然后，我们暴力递推，时间复杂度 $O(n\times k\times 2^m)$。~~1s 都能过了，别说 7s~~

（ps：```popcount()``` 的 $O(\log 2^m)=O(m)$ 其实也得算，所以实际上是 $O(n\times m\times k \times 2^m)$）——update 2/6

需要注意的一点是，这题空间卡得比较极限，~~像我这样喜欢多开 5 的直接 MLE 了~~。

所以我使用了滚动数组优化，空间复杂度由 $O(n\times k\times 2^m)$ 变为了 $O(k\times 2^m)$。~~也跑得更快了（喜）~~

最后，在转移的时候别忘记使用 ```1ll*```，不然会爆掉。

代码：（[提交记录](https://www.luogu.com.cn/record/146383987) $(93\text{ms}/4.00\text{KB})$）

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5, K = 13, M = 1 << 4;
const int mod = 1e9 + 7;

int f[2][K][M]; //滚动数组
int n, k, m;
int popcount(int i){
	int ans = 0;
	while(i) {
		if(i & 1) ++ans;
		i >>= 1;
	}
	return ans;
}

int main() {
	scanf("%d%d%d", &n, &k, &m);
	f[0][0][0] = 1; //记得初始化
	for (int i = 0; i < n; ++i) { //从 0 开始，因为往后递推
		for (int j = 0; j <= k; ++j) {
			for (int l = 0; l < (1 << m); ++l){
				f[(i + 1) % 2][j][(l << 1) & ((1 << m) - 1)] = (f[(i + 1) % 2][j][(l << 1) & ((1 << m) - 1)] + f[i % 2][j][l]) % mod; //不放入新的数
				if(j < k) //j 小于 k 时才要转移
					f[(i + 1) % 2][j + 1][((l << 1) & ((1 << m) - 1)) + 1] = (1ll * f[(i + 1) % 2][j + 1][((l << 1) & ((1 << m) - 1)) + 1] + 1ll * f[i % 2][j][l] * (popcount(l) + 1)) % mod; //每个 1 后面可以插入一个，也可以放在最前面。（不用 1ll* 见祖宗）
				f[i % 2][j][l] = 0; //用完了记得清空（滚动数组）
			}
		} 
	}
	int ans = 0;
	for(int i = 0; i < (1 << m); ++i) ans = (ans + f[n % 2][k][i]) % mod; //统计答案
	printf("%d", ans);
	return 0;
}
```

~~别想拿这个代码去交 large version，我试过，第 30 个点就会 TLE。好好写你的矩阵快速幂吧！~~

---

## 作者：CQ_Bab (赞：1)

# 思路（F1）
一看到提就可能想出一种 $f_{i,j}$ 表示现在到 $i$ 选了 $j$ 个数的方法的，但是如果看见了每一个互不相同就不行了。所以我们考虑从小往大去添数，而这里我们需要分类讨论（后文假设已经枚举到了 $i$ 及即将添加 $i+1$ 了）。

- 若不添加 $i+1$ 则直接继承上一个的答案即可。
- 否则我们发现 $i+1$ 一定能添加在这个队的对头毕竟 $i+1$ 大于此时数列中的所有数，然后我们的 $i+1$ 也可能能添加在一些数 $a_{j}$ 的后面但是这些数必须满足 $i+1\leq a_j+m$ 移项即为 $i+1-m\leq a_j$ 而我们并不注重位置而是注重数量，所以我们可以对 dp 数组多加一维 $l$ 表示从 $i-m+1\sim i$ 选与不选的情况。

我们将状态定义完了之后便很快就能得出转移。

- 不选，$f_{i+1,j,newl}=f_{i,j,l}$ 这里 $newl$ 表示将 $l$ 整体右移并去头。
- 选，$f_{i+1,j+1,newl+1}=f_{i,j,l}$ 这里的 $newl$ 与上述定义一样。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,k,m;
const int N=1e5+10,M=14,K=17,mod=1e9+7;
int f[N][M][K];
int lowbit(int x) {
	return x&-x;
}
int calc(int x) {
	int res=0;
	for(;x;x-=lowbit(x)) res++;
	return res;
}
void solve() {
	in(n),in(k),in(m);
	f[0][0][0]=1;
	rep(i,0,n-1) {
		rep(j,0,min(i,k)) {
			rep(kk,0,(1<<m)-1) {
				int dis=false;
				rep(l,0,m-2) if((kk>>l)&1) dis|=(1<<(l+1));
				f[i+1][j][dis]=(f[i+1][j][dis]+f[i][j][kk])%mod;
				f[i+1][j+1][dis+1]=(f[i+1][j+1][dis+1]+f[i][j][kk]*(calc(kk)+1))%mod;
			}
		}
	}
	int res=false;
	rep(l,0,(1<<m)-1) {
		res=(res+f[n][k][l])%mod;
	}
	cout<<res<<endl;
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```
# 思路（F2）
我们还是借助上述思路，但是我们发现这道题的 $n$ 达到了 $10^9$ 所以我们发现转移并不涉及 $i$ 所以考虑用矩阵快速幂优化。我们发现转移中可以从 $j\to j$ 以及 $j\to j+1$ 所以考虑对于每一对 $j,l$ 压成一个点来转移及对于每一个 $j$ 分别开 $l$ 个来存，然后开一个邻接矩阵来代表转移的边即可。

注意边界。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n,k,m;
const int N=1e5+10,M=14,K=17,mod=1e9+7;
int f[M*K];
int lowbit(int x) {
	return x&-x;
}
int calc(int x) {
	int res=0;
	for(;x;x-=lowbit(x)) res++;
	return res;
}
int ba[K*M][K*M],pos[M*K],p[M*K][M*K],d,now;
void merge1(int x[],int y[][M*K]) {
	memset(pos,0,sizeof pos);
	rep(i,0,now) {
		rep(j,0,now) {
			pos[j]=(pos[j]+x[i]*y[i][j])%mod;
		}
	}
} 
void merge(int x[][M*K],int y[][M*K]) {
	memset(p,0,sizeof p);
	rep(i,0,now) {
		rep(j,0,now) {
			rep(l,0,now) {
				p[i][l]=(p[i][l]+x[i][j]*y[j][l])%mod;
			}
		}
	}
}
void solve() {
	in(n),in(k),in(m);
	d=((1<<m)-1);
	rep(j,0,k) {
		rep(kk,0,(1<<m)-1) {
			int dis=false;
			rep(l,0,m-2) if((kk>>l)&1) dis|=(1<<(l+1));
			ba[kk+j*(d+1)][dis+(j)*(d+1)]=1;
			if(j<k) ba[kk+j*(d+1)][dis+1+(j+1)*(d+1)]=calc(kk)+1;
		}
	}
	now=(d+1)*(k+1)-1;
	int res=false;
	f[0]=1;
	while(n) {
		if(n&1) {
			merge1(f,ba);
			memcpy(f,pos,sizeof f);
		}
		merge(ba,ba);
		memcpy(ba,p,sizeof p);
		n>>=1;
	}
	rep(i,(d+1)*k,now) {
		res=(res+f[i])%mod;
	}
	cout<<res<<endl;
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：UKE_Automation (赞：0)

### CF1152F Neko Rules the Catniverse

[$\text{Small Version}$](https://codeforces.com/problemset/problem/1152/F1)，[$\text{Large Version}$](https://codeforces.com/problemset/problem/1152/F2)

发现两个版本的区别只在于 $n$，所以我们肯定要先从 $n$ 下手然后优化。考虑从小往大往序列里插入数字，那么我们插入 $i$ 的时候插入的位置实际上只有两种：数列的开头或者 $[i-1,i-m]$ 中某个数字的后面。正好我们发现 $m$ 比较小，于是想到状压这个信息。

所以容易设计出一个 dp：设 $dp(i,j,S)$ 表示当前插入第 $i$ 个数后，总共插入了 $j$ 个，当前 $[i,i-m+1]$ 的出现信息为 $S$ 的方案数，转移有两种：

- 如果不插入 $i$，那么 $dp(i,j,S')\leftarrow dp(i-1,j,S)$。
- 如果插入 $i$，那么 $dp(i,j,S')\leftarrow dp(i-1,j,S)\times (1+\text{btc}(S))$，其中 $\text{btc}(S)$ 表示 $S$ 二进制下 $1$ 的数量。

这样做的复杂度是 $O(nk2^m)$ 的，可以通过 F1。考虑 F2，如果我们将 $(j,S)$ 再进行一次压缩，把它们压成一个状态后，不难发现转移的过程可以用矩阵快速幂优化，然后就做完了。复杂度是 $O((k2^m)^3\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define btc __builtin_popcount

using namespace std;

const int Maxn = 4e2 + 5;
const int Inf = 2e9;
const int Mod = 1e9 + 7;
int Add(int x, int y) {return x + y >= Mod ? x + y - Mod : x + y;} 
void pls(int &x, int y) {x = Add(x, y);}
int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;}
void sub(int &x, int y) {x = Del(x, y);}
int qpow(int a, int b) {
	int res = 1;
	while(b) {
		if(b & 1) res = 1ll * res * a % Mod;
		a = 1ll * a * a % Mod; b >>= 1; 
	}
	return res;
}
int inv(int a) {return qpow(a, Mod - 2);}

int n, k, m, N;
int calc(int x, int y) {return x * (1 << m) + y + 1;}
struct Mat {
	int a[Maxn][Maxn];
	Mat() {for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++) a[i][j] = 0;}
	int* operator [](int x) {return a[x];}
	Mat operator * (Mat &b) {
		Mat c;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				for(int k = 1; k <= N; k++) pls(c[i][j], 1ll * a[i][k] * b[k][j] % Mod);
			}
		}
		return c;
	}
}A;

Mat matp(Mat a, int b) {
	Mat res;
	for(int i = 1; i <= N; i++) res[i][i] = 1;
	while(b) {
		if(b & 1) res = res * a;
		a = a * a; b >>= 1; 
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k >> m;
	A[1][1] = 1;
	for(int i = 1; i <= k; i++) {
		for(int j = 0; j < (1 << m); j++) {
			A[calc(i, (j >> 1) | (1 << (m - 1)))][calc(i - 1, j)] = btc(j) + 1;
			A[calc(i, j >> 1)][calc(i, j)] = 1;
		}
	} 
	N = calc(k, (1 << m) - 1);
	A = matp(A, n);
	int ans = 0;
	for(int i = 0; i < (1 << m); i++) pls(ans, A[calc(k, i)][1]);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

关键性质：一个合法的序列，删去最大值后，还是合法序列。

考虑最大值为 $a_t$。不妨设他有前驱，也有后继。

则 $a_t \le a_{t-1} + m$，且 $a_{t+1} < a_t$。

所以 $a_{t+1} < a_{t-1}+m$，结论成立。

那么我们可以按照 $1$ 到 $n$ 的顺序插入数，时刻保证合法。**这样自动满足所有数互不相同**，解决了最难处理的部分。

假设插入的数是 $u$，他前面的那个数应满足 $\ge u-m$。

因此需要状压记录一下 $m$ 个数的状态。还要记录选了多少个数。

使用矩阵快速幂优化。矩阵大小为 $O(2^mk)$。因此复杂度为：$O(2^{3m}k^3 \log n)$。


```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MOD=1e9+7;
int n,k,m;
struct Matrix {int v[210][210];};
Matrix operator *(Matrix A,Matrix B) {
	Matrix C; memset(C.v,0,sizeof(C.v));
	ffor(i,1,208) ffor(j,1,208) ffor(k,1,208) C.v[i][k]=(C.v[i][k]+1ll*A.v[i][j]*B.v[j][k])%MOD;
	return C;
}
Matrix operator ^(Matrix A,int p) {
	Matrix ans; memset(ans.v,0,sizeof(ans.v));
	ffor(i,1,208) ans.v[i][i]=1;
	while(p) {
		if(p&1) ans=ans*A;
		A=A*A,p>>=1;
	}
	return ans;
}
int gid(int i,int st) {return i*(1<<m)+st+1;}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k>>m;
	Matrix trans,ori; memset(ori.v,0,sizeof(ori.v)),memset(trans.v,0,sizeof(trans.v));
	ffor(lst,0,k) ffor(st,0,(1<<m)-1) {
		trans.v[gid(lst,st)][gid(lst,st>>1)]=1;
		if(lst!=k) trans.v[gid(lst,st)][gid(lst+1,(st>>1)|(1<<m-1))]=__builtin_popcount(st)+1;
	}
	ori.v[1][gid(0,0)]=1;
	trans=ori*(trans^n);
	int ans=0;
	ffor(st,0,(1<<m)-1) ans=(ans+trans.v[1][gid(k,st)])%MOD;
	cout<<ans; 
	return 0;
}
```

---

## 作者：_ANIG_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1152F1)

从 $1-n$ 依次插入每个数，这样就不需要考虑重复的问题。

考虑当前这个数能放到哪。可以发现这个数只能放到 $[n-m,n-1]$ 的后面。

而 $m$ 很小，所以可以装压记录哪些 $n-m$ 被选了，则新的数要么填到最前面，要么填到任意一个范围内的数后面，转移系数为 $cnt+1$，其中 $cnt$ 为状态的 $1$ 的个数。

可以发现转移与 $n$ 无关，所以可以直接矩阵优化到 $O(2^{3m}k^3\log n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5,mods=1e9+7;
struct node{
    signed w[305][305],n,m;
    friend node operator*(node a,node b){
        node c;
        c.n=a.n,c.m=b.m;
        for(int i=1;i<=a.n;i++){
            for(int j=1;j<=b.m;j++){
                c.w[i][j]=0;
                for(int k=1;k<=a.m;k++){
                    c.w[i][j]+=1ll*a.w[i][k]*b.w[k][j]%mods;
                    c.w[i][j]%=mods;
                }
            }
        }
        return c;
    }
}zy,cs,rs;
void pows(node&a,int b,node&res){
    if(b==1){
        res=a;
        return;
    }
    pows(a,b>>1,res);
    res=res*res;
    if(b&1)res=res*a;
}
int f[N][15][18],n,m,k,al,cnt[18],bh[15][18],idx;
signed main(){
    cin>>n>>m>>k;
    for(int i=0;i<(1<<k);i++)cnt[i]=__builtin_popcount(i);
    al=(1<<k)-1;
    for(int i=0;i<=m;i++)for(int j=0;j<=al;j++)bh[i][j]=++idx;
    idx++;
    zy.w[idx][idx]=1;
    for(int j=0;j<m;j++){
        for(int l=0;l<=al;l++){
            zy.w[bh[j][l]][bh[j][l<<1&al]]=1;
            zy.w[bh[j][l]][bh[j+1][l<<1&al|1]]=cnt[l]+1;
            if(j+1==m)zy.w[bh[j][l]][idx]=cnt[l]+1;
        }
    }
    zy.n=zy.m=idx;
    cs.n=1,cs.m=idx;
    cs.w[1][bh[0][0]]=1;
    pows(zy,n,rs);
    cs=cs*rs;
    cout<<cs.w[1][idx];
}
```


---

## 作者：pikiuk (赞：0)

考虑在值域上倒着枚举每个星球，并考虑他插入在现有序列的位置，由于是在值域上逆向枚举，他和其前驱之间一定满足关系，只用考虑他和他后继的关系，对他值域上 $m$ 范围内的数状压即可转移。

进一步的，发现该转移有矩阵形式，矩阵快速幂优化即可。

---

