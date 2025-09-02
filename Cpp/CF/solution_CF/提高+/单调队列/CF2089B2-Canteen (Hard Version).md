# Canteen (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本的区别在于此版本中，对 $$$k$$$ 没有额外限制。只有当你解决了该问题的所有版本时才能进行 hack。

Ecrade 有两个由整数构成的序列 $$$a_0, a_1, \ldots, a_{n - 1}$$$ 和 $$$b_0, b_1, \ldots, b_{n - 1}$$$。保证 $$$a$$$ 中所有元素的总和不超过 $$$b$$$ 中所有元素的总和。

初始时，Ecrade 可以对序列 $$$a$$$ 进行恰好 $$$k$$$ 次修改。保证 $$$k$$$ 不超过 $$$a$$$ 的总和。每次修改操作如下：
- 选择一个整数 $$$i$$$（$$0 \le i < n$$）满足 $$$a_i > 0$$$，并执行 $$$a_i := a_i - 1$$$。

然后，Ecrade 将对 $$$a$$$ 和 $$$b$$$ 依次执行以下三个操作，这三个操作构成一轮操作：
1. 对每个 $$$0 \le i < n$$$：$$t := \min(a_i, b_i)$$，$$a_i := a_i - t$$，$$b_i := b_i - t$$；
2. 对每个 $$$0 \le i < n$$$：$$c_i := a_{(i - 1) \bmod n}$$；
3. 对每个 $$$0 \le i < n$$$：$$a_i := c_i$$。

Ecrade 想知道，在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。

然而，这似乎有些复杂，因此请帮助他！

## 说明/提示

在第五个测试用例中，$$$a$$$ 的所有元素在恰好 $$$6$$$ 次修改后变为 $$$0$$$。

在第六个测试用例中，Ecrade 可以对 $$$a_3$$$ 进行一次修改，之后 $$$a$$$ 将变为 $$$[1,2,2,4]$$$：
- 第一轮操作后，$$a=[3,0,0,0]$$，$$b=[3,1,0,0]$$；
- 第二轮操作后，$$a=[0,0,0,0]$$，$$b=[0,1,0,0]$$。

在第七个测试用例中，Ecrade 可以对 $$$a_4$$$ 进行一次修改，之后 $$$a$$$ 将变为 $$$[2,1,1,1]$$$：
- 第一轮操作后，$$a=[0,1,0,0]$$，$$b=[0,1,1,0]$$；
- 第二轮操作后，$$a=[0,0,0,0]$$，$$b=[0,0,1,0]$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
8
3 0
1 1 4
5 1 4
4 0
1 2 3 4
4 3 2 1
4 0
2 1 1 2
1 2 2 1
8 0
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
3 6
1 1 4
5 1 4
4 1
1 2 3 4
4 3 2 1
4 1
2 1 1 2
1 2 2 1
4 2
2 1 1 2
1 2 2 1```

### 输出

```
1
4
4
8
0
2
2
1```

# 题解

## 作者：StayAlone (赞：7)

~~嗯？这不是模拟题吗？~~

一个纯模拟做法，无法从 Easy Version 导出。

时间复杂度 $\mathcal O(\frac{n^2}{w})$，但是跑得很快！

---------


当一个 $a_i$ 变成 $0$ 之后，称之为无效；当一个 $b_i$ 变成 $0$ 之后，称之为无效。可以发现，每一次操作只有 $a_i,b_i$ 均有效才有意义，每一次有意义的操作之后，要么 $a_i$ 变得无效，要么 $b_i$ 变得无效。

最初共 $2n$ 个有效元素，每次有效操作减少一个有效元素，只要能找到每一轮的有效操作，时间复杂度就是对的。

考虑用两个 bitset 分别维护 $a_i$ 和 $b_i$ 的有效状态，每一轮对 $a_i$ 的 bitset 右移，再将两个 bitset 按位与，就找到了有效操作的位置！

通过模拟，可以得知每一轮 $a_i$ 的减少量，那么原问题就迎刃而解了。

这里手写 bitset，减少每个有效操作的代价是 $\mathcal O(w)$，因为要枚举其所在的 unsigned long long。总时间复杂度 $\mathcal O(\frac{n^2}{w}+wn)$，$w$ 取 $\sqrt n$ 最优，在线求一个 $\sqrt n$ 位机。

由于一些原因，这里 $w=64$。

```cpp
int n, a[MAXN], b[MAXN], tim, mx;
ull W, k, S, Sn;
 
struct {
	ull val[3200];
	
	il int query(int i) {
		return val[i >> 6] >> (i & 63) & 1;
	}
	
	il void change(int i) {
		val[i >> 6] ^= 1ull << (i & 63);
	}
	
	il void right() {
		int p = query(n - 1);
		rep2(i, mx, 1) {
			val[i] <<= 1;
			val[i] |= val[i - 1] >> 63;
		} val[0] <<= 1; val[0] |= p;
	}
	
	il void init() {
		rep1(i, 0, mx) val[i] = -1;
	}
} bal, cas;
 
il void find() {
	rep1(i, 0, mx) if (W = (bal.val[i] & cas.val[i])) {
		int pre = i << 6;
		rep1(j, 0, 63) if (W >> j & 1) {
			int x = pre + j, y = x < tim ? x - tim + n : x - tim, t = min(b[x], a[y]);
			if (x >= n) break;
			Sn += t;
			if (!(a[y] -= t)) bal.change(x);
			if (!(b[x] -= t)) cas.change(x);
		}
	}
}
 
il void solve() {
	read(n, k); mx = n - 1 >> 6; bal.init(); cas.init(); tim = S = Sn = 0;
	rer(i, 0, n - 1, a), S += a[i]; rer(i, 0, n - 1, b);
	if (k >= S) return puts("0"), void();
	while (true) {
		find(), ++tim;
		if (Sn + k >= S) return printf("%d\n", tim), void();
		bal.right();
	}
}
 
int main() {
	for (int T = read(); T--; ) solve();
	return 0;
}
```

---

## 作者：Diana773 (赞：7)

# 问题描述
给定长度为 $n$（$1 \leq  n\leq 2 \cdot 10^5$）的两个正整数序列 $a,b$（$1\leq a_i,b_i \leq 10^9$），保证 $\sum a_i\leq \sum b_i$。
- 操作 $1$：将所有 $i \in [1,n]$ 的 $a_i$、$b_i$ 
同时减去 $\min(a_i,b_i)$，再将数组 $a$ 进行一次轮换。
- 操作 $2$：选择一个 $i \in [1,n]$，将 $a_i$ 减少 $1$。

操作 $2$ 最多进行 $k$（$0\leq k\leq 2 \cdot 10^{14}$）次，问最少进行几次操作 $1$ 序列 $a$ 会变为全部为 $0$ 的序列？

# 问题分析

- 先进行 $k=0$ 的问题的考虑，容易发现每次操作 $1$ 可以拆解成若干次 $a_i$、$b_j$ 进行减法的操作，且只有非 $0$ 的 $a_i$、$b_j$ 在操作 $1$ 中是有意义的。

- 按照操作 $1$ 的操作次数，可以得到一个时间。发现在每一对 $a_i$、$b_j$ 进行减法操作时是按照时间顺序进行的。

- 模仿 dij 最短路算法的思想，我们按照时间的先后顺序处理每一对 $a_i$、$b_j$ 的减法操作。

- 初始状态下添加 $(1,1,1),(1,2,2),(1,3,3),\ldots,(1,n,n)$ 到优先队列中，其中第 $1$ 个数代表操作发生的时间，第 $2$、$3$ 个数代表在这个时间内发生的 $a_i$、$b_j$ 的减法。

- 按照时间小优先的顺序进行操作，在 $a_i$、$b_j$ 操作进行完成之后，如果 $a_i>0$ 那么就应该为 $a_i$ 寻找最近的 $b_j>0$ 将这个新的待完成的操作添加到优先队列中。

- 可能存在 $a_i$、$b_j$，当这个操作被添加进入队列时 $b_j>0$，但是在进行操作时 $b_j=0$ 了，这样会进行一些无效运算。这样的无效运算应该不是很多，应该为 $O(n\log n)$ 级别，时间复杂度应该大约为 $O(n\log^2 n)$，通过这个优先队列的操作可以算出 $k=0$ 的答案。

- 对于 $k>0$，我们可以在这个优先队列记录过程中，记录每个操作时间操作减少的量，容易发现这些减少的量可以在一开始就减掉，并不会影响后面的操作。

- 因此直接按照操作时间逆序，看最早能减到哪个操作时间，这个操作时间就是 $k>0$ 的答案。

# 参考代码

```
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;


void solve() 
{
	int n;
	i64 k;
	cin>>n>>k;
	vector<int> a(n);
	vector<int> b(n);
	vector<int> c(n);
	for (int i=0; i<n; i++)
	  cin>>a[i];
	  
	//维护所有不为 0 的 b; 因为是一个环，所以多放一份。
	set<int> wan;
	for (int i=0; i<n; i++) 
	{
	  cin>>b[i];
	  wan.insert(i);
	  wan.insert(i+n);
	}
	
	priority_queue<array<int,3> > q; //用优先队列维护时间顺序
	for (int i=0; i<n; i++) //优先队列初始化状态
	  q.push({0,i,i});

	vector<pair<int,int> > val(0);
	val.push_back({0,0});
	
	int ans=0;
	while (!q.empty())
	{
		auto ccf=q.top();
		q.pop();
		ans=-ccf[0]+1;
		int ia=ccf[1];
		int ib=ccf[2];
		if (ib>=n)
		  ib-=n;

		//进行操作
		int minab=min(a[ia],b[ib]);
		a[ia]=a[ia]-minab;
		b[ib]=b[ib]-minab;
		val.push_back({-ccf[0]+1,minab});
		
		if (b[ib]==0)
		{
			//删除为 0 的 b
			wan.erase(ib);
			wan.erase(ib+n);
		}
		if (a[ia]>0)
		{
			//如果 a 不为 0 则继续加入优先队列
			auto cf=*wan.lower_bound((ia-ccf[0])%n);
			q.push({-(-ccf[0]+(cf-(ia-ccf[0])%n)),ia,cf});
		}
	}
	int sz=val.size();
	
	//倒序找最早能减到哪个操作
	for (int i=sz-1; i>=1; i--)
	{
		if (k>=0 && val[i].second>=0)
		{
			i64 minab=min(k,(i64)val[i].second);
			k=k-minab;
			val[i].second=val[i].second-minab;
			if (val[i].second==0)
			  ans=min(ans,val[i-1].first);
			if (val[i].second>k)
			  break;			  
		}
	}
	
	cout<<ans<<'\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t=1;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

```

---

## 作者：Stupid_CCCat (赞：5)

# 题意描述

给定两个长度为 $n$ 的整数序列 $a$ 和 $b$，保证 $a$ 的元素和不超过 $b$ 的元素和。需对 $a$ 进行以下操作恰好 $k$ 次：选择任意 $a_i$（满足 $a_i > 0$），使得 $a_i=a_i-1$。

之后按以下操作循环处理：

每轮操作流程：

1. 对每个位置 $i$，对 $a_i$ 和 $b_i$ 同时减去 $a_i$ 和 $b_i$ 的较小值。
2. 构造新序列 $c$，其中 $c_i = a_{(i-1) \bmod n}$。
3. 将 $c$ 复制给 $a$。

目标：找到经过恰好 $k$ 次减操作后，使 $a$ 全变为 $0$ 所需的最少操作轮数。

# 解题思路

***声明：以下序列下标均从 $0$ 开始。***

## Easy Version

+ 首先，我们容易证明经过至多 $n$ 轮操作即可使 $a$ 全变为 $0$，因为在经过 $n$ 轮操作后，任意 $a_i$ 和任意 $b_i$ 都已匹配过一次，且 $sum_a \leq sum_b$。

+ 考虑破环成链，将 $a$ 与 $b$ 都循环延长，即：$a_i=a_{i-n}$，$b_i=b_{i-n}$（$n\leq i < 2n$），那么我们可以发现，对于每个 $a_i$（$0 \leq i < n$），只可能和 $b_j$（$i \leq j < i+n$）匹配。

+ 可以仿照括号匹配，将 $a_i$ 当作左括号，对每个 $b_i$ 我们优先和左边第一个不为 $0$ 的 $a_i$ 匹配。
+ 从左到右枚举 $i$，将每个不为 $0$ 的  $a_i$ 入栈，然后 $b_i$ 和不断和栈首的 $a_j$ 匹配，直到栈空或者 $b_i=0$，匹配的同时更新最大操作轮数，因为 $b_i$ 和 $a_j$ 匹配需要经过 $i-j+1$ 轮，即 $ans=max(ans,i-j+1)$。 

+ 为什么这样是正确的呢？可能有人会问：这是一个环，如果对于某个 $b_i$，前面所有的 $a_j$ 都为 $0$，那应该从序列尾开始找最后一个不为 $0$ 的 $a_j$ 与当前 $b_i$ 匹配呀。所以我们破环成链，当我们维护 $a_j$ （$j<n$） 和 $b_i$ （$i<n$） 时，我们需要同时维护 $a_{j+n}$ 和  $b_{i+n}$，这样，当我们枚举到 $b_{i+n}$，它的意义和 $b_i$ 是一样的，假设真的存在一个 $a_j$ （$i<j<n$） 和 $b_i$ 匹配，这个 $a_j$ 就会和 $b_{i+n}$ 匹配上。

+ 时间复杂度为 $O(n)$。

## Hard Version

+ 考虑二分答案，检查需要多少次$a_i=a_i-1$ 的操作，才能使轮数不超过 $mid$。

+ 设需要 $ans$ 次操作，才能使轮数不超过 $mid$，$ans$ 初始值为 $0$。

+ 我们知道 $b_i$ 和 $a_j$ 匹配需要经过 $i-j+1$ 轮，当 $i-j+1>=mid$ 时，我们不能进行匹配了，所以当前的 $a_j$ 就需要用初始的次数去将它减少到 $0$，即 $ans+=a_j$。

+ 二分答案即可，时间复杂度为 $O(nlogn)$。

# 代码呈现

## Easy Version

```c++
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

void solve()
{
	int n,k;
	cin>>n>>k;
	vector<int> a,b;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		a.push_back(x);
	}
	for(int i=0;i<n;i++)
		a.push_back(a[i]);
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		b.push_back(x);
	}
	for(int i=0;i<n;i++)
		b.push_back(b[i]);
	stack<int> stk;
	int ans=0;
	for(int i=0;i<2*n;i++)
	{
		if(a[i])
			stk.push(i);
		while(!stk.empty()&&b[i])	
		{
			int now=stk.top();
			ans=max(ans,i-now+1);
			int minn=min(a[now],b[i]);
			b[i]-=minn,a[now]-=minn;
			if(i<n)
				b[i+n]-=minn,a[now+n]-=minn;
			if(a[now]==0)
				stk.pop();
		}
	}
	cout<<ans<<endl;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)
		solve();
}
```

## Hard Version

```c++
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

int check(int n,int mid,vector<int> a,vector<int> b)
{
	stack<int> stk;
	int ans=0;
	for(int i=0;i<2*n;i++)
	{
		if(a[i])
			stk.push(i);
		while(!stk.empty()&&b[i])	
		{
			int now=stk.top();
			if(i-now+1>mid)
			{
				ans+=a[now];
				a[now]=0;
				if(now<n)
					a[now+n]=0;
				stk.pop();
			}
			else
			{
				int minn=min(a[now],b[i]);
				b[i]-=minn,a[now]-=minn;
				if(i<n)
					b[i+n]-=minn,a[now+n]-=minn;
				if(a[now]==0)
					stk.pop();
			}
		}
	}
	return ans;
}
void solve()
{
	int n,k;
	cin>>n>>k;
	vector<int> a,b;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		a.push_back(x);
	}
	for(int i=0;i<n;i++)
		a.push_back(a[i]);
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		b.push_back(x);
	}
	for(int i=0;i<n;i++)
		b.push_back(b[i]);
	int l=0,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(n,mid,a,b)>k)
			l=mid+1;
		else
			r=mid;
	}
	cout<<l<<endl;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)
		solve();
}
```

---

## 作者：zhengjinyi (赞：3)

## Problem
给定序列 $a,b$，$k$ 次操作将 $a$ 选择一个元素 $-1$。$a_i$ 每回合向右循环移位一格并且与 $b_i$ 对消，即令 $a_i$ 和 $b_i$ 都减去两者最小值。求最小的移动轮数。

## Easy Version
显然每轮每个位置都会有至少一个数变为 $0$，可以看作二者互相湮灭。由于 $\sum a\le\sum b$，所以一定能将 $a$ 全部消为 $0$。任意一个 $a_i$ 在完成 $n$ 轮后会与每一个相遇的 $b_j$ 进行对消，因此答案上界为 $n$。\
注意到答案其实就是最大的 $a_i$ 在变为 $0$ 之前移动的距离 $+1$。\
一起处理多个 $a_i$ 是比较麻烦的，所以考虑单独计算每个 $a_i$ 移动距离，模拟每个 $a_i$ 向后移动与对消的过程。\
先不考虑环上问题，展开到链上求解，发现从后往前计算可以规避后效性。\
现在问题转变为如何处理末尾向后移动到开头时产生的影响。将环展开并且复制 $2$ 遍，划分为 $[1,n],[n+1,2n],[2n+1,3n]$ 三个周期。\
从 $i=2n$ 开始遍历 $a$ 数组。在模拟第二个周期时，不考虑第三周期的 $a$ 对 $b$ 的影响，这样保证了第一周期的 $a_i$ 从末尾走到第二周期时 $b$ 数组值的正确性。根据前面的结论，每个 $a_i$ 移动距离都不超过 $n$，因此也不会产生循环移动的结果。
### Example
```
a: 1 2 3
b: 3 2 1
```
对第二周期进行移动后：
```
a: 1 2 3 0 0 0
b: 3 2 1 2 0 0 1 2 1
```
直接模拟移动过程是 $O(n^2)$ 的，依旧很劣。但是可以利用链表维护下一个非 $0$ 的 $b_j$ 位置，做到均摊 $O(n)$（因为每个 $b_j$ 只会被删一次）。\
可以通过 Easy Version。
## Hard Version
扩展为正解是不难的。观察求解 Easy Version 的过程，答案仅和最大移动距离有关，而我们希望让这个最大值最小。\
二分答案！\
每当 $a_i$ 即将超出限定的移动距离，我们再将 $a_i$ 的初始值减去它剩余的值，这样可以保证其现在的值为 $0$，不再移动。
判一下减值的总和与 $k$ 的大小关系就做完了。\
复杂度 $O(n\log n)$。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define R read<ll>()
#define fi first
#define se second
using namespace std;
template <typename T> inline T read(){
	T x=0,fl=1; char c=getchar();
	while(c<'0'||c>'9') (c=='-'?fl=-1:0),c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*fl;
}
void print(auto *arr,int len){ for(int i=1;i<=len;i++) cout<<arr[i]<<" "; cout<<endl; }
const int inf=0x3f3f3f3f,N=600005;
const ll INF=0x3f3f3f3f3f3f3f3f;
int T,n,at[N],ab[N],c[N],b[N],pre[N],nxt[N];
ll k;
bool check(int x){
	for(int i=1;i<=n;i++) c[i]=c[i+n]=c[i+2*n]=at[i];
	for(int i=1;i<=n;i++) b[i]=b[i+n]=b[i+2*n]=ab[i];
	for(int i=1;i<=3*n;i++) pre[i]=i-1,nxt[i]=i+1;
	auto del=[](int i){ nxt[pre[i]]=nxt[i],pre[nxt[i]]=pre[i]; };
	ll sum=0;
	for(int i=2*n;i;i--){
		for(int j=i;;j=nxt[j]){
			if(c[i]>b[j]) c[i]-=b[j],b[j]=0,del(j);
			else{
				b[j]-=c[i];
				if(!b[j]) del(j);
				break;
			}
			if(nxt[j]-i+1>x){
				if(i<=n) sum+=c[i];
				break;
			}
		}
	}
	return sum<=k;
}
void solve(){
	n=R,k=R;
	int ans=0; ll sa=0;
	for(int i=1;i<=n;i++) at[i]=R,sa+=at[i];
	for(int i=1;i<=n;i++) ab[i]=R;
	if(sa==k){ puts("0"); return; }
	int l=0,r=n+1,mid;
	while(l+1<r){
		mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%d\n",r);
}
int main(){
	T=R;
	while(T--) solve();
	return 0;
}
```

---

