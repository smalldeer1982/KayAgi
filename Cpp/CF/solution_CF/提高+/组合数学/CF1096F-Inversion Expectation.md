# Inversion Expectation

## 题目描述

一个长度为 $n$ 的排列是一个长度为 $n$ 的数组，其中每个整数 $1$ 到 $n$ 恰好出现一次。对于排列 $p$，一次逆序对定义为一对下标 $(i, j)$，满足 $i > j$ 且 $a_i < a_j$。例如，排列 $[4, 1, 3, 2]$ 包含 $4$ 个逆序对：$(2, 1)$，$(3, 1)$，$(4, 1)$，$(4, 3)$。

现在给定一个长度为 $n$ 的排列 $p$，但其中某些位置上的数字被替换成了 $-1$。我们称“有效排列”为：将这些 $-1$ 替换回 $1$ 到 $n$ 中未出现的数字，使得最终序列是一个长度为 $n$ 的排列。

假设每一种有效排列都等概率地被选中。

请计算最终有效排列中逆序对的期望总数。

可以证明答案可以表示为 $\frac{P}{Q}$，其中 $P$ 和 $Q$ 是非负整数且 $Q \ne 0$。请输出 $P \cdot Q^{-1} \bmod {998244353}$。

## 说明/提示

在第一个样例中，有两种可能的有效排列：

- $[3, 1, 2]$ —— $2$ 个逆序对；
- $[3, 2, 1]$ —— $3$ 个逆序对。

期望值为 $\frac{2 \cdot 1 + 3 \cdot 1}{2} = 2.5$。

在第二个样例中，没有 $-1$，因此只有给定的排列本身是有效排列，逆序对数为 $0$。

在第三个样例中，有两种有效排列，一种有 $0$ 个逆序对，一种有 $1$ 个逆序对。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 -1 -1
```

### 输出

```
499122179
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
-1 -1
```

### 输出

```
499122177
```

# 题解

## 作者：ouuan (赞：8)

逆序对分为四种：

1. 给定的数之间的逆序对。

2. 不确定的数之间的逆序对。

3. 给定的数在不确定的数左边的逆序对。

4. 给定的数在不确定的数右边的逆序对。

## 一、给定的数之间的逆序对

用树状数组/归并排序之类的求即可。

## 二、不确定的数之间的逆序对

任取两个不确定的数，为逆序对的概率为 $\frac1 2$ 。记总的 $-1$ 数量为 $\rm tot$，那么总期望为 $\frac{\rm{tot}\times(\rm{tot}-1)}4$ 。

## 三、给定的数在不确定的数左边的逆序对

对于每个给定的数，记总的 $-1$ 数量为 $\rm tot$，没有出现在给定的数中的数（也就是不确定的数可以取的值）里有 $\rm low$ 个比它小，那么每个在它右边的不确定的位置比它小的概率为 $\frac{\rm low}{\rm tot}$，在它右边有 $r$ 个位置不确定，这个给定的数贡献就是 $\frac{r\times\rm{low}}{\rm tot}$ 。

## 四、给定的数在不确定的数右边的逆序对

与上面一种情况类似，对于每个给定的数，记总的 $-1$ 数量为 $\rm tot$，没有出现在给定的数中的数（也就是不确定的数可以取的值）里有 $\rm high$ 个比它大，那么每个在它左边的不确定的位置比它大的概率为 $\frac{\rm high}{\rm tot}$，在它左边有 $l$ 个位置不确定，这个给定的数贡献就是 $\frac{l\times\rm{high}}{\rm tot}$ 。

## 关于三、四的具体实现

$l$ 和 $r$ 可以用前缀和计算。

预处理出小于等于 $i$ 的数中有 $\mathrm{cnt}[i]$ 个数给定，那么 $\mathrm{low}[i]=i-\mathrm{cnt}[i]$，$\mathrm{high}[i]=\mathrm{tot}-\mathrm{low}[i]$ 。

## 参考代码

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

const int N=200010;
const int M=998244353; 

int qpow(int x,int y); //快速幂用于求逆元 
void add(int p,int x); //树状数组 
int query(int p);

int n,a[N],l[N],r[N],BIT[N],cnt[N],ans;

int main()
{
	int i,inv;
	
	scanf("%d",&n);
	
	for (i=1;i<=n;++i)
	{
		scanf("%d",a+i);
		if (a[i]!=-1) ++cnt[a[i]];
		l[i]=l[i-1]+(a[i]==-1);
	}
	
	for (i=1;i<=n;++i)
	{
		cnt[i]+=cnt[i-1]; //求给定的数个数的前缀和 
	}
	
	inv=qpow(4,M-2);
	ans=(ll)l[n]*(l[n]-1)%M*inv%M; //第二种逆序对
	
	inv=qpow(l[n],M-2); //用l[n]代表tot，求出tot的逆元 
	
	for (i=n;i>=1;--i)
	{
		r[i]=r[i+1]+(a[i]==-1);
		if (a[i]!=-1)
		{
			ans=(ans+query(a[i]))%M; //第一种逆序对 
			add(a[i],1);
			ans=(ans+(ll)r[i]*(a[i]-cnt[a[i]])%M*inv%M)%M; //第三种逆序对
			ans=(ans+(ll)l[i]*(l[n]-a[i]+cnt[a[i]])%M*inv%M)%M; //第四种逆序对 
		}
	}
	
	printf("%d",ans);
	
	return 0;
}

int qpow(int x,int y)
{
	int out=1;
	while (y)
	{
		if (y&1) out=(ll)out*x%M;
		x=(ll)x*x%M;
		y>>=1;
	}
	return out;
}

void add(int p,int x)
{
	for (;p<=n;p+=(p&-p))
	{
		BIT[p]+=x;
	}
}

int query(int p)
{
	int out=0;
	for (;p>0;p-=(p&-p))
	{
		out+=BIT[p];
	}
	return out;
}
```

---

## 作者：Fanch100 (赞：3)

[原题地址](https://codeforces.com/problemset/problem/1096/F)

[luogu地址](https://www.luogu.com.cn/problem/CF1096F)

题意十分清晰，不再赘述。

### 分析

观察到一共有两种数字，确定的和不确定的，我们可以分成三种情况讨论逆序对贡献。

#### 1. 确定位置和确定位置之间的贡献

树状数组或归并直接求即可。

注意这一部分的逆序对是对每个排列都有贡献的，所以不用除以 $k!$。

#### 2. 不确定位置和不确定位置之间的逆序对贡献

由于题目保证给定的一定是一个排列，故不存在两个数字相同的情况。

设一共有 $k$ 个不确定的数字，问题可以转化为长度为 $k$ 的所有排列中的逆序对数量和。

注意到一个排列 $p_1,p_2,...p_{n}$ 中一共有 $ \dfrac{n\times(n-1)}{2}$ 个二元组 $(p_i,p_j)$  $(i < j)$，考虑翻转的排列 $p_{n},p_{n-1},...,p_1$ ，每个二元组会以相反的形式出现在翻转排列中，由于两个数字不相等，必然有且仅有一组贡献 $1$ 的逆序对数，所以两个排列一共的逆序对数便是 $ \frac{n\times(n-1)}{2}$。

一共有 $\frac{n!}{2}$ 种相反的排列，所以这一部分的总贡献是 $\frac{k \times (k-1) \times k!}{4}$。

注意这是总逆序对数量，要除以 $k!$。

#### 3. 确定位置和不确定位置间的逆序对贡献

假设我们枚举到第 $i$ 个位置，它前面有 $num$ 个不确定的位置（这表明后面共有 $k-num$ 个）。

二分或树状数组找到比 $p_i$ 小的并且未确定位置的数的个数，假设为 $m$。

那么每个比 $p_i$ 小的数有 $\frac{num}{k}$ 的概率在 $p_i$ 前面，每个比 $p_i$ 大的数有 $\frac{k-num}{k}$ 的概率在 $p_i$ 后面。

故这个位置的期望贡献为

$$\frac{m \times num}{k} + \frac{(k-m)\times(k-num)}{k}$$

对每个位置求和即可。

这里我们算的是概率，所以也不用除以 $k!$。

最后把三种情况的期望加起来即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200010;
const int mod = 998244353;
int n;
int a[N];
bool vis[N];
ll qpow(ll a,ll b){
    ll res=1;
    for (; b; b>>=1){
        if (b&1) res=res*a%mod;
        a=a*a%mod;
    }
    return res;
}
ll pro[N], inv[N], invn[N];
void init(){
    pro[0]=inv[0]=invn[0]=1;
    for (int i=1;i<=N-10;++i) pro[i]=pro[i-1]*i%mod;
    inv[N-10]=qpow(pro[N-10],mod-2);
    for (int i=N-11;i>=1;--i) inv[i]=inv[i+1]*(i+1)%mod;
    for (int i=N-10;i>=1;--i) invn[i]=inv[i]*pro[i-1]%mod;
}
int c[N];
void add(int x,int d){for (; x<=n; x+=x&-x) c[x]+=d;}
int ask(int x){int res=0; for (; x; x-=x&-x) res+=c[x]; return res;}
int main(){
    cin>>n;
    init();
    for (int i=1;i<=n;++i){
        cin>>a[i];
        if (a[i]>0) vis[a[i]]=1;
    }
    int k=0;
    for (int i=1;i<=n;++i){
        if (!vis[i]) add(i,1),k++;
    }
    ll inv2=qpow(2,mod-2);
    ll ans=pro[k]*inv2%mod*k%mod*(k-1)%mod*inv2%mod*inv[k]%mod;
    ll cnt=0;
    for (int i=n;i>=1;--i){
        if (a[i]==-1) cnt++;
        else{
            ll m=ask(a[i]);
            ll add1=cnt*invn[k]%mod*m%mod;
            ll add2=(k-cnt)*invn[k]%mod*(k-m)%mod;
            ans=(ans+add1+add2)%mod;
        }
    }
    memset(c,0,sizeof(c));
    for (int i=n;i>=1;--i){
        if (a[i]!=-1){
            ans=(ans+ask(a[i]))%mod;
            add(a[i],1);
        }

    }
    cout<<ans;
    return 0;
}
```

---

## 作者：λᴉʍ (赞：2)

$a_i=-1$的称为未知数，否则称为已知数

逆序对数分成3块考虑，两个已知数的逆序对，已知数和未知数的逆序对，两个未知数的逆序对。

两个已知数的逆序对，树状数组扫一遍即可

两个未知数的逆序对，设有$m$个未知数，每一对之间的逆序对数量期望都是$0.5$，所以这一块答案是$m(m-1)*0.25$

已知数和未知数的逆序对，也很简单，先把所有未知数算出来，求出每一个已知数大于多少个未知数，设为$cnt_i$

从左到右扫一遍所有的未知数，对于在左边的已知数，那个数必须大于这个未知数才能产生贡献，所以期望是$\frac{cnt_i}{m}$；右边的期望是$\frac{m-cnt_i}{m}$

所以扫到已知数的时候重新算这个已知数的贡献就好了

```cpp
#include<bits/stdc++.h>
#define il inline
#define vd void
#define mod 998244353
#define inv2 499122177
typedef long long ll;
il int gi(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int n,ans,A[200010],t[200010],B[200010],m;
bool yes[200010];
il vd update(int x){while(x<=n)++t[x],x+=x&-x;}
il int query(int x){int r=0;while(x)r+=t[x],x-=x&-x;return r;}
il int pow(int x,int y){
    int ret=1;
    while(y){
        if(y&1)ret=1ll*ret*x%mod;
        x=1ll*x*x%mod;y>>=1;
    }
    return ret;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    n=gi();
    for(int i=1;i<=n;++i)A[i]=gi();
    for(int i=n;i;--i)if(~A[i])ans=(ans+query(A[i]))%mod,update(A[i]);
    int cnt=0;for(int i=1;i<=n;++i)if(A[i]==-1)++cnt;
    ans=(ans+1ll*cnt*(cnt-1)%mod*inv2%mod*inv2%mod)%mod;
    if(cnt){
        for(int i=1;i<=n;++i)if(~A[i])yes[A[i]]=1;
        for(int i=1;i<=n;++i)if(!yes[i])B[++m]=i;
        int invm=pow(m,mod-2);
        for(int i=1;i<=n;++i)if(~A[i])A[i]=1ll*invm*(std::lower_bound(B+1,B+m+1,A[i])-B-1)%mod;
        int res=0;for(int i=1;i<=n;++i)if(~A[i])res=(res+1+mod-A[i])%mod;
        for(int i=1;i<=n;++i)
            if(~A[i])res=(res-1ll+A[i]+A[i])%mod;
            else ans=(ans+res)%mod;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：LJC00118 (赞：2)

分别计算 $ -1 $ 和 $ -1 $ 的贡献，$ -1 $ 和数字的贡献，数字和数字的贡献

第一个用 $ dp $ 求出，第二个用前缀和求出，第三个用树状数组求出

$ sb $ 的我能用前缀和的地方写了树状数组

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 2e5 + 5, md = 998244353;

inline int mul(int x, int y) { return (ll)x * y % md; }

inline int add(int x, int y) {
	x += y;
	if(x >= md) x -= md;
	return x;
}

inline int sqr(int x) { return mul(x, x); }

inline int fpow(int x, int y) {
	int ans = 1;
	while(y) {
		if(y & 1) ans = mul(ans, x);
		y >>= 1; x = sqr(x);
	}
	return ans;
}

int a[N], s[N], f[N], fac[N];
int n, inv2 = (md + 1) / 2, ans1;

inline int lowbit(int x) { return x & -x; }

void change(int x, int y) {
	for(register int i = x; i <= n; i += lowbit(i))
		f[i] += y;
}

int query(int x) {
	int ans = 0;
	for(register int i = x; i; i -= lowbit(i))
		ans += f[i];
	return ans;
}

int main() {
	read(n); fac[0] = 1;
	for(register int i = 1; i <= n; i++) read(a[i]), fac[i] = mul(fac[i - 1], i), s[i] = 1;
	for(register int i = n; i >= 1; i--) {
		if(a[i] == -1) continue;
		ans1 = add(ans1, query(a[i]));
		change(a[i], 1);
	}
	memset(f, 0, sizeof(f));
	for(register int i = 1; i <= n; i++) {
		if(a[i] != -1) s[a[i]] = 0;
	}
	for(register int i = 1; i <= n; i++) s[i] += s[i - 1];
	ans1 = mul(ans1, fac[s[n]]);
	for(register int i = 1; i <= s[n]; i++) f[i] = add(f[i - 1], mul(mul(fac[s[n]], fpow(i, md - 2)), mul(i - 1, mul(i, inv2))));
	ans1 = add(ans1, f[s[n]]); memset(f, 0, sizeof(f));
	for(register int i = 1; i <= n; i++) if(a[i] == -1) change(i, 1);
	for(register int i = 1; i <= n; i++) {
		if(a[i] == -1) continue;
		int val = mul(s[a[i]], query(n) - query(i));
		val = add(val, mul(s[n] - s[a[i]], query(i)));
		val = mul(val, fac[s[n] - 1]);
		ans1 = add(ans1, val);
	}
	print(mul(ans1, fpow(fac[s[n]], md - 2)), '\n');
	return 0;
}
```


---

## 作者：wizardMarshall (赞：1)

## 题意

给定一个未完全填满的排列，求逆序对期望个数。

## 思路

可以针对每一种情况分类讨论。

### 已填与已填

与逆序对模版并无二异，直接计算即可。

### 未填与未填

将其单独提取出来思考，随即取两个数，前面大于后面的概率是 $\dfrac{1}{2}$，因此设未填的个数总共有 $cnt$ 个，则答案为 $\dfrac{cnt(cnt-1)}{2} \times \dfrac{1}{2}=\dfrac{cnt(cnt-1)}{4}$。

### 已填与未填

我们考虑已填的数 $a_i$，前面有 $c_1$ 个空位，后面有 $c_2$ 个空位。假设还未填的数中有 $k_1$ 个数比 $a_i$ 小，$k_2$ 个数比 $a_i$ 大。

首先考虑一个还未填的数填到前面的概率为 $\dfrac{c_1}{c_1+c_2}$。而能跟 $a_i$ 构成逆序对的只有比 $a_i$ 大的数，因此总的贡献为 $\dfrac{c_1k_2}{c_1+c_2}$。

填到后面同理，贡献为 $\dfrac{c_2k_1}{c_1+c_2}$。

$c_1$ 及其他变量均可以使用数据结构维护。

（值得注意的是 $c_1+c_2$ 不变，可以用 $cnt$ 代替，不必重复计算逆元）

## 代码

代码变量与上文稍有出入。

实现细节：这里两次计算（一次是逆序对，一次是比 $a_i$ 大或小的数）都使用了线段树，第二次记录的是未填的数，恰好和第一次相反，因此线段树取反即可。（或直接沿用第一次的线段树，用区间长度减等等方法均可以）

```c++

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int p = 998244353;
int a[200005];
int sum[800005];
void build(int l, int r, int x) {//取反
	sum[x] = (r - l + 1) - sum[x];//将已填的设为0，未填的记为1，方便下文计算
	if (l == r)return;
	int m = (l + r) / 2;
	build(l, m, x * 2);
	build(m + 1, r, x * 2 + 1);
    return;
}

void change(int id, int l, int r, int x) {//单点更新
	if (l == r) {
		sum[x]++;
		return;
	}
	int m = (l + r) / 2;
	if (id <= m) {
		change(id, l, m, x * 2);
	}else {
		change(id, m + 1, r, x * 2 + 1);
	}sum[x] = sum[x * 2] + sum[x * 2 + 1];
    return;
}

int ask(int L, int R, int l, int r, int x) {//查询区间总和
	if (L <= l && r <= R) {
		return sum[x];
	}
	int m = (l + r) / 2;
	int ret = 0;
	if (L <= m) {
		ret += ask(L, R, l, m, x * 2);
	}if (R > m) {
		ret += ask(L, R, m + 1, r, x * 2 + 1);
	}return ret;
}
int pw(int a, int b) {
	int sum = 1;
	while (b) {
		if (b & 1) {
			sum *= a;
			sum %= p; 
		}a *= a;
		a %= p;
		b = (b >> 1);
	}return sum;
}
signed main() {
	int n;
	cin >> n;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		if (a[i] == -1) {
			cnt++;
		}
	}
	int ans = (((cnt * (cnt - 1)) % p) * pw(4, p - 2)) % p;//情况二，未填之间的逆序对
	for (int i = 1; i <= n; i++) {
		if (a[i] == -1)continue;
		if (a[i] != n)ans += ask(a[i] + 1, n, 1, n, 1);//线段树计算逆序对，这里采用合适的算法均可
		change(a[i], 1, n, 1);
	}
	build(1, n, 1);//取反
	int cc = 0, nc = pw(cnt, p - 2);//预处理逆元
	for (int i = 1; i <= n; i++) {
		if (a[i] == -1) {//前面-1个数
			cc++;
			continue;
		}
		if (a[i] != n) {
			ans += (((ask(a[i] + 1, n, 1, n, 1) * cc) % p) * nc) % p;//上文计算
			ans %= p;
		}
		if (a[i] != 1) {
			ans += (((ask(1, a[i] - 1, 1, n, 1) * (cnt - cc)) % p) * nc) % p;//c_2=cnt-c_1
			ans %= p;
		}
	}
	cout << ans;
    return 0;
}

```

---

## 作者：KokiNiwa (赞：1)

# CF1096F

Inversion Expectation

## 题目叙述

给你一个扣掉了一些数的全排列。问你这个全排列如果加上那些扣掉的数，逆序对数的期望。

## 题解

答案即为$E(\sum_{i=1}^{n-1}\sum_{j=i+1}^n a_i>a_j)$。

考虑把逆序对分为三种：

1. 两个未知数的逆序对
2. 一个未知数何一个已知数的逆序对
3. 两个已知数的逆序对

前两种推式子，最后一种树状数组即可。

## 知识点

+ Fading 叫这个计算贡献...可能有点像是？不知道

---

## 作者：Lotus_Land (赞：0)

已知的数之间的逆序对可以用树状数组求。

未知的数之间的逆序对：设未知数个数为 $k$，每对未知数产生或不产生贡献的概率都是 $\frac{1}{2}$，故未知的数之间的逆序对数期望为 $\frac{1}{2}C_{k}^2$。

对每个已知的数 $x$ 考虑，设它的左边有 $p$ 个未知数，它左边的未知数需要比 $x$ 大才能产生贡献。设比 $x$ 大**且没有被选**的数有 $m$ 个，则产生贡献的期望为 $p\times \frac{m}{k}$。右边同理。$m$ 可用前面求逆序对留下来的树状数组的数据计算。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define mkpr make_pair
#define fir first
#define sec second
#define lc(p) ((p)*2)
#define rc(p) ((p)*2+1)
using namespace std;
inline LL read() {
	LL x=0;
	bool t=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')t|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return t?-x:x;
}
const LL mod=998244353;
const int N=200005;
int n,a[N];
int lowbit(int x) {
	return x&-x;
}
LL tr[N];
void Add(int x,int v) {
	while(x<=n) {
		tr[x]+=v;
		x+=lowbit(x);
	}
}
LL query(int x) {
	LL res=0;
	while(x>0) {
		res+=tr[x];
		x-=lowbit(x);
	}
	return res;
}
LL qpow(LL a,int b=mod-2) {
	LL res=1;
	while(b) {
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
LL cnt,sum,ans;
int main() {
	n=read();
	for(int i=1; i<=n; i++)a[i]=read();
	for(int i=n; i>=1; i--) {
		if(a[i]!=-1) {
			sum+=query(a[i]);
			sum%=mod;
			Add(a[i],1);
		} else cnt++;
	}
	ans=(sum+cnt*(cnt-1)%mod*qpow(4)%mod)%mod;
	LL p=0;
	for(int i=1; i<=n; i++) {
		if(a[i]==-1)p++;
		else (ans+=p*(cnt+query(a[i])-a[i])%mod*qpow(cnt))%=mod;
	}
	p=0;
	for(int i=n; i>=1; i--) {
		if(a[i]==-1)p++;
		else (ans+=p*(a[i]-query(a[i]))%mod*qpow(cnt))%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有一个长度为 $n$ 的序列 $p$，我们定义一个排列 $q$ 是满足条件的，当且仅当：

* 对于 $p_i\neq -1$，有 $q_i=p_i$。

求随机选择一个满足条件的排列 $q$ 的期望逆序对数。保证至少存在一个满足条件的 $q$。

$1\leq n\leq 2\times10^5$。

## 思路

逆序对数的性质是除了逆序对中的两个数外，其他数不影响逆序是否成立。根据期望的线性性，我们先将期望转成计数，然后分情况讨论每种逆序对数总和。

**Case 1**：对于逆序对 $(q_i,q_j)$，有 $p_i\neq -1,p_j\neq -1$。

这种情况就是传统的逆序对计数，树状数组即可。记得由于每个这种情况的逆序对都会对所有 $q$ 产生贡献，所以答案要乘以 $m!$。$m$ 指 $p$ 中 $-1$ 的数量。

**Case 2**：对于逆序对 $(q_i,q_j)$，有 $p_i=p_j=-1$。

不妨考虑枚举 $q_i,q_j$ 这两个数的取值，这样的取值对一共有 $\binom{m}{2}$ 种。然后考虑如何将其放到排列中去，首先我们要选出两个位置按照顺序把这两个元素放进去，这有 $\binom{m}{2}$ 种方案，剩下的位置随便填，有 $(m-2)!$ 种方案。所以总方案数就是：

$$
\binom{m}{2}^2(m-2)!
$$

**Case 3**：对于逆序对 $(q_i,q_j)$，有 $i<j,q_i>q_j,p_i\neq -1,p_j=-1$。

考虑我们枚举 $q_j$，设需要填进排列中的元素集合为 $S$，则可以看成我们在算这个：

$$
(m-1)!\sum_{t\in S}\sum_{k=1}^{j-1}[t > q_k]
$$

这玩意计算需要用线段树，比较麻烦。考虑枚举 $q_i$ 去累计贡献，每次相当于会对接下来的 $q_j$ 产生 $X_i(m-1)!$ 的贡献，其中 $X_i$ 为 $S$ 中小于 $q_i$ 的元素数量。这个用一个变量就可以统计。

最后的问题是如何求 $X_i$，可以将 $S$ 中所有元素插入到权值树状数组中，那么 $X_i$ 可以看成求前缀和。

**Case 4**：对于逆序对 $(q_i,q_j)$，有 $i>j,q_i<q_j,p_i\neq -1,p_j=-1$。

只需要将 Case 3 的过程倒着做一遍即可。

时间复杂度 $O(n\log n)$ 可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 2e5 + 5, mod = 998244353;
int n, m, a[N], fact[N], ans, t[N], inv[N];
bool vis[N];
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }
int binom(int x, int y){
    if(x < y || x < 0 || y < 0) return 0;
    return Mul(fact[x], Mul(inv[y], inv[x - y]));
}

void update(int p, int v){
    for(;p<=n;p+=lowbit(p)) t[p] += v;
}

int query(int p){
    int res = 0;
    for(;p;p-=lowbit(p)) res += t[p];
    return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    fact[0] = fact[1] = inv[0] = inv[1] = 1;
    for(int i=2;i<=n;i++){
        fact[i] = Mul(fact[i-1], i);
        inv[i] = Mul(inv[mod % i], mod - mod / i);
    }
    for(int i=2;i<=n;i++) inv[i] = Mul(inv[i-1], inv[i]);
    m = count(a + 1, a + n + 1, -1);
    // 第一部分
    int tmp = 0;
    for(int i=1;i<=n;i++){
        if(a[i] == -1) continue;
        tmp = Add(tmp, query(n) - query(a[i]));
        update(a[i], 1);
    }
    ans = Add(ans, Mul(tmp, fact[m]));
    // 第二部分
    if(m >= 2) ans = Add(ans, Mul(binom(m, 2), Mul(binom(m, 2), fact[m - 2])));
    if(m >= 1){
        // 第三部分
        fill(t + 1, t + n + 1, 0);
        for(int i=1;i<=n;i++){
            if(a[i] != -1) vis[a[i]] = 1;
        }
        for(int i=1;i<=n;i++){
            if(vis[i] == 0) update(i, 1);
        }
        tmp = 0;
        for(int i=1;i<=n;i++){
            if(a[i] != -1) tmp = Add(tmp, Mul(fact[m - 1], query(a[i])));
            else ans = Add(ans, tmp);
        }
        // 第四部分
        tmp = 0;
        for(int i=n;i;i--){
            if(a[i] != -1) tmp = Add(tmp, Mul(fact[m - 1], query(n) - query(a[i])));
            else ans = Add(ans, tmp);
        }
    }
    ans = Mul(ans, inv[m]);
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

