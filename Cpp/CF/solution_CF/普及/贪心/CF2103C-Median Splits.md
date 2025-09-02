# Median Splits

## 题目描述

数组 $b_1, b_2, \ldots b_m$ 的中位数记作 $\operatorname{med}(b_1, b_2, \ldots, b_m)$，定义为数组 $b$ 中第 $\left\lceil \frac{m}{2} \right\rceil$ 小的元素。

给定一个整数数组 $a_1, a_2, \ldots, a_n$ 和一个整数 $k$。你需要判断是否存在一对下标 $1 \le l < r < n$ 满足：

$$
\operatorname{med}(\operatorname{med}(a_1, a_2 \dots a_l), \operatorname{med}(a_{l + 1}, a_{l + 2} \dots a_r), \operatorname{med}(a_{r + 1}, a_{r + 2} \dots a_n)) \leq k.
$$

换句话说，判断是否可以将数组分割为三个连续的子数组，使得这三个子数组中位数的中位数小于或等于 $k$。

## 说明/提示

在第一个和第二个测试用例中，唯一可能的分割方式是将数组分为 $[3]$、$[2]$、$[1]$。它们的中位数分别是 $3$、$2$ 和 $1$。这三个中位数的中位数是 $\operatorname{med}(3, 2, 1) = 2$。因此，第一个测试用例的答案是 "YES"（因为 $2 \le 2$），而第二个测试用例的答案是 "NO"（因为 $2 > 1$）。

在第三个测试用例中，可以证明不存在满足条件的分割。

在第四个测试用例中，一个满足条件的分割是 $[10, 7]$、$[12, 16, 3, 15]$、$[6, 11]$。子数组的中位数分别是 $7$、$12$ 和 $6$。这三个中位数的中位数是 $\operatorname{med}(7, 12, 6) = 7 \le k$，因此该分割满足条件。

在第五个测试用例中，一个满足条件的分割是 $[7, 11]$、$[12, 4]$、$[9, 17]$。子数组的中位数分别是 $7$、$4$ 和 $9$。这三个中位数的中位数是 $\operatorname{med}(7, 4, 9) = 7 \le k$，因此该分割满足条件。

在第六个测试用例中，唯一可能的分割方式是将数组分为 $[1000]$、$[10^9]$、$[1000]$。子数组的中位数分别是 $1000$、$10^9$ 和 $1000$。这三个中位数的中位数是 $\operatorname{med}(1000, 10^9, 1000) = 1000 \le k$，因此该分割满足条件。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6
3 2
3 2 1
3 1
3 2 1
6 3
8 5 3 1 6 4
8 7
10 7 12 16 3 15 6 11
6 8
7 11 12 4 9 17
3 500000000
1000 1000000000 1000```

### 输出

```
YES
NO
NO
YES
YES
YES```

# 题解

## 作者：potata111 (赞：4)

## [_CF2103C_](https://www.luogu.com.cn/problem/CF2103C) Median Splits

### 题意

定义 $\operatorname{med}(b_1, b_2, \dots, b_m)$ 为数列 $b$ 的中位数。

形式上，$\operatorname{med}(b_1, b_2, \dots, b_k)$ 是 $b$ 中第 $\lceil \frac{m}{2} \rceil$ 小的元素。

给定一个长为 $n$ 的数列 $a$ 和一个整数 $k$，请你判断能不能将 $a$ 分成三部分（三个**子数组**），使得每部分的中位数不超过 $k$。


---


### 分析

我们首先明确一个思路：若 $a$ 的子数列 $a_{[l, r]}$ 的中位数小于等于 $k$，当且仅当有至少 $\lceil \frac{r - l + 1}{2} \rceil $ 个元素小于等于 $k$。~~这很显然~~


如题意，若存在一种分割的方式（使得每部分的中位数小于等于 $k$），则应当存在一个 $l, r$ 将 $a$ 的**下标**分为：$[1, l],\ (l, r),\ [r, n]$ **三个部分**。


---

### 细节

我们考虑如何以 $O(n)$ 的时间复杂度得到 $l, r$，故考虑以 $O(1)$ 的时间判断每个小标 $i$ 分别能否作为**左**割点与**右**割点。

那么我们就可以以线性的时间预处理：

- $L_i$ 表示前 $i$ 个数（也即 $a_{[1, i]}$ ）中**不超过** $k$ 的数的数量。
- $R_i$ 表示后 $i$ 个数（也即 $a_{[n - i + 1, n]}$）中**不超过** $k$ 的数的数量。

分别考虑 $l$ 和 $r$：

- 若某个下标 $l$ 可以作为左割点，则应当有 $2L_l \ge l$。
- 若某个下标 $r$ 可以作为右割点，则应当有 $2R_r \ge (n - r + 1)$。

则可以分成符合题意的三个部分的充分条件有三：

1. 有**两**个**左**割点；
2. 有**两**个**右**割点；
3. 一左一右（注意**左割点**必须**在右割点**的**左边**）。



---

### 实现

上面讲的很清楚，先预处理，再判别即可。


```cpp
#include<iostream>

using namespace std;

const int Potata = (114514 << 1);

int q;
int n, k;
int arr[Potata];
int Left[Potata], Right[Potata];

void solve()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	int left = -1, right = -1;
	bool ans = false;

	Left[0] = 0;
	for (int i = 1; i <= n; i++)
		Left[i] = Left[i - 1] + (arr[i] <= k);

	Right[n + 1] = 0;
	for (int i = n; i >= 1; i--)
		Right[i] = Right[i + 1] + (arr[i] <= k);

	for (int i = 1; i <= n; i++)
		if ((Left[i] << 1) >= i)
			ans = ((ans) || ((left != -1) && (Left[i] > 1))), // 两个左割点
			left = ((ans == false) ? (i) : (left));

	for (int i = n; i >= 1; i--)
		if ((Right[i] << 1) >= (n - i + 1))
			ans = ((ans) || ((right != -1) && (Right[i] > 1))), // 两个右割点
			right = ((ans == false) ? (i) : (right));

	ans = ((ans) || ((left != -1) && (right != -1) && (left < right))); // 一左一右

	if (ans)
		cout << "Yes" << '\n';
	else
		cout << "No" << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> q;

	while (q--)
		solve();

	return 0;
}
```

---

## 作者：znzryb (赞：1)

## 思路讲解

首先，注意到，这道题目我们是不在意这个段的中位数到底是几的，我们只在意这个段的中位数是 $>K$ 还是 $≤K$。因此我们只需要通过记录 $≤K$ 的数的数量，就可以知道符不符合要求。

那么前缀和后缀可以用这种方法比较简便的求得，那么中间的怎么办呢？

以前缀为例，在处理的时候，直接判断该位置和最近的前缀合法位置能不能组合为两个合法段（贪心地，我们认为总是和最近的段组合为两个合法段），后缀反之亦然。
```cpp
vector<ll> pres;
	FOR(i,1,N){
		preA[i]=preA[i-1];
		if(A[i]<=K){
			++preA[i];
		}
		if(!pres.empty()){
			// 将这个点和之前合法的前缀组合一下，看看呢能不能凑出两个合法段
			ll len=i-pres.back();
			ll num=preA[i]-preA[pres.back()];
			if(num>=ceil(len/2.0)){
				cout<<"YES\n";
				return;
			}
		}
		if(preA[i]>=ceil(i/2.0l)){
			pres.pb(i);
		}
	}
```

## AC代码

https://codeforces.com/contest/2103/submission/318394685

    
```cpp
    // Problem: C. Median Splits
    // Contest: Codeforces - Codeforces Round 1019 (Div. 2)
    // URL: https://codeforces.com/contest/2103/problem/C
    // Memory Limit: 256 MB
    // Time Limit: 2000 ms
    // by znzryb
    // 
    // Powered by CP Editor (https://cpeditor.org)
    
    #include <bits/stdc++.h>
    #define all(x) x.begin(),x.end()
    #define CLR(i,a) memset(i,a,sizeof(i))
    #define fi first
    #define se second
    #define pb push_back
    #define SZ(a) ((int) a.size())
    #define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
    #define ROF(i, a, b) for (int i = (a); i >= (b); --i)
    
    using namespace std;
    
    typedef long long ll;
    typedef unsigned long long ull;
    typedef __int128 i128;
    typedef pair<ll,ll> pll;
    typedef array<ll,3> arr;
    typedef double DB;
    typedef pair<DB,DB> pdd;
    typedef pair<ll,bool> plb;
    constexpr ll MAXN=static_cast<ll>(1e6)+10,INF=static_cast<ll>(1e18)+3;
    constexpr ll mod=static_cast<ll>(1e9)+7;
    constexpr double eps=1e-8;
    
    ll N,M,K,T,A[MAXN];
    // 比K小的计数（前序，后序）
    ll sufA[MAXN],preA[MAXN];
    
    inline void solve(){
    	cin>>N>>K;
    	// vector<ll> posK;
    	FOR(i,1,N){
    		cin>>A[i];
    		// if(A[i]<=K){
    			// posK.pb(i);
    		// }
    	}
    	preA[0]=0,sufA[N+1]=0;
    	vector<ll> pres;
    	FOR(i,1,N){
    		preA[i]=preA[i-1];
    		if(A[i]<=K){
    			++preA[i];
    		}
    		if(!pres.empty()){
    			ll len=i-pres.back();
    			ll num=preA[i]-preA[pres.back()];
    			if(num>=ceil(len/2.0)){
    				cout<<"YES\n";
    				return;
    			}
    		}
    		if(preA[i]>=ceil(i/2.0l)){
    			pres.pb(i);
    		}
    	}
    	vector<ll> sufs;
    	ROF(i,N,1){
    		sufA[i]=sufA[i+1];
    		if(A[i]<=K){
    			++sufA[i];
    		}
    		if(!sufs.empty()){
    			ll len=sufs.back()-i;
    			ll num=sufA[i]-sufA[sufs.back()];
    			if(num>=ceil(len/2.0)){
    				cout<<"YES\n";
    				return;
    			}
    		}
    		if(sufA[i]>=ceil((N-i+1)/2.0l)){
    			sufs.pb(i);
    		}
    	}
    	if(!pres.empty()){
    		if(!sufs.empty()){
    			if(sufs.front()-pres.front()>=2){
    				cout<<"YES\n";
    				return;
    			}
    		}
    	}
    	// if(!pres.empty()){
    // 		
    	// }
    	cout<<"NO\n";
    }
    
    int main()
    {
    	ios::sync_with_stdio(false);
    	cin.tie(0);cout.tie(0);
    	cin>>T;
    	while(T--){
    		solve();
    	}
    	// solve();
    	return 0;
    }
    /*
    AC
    https://codeforces.com/contest/2103/submission/318394685
    */
```

---

## 作者：Cells (赞：0)

## 题意
给定一个数组，求将是否有将数组划分为连续的三个子数组，使得三个子数组的中位数的中位数小于等于 $k$。
## 思路
由题得，因为三个数组的中位数的中位数，所以三个数组的中位数必须有两个的小于等于 $k$。问题转化为怎么找出这样的划分，无非这三种情况：

1. 左边（中位数小于等于 $k$），中间（和前面一样）
2. 中间，右边
3. 左边，右边

有一个经典的套路，设 $b_i = \displaystyle \sum_{j = 1}^{i} [a_j \le k]$，如果 $b_i \times 2 \ge i$，说明 $[1, i]$ 这个区间可以作为一个划分，这是从左到右，从右到左反过来枚举。

如果有两个左边点，只要当前的小于等于 $k$ 的个数大于 $1$，就一定可以将一部分划给第一个区间，然后完成，右边点亦然。

最后是两种点都有，只要满足左在右的左边就可以了（$left < right - 1$）。

```c++
//# pragma GCC optimize("Ofast")
# include <bits/stdc++.h>
# define fr front
# define il inline
# define fir first
# define sec second
# define vec vector
# define it iterator
# define pb push_back
# define lb lower_bound
# define ub upper_bound
# define all(x) x.begin(), x.end()
# define mem(a, b) memset(a, b, sizeof(a))

# define lc (t[p].l)
# define rc (t[p].r)
# define ls(x) (x << 1)
# define rs(x) (x << 1 | 1)
# define lson ls(p), l, mid
# define rson rs(p), mid + 1, r

# define sqr(x) ((x) * (x))
# define bpc __builtin_popcount
# define lowbit(x) ((x) & (-(x)))
# define geti(x, i) (((x) >> (i)) & 1)
# define set1(x, i) ((x) | (1 << (i)))
# define set0(x, i) ((x) & (~(1 << (i))))

# define debug1(x) cerr << #x << " = " << x << " "
# define debug2(x) cerr << #x << " = " << x << "\n"
# define bug cerr << "--------------------------\n"

# define each1(i, x) for(auto (i) : (x))
# define each2(i, x) for(auto (&i) : (x))
# define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
# define pre(i, a, b) for(int i = (a); i >= (b); -- i)
# define G(i, h, u, ne) for(int i = (h[(u)]); i; i = (ne[(i)]))
# define reps(i, a, b, c) for(int i = (a); i <= (b); i += (c))
# define pres(i, a, b, c) for(int i = (a); i >= (b); i -= (c))
using namespace std;

using DB = double;
using LL = long long;
using LDB = long double;
using PII = pair<int, int>;
using ULL = unsigned long long;

const int N = 2e5 + 10;
const int INF1 = 0x3f3f3f3f, INF2 = INT_MAX;
const LL INF3 = (LL)1e18, INF4 = 0x3f3f3f3f3f3f3f3f, INF5 = LLONG_MAX;

int T, n, k, l, r;
int a[N], pre[N], suf[N];

bool ans;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> T;
	while(T --){
		cin >> n >> k;
		ans = false;
		l = r = pre[0] = suf[n + 1] = 0;
		
		rep(i, 1, n){
			cin >> a[i];
			pre[i] = pre[i - 1] + (a[i] <= k);
			if(l && pre[i] * 2 >= i && pre[i] > 1){
				ans = true;
			}
			if(!l && pre[i] * 2 >= i) l = i;
		}
		
		pre(i, n, 1){
			suf[i] = suf[i + 1] + (a[i] <= k);
			if(r && suf[i] * 2 >= (n - i + 1) && suf[i] > 1){
				ans = true;
			}
			if(!r && suf[i] * 2 >= (n - i + 1)) r = i;
		}
		
		if(l && r && l < r - 1){
			ans = true;
		}
		
		if(ans) cout << "YES\n";
		else cout << "NO\n";
	}
	
	return 0;
}
```

---

