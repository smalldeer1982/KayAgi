# Scalar Queries

## 题目描述

给出一个数组$a_1,a_2,...,a_n$，其中所有元素两两不同。

定义函数$f(l,r)$：

- 定义数组$b_1,b_2,...,b_{r-l+1}$，其中$b_i=a_{l-1+i}$
- 将$b$按从小到大排序
- 则此时函数的值是$\sum\limits_{i=1}^{r-l+1}{b_i}\cdot i$

请计算对于所有满足$1 \le l \le r \le n$的$l$和$r$，$f(l,r)$的和。

由于结果可能很大，请输出对$10^9+7$取模的值。

## 说明/提示

$1 \le n \le 5 \cdot 10^5$, $1 \le a_i \le 10^9$, 所有$a_i$两两不同。

样例1解释：

$ f(1, 1) = 5 \cdot 1 = 5 $ ;

$ f(1, 2) = 2 \cdot 1 + 5 \cdot 2 = 12 $ ;

$ f(1, 3) = 2 \cdot 1 + 4 \cdot 2 + 5 \cdot 3 = 25 $ ;

$ f(1, 4) = 2 \cdot 1 + 4 \cdot 2 + 5 \cdot 3 + 7 \cdot 4 = 53 $ ;

$ f(2, 2) = 2 \cdot 1 = 2 $ ;

$ f(2, 3) = 2 \cdot 1 + 4 \cdot 2 = 10 $ ;

$ f(2, 4) = 2 \cdot 1 + 4 \cdot 2 + 7 \cdot 3 = 31 $ ;

$ f(3, 3) = 4 \cdot 1 = 4 $ ;

$ f(3, 4) = 4 \cdot 1 + 7 \cdot 2 = 18 $ ;

$ f(4, 4) = 7 \cdot 1 = 7 $ ;

## 样例 #1

### 输入

```
4
5 2 4 7
```

### 输出

```
167
```

## 样例 #2

### 输入

```
3
123456789 214365879 987654321
```

### 输出

```
582491518
```

# 题解

## 作者：mraymes (赞：14)

本文章将同步到 [Hexo 博客](https://mraymes.github.io/).

这题是一道**非常难想**的线段树 / 树状数组题.

其实这道题可以算是 [P2345](https://www.luogu.org/problemnew/show/P2345) 的升级版. 如果理解本题有困难, 那么可以先去看看 P2345.

## 简化式子

我们将题意稍微简化一下:  
- 给你一个数组 $a$.
- 设 $a_i$ 在 $a_l, a_{l + 1}, \cdots, a_r$ 中为第 $ord_{i, l, r}$ 小.  
- 并且定义 $sum_i$ 为 $ord_{i, l, r} (1 \leqslant l \leqslant r \leqslant n)$ 之和. 
- $f(l, r)$ 的函数值为:  
    $$ \sum_{i = l}^{r}{a_i \cdot ord_{i, l, r}} $$
- 最后求的是:
    $$ \left(\sum_{1 \leqslant l \leqslant r \leqslant n}{f(l, r)}\right) \bmod (10^9 + 7) $$

我们可以把这个式子给~~瞎捣鼓一通~~分析一下, 最后会变成这样:  
$$ \sum_{i = 1}^n{a_i \cdot sum_i} $$  
换一种说法, 就是每一个元素乘它所在区间内比它小的数的个数加 $1$, 最后再相加所得的和.

## 计算

**这一步就是重点了!**

每当一个数大于另一个数时, 那么, 对于每一个同时包含两个数的区间内, 都会因为这个小数的存在而为大数的 $sum$ 值增加 $1$.  
如果这一部分有点难理解, 那么看下面的例子:  
$$ a = \{ 7, 2, 6, 8, 3, 1 \} $$  
我们现在分析的是 $6$ 的 $sum$ 值.  
在左侧有一个 $2$ 比 $6$ 小, 因此:  
```cpp
for (int i = 1; i <= 2; i++) { // 2 为 2 在 a 中所在的位置
    for (int j = 3; j <= 6; j++) { // 3 为 6 的位置, 6 为总数
        ord[3][i][j]++;
        sum[3]++;
    }
}
```
那么, 类似地, 因为右侧 $3$ 的存在, 所以:  
```cpp
for (int i = 1; i <= 3; i++) { // 3 为 6 的位置
    for (int j = 5; j <= 6; j++) { // 5 为 3 的位置
        ord[3][i][j]++;
        sum[3]++;
    }
}
```
相信在这里应该可以比较容易地得出一定的规律了.

该规律就是:  
设当前分析的数为 $a_i$.  
设 $L$ 为比 $a_i$ 小并且在其**左侧**的所有数所处的位置 (下标) 的集合.  
$R$ 为比 $a_i$ 小并且在其**右侧**的所有数所处的位置 (下标) 的集合.  
相信大家也已经发现了, 同时包含 $a_l$ 和 $a_r$ 的区间 $(1 \leqslant l \leqslant r \leqslant n)$ 的数量为 $l \cdot (n - r + 1)$.

当然也不要忘了这个数本身, 因为上面 $sum_i$ 以及 $ord_{i, l, r}$ 增加都是因为有数比 $a_i$ 小, 然而我们要计算的是**从 $1$ 开始的**排名, 所以必须再加上当前数所在的区间总数. 这里应该不难理解, 因为如果区间 $[l, r]$ 没有同时包含 $a_i$ 与比 $a_i$ 小的数, 那么 $ord_{i, l, r} = 1$; 如果包含了的话, 那么仍然需要加 $1$, 因为 $ord_{i, l, r}$ 中存储的目前只是在区间 $[l, r]$ 中比 $a_i$ 小的数的数量.

包含一个数 $a_i$ 的区间数量也不难算, 那就是 $i \cdot (n - i + 1)$.

那么, 我们就可以得到如下公式:  
$$ sum_i = \sum_{x \in L}{\left(x \cdot (n - i + 1)\right)} + \sum_{x \in R}{\left(i \cdot (n - x + 1)\right)} + i \cdot (n - i + 1) $$  
$$ sum_i = \sum_{x \in L}{x} \cdot (n - i + 1) + \sum_{x \in R}{(n - x + 1)} \cdot i + i \cdot (n - i + 1)$$

## 数据结构维护

如何维护 $L$ 和 $R$ 的和? 那就需要用到~~某些毒瘤~~数据结构了, 这里使用的是线段树. ~~因为我不会树状数组.~~

线段树如何使用也是一个重点.

要保证线段树中存储的下标所对应的数都小于当前要分析的数, 那就应该先将原数组进行排序, 然后从小到大处理.

但是又因为要根据 $R$ 的大小决定 $n + 1$ 的部分应该加几遍 (具体见上面公式), 我们又要存一个 $cnt$ 值, 表示当前区间内有多少个下标已经被存进去.

最后代码如下:  
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef pair<ull, ull> puu;

const ull MOD = 1000000007ULL;

struct st_node_t {
    ull sum;
    ull cnt; // 最好全开 ull, 否则会挂掉
};

int n;
puu a[500001];
st_node_t st[2000001];
ull sum = 0;

template <typename T>
inline T read() {
    T x = 0;
    T multiplier = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            multiplier = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * multiplier;
}

void modify(int u, int l, int r, int idx, ull val) {
    if (l == r) {
        st[u].sum = val; // 插入新数
        st[u].cnt = 1;   // 当前区间内有 1 个数
        return;
    }

    int mid = l + (r - l >> 1);
    if (idx <= mid) {
        modify(u << 1, l, mid, idx, val);
    } else {
        modify(u << 1 | 1, mid + 1, r, idx, val);
    }

    // 更新
    st[u].sum = (st[u << 1].sum + st[u << 1 | 1].sum) % MOD;
    st[u].cnt = (st[u << 1].cnt + st[u << 1 | 1].cnt) % MOD;
}

ull query_sum(int u, int l, int r, int lq, int rq) { // 询问下标之和
    if (l == lq && r == rq) {
        return st[u].sum % MOD;
    }

    int mid = l + (r - l >> 1);
    if (rq <= mid) {
        return query_sum(u << 1, l, mid, lq, rq);
    } else if (lq > mid) {
        return query_sum(u << 1 | 1, mid + 1, r, lq, rq);
    } else {
        return (query_sum(u << 1, l, mid, lq, mid)
                + query_sum(u << 1 | 1, mid + 1, r, mid + 1, rq))
               % MOD;
    }
}

ull query_cnt(int u, int l, int r, int lq, int rq) { // 询问数量
    if (l == lq && r == rq) {
        return st[u].cnt % MOD;
    }

    int mid = l + (r - l >> 1);
    if (rq <= mid) {
        return query_cnt(u << 1, l, mid, lq, rq);
    } else if (lq > mid) {
        return query_cnt(u << 1 | 1, mid + 1, r, lq, rq);
    } else {
        return (query_cnt(u << 1, l, mid, lq, mid)
                + query_cnt(u << 1 | 1, mid + 1, r, mid + 1, rq))
               % MOD;
    }
}

int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i].first = read<ull>();
        a[i].second = i; // 记录原下标
    }

    sort(a + 1, a + n + 1); // 按大小排序

    for (int i = 1; i <= n; i++) {
        ull sum1 = query_sum(1, 1, n, 1, a[i].second); // idx_l[] 中所有数之和
        ull sum2 = query_sum(1, 1, n, a[i].second, n); // idx_r[] 中所有数之和
        ull cnt2 = query_cnt(1, 1, n, a[i].second, n); // idx_r[] 的大小

        // 这里要疯狂取模, 因为不取模很容易爆 ull
        sum += (sum1 * (n - a[i].second + 1) % MOD
                + ((n + 1) * cnt2 + MOD - sum2) % MOD * a[i].second % MOD)
               * a[i].first % MOD;
        sum %= MOD;
        sum += a[i].second * (n - a[i].second + 1) % MOD * a[i].first % MOD;
        sum %= MOD;
        modify(1, 1, n, a[i].second, a[i].second);
    }

    printf("%llu\n", sum);

    return 0;
}
```

如果看懂了就留个赞, 写题解不容易啊w...  
如果不懂就在评论区留言, 我会根据需求来修改.


---

## 作者：程就未来 (赞：6)

### 1.观察题目，容易想出暴力做法
枚举字串，每个子串sort一边，加上答案，时间复杂度O(n^3×logn)

### 2.更快的做法
看数据范围n <= 1e5 , 肯定不能枚举子串了。
这时候考虑枚举点ai，这个点对于最后答案的贡献是 ， 所有包含ai的子串中比ai小的数的个数和×ai。
比如样例

4

5 2 4 7

比如4这个数，假设4在每个子串中是最小的，那么贡献为所有包含4子串个数6×6 。

但ai的贡献答案显然>=它。

观察2 4 ， 包含“2 4”的子串中，2这个数因为比4小使4的rk变大了。那么加上，包含“2 4”的子串个数4 , 再 ×4 ， 最后得4这个数的贡献是4×4 + 6×4 = 40.

依次类推，5的贡献是（4 + 5）× 5 , 2的贡献是6 × 2 ， 7的贡献是（4 + 6）×7, 最后得答案167

枚举每个点ai，再枚举每个比ai小的点aj。 时间复杂度O（n^2）

### 3. 优化
在2.中我们已经知道ai的贡献是，（经过ai的子串个数+经过ai和aj（ai<aj））的字串个数） ×  ai

即j × (n - i + 1)

其中对于每一个i，n-i+1是固定的，j是变量 ， 这时候就可以用权值线段树优化了

首先离散化，线段树中存第i大的数的位置。

枚举每个数，求和线段树中1~i-1的值，再在线段树中ai的位置加上i

时间复杂度O（nlogn）

### 4.code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define lowbit(x) x & -x
#define R register int
const int N = 1e6 + 5 , P = 1e9 + 7;

ll n , a[N] , b[N] , c[N] , t[N] , cnt[N] , ans;

inline ll read() {
	ll s = 0 , w = 1 ; char ch = getchar();
	while(ch < 48 || ch > 57) {if(ch == '-') w = -1; ch = getchar();}
	while(ch >= 48 && ch <= 57) s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar();
	return s * w;
}

inline void update(int x , int y) {while(x <= n) c[x] += y , c[x] %= P , x += lowbit(x) ;}

inline ll query(int x) {
	ll res = 0 ;
	while(x) res = (res + c[x]) % P , x -= lowbit(x);
	return res % P;
}

bool cmp(ll A , ll B) {return A < B;}

ll find(ll x) {
	int l = 1 , r = n , mid ;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(b[mid] < x) l = mid + 1;
		else if(b[mid] > x) r = mid - 1;
		else return mid;
	}
}

int main() {
	R i , j;
	n = read();
	for(i = 1 ; i <= n ; ++ i) a[i] = b[i] = t[i] = read();
	sort(b + 1 , b + n + 1 , cmp);
	for(i = 1 ; i <= n ; ++ i) {
		ll num = find(a[i]);
		update(num , i);
		cnt[i] = (cnt[i] + query(num - 1) * (n - i + 1) % P) % P;
	}
	memset(c , 0 , sizeof(c));
	for(i = 1 ; i <= n ; i ++) a[i] = b[i] = t[n - i + 1];
	sort(b + 1 , b + n + 1 , cmp);
	for(i = 1 ; i <= n ; ++ i) {
		ll num = find(a[i]);
		update(num , i); 
		cnt[n - i + 1] = (cnt[n - i + 1] + query(num - 1) * (n - i + 1) % P ) % P ; 
	}
	for(i = 1 ; i <= n ; ++ i) cnt[i] = (cnt[i] + i * (n - i + 1) % P) % P;
	for(i = 1 ; i <= n ; i ++) ans = (ans + cnt[i] * t[i] % P) % P;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：_ztyqwq (赞：5)

*2300的数学（？）题，值得一做

题意：定义 $ f(l,r) = \sum\limits_{i=l}^r a_i \cdot rk_{i,l,r} $，其中 $ rk_{i,l,r} $ 代表 $ a_i $ 在 $ a_l, ..., a_r $ 中的排名，求所有 $ f(l,r) $（所有区间内） 的和（取模）

数据范围 $ n \leqslant 5 \cdot 10^5 $，应该是个 $ O(n\log n) $ 的算法（当然如果哪位大佬有 $ O(n) $ 算法欢迎评论区爆踩~~不过似乎没有~~）

怎么做？

首先考虑一个数在包含它的所有区间中的贡献，这时 $ a_i $ 可以提出，所以需要计算排名之和

排名这东西不好搞，我们考虑转化一下

假设 $ x $ 这个数在五个不同的区间中排名分别为 $ 1,1,2,2,3 $，那它对排名和的贡献是 $ (1+1+2+2+3)x $

但我们也可以写成 $ [(1+1+1+1+1)+(0+0+1+1+1)+(0+0+0+0+1)]x = (5+3+1)x $

发现什么了吗？

~~经过漫长时间的理解与思考~~扩展到一般情况：

· 对于所有 $ x $ 数排名**至少**是 $ 1 $ 的区间，计算贡献 = 这样的区间数

· 对于所有 $ x $ 数排名**至少**是 $ 2 $ 的区间，计算**额外**贡献 = 这样的区间数

· 对于所有 $ x $ 数排名**至少**是 $ 3 $ 的区间，……

所以我们可以考虑包含 $ x $ 的区间，先令右端点不断向右移。**一旦 $ x $ 的排名增加了 $ 1 $，则接着延申时所有的区间都会额外产生 $ 1 $ 的贡献（包括这一个），所以可以把之后的区间数量累加到排名和中。**

双向延申也是一样，**只要任意一边（左/右）移动时（不妨设移动后的区间为 $ [l,r] $）$ x $ 的排名增加 $ 1 $，那么所有包含 $ [l,r] $ 的区间都会额外产生 $ 1 $ 的贡献，将包含 $ [l,r] $ 的区间数累加到排名和中。**

~~get？~~

~~手动模拟例子见mraymes神仙的题解，或者样例~~

接下来，我们看如何计算这个东西

$ x $ 排名增加 $ 1 \Leftrightarrow $ 有一个数比 $ x $ 小

包含 $ [l,r] $ 的区间（不妨设是 $ [i,j] $）$ \Leftrightarrow 1 \leqslant i \leqslant l, r \leqslant j \leqslant n $

所以数量为 $ l(n-r+1) $（$ i $ 有 $ l $ 种，$ j $ 有 $ n-r+1 $ 种）

所以 $ i $ 对答案的贡献是

$ a_i[i(n-i+1) + \sum\limits_{i<j\leqslant n, a_j<a_i}i(n-j+1) + \sum\limits_{1\leqslant j<i, a_j<a_i}j(n-i+1)] $

前一个 $ \sum $ 是 $ j $（让 $ a_i $ 排名增加的那个数）在 $ i $ 右边的情况，后一个是在左边

再说得清楚一点，如果区间包含 $ a_j $，$ a_i $ 的排名就会增加，所以所有同时包含 $ i $ 和 $ j $ 的区间都要累加 $ 1 $ 的贡献，这样的区间一共有 $ i(n-j+1) $（$ j $ 在右，$ [i,j] $）个或 $ j(n-i+1) $（$ j $ 在左，$ [j,i] $）个

前面那个 $ i(n-i+1) $ 是初始排名 $ 1 $（所有区间都有）

**别忘了乘以 $ a_i $！**

累加每个 $ i $ 对答案的贡献就能得到答案啦~

看起来还是 $ O(n^2) $……~~（当然暴力是 $ O(n^3\log n) $，已经进步啦）~~

考虑优化

在 $ i $ 对答案的贡献中（就上面那个很长的式子），$ i(n-i+1) $ 是 $ O(1) $ 的，所以我们只关注后面两个 $ \sum $。两个处理方法类似，我们看第二个

$ \sum\limits_{1\leqslant j<i, a_j<a_i}j(n-i+1) = (n-i+1)\sum\limits_{1\leqslant j<i, a_j<a_i}j $（提出只跟 $ i $ 有关的）

所以只要考虑后面那个 $ \sum $，也就是如何做出**比 $ a_i $ 小的数中，在 $ a_i $ 前面的（下标更小）那些的下标之和**

~~显然需要某些数据结构~~

因为涉及权值排序，我们考虑所有的数一起做（不按下标一个一个来）

我们根据权值进行排序，**从 $ a_i $ 最小的数开始，到 $ a_i $ 最大的数这样的顺序进行计算**

我们用一个树状数组来维护 $ a_1, ..., a_n $ 的下标，当然 $ a_i $ 的下标就是 $ i $。但因为我们只计算比当前数权值小的数的下标和，所以此时比当前数权值大的数的下标我们需要设成 $ 0 $。

发现在计算 $ a_i $ 的贡献时，所有权值比 $ a_i $ 小的数都做过了，这些数的下标需要累加；比 $ a_i $ 大的数都没有做过，这些数的下标需要设成 $ 0 $。

这启发我们可以**先清空树状数组，在计算完一个数对答案的贡献后，将树状数组中设成它的下标“恢复”（也就是从 $ 0 $ 变为它真正的下标）**，为以后的计算做准备。

这样我们就可以计算**比 $ a_i $ 小的数中，在 $ a_i $ 前面的（下标更小）那些的下标之和**了（树状数组查询 $ 1 $ ~ $ i-1 $）

后一个 $ \sum $ 同理，可以用同一个树状数组（但是要维护这一段比 $ a_i $ 小的数的数量，以计算有多少个 $ n-1 $），当然也可以暴力再开一个树状数组，下面代码就是清空树状数组重新维护的（这时维护的是 $ n - j + 1 $，不再是单独的下标 $ j $）

~~（其实是为了代码对称 **强迫症**）~~

~~然后就做完了~~

~~就没有然后了~~

几点提醒：

1. 最好 ```#define int long long```，不然指不定哪里就忘了

2. 算两个 $ \sum $ 时枚举的是排名，不是下标，所以要转换一下

3. 记得时刻取模 ~~（取膜）~~

4. 减法要先加上模数再取模，不然可能会出现负数

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1000000007;
int n,a[500001];
struct number
{
	int x,ind;
	number(int x=0,int i=0):x(x),ind(i){} 
	bool operator<(const number& ano)const
	{
		return x<ano.x;
	}
}num[500001];
int c[500001];
inline int lowbit(int x)
{
	return x&-x;
}
void add(int x,int a)
{
	for(int i=x;i<=n;i+=lowbit(i))
		c[i]=(c[i]+a)%mod;
}
int sum(int x)
{
	int ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans=(ans+c[i])%mod;
	return ans%mod;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		num[i]=number(a[i],i);
	}
	sort(num+1,num+n+1);
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+i*(n-i+1)%mod*a[i])%mod;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)
	{
		int x=num[i].ind;
		ans=(ans+(n-x+1)*sum(x)%mod*a[x])%mod;
		add(x,x);
	}
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)
	{
		int x=num[i].ind;
		ans=(ans+x*(sum(n)-sum(x)+mod)%mod*a[x])%mod;
		add(x,n-x+1);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：3)

难度适中的 2300，还是不错的。

对于 $a_{l \ldots r}$，我们知道每个 $a_k$ 的排名为：

$$
1 + \sum_{j = l} ^ r [a_j < a_k].
$$

那么答案就是：

$$
\sum_{1 \le l \le r \le n} f(l, r) = \sum_{1 \le l \le r \le n} \sum_{k = l}^r a_k\left(1 + \sum_{j = l} ^ r [a_j < a_k]\right).
$$

这里有个多余的 $1$，我们直接拆开单独算贡献，就是 $\displaystyle \sum_{i = 1} ^ n a_i \cdot i(n - i + 1)$，接下来考虑一下剩余部分。

考虑枚举 $a_i$ 贡献了几次。想象一下我们有两个下标 $i, j$ 满足 $a_i < a_j$，那么他们可能同时存在的区间数量为 $\min(i, j) \cdot (n - \max(i, j) + 1)$，那么我们的式子可以转换为：

$$
\begin{aligned}
\sum_{i = 1} ^ n a_i\left[\sum_{j < i, a_j < a_i}j(n - i + 1) + \sum_{j > i, a_j < a_i} i(n - j + 1)\right].
\end{aligned}
$$

我们从小到大排序就可以将 $a_j < a_i$ 的那一维给去掉，接着用树状数组维护一下 $\displaystyle \sum_{j < i} j$ 和 $\displaystyle \sum_{j > i} (n - j + 1)$ 就行了，时间复杂度 $\mathcal{O}(n \log n)$。

参考代码如下：

```cpp
/*
 * author: LostKeyToReach
 * created time: 2025-05-14 13:37:27
 */
#include <bits/stdc++.h>
#define int long long
#define vi vt<int>
using ll = long long; using pii = std::pair<int, int>;
template<typename T> using vt = std::vector<T>;
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define For(i, a, b) for(int i = (a); i <= (b); ++i)
#define Rof(i, a, b) for(int i = (a); i >= (b); --i)
#define S std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0)
template<typename T> T chkmax(T& x, T y) {
    return (x < y) ? (x = y, y) : x;
} template<typename T> T chkmin(T& x, T y) {
    return (x > y) ? (x = y, y) : x;
}int fio = (S, 0); constexpr int N = 5e5 + 5, mod = 1e9 + 7;
struct Fenw {vi f; int n;
    Fenw(int n) : n(n), f(n + 1, 0) {}
    void add(int x, int y) {
        for (; x <= n; x += x & -x) (f[x] += y) %= mod;
    } int qry(int x) { int ans = 0;
        for (; x > 0; x -= x & -x) (ans += f[x]) % mod;
        return ans;}
}; int32_t main() {int n, ans = 0, tot = 0; std::cin >> n;
    vi a(n + 1); For(i, 1, n)  std::cin >> a[i],
        (ans += i * (n - i + 1) % mod * a[i] % mod) %= mod;
    vt<pii> ord; For(i, 1, n) ord.emplace_back(a[i], i);
    std::sort(ord.begin(), ord.end()); Fenw fl(n), fr(n);
    for (auto& [v, id] : ord) {
        (ans += ((n - id + 1) * fl.qry(id - 1) % mod 
            + id * (tot - fr.qry(id) + mod) % mod) % mod * v % mod) %= mod;
        fl.add(id, id), fr.add(id, n - id + 1);
        (tot += n - id + 1) %= mod;
    } std::cout << (ans + mod) % mod << "\n";
}
```

---

## 作者：vme50xiex2 (赞：3)

简单的。

发现 $a_{pos}$ 在 $[l,r]$ 中的贡献即为 $[l,r]$ 中小于等于 $a_{pos}$ 的数的个数。因此考虑从小到大加数，将加过的位置置为 $1$，剩下的数置为 $0$，则系数即为 $s_r-s_{l-1}$，其中 $s$ 为前缀和数组。

那么 $a_{pos}$ 的总贡献即为：
$$
\begin{aligned}
ans&=a_{pos}\times\sum_{i=1}^{pos}\sum_{j=pos}^{n}s_j-s_{i-1}\\
&=a_{pos}\times(-\sum_{i=1}^{pos}s_{i-1}\times(n-pos+1)+ \sum_{j=pos}^{n}s_j \times pos)
\end{aligned}
$$

只需在前缀和上维护区间加，区间和即可。易于用树状数组维护，时间复杂度 $\mathcal{O(n\log n)}$。

$\mathcal{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 10;
const int MOD = 1e9 + 7;
struct BIT {
	int c[N];
	void Add(int pos, int k);
	int Sum(int pos);
	int Sum(int l, int r);
} t1, t2;
int n, id[N], a[N];
inline int Add(int x, int y) {
	return x + y >= MOD ? x + y - MOD : x + y;
}
inline void BIT::Add(int pos, int k) {
	while(pos <= n) c[pos] = ::Add(c[pos], k), pos += pos & -pos;
}
inline int BIT::Sum(int pos) {
	int ans = 0;
	while(pos > 0) ans = ::Add(ans, c[pos]), pos -= pos & -pos;
	return ans; 
}
inline int BIT::Sum(int l, int r) {
	return ::Add(Sum(r), MOD - Sum(l - 1));
}
inline int Sum(int l, int r) {
	int ans = 1ll * t1.Sum(l - 1) * (r - l + 1) % MOD;
	ans = Add(ans, 1ll * t1.Sum(l, r) * (r + 1) % MOD);
	ans = Add(ans, MOD - t2.Sum(l, r));
	return ans;
}
signed main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), id[i] = i;
	sort(id + 1, id + n + 1, [](int x, int y) { return a[x] < a[y]; });
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		int pos = id[i], cnt = 0;
		t1.Add(pos, 1), t2.Add(pos, pos);
		cnt = Add(cnt, 1ll * Sum(pos, n) * pos % MOD);
		cnt = Add(cnt, MOD - 1ll * Sum(1, pos - 1) * (n - pos + 1) % MOD);
		ans = Add(ans, 1ll * a[pos] * cnt % MOD);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：justin_cao (赞：3)

感觉这道题目巨妙。。

首先我们考虑把$b_i\times i$的$i$给展开成有多少个数$\leq i$。

这种转化非常的妙，可以简化题目。。

那么我们考虑一对数$(i,j)$，假设$a_j<a_i$，那么按照上面的考虑，那么$i$对$j$的贡献就非常明显了：
$$
f(i,j)=j\times(n-i+1)\times a_i
$$
这个也是非常清楚，就是包含$i$和$j$的区间有$j\times (n-i+1)$个，然后每个都会构成$a_i$的贡献。

所以我们考虑对于每一个$j$，都考虑后面的比他大的$i$，并将他们求和。那么会发现，$(n-i+1)\times a_i$对于每个$i$都是不会变的，于是我们考虑可以用树状数组来存下每个点的$(n-i+1)*a_i$，那么剩下的就是从后往前扫一遍，然后求一下比他大的数的贡献之和即可。。。

**但是要记住，这个只算了一边，对于另一边的$j>i$而$a_j<a_i$的贡献并没有算，所以必须再从前到后地去扫一遍，再用相同的方法算一遍即可** 

下面是本人丑陋的代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 500010
#define mod 1000000007
using namespace std;
typedef long long ll;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n;
int a[maxn];
int b[maxn];
int find(int x)
{
    return lower_bound(b+1,b+n+1,x)-b;
}
int t[maxn];
int lowbit(int x)
{
    return x&(-x);
}
int query(int x)
{
    int res=0;
    for(int i=x;i;i-=lowbit(i))  res=(res+t[i])%mod;
    return res;
}
void modi(int x,int y)
{
    for(int i=x;i<=n;i+=lowbit(i))  t[i]=(t[i]+y)%mod;
}
int res;
int main()
{
    n=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   b[i]=a[i];
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)   a[i]=find(a[i]);
    for(int i=n;i>=1;i--)
    {
        int tmp=(query(n)-query(a[i])+mod)%mod; 
        modi(a[i],1ll*b[a[i]]*(n-i+1)%mod);
        res=(res+1ll*i*tmp%mod)%mod;
    }
    memset(t,0,sizeof(t));
    for(int i=1;i<=n;i++)
    {
        int tmp=(query(n)-query(a[i])+mod)%mod; 
        modi(a[i],1ll*b[a[i]]*i%mod);
        res=(res+1ll*(n-i+1)*tmp%mod)%mod;
    }   
    for(int i=1;i<=n;i++)   res=(res+1ll*b[a[i]]*i%mod*(n-i+1)%mod)%mod;
    printf("%d\n",res);
    return 0;
}
```


---

## 作者：ziyistudy (赞：2)

我们设 $sum_i$ 为 $a_i$ 在所有包含它的区间中的排名总和。

则可以将题目转换为：

$$ {\textstyle \sum \limits_{i=1}^{n}} a_i \times sum_i$$

对于一个 $a_i$，比它小的数都会使在共同包含它们俩的每个区间中 $a_i$ 的排名增加 $1$。

形式化地，对于 $1\leq i<j\leq n$ 且 $a_i<a_j$，点对 $(i,j)$ 对答案的贡献为：$a_j\times i\times (n-j+1)$。因为同时包含 $i,j$ 的区间有 $i\times (n-j+1)$ 个，每个区间中的 $a_j$ 都因为有 $a_i$ 所以排名加 $1$。

再回到 $a_i$，这时我们就可以写出 $a_i$ 对答案的贡献了：

$$a_i\times i \times (n-i+1)+{\textstyle \sum \limits_{j=1}^{i-1}} a_i \times j\times (n-i+1)[a_j< a_i]+{\textstyle \sum \limits_{j=i+1}^{n}} a_i \times i\times (n-j+1)[a_j< a_i]$$

因为 $a_i$ 在包含自己的所有区间中本身就排名为 $1$（包含自己的区间有 $i \times (n-i+1)$ 个），然后考虑 $j$ 分别在 $i$ 左边和右边的贡献，固得到上式。

直接求上面的式子是 $O(N^2)$，考虑如何优化计算过程。

我们先只看第二个加法部分（及 $j$ 在 $i$ 的左边）。

我们相当于是要求“又比 $a_i$ 小，又在 $i$ 左边的数的**下标总和**”。这不就可以用线段树（或树状数组）优化吗！

我们先将 $a$ 排序，从小到大进行遍历。设当前遍历的 $a_i$ 在原数组的位置为 $dir_i$，每次查询区间 $1$ 至 $dir-1$ 的区间和，然后再让线段树的 $dir$ 位置赋值为 $dir$ 即可。

感谢 _ztyqwq 大佬的启发。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=1e9+7;
// head
const int N=5e5+5;
int a[N],ans[4*N];
vector<PII> V(N);
int ls(int x) {return x<<1;}
int rs(int x) {return x<<1|1;}
void push_up(int dir)
{
    ans[dir]=ans[ls(dir)]+ans[rs(dir)];
}
void modify(int dir,int l,int r,int x,int k)
{
    if(l==x&&r==x) {ans[dir]=k;return ;}
    int mid=(l+r)>>1;
    if(x<=mid) modify(ls(dir),l,mid,x,k);
    else modify(rs(dir),mid+1,r,x,k);
    push_up(dir); 
}
int query(int qx,int qy,int x,int y,int dir)
{
    int sum=0;
    if(qx<=x&&y<=qy) return ans[dir];
    int mid=(x+y)>>1;
    if(qx<=mid) sum+=query(qx,qy,x,mid,ls(dir));
    if(qy>mid) sum+=query(qx,qy,mid+1,y,rs(dir));
    return sum;
}
signed main() 
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n;cin>>n;
    int sum=0;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        V[i]={a[i],i};
        (sum+=i*(n-i+1)%MOD*a[i]%MOD)%=MOD;
    }
    sort(V.begin()+1,V.begin()+n+1);
    for(int i=1;i<=n;i++){
        int now=V[i].se;
        (sum+=(n-now+1)*a[now]%MOD*(query(1,now,1,n,1)%MOD)%MOD)%=MOD;
        modify(1,1,n,now,now);
    }
    memset(ans,0,sizeof(ans));
    for(int i=1;i<=n;i++){
        int now=V[i].se;
        (sum+=now*a[now]%MOD*(query(now,n,1,n,1)%MOD)%MOD)%=MOD;
        modify(1,1,n,now,n-now+1);
    }
    cout<<sum<<endl;
}
```

---

## 作者：wcyQwQ (赞：2)

~~再不写题解要掉社贡了~~

简单题，考虑一个 $a_i$ 对 $f(l, r)$ 的贡献，显然是 $\left(\sum_{j = l}^r [a_j <a_i]\right) +1$。

那么我们就可以算出 $a_i$ 对答案的贡献了，即为
$$
\begin{aligned}
&\sum_{l = 1}^i\sum_{r = i}^n\sum_{j = l}^r([a_j <a_i]+ 1)\\
&= \left(\sum_{j = 1}^n\sum_{l = 1}^{\min(i, j)}\sum_{\max(i, j)}^n 1 \right)+n(n - i +1)\\
&= \left(\sum_{j = 1}^{i - 1}[a_j < a_i]j(n - i +1)\right) + \left(\sum_{j = i +1}^n[a_j < a_i]i(n - j +1)\right) + n(n - i +1)
\end{aligned}
$$
不难发现是二维偏序形式，用 BIT 正反各扫一遍即可。时间复杂度 $O(n\log n)$。[Code](https://codeforces.com/contest/1167/submission/214032038)

---

## 作者：kouylan (赞：2)

首先很容易想到，我们可以对于每个数分开算答案。那么，就是要求对于 $i$，包含 $i$ 的子段中 $rank_i$ 之和。排名和记为 $t_i$，有 $t_i=s(rank_i\geq1)+s(rank_i\geq2)+\dots$

很显然只有 $a_j\leq a_i$ 的才会对 $t_i$ 产生影响。所以我们只考虑这部分，答案就是对于 $i,j$，包含 $i,j$ 的子段数之和。以下分类讨论：

若 $i\leq j$，对答案的贡献是 $i\times (n-j+1)$。

若 $i>j$，对答案的贡献是 $j\times (n-i+1)$。

推到这里，发现我们只需要用树状数组维护个数和下标和，正反各做一遍即可。

下面是 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define lowbit(i) (i&-i)

const int M = 1e9+7ll;

int n,ans,a[500005],b[500005],t[500005];
int c1[500005],c2[500005];

void lsh_()
{
	vector<int> v;
	for(int i=1;i<=n;i++)
		v.push_back(a[i]);
	sort(v.begin(),v.end());
	for(int i=1;i<=n;i++)
		b[i] = lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
}

void fix(int x,int v1,int v2)
{
	for(int i=x;i<=n;i+=lowbit(i))
		c1[i] += v1, c2[i] += v2;
}

int ask1(int x)
{
	int s=0;
	for(int i=x;i>=1;i-=lowbit(i))
		s = (s+c1[i])%M;
	return s;
}

int ask2(int x)
{
	int s=0;
	for(int i=x;i>=1;i-=lowbit(i))
		s = (s+c2[i])%M;
	return s;
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;cin>>a[i++]);
	lsh_();
	for(int i=1;i<=n;i++)	
		t[i] = i*(n-i+1)%M;
	for(int i=1;i<=n;i++)
	{
		int j=ask2(b[i]-1);
		t[i] = (t[i]+j*(n-i+1)%M)%M;
		fix(b[i],1,i);
	}
	memset(c1,0,sizeof(c1)), memset(c2,0,sizeof(c2));
	for(int i=n;i>=1;i--)
	{
		int cnt=ask1(b[i]-1),j=ask2(b[i]-1);
		t[i] = (t[i]+i*((n+1)*cnt%M-j)%M+M)%M;
		fix(b[i],1,i);
	}
	for(int i=1;i<=n;i++)
		ans = (ans+t[i]*a[i])%M;
	cout<<ans<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：fush (赞：1)

对于每个 $a_k$ 在 $[l, r]$ 排名为：

$$
\sum_{j = l} ^ r [a_j \le a_k].
$$

那么答案就是：

$$
\sum_{1 \le l \le r \le n} f(l, r) = \sum_{i = 1}^{n}a_k \left(\sum_{1\le l \le k \le r \le n}\sum_{j = l}^{r}[a_j \le a_i] \right)
$$

考虑怎么求后面的一坨。  

我们先离线后排序，来保证 $a_j \le a_i$，我们设后面的一坨为 $sum$。  
设 $j \le i$，那么区间最小为 $[j, i]$，那么左侧有 $j$ 种可能，右侧有 $n - i + 1$ 种，而 $j > i$ 同理。
$$
sum = (n - i +1) \times \sum_{j \le i} {j} + i \times \sum_{j > i} (n - j + 1)
$$

直接用树状数组维护即可。

[过题链接](https://codeforces.com/contest/1167/submission/319710379)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FL(a,b,c) for(int a=(b),a##end=(c);a<=a##end;++a)
#define FR(a,b,c) for(int a=(b),a##end=(c);a>=a##end;--a)
#define lowbit(x) ((x)&-(x))
#define eb emplace_back
#define SZ(x) (int)((x).size())
#define int long long
#define vt vector
#define fr first
#define se second
#define ar(x) array<int,x>
#define PII pair<int, int>
#define max(a, b)({auto f7r=(a);auto j3h=(b);f7r<j3h?j3h:f7r;})
#define cmax(a, b)({auto j3h=(b);(j3h>a)&&(a=j3h);})
#define min(a, b)({auto f7r=(a);auto j3h=(b);f7r>j3h?j3h:f7r;})
#define cmin(a, b)({auto j3h=(b);(j3h<a)&&(a=j3h);})
constexpr int N = 1e6 + 10, mod = 1e9 + 7;
int w1[N], w2[N];
PII a[N];
void add(int x, int v, int*w){while(x < N)w[x] += v, x += lowbit(x);}
int query(int x, int*w){int s = 0;while(x)(s += w[x]) %= mod, x -= lowbit(x);return s % mod;}
int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, ans = 0;
    cin >> n;
    FL(i, 1, n)cin >> a[i].fr, a[i].se = i;
    sort(a + 1, a + 1 + n);
    FL(i, 1, n){
        add(a[i].se, a[i].se, w1);
        add(n - a[i].se + 1, n - a[i].se + 1, w2);
        int s = (query(a[i].se, w1) * (n - a[i].se + 1) % mod);
        (s += a[i].se * query(n - a[i].se, w2) % mod) %= mod;
        (ans += a[i].fr * s % mod) %= mod;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：MagicalGirl_0d00 (赞：1)

### 鲜花
给 @do_it_tomorrow 推了我做的数据结构单子，怎么他的效果明显比我好呢？ 

这么菜这么菜这么菜？
### sol
你会发现在一个区间内有 $a_i\leq a_j$ 就会对全局产生一次 $a_j$ 的贡献。

所以实际上让我们求的是以下这个东西：

$$
\sum_{i=1}^n\sum_{j=1}^n [a_i\leq a_j]a_j \times \min(i,j) \times (n-\max(i,j)+1)
$$
后面那两个是包含 $a_i,a_j$ 的区间个数。

这个就可以 $n^2$ 去做了，但不够快。

我们先把这个式子变成：
$$
\sum_{i=1}^n\sum_{j=i}^n [a_i\leq a_j]a_j \times \min(i,j) \times (n-\max(i,j)+1)
$$
这个形式显然可以拿个树状数组离散化后用类似二维偏序的方式去做（确实比较版）。

具体操作就是对于一个 $a_i$，算区间 $[i,j]$ 中大于等于 $a_i$ 的所有答案就行。

把 $a_i$ 推进树状数组里推的是 $i\times a_i$。

然后你扫两遍，注意下第二遍不能算等于的答案不然就算重复了。
### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,k,x,y,z,ans,a[500001],b[500001],c[500001],tot;
int lowbit(int x){return x&(-x);}
void update(int x,int val){while(x){c[x]=(c[x]+val)%mod;x-=lowbit(x);}}
int get(int x){int val=0;while(x<=n){val=(val+c[x])%mod,x+=lowbit(x);}return val;}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
//		ans=(ans+a[i]*i%mod*(n-i+1)%mod)%mod;
		b[i]=a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) b[i]=lower_bound(a+1,a+n+1,b[i])-a;
	for(int i=1;i<=n;i++){
		update(b[i],a[b[i]]*i%mod);
		ans=(ans+(n-i+1)*get(b[i])%mod)%mod;
//		cout<<(n-i+1)*get(b[i])<<" ";
	}
//	cout<<"\n";
	memset(c,0,sizeof c);
	for(int i=n;i>=1;i--){
		ans=(ans+i*get(b[i])%mod)%mod;
		update(b[i],a[b[i]]*(n-i+1)%mod);
//		cout<<i*get(b[i])<<' ';
	}
//	cout<<"\n";
	cout<<ans;
}
/*
膜拜传奇宗师 @do_it_tomorrow 5min 秒掉紫题。
我太弱了，第一步就想错了。 
会发现对于一组 (i,j) a_i<a_j 的贡献是 a_i*同时包含 i,j 的区间数。
扫两遍，然后用一个类似二位偏序问题的东西去做就行了，离散化搞棵树状数组就好了。 
*/
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1167F)

## 思路

题解里大多都写的复杂了，这题其实是傻逼题。

考虑拆贡献，假设我们枚举到了位置 $i$，我们只需要求出 $i$ 在所有包含 $i$ 的区间里的排名总和就好了，所以我们就有了一个 $\mathcal O(n^3)$ 做法（似乎比直接暴力还要烂）。

令 $<a_i$ 的数为 $1$，别的数为 $0$。

从点 $i$ 开始往点 $1$ 做一遍后缀和，记为 $sum1$，从点 $i$ 开始往点 $n$ 做一遍前缀和，记为 $sum2$，容易发现 $i$ 在区间 $l,r$ 中的排名就是 $sum1_l+sum2_r+1$。

于是我们的问题就转化成了求 $\sum_{l=1}^i \sum_{r=i}^n sum1_l+sum2_r+1$，暴力求它是 $\mathcal O(n^3)$ 的。

把 $1$ 提出，容易发现 $1$ 的贡献是 $i \times (n-i+1)$，然后考虑分别计算 $sum1$ 和 $sum2$ 的贡献，我们发现每个 $sum1$ 都会与 $n-i+1$ 个 $sum2$ 产生贡献，至于 $sum2$ 具体是啥我们并不关系，因为我们求的只是 $sum1$ 的贡献。

对于 $sum2$ 的贡献同理。

于是，现在我们就把上面的柿子转化成了 $\sum_{l=1}^i sum1_l \times (n-i+1)+\sum_{r=i+1}^n sum2_r \times i+i \times (n-i+1)$，做到了 $\mathcal O(n^2)$ 的复杂度。

我们发现这依然是可以优化的，复杂度瓶颈只在于 $\sum_{l=1}^i sum1_l$ 和 $\sum_{r=i+1}^n sum2_r$，我们只需要快速求出这两个的值即可。

考虑每个 $a_j<a_i$ 的 $j$ 的贡献，我们钦定 $j$ 在 $i$ 的左边，则 $j$ 会对 $1$ 到 $j$ 的 $sum1$ 产生 $1$ 的贡献，它的贡献就是 $j$。

$j$ 在 $i$ 的右边同理，直接树状数组维护即可。

时间复杂度 $\mathcal O(n \log n)$。

## 码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
int const N=5e5+10;
int const mod=1e9+7;
int a[N],n,b[N],pre[N],suf[N];
struct Tree_Array{
	int c[N];
	inline void update(int x,int v){while (x<=n) c[x]+=v,x+=lowbit(x);}
	inline int query(int x){int res=0;while (x) res+=c[x],x-=lowbit(x);return res;}
}T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;int ans=0;
	for (int i=1;i<=n;++i) cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);int l=unique(b+1,b+n+1)-b-1;
	for (int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+l+1,a[i])-b;
    //离散化
	for (int i=1;i<=n;++i)
		pre[i]=T.query(a[i]-1),T.update(a[i],i);
	memset(T.c,0,sizeof(T.c));
	for (int i=n;i>=1;--i)
		suf[i]=T.query(a[i]-1),T.update(a[i],n-i+1);
	for (int i=1;i<=n;++i){
		int res=0;
		res=pre[i];res*=(n-i+1);res%=mod;
		int now=suf[i];now*=i;now%=mod;
		now+=(n-i+1)*i%mod;now%=mod;
		res+=now;res%=mod;res*=b[a[i]];res%=mod;
		ans+=res;ans%=mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

























---

## 作者：TheShadow (赞：1)

# 闲扯

这道题挺妙的。

# 题面

[CF1167F Scalar Queries](https://www.luogu.org/problem/CF1167F)

# Solution

这道题直接模拟肯定是不行的，我们考虑换个思路。

我们统计对于每一个 $a_i$ ，它被计算了几次。

排序后，假如 $a_i$ 处于第 $k$ 个，那么它就会被多算 $k-1$ 次。那么相当于在这个区间中每一个比 $a_i$ 小的数都会使 $a_i$ 多算一次。

那么我们只需要统计每一个比 $a_i$ 小的数能在多少个区间里面被包含即可。

1. 若 $a_j<a_i,j<i$ ，则同时包含 $a_i,a_j$ 的区间有 $j\cdot (n-i+1)$ 个，那么 $a_i$ 就会被多算 $j\cdot (n-i+1)$ 次。
2. 若 $a_j<a_i,j>i$ ，则同时包含 $a_i,a_j$ 的区间有 $i\cdot(n-j+1)$ 个，那么 $a_i$ 就会被多算 $i\cdot(n-j+1)$ 次。

我们按照权值大小对 $a$ 数组排序，然后依次插入，统计两种情况的答案即可。

对于权值相等的，插入顺序是不会影响答案的，简单推一下即可。

# Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 5e5+5,mod = 1e9+7;
int n,ans;
it add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
it mul(int x,int y){return 1ll*x*y%mod;}
struct Node{
	int val,pos;
	bool operator <(const Node &t) const{
		return val<t.val;
	}
}node[MAXN];
#define lc (cur<<1)
#define rc (cur<<1|1)
struct Seg_Tree{
	int sum1,sum2;
}T[MAXN<<2];
il pushup(int cur){T[cur].sum1=add(T[lc].sum1,T[rc].sum1),T[cur].sum2=add(T[lc].sum2,T[rc].sum2);}
il updata(int cur,int l,int r,int pos){
	if(l==r) return T[cur].sum1=pos,T[cur].sum2=n-pos+1,void();
	if(mid>=pos) updata(lc,l,mid,pos);
	else updata(rc,mid+1,r,pos);
	pushup(cur);
}
it query1(int cur,int l,int r,int L,int R){
	if(l>=L&&r<=R) return T[cur].sum1;
	ri res=0;
	if(mid>=L) res=add(res,query1(lc,l,mid,L,R));
	if(R>mid) res=add(res,query1(rc,mid+1,r,L,R));
	return res;
}
it query2(int cur,int l,int r,int L,int R){
	if(l>=L&&r<=R) return T[cur].sum2;
	ri res=0;
	if(mid>=L) res=add(res,query2(lc,l,mid,L,R));
	if(R>mid) res=add(res,query2(rc,mid+1,r,L,R));
	return res;
}

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	for(ri i=1;i<=n;++i) read(node[i].val),node[i].pos=i;
	sort(node+1,node+1+n);
	for(ri i=1;i<=n;++i){
		if(node[i].pos!=1) ans=add(ans,mul(mul(query1(1,1,n,1,node[i].pos-1),n-node[i].pos+1),node[i].val));
		if(node[i].pos!=n) ans=add(ans,mul(mul(query2(1,1,n,node[i].pos+1,n),node[i].pos),node[i].val));
		updata(1,1,n,node[i].pos);
		ans=add(ans,mul(node[i].val,mul(node[i].pos,n-node[i].pos+1)));
	}
	print(ans);
	return 0;
}
```

# 总结

要抓住问题的本质，善于将问题转换成容易求解的形式。

---

## 作者：Composite_Function (赞：0)

小清新计算贡献题。

首先不难看出，$f(l, r) = \sum_{i = l} ^ r a_i \times  rk_{i, l, r}$，其中 $rk_{i, l, r}$ 表示 $a_i$ 是在 $a_l,a_{l+1}, \dots, a_r$ 中的第 $rk_{i, l, r}$ 大的数。那么进一步得到：$f(l, r) = \sum_{i = 1} ^ n sum_i$，$sum_i$ 表示所有包含 $i$ 的区间中 $a_i$ 的排名和。

考虑计算 $sum_i$。注意到，一个区间中一个数的排名，其实是比这个数小的数的数量加一。包含一个数的区间数很好计算，于是转而考虑所有包含 $i$ 的区间中比 $a_i$ 小的数。

对于 $a_j < a_i$，$a_j$ 对 $sum_i$ 的贡献是所有同时包含 $a_j$ 和 $a_i$ 的区间数，即 $\min(i, j) \times (n - \max(i, j) + 1)$。

那么就可以分成 $j < i$ 与 $j > i$ 的数分开计算。不妨 $j < i$ 那么 $a_j$ 对 $sum_i$ 的贡献是 $j \times (n - i + 1)$，只用考虑 $j$，用数据结构维护一下即可。另一侧同理。

跑的理论上讲应该比其他做法快，但是常数巨大。。。

还有记得取模！

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define uint unsigned int
#define reg register
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define qint const int&
#define qll const ll&
#define quint cosnt uint&
#define qull const ull&

const int N = 5e5 + 10, mod = 1e9 + 7;
int n, a[N], id[N], pre[N], suf[N], ans;

int bitp[N], bits[N];
inline int LSB(int x) {
	return x & (-x);
}
inline int qp(int x) {
	int ret = 0;
	while (x) {
		ret += bitp[x];
		x -= LSB(x);
		if (ret >= mod) ret -= mod;
	}
	return ret;
}
inline int qs(int x) {
	int ret = 0;
	while (x <= n) {
		ret += bits[x];
		x += LSB(x);
		if (ret >= mod) ret -= mod;
	}
	return ret;
}
inline void cp(int x, int y) {
	while (x <= n) {
		bitp[x] += y;
		if (bitp[x] >= mod) bitp[x] -= mod;
		x += LSB(x);
	}
}
inline void cs(int x, int y) {
	while (x) {
		bits[x] += y;
		if (bits[x] >= mod) bits[x] -= mod;
		x -= LSB(x);
	}
}

bool cmp(int x, int y) {
	return a[x] < a[y];
}

signed main() {
	cin >> n;
	for (reg int i = 1; i <= n; ++i) {
		cin >> a[i];
		id[i] = i;
	}
	sort(id + 1, id + n + 1, cmp);
	for (reg int j = 1; j <= n; ++j) {
		int i = id[j];
		pre[i] = qp(i), suf[i] = qs(i);
		cp(i, i), cs(i, n - i + 1);
	}
	for (reg int i = 1; i <= n; ++i) {
		ans = (ans + 1ll * a[i] * (((ll)pre[i] * (n - i + 1) % mod + (ll)suf[i] * i % mod + (ll)i * (n - i + 1) % mod) % mod)) % mod;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：forest114514 (赞：0)

### CF1167F Scalar Queries
首先推式子：
$$
f(l,r)=\sum\limits_{i=1}^{r-l+1}b_i\times i=\sum \limits_{i=l}^{r}\sum\limits_{j=l}^{r}([a_i>a_j]+1)\times a_i
$$

所以：

$$
\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}f(l,r)=\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}(\sum \limits_{i=l}^{r}\sum\limits_{j=l}^{r}([a_i>a_j]+1)\times a_i)=\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}\sum \limits_{i=l}^{r}\sum\limits_{j=l}^{r}[a_i>a_j]\times a_i+\sum\limits_{i=1}^n i\times(n-i+1)\times a_i
$$

考虑每一个数对的贡献，一个 $a_i>a_j,i>j$ 会贡献 $i\times(n-j+1)$，一个 $a_i>a_j,j>i$ 会产生贡献 $(n-i+1)\times j$，就是两个二维数点，正着倒着树状数组扫两遍即可，数组离散化一下即可。

CODE：
```cpp
const int N=5e5+100;
const LL mod=1e9+7;
int n;
LL a[N],b[N],cpy[N];
struct BIT{
	LL c[N];
	void clear(){memset(c,0,sizeof c);}
	#define lowbit(x) (x&(-x))
	void update(int u,LL x){for(;u<=N;u+=lowbit(u))(c[u]+=x)%=mod;}
	LL query(int u){LL res=0;for(;u;u-=lowbit(u))res+=c[u];return res%mod;}
}tr;
LL ans; 
signed main(){
	read(n);
	rep(i,1,n) read(b[i]),cpy[i]=b[i];
	sort(cpy+1,cpy+1+n);
	rep(i,1,n) a[i]=lower_bound(cpy+1,cpy+1+n,b[i])-cpy,ans=(ans+1ll*i*(n-i+1)%mod*b[i]%mod)%mod;
	rep(i,1,n){
		ans=(ans+1ll*tr.query(a[i])*(n-i+1)%mod*b[i]%mod)%mod;
		tr.update(a[i],i);
	}
	tr.clear();
	per(i,n,1){
		ans=(ans+1ll*tr.query(a[i])*i%mod*b[i]%mod)%mod;
		tr.update(a[i],n-i+1);
	}
	write(ans,'\n');
	return 0;
}
```



---

## 作者：daniEl_lElE (赞：0)

一道简单线段树题目。

## 思路

考虑计算贡献，现将所有的数从小到大排序，考虑 $i$ 在所有段中的排名贡献。

从小到大排序之后，每次新加入一个，并将左边和右边维护两个线段树分别加一，这样后面在查询的时候就可以直接计算总和。

但是当你这么做完，你会发现样例都过不了。

为什么呢？因为当 $i$ 在向右加一的时候，后面的一个 $j>i$ 在向右统计的时候会误把 $i$ 加入，所以我们还需要维护一个目前被激活的数的总和即可。复杂度 $O(n\log n)$，本题常数可能需要一定优化，不然会 $\texttt{TLE}$。

## 代码

线段树部分：

$\texttt{f}$ 数组表示计算所有位置的和，$\texttt{num}$ 表示统计目前已经遍历到的位置数量。两个 $\texttt{change}$ 分别表示区间位置和的增加和单点遍历位置数量增加。

```cpp
struct sgt{
	int f[2000005],siz[2000005],lzt[2000005],num[2000005];
	void pushdown(int i){
		f[ls]=(f[ls]+siz[ls]*lzt[i])%mod;
		lzt[ls]=(lzt[ls]+lzt[i]);
		f[rs]=(f[rs]+siz[rs]*lzt[i])%mod;
		lzt[rs]=(lzt[rs]+lzt[i]);
		lzt[i]=0;
	}
	void pushup(int i){
		f[i]=(f[ls]+f[rs])%mod;
		siz[i]=siz[ls]+siz[rs];
		num[i]=num[ls]+num[rs];
	}
	void build(int i,int l,int r){
		if(l==r){
			siz[i]=1;
			return ;
		}
		build(Ls),build(Rs);
		pushup(i);
	}
	void change(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr){
			f[i]=(f[i]+siz[i])%mod;
			lzt[i]=(lzt[i]+1);
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(Ls,ql,qr);
		if(qr>mid) change(Rs,ql,qr);
		pushup(i);
	}
	void change2(int i,int l,int r,int pos){
		if(l==r){
			num[i]=1;
			return ;
		}
		pushdown(i);
		if(pos<=mid) change2(Ls,pos);
		else change2(Rs,pos);
		pushup(i);
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		pushdown(i);
		return (qry(Ls,ql,qr)+qry(Rs,ql,qr))%mod;
	}
	int qrynum(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return num[i];
		if(ql>r||qr<l) return 0;
		pushdown(i);
		return (qrynum(Ls,ql,qr)+qrynum(Rs,ql,qr));
	}
}tl,tr;
```

操作部分：

前面已经排序过了。$\texttt{ans}$ 每次统计的时候一定要再增加一次。具体操作见代码。

```cpp
for(int i=1;i<=n;i++){
	ans=(ans+(tl.qry(1,1,n,1,a[i].pos)+mod-tl.qrynum(1,1,n,a[i].pos,n)*a[i].pos%mod)*(n-a[i].pos+1)%mod*a[i].num%mod)%mod;
	ans=(ans+(tr.qry(1,1,n,a[i].pos,n)+mod-tl.qrynum(1,1,n,1,a[i].pos)*(n-a[i].pos+1)%mod)*a[i].pos%mod*a[i].num%mod)%mod;
	ans=(ans+(n-a[i].pos+1)*a[i].pos%mod*a[i].num%mod)%mod;
	tl.change(1,1,n,1,a[i].pos);
	tr.change(1,1,n,a[i].pos,n);
	tl.change2(1,1,n,a[i].pos);
}
```

---

## 作者：_gjm2005_ (赞：0)

首先我们假设每个$a_i$都是对应子串中最小的，则此时每个$a_i$对答案的贡献为$\sum_{i=1}^n (n-i+1)*a_i*i$

但是显然每个$a_i$不一定是最小的，这时我们可以枚举$j$，当$a_j < a_i$时，这两个数就会对答案有贡献，因为$a_i$的排名被提高了

当$j < i$时， $i,j$对答案的贡献为$j*(n - i + 1)*a_i$

当$i < j$时， $i,j$对答案的贡献为$i*(n - j + 1)*a_i$

我们先考虑$j < i$的情况，另一种情况也同理。我们可以枚举$j$，考虑所有在$j$后面的$i$。我们发现对于每个$i，a_i*(n - i + 1)$一定,于是我们存下每个点的$a_i*(n - i + 1)$。然后从后往前枚举$j$，查询比它大的贡献之和

树状数组维护即可 记得离散化
```cpp
#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;
const int N = 1e6 + 10;
const int inf = INT_MAX;

#define int long long
#define FOR(i,a,b) for(int i = a;i <= b;i++)
#define _FOR(i,a,b) for(int i = a;i >= b;i--)

template<typename T> void read(T &x)
{
    x = 0;int f = 1;
    char c = getchar();
    for(;!isdigit(c);c = getchar()) if(c == '-') f = -1;
    for(;isdigit(c);c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int ans,T,n,c[N],a[N],A[N];

int query(int x)
{
	int ans = 0;
	for(; x; x -= x & -x)
		ans += c[x],ans %= mod;
	return ans;
}

void change(int x,int y)
{
	for(; x <= n; x += x & -x)
		c[x] = (c[x] + y) % mod;
}

signed main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	read(n);
	FOR(i,1,n)
		read(a[i]),A[i] = a[i];
	FOR(i,1,n)
		ans = (ans + a[i] * i % mod * (n - i + 1) % mod) % mod;
	sort(A + 1,A + 1 + n); 
	FOR(i,1,n)
		a[i] = lower_bound(A + 1,A + 1 + n,a[i]) - A;
	_FOR(i,n,1)
	{
		int sum = (query(n) - query(a[i]) + mod) % mod;
		change(a[i],A[a[i]] * (n - i + 1) % mod);
		ans = (ans + sum * i % mod) % mod;
	}
	memset(c,0,sizeof(c));
	FOR(i,1,n)
	{
		int sum = (query(n) - query(a[i]) + mod) % mod;
		change(a[i],A[a[i]] * i % mod);
		ans = (ans + sum * (n - i + 1) % mod) % mod;
	}
	printf("%lld\n",ans);
    return 0;
}



```


---

