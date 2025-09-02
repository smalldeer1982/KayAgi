# Omsk Metro (hard version)

## 题目描述

This is the hard version of the problem. The only difference between the simple and hard versions is that in this version $ u $ can take any possible value.

As is known, Omsk is the capital of Berland. Like any capital, Omsk has a well-developed metro system. The Omsk metro consists of a certain number of stations connected by tunnels, and between any two stations there is exactly one path that passes through each of the tunnels no more than once. In other words, the metro is a tree.

To develop the metro and attract residents, the following system is used in Omsk. Each station has its own weight $ x \in \{-1, 1\} $ . If the station has a weight of $ -1 $ , then when the station is visited by an Omsk resident, a fee of $ 1 $ burle is charged. If the weight of the station is $ 1 $ , then the Omsk resident is rewarded with $ 1 $ burle.

Omsk Metro currently has only one station with number $ 1 $ and weight $ x = 1 $ . Every day, one of the following events occurs:

- A new station with weight $ x $ is added to the station with number $ v_i $ , and it is assigned a number that is one greater than the number of existing stations.
- Alex, who lives in Omsk, wonders: is there a subsegment $ \dagger $ (possibly empty) of the path between vertices $ u $ and $ v $ such that, by traveling along it, exactly $ k $ burles can be earned (if $ k < 0 $ , this means that $ k $ burles will have to be spent on travel). In other words, Alex is interested in whether there is such a subsegment of the path that the sum of the weights of the vertices in it is equal to $ k $ . Note that the subsegment can be empty, and then the sum is equal to $ 0 $ .

You are a friend of Alex, so your task is to answer Alex's questions.

 $ \dagger $ Subsegment — continuous sequence of elements.

## 说明/提示

Explanation of the first sample.

The answer to the second question is "Yes", because there is a path $ 1 $ .

In the fourth question, we can choose the $ 1 $ path again.

In the fifth query, the answer is "Yes", since there is a path $ 1-3 $ .

In the sixth query, we can choose an empty path because the sum of the weights on it is $ 0 $ .

It is not difficult to show that there are no paths satisfying the first and third queries.

## 样例 #1

### 输入

```
1
8
+ 1 -1
? 1 1 2
? 1 2 1
+ 1 1
? 1 3 -1
? 1 1 1
? 1 3 2
? 1 1 0```

### 输出

```
NO
YES
NO
YES
YES
YES```

## 样例 #2

### 输入

```
1
7
+ 1 -1
+ 2 -1
+ 2 1
+ 3 -1
? 5 2 2
? 3 1 -1
? 5 4 -3```

### 输出

```
NO
YES
YES```

# 题解

## 作者：寄风 (赞：16)

直接推结论+最近公共祖先。

先考虑 $k > 0$，$k < 0$ 同理（就是乘 $-1$），这里就不再阐述。

有一个比较核心（神奇）的结论：如果一个子段和为 $sum$，则 $[0,sum]$ 之内的数全都可以在这个子段的子段中找到。

我们感性理解一下：

和为 $sum$，则至少有 $sum$ 个值为 $1$ 的节点。反向考虑，增加一个权值为 $1$ 的节点贡献为 $1$，则删除这个节点对答案的的贡献为 $-1$。而在最坏情况下（只有 $sum$ 个值为 $1$ 的节点），最多可以把答案减少 $sum$。所以 $[0,sum]$ 区间内都是可以取到的。

所以只要看最大（$k \ge 0$）和最小（$k < 0$）子段和即可。

然后就比较经典了。

维护一个点的最大、最小前驱，最大、最小后续，子段最小、最大值，和，然后用倍增求 $\operatorname{LCA}$ 的方法倍增跳，在这个过程中多开一个数组 $f$ 合并信息并更新即可。

时间、空间复杂度均为 $O(n\log n)$。

## 代码：

```
#include <bits/stdc++.h>
using namespace std;
//#define int long long
struct node{
	int maxlast , minlast , maxnext , minnext , maxn , minn , sum;
	node(){
		maxlast = minlast = maxnext = minnext = maxn = minn = sum = 0;
	}
	node operator +(const node &a) const{
		node ans;
		ans.maxlast = max(maxlast , sum + a.maxlast);
		ans.minlast = min(minlast , sum + a.minlast);
		ans.maxnext = max(a.maxnext , a.sum + maxnext);
		ans.minnext = min(a.minnext , a.sum + minnext);
		ans.maxn = max(maxn , max(a.maxn , maxnext + a.maxlast));
		ans.minn = min(minn , min(a.minn , minnext + a.minlast));
		ans.sum = sum + a.sum;
		return ans;
	}
	node reverse(){
		node ans = *this;
		swap(ans.maxlast , ans.maxnext);
		swap(ans.minlast , ans.minnext);
		return ans;
	}
};	
struct qu{
	int u , v , w;
};
inline void solve(){
	int n;
	cin >> n;
	vector <int> p{-1} , x{1};
	vector <qu> xuyiluo2;
	for(int i = 1;i <= n;i++){
		char op;
		cin >> op;
		if(op == '+'){
			int u , vv;
			cin >> u >> vv;
			u--;
			p.push_back(u);
			x.push_back(vv);
		}
		else{
			int u , v , w;
			cin >> u >> v >> w;
			u--;
			v--;
			xuyiluo2.push_back(qu{u , v , w});
		}
	}
	n = p.size();
	const int up = __lg(n);
	vector fa(up + 1 , vector <int> (n , -1));
	vector f(up + 1 , vector <node> (n)); 
	vector <int> dep(n);
	
	for(int i = 0;i < n;i++){
		if(i > 0) dep[i] = dep[p[i]] + 1;
		fa[0][i] = p[i];
		if(x[i] == 1) f[0][i].maxn = f[0][i].maxlast = f[0][i].maxnext = f[0][i].sum = 1;
		else f[0][i].minn = f[0][i].minlast = f[0][i].minnext = f[0][i].sum = -1;
		for(int j = 0;(1 << (j + 1)) <= dep[i] + 1;j++){
			fa[j + 1][i] = fa[j][fa[j][i]];
			f[j + 1][i] = f[j][i] + f[j][fa[j][i]];
		}
	}
	auto work = [&] (int x , int y){		
		if(dep[x] < dep[y]) swap(x , y);
		node l , r;
		int up = log2(n);
		for(int i = up;i >= 0;i--){
			if(dep[x] - dep[y] >= (1 << i)){
				l = l + f[i][x];
				x = fa[i][x];
			}
		}
		if(x == y){
			return l + f[0][x];
		}
		for(int i = up;i >= 0;i--){
			if(fa[i][x] != fa[i][y]){
				l = l + f[i][x];
				r = r + f[i][y];
				x = fa[i][x];
				y = fa[i][y];
			}
		}
		return l + f[1][x] + f[0][y] + r.reverse();
	};
	for(auto [u , v , k] : xuyiluo2){
		auto ans = work(u , v);
		if((k >= 0 && k <= ans.maxn) || (k < 0 && k >= ans.minn)){
			puts("Yes");
		}
		else{
			puts("No");
		}
	}
}
int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}
```

---

## 作者：iyaang (赞：2)

[可爱的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17578101.html)

[题目链接](https://www.luogu.com.cn/problem/CF1843F2)

都这么强？都会倍增？

首先结论是肯定的：记路径上最大子段和为 $maxx$，最小子段和为 $minx$，有解当且仅当 $minx \leq k \leq maxx$，所以要做的是维护最大/最小前缀和，最大/最小后缀和，区间和，最大/最小子段和。其他几篇题解都证过了我们就直接跳过。看到这种**动态**加点和**路径**信息维护不应该直接无脑上 LCT 吗？注意 splay 区间翻转的时候还要交换前缀和与后缀和即可，和 splay 维护区间子段和是一样的，可以参考 [GSS6](https://www.luogu.com.cn/problem/SP4487)。因为保证路径合法，所以动态加点是假的，先把操作离线建好整棵树，这样 LCT 需要实现的只有 split 操作。于是我们做到了 $\mathcal O(n \log n)$，~~甚至可以强制在线~~。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
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
        putchar(ch);
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
    TT inline void cmax(T &a,T b) {a=a>b?a:b;}
    TT inline void cmin(T &a,T b) {a=a<b?a:b;}
    TT inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
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
    static const int mod=1e9+7;
    static const int bas=131;
    
    struct node
    {
    	int sum,minx,premin,sufmin,maxx,premax,sufmax;
    	node(int Val=0) {sum=minx=premin=sufmin=maxx=premax=sufmax=Val;}
    	inline friend node operator + (node l,node r)
    	{
    		node res;
    		res.sum=l.sum+r.sum;
    		res.premin=min(l.premin,l.sum+r.premin),res.premax=max(l.premax,l.sum+r.premax);
    		res.sufmin=min(r.sufmin,r.sum+l.sufmin),res.sufmax=max(r.sufmax,r.sum+l.sufmax);
    		res.minx=min({l.minx,r.minx,l.sufmin+r.premin}),res.maxx=max({l.maxx,r.maxx,l.sufmax+r.premax});
    		return res;
		}
	};
    
    namespace Link_Cat_Tree
	{
	    int fa[MAX],ch[MAX][2],tag[MAX],siz[MAX],val[MAX];
	    node lmy[MAX];
	    inline bool get(int i)      {return ch[fa[i]][1]==i;}
	    inline bool noroot(int i)   {return ch[fa[i]][get(i)]==i;}
	    inline void pushup(int i)   {siz[i]=siz[ch[i][0]]+siz[ch[i][1]]+1,lmy[i]=lmy[ch[i][0]]+(node){val[i]}+lmy[ch[i][1]];}
	    inline void down(int i)     {if(!i) return; tag[i]^=1,Swp(ch[i][0],ch[i][1]),Swp(lmy[i].premin,lmy[i].sufmin),Swp(lmy[i].premax,lmy[i].sufmax);}
	    inline void pushdown(int i) {if(tag[i]) down(ch[i][0]),down(ch[i][1]),tag[i]=0;}
	    inline void pushall(int i)  {if(noroot(i)) pushall(fa[i]); pushdown(i);}
	    inline void rotate(int x)
	    {
	        int y=fa[x],z=fa[y];
	        bool k1=get(x),k2=get(y);
	        if(noroot(y)) ch[z][k2]=x; fa[x]=z;
	        ch[y][k1]=ch[x][!k1],fa[ch[x][!k1]]=y;
	        ch[x][!k1]=y,fa[y]=x;
	        pushup(y),pushup(x);
	    }
	    inline void splay(int x)
	    {
	        pushall(x);
	        while(noroot(x))
	        {
	            int y=fa[x];
	            if(noroot(y)) (get(x)^get(y))?rotate(x):rotate(y);
	            rotate(x);
	        }
	    }
	    inline void access(int x)      {for(int y=0;x;y=x,x=fa[x]) splay(x),ch[x][1]=y,pushup(x);}
	    inline void makeroot(int x)    {access(x),splay(x),down(x);}
	    inline int  findroot(int x)    {access(x),splay(x); while(ch[x][0]) pushdown(x),x=ch[x][0]; return splay(x),x;}
	    inline void split(int x,int y) {makeroot(x),access(y),splay(y);}
	    inline void link(int x,int y)  {makeroot(x); if(findroot(y)!=x) fa[x]=y;}
	    inline void cut (int x,int y)  {makeroot(x); if(findroot(y)==x&&fa[y]==x&&!ch[y][0]) fa[y]=ch[x][1]=0,pushup(x);}
	}
	using namespace Link_Cat_Tree;
	
	int T,n,all,con;
	char c;
	int x,y,z;
	struct qry{int x,y,z,ans;}q[MAX];
	
    inline void lmy_forever()
    {
    	read(T);
    	while(T--)
    	{
    		for(int i=1;i<=all;++i) fa[i]=ch[i][0]=ch[i][1]=tag[i]=siz[i]=val[i]=0,lmy[i]=(node){0};
    		read(n),all=1,con=0;
    		val[1]=1,siz[1]=1,lmy[1]=(node){1};
    		for(int i=1;i<=n;++i)
    		{
    			do c=getchar(); while(c!='+'&&c!='?');
    			if(c=='+') read(x,z),++all,val[all]=z,lmy[all]=(node){z},fa[all]=x,siz[all]=1;
    			if(c=='?') ++con,read(q[con].x,q[con].y,q[con].z);
			}
    		for(int i=1;i<=con;++i) {split(q[i].x,q[i].y); if(lmy[q[i].y].minx<=q[i].z&&q[i].z<=lmy[q[i].y].maxx) puts("YES"); else puts("NO");}
		}
        return;
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

## 作者：Benzenesir (赞：2)

> 动态给出一棵 $n$ 个节点的树，每个节点有一个权值，权值为 $1$ 或 $-1$，给出若干次询问，询问 $u$，$v$ 之间的路径上是否有一个子串的和为 $k$。   
> $n\in [1,10^5]$ 。

这里加一减一，则增长是连续的，所以我们要找到最大的和最小的子段和，然后判断是不是在这个区间里就可以了。

这里使用了倍增实现。

```
inline int logx(int n) {  
  int result = 0;  
  if(n&0xffff0000) {result += 16; n >>= 16; }  
  if(n&0x0000ff00) {result += 8; n >>= 8; }  
  if(n&0x000000f0) {result += 4; n >>= 4; }  
  if(n&0x0000000c) {result += 2; n >>= 2; }  
  if(n&0x00000002) {result += 1; n >>= 1; }  
  return result; 
}
const int maxN = 2 * 1e5 + 10;
int n;
int acc[maxN][20], dep[maxN], va[maxN], fa[maxN];
struct node {
	int minx, maxx;
	int mal, mar;
	int mil, mir, sum;
} f[maxN][20], g[maxN];

node update(node x, node y) {
	node z;
	z.mal = max(x.mal, y.mal + x.sum);
	z.mar = max(y.mar, x.mar + y.sum);
	z.mil = min(x.mil, y.mil + x.sum);
	z.mir = min(y.mir, x.mir + y.sum);
	z.minx = min(x.minx, min(y.minx, x.mir + y.mil));
	z.maxx = max(x.maxx, max(y.maxx, x.mar + y.mal));
	z.sum = x.sum + y.sum;
	return z;
}

void add(int x) {
	for (int i = 0, v = acc[x][i]; v; v = acc[x][++i]) acc[x][i + 1] = acc[v][i];
	dep[x] = dep[acc[x][0]] + 1;
	g[x].minx = min(va[x], 0), g[x].maxx = max(va[x], 0);
	g[x].mal = g[x].mar = max(0, va[x]);
	g[x].mil = g[x].mir = min(0, va[x]);
	g[x].sum = va[x];
	f[x][0] = g[x];z
	for (int i = 0, v = acc[x][i]; dep[x] >= (1 << (i + 1)); ++i,v = acc[x][i]){
		f[x][i + 1] = update(f[x][i], f[v][i]);
	} 
}

inline int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int gap = dep[x] - dep[y], bit = logx(gap); gap; gap -= (1<<bit), bit = logx(gap)) x = acc[x][bit];
	for (int i = logx(dep[x]); ~i; --i) if (acc[x][i] != acc[y][i]) x = acc[x][i], y = acc[y][i];
	return (x == y) ? x : acc[x][0];
}

node get_chain(int u, int c) {
	node ans;
	ans.sum=-inf;
	int flag = 0;
	for(int x=dep[u]-dep[c],bit=logx(x);x>0;x-=(1<<(bit)),bit=logx(x)) {
		if(!flag)
			ans=f[u][bit],flag=1;
		else 
			ans=update(ans,f[u][bit]);
		u=acc[u][bit];
	}
	return ans;
}

void M_clear(){
	node p=node{0,0,0,0,0,0,0};
	fp(i,1,n){
		va[i]=0,dep[i]=0,fa[i]=0;
		met(acc[i],0);
		fp(j,0,20) f[i][j]=p;
		g[i]=p;
	}
}

void solve() {
	int op = rd();
	dep[1] = 1;
	n = 1;
	va[1]=1;
	g[n].minx = min(va[n], 0), g[n].maxx = max(va[n], 0);
	g[n].mal = g[n].mar = max(0, va[n]);
	g[n].mil = g[n].mir = min(0, va[n]);
	g[n].sum = va[n];
	f[n][0] = g[n];
	while (op--) {
		char ch = getchar();
		if (ch == '+') {
			fa[++n] = rd();
			acc[n][0] = fa[n];
			va[n] = rd();
			add(n);
		} else {
			int u = rd(), v = rd(), k = rd();
			int c = lca(u, v);
			if (dep[u] < dep[v]) swap(u, v);
			node ans;
			if(c==u||c==v){
				ans=get_chain(u,c);
				if(ans.sum==-inf) ans=g[c];
				else ans=update(ans,g[c]);
			}
			else {
				ans=get_chain(u,c);
				ans=update(ans,g[c]);
				node p=get_chain(v,c);
				swap(p.mil,p.mir);
				swap(p.mar,p.mal);
				ans=update(ans,p);
			}
			if(ans.minx<=k&&ans.maxx>=k)
				cout << "YES" << endl;
			else cout << "NO" << endl;
		}
	}
	M_clear();
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

给定一颗带点权且只可能为 $1$ 或 $-1$ 的树，若干次询问顶点 $x$ 和顶点 $y$ 之间是否存在点权和为 $k$ 的子路径。

## 题目分析

存在对于我们来讲是个很抽象的玩意，一般出现这个字眼，我们都要设法通过题目中的特殊性质，将条件转换成任意或者是其它我们熟悉的格式。

显然这道题中一个突出的特点就是点权只可能是 $1$ 或 $-1$。这给我们带来的性质其实也很好想，就是所有的子路径权值和在值域上是一段连续的区间。因为一条子路径权值和总可以表示成另一个权值和在数轴上往相邻位置跳一下。

这下就是看这个区间是否包含了 $k$。这下我们就熟悉了，只要求这个区间的左右端点就行，那不就是最大、最小子段和吗？不带修改，倍增能做到 $O(n\log n)$，树剖线段树能做到 $O(n\log^2 n)$。不过后者还能支持路径修改，拓展性强，只是码量比倍增大亿点。本怨种写了后者。

这里注意，无论写哪一种，要注意自己维护的前后缀在树上体现为哪种朝向，以及合并时的先后次序，否则就要吃罚时咯！

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=2e18,mod=1e9+7;
using namespace std;
int T=read(),n,m,h[N],to[N<<1],nxt[N<<1],cnt;
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
int siz[N],dep[N],son[N],f[N],val[N],top[N],dfn[N],Id[N],Time;
struct node{
	int x,y,k;
}q[N];
int cq;
inline  void clear(){
	rep(i,1,n)h[i]=val[i]=son[i]=0;
	cnt=Time=cq=n=0;
}
inline void dfs(int x,int fa){
	dep[x]=dep[fa]+1,siz[x]=1,f[x]=fa;
	e(x)dfs(y,x),siz[x]+=siz[y],son[x]=siz[y]>son[x]?y:son[x];
}
inline void Dfs(int x,int low){
	top[x]=low,dfn[x]=++Time,Id[Time]=x;
	if(son[x])Dfs(son[x],low);
	e(x)if(y^son[x])Dfs(y,y);
}
struct seg{
	int px,pn,sx,sn,mx,mn,sm;
}xd[N<<2];
inline seg getup(seg a,seg b){
	seg c;
	c.px=max(a.px,a.sm+b.px),c.pn=min(a.pn,a.sm+b.pn);
	c.sx=max(b.sx,b.sm+a.sx),c.sn=min(b.sn,b.sm+a.sn);
	c.sm=a.sm+b.sm;
	c.mx=max({a.mx,b.mx,a.sx+b.px});
	c.mn=min({a.mn,b.mn,a.sn+b.pn});
	return c;
}
inline void build(int x,int l,int r){
	if(l==r){
		if(val[Id[l]]==1)xd[x]={1,0,1,0,1,0,1};
		else xd[x]={0,-1,0,-1,0,-1,-1};
		return;
	}build(lc),build(rc),xd[x]=getup(xd[L],xd[R]);
}
inline seg query(int x,int l,int r,int Ll,int Rr){
	if(OK)return xd[x];
	if(Rr<=mid)return query(lc,Ll,Rr);
	if(Ll>mid)return query(rc,Ll,Rr);
	return getup(query(lc,Ll,Rr),query(rc,Ll,Rr));
}
inline seg rev(seg a){
	swap(a.px,a.sx),swap(a.sn,a.pn);
	return a;
}
inline Pi get(int x,int y){
	seg l,r;
	l=r={0,0,0,0,0,0,0};
	while(top[x]^top[y]){
		if(dep[top[x]]>dep[top[y]]){
			l=getup(l,rev(query(Root,dfn[top[x]],dfn[x])));
			x=f[top[x]];
		}
		else {
			r=getup(query(Root,dfn[top[y]],dfn[y]),r);
			y=f[top[y]];
		}
	}
	if(dep[x]>=dep[y])l=getup(l,rev(query(Root,dfn[y],dfn[x])));
	else r=getup(query(Root,dfn[x],dfn[y]),r);
	l=getup(l,r);
	return {l.mn,l.mx};
}
signed main(){
	while(T--){
		m=read(),n=1;
		val[1]=1;
		for(int i=1,x;i<=m;i++){
			char opt;
			cin >>opt;
			if(opt=='+'){
				x=read(),val[++n]=read();
				add(x,n);
			}else {
				cq++;
				q[cq].x=read(),q[cq].y=read(),q[cq].k=read();
			}
		}
		dfs(1,0),Dfs(1,1),build(Root);
		rep(i,1,cq){
			Pi k=get(q[i].x,q[i].y);
			if(q[i].k==0||(q[i].k>=k.first&&q[i].k<=k.second))cout <<"Yes\n";
			else cout <<"No\n";
		}
		clear();
	}
	return 0;
}
```


---

## 作者：鲤鱼江 (赞：1)

因为一些奇怪的原因，这题改了我两个小时。

这个题的结论好像已经普及了，所以一眼就看出来了做法，具体来讲就是：若只考虑 $k$ 为正数，则可以凑出 $k$ 当且仅当最大子段和大于等于 $k$。

考虑证明一下该结论：（定义最大子段和为 $maxx$）

+ 若凑出了 $k$ 明显最大子段和已经大于等于 $k$。
+ 因为只有 $1$ 和 $-1$ 两种权值，所以最大子段和的变化定是连续的，即若要变化到 $maxx$ 首先得变化到 $maxx-1$，所以得证一定能凑出 $k$。

综上得证充要性，如果有负数，再求个最小子段和就行了。

注意清空不能只清空到 $n$。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader& operator >> (char& c) {c=getchar();while(c==' '||c=='\n')c=getchar();return *this;}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer& operator << (const char* str){int cur=0;while(str[cur])putchar(str[cur++]);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n' 
#define ls now<<1
#define rs now<<1|1
#define cin Fastio :: cin
#define cout Fastio :: cout

const int N=5e5+10;
struct edge{
	int to,ne;
	edge(int to=0,int ne=0):
		to(to),ne(ne){;}
}a[N<<1];
struct Query{int x,y,k;}q[N]; 
int n,val[N],m,h[N],cnt,dep[N],siz[N],son[N],top[N],id[N],idx,T,father[N],tot,ct,w[N];
char opt;

void clear(){
	for(int i=1;i<=n+10;++i) w[i]=h[i]=val[i]=dep[i]=siz[i]=son[i]=top[i]=id[i]=father[i]=0;
	idx=cnt=tot=ct=0;
}

struct node{
	int pre,suf,sum,ans;
	node(int v=0){pre=suf=ans=max(v,0);sum=v;}
	node operator +(const node &t)const{
		node z;
		z.sum=sum+t.sum;
		z.pre=max(pre,sum+t.pre);
		z.suf=max(t.suf,suf+t.sum);
		z.ans=max(max(ans,t.ans),suf+t.pre);
		return z;
	}
};

struct Segment{
	node tr[N<<2];
	inline void pushup(int now){tr[now]=tr[ls]+tr[rs];}
	void build(int now,int l,int r){
		if(l==r){tr[now]=node(w[l]);return ;}
		int mid=(l+r)>>1;build(ls,l,mid);build(rs,mid+1,r);pushup(now);
	}
	node ask(int now,int l,int r,int x,int y){
		if(now==1&&x>y) exit(114);
		if(x<=l&&r<=y) return tr[now];
		int mid=(l+r)>>1;
		if(y<=mid) return ask(ls,l,mid,x,y);
		else if(x>mid) return ask(rs,mid+1,r,x,y);
		else return ask(ls,l,mid,x,mid)+ask(rs,mid+1,r,mid+1,y);
	}
	inline node query(const int l,const int r){return ask(1,1,tot,l,r);}
}t1,t2;

void add(const int x,const int y){a[++cnt]=edge(y,h[x]);h[x]=cnt;}
void dfs1(int x,int y){
	dep[x]=dep[y]+1;siz[x]=1;father[x]=y;
	for(int i=h[x];i;i=a[i].ne){
		dfs1(a[i].to,x);
		siz[x]+=siz[a[i].to];
		son[x]=siz[a[i].to]>siz[son[x]]?a[i].to:son[x];
	}
}

void dfs2(int x,int topf){
	top[x]=topf;
	id[x]=++idx;
	w[idx]=val[x];
	if(son[x]) dfs2(son[x],topf);
	for(int i=h[x];i;i=a[i].ne){
		if(top[a[i].to]) continue;
		dfs2(a[i].to,a[i].to);
	}
}

inline node rever(const node &t){node z=t;swap(z.pre,z.suf);return z;}

int LCA(int x,int y){
	while(top[x]!=top[y]) dep[top[x]]<dep[top[y]]?y=father[top[y]]:x=father[top[x]];
	return dep[x]<dep[y]?x:y;
}

node Query(int x,int y,Segment &t){
	node res1=node();
	int fg1=0;
	while(top[x]!=top[y]){
		if(!fg1) res1=t.query(id[top[x]],id[x]);
		else res1=t.query(id[top[x]],id[x])+res1;fg1=1;
		x=father[top[x]];
	}
	if(x!=y&&id[y]+1>id[x]) exit(id[y]);
	if(x!=y) res1=fg1?t.query(id[y]+1,id[x])+res1:t.query(id[y]+1,id[x]);
	return res1;
}


bool Query(int x,int y,int k,Segment &t,int tag){
	int z=LCA(x,y);
	node ans=rever(Query(x,z,t))+node(tag*val[z])+Query(y,z,t);
	return ans.ans>=k;
}

int main(){
	cin>>T;
	while(T--){
		cin>>n;tot=1;val[1]=1;
		for(int i=1,x,y;i<=n;++i){
			cin>>opt>>x>>y;
			if(opt=='+') {add(x,++tot);val[tot]=y;}
			else {++ct;q[ct].x=x;q[ct].y=y;cin>>q[ct].k;}
		} 
		dfs1(1,0);dfs2(1,1);t1.build(1,1,tot);
		for(int i=1;i<=tot;++i) w[i]=-w[i];
		t2.build(1,1,tot);
		for(int i=1;i<=ct;++i){
			int tmp=0;
			if(q[i].k<0) tmp=Query(q[i].x,q[i].y,-q[i].k,t2,-1);
			else tmp=Query(q[i].x,q[i].y,q[i].k,t1,1);
			cout<<(tmp?"YES\n":"NO\n");
		}
		clear();
	}
	return 0;
}
```

---

## 作者：yangshengyu0719 (赞：0)

这道题其实就是一个树剖裸题，我们只用知道一段路径的最大子段和与最小子段和，若询问的值在两者间，那么存在；否则不存在。

原因是也很简单，因为每个位置的权值要么使一段的总和加 $1$，要么使它减 $1$，因此和在最大子段和与最小子段和的子段一定会存在。这里是我个人认为本题唯一需要动一点脑子的地方，可以自己多感悟一下。

问题至此就很简单了只需要会 [P4513 小白逛公园](https://www.luogu.com.cn/problem/P4513)（求最大子段和）和 [P3384 【模板】重链剖分/树链剖分](https://www.luogu.com.cn/problem/P3384) 这俩模板题就行了。

或许有人会问：题目中动态添加结点这一操作不好搞呀！其实这也很好避免，我们只要离线，先根据操作建好整棵树，再一次一次回答问题即可。

然后就没有然后了。

## 代码
```cpp
#include <bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=2e5+5;
int n,w[N],val[N];
int h[N],e[N],nx[N],idx;
int sz[N],son[N],prt[N],dep[N];
int tot,tid[N],top[N];
struct Query{int u,v,k;};
queue<Query> Q;
struct node{
	int l,r;
	int sum,lmax,rmax,maxn;
	int lmin,rmin,minn;
}T[N<<2];
node Empty={0,0,0,0,0,0,0,0,0};
void init(){
	for(int i=0;i<=tot;i++) h[i]=son[i]=0;
	for(int i=1;i<=(tot<<2);i++) T[i]=Empty;
	idx=0;w[tot=1]=1;
}
void AddEdge(int a,int b){e[++idx]=b;nx[idx]=h[a];h[a]=idx;}
void dfs1(int fa,int u,int deep){
	dep[u]=deep;
	prt[u]=fa;
	sz[u]=1;
	for(int i=h[u];i;i=nx[i]){
		int v=e[i];
		if(v!=prt[u]){
			dfs1(u,v,deep+1);
			sz[u]+=sz[v];
			if(sz[v]>=sz[son[u]]) son[u]=v;
		}
	}
}
void dfs2(int u,int t){
	tid[u]=++tot;
	top[u]=t;
	if(son[u]) dfs2(son[u],t);
	for(int i=h[u];i;i=nx[i]){
		int v=e[i];
		if(v!=prt[u]&&v!=son[u]) dfs2(v,v);
	}
}
node merge(node L,node R){
	node res=Empty;
	res.sum=L.sum+R.sum;
	res.lmax=max(L.lmax,L.sum+R.lmax);
	res.rmax=max(R.rmax,R.sum+L.rmax);
	res.maxn=max(max(L.maxn,R.maxn),L.rmax+R.lmax);
	res.lmin=min(L.lmin,L.sum+R.lmin);
	res.rmin=min(R.rmin,R.sum+L.rmin);
	res.minn=min(min(L.minn,R.minn),L.rmin+R.lmin);
	return res;
}
void build(int k,int l,int r){
	if(l==r){
		T[k].l=T[k].r=l;T[k].sum=val[l];
		T[k].lmax=T[k].rmax=T[k].maxn=max(val[l],0);
		T[k].lmin=T[k].rmin=T[k].minn=min(val[l],0);
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	T[k]=merge(T[ls],T[rs]);
	T[k].l=l,T[k].r=r;
}
node Get(int k,int L,int R){
	int l=T[k].l,r=T[k].r;
	if(L<=l&&r<=R) return T[k];
	int mid=(l+r)>>1;
	if(R<=mid) return Get(ls,L,R);
	else if(L>mid) return Get(rs,L,R);
	else return merge(Get(ls,L,R),Get(rs,L,R));
}
bool query(int u,int v,int k){
	if(!k) return true;
	node f1=Empty,f2=Empty;
	while(top[u]!=top[v]){
		int tu=top[u],tv=top[v];
		if(dep[tu]>dep[tv]) f1=merge(Get(1,tid[tu],tid[u]),f1),u=prt[tu];
		else f2=merge(Get(1,tid[tv],tid[v]),f2),v=prt[tv];
	}
	if(dep[u]>dep[v]) f1=merge(Get(1,tid[v],tid[u]),f1);
	else f2=merge(Get(1,tid[u],tid[v]),f2);
	swap(f1.lmax,f1.rmax);
	swap(f1.lmin,f1.rmin);
	f1=merge(f1,f2);
	return k>0?k<=f1.maxn:k>=f1.minn;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--){
		init();
		cin>>n;
		char op;int u,v,x;
		while(n--){
			cin>>op;
			if(op=='+'){cin>>u>>x;tot++;AddEdge(u,tot);w[tot]=x;}
			else{cin>>u>>v>>x;Q.push({u,v,x});}
		}
		dfs1(0,1,1);tot=0;dfs2(1,1);
		for(int i=1;i<=tot;i++) val[tid[i]]=w[i];
		build(1,1,tot);
		while(!Q.empty()){
			Query q=Q.front();Q.pop();
			cout<<(query(q.u,q.v,q.k)?"YES":"NO")<<'\n';
		}
	}
	return 0;
}
```

---

