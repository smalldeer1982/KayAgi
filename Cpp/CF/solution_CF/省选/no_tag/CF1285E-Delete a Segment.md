# Delete a Segment

## 题目描述

There are $ n $ segments on a $ Ox $ axis $ [l_1, r_1] $ , $ [l_2, r_2] $ , ..., $ [l_n, r_n] $ . Segment $ [l, r] $ covers all points from $ l $ to $ r $ inclusive, so all $ x $ such that $ l \le x \le r $ .

Segments can be placed arbitrarily — be inside each other, coincide and so on. Segments can degenerate into points, that is $ l_i=r_i $ is possible.

Union of the set of segments is such a set of segments which covers exactly the same set of points as the original set. For example:

- if $ n=3 $ and there are segments $ [3, 6] $ , $ [100, 100] $ , $ [5, 8] $ then their union is $ 2 $ segments: $ [3, 8] $ and $ [100, 100] $ ;
- if $ n=5 $ and there are segments $ [1, 2] $ , $ [2, 3] $ , $ [4, 5] $ , $ [4, 6] $ , $ [6, 6] $ then their union is $ 2 $ segments: $ [1, 3] $ and $ [4, 6] $ .

Obviously, union is a set of pairwise non-intersecting segments.

You are asked to erase exactly one segment of the given $ n $ so that the number of segments in the union of the rest $ n-1 $ segments is maximum possible.

For example, if $ n=4 $ and there are segments $ [1, 4] $ , $ [2, 3] $ , $ [3, 6] $ , $ [5, 7] $ , then:

- erasing the first segment will lead to $ [2, 3] $ , $ [3, 6] $ , $ [5, 7] $ remaining, which have $ 1 $ segment in their union;
- erasing the second segment will lead to $ [1, 4] $ , $ [3, 6] $ , $ [5, 7] $ remaining, which have $ 1 $ segment in their union;
- erasing the third segment will lead to $ [1, 4] $ , $ [2, 3] $ , $ [5, 7] $ remaining, which have $ 2 $ segments in their union;
- erasing the fourth segment will lead to $ [1, 4] $ , $ [2, 3] $ , $ [3, 6] $ remaining, which have $ 1 $ segment in their union.

Thus, you are required to erase the third segment to get answer $ 2 $ .

Write a program that will find the maximum number of segments in the union of $ n-1 $ segments if you erase any of the given $ n $ segments.

Note that if there are multiple equal segments in the given set, then you can erase only one of them anyway. So the set after erasing will have exactly $ n-1 $ segments.

## 样例 #1

### 输入

```
3
4
1 4
2 3
3 6
5 7
3
5 5
5 5
5 5
6
3 3
1 1
5 5
1 5
2 2
4 4```

### 输出

```
2
1
5```

# 题解

## 作者：syksykCCC (赞：22)

看到负数，首先考虑 **离散化**，然后就很自然地想到用 $d_i$ 来表示坐标（离散化后）为 $i$ 的点被几条线段覆盖，然后姑且不说删去一条线段，就是原线段集的 _并集_ 怎么求呢？

画个图看看（图中为了防止线段重叠将线段进行了竖直平移，一条线段的实际覆盖区域即为其竖直投影）：

![image.png](https://i.loli.net/2020/01/13/9w382IzSYV7UsBR.png)

简单！连续非零段的个数就是 _并集_ 大小！

真的是这样吗？

![image.png](https://i.loli.net/2020/01/13/OzRW4nKr1ixvPuH.png)

似乎……不太对？

于是就有了一种神仙的方法：既然我们的标号都在点上，第二张图不能很好处理，那么，我们给边也来个 $d$！

怎么实现呢？只要把所有的 $l_i, r_i$ 都 $\times 2$ 即可！

于是我们就能很好地处理了：

![image.png](https://i.loli.net/2020/01/13/NEWRaBZYhSv3QUt.png)

那么 $\mathcal O(n^2)$ 的做法就呼之欲出了：删去线段 $i$ 时，就把 $[l_i, r_i]$ 的 $d$ 都减去 $1$，然后重新统计一遍求最大值！

显然是过不了的，还需要优化。

把 $[l_i, r_i]$ 的 $d$ 都减去 $1$ 后，有能力成为新的空段的条件，显然是 $d = 1$，我们不妨大胆的假设一下，$[l_i, r_i]$ 中 $d = 1$ 的连续段数（显然这里的 $d$ 不会为 $0$，至少有线段 $i$ 覆盖呢），就是删去线段 $i$ 后 **新增的段数**。

试一下？

![image.png](https://i.loli.net/2020/01/13/xHsFXQk3uJnv1oI.png)

好像是对的？

那要是这样呢？

![image.png](https://i.loli.net/2020/01/13/pFl1gfciCO3S4h6.png)

可是显然答案是增加 $1$，而不是增加 $2$ 呀？

再举个最简单的例子：

![image.png](https://i.loli.net/2020/01/13/qoxQs4fzLDtWeUO.png)

这时，显然答案是减去 $1$ 了，而不是离谱地增加 $1$。（虽然 $n \ge 2$，但这里姑且认为那个 $l$ 和 $r$ 非常大）

发现了什么？当新增段和 $l_i$ 相通时，答案要 $-1$，和 $r_i$ 相通时也要 $-1$，实现上只要判断一下 $d_{l_i}$ 和 $d_{r_i}$ 是不是等于 $1$ 就好了。

然后怎么求新增段呢？很简单，把每一个连续 $1$ 段的最左边的 $d' + 1$，最右边的 $d' + 1$，我们就可以用 $\left \lfloor \dfrac{\sum_{i = l}^{r} d'_i}{2} \right \rfloor $ 来计算段数了（想一想，为什么？），如果加上前缀和优化，那么去掉 $\mathcal O(n \log n)$ 的离散化，代码就是 $\mathcal O(n)$ 的了。

下面是一个直观的演示：

![image.png](https://i.loli.net/2020/01/13/THJ4nb1uMFYr6CQ.png)

代码贴出，仅供参考。（代码中用 `d_` 来表示 $d'$）

```cpp
#include <bits/stdc++.h>
#define REP(i, x, y) for(register int i = x; i <= y; i++)
using namespace std;
typedef long long LL;
const int N = 2e5 + 5;
struct segment { LL l, r; } s[N];
int n;
LL ans0, ans1, tmp[N << 1], d_[N << 2], d[N << 2];
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--)
	{
		ans0 = 0; ans1 = INT_MIN;
		cin >> n;
		REP(i, 1, n)
		{
			cin >> s[i].l >> s[i].r;
			tmp[(i << 1) - 1] = s[i].l;
			tmp[i << 1] = s[i].r;
		}
		sort(tmp + 1, tmp + (n << 1) + 1);
		int tot = unique(tmp + 1, tmp + (n << 1) + 1) - tmp - 1;
		REP(i, 1, n)
		{
			s[i].l = lower_bound(tmp + 1, tmp + tot + 1, s[i].l) - tmp;
			s[i].r = lower_bound(tmp + 1, tmp + tot + 1, s[i].r) - tmp;
			s[i].l <<= 1LL; s[i].r <<= 1LL; 
			d[s[i].l]++; d[s[i].r + 1]--; // 差分算原始数组 
		}
		tot <<= 1LL;
		REP(i, 1, tot + 5) d[i] += d[i - 1];
		REP(i, 0, tot + 5) ans0 += d[i] && !d[i + 1];
		REP(i, 0, tot + 4) if(d[i] == 1 && d[i + 1] != 1) d_[i]++;
		REP(i, 1, tot + 5) if(d[i] == 1 && d[i - 1] != 1) d_[i]++;
		REP(i, 1, tot + 5) d_[i] += d_[i - 1]; // d_[] 上前缀和 
		REP(i, 1, n)
		{
			LL t = (d_[s[i].r] - d_[s[i].l - 1]) / 2; 
			t -= (d[s[i].r] == 1) + (d[s[i].l] == 1);
			ans1 = max(ans1, t);
		}
		cout << ans0 + ans1 << endl; // 初始答案加上新增答案 
		REP(i, 0, tot + 10) d[i] = d_[i] = 0; // 用多少清多少，避免 memset 浪费时间 
	}
	return 0;
}
```

---

## 作者：OMG_wc (赞：7)

讲一种最简单的方法，不需要复杂的数据结构，只需`set`即可。

先来看一种极端的情况

![](https://s2.ax1x.com/2020/01/24/1VHx39.jpg)

如上图所示，一共四条黑色线段，显然我们去掉那条最长线段，就能得到三个区域，所以答案是3。

那么为什么去掉是这条长线段呢？

为了区别段和原题中的线段，把段称谓**部位**。我们发现这条长线段的四个红色部位是它自己独占的，而三条短线段根本没有独占的部位。

而这四个部位中头尾两个其实是无效的，真正带来贡献的是中间两个独占的部位。我们可以这样计算，一条都不删时的区域数量是1，加上所有线段中最大的有效独占部位数2，就是最终答案 3。


具体的做法是：把题中 n 个线段转成 2n 个事件，然后按坐标排序（要保证同一个位置的起点比终点先）。然后遍历这些事件，统计以每个位置为起点那个部位是否独占，详情见代码里的注释。



```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 200005;

pair<int, int> a[N * 2];  //first 为事件的坐标，second 为线段编号（负数表示起点，正数表示终点，因为排序要保证先考虑起点）
int cnt[N];               // 统计每个线段中 自己独占的部位数量（排除两端边界外）
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int n, m = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            a[m++] = {x, -i};
            a[m++] = {y, i};
        }
        sort(a, a + m);
        set<int> se;  //储存包含当前考虑的部位的线段编号
        int ans = 0;  // 统计空隙数量，包括最右边的空白，不包括最左边的空白，所以就等于一条不删时的区域数
        for (int i = 0; i < m; i++) {
            //用扫描线考察以 a[i].first 为起点的那个部位
            int id = abs(a[i].second);
            if (a[i].second < 0) {
                if (se.size() == 0) cnt[id]--;  // 该部位是左边界
                se.insert(id);
            } else {
                if (se.size() == 1) cnt[id]--;  // 该部位是右边界
                se.erase(id);
            }
            if (se.empty()) ans++;                   // 这是一个间隙
            if (se.size() == 1) cnt[*se.begin()]++;  // 该部分独占
        }
        int mx = -1;  // 最坏情况下，排除左右边界后，独占数为-1, 相当于本来孤零零的一段被删掉了。
        for (int i = 1; i <= n; i++) mx = max(mx, cnt[i]);
        ans += mx;
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：wz20201136 (赞：5)

可以发现，线段集的并集线段个数转化为将线段映射到桶上之后不为零的段数，于是首先先将原线段集离散化。但是问题来了，如果桶里存点，就会出现将线段 $[1,4]$，$[5,6]$ 并为 $[1,6]$ 的情况，而如果桶里存边则无法处理 $l_i=r_i$ 的情况。一种可行的方案是将离散化后的左右断点 $\times2$，桶里存点，这样相邻的两个不为零的点一定就同属于一条线段了。

转化问题后用线段树求解，就非常容易了，分别维护区间内段数，左右是否有未结束的一段。但是统计答案是需要将区间内每个位置的覆盖次数减一，而直接通过线段树的区间修改无法实现。考虑到每个位置最多只会减一，所以完全可以再建一颗线段树，维护桶内每个位置都减一（若本来就为 $0$ 则不变）后的答案，再通过两个线段树的答案组合起来得到删掉每条线段的答案，取最大值即可。

时间复杂度 $O(nlogn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200005,MAXM=800005;
struct node
{
	bool lft,rt;
	int cnt;
	node operator+(const node &o) const
	{
		if(cnt==-1) return o;
		if(o.cnt==-1) return (node){lft,rt,cnt};
		return (node){lft,o.rt,cnt+o.cnt-(rt&o.lft)};
	}
}tr1[MAXM<<2],tr2[MAXM<<2];//两颗线段树
int n,l[MAXN],r[MAXN],t,ct[MAXM]/*桶*/,dif[MAXM]/*差分*/,m;
map<int,int> mp;
void init()
{
	mp.clear(),m=0;
	memset(dif,0,sizeof(dif));
}
void ls()//离散化
{
	vector<int> vc;
	for(int i=1;i<=n;i++)
		vc.push_back(l[i]),vc.push_back(r[i]);
	sort(vc.begin(),vc.end());
	m=mp[vc[0]]=1;
	for(int i=1;i<vc.size();i++)
		if(vc[i]!=vc[i-1]) mp[vc[i]]=++m;
	for(int i=1;i<=n;i++)
		l[i]=mp[l[i]]*2,r[i]=mp[r[i]]*2;
	m*=2;
}
void bd1(int u,int l,int r)
{
	if(l==r)
	{
		tr1[u].cnt=tr1[u].lft=tr1[u].rt=(ct[l]>0);
		return;
	}
	int mid=(l+r)/2;
	bd1(u*2,l,mid),bd1(u*2+1,mid+1,r);
	tr1[u]=tr1[u*2]+tr1[u*2+1];
}
void bd2(int u,int l,int r)
{
	if(l==r)
	{
		tr2[u].cnt=tr2[u].lft=tr2[u].rt=(ct[l]>1);
		return;
	}
	int mid=(l+r)/2;
	bd2(u*2,l,mid),bd2(u*2+1,mid+1,r);
	tr2[u]=tr2[u*2]+tr2[u*2+1];
}
node _0=(node){0,0,-1};
node qr1(int u,int l,int r,int L,int R)
{
	if(L<=l&&r<=R) return tr1[u];
	if(L>r||l>R) return _0;
	int mid=(l+r)/2;
	return qr1(u*2,l,mid,L,R)+qr1(u*2+1,mid+1,r,L,R);
}
node qr2(int u,int l,int r,int L,int R)
{
	if(L<=l&&r<=R) return tr2[u];
	if(L>r||l>R) return _0;
	int mid=(l+r)/2;
	return qr2(u*2,l,mid,L,R)+qr2(u*2+1,mid+1,r,L,R);
}
int main()
{
	cin>>t;
	while(t--)
	{
		init();
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&l[i],&r[i]);
		ls();
		for(int i=1;i<=n;i++)
			dif[l[i]]++,dif[r[i]+1]--;
		for(int i=1;i<=m;i++)
			ct[i]=ct[i-1]+dif[i];
		bd1(1,1,m),bd2(1,1,m);
		int ans=0;
		for(int i=1;i<=n;i++)
			ans=max(ans,(qr1(1,1,m,1,l[i]-1)+qr2(1,1,m,l[i],r[i])+qr1(1,1,m,r[i]+1,m)).cnt);
		cout<<ans<<endl;
	}
	return 0;
} 
```



---

## 作者：AThousandSuns (赞：4)

看起来我的做法最奇怪，甚至没有数据结构……发一下我的垃圾重工业做法吧……

将所有线段按 $l$ 排序。

令 $mx_i$ 表示前 $i$ 条线段中 $r$ 的最大值，那么联通块个数就应该是：

$$\sum_{i=1}^n[l_i>mx_{i-1}]$$

考虑删除了一条线段 $j$，它会对某个区间内的 $mx$ 都产生影响。这个区间满足 $mx=r_j$，因为 $mx$ 单调，可以二分求出。

删掉这条线段后，这区间里面的 $mx$，也就是前缀最大值会变成前缀次大值（不要求严格）。

再弄一个前缀次大值 $mx2$，然后就能简单算了。这个区间里面每条线段的贡献是 $[l>mx2]$，外面每条线段的贡献是 $[l>mx]$，再弄个前缀和。

时间复杂度 $O(n\log n)$。

虽然没有数据结构，但感觉比数据结构做法还难码……

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=444444;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
struct seg{
	int l,r;
	bool operator<(const seg &s)const{return l<s.l;}
}s[maxn];
int t,n,mx[2][maxn],pre[2][maxn];
int main(){
	t=read();
	while(t--){
		n=read();
		FOR(i,1,n){
			s[i].l=read();s[i].r=read();
		}
		sort(s+1,s+n+1);
		FOR(i,0,n) mx[0][i]=mx[1][i]=-2e9;
		FOR(i,1,n){
			mx[0][i]=mx[0][i-1];
			mx[1][i]=mx[1][i-1];
			if(s[i].r>mx[0][i]) mx[1][i]=mx[0][i],mx[0][i]=s[i].r;
			else mx[1][i]=max(mx[1][i],s[i].r);
			pre[0][i]=pre[0][i-1]+(s[i].l>mx[0][i-1]);
			pre[1][i]=pre[1][i-1]+(s[i].l>mx[1][i-1]);
		}
		int ans=0;
		FOR(i,1,n){
			int p1=lower_bound(mx[0]+i,mx[0]+n+1,s[i].r)-mx[0];
			int p2=lower_bound(mx[0]+i,mx[0]+n+1,s[i].r+1)-mx[0];
			if(mx[0][p1]!=s[i].r) ans=max(ans,pre[0][n]);
			else{
				p2--;
				assert(mx[0][p2]==s[i].r);
				bool in=i>=p1+1 && i<=p2+1 && s[i].l>mx[1][i-1] || (i<p1+1 || i>p2+1) && s[i].l>mx[0][i-1];
				ans=max(ans,pre[0][p1]+pre[1][min(n,p2+1)]-pre[1][p1]+pre[0][n]-pre[0][min(n,p2+1)]-in);
			}
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：little_sun (赞：2)

### 题目大意

你有$n$个区间$[l_i, r_i]$， 你要恰好删掉一个区间，使得剩下的$n-1$个区间的并的总和最多

$\texttt{eg.}$ $[1,2], [3,5], [3,7]$的并是$[1,2], [3,7]$

<!--more-->

### 题目分析

首先我们将给定的区间进行离散化

由于区间端点相邻的区间并不算相交，所以离散化时要进行特殊处理$(x=x*2-1)$

然后本题就变成了这样一个问题:

1.对于所有$[l_i, r_i]$, 把对应区间的数值$a_i$全部加上1，并统计此时所有区间并的个数$num$

2.对于每个$[l_i, r_i]$, 求出该区间内满足$a_i=1$的连续段个数，并统计最大值$ans$

那么，$ans+num$即为答案

对于步骤$1$，可以用差分求出；对于步骤$2$， 可以用前缀和求出（注意特判开头和结尾相等的情况）

### 代码

```cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)

const int MaxN = 1e6 + 10;

std::map<int, int> m1, m2;
int n, cnt, l[MaxN], r[MaxN], a[MaxN], s[MaxN];

inline void prework()
{
    m1.clear(), m2.clear();
    for (int i = 1; i <= n; i++)
        m1[l[i]] = m1[r[i]] = 1;
    cnt = 0;
    for (std::map<int, int>::iterator it = m1.begin(); it != m1.end(); it++)
        m2[it->first] = ++cnt;
    for (int i = 1; i <= n; i++)
        l[i] = m2[l[i]] * 2 - 1, r[i] = m2[r[i]] * 2 - 1;
}

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0')
    {
        if (ch == '-')
            f = 0;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? x : (-x);
}

int main()
{
    int T = read();
    while (T--)
    {
        n = read(), cnt = 0;
        for (int i = 1; i <= n; i++)
            l[i] = read(), r[i] = read();
        prework(), cnt = cnt * 2 - 1;
        for (int i = 1; i <= n; i++)
            a[l[i]]++, a[r[i] + 1]--;
        for (int i = 1; i <= cnt; i++)
            a[i] += a[i - 1];
        int num = 0, ans = -1000000;
        for (int i = 1; i <= cnt; i++)
        {
            s[i] = s[i - 1];
            num += (a[i] && !a[i - 1]);
            if (a[i] > 1 && a[i - 1] <= 1)
                ++s[i];
        }
        for (int i = 1; i <= n; i++)
        {
            int cur = s[r[i]] - s[l[i] - 1] + ((a[l[i]] > 1) && (a[l[i] - 1] > 1)) - 1;
            ans = std::max(ans, cur);
        }
        printf("%d\n", num + ans);
        for (int i = 0; i <= cnt * 2; i++)
            a[i] = s[i] = 0;
    }
    return 0;
}
```



---

## 作者：Grammar_hbw (赞：1)

暴力出奇迹。这个题暴力+优化=AC。

看到 $l,r$ 的数据范围，首先离散化。

我们可以用每一个“并集”后的那个点来充当这个“并集”的代表元，只需对这类点计数即可……等等，遇到 $[1,2] \cup [3,4]$ 怎么办？$2$ 后面那个点也被覆盖了，那代表元和普通的点无法区分了！简单，把所有坐标 $\times 2$ 就行。至于正确性，这相当于把 $(i,i+1)$ 抽象成了一个虚点，而并集的端点一定都是表示整数位置的“实点”，所以此时每一个并集的后面一定是未被覆盖的。对满足“当前点未被覆盖、前一个点被覆盖”的点计数就是答案。

考虑删区间。枚举每一个区间，暴力把它覆盖的点 $-1$ ，然后计数，计完了再加回来就行。

等等，怎么 TLE 了？一个点可能被枚举到多次，$O(n^2)$ 过 $2 \times 10^5$，显然不可能。考虑优化。

注意到如果一个点被覆盖超过 $2$ 次，那么对它的修改没有意义。而对每个区间只枚举其中被覆盖 $1$ 次的点显然不会重复枚举点，那么可以 $O(n)$ 完成对所有点的枚举！

现在做法已经呼之欲出了，看代码吧。

```cpp
#include <bits/stdc++.h> 
using namespace std;
const int N=200007;
int num[N<<2],val[N<<2],l[N],r[N]; //离散化之后最多 2n 个点，还要 ×2，所以数组要开 4 倍。
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin>>t;
	while(t-->0){
		int n;
		cin>>n;
		memset(val,0,sizeof(val[0])*(4*n+6)); // 多测不清空，爆零见祖宗。
		int cnt=0,m=0;
		for(int i=1;i<=n;i++) cin>>l[i]>>r[i],num[++cnt]=l[i],num[++cnt]=r[i]; //num 数组用来离散化，由于离散化之后该数组无用，故后面会复用。
		sort(num+1,num+cnt+1);
		cnt=unique(num+1,num+cnt+1)-num-1;
		for(int i=1;i<=n;i++) l[i]=lower_bound(num+1,num+cnt+1,l[i])-num,r[i]=lower_bound(num+1,num+cnt+1,r[i])-num;
		for(int i=1;i<=n;i++) l[i]=l[i]*2,r[i]=r[i]*2; //处理坐标。你要枚举的点不会超过离散化后点总数的 2 倍 + 3 。
		for(int i=1;i<=n;i++) val[l[i]]++,val[r[i]+1]--; //先把所有点都覆盖上，区间修改转化为差分+前缀和。
		m=cnt*2+3; 
		for(int i=1;i<=m;i++) val[i]+=val[i-1];
		cnt=0;
		for(int i=1;i<=m;i++) if(val[i]==1) num[++cnt]=i; //num 数组中保存只覆盖 1 次的点坐标。
		int res=0,ans=0;
		for(int i=1;i<=m;i++) if(val[i-1]&&(!val[i])) res++; //先计算不删线段时的答案。
		for(int i=1;i<=n;i++){
			int* ll=lower_bound(num+1,num+cnt+1,l[i]),*rr=upper_bound(num+1,num+cnt+1,r[i])-1,tmp=0; //二分找出当前区间对应的 num 数组上点的范围。注意 lower_bound 和 upper_bound 返回指针，后面也直接用指针枚举。可能存在把区间排序之后双指针的真·O(n)枚举，具体实现留作习题。
			for(int* j=ll;j<=rr;j++) if(!val[*j+1]) tmp--; //要删掉的点后面有未被覆盖的点 x，则 x 不再符合条件。
			for(int* j=ll;j<=rr;j++) val[*j]--; // 删数。
			for(int* j=ll;j<=rr;j++) if(val[*j-1]) tmp++; //删之后的点 x 前面被覆盖过了，那么 x 是新的符合条件的点。
			//注意上面几个操作的顺序。顺序不对可能导致重复计算或者漏计算（自己想想为什么）。 
			ans=max(ans,res+tmp);
			for(int* j=ll;j<=rr;j++) val[*j]++;
		}
		cout<<ans<<'\n';
	}
}
```

时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$，这个暴力做法的思维量极小。

---

## 作者：Wf_yjqd (赞：1)

典题，顶多蓝吧。

容易联想到扫描线中的线段树，所以秒掉了。

------------

考虑对于每条线段求出删去它后的答案并取最大值。

发现维护的结构要支持区间修改加减一和查询区间内连续非 $0$ 的段数。

对于线段树每个节点，标记一定非负，而我们只需要判断是否为 $0$，所以可以标记永久化。

对于每个节点维护其区间中连续非 $0$ 的段数，以及左右端点是否非 $0$，这样就可以向上合并答案了。

初始对所有端点离散化。

注意两条线段可能共用端点，那需要左儿子的右端点和右儿子的左端点相同。

但这样我们没法维护单点的加减一，所以考虑将每个点拆成三个，将区间 $[l,r]$ 变为 $[l\times3-1,r\times3+1]$ 避免以上问题。

复杂度 $\operatorname{O}(n\log n)$。

------------

于是写个臭长代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+26;
namespace Sherry_SgmTre{
    struct Node{
        int l,r,cnt,lzy;
        bool l1,r1;
    }T[maxn<<6];
    inline void Init(int id,int l,int r){
        T[id]={l,r,0,0,0,0};
        if(r-l<2){
            T[id<<1]=T[id<<1|1]={l,r,0,0,0,0};
            return ;
        }
        int mid=l+r>>1;
        Init(id<<1,l,mid);
        Init(id<<1|1,mid,r);
        return ;
    }
    inline void Modify(int id,int l,int r,int val){
        if(l<=T[id].l&&T[id].r<=r)
            T[id].lzy+=val;
        else{
            int mid=T[id].l+T[id].r>>1;
            if(l<mid)
                Modify(id<<1,l,r,val);
            if(mid<r)
                Modify(id<<1|1,l,r,val);
        }
        if(T[id].lzy)
            T[id].cnt=T[id].l1=T[id].r1=1;
        else{
            T[id].l1=T[id<<1].l1;
            T[id].r1=T[id<<1|1].r1;
            T[id].cnt=T[id<<1].cnt+T[id<<1|1].cnt-(T[id<<1].r1&&T[id<<1|1].l1);
        }
        return ;
    }
}
using namespace Sherry_SgmTre;
int Tt,n,m,l[maxn],r[maxn],st[maxn<<1],ans;
int main(){
    scanf("%d",&Tt);
    while(Tt--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&l[i],&r[i]);
            st[i]=l[i];
            st[n+i]=r[i];
        }
        sort(st+1,st+n*2+1);
        m=unique(st+1,st+n*2+1)-st-1;
        Init(1,1,m*3+1);
        for(int i=1;i<=n;i++){
            l[i]=lower_bound(st+1,st+m+1,l[i])-st;
            r[i]=lower_bound(st+1,st+m+1,r[i])-st;
            Modify(1,l[i]*3-1,r[i]*3+1,1);
        }
        ans=0;
        for(int i=1;i<=n;i++){
            Modify(1,l[i]*3-1,r[i]*3+1,-1);
            ans=max(ans,T[1].cnt);
            Modify(1,l[i]*3-1,r[i]*3+1,1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Thaumaturge (赞：1)

Div2的E题，都会的吧

就是没时间打CF（跳跃式发牢骚）

先离散化他一手 ~~离散化真的鸡肋~~ 定义线段组数为合并完后的线段个数。

删去一条线段后，很明显，所增加的线段组数就是只有这条线段覆盖的区间个数。如$[1,7],[-2,3],[4,5],[6,8]$这四条线段，只被$[1,7]$所包含的区间就是$(3,4),(5,6)$，所以断开后，答案会增加$2$。

做法至此就很显然了。把离散化后的线段坐标先全部乘以2，防止繁琐的相邻区间的判断，再用一个前缀和，每个元素以开区间$(i,i+1)$的形式维护坐标轴上的线段的情况（实现时，前缀和数组下标用右端点$i+1$表示即可）。

如相邻两坐标{$i,i+1$}，一个只被1条线段覆盖，另一个被多条线段覆盖，则$(i,i+1)$权值++（将$(i,i+1)$称之为好区间），若一个只被1条线段覆盖，另一个无线段覆盖，则$(i,i+1)$权值--，用来表示自身被删除后两侧无线段拼接，因此减少了一线段。询问时，$(l_i-1,r_i+1)$的权值之和再除以$2$就能表示该线段中有多少个只被它自己覆盖的区间了。

还要特殊处理一下！再看该线段的端点处。如果$l_i,r_i$都只被一条线段覆盖，且$l_i-1,r_i+1$被多条线段覆盖，则答案还要再$-1$，因为线段两侧是两个不配对的好区间，即左部分在右，右部分在左，去除后，两侧线段是无法断开成为一个新的线段组的。

询问的答案加上初始答案（有n个线段时的线段组数）后即为最终答案。取max即可。

（只有一个可以偷懒不减，因为除以2的时候会向下取整）

（题解里我用的树状数组代替的前缀和，反正这俩差不多是吧。。。）

代码如下：

```cpp
/*************************************************************************
	> File Name: CF1285E.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2020年01月11日 星期六 11时38分15秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 800010

using namespace std;

const int inf=800000;

//记得开2*2倍空间

int n;

int sum[N];

int l[N],r[N],a[N];

int ans,fans;

struct bittree{//树状数组
	int T[N];
	inline void add(int x,int y){
		for(re int i=x;i<=inf;i+=(i&-i))
		T[i]+=y;
		return;
	}
	
	inline int query(int x){
		int ans=0;
		for(re int i=x;i;i-=(i&-i))
		ans+=T[i];
		return ans;
	}
	inline int ret(int x,int y){
		return query(y)-query(x-1);
	}
}Q,P;

inline int getans(int x,int y){
	return (Q.ret(x,y))>>1;
}

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

inline void Input(){
	ans=0;
	n=read();
	a[0]=0;
	for(re int i=1;i<=n;++i) l[i]=read(),a[++a[0]]=l[i],r[i]=read(),a[++a[0]]=r[i];
	sort(a+1,a+a[0]+1);
	a[0]=unique(a+1,a+a[0]+1)-a-1;
	for(re int i=1;i<=n;++i) l[i]=(lower_bound(a+1,a+a[0]+1,l[i])-a)*2,r[i]=(lower_bound(a+1,a+a[0]+1,r[i])-a)*2/*,cout<<l[i]<<" "<<r[i]<<endl*/;
	//离散化
	for(re int i=1;i<=(a[0]<<1)+10;++i) sum[i]=0;//多组询问一定要记得清空！

	for(re int i=1;i<=n;++i) ++sum[l[i]],--sum[r[i]+1];
	
	for(re int i=1;i<=(a[0]<<1)+10;++i){
		sum[i]+=sum[i-1];
		if(sum[i] && !sum[i-1]) ++ans;//计算初始答案
	}

	//enter;

	return;
}

inline void solve(){
	fans=-1;
	for(re int i=1;i<=(a[0]<<1)+10;++i)
	{
		if((sum[i]==1 && sum[i-1]==0) || (sum[i]==0 && sum[i-1]==1))
		Q.add(i,-1);//(i-1,i)--
		
		else if((sum[i]==1 && sum[i-1]>1) || (sum[i]>1 && sum[i-1]==1))
		Q.add(i,1)/*,printf("plus:%d\n",i)*/;//(i,i+1)++

		if(sum[i]==1)
		P.add(i,1);
	}

	//cout<<ans<<endl;

	for(re int i=1;i<=n;++i)
	{
		if(!P.ret(l[i],r[i])) {fans=max(fans,0);continue;}
		int now=getans(l[i],r[i]+1);
		//printf("%d %d %d %d %d %d\n",l[i],r[i],sum[l[i]],sum[l[i]-1],sum[r[i]],sum[r[i]+1]);
		if(sum[l[i]]>1 && sum[l[i]-1]==1 && sum[r[i]]>1 && sum[r[i]+1]==1)
		--now/*,cout<<"!!!!"<<endl*/;
		fans=max(now,fans);
	}

	printf("%d\n",ans+fans);

	//enter;

	for(re int i=1;i<=(a[0]<<1)+10;++i)
	{
		if((sum[i]==1 && sum[i-1]==0) || (sum[i]==0 && sum[i-1]==1))
		Q.add(i,1);
		
		else if((sum[i]==1 && sum[i-1]>1) || (sum[i]>1 && sum[i-1]==1))
		Q.add(i,-1);

		if(sum[i]==1)
		P.add(i,-1);
	}//复杂度正确的树状数组还原,直接memset是错误的
	return;
}

int TT;

int main(){
	//freopen("appl.in","r",stdin);
	//freopen("appl.out","w",stdout);
	TT=read();
	while(TT--)
	{
		Input();
		solve();
	}
	return 0;
}
```


---

## 作者：冷却心 (赞：0)

【数据删除】题，建议降蓝或绿。

首先值域很大所以离散化。注意到如 $[1,4],[5,7]$ 这两个区间并不相连，但是 $4,5$ 是连续的，所以我们把下标乘以二，相当于以 $1/2$ 的步长重新标号，这样就规避了上述问题。

我们差分求出 $c_i$ 表示 $i$ 这个点被多少个区间覆盖，那么对于一个区间集合，他的并集线段个数等于满足 $c_i=0 \wedge c_{i-1}>0$ 的位置 $i$ 的个数。我们记 $r$ 表示原始区间集合的答案。

考虑枚举删除哪个集合，求出答案增量。如果删除的是 $[l,r]$，容易注意到至多减少 $1$，也就是判断一下 $r+1$ 这个位置是否满足条件。增加的位置就是满足 $l< j \le r$ 并且 $c_j=1 \wedge c_{j-1}>1$ 的位置 $j$ 数量，这个可以预处理然后差分求区间和。然后做完了。

时间复杂度 $O(n\log n)$，瓶颈在于离散化。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 2e6 + 10;
int n, m, cnt[N], tmp2[N]; LL L[N], R[N], tmp[N];
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n; m = 0;
		for (int i = 1; i <= n; i ++) {
			cin >> L[i] >> R[i]; L[i] = L[i] * 2, R[i] = R[i] * 2;
			tmp[++ m] = L[i], tmp[++ m] = L[i] - 1, tmp[++ m] = R[i], tmp[++ m] = R[i] + 1;
		} sort(tmp + 1, tmp + 1 + m); m = unique(tmp + 1, tmp + 1 + m) - tmp - 1;
		for (int i = 1; i <= n; i ++) {
			L[i] = lower_bound(tmp + 1, tmp + 1 + m, L[i]) - tmp;
			R[i] = lower_bound(tmp + 1, tmp + 1 + m, R[i]) - tmp;
			cnt[L[i]] ++, cnt[R[i] + 1] --;
		}
		int res = 0, Ans = 0;
		for (int i = 1; i <= m; i ++) 
			cnt[i] += cnt[i - 1], res += (cnt[i - 1] > 0 && cnt[i] == 0),
			tmp2[i] = (cnt[i - 1] > 1 && cnt[i] == 1) + tmp2[i - 1];
		for (int i = 1; i <= m; i ++) cerr << cnt[i] << " \n"[i == m];
		for (int i = 1; i <= m; i ++) cerr << tmp2[i] << " \n"[i == m];
		for (int i = 1; i <= n; i ++) {
			Ans = max(Ans, res - (cnt[R[i]] == 1 && cnt[R[i] + 1] == 0) + tmp2[R[i]] - tmp2[L[i]]);
		}
		cout << Ans << "\n";
		for (int i = 1; i <= m; i ++) cnt[i] = tmp2[i] = tmp[i] = 0;
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：0)

目前为止没有看到莫队做法。

~~2022/10/4，Ender32k 在学校模拟赛中试图使用莫队解决此题，且被毒瘤搬题人 1s 的时限卡到暴力分数，距今 7 个小时，望周知。~~

---

### Solution

首先可以发现线段覆盖等同于区间加/区间覆盖，最后求不包含 $0$ 的极长连续段个数。

由于只需要删除一条线段，可以先离散化后把所有线段加到数轴上，于是我们需要实现区间删除，查询全局极长非 $0$ 连续段个数。

如果把要删除的线段看成询问，我们就能够使用莫队了。考虑数轴第 $i$ 位 $+1$ 或 $-1$ 后对于答案的贡献。

如果第 $i$ 位被减到了 $0$，如果 $i-1,i+1$ 均不等于 $0$，则第 $i$ 位将原来 $i$ 所在的段分成了两半，答案增加 $1$；如果 $i-1,i+1$ 均为 $0$，则原来 $i$ 自己就是一段，现在把它删去了，对答案的贡献减少 $1$；否则对答案没有贡献

第 $i$ 位从 $0$ 增加到 $1$ 的情况同理。

于是对询问离线排序后，我们能使用莫队在 $O(n\sqrt n)$ 内解决此题。

于是你高兴地写了一发上去，连样例都过不了。因为在上述做法中，区间 $[l_i,r_i]$ 表示并不是题目所说的点。比如目前有区间 $[2,3],[5,6]$，那么加入 $[4,5]$ 后我们的做法会将 $[2,6]$ 连成一块，然而操作后的区间应该是 $[2,3],[4,6]$。

为了防止这种情况，可以将原 $[l_i,r_i]$ 的下标全部乘 $2$。这样如果存在原区间 $[l_1,r],[r+1,r_1]$ 的话，我们就会覆盖区间 $[2l_1,2r],[2r+2,2r_1]$，中间间隔了一个 $2r+1$，我们就不会把两个区间合并了。

但是这样写的常数会乘等于 $2\sqrt 2$，约等于 $3$，所以需要**奇偶排序**优化，优化后最大的测试点时间大概 $0.9s$。

[AC Code](https://codeforces.com/contest/1285/submission/174590323)

---

## 作者：youngk (赞：0)

这个题目首先我们要对于点进行离散化的处理，为接下来用树状数组作准备。经过离散化之后的点，我们可以对进行区间的累计，得到每个点对应位置上有几条线段。

先考虑不删除的情况下有多少个满足条件的union，这个答案是从1到(k+1)个点中，有多少个点满足当前位置线段覆盖数0而前一个位置线段覆盖数不为0。其中k为离散化后的最大值。这个结论比较显然，对于每个union，结尾必然有一个点为0。

呢么对于要删去的线段，其实只要会影响到有点线段覆盖数为1的情况，对于连续的线段覆盖数为1，呢么则认为他们是一个整体。做一个前缀和，认为一段连续的1和后面后续的内容非1的值，要认为是一个整体。同时，对于出现11100111这样在连续的1中前后如何碰到了0，也认为是一个整体，这样就可以实现0(1)查询两个点之间跨越了多少个区域。

我们也可以观察到对于数据1到2和3到4这两条线段对应的union应该是2，但如何我们只是普通的离散化的话会认为2和3是连在一起的，因而我们要对于每个点的值*2，实现对于变成4和6是分开的。

同时有一个点，如何查询到是同一个区域，上述计算方法对于答案的贡献度是0，但就比如上面的数据1到2和3到4，最终的答案应该是1，因为必须删去一条边，呢么有一个特殊情况，在这个union是一个区域的情况下，应该特判对于答案的贡献度为-1。特判方法是两点属于同一个区域且这两个点对应位置的线段覆盖数都为1。

注意空间实际上是要开到8*10^5。因为实际上给了4*10^5个点，同时我们将所有的点*2处理了。

最后上代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define lowbit(x) x & -x
#define endl '\n'
#pragma GCC optimize(2)
int t;
int tree[802000];
void add(int x, int num) {
    while (x <= 801000) {
        tree[x] += num;
        x += lowbit(x);
    }
}
int query(int x) {
    int ans = 0;
    while (x) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}
int c[802000],b[802000];
void solve(){
    vector<int> l,r,a;
    int x,y,n,mx = 0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x>>y;
        l.push_back(x);
        r.push_back(y);
        a.push_back(x);
        a.push_back(y);
    }
    sort(a.begin(),a.end());
    int p = unique(a.begin(),a.end())-a.begin();
    for(auto& u:l){
        u = lower_bound(a.begin(),a.begin()+p,u)-a.begin()+1;
        u<<=1;
    }
    for(auto& u:r){
        u = lower_bound(a.begin(),a.begin()+p,u)-a.begin()+1;
        u<<=1;
    }
    for(int i=0;i<n;i++){
        add(l[i],1);
        add(r[i]+1,-1);
        mx=max(mx,r[i]);
    }
    mx++;
    for(int i=1;i<=mx;i++){
        b[i]=query(i);
    }
    int ans = 0,mmax = INT_MIN,flag0 = 0,cnt = 1;
    for(int i=1;i<=mx;i++) {
        if (!b[i] && b[i - 1])
            ans++;
    }
    for(int i=1;i<=mx;i++) {
        if (b[i] > 1)
            c[i] = cnt;
        if (b[i] <= 1) {
            int p = i;
            flag0 = 0;
            while (b[p] <= 1 && p <= mx) {
                if (!b[p])
                    flag0 = 1;
                p++;
            }
            if (!flag0)
                cnt++;
            for (int j = i; j <= p; j++)
                c[j] = cnt;
            i = p;
        }
    }
    for(int i=0;i<n;i++){
        int tt = c[r[i]]-c[l[i]];
        if(c[r[i]]==c[l[i]]&&b[l[i]]==1&&b[r[i]]==1)
            tt=-1;
        mmax=max(mmax, tt);
    }
    cout<<ans+mmax<<endl;
    for(int i=0;i<n;i++){
        add(l[i],-1);
        add(r[i]+1,1);
    }


}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>t;
    while(t--)
        solve();
    return 0;
}
```



---

