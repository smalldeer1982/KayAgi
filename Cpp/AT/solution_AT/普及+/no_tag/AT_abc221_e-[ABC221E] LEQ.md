# [ABC221E] LEQ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc221/tasks/abc221_e

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ が与えられます。

$ A $ の連続するとは限らない、長さが $ 2 $ 以上である部分列 $ A'=(A'_1,A'_2,\ldots,A'_k) $ のうち以下の条件を満たすものの個数を求めてください。

- $ A'_1\ \leq\ A'_k $

なお、この値は非常に大きくなることがあるため、$ 998244353 $ で割ったあまりを出力してください。

ただし、$ 2 $ つの部分列は、列として同じであっても、取り出す添字が異なる場合は区別されます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ A=(1,2,1) $ の連続するとは限らない、長さが $ 2 $ 以上である部分列は $ (1,2) $, $ (1,1) $, $ (2,1) $, $ (1,2,1) $ の $ 4 $ 通りあります。 そのうち問題文中の条件を満たすものは、$ (1,2) $, $ (1,1) $, $ (1,2,1) $ の $ 3 $ 通りです。

### Sample Explanation 2

列として同じであっても、取り出す添字が異なる場合 $ 2 $ つの部分列は区別されることに注意してください。 この入出力例において、問題文中の条件を満たすような部分列は $ (1,2) $, $ (1,2) $, $ (2,2) $, $ (1,2,2) $ の $ 4 $ 通りです。

### Sample Explanation 3

問題文中の条件を満たすような部分列が存在しない場合もあります。

## 样例 #1

### 输入

```
3
1 2 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 2 2```

### 输出

```
4```

## 样例 #3

### 输入

```
3
3 2 1```

### 输出

```
0```

## 样例 #4

### 输入

```
10
198495780 28463047 859606611 212983738 946249513 789612890 782044670 700201033 367981604 302538501```

### 输出

```
830```

# 题解

## 作者：Shunpower (赞：4)

## 思路

考虑任意一对 $(i,j)$ 满足 $a_i\leqslant a_j$，明显的，下标在 $[i+1,j-1]$ 中的元素可以随便选，反正最终都会为答案做出贡献。因此，对于这样一对 $(i,j)$，对答案的贡献为 $2^{j-i-1}$。

考虑枚举 $j$，则前面有许多个下标 $i$ 可以满足 $a_i\leqslant a_j$。不妨令所有满足条件的下标 $i$ 构成的集合为 $S$，则对于这个 $j$，答案可以转化：

$$
\begin{aligned}
\sum\limits_{i\in S} 2^{j-i-1}&=2^j\times \sum\limits_{i\in S} 2^{-i-1}\\
&=2^j\times\sum\limits_{i\in S} (\frac{1}{2})^{i+1}\\
&=2^j\times\sum\limits_{i\in S} \frac{1}{2^{i+1}}
\end{aligned}
$$

在 $\bmod M$ 的情况下，我们需要使用乘法逆元，因此原来的答案继续变为：

$$
\begin{aligned}
2^j\times\sum\limits_{i\in S} \frac{1}{2^{i+1}}=2^j\times\sum\limits_{i\in S} \text{inv}(2^{i+1})
\end{aligned}
$$

注意到右边的和式需要我们对所有满足 $a_i\leqslant a_j$ 的 $i$ 的 $\text{inv}(2^{i+1})$ 取和。不妨离散化后权值线段树，并且动态加入逆元。注意加入必须是单点加的形式而不是覆盖原位置上的数，因为可能有多个 $a_i$ 相等。

## 代码

```
int n;
int a[N],tot;
const int V=3e5;
map <int,int> p;
set <int> s;
int ans;
#define mid (l+r>>1)
struct Segment_Tree{
	int sum[N<<2];
	void pushup(int p){
		sum[p]=sum[p<<1]+sum[p<<1|1];
		sum[p]%=M;
	}
	void insert(int p,int l,int r,int d,int x){
		if(l==r){
			sum[p]+=x%M;
			sum[p]%=M;
			return;
		}
		if(d<=mid){
			insert(p<<1,l,mid,d,x);
		}
		else{
			insert(p<<1|1,mid+1,r,d,x);
		}
		pushup(p);
	}
	int query(int p,int l,int r,int ml,int mr){
		if(ml>mr){
			return 0;
		}
		if(ml<=l&&r<=mr){
			return sum[p];
		}
		int ans=0;
		if(ml<=mid){
			ans+=query(p<<1,l,mid,ml,mr);
		}
		if(mid<mr){
			ans+=query(p<<1|1,mid+1,r,ml,mr);
		}
		return ans%M;
	}
} T;//普通线段树，包括单点加和区间查询
#undef mid
ll qpow(ll b,ll p,ll k){
	if(!p){
		return 1;
	}
	ll d=qpow(b,p>>1,k);
	if(p&1){
		return d*d%k*b%k;
	}
	else{
		return d*d%k;
	}
}
ll inv(ll x){
	return qpow(x,M-2,M);//费马小定理
}
signed main(){
#ifdef Griffin
	freopen("hack.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	cin>>n;
	fr1(i,1,n){
		cin>>a[i];
		s.insert(a[i]);
	}
	for(auto d:s){
		if(!p.count(d)){
			tot++;
			p[d]=tot;
		}
	}
	fr1(i,1,n){
		a[i]=p[a[i]];
	}//离散化
	fr1(i,1,n){
		ll d=qpow(2,i,M);
		ll g=T.query(1,1,V,1,a[i]);//逆元和
		ans+=d*g%M;//加上此位置贡献的答案
		ans%=M;
		T.insert(1,1,V,a[i],qpow(inv(2),i+1,M));//动态加入
	}
	cout<<ans<<endl;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/108351120)

---

## 作者：2huk (赞：3)

> 给定一个长度为 $n$ 的序列 $a_1 \dots a_n$。问有多少个长度大于 $1$ 的子序列满足子序列的首项小于等于末项。

最暴力的肯定是 $\mathcal O(2^n)$。

稍微好点的，我们可以枚举子序列的首项 $a_i$ 和末项 $a_j$，当然首先需要满足 $i < j$ 且 $a_i \le a_j$。那么 $[i + 1, j - 1]$ 内的元素肯定是任意选，也就是说有 $2^{j - i - 1}$ 种方案。也就是说答案为：
$$
\sum_{i = 1}^{n - 1} \sum _{j = i + 1}^n [a_i \le a_j] \times 2^{j - i - 1}
$$
这是 $\mathcal O(n^2)$ 的（不计快速幂）。

然后发现 $i < j$ 且 $a_i \le a_j$ 就是顺序对，然后我们尝试把上面那个式子改成可以树状数组优化的形式。
$$
\begin{aligned} \sum_{i = 1}^{n - 1} \sum _{j = i + 1}^n [a_i \le a_j] \times 2^{j - i - 1} &= \sum_{i = 1}^{n - 1} \sum _{j = i + 1}^n [a_i \le a_j] \times 2^{j - 1} \times 2^{-i} \\ &= \sum_{i = 1}^{n - 1} \left( 2^{-i} \times \sum _{j = i + 1}^n [a_i \le a_j] \times 2^{j - 1}\right)\end{aligned}
$$


这个东西就很好维护了。维护权值树状数组。用 $T_x = \sum_{a_i = x} 2^{i - 1}$，然后每次求 $\sum_{1 \le k \le a_j} T_k$ 即可。

这个东西用到了求后缀和和单点修改，树状数组即可。

[代码](https://atcoder.jp/contests/abc221/submissions/49237822)。

---

## 作者：lhz2022 (赞：1)

根据题意，不难想到使用归并排序。

根据题意，因为序列只要求一首一尾的数量关系，假设所有首为 $i$，尾为 $j$ 的序列的贡献为 $v$，易得

$v=2^{j-i-1}$。

也就是说，我们要求的 ans 可以表达成

 $ans= \sum_{i=1}^{n-1}{ \sum_{j=i+1}^{n}{[a[i]\leq a[j]] \times2^{j-i-1}}}$。

这里的 $[a[i]\leq a[j]] \times2^{j-i-1}$ 是顺序对，只需稍微改改代码即可。


 如果考虑这一组数列
 $[1,2,7,8,5,6,3,4]$，
 
假设已经到了这一步（只算这一步的贡献）
$[1,2,7,8][3,4,5,6]$，

那么对于位于后面一半的 $3$，我们可以得出它此次的贡献为前面一半所有小于 $3$ 的数字，即：

$2^{5-1-1}+2^{5-2-1}$。

提取公因式，得

$2^{5}\times2^{-1}\times(2^{-1}+2^{-2}+2^{-3})$。

显然，这个5指的是计算此次贡献的元素 $3$ 下标，且后面的都是 $x^{满足条件下标的相反数}$ 的和，并且对于 $5$ 后面的几个数字，它的贡献也只是把  $2^{5}$ 变成了 $2^{6}$，并且在后面增加了几项而已（如果有）。

只需要把这坨东西累加到 ans 上就并输出就可以了。

于是通过将归并排序的模板适当修改，就可以~~轻松~~的写出这坨AC代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300007
#define M 998244353
#define int long long
int ans;
int n,qj[N];
pair<int,int> b[N],a[N];
int ksm(int a,int b){
	int sum=1;
	a=a%M;
	while(b>0){
		if (b%2==1)	sum=(sum*a)%M;
		b/=2;
		a=(a*a)%M;
	}
	return sum;
}
void msort(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	msort(l,mid),msort(mid+1,r);//递归 下面的讨论是计算两个不同的区间贡献的，这两个区间的贡献在下面已经算完了
	qj[r+1]=0;
	for(int i=r;i>=l;--i){
		qj[i]=(qj[i+1]+ksm(2,a[i].second))%M;
	}//预处理
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(a[i]<=a[j]){ //pair 类型的比较是基于第一关键字优先的
			ans=(ans+(qj[j]*ksm(ksm(2,a[i].second+1),M-2))%M)%M;
			b[k++]=a[i++];
		} 
		else {
			b[k++]=a[j++];
		}
	}
	while(i<=mid){
		b[k++]=a[i++];
	}
	while(j<=r){
		b[k++]=a[j++];
	}
	for(int u=l;u<=r;++u){
		a[u]=b[u];
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1,u;i<=n;++i){
		scanf("%lld",&u);
		a[i]={u,i};//记录这个元素的原始下标
	}
	msort(1,n);
	printf("%lld",ans);
}
```

[AC记录](https://www.luogu.com.cn/record/175435377)

---

## 作者：Register_int (赞：1)

首先，当选定 $A_i,A_j$ 为 $A_1',A_k'$ 后，中间的数就可以不用管了，选或不选都可以。所以，枚举所有满足 $A_i\leA_j$ 的点对 $(i,j)$，累加贡献 $2^{j-i-1}$ 即可。这样我们就得到了一个 $O(n^2\log n)$ 的算法。  
然而复杂度优秀到爆炸，而原问题又类似于二维数点，容易想到离散化树状数组。对于二次幂的累加，设 $ans_j$ 为 $A'_k=A_j$ 时的答案，我们可以这样统计：
$$
\begin{aligned}
ans_j&=\sum_{A_i\le A_j}2^{j-i-1}\\
&=\sum_{A_i\le A_j}2^{j-1}\times2^{-i}\\
&=2^{j-1}\sum_{A_i\le A_j}\times\left(\dfrac 12\right)^i\\
\end{aligned}
$$
这样就将求和分成了分别只关于 $i,j$ 的项的成绩，每次在树状数组上添加 $\left(\dfrac 12\right)^i$ 即可。时间复杂度 $O(n\log n)$。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;
const int mod = 998244353;
const int inv2 = mod + 1 >> 1;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

int n, tot;

ll a[MAXN], b[MAXN], c[MAXN];

inline 
int lowbit(int k) {
	return k & -k;
}

inline 
void add(int k, ll x) {
	for (int i = k; i <= n; i += lowbit(i)) c[i] = (c[i] + x) % mod;
}

inline 
ll query(int k) {
	ll res = 0;
	for (int i = k; i; i -= lowbit(i)) res = (res + c[i]) % mod;
	return res;
}

ll ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1), tot = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
	for (int i = 1; i <= n; i++) ans = (ans + qpow(2, i - 1) * query(a[i]) % mod) % mod, add(a[i], qpow(inv2, i));
	printf("%lld", ans);
}
```

---

## 作者：2020luke (赞：0)

# [[ABC221E] LEQ](https://www.luogu.com.cn/problem/AT_abc221_e) 题解

## 思路解析

很有思维量的一道题。首先根据题目要求发现，新求的子序列只跟子序列的头尾有关，而在确定头尾之后中间的元素选或不选没有任何关系。也就是确定新子序列的头尾下标分别为 $i,j$，那么以当前头尾的可行子序列个数就是 $2^{j-i-1}=2^j \div 2^{i+1}$ 种可能。

接下来我们思考，根据题目要求，上方的 $i,j$ 一定有 $a_i \le a_j$，于是我们要做的其实就是找固定 $j$，有多少个 $i$ 使得 $i<j,a_i \le a_j$，也就是个二维偏序。但事实上不需要那么复杂，假设有 $i_1,i_2,\dots,i_k$ 都满足题目的条件，那么以 $j$ 结尾的子序列的个数就是 $2^j \div 2^{i_1+1}+2^j \div 2^{i_2+1}+\dots+2^j \div 2^{i_k+1}=2^j \div (2^{i_1+1}+2^{i_2+1}+\dots+2^{i_k+1})$。

那么接下来就很轻松了，由于上方的 $i,j$ 一定有 $a_i \le a_j$，所以我们可以用一个 $rk_i$ 存下 $a_i$ 的排名，设 $v_{rk_i}=2^{i+1}$，然后求 $\sum_{k=1}^{rk_j-1}v_k$，这样我们就可以求得满足 $a_i \le a_j$ 的条件所有的 $i$ 对答案的贡献，还要继续考虑 $i<j$ 这个条件。我们其实可以不先处理出来 $v$ 的值，而是在 $j \to j+1$ 时处理 $v_j$ 的值，这样就能保证所有 $v$ 当中有值的 $v_{rk_i}$ 都有 $i<j$。由于 $v$ 需要满足单点修改和区间求和的操作，所以需要使用树状数组优化。

注意：由于有取模和乘方，所以需要使用逆元和快速幂求解。

时间复杂度：需要遍历每个下标，都需要一次区间查询和单点修改，复杂度为 $O(n \log n)$。

## code

```cpp
//ABC211E
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3e5 + 10;
const ll mod = 998244353;
int n, m;
ll a[N], c[N], b[N];
map<ll, int> rk;

ll ksm(ll a, ll b, ll p) {
	ll ans = 1;
	while(b) {
		if(b & 1) {
			ans = ans * a % p;
		}
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
ll niyuan(ll a, ll p) {
	return ksm(a, p - 2, p);
}

void add(ll x, ll y) {
	for(; x <= n; x += (x & -x)) {
		c[x] = (c[x] + y) % mod;
	}
}
ll ask(ll x) {
	ll sum = 0;
	for(; x > 0; x -= (x & -x)) {
		sum = (sum + c[x]) % mod;
	}
	return sum;
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; i++) {
		rk[b[i]] = i;
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		ans = (ans + (ksm(2, i, mod) * ask(rk[a[i]])) % mod) % mod;
		add(rk[a[i]], ksm(niyuan(2, mod), i + 1, mod));
	}
	cout << ans;
	return 0;
}
```

---

## 作者：apiad (赞：0)

我们只需要关心子区间的左端点和右端点怎么选，然后中间的随便选。

所以我们可以得到答案为 $\sum_{i=1}^{n-1} \sum_{j-i}^{n} [a_i \le a_j] \times 2^{i-j-1}$。$ [a_i \le a_j] $ 代表的是一个布尔值，可以理解为如果 $a_i \le a_j$ 才需要加上 $2^{i-j-1}$。

直接求这个式子的时间复杂度是 $O(n^2 \log n)$。（因为快速幂时间复杂度是 $\log n$，当然你可以直接位移，就是 $O(1)$，但时间复杂度依然是 $O(n^2)$ 及以上。还是需要优化。）

我们对这个式子进行一些转换：

$\sum_{i=1}^{n-1} \sum_{j=i+1}^{n} [a_i \le a_j] \times 2^{i-j-1} $ 

$= \sum_{i=1}^{n-1} (\sum_{j=i+1}^{n} 2^{-i-1} \times [a_i \le a_j] \times 2^{j})$

$= \sum_{i=1}^{n-1} ( 2^{-i-1} \times  \sum_{j=i+1}^{n} [a_i \le a_j] \times 2^{j})$

然后对于 $\sum_{j=i+1}^{n} [a_i \le a_j] \times 2^{j}$ 我们可以直接用数据结构来维护，这里用的是树状数组。

[link](https://atcoder.jp/contests/abc221/submissions/51471326)。

---

## 作者：mojoege (赞：0)

## 分析

有点像 dp，但不多。

肯定第 $i$ 个数的贡献就是 $\sum_{j=1}^{i-1}2^{i-j-1}$ 其中 $a_j \le a_i$。根据同底数幂的除法，实际上后面那个幂就是 $2^{i-1}/2^{j}$，总和也就是 $\sum_{j=1}^{i-1} 2^{i-1} \times 2^{-j}$。提取公因数一下，我们发现其实就是要求 $\sum_{j=1}^{i-1} 2^{-j}$，这样就转化成了处理一下符合条件的 $2^{j-1}$ 的和。

考虑离散化+树状数组，用离散化给这些数字标个顺序，然后按公式求和。因为有离散化，我们把 $b_i$ 表示 $a_i$ 离散化之后的位置，所以查询的时候直接查询 $b_i$ 而不是查询 $a_i$，这就保证了查询时第 $b_i$ 个数前面的数都是比它小的，满足条件；而更新的时候有树状数组的性质肯定保证只会更新比 $b_i$ 大的数，也就是剩下部分的权值和。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int n, ans;
int a[300005], b[300005], c[1000005];

int ksm(int a, int b){
    int res = 1;
    while (b){
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int lowbit(int x){
    return x & (-x);
}

int query(int x){
    int res = 0;
    while (x){
        res = (res + c[x]) % mod;
        x -= lowbit(x);
    }
    return res;
}

int update(int x, int k){
    int res = 0;
    while (x <= n){
        c[x] += k;
        x += lowbit(x);
    }
    return res;
}

signed main(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1);
    int m = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;//离散化
    for (int i = 1; i <= n; i++){
        ans = (ans + ksm(2, i - 1) * query(a[i]) % mod) % mod;//求之前的总和+提取公因式
        update(a[i], ksm(ksm(2, mod - 2), i));//往后更新a[i]之后的和
    }
    cout << ans;
    return 0;
}
```

---

## 作者：CRTL_xzh2009 (赞：0)

假设子序列的尾元素在原序列的位置为 $j$，如果 $i(i<j)$ 位置满足 $A_i \le A_j$，那么，$[i,j]$ 的合法子序列个数为 $2^{j-i-1}$，因为一定选 $i$ 和 $j$，中间有 $j-i-1$ 个数，子集个数就为 $2^{j-i-1}$。那么我们遍历每个位置，当成 $j$，找 $[1,j-1]$ 中有多少 $i$ 满足 $A_i \le A_j$，每个 $i$ 的贡献为 $\dfrac{2^{j-1}}{2^i}$。每次找区间元素符合条件的个数，单点修改，用线段树即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
    long long x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
inline void write(long long x){
    if(x==0){putchar('0');return;}
    long long len=0,k1=x,c[10005];
    if(k1<0)k1=-k1,putchar('-');
    while(k1)c[len++]=k1%10+'0',k1/=10;
    while(len--)putchar(c[len]);
}
const long long MOD=998244353;
long long a[1000005],b[1000005],c[1000005],n;
long long lowbit(long long x){
	return x&-x;
}
long long qpow(long long a,long long b){
	long long res=1;
	while(b){
		if(b&1){
			res=res*a%MOD;
		}
		a=a*a%MOD;
		b=b>>1;
    }
	return res%MOD;
}
void add(long long x,long long k){
	for(long long i=x;i<=n;i+=lowbit(i)){
		c[i]+=k;
	}
}
long long ask(long long x){
	long long ans=0;
	for(long long i=x;i!=0;i-=lowbit(i)){
		ans=(ans+c[i])%MOD;
	}
	return ans;
} 
vector<long long > v;
int main(){
	//freopen("seq.in","r",stdin);
	//freopen("seq.out","w",stdout);
	n=read();
	for(long long i=1;i<=n;i++){
		a[i]=read(); v.push_back(a[i]);
	} 
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	long long size=v.size();
	for(long long i=1;i<=n;i++){
		a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
	}
	long long ans=0;
	for(long long i=1;i<=n;i++){
		ans=(ans+(qpow(2,i-1)*ask(a[i]))%MOD)%MOD;
		add(a[i],qpow(qpow(2,MOD-2),i));
	} cout<<ans;
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

## 思路

首先因为只需要考虑相对大小关系，所以先将序列离散化。

因为只需要考虑第一个元素和最后一个元素，因此对于每对 $(i, j)， i \le j，a_i \le a_j$ 中间的任何元素都可选可不选，因此会有 $2^{j - i - 1}$ 的贡献。

把 $i$ 和 $j$ 分开，贡献变为 $\frac {2^{j - 1}}{2_i}$ 然后用权值树状数组对于 $a_j$ 维护 $2^{j - 1}$ 的后缀和乘 $2_i$ 的逆元即可。

[$\texttt{Code}$](https://atcoder.jp/contests/abc221/submissions/54733240)

---

