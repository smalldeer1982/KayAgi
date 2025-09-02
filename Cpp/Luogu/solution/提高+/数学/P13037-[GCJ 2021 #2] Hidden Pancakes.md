# [GCJ 2021 #2] Hidden Pancakes

## 题目描述

我们总共要烹饪 $\mathbf{N}$ 张煎饼。这些煎饼的半径分别为 $1$ 厘米（cm）、$2 \mathrm{~cm}$、$3 \mathrm{~cm}$，……，以及 $\mathbf{N} \mathrm{cm}$，但烹饪顺序不一定按半径从小到大排列。烹饪完第一张煎饼后，我们直接将其放在盘子上。之后每烹饪完一张煎饼，就将其叠放在之前所有煎饼的最上方，且所有煎饼的中心对齐。这样，每张煎饼在刚被加入时都能从顶部被看到。只有当之后烹饪了比它半径更大的煎饼时，这张煎饼才会被隐藏。

例如，假设我们烹饪 4 张煎饼。首先烹饪半径为 $3 \mathrm{~cm}$ 的煎饼，此时它可见。接着烹饪半径为 $1 \mathrm{~cm}$ 的煎饼，叠放在第一张煎饼上，此时两张煎饼都可见。然后烹饪半径为 $2 \mathrm{~cm}$ 的煎饼，它会覆盖前一张煎饼（半径为 $1 \mathrm{~cm}$ 的煎饼），但不会覆盖第一张煎饼，因此此时共有 2 张煎饼可见。最后，烹饪半径为 $4 \mathrm{~cm}$ 的煎饼，它会覆盖所有其他煎饼，此时只有 1 张煎饼可见。下图展示了每张煎饼被烹饪后叠放的状态，其中完全不透明的煎饼表示可见，半透明的煎饼表示不可见。

![](https://cdn.luogu.com.cn/upload/image_hosting/s69k9evw.png)

设 $\mathbf{V}_{\mathbf{i}}$ 表示叠放了恰好 $i$ 张煎饼时可见的煎饼数量。在上面的例子中，$\mathbf{V}_{1}=1$、$\mathbf{V}_{2}=2$、$\mathbf{V}_{3}=2$、$\mathbf{V}_{4}=1$。

给定列表 $\mathbf{V}_{1}, \mathbf{V}_{2}, \ldots, \mathbf{V}_{\mathbf{N}}$，问在所有 $\mathbf{N} !$ 种可能的烹饪顺序中，有多少种顺序能恰好得到给定的 $\mathbf{V}_{\mathbf{i}}$ 序列？由于结果可能非常大，只需输出结果对质数 $10^{9}+7$（即 $1000000007$）取模后的值。


## 说明/提示

**样例解释**

样例 #1 已在题目描述中说明，唯一的满足条件的烹饪顺序是 $3,1,2,4$。

在样例 #2 中，顺序 $1,3,2$ 和 $2,3,1$ 均能满足给定的 $\mathbf{V}_{\mathbf{i}}$ 序列。下图展示了这两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/o981r60x.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/3vhqt53k.png)

在样例 #3 中，叠加第二张煎饼后只有 1 张煎饼可见，因此无法通过叠加第三张煎饼使可见煎饼数量超过 2。

样例测试集 2 符合测试集 2 的限制条件，但提交的解法不会实际运行该测试集。

在测试集 2 的样例中，共有 $316234143225$ 种烹饪顺序满足给定的 $\mathbf{V}_{\mathbf{i}}$ 序列，对 $10^{9}+7$ 取模后的结果是 $234141013$。

**限制条件**

- $1 \leq \mathbf{T} \leq 100$。
- 对于所有 $i$，$1 \leq \mathbf{V}_{\mathbf{i}} \leq i$。

**测试集 1（可见判定）**

- 时间限制：30 秒。
- $2 \leq \mathbf{N} \leq 13$。

**测试集 2（隐藏判定）**

- 时间限制：40 秒。
- $2 \leq \mathbf{N} \leq 10^{5}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
4
1 2 2 1
3
1 1 2
3
1 1 3```

### 输出

```
Case #1: 1
Case #2: 2
Case #3: 0```

## 样例 #2

### 输入

```
1
24
1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2```

### 输出

```
Case #1: 234141013```

# 题解

## 作者：_LDX_WWS_ (赞：6)

首先考虑什么时候会出现在 $v_i$ 中出现 1，能够想到出现在一段区间能最大的饼就会产生一个 1 由此可以发现，最后一个出现在 $v_i$ 中的 1 就是最大的饼。那受这个思路的启发，我们可以考虑分治，按照这个 1 的位置分成两块进行计算，在前面一段，就去找寻新的最右边的 1，在左边就去找最右边的 2（因为已经有一个最大的饼在下面垫着了）。以此类推，我们假设左边获得了一个方案数 $ans_1$，右边一个方案数 $ans_2$，假设这一段区间为 $[l,r]$，这里的分割点为 $p$（就是最大的饼所在的位置），那么两端其实就是将这 $r-l+1$ 个大小不同的饼分到两边了，因为我们只关心相对大小，所以这个子段的答案就是 $ans=ans_1 \times ans_2 \times \binom{r-l+1}{p-l}$。

那么接下来的问题就是如何快速找到区间内最大的要找的数了，我们这里使用桶来解决，具体而言，我们在桶中按顺序存 $i$ 的值，在找寻时，只需要二分就可以了，具体可以参考代码。

综合复杂度 $O(n \log (n))$ 很轻松就可以通过。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-') f=-1;
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f*x;
}
const int N=1e5+10,M=1e9+7;
int T,n,v[N];
inline int quick_power(int x,int p){
	int res=1,base=x;
	while(p){
		if(p&1) res*=base,res%=M;
		base*=base;base%=M;
		p=(p>>1);
	}
	return res;
}
int fac[N];
inline int ny(int x){
	return quick_power(x,M-2);
}
inline int getC(int x,int y){
	if(y==0) return 1;
	if(x==y)return 1;
	return ((fac[x]*ny(fac[y]))%M*ny(fac[x-y]))%M;
}
vector<int> ha[N];
int ef(int x,int w){
	int l=1,r=ha[x].size()-1,s=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ha[x][mid]<=w){
			l=mid+1;s=mid;
		}
		else r=mid-1;
	}
	return s;
}
int dfs(int l,int r,int fx){
	if(l>r) return 1;
	int ad=ef(fx,r);
	if(ad==-1) return 0;
	ad=ha[fx][ad];
	if(ad<l) return 0;
	int res1=dfs(l,ad-1,fx),res2=dfs(ad+1,r,fx+1);
	return (((getC(r-l,ad-l)*res1)%M)*res2)%M;
}
signed main(){
	T=read();
	fac[0]=1;
	for(int i=1;i<=N-10;i++) fac[i]=fac[i-1]*i,fac[i]%=M; 
	for(int t=1;t<=T;t++){
		n=read();
		for(int i=1;i<=n;i++) ha[i].clear(),ha[i].push_back(0);
		for(int i=1;i<=n;i++) v[i]=read(),ha[v[i]].push_back(i);
		cout<<"Case #"<<t<<": "<<dfs(1,n,1)<<endl;
	}
	return 0;
}

```

---

## 作者：IC0CI (赞：0)

# 题面分析

一个饼能不能被看见只有关这个饼和他上面所有饼的相对大小。

考虑分治。

全部放好后能看见的饼中最下面一个就是目前最大的饼，而最大的饼上下的饼分属两部分，因为只考虑相对大小的缘故最终的 $V$ 数组不关心上下具体是哪些饼。于是对于当前的最大饼，其产生的贡献是 $\binom{n}{m}$，其中 $n$ 表示目前除最大饼外所有饼，$m$ 是上部分或下部分的个数。

至于定位最大的饼就是目前 $[l,r]$ 中最靠右的 $1$，线段树维护或二分套线段树。

## 关于具体实现

注意分治到 $[l,pos - 1]$ 和 $[pos + 1,r]$ 时右边部分所有 $V$ 值应减少 $1$。

## Code

$O(n\log_2^3{n})$ 二分套线段树做法。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>

int rd()
{
    int x = 0,w = 1;
    char ch = 0;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * w;
}

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int qpow(int a,int b)
{
    int ans = 1;
    while(b)
    {
        if(b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

int T;
int n,a[N],fac[N],inv[N];

int C(int n,int m){ return fac[n] * inv[m] % mod * inv[n - m] % mod;}

#define ls (p << 1)
#define rs (ls | 1)
#define mid ((pl + pr) >> 1)

int t[N << 2];

void pu(int p) { t[p] = min(t[ls],t[rs]); }

void build(int p,int pl,int pr)
{
    if(pl == pr) return (void)(t[p] = a[pl]);
    build(ls,pl,mid);
    build(rs,mid + 1,pr);
    pu(p);
}

int qry(int p,int pl,int pr,int l,int r)
{
    if(l <= pl && pr <= r) return t[p];
    if(r <= mid) return qry(ls,pl,mid,l,r);
    if(l > mid) return qry(rs,mid + 1,pr,l,r);
    return min(qry(ls,pl,mid,l,r),qry(rs,mid + 1,pr,l,r));
}

int check(int pl,int pr,int mi)
{
    int ans = 0;
    while(pl <= pr)
    {
        if(qry(1,1,n,mid,pr) == mi) ans = mid,pl = mid + 1;
        else pr = mid - 1;
    }
    return ans;
}

int ans;

void fz(int l,int r,int mi)
{
    if(l >= r) return;
    int pos = check(l,r,mi);
    fz(l,pos - 1,mi);
    fz(pos + 1,r,mi + 1);
    ans = ans * C(r - l,pos - l) % mod;
    return;
}

void solve()
{
    ans = 1;
    n = rd();
    for(int i = 1;i <= n;i++) a[i] = rd();
    for(int i = 1;i <= n;i++) if(a[i] - a[i - 1] > 1) return (void)(cout << "0\n");
    build(1,1,n);
    fz(1,n,1);
    cout << ans << '\n';
}

signed main()
{
    T = rd();
    fac[0] = inv[0] = 1;
    for(int i = 1;i <= 100000;i++) fac[i] = fac[i - 1] * i % mod;
    inv[100000] = qpow(fac[100000],mod - 2);
    for(int i = 99999;i >= 0;i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    for(int t = 1;t <= T;t++)
    {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
```

$O(n\log_2^2{n})$ 线段树做法。 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>

int rd()//快读

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int qpow(int a,int b)
{
    int ans = 1;
    while(b)
    {
        if(b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

int T;
int n,a[N],fac[N],inv[N];

int C(int n,int m){ return fac[n] * inv[m] % mod * inv[n - m] % mod;}

#define ls (p << 1)
#define rs (ls | 1)
#define mid ((pl + pr) >> 1)

pii t[N << 2];

pii mymin(pii l,pii r) { return (l.first == r.first ? (l.second > r.second ? l : r) : (l.first < r.first ? l : r)); }

void pu(int p) { t[p] = mymin(t[ls],t[rs]); }

void build(int p,int pl,int pr)
{
    if(pl == pr) return (void)(t[p] = {a[pl],pl});
    build(ls,pl,mid);
    build(rs,mid + 1,pr);
    pu(p);
}

pii qry(int p,int pl,int pr,int l,int r)
{
    if(l <= pl && pr <= r) return t[p];
    if(r <= mid) return qry(ls,pl,mid,l,r);
    if(l > mid) return qry(rs,mid + 1,pr,l,r);
    return mymin(qry(ls,pl,mid,l,r),qry(rs,mid + 1,pr,l,r));
}

int ans;

void fz(int l,int r,int mi)
{
    if(l >= r) return;
    int pos = qry(1,1,n,l,r).second;
    fz(l,pos - 1,mi);
    fz(pos + 1,r,mi + 1);
    ans = ans * C(r - l,pos - l) % mod;
    return;
}

void solve()
{
    ans = 1;
    n = rd();
    for(int i = 1;i <= n;i++) a[i] = rd();
    for(int i = 1;i <= n;i++) if(a[i] - a[i - 1] > 1) return (void)(cout << "0\n");
    build(1,1,n);
    fz(1,n,1);
    cout << ans << '\n';
}

signed main()
{
    T = rd();
    fac[0] = inv[0] = 1;
    for(int i = 1;i <= 100000;i++) fac[i] = fac[i - 1] * i % mod;
    inv[100000] = qpow(fac[100000],mod - 2);
    for(int i = 99999;i >= 0;i--) inv[i] = inv[i + 1] * (i + 1) % mod;
    for(int t = 1;t <= T;t++)
    {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
```

---

## 作者：qiuqiuhome (赞：0)

首先这道题一眼排列计数。

然后考虑最大的煎饼所在位置。

不难发现最大的煎饼就是在最右边的 $1$ 的位置。

感性证明一下，最大的煎饼覆盖完之后肯定是 $1$ 而且不能在被覆盖，也就是后面都会 $+1$ 所以后面的至少为 $2$。

所以以最大的煎饼为分界点，将序列分成两段，对右半段 $-1$ 以去除影响，最后递归解决

一次划分对答案的贡献为 $\binom{N}{K}$ 其中 $N$ 是整个序列的长度（不包括最大煎饼），$K$ 是划分出的一段的长度，可以这样理解，因为整个序列被分成了不相关的两段，而我们只在乎煎饼的相对大小，所以要选 $K$ 个煎饼放在其中一段中。

所以共有 $\binom{N}{K}$ 种方案。

找最大的煎饼也就是找区间最右边的 $1$，使用线段树维护。

时间复杂度约为 $\mathcal{O}(n\log^2(n))$

实现时，维护最小值可以不对右半段 $-1$，因为相对大小不变。

# CODE

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+20,mod=1e9+7;

int qpow(int a,int b,int md){
	if(a==0)return 0;
	int ans=1;
	while(1){
		if(b==0)break; 
		if(b&1)ans=(ans*a)%md;
		a=a*a%md;
		b>>=1;
	}
	return ans;
}
int fc[N+10],infc[N+10]; 

int C(int n,int m){
	return fc[n]%mod*infc[m]%mod*infc[n-m]%mod;
}
void init(){
	fc[0]=infc[0]=1;
	for(int i=1;i<=N;i++)
		fc[i]=fc[i-1]*i%mod,
		infc[i]=qpow(fc[i],mod-2,mod)%mod;
}

int n;
int wh[N*4],a[N];
#define mid ((l+r)>>1)
void build(int p,int l,int r){
	if(l==r){wh[p]=l;return;}
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	if(a[wh[p*2]]<a[wh[p*2+1]])wh[p]=wh[p*2];
	else wh[p]=wh[p*2+1];//右边优先
}
void clear__(int p,int l,int r){
	if(l==r){wh[p]=0;return;}
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	wh[p]=0;
}
int ask(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R){return wh[p];}
	int ans1=0,ans2=0;
	if(L<=mid)ans1=ask(p*2,l,mid,L,R);
	if(mid+1<=R)ans2=ask(p*2+1,mid+1,r,L,R);
	if(ans1==0||ans2==0)return ans1+ans2;
	if(a[ans1]<a[ans2])return ans1;
	return ans2;
}
int ans=1;
void f(int l,int r){
	if(l>=r)return;
	int w=ask(1,1,n,l,r);
	f(l,w-1);
	f(w+1,r);
	ans=(ans*C(r-l,w-l))%mod;
}
int one(){
	ans=1;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]-a[i-1]>1||a[i]>i)ans=0;
	}
	if(ans==0)return 0;
	build(1,1,n);
	f(1,n);
	return ans;
}
signed main(){
	init();
	int T;
	scanf("%lld",&T);
	for(int i=1;i<=T;i++){
		printf("Case #%lld: %lld\n",i,one());
	}
	return 0;
}
```

---

