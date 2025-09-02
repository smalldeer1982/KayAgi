# Kirill and Mushrooms

## 题目描述

当营地里的每个人都进入梦乡后，基里尔便偷偷溜出帐篷，到智慧的橡树下采蘑菇。

众所周知，橡树下生长着 $n$ 朵蘑菇，每朵蘑菇都有 $v_i$ 的魔力。 基里尔非常想用这些蘑菇制作一种魔力最大的灵药。

灵药的强度等于其中蘑菇的数量与这些蘑菇中最小魔力的乘积。要配制灵药，基里尔要依次采摘生长在橡树下的蘑菇。基里尔可以按照任何顺序采集蘑菇。

然而，事情并非如此简单。智慧的橡树给出了一个排列 $p_1,p_2,...,p_n$，如果基里尔只采摘 $k$ 朵蘑菇，那么 $v_{p_1},v_{p_2},...,v_{p_{k-1}}$ 都将变为 $0$。 基里尔不会使用魔力为零的蘑菇来配制灵药。

你的任务是帮助基里尔采集蘑菇，使他能够酿造出最大魔力的灵药。然而，基里尔有点害怕在橡树旁待太久，所以在所有适合采集蘑菇的方案中，他要求你找到蘑菇数量最少的那个。

## 说明/提示

在样例的第一个测试用例中，你需要采摘前两朵蘑菇，因此灵药的魔力等于 $2 \cdot \min(a_1, a_2) = 2 \cdot \min(9, 8) = 2 \cdot 8 = 16$。 请注意，采摘两朵蘑菇后，第三朵蘑菇的魔力将变为 $0$。

## 样例 #1

### 输入

```
6
3
9 8 14
3 2 1
5
1 2 3 4 5
1 2 3 4 5
6
1 2 3 4 5 6
6 5 4 3 2 1
5
1 4 6 10 10
2 1 4 5 3
4
2 2 5 5
4 2 3 1
5
1 2 9 10 10
1 4 2 3 5```

### 输出

```
16 2
9 3
8 2
20 2
5 1
20 2```

# 题解

## 作者：Silvestorm (赞：17)

### 题目大意

假设取 $k$ 个数，那么会有 $k-1$ 个数变成 $0$，此时的贡献为 $k$ 乘以选的数中的最小值，要求在贡献尽可能大的情况下，选尽可能少的数。

### 题目类型

贪心。

### 解题思路

基于贪心思路，枚举 $k$，再删去 $k-1$ 个数之后，再找出第 $k$ 大的数，记录最优解即可。

问题是如何去实现。

不妨逆向思维，从数组里一个一个添加元素。当还剩下 $k-1$ 个元素待添加时，求数组的第 $k$ 小，这就转化成排序问题。这里可以维护一个长度为 $k$ 的升序优先队列，以达到优化效果。每次添加元素，贡献为队首乘以队列大小。

时间复杂度为 $O(n\log n)$。

### code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
long long n, x, ans, arr[300100], num[200100];
priority_queue<ll, vector<ll>, greater<ll>> q;
void solve()
{
	ans = 0;
	while (!q.empty())
		q.pop();
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> num[i];
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	for (int i = n; i > 0; i--)
	{
		q.push(num[arr[i]]);
		while (q.size() > i)
			q.pop();
		if (q.size() >= i && q.top() * i >= ans)
		{
			ans = q.top() * i;
			x = i;
		}
	}
	cout << ans << " " << x << '\n';
	return;
}
int main()
{
	int t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：spfa_ (赞：6)

[CF1945F Kirill and Mushrooms](https://www.luogu.com.cn/problem/CF1945F)

### 题目翻译

给一个数组 $v$ 和排列 $p$，若在 $v$ 中选 $k$ 个数，则 $v$ 中下标为 $p_1,p_2\dots p_{k-1}$ 均变成为 $0$，这 $k$ 个数 $a_1,a_2\dots a_k$ 的权值为

$$k\times\min_{1\le i\le k}a_i$$

求最大权值和对应的 $k$，若有相同的取 $k$ 较小的那个。

### 题目分析

我们可以直接从小到大枚举 $k$，然后将对应的 $v$ 进行赋 $0$，那么权值最大即为 $v$ 中第 $k$ 大的数与 $k$ 的乘积。这里我们可以选择平衡树来维护 $v$，时间复杂度为 $O(n\log n)$。

[code](https://codeforces.com/contest/1945/submission/252396047)

---

## 作者：Sternenlicht (赞：2)

### 题目大意

有 $n$ 个数，每个数都有一个权值 $v_i$。假设取 $i$ 个数，那么 $v$ 中会有 $i−1$ 个数变成 $0$，其下标为 $p_1 ,p_2,\dots,p_{i-1}$。此时的贡献值为， $i$ 乘以所选数中的最小值。求在贡献值最大，选数数量最少时，贡献值与选数数量。

### 思路

枚举取数个数 $i$，注意 $i \in [1, \lceil \frac{n}{2} \rceil]$，因为取了总个数的一半后，最好情况也是另一半数的权值变为 $0$。

取 $i$ 个数后，由题意，需求剩余能取的数中第 $i$ 大的数，可以用权值线段树求解。具体地，将原数组离散化后，用权值线段树维护第 $i$ 大的数。

现在考虑权值归零如何处理。由于权值线段树记录的是每个数的出现次数，因此当权值 $v$ 归零时，将其出现次数 $-1$ 即可。

```cpp
#include <bits/stdc++.h>
#define il inline
namespace Fast_IO {
	template <typename T> il void read(T &x) {
		x = 0; int f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + (ch - 48), ch = getchar();
		x = f ? -x : x;
	}
	template <typename T, typename ...Args>
	il void read(T &x, Args& ...args) {read(x), read(args...);}
	template <typename T> il void write(T x, char c = '\n') {
		if (x) {
			if (x < 0)x = -x, putchar('-');
			char a[30]; short l;
			for (l = 0; x; x /= 10) a[l ++] = x % 10 ^ 48;
			for (l --; l >= 0; l --) putchar(a[l]);
		} else putchar('0');
		putchar(c);
	}
} using namespace Fast_IO;
using namespace std;

#define int long long
const int Maxn = 200005;
int a[Maxn], b[Maxn], p[Maxn], tree[Maxn << 2];
il int ls(int u) {return u << 1;}
il int rs(int u) {return u << 1 | 1;}
il void pushup(int u) {tree[u] = tree[ls(u)] + tree[rs(u)];}
void update(int u, int l, int r, int x, int k) {
	if (l == r) {tree[u] += k; return ;}
	int mid = (l + r) >> 1;
	if (x <= mid) update(ls(u), l, mid, x, k);
	else update(rs(u), mid + 1, r, x, k);
	pushup(u);
}
int query(int u, int l, int r, int x) {
	if (l == r) return l;
	int mid = (l + r) >> 1, kth = tree[ls(u)];
	if (x <= kth) return query(ls(u), l, mid, x);
	else return query(rs(u), mid + 1, r, x - kth);
}
signed main() {
	int T; read(T);
	while (T --) {
		int n; read(n);
		for (int i = 0; i <= (n << 2); i ++) tree[i] = 0;
		for (int i = 1; i <= n; i ++) read(a[i]), b[i] = a[i];
		for (int i = 1; i <= n; i ++) read(p[i]);
		sort(b + 1, b + n + 1);
		int m = unique(b + 1, b + n + 1) - b - 1;
		for (int i = 1; i <= n; i ++) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b, update(1, 1, m, a[i], 1);
		int ans = -1, num = 0; //最大值与最少数量 
		for (int i = 1; i <= ceil(n / 2.0); i ++) {
			int kth = (n - i + 1) - i + 1;
			int res = query(1, 1, m, kth);
			if (ans < b[res] * i) ans = b[res] * i, num = i;
			update(1, 1, m, a[p[i]], -1);
		}
		write(ans, ' '), write(num);
	}
	return 0;
}
```

---

## 作者：appear_hope (赞：2)

简化题意：

要求选择序列 $A = \{ 1, 2, \dots, n \}$ 的子序列 $S$，令这个子序列的长度为 $k$。

选出的子序列满足： $\forall i \in \{ 1, 2, \dots k - 1 \} , p_i \notin S$。

请你求出 $\max \{ k \times \min \limits_{i=1}^{k} v_{S_i}\}$。

稍作思考可以发现没法对于每一个 $\min \limits_{i=1}^{k} S_i$ 求出最大的 $k$。

转变思路我们只能对于每个 $k$，我们要求出 $\min \limits_{i=1}^{k} v_{S_i}$ 的最大值，所以我们可以对于区间 $v_{k \sim n}$ 从大到小排序，找到第 $k$ 大这就是枚举了 $k$ 之后 $\min \limits_{i=1}^{k} v_{S_i}$ 的最大值。

查找第 $k$ 大或第 $k$ 小可以用堆或线段树，这里讲一下如何用线段树。

首先对 $v_i$ 不去重离散化（可能多个位置用着一个编号这样时会有问题的，自己想想），然后在线段树上做二分。（判断大于等于这个数的数量是否大于等于 $k$）

那么如何在线段树上做二分呢？

仔细想想二分是怎么写的，把这种思想推广到线段树上，稍作思考你就可以得到如下伪代码：

```cpp
query(id, l, r, x):
   	//当前遍历节点编号为 id，区间为 [l, r]，限制为 x
   if(绝对不存在答案){
        	return INF;
   }
	if(l == r){
        	return l;
   }
	int mid = (l + r) >> 1;
	if(答案在右区间){ //最小值还能变得更大
  		return query(id * 2 + 1, mid + 1, r, x);
   }
	return query(id * 2, l, mid, 去掉右半边带来的贡献);
```

完整代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

pair<long long, long long> b[N];
int T, n, a[N], p[N], tree[4 * N];

void Change(int id, int l, int r, int x){
  if(l == r){
    tree[id] = 0;
    return ;
  }
  int mid = (l + r) >> 1;
  x <= mid ? Change(id * 2, l, mid, x) : Change(id * 2 + 1, mid + 1, r, x);
  tree[id] = tree[id * 2] + tree[id * 2 + 1];
}

void Build(int id, int l, int r){
  if(l == r){
    tree[id] = 1;
    return ;
  }
  int mid = (l + r) >> 1;
  Build(id * 2, l, mid), Build(id * 2 + 1, mid + 1, r);
  tree[id] = tree[id * 2] + tree[id * 2 + 1];
}

int query(int id, int l, int r, int x){
  if(tree[id] < x){
    return -1;
  }
  if(l == r){
    return l;
  }
  int mid = (l + r) >> 1;
  if(tree[id * 2 + 1] >= x){
    return query(id * 2 + 1, mid + 1, r, x);
  }
  return query(id * 2, l, mid, x - tree[id * 2 + 1]);
}

void Solve(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
    b[i] = {a[i], i};
  }
  for(int i = 1; i <= n; i++){
    cin >> p[i];
  }
  Build(1, 1, n);
  sort(b + 1, b + n + 1);
  for(int i = 1; i <= n; i++){
    a[b[i].second] = i;
  }
  long long ans = 0, s = INT_MAX;
  for(long long i = 1; i <= n; i++){
    int v = query(1, 1, n, i);
    if(~v && i * b[v].first > ans){
      s = i, ans = i * b[v].first;
    }
    Change(1, 1, n, a[p[i]]);
  }
  cout << ans << ' ' << s << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  for(cin >> T; T--; Solve()){
  }
  return 0;
}
```

时空复杂度：

时间复杂度：$O(n \log_2 n)$。

空间复杂度：$O(n)$。

---

## 作者：Otue (赞：2)

当确定摘的蘑菇的个数后，哪些蘑菇被清空是确定的。则我们先枚举摘 $i$ 个蘑菇，在按照题意先将 $i-1$ 个蘑菇清空，然后只需要在剩下没有被清 0 的蘑菇中找到前 $i$ 大的数，将它乘上 $i$ 就是答案（灵药的强度等于蘑菇的数量与蘑菇中最小魔力的乘积）。

如何同时清空又同时求第 $k$ 大数？权值线段树。

---

## 作者：Vitamin_B (赞：1)

# 前置芝士
vector 的一些功能：
1. `lower_bound(v.begin(),v.end(),x)`，在 vector 变量 $v$ 中找到第一个 $\ge x$ 的**迭代器**；
2. `v.erase(iter)`，在 vector 变量 $v$ 中删除迭代器 $iter$ 的位置；
3. 根据 $1,2$，我们知道 `v.erase(lower_bound(v.begin (),v.end(),x))` 可以删掉 vector 变量 $v$ 中第一个 $\ge x$ 的数。

# 思路
首先对蘑菇们的魔力值排序，然后依次枚举选取的蘑菇个数，根据题目的定义，此时的魔力值之和为 $v_{\operatorname{card}(v)-i}\times i$。每次枚举后就把 $a_{p_i}$ 删了就行。
# 代码
```cpp
# pragma GCC optimize("Ofast,no-stack-protector") //佩戴 Ofast 食用更好
# pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
typedef long long ll;
using namespace std;
int t, n, a[200005], p[200005], minx;
ll maxx;
vector <int> v;
void del (int x) {
	v.erase (lower_bound (v.begin (), v.end (), a[x]));
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		v.clear (), maxx = minx = 0;
		cin >> n;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i], v.emplace_back (a[i]);
		for (int i = 1; i <= n; ++ i)
			cin >> p[i];
		sort (v.begin (), v.end ());
		for (int i = 1; i <= n - (i - 1); ++ i) {
			if (v[v.size () - i] * (ll) i > maxx)
				maxx = v[v.size () - i] * (ll) i, minx = i;
			del (p[i]);
		}
		cout << maxx << ' ' << minx << '\n';
	}
	I AK IOI
}
```

---

## 作者：菲斯斯夫斯基 (赞：1)

## CF1945F Kirill and Mushrooms 题解

考虑直接枚举答案。

假设枚举摘 $i$ 个蘑菇，那么接下来要求的就是**剩余能摘的蘑菇中第** $i$ **大的价值**。

不难想到用**权值线段树**，可以容易地找到第 $i$ 大的数。

对于价值归 $0$ 的操作，只需要每次枚举完之后在原价值处加上 $-1$ 即可。

因为 $1\le v_i\le10^9$，所以还要离散化一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,cnt,id;
int a[N],b[N],c[N],f[N<<2];
long long ans;
void add(int k,int l,int r,int x,int y)
{
	if(l>x||r<x)return ;
	if(l==r)
	{
		f[k]+=y;
		return ;
	}
	int mid=(l+r)/2;
	add(k*2,l,mid,x,y);
	add(k*2+1,mid+1,r,x,y);
	f[k]=f[k*2]+f[k*2+1];
}
int ask(int k,int l,int r,int x)
{
	if(l==r)return l;
	int sum=f[k*2],mid=(l+r)/2;
	if(sum>=x)return ask(k*2,l,mid,x);
	else return ask(k*2+1,mid+1,r,x-sum);
}//权值线段树基本操作 
int main()
{
	cin>>t;
	while(t--)
	{
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),b[i]=a[i];
		for(int i=1;i<=n;i++)
			scanf("%d",&c[i]);
		sort(b+1,b+1+n);
		int m=unique(b+1,b+1+n)-b-1;//离散化
		for(int i=1;i<=n;i++)
		{
			a[i]=lower_bound(b+1,b+1+m,a[i])-b;
			add(1,1,m,a[i],1);
		}
		for(int i=1;i*2-1<=n;i++)//注意i*2-1>n时没有足够的蘑菇能选
		{
			int k=ask(1,1,m,(n-i+1)-i+1);//将第i大换成第x小 
			if(1ll*b[k]*i>ans)
				ans=1ll*b[k]*i,id=i;
			add(1,1,m,a[c[i]],-1);//价值归0 
		}
		printf("%lld %d\n",ans,id);
		for(int i=0;i<=(n<<2);i++)
			f[i]=0;//多测要清空
	}
	return 0;
}
```

---

## 作者：Starrykiller (赞：1)

我们考虑用类似对顶堆的方法来解决本题。

对于一个元素 $a_i$，我们将其变成一个二元组 $(a_i,i)$，存储在 `std::set` 中。这样做的目的一是为了方便 `std::set` 的排序，二是为了处理 $a_i$ 重复的情况。

然后我们维护两个 `std::set`，第一个存储前 $i$ 大的 $(a_i,i)$（按照 $a_i$ 比较），第二个存储其他的元素。当我们需要删除一个 $a_i$ 的时候，直接在两个堆中的一个将其删除就行了。

删除完元素之后，我们维护第一个 `std::set`，将第二个 `std::set` 中的最大的元素加入第一个 `std::set` 中，直到第二个 `std::set` 为空或者第一个 `std::set` 中的元素数量达到 $i$。然后直接取出第一个 `std::set` 中的最小的元素更新答案即可。

如果第二个 `std::set` 都空了还无法让第一个的元素数量达到 $i$，那就显然无解了。

时间复杂度是常数略大的 $\Theta(n\log n)$。

[My Submission](https://codeforces.com/contest/1945/submission/252238557).

---

## 作者：Better_Fish (赞：0)

考虑 **对顶堆** 的思路。

开两个 multiset $s$ 和 $t$，$s$ 表示没采的蘑菇，$t$ 表示采了的蘑菇。开始时，我们把所有元素加入 $s$。

我们从小到大枚举 $k$。当小 K 采摘到第 $k(k>1)$ 个蘑菇时，第 $p_{k-1}$ 个蘑菇将会失效。这可以看成是从堆中删元素的操作。随后，我们将 $s$ 中最大的元素加入 $t$ 中，直到 $t$ 有 $k$ 个元素了为止。最后维护答案即可。

时间复杂度 $O(n\log n)$。

---

## 作者：__HHX__ (赞：0)

# 思路一（暴力修改）
首先我们设我采了 $x$ 个蘑菇。

我们一定希望采到蘑菇的 $v_i$ 最小的最大。

所以我们可以设容器 $G$ 存放 $x$ 个最大的 $v_i$。

我设一个第 $x - 1$ 版本的 $G'$。

若我们想将 $G'$ 变为 $G$，我们可以如下操作。

1. 将 $v_{p_{x - 1}}$ 修改为 $0$。

2. 重新将 $x$ 个最大的 $v_i$ 加入 $G$。

很明显操作 $2$ 有些多余。

我们可以设容器 $H$ 存放非 $G$ 的所有 $v_i$。

每次我就只用 $H$ 的最大元素加入 $G'$。

但我们发现操作 $1$ 如果在 $G'$ 中执行十分棘手。

但是很明显操作 $1$ 只会修改 $G'$ 中的其中一个值。

所以我们可以将修改值存在 $H$ 中然后 $H$ 再取一个最大值到 $G'$。

因为操作 $1$ 后修改值一定为 $0$，所以理论上我们可以直接删去。

此时容器 $H$ 需要满足以下操作：
1. 快速查找最大元素。
2. 快速寻找值并修改或删除。

此时容器 $G$ 需要满足以下操作：
1. 快速寻找值并修改或删除。

其实这里使用 ``multiset`` 暴力修改其实就可以过。

我们可以通过排序保证 $H$ 的首元素最优，然后 $G,H$ 用链表维护删除操作，如果弄个恶心的指针理论可以达到 $O(1)$ 的修改。
# 思路二（倒推）
与思路一类似，但是我们将棘手的删除变为加入。

此时容器 $H$ 需要满足以下操作：
1. 快速查找最大元素。
2. 快速删除最大元素。

此时容器 $G$ 需要满足以下操作：
1. 快速查找最小元素。
2. 快速删除最小元素。
3. 快速加入最小元素。

此时我们很容易看出这就是个对顶堆。

但是我们我们可以通过排序满足 $H$ 操作。

# 代码
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int N = 2e5 + 3;

int v[N], a[N], k;

multiset<int> p, q;

void Solve() {
  int n, pl;
  long long ans = -1e18;
  cin >> n, k = 1;
  for (int i = 1; i <= n; i++) {
    cin >> v[i], q.insert(v[i]);
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    p.insert(*(--q.end())), q.erase(--q.end());
    long long ap = *p.begin() * p.size();
    if (ap > ans) ans = ap, pl = i;
    if (q.find(v[a[i]]) != q.end()) q.erase(q.find(v[a[i]])), q.insert(0);
    else p.erase(p.find(v[a[i]])), q.insert(0), p.insert(*(--q.end())), q.erase(--q.end());
  }
  while (p.size()) p.erase(p.begin());
  cout << ans << ' ' << pl << '\n';
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    Solve();
  }
  return 0;
}
```
```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int N = 2e5 + 3;

int v[N], a[N], k;

priority_queue<int, vector<int>, greater<int> > q;

void Solve() {
  int n, pl;
  long long ans = -1e18;
  cin >> n, k = 1;
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n; i > n - n / 2; i--) {
    q.push(v[a[i]]);
  }
  for (int i = n - n / 2; i >= 1; i--, k++){
    q.push(v[a[i]]);
    while (q.size() > i) q.pop();
    if (ans <= 1ll * q.top() * i) ans = 1ll * q.top() * i, pl = i;
  }
  q.pop();
  cout << ans << ' ' << pl << '\n';
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    Solve();
  }
  return 0;
}
```

---

## 作者：_qingshu_ (赞：0)

直接使用万能的 STL 无脑水过！

# 思路：

可以发现当我们确定采摘个数且去除了会变成 $0$ 的蘑菇之后答案是可以 $\mathcal{O}(1)$ 计算的：对于剩下的序列我们暂定为有序的，那么最小的一定是从大往小的第 $i$ 个（其中 $i$ 为我们钦定的采摘数量）。

现在来考虑如何使得存在一个序列有且仅有魔力不为 $0$ 的蘑菇且有序排列，我们可以使用 vector 来保存剩下的蘑菇。

对于 $i>1$ 的时候，我们会有一个蘑菇的魔力变成 $0$，我们在 vector 中删去它就好了，这不会改变整体的有序性。


期望复杂度 $\mathcal{O}(n\log n)$，但实际跑起来非常的慢。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5200010],p[5200010];
inline void solve(){
	cin>>n;vector<int>q;
	long long ans=0,len=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)q.emplace_back(a[i]);
	stable_sort(q.begin(),q.end());
	for(int i=1;i<=(n+1)/2;i++){
		if(i!=1)q.erase(lower_bound(q.begin(),q.end(),a[p[i-1]]));
		if(1ll*i*q[q.size()-i]>ans){
			ans=1ll*i*q[q.size()-i];
			len=i;
		}
	}
	cout<<ans<<" "<<len<<"\n";
}
int main(){
	int T;cin>>T;
	while(T--)solve();
}
```

---

## 作者：Halberd_Cease (赞：0)

题意：有 $n$ 个蘑菇，定义收益为你选的蘑菇数量 $k$ 乘上你选的蘑菇中最小的魔力 $v_{min}$，同时，如果你要选 $k$ 个蘑菇，那么编号为 $p_1,p_2,\dots,p_{k-1}$ 的蘑菇的 $v$ 变为 $0$，即你不能选，问可能的最大收益，以及满足最大收益时的最小 $k$。

显然，我们枚举 $k$，将蘑菇按照强制变为 $0$ 的顺序排一次序。对于每一个 $k$，求的就是除去前 $k-1$ 个蘑菇，剩下蘑菇 $v$ 的第 $k$ 大。

考虑线段树，先查找区间的最大值，作为 $k=1$ 时的答案，然后把这个最大值改成 $-1$ 表示不可选。

然后我们找到从前往后第 $k$ 个蘑菇，如果已经被 ban，那我们就 ban 掉整个区间的最大值，否则 ban 掉这一个蘑菇。

为什么这么做是对的？

每一轮结束过后，前 $k$ 个蘑菇，和剩下的蘑菇中最大的 $k$ 个被 ban 了，那么接下来第 $k+1$ 轮的全局最大值，就是前面说的“除去前 $k-1$ 个蘑菇，剩下蘑菇 $v$ 的第 $k$ 大”。

[submission](https://codeforces.com/contest/1945/submission/252376739)

---

## 作者：StrSeeker (赞：0)

## 平衡树做法
请在确保自己会打平衡树板子的情况下观看此篇题解。
#### 题意简述
有 $n$ 个数和两个长度为 $n$ 的序列 $v,p$，可以选任意 $k$ 件物品，但是选择 $k$ 件物品时第 $p_1,p_2,\cdots,p_{k-1}$ 件物品不可选。选择 $k$ 件物品的价值定义为其中 $v_i$ 的最小值与 $k$ 的乘积。问最大价值。
#### 题解
首先有一个显然的贪心想法，就是当我们钦定要选 $k$ 个物品时，尽量去选 $v_i$ 较大的那些。这样就能保证 $v_i$ 的最小值最大，从而保证选择 $k$ 个的情况下所获价值最大。

于是问题来到寻找一个数据结构，支持插入、删除、获取第 $k$ 大元素。考虑用平衡树来维护。

具体做法是先将所有元素插入平衡树中，再枚举选择的物品的数量 $k$。注意当 $k \gt 1$ 时要根据 $p$ 序列从平衡树删掉前 $k-1$ 个。 

示例代码使用非旋 Treap 实现。

```cpp 
#include<cstdio>
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+5;
int v[maxn],p[maxn];
template <class T>
inline T randint(T l, T r) {
	static unsigned long long seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	return generator() % (1ll + r - l) + l; 
}
struct Treap {
public:
	typedef int key_type;
	typedef int val_type;

private:
	struct node {
		int ch[2];
		key_type key;
		val_type val;
		unsigned int pri;
		int siz;
	} treap[maxn + 5];
	int root = 0, doc = 0;
	queue<int> waste;
	inline int new_node() {
		if (!waste.empty()) {
			int p = waste.front();
			waste.pop();
			return p;
		}
		return ++doc;
	}
	inline int create_node(key_type key, val_type val = val_type()) {
		int p = new_node();
		treap[p].ch[0] = treap[p].ch[1] = 0;
		treap[p].key = key;
		treap[p].val = val;
		treap[p].pri = randint(-100000, 100000);
		treap[p].siz = 1;
		return p;
	}
	inline void pushup(int p) {
		treap[p].siz = treap[treap[p].ch[0]].siz + 1 + treap[treap[p].ch[1]].siz;
		return;
	}
	inline void pushdown(int p) {
		return;
	}
	int merge(int x, int y) {
		if (x == 0 || y == 0)
			return x + y;
		if (treap[x].pri < treap[y].pri) {
			pushdown(x);
			treap[x].ch[1] = merge(treap[x].ch[1], y);
			pushup(x);
			return x;
		}
		else {
			pushdown(y);
			treap[y].ch[0] = merge(x, treap[y].ch[0]);
			pushup(y);
			return y;
		}
		return -1;
	}
	pair<int, int> split(int x, key_type k) {
		if (x == 0)
			return make_pair(0, 0);
		pushdown(x);
		if (k <= treap[x].key) {
			pair<int, int> ans = split(treap[x].ch[0], k);
			treap[x].ch[0] = ans.second;
			ans.second = x;
			pushup(x);
			return ans;
		}
		else {
			pair<int, int> ans = split(treap[x].ch[1], k);
			treap[x].ch[1] = ans.first;
			ans.first = x;
			pushup(x);
			return ans;
		}
		return make_pair(-1, -1);
	}
	pair<int, int> split_by_rank(int x, int k) {
		if (x == 0)
			return make_pair(0, 0);
		pushdown(x);
		if (k <= treap[treap[x].ch[0]].siz) {
			pair<int, int> ans = split_by_rank(treap[x].ch[0], k);
			treap[x].ch[0] = ans.second;
			ans.second = x;
			pushup(x);
			return ans;
		}
		else {
			pair<int, int> ans = split_by_rank(treap[x].ch[1], k - treap[treap[x].ch[0]].siz - 1);
			treap[x].ch[1] = ans.first;
			ans.first = x;
			pushup(x);
			return ans;
		}
		return make_pair(-1, -1);
	}

public:
	inline int size() {
		return treap[root].siz;
	}
	inline void insert(key_type y, val_type z = val_type()) {
		pair<int, int> ans = split(root, y);
		root = merge(merge(ans.first, create_node(y, z)), ans.second);
		return;
	}
	inline void erase(key_type y) {
		pair<int, int> ans = split(root, y);
		pair<int, int> sna = split(ans.second, y + 1);
		root = merge(ans.first, merge(merge(treap[sna.first].ch[0], treap[sna.first].ch[1]), sna.second));
		waste.push(sna.first);
		return;
	}
	inline void burn(int y) {
		pair<int, int> ans = split_by_rank(root, y);
		root = merge(ans.second, ans.first);
		return;
	}
	inline void insert_by_rank(int y, val_type z = val_type()) {
		pair<int, int> ans = split_by_rank(root, y);
		root = merge(merge(ans.first, create_node(key_type(), z)), ans.second);
		return;
	}
	inline void erase_by_rank(int y) {
		pair<int, int> ans = split_by_rank(root, y);
		pair<int, int> sna = split_by_rank(ans.second, 1);
		root = merge(ans.first, sna.second);
		waste.push(sna.first);
		return;
	}
	inline int rank_of_key(key_type y) { 
		pair<int, int> ans = split(root, y);
		int ret = ans.first ? treap[ans.first].siz : 0;
		root = merge(ans.first, ans.second);
		return ret;
	}
	inline key_type key_of_rank(int y) {
		if (y < 0 || y >= treap[root].siz)
			return -2147483648;
		pair<int, int> ans = split_by_rank(root, y);
		pair<int, int> sna = split_by_rank(ans.second, 1);
		key_type ret = treap[sna.first].key;
		root = merge(ans.first, merge(sna.first, sna.second)); 
		return ret;
	}
	inline val_type value_of_key_of_rank(int y) {
		if (y < 0 || y >= treap[root].siz)
			return val_type();
		pair<int, int> ans = split_by_rank(root, y);
		pair<int, int> sna = split_by_rank(ans.second, 1);
		val_type ret = treap[sna.first].val;
		root = merge(ans.first, merge(sna.first, sna.second)); 
		return ret;
	}
	inline val_type value_of_key(key_type y) { 
		pair<int, int> ans = split(root, y);
		pair<int, int> sna = split(ans.second, y + 1);
		val_type ret = sna.first ? treap[sna.first].val : val_type();
		root = merge(ans.first, merge(sna.first, sna.second)); 
		return ret;
	}
}Trep;
void solve()
{
    int n;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&v[i]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&p[i]);
    }
    for(int i=1;i<=n;i++)
    {
        Trep.insert(v[i]);
    }
    int ans=-1;
    int pos=n+100;
    int cct=n;
    for(int i=1;i<=n;i++)
    {
        if(i>1) 
        {
            Trep.erase(v[p[i-1]]);
            cct--;
        }
        int k=Trep.key_of_rank(cct-i);
        if(ans<k*i)
        {
            ans=k*i;
            pos=i;
        }
    }
    printf("%lld %lld\n",ans,pos);
    Trep.erase_by_rank(0);
}
signed main()
{
    int T;
    scanf("%lld",&T);
    while(T--) solve();
}

---

