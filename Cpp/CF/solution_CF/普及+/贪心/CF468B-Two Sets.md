# Two Sets

## 题目描述

> 给出 $n$ 个各不相同的数字，将它们分别放入 $A$ 和 $B$ 两个集合中，使它们满足：
> * 若数字 $x$ 在集合 $A$ 中，那么数字 $a-x$ 也在集合 $A$ 中；
> * 若数字 $x$ 在集合 $B$ 中，那么数字 $b-x$ 也在集合 $B$ 中。

## 样例 #1

### 输入

```
4 5 9
2 3 4 5
```

### 输出

```
YES
0 0 1 1
```

## 样例 #2

### 输入

```
3 3 4
1 2 4
```

### 输出

```
NO
```

# 题解

## 作者：pufanyi (赞：14)

感觉网上全是并查集的题解。

没有贪心？

感觉贪心比并查集好想啊……

首先我们想到的肯定是开个`set`大力匹配，然而发现对于一个$x$可能$a-x$和$b-x$都在序列中，于是我们就陷入两难了。

如何解决这个问题呢？

现在我们假设$a\ge b$。

我们每次贪心地选出没有匹配过的数的最小值，设其为$x$。

假设我们发现$a-x$和$b-x$都在序列中且都没有被匹配过。

我们会发现$x$一定与$a - x$匹配。

假设答案是$x$与$b - x$匹配，那也就是说$a - x$不在$A$集合里，所以其在$B$集合里，则与之匹配的是$b - (a - x) = x + (b - a)\le x$，但由于$x$是序列中的最小数，所以不存在$b - (a - x)$。

代码也很简单：

```cpp
#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int maxn = 100005;

int ans[maxn];

struct EE
{
	int x, id;

	inline bool operator < (const EE& other) const
	{
		return this->x < other.x;
	}
} aa[maxn];

set<EE> ss;

int main()
{
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	ss.clear();
	bool f = false;
	if(a < b)
	{
		swap(a, b);
		f = true;
	}
	for(int i = 1; i <= n; ++i)
	{
		EE aa;
		scanf("%d", &aa.x);
		aa.id = i;
		ss.insert(aa);
	}
	memset(ans, 0xff, sizeof(ans));
	while(!ss.empty())
	{
		set<EE>::iterator it = ss.begin();
		EE tx = *it;
		tx.x = a - it->x;
		set<EE>::iterator x = ss.lower_bound(tx);
		if(x != ss.end() && x->x + it->x == a)
		{
			ans[x->id] = ans[it->id] = 0;
			if(x->id != it->id)
			{
				ss.erase(x);
				ss.erase(it);
			}
			else
				ss.erase(x);
		}
		else
		{
			tx.x = b - it->x;
			x = ss.lower_bound(tx);
			if(x != ss.end() && x->x + it->x == b)
			{
				ans[x->id] = ans[it->id] = 1;
				if(x->id != it->id)
					ss.erase(it);
				ss.erase(x);
			}
			else
				return puts("NO"), 0;
		}
	}
	puts("YES");
	for(int i = 1; i <= n; ++i)
		printf("%d ", ans[i] ^ f);
	return 0;
}
```



---

## 作者：D_14134 (赞：10)

## 思路：
对于一个x来说，能分成以下4种情况（这里a!=b）：

1.a-x不存在，b-x不存在。这种情况直接输出NO。

2.a-x存在，b-x不存在。这种情况把x和a-x放在集合A中。

3.a-x不存在，b-x存在。这种情况把x和b-x放在集合B中。

4.a-x存在，b-x存在。这种情况比较我们就不能直接确定要放A还是要放B了。

那么我们接下还需要判断是否存在y有a-y=b-x或者b-y=a-x其中之一存在。

如果存在a-y=b-x，那么就把x和a-x和y和a-y(b-x)都放到集合A中。同理b-y=a-x存在的情况。

如果都不存在就输出NO。

这里用并查集来维护即可。
# code
```cpp
#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 100010 
using namespace std;
int maxx,n,a,b,fa[maxn],val[maxn];
map<int,int> pre;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void hb(int x,int y){int fx=find(x),fy=find(y);if(fx!=fy) fa[fx]=fy;}
int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++){
		scanf("%d",&val[i]);
		pre[val[i]]=i;
		maxx=max(maxx,val[i]);
		fa[i]=i;
	}fa[0]=0;fa[n+1]=n+1;
	if(maxx>=max(a,b)){printf("NO");return 0;}
	for(int i=1;i<=n;i++){
		if(pre[a-val[i]]>0) hb(i,pre[a-val[i]]);
		else hb(i,n+1);
		if(pre[b-val[i]]>0) hb(i,pre[b-val[i]]);
		else hb(i,0);
	}
	int head=find(0),tail=find(n+1);
	if(head!=tail){
		printf("YES\n");
		for(int i=1;i<=n;i++){
			if(i!=1) printf(" ");
			if(find(i)==head) printf("0");
			else printf("1");
		}
	}
	else printf("NO");
}
```


---

## 作者：BreakPlus (赞：5)

[$\large \text{CF468B Two Sets}$](https://www.luogu.com.cn/problem/CF468B)

### $\text{Description}$

把序列 $p$ 中的所有元素分到 $A,B$ 两个集合中，使得当数 $x$ 被分到集合 $A$ 中的时候，$a-x$ 也被分到集合 $A$；数 $x$ 被分到 $B$ 时，$b-x$ 也被分到集合 $B$。

### $\text{Solution}$

好题。

第一波，我们把 $A$ 集合和 $B$ 集合都不能放的数找出来，如果有直接输出 ``NO``，这种情况显然是 $a-x$ 与 $b-x$ 都不在序列 $p$ 中。

然后我们把必须同在 $A$ 集合/$B$ 集合的数连一条边，组成一张图。

一个显而易见的结论：一个连通块内的元素必须放在同一个集合中。

假设我们有元素 $x_1,x_2,x_3$，其中 $a-x_1=x_2,b-x_1=x_3$，图中就有 $x_1 \to x_2$ 和 $x_1\to x_3$ 两条边。

如果 $x_1$ 归集合 $A$，则 $x_2$ 必归集合 $A$，$x_3$ 若归集合 $B$ 则 $x_1$ 也要归集合 $B$，所以 $x_3$ 也得归集合 $A$；如果 $x_1$ 归集合 $B$ 同理。


但是有些元素不能归某个集合，因为与其配对的 $a-x$ 或 $b-x$ 在 $p$ 中不存在。我们用一个数组 ``must`` 记录一个元素的状态（$0$ 是均可；$1$ 是只能归 $A$；$2$ 是只能归 $B$）。如果一个连通块内 ``must`` 数组发生冲突，即同时有 $1$ 和 $2$，输出 ``NO``。

如果没有发生冲突，就可以对连通块染色了。

### $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,p[100010],col[100010],colt;
int must[100010],vis[100010]; vector<int>vec[100010];
int ans[100010];
map<int,int>mp;
inline int dfs(int x){
	vec[colt].push_back(x);
	vis[x]=true;
	if(!mp.count(a-p[x])) must[x]=2;
	else if(!vis[mp[a-p[x]]]) dfs(mp[a-p[x]]);
	
	if(!mp.count(b-p[x])){
		if(must[x]){
			puts("NO");
			exit(0);
		}else must[x]=1;
	}else if(!vis[mp[b-p[x]]]) dfs(mp[b-p[x]]);
}
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) cin>>p[i],mp[p[i]]=i;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			colt++;
			dfs(i);
		}
	}
	for(int i=1;i<=colt;i++){
		int len=vec[i].size();
		for(int j=0;j<len;j++){
			if(must[vec[i][j]]){
				if(col[i] && col[i]!=must[vec[i][j]]){
					puts("NO");
					exit(0);
				}
				col[i]=must[vec[i][j]];
			}
		}
	}
	for(int i=1;i<=colt;i++){
		int nowcol=col[i],len=vec[i].size();
		if(nowcol==0) nowcol=1;
		for(int j=0;j<len;j++) ans[vec[i][j]]=nowcol;
	}
	puts("YES");
	for(int i=1;i<=n;i++) cout<<ans[i]-1<<" ";
	return 0;
} 
```

---

## 作者：Fading (赞：4)

怎么没有$2-SAT\ ??????$

这道题，显然是由一堆限制构成的，所以考虑$2-SAT$。

简单说一下吧。

我们先开一个$map$，记录每一个数的出现位置（$x[3]=2$，则$map[2]=3$）。

然后枚举每一个数$x[i]$

若$a-x[i],b-x[i]$都没出现过，输出$NO$

若仅仅是$a-x[i]$出现过，则$x[i],map[a-x[i]]$必在$A$中。

若仅仅是$b-x[i]$出现过，则$x[i],map[b-x[i]]$必在$B$中。

否则，

若$x[i]$在$A$中，则$map[a-x[i]]$也在$A$中。

若$x[i]$在$B$中，则$map[a-x[i]]$也在$B$中。

若$x[i]$在$A$中，则$map[b-x[i]]$也在$A$中。

若$x[i]$在$B$中，则$map[b-x[i]]$也在$B$中。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
#ifdef Fading
#define gc getchar
#endif
inline int read(){
    int x=0,f=1;char ch=gc();
    while(!isdigit(ch)) {if (ch=='-') f=-1;ch=gc();}
    while(isdigit(ch)) x=x*10+ch-'0',ch=gc();
    return x*f;
}
struct edge{
    int to,nxt;
}g[1000001];
int tot,head[1000001],len,n,A,B,m,col[1000001],id;
int vis[1000001],dfn[1000001],low[1000001];
stack<int> S;
inline void made(int from,int to){
    g[++tot].to=to;g[tot].nxt=head[from];head[from]=tot;
}
void tarjan(int u){
    low[u]=dfn[u]=++id;S.push(u);vis[u]=1;
    for (int i=head[u];i;i=g[i].nxt){
        int v=g[i].to;
        if (!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if (vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (low[u]==dfn[u]){
        len++;
        while (S.top()!=u){
            int x=S.top();S.pop();
            col[x]=len;vis[x]=0;
        }
        col[u]=len;S.pop();vis[u]=0;
    }
}
int x[1000001];
map<int,int> has;
signed main(){
    n=read(),A=read(),B=read();
    for (int i=1;i<=n;i++){
        x[i]=read();has[x[i]]=i;
    }
    for (int i=1;i<=n;i++){
        int flaga=-1,flagb=-1;
        if (has.count(A-x[i])) flaga=has[A-x[i]];
        if (has.count(B-x[i])) flagb=has[B-x[i]];
        if ((~flaga)&&(~flagb)){
            made(i*2,flaga*2);
            made(i*2+1,flagb*2+1);
            made(i*2+1,flaga*2+1);
            made(i*2,flagb*2);
        }else if (~flaga){
            made(flaga*2+1,flaga*2);
            made(i*2+1,i*2);
        }else if (~flagb){
            made(flagb*2,flagb*2+1);
            made(i*2,i*2+1);
        }else{
            printf("NO\n");
            return 0;
        }
    }
    for (int i=2;i<=2*n+1;i++){
        if (!dfn[i]) tarjan(i);
    }
    for (int i=1;i<=n;i++){
        if (col[2*i]==col[2*i+1]){
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    for (int i=1;i<=n;i++){
        printf("%d ",(int)(col[2*i]>col[2*i+1]));
    }
    return 0;
}

```


---

## 作者：滑不拉稽 (赞：3)

## upd：将case3的解释详细化。

貌似是51nod上的弱化版（ ~~指只有一组数据~~ ）。

# 思路

对于给出的任意一个数 **x**，有几种情况：

### case 1：
若 **a-x**,**b-x** 都不存在，返回 **NO**。

### case 2：
若 **a-x** 存在，则 **x**,**a-x** 都放到 A 里面。

若 **b-x** 存在，则 **x**,**b-x** 都放到 B 里面。

### case 3：
若 **a-x**,**b-x** 都存在，进一步讨论：

若 **b-(a-x)** 存在，由题意 **x**,**a-x** 必须同时要在 A 中，而 **a-x**,**b-(a-x)** 是必须同时要在 B 中，而 **a-x** 不能同时位于两个集合中，为符合题意，所以我们选择把 **x**,**a-x**,**b-(a-x)** 都并入同一个集合 A。

同理，若 **a-(b-x)** 存在，则我们选择将 **x**,**b-x**,**a-(b-x)** 都并入同一个集合 B。

# 方法
并查集维护，具体维护方式见代码注释。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f==1?x:-x;
} 
const int N=1e5+10;
int n,a,b,val[N],fa[N];
map<int,int> pre;

//并查集初始化中，将i=0与i=n+1也初始化
//其中与0并在一起的默认为A集合，与n+1并在一起的默认为B集合 
void init(){for(int i=0;i<=n+1;++i)fa[i]=i;}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y){int xx=find(x),yy=find(y);if(xx!=yy)fa[xx]=yy;}

signed main()
{
	n=read(),a=read(),b=read();
	for(int i=1;i<=n;++i)
	{
		val[i]=read();
		pre[val[i]]=i;//将数值与下标对应，判断时如果pre[a]>0即说明a存在 
	}
	init();
	int flag1,flag2;//用来分别标记a-x，b-x是否存在 
	for(int i=1;i<=n;++i)
	{
		flag1=0;flag2=0;
		int x=val[i];
		if(pre[a-x]>0) flag1=1;
		if(pre[b-x]>0) flag2=1;
		if( (!flag1) && (!flag2) ) {puts("NO");return 0;}//都不存在，直接返回 
		else if( flag1 && (!flag2) ) merge(i,pre[a-x]),merge(i,0);//与0合并表示属于A集合 
		else if( (!flag1) && flag2 ) merge(i,pre[b-x]),merge(i,n+1);//与n+1合并表示属于B集合 
		else
		{
			if(pre[b-(a-x)]>0)merge(i,pre[a-x]),merge(i,pre[b-(a-x)]);//将i,a-x,b-(a-x)都并进A里 
			else if(pre[a-(b-x)]>0)merge(i,pre[b-x]),merge(i,pre[a-(b-x)]);//将i,b-x,a-(b-x)都并进B里 
		}
	}
	int A=find(0),B=find(n+1);
	if(A==B){puts("NO");return 0;}//注意，不判断会WA一个点，不可能存在同时属于两个集合的数 
	else
	{
		puts("YES");
		for(int i=1;i<=n;++i)
		{
		 	find(i)==A?printf("0 "):printf("1 ");
		}
	}
	return 0;
}
```



---

## 作者：UnyieldingTrilobite (赞：1)

首先，对于给出的任意一个数 $x$：

若 $a-x$ 亦被给出，则此两者在同一个集合里；

若其未被给出，则 $x\in B$。

这是 $x\in A$ 等价于 $a-x\in A$ 的直接推论。

$b-x$ 同理有类似结论，然后就可以并查集维护了。

实现大概就是开两个虚点表示两个集合本身，然后最后如果发现两个集合连通了就不行，反之可以，然后把所有推出必须放 $B$ 的放 $B$，其他统一放 $A$，就可以了。

复杂度 $\Theta(n\alpha(n))$，瓶颈在并查集。（是否给出那一段可以用哈希表，然后这个并查集复杂度其实可以显式建出图然后搜索，可以把这个 $\alpha(n)$ 吃掉，不过实际上没什么大意义。）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e5+9;
int fa[N],sz[N];
int n,a,b,val[N];
int findf(int x){
	return x==fa[x]?x:fa[x]=findf(fa[x]);
}
void merge(int u,int v){
	if((u=findf(u))==(v=findf(v)))return;
	if(sz[u]>sz[v])swap(u,v);
	sz[fa[u]=v]+=sz[u];
}
unordered_map<int,int>umap;
signed main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;++i)cin>>val[i],umap[val[i]]=i;
	for(int i=1;i<=n;++i)sz[fa[i]=i]=1;
	sz[fa[0]=0]=1,sz[fa[n+1]=n+1]=1;
	for(int i=1;i<=n;++i){
		if(umap.find(a-val[i])!=umap.end())merge(i,umap[a-val[i]]);
		else merge(i,0);
		if(umap.find(b-val[i])!=umap.end())merge(i,umap[b-val[i]]);
		else merge(i,n+1);
	}
	if(findf(0)==findf(n+1))puts("NO");
	else{
		puts("YES");
		for(int i=1;i<=n;putchar(" \n"[i++==n])){
			if(findf(i)==findf(0))putchar('1');
			else putchar('0');
		}
	}
	return 0;
}
```

---

## 作者：傅思维666 (赞：0)

## 题解：

很容易看出来这道题最难搞的是冲突的处理，也就是a-x,b-x和x同时存在于原数列的情况。

于是就有了思路（比较清奇，因为是先想到什么东西难搞，然后再回推思路）

也就是：

对于一个$x$来说，能分成以下4种情况进行分类讨论：

1.$a-x$不存在，$b-x$不存在。这种情况直接NO。

2.$a-x$存在，$b-x$不存在。这种情况是集合A。

3.$a-x$不存在，$b-x$存在。这种情况是集合B。

4.$a-x$存在，$b-x$存在。

第四种情况就是着重要讨论的冲突情况。

那么我们接下就需要再找到一个证据来唯一确定这个数的从属集合。也就是：还需要判断是否存在$y$有$a-y=b-x$或者$b-y=a-x$其中之一存在。

如果存在$a-y=b-x$，那么就把$x$和$a-x$和$y$和$a-y(b-x)$都放到集合A中。同理$b-y=a-x$存在的情况。如果都不存在就输出NO。

然后我们采用并查集来维护这个东西。

我还写了个版本是$set$直接模拟维护的，但是挂了，，，有兴趣的同学请去讨论区康康，感谢抓虫。

代码：

```cpp
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
int maxx,n,a,b,fa[maxn],val[maxn];
map<int,int> mp;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx!=fy)
		fa[fx]=fy;
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&val[i]);
		mp[val[i]]=i;
		maxx=max(maxx,val[i]);
		fa[i]=i;
	}
	fa[0]=0;
	fa[n+1]=n+1;
	if(maxx>=max(a,b))
	{
		printf("NO");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(mp[a-val[i]]>0) 
			merge(i,mp[a-val[i]]);
		else 
			merge(i,n+1);
		if(mp[b-val[i]]>0) 
			merge(i,mp[b-val[i]]);
		else 
			merge(i,0);
	}
	int l=find(0),r=find(n+1);
	if(l!=r)
	{
		puts("YES");
		for(int i=1;i<=n;i++)
		{
			if(i!=1) 
				printf(" ");
			if(find(i)==l) 
				printf("0");
			else 
				printf("1");
		}
	}
	else 
		puts("NO");
	return 0;
}
```



---

