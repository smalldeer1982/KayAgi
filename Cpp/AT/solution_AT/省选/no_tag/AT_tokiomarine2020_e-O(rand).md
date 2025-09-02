# O(rand)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tokiomarine2020/tasks/tokiomarine2020_e

$ N $ 個の相異なる非負整数 $ A_1,A_2,\ldots,A_N $ が与えられます。 与えられた数の中から $ 1 $ 個以上 $ K $ 個以下の数を選ぶ方法であって、次の $ 2 $ つの条件を満たすような方法は何通りあるか求めてください。

- 選ばれた数のビットごとの論理積は $ S $ である。
- 選ばれた数のビットごとの論理和は $ T $ である。

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 50 $
- $ 1\ \leqq\ K\ \leqq\ N $
- $ 0\ \leqq\ A_i\ <\ 2^{18} $
- $ 0\ \leqq\ S\ <\ 2^{18} $
- $ 0\ \leqq\ T\ <\ 2^{18} $
- $ A_i\ \neq\ A_j $ ($ 1\ \leqq\ i\ <\ j\ \leqq\ N $)

### Sample Explanation 1

$ \{1,2\} $ もしくは $ \{1,2,3\} $ と数を選ぶと条件を満たします。

## 样例 #1

### 输入

```
3 3 0 3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5 3 1 7
3 4 9 1 5```

### 输出

```
2```

## 样例 #3

### 输入

```
5 4 0 15
3 4 9 1 5```

### 输出

```
3```

# 题解

## 作者：roger_yrj (赞：3)

## 题解

- 如果 $S\not\subseteq T$，无解，输出 $0$。
- 如果一个数 $x\not\subseteq T$ 或 $x\not\supseteq S$，那么这个数一定不会被选。

对于筛剩的数，我们只需要考虑 $T-S$ 的部分就行了。我们选出来的数是合法的，当且仅当对于 $T-S$ 的每一位，有些数这一位是 $0$，有些数这一位是 $1$。

我们考虑容斥，我们设 $f_{sub}$ 表示 $sub$ 这些位置不合法的情况有多少种。那么对于选出来的这些数，它们与 $sub$ 的值都是相等的，所以只要求出有多少个相等的数，然后求个组合数就行了。

最终的答案为 $\sum\limits
_{sub\subseteq (T-S)}(-1)^{|sub|}f_{sub}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=60;
int nn,n,k;
ll S,T,a[N],C[N][N],sum[N],ans,cnt[11451419];
int cnt1(int x){
	int ret=0;
	while(x)x-=(x&-x),ret++;
	return ret;
}
int main(){
	cin>>nn>>k>>S>>T;
	if((S&T)!=S)return cout<<0,0;
	for(int i=1;i<=nn;i++){
		ll x;scanf("%lld",&x);
		if((S&x)==S&&(x&T)==x)a[++n]=x;
	}
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=min(i,k);j++)C[i][j]=C[i-1][j-1]+C[i-1][j],sum[i]+=C[i][j];
	}
	int Sub=(T-S);ans=sum[n];
	for(int sub=Sub;sub;sub=(sub-1)&Sub){
		ll ret=0;
		for(int i=1;i<=n;i++)cnt[a[i]&sub]++;
		for(int i=1;i<=n;i++){
			ret+=sum[cnt[a[i]&sub]];
			cnt[a[i]&sub]=0;
		}
		ans+=((cnt1(sub)&1)?-1:1)*ret;
	}
	cout<<ans;
}
```

---

## 作者：liuzhenhao09 (赞：2)

首先显然若 $S$ 不是 $T$ 的子集则无解。

其次若一个数不是 $S$ 的超集或一个数不是 $T$ 的子集，则这个数一定不会被选。

我们只用考虑 $T$ 比 $S$ 多的那部分，即 $S$ 异或 $T$ 的部分。

对于这些部分的限制是至少出现了一个数的这一位为 $1$，但不能全部出现。

如果直接统计 $\sum\limits_{i=1}^k{C_n^i}$ 则不满足上述限制，考虑容斥。

我们钦定一些位全部选或全部不选，设这些位拼起来是 $msk$，则对于所有合法的数 $x$（即排除掉一定不会被选的数），$x\operatorname{and}msk$ 均相等。直接对于每个 $x\operatorname{and}msk$，统计它出现的次数 $cnt$，然后将 $\sum\limits_{i=1}^k{C_{cnt}^i}$ 加进答案即可。容斥系数显然为 $(-1)^{\operatorname{popcount}(msk)}$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,s,t,tot = 0;
int a[60],cnt[262144];
int C[60][60],p[60];
signed main(){
	scanf("%lld %lld %lld %lld",&n,&k,&s,&t);
	if(t != (s | t)){
		printf("0");
		return 0;
	}
	for(int i = 1,x; i <= n; i++){
		scanf("%lld",&x);
		if((s & x) == s && (t | x) == t) a[++tot] = x; //合法的 
	}
	for(int i = 0; i <= tot; i++){
		C[i][0] = 1; //不能一个都不选，所以不加入答案 
		for(int j = 1; j <= i && j <= k; j++){
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			p[i] += C[i][j];
		}
	}
	int ans = p[tot]; //无限制随便选 
	int dif = s ^ t;
	for(int i = dif; i; i = (i - 1) & dif){
		int tmp = 0;
		for(int j = 1; j <= tot; j++) cnt[a[j] & i]++;
		for(int j = 1; j <= tot; j++){
			tmp += p[cnt[a[j] & i]];
			cnt[a[j] & i] = 0;
		}
		ans += (__builtin_popcountll(i) & 1 ? -tmp : tmp); //容斥 
	}
	printf("%lld",ans);
	return 0;
}
```

该题解部分思路受益于[这篇博客](https://www.cnblogs.com/AThousandMoons/p/14609677.html)。

---

## 作者：Conan15 (赞：1)

简单题想了两个小时 /ll\
看到这题有两个思路：

1. 类似于之前某道题，把下界干成 $0$ 变成单上界，接下来再搞一堆观察或许会有性质。
2. 直接对二进制位容斥。

~~结果最后的做法成了两个的杂交版。~~\
首先显然有 $S \subseteq T$，为了简化问题，先进行如下转化：

1. 依次考虑每一个二进制位，若 $T=0,a=1$ 则这个 $a$ 对答案没有贡献可以删掉，即 $T ~|~ a \not= T$。
2. 若 $S=1, a=0$ 也没有贡献，即 $S \& a \not= S$。
3. 把确定无贡献的数全都踢出去之后，为了简化二进制形式，只把 $T - S$ 二进制下为 $1$ 的位保留，其它都删掉（类似于线性基重排二进制位）。

**此时 $T$ 全 $1$，只需要选择一些 $a$ 使得它们与和为 $0$ 或和为全集即可。**\
正难则反，考虑一个二进制位如何才能**不满足条件**。

1. 选出的所有数这一位都为 $0$。
2. 选出的所有数这一位都为 $1$。

接下来对二进制位容斥，设 $f_i$ 表示选择了 $i$ 这个集合的二进制位，**恰好**只有这些位不满足条件的方案数。\
一种转化是**位置集合 $i$ 的每一位都必须至少有一个** $0$ 或 $1$，但推了半天没什么进展。\
然后转回来想想直接做就是对的：**即对于 $i$ 集合的每一位，选出的数在这一位都必须相同**。\
设选出的数是 $a_1,a_2,\dots,a_k$，则 $a_j \& i$ 相同的 $a$ 才能同时被选择。

显然可以用一个桶维护 $a_j \& i$ 的数字数量，然后组合数前缀和求一下选 $1 \leq x \leq k$ 个数的方案数。\
由于算出来的是 $g_i$ 表示 $i$ 的**超集**选择方案数，所以最后**子集反演**即可求出 $f_0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 55, M = (1 << 18) + 5;
int n, nn, k, S, T;
int a[N];
long long C[N][N], ans;

inline bool chk(int x, int i) { return (x >> i) & 1; }
inline int get(int x) {
    int res = 0;
    for (int i = 18; i >= 0; i--)
        if (chk(T, i)) res = (res << 1) | chk(x, i);
    return res;
}
inline int popcnt(int x) {
    int res = 0; while (x) res += x & 1, x >>= 1;
    return res;
}

void init() {
    for (int i = 1; i <= n; i++) a[i] ^= S; T ^= S;
    for (int i = 1; i <= n; i++) a[i] = get(a[i]);
    T = (1 << popcnt(T)) - 1;
    C[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) {
            if (!j) C[i][j] = 1;
            else C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
}
long long mem[N];
inline long long getC(int i) {
    if (mem[i]) return mem[i];
    long long res = 0;
    for (int j = 1; j <= min(i, k); j++) res += C[i][j];    // 不能不选
    return mem[i] = res;
}

int cnt[M]; bool st[M];

int main() {
    scanf("%d%d%d%d", &n, &k, &S, &T), nn = 0;
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        if ( !((S & x) != S || (T | x) != T) ) a[++nn] = x;
    } n = nn;
    init();
    for (int i = 0; i <= T; i++) {
        for (int j = 1; j <= n; j++) ++cnt[i & a[j]];
        long long res = 0;
        for (int j = 1; j <= n; j++) {
            if (st[i & a[j]]) continue;
            st[i & a[j]] = 1, res += getC(cnt[i & a[j]]);
        }
        ans += ((popcnt(i) & 1) ? -1 : 1) * res;
        for (int j = 1; j <= n; j++) --cnt[i & a[j]], st[i & a[j]] = 0;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：ll_dio (赞：0)

## 题目大意
给定 $n$ 个数 $a_{i}$，要在其中选出**至少** $1$ 个，**至多** $k$ 个数，使得这 $k$ 个数的与为 $S$，或为 $T$。求方案数。
## 题目分析
显而易见，这是一道组合题。
### 逐位分析
因为跟位运算有关，我们考虑逐位分析。

对于 $S$ 和 $T$ 的第 $i$ 位，设选中的 $x$ 个数为 $b_{j}$，则若：

$S_{i}=T_{i}=1$，则对于所有的 $j$，有 $b_{j,i}=1$。

$S_{i}=T_{i}=0$，则对于所有的 $j$，有 $b_{j,i}=0$。

$S_{i}=1$，$T_{i}=0$，则没有符合条件的 $b_{j}$，无解。

$S_{i}=0$，$T_{i}=1$，则对于所有的 $j$，$b_{j,i}$ 中不能全都是 $0$ 或全都是 $1$。

根据上面的分析，我们可以发现，只需要先判断是否有解，然后把不满足 $S_{i}=T_{i}=0/1$ 的所有 $a_{i}$ 剔除，接下来只需要考虑 $S_{i}=0$，$T_{i}=1$ 的位就可以了，我们用 $T-S$ 来表示有解的情况下需要考虑的位。

### 推式子
我们发现正着算哪些选法符合条件比较难，正难则反，考虑计算不符合条件的选法，并将总方案数减去它。

我们不妨设剔除操作处理完后合法的 $a$ 有 $m$ 个，那么总方案数就很好计算，为 $\sum_{x=1}^{k} \operatorname{C}_{m}^{x}$。

接下来我们要计算不符合条件的选法数量。我们发现，对于每一个要考虑的位置，只有所有选的数在这一位上相等，才会不合法。直接枚举很容易重算，所以我们考虑容斥原理（~~这里点名批评容斥想到了但是第一次写的时候枚举错东西的铸币作者~~）。

我们枚举 $T-S$ 的子集 $P$，也就是不合法位置的集合，我们用一个计数器数组 $cnt_i$ 记录每一个 $a_{i}$ 在位置集合 $P$ 中的位置上的值，我们就可以容斥计算出不合法的方案数，为 $\sum_{P\subseteq(T-S)}((-1)^{\operatorname{popcount}(P)}\times\sum_{i=1}^{m}\sum_{x=1}^{k}\operatorname{C}_{cnt_{a_{i}\operatorname{and}P}}^{x})$。

所以，我们可以计算出
$$
ans=\sum_{x=1}^{k}\operatorname{C}_{m}^{x}-\sum_{P\subseteq(T-S)}((-1)^{\operatorname{popcount}(P)}\times\sum_{i=1}^{m}\sum_{x=1}^{k}\operatorname{C}_{cnt_{a_{i}\operatorname{and}P}}^x)
$$

通过预处理 $\sum_{x=1}^{k}\operatorname{C}_{i}^{x}$ 可以使得代码的复杂度为 $O(nS)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define N 51
#define Le 19
#define K 270001
using namespace std;
typedef long long ll;
ll n,k,s,t,a[N],cnt[K],L,C[N][N],nPtn,tot,pos[Le],b[N],nValid,cou[K],sum[N];
bool ok[N];
void print(ll num){
	for(ll i=L-1;i>=0;i--) printf("%lld",ll(bool((num&(1<<i)))));
	printf(" ");
}
void input(){
	scanf("%lld %lld %lld %lld",&n,&k,&s,&t);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]),ok[i]=1;
}
void solve(){
	L=18;
	C[0][0]=1;
	for(ll i=1;i<=n;i++){
		C[i][0]=1;
		for(ll j=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
		for(ll j=1;j<=min(i,k);j++) sum[i]+=C[i][j];
	}
	for(ll i=0;i<L;i++)
		if((s&(1<<i))&&(t&(1<<i))==0){
			printf("0");
			return;
		}else if((s&(1<<i))==0&&(t&(1<<i))) pos[++tot]=i;
		else
			for(ll j=1;j<=n;j++)
				if((s&(1<<i))!=(a[j]&(1<<i))) ok[j]=0;
	for(ll i=1;i<=n;i++)
		if(ok[i]) b[++nValid]=a[i];
	ll ans=sum[nValid];
	t-=s;
//	printf("%lld\n",nValid);
//	print(t);
//	printf("\n");
	for(ll p=t;p;p=((p-1)&t))
		for(ll i=0;i<L;i++)
			if((p&(1<<i))) cou[p]++;
	for(ll p=t;p;p=((p-1)&t)){
		ll delta=(cou[p]%2==1?-1:1),res=0;
//		print(p);
//		printf("\n");
		for(ll i=1;i<=nValid;i++) cnt[b[i]&p]++;
		for(ll i=1;i<=nValid;i++){
//			print((b[i]&p));
//			printf("%lld\n",cnt[b[i]&p]);
			res+=sum[cnt[b[i]&p]];
			cnt[b[i]&p]=0;
		}
		ans+=delta*res;
	}
	printf("%lld",ans);
}
int main(){
	input();
	solve();
	return 0;
}

```

---

## 作者：Galois_Field_1048576 (赞：0)

不妨设每一个 $a_i$ 都满足 $S \subseteq a_i \subseteq T$，即 $a_i \mathop{\triangle} S\subseteq T \mathop{\triangle} S$。不满足条件的显然没有贡献。设 $b_i \coloneqq a_i \mathop{\triangle} S$，则我们的目标是：
> 选择若干（$\leqslant k$）个 $b_i$ 组成一个集合 $A$，使得对于每一位 $i$，$A$ 中都有元素 $x_i$ 使得这一位为 1，也有元素 $y_i$ 使得这一位元素为 0。

正难则反。这是本题的关键。统计有多少个集合满足：
> 存在至少一位 $i$，对于每一个 $a \in A$，$a$ 的 $i$ 位全 0 或全 1。
> 这样的位 $i$ 称为 $A$ 的 **反例位**。反例位组成的集合记作 $\mathcal C(A)$。

我们考虑枚举是哪一位。但是我们统计的是集合而不是位，所以需要容斥。具体而言，设 $f(B)$ 为使得 $B \subseteq \mathcal C(A)$ 的 $A$ 的数目。因为对所有的 $x \in A$，$x \cap \mathcal C(A)$ 一定是全为同样的集合，所以对所有得到 $x \in A$，$x \cap B$ 一定全为同样的集合。对于每个 $B$ 统计出所有使 $b_i \cap B = f$ 的数量 $c_f(B)$，则
$$
\sum_{i=1}^k \left(\sum_f {c_f(B) \choose i}\right)
$$
即为所求。然后套个容斥的壳就好。

---

