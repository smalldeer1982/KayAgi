# Pairs of Segments

## 题目描述

Two segments $ [l_1, r_1] $ and $ [l_2, r_2] $ intersect if there exists at least one $ x $ such that $ l_1 \le x \le r_1 $ and $ l_2 \le x \le r_2 $ .

An array of segments $ [[l_1, r_1], [l_2, r_2], \dots, [l_k, r_k]] $ is called beautiful if $ k $ is even, and is possible to split the elements of this array into $ \frac{k}{2} $ pairs in such a way that:

- every element of the array belongs to exactly one of the pairs;
- segments in each pair intersect with each other;
- segments in different pairs do not intersect.

For example, the array $ [[2, 4], [9, 12], [2, 4], [7, 7], [10, 13], [6, 8]] $ is beautiful, since it is possible to form $ 3 $ pairs as follows:

- the first element of the array (segment $ [2, 4] $ ) and the third element of the array (segment $ [2, 4] $ );
- the second element of the array (segment $ [9, 12] $ ) and the fifth element of the array (segment $ [10, 13] $ );
- the fourth element of the array (segment $ [7, 7] $ ) and the sixth element of the array (segment $ [6, 8] $ ).

As you can see, the segments in each pair intersect, and no segments from different pairs intersect.

You are given an array of $ n $ segments $ [[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]] $ . You have to remove the minimum possible number of elements from this array so that the resulting array is beautiful.

## 说明/提示

In the first test case of the example, it is enough to delete the $ 5 $ -th element of the array of segments. Then you get the array $ [[2, 4], [9, 12], [2, 4], [7, 7], [10, 13], [6, 8]] $ , which is beautiful.

In the second test case of the example, you can delete the $ 1 $ -st, $ 3 $ -rd and $ 4 $ -th element of the array. Then you get the array $ [[2, 8], [5, 6]] $ , which is beautiful.

In the third test case of the example, you have to delete the whole array.

## 样例 #1

### 输入

```
3
7
2 4
9 12
2 4
7 7
4 8
10 13
6 8
5
2 2
2 8
0 10
1 2
5 6
4
1 1
2 2
3 3
4 4```

### 输出

```
1
3
4```

# 题解

## 作者：inc1ude_c (赞：9)

这里讲讲简单的官方做法。

枚举两个数 $i,j(1\le i\le n,i<j\le n)$，如果线段 $i$ 与线段 $j$ 有交集，那么计算它们的并集。

这样操作后，这些并集就代表答案中可能的一对，由于对与对之间不能有交集，又要舍弃尽量少的线段，所以我们考虑在这个新集合上算最大不相交区间数量。

这是一个极为经典的问题，核心思路就是按右端点排序后再贪心，具体做法可以参考[这篇博客](https://blog.csdn.net/yl_puyu/article/details/109681226)，这里不再赘述。设数量为 $cnt$，因为每一条新线段都由两条原线段组成，所以我们实际上选择了 $cnt\times 2$ 条原线段，也就是舍弃了 $n-cnt\times 2$ 条原线段。

复杂度 $O(n^2\log n)$。

---

## 作者：一扶苏一 (赞：5)

# 【DP】【CF1841D】Pairs of Segments

## Description
给定 $n$ 个线段 $[l_i, r_i]$，你需要从中删除尽可能少的线段，满足：

- 剩余线段数量是偶数。
- 剩余的线段可以两两配对，满足：
  + 属于同一对的两个线段有交；
  + 任意不属于同一对的两个线段均无交。
  
请你求出最少删除多少个线段才能满足要求。

多组数据，$n$ 之和不超过 $2000$，$0 \leq l_i \leq r_i \leq 10^9$。

## Analysis

刚补完山东省赛的 F 就碰到了它，感觉很亲切。

首先删最少的就是选最多的。我们把线段按照右端点排序，考虑枚举一个被选的 pair 中右端点更靠右的那个线段。

设 $f_i$ 表示考虑了前 $i$ 条线段，且第 $i$ 条线段必选，此时最多可以选几条线段。

考虑枚举哪条线段 $j$ 可以和第 $i$ 条线段配对，则需要满足的条件是 $j < i$ 且 $r_j \geq l_i$。此时 $[\min(l_i, l_j), r_i]$ 这段区间已经全部被 $(i, j)$ 这个 pair 覆盖，所以 $j$ 再往前的的 pair 的线段右端点必须小于 $\min(l_i, l_j)$。因为线段是按右端点排序的，所以满足右端点小于 $\min(l_i, l_j)$ 的线段 $k$ 是序列的一个前缀。设 $p_{i,j}$ 表示满足上述约束的最大的 $k$，则 $p_{i,j}$ 可以在序列上简单的二分得到。转移显然：

$$f_{i} = \max\limits_{j = 1}^{i - 1} [r_j \geq l_i]  \times(\max_{k = 1}^{p_{i,j}} f_k + 2)$$

式中 $[]$ 是艾弗森括号。

注意到 $\max_{k = 1}^{p_{i,j}}$ 是个前缀最大值。设 $\mathrm{premax}_{i} = \max\limits_{j = 1}^i f_j$，则

$$f_{i} = \max\limits_{j = 1}^{i - 1} [r_j \geq l_i]  \times (\mathrm{premax}_{p_{i,j}} + 2)$$

这样，共 $O(n)$ 个状态，转移有 $O(n)$ 的情况，每次用 $O(\log n)$ 的时间二分出 $p_{i,j}$，总时间复杂度 $O(n^2 \log n)$。

## Code

注意代码中 pair 的 first 元素是右端点，second 元素是左端点。

```cpp
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

int T;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  auto read = []() { int x; std::cin >> x; return x; };
  for (std::cin >> T; T; --T) {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a(n);
    for (auto &[r, l] : a) {
      std::cin >> l >> r;
    }
    std::sort(a.begin(), a.end());
    std::vector<int> f(n), premax(n);
    int ans = 0;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) if (a[j].first >= a[i].second) {
        auto pos = std::lower_bound(a.begin(), a.end(), std::make_pair(std::min(a[j].second, a[i].second), -1));
        if (pos == a.begin()) {
          f[i] = std::max(f[i], 2);
        } else {
          int k = pos - a.begin() - 1;
          f[i] = std::max(premax[k] + 2, f[i]);
        }
      }
      premax[i] = std::max(premax[i - 1], f[i]);
      ans = std::max(f[i], ans);
    }
    std::cout << n - ans << '\n';
  }
}
```

---

## 作者：shipeiqian (赞：3)

# CF1841D 题解

## 题意

给定 $n$ 个线段 $[l_i, r_i]$，你需要从中删除尽可能少的线段，满足：

- 剩余线段数量是偶数。
- 剩余的线段可以两两配对，满足：
    + 属于同一对的两个线段有交；
    + 任意不属于同一对的两个线段均无交。

求出最少删除多少个线段才能满足要求。

## 思路

根据要求可以发现，如果最终满足要求的 $2k$ 条线段里属于同一对分别的合并成一条线段，那么合并后的 $k$ 条线段必然不相交，因此，可将所有可能合并的至多 $n^2$ 条线段合并出来，然后找出这些线段中，最多的不相交的一些即是最后留下的线段。

## 做法

首先合并线段。如果对于线段 $i$ 和 $j$，有$\min(r_i,r_j)\geq\max(l_i,l_j)$，那么这两条线段就可以合并。合并的时间复杂度为 $O(n^2)$。

然后找出不相交的线段。考虑到要最大化这个结果，所以要最小化每条线段的右端点，让更多线段得以排在后面。所以可以先按右端点排序。

## Code

```cpp
#include <bits/stdc++.h>
#define de "debug"
using namespace std;
typedef long long ll;
struct node{
    int l,r;
}a[100005];
int n;
void solve(){
    cin >>n;
    for(int i=1;i<=n;i++)cin >>a[i].l >>a[i].r;
    vector<node>v;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(min(a[i].r,a[j].r)>=max(a[i].l,a[j].l)){
                v.push_back({min(a[i].l,a[j].l),max(a[i].r,a[j].r)});//合并线段
            }
        }
    }
    sort(v.begin(),v.end(),[](node x,node y){return x.r<y.r;});
    int ans=0,lst=-1;//ans 是保留的线段
    for(auto x:v){
        if(x.l>lst){
            ans+=2;
            lst=x.r;
        }
    }
    cout <<n-ans <<"\n";
}
int main(){
    //ios::sync_with_stdio(false);
    int T=1;
    cin >>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：buaa_czx (赞：3)


## 题目大意
有 $n$ 条线段，一对线段由两个相交线段组成。

称某 $k$ 条线段为漂亮的线段组，如果 $k$ 条线段满足:
- $k$ 是偶数
- 可以分成 $\frac k 2$ 对线段，且不同对线段中的线段各不相交

问最少删去多少条线段可以使这 $n$ 条线段是漂亮的。

## 思路

先 $O(n^2)$ 的处理出所有可能出现的线段对，每个线段对可以合成一条新的线段。在这些新线段中选取一些互不相交的线段，互不相交的线段数量即为漂亮线段组中线段数的一半。

问题即转化为经典的**选择不相交区间问题**：给出一堆区间，要求选择尽量多的区间，使得这些区间互不相交，求可选取的区间的最大数量。这里端点相同也算有重复。

贪心的解决这类问题，将这些线段右端点从小到大排序，每次选择与前面选择的线段不相交的线段。贪心正确性显然。

## 代码
```cpp
struct sgm {
    int l, r;
};
bool cmp(sgm x, sgm y) {
    return x.r < y.r;
    //    return x.l > y.l;
}
bool is_pair(sgm x, sgm y) {
    return (x.l >= y.l && x.l <= y.r) || (x.r >= y.l && x.r <= y.r);
}
sgm a[2010], u[4000010];
int n, res, tot;
void solve() {
    tot = 0;
    cin >> n;
    rep(i, 0, n - 1) cin >> a[i].l >> a[i].r;
    rep(i, 0, n - 1) rep(j, i + 1, n - 1) {
        if (is_pair(a[i], a[j]) || is_pair(a[j], a[i]))
            u[tot++] = sgm{min(a[i].l, a[j].l), max(a[i].r, a[j].r)};
    }
    if (tot == 0) {
        cout << n << endl;
        return;
    }
    sort(u, u + tot, cmp);
    sgm tmp = u[0];
    res = 1;
    rep(i, 1, tot - 1) {
        if (!is_pair(tmp, u[i]) && !is_pair(u[i], tmp)) {
            res++;
            tmp = u[i];
        }
    }
    cout << n - 2 * res << endl;
}
```

---

## 作者：qiuzijin2026 (赞：2)

# Pairs of Segments

[题面](https://www.luogu.com.cn/problem/CF1841D)

## 思路

我看题解里没有 $O(n\log n)$ 的做法，交一发。

把所有的区间按 $r$ 的大小从小到大排个序，然后贪心，设现在处理的是第 $i$ 条线段，有以下几种情况：

- $l_{i}$ 小于前面选了的线段的右端点，直接跳过。

- $l_{i}$ 与上一个没选线段相交，选择的对数增加，更新已经选择了的线段的右端点。

- 否则更新没选线段的右端点。

最后用 $n$ 减去选择的对数乘 $2$ 就是删除的对数。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	long long l;
	long long r;
}xd[2005];
long long t;
long long n;
long long ans;
bool cmp(node x,node y){
	return x.r<y.r;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld",&t);
	while(t--){
		ans=0;
		scanf("%lld",&n);
		for(long long i=1;i<=n;i++) scanf("%lld%lld",&xd[i].l,&xd[i].r);
		sort(xd+1,xd+n+1,cmp);
		long long ansr=-1;
		long long xr=-1;
		for(long long i=1;i<=n;i++){
    	    if(xd[i].l<=ansr) continue;
			if(xd[i].l<=xr){
				ans++;
				ansr=xd[i].r;
			}
			else xr=xd[i].r;
    	}
		printf("%lld\n",n-2*ans);
		for(long long i=1;i<=n;i++){
			xd[i].l=0;
			xd[i].r=0;
		}
	}
	return 0;
}
```

---

## 作者：xs_siqi (赞：2)

给出一个 $O(n^2+n\log n)$，而且 $O(n^2)$ 大多数情况下难以跑满，且解题思路过程简单，状态设计简洁的题解。

首先容斥一下，删最少的就是选最多的。然后将所有端点按右端点排序一下。为什么按右端点排序？这是线段覆盖问题的基本结论，可以通过[这篇博客](https://blog.csdn.net/yl_puyu/article/details/109681226)得到具体的证明。这里不多赘述。

以 $f_i$ 表示必选 $i$，考虑了 $i$ 个元素的最大值。考虑如何转移。

考虑到 $i$ 对后方不好转移，所以将转移区间定位在 $[1,i-1]$ 区间中。然后从大到小枚举区间 $[1,i-1]$，找一个位于该区间的 $j$ 满足 $r_j>l_i$。因为区间关于右端点非严格递减，所以遇到不满足可以直接退出。所以这是很难跑满的。

考虑转移 $j$ 前的 $f$ 序列。选取的点 $k$ 必然在 $[1,j-1]$ 区间内，且满足 $r_k<l_j$ 且 $r_k<l_i$。由于区间 $[1,j-1]$ 的 $f$ 值已定且为静态，可以考虑对 $f$ 值做前缀最大值，然后预处理在 $[1,j-1]$ 区间内，满足 $r_k<l_j$ 的最大的 $k$。记前缀最大值为 $pre$ 序列。转移方程显然是 $f_i=pre_k+2$。

考虑到 $r_k$ 单调，可以二分。但是考虑到这个优化对复杂度没用（因为枚举转移还是要两重循环），也可以直接写暴力两重循环转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2005;
int ans,T,n,f[maxn],pre[maxn],p[maxn];
struct edge{
	int l,r;
	friend bool operator < (edge x,edge y){
		return x.r==y.r?x.l<y.l:x.r<y.r;}}a[maxn];
int main(){
	scanf("%d",&T);
	while(T--){
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)f[i]=p[i]=pre[i]=0;
		for(int i=1;i<=n;i++)
			scanf("%d%d",&a[i].l,&a[i].r);
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
			for(int j=i-1;j>=1;j--)
				if(a[j].r<a[i].l){
					p[i]=j;break;}
		for(int i=1;i<=n;i++){
			for(int j=i-1;j>=1;j--){
				if(a[j].r<a[i].l)break;
				f[i]=max(pre[min(p[i],p[j])]+2,f[i]);}
			pre[i]=max(pre[i-1],f[i]);}
		printf("%d\n",n-pre[n]);}
	return 0;}
```


---

## 作者：Little_Cabbage (赞：1)

**题目大意：**

给你 $n$ 条线段，让你删除掉其中的一些线段，使得剩余的线段是偶数且可以两两配对且每组不相交。

**解题思路：**

正难则反，计算选择多少条可以满足要求。

只有相交的两条线段才可能成为一组，所以枚举两条线段，如果它们相交，直接合并起来。

题目还要求每组线段不相交，所以直接计算合并后的线段最多不相交的数量。

最后用总线段数减去合并后的线段最多不相交的数量即可。

**代码：**

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define ldb long double
#define db double
#define endl '\n'
using namespace std;
const int N = 2010;
int read() {
	char c = 0;
	int f = 1, x = 0;
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + (int)(c - '0');
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x == 0) {
		putchar(x + '0');
		return ;
	}
	if (x < 0) {
		putchar('-');
		x = abs(x);
	}
	stack<int> s;
	while (x) {
		s.push(x % 10);
		x /= 10;
	}
	while (s.size()) {
		putchar(s.top() + '0');
		s.pop();
	}
}
int n;
struct node {
	int x, y;
} a[N], b[N * N];
int len;
bool cmp(node a, node b) {
	return a.y < b.y;
}
int ans, cnt;
void Solve() {
	len = 0;
	n = read();//输入数据
	for (int i = 1; i <= n; i++) a[i].x = read(), a[i].y = read();
	for (int i = 1; i <= n; i++)//枚举线段
		for (int j = i + 1; j <= n; j++) {
			if (a[i].y < a[j].x || a[i].x > a[j].y) continue;
			b[++len] = {min(a[i].x, a[j].x), max(a[i].y, a[j].y)};
		}
	sort(b + 1, b + len + 1, cmp);//计算合并后的线段最多不相交的数量
	ans = 0;
	cnt = -1;
	for (int i = 1; i <= len; i++)
		if (b[i].x > cnt) {
			cnt = b[i].y;
			ans += 2;
		}
	cout << n - ans << endl;
}
signed main() {
	int t = 1;
	t = read();
	while (t--) Solve();
	return 0;
}
```

[通过记录](https://codeforces.com/contest/1841/submission/254057122)

最后一句话：如果你在洛谷上总是 `UKE`，建议到 `Codeforces` 直接看评测结果，~~比如我~~。

---

## 作者：lucktains (赞：1)

观察题目：要删除最少的线段，就等于选择最多的线段。

看到 $n<=2000$，就知道应该是 $O(n^2)$ 级别的做法。

先枚举出每条线段，两两结合，得到 $n^2$ 个线段。

这时就转化成了最大不相交区间数量。

先按右端点排序然后贪心，时间复杂度 $O(n^2\log{n^2})$。

### AC Code
```cpp
/*
把每两个能合并的线段合并
在找出最多能选几条不合并的线段
在用n减去线段数就行了
*/
#include <bits/stdc++.h>
#define PII pair<int, int>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<PII> a(n + 1), b;
        for (int i = 1; i <= n; i++)
            cin >> a[i].first >> a[i].second;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if(min(a[i].second, a[j].second)>=max(a[i].first, a[j].first))
                b.push_back({min(a[i].first, a[j].first),
                             max(a[i].second, a[j].second)});
            }
        }
        sort(b.begin(), b.end(),
             [](PII x, PII y) { return x.second < y.second; });
        int ed = -1, ans = 0;
        for (int i = 0; i < b.size(); i++) {
            if (b[i].first > ed) {
                ans++;
                ed = b[i].second;
            }
        }
        cout << n - ans - ans << '\n';
    }
    return 0;
}

```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给出 $n$ 个线段，你需要删去一些线段，使得剩下的可以两两配对。同一对线段有交，不同对线段无交。最小化删去线段数量。

$T$ 组数据。

$1\leq\sum n\leq 2\times10^3$

## 思路

首先我们可以将可以构成同一对线段合并成一个线段。然后就变成了给出多个线段，你需要选出最多的线段，使得两两无交。

考虑一个显然的贪心策略，对于每一个线段，按照右端点从小到大排序，枚举每一条线段，如果可以选择就选。

考虑证明这一点：假设我们现在的决策位于后缀 $[p,n]$。如果存在选择一个线段 $[p,r]$ 为最优策略，则若存在线段 $[p,r^{'}],r>r^{'}$，则 $[r^{'}+1,n]$ 的答案一定不劣于 $[r+1,n]$（因为大不了我可以不覆盖 $[r^{'}+1,r]$）。所以贪心策略是正确的。

时间复杂度 $O(n^2\log n)$ 可以通过本题。事实上我们已经有方法做到 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2005;

struct segment{
	int l,r;
	segment(){}
	segment(int L, int R){l = L, r = R;}
	bool operator<(const segment &x) const {return r < x.r;}
	bool operator^(const segment &x) const {return (r < x.l) || (l > x.r);}
	segment operator+(const segment &x) const {return segment(min(l, x.l), max(r, x.r));}
} a[N], b[N * N];

int n;

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].l>>a[i].r;
	int tot = 0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(!(a[i] ^ a[j])) b[++tot] = a[i] + a[j];
		}
	}
	sort(b + 1, b + tot + 1);
	int ans = 0, R = -1;
	for(int i=1;i<=tot;i++){
		if(b[i].l > R) ans++, R = b[i].r;
	}
	cout<<(n - (ans << 1))<<'\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Schi2oid (赞：1)

给出一个 $O(n^2+n\log n)$ 的做法。

容易发现，对于一组合法的区间，按照左端点排序后，匹配情况应该是第 $2i-1$ 和第 $i$ 个区间进行匹配。

这是由于合法区间组中任何一个区间内只会至多包含来自一个其他区间的端点。考虑左端点最靠左的区间 $L_1$，其匹配区间 $L_i$ 的左端点无法避免在 $L_1$ 出现，又因为 $L_1$ 中出现的端点只能来自至多一个区间，故直接将其与 $L_2$ 匹配一定是正确的。删去 $L_1,L_2$，可以归纳证明该结论正确。

那么直接排序区间，设 $dp_{i,j,0/1}$ 表示当前考虑完 $i$，最靠右被覆盖到的点是编号为 $j$ 的区间的右端点，目前共保留了偶/奇数个区间。直接朴素转移即可。具体转移式子可以参考下方代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r;
}a[2005];
bool cmp(node x,node y){
	if(x.l!=y.l) return x.l<y.l;
	else return x.r<y.r;
}
int dp[2005][2005][2];
bool inter(int x,int y){
	return a[y].l<=a[x].r;
}
int main(){
	int t,n;
	cin>>t;
	a[0].l=-1;
	a[0].r=-1;
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d%d",&a[i].l,&a[i].r);
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++) for(int j=0;j<=n;j++) dp[i][j][0]=dp[i][j][1]=n+1;
		dp[0][0][1]=n+1;
		for(int i=0;i<n;i++){
			for(int j=0;j<=i;j++){
				if(!inter(j,i+1)) dp[i+1][i+1][1]=min(dp[i+1][i+1][1],dp[i][j][0]);
				dp[i+1][j][0]=min(dp[i+1][j][0],dp[i][j][0]+1);
				if(inter(j,i+1)){
					if(a[i+1].r>a[j].r) dp[i+1][i+1][0]=min(dp[i+1][i+1][0],dp[i][j][1]);
					else dp[i+1][j][0]=min(dp[i+1][j][0],dp[i][j][1]);
				}
				dp[i+1][j][1]=min(dp[i+1][j][1],dp[i][j][1]+1);
			}
		}
		int ans=n+1;
		for(int i=0;i<=n;i++) ans=min(ans,dp[n][i][0]);
		printf("%d\n",ans);
	}
	return 0;
}


---

## 作者：封禁用户 (赞：0)

# 题意
一条直线上有 $n$ 条线，给你左右端点。我们将他们两两配对，满足配对的两条线段有相交，不配对的线段不相交。

注意相交的定义：两条线段左右端点分别为 $l_x,r_x,l_y,r_y$。那么相交的定义为 $l_y \le l_x \le r_y$ 或 $l_y \le r_x \le r_y$ 或 $l_x \le l_y \le r_x$ 或 $l_x \le r_y \le r_x$。即有一条线段的一个端点在另一个线段之内，包括端点重合。

看一下样例的第一组：

```
7
2 4
9 12
2 4
7 7
4 8
```
![](https://cdn.luogu.com.cn/upload/image_hosting/uptostal.png)

绿的线段是选的，红的线段是删的。所以删一条。

# 思路
又是正难则反。我们将两两可以重一起的线段并成一条线段，就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/mh1q23wp.png)

这样就转换成了一个经典的贪心：在直线内取线段，让所有都不重叠，求取最多的线段数。

方法很简单，也就是按最右边排序，如果当前的与以前重复就跳过，不然就取即可。

这种方法并不会算重线段，因为同一条线段与不同的线段组出来的线段一定会有重复，所以不会算重。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,n) for(int i=j;i<=n;i++)
using namespace std;
int t;
struct ab{
	int l;
	int r;
	friend bool operator <(ab a,ab b){
		return a.r<b.r;
	}
}op[4000010];
struct abc{
	int l;
	int r;
}ss[2010];
int tot;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>t;
	while(t--){
		tot=0;
		int n;
		cin>>n;
		f(i,1,n){
			cin>>ss[i].l>>ss[i].r;
		}
		f(i,1,n){
			f(j,i+1,n){
				if(ss[i].l<=ss[j].r&&ss[i].l>=ss[j].l){
					op[++tot].l=min(ss[j].l,ss[i].l);
					op[tot].r=max(ss[i].r,ss[j].r);
				}else if(ss[i].r<=ss[j].r&&ss[i].r>=ss[j].l){
					op[++tot].l=min(ss[j].l,ss[i].l);
					op[tot].r=max(ss[i].r,ss[j].r);
				}else if(ss[j].l<=ss[i].r&&ss[j].l>=ss[i].l){
					op[++tot].l=min(ss[j].l,ss[i].l);
					op[tot].r=max(ss[i].r,ss[j].r);
				}else if(ss[j].r<=ss[i].r&&ss[j].r>=ss[i].l){
					op[++tot].l=min(ss[j].l,ss[i].l);
					op[tot].r=max(ss[i].r,ss[j].r);
				}
			}
		}
		sort(op+1,op+1+tot);
		int ll=-1,sum=0;
		for(int i=1;i<=tot;i++){
//			cout<<op[i].l<<" "<<op[i].r<<endl;
			if(op[i].l<=ll){
				continue;
			}
			sum++;
			ll=max(ll,op[i].r);
		}
//		cout<<"        ";
		cout<<n-2*sum<<endl;
	} 
	return 0;
}
```

---

## 作者：qw1234321 (赞：0)

过水，建议降绿。

一个很自然的想法是枚举所有的线段对，把原本相交的两条线段合成一条新的线段，如下实现：

```cpp
int sections = 0;
for (int i = 1; i <= n; i++){
	for (int j = i + 1; j <= n; j++){
		a[++sections].l = min(b[i].l, b[j].l);
		a[sections].r = max(b[i].r, b[j].r);
		if (a[sections].r - a[sections].l + 1 >= b[i].r - b[i].l + 1 + b[j].r - b[j].l + 1) sections--;
	}
}
```

其中 $b$ 数组是读入的线段，$a$ 数组是合成的线段，if 那行判断了原先的线段 $i$ 和 $j$ 是否相交，没相交就废掉这条合成的线段，因为不满足题目要求。

然后得到若干条线段后，选取最多的线段数，记为 $ans$，则最少删除的线段数为 $n - 2 \times ans$。（请读者自行思考，证明十分简单）。

拿上线段覆盖的模板怼上去就行了。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e3 + 5;
int t, n;
struct line{
	int l, r;
}a[N << 11], b[N];

bool cmp(line a, line b){
	return a.r < b.r;
}

signed main(){
	cin >> t;
	while(t--){
		cin >> n;
		for (int i = 1; i <= n; i++) scanf("%lld %lld", &b[i].l, &b[i].r);
		int sections = 0;
		for (int i = 1; i <= n; i++){
			for (int j = i + 1; j <= n; j++){
				a[++sections].l = min(b[i].l, b[j].l);
				a[sections].r = max(b[i].r, b[j].r);
				if (a[sections].r - a[sections].l + 1 >= b[i].r - b[i].l + 1 + b[j].r - b[j].l + 1) sections--;
			}
		}
		int now = -1, ans = 0;
		sort(a + 1, a + sections + 1, cmp);
		for (int i = 1; i <= sections; i++){
			if (a[i].l > now){
				ans++;
				now = a[i].r;
			}
		}
		printf("%lld\n", n - ans * 2);
	}
	return 0;
}
```

------------

题外话： 建议降绿。（）（）（）

---

## 作者：huangrenheluogu (赞：0)

简单题。

考虑合法的应该是什么样的，我们按照左端点排序之后，$(1,2),(3,4),\dots,(2i-1,2i)$ 会分成一组，按照组内组外的要求判断就可以了。

先把线段按照左端点排序。

同时，把一组分成第一条和第二条两部分。

那么，记 $f_i$ 为选了第 $i$ 条线段作为一组里的第一条，这个组编号的最大值。

为了转移 $f_i$，可以记 $maxn_i$ 表示目前的又端点是第 $i$ 个点，最多选了几组，注意这里是完整的一组。

转移就很简单了，$f_i=max\{maxn_j\}(j<l_i),maxn_{r_i}=max\{f_j+1\}(r_j\ge l_i,j<i)$。

转移 $f$ 可以做到线段树维护 $maxn$ 的 $O(n\log n)$，但是因为转移 $maxn$ 用了 $O(n^2)$ 以及题目要求，所以代码中用 $O(n^2)$ 转移 $f$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2005;
int T, n, aa[N << 1], tot, f[N], maxn[N << 1], ans;
struct seg{
    int l, r;
}a[N];
inline void get(int &x){
    x = lower_bound(aa + 1, aa + tot + 1, x) - aa;
}
inline void Unique(){
    tot = 0;
    for(int i = 1; i <= n; i++) f[i] = 0;
    for(int i = 1; i <= n; i++){
        aa[++tot] = a[i].l;
        aa[++tot] = a[i].r;
    }
    sort(aa + 1, aa + tot + 1);
    tot = unique(aa + 1, aa + tot + 1) - aa - 1;
    for(int i = 1; i <= n; i++){
        get(a[i].l);
        get(a[i].r);
    }
    for(int i = 1; i <= tot; i++) maxn[i] = 0;
}
inline bool cmp(seg x, seg y){
    return x.l < y.l;
}
int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);
        Unique();
        sort(a + 1, a + n + 1, cmp);
        for(int i = 1; i <= n; i++){
            f[i] = 1;
            for(int j = 1; j < a[i].l; j++) f[i] = max(f[i], maxn[j] + 1);
            for(int j = 1; j < i; j++){
                if(a[j].r >= a[i].l){
                    maxn[max(a[j].r, a[i].r)] = max(maxn[max(a[j].r, a[i].r)], f[j]);
                }
            }
            //printf("f[%d] = %d\n", i, f[i]);
        }
        ans = 0;
        for(int i = 1; i <= tot; i++) ans = max(ans, maxn[i] * 2);
        printf("%d\n", n - ans);
    }
    return 0;
}
/*
1
7
2 4
9 12
2 4
7 7
4 8
10 13
6 8
*/
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

我们先把向线段按右端点排序。

设 dp 状态 $dp_{i}$ 为考虑了前 $i$ 个线段，并且选了线段 $i$ 时可以选择的最多的线段数量。对于线段 $i$，可以与其匹配的是线段 $j$ 满足 $i<j,r_j>l_i$，这一点很容易想到。那么为了保证组与组之间不重叠，那么我们上一组的右端点就应该 $≤\min(l_i,l_j)$。

我们把线段按右端点排序，所以右端点小于某一个特定值的线段应该是一个前缀。

所以我们可以这样转移：

$dp_{i}=\max_{j=1}^{i-1}([r_j≥l_i](\max_{k=1}^{l_k<\min(l_i,r_i)} f_k+2))$。

那么我们后面部分的 $\max $ 很明显是一个前缀最大值，我们维护一个前缀最大值数组即可。至于我们要求出k的最大值，那么我们就直接在单调递增的线段数组上二分查询即可。

时间复杂度是枚举 $i$，$O(n)$，第一个 $\max$，$O(n)$，第二个 $\max$ 可以用前缀最大值 $O(1)$ 维护，二分则是 $O(\log n)$ 的。所以总复杂度为 $O(n^2\log n)$。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define ps second
#define pf first
 
 
#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int N=2e5+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;
 
int q;
int T,mn=INF,ans;
int f[N],r;
pii a[N];
int tot,pmx[N];

bool cmp(pii a,pii b){
	return a.pf<b.pf;
}


void init(){
	memset(f,0,sizeof(f));
	memset(pmx,0,sizeof(pmx));
}

void solve(){
	int n=rd;
	for(int i=0;i<n;i++){
		a[i].ps=rd,a[i].pf=rd;
	}
	sort(a, a+n,cmp);
	ans = 0;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (a[j].pf >= a[i].ps) {
				auto pos = lower_bound(a, a+n, make_pair(min(a[j].ps, a[i].ps), -1),cmp);
				if (pos == a+1) {
					f[i] = max(f[i], 2ll);
				} else {
					int k = pos - a - 1;
					f[i] = max(pmx[k] + 2, f[i]);
				}
			}
		}
		pmx[i] = max(pmx[i - 1], f[i]);
		ans = max(f[i], ans);
	}
		
}

signed main() {
	int T=rd;
	while(T--){
		init();
		solve();
		// cerr<<"ans=";
		cout << n - ans << '\n';
	}
}
/*
2
3 2 3 6
*/
```




---

## 作者：luogu_gza (赞：0)

考虑枚举任意两个区间，如果他们有交，就往数组里插入它们的并，然后跑一遍最大不相交区间数量。

这样操作后，这些并集就代表答案中可能的一对。

然后，每一对对答案产生的贡献是相同的，这就意味着答案只关心有几对，不关心哪几对，所以这是对的。

---

## 作者：AlicX (赞：0)

## Solution 

做这道题之前不妨先看看 [P1803](https://www.luogu.com.cn/problem/P1803)。

题目需要删除最少的线段，即保留最多的线段。那么选出尽可能多的区间不相交，不妨借鉴 P1803 的贪心按右端点排序后选择。

定义 $f_i$ 表示第 $i$ 条线段必选，则枚举线段 $j$ 与 $i$ 匹配，此时满足 $j<i$ 且 $r_j \geq l_i$，此时 $i,j$ 线段包含 $\min(l_i,l_j) \sim r_i$。其他线段不与此段相交，即 $r_k < \min(l_i,l_j)$，因为已经按 $r$ 排序了，所以有贡献的区间一定是一段连续区间，二分出最后一个满足 $r_k < \min(l_i,l_j)$ 的下标然后取前缀最大值即可。 

时间复杂度 $O(n^2 \log n)$。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define db double 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2010; 
int n; 
int f[N],g[N]; 
struct Node{ 
	int l,r; 
	il bool operator<(const Node& dwy)const{ 
		return r<dwy.r; 
	} 
}a[N]; 
il void solve(){ 
	n=read(); 
	for(int i=1;i<=n;i++) a[i].l=read(),a[i].r=read(),f[i]=g[i]=0; 
	sort(a+1,a+n+1); 
	// debug(); for(int i=1;i<=n;i++) cout<<a[i].l<<" "<<a[i].r<<endl; 
	for(int i=2;i<=n;i++){ 
		for(int j=1;j<i;j++){ 
			if(a[j].r<a[i].l) continue; 
			int l=0,r=j-1,res=0; 
			while(l<=r){
				int mid=l+r>>1; 
				if(a[mid].r<min(a[j].l,a[i].l)) l=mid+1,res=mid;  
				else r=mid-1; 
			} f[i]=max(f[i],g[res]+2); 
		} g[i]=max(g[i-1],f[i]); 
	} printf("%d\n",n-g[n]); 
} 
signed main(){ 
	int T=read(); 
	while(T--) solve(); 
	return 0; 
} 
```

---

