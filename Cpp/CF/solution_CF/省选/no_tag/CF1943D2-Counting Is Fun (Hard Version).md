# Counting Is Fun (Hard Version)

## 题目描述

This is the hard version of the problem. The only difference between the two versions is the constraint on $ n $ . You can make hacks only if both versions of the problem are solved.

An array $ b $ of $ m $ non-negative integers is said to be good if all the elements of $ b $ can be made equal to $ 0 $ using the following operation some (possibly, zero) times:

- Select two distinct indices $ l $ and $ r $ ( $ 1 \leq l \color{red}{<} r \leq m $ ) and subtract $ 1 $ from all $ b_i $ such that $ l \leq i \leq r $ .

You are given two positive integers $ n $ , $ k $ and a prime number $ p $ .

Over all $ (k+1)^n $ arrays of length $ n $ such that $ 0 \leq a_i \leq k $ for all $ 1 \leq i \leq n $ , count the number of good arrays.

Since the number might be too large, you are only required to find it modulo $ p $ .

## 说明/提示

In the first test case, the $ 4 $ good arrays $ a $ are:

- $ [0,0,0] $ ;
- $ [0,1,1] $ ;
- $ [1,1,0] $ ;
- $ [1,1,1] $ .

## 样例 #1

### 输入

```
4
3 1 998244853
4 1 998244353
3 2 998244353
343 343 998244353```

### 输出

```
4
7
10
456615865```

# 题解

## 作者：strcmp (赞：17)

这是积木大赛，所以如果没有 $l < r$ 的限制我们一定有解。

但是有 $l < r$ 的限制，就要看它产生了什么限制。

![](https://cdn.luogu.com.cn/upload/image_hosting/jamyjmlq.png)

对，就是这种类似 CF Logo 的图形。

翻译成人话就是：存在 $i$ 满足 $a_i > a_{i - 1} + a_{i + 1}$，则必定无解。

![](https://cdn.luogu.com.cn/upload/image_hosting/6umv861x.png)

首先无解是一定的，这种情况下 $a_i$ 最多减 $a_{i - 1} + a_{i + 1}$ 次，然后 $a_{i - 1}$ 和 $a_{i + 1}$ 变成 $0$，就消不了了。

那不存在这种情况就合法了吗？这也是容易理解的。

根据积木大赛的结论，我们考虑包含 $a_{i - 1}$ 的所有区间 $[?,\,i - 1]$，我们显然不关心 $?$ 是什么。然后考虑将这个区间多覆盖到 $i$。进而还剩下 $a_{i}' = a_{i} - a_{i - 1}$。如果 $a_{i + 1} - a_i' \ge 0$ 显然能消完 $a_i$（把包含 $a_{i + 1}$ 的区间左端点扩到 $a_i$ 就好了）。对所有 $a_i$ 从外到内这样讨论可知必然有解。

---

好，现在就是计数所有满足 $a_{i} \ge a_{i - 1} - a_{i - 2}$  的序列方案数了。

此时有一个 naive 的做法就是设个 $f_{i,\,x,\,y}$ 代表前 $i$ 个位置 $i$ 位置是 $x$ 而 $i - 1$ 位置是 $y$ 的方案数。朴素实现 $\Theta(nk^3)$，后缀和优化一下 $\Theta(nk^2)$。后者能过 Easy Version。

但还是不够切这道题。

从转移方程上找东西显然是无用功，只能继续发掘性质。比如——考虑容斥。

发现一个重要性质：不合法的位置不会相邻。

很简单，因为你随便考虑某两个相邻的不合法位置，假设分别是 $a_{i - 1}$ 和 $a_i$。

则 $a_{i - 1} > a_{i - 2} + a_{i},\,a_{i} > a_{i - 1} + a_{i + 1} \Rightarrow a_{i} > a_{i} + a_{i - 2} + a_{i + 1} \Rightarrow a_{i - 2} + a_{i + 1} < 0$。显然矛盾。

![](https://cdn.luogu.com.cn/upload/image_hosting/7qc1n5iu.png)

不合法位置不相邻，给我们优化复杂度以极大方便。

一个明显的好处就是我们可以直接从 $i - 2$ 位置转移过来。进而不用考虑 $i - 3$ 选取了什么。

设 $f_{i,\,j}$ 代表考虑到第 $i$ 个数，末尾是 $j$ 的合法序列数。

则有：

$$
f_{i,\,j} \leftarrow \sum f_{i - 1} - \sum_{x = 0}^{k - j - 1} f_{i - 2,\,x} \times (k - j - x)
$$

因为 $i$ 不合法所以我们不用考虑 $i - 1$ 不合法的可能。后面一项相当于计数 $i$ 位置之前都合法，而 $i$ 位置不合法的序列并容斥。

前面一坨直接记录和，后面一坨倒序枚举 $j$ 前缀和记录 $k - j - x$  的增量即可。

时间复杂度 $\Theta(nk)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using ld = double;
typedef long long int ll;
using pdi = pair<ld, int>;
using vec = vector<int>;
constexpr int maxn = 3e3 + 10; 
int T, n, k, mod, f[maxn][maxn], g[maxn][maxn];
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &k, &mod);
		rep(i, 0, n + 1) rep(j, 0, k) f[i][j] = g[i][j] = 0;
		f[0][0] = 1; rep(i, 0, k) f[1][i] = g[0][i] = 1, g[1][i] = i + 1;
		rep(i, 2, n + 1) {
			int s = 0;
			per(j, k, 0) f[i][j] = ((ll)g[i - 1][k] - (s = (s + g[i - 2][k - j - 1]) % mod) + mod) % mod;
			rep(j, 0, k) g[i][j] = ((j ? g[i][j - 1] : 0) + f[i][j]) % mod;
		}
		printf("%d\n", f[n + 1][0]);
	}
	return 0;
}
```

  同类题（lca 长训营入营测试赛，侵删）：给定长度为 $n$ 的非负整数序列 $w$。定义一个长度为 $n$ 的序列 $a$ 的权值是 $\prod\limits_{i = 1}^{n - 2} w_{\max \{ a_i,\,a_{i + 1},\,a_{i + 2}\}}$，求所有值域在 $[0,\,n]$ 长度为 $n$ 的非负整数序列的权值和。对 $998244353$ 取模，$n \le 4 \times 10^3$。

---

## 作者：honglan0301 (赞：13)

upd：感谢 Reunite 指出问题，修改了关于“合法序列”的表述。

## 前置知识（D1）

我们定义长为 $m$ 的序列 $x$ “合法“当且仅当对于 $\forall 1<i<m, x_i\leq x_{i-1}+x_{i+1}$。

那么由 D1 可知，序列 $b_1,b_2,\dots,b_n$ 是“好序列”要求序列 $b'=(0,b_1,b_2,\dots,b_n,0)$ 合法。

于是转换成对“长为 $n+2$，首尾都是 $0$ 的合法序列”计数，容易设计 $O(n^3)$ dp 通过 D1。这种做法的瓶颈在于需要同时记录 $b_i$ 和 $b_{i-1}$ 的信息，下面我们尝试优化。

## 分析

注意到，$b_{i}>b_{i-1}+b_{i+1}$ 与 $b_{i-1}>b_i+b_{i-2}$ 不可能同时发生，这启示我们从反面考虑。

记 $f_{i,j}$ 表示长为 $i$ 末尾为 $j$ 的**合法**序列数量，$g_{i,j}$ 表示长为 $i$，末尾为 $j$，且恰好在位置 $i$ 处**不合法**的序列数量（即使得 $b_{1,2,\dots,i-1}$ 合法的不合法序列数量）。

这样的好处是 $g_{i,j}$ 可以直接从 $f_{i-2,\_}$ 处转移得来，不必担心与 $g_{i-1,\_}$ 算重，式子如下：

$$g_{i,j}=\sum\limits_{p=0}^k f_{i-2,p}\times\max(k-j-p,0)$$

$$f_{i,j}=\sum\limits_{p=0}^kf_{i-1,p}-g_{i,j}$$

正确性显然。最后 $g$ 那里前缀和优化一下时间复杂度就 $O(n^2)$ 了，可以通过 D2。

## 代码

[赛时代码](https://codeforces.com/contest/1943/submission/251770959)。赛时 $f_{i,j}$ 的转移有点麻烦，用上文所说的转移方式即可。

---

## 作者：EuphoricStar (赞：8)

被自己的赛时智障操作气笑了。谁告诉你容斥钦定了几个要记到状态里面的。。。/tuu

显然先找“好数组”的充要条件。对原数组 $a$ 差分，设 $b_i = a_i - a_{i - 1}$。那么一次可以选择一对 $(i, j)$ 满足 $i \le j - 2$，然后给 $b_i$ 减 $1$，给 $b_j$ 加 $1$。

我们从左往右操作。注意到我们不能操作相邻的一对元素，所以若某个时刻 $b_i > 0$ 且 $b_{1 \sim i - 2}$ 都为 $0$ 就不合法。这就是充要条件。

充要条件可以表述成 $b_i + \sum\limits_{j = 1}^{i - 2} b_j \ge 0$，即 $a_i - a_{i - 1} + a_{i - 2} \ge 0$，注意 $a_0 = a_{n + 1} = 0$。

对于 $n \le 400$ 可以直接做一个 $O(n^3)$ dp，设 $f_{i, j, k}$ 为考虑了 $[1, i]$ 的前缀，$a_{i - 1} = j, a_i = k$ 的方案数。因为合法的 $a_{i - 2}$ 是一段后缀，所以预处理后缀和即可做到 $O(1)$ 转移。这样可以[通过 D1](https://codeforces.com/problemset/submission/1943/251749221)。

对于 $n \le 3000$ 显然不能这么做了。发现 dp 状态数都成瓶颈了，换个思路，考虑容斥，钦定一些位置 $i$ 是满足 $a_i > a_{i - 1} + a_{i + 1}$（显然这些位置不会相邻），容斥系数就是 $-1$ 的位置个数次方。

对于 $i$ 被钦定的方案，注意到我们不用枚举 $a_i$，只要知道 $a_{i - 1}$ 和 $a_{i + 1}$，就能算出 $a_i$ 的取值个数为 $m - a_{i - 1} - a_{i + 1}$（令题面中的 $k$ 为 $m$）。

所以设 $f_{i, j}$ 为考虑了 $[1, i]$ 的前缀，$a_i = j$，每种方案乘上容斥系数的和。那么有 $f_{i, j} = \sum\limits_{k = 0}^m f_{i - 1, k} - (m - j - k) f_{i - 2, k}$，容易前缀和优化。

时间复杂度 $O(n^2)$。

[code](https://codeforces.com/problemset/submission/1943/251867516)

---

## 作者：Alex_Wei (赞：7)

### *[D2. Counting Is Fun (Hard Version)](https://www.luogu.com.cn/problem/CF1943D2)

你需要会 [D1](https://www.luogu.com.cn/article/qc5ynhql)。

首先有结论：序列合法的充要条件为 $\forall 1\leq i \leq n$，$a_i \leq a_{i - 1} + a_{i + 1}$。直接 DP 无法避免记录 $a_{i - 1}$ 和 $a_i$，的复杂度至少为 $\mathcal{O}(n ^ 3)$。

考虑容斥，钦定某些位置不满足条件，则相邻的位置一定不会同时不满足条件。

设 $f_{i, x}$ 表示 $a_i = x$ 的答案，则根据是否钦定 $a_{i + 1}$ 不满足条件，有两种转移方式：

- 若不钦定 $a_{i + 1}$ 不满足条件，则 $a_{i + 1}$ 任意。对 $0\leq y\leq k$，$f_{i, x}\to f_{i + 1, y}$。
- 若钦定 $a_{i + 1}$ 不满足条件，则考虑 $a_{i + 2}$ 的值 $y$。首先有 $x + y\leq k$，此时 $a_{i + 1}$ 有 $k - (x + y)$ 种取值。于是对 $0\leq y\leq k - x$，$-(k - (x + y))f_{i, x}\to f_{i + 2, y}$。

使用前缀和优化，时间复杂度 $\mathcal{O}(n ^ 2)$。[代码](https://codeforces.com/contest/1943/submission/251757628)。

---

## 作者：zzy0618 (赞：4)

[题目链接](https://www.luogu.com.cn/problem/CF1943D2)

首先转化一下题意，题目说对一段区间减 $1$，不能单点修改，所以当 $a_i$ 被减时，必有它旁边的数字也被减，故要有 $a_i\le a_{i-1}+a_{i+1}$。为了方便，不妨令 $a_0=a_{n+1}=0$。

如果进行 dp，由于刚才的不等式，必然要维护 $a_i,a_{i-1}$ 的信息才能转移，时间复杂度为 $O(n^3)$，是 D1 的解法。

考虑容斥，用全部的数量减去不合法的。设 $f_{i,j}$ 为第 $i$ 个数字为 $j$ 的**合法方案**个数，算总数为 $\sum_{l=0}^{k}f_{i-1,l}$ 种，但要减去**在 $i$ 处**不合法的，共 $\sum_{l=0}^{k-j}f_{i-2,l}\times(k-j-l)$ 种。解释一下 $k-j-l$ 怎么来，由 $a_i\le a_{i-1}+a_{i+1}$ 得不合法的情况 $a_i>a_{i-1}+a_{i+1}$。由于上限为 $k$ 故能够使得**在 $i$ 处**不合法的 $a_i$ 有 $k-a_{i-1}-a_{i+1}$ 个，即我们枚举的 $l,j$。

这样我们可以得出方程：

$f_{i,j}=\sum_{l=0}^{k}f_{i-1,l}-\sum_{l=0}^{k-j}f_{i-2,l}\times(k-j-l)$。

最终答案为 $f_{n+1,0}$。

通过前缀优化实现 $O(n^2)$。具体地说，方程的前一半前缀很好做，后一半我们可以让 $j$ 从大往小做，$\sum_{l=0}^{k-j}f_l\times(k-j-l)$ 到 $\sum_{l=0}^{k-j-1}f_l\times(k-j-l-1)$ 的变化为 $\sum_{l=0}^{k-j-1}f_l$，故使用前缀也很好做。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+5;
int t,n,k,p;
int f[N][N],s[N][N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k>>p;
		const int P=p;
		f[0][0]=1;
		for(int i=0;i<=k;++i)
			f[1][i]=1,s[0][i]=1,s[1][i]=i+1;			
		for(int i=2;i<=n+1;++i){
			int sum=0;
			for(int j=k;j>=0;--j){
				f[i][j]=s[i-1][k];
				(sum+=s[i-2][k-j-1])%=P;
				(f[i][j]+=P-sum)%=P;
			}
			for(int j=0;j<=k;++j){
				s[i][j]=f[i][j];
				if(j)(s[i][j]+=s[i][j-1])%=P;
			}
		}
		cout<<f[n+1][0]<<'\n';
		for(int i=0;i<=n+1;++i)
			for(int j=0;j<=k;++j)
				f[i][j]=s[i][j]=0;
	}
	return 0;
}
```

---

## 作者：hxhhxh (赞：3)

一种没有用到容斥的思路。

### 前置

[D1](https://www.luogu.com.cn/problem/CF1943D1) 的做法。这里简单描述一下。

这里直接给出结论，一个序列是好的，当且仅当 $\forall i\in[1,n],a_i\leq a_{i-1}+a_{i+1}$。这里认为 $a_0=a_{n+1}=0$。

设计 $f_{i,j,k}$ 表示目前填了前 $i$ 个数，$a_i=j$ 且 $a_{i-1}=k$ 的方案数。容易用前缀和优化成 $O(nk^2)$。

### 本题思路

猜测时间复杂度为 $O(nk)$，所以设计 $f_{i,j,k}$ 表示目前填了前 $i$ 个数，$a_i=j$，状态为 $k$ 的方案数。这里的 $k$ 是 $O(1)$ 的。

由于合法条件和 $3$ 个位置有关，所以逐个转移很难不记录两个数从而状态数爆炸，所以考虑找一些性质。

只有 $a_i>\max(a_{i-1},a_{i+1})$ 的位置才有可能不合法，也就是先递增后递减的位置。所以我们把 $k$ 记为 $[a_i>a_{i-1}]$。容易发现，最终答案为 $f(n+1,0,0)$，初始状态为 $f(0,0,0)=1$。

现在只有 $(i,x,1)\to (i+1,y,0)$ 的转移是有问题的，我们没有记录上一个数的具体数值，不能直接转移。所以考虑从它的上一步开始，观察转移形式： $(i-1,x,0/1)\to(i,t,1)\to(i+1,y,0)$。

发现 $t\in[\max(x+1,y),\min(k,x+y)]$ 时这个转移是合法的。所以我们可以枚举 $t,y$，进行转移 $(i-1,x,0/1)\to(i+1,y,0)$。观察到 $t$ 与状态无关，所以如果枚举 $y$，只需要乘上选 $t$ 的方案数即可。

剩下的转移都一定合法，所可以直接转移。到这里，朴素的转移是 $O(k)$ 的，所以时间复杂度为 $O(nk^2)$。

发现把 $\min$ 和 $\max$ 拆开后，系数只和 $x$ 或 $y$ 有关（具体细节在代码的注释内），所以也可以用前缀和优化。时间复杂度 $O(nk)$。

### 代码

代码中的 $g$ 是辅助数组。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,mod,g[3005][3005][3];
void add(int&x,int v){
	x+=v;
	if(x>mod) x-=mod;
}
void addl(int i,int l,int r,int k,int v){//给 f(i,j,k%2) 加上 k==2?j*v:v，其中 j 在区间 [l,r] 内
	add(g[i][l][k],v);
	add(g[i][r+1][k],mod-v);
}
void doing(){
	cin>>n>>k>>mod;
	for(int i=0;i<=n+1;i++) for(int j=0;j<=k;j++) for(int l=0;l<3;l++) g[i][j][l]=0;
	g[0][0][0]=1,g[0][1][0]=-1;
	for(int i=0;i<=n;i++){
		for(int j=1;j<=k;j++) for(int l=0;l<3;l++) add(g[i][j][l],g[i][j-1][l]);
		for(int x=0;x<=k;x++){
			int p=(x*g[i][x][2]+g[i][x][0])%mod,s=(p+g[i][x][1])%mod;//p=f(i,x,0),s=f(i,x,0/1) 
			addl(i+1,0,x,0,p);		//(i,x,0  )->(i+1,y,0)
			addl(i+1,x+1,k,1,s);	//(i,x,0/1)->(i+1,y,1)
			//以下都是 (i,x,0/1)->(i+2,x,0)
			addl(i+2,0,min(x,k-x),2,s);					//max(x+1,y)=x+1,min(k,x+y)=x+y	 v=y 
			addl(i+2,max(x,k-x)+1,k,0,(k+1)*s%mod);		//max(x+1,y)=y  ,min(k,x+y)=k	 v=k-y+1，这是 k+1 部分
			addl(i+2,max(x,k-x)+1,k,2,mod-s);           //max(x+1,y)=y  ,min(k,x+y)=k	 v=k-y+1，这是 -y 部分
			if(x<=k-x) addl(i+2,x+1,k-x,0,(x+1)*s%mod);	//max(x+1,y)=y  ,min(k,x+y)=x+y	 v=x+1
			else       addl(i+2,k-x+1,x,0,(k-x)*s%mod);	//max(x+1,y)=x+1,min(k,x+y)=k	 v=k-x
		}
	}
	cout<<(g[n+1][0][0]%mod+mod)%mod<<"\n";//答案为 f(n+1,0,0)
}
signed main(){
	int T;
	cin>>T;
	while(T--) doing();
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

人人都会 $\rm D1$：一个序列是“好的”的充要条件是 $\forall 1 \le i \le n$，$b_i \le b_{i-1}+b_{i+1}$，其中 $b_0=b_{n+1}=0$。设 $dp_{u,v_1,v_2}$ 为确定到了 $u$，其中 $b_{u-1}=v_1$，$b_u = v_2$ 的方案数，使用前缀和优化。

考虑到 $b_i > b_{i-1}+b_{i+1}$ 和 $b_{i+1} > b_i + b_{i+2}$ 并不能同时成立，考虑只记录第二维并且使用容斥原理。$dp_{u,v}$ 表示确定到了 $u$，$b_u = v$ 且 $1$ 到 $u-1$ 位置都合法的方案数。

考虑计算 $dp_{u+1,v}$ 时，先不管第 $u$ 个位置是否合法，加入 $\sum_{i=0}^k dp_{u,i}$ 进答案中。再减去第 $u$ 个位置不合法的情况。注意到如果第 $u$ 个位置不合法，第 $u-1$ 个位置一定合法，所以借用 $dp_{u-1}$ 的答案，即 $\sum_{i=0}^k dp_{u-1,i} \times \max\{0,k-v-i\}$。

综上所述，转移方程式为：

$$
dp_{u+1,v} = \sum_{i=0}^k dp_{u,i} - \sum_{i=0}^k dp_{u-1,i} \times \max\{0,k-v-i\}
$$

这道题省去一维状态的根本原因是**不可能有相邻的不合法位置**。

[Submission](https://codeforces.com/problemset/submission/1943/252578757)

---

## 作者：Rain_chr (赞：2)

### 题意

我们认为一个序列是好的当且仅当能通过区间减一变成全零序列，其中区间减一不能退化成单点减一。

对所有长度为 $n$，值域在 $[1,m]$ 的好序列计数。

### D1 做法

时间复杂度：$O(n^3)$

对于这种题，我们先可以转化好序列的充要条件。

区间减一，很容易想到差分序列。那么我们对原序列求差分序列，问题就转化为在选择点不相邻的情况下单点减一并单点加一，让 $[1,n+1]$ 全部变成零。

单点减一并单点加一很容易就想到是匹配问题——差分数组总用前面的正数匹配后面的负数，这样就可以了。

我们设 $dif$ 为原序列的差分序列，那么能匹配完当且仅当  $\displaystyle \sum^{i-2}_{j=1} dif_j \ge -dif_i$，这样的话当前这一位能够匹配前面剩下的。

但是我们发现这样很蠢，因为差分数组的前缀和就是原数组，所以上式等价于 $a_{i-2} \ge -a_i+a_{i-1}$，即 $a_{i-2}+a_i \ge a_{i-1}$。

所以，只要原数列对于 $1\le i \le n$ 的下标都满足上述条件，原数列就是合法的。

所以我们设 $dp[i][j][k]$ 表示当前有 $i$ 位，原数列倒数第一位为 $j$，倒数第二位为 $k$，用前缀和优化转移即可。

### D2 做法

时间复杂度：$O(n^2)$

赛时我的思路止步于此，最终也因此下大分。

由于状态数已经不能接受了，我们考虑优化状态。具体的，我们通过容斥将性质弱化。

我们设 $f(i)$ 表示钦定有 $i$ 个位置是不合法的，根据容斥答案显然为 $\displaystyle \sum^{n}_{i=0} (-1)^i f(i)$ 。

可以发现，如果我们要使 $a_{i-2}+a_i \ge a_{i-1}$ 不合法，在已知 $a_{i-2}$ 的情况下，$a_{i-1}$ 是可以直接算的。

**提示**：为什么要用容斥弱化条件，是因为如果我们不容斥，直接算 $a_{i-1}$，我们并不知道 $a_{i-1}$ 造成的贡献是什么。只有容斥，我们才能只考虑当前位。

所以我们可以设 $dp[i][j][k]$ 表示前 $i$ 位，最后一个数为 $j$，当前钦定有 $k$ 个不合法的位置。

再次发现这样很蠢，因为系数仅与钦定的不合法位置个数的奇偶性相关，所以我们就可以优化成 $dp[i][j][0/1]$ 表示其奇偶性。

那么我们现在转移就要分类讨论了：

1. 当前位不钦定产生贡献 
	
那么前一位选啥都可以（因为不钦定），所以直接继承上一位选所有数的答案。

2. 当前位钦定产生贡献

$dp[i][j][k]=\displaystyle \sum^{m}_{l=1} dp[i-2][l][1-k] \times (m-l-j)$

同样可以前缀和优化，具体的，维护 $\displaystyle \sum^{m}_{l=1} dp[i-2][l][1-k] \times (m-l)$ 与 $\displaystyle \sum^{m}_{l=1} dp[i-2][l][1-k]$，分类讨论即可。

### 总结

本题考查了转化条件的能力，对于充要条件进行容斥计数。并且压状态的方式十分巧妙，是一道有思维的计数题。

---

## 作者：Unnamed114514 (赞：0)

[easy](https://www.luogu.com.cn/article/wgmu9mhq)

我们继续发掘性质，发现不合法的位置（$a_i<a_{i-1}-a_{i-2}$）一定不连续。

反证，令 $i,i-1$ 都不合法，得到：

$$a_i<a_{i-1}-a_{i-2}$$

$$a_{i-1}<a_{i-2}-a_{i-3}$$

放缩有：

$$a_i<a_{i-1}-a_{i-2}<a_{i-2}-a_{i-3}-a_{i-2}=-a_{i-3}$$

因此 $a_i+a_{i-3}<0$，又因为 $a_i,a_{i-3}\in [0,k]$，所以显然是不行的。

综上，不合法的点一定不连续。

D1 的 dp 已经很难优化了，考虑容斥，**在每一个方案第一次出现不合法方案的时候给它减去**。

因此定义 $f_{i,j}$ 为 $[1,i]$ 时 $a_i=j$ 的合法方案数，$g_{i,j}$ 表示 $[1,i]$ 时 $a_i=j$ 并**钦定** $i$ 为第一个不合法的位置。

转移 $g_i$ 的时候，因为 $i-1$ 一定合法，所以直接从 $f_{i-2}$ 转移是没有问题的。

这样写你要枚举 $i-2$ 的值 $x$，但是注意到 $0\le x\le m-j$ 所以你直接前缀和就行了。

---

## 作者：云浅知处 (赞：0)

- [PYD1](https://www.luogu.com.cn/user/266732) 给我说的这个题，我在原神启动之前就会做了，很快啊！
- 话说官方题解为啥要容斥呢。下面是不用容斥的做法。

考虑合法的充要条件。求差分序列 $b_i=a_i-a_{i-1},1\le i\le n+1$，其中 $a_{n+1}=a_0=0$。

则每次可以选 $i+1<j$，让 $b_i\leftarrow b_i-1,b_j\leftarrow b_j+1$。

考虑 Hall 定理，发现限制最严的时候一定是取左部点是一个前缀。于是这等价于对任意 $i\ge 2$，有 $\sum_{j=1}^{i-2}[b_i>0]b_i\ge \sum_{j=1}^i[b_i<0](-b_i)$。

即 $\sum_{j=1}^ib_i-[b_i>0]b_{i}-[b_i>0]b_{i-1}\ge 0$。讨论一下：

- $b_i>0,b_{i-1}>0$：左边变成 $a_{i-2}$，一定 $\ge 0$。
- $b_i>0,b_{i-1}<0$：左边变成 $a_{i-1}$，一定 $\ge 0$。
- $b_i<0,b_{i-1}>0$：左边是 $a_i-b_{i-1}$。
- $b_i<0,b_{i-1}<0$：左边是 $a_i$，一定 $\ge 0$。

于是只需要

- 对任意的 $i\ge 2$，有 $a_i-b_{i-1}\ge 0$。这里 $i$ 可以取到 $n+1$。

为了方便我们改写为：

- 对任意 $1\le i\le n,a_{i-1}-a_i+a_{i+1}\ge 0$。其中 $a_0=a_{n+1}=0$。

此时有简单 $O(nk^2)$ DP：记录最后两个元素的值即可。考虑优化。

~~感觉直接对这个自动机跑最小化就好了。~~

我们还是来脑动跑一下 DFA minimize 吧！

设 $f(i,j,k)$ 表示 $i$ 个元素，$a_i=j,a_{i-1}=k$。我们发现：

- $j\le k$ 的状态，DP 值全都一样。这是因为 $j$ 这个位置一定符合要求了，所以 $k$ 就不会影响合法性。
- $j\ge k$ 的状态，转移全都一样。这是因为 $k$ 这个位置一定符合要求了，所以 $j$ 不会影响合法性。

于是就做完啦。对于 $j\le k,j>k$ 我们分别记录单独 $j$ 和 $k$，转移时再乘上系数即可。

具体的系数和转移在代码的注释中写的很清楚。

<https://codeforces.com/contest/1943/submission/252190617>

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

对于一个自然数序列 $a$，我们称其是好的，当且仅当可以通过如下操作使其全部变为 $0$：

- 选择一个长度大于 $1$ 的区间，使得区间内所有数 $-1$。

求长度为 $n$，值域为 $[0,k]$ 的好的序列的数量，$1\le k\le n\le 3\times 10^3$。

## 题目分析

首先，这种区间减的操作很难不让我们想到差分。求出 $a$ 的差分数组 $b$，则操作转换为在 $b$ 序列上选择两个不相邻的数，前一个 $-1$，后一个 $+1$，同样是要全部消为 $0$。

这类似于括号匹配，成立的条件其实和括号匹配的实质是一样的，也很好想出来：

- $\forall i\in[2,n+2],\sum\limits_{j\le i-2}b_j\ge -b_i$。其中 $b_0=b_{n+2}=0$（差分数组自然满足总前缀和为 $0$）。

根据差分的性质和定义，可以将式子化简为 $\forall i\in [1,n],a_{i}\le a_{i-1}+a_{i+1}$。

注意到由于 $a_i$ 都是自然数，所以**不会有相邻的 $i$ 同时非法**，这是 Hard version 的关键。

考虑 dp。设 $dp_{i,j}$ 表示考虑前 $i$ 个数，$a_i=j$ 的答案，$g_{i,j}$ 表示恰好在 $i$ 处非法，$a_i=j$ 的方案数。则有 $dp_{i,j}=\sum dp_{i-1} +g_{i,j}$，$g_{i,j}=\sum\limits_{l<k-j} (k-j-l)dp_{i-2,l}$。前缀和优化即可 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =3e3+5,M=1e6+5,inf=(1LL<<30)-1;
int mod;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int dp[N][N],n,k,sdp[N][N],Sdp[N][N];
inline void sol(int i){
	sdp[i][0]=dp[i][0],Sdp[i][0]=mul(dp[i][0],k);
	rep(j,1,k)sdp[i][j]=Add(sdp[i][j-1],dp[i][j]),Sdp[i][j]=Add(Sdp[i][j-1],mul(dp[i][j],k-j));
}
inline int getg(int i,int j){
	int ans=0,r=k-j-1;
	if(r<0)return 0;
	if(i<2)return 0;
	return Red(Sdp[i-2][r],mul(sdp[i-2][r],j));
}
inline void Main(){
	n=read(),k=read(),mod=read();
	n+=2;
	repn(i)rep(j,0,k)dp[i][j]=sdp[i][j]=Sdp[i][j]=0;
	dp[1][0]=1,sol(1);
	rep(i,2,n){
		rep(j,0,k)dp[i][j]=Red(sdp[i-1][k],getg(i,j));
		sol(i);
	}
	cout <<dp[n][0]<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main(); 
	return 0;
}
```

---

## 作者：zhicheng (赞：0)

### 思路

先转化题目条件。考虑对于一个 $a_i$，操作它时一定会同时操作 $a_{i-1}$ 或 $a_{i+1}$（设 $a_0=a_{n+1}=0$）。故猜测原条件等价于 $\forall i\in[1,n],a_i\leq a_{i-1}+a_{i+1}$。必要性显然。充分性考虑构造证明。考虑每次操作这个数列的最长前缀不降子段，如果有 $0$ 就把它删除。容易发现可以删完。

考虑转化后怎么算。直接 DP 需要记录这个数列最后两项，状态数直接爆炸。考虑容斥原理，把 $a_i>a_{i-1}+a_{i+1}$ 的所有 $i$ 设为特殊位置。设 $f(x)$ 表示至少有 $x$ 个特殊位置的方案数。则答案为 $\sum\limits_{i=0}^{n}(-1)^if(i)$。

考虑 DP。设 $dp_{i,j,x}$ 表示考虑到 $i$ 这个位置，最后一个数为 $j$，现在有 $x$ 个特殊位置的方案数。注意到所有 $i$ 奇偶相同的 $f(i)$ 可以放到一起算。因此第三维可以改成 $0/1$。对于 $dp_{i,j,x}$，转移有两种：

- 不一定产生新的特殊位置：$\sum\limits_{r=0}^k dp_{i-1,r,x}$（每个都可以选）。
- 钦定产生新的特殊位置：$\sum\limits_{r=0}^{k-j}(k-j-r)dp_{i-2,r,x\ \text{xor}\ 1}$（$k-j-r$ 表示 $i-1$ 这个位置放 $j+r+1\sim k$ 这些数会产生新的特殊位置）。

考虑记录前缀和 $sum1_{i,j,x}=\sum\limits_{r=0}^j dp_{i,r,x},sum2_{i,j,x}=\sum\limits_{r=0}^j r\times dp_{i,r,x}$，直接转移即可。时间复杂度 $O(nk)$。

### Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3010;
int dp[N][N][2],sum1[N][N][2],sum2[N][N][2];
void solve(){
	int n,k,mod;
	scanf("%d%d%d",&n,&k,&mod);
	dp[0][0][0]=1;  //a[0]=0
	for(int i=0;i<=k;i++){
		sum1[0][i][0]=1;
	}
	for(int i=1;i<=n+1;i++){
		for(int j=0;j<=k;j++){
			dp[i][j][0]=(sum1[i-1][k][0]+1ll*(k-j)*(i-2<0?0:sum1[i-2][k-j][1])%mod-(i-2<0?0:sum2[i-2][k-j][1])+mod)%mod;
			dp[i][j][1]=(sum1[i-1][k][1]+1ll*(k-j)*(i-2<0?0:sum1[i-2][k-j][0])%mod-(i-2<0?0:sum2[i-2][k-j][0])+mod)%mod;
			sum1[i][j][0]=j?(sum1[i][j-1][0]+dp[i][j][0])%mod:dp[i][j][0];
			sum1[i][j][1]=j?(sum1[i][j-1][1]+dp[i][j][1])%mod:dp[i][j][1];
			sum2[i][j][0]=j?(sum2[i][j-1][0]+1ll*j*dp[i][j][0]%mod)%mod:1ll*j*dp[i][j][0]%mod;
			sum2[i][j][1]=j?(sum2[i][j-1][1]+1ll*j*dp[i][j][1]%mod)%mod:1ll*j*dp[i][j][1]%mod;
		}
	}
	printf("%d\n",(dp[n+1][0][0]-dp[n+1][0][1]+mod)%mod);//a[n+1]=0
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
}
```

---

