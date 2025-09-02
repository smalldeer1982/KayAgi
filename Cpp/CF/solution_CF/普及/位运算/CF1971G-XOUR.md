# XOUR

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

You can swap the elements at positions $ i $ and $ j $ if $ a_i~\mathsf{XOR}~a_j < 4 $ , where $ \mathsf{XOR} $ is the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the lexicographically smallest array that can be made with any number of swaps.

An array $ x $ is lexicographically smaller than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i < y_i $ .

## 说明/提示

For the first test case, you can swap any two elements, so we can produce the sorted array.

For the second test case, you can swap $ 2 $ and $ 1 $ (their $ \mathsf{XOR} $ is $ 3 $ ), $ 7 $ and $ 5 $ (their $ \mathsf{XOR} $ is $ 2 $ ), and $ 7 $ and $ 6 $ (their $ \mathsf{XOR} $ is $ 1 $ ) to get the lexicographically smallest array.

## 样例 #1

### 输入

```
4
4
1 0 3 2
5
2 7 1 5 6
8
1 2 1 2 1 2 1 2
4
16 4 1 64```

### 输出

```
0 1 2 3 
1 5 2 6 7 
1 1 1 1 2 2 2 2 
16 4 1 64```

# 题解

## 作者：sto__Liyhzh__orz (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF1971G)

从 $a_i \oplus a_j <4$ 入手。

根据定义得：若 $a_i \oplus a_j <4$，当且仅当 $\lfloor \frac{a_i}{4}\rfloor = \lfloor \frac{a_j}{4} \rfloor$。

所以我们可以把满足条件的 $a_i$ 和 $a_j$ 存起来，输出时取堆里最小值即可。

---

## 作者：Gapple (赞：3)

首先考虑题目给的条件：$a_i ⊕ a_j < 4$。若满足条件，则 $a_i$ 与 $a_j$ 的二进制表示中第二位及更高位完全相同，这样只会留下最低两位。

所以我们考虑用 $a_i$ 的第二位及更高位的部分进行分组。如 $(1110)_2$ 和 $(1101)_2$ 会分入一组，但 $(1100)_2$ 和 $(1000)_2$ 不会分入一组。

之后对于每组，我们分别在原数组中排序即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

struct Hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve()
{
    int n;
    vector<int> arr;
    unordered_map<int, vector<int>, Hash> idx;
    
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        idx[x >> 2].emplace_back(i);
        arr.emplace_back(x);
    }

    unordered_map<int, int, Hash> pos;

    for (auto& [_, i] : idx)
        sort(i.begin(), i.end(), [&arr](int u, int v) { return arr[u] < arr[v]; });

    for (int i = 0; i < n; ++i)
        cout << arr[idx[arr[i] >> 2][pos[arr[i] >> 2]++]] << ' ';

    cout << '\n';
}

int main()
{
    int t;
    cin >> t;

    while (t-- > 0)
        solve();

    return 0;
}
```

---

## 作者：Harry1000 (赞：3)

前置知识：[位运算](https://oi-wiki.org/math/bit/)，[快速排序](https://oi-wiki.org/basic/quick-sort/)，[二分查找](https://oi-wiki.org/basic/binary/)
# 题目大意
给出一个序列 $A$，如果 $A_i\oplus A_j<4$，那么可以交换 $A_i$ 和 $A_j$。经过若干次交换后，输出字典序最小的序列。
# 思路 & 做法
如果题目中没有 $A_i\oplus A_j<4$ 这个限制，那么这道题就是一道排序题。但题目增加了这一条限制，所以我们可以观察什么样的两个数可以进行交换。  
因为 $A_i\oplus A_j<4$，所以 $A_i\oplus A_j$ 只能等于 $0/1/2/3$。让我们对这 $4$ 种情况进行分类讨论。  
当 $A_i\oplus A_j=0$ 时，$A_i=A_j$。  
当 $A_i\oplus A_j=1$ 时，$A_i$ 与 $A_j$ 二进制的最后一位不同。  
当 $A_i\oplus A_j=2$ 时，$A_i$ 与 $A_j$ 二进制的倒数第二位不同。  
当 $A_i\oplus A_j=3$ 时，$A_i$ 与 $A_j$ 二进制的最后两位不同。  
综上所述，当两个数**二进制的最后两位不同时**，两个数可以交换。  
那这有什么用呢？  
因为序列的字典序要最小，所以序列要尽可能按按从小到大排列，即**前面的数要尽可能小，后面的数要尽可能大**。  
所以我们可以**把能交换的数分成一组**，接着对原序列从前往后遍历，把前面的数**交换成它能交换的最小数字**。  
那如何分组呢？  
因为能交换的两个数的二进制除了最后两位都一样，所以我们们可以把**每个数除以 $4$（即右移 $2$）**，提取它除了最后两位的部分，把它存到数组里，然后对这个数组进行排序，这样就可以把能交换的数分成一组。  
接着，我们把**每一组里的数字从小到大排好序**，方便提取第几小的数。  
最后，对于每个数 $A_i$，我们利用**二分查找找到它所在的组别**，再找出组别里对应小的数(如果它在原序列的位置在这个组别里排名第 $1$，那么就是这个组别里第 $1$ 小的数，如果是第 $2$ 就是第 $2$ 小的数)，把它输出，这样就完成了这道题。  
时间复杂度为 $O(tn\log n)$。
# 参考代码
```cpp
#include<bits/stdc++.h>
#define fo(i,x,y) for(int i=x;i<=y;i++) 
using namespace std;
int a[200001],b[200001][3];
void qsort(const int l,const int r,const int &x)//快速排序 
{
	if(l>=r)
		return;
	const int mid=b[l+r>>1][x];
	int i=l,j=r;
	while(i<=j)
	{
		while(b[i][x]<mid)
			i++;
		while(b[j][x]>mid)
			j--;
		if(i<=j)
		{
			swap(b[i],b[j]);
			i++;
			j--;
		}
	}
	qsort(l,j,x);
	qsort(i,r,x);
}
int main()
{
	int n,m;
	scanf("%d",&n);
	fo(i,1,n)
	{
		scanf("%d",&m);
		fo(j,1,m)
		{
			scanf("%d",&a[j]);
			b[j][0]=a[j];//下标为0表示原数 
			b[j][1]=a[j]>>2;//下标为1表示原数右移2 
			b[j][2]=0;//下标为3表示当前组别取到第几小的数字 
		}
		qsort(1,m,1);//对能交换的进行分类 
		int x=1;
		fo(j,1,m)//对组内从小到大排序 
		{
			if(b[j][1]>b[j-1][1])
				x=j;
			if(j==m||b[j][1]<b[j+1][1])
				qsort(x,j,0);
		}
		fo(j,1,m)
		{
			int l=1,r=m,mid;//二分查找组别 
			while(l<=r)
			{
				mid=l+r>>1;
				if(b[mid][1]<a[j]>>2)
					l=mid+1;
				else
					r=mid-1;
			}
			printf("%d ",b[l+b[l][2]++][0]);//输出组别里第b(l,2)的数（b(l,2)即此数在组别里的排名） 
		}
		printf("\n");
	}
	return 0;
}
```
## 后记
这是本人第一次使用 Markdown，也是第一次在洛谷写题解。如果有什么改进建议，请多多指教，本人不胜感激！

---

## 作者：JXR_Kalcium (赞：3)

## 题目大意
现有 $N$ 个非负整数 $a_i$，如果 $a_i\oplus a_j<4$，那么就可以交换 $a_i$ 和 $a_j$。现在要使交换任意若干次后的 $a[]$ 字典序尽量小，问交换后的 $a[]$。

## 解题思路
题目中最奇怪的地方在于为什么异或后的值要小于 $4$，就从这入手。

根据定义可以很轻松地发现，如果 $a_i=a_j$，那么 $a_i\oplus a_j=0$；如果 $a_i$ 和 $a_j$ 最后一位不相同，其它位都相同，那么 $a_i\oplus a_j=1$。以此类推，当 $a_i$ 和 $a_j$ 异或值小于 $4$ 时，只有**除了后 $2$ 位之外的所有位相同**才可以（后 $2$ 位是什么已经不重要了），那么就可以通过把 $a_i$ 和 $a_j$ 都除以 $4$，如果它们相等那么就证明可以交换，放进同一堆里。

然后，为了使字典序尽量小，我们可以把同一堆用优先队列存起来（因为 $0\le \displaystyle \frac{a_i}{4}\le 2.5\times 10^8$，所以要用 `map` 来储存优先队列），最后再重新遍历一遍 $a[]$，每次从堆里取相应的最小数输出即可。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,a[200001];

int main()
{
	scanf("%d",&t);
	
	while(t--)
	{
		scanf("%d",&n);
		map<int,priority_queue<int> > mp;
		for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]), mp[a[i]/4].push(-a[i]);
        // 小根堆
		
		for(int i=1; i<=n; ++i)
		printf("%d ",-mp[a[i]/4].top()), mp[a[i]/4].pop();
		printf("\n");
	}
	
	return 0;
}
```

---

## 作者：FiraCode (赞：1)

显然的，由于要求 $a_i \oplus a_j < 4$，那么我们对于二进制就不管最后的两位。

那么就让所有的数把后两位去掉，然后排个序，对于此时相同的数可以随便换，所以直接贪心选然后放到原序列中即可。

---

## 作者：L_xcy (赞：1)

[G. XOUR](https://codeforces.com/contest/1971/problem/G)

---

### 题目大意

给你一个整数 $n$ 和 $n$ 个 $a_i$，如果 $a_i \oplus a_j < 4 (1 \le i,j \le n)$ 那么就可以交换 $a_i$ 和 $b_i$，最后使 $a$ 数组尽量从小到大排序。

---

### 解题思路

当你看完题的时候，就要敏锐地想到为什么要异或小于 4，这是个很有趣的点。

如果你拿几个数试一下，就会发现当两个数都除以 4（下取整）相同时，这两个数异或就小于 4。

也就是说这道题实际上是在问我们把每个 $a_i$ 除以 4 相同的数放在同一个组，最后把每个 $a_i$ 所在的组中最小的数输出来（代表它们可以交换）然后删掉。

对于维护每一个组，官方题解（我看了）用的是优先队列，所以时间复杂度为 $O(N \log N)$。

---

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
void solve() {
	int n,a[200005];
	map< int , priority_queue<int> > q;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		q[a[i]>>2].push(-a[i]);
	}
	for(int i=1;i<=n;i++) {
		cout<<-q[a[i]>>2].top()<<' ';
		q[a[i]>>2].pop();
	}
	cout<<'\n';
}
signed main() {
	cin>>T;
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：0)

$a_i \oplus a_j<4$ 等价于 $\lfloor \frac{a_i}{4} \rfloor=\lfloor \frac{a_j}{4} \rfloor$。

所有除四下取整相同的 $a_i$ 都可以按照原来的位置排序，我实现上是塞进了 multiset。

```
const int N=2e5+10;
int n;
int a[N];
map<int,multiset<int> > ma;
void solve()
{
  ma.clear();
  n=R;
  fo(i,1,n) a[i]=R,ma[a[i]>>2].insert(a[i]);
  fo(i,1,n)
  {
    int tmp=(a[i]>>2);
    write((*ma[tmp].begin())),pc(' ');
    ma[tmp].erase(ma[tmp].begin());
  }
  puts("");
}
```

---

## 作者：Kindershiuo (赞：0)

# 解题思路
两个整数之间的 $\operatorname{XOR}$ 操作的结果小于 $4$ 的条件是：两个整数的二进制表示在低位上只有 $0,1,2$ 或 $3$ 的差异。
具体来说，我们可以交换满足以下条件的数对：

相等的数：$a_i\oplus a_j=0$

数值差为 $1$ 的数：$a_i\oplus a_j=1$

数值差为 $2$ 的数：$a_i\oplus a_j=2$

数值差为 $3$ 的数：$a_i\oplus a_j=3$

换句话说，满足条件的数对之间差异很小，因此可以进行局部交换。

我们的目标是尽可能地在允许的交换范围内对数组进行排序。
1. 块划分：将数组元素按 $a_i\div4$ 进行分组，每个组内的元素都可以相互交换。例如，如果元素为 $0$ 到 $3$，那么 $a_i\div4=0$；如果元素为 $4$ 到 $7$，那么 $a_i\div4=1$，以此类推。
2. 块内排序：对每个分组内的元素进行排序，因为在同一个分组内可以任意交换，最终实现块内的排序。
3. 拼接结果：将每个分组内的有序元素合并，形成一个最终的有序数组。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T;

void solve() {
	int n;
	cin >> n;
	int a[n + 5];
	map<int, int>ma_index;
	map < int, priority_queue<int, vector<int>, greater<int>>>ma;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		int t = a[i] / 4;
		ma[t].push(a[i]);
		ma_index[i] = t;
	}
	for (int i = 1; i <= n; i++) {
		int t = ma[ma_index[i]].top();
		cout << t << " ";
		ma[ma_index[i]].pop();
	}
	cout << endl;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：kimi0705 (赞：0)

考场 5 分钟切的简单题。由 $a_i \oplus a_j<4$ 得：$\lfloor\frac{a_i}{4}\rfloor=\lfloor\frac{a_j}{4}\rfloor$。想到放入一个桶（map）。把里面的值从小到大排序，在一个个填充到答案数组中。

code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
int arr[200005], ans[200005];
map <int, pair <vector <int>, vector <int>>> a; // first id; second val
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        a.clear();
        for (int i = 1; i <= n; i++) cin >> arr[i];
        for (int i = 1; i <= n; i++) a[arr[i] / 4].first.push_back(i),
                                     a[arr[i] / 4].second.push_back(arr[i]);
        for (auto &i : a) sort (i.second.second.begin(), i.second.second.end());
        for (auto &i : a) 
            for (int j = 0; j < i.second.first.size(); j++) 
                ans[i.second.first[j]] = i.second.second[j];
        for (int i = 1; i <= n; i++) 
            cout << ans[i] << ' ';
        cout << '\n';
    }
}
```

---

## 作者：shenwentao (赞：0)

## 题目大意：

给出 $n$ 个数字，你可以选择两个数字 $a_i$ 和 $a_j$ $($ 其中 $i \neq j$ $)$，假如 $a_i ∧ a_j < 4$，那么两者就可以调换位置。

现在我们要尽可能地把所有小的数字往前挪，大的往后挪，求解最后所得数组。

## 思路解析：

只有在 $a_i ∧ a_j <4$ 时才可以交换两者位置，所以当 $a_i$ 除以 4 等于 $a_j$ 除以 4 时，那么我们就可以断定 $a_i$ 与 $a_j$ 可以切换位置。那么我们就可以按照这个条件给数字进行分组，每个满足条件的数字被划分到对应的小组当中。

### 步骤：

1. 按照这个条件给每个数字进行分组，相同的结果的数字之间可以互相调换下标。

1. 当我们从左往右遍历的时候，在遍历到某个小组的数组的时候，就可以让这个小组最小的数字先输出，较大的往后挪。

1. 直到输出完 $n$ 个数字之后，刚好输出完所有数字，并且是尽可能小的靠前，大的靠后的。这里可以利用优先队列进行维护，保证小的考前，大的靠后。

## 代码示范：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a[200010];
	int n,t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n;
		map<int,priority_queue<int> > mp;
		for(int i=1;i<=n;i++)
		{	
			cin>>a[i];
			mp[a[i]>>2].push(-a[i]);
		}
		for(int i=1;i<=n;i++)
		{
			cout<<-mp[a[i]>>2].top()<<" ";
			mp[a[i]>>2].pop();
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

如果在能交换的点之间连边，那么同一个连通块内可以任意排序。


暴力连边的边数可能很大。

考虑到不同的值最多 $n$ 种，建若干关于值的虚点，点先向值连边，然后再值与值间连边，这样的边数是 $O(n)$ 的。

可以简单的用并查集维护。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int N = 2e5 + 5;

int n, a[N], fa[N << 1], idx;

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void Merge(int x, int y) { //x --> y
	x = find(x);
	y = find(y);
	if(x != y) {
		fa[x] = y;
	}
}

void solve() {
	cin >> n;
	map<int, int> mp;
	for(int i = 1; i <= 2 * n; ++ i) fa[i] = i;
	idx = n;
	for(int i = 1; i <= n; ++ i) {
		cin >> a[i];
		if(mp.find(a[i]) == mp.end()) {
			mp[a[i]] = ++ idx;
		}
		Merge(i, mp[a[i]]);
	}
	for(auto [x, id] : mp) {
		for(int i : {0, 1, 2, 3}) {
			if(mp.find(x ^ i) != mp.end()) {
				Merge(id, mp[x ^ i]);
			}
		}
	}
	vector<vector<int>> b(n + 1);
	for(int i = 1; i <= n; ++ i) {
		b[find(i) - n].push_back(i);
	}

	for(int i = 1; i <= n; ++ i) {
		if(!b[i].empty()) {
			vector<int> val;
			for(auto j : b[i]) {
				val.push_back(a[j]);
			}
			sort(val.begin(), val.end());
			for(int j = 0; j < b[i].size(); ++ j) {
				a[b[i][j]] = val[j];
			}
		}
	}
	for(int i = 1; i <= n; ++ i) cout << a[i] << " \n"[i == n];
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int T;
	cin >> T;
	
	while(T --) {
		solve();
	}
	return 0;
}
```

---

## 作者：tder (赞：0)

[CF1971 场记](https://tder6.github.io/articles/CF1971A%20to%20CF1971G%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。

---

**【题意】**

给定长度为 $n$ 的序列 $a$，每次操作选择交换 $a_i$ 和 $a_j$，需要满足 $a_i\text{ xor }a_j<4$。求进行不限次操作后字典序最小的序列。多测。

**【思路】**

观察到 $4=2^2$，因此 $a_i\text{ xor }a_j<4$ 当且仅当 $a_i$ 和 $a_j$ 在二进制下除后两位完全相同。

考虑据此分类，例如当 $a$ 为 $\{(0110)_2,(0100)_2,(1110)_2\}$ 时，应将前两个分为一组，剩下的单独成组。

为了使整个序列的字典序尽可能小，不妨在每组内从小到大排序，用优先队列维护是简单的。另注意到 $a_i$ 可达 $10^9$ 量级，应使用 map 维护。

单组数据时间复杂度 $O(n\log n)$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 5;
int n, a[N];
map<int, priority_queue<int, vector<int>, greater<int>>> m;
void solve() {
	cin>>n;
	for(int i = 1; i <= n; i++) cin>>a[i];
	for(int i = 1; i <= n; i++) m[a[i] >> 2].push(a[i]);
	for(int i = 1; i <= n; i++) {
		cout<<m[a[i] >> 2].top()<<" ";
		m[a[i] >> 2].pop();
	}
	cout<<endl;
}
int t;
signed main() {
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：jhdrgfj (赞：0)

## 解法

让我们考虑 $a_i \oplus a_j < 4$ 有什么性质。$a_i \oplus a_j < 4$ 当且仅当 $a_i$ 与 $a_j$ 的二进制从倒数第三位开始都相同。显然，若 $a_i$ 与 $a_j$ 的二进制除最后两位之外还有不相同之处，那么这一位对两数异或的贡献就至少为 $2^2=4$。

我们考虑把 $a_i$ 分到 $a_i \mid 3$ 这一组，即我们将 $a_i$ 最后两位赋值为 $1$ 后将相等的数归为一组，因为我们已经令所有 $a_i$ 最后两位都相等，所以现在 $a_i=a_j$ 就等价于 $a_i$ 和 $a_j$ 在不考虑最后两位的情况下相等。

现在每一组中任取两个数都满足交换的条件，也就是每组内可以任意交换。那么让字典序最小就等价于从小到大排序。我这里用了 ``map`` 套 ``multiset`` 维护每个组内的数，虽然带了两只 $\log$ 但是能过而且很好写。

## 代码

```cpp
#include<bits/stdc++.h>
 #define int long long
using namespace std;
const int mxn=2000005;
int a[mxn],n;
map<int,multiset<int> > m;
signed main()
{
	int t;
	cin>>t;
	while (t--){
		cin>>n;
		for (int i=1;i<=n;i++){
			cin>>a[i];
			m[a[i]|3].insert(a[i]);
		}
		for (int i=1;i<=n;i++){
        
			cout<<*m[a[i]|3].begin()<<" ";
			m[a[i]|3].erase(m[a[i]|3].begin());
			//注意这里如果写 *m[a[i]|3].begin() 会删去所有值相同的数 
		}
		cout<<endl;
		m.clear();
	}
}
```

---

