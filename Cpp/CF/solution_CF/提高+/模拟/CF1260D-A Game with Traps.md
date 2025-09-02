# A Game with Traps

## 题目描述

You are playing a computer game, where you lead a party of $ m $ soldiers. Each soldier is characterised by his agility $ a_i $ .

The level you are trying to get through can be represented as a straight line segment from point $ 0 $ (where you and your squad is initially located) to point $ n + 1 $ (where the boss is located).

The level is filled with $ k $ traps. Each trap is represented by three numbers $ l_i $ , $ r_i $ and $ d_i $ . $ l_i $ is the location of the trap, and $ d_i $ is the danger level of the trap: whenever a soldier with agility lower than $ d_i $ steps on a trap (that is, moves to the point $ l_i $ ), he gets instantly killed. Fortunately, you can disarm traps: if you move to the point $ r_i $ , you disarm this trap, and it no longer poses any danger to your soldiers. Traps don't affect you, only your soldiers.

You have $ t $ seconds to complete the level — that is, to bring some soldiers from your squad to the boss. Before the level starts, you choose which soldiers will be coming with you, and which soldiers won't be. After that, you have to bring all of the chosen soldiers to the boss. To do so, you may perform the following actions:

- if your location is $ x $ , you may move to $ x + 1 $ or $ x - 1 $ . This action consumes one second;
- if your location is $ x $ and the location of your squad is $ x $ , you may move to $ x + 1 $ or to $ x - 1 $ with your squad in one second. You may not perform this action if it puts some soldier in danger (i. e. the point your squad is moving into contains a non-disarmed trap with $ d_i $ greater than agility of some soldier from the squad). This action consumes one second;
- if your location is $ x $ and there is a trap $ i $ with $ r_i = x $ , you may disarm this trap. This action is done instantly (it consumes no time).

Note that after each action both your coordinate and the coordinate of your squad should be integers.

You have to choose the maximum number of soldiers such that they all can be brought from the point $ 0 $ to the point $ n + 1 $ (where the boss waits) in no more than $ t $ seconds.

## 说明/提示

In the first example you may take soldiers with agility $ 3 $ , $ 4 $ and $ 5 $ with you. The course of action is as follows:

- go to $ 2 $ without your squad;
- disarm the trap $ 2 $ ;
- go to $ 3 $ without your squad;
- disartm the trap $ 3 $ ;
- go to $ 0 $ without your squad;
- go to $ 7 $ with your squad.

The whole plan can be executed in $ 13 $ seconds.

## 样例 #1

### 输入

```
5 6 4 14
1 2 3 4 5
1 5 2
1 2 5
2 3 5
3 5 3
```

### 输出

```
3
```

# 题解

## 作者：lytqwq (赞：11)

~~抢第一篇题解~~

因为没有翻译，所以贴一下QQ自带的翻译（我英语不好啊QAQ），感性理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/a1ghwom6.png)

建议拖到新标签页看

### 二分

首先我们对每个士兵按a从大到小排序。所以当我们取x个士兵时就是用前x个a[i]，然后这组士兵的最小a就是a[x]。我们二分一个最大的x，模拟取mid个士兵是不是可行。

### 如何模拟

~~当时我就是因为这个最后没A~~

设sum为需要的时间

差分算出陷阱有威胁的位置，然后到每个位置时，如果有威胁sum+=3；因为（我去，然后我回来，然后我带着士兵再去），不然的话sum+=1；因为（我直接带着士兵一起去）。

如果sum<=t，return 1；不然return 0;

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200010
int m,n,k,t;
int a[N];
int l[N],r[N],d[N],vi[N];
bool check(int x)
{
	int jd=a[x];
	for(int i=1;i<=k;i++)
	{
		if(d[i]>jd)
		{
			vi[l[i]]++;
			vi[r[i]+1]--;
		}
	}
	int last=0,sum=0;
	for(int i=1;i<=n+1;i++)
	{
		vi[i]=vi[i]+vi[i-1];
		if(vi[i]!=0)
		{
			sum+=3;
		}
		else
		{
			sum+=1;
		}
	}
	if(sum<=t)
	{
		return 1;
	}
	return 0;
}
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	cin>>m>>n>>k>>t;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d%d",&l[i],&r[i],&d[i]);
	}
	sort(a+1,a+m+1,cmp);
	int ll=0,rr=m+1,mid;
	while(ll<rr)
	{
		mid=(ll+rr)>>1;
		memset(vi,0,sizeof(vi));
		if(check(mid))
		{
			ll=mid+1;
		}
		else
		{
			rr=mid;//菜鸡lyt二分写的比较（很）丑 
		}
	}
	if(rr==0)
	{
		rr++;
	}
	printf("%d\n",rr-1);
}
/*
5 6 4 14
1 2 3 4 5
2 5 2
2 2 5
2 3 5
3 5 3

*/
```



---

## 作者：Lydia1010__ (赞：5)

## 本题思路：
拿到这道题发现其实是可以二分答案的，因为如果可以带 $x$ 人在规定的时间内到达终点，那么带比 $x$ 少的人就一定合法。

考虑如何判断当前人数能否过去。我们贪心选择当前跑得最快的几人，然后以其中最慢的为标准看看有哪些陷阱会拦住他。这些陷阱就需要我先走到 $r$，再回来接这个人。

那么这些陷阱就会被走三遍，考虑到陷阱中的位置有交集走三遍会浪费交集部分，我们就需要去掉交集。那么其实可以差分，被覆盖的部分走三遍，其余部分走一遍即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,t;
struct f{int l,r,k;}a[200005];
int b[200005],sum[200005];
bool cmp(f x,f y){return x.k<y.k;}
int check(int l){
	int op=b[n-l+1];
	for(int i=1;i<=m;i++) sum[i]=0;
	for(int i=1;i<=k;i++){
		if(a[i].k>op) sum[a[i].l]++,sum[a[i].r+1]--;
	}
	int ans=0;
	for(int i=1;i<=m;i++) sum[i]=sum[i-1]+sum[i],ans+=(sum[i]>0?1:0);
	if(m+ans*2+1<=t) return 1;
	return 0;
}
signed main(){
	cin>>n>>m>>k>>t;
	for(int i=1;i<=n;i++) cin>>b[i];
	sort(b+1,b+1+n);b[n+1]=1e18;
	for(int i=1;i<=k;i++){cin>>a[i].l>>a[i].r>>a[i].k;}
	sort(a+1,a+1+k,cmp);
	int l=0,r=n,sum=0;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)) l=mid+1,sum=mid;
		else r=mid-1;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：SilverLi (赞：2)

> [A Game with Traps の 传送门](https://www.luogu.com.cn/problem/CF1579G)
>
> [开一开](https://www.cnblogs.com/Silver-Wolf/p/18690045/CF1260D)

首先，假设带 $p$ 个人可以，那么带更少的人一定可以。

那么，可以**二分**带多少个人。

设当前二分带 $x$ 个人。

带敏捷值最大的 $x$ 个士兵肯定最好。

先**去除当前无用的陷阱**，即 $d_i$ 小于等于 $x$ 个士兵中的最小敏捷值。

### 陷阱区间不相交时

然后就是自己从 $l_i$ 走到 $r_i$ 解除这个陷阱，再走回来

### 陷阱区间相交时

看一看下面这个。

![](https://cdn.luogu.com.cn/upload/image_hosting/95wguc7s.png)

肯定不会从一个一个地从每个区间左边走到右边。

而是从第一个区间左边一直走到第二个区间右边。

写的时候直接左右端点差分，加贡献时对 $2$ 取个 $\min$（往返总共走 $2$ 次）。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid (l + r >> 1)
using namespace std;
inline int read()
{
    int f = 0, ans = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return f ? -ans : ans;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
constexpr int N = 2e5 + 5, inf = 1e18;
int m, n, k, t, a[N];
int adj[N];
struct trap
{
    int l, r, d;
} b[N];
inline bool check(int x)
{
    int mn = a[x], ti = n + 1;
    for (int i = 1; i <= k; ++i)
        if (mn < b[i].d)
            adj[b[i].l] += 2, adj[b[i].r + 1] -= 2;
    for (int i = 1; i <= n; ++i)
        adj[i] += adj[i - 1], ti += min(adj[i], 2ll);
    for (int i = 1; i <= n; ++i)
        adj[i] = 0;
    return ti <= t;
}
signed main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    m = read(), n = read(), k = read(), t = read();
    for (int i = 1; i <= m; ++i)
        a[i] = read();
    sort(a + 1, a + m + 1, greater<>());
    a[0] = inf;
    for (int i = 1; i <= k; ++i)
        b[i].l = read(), b[i].r = read(), b[i].d = read();
    int l = 0, r = m, it = -1;
    while (l <= r)
        check(mid)
            ? (it = mid, l = mid + 1)
            : (r = mid - 1);
    write(it);
    return 0;
}
```

---

## 作者：amlhdsan (赞：2)

非常好的一道训练二分答案思想和差分的题目。
## 基本思路
二分答案，每次判断带 $x$ 个士兵是否可以，可以的话就再次往上查，直到人数再也不能上升为止。代码如下：

```cpp
int l = 0, r = n + 1, mid;

while(l < r) {
    mid = l + r >> 1;
    if(check(mid)) {
        l = mid + 1;
    } 
    else {
        r = mid;
    }
}
```

但是这个 `check` 函数怎么写呢？

首先，很显然的一点就是：尽可能带敏捷度大的士兵，这样可以过滤掉尽可能多的陷阱，也就是说，危险等级小于等于敏捷度的陷阱可以直接忽略。其次，对于一个陷阱来说，如果其和其他陷阱的“线”（也就是陷阱的位置到消除的位置）没有重叠，应该在这个“线”上走三遍（就是独自过去，回来，再带着士兵过去）；如果有重叠，就“一路走到底”，将陷阱全部排除了再走回来带士兵继续走。

基于这一点，很显然地可以使用差分和前缀和来做扫描线，如果此处有标记，就把答案加三；如果没有，就加一。最后判断时间是否小于 $t$，返回 `true` 或者 `false`。

## 具体代码
```cpp
#include <bits/stdc++.h>

#define N 200010

using namespace std;


int n, m, k, t;
int a[N];

struct node {
    int l, r;
    int minn;
}b[N];

inline bool cmp(int x, int y) {
    return x > y;
}

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int c[N];

bool check(int x) {
    memset(c, 0, sizeof(c));
    int minn = a[x];

    for(int i = 1; i <= k; ++i) {
        if(b[i].minn > minn) {
            ++c[b[i].l];
            --c[b[i].r + 1];
        }
    }
    int ret = 0;
    for(int i = 1; i <= m + 1; ++i) {
        c[i] += c[i - 1];
        if(c[i] != 0) {
            ret += 3;
        }
        else {
            ++ret;
        }
    }
    return ret <= t;
}

int main() {

    n = read();
    m = read();
    k = read();
    t = read();

    for(int i = 1; i <= n; ++i) {
        a[i] = read();
    }

    sort(a + 1, a + n + 1, cmp);

    for(int i = 1; i <= k; ++i) {
        b[i].l = read();
        b[i].r = read();
        b[i].minn = read();
    }

    int l = 0, r = n + 1, mid;

    while(l < r) {
        mid = l + r >> 1;
        if(check(mid)) {
            l = mid + 1;
        } 
        else {
            r = mid;
        }
    }

    cout << max(r - 1, 0) << endl;

    return 0;
}
```

---

## 作者：ZjfAKIOI (赞：2)

首先，我们不难想到，我们一定是带着敏捷值最高的士兵走。考虑二分枚举带多少个士兵。这样问题就转化成了判断带 $c$ 个士兵能否在 $t$ 秒内到达点 $n+1$，其中 $c$ 是二分每举出的值。我们考虑将每个的 $l$ 和 $r$ 障碍之间分成一段，容易发现，每段路程有两种情况:
1. 总共走一次
2. 总共走三次

第一种情况就是所有士兵都能通过这个障碍，则直接通过。第二种情况就是有士兵不能通过，这时就需要自己去走到 $r$，再走回来，再带着兵走过去，所以是走三次。我们可以拿差分来维护每一段的情况。具体实现见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n,k,t,tot;
int cha[200005],a[200005];
struct node{
	int l,r,d;
}xi[200005];
bool cmp(int x,int y){
	return x>y;
}
bool check(int x){
	memset(cha,0,sizeof(cha));
	int cnt=0;
	int minn=a[x];
	for(int i=1;i<=k;i++){
		if(xi[i].d>minn){
			cha[xi[i].l]++;//差分维护每个区间
			cha[xi[i].r+1]--;
		}
	}
	for(int i=1;i<=n+1;i++){
		cha[i]+=cha[i-1];//前缀和
		if(cha[i]!=0) cnt+=3;//如果不为零就要去消灭障碍
		else cnt++;//否则直接通过
	}
	return cnt<=t;
}
int main(){
	cin>>m>>n>>k>>t;
	for(int i=1;i<=m;i++) cin>>a[i];
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=k;i++){
		int l,r,d;
		cin>>xi[i].l>>xi[i].r>>xi[i].d;
	}
	int l=0,r=m+1,mid,ans=0;
	while(l<r){
		mid=(l+r)>>1;//二分答案
		memset(cha,0,sizeof(cha));
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else{
			r=mid;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

[Blog](https://www.cnblogs.com/zhr0102/p/18943976)

## Sol.1 二分

注意到选**敏捷度更大**的士兵一定更优，所以选择的士兵敏捷度一定是最大的那几个，具有单调性。于是考虑**二分**选的最小敏捷度的士兵。

那么危险度大于最小敏捷度的陷阱就必须解决掉。考虑在陷阱已知的情况下，如何耗费最少的时间。首先我们把路径拆成“带士兵走”和“不带士兵走”两部分，发现带士兵走的部分一定只走了 $n+1$ 步，这是显然的。考虑不带士兵走的部分，此时是将军去排除陷阱的时候，因此需要走到右端点，再走到左端点，那么若一段路径被陷阱的区间覆盖，则最优策略下**一定会被走两次**。

如果区间两两不交，这样做的最优性是显然的，但是如果相交呢？考虑推式子，如果遇到一个区间回一个区间，则会**多走一遍两区间的重叠部分**。因此把所有重叠的区间全部走完后，再来带士兵走是最优的。依次用差分计算即可。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
using pi=pair<int,int>;
const int N=200005,inf=0x3f3f3f3f;
int m,n,k,t,a[N],lx[N],rx[N],dx[N],f[N],res;
bool cmp(int x,int y)
{
	return x>y;
}
bool check(int x)
{
	int mn=a[x];res=n+1;
	memset(f,0,sizeof(f));
	for(int i=1;i<=k;i++)
	{
		if(dx[i]>mn)
		{
			f[lx[i]]++;
			f[rx[i]]--;
		}
	}
	for(int i=1;i<=n;i++)
		f[i]+=f[i-1];
	for(int i=0;i<=n;i++)
		if(f[i])
			res+=2;
	return (res<=t);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>m>>n>>k>>t;
	for(int i=1;i<=m;i++)cin>>a[i];
	a[0]=inf;
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=k;i++)
	{
		cin>>lx[i]>>rx[i]>>dx[i];
		lx[i]--;
	}
	int l=0,r=m,mid;
	while(l<r)
	{
		mid=(l+r+1)>>1;
		if(check(mid))l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}
```


## Sol.2 并查集

发现二分的过程等价于不断向选的士兵集合里添加最大的几个，于是考虑直接维护这个过程，并且维护被覆盖的点的数量。因为每个点被覆盖之后一定不会再取消覆盖了，所以只要我们在它**第一次被覆盖的时候**统计其贡献即可。为了保证每个点只被遍历一次，所以使用“**并查集维护序列连通性**”的 trick，每个点的父亲指向大于等于这个点的坐标的第一个未覆盖的点，操作的时候暴力跳即可做到均摊线性复杂度。

关于排序的部分，发现值域很小，所以直接**桶排序**即可。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
using pi=pair<int,int>;
const int N=200005,inf=0x3f3f3f3f;
int m,n,k,t,a[N],fa[N],res,suf[N];
void init()
{
	for(int i=0;i<=n+1;i++)fa[i]=i;
}
int findf(int x)
{
	if(fa[x]!=x)fa[x]=findf(fa[x]);
	return fa[x];
}
void combine(int x,int y)
{
	int fx=findf(x),fy=findf(y);
	fa[fx]=fy;
}
int h[N],idx=0;
struct Node{
	pi v;int ne;
}b[N];
void add(int u,pi v)
{
	b[++idx]={v,h[u]};
	h[u]=idx;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>m>>n>>k>>t;
	init();
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
		suf[a[i]]++;
	}
	for(int i=200000;i>=0;i--)suf[i]+=suf[i+1];
	res=n+1;
	for(int i=1;i<=k;i++)
	{
		int l,r,d;
		cin>>l>>r>>d;
		l--;
		add(d,{l,r});
	}
	for(int i=200000;i>=1;i--)
	{
		for(int j=h[i+1];j;j=b[j].ne)
		{
			pi itm=b[j].v;
			int lx=findf(itm.fi),rx=itm.se;
			while(lx<rx)
			{
				res+=2;
				combine(lx,lx+1);
				lx=findf(lx);
			}
		}
		if(res>t)
		{
			cout<<suf[i+1];
			return 0;
		}
	}
	cout<<suf[0];
	return 0;
}
```

---

## 作者：kkxacj (赞：1)

#### 题面描述

你有 $m$ 位士兵，每位士兵敏捷值为 $a_i\left(1 \leq a_i \leq 2\cdot10^5\right)$。

你要带领士兵从线段的 $0$ 点到 $n+1\left(1 \leq n \leq 2\cdot10^5\right)$ 点。

线段上有 $k\left(1 \leq k \leq 2\cdot10^5\right)$ 个陷阱，$l_i\left(1 \leq l_i \leq 2\cdot10^5\right)$ 代表第 $i$ 个陷阱的位置，$d_i\left(1 \leq d_i \leq 2\cdot10^5\right)$ 为危险等级（当士兵移动至 $l_i$ 且 $a_i<d_i$，就会被杀死，陷阱无法伤害你）。当你走到 $r_i\left(1 \leq r_i \leq 2\cdot10^5\right)$ 时，可以解除这个陷阱。

你要选择一些士兵，并在 $t\left(1 \leq t \leq 2\cdot10^5\right)$ 秒内带着**所有的**士兵走到 $n+1$ 点，你可以进行以下操作：

- 若你的位置在 $x$，则可以耗费 $1$ 秒走到 $x-1$ 或 $x+1$。
- 若你和士兵的位置都在 $x$，则可以耗费 $1$ 秒一起走到 $x-1$ 或 $x+1$，但不能让士兵处于危险之中。
- 若你的位置在 $x$，并且满足 $r_i=x$，你可以解除这个陷阱（不花费时间）。

每次操作后，你和士兵的坐标都应为整数。

你要选择尽可能多的士兵，在 $t$ 秒内把它们从 $0$ 点带到 $n+1$ 点。

#### 思路

考虑先按 $a_i$ 给士兵排序，然后二分一个 $mid$ 表示我带 $mid$ 个人是否能在 $t$ 秒内走到终点，肯定是选后 $mid$ 个最优。

然后考虑如何算贡献，对于需要解决的陷阱，如果不交，贡献为 $\left(r_i-\left(l_i-1\right)\right)\times 2$ ，考虑相交会有什么问题。

相交后，我们更希望将相交的陷阱全部拆完然后在回去，所以最终贡献应是所有需要拆的陷阱范围的并集乘二。

差分前缀和即可，复杂度单 $\log$。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 2e5+10;
int m,n,k,t,a[N],c[N],l,r,sum,mid,ans;
struct w
{
	int l,r,x;
}b[N]; 
inline bool check(int x)
{
	sum = n+1;
	for(int i = 0;i <= n+1;i++) c[i] = 0;
	for(int i = 1;i <= k;i++)
		if(b[i].x > a[m-mid+1])
			c[b[i].l]++,c[b[i].r+1]--;
	for(int i = 1;i <= n+1;i++) c[i] += c[i-1],sum += (c[i]>0)*2;
	return (sum <= t);
}
signed main()
{
	read(m),read(n),read(k),read(t);
	for(int i = 1;i <= m;i++) read(a[i]);
	sort(a+1,a+1+m);
	for(int i = 1;i <= k;i++) read(b[i].l),read(b[i].r),read(b[i].x);
	l = 1,r = m; //ans初值为0，不用管0 
	while(l <= r)
	{
		mid = ((l+r)>>1);
		if(check(mid)) ans = mid,l = mid+1;
		else r = mid-1;
	}
	print(ans); flush();
	return 0;
}
```

---

## 作者：yangmuguang (赞：1)

### 题意

你有 $m$ 个士兵，第 $i$ 个士兵的能力值为 $a_i$。你要选择一些士兵，和你从初始的 $0$ 点到第 $n+1$ 点。

为了阻碍通行，有 $k$ 个机关，第 $i$ 个机关有 $3$ 个参数 $l_i,r_i,d_i$。

若你的士兵们到达了 $l_i$ 且有一个士兵能力值小于 $d_i$，机关会被触发，你就失败了。你的能力值可以认为是无限。

但是，如果你独自走到 $r_i$，你可以解除机关 $i$。

你一共可以进行 $t$ 次操作：

1.自己移动一单位距离。

2.若你和士兵们在一起，你们可以在不触发任何机关的前提下一起移动一单位距离。

3.若你在一个机关 $j$ 的 $r_j$ 上，你可以不花费任何操作次数解除这个机关。

求你最多带多少士兵。

### 思路

首先，假设要带 $x$ 个士兵，则带能力最强的 $x$ 名士兵一定最优。

又可以看出，若带 $x$ 名士兵不行，带 $x+1$ 名士兵也一定不行，满足单调性。考虑二分。

二分士兵数量，check 函数里统计所有需要解除的机关，处理出队长为了解除机关自己要走的多余的路（也就是从所有危险的机关的 $l$ 到 $r$ 的距离，注意重复走的只算一次，需要把机关按左端点排序），最后与 $t$ 比较即可。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
ll n,m,k,t,a[200005],ans=0;
bool danger[200005];
vector<ll>v;
struct trap
{
	ll l,r,d;
	bool operator<(trap ot)
	{
		return l==ot.l?r<ot.r:l<ot.l;
	}
}aaa[200005];
bool chk(ll x)
{
	ll mn=a[n-x+1],lst=0,cnt=0;
	memset(danger,0,sizeof(danger));
	for (ll i=1;i<=k;i++)
	{
		if (aaa[i].d>mn)
		{
			if (aaa[i].l<=lst)
			{
				cnt+=max(0ll,aaa[i].r-lst);
				lst=max(lst,aaa[i].r);
			}
			else
			{
				cnt+=aaa[i].r-aaa[i].l+1;
				lst=aaa[i].r;
			}
		}
	}
	return t>=1+m+2*cnt;
}
int main()
{
	faster;
	cin>>n>>m>>k>>t;
	for (ll i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for (ll i=1;i<=k;i++)
	{
		cin>>aaa[i].l>>aaa[i].r>>aaa[i].d;
	}
	sort(aaa+1,aaa+1+k);
	sort(a+1,a+1+n);
	ll l=1,r=n;
	while (l<=r)
	{
		ll mid=(l+r)/2;
		if (chk(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：SengRiy (赞：1)

限定的时间条件与最大答案可以考虑到二分答案。

二分士兵的数量，当已知士兵数量 $sum$ 时，很显然最优就是选出敏捷值的前 $sum$ 大。

对于一个陷阱，会对士兵造成影响当前仅当其提供的伤害值大于第 $sum$ 大敏捷值。

于是可以将所有能造成影响的陷阱覆盖到区间上，也就是对于每个位置只有存在陷阱和不存在两个状态。

陷阱中的每个位置由于先经过解除陷阱后需要再走一个来回，所以需要走三次。于是我们便可以用差分求出每个区间是否有陷阱，再线性模拟一遍，最后只需检查最后用时是否小于 $k$ 便做完了。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, m, k, t, a[N];
int l[N], r[N], d[N], vis[N];

bool check(int mid) {
  memset(vis, 0, sizeof vis);
  // 清空 vis 数组
  int jd = a[mid];
  for (int i = 1; i <= k; ++ i) {
    if (d[i] > jd) {
      vis[l[i]] ++;
      vis[r[i] + 1] --;
    }
  }
  // 差分判断位置上是否有陷阱
  int sum = 0;
  for (int i = 1; i <= m + 1; ++ i) {
    vis[i] += vis[i - 1];
    if (vis[i] != 0) {
      sum += 3;
      // 若存在陷阱则此位置需要走三次
    } else {
      sum += 1;
    }
  }
  return (sum <= t);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> k >> t;
  for (int i = 1; i <= n; ++ i) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1, [](int a, int b) {
    return a > b;
  });
  for (int i = 1; i <= k; ++ i) {
    cin >> l[i] >> r[i] >> d[i];
  }
  int l = 0, r = n + 1, mid, ans = 0;
  while (l < r) {
    mid = l + r >> 1;
    if (check(mid)) {
      l = mid + 1;
      // ans = mid;
    } else {
      r = mid;
    }
  }
  if (r == 0) {
    ++ r;
  }
  cout << r - 1;
  return 0;
}
```

---

## 作者：TanX_1e18 (赞：1)

对于每个陷阱，考虑其对时间的影响，当 $l_i>r_i$ 时，显然无意义，否则需要额外从 $l_i-1$ 到 $r_i$ 来回走一次再带士兵走。

再考虑两个陷阱之间的影响，如果有一组 $i,j$ 使得 $l_i\le l_j \le r_i \le r_j$，则直接从 $l_i-1$ 走到 $r_j$ 消掉两个陷阱更优

由此得到一个结论，把每个陷阱看作一条线段，总时间即为 $n+1$ 加上 $2$ 乘陷阱覆盖的总点数。

对于每个士兵，只需要考虑危险度大于其敏捷度的陷阱，于是可以对每个点用优先队列处理出覆盖它的线段危险度最大值，然后对值域后缀和一下。

预处理完后只需要知道敏捷度最低士兵的敏捷度即可 $O(1)$ 求出时间，于是不需要二分了，直接对士兵按敏捷度从大到小排，枚举最小敏捷度即可。

总复杂度 $O(n\log n)$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int a[N],nd[N];
int n,m,k,t;
priority_queue<int>q;
int num[N];
vector<pair<int,int> >jntm[N];
int main()
{
    cin>>n>>m>>k>>t;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=k;i++)
    {
        int l,r,v;
        cin>>l>>r>>v;
        if(l<=r)
        {
            jntm[l].push_back({v,1});
            jntm[r+1].push_back({v,-1});
        }
    }
    for(int i=1;i<=m+1;i++)
    {
        int len=jntm[i].size();
        for(int j=0;j<len;j++)
        {
            if(jntm[i][j].second==1)
            q.push(jntm[i][j].first);
            num[jntm[i][j].first]+=jntm[i][j].second;
        }
        while((!q.empty())&&(!num[q.top()]))
        {
            q.pop();
        }
        if(!q.empty())nd[q.top()]++;
    }
    for(int i=N-2;~i;i--)
    nd[i]+=nd[i+1];
    //预处理
    sort(a+1,a+n+1);
    reverse(a+1,a+n+1);
    //对敏捷度排序
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(m+1+nd[a[i]+1]*2<=t)//O(1)计算
        {
            ans=i;
        }
        else
        break;
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：HyperSQ (赞：1)

提供一个不用二分的另类思路。

显然，带队的可以看作是一个能力为 $+\infty$ 的士兵。对于一个能力值为 $a_i$ 的兵，只有那些 $d_j>a_i$ 的陷阱会影响他。考虑只有一个陷阱的最简单情况，我们可以将这个士兵（小队）留在 $l_j$ 前，用带队的 $+\infty$ 去走到 $r_j$ 卸载陷阱，然后回去接那个士兵（小队），这样子一段路会比正常多走 $2$ 次。有多个陷阱的话，多走两次的区间实际上就是这些陷阱的区间并。

现在考虑每次加入一个士兵（显然每次应该加入能力最大的士兵），将影响它的陷阱区间全部染成 $1$，看看总时间 $n+1+2\operatorname{cnt}_1
$ 会不会超过 $T$，如果超过，跳出就可以了。用线段树维护即可。

（当然还是二分方便，有点大炮打蚊子了）

[Code](https://www.luogu.com.cn/paste/lkbwxt4b)

---

## 作者：Laisira (赞：1)

### 思路
简单二分，显然选最大的几个人一定不劣，拆掉 $i$ 陷阱有意义当且仅当所有 $j$，使得 $d_j \leq d_i$ 被拆掉，二分拆陷阱的最小值，模拟跑一边就行了。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 400005 
using namespace std;
int a[Maxn];
struct node {
	int l,r,d;
	bool operator<(const node&is)
	const {return l != is.l?l < is.l:r < is.r;}
} e[Maxn],t[Maxn];
signed main()
{
	int m,n,k,t1;
	cin>>m>>n>>k>>t1;
	for(int i=1;i<=m;i++)
		cin>>a[i];
	sort(a+1,a+1+m);
	for(int i=1;i<=k;i++)
		cin>>e[i].l>>e[i].r>>e[i].d;
	int l = 0,r = 4e5+5,mid;
	while(l < r) {
		int tot = 0;
		mid = (l+r)>>1;
		for(int i=1;i<=k;i++)
			if(e[i].d >= mid)
				t[++tot] = e[i];
		sort(t+1,t+1+tot);
		int ans = 0;
		for(int i=1;i<=tot;i++)  {
			int l1 = t[i].l,r1 = t[i].r;
//			cout<<i<<"|";
			while(i < tot&&t[i+1].l <= r1)r1 = max(r1,t[++i].r);
			ans += (r1-l1+1)*2;
//			cout<<l1<<" "<<r1<<"]\n";
		}
//		cout<<mid<<" "<<ans+n+1<<"\n";
		if(ans+n+1 <= t1)r = mid;
		else l = mid+1;
	} int maxn = 0;
	for(int i=1;i<=k;i++)
		if(e[i].d < l)
			maxn = max(maxn,e[i].d);
	l = 0,r = m;
	while(l < r) {
		mid = (l+r+1)>>1;
		if(a[mid] < maxn)l = mid;
		else r = mid-1;
	}
//	cout<<a[l]<<" "<<maxn<<" ";
	cout<<m-l;
	return 0;
}
```

---

## 作者：_determination_ (赞：0)

显然要二分答案。

选 $x$ 名士兵的最优方案一定是选敏捷度最高的 $x$ 名士兵。那么我们就得到了一个需要拆除的陷阱集合 $S$。

思考将军是怎么拆陷阱的。肯定是走到一个陷阱的 $l-1$ 然后自己过去拆一些陷阱再回来把兵带过去，思考我们浪费了哪些时间。显然是折返这一段。

那么有交的线段我们给他合并成一条大线段，然后走到一个线段的 $l-1$ 就将军自己去拆陷阱然后折返把兵带过去。

单次 check 写的好的话是 $O(n)$ 的，写的不好就是 $O(n\log n)$ 的，虽然总复杂度 $O(n\log ^2n)$ 也能过。

[Link.](https://codeforces.com/contest/1260/submission/304551885)

---

## 作者：Oracynx (赞：0)

## [CF1260D] A Game with Traps 题解

### 思路分析

如果我们需要带 $x$ 个士兵到达目的地，显然带敏捷度最大的 $x$ 个士兵不劣。

同样的，如果能带 $x$ 个士兵在 $t$ 秒内到达，那么当 $y \le x$ 时显然也能成功到达。

因为所有的士兵的敏捷度都大于先前的，之前有解显然现在依然有解。

显然可以二分。

下文定义最小的士兵敏捷度为 $r$，则需要考虑的陷阱为 $d_i > r$。

如果需要度过的陷阱为 $[l_i, r_i]$，显然花费为 $3 \times (r_i - l_i)$。

因为“我”需要前往 $r_i$，拆除陷阱，返回 $l_i$，带队前往 $r_i$。

可以看作如果当前出于陷阱范围内则每一步需要花费 $3$ 的时间。

而对于多个陷阱相交的情况下可以将这几个陷阱保留最左的 $l$ 和最右的 $r$。

其余的陷阱在拆除范围最大的陷阱时顺便拆了即可。

而如果当前不处于任何陷阱内时只需花费 $1$ 的时间。

将有效陷阱的开始与起点差分一下即可。

## 代码实现

```cpp
#include <algorithm>
#include <cstdio>
#include <functional>
constexpr int MaxN = 2e5 + 5;
int m, n, k, t;
int p[MaxN];
int l[MaxN];
int r[MaxN];
int d[MaxN];
int cf[MaxN];
bool check(int x)
{
    int minPlayer = 0x3f3f3f3f;
    for (int i = 1; i <= x; i++)
    {
        minPlayer = std::min(minPlayer, p[i]);
    }
    for (int i = 1; i <= k; i++)
    {
        if (d[i] > minPlayer)
        {
            cf[l[i]]++;
            cf[r[i] + 1]--;
        }
    }
    int cost = 0;
    for (int i = 1; i <= n + 1; i++)
    {
        cf[i] += cf[i - 1];
        if (cf[i] >= 1)
        {
            cost += 3;
        }
        else
        {
            cost++;
        }
    }
    for (int i = 1; i <= n + 1; i++)
    {
        cf[i] = 0;
    }
    return cost <= t;
}
int main()
{
    scanf("%d%d%d%d", &m, &n, &k, &t);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &p[i]);
    }
    std::sort(p + 1, p + 1 + m, std::greater<>());
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d%d", &l[i], &r[i], &d[i]);
    }
    int l, r;
    l = 0;
    r = m;
    int res = 0;
    for (; l <= r;)
    {
        int mid = (l + r) / 2;
        if (check(mid))
        {
            l = mid + 1;
            res = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    printf("%d\n", res);
    return 0;
}


```

---

