# Almost Union-Find

## 题目描述

有 $n$ 个集合，$m$ 次操作。规定第 $i$ 个集合里初始只有 $i$。有三种操作：

1. 输入两个元素 $p$ 和 $q$，若 $p$ 和 $q$ 不在一个集合中，合并两个元素的集合。
2. 输入两个元素 $p$ 和 $q$，若 $p$ 和 $q$ 不在一个集合中，把 $p$ 添加到 $q$ 所在的集合。
3. 输入一个元素 $p$，查询 $p$ 所在集合的元素个数和所有元素之和。

## 说明/提示

$1 \leq  n,m\leq 10 ^ 5$，$1 \leq  p,q\leq n$。

## 样例 #1

### 输入

```
5 7
1 1 2
2 3 4
1 3 5
3 4
2 4 1
3 4
3 3```

### 输出

```
3 12
3 7
2 8```

# 题解

## 作者：Mr_think (赞：53)

## [UVA11987 Almost Union-Find](https://www.luogu.com.cn/problem/UVA11987)

## 题目大意
现有 $n$ 个集合 $m$ 个操作。规定第 $i$ 个集合里为 $\{i\}$ 。操作包括：
		
   1. 输入两个元素 `p` 、 `q` ，如果 `p` 、`q` 不在一个集合中，合并这两个元素所在的集合。
   2. 输入两个元素 `p` 、 `q` ，如果 `p` 、`q` 不在一个集合中，将 `p` 添到 `q` 所在的集合。
   3. 输入一个元素 `p` ，查询 `p` 所在的集合的大小和元素和。

## solution:
看到集合，考虑使用并查集 ~~(冰茶姬)~~ ， `1` 和 `3` 操作都很容易实现，难点在于操作 `2` 。我们并不可以通过
```cpp
fa[p]=cha(q);//cha()函数返回q所在集合的根节点
```
直接将 `p` 添加到 `q` 所在的集合。举个反例：

![](https://cdn.luogu.com.cn/upload/image_hosting/frg0gbbr.png)

现在集合的状态如上图，如果此时有 `2 1 3` ，按照上面的语句就变成了这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/glacqbxi.png)

我们会发现，此时元素 `2` 也被添加到了集合中，是不允许的。分析一下原因，源赖氏由于 `1` 为根节点才出错。考虑解决：我们可以添加一个虚拟根节点，编号为 $i+n$ ，现在我们再看这个过程：

![](https://cdn.luogu.com.cn/upload/image_hosting/gvw2eccx.png)

经过上述操作后：

![](https://cdn.luogu.com.cn/upload/image_hosting/mkriv9go.png)

噫，好了！符合题意。

## 接下来是细节的处理：

1. 由于我们建立了虚拟根节点，所以要开二倍的空间。
2.  $\text{UVA}$ 是多组输入，要
```cpp
while(scanf("%d%d",&n,&m)!=EOF)
```

看到这的同学，可以自己去写代码了(~~tf口吻~~)

[code](https://www.luogu.com.cn/paste/m9abj2nq)

### End

## 作者的碎碎念：

有用留赞(~~言简意赅~~)

---

## 作者：Cry_For_theMoon (赞：37)

[传送门](https://www.luogu.com.cn/problem/UVA11987)

从OI wiki过来的。发现题解都没讲清楚为什么可以用虚点然后并查集做（如果是Treap或者hash的当我没说）。

对于操作2，有一种错误思路是路径压缩后每个点都直连根节点，然后对于操作2我们只需要正常的移动就可以了。但是你会连样例都过不去。

为什么？因为你在操作2执行时这个并查集不一定是路径压缩过的。此时你的点 $p$ 可能还有儿子，此时如果直接移动关系就是错的。

自然我们会往保证时刻都进行路径压缩这个方面靠，但这复杂度过高，因为你合并的时候必须要把每个叶子节点进行一遍路径压缩，复杂度是 $O(nm)$ 往上的。

你已经发现了如果 $p$ 点没有儿子就可以直接做。然后发现不管是1的合并还是2的直接移动都是直接接在根上的，换言之只要每个集合的根节点不可能作为 $p$ 点出现那么每次 2 操作就可以直接移动 $p$。但是题目很显然 $p$ 可以是 $1...n$ 的任何一个点。因此你的集合的根节点不应该是 $1...n$ 的任何一个点。对于每个集合的根，都应该是一个虚点。

那么初始有 $n$ 个集合，自然就对应了 $n$ 个虚点，又因为初始第 $i$ 个集合就是元素 $i$，方便起见我们把这 $n$ 个虚点设置成了 $i+n$ 的形式。这才是真正需要用到虚点的原因

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10;
int n,m,opt,p,q,fa[MAXN],sz[MAXN];
long long sum[MAXN];
int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
int main(){
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i=1;i<=n;i++){
			fa[i]=i+n;
		}
		for(int i=n+1;i<=n+n;i++){
			fa[i]=i;sz[i]=1;sum[i]=i-n;
		}
		for(int i=1;i<=m;i++){
			scanf("%d",&opt);
			if(opt==1){
				scanf("%d%d",&p,&q);
				int u=find(p),v=find(q);
				if(u==v)continue;
				fa[u]=v;
				sz[v]+=sz[u];
				sum[v]+=sum[u]; 
			}else if(opt==2){
				scanf("%d%d",&p,&q);
				int u=find(p),v=find(q);
				if(u==v)continue;
				fa[p]=v;
				sz[u]--;sz[v]++;
				sum[u]-=p;sum[v]+=p;
			}else{
				scanf("%d",&p);
				printf("%d %lld\n",sz[find(p)],sum[find(p)]);
			}
		}
	}
	return 0;
}
```


---

## 作者：142857cs (赞：9)

这道题的关键在于怎么处理移动操作，这个有3种方式，一种是按另一篇题解的处理方式，一种是另一篇题解的方式，建一个虚点代表原来的位置（我不明白另一篇题解为什么要用unordered_map,不是一个数组就行了吗？），第二种和第一种类似，是建一个虚点代表这个元素，原来的点代表原来的位置。而我这里讲的是第三种写法。

如另一篇题解代码中所说，如果一个节点被加入到一个集合中，它就不会成为代表节点了，那么我们可以在最开始时就对每个节点建一个虚点，使集合的代表节点为虚点，这样所有真实节点都不会是代表节点，也就可以移动了
```cpp
#include<stdio.h>
int fa[262144];
int findroot(int x)
{
	if(fa[x]==x)
	{
		return x;
	}
	return fa[x]=findroot(fa[x]);
}
int ans[262144];
long long ans2[262144];
int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)>0)
	{
		for(int i=1;i<=n;i++)
		{
			fa[i]=i+n;
			fa[i+n]=i+n;
			ans[i+n]=1;
			ans2[i+n]=i;
		}
		while(m--)
		{
			int opt;
			scanf("%d",&opt);
			if(opt==1)
			{
				int u,v;
				scanf("%d%d",&u,&v);
				u=findroot(u);
				v=findroot(v);
				if(u==v)
				{
					continue;
				}
				ans[v]+=ans[u];
				ans2[v]+=ans2[u];
				fa[u]=v;
			}
			else if(opt==2)
			{
				int u,v;
				scanf("%d%d",&u,&v);
				int x=findroot(u);
				int y=findroot(v);
				ans[x]--;
				ans[y]++;
				ans2[x]-=u;
				ans2[y]+=u;
				fa[u]=y;
			}
			else
			{
				int u;
				scanf("%d",&u);
				u=findroot(u);
				printf("%d %lld\n",ans[u],ans2[u]);
			}
		}
	}
	return 0;
}
```

---

## 作者：OldVagrant (赞：5)

## 题意
给定 $n$ 个集合，编号为 $1\sim n$,最开始每个集合 $s_i$ 里面都有一个元素  $i$ 。现在要对这些集合进行 $m$ 次操作，每次操作都是以下三种操作中的一种：   
```1 p q``` 合并元素 $p,q$ 所在的集合，如果它们已经在一个集合内则忽略本次操作。   
```2 p q``` 把元素 $p$ 从其所在的集合内剥离出来，合并到元素 $q$ 所在的集合内，如果它们已经在一个集合内则忽略本次操作。     
```3 p``` 查询元素 $p$ 所在的集合的元素个数和元素总和。    
$1\le n,m\le 10^5,1\le p,q\le n$。
## Solution
前置知识：并查集（不会的请先移步[P3367【模板】并查集](https://www.luogu.com.cn/problem/P3367)）。   
题目名称翻译一下就是“几乎是并查集”，~~那直接无脑并查集，刚好三个操作看起来都是并查集擅长的~~。然后再认真地看一下三个操作，操作 1 和 3 并查集都能很简单地维护，~~操作 2 是个什么鬼东西~~。   
再来看一下操作 2 的描述，是把 $p$ 从其所在集合里剥离出来，放进 $q$ 所在的集合里。如果直接用传统的合并，对 $p,q$ 所在集合的元素个数和元素和进行更改，然后把 $p$ 的父亲节点指向 $q$ 所在集合的代表，会出大差错。当 $p$ 不是一个集合的代表的时候不影响什么，但万一 $p$ 是一个集合的代表那就直接挂了，这就直接把 $p$ 所在集合的所有元素全部合并到了 $q$ 所在的集合里面，还只计算了 $p$ 的贡献。那么怎么办呢？    
传统的合并操作会在 $p$ 是一个集合的代表时出错，那么不如再新建 $n$ 个虚拟元素，每个虚拟元素不会对答案产生贡献，其值为 $n+1\sim 2\times n$ ，最开始时令虚拟元素 $i+n$ 为元素 $i$ 所在的集合的代表，然后合并时只要采用路径压缩优化，就一定可以保证所有的 $p\in[1,n]$ 在任何时刻都不为任何一个集合的代表。因为路径压缩会直接把集合中的非代表的元素的父亲节点指向代表元素，而初始的代表元素都是虚拟元素。这样来做的话就不会有错了。         
## Code
注释掉的代码为快读快写，卡常用的，可以加上。
```c
#include <bits/stdc++.h>
using namespace std;
#define gc getchar
#define pc(x) putchar(x)
int n,m,fa[200001],sum[200001],size[200001],y,k;//注意这里的数组都要开两倍于n的大小，sum为每个集合内元素总和，size为每个集合内元素总个数。
/*const int LEN=114514;
char BUF[LEN],*Pin,*Pin_last,PUF[LEN],*Pout=PUF,*Pout_last=PUF+LEN-1;
char gc(){
	return Pin==Pin_last&&(Pin_last=(Pin=BUF)+fread(BUF,1,LEN,stdin),Pin==Pin_last)?EOF:*Pin++;
}
void pc(char x){
	if(Pout==Pout_last) fwrite(PUF,1,Pout-PUF,stdout),Pout=PUF;
	*Pout++=x;
}*/
int read(){
	int x=0;
	char ch=gc();
	while(ch<48||ch>57){
		if(ch==EOF) exit(0);
		ch=gc();
	}while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return x;
}
void write(int x){
    if(x>9) write(x/10);
    pc(x%10+48);
}
int find(int x){//路径压缩优化，这个一定要加上，把每个元素的父亲直接指向所在集合的代表元素。
	if(fa[x]==x) return fa[x];
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){//合并两个元素所在的集合，元素总和直接相加，元素总个数直接相加，如果已经在同一集合直接返回。
	x=find(x),y=find(y);
	if(x==y) return;
	fa[y]=x,size[x]+=size[y],sum[x]+=sum[y];
}
void split(int x,int y){//把 x 从所在集合移除，合并到 y 所在集合内，如果已经在同一集合内则直接返回。
	int a=find(x),b=find(y);
	if(a==b) return;
	size[a]--,sum[a]-=x,sum[b]+=x,size[b]++,fa[x]=b;
}
signed main(){
	n=read(),m=read(),k=n<<1;
	while(1){
		for(int i=1;i<=n;i++) fa[i]=i+n,sum[i+n]=i;//初始化。元素i的父节点为i+n，所在集合为i+n,所以是 sum[i+n]=i。
		for(int i=n+1;i<=k;i++) fa[i]=i,size[i]=1;//建立虚拟元素，父亲节点就是自己，所在集合的大小为1，因为虚拟元素不对答案产生贡献。
		while(m--){
			int tp=read(),x=read();
			if(tp<3) y=read(),tp&1?merge(x,y):split(x,y);
			else y=find(x),write(size[y]),pc(' '),write(sum[y]),pc('\n');
		}n=read(),m=read(),k=n<<1;
	}//fwrite(PUF,1,Pout-PUF,stdout);
	return 0;
}
```


---

## 作者：Mihari (赞：4)

# 题目

[传送门](https://www.luogu.com.cn/problem/UVA11987)

# 题解

首先考虑，如果没有操作二，这道题将会是一道并查集板题。

现在我们考虑操作二怎么处理。

操作二难在哪里？难在如果 $p$ 的父亲被修改，那么 $p$ 以下的点将会是错误的根节点关系。

对于每一个修改 $2$，我们将 $p$ 的原点保留，只是将 $p$ 和 $q$ 的根节点信息修改一下，然后我们对于 $p$ 建出一个新的虚点，将这个虚点连到 $q$ 的并查集中即可。

代码实现中使用 `has[u]` 表示 $u$ 这个时候对应的新的虚点是多少，用 `ncnt` 记录虚点的编号。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i<=i##_end_;++i)
#define fep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i>=i##_end_;--i)
#define writc(a,b) fwrit(a),putchar(b)
#define mp(a,b) make_pair(a,b)
#define ft first
#define sd second
#define LL long long
#define ull unsigned long long
#define uint unsigned int
#define pii pair< int,int >
#define Endl putchar('\n')
// #define int long long
// #define int unsigned
// #define int unsigned long long

#ifdef _GLIBCXX_CSTDIO
#define cg (c=getchar())
template<class T>inline void qread(T& x){
    char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    if(f)x=-x;
}
template<class T>inline T qread(const T sample){
    T x=0;char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    return f?-x:x;
}
#undef cg
#endif
// template<class T,class... Args>inline void qread(T& x,Args&... args){qread(x),qread(args...);}
template<class T>inline T Max(const T x,const T y){return x>y?x:y;}
template<class T>inline T Min(const T x,const T y){return x<y?x:y;}
template<class T>inline T fab(const T x){return x>0?x:-x;}
inline int gcd(const int a,const int b){return b?gcd(b,a%b):a;}
inline void getInv(int inv[],const int lim,const int MOD){
    inv[0]=inv[1]=1;for(int i=2;i<=lim;++i)inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
}
template<class T>void fwrit(const T x){//just short,int and long long
    if(x<0)return (void)(putchar('-'),fwrit(-x));
    if(x>9)fwrit(x/10);
    putchar(x%10^48);
}
inline LL mulMod(const LL a,const LL b,const LL mod){//long long multiplie_mod
    return ((a*b-(LL)((long double)a/mod*b+1e-8)*mod)%mod+mod)%mod;
}

const int MAXN=100000;

int has[MAXN+5],fa[(MAXN<<1)|2],siz[(MAXN<<1)|2];
LL w[(MAXN<<1)|2];
int ncnt;

int n,m;

inline void makeSet(){
    rep(i,1,MAXN)fa[i]=i,w[i]=i,siz[i]=1;
}

int findSet(const int u){
    return fa[u]==u?u:fa[u]=findSet(fa[u]);
}

int opt,p,q,u,v,x;
signed main(){
    // ios::sync_with_stdio(false);
    while(~scanf("%d %d",&n,&m)){
        ncnt=0;
        rep(i,1,n)has[i]=++ncnt;
        makeSet();
        while(m--){
            opt=qread(1),p=qread(1);
            if(opt==1){q=qread(1);
                p=has[p],q=has[q];
                u=findSet(p),v=findSet(q);
                if(u==v)continue;
                siz[v]+=siz[u];
                w[v]+=w[u];
                fa[u]=v;
            }else if(opt==2){q=qread(1);
                x=has[p],q=has[q];
                u=findSet(x),v=findSet(q);
                --siz[u],w[u]-=p;
                ++siz[v],w[v]+=p;
                has[p]=++ncnt;
                p=has[p];
                fa[p]=v;
            }else{p=has[p];
                findSet(p);
                writc(siz[fa[p]],' '),writc(w[fa[p]],'\n');
            }
            // rep(i,1,n<<1){
            //     printf("has[%d] == %d, fa[%d] == %d, w[%d] == %d\n",i,has[i],i,fa[i],i,w[i]);
            // }
        }
    }
	return 0;
}
```



---

## 作者：浅色调 (赞：4)

### Solution：

　　本题平衡树。

　　考试的时候想到的就是无旋treap了，正解貌似是并查集（我没想出来，太菜了）。

　　节点维护子树大小和子树和，开始时每个节点就是一棵treap，因为我们并不要保证有序，所以可以直接按中序遍历维护，合并分离就不需要考虑优先级了。

　　对于操作一，若不在同一棵树中，直接merge两棵树。

　　对于操作二，因为随机键值树高为$\log n$，所以直接暴力往上跳到$x$所在树的根，跳的同时求出$x$在该树中的排名，若$x,y$不在同一棵树中，按排名将$x$分离出来，与$y$所在树合并。

　　对于操作三，直接找到$x$所在树根输出子树大小和子树和就好了。

$\quad\;\;$欢迎来踩博客：[five20](https://www.cnblogs.com/five20/p/9886349.html)（蒟蒻写题解不易，转载请注明出处，万分感谢！～）

### 代码：
```cpp
/*Code by 520 -- 10.24*/
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define il inline
#define ll long long
#define RE register
#define For(i,a,b) for(RE int (i)=(a);(i)<=(b);(i)++)
#define Bor(i,a,b) for(RE int (i)=(b);(i)>=(a);(i)--)
using namespace std;
const int N=100005;
int n,m,ch[N][2],rnd[N],siz[N],date[N],cnt,fa[N],sum[N];

int gi(){
	int a=0;char x=getchar();
	while(x<'0'||x>'9') x=getchar();
	while(x>='0'&&x<='9') a=(a<<3)+(a<<1)+(x^48),x=getchar();
	return a;
}

il void newnode(int v){
	++cnt;
	ch[cnt][0]=ch[cnt][1]=0,sum[cnt]=v;
	siz[cnt]=1,date[cnt]=v,rnd[cnt]=rand(),fa[cnt]=0;
}

il void up(int rt){
	if(ch[rt][0]) fa[ch[rt][0]]=rt;
	if(ch[rt][1]) fa[ch[rt][1]]=rt;
	siz[rt]=siz[ch[rt][0]]+siz[ch[rt][1]]+1;
	sum[rt]=sum[ch[rt][0]]+sum[ch[rt][1]]+date[rt];
}

int merge(int x,int y){
	if(!x||!y) return x+y;
	if(rnd[x]<rnd[y]) {ch[x][1]=merge(ch[x][1],y),up(x);return x;}
	else {ch[y][0]=merge(x,ch[y][0]),up(y);return y;}
}

void split(int rt,int v,int &x,int &y){
	if(!rt) {x=y=0;return;}
	if(siz[ch[rt][0]]>=v) y=rt,split(ch[rt][0],v,x,ch[y][0]),up(y);
	else x=rt,split(ch[rt][1],v-siz[ch[rt][0]]-1,ch[x][1],y),up(x);
}

int find(int x,int &tot){
	if(!fa[x])return x;
	if(ch[fa[x]][1]==x) tot+=siz[ch[fa[x]][0]]+1;
	return find(fa[x],tot);
}

int main(){
	srand(time(0));
	while(scanf("%d%d",&n,&m)!=EOF){
		cnt=0; int opt,a,b,c,x,y,z;
		For(i,1,n) newnode(i);
		while(m--){
			opt=gi(),a=gi();
			if(opt==1){
				b=gi();
				a=find(a,x=0),b=find(b,x=0);
				if(a!=b) merge(a,b);
			}
			else if(opt==2){ int k=siz[ch[a][0]]+1;
				b=gi();c=find(a,k),b=find(b,opt);
				if(c!=b){
					x=y=z=0; 
					split(c,k,x,y),split(x,k-1,x,z),x=merge(x,y),b=merge(b,z);
					fa[x]=0,fa[b]=0;
				}
			}
			else {
				a=find(a,x=0);
				printf("%d %d\n",siz[a],sum[a]);
			}
		}
	}
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：3)

## 题意

由于原文没有正确翻译，现在来重新描述一下题意：

现在你有一个类似于并查集的数据结构，并且可以支持以下操作：

1. 输入两个数 $p, q$，表示将 $p$ 所在的集合和 $q$ 所在的集合合并。

2. 输入两个数 $p, q$，表示将 $p$ 这个数移到 $q$ 所在的集合里。

3. 输入一个数 $p$，表示询问 $p$ 所在的集合里的数的个数和所有数的总和。

这种数据结构规定最初 $p$ 的集合里只有 $p$ 这个数字。

## 思路

这道题目一看就是一道并查集的水题，$1$ 操作和 $3$ 操作都可以用普通的并查集实现，但是如果 $2$ 操作用普通并查集实现，就会出现问题。下面举个栗子：

某次操作后的集合状态如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/cny1dvyv.png)

现在执行操作 $2\ 1\ 5$，如果我们用普通并查集就会出现以下情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/osx1glhs.png)

现在我们可以发现，$3$ 和 $2$ 一同连着 $1$ 飞走了。

我们总结之后发现，会出现这种情况的原因是在第一个集合内，$1$ 是这个集合内某一颗子树的根节点（理解什么意思就行），也就是说，我们不想让这种情况发生，只能让所有的节点为这个集合/树的叶子节点，才能保证它们安然无恙的离开。

所以引入了一个概念：虚点。

具体操作是这样的：

我们可以对每个数 $i$ 建立虚点 $i + n$ 为它的上司。还是用上面那个栗子来理解：

然后建立虚点就会变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/s5n18t4u.png)

然后再执行上面那个操作就是这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/1dqcvqe6.png)

是不是很妙。

## 代码

只要思路理解了，代码应该就能打出来，这里就不给出代码了。作者最后提一句：并查集要开双倍空间。

---

## 作者：andyli (赞：2)

本题三种操作第一种操作和第三种操作都可以使用加权并查集实现，使用指针存储并查集便可以实现第二种操作。  
使用指针存储并查集时不建议使用$new$运算符，容易出错，比较常见的办法是初始一个内存池（比如代码中的$nodes$），初始化时便可直接使用。
代码如下：  
```cpp
#include <cstdio>
const int maxn = 100000;

struct Node {
    int num;
    Node *nxt, *prev, *parent, *tail;
} nodes[maxn];

void insert(Node* p, Node* root)
{
    p->parent = root;
    p->prev = root->tail;
    root->tail->nxt = p;
    p->nxt = nullptr;
    root->tail = p;
}

Node* find(int x)
{
    Node *px = nodes + x, *root = px->parent;
    while (root != root->parent)
        px->parent = (root = root->parent);
    return root;
}

void uni_set(int a, int b)
{
    Node *p = find(a), *q = find(b);
    if (p != q) {
        q->tail->nxt = p;
        p->prev = q->tail;
        q->tail = p->tail;
        for (Node* cur = p; cur; cur = cur->nxt)
            cur->parent = q;
    }
}

void move_set(int a, int b)
{
    Node *u = nodes + a, *p = find(a), *q = find(b);
    if (p == q)
        return;
    if (u == p) {
        Node *cur = u->nxt, *first = cur;
        if (cur) {
            cur->prev = nullptr;
            cur->tail = p->tail;
        }
        while (cur) {
            cur->parent = first;
            cur = cur->nxt;
        }
    } else {
        if (u == p->tail)
            p->tail = u->prev;
        u->prev->nxt = u->nxt;
        if (u->nxt)
            u->nxt->prev = u->prev;
    }
    insert(u, q);
}

void query_set(int p)
{
    long long num = 0, sum = 0;
    for (Node* cur = find(p); cur; cur = cur->nxt, num++)
        sum += cur->num;
    printf("%lld %lld\n", num, sum);
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        Node* cur = nodes + 1;
        for (int i = 1; i <= n; i++, cur++) {
            cur->num = i;
            cur->nxt = nullptr;
            cur->parent = cur;
            cur->tail = cur;
        }
        for (int i = 0; i < m; i++) {
            int opt, p, q;
            scanf("%d%d", &opt, &p);
            if (opt != 3)
                scanf("%d", &q);
            if (opt == 1)
                uni_set(p, q);
            else if (opt == 2)
                move_set(p, q);
            else
                query_set(p);
        }
    }
}

```

---

## 作者：Purslane (赞：1)

## Solution

并查集 .

操作 1 和操作 3 十分显然 , 是并查集的模板 .

但是操作 2 有些棘手 . 因为这要求我们的并查集支持单点修改 .

我们考虑一下如何单点删除 :

1. 找到这个点 ;
2. 把这个点的儿子全部连到原点的父亲上 ;
3. 把这个点删掉 .

好像把操作 2 解决了 , 但是复杂度会炸 , 况且如果这个点是集合的根节点怎么办 ?

但有一个特例 : **当这个点是叶子节点时 , 复杂度是 $O(1)$ 的 (因为他没有儿子) . 而且不用考虑是根节点的情况 .**

那怎样保证每个点都是叶子节点呢 ?

显然 , 拘泥于这 $n$ 个点是没有用的 , 因为必定会至少有 1 个点是根 .

那我们就给每个点创造一个新的点 , 作为初始情况下的根 .

这样每次合并时 , 都一定是一个新点连到另一个新点上去 , 这样 , 原本在叶子节点上的有效点还是叶子节点 .

注意 , 新点的大小和贡献都应为 0 .

code :

```cpp
const int MAXN=100000+10;
int n,m,fa[MAXN<<1],sze[MAXN<<1],ans[MAXN<<1]; 
int find(const int k) {
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);	
}
signed main() {
	while(~scanf("%lld %lld\n",&n,&m)) {
		for(int i=1;i<=n;i++) sze[i]=0,ans[i]=0,fa[i]=i+n;
		for(int i=n+1;i<=n+n;i++) ans[i]=i-n,sze[i]=1,fa[i]=i;
		for(int i=1,op,p,q;i<=m;i++) {
			op=read(),p=read();
			if(op==1) {
				q=read();
				int P=find(p),Q=find(q);
				if(P==Q) continue;
				fa[P]=Q,sze[Q]+=sze[P],ans[Q]+=ans[P];
			}
			if(op==2) {
				q=read();
				int P=find(p),Q=find(q);
				if(P==Q) continue;
				sze[P]--,ans[P]-=p,fa[p]=Q,sze[Q]++,ans[Q]+=p;	
			}
			if(op==3) printf("%lld %lld\n",sze[find(p)],ans[find(p)]);
		}
	}		
	return 0;
}
```

---

## 作者：Huang_Yuhan (赞：1)

# 题目描述：

一开始有$n$个集合，第$i$个集合里为$\{i\}$

现在有$m$个操作。

$1\ x\ y$ 把$x$所在集合合并到$y$所在集合中去

$2\ x\ y$ 把$x$元素移动到$y$集合中去。

$3\ x$ 输出$x$元素所在集合中的元素个数和总和。

$n,m\leqslant 100,000$

# 解：

假如说没有$2$号操作，这就是一个加权并查集的板题。

为什么呢？

首先我们知道，并查集就是一棵树。加权并查集之所以可以处理$1,3$操作因为它不会把一棵树中的根给弄走了。

但是$2$号操作会，那怎么办呢？

我们再来想想，加权并查集是怎么处理$1$号操作的。

$x$这棵树的根本来它的父亲就是它自己，然后把 getfa(x)的父亲赋为getfa(y)。

但是在$2$号操作中会操作根。

所以我们建$n$个虚根。

一开始$i\rightarrow i'=n+i$

因为在操作中始终满足一棵树的根是$i'$。

所以时间复杂度为$O(n+m)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int fa[maxn],cnt[maxn],sum[maxn];
int getfa(int v)
{return fa[v]==v?v:fa[v]=getfa(fa[v]);}
int n,m;
int main()
{
	//freopen("ans.out","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++)fa[i]=i+n;
		for(int i=n+1;i<=2*n;i++)fa[i]=i,cnt[i]=1,sum[i]=i-n;
		int k,x,y;
		while(m--)
		{
			scanf("%d",&k);
			if(k==1)
			{
				scanf("%d%d",&x,&y);
				int fx=getfa(x);
				int fy=getfa(y);
				if(fx!=fy)
				{
					fa[fx]=fy;
					cnt[fy]+=cnt[fx];
					sum[fy]+=sum[fx];
					cnt[fx]=0;
					sum[fx]=0;
				}
			}
			if(k==2)
			{
				scanf("%d%d",&x,&y);
				int fx=getfa(x);
				int fy=getfa(y);
				if(fx!=fy)
				{
					cnt[fy]++;
					sum[fy]+=x;
					cnt[fx]--;
					sum[fx]-=x;
					fa[x]=fy;
				}
			}
			if(k==3)
			{
				scanf("%d",&x);
				int fx=getfa(x);
				printf("%d %d\n",cnt[fx],sum[fx]);
			}	
		}
	}
	return 0;
}
```

---

## 作者：HolseLee (赞：1)

同步发表在[蒟蒻的cnblogs](https://www.cnblogs.com/cytus/p/9517940.html)上

不得不说是一道神奇的题目

　　如果只有操作1和操作3，那就是一道普通的带权并查集。然而，还有个毁天灭地的操作2。。。因为并查集是不支持删除操作的，所以我们得想个办法表示某一个元素在该集合中被删除。

　　这里我们用一个数组$id[i]$记录$i$节点当前的编号，如果我们删除了一个点，我们就把$id[i]$指向一个新的地址，在原本的集合中删除掉它的信息，然后把这个新的地址与要合并的集合合并。原本的点就基本可以当作是“被废弃了”，因为我们每次查找一个点的集合的时候就直接$find(id[x])$。当然，$id[x]$一开始就赋值为$x$。

　　不过貌似有巨佬用可持久化并查集$A$了，并不知道怎么用可持久化并查集做。。。。。。

Code：

```cpp
//It is made by HolseLee on 22nd Aug 2018
//UVA11987
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2e5+7;
int n,m,id[N],fa[N],cnt[N],rk[N];
ll sum[N];
inline int read()
{
    char ch=getchar();int num=0;bool flag=false;
    while(ch<'0'||ch>'9'){if(ch=='-')flag=true;ch=getchar();}
    while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
    return flag?-num:num;
}
inline void print(int x)
{
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
inline int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
inline void merge(int x,int y)
{
    int fx=find(id[x]),fy=find(id[y]);
    if(rk[fx]>rk[fy]){
        fa[fy]=fx;
        sum[fx]+=sum[fy];
        cnt[fx]+=cnt[fy];
    }else{
        fa[fx]=fy;
        sum[fy]+=sum[fx];
        cnt[fy]+=cnt[fx];
        if(rk[fx]==rk[fy])rk[fy]++;
    }
}
inline void del(int x)
{
    int fx=find(id[x]);
    cnt[fx]--;sum[fx]-=(ll)x;
    id[x]=++n;
    fa[id[x]]=id[x];
    cnt[id[x]]=rk[id[x]]=1;
    sum[id[x]]=(ll)x;
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;++i)fa[i]=id[i]=i,sum[i]=(ll)i,cnt[i]=rk[i]=1;
        int op,x,y;
        for(int i=1;i<=m;++i){
            op=read();
            switch(op){
                case 1:
                    x=read();y=read();
                    if(find(id[x])!=find(id[y]))merge(x,y);
                    break;
                case 2:
                    x=read();y=read();
                    if(find(id[x])!=find(id[y])){
                        del(x);merge(x,y);
                    }
                    break;
                case 3:
                    x=read();
                    print(cnt[find(id[x])]);
                    putchar(' ');
                    print(sum[find(id[x])]);
                    putchar('\n');
                    break;
            }
        }
    }
    return 0;
}
```


---

## 作者：asuldb (赞：1)

这是一道神奇的题目，我调了大概一天多吧

首先hack一下翻译，操作3并没有要求查询后从其所在集合里删除该元素

于是我们来看一下这三个操作

第一个合并属于并查集的常规操作

第三个操作加权并查集也是可以解决的

至于第二个操作就是这个题的难点了

对于操作二的要求“ 将 $p$ 移动至包含 $q$ 的集合中,如果 $p$ 和 $q$ 已经在一个集合中,忽视此项操作”,我们可以发现这个操作其实隐含了一个删除的操作，即先从原集合中将 $p$删除，再将其移动到集合$q$中

我们知道并查集是并不支持删除操作的，于是我们必须对于这个毁天灭地的操作二想出一些奇技淫巧

于是呢，对于操作二，我们可以用一个虚点来代替那个要被从某个集合中删除的点，我们使这个虚点继承这个要被删除的点的所有状态，比如说元素和、元素个数和他的代表元素是谁，而我们在以后$find$里路径压缩时只要遇到以这个被删除的点为代表元素的元素，我们把他们的代表元素更新成这个虚点就好了

至于我们如何在路径压缩里判断这个点是否已经被从被某个虚点代替，这里就是真·奇技淫巧了

或许我们可以用map，但map的一次$find$复杂度可是$O(log_2\ n)$的，我们，可能只有我在这种多组数据的会t的非常欲仙欲死，于是我们的奇技淫巧就要登场了

它就是unordered_map

这是个什么东西呢，我们都知道map是用红黑树实现的，所以map内部$key$是有序的，但这也导致我们查询一个元素是否存在是要$O(log_2\ n)$的

而这个unordered_map，是c++ 11的新特性，是一个$key$无序的map，其内部是用哈希表实现的，单次查询的复杂度可以达到$O(1)$的

于是就是代码了
```cpp
#include<iostream>
#include<map>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<tr1/unordered_map>
//unordered_map所需的头文件，同时在命名空间里加::tr1
#define re register
#define maxn 100001
#define gc getchar
using namespace std::tr1;
using namespace std;
unordered_map<int,int> s;
int fa[maxn<<2],tot[maxn<<2],sum[maxn<<2];
//因为我们虚点的是要用到n+1,n+2...的，所以多开几倍空间
int n,m;
inline int read()
{
    char c=gc();
    int dx=0;
    while(c<'0'||c>'9') c=gc();
    while(c>='0'&&c<='9')
      dx=(dx<<3)+(dx<<1)+c-48,c=gc();
    return dx;
}
int find(int x)
{
    if(x==fa[x]) return fa[x];
    if(s.count(fa[x])) fa[x]=s[fa[x]];
    //如果一个元素的代表元素已经被删除了，那么我们就把它的代表元素换成其映射的那个虚点
    return fa[x]=find(fa[x]);
}
void write(int x)
{
	if(x>9) write(x/10);
	putchar(x%10+48);
}
int main()
{  
    while(scanf("%d%d",&n,&m)!=EOF)//多组数据标配
    {
    	s.clear();
    	for(re int i=1;i<=n;i++)
        	fa[i]=sum[i]=i,tot[i]=1;
    	while(m--)
    	{
        	int p=read();
        	if(p==1)
        	{
            	int xx=find(read());
            	int yy=find(read());
            	if(xx==yy) continue;
            	tot[xx]+=tot[yy];
            	sum[xx]+=sum[yy];
            	fa[yy]=xx;
            	tot[yy]=sum[yy]=0;//常规合并操作
        	}
        	if(p==2)
        	{
            	int x=read();
            	int xx=find(x);
            	int yy=find(read());
            	if(xx==yy) continue;
            	if(fa[x]==x&&tot[x]==1)
            	{
                	tot[x]=0;
                	sum[x]=0;
                	fa[x]=yy;
                	tot[yy]+=1;
                	sum[yy]+=x;
                	continue;
            	}//如果这个元素代表元素是它自己，且元素个数为1，那它就不可能是其他元素的代表元素，于是我们直接fa[x]=yy就好了
            	if(s.find(x)==s.end())
            	{
            		s[x]=++n;
            		if(xx==x) fa[n]=n;
            		else fa[n]=xx;//如果这个元素代表元素是它自己，那么虚点继承这个状态的时候，让虚点的代表元素也是它自己就好了
            		tot[n]=tot[xx]-1;
            		sum[n]=sum[xx]-x;
            		tot[yy]+=1;
            		sum[yy]+=x;//向新集合添加x
            		tot[xx]-=1;
            		sum[xx]-=x;//从原集合中删除x
            		if(xx==x) sum[xx]=tot[xx]=0;
           			fa[x]=yy;
				}else fa[x]=yy,sum[xx]-=x,tot[xx]-=1,tot[yy]+=1,sum[yy]+=x;
    //如果这个元素已经被映射过了，即它已经被加入某一个集合，所以这个时候它不可能成为代表元素，于是这个时候我们也可以直接进行删除和合并的操作
        	}
        	if(p==3)
        	{
            	int xx=find(read());
            	write(tot[xx]),putchar(' '),write(sum[xx]);
            	putchar(10);
        	}
    	}
    }
    return 0;
}
```

---

## 作者：漠寒 (赞：1)

## 题意

操作1：将两点所在的区间合并。

操作2：将一点移至另一点所在集合内。

操作3：求一点所在区间的元素个数和元素的总和。

## 分析

并查集的大小以及元素和是很好计算的，在合并时将“认亲”的点的对应值加给它祖先就行了。主要是操作2。

对于一个点单独抽离出来，我们发现是不好弄的，按照常规的方法做的话，如果直接以它向集合的祖先相连，则它的子孙们也会受影响。而去除这一影响的关键就在于建虚点。即用一个实际并不存在的点来代表集合的祖先，这样挪走集合内的任意一个点，对其它点都不会造成影响，因为没有人会管它。于是我们在初始给每个点创造一个属于它自己的虚点，照常合并即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,fa[200005],m,x,y,op;
int sum[200005],siz[200005];
int p,q;
inline void read(int &res){
	char c;
	int f=1;
	res=0;
	c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')res=(res<<1)+(res<<3)+c-48,c=getchar();
	res*=f;
}
inline int find(int x){
	if(fa[x]!=x)return fa[x]=find(fa[x]);//压缩路径 
	return x;
}
signed main(){
	while(cin>>n>>m){
		for(int i=1;i<=n;i++)fa[i]=i+n,sum[i+n]=i;
		for(int i=n+1;i<=2*n;i++)fa[i]=i,siz[i]=1;//建虚点 
		while(m--){
			cin>>op;
			if(op==1){
				read(p);read(q);
				int x=find(p),y=find(q);
				if(x==y)continue;
				if(siz[x]<siz[y]){//按秩合并 
					fa[x]=y;
					sum[y]+=sum[x];//合并 
					siz[y]+=siz[x];
				}
				else {
					fa[y]=x;
					sum[x]+=sum[y];
					siz[x]+=siz[y];
				}
			}
			if(op==2){
				read(p);read(q);
				int x=find(p),y=find(q);
				if(x==y)continue;
				fa[p]=y;
				sum[y]+=p;
				sum[x]-=p;
				siz[y]++;
				siz[x]--;
			}
			if(op==3){
				read(q);
				int x=find(q);
				cout<<siz[x]<<" "<<sum[x]<<endl;
			}
		}
	}
	return 0;
} 
```


---

## 作者：gSE2xWE (赞：1)

[更好的阅读体验](https://www.cnblogs.com/loney-s/p/12940103.html)

# 题目

[传送门](https://www.luogu.com.cn/problem/UVA11987)

# 思路

如果只有操作1和操作3，

那么这道题就是道板的冰茶姬

只需要将元素和与大小记录在根上就行了

主要的难点在于操作2

为什么操作2很难呢？

因为如果我们将一个冰茶姬的一个元素提出来的时间复杂度不可接受

但是我们反向思考

如果删除一个元素

我们只需要$O(1)$的时间复杂度维护这一个冰茶姬

对于另一个冰茶姬也只需要$O(1)$的时间复杂度合并

同时我们考虑因为元素在原来的冰茶姬里面已经删除了

所以这个元素不会再移动

但是在另一个冰茶姬里面会有影响

我们建一个hash表就行了

也就是我们对于原来的冰茶姬我们不删除元素

只加入一个新的元素到另一个冰茶姬里面就行了

对于之后涉及到元素的操作

我们只需要用hash表里面的编号进行操作就行了

最多加$m$个虚点

因为$m和n$同阶

实际的复杂度还是$O(nlog_n)$

# 代码

```cpp
#include<iostream>
using namespace std;
void read(int &x)
{
	x=0;
	int f=1;
	char c=getchar();
	while('0'>c||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while('0'<=c&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	x*=f;
}
void write(long long x)
{
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int n,m;
int cnt;
int h[100005];
int fa[200005];
int siz[200005];
long long s[200005];
void makeset(int n)
{
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		h[i]=i;
		s[i]=i;
		siz[i]=1;
	}
}
void add(int u,int w,int add)
{
	siz[u]+=w;
	s[u]+=add;
}
int findset(int u)
{
	if(fa[u]==u)
		return u;
	fa[u]=findset(fa[u]);
	return fa[u];
}
void unionset(int a,int b)
{
	int u=findset(a);
	int v=findset(b);
	if(u==v)
		return;
	fa[u]=v;
	siz[v]+=siz[u];
	s[v]+=s[u];
}
int main()
{
	while(~scanf("%d %d",&n,&m))
	{
		cnt=n;
		makeset(n+m);
		for(int i=1,opt,u,v;i<=m;i++)
		{
			read(opt);
			if(opt==1)
			{
				read(u);
				read(v);
				unionset(h[u],h[v]);
			}
			if(opt==2)
			{
				read(u);
				read(v);
				int fau=findset(h[u]);
				int fav=findset(h[v]);
				if(fau==fav)
					continue;
				add(fau,-1,-u);
				add(fav,1,u);
				h[u]=++cnt;
				s[cnt]=u;
				fa[h[u]]=h[v];
			}
			if(opt==3)
			{
				read(u);
				int fau=findset(h[u]);
				write(siz[fau]);
				putchar(' ');
				write(s[fau]);
				putchar('\n');
			}
		}
		
	}
	return 0;
}
```



---

## 作者：hswfwkj_ (赞：0)

## [UVA11987 Almost Union-Find](https://www.luogu.com.cn/problem/UVA11987)

## 思路：
这道题的难点在于二操作，它需要把一个集合中的某个元素移到另一个集合去，那么普通的并查集就不能解决本题，因为假设这样一组数据：
```
5 4
1 3 4
1 2 3
2 3 1
3 4
```
在 $2$ 操作之前，情况是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/apprjq13.png)

如果只是简单的把 $3$ 移到 $1$ 的集合里，就会变成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/kwhifggy.png)

我们看到，本不应该被移动的 $2$，现在也到了 $1$ 的集合里，这不是我们想看到的。

那么解决办法是什么呢？
其实，我们可以开虚点来避免这种情况，具体来说，就是给每个编号为 $i$ 的节点创建一个新的编号为 $i+1$ 的虚拟节点，当我们移动 $i$ 号节点时，虚拟节点并不会被移动，这样，我们只需保证每个实点都连接虚点，就可以完美避免移动一个实点，有别的实点跟着移动的情况。合并也只需要在虚点之间合并即可。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int f,cnt,sum;
}a[300005];
int n,m;
int find(int k)
{
	if(a[k].f==k)return k;
	else return (a[k].f=find(a[k].f));
}
void Union(int x,int y)
{
	a[x].f=y;
	a[y].cnt+=a[x].cnt;
	a[y].sum+=a[x].sum;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0); 
	while(cin>>n>>m)
	{
		for(int i=1;i<=n;i++)
		{
			a[i].f=i+n;
			a[i].cnt=1;
			a[i].sum=i;
		}
		for(int i=n+1;i<=n*2;i++)
		{
			a[i].f=i;
			a[i].cnt=1;
			a[i].sum=i-n;
		}
		for(int i=1;i<=m;i++)
		{
			int op,p,q;
			cin>>op>>p;
			if(op==1)
			{
				cin>>q;
				if(find(p)==find(q))continue;
				Union(find(q),find(p));
			}
			if(op==2)
			{
				cin>>q;
				int fa=find(p);
				if(fa==find(q))continue;
				a[fa].cnt--;a[fa].sum-=p;
				Union(p,find(q));
			}
			if(op==3)
			{
				int fa=find(p);
				cout<<a[fa].cnt<<' '<<a[fa].sum<<'\n'; 
			}
		}
	}
	return 0;
} 
```

---

