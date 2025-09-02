# Almost Sorted

## 题目描述

You are given a permutation $ p $ of length $ n $ and a positive integer $ k $ . Consider a permutation $ q $ of length $ n $ such that for any integers $ i $ and $ j $ , where $ 1 \le i < j \le n $ , we have $ $$$p_{q_i} \le p_{q_j} + k. $ $ </p><p>Find the minimum possible number of inversions in a permutation  $ q $ .</p><p>A permutation is an array consisting of  $ n $  distinct integers from  $ 1 $  to  $ n $  in arbitrary order. For example,  $ \[2,3,1,5,4\] $  is a permutation, but  $ \[1,2,2\] $  is not a permutation ( $ 2 $  appears twice in the array) and  $ \[1,3,4\] $  is also not a permutation ( $ n=3 $  but there is  $ 4 $  in the array).</p><p>An inversion in a permutation  $ a $  is a pair of indices  $ i $  and  $ j $  ( $ 1 \\le i, j \\le n $ ) such that  $ i &lt; j $ , but  $ a\_i &gt; a\_j$$$.

## 说明/提示

In the first example, the only permutation is $ q = [1] $ ( $ 0 $ inversions). Then $ p_{q_1} = 1 $ .

In the second example, the only permutation with $ 1 $ inversion is $ q = [1, 3, 2] $ . Then $ p_{q_1} = 2 $ , $ p_{q_2} = 1 $ , $ p_{q_3} = 3 $ .

In the third example, one of the possible permutations with $ 6 $ inversions is $ q = [3, 4, 5, 1, 2] $ . Then $ p_{q_1} = 3 $ , $ p_{q_2} = 2 $ , $ p_{q_3} = 1 $ , $ p_{q_4} = 5 $ , $ p_{q_5} = 4 $ .

## 样例 #1

### 输入

```
1 1
1```

### 输出

```
0```

## 样例 #2

### 输入

```
3 1
2 3 1```

### 输出

```
1```

## 样例 #3

### 输入

```
5 2
5 4 3 2 1```

### 输出

```
6```

## 样例 #4

### 输入

```
10 3
5 8 6 10 2 7 4 1 9 3```

### 输出

```
18```

# 题解

## 作者：Leasier (赞：11)

~~与 NOI2023 D1T2 有点像。~~

没能一眼秒被 [goujingyu](https://www.luogu.com.cn/user/266966) 嘲讽了 /dk

------------

考虑钦定一个填入 $q_i$ 的顺序——比如说按 $p_{q_i}$ 从小到大填入。

考虑我们对 $q_i$ 的限制，可得：

- $\forall j < i, p_{q_j} \leq p_{q_i} + k$。
- $\forall j > i, p_{q_i} \leq p_{q_j} + k$。

或言：

- 当前要填入的 $p_{q_i} \geq $ 已填入的最大 $p_{q_j} - k$。
- 当前要填入的 $p_{q_i} \leq $ 未填入的最小 $p_{q_j} + k$。

注意到 $k$ 很小，感性理解可以发现此时前面有一大堆都已填入。

具体的，当考虑换一种描述方式：

- 设 $[1, x]$ 中的数都已填入。
- $x + 1$ 未填入。
- $> x + 1$ 且已填入的数 $\leq x + k + 1$。
- 当前要填入的数 $\in [x + 1, x + k + 1]$。

考虑状压 dp，设 $dp_{i, S}$ 表示 $[1, i]$ 中的数都已填入，$i + 1$ 未填入，$[x + 1, x + k + 1]$ 中数的填入信息为 $S$。

枚举填入哪个并暴力维护逆序对即可。时间复杂度为 $O(n^2 + nk 2^k)$。

代码：
```cpp
#include <stdio.h>

int pos[5007], dp[5007][517], sum[5007];

inline int min(int a, int b){
	return a < b ? a : b;
}

int main(){
	int n, k, full;
	scanf("%d %d", &n, &k);
	k++;
	full = (1 << k) - 1;
	for (int i = 1; i <= n; i++){
		int p;
		scanf("%d", &p);
		pos[p] = i;
	}
	for (int i = 0; i <= n; i++){
		for (int j = 0; j <= full; j++){
			dp[i][j] = 0x7fffffff;
		}
	}
	dp[0][0] = 0;
	for (int i = 0; i <= n; i++){
		if (i > 0){
			for (int j = 1; j <= pos[i]; j++){
				sum[j]++;
			}
		}
		for (int j = 0; j <= full; j += 2){
			if (dp[i][j] != 0x7fffffff){
				for (int x = 1; x <= k && i + x <= n; x++){
					if (!(j >> (x - 1) & 1)){
						int p = i, q = j | (1 << (x - 1)), cnt = sum[pos[i + x] + 1];
						while (q & 1){
							p++;
							q >>= 1;
						}
						for (int y = 1; y <= k; y++){
							if ((j >> (y - 1) & 1) && pos[i + y] > pos[i + x]) cnt++;
						}
						dp[p][q] = min(dp[p][q], dp[i][j] + cnt);
					}
				}
			}
		}
	}
	printf("%d", dp[n][0]);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：6)

过程相当于是将 $p$ 重排列。设 $b_i$ 为 $p$ 中数为 $i$ 的位置。考虑当前填的数 $x$ 贡献的逆序对数，相当于是当前所有已经填入 $p$ 的数 $y$，都有 $[b_y > b_x]$ 的贡献。

考虑 $p_{q_i} \le p_{q_j} + k$ 意味着什么。

当正在填 $p_{q_i}$ 时，之后还没填的数 $\ge p_{q_i} - k$；当正在填 $p_{q_j}$ 时，之前填了的数 $\le p_{q_j} + k$。

综合一下就是，若考虑某个前缀已经填入 $p$ 的状态，**最小的还没填的数 $\le$ 最大的已经填了的数 $+ k$**。

由此可以想到状压。设 $f_{i, S}$ 为当前最小的还没填的数为 $i + 1$，$[i + 1, i + k + 1]$ 的数的填入状态为 $S$（填入为 $1$，没填入为 $0$）。

转移枚举当前位填 $x$（$x$ 只能在 $[i + 1, i + k + 1]$ 中），分开计算 $[1, i]$ 的贡献和 $[i + 1, i + k + 1]$ 的贡献即可。前部分预处理一个前缀有多少个 $b_i \ge j$，后部分暴力。然后还要计算，填了 $x$ 后，新的最小的没填的数是多少。

时间复杂度 $O(n^2 + n k^2 2^k)$。

[code](https://codeforces.com/problemset/submission/1730/224109793)，压行后是 CF 最短解。

---

## 作者：Purslane (赞：4)

# Solution

你发现有一个非常奇怪的限制：$k \le 8$。这很奇怪。

观察题目的 Almost Sorted，我们发现，本质上就是求最少要进行交换相邻两项的操作，使得原数列几乎是排序好的，也就是不存在绝对值差超过 $k$ 的逆序对。

然后假设我们考虑最终的序列，从前往后一个一个填数。

假设我们填到了所有 $\le t$ 的数。容易知道，这个数 $t$ 的位置不能在 $t+k$ 之后。另一方面，它肯定不能在 $t-k$ 之前。因此一个数能填的位置将会非常狭小。

但是如果你枚举这 $2k+1$ 个位置的状态，发现好像信息量有点大，维护不了啊。于是考虑改一改。

假设目前我们已经填了的最大值是 $mx$，那么容易发现最多只有 $[mx-k,mx-1]$ 中间的数没填进来。那么我们可以状压维护这个东西。在 $mx-k$ 填进去之前，不能再填 $mx+1$。

定义 $dp_{i,mx,S}$ 表示我们填了前 $i$ 个数，目前填了的最大值是 $mx$，在 $[mx-k,mx-1]$ 中所有数填还是没填的状态是 $S$，能获得最小的逆序对数。当 $mx-k$ 选过的时候，可以考虑 $mx+1$（甚至如果 $mx-k+1$ 都选过了，你就可以考虑 $mx+2$）这个过程中可以暴力计算有多少前缀和（先预处理所有比他小的放在前面进行逆序对有多少个。然后减去比他小还没出现的，再加上比他大而已经出现了的。）

然后这个 $mx$ 就有 $O(k)$ 种取值了（原因是 $mx$ 在 $i$ 到 $i+k$ 之间），而我们再填一个数会有 $O(k)$ 种方案。光看这个就已经有 $O(n \times 2^k \times k^2)$ 了。因此我们计算逆序对数必须在 $O(1)$ 解决才行！

这个要预处理每个数比他小的 $k$ 个数的所有状态下部分逆序对的数量，比他大的 $k$ 个数所有状态下部分逆序对的数量。

预计复杂度 $O(n \times 2^k \times k^2)$。

---

## 作者：WrongAnswer_90 (赞：2)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/18005665)

[CF1730F Almost Sorted](https://www.luogu.com.cn/problem/CF1730F)

挺有意思的一道题。

刚看到可能有好几种思路，按照 $p$ 的大小填 $q$，或者按照下标顺序填等等。

~~试了几次之后~~ 考虑按照 $i$ 从小到大填入 $q_i$，设 $pos$ 为当前填了的最大的 $p_{q_i}$，由于题目的要求，$1\sim(pos-m-1)$ 的所有数一定都用过（$p_{q_j},j<i$）。所以状压记录值域的 $(pos-m)\sim pos$ 位上有哪些数还没填，这里的值域指的仍然是 $p_{q_i}$，根据 $i$ 和 $S$ 可以推出 $pos$。

然后求逆序对的话对于值域的最后 $m+1$ 位暴力计算，对于 $\leq pos-m$ 的部分，设 $b_{p_i}=i$ 则可以看成是一个询问 $i<pos-m$ 且 $b_i>b_{now}$ 的点的数量，二维前缀和即可，复杂度 $\mathcal O(n^2+n2^kk^2)$。

```cpp
	int n,m,b[5010],f[5010][512],a[5010];
	unsigned short t[5010][5010];
	inline void mian()
	{
		read(n,m),++m;
		for(int i=1;i<=n;++i)read(a[i]),++t[i][a[i]],b[a[i]]=i;
		for(int i=n;i>=1;--i)for(int j=1;j<=n;++j)t[i][j]+=t[i+1][j]+t[i][j-1]-t[i+1][j-1];
		memset(f,127,sizeof(f)),f[0][(1<<m)-1]=0;
		for(int i=1;i<=n;++i)
		{
			for(int j=1,pos;j<(1<<m);j+=2)
			{
				pos=i+m-__builtin_popcount(j)-1;
				if(f[i-1][j]>=inf)continue;
				for(int k=1;k+pos<=n&&k<=m;++k)
				{
					if(!(j>>(m-k)&1))break;
					int x=0;
					for(int l=0;l<m&&pos>l;++l)x+=(j>>l&1)&&b[pos-l]>b[pos+k];
					Mmin(f[i][(j<<k|1)&((1<<m)-1)],f[i-1][j]+x+(pos>m?t[b[pos+k]+1][pos-m]:0));
				}
				for(int k=0;k<m&&k<pos;++k)
				{
					if(j>>k&1)continue;
					int x=0;
					for(int l=0;l<k;++l)x+=(j>>l&1)&&b[pos-l]>b[pos-k];
					for(int l=k+1;l<m&&l<pos;++l)x+=(j>>l&1)&&b[pos-l]>b[pos-k];
					Mmin(f[i][j|1<<k],f[i-1][j]+x+(pos>m?t[b[pos-k]+1][pos-m]:0));
				}
			}
		}
		write(f[n][(1<<m)-1]);
	}
```

---

## 作者：do_while_true (赞：2)

> 给定一个长度为 $n$ 的置换 $p$，以及一个正整数 $k$．
> 
> 对于一个置换 $q$，要求对于所有满足 $1\leq i<j\leq n$ 的 $i,j$，有以下不等式成立：
> $$
p_{q_i}\leq p_{q_j}+k
$$
> 现在请求出满足条件的置换 $q$ 中，逆序对数最小的 $q$，它逆序对数是多少。
> 
> $1\leq n\leq 5000,1\leq k\leq 8$．

相当于要对 $p$ 进行重排，如果将某个前缀出现过的 $p$ 看作一个二进制数，那么即为要求最高的 $1$ 和最低的 $0$ 之间相差不能超过 $k$．所以我们知道如果填了 $i$，那么 $<i-k$ 的那些数一定已经填过了。所以先 $\mathcal{O}(n^2)$ 把 $<i-k$ 的那些逆序对给统计上。

那么就好 dp 了，$f_{i,S}$ 表示从低到高填到了 $i$，然后 $i$ 前面 $k$ 个数填的状态是 $S$，只记前 $k$ 个是因为由于条件的限制 $<i-k$ 的都一定已经填过了。

这样时间复杂度就是 $\mathcal{O}(n^2+nk^22^k)$，因为转移的时候枚举下一个填啥是 $\mathcal{O}(k)$ 的，还有一个暴力 $\mathcal{O}(k)$ 计算逆序对贡献。


```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
const int inf=0x3f3f3f3f;
inline int bit(int x){
	return 1<<(x-1);
}
inline int all(int x){
	return (1<<x)-1;
}
const int N=5010;
int n,k,p[N],vis[N],c[N];
int f[N][260],ans;
int calc(int x,int s,int i){
	int sum=vis[x]>vis[x-i];
	for(int j=1;j<=k&&x-j>=1;j++)
		if(bit(j)&s)
			if(vis[x-j]>vis[x-i])
				++sum;
	for(int j=k+1;x-j>=1&&j<=k+i;j++)
		if(vis[x-j]>vis[x-i])
			++sum;
	return sum;
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n,k);
	for(int i=1;i<=n;i++)read(p[i]),vis[p[i]]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<i-k;j++)
			if(vis[j]>vis[i])
				++ans;
	memset(f,0x3f,sizeof(f));
	f[0][(1<<k)-1]=0;
	for(int i=0;i<=n;i++)
		for(int s=0;s<(1<<k);s++)if(f[i][s]!=inf){
			for(int j=1;j<=k;j++)
				if(!(bit(j)&s)){
					cmin(f[i][s|(1<<(j-1))],f[i][s]+calc(i,s,j));
				}
			for(int j=1;j<=k+1&&i+j<=n;j++){
				if(j<=k && !(bit(k-j+1)&s))break;
				int to=((s<<j)|bit(j))&all(k);
				cmin(f[i+j][to],f[i][s]+calc(i+j,to,0));
			}
		}
	cout << f[n][(1<<k)-1]+ans << '\n';
    #ifdef do_while_true
//		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：Refined_heart (赞：2)

首先我们考虑题目本质是在要求什么。

实际上，它是想让我们把原序列进行一种排序，使得其满足题目给定条件的情况下，将原序列的编号对应排序后写下来，让这个序列的逆序数最少。

那么我们思考后发现，这东西无疑要 dp ，但是其具有两个关键维度：其一是值域，这是题目要求的限制之一；其二是序列，我们要求逆序数最少。

这里一定要看准，**逆序数不是元素大小的逆序数，而是下标的逆序数**。

我们先来观察一下性质。不难发现，对于 $p_i = 1,$ 最终在 $q$ 中 $i$ 最多也就只能放到 $q_{k + 1}$ 的位置上。原因是前面会出现不满足条件的数字。

因此我们可以观察到，对于一个值 $v$ 而言，其能够填写的位置是 $O(k)$ 级别的，并且组成一段连续区间。

继续看，我们考虑可以将填写看成每次选一个数塞到前缀的末尾。我们为满足题目限制，考虑按照值域来填写数，然后把逆序数放到 $f$ 的数组里面，将其最小化。

根据上述性质，一个**值**的出现范围连续并且是 $O(k)$ 的，而 $k\leq 8$ 不难考虑到状压行为。

我们考虑，如果最长的连续值域前缀已经填写了 $i,$ 那么 $i + k + 2$ 无论如何不能写进去，因为 $i + 1$ 还没有写进去，这样一定不合法。

因此，我们设 $f(i, S)$ 表示已经填写完毕值域在 $[1, i]$ 中的数字，$[i + 1, i + k + 1]$ 这部分数字的填写状态是 $S$ 的最优解。其中 $S$ 若为 $0$ 则表示还没填进去。

那么考虑转移。我们考虑，在 $i$ 处所有的合法状态必然满足 $S_0 = 0$ 也就是 $i + 1$ 还没有填写。否则可以构成更长的前缀。

当然为方便状态转移我们可以直接将这些状态转移到 $f(i + 1, S / 2)$ 。

那么我们考虑正常的转移，我们考虑从小到大枚举数位，转移到 $f(i, S \cup \{d\})$ 此时我们需要仔细考虑**转移代价如何计算**。

上述已经强调逆序数是下标的逆序数。因此，我们维护一个 BIT 支持查询后缀和，将 $[1, i]$ 所有值的编号插入进去。那么计算代价的时候，先查询当前插入的值的下标的后缀和（也就是已经插入的部分构成的逆序数），再考虑未插入 BIT 里面的下标（也就是 $S$ 中的数）暴力计算代价。

这样下来总复杂度是 $O(n2^kk(k + \log n))$ 的。常数很小，跑的很快。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
inline int read()
{
	int s = 0, w = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int N = 6000;
int f[N][1 << 9];
int a[N], n, K;
// f(i, S) shows that [1, i] has been filled in a prefix, and [i + 1, i + k]'s state = S 
// 1 is equal to has been filled, 0 is not.
int tr[N], b[N];
inline int lowbit(int x) {return x & -x;}
inline void change(int x, int v) {
	while(x) {
		tr[x] += v;
		x -= lowbit(x);
	}
}
inline int query(int x) {
	int res = 0; while(x <= n) {
		res += tr[x];
		x += lowbit(x);
	}
	return res;
}
inline int calc(int st, int S, int fl) {
	int res = query(a[st + 1 + fl]);
	for(int i = 0; i < K; ++i) if(i != fl && (S >> i & 1)) {
		if(a[st + 1 + fl] < a[st + 1 + i]) res = res + 1;
	}
	return res;
}
int main() {
	freopen("in.txt", "r", stdin);
	n = read(); K = read(); K = K + 1;
	for(int i = 1; i <= n; ++i) a[i] = read(), b[a[i]] = i;
	for(int i = 1; i <= n; ++i) a[i] = b[i];
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	for(int i = 0; i < n; ++i) {
		for(int S = 0; S < (1 << K); ++S) {
			if(f[i][S] > n * n) continue;
			if(!(S & 1)) {
//				 i + 1 has not been filled, so, i + 1 + k + 1 must be not.
				for(int j = 0; j < K; ++j) {
					if(i + j + 1 > n) break;
					if(!(S >> j & 1)) {
						f[i][S | (1 << j)] = min(f[i][S | (1 << j)], f[i][S] + calc(i, S, j));
					}
				}
			}
			else {
				f[i + 1][S >> 1] = min(f[i + 1][S >> 1], f[i][S]);
			}
		}
		change(a[i + 1], 1);
	}
	cout << f[n][0] << '\n';
	return 0;
}
```


---

## 作者：小木虫 (赞：1)

### Preface  
我个人觉得这题细节很多很恶心。  
### Problem  
给你一个长度为 $n$ 的排列 $p$，现在要你求一个逆序对数最小的排列 $q$ 使得对于每一对满足 $1\leq i<j\leq n$ 的 $i,j$ 满足：    
$$p_{q_i}\leq p_{q_j}+k$$  

$(1\leq n \leq 5000,1\leq k \leq 8)$  

### Solution  
发现在选择 $q$ 的元素的过程中，一旦选择了一个 $q_i$ 会使得以后再也不能选任何 满足 $p_{q_j}<p_{q_i}-k$ 的 $j$ 了，那么事实上当我们选的最大的数为 $J$ 的时候，$J-k-1$ 及以下的的数字都应该早就被选择，只有 $[J-k,J-1]$ 这个区间的数能在 $J$ 之后存在。  

发现这个区间很小，可以状压。  

于是设 $dp_{i,J,g}$ 为选择到第 $i$ 个数，最大的数为 $J$，$[J-k,J-1]$ 区间选择状态为 $g$ 的最小逆序对数。  

转移大致为（注意判边界）：  
第一个式子：  
$$dp_{i+1,J+f,(g+(1<<k))>>f)}=\min(dp_{i,J,g}+sum_{J-k-1+f,q_{J+f}}+cost_{J+f,(g+(1<<k))>>f),k})$$  
$f$ 为一个小于 $g$ 的全 1 最大后缀长度的数。  
$sum$ 为一个二维前缀和，但是第二维的转移向上代表逆序对。  
$q$ 在此处为按 $p_i$ 从小到大排序后组成的原下标数列。  
$cost_{i,g,j}$ 为计算在 $i$ 上的 $g$ 状态中比 $q_{i-k-1+j}$ 更小的数字的数量，可进行预处理。  
注意如果一个位置的状态填满了则它有资格直接跳到 $J+k+1$ 上。

第二个式子：  
$$dp_{i+1,J,g|(1<<(f-1)}=\min(dp_{i,j,g}+sum_{J-k-1,q_{J-1-k+f}}+cost_{J,g|(1<<(f-1),f}+(q_J>q_{J-1-k+f}))$$  
$f$ 为 $g$ 没有被填的一个位置。  
其它意义同上。  

发现 $J$ 太大了，完全无法进行转移。  
但是我们发现 $J\leq i+k$，于是我们设 $j=J-i$ 进行转移，从上文进行意义转换即可。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5010;
int n,k,p[N],q[N],sum[N][N];
int dp[N][10][(1<<8)];
int cost[N][(1<<8)][10];
int popcnt[(1<<8)];
bool flag1,flag2;
//i=j-k+popcnt
//j=i+k-popcnt
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>p[i],q[p[i]]=i;
	//for(int i=1;i<=n;i++)
	//	cout<<q[i]<<" ";
	//cout<<endl;
	for(int i=1;i<=n;i++)
		sum[i][q[i]]++;
	for(int i=1;i<=n;i++)
		for(int j=n;j>=1;j--)
			sum[i][j]+=sum[i-1][j]+sum[i][j+1]-sum[i-1][j+1];
	for(int i=0;i<(1<<k);i++)
		for(int j=1;j<=8;j++)
			popcnt[i]+=((i>>(j-1))&1);
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<=k;i++)
		dp[1][i][0]=0;
	for(int i=1;i<=n;i++){
		for(int g=0;g<(1<<k);g++){
			int res=0;
			for(int f=1;f<=k+1;f++){
				res=0;
				for(int j=1;j<=k;j++){
					if(j==f)continue;
					if(!((g>>(j-1))&1))continue;
					if(i-1-k+j<1||i-1-k+f<1)continue;
					res+=(q[i-1-k+j]>q[i-1-k+f]);
				}
				cost[i][g][f]=res;
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<=8;j++){
			int J=j+i;
			for(int g=0;g<(1<<k);g++){
				bool flag=0;
				//cout<<i<<" "<<J<<" "<<g<<" "<<dp[i][j][g]<<endl;
				for(int f=1;f<=k;f++){
					//J-1 k-(J-1) k-J+1
					if(J-1-k+f>=1&&(!((g>>(f-1))&1))){flag=1;break;}
					if(J+f>n){flag=1;break;}
					int to=((g+(1<<k))>>f);
					//cout<<"To"<<to<<" "<<sum[J-k-1+f][q[J+f]]<<" "<<cost[J+f][to][k+1]<<endl;
					if(J-k-1+f>=1)
						dp[i+1][j+f-1][to]=min(dp[i+1][j+f-1][to],
							dp[i][j][g]+sum[J-k-1+f][q[J+f]]+cost[J+f][to][k+1]);
					else dp[i+1][j+f-1][to]=min(dp[i+1][j+f-1][to],
							dp[i][j][g]+cost[J+f][to][k+1]);
				} 
				if(J+k+1<=n&&!flag){
					int to=0;
					dp[i+1][j+k][to]=min(dp[i+1][j+k][to],dp[i][j][g]+sum[J][q[J+k+1]]);
				}
				for(int f=1;f<=k;f++){
					if((g>>(f-1))&1)continue;
					if(J-1-k+f<1)continue;
					if(j==0)break;
					int to=(g|(1<<(f-1)));
					//cout<<sum[J-k-1][q[J-1-k+f]]+cost[J][to][f]<<endl;
					if(J-k-1>0)
						dp[i+1][j-1][to]=min(dp[i+1][j-1][to],
							dp[i][j][g]+sum[J-k-1][q[J-1-k+f]]+cost[J][to][f]+(q[J]>q[J-1-k+f]));
					else dp[i+1][j-1][to]=min(dp[i+1][j-1][to],
							dp[i][j][g]+cost[J][to][f]+(q[J]>q[J-1-k+f]));
				}
			}
		}
	}
	//for(int j=0;j<=8;j++){
	//	int J=j+n;
	//	for(int g=0;g<(1<<k);g++)
	//		cout<<n<<" "<<J<<" "<<g<<" "<<dp[n][j][g]<<endl;
	//}
	cout<<dp[n][0][(1<<min(n-1,k))-1];
	return 0;
}
```


---

