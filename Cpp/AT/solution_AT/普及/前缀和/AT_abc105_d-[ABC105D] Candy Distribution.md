# [ABC105D] Candy Distribution

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc105/tasks/abc105_d

$ N $ 個の箱が左右一列に並んでおり、左から $ i $ 番目の箱には $ A_i $ 個のお菓子が入っています。

あなたは、連続したいくつかの箱からお菓子を取り出して $ M $ 人の子供たちに均等に配りたいと考えています。

そこで、以下を満たす組 $ (l,\ r) $ の総数を求めてください。

- $ l,\ r $ はともに整数であり $ 1\ \leq\ l\ \leq\ r\ \leq\ N $ を満たす
- $ A_l\ +\ A_{l+1}\ +\ ...\ +\ A_r $ は $ M $ の倍数である

## 说明/提示

### 制約

- 入力は全て整数である
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 2\ \leq\ M\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

各組 $ (l,\ r) $ に対する和 $ A_l\ +\ A_{l+1}\ +\ ...\ +\ A_r $ は次のとおりであり、このうち $ 3 $ つが $ 2 $ の倍数です。 - $ (1,\ 1) $ に対する和: $ 4 $ - $ (1,\ 2) $ に対する和: $ 5 $ - $ (1,\ 3) $ に対する和: $ 10 $ - $ (2,\ 2) $ に対する和: $ 1 $ - $ (2,\ 3) $ に対する和: $ 6 $ - $ (3,\ 3) $ に対する和: $ 5 $

## 样例 #1

### 输入

```
3 2
4 1 5```

### 输出

```
3```

## 样例 #2

### 输入

```
13 17
29 7 5 7 9 51 7 13 8 55 42 9 81```

### 输出

```
6```

## 样例 #3

### 输入

```
10 400000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
25```

# 题解

## 作者：heyx0201 (赞：2)

# 题解
## 题意简述
> 给定 $n$ 个数，求这 $n$ 个数中有多少个二元组 $(x,y)$ 满足其中每一个数都是 $m$ 的倍数。
## 思路
前缀和，$(x,y)$ 内每一个数 $\bmod \ m = 0$，可以用 $(sum_y - sum_{x - 1}) \bmod \ m = 0$ 表示。但是这题数据太大，所以要使用 `map`。

如果 $x = 1$，那么 $sum_{x - 1} = sum_0$，所以要先给 $sum_0$ 赋值为 $1$

## AC Code
```cpp
#include<bits/stdc++.h>

using namespace std;

int n, m, x;
map<long long, int> cnt;
long long sum, ans;

int main(){
  cin >> n >> m;
  cnt[0] = 1;
  for (int i = 1; i <= n; i++){
    cin >> x;
    sum += x;
    ans += cnt[sum % m];
    cnt[sum % m]++;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：qwerty12346 (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc105_d)

## 题意

就是求一共有多少个二元组 $(l,r)$ 满足其中每一个数都是 $m$ 的倍数的数。

## 思路

直接前缀和加区间和就行。$(l,r)$ 区间满足其中每一个数都是 $m$ 的倍数的数，可以有公式 $(a_{r}-a_{l-1}) \operatorname{mod} m=0$ 来表示。还有如果 $a_{l-1}$ 中的 $l$ 等于 $1$ 时那么 $a_{l-1}$ 就等于 $a_{0}$，所以要先给 $a_{0}$ 赋值为 $1$，也就是给 map 容器中的 $mp_{0}$ 赋为 $1$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,sum,ret;
map<int,int>mp;//mp容器
int main(){
    cin>>n>>m;
    mp[0]=1;//赋初始值
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        sum=(sum+x)%m;
        ret+=mp[sum];
        mp[sum]++;
    }
    cout<<ret<<endl;
    return 0;
}
```


---

## 作者：细数繁星 (赞：1)

[更好的体验？](https://www.cnblogs.com/2044-space-elevator/articles/17956344)

[题目传送门。](https://www.luogu.com.cn/problem/AT_abc105_d)

> 建议管理员调低难度。感觉明显标高了。

## 大意

求满足以下情况的个数：

$$
m\mid \sum_{i=l}^r a_i
$$
也就是说，满足：

$$
\sum_{i=l}^r a_i =km
$$
两边模同一个模数相同，因此：

$$
\begin{aligned}
\left(\sum_{i=l}^ra_i\right)\bmod m &=0\\
\sum_{i=l}^r(a_i\bmod m)&=0\\
\end{aligned}
$$

对每一个 $a_i$ 重赋值为 $a_i \bmod m$，问题转换为，是否存在一种情况，使得：

$$
\sum_{i=l}^r a_i=0
$$

问题转换为：求前缀和数组中有多少个相同的值的组合。为什么要加个“的组合”呢？因为假设我么就考虑一种情况：就是整个数组里相同项只有一个，那么对应的，如果对于这个相同项有 $n$ 个数组里的数能匹配上，答案就相当于：把这些能匹配上的数两两组合，也就是一共有 $\dfrac{n(n-1)}{2}$ 个。最佳的数据结构当然是散列表。

另外，还有一个注意事项：散列表中 $0$ 得对应设成 $1$。

```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define int ll
map<int, bool> mark;

void solve() {
    
}

#define int ll

main() {
    map<int, int> _M;
    int n, m;
    cin >> n >> m;
    int sum = 0;
    _M[0] = 1;
    rep(i, 1, n) {
        int x;
        cin >> x;
        sum += x;
        _M[sum % m]++;
    }    
    int ans = 0;
    for (auto [keyword, val] : _M) {
        ans += val * (val - 1) / 2; 
    }
    cout << ans;
    return 0;
}

```




---

## 作者：mayike (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc105_d)

~~题外话：这题都没人做吗~~

## 思路

题意就是在一个序列中找一个子串，其子串中所有 $a_i$ 和为 $m$ 的倍数，有多少个这样的子串。

由于 $n$ 的数据实在有点大，所以我们不难想到用前缀和来做。

假设区间 $(l,r)$ 是满足要求的子串，则有
 
$$(sum_r - sum_{l-1}) \bmod m = 0$$

即 $sum_r \bmod m =sum_{l-1} \bmod m$。

由于只能用 $O(n)$ 做法，且 $a_i$ 太大了，所以我们可以用 map 对余数标记，进行到一个数时，看前面有多少个和它一样模 $m$ 余数一样的。特殊情况：即模 $m$ 为 $0$，那么我们给 $sum_0 = 1$ 即可，因为从 $1$ 到这个数的和也是 $m$ 的倍数，具体见代码。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,cnt,sum; 
map<int,int>mayike2b;
int main(){
	cin>>n>>m;mayike2b[0]=1;//初始赋值
	while(n--){
		cin>>x;
		sum=(sum+x)%m;//算余数
		cnt+=mayike2b[sum]++;//和前面的余数一样的加起来
                //这里是从后面算前面的，可以保证不重复
	}cout<<cnt<<'\n';//完美撒花
	return mike;
}
```
谢谢大家

---

## 作者：Nightingale_OI (赞：1)

### 大意

给定一个长度为 $ n $ 的数组 $ a $ 。

求数对个数 $ (l,r) $ ，满足：

$$ (l \leq r) \quad m \Bigg| \sum_{i=l}^{r} a_i $$

### 思路

发现该条件可以改为：

$$ (l \leq r) \quad \sum_{i=1}^{l}a_i \equiv \sum_{i=1}^{r}a_i \quad (mod \quad m)   $$

只需要处理取模后的前缀和并使用映射记录即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
map<int,int>p;
long long ans;
int main(){
    cin>>n>>m;
    ++p[s];
    f(i,1,n){
        scanf("%d",&l);
        s=(s+l)%m;
        ans+=p[s]++;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：xz001 (赞：0)

- 首先我们求出前缀和数组，并模 $m$。
- 这时一段区间和能被 $m$ 整除，仅当 $sum_{r}-sum_{l-1}=0$。也就是问有多少对前缀是相同的。
- 所以我们可以存下来每个前缀的值出现的次数，然后对于每个数的次数 $x$，求其 $\frac{x(x-1)}{2} $，相加即可。
- 代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

// define
#define re register
#define fi first
#define se second
#define il inline
#define co const
#define ls (u << 1)
#define rs (u << 1 | 1)
#define fup(x, l, r) for (re int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (re int x = (r), eNd = (l); x >= eNd; -- x )
#define int long long
#define lowbit(x) ((x)&(-x))

// typedef
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

// const
const int N = 1e6 + 10, M = 1e9 + 1;
const int INF = 2e9, mod = 1e9 + 7;
const double eps = 1e-6;


// debug
const bool DeBug = true;
int db_cnt;
il void db() { if (DeBug) puts("--------------"); return; }
il void db(auto a) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << '\n'; return; }
il void db(auto a, auto b) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << '\n'; return; }
il void db(auto a, auto b, auto c) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << '\n'; return; }
il void db(auto a, auto b, auto c, auto d) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << '\n'; return; }
il void db(auto a, auto b, auto c, auto d, auto e) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << ", " << e << '\n'; return; }
il void db(auto *a, auto len) { if (DeBug) { ++ db_cnt; cout << "-- | t" << db_cnt << " : {"; if (!len) cout << "empty";else { cout << a[1]; for (int i = 2; i <= len; ++ i ) cout << ", " << a[i]; } cout << "}\n"; } return; }
il void db(pair<auto, auto> a) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : <" << a.first << ", " << a.second << ">\n"; return; }

// common functions
il int Max(co int a, co int b) { return a > b ? a : b; }
il int Min(co int a, co int b) { return a < b ? a : b; }
il int read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { (c == '-') ? f = false : 0; c = getchar(); }while (c > 47 && c < 58) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(re auto x) { (x < 0) ? putchar('-'), x = -x : 0; (x > 9) ? write(x / 10) : void(); putchar(x % 10 + 48); return; }
il void wel(co auto x) { write(x), putchar('\n'); return; }
il void wel(co auto x, co int y) { write(x), putchar(' '), write(y), putchar('\n'); return; }
il void wel(co auto x, co int y, co int z) { write(x), putchar(' '), write(y), putchar(' '), write(z), putchar('\n'); return; }
il void wsp(co auto x) { write(x), putchar(' '); return; }

int n, m, a[N], ans;

map <int, int> p;

signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    p[0] = 1;
    for (int i = 1; i <= n; ++ i) a[i] += a[i - 1], ++ p[a[i] % m];
    for (auto i : p) ans += i.second * (i.second - 1) / 2;
    cout << ans;
	return 0;
}


```

---

## 作者：xiongzecheng (赞：0)

### 题目分析：

给定一串数组，找一个子串，和为 $m$ 的倍数，求子串数量。

既然题目要我们记录子串和，不难想到前缀和。

事实上，如果前缀和数组 $s$ 中满足 $s_l$ 和 $s_r(1 \le l < r \le n)$ 除以 $m$ 的余数相同，那么原数组的第 $l+1$ 位至第 $r$ 位的和一定能被 $m$ 整除。

于是我们将前缀和数组整体除以 $m$ 取余数。

那么对于每一个 $s_i$，我们用一个计数器记录之前 $s_i$ 出现了几次，加入到答案中即可。

### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,a[100005],s[100005],ans;
map<ll,ll>mp;
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)s[i]=(a[i]+s[i-1])%m;
	//前缀和数组除以 m 取余数 
	mp[0]++;
	//小心！s[0]=0！ 
	for(int i=1;i<=n;i++){
		//记录s[i]之前出现的次数。 
		ans+=mp[s[i]];mp[s[i]]++;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Down_syndrome (赞：0)

## 题意
给定长度为 $N$ 的序列 $A$，找到满足以下条件的二元组 $(l,r)$ 的数量：
- $\sum\limits_{i=l}^rA_i$ 为 $M$ 的倍数
## 思路
转换一下题中二元组的条件。$\sum\limits_{i=l}^rA_i\mid M$ 等价于 $(\sum\limits_{i=l}^rA_i-\sum\limits_{i=1}^{l-1}A_i)\equiv0\pmod{M}$ 等价于 $\sum\limits_{i=l}^rA_i\equiv\sum\limits_{i=1}^{l-1}A_i\pmod{M}$。
所以题目可以转换为令 $B_i=\sum\limits_{j=1}^iA_j\bmod M$，对于每个 $i$ 有多少个 $j(j<i)$ 使得 $B_i=B_j$。可以用 map 记录。记得初始化 $mp_0\gets1$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
long long n,m,ans,a[N],b[N];
map<long long,long long> f;
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i]=(b[i-1]+a[i])%m;
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		ans+=f[b[i]];
		f[b[i]]++;
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：Jerrywang09 (赞：0)

### 分析

比较老套的题目，思路不是很难想到。

看到“连续的盒子”，就应该想到前缀和，区间问题转化为单点问题。

对于 $[l,r]$ 这一段的区间和是 $m$ 的倍数，转化过后就有：

$$
(sum_r-sum_{l-1}) \bmod m=0
$$

也就是，$sum_r$ 和 $sum_{l-1}$ 模 $m$ 同余。

我们可以用 map 对 $sum$ 进行余数的归类，每类中两两互相组合，就对应最初的一种取糖果方案。

**细节：$sum_{0}$ 是可能用到的，需要加进 map 中。**

### 代码

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, s, t) for(int i=(s); i<=(t); ++i)
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define all(x) x.begin(), x.end()
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=100010, M=200010;
using namespace std;

int n, m;
int a[N];
unordered_map<int, int> mp;

signed main()
{
	scanf("%d%d", &n, &m);
	ll ans=0;
	mp[0]++;
	rep(i, 1, n)
	{
		scanf("%d", a+i);
		a[i]=(a[i]+a[i-1])%m;
//		debug(a[i]);
		mp[a[i]]++;
	}
	for(auto t:mp) ans+=1ll*t.S*(t.S-1)/2;					// 同余前缀和相互组合
	printf("%lld", ans);
	
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

注意到 $\mathcal O(n^3)$ 的复杂度是必定会 TLE 的，考虑优化。

使用前缀和，每次 $\mathcal O(n^2)$ 枚举左右端点 $\mathcal O(1)$ 判断，注意到 $n\le 10^5$，仍会超时。

对于题目里的式子 $\sum\limits_{i=l}^r a_i \mid m$，考虑转化为 $(S_r-S_{l-1})\mid m$，那么必定 $S_r \equiv S_l \pmod m$，那么遍历一遍，在跑的过程中用 `map` 或者 `unordered_map` 记录一下即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)

const int N = 1e5 + 10;
int a[N], s[N];
int n, m;

int main() {
   cin >> n >> m;
   rep (i, 1, n) {
      cin >> a[i]; s[i] = (s[i - 1] + a[i]) % m;
   } 
   unordered_map<int, int> mp; long long ans = 0; 
   mp[0] = 1;
   rep (i, 1, n) ans += mp[s[i]], mp[s[i]]++; 
   cout << ans << '\n';
}
```

---

## 作者：SpeedStar (赞：0)

#### 算法分析

暴力做法的计算量为 $O(N^3)$，通过前缀和技巧可以降到 $O(N^2)$，但依然过不了。。。⊙︿⊙

记 $S_i = \sum\limits_{k = 1}^i A_k$

若 $(A_l + A_{l + 1} + \cdots + A_r) \equiv 0 \pmod M$，则有 $S_r - S_{l - 1} \equiv 0 \pmod M$，于是有 $S_r \equiv S_{l - 1} \pmod M$。

所以，我们只需把每个 $S_i$ 对 $M$ 取模，然后开一个 `std::map` 用来记录 $S_i$ 出现的次数，接着扫描每个 $S_i$，把在位置 $i$ 之前出现的 $S_i$ 的次数加入答案，同时更新 $S_i$ 的次数。 计算量为 $O(N\log N)$。

#### C++ 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using std::cin;
using std::cout;
using std::map;
using std::vector;
using ll = long long;

int main() {
	int n, m;
	cin >> n >> m;
	
	vector<int> a(n);
	rep(i, n) cin >> a[i];
	
	vector<int> s(n + 1);
	rep(i, n) s[i + 1] = (s[i] + a[i]) % m;
	
	map<int, int> mp;
	ll ans = 0;
	rep(i, n + 1) {
		ans += mp[s[i]];
		mp[s[i]]++;
	} 
	
	cout << ans << '\n';
	
	return 0;
}
```


---

