# Bakery

## 题目描述

Monocarp would like to open a bakery in his local area. But, at first, he should figure out whether he can compete with other shops.

Monocarp plans that the bakery will work for $ n $ days. On the $ i $ -th day, $ a_i $ loaves of bread will be baked in the morning before the opening. At the end of the $ n $ -th day, Monocarp will sell all the remaining bread that wasn't sold earlier with a huge discount.

Because of how bread is stored, the bakery seller sells the bread in the following order: firstly, he sells the loaves that were baked that morning; secondly, he sells the loaves that were baked the day before and weren't sold yet; then the loaves that were baked two days before and weren't sold yet, and so on. That's why some customers may buy a rather stale bread and will definitely spread negative rumors.

Let's define loaf spoilage as the difference between the day it was baked and the day it was sold. Then the unattractiveness of the bakery will be equal to the maximum spoilage among all loaves of bread baked at the bakery.

Suppose Monocarp's local area has consumer demand equal to $ k $ , it means that each day $ k $ customers will come to the bakery and each of them will ask for one loaf of bread (the loaves are sold according to the aforementioned order). If there is no bread left, then the person just doesn't buy anything. During the last day sale, all the remaining loaves will be sold (and they will still count in the calculation of the unattractiveness).

Monocarp analyzed his competitors' data and came up with $ m $ possible consumer demand values $ k_1, k_2, \dots, k_m $ , and now he'd like to calculate the unattractiveness of the bakery for each value of demand. Can you help him?

## 说明/提示

In the first example, let's describe what happens for couple consumer demands:

If consumer demand is equal to $ 1 $ :

- at day $ 1 $ : $ 5 $ loaves are baked and only $ 1 $ is sold with spoilage equal to $ 1 - 1 = 0 $ ;
- at day $ 2 $ : $ 4 $ loaves are left and $ 2 $ more are baked. Only $ 1 $ loaf was sold and it was the loaf baked today with spoilage $ 2 - 2 = 0 $ ;
- at day $ 3 $ : $ 4 $ loaves from the first day and $ 1 $ loaf from the second day left. One more loaf was baked and was sold this day with spoilage $ 3 - 3 = 0 $ ;
- at day $ 4 $ : $ 4 $ loaves from the first day and $ 1 $ loaf from the second day left. $ 3 $ more loaves were baked and one of them was sold this day with spoilage $ 4 - 4 = 0 $ ;
- at day $ 5 $ : $ 4 $ loaves from the first day, $ 1 $ loaf from the second day and $ 2 $ loaves from the fourth day left. $ 7 $ more loaves were baked and, since it's the last day, all $ 14 $ loaves were sold. $ 4 $ loaves from the first day have the maximum spoilage equal to $ 5 - 1 = 4 $ .

 In total, the unattractiveness of the bakery will be equal to $ 4 $ .If consumer demand is equal to $ 10 $ then all baked bread will be sold in the day it was baked and will have spoilage equal to $ 0 $ .

## 样例 #1

### 输入

```
5 4
5 2 1 3 7
1 3 4 10```

### 输出

```
4 2 1 0```

## 样例 #2

### 输入

```
8 9
3 1 4 1 5 9 2 6
1 2 3 4 5 6 7 8 9```

### 输出

```
7 5 3 3 2 1 1 1 0```

# 题解

## 作者：zhimao (赞：5)

不得不说官方做法太巧妙了 。

显然暴力模拟不可取 ， 似乎也无法优化模拟 。于是我们考虑瞎搞 ：询问中 k 是递增的 。 这提示我们离线解决问题 。显然当 $k$ 为 $10^9$ 时 ， 当天的面包一定当天卖出 ， 当 $k$ 逐渐减小 ， 就可能出现某一天卖不完当天面包  ，要合并到后一天卖，当然也可能还要合并到后天或者直接大促销了 ， $k$ 不断减小 ， 日子不断合并 ， 最多只会合并 $n-1$ 次 。于是我们倒着做 ， 每次检查是否有块可合并 ：记录块的三个属性 : 总面包数 $x$ ，连起来的天数 $y$ ， 最后是哪一天 $z$ 。 则只要 $x>y\times k$ ， 则此块要与 $z+1$ 天所属块合在一起 ，如果 $z=n$ 则会大促销 ， 不用管它 。
 
 具体实现可用 $set$ 和并查集 。
 
 代码
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans[1000000],fa[1000000],c[1000000];
long long a[1000000],b[1000000];
struct cmp
{
	bool operator()(int x,int y)
	{
		return a[x]*c[y]!=a[y]*c[x]?a[x]*c[y]>a[y]*c[x]:x<y;
	}
};
set<int,cmp> s1;
multiset<int> s2;
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++)
	{
		c[i]=1;
		fa[i]=i;
		s1.insert(i);
		s2.insert(-1);
	}
	for(int i=m;i;i--)
	{
		while(s1.size())
		{
			int x=*s1.begin();
			if(c[x]*b[i]>=a[x]) break;
			s1.erase(x);
			s2.erase(s2.find(-c[x]));
			int p=find(x+1);
			if(p)
			{
				s1.erase(p);
				s2.erase(s2.find(-c[p]));
				c[p]+=c[x];
				a[p]+=a[x];
				s1.insert(p);
				s2.insert(-c[p]);
			}
			else c[n+1]+=c[x];
			fa[x]=p;
		}
		ans[i]=max(c[n+1],-(*s2.begin()))-1;
	}
	for(int i=1;i<=m;i++) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：Fido_Puppy (赞：1)

## 一、题目链接

<https://www.luogu.com.cn/problem/CF1468B>

<https://codeforces.com/contest/1468/problem/B>

## 二、题解

先考虑给定一个 $k$ 怎么做。

假设在第 $x$ 天面包会被顾客买完，那我们称第 $x$ 天为清空点，否则称第 $x$ 天为普通点。

第 $0$ 天和第 $n$ 天永远是清空点，我们将所有清空点串起来，可以得到一条链。

![](https://cdn.luogu.com.cn/upload/image_hosting/jrdue0sn.png)

其中黑色的为普通点，红色的为清空点。

容易发现答案就是链上相邻的清空点之间差减 $1$ 的最大值。

举个例子，当遇到第 $4$ 天清空时，由于之前第 $2$ 天的时候面包被清空了，所以没有第 $2$ 天及以前的面包了，但是由于在 $(2, 4)$ 之间没有清空过，所以第 $3$ 天的面包一定是一直在的，所以贡献就是 $4 - (2 + 1) = 1$。

并且在普通点对答案的贡献一定是不优的，所以上述结论成立。

考虑怎么判断一个点是否为清空点。

以第 $4$ 天为例，容易发现充要条件为：

$$a_4 \le k, a_4 + a_3 \le 2k, a_4 + a_3 + a_2 \le 3k, a_4 + a_3 + a_2 + a_1 \le 4k$$

即对于第 $x$ 天，其为清空点的充要条件为：

$$\forall 1 \le y \le x, \sum_{i = y} ^ x a_i \le (x - y + 1) \cdot k$$

那么就可以对一个 $k$ 做到 $\Theta(n)$ 求出答案。

但是现在有多个 $k$，通过观察能够发现对于一个点 $x$，存在一个限制 $L$，使得当 $k \ge L$ 时 $x$ 为清空点，当 $k < L$ 时 $x$ 为普通点。

考虑如何对每个点求出其限制 $L$。

设 $a$ 数组的前缀和为 $s$。

容易发现对第 $x$ 天：

$$L = \max_{i = 0}^{x - 1}\left(\dfrac{s_x - s_i}{x - i}\right)$$

最后对 $L$ 上取整。

那么发现这个式子很像斜率的式子，考虑将所有 $(i, s_i)$ 放到平面直角坐标系上。

从前往后扫，维护一个下凸壳，能够 $\Theta(n)$ 求出所有点的限制 $L$。

接着考虑计算答案，可以将所有限制 $L$ 从大到小排序，将询问的 $k$ 也从大到小排序。

然后双指针，即刚开始我们认为所有点都是清空点，每次将一些清空点变成普通点，维护答案。

使用链表维护即可。

最终时间复杂度 $\Theta(n \log n)$，使用基数排序即可做到 $\Theta(n)$。

## 三、代码链接

<https://codeforces.com/contest/1468/submission/234356412>

---

## 作者：sunkuangzheng (赞：0)

注意到我们永远卖的是最新做好的面包，因此任意时刻我们都只关心当前时刻最早做好的面包，而只有在清空了当前所有面包的时候才会使得这个时刻发生改变。

我们称一个导致背包清空的位置是 _关键位置_，答案就是相邻关键位置距离的最大值，因此问题转化为动态维护这些关键位置。

- 观察 A：$k$ 时刻的关键位置集合是 $k+1$ 时刻的子集。
   - 证明比较显然：考虑 $k$ 时刻两个相邻的关键位置 $x,y$，假设它们在 $x$ 在 $k+1$ 时刻存在。如果 $z \in [x+1,y-1]$ 在 $k+1$ 时刻是关键位置，那么只会导致后面清空的更早，所以 $y$ 以前一定还存在关键位置；可以推出 $y$ 一定是关键位置。
- 观察 B：我们只关心距离最远的两个相邻关键位置。
  - 因此每次 $k$ 变化时，我们暂时不用考虑其它线段，只需要考虑最大的那个中间有没有出现新的关键点。

类似超级钢琴的，用一个堆维护所有线段，每次取出长度最大的断成两段。问题转化为，给定 $k$，怎么快速判断 $[l,r]$ 内是否存在关键位置？

不难发现 $1 \sim k$ 的每个时刻区间内所有元素都被减 $1$。其实我们就是在判断，是否存在 $i \in [l,r]$ 满足 $\sum\limits_{j=l}^i a_j - k \le 0$，即区间最小前缀和。把它直接写成前缀和的形式，即 $sm_j - kj$ 的最小值，发现这是一个一次函数，线段树套李超树维护即可。

时间复杂度 $\mathcal O(n \log^2 n)$，可以通过。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 23.11.2024 16:39:45
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 2e5+5;
using namespace std;
int T,n,m,a[N],k; priority_queue<tuple<int,int,int>> q; ll sm[N];
ll get(int i,int x){return !i ? 1e18 : sm[i] - 1ll * i * x;}
int cmp(int i,int j,int x){return get(i,x) < get(j,x) ? i : j;}
struct LCT{
    int mn[N*60],tot,rt[N*4],ls[N*60],rs[N*60];
    void upd(int &s,int l,int r,int x){
        if(!s) s = ++tot; int mid = (l + r) / 2;
        if(!mn[s]) return mn[s] = x,void();
        if(get(x,mid) < get(mn[s],mid)) swap(x,mn[s]);
        if(get(x,l) < get(mn[s],l)) upd(ls[s],l,mid,x);
        else if(get(x,r) < get(mn[s],r)) upd(rs[s],mid+1,r,x);
    }int qry(int s,int l,int r,int x){
        if(!mn[s]) return 0; if(l == r) return mn[s];
        int mid = (l + r) / 2;
        return x <= mid ? cmp(qry(ls[s],l,mid,x),mn[s],x) : cmp(qry(rs[s],mid+1,r,x),mn[s],x);
    }
}t;
void build(int s,int l,int r){
    for(int i = l;i <= r;i ++) t.upd(t.rt[s],1,1e9,i);     
    if(l == r) return ; int mid = (l + r) / 2;
    build(s*2,l,mid),build(s*2+1,mid+1,r);
}int qry(int s,int l,int r,int ql,int qr,int k){
    if(ql <= l && r <= qr) return t.qry(t.rt[s],1,1e9,k);
    int mid = (l + r) / 2,pos = 0;
    if(ql <= mid) pos = cmp(pos,qry(s*2,l,mid,ql,qr,k),k);
    if(qr > mid) pos = cmp(pos,qry(s*2+1,mid+1,r,ql,qr,k),k);
    return pos;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m; q.emplace(n,1,n);
    for(int i = 1;i <= n;i ++) cin >> a[i],sm[i] = sm[i - 1] + a[i]; build(1,1,n);
    while(m --){
        cin >> k; int ans = 0;
        while(q.size()){
            auto [len,x,y] = q.top(); q.pop(); int pos = 0;
            if(x != y) pos = qry(1,1,n,x,y - 1,k); 
            ll sm = ::sm[pos] - ::sm[x - 1] - 1ll * k * (pos - x + 1);
            if(pos && sm <= 0){
                q.emplace(pos - x + 1,x,pos),q.emplace(y - pos,pos + 1,y);
            }else{
                q.emplace(len,x,y),ans = len - 1; break;
            }
        }cout << ans << " ";
    }
}
```

---

