# [ABC361C] Make Them Narrow

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc361/tasks/abc361_c

長さ $ N $ の数列 $ A $ が与えられます。  
 $ A $ のうち丁度 $ K $ 要素を自由に選んで消し、残った要素を順序を保って連結した数列を $ B $ とします。  
 ( $ B $ の最大値 ) $ - $ ( $ B $ の最小値 ) としてありうる最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ K\ <\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
 
### Sample Explanation 1

$ A=(3,1,5,4,9) $ から丁度 $ 2 $ 要素を自由に選んで消すことを考えます。 - 例えば $ 2 $ 要素目の $ 1 $ 、 $ 5 $ 要素目の $ 9 $ を消すと、消した後の数列 $ B=(3,5,4) $ となります。 - このとき $ B $ の最大値は $ 5 $ 、最小値は $ 3 $ なので ( $ B $ の最大値 ) $ - $ ( $ B $ の最小値 ) $ =2 $ となり、これは達成可能な最小値です。

## 样例 #1

### 输入

```
5 2
3 1 5 4 9```

### 输出

```
2```

## 样例 #2

### 输入

```
6 5
1 1 1 1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
8 3
31 43 26 6 18 36 22 13```

### 输出

```
18```

# 题解

## 作者：ganyu1 (赞：0)

# ABC361_C Make Them Narrow
## 题目大意
有一个长度为 $n$ 的序列，需要从中删去 $k$ 个数，使序列的最大值与最小值之差最小。
## 思考过程
删数一定要从数列的最大值或最小值中删的，这样才会使最值之差减小，因此要先将序列排序。由于无论怎么删，都是要删掉 $k$ 个数，所以我们可以枚举从序列左边删去多少个数，从而得出此种删数方法的结果，最后比出最小值即可，复杂度 $O(n)$ 。
## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200001
using namespace std;
int n,k,a[N];
int ans=LLONG_MAX;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);//排序
	for(int i=0;i<=k;i++){//枚举从左边删去多少数
		ans=min(ans,a[n-k+i]-a[1+i]);//计算每种方式答案，比出最小值
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：unordered_yao (赞：0)

## 思路

1. 因为删两边的数要比删中间的数要优，所以，我们可以枚举删除两边的数，算其剩余的数的最大值减最小值。

2. 那怎么枚举两边的数呢？设枚举到的数的坐标为 $i$，那么我们要删除 $k$ 个数，就只能保留 $n-k$ 个数。所以，当枚举到 $a_i$ 这个数时，只需要往后找 $n-k$ 个数，即找到 $a_{i+n-k+1}$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T &x){
    x = 0;char ch = getchar();bool f = 0;
    while(ch < '0' || ch > '9'){if(ch == '-')f = 1;ch = getchar();}
    while(ch >= '0' && ch <= '9')x = (x<<1) + (x<<3) + (ch^48),ch=getchar();
    if(f)x = -x;                                       
}
template <typename T,typename ...Args>
inline void read(T &tmp,Args &...tmps){read(tmp);read(tmps...);}
template<typename type>
inline void write(type x,short mode=0)//0为空格，1为换行，2啥也不干
{
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10; while(x);
    while(top) putchar(Stack[top--]|48);
    if(mode == 2) return;
    mode?putchar('\n'):putchar(' ');
}
const int N = 2e5+10;
int n,k;
int a[N],d[N];
signed main(){
    read(n,k);
    for(int i=0;i<n;i++) read(a[i]);
    sort(a,a+n);
    int res=2e9;
    for(int i=0;i<=k;i++) res=min(res,a[i+n-k-1]-a[i]);
    write(res);
    return 0;
}
```

---

## 作者：int_stl (赞：0)

我们可以将题目转变为：从序列 $A$ 中取出 $N - K$ 个数，最小化极差。

我们考虑将 $A$ 排序，那么答案就是：

$$
\min_{1 \le i \le N, i + N - K - 1 \le N} (A_{i + N - K - 1} - A_{i})
$$

直接计算即可，时间复杂度 $O(n \log n)$。

[Submission Link.](https://atcoder.jp/contests/abc361/submissions/55298960)

---

## 作者：Hughpig (赞：0)

要让 $B$ 的极差最小，在删数时保留从大到小连续的 $N-K$ 个数即可（这样最大值和最小值最接近，就可以最小化极差了）。

先把 $A$ 从小到大排序，问题转化为找到连续的 $N-K$ 个数，最后一个减去第一个的差最小。把 $A$ 扫描一遍即可。

时间复杂度 $O(n\log n)$，瓶颈在于排序。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

constexpr int N=2e5+9;

int n,k,a[N],ans=1e9;

int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>a[i];sort(a+1,a+n+1);
   	for(int i=1;i<=k+1;++i){
   		ans=min(ans,a[i+n-k-1]-a[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

为了使极差最小，排序后从两边删起，可以让极差更小。理由：删去中间的，不会影响最大值与最小值，删去两边可使最大值更小、最小值更大。

删去方法是有限的且不多。从小到大排序后从左删 $x$ 个数，则要从右删 $K-x$ 个数。此时极差为 $A_{N-K+x}-A_{x+1}$。对于每个 $x$，分别计算取最小即可。

---

## 作者：1234567890sjx (赞：0)

降智了。贪心的发现答案一定是把原数组排序，然后删除 $k$ 个元素之后剩下的数的值尽量连续，才能保证极差最小。所以**考虑使用 ST 表维护静态区间最值**，时间复杂度为 $O(n\log n)$。

注：其实有序数组中求 $[l,r]$ 区间的极差可以直接 $a_r-a_l$。使用 ST 表求是【】的日常 AT 降智行为。

```cpp
bool begmem;
#include <bits/stdc++.h>
#define int long long
using namespace std;
class FastIO {
public:
    int read() {
        int o = 1, x; char ch;
        while (!isdigit(ch = getchar())) {
            if (ch == '-') {
                o = -1;
            }
        }
        x = ch ^ 48;
        while (isdigit(ch = getchar())) {
            x = (x << 3) + (x << 1) + (ch ^ 48);
        }
        return o * x;
    }
} ; FastIO io;

void calcqwq();
const int N = 500100, inf = 1e18;
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
inline void swap(int &a, int &b) { a ^= b ^= a ^= b; }
int f[N][20], g[N][20], lg[N], a[N];
int q1(int l,int r){
  if(l>r)
    return 0;
  int len=r-l+1,k=lg[len];
  return max(f[l][k],f[r-(1<<k)+1][k]);
}
int q2(int l,int r){
  if(l>r)
    return 1e18;
  int len=r-l+1,k=lg[len];
  return min(g[l][k],g[r-(1<<k)+1][k]);
}
signed main() {
    atexit(calcqwq);
    int n, k, x;
    n = io.read(), k = io.read();
    for (int i = 1; i <= n; ++i) a[i] = io.read();
    sort(a + 1, a + n + 1);
    lg[0] = -1;
    for (int i = 1; i <= n; ++i) lg[i] = lg[i / 2] + 1, f[i][0] = a[i], g[i][0] = a[i];
    for (int j = 1; j < 20; ++j)
        for (int i = 1; i <= n - (1ll << j) + 1; ++i) {
            f[i][j] = max(f[i][j - 1], f[i + (1ll << (j - 1))][j - 1]);
            g[i][j] = min(g[i][j - 1], g[i + (1ll << (j - 1))][j - 1]);
        }
    int mi = 1e18;
    for (int l = 1, r = n - k; r <= n; l++, r++) {
        int f1 = q1(l, r), f2 = q2(l, r);
        mi = min(mi, f1 - f2);
    }
    printf("%lld\n", mi);
    return 0;
}
bool endmem;
void calcqwq() {
    fprintf(stderr, "Memory = %.5lf\n", (&begmem - &endmem) / 1048576.);
}
```

---

## 作者：juruo5e59 (赞：0)

### 翻译：
给定一个长度为 $N$ 的数列 $A$，你需要在 $A$ 内删除 $K$ 个元素，使得删除后元素集合的最大值和最小值的差值最小。
### 思路：
根据贪心思想，每次都删最小的或者最大的才能保证能删出最优答案。代码实现中，由于原序列删除过后产生的序列必然是它排序后的一段连续子序列，所以不用真的删，可以暴力枚举连续子序列的左端点，右端点也可以计算。因为整个序列有序，连续子序列也必然有序，所以计算连续子序列中最大值和最小值的差时，只需要计算连续子序列第一项和最后一项的差即可。
### 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[200010];
signed main() {
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	sort(a + 1, a + 1 + n);
	int minn = 1e12, m = n - k; //这里的 m 为删除后的元素个数
	for (int i = 1; i <= n - m + 1; i ++)
		minn = min(minn, a[i + m - 1] - a[i]);
	cout << minn;
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# Part 1 - 题面翻译

给你一个长度为 $N$ 的序列 $A$。  

请从 $A$ 中任意选择 $K$ 个元素并将其删除，然后按原来的顺序将剩余的元素连接起来，形成一个新的序列 $B$。  

求 $B$ 的极差的最小值。

# Part 2 - 算法思路

要求 $B$ 的极差最小，显然需要是 $A$ 从小到大排序后连续的长度为 $N-K$ 的一段。

那么我们可以将 $A$ 排序后枚举每一段连续子序列。设当前的左端点是 $i$，右端点是 $i+N-K-1$，那么最小值是 $A_i$，最大值是 $A_{i+N-K-1}$，极差就是 $A_{i+N-K-1}-A_i$。更新最小值即能算出答案。

# Part 3 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n, k, a[200024], ans = 1e18;	 

int main() {

	scanf("%lld %lld", &n, &k);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	sort(a + 1, a + n + 1);
	ll len = n - k;
	for (ll i = len; i <= n; i++) {
		ans = min(ans, a[i] - a[i - len + 1]);
	}
	printf("%lld", ans);

	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

注意到要使极差最小，那么如果要删除一个数，当前最优肯定是删最大值或最小值。

那么我们可以先将数组排序，然后枚举删除多少个最小值 $i$，则删除的最大值数量肯定是 $k-i$，那么此时的极差就是 $a_{n-(k-i)}-a_{i+1}$。

取一个最小值即可，时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,k,ans=1e18;
ll a[N];
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	sort(a+1,a+n+1);
	for(int i=0;i<=k;i++)
	  ans=min(ans,a[n-(k-i)]-a[i+1]);
	write(ans);
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

题意：给定正整数 $n,k$，长为 $n$ 的序列 $a$，求从 $a$ 中任意删除 $k$ 个元素后 $\max a-\min a$ 的最小值。

先把 $a$ 升序排序。由贪心可知，最优解一定是在左右两边累计删除 $k$ 个产生的。

可以枚举删除后左边元素的原下标 $i$，则右边下标为 $n-k+i+1$，更新答案即可。

```cpp
#include <bits/stdc++.h>
#define N 200005
using namespace std;

int n, k, a[N];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	int res = INT_MAX;
	for (int i = 1; i <= k + 1; i++) {
		res = min(res, a[n - k + i - 1] - a[i]);
	}
	cout << res;
	return 0;
}
```

复杂度 $O(n \log n+k)$。

---

## 作者：_xdd_ (赞：0)

- 删去 $k$ 个数，就等于留下 $n-k$ 个数。
- 要使答案最小，删去的数一定在**排序后**的序列两端。

先从大到小排序，然后枚举左右两边删去的数的可能位置，计算当前状态的答案。也就是求 $\min{A_{n-k+i}-A_{i+1}}$，其中 $0 \le i \le k$。

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int n,k,a[1000000],ans=2147483647;
signed main(){
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    sort(a+1,a+n+1);
    for(int i=0;i<=k;i++){
        ans=min(ans,a[n-k+i]-a[i+1]);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：DrAlfred (赞：0)

摘要：贪心，枚举，极差

[传送门：https://www.luogu.com.cn/problem/AT_abc361_c](https://www.luogu.com.cn/problem/AT_abc361_c)

## 题意

给定一个长度为 $n$ 的序列 $a_n$，从中任意删除 $k$ 个数字，使得剩余数字的极差最小。

## 分析思路

注意到极差的一个性质：如果删除一个数之后，数列的极差改变，那删除的一定是某个最大值或最小值。考虑先对 $a$ 进行排序。

由于一共删除了 $k$ 个数，我们枚举删除的最小值的个数 $i$，则剩下的数为 $a_{i + 1}, a_{i + 2}, \dots a_{i + n - k}$。由于 $a$ 已经排序，这段数的极差即为 $a_{i + n - k} - a_{i + 1}$。取极差的最小值即可。

时间复杂度为排序带来的 $O\left(n \log n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int n, k, a[N], ans = 1e9;
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    for (int i = 0; i <= k; i++) {
        ans = min(ans, a[i + n - k] - a[i + 1]);
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc361_c)

## 思路

题目中要求找极差的最小值，那么我们可以考虑排序后从 $1$ 到 $N$ 遍历一遍，用滑动窗口的思想找。

注意这样找出来的是选中的 $K$ 个数的最小极差，单题目中要求找的是剩下的 $N-K$ 个数的最小极差，所以我们要在进行 ``k=n-k`` 这步操作后再找。

- 找最小值，结果变量最初要赋极大值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,k,a[N],ans=1e9;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>a[i];
	sort(a+1,a+1+n);
	k=n-k;
	for(int i=k;i<=n;++i)ans=min(ans,a[i]-a[i-k+1]);
	cout<<ans<<"\n";
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc361/submissions/55291765)

---

## 作者：PineappleSummer (赞：0)

[[ABC361C] Make Them Narrow](https://www.luogu.com.cn/problem/AT_abc361_c)

题意：给出长为 $n$ 的序列 $a$ 和一个正整数 $k$，你需要删去 $k$ 个数字，使留下数字的最大值与最小值之差最小。

题目上要删去 $k$ 个数字，就是要留下 $n-k$ 个数字，发现留下的数字一定是连续的，否则答案一定不是最优。那么只需要从 $k$ 到 $n$ 枚举，答案对 $a_i-a_{i-k+1}$ 取 $\min$ 即可。


[提交记录](https://atcoder.jp/contests/abc361/submissions/55384989)

---

## 作者：Heldivis (赞：0)

去掉 $K$ 个数，相当于选出 $N-K$ 个数。

如果选出来的若干个数 $B_1, B_2, \dots B_{n-k}$，为了方便，不妨设 $ B_i \le B_{i + 1}$.

考虑如果存在一个数 $x \in A$，使得 $x \notin B$ 且 $B_1 \le x \le B_{N-K}$，那么 $B$ 去掉 $B_1$ 或 $B_{N-K}$，加上 $x$ 一定是不劣的。所以可以发现 $B$ 一定是排过序的 $A$ 中，一段连续的区间。

枚举一遍左端点，计算右端点，计算极差更新答案即可。

代码：

```cpp
int n, k, res = Inf;
k = n = read();
k -= read();
for (int i = 1; i <= n; i++) a[i] = read();
sort(a + 1, a + 1 + n);
for (int i = 1; i + k - 1 <= n; i++)
  res = min(res, a[i + k - 1] - a[i]);
printf("%lld\n", res);
```

---

## 作者：Redamancy_Lydic (赞：0)

## 背景

昨天打比赛的时候查了中考分，心快停跳了。

## 题意

从 $n$ 个数字中删除 $k$ 个数字，问剩下的数字中极差的最小值。

## 分析

首先把这 $n$ 个数字排序，然后问题就可以转化为求这 $n$ 个数字中所有长度为 $n-k$ 的连续子段的极差的最小值。

采用尺取法，可以从 $1$ 开始枚举左端点。设当前左端点为 $i$，则右端点为 $n-k+i-1$。然后中途更新 $ans$ 值即可。

## Code

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
using namespace std;
using namespace  __gnu_pbds;
//gp_hash_table<string,int>mp2;
//__gnu_pbds::priority_queue<int,less<int>,pairing_heap_tag> q;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
int n,k;
int a[maxn],ans=1e9+7;
signed main()
{
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n>>k;
	k=n-k;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n-k+1;i++)
	{
		ans=min(ans,a[i+k-1]-a[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：OIer_Tan (赞：0)

[AT 传送门](https://atcoder.jp/contests/abc361/tasks/abc361_c)  [洛谷传送门](https://www.luogu.com.cn/problem/AT_abc361_c)

看见好多人赛时不会贪，乐。

## 题意

给你一个长度为 $N$ 的序列 $A$ 。  
请从 $A$ 中任意选择 $K$ 个元素并将其删除，然后将剩余的元素按原来的顺序连接起来，形成一个新的序列 $B$ 。  
求 $B$ 的最大值减去 $B$ 的最小值的最小值。

## 思路

既然删掉 $k$ 个数后，最大值减去最小值最小，所以在对 $A$ 排序后，答案对应的 $B$ 一定是上面连续的 $n-k$ 个数。

根据这个思路，即可完成。

时间复杂度为 $O(n\log n+n)$。

## 代码

```cpp
#include <bits/stdc++.h>

#ifndef CRT
#define endl '\n'
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , k , a [N] ;

ll minn = 1e18 ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> n >> k ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> a [i] ;
	}
	k = n - k ;
	sort ( a + 1 , a + 1 + n ) ;
	for ( ll i = k ; i <= n ; i ++ )
	{
		minn = min ( minn , a [i] - a [i - k + 1] ) ;
	}
	cout << minn << endl ;
	return 0 ;
}
```

---

## 作者：云裳 (赞：0)

**题意**

求将序列 $A$ 中删去 $k$ 个数后得到的序列的极差的最小值。

**思路**

由于对于删去的数没有顺序限制，所以先将 $A$ 排序。然后转换一下题意，删去 $k$ 个数就是选出 $k'=n-k$ 个数。

显然最后得到的数列一定是 $A$ 中连续的一段。因为比如样例排序后是 `1 3 4 5 9`，选 `3 4 5` 肯定不劣于 `1 4 5` 或 `3 4 9` 。

所以答案就变成了 $\max_{i=1}^{n-k'+1}\{f(i,i+k'-1)\}$，其中 $f(i,j)$ 为 $[i,j]$ 的极差。

**代码**
```cpp
void solve(){
		ll n=read(),k=read();
		up(i,1,n) a[i]=read();
		k=n-k;
		sort(a+1,a+n+1);
		up(i,1,n-k+1)  ans=min(ans,a[i+k-1]-a[i]);
		write(ans);
    }
```

---

## 作者：zhlzt (赞：0)

### 题解
题目要求最大值减最小值最小，我们可以贪心地将序列 $a$ 排序，暴力枚举其中每一个长度为 $n-k$ 的子串即可，最大值和最小值显然分别是子串的最后和最前。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int a[maxn]; 
int main(){
	int n,k;scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	sort(a+1,a+1+n); k=n-k;
	int ans=2e9;
	for(int i=1;i<=n-k+1;i++){
		ans=min(ans,a[i+k-1]-a[i]);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

