# Fill the Matrix

## 题目描述

There is a square matrix, consisting of $ n $ rows and $ n $ columns of cells, both numbered from $ 1 $ to $ n $ . The cells are colored white or black. Cells from $ 1 $ to $ a_i $ are black, and cells from $ a_i+1 $ to $ n $ are white, in the $ i $ -th column.

You want to place $ m $ integers in the matrix, from $ 1 $ to $ m $ . There are two rules:

- each cell should contain at most one integer;
- black cells should not contain integers.

The beauty of the matrix is the number of such $ j $ that $ j+1 $ is written in the same row, in the next column as $ j $ (in the neighbouring cell to the right).

What's the maximum possible beauty of the matrix?

## 样例 #1

### 输入

```
6
3
0 0 0
9
4
2 0 3 1
5
4
2 0 3 1
6
4
2 0 3 1
10
10
0 2 2 1 5 10 3 4 1 1
20
1
1
0```

### 输出

```
6
3
4
4
16
0```

# 题解

## 作者：一扶苏一 (赞：9)

# 【单调栈】【CF1841E】Fill the Matrix

## Description

有一个 $n$ 行 $n$ 列的矩阵，行和列都从 $1$ 到 $n$ 编号。对于第 $i$ **列**，第 $1 \sim a_i$ 个格子是黑色的，其余格子是白色的。

你可以把 $1 \sim m$ 共 $m$ 个整数放到矩阵里，满足两条规则：

1. 每个格子包含至多一个整数。
2. 黑色格子不能包含整数。

一个矩阵的美丽程度是满足这样的格子个数：该格子自身包含一个数 $j$，且它右边与它相邻的格子包含的数为 $j + 1$。

请求出矩阵的最大美丽值。

多组数据，$n$ 之和不超过 $2 \times 10^5$，请注意 $m$ 的大小可能超过 32 位整数所存储的范围。

## Analysis

我们自然关注那些横向的极长连续段，考察他们的贡献。例如，假设给出的矩阵状态是图 $1$，我们关注的是图二中被涂上相同颜色的那些横向连续的格子段。

![](https://cdn.luogu.com.cn/upload/image_hosting/i27lxedj.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/pgix2dkh.png)

对于一个长度为 $\mathrm{len}$ 的格子段，我们向其中放入 $len$ 个数，可以得到 $len - 1$ 的贡献。假设我们有 $m$ 个数可填，一共填充了 $k$ 个格子段，则得到的美丽值就是 $m - k$。$m$ 是个定值，因此我们希望 $k$ 尽量小。于是当有多个格子段可填的时候，我们自然希望填充更长的格子段。这就是填数的策略。

于是问题转化成了维护出每种长度的格子段各有多少个。这是一个能用单调栈解决的经典问题：

对于 $a$ 数列的一个前缀 $a_1 \sim a_i$，以第 $i$ 列为右端点（开）的那些格子段的左端点只可能是这个前缀的那些后缀最大值。对于这个前缀的两个（在单调栈内）相邻的后缀最值 $a_j, a_k$，设 $a_i > a_j > a_k$，则以第 $j$ 列为左端点（开）的区间格子段个数就是 $a_k - a_j$，其长度是 $i - j - 1$。于是在弹栈的时候顺手维护出所有的极长格子段长度就可以了。需要特殊处理的是弹完栈栈仍不为空，此时贡献的格子段个数与 $a_i$ 和上一个被弹栈的数相关。

接下来按照长度从大到小枚举所有的段，设长度为 $\mathrm{len}$ 的段共有 $\mathrm{cnt}$ 个。假设当前剩余能填的数 $m \geq \mathrm{cnt} \times \mathrm{len}$，则直接把这些段填满，更新 $m$ 的值；否则首先可以填满 $\left\lfloor\dfrac{m}{\mathrm{len}}\right\rfloor$ 个段，计算其贡献，剩余 $m \bmod \mathrm{len}$ 个数填在一个不满的段里，会产生 $m \bmod \mathrm{len} - 1$ 的贡献。这里需要特判 $m$ 整除 $\mathrm{len}$ 的情况。

时间复杂度 $O(n)$，代码用 map 维护了长度（事实上长度最大到 $n$，直接开桶即可），所以是一个 $O(n \log n)$ 的写法。

## Code

```cpp
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

int T;

typedef long long int ll;

int main() {
#ifndef ONLINE_JUDGE
  freopen("data.txt", "r", stdin);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  auto read = []() { int x; std::cin >> x; return x; };
  for (std::cin >> T; T; --T) {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 2);
    std::generate(a.begin() + 1, a.end() - 1, read);
    a[0] = n;
    a[n + 1] = n;
    ++n;
    long long m;
    std::cin >> m;
    std::vector<int> Q;
    std::map<int, ll> c;
    Q.push_back(0);
    for (int i = 1; i <= n; ++i) {
      if (a[i] >= a[i - 1]) {
        int prev = a[Q.back()];
        Q.pop_back();
        while (!Q.empty() && a[Q.back()] <= a[i]) {
          c[i - Q.back() - 1] += a[Q.back()] - prev;
          prev = a[Q.back()];
          Q.pop_back();
        }
        if (!Q.empty()) {
          c[i - Q.back() - 1] += a[i] - prev;
        }
      }
      Q.push_back(i);
    }
    std::vector<std::pair<int, ll>> v;
    for (auto t : c) v.push_back(t);
    std::reverse(v.begin(), v.end());
    long long ans = 0;
    for (auto [len, cnt] : v) if (len != 1) {
      if (len * cnt <= m) {
        ans += cnt * (len - 1);
        m -= len * cnt;
      } else {
        long long k = m / len;
        ans += k * (len - 1);
        m -= k * len;
        if (m != 0) ans += m - 1;
        m = 0;
      }
      if (m == 0) break;
    }
    std::cout << ans << '\n';
  }
}
```

---

## 作者：_edge_ (赞：5)

挺简单的一个题？

首先，肯定有大的空隙优于小的空隙，这个证明也非常简单，只需要考虑不会产生的贡献的点，发现如果选小的，则一定不优。

然后现在我们只需要去找出所有的空隙，但是很遗憾，这是 $n^2$ 级别的。

那这时候可以去研究这个矩阵给出的形式，发现每一行改变的数量的总和不超过 $n$ 个，也就是说，很多空隙都是这样继承下来的。

于是如果我们可以找出改变了某个点状态之后，包含这个点的空隙大小，以及最左边挡住他的点，最右边挡住它的点就可以了，这样就能算出来每个空隙它所存在的时间，上述可以利用链表很简单的维护。

思路挺自然的。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int INF=3e5+5;
int b[INF],n,a[INF],sum2[INF],aa[INF],sum3[INF],L[INF],R[INF],num[INF],tot;
vector <int> v3[INF];
void solve() {
    cin>>n;int ans=0,sum=0,sum1=0;
    for (int i=0;i<=n+3;i++) vector <int> ().swap(v3[i]);
    for (int i=0;i<=n+3;i++) num[i]=0;
    for (int i=1;i<=n;i++) {
        cin>>a[i];
        v3[a[i]].pb(i);
    }
    for (int i=0;i<=n+1;i++) L[i]=i-1,R[i]=i+1;
    int m=0;cin>>m;
    for (int i=1;i<=n;i++) {
        for (int j:v3[i-1]) {
            // sum1+=(R[j]-L[j]-1);
            int E=n;
            if (R[j]<=n) E=min(E,a[R[j]]);
            if (L[j]>=1) E=min(E,a[L[j]]);
            num[R[j]-L[j]-1]+=E-i+1;
            L[R[j]]=L[j];
            R[L[j]]=R[j];
        }
    }
    // cout<<num[5]<<" qweqew?\n";
    for (int i=n;i;i--) {
        if (!m) break;
        if (m>=num[i]*i) ans+=num[i]*(i-1),m-=num[i]*i;
        else {
            ans+=(i-1)*(m/i);
            m%=i;
            // while (m>=i) {
            //     m-=i;
            //     ans+=i-1;
            // }
            if (m) ans+=m-1;
            break;
        }
    }
    cout<<ans<<"\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    int t=0;cin>>t;
    while (t--) solve();
    return 0;
}
```


---

## 作者：caoshuchen (赞：3)

# [Fill the Matrix](https://www.luogu.com.cn/blog/caoshuchen/fill-the-matrix-zhong-zhuai)

## 前言

这是一道为数不多的我能自己做出来的 CF 评分 $2000$ 以上的题目

## 思路

肯定是先要贪心出如何填数才能保证最大美丽值。我们发现，如果我们横着填一个长为 $len$ 的连续数列，那我们就会得到 $len-1$ 的美丽值，那就不难发现，最开始我们的美丽值是 $m$，然后我们每填一个这样的连续数列，美丽值就会减少 $1$，所以问题就转换成：最少需要填多少个连续数列才可覆盖 $m$ 个空格。于是，就可以引申出 $2$ 种方法。

### 法一

这个方法好想，难写，效率低。

首先，我们发现，自下而上，最长连续空格串的长度会越来越短，所以我们的方法是：

设一个一位数组 $block$，存储这个格子现在是否为黑。

应该从下而上依次找到最长的那个串，然后覆盖它，随后把这一段的访问高度往上升 $1$，此时这个长串可能会因为上面有黑格而断开，所以我们需要把 $block$ 在区间内黑色的格子标记为黑，但是区间外不需要。这样依次递推即可。

我们发现以上操作和题目 [Glass Carving](https://www.luogu.com.cn/problem/CF527C) 有异曲同工之妙，都是把序列割开，不过一个是把两个块之间的边割掉，一个是直接把格子割掉，我们其实就是用线段树维护最长和去除最左边的区间后的最长，然后依次递推等等，不细说了，看代码。

口说不明，见图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xf7yqzgk.png)

从下往上看

第一、二行都是空白不说，第三行，我们把 $1,10$ 涂黑，注意，此时我们只有 $[1,10]$ 这一段是在第 $3$ 行，其余依然停留在第 $2$ 行的空格。

第四行，涂黑 $3,9$，此时再访问 $(3,9)$，以此类推……

直至第 $5$ 行时，我们应该不再往里面搜了，因为此时 $[12,14]$ 这个 $3$ 空白区间更优于目前的 $[4,5]$ 或 $[7,8]$，注意啊，$[12,14]$ 依然是在第 $2$ 所以不要等同于目前的第 $5$ 行。

但我们发现，如果这样弄，时间复杂度会达到 $O(n^2\log_2n)$，CF 那可是嘎嘎开心，所以不行，需要优化。

我们发现，其实如果当前这个访问的区间，以上 $k$ 行都没有黑色，那么你这 $k+1$ 行肯定它都是最长的那个区间，所以可以直接跳过这 $k$ 行再接着访问。

但此时，我们还需要一个树状数组存储每一个位置当前准备访问的高度，还需要一个 st 表快速访问区间内下一个黑色块的高度，一个 vector 存储当前高度正好是黑色块且下面就是空格的格子的所有位置。

最终复杂度为 $O(C\times n\log_2n)$，$C$ 是一个大常数，不好判断是多少，但可以放心的是，这个复杂度是可以 $AC$ 的。

其实实际这个方法挺好想的，但是说出来不好说，因为它太简单以至于有很多需要考虑的，实在理解不了可以看下一个方法或者看代码。

---

### 法二

我们把图反过来想，最底下的是黑色最多的，那么越往上，空白区间就越长，所以我们可以反着推：

设数组 $l,r$ 存储当前方格的左边格挡和右边格挡，然后从上到下依次访问黑色高度为 $i$ 的列，然后计算这样的长度会维持多久，也就会产生多少个这样长度的区间，这可以通过查询 `它左右边界黑色高度的最小值`$-i$ 得到。然后，我们把左端点、自己、右端点全部连成一个区间即可：$r[l[x]]=r[x],l[r[x]]=l[x]$，注意，这样其实等于把自己给删了，但你想想，由于高度 $i$ 只会访问一次，所以把它删掉不会影响以后操作。

最后就是依次取出长度 $i=n,n-1,...,1,0$ 的区间来填充，直至填满，看看要多少区间即可。

复杂度为 $O(n)$。

## Code

### 法一

```c++
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

//嘿嘿，偷懒，直接用	Glass Carving    的模板 
//嘿嘿，注释不删了（懒得删） 

struct Tag {
	long long a;
	Tag() {
		a = -1;
	}
	Tag(long long A) {
		a = A;
	}
};
struct Value {
	long long mxq, mx2q, ll, lr, len, st, st2;//比 	Glass Carving    多了两个个起点st表示所有的，st2表示去掉后缀的（后缀可能会被修改） 
	Value() {
		st = st2 = ll = lr = mxq = mx2q = len = 0;
	}
	Value(long long lth, int l, int r) {
		st = r, mxq = r - l + 1, st2 = mx2q = 0, len = lth, ll = l, lr = r;
	}
};
Tag operator*(Tag x, Tag y) {//合成两Tag 
	if (y.a == -1)
		return x;
	return Tag(max(x.a, y.a));
}
Value operator+(Value x, Value y) {//合成两Value 
	Value ans;//定义临时答案
	if (x.mxq > y.mxq) 
		ans.mxq = x.mxq, ans.st = x.st;//最大
	else
		ans.mxq = y.mxq, ans.st = y.st;
	ans.ll = x.ll;
	if (x.ll == y.ll) {//在同一块碎玻璃中 
		ans.lr = y.lr;//则最（左/下）端的（右/上）边界是y的 
		ans.mx2q = y.mx2q;
		ans.st2 = y.st2;
		//不包含最（左/下）端的最大玻璃碎片为y的包含最（左/下）端的最大
	}
	else {//不在 
		ans.lr = x.lr;//则最（左/下）端的（右/上）边界是x的 
		if (x.mx2q > y.mxq)
			ans.mx2q = x.mx2q, ans.st2 = x.st2;
		else
			ans.mx2q = y.mxq, ans.st2 = y.st;
		//不包含最（左/下）端的最大玻璃碎片为 max(x的包含最（左/下）端的最大, y的最大)
	}
	ans.len = x.len + y.len;//长度相加 
	return ans;//返回答案 
}
Value operator*(Value x, Tag y) {//Value 和 Tag 进行运算 
	Value ans = x;//定义临时答案
	if (y.a == -1)//不需修改 
		return x;//直接返回 
	ans.ll = max(ans.ll, y.a);//更新左边界 
	if (ans.mx2q > ans.lr - ans.ll + 1)//更新最大 
		ans.mxq = ans.mx2q, ans.st = ans.st2;
	else
		ans.mxq = ans.lr - ans.ll + 1;
	return ans;
}

struct segTree {//一个完整的线段树 
	vector<Value> val;//结点属性 
	vector<Tag> tag;//结点改变量 
	int sz;
	Value ide1 = Value();//val单位元 
	Tag ide2 = Tag();//tag单位元 
	
	void pushdown(int x, int lx, int rx) {
		tag[2 * x] = tag[2 * x] * tag[x];
		tag[2 * x + 1] = tag[2 * x + 1] * tag[x];
		val[2 * x] = val[2 * x] * tag[x];
		val[2 * x + 1] = val[2 * x + 1] * tag[x];
		tag[x] = ide2;
	}
	void pushup(int x, int lx, int rx) {
		val[x] = (val[2 * x] + val[2 * x + 1]) * tag[x];
	}
	void build(int x, int lx, int rx, vector<Value> &a) {//建树 
		if (lx + 1 == rx) {//叶结点 
			//此叶结点在原始区间内，则为原始元素的值，否则为单位元 
			val[x] = (lx <= a.size()) ? a[lx - 1] : ide1;
			return ;//结束 
		}
		int m = (lx + rx) / 2;
		build(2 * x, lx, m, a), build(2 * x + 1, m, rx, a);
		pushup(x, lx, rx);
	}
	Value qry(int x, int lx, int rx, int l, int r) {//查询 
		if (l <= lx && rx <= r)
			return val[x];
		if (rx <= l || r <= lx)
			return ide1;
		int m = (lx + rx) / 2;
		pushdown(x, lx, rx);
		return qry(2 * x, lx, m, l, r) + qry(2 * x + 1, m, rx, l, r);
	}
	void mdf(int x, int lx, int rx, int l, int r, Tag v) {//修改 
		if (l <= lx && rx <= r) {
			tag[x] = tag[x] * v;
			val[x] = val[x] * v;
			return ;
		}
		if (rx <= l || r <= lx)
			return ;
		int m = (lx + rx) / 2;
		pushdown(x, lx, rx);
		mdf(2 * x, lx, m, l, r, v), mdf(2 * x + 1, m, rx, l, r, v);
		pushup(x, lx, rx);
	}
	segTree(vector<Value> &a) {//初始化 
		for (sz = 1; sz < a.size(); sz *= 2);
		val.assign(2 * sz, ide1);
		tag.assign(2 * sz, ide2);
		build(1, 1, sz + 1, a);
	}
	segTree(){}
} st;//这个st是线段树的segTree :)

long long t, n, m;
int a[200005];
int ST[25][200005], lg[200005], pw[25];//这个st是st表  :) 
vector<int> rev[200005];

void init() {
	for (int i = 2; i <= n; i++)
		lg[i] = lg[i / 2] + 1;
	pw[0] = 1;
	for (int i = 1; i <= 20; i++)
		pw[i] = pw[i - 1] * 2;
	for (int i = 1; i <= n; i++)
		ST[0][i] = a[i];
	for (int k = 1; k <= 20; k++)
		for (int i = 1; i + pw[k] - 1 <= n; i++)
			ST[k][i] = max(ST[k - 1][i], ST[k - 1][i + pw[k - 1]]);
}
int qry(int l, int r) {
	int i = lg[r - l + 1];
	return max(ST[i][l], ST[i][r - pw[i] + 1]);
}

struct BIT {
	vector<int> tree;
	int size = 0;
	BIT(){};
	BIT(int x) {
		size = x;
		tree.assign(x + 5, 0);
	}
	inline int lowbit(int x) {
		return x & -x;
	}
	void mdf(int x, int v) {
		while (x <= size)
			tree[x] += v, x += lowbit(x);
	}
	int qry(int x) {
		int sum = 0;
		while (x)
			sum += tree[x], x -= lowbit(x);
		return sum;
	}
} bt;

int main() {
	cin >> t;
	while (t--) {
		scanf("%d", &n);
		long long ans = 0;
		for (int i = 0; i <= n; i++)
			rev[i].clear();
		for (int i = 1; i <= n; i++)
			scanf("%d", a + i), (rev[a[i]].push_back(i));
		scanf("%lld", &m);
		vector<Value> tmp(0);
		for (int i = 1; i <= n; i++)
			tmp.push_back(Value(1, 1, i));
		st = segTree(tmp);
		bt = BIT(n);
		init();
		//如果第一层没有被占，那么循环里是会漏考虑的，单独特判 
		if (qry(1, n) != n) {
			int TMP = n - qry(1, n);
			if (m >= TMP * n)
				m -= TMP * n, ans += TMP * (n - 1), bt.mdf(1, TMP);
			else {
				ans += (m / n) * (n - 1) + max(0ll, m % n - 1);
				m = 0;
			}
		}
		while (m) {
			Value tp = st.qry(1, 1, st.sz + 1, 1, n + 1);
			long long l = tp.st - tp.mxq + 1, r = tp.st;
			if (l == r)
				break;
			long long h = qry(l, r);
			for (auto i : rev[h]) {
				if (i > r)
					break;
				if (i >= l)
					st.mdf(1, 1, st.sz + 1, i, n + 1, Tag(i + 1));
			}
			tp = st.qry(1, 1, st.sz + 1, 1, n + 1);
			l = tp.st - tp.mxq + 1, r = tp.st;
			h = bt.qry(l);
			long long h2 = n - qry(l, r);
			if (m >= (h2 - h) * (r - l + 1))
				m -= (h2 - h) * (r - l + 1), ans += (h2 - h) * (r - l), bt.mdf(l, (h2 - h)), bt.mdf(r + 1, -(h2 - h));
			else {
				ans += (m / (r - l + 1)) * (r - l) + max(0ll, m % (r - l + 1) - 1);
				m = 0;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

### 法二

```c++
#include <bits/stdc++.h>
using namespace std;

long long t, n, m, cnt[200005];
int a[200005], l[200005], r[200005];
vector<int> rev[200005];

int main() {
	cin >> t;
	while (t--) {
		scanf("%d", &n);
		memset(cnt, 0, sizeof(cnt));
		long long ans = 0;
		for (int i = 0; i <= n; i++)
			rev[i].clear();
		for (int i = 1; i <= n; i++)
			scanf("%d", a + i), (rev[a[i]].push_back(i));
		scanf("%lld", &m);
		a[0] = a[n + 1] = n;
		for (int i = 1; i <= n; i++)
			l[i] = i - 1, r[i] = i + 1;
		for (int i = 0; i <= n; i++) {
			for (auto j : rev[i]) {
				int h = min(a[l[j]], a[r[j]]);
				cnt[r[j] - l[j] - 1] += h - i;
				l[r[j]] = l[j];
				r[l[j]] = r[j];
			}
		}
		long long k = 0, sum = 0;
		for (int i = n; i >= 0; i--) {
			if (cnt[i] * i + sum <= m)
				sum += cnt[i] * i, k += cnt[i];
			else {
				k += ceil(1. * (m - sum) / i);
				break;
			}
		}
		printf("%lld\n", m - k);
	}
	return 0;
}

```

---

## 作者：729hao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1841E)
## 思路
- 首先，选更长的白色区间肯定比选短的优，因为有更多的白色方块同时担任了题目中“包含数 $j$”和“包含数 $j+1$”两种方块。  
如图，选天蓝色部分放数肯定比选粉色部分更优。（下图为输入样例 $1$ 的第二、三组数据。）  
![](https://cdn.luogu.com.cn/upload/image_hosting/ody4na5d.png)  
- 又因为黑色方块只会在图的上方，所以图越往上，连续的白色区间长度越短。

所以我们可以找出所有白色区间，用桶统计所有区间的长度，最后按区间长度从大到小放数，直到 $m$ 个数放完为止。

**那怎么找？**  
本蒟蒻没想到~~也不会用~~单调队列和单调栈，只会用 **dfs+RMQ** 来求最大值。
## dfs
可以发现，当我们从下往上扫描整个图时，总会扫到一列（或多列，看为多个一列）黑色方块将整个区间分割为两部分。  
所以我们每次搜索时，找到区间中最高的黑色方块列，同时把区间高度加到对应的桶中。  
递归搜索此列左右两边的部分，直到区间高度为 $0$ 或宽度为 $0$ 为止。

下图更直观地体现了整个 dfs 过程。（下图仍然为输入样例 $1$ 的第二、三组数据。）
![](https://cdn.luogu.com.cn/upload/image_hosting/1ei4mqbi.png)  
抽象成搜索树就是：  
![](https://cdn.luogu.com.cn/upload/image_hosting/j6ep8cht.png)
## RMQ
普通的 RMQ 维护区间的最大值，这里，我们用 RMQ 维护区间最大值的下标。
## 桶
dfs 结束后，从 $n$ 到 $2$ 扫一遍桶，如果长为的 $i$ 区间个数 $\times i<$ 没放的数的个数，则所有区间长为 $i$ 的区间都放数；否则尽量放满这些区间。  
注意不用扫长度为 $1$ 的桶，因为单个白色方块即便放了数也没有贡献。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200005];
long long m,ans,bsk[200005];
//bsk：桶 
int maid[200005][20];
//maid：RMQ，维护区间最大值的下标 
void ST(){
	for(int i=1;i<=n;i++)maid[i][0]=i;
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			if(a[maid[i][j-1]]>a[maid[i+(1<<(j-1))][j-1]])maid[i][j]=maid[i][j-1];
			else maid[i][j]=maid[i+(1<<(j-1))][j-1];
		}
	}
}
int RMQ(int L,int R){
	int k=log(R-L+1)/log(2);
	if(a[maid[L][k]]>=a[maid[R-(1<<k)+1][k]])return maid[L][k];
	return maid[R-(1<<k)+1][k];
}
void dfs(int L,int R,int H){//L：左端点，R：右端点，H：上个区间的最高点高度 
	if(L>R||H<=0)return;
	int lsmaid=RMQ(L,R);
	bsk[R-L+1]+=H-a[lsmaid];
	dfs(L,lsmaid-1,a[lsmaid]);
	dfs(lsmaid+1,R,a[lsmaid]);
}
int main(){
	scanf("%d",&T);
	while(T--){
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			bsk[i]=0;
		}
		scanf("%lld",&m);
		ST();
		dfs(1,n,n);
		for(int i=n;i>=2;i--){
			if(!bsk[i])continue;
			if(m>=bsk[i]*i){
				ans+=bsk[i]*(i-1);
				m-=bsk[i]*i;
				if(m<=1)break;
			}
			else{
				ans+=m/(1ll*i)*(1ll*i-1);
				if(m%(1ll*i)!=0)ans+=m%(1ll*i)-1ll;
				break;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```
时间复杂度 $O(nlogn)$，空间复杂度 $O(nlogn)$，满足题目要求。

---

## 作者：ManInM00N (赞：2)

# 贪心 （ 水题 2200 )

------

## 题意

题目给你一个大小为 $ n $ 的数组 $ a $ ,表示第 $ i $ 列的格子从 $ 1 - a_i $ 是黑色的，剩下的都是白色的，那么我们可以把这张图看成一个山脉地形的竖剖面(地理乱入)，同时题目还给了我们一个 $ m $ 表示我们可以把 $ 1-m $ 填入白色格子中，并且每个格子最多填入一个数字(每个数字只能填一次)，答案要求我们输出填充完数字后，每行内每一组连续的数字是一个公差为 $ 1 $ 的等差序列的长度 $ -1 $ 。

------

## 解法思路

手玩样例可以发现，如果一个等差序列的长度为 $ x $ 那么他的贡献就是 $ x - 1 $ ，毛估估想，他的长度越长那么贡献的性价比就越大。
既然我们把它看成一张竖剖图，我们可以用一根线从上到下扫描他所覆盖的空白格子，那么我们可以用优先队列将每次扫描到的区间存起来，贪心选择他的长度，然后缩短区间，如法炮制。

![](https://raw.githubusercontent.com/ManInM00N/Pics/main/20240402210813.png)

这样的操作，我们就需要用到优先队列来维护，当区间扫下来遇到隔断时，就对 $ [ l , r ] $ 这个区间进行拆分，为了避免一些极端情况，我们用 ST 表来维护区间的最大值，即当剩下的区间是满足高度条件，但是走完这段区间会浪费很多时间，因此对剩下的区间查询最大的高度是否小于我需要的高度可以做到提前跳出循环避免超时。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e6 + 7;
const int N = 2e5+7;
const int INF = 0x3f3f3f3f;
ll n, m, cnt, k, x, y, z;
#define ls p << 1
#define rs p << 1 | 1
#define Pa pair<ll, ll>
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define rep(i,n) for(int i = 0; i < (int)n; i++)
#define FOR(n) for(int i = 0; i < (int)n; i++)
#define repi(i,a,b) for(int i = (int)a; i < (int)b; i++)
ll st[N][20];
void init(){
    for (int k = 1; k < 20; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (i+(1ll<<(k-1))<=n)
                st[i][k]= max(st[i][k-1],st[i+(1ll<<(k-1))][k-1]);
        }
    }
}
ll query(ll l,ll r){
    ll len = log2(r-l+1);
    return max(st[l][len],st[r-(1ll<<(len))+1][len]);
}
struct pos{
    ll l,r,h;
    bool operator<(const pos& a) const{
        return r-l< a.r-a.l;
    }
};
void solve()
{
    cin >>n ;
    vector<ll> a(n+2);
    repi(i,1,n+1){
        cin >>st[i][0];
        a[i] = st[i][0];
    }   
    cin >>m;
    init();
    priority_queue<pos> q;
    a[0] = n+1;
    a[n+1] = n+1;
    vector<ll> point;
    ll height = n;
    repi(i,1,n+1){
        if (a[i]<height&&((a[i-1]>=height)^(a[i+1]>=height))){
            point.push_back(i);
        }
    }
    for (int i = 0; i < point.size(); i+=2){
        q.push({point[i],point[i+1],n});//把合法区间放进去
    }
    ll ans =0 ;
    auto check=[&](ll l,ll r,ll h)->void{
        ll tt = a[l-1];
        a[l-1] = n+1;
        while(r>=l){
            if (a[r]<h&&a[r-1]<h){
                break;
            }
            r--;//找到第一个有效的右端点
        }
        if (r<=l) return ;
        vector<ll> p;
        while (l<=r){
            if (a[l]<h&&((a[l-1]>=h)^(a[l+1]>=h))){
                p.push_back(l);
            }
            if (query(l,r)<h){
                break;
            }
            l++;
        }
        p.push_back(r);
        for (int i = 0; i < p.size(); i+=2){
            q.push({p[i],p[i+1],h});//区间拆分如法炮制
        }
        a[l-1] = tt;
    };
    while (!q.empty()&&m>0)
    {
        auto [l,r,h] = q.top();
        q.pop();
        ll nxth = query(l,r);//求出这段区间可以贪多少高度
        ll lst = min(h-nxth,m/(r-l+1));
        m-= lst*(r-l+1);
        ans += lst*(r-l);
        if (lst<h-nxth){
            if (m>0)
                ans+=m-1;
            m = 0;
            break;//特判是否填不完
        }
        check(l,r,nxth);
    }
    cout << ans<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll t = 1;
    cin >>t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Null_h (赞：2)

## 前言

在~~偷看~~学习了众多题解的做法后，本人被一堆前缀后缀搞蒙了，故打算写篇详细的题解帮助同样看不懂专业术语的萌新们。


## 思路

首先，对于题目最基本的分析，借用一下扶姑姑的原话以及图片：

“我们自然关注那些横向的极长连续段，考察他们的贡献。例如，假设给出的矩阵状态是图 $1$，我们关注的是图二中被涂上相同颜色的那些横向连续的格子段。”

![](https://cdn.luogu.com.cn/upload/image_hosting/i27lxedj.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/pgix2dkh.png)

好了，不难发现，如果把一条格子段填满，那么第一个格子是不计入贡献的。因此，我们应该尽量选择长的格子段，这样，填的无用格子就最少了。

于是开始考虑如何维护格子段的长度。

首先，如果在最左边及最右边个添加一列黑色格子，那么不难发现，所有的格子段都是由某个黑条（指一列上添加的黑色格子）和它左边第一个不比它短的黑条产生的。例如：图 $2$ 中的绿色格子段就是由第 $5$ 列的黑条与我们添加的第 $0$ 列的黑条产生的。

于是我们看到了一个好东西：“左边第一个大于等于它的数。”妥妥的**单调栈**。

接下来就是一些细节实现。在单调栈中，如果该黑条的长度比栈顶高，就要弹栈及更新长度，注意第一次比较无需记录，格子段数是由上一个被弹的数和栈顶决定的。

至此，该思路可通过此题。

## 代码1

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int> h;
map<int,int> l;
int a[200010];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		h.clear();
		l.clear();
		int n;
		cin>>n;
		a[0]=n;
		h.push_back(0);
		for(int i=1;i<=n+1;i++){
			if(i!=n+1)cin>>a[i];
			else a[i]=n;
			if(a[i]>=a[i-1]){
				int d=a[h.back()];
				h.pop_back();
				while(h.size()&&a[h.back()]<=a[i]){
					l[i-h.back()-1]+=a[h.back()]-d;
					d=a[h.back()];
					h.pop_back();
				}
				if(h.size())l[i-h.back()-1]+=a[i]-d;
			}
			h.push_back(i);
		}
		int q,s=0;
		cin>>q;
		for(auto it=l.rbegin();it!=l.rend();it++){
			int v=it->first,w=it->second;
			if(v==1)break;
			//cout<<"*"<<v<<" "<<w<<endl;
			if(v*w<=q){
				q-=v*w;
				s+=w*(v-1);
			}else{
				s+=q/v*(v-1);
				q-=q/v*v;
				if(q)s+=q-1,q=0;
			}
			if(q==0)break;
		}
		cout<<s<<'\n';
	}
	return 0;
}
```

## 优化

打完代码，对照着最优解的一众大神，我看着自己的用时与内存陷入了沉思。

于是开始了疯狂的优化。

首先，大体的复杂度而言，map 可以用桶替代，果断改！

随后发现第三行的罪恶代码浪费了太多空间，改！

多测方面，可以手写栈来避免清空的复杂度，通过在读入时初始化桶省去循环，细节拉满，改！

以下放改后注释版代码。

## 代码2

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200002],h[200002],top,n,d;
long long l[200002],q,s;//不开多余的long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		a[0]=n;//开头加一列
		top=0;//手写栈，避免清空
		h[++top]=0;
		for(int i=1;i<=n+1;i++){
			l[i]=0;
			if(i!=n+1)cin>>a[i];
			else a[i]=n;//结尾加一列，处理剩余格子段
			if(a[i]>a[i-1]){
				d=a[h[top]];
				top--;
				while(top&&a[h[top]]<a[i]){//不用取等号，对极限数据有很大优化
					l[i-h[top]-1]+=a[h[top]]-d;//添加格子段信息
					d=a[h[top]];
					top--;
				}
				if(top)l[i-h[top]-1]+=a[i]-d;
			}
			h[++top]=i;
		}
		s=0;
		cin>>q;
		for(int i=n;i>1;i--){//桶省了复杂度
			if(l[i]==0)continue;
			if(i*l[i]<=q){//可以全取
				q-=i*l[i];
				s+=l[i]*(i-1);
			}else{
				s+=q/i*(i-1);
				q-=q/i*i;
				if(q)s+=q-1,q=0;//最后剩一条
			}
			if(q==0)break;
		}
		cout<<s<<'\n';
	}
	return 0;
}
```

## 总结

李煜东曾经说过：“虽然很多问题的时间复杂度是有下界的，但从某种程度上说，算法的设计、优化是永无止境的。我们不应该被已有的思维束缚，或只满足于得到 AC，而是尽可能地挖掘、总结一个模型的相关性质，探究其本质。”

虽然这是一道单调栈的典型题目，但我们也可以在细节上追求尽善尽美。同时，我相信，我的代码必然不是最优美的，最简洁的，也一定会有人如我一般不断追求，不断探索。

希望你在追寻的路上找到编程对于自己的快乐与意义，同时把勇于求索的精神传递给每一个人！

---

## 作者：xs_siqi (赞：1)

提供一个好写的 $O(n\log n)$ 方法。

以下将白格称为空格，黑格称为障碍。

首先我们发现数字要填到空格，就是要我们找两边的障碍。我们可以把格子按每行分开来，然后问题就变成了去找障碍，障碍中间就是空格。这是 $O(n^2)$ 的。但这能给我们一些启示。

把格子并回去，然后考虑能不能单格转移。对于每个点找到左右第一大，中间以这个点为最高格的位置之间都是空格。可能这样说有点抽象，请看例子：

```
4 3 2 4
```

那么对于 $3$，显然能找到左右的 $4$，然后可以发现，$3$ 与右边的 $4$ 可以构成一个空格，高度为 $3$，宽度为 $1$。

但是当搜到 $4$ 时，我们发现了这个解法的一个问题：当数相同时也应记。这个好操作，只要在某一次的单调栈时小改单调的判定就行了。为什么只搜一次呢？我们发现左边的 $4$ 右边第一大是右边的 $4$，而右边的 $4$ 左边第一大是左边的 $4$，这样中间高度为 $4$，宽度为 $2$ 的方格就被重复算了两次。因此搜一次就够。

但是我们发现还存在一个问题。当我们找当前格子高度为多少时，我们不能只看当前格状态，还要看当前格和左右第一大之间（不含）最高的格子是多少，因为我当前的格子算空格肯定不能算在这个区间最高格的。显然可证这个区间第一大比两个端点都小（因为这个如果更大，第一大就不会是更右/更左边的了）。

考虑静态区间求最大值，我们可以使用 rmq 来求。但是我忘记怎么写了，所以写了树状数组。

然后就是最后一个问题，怎么把数放到空格里去。

显然看到这个问题我们会很自然地想到背包。但是时间复杂度爆炸。

然后考虑找性质。我们发现必然放连续空格数最大的优。首先我们考虑，放一个长度为 $l$ 的格子，就会得到 $l-1$ 的收益，我们肯定要让放的个数最小。

当 $m\geq l$ 时，肯定要放这个格子。证明显然。

当 $m<l$ 时，也要放这个格子。证明如下：

假如你去放一个连续的格子 $l_2$ 满足 $m<l_2$ 且 $l_2\leq l$，那么这与直接放 $l$ 等价。

假如你去放一个连续的格子 $l_2$ 满足 $m\geq l_2$ 且 $l_2\leq l$，那么这不符合条件“使得放的格子数最小”。

所以我们把格子从大到小处理出来就行。注意到格子值域与 $n$ 同级，所以直接用筒存就行。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int T,n,ans,Max,m,a[maxn],c[maxn],q[maxn],t,l[maxn],r[maxn],cd[maxn];
int lowbit(int x){return x&(-x);}
void modify(int x){
	int y=x;
	while(x<=n){
		c[x]=max(c[x],a[y]);
		x+=lowbit(x);}}
int query(int l,int r){
	int ans=a[r];
	while(l!=r){
		for(--r;r>=l+lowbit(r);r-=lowbit(r))
			ans=max(ans,c[r]);
		ans=max(ans,a[r]);}
	return ans;}
signed main(){
	scanf("%lld",&T);
	while(T--){
		ans=m=Max=0;
		scanf("%lld",&n);
		for(int i=0;i<=n;i++)l[i]=r[i]=c[i]=cd[i]=0;
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]),Max=max(Max,a[i]);
		a[0]=2e15,t=0,q[0]=0;
		for(int i=1;i<=n;i++){
			while(t&&a[q[t]]<=a[i])t--;
			l[i]=q[t];
			q[++t]=i;}
		a[n+1]=2e15,t=0,q[0]=n+1;
		for(int i=n;i>=1;i--){
			while(t&&a[q[t]]<a[i])t--;
			r[i]=q[t];
			q[++t]=i;}
		for(int i=1;i<=n;i++)
			modify(i);
		for(int i=1;i<=n;i++){
			int x=l[i]+1>i-1?0:query(l[i]+1,i-1);
			int y=r[i]-1<i+1?0:query(i+1,r[i]-1);
			cd[i-l[i]-1]+=a[i]-x,cd[r[i]-i-1]+=a[i]-y;}
		cd[n]+=n-Max;
		scanf("%lld",&m);
		for(int i=n;i>=1;i--){
			if(!m)break;
			if(cd[i]){
				if(m>=cd[i]*i){
					ans+=(i-1)*cd[i];
					m-=cd[i]*i;}
				else{
					ans+=(m/i)*(i-1)+max(1ll,m-(m/i)*i)-1;
					m=0;}}}//这里不能用while暴力枚举每一个cd。因为sigma cd可能大于m，时间复杂度爆炸。
		printf("%lld\n",ans);}
	return 0;}
```


---

## 作者：N1K_J (赞：0)

我们注意到如果连续横着放 $L$ 个连续的数将产生 $L-1$ 的贡献（只有最后一个格子不是美丽的）。

我们放置了数格子被分成了 $S$ 个横段，显然每个横段都能产生其长度 $-1$ 的美丽值（填连续的数就行），因此美丽值为 $m-S$。

因此注意到实际上是要取尽可能少的横段，也就是说要从最长的连续极长横段开始选。

注意到如果按照横段来考虑由于可能会有间断，很难考虑，不妨竖着来。

每次不妨来考虑当前最小的一个 $a_i$，注意到设他**左边第一个比他大的项** $l_i$ 和**右边第一个比他大的项** $r_i $将会隔出一个大小为 $(r_i-l_i-1) \times (\min(a_{l_i},a_{r_i})-a_i)$ 的长方体。

不妨参考该图，最上面一行的数字表示了 $a_1,a_3,\cdots,a_n$，红色的格子是不能被放置整数的。

![](https://cdn.luogu.com.cn/upload/image_hosting/qpo59sog.png)

如图所示，最开始我们来考虑最小的 $a_6,a_7,a_8 = 2$。

对于记录左边第一个比该项大的，右边第一个比该项大的，由于我们从小往大找，我们不妨令初始时 $l_i = i-1,r_i = i+1$，特别的，我们定义 $a_0 = a_{n+1} = n$。

当我们解决一个 $a_i$ 时，将 $l_i,r_i$ 合并，即为：`l[r[i]] = l[i],r[l[i]] = r[i];`。

首先，对于这种连续的重复的最小值，由于我们长方体的高是 $\min(a_{l_i},a_{r_i})-a_i$，所以除了最后被我们在代码中计算的一项外，其余的高都是 $0$，不会参与我们的讨论。

对于这张图而言，$a_6,a_7$ 我们因为高为 $0$ 直接不予讨论，接下来来讨论 $a_8$。

此时 $l_8 = 5,r_8 = 9$，这里我们有了一个 $(9-5-1) \times (\min(a_5,a_9)-a_8) = 3 \times 2$ 的矩形，也就是说我们找到了 $2$ 个长度为 $3$ 的横段。

在这之后，令 $r_5 = 9,l_9 = 5$，将两端合并。

显然，这样一来我们对于连续的重复的值只讨论其中一个，并且讨论任意一个 $a_i$ 时 $l_i,r_i$ 刚好是正确的。

这样一来，我们将能不重不漏的统计所有图中的矩形。

这张表最终形态就是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/5me4kvn8.png)

颜色越深，表示越后讨论。

最后我们从大到小讨论所有长度，来使 $m$ 分成尽量少的横段即可。

[Code](https://codeforces.com/contest/1841/submission/280059887)

---

## 作者：Exp10re (赞：0)

喜欢线段树，拦不住的。

Exp 因为最近喜欢玩 PVZ，导致现在思考题目不喜欢带脑子，所以给出一种无脑做法。

## 解题思路

考虑到如果用连续的数填充长度为 $k$ 的白色横行得到的贡献为 $k-1$，启发我们尽可能填充较大的白色横行。

考虑从下往上遍历行，这样一列黑色格子就可以视为从中间某个位置断开白色横行得到两个新的白色横行，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3fng56q6.png)

该操作与 [P1503](https://www.luogu.com.cn/problem/P1503) 类似，随便用线段树或者平衡树维护即可。

本题使用的是线段树做法，具体而言，维护每个白色格子往左和往右能到达最远的格子的位置，那么断开的操作带来的影响显然可以计算得出。

注意到对于一行，其白色横行的不同长度个数最多为 $\sqrt n$ 规模，启发我们使用 multiset 维护不同长度，桶维护个数。

完成维护之后按从大到小的顺序填充并计算贡献即可。

时间复杂度 $O(n^{\frac 3 2})$，对于随机数据基本跑不满。

详情见代码。

## 代码

实现难度瓶颈在两棵线段树。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=200100;
multiset<long long> ex;
multiset<long long>::iterator it;
long long n,cnt[MAXN],pcnt[MAXN];
struct par
{
	long long pos,val;
};
bool cmp(par ta,par tb)
{
	return ta.val>tb.val;
}
par bl[MAXN];
struct segtree
{
	long long l,r,val,lazy;
};
segtree a[MAXN*4],b[MAXN*4];
void builda(long long x,long long l,long long r)
{
	a[x].l=l;
	a[x].r=r;
	a[x].lazy=0;
	a[x].val=0;
	if(l==r)
	{
		a[x].val=1;
		return;
	}
	long long mid=(l+r)/2;
	builda(x*2,l,mid);
	builda(x*2+1,mid+1,r);
	return;
}
void buildb(long long x,long long l,long long r)
{
	b[x].l=l;
	b[x].r=r;
	b[x].lazy=0;
	b[x].val=0;
	if(l==r)
	{
		b[x].val=n;
		return;
	}
	long long mid=(l+r)/2;
	buildb(x*2,l,mid);
	buildb(x*2+1,mid+1,r);
	return;
}
void pushdowna(long long x)
{
	if(a[x].lazy!=0)
	{
		a[x*2].lazy=a[x*2].val=a[x].lazy;
		a[x*2+1].lazy=a[x*2+1].val=a[x].lazy;
		a[x].lazy=0;
	}
	return;
}
void pushdownb(long long x)
{
	if(b[x].lazy!=0)
	{
		b[x*2].lazy=b[x*2].val=b[x].lazy;
		b[x*2+1].lazy=b[x*2+1].val=b[x].lazy;
		b[x].lazy=0;
	}
	return;
}
void inca(long long x,long long l,long long r,long long c)
{
	if(l>r)
	{
		return;
	}
	if(a[x].l==l&&a[x].r==r)
	{
		a[x].lazy=a[x].val=c;
		return;
	}
	pushdowna(x);
	long long mid=(a[x].l+a[x].r)/2;
	if(l<=mid)
	{
		inca(x*2,l,min(mid,r),c);
	}
	if(r>=mid+1)
	{
		inca(x*2+1,max(l,mid+1),r,c);
	}
	return;
}
void incb(long long x,long long l,long long r,long long c)
{
	if(l>r)
	{
		return;
	}
	if(b[x].l==l&&b[x].r==r)
	{
		b[x].lazy=b[x].val=c;
		return;
	}
	pushdownb(x);
	long long mid=(b[x].l+b[x].r)/2;
	if(l<=mid)
	{
		incb(x*2,l,min(mid,r),c);
	}
	if(r>=mid+1)
	{
		incb(x*2+1,max(l,mid+1),r,c);
	}
	return;
}
long long querya(long long x,long long p)
{
	if(a[x].l==p&&a[x].r==p)
	{
		return a[x].val;
	}
	pushdowna(x);
	long long mid=(a[x].l+a[x].r)/2;
	if(p<=mid)
	{
		return querya(x*2,p);
	}
	if(p>=mid+1)
	{
		return querya(x*2+1,p);
	}
}
long long queryb(long long x,long long p)
{
	if(b[x].l==p&&b[x].r==p)
	{
		return b[x].val;
	}
	pushdownb(x);
	long long mid=(b[x].l+b[x].r)/2;
	if(p<=mid)
	{
		return queryb(x*2,p);
	}
	if(p>=mid+1)
	{
		return queryb(x*2+1,p);
	}
}
void del(long long x)
{
	pcnt[x]--;
	if(pcnt[x]==0)
	{
		ex.erase(ex.lower_bound(x));
	}
	return;
}
void add(long long x)
{
	if(pcnt[x]==0)
	{
		ex.insert(x);
	}
	pcnt[x]++;
	return;
}
void work()
{
	long long i,m,k=1,l,r,ans=0,t;
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
	{
		bl[i].pos=i;
		scanf("%lld",&bl[i].val);
		cnt[i]=pcnt[i]=0;
	}
	sort(bl+1,bl+1+n,cmp);
	builda(1,1,n);
	buildb(1,1,n);
	ex.clear();
	add(n);
	scanf("%lld",&m);
	for(i=n;i>=1;i--)
	{
		for(;k<=n;k++)
		{
			if(bl[k].val<i)
			{
				break;
			}
			l=querya(1,bl[k].pos);
			r=queryb(1,bl[k].pos);
			del(r-l+1);
			if(l!=bl[k].pos)
			{
				add(bl[k].pos-l);
			}
			if(r!=bl[k].pos)
			{
				add(r-bl[k].pos);
			}
			inca(1,bl[k].pos+1,r,bl[k].pos+1);
			incb(1,l,bl[k].pos-1,bl[k].pos-1);
		}
		for(it=ex.begin();it!=ex.end();it++)
		{
			cnt[*it]+=pcnt[*it];
		}
	}
	for(i=n;i>=1;i--)
	{
		if(m==0)
		{
			break;
		}
		if(m>=cnt[i]*i)
		{
			ans+=(cnt[i]*(i-1));
			m-=cnt[i]*i;
		}
		else
		{
			t=m/i;
			ans+=(t*(i-1));
			m-=t*i;
			if(m>=1)
			{
				ans+=m-1;
			}
			m=0;
		}
		if(m==0)
		{
			break;
		}
	}
	printf("%lld\n",ans);
	return;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

我们记横着连续的一条是一个块。如果放了 $j$ 个块，那么答案就是 $m-j$，所以目标就是尽量减少 $j$。贪心，先选长的块。

如果目前是 $l\sim r$，前一个最高点的地方为 $h$（开始是 $n$），我们找到最高点 $p$，显然长度为 $r-l+1$ 的段有 $h-a_p$ 条。

代码实现比较简单。

VP 的时候主要因为 xs_siqi 给我做过他出的类似的题目，所以无法评估难度，就直接想到了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls p << 1
#define rs p << 1 | 1
using namespace std;
const int N = 2e5 + 5;
int T, n, a[N], sum[N], maxn[N << 2], m, mm, ans;
inline void init(){
    for(int i = 1; i <= n; i++) sum[i] = 0;
}
inline int Max(int x, int y){
    return a[x] > a[y] ? x : y;
}
inline void build(int p, int l, int r){
    if(l == r){
        maxn[p] = l;
        return ;
    }
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    maxn[p] = Max(maxn[ls], maxn[rs]);
}
inline int query(int p, int l, int r, int x, int y){
    if(x <= l && r <= y) return maxn[p];
    int mid = l + r >> 1, res = 0;
    if(mid >= x) res = Max(res, query(ls, l, mid, x, y));
    if(mid < y) res = Max(res, query(rs, mid + 1, r, x, y));
    return res;
}
inline void solve(int l, int r, int h){
    if(l > r) return ;
    //printf("%lld %lld\n", l, r);
    int p = query(1, 1, n, l, r);
    sum[r - l + 1] += h - a[p];
    solve(l, p - 1, a[p]);
    solve(p + 1, r, a[p]);
}
signed main(){
    scanf("%lld", &T);
    while(T--){
        init();
        scanf("%lld", &n);
        for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
        build(1, 1, n);
        solve(1, n, n);
        scanf("%lld", &m);
        mm = m;
        ans = 0ll;
        for(int i = n; i; i--){
            if(m >= sum[i] * i){
                m -= sum[i] * i;
                ans += sum[i];
            }
            else{
                ans += (m + i - 1) / i;
                m = 0;
            }
        }
        printf("%lld\n", mm - ans);
    }
    return 0;
}
/*
1
3
0 0 0
9
*/
```

---

## 作者：wth2026 (赞：0)

# 题目大意
有一个 $n$ 行 $n$ 列的矩阵，行和列都从 $1$ 到 $n$ 编号。对于第 $i$ **列**，第 $1 \sim a_i$ 个格子是黑色的，其余格子是白色的。

你可以把 $1 \sim m$ 共 $m$ 个整数放到矩阵里，满足两条规则：

1. 每个格子包含至多一个整数。
2. 黑色格子不能包含整数。

一个矩阵的美丽程度是满足这样的格子个数：该格子自身包含一个数 $j$，且它右边与它相邻的格子包含的数为 $j + 1$。

请求出矩阵的最大美丽值。

多组数据，$n$ 之和不超过 $2 \times 10^5$，请注意 $m$ 的大小可能超过 32 位整数所存储的范围。
# 题目思路
运用单调栈维护一下，挺水的。
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")//这五行纯属个人习惯，可以不要

using namespace std;

int n;

struct nood {
    int s, c;
};

stack<nood> a;
map<int, int> mp;
vector<int> b;
int T;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//这三行也纯属个人习惯，用来加速cin、cout的
	
    cin >> T;

    while (T--) {
        while (!a.empty()) {
            a.pop();
        }

        b.clear();
        mp.clear();
        cin >> n;

        for (int i = 1; i <= n; i++) {
            int temp;
            cin >> temp;
            int tep = 0;
            int s = 0;

            while (!a.empty() && a.top().c > n - temp) {
                if (s == 0) {
                    tep = a.top().c;
                } else if (tep > a.top().c) {
                    if (mp.find(s) == mp.end()) {
                        b.push_back(s);
                    }

                    mp[s] += tep - a.top().c;
                    tep = a.top().c;
                }

                s += a.top().s;
                a.pop();
            }

            if (s != 0) {
                if (mp.find(s) == mp.end()) {
                    b.push_back(s);
                }

                mp[s] += tep - (n - temp);
            }

            nood temmp;
            temmp.c = n - temp;
            temmp.s = s + 1;
            a.push(temmp);
        }

        int tep = 0;
        int s = 0;

        while (!a.empty()) {
            if (s == 0) {
                tep = a.top().c;
            } else if (tep > a.top().c) {
                if (mp.find(s) == mp.end()) {
                    b.push_back(s);
                }

                mp[s] += tep - a.top().c;
                tep = a.top().c;
            }

            s += a.top().s;
            a.pop();
        }

        if (mp.find(s) == mp.end()) {
            b.push_back(s);
        }

        mp[s] += tep;
        sort(b.begin(), b.end());
        int k;
        int ans = 0;
        cin >> k;
        int i;

        for (i = b.size() - 1; i >= 0; i--) {
            if (k < mp[b[i]]*b[i]) {
                break;
            }

            ans += (mp[b[i]] * (b[i] - 1));
            k -= mp[b[i]] * b[i];
        }

        if (i >= 0) {
            ans += k / b[i] * (b[i] - 1);

            if (k % b[i]) {
                ans += k % b[i] - 1;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
```

---

