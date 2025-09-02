# [ABC383F] Diversity

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc383/tasks/abc383_f

店で $ N $ 個の商品が売られています。 $ i $ 個目の商品の価格は $ P_i $ 円、効用は $ U_i $ 、色は $ C_i $ です。

あなたは、これらの $ N $ 個の商品から何個か( $ 0 $ 個でもよい)を選んで購入します。 このとき、購入した品物の合計価格は $ X $ 円以下でなければなりません。

あなたの満足度は、購入した商品の効用の合計を $ S $、購入した商品の色の種類数を $ T $ としたとき、$ S+T\ \times\ K $ です。 ここで、$ K $ は入力で与えられる定数です。

あなたの満足度を最大化するように購入する商品を選んだとき、満足度を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ X\ \leq\ 50000 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ 1\ \leq\ P_i\ \leq\ X $ $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ U_i\ \leq\ 10^9 $ $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ C_i\ \leq\ N $ $ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数
 
### Sample Explanation 1

$ 1 $ 個目、$ 2 $ 個目の商品を購入したとき、効用の合計 $ S $ は $ 7 $ で、色の種類数 $ T $ は $ 2 $ です。よって、満足度は $ 7+2\ \times\ 5\ =\ 17 $ です。また、満足度が $ 18 $ 以上になるような購入の仕方は存在しないため、答えは $ 17 $ です。

### Sample Explanation 2

$ 2 $ 個目、$ 3 $ 個目、$ 4 $ 個目の商品を購入したとき、効用の合計 $ S $ は $ 35 $ で、色の種類数 $ T $ は $ 3 $ です。よって、満足度は $ 35+3\ \times\ 3\ =\ 44 $ です。また、満足度が $ 45 $ 以上になるような購入の仕方は存在しないため、答えは $ 44 $ です。

## 样例 #1

### 输入

```
3 10 5
1 3 1
7 4 2
4 5 1```

### 输出

```
17```

## 样例 #2

### 输入

```
5 30 3
5 4 3
11 20 1
9 10 4
7 5 2
16 15 4```

### 输出

```
44```

## 样例 #3

### 输入

```
22 75 6426
9 309 9
5 470 5
17 481 12
27 352 14
1 191 18
7 353 20
9 99 15
20 401 17
46 434 19
11 459 22
10 317 19
15 440 18
17 438 19
25 461 22
5 320 22
1 476 21
11 315 3
8 112 9
11 438 13
19 362 8
10 422 13
10 152 21```

### 输出

```
67717```

# 题解

## 作者：gesong (赞：15)

题目传送门：[[ABC383F] Diversity](https://www.luogu.com.cn/problem/AT_abc383_f)。

# 思路
遇到这种题目不是贪心就是 dp，这题我们考虑使用 **dp** 求解。

首先将所有的商品按照颜色分类记 $p_{i,j}$ 为第 $i$ 种颜色第 $j$ 个的 $P$ 数组值，$u_{i,j}$ 同理。

设 $f_{i,j}$ 表示使用前 $i$ 种颜色且使用 $j$ 元的最大满意度，转移考虑不用颜色为 $i$ 的，用第一次使用颜色为 $i$ 的，多次使用颜色为 $i$ 的。

综上，对于一个 $p_{i,k}$ 和 $u_{i,k}$ 有转移 $f_{i,j}=\max(f_{i-1,j},f_{i-1,j-p_{i,k}}+u_{i,k}+K,f_{i,j-p_{i,k}}+u_{i,k})$。

最后的答案即为所有 $f_{i,j}$ 的最大值，注意转移时要按照背包的方法**倒序转移**。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510,M=5e4+10;
int f[N][M];
vector<pair<int,int> >a[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
inline int max(int a,int b,int c){
	return max(a,max(b,c));
}
main(){
	int n=read(),m=read(),k=read();
	for (int i=1;i<=n;i++){
		int p=read(),u=read(),c=read();
		a[c].push_back({p,u});
	}
	for (int i=1;i<=n;i++){
		for (int j=0;j<=m;j++)
			f[i][j]=f[i-1][j];
		for (auto xx:a[i]){
			int p=xx.first,u=xx.second;
			for (int j=m;j>=p;j--)
				f[i][j]=max(f[i][j],f[i-1][j-p]+u+k,f[i][j-p]+u);
		}
	}
	int ans=0;
	for (int i=1;i<=n;i++)
		for (int j=0;j<=m;j++) ans=max(ans,f[i][j]);
	cout <<ans;
    return 0;
}
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
// NOIP 2024 RP++
```

---

## 作者：kkxacj (赞：6)

#### 思路

首先观察数据范围可以发现 $n\times V$ 可以通过此题。

考虑先按颜色排序，转移时，若 $c_j = c_i$，则正常背包转移，即 $f_{i,v+p_i} = \max\left(f_{i,v+p_i},f_{j,v}+u_i\right)$。

若不同，转移时额外加上 $k$ 的贡献，即 $f_{i,v+p_i} = \max\left(f_{i,v+p_i},f_{j,v}+u_i+k\right)$。

设 $f_{i,0/1}$ 表示背包容量用了 $i$ 时，是否用了和当前颜色一样的点最大贡献，转移就行了。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
#define ys int
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 510,M = 5e4+10;
int n,x,k,K,f[2][M],cnt,ans;
struct w
{
	int p,u,c;
}a[N];
inline bool cmp(w x,w y){return x.c < y.c;}
signed main()
{
	read(n),read(x),read(K);
	for(int i = 1;i <= n;i++) read(a[i].p),read(a[i].u),read(a[i].c);
	sort(a+1,a+1+n,cmp);
	for(int i = 1;i <= x;i++) f[0][i] = -1e17;
	f[0][0] = 0;
	for(ys i = 1;i <= n;i++) 
	{
		if(a[i].c != a[i-1].c)
			for(int j = 0;j <= x;j++) f[0][j] = max(f[0][j],f[1][j]),f[1][j] = -1e17;//不一样更新 
		for(ys j = x;j >= a[i].p;j--) f[1][j] = max(f[1][j],max(f[0][j-a[i].p]+a[i].u+K,f[1][j-a[i].p]+a[i].u));
	}
	for(ys i = 0;i <= 1;i++) 
		for(ys j = 0;j <= x;j++)
			ans = max(ans,f[i][j]);
	print(ans); flush();
	return 0;
}
```

---

## 作者：wangyizhi (赞：5)

一道挺好的 DP 题。

~~可惜赛时没写出来 /kk~~

## 题目大意

有 $n$ 个物品，每个东西都有一个价格 $v_i$、价值 $w_i$ 和颜色 $c_i$。设选的物品的总价值为 $S$，其中颜色的种类数为 $T$，则你的**满意度**为 $S+T\times K$，其中 $K$ 为给定的常数。求用 $X$ 元钱可以获得的最大满意度。其中 $c_i\le n\le 500$，$v_i\le X\le50000$，$w_i,K\le10^9$。

## 题目分析

有价格、价值，很容易就能想到是背包问题。虽然有个颜色，但肯定要用 DP。

### 状态设计？

根据背包问题的套路，肯定有一维是已用的钱的数量。又由于答案和颜色数有关，那我们不妨再设另一维为当前选到的颜色。

于是状态就有了：设 $f_{i,j}$ 表示当前选到了第 $i$ 种颜色，花费的钱为 $j$ 时最大的满意度。

### 状态转移？

（下文中记第 $i$ 件物品的价格为 $v_i$，价值为 $w_i$，颜色为 $c_i$。）

假设现在我们已经算到了第 $i$ 件物品，在计算 $f_{c,j}$。

$f_{c,j}$ 这个状态可以从哪些状态转移来呢？如果我们已经选过 $c$ 这个颜色，那我们只要在相同颜色的情况下做普通的背包转移，即

$$\large{f_{c,j}=f_{c,j-v_i}+w_i}$$

如果我们没有选过这个颜色，那我们可以从前面的任意一个颜色中转移过来，同时在普通的背包转移中加上一个 $K$，即

$$\large{f_{c,j}=\displaystyle\max_{0\le r<c}\{f_{r,j-v_i}+w_i+K\}}$$

可能的疑惑：

Q：为什么 $r$ 要从 $0$ 开始？

A：为了方便计算（见下文），我们令 $f_{0,j}=0$。

Q：如果是第一个选的颜色的第一个物品套用第一个式子会少加一个 $K$。

A：在 $f_{0,j}=0$ 的前提下，由于这是第一种颜色的第一个物品，显然此时所有的 $f_{c,j}$ 都为 $0$。这时第一个式子算出来的结果为 $w_i$，第二个式子算出来的结果为 $w_i+K$，因为我们要取最大值，所以只会取第二个式子的值。

OK？让我们继续。

于是我们的状态就转移完了——吗？

这样转移的时间复杂度为 $O(n^2X)$，理论上可以卡着时限通过本题。但我们可以做的更优。~~才不会告诉你是本蒟蒻不会卡常 T 飞了。~~

我们再来看第二个式子：

$$\large{f_{c,j}=\displaystyle\max_{0\le r<c}\{f_{r,j-v_i}+w_i+K\}}$$

然后你会惊奇的发现，里面的 $w_i$ 和 $K$ 都是常量！

于是我们可以把它们提出来，得到：

$$\large{f_{c,j}=\displaystyle\max_{0\le r<c}\{f_{r,j-v_i}\}+w_i+K}$$

然后你会更惊奇的发现，前面这坨可以优化！

令 $pre_{c,j}=\displaystyle\max_{0\le r\le c}{f_{c,j}}$，原式就可化为：

$$\large{f_{c,j}=pre_{c-1,j-v_i}+w_i+K}$$

综合两式，得：

$$\large{f_{c,j}=\max\{f_{c,j-v_i}+w_i,pre_{c-1,j-v_i}+w_i+K}\}$$

记得更新前缀最大值：

$$\large{pre_{c,j}=\max\{pre_{c-1,j},f_{c,j}\}}$$

最终答案就为 $\displaystyle\max_{1\le c \le n}\{f_{c,X}\}$

时间复杂度为 $O(nX)$，轻松通过本题。

然后这题就做完了——吗？

### 预处理？

我们显然要把相同颜色的东西放在一段一起考虑，否则可能在更新的时候会用到 $r>c$ 的状态，这样就不行了。

所以我们得先把物品按照颜色排序。这个简单。

然后这题就真的做完啦！

## AC Code

```cpp
// by wangyizhi(571247)
#include<iostream>
#include<algorithm>
using namespace std;
using ll=long long; // 十年 OI 一场空
struct node
{
	ll v,w,c;
}a[501];
ll dp[501][50001];
ll pre[501][50001];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,x,k;
	cin>>n>>x>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i].v>>a[i].w>>a[i].c;
	sort(a+1,a+n+1,[&](node &x,node &y){
		return x.c<y.c;
	}); // lambda 大法好！！！
	int c=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].c!=a[i-1].c) c++; // 下一种颜色
		for(int j=x;j>=a[i].v;j--)
			dp[c][j]=max(dp[c][j],dp[c][j-a[i].v]+a[i].w); // 第一个式子
		for(int j=x;j>=a[i].v;j--)
			dp[c][j]=max(dp[c][j],pre[c-1][j-a[i].v]+a[i].w+k); // 第二个式子
		for(int j=x;j>=0;j--)
			pre[c][j]=max(pre[c-1][j],dp[c][j]); // 第三的式子
	}
	ll ans=0;
	for(int i=1;i<=c;i++)
		ans=max(ans,dp[i][x]); // 取最大值
	cout<<ans;
	return 0;
}
```
看在蒟蒻打了这么多字的份上，点个赞再走吧！！！

有错误或不好的地方欢迎指出！

---

## 作者：mayike (赞：4)

省流：F 比 C 简单。

## 思路

发现是个背包问题，猜测复杂度是 $O(nX)$ 级别，但是由于颜色不同数的限制，不知该怎么办才好？

那就先按颜色排个序，相同颜色一定是一个连续段，在每个不同颜色的连续段 dp 即可，复杂度 $O(n\log n+nX)$，可以接受。

对于每个连续段内，设 $g_{i,j}$ 表示当前选没选这个段内的商品，$j=0$ 表示没选，$j=1$ 则表示选了，花费了 $i$ 的代价所获得的最大满意度。设当前遍历到 $k$ 商品，则有转移方程：

$$g_{i,1}=\max(g_{i,1},g_{i-p_k,1}+u_k,g_{i-p_k,0}+u_k+K)$$

$g_{i,0}$ 是从上一个连续段转移过来的，不变。还需一个数组 $f_i$ 来维护全局的 $\max(g_{i,0},g_{i,1})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505,M=5e4+5;
int n,X,K;
long long f[M],g[M][2];
struct yes{
	int p,u,c;
}a[N];
bool cmp(yes x,yes y){
	return x.c<y.c;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>X>>K;
	for(int i=1;i<=n;i++)cin>>a[i].p>>a[i].u>>a[i].c;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(i==1||a[i].c!=a[i-1].c){
			for(int j=0;j<=X;j++)g[j][0]=f[j];
		}
		for(int j=X;j>=a[i].p;j--)g[j][1]=max({g[j][1],g[j-a[i].p][1]+a[i].u,g[j-a[i].p][0]+K+a[i].u});
		if(i==n||a[i].c!=a[i+1].c){
			for(int j=0;j<=X;j++){
				f[j]=max(g[j][0],g[j][1]);
				g[j][0]=g[j][1]=0;
			}
		}
	}
	long long ans=0;
	for(int i=0;i<=X;i++)ans=max(ans,f[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Po7ed (赞：3)

赛时没做出来，赛后 10min 想 + AC，难绷。

显然如果没有颜色的贡献，这题就是裸的背包。

不难发现满意度 $S+T\times K$ 中颜色的贡献可以拆成：每增加一种颜色，满意度加上 $K$。

将物品按颜色排序，将上述贡献（$+K$）算在每种颜色第一个购买的物品上，即可解决问题。

```cpp
#include <bits/stdc++.h>

using std::cin;
typedef long long ll;
constexpr int N=514,M=5e4+N;
constexpr ll INF=4e18;
int n,m,v;
ll f[N][M];
struct node{ll w,v,c;};
inline bool operator < (node x,node y){return x.c<y.c;}
node a[N];

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m>>v;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].w>>a[i].v>>a[i].c;
	}
	std::sort(a+1,a+n+1); // 按颜色排序，使同颜色物品相邻
	for(int i=1,k=0;i<=n;i++)
	{
		for(int j=1;j<a[i].w;j++)
		{
			f[i][j]=f[i-1][j];
		}
		for(int j=a[i].w;j<=m;j++)
		{
			f[i][j]=std::max
			({
				f[i-1][j], // 除了基本的背包之外
				f[i-1][j-a[i].w]+a[i].v,
				f[k][j-a[i].w]+a[i].v+v // 多了此转移，注意这里多加了一个 v
			}); // 从上一个颜色的最后一个物品转移过来
				// 保证当前物品是当前颜色中第一个取的
		}
		if(a[i].c!=a[i+1].c)
		{ // 记录上一个颜色的最后一个物品
			k=i;
		}
	}
	printf("%lld",f[n][m]);
	return 0;
}

```

---

## 作者：Ray662 (赞：3)

场上写了将近 1h，记录一下自己有多么 sb。

---

### Task

有 $n$ 个物品，每个物品有三个属性：质量 $w_i$，价值 $v_i$ 和颜色 $c_i$。你可以选出一些物品构成集合 $S$，保证质量之和 $\sum_{i \in S} \le X$，最大化：

$$
\sum_{i \in S} v_i + K \times |\cup_{i \in S} \{c_i\}|
$$

$K$ 是给定的常数，$n \le 500, X \le 5 \times 10^4$。

---

### Solution

首先解决颜色的问题，按颜色排个序，保证相同颜色的物品是一段。记 $pre_i$ 表示物品 $i$ 的颜色的颜色段开头物品编号。

考虑 DP。设 $f_{i, j}$ 表示当前选到第 $i$ 个物品，质量之和为 $j$ 的最大答案。

转移的话分类讨论一下从相同颜色转移还是不同颜色转移：

$$
f_{i, j} = \max
\begin{cases}
f_{i - 1, j} \\
f_{k, j - w_i} + v_i + K & j \ge w_i \text{ and } k < pre_i \\
f_{k, j - w_i} + v_i & j \ge w_i \text{ and } k \ge pre_i
\end{cases}
$$

直接做是 $O(n^2X)$ 的，需要优化。发现对于后两个转移，转移点是连续的一段。所以考虑前缀 max 优化，具体来说记 $g_{i, j} = \max_{1 \le k \le i} f_{k, j}$，于是转移就变为了：

$$
f_{i, j} = \max
\begin{cases}
f_{i - 1, j} \\
g_{pre_i - 1, j - w_i} + v_i + K & j \ge w_i \\
g_{i - 1, j - w_i} + v_i & j \ge w_i
\end{cases}
$$

有个小问题，就是说第三条转移的 $g_{i - 1, j - w_i}$ 包含了 $g_{pre_i - 1, j - w_i}$，事实上应该只计算 $k \in [pre_i, i - 1]$ 的 $f_{k, j}$。但由于我们是取 max，$ < pre_i$ 的部分在第三条中一定劣于在第二条中，所以不影响。

时间复杂度 $O(nX)$。

[code](https://atcoder.jp/contests/abc383/submissions/60542365)

---

## 作者：Walrus (赞：3)

## Tricks
一个比较板的 trick。

- 记录颜色再枚举是容易想到的。考虑拿个 `vector` 存下。

- 对于背包中与「颜色数」有关的题目，不难想到 dp 的转移是在朴素背包的基础上加上与颜色有关的限制。

考虑定义 $dp_{i,j}$ 表示选到第 $i$ 种颜色当前容量是 $j$ 的最大满意度。因为颜色选择的先后顺序显然是没有影响的，所以这个状态是没有问题的。

考虑怎么转移。对于朴素的背包转移，应有（假设 $c_k=i$）：
$$dp_{i,j}=\max_{m\geq j \geq p_k}dp_{i,j-p_k}+u_k$$

考虑加入颜色的限制，有：
$$dp_{i,j}=\max_{m\geq j \geq p_k} dp_{i-1,j-p_k}+u_k+K$$

初始值 $dp_{0,0}=0$。注意把 $dp_{i,j}$ 弄成 $dp_{i-1,j}$ 再转移。

时间复杂度感觉有点玄学，严格来说可以到 $O(N^2M)$，但是实际上跑不满。

空间的话是 $O(NM)$，但是由于 $dp_i$ 只与 $dp_{i-1}$ 有关系所以可以考虑把第一维滚掉，可以做到 $O(M)$。

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define lowbit(i) (i & -i)
#define inf 0x3fffffff
#define int long long
#define pb push_back
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 5e2 + 5;
const int M = 5e4 + 5;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, m, k, res;
int p[N], u[N], c[N], dp[N][M];
vector<int> id[N];

signed main() {
	FASTIO
	
	cin >> n >> m >> k;
	rep(i, 1, n) cin >> p[i] >> u[i] >> c[i], id[c[i]].pb(i);
	memset(dp, 0xcf, sizeof dp);
	dp[0][0] = 0;
	rep(i, 1, n) {
		rep(j, 0, m) dp[i][j] = dp[i - 1][j];
		for(auto cl : id[i]) {
			pre(j, m, p[cl]) {
				dp[i][j] = max(dp[i][j], dp[i][j - p[cl]] + u[cl]);
				dp[i][j] = max(dp[i][j], dp[i - 1][j - p[cl]] + u[cl] + k);
			}
		}
	} 
	rep(i, 0, m) res = max(res, dp[n][i]);
	cout << res;
	return 0;
}

```

后记：复杂度就是 $O(NM)$ 的，因为总共只会枚举 $N$ 个东西，即第一二两层循环总共是 $O(N)$ 的。

---

## 作者：Lydia1010__ (赞：1)

## 本题思路：
这道题有三个值对答案有贡献，分别是实用度，买它的价值和颜色。

因为每增加一种颜色总价值上涨 $k$，那我们就可以考虑每种颜色去分别处理。针对每一种颜色，考虑选与不选两种情况。当前已经选过这种颜色的物品了那么就直接做一个背包就可以了；没有选过这种颜色也是从没选过的中做一个背包转到选过的转移中（注意，物品价值需要增加 $k$）。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct f{int p,u,c;}a[505];
int dp[50005],dp1[50005],pd[50005];
bool cmp(f x,f y){return x.c<y.c;}
int n,x,k,ans=0;
void pdd(int l,int r){
	for(int i=0;i<=x;i++) dp1[i]=0;
	for(int i=l;i<=r;i++){
		for(int j=x;j>=a[i].p;j--){
			if(dp1[j]<dp1[j-a[i].p]+a[i].u){
				dp1[j]=dp1[j-a[i].p]+a[i].u;
				ans=max(ans,dp1[j]);
			}
		}
		for(int j=x;j>=a[i].p;j--){
			if(dp1[j]<dp[j-a[i].p]+a[i].u+k){
				dp1[j]=dp[j-a[i].p]+a[i].u+k;
				ans=max(ans,dp1[j]);
			}
		}
	}
	for(int i=0;i<=x;i++) dp[i]=max(dp[i],dp1[i]);
}
signed main(){
	cin>>n>>x>>k;
	for(int i=1;i<=x;i++)dp[i]=-1;
	for(int i=1;i<=n;i++){cin>>a[i].p>>a[i].u>>a[i].c;}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;){
		int l=i,r=i;
		while(a[r+1].c==a[l].c)r++;
		for(int j=0;j<=x;j++)pd[j]=1;
		pdd(l,r);
		i=r+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zhangzheng2026 (赞：1)

考虑将每一种颜色分开讨论，所以我们先按颜色排序。设 $f_{i,j,1/0}$ 表示前 $i$ 个数中花 $j$ 元，选或没选当前颜色的衣服，能得到的最大满意度。对于同一种颜色的产品，要么是已经选过当前颜色，要么是没选过，所以我们可以得到以下转移：  
$$f_{i,j,1}=\max(f_{i-1,j,1},\max(f_{i-1,j-p_i,1},f_{i-1,j-p_i,0}+k)+u_i)$$  
$$f_{i,j,0}=f_{i-1,j,0}$$  
当 $c_i \ne c_{i+1}$ 时，我们需要在统计完当前位置答案后再次更新数组：  
$$f_{i,j,0}=\max(f_{i,j,0},f_{i,j,1})$$  
$$f_{i,j,1}=0$$  
因为开始处理新的颜色时，旧的颜色选或不选都属于不选新颜色的情况。最终的答案就是 $\displaystyle\ \max_{j \le m}(\max(f_{n,j,0},f_{n,j,1}) )$ 了。  
我在场上压了一维，可以省去 $f_{i,j,0}$ 的转移，速度较快。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,f[50005][2],now,ans;
struct node{int p,u,c;}a[505];
bool cmp(node x,node y){return x.c<y.c;}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>a[i].p>>a[i].u>>a[i].c;
	sort(a+1,a+n+1,cmp);//按颜色排序
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=a[i].p;j--) f[j][1]=max(f[j][1],max(f[j-a[i].p][0]+k,f[j-a[i].p][1])+a[i].u);
		//压维可以省去第二个转移
		if(a[i].c!=a[i+1].c) for(int j=1;j<=m;j++) f[j][0]=max(f[j][0],f[j][1]),f[j][1]=0;
		//颜色交换时再更新一次 
	}
	for(int j=1;j<=m;j++) ans=max(ans,max(f[j][1],f[j][0]));
	cout<<ans;
	return 0;
}
```

---

## 作者：Dtw_ (赞：0)

# 题意
你有 $n$ 个物品，每个物品有 $3$ 个属性，$w,v,c$ 表示这个物品价钱为 $w$，价值为 $v$，颜色为 $c$。

你有 $x$ 元，求最大的价值。价值为 $V + t\times k$ 其中 $k$ 是给定常数，$V$ 为所选的所有物品的价值，$t$ 为所选颜色的种类数。
# Solution
我们可以背包解决 $V$，但是 $t$ 这个限制不好做。

考虑我们设 $f_{i, j}$ 表示只买 $c\in[1,i]$ 的物品此时用了 $j$ 元钱的最大价值。

考虑我们转移的时候要么我们从来没选过颜色为 $i$ 的，那就是：

$$f_{i,j} = f_{i - 1, j - w} + v + k$$

要么选过颜色为 $i$ 的，即：

$$f_{i,j} = f_{i, j - w} + v$$

要么当前这个不选 $f_{i,j} = f_{i - 1, j}$。

然后就做完了。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 5e2 + 10, M = 5e4 + 10, inf = 0x3f3f3f3f;

int f[N][M], n, m, k;

vector<pii> c[N];

signed main()
{
    fst
    cin >> n >> m >> k;
    for (int i = 1, w, v, col; i <= n; i++) cin >> w >> v >> col, c[col].emplace_back(w, v);
    memset(f, -inf, sizeof f);
    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++) f[i][j] = max(f[i][j], f[i - 1][j]);
        for (auto r : c[i])
        {
            int w = r.first, v = r.second;
            for (int j = m; j >= w; j--) f[i][j] = max({f[i][j], f[i - 1][j - w] + v + k, f[i][j - w] + v});
        }
    }
    int res = -inf;
    for (int i = 1; i <= m; i++) res = max(res, f[n][i]);
    cout << res;
    return 0;
}
```

---

## 作者：_czy (赞：0)

考虑将不同颜色分开，可以按颜色排序后进行背包。

设 $f_{i,j,0/1}$ 表示考虑前 $i$ 个花费为 $j$ 选/不选当前颜色，分讨 $c_i$ 是否等于 $c_{i-1}$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,x,k;
ll f[503][50003][2];
struct node{
	int p,u,c;
}a[503];
bool cmp(node a,node b){
	return a.c<b.c;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>x>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].p>>a[i].u>>a[i].c;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=x;j;j--){
			if(a[i].c==a[i-1].c){
				f[i][j][0]=f[i-1][j][0];
				if(j>=a[i].p)f[i][j][1]=max(f[i-1][j-a[i].p][0]+k,f[i-1][j-a[i].p][1])+a[i].u;
				f[i][j][1]=max(f[i][j][1],f[i-1][j][1]);
			}else{
				f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
				if(j>=a[i].p)f[i][j][1]=max(f[i-1][j-a[i].p][0]+k,f[i-1][j-a[i].p][1]+k)+a[i].u;
			}
		}
	}
	cout<<max(f[n][x][0],f[n][x][1]);
}
```

---

## 作者：liugh_ (赞：0)

### [[ABC383F] Diversity](https://www.luogu.com.cn/problem/AT_abc383_f)

> $n$ 个物品有花费 $c_i$ 价值 $w_i$ 颜色 $col_i$，选了 $t$ 种颜色的物品时总价值为 $tk+\sum w_i$，其中 $k$ 为给定的常数。给定花费上限 $m$ 求最大价值。$n,col_i\le 500$，$m\le 50000$。

除去颜色的限制就是背包问题了，于是考虑对 dp 稍作修改。

颜色是多的，不能加入状态，考虑按颜色分组，每选一个组就能多获得 $k$ 的价值。一个组有选和不选两种状态，考虑加入状态，设 $f(i,j,0/1)$ 为前 $i$ 个组花费为 $j$ 且是 $(1)$ 否 $(0)$ 选了当前组时的最大价值。对于当前组 $i$，有
$$
f(i,j,0)=\max\{f(i-1,j,0),f(i-1,j,1)\}
$$
枚举 $i$ 内物品 $(c,w)$，有
$$
f(i,j,1)\xleftarrow{\max} w+\max\{f(i,j-c,0)+k,f(i,j-c,1)\}
$$
注意转移顺序

- 组内物品可多选且互不影响，应先枚举组内物品 $(c,w)$ 再枚举花费 $j$。
- 一个物品至多选一次，故花费 $j$ 应从大到小枚举。

时间复杂度 $\Theta(nm)$。

```cpp
for(int i=1;i<=n;i++){
    for(int j=0;j<=m;j++)f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
    for(auto [c,w]:a[i]){
        for(int j=m;j>=c;j--){
            tomax(f[i][j][1],w+max(f[i][j-c][0]+K,f[i][j-c][1]));
            tomax(ans,max(f[i][j][0],f[i][j][1]));
        }
    }
}
```

---

## 作者：o06660o (赞：0)

# ABC383F 题解

[英文题面](https://atcoder.jp/contests/abc383/tasks/abc383_f)

## 题意

已知 $N$ 件商品，第 $i$ 件商品的价格为 $P_i$，价值为 $U_i$，颜色为 $C_i$；和一个给定的常数 $K$。

你希望购买总价格不超过 $X$ 单位的商品（每件可以不买或买一个），使得 $S + T \times K$ 最大。其中 $S$ 是选择的商品总价值，$T$ 是这些商品的不同颜色数。

数据范围：

- $1 \le N, C_i \le 500$；
- $1 \le K, P_i, U_i \le 10^9$；
- $1 \le X \le 5 \times 10^4$。

## 思路

不难想到这是背包问题的变式，但是目标值有两个变量。我们可以先看看每次选择一个新商品对目标值的影响：
$$\Delta F_i = U_i + \begin{cases}K & \text{没有选择过 } C_i \\ 0 & \text{已经选择过 } C_i \end{cases}$$
可以发现第一项就是背包板子，第二项启示我们可以根据颜色来分组决策。那么先根据颜色给商品排个序，依旧定义 $f(i, j)$ 为考虑前 $i$ 个商品用去价值 $j$ 所得的最大目标值。

如果已经选择过 $C_i$, 转移方程就是简单的
$$f(i, j) \leftarrow f(i - 1, j - P_i) + U_i$$

如果没有选择过 $C_i$, 那么这一整组, $i$ 之前的商品等于被跳过了，记录上一组最后位置是 $p$，转移方程变为了
$$f(i, j) \leftarrow f(p, j - P_i) + U_i + K$$

然后考虑用滚动数组优化，在遇上新一组商品的时候令 `vector<int>g = f` 保留上一组最后位置的状态，

```cpp
for (int j = X; j >= P[i]; j--) {
    f[j] = max(f[j], f[j - P[i]] + U[i]);
    f[j] = max(f[j], g[j - P[i]] + U[i] + K);
}
```

最后考虑一下边界条件，发现全部初始化为 $0$ 就可以了。

## 代码

```cpp
#include <bits/stdc++.h>
#define all(a) a.begin(), a.end()
using namespace std;
using ll = long long;  // 2.15e9, 9.22e18
using pii = pair<int, int>;
struct Item {
    int p, u, c;
    bool operator<(const Item& rhs) const { return c < rhs.c; }
};

int n, x, k;
vector<ll> f;
vector<Item> a;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> x >> k;
    a.resize(n);
    f.resize(x + 1);
    for (int i = 0; i < n; i++) cin >> a[i].p >> a[i].u >> a[i].c;
    sort(all(a));

    int prec = 0;
    vector<ll> g = f;
    for (int i = 0; i < n; i++) {
        if (a[i].c != prec) {
            prec = a[i].c;
            g = f;
        }
        for (int j = x; j >= a[i].p; j--) {
            f[j] = max(f[j], f[j - a[i].p] + a[i].u);
            f[j] = max(f[j], g[j - a[i].p] + a[i].u + k);
        }
    }
    cout << f[x] << "\n";
    return 0;
}
```

---

## 作者：11400F (赞：0)

### AT_ABC383_F 题解

#### 题目大意：

有 $N$ 种商品，其中第 $i$ 件商品的价格为 $P_i$，贡献为 $U_i$，颜色为 $C_i$。每一种商品只能选 $1$ 次，总价最多为 $X$。

令 $S$ 为所选所有商品的贡献之和，$T$ 为所选商品的颜色个数，$K$ 为题目给定常数，求 $S+T\times K$ 的最大值。

#### 思路：

第一眼就是一个普通的 $0/1$ 背包，但是这道题里面多了个颜色，我们要转化一下思路。

我们可以把 $K$ 理解为：当新增了一种颜色的时候，答案加上 $K$。

所以我们把每一个颜色单独拿出来，进行 dp（因为 $C_i \le N$，所以很好做）。

我们设 $dp_{i, w}$ 为选了颜色 $1\sim i$ 的时候，容量为 $w$ 的最大答案。我们要从上一个颜色转移过来，那么首先就先让所有的 $dp_{i, w} = dp_{i-1, w}$，就是处理边界问题。

假设当前枚举的商品编号为 $y$（此时 $C_y=  i$），那么转移如下：
$$
dp_{i, w}=\left\{
\begin{aligned}
&\max\{dp_{i, w}, dp_{i-1, w-P_y} + U_y+ K, dp_{i, w-P_y} + U_y\} &(w \ge P_y)\\
&dp_i, w &(w < P_y)
\end{aligned}
\right.
$$
解释一下：

- $\max$ 里的第一项 $dp_{i, w}$ 就是不选这个商品的答案，
- 第二项 $dp_{i-1, w-P_y} + U_y+ K$ 就是选了这个商品，并且这个颜色是第一次选，就要从 $i-1$ 的状态转移过来，并且答案还要加上 $K$。
- 第三项 $dp_{i, w-P_y} + U_y$ 就是选了这个商品，并且这个颜色之前已经选过了，那么就从 $i$ 的状态转移。

$w < P_y$ 的情况应该很好懂，就是如果背包容量小于商品重量，那么就不能选。

最后取 $\displaystyle\max_{0\le w \le X} dp_{n, w}$ 即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 504, M = 50004;
int n, k, x;
typedef long long ll;
struct Goods{
    int pri, usm; //pow!
};
vector<Goods> goods[N]; //goods[i]: color = i;
ll dp[N][M];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n>>x>>k;
    int p, u, c;
    for(int i=1;i<=n;i++){
        cin>>p>>u>>c;
        goods[c].push_back({p, u});
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=x;j++){
            dp[i][j] = dp[i-1][j];
        }
        for(Goods g:goods[i]){
            for(int w=x;w>=g.pri;w--){
                dp[i][w] = max(dp[i][w], dp[i-1][w-g.pri] + g.usm + k);
                dp[i][w] = max(dp[i][w], dp[i][w-g.pri] + g.usm);
            }
        }
    }
    ll ans = 0;
    for(int i=0;i<=x;i++){
        ans = max(ans, dp[n][i]);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：cyq32ent (赞：0)

按颜色排序，考虑前 $i$ 种物品，花 $j$ 元的最优方案。有 

$$f_{i,j}=\max\{f_{i-1,j},f_{i-1,j-u_i}+p_i,f_{l_i,j-u_i}+p_i+K\}$$

其中三项分别为不选、选了选过的颜色、选了且选的是之前没选的颜色。其中 $l_i$ 为上一个颜色不同的点的下标。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef struct{int p,u,c;}I;I T[505];
int N,X,K,f[505][50505],lst[505];
signed main(){
	cin>>N>>X>>K;
	for(int i=1;i<=N;i++)cin>>T[i].p>>T[i].u>>T[i].c;
	sort(T+1,T+1+N,[&](I i,I j){return i.c<j.c;});
	for(int i=1;i<=N;i++)lst[i]=(T[i].c==T[i-1].c?lst[i-1]:i-1);
	for(int i=1;i<=N;i++)for(int j=0;j<=X;j++){
		f[i][j]=f[i-1][j];if(j<T[i].p)continue;
		if(T[i].c==T[i-1].c)f[i][j]=max(f[i-1][j-T[i].p]+T[i].u,f[i][j]);
		f[i][j]=max(f[i][j],f[lst[i]][j-T[i].p]+T[i].u+K);
	}int ans=0;
	for(int i=0;i<=X;i++){
		ans=max(ans,f[N][i]);
	}cout<<ans<<endl;
	
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

涉及到选物品的颜色，因此将物品按照颜色排序。考虑如下 dp：$dp_{i,j,0/1}$ 表示前 $i$ 个物品，花了 $j$ 块，**跟第 $i$ 个物品同颜色的物品**是否选，最大价值。

转移要分两种情况。
### 第 $i$ 个物品和第 $i-1$ 个物品同色
这时，$dp_{i-1,j,0}\to dp_{i,j,0}$，只能不选；$\max(dp_{i-1,j-p_i,0}+u_i+k,dp_{i-1,j-p_i,1}+u_i)\to dp_{i,j,1}$，讨论前面物品中是否选跟 $i$ 同色的。
### 第 $i$ 个物品和第 $i-1$ 个物品不同色
这时，$\max(dp_{i-1,j,0},dp_{i-1,j,1})\to dp_{i,j,0}$，$\max(dp_{i-1,j-p_i,0},dp_{i-1,j-p_i,1})+u_i+k\to dp_{i,j,1}$，讨论前面一种颜色的物品选不选。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
long long dp[501][50001][2],ans;
struct P{
	int a,b,c;
	bool operator<(const P&t){return c<t.c;}
}s[510];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int w=1;w<=n;w++)scanf("%d%d%d",&s[w].a,&s[w].b,&s[w].c);
	sort(s+1,s+n+1);
	for(int w=1;w<=n;w++){
		for(int x=0;x<m;x++)dp[w][x][0]=max(dp[w-1][x][0],((s[w].c!=s[w-1].c)?dp[w-1][x][1]:0)),dp[w][x][1]=dp[w-1][x][1];
		for(int x=m;x>=s[w].a;x--)
			if(s[w].c==s[w-1].c)dp[w][x][1]=max(dp[w][x][1],max(dp[w-1][x-s[w].a][1]+s[w].b,dp[w-1][x-s[w].a][0]+s[w].b+k));
			else dp[w][x][1]=max(dp[w-1][x-s[w].a][1],dp[w-1][x-s[w].a][0])+s[w].b+k;
	}
	for(int w=1;w<=n;w++)for(int x=0;x<=m;x++)ans=max(ans,max(dp[w][x][0],dp[w][x][1]));
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：zhangbo1000 (赞：0)

有钱数，有价值，考虑背包。

但是只知道容量和收益无法得知方案，无法处理 $K$ 的贡献，所以考虑在传统 01 背包上加一维颜色：令 $dp_{i,k}$ 表示考虑了前 $i$ 种颜色，已用容量不超过 $k$ 的最大收益。

对于价值为 $w$，价格为 $v$，颜色为 $c$ 的物品，有转移：

$$dp_{c,k}=\max(dp_{c-1,k-v}+K+w,dp_{c,k-v}+w,dp_{c-1,k},dp_{c,k})$$

含义是对于这个物品有 $3$ 种决策：

- 不选这个物品，收益为 $0$，从 $dp_{c-1,k}$ 和 $dp_{c,k}$ 转移来。

- 选这个物品，此前已经选择过该颜色的物品，收益为 $w$，从 $dp_{c,k-v}$ 转移来。

- 选这个物品，此前未选择过该颜色的物品，收益为 $w+K$，从 $dp_{c-1,k-v}$ 转移来（从上个颜色转移以确保没有选择过这种颜色的物品。）。

**注意不一定每种颜色的物品都有，转移可能出现“断档”，可以特判一下，或者干脆给每种颜色加一个价值为 $-K$（想一想为什么），价格为 $0$ 的物品**，~~你以为我会告诉你我赛时挂在这了吗？~~

此外实现时颜色维是可以滚动掉的。

[代码与评测记录。](https://atcoder.jp/contests/abc383/submissions/60556107)

---

## 作者：YangRuibin (赞：0)

## 思路
看这个题意可以联想到经典 01 背包，唯一的不同是多了“颜色”这个附加价值。首先枚举顺序肯定不影响结果，所以先把相同颜色归类。

依题意，对于颜色的价值，每种颜色只能计算一次，也就是说**同种颜色**的第 $i$ 个物品，如果选了，那么只有当 $i$ 之前**都没选**时才可以附加颜色价值。所以除了正常以物品为阶段，空间为状态，还要附加一维，表示这种颜色到第 $i$ 个物品是否都没选，$0$ 代表都没选，$1$代表**不保证**都没选（注意我的用词“不保证”）。

$f_{i,j,0/1}$ 表示前 $i$ 种物品，占用 $j$ 的空间，是否保证这种颜色此物品之前都没选。依照经典的背包 DP 转移，可得出以下转方程（设 $q_i$ 为归类后往前第一个与 $i$ 颜色不同的物品）。


$$
f_{i,j,0}=\begin{cases}
f_{i-1,j,0} & i>q_i+1\\
\max(f_{i-1,j,0},f_{i-1,j,1}) & i=q_i+1
\end{cases}
$$

$$
f_{i,j,1}=\max(f_{i-1,j,1},f_{i-1,j-P_i,1}+U_i,f_{i-1,j-P_i,0}+U_i+K)
$$

同样的，也可以和经典背包一样将 $i$ 这一维省略。

## 关于正确性
有读者可能会问：$f_{i,j,1}$ 只是不保证都没选，岂不是会和 $f_{i,j,0}$ 重复？不用担心。我们设置附加维度就是要把“都没选”的情况单独提出来，方便正确转移。并且我们求价值最大值，即使决策重复也会得到最大的值。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=505,M=5e4+5,inf=0x3f3f3f3f3f3f3f3fll;
int n,x,k,p[N],u[N],c[N],f[M][2];
vector<int>g[N];
signed main()
{
	scanf("%lld%lld%lld",&n,&x,&k);
	for(int i=1;i<=n;i++)scanf("%lld%lld%lld",p+i,u+i,c+i);
	for(int i=1;i<=n;i++)g[c[i]].push_back(i);
	for(int i=1;i<=n;i++)
	{
		for(int j=x;~j;j--)f[j][0]=max(f[j][0],f[j][1]);
		for(int id:g[i])
		{
			for(int j=x;j>=p[id];j--)
				f[j][1]=max(f[j][1],max(f[j-p[id]][1]+u[id],f[j-p[id]][0]+u[id]+k));
		}
	}
	int ans=0;
	for(int i=0;i<=x;i++)ans=max(ans,max(f[i][0],f[i][1]));
	printf("%lld",ans);
	return 0;
}
```

## 拓展
~~本段为笔者口胡，有兴趣的可以去验证一下正确性。~~

有没有可能不需要附加维度就可以 DP？理论上是有的。其它的同经典背包，对于附加颜色价值的转移，我们直接从前文提到的 $q_i$ 转移过来，就能保证它是此颜色第一个选的，从而保证不会重复计算颜色价值。不过这样就不能把 $i$ 这一维省略或滚动掉，空间复杂度稍逊与原做法。

---

