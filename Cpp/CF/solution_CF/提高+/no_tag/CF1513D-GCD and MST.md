# GCD and MST

## 题目描述

You are given an array $ a $ of $ n $ ( $ n \geq 2 $ ) positive integers and an integer $ p $ . Consider an undirected weighted graph of $ n $ vertices numbered from $ 1 $ to $ n $ for which the edges between the vertices $ i $ and $ j $ ( $ i<j $ ) are added in the following manner:

- If $ gcd(a_i, a_{i+1}, a_{i+2}, \dots, a_{j}) = min(a_i, a_{i+1}, a_{i+2}, \dots, a_j) $ , then there is an edge of weight $ min(a_i, a_{i+1}, a_{i+2}, \dots, a_j) $ between $ i $ and $ j $ .
- If $ i+1=j $ , then there is an edge of weight $ p $ between $ i $ and $ j $ .

Here $ gcd(x, y, \ldots) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ , $ y $ , ....

Note that there could be multiple edges between $ i $ and $ j $ if both of the above conditions are true, and if both the conditions fail for $ i $ and $ j $ , then there is no edge between these vertices.

The goal is to find the weight of the [minimum spanning tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) of this graph.

## 说明/提示

Here are the graphs for the four test cases of the example (the edges of a possible MST of the graphs are marked pink):

For test case 1

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1513D/73410493ea480145bcececd4920bc7b442158d5d.png)For test case 2

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1513D/244430036440b5951052685b881ac283e38569b1.png)For test case 3

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1513D/3b76480fd803697ef4eb1c8f9a262cb141140b6b.png)For test case 4

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1513D/2aa511e43d0533b40192099a2b9004202f659de5.png)

## 样例 #1

### 输入

```
4
2 5
10 10
2 5
3 3
4 5
5 2 4 9
8 8
5 3 3 6 10 100 9 15```

### 输出

```
5
3
12
46```

# 题解

## 作者：lgswdn_SA (赞：8)

首先上述条件可以转换为区间内所有数都是最小数的倍数。

容易发现对于一个满足这个条件的极大区间，设其最小值为 $a_x$，则其所有包含 $a_x$ 的子区间必然也是满足的，即意味着这一个极大区间 $[l,r]$ 可以用 $\min(a_x,p)\times (r-l)$ 的代价连通。

于是我们从小到大枚举所有这样的最小值，然后从中间向两边扩展求出满足条件的极大区间即可。统计一下边数，这样就能求出连通所有极大区间后还剩多少边没连。对于一些细节问题可以自己想一想，这题基本没有什么细节。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=2e5+9;
typedef pair<int,int> pii;

inline long long read() {
    register long long x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int T,n,p,a[N];
bool vst[N];

signed main() {
	T=read();
	while(T--) {
		n=read(), p=read();
		rep(i,1,n) a[i]=read(), vst[i]=0;
		priority_queue<pii>q;
		rep(i,1,n) q.push(pii(-a[i],i));
		vst[0]=vst[n]=vst[n+1]=1;
		int cnt=0,ans=0;
		while(!q.empty()) {
			int x=-q.top().first, pos=q.top().second; q.pop();
			if(vst[pos]&&vst[pos-1]) continue;
			if(x>=p) continue;
			int l=pos, r=pos;
			while(l-1>=1&&a[l-1]%x==0&&!vst[l-1]) l--, vst[l]=1, cnt++, ans+=x;
			while(r<=n&&a[r+1]%x==0&&!vst[r]) vst[r]=1, r++, cnt++, ans+=x;
		}
		ans+=(n-1-cnt)*p;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：EDqwq (赞：3)

### 思路：

首先一个显然的性质：如果一个区间内的最小数等于这个区间的最大公约数，这个区间的所有数，一定是区间最小数的倍数。

由于我们需要求最小生成树，而如果两个点可以连接，这条边的权值会为这两个点区间内最小数，所以我们按照 a 的值排序，从小到大向外 “扩展”。

也就是说，对于一个位置，我们尽量向外跑，直到有一个点的值并不是最小值的倍数。

由于我们排了序，这个和一定是最小的。

对于相邻的点连接的权值为 $p$ 的边，处理一下剩下还需要加的边就好了。

***

### 代码：

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x) memset(x,0,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

struct node{
	int w;
	int id;
}e[200010];

int t;
int n,m;
int a[200010];
int ans;
int res;
int q[200010];
int l,r;

bool cmp(node x,node y){
	return x.w < y.w;
}

void move(int i){
	while(!(a[l] % e[i].w) && l >= 1){
		l --;
		if(q[l + 1] == 1)break;
	}
	while(!(a[r] % e[i].w) && r <= n){
		r ++;
		if(q[r - 1] == 1)break;
	}
}

signed main(){
	cin>>t;
	while(t --){
		n = read(),m = read();
		for(int i = 1;i <= n;i ++)q[i] = 0;
		ans = 0;
		res = n - 1;
		for(int i = 1;i <= n;i ++){
			a[i] = read();
			e[i].w = a[i];
			e[i].id = i;
		}
		sort(e + 1,e + n + 1,cmp);
		for(int i = 1;i <= n;i ++){
			if(q[e[i].id])continue;
			if(e[i].w >= m)break;
			l = e[i].id;
			r = e[i].id;
			move(i);
			l ++;
			r --;
			for(int j = l;j <= r - 1;j ++){
				q[j] ++;
				q[j + 1] ++;
			}
			ans += (r - l) * e[i].w;
			res -= (r - l);
		}
		ans += res * m;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：SIXIANG32 (赞：3)

其实这题并不难，但是因为各种奇奇怪怪的细节问题卡了许久。  
真·细节决定成败  
闲话少说，切入正题——  

---
我们来看看满足 $\gcd(a_i, a_{i + 1}, a_{i + 2}\dots, a_j) = \min(a_i, a_{i + 1}, a_{i + 2}, \dots a_j)$ 这样的区间显然满足 $\min(a_i, a_{i + 1}, a_{i + 2}, \dots a_j)$ 为区间 $[i,j]$ 中所有数的因数。~~小学数学知识~~    
这个是解题算法的基础依据，那么根据该算法我们可以得到一个这样的算法雏形——    
先对 $a_i$ 排序，然后挨个枚举，把第 $i$ 个数 $a_i$ 看成最小的。当这个值比 $p$ 要大的时候直接退出，因为这个时候添加这条边是没有意义的，可以被 $p$ 取代。满足这个条件，就要用双指针拓展一个区间 $[l,r]$ 满足其中任意元素都可以整除 $a_i$。显然对于答案的贡献就是 $(r - l) \times a_i$。  

---
在写代码的时候，我们会发现可能会有区间重复计算了，所以要开一个 $vis$ 数组，$vis_i = 0$ 表示没有被碰过，$vis_i = 1$ 是覆盖的一个端点，而 $vis_i = 2$ 是覆盖的里面的点。  
比如说找到一个左端点 $l$ 然后 $vis_l = 1$ 且找到一个 $r$ 然后 $vis_r = 1$，那么我们就可以判定 $[l, r]$ 是一个合法区间，只用计算这个区间的贡献，因为再把 $l$ 左移或把 $r$ 右移会重复计算贡献。

---
总的来说，就是排序，扫一遍双指针找区间然后标记统计一下贡献就可以了。  
但是真的就这么简单吗？不不不——  
> $p \le 10^9, a_i \le 10^9$  

诶诶诶，这看上去要开 long long 的样子诶/shq/cy  
然后开一个 long long 就好了

---
代码：  
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAXN 200000
#define int long long//万恶之源 long long
#define QWQ printf("qwq\n");
using namespace std;
struct node {
	int pos, val;
}pika[MAXN + 10];
int a[MAXN + 10], vis[MAXN + 10];
bool cmp(node &x, node &y) {//排序
	if(x.val != y.val) return x.val < y.val;
	else return x.pos < y.pos;
}
signed main() {
	int T, n, k;
	scanf("%lld", &T);
	while(T--) {
		scanf("%lld%lld", &n, &k);
		memset(vis, 0, sizeof(vis));//多测不清空，保龄两行泪
		int ans = 0, b = n - 1;//b 是权值为 k（初始边权） 的边数
		for(int p = 1; p <= n; p++) {
			scanf("%lld", &a[p]);
			pika[p].pos = p;
			pika[p].val = a[p];
		}
		sort(pika + 1, pika + n + 1, cmp);
		for(int p = 1; p <= n; p++) {
			int l = pika[p].pos, r = pika[p].pos;
			if(pika[p].val >= k) break;//如果以 val[i] 为边权不如以 k 为边权，由于 val[i] 单调递增所以后面不可能出现权值更小的，直接退出
			if(vis[pika[p].pos]) continue;//曾经被覆盖过，贡献被统计过
			while(l >= 1 && (a[l] % pika[p].val == 0)) {
				l--;
				if(vis[l + 1] == 1) break;
			}//找 l
			while(r <= n && (a[r] % pika[p].val == 0)) {
				r++;
				if(vis[r - 1] == 1) break;
			}//找 r
			l++, r--;//调整一下
			for(int i = l; i < r; i++) vis[i]++, vis[i + 1]++;//端点标记为 1，内部标记为 2
			ans = ans + (r - l) * pika[p].val;//统计贡献
			b -= (r - l);//初始边权的边数要减去这些
		}
		printf("%lld\n", ans + b * k);//输出答案，记得加上初始边数
	}
}
```

---

## 作者：iyaang (赞：2)

[劲爆的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17672047.html)

[题目链接](https://www.luogu.com.cn/problem/CF1513D)

更好理解的无脑方法。要寻找区间使得 $\gcd_{i = l}^{r} a_i = \min_{i = l}^{r} a_i$，这意味着区间内所有值都为最小值的倍数。假设最小值为 $a_k (l \leq k \leq r)$，那么我们把最小值放在边上，这样就可以拆成正序找一遍再倒序找一遍，即 $\forall a_i (l \leq i \leq k),a_k \mid a_i$ 和 $\forall a_i (k \leq i \leq r),a_k \mid a_i$。初始 $a_i$ 和 $a_{i+1}$ 都相连权为 $p$ 的边，找出所有区间，每个区间意味着区间内的边都可以替换成找到的最小值，将区间按最小值从大到小排序后按顺序覆盖即可，因为后覆盖的一定比先覆盖的优。维护区间和，区间推平，暴力线段树即可。因为是最小生成树，所以代码实现上 $i$ 上的值是 $i$ 和 $i+1$ 间的连边边权，于是做到 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmax(T &a,T b,Args... args) {a=max({a,b,args...});}
    TA inline void cmin(T &a,T b,Args... args) {a=min({a,b,args...});}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=200010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int T,n,p,a[MAX];
    struct lmy{int l,r,v;}b[MAX]; int cnt;
	
	namespace SegmentTree
	{
		int tag[MAX<<2],sum[MAX<<2];
		inline void pushup(int i) {sum[i]=sum[i<<1]+sum[i<<1|1];}
		inline void down(int i,int l,int r,int k) {sum[i]=(r-l+1)*k,tag[i]=k;}
		inline void pushdown(int i,int l,int r)
		{
			if(!tag[i]||l==r) return;
			int mid=(l+r)>>1;
			down(i<<1,l,mid,tag[i]),down(i<<1|1,mid+1,r,tag[i]),tag[i]=0;
		}
		void build(int i,int l,int r)
		{
			tag[i]=0;
			if(l==r) return sum[i]=p,void();
			int mid=(l+r)>>1;
			build(i<<1,l,mid),build(i<<1|1,mid+1,r);
			pushup(i);
		}
		void modify(int i,int l,int r,int L,int R,int k)
		{
			if(l<=L&&R<=r) return down(i,L,R,k);
			pushdown(i,L,R);
			int mid=(L+R)>>1;
			if(l<=mid) modify(i<<1,l,r,L,mid,k);
			if(r>mid)  modify(i<<1|1,l,r,mid+1,R,k);
			pushup(i);
		}
	}
	using namespace SegmentTree;
	
    inline void lmy_forever()
    {
    	read(T);
    	while(T--)
    	{
    		read(n,p),cnt=0,build(1,1,n-1);
    		for(int i=1;i<=n;++i) read(a[i]);
    		for(int l=1,r=1;r<=n;l=r+1,++r) {if(a[l]>=p) continue; while(r<=n&&a[r]%a[l]==0) ++r; --r; if(l!=r) b[++cnt]=(lmy){l,r-1,a[l]};}
    		for(int l=n,r=n;l;r=l-1,--l) {if(a[r]>=p) continue; while(l>=1&&a[l]%a[r]==0) --l; ++l; if(l!=r) b[++cnt]=(lmy){l,r-1,a[r]};}
    		sort(b+1,b+cnt+1,[](lmy x,lmy y){return x.v>y.v;});
    		for(int i=1;i<=cnt;++i) modify(1,b[i].l,b[i].r,1,n-1,b[i].v);
    		write(sum[1],'\n');
		}
	}
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：zesqwq (赞：2)

我今天就要用 $\text{ds}$ 优化建图过了这道题！[submission](https://codeforces.com/contest/1513/submission/203023663)

你发现 $\gcd$ 有一个性质，就是对于相同的右端点，后缀 $\text{gcd}$ 总数不会超过 $O(\log V)$ 段，而后缀 $\text{min}$ 单调递减，意味着从相同的 $r$ 端点，连边 **段数** 是 $O(\log V)$ 的。

我们可以使用 栈 来维护后缀 $\gcd$，用 $\text{ST}$ 表来维护后缀 $\min$（当然这个也可以用栈维护），这样问题就变成了给你 $O(n \log V)$ 个从一个点向一个区间连边，求 $\text{MST}$。考虑使用 $\text{kruskal}$，问题变为快速让一个点对一个区间连边，求并查集合并次数。

注意到因为是求 $\text{MST}$，所以不能用一般的数据结构优化建边解决，因为数据结构维护的边都是无向边，而我们需要长度为 $0$ 的辅助边，很难解决问题。

然而这个过程可以使用启发式合并 $+$ 哈希 $+$ 树状数组解决，具体的，假设我们要合并 $\operatorname{merge}(u, [l, r])$，我们给每个集合附一个哈希值 $h_x$，然后用启发式合并维护集合合并，用树状数组查询区间哈希值是否等于区间中所有数都是 $u$ 的哈希值，如果不是，可以采用分治，递归判定左半边和右半边，直到区间长度为 $1$ 时暴力合并。

---

## 作者：Mophie (赞：2)

为了感谢这个上分场，决定给这个D写一份题解。

我的思路可能比较奇怪。

因为首先每次是改变一个区间 $[l_i,r_i]$。每次贪心枚举 $a[i]$ 最小值并覆盖。

现在只需解决重合问题即可。

然后我们对每个点设一个权值 $val_i$，$0$ 代表未被覆盖，$1$ 代表被覆盖但是覆盖的是端点，$2$ 代表覆盖的点在里面。

一个点当两次端点权值变成 $2$。

然后就比较简单了，因为我们每次覆盖的那个线段如果与其他线段重合,例如说区间 $[l_i,r_i]$ 与 $[l_j,r_j]$ 合并的时候，$l_j$ 在 $r_i$ 左边，那么应该合并为 $[l_i,r_j]$

所以我们每一次扩展的时候，找到 $val_i=1$ 且可以扩展到的可以直接将左端点设为它就好了。

右端点同理，这样可以发现就不会有重复的出现。

时间复杂度因为所有点都只会被枚举 $\leq3$ 次故是 $O(n)$ 的。

```cpp
//红太阳zhouakngyang txdy!
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
int taxi,n,p;
int a[200009];
long long ans,now;
int vis[200009];
struct point
{
	int x,pos;
}k[200009];
inline bool cmp(point xxx,point yyy)
{
	return xxx.x<yyy.x;
}
signed main()
{
	taxi=read();
	for(int ttt=1;ttt<=taxi;ttt++)
	{
		ans=0;
		n=read(),p=read();now=n-1;
		for(int i=1;i<=n;i++)a[i]=read(),k[i].x=a[i],k[i].pos=i,vis[i]=0;
		sort(k+1,k+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			if(vis[k[i].pos]!=0)continue;
			if(k[i].x>=p)break; 
			int l=k[i].pos,r=k[i].pos;
			while(a[l]%k[i].x==0&&l>=1)
			{
				if(vis[l]==1)
				{
					l--;break;
				}
				l--;
				
			}
			while(a[r]%k[i].x==0&&r<=n)
			{
				if(vis[r]==1)
				{
					r++;break;
				}
				r++;
			}
			l++,r--;
			for(int j=l;j<r;j++)vis[j]++,vis[j+1]++;
		//	cout<<l<<" "<<r<<endl;
			ans=ans+(r-l)*k[i].x;now=now-(r-l);
		}
		ans=ans+now*p;
		printf("%lld\n",ans);
	}
	return 0;
}


```


---

## 作者：DaiRuiChen007 (赞：1)

# CF1513D 题解



## 思路分析

容易把第一种连边条件转化为 $a_i\sim a_j$ 都是某个 $a_x$ 的倍数，考虑 Kruskal 生成树，对于所有点权 $<p$ 的点从小到大枚举，每次对于一个 $a_x$，扩展出其左边有多少个连续的 $a_x$ 的倍数和其右边有多少个连续的 $a_x$ 的倍数，求出有 $a_x$ 这一约数的极大的区间 $[l_x,r_x]$，那么对于所有 $i\in [l_x,r_x]$，对于每条可能的边 $(i,x)$ 有并查集判断一下即可，每次这样的操作能够联通区间 $[l_x,r_x]$。

此时生成森林一定是若干个连续的区间构成一棵树，把剩下的边用 $p$ 的代价都连接起来就可以。

但是这种做法对于每个 $x$ 在最坏情况下都需要遍历整个区间，复杂度退化为 $\Theta(n^2)$。

考虑优化，注意到如下的观察：

> 观察：
>
>  当遇到一个 $i$ 使 $(i,x)$ 构成环后，再往后的 $i$ 一样会生成环，在这个地方直接 `break` 掉即可。
>
> 我们只需要证明，每次 `break` 后区间 $[l_x,r_x]$ 已经是联通的。
>
> 考虑数学归纳法，当前所有区间 $[l_x,r_x]$ 已经考虑完毕并联通，考虑下一个区间 $[l_{x'},r_{x'}]$，只需要证明 $x'$ 不会越过这个区间去连接，即不存在 $x'\to i'$ 满足 $i'<l_x\le r_x<x'$ 或 $i'>r_x\ge l_x>x'$，注意到这种 $x\in[l_{x'},r_{x'}]$ 只会在 $x'=x$ 时发生，此时有 $[l_{x'},r_{x'}]=[l_x,r_x]$，因此这样的 $(x',i')$ 不存在，故原命题得证。

这样每个点至多同时作为某个区间的左端点和右端点，访问次数不会超过 $2$。

时间复杂度 $\Theta(n\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int MAXN=2e5+1;
int dsu[MAXN],a[MAXN];
inline int find(int x) {
	if(dsu[x]==x) return x;
	return dsu[x]=find(dsu[x]);
}
inline void solve() {
	int n,p,tot=0,ans=0;
	scanf("%lld%lld",&n,&p);
	for(int i=1;i<=n;++i) dsu[i]=i;
	priority_queue <pii,vector<pii>,greater<pii> > q;
	for(int i=1;i<=n;++i) {
		scanf("%lld",&a[i]);
		if(a[i]<p) q.push(make_pair(a[i],i));
	}
	while(!q.empty()) {
		int x=q.top().second; q.pop();
		for(int i=x-1;i>=1;--i) {
			if(a[i]%a[x]!=0) break;
			int u=find(x),v=find(i);
			if(u!=v) {
				++tot,ans+=a[x];
				dsu[u]=v;
			} else break;
		}
		for(int i=x+1;i<=n;++i) {
			if(a[i]%a[x]!=0) break;
			int u=find(x),v=find(i);
			if(u!=v) {
				++tot,ans+=a[x];
				dsu[u]=v;
			} else break;
		}
	}
	printf("%lld\n",ans+(n-1-tot)*p);
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：bianshiyang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1513D)

好像题解区还没我这种倍增+并查集的做法，于是补充一发。

# 分析
首先发现题目有两种边，一种是长度为某个 $a_i$ 的边，一种是固定长度为 $p$ 的边，为了方便描述，我们在后文称前者为一类边，后者为二类边。二类边的目的主要是使得这个图一定存在一棵生成树，即本题一定有解（全部都用二类边就是一条链显然是一棵生成树）。

不难想到我们可以模拟一个类似 Kruskal 的算法来解决本题，也就是按照边权排序，从小到大加入生成树，如果加入的边的权值已经不小于 $p$（注意包含等于可以减一点常数，其实严格大于也可以）了那么后面都用二类边代替一定是最优的。因为二类边每操作一次一定可以找到两个不连通的块并连在一起，但是一类边不一定，换句话说二类边性质更强，对于边权不小于 $p$ 的一类边直接舍去是能保证答案正确的。

进一步我们发现，对于一条长为 $a$ 的边（我们只考虑满足 $a<p$ 的边），能通过它连通的点一定是一段区间。这也不难证明，假设存在区间 $[l,r]$ 使得 $\gcd_{k=l}^ra_k=\min_{k=l}^ra_k$，那么对于 $[l,r]$ 的任意跨过某个等于 $a$ 的位置的子区间 $[l',r']$ 也一定存在一条 $l'$ 到 $r'$ 长度为 $a$ 的边。这是显然的，因为如果满足 $\gcd_{k=l}^ra_k=\min_{k=l}^ra_k$，那么必然有 $a$
是 $[l,r]$ 的最小值，并且 $[l,r]$ 区间的所有数都是 $a$ 的倍数，所以对于包含 $a$ 的子区间 $[l',r']$，也必然有上述性质成立。

这样子做有什么好处呢？我们会发现这样子做我们可以通过若干条长为 $a$ 的边把 $[l,r]$ 内的点全部连起来，假设我们以 $a$ 来把 $[l,r]$ 划分为左右两部分（$a$ 左侧和 $a$ 右侧）看（这里随意取一个为 $a$ 的位置就可以），假设 $a$ 属于左右两部分更小的那一部分（这样子两部分都不空）。对于区间内任意两点 $i$ 和 $j$ 不相连，如果 $i$，$j$ 在不同的部分那么显然可以直接连边，否则，我们不妨假设 $i$ 和 $j$ 都在左侧，那么我们从右侧随意找一个点 $k$，将 $i$ 和 $k$ 相连，$j$ 和 $k$ 相连（如果某个点已经和 $k$ 相连则跳过此步骤），$i$ 和 $j$ 就可以相连。所以我们对于每个 $a_i$，都可以找到符合 $\gcd_{k=l}^ra_k=\min_{k=l}^ra_k=a_i$ 的极长区间 $[l,r]$，然后用并查集维护这个区间的连通性。注意我们这里没有必要确定真实连边的顺序，也没必要确定哪些边可以直接连，哪些边要通过某个点间接连边，因为我们只需要知道这个区间所产生的代价就是这个区间内连通块数减一条权值为 $a$ 的边就可以了，具体怎么连无所谓反正之前证明过都可以连起来。

注意到 $l$ 和 $r$ 可以分开求，即先求出每个点向左可以扩展多长，向右可以扩展多长，那么两段拼起来就是我们上述的极长区间，这一部分我们可以维护一个类似 ST 表的倍增来做。

最后我们来分析一下复杂度，倍增的复杂度是 $O(n\log n)$，由于我们至多进行 $n-1$ 次并查集操作（连边），那么并查集复杂度是 $O(n\alpha(n))$ 的，还有排序的 $O(n\log n)$，单组数据总复杂度就是近似 $O(n\log n)$。

题外话：之所以想到这个奇葩解法可能是因为之前做过[这题](https://codeforces.com/problemset/problem/1231/G)，仔细想想这题其实就是那题树上的倍增改到区间上来做，再加上一点 Kruskal 的贪心性质。

# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int T,n,p,l[N],r[N],cnt;
int st[N][25],lg[N],f[N];
ll ans;
 
struct node{
	int w,num;
	friend bool operator<(node x,node y){return x.w<y.w;}
}a[N];
 
int fa(int x)
{
	if(x==f[x]) return x;
	return f[x]=fa(f[x]);
}//这一部分类似Kruscal
 
int main()
{
	for(int i=2;i<N;i++) lg[i]=lg[i>>1]+1;//预处理log2(i)
	scanf("%d",&T);
	while(T--)
	{
		cnt=0;ans=0;//cnt表示连了多少条边，为了判断最后需要多少条长为p的边
		scanf("%d%d",&n,&p);
		for(int i=1;i<=n+1;i++) f[i]=i;//n+1是哨兵节点
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i].w);
			st[i][0]=a[i].w;a[i].num=i;
		}
		for(int j=1;j<=lg[n];j++)
			for(int i=1;i+(1<<j)-1<=n;i++) st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);//gcd上的st表（雾）
		for(int i=1;i<=n;i++)//左右分开跑倍增，这里好像写的有些丑陋
		{
			l[i]=r[i]=i;
			int gg=a[i].w;
			for(int j=lg[i];j>=0;j--)
				if(l[i]-(1<<j)>=1&&__gcd(gg,st[l[i]-(1<<j)][j])==a[i].w) gg=__gcd(gg,st[l[i]-(1<<j)][j]),l[i]=l[i]-(1<<j);
			gg=a[i].w;
			for(int j=lg[n-i+1];j>=0;j--)
				if(r[i]+(1<<j)<=n&&__gcd(gg,st[r[i]+1][j])==a[i].w) gg=__gcd(gg,st[r[i]+1][j]),r[i]=r[i]+(1<<j);
		}
		sort(a+1,a+n+1);//按照边权排序
		for(int i=1;i<=n;i++)
		{
			if(a[i].w>=p) break;//无用的一类边
			int x=a[i].num;
			for(int j=fa(l[x]);j<r[x];)
			{
				f[j]=j+1;j=fa(f[j]);//直接计数和连起来即可，不用管具体怎么连的
				cnt++;ans+=a[i].w;
			}
		}
		if(cnt<n-1) ans+=1ll*(n-1-cnt)*p;//剩下的边用p来连，一定可以连
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：hytallenxu (赞：0)

## 前言
这道题细节有一点多，做的时候差点被各种 corner case 创死，出题人 ~~**[数据删除]**~~ 出的真好。

## 正文
首先观察一波条件。

$$\gcd_{i=l}^{r} a_i=\min_{i=l}^{r} a_i$$

这个式子看上去非常熟悉，转化一下这个条件，变成「数列 $a$ 在区间 $[l,r]$ 中所有的数都是其在此区间的**最小数**的倍数」。

这个东西我们可以快捷的用双指针求出 $l,r$。

题目虽然说的是要求出 `MST` 的边全之和，但是我们并不需要建边跑一遍 `MST`，只需要每次考虑是否加入边，以及这些边的贡献。

显然，只有当 $\min_{i=l}^{r} a_i < p$ 的时候才可以尝试连边。 

贪心的来说，我们要选中尽可能小的 $\min_{i=l}^{r} a_i$（设为 $a_x$），并且多扩展 $l,r$。这样，对于所有包括 $a_x$ 的子区间 $[l,r]$，每条边都可以用 $a_x$ 的代价联通，贡献就是最小的。

这里有一个细节，就是这里会有重复计算的问题。

我们可以开一个 $\text{vis}$ 数组来储存这个点是否被访问过。

**特殊的，我们必须每次操作后把左右端点设成 $1$，而中间的设为 $2$，因为端点之后是可以继续连边的。** 每次双指针扩展**只能最多**扩展到端点为 $1$ 的点，因为若是 $2$ 的话则表示这个点的已经被连接了。

贡献的计算方法便是每次的 $(r-l) \times \min_{i=l}^{r} a_i$。

这么说有点抽象，看代码就全都懂了。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
#ifdef LOCAL
	#include "debug.h"
#else
	#define debug(...) 42
#endif
#define mkp make_pair
#define pb emplace_back
#define endl "\n"
using namespace std;
using ll = long long;
int t;

void solve(){
	int n,p,cnt=0,ans=0;
	cin>>n>>p;
	vector<pair<int,int>> arr(n+1);
	vector<int> brr(n+1),vis(n+1);
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		arr[i]=mkp(x,i);
		brr[i]=x;
	}
	cnt=n-1;
	sort(arr.begin()+1,arr.end());
	for(int i=1;i<=n;i++){
		auto [num,index]=arr[i];
		int l=index,r=index;
		if(num>=p) break;
		if(vis[index]) continue;
		if(num<p){
			while(l>=1 && brr[l]%num==0 && brr[l]>=num){
				l--;
				if(vis[l+1]==1) break;
			}
			l++;
			while(r<=n && brr[r]%num==0 && brr[r]>=num){
				r++;
				if(vis[r-1]==1) break;
			}
			r--;
			vis[l]++,vis[r]++;
			for(int j=l+1;j<r;j++){
				vis[j]+=2;
			}
			ans+=(r-l)*num;
			cnt-=(r-l);
		}
	}
	cout<<ans+cnt*p<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

## 题面
对于一个序列，若有 $(i,j)(i < j)$，若 $\gcd_{k=i}^j a_k =\min_{k=i}^j a_k$，则连一条无向边 $(i,j)$，边权为 $\min_{k=i}^j a_k$；若有 $(i,j)(i+1=j)$，连一条无向边 $(i,j)$，边权为 $p$。

给定一个长度为 $n$ 的序列，求连边所构成图的 MST 的边权之和，多测。

## 题意
首先考虑转化限制条件，假设我们在 $l, r$ 之间连了一条边（$l < r$），记 $v = \min\limits_{i = l}^{r}a_i$，那么可以得到
$$\gcd\limits_{i = l}^{r}a_i = \min\limits_{i = l}^{r}a_i \Leftrightarrow \forall i \in \left[l,r\right], v \mid a_i$$

既然题目要求的是最小生成树，那么我们贪心的去处理。考虑从小到大枚举边权，并计算当前边权在当前情况下可以最多联通多少个连通块（单点也看作连通块），显然对于 $a_i$ 来说，可以以边权 $a_i$ 联通的点对 $\left(l, r\right)$ 一定满足 $i \in \left[l,r\right] \land \forall k \in \left[l,r\right], a_i \mid a_k$，从 $i$ 开始两侧遍历即可最大化该区间，因为边权是从小到大枚举的，所以在当前情况下最大化区间一定不劣。同时注意一点，如果左右边界扩充到了已经被其他点联通过的点也需要停止扩充，如果 $a_i \ge p$ 那么剩下的未联通的联通块直接使用第二种边联通即可。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;
typedef std::vector<bool> bitset;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, P;

        std::cin >> N >> P;

        ValueVector source(N);
        PairVector map(N);

        for (valueType i = 0; i < N; ++i) {
            std::cin >> source[i];

            map[i] = std::make_pair(source[i], i);
        }

        std::sort(map.begin(), map.end());

        bitset visited(N, false);

        valueType ans = 0, count = 0;

        for (auto const &value: map) {
            if (value.first >= P)
                break;

            valueType const index = value.second;

            if (visited[index])
                continue;

            visited[index] = true;

            valueType leftBound = index, rightBound = index;

            while (leftBound > 0 && source[leftBound - 1] % source[index] == 0) {
                --leftBound;

                if (visited[leftBound])
                    break;

                visited[leftBound] = true;
            }

            while (rightBound < N - 1 && source[rightBound + 1] % source[index] == 0) {
                ++rightBound;

                if (visited[rightBound])
                    break;

                visited[rightBound] = true;
            }

            count += rightBound - leftBound;

            ans += source[index] * (rightBound - leftBound);
        }

        ans += (N - 1 - count) * P;

        std::cout << ans << '\n';
    }

    std::cout << std::flush;

    return 0;
}
```

---

