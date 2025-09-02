# [ARC171D] Rolling Hash

## 题目描述

给定整数 $P,B$ 满足 $P$ 是质数，$1\le B\le P-1$。

对于序列 $X=(x_1,x_2,\cdots,x_n)$，定义 $\operatorname{hash}(X)$ 的值为
$$\operatorname{hash}(X)=\left(\sum_{i=1}^nx_iB^{n-i}\right)\bmod P$$

给定 $M$ 对整数 $(L_i,R_i)(1\le i\le M)$，请问是否存在长度为 $N$ 的序列 $A=(A_1,A_2,\cdots,A_N)$ 满足：

- 对每一个 $i(1\le i\le M)$，都有
  $$\operatorname{hash}((A_{L_i},A_{L_i+1},\cdots,A_{R_i}))\not=0$$

## 说明/提示

-   $2 \leq P \leq 10^9$
-   $P$ 是质数。
-   $1 \leq B \leq P - 1$
-   $1 \leq N \leq 16$
-   $1 \leq M \leq \frac{N(N+1)}{2}$
-   $1 \leq L_i \leq R_i \leq N$
-   $(L_i, R_i) \neq (L_j, R_j)$ if $i \neq j$.
-   所有的输入都是整数。

## 样例 #1

### 输入

```
3 2 3 3
1 1
1 2
2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 1 3 3
1 1
2 3
1 3```

### 输出

```
No```

## 样例 #3

### 输入

```
998244353 986061415 6 11
1 5
2 2
2 5
2 6
3 4
3 5
3 6
4 4
4 5
4 6
5 6```

### 输出

```
Yes```

# 题解

## 作者：rui_er (赞：11)

UPD：对 $s_i$ 的定义进行了一些修改，使得结论的得出更加自然。感谢 @[233L](https://www.luogu.com.cn/user/405894) 对本题解提出的修改建议！

来补题了。昨天赛时想法是对的，代码写错了，没调过太可惜了。

显然 $P > n$ 时必定有解。

设后缀 $[i,n]$ 的哈希值为 $s_i$，则区间 $[l,r]$ 的哈希值为 $B^{r-n}(s_l-s_{r+1})\bmod P$，即 $[l,r]$ 的哈希值不为 $0$ 的充要条件是 $s_l\ne s_{r+1}$。建立一个点的编号为 $1\sim n+1$ 的图，对于每个输入的区间 $[l,r]$，连接一条边 $(l,r+1)$，问题转化为是否可以用 $P$ 种颜色将所有点染色，使得每条边两侧颜色不同。

设 $f_S$ 表示将点集 $S$ 的导出子图按以上规则染色，需要的最少颜色数。设 $g_S$ 表示点集 $S$ 是否为独立集。有转移：

$$
f_S=
\begin{cases}
0,&S=\varnothing\\
\min\limits_{T\subseteq S\land g(T)}\{f_{S\setminus T}+1\},&S\ne\varnothing
\end{cases}
$$

答案即为 $[f_U\le P]$，其中 $U$ 表示节点的全集。

时间复杂度 $O(3^n)$。

```cpp
// Problem: D - Rolling Hash
// Contest: AtCoder - AtCoder Regular Contest 171
// URL: https://atcoder.jp/contests/arc171/tasks/arc171_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

const int N = 17;

int P, B, n, m, G[N][N], f[1 << N], g[1 << N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> P >> B >> n >> m;
    rep(i, 1, m) {
    	int l, r;
    	cin >> l >> r;
    	G[l - 1][r] = G[r][l - 1] = 1;
    }
    if(P > n) {cout << "Yes" << endl; return 0;}
    const int U = (1 << (n + 1)) - 1;
    rep(S, 0, U) {
    	g[S] = 1;
    	rep(u, 0, n) {
    		if((S >> u) & 1) {
    			rep(v, u + 1, n) {
    				if((S >> v) & 1) {
    					if(G[u][v]) {
    						g[S] = 0;
    					}
    				}
    			}
    		}
    	}
    }
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    rep(S, 1, U) {
    	for(int T = S; T; T = (T - 1) & S) {
    		if(g[T]) {
    			chkmin(f[S], f[S ^ T] + 1);
    		}
    	}
    }
    cout << (f[U] <= P ? "Yes" : "No") << endl;
    return 0;
}
```

---

## 作者：KingPowers (赞：6)

为了方便，不妨将 $A_i$ 全部模 $p$ 考虑，也就是假设 $0\le A_i<p$。

设 $suf_i$ 表示后缀 $[i,n]$ 的哈希值，注意这个可能和你理解的后缀哈希值不太一样：
$$
suf_i=\sum_{j=i}^nA_jB^{n-j}
$$
则 $suf_i$ 是可以在 $[0,p-1]$ 任意取值的，且 $suf_i$ 的每种取值都可以唯一对应一个 $A$ 序列。

于是哈希函数可以重写如下：
$$
\begin{aligned}
{\rm hash}(l,r)&=\sum_{i=l}^r(A_iB^{r-i}) \\
&=B^{r-n}\sum_{i=l}^r A_iB^{n-i} \\
&=B^{r-n}(suf_l-suf_{r+1})
\end{aligned}
$$
由于 $B<p$，$B^k$ 恒不为模数 $p$ 的倍数，故 ${\rm hash}(l,r)\not =0$ 等价于 $suf_l\not = suf_{r+1}$。

不难发现，当 $p>n$ 时一定存在解，先判掉。

不妨对现在的问题进行一个具体的建模，建立 $n+1$ 个点，限制区间 $[l,r]$ 就连边 $l\to r+1$，现在的问题就转化成了：对图上的点进行染色，使得不存在一条边连接的两个点颜色相同，求最大颜色数是否不小于 $p$。

这是个经典的无多项式解法问题，考虑状压，设 $f(S)$ 表示染完集合 $S$ 内的点的最大颜色数，转移考虑枚举 $T\subseteq S$，如果 $T$ 是一个独立集那么 $T$ 就可以染成相同颜色，就有转移 $f(S)\leftarrow f(S-T)+1$。

判断独立集可以暴力预处理，总复杂度 $O(3^n)$。

---

## 作者：小木虫 (赞：3)

### Preface  
比较好玩的思维题。  
### Problem  

给定整数 $P,B$ 满足 $P$ 是质数，$1\le B\le P-1$。

对于序列 $X=(x_1,x_2,\cdots,x_n)$，定义 $\operatorname{hash}(X)$ 的值为
$$\operatorname{hash}(X)=\left(\sum_{i=1}^nx_iB^{n-i}\right)\bmod P$$

给定 $M$ 对整数 $(L_i,R_i)(1\le i\le M)$，请问是否存在长度为 $N$ 的序列 $A=(A_1,A_2,\cdots,A_N)$ 满足：

对每一个 $i(1\le i\le M)$，都有
  $$\operatorname{hash}((A_{L_i},A_{L_i+1},\cdots,A_{R_i}))\not=0$$

$2 \leq P \leq 10^9$。  
$P$ 是质数。  
$1 \leq B \leq P - 1$。  
$1 \leq N \leq 16$。  
$1 \leq M \leq \frac{N(N+1)}{2}$。  
$1 \leq L_i \leq R_i \leq N$。  
$(L_i, R_i) \neq (L_j, R_j)$ if $i \neq j$。  
所有的输入都是整数。  
### Solution  
感觉出一个很牛的事情：在大多数时候我们不断随机化序列是能找到解的。  
为什么呢？  
考虑每一条限制到底有多强，不难发现一条限制最多可以排除掉所有序列中 $\frac{1}{P}$ 的序列，因为如果一条限制的区间长度是 $len$，那么我们只需要确定 $len-1$ 个数，剩下的那个数就也已知了，这样的话我们就有 $P^{len-1}$ 个区间是不合法的。  

然后我们容易发现的是，在 $P>N$ 的时候，无论如何都有合法解，我们也可以通过随机化真的构造出一组解。  

然后考虑对 $P$ 很小的情况怎么做。  
前缀和和序列形成双射，序列转前缀和，然后题目限制变为了两个位置值不能相同。  

于是我们知道在同一个值下的合法填充方案们（剔除了互相冲突的位置同时出现的情况），这可以用一堆状态压缩的二进制位表示，我们从 $0$ 到 $P-1$ 枚举每一个可能的值，然后做或卷积，直接暴力是 $O(3^n)$ 的，使用 FWT 可以优化到 $O(n^2 2^n)$，如果你想再精细一点也可以快速幂做到 $O(\log n \times n 2^n)$。  

code：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
mt19937 rnd(time(0));
const int N=20;
int l[N*N],r[N*N],val[N];
int mod,base,n,m,a[N];
vector <int> c[N];
void Random(){
	for(int i=1;i<=n;i++)
		a[i]=rnd()%mod;
	memset(val,0,sizeof(val));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)
			val[j]=(val[j]*base+a[i])%mod;
		for(auto L:c[i]){
			if(val[L]==0)return;
		}
	}
	cout<<"Yes"<<endl;
	exit(0);
}
int f[1<<16],trans[1<<16];
void add(int &x,int y){x+=y;}
void OR(int *f,int op){
	//fwt(a)=merge(fwt(a0),fwt(a0)+fwt(a1))
	for(int k=0;k<n;k++){
		for(int i=0;i<(1<<n);i+=(1<<(k+1))){
			for(int j=0;j<(1<<k);j++)
				add(f[i+j+(1<<k)],op*f[i+j]);
		}
	}
}
int tag[N];
void DP(){
	for(int i=1;i<=m;i++){
		if(l[i]==1)tag[r[i]]=1;
	}
	for(int i=0;i<(1<<n);i++){
		int flg=1;
		for(int j=1;j<=n;j++){
			if((i>>(j-1))&1){
				flg&=(tag[j]^1);
			}
		}
		for(int j=1;j<=m;j++){
			if(l[j]==1)continue;
			if(((i>>(l[j]-2))&1)&&((i>>(r[j]-1))&1))flg=0;
		}
		if(flg){
			f[i]=1;
		}
	}
	for(int i=0;i<(1<<n);i++){
		int flg=1;
		for(int j=1;j<=m;j++){
			if(l[j]==1)continue;
			if(((i>>(l[j]-2))&1)&&((i>>(r[j]-1))&1))flg=0;
		}if(flg)trans[i]=1;
	}
	OR(trans,1);
	for(int k=1;k<mod;k++){
		OR(f,1);
		for(int i=0;i<(1<<n);i++)
			f[i]*=trans[i];
		OR(f,-1);
		for(int i=0;i<(1<<n);i++)
			f[i]=(f[i]>0);
	}
	if(f[(1<<n)-1])cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>mod>>base>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>l[i]>>r[i],c[r[i]].push_back(l[i]);
	if(mod>15){
		while(1.0*clock()/CLOCKS_PER_SEC<1.8){
			for(int i=1;i<=50;i++)Random();
		}
		cout<<"No"<<endl;
	}else{
		DP();
	}
	return 0;
}

```


---

## 作者：Coffee_zzz (赞：1)

这个题，真的是，牛大了！！！

我们令 $s_i$ 等于 $\operatorname{hash}(A_i,A_{i+1},\dots,A_n)$，那么 $\operatorname{hash}(A_l,A_{l+1},\dots,A_r)$ 可以表示为 $(s_l-s_{r+1}) \cdot \dfrac1{B^{n-r}} \bmod P$，其中 $s_{n+1}=0$。

因为 $\dfrac1{B^{n-r}} \bmod P$ 显然不为 $0$，所以 $\operatorname{hash}(A_l,A_{l+1},\dots,A_r)\ne0$ 的充要条件是 $(s_l-s_{r+1}) \bmod P \ne 0$，即 $s_l \bmod P \ne s_{r+1} \bmod P$。

由于 $s_i \bmod P$ 共有 $P$ 种可能的取值，我们可以看做，对 $1 \sim n+1$ 这 $(n+1)$ 个点进行染色，要求 $L_i$ 与 $R_i+1$ 的颜色不同。我们称「$L_i$ 与 $R_i+1$ 的颜色不同」为条件。

这个问题是经典的，我们可以进行状压 DP。

我们令 $f_S$ 表示将点集 $S$ 染色且满足条件所至少需要的颜色数。

我们可以先预处理出所有的独立集，转移时枚举点集 $S$ 的子集 $T$，如果 $T$ 是独立集且 $f_S>f_{S\backslash T}+1$，那么进行 $f_S \leftarrow f_{S\backslash T}+1$ 。

完成 DP 后就可以判断了。如果 $f_V \le P$，那么有合法方案，否则没有合法方案。其中 $V$ 表示所有点所组成的集合。

时间复杂度 $\mathcal{O}(3^n)$。

---

## 作者：XYQ_102 (赞：0)

## 思路

不妨把原式书写为：

$$\displaystyle\mathrm{hash}(X)=\left(\sum_{i=1}^n x_i B^{i}\right)\bmod P$$

由对称性可知这样是等价的。

这样一来，区间的哈希值就等于 $(h_r - h_{l - 1}) / {B^{r - l + 1}}$，这意味着题目中给定的若干条约束等价于 $h_r\ne h_{l - 1}$。

这种关系可以从图论的角度思考，建图之后我们需要解决这个子问题：

给定一张无向图，请判断是否存在一种染色方案使得所有相邻的点颜色不同，且颜色数 $\le P$。

这个是经典问题，可以用状压解决，具体而言，$f_s$ 表示已经对 $s$ 集合染色，最少颜色数，可以枚举子集，并且子集的点两两无边，转移。

时间复杂度：$\Theta(3^n)$。
## 代码
```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
// #define int long long
using namespace std;
const int N = 17;

int n, m, p;
int b[N], f[(1 << N)], disj[(1 << N)];

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> p >> n >> n >> m;
    for(int i = 1, l, r; i <= m; i ++) {
        cin >> l >> r;
        b[l - 1] |= (1 << r), b[r] |= (1 << (l - 1));
    }
    n ++;
    for(int s = 0; s < (1 << n); s ++) {
        disj[s] = 1;
        for(int i = 0; i < n; i ++)
            if(s >> i & 1) if(s & b[i]) {
                disj[s] = 0;
                break;
            }
    }
    memset(f, 0x3f, sizeof f), f[0] = 0;
    for(int s = 0; s < (1 << n); s ++)
        for(int t = s; t; t = (t - 1) & s)
            if(disj[t]) f[s] = min(f[s], f[t ^ s] + 1);
    cout << (f[(1 << n) - 1] <= p ? "Yes" : "No") << '\n';

    return 0;
}
```

---

