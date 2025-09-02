# Buying gifts

## 题目描述

Little Sasha has two friends, whom he wants to please with gifts on the Eighth of March. To do this, he went to the largest shopping center in the city.There are $ n $ departments in the mall, each of which has exactly two stores. For convenience, we number the departments with integers from $ 1 $ to $ n $ . It is known that gifts in the first store of the $ i $ department cost $ a_i $ rubles, and in the second store of the $ i $ department — $ b_i $ rubles.

Entering the mall, Sasha will visit each of the $ n $ departments of the mall, and in each department, he will enter exactly one store. When Sasha gets into the $ i $ -th department, he will perform exactly one of two actions:

1. Buy a gift for the first friend, spending $ a_i $ rubles on it.
2. Buy a gift for the second friend, spending $ b_i $ rubles on it.

Sasha is going to buy at least one gift for each friend. Moreover, he wants to pick up gifts in such a way that the price difference of the most expensive gifts bought for friends is as small as possible so that no one is offended.

More formally: let $ m_1 $ be the maximum price of a gift bought to the first friend, and $ m_2 $ be the maximum price of a gift bought to the second friend. Sasha wants to choose gifts in such a way as to minimize the value of $ \lvert m_1 - m_2 \rvert $ .

## 说明/提示

In the first test case, Sasha has two possible options: buy a gift for the first friend in the first department, and the second friend — in the second department, or vice versa. In the first case, $ m_1 = m_2 = 1 $ , and in the second case — $ m_1 = m_2 = 2 $ . In both cases, the answer is $ 0 $ . In the second test case, you can buy gifts for the first friend in the $ 2 $ , $ 4 $ and $ 5 $ departments, and for the second friend — in the $ 1 $ and $ 3 $ departments.So $ m_1 = \max(2, 4, 2) = 4 $ , $ m_2 = \max(5, 3) = 5 $ . The answer is $ \lvert 4 - 5 \rvert = 1 $ .

## 样例 #1

### 输入

```
2
2
1 2
2 1
5
1 5
2 7
3 3
4 10
2 5```

### 输出

```
0
1```

# 题解

## 作者：芷陌陌吖 (赞：9)

[更好的阅读体验](https://www.cnblogs.com/zhimomoya-blog/articles/Solution-CF1801B.html)

### 题意

有 $n$ 个商店，在第 $i$ 个商店会进行下面两个操作之一：

- 为朋友 A 买礼物，花费 $a_i$ 元。
- 为朋友 B 买礼物，花费 $b_i$ 元。

求在每个商店进行过以上操作后，朋友 A 和 B 获得的礼物中的最大价值之差的最小值。

有 $t$ 组测试数据。

数据范围：$1\le t\le1000$，$2\le n\le5\times 10^5$，$0\le a_i, b_i\le 10^9$。

### 题解

我们选择选枚举朋友 A 的最大价值，即把 $a_i$ 和 $b_i$ 按照 $a_i$ 从小到大排序。

如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/cq2m0fus.png)

上面一排表示朋友 A，下面表示朋友 B。（已排序）

红色表示我们当前枚举到的 A 收到的最大价值的礼物。

设 $m1$ 表示上图红色点表示的价值。

![](https://cdn.luogu.com.cn/upload/image_hosting/0i34lpud.png)

因此绿色一定是 B 收到的礼物。

设 $m2$ 为当前绿色中的最大价值。

如果 $m1<m2$，那么红色左侧的礼物应该都给 A，这样 A 的最大值为 $m1$ 不变，B 的最大值仍为 $m2$，$ans=m2-m1$，一定最优。（如下图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/skbl9vgu.png)

如果 $m1>m2$，那么我们在红色左侧和 $m2$ 中找到一个最接近 $m1$ 的值给 B，这样一定最优。（如下图所示）

![](https://cdn.luogu.com.cn/upload/image_hosting/39nkjlcc.png)

具体实现方法：（可见代码）

1. 建两个 `multiset`，存下上面枚举的红色点前面的值和后面的值。（枚举向后动态更新两个 `multiset` 即可）
2. 寻找最接近的值可以在 `multiset` 中插入这个值，然后查询它的前驱和后继即可。

（使用指针时注意边界问题）

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int t,n,ans;
struct node
{
	int id,a,b;
}s[N];
multiset <int> pre,nxt;               //前后两个 multiset
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while (c<'0'||c>'9')
	{
		if (c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while (c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9)
	{
		write(x/10);
	}
	putchar((x%10)^48);
	return;
}
inline bool cmp(node a,node b)
{
	return a.a<b.a;
}
int main()
{
	t=read();
	while (t--)
	{
		ans=0x3fffffff;
		nxt.clear();
		pre.clear();
		n=read();
		for (int i=1;i<=n;i++)
		{
			s[i].id=i;
			s[i].a=read();
			s[i].b=read();
			nxt.insert(s[i].b);
		}
		sort(s+1,s+n+1,cmp);            //排序
		for (int i=1;i<=n;i++)
		{
			nxt.erase(nxt.find(s[i].b));
			auto w=nxt.end();
			int maxn=-0x3fffffff;
			if (!nxt.empty())          //找出后面最大的值
			{
				w--;
				maxn=*w;
			}
			if (maxn>s[i].a)
			{
				if (ans>maxn-s[i].a)
				{
					ans=maxn-s[i].a;
				}
			}
			else
			{
				if (ans>s[i].a-maxn)
				{
					ans=s[i].a-maxn;
				}
				auto it=pre.insert(s[i].a),ed=pre.end();
				ed--;
				if (it!=pre.begin())       //查前驱和后继
				{
					it--;
					if (ans>s[i].a-(*it))
					{
						ans=s[i].a-(*it);
					}
					it++;
				}
				if (it!=ed)
				{
					it++;
					if (ans>(*it)-s[i].a)
					{
						ans=(*it)-s[i].a;
					}
					it--;
				}
				pre.erase(it);
				
			}
			pre.insert(s[i].b);
		}
		write(ans);
		puts("");
	}
	return 0;
}
```



---

## 作者：lingying (赞：5)

本人这题考试时交了 $9$ 次才过，结果被 CF 当场 FST，特写一篇题解来寄念一下。


## 题意

你需要把 $n$ 个礼物不差不漏地送给你的两个朋友，把第 $i$ 个礼物送给第一个朋友要花 $a_i$ 元，送给第二个朋友要花 $b_i$ 元。现在问你，你所花费的 $a_i$ 的最大值与 $b_i$ 的最大值差的绝对值最小可以是多少。

注意一个礼物只能送给一个朋友且两个朋友都要分到至少一个礼物。

## 做法

首先想到把这 $n$ 个礼物按照 $a_i$ 来排序，然后枚举每一个点来作为你所选的送给第一个朋友的最大值。

接着我们分类讨论一下。

我们设 $m_i=\max\limits_{a_j>a_i}b_j$ 以及 $s_i=\min\limits_{a_j\le a_i}{\left\vert b_j-a_i \right\vert}$。

如果 $m_i\ge a_i$，那么我们选它当做送给第一个朋友的礼物中的最大值的答案就是 $m_i-a_i$。

如果 $m_i<a_i$，那么我们选它当做送给第一个朋友的礼物中的最大值的答案就为 $\min(s_i,a_i-m_i)$。

我们发现 $m_i$ 可以一次 $O(n)$ 的预处理，$s_i$ 可以用 `set` 维护，这道题就做完了。

时间复杂度 $O(n\log n)$。

细节不是很多，不过要注意 $m_{n+1}$ 一开始一定要赋值为 $-10^9$，不然的话会在第 $69$ 个点上错误，听说这个点卡掉了不上考试时的正确代码（包括我）。

## 代码

```
#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;

int _,n;
int maxn[N];
struct node
{
	int a,b;
}a[N];

bool cmp(node x,node y)
{
	return x.a==y.a?abs(x.a-x.b)<abs(y.a-y.b):x.a<y.a;
}

int main()
{
	scanf("%d",&_);
	while(_--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&a[i].a,&a[i].b);
		}
		sort(a+1,a+n+1,cmp);
		int now=-1e9;
		for(int i=n,j=n;i>=1;i=j-1,j=i)
		{
			int ret=now;
			while(a[j-1].a==a[i].a&&j>1)
			{
				maxn[j]=ret;
				now=max(now,a[j].b);
				j--;
			}
			maxn[j]=ret;
			now=max(now,a[j].b);
		}
		int ans=2e9;
		set<int> s;
		s.clear();
		for(int i=1;i<=n;i++)
		{
			ans=min(ans,abs(maxn[i]-a[i].a));
			if(maxn[i]<a[i].a)
			{
				auto it=s.lower_bound(a[i].a);
				if(it!=s.end())ans=min(ans,abs(*it-a[i].a));
				if(it!=s.begin())--it,ans=min(ans,abs(*it-a[i].a));
			}
			s.insert(a[i].b);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：chlchl (赞：4)

upd on 2023.4.11：博客界面好像炸掉了，改一下。

挺不错的一道题，CF 评分 1800，感觉**绿**刚刚好。

因为你谷日爆没法交（UKE 了），给出 CF 的 [AC 链接](https://codeforces.com/contest/1802/submission/197849507)。

这篇题解主要讲的是一些细节（包括作者一直 WA 的原因）。

## 题意简述
有 $n$ 个商店，在第 $i$ 个商店给第一个、第二个朋友买礼物分别花费 $a_i,b_i$。每个商店都必须且仅能给一个朋友买礼物。

要求输出给两个朋友最贵礼物的最小价值差。

## Solution
$n\leq 500000$，大概是个 $O(n\log n)$ 的算法。

考虑先按 $a$ 从大到小排序，然后分别枚举每个 $a_i$ 作为最贵礼物时的最小差值。

然后你会发现它分成了两个部分：
- $j<i$，此时 $a_j\geq a_i$，在这些商店必须给另一个人买（不然 $a_i$ 不是最大值），所以可以预处理出一个前缀 $b$ 的最大值 $mx_i$，这部分的差值就是 $|a_i-mx_i|$。
- $j>i$，此时 $a_j\leq a_i$。此时如果 $mx_i<a_i$，我们求出这一段后缀区间内的前驱后继，然后分别作差取最小值。这个在其他大佬的讲解中非常清晰，故不再赘述。

第一部分可以预处理，$O(n)$；第二部分可以用一个 `set` 在线维护，每求一个就放进去一个，时间复杂度 $O(n\log n)$。

然后讲一下一些实现的细节，提供几组 hack 数据。

- 求 $mx$ 的时候，$a_i$ 会有相等的情况。这种情况是不能算进 $mx$ 里的，因为 $mx$ 里的数必须买 $b$，但是 $a_i$ 相等的情况下买 $a$ 也不会使最大值有变化，它应该属于后半部分。

hack 数据：

```
输入：
1
5
3 1
2 5
2 4
2 3
1 2

输出：0
```

- 排序的时候需要加入**第二关键字**。若 $a_i$ 相等，$|a_i-b_i|$ 较大的应该排在前面。因为我们是从后往前走的，这样可以保证最后去到的差值最小。举个例子：

```
输入：
1
2
0 0
0 1

输出：0
错误输出：1
```

因为 `sort` 是不稳定的，它有可能排成 `0 0`、`0 1`。这个时候，在原来第二个商店买东西的时候，它不知道第一个商店能够使差更小（`set` 中还没有插入 $0$）；在第一个商店买的时候，因为不能选自己，所以它会选择 $1$，算出来的答案就是 $1$。

注意以上两点基本上就过了，代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 5e5 + 10;
int T, n;
ll mx[N];
set<ll> mn;
struct store{
	ll a, b;
	bool operator < (const store &p) const {
		if(a != p.a)
			return a > p.a;
		return abs(a - b) > abs(p.a - p.b);
	}
} s[N];

int main(){
	scanf("%d", &T);
	while(T--){
		mn.clear();
		memset(mx, 0, sizeof(mx));//多测清空，别忘了 
		scanf("%d", &n);
		for(int i=1;i<=n;i++)
			scanf("%lld%lld", &s[i].a, &s[i].b);
		sort(s + 1, s + 1 + n);
		ll now = -1e18;//前缀最大值 
		for(int i=1,j=1;i<=n;i=j+1,j=i){//双指针求 mx 
			ll tmp = now;
			while(s[j + 1].a == s[i].a && j < n){//等于的话，是不能算进大于里面的 
				mx[j] = tmp;
				now = max(now, s[j].b);
				j++;
			}
			mx[j] = tmp;
			now = max(now, s[j].b);
		}
		ll res = 1e18;
		for(int i=n;i>=1;i--){
			res = min(res, abs(mx[i] - s[i].a));
			auto it = mn.lower_bound(s[i].a);
			if(s[i].a > mx[i]){
				if(it != mn.end())
					res = min(res, abs(*it - s[i].a));
				if(it != mn.begin())
					--it, res = min(res, abs(*it - s[i].a));
			}
			mn.insert(s[i].b);
		}
		printf("%lld\n", res);
	}
	return 0;
}
/*赠送一组 hack 数据
输入：
1
2
0 1
1 1
输出：0
*/
```



---

## 作者：zac2010 (赞：3)

简单思路和段代码的合集，考试时硬是没调出来。

这题是一个枚举、预处理和二分结合。我们考虑枚举给第二个人买的最贵的礼物。那么我们可以把所有部门按照 $a_i$ 排序后做一个 $b_i$ 的后缀最大值（假设当前 $a_i$ 作为最大值，大于当前 $a_i$ 的一律得选 $b_i$ 那一维，故而为了判断而做后缀最大值），用 $mx_i$ 记录，那么枚举时只要通过二分查找找到最左边的可以作为最大 $a_i$ 的位置，然后在范围内亦是通过二分去查询当前最优值，尝试去更新答案即可。

时间复杂度 $O(n \log n)$ 级别，带有二分的小常数。

[代码](https://codeforces.com/contest/1802/submission/196729009)。

---

## 作者：六楼溜刘 (赞：2)

## 题意
- 有两个长度为整数 $n$ 的序列 $a_1,a_2,\dots,a_n$ 和 $b_1,b_2,\dots,b_n$。
- 对于 $1 \leq i \leq n$，你可以选择 $a_i$ 或 $b_i$。
- 你要最小化选择的 $a_i$ 中的最大值与 $b_i$ 的最大值之差的绝对值。
- 多组测试数据，$1 \leq n \leq 5 \times 10^5$。

## 题解
看到这个数据规模，容易想到要用 $O(n \log n)$ 的做法，我们考虑枚举每个 $a_i$ 是最大值的情况查找一个合适的 $b_i$ 作为最大值。

首先，为了保证枚举的 $a_i$ 是最大值，我们先把两个序列放在一起按照 $a_i$ 升序排列，每次选择一个 $a_i$ 时，在它后面的 $b_i$ 全都要选，我们可以用一个后缀最大值维护这个东西（其实方法很多，比如我们机房某大佬用了一个堆）。

然后对于当前 $a_i$ 前面的 $b_i$，我们可以随意选择而不影响 $a_i$ 是最大值，我们可以把它压进一个 `multiset` 里面，二分查找最合适的 $b_i$，然后与后缀最大值比较，如果比后缀最大值更大就说明这是一个合法的解。

需要注意，边界需要额外判断，如果后缀最大值的边界定义成 $0$ 就可能被精心构造的数据卡掉（指 text 69，我们整个初三都挂在这个数据上了），所以我们可以特判一下边界，或者索性定义成负无穷。
## code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define mem(a,b) memset(a,b,sizeof(a))
#include<string>
#include<cmath>
#include<set>
using namespace std;
typedef pair<int,int> pii;
const int N=5e5+5,inf=0x3f3f3f3f;
int t,n,ans,suf[N];
pii gft[N];
multiset<int> s;
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		ans=inf;s.clear();
		for(int i=1;i<=n;i++){
			scanf("%d %d",&gft[i].first,&gft[i].second);
		}
		suf[n+1]=-inf;//边界定义成负无穷
		sort(gft+1,gft+n+1);
		for(int i=n;i>=1;i--){
			suf[i]=max(suf[i+1],gft[i].second);
		}
		for(int i=1;i<=n;i++){
			ans=min(ans,abs(gft[i].first-suf[i+1]));
			if(gft[i].first>suf[i+1]){
				set<int>::iterator it=s.lower_bound(gft[i].first),jt=it;
//二分查找最佳的 b[i]。
//如果当前的 a[i] 已经比后缀小了，那么不可能有更优解，就不必再查找了。
				if(it!=s.end()){
					if(*it>suf[i+1]) ans=min(ans,abs(gft[i].first-*it));
					if(it!=s.begin()){
						jt--;
						if(*jt>suf[i+1]) ans=min(ans,abs(gft[i].first-*jt));
					}
				}else{
					if(s.size()>0&&*s.rbegin()>suf[i+1]) ans=min(ans,abs(gft[i].first-*s.rbegin()));
				}
			}
			s.insert(gft[i].second);
			if(ans==0) break;
//如果差为 0，不可能有更优解，可以直接跳出循环
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：Xttttr (赞：2)

## CF1801B题解

[传送门](https://www.luogu.com.cn/problem/CF1801B)

[更好的阅读体验](https://www.cnblogs.com/Xttttr/p/17203514.html)

简化题意：有 $n$ 个商店，每个商店卖 $a,b$ 两种商品，价格分别为 $a_i,b_i$，你需要在每个商店买一个商品，并且不能在所有商店都买同一种商品，最小化买的最贵的 $a$ 商品和买的最贵的 $b$ 商品的价格差的绝对值。

思路：首先观察到数据范围是 $n\leqslant5\times10^5$，也是就感觉像个贪心，于是就考虑枚举某一种商品的最大值然后计算答案。我们不妨枚举买的 $a$ 商品的最大值。我们将所有商店按 $a_i$ 从大到小排序，钦定当前的 $a_i$ 为 $a$ 商品的最大值，我们发现这时有 $2$ 类 $b$。首先是满足 $a_j>a_i$ 的 $b_j$，接着是所有满足 $a_j\leqslant a_i$ 的 $b_j$。对于第一类，它们是必须选的，我们记最大值为 $maxb$ 。对于第二类，会做贡献的肯定是最大的小于等于 $a_i$ 的 $b_j$ 和最小的大于等于 $a_i$ 的 $b_j$，记为 $maxl$ 和 $minr$，需注意的是如果没有其他的 $a_j=a_i$，那不能算上对应的 $b_j$ 的贡献。同时，因为 $maxl,minr$ 最多只会有一个被选，那么我们也无需担心我们没有购买任何一个 $a$ 商品。

然后我们考虑如何计算答案。首先，如果 $maxb\geqslant a_i$，这时无论怎么买答案都不会小于 $maxb-a_i$，于是可以直接更新答案。如果 $maxb<a_i$ 那么当前答案就是 $\min(a_i-maxl,minr-a_i)$，再更新答案即可。

代码实现的时候，因为是从大到小考虑 $a_i$，那么 $maxb$ 显然可以直接维护，然后对于 $a_j=a_i$ 的部分可以直接扫一遍，剩下部分的可以考虑用 multiset 来查前驱后继，这样就做完了。时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

代码：
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int s=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')s=s*10+(ch^48),ch=getchar();
    return s;
}
const int N=500501;
int T,n;
struct node{
    int a,b;
}t[N];
multiset<int>s;
inline bool cmp(node a,node b){
    return a.a<b.a;
}
int main(){
    T=read();
    while(T--){
        s.clear();
        n=read();
        for(int i=1;i<=n;i++)t[i].a=read(),t[i].b=read(),s.insert(t[i].b);
        sort(t+1,t+n+1,cmp);
        int maxn=-1e9,ans=1e9;
        t[n+1].a=t[0].a=-1;
        for(int i=n;i>=1;i--){
            if(t[i].a==t[i+1].a)continue;
            int j=i;
            while(t[j-1].a==t[i].a)j--;
            if(maxn>=t[i].a){
                ans=min(ans,maxn-t[i].a);
                break;
            }
            int cur,maxl=-1e9,minr=2e9+1;
            for(int k=j;k<=i;k++){
                s.erase(s.find(t[k].b));
            }
            if(j!=i){
                for(int k=j;k<=i;k++){
                    if(t[k].b<=t[i].a&&t[k].b>maxl)maxl=t[k].b;
                    if(t[k].b>t[i].a&&t[k].b<minr)minr=t[k].b;
                }
            }
            if(s.size()){
                set<int>::iterator it=s.lower_bound(t[i].a);
                if(it!=s.end()){
                    minr=min(minr,*it);
                }
                if(it!=s.begin())it--,maxl=max(maxl,*it);
            }
            maxl=max(maxl,maxn);
            cur=min(t[i].a-maxl,minr-t[i].a);
            ans=min(ans,cur);
            for(int k=j;k<=i;k++)maxn=max(maxn,t[k].b);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：hereiszd (赞：1)


不知道为什么和 THUPC 的那道众数这么像。

## 题意简述

有长度为 $n$ 的数列 $a_n,b_n$ ，对于每个位置 $i$，我们只能选择 $a_i$ **或** $b_i$ ，求选择的 $|a_{max}-b_{max}|$。$(1\le n \le 5\times 10^5)$

## 题意分析

我们有一个显然的 $\Theta(2^n)$ 的暴力，考虑优化这个暴力。

因为 $a_i$ 和 $b_i$ 同时对答案产生了贡献，我们不妨固定一个数列的贡献，具体地，我们枚举每一位 $i$，钦定 $a_i$ 为 $a$ 中做贡献的元素，即 **这个数是选中的 $a$ 的最大值**。

那么现在有两类位置，第一类位置 $p_1$ 是 $a_{p_1}$ 比 $a_i$ 小的，我们发现这些位置无论是选 $a$ 还是 $b$ 都没有影响，那我们就选 $|a-b|_{min}$ ；第二类位置 $p_2$ 是 $a_{p_2} 比 a_i$ 大的，这些位置中我们只能选 $b$ ，即 $|a-b|$ 已经确定。

这两种情况取最小的值就是 $a_i$ 为 $a_{max}$ 时的最小值，循环一遍就可以得到最后的答案，总的时间复杂度是 $\Theta(n\log n)$。

## 代码时间

代码使用 `std::set` 实现细节，注意判断是否是开头和结尾元素。

```cpp
/*
	Author:zd
	Status:Accept
	note: 去掉了快读和缺省源
*/

#define int long long

int n,m,k;

signed main(){
	mul();
	return 0;
}

//数组开大了没有 ？开不开 long long ？多测清空了吗 ？
int a[N],b[N],mb[N];
set<int>s;
struct node{
	int a,b;
}f[N];
bool cmp(node x,node y){
	return x.a<y.a;
}
void solve(){
	read(n);
	for(int i=1;i<=n+10;i++)mb[i]=0;//清空多清一点，没有坏处
	s.clear();
	for(int i=1;i<=n;i++){
		read(f[i].a,f[i].b);
	}
	sort(f+1,f+1+n,cmp);
	for(int i=n;i>=1;i--){
		mb[i]=max(mb[i+1],f[i].b);
	}
	mb[n+1]=-1;
	int ans=1e12;
	s.insert(-LINF);
	for(int i=1;i<=n;i++){
		int tmp1=-1,tmp2=-1;
		//求 1<j<i中 |ai-bj| 的最小值
		if(!s.empty()){
			auto it=s.lower_bound(f[i].a);
			auto itt=prev(it);
			if(it!=s.begin())tmp1=*itt;
			if(it!=s.end())tmp2=*it;//特判防止越界
			tmp1=max(tmp1,mb[i+1]);tmp2=max(tmp2,mb[i+1]);
			if(tmp1==-1)tmp1=INF;if(tmp2==-1)tmp2=INF;
		}
		ans=min(ans,min(abs(f[i].a-tmp1),abs(f[i].a-tmp2)));
		s.insert(f[i].b);
	}
	writeh(ans);
}


```

---

## 作者：__vector__ (赞：0)

纪念一下第一次比赛状态搞出 Div.2 ABCD 正解，虽然只是 vp。  
## 题解  
设第一个朋友为小 $a$，第二个为小 $b$。  

很自然地想到枚举小 $a$ 得到的最贵礼品的价值。  

于是先将卖部按照 $a_i$ 值升序排列。  

然后枚举小 $a$ 得到的最贵礼品所在的卖部，设当前枚举到第 $i$ 个卖部。  

显然，$a$ 值大于 $a_i$ 的所有卖部必须卖给小 $b$。  

而 $a$ 值小于等于 $a_i$ 的所有卖部，除了当前卖部 $i$，都可以自由选择卖给小 $a$ 还是小 $b$。  

为了让卖给小 $b$ 的最大价值最接近小 $a$ 得到的最大价值即 $a_i$，应尽可能让卖给小 $b$ 的最大价值等于 $a_i$ 在所有可以自由选择卖给谁的卖部的 $b$ 数组中的前驱或后继。  

$a$ 值大于 $a_i$ 的所有卖部都必须卖给小 $b$，这个改变不了，所以就在所有可以自由选择卖给谁的卖部的 $b$ 数组里面选择 $a_i$ 的前驱，后继分别作为可以自由卖的卖部中卖给小 $b$ 的最大值，分别取最优值。  

如果做到这一步结束了，并且是在赛时，那么恭喜你 FST 了。  

还有一种可能，那就是只选择 $a$ 值大于 $a_i$ 的卖部卖给小 $b$，也就是可以自由卖的全都给小 $a$。  

就这个东西让我 vp 的时候吃了 5 次罚时。  

细节比较多。  

[CF 提交记录](https://codeforces.com/contest/1802/submission/198715687)

---

