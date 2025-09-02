# 「LAOI-12」Calculate

## 题目背景

![](bilibili:BV1gf4y1i76y)

## 题目描述

令一个长度为 $p$ 的序列的权值为将这个序列按任意顺序重排后使得序列第一个数为最小值，可能的 $\sum\limits_{i=1}^{p-1}(a_{i+1}-a_i)^2$ 的最大值。

给定一个长度为 $n$ 序列，现在求这个序列所有长度为**偶数**的非空子序列（可以不连续）的权值和，结果对 $998244353$ 取模。

## 说明/提示

### 样例解释
对于样例一中的序列，共有以下几个子序列（长度为 $1$ 不计入）计入权值：  
1. $\langle1,2\rangle$，贡献权值为 $1$；
2. $\langle1,3\rangle$，贡献权值为 $4$；
3. $\langle1,4\rangle$，贡献权值为 $9$；
4. $\langle2,3\rangle$，贡献权值为 $1$；
5. $\langle2,4\rangle$，贡献权值为 $4$；
6. $\langle3,4\rangle$，贡献权值为 $1$；
7. $\langle1,2,3,4\rangle$，贡献权值为 $9+4+1=14$。

所以总贡献为 $1+4+9+1+4+1+14=34$。
### 数据范围
**本题采用捆绑测试。**

|子任务编号|$n$|特殊性质|分值|
|:-:|:-:|:-:|:-:|
|$1$|$\le8$|无|$5$|
|$2$|$\le5\times10^3$|$a_i\le2$|$10$|
|$3$|$\le10^3$|无|$30$|
|$4$|$\le5\times10^3$|无|$55$|

对于 $100\%$ 的测试数据，满足 $2\le n \le 5\times10^3$，$1\le a_i\le 10^9$。

## 样例 #1

### 输入

```
4
1 2 3 4```

### 输出

```
34```

# 题解

## 作者：Anemones (赞：2)

首先不难发现将 $a$ 重排后不影响答案，所以我们先从小到大排列。  

对于这个权值和有一个贪心策略：这个序列必然是一小一大的，具体证明的话可以任意交换，交换后一定更劣。

那么我们便可以对每个 $a_i,a_j$ 组合进行计数，由于序列已排序，那么便是在 $i$ 左边有 $x$ 个数，$j$ 左边有 $y$ 个数，那么先假设左右选的数相同，方案数即为 $\sum\limits_{i=0}^{\min(a,b)}\binom{a}{i}\binom{b}{i}=\binom{a+b}{\min(a,b)}$，上述式子可以用范德蒙德卷积证明，然后中间再选偶数个数乘起来。显然左右选的个数可以不对等，右边可以多一个，那方案便是 $\sum\limits_{i=0}^{\min(a,b-1)}\binom{a}{i}\binom{b}{i+1}=\binom{a+b}{a+1}$，然后中间再选奇数个数乘起来，故时间复杂度 $O(n^2+n\log p)$。


```cpp
#include<bits/stdc++.h>
#include<ext/rope>
using namespace __gnu_cxx;
#define mp make_pair
#define pb push_back
#define dbg puts("-------------qaqaqaqaqaqaqaqaqaq------------")
#define pl (p<<1)
#define pr ((p<<1)|1)
#define pii pair<int,int>
#define int long long
#define mod 998244353
#define eps 1e-9
#define ent putchar('\n')
#define sp putchar(' ')
using namespace std;
inline int read(){
    char c=getchar(),f=0;int t=0;
    for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
    for(;c>='0'&&c<='9';c=getchar()) t=(t<<1)+(t<<3)+(c^48);
    return f?-t:t;
}
inline void write(int x){
    static int t[25];int tp=0;
    if(x==0) return(void)(putchar('0'));else if(x<0) putchar('-'),x=-x;
    while(x) t[tp++]=x%10,x/=10;
    while(tp--) putchar(t[tp]+48);
}
int a[5009],p2[10009];
int f[10009],inv[10009];
int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
void init(){
    f[0]=inv[0]=1;
    p2[0]=1;
    for(int i=1;i<=10000;i++){
        p2[i]=p2[i-1]*2%mod;
        f[i]=f[i-1]*i%mod;
        inv[i]=qpow(f[i],mod-2);
    }
}
int calc(int n,int m){
    if(n==m||m==0) return 1;
    if(n<m) return 0;
    return f[n]*inv[n-m]%mod*inv[m]%mod;
}
int get(int n){return p2[n-1];}
signed main(){
    init();
    for(int task=0;task<=0;task++){
        char awa[30];
        //sprintf(awa,"calc%d.in",task);
	    //freopen(awa,"r",stdin);
		//sprintf(awa,"calc%d.out",task);
		//freopen(awa,"w",stdout);
        int n=read();
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        int ans=0;
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                int las=ans;
                int mid=j-i-1,res=(a[j]-a[i])*(a[j]-a[i])%mod;
                int lsum=i-1,rsum=n-j;
                if(mid==0){
                    ans=(ans+res*(calc(lsum+rsum,min(lsum,rsum)))%mod)%mod;
                    //write(i),sp,write(j),sp,write(ans-las),dbg; 
                    continue;
                }
                int temp=calc(lsum+rsum,min(lsum,rsum))*get(mid)%mod;
                //if(rsum!=0) temp=(temp+get(mid)*calc(lsum+rsum,lsum+1)%mod)%mod;
                if(lsum!=0) temp=(temp+get(mid)*calc(lsum+rsum,rsum+1)%mod)%mod;
                //res=res*temp%mod;
                ans=(ans+(temp)*res%mod)%mod;
                //write(i),sp,write(j),sp,write(temp+1),sp,write(ans-las),dbg;
            }
        }
        write(ans),ent;
    }
    return 0;
}
```

---

## 作者：Sliarae (赞：1)

考虑一个长度为 $p$ 的序列 $a$ 的权值怎么算，假设 $a_1 \le a_2 \le \ldots \le a_p$，那么肯定是重排成 $a_1, a_p, a_2, a_{p - 1}, \ldots$ 最优。

对于题目中给定的序列 $a$ 也进行排序。接下来拆贡献，枚举一对 $i, j(i < j)$，考虑 $(a_i - a_j)^2$ 会对答案贡献多少次。

假设 $p$ 为 $i$ 左边的数的个数，$q$ 为 $j$ 右边的数的个数。显然 $p = i - 1, q = n - j$。要使 $a_i, a_j$ 在重排后的序列中相邻，设在 $i$ 左边选 $x$ 个数，经过一些分类讨论可得要在 $j$ 右边选 $x - 1$ 或 $x$ 个数。

先考虑在 $j$ 右边选 $x$ 个数的情况，方案数为 $\sum\limits_{x} {p \choose x} {q \choose x}$，根据范德蒙德恒等式，它等于 $p + q \choose q$。在 $j$ 右边选 $x + 1$ 个数的情况同理，类似可得方案数为 $p + q \choose q + 1$。

还有一个问题是要在区间 $[i + 1, j - 1]$ 中选若出干个数，还要使得选出数的总个数为偶数。但其实这是简单的，假设中间有 $c$ 个数，我们要在其中选出奇数/偶数个数，由对称性（或一些二项式推论）可得除 $c = 0$ 外方案数均为 $2^{c - 1}$。

对于每对 $i, j$，计算 $(a_i - a_j)^2$ 对答案的贡献系数是 $O(1)$ 的，故总时间复杂度为 $O(n^2)$。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int kN = 5e3 + 5;
const int Mod = 998244353;

int n;
int a[kN], pw[kN];
int inv[kN], fac[kN], ifac[kN];

int C (int n, int m) {
  if (n < m) return 0; 
  return 1ll * fac[n] * ifac[m] % Mod * ifac[n - m] % Mod;
}

int main () {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = 1ll * (Mod - Mod / i) * inv[Mod % i] % Mod;
    fac[i] = 1ll * fac[i - 1] * i % Mod;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % Mod;
  }
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * 2 % Mod;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  sort(a + 1, a + n + 1);
  int ans = 0; 
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int even = (j == i + 1 ? 1 : pw[j - i - 2]), odd = (j == i + 1 ? 0 : even);
      int p = i - 1, q = n - j;
      int coef = (1ll * even * C(p + q, q) + 1ll * odd * C(p + q, q + 1)) % Mod;
      ans = (ans + coef * (1ll * (a[i] - a[j]) * (a[i] - a[j]) % Mod)) % Mod;
    }
  }
  cout << ans << '\n';
  return 0; 
}
```

---

## 作者：晴空一鹤 (赞：1)

短暂回归跳到主题库最后一题看看自己有没有文化课学傻了，好在蓝题还是能够快速切掉。

先考虑一个序列的权值如何计算，显然应该是 $\min\rightarrow\max\rightarrow\min'\rightarrow\max'\rightarrow...$ 时取到，证明考虑交换。

接下来由于是子序列计数，且权值与元素在序列中排列顺序无关，因此可以任意重排。不妨从小到大排序，那么我们仿照序列权值的计算式进行 `dp`。记 $dp_{i,j}$ 表示正中间两个数下标为 $i$ 和 $j$ 时，所有偶数长子序列的权值和。一个朴素的做法是枚举两个数 $k,d(k<i,d>j)$，从 $dp_{k,d}$ 转移，实际上我们让 $i$ 递增，$j$ 递减计算状态，计算过程中直接把贡献累加起来即可优化掉 $k,d$ 的枚举，做到 $O(n^2)$，足以通过此题。

注意我们实际上需要一个 $cnt_i$ 表示有多少个以 $i$ 为中间靠右端点的偶数长子序列来辅助转移，而它自己本身的转移与 $dp_{i,j}$ 类似且更为简单，这里就不赘述了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353;
const int N=5e3;
ll dp[N+5][N+5],ans[N+5],cnt[N+5],n,a[N+5],ANS;
int main(){
   ios::sync_with_stdio(false);cin.tie(0);
   cin>>n;
   for(int i=1;i<=n;i++)cin>>a[i];
   sort(a+1,a+n+1);
   for(int i=1;i<n;i++)
   dp[i][n]=(a[i]-a[n])*(a[i]-a[n])%mod;
   for(int i=1;i<=n;i++){
   ll P=1,Q=0;
   for(int j=n-1;j>i;j--){
   P+=cnt[j+1];
   Q+=cnt[j+1]*((a[i]-a[j+1])*(a[i]-a[j+1])%mod)%mod+ans[j+1];
   P%=mod,Q%=mod;
   dp[i][j]=(Q+(P*(a[i]-a[j])%mod)*(a[i]-a[j])%mod)%mod;
   cnt[j+1]=P;
   ans[j+1]=(ans[j+1]+dp[i][j+1])%mod;
   }
   }
   for(int i=1;i<n;i++)
   for(int j=i+1;j<=n;j++)
   ANS=(ANS+dp[i][j])%mod;
   cout<<(ANS+mod)%mod<<"\n";
}
```

---

## 作者：冷却心 (赞：0)

Cattleya，植物界被子植物门单子叶植物纲天门冬目兰科卡特兰属卡特兰数。

一个序列对其升序排序后设它为 $a_1,a_2,\dots,a_n$，那么他排列成形如 $a_1,a_n,a_2,a_{n-1},\dots$ 时得到最大权值。放到子序列上我们发现它相当于是一个区间 $[l,r]$ 左右端点轮换着向内移动，所以我们记 $f_{l,r,0/1}$ 表示当前匹配的一对是 $(l,r)$，上一次移动了左/右端点，得到的子序列的答案总和，而 $g_{l,r,0/1}$ 则表示方案数，发现转移是简单的，一个类前缀和状物。所以 $O(n^2)$ 做完。

但是能注意到每一对 $(l,r)$ 贡献 $(a_r-a_l)^2$ 的次数可以单独求出。我们设 $f_i$ 表示 $i$ 个数选出奇数个的方案数，$g_i$ 则表示选择偶数个的方案数。记 $a=l-1$，$b=n-r$，那么一对 $(l,r)$ 的贡献次数有两种：

- $(l,r)$ 恰好左右都选择了相同个数的位置，此时两个位置之间还要选择偶数个位置。那么次数为 $\displaystyle g_{r-l-1} \sum_{i=0} \binom{a}{i}\binom{b}{i}$，后面的求和可以范德蒙德卷积得到贡献是 $g_{r-l-1} \binom{a+b}{a}$。
- $(l,r)$ 左侧选择的数恰好是右侧加一，此时两个位置之间还要选择奇数个位置，对答案的贡献次数为 $\displaystyle f_{r-l-1} \sum_{i=0} \binom{a}{i+1}\binom{b}{i}$，范德蒙德卷积得到贡献为 $f_{r-l-1} \binom{a+b}{b+1}$。

最后求和即可，时间复杂度 $O(n^2)$，没计入预处理阶乘及其逆元的复杂度。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e3 + 10;
const LL MOD = 998244353;
LL Qpow(LL x, LL k, LL P) {
	LL ret = 1, tmp = (x + P) % P;
	while (k) {
		if (k & 1) ret = ret * tmp % P;
		tmp = tmp * tmp % P; k >>= 1;
	} return ret;
}
int n; LL A[N], fact[N], inv[N], F[N], G[N];
LL C(int n, int m) { return (n < m ? 0 : fact[n] * inv[m] % MOD * inv[n - m] % MOD); }
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n; fact[0] = 1;
	for (int i = 1; i <= n; i ++) fact[i] = fact[i - 1] * i % MOD;
	inv[n] = Qpow(fact[n], MOD - 2, MOD);
	for (int i = n - 1; i >= 0; i --) inv[i] = inv[i + 1] * (i + 1) % MOD;
	for (int i = 1; i <= n; i ++) cin >> A[i];
	sort(A + 1, A + 1 + n); LL Ans = 0;
	for (int i = 0; i <= n; i ++) {
		for (int j = 1; j <= i; j += 2) F[i] = (F[i] + C(i, j)) % MOD;
		for (int j = 0; j <= i; j += 2) G[i] = (G[i] + C(i, j)) % MOD;
	}
	for (int l = 1; l <= n; l ++) for (int r = l + 1; r <= n; r ++)	{
		int a = l - 1, b = n - r;
		LL c = G[r - l - 1] * C(a + b, a) % MOD + F[r - l - 1] * C(a + b, b + 1) % MOD;
		Ans = (Ans + (A[r] - A[l]) * (A[r] - A[l]) % MOD * c % MOD) % MOD;
	} cout << Ans << "\n";
	return 0;
}
```

---

