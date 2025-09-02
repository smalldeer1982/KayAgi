# Digital Logarithm

## 题目描述

### 题目大意

我们定义 $f(x)$ 表示取出 $x$ 在**十进制**下的位数。( 如 $f(114514) = 6, \; f(998244353) = 9$ )。形式化讲，就是 $f(x) = \lfloor \log_{10} x \rfloor + 1$。

给定两个数组 $a$ 和 $b$，求执行若干次以下操作后使得 $a$ 和 $b$ **排序后**相等的最小操作次数。

操作方法如下：

- 选择一个下标 $i$，将 $a_i$ 赋值为 $f(a_i)$ **或者**将 $b_i$ 赋值为 $f(b_i)$。

## 样例 #1

### 输入

```
4
1
1
1000
4
1 2 3 4
3 1 4 2
3
2 9 3
1 100 9
10
75019 709259 5 611271314 9024533 81871864 9 3 6 4865
9503 2 371245467 6 7 37376159 8 364036498 52295554 169```

### 输出

```
2
0
2
18```

# 题解

## 作者：litachloveyou (赞：6)

这个题只需要在操作之后让 $a$ 和 $b$ 中的元素相同就可以了。

所以我们先尝试排序一下看看。

假设我们是从小到大排序的，如果 $a_i=b_i$ 的话那么肯定就不用操作了，如果当前 $a_i \neq b_i$ 那么肯定是要操作的。

$a_i \neq b_i$ 有三种情况。

第一种，$a_i > b_i$ ，因为我们是假设从小到大排序的，所以有可能 $b_{i+1}=a_i$ 。不过这说明，$b_i$ 当前没有能跟它相同的元素了。可是操作 $ b_i$ 意味着之后还要操作一个 $a_j$ 并且还不一定能保证最优，于是只好放弃从小到大排序。

那么从大到小排序呢，同理，只有当 $a_i \neq b_i $ 时才需要操作。

当 $a_i > b_i $ 的时候，说明 $a_i$ 一定要操作了，因为剩下 $b_j$ 都比 $a_i$ 要小。操作完之后如果 $a_{i+1}=b_{i}$ 的时候怎么办呢，我们可以使用优先队列来模拟这个比较的操作，这样每操作一次 $a_i$ 就会让 $a_{i+1}$ 继续跟 $b_i$ 比较。记得将操作完的 $a_i$ 塞回优先队列。


反之就是 $b_i$ 一定需要操作。当他们相同时直接弹出即可。

因为每一次操作的都是一定需要操作的，所以这样的次数一定是最少的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int len(int x)
{
	int cnt = 0;
	while (x)
	{
		cnt++;
		x = x / 10;
	}
	return cnt;
}
void solve()
{
	priority_queue<int, vector<int>, less<int>>a, b;
	int n, x, y;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		a.push(x);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		b.push(x);
	}
	int ans = 0;
	while (!a.empty())
	{
		x = a.top();
		y = b.top();
		if (x > y)
		{
			a.pop();
			a.push(len(x));
			ans++;
		}
		else if (x < y)
		{
			b.pop();
			b.push(len(y));
			ans++;
		}
		else
		{
			a.pop();
			b.pop();
		}
	}
	printf("%d\n", ans);
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：Forever1507 (赞：4)

先看数据范围，区别于一般的小于等于 $10^9$，这道题不允许等于的情况，所以一定有内幕（不是）。

然后浅算一下，发现对于任意小于 $10^9$ 的正整数 $x$ 均有 $f(f(x))=1$。

然后我想出了一个方案，我们可以对 $a,b$ 两个数组分别开优先队列，每次取出最大的数，如果一样直接弹出，否则，对于较大的那个数，不可能出现比它更大的数了，所以对它进行操作再丢回去，小的那个不变。因为两次之后一定会变成 $1$，所以操作次数一定不超过两轮，也就是重复次数是常数，所以 $\Theta(nlog_2n)$ 的时间复杂度是有保证的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],b[200005];
int mp[15];
void change(int &x){
	int cnt=0;
	while(x){
		++cnt;
		x/=10;
	}
	x=cnt;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		priority_queue<int>pq1,pq2;
		cin>>n;
//		memeset(mp,0,sizeof(mp));
		for(int i=1;i<=n;++i){
			cin>>a[i];
			pq1.push(a[i]);
		}
		for(int i=1;i<=n;++i)cin>>b[i],pq2.push(b[i]);
		int ans=0;
		while(!pq1.empty()&&!pq2.empty()){
			int cur1=pq1.top(),cur2=pq2.top();
			if(cur1==cur2){
				pq1.pop();
				pq2.pop();
				continue;
			}
			if(cur1>cur2){
				ans++;
				change(cur1);
				pq1.pop();
				pq1.push(cur1);
			}
			else{
				ans++;
				change(cur2);
				pq2.pop();
				pq2.push(cur2);
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}

```


---

## 作者：lrqlrq250 (赞：2)

## 解题思路
我们先考虑从小到大排序：当比较 $a_i$ 和 $b_i$ 的时候，如果 $a_i > b_i$，我们无法确定 $b$ 中下一个元素是否和 $a_i$ 相等，因此无法很高效地维护答案。

所以我们考虑从大到小排序，同样在比较 $a_i$ 和 $b_i$ 的时候，如果 $a_i > b_i$，则 $b_i$ 后面的数一定都小于 $b_i$，也就不可能有和 $a_i$相同的数，就说明 $a_i$ 一定需要被修改，然后我们保留 $b_i$，取 $a$ 中的下一个元素再和 $b_i$ 比较。

对于 $a_i < b_i$ 就是修改 $b_i$ 保留 $a_i$，对于 $a_i = b_i$ 就直接跳过就行了。

这个过程很容易用两个堆维护。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a, b;


int main(){
	int t;
	scanf("%d", &t);
	priority_queue<int, vector<int>, less<int> > q1, q2;
	while (t--){
		scanf("%d", &n);
		for (int i=1; i<=n; i++) scanf("%d", &a), q1.push(a);
		for (int i=1; i<=n; i++) scanf("%d", &b), q2.push(b);
		int ans = 0;
		while (!q1.empty()){
			a = q1.top(); b = q2.top();
			if (a > b){
				a = (int)log10(a) + 1;
				q1.pop(); q1.push(a);
				ans++;
			}
			else if (b > a){
				b = (int)log10(b) + 1;
				q2.pop(); q2.push(b);
				ans++;
			}
			else q1.pop(), q2.pop();
		}
		printf("%d\n", ans);
	}
	return 0;
}

```


---

## 作者：Erotate (赞：1)

### solutions

显然，应该先把 $a,b$ 数组中相同的部分先去掉，程序如下：

```
map<int,int>mp;

for(int i=1;i<=n;++i){
	cin>>a[i];
	mp[a[i]]++;
}
for(int i=1;i<=n;++i){
	cin>>b[i];
	if(mp[b[i]]) mp[b[i]]--;
	else bb[++cnt]=b[i];
}
cnt=0;
for(int i=1;i<=n;++i)
	if(mp[a[i]]>0) aa[++cnt]=a[i],mp[a[i]]--;
```

然后我们发现对于任意小于 $10^9$ 的正整数 $t$，都有 $f(f(t))=1$。于是我们可以把剩下的大于 $9$ 的数都进行一次操作，并在操作完之后记录下每一个数组中每一种数字出现的次数。那么对于不同数组中的相同数字，使得他们相同的最少次数为它们次数之差的绝对值。

```cpp
for(int i=1;i<=cnt;++i){
	if(aa[i]>9) aa[i]=gett(aa[i]),ans++;
	if(bb[i]>9) bb[i]=gett(bb[i]),ans++;
	visa[aa[i]]++,visb[bb[i]]++;
}
for(int i=2;i<=9;++i) ans+=abs(visa[i]-visb[i]);
//aa，bb 为去掉相同部分后的 a，b 数组
//visa，visb 为每种数字在 aa，bb 里出现的次数
//gett(x) 即 f(x)
//ans 为最后的答案
```


---

## 作者：StayAlone (赞：1)

### 题意

令 $f(x)$ 表示十进制下不含前导零时，$x$ 的位数。给定长度为 $n(1\leqslant \sum n \leqslant 2\times 10^5)$ 的数组 $a, b(1\leqslant a_i,b_i < 10^9)$，每一次操作选择 $a$ **或** $b$ 中的一个数 $y$，令 $y = f(y)$。求最少多少次操作可以使得任意排列后，$a$ 和 $b$ 完全相同。

### 思路

显然若 $a,b$ 中有相同的数，可以直接将它们配对。因此先把所有能配对的数从 $a,b$ 中删去。剩下的数中，所有大于等于 $10$ 的数不通过操作必定不能配对，因此把这些数进行一次操作。

接下来所有的数都在 $1\sim 9$。和第一步相似，把所有相同的数配对删去。删去后剩下一些数，这些数必须变成 $1$。因此再把这些数变成 $1$ 即可。

通过 multiset 实现删除 $O(n\log n)$。也可以通过双指针实现，时间复杂度降到 $O(n)$。$\log_{10}10^9$ 实在是太小了，而且并不是每一次操作都要算，所以直接忽略。

这里给出略丑的 multiset 实现。

[AC code record](https://www.luogu.com.cn/record/86550061)

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define ptc putchar
#define il inline
#define eb emplace_back
#define mp make_pair
#define fst first
#define snd second
#define .....
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 2e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int LOGN = log2(MAXN) + 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc {
	template <typename T> il bool read(T &x)
    
	il int read()

	template <typename T> il bool read(pair <T, T> &x) 

	template <typename T, typename ...L>
	il bool read(T &x, L &...y)

	template <typename T> il void write(T x)

	template <typename T> il void write(T x, char ch) 

	template <typename T> il void write(pair <T, T> x) 

	template <typename T> il T my_max(const T &x, const T &y)

	template <typename T> il T my_min(const T &x, const T &y)

	template <typename T> il T lowbit(const T &x)
}
using namespace stupid_lrc;
// 奇妙缺省源......
int n, a[MAXN], b[MAXN];
multiset <int> t1, t2;
vector <int> k1, k2;

il int get(int k) {
	if (!k) return 1;
	int cnt = 0;
	while (k) ++cnt, k /= 10;
	return cnt;
}

int main() {
	for (int T = read(); T--; ) {
		t1.clear(); t2.clear();
		read(n); rer(i, 1, n, a); rer(i, 1, n, b);
		rep1(i, 1, n) t1.insert(a[i]), t2.insert(b[i]);
		int ans = 0;
		for (auto p = t1.begin(); p != t1.end(); ) {
			auto m = t2.find(*p);
			if (m != t2.end()) {
				t2.erase(m);
				p = t1.erase(p);
			} else ++p;
		}
		k1.clear(); k2.clear();
		for (auto v : t1) k1.eb(v);
		for (auto v : t2) k2.eb(v);
		for (auto &v : k1) if (v >= 10) v = get(v), ++ans;
		for (auto &v : k2) if (v >= 10) v = get(v), ++ans;
		t1.clear(); t2.clear();
		for (auto v : k1) t1.insert(v);
		for (auto v : k2) t2.insert(v);
		for (auto p = t1.begin(); p != t1.end(); ) {
			auto m = t2.find(*p);
			if (m != t2.end()) {
				t2.erase(m);
				p = t1.erase(p);
			} else ++p;
		}
		for (auto v : t1) ans += v != 1;
		for (auto v : t2) ans += v != 1;
		write(ans, '\n');
	}
	rout;
}
```


---

## 作者：郑朝曦zzx (赞：1)

## 解题思路
如果我们把数字两两配对去讨论，就会很复杂，本题考虑按“轮”讨论。

我们每次取出两个数组中的最大值 $A, B$。

- 如果 $A,B$ 相等，给他们配上“对”，就不管他们了。

- 如果不相等，那么就一定要对最大的数进行 $1$ 次操作，不然就不可能给他配上“对”。

- 直到所有数都配上“对”了，我们停止执行算法。


这个找出最大值的过程可以用堆来实现。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read()
{
	bool flag = true;
	char c = getchar();
	if (c == '-') flag = false;
	while(!(c >= '0' && c <= '9')) c = getchar();
	int x = 0;
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (flag == true) return x;
	return -x;
}
priority_queue <int> a, b;
int len(int x)
{
	int res = 0;
	while (x)
	{
		x /= 10;
		++res;
	}
	return res;
}
int main()
{
	int t = read();
	while (t--)
	{
		int n = read(), ans = 0;
		while (!a.empty()) a.pop();
		while (!b.empty()) b.pop();
		for (int i = 1; i <= n; ++i)
		{
			int x = read();
			a.push(x);
		}
		for (int i = 1; i <= n; ++i)
		{
			int x = read();
			b.push(x);
		}
		while (a.size())
		{
			if (a.top() == b.top())
			{
				a.pop();
				b.pop();
				continue;
			}
			++ans;
			if (a.top() > b.top())
			{
				a.push(len(a.top()));
				a.pop();
			}
			else
			{
				b.push(len(b.top()));
				b.pop();
			}
		}
		printf("%d\n", ans);
	}
    return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：1)

# CF1728C 题解



## 思路分析

首先可以去掉所有相同的 $a_i$ 和 $b_j$，此时匹配某一对 $a_i$ 和 $b_j$ 至少要经过依次操作。

不难发现对于所有 $a_i,b_i$ 都有 $f(a_i)<10,f(b_i)<10$，因此此时所有 $\ge 10$ 的 $a_i,b_i$ 都必然不能直接匹配，所以经过一次操作压入 $f(a_i),f(b_i)$ 中。

接下来就变成了解决 $\forall a_i,b_i<10$ 的问题，首先同样先去重，剩下的都必须再经过一次操作变成 $1$，原问题解决。

时间复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int MAXN=2e5+1;
inline int f(int x) {
	if(x<1e1) return 1;
	if(x<1e2) return 2;
	if(x<1e3) return 3;
	if(x<1e4) return 4;
	if(x<1e5) return 5;
	if(x<1e6) return 6;
	if(x<1e7) return 7;
	if(x<1e8) return 8;
	return 9;
}
int a[MAXN],b[MAXN],c1[11],c2[11];
inline void solve() {
	memset(c1,0,sizeof(c1));
	memset(c2,0,sizeof(c2));
	int n,res=0;
	scanf("%d",&n);
	set <pii> S;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) scanf("%d",&b[i]),S.insert(make_pair(b[i],i));
	for(int i=1;i<=n;++i) {
		auto it=S.lower_bound(make_pair(a[i],0));
		if(it==S.end()||it->first!=a[i]) continue;
		a[i]=0,b[it->second]=0;
		S.erase(it);
	}
	for(int i=1;i<=n;++i) {
		if(!a[i]) continue;
		if(a[i]<10) ++c1[a[i]];
		else {
			++res;
			a[i]=f(a[i]);
			++c1[a[i]];
		}
	} 
	for(int i=1;i<=n;++i) {
		if(!b[i]) continue;
		if(b[i]<10) ++c2[b[i]];
		else {
			++res;
			b[i]=f(b[i]);
			++c2[b[i]];
		}
	}
	for(int i=1;i<=9;++i) {
		int x=min(c1[i],c2[i]);
		c1[i]-=x,c2[i]-=x;
		if(i!=1) res+=c1[i]+c2[i];
	}
	printf("%d\n",res);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：y_kx_b (赞：0)

Preface
-
cf
掉大分www。我不敢相信我前两题做的比这题慢多了，而且吃满了罚时![](//啧.tk/kk)

Analysis
-
$f(x)=\left\lfloor\log_{10}\right\rfloor$，容易发现 $f(x)$ 是单调不增的。又因 $x<10^9$，所以 $f(x)<10$，$f(f(x))=1$，那么答案最多为 $4\times n$。

考虑缩小答案。因为 $f(x)$ 是单调不增的，所以我们需要从大元素依次入手，因为如果有最大的元素不成对那么肯定要对这个元素进行操作，否则不可能达到目标状态 $a_i=b_i$（因为你无法对其他元素操作获得这个最大值）。所以我们每次找到 $a$ 和 $b$ 中的最大元素进行一次操作。可以用优先队列或平衡树（`std::multiset`）实现。

当然我觉得分别维护两个序列有点麻烦，于是我写成了一加一减的 `map`。$\text{first}$ 是值，$\text{second}$（的绝对值）是需要对该值进行修改的次数。

Code
-
自我感觉马蜂良好/oh
```cpp
int n,m,q,k;
map<int,int>S;
int f(int x){
	int r=0;
	while(x)x/=10,r++;
	return r;
}
bool major(){
	S.clear();//多测必备/oh
	n=read();
	for(int i=1;i<=n;i++)S[read()]++;
	for(int i=1;i<=n;i++)S[read()]--;
	int ans=0;
	for(auto p=(--S.end());1;--p){
	//这里的--S.end()实际上并不会改变S.end()的值。
		// printf("%d ",(*p).x);
		ans+=abs((*p).y);
		S[f((*p).x)]+=(*p).y;
		if(p==S.begin())break;
	}
	printf("%d ",ans);
	puts("");
	return 114514;
}
```

---

