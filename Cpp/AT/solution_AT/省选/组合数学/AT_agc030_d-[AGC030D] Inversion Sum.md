# [AGC030D] Inversion Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc030/tasks/agc030_d

長さ $ N $ の整数列 $ A_1,A_2,...,A_N $ が与えられます。$ Q $ 回の操作を順に行います。 $ i $ 回目の操作は $ 2 $ つの整数 $ X_i,Y_i $ を用いて表され、以下の $ 2 $ つの操作からちょうど片方を選んで行います。

- $ A_{X_i} $ と $ A_{Y_i} $ の値を入れ替える
- 何もしない

操作の行い方は $ 2^Q $ 通りあります。これらすべての操作の行い方に対する最終的な数列の反転数をすべて足し合わせたものを $ 10^9+7 $ で割ったあまりを求めてください。

ただし、数列 $ P_1,P_2,...,P_M $ の反転数とは、$ 1\leq\ i\ <\ j\leq\ M $ かつ $ P_i\ >\ P_j $ を満たすような整数の組 $ (i,j) $ の個数です。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 0\ \leq\ Q\ \leq\ 3000 $
- $ 0\ \leq\ A_i\ \leq\ 10^9(1\leq\ i\leq\ N) $
- $ 1\ \leq\ X_i,Y_i\ \leq\ N(1\leq\ i\leq\ Q) $
- $ X_i\neq\ Y_i(1\leq\ i\leq\ Q) $
- 入力はすべて整数である

### Sample Explanation 1

操作の行い方としてありうるものは次の $ 4 $ 通りです。 - $ 1 $ 回目も $ 2 $ 回目は何もしない。最終的な数列は $ 1,2,3 $ であり、反転数は $ 0 $ である。 - $ 1 $ 回目は何もせず、$ 2 $ 回目は入れ替えを行う。最終的な数列は $ 3,2,1 $ であり、反転数は $ 3 $ である。 - $ 1 $ 回目は入れ替えを行い、$ 2 $ 回目は何もしない。最終的な数列は $ 2,1,3 $ であり、反転数は $ 1 $ である。 - $ 1 $ 回目も $ 2 $ 回目も入れ替えを行う。最終的な数列は $ 3,1,2 $ であり、反転数は $ 2 $ である。 これらの反転数の総和である、$ 0+3+1+2=6 $ を出力します。

## 样例 #1

### 输入

```
3 2
1
2
3
1 2
1 3```

### 输出

```
6```

## 样例 #2

### 输入

```
5 3
3
2
3
1
4
1 5
2 3
4 2```

### 输出

```
36```

## 样例 #3

### 输入

```
9 5
3
1
4
1
5
9
2
6
5
3 5
8 9
7 9
3 2
3 8```

### 输出

```
425```

# 题解

## 作者：小粉兔 (赞：20)

因为 $N$ 很小，考虑直接枚举位置对 $\langle i, j \rangle$（$1 \le i < j \le N$）以统计逆序对。

考虑一个概率 DP：令 $f(i, j)$（$1 \le i, j \le N$）为**当前时刻下**，$A_i > A_j$ 的概率。  
（这里假设对于 $Q$ 个操作，每个操作都以 $1 / 2$ 的概率执行）

那么最终时刻下，满足 $i < j$ 的 $f(i, j)$ 之和，再乘以 $2^Q$ 就是答案（期望的线性性）。

按顺序考虑每个时刻（操作），考虑新的 $f(i, j)$ 和原先的比有什么变化。

可以发现只有 $\mathcal O (N)$ 个位置会发生变化。具体地说，只有 $i, j$ 有至少一个等于 $X_i$ 或 $Y_i$ 时才有可能发生变化。

暴力转移即可。

时间复杂度为 $\mathcal O (N (N + Q))$，[评测链接](https://atcoder.jp/contests/agc030/submissions/9829970)。

---

## 作者：冰冷的心 (赞：10)

这题如果不知道这个转换感觉根本无法下手。。

首先发现枚举$2^q$肯定不可行 也没有存的下状态的dp

那么考虑从序列本身下手。现在的问题就在于怎么描述交换两个元素后序列的状态。

其实这个问题可转化为每次有$1/2$的概率选择进行操作，问最后期望总的逆序对数。只要再乘上$2^q$就可以了

可以这么理解：最终得到$2^q$中序列，而一对位置是逆序的概率就是这对位置在$2^q$个序列中的方案$/2^q$ 

那么设$f[i][j]$表示位置$i$的数$<$位置$j$的数的概率

发现每次操作只会修改$O(n)$个状态（就是包含$x,y$的）

例如$f[x][i]=(f[x][i]+f[y][i])/2$

总复杂度$O(n^2+nq)$

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e3 + 11;
const int mod = 1e9 + 7;
int f[N][N], n, q, a[N];
inline int A(int x, int y){
    return x + y - (x + y >= mod ? mod : 0);
}
inline int M(int x, int y){
    return 1LL * x * y % mod;
}
int main(){
    cin>>n>>q;
    for(int i = 1;i <= n; i++)cin>>a[i];
    for(int i = 1;i <= n; i++){
        for(int j = 1;j <= n; j++)f[i][j] = a[i] < a[j];
    }
    int inv2 = (mod + 1) / 2, mi = 1;
    for(int i = 1;i <= q; i++){
        mi = (mi << 1) % mod;
        int x, y;
        cin>>x>>y;
        f[x][y] = f[y][x] = M(inv2, A(f[x][y], f[y][x]));
        for(int j = 1;j <= n; j++){
            if(j == x || j == y)continue;
            f[x][j] = f[y][j] = M(inv2, A(f[x][j], f[y][j]));
            f[j][x] = f[j][y] = M(inv2, A(f[j][x], f[j][y]));
        }
    }
    int ans = 0;
    for(int i = 1;i <= n; i++){
        for(int j = i - 1;j >= 1; j--)ans = A(ans, f[i][j]);
    }
    ans = M(ans, mi);
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：lfxxx (赞：5)

先考虑计数转期望。

又因为你要算逆序对，所以考虑直接维护所有偏序关系。

定义 $f_{i,j}$ 表示 $a_i < a_j$ 的概率，那么对于每一次操作 $u,v$ 都有如下转移：

1. $f_{u,v} = f_{v,u} = \frac{f_{u,v} + f_{v,u}}{2}$。

2. $f_{u,i} = f_{v,i} = \frac{f_{u,i} + f_{v,i}}{2}$。

3. $f_{i,u} = f_{i,v} = \frac{f_{i,u} + f_{i,v}}{2}$。

不难发现每个都只有 $O(n)$ 此操作，预处理逆元即可做到 $O(nq)$。

最后不要忘了乘 $2^q$ 回到方案数。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 3e3+114;
const int mod = 1e9+7;
int f[maxn][maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a%mod;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*(a%mod)%mod;
    return res;
}
int a[maxn],n,m;
int inv;
//f[i][j] a[i] < a[j] 的概率
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    inv=qpow(2,mod-2);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) f[i][j]=(a[i]<a[j]);
    }   
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        for(int i=1;i<=n;i++){
            if(i!=u&&i!=v) f[u][i]=f[v][i]=(f[u][i]+f[v][i])%mod*inv%mod;
        }
        for(int i=1;i<=n;i++){
            if(i!=u&&i!=v) f[i][u]=f[i][v]=(f[i][u]+f[i][v])%mod*inv%mod;
        }
        f[u][v]=f[v][u]=(f[u][v]+f[v][u])%mod*inv%mod;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            ans=(ans+f[i][j])%mod;
        }
    }
    ans=ans*qpow(2,m)%mod;
    cout<<ans<<'\n';
    return 0;
}
```




---

## 作者：541forever (赞：3)

# AGC030D

感觉这种，将期望与将所有方案求和相互转换的 trick 很厉害啊（）。

首先，有个暴力的思路是设 $f_{i,j}$ 表示在当前状态下有多少种方案使得 $a_i>a_j$，转移时我们可以发现除了 $i,j$ 等于 $x$  或 $y$ 的情况，其他的答案都乘了 $2$，显然，每次暴力将其他数乘二的复杂度是不可接受的，但是，我们可以选择每次将 $i,j$ 等于 $x$ 或 $y$ 时的方案数除以二，最后再乘上 $2^q$，此时 $f_{i,j}$ 的实际意义是在每次有二分之一的概率下进行操作的情况下，$a_i>a_j$ 的概率。我们最后求的答案即为逆序对期望个数乘 $2^q$。这两种思路殊途同归。

转移可以注意到只有 $i,j$ 等于 $x$ 或 $y$ 时 dp 数组才会发生变化。

[Code](https://atcoder.jp/contests/agc030/submissions/44220666)

---

## 作者：Aw顿顿 (赞：3)

**核心思想：期望的线性性质。**

------

这道题和 [CF258D Little Elephant and Broken Sorting](https://www.luogu.com.cn/problem/CF258D) 的区别在于结果是否需要乘上 $2^q$ 以及答案求取过程中是否要求取模。此题的取模和除法可以用逆元实现。

由费马小定理可知除以二在模 $10^9+7$ 意义下相当于乘上 $2^{10^9+7}$。预处理结束后，令 $f(i,j)$ 表示 $i$ 比 $j$ 大的概率，则根据期望的线性性质得到：

$$f(i,x)=f(i,y)=\dfrac{f(i,x)+f(i,y)}{2}$$

$$f(x,i)=f(y,i)=\dfrac{f(x,i)+f(y,i)}{2}$$

由于每次等概率求取，因此对于 $f(x,y)$ 也要进行一次计算，因此答案为：

$$2^q\times\sum\limits_{i=1}^{n}\sum\limits_{j=i+1}^{n}f(i,j)$$

代码实现如下：


```cpp
#include<bits/stdc++.h>
#define N 3005
#define mod 1000000007
#define int long long
using namespace std;
int n,q,s,inv;
int a[N],f[N][N];
int ksm(int b,int p){
	int s=1;b%=mod;
	while(p){
		if(p&1)s=s*b%mod;
		b=b*b%mod;p>>=1;
	}return s%mod;
}signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		if(a[i]<a[j])f[i][j]=1;
	inv=ksm(2,mod-2);
	for(int i=1;i<=q;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		f[x][y]=f[y][x]=(f[x][y]+f[y][x])*inv%mod;
		for(int j=1;j<=n;j++){
			if(j==x||j==y)continue;
			f[x][j]=f[y][j]=(f[x][j]+f[y][j])*inv%mod;
			f[j][x]=f[j][y]=(f[j][x]+f[j][y])*inv%mod;
		}
	}for(int i=1;i<=n;i++)for(int j=1;j<i;j++)
		s=(s+f[i][j])%mod;
	cout<<s*ksm(2,q)%mod<<endl;
	return 0;
}
```

时间复杂度 $O(qn)$ 可以通过本题。

---

## 作者：Lyrella (赞：1)

# [AGC30 - D - Inversion Sum](https://atcoder.jp/contests/agc030/tasks/agc030_d) 2024.8.29

## 简要题意

有一个长度为 $n$ 的序列，现在有 $q$ 次操作，每次操作都可以交换两个数的位置，对于每次操作可以选择执行或不执行。对于所有的情况求出一共的逆序对数量。

## 题解

首先要知道一个技巧：在多种情况下计数可以转换成求概率再乘上情况数。

然后就可以将题意转换成求 $a_i>a_j,i<j$ 的概率和，于是就可以设计一个 dp $f_{i,j}$ 表示 $a_i>a_j,i<j$ 的概率。当一次操作交换 $x,y$ 时，对于所有的 $f_{x,i},f_{y,i},f_{i,x},f_{i,y}$ 都会改变。就拿 $f_{x,i}$ 举例，一次操作后它有 $\frac{1}{2}$ 的概率继承之前的状态，还有 $\frac{1}{2}$ 的概率变成 $f_{y,i}$ 的状态，所以转移就是两个状态相加除以二。对于每次操作都需要改变 $O(n)$ 的状态，时间复杂度 $O(nq)$。

## 代码

```cpp
int n, q, a[N];
ll f[N][N];

ll qmi(ll x, int y){
    ll res = 1;
    for(; y; y >>= 1, x = x * x % p)if(y & 1)res = res * x % p;
    return res;
}
const ll i2 = p + 1 >> 1;

ll add(ll x, ll y){
    x += y; return x >= p ? x - p : x;
}

signed main(){
    // fileio(fil);
    n = rd(), q = rd();
    for(int i = 1; i <= n; ++i)a[i] = rd();
    for(int i = 1; i <= n; ++i)for(int j = 1; j <= n; ++j)f[i][j] = a[i] > a[j];
    for(int i = 1; i <= q; ++i){
        int x = rd(), y = rd();
        for(int j = 1; j <= n; ++j)if(j ^ x and j ^ y)f[x][j] = f[y][j] = add(f[x][j], f[y][j]) * i2 % p, f[j][x] = f[j][y] = add(f[j][x], f[j][y]) * i2 % p;
        f[x][y] = f[y][x] = add(f[x][y], f[y][x]) * i2 % p;
    }
    ll s = qmi(2, q), res = 0;
    for(int i = 1; i < n; ++i)for(int j = i + 1; j <= n; ++j)res = add(res, f[i][j]);
    printf("%lld", res * s % p);
    return 0;
}
```

---

## 作者：RockyYue (赞：1)

统计所有方案中逆序对的个数之和，不妨对每对数分别考虑在多少种方案中为逆序对，或者计算操作后构成逆序对的概率，更为方便。

设 $f_{i,j}$ 为在当前处理的若干个操作后，$a_i>a_j$ 的概率。这里 $i$ 和 $j$ 仅代表操作后的下标。

对于一次操作 $(x,y)$：
- $f_{x,y}=f_{y,x}=\frac{f_{x,y}+f_{y,x}}{2}$。
- 对于 $1\le i\le n$ 且 $i\neq x,y$：
	- $f_{x,i}=f_{y,i}=\frac{f_{x,i}+f_{y,i}}{2}$。
    - $f_{i,x}=f_{i,y}=\frac{f_{i,x}+f_{i,y}}{2}$。

这样只针对 $x,y$ 这两个数进行更新，可以将每次的复杂度控制在 $O(n)$。
   
进行完 $q$ 次操作后，答案即为 $2^q\sum_{1\le i<j\le n}{f_{i,j}}$。

复杂度 $O(n^2)$，注意实现中除以 $2$ 写作乘其逆元。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3005, P = 1e9 + 7;
int a[N], f[N][N];
int qpow(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1) (res *= x) %= P;
		(x *= x) %= P, y >>= 1;
	}
	return res;
}
signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n, q; cin >> n >> q;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) f[i][j] = a[i] > a[j];
	}
	int inv2 = qpow(2, P - 2);
	for (int T = 1; T <= q; ++T) {
		int x, y; cin >> x >> y;
		f[x][y] = f[y][x] = (f[x][y] + f[y][x]) % P * inv2 % P;
		for (int i = 1; i <= n; ++i) {
			if (i == x || i == y) continue;
			f[x][i] = f[y][i] = (f[x][i] + f[y][i]) % P * inv2 % P;
			f[i][x] = f[i][y] = (f[i][x] + f[i][y]) % P * inv2 % P;
		}
	}
	int res = 0;
	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) (res += f[i][j]) %= P;
	}
	cout << res * qpow(2, q) % P << '\n';
	return 0;
}
```

---

## 作者：1saunoya (赞：1)

[你咋抄 cf 啊。。。](https://www.luogu.com.cn/blog/Isaunoya/solution-cf258d)


根据期望的线性性展开。

让 $f_{i,j}$ 变成 $i$ 比 $j$ 大的概率。(位置)


$f_{i,x} = f_{i,y} = \frac{f_{i,x} + f_{i,y}}{2}$。

$f_{x,i} = f_{y,i} = \frac{f_{x,i} + f_{y,i}}{2}$。


然后考虑交换 $x,y$，那么 $x$ 比 $y$ 大和 $y$ 比 $x$ 大的概率相同，所以 $f_{x,y} = f_{y,x} = 0.5$

要求的是 $\sum_{i = 1}^{n} \sum_{j=i+1}^{n} f_{i,j} \times 2^q$。

然后完了。

```cpp
/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rp(i,y) for(int i=1;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define pr(i,y) for(int i=y;i>=1;i--)
#define sz(v) (int)v.size()
using namespace std;
const int SIZE=1<<26;
char gc[SIZE],*pgc=gc;
char pc[SIZE],*ppc=pc;
clock_t clk=clock();
struct flusher{
	flusher(){
#ifdef WHX_TXDY
		freopen("fuck.in","r",stdin);
#endif
		fread(gc,true,SIZE,stdin);
	}
	~flusher(){
		fwrite(pc,true,ppc-pc,stdout);
#ifdef WHX_TXDY
		std::cerr<<"TIME:"<<(clock()-clk)/1000.<<"s\n";
#endif
	}
}Flusher;
int _Neg=0;
template<class T>
void rd(T&x){
	x=_Neg=0;
	while(!isdigit(*pgc)){
		if((*pgc++)=='-'){
			_Neg=1;
		}
	}
	while(isdigit(*pgc)){
		x=x*10+*pgc++-48;
	}
	if(_Neg){
		x=-x;
	}
}
int _Stk[233],_Top=0;
template<class T>
void pt(T x,char c='\n'){
	if(x<0){
		*ppc++='-';
		x=-x;
	}
	do{
		_Stk[++_Top]=x%10;
		x/=10;
	}while(x);
	while(_Top){
		*ppc++=_Stk[_Top--]+48;
	}
	*ppc++=c;
}
void pts(const string&str){
	int len=sz(str);
	rep(i,0,len-1){
		*ppc++=str[i];
	}
	*ppc++='\n';
}
template<class T>
void cmax(T&x,const T&y){
	x=(x>y)?x:y;
}
template<class T>
void cmin(T&x,const T&y){
	x=(x<y)?x:y;
}

const int P = 1e9 + 7;
const int inv2 = P + 1 >> 1;
int add(int x, int y) {
	return (x + y < P) ? (x + y) : (x + y - P);
}
int mul(int x, int y) {
	return 1ll * x * y % P;
}

const int N = 3005;
int f[N][N];
int n, q;
int a[N];

int main() {
	rd(n); rd(q);
	rp(i,n) rd(a[i]);
	rp(i,n) {
		rp(j,n) {
			f[i][j] = a[i] > a[j];
		}
	}
	rp(_,q){
		int x, y;
		rd(x);
		rd(y);
		rep(j,1,n){
			if (j == x || j == y) {
				continue;
			}
			f[j][x] = f[j][y] = mul(add(f[j][x], f[j][y]), inv2);
			f[x][j] = f[y][j] = mul(add(f[x][j], f[y][j]), inv2);
		}
		f[x][y] = f[y][x] = mul(add(f[x][y], f[y][x]), inv2);
	}
	int ans = 0;
	rp(i,n) {
		rep(j,i+1,n){
			ans = add(ans, f[i][j]);
		}
	}
	while(q--){ans=add(ans,ans);}
	pt(ans);
	return 0;
}

---

## 作者：yyxmy (赞：1)

一看$n$比较小, 那应该是对每一对$A_i, A_j$ 考虑有多少种情况大的会在前面。朴素$dp$为$fi,j,x,y$ 表示$i,j$ 对， $i$在x， j在$y$的方案数， 我们发现每一层转移的状态数只有$O(n)$个，那么复杂度为$O(n^4)$，  与题目要求的还有差距。考虑如何优化， 其实我们不用知道每一对$i, j$具体在那个位置， 只需要知道，$i，j$这两个位置$A_i$比$A_j$大的情况有多少种就好, 于是每一次交换转移状态只涉及到$O(n)$个， 对于不需要的状态打个标记*2就好， 复杂度$O(n^2 + nq)$.

```cpp
#include<bits/stdc++.h>
#define reg register
#define mod 1000000007
using namespace std;
inline int  read() {
    reg int s = 0, t = 0; reg char ch = getchar();
    while(ch > '9' || ch < '0') t |= ch == '-', ch = getchar();
    while(ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
    return t ? -s : s;
}
int ksm(int u, int v){
	int s = 1;
	for(int i = v; i; i >>= 1){
		if(i & 1) s = 1ll * s * u % mod;
		u = 1ll * u * u % mod;
	}
	return s;
}
int n, m, f[5001][5001], inv2, ans, a[5001], g[5001][5001];
int main()
{
	n = read(); m = read(); inv2 = 500000004;
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) f[i][j] = (a[i] > a[j]);
	
	for(int i = 1; i <= m; i++){
		int x = read(), y = read();
		for(int j = 1; j <= n; j++) {
			if(j == x || j == y) continue;
			g[x][j] = 1ll * (f[x][j] + f[y][j]) % mod * inv2 % mod;		
			g[j][x] = 1ll * (f[j][x] + f[j][y]) % mod * inv2 % mod;
			g[y][j] = 1ll * (f[x][j] + f[y][j]) % mod * inv2 % mod;
			g[j][y] = 1ll * (f[j][y] + f[j][x]) % mod * inv2 % mod;
		}
		for(int j = 1; j <= n; j++) {
			if(j == x || j == y) continue;
			f[x][j] = g[x][j]; f[j][x] = g[j][x];
			f[y][j] = g[y][j]; f[j][y] = g[j][y];
		}
		f[x][y] = 1ll * (f[x][y] + f[y][x]) % mod * inv2 % mod; f[y][x] = f[x][y];
	
	}
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			ans = (ans + f[i][j]) % mod;
	ans = 1ll * ans * ksm(2, m) % mod; cout << ans << endl;
	return 0;
}
```


---

## 作者：MoonCake2011 (赞：0)

首先，想到 dp 但做不出来。

~~看题解~~想到可以计数转期望再乘 $2^q$。

于是设 $dp_{i,j}$ 为 $(i,j)$ 所产生的答案贡献期望。

最开始，如果 $a_i<a_j$，$dp_{i,j}=1$，否则等于 $0$。

其他就是枚举交换对一些相关点对的贡献即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define int long long
int n,q,a[3010],dp[3010][3010];
inline int power(int x,int y){
	if(y==0) return 1;
	int tot=power(x,y>>1);
	if(y&1) return tot*tot%mod*x%mod;
	else return tot*tot%mod;
}
signed main() {
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	int inv=power(2,mod-2);//逆元 
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dp[i][j]=a[i]<a[j];
	for(int i=1;i<=q;i++){
		int u,v;
		cin>>u>>v;
		for(int i=1;i<=n;i++) if(i!=u && i!=v) dp[u][i]=dp[v][i]=(dp[u][i]+dp[v][i])*inv%mod,dp[i][u]=dp[i][v]=(dp[i][u]+dp[i][v])*inv%mod;//更新对其他点的贡献 
		dp[u][v]=dp[v][u]=(dp[u][v]+dp[v][u])*inv%mod;//对双方的贡献 
	}
	int ans=0;
	for(int i=1;i<=n;i++) for(int j=1;j<i;j++) ans=(ans+dp[i][j])%mod;//最后是贡献之和
	cout<<ans*power(2,q)%mod;//乘回来
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

这题相对特别一点的地方就是把求贡献转化成了求期望。

其实，点到这里就已经差不多了。我们将每次操作的执行概率设为 $\frac{1}{2}$，最后再将符合要求的状态的期望乘上 $2^m$，求一下和就做完了。

初始状态：$dp_{i,j}=[a_i>a_j]$。

状态转移：

$dp_{x,y}=dp_{y,x}=(dp_{x,y}+dp_{y,x})/2$；

$dp_{j,l}=dp_{j,r}=(dp_{j,l}+dp_{j,r})/2$；

$dp_{l,j}=dp_{r,j}=(dp_{l,j}+dp_{r,j})/2$；

其实说白了就是这两个数一换就把和他们相关的概率给摇匀了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int mod = 1e9 + 7;
int n, m, a[3005], dp[3005][3005], ny, ti, ans;
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m; ny = mod + 1 >> 1; ti = 1;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			dp[i][j] = (a[i] > a[j]);
	for (int i = 1, l, r; i <= m; ++i) {
		cin >> l >> r; ti = ti * 2 % mod;
		dp[l][r] = dp[r][l] = (dp[l][r] + dp[r][l]) * ny % mod;
		for (int j = 1; j <= n; ++j)
			if (j != l && j != r)
				dp[j][l] = dp[j][r] = (dp[j][l] + dp[j][r]) * ny % mod,
				dp[l][j] = dp[r][j] = (dp[l][j] + dp[r][j]) * ny % mod;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
			ans = (ans + dp[i][j] * ti) % mod;
	cout << ans << endl;
	return 0;
}
//私は猫です
```

---

## 作者：Purslane (赞：0)

# Solution

高二赛季的第一篇题解！

考虑所有的 $p_i < p_j$ 的数对 $(i,j)$，我们维护这样的 $(i,j)$ 出现的期望次数。（其实不需要求期望，但是这样会更加容易实现）

考虑操作 $(u,v)$，只会对 $O(n)$ 对 $(i,j)$ 产生影响。因此直接暴力修改即可。复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10,MOD=1e9+7,_2=(MOD+1)/2;
int n,m,p[MAXN],f[MAXN][MAXN],g[MAXN][MAXN]; 
int t(int id,int u,int v) {
	if(id==u) return v;
	if(id==v) return u;
	return id;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>p[i];
	ffor(i,1,n) ffor(j,1,n) if(p[i]<p[j]) f[i][j]=1;
	ffor(s,1,m) {
		int u,v;
		cin>>u>>v;
		ffor(i,u,u) ffor(j,1,n) g[i][j]=(f[i][j]+f[t(i,u,v)][t(j,u,v)])%MOD*_2%MOD;	
		ffor(i,v,v) ffor(j,1,n) g[i][j]=(f[i][j]+f[t(i,u,v)][t(j,u,v)])%MOD*_2%MOD;	
		ffor(i,1,n) ffor(j,u,u) g[i][j]=(f[i][j]+f[t(i,u,v)][t(j,u,v)])%MOD*_2%MOD;	
		ffor(i,1,n) ffor(j,v,v) g[i][j]=(f[i][j]+f[t(i,u,v)][t(j,u,v)])%MOD*_2%MOD;	
		ffor(i,u,u) ffor(j,1,n) f[i][j]=g[i][j];	
		ffor(i,v,v) ffor(j,1,n) f[i][j]=g[i][j];	
		ffor(i,1,n) ffor(j,u,u) f[i][j]=g[i][j];	
		ffor(i,1,n) ffor(j,v,v) f[i][j]=g[i][j];	
	}
	int ans=0;
	ffor(i,1,n) ffor(j,1,i-1) ans=(ans+f[i][j])%MOD;
	ffor(i,1,m) ans=ans*2%MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

由于逆序对的贡献是仅由两个位置产生的，所以可以拆分所有可能的两个位置组合，对每个组合求出形成逆序对的方案数，最后加和即可。

考虑动规解决。每次交换两个位置时更新方案数，我们发现仅仅与交换位置有关的位置方案数需要计算，其他不相关位置直接乘二就行。那么使用懒标记维护这个二的幂，每次算方案时更新。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3010, mod = 1e9 + 7;
int n, q, a[N], tag[N][N]; long long f[N][N], ans, pw[N];
inline void refresh(int x, int y, int col)
{
	f[x][y] = f[x][y] * pw[col - tag[x][y]] % mod;
	tag[x][y] = col;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	pw[0] = 1; for(int i = 1; i <= q; ++i) pw[i] = pw[i - 1] * 2 % mod;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			f[i][j] = (a[i] > a[j]);
	for(int i = 1; i <= q; ++i)
	{
		int x, y; cin >> x >> y;
		for(int j = 1; j <= n; ++j)
		{
			if(j == x || j == y) continue;
			
			refresh(j, x, i - 1), refresh(j, y, i - 1);
			tag[j][x] = tag[j][y] = i;
			long long n1 = f[j][x], n2 = f[j][y];
			f[j][x] = f[j][y] = (n1 + n2) % mod;
			
			refresh(x, j, i - 1), refresh(y, j, i - 1);
			tag[x][j] = tag[y][j] = i;
			n1 = f[x][j], n2 = f[y][j];
			f[x][j] = f[y][j] = (n1 + n2) % mod;
		}
		refresh(x, y, i - 1), refresh(y, x, i - 1);
		tag[x][y] = tag[y][x] = i;
		f[x][y] = f[y][x] = (f[x][y] + f[y][x]) % mod;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j)
			refresh(i, j, q), ans = (ans + f[i][j]) % mod;
	cout << ans << '\n';
	return 0;
}

/*

*/
```

---

## 作者：win114514 (赞：0)

很好的一道题。

### 思路

由于 $n$ 较小。

我们可以枚举位置 $(i,j)$ 统计逆序对。

由于每次交换 $(x,y)$ 只会影响与 $x,y$ 有关的逆序对。

所以我们可以在修改的时候暴力修改。

但是这样有一个问题。

就是我们统计总和的时候，其他项应该需要乘二。

我们可能可以想到一些技巧性的方法比如整体打标记，给特殊项除二。

考虑我们实际统计的是什么。

是概率！

我们可以统计每一个逆序对出现的概率。

在最后面给答案乘上 $2^m$ 就是期望。

这也是期望与概率的互转。

如何 dp。

设 $f1_{i,j}$ 表示 $a_i<a_j$ 的概率，$f2_{i,j}$ 表示 $a_i>a_j$ 的概率。

转移比较简单，读者可以自行思考。

时间复杂度：$O(n(n+q))$。

这道题其实有一个概率版本，CF258D。

### Code

```cpp
/*
  ! Though life is hard, I want it to be boiling.
  ! Created: 2024/04/10 09:10:38
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
// #define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

typedef long long i64;
typedef pair<int, int> PII;

bool ST;
const int N = 3010;
const int mod = 1e9 + 7;
const int inv = 500000004;

i64 n, m, a[N], f1[N][N], f2[N][N];

signed main() {
  JYFILE19();
  cin >> n >> m;
  fro(i, 1, n) cin >> a[i];
  fro(i, 1, n) fro(j, i + 1, n) f1[i][j] = (a[i] < a[j]);
  fro(i, 1, n) fro(j, i + 1, n) f2[i][j] = (a[i] > a[j]);
  fro(i, 1, m) {
    int l, r;
    cin >> l >> r;
    if (l > r) swap(l, r);
    vector<int> fl1(n + 1);
    vector<int> fr1(n + 1);
    vector<int> fl2(n + 1);
    vector<int> fr2(n + 1);
    fro(j, 1, n) {
      if (j == l) continue;
      if (j < l) {
        fl1[j] = f1[j][r], fl2[j] = f2[j][r];
      } else if (j < r) {
        fl1[j] = f2[j][r], fl2[j] = f1[j][r];
      } else if (j > r) {
        fl1[j] = f1[r][j], fl2[j] = f2[r][j];
      }
    }
    fro(j, 1, n) {
      if (j == r) continue;
      if (j > r) {
        fr1[j] = f1[l][j], fr2[j] = f2[l][j];
      } else if (j > l) {
        fr1[j] = f2[l][j], fr2[j] = f1[l][j];
      } else if (j < l) {
        fr1[j] = f1[j][l], fr2[j] = f2[j][l];
      }
    }
    fl1[r] = f2[l][r], fl2[r] = f1[l][r];
    fro(j, 1, n) {
      if (j < r && j != l) f1[j][r] = (fr1[j] + f1[j][r]) % mod, f2[j][r] = (fr2[j] + f2[j][r]) % mod;
      if (j > r) f1[r][j] = (fr1[j] + f1[r][j]) % mod, f2[r][j] = (fr2[j] + f2[r][j]) % mod;
      if (j < l) f1[j][l] = (fl1[j] + f1[j][l]) % mod, f2[j][l] = (fl2[j] + f2[j][l]) % mod;
      if (j > l && j != r) f1[l][j] = (fl1[j] + f1[l][j]) % mod, f2[l][j] = (fl2[j] + f2[l][j]) % mod;
    }
    f1[l][r] = (fl1[r] + f1[l][r]) % mod;
    f2[l][r] = (fl2[r] + f2[l][r]) % mod;
  }
  int ans = 0;
  fro(i, 1, n) fro(j, i + 1, n) (ans += f2[i][j]) %= mod;
  cout << ans << "\n";
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen("", "r", stdin);
  // freopen("", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED-&ST)/1048576.), LIM = 1024;
  cerr << "MEMORY: " << MIB << endl, assert(MIB<=LIM);
}
```

---

## 作者：elbissoPtImaerD (赞：0)

考虑**计数转期望**。

逆序对不是一个很好全局统计的东西，好在我们可以枚举它，将其转化为局部的统计。

设 $f_{i,j}$ 表示 $a_i > a_j$ 的概率。

每次对于点对 $(u,v)$，有转移：


$$\forall x \neq u, x \neq v, F(f_{u,x},f_{v,x})$$
$$\forall x \neq u, x \neq v, F(f_{x,u},f_{x,v})$$
$$F(f_{u,v},f_{v,u})$$

其中 $F(x,y)$ 表示将 $x,y$ 同时赋值为他们的平均数。

暴力转移即可，复杂度 $O(n(n+q))$。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/agc030/submissions/50410902)

---

## 作者：xht (赞：0)

## [Inversion Sum](https://atcoder.jp/contests/agc030/tasks/agc030_d)

### 题意

- 给定一个序列 $a_{1\dots n}$。
- 有 $q$ 次操作，每次操作会交换两个位置上的数，你都可以选择是否执行。
- 求所有情况下最终序列的逆序对数之和。
- $n,q \le 3 \times 10^3$，答案对 $10^9+7$ 取模。

### 题解

令 $f_{i,j}$ 表示 $a_i > a_j$ 的概率，这样每次转移只会修改 $\mathcal O(n)$ 对 $(i,j)$，时间复杂度 $\mathcal O(n(n+q))$。

### 代码

```cpp
const int N = 3e3 + 7;
const modint v2 = (modint)1 / 2;
int n, q, a[N];
modint f[N][N], ans;

inline void work(modint &x, modint &y) {
	x = y = (x + y) * v2;
}

int main() {
	rd(n, q), rda(a, n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			f[i][j] = a[i] > a[j];
	for (int i = 1, x, y; i <= q; i++) {
		rd(x, y), work(f[x][y], f[y][x]);
		for (int j = 1; j <= n; j++)
			if (j != x && j != y)
				work(f[j][x], f[j][y]), work(f[x][j], f[y][j]);
	}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			ans += f[i][j];
	print(ans * ((modint)2 ^ q));
	return 0;
}
```

---

## 作者：Meteor_ (赞：0)

# AT_agc030_d [AGC030D] Inversion Sum 题解

## 题目大意

给你一个长度为 $n$ 的数列，然后给你 $q$ 次交换操作，你每次可以选择操作或者不操作，问所有情况下逆序对的总和。（$n, q \le 3000$）

## 分析

很容易想到 $dp$，但是发现不好直接算方案。所以我们用一个小技巧，**将求方案数转化为求期望**，然后求出最终答案。那么就来考虑怎么设计期望 $dp$。

## 题解

我们先来想怎么求某一情况下期望的逆序对数。

第一反应想到计数，用 $dp_{i, j}$ 来代表数对 $(i, j)$ 对最终答案作出的贡献。但是在写转移时发现有一点麻烦，于是浅改一下思路，用 $dp_{i, j}$ 来代表 位置 $i$ 上的数比位置 $j$ 上的数大的概率。

我们很容易得到，某一情况下期望的逆序对数就是 $\displaystyle \sum_{i = 1}^{n} \sum_{j = i + 1}^{n} dp_{i, j}$。

$dp$ 的初始值比较好想，就是 $O(n^2)$ 跑一遍，对于每一个 $i$ 位置上的数大于 $j$ 位置上的数的情况，把 $dp_{i, j}$ 赋成 $1$ 即可。接下来我们考虑操作一次会使 $dp$ 怎样变化。假设我们这一次操作所交换的两个位置是 $x$ 和 $y$，$x$ 位置上的数为 $a_x$，$y$ 位置上的数为 $a_y$。

首先列一个非常显然的式子：

$$
\begin{aligned}

dp_{x, t} &= 1 - dp_{t, x}\\

dp_{x, t} &= 1 - dp_{t, x}

\end{aligned}
$$

有了这个式子，我们就能容易地想到 $dp_{x, y}$ 和 $dp_{y, x}$ 的转化。首先我们想到，$a_x$ 和 $a_y$ 的关系有两种可能，相等或不相等。如果不相等，交换 $x$ 和 $y$ 以后，$dp_{x, y}$ 和 $dp_{y, x}$ 都会被直接赋值成 $0.5$，这很好理解。如果相等，那么两者都是 $0$。又因为上面的那两个式子，所以我们可以直接简写成 $\displaystyle dp_{x, y} = dp_{y, x} = \frac{dp_{x, y} + dp_{y, x}}{2}$。

而对于其他的位置上的数，我们再设一个位置 $t(1 \le t \le n \land t \neq x \land t \neq y)$（$\land$ 是“且”的意思，$\lor$ 是“或”的意思），其位置上的数为 $a_t$，那么一定有：

$$
\begin{aligned}

dp_{x, t} &= 1 - dp_{t, x}\\

dp_{x, t} &= 1 - dp_{t, x}\\

dp_{t, x} = dp_{t, y} &= \frac{dp_{t, x} + dp_{t, y}}{2}\\

dp_{x, t} = dp_{y, t} &= \frac{dp_{x, t} + dp_{y, t}}{2}

\end{aligned}
$$

前两个式子显然成立（但是好像这个题没用上），我们考虑怎么去证明后两个式子。其实也很好证，因为如果两者换位成功，则 $dp_{t, x} = dp_{t, y}$，否则不变。而我们又知道，成功的几率为 $0.5$，那么 $\displaystyle dp_{t, x} = \frac{dp_{t, x} + dp_{t, y}}{2}$ 显然成立。其他的同理。

既然有了这些结论，那么我们就可以对于每一次操作，枚举一遍 $t$，最终求得某一情况下期望的逆序对数。

得到这个我们就能轻松地算出最终答案。因为一共有 $2^q$ 种情况，所以我们用刚刚得到的再乘上 $2^q$ 就是最终答案。

需要注意的是，计算过程中的除法要写成逆元。

时间复杂度： $O(n^2 + qn)$。

## 代码

```cpp
//https://www.luogu.com.cn/problem/AT_agc030_d AT_agc030_d [AGC030D] Inversion Sum
#include <bits/stdc++.h>
#define M 3005
#define int long long
#define mod 1000000007

using namespace std;

inline int read() {
    int x = 0, s = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')
            s = -s;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * s;
}

void write(int x) {
    if(x < 0)  {
        x = ~(x - 1);
        putchar('-');
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}

int n, q, a[M], dp[M][M], ans;
const int inv2 = 500000004;

inline int  quick_pow(int base, int P) {
    int ji = 1;
    while(P) {
        if(P & 1)
            ji = (ji * base) % mod;
        P >>= 1;
        base = (base * base) % mod;
    }
    return ji;
}

signed main() {
    n = read();
    q = read();
    for(int i = 1; i <= n; ++ i)
        a[i] = read();
    for(int i = 1; i <= n; ++ i)
        for(int j = 1; j <= n; ++ j)
            if(a[i] > a[j])
                dp[i][j] = 1;
    for(int i = 1; i <= q; ++ i) {
        int x = read(), y = read();
        if(x == y)
            continue;
        for(int j = 1; j <= n; ++ j) {
            if(j != x && j != y) {
                dp[y][j] = dp[x][j] = (dp[x][j] + dp[y][j]) % mod * inv2 % mod;
                dp[j][y] = dp[j][x] = (dp[j][x] + dp[j][y]) % mod * inv2 % mod;
            }
        }
        dp[x][y] = dp[y][x] = (dp[x][y] + dp[y][x]) % mod * inv2 % mod;
    }
    for(int i = 1; i <= n; ++ i)
        for(int j = i + 1; j <= n; ++ j)
            ans = (ans + dp[i][j]) % mod;
    ans = ans * quick_pow(2, q) % mod;
    write(ans);
}
```

## 后记

[~~放在最后的双倍经验~~](https://www.luogu.com.cn/problem/CF258D)

---

## 作者：Tastoya (赞：0)

### 题目大意
一个长度为 $n$ 的数列，然后给你 $q$ 个交换或不交换操作，你可以选择操作或者不操作，问所有情况下逆序对的总和。

答案需要对 $10 ^ 9 + 7$ 取模。

（$n\leq 3000$，$q\leq 3000$）。
### 思路
[更好的阅读体验](https://www.cnblogs.com/baijian0212/p/AT_agc030_d.html)

这道题非常巧妙。

我们先考虑转化题意，求逆序对数量的期望。

记 $dp_{i,j}$ 表示 $a_i>a_j$ 的概率，初始值很好设，直接根据初始给出的排列情况进行赋值。

- 若 $a_i>a_j$，则 $dp_{i,j}=1$；
- 若 $a_i < a_j$，则 $dp_{j,i}=1$。

考虑如果我们交换 $x$ 和 $y$ 的位置，会产生什么影响。对于 $\forall i,j \in \left[ 1,n \right]$，其中 $i,j$ 没有与 $x$ 或 $y$ 的情况，不会影响 $dp_{i,j}$ 的值。

记 $f_{i,j}$ 表示未更改前的 $dp$ 数组，考虑有 $x,y$ 的情况，显然有

$$dp_{i,x}=\dfrac{f_{i,x}+f_{i,y}}{2}$$
$$dp_{i,y}=\dfrac{f_{i,x}+f_{i,y}}{2}$$
$$dp_{x,i}=\dfrac{f_{x,i}+f_{y,i}}{2}$$
$$dp_{y,i}=\dfrac{f_{x,i}+f_{y,i}}{2}$$
这道题求的是逆序对的总和，所以答案应当是所有情况数与逆序对数量的期望的乘积。

所以最后答案为
$$2^m \times \sum^{n}_{i=1}\sum^{n}_{j=i+1}dp_{i,j}$$
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int Mod = 1e9 + 7;
const int N = 3050;

int n,m;

int a[N];

long long Pow(long long a ,long long b) {
    long long res = 1 ;
    long long base = a;
    while(b) {
   	    if(b & 1)
   		    res = res * base % Mod;
   	    base = base * base % Mod;
   	    b >>= 1;
   }
   return res;
}

long long Inv(int x) {
    return Pow(x,Mod - 2) % Mod;
}

long long dp[N][N],ans = 0;

signed main() {
    cin >> n >> m;
    for(int i = 1;i <= n; i++) 
        cin >> a[i];
    
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= n; j++) {
            if(a[i] > a[j])
                dp[i][j] = 1;
        }
    }

    for(int i = 1,x,y;i <= m; i++) {
        cin >> x >> y;

        for(int i = 1;i <= n; i++) {
            if(i == x || i == y)
                continue;
            
            dp[i][x] = dp[i][y] = (dp[i][x] + dp[i][y]) * Inv(2) % Mod;
            dp[x][i] = dp[y][i] = (dp[x][i] + dp[y][i]) * Inv(2) % Mod;
        }

        dp[x][y] = dp[y][x] = (dp[x][y] + dp[y][x]) * Inv(2) % Mod;
    }

    for(int i = 1;i <= n; i++) 
        for(int j = i + 1;j <= n; j++) 
            ans = (ans + dp[i][j]) % Mod;

    ans = 1ll * ans * Pow(2,m) % Mod;

    cout << ans << "\n";
    return 0;
}
```

---

## 作者：User_Authorized (赞：0)

## 题意

给定一个长度为 $n$ 的排列 $a$ 和 $m$ 个形如 $\left(x,y\right)$ 的操作，每次操作可以选择是否交换 $a_x, a_y$，求最终所有形成的排列的逆序对总数。

（$1 \le n,m \le 3000$）。

## 题解

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-AGC030D.html)**

考虑转化题意，考虑求出最终总的期望逆序对数，即 [CF258D](https://codeforces.com/problemset/problem/258/D)。

转化答案

$$\text{Ans} = \sum\limits_{i = 1}^{n} \sum\limits_{j = i + 1}^{n} \operatorname{P}\left(a_i > a_j\right)$$

考虑设 $f_{i, j} = \operatorname{P}\left(a_i > a_j\right)$。初始值很显然

$$f_{i, j} = \left[a_i > a_j\right]$$

考虑交换操作 $\left(x, y\right)$ 对该数组值的影响，设 $g$ 为更改操作前 $f$ 的拷贝，对于 $\forall t \neq x \land t \neq y$，有 

$$\begin{aligned}
f_{t, x} &= \dfrac{1}{2} g_{t, x} + \dfrac{1}{2} g_{t, y} \\
f_{t, y} &= \dfrac{1}{2} g_{t, x} + \dfrac{1}{2} g_{t, y} \\
f_{x, t} &= \dfrac{1}{2} g_{x, t} + \dfrac{1}{2} g_{y, t} \\
f_{y, t} &= \dfrac{1}{2} g_{x, t} + \dfrac{1}{2} g_{y, t} \\
\end{aligned}$$

因为原数组为排列，即元素互不相同，那么对于 $x, y$，有

$$\begin{aligned}
f_{x, y} &= 0.5 \\
f_{y, x} &= 0.5 \\
\end{aligned}$$

所有操作处理完成后直接乘上所有可能的排列数即 $2^m$ 即可得到本题答案。

每次操作 $\mathcal{O}(n)$ 维护即可，总复杂度 $\mathcal{O}(n^2 + nm)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 1e9 + 7;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

constexpr valueType Inv2 = 500000004;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    ValueVector source(N + 1);
    ValueMatrix F(N + 1, ValueVector(N + 1, 0));

    for (valueType i = 1; i <= N; ++i)
        std::cin >> source[i];

    for (valueType i = 1; i <= N; ++i)
        for (valueType j = 1; j <= N; ++j)
            if (source[i] > source[j])
                F[i][j] = 1;

    for (valueType t = 0; t < M; ++t) {
        valueType a, b;

        std::cin >> a >> b;

        for (valueType i = 1; i <= N; ++i) {
            if (i == a || i == b)
                continue;

            F[i][a] = F[i][b] = mul(sum(F[i][a], F[i][b]), Inv2);
            F[a][i] = F[b][i] = mul(sum(F[a][i], F[b][i]), Inv2);
        }

        F[a][b] = F[b][a] = mul(sum(F[a][b], F[b][a]), Inv2);
    }

    valueType ans = 0;

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = i + 1; j <= N; ++j) {
            Inc(ans, F[i][j]);
        }
    }


    Mul(ans, pow(2, M));

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：Butterfly_qwq (赞：0)

$dp_{k,i,j}$ 表示第 $k$ 操作完成之后，$A_i\le A_j$ 的概率。

交换和不交换概率都是 $\frac{1}{2}$，所以可得在第 $k$ 次交换，交换  $A_x,A_y$  后：

$dp_{k,x,y}=dp_{k,y,x}=(dp_{k-1,x,y}+dp_{k-1,y,x})\div 2$。

$dp_{k,x,i}=dp_{k,y,i}=(dp_{k-1,x,i}+dp_{k-1,y,i})\div 2$。

$dp_{k,i,y}=dp_{k,i,x}=(dp_{k-1,i,y}+dp_{k-1,i,x})\div 2$。

其中 $1\le i\le n,i\not =x,i\not =y$。

我们可以注意到，除以 $2$ 精度会爆炸，我们可以考虑如何处理这个问题。

前置芝士：有理数取模。

设有理数 $t=\frac{p}{q}$，则 $t\equiv r (\!\!\!\!\mod m)\iff p\equiv qr(\!\!\!\!\mod m)$

前置芝士：逆元。

设 $pq\equiv 1(\!\!\!\!\mod m)$，则 $q$ 称作 $p$ 在模 $m$ 意义下的逆元。

注意，只有 $\gcd(p,m) = 1$ 的时候 $p$ 在模 $m$ 意义下才有逆元。

把 $q$ 记作 $p^{-1}(\!\!\!\!\mod m)$。

我们可以发现这个逆元 $q$ 就是 $\frac{1}{p}\!\!\mod m$（虽然看似废话，但在后面很有用）。

那么除以 $2$ 就相当于乘以 $2^{-1} (\!\!\!\!\mod 10^9+7)$

$2$ 正好和 $10^9+7$ 互质。

由费马小定理，$10^9+7$ 是质数得到：

$2^{10^9+6}\equiv 1(\!\!\!\!\mod 10^9+7)$。

即为 $2\times 2^{10^9+5}\equiv 1(\!\!\!\!\mod 10^9+7)$。

所以 $2$ 在模 $10^9+7$ 意义上的逆元是 $2^{10^9+5} \!\!\mod 10^9+7$。

考虑怎么求右式。

$2^{10^9+6}\equiv 1 \equiv 10^9+8(\!\!\!\!\mod 10^9+7)$。

$2^{10^9+5}=\frac{2^{10^9+6}}{2}\equiv \frac{10^9+8}{2}=5\times10^8+4(\!\!\!\!\mod 1e9+7)$。

又有 $5\times 10^8+4<10^9+7$，于是 $2^{-1}(\!\!\!\!\mod 10^9+7)=5\times 10^8+4$。

将除以 $2$ 变为乘以 $5\times 10^8+4$ 即可。

还有一个问题：空间复杂度是 $O(kn^2)$ 的，会 MLE。

我们只需要滚动数组优化就可以把空间复杂度变成 $O(n^2)$。

一切问题都解决了。

献上本人拙码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7,inv=5e8+4;
int a[3420],dp[3420][3420];
signed main()
{
	int n,q,ans=0;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i]<a[j])dp[i][j]=1;
	for(int i=1;i<=q;i++)
	{
		int x,y;
		cin>>x>>y;
		dp[x][y]=dp[y][x]=(dp[x][y]+dp[y][x])*inv%mod;
		for(int i=1;i<=n;i++)
		{
			if(i==x||i==y)continue;
			dp[x][i]=dp[y][i]=(dp[x][i]+dp[y][i])*inv%mod;
         dp[i][x]=dp[i][y]=(dp[i][x]+dp[i][y])*inv%mod;
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)ans=(ans+dp[i][j])%mod;
	for(int i=1;i<=q;i++)ans=ans*2%mod;
	ans=(ans+mod)%mod;
	cout<<ans;
	return 0;
}
```


---

## 作者：ZigZagKmp (赞：0)

本文同步于我的 [cnblog](https://www.cnblogs.com/ZigZagKmp/p/14380052.html)

## 题意简述
给定一个长度为 $n$ 序列和 $m$ 次操作，每次操作交换一对位置上的元素。

现在每一个操作可以做也可以不做，求所有操作方案得到的最终序列的逆序对个数和。

$n,m\le 3000$。

## 算法分析
直接做没有头绪，考虑期望化。

期望有一个很重要的**线性性质**，可以将**问题独立**。我们考虑每一对逆序对的单元是一对数，因此我们需要维护所有二元组 $\left(x,y\right)$ 满足 $a_x<a_y$ 的概率。

这样对于一次交换操作的做或不做，只会影响到**与当前操作相关**的二元组，这些二元组要么包含第一个数，要么包含第二个数，总量为 $O(n)$ ，可以接受。

注意最后将概率和乘上 $2^m$ 。

总时间复杂度为 $O(n^2+nm)$ 。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 3005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
int a[maxn];
int dp[maxn][maxn];
int ksm(int b,int p){int ret=1;while(p){if(p&1)ret=1ll*ret*b%mod;b=1ll*b*b%mod;p>>=1;}return ret;}
signed main(){
	read(n);read(m);
	for(int i=1;i<=n;++i)read(a[i]);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			dp[i][j]=(a[i]<a[j]);
		}
	}
	for(int i=1,x,y;i<=m;++i){
		read(x);read(y);
		dp[x][y]=dp[y][x]=1ll*ksm(2,mod-2)*(dp[x][y]+dp[y][x])%mod;//两者交换，等概率出现自身与对方的情况
		for(int j=1;j<=n;++j){
			if(j!=x&&j!=y){//下面两种同理
				dp[x][j]=dp[y][j]=1ll*ksm(2,mod-2)*(dp[x][j]+dp[y][j])%mod;
				dp[j][x]=dp[j][y]=1ll*ksm(2,mod-2)*(dp[j][x]+dp[j][y])%mod;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<i;++j){
			ans=(ans+dp[i][j])%mod;
		}
	}
	ans=1ll*ans*ksm(2,m)%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：RainsAFO (赞：0)

我们不妨把它当做期望来做。

根据期望的线性性，对每对$(i,j)$计算贡献。

记$f_{i,j}$为$(i,j)$产生贡献的概率。

那么每次修改 $(x,y)$ 只会对$(i,j)$至少有一个为 $x$ 或 $y$ 的数对产生影响，转移平凡，最后乘上一个 $2^q$ 得到答案。


code:

```cpp
#include <cstdio>
#include <iostream>

#define int long long

using namespace std;

int n , q , ans;

const int N = 3e3 + 5;
const int mod = 1e9 + 7;

int a[N] , f[N][N];

int qpow(int x , int y){
	int ans = 1;
	while(y){
		if(y & 1)
			ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}

signed main(){
	cin >> n >> q;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(a[i] < a[j])
				f[i][j] = 1;
	int inv = qpow(2 , mod - 2) % mod;	
    int mul = 1;
	while(q--){
        mul = mul * 2 % mod;
		int x , y;
		cin >> x >> y;
		f[x][y] = f[y][x] = (f[x][y] + f[y][x]) * inv % mod;
		for(int j = 1; j <= n; j++){
			if(j == x || j == y)	
				continue;
			f[x][j] = f[y][j] = (f[x][j] + f[y][j]) * inv % mod;
			f[j][x] = f[j][y] = (f[j][x] + f[j][y]) * inv % mod;
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < i; j++)
			ans = (ans + f[i][j]) % mod;
//	cout << ans << endl;
//	ans = ans * 4 % mod;
//	int mul = qpow(2 , q);
//	for(int i = 1; i <= q; i++)
//		mul = mul * 2;
//	for(int i = 1; i <= q; i++)
//		ans = (ans << 1) % mod;
////	cout << mul << endl;
	ans = ans * mul % mod;
	cout << (ans + mod) % mod << endl;
	return 0;
}
```


---

