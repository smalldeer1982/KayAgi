# Counting Pairs

## 题目描述

给定一个整数序列 $ a $，长度为 $ n $，其中第 $ i $ 个元素为 $ a_i $。此外，还有两个整数 $ x $ 和 $ y $，且满足 $ x \le y $。

如果一对整数 $ (i, j) $ 满足以下条件，则称其为有趣的：

- $ 1 \le i < j \le n $；
- 从序列 $ a $ 中同时移除位置 $ i $ 和 $ j $ 的元素后，剩余元素的和在 $ x $ 和 $ y $ 之间。

你的任务是找出给定序列 $ a $ 中有多少对这样的有趣整数组合。

## 说明/提示

例如，在第一个示例中，有 $ 4 $ 个有趣的整数组合：

1. $ (1, 2) $；
2. $ (1, 4) $；
3. $ (2, 3) $；
4. $ (3, 4) $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7
4 8 10
4 6 3 6
6 22 27
4 9 6 3 4 5
3 8 10
3 2 1
3 1 1
2 3 4
3 3 6
3 2 1
4 4 12
3 3 2 1
6 8 8
1 1 2 2 2 3```

### 输出

```
4
7
0
0
1
5
6```

# 题解

## 作者：JimmyQ (赞：4)

# CF2051D Counting Pairs
## 思路
首先给数组排个序，然后再暴力枚举 $i$，不难发现所有符合的 $j$ 一定是连续的，所以再二分计算出符合数列的开头以及结尾。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300005
long long t,n,x,y,a[N],ans,sum;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x>>y;
		sum=ans=0;
		for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
		sort(a+1,a+n+1);
		for(long long i=1;i<=n;i++){
			long long pos1=lower_bound(a+i+1,a+n+1,sum-y-a[i])-a;//开头
			long long pos2=upper_bound(a+i+1,a+n+1,sum-x-a[i])-a-1;//结尾
			if(sum-y-a[i]<=a[pos1]&&a[pos2]<=sum-x-a[i]) ans+=pos2-pos1+1;//别忘了+1
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```
[AC 记录](https://codeforces.com/contest/2051/submission/298491422)
###### ~~我才不会告诉你我赛事因为调试代码和数组大小挂了2次。~~

---

## 作者：OIerWu_829 (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/CF2051D) / [Codeforces 传送门](https://codeforces.com/contest/2051/problem/D)

恼，赛时调了半天才 AC，问题包括算错时间复杂度……

---

我们设 $a$ 数组的总和为 $sum$，则可以转换一下题目中的定义：

$$x\le sum-a_i-a_j\le y$$

$$sum-y\le a_i+a_j\le sum-x$$

问题理解后，我们先把 $a$ 数组从小到大排个序，然后遍历每个元素 $a_i$，设移除 $a_i$ 后的剩余元素总和为 $sum-a_i$，可以使用 `lower_bound()` 和 `upper_bound()` 来确定满足条件 $sum-y$ 和 $sum-x$ 的 $a_j$ 的范围。具体就是先用 `lower_bound()` 找到第一个 $\ge sum-y$ 的位置，再用 `upper_bound()` 找到第一个 $>sum-x$ 的位置，然后两个位置之间的元素就是满足条件的 $a_j$，所以我们把答案加上这两个位置的距离，也就是它们的差的绝对值，最后输出即可。

遍历的 $\Theta(n)$，加上查找的 $\Theta(\log n)$，整体时间复杂度 $\Theta(n\log n)$，在 $2\cdot10^5$ 的数据范围下可以通过。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const LL N = 2e5 + 5;

LL a[N];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	LL T;
	cin >> T;
	while (T--)
	{
		LL n, x, y;
		cin >> n >> x >> y;
		LL sum = 0;
		for (LL i = 1; i <= n; i++)
		{
			cin >> a[i];
			sum += a[i];
		}
		sort(a + 1, a + 1 + n);
		LL ans = 0;
		for (LL i = 1; i <= n; i++)
		{
			sum -= a[i];
			auto lb = lower_bound(a + 1 + i, a + 1 + n, sum - y);
			auto ub = upper_bound(a + 1 + i, a + 1 + n, sum - x);
			ans += abs(lb - ub);
			sum += a[i];
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：imljw (赞：2)

比较简单，赛时无压力通过。

我们可以将 $a$ 数组升序排序，枚举每一个数 $a_i$，二分查找找到最左边的和最右边的满足条件的数 $a_l$ 和 $a_r$，那么 $a_i$ 的贡献就是 $r - l + 1$，把答案加起来即可。

赛时代码，不喜勿喷。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,a[200005],x,y,an,sum;
int main() {
	std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--){
    	cin>>n>>x>>y;
    	an=sum=0;
    	for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
    	sort(a+1,a+n+1);
    	for(int i=1;i<=n;i++){
    		if(sum-a[i]<=x)break;
    		int l=1,r=n,p=0;
    		while(l<=r){
    			int mid=l+r>>1;
    			if(a[mid]<=sum-x-a[i])p=mid,l=mid+1;
    			else r=mid-1;
			}
			if(p<1)break;
			l=1,r=n;
			int q=0;
			while(l<=r){
				int mid=l+r>>1;
				if(a[mid]>=sum-y-a[i])q=mid,r=mid-1;
				else l=mid+1;
			}
			if(p&&q&&p>=q)an+=max(0,p-q+1-(q<=i&&p>=i));
		}
		cout<<an/2<<'\n';
	}
	return 0;
}
```

---

## 作者：Ambrose0321 (赞：1)

比较简单的一道题


思路：
---

枚举位置 $i$，然后二分 $j$ 即可，最后答案要除以 $2$。


AC code:
---


```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
int _, n, a[200001];
ll x, y, ans, sum;
int main() {
	scanf("%d", &_);
	for (; _--; ) {
		scanf("%d%lld%lld", &n, &x, &y);
		ans = sum = 0;
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]), sum += a[i];
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) {
			ans += upper_bound(a + 1, a + n + 1, sum - x - a[i]) - lower_bound(a + 1, a + n + 1, sum - y - a[i]);
			ll t = sum - 2LL * a[i];
			if (t >= x && t <= y)
				--ans;
		}
		printf("%lld\n", ans / 2);
	}
}
```
求过审 qwq。

---

## 作者：Elysia_019 (赞：1)

这里提供一个双指针的思路。

### 思路

简单来说，整体的思路是排序 + 双指针。

假设整个数组之和为 $sum$，那么题目所给的条件即为 $x \le sum - (a_i + a_j) \le y$。这个条件可以转化为 $sum - y - a_i \le a_j \le sum - x - a_j$。所以我们可以考虑固定左端点 $i$ 后统计可行的右端点 $j$ 的数量。

注意到原数组顺序对结果没有影响，所以我们可以先进行排序, 此时 $j$ 的可能取值会分布在一个区间内，我们只需要找到这个区间的左右端点 $pmin$ 和 $pmax$ 即可。

考虑到我们要维持和在同一个区间内，可以发现随着左指针 $l$ 的右移，$pmin$ 和 $pmax$ 要么不动，要么左移，所以可以用双指针来做。

考虑到需要排序，时间复杂度是 $O(n \log n)$。

### 核心代码

```c++
using ll = long long;

const ll maxn = 2e5 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3fLL;

ll n, x, y;
ll a[maxn];

void solve(void) {
    cin >> n >> x >> y;

    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    sort(a + 1, a + n + 1);
    a[n + 1] = inf; // 哨兵值

    ll min_sum = sum - y;
    ll max_sum = sum - x;

    ll ans = 0;
    int l = 1, pmin = n + 1, pmax = n + 1;
    while (l < pmax) {
        // a[l] + a[pmin] >= min_sum, a[l] + a[pmax] <= max_sum
        while (pmin > l && a[l] + a[pmin - 1] >= min_sum) {
            pmin--;
        }
        while (pmax > l && a[l] + a[pmax] > max_sum) {
            pmax--;
        }

        int cnt = pmax - max(pmin, l + 1) + 1;
        if (cnt > 0) {
            ans += cnt;
        }

        l++;
    }

    cout << ans << endl;
}
```

### 其他

完整代码：[Codeforces](https://codeforces.com/contest/2051/submission/300910915) (93ms)。

---

## 作者：postpone (赞：1)

将题目的条件转化一下：

$$
x \leq sum - a_i - a_j \leq y \\
sum - a_i - y \leq a_j \leq sum - a_i - x
$$

那么可以二分对每个元素统计其贡献。我的方法是：对每个元素，先判断和它自己是不是满足条件，然后二分查找上界和下界，最后将统计的和减半就是答案。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    ll x, y;
    cin >> n >> x >> y;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll sum = accumulate(a.begin(), a.end(), 0ll);
    
    ranges::sort(a);

    ll ans{};
    for (auto i : a) {
        // 如果它和它自己的组合能满足条件，就要先减去这部分的贡献
        if (x <= sum - 2ll * i and sum - 2ll * i <= y) {
            ans--;
        }
        auto l = lower_bound(a.begin(), a.end(), sum - i - y);
        auto r = upper_bound(a.begin(), a.end(), sum - i - x);
        ans += (r - l);
    }

    cout << ans / 2 << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    for (cin >> T; T--;) {
        solve();
    }

    return 0;
}
```

---

## 作者：Roy_2010 (赞：0)

# CF2051D Counting Pairs 题解
这里提供一种特殊的方法。见特殊方法部分。
## 思路
不难发现，如果数组总和为 $sum$，我们选定了 $a_i$ 这一个元素，那么有以下式子。
$$sum-y-a_i \le a_j \le sum-x-a_i$$
现在只要考虑如何快速求出符合要求的 $a_j$ 数量。\
有人说先排序，然后双指针。\
话是这么说，但笔者在赛场上没有想到**排序后数组的合法对数量不变**，所以我们考虑另一种方法。
## 特殊方法
我们将数据离散化一下扔到树状数组里，~~不想离散化也可以用平衡树~~，这样对每个元素先查询再加入树状数组即可。有一些细节在代码中展示。
## Code
树状数组解法。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int T;

int n;
ll x,y;
int a[200050];
ll lsh[600050];
int tp=0;

struct BIT{
	int Tree[600050];
	void Clear(){for(int i=1;i<=tp;++i){Tree[i]=0;}}
	int Lowbit(int x){return x&(-x);}
	void Update(int x){for(int i=x;i<=tp;i+=Lowbit(i)){++Tree[i];}} 
	int Query(int x){int s=0;for(int i=x;i;i-=Lowbit(i)){s+=Tree[i];}return s;}
}tr;

void Work(){
	tp=0;
	cin>>n>>x>>y;
	ll sum=0;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=1;i<=n;++i){
		lsh[++tp]=a[i];
		lsh[++tp]=sum-x-a[i];
		lsh[++tp]=sum-y-a[i];
    //不一定要全放进去，但全放进去可能会方便一点
	} 
	sort(lsh+1,lsh+tp+1);
	tp=unique(lsh+1,lsh+tp+1)-lsh-1;
	tr.Clear();
	/*
	for(int i=1;i<=tp;++i){
		cout<<lsh[i]<<' ';
	}
	cout<<'\n';
	*/
	ll ans=0;
	for(int i=1;i<=n;++i){
		ans+=(tr.Query(lower_bound(lsh+1,lsh+tp+1,sum-x-a[i])-lsh)-tr.Query(lower_bound(lsh+1,lsh+tp+1,sum-y-a[i])-lsh-1));
		//cout<<lower_bound(lsh+1,lsh+tp+1,y-a[i])-lsh<<' '<<lower_bound(lsh+1,lsh+tp+1,x-a[i])-lsh-1<<'\n';
		tr.Update(lower_bound(lsh+1,lsh+tp+1,a[i])-lsh);
	}
	cout<<ans<<'\n';
	return ;
}

int main(){
	cin>>T;
	for(int i=1;i<=T;++i){
		Work();
	}
	return 0;
}
```
时间复杂度 $O(n\log n)$。

---

## 作者：ybclch2026 (赞：0)

# CF2051D Counting Pairs

## 思路
只选两个数，枚举一个数，再利用二分求出符合条件的两个极端下标，求差在全部加起来即可。
## 细节
我们假设总和是 $sum$，那么条件可转化为 $x≤sum-a_i≤y$，那么用二分求的答案范围为 $sum-a_i-y≤a_j≤sum-a_i-x$。$a_j≤sum-a_i-x$ 用 `upper_bound()` 求，$sum-a_i-y≤a_j$ 用 `lower_bound` 求，该答案为两个的差。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2e5+5;
int T,n;
ll x,y,a[maxn],sum,ans;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        sum=ans=0;
        cin>>n>>x>>y;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            sum+=a[i];
        }
        sort(a+1,a+1+n);
        a[n+1]=0x7f7f7f7f;
        for(int i=1;i<=n;i++){
            int op=upper_bound(a+i+1,a+2+n,sum-a[i]-x)-a-1;
            int oq=lower_bound(a+i+1,a+2+n,sum-a[i]-y)-a;
//不重复计算，范围为i到n。
            if(op>n||op<=i)op=-5;//不符要求
            if(oq<=i||oq>n)oq=-5;//不符要求
            if(op!=-5&&oq!=-5)ans+=max(op-oq+1,0);//得答案
        }
        cout<<ans<<endl;
    }
    return 0;
} 
```

---

## 作者：沉石鱼惊旋 (赞：0)

# D. Counting Pairs

枚举一个 $a_i$，设 $s=\sum\limits_{i=1}^n a_i$，那么我们就是要找 $a_j$ 的数量满足 $x \leq s - a_j \leq y$，移项得到 $s - y \leq a_j \leq s - x$。

把数组复制一份一样的 $b$ 进行**排序**，通过**二分**求出满足条件的 $s - y \leq b_j \leq s - x$ 的 $j$ 的范围。那么 $a_i$ 和这些 $b_j$ 都可以满足条件。如果 $b_j$ 里包含了 $a_i$ 要减掉一的贡献。

这里计算的是无序对的数量，有序对数量除以二即可。

<https://codeforces.com/contest/2051/submission/297830381>

---

## 作者：DoubleQLzn (赞：0)

首先思考，什么双元组删掉后可以使得和大于等于 $x$，且小于等于 $y$。

令双元组的和为 $sum$，总和为 $s$，则有不等式 $x\le sum-s\le y$。可以转化成 $sum-y\le s\le sum-x$。因此，双元组的最大和 $ma$ 是 $sum-x$，最小 $mi$ 是 $sum-y$。

一个数字确定，另一个数字 $x$ 的范围就是 $mi\le ma\le x$，可以在数组中进行二分答案。为了确保问题的单调性，记得排序。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t,n,m,k;
	cin>>t;
	while(t--){
		int x,y,s=0;
		cin>>n>>x>>y;
		for(int i=1;i<=n;i++)cin>>a[i],s+=a[i];
		int mi=s-y,ma=s-x,ans=0;
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			if(a[i]<ma){
				int l=lower_bound(a+1,a+n+1,mi-a[i])-a;
				int r=upper_bound(a+1,a+n+1,ma-a[i])-1-a;
				if(l>r)continue;
				if(l<=i)l=i+1;
				if(r<=i)continue;
				if(l>=1&&l<=n&&r>=1&&r<=n)ans+=(r-l+1);
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Even_If (赞：0)

~赛时能切真的意想不到。~

# $\texttt{Solution}$
不难发现，这样枚举数对的题，其实跟顺序无关。所以我们可以先给整个序列排序。

然后，顺序枚举每个元素，求出删除当前元素之后，最多和最少还能减去多少，然后在 $i + 1$ 到 $n$ 的区间二分满足要求的数的区间，累计答案即可。

# $\texttt{Code}$
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10;

int tt;

int n, x, y;

int sum;

int vec[N];

signed main() {
	cin >> tt;

	while (tt --) {
		cin >> n >> x >> y;
		sum = 0; // 多测要清空。

		for (int i = 1; i <= n; i ++) {
			cin >> vec[i];

			sum += vec[i]; // 累加和。
		}

		int ans = 0;

		sort(vec + 1, vec + n + 1); // 排序后才能二分

		for (int i = 1; i <= n; i ++) {
			int v1 = sum - vec[i] - x; // 最大还能删的数。
			int v2 = sum - vec[i] - y; // 最小还能删的数。

			int l = upper_bound(vec + i + 1, vec + n + 1, v1) - vec; // 注意这里是 upper_bound，位置 l 的元素其实是不满足要求的。
			int r = lower_bound(vec + i + 1, vec + n + 1, v2) - vec;

			ans += (l - r); // 因为前面是 upper_bound 所以不用加 1。
		}

		cout << ans << endl;
	}

    return 0;
}
```

---

## 作者：Lfz312g (赞：0)

# solution
## 题目分析
一对整数 $(i,j)$ 被计入答案，只当满足： 
$$ 
x \le sum-a_i-a_j \le y
$$
也就是：  
$$
sum-a_i -y \le a_j \le sum-a_i-x
$$
因此，我们可以遍历每一个 $i$，二分查找在此区间的元素个数，加到计数器里。  
由于需要满足 $i \ne j$，如果自身满足：
$$
sum-a_i-y \le a_i \le sum-a_i-x
$$
则需要将计数器减一，删去不符合条件的情况。   
最后将计数器减半即为答案。  
单组时间复杂度：$O(n \log n)$。
## 代码实现

```cpp
#include <bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
ll a[200005];
void solve() {
	ll n,x,y;
	ll sum=0;
	cin>>n>>x>>y;
	ffor(i,1,n) cin>>a[i],sum+=a[i];
	sort(a+1,a+1+n);
	ll ans=0;
	ffor(i,1,n) {
		if (x<=sum-2*a[i]&&sum-2*a[i]<=y) ans--;
		ans+=upper_bound(a+1,a+1+n,sum-a[i]-x)-lower_bound(a+1,a+1+n,sum-a[i]-y);
	}
	cout<<ans/2<<'\n';
}
int main()
{
	int t;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：cqbzhzf (赞：0)

[vjudge中文翻译](https://vjudge.net/problem/CodeForces-2051D#author=GPT_zh)
### 思路
读完题目，可以整理出如果整数对 $(i,j)$ 是一对有趣整数对，那么必须满足 $x\le \sum_{i=1}^{n}a_i -a_i-a_j\le y$，移项，得 $a_j\le \sum_{i=1}^{n}a_i -a_i-x$ 和 $a_j \ge \sum_{i=1}^{n}a_i -a_i-y$，于是我们可以遍历数组，利用两个不等式二分得到每一个 $i$ 对应的 $j$ 的范围 $id\le j \le id2$ 即可，即每一个 $i$ 的答案为 $id2-id$，总时间复杂度为 $O(t n\log n)$。

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
int t,n;
ll x,y,a[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		ll ans=0,sum=0;
		cin>>n>>x>>y;
		for(int i=1;i<=n;i++)
			cin>>a[i],sum+=a[i];
		sort(a+1,a+n+1);
		for(int i=1;i<n;i++)
		{
			int id=lower_bound(a+i+1,a+n+1,sum-a[i]-y)-a;
			int id2=upper_bound(a+i+1,a+n+1,sum-a[i]-x)-a;
			ans+=id2-id;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：luoYiCheng_PrOI (赞：0)

### 分析
此题的 $t\le10^4,\sum_{i=1}^{t}n\le2\times10^5$，此时可以 $O(n\log{n})$ 二分求解答案。

### 解题方法
1. 设 $a$ 数组的总和为 $sum$，则可以转换一下题目中的定义：
+ $x\le sum-a_i-a_j\le y$
+ $sum-y\le a_i+a_j\le sum-x$

2. 将 $a$ 数组从小到大排序。
  
3. 然后遍历每个元素 $a_i$，设移除 $a_i$ 后的剩余元素总和为 $sum-a_i$。

4. 先用 `lower_bound()` 找到第一个 $\ge sum-y$ 的位置，再用 `upper_bound()` 找到第一个 $>sum-x$ 的位置，然后两个位置之间的元素就是满足条件的 $a_j$，所以我们把答案加上这两个位置的距离，也就是它们的差的绝对值，输出即可。

### 总结
最终代码时间复杂度 $O(n\log{n})$。

---

