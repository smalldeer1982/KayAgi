# [ABC107D] Median of Medians

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc107/tasks/arc101_b

長さ $ M $ の数列 $ b $ の **中央値** を次のように定義します。

- $ b $ を昇順にソートして得られる数列を $ b' $ とする。 このとき、$ b' $ の $ M\ /\ 2\ +\ 1 $ 番目の要素の値を、$ b $ の中央値とする。 ここで、$ / $ は小数点以下を切り捨てる除算である。

例えば、$ (10,\ 30,\ 20) $ の中央値は $ 20 $ であり、$ (10,\ 30,\ 20,\ 40) $ の中央値は $ 30 $ であり、$ (10,\ 10,\ 10,\ 20,\ 30) $ の中央値は $ 10 $ です。

すぬけ君は次のような問題を思いつきました。

長さ $ N $ の数列 $ a $ があります。 各 $ (l,\ r) $ ($ 1\ \leq\ l\ \leq\ r\ \leq\ N $) について、$ a $ の連続部分列 $ (a_l,\ a_{l\ +\ 1},\ ...,\ a_r) $ の中央値を $ m_{l,\ r} $ とします。 すべての $ (l,\ r) $ に対する $ m_{l,\ r} $ を並べ、新たに数列 $ m $ を作ります。 $ m $ の中央値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ a_i $ は整数である。
- $ 1\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

$ a $ のそれぞれの連続部分列の中央値は次のようになります。 - $ (10) $ の中央値は $ 10 $ - $ (30) $ の中央値は $ 30 $ - $ (20) $ の中央値は $ 20 $ - $ (10,\ 30) $ の中央値は $ 30 $ - $ (30,\ 20) $ の中央値は $ 30 $ - $ (10,\ 30,\ 20) $ の中央値は $ 20 $ よって、$ m\ =\ (10,\ 30,\ 20,\ 30,\ 30,\ 20) $ となり、$ m $ の中央値は $ 30 $ です。

## 样例 #1

### 输入

```
3
10 30 20```

### 输出

```
30```

## 样例 #2

### 输入

```
1
10```

### 输出

```
10```

## 样例 #3

### 输入

```
10
5 9 5 9 8 9 3 5 4 3```

### 输出

```
8```

# 题解

## 作者：bugmaker3243 (赞：15)

# 基本分析

中位数的定义不再赘述。

首先分析答案的性质，若一个大小为 $n$ 的集合 $S$ 的中位数是 $x$，则 $x$ 一定满足以下条件：

- $S$ 中至少存在 $\left\lceil\frac{n}{2}\right\rceil$ 个数大于等于 $x$。

- $x$ 是满足条件 $1$ 中最大的数。

因此答案具有单调性，可以采用二分答案的方式。

# 具体实现

在二分答案的背景下，题目可以转换为：对于数组 $a$，求中位数大于等于 $x$ 的区间 $(l,r)$ 数量。

考虑辅助数组 $b$，$b_i=\begin{array}{l} 
  \left\{\begin{matrix} 
  1 (a_i\geq x) \\ 
  -1 (a_i<x) \\
\end{matrix}\right.    
\end{array}$，如果区间 $(l,r)$ 的中位数大于等于 $x$，则 
$\sum_{i=l}^{r}b_i\geq0$。

于是题目又转换为：对于数组 $b$，求出区间和非负的区间数。

使用前缀和可简化为求满足 $sum_r-sum_{l-1}\geq0$ 的 $(l,r)$ 数量。

扫一遍前缀数组，并用树状数组统计小于等于 $sum_i$ 的总数即可。

注意由于 $b$ 数组可能为负数，所以在树状数组统计时需要加上 $n+1$。

显然答案是原数组里的数，于是可以只用二分原数组。

时间复杂度： $O(N\log^2 N)=10^5\times17^2\approx3\times10^7$，可以通过。


update：优化了算法，感谢 [small_peter](https://www.luogu.com.cn/user/298994) 和 [daehsif](https://www.luogu.com.cn/user/389474) 指出错误。

# 代码（请勿抄袭）

```cpp
#include<bits/stdc++.h>
#define N 100005
#define int long long //n^2 可能会爆 int 
#define lb(x) (x&(-x))
using namespace std;
int n,a[N],b[N],tmp[N],sum[N],c[N*2];//由于插入时加了 N，所以要开二倍 
void add(int k,int x)
{
	for(;k<2*N;k+=lb(k)) c[k]+=x;
}
int ask(int k)
{
	int s=0;
	for(;k;k-=lb(k)) s+=c[k];
	return s;
}
int check(int x)
{
	int ans=0;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)
	{
		if(a[i]>=x) b[i]=1;
		else b[i]=-1;
		sum[i]=sum[i-1]+b[i];
	}
	add(N,1);//插入 sum[0]
	for(int i=1;i<=n;i++)
	{
		ans+=ask(sum[i]+N);
		add(sum[i]+N,1);
	}
	if(ans>=(n*(n+1)/2-1)/2+1) return 1;
//	(x-1)/2+1 是对 (x/2) 向上取整的一种办法 
//	也可以写成 if(ans*2>=n*(n+1)/2) return 1;
	return 0;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),tmp[i]=a[i];
	sort(tmp+1,tmp+n+1);
	int l=1,r=n,ans=0;
	while(l<=r) //二分 
	{
		int mid=(l+r)/2;
		if(check(tmp[mid])) ans=tmp[mid],l=mid+1;
		else r=mid-1;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：KingPowers (赞：3)

## ABC107D Median of Medians

[题目链接](https://www.luogu.com.cn/problem/AT_arc101_b)

考虑下正常求中位数二分的时候我们是怎么求的：假如当前二分的值为 $mid$，将原序列中大于等于 $mid$ 的数设为 $1$，小于 $mid$ 的数设为 $-1$，若此时整个序列的和为非负数，就说明原序列的中位数大于等于 $mid$。

那么再看到这一题，其实就是在求处理之后是否有至少一半的子段，其子段和大于等于 $0$。这是个经典问题了，可以使用前缀和与树状数组来维护。具体地，记 $s$ 为处理后的序列的前缀和，那么以当前点 $i$ 结尾的和大于等于 $0$ 的子段数其实就是：

$$
\sum_{j=1}^{i} [s_i-s_{j-1}\ge0]
$$

在值域上开个树状数组就行了。注意和可能为负数，因此将下标向右平移 $n$ 位。

```cpp
#define ID(x) x+n
int n,lmt,a[N],b[N],c[N],ss[N];
void add(int x,int y){
	while(x<=ID(n)){
		c[x]+=y;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	for(;x;x-=lowbit(x)) res+=c[x];
	return res;
}
bool check(int mid){
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++){
		if(a[i]>=mid) b[i]=1;
		else b[i]=-1;
		ss[i]=ss[i-1]+b[i];
	}
	add(ID(0),1);
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=query(ID(ss[i]));
		add(ID(ss[i]),1);
	}
	if((cnt<<1)>=(n*(n+1)>>1)) return 1;
	return 0;
}
void Main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),lmt=max(lmt,a[i]);
	int l=1,r=lmt,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%lld",ans);
}
```

---

## 作者：Rubyonly (赞：3)

首先定义中位数，将 $n$ 个数排序后，如果有奇数个数，则中位数为 $a[\frac{n}{2}]$，否则中位数为 $a[\frac{n}{2}+1]$

让你求出 $\frac{n(n+1)}{2}$ 个区间中位数的中位数

首先考虑一下中位数的性质：

* 如果 $n$ 为奇数，中位数满足 

$$num_{a[i]\geq a[mid]}=num_{a[i]\leq a[mid]}$$

* 如果 $n$ 为偶数，中位数满足 

$$num_{a[i]\geq a[mid]}=num_{a[i]\leq a[mid]}-1$$

不妨我们二分答案 $x$，然后用中位数的性质 $check$ 答案是否正确，现在问题是如何求出有多少个区间的中位数大于等于 $x$，有多少个区间的中位数小于等于 $x$

我们将 $\geq x$ 的数置为 $1$，$< x$ 的数置为 $-1$

容易发现，一个区间的和 $\geq 0$，说明这个区间的中位数 $\geq x$，如果这个和 $< 0$，说明这个区间的中位数 $\leq x$

根据求区间和 $sum[r]-sum[l-1]$ 的式子，我们可以对于每个右端点求出左边有多少个点的 $sum[l] \leq sum[r]$，同时也可以求出 $sum[l] > sum[r]$ 的个数，这个用树状数组维护一下就行了

最后复杂度是二分内套一个 $\mathcal{O}(n\log n)$，所以是 $\mathcal{O}(n\log^2 n)$ 的

$\mathcal{Code}$

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

using namespace std;

const int maxn = 2e5 + 50, INF = 0x3f3f3f3f, base = 1e5;

inline int read () {
	register int x = 0, w = 1;
	register char ch = getchar ();
	for (; ch < '0' || ch > '9'; ch = getchar ()) if (ch == '-') w = -1;
	for (; ch >= '0' && ch <= '9'; ch = getchar ()) x = x * 10 + ch - '0';
	return x * w;
}

int n, typ, a[maxn], b[maxn], c[maxn], tree[maxn];

inline void Insert0 (register int x) {
	for (; x <= maxn; x += x & -x) tree[x] ++;
}

inline int Query0 (register int x, register int ans = 0) {
	for (; x; x -= x & -x) ans += tree[x];
	return ans;
}

inline void Insert1 (register int x) {
	for (; x; x -= x & -x) tree[x] ++;
}

inline int Query1 (register int x, register int ans = 0) {
	for (; x <= maxn; x += x & -x) ans += tree[x];
	return ans;
}

inline bool Check (register int x, register ll num0 = 0, register ll num1 = 0) {
	memset (tree, 0, sizeof tree), Insert0 (0 + base);
	for (register int i = 1; i <= n; i ++) c[i] = a[i] < x ? -1 : 1;
	for (register int i = 1, res = 0; i <= n; i ++) 
		res += c[i], num0 += Query0 (res + base), Insert0 (res + base);
	memset (tree, 0, sizeof tree), Insert1 (0 + base);
	for (register int i = 1, res = 0; i <= n; i ++) 
		res += c[i], num1 += Query1 (res + base + 1), Insert1 (res + base);
	return num0 >= num1 - typ;
}

int main () {
	n = read(), typ = 1ll * n * (n + 1) / 2 % 2 == 0;
	for (register int i = 1; i <= n; i ++) a[i] = b[i] = read();
	sort (b + 1, b + n + 1);
	register int L = 1, R = n;
	while (L <= R) {
		register int mid = (L + R) >> 1;
		if (Check (b[mid])) L = mid + 1;
		else R = mid - 1;
	}
	return printf ("%d\n", b[L - 1]), 0;
}
```

---

## 作者：Rannio (赞：2)

**题目大意**：一个长度为 $M$ 的序列的中位数为这个序列从小到大排序后第 $\lfloor\frac M 2\rfloor + 1$ 个数，将这个序列的所有子段的中位数放入一个序列中，求这个序列的中位数。
  
设一个序列 $a$ 的中位数为 $x$，那么 $a$ 中至少会有一半的数大于等于 $x$，并且 $x$ 是 $a$ 中满足这个条件的数中最大的，因此答案满足单调性，考虑二分答案。  
同时也不难发现，上述所求答案满足： $i<j$ 并且 $a_i\leq a_j$ 的数对数量大于等于总对数的一半。

运用差分与前缀和思想，对于每一次二分找到的中间位置，将已排列好的原序列的中间位置的值与未排序序列中的元素作比较，如果该值比原序列的中间位置的值小则标记为 $-1$，否则标记为 $1$，同时对标记数组求前缀和。

现在问题转化为了在前缀和数组里求 $i<j$ 并且 $a_i\leq a_j$ 的数对数量是否大于等于总对数的一半，我们发现这种数对的数量等于总对数减去 $i<j$ 并且 $a_i>a_j$ 的数对数量，这不就是逆序对吗？  

设序列元素个数为 $n$，运用归并排序思想求出逆序对数量，再判断总对数 $\frac{n(n+1)}{2}$ 减去逆序对数量是否大于总对数数量的一半即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,s[100005],d[100005],f[100005],g[100005];
int ans,sum,num;
int n[100005],m[100005];
void merge(int x,int y){
	if(x==y) return ;
	int mid=(x+y)/2;
	merge(x,mid);
	merge(mid+1,y);
	int i=x,j=mid+1,k=x;
	while(i<=mid&&j<=y){
		if(f[i]<=f[j]){
			m[k++]=f[i++];
		}
		else{
			m[k++]=f[j++];
			sum+=mid-i+1;
		}
	}
	while(i<=mid) m[k++]=f[i++];
	while(j<=y) m[k++]=f[j++];
	for(int i=x;i<=y;i++) f[i]=m[i];
}
bool check(int x){
    for(int i=1;i<=a;i++){
        if(s[i]<g[x]){
            f[i]=f[i-1]-1;
        }
        else {
            f[i]=f[i-1]+1;
        }
    }
    merge(0,a);
    if(num-sum>=num/2){
        return true;
    }
    return false;
}
signed main(){
	scanf("%lld",&a);
    num=a*(a+1)/2;
	for(int i=1;i<=a;i++){
		scanf("%lld",&s[i]);
        g[i]=s[i];
	}
    sort(g+1,g+a+1);
	int l=1,r=a;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			ans=g[mid];
            l=mid+1;
		}
		else{
			r=mid-1;
		}
        sum=0;
	}
    printf("%lld",ans);
	return 0;
}
```

---

## 作者：zac2010 (赞：2)

考虑二分答案。于是现在问题转化成了：$S$ 的中位数是否 $\geq x$（$x$ 为二分的值）。

可单纯这样，还没法直接做。继续转化：求出中位数 $\geq x$ 的区间个数。假设我们求出了这个区间个数（设它为 $cnt$），通过数学归纳，不难得出 $S$ 的中位数 $\geq x$ 当且仅当 $\lfloor cnt \geq \frac{(n+1)\times n\div 2}{2}\rfloor$。

对于现在的问题，不妨采用一种常见的套路：当所有数与 $x$ 只有大小关系的贡献时，可以把大小满足条件的赋值为 $1$，不满足条件的赋值为 $-1$；在本题中，所有 $<x$ 的位置赋值为 $-1$，所有 $\geq x$ 的位置赋值为 $1$。我们要求的有进一步转化为了：和 $\geq 0$ 的区间个数。

考虑求一个前缀和（记 $1$ 到 $i$ 的和为 $s_i$）。一个 $i$ 作为右端点的某个区间和 $\geq 0$，当且仅当它的左端点 $j$ 满足 $s_j\leq s_i$。这是一个二维偏序问题，使用树状数组/线段树求解即可。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, a[N], s[N]; ll num;
struct BIT{
    int n = 0, c[N];
    void clear(){FL(i, 0, n) c[i] = 0;}
    void resize(int t){FL(i, n + 1, t) c[i] = 0; n = t;}
    void add(int x, int v){
        for(; x <= n; x += x & -x) c[x] += v;
    }
    int ask(int x, int ret = 0){
        for(; x; x -= x & -x) ret += c[x];
        return ret;
    }
} b;
int check(int x){
    ll cnt = 0; b.clear();
    FL(i, 1, n) s[i] = s[i - 1] + (a[i] < x? -1 : 1);
    FL(i, 0, n) cnt += b.ask(s[i]), b.add(s[i], 1);
    return (cnt << 1) >= num;
}
int main(){
    scanf("%d", &n), num = 1ll * (s[0] = n + 1) * n >> 1;
    FL(i, 1, n) scanf("%d", &a[i]);
    int l = 0, r = 1e9, ans; b.resize(n << 1 | 1);
    while(l <= r){
        int mid = l + r >> 1;
        if(check(mid)) l = (ans = mid) + 1;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：luchenxi2012 (赞：0)

题目传送门 [[ABC107D] Median of Medians](https://www.luogu.com.cn/problem/AT_arc101_b)

题目要求所有子段的中位数的中位数。那么，我们先考虑简单的版本 [P3031](https://www.luogu.com.cn/problem/P3031)：怎么求出所有子段中，中位数大于等于某一个 $X$ 的个数？其实，这个题在那个题的基础上加一个二分答案就行了。

首先，“中位数大于等于 $X$”等价于“子段中大于等于 $X$ 的数的个数不少于小于 $X$ 的个数”，而“一个数大于等于 $X$”这个变量非零即一，所以我们想到，将大于等于 $X$ 的数标上 $1$，反之小于 $X$ 的数标上 $-1$。那么，问题转化为区间和大于等于 $0$。这个只需维护前缀和然后树状数组计数即可。

在上面的问题的基础上加二分即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int tr[200005], n; // 树状数组（其实可以用其他方法的）
// 这里将值域设成 2n+1 避免出现负数。
void add(int x) {
	for (int i = x; i <= 2 * n + 1; i += i & -i)
		tr[i]++;
}
int sum(int x, int res = 0) {
	for (int i = x; i; i -= i & -i)
		res += tr[i];
	return res;
}
int a[100001];
bool chk(int X) {
	memset(tr, 0, sizeof tr);
	int s = n + 1, ans = 0, f; add(s);
	for (int i = 1; i <= n; i++)
		f = a[i] >= X ? 1 : -1, // 计算即可。
		ans += sum(s += f), add(s); // s 代表前缀和。
	return ans > (n * (n + 1) - 1) / 4; // 中位数，注意细节！
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	int l = 1, r = 1.1e9;
	while (l < r) { // 简单二分即可。
		int mid = l + r >> 1;
		if (chk(mid)) l = mid + 1;
		else r = mid;
	}
	return printf("%lld", l - 1), 0;
}
```

---

## 作者：xukehg (赞：0)

vp 时花了二十分钟才切，没想到以前还做过。

设序列 $a$ 长度为 $n$，设 $x$ 是 $a$ 的中位数，则排序后 $a_{\lceil\frac{n}{2}\rceil} = x$，也就是说有至少 $\frac{n}{2}$ 个数大于等于 $x$。考虑二分，尝试验证 $k \leq x$，的正确性，最后一个正确的数即为 $x$。

考虑将小于 $k$ 的数标为 $-1$，否则标为 $1$。则一个连续子序列的中位数大于等于 $k$ 相当与在新序列中和大于等于 $0$。换一种说法，记 $sum_i$ 为新序列前 $i$ 项之和，则中位数大于 $k$ 的子序列数量为：$\sum\limits_{l=1}^n\sum\limits_{r=l}^n[sum_r - sum_{l - 1} \geq 0]$。如果前面的值大于 $\frac{(\frac{(n \times (n + 1))}{2} + 1)}{2}$，则为真，否则为假。

上式的维护是非常简单的：用树状数组动态维护即可。避免负数则可以给 $sum_i$ 加上一个较大值来处理。

[记录。](https://atcoder.jp/contests/arc101/submissions/61683513)

---

## 作者：Fire_Shadow_Dream (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc101_b)

## 题意
定义一个长度为 $S$ 序列的中位数为将序列内元素从小到大排序后第 $\lfloor\frac{S}{2}\rfloor+1$ 个数。

给定一个长度为 $n$ 的序列，令这个序列中的所有非空连续子序列的中位数成为一个新序列，显然序列长度为 $\frac{n(n+1)}{2}$ ，求这个新序列的中位数。

## 思路
首先有一个很常见的求中位数的思路：二分中位数的值 $sum$，让序列中小于 $sum$ 的数的权值定为 $-1$，大于等于 $sum$ 定位 $1$，如果满足所有数的权值和大于等于 $0$，则向右二分，否则向左二分。

那么我们也在这道题中应用这个思路。

我们依旧二分枚举一个 $sum$，然后定权值，接着计权值和大于等于 $0$ 的区间，如果满足区间数大于 $\lfloor\frac{n(n+1)/2+1}{2}\rfloor$ 则向右二分，否则向左二分。

求满足区间数用树状数组统计即可，只需要对权值数组做前缀和。

对于满足区间 $[l,r]$ 需要有 $s_r-s_{l-1}\le0$，那么我们在枚举到第 $i$ 位前缀权值和时，只需要知道前面（即前 $i-1$ 位）有多少前缀权值和小于等于当前前缀和，这个数就是以 $i$ 为右端点的满足区间数。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e6+90;
ll n,m,a[N],f[N];
ll tr[N],sum[N];
ll lowbit(ll x){
	return x&-x;
}
void add(ll x,ll z){
	for(int i=x;i<=(n<<1)+1;i+=lowbit(i)) tr[i]+=z;
}
ll query(ll x){
	ll res=0;
	for(int i=x;i;i-=lowbit(i)) res+=tr[i];
	return res;
}
bool check(ll mid){
	for(int i=1;i<=n;i++) sum[i]=(a[i]<f[mid] ? -1 : 1);
	ll tot=0;
	for(int i=1;i<=n;i++){
		sum[i]+=sum[i-1];
		tot+=query(sum[i]+n+1);
		if(sum[i]>=0) tot++;
		add(sum[i]+n+1,1);
	}
	for(int i=1;i<=n;i++) add(sum[i]+n+1,-1);
	return tot>=(n*(n+1)/2)/2;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],f[i]=a[i];
	sort(f+1,f+n+1);
	ll l=0,r=n+1;
	while(l+1<r){
		ll mid=l+r>>1;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<f[l];
	return 0;
}
```
记得离散化。

---

## 作者：Autream (赞：0)

#### 题意简述

定义一个长度为 $M$ 的序列的中位数为这个序列中第 $\lfloor \frac{M}{2} \rfloor +1$ 小的数。

现在有一个长度为 $N$ 的序列 $A$，将 $A$ 的所有子段的中位数取出来作为一个序列 $S$，问序列 $S$ 的中位数是多少。

---

#### 题目分析

~~早期 ABC 真的好变态~~

中位数有个性质：

- 如果 $x$ 是序列的中位数，那么这个序列中至少有一半的数 $\geq x$。

本题是求“中位数的中位数”。因为中位数具有单调性，所以考虑二分答案。

先将 $A$ 复制到另一个数组 $B$ 中，将 $B$ 排序。枚举答案在 $B$ 中的下标 $idx$。

`check` 怎么写？

对于一个序列 $[l,r]$ 和枚举的答案 $x$，我们把其中 $>x$ 的数标记为 $1$，$\leq x$ 的数标记为 $-1$，如果所有标记的和 $\geq0$，那么就说明这个序列的中位数肯定 $\geq x$。

序列 $A$ 中共有 $\frac{n\times(n+1)}{2}$ 个区间，如果其中有一半的区间的中位数 $\geq B_{idx}$（即有一半的区间的区间和 $\geq0$），那么就说明真正的中位数比 $B_{idx}$ 大，向有缩减区间，反之亦然。

设 $s_i$ 表示前 $i$ 个标记的和，求有多少个区间的和 $\geq0$就变成了有多少个 $s_i\geq s_j$。

可以使用类似逆序对的思想，用树状数组统计 $s$ 不同值域的数量。

**注意：由于 $s_i$ 可能小于 $0$，所以需要整体加上 $n$。**

---

#### AC Code

```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::cin>>a[i]
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
CI N=2e5+5;
int n,a[N],s[N],c[N<<1],d[N],b[N];
int lowbit(int x) {
    return x&(-x);
}
void update(int x,int v) {
    for(int i=x;i<=n*2;i+=lowbit(i)) {
        c[i]+=v;
    }
}
int query(int x) {
    int b=0;
    for(int i=x;i;i-=lowbit(i)) {
        b+=c[i];
    }
    return b;
}
bool check(int x) {
    int cnt=0;
    rep(i,1,n) {
        s[i]=s[i-1];
        if(std::l_b(arrall(b,n),a[i])-b<=x) {
            s[i]--;
        } else {
            s[i]++;
        }
    }
    mem(c,0);
    rep(i,1,n) {
        update(s[i-1]+n,1ll);
        cnt+=i-query(s[i]+n);//统计到s[i]位置有多少个“逆序对”
    }
    return cnt>=n*(n+1)/2/2+1;//真实答案大于等于b[x]
}
signed main() {
    std::cin>>n;
    arrin(a,n);
    rep(i,1,n){ //离散化
        b[i]=a[i];
    }
    std::sort(arrall(b,n));
    int l=0,r=n,idx;
    while(l<=r) {
        int mid=l+r>>1;
        if(check(mid)) {//mid小了，向大的缩减
            r=mid-1;
            idx=mid;
        } else {
            l=mid+1;
        }
    }
    std::cout<<b[idx];
    return 0;
}
```

---

## 作者：longdie (赞：0)

# D - Median of Medians  

看题目就应该可以猜出这道题是中位数的中位数。  

大概就是给定一个长度为 n 的序列,对它的所有连续子区间拿出来求中位数(如果是偶数长度就取较大的那个),再将这些中位数排起来求中位数,问这个中位数是什么。  

这道题是一道不错的题目吧，反正我没想出来，挺菜的。  

直接考虑二分答案，然后我们可以进行操作，把小于等于 mid 的设为 -1，把大于它的设为 1，再求出前缀和，这样如果一个区间的和大于 0, 那么就是合法的。
注意二分答案的是区间的中位数为小于等于 mid 的区间有多少个。  
然后考虑如何维护，其实可以用树状数组维护就行了。  

代码不长 
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
inline int read(int x = 0) { return scanf("%d", &x), x; }
int n, a[N], c[N], b[N], sum[N], d[N];
ll cnt, value;
inline int lowbit(int x) { return x & -x; }
inline void add(int p) {
	while(p <= 2*n + 1) { c[p]++, p += lowbit(p); }
}
inline ll get(int p, ll tmp = 0) {
	while(p) { tmp += c[p], p -= lowbit(p); }
	return tmp;
}
bool pan(int mid) {
	cnt = 0;
	for(register int i = 1; i <= n; ++i) 
		b[i] = a[i] > mid ? -1 : 1, sum[i] = sum[i-1] + b[i];
	memset(c, 0, sizeof(c));
	add(n+1);
	for(register int i = 1; i <= n; ++i) {
		cnt += get(sum[i] + n), add(sum[i] + n + 1);
	}
	return cnt >= value;
}
int main() {
	n = read(), value = 1ll*n*(n+1)/4+1;
	for(int i = 1; i <= n; ++i) d[i] = a[i] = read();
	sort(d + 1, d + n + 1);
	int l = 1, r = n, mid = 0;
	while(l <= r) {
		mid = (l + r) / 2;
		if(pan(d[mid])) r = mid - 1;
		else l = mid + 1;
	}
	cout << d[l] << '\n';
	return 0;
}
```

---

