# [ABC250E] Prefix Equality

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc250/tasks/abc250_e

長さ $ N $ の整数列 $ A\ =\ (a_1,\ldots,a_N) $ と $ B\ =\ (b_1,\ldots,b_N) $ が与えられます。

$ i=1,...,Q $ に対し、次の形式のクエリに答えてください。

- $ A $ の先頭 $ x_i $ 項 $ (a_1,\ldots,a_{x_i}) $ に含まれる値の集合と $ B $ の先頭 $ y_i $ 項 $ (b_1,\ldots,b_{y_i}) $ に含まれる値の集合が等しいならば `Yes` と、そうでなければ `No` と出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N,Q\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ a_i,b_i\ \leq\ 10^9 $
- $ 1\ \leq\ x_i,y_i\ \leq\ N $
- 入力は全て整数

### Sample Explanation 1

集合は各値が含まれるかどうかのみに注目した概念であることに気を付けてください。 $ 3 $ 番目のクエリにおいて、$ A $ の先頭 $ 2 $ 項には $ 1 $ と $ 2 $ が $ 1 $ 個ずつ、$ B $ の先頭 $ 3 $ 項には $ 1 $ が $ 1 $ 個と $ 2 $ が $ 2 $ 個含まれます。しかし、それぞれに含まれる値の集合はどちらも $ \{\ 1,2\ \} $ となり、一致します。 また、$ 6 $ 番目のクエリにおいては各値が現れる順番が異なりますが、やはり集合としては一致します。

## 样例 #1

### 输入

```
5
1 2 3 4 5
1 2 2 4 3
7
1 1
2 2
2 3
3 3
4 4
4 5
5 5```

### 输出

```
Yes
Yes
Yes
No
No
Yes
No```

# 题解

## 作者：Hanx16Kira (赞：6)

# [ABC250E] Prefix Equality

[Luogu ABC250E](https://www.luogu.com.cn/problem/AT_abc250_e)

## Solution

看到要判断两个数列的前缀组成的集合是否相等，一个很基础的想法就是将两个数列的前缀集合预处理出来。但是如果要存储下集合，并且还要判断集合是否相等显然时间和空间双重爆炸，因此考虑用 Hash 来唯一表示一个集合。询问就可以 $\mathcal O(1)$ 查询了。

然后思路上就没东西了。

考虑代码怎么实现。可以开一个桶存储当前有哪些数字，如果之前没出现过这个数字，就把这个数字贡献进 Hash 值内，否则不需要进行操作。由于数据的值域是 $10^9$ 这一级别，因此要么进行离散化，要么用 `map` 代替桶，用快速幂计算当前的 Hash 值。

总时间复杂度 $\mathcal O(n\log n + q)$

### Code

使用 `map` 代替了桶，没有进行离散化操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int _SIZE = 2e5 + 5;
int n, q, a[_SIZE], b[_SIZE];
using ui64 = unsigned long long;
const int P = 13331;
ui64 h1[_SIZE], h2[_SIZE];
ui64 Qpow(int x, int y) {
	ui64 res = 1, base = x;
	for (; y; y >>= 1, base *= base) if (y & 1) res *= base;
	return res;
}
map<int, bool> cnt;
void Calc(int *a, ui64 *h) {
	cnt.clear();
	for (int i = 1; i <= n; ++i) {
		h[i] = h[i - 1];
		if (!cnt.count(a[i]))
			cnt[a[i]] = 1, h[i] += Qpow(P, a[i]);
	}
}
void Solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) cin >> b[i];
	Calc(a, h1), Calc(b, h2); cin >> q;
	while (q--) {
		static int x, y; cin >> x >> y;
		cout << (h1[x] == h2[y] ? "Yes" : "No") << '\n';
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Solve();
}
```

---

## 作者：yangshengyu0719 (赞：5)

## 思路
一眼 [异或哈希](https://blog.csdn.net/notonlysuccess/article/details/130959107) 版题。

我们可以先给每一个值赋一个随机数（千万记得要用 **mt19937**，不然哈希冲突概率会较大）。

再维护两个随机数的前缀和 $asum_{i}$ 和 $bsum_{i}$ 表示在 $a$ 或 $b$ 数组前 $i$ 个数，原数去重后对应随机值的异或和。

然后每次询问比对一下即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
mt19937 rd(time(0));
const int N=2e5+5;
int n,m,a[N],b[N],asum[N],bsum[N];
map<int,int> h,mpa,mpb;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],h[a[i]]=rd();
	for(int i=1;i<=n;i++) cin>>b[i],h[b[i]]=rd();
	for(int i=1;i<=n;i++) a[i]=h[a[i]],b[i]=h[b[i]];
	for(int i=1;i<=n;i++){
		if(!mpa[a[i]]) asum[i]=asum[i-1]^a[i];
		else asum[i]=asum[i-1];
		if(!mpb[b[i]]) bsum[i]=bsum[i-1]^b[i];
		else bsum[i]=bsum[i-1];
		mpa[a[i]]=1,mpb[b[i]]=1;
	}
	cin>>m;
	int x,y;
	while(m--){
		cin>>x>>y;
		if(asum[x]==bsum[y]) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：lnwhl (赞：4)

## Solution
考虑如何判断 $a[1]\sim a[x]$ 去重后 与 $b[1]\sim b[y]$ 去重后相同。

1. 我们需要保证 $a[1]\sim a[x]$ 与 $b[1]\sim b[y]$ 中去重后元数的个数相等。
2. 但这是不够的，我们还需要保证 $a[1]\sim a[x]$ 中的每一个数都在 $b[1]\sim b[y]$ 中出现。
 
考虑如何实现。

1. 第一个要求比较好满足，只需要用一个桶和一个前缀和数组记录一下即可。(前缀和数组记为 $numa$ 和 $numb$)
2. 考虑第二个要求，我们先将两个数组离散化一下，用一个 $pos$ 数组记录一下每个数在 $b$ 数组中出现的最早位置。

**定义 $f[i]$ 表示 $a[1]\sim a[i]$ 中的每一个数在 $b$ 数组中第一次出现的最晚位置。** 
$$f[i]=\max\{f[i-1],pos[a[i]]\}$$
 
输出的时候只需要判断 $f[x]\le y$ 即可。 

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4e5+5;
int n,q,a[N],b[N],c[N],pos[N],f[N];
int numa[N],numb[N],ta[N],tb[N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i],c[i]=a[i];
	for(int i=1;i<=n;++i)
		cin>>b[i],c[n+i]=b[i];
	sort(c+1,c+n+n+1);
	int cntl=unique(c+1,c+n+n+1)-c-1;
	for(int i=1;i<=n;++i)
	{
		a[i]=lower_bound(c+1,c+cntl+1,a[i])-c;
		ta[a[i]]++;numa[i]=numa[i-1]+(ta[a[i]]==1);
	}
	for(int i=1;i<=n;++i)
	{
		b[i]=lower_bound(c+1,c+cntl+1,b[i])-c;
		tb[b[i]]++;numb[i]=numb[i-1]+(tb[b[i]]==1);
		if(!pos[b[i]])pos[b[i]]=i;
	}
	for(int i=1;i<=n;++i)
		if(!pos[a[i]])f[i]=5e5;
		else f[i]=max(f[i-1],pos[a[i]]);	
	cin>>q;	
	while(q--)
	{
		int x,y;cin>>x>>y;
		if(numa[x]==numb[y]&&f[x]<=y)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：苏联小渣 (赞：4)

多年前比赛时一脸懵逼的题目今天切出来了，写个题解纪念一下往事吧（）

题目问 $a[1,x_i]$ 去重后和 $b[1,y_i]$ 去重后是否相等。

这种看起来很难维护的东西很容易想到莫队，但这是 E 题，而且询问的左端点都是 $1$，这样莫队就退化成单指针了。因此不难想到用一个指针去维护这个东西。

不难发现对于每一个 $x_i$，合法的 $y_i$ 要么不存在，要么是一个连续段。同时这个东西具有单调性，也就是新加入一个数一定不会使得集合的大小变小。

所以说可以枚举 $i \in [1,n]$，算一下 $a[1,i]$ 有多少个不同的数并且放到桶里。一个指针 $j$ 记录当前枚举到 $b$ 的哪里。每次 $a$ 新增了一个没出现过的数的时候，让 $j$ 不断增加直到 $a[1,i]$ 去重后和 $b[1,j]$ 去重后相等为止。这是这个 $i$ 对应的最小的 $j$。如果是最大的 $j$ 的话就在不影响答案的情况下让 $j$ 继续增加就好了。

注意要先离散化。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, q, x, y, cnt, tot, totb, r, a[200010], b[200010], p[400010], pb[400010], ansl[200010], ansr[200010];
map <int, int> mp;
map <int, int> :: iterator it;
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
		mp[a[i]] = 1;
	}
	for (int i=1; i<=n; i++){
		scanf ("%d", &b[i]);
		mp[b[i]] = 1;
	}
	for (it=mp.begin(); it!=mp.end(); it++){
		mp[it->first] = ++cnt;
	}
	for (int i=1; i<=n; i++){
		a[i] = mp[a[i]], b[i] = mp[b[i]];
	}
	r = 0;
	for (int i=1; i<=n; i++){
		if (!p[a[i]]) p[a[i]] = 1, tot ++;
		else{
			ansl[i] = ansl[i-1], ansr[i] = ansr[i-1];
			continue;
		}
		while (r < n && totb < tot && p[b[r+1]]){
			if (!pb[b[r+1]]) pb[b[r+1]] = 1, totb ++;
			r ++;
		}
		if (totb == tot){
			ansl[i] = r;
			while (r < n && pb[b[r+1]]) r ++;
			ansr[i] = r;
		}
	}
	scanf ("%d", &q);
	for (int i=1; i<=q; i++){
		scanf ("%d%d", &x, &y);
		if (y >= ansl[x] && y <= ansr[x]) puts ("Yes");
		else puts ("No");
	}
	return 0;
}

```

---

## 作者：aimcf (赞：3)

尺取法。

假设目前选择了 $a$ 数组中前 $i$ 个数，那么可以通过尺取得到满足条件的区间 $[L_i,R_i]$，满足在 $1$ 到这个这个区间的任意一个位置中 $a_1\sim a_i$ 和 $b_1\sim b_j$，$j\in [L_i,R_i]$ 里面的数相等。

然后对于每一个 $a_i$ 直接进行判断即可。

时间复杂度 $O(n)$。

---

## 作者：Galois_Field_1048576 (赞：2)

考虑将 $A_{1..i}$ 和 $B_{1..i}$ 进行哈希。  
由于集合的相等与数的顺序无关，所以需要一个交换律运算，考虑使用异或运算。  
构造出的哈希函数为：
$$H(S) = \bigoplus_{s \in S} f(x)$$
，其中 $f(x)$ 是一个数字产生数字的哈希函数，于是有
$$H(S \cup \{x\}) = \left\{\begin{matrix}H(S) & x \in S \\ H(S) \oplus f(x) & x \notin S\end{matrix}\right.$$
，考虑用 `set` 维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i, j, k) for (int i = j; i <= k; ++i)
#define Fi F(i, 1, n)
#define Fj F(j, 1, n)
#define int long long
const int N = 2e5 + 5;
const int M = 1e18 + 3;
set<int> s, t;
int a[N], b[N], as[N], bs[N], n, q, x, y;
int seed = 114514;
int rand(int MGC)
{
    return ((seed << 15) * MGC % M + M) % M;
}
signed main()
{
    cin >> n;
    Fi cin >> a[i];
    Fi cin >> b[i];
    Fi if (s.find(a[i]) == s.end())
    {
        s.insert(a[i]);
        as[i] = as[i - 1] ^ rand(a[i]);
    }
    else as[i] = as[i - 1];
    seed = 114514;

    Fi if (t.find(b[i]) == t.end())
    {
        t.insert(b[i]);
        bs[i] = bs[i - 1] ^ rand(b[i]);
    }
    else bs[i] = bs[i - 1];
    cin >> q;
    F(i, 1, q)
    {
        cin >> x >> y;
        if (as[x] == bs[y])
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    getchar();
    getchar();
}
```


---

## 作者：Symbolize (赞：1)

# $\tt{solution}$
这题说一说哈希的方法，对于每个数你都给它一个哈希值，又因为所有的左边界都为 $1$，所以可以用一个前缀和，如果你发现这个值出现过就不管它，如果每出现过，给它一个哈希值并记录前缀和，判断是否正确时只需要判断两个前缀和对应的值是否相等就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
#define debug() puts("----------")
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const double pi=acos(-1);
using namespace std;
typedef complex<int> ci;
typedef complex<double> cd;
int n,q,a[N],b[N];
map<int,int> mp;
set<int> s;
mt19937_64 g(N);
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
//	#ifndef ONLINE_JUDGE
//		freopen(".in","r",stdin);
//		freopen(".out","w",stdout);
//	#endif
	n=read();
	rep1(i,1,n)
	{
		int x=read();
		if(!mp.count(x)) mp[x]=g();
		if(!s.count(x))
		{
			a[i]=a[i-1]+mp[x];
			s.insert(x);
		}
		else a[i]=a[i-1];
	}
	s.clear();
	rep1(i,1,n)
	{
		int x=read();
		if(!mp.count(x)) mp[x]=g();
		if(!s.count(x))
		{
			b[i]=b[i-1]+mp[x];
			s.insert(x);
		}
		else b[i]=b[i-1];
	}
	q=read();
	while(q--)
	{
		if(a[read()]==b[read()]) puts("Yes");
		else puts("No");
	}
	return 0;
}

```

---

## 作者：chengning0909 (赞：1)

# abc 250 e

[AT 链接](https://atcoder.jp/contests/abc250/tasks/abc250_e)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc250_e)

## 题意

给定两个长度为 $n$ 的序列 $a, b$，有 $q$ 次询问，每次询问给出 $x_i, y_i$，请你回答 $a$ 的前 $x_i$ 项所构成的集合与 $b$ 的前 $y_i$ 项所构成的集合是否相同。

## 思路

### 暴力

每次枚举 $a$ 的前 $x_i$ 个元素和 $b$ 的前 $y_i$ 个元素，用两个 `set` 维护集合，最后比较即可。

时间复杂度为 $O(n ^ 2 \times \log n)$。

### 正解

我们可以将先预处理出 $n$ 个区间：对于 $a$ 的前 $i$ 项构成的集合，在第 $i$ 个区间内的所有 $j$，$b$ 的前 $j$ 项所构成的集合都和 $a$ 的前 $i$ 项构成的集合相同。

那么，每次询问只需要判断 $y_i$ 是否在第 $x_i$ 个区间内就可以了。

但是，我们应该如何处理出这些区间呢？

可以直接双指针。

令 $a$ 序列中的某个前缀所构成的集合为 $S1$，$b$ 序列中的某个前缀所构成的集合为 $S2$。

很明显，每次遍历到一个 $i$，都需要将 $a_i$ 加入 $S1$，而这个操作，可能会改变 $S1$，就将 $b$ 的指针往后挪，并且将 $b_j$ 放进 $S2$，前提是，$b_j$ 在 $S1$ 中。当 $S1$ 的大小与 $S2$ 的大小相等时，便可以更新区间了。

但是，如果没有改变 $S1$，便与第 $i - 1$ 个区间是一样的。

时间复杂度为 $O(n \times \log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, q, a[N], b[N], l[N], r[N];
set<int> s1, s2;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = 1, j = 1; i <= n; i++) {
    if (s1.find(a[i]) != s1.end() && s1.size() == s2.size()) {  // 没有改变 s1
      l[i] = l[i - 1], r[i] = r[i - 1];
    }
    s1.insert(a[i]);
    for (; j <= n && s1.find(b[j]) != s1.end(); j++) {
      s2.insert(b[j]);
      if (s1.size() == s2.size()) {  // 更新区间
        if (!l[i]) {
          l[i] = j;
        }
        r[i] = j;
      }
    }
  }
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << (l[x] <= y && y <= r[x] ? "Yes\n" : "No\n");
  }
  return 0;
}
```

---

## 作者：yzx3195 (赞：0)

# 题目大意

给定两个长为 $N$ 的数列 $A,B$ 与 $Q$ 次询问，每次询问给出 $x_i,y_i$，求出 $A$ 的前 $x_i$ 项去重后是否与 $B$ 的前 $y_i$ 项去重后相同。

# 思路
看到这道题，第一时间是暴力，看一眼数据范围：$1\leq N,Q\leq 2\times 10^5$。

肯定不是暴力，所以？

我们有[哈希](https://blog.csdn.net/Beyond_2016/article/details/8128660)！

我们可以对前 $i$ 个区间做一次哈希，这样查询就可以 $O(1)$ 了。具体怎么哈希呢？就是对每一个 $a_i$ 用一个桶来标记它有没有出现过，如果没有，就加一下前 $i$ 个的哈希值。

- 注意：因为数据到达了 $10^9$，所以正常的桶是存不下的，所以要么离散化，要么用 map。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int P = 123321;

const int MAXN = 1e05 * 2 + 7;

#define int long long

int n;

int q;

int a[MAXN];

int b[MAXN];

int h_a[MAXN];

int h_b[MAXN];yoummei

int bin_pow(int a, int b)
{
	int res = 1;
	while(b > 0)
	{
		if(b & 1)
			res = res * a;
		a *= a;
		b >>= 1; 
	}
	return res;
}

map<int, int> t;

void HUSH(int *A, int *H)
{
	for(int i = 1; i <= n; i++)
	{
		H[i] = H[i - 1];
		if(t[A[i]] == 0)
		{
			t[A[i]] = 1;
			H[i] = H[i] + bin_pow(P, A[i]);
		}
	}
	return ;
}

signed main()
{
	cin >> n;
	
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	
	for(int i = 1; i <= n; i++)
		cin >> b[i];
		
	HUSH(a, h_a);
	
	t.clear();
	
	HUSH(b, h_b);
		
	cin >> q;
	
	while(q--)
	{
		int x, y;
		cin >> x >> y;
		printf(h_a[x] == h_b[y] ? "Yes\n" : "No\n");
		}	
	
	return 0;
}
```

---

## 作者：tmpliyijiang (赞：0)

## 题意
给定 $2$ 个序列 $a$ 和 $b$，对于每个 $x_i$ 与 $y_i$，对 $a$ 的前 $x_i$ 个元素、$b$ 的前 $y_i$ 个元素进行排列和去重，得到序列 $c$ 和 $d$，若 $c=d$，输出 `Yes`，否则输出 `No`。

## 思路
注意到所有序列的左端点都是 $1$，容易想到 $O(n)$ 的哈希。而对于查重操作，有一个好用的容器 `unordered_map`，查找复杂度为 $O(1)$，可以当做桶。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=1e18+3;//一个质数
int a[200005],b[200005],n,q,k1[200005],k2[200005],x,y;//k1,k2存哈希值
unordered_map<int,int>m,m2;//表示有没有出现过
signed main(){
	scanf("%lld",&n);
	for(register int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(register int i=1;i<=n;i++)scanf("%lld",&b[i]);
	scanf("%lld",&q);
	for(register int i=1;i<=n;i++){//计算哈希
		if(m[a[i]])k1[i]=k1[i-1];
		else m[a[i]]++,k1[i]=(k1[i-1]+a[i]*a[i]%p*a[i]%p)%p;
     		if(m2[b[i]])k2[i]=k2[i-1];
		else m2[b[i]]++,k2[i]=(k2[i-1]+b[i]*b[i]%p*b[i]%p)%p;
	}
	for(register int i=0;i<q;i++){//输出
		scanf("%lld%lld",&x,&y);
		if(k1[x]==k2[y])printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

题目的大意是要我们求出 $a$ 的前 $i$ 项的 set 与 $b$ 的前 $j$ 项的 set 是否相同。

首先最暴力的做法当然是把他们俩的 set 求出来，然后一一比对，这样肯定是不行的，所以我们寻求哈希的算法。

我们注意到，在之前志不畅哈希中，我们把每个字符映射成一个整数，那这样每一个字符串就会映射成一个整数，但是这样的话每个字母出现的顺序对哈希是有影响的。

但是在本题中我们**只关心这个字符是否出现过，而不关心它出现的顺序**。所以我们就不能使用之前字符串哈希的方法。

我们举个例子，字符串 $12$ 和字符串 $21$ 是不同的字符串，但是在两个 set 中先加入 $1$ 再加入 $2$ 和先加入 $2$ 再加入 $1$，是一样的。

对于本题的哈希函数，我们很容易就可以想到加法，因为加法满足交换律，所以他对于顺序是没有要求的。

但是这样我们很轻松就可以举出反例，比如说 $1+2+6=2+3+4$。那么我们就需要把这个哈希哈希函数变得复杂一点，比如说：

- 比对它们的和，平方的和，立方和分别是否相等。

- 或者将每个数字左移若干位再右移若干位，再将它们相加比对它们是否相等。

- 我们也可以将每个数计算一个随机值出来：我们把每个数 $i $ 分配一个随机数 $h_i$，将它的哈希值设定为 $i\times h_i$。

这个问题与树的同构较为相似。

```C++
ull shift(ull x){//ull是unsigned long long
    x^=mask;//mask是随机质数
    x^=x<<13;
    x^=x>>7;
    x^=x<<17
    x^=mask;
    return x;
}
```


上面就是一种哈希的算法，我们只需要保证一个建立一个 $x$ 与其哈希值的单射即可。

总结一下对于这种顺序对结果没有影响的情况我们需要使用满足交换律的运算符来构建哈希函数，比如加法乘法或者异或。

我们维护一个前缀的哈希值。对于去重问题，我们在从前往后后加入数时，我们将它加入一个 set 中来判断是否之前已经存在过这个数，如果之前有过就不将它的哈希值算出进行累加。

**Code**

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;



const int N=2e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;
int suma[N],sumb[N],a[N],b[N],n,q,x,y,suma2[N],sumb2[N];
void solve(int x,int y){
	if(suma[x]==sumb[y]&&suma2[x]==sumb2[y])cout<<"Yes\n";
	else cout<<"No\n";
	return;
}

int hashh(int x){
	return x*x;
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)cin>>b[i];
	
	set<int> sa,sb;
	for(int i=1;i<=n;i++){
		suma[i]=suma[i-1];
		suma2[i]=suma2[i-1];
		sumb[i]=sumb[i-1];
		sumb2[i]=sumb2[i-1];
		if(sa.count(a[i])==0)
		{
//			cout<<"OK";
			suma[i]+=hashh(a[i]);
			suma2[i]+=a[i];
			sa.insert(a[i]);
		}
		if(sb.count(b[i])==0){
			sumb[i]+=hashh(b[i]);
			sumb2[i]+=b[i];
			sb.insert(b[i]);
		}
	}
	
	cin>>q;
	while(q--){
		cin>>x>>y;
		solve(x,y);
	}
	return 0;
}

```




---

## 作者：yinpeichu2021 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc250_e)

给出一个乱搞的方法。

判断两个数列去重后是否相同，可以将两个数列去重后的数字揉成一团，这可以用 hash 实现。

令 $f(i)$ 表示 $a$ 数组第 $i$ 个数的 hash 值，则有:

$$
f(i)=\begin{cases}
f(i-1)+a_i^3&v_i=1\\
f(i-1)&v_i=0
\end{cases}
$$

其中，$v_i$ 表示的是 $a_i$ 是否是第一次出现在 $a$ 数组当中，是则为 $1$，否则为 $0$。

同理，$b$ 数组的 hash 值也可以通过同样的方法计算出来。

然后，判断其 hash 值是否相等即可。

```cpp
#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
#define int long long
#define MAXN 200005
int n,Q,a[MAXN],b[MAXN],h1[MAXN],h2[MAXN];
map<int,bool>mp1,mp2;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!mp1[a[i]])
        	h1[i]=(h1[i-1]+a[i]*a[i]%MOD*a[i]%MOD)%MOD;
        else h1[i]=h1[i-1];//照着公式来
        mp1[a[i]]=1;//打上标记
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        if(!mp2[b[i]])
        	h2[i]=(h2[i-1]+b[i]*b[i]%MOD*b[i]%MOD)%MOD;
        else h2[i]=h2[i-1];
        mp2[b[i]]=1;
    }
    cin>>Q;
    while(Q--){
        int l,r;
        cin>>l>>r;
        puts(h1[l]==h2[r]?"Yes":"No");//判断hash值是否相等
    }
    return 0;
}
```

---

## 作者：Swirl (赞：0)

**涉及芝士点：异或哈希**。

感觉是一道模板的异或哈希。

### Solution

异或哈希的原理详见 notonlysuccess 大佬的一篇博客：[Link](https://blog.csdn.net/notonlysuccess/article/details/130959107)，这里只讲本题的思路。

给每个数 $t$ 都映射到一个随机数 $B_t$，我们希望数组 $A$ 的前 $x$ 个数的哈希值为：

$$
\bigoplus_{i=1}^{k} B_{C_i}
$$

其中 $C$ 数组表示 $A$ 数组的前 $x$ 个数去重后的数组，长度为 $k$。

那么用 set 维护一下去重后的数组即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

int n;
int a[200005], b[200005];
int q;
map<int, unsigned int> Map1;
set<int> hasA, hasB;
int ansA[200005], ansB[200005];

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	mt19937_64 f(time(NULL));
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (!Map1[a[i]])
			Map1[a[i]] = f();
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
		if (!Map1[b[i]])
			Map1[b[i]] = f();
	}
	cin >> q;
	for (int i = 1; i <= n; i++) {
		if (hasA.find(a[i]) == hasA.end()) {
			hasA.insert(a[i]);
			ansA[i] = ansA[i - 1] ^ Map1[a[i]];
		}
		else {
			ansA[i] = ansA[i - 1];
		}
	}
	for (int i = 1; i <= n; i++) {
		if (hasB.find(b[i]) == hasB.end()) {
			hasB.insert(b[i]);
			ansB[i] = ansB[i - 1] ^ Map1[b[i]];
		}
		else {
			ansB[i] = ansB[i - 1];
		}
	}
	while (q--) {
		int x, y;
		cin >> x >> y;
		if (ansA[x] == ansB[y]) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
	return 0;
}
```

---

## 作者：PDAST (赞：0)

## 题目大意
题目的意思是，给你两个正整数串 $A$ 和 $B$，再给你 $Q$ 个询问，每次询问给出一个 $X_{i}$ 和一个 $Y_{i}$，问从 $1$ 到 $A_{X_{i}}$ 去重后，与从 $1$ 到 $B_{Y_{i}}$ 去重后相等吗？
## 思路
最开始想的是前缀和，前缀的是去重后的和，但发现会被几个数相加后与另几个不同的数相加后的和相等，于是想到加一个异或，发现还不行，就又加了一个奇数的前缀和，三个前缀和加在一起，总算行啦！！！
## Code
[AC 记录](https://www.luogu.com.cn/record/152557594)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int suma[200001],sumb[200001];
int sum1[200001],sum2[200001];
int xora[200001],xorb[200001];
int a[200001],b[200001];
map<int,bool> m1,m2;
signed main(){
	int n,x,y;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	for(int i=1;i<=n;i++){
		sum1[i]=sum1[i-1]+a[i]*(!m1.count(a[i]));
		sum2[i]=sum2[i-1]+b[i]*(!m2.count(b[i]));
		xora[i]=xora[i-1]^(a[i]*(!m1.count(a[i])));
		xorb[i]=xorb[i-1]^(b[i]*(!m2.count(b[i])));
		suma[i]=suma[i-1]+(a[i]*(!m1.count(a[i])))*(a[i]%2);
		sumb[i]=sumb[i-1]+(b[i]*(!m2.count(b[i])))*(b[i]%2);
		m1[a[i]]=1;
		m2[b[i]]=1;
	}
	int q;
	scanf("%lld",&q);
	while(q--){
		scanf("%lld %lld",&x,&y);
		if(suma[x]==sumb[y]&&xora[x]==xorb[y]&&sum1[x]==sum2[y]){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
	return 0;
}
		
```

---

