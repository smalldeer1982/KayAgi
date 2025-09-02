# Tourist

## 题目描述

Tourist walks along the $ X $ axis. He can choose either of two directions and any speed not exceeding $ V $ . He can also stand without moving anywhere. He knows from newspapers that at time $ t_{1} $ in the point with coordinate $ x_{1} $ an interesting event will occur, at time $ t_{2} $ in the point with coordinate $ x_{2} $ — another one, and so on up to ( $ x_{n},t_{n} $ ). Interesting events are short so we can assume they are immediate. Event $ i $ counts visited if at time $ t_{i} $ tourist was at point with coordinate $ x_{i} $ .

Write program tourist that will find maximum number of events tourist if:

- at the beginning (when time is equal to 0) tourist appears at point 0,
- tourist can choose initial point for himself.

Yes, you should answer on two similar but different questions.

## 样例 #1

### 输入

```
3
-1 1
42 7
40 8
2
```

### 输出

```
1 2
```

# 题解

## 作者：HowToCarry (赞：5)

[Tourist](https://www.luogu.com.cn/problem/CF76F)

### 朴素做法
我们定义 $dp_i$ 表示最后看 $i$ 事件能看到的最多的事件数量，然后我们考虑转移，首先肯定的是我们一定是从 $t_i$ 小的转移到 $t_i$ 大的事件，所以我们首先要对每个事件按时间 $t_i$ 排序，能从 $j$ 转移到 $i$ 的条件是 $(t_i -  t_j)\times v\leq \left | x_i - x_j\right|$，转移方程为 $dp_i = \max {dp_j}+1$，然后将 $dp_i$ 初值赋为 $1$ 即可，复杂度 $O(n^2)$，对于第一问我们只需再加一个判断 $t_i\times v\geq |x_i|$ 即可。
### 优化
我们发现朴素做法的瓶颈在 dp 转移的过程，我们需要花时间去遍历，所以显然我们需要数据结构优化。我们先对转移条件拆开：

当 $x_i\leq x_j$ 时，原式可化为 $t_i\times v + x_i\geq t_j\times v + x_j$；

当 $x_i > x_j$ 时，原式可化为 $t_i\times v - x_i\geq t_j\times v - x_j$；

然后我们发现：

当 $x_i\leq x_j$ 时，若 $t_i\times v + x_i\geq t_j\times v + x_j$ 成立，那么当 $x_i > x_j$ 时，$t_i\times v + x_i\geq t_j\times v + x_j$ 也必然成立；

当 $x_i > x_j$ 时，若 $t_i\times v - x_i\geq t_j\times v - x_j$ 成立，那么当 $x_i \leq x_j$ 时，$t_i\times v - x_i\geq t_j\times v - x_j$ 也必然成立；

我们设 $u_i = t_i\times v - x_i$，$v_i = t_i\times v + x_i$，那么我们发现若 $j$ 可以转移到 $i$，那么必然满足 $u_j\leq u_i$ 并且 $v_j\leq v_i$，我们发现这其实就是一个二维偏序问题，用树状数组维护即可，对于第一问我们只需关注第一象限的点即可。
### 注意
1.记得开 long long。

2.用树状数组需要离散化。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define il inline
#define ll long long
using namespace std;
const int N=200005;
int n,s,k,len=1;
ll ans;
int x[N],t[N],tmp[N<<1];//tmp数组用于离散化
ll dp[N],c[N<<1];
struct nd{
	int u,v;
}a[N];
il ll mx(ll p,ll q){
	return p>q?p:q;
}
void add(int i,ll u){
	while(i<=len){
		c[i]=mx(u,c[i]);
		i+=i&-i;
	}
}
ll query(int i){
	ll sum=0;
	while(i){
		sum=mx(sum,c[i]);
		i-=i&-i;
	}
	return sum;
}
bool cmp(nd p,nd q){
	if(p.u==q.u) return p.v<q.v;
	return p.u<q.u;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>t[i];
		dp[i]=1;
	}
	cin>>s;
	for(int i=1;i<=n;i++){
		a[i].u=t[i]*s-x[i];
		tmp[++len]=a[i].u;
		a[i].v=t[i]*s+x[i];
		tmp[++len]=a[i].v;
	}
	sort(tmp+1,tmp+len+1);
	len=unique(tmp+1,tmp+len+1)-tmp-1;
	k=lower_bound(tmp+1,tmp+len+1,0)-tmp;//记录离散化后0的位置
	for(int i=1;i<=n;i++){
		a[i].u=lower_bound(tmp+1,tmp+len+1,a[i].u)-tmp;
		a[i].v=lower_bound(tmp+1,tmp+len+1,a[i].v)-tmp;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].u<k||a[i].v<k) continue;
		dp[i]=query(a[i].v)+1;
		ans=mx(ans,dp[i]);
		add(a[i].v,dp[i]);
		dp[i]=0;
	}
	cout<<ans<<" ";
	ans=0;
	for(int i=1;i<=len;i++){
		c[i]=0;
	}
	for(int i=1;i<=n;i++){
		dp[i]=query(a[i].v)+1;
		ans=mx(ans,dp[i]);
		add(a[i].v,dp[i]);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：是个汉子 (赞：3)

~~调了半天，发现是没开long long~~

### Solution

看这个题的时候，第一想法是按时间排序，然后朴素DP，但这样差不多是 $O(n^2\cdot v)$ 的。

所以我们需要考虑更优的解法。

不难发现，只有当 $i,j$ 两点满足 $|x_i-x_j|\leq |t_i-t_j|\times v$ 时，才可以从一个点到另一个，然后我们尝试去转化这个式子。

当 $t_i\leq t_j$ 时，如果 $x_i\leq x_j$ ， $x_j-x_i\leq t_j\times v-t_i\times v\Rightarrow-x_i+t_i\times v\leq -x_j+t_j\times v$ ，

​						  				   否则 $x_i-x_j\leq t_j\times v-t_i\times v\Rightarrow x_i+t_i\times v\leq x_j+t_j\times v$ 

 $t_i\geq t_j$ 同理，那么我们设 $a_i=x_i+t_i\times v,b_i=-x_i+t_i\times v$ ，可以将上面的式子变成 $a_i\leq a_j,b_i\leq b_j$ ，也就是需要满足这两个条件就可以转移。

然后将 $a$ 排序，就是LIS问题。

对于第一个问题，只要判断一下 $a_i,b_i\geq 0$ 就行了。、

时间复杂度： $O(n\log n)$ ，和普通的LIS问题一样。

### 代码

```c++
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
const int N=1e5+10;
const ll INF=1e12;
struct node{
    ll a,b;
}mt[N];
ll q[N],x[N],t[N],v;
int n,r,ans1,ans2;

inline bool cmp(node a,node b){
    return a.a==b.a?a.b<b.b:a.a<b.a;
}

int find(int l,int r,ll x){
    int res=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(q[mid]>x) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld%lld",&x[i],&t[i]);
    scanf("%lld",&v);
    for(int i=1;i<=n;i++){
        mt[i].a=-x[i]+t[i]*v;
        mt[i].b=x[i]+t[i]*v;
    }
    sort(mt+1,mt+1+n,cmp);
    q[0]=-INF,q[++r]=INF;
    for(int i=1;i<=n;i++){
        int pos=find(0,r,mt[i].b);
        if(q[pos]>mt[i].b) q[pos]=mt[i].b;
        if(pos>=r) q[++r]=INF;
    }
    ans2=r-1;
    q[r=1]=INF;
    for(int i=1;i<=n;i++)
        if(mt[i].a>=0&&mt[i].b>=0){
            int pos=find(0,r,mt[i].b);
            if(q[pos]>mt[i].b) q[pos]=mt[i].b;
            if(pos>=r) q[++r]=INF;
        }
    ans1=r-1;
    printf("%d %d\n",ans1,ans2);
    return 0;
}
```



---

## 作者：RAINBOW_ddd (赞：3)

对于这个题我们首先可以想到一个 $O(n^2)$ 的暴力 dp，遍历 $1$ 到 $n$ 作为右端点，每次枚举左端点转移即可。

dp 方程为 $dp_i=\min\limits_{j\le i}\left\{dp_j\right\}+1$，然后把 $dp_i$ 全部初值赋为 $1$，对于第一个询问加一个 $\lvert t_i-t_j \rvert \times v \ge \lvert x_i-x_j \rvert$ 的判断即可。

因此我们需要考虑如何用**数据结构**优化。

首先我们可以知道对于点 $i$ 和点 $j$ 当且仅当 $\lvert t_i-t_j \rvert \times v \ge \lvert x_i-x_j \rvert$ 的时候才可以进行合法的转移。

那么我们可以先进行**分类讨论**。

令 $t_i<t_j$ 我们考虑从 $i$ 向 $j$ 转移：

- 若 $x_i>x_j$ 时，我们可以得到 $t_i \times v-x_i \ge t_j \times v-x_j$ 的式子。
- 若 $x_i \le x_j$ 时，我们可以得到 $t_i \times v+x_i \ge t_j \times v+x_j$ 的式子。

那么显然我们会想到**二维偏序**，问题就迎刃而解了。

设 $a_i=t_i \times v+x_i$，$b_i=t_i \times v-x_i$ 那么我们假设从 $i$ 转移到 $j$，则必须满足 $a_i\le a_j$，$b_i\le b_j$ 的条件。

至此，我们已经将这道题目转化为一道二维偏序的题目，直接用**树状数组**维护即可，第一种询问判断是否在第一象限，即是否能从状态 $0$ 位置 $0$ 时刻到达。

现在我们先按 $a_i$ 为第一关键字，$b_i$ 为第二关键字排序，建立值域树状数组，每次对 $b_i$ 先查询 $1$ 到 $b_i$ 区间的最大值，加上 $1$ 来更新 $dp_i$，再向 $b_i$ 位置插入 $dp_i$ 的值即可， 注意需要对 $a_i$，$b_i$ 数组离散化处理，同时要注意对第一个询问需要查询原值是否两者都大于 $0$ 即可，还有要开 **long long**。

下面是代码（蒟蒻离散化用的 sort 大佬轻喷）。

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
int N;
long long x[MAXN],t[MAXN],v,cnt1,cnt2,dp[MAXN],S[MAXN],ans=-1;
struct Node{
    long long val,fake_val,cnt;
};
struct eve{
    long long a,b,ta,tb;
}Event[MAXN];
Node E1[MAXN],E2[MAXN];
bool cmp1(Node a,Node b){return a.val<b.val;}
bool cmp2(Node a,Node b){return a.cnt<b.cnt;}
bool cmp3(eve a,eve b){if(a.a==b.a)return a.b<b.b;return a.a<b.a;}
void add(int p,long long x){
    while(p<=N){
        S[p]=max(S[p],x);
        p+=(p&(-p));
    }
}
long long query(int p){
    long long ans=-1;
    while(p){
        ans=max(ans,S[p]);
        p-=(p&(-p));
    }
    return ans;
}
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        scanf("%lld%lld",&x[i],&t[i]);
        dp[i]=1;
    }
    scanf("%lld",&v);
    for(int i=1;i<=N;i++){
        E1[i].cnt=E2[i].cnt=i;
        E1[i].val=t[i]*v-x[i],E2[i].val=t[i]*v+x[i];
    }
    sort(E1+1,E1+N+1,cmp1);
    sort(E2+1,E2+N+1,cmp1);
    for(int i=1;i<=N;i++){
        if(i==1||E1[i].val!=E1[i-1].val)cnt1++;
        if(i==1||E2[i].val!=E2[i-1].val)cnt2++;
        E1[i].fake_val=cnt1;E2[i].fake_val=cnt2;
    }
    for(int i=1;i<=N;i++){
        Event[E1[i].cnt].a=E1[i].fake_val;
        Event[E2[i].cnt].b=E2[i].fake_val;
        Event[E1[i].cnt].ta=E1[i].val;
        Event[E2[i].cnt].tb=E2[i].val;
    }
    sort(Event+1,Event+1+N,cmp3);
    for(int i=1;i<=N;i++){
        if(Event[i].ta<0||Event[i].tb<0)continue;
        dp[i]=query(Event[i].b)+1;
        ans=max(ans,dp[i]);
        add(Event[i].b,dp[i]);
        dp[i]=0;
    }
    cout<<ans<<" ";
    for(int i=1;i<=N;i++)S[i]=0;
    for(int i=1;i<=N;i++){
        dp[i]=query(Event[i].b)+1;
        ans=max(ans,dp[i]);
        add(Event[i].b,dp[i]);
        dp[i]=0;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：FjswYuzu (赞：2)

$\ \ \ \ \ \ \ $同步更新于[动态规划 100 题](https://www.luogu.com.cn/blog/blog10086001/dong-tai-gui-hua-100-ti)第 20 题。

$\ \ \ \ \ \ \ $[luogu](https://www.luogu.com.cn/problem/CF76F)

$\ \ \ \ \ \ \ $不得不说是一道好题。

$\ \ \ \ \ \ \ $考虑到我们将每一个事件按时间排序之后，可以很容易的得到 dp 式。我们从一个点走到另外一个点，dp 值加 1 即可。

$\ \ \ \ \ \ \ $一个点走到另一个点的条件是：$|x_i-x_j| \leq |t_i-t_j| \times v$。从这里怎么下手？ 

$\ \ \ \ \ \ \ $首先说结论，$-x_i+t_i \times v \leq -x_i+t_j \times v \operatorname{and} x_i+t_i \times v \leq x_j+t_j \times v$ 和上面那个式子等价。 

$\ \ \ \ \ \ \ $假设 $t_i \leq t_j$，当 $x_i \geq x_j$ 时，$x_i -x_j \leq (t_j -t_i) \times v$ ，否则 $x_j-x_i \leq (t_j-t_i)\times v$。

$\ \ \ \ \ \ \ $去掉前提。我们假设 $a_i=x_i + t_i \times v,b_i=x_i+t_j \times v$。如果一个点走到另一个点的话，必有 $a_i \leq a_j,b_i \leq b_j$。

$\ \ \ \ \ \ \ $这里没看懂可以在理解一下，是挺麻烦的。

$\ \ \ \ \ \ \ $现在我们得出 $a_i,b_i$ 单调。按 $a_i,b_i$ 排个序，求最长不下降子序列就行了。特殊的，对于第一个问题，我们只需要 $a_i,b_i \geq 0$ 的点就行了。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<iostream>
#include<cstring>
using namespace std;
int x[100005],t[100005],n,v;
struct Point{//Map to an event.
	int x,y;
	bool operator < (Point q) const
	{
		if(x!=q.x)	return x<q.x;
		return y<q.y;
	}
	Point() {}
	Point(int X,int Y){x=X,y=Y;}
}event[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)	cin>>x[i]>>t[i];
	cin>>v;
	int tot=0;
	for(int i=1;i<=n;++i)	if(v*t[i]+x[i]>=0 && v*t[i]-x[i]>=0)	event[++tot]=Point(v*t[i]+x[i],v*t[i]-x[i]);
	sort(event+1,event+1+tot);
	multiset<int> S;
	multiset<int>::iterator Sit;
	for(int i=1;i<=tot;++i)
	{
		Sit=S.upper_bound(event[i].y);
		if(Sit!=S.end())	S.erase(Sit);
		S.insert(event[i].y);
	}
	cout<<S.size()<<' ';
	S.clear();
	for(int i=1;i<=n;++i)	event[i]=Point(v*t[i]+x[i],v*t[i]-x[i]);
	sort(event+1,event+1+n);
	for(int i=1;i<=n;++i)
	{
		Sit=S.upper_bound(event[i].y);
		if(Sit!=S.end())	S.erase(Sit);
		S.insert(event[i].y);
	}
	cout<<S.size()<<endl;
	return 0;
}
``` 

---

## 作者：ZolaWatle (赞：1)

## CF76F 题解

### 题目大意

有一条数轴和在这条数轴上的 $n$ 件事件，每一个事件使用一个二元组 $(x_i, t_i)$ 表示。代表这件事将在第 $t_i$ 秒时于 $x_i$ 处发生。有一个速度 $v$，表示你每一秒可以走 $v$ 个单位长度。需要求：

1. 如果你于 $0$ 时刻在原点出发，
2. 如果你于 $0$ 时刻在任意位置出发，

分别**最多**能经历多少事件。

我们需要注意以下几点：

- **事件瞬间发生**。这意味着要看到事件 $i$，人必须在 $t_i$ 时刻位于 $x_i$ 位置上。如果有多件事情同时于 $t_i$ 时刻发生，我们只能看到其中的一件。（当然，如果多个事件重合那就另当别论）
- **人的移动方向任意**，这意味着在一秒内你不一定只能向正方向或反方向走 $v$ 个单位，你可以中途掉头，甚至反复横跳。
- **题中有两问**，我们应该从这里入手，探究出发点对问题答案的影响。

### 解题思路

由以上，我们把刚刚目睹过事件的点当作出发点。假设当前刚刚目睹完一个事件 $i$，也就是说，我们现在所处的位置是 $x_i$，时间是 $t_i$。那么接下来的事件中，我们有哪些是可以目睹的呢？

假设有一次事件 $j$ 能被我们所经历。显然，$j$ 的发生时间不可能在 $i$ 之前。同时为了方便，我们均不讨论事件重合的情况。那么得到 $t_j>t_i$。我们还应该在事件发生之前赶到那里（如果提前到了就反复横跳）。在 $j$ 发生之前，有 $t_j-t_i$ 的时间空隙可以行动，可以行动的最大路程 $S=v\cdot (t_j-t_i)$。事件 $i$ 和 $j$ 相距 $|x_i-x_j|$，为了看到事件 $j$，我们应该满足 $|x_i-x_j|\leq S$。

我们发现这个不等式的解等价于以下两个不等式的解的交：

$$\begin{cases}
 v\cdot t_i-x_i\leq v\cdot t_j-x_j\\
 v\cdot t_i+x_i\leq v\cdot t_j+x_j
 \end{cases}$$

证明不赘述，初中数学。

细心的读者会发现，将两式相加可以得到 $t_i\leq t_j$，即是我们的先决条件。

我们注意到这两个不等式的形式很特殊，于是构建一组映射：$incident(x_i, t_i) \rightarrow mapping(v\cdot t_i-x_i, v\cdot t_i+x_i)$。设映射中的两个参数为 $k1, k2$。

~~然而本蒟蒻于草吃牛神仙持不同观点，因为我不知道什么是三位偏序，所以我并不觉得这道题很板。~~

这样一来，方法就明了了。对于一组解 $a_1, a_2,..., a_p$，应该满足 $k_{1_{a_p}}\geq k_{1_{a_{p-1}}}$ 且 $k_{2_{a_p}}\geq k_{2_{a_{p-1}}}$。简单来说，就是满足对于两个关键字均单调。显然，$p$ 最大时是最优解，而我们要求的即是这个 $p$。

考虑以 $k_1$ 为关键字进行从小到大排序，再以 $k_2$ 为关键字求一个最长不降子序列即可。由于我们只需要知道其长度，用 $\text{multiset}$ 求解挺香，毕竟常数小嘛。

然而，我们以上考虑的都是**不限制出发点**的情况，解决了第二问。对于第一问，我们要考虑哪些点能由原点直接到达，我们将这些点称作**有效点**。对于一个有效点 $i$，其应满足：$ v\cdot t_i\geq |x_i| $。同样，这个不等式可以等价于这两个不等式的交：

$$\begin{cases}
 v\cdot t_i-x_i\geq 0\\
 v\cdot t_i+x_i\geq 0
 \end{cases}$$

对所有有效点进行同上操作即可解决第一问。

温馨提示：记得开 $\text{long long}$。

### 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#define ll long long
#define re register int
#define rl register ll
using namespace std;

const int N=1e5+1;
int n,cnt,tot;
ll v;
struct incident{ll x,t;}a[N];
struct mapping{ll k1,k2;}m[N],p[N];
multiset <ll> s;
multiset <ll>::iterator it;

inline int rint()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
	return x*f;
}
inline ll rll()
{
	ll x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
	return x*f;
}


inline bool cmp(mapping a,mapping b)
{
	if(a.k1==b.k1)
		return a.k2<b.k2;
	return a.k1<b.k1;
}//以k1为关键字排序 

int main()
{
	n=rint();
	for(re i=1;i<=n;i++)
		a[i]=(incident){rll(),rll()};
	v=rll();
	for(re i=1;i<=n;i++)
	{
		m[i]=(mapping){v*a[i].t-a[i].x,v*a[i].t+a[i].x};  //建立映射 
		if(m[i].k1>=0&&m[i].k2>=0)
			p[++tot]=m[i];  //筛选“有效点” 
	}
	
	sort(p+1,p+tot+1,cmp);
	for(re i=1;i<=tot;i++)
	{
		it=s.upper_bound(p[i].k2);
		if(it!=s.end())
			s.erase(it);
		s.insert(p[i].k2);
	}
	printf("%d ",s.size());  //对第一问求解，最后set的大小即是答案 
	s.clear();
	
	sort(m+1,m+n+1,cmp);
	for(re i=1;i<=n;i++)
	{
		it=s.upper_bound(m[i].k2);
		if(it!=s.end())
			s.erase(it);
		s.insert(m[i].k2);
	}
	printf("%d",s.size());  //对第二问求解，无需考虑“有效点的限制” 
	return 0;
}
```

------------

感谢阅读

---

## 作者：Hoks (赞：0)

## 前言
简单的二维偏序题。

摘自 [杂题选做 Part 4. dp](https://www.luogu.com.cn/training/660942)。
## 思路分析
看到题目肯定先胡一个多项式复杂度做法。

比较容易想到的是按照时间去排序，那么事件就是依次发生的。

此时我们只需要考虑当前在哪个位置能否到达就行了。

设计 $f_i$ 表示**一定要**看到了第 $i$ 个事件，那么能看到的最多事件数。

注意到这里是钦定 $i$ 必须要选上，这样我们就保证了在 $t_i$ 时刻人肯定在 $x_i$ 上，方便转移。

那么我们有转移方程式：
$$f_i=\max\limits_{(t_i-t_j)\cdot v\ge|x_i-x_j|}^{j<i}{f_j}+1$$

其中 $||$ 符号表示绝对值。

但这个方程貌似是不太好优化了，因为每次对于 $i$ 选择 $j$ 的时候我们都需要考虑到 $x,t$ 两个变量的影响。

所以考虑来化开这个式子。

看下我们的限制条件是 $(t_i-t_j)\cdot v\ge|x_i-x_j|$。

比较难处理的是绝对值，而我们又注意到绝对值的本质就是将一个负数的东西取反。

也就是：$|x-y|$ 可以转化为 $\max(x-y,y-x)$。

这点比较显然，绝对值取正的就相当于是我们在正负两个中取大的那个。

那这有什么用呢？

$$(t_i-t_j)\cdot v\ge\max(x_i-x_j,x_j-x_i)$$

这是个不等式，而左半部分大于两数中的较大值，显然也大于其中任何一个数。

所以就变成了：
$$(t_i-t_j)\cdot v\ge x_i-x_j$$
$$(t_i-t_j)\cdot v\ge x_j-x_i$$
考虑到我们是每次对于 $i$ 去选择 $j$，所以这个式子肯定是把相同变量放到一边比较舒服。

然后就可以得到：
$$t_i\cdot v-x_i\ge t_j\cdot v-x_j$$
$$t_i\cdot v+x_i\ge t_j\cdot v+x_j$$
我们不妨通过 $(x_i,t_i)$ 以及常数 $v$ 得到新钦定的点坐标 $(t_i\cdot v-x_i,t_i\cdot v+x_i)$。

那这个问题就变成了一个简单的二维偏序求最长路径问题。

最后我们来考虑第一问。

第一问就是说必须要从点 $(0,0)$ 开始计算最长路径，按照题意再跑一遍 dp 就行了。
## 代码
没搞懂为什么要给第一维也离散化了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=2e6+10,M=1e5+10,V=1e6,lim=19,mod=998244353,INF=0x3f3f3f3f3f3f3f3f;
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]=max(c[x],v);}
    int query(int x){int res=0;for(;x;x-=x&-x) res=max(res,c[x]);return res;}
    void mdf(int l,int r,int v){modify(l,v),modify(r+1,-v);}
    int qry(int l,int r){return query(r)-query(l-1);}
}tt;
int n,m,v,tot=1,a[N],b[N],c[N],f[N];pair<int,int>p[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int get(int x){return lower_bound(c+1,c+1+tot,x)-c;}
inline void solve()
{
	n=read();for(int i=1;i<=n;i++) a[i]=read(),b[i]=read();v=read();
    for(int i=1;i<=n;i++) c[++tot]=b[i]*v+a[i];sort(c+1,c+1+tot);
	tt.n=tot=unique(c+1,c+1+tot)-c-1;int o=get(0);
    for(int i=1;i<=n;i++) p[i]={b[i]*v-a[i],get(b[i]*v+a[i])};sort(p+1,p+1+n);
    for(int i=1;i<=n;i++)
    {
        if(p[i].first<0||p[i].second<o) continue;
        f[i]=tt.query(p[i].second)+1;tt.modify(p[i].second,f[i]);
    }print(*max_element(f+1,f+1+n));put(' ');
    memset(tt.c,0,sizeof tt.c);
    for(int i=1;i<=n;i++)
    {
        f[i]=tt.query(p[i].second)+1;
        tt.modify(p[i].second,f[i]);
    }print(*max_element(f+1,f+1+n));put('\n');
}
signed main()
{
	int T=1;
	//	T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：cqbzlzm (赞：0)

### Description

有一个数轴和 $n$ 个事件，每个事件 $(x_i,t_i)$ 表示第 $i$ 个事件在位置 $x_i$ 处 $t_i$ 时刻发生。你的一秒**最多**走 $V$ 个单位长度。求下面两个问题的答案：

1. 你从 $0$ 位置，$0$ 时刻出发，最多遇见几个事件。

2. 你从任何位置，$0$ 时刻出发，最多遇见几个事件。

**数据规模：**$n\leq 10^5$。

### Solution

先按照时间排序，易得状态转移方程：
$$
dp_i=\min(dp_j+1),\quad(t_i-t_j)\times v\geq |x_i-x_j|
$$
那么我们已经可以写出 $O(n^2)$ 的程序了。

考虑优化，先把绝对值拆开。

1. $x_i-t_i\times V\leq x_j-t_j\times V,\quad x_i\geq x_j$
2. $-x_i-t_i\times V\leq -x_j-t_j\times V,\quad x_i< x_j$

我们发现，如果 $i$ 可以转移到 $j$，那么一定会**同时**满足上述的两个条件。那么问题就转换成了二位偏序的问题，用树状数组维护即可（类似 LIS）。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;
int n, v;
int x[MAXN + 5], t[MAXN + 5];
struct node {
    int a, b;
} a[MAXN + 5];
int re[MAXN * 2 + 5], m;
int tr[MAXN * 2 + 5];
int lowbit(int i) {return i & (-i);}
void modify(int i, int x) {
    for (; i <= m; i += lowbit(i)) tr[i] = max(tr[i], x);
    return ;
}
int query(int i) {
    int ans = 0;
    for (; i; i -= lowbit(i)) ans = max(ans, tr[i]);
    return ans;
}
int dp[MAXN + 5];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++)
        scanf("%d%d", &x[i], &t[i]);
    scanf("%d", &v);
    for (int i = 1; i <= n; i ++) {
        a[i].a = x[i] - t[i] * v;
        a[i].b = -x[i] - t[i] * v;
        re[++ m] = a[i].a;
        re[++ m] = a[i].b;
    }
    sort(re + 1, re + 1 + m); m = unique(re + 1, re + 1 + m) - re - 1;
    for (int i = 1; i <= n; i ++) {
        a[i].a = lower_bound(re + 1, re + 1 + m, a[i].a) - re;
        a[i].b = lower_bound(re + 1, re + 1 + m, a[i].b) - re;
    }
    sort(a + 1, a + 1 + n, [](node a, node b){return a.a < b.a || a.a == b.a && a.b < b.b;});
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        if (re[a[i].a] > 0 || re[a[i].b] > 0) continue;
        int x = query(a[i].b);
        modify(a[i].b, x + 1);
        ans = max(ans, x + 1);
    }
    printf("%d ", ans);
    memset(tr, 0, sizeof(tr));
    ans = 0;
    for (int i = 1; i <= n; i ++) {
        int x = query(a[i].b);
        modify(a[i].b, x + 1);
        ans = max(ans, x + 1);
    }
    printf("%d ", ans);
    return 0;
}
```

---

## 作者：Forg1weN (赞：0)

题意省略。

首先有个前提，转移必须是要满足 $t_i\le t_j$ 的。

于是列出一下方程：$ |x_i-x_j|\le (t_j-t_i)\times V$，这里默认是 从 $i$ 走到 $j$。

于是就解出一下两组解：

$ \begin {cases} -x_i+t_i\times V\le -x_j+t_j\times V \\ x_i+t_i\times V\le x_j +t_j\times V\end {cases}$

按理来说方程式解集求并集，这里两种情况分别对应着 $x_i$ 和 $x_j$ 的大小关系，两者应该是不相互影响的，**很多题解都没有说明白为什么求交集**。

考虑针对 $x_i\le x_j$ 的情况，若只满足第一个不等式，则无法推出 $t_i\le t_j$ 的前提条件，所以这里不是并集，而是交集。

记 $a_i=-x_i+t_i\times V,b_i=x_i+t_i\times V$，所以求满足 $a_i\le a_j$ 且 $b_i\le b_j$ 的条件最多的事件个数，转化为最长上升子序列问题。

那么对于 $0$ 时刻 $0$ 位置出发的话，考虑代入方程，发现 $a_j,b_j$ 一定大于 $0$ ，且由于是上升的序列，小于 $0$ 的一定没有贡献，于是在离散化数组中小于 $0$ 的坐标直接舍弃即可。

时间复杂度 $O(n\log n)$。

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2300}$
---
### 解题思路：

考虑朴素的思路，将所有的事件按照时间排序，$f_i$ 表示强制看到第 $i$ 个事件能看到的最多事件数量。转移的条件就是 $|x_i-x_j|\le (t_i-t_j)\times v$。复杂度 $O(n^2)$。

把绝对值符号拆开，得到 $x_i-x_j\le (t_i-t_j)\times v$ 且 $x_j-x_i\le (t_i-t_j)\times v$。移项得到 $t_i\times v-x_i\ge t_j\times v -x_j$ 且 $t_i\times v+x_i\ge t_j\times v +x_j$。

此时如果令 $t_i\times v-x_i=a_i$，$t_i\times v+x_i=b_i$，能够完成转移的条件就是 $a_i\ge a_j$ 且 $b_i\ge b_j$，也就是一个二维偏序问题。

至于题目中给出的两个限制条件，明显就是 $f$ 的初值问题，处理的时候注意一下就行。复杂度 $O(n\log n)$。

---
注意排序的时候 $a$ 相同要按照 $b$ 排序。

---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=200005;
struct str{
	int a,b,init;
	bool operator < (str x){
		if(a==x.a)return b<x.b;
		return a<x.a;
	}
}p[MAXN];
int n,v,x[MAXN],t[MAXN],f[MAXN],d[MAXN],cnt,maxn;
void init(){
	memset(f,0,sizeof(f));
	memset(d,0,sizeof(d));
	cnt=0;maxn=0;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&x[i],&t[i]);
	scanf("%lld",&v);
	for(int i=1;i<=n;i++){
		p[i].a=t[i]*v+x[i];
		p[i].b=t[i]*v-x[i];
		p[i].init=(p[i].a>=0)&&(p[i].b>=0);
	}
	sort(p+1,p+n+1);
	d[0]=-1e15;
	for(int i=1;i<=n;i++){
		if(p[i].init==0)continue;
		if(p[i].b>=d[cnt])d[++cnt]=p[i].b;
		else{
			int now=upper_bound(d+1,d+cnt+1,p[i].b)-d;
			d[now]=p[i].b;
		}
	}
	printf("%lld ",cnt);
	init();
	d[0]=-1e12;
	for(int i=1;i<=n;i++){
		if(p[i].b>=d[cnt])d[++cnt]=p[i].b;
		else{
			int now=upper_bound(d+1,d+cnt+1,p[i].b)-d;
			d[now]=p[i].b;
		}
	}
	printf("%lld\n",cnt);
	return 0;
}
```



---

## 作者：Elma_ (赞：0)

考虑 dp。设 $f_i$ 为看到第 $i$ 个事件，之前看到的最多事件数目。显然有 $f_i=\max\{f_j\} + 1$，其中 $j$ 需要满足：

$$\frac{|x_i-x_j|}{(t_i-t_j)} \leq v$$

也就是：

$$|x_i-x_j| \leq v \times (t_j-t_i)$$

注意这里的 $t_j-t_i$ 其实并不需要加绝对值，因为时间并不会倒流，因此能从 $j$ 走到 $i$ 其实就已经保证了 $t_i \leq t_j$。然后我们分类讨论一下：

- 若 $x_i \leq x_j$，则：
$$(x_j-x_i) \leq v \times (t_j-t_i)$$

拆开得到：

$$-x_i + v \times t_i \leq -x_j + v \times t_j$$

- 若 $x_i > x_j$，则：

$$(x_i-x_j) \leq v \times (t_j-t_i)$$

拆开得到：

$$x_i + v \times t_i \leq x_j + v \times t_j$$

于是我们设 $a_i=-x_i + v \times t_i$，$b_i=x_i + v \times t_i$，那么能从 $j$ 转移到 $i$ 当且权当 $a_i \leq a_j$ 且 $b_i \leq b_j$。把 $(a_i,b_i)$ 看做一个点，那么可以发现这其实是一个二维偏序的形式，我们对 $a$ 排序，对 $b$ 这一维求一边 $\mathrm{LIS}$ 即可。

对于第一问，因为只能从原点出发，因此一个点可能到达当且权当 $v \times t_i \geq |x_i|$。拆开得到：

$$
\begin{cases}
v \times t_i - x_i \geq 0\\
v \times t_i + x_i \geq 0
\end{cases}
$$

其实也就是 $a_i,b_i\geq 0$，因此我们把所有在第一象限的点抽出来再做一遍就行了。时间复杂度 $O(n \log n)$。

```cpp
#include <set>
#include <ctime>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 1e5 + 5;
const int mod = 998244353;
const int inf = 1e9;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

struct node {
    int x, y;
    bool operator < (node q) {
        return x == q.x ? y < q.y : x < q.x;
    }
} a[maxn];
int n, v, tot, x[maxn], t[maxn];
multiset<int> s;
multiset<int> :: iterator it;

signed main(void) { 
    n = read();
    for (int i = 1;i <= n;i++) x[i] = read(), t[i] = read();
    v = read();
    for (int i = 1;i <= n;i++) {
        if (v * t[i] + x[i] >= 0 && v * t[i] - x[i] >= 0) {
            a[++tot] = (node){v * t[i] + x[i], v * t[i] - x[i]};
        }
    }
    sort(a + 1, a + tot + 1);
    for (int i = 1;i <= tot;i++) {
        it = s.upper_bound(a[i].y);
        if (it != s.end()) s.erase(it);
        s.insert(a[i].y);
    }
    printf("%d ", s.size());
    s.clear();
    for (int i = 1;i <= n;i++) {
        a[i] = (node){v * t[i] + x[i], v * t[i] - x[i]};
    }
    sort(a + 1, a + n + 1);
    for (int i = 1;i <= n;i++) {
        it = s.upper_bound(a[i].y);
        if (it != s.end()) s.erase(it);
        s.insert(a[i].y);
    }
    printf("%d\n", s.size());
    return 0; 
}
```


---

