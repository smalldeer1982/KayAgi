# [AGC015E] Mr.Aoki Incubator

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc015/tasks/agc015_e

数直線上に $ N $ 人の高橋君が並んでおり、$ 1 $ から $ N $ までの番号がついています。 $ i $ 人目の高橋君は、時刻 $ 0 $ に位置 $ X_i $ にいて、速度 $ V_i $ で正の方向に歩き始めます。

けすぬ君は、時刻 $ 0 $ に高橋君たちのうちの何人かを選んで青木君にすることができます。 高橋君が青木君になっても歩く速度は変化しません。 それ以降、もしある瞬間に高橋君と青木君が同じ座標にいたなら、高橋君は青木君になります。

けすぬ君が時刻 $ 0 $ に高橋君を青木君にする $ 2^N $ 通りの方法のうち、 十分な時間が経過した後、高橋君が全員青木君になっているような方法の数を $ 10^9+7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 200000 $
- $ 1\ ≦\ X_i,V_i\ ≦\ 10^9(1\ ≦\ i\ ≦\ N) $
- $ X_i,V_i $ は整数である
- $ X_i $ たちはすべて異なる
- $ V_i $ たちはすべて異なる

### Sample Explanation 1

けすぬ君が $ (2),(3),(1,2),(1,3),(2,3),(1,2,3) $ 番目の高橋君を青木君にしたとき、十分な時間が経過した後にすべての高橋君が青木君になっています。

## 样例 #1

### 输入

```
3
2 5
6 1
3 7```

### 输出

```
6```

## 样例 #2

### 输入

```
4
3 7
2 9
8 16
10 8```

### 输出

```
9```

# 题解

## 作者：苹果蓝17 (赞：14)

下面称变成 Aoki 的 Takahashi 为**被标记的**。

> 结论：设若初始标记集合 $S$，最终被标记的人集合为 $f(S)$，那么 $f(S \bigcup T)=f(S) \bigcup f(T)$。

> 证明：假设最终有一个人 $x \notin f(S) \bigcup f(T)$，那么他不可能初始被标记，且标记他的人 $x'$ 同样满足 $x' \notin f(S) \bigcup f(T)$……无限递归下去，而这个过程是有限的，故假设矛盾。

那么考虑只标记一个人 $x$，最终被标记的是哪些。

首先在 $x$ 右边且比 $x$ 慢的会被标记，在 $x$ 左边且比 $x$ 快的会被标记。

但不仅如此。在 $x$ 左边且比 $x$ 快的超过 $x$ 后会将右边比它们慢的标记，同样在 $x$ 右边且比 $x$ 慢的会将左边比它们快的标记。容易发现**新增的这些不会标记更多的人**。

将所有人按坐标排序，记速度的前缀最大值为 $pmx_x$，后缀最小值为 $smn_x$，那么被标记的人是：

+ $x$ 本身。
+ 在 $x$ 左边，且比 $smn_x$ 严格快的人。
+ 在 $x$ 右边，且比 $pmx_x$ 严格慢的人。

设 $dp_i$ 表示考虑前 $i$ 个人，初始标记了第 $i$ 个人的方案数。

假设由 $j$ 转移而来（上一个初始标记的是 $j$），那么覆盖不到的区域是位置在 $(j,i)$ 的人且速度在 $[pmx_j,smn_i]$ 中的人。

由于 $pmn,pmx$ 都是单调不降的，故对于一个 $i$ 而言 $j$ 具有可二分性。那么维护能转移的最小的 $j$，其具有单调性。

用 Two-pointer 维护即可，同时类似莫队维护检查的矩形。时间复杂度 $O(n \log n)$，瓶颈在于排序与离散化。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,mod=1e9+7;
int n;
struct abc{
	int x,y;
}p[N];
bool operator <(abc X,abc Y){
	return X.x<Y.x;
}

int v[N],mp[N];
int pmx[N],smn[N],dp[N],s[N];

int l,r=-1,L,R=-1,sum;

int check(int l_,int r_,int L_,int R_){
	if(l_>r_ || L_>R_) return 0;
	while(r<r_) r++,sum+=(p[r].y>=L && p[r].y<=R);
	while(l<l_) sum-=(p[l].y>=L && p[l].y<=R),l++;
	while(R<R_) R++,sum+=(mp[R]>=l && mp[R]<=r);
	while(L<L_) sum-=(mp[L]>=l && mp[L]<=r),L++;
	return sum; 
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y),v[i]=p[i].y;
	sort(v+1,v+n+1);
	for(int i=1;i<=n;i++) p[i].y=lower_bound(v+1,v+n+1,p[i].y)-v;
	
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++) pmx[i]=max(pmx[i-1],p[i].y);
	smn[n+1]=n+1;
	for(int i=n;i>=1;i--) smn[i]=min(smn[i+1],p[i].y); 
	
	for(int i=1;i<=n;i++) mp[p[i].y]=i;
	
	dp[0]=s[0]=1;
	int nw=0;
	for(int i=1;i<=n+1;i++){
		while(check(nw+1,i-1,pmx[nw],smn[i])) nw++;
		dp[i]=s[i-1];
		if(nw) dp[i]=(dp[i]+mod-s[nw-1])%mod;
		s[i]=(s[i-1]+dp[i])%mod;
	}
	cout<<dp[n+1];
}
```

---

## 作者：Kewth (赞：12)

足够长的时间后，点一定是按速度排序的，不妨假定 v 升序。  
考虑点 i 被染色后有哪些点会被染到，事实上染到的一定是一段区间 [l, r] ，  
l 是最小的满足 x[l] >= x[i] 的下标，  
r 是最大的满足 x[r] <= x[i] 的下标。

原因：  
i 最开始在 l 左边 (x[l] >= x[i])，最后一定会在 l 右边 (v[l] <= v[i]) ，  
可以反证最后在 [l, i] 区间内的点都会被经过，  
对于 r 同理。

求出了所有点的 [l, r] 后，问题转换为选择若干 [l, r] 使得它们的并为 [1, n] 。  
根据定义不难发现 l, r 都 **随 x[i]** 的增大单调不降。  
那么再将点按 x 升序，此时的 l, r 也就都是升序的了。

DP 设 f[i] 表示用前 i 个区间，钦定第 i 个区间必选，覆盖 [1, r[i]] 的方案数。  
对于所有满足 r[j] >= l[i] - 1 且 j < i 的 j 都可以从 f[j] 转移到 f[i] 。  
而 r 是升序的，这意味着只要 f[j] 能转移到 f[i] ，f[j + 1] 就能转移到 f[i] ，  
换言之，f[i] 的转移是一段区间 [L, i - 1] ，其中 L 是满足条件的最小 j 。  
而同时 l 也是升序的，这意味着 L 也是升序的，dp 的过程中维护这个 L 即可。  
区间转移用前缀和优化即可做到 $O(1)$ 。

实现上并不需要反复排序，只需要将 x 离散化后就可以替代第二次排序，  
并且 x 离散化后求 l, r 相当于求一类前缀后缀最值。  
总复杂度 $O(nlogn)$ ，瓶颈在于排序和离散化。

参考实现：

```cpp
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005, mod = 1000000007;
int l[maxn], r[maxn];
int p[maxn];
int tmp[maxn];
Par pr[maxn];
ll f[maxn], s[maxn];

int main() {
	int n = read;

	for(int i = 1; i <= n; i ++)
		read(pr[i].second, pr[i].first);
	std::sort(pr + 1, pr + n + 1);

	for(int i = 1; i <= n; i ++)
		tmp[i] = pr[i].second;
	std::sort(tmp + 1, tmp + n + 1);

	for(int i = 1; i <= n; i ++) {
		pr[i].second = int(std::lower_bound(tmp + 1, tmp + n + 1, pr[i].second) - tmp);
		p[pr[i].second] = i;
	}

	for(int i = 1; i <= n; i ++)
		r[i] = std::max(r[i - 1], p[i]);
	l[n] = p[n];
	for(int i = n - 1; i; i --)
		l[i] = std::min(l[i + 1], p[i]);

	int L = 0;
	f[0] = s[0] = 1;

	for(int i = 1; i <= n; i ++) {
		while(r[L] < l[i] - 1)
			++ L;
		f[i] = (s[i - 1] - s[L - 1] + mod) % mod;
		s[i] = (s[i - 1] + f[i]) % mod;
	}

	while(r[L] < n)
		++ L;
	printf("%lld\n", (s[n] - s[L - 1] + mod) % mod);
}
```

---

## 作者：w4p3r (赞：9)

考虑第$i$个人与第$j$个人的相遇时间为：$\dfrac {X_i-X_j}{V_j-V_i}$（如果这个值小于$0$则不能相遇）。

我们考虑把第$i$个人看做平面直角坐标系的一个点$(V_i,X_i)$，并假设$K_{i,j}$表示第$i$个点与第$j$个点的斜率，则$i$与$j$的相遇时间为$-K_{i,j}$。

考虑把一个点（人）$x$染色后的影响，对于满足$K_{x,y} \le 0$的$y$，$y$可以被$x$染色。同时对于满足$K_{y,z}<K_{x,y}$的点$z$，$z$会被$y$染色，以此类推...

画图之后可以发现 ~~（本人是画图渣所以还是不放图了，大家可以直接画图看一看awa）~~，若找到满足$K_{x,l}<0$且$V$最小的$l$，以及满足$K_{x,r}<0$且$V$最大的$r$，可以发现：

对于任意$p$满足$V_l \le V_p \le V_r$，$p$都会被$x$直接或间接染色，若不满足则一定不会被$x$直接或间接染色。

后者显然（画个图就知道了），考虑对于前者：

若$K_{p,x}<0$，则$p$可以被$x$直接染色。

否则，若$V_l \le V_p \le V_x$，有$K_{l,p}<K_{p,x}$，$p$会被$l$染色。$V_x \le V_p \le V_r$时同理。

~~（画图！画图！画图！）~~

所以一个点染色后只会影响一个区间，那么这就是一个简单的区间覆盖问题了，直接$DP$即可。

假设$f_i$
是覆盖到第$i$个点的方案数，$s$是$f$的前缀和，$l_i$和$r_i$表示对$i$染色后能影响的区间的左端点/右端点

则$s_{r_i}-s_{l_i-2}\ \ \ \ ->\ \ \ \ f_{r_i}$ 

（箭头表示左边对右边有贡献）

代码（我找区间用的是线段树二分，比较2b）：

```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define re register int 
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define mp make_pair
#define pb push_back
#define pf push_front
#define pa pair<int,int>
#define fr first
#define sd second
#define Z(x) (x>=mod?x-mod:x)
#define lowbit(x) (x&(-x))
#define N 1000010
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline ll read()
{
    char ch=getchar();
    ll s=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
pa p[N],g[N];
int n;int st[N],top,f[N],s[N];
vector<int>v[N];
const int mod=1e9+7;
int minn[N<<2],maxn[N<<2];
void build(int l,int r,int x)
{
	if(l==r){minn[x]=maxn[x]=p[l].sd;return ;}
	build(l,mid,ls);build(mid+1,r,rs);
	minn[x]=min(minn[ls],minn[rs]);
	maxn[x]=max(maxn[ls],maxn[rs]);
}
int askl(int l,int r,int x,int val)
{
	if(maxn[x]<val)return inf;
	if(l==r){return l;}int t=askl(l,mid,ls,val);
	if(t!=inf)return t;
	else return askl(mid+1,r,rs,val);
}
int askr(int l,int r,int x,int val)
{
	if(minn[x]>val)return -inf;
	if(l==r){return l;}int t=askr(mid+1,r,rs,val);
	if(t!=-inf)return t;
	else return askr(l,mid,ls,val);
}
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read();
    FOR(i,1,n)p[i].sd=read(),p[i].fr=read();
    sort(p+1,p+n+1);build(1,n,1);
    FOR(i,1,n)g[i].sd=min(askl(1,n,1,p[i].sd),i),g[i].fr=max(askr(1,n,1,p[i].sd),i);//找区间，sd是左端点，fr是右端点
    FOR(i,1,n)v[g[i].fr].pb(g[i].sd);
    FOR(i,1,n)sort(v[i].begin(),v[i].end());//我的DP实现比较2b才需要排序，如果您的实现比较优秀可以忽略
    f[0]=1;
    FOR(i,0,n)s[i]=1;
    FOR(i,1,n)
    {
    	s[i]=Z(s[i-1]+f[i]);
    	for(int x:v[i])
		{
			f[i]=Z(f[i]+Z(s[i]+mod-(x>1?s[x-2]:0)));//区间覆盖DP
			s[i]=Z(s[i-1]+f[i]);//更新前缀和
		}
    }
    printf("%d\n",f[n]);
    return 0;
}
//code once,check twice
```


**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**



---

## 作者：Arghariza (赞：4)

这种点对移动互相感染的题，一般可以建笛卡尔坐标系。每个点 $i$ 坐标为 $(V_i,X_i)$，若有两个点 $a,b$ 的相遇时间为 $\dfrac{X_a-X_b}{V_b-V_a}$，即 $-k_{ab}$。

所以当且仅当两个点连接直线的斜率为负数时，两个点会在时间 $t_{ab}=-k_{ab}$ 相遇。现在考虑如果只有一个点 $a$ 被染色，然后 $a$ 感染了 $b$，$b$ 再感染了 $c$ 的条件：显然是要求 $t_{ab}<t_{bc}$，即 $k_{ab}>k_{bc}$。

所以一个点被 $a$ 直接/间接感染，当且仅当它可以通过一条**斜率单调上升且均为负数的路径**到达 $a$。于是我们考虑 $a$ 的影响范围。

不难可以猜到结论：$a$ 的影响范围为 $V_{i}\in [V_l,V_r]$ 的点，其中 $l$ 为满足 $k_{al}\le 0$ 中的点中 $V$ 值最小的点，$r$ 为满足 $k_{ar}\le 0$ 的点中 $V$ 值最大的点。

一方面，因为如果一个点 $b$ 使得 $V_b<V_l$，显然有 $X_b<X_a$。由于 $b$ 想被 $a$ 影响到必须要经过一条斜率单调上升且均为负数的路径，并且它一定要往右边走，所以走路径的过程中 $X$ 值是单调下降的，那就不可能走到 $a$ 了。$V_b>V_r$ 同理，可以画图理解。

另一方面，对于 $V_{b}\in [V_l,V_r]$ 的点，假设 $V_{b}<V_a$（另一边同理），考虑两种情况：

- $k_{ab}<0$，可以直接被 $a$ 感染。
- $k_{ab}>0$，画图发现 $b$ 显然可以被 $l$ 感染。

证毕。

所以可以先将所有点按照 $V$ 排序，一个点 $a$ 影响的是一段区间 $[l_i,r_i]$ 的点。问题转化为线段覆盖求方案数。

令 $f_i$ 为覆盖到 $i$ 的方案数，显然对于一个点 $i$，$f_{r_i}$ 可以被 $\sum\limits_{k=l_i-1}^{r_i}f_k$ 转移。前缀和优化即可。

复杂度 $O(n\log n)$。预处理我用的树状数组。

[评测记录。](https://atcoder.jp/contests/agc015/submissions/38506361)

---

## 作者：Mr_Wu (赞：4)

将所有点按 $x_i$ 排序。考虑当第 $i$ 个点被选中后，什么样的点最后会因为它被打上标记。首先对 $j<i,v_j>v_i$ 和 $j>i,v_j<v_i$ 是会被直接打标记的。然后考虑被间接打标记的点，对于一个 $j>i,v_j>v_i$，它可以被一个在 $i$ 左侧且比它速度大的一个点打标记（因为这个点会先被 $i$ 打标记）。所以 $j>i,v_j\le \max_{k\le i} v_k$ 的点都可以。同理 $j<i,v_j\ge \min_{k\ge i} v_k$ 的点都可以。我们发现，从对右侧的影响来看，$i$ 越大影响越强。从对左侧的影响来看，$i$ 越小影响越强。

考虑初始时最靠右的被打标记的点 $i$。由于 $i$ 现在是对右侧影响最强的点，故右侧的点 $j$ 被打标记当且仅当 $v_j\le \max_{k\le i} v_k$。而在 $i$ 被打标记后，我们就只需操控 $[1,i-1]$ 的点，使得 $j<i,v_j<\min_{k\ge i} v_k$ 的点都被打标记。

设 $f_i$ 表示操纵 $[1,i-1]$ 的点使得 $j<i,v_j<\min_{k\ge i} v_k$ 的点都被打标记的方案数，同上分析，考虑 $j$ 是初始时 $[1,i-1]$ 内最靠右被打标记的点，要满足 $\max_{j<k<i, v_k<\min_{t\ge i} v_t} v_k<\max_{1\le k\le j} v_k$，然后用 $f_j$ 转移过来。发现合法的 $j$ 是一段右端点为 $i$ 的区间，而考虑左端点，首先我们设 $mx$ 表示 $mx<i,v_{mx}<\min_{t\ge i} v_t$ 的 $v_{mx}$ 最大的 $mx$。对于 $v_{mx}$ 它是可以当 $j$ 的，而对于 $v_{mx}$ 左侧我们只需考虑 $\max_{1\le k\le j} v_k>v_{mx}$，而 $v_{mx}$ 单调所以这部分的 $j$ 也是单调的。这两部分分别用一个指针去维护。

时间复杂度为 $O(n\log n)$，瓶颈在于两遍排序。

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
const int MAXN=2e5+5,MOD=1e9+7,INF=1e9+7;
inline int add(int x,int y){return x+y<MOD?x+y:x+y-MOD;}
inline int dec(int x,int y){return x<y?x-y+MOD:x-y;}
inline void ADD(int& x,int y){x+=y;if(x>=MOD)x-=MOD;}
inline void DEC(int& x,int y){x-=y;if(x<0)x+=MOD;}

int N,f[MAXN],sf[MAXN];
struct node{
	int x,v;
	bool operator<(const node& t)const{return x<t.x;}
}a[MAXN];
int id[MAXN];bool cmp(int x,int y){return a[x].v<a[y].v;}
int premn[MAXN],sufmn[MAXN],premx[MAXN];

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;++i)scanf("%d%d",&a[i].x,&a[i].v);
	sort(a+1,a+N+1);
	premn[0]=sufmn[N+1]=INF;
	for(int i=1;i<=N;++i)premn[i]=min(premn[i-1],a[i].v);
	for(int i=1;i<=N;++i)premx[i]=max(premx[i-1],a[i].v);
	for(int i=N;i>=1;--i)sufmn[i]=min(sufmn[i+1],a[i].v);
	for(int i=1;i<=N;++i)id[i]=i;
	sort(id+1,id+N+1,cmp);
	for(int i=1,j=1,p1=0,p2=1;i<=N+1;++i){
		if(i!=1){
			if(a[i-1].v<sufmn[i]){
				if(!p1||a[i-1].v>a[p1].v)p1=i-1;
			}
		}
		while(j<=N&&a[id[j]].v<sufmn[i]){
			if(id[j]<i){
				if(!p1||a[id[j]].v>a[p1].v)p1=id[j];
			}
			++j;
		}
		while(p2<=N&&a[p2].v<a[p1].v)++p2;
		if(p1){
			int p=min(p2,p1);
			f[i]=dec(sf[i-1],sf[p-1]);
			sf[i]=add(sf[i-1],f[i]);
		}else{
			f[i]=add(sf[i-1],1);
		}
		sf[i]=add(sf[i-1],f[i]);
	}
	printf("%d",f[N+1]);
	return 0;
}
```

---

## 作者：Graphcity (赞：2)

首先把所有点按照 $x$ 坐标从小往大排序。

考察一个点 $k$ 何时不能满足题目要求：设 $k$ 左右两边第一个染色点为 $pre,nxt$，如果 $pre$ 及前面的点都有 $v<v_k$，$nxt$ 及后面的点都有 $v>v_k$，那么无论如何都不能满足，否则必能满足。

那么我们可以求出对于每个点 $i$ 的一个区间 $[L_i,R_i]$，表示至少应该有一个染色点在这个区间里面。

设 $f_{i,j}$ 表示从左往右扫描到第 $i$ 个点，最后一个染色点为 $j$ 的方案数。有三种转移：
$$
\begin{cases}
f_{i-1,j}\to f_{i,j} & j<i \\
f_{i-1,j}\to f_{i,i} & j<i \\
f_{R_i,j}=0 & j<L_i
\end{cases}
$$
前两种显然维护单点值和总和就行。第三种可以发现赋值为零的 $j$ 是一段前缀，记录这段前缀的长度即可。时间复杂度瓶颈在于排序，$O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,Mod=1e9+7;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,f[Maxn+5],id[Maxn+5];
int L[Maxn+5],R[Maxn+5],sum,pos;
struct Point{int x,v;} h[Maxn+5];
vector<int> v[Maxn+5];

int main()
{
    n=read();
    For(i,1,n) h[i].x=read(),h[i].v=read(),id[i]=i;
    sort(h+1,h+n+1,[](Point a,Point b){return a.x<b.x;});
    sort(id+1,id+n+1,[&](int a,int b){return h[a].v<h[b].v;});
    for(int i=1,mx=0;i<=n;++i) mx=max(mx,id[i]),R[id[i]]=mx;
    reverse(id+1,id+n+1);
    for(int i=1,mn=n;i<=n;++i) mn=min(mn,id[i]),L[id[i]]=mn;
    For(i,1,n) v[R[i]].push_back(L[i]);
    f[0]=1,sum=1;
    For(i,1,n)
    {
        f[i]=sum,sum=(sum+f[i])%Mod;
        for(auto j:v[i]) while(pos<j) sum=(sum-f[pos]+Mod)%Mod,f[pos++]=0;
    }
    int ans=0; For(i,0,n) ans=(ans+f[i])%Mod;
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc015_e)

**题目大意**

> 给定 $n$ 个动点，第 $i$ 个动点从 $x_i$ 出发以 $v_i$ 的速度移动，初始给若干个动点染色，两个动点相遇后，如果有一个染色点，会给另一个点也染色。
>
> 求有多少种初始染色方案，使得最终每个点都被染色。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

设 $f(S)$ 表示给 $S$ 染色后最终会有哪些点被染色，容易发现 $f(S\cup T)=f(S)\cup f(T)$，否则考虑一个 $x\in f(S\cup T)\setminus f(S)\cup f(T)$，不断考虑 $x$ 从哪里被染色会导出矛盾。

观察 $f(\{i\})$ 的性质，把每个点画在 $(v_i,x_i)$ 的坐标上，两个点相遇当且仅当连线斜率 $<0$，且连线越平缓相遇时间越早。

因此一条染色路径是斜率 $<0$ 且递减的折线。

观察发现每个点可以染色的点是横坐标连续的一段区间，即 $v_j<v_i$ 且 $x_j>x_i$ 的最小的 $j$，以及 $v_i<v_j$ 且 $x_j<x_i$ 的最大的 $j$。

那么给一个点染色相当于选择一个区间，要求所有区间的并为 $[1,n]$。

用 $f_i$ 表示考虑当前恰好覆盖 $[1,i]$ 的方案数，转移时枚举 $r=i$ 的区间，从 $f_{l-1}\sim f_r$ 更新 $f_r$，注意右端点相同的区间要先从 $l$ 最小的开始更新。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,MOD=1e9+7;
struct Node { int x,v; } a[MAXN];
ll f[MAXN],s[MAXN];
int n,l[MAXN],r[MAXN];
vector <int> op[MAXN];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i].x,&a[i].v);
	sort(a+1,a+n+1,[&](auto i,auto j){ return i.v<j.v; });
	map <int,int> q;
	for(int i=1,t=0;i<=n;++i) {
		if(a[i].x>t) q[t=a[i].x]=i;
		l[i]=q.lower_bound(a[i].x)->second;
	}
	q.clear();
	for(int i=n,t=MOD;i>=1;--i) {
		if(a[i].x<t) q[t=a[i].x]=i;
		r[i]=(--q.upper_bound(a[i].x))->second;
		op[r[i]].push_back(l[i]);
	}
	f[0]=s[0]=1;
	for(int i=1;i<=n;++i) {
		s[i]=s[i-1];
		sort(op[i].begin(),op[i].end());
		for(int k:op[i]) {
			f[i]=(f[i]+s[i]+MOD-(k>1?s[k-2]:0))%MOD;
			s[i]=(s[i-1]+f[i])%MOD;
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}
```

---

## 作者：hanjinghao (赞：1)

# 思路

建立一个以 $ V $ 为横坐标，$ X $ 为纵坐标的坐标系。如果 $ i $ 被染色后能直接使 $ j $ 被染色，即 $ i $ 追上 $ j $ 或 $ j $ 追上 $ i $，那么 $ (v_i,x_i) $ 和 $ (v_j,x_j) $ 的连线斜率为负。如果 $ i $ 被染色后能间接使 $ j $ 被染色，即被 $ i $ 染色的点把 $ j $ 染上了色，那么 $ (v_j,x_j) $ 一定能通过一条斜率单调递增并且均为负的路径到达 $ (v_i,x_i) $。

把所有点按 $ v_i $ 从小到大排序。设 $ l_i $ 为 $ i $ 左边的编号最小的与 $ i $ 连线斜率为负（即纵坐标大于 $ x_i $）的点，$ r_i $ 为 $ i $ 右边的编号最大的与 $ i $ 连线斜率为负（即纵坐标小于 $ x_i $）的点。可以证明，$ [l_i,r_i] $ 这个区间内所有的点都会在 $ i $ 被染色后直接或间接被染色。先将 $ x_i $ 离散化，然后用树状数组即可求出 $ l_i $ 和 $ r_i $。

现在问题变成了这样：有 $ n $ 条线段，第 $ i $ 条线段的左端点为 $ l_i $，右端点为 $ r_i $。你需要选择若干条线段，使 $ 1 $ 到 $ n $ 中的每个点都至少被一条线段覆盖到。问有多少种选择方式。

如果存在 $ i $、$ j $，使得 $ l_i \lt l_j $ 且 $ r_i \gt r_j $，那么这个问题会非常麻烦。**但是，这种情况并不会出现！**

可以用反证法：如果 $ l_i \lt l_j $ ，那么 $ x_i \lt x_{l_i} \lt x_j $；如果 $ r_i \gt r_j $，那么 $ x_j \lt x_{r_i} \lt x_i $。显然，两者不会同时成立。得证。

排除了这种情况，我们就可以设计一个没有后效性的动规方程。

先把线段按右端点从小到大排序 (如果右端点相同，左端点小的排在前面)，然后令 $ f_i $ 表示恰好前 $ i $ 个点被覆盖的方案数。设当前线段为 $ [L,i] $，则 $ f_i $ 可以从 $ f_{L-1} $、$ f_L $、$ f_{L+1} $、......、$ f_i $ 转移过来。用前缀和可以把转移优化到 $ O(1) $。

总时间复杂度为 $ O(n \log n) $。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline const void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline const void writesp(const T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline const void writeln(const T x)
{
	write(x);
	putchar(10);
}

const int N = 2e5 + 5, P = 1e9 + 7;
pair < int, int > a[N];
int n, len, b[N], t[N], l[N], r[N], f[N], s[N];
vector < int > G[N];

inline void Add(int &x, int y)
{
	x += y;
	if (x >= P) x -= P;
}

inline bool cmp(const pair < int, int > &A, const pair < int, int > &B)
{
	return A.second < B.second;
}

inline int lowbit(int x)
{
	return x & (-x);
}

inline void Updr(int x, int val)
{
	while (x <= len)
	{
		if (val > t[x]) t[x] = val;
		x += lowbit(x);
	}
}

inline int Qryr(int x)
{
	int ret = 0;
	while (x)
	{
		if (t[x] > ret) ret = t[x];
		x -= lowbit(x);
	}
	return ret;
}

inline void Updl(int x, int val)
{
	while (x)
	{
		if (val < t[x]) t[x] = val;
		x -= lowbit(x);
	}
}

inline int Qryl(int x)
{
	int ret = 0x3f3f3f3f;
	while (x <= len)
	{
		if (t[x] < ret) ret = t[x];
		x += lowbit(x);
	}
	return ret;
}

int main()
{
	read(n);
	for (int i = 1; i <= n; ++i)
	{
		read(a[i].first);
		read(a[i].second);
		b[i] = a[i].first;
	}
	sort(b + 1, b + n + 1);
	len = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; ++i)
		a[i].first = lower_bound(b + 1, b + len + 1, a[i].first) - b;
	sort(a + 1, a + n + 1, cmp);
	for (int i = n; i; --i)
	{
		Updr(a[i].first, i);
		r[i] = Qryr(a[i].first);
	}
	memset(t, 0x3f, sizeof(t));
	for (int i = 1; i <= n; ++i)
	{
		Updl(a[i].first, i);
		l[i] = Qryl(a[i].first);
	}
	for (int i = 1; i <= n; ++i)
		G[r[i]].emplace_back(l[i]);
	for (int i = 1; i <= n; ++i)
		sort(G[i].begin(), G[i].end());
	f[0] = 1;
	s[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		s[i] = s[i - 1];
		for (auto j : G[i])
		{
			Add(f[i], s[i]);
			if (j > 1) Add(f[i], P - s[j - 2]);
			s[i] = s[i - 1];
			Add(s[i], f[i]);
		}
	}
	writeln(f[n]);
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

按照 $(X_i,V_i)$ 建立平面直角坐标系（不是 $(V_i,X_i)$），点 $i$ 能直接到达左上，右下的点。能到达的点对连线斜率一定为负数，斜率越小相遇越早。

考虑 $i$ 能间接到达的点。

+ 考虑右上，$i$ 贪心地先到达左上且最靠上，即 $X_j\le X_i,V_j$ 最大的 $j$，那么 $V_k\lt V_j$ 的右下点 $k$ 都能到达。
+ 考虑左下，$i$ 贪心地先到达右下且最靠下，即 $X_j\ge X_i,V_j$ 最小的 $j$，那么 $V_k\gt V_j$ 的左上点 $k$ 都能到达。

将所有点按照 $X$ 排序，求出 $V$ 的前缀最大值 $a$，后缀最小值 $b$，$i$ 能到达的点满足：

+ $k\le i,V_k\gt b_i$。
+ $k\ge i,V_k\lt a_i$。

问题转化为：求点对 $(P_1,\cdots,P_k)$ 数量，对于任意 $i\in[1,k)$ 不存在 $j\in(P_i,P_{i+1}),V_j\in(a_{P_i},b_{P_{i+1}})$。

设 $f_i$ 为取点 $i$ 使前缀 $1\cdots i$ 满足条件的方案数，$f_i=f_j+\cdots+f_{i-1}$，且 $j$ 递增。前缀和优化，双指针维护 $j$，`set` 记录 $k\in(j,i)$ 的所有 $V_k$ 判断合法即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 5;
const ll mod = 1e9 + 7;

int n,L = 1,R,b[N],c[N],d[N];
ll f[N],g[N],ans;
pair<int,int> a[N];
multiset<int> S;

void upd(int l,int r){
	while(R < r) ++R,S.insert(a[R].second);
	while(L > l) --L,S.insert(a[L].second);
	while(L < l) S.erase(S.find(a[L].second)),++L;
	while(R > r) S.erase(S.find(a[R].second)),--R;
}

bool chk(int j,int i){ return b[j] > c[i] ? 1 : S.lower_bound(b[j]) == S.upper_bound(c[i]); }

int main(){
	scanf("%d",&n);
	for(int i = 1,x,y;i <= n;++i) scanf("%d%d",&a[i].first,&a[i].second);
	sort(a + 1,a + n + 1);
	for(int i = 1;i <= n;++i) b[i] = max(b[i - 1],a[i].second);
	c[n + 1] = 2e9;
	for(int i = n;i >= 1;--i) c[i] = min(c[i + 1],a[i].second),d[i] = max(d[i + 1],a[i].second);
	f[0] = g[0] = 1;
	for(int i = 1,j = 0;i <= n;++i){
		while(!(upd(j + 1,i - 1),chk(j,i))) ++j;
		f[i] = (g[i - 1] - (j ? g[j - 1] : 0)) % mod;
		g[i] = (g[i - 1] + f[i]) % mod;
		if(d[i + 1] < b[i]) (ans += f[i]) %= mod;
	}
	printf("%lld\n",(ans + mod) % mod);
	return 0;
}
```

---

## 作者：peidi (赞：0)

前面很多题解都提到了建立笛卡尔坐标系（这里即平面直角坐标系），我来进行一些更详细且易于理解的阐释。

以速度为 $x$ 轴，初始位置为 $y$ 轴，建立笛卡尔坐标系。对于点 $i$，他的坐标为 $(V_{i},X_{i})$。那么两点的相遇时间就是两点连线斜率的绝对值，即两点连线斜率为负才会相遇，同时斜率越大（连线越平缓），相遇越早。

![1](https://cdn.luogu.com.cn/upload/image_hosting/zsjjqtdy.png)

对于上面这张图来说，按时间顺序相遇的依次是 $AE、BC、DE、AC、AB、DC$，这些都属于**直接相遇**。

接下来我们考虑**间接相遇**。以 $BD$ 两点为例，他们是不会直接相遇的，因为两点连线斜率为正。但是，他们都会与 $C$ 相遇，且由于 $BC$ 更平缓，$B$ 先与 $C$ 相遇，$C$ 再与 $D$ 相遇。因此，我们如果给 $B$ 染色，就会通过 $C$ 传递给 $D$，但是反过来不行，除非 $B$ 的左侧还存在一个高于点 $D$ 的点 $F$，$F$ 先与 $D$ 相遇，再与 $B$ 相遇，实现间接传递。

![2](https://cdn.luogu.com.cn/upload/image_hosting/ggltonqd.png)

假设 $A$ 为可以直接与 $B$ 相遇且速度最小的点，$C$ 为可以直接与 $B$ 相遇且速度最大的点。
1. 对于灰色区域的任意一点，我们可以让他直接与 $B$ 相遇，完成直接染色。

2. 对于紫色区域的任意一点 $M$，我们都可以让 $B$ 先与 $A$ 相遇，$A$ 与 $M$ 再相遇，从而完成间接染色。

3. 对于绿色区域的任意一点 $M$，我们都可以让 $B$ 先与 $C$ 相遇，$C$ 再与 $M$ 相遇，完成间接染色。

4. 对于黄色区域，因为 $AC$ 已经是速度最大或最小的能直接相遇的点，所以黄色区域里没有点。

5. 对于橙色区域中的点，既不能直接与 $B$ 相遇，又不能找到中继完成间接相遇，因此无法被染色。

综上，如果 $B$ 点被染色，那么紫色，绿色，灰色内的点一定会被直接或间接染色，也就是说，对于速度在 $V_{A}$，$V_{C}$ 之间的所有点，一定会被染色，而其他点一定不会被染色。

我们发现，**一个点能染到的点，是按照速度排序后一段连续的区间**。这个结论可以说是这道题的灵魂所在。

所以，我们只需要找到能与 $B$ 直接相遇且 $V$ 最小的，和能与 $B$ 直接相遇且 $V$ 最大的点，就能确定该点染色后能被染色的范围。而找这两个点是比较容易的，线段树二分，树状数组，或神奇的 $O(n)$ 做法均可。

那么，此问题就被转化为子区间覆盖总区间的方案数问题，利用单调性和前缀和，可将 dp 的复杂度由 $O(n_{}^{2})$ 降为 $O(n)$，前人之述备矣，这里不再展开。

---

## 作者：UKE_Automation (赞：0)

### AGC015E Mr.Aoki Incubator

[$\text{Link}$](https://atcoder.jp/contests/agc015/tasks/agc015_e)

首先先找一找题目中的性质，我们发现两个点染色后互相不会影响，那么每个人的贡献是独立的。考虑一个点染色后哪些点也会被染上，很显然左边比它快的和右边比它慢的都可以被染到；进一步的，此时右边所有染上颜色的依然可以染左边比它快的，左边也是同理。

所以如果令 $pre_i$ 表示速度前缀最大值，$suf_i$ 表示速度后缀最小值，那么对于一个 $i$，所有在 $i$ 左边且速度大于 $suf_i$ 的都能被染上，同理所有在 $i$ 右边且速度小于 $pre_i$ 的都能被染上。

考虑 dp，设 $dp_i$ 表示最后一次染色在 $i$，$[1,i]$ 已经染完的方案数。转移的时候枚举上一次染色的点 $j$，此时我们的条件是 $\forall x\in(j,i),a_x\notin[pre_j,suf_i]$。由于 $pre_j,suf_i$ 均单调不减，所以我们知道合法的 $j$ 一定是一段以 $i-1$ 为结尾的区间。那么我们用桶维护一下当前 $[pre_j,suf_i]$ 中数的个数，然后双指针计算出合法的区间，用前缀和计算一下即可。复杂度 $O(n\log n)$，瓶颈在离散化和排序。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
const int Mod = 1e9 + 7;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b, int P = Mod) {int res = 1; for(; b; a = 1ll * a * a % P, b >>= 1) if(b & 1) res = 1ll * res * a % P; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n;
struct node {
	int x, v;
}p[Maxn];
int t[Maxn], tot;
int dp[Maxn], sum[Maxn];
int pre[Maxn], suf[Maxn];
int b[Maxn], l, r, cnt;

void add(int x) {
	b[p[x].v]++;
	if(p[x].v <= r) cnt++;
	if(p[x].v < l) cnt--;
}

void del(int x) {
	b[p[x].v]--;
	if(p[x].v <= r) cnt--;
	if(p[x].v < l) cnt++;
}

void work(int tl, int tr) {
	while(r < tr) r++, cnt += b[r];
	while(l < tl) cnt -= b[l], l++;
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n);
	for(int i = 1; i <= n; i++) read(p[i].x), read(p[i].v), t[++tot] = p[i].v;
	sort(t + 1, t + tot + 1); tot = unique(t + 1, t + tot + 1) - t - 1;
	for(int i = 1; i <= n; i++) p[i].v = lower_bound(t + 1, t + tot + 1, p[i].v) - t;
	sort(p + 1, p + n + 1, [](node x, node y){return x.x < y.x;});
    pre[0] = 0, suf[n + 1] = n + 1;
	for(int i = 1; i <= n; i++) pre[i] = max(pre[i - 1], p[i].v);
    for(int i = n; i >= 1; i--) suf[i] = min(suf[i + 1], p[i].v);
	dp[0] = sum[0] = 1; l = r = 0;
	for(int i = 1, j = 0; i <= n; i++) {
		work(pre[j], suf[i]);
		while(cnt > 0) j++, del(j), work(pre[j], suf[i]);
		dp[i] = sum[i - 1];
		if(j) sub(dp[i], sum[j - 1]);
		sum[i] = Add(sum[i - 1], dp[i]);
		add(i);
	}
	int mx = 0, ans = 0;
	for(int i = n; i >= 1; i--) {
		if(pre[i] > mx) pls(ans, dp[i]);
		chkmax(mx, p[i].v);
	}
	write(ans);
	Usd();
	return 0;
}

```

---

## 作者：Sktic (赞：0)

[AT2383 [AGC015E] Mr.Aoki Incubator ](https://www.luogu.com.cn/problem/AT2383)

首先我们可以发现，在经过足够长时间的运动后，数轴上的所有点一定是按照速度排列的。（可以感性理解）



于是我们可以发现，如果我们将点 $i$ 染色，其速度为 $v_i$，初始位置为 $x_i$，它能染色的点为所有满足当 $v_k>v_i,x_k<x_i$ 或 $v_k<v_i,x_k>x_i$ 的点，考虑证明。因为若存在一个点 $k$ 使得 $v_k>v_i,x_k<x_i$，那么由于 $x_k<x_i$ 可知点 $k$ 在开始时处于点 $i$ 的左端，但是经过足够长的时间后，因为 $v_k>v_i$ ，所以点 $k$ 一定能追上点 $i$ 到它的右边。因为点 $k$ 从点 $i$ 的左侧到了其右侧，所以一定会被 $i$ 染色。对于另一种情况同理可得。



于是我们考虑先按速度排序所有点，再将每个点能染色的点所在的区间 $[l,r]$ 求出来，将问题转换为将若干段区间覆盖总区间的方案数。



我们考虑采用 $\text{dp}$ 解决此问题。设 $dp_i$ 为仅染色 $1\sim i$ 个点，在必定染色点 $i$ 时覆盖区间 $1\sim r_i$ 的方案数。可以很容易得到状态转移方程：
$$
dp_i=\sum_{j=1}^{i-1}dp_j[l_i-1\le r_j]
$$
但是这样转移是 $O(n^2)$ 的，显然会寄，考虑优化。



先前我们已经按照 $v$ 对所有的点进行了一边排序，我们可以发现，由于排序后的 $v$ 单调递增，因而它可以染色的点所在区间 $[l,r]$ 因为速度的关系也必定是单调递增的。于是我们可以发现，若转移 $dp_i$ 时有一个 $j$ 满足 $l_1-1\le r_j$，那因为 $r$ 单调递增的性质可以发现点 $j+1,j+2,\cdots,i-1$ 也必然都满足条件，因此我们只需要找到一个满足条件的最小下标 $t$ ，使得：
$$
dp_i=\sum_{i=t}^{i-1}dp_j
$$
这样看起来虽然没有实质性优化，但我们可以发现 $t$ 存在一个优美的性质，随着 $i$ 的增加，由于 $v_i$ 与 $l_i$ 在增加，$t$ 也是升序的。因此我们只需要采用离散化+前缀和优化，在 $\text{dp}$ 过程中维护 $t$ 即可，转移可以做到 $O(1)$，总 $\text{dp}$ 过程时间复杂度 $O(n)$ 。



实现复杂度为 $O(n\log n)$，瓶颈在于排序。



AC Code（代码较丑）:

```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
const int mod=1e9+7;
typedef long long ll;
struct node
{
	ll x,v;
	bool operator<(const node &b)const
	{
		return (v==b.v)?x<b.x:v<b.v;
	}
}a[maxn];
int tmp[maxn],num[maxn];
int l[maxn],r[maxn];
ll dp[maxn],sum[maxn];
int top;
inline void upd(int x)
{
	while(l[x]-1>r[top])
		top++;
	return;
}
inline ll read()
{
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
int main()
{
	int n;
	n=read();
	for(int i=1;i<=n;i++)
		a[i].x=read(),a[i].v=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		tmp[i]=a[i].x;
	sort(tmp+1,tmp+n+1);
	dp[0]=sum[0]=1;
	for(int i=1;i<=n;i++)
		a[i].x=lower_bound(tmp+1,tmp+n+1,a[i].x)-tmp,num[a[i].x]=i;
	for(int i=1;i<=n;i++)
		l[n-i+1]=((i==1)?num[n]:min(num[n-i+1],l[n-i+2])),r[i]=max(num[i],r[i-1]);
	for(int i=1;i<=n;i++)
	{
		upd(i);
		dp[i]=(sum[i-1]-sum[top-1]+mod)%mod;
		sum[i]=(dp[i]+sum[i-1]+mod)%mod;
	}
	while(n>r[top])
		top++;
	ll ans=(sum[n]-sum[top-1]+mod)%mod;
	printf("%lld",ans);
	return 0;
}
```



---

