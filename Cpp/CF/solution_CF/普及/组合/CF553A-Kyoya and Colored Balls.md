# Kyoya and Colored Balls

## 题目描述

Kyoya Ootori has a bag with $ n $ colored balls that are colored with $ k $ different colors. The colors are labeled from $ 1 $ to $ k $ . Balls of the same color are indistinguishable. He draws balls from the bag one by one until the bag is empty. He noticed that he drew the last ball of color $ i $ before drawing the last ball of color $ i+1 $ for all $ i $ from $ 1 $ to $ k-1 $ . Now he wonders how many different ways this can happen.

## 说明/提示

In the first sample, we have 2 balls of color 1, 2 balls of color 2, and 1 ball of color 3. The three ways for Kyoya are:

`<br></br>1 2 1 2 3<br></br>1 1 2 2 3<br></br>2 1 1 2 3<br></br>`

## 样例 #1

### 输入

```
3
2
2
1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1
2
3
4
```

### 输出

```
1680
```

# 题解

## 作者：oh_yes (赞：9)

_**组合数学**_

### 介绍一个知识:  插板法

插板法是一种排列组合中用到的方法，用来解决几个数分组的问题

**举个例子:**

现在有10个物体我们要把他们分成5组
求分组的方案数(编号不同算不同的方案)

![](https://i.loli.net/2019/01/13/5c3aa9bbf1de6.jpg)

如图这种情况算不同的方案。

![](https://i.loli.net/2019/01/13/5c3aad161be70.jpg)

可以看成在这十个物体里插入了4个隔板

![](https://i.loli.net/2019/01/13/5c3aaebf16d8a.jpg)

如果我们把隔板也看做物体就变成了这种情况

![](https://i.loli.net/2019/01/13/5c3aafe9defe6.jpg)

相当于在10 + 4个物体里选取4个物体当隔板
可以发现方案数相当于在14个数里选取4个数的方案数

就是我们的组合数 $ C^{4}_{14} $

实在不懂的同学可以自行百度

现在我们回头来看这道题

可以看成是** $k$ 种颜色的球在有限制条件下排列的方案数**

举个例子:

$k = 3$

$c_1 = 2$
$c_2 = 2$
$c_3 = 2$

![](https://i.loli.net/2019/01/13/5c3ab1f563fa1.jpg)

由于**他的最后一个球总是在编号比他大的球拿完之前拿完**

言外之意**当前颜色的最后一个球总是在颜色编号比它小的球拿完之后被拿**

于是设方案数为 $ans$

假如当前已经处理完了前两种颜色的球被拿顺序的序列:

$case1:$ 1 1 2 2

$case2:$ 1 2 1 2

$case3:$ 2 1 1 2

$ans = 3$

我们需要将有第三种颜色的球的情况加入进来

因为我们必须有一个球放在最后，所以我们可以插入的球只有 $c_3 - 1 = 1$ 个，而这一个可以插在已知序列的任何位置

$case1:$

![](https://i.loli.net/2019/01/13/5c3ab743e98a1.jpg)

所以我们可以根据插板法算出插入当前序列的方案数 $ C^{1}_{5} $ 再根据乘法原理

$ans = ans * C^{1}_{5} $

$ans = 15$
	
```cpp
inline void another_solve(){
	//init();
	//scanf("%d", &n);
	//for(register int i = 1; i <= n; i ++)scanf("%lld", &c[i]);
	ll ans = 1;
	ll sum = 0;
	for(register int i = 1; i <= n; i ++){
		/*
		ans *= C[sum + c[i] - 1][c[1] - 1];//插板法
		sum += c[i];//插完之后把"板"也算入总数里
		*/
		sum += c[i];//
		ans *= C[sum - 1][c[i] - 1];//这种写法和上面被注释掉的写法是一样的
	}
	printf("%lld\n", ans);
}

```

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1010;
const int mod = 1e9 + 7;
ll C[maxn][maxn];

inline void init(){//利用帕斯卡恒等式求组合数 
	for(int i = 0; i < maxn; ++i){
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
        C[i][i + 1] = 0;
    }
}

int n;

ll c[maxn];

inline void another_solve(){
	//init();
	//scanf("%d", &n);
	//for(register int i = 1; i <= n; i ++)scanf("%lld", &c[i]);
	ll ans = 1;
	ll sum = 0;
	for(register int i = 1; i <= n; i ++){
		sum += c[i];
		ans *= C[sum - 1][c[i] - 1];
		/*
		ans *= C[sum + c[i] - 1][c[1] - 1];
		sum += c[i];
		*/
	}
	printf("%lld\n", ans);
}

int main(){
	init();
	scanf("%d", &n);
	ll total = 0;
	for(register int i = 1; i <= n; i ++){
		scanf("%lld", &c[i]);
		total += c[i];
	}
	ll ans = 1;
	for(register int i = n; i >= 1; i --){//这种写法和上面的哪一种本质是一样的只是循环的方向不同 
		ans = (ans * C[total - 1][c[i] - 1]) % mod;
		total -= c[i];
	}
	printf("%lld\n", ans);
	another_solve();
	return 0;
}
```

---

## 作者：wxzzzz (赞：3)

### 思路

对于颜色 $i$，它的 $c_i$ 中颜色可选 $1\sim c_i-1$ 个，放到前面颜色编号比它小的 $\displaystyle\sum_{j=1}^{i-1}c_j$ 个球中，有 $\Big(\displaystyle\sum_{j=1}^{i-1}c_j\Big)+c_i-1$ 个空，选 $c_i-1$ 个球放入，有 $\dbinom{\Big(\displaystyle\sum_{j=1}^{i-1}c_j\Big)+c_i-1}{c_i-1}$ 种方法。

答案即为 $\displaystyle\prod_{i=1}^n\dbinom{\Big(\displaystyle\sum_{j=1}^{i-1}c_j\Big)+c_i-1}{c_i-1}$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int k, sum;
long long ans = 1, mul[2005];
long long mod(long long x) {
    return x % 1000000007;
}
long long qpow(int x, int k) {
    long long ret = 1, base = x;

    while (k) {
        if (k & 1)
            ret = mod(ret * base);

        base = mod(base * base);
        k >>= 1;
    }

    return ret;
}
long long C(int x, int y) {
    if (y > x)
        return 0;

    long long t1, t2;
    t1 = qpow(mul[y], 1000000005);
    t2 = qpow(mul[x - y], 1000000005);
    return mod(mod(mul[x] * t1) * t2);
}
int main() {
    mul[0] = 1;

    for (int i = 1; i <= 2000; i++)
        mul[i] = mod(mul[i - 1] * i);

    cin >> k;

    for (int i = 1, t; i <= k; i++) {
        cin >> t;
        ans = mod(ans * C(sum + t - 1, t - 1));
        sum += t;
    }

    cout << ans;
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：2)

## 思路

考虑到有很多个颜色，且颜色从小到大考虑，所以考虑把每个颜色当前方案数相乘为总方案数。

我们设 $r_i = \sum\limits_{p = 1}^i c_p$，那么当前考虑到第 $i$ 种颜色且没有把第 $i$ 种颜色放进去时球的总数有 $r_{i - 1}$ 个，考虑 $c_i$ 个颜色为 $i$ 的球，我们要钦定一个球放在 $r_{i - 1}$ 个球的后面，然后再让剩下 $c_{i} - 1$ 个球插入 $r_{i - 1}$ 个球中，由于球是不区分的，所以当前的方案数用插板法就是 $C_{r_{i - 1} + c_i - 1}^{r_{i - 1}} = C_{r_i - 1}^{r_{i - 1}}$，所以最后的答案就是相乘：

$$\prod_{i = 1}^{k} C_{r_i - 1}^{r_{i - 1}}$$

然后求组合数你可以用杨辉三角，我用得是求阶乘逆元直接求。

## 代码

Code：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 5;

int t, n, p = 1e9 + 7, ans = 1;
int fac[N], inv[N], c[N], sum[N];

int fast_pow ( int a, int b ) {
	int res = 1;
	while ( b ) {
		if ( b & 1ll ) {
			res = res * a;
			res %= p;
		}
		b >>= 1ll;
		a = a * a;
		a %= p;
	}
	return res;
}

void init () {
	fac[0] = inv[0] = 1;
	for ( int i = 1; i <= 100000; i ++ ) {
		fac[i] = fac[i - 1] * i;
		fac[i] %= p;
	}
}

int C ( int n, int m ) {
	if ( n < m ) {
		return 0;
	}
	return fac[n] * fast_pow ( fac[m], p - 2 ) % p * fast_pow ( fac[n - m], p - 2 ) % p;
}

signed main () {
	init ();
	cin >> n;
	for ( int i = 1; i <= n; i ++ ) {
		cin >> c[i];
		sum[i] = sum[i - 1] + c[i];
	}
	for ( int i = 1; i <= n; i ++ ) {
		ans *= C ( sum[i] - 1, sum[i - 1] );
		ans %= p;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Milmon (赞：2)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF553A) & [Problem](//www.luogu.com.cn/problem/CF553A)

## 题目大意

- 有 $n$ 个球，这些球有 $k$ 种颜色，颜色 $i$ 的球有 $c_i$ 个。

- 将这些球排序，满足 $\forall\ 1\leq i<n$，序列中最后一个颜色 $i$ 的球出现在序列中最后一个颜色 $i+1$ 的球之前。求合法的排序数量。

- $1\leq n,\ k,\ c_i\leq 10^3$

## 解题思路

考虑依次往序列中插入颜色为 $1$ 的球，颜色为 $2$ 的球，以此类推直到颜色为 $k$ 的球也被插入。

在颜色 $<i$ 的球全都插入序列时，我们要插入颜色为 $i$ 的球，设

$$
n_i=\sum_{j=1}^{i-1}c_i.
$$

显然插入完毕后序列中最后一个球必为颜色 $i$，那么不妨先将其插入序列的末端。那么剩余 $c_i-1$ 个求要插入到前面 $n_i$ 个球的 $n_i+1$ 个缝隙中，等价于用 $n_i$ 个球将 $c_i-1$ 个球隔开，由插板法易得有 $\dbinom{n_i+c_i-1}{n_i}$ 种方法。

故最终方法数为

$$
\prod_{i=1}^k\dbinom{n_i+c_i-1}{n_i}.
$$

时间复杂度 $\Theta(n^2)$（用于初始化组合数）。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int C[1001][1001];

long long answer=1;
int n,k;

int main(){
	for(int i=0;i<=1000;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		int c;
		scanf("%d",&c);
		answer*=C[c+n-1][n];
		n+=c,answer%=mod;
	}
	printf("%lld\n",answer);
	return 0;
}
```

---

## 作者：BADFIVE (赞：2)

**题意**：用 $k$ 种不同的颜色给 $n$ 个球涂色，每种颜色表上序号 $1 \sim K$ ，涂色规则为涂 $i$ 颜色球的最后一个球时，它的后面一个球为 $i+1$ 颜色的球。   
**思路**：我们先确定每种颜色的最后一个球，然后再扔球进去，可以发现第 $i$ 种颜色的方案数刚好是 $C_{sum-1}^{a[i]-1}$ ，$sum$ 为 $ai$ 的前缀和。   
这是一个组合排列问题。假设 $k$ 颜色球有 $m$ 个，那么一个球放在最右边就好，剩下的 $m-1$ 个球排列情况有 $C_{n-1}^{m-1}$，假设 $k-1$ 颜色的球有 $z$ 个，那么这是后选出一个放在最右侧的空位就好，剩余的 $z-1$ 个排列情况有 $C_{n-m-1}^{z-1}$，$...$，直到第一种颜色结束。
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1000000007;
int a[1001],sum[1001],b[1001][1001];
signed main(){
	int k,ans=1;
    memset(b,0,sizeof(b));
    for(int i=1;i<1001;i++){
        b[i][0]=b[i][i]=1;
        for(int j=1;j<i;j++){
            b[i][j]=(b[i-1][j-1]+b[i-1][j])%mod;
        }
    }
	cin>>k;
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=k;i++){
        cin>>a[i];
        sum[i] +=sum[i-1]+a[i];
    }
    for(int i=k;i>=1;i--){
        if(a[i]==1)continue;
        ans=(ans*b[sum[i]-1][a[i]-1])%mod;
    }
    cout<<ans;
}
```

---

## 作者：离散小波变换° (赞：1)

## 题解

记颜色为 $i$ 的球的个数为 $c_i$。

考察颜色编号最大的那一种球（即颜色为 $k$ 的球）。容易发现，最后一个被取走的球的颜色一定为 $k$。那么对于剩下来的那 $c_{k}-1$ 个球，总是可以任意安排取走的顺序而不影响到别的球。

当我们把编号为 $k$ 的球安排好之后，最大的颜色编号变成了 $k-1$。按照上述过程如法炮制安排好颜色为 $k-1$ 的球，接着安排颜色为 $k-2$ 的球，以此类推，直到安排完所有的球，就可以得到最终答案：

$$\mathit{ans}=\prod_{i=1}^k \dbinom{n-\sum_{j=i+1}^{k} c_j - 1}{c_i - 1}$$

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 1e3 + 3;
const int MOD  = 1e9 + 7;
int C[MAXN], n, T[MAXN][MAXN], ans = 1;
int main(){
    int k = qread(), t = 1e3;
    up(0, t, i) T[i][0] = 1;
    up(1, t, i){
        up(1, i, j){
            T[i][j] = (T[i - 1][j] + T[i - 1][j - 1]) % MOD;
        }
    }
    up(1, k, i) C[i] = qread(), n += C[i];
    dn(k, 1, i){
        ans = 1ll * ans * T[n - 1][C[i] - 1] % MOD;
        n -= C[i];
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Grisses (赞：1)

[题面](https://www.luogu.com.cn/problem/CF553A)

如果我们现在已经放完了前 $i-1$ 种球共 $sum$ 个，方案数为 $ans$，而第 $i$ 种球有 $a$ 个。

那么，为了保证第 $i$ 种球在前 $i-1$ 种球放完后放完，我们第 $i$ 种球种必有一个放在最后。

然后我们就只有 $a-1$ 个球了，这些球可以在前面随便放，即放在前面 $sum$ 个球分出的 $sum+1$ 个间隙里，方案数为 $C_{a+sum-1}^{sum}$（类似盒球问题）。

所以现在的方案数为 $ans\times C_{a+sum-1}^{sum}$。

代码：
```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int mod=1e9+7;
  int m,n,x,y,ans,num[40],c[5000005],inc[5000005],l[2000005],r[2000005];
  char s[2000005];
  int fpow(int a,int b){
      if(b<0)return 1;
      int res=1;
      while(b){
          if(b&1)res=res*a%mod;
          a=a*a%mod;
          b>>=1;
      }
      return res;
  }
  inline int C(int n,int m){
      if(m>n)return 0;
      return c[n]*inc[m]%mod*inc[n-m]%mod;
  }
  signed main()
  {
      c[0]=c[1]=1;
      for(int i=2;i<=5000000;i++)c[i]=c[i-1]*i%mod;
      inc[5000000]=fpow(c[5000000],mod-2);
      for(int i=5000000-1;i>=0;i--)inc[i]=inc[i+1]*(i+1)%mod;//初始化阶乘及其逆元
      scanf("%lld",&n);
      ans=1;
      for(int i=1,a,sum=0;i<=n;i++){
          scanf("%lld",&a);
          ans=ans*C(a+sum-1,a-1)%mod;//更新答案
          sum+=a;//更新sum
      }
      printf("%lld",ans);
      return 0;
  }
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

当颜色小于 $i$ 的球全部进入出袋序列时，颜色为 $i$ 的球进入序列。

令 $s_i=\sum_{j=1}^i c_i$。

由题可知，拿完后最后的一个球必定颜色为 $k$，将其插入序列末端，则剩余 $c_k-1$ 个颜色为 $k$ 的球可自由排序而不影响别的球。

拿完颜色为 $k$ 的后，最终的球颜色变为 $k-1$。以此类推，推完所有的球，则有：

$$ans=\prod_{i=1}^{k}{s_{i-1}+c_i-1 \choose s_{i-1}}$$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+10;
const int p=1e9+7;
int farc[N],c[N],n,ans=1,sm[N];
inline int Pow(int a,int b){int s=1ll;while(b){if(b&1ll)s=s*a%p;a=a*a%p;b>>=1ll;}return s%p;}
inline int C(int n,int m){if(m>n)return 0;return farc[n]*Pow(farc[m],p-2ll)%p*Pow(farc[n-m],p-2ll)%p;}
inline int Lucas(int n,int m){if(!m)return 1ll;return 1ll*Lucas(n/p,m/p)*C(n%p,m%p)%p;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n;farc[0]=1;for(int i=1;i<N;++i)farc[i]=(farc[i-1]*i)%p;
	for(int i=1;i<=n;++i)cin>>c[i],sm[i]=sm[i-1]+c[i];
	for(int i=1;i<=n;++i)ans=(ans*Lucas(sm[i-1]+c[i]-1,sm[i-1]))%p;
	cout<<ans;
	return 0;
}

```


---

## 作者：lfxxx (赞：0)

考虑设计状态 $dp_{i,j}$ 表示考虑到第 $i$ 位并填了第 $j$ 种颜色的最后一个球。

那么前面 $i-1$ 个空已经被前 $j-1$ 种颜色填了 $\sum_{i=1}^{j-1} c_i$ 个球，还剩下 $j-1-\sum_{l=1}^{j-1} c_l$ 个位置要填 $c_j - 1$ 个球，直接处理出组合数即可。

那么有转移 $dp_{i,j} = \sum_{k=1}^{i-1} dp_{k,j-1} \times {j-1-\sum_{l=1}^{j-1} c_l\choose c_j - 1}$。预处理出前缀和即可做到 $O(n^2 \log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
//dp[i][k] i-\sum_{j=1}^{k-1} c_j c_i * dp_{l,k-1}  l<i
const int maxn = 1e3+114;
const int mod = 1e9+7;
int dp[maxn][maxn];
int pre[maxn][maxn];
int C[maxn];
int preC[maxn];
int n,k;
int fac[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a%mod;
    int res=qpow(a,b/2);
    res=(res*res)%mod;
    if(b%2==1) res=(res*(a%mod))%mod;
    return res;
}
int work(int n,int m){
    if(m>n) return 0;
    return (((fac[n]*qpow(fac[n-m],mod-2))%mod)*qpow(fac[m],mod-2))%mod;
}
signed main(){
	fac[0]=1;
	for(int i=1;i<maxn;i++) fac[i]=(fac[i-1]*i)%mod;
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>C[i];
		n+=C[i];
		preC[i]=preC[i-1]+C[i];
	}
	for(int j=1;j<=n;j++){
		dp[1][j]=work(j-1,C[1]-1);
		pre[1][j]=(pre[1][j-1]+dp[1][j])%mod;
	}
	for(int i=2;i<=k;i++){
		for(int j=1;j<=n;j++){
			dp[i][j]=(pre[i-1][j-1]*work(j-1-preC[i-1],C[i]-1))%mod;
			pre[i][j]=(pre[i][j-1]+dp[i][j])%mod;
		}
	}
	cout<<dp[k][n]<<'\n';
	return 0;
}

```


---

## 作者：SpringFullGarden (赞：0)

## 题意

有 $k$ 种颜色的球，每种颜色的球有 $a_i$ 个，将这些球排序，求有多少个序列满足：所有颜色为 $i$ 的球必须在颜色为 $i + 1$ 的最后一个球前。

## 思路

### 箱球问题

将 $n$ 个相同的球放进 $m$ 个不同的箱子里，箱子不能为空。可以将其转化为 $n - 1$ 个空中插入 $m - 1$ 块板，结果为 $C_{n - 1} ^ {m - 1}$。

那么当可以为空时，将球和板看成同一种物体，从里面选 $m - 1$ 个板出来，结果为 $C_{n + m - 1} ^ {m - 1}$

### 转化

可以看成在颜色 $< i$ 的球放入后，放入颜色为 $i$ 的球的方案数的乘积。

把 $1$ 个颜色为 $i$ 的球放在最后面，就保证所有颜色 $< i$ 的球在颜色为 $i$ 的球前。

其余 $a_i - 1$ 个球插入前面排好的球中，构成了球同、箱不同、箱可以为空的箱球问题。

结果为 $\prod _ {i = 1} ^ {k} C _ {sum - 1} ^ {a_i - 1}$，$sum$ 为 $a_i$ 的前缀和。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define sp() putchar(' ')
#define et() putchar(' \n')
#define mod 1000000007
//#pragma GCC optimize(2)
using namespace std;
 
inline ll rd() {
    ll x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
inline void wt(ll x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) wt(x / 10);
    putchar(x % 10 + '0');
    return;
}
 
ll a[1005], c[1005][1005];
 
int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
	for(ll i = 0; i < 1005; i++) c[i][0] = 1;
	for(ll i = 0; i < 1005; i++) 
		for(ll j = 1; j <= i; j++) 
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	ll k = rd(), ans = 1, sum = 0;
	for(ll i = 1; i <= k; i++) 
		a[i] = rd(), sum += a[i], 
		ans = ans * c[sum - 1][a[i] - 1] % mod;
	wt(ans);
    return 0;
}
```

---

## 作者：TTpandaS (赞：0)

当前在放第 $i$ 种球，令前 $i-1$ 种球的总数为 $x$，第 $i$ 球数量为 $y$。

我们需要保证有一个球需要放在最后，所以将 $y-1$ 个球放置在前 $x+1$ 个空隙中，方案数为：

$$\prod_{i=1}^{n} C_{a_i-1+\sum_{j=1}^{i-1}a_j}^{a_i-1}   $$

---

