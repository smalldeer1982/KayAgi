# [集训队互测 2023] Permutation Counting 2

## 题目描述

给定 $n$，对于每组 $x,y\in [0,n)$ 求出有多少个 $1\sim n$ 的排列 $p$ 满足以下条件：

- $\sum\limits_{i=1}^{n-1}[p_i<p_{i+1}]=x$。

- $\sum\limits_{i=1}^{n-1}[p^{-1}_i<p^{-1}_{i+1}]=y$。

其中 $p^{-1}$ 表示 $p$ 的逆排列，满足 $p^{-1}_{p_i}=i$。

答案对给定的质数 $MOD$ 取模。

## 说明/提示

对于 $100\%$ 数据，$1\le n\le 500$，$10^9\le MOD\le 1.01\times 10^9$，保证 $MOD$ 为质数。

$\operatorname{Subtask} 1(10\%):n\le 8$。

$\operatorname{Subtask} 2(15\%):n\le 16$。

$\operatorname{Subtask} 3(25\%):n\le 40$。

$\operatorname{Subtask} 4(25\%):n\le 100$。

$\operatorname{Subtask} 5(25\%):$ 无特殊限制。

## 样例 #1

### 输入

```
3 1000000007```

### 输出

```
1 0 0
0 4 0
0 0 1```

## 样例 #2

### 输入

```
5 1000000007```

### 输出

```
1 0 0 0 0
0 20 6 0 0
0 6 54 6 0
0 0 6 20 0
0 0 0 0 1```

## 样例 #3

### 输入

```
10 1000000007```

### 输出

```
1 0 0 0 0 0 0 0 0 0
0 165 462 330 55 1 0 0 0 0
0 462 9273 22023 13750 2266 66 0 0 0
0 330 22023 147301 203610 75306 6556 66 0 0 
0 55 13750 203610 592130 423236 75306 2266 1 0
0 1 2266 75306 423236 592130 203610 13750 55 0
0 0 66 6556 75306 203610 147301 22023 330 0
0 0 0 66 2266 13750 22023 9273 462 0
0 0 0 0 1 55 330 462 165 0
0 0 0 0 0 0 0 0 0 1```

# 题解

## 作者：allenchoi (赞：8)

### 前言：  
这是蒟蒻做的第一道二项式反演，一开始反演的方向反了（致敬反方向的钟   
### 科技：  
[二项式反演](https://www.luogu.com.cn/article/0ukqnypr)
### 思路：  
直接计算 $ans_{i,j}$ 是不好做的，我们考虑求出钦定在原排列和逆排列种各有 $i,j$ 个上升的连续对的方案数 $f_{i,j}$，则 $f_{i,j}=\sum\limits_{a\ge i}\sum\limits_{b \ge j}\binom{a}{i}\binom{b}{j}ans_{a,b}$，反演得 $ans_{i,j}=\sum\limits_{a\ge i}(-1)^{a-i}\binom{a}{i}\sum\limits_{b\ge j}(-1)^{b-j}\binom{b}{j}f_{a,b}$。直接算是 $O(n^4)$ 的，但我们可以预处理一个 $s_{j,a}=\sum\limits_{b\ge j}(-1)^{b-j}\binom{b}{j}f_{a,b}$，这样就可以得到 $ans_{i,j}=\sum\limits_{a\ge i}(-1)^{a-i}\binom{a}{i}s_{j,a}$。两者都是 $O(n^3)$ 的复杂度。   
剩下的事就是求 $f_{i,j}$ 了。  
我们钦定了原排列、逆排列中各有 $i,j$ 个上升的连续对，那么就相当于钦定原排列、逆排列中各有 $n-i,n-j$ 个连续的上升段。接下来有一个显然的结论：一个原排列中的连续上升段，段内的值的位置一定也是上升的。也就是说，原排列中一段连续上升的元素，是按照其原顺序被划分至逆排列的若干个上升段的。既然顺序已定，我们可以设 $c_{x,y}$ 表示原排列中第 $x$ 个上升段中有 $c_{x,y}$ 个元素划分在逆排列的第 $y$ 个上升段中。那么，我们钦定原排列、逆排列中各有 $i,j$ 个连续的上升段，就相当于要有一个 $i\times j$ 的矩阵，满足其中每一行每一列的总和为正，且整个矩阵总和为 $n$。  
设 $g_{i,j}$ 表示钦定原排列、逆排列中各有 $i,j$ 个连续的上升段时的方案数，也就是合法的大小为 $i\times j$ 的矩阵 $c$ 的数。注意 $f_{i,j}=g_{n-i,n-j}$。   
设 $t_{i,j}$ 表示只满足第二条限制（总和为 $n$）的矩阵的数量，易得 $t_{i,j}=\binom{n+ij-1}{ij-1}$，且 $t_{i,j}=\sum\limits_{a\le i}\binom{i}{a}\sum\limits_{b\le j}\binom{j}{b}g_{i,j}$，反演得 $g_{i,j}=\sum\limits_{a\le i}\binom{i}{a}(-1)^{i-a}\sum\limits_{b\le j}\binom{j}{b}(-1)^{j-b}t_{i,j}$，用上文提到的方法可优化至 $O(n^3)$。   
### 代码：  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 510,M = 250510;
int n,v,mod,inv[M],fac[M],ifac[M],ans[N][N],g[N][N],t[N][N],s[N][N],c[N][N];
int C(int n,int m){return 1LL * fac[n] * ifac[m] % mod * ifac[n - m] % mod;}
int main()
{
	scanf("%d%d",&n,&mod);
	v = n * n + n;
	inv[1] = fac[0] = ifac[0] = 1;
	for(int i = 2;i <= v;i++) inv[i] = mod - 1LL * (mod / i) * inv[mod % i] % mod;
	for(int i = 1;i <= v;i++)
	{
		fac[i] = 1LL * fac[i - 1] * i % mod;
		ifac[i] = 1LL * ifac[i - 1] * inv[i] % mod;
	}
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			t[i][j] = C(n + i * j - 1,i * j - 1);
	for(int i = 0;i <= n;i++)
	{
		c[i][0] = 1;
		for(int j = 1;j <= i;j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	}
	int tmp;
	for(int j = 1;j <= n;j++)
		for(int a = 1;a <= n;a++)
			for(int b = 1;b <= j;b++)
			{
				tmp = 1LL * c[j][b] * t[a][b] % mod;
				if((j - b) & 1) s[j][a] = (s[j][a] - tmp + mod) % mod;
				else s[j][a] = (s[j][a] + tmp) % mod;
			}
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			for(int a = 1;a <= i;a++)
			{
				tmp = 1LL * c[i][a] * s[j][a] % mod;
				if((i - a) & 1) g[i][j] = (g[i][j] - tmp + mod) % mod;
				else g[i][j] = (g[i][j] + tmp) % mod;
			}
	memset(s,0,sizeof(s));
	for(int j = 0;j < n;j++)
		for(int a = 0;a < n;a++)
			for(int b = j;b < n;b++)
			{
				tmp = 1LL * c[b][j] * g[n - a][n - b] % mod;
				if((b - j) & 1) s[j][a] = (s[j][a] - tmp + mod) % mod;
				else s[j][a] = (s[j][a] + tmp) % mod;
			}
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			for(int a = i;a < n;a++)
			{
				tmp = 1LL * c[a][i] * s[j][a] % mod;
				if((a - i) & 1) ans[i][j] = (ans[i][j] - tmp + mod) % mod;
				else ans[i][j] = (ans[i][j] + tmp) % mod;
			}
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++) printf("%d ",ans[i][j]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Anoshag_Ruwan (赞：7)

祝贺你谷主题库编号达到 $10^4$。（逃）

前情回顾 [P5825 排列计数](https://www.luogu.com.cn/blog/111172/solution-p5825)，本题可以视作对其的升维打击版本。那题中普遍切入点的递推在这里没前途，还是考虑二项式反演/容斥。将一个排列看做 $x$ 个递增连续段的拼接，其逆排列为 $y$ 个递增段的拼接。观察排列插入过程，原排列的 $[p_l,p_r]$ 段单调递增，对应逆排列的 $[l,r]$ 这些元素出现位置也是单调递增的（废话）。这说明原排列的任意第 $a$ 个连续段和逆排列第 $b$ 个连续段的交集必然也是一个连续段，且该段的所有相邻元素同时在数轴上相邻。

令 $G_{a,b}$ 表示这一交集连续段长度，则每个满足 $\forall i,\sum\limits_j G_{i,j}>0,\sum\limits_j G_{j,i}>0$ 且 $\sum\limits_{i,j} G_{i,j}=n$ 的矩阵 $G$ 就能对应一个将 $[1,n]$ 划分为 $x$ 个原排列连续段、$y$ 个逆排列连续段的方案，相当于 P5825 中的划分为 $k$ 个非空集合。令 $g_{x,y}$ 表示合法的 $x$ 行 $y$ 列矩阵方案数，统计出 $g$ 即可。

考虑怎么计数，如果没有每行、每列非空的条件是显然的。正如第二类斯特林数的推导那样，还是反演/容斥。令 $q_{a,b}=\tbinom{ab+n-1}{ab-1}$ 表示忽略非空条件下的贡献，钦定 $x-a$ 行 $y-b$ 列为空，得 $q_{x,y}=\sum\limits_{a \leq x}\sum\limits_{b \leq y}\tbinom{x}{a}\tbinom{y}{b}g_{a,b}$，二维容斥得 $g_{x,y}=\sum\limits_{a \leq x}\sum\limits_{b \leq y}\tbinom{x}{a}\tbinom{y}{b}q_{a,b}(-1)^{x+y-a-b}$。看似要枚举 $x,y,a,b$ 四个量所以是 $O(n^4)$，但实际上可以先枚举一维 $y$,令 $h_a=\sum\limits_{b \leq y}\tbinom{y}{b}(-1)^{y-b}q_{a,b}$，则 $g_{x,y}=\sum\limits_{a \leq x}\tbinom{x}{a}(-1)^{x-a}h_a$ 就可以直接算了，总复杂度 $O(n^3)$。

计算出 $g$ 后，和 P5825 一样需要考虑原排列/逆排列相邻连续段的拼接处是否依然能产生升高（即实际是一段）的问题，又需要一个二维容斥，令答案为 $f_{x,y}$ ,这次是 $g_{n-x,n-y}=\sum\limits_{a \geq x}\sum\limits_{b\geq y}\tbinom{a}{x}\tbinom{b}{y}f_{a,b}$，相当于二项式反演的另一个常用形式，类似做就行，复杂度 $O(n^3)$。

注意本题对常数有一定考察，除了处理 $q$ 数组的组合数上指标可以达到 $n^2$ 级别，其余组合数应使用递推预处理，避免被卡。此外，如果给 $G$ 矩阵加上每个元素只能取 $0$ 或 $1$ 的限制，也就是令 $q_{x,y}=\tbinom{xy}{n}$，得到的答案矩阵是原答案矩阵的翻转，这个应该也是有组合意义的。

---

## 作者：wYYSZLwSSY (赞：4)

谁能想到这是我做的第一个二项式反演的题呢。
## 题解
我们称 $p_i<p_{i+1}$ 为原排列的一个“上升”，类似的定义逆排列的“上升”。

那么原题目就是要求原排列**恰好**有 $x$ 个上升，同时逆排列**恰好**有 $y$ 个上升的方案数。

看到“恰好”，不难想到二项式反演，那么我们就是要对于每一个 $a,b$，求出钦定 $a$ 个原排列上升，$b$ 个逆排列上升，其他地方任意的方案数，不妨称为 $dp_{a,b}$。

直接求似乎比较抽象，考虑能不能把一个排列跟一个什么东西建立一一对应的映射。这种映射还是挺神奇的。

考虑将一段连续的“上升”称为一个“上升段”（例如排列 `1 2 4 5 3` 中 `1 2 4 5` 就可以看成一个上升段，`1 2` 也可以，甚至 `1` 也可以，但是什么都没有不能称为“上升段”），称一个不能在拓展的“上升段”为极长上升段（比如前面的 `1 2 4 5` 和 `3`），那么：

**结论 1**：如果一个排列有 $n-x$ 个极长上升段，逆排列有 $n-y$ 个极长上升段，就说明它有 $x$ 个原排列上升，有 $y$ 个逆排列上升。这很显然。同样，如果一个排列有 $n-x$ 个上升段（不重叠，不漏项，下同），逆排列有 $n-y$ 个上升段，就说明它至少有 $x$ 个原排列上升，至少有 $y$ 个逆排列上升。（为什么是至少呢？因为两个相邻的上升段之间也是一个上升而把两个上升段连起来。）

考虑使用这种方法进行钦定，定义 $g_{a,b}$ 为钦定分别有 $a,b$ 个原排列和逆排列上升的方案数，根据前面的讨论显然有：
$$g_{n-a,n-b}=dp_{a,b}$$

尝试再把 $g_{a,b}$ 转化。注意到：

**结论 2**：假设有一个排列，有若干个排列上升和逆排列上升，那么如果我们确定了任意两个排列上升和逆排列上升的交的大小，就可以确定这个排列。

什么意思呢，先来解释“排列上升和逆排列上升的交”，其实就是把逆排列的上升中的数对应到排列的下标，与排列某个上升段的下标的交。例如排列 `1 4 2 3`，它的逆排列是 `1 3 4 3`，对于上升 `1 4` 和上升 `1 3 4`，它们的交就是 $\{1\}$ 。

那么，为什么又说确定了所有交的大小就可以确定排列呢了？首先，知道所有的交之后就可以知道每一个上升段的长度。考虑从逆排列的第一个上升段开始，把它们的下标填到排列里，由于在排列中逆排列的下标出现位置是上升的，而且确定了可以填这些逆排列下标的位置，那么逆排列下标在排列中的位置就唯一确定了。其实就是确定了一个排列。这说明了：

**结论 3**：一个二维数组 $a$，如果有 
$$\forall i,\sum_j a_{i,j}>0,\sum_j a_{j,i}>0$$
（上升的长度不能为 $0$。）

同时 
$$\sum_{i,j} a_{i,j} =n,\forall i,j ,a_{i,j} \geq0$$
（没有漏项。）

就可以映射为一个排列。反过来的映射显然。

所以，令 $G_{a,b}$ 表示满足条件的两维大小为 $a,b$ 的数组个数，显然有 
$$g_{a,b}=G_{a,b}$$

考虑求 $G_{a,b}$，因为有行列和不为零的要求，不方便，考虑容斥，设 $Al_{a,b}$ 为仅满足第二个条件的合法数组数，显然 $Al_{a,b}=C_{n+ab-1}^{ab-1}$，那么有：
$$G_{a,b}=\sum_{x\le a } \sum_{y\le b } (-1)^{x-a+y-b}C_{a}^xC_b^y Al_{x,y}$$

这个转移是 $O(n^4)$ 的，考虑优化，发现：

$$G_{a,b}=\sum_{x\le a }  (-1)^{x-a}C_{a}^x\sum_{y\le b } (-1)^{y-b}C_b^y Al_{x,y}$$

式子的后半段止于 $b,x,y$ 有关，设：
$$l_x=\sum_{y\le b } (-1)^{y-b}C_b^y Al_{x,y}$$
随着 $b$ 的变化求 $l$，有：
$$G_{a,b}=\sum_{x\le a }  (-1)^{x-a}C_{a}^xl_x$$

之后，根据前文有：
$$dp_{a,b}=g_{n-a,n-b}=\sum_{x\ge a}\sum_{x\ge b}C_{x}^aC_y^b ans_{x,y}$$
这是二维的二项式反演的基本形式，反演类似一维的，有：
$$ans_{n-a,n-b}=\sum_{x\ge a}\sum_{x\ge b}(-1)^{x-a+y-b}C_{x}^aC_y^b g_{x,y}$$
依然是 $O(n^4)$ 的，可以用类似前面的方法优化，最终时间复杂度 $O(n^2)$。

另外这个题卡常，~~尤其是洛谷的取模很慢~~，除了求 $Al_{x,y}$ 时用到的组合数是 $O(n)$ 的，可以且要预处理；自然 $Al_{x,y}$ 要预处理。

## 代码
代码~~如果不在需要什么奇奇怪怪的卡常的话~~是简单的。
```cpp
#include<bits/stdc++.h>
// #define int long long 
#define ll long long
using namespace std;
int n;
ll MOd;
ll G[505][505];
ll f[505][505];
ll C[505][505],l[505];
ll fc[256035],inv[256035];
ll al[505][505];
ll ksm(ll x,int y){
	ll sum=1;
	while(y){
		if(y&1)sum=sum*x%MOd;
		x=x*x%MOd;
		y>>=1;
	}
	return sum;
}
int AL(int x,int y){
	int nn=x*y+n-1,mm=x*y-1;
	return fc[nn]*inv[n]%MOd*inv[mm]%MOd;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
// 	freopen("1.in","r",stdin);
	cin>>n>>MOd;
	fc[0]=1;
	for(int i=1;i<=n*n+2*n;++i)fc[i]=fc[i-1]*i%MOd;
	inv[n*n+2*n]=ksm(fc[n*n+2*n],MOd-2);
	for(int i=n*n+2*n-1;i>=0;--i)inv[i]=inv[i+1]*(i+1)%MOd;
	for(int i=0;i<=n;++i)C[i][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOd;

	for(int x=1;x<=n;++x)
		for(int y=1;y<=n;++y)
			al[x][y]=AL(x,y);
	for(int b=1;b<=n;++b){
		for(int x=1;x<=n;++x){
			l[x]=0;
			for(int y=1;y<=b;++y)
				l[x]=(l[x]+((b-y&1)?-1:+1)*C[b][y]*al[x][y])%MOd;
		}
		for(int a=1;a<=n;++a){
			G[a][b]=0;
			for(int x=1;x<=n;++x)
				G[a][b]=(G[a][b]+C[a][x]*((a-x&1)?-1:1)*l[x])%MOd;
		}
	}
	cerr<<clock()<<' ';
	for(int y=0;y<=n;++y){
		for(int a=0;a<n;++a){
			l[a]=0;
			for(int b=y;b<=n;++b)
				l[a]=(l[a]+((b-y&1)?-1:1)*C[b][y]*G[n-a][n-b])%MOd;
		}
		for(int x=0;x<=n;++x){
			f[x][y]=0;
			for(int a=x;a<n;++a)
				f[x][y]=(f[x][y]+((a-x&1)?-1:1)*C[a][x]*l[a])%MOd;
		}
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)
			cout<<(f[i][j]+MOd)%MOd<<' ';
		cout<<'\n';
	}
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<' ';
	return 0;
}
```

---

## 作者：JWRuixi (赞：4)

## [集训队互测 2023] Permutation Counting 2

### 题意

给定 $n, P$，对于每个 $x, y < n$，求 $(\sum\limits_{p}[\sum\limits_{i = 1}^{n - 1} [p_i < p_{i + 1}] = x][\sum\limits_{i = 1}^{n - 1} [p^{-1}_i < p^{-1}_{i + 1}] = y]) \bmod P$。

$n \le 400$。

### 分析

两个信息放在一起比较恶心，研究了很久，反正不会 DP，所以只能转向容斥。

首先恰好转钦定，$i$ 个上升可以等价于 $n - i$ 个上升段，相当于我们钦定 $p$ 有 $x$ 个上升段，$p^{-1}$ 有 $y$ 个上升段。

显然，这相当于将 $p^{-1}$ 的 $y$ 个段按某种顺序归并起来，要求 $p$ 有 $x$ 个上升段。那么，由于是钦定，所以相当于我们只需要知道 $p^{-1}$ 中的一段分在 $p$ 中的一段的数量，也就是计数 $x \times y$ 的矩阵，满足和为 $n$ 且不存在一列或一行为空的方案数。

考虑二次容斥，钦定若干行和若干列为空，接下来的方案数是插板法，可以 $\mathcal O(n)$ 计算一个点，$\mathcal O(n^3)$ 计算整个矩阵。

留给我们的问题就是如何计算容斥之后的结果：其实我们发现，这里的容斥相当于二项式反演。而二项式反演的本质是乘一个转移矩阵，那么根据矩阵乘法的结合律，计算顺序是无所谓的。也就是说，可以视为：容斥行、容斥列、反演列、反演行，按这样的顺序计算。

总复杂度 $\mathcal O(n^3)$。

### 提交记录

<https://qoj.ac/submission/515406>。

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P10004)

**题目大意**

> 给定 $n$，对于所有 $x,y\in[0,n)$ 计数有多少 $n$ 阶排列 $p$ 满足 $\sum[p_i<p_{i+1}]=x,\sum[p^{-1}_i<p^{-1}_{i+1}]=y$。
>
> 数据范围：$n\le 500$。

**思路分析**

先考虑只有 $x$ 的限制如何做，这就是欧拉数，可以二项式反演钦定 $i$ 个位置填 $<$ 号，那么原序列会被分成 $n-i$ 个连续段，每个段内元素严格递增。

回到这题，考虑二元二项式反演，钦定 $p$ 上形成 $i$ 个递增连续段，$p^{-1}$ 上形成 $j$ 个递增连续段，然后对两维分别二项式反演回去即可。

然后只需要考虑 $p$ 上形成 $i$ 个递增连续段，$p^{-1}$ 上形成 $j$ 个递增连续段的方案数。

观察 $p^{-1}$ 上一个递增连续段的形态，如果该连续段下标区间为 $[l,r]$，那么 $p$ 上值在 $[l,r]$ 内的元素下标递增。

那么对于 $p^{-1}$ 上的一个递增连续段，我们把其对应的 $[l,r]$ 依次插入 $p$ 中的 $i$ 个递增连续段内，只关心每个连续段内插了多少元素，容易发现每一种分配方式恰好对应一组 $p$。

那么我们就是要计数有多少 $i\times j$ 矩阵 $A$ 每行每列和非零，且总元素和为 $n$。

这里再二维容斥一遍，即钦定 $a$ 行 $b$ 列元素为 $0$，剩余的行列无限制，相当于直接插板，然后对每一维容斥回去即可。

时间复杂度 $\mathcal O(n^3)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace FastMod {
typedef unsigned long long ull;
typedef __uint128_t uLL;
ull b,m;
inline void init(ull B) { b=B,m=ull((uLL(1)<<64)/B); }
inline ull mod(ull a) {
	ull q=((uLL(m)*a)>>64),r=a-q*b;
	return r>=b?r-b:r;
}
};
#define o(x) FastMod::mod(x)
const int MAXN=505,MAXV=2.6e5+5;
int n,MOD;
ll C[MAXN][MAXN],fac[MAXV],ifac[MAXV];
ll g[MAXN][MAXN],f[MAXN][MAXN],h[MAXN];
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
signed main() {
	scanf("%d%d",&n,&MOD),FastMod::init(MOD);
	for(int i=fac[0]=1;i<MAXV;++i) fac[i]=fac[i-1]*i%MOD;
	ifac[MAXV-1]=ksm(fac[MAXV-1]);
	for(int i=MAXV-1;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	for(int i=0;i<=n;++i) for(int j=C[i][0]=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) g[i][j]=fac[i*j+n-1]%MOD*ifac[i*j-1]%MOD*ifac[n]%MOD;
	for(int i=1;i<=n;++i) {
		memset(h,0,sizeof(h));
		for(int j=1;j<=n;++j) {
			for(int k=1;k<=i;++k) {
				h[j]=o(h[j]+((i-k)&1?MOD-C[i][k]:C[i][k])*g[k][j]);
			}
		}
		for(int j=1;j<=n;++j) {
			for(int k=0;k<=j;++k) {
				f[i][j]=o(f[i][j]+((j-k)&1?MOD-C[j][k]:C[j][k])*h[k]);
			}
		}
	}
	memset(g,0,sizeof(g));
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) g[n-i][n-j]=f[i][j];
	memset(f,0,sizeof(f));
	for(int i=0;i<n;++i) {
		memset(h,0,sizeof(h));
		for(int j=0;j<n;++j) {
			for(int k=i;k<n;++k) {
				h[j]=o(h[j]+((k-i)&1?MOD-C[k][i]:C[k][i])*g[k][j]);
			}
		}
		for(int j=0;j<n;++j) {
			for(int k=j;k<n;++k) {
				f[i][j]=o(f[i][j]+((k-j)&1?MOD-C[k][j]:C[k][j])*h[k]);
			}
		}
	}
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) printf("%lld ",f[i][j]);
		puts("");
	}
	return 0;
}
```

---

