# [AGC055C] Weird LIS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc055/tasks/agc055_c

整数 $ N,\ M $ が与えられます。次の条件を満たす長さ $ N $ の列 $ A=[A_1,\ A_2,\ \ldots,\ A_N] $ の個数を求めてください。

- $ 2\ \le\ A_i\ \le\ M $ ($ 1\ \leq\ i\ \leq\ N $)
- $ 1 $ から $ N $ までの整数の順列 $ P=[P_1,P_2,\ldots,P_N] $ であって次の性質を持つものが存在する。
  - $ 1 $ から $ N $ までの各 $ i $ について、$ A_i $ は列 $ [P_1,\ P_2,\ \ldots,\ P_{i-1},\ P_{i+1},\ \ldots,\ P_{N-1},\ P_N] $ の最長増加部分列の長さに等しい。

この個数は非常に大きい可能性があるため、これを素数 $ Q $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 3\ \le\ N\ \le\ 5000 $
- $ 2\ \le\ M\ \le\ N-1 $
- $ 10^8\ \le\ Q\ \le\ 10^9 $
- $ Q $ は素数である。

### Sample Explanation 1

このような列は $ [2,\ 2,\ 2] $ のみです。ここで $ [1,\ 2,\ 3] $ という順列が存在して性質を満たします。

### Sample Explanation 2

このような列は次の $ 9 $ 個です: $ [2,\ 2,\ 2,\ 2] $, $ [2,\ 2,\ 2,\ 3] $, $ [2,\ 2,\ 3,\ 2] $, $ [2,\ 2,\ 3,\ 3] $, $ [2,\ 3,\ 2,\ 2] $, $ [2,\ 3,\ 3,\ 2] $, $ [3,\ 2,\ 2,\ 2] $, $ [3,\ 3,\ 2,\ 2] $, $ [3,\ 3,\ 3,\ 3] $。

### Sample Explanation 3

このような列は $ [2,\ 2,\ 2,\ 2,\ 2] $ のみです。

## 样例 #1

### 输入

```
3 2 686926217```

### 输出

```
1```

## 样例 #2

### 输入

```
4 3 354817471```

### 输出

```
9```

## 样例 #3

### 输入

```
5 2 829412599```

### 输出

```
1```

## 样例 #4

### 输入

```
5 3 975576997```

### 输出

```
23```

## 样例 #5

### 输入

```
69 42 925171057```

### 输出

```
801835311```

# 题解

## 作者：_⁢　 (赞：13)

设 $\{p_i\}$ 的 LIS 长度为 $K$。

容易发现，$a_i\in\{K-1,K\}$。

下文默认固定 $K$，将 $a_i$ 都减去 $K$。

## 划分

将排列中每个数划分为四种类型：

- 绿色点：LIS 上不可替代的点。
- 红色点：LIS 上可替代的点。
- 黑色点：用来替代红色点的点。
- 蓝色点：无用点。

如：

$$
{\color{red}3},\,{\color{black}2},\,{\color{blue}1},\,{\color{green}4},\,{\color{red}6},\,{\color{black}5}
$$

如果一个红色点有多个可以用于替代的黑色点，只需保留最靠前的即可，其他视为蓝色点。

同理，可以证明，对于每个红黑点对，选择**位置靠前**的作为红点，替换黑点时一定不会发生需要替换其他点的情况。

一种错误的染色方法：

$$
{\color{black}3},\,{\color{red}1},\,{\color{red}4},\,{\color{black}2}
$$

需要用 $\color{black}3$ 替换 $\color{red}1$ 时，必须用 $\color{red}4$ 替换 $\color{black}2$。

## 观察

考虑两个答案不同，当且仅当 $K$ 不同或每个位置 $0$、$-1$ 的取值不同。

以下是四种点对应的情况：

- 绿色点：$K$ 增加 $1$，此处为 $-1$。
- 红色点：$K$ 增加 $1$，此处为 $0$。
- 黑色点：$K$ 不增加，此处为 $0$。
- 蓝色点：$K$ 不增加，此处为 $0$。

可以发现，黑色点和蓝色点对答案的影响**完全一致**。

之所以黑色点会存在，是因为红色点需要一个「匹配」。

换言之，黑色点只会紧贴着红色点出现。

## 计数

对于确定的 $K$ 以及**满足题意的**序列 $\{a_i\}$，考虑将其对应到唯一一种染色方案上。

- 对于 $-1$，只能放绿。
- 否则，由于 $K$ 已经确定，红黑对的数量也已经确定。
- **贪心地**让红黑对尽量排在前面。
- 需要注意的是，可能出现 ${\color{red}3},\,{\color{black}2},\,{\color{blue}1},\,{\color{green}4},\,{\color{red}6},\,{\color{black}5}$ 的情况。
- 如果仅剩一个空位（再下一个是绿点），就只能放蓝了。

建出自动机：

$0$：最后放了一个绿，下一个除了黑都能放。

$1$：最后放了一个红，下一个必须放黑。

$2$：最后放了一个蓝，下一个只能放绿或蓝，如果再放一个蓝的就不能放红黑对了。

$3$：红黑对放完了，下一个只能放绿或蓝。

考虑转移：

$$
\begin{aligned}
f'_{0,K+1} &\gets f_{0,K} & {\color{green}\text{绿}} \\
f'_{1,K+1} &\gets f_{0,K} & {\color{red}\text{红}} \\
f'_{2,K} &\gets f_{0,K} & {\color{blue}\text{蓝}} \\
f'_{0,K} &\gets f_{1,K} & {\color{black}\text{黑}} \\
f'_{0,K+1} &\gets f_{2,K} & {\color{green}\text{绿}} \\
f'_{3,K} &\gets f_{2,K} & {\color{blue}\text{蓝}} \\
f'_{3,K+1} &\gets f_{3,K} & {\color{green}\text{绿}} \\
f'_{3,K} &\gets f_{3,K} & {\color{blue}\text{蓝}}
\end{aligned}
$$

时间复杂度 $\mathcal{O}(nm)$。

[提交记录](https://atcoder.jp/contests/agc055/submissions/38935975)。


---

## 作者：Edward1002001 (赞：5)

此题解是对 Legitimity 大佬的题解做的补充，由于最后求得公式的一部分只是简单的用“插板法”一语带过，我只好对着公式想了好几个小时，才想出公式的意义，希望这篇注解能帮到大家

本文假设你已经看懂了 Legitimity 大佬的题解中“分析出必要条件是...”之前的部分。

考虑既有必经点又有其他点的情况，需要强调的是，我们是对最后的方案计数，所以**如果必经点的放置方案是相同的，$k$也是相同的，那么这就是同样的方案**

考虑一种必经点的放置方案，我们需要将剩下的点划分成无用点和非必经点，再求出他们可能的 $k$ 值域的并，由于必经点的放置方案确定，值域下界是不变的 $\max(x,3)$，因此要求值域的并只要求出 $k$ 在这种必经点的放置方案下的最大值就可以了，而这意味着必经点划分出的 $x+1$ 段区间中每段区间最多只有一个点是无用点/三个一组的非必经点，剩下都是两两成组的非必经点。

于是我们只需要对这样的方案计数，再乘上此时 $k$ 的值域。

考虑枚举必经点的个数 $x$ 以及成对非必经点的对数 $y$，那么分配这些点的方案数（一对点必须在一起被安排）就是 $\binom{x+y}{y}$，此时还剩下 $n-x-2y$ 个点，他们只可能是无用点/三个一组的非必经点，而且 $x+1$ 段区间的每一段最多只能插入一个，但是这一个插在区间的哪个位置是不影响的（因为成对非必经点和这种点都是 $k-1$），因此再乘上一个 $\binom{x+1}{n-x-2y}$ 即可计算出方案数。

---

## 作者：Legitimity (赞：5)

### solution

考虑寻求存在满足条件的排列 $P$ 的充要的条件。

首先显然的是假设整个序列的 LIS 长度为 $k$，那么 $A_i\in\{k-1,k\}$，因为去掉一个 LIS 里的数之后剩下的 $k-1$ 个数仍然构成 LIS，长度至少为 $k-1$，并且还可能去掉后无影响即长度为 $k$。

下面定义必经点、非必经点、无用点。

1. 若位置 $i$ 在所有 LIS 中，即去掉位置 $i$ 后 LIS 长度减少，那么称 $i$ 为必经点，有 $A_i=k-1$。
2. 若位置 $i$ 在某个 LIS 中，且去掉位置 $i$ 后 LIS 长度不变，那么称 $i$ 为非必经点，有 $A_i=k$。
3. 若位置 $i$ 不在任何一个 LIS 中，那么称 $i$ 为无用点，有 $A_i=k$。

首先我们考虑整个 $A$ 序列都是一种值的情况。

1. 全都是 $k-1$，即全是必经点，显然满足条件的只有 $k=n$ 时 $P=\{1,2,\ldots,n-1,n\}$。
2. 全都是 $k$，考虑非必经点一定是成对出现，当一对点中的一个点被删掉，另一个点能发挥等效的作用，即一对点对 LIS 产生长度为 $1$ 的贡献，那么可得 $n$ 个非必经点至多产生 $\lfloor\dfrac{n}{2}\rfloor$ 的贡献，必要条件就是 $k\leq \lfloor\dfrac{n}{2}\rfloor$，这个序列由 $2k$ 个非必经点和 $n-2k$ 个无用点构成。这个条件也是充分的，考虑形如 $P=\{n-k+1,n-k,\ldots n,n-2k+1,\ldots\}$

接下来就只考虑 $A$ 存在两种值的情况，分析 $k$ 的取值范围。假设有 $x$ 个必经点，那么会产生 $x$ 的贡献，可得 $k\geq x$；非必经点也可能对 $k$ 产生贡献，假设将必经点的位置作为切割点将整个序列分成若干段，我们发现只有同段的点才可能等效，那么可得每对非必经点都在一段内，设每段的长度为 $len_i$，那么至多有 $\sum_i \lfloor\frac{len_i}{2}\rfloor$ 对非必经点，可得 $k\leq x+\sum_i \lfloor\frac{len_i}{2}\rfloor$。

分析出了必要条件是 $x\leq k\leq x+\sum_i \lfloor\frac{len_i}{2}\rfloor$。似乎分析不出更多了，那么就大胆猜测这就是充要条件（的确是充要的，如果是打比赛就可以直接开始数数了）。我们尝试通过构造方案来证明这是充分的。

设 $x$ 个必经点分别为 $b_1,b_2,\ldots,b_x$，必经点和非必经点合并在一起构成 $c_1,c_2,\ldots,c_m$。

我们首先考虑填上无用点，考虑对于前 $l$ 个无用点我们依次填上 $\{n,n-1,\ldots,l+1,l\}$，对于后 $r$ 个无用点依次填上$\{r,r-1,\ldots,1\}$。这样做是不合法的当且仅当 $l$ 填到了 $c_{m-1}$ 的后面或 $r$ 填到了 $c_2$ 的前面，想要满足这样必须要满足 $x=2$ 并且不存在非必经点，这种情况下 $k=2,k-1=1$，但是题目要求 $A_i\geq 2$，所以非法的情况不存在，我们这样填一定是可以的。

之后考虑非必经点被必经点划分成了若干段（$(b_i,b_i+1)$ 对应的值域为 $(a_{b_i},a_{b_{i+1}})$），处理方法和上面“全都是 $k$ ”一样，假设给第 $i$ 段（设值域为 $[l_i,r_i]$）分配了 $k_i$ 个贡献，那么填上 $P_i=\{r_i-k_i+1,r_i-k_i,\ldots r_i,r_i-2k_i+1,\ldots\}$ 即可。

于是我们证明了充分性。

之后考虑如何数这个东西，枚举必经点数量 $x$ 和非必经点对数量 $y$，使用插板法然后乘上 $k$ 的方案即可：
$$
\sum_{x=1}^{\min\{m,n-1\}}\sum_{y=0}^{\lfloor\frac{n-x}{2}\rfloor}\binom{x+y}{y}\binom{x+1}{n-x-2y}(\min\{m,x+y\}-\max\{x,3\}+1)
$$

### code
```cpp
int n,m,ans;
int C[5005][5005];
signed main(){
	//file();
	n=read(),m=read(),djq=read(); C[0][0]=1;
	rep(i,n) C[i][0]=1;
	rep(i,n) rep(j,i) C[i][j]=add(C[i-1][j-1],C[i-1][j]);
	ans=min(m,n/2)-1+(m>=n-1);
	rep(i,min(n-1,m))
		for(rg int j=0;j*2+i<=n;++j)
			if(min(i+j,m)>=max(3,i)) 
				pls(ans,1ll*C[i+1][n-i-j*2]*C[i+j][j]%djq*(min(i+j,m)-max(3,i)+1)%djq);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：BYR_KKK (赞：0)

断断续续做了一晚上，还是有点菜。

  首先找一些性质，序列中只会有 $p$ 和 $p-1$ 两种数。我们将 $p-1$ 视作 $0$，$p$ 视作 $1$，对于一个 $01$ 序列看其能对应多少 $p$。这需要我们进一步考察性质，对于一个有 $x$ 个 $0$ 的 $01$ 序列，$p$ 的一个下界是 $x$，考虑上界，通过简单手玩，设 $a_1,a_2,\dots,a_s$，为所有极长连续 $1$ 段的长度，则上界是 $x+\sum\limits\lfloor\dfrac{a_i}{2}\rfloor$。

我们称 $(i,j)=1$ 当且仅当存在 LIS 长度为 $j$ 的 $i$ 阶排列，同时**不存在必选点**。我们手玩出的事情是 $(i,j)=1$ 当且仅当 $j\le\lfloor\dfrac{i}{2}\rfloor$。证明其它题解有写，就是从非必经点成对出现这一角度证明。可以发现该结论等价于上面所说的上界，同时也说明了上下界之间的每一个数都可以被取到。

这样我们就能对一个 $01$ 序列列出一个贡献式子 $x+\sum\lfloor\dfrac{a_i}{2}\rfloor-x+1$，如果没有 $m$ 的限制是好做的，有了之后我们考虑将其变形为：

$$\min(m,x+\sum\lfloor\dfrac{a_i}{2}\rfloor)-\min(m,\max(2,x-1))$$

**注意这个式子在 $n=3$ 时是错的，因为可能会有上界 $<1$ 的 $01$ 序列，特判掉即可。**

对这个式子拆贡献，令 $f_{i,j,0/1}$ 代表考虑完前 $i$ 个数，$x+\sum\lfloor\dfrac{a_i}{2}\rfloor=j$，同时当前位在当前极长 $1$ 段中是奇数/偶数个位置。令 $g_{i,j}$ 代表考虑完前 $i$ 个数，$0$ 的数量为 $j$ 的方案数（实际上就是组合数）。两个 dp 都是 $O(n^2)$ 的。

最后算一下贡献即可。不过在 $m=n-1$ 的时候是错的，原因是我们规定了 $p\le m$，但是当整个序列全是 $p-1$ 的时候 $p=m+1$ 也是合法的，判掉即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pii std::pair<int,int>
#define vint std::vector<int>
#define vpair std::vector<pii>
#define debug(...) fprintf(stderr,##__VA_ARGS__)

template<typename T>
void read(T &x){
	x=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=x*10+(int)(c-'0'),c=getchar();
	x*=f;
}

std::stack<char>st;
template<typename T>
void print(T x){
	if(x==0) putchar('0');
	if(x<0) putchar('-'),x=-x;
	while(st.size()) st.pop();
	while(x) st.push((char)('0'+x%10)),x/=10;
	while(st.size()) putchar(st.top()),st.pop();
}

template<typename T>
void printsp(T x){
	print(x),putchar(' ');
}

template<typename T>
void println(T x){
	print(x),putchar('\n');
}

template<typename T,typename I>
bool chkmin(T &a,I b){
	if(a>b) return a=b,1;
	return 0;
}

template<typename T,typename I>
bool chkmax(T &a,I b){
	if(a<b) return a=b,1;
	return 0;
}

template<typename T,typename I>
void addedge(std::vector<I>*vec,T u,T v){
	vec[u].push_back(v);
}

template<typename T,typename I,typename K>
void addedge(std::vector<K>*vec,T u,T v,I w){
	vec[u].push_back({v,w});
}

template<typename T,typename I>
void addd(std::vector<I>*vec,T u,T v){
	addedge(vec,u,v),addedge(vec,v,u);
}

template<typename T,typename I,typename K>
void addd(std::vector<K>*vec,T u,T v,I w){
	addedge(vec,u,v,w),addedge(vec,v,u,w);
}

bool Mbe;

const int inf=1e18,MOD1=998244353,MOD2=1e9+7;

const int maxn=5010;

int f[maxn][maxn][2],m,n,mod,g[maxn][maxn];

void add(int &a,int b){
	a+=b;
	if(a>=mod) a-=mod;
}

bool Men;

signed main(){
	debug("%.6lfMB\n",(&Mbe-&Men)/1048576.0);
	read(n),read(m),read(mod);
	if(n==3&&m==2){
		println(1);
		return 0;
	}
	f[0][0][0]=1;
	g[0][0]=1;
	// assert(m!=n-1);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++){
			if(j>=1) f[i][j][0]=f[i-1][j-1][0],add(f[i][j][0],f[i-1][j-1][1]*2%mod);
			f[i][j][1]=f[i-1][j][0];
			g[i][j]=g[i-1][j-1],add(g[i][j],g[i-1][j]);
		}
	int ans=0;
	for(int i=1;i<=n;i++) add(ans,std::min(m,i)*(f[n][i][0]+f[n][i][1])%mod);
	for(int i=1;i<=n;i++) add(ans,mod-(std::min(m,std::max(2ll,i-1))*g[n][i])%mod);
	add(ans,mod-1);	
	if(m==n-1) add(ans,1);
	println(ans);
	debug("%.6lfms\n",1e3*clock()/CLOCKS_PER_SEC);
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc055_c)

**题目大意**

> 对于一个排列 $p$，定义 $a_i$ 表示 $p_1,\dots,p_{i-1},p_{i+1},\dots,p_n$ 的 LIS，求共能生成有多少个值域 $[2,m]$ 的序列 $a_1\sim a_n$。
>
> 数据范围：$n\le 5000$。

**思路分析**

很显然 $a$ 的极差 $\le 1$，并且大部分情况下最大值就是 $p$ 的 LIS 长度，除非 $a_1=\cdots=a_n=n-1$，此时 $p_i=i$。

先考虑 $a$ 中元素全部相等的情况，此时每个 $a_i$ 都是 LIS 长度，即每个 $p_i$ 都可以找到 LIS 外的替换元素。

很显然此时 LIS 长度 $k\le \lfloor n/2\rfloor$，因为每个元素的替换元素不可能相同。

并且这样的序列总能构造，一组合法的构造形如： $n,n-1,\dots,2k+1,2,1,4,3,\dots,2k,2k-1$。

那么对于一般的情况，会有一些 $a_i=k-1$ 的元素，表示他们是 LIS 的必经点。

设这些必经点为 $x_1\sim x_q$，那么很显然 $k\ge q$，并且对于每个 $(x_i,x_{i+1})$ 中间的段，对 LIS 的贡献至多为 $\left\lfloor\dfrac{x_{i+1}-x_i-1}2\right\rfloor$（设 $x_0=0,x_{q+1}=n+1$）。

那么一个必要条件就是 $q\le k\le q+\sum \left\lfloor\dfrac{x_{i+1}-x_i-1}2\right\rfloor$，手玩发现这样的序列也总是能构造出来的。

不妨设 $s=\sum \left\lfloor\dfrac{x_{i+1}-x_i-1}2\right\rfloor$，那么 $k$ 的取值区间就是 $\max(q,3)\sim\min(m,q+s)$，并且确定 $q,s$ 后，直接分配 $s$ 个元素进入 $q+1$ 个空，还剩 $n-q-2s$ 个元素作为除以二的余数分进 $q+1$ 个空（每个空至多一个）。

那么我们只要枚举 $q,s$ 就能计算出对应方案数。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e4+5;
int n,m,MOD;
ll fac[MAXN],ifac[MAXN];
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
ll C(int x,int y) {
	if(x<0||y<0||y>x) return 0;
	return fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}
signed main() {
	scanf("%d%d%d",&n,&m,&MOD);
	for(int i=fac[0]=ifac[0]=1;i<MAXN;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	ll ans=1;
	if(n>3&&(m==n-1)) ++ans;
	for(int k=0;k<=n;++k) for(int s=0;2*s+k<=n;++s) {
		ans=(ans+C(s+k,k)*C(k+1,n-k-2*s)%MOD*max(min(m,k+s)-max(k,3)+1,0))%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

对 <https://www.luogu.com.cn/blog/o-i-e-r/solution-at-agc055-c> 的一个解释。


设 $p$ 的 LIS 长度为 $K$，那么应该有 $a_i\in [K,K-1]$。我们将 $a_i\leftarrow a_i-K$。

排列上的数可以划分成四种类型：

- 绿色：$a$ 填 $-1$，$K$ 增加 $1$；
- 红色：$a$ 填 $0$，$K$ 增加 $1$；
- 黑色：$a$ 填 $0$，$K$ 不变；
- 蓝色：$a$ 填 $0$，$K$ 不变。

让红黑匹配尽可能地先出现，也就是说只让黑点靠着红点出现，那么 $f_{i,k}$ 代表其结尾的性质为 $i$，当前 $K=k$，考虑人脑建出自动机：

- $i=0$，放了一个绿，下一个什么都能放。
- $i=1$，放了一个红，下一个只能是黑色。
- $i=2$，放了一个蓝，下一个只能放绿或蓝。放蓝的话，就不能再放红黑对了。
- $i=3$，放完红黑对了，那么下一个点只能放绿色或蓝色。再放一个蓝，则不能放置红黑对了。因为我们需要尽可能让红黑对出现在前面。

实际上，蓝蓝红黑和红黑蓝蓝是等价的状态（转移 $3$），蓝红黑和红黑蓝也是等价的状态，黑点只是为了给红点提供一个匹配，来保证其在删去后不会让 $a$ 的值发生改变。这是这样转移的原因。

如何统计答案？首先最后不能停留在 $1$，然后对于 $K=2,n-1$ 进行一个特判即可。 

```cpp
#include <bits/stdc++.h>
const int N = 5005;
using namespace std;

int f[4][N], g[4][N];
int n, m, P;

inline void add(int &x, int y) { x += y; if (x >= P) x -= P; }

int main(void) {
    ios::sync_with_stdio(0);
    cin >> n >> m >> P; f[0][0] = 1; 
    for (int i = 1; i <= n; ++i) {
        memcpy(g, f, sizeof(f)); memset(f, 0, sizeof(f));
        for (int j = 0; j <= m; ++j) {
            add(f[0][j + 1], g[0][j]);
            add(f[1][j + 1], g[0][j]);
            add(f[2][j], g[0][j]);

            add(f[0][j], g[1][j]);

            add(f[3][j], g[2][j]);
            add(f[0][j + 1], g[2][j]);

            add(f[3][j + 1], g[3][j]);
            add(f[3][j], g[3][j]);
        }
    }
    int res = 0;
    for (int i = 3; i <= m; ++i) {
        add(res, f[0][i]);
        add(res, f[2][i]); 
        add(res, f[3][i]);
    }
    ++res; // [2, 2, 2]
    if (m != 2 && m == n - 1) ++res; // [b - 1, n - 1, n - 1]
    cout << res % P << "\n";
    return 0;
}
```

---

