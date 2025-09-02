# [AGC035D] Add and Remove

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc035/tasks/agc035_d

非負整数のひとつ書かれたカードが $ N $ 枚積まれた山があります。上から $ i $ 番目のカードに書かれた整数は $ A_i $ です。

すぬけ君は、以下の操作をカードが $ 2 $ 枚になるまで繰り返します。

- 連続して積まれている $ 3 $ 枚のカードを選ぶ。
- $ 3 $ 枚のうち真ん中のカードを食べる。
- あとの $ 2 $ 枚のカードに書かれている整数を、その整数に食べたカードに書かれていた整数を足してできる整数に書き換える。
- 食べなかった $ 2 $ 枚のカードを、順序を保ったまま山のもとの位置に戻す。

最終的に残る $ 2 $ 枚のカードに書かれた整数の和の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 18 $
- $ 0\ \leq\ A_i\ \leq\ 10^9\ (1\leq\ i\leq\ N) $
- 入力はすべて整数である

### Sample Explanation 1

以下の操作を行うことで、最終的に残る $ 2 $ 枚のカードに書かれた整数の和を最小にできます。 - 最初、カードに書かれた整数は順に $ 3,1,4,2 $ である。 - $ 1,2,3 $ 番目のカードを選ぶ。$ 1 $ の書かれた $ 2 $ 枚目のカードを食べ、残ったカードに書かれた整数に $ 1 $ を足し、山のもとの位置に戻す。カードに書かれた整数は順に $ 4,5,2 $ となる。 - $ 1,2,3 $ 番目のカードを選ぶ。$ 5 $ の書かれた $ 2 $ 枚目のカードを食べ、残ったカードに書かれた整数に $ 5 $ を足し、山のもとの位置に戻す。カードに書かれた整数は順に $ 9,7 $ となる。 - 最後に残った $ 2 $ 枚のカードに書かれた整数の和は $ 16 $ になる。

## 样例 #1

### 输入

```
4
3 1 4 2```

### 输出

```
16```

## 样例 #2

### 输入

```
6
5 2 4 1 6 9```

### 输出

```
51```

## 样例 #3

### 输入

```
10
3 1 4 1 5 9 2 6 5 3```

### 输出

```
115```

# 题解

## 作者：小粉兔 (赞：23)

可以发现 $A_1$ 和 $A_N$ 没啥用，不用考虑它们，然后最后加到答案里去就行。

那也就是说，现在有 $N - 2$ 个数排成一行，你每次可以删掉其中一个，它就会加到左右两边去。

特别的，如果它在最左边，它就会被加到一个变量 $L$ 上，如果它在最右边，它就会被加到一个变量 $R$ 上。

最后要让 $L + R$ 最小。

这时可以考虑倒着做。假设最后一个删掉的元素，是 $i$。

那么 $i$ 左边的数，一部分扔到 $L$ 里了，一部分扔到 $i$ 上了，$i$ 右边的数，一部分扔到 $R$ 里了，一部分扔到 $i$ 上了。

然后删除 $i$ 本身，就有那些扔到 $i$ 上的数，以及 $i$ 本身，都会被加到 $L$ 和 $R$ 上。

那么我们假设，$i$ 左边的数删除后，加到 $i$ 上，总共加了 $x$。那么这 $x$ 最后产生的贡献就是 $2x$，因为加到了 $L$ 和 $R$ 上。

右边同理，只不过换了个方向，也是两倍贡献。

既然倒着考虑了，那就要想到区间 DP。我们观察 $i$ 左边的区间，这段区间中的数，加到左边会对总答案贡献 $1$ 倍，但是加到右边会贡献 $2$ 倍。

于是定义如下状态：$dp(l, r, cl, cr)$ 表示考虑区间 $[l, r]$ 中的数，把它们删除后，会对总答案贡献 $cl \cdot L + cr \cdot R$，要使这个贡献最小。

则最终答案为 $dp(2, N - 1, 1, 1) + A_1 + A_N$。

有转移：

$$ dp(l, r, cl, cr) = \min_{i = l}^{r} [ dp(l, i-1, cl, cl + cr) + dp(i + 1, r, cl + cr, cr) + (cl + cr) A_i ] $$

特别地，如果 $l > r$，则 DP 值为 $0$。

容易发现，DP 状态数的上界是 $\mathcal O (N^2 2^N)$，因为区间只有 $\mathcal O (N^2)$ 对，而后面的系数的增长可以看作一个 $N$ 层的二叉树的形态。

经过一些精细计算，其实 DP 状态数和转移数只有 $\mathcal O (2^N)$，这里就略去不证了。

---

## 作者：StudyingFather (赞：16)

*集训队作业 2019 AGC035D*

考虑计算每个元素对答案的贡献次数。

我们来倒着考虑整个过程。刚开始我们只有两个元素，这两个元素对答案的贡献次数为 $1$。假如在 $a_i$ 和 $a_{i+1}$ 中插入了一个元素，这个元素会对总答案产生多少次贡献呢？

容易发现，设 $a_i$ 被计入答案 $x_i$ 次，则这个元素会对答案产生 $x_i+x_{i+1}$ 次贡献。

我们设 $f(l,r,xl,xr)$ 代表区间 $[l,r]$ 中，$a_l$ 将被计算 $xl$ 次，$a_r$ 将被计算 $xr$ 次的最小和（注意这时候 $a_l$ 和 $a_r$ 对答案的贡献还没有被统计）。

转移的时候枚举断点，将整个区间拆分成两个区间递归求解即可。

转移方程为：

$$
f(l,r,xl,xr)=\min_{l \lt p \lt r} f(l,p,xl,xl+xr)+f(p,r,xl+xr,xr)+a_p \times (xl+xr)
$$

最后要求的当然是 $f(1,n,1,1)+a_1+a_n$。

代码写起来非常短（

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
long long a[25];
long long dfs(int l,int r,int xl,int xr)
{
 if(r-l<=1)return 0;
 long long ans=1e18;
 for(int i=l+1;i<=r-1;i++)
  ans=min(ans,dfs(l,i,xl,xl+xr)+dfs(i,r,xl+xr,xr)+a[i]*(xl+xr));
 return ans;
}
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<=n;i++)
  cin>>a[i];
 cout<<a[1]+a[n]+dfs(1,n,1,1)<<endl;
 return 0;
}

```


---

## 作者：xzx34 (赞：11)

这个题的正解并不好想，但我们可以考虑随机算法。

注意到这个数据范围，$ n<=18 $，事实上我们可以选择操作顺序的数只有$ 16 $个，总共$ 16！$ 种可能的状态。

于是我们可以尝试模拟退火/爬山，显然，我们可以调整两张卡被抽走的先后顺序，并$ O(n) $ 的尝试更新结果（用链表实现）。

经过漫长的调参，我的模拟退火在ATCoder上得到了99AC 3WA 的好成绩，而参数上已经没有什么优化可能了。

但是我们仔细思考，发现这个题很难搞成什么跳不出去的局部最优局面，于是我们放弃退火直接暴力爬山，最后得到了102AC的优秀成绩。

因为AtCoder上是102个点的捆绑测试，能通过102个点的大捆绑的随机化的正确性应该还是比较可靠的吧。。。

然后欢迎大家来hack这个做法吧hhh

```cpp
#include <bits/stdc++.h>
#define re register int 
#define il inline
#define ll long long
using namespace std;
const int inf=1e9;
il int read(){
	char c=getchar();int z=0,f=1;
	while(c!='-'&&(c>'9'||c<'0')) c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(c>='0'&&c<='9') z=(z<<1)+(z<<3)+c-'0',c=getchar();
	return z*f;
}
const int N=20;
ll ans=1e15;
int n,a[N],le[N],ri[N],b[N];
ll v[N];
il ll chk(){
	for(re i=1;i<=n;i++) v[i]=a[i],le[i]=i-1,ri[i]=i+1;
	for(re i=2;i<=n-1;i++){
		int x=b[i];
		v[le[x]]+=v[x];v[ri[x]]+=v[x];
		le[ri[x]]=le[x],ri[le[x]]=ri[x];
	}
	return v[1]+v[n];
}
il void work(){
	random_shuffle(b+2,b+n);
	ll now=chk(),nex;
	for(re i=1;i<=1000;i++){
		int p=rand()%(n-2)+2,q=rand()%(n-2)+2;
		swap(b[q],b[p]);nex=chk();
		if(nex<now) now=nex;
		else swap(b[q],b[p]);
	}
	ans=min(ans,now);
}
int main (){
	n=read();
	for(re i=1;i<=n;i++) a[i]=read(),b[i]=i;
	if(n==2) return cout<<a[1]+a[2],0;//防RE
	while(clock()<=1.8*CLOCKS_PER_SEC) work();
	cout<<ans;
	return 0;
}
```


---

## 作者：tuiyideleba (赞：6)

提供一种比较快且比较弱智的做法。

最笨的，对于每一个区间，我们把所有可能的左右端点的值全部记下来。

转移是显然的，对于区间 $[l,r]$ ，枚举一个点 $k$ ，表示 $(l,r)$ 中最后一个操作的位置。

设区间 $[l,k]$ 的左右端点的值分别为 $a,b$ ，区间 $[k,r]$ 的左右端点的值分别为 $c,d$ 。

则有操作前点 $k$ 的值为 $b+c-a_k$ ，操作后点 $l,r$ 的值分别为 $a+b+c-a_k$ 和 $b+c+d-a_k$ 。

考虑时间复杂度，显然有 $T(n)=\sum_{i=2}^{n-1} T(i)T(n-i+1)$ ， $T(2)=1$ ，其中 $T(n)$ 表示长度为 $n$ 的区间的状态数。

当 $n$ 取到 $18$ 时 $T(n)\approx 3.5\times 10^7$ ，可能可以通过一些奇技淫巧卡过去。

发现一个显然的结论，对于一个区间，当一个状态的左右端点的值均 $\le $ 另一个状态时，后者就可以删掉。

感受一下，很快啊，一下子就过了。[提交记录](https://atcoder.jp/contests/agc035/submissions/45508878)。这份代码在细节上可能和上面说的略有不同。

---

## 作者：louhao088 (赞：3)

较好的 dp 题。

我们用天顶星科技时光倒流，把拿牌变为加牌，可以证明答案不变。 

这样我们用 $f[i][j][k][l]$ 表示第 i 到 j 且第 i 个被算了 k 次 第 j 个被算了 l 次的最小代价，且第 i 个 和 第 j 个不算。

很容易推出转移 ：

$f[i][j][k][l]=\min (f[i][p][k][k+l]+f[p+1][j][k+l][l]) (i<k<j)$。

我们要计算的是 $f[1][n][1][1]+a[1]+a[n]$。

我采用了可 dfs 直接算，开数组可能会爆内存。根据小粉兔大佬的精密计算，这样的复杂度是 $O(2^n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define int long long
const int maxn=21;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,a[maxn];
int dfs(int l,int r,int L,int R)
{
	if(r-l<=1)return 0;
	int ans=1e18;
	for(int i=l+1;i<=r-1;i++)
		ans=min(ans,dfs(l,i,L,L+R)+dfs(i,r,L+R,R)+a[i]*(L+R));
	return ans;	
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(); 
	cout<<a[1]+a[n]+dfs(1,n,1,1)<<endl;
 	return 0;
}

```

---

## 作者：little_sun (赞：3)

### 题目大意

有一个长度为$n$的序列$\{a_i\}$，每次可以选择连续的$3$个数，把中间那个数加到左右两个数上后删除中间那个数。

求最后剩下的两个数的最小值。 $n \leq 18$

### 分析

我们发现最后的结果肯定是每一个$a_i$乘上一个系数的和，我们考虑倒着$\texttt{dp}$  

设$\texttt{f[l][r][x][y]}$表示当前区间的左右端点分别是$l, \; r$，$[l, r]$之间的部分已被删除，$a_l$的系数为$x$，$a_r$的系数为$y$，对整个序列贡献的答案。

那么我们模仿区间$\texttt{dp}$的形式，枚举一个中间点$\texttt{mid} \in (l, r)$则$f[l][r][x][y] = \min\{f[l][mid][x][x+y]+f[mid][r][x+y][y]+a[mid] \times (x+y)\}$

由于$n$不大，直接搜索即可。

由于$\texttt{(x,y)}$从$(1,1)$开始，每一步最多会拓展$2$个状态，所以总的$(x,y)$数量是$O(2^n)$的

又由于总共只有$O(n^2)$个区间，所以粗略估计本题的复杂度是$O(n^2 \times 2^n)$

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)

ll n, a[50];

ll f(ll l, ll r, ll x, ll y)
{
    ll ans = 1e18;
    if(r - l <= 1) return 0;
    for(int i = l + 1; i <= r - 1; i++)
        ans = std::min((f(l, i, x, x + y) + f(i, r, x + y, y) + a[i] * (x + y)), ans);
    return ans;
}

int main()
{   
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    printf("%lld\n", f(1, n, 1, 1) + a[1] + a[n]);
    return 0;
}
```

---

## 作者：xht (赞：2)

## [Add and Remove](https://atcoder.jp/contests/agc035/tasks/agc035_d)

### 题意

- 给定 $n$ 个数 $a_{1\dots n}$。
- 你需要进行若干次下列操作，直到只剩下两个数：
  - 选择三个连续的数 $a_{i-1},a_i,a_{i+1}$。
  - 将 $a_{i-1},a_{i+1}$ 都加上 $a_i$，然后删掉 $a_i$。
- 要求最小化最终剩下的两个数的和。
- $n \le 18$。

### 题解

显然答案是对于每个 $a_i$ 乘上一个系数 $x_i$。

倒序考虑整个过程，一开始只有两个元素 $a_1,a_n$，这两个元素的系数 $x_1 = x_n$ 都为 $1$。若在 $a_i$ 和 $a_j$ 中插入了一个元素，其中 $a_i$ 的系数为 $x_i$，$a_j$ 的系数为 $x_j$，则可以发现插入的元素系数为 $x_i + x_j$。

考虑 DP，我们设 $f(i,j,l,r)$ 表示对于区间 $[i,j]$，$x_i = l$，$x_j = r$ 时 $(i,j)$ 对答案的最小贡献，转移时枚举断点 $d \in (i,j)$ 即可。

状态数的上界为 $\mathcal O(n^22^n)$。

### 代码

```cpp
const int N = 19;
int n, a[N];

ll f(int i, int j, int l, int r) {
	ll ans = 1e18;
	if (j - i <= 1) return 0;
	for (int d = i + 1; d < j; d++)
		ans = min(ans, f(i, d, l, l + r) + f(d, j, l + r, r) + 1ll * a[d] * (l + r));
	return ans;
}

int main() {
	rd(n), rda(a, n);
	print(f(1, n, 1, 1) + a[1] + a[n]);
	return 0;
}
```

---

## 作者：xcyle (赞：2)

### 前言

本篇题解的可能和其它题解略有不同。本蒟蒻没想到记搜，于是傻傻的写了个区间dp

### 分析

很多人可能第一眼会想贪心，每次选最小的

然而这个显然不行，再观察以下数据范围$n\le 18$，这显然是$2^n \times n$或者$n^5$

回到题面，观察以下这个数学模型。我们可以看做安排一个删数先后顺序的排列，删掉之后我们让其它的东西位置不变就好了

### 算法

于是我尝试用dp代替贪心，容易想到区间dp，于是思考转移，发现枚举区间内最后一次操作的位置时，两侧的答案是互不影响的，因此我们只需要让两边的内部最小化

但是容易发现一段区间可以对两侧都造成贡献，因此我们希望找到一个平衡点。

换个角度，我们倒退。考虑整个序列$[1,n]$其实只有$[2,n-1]$是可以删掉的，假设最后一次删掉的位置是$i$，假设$[l,r]$内的操作对左侧产生$A$的代价，对右侧产生$B$的代价，那么$[l,r]$将会对最终答案产生$A+2\times B$ 的代价

因为$B$将会作用在$i$上。这样的话，我们希望[l,r]内的操作可以最小化$A+2\times B$，因此将这两个东西压入状态就好了

具体来说，我们设$f[l][r][a][b]$为区间$[l,r]$内的操作使得$a\times A + b \times B$最小的代价

到此为止，我和别的题解的思路都差不多

### 乱搞（?）

我没有意识到可以记搜，因此真的写了区间dp

接下来我们来分析以下这个东西

系数$a$和$b$的上界是$2^n=2\times 10^5$，如果我把后两维状态直接设为$2\times 10^5$，显然时空都会炸

因此接下来我卡亿点常数

显然$a,b$在每一次会变成$a+b$，因此长度为$len$的区间的系数最大为$F_{n-len-1}$，这里$F$是斐波那契数列

而斐波那契数列的第15项到第20项大概长这样：

377,610,987,1597,2584

$F_{18}$还是四位数级别，显然还不够

至此，通过以上分析，时间约为$\sum \limits_{len=1}^n F_i \times (n - len + 1)$，已经能在atcoder上的评测机跑过了

接下来只需要卡空间即可

其实空间也是跑不满的，如果闲得无聊可以开个vector去卡

这里我使用了暴力卡常技巧：用码量换空间

显然$F_{15}=377$是符合我们的要求的，系数大于这个东西只有可能是$len = 2$，我们用码量暴力做就可以了：

```cpp
#define calc(l, r, a, b) min(s[r] * (a + 2 * (b)) + (a + b) * s[l], s[l] * ((a) * 2 + b) + (a + b) * s[r])
```
卡到这里，你就会惊喜的发现自己AC了本题

附代码
```cpp
#include <iostream>
#include <cstdio>
#define maxn 19
#define S 755
#define calc(l, r, a, b) min(s[r] * (a + 2 * (b)) + (a + b) * s[l], s[l] * ((a) * 2 + b) + (a + b) * s[r])
using namespace std;
const long long INF = 999999999999999999;
int n;
long long s[maxn];
long long f[maxn][maxn][S][S];
int fi[maxn];
int main()
{
	scanf("%d", &n);
	fi[0] = 1, fi[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		fi[i] = fi[i - 1] + fi[i - 2];
//		printf("%d %d\n", i, fi[i]);
	}
	for (int len = 2; len <= n - 2; len++)
	{
		for (int l = 2; l < n - len + 1; l++)
		{
			int r = l + len - 1;
			for (int a = 1; a <= fi[n - len - 1]; a++)
			{
				for (register int b = 1; b <= fi[n - len - 1]; b++)
				{
					f[l][r][a][b] = INF;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &s[i]);
		for (long long a = 1; a < S; a++)
		{
			for(long long b = 1; b < S; b++)
			{
				f[i][i][a][b] = (a + b) * s[i];
			}
		}
	}
	for (int len = 3; len <= n - 2; len++)
	{
		for (int l = 2; l < n - len + 1; l++)
		{
			int r = l + len - 1;
			for (long long a = 1; a <= fi[n - len - 1]; a++)
			{
				for (long long b = 1; b <= fi[n - len - 1]; b++)
				{
					for (register int k = l; k <= r; k++)
					{
						long long tmp1, tmp2;
						if(k - l == 2) tmp1 = calc(l, k - 1, a, a + b);
						else if(k - l == 1) tmp1 = (2 * a + b) * s[l];
						else if(k - l == 0) tmp1 = 0;
						else tmp1 = f[l][k - 1][a][a + b];
						if(r - k == 2) tmp2 = calc(k + 1, r, a + b, b);
						else if(r - k == 1) tmp2 = (a + 2 * b) * s[r];
						else if(r - k == 0) tmp2 = 0;
						else tmp2 = f[k + 1][r][a + b][b];
						f[l][r][a][b] = min(f[l][r][a][b], tmp1 + tmp2 + (a + b) * s[k]);
					}
				}
			}
		}
	}
	if(n == 3) printf("%lld", s[1] + s[2] * 2 + s[3]);
	else if(n == 4) printf("%lld", (calc(2, n - 1, 1, 1)) + s[1] + s[n]);
	else printf("%lld",f[2][n - 1][1][1] + s[1] + s[n]);
	return 0;
}
```

---

## 作者：starseven (赞：1)

[AtCoder](https://atcoder.jp/contests/agc035/tasks/agc035_d)

[luogu](https://www.luogu.com.cn/problem/AT5141)

[我的博文](https://www.cnblogs.com/starseven/p/13100304.html)

-----

# 题目大意：

给定一个长度为$N$的序列，每一次可以选择连续的三个数$a_{i-1}$,$a_{i}$,$a_{i+1}$,将其合并变为$a_{i-1}+a_{i}$和$a_{i},a_{i+1}$,依次合并，最后只剩下两个数，求合并后这两个数的和的最小值。

# 输入格式：

$n$

$a_1$ $a_2$ $a_3$ $a_4$ $\dots$ $a_n$

# 思路分析

## 1. 猜测

刚拿到这道题的时候，我看了一下，发现不可做（~~哈哈哈~~）

但是我看了一下数据范围

$$ n \leq 18 $$

然后通过计算器可以算出来

$$ 2^{18}= 262144 $$

$$ 3……{18}=\dots $$

然后可以猜出，$2$的指数级别的可做。

## 2.分析猜测

我在上面为什么要写出2的指数，不是因为其他，就是因为在竞赛里面，这种看着$n$特别小的东西，一般时间复杂度都是指数级别的。

所以我们可以猜测时间复杂度的主流是$2^n$

## 3.分析题目

题目上描述的是将中间删去，再添加到两边去，那么我们可以考虑到说选两个点$l$,$r$,表示在l~r区间中最后留下来的是l&r。

题目上说的是将中间的删去，再添加到两边上去，那么我们可以想到**正难则反**的思想！


我们不考虑第一个删去的是谁，我们考虑最后一个留下的是谁。我们可以分析出为什么要这样想：

因为若是考虑第一个删去的是谁，那删去之后就还有许多不确定的抉择，很难分析，而且无法划分出区间，但是若考虑最后留下 的是谁，那我们就可以清楚的划分出区间，然后左右区间处理就对了。

区间！关键词！

那我们就自然而然想到区间DP

首先，操作可以看做是选择不是两边的一个数，将它删去并把它加到左右两项上

妨考虑倒序考虑整个过程，同时最后的结果一定是每个数乘上一个系数的和。那么最开始，$a_1$和$a_n$的系数都是1

那就可以考虑说设$dp[l][r][x][y]$

表示当前未被删除的数两端是l和r，中间的数已经被删除过了。$a_l$对答案贡献的系数为$x$,$a_r$对答案贡献的系数为$y$。

然后每次转移的时候就是贡献的转移

$$ f[l][r][x][y]=min(f[l][i][x][x+y]+f[i][r][x+y][y]+a[i]\times (x+y)) $$

这样下来的话就是$O(n^3 \times 2^n)$

可是我们完全可以将其改为搜索，然后$n^3$就没有了

$$ the\;small\;but\;strong\;code $$

```cpp
#include<cstdio>
#include<iostream>
#define re register int
#define Starseven main
#define ll long long
using namespace std;
const int N=20;
ll a[N];

ll Dfs(int l,int r,int x,int y){
	if(l+1>=r) return 0;
	ll ans=100000000000000000;
	for(re i=l+1;i<=r-1;i++)
		ans=min(ans,Dfs(l,i,x,x+y)+Dfs(i,r,x+y,y)+a[i]*(x+y));
	return ans;	
}

int Starseven(void){
	int n;
	cin>>n;
	for(re i=1;i<=n;i++) cin>>a[i];
	cout<<a[1]+a[n]+Dfs(1,n,1,1)<<endl;
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

一道其实还是挺有意思的题目，被机房一堆人秒切了自己却还只能想一半，太菜了。        

首先看这数据范围，我就直接想搜了，但是想了想感觉时间复杂度还是有点惨就没往这方面想了。      

接着就发现了 $a_1$ 和 $a_n$ 是两个混子，根本没有什么用，对答案的影响就是他们本身，所以发现“区间端点”和此题的联系。      

感觉可以把原序列拆成一些子问题最后来合并答案，考虑区间 $DP$ 。    

对于区间 $DP$ 有一个很经典的套路：考虑最后一步怎么转移的，假设我们现在只有两个数 $a_1$ 和 $a_n$ 。      

那么现在我们知道这个 $a_1,a_n$ 都只会被贡献 $1$ 次，诶我们就知道他的贡献了，接着考虑中间有个数 $a_{mid}$ ，现在我们就只有一种办法：删除 $a_{mid}$ ，然后把它的贡献次数变成 $2$ 后得到答案，发现了一个数的贡献次数其实可以累加。     

接着我们考虑还原这个长度为 $n$ 的序列，在 $mid$ 这个地方把区间截成两半算，也就是变成了 $(a_1 , a_{mid})$ 和 $(a_{mid} , a_n)$ 两个问题并加上 $a_mid$ 的贡献。      

由于 $a_{mid}$ 的贡献次数如上述就是 $2 = num_{a_1} + num_{a_n}$ ，所以我们可以知道在拆子问题的时候，我们中间枚举的点的贡献次数就是 $num_{a_l} + num_{a_r}$ ，用一个 $dp(l,r,num_l,num_r)$ 即可表示一种状态，而状态转移方程就是：      

$\sum_{i = l + 1}^{r - 1}dp(l,r,num_l,num_r) = min(dp(l , i , num_l , num_l + num_r) + dp(i , r , num_l + num_r , num_r) + (num_l + num_r) \times a_i)$      

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>//发现了最后最左边和最右边的数死不掉 
using namespace std;
const int Len = 55;
long long n,m,a[Len];
long long dfs(int l,int r,int Lnum,int Rnum)
{
	if(l + 1 == r) return 0;
	long long ans = 1e15;
	for(int i = l + 1 ; i <= r - 1 ; i ++) ans = min(ans , dfs(l , i , Lnum , Rnum + Lnum) + dfs(i , r , Lnum + Rnum , Rnum) + a[i] * (Lnum + Rnum));	
	return ans;
} 
int main()
{
	scanf("%lld",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld",&a[i]);
	printf("%lld\n",dfs(1 , n , 1 , 1) + a[1] + a[n]);
	return 0;
}
```

---

