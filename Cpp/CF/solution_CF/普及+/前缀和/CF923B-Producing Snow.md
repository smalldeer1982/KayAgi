# Producing Snow

## 题目描述

Alice非常喜欢雪！

她每天都会堆一堆$V$  升的雪，然而每堆雪每天都会融化$T$  升，当然，要是这堆雪的体积$V<=0$  时，它就永远消失了。

现在她想知道，$n$  天中每天融化了多少升雪呢？

## 样例 #1

### 输入

```
3
10 10 5
5 7 2
```

### 输出

```
5 12 4
```

## 样例 #2

### 输入

```
5
30 25 20 15 10
9 10 12 4 13
```

### 输出

```
9 20 35 11 25
```

# 题解

## 作者：cherry2010 (赞：6)

# CF923B Producing Snow 题解

## 一.注意事项

第三行输入的是：

#### 每天每堆雪

熔化的体积！！

## 二.解题思路

### 1.暴力

暴力枚举每天有哪几堆雪会熔化，但这样做会超时。

### 2.小根堆+前缀和

##### 计算前 $i$ 天熔化雪量的前缀和，将新增的雪堆的雪量加入到优先队列中

当循环到第 $i$ 天时:（记 $sum_{i}$ 为前 $i$ 天熔化雪量的前缀和，$ans$ 为第 $i$ 天雪总共的熔化量）。

当优先队列中的元素小于 $sum_{i}$ 时，说明该元素无法承受到第 $i$ 天的熔化量，否则就可以承受。

如果不能承受，$ans$ 加上该雪堆第 $i$ 天时的体积，并将该雪堆从队列中取出。

将所有不能承受熔化的雪堆从队列中取出后，（$ans$ 加上以承受熔化的雪堆的数量）$\times$（第 $i$ 天每堆雪熔化的体积）。

$Q:$ 如何计算一个雪堆第 $i$ 天时的体积？（假设这个雪堆在第 $x$ 天堆出来）

$A:$ 可以考虑用该雪堆最开始的体积减去 $sum_{i-1}$，但是这样的话就会多减 $sum_{x-1}$，所以我们可以在这堆雪加入优先队列时就将这堆雪的总量加上 $sum_{x-1}$。

## 三.代码

```c++
#include <bits/stdc++.h>
using namespace std;
int n,x;
long long ans;  //注意计算前缀和要开long long
int a[100010];
long long sum[100010];
priority_queue<long long,vector<long long>,greater<long long> > q;//小根堆(优先队列）
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		ans=0; //记录雪总共的熔化量
		sum[i]=sum[i-1]+x;  //前i天熔化雪量的前缀和
		q.push(a[i]+sum[i-1]);  //将这堆雪的总量加上sum[x-1]
		while(!q.empty()&&q.top()<=sum[i])  //判断是否可以承受熔化
		{
			ans+=q.top()-sum[i-1];  //不能承受就熔化第i天的体积
			q.pop(); //从队列中取出
		}
		ans+=x*q.size();  //当天的熔化量*可以承受熔化的雪堆数量
		printf("%lld ",ans);
	}
	
	return 0;
}
```

---

## 作者：CaiXY06 (赞：2)

我们考虑**前缀和**以及**二分**。

我们先给 $T_i$ 做一套前缀和，前缀和数组为 $S_i$。

我们再假设每一堆雪在第 $0$ 天就已堆好，在第 $i$ 天刚好融化成 $V_i$，那么这堆雪的初始体积很显然就是 $V_i+S_{i-1}$。

我们再把初始体积 $V_i+S_{i-1}$ 在 $S$ 中二分出刚好融化完的位置，设为 $j(j\leq i\leq n)$。

我们对于每一天都维护两个值，这刚好一天融化完的雪堆的数量，和刚好这天融化完的雪堆所产生的贡献（因为可能取不满当天融化量），分别设为 $finish_i$ 和 $rest_i$。可以对 $finish$ 做一个前缀和，这样就可以轻松得到当天没融化完的雪堆数量，即 $i-finish_i$。

那么每一天的融化量就是 $T_i\times (i-finish_i)+rest_i$（没化完的贡献+化完的贡献）。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;//前缀和以及计算贡献会爆int
int n,V[100010],T[100010],finish,f[100010],rest[100010];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&V[i]);
	for(int i=1,x;i<=n;i++)scanf("%lld",&x),T[i]=T[i-1]+x;//前缀和
	for(int i=1;i<=n;i++){
		int j=lower_bound(T+i,T+n+1,T[i-1]+V[i])-T;//二分
		f[j]++;rest[j]+=V[i]+T[i-1]-T[j-1];finish+=f[i];//更新融化完的那天的权值，以及化完的数量
		printf("%lld ",(T[i]-T[i-1])*(i-finish)+rest[i]);//计算贡献
	}
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：2)

emmmm fhq treap板子，可并堆板子。 并不怎么想思考

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1e5+5;
int cnt,n,b[N],c[N];
inline void init(){
	n=read();
	for (int i=1;i<=n;i++) b[i]=read();
	for (int i=1;i<=n;i++) c[i]=read();
}
struct node{
	int sz,sum,dec,V,v,son[2];
}a[N];
inline void plu(int k,int v) {
	if (!k) return;
	a[k].v-=v; a[k].dec+=v; a[k].sum-=v*a[k].sz;
} 
inline void pushup(int k){
	if (!k) return;
	a[k].sz=a[a[k].son[0]].sz+a[a[k].son[1]].sz+1;
	a[k].sum=a[a[k].son[0]].sum+a[a[k].son[1]].sum+a[k].v;
}
inline void pushdown(int k){
	if (a[k].dec) {
		plu(a[k].son[0],a[k].dec);
		plu(a[k].son[1],a[k].dec);
		a[k].dec=0;
	}
}
int merge(int x,int y){  
	if (!x||!y) return x+y;
	pushdown(x); pushdown(y);
	if (a[x].V<a[y].V) {
		a[x].son[1]=merge(a[x].son[1],y);
		pushup(x);
		return x;
	}else{
		a[y].son[0]=merge(x,a[y].son[0]);
		pushup(y);
		return y;
	}
}
void split(int k,int rk,int &x,int &y){
	if (!k) x=y=0;
		else {
			pushdown(k);
			if (a[k].v<=rk) x=k,split(a[k].son[1],rk,a[x].son[1],y); 
				else y=k,split(a[k].son[0],rk,x,a[y].son[0]);
			pushup(k);
		}
}
inline int newnode(int v){
	a[++cnt].v=v; a[cnt].V=rand(); a[cnt].sz=1; a[cnt].sum=v; return cnt;
}
int root;
inline void solve(){
	for (int i=1;i<=n;i++){
		int A,B; 
		split(root,b[i],A,B);
		root=merge(merge(A,newnode(b[i])),B);
		split(root,c[i],A,B);
		write(a[A].sum+c[i]*a[B].sz); putchar(' ');
		if (B) plu(B,c[i]);
		root=B;
	}
}
signed main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：TheShadow (赞：2)

# 这是一道水题！！！！
### 心酸历程
- 我看到这道题的是时候第一反应是这题能有蓝题？？于是我信心满满的想用**雪的体积**的前缀和切掉这道题，然后。。。。。。我忘了每天的雪剩的不一样啊，所以十分果断的WA掉了。。

- 但我是一个~~表面~~坚持的人，所以我怎么能这么轻易就放弃呢？？~~不然呢？~~
- 所以我决定继续肝题，而且一定要用前缀和做！！！

- 刚刚说了，用**雪的体积**的前缀和会炸，所以还剩下的就只有每天的**融雪量**了，所以，开搞吧！！
### 解题思路
- 既然说了要用前缀和，那肯定的，先把*Sum*数组求出来啊，然后我们就可以开始~~水题了~~。

- 既然我们求的是**融雪量**的前缀和，那么解题肯定是要用到它的，至于怎么用，经过我们一番思考~~乱搞~~，我们可以把每一堆雪自身的体积加上它出现的前一天的前缀和相加$$V[i]+Sum[i-1]$$因为是第*i*天才出现的这堆雪，所以我们应该在第*i*天才将它加入我们计算的队列中。（其实这步操作就相当于是把这堆雪看成是在第一天出现的）
- 这时候有些小伙伴应该已经知道该怎么搞了吧？？

- 没错，我们只需要在每一天的时候都做一个比较，将 <= *Sum[i]* 的取出，用它减去前一天的融雪量得到的就是这堆雪在今天剩的~~那么可怜巴巴的~~一点的量对于答案的贡献$$ans+=	V-Sum[i-1]$$当然，太少了，~~灭口吧~~。
- 你问那些雪还足够多的？？那就把它们留下，留给以后的来处理吧。

- 这里还有一个小技巧，我们可以将每天加入的雪（处理过后的），加入到一个小根堆里面，这样就避免的每次的遍历，可以省很多的事。
- 差不多就这样吧，上代码，还有什么不太清楚，我在代码里面尽量写明：
```cpp
#include<set>
#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
#define it inline int
#define rl register ll
#define il inline void
#define ri register int
#define clean(a,i) memset(a,i,sizeof(a))
#define MAXN 100005
using namespace std;
template<class T>il read(T &x)
{
    int f=1;char k=getchar();x=0;
    for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
    for(;k>='0'&&k<='9';k=getchar()) x=x*10+k-'0';
    x*=f;
}//读入优化
priority_queue<ll,vector<ll>,greater<ll> > s;//用来维护答案的那个小根堆，但注意要用long long来存，不然会炸
int n,tot,v[MAXN],t[MAXN];
ll sum[MAXN];
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    read(n);
    for(ri i=1;i<=n;i++)
        read(v[i]);//读入体积
    for(ri i=1;i<=n;i++)
    {
        read(t[i]);//读入融雪量
        sum[i]=sum[i-1]+t[i];//计算前缀和
    }
    for(ri i=1;i<=n;i++)
    {
        ll ans=0;//答案清零
        s.push(v[i]+sum[i-1]);//将今天的那一堆雪放入小根堆里
        while(!s.empty()&&s.top()<=sum[i])
            ans+=s.top()-sum[i-1],s.pop();//处理掉那些不够交钱的:)
        ans+=t[i]*s.size();//里面还留下的个数就是交的起钱的良民
        printf("%lld ",ans);//输出
    }
    return 0;
}
```
- ps：最下面那位大佬的题解有点小问题，不能用set来存，因为set虽然也能排序，但是会自动去除掉重复的部分，会导致答案有问题。
- 例如：
#### input：10 5 5 //体积 5 7 2//融雪量
#### output：5 10 2
- 这组数据就会出问题，因为有两个10分别在第一、第二次加了进来。

- 最后附上题目链接
[戳这里](https://www.luogu.org/problemnew/show/CF923B)

---

## 作者：lihongqian__int128 (赞：0)

# CF923B Producing Snow题解
看到这题，明显暴力会超时，考虑换一种做法。

想到使用小根堆，将堆里不足总融化雪量的单独计算，剩余的按当天雪的融化量计算。

但我们发现，后面堆的雪在前几天时不会融化的，容易想到，我们可以将后面堆的雪先加上原来雪的融化总量再放入堆中，这样就可以加减抵消，不会少算。

时间复杂度：$\Theta(N\log N)$

代码：
```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std ;
int n , v[100005] , t[100005] , sum ;
priority_queue <int , vector <int> , greater <int> > q ;
signed main()
{
    cin >> n ;
    for(int i = 1 ; i <= n ; i++)
        cin >> v[i] ;
    for(int i = 1 ; i <= n ; i++)
        cin >> t[i] ;
    for(int i = 1 ; i <= n ; i++)
    {
        q.push(v[i] + sum) ;//将当天堆的雪加上之前融化的雪量放入堆中
        int ans = 0 ;
        while(!q.empty() && q.top() <= sum + t[i])    
        {
            ans += q.top() - sum ;//将不足总融化雪量的雪堆单独计算
            q.pop() ;
        }
        ans += t[i] * q.size() ;
        cout << ans << " " ;
        sum += t[i] ;
    }
    return 0 ;
}
```

---

## 作者：fls233666 (赞：0)

如果直接暴力维护每天每堆雪的融化情况来计算每天的答案，好像有点难做，而且超时的可能性也大......

这时候不妨换一个角度思考：**分别考虑每堆雪对每一天答案的影响。**

从这个思路出发分析样例会发现，**对于一堆第 $i$ 天堆起来的雪，它能影响到的答案是一段以 $i$ 为起点的连续区间。**

如果直接根据每天雪的融化情况暴力进行区间修改，复杂度还是很劣。这时候就会想到，能不能把区间修改转化成单点修改呢？于是 **差分+前缀和** 的组合就呼之欲出了。

那么具体怎么差分呢，我们通过下面一张图来描述一下：

![Pic](https://cdn.luogu.com.cn/upload/image_hosting/lx6vmp5u.png)

我们假设第 $i$ 天产生了一堆新的雪，这堆雪到第 $j$ 天才完全融化。

由于每天每堆雪的融化上限是 $T$，所以，对于 $[i,j-1]$ 这段时间里，每天这堆雪都能对当天的答案产生 $T$ 的贡献。而对于第 $j$ 天，雪剩下的体积可能不足以到达融化上限，这时候就要单独计算。

而对于 $[i,j-1]$ 这段，我们可以记 $cnt_i$ 为第 $i$ 天能到达融化上限 $T_i$ 的雪堆的个数。那么，从第 $i$ 天到第 $j-1$ 天的 $cnt$ 值都需要 $+1$。这时候可以用差分转化为 $cnt_i+1$ 和 $cnt_j-1$ 两次单点修改，在全部修改操作都完成后对 $cnt$ 求前缀和即可。

-----

那么还剩下最后一个问题：**如何确定某堆雪到哪一天才会融化？**

我们假设这堆雪在第 $x$ 天形成，体积为 $V_x$。

那么我们希望找到一个 $p$，到第 $p$ 天的时候雪完全融化。我们发现，$p$ 和 $x$ 之间存在如下关系

$$
\sum ^p_{i=x}{T_i} \ge V_x
$$

我们对 $T$ 做前缀和，记为 $S$，于是上式可以转化为：

$$
S_p - S_{x-1} \ge V_x
$$

移项我们可以得到 $S_p \ge V_x + S_{x-1}$ ,考虑到求完前缀和后 $S$ 是递增的，我们可以用**二分查找**来确定 $p$，进而我们就确定了雪会在哪一天完全融化了。

于是这题到这里就完全做完了。

---------

代码部分：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;

const int mxn = 1e5+5;

int n;
ll vn[mxn],tn[mxn],st[mxn],ans[mxn],cnt[mxn];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&vn[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&tn[i]);
    }  //数据输入
    
    for(int i=1;i<=n;i++){
        st[i]=st[i-1]+tn[i];
    }  //对T前缀和
    for(int p,i=1;i<=n;i++){
        if(st[n]<=st[i-1]+vn[i]){  //雪到第 n 天没有融化完或者正好融化完，这时候差分的右端点-1的操作就不需要了
            cnt[i]++;
        }else{  //否则二分确定 p 的位置进行差分
            p=lower_bound(st+1,st+1+n,st[i-1]+vn[i])-st;
            cnt[i]++;
            cnt[p]--;  //差分
            ans[p]+=vn[i]-(st[p-1]-st[i-1]);  //不满上限的那一天额外计算
        }
    }
    for(int i=1;i<=n;i++){
        cnt[i]+=cnt[i-1];  //对cnt求前缀和
        ans[i]+=cnt[i]*tn[i];  //计算答案
        printf("%lld ",ans[i]);  //输出
    }
    return 0;
}
```


---

## 作者：sjr3065335594 (赞：0)

## 题意简述

每天堆一堆体积 $v_i$ 的雪，且所有雪堆各融化 $t_i$，如果雪堆体积小于等于零则消失，求每天融化总量。

## 思路

如果知道每一堆雪是在第 $l$ 到 $r$ 天内没有被融化，那么会给 $[l,r]$ 中每个 $i$ 做 $t_i$ 的贡献，也就是只需要统计每个 $t_i$ 被计算了多少次，直接相乘就可以算出每天的融化总量，当然也会有一些雪堆在第 $r+1$ 天被融化掉剩余的不足 $t_{r+1}$ 的部分，需要加上。

要求出每一堆雪在哪些天里没有融化，由于这堆雪在第 $k$ 天融化了，那么肯定在第 $k+1$ 天也是融化的，考虑进行二分。

对 $t$ 数组进行前缀和，如果 $sum_{mid}-sum_{i-1}\geqslant v_i$，说明在第 $mid$ 天已经融化，否则还没有融化。

求出哪一天被融化之后，再将剩余的部分加到这一天上即可，时间复杂度 $O(n\log n)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp(x,y) make_pair(x,y)
#define CLR(a,x) memset(a,x,sizeof(a))
#define int long long
//#define int __int128
using namespace std;
const int N=1e5+5;
const int M=1e6+5;
const int INF=2e9+5;
int n,v[N],t[N],sum[N],las[N],c[N],ans[N];
signed main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&v[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&t[i]);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+t[i];
	for(int i=1;i<=n;i++) {
		int l=i,r=n,res=n+1;
		while(l<=r) {
			int mid=l+r>>1;
			if(sum[mid]-sum[i-1]>=v[i])r=mid-1,res=mid;
			else l=mid+1;
		}
		res--;
		c[i]++,c[res+1]--;
		ans[res+1]+=v[i]-(sum[res]-sum[i-1]);
	}
	for(int i=1;i<=n;i++)
		c[i]+=c[i-1];
	for(int i=1;i<=n;i++)
		printf("%lld ",c[i]*t[i]+ans[i]);
	return 0;
}
```


---

## 作者：happybob (赞：0)

听说赛前写题解可以 rp++。

我们需要求每天融化总数，但直接求并不容易，考虑求每一堆的起始时间到结束时间，那么这一区间内每一天都应该贡献 $+1$，**注意每个区间的最后一天可能融化不满**。

考虑对于每个数二分加前缀和找到终止天数，然后使用线段树区间 $+1$，特判最后一个数即可，时间复杂度 $O(n \log n)$。

注意贡献 $+1$ 指这一天的融化和 $+t_i$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

#define int long long

const int N = 1e5 + 5;

int n, a[N], b[N], c[N], s[N], f[N], ext[N];

class SegmentTree
{
public:
	struct Node
	{
		int l, r, sum, add;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
	}
	void pushdown(int u)
	{
		Node& rt = tr[u], & lf = tr[u << 1], & rit = tr[u << 1 | 1];
		if (rt.add)
		{
			lf.add += rt.add;
			lf.sum += (lf.r - lf.l + 1) * rt.add;
			rit.add += rt.add;
			rit.sum += (rit.r - rit.l + 1) * rt.add;
			rt.add = 0;
		}
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 0, 0 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update(int u, int l, int r, int p)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			tr[u].add += p;
			tr[u].sum += (tr[u].r - tr[u].l + 1) * p;
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r, p);
		if (r > mid) update(u << 1 | 1, l, r, p);
		pushup(u);
	}
	int query(int u, int x)
	{
		if (tr[u].l == tr[u].r) return tr[u].sum;
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) return query(u << 1, x);
		return query(u << 1 | 1, x);
	}
}t;

signed main()
{
	scanf("%lld", &n);
	t.build(1, 1, n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &b[i]);
		s[i] = s[i - 1] + b[i];
	}
	for (int i = 1; i <= n; i++)
	{
		c[i] = i;
		if (a[i] <= b[i])
		{
			ext[i] += a[i];
			continue;
		}
		int l = i, r = n + 1;
		while (l + 1 < r)
		{
			int mid = l + r >> 1;
			if (s[mid] - s[i - 1] >= a[i]) r = mid;
			else l = mid;
		}
		c[i] = min(r, n);
		t.update(1, i, c[i], 1);
		if (s[r] - s[i - 1] >= a[i])
		{
			f[r] += b[r] - (a[i] - (s[r - 1] - s[i - 1]));
		}
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%lld ", b[i] * t.query(1, i) - f[i] + ext[i]);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：Sasiyar (赞：0)

使用的算法：前缀和、差分。先维护融化量的前缀和数组，所以在计算每一堆雪的融化所用的天数的时候，就可以二分查找出它最后融化的天数pos,相当于第i天到第pos-1天都会增加一个单位该天的融化量，所以使用差分维护，而如果某一天雪融化完而实际剩余的雪不足该天的融化量，就将其维护到other数组中，最后输出答案时稍加计算即可。
```cpp
#include<cstring>
#include<cstdio>
#include<iostream>
#include<windows.h>
#include<cmath>
#include<algorithm>
#include<utility>
#include<limits.h>
#include<map>
#include<queue>
#define R register
#define rint R int
#define ll long long
#define I inline
#define iint I int
#define ivoid I void
#define int void
#define ill I ll
#define maxn 100500
using namespace std;
ll n; 
ll vol[maxn],tem[maxn];
ll tem_sum[maxn];
ll cf[maxn],other[maxn];
ll acfind(ll k)
{
    ll aim=vol[k];
    ll l=k,r=n+1;
    while(l<r)
    {
        ll mid=(l+r)/2;
        if(tem_sum[mid]-tem_sum[k-1]>aim)
            r=mid;
        else
            l=mid+1;
    }
    return l;
}
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++)
        scanf("%lld",&vol[i]);
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&tem[i]);
        tem_sum[i]=tem_sum[i-1]+tem[i];
    }
    tem_sum[n+1]=9223372036854775807LL;tem[n+1]=9223372036854775807LL;
    for(ll i=1;i<=n;i++)
    {
        ll pos=acfind(i);
        cf[i]++;
        cf[pos]--;
        other[pos]+=vol[i]-(tem_sum[pos-1]-tem_sum[i-1]);
    }
    ll res=0;
    for(ll i=1;i<=n;i++)
    {
        res+=cf[i];
        printf("%lld ",res*tem[i]+other[i]);
    }
    return 1;
}

```

---

## 作者：Playnext (赞：0)

~~来发个我的心酸历程....~~

------------

看到题目，感觉是区间更新与区间查询，先查询区间的和，再减掉，再查询一次和，两次的查询和之差即为熔化量。

先上代码：

```cpp
struct SegmentTree{
    long long val[kmax_num << 2], maxn[kmax_num << 2];

    #define lson (root << 1)
    #define rson ((root << 1) | 1)

    inline void PushUp(REG int root)	{
        val[root] = val[lson] + val[rson];
        maxn[root] = std::max(val[lson], val[rson]);
        return ;
    }

    inline void Build(REG int root, REG int begin, REG int end)	{
        if(begin == end)	{
            AIOS::file_input >> val[root];
            maxn[root] = val[root];
            return ;
        }
        else	{
            REG int mid = (begin + end) >> 1;
            Build(lson, begin, mid);
            Build(rson, mid + 1, end);
            PushUp(root);
            return ;
        }
    }

    inline void Update(REG int root, REG int begin, REG int end, REG int udp_begin, REG int udp_end, REG long long num)	{
        if(maxn[root] == 0)	{	
            //我还以为这个蜜汁剪枝能快点的
            return ;	            
        }
        else	if(begin == end)	{
            REG long long change = val[root] - num;
            if(change < 0)	change = 0;
            maxn[root] = val[root] = change;
            //要是更新后的值小于0，就改为0
            return ;
        }
        else	{
            REG int mid = (begin + end) >> 1;
            if(udp_begin <= mid)  Update(lson, begin, mid, udp_begin, udp_end, num);
            if(udp_end > mid)     Update(rson, mid + 1, end, udp_begin, udp_end, num);
            PushUp(root);
            return ;
        }
    }

    inline long long Query(REG int root, REG int begin, REG int end, REG int que_begin, REG int que_end)	{
        if(begin >= que_begin && end <= que_end)	{
            return val[root];
        }
        else	{
            REG int mid = (begin + end) >> 1;
            REG long long ans = 0;
            if(que_begin <= mid)  ans += Query(lson, begin, mid, que_begin, que_end);
            if(que_end > mid)     ans += Query(rson, mid + 1, end, que_begin, que_end);
            return ans;
        }
    }

    #undef lson
    #undef rson
}	segment_tree;
```

------------

然后......

稳稳的T了。

后来才想到Update操作最差会被卡成$O(n)$。

------------

好了，现在讲正解。

维护前缀和$pre_{n} = pre_{n-1} + T_{n}$，我们可以把$V_{n}$看作在第一天出现，此时它的值应改为$V_{n} + pre_{n-1}$。

用$set$维护，因为$set$内部是有序的，所以可以直接用$.begin()$获取最小值，若最小值比$pre_{n}$小，答案就加上$.begin() - pre_{n01}$并删除那个值，最后答案加上$set.size() * T_{n}$就行了。

代码如下：

```cpp
#include <bits/stdc++.h>
#define REG register
#define IN inline
#define For(x,y,z) for (REG int (x) = (y); (x) <= (z); ++(x))
#define FOR(x,y,z) for (REG int (x) = (y); (x) <  (z); ++(x))
const int kmax_num = 1e3 + 10, kmax_int = 2147483647, kmod = 1e9+7;

int v[kmax_num], t[kmax_num];
long long pre[kmax_num];

std::multiset<long long>	mset;

int main() {
//	freopen("G:\\Data\\eclipse-workspace\\IO\\Input\\Input.txt", "r", stdin);
//	freopen("G:\\Data\\eclipse-workspace\\IO\\Output\\Output.txt", "w",stdout);
    REG int n;
    std::cin >> n;
    For(i,1,n)	std::cin >> v[i];
    For(i,1,n)	std::cin >> t[i], pre[i] = pre[i-1] + t[i];

    For(i,1,n)	{
        REG long long ans = 0;
        mset.insert(v[i] + pre[i-1]);
        while(!mset.empty() && *mset.begin() <= pre[i])
            ans += *mset.begin() - pre[i-1], mset.erase(mset.begin());
        ans += t[i] * mset.size();
        printf("%I64d\n", ans);
    }
    return 0;
}
```

---

