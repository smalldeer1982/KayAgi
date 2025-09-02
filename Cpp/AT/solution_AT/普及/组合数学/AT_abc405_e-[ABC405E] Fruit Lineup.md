# [ABC405E] Fruit Lineup

## 题目描述

你有 $A$ 个苹果，$B$ 个橙子，$C$ 串香蕉，$D$ 串葡萄。同种水果之间是完全相同的。

求把它们从左往右排成一排的方案数，方案需要满足：
- 所有的苹果都在所有的香蕉的左边；
- 所有的苹果都在所有的葡萄的左边；
- 所有的橙子都在所有的葡萄的左边。

答案对 $998244353$ 取模。

## 说明/提示

**样例 1 解释**

以下为所有 $5$ 种合法的排列方案：
- 苹果，橙子，香蕉，葡萄
- 苹果，橙子，葡萄，香蕉
- 苹果，香蕉，橙子，葡萄
- 橙子，苹果，香蕉，葡萄
- 橙子，苹果，葡萄，香蕉

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
1 1 1 1```

### 输出

```
5```

## 样例 #2

### 输入

```
1 2 4 8```

### 输出

```
2211```

## 样例 #3

### 输入

```
834150 21994 467364 994225```

### 输出

```
947921688```

# 题解

## 作者：zhuoheng (赞：5)

这题第一眼看上去就数学。        
首先我们需要做在 $a+b$ 里放置 $a$ 个相同的物品和b个相同的物品的不同情况数。                
这个的很显然等同于在 $a+b$ 个空位中放 $a$ 个物品的组合数，即 $C^{a+b}_{a}$ 。                         
接着我们从头考虑这个问题，苹果和橙子肯定是放在最开始的，但是它们之间的顺序是不确定的所以需要计算一下。                 
接着我们来看橙子，它被要求在葡萄之后，但是它和香蕉的顺序是不固定的。                               
然后看到葡萄，它被要求在橙子和苹果之后，所以相当于确定了苹果和橙子后它就基本上固定了，但是它和香蕉的顺序也是不固定的。       
那么我们可以发现只需要枚举一下有多少个橙子在苹果之后然后就相当于在确定的橙子和葡萄中放置橙子。      
这题就做完了。自认为思路比较清新。                             
放个代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353,N=4e6;
int qpow(int a,int b){
    int res=1;a%=mod;
    while(b){
        if(b%2)res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}
int A[N+1],inva[N+1];
int C(int a,int b){
	if(!a||!b)return 1;
	return A[a+b]*inva[a]%mod*inva[b]%mod;
}
int a,b,c,d,ans;
signed main(){
	A[0]=1,A[1]=1;
	for(int i=1;i<=N;i++)A[i]=A[i-1]*i%mod,inva[i]=qpow(A[i],mod-2);
	cin>>a>>b>>c>>d;
	for(int i=0;i<=b;i++)ans+=C(a-1,i)*C(b+d-i,c)%mod,ans%=mod;
	cout<<ans;
	
}

```
注意代码中的 $C$ 函数并不等同于组合数。

---

## 作者：Jenny_yu (赞：2)

是道数学题。

设 $n = A + B + C + D$。根据题目条件能想出来大概水果应该这么排。

![](https://cdn.luogu.com.cn/upload/image_hosting/vq18cony.png)

这样的排法初步保证了苹果和橙子都排在葡萄前。

为什么要单独把第一个葡萄的位置列出来？因为第一个葡萄的位置确定后，橙子和苹果的位置区间就定了。因此考虑枚举第一个葡萄的位置。

前 $i - 1$ 个水果，先排橙子，情况有 $\binom{i - 1}{B}$ 种。之后从前往后找空位先把苹果都填了，剩余还有位置就填香蕉。这样保证了苹果排在香蕉前。

之后还要考虑葡萄和香蕉的区间。一共 $n - i$ 个位置，还没排位置的葡萄有 $D - 1$ 个，因此情况数有 $\binom{n - i}{D - 1}$ 种。

因此对于 $A + B + 1 \le i \le n - D + 1$ 的 $i$，贡献有 $\binom{i - 1}{B} \binom{n - i}{D - 1}$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int s[4000010];
int poww(int x,int y){
	int res = 1;
	while(y){
		if(y % 2 == 1)res = res * x % mod;
		x = x * x % mod;
		y /= 2;
	}
	return res;
}
int C(int n,int m){
	return s[m] * poww(s[n],mod - 2) % mod * poww(s[m - n],mod - 2) % mod;
}
signed main(){
	int a,b,c,d;
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	int ans = 0;
	s[0] = 1;
	for(int i = 1; i <= a + b + c + d; i++){
		s[i] = s[i - 1] * i % mod;
	}
	for(int i = a + 1 + b; i <= a + b + c + 1; i++){
		ans = (ans + C(b,i - 1) * C(d - 1,a + b + c + d - i) % mod) % mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：LucasAoSaic (赞：2)

## 问题描述

给定四种水果的数量：
- **A** 个苹果
- **B** 个橙子
- **C** 个香蕉
- **D** 个葡萄

要求将这 $A+B+C+D$ 个水果排成一排（从左到右），排列必须满足以下条件：
1. 每个苹果必须排在每个香蕉之前；
2. 每个苹果必须排在每个葡萄之前；
3. 每个橙子必须排在每个葡萄之前。

果物之间同种不可区分，所有排列结果取模 $998244353$ 。

---

## 核心思想与公式推导

由于题目条件：
- 条件 (2) 和 (3) 要求所有苹果和橙子在所有葡萄之前，
- 条件 (1) 要求所有苹果必须位于香蕉之前。

我们可以将整个排列分为两部分：
1. **左侧部分**：包含所有苹果、所有橙子以及部分香蕉。
2. **右侧部分**：包含所有葡萄以及剩余的香蕉。

设左侧放香蕉数为 $x$（其中 $x$ 可以取 $0 \le x \le C$），则右侧放香蕉数为 $C - x$。

### 左侧部分的排列
左侧部分包含：
- 苹果：$A$ 个
- 橙子：$B$ 个
- 左侧香蕉：$x$ 个

由于苹果必须全部在香蕉之前，所以苹果和香蕉的相对顺序固定（先 $A$ 个苹果，再 $x$ 个香蕉）。橙子可以插入到这 $A+x$ 个确定位置的任意位置，总数即为 $A+B+x$ 个位置中任选 $B$ 个位置放橙子，因此有：
$$
\text{ways}_{\text{left}}(x) = \binom{A+B+x}{B}.
$$

### 右侧部分的排列
右侧部分包含：
- 葡萄：$D$ 个
- 右侧香蕉：$C - x$ 个

为满足条件“所有橙子（及苹果）必须在葡萄之前”，右侧部分的第一个位置必须是葡萄。固定后，剩余的葡萄数为 $D-1$ 个，和 $C-x$ 个香蕉共计 $(D-1)+(C-x)$ 个位置，任选 $D-1$ 个位置放葡萄，即：
$$
\text{ways}_{\text{right}}(x) = \binom{(C-x) + D - 1}{D-1}.
$$

### 总排列数
把左侧和右侧部分的方法数相乘后，对 $x$ 从 $0$ 到 $C$ 求和，即当 $D \ge 1$ 时，总方案数为：
$$
\text{ans} = \sum_{x=0}^{C} \binom{A+B+x}{B} \cdot \binom{(C-x)+(D-1)}{D-1} \pmod{998244353}.
$$
当 $D=0$（没有葡萄）时，只需满足苹果在香蕉之前：
$$
\text{ans} = \binom{A+B+C}{B} \pmod{998244353}.
$$

---

## 详细代码（带注释）

下面是完整的 C++ 代码，代码中利用预处理阶乘和逆阶乘（使用快速幂法计算模逆元），从而快速求组合数。注释部分详细说明了每一步的含义。

```cpp
#include <iostream>
using namespace std;

typedef long long ll;

const int MOD = 998244353;
// 预处理数组大小，取值足够覆盖题目最大规模，这里取 MAXN = 3000000 + 10
const int MAXN = 3000000 + 10;

int a, b, c, d; // 分别代表苹果、橙子、香蕉、葡萄的数量
ll fact[MAXN], invfact[MAXN];

// 快速幂函数，计算 base^exp mod MOD
inline ll quickPow(ll base, ll exp)
{
    ll cnt = 1;
    while (exp)
    {
        if (exp & 1)
        {
            cnt = cnt * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }
    return cnt;
}

// 预处理 0 到 n 的阶乘和逆阶乘数组
inline void precompute(int n)
{
    fact[0] = 1;
    for (int i = 1; i <= n; ++ i)
    {
        fact[i] = fact[i - 1] * i % MOD;
    }
    // 利用费马小定理计算 fact[n] 的逆元
    invfact[n] = quickPow(fact[n], MOD - 2);
    // 反向递推计算 invfact 数组，从 n 到 0
    for (int i = n; i >= 0; -- i)
    {
        if (i)
        {
            invfact[i - 1] = invfact[i] * i % MOD;
        }
    }
}

// 计算组合数 C(n, k) mod MOD（n 选 k）
inline ll cnm(int n, int k)
{
    if (k < 0 || k > n)
    {
        return 0;
    }
    return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
}

int main()
{
    // 读入水果数量：a=苹果, b=橙子, c=香蕉, d=葡萄
    scanf("%d%d%d%d", &a, &b, &c, &d);
    
    // 计算预处理上界：
    // 左侧部分最多需要 a+b+c 项；右侧部分需要的最大项为 c+d-1，
    // 取两者较大值作为预处理范围。
    int n1 = a + b + c, 
        n2 = c + d - 1, 
        nmax = n1 > n2 ? n1 : n2;
    
    // 预处理阶乘与逆阶乘数组，范围 [0, nmax]
    precompute(nmax);
    
    ll ans = 0;
    // 当没有葡萄时，仅考虑苹果、橙子、香蕉的排序
    if (d == 0)
    {
        ans = cnm(a + b + c, b);
    }
    else
    {
        // 枚举 x：放在左侧的香蕉数，从 0 到 c
        for (int x = 0; x <= c; x++)
        {
            // 左侧部分：
            // 包含 a 个苹果、b 个橙子和 x 个香蕉
            // 由于苹果必须在香蕉前面，其排列方案数为从 (a+b+x) 个位置中选出 b 个位置放橙子
            ll ways1 = cnm(a + b + x, b);
            
            // 右侧部分：
            // 包含剩余的香蕉（c - x）个和 d 个葡萄，
            // 且为满足条件，右侧部分的第一个位置必须为葡萄，
            // 剩下的有 (c-x) + (d-1) 个位置，从中选择 (d-1) 个放葡萄
            ll ways2 = cnm((c - x) + d - 1, d - 1);
            
            // 将左右两部分方案数的乘积累加到答案中
            ans = (ans + ways1 * ways2) % MOD;
        }
    }
    
    // 输出答案（模 MOD）
    printf("%lld\n", ans);
    
    // 此处 cin >> a; 可用于调试时暂停，但在提交时可以删除
    cin >> a;
    return 0;
}
```

---

## 作者：AC_Lover (赞：2)

记 $N=A+B+C+D$ 表示水果总数

可以发现位置关系一定是：

```text
|----A----|     |--D--|
|-------B------|
           |-----C----|
```

  要计算方案数，很明显要枚举水果边界的位置，由于苹果约束最多，所以考虑枚举苹果的边界，即最靠右的苹果，记其位置为 $i$，那么所有苹果处于 $[1,i]$，因为钦定第 $i$ 个位置必放，所以放苹果方案数为 $\binom{i-1}{A-1}$。并且由于香蕉都处于苹果右边，所以香蕉的位置处于 $[i+1,N]$，往里面填 $C$ 个香蕉，方案数是 $\binom{N-i}{C}$。此时我们发现，苹果和香蕉已经选好了，而由于橙子和葡萄的位置关系确定，所以只能将其按顺序插到剩余的空位里，所以只要确定苹果和香蕉就确定整个顺序，于是方案数就是 $\binom{i-1}{A-1}\binom{N-i}{C}$。然后考虑 $i$ 的范围，首先由于苹果要放得下所以 $i\ge A$，并且前面的空位要橙子来填补，只有 $B$ 个橙子，所以最多空 $B$ 个位，$i\le A+B$，而且右边的香蕉要能够放下，所以 $i\le N-C+1$，综上就是 $A\le i\le \min(A+B,N-C+1)$，所以答案就是：

$$
\sum_{i=A}^{\min(A+B,N-C+1)}\binom{i-1}{A-1}\binom{N-i}{C}
$$

时间复杂度 $O(N)$。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int mod=998244353;
struct mint
{
	int x;
	mint() { x=0; }
	mint(int y) { x=(y<0) ? (y+mod) : ((y>=mod) ? y-mod : y); }
	friend ostream &operator << (ostream &os,const mint &p) { return os << p.x; }
	friend istream &operator >> (istream &is,mint &p) 
	{
		int x;is >> x;p=mint(x);
		return is;
	}
	friend mint operator + (const mint &lhs,const mint &rhs) { return mint(lhs.x+rhs.x); }
	friend mint operator - (const mint &lhs,const mint &rhs) { return mint(lhs.x-rhs.x); }
	friend mint operator * (const mint &lhs,const mint &rhs) { return mint((ll)lhs.x*rhs.x%mod); }
	friend mint operator ^ (mint a,int b) 
	{
		mint res(1);
		while (b)
		{
			if (b&1) res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
	friend mint inv(const mint &p) { return p^(mod-2); }
	friend mint operator / (const mint &lhs,const mint &rhs) { return lhs*inv(rhs); } 
	mint &operator += (const mint &o) { return (*this)=(*this)+o; }
	mint &operator -= (const mint &o) { return (*this)=(*this)-o; }
	mint &operator *= (const mint &o) { return (*this)=(*this)*o; }
	mint &operator /= (const mint &o) { return (*this)=(*this)/o; }
};

const int N=4e6+10;
mint fac[N],infac[N];

void init(int n)
{
	fac[0]=1;
	for (int i=1;i<=n;i++) fac[i]=fac[i-1]*i;
	infac[n]=inv(fac[n]);
	for (int i=n-1;i>=0;i--) infac[i]=infac[i+1]*(i+1);
}

mint C(int a,int b) { return fac[a]*infac[b]*infac[a-b]; }

int main()
{
	int a,b,c,d;
	cin >> a >> b >> c >> d;
	
	int n=a+b+c+d;
	init(n);
	
	mint ans=0;
	for (int i=a;i<=min(a+b,n-c+1);i++) ans+=C(i-1,a-1)*C(n-i,c);
	cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：XXh0919 (赞：1)

好吧。。。又是数学题。。。

### 题意

有 $A$ 个苹果，$B$ 个橘子，$C$ 根香蕉，$D$ 个葡萄。现在要求将它们排成一排，并且满足：

- 所有苹果在所有香蕉左边。
- 所有苹果在所有葡萄左边。
- 所有橘子在所有葡萄左边。

求总的摆放方案数对 $998244353$ 取余。

### 解法

首先我们看到葡萄的限制较多，所以我们从葡萄入手。

先看最左边的葡萄及其左边：

设这里有 $A$ 个苹果，$B$ 个橘子，$i$ 根香蕉，则这边的总方案数就是在 $A+i$ 个苹果和香蕉之间插入 $B$ 个橘子的总组合数，得到这里的答案式子

$$ans_{left}=C^{B}_{A+B+i}$$

再看最左边的葡萄的右边：

通过上面的推导，这里一定会有 $C-i$ 根香蕉和 $D-1$ 个葡萄，而香蕉和葡萄这两个东西之间被有任何限制，所以它们可以任意组合，得到这里的答案式子

$$ans_{right}=C^{D-1}_{C-i+D-1}$$

所以最终的答案为

$$ans=\sum^C_{i=0}C^{B}_{A+B+i}\times C^{D-1}_{C-i+D-1}$$

最后别忘了取模。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 4e6 + 15;
const ll mod = 998244353;

ll a, b, c, d;
ll fac[N], inv[N];

ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}//快速幂

void init() {
    ll n = a + b + c + d;
    fac[0] = 1;
    for (ll i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    inv[n] = qpow(fac[n], mod - 2);
    for (ll i = n - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % mod;
    }
}//预处理阶乘和逆元

ll C(ll n, ll m) {
    if (m < 0 || m > n) return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}//计算组合数

int main() {
    scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    init();
    
    ll ans = 0;
    for (int i = 0; i <= c; i++) {
        ll s1 = C(a + b + i, b);
        ll s2 = C(d - 1 + c - i, d - 1);
        ans = (ans + s1 * s2 % mod) % mod;
    }//如上所述
    
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：xy_mc (赞：1)

求组合数，还要取模，显然是还要加上线性求逆元。不会的跳转至[组合数问题](https://www.luogu.com.cn/problem/B3717)进行学习。

首先看一下条件：

- 每个苹果都放在每根香蕉的左边。
  
- 每个苹果都放在每个葡萄的左边。
  
- 每个桔子都放在每个葡萄的左边。

我们发现苹果、香蕉、葡萄放在哪里是可以确定的，而桔子不行，所以我们先不考虑桔子。由于条件 $1$ 和条件 $2$，所有苹果必须放在最左边，而香蕉和葡萄可以交叉放，所以现在的方案数就是香蕉和葡萄随便放的方案数。

假设有 $4$ 个葡萄和 $5$ 个香蕉，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/cp859vch.png)

现在要把 $5$ 个香蕉放入 $5$ 个空隙中，允许有空隙为空，细想一下，这个问题就可以转化为有 $5+5$ 个香蕉（这里的 $5+5$ 指原来的 $5$ 个香蕉加上空隙数）要放入 $5$ 个空隙中，不允许有空的空隙，那么现在只需要先把 $5$ 个香蕉均匀放在每个空隙中，使每个空隙不为空，再把剩下的 $5$ 个香蕉放到 $5$ 个空隙中去。这就相当于有 $10$ 个香蕉，中间有 $9$ 个空隙，现在要插入 $4$ 个挡板，这样就可以分成 $5$ 个部分，每个部分都不能为空，那方案数就是 $C_{9}^{4}$。扩展到有 $C$ 个香蕉和 $D$ 个葡萄的情况，就是有 $C+D+1$ 个香蕉，要放到 $D+1$ 个空隙中，空隙不能为空的情况。那就是有$C+D$ 个空隙，要往里插 $D$ 个板，就是 $C_{C+D}^{D}$。

现在把桔子加进来，它只需要放在葡萄后面就可以，现在枚举一下第一个葡萄之前（左侧）放了几个香蕉，比如放了 $i$ 个，那么第一个葡萄之后（右侧）就放了 $C-i$ 个香蕉。因为桔子和苹果香蕉之间并无关系，所以左侧的方案数同上，要在 $B+A+i$ 个空隙里，放入 $A+i$ 个板，为 $C_{B+A+i}^{A+i}$。右侧同理，在 $C-i+D-1$ 个空隙里插入 $D-1$ 个板，方案数为 $C_{C-i+D-1}^{D-1}$。
这样的话，就有 $C_{B+A+i}^{A+i} \times C_{C-i+D-1}^{D-1}$ 中方案。

最后就是通过逆元求组合数了。

注意：及时取模！！！

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define pll pair<ll,ll>
#define yes "Yes"
#define no "No"
#define debug(x) cout<<#x<<" = "<<x<<"\n"
#define rep(i,x,y) for(int i=x;i<=(y);++i)
#define per(i,x,y) for(int i=x;i>=(y);--i)

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int INF=0x3f3f3f3f;
const ll LNF=0x3f3f3f3f3f3f3f3f;
const int N=4e6+10,mod=998244353;
ll fac[N],inv[N];

ll power(ll x,int p){
	ll res=1;
	while(p){
		if(p&1) res=res*x%mod;
		x=x*x%mod;
		p>>=1;
	}
	return res;
} 

ll C(int n,int m){
	if(n<m) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int a,b,c,d;

void solve(){
	cin>>a>>b>>c>>d;
	fac[0]=1;
	rep(i,1,a+b+c+d){
		fac[i]=fac[i-1]*i%mod;
	}	
	inv[a+b+c+d]=power(fac[a+b+c+d],mod-2);
	per(i,a+b+c+d-1,0){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
	ll ans=0;
	rep(i,0,c){
		ans=(ans+C(a+b+i,a+i)%mod*C(c-i+d-1,d-1)%mod)%mod;
	}
	cout<<ans;
}

int main(){
	int t=1;
	while(t--){
		solve();
	}
	return 0;
}


```

---

## 作者：Chase12345 (赞：0)

结论题。

首先最右边的苹果假设位置为 $i$，则满足 $A \le i \le \min(A+B,N-C-1)$，这一点比较容易理解。

其次，我们注意到剩下 $A-1$ 个苹果已经完全没有限制，也就是可以在前 $i-1$ 个空位任意放，那么由组合数的公式，可以得到这样的选法有 $\binom{i-1}{A-1}$。

最后，要处理的也就只有香蕉了。从后往前 $\sum a+i$ 个位置都是可以放置香蕉的，也就是说这样就可以有 $\binom{\left(\sum a\right)-i}{C}$ 种放法。

综上，要处理的式子也就只有：
$$
\sum_{i=A}^{\min(A+B,N-C-1)}\binom{i-1}{A-1} \times \binom{\sum a-i}{C}
$$
简单使用组合数公式和线性求逆元即可。总的复杂度 $O(\sum a)$，这里表示轮换式（懒得写这么多）。完全足以通过此题。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int P = 998244353, N = 4e6 + 5;
int fact[N], inv[N];

i64 fpow(i64 n, i64 m) {
	i64 res = 1;
	for (; m; n = n * n % P, m >>= 1)
		if (m & 1)
			res = res * n % P;
	return res;
}

void init(i64 n) {
	fact[0] = inv[0] = 1;
	for (int i = 1; i <= n; i++)
		fact[i] = 1LL * fact[i - 1] * i % P;
	inv[n] = fpow(fact[n], P - 2);
	for (int i = n - 1; i > 0; i--)
		inv[i] = 1LL * inv[i + 1] * (i + 1) % P;
}

i64 C(i64 n, i64 m) {
	if (m > n)
		return 0;
	return 1LL * fact[n] * inv[m] % P * inv[n - m] % P;
}

i64 A(i64 m, i64 n) {
	if (m > n)
		return 0;
	return 1LL * fact[n] * inv[n - m] % P;
}

int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	long long res = 0;
	init(a + b + c + d);
	for (int i = a; i <= min(a + b, a + b + 2 * c - 1); i++)
		res = (res + C(i - 1, a - 1) * C(a + b + c + d - i, c) % P) % P;
	cout << res << '\n';
	return 0;
}
```

---

