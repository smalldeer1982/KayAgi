# X(or)-mas Tree

## 题目描述

'Twas the night before Christmas, and Santa's frantically setting up his new Christmas tree! There are $ n $ nodes in the tree, connected by $ n-1 $ edges. On each edge of the tree, there's a set of Christmas lights, which can be represented by an integer in binary representation.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1615D/cdce1a00879a13f8e819670249833036f71cf48d.png)He has $ m $ elves come over and admire his tree. Each elf is assigned two nodes, $ a $ and $ b $ , and that elf looks at all lights on the simple path between the two nodes. After this, the elf's favorite number becomes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of the values of the lights on the edges in that path.

However, the North Pole has been recovering from a nasty bout of flu. Because of this, Santa forgot some of the configurations of lights he had put on the tree, and he has already left the North Pole! Fortunately, the elves came to the rescue, and each one told Santa what pair of nodes he was assigned $ (a_i, b_i) $ , as well as the parity of the number of set bits in his favorite number. In other words, he remembers whether the number of $ 1 $ 's when his favorite number is written in binary is odd or even.

Help Santa determine if it's possible that the memories are consistent, and if it is, remember what his tree looked like, and maybe you'll go down in history!

## 说明/提示

The first test case is the image in the statement.

One possible answer is assigning the value of the edge $ (1, 2) $ to $ 5 $ , and the value of the edge $ (2, 5) $ to $ 3 $ . This is correct because:

- The first elf goes from node $ 2 $ to node $ 3 $ . This elf's favorite number is $ 4 $ , so he remembers the value $ 1 $ (as $ 4 $ has an odd number of $ 1 $ bits in its binary representation).
- The second elf goes from node $ 2 $ to node $ 5 $ . This elf's favorite number is $ 3 $ , so he remembers the value $ 0 $ (as $ 3 $ has an even number of $ 1 $ bits in its binary representation).
- The third elf goes from node $ 5 $ to node $ 6 $ . This elf's favorite number is $ 7 $ , so he remembers the value $ 1 $ (as $ 7 $ has an odd number of $ 1 $ bits in its binary representation).
- The fourth elf goes from node $ 6 $ to node $ 1 $ . This elf's favorite number is $ 1 $ , so he remembers the value $ 1 $ (as $ 1 $ has an odd number of $ 1 $ bits in its binary representation).
- The fifth elf goes from node $ 4 $ to node $ 5 $ . This elf's favorite number is $ 4 $ , so he remembers the number $ 1 $ (as $ 4 $ has an odd number of $ 1 $ bits in its binary representation).

Note that there are other possible answers.

## 样例 #1

### 输入

```
4
6 5
1 2 -1
1 3 1
4 2 7
6 3 0
2 5 -1
2 3 1
2 5 0
5 6 1
6 1 1
4 5 1
5 3
1 2 -1
1 3 -1
1 4 1
4 5 -1
2 4 0
3 4 1
2 3 1
3 3
1 2 -1
1 3 -1
1 2 0
1 3 1
2 3 0
2 1
1 2 1
1 2 0```

### 输出

```
YES
1 2 0
1 3 1
2 4 7
3 6 0
2 5 0
YES
1 2 1
1 3 0
1 4 1
4 5 1
NO
NO```

# 题解

## 作者：EricQian (赞：9)

>给定一颗 $n(n\le 2\times 10^5)$ 个点的带权树，一些权值已经确定而其他的没有确定（用 $-1$ 表示）。

>现在有 $m(m\le 2\times 10^5)$ 条信息表示 $u_i$ 到 $v_i$ 的路径上的权值 $\texttt{xor}$ 和的 popcount 为奇数还是偶数。

>请你构造出这样一棵树，或者输出无解。

我想到的内容：将路径上的异或和转化为两个点到根的距离的异或和，而且每改变路径上一条边的二进制位都会改变路径 popcount 的奇偶性。

之后就不 wei zhuo 啦。

核心思想：其实我们可以直接将一条边的权值根据其 popcount 的奇偶性改为 $0$ 或 $1$，因为任意一位改变都会影响奇偶性。

那么所有的异或值只能为 $0$ 或 $1$ 了。

如果两个点之间的路径奇偶性等于 $1$，则这两个点到根的路径 popcount 不等；反之，则相等。

因此转化为了这样一道题：有两个集合，第 $i$ 个条件表示 $u$ 和 $v$ 在同一个集合，或不在同一个集合，求出一组解。

这不就是 2-sat 或扩展域并查集裸题吗？直接跑即可。

输出方案的时候看一条边上的两个点是否在同一个集合，在即 $0$，不在即 $1$。

```cpp
#define Maxn 200005
typedef long long ll;
int T,n,m,tot=1;
int hea[Maxn<<1],nex[Maxn<<1],ver[Maxn<<1],edg[Maxn<<1],ans[Maxn<<1];
int fa[Maxn<<1];
bool Last[Maxn];
inline void add(int x,int y,int d)
{ ver[++tot]=y,nex[tot]=hea[x],hea[x]=tot,edg[tot]=d; }
int Find(int x){ return (fa[x]==x)?x:(fa[x]=Find(fa[x])); }
inline void merge(int x,int y) { fa[Find(x)]=Find(y); }
void dfs(int x,int F)
{
	 for(int i=hea[x];i;i=nex[i])
	 {
	 	 if(ver[i]==F) continue;
	 	 if(Last[x]!=Last[ver[i]]) ans[i]=ans[i^1]=1;
	 	 else ans[i]=ans[i^1]=0;
	 	 dfs(ver[i],x);
	 }
}
void solve()
{
 	 n=rd(),m=rd(),tot=1;
 	 for(int i=1;i<=n+n;i++) fa[i]=i,hea[i]=0;
 	 for(int i=1,x,y,d;i<n;i++)
	 {
	 	 x=rd(),y=rd(),d=rd(),add(x,y,d),add(y,x,d);
 	 	 if(d!=-1)
		 {
		 	 if(__builtin_popcount(d)&1) merge(x,y+n),merge(x+n,y);
		 	 else merge(x,y),merge(x+n,y+n);
		 }
	 }
 	 for(int i=1,x,y,d;i<=m;i++)
 	 {
 	 	 x=rd(),y=rd(),d=rd();
 	 	 if(d) merge(x+n,y),merge(x,y+n);
 	 	 else merge(x,y),merge(x+n,y+n);
	 }
	 for(int i=1;i<=n;i++) if(Find(i)==Find(i+n)) { printf("NO\n"); return; }
	 for(int i=1;i<=n;i++) Last[i]=(Find(i)<=n)?1:0;
 	 dfs(1,0);
 	 printf("YES\n");
 	 for(int i=2;i<=tot;i+=2)
	  	 if(edg[i]!=-1) printf("%d %d %d\n",ver[i],ver[i^1],edg[i]);
	  	 else printf("%d %d %d\n",ver[i],ver[i^1],ans[i]);
}
int main()
{
	 T=rd();
	 while(T--) solve();
	 return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：3)

和 E 一样也是妙妙题

#### 分析：

本题毒瘤在两处：

- 两点路径异或和

- popcount

对于第一个，我们知道设 $d(u)$ 表示 $u$ 到根的异或和，由于异或的良好性质 $u,v$ 路径的异或和等于 $d(u)\oplus d(v)$，这样我们把一连串数异或转成了两个数异或。

既然我们用了 $d$，我们就直接构造 $d$，最后根据 $d(fa)$ 和 $d(u)$ 就可以确定 $fa\Leftrightarrow u$ 这条边的权值。

但是此时我们还没解决 popcount 的问题。注意这里只关注其奇偶性，关键性的结论是：

$$count(x\oplus y)\equiv count(x)+ count(y)(\bmod\,2)$$

这个结论还是挺常见的，如果你没了解过很可能做不出（比如我www）。

如果你没学过，我们来证明一下：

我们任选 $x,y$ 的某一位，当其为 $0,0$ 的时候，在左边的式子里没有贡献，右边没有贡献；当其为 $1,1$ 的时候，在左边没有贡献，右边贡献 $2$；当其为 $0,1$（或 $1,0$）的时候，在左边贡献 $1$，右边贡献 $1$。所以在模 $2$ 意义下左右相等，而模 $2$ 意义其实就等价于奇偶性！

如果我们令 $count$ 的定义改为位数的奇偶性，则根据上面得出：

$$count(x\oplus y)=count(x)\oplus count(y)$$

你发现其实上面的那个 $d$ 可以直接改为 $count$，这样，不管是初始给的边，还是题目里的 $m$ 个限制，都是再给你两个点 $u,v$，使得 $count(u)$ 和 $count(v)$ 的值必须相同/不同。

这是一个经典的带权并查集模型，可以构造出一组合法的 $count$ 来，有了 $count$，就可以还原出所有的边权了，有意思的是我们发现我们可以通过只填 $0/1$ 来构造方案。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2e5+10;
int T,n,m,u,v,w;
int fa[MAXN],dsu[MAXN],dis[MAXN];
map<pi,int>f;
vector<int>e[MAXN];
int Find(int x){
	if(dsu[x]==x)return x;
	int tmp=dsu[x];dsu[x]=Find(tmp);dis[x]^=dis[tmp];return dsu[x]; 
}
void dfs(int u){
	for(auto v:e[u]){
		if(v==fa[u])continue;
		fa[v]=u;dfs(v);
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	f.clear();rep(i,1,n){
		e[i].clear();
		fa[i]=0;
		dsu[i]=i;dis[i]=0;
	}
	rep(i,1,n-1){
		scanf("%d%d%d",&u,&v,&w);
		e[u].pb(v);e[v].pb(u);
		if(w!=-1)f[mp(u,v)]=f[mp(v,u)]=w;
	}
	dfs(1);
	int flag=0;
	for(auto tmp:f){
		int u=tmp.fr.fr,v=tmp.fr.se,w=tmp.se;
		w=__builtin_popcount(w)&1;
		int a=Find(u),b=Find(v);
		if(a==b){
			if((dis[u]^dis[v])!=w){
				flag=1;
			}
		}else{
			dis[a]=dis[u]^dis[v]^w;
			dsu[a]=b;
		}
	}
	rep(i,1,m){
		scanf("%d%d%d",&u,&v,&w);
		int a=Find(u),b=Find(v);
		if(a==b){
			if((dis[u]^dis[v])!=w){
				flag=1;
			}
		}else{
			dis[a]=dis[u]^dis[v]^w;
			dsu[a]=b;
		}
	}
	if(flag){printf("NO\n");return;}
	printf("YES\n");
	rep(i,2,n){
		if(f.find(mp(i,fa[i]))!=f.end()){
			printf("%d %d %d\n",i,fa[i],f[mp(i,fa[i])]);
		}else{
			int a=Find(i),b=Find(fa[i]);
			int vala=dis[i],valb=dis[fa[i]];
			printf("%d %d %d\n",i,fa[i],vala^valb);
		}
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		solve();
	}

	return 0;
}
```

---

## 作者：一念之间、、 (赞：1)


## 简述题意：
说：给一棵树，某些地方（边权）是 -1 ，让你把每个 -1 的位置填一个值，使得满足 $q$ 个限制，每个限制形如 $x,y,0/1$ 表示从 $x$ 走到 $y$ 的所有边权异或和的二进制表示有奇数/偶数个1。

## 解法：

仔细观察，发现对于一条边，若二进制的某一位填一个 1 ，则会影响所有过这个边的限制（ 0 变 1 , 1 变 0 ），二进制任意一位填1这个的影响是相同的，于是我们只用考虑-1边填0/1即可，然后消除已经填了的边限制。

然后就会变成一堆边异或起来为一个定值，显然**不能**高斯消元，直接树上差分，换成到根前缀异或和（注意在一条带初始边权的边的两端到根是有限制的，在消除影响后限制是两边到根前缀和相等相等），然后带权并查集维护。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
//#define getchar gc
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&((fwrite(buf,1,s-buf,stdout)),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x);pc(op,0);
}
const int xx=2e5+5;
int fa[xx],sum[xx];//0表示相等1表示不相等 
int find(int x)//返回的还是点 
{
	if(fa[x]==x)return x;
	int a=find(fa[x]);
	sum[x]=sum[x]^sum[fa[x]];
	fa[x]=fa[fa[x]];
	return fa[x];
}
struct nod{int next,to,v;}e[xx<<1];
int cnt,h[xx];
void add(int x,int y,int z)
{
	cnt++;
	e[cnt].next=h[x];
	h[x]=cnt;
	e[cnt].to=y;
	e[cnt].v=z;
}
int d[xx],f[xx],fv[xx];
int dep[xx];
//注意可能给出来有0的边权 
void dfs(int x,int y)
{
	dep[x]=dep[y]+1;
	f[x]=y;
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y)continue;
		fv[e[i].to]=e[i].v;
		if(e[i].v==-1)
			d[e[i].to]=d[x];
		else d[e[i].to]=d[x]^e[i].v;
		dfs(e[i].to,x);
		
	}
}
struct No
{
	int a,b,c;
};
int op=1;
void AD(int x,int y,int z)
{
	if(!op)return;
	if(find(x)==find(y))
	{
		if((sum[x]^sum[y])!=z)op=0;
		return;
	}
	int o=find(y); 
	sum[o]=sum[y]^z;
	//这里先更新sum find要错！ 
	fa[o]=x;
}
int ans[xx];
int main(){
	int T=read();
	while(T--)
	{
		op=1;
		int n=read(),m=read();
		memset(e,0,sizeof(e[0])*(cnt+1));
		memset(h,0,sizeof(h[0])*(n+1));
		cnt=0;
		for(int i=1;i<=n;i++)fa[i]=i,sum[i]=0;
		vector<No>v;
		for(int i=1;i<n;i++)
		{
			int a=read(),b=read(),c=read();
			add(a,b,c),add(b,a,c);
			v.push_back({a,b,c});
		}
		dfs(1,0);
		for(int i=1;i<=m;i++)
		{
			int a=read(),b=read(),c=read();
			int now=d[a]^d[b];
			int num=__builtin_popcount(now);
			num&=1,c^=num;
			AD(a,b,c);
		}
		//相当于把所有带限制的地方都转成了0 
		for(int i=2;i<=n;i++)
		{
			if(fv[i]!=-1)
			{
				int a=i,b=f[i],c=0;
				AD(a,b,c);//强制要求相等 
			}
		}
		if(!op)
		{
			puts("No");
			continue;
		}
		for(int i=1;i<=n;i++)ans[i]=0;
		for(int i=1;i<=n;i++)
			if(find(i)==i)ans[i]=0;
		for(int i=1;i<=n;i++)
			if(find(i)!=i)ans[i]=sum[i];
		puts("Yes");
		for(auto it:v)
		{
			if(it.c!=-1)
				cout<<it.a<<" "<<it.b<<" "<<it.c<<"\n";
			else 
				cout<<it.a<<" "<<it.b<<" "<<(ans[it.a]^ans[it.b])<<"\n";
		}
	}
	pc('1',1);
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

### Analysis

我们设题目中**边权条件为 A 条件，路径条件为 B 条件**。

**以下 ppcnt 均指 __builtin_popcount 函数，即二进制下 $1$ 的个数。$f(x)=ppcnt(x)\mod 2$。设点 $x$ 到 $root$ 的路径边权异或和为 $g(x)$**

容易发现设 $x\leftrightarrow y$ 的路径异或和为 $z$，则 $g(x)\operatorname{xor}g(y)=z,f(g(x))\operatorname{xor}f(g(y))=f(z)$（读者自证）。

因为 B 条件只和异或和的 $f$ 有关，所以边权的具体数值根本没用（除了最后的构造），对于一条已知的边权 $x$，我们存 $f(x)$ 即可。就是说 **A 条件均可转换成 B 条件**。

我们很容易想到 NO 的方案，就是一系列条件推出两个点 $x,y$ 的 $f(g(x))$ 与 $f(g(y))$ 既相同又不同，自相矛盾。

发现这可以用**带边权的并查集**维护，并查集的边 $(x,y)$ 边权表示点 $x,y$ 的 $f(g(x)),f(g(y))$ 是（$0$）否（$1$）相同。

最后，如果判定为 YES（即在并查集的过程中没有矛盾），则这样构造边权初始为 $-1$ 的边：

* 如果这条边两端 $x,y$ 在同一个并查集内，则边权设为 $f(g(x))\ !=f(g(y))$（bool 类型）

* 否则，边权任意（因为两者的关系现在不明确），再将这两个并查集合并即可。

### Code

```cpp
int n,m;
int f[N],g[N];
struct node{int x,y,val;};
vector<node> v,inp;
inline int gf(int x){//get father in dsu
	if(x==f[x]) return x;
	int tmp=gf(f[x]);
	g[x]^=g[f[x]];
	return f[x]=tmp;
}
inline void mou(int x){//make root in dsu
	int tmp=gf(x);
	if(x==tmp) return ;
	f[tmp]=x;
	g[tmp]=g[x];
	g[x]=0;
	f[x]=x;
}
inline int dis(int x){//the val to the root in dsu
	int tmp=gf(x);
	if(x==tmp) return 0;
	return g[x];
}
int calc(int x,int y){
	if(gf(x)!=gf(y)){
		mou(x);
		mou(y);
		f[x]=y;
		g[x]=0;
		return 0;
	}else{
		return dis(x)^dis(y);
	}
}
void work(){
	cin>>n>>m;
	v.clear();
	inp.clear();
	For(i,1,n) f[i]=i;
	For(i,1,n) g[i]=0;
	int x,y,z;
	For(i,1,n-1){
		 cin>>x>>y>>z;
		 inp.pb((node){x,y,z});//for construction
		 if(z>=0){
		 	v.pb((node){x,y,__builtin_popcount(z)&1});
		 }
	}
	For(i,1,m){
		cin>>x>>y>>z;
		v.pb((node){x,y,z});
	}
	for(auto i:v){
		if(gf(i.x)!=gf(i.y)){
			mou(i.x);
			mou(i.y);
			f[i.x]=i.y;
			g[i.x]=i.val;
		}else if(dis(i.x)^dis(i.y)^i.val){
			cout<<"NO"<<endl;
			return ;
		} 
	}
	cout<<"YES"<<endl;
	for(auto i:inp){
		cout<<i.x<<" "<<i.y<<" ";
		if(i.val>=0) cout<<i.val<<endl;
		else cout<<calc(i.x,i.y)<<endl;
	}
}
```

---

## 作者：kkio (赞：1)

首先是做这道题的一个重要式子:
	
$$ (x \oplus y)\mod 2 = (x \mod 2) \oplus (y\mod2)$$ 

然后再原图的基础上建一张新图,表示点之间的异或关系,已确定的边也可以加进去。

令$val[i]$为$i$与其父亲边的值。令$val[root]=0$，然后在新图上跑dfs,求出所有的值，再将原来的图上边上的值代入即可。

注意特判矛盾。

```cpp
#include <bits/stdc++.h>
#define fir first
#define sec second
using namespace std;
const int maxn=2e5+10;
vector< pair<int,int> > X[maxn],G[maxn];
int T,n,m;
bool vis[maxn],flag;
int sta[maxn],ans[maxn];
void xorval(int u,int val)
{
	vis[u]=1;sta[u]=val;
	for(auto cur : X[u])
	{
		int v=cur.fir,w=cur.sec;
		if(vis[v]&&w^val!=sta[v])flag=1;
		if(!vis[v])xorval(v,w^val);
	}
}
void dfs(int u,int fa)
{
	for(auto cur : G[u])
	{
		int v=cur.fir,w=cur.sec;
		if(v==fa)continue;
		ans[v]=(w==-1?sta[u]^sta[v]:w);
		printf("%d %d %d\n",v,u,ans[v]);
		dfs(v,u);
	}
}
void solve()
{
	scanf("%d%d",&n,&m);
	flag=0;
	for(int i=1;i<=n;i++)
		X[i].clear(),G[i].clear(),vis[i]=sta[i]=0;
	for(int i=1,a,b,c,num;i<n;i++)
	{
		num=0;
		scanf("%d%d%d",&a,&b,&c);
		G[a].push_back({b,c});
		G[b].push_back({a,c});
		if(c==-1)continue;
		for(int i=0;i<=30;i++)
			if(c&(1<<i))num++;
		X[a].push_back({b,num%2});
		X[b].push_back({a,num%2});
	}
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		X[a].push_back({b,c});
		X[b].push_back({a,c});
	}
	for(int i=1;i<=n;i++)if(!vis[i])xorval(i,0);
	if(flag){puts("NO");return;} 
	else puts("YES");
	dfs(1,0);
}
int main()
{
	cin>>T;
	while(T--)solve();
}
```


---

## 作者：Refined_heart (赞：0)

~~题目难度逐渐从 2400 掉到 2200 做不动了）~~

清新构造题。

[CF1615D X(or)-mas Tree](https://www.luogu.com.cn/problem/CF1615D)

$\text{Solution:}$

首先我们尝试发现性质。以下是写的时候发现的：

以下令 $pc(a)=popcount(a),$ 性质二以及后面都直接让它对 $2$ 取模了。

* 若 $pc(a)\equiv pc(b)(\bmod 2),pc(a\text{ xor }b)=0(\bmod 2)$

* 若 $pc(a)\not = pc(b),pc(a\text{ xor }b)=1$

以及，有一个自然的联想：这是异或，所以两点路径的 $\text{xor}$ 实际就是从根到这个点的 $\text{prexor}$ 的异或值。

所以我们不妨把题目所给的限制 $(u,v,w)$ 看做逻辑推导的 **边** ，那么我们按照限制建图，在图上面根据边来定值即可。

顺便一句，我们其实可以发现构造只需要用到 $0/1$

注意要用到原图的边。$(u,v,w)\to pc(p[u]\text{ xor }p[v])=w$ 都加上去。

那么无解的条件就是逻辑定值的时候冲突。随便判断一下即可。

然后我们还要在原树上跑一边避免解不合法。

最后输出即可。这里定边用了 ```map,``` 实际上可以不带这个 $\log.$

我的代码复杂度是 $O(n\log n).$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef double db;
#define int long long
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
#define poly vector<int>
#define Bt(a) bitset<a>
#define bc __builtin_popcount
#define pc putchar
#define ci const int&
const int mod = 1e9 + 7;
const db eps = 1e-10;
const int inf = (1 << 30);
inline int Max(ci x, ci y) {return x > y ? x : y;}
inline int Min(ci x, ci y) {return x < y ? x : y;}
inline db Max(db x, db y) {return x - y > eps ? x : y;}
inline db Min(db x, db y) {return x - y < eps ? x : y;}
inline int Add(ci x, ci y, ci M = mod) {return (x + y) % M;}
inline int Mul(ci x, ci y, ci M = mod) {return 1ll * x * y % M;}
inline int Dec(ci x, ci y, ci M = mod) {return (x - y + M) % M;}
typedef pair<int, int> pii;
inline int Abs(int x) {return x < 0 ? -x : x;}
//char buf[1<<21],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char Obuf[105000],*O=Obuf;//Siz shoule be the size of Out File
int pst[30],ptop;
inline void Fprint(){fwrite(Obuf,1,O-Obuf,stdout);}
inline void Fwrite(int x){
  if(x==0){*O++='0';return;}
  if(x<0)*O++='-',x=-x;ptop=0;
  while(x)pst[++ptop]=x%10,x/=10;
  while(ptop)*O++=pst[ptop--]+'0';
  if(O-Obuf>100000)Fprint(),O=Obuf;
}
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') w = -1;ch = getchar();}
    while (isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
    return s * w;
}
inline void write(int x) {
    if (x < 0)putchar('-'), x = -x;
    if (x > 9)write(x / 10);
	pc(x % 10 + '0');
}
inline int qpow(int x, int y) {
    int res = 1;
    while (y) {if (y & 1)res = Mul(res, x);x = Mul(x, x);y >>= 1;}
    return res;
}
inline void cadd(int &x, int y) {x += y;}
inline void cmul(int &x, int y) {x *= y;}
inline void cmax(int &x, int y) {x = Max(x, y);}
inline void cmin(int &x, int y) {x = Min(x, y);}
const int N = 2e6 + 10;
namespace Refined_heart{
	int T,head[N],tot,n,m;
	struct E{int nxt,to,dis;}e[N],Eg[N];
	inline void link(int x,int y,int v){
		e[++tot]=(E){head[x],y,v};
		head[x]=tot;
	}
	int TOT=1,Head[N];
	inline void linktr(int u,int v,int w){
		Eg[++TOT]=(E){Head[u],v,w};
		Head[u]=TOT;
	}
	struct Node{int u,v,w;};
	vector<Node> eg;
	int val[N],vis[N];
	int Tg=0;
	void dfs(int x,int fa,int v){
		if(Tg)return;
		vis[x]++;
		if(val[x]!=-1&&val[x]!=v){
			Tg=1;
			return;
		}
		val[x]=v;
		for(int i=head[x];i;i=e[i].nxt){
			int j=e[i].to;
			if(j==fa)continue;
			if(val[j]==(v^e[i].dis))continue;
			dfs(j,x,v^e[i].dis);
		}
	}
	map<int,int>edge[N];
	int tag[N];
	void dfs2(int x,int fa){
		for(int i=Head[x];i;i=Eg[i].nxt){
			int j=Eg[i].to;
			if(j==fa)continue;
			int vl=val[j]^val[x];
			vl=bc(vl);vl&=1;
			if(vl)edge[j][x]=edge[x][j]=1;
			else edge[j][x]=edge[x][j]=0;
			dfs2(j,x);
		}
	}
	bool check(int x,int fa,int prev){
		int fg=1;
		for(int i=Head[x];i;i=Eg[i].nxt){
			int j=Eg[i].to;
			if(j==fa)continue;
			int vl=(Eg[i].dis==-1?edge[x][j]:Eg[i].dis)^prev;
			vl=bc(vl);vl&=1;
			if(vl!=val[j]){
				fg=0;
				return fg;
			}
			fg&=check(j,x,prev^(Eg[i].dis==-1?edge[x][j]:Eg[i].dis));
		}
		return fg;
	}
	void clear(){
		TOT=1,tot=0;eg.clear();Tg=0;
		for(int i=1;i<=n;++i)Head[i]=head[i]=vis[i]=0,val[i]=-1;
		for(int i=1;i<=n;++i){edge[i].clear();}
	}
	void work(){
		clear();
//		if(T==1){
//			int a=0;
//			int b=1;
//			assert(a>b);
//		}
		n=read();m=read();
		for(int i=1;i<n;++i){
			int u=read(),v=read(),w=read();
			linktr(u,v,w);linktr(v,u,w);
			eg.pb((Node){u,v,w});
			if(w==-1)continue;
			link(u,v,bc(w)&1);
			link(v,u,bc(w)&1);
		}
		for(int i=1;i<=m;++i){
			int u=read(),v=read(),w=read();
			link(u,v,w);link(v,u,w);
		}
		for(int i=1;i<=n;++i)val[i]=-1;
		
		for(int i=1;i<=n;++i){
			if(!vis[i]){
				val[i]=0;
				dfs(i,0,0);
			}
		}
		if(Tg){
			puts("NO");
			return;
		}
		
		dfs2(1,0);
		int fg=check(1,0,0);
		if(!fg){
			puts("NO");
			return;
		}
		puts("YES");
		for(auto vv:eg){
			int u=vv.u;
			int v=vv.v;
			int w=vv.w;
			if(w==-1)w=edge[u][v];
			printf("%lld %lld %lld\n",u,v,w);
		}
		return;
	}
	void solve(){
		T=read();int Z=T;
		while(Z--)work();
	}
}
signed main(){
	freopen("in.txt","r",stdin);
	Refined_heart::solve();
	return 0;
}


```


---

## 作者：Little09 (赞：0)

首先根据异或的性质容易发现，若干个数异或的 popcount 是奇是偶等同于每个数 popcount 的奇偶异或起来。因此每条边可以等效于 $0$ 和 $1$。

我们进行树上差分，对每个点计算一个 $dis_i$ 表示从根到节点 $i$ 的路径上的异或和。那么对于每个条件可以转化为 $dis_u \text{ xor } dis_v =w$。

对于树上原有的边，也可以进行相同的转化。因此问题变成很经典的题目了。若干 $01$ 变量若干条件，每个条件是其中两个变量的异或，求一组构造。

你可以使用二分图等方式解决这个问题。我选择的是种类并查集，类似于 [[NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024) 的做法。

```cpp
int fa[N];
vector<int>t[N],v[N];
int find(int x)
{
	if (x==fa[x]) return fa[x];
	return fa[x]=find(fa[x]);
}
int wq[N];
bool ans;
inline int wr(int z)
{
	int res=0;
	while (z)
	{
		if (z&1) res^=1;
		z>>=1;
	}
	return res;
}
void merge(int x,int y)
{
	x=find(x),y=find(y);
	if (x==y) return;
	fa[x]=y;
}
void ddd(int x,int y,int z)
{
	if (z==0) 
	{
		if (find(x+n)==find(y)||find(y+n)==find(x))
		{
			ans=1;
			return;
		}
		merge(x,y),merge(x+n,y+n);
	}
	else
	{
		if (find(x)==find(y)||find(y+n)==find(x+n))
		{
			ans=1;
			return;
		}
		merge(x,y+n),merge(y,x+n);
	}
}
void dfs(int x,int f,int vv)
{
	if (x==1) a[x]=0,wq[find(1)]=0,wq[find(1+n)]=1;
	else 
	{
		if (wq[find(x)]==-1) 
		{
			a[x]=0;
			wq[find(x)]=0,wq[find(x+n)]=1;
		}
		else
		{
			a[x]=wq[find(x)];
		}
		if (vv!=-1) printf("%d %d %d\n",x,f,vv);
		else printf("%d %d %d\n",x,f,(a[x]^a[f]));
	}
	for (int i=0;i<t[x].size();i++)
	{
		if (t[x][i]==f) continue;
		dfs(t[x][i],x,v[x][i]);
	}
}
void work()
{
	n=read(),m=read(),ans=0;
	for (int i=1;i<=2*n;i++) fa[i]=i,wq[i]=-1;
	for (int i=1;i<=n;i++) t[i].clear();
	for (int i=1;i<=n;i++) v[i].clear();
	for (int i=1;i<n;i++)
	{
		int x=read(),y=read(),z=read();
		t[x].push_back(y),t[y].push_back(x);
		v[x].push_back(z),v[y].push_back(z);
		if (z!=-1) ddd(x,y,wr(z));
	}
	for (int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		ddd(x,y,z);
	}
	if (ans==1)
	{
		printNO;
		return;
	}
	a[1]=0;
	printYES;
	dfs(1,-1,-1);
	return;
}

int main()
{
	int T=read();
	while (T--) work();
	return 0;
}

```


---

## 作者：清烛 (赞：0)

写个详细点的题解。

## Description
给定一棵 $n$ 个节点的树，其中某些边权尚未确定。要求你根据如下的 $m$ 条限制确定所有的边权：

- 每个限制形如 $(a, b, c)$，意味着从 $a$ 到 $b$ 的路径上的所有边权的异或和 $S$ 在二进制的表示下的位数满足 $\operatorname{popcount}(S) \bmod 2 = c$。

$n,m\le 2\times 10^5$

## Solution

定义 $\operatorname{parity}(x)$ 表示 $\operatorname{popcount}(x)\bmod 2$，则我们可以知道 $\operatorname{parity}(x\oplus y) = \operatorname{parity}(x)\oplus \operatorname{parity}(y)$。所以干脆直接先将树上的所有边权 $d$ 先变成 $\operatorname{parity}(d)$。

令树上前缀异或和（从根到 $u$ 的路径上的异或和）为 $r_u$，则我们注意到，由异或的消去律，$(a,b)$ 路径的异或和为 $r_a\oplus r_b$。所以我们现在就有了若干条形如 $r_a\oplus r_b = c$ 的限制（对于树上已有的边 $(u,v, x)$ 可以看作是 $r_u\oplus r_v = x$）。

对于每个限制 $r_a\oplus r_b = c$，在新图上建一条边 $(a, b, c)$，然后考虑二分图染色（一开始钦定一个 $r_i = 0$，然后进行 dfs），这样子就可以求出所有的 $r_u$。在 dfs 的过程中若遇到矛盾则说明寄了，特判一下即可。

## Implementation
```cpp
const int maxn = 2e5 + 5;
int r[maxn], vis[maxn], n, m, flag;
struct edge {
    int to, w;
    edge(int v, int d) : to(v), w(d) {}
};
vector<edge> G[maxn], G1[maxn];

il int parity(int n) {return __builtin_popcount(n) & 1;}

void dfs1(int u, int val) {
    vis[u] = 1, r[u] = val;
    for (auto &e : G1[u]) {
        int v = e.to, w = e.w;
        if (vis[v] && (w ^ val) != r[v]) flag = 1;
        if (!vis[v]) dfs1(v, val ^ w);
    }
    return;
}

void dfs2(int u, int fa) {
    for (auto &e : G[u]) {
        int v = e.to, w = e.w;
        if (v == fa) continue;
        print(v, u, w == -1 ? r[u] ^ r[v] : w);
        dfs2(v, u);
    }
    return;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n, m);
        flag = 0;
        FOR(i, 1, n) r[i] = vis[i] = 0, G[i].clear(), G1[i].clear();
        FOR(i, 1, n - 1) {
            int a, b, c; read(a, b, c);
            G[a].push_back(edge(b, c));
            G[b].push_back(edge(a, c));
            if (c == -1) continue;
            G1[a].push_back(edge(b, parity(c)));
            G1[b].push_back(edge(a, parity(c)));
        }
        FOR(i, 1, m) {
            int a, b, c; read(a, b, c);
            G1[a].push_back(edge(b, c));
            G1[b].push_back(edge(a, c));
        }
        FOR(i, 1, n) if (!vis[i]) dfs1(i, 0);
        if (flag) print("NO");
        else {
            print("YES");
            dfs2(1, 0);
        }
    }
    return output(), 0;
}
```

---

