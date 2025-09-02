# Neutral Tonality

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, as well as an array $ b $ consisting of $ m $ integers.

Let $ \text{LIS}(c) $ denote the length of the [longest increasing subsequence](https://en.wikipedia.org/wiki/Longest_increasing_subsequence) of array $ c $ . For example, $ \text{LIS}([2, \underline{1}, 1, \underline{3}]) $ = $ 2 $ , $ \text{LIS}([\underline{1}, \underline{7}, \underline{9}]) $ = $ 3 $ , $ \text{LIS}([3, \underline{1}, \underline{2}, \underline{4}]) $ = $ 3 $ .

You need to insert the numbers $ b_1, b_2, \ldots, b_m $ into the array $ a $ , at any positions, in any order. Let the resulting array be $ c_1, c_2, \ldots, c_{n+m} $ . You need to choose the positions for insertion in order to minimize $ \text{LIS}(c) $ .

Formally, you need to find an array $ c_1, c_2, \ldots, c_{n+m} $ that simultaneously satisfies the following conditions:

- The array $ a_1, a_2, \ldots, a_n $ is a subsequence of the array $ c_1, c_2, \ldots, c_{n+m} $ .
- The array $ c_1, c_2, \ldots, c_{n+m} $ consists of the numbers $ a_1, a_2, \ldots, a_n, b_1, b_2, \ldots, b_m $ , possibly rearranged.
- The value of $ \text{LIS}(c) $ is the minimum possible among all suitable arrays $ c $ .

## 说明/提示

In the first test case, $ \text{LIS}(a) = \text{LIS}([6, 4]) = 1 $ . We can insert the number $ 5 $ between $ 6 $ and $ 4 $ , then $ \text{LIS}(c) = \text{LIS}([6, 5, 4]) = 1 $ .

In the second test case, $ \text{LIS}([\underline{1}, 7, \underline{2}, \underline{4}, \underline{5}]) $ = $ 4 $ . After the insertion, $ c = [1, 1, 7, 7, 2, 2, 4, 4, 5, 5] $ . It is easy to see that $ \text{LIS}(c) = 4 $ . It can be shown that it is impossible to achieve $ \text{LIS}(c) $ less than $ 4 $ .

## 样例 #1

### 输入

```
7
2 1
6 4
5
5 5
1 7 2 4 5
5 4 1 2 7
1 9
7
1 2 3 4 5 6 7 8 9
3 2
1 3 5
2 4
10 5
1 9 2 3 8 1 4 7 2 9
7 8 5 4 6
2 1
2 2
1
6 1
1 1 1 1 1 1
777```

### 输出

```
6 5 4
1 1 7 7 2 2 4 4 5 5
9 8 7 7 6 5 4 3 2 1
1 3 5 2 4
1 9 2 3 8 8 1 4 4 7 7 2 9 6 5
2 2 1
777 1 1 1 1 1 1```

# 题解

## 作者：Alex_Wei (赞：10)

### [CF1893B Neutral Tonality](https://www.luogu.com.cn/problem/CF1893B)

首先肯定将 $b$ 降序排序。

设 $a$ 的后缀 $\max$ 为 $c$，那么在放入 $a_j$ 之前，将所有 $b_i > c_j$ 的 $b_i$ 全部加入序列。这样可以保证原序列的 LIS 长度不变：假设存在 $b_i$ 让 LIS 长度增加，则 LIS 包含 $b_i$。假设 $b_i$ 在 $a_j$ 和 $a_{j + 1}$ 之间。由于 $b_i > c_{j + 1}$，于是 $b_i$ 是 LIS 的结尾。如果 $j = 0$，说明 $b_i$ 是 LIS 的开头，原序列 LIS 长度小于 $1$，矛盾。因此 $j > 0$，那么 $a_j \geq b_i$，否则 $b_i > c_j$，$b_i$ 会放在 $a_j$ 前面。将新序列的 LIS 中的 $b_i$ 替换为 $a_j$ 可得原序列长度相等的 IS，与 LIS 长度增加矛盾。

时间复杂度 $\mathcal{O}(m\log m + n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rnd(1064);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 998244353;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e6 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

// ---------- templates above ----------

constexpr int N = 2e5 + 5;

int n, m, a[N], b[N], c[N];
void mian() {
  cin >> n >> m;
  a[n + 1] = c[n + 1] = 0;
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = n; i; i--) c[i] = max(c[i + 1], a[i]); 
  for(int i = 1; i <= m; i++) cin >> b[i];
  sort(b + 1, b + m + 1);
  reverse(b + 1, b + m + 1);
  vector<int> ans;
  for(int i = 1, pt = 1; i <= n + 1; i++) {
    while(pt <= m && b[pt] >= c[i]) ans.push_back(b[pt++]);
    if(i <= n) ans.push_back(a[i]);
  }
  for(int it : ans) cout << it << " ";
  cout << "\n";
}


bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while(T--) mian();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：james1BadCreeper (赞：9)

答案的下界是 $a$ 的 LIS 长度，我们看看是否能够让答案就是这个。

由于 $b$ 可以随便加，因此将 $b$ 从大到小排序，这样能保证 $b$ 自身不会贡献 LIS 的长度。如果在 $a_i$ 前面扔一个所有数都比 $a_i$ 大的下降序列，那么此时将 $a_i$ 选进 LIS 里只可能比将下降序列的任何一个数选进 LIS 的长度更长，因此这样将 $b$ 扔进 $a$ 里一定不会使 LIS 变长。最后将剩余的 $b$ 扔到 $a$ 末尾，双指针合并 $a,b$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n, m; 
int a[200005], b[200005], c[400005]; 

void solve(void) {
    cin >> n >> m; 
    for (int i = 1; i <= n; ++i) cin >> a[i]; 
    for (int i = 1; i <= m; ++i) cin >> b[i]; 
    sort(b + 1, b + m + 1, greater<int>()); 
    for (int i = 1, p = 1, q = 1; i <= n + m; ++i) {
        if (p > n || (q <= m && b[q] > a[p])) c[i] = b[q++]; 
        else c[i] = a[p++]; 
    }
    for (int i = 1; i <= n + m; ++i) cout << c[i] << " \n"[i == n + m]; 
}

int main(void) {
    ios::sync_with_stdio(0); 
    int T; cin >> T; 
    while (T--) solve(); 
    return 0; 
}
```

---

## 作者：cpchenpi (赞：7)

每插入一个数 $x$，我们一定可以使 LIS 长度不变。

具体方法：若 $x$ 是新的最大值，则将它放在数组最开始。

否则，找到最后一个大于它的数 $y$，将 $x$ 放在紧跟 $y$ 的后面，一定不会加长 LIS。反证：若新的 LIS 更长，一定以 $x$ 为结尾，将其替换为 $y$，LIS 长度不减。

接下来考虑如何执行这个操作。若对每个插入都暴力执行一遍这样的插入，时间复杂度显然是不过关的 $O(nm)$，所幸我们可以将插入排序，这样对每个 $x_i$，对应的 $y_i$ 的位置是单调递减的，可以在一遍从后往前的扫描中完成“若原数组当前数更大，就将新数组当前数插入”这样操作。

可以发现这正好是有序序列归并的方式。因此我们可以直接调用标准库的 `merge` 函数完成操作，最终总时间复杂度 $O(m \log m + n + m)$，即 $O (n + m \log m)$。

参考代码（C++）：

``` cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m), c(n + m);
    for (int &x : a)
        cin >> x;
    for (int &x : b)
        cin >> x;
    ranges::sort(b, greater<>());
    ranges::merge(a.rbegin(), a.rend(), b.rbegin(), b.rend(), c.rbegin());
    for (int x : c)
        cout << x << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
```

---

## 作者：incra (赞：2)

### Solution
挺有意思的构造题。

考虑把 $\{b\}$ 序列降序插入，这样 $\{b\}$ 之间对答案的影响就没了。

考虑以下构造方法：对于数 $x$，把它插入到最后一个 $a_i$ 使得 $a_i>x$。这样答案一定最小。

证明：考虑 LIS 的计算过程，以 $a_i$ 结尾的 LIS 显然比以 $x$ 结尾的 LIS 长，又因为 $\displaystyle\max_{k=i+1}^n\{a_i\}<x$，所以 $a_i>\displaystyle\max_{k=i+1}^n\{a_i\}$，所以以 $a_i$ 结尾的 LIS 的长度就是原来不加数的 LIS 的长度，而这个长度大于等于以 $x$ 结尾的 LIS 的长度，所以加上 $x$，LIS 长度不变。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 200010;
int n,m;
int a[N],b[N];
int p[N];
vector <int> v[N];
int main () {
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		v[0].clear ();
		for (int i = 1;i <= n;i++) cin >> a[i],v[i].clear ();
		p[n + 1] = 0;
		for (int i = n;i >= 1;i--) p[i] = max (p[i + 1],a[i]);
		for (int i = 1;i <= m;i++) cin >> b[i];
		sort (b + 1,b + m + 1,greater <int> ());
		for (int i = 1;i <= m;i++) {
			int l = 1,r = n;
			while (l < r) {
				int mid = l + r + 1 >> 1;
				if (p[mid] >= b[i]) l = mid;
				else r = mid - 1;
			}
			if (p[l] >= b[i]) v[l].pb (b[i]);
			else v[0].pb (b[i]);
		}
		for (int x : v[0]) cout << x << ' ';
		for (int i = 1;i <= n;i++) {
			cout << a[i] << ' ';
			for (int x : v[i]) cout << x << ' ';
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：naroto2022 (赞：1)

# CF1893B 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1893B)

### 题意

给定两个数组 $a,b$，构造一个序列 $c$，使得其包含 $a,b$ 中的所有元素，保证 $a$ 在其中的相对顺序不变，且最长（严格）上升子序列（$\text{LIS}(c)$）最短。

转化一下，也可以理解为，给定两个数组 $a,b$，要求把 $b$ 中的所有元素按照任意顺序插入 $a$ 中，要求最终形成的数组的最长（严格）上升子序列最短。

### 思路

首先因为 $a$ 在 $c$ 中的相对位置不变，所以必然有 $\text{LIS}(c)\geqslant\text{LIS}(a)$。

那么就考虑如何插入 $b$ 可以使得 $\text{LIS}(c)=\text{LIS}(a)$，容易想到一种简单的构造方法，现将 $b$ 从大到小排序，对于一个数 $b[j]$，将它插入到第一个满足 $a[i]\leqslant b[j]$ 的 $a[i]$ 前面，那为什么这样是 $\text{LIS}(c)=\text{LIS}(a)$ 的呢？接下来开始证明。

首先，因为是插入到第一个满足 $a[i]\leqslant b[j]$ 的 $a[i]$ 前面，所以在 $a[i]$ 前面的所有数都小于 $b[j]$，但是因为 $a[i]\leqslant b[j]$，所以对于一个上升子序列，选 $a[i]$ 肯定更优（至少是一样），要是有多个数插在同一个位置也不会影响答案，因为 $b$ 已经被从大到小排序过，所以每次的插入不会改变序列的最长（严格）上升子序列。

那么，开始打代码吧~

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=200005;
ll T,n,m,a[MN],b[MN];
bool cmp(ll x, ll y){return x>y;}
void write(ll n){if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
int main(){
	T=read();while(T--){
		n=read();m=read();for(int i=1; i<=n; i++) a[i]=read();for(int i=1; i<=m; i++) b[i]=read();
		sort(b+1,b+1+m,cmp);//从大到小排序 
		for(int i=1,p1=1,p2=1; i<=n+m; i++){
			if(p1>n||(p2<=m&&b[p2]>=a[p1])) write(b[p2++]),putchar(' ');
			else write(a[p1++]),putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：1)

很巧妙的一道题。

为了让 $\text{LIS}$ 长度最小，我们肯定先将 $b$ 数组降序排序，这样 $b$ 自身对 $\text{LIS}$ 的贡献最小。

考虑是否存在一种插入方式使得最终 $a$ 的 $\text{LIS}$ 长度和最初 $a$ 的 $\text{LIS}$ 长度相等。这时我们会发现，如果我们插入 $b$ 的时候形如：$a_1,a_2,\dots,a_k,{\color{Red}b_1,b_2,\dots,b_p},a_{k+1}$，且满足 $\min_{1 \le i \le k}(a_i) > \max_{1 \le i \le p}(b_i) > a_{k+1}$，那么 $b$ 数组一定对答案没有影响（一定不会增加 $\text{LIS}$ 的长度），因为选 $b$ 中的任意一个数都不如选 $a_{k+1}$（$a_{k+1}$ 更小，后面能选的更多）。

所以我们的构造方式为：对于一个数 $a_i$，把 $b$ 的一段大于 $a_i$ 的前缀全部放到 $a_i$ 前面，最后剩下的数一定小于所有数，直接放到最后即可。 

---

## 作者：fuxuantong123 (赞：1)

# CF1893B Neutral Tonality 题解
## 思路
首先，不管 $b$ 怎么插入 $a$，$a$ 的 LIS 都不可能减小。所以应该让 $a$ 的 LIS 不增。每次插入时让插入的元素小于前一个元素即可使 LIS 一定不增。

具体来说，使用两个指针 $i$ 和 $j$ 遍历 $a$ 和 $b$，每一次都在 $c$ 中加入两个数字（$a_i$ 或 $b_j$）中较大的一个，并移动相应的指针。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010];
int b[200010];
int c[400010];
bool cmp(int x,int y){
	return x>y;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=m;i++){
			scanf("%d",&b[i]);
		}
		sort(b+1,b+m+1,cmp);
		int cnt=0;
		int i,j;
		for(i=1,j=1;i<=n && j<=m;){
			if(a[i]>b[j]){
				c[++cnt]=a[i];
				i++;
			}
			else{
				c[++cnt]=b[j];
				j++;
			}
		}
		while(i<=n){
			c[++cnt]=a[i];
			i++;
		}
		while(j<=m){
			c[++cnt]=b[j];
			j++;
		}
		for(i=1;i<=n+m;i++){
			printf("%d ",c[i]);
		}
		printf("\n");
	}
return 0;
}

```


---

## 作者：One_JuRuo (赞：1)

## 思路

首先可以知道答案的下界就是序列 $a$ 原来的 LIS，现在需要做的就是尽可能地保持答案不增加。

可以肯定的是，将序列 $b$ 从大到小地插入序列 $a$ 是不劣的，并且如果在 $a_i$ 前插入的都是 $\ge a_i$ 的不会使答案增加，可以感性理解，如果原来的 LIS 没有选择 $a_i$，那么选择插入的降序序列则会让答案变劣，如果选择了 $a_i$，并且在插入后改为下降序列的某一个数字，那么后面的选择会变少，答案一定不会增加。

所以这道题就很明了了。

对于 $a_i$，直接将目前剩下的所有 $\ge a_i$ 的数字按照降序全部在 $a_i$ 前插入即可，还需要将没插完的 $b_i$ 在最后降序输出。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a[200005],b[200005],p;
inline bool cmp(int a,int b){return a>b;}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m),p=1;
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1;i<=m;++i) scanf("%d",&b[i]);
		sort(b+1,b+m+1,cmp);
		for(int i=1;i<=n;++i)
		{
			while(p<=m&&b[p]>=a[i]) printf("%d ",b[p++]);
			printf("%d ",a[i]);
		}
		for(int i=p;i<=m;++i) printf("%d ",b[i]);
		puts("");
	}
	return 0;
}

```

---

## 作者：AllenAlien (赞：1)

我们发现，不管序列 $b$ 如何插入序列 $a$，序列 $a$ 的 $\text{LIS}$ 只有可能增大，不可能减小，因此只要找到一种插入方式使 $\text{LIS}$ 不增即可。每次插入时保证插入的元素小于前一个元素，则 $\text{LIS}$ 一定不增。

具体方法为：从 $a[n]$ 开始将排序后的 $b$ 依次插入，若最后一个元素小于待插入元素则向前寻找，直到找到大于该元素的 $a[i]$，若找到 $a$ 开头仍有剩余，则将剩余元素插入在头部。

由于需要频繁插入和删除元素，因此选择使用链表维护。

时间复杂度 $O(m+n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
    int s=0;
    node* next;
    void ins(node &a){
        a.next=this->next;
        this->next=&a;
    }
    void pop(){
        this->next=this->next->next;
    }
    bool operator<(node &a){
        return this->s<a.s;
    }
};
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        node a[n+2],b[m];
        a[0].next=&a[1];
        for(int i=1;i<=n;i++){
            cin>>a[i].s;
            a[i].next=&a[i+1];
        }
        for(int i=0;i<m;i++) cin>>b[i].s;
        sort(b,b+m);
        int f=0;
        for(int i=n;i>0;i--){
            if(a[i].s>=b[f].s){
                a[i].ins(b[f]);
                f++;
                i++;
            }
            if(f==m) break;
        }
        while(f<m){
            a[0].ins(b[f]);
            f++;
        }
        while(a[0].next->s!=0){
            cout<<a[0].next->s<<' ';
            a[0].pop();
        }
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：Msents (赞：0)

纯水贪心

首先肯定的是答案最后不会比原来的答案小，因为无论怎么插入，原来的 LIS 都不会被影响。

再考虑使最后答案最小。

每次插入一个数字时，找到最后一个大于等于它的数字，放在它的后面。

以这个数字为末尾的 LIS 肯定小于等于最后一个大于等于它的数字。

又因为后面没有大于等于它的数字，所以后面的 LIS 也不会更新。

这样答案肯定是最小的。

整一个树状数组维护大于等于一个数字的数字最大编号。

对于插入造成的序号问题，可以直接将插入的数字从大到小排序，然后将它们插入的位置为第一关键字从小到大，值的大小为第二关键字从大到小排序，输出的时候将原来的数字和插入的数字一起输按顺序输出就行。

这样就能保证若插入的数字放在了另一个插入的数字后面，后者一定大于等于前者。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=200000,Inf=1e9+114;
int n,m,a[MaxN+1],b[MaxN+1];
map<int,int>tree;
int LowBit(int x){return(x)&(-x);}
void Modify(int pos,int x){for(;pos<=Inf;pos+=LowBit(pos))tree[pos]=max(tree[pos],x);}
int Ask(int pos){
	int ans=0;
	for(;pos;pos-=LowBit(pos))ans=max(ans,tree[pos]);
	return ans;
}
void Undo(){tree.clear();}
pair<int,int>ans[MaxN+1];
void Solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(b+1,b+1+m,greater<int>());
	for(int i=1;i<=n;i++){
		Modify(Inf-a[i],i);
	}
	for(int i=1;i<=m;i++){
		int res=Ask(Inf-b[i]);
		ans[i]=make_pair(i,res);
		Modify(Inf-b[i],res);
	}
	sort(ans+1,ans+1+m,[](const pair<int,int>&a,const pair<int,int>&b){
		return a.second==b.second?a.first<b.first:a.second<b.second;
	});
	int p=1;
	for(int i=1;i<=n;i++){
		while(p<=m&&ans[p].second<i)cout<<b[ans[p++].first]<<' ';
		cout<<a[i]<<' ';
	}
	while(p<=m)cout<<b[ans[p++].first]<<' ';
	cout<<'\n';
	Undo();
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--)
	Solve();
	return 0;
}
```

---

## 作者：Gmt丶FFF (赞：0)

很明显 $b$ 序列单调不增插入肯定更优。

那么顺序的问题就解决了，现在是位置的问题。

如果一个数大于了后面的所有的数（或后面没数），且前面的那个数大于等于它（或前面没数），那这个数一定不会对 LIS 造成贡献，因为其不能向后面转移，对于前面的转移等同于在前面那个更大的数。

可以知道，这个位置就是在从前往后遍历时，第一次大于后缀最大值的位置。

那么思路就明确了，我们对 $a$ 求一遍后缀最大值，记为 $suf$，然后对 $b$ 单调不增排序，然后从前往后跑双指针，如果当前 $b_i\ge suf_j$ 则插入 $b_i$。

时间复杂度：$O(n+m\log m)$。

感觉比 A 简单。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2e5+5;
vector<int>t[N];
int n,m,a[N],b[N],c[2*N],suf[N];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=n;i>=1;i--)suf[i]=max(suf[i+1],a[i]);
		for(int i=1;i<=m;i++)scanf("%d",&b[i]);
		sort(b+1,b+1+m);
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			while(b[m]>=suf[i])c[++cnt]=b[m--];
			c[++cnt]=a[i];
		}
		while(m)c[++cnt]=b[m--];
		for(int i=1;i<=cnt;i++)printf("%d ",c[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给定两个数组 $a$ 和 $b$，请你把 $b$ 中的元素按任意顺序和位置插入 $a$ 中，最小化最终 $a$ 数组的 LIS 长度。

## 题目分析

看到这道题首先得自信的认为我能不增加 $a$ 的 LIS 长度。考虑贪心。

设当前元素为 $b_i$，要插入 $a$ ，使得 $a$ 的 LIS 长度不变。则我可以找到数组中小于等于 $b_0$ 的最大值的最靠前的位置 $a_j$，放在 $a_j$ 前面，则靠前的数都大于 $b_i$，靠后的数都用 $a_j$ 计算贡献更优。LIS 的长度不变。如果不存在 $a_j$，说明 $b_i$ 已经比所有的 $a_j$ 小了，直接放在最后

如果在 $b_i$ 之后加入的元素 $b_{i+k}$ 小于 $b_i$ 大于 $a_j$。则放在 $b_i$ 和 $a_j$ 的中间才不会被影响，所以我们按照 $b$ 中的元素从小到大插入是绝对可行的。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=2e18,mod=1e9+7;
using namespace std;
int T=read(),n,m,b[N],Id[N];
vector<int>p[N];
inline bool cmp(int a,int b){
	return a>b;
}
struct node{
	int k,id;
}a[N];
bool Cmp(node a,node b){
	return	a.k==b.k?a.id>b.id:a.k<b.k;
}
inline void find(int x){
	int l=1,r=n,ans=n+1;
	while(l<=r){
		if(a[mid].k<=x)ans=mid,l=mid+1;
		else r=mid-1;
	}
	if(ans!=n+1)a[ans].k=x;
	if(ans==n+1)p[n+1].pb(x);
	else p[a[ans].id].pb(x);
}
signed main(){
	while(T--){
		n=read(),m=read();
		rep(i,1,n)a[i]={read(),i};
		rep(i,1,n+1)p[i].clear();
		rep(i,1,n)p[i].pb(a[i].k);
		rep(i,1,m)b[i]=read();
		sort(b+1,b+m+1,cmp),sort(a+1,a+n+1,Cmp);
		per(i,m,1)find(b[i]);
		rep(i,1,n){
			int siz=p[i].size();
			per(j,siz-1,0)cout <<p[i][j]<<' ';
		}
		sort(p[n+1].begin(),p[n+1].end(),cmp);
		E(n+1)cout <<y<<' ';
		cout <<endl;
		
	} 
	return 0;
}
```


---

## 作者：ganpig (赞：0)

首先没必要对 $b$ 进行排序，把 $b$ 中的元素逐个插入 $a$ 中即可。

如果新元素比 $\max a_i$ 还大，扔最前面就好了。

否则，找到 $a$ 中**最小的不小于它的元素**（若出现多次，取最后一个）作为“保护伞”，把它插到“保护伞”后面，可以证明不会有新的贡献：如果原来的 LIS 经过了“保护伞”，只可能从前一个改接到新插入的元素，不会使长度增加，而接到的后一个元素也一定是原来的 LIS 中就有的，不然“保护伞”就不是 $a$ 中最小的不小于它的元素了。

如果多个新元素被插到了同一个位置，从大到小排序即可。

### $\text{Code}$

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
        std::cin >> a[i].fi, a[i].se = i;

    std::sort(a.begin(), a.end(), [](auto x, auto y) { return x.fi == y.fi ? x.se > y.se : x.fi < y.fi; });

    while (m--) {
        int x;
        std::cin >> x;
        auto it = std::lower_bound(a.begin(), a.begin() + n, std::make_pair(x, INT_MAX),
            [](auto x, auto y) { return x.fi == y.fi ? x.se > y.se : x.fi < y.fi; });
        a.emplace_back(x, it == a.begin() + n ? -1 : it->se);
    }

    std::sort(a.begin(), a.end(), [](auto x, auto y) { return x.se == y.se ? x.fi > y.fi : x.se < y.se; });

    for (auto x : a)
        printf("%d ", x.fi);
    putchar('\n');
}

int main() {
    int T;
    std::cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：robinyqc (赞：0)

这题我居然赛时想了这么久。浪费了前三题的手速。

### 题意简述

给定序列 $a, b$，长度分别为 $n, m$。求满足下列要求的，最长上升子序列长度最小的序列 $c$：

+ $a$ 是 $c$ 的子序列。
+ 将 $a, b$ 合并成一个序列并重新排列后可以得到 $c$。（或者说，$c$ 是向 $a$ 中任意位置插入 $b$ 数组中的元素得到的。）

### 解题思路

首先，因为 $a$ 是 $c$ 的子序列，所以 $c$ 序列 LIS 长度的下界是 $a$ 的 LIS 的长度。

观察样例我们发现一个很显然的性质：若 $b_i$ 在 $a$ 中出现过，假设 $a_j = b_i$，那么我们直接把 $b_i$ 放在 $a_j$ 后面就好了。发现这样不发生任何影响。

进一步地，可以发现，设 $x$ 为 $a$ 中大于等于 $b_i$ 的最小值，若把 $b_i$ 放在 $a$ 中最后一个等于 $x$ 的元素 $a_j$ 的后面，也不会对原序列的 LIS 造成任何影响：以它结尾的 LIS 长度小于等于以 $j$ 结尾的 LIS 长度，而它后面比它大的数也一定比 $a_j$ 大，所以从 $j$ 转移一定比它优，导致对后面的也没有影响。

所以这样做，我们可以保证 $c$ 的 LIS 长度等于 $a$ 的 LIS 长度。模拟这个过程即可通过此题。

### 代码实现



```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

int n, m, a[200005];
vector<int> nxt[200005];

void solve()
{
    cin >> n >> m;
    map<int, int> pos;
    for (int i = 0; i <= n; i++) nxt[i].clear();
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]] = i;
    pos[1000000001] = 0;
    for (int i = 1, b; i <= m; i++) {
        cin >> b;
        auto x = pos.lower_bound(b);
        nxt[x->second].push_back(b);
    }
    for (int i = 0; i <= n; i++) {
        if (i > 0) cout << a[i] << ' ';
        sort(nxt[i].begin(), nxt[i].end(), greater<>());
        for (int j : nxt[i]) cout << j << ' ';
    }
    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：eastcloud (赞：0)

好清新的构造题。

我们先考虑一些尽量小的构造，一个比较容易发现的方案是将 $b$ 倒序随意插入 $a$ 中，由于 $b$ 中只要有一个参与构成最长上升子序列，其他的就不可能参与，因此此时 $\operatorname{LIS}(a)\leq\operatorname{LIS}(c) \leq \operatorname{LIS}(a)+1$。

这个限制还算比较宽松，我们继续考察有没有使得 $\operatorname{LIS}(a)=\operatorname{LIS}(c)$ 的构造，考虑加入 $b$ 对序列可能造成的影响：要么成为一个新的结尾使长度加一，要么成为一个新的连接点连接前后并使长度加一。

对于第一个影响，可以发现只有插入 $b_i$ 时前面的数大于 $b_i$ 时才有可能完全避免，因为此时任意一条连到 $b_i$ 的边都可以换成连到前方那个大于它的数上。

对于第二个影响，要么 $b_i$ 小于前面所有点，要么其大于后面所有点，由于前面这个条件加入后与影响一带来的条件有点重合，且二者合并后也无法提供一个具体的构造方案，因此我们选取后面的条件与影响一带来的条件合并。

此时，$b_i$ 的位置则被唯一限定为 $a$ 中从后往前第一个大于它的数的后面，只要将 $b$ 排序简单模拟即可。

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#define N 500005
using namespace std;
int a[N],b[N];
vector<int> ans;
void solve(){
	int n,m,pos=1;cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(b+1,b+m+1);
	while(pos<=m && b[pos]<a[n])ans.push_back(b[pos]),pos++;
	for(int i=n;i>=1;i--){
		while(pos<=m && b[pos]<a[i])ans.push_back(b[pos]),pos++;
		ans.push_back(a[i]);
	}
	while(pos<=m)ans.push_back(b[pos]),pos++;
	reverse(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)cout<<ans[i]<<' ';
	ans.clear();cout<<endl;
}
int main(){
	int T;cin>>T;while(T--)solve();
}
```


---

## 作者：sgl654321 (赞：0)

## 题目大意
给定两个序列 $a,b$，将 $b$ 中所有元素以任意顺序在任意位置插入 $a$ 中，使得形成的新序列 $c$ 的最长上升子序列最短，输出你的序列 $c$。

## 解题思路
设 $a$ 的 LIS 长度为 $s$。下证：$c$ 的 LIS 长度最小值也是 $s$，即存在一种构造方案使得插入元素后最长上升子序列不变。

首先我们考虑 $a$ 是一个单调不上升的序列。那么显然你会把大于 $a_1$ 的数插入到 $a_1$ 前面，在 $a_1$ 和 $a_2$ 之间的数插入到 $a_2$ 前面……**在 $a_i$ 和 $a_{i+1}$ 之间的数插入到 $a_{i+1}$ 前面**，小于 $a_n$ 的数插入到数列最后。

当然你插入的时候肯定是**从大到小**插入的，这个毫无疑问。然后你就能使得插入元素后，序列的 LIS 长度仍然为 $0$。

那么如果 $a$ 是一个一般性的序列，我们也能类似考虑。若 $a_i\ge a_{i+1}$，我们就把 **$[a_{i+1},a_i]$ 之间的数从大到小插入到 $a_{i+1}$ 前面**即可。特殊的，我们把**大于 $a_1$ 的数插到最前面，小于 $a_n$ 的数插到最后面**。

由于你这样插入之后，这些插入的数 $b_i$ 都不可能对答案产生贡献。同时，可以证明你一定会把所有的 $b$ 给插完。因此你 LIS 的长度不变。

举个例子， $\{a\}=\{10,6,1,8,5,11\}$，其 $\text{LIS}$ 长度为 $3$。而要插入的 $\{b\}=\{13,8,7,5,4\}$。

那么你就把 $13$ 插入到 $a_1=10$ 前面，$8,7$ 插入到 $a_2=6$ 前面，$5,4$ 插入到 $a_3=1$ 前面即可。

$\{c\}=\{\color{red}{13},\color{black}10,\color{red}{8,7},\color{black}6,\color{red}{5,4},\color{black}{1},8,5,11\}$。红色的数对答案没有任何贡献，LIS 长度仍然为 $3$。

## 实现思路
为了找到序列中属于 $[l,r]$ 的数，并将其删除，我们可以考虑使用平衡树或者直接用 ``std::multiset`` 实现。相信大家一定都会，这里不展开叙述。

## 注意点
1. 某同学在打 cf 的时候错误提交 $5$ 遍也不知道哪里错了。最后发现 `multiset` 打成了 `set`。

2. 注意特殊处理开头和结尾。

3. `multiset` 中删除元素要删除其迭代器，而不是删除这个数值，不然所有相等的数都没了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define maxn 600010
using namespace std;
typedef long long ll;
ll tt,n,m,a[maxn],b[maxn],num;
multiset<ll,greater<ll>>s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>tt;
	while(tt--){
		s.clear();
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=m;i++){
			cin>>b[i];
			s.insert(b[i]);
		}
		a[n+1]=-1145141919810;
		while(!s.empty()){
			auto it=s.lower_bound(1145141919810);
			if(it==s.end())break;
			num=*it;
			if(num>=a[1])
				s.erase(it);
			else break;
		}
		for(int i=1;i<=n;i++){
			while(!s.empty()){
				auto it=s.lower_bound(a[i]);
				if(it==s.end())break;
				num=*it;
				if(num>=a[i+1])s.erase(it);
				else break;
			}
		}
		cout<<endl;
	}
	return 0;
}


```


---

