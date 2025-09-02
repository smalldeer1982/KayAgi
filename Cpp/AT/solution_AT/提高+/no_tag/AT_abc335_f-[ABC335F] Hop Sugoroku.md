# [ABC335F] Hop Sugoroku

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc335/tasks/abc335_f

一列に並んだ $ N $ 個のマス $ 1,2,\dots,N $ と長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ があります。  
 最初、マス $ 1 $ は黒く、他の $ N-1 $ 個のマスは白く塗られており、 $ 1 $ つのコマがマス $ 1 $ に置かれています。

以下の操作を $ 0 $ 回以上好きな回数繰り返します。

- コマがマス $ i $ にあるとき、ある正整数 $ x $ を決めてコマをマス $ i\ +\ A_i\ \times\ x $ に移動させる。
  - 但し、 $ i\ +\ A_i\ \times\ x\ >\ N $ となるような移動はできません。
- その後、マス $ i\ +\ A_i\ \times\ x $ を黒く塗る。
 
操作を終えた時点で黒く塗られたマスの集合として考えられるものの数を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 2\ \times\ 10^5 $
 
### Sample Explanation 1

黒く塗られたマスの集合として考えられるものは以下の $ 8 $ 通りです。 - マス $ 1 $ - マス $ 1,2 $ - マス $ 1,2,4 $ - マス $ 1,2,4,5 $ - マス $ 1,3 $ - マス $ 1,4 $ - マス $ 1,4,5 $ - マス $ 1,5 $

### Sample Explanation 3

$ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
5
1 2 3 1 1```

### 输出

```
8```

## 样例 #2

### 输入

```
1
200000```

### 输出

```
1```

## 样例 #3

### 输入

```
40
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
721419738```

# 题解

## 作者：2huk (赞：5)

> 形式化题意：
>
> 给定 $n$ 和 $a_1 \dots a_n$。求有多少个正整数序列 $b_1 \dots b_k$（长度 $k$ 任意），满足：
>
> - 对于所有 $i \in [1, k)$，有 $b_i < b_{i + 1} \le n$；
> - $b_1 = 1$；
> - 对于所有 $i \in (1, k]$，存在正整数 $x$，使得 $b_i = b_{i - 1} + a_{b_{i - 1}} \cdot x$。

首先对「存在正整数 $x$，使得 $b_i = b_{i - 1} + a_{b_{i - 1}} \times x$」变形：
$$
b_i = b_{i - 1} + a_{b_{i - 1}} \cdot x\\
b_i - b_{i - 1} = a_{b_{i - 1}} \cdot x\\
x = \dfrac {b_i - b_{i - 1}}{a_{b_{i - 1}}}
$$
也就是说需要保证 $a_{b_{i - 1}} \mid (b_i - b_{i - 1})$。

然后直接 DP。设 $f_i$ 表示 $b_k = i$ 的 $b$ 的数量。

转移显然。$\mathcal O(n^2)$ 的初始 DP：

```cpp
f[1] = 1;
for (int i = 2; i <= n; ++ i )
    for (int j = 1; j < i; ++ j )
        if ((i - j) % a[j] == 0)
            (f[i] += f[j]) %= P;
```

答案为 $\sum _{i = 1} ^ n f_i$。

改成刷表，枚举  $a_i$ 的所有倍数：

```cpp
f[1] = 1;
for (int i = 1; i <= n; ++ i )
	for (int j = a[i]; j + i <= n; j += a[i])
		(f[j + i] += f[i]) %= P;
```

继续瞎改：

```cpp
f[1] = 1;
for (int i = 1; i <= n; ++ i )
	for (int j = a[i] + i; j <= n; j += a[i])
		(f[j] += f[i]) %= P;
```

可以发现，当 $a_i$ 很大时，内层循环的复杂度是很低的。但问题就出在了 $a_i$ 比较小的时候。

直接联想根号分治。令 $B = \sqrt n$。

当 $a_i > B$ 时，还是上面那么做。否则维护额外信息。

首先把 $(i - j) \bmod a_j = 0$ 替换为 $i \equiv j \pmod {a_j}$。

理解 DP 可以从集合角度分析。那么我们将 $s_{x, y}$ 定义为：

- $s_{x, y}$ 表示所有满足 $x = a_i, y = i \bmod a_i$ 的 $i$ 构成的集合。即 $s_{x, y} = \{i \mid x = a_i, y = i \bmod a_i\}$。

并且定义 $g(A)= \sum\limits_{i \in A} f_i$，其中 $A$ 是一个集合。

转移有：
$$
f_k = \sum_{i = 1}^{B} g(s_{i, k \bmod i})
$$
这样理解转移方程：

- 首先令 $s_{i, k \bmod i}$ 这个集合中的一个元素为 $t$，即 $t \in s_{i, k \bmod i}$，那么**根据定义**有：

  - $i = a_t$；
  - $k \bmod i = t \bmod a_t$；

  稍微解释一下：这里 $i$ 表示定义中的 $x$，$k \bmod i$ 表示定义中的 $y$，$t$ 表示定义中的 $i$，$a_t$ 表示定义中的 $a_i$。事实上就是这八个东西互相替换了。

- 那么将 $1$ 式代入 $2$ 式，有：

  - $k \bmod a_t = t \bmod a_t$，即 $k \equiv t \pmod {a_t}$。

然后发现这样就满足了最开始 $f_k$ 的定义。

[代码](https://atcoder.jp/contests/abc335/submissions/49124764)。



---

## 作者：FReQuenter (赞：5)

设当前纸片在点 $i$ 的方案数为 $f_i$。则最终答案为 $\sum^{n}_{i=1} f$。

考虑 $f$ 有两种转移方式：

- 枚举之前是哪里转移过来的。记 $sum_{i,j}$ 表示在形如 $j+ka_i(k>0)$ 的点可被转移到的方案数。复杂度 $O(na_i)$。

- 去更新后方的转移。即对所有的 $f_{i+ka_i}(k>0)$ 加上 $f_i$。时间复杂度 $O(\frac{n}{a_i})$。

不难发现当取 $a_i=\sqrt n$ 的时候两种转移复杂度都是 $O(n\sqrt n)$。所以考虑根号分治。对 $a_i\le\sqrt n$ 采取前者，否则后者。

```cpp
#pragma GCC optimize(2,3,"inline","-Ofast")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define int long long
#define mod 998244353
using namespace __gnu_pbds;
using namespace std;
int n,sqr=700,ans,a[200005],sum[1005][1005],f[200005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	f[1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=sqr;j++) f[i]+=sum[j][i%j],f[i]%=mod;
		if(a[i]<=sqr){
			sum[a[i]][i%a[i]]+=f[i],sum[a[i]][i%a[i]]%=mod;
		}
		else{
			for(int j=i+a[i];j<=n;j+=a[i]) f[j]+=f[i],f[j]%=mod; 
		}
		ans+=f[i],ans%=mod;
	}
	cout<<ans;
} 
```

---

## 作者：robinyqc (赞：5)

首先棋子不能回退，无后效性，考虑朴素 dp。设 $dp_i$ 表示当前棋子在第 $i$ 格的填色方案。显然有：

$$
dp_i\to dp_{i + kA_i}(k\in \mathbb{N_+})
$$

复杂度 $O(n^2)$，不行。

有另一种方法，维护一个 $V\times n$ 的表格 $b$，$b_{i, j}$ 表示模 $i$ 为 $j$ 的位置的 dp 值。那么有：

$$
\begin{aligned}
dp_i = \sum_{j = 1}^V b_{j, i \bmod j}\\
dp_i\to b_{A_i, i \bmod A_i}\\
\end{aligned}
$$

然而也是 $O(n^2)$。

你会发现对于第一种方法，若 $A_i$ 很大，转移数就很小。对于第二种方法，若所有 $A_i$ 都比较小，复杂度就可以接受。所以考虑根号分治。

设阈值 $B$。若 $A_i$ 大于等于 $B$ 就直接方法一转移。否则，放进表格里惰性转移。取 $B = \sqrt n$，则总复杂度 $O(n\sqrt n)$。

### 代码实现

```cpp
#include <iostream>
#include <atcoder/modint.hpp>
using namespace std;
using namespace atcoder;

const int N = 200005, B = 450;

int n;
modint998244353 dp[N], v[B][B];

signed main()
{
    cin >> n;
    dp[1] = 1;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        for (int j = 1; j < B; j++) {
            dp[i] += v[j][i % j];
        }
        if (a < B) {
            v[a][i % a] += dp[i];
        }
        else {
            int p = i;
            while (p + a <= n) {
                p += a;
                dp[p] += dp[i];
            }
        }
    }
    modint998244353 ans = 0;
    for (int i = 1; i <= n; i++) ans += dp[i];
    cout << ans.val() << '\n';
    return 0;
}
```

---

## 作者：未来姚班zyl (赞：4)

## 题目大意

有 $n$ 个点，你初始时在点 $1$，位于点 $i$ 时，可以跳到 $i+ka_i$（$k$ 为正整数）。求可能经过的点集总数。

## 题目分析

设 $dp_i$ 为在 $i$ 结尾的方案总数，则有答案等于 $\sum dp_i$，且能得出朴素转移：

$$dp_i\rightarrow dp_{i+ka_i}$$

则 $i$ 能转移到 $j$ 当且仅当 $i<j$ 并且 $i+ka_i=j$，即 $i\bmod a_i=j\bmod a_i$。

看到取模，啪的一下就是一个根号分治，很快啊，设阈值为 $B$。

对于 $a_i\le B$ 的 $i$，直接用一个 $B\times B$ 的数组记录每个模数对应的结果的 $dp_i$ 的和，复杂度 $O(nB)$。

对于 $a_i>B$ 的 $i$，直接暴力转移，复杂度 $O(\frac{n}{B}n)$。

根据基本不懂式，$B$ 取 $O(\sqrt n)$ 时有理论最优复杂度 $O(n\sqrt n)$。轻松通过此题。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
inline ll read(){ll s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =3e5+5,M=1e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n=read(),a[N],siz=450;
int dp[N],ans;//以i结尾的方案数
int ct[455][455]; 
signed main(){
	repn(i)a[i]=read();
	dp[1]=1;
	if(a[1]<=siz)ct[a[1]][1%a[1]]=1;
	else for(int j=1+a[1];j<=n;j+=a[1])dp[j]=1;
	rep(i,2,n){
		rep(j,1,siz)add(dp[i],ct[j][i%j]);
		if(a[i]<=siz)add(ct[a[i]][i%a[i]],dp[i]);
		else for(int j=i+a[i];j<=n;j+=a[i])add(dp[j],dp[i]);
	}
	repn(i)add(ans,dp[i]);
	cout <<ans;
	return 0;
}
```


---

## 作者：LiJoQiao (赞：2)

[更好的阅读体验](https://www.cnblogs.com/LiJoQiao/p/17949738)  
题意翻译：

>- 有 $N$ 个格子。  
>- 你初始在格子 $1$。  
>- 格子 $1$ 是染黑的，其他的格子都是白的。  
>- 当你在格子 $i$ 的时候，你可以到达 $a_i\times x+i,x>0$ 或将该格子染黑。  
>- 求所有格子的状态有多少种情况。  

首先我们来考虑一下不加优化的 dp。  
对于任意一个格子 $i\ne1$，都可以是白的，不妨设格子 $1$ 也可以是白的，然后将答案除以 $2$。  

`dp[i]` 统计的是对于一个格子 $i$ 可以到达其他格子的染色的情况，转移方程为 $dp_i=\sum\limits_{j,a_j\mid(i-j)}dp_j+2$。  
这个 dp 是倒着跑的。  

好像不是很好优化啊，一时间想不出来数据结构。  

赛事用了反着的前缀和可以让两个 TLE -> AC。  
能不能用每几个数求和的类似于前缀和的东西，优化一下。  

如果不论每多少数都求这个东西复杂度会炸掉。  

可以隔的数的数量最大到 $\sqrt N$，此时在空间时间都会平衡一些。  

定义一个二维的 `sum[i][j]`，存的是在某点之后的 $\sum\limits_{dp_{i\times x+j},x\ge 0}$，跑 dp 的时候维护一下，如果 $a_i\le\sqrt N$ 就直接加一下，否则暴力。  

这样的做法是 $N\sqrt N$ 的。  

代码如下。  

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN=2e5+10,MAXSQRTN=500,MOD=998244353;
int n,a[MAXN],dp[MAXN],sum[MAXSQRTN][MAXSQRTN];
template<typename T>
T read(){
	T f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return f*x;
}
namespace sol{
	void solve(){
		n=read<int>();
		for(int i=1;i<=n;++i){
			a[i]=read<int>();
		}
		int T=sqrt(n);
		for(int i=n;i;--i){
			dp[i]=2;
			if(a[i]<=T){
				dp[i]+=sum[a[i]][i%a[i]];
				dp[i]%=MOD; 
			}
			else for(int j=i+a[i];j<=n;j+=a[i]){
				dp[i]+=dp[j];
				dp[i]%=MOD;
			}
			for(int j=1;j<=T;++j){
				int temp=i%j;
				sum[j][temp]+=dp[i];
				sum[j][temp]%=MOD;
			}
		}
		dp[1]=1ll*dp[1]*499122177%MOD;
		printf("%d\n",dp[1]);
	}
}
int main(){
	sol::solve();
	return 0;
}
```

---

## 作者：harmis_yz (赞：2)

比 E 简单。

## 分析

考虑暴力 DP。

定义状态函数 $f_i$ 表示最后一个黑点为 $i$ 时的方案数，有：$f_i =\sum\limits_{j=1}^{i-1}f_j[(i-j)\bmod val_j =0]$。不难发现在使用刷表法的时候，转移代码：

```cpp
for(re int j=1;i+val[i]*j<=n;++j) f[i+val[i]*j]=(f[i+val[i]*j]+f[i])%p;
```
这玩意复杂度是 $O(\frac{n}{val_i})$ 的。

又有一种 DP 方式，定义状态函数 $g_{i,j}$ 表示在枚举到下标 $x$ 时，$k \bmod i =j$ 的方案数。因为 $a \bmod b =c \bmod b$ 时，$(a-c) \bmod b =0$，所以有：$f_i =\sum\limits_{j=1}^{V} g_{j,i \bmod j}$。复杂度 $O(V)$。

然后有个很经典的东西，叫根号分治：对于 $val_i \le V$ 的情况，用第二种 DP 方式，否则使用第一种。有复杂度 $O(nV+n\frac{n}{v})$，$V=\sqrt{n}$ 时接近 $O(n\sqrt{n})$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}

const int N=2e5+10,M=sqrt(N)+10,p=998244353;
int n,val[N],ans;
int f[N],g[M][M],base;

il void solve(){
	n=read(),base=sqrt(n);
	for(re int i=1;i<=n;++i) val[i]=read();
	f[1]=1;
	for(re int i=1;i<=n;++i){
		for(re int j=1;j<=base;++j) f[i]=(f[i]+g[j][i%j])%p;
		if(val[i]<=base) g[val[i]][i%val[i]]=(g[val[i]][i%val[i]]+f[i])%p;
		else for(re int j=1;i+val[i]*j<=n;++j) f[i+val[i]*j]=(f[i+val[i]*j]+f[i])%p;
		ans=(ans+f[i])%p;
	}
	printf("%d\n",ans);
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：RYANGSJ (赞：1)

## 题意翻译

你有 $1$ 行 $n$ 列的方格，第 $i$ 个方格上有一个数字 $a_i$。初始时第 $1$ 个格子为黑色，其余格子为白色。

最开始你有一颗棋子位于 $1$ 号方格。

你可以进行任意多次移动，如过你当前在位置 $i$ ，你可以选择一个正整数 $x$ ，移动到 $i + x \times a_i$ 的位置。并把移动到的格子染成黑色。

求移动结束后有多少种不同的涂黑格子的集合。

## 题解

设 $f_i$ 表示棋子移动到 $i$ 号位置时有多少种不同的涂黑格子的集合，转移即为$f_i=\sum_{j=1}^{\lfloor \frac{n-i}{a_i} \rfloor} f_{i+j \times a_i}$，答案即为 $\sum_{i=1}^{n}f_i$。

显然这样做的时间复杂度为 $n^2$，不能通过本题，观察到 $j$ 的枚举范围，发现可以使用根号分治。

对于 $a_i > \sqrt n$ 直接进行暴力转移，对于 $a_i \le \sqrt n $，用一个数组记录下来即可。

```c++
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
using namespace std;
namespace _IO{inline int read(){char ch=getchar();int f=1,res=0;while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){res*=10;res+=ch-'0';ch=getchar();}return res*f;}inline void write(int x){if(x<0){putchar('-');write(-x);}else if(x<10){putchar(x+'0');}else{write(x/10);putchar((x%10)+'0');}return;}}
namespace _Min{inline int Min(int x,int y){return x<=y?x:y;}inline int Max(int x,int y){return x>=y?x:y;}}

using namespace _IO;
using namespace _Min;

int n,a[200005];
const int mod=998244353;
int f[200005];
int sum[200005][505];
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	f[1]=1;
	int ans=0,sq=sqrt(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=sq;j++){
			f[i]=(f[i]+sum[i][j])%mod; 
			if(i+j<=n)sum[i+j][j]=sum[i][j];
		}
		if(a[i]<=sq){
			if(i+a[i]<=n){
				sum[i+a[i]][a[i]]=(sum[i+a[i]][a[i]]+f[i])%mod;
			}
		}else{
			for(int j=i+a[i];j<=n;j+=a[i]){
				f[j]=(f[j]+f[i])%mod;
			}
		}
		ans=(ans+f[i])%mod;
	}
	write(ans);
	return 0;
}
/*

*/
```



---

## 作者：_Trangle_ (赞：1)

根据题目条件易得状态转移方程：$dp_i=\sum\limits_{x=1}^{i+xA_i\le n}{dp_{i+xA_i}}$。

显然，该式子对于 $A_i$ 较大时还好，但对于 $A_i$ 较小时就没辙了。

如何优化？

先设一个阈值 $B$。然后我们将除数和余数分类记录，用一个二维数组记录每个除数与余数所对应的 $dp_i$ 之和。若 $A_i \le B$，那么 $dp_i=sum_{A_i,i\bmod a_i}$，否则暴力计算，最后从 $1$ 到 $B$ 枚举 $j$，将 $sum_{j,i\bmod j}$ 改为 $sum_{j,i\bmod j}+dp_i$。

可以得到时间复杂度为 $O(N(\dfrac{N}{B}+B))$，显然当 $B$ 取 $\sqrt{N}$ 时，时间复杂度最优，为 $O(N\sqrt{N})$。

### code:
```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
int n;
int a[200005];
long long dp[200005], sum[450][450];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;

	for (int i = 1; i <= n; i++) cin >> a[i];

	const int len = ceil(sqrt(n));

	for (int i = n; i; i--) {
		dp[i] = 1; //棋子不移动也是一种方案

		if (a[i] <= len) dp[i] = (dp[i] + sum[a[i]][i % a[i]]) % mod;
		else for (int j = i + a[i]; j <= n; j += a[i]) dp[i] = (dp[i] + dp[j]) % mod;

		for (int j = 1; j <= len; j++) sum[j][i % j] = (sum[j][i % j] + dp[i]) % mod; //更新 sum
	}

	printf("%lld", dp[1]);
	return 0;
}
```

---

## 作者：lfxxx (赞：1)

考虑设计状态 $dp_{i}$ 表示最终棋子落在格子 $i$ 上的方案数，不难发现答案就是 $\sum dp_i$。

假若 $a_i > \sqrt n$，那么一个 $i$ 可以贡献到的 $j$ 少于 $\sqrt n$ 个，暴力即可。

否则，它会对后面所有满足 $x \bmod a_i = i \bmod a_i$ 的 $x$ 贡献，所以记录下每个模数下的每个余数的贡献即可。

总时间复杂度 $O(n \sqrt n)$。

```cpp
//dp[n]
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define mod 998244353
const int maxn = 2e5+114;
const int B = 500;
int a[maxn],dp[maxn];
int val[B+40][B+40];
vector<int> Prev[maxn];
int n;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        if(a[i]<=B) continue;
        for(int j=1;i+j*a[i]<=n;j++) Prev[i+j*a[i]].push_back(i);
    }
    dp[1]=1;
    if(a[1]<=B) val[a[1]][1%a[1]]=(val[a[1]][1%a[1]]+dp[1])%mod;
    for(int i=2;i<=n;i++){
        for(int x:Prev[i]) dp[i]=(dp[i]+dp[x])%mod;
        for(int j=1;j<=B;j++) dp[i]=(dp[i]+val[j][i%j])%mod;
        if(a[i]<=B){
            val[a[i]][i%a[i]]=(dp[i]+val[a[i]][i%a[i]])%mod;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) ans=(ans+dp[i])%mod;
    cout<<ans<<'\n';
    return 0;
}

```


---

## 作者：Milthm (赞：0)

赛时差一点就想出来了，我想到了根号分治，想到了 $a_i\ge B$ 的情况，但是小于不知道为什么没想出来。

正如上面所说，此题正解是根号分治，但是是用来优化 dp 用的。这题题目一眼看上去就是个 dp，容易得出一个暴力的转移方程：

$dp_{i+ka_i}=dp_{i+ka_i}+dp_i$

其中 $dp_i$ 表示以 $i$ 为最后一个黑格子的方案数，答案就是 $\sum dp_i$。但是这显然是 $O(n^2)$，会超时。

我们发现直接暴力做时，当 $a_i$ 比较大时循环次数就比较小，所以考虑分成两部分讨论，$a_i\ge B$ 和 $a_i<B$。

刚才 $a_i\ge B$ 已经讨论完了，这部分暴力复杂度为 $O(\frac{n^2}B)$。然后考虑 $a_i<B$，发现可以建一个二维数组先存着。所以设 $f_{i,j}$ 表示满足下标模 $i$ 余 $j$ 的 $dp$ 值的和。每次只要把 $f_{a_i,i}$（这里因为 $i$ 有可能比 $a_i$ 大，所以 $i$ 还要对 $a_i$ 取模一下）加上这个 $dp$ 值就可以了。

这部分时间复杂度是 $O(nB)$ 的，取 $B=\sqrt n$，总时间复杂度为 $O(n \sqrt n)$。



---

## 作者：TernaryTree (赞：0)

一个朴素 dp：设 $f_i$ 表示以 $i$ 结尾的合法序列的数量。则有

$$f_{i+a_ix}\gets f_{i+a_ix}+f_i$$

这东西暴力做，最坏复杂度是 $a_i$ 全 $1$ 的时候会达到 $n^2$。

然而我们发现，这样一个对构成等差数列的下标加上一个数的结构，很像一个**根号分治**的板子 P3396。我们考虑去根号分治它。

对于 $a_i\gt \sqrt n$ 的部分，我们直接暴力去对后边加上。这里是 $\dfrac{n}{a_i}\lt \sqrt n$。

对于 $a_i\le \sqrt n$，我们开一个数组 $b_{i,j}$ 表示模 $i$ 余 $j$ 的位置目前加的总和。此时直接令 $b_{a_i,i\bmod a_i}\gets b_{a_i,i\bmod a_i}+f_i$ 即可。

记得每次转移之前要先把 $f_i$ 算出来，加上 $b$ 的贡献，即

$$f_i\gets f_i+\sum_{j=1}^{\sqrt n}b_{j,i\bmod j}$$

总时间复杂度 $\Theta(n\sqrt n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int maxs = 1e3 + 10;
const int mod = 998244353;

int n, s, ans;
int a[maxn];
int f[maxn];
int rem[maxs][maxs];

signed main() {
	cin >> n;
	s = sqrt(n);
	for (int i = 1; i <= n; i++) cin >> a[i];
	f[1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= s; j++) (f[i] += rem[j][i % j]) %= mod;
		if (a[i] > s) for (int j = i + a[i]; j <= n; j += a[i]) (f[j] += f[i]) %= mod;
		else (rem[a[i]][i % a[i]] += f[i]) %= mod;
		(ans += f[i]) %= mod;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

听说有原题，但好像不太像。

很显然 DP。

实际上挺玄学的做法，令 $dp_i$ 代表第 $i$ 个点结尾的方案数。直接暴力肯定会超时。所以玄学地开两个 DP 数组，如果这个倍数间隔大于 $10^3$ 那么肯定暴力是没有问题的。所以这种情况直接暴力跳。否则，开另一个数组来存，$dp2_{i,j}$ 代表倍数间隔为 $i$，距离这个倍数取模的结果为 $j$。然后在每一次遍历的时候把之前的 $dp2$ 数组转到 $dp$ 数组上。

```cpp
int n, a[N];
int dp[N], dp2[M][M];
void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	dp[1] = 1;
	if (a[1] >= 1E3)	for (int i = 1 + a[1]; i <= n; i += a[1]) dp[i] = 1;
	else dp2[a[1]][1 % a[1]] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= min(n, (int)1e3); j++) dp[i] += dp2[j][i % j], dp[i] %= mod;
		if (a[i] >= 1e3) for (int j = i + a[i]; j <= n; j += a[i]) dp[j] += dp[i], dp[j] %= mod;
		else dp2[a[i]][i % a[i]] = (dp2[a[i]][i % a[i]] + dp[i]) % mod;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += dp[i], sum %= mod;
	cout << sum;

}
```

---

## 作者：rainygame (赞：0)

根号分治入门题。

首先考虑 DP。将从 $i$ 开始的方案数设为 $f_i$。那么有转移方程：

$$
f_i=(\sum\limits_{j \equiv i \pmod {A_i}}^{i < j \le n}f_j)+1
$$

后面那个 $+1$ 是因为可能会在 $i$ 这里停下，边界为 $f_n=1$。

发现现在这个 DP 是 $O(n^2)$ 的，考虑优化。

我们可以令 $s_{i,j}=\sum\limits_{k \equiv i \pmod j}f_k$，这样方程即为：

$$
f_i=s_{A_i,i \bmod A_i}+1
$$

转移是 $O(1)$ 了，但是维护 $s$ 是 $O(n)$ 的，怎么办？

考虑设立一个阈值 $B$，当 $A_i \le B$ 的时候使用 $s$ 转移，当 $A_i > B$ 时暴力转移。转移的复杂度为 $O(B+\frac{n}{B})$。根据均值不等式，取 $B=\sqrt{n}$ 时复杂度最优。

总时间复杂度为 $O(n\sqrt{n})$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200001
#define MAXB 448
const int MOD(998244353);

int n;
int a[MAXN], f[MAXN];
int sum[MAXB][MAXB];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i(1); i<=n; ++i) cin >> a[i];

    f[n] = 1;
    for (int i(1); i<MAXB; ++i) ++sum[i][n%i];
    for (int i(n-1); i>=1; --i){
        if (a[i] >= MAXB){
            for (int j(i); j<=n; j+=a[i]) f[i] = (f[i] + f[j]) % MOD;
        }else f[i] = sum[a[i]][i%a[i]];
        f[i] = (f[i] + 1) % MOD;
        for (int j(1); j<MAXB; ++j) sum[j][i%j] = (sum[j][i%j] + f[i]) % MOD;
    }

    cout << f[1];

    return 0;
}

```


---

