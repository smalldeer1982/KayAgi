# Longest Max Min Subsequence

## 题目描述

You are given an integer sequence $ a_1, a_2, \ldots, a_n $ . Let $ S $ be the set of all possible non-empty subsequences of $ a $ without duplicate elements. Your goal is to find the longest sequence in $ S $ . If there are multiple of them, find the one that minimizes lexicographical order after multiplying terms at odd positions by $ -1 $ .

For example, given $ a = [3, 2, 3, 1] $ , $ S = \{[1], [2], [3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 3, 1], [3, 2, 1]\} $ . Then $ [2, 3, 1] $ and $ [3, 2, 1] $ would be the longest, and $ [3, 2, 1] $ would be the answer since $ [-3, 2, -1] $ is lexicographically smaller than $ [-2, 3, -1] $ .

A sequence $ c $ is a subsequence of a sequence $ d $ if $ c $ can be obtained from $ d $ by the deletion of several (possibly, zero or all) elements.

A sequence $ c $ is lexicographically smaller than a sequence $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ;
- in the first position where $ c $ and $ d $ differ, the sequence $ c $ has a smaller element than the corresponding element in $ d $ .

## 说明/提示

In the first example, $ S = \{[1], [2], [3], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 1, 3], [3, 2, 1]\} $ . Among them, $ [2, 1, 3] $ and $ [3, 2, 1] $ are the longest and $ [-3, 2, -1] $ is lexicographical smaller than $ [-2, 1, -3] $ , so $ [3, 2, 1] $ is the answer.

In the second example, $ S = \{[1]\} $ , so $ [1] $ is the answer.

## 样例 #1

### 输入

```
4
4
3 2 1 3
4
1 1 1 1
9
3 2 1 3 2 1 3 2 1
1
1```

### 输出

```
3
3 2 1
1
1
3
3 1 2
1
1```

## 样例 #2

### 输入

```
10
2
1 2
10
5 2 1 7 9 7 2 5 5 2
2
1 2
10
2 2 8 7 7 9 8 1 9 6
9
9 1 7 5 8 5 6 4 1
3
3 3 3
6
1 6 4 4 6 5
6
3 4 4 5 3 3
10
4 1 4 5 4 5 10 1 5 1
7
1 2 1 3 2 4 6```

### 输出

```
2
1 2
5
5 1 9 7 2
2
1 2
6
2 7 9 8 1 6
7
9 1 7 5 8 6 4
1
3
4
1 4 6 5
3
4 5 3
4
5 4 10 1
5
2 1 3 4 6```

# 题解

## 作者：chenmingeng (赞：21)

——提供一种线性方法


### 题意

求正整数序列 $a$ 的每个元素恰好出现一次的子序列中，将奇数位置上的项乘以 $-1$ 后字典序最小的序列。数据范围：$1 \leqslant a_{i} \leqslant n \leqslant 3\times 10^{5}$。

### 思路

问题等价于最大化奇数位，最小化偶数位。

#### 引例

先考虑这样的问题：求每个元素恰好出现一次的子序列中字典序最小的序列。

维护一个栈。

从前向后遍历，如果新加入的元素比栈尾元素小，就将其弹出，以保证字典序最小。

还有一个问题是可能弹出后这个元素就没有出现过了，故加上两个特判：

- 一是如果已经在栈中，就不做处理，用 `vis` 数组判断；
- 二是如果栈尾元素在序列中最后一次出现，就不弹出，用 `lst` 数组判断。

```cpp
void eachT() {
	int n = read();

	vector<int> a(n), lst(n);
	for (int i = 0; i < n; ++i) {
		a[i] = read() - 1;
		lst[a[i]] = i;
	}

	vector<int> vis(n);
	deque<int> stk;
	for (int i = 0; i < n; ++i) {
		if (vis[a[i]]) continue;
		while (!stk.empty() && a[stk.back()] > a[i] && lst[a[stk.back()]] > i) {
			vis[a[stk.back()]] = 0;
			stk.pop_back();
		}
		stk.push_back(i);
		vis[a[i]] = 1;
	}

	printf("%d\n", stk.size());
	for (int i = 0; i < stk.size(); ++i) {
		printf("%d ", a[stk[i]] + 1);
	}
	printf("\n");
}
```



#### 回到原问题

与上面不同的是，需要依据栈的大小改变大于小于号，维护一个波浪形的栈。

测样例后发现 `4 1 4 5 4 5 10 1 5 1`，错解为 `4 1 10 5`，正解为 `5 4 10 1`，栈中有 `4 1`，`5` 应该将这两个数都弹出后再入栈，但是按上面的写法 `1<5`，不用弹出，补上直接弹出栈尾的两个元素的情形就好了。

时空复杂度 $\Theta(n)$。

### 代码

因为需要访问倒数第二个元素，没有用 `std::stack`。

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
inline ll read() {
    ll S = 0, C = 0; char Y = getchar();
    while (Y > 57 || Y < 48) C |= Y == 45, Y = getchar();
    while (Y <= 57 && Y >= 48) S = (S << 3) + (S << 1) + Y - 48, Y = getchar();
    return C ? -S : S;
}

void beforeT() {}
void eachT() {
    int n = read();

    vector<int> a(n), lst(n);
    for (int i = 0; i < n; ++i) {
        a[i] = read() - 1;
        lst[a[i]] = i;
    }

    int top = -1;
    vector<int> stk(n), vis(n);
    for (int i = 0; i < n; ++i) {
        if (vis[a[i]]) continue;
        while (top >= 0 && (top & 1 ? a[stk[top]] > a[i] : a[stk[top]] < a[i]) && lst[a[stk[top]]] > i) {
            vis[a[stk[top--]]] = 0;
        }
        while (top >= 1 && (top & 1 ? a[stk[top - 1]] < a[i] : a[stk[top - 1]] > a[i]) && lst[a[stk[top - 1]]] > i && lst[a[stk[top]]] > i) {
            vis[a[stk[top--]]] = 0;
            vis[a[stk[top--]]] = 0;
        }
        vis[a[stk[++top] = i]] = 1;
    }

    printf("%d\n", top + 1);
    for (int i = 0; i <= top; ++i) {
        printf("%d ", a[stk[i]] + 1);
    }
    printf("\n");
}

int main() {
    beforeT();
    for (int T = read(); T--; eachT());
    return 0;
}
```

---

## 作者：Z1qqurat (赞：9)

### 大致思路

每场 Div2 是不是都有一个这样的小清新 DS 题啊。和 Level Up 一样，都是只用简单数据结构就能解决的，但是这题的思路和做法比 Level Up 直接多了，也没有那么多种切入角度。

1. Observation: 首先序列长度一定是  $a$ 中出现过的不同的权值个数 $m$，最终的子序列 $b$ 肯定是这 $m$ 种权值各出现一次。

   要求最小化奇偶变号操作之后的子序列字典序，对于这种问题我们从前往后贪心。对于奇数位，我们考虑取当前能选择的最大的数；对于偶数位，我们考虑选当前能选的最小的数。

2. Analysis: 考虑什么样的数 $a_j$ 是能选做子序列的第 $i$ 项的。如果 $b_{i\sim m}$ 中该包含的那 $m-i+1$ 种权值在 $a_{j\sim n}$ 中都出现过，那么 $b_i\gets a_j$ 就是可行的。对于每个 $i$，我们需要按照上面的贪心策略来选取最优的 $a_j$ 填充。

3. Analysis: 考虑怎样判定这个限制。首先是 $b_{i\sim m}$ 中该包含的那 $m-i+1$ 种权值在 $a_{j\sim n}$ 中都出现过。

   * 我们不如直接记录 $suf_i$ 表示 $a_{i\sim n}$ 中不同的权值种数，那么 $suf$ 数组应该是单调不增的。于是我们可以二分出最后一个 $suf_r\ge m-i+1$ 的位置 $r$，假设 $b_{i-1}$ 所在位置为 $lst$，那么 $[lst+1,r]$ 之间的位置都是可以放在 $b_i$ 的。

     我们会发现如果 $b_i\gets v$，那么从现在开始，$v$ 对 $suf$ 每一项产生的贡献都得撤销掉。这个 $suf$ 怎么动态维护？实际上我们只需要记录每一种数最后一次出现的位置 $pos$，然后将 $1\sim pos$ 的 $suf$ 值全部 $-1$。前缀加，单点查询，树状数组结合差分即可。然后外层套一个二分，这样可以 $\log^2 n$ 找到可选位置区间。

   * 观察 $suf$ 的动态维护时可以发现，实际上我们只关心每种数最后一次出现的位置，那么就好办了。我们维护还未填过的数的最晚出现位置集合 $s$，那么 $j$ 的可行位置只要不超过 $s$ 中最小值即可，每次从 $s$ 中删掉 $b_i$ 的最后一次出现位置，就可以动态维护满足限制的选择区间了，同时还能做到单 $\log$，也用不上数据结构。

4. Analysis: 现在就只剩下从限制区间 $[lst+1,r]$ 中选出权值最小/最大的数了。

   * 很容易想到线段树维护区间 $\min,\max$ 以及它们的出现位置。不用 ST 表之类的静态结构维护是因为我们填了 $b_i\gets v$ 之后会把线段树上所有 $a_j=v$ 的位置 ban 掉，因为一种权值不能重复被选择。这样就是单点修改，区间查询，单 $\log$。
   * 当然我们发现可以双指针，并且使用 set 维护当前区间内的数和下标。但是这样写起来还远不如线段树好写，因为直接双指针细节比较多，需要一些分讨，而且 set 的 `begin(), end(), prev(), next(), erase()` 这些都各自有会 RE 的 corner case，稍有不慎少了分讨，就会引发 RE 等错误。虽然 set 的使用少了一个 DS，但是写起来不清爽多了，所以这里还是建议写线段树。

### 代码解析

1. 维护 $suf$ 值 + 线段树维护区间极值，$\mathcal{O}(n\log^2 n)$。

   ```cpp
   #include <bits/stdc++.h>
   
   #define FOR(i, l, r) for (int i = l; i <= (r); ++i)
   #define ROF(i, l, r) for (int i = (r); i >= l; --i)
   #define rep(n) FOR(ii, 1, n)
   #define each(i, x) for (auto &i : x)
   
   using ll = long long;
   using db = double;
   using str = std::string;
   
   using std::cin;
   using std::cout;
   
   using pi = std::pair<int, int>;
   #define mr std::make_pair
   #define fi first
   #define se second
   
   #define tp template <typename T
   tp > using V = std::vector<T>;
   tp, size_t n > using A = std::array<T, n>;
   
   #define sz(x) int((x).size())
   #define ALL(v) begin(v), end(v)
   #define All(v, l, r) &v[l], &v[(r) + 1]
   #define eb emplace_back
   
   #define il inline
   tp > il bool ckmin(T &x, const T &y) { return y < x ? x = y, true : false; }
   tp > il bool ckmax(T &x, const T &y) { return y > x ? x = y, true : false; }
   
   constexpr int inf = 1e9;
   
   struct fwk {
      int n;
      V<int> t;
      fwk (int _n) : n(_n), t(n + 1, 0) {}
   
      int ask(int x) {
         int r = 0;
         for (int i = x; i; i -= i & (-i)) r += t[i];
         return r;
      }
      void _upd(int x, int v) {
         for (int i = x; i <= n; i += i & (-i)) t[i] += v;
         return ;
      }
      void upd(int x, int v) { _upd(1, v), _upd(x + 1, -v); }
   };
   
   struct Info {
      int mn, mx, mnp, mxp;
      void reset(int p) { mn = inf, mx = -inf, mnp = mxp = p; }
      void apply(int v, int p) {
         if (v == -1) reset(p);
         else mn = mx = v, mnp = mxp = p;
      }
      Info operator+ (const Info b) const {
         Info c;
         c.mn = std::min(mn, b.mn), c.mx = std::max(mx, b.mx);
         c.mnp = mn == c.mn ? mnp : b.mnp, c.mxp = mx == c.mx ? mxp : b.mxp;
         return c;
      }
   };
   struct sgt {
      int n;
      V<Info> t;
      sgt (int _n) : n(_n), t(n << 2 | 1) {}
      int lc(int o) { return o << 1; }
      int rc(int o) { return o << 1 | 1; }
      void push_up(int o) { t[o] = t[lc(o)] + t[rc(o)]; }
   
      void modify(int x, int v) {
         auto modify { [&] (auto modify, int o, int l, int r) {
            if (l == r && x == l) return t[o].apply(v, x), void();
            int mid = l + r >> 1;
            if (x <= mid) modify(modify, lc(o), l, mid);
            else modify(modify, rc(o), mid + 1, r);
            push_up(o); return ;
         }};
         return modify(modify, 1, 1, n);
      }
      Info query(int x, int y) {
         auto query { [&] (auto query, int o, int l, int r) {
            if (x <= l && r <= y) return t[o];
            int mid = l + r >> 1; Info ret = {inf, -inf, 0, 0};
            if (x <= mid) ret = query(query, lc(o), l, mid);
            if (y > mid) ret = ret + query(query, rc(o), mid + 1, r);
            return ret;
         }};
         return query(query, 1, 1, n);
      }
   };
   
   void solve() {
      int n, m = 0; cin >> n;
      V<int> a(n + 1, 0);
      FOR (i, 1, n) cin >> a[i];
      V<bool> vis(n + 1, 0);
      V<V<int>> ps(n + 1);
      fwk bt(n); sgt mt(n);
      ROF (i, 1, n) {
         if (ps[a[i]].empty()) bt.upd(i, 1), ++m;
         ps[a[i]].eb(i), mt.modify(i, a[i]);
      }
   
      V<int> ans(m + 1, 0);
      FOR (i, 1, m) {
         int lt = ans[i - 1], rt = n + 1;
         while (lt + 1 < rt) {
            int mid = lt + rt >> 1;
            if (bt.ask(mid) >= m - i + 1) lt = mid;
            else rt = mid;
         }
         auto [mn, mx, mnp, mxp] = mt.query(ans[i - 1] + 1, lt);
         int x = mnp, v = mn;
         if (i & 1) x = mxp, v = mx;
         ans[i] = x;
         for (auto y : ps[v]) mt.modify(y, -1);
         bt.upd(ps[v][0], -1);
      }
      cout << m << "\n";
      FOR (i, 1, m) cout << a[ans[i]] << ' ';
      cout << "\n";
      return ;
   }
   
   int main() {
      std::ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
   
      int tc; cin >> tc;
      while (tc--) solve();
      return 0;
   }
   ```

2. 用 set 找可行区间右端点位置 + 线段树维护区间极值（*感觉最好的一种），$\mathcal{O}(n\log n)$。

   kotatsugame

   ```cpp
   #include<iostream>
   #include<set>
   #include<vector>
   #include<cassert>
   
   #include <algorithm>
   #include <cassert>
   #include <vector>
   
   
   #ifdef _MSC_VER
   #include <intrin.h>
   #endif
   
   namespace atcoder {
   
   namespace internal {
   
   int ceil_pow2(int n) {
       int x = 0;
       while ((1U << x) < (unsigned int)(n)) x++;
       return x;
   }
   
   constexpr int bsf_constexpr(unsigned int n) {
       int x = 0;
       while (!(n & (1 << x))) x++;
       return x;
   }
   
   int bsf(unsigned int n) {
   #ifdef _MSC_VER
       unsigned long index;
       _BitScanForward(&index, n);
       return index;
   #else
       return __builtin_ctz(n);
   #endif
   }
   
   }  // namespace internal
   
   }  // namespace atcoder
   
   
   namespace atcoder {
   
   template <class S, S (*op)(S, S), S (*e)()> struct segtree {
     public:
       segtree() : segtree(0) {}
       explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
       explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
           log = internal::ceil_pow2(_n);
           size = 1 << log;
           d = std::vector<S>(2 * size, e());
           for (int i = 0; i < _n; i++) d[size + i] = v[i];
           for (int i = size - 1; i >= 1; i--) {
               update(i);
           }
       }
   
       void set(int p, S x) {
           assert(0 <= p && p < _n);
           p += size;
           d[p] = x;
           for (int i = 1; i <= log; i++) update(p >> i);
       }
   
       S get(int p) const {
           assert(0 <= p && p < _n);
           return d[p + size];
       }
   
       S prod(int l, int r) const {
           assert(0 <= l && l <= r && r <= _n);
           S sml = e(), smr = e();
           l += size;
           r += size;
   
           while (l < r) {
               if (l & 1) sml = op(sml, d[l++]);
               if (r & 1) smr = op(d[--r], smr);
               l >>= 1;
               r >>= 1;
           }
           return op(sml, smr);
       }
   
       S all_prod() const { return d[1]; }
   
       template <bool (*f)(S)> int max_right(int l) const {
           return max_right(l, [](S x) { return f(x); });
       }
       template <class F> int max_right(int l, F f) const {
           assert(0 <= l && l <= _n);
           assert(f(e()));
           if (l == _n) return _n;
           l += size;
           S sm = e();
           do {
               while (l % 2 == 0) l >>= 1;
               if (!f(op(sm, d[l]))) {
                   while (l < size) {
                       l = (2 * l);
                       if (f(op(sm, d[l]))) {
                           sm = op(sm, d[l]);
                           l++;
                       }
                   }
                   return l - size;
               }
               sm = op(sm, d[l]);
               l++;
           } while ((l & -l) != l);
           return _n;
       }
   
       template <bool (*f)(S)> int min_left(int r) const {
           return min_left(r, [](S x) { return f(x); });
       }
       template <class F> int min_left(int r, F f) const {
           assert(0 <= r && r <= _n);
           assert(f(e()));
           if (r == 0) return 0;
           r += size;
           S sm = e();
           do {
               r--;
               while (r > 1 && (r % 2)) r >>= 1;
               if (!f(op(d[r], sm))) {
                   while (r < size) {
                       r = (2 * r + 1);
                       if (f(op(d[r], sm))) {
                           sm = op(d[r], sm);
                           r--;
                       }
                   }
                   return r + 1 - size;
               }
               sm = op(d[r], sm);
           } while ((r & -r) != r);
           return 0;
       }
   
     private:
       int _n, size, log;
       std::vector<S> d;
   
       void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
   };
   
   }  // namespace atcoder
   
   using namespace std;
   using dat=pair<int,int>;
   dat opmax(dat a,dat b)
   {
   	if(a.first!=b.first)return max(a,b);
   	return a;
   }
   dat opmin(dat a,dat b)
   {
   	if(a.first!=b.first)return min(a,b);
   	return a;
   }
   dat emax(){return make_pair(0,-1);}
   dat emin(){return make_pair((int)1e9,-1);}
   int N,A[3<<17];
   vector<int>idx[3<<17];
   int main()
   {
   	ios::sync_with_stdio(false);
   	cin.tie(nullptr);
   	int T;cin>>T;
   	for(;T--;)
   	{
   		cin>>N;
   		for(int i=1;i<=N;i++)idx[i].clear();
   		for(int i=0;i<N;i++)
   		{
   			cin>>A[i];
   			idx[A[i]].push_back(i);
   		}
   		set<int>L;
   		for(int i=1;i<=N;i++)if(!idx[i].empty())L.insert(idx[i].back());
   		vector<dat>init(N);
   		for(int i=0;i<N;i++)init[i]=make_pair(A[i],i);
   		atcoder::segtree<dat,opmax,emax>segmax(init);
   		atcoder::segtree<dat,opmin,emin>segmin(init);
   		vector<int>B;
   		int pos=0;
   		while(!L.empty())
   		{
   			int r=*L.begin()+1;
   			dat t;
   			if(B.size()%2==0)
   			{//max
   				t=segmax.prod(pos,r);
   			}
   			else
   			{//min
   				t=segmin.prod(pos,r);
   			}
   			assert(t.second!=-1);
   			B.push_back(t.first);
   			for(int id:idx[t.first])
   			{
   				segmax.set(id,emax());
   				segmin.set(id,emin());
   			}
   			L.erase(idx[t.first].back());
   			pos=t.second+1;
   		}
   		cout<<B.size()<<"\n";
   		for(int i=0;i<B.size();i++)cout<<B[i]<<(i+1==B.size()?"\n":" ");
   	}
   }
   ```

   potato167

   ```cpp
   #line 1 "fin.cpp"
   #include <bits/stdc++.h>
   using namespace std;
   using std::cout;
   using std::cin;
   using std::endl;
   using ll=long long;
   using ld=long double;
   const ll ILL=2167167167167167167;
   const int INF=2100000000;
   const int mod=998244353;
   #define rep(i,a,b) for (int i=(int)(a);i<(int)(b);i++)
   #define all(p) p.begin(),p.end()
   template<class T> using _pq = priority_queue<T, vector<T>, greater<T>>;
   template<class T> ll LB(vector<T> &v,T a){return lower_bound(v.begin(),v.end(),a)-v.begin();}
   template<class T> ll UB(vector<T> &v,T a){return upper_bound(v.begin(),v.end(),a)-v.begin();}
   template<class T> bool chmin(T &a,T b){if(a>b){a=b;return 1;}else return 0;}
   template<class T> bool chmax(T &a,T b){if(a<b){a=b;return 1;}else return 0;}
   template<class T> void So(vector<T> &v) {sort(v.begin(),v.end());}
   template<class T> void Sore(vector<T> &v) {sort(v.begin(),v.end(),[](T x,T y){return x>y;});}
   bool yneos(bool a,bool upp=0){if(a){cout<<(upp?"YES\n":"Yes\n");}else{cout<<(upp?"NO\n":"No\n");}return a;}
   template<class T> void vec_out(vector<T> &p,int ty=0){
   if(ty==2){cout<<'{';for(int i=0;i<(int)p.size();i++){if(i){cout<<",";}cout<<'"'<<p[i]<<'"';}cout<<"}\n";}
   else{if(ty==1){cout<<p.size()<<"\n";}for(int i=0;i<(int)(p.size());i++){if(i) cout<<" ";cout<<p[i];}cout<<"\n";}}
   template<class T> T vec_min(vector<T> &a){assert(!a.empty());T ans=a[0];for(auto &x:a) chmin(ans,x);return ans;}
   template<class T> T vec_max(vector<T> &a){assert(!a.empty());T ans=a[0];for(auto &x:a) chmax(ans,x);return ans;}
   template<class T> T vec_sum(vector<T> &a){T ans=T(0);for(auto &x:a) ans+=x;return ans;}
   int pop_count(long long a){int res=0;while(a){res+=(a&1),a>>=1;}return res;}
   template<class T> bool inside(T l,T x,T r){return l<=x&&x<r;}
   
   
   #include <algorithm>
   #include <cassert>
   #include <functional>
   #include <vector>
   
   
   #ifdef _MSC_VER
   #include <intrin.h>
   #endif
   
   #if __cplusplus >= 202002L
   #include <bit>
   #endif
   
   namespace atcoder {
   
   namespace internal {
   
   #if __cplusplus >= 202002L
   
   using std::bit_ceil;
   
   #else
   
   // @return same with std::bit::bit_ceil
   unsigned int bit_ceil(unsigned int n) {
       unsigned int x = 1;
       while (x < (unsigned int)(n)) x *= 2;
       return x;
   }
   
   #endif
   
   // @param n `1 <= n`
   // @return same with std::bit::countr_zero
   int countr_zero(unsigned int n) {
   #ifdef _MSC_VER
       unsigned long index;
       _BitScanForward(&index, n);
       return index;
   #else
       return __builtin_ctz(n);
   #endif
   }
   
   // @param n `1 <= n`
   // @return same with std::bit::countr_zero
   constexpr int countr_zero_constexpr(unsigned int n) {
       int x = 0;
       while (!(n & (1 << x))) x++;
       return x;
   }
   
   }  // namespace internal
   
   }  // namespace atcoder
   
   
   namespace atcoder {
   
   #if __cplusplus >= 201703L
   
   template <class S, auto op, auto e> struct segtree {
       static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                     "op must work as S(S, S)");
       static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                     "e must work as S()");
   
   #else
   
   template <class S, S (*op)(S, S), S (*e)()> struct segtree {
   
   #endif
   
     public:
       segtree() : segtree(0) {}
       explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
       explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
           size = (int)internal::bit_ceil((unsigned int)(_n));
           log = internal::countr_zero((unsigned int)size);
           d = std::vector<S>(2 * size, e());
           for (int i = 0; i < _n; i++) d[size + i] = v[i];
           for (int i = size - 1; i >= 1; i--) {
               update(i);
           }
       }
   
       void set(int p, S x) {
           assert(0 <= p && p < _n);
           p += size;
           d[p] = x;
           for (int i = 1; i <= log; i++) update(p >> i);
       }
   
       S get(int p) const {
           assert(0 <= p && p < _n);
           return d[p + size];
       }
   
       S prod(int l, int r) const {
           assert(0 <= l && l <= r && r <= _n);
           S sml = e(), smr = e();
           l += size;
           r += size;
   
           while (l < r) {
               if (l & 1) sml = op(sml, d[l++]);
               if (r & 1) smr = op(d[--r], smr);
               l >>= 1;
               r >>= 1;
           }
           return op(sml, smr);
       }
   
       S all_prod() const { return d[1]; }
   
       template <bool (*f)(S)> int max_right(int l) const {
           return max_right(l, [](S x) { return f(x); });
       }
       template <class F> int max_right(int l, F f) const {
           assert(0 <= l && l <= _n);
           assert(f(e()));
           if (l == _n) return _n;
           l += size;
           S sm = e();
           do {
               while (l % 2 == 0) l >>= 1;
               if (!f(op(sm, d[l]))) {
                   while (l < size) {
                       l = (2 * l);
                       if (f(op(sm, d[l]))) {
                           sm = op(sm, d[l]);
                           l++;
                       }
                   }
                   return l - size;
               }
               sm = op(sm, d[l]);
               l++;
           } while ((l & -l) != l);
           return _n;
       }
   
       template <bool (*f)(S)> int min_left(int r) const {
           return min_left(r, [](S x) { return f(x); });
       }
       template <class F> int min_left(int r, F f) const {
           assert(0 <= r && r <= _n);
           assert(f(e()));
           if (r == 0) return 0;
           r += size;
           S sm = e();
           do {
               r--;
               while (r > 1 && (r % 2)) r >>= 1;
               if (!f(op(d[r], sm))) {
                   while (r < size) {
                       r = (2 * r + 1);
                       if (f(op(d[r], sm))) {
                           sm = op(d[r], sm);
                           r--;
                       }
                   }
                   return r + 1 - size;
               }
               sm = op(d[r], sm);
           } while ((r & -r) != r);
           return 0;
       }
   
     private:
       int _n, size, log;
       std::vector<S> d;
   
       void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
   };
   
   }  // namespace atcoder
   
   struct F{
       int max_val = -INF;
       int min_val = INF;
       int max_ind = -1;
       int min_ind = -1;
   };
   
   F op(F a, F b){
       if (chmax(a.max_val, b.max_val)){
           a.max_ind = b.max_ind;
       }
       if (chmin(a.min_val, b.min_val)){
           a.min_ind = b.min_ind;
       }
       return a;
   }
   F e(){
       return F{};
   }
   
   void solve();
   // CYAN / FREDERIC
   int main() {
       ios::sync_with_stdio(false);
       cin.tie(nullptr);
       
       int t = 1;
       cin >> t;
       rep(i, 0, t) solve();
   }
   
   void solve(){
       int N;
       cin >> N;
       vector<vector<int>> G(N + 1);
       vector<int> A(N);
       rep(i, 0, N){
           cin >> A[i];
           G[A[i]].push_back(i);
       }
       atcoder::segtree<F, op, e> lim(N), seg(N);
       rep(i, 0, N + 1){
           if (!G[i].empty()){
               for (auto x : G[i]){
                   seg.set(x, {i, i, x, x});
               }
               lim.set(G[i].back(), {1, 1, G[i].back(), G[i].back()});
           }
       }
       int ind_l = 0;
       vector<int> ans;
       rep(rp, 0, N){
           auto tmp = lim.all_prod();
           if (tmp.max_ind == e().max_ind) break;
           // cout << ind_l << " " << tmp.max_ind << endl;
           auto tmp2 = seg.prod(ind_l, tmp.max_ind + 1);
           if (rp & 1){
               ind_l = tmp2.min_ind;
           }
           else ind_l = tmp2.max_ind;
           int v = A[ind_l];
           ans.push_back(v);
           for (auto x : G[v]){
               seg.set(x, e());
           }
           lim.set(G[v].back(), e());
           ind_l++;
       }
       vec_out(ans, 1);
   }
   ```

3. 用 set 找可行区间右端点位置 + set 结合双指针维护区间极值（写起来最容易错的一种），$\mathcal{O}(n\log n)$。

   Rubikun

   ```cpp
   #include <bits/stdc++.h>
   using namespace std;
   typedef long long ll;
   template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return true; } return false; }
   template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return true; } return false; }
   #define all(x) (x).begin(),(x).end()
   #define fi first
   #define se second
   #define mp make_pair
   #define si(x) int(x.size())
   const int mod=998244353,MAX=300005,INF=15<<26;
   
   int main(){
       
       std::ifstream in("text.txt");
       std::cin.rdbuf(in.rdbuf());
       cin.tie(0);
       ios::sync_with_stdio(false);
       
       int Q;cin>>Q;
       while(Q--){
           int N;cin>>N;
           vector<int> A(N),R(N,-1),iru(N);
           vector<vector<int>> po(N);
           for(int i=0;i<N;i++){
               cin>>A[i];A[i]--;
               chmax(R[A[i]],i);
               po[A[i]].push_back(i);
           }
           set<pair<int,int>> SE;
           for(int i=0;i<N;i++){
               if(R[i]!=-1){
                   iru[i]=true;
                   SE.insert(mp(R[i],i));
               }
           }
           
           map<int,int> cand;
           
           vector<int> ans;
           
           int l=0,r=0;
           
           while(1){
               if(si(SE)==0) break;
               
               while(r<=(*SE.begin()).fi){
                   if(iru[A[r]]) cand[A[r]]++;
                   r++;
               }
               
               if(si(ans)%2==0){
                   int x=(*cand.rbegin()).fi;
                   ans.push_back(x);
                   SE.erase(mp(R[x],x));
                   iru[x]=false;
                   int pos=*lower_bound(all(po[x]),l);
                   cand.erase(x);
                   while(l<=pos){
                       if(!cand.count(A[l])){
                           l++;
                           continue;
                       }
                       cand[A[l]]--;
                       if(cand[A[l]]==0) cand.erase(A[l]);
                       l++;
                   }
               }else{
                   int x=(*cand.begin()).fi;
                   ans.push_back(x);
                   SE.erase(mp(R[x],x));
                   iru[x]=false;
                   int pos=*lower_bound(all(po[x]),l);
                   cand.erase(x);
                   while(l<=pos){
                       if(!cand.count(A[l])){
                           l++;
                           continue;
                       }
                       cand[A[l]]--;
                       if(cand[A[l]]==0) cand.erase(A[l]);
                       l++;
                   }
               }
               //cout<<l<<" "<<r<<"\n";
           }
           
           cout<<si(ans)<<"\n";
           for(int a:ans) cout<<a+1<<" ";
           cout<<"\n";
           
       }
   }
   ```

---

## 作者：wujingfey (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF2001D)

感觉能评蓝？反正自己没想出来，看题解受启发才过的。就浅谈一下自己对这道题的理解罢。

## 关于题意

保证两点：

- 每个元素都要刚好出现一次。
- 奇数位最大，偶数位最小。

## 关于弱化版

这道题很恶心的地方时**奇数位尽量大，偶数位尽量小**。我们先考虑弱化版：只求字典序最小。对于一个序列求子序列字典序最小这类问题，可以向单调栈、单调队列的方面考虑。弱化版可以考虑使用单调栈。

我们用一个单调栈存储最终的答案。假设现在要向栈中加入新元素 $p$，且当前栈顶元素叫 $s_{tp}$。分情况讨论：

1. $s_{tp}<p$，那 $p$ 取代了也不会更优，那就让 $p$ 入栈吧。
2. $s_{tp}<p$，那 $s_{tp}$ 换成 $p$ 更优秀，就让 $s_{tp}$ 出栈，实现替换操作。**综上，如果字典序最小，我们维护单调递增栈。**
3. 但根据题目的性质，如果 $s_{tp}$ 是最后一个，那删了栈顶会导致不满足**每个元素都要刚好出现一次**的要求。所以用 $last$ 数组（类似桶）记录每个数最后出现的**位置**。
4. 小小的注意事项：推荐栈里别装元素值，装元素下标。这样代码好些很多。

## 关于正常版

现在我们要**在奇数位最大，在偶数位**最小。怎么魔改呢？

那在奇数位时，我们维护**单调递减栈**，这样栈顶就尽可能大了；在偶数位时维护**单调递增栈**，这样栈顶就尽可能小了。
```
while (tp >= 1){//替换一个 
  if(last[a[s[tp]]] <= i) break;
  //说明后面不会出现了，则break 
  if((tp & 1) == 0){//偶数单调递增 
    if(a[s[tp]]<=a[i]) break;
  }else{//奇数单调递减 
    if(a[s[tp]]>=a[i]) break;
  }
  vis[a[s[tp]]] = 0, tp--; 
}
```

## 关于坑点

因为字典序中，**数位靠前的数字有绝对的统治力**，所以可能出现 $p$ 替换 $s_{tp}$ 不优，但替换 $s_{tp-1}$ 更优秀。这种我们依然要替换。

例如：
```
5
4 1 5 4 1
```
不过不考虑上述情况，$5$ 就不会替换 $1$。但最有解应该是 $5$ 把 $4,1$ 都替换了。

所以我们还要把替换两个的情况写进去。
```
while (tp >= 2) {//替换两个
  if(last[a[s[tp]]] <=i || last[a[s[tp-1]]] <=i) break;
  //同上
  if(((tp-1) & 1) == 0){//偶数单调递增 
    if(a[s[tp-1]]<=a[i]) break;
  }else{
    if(a[s[tp-1]]>=a[i]) break;
  }
  vis[a[s[tp]]] = 0, tp--;
  vis[a[s[tp]]] = 0, tp--;
}
```

~~因为我太弱了~~，两种出栈过程，哪个在前哪个在后的问题困扰了我许久。

我的理解是：**第二种操作的触发条件是 $p$ 替换 $s_{tp}$ 不优时，所以只有第一种操作无法解决时，才会依靠第二种操作补救**。所以第二种写在第一种后面。

## 小结

本题重点：

1. 这类求字典序最大最小子序列的题，可以使用单调数据结构。
2. 这道题存在**一正一反的周期**，要记住在整个周期内考虑替换单调。
3. 一般单调栈内记录 $idx$ 而不是权值（更好写）。
4. 用 $vis,last$ 维护元素是否重复、后面是否还有相同元素。

## CODE:
还有超详细注释。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int n,tp,T;
int a[N],last[N],s[N],vis[N];//last[a[i]]记录a[i]最后一次出现的位置 
void init(){//多测用memset容易暴毙 
	for(int i=1;i<=n;i++){
		last[a[i]]=0;
		vis[a[i]]=0;
		a[i]=0;
	}
	tp=0;
}
signed main() {
//	freopen("t3.in","r",stdin);
//	freopen("t3.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); 
    cin>>T;
    while(T--){
    	cin>>n;
	    for (int i = 1; i <= n; ++i) {
	    	cin>>a[i];
	        last[a[i]] = i;
	    }
	    for (int i = 1; i <= n; ++i){
	        if (vis[a[i]]){
				continue;//不能是[已经在栈中元素] 
			}
			while (tp >= 1){//替换一个 
	        	if(last[a[s[tp]]] <= i) break;
				//说明后面不会出现了，则break 
	        	if((tp & 1) == 0){//偶数单调递增 
	        		if(a[s[tp]]<=a[i]) break;
				}else{//奇数单调递减 
					if(a[s[tp]]>=a[i]) break;
				}
	            vis[a[s[tp]]] = 0, tp--; 
	        }
	        while (tp >= 2) {//替换两个
	        	if(last[a[s[tp]]] <=i || last[a[s[tp-1]]] <=i) break;
				//同上
	            if(((tp-1) & 1) == 0){//偶数单调递增 
	            	if(a[s[tp-1]]<=a[i]) break;
				}else{
					if(a[s[tp-1]]>=a[i]) break;
				}
			    vis[a[s[tp]]] = 0, tp--;
	            vis[a[s[tp]]] = 0, tp--;
	        }
	        s[++tp] = i;
	        vis[a[i]] = 1;
	    }
	    cout<<tp<<'\n';
	    for (int i = 1; i <= tp; ++i) {
	        cout<<a[s[i]]<<" ";
	    }
	    cout<<'\n';
    	init();
	}
    return 0;
}
```

---

## 作者：songge888 (赞：1)

### 题意

给你一个序列 $a$，输出 $a$ 的最长不重复子序列，若存在长度相同的子序列，则输出将奇数位取反后字典序最小的一个。

### 思路

首先子序列的最长长度一定是序列 $a$ 中不同数字的个数。

为了找到符合题意的子序列，则要让奇数位最大，偶数位最小。

那么最值应该在哪一些数里面取呢？

维护一个 `last` 数组，存的是每个元素最后出现的位置，从前往后遍历，如果当前的位置是这个数字最后一次出现并且前面没有选过，那么这个数字是肯定要选的，但是当前不一定要选这个数。

```c++
   a:5  2 1 7 9 7  2 5 5 2
last:9 10 3 6 5 6 10 9 9 10
```

当遍历到 $1$ 时，这是 $1$ 最后一次出现，但可以让它前面的数字先进入子序列，奇数位要尽可能大，所以选前三位中最大的数字 $5$，之后就不能选 $5$ 之前的了，下一次在 $2$ 和  $1$ 中选一个最小值 $1$，注意每次选完之后都要将选的数打一个标记，这样就算之后这个数最后一个出现也不用选了。

可以看出这是在维护一个区间最值，如果暴力枚举时间复杂度是 $O(n)$，总的复杂度就是 $O(n^2)$，但可以用优先队列实现 $O(\log n)$ 维护~~当然也可以用单调队列维护，但这个题可以过  $\log$ 所以就没用~~。

这样总的复杂度就是 $O(n \log n)$，可以通过此题。

注意多测要清空。

### Code

```c++
#include<bits/stdc++.h>
#define int long long
#define bug cout<<"songge888"<<'\n'
using namespace std;
int T,n,a[300010],Last[300010];
int vis[300010];
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
 	cin>>T;
 	while(T--){
	 	cin>>n;
		for(int i=1;i<=n;i++){
		    cin>>a[i];
		}
		for(int i=1;i<=n;i++){
		    Last[i]=1e18;
		}
		for(int i=1;i<=n;i++){
		    Last[a[i]]=i;
		}
		    
		priority_queue<int,vector<int>,greater<int>> q(Last+1,Last+1+n);
		priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q1,q2;
		for(int i=0;i<=n+10;i++){
		    vis[i]=0;
		}
		for(int i=0;i<=q.top();i++){
		    q1.push({-a[i],i});
		    q2.push({a[i],i});
		}
		vector<int> ans;
		int now=0,tot=1;
		while(!q2.empty()){
		    int x,pos;
		    if(tot%2){
		    	x=q1.top().first;
		    	pos=q1.top().second; 
			}
			else{
				x=q2.top().first;
		    	pos=q2.top().second;
			}
		        
		    if(tot%2){
		        q1.pop();
		        x*=-1;
		    }
			else{
		        q2.pop();
		    }
		        
		    ans.push_back(x);
		    now=pos+1;
		    vis[x]=1;
		    tot++;
		    while(!q.empty()&&q.top()!=1e18&&vis[a[q.top()]]){
		        int j=q.top();
		        q.pop();
		        for(int k=j+1;k<=min(q.top(),n);k++){
		            q1.push({-a[k],k});
		            q2.push({a[k],k});
		        }
		    }
		    while(!q1.empty()&&(vis[-q1.top().first]||q1.top().second<now)){
		        q1.pop();
		    }
		    while(!q2.empty()&&(vis[q2.top().first]||q2.top().second<now)){
		        q2.pop();
		    }
		}
		cout<<ans.size()<<'\n';
		for(auto x:ans){
		    cout<<x<<' ';
		}
		cout<<'\n';
	}
	
    return 0;
}
```
[提交记录](https://codeforces.com/contest/2001/submission/297769938)

---

## 作者：lwwwb_555 (赞：1)

提供一种用线段树维护，时间复杂度为 $O(n\log n)$ 的做法。

首先，我们先倒着把序列扫一遍，对于每个位置 $i$ 记录从 $i$ 到 $n$ 有多少个不同的数，我们还可以顺便记录一下每个数最晚出现的位置。

然后我们将序列顺着扫，一个数要插入最终的答案之中而不是原来答案的后一位必然要满足如下的条件：

对于是奇数的位置，需要满足的条件有：

1. 这个数一定不在原来的答案中。

2. 这个数比原来在这个位置的数要大。

3. 这个数放进去之后，后面还有足够的数放。

对于是偶数的位置，需要满足的条件有：

1. 这个数一定不在原来的答案中。

2. 这个数比原来在这个位置的数要小。

3. 这个数放进去之后，后面还有足够的数放。

第 $3$ 个是什么意思呢？

比如第一个样例：```3 1 2 3```。

扫到 $2$ 的时候，答案是：```3 1```。

如果只看前两个限制条件，那么 $2$ 是能够取代 $1$ 放进原来 $1$ 的位置的，但是我们发现把 $2$ 放到那里之后，整个答案就只有 $2$ 个数，不可能再放进第 $3$ 个数进去了。所以我们在放一个数的时候，要考虑它后面有没有足够的数去放满。

再直观一点，其实每个数的第三个条件就是它及它以后有多少个数它们互不相同且这些数没有出现在之前的答案当中。

我们发现前两个条件都很好维护，但第 $3$ 个可能会由于现在答案中的数不同而导致每个数的三条件在变化，所以我们可以考虑在答案中插入一个数之后会对每个数的 $3$ 条件造成什么变化。

假设我们现在要把 $i$ 插入答案当中，设它在序列当中最后一次出现的位置为 $pos$ 那么从 $1$ 到 $pos-1$ 的 $3$ 条件都会减少 $1$，这明显是一个区间加减的操作，所以我们用线段树来维护就行了。

~~代码有点丑，轻点喷~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
int qq,n,a[300005],tong[300005],num[300005],q[300005],t=0,h=1,b[300005],book[300005];
int read(){
	int res=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		res=(res<<3)+(res<<1)+c-'0';
		c=getchar();
	}
	return res*f;
}
struct node{
	int ll,rr;
	long long w,tag;
}tt[1200005];
void build(int p,int l,int r){
	tt[p].ll=l,tt[p].rr=r,tt[p].w=0,tt[p].tag=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(p*2,l,mid),build(p*2+1,mid+1,r); 
}
void pushdown(int p){
	if(tt[p].ll==tt[p].rr || !tt[p].tag) return;
	int ls=p*2,rs=p*2+1;
	tt[ls].w+=(long long)(tt[ls].rr-tt[ls].ll+1)*tt[p].tag,tt[ls].tag+=tt[p].tag;
	tt[rs].w+=(long long)(tt[rs].rr-tt[rs].ll+1)*tt[p].tag,tt[rs].tag+=tt[p].tag;
	tt[p].tag=0;
	return;
}
void add(int p,int l,int r,int k){
	if(tt[p].ll>=l && tt[p].rr<=r){
		tt[p].w+=(long long)(tt[p].ll-tt[p].rr+1)*k;
		tt[p].tag+=k;
		return;
	}
	pushdown(p);
	int mid=(tt[p].ll+tt[p].rr)>>1;
	if(l<=mid) add(p*2,l,r,k);
	if(r>mid) add(p*2+1,l,r,k);
	tt[p].w=tt[p*2].w+tt[p*2+1].w;
}
int query(int p,int l){
	if(tt[p].ll==tt[p].rr) return tt[p].w;
	pushdown(p);
	int mid=(tt[p].ll+tt[p].rr)>>1;
	if(l<=mid) return query(p*2,l);
	return query(p*2+1,l);
}//线段树的基本操作
int main(){
	qq=read();
	while(qq--){
		t=0,h=1;
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=n;i>=1;i--){
			num[i]=num[i+1];
			if(!tong[a[i]]) num[i]++,b[a[i]]=i;
			tong[a[i]]++;
		}
		build(1,1,n);
		printf("%d\n",num[1]);
		for(int i=1;i<=n;i++){
			if(book[a[i]]) continue; //如果这个数已经在答案中了，那么直接continue
			bool flag1=0,flag2=0;
			int p=t+1;
			int pp=1e9+10;
			for(int j=t;j>=h;j--){
				if(flag1 && flag2) break;
				if(j%2==1){
					add(1,1,b[a[q[j]]],-1);//先把这个位置对后面造成的影响先去掉，因为如果i能替换这个位置，那么这个位置就不能对i造成影响了
					pp=min(pp,j);
					if(flag1) continue;
					if(a[i]>a[q[j]] && num[i]-query(1,i)>=num[1]-j+1) p=j;
					else flag1=1;
				}else{
					add(1,1,b[a[q[j]]],-1);
					pp=min(pp,j);
					if(flag2) continue;
					if(a[i]<a[q[j]] && num[i]-query(1,i)>=num[1]-j+1) p=j;
					else flag2=1;
				}
			}
			for(int j=p;j<=t;j++) book[a[q[j]]]=0;
			for(int j=pp;j<p;j++) add(1,1,b[a[q[j]]],1);//把刚刚去掉了影响，但现在仍然在答案中的数的影响给加回来
			q[p]=i;
			book[a[i]]=1;
			add(1,1,b[a[i]],1);
			t=p;
		}//用q来维护从1到i的答案
		for(int i=1;i<=num[1];i++) printf("%d ",a[q[i]]);
		for(int i=1;i<=n;i++) num[i]=0,tong[a[i]]--,b[a[i]]=0,book[a[i]]=0;
		for(int i=h;i<=t;i++) q[i]=0;//多测不清空，爆零两行泪
		printf("\n");
	}
	return 0;
}
```

---

## 作者：JiuZhE66666 (赞：1)

提供一种优先队列的做法。

首先，最长序列的长度一定等于数组中有多少不同的数，我们设其为 $m$。

因此，我们选的第一个数，一定是在所有**选了它之后还能再选 $m-1$ 个不同数的数**里面，选一个最小的数。

记该数的位置为 $a$ ，其在数组中出现的最后一个位置为 $b$ ，设 $suf[i]$ 代表从这个数开始选，能选多少不同的数。

则有 $(a,b)$ 内所有的 $suf[i]$ 都减一，因为对于 $(a,b)$ 内的数来说，位置 $b$ 处数是作为一个新的不同数存在的，但是又不能选（因为已经选过了）。

选第二个数和选第一个数的道理是一样的，只不过变成选一个最大的数。


# code
```
#include<bits/stdc++.h>
using namespace std;

struct node1
{
    int val,index;
    bool operator<(const node1 &b) const
    {
        if(b.val!=val)return b.val<val;
        else return b.index<index;
    }
};

struct node2
{
    int val,index;
    bool operator<(const node2 &b) const
    {
        if(b.val!=val)return b.val>val;
        else return b.index<index;
    }
};

int a[300005];
void solve()
{
    int n;
    cin>>n;

    priority_queue<node1> qmin;
    priority_queue<node2> qmax;

    for(int i=1;i<=n;i++) cin>>a[i];

    map<int,int> rec;
    stack<int> split;
    for(int i=n;i>=1;i--)
    {
        if(!rec[a[i]])
        {
            split.push(i);
            rec[a[i]]=i;
        }
    }

    int it=1;
    int r=split.top();
    split.pop();
    int op=1;
    map<int,int> vis;
    int l=1;
    vector<int> ans;
    int num=rec.size();

    set<int> finish;
    while(num)
    {
        while(it<=r)
        {
            qmax.push({a[it],it});
            qmin.push({a[it],it});
            it++;
        }

        while(!qmax.empty() && (vis[qmax.top().val]||qmax.top().index<l)) qmax.pop();
        while(!qmin.empty() && (vis[qmin.top().val]||qmin.top().index<l)) qmin.pop();

        if(op)
        {
            if(!qmax.empty())
            {
                auto [val,index]=qmax.top();
                l=index+1;
                vis[val]=1;
                ans.push_back(val);
                finish.insert(rec[val]);
            }
        }
        else
        {
            while(!qmin.empty() && vis[qmin.top().val]) qmin.pop();
            if(!qmin.empty())
            {
                auto [val,index]=qmin.top();
                l=index+1;
                vis[val]=1;
                ans.push_back(val);
                finish.insert(rec[val]);
            }
        }


        while(finish.count(r) && !split.empty())
        {
            r=split.top();
            split.pop();
        }

        num--;
        op^=1;

    }
    cout<<ans.size()<<'\n';
    for(auto it: ans )cout<<it<<' ';
    cout<<"\n\n";
}
signed main()
{
    //ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int TT=1;
    cin>>TT;
    while(TT--) solve();
    return 0;
}


```

---

## 作者：Kevin911 (赞：1)

数据结构题，感觉我用两个堆和一个线段树有点麻烦了。

## 思路

首先最大长度显然，就是不同的数的个数。然后用桶把每个数的出现位置存下来，奇数位尽可能大的放，偶数位尽可能小的放。贪心考虑什么情况下这个位置可以放这个数，只有当剩下所有没有放的数的最大位置都大于当前位置才可以。

所以实现的时候一堆从前往后走（类似快实现双指针），把所有位置小于当前位置的指针都往后移，另一个堆维护最小值剩下数值最大位置，线段树求最小或最大的可以放的数，总时间复杂度 $O(n\log n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn=3e5+10;
int n,cnt;
int a[maxn],to[maxn];
bool flag[maxn];
vector<int> b[maxn];
priority_queue<pii,vector<pii>,greater<pii> > q1,q2;
struct tree
{
	int l,r,mn;
}tr[maxn<<2];
void push_up(int id)
{
	tr[id].mn=min(tr[id*2].mn,tr[id*2+1].mn);
}
void build(int id,int l,int r)
{
	tr[id].l=l,tr[id].r=r,tr[id].mn=1e9;
	if(l==r) return;
	int mid=(l+r)/2;
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
	push_up(id);
}
void update(int id,int x,int c)
{
	if(tr[id].l==tr[id].r)
	{
		tr[id].mn=c;
		return;
	}
	int mid=(tr[id].l+tr[id].r)/2;
	if(x<=mid) update(id*2,x,c);
	else update(id*2+1,x,c);
	push_up(id);
}
int query1(int id,int x)
{
	if(tr[id].l==tr[id].r) return tr[id].l;
	int mid=(tr[id].l+tr[id].r)/2;
	if(tr[id*2+1].mn<=x) return query1(id*2+1,x);
	else return query1(id*2,x);
}
int query2(int id,int x)
{
	if(tr[id].l==tr[id].r) return tr[id].l;
	int mid=(tr[id].l+tr[id].r)/2;
	if(tr[id*2].mn<=x) return query2(id*2,x);
	else return query2(id*2+1,x);
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cnt=0;
		while(!q1.empty()) q1.pop();
		while(!q2.empty()) q2.pop();
		cin>>n;
		build(1,1,n);
		for(int i=1;i<=n;i++) b[i].clear(),to[i]=flag[i]=0;
		for(int i=1;i<=n;i++) cin>>a[i],b[a[i]].push_back(i);
		for(int i=1;i<=n;i++)
			if(b[i].size())
			{
				cnt++;
				update(1,i,b[i][0]);
				q1.push({b[i][0],i}),q2.push({b[i][b[i].size()-1],i});
				for(int j=0;j<b[i].size()-1;j++) to[b[i][j]]=b[i][j+1];
			}
		cout<<cnt<<endl;
		int num=1;
		while(!q1.empty())
		{
			int x=q2.top().first,r=0;
			if(num%2) r=query1(1,x);
			else r=query2(1,x);
			cout<<r<<' ';
			flag[r]=1;
			update(1,r,(int)1e9);
			while(!q1.empty()&&q1.top().second!=r)
			{
				int xx=q1.top().first,yy=q1.top().second;
				q1.pop();
				update(1,yy,to[xx]);
				q1.push({to[xx],yy});
			}
			q1.pop();
			if(q2.top().second==r)
			{
				q2.pop();
				while(!q2.empty()&&flag[q2.top().second]) q2.pop();
			}
			num^=1;
		}
		cout<<endl;
	}
}
```

---

## 作者：wfc284 (赞：0)

首先，这个子序列的最大长度是可以确定的，就是 $a$ 中不同元素种类数。  
在此基础上，我们要最大化奇数位，最小化偶数位。

如果不考虑长度的限制，我们就每次取能取的最大（小）值，然后更新范围。所谓能取，即每取完一个值，它前面的值就不能取了。  
这个过程可以用两个 heap 打打标记实现。

现在有长度的限制了，无非就是加了一个限制：
- 每次取元素时，要保证它后面有所有没取过的元素。

【后面所有没取过】，这个好像用 set 很好维护。  
具体地，我们用 set 维护每种元素最后面下标的位置，取一个元素就删一个。取元素的时候，保证其下标小于等于 set 中最小值即可。  
刚才的两个 heap 的思路可以沿用，但是每次只能加入 position 小于等于当前 set 中最小值的元素。

时间复杂度 $O(n \log n)$，还是有些细节的。  
[submission.](https://codeforces.com/problemset/submission/2001/305942503)

---

## 作者：Na2PtCl6 (赞：0)

首先我们知道，答案肯定是把原数组去重后再重排的结果。

令一个数 $x$ 在原序列中最靠后的位置为 $last_x$，则答案是一个序列加上 $last$ 的一个后缀。所以考虑一种做法，先把 $last$ 求出来，然后从前往后在可以选数的区间里找比 $last$ 里面的数更优的数，找到了就在 $last$ 里面删掉这个数的位置。所谓可以选数的区间，就是从前面已经选好的数的最靠后的位置，到下一个 $last$ 里面的位置的一个左开右闭的区间。 

总之就是从前往后，把 $last$ 里面的出现的数换成更优的顺序。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=300004;
int t,n,a[maxn],cnt[maxn],last[maxn];
set< int > s;
vector< int > val[maxn];
struct item{ int mx,mn,mxpos,mnpos;}tree[maxn<<2];

item operator + (item &a,item &b){
	item ret;
	if(a.mn<=b.mn)
		ret.mnpos=a.mnpos;
	else
		ret.mnpos=b.mnpos;
	ret.mn=min(a.mn,b.mn);
	if(a.mx>=b.mx)
		ret.mxpos=a.mxpos;
	else
		ret.mxpos=b.mxpos;		
	ret.mx=max(a.mx,b.mx);
	return ret;
}

void build(int l,int r,int ver){
	int mid=(l+r)>>1,lver=ver<<1,rver=ver<<1|1;
	if(l==r){
		tree[ver].mn=tree[ver].mx=a[l];
		tree[ver].mnpos=tree[ver].mxpos=l;
		return ;
	}
	build(l,mid,lver),build(mid+1,r,rver);
	tree[ver]=tree[lver]+tree[rver];
}

void del(int l,int r,int ver,int p){
	if(l==r){
		tree[ver]={0,0x7fffffff,0,0};
		return ;
	}
	int mid=(l+r)>>1,lver=ver<<1,rver=ver<<1|1;
	if(p<=mid)
		del(l,mid,lver,p);
	if(p>mid)
		del(mid+1,r,rver,p);
	tree[ver]=tree[lver]+tree[rver];
}

item query(int l,int r,int ver,int start,int end){
	if(start<=l&&r<=end)
		return tree[ver];
	int mid=(l+r)>>1,lver=ver<<1,rver=ver<<1|1;
	item lret,rret;lret=rret={0,0x7fffffff,0,0};
	if(start<=mid)
		lret=query(l,mid,lver,start,end);
	if(end>mid)
		rret=query(mid+1,r,rver,start,end);
	return lret+rret;
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			s.insert(a[i]);
			val[a[i]].push_back(i);
		}
		build(1,n,1);
		int sz=s.size();
		s.clear();
		for(int i=n;i>=1;i--){
			if(cnt[a[i]]==0){
				last[a[i]]=i;
				s.insert(i);
			}
			++cnt[a[i]];
		}
		int l=0;vector< int > res;
		for(int i=1;i<=sz;i++){
			int r=*s.begin();
			if(l>=r)
				break;
			auto q=query(1,n,1,l+1,r);
			if(i&1){
				if(q.mx>=a[r]){
					l=q.mxpos;
					s.erase(last[q.mx]);
					for(int j:val[q.mx])
						del(1,n,1,j);
					res.push_back(q.mxpos);
				}
			}
			else{
				if(q.mn<=a[r]){
					l=q.mnpos;
					s.erase(last[q.mn]);
					for(int j:val[q.mn])
						del(1,n,1,j);
					res.push_back(q.mnpos);
				}
			}
		}
		printf("%d\n",sz);
		for(int i:res)
			printf("%d ",a[i]);
		for(int i:s)
			printf("%d ",a[i]);
		puts("");
		s.clear();
		for(int i=1;i<=n;i++){
			val[i].clear();
			cnt[i]=last[i]=0;
		}
		for(int i=1;i<=(n<<2);i++)
			tree[i]={0,0x7fffffff,0,0};
	}
	return 0;
}
```

---

## 作者：qtanglani (赞：0)

$a$ 数组为输入数组

为了方便，先倒序遍历，将每个数字所出现的位置存下来，使用`vector g[N]`来存储，`g[x][0]`便是 $x$ 这个数最后一次出现的位置，为方便描述，我们定义数组 $pos$,来存储每个数最后一次出现的位置，设 $pos$ 数组的长度是 $cnt$，答案数组的长度同样也是 $cnt$。

我们让 $pos$ 数组单调递增，现在我们考虑第一个数可以选择的范围，由于答案是让每个数都恰好出现一次，所以第一个数可以选择的范围便是 $[1,pos_{1}]$，若选择的数字 $x$，位置为 $l$，$x$ 恰好是 $a_{pos_{1}}$，那么第二个数可选择的范围便扩展到了 $[l+1,pos_{2}]$，若 $x$ 不为 $a_{pos_{1}}$，则第二个数的范围是 $[l+1,pos_{1}]$，也就是说只要 $a_{pos_{1}}$ 还没有被选，那么范围就得不到扩展。

我们将 $a_{pos_{i}}$ 能选择的范围看作一条线段，第 $i$ 条的范围便是 $[1,pos_{i}]$。我们将每一条线段所管辖的区间 $+1$。举个例子。

$$
pos=\left \{ 2,4,5,7\right \} 
$$

则对应的数列便是

$$
4,4,3,3,2,1,1
$$

答案数组的第 $i$ 个数可以在数列的数等于 $cnt-i+1$ 的范围里选择，在上述数列中，第一个数只能在 $[1,2]$ 中选择。

每当选择完了一个数 $x$，我们便将他对应的线段删去，也就是区间 $[1,g[x][0]]-1$，并遍历这个数的每个位置，将它修改为合适的值（下面再说），再进行下一轮的选数。

现在我们考虑如何使得题目要求中字典序最小。假设我们现在可以选择的区间是 $[l,pos_{i}]$（可以证明任意一个可选择的区间的右端点都是 $pos$ 数组中的一个数），当选到第奇数个数时，我们要找的是区间最大值，反之一样。而为了能够多选，我们每次都要选择最靠左的那个数。若当前是第 $j-1$ 次查找，选择的数 $x$，位置为 $l$，则第 $j$ 次的范围是 $[l+1,最后一个为cnt-j+1的位置]$。

以上操作都能用线段树简单实现，具体而言。

- 维护数列里的最大值最小值以及他们最靠左的位置。
- 维护上述区间加减的序列。
- 每次查找完一个数 $x$，首先要 $[1,g[x]。[0]]-1$，其次将每个位置的最大值设为极小值，最小值设为极大值，目的是取消这个数对以后选择的影响。
- 最后查找右端点位置时，使用线段树上二分便可以实现。

每个位置只会进行一次赋值操作，区间修改是 $n\log n$ 次，查询也是 $n\log n$ 次，总时间复杂度便是高贵的 $O(n\log n)$。

```cpp
#include<iostream>
#include<vector>
using namespace std;
const int N=300010;
vector<int> g[N];
int n,a[N];
int cnt;
struct info
{
    int maxx,minn;
    int pos_x,pos_n;
    int sum;
    int minnn,maxxx;
};
struct node
{
    int tag;
    info v;
}tr[N*4];
info merge(info a,info b)
{
    info c;
    c.maxx=max(a.maxx,b.maxx);
    c.minn=min(a.minn,b.minn);
    c.minnn=min(a.minnn,b.minnn);
    c.maxxx=max(a.maxxx,b.maxxx);
    if(a.maxx==c.maxx)
        c.pos_x=a.pos_x;
    else
        c.pos_x=b.pos_x;
    if(a.minn==c.minn)
        c.pos_n=a.pos_n;
    else
        c.pos_n=b.pos_n;
    c.sum=a.sum+b.sum;
    return c;
}
void update(int x)
{
    tr[x].v=merge(tr[x*2].v,tr[x*2+1].v);
}
void built(int x,int l,int r)
{
    tr[x].tag=0;
    if(l==r)
    {
        tr[x].v.maxx=a[l];
        tr[x].v.minn=a[l];
        tr[x].v.sum=a[l];
        tr[x].v.pos_x=l;
        tr[x].v.pos_n=l;
        tr[x].v.minnn=0;
        tr[x].v.maxxx=0;
        return;
    }
    int mid=(l+r)/2;
    built(x*2,l,mid);
    built(x*2+1,mid+1,r);
    update(x);
}
void maketag(int x,int k,int L,int R)
{
    tr[x].tag+=k;
    tr[x].v.sum+=(R-L+1)*k;
    tr[x].v.minnn+=k;
    tr[x].v.maxxx+=k;
}
void pushdown(int x,int L,int R)
{
    if(L==R)
        return;
    int mid=(L+R)/2;
    maketag(x*2,tr[x].tag,L,mid);
    maketag(x*2+1,tr[x].tag,mid+1,R);
    tr[x].tag=0;
}
void modify1(int x,int l,int r,int k,int L,int R)
{
    pushdown(x,L,R);
    if(l==L&&r==R)
    {
        maketag(x,k,L,R);
        return;
    }
    int mid=(L+R)/2;
    if(r<=mid)
        modify1(x*2,l,r,k,L,mid);
    else if(l>=mid+1)
        modify1(x*2+1,l,r,k,mid+1,R);
    else
    {
        modify1(x*2,l,mid,k,L,mid);
        modify1(x*2+1,mid+1,r,k,mid+1,R);
    }
    update(x);
}
void modify2(int x,int pos,int L,int R)
{
    pushdown(x,L,R);
    if(L==R)
    {
        tr[x].v.maxx=-1e9;
        tr[x].v.minn=1e9;
        return;
    }
    int mid=(L+R)/2;
    if(pos<=mid)
        modify2(x*2,pos,L,mid);
    else
        modify2(x*2+1,pos,mid+1,R);
    update(x);
}
int find2(int x,int k,int L,int R)
{
    pushdown(x,L,R);
    if(L==R)
        return L;
    int mid=(L+R)/2;
    if(tr[x*2+1].v.maxxx==k)
        return find2(x*2+1,k,mid+1,R);
    else
        return find2(x*2,k,L,mid);
    return -1;
}
info find1(int x,int l,int r,int L,int R)
{
    pushdown(x,L,R);
    if(l==L&&r==R)
        return tr[x].v;
    int mid=(L+R)/2;
    if(r<=mid)
        return find1(x*2,l,r,L,mid);
    else if(l>=mid+1)
        return find1(x*2+1,l,r,mid+1,R);
    return merge(find1(x*2,l,mid,L,mid),find1(x*2+1,mid+1,r,mid+1,R));
}
void solve()
{
    cnt=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        g[i].clear();
    }
    built(1,1,n);
    for(int i=n;i>=1;i--)
    {
        if(!g[a[i]].size())
        {
            modify1(1,1,i,1,1,n);
            cnt++;
        }
        g[a[i]].push_back(i);
    }
    int l=1,r;
    cout<<cnt<<'\n';
    for(int i=cnt;i>=1;i--)
    {
        r=find2(1,i,1,n);
        int val;
        info shabi=find1(1,l,r,1,n);
        if((cnt-i+1)%2==1)
        {
            val=shabi.maxx;
            cout<<val<<" ";
            l=shabi.pos_x+1;
        }
        else
        {
            val=shabi.minn;
            cout<<val<<" ";
            l=shabi.pos_n+1;
        }
        for(int i=0;i<int(g[val].size());i++)
            modify2(1,g[val][i],1,n);
        modify1(1,1,g[val][0],-1,1,n);
    }
    cout<<'\n';
}
int main()
{
    int T;
    cin>>T;
    while(T--)
        solve();
}
/*
1
10
5 2 1 7 9 7 2 5 5 2

5 5 5 4 4 3 2 2 2 1

4 4 4 3 3 2 1 1 1 1

3 3 3 3 3 2 1 1 1 1
*/
```

---

