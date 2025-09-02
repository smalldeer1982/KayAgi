# New Year Tree

## 题目描述

You are a programmer and you have a New Year Tree (not the traditional fur tree, though) — a tree of four vertices: one vertex of degree three (has number 1), connected with three leaves (their numbers are from 2 to 4).

On the New Year, programmers usually have fun. You decided to have fun as well by adding vertices to the tree. One adding operation looks as follows:

- First we choose some leaf of the tree with number $ v $ .
- Let's mark the number of vertices on the tree at this moment by variable $ n $ , then two vertexes are added to the tree, their numbers are $ n+1 $ and $ n+2 $ , also you get new edges, one between vertices $ v $ and $ n+1 $ and one between vertices $ v $ and $ n+2 $ .

Your task is not just to model the process of adding vertices to the tree, but after each adding operation print the diameter of the current tree. Come on, let's solve the New Year problem!

## 样例 #1

### 输入

```
5
2
3
4
8
5
```

### 输出

```
3
4
4
5
6
```

# 题解

## 作者：inexistent (赞：9)

代码与更好的阅读效果，详见我的[博客](https://www.cnblogs.com/qixingzhi/p/9309102.html)

思路分析：

　　给出q个操作，每次在一个节点上接上两个叶子。每一次询问树的直径。

　　暴力做法：每一次操作暴力BFS两遍……然而……复杂度时\(O(Q * 2n\)，爆到不知哪里去了。

　　其实我们会发现，除非新加进来的两个点能够对直径产生影响，直径根本不会变。所以我们只需要考虑新加进来的点对原图的影响。

　　那么如何操作呢？先假设没经过任何操作之前，直径的端点时2和3（事实上2,3,4中任意两个都可以），设直径的端点1为A，端点2为B。每加进来两个点x,y时，若dist(x,A)或dist(x,B)大于原先的直径，则用它们更新，并且将直径的另一个端点设置为x或y。

　　下面来证明这样的做法的正确性：

　　由于在讲树的直径的时候我们提到过，从任意一个点出发进行BFS，所能到达的最远点一定是树的一个直径之一。

　　先假设新加进来的两个点x,y不存在，那么原先的树的直径就是A->B，并且一定是最长的了。设x,y的父亲节点为v。那么从v所能到达的最远的点一定是A或B。并且x或y到v的距离只有1，也只能是1。所以从x或y出发遍历所能够到达的最远的点一定也是A或B。而由于之前的直径是最长的，所以我当前的直径要比上一轮更长，只能是加了一，而这个1就是从x或y到v的距离的距离中产生的。

　　所以我们选择x来更新（因为x和y其实是一样的，你不可能有一条直径是从x到y的，因为这样只能是2，而刚开始就已经是2了）。分别求出x到A与B的距离，如果x到A更新成功，则B=x；如果x到B更新成功，则A=x；事实上，它们只有一个能更新成功。

　　于是现在问题就转化为了求两点之间距离了，LCA随便搞一搞就好了。这题还不用Dfs预处理，真是太可爱了……

代码注意点：

　　由于有q次操作，每次操作增加两个点，所以点的数目是\(2q+4\)，而不是\(q+4\)

---

## 作者：fangxk2003 (赞：3)


## Solution

首先要知道一个定理，在一棵树中，每次加1个节点，直径最多增长1
而且一定是有一个顶点是没有移动的（感性认识一下就能发现）。
那么我们每次要一个节点新增两个相邻的节点该怎么办？？
其实是跟增长一个节点一样的，因为这两个点是连向同一个点的
这样的话我们就只需要维护直径的两个端点就好了（有多个的话随便两个）
我们先令1为根，每次新增点的时候维护倍增数组
再与当前直径的两个端点用$lca$计算一下距离，如果直径大了就更新
时间复杂度是$O(nlogn)$的

## Warning
有一个需要特别注意的地方，数组的范围大小至少开两倍（因为要加两个点）
我就是因为没有注意这个细节结果TLE了？？？！！！

## Code

```cpp
#include <cstdio>
#include <algorithm>
#define N 2000010
#define P 21

using namespace std;

inline int read() {
    int x = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x;
}

struct Node{
    int to, nxt;
}e[N];

int tot, cnt, q, d1, d2, prelen, lst[N], dep[N], c[N][P];

inline void add(int u, int v) {
    e[++tot].to = v;
    e[tot].nxt = lst[u];
    lst[u] = tot;
}

void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    c[x][0] = fa;
    for (int i = 1; i < P; ++i)
        c[x][i] = c[c[x][i - 1]][i - 1];
    for (int i = lst[x]; i; i = e[i].nxt) {
        if (e[i].to == fa) continue;
        dfs(e[i].to, x);
    }
}

inline int lca(int x, int y) {
    if (dep[x] != dep[y]) {
        if (dep[x] < dep[y]) swap(x, y);
        int jump = dep[x] - dep[y];
        for (int i = 0; i < P; ++i)
            if (jump & (1 << i)) x = c[x][i];
    }
    if (x == y) return x;
    for (int i = P - 1; i >= 0; --i)
        if (c[x][i] != c[y][i]) {
            x = c[x][i];
            y = c[y][i];
        }
    return c[x][0];
}

inline void init() {
    add(1, 2);
    add(1, 3);
    add(1, 4);
    cnt = 4;
    q = read();
    d1 = 2;
    d2 = 3;
    dfs(1, 1);
    prelen = 2;
}

inline void solve() {
    for (int i = 1; i <= q; i++) {
        int x;
        x = read();
        add(x, ++cnt);
        add(x, ++cnt);
        dfs(x, c[x][0]);
        int l1 = lca(x, d1);
        int l2 = lca(x, d2);
        int len1 = dep[x] + dep[d1] - dep[l1] * 2, len2 = dep[x] + dep[d2] - dep[l2] * 2;
        if (len1 + 1 <= prelen && len2 + 1 <= prelen) printf("%d\n", prelen);
        else
        if (len1 > len2) {
            prelen = len1 + 1;
            printf("%d\n", prelen);
            d2 = cnt;
        }
        else {
            prelen = len2 + 1;
            printf("%d\n", prelen);
            d1 = cnt;
        }
    }
}

int main() {
    init();
    solve();
    return 0;
}
```

---

## 作者：王炸拆开打 (赞：2)

## 核心算法：LCA（最近公共祖先）

### 核心标签：树的直径（第二部分讲解）

------------

### 第一部分：

通过题目，我们可以知道其实本题就是**在一棵树上添加叶节点**，然后更新**树的直径**

我们可以通过**LCA算法**来得知目前加进来的点与**关键点（树的直径的两个端点**）的距离。公式为：

$Len(u,v)=dep[u]-dep[lca]+dep[v]-dep[lca]$

$U,V$为树的直径的两个端点,$X$为新加入的点（两点深度一样，更新端点只用一个新点即可）

勿忘倍增数组的维护：

$f[x][0]=father$与$f[x][i]=f[f[x][i-1]][i-1]$

#### 总而言之就是：

求出len(u,v)、len(u,x)、len(v,x)->

判断直径是不是小于新点到两端点距离的其中一个->

小于则更新



------------
### 第二部分（~~dalao~~可以跳过）：

 _树的直径_ ，定义为**一棵树上最远的两个节点的路径**

正常情况下需要两次$DFS$,但是本题已经给出初始的树，所以我们直接自己就能知道

所以，我们人为的规定```(2,3)(3,4)(2,4)```任意一组都可以为树的直径的端点，自己喜欢就好，本人```(2,3)```


------------
代码中还有相关注释方便大家阅读：
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,s,m;
int cnt=0,f[1000010][22],dep[1000010];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline int LCA(int x,int y){//LCA模板，有无用语句，不要直接抄~ 
	if(dep[x]<dep[y]) swap(x,y);
	int fx=x,fy=y;
	for(int i=21;i>=0;i--){
		if(dep[f[fx][i]]>=dep[fy]) fx=f[fx][i];
	}
	if(fx==fy) return fx;
	for(int i=21;i>=0;i--){
		if(f[fy][i]!=f[fx][i]) fx=f[fx][i],fy=f[fy][i];
	}
	return f[fx][0];
}
int main(){
	m=read();int n=4;
	dep[1]=1;dep[2]=2;dep[3]=2;dep[4]=2;//初始化dep数组 
	f[2][0]=1;f[3][0]=1;f[4][0]=1;//初始化倍增数组 
	int u=2,ans=2,v=3;//初始化两端点与直径 
	while(m--){
		int x=read();
		f[++n][0]=x;dep[n]=dep[x]+1;//链接一个新点 
		for(int i=1;i<=21;i++){
			f[n][i]=f[f[n][i-1]][i-1];//维护数组 
		}
		int l1=LCA(n,u),l2=LCA(n,v),xx=u,ll;
		int L1=dep[n]-dep[l1]+dep[u]-dep[l1];
		int L2=dep[n]-dep[l2]+dep[v]-dep[l2];//求出两点距离 
		(L1>L2)?xx=v,ll=L1:ll=L2;//从这里->
		if(ll>ans){
			((xx==v)?v:u)=n;//更新直径端点 
			ans=ll;//更新树的直径 
		}//->到这里,非常nt,建议自己写~ 
		printf("%d\n",ans);
		f[++n][0]=x;dep[n]=dep[x]+1;
		for(int i=1;i<=21;i++) f[n][i]=f[f[n][i-1]][i-1];//加入第二个点 
	}x
	return 0;
}
```


---

## 作者：Piwry (赞：1)

## 解析

### Part 1

考虑一个更一般的问题：

> 已知存在非负边权的树 $T$ 的某一直径 $p(u, v)$。现为 $T$ 添加一个叶节点 $x$ 及边 $(x, w)$（权非负），求新树 $T'$ 的任意一条直径

这里直接给出结论：$T'$ 的直径之一一定为 $p(x, u)$ 或 $p(x, v)$

### Part 2

接下来考虑证明

为了方便，这里设新的直径为 $p(x, u)$；并且也不考虑多条直径的情况（那样的话证明也类似，只是繁琐些）

考虑新直径和原直径的关系，只有两种情况：

#### 情况 I

![I](https://cdn.luogu.com.cn/upload/image_hosting/mmg4gcbr.png)

这种情况比较显然：

由直径 $p(u, v)$ 可得 $a+b>a+c \Rightarrow b>c$

（这里的 $a$、$b$ 等字母即指对应的路径的长度）

若直径产生更新，新直径的端点其中之一一定为 $x$；否则在更新前它就已经是直径了

假设新直径为 $p(x, y)$，可得 $c+d+(w, x)>b+d+(w, x) \Rightarrow c>b$

由此导出了矛盾。

#### 情况 II

![II](https://cdn.luogu.com.cn/upload/image_hosting/eh1n0pg9.png)

这种情况会稍微复杂些，但具体做法也类似：

由直径 $p(u, v)$ 可得 $a+b>a+e+c \Rightarrow b>e+c$

同样设新直径 $p(x, y)$，可得 $c+d+(w, x)>b+e+d+(w, x) \Rightarrow c>b+e$

即 $c-e>b>c+e$；

又因为边权非负，因此应当有 $c+e>c-e$

由此导出了矛盾。

### Part 3

有了这个结论后直接套用它，原题目就差不多做完了

需要写的实际上只有查询树上路径长，这直接离线下来预处理一下最终的树即可

## CODE

这里不想写 LCA 就直接拉了个 LCT 板子过来维护树上路径长qaq；代码仅供参考

```cpp
#include <cstdio>

const int MAXQ =5e5+20;

/*------------------------------IO------------------------------*/

namespace IO_base{
	const int MAXB =1<<10;
	char gbuf[MAXB], *ps =gbuf, *pt =gbuf;
	char pbuf[MAXB+1], *pp =pbuf;
	struct Flusher{
		~Flusher(){
			fwrite(pbuf, 1, pp-pbuf, stdout);
		}
	}flusher;
	
	inline char Getchar(){
		if(ps == pt){
			ps =gbuf;
			pt =gbuf+fread(gbuf, 1, MAXB, stdin);
		}
		return (ps == pt) ? EOF : *ps++;
	}
	inline void Putchar(const char &ch){
		if(pp == pbuf+MAXB){
			pp =pbuf;
			fwrite(pbuf, 1, MAXB, stdout);
		}
		*pp++ =ch;
	}
}
#define getchar IO_base::Getchar
#define putchar IO_base::Putchar

namespace IO_number{
	int read(){
		int x =0; char c =getchar(); bool f =0;
		while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
		while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
		return (f) ? -x : x;
	}
	
	void write(const int &x){
		if(x < 0){
			putchar('-');
			write(-x);
		}
		else{
			if(x/10)
				write(x/10);
			putchar('0'+x%10);
		}
	}
}
using namespace IO_number;

/*------------------------------Lct------------------------------*/

const int MAXN_LCT =MAXQ*2;
#define MAXN MAXN_LCT

namespace Lct{
	bool rev[MAXN];
	int sum[MAXN];
	
	namespace Splay{
		int ch[2][MAXN], fa[MAXN];
		
		inline void pushdown(const int &x){
			if(rev[x]){
				rev[ch[0][x]] ^=1, rev[ch[1][x]] ^=1;
				ch[0][x] ^=ch[1][x] ^=ch[0][x] ^=ch[1][x];
				rev[x] =0;
			}
		}
		
		inline void pushup(const int &x){
			sum[x] =sum[ch[0][x]]+sum[ch[1][x]]+1;
		}
		
		inline bool is_top(const int &x){ return (fa[x] == 0 || (ch[0][fa[x]] != x && ch[1][fa[x]] != x)); }
		
		inline bool get_type(const int &x){ return ch[1][fa[x]] == x; }
		
		inline void rotate(const int &x){
			bool typ_x =get_type(x);
			int y =fa[x], z =fa[y], a =ch[!typ_x][x];
			fa[x] =z; if(!is_top(y)) ch[get_type(y)][z] =x;
			fa[y] =x, ch[!typ_x][x] =y;
			fa[a] =y, ch[typ_x][y] =a;
			pushup(y);
		}
		
		void pushall(const int &x){
			if(!is_top(x))
				pushall(fa[x]);
			pushdown(x);
		}
		
		void splay(const int &x){
			pushall(x);
			for(; !is_top(x); rotate(x))
				if(!is_top(fa[x])){
					if(get_type(fa[x]) == get_type(x))
						rotate(fa[x]);
					else
						rotate(x);
				}
			pushup(x);
		}
		
		int find_min(const int &top){
			int x =top;
			while(ch[0][x]){
				x =ch[0][x];
				pushdown(x);
			}
			splay(x);
			return x;
		}
	}
	using namespace Splay;
	
	void access(const int &x){
		for(int pre =0, top =x; top; pre =top, top =fa[top]){
			splay(top);
			ch[1][top] =pre;
			pushup(top);
		}
	}
	
	inline void setroot(const int &x){
		access(x), splay(x);
		rev[x] =1;
	}
	
	inline int findroot(const int &x){
		access(x), splay(x);
		return find_min(x);
	}
	
	inline void link(const int &x, const int &y){
		setroot(x);
		fa[x] =y;
	}
	
	inline int query(const int &x, const int &y){
		setroot(x);
		access(y), splay(y);
		return sum[y];
	}
}

#undef MAXN

/*------------------------------Func------------------------------*/

int u, v; /* 当前树直径的两端 */
int tot, Ans;

inline void init(){
	using namespace Lct;
	for(int i =1; i <= 4; ++i)
		sum[i] =1;
	for(int i =2; i <= 4; ++i)
		link(1, i);
	u =2, v =3;
	tot =4, Ans =3;
}

inline void _add(const int &_u){
	using namespace Lct;
	sum[++tot] =1;
	link(_u, tot);
	const int _ans1 =query(u, tot), _ans2 =query(v, tot);
	if(_ans1 > _ans2 && _ans1 > Ans)
		v =tot, Ans =_ans1;
	else if(_ans2 > Ans)
		u =tot, Ans =_ans2;
}

inline void add(const int &_u){
	_add(_u), _add(_u);
}

/*------------------------------Main------------------------------*/

int main(){
	init();
	for(int i =0, q =read(); i < q; ++i){
		add(read());
		write(Ans-1), putchar('\n');
	}
}
```

---

## 作者：梨衣 (赞：1)

给定一棵树，通过不断加入新的节点，求树的直径。

题目要求每次向一个叶节点增加两个节点，但两个节点到叶节点的长度都是 $1$ ，对于树的直径是否变化的贡献是一样的，所以只需任选一个判断即可。

新加入的节点，如果能对直径产生影响，仅会更新当前直径的一个端点，那么，每次加入节点后，分别求出新节点到当前直径两端点的距离是否大于直径，更新最大值同时更新端点即可。由于初始树已给，除根节点外任选两节点成为直径端点，直径长度为 $2$ 。

利用 $LCA$ 求节点间长度，由于从根节点走到两个节点时会重复经过两节点最近公共祖先的深度，则两节点间长度为 **$a$ 节点深度与 $b$ 节点深度和减去两倍最近公共祖先深度**。
## 代码如下
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int head[1000100],tot;
int dep[1000100],f[20][1000100];
struct edge{
	int to,nxt;
}e[2000100];
void add(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
void dfs(int cur,int fa){
	dep[cur]=dep[fa]+1;
	f[0][cur]=fa;
	for(int i=1;i<=19;i++)
		f[i][cur]=f[i-1][f[i-1][cur]];
	for(int i=head[cur];i;i=e[i].nxt){
		if(e[i].to==fa)continue;
		dfs(e[i].to,cur);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y]){
		for(int i=0;i<=19;i++)
			if(dep[f[i][x]]<dep[y]){
				x=f[i-1][x];
				break;
			}
	}
	while(f[0][x]!=f[0][y]){
		for(int i=1;i<=19;i++)
			if(f[i][x]==f[i][y]){
				x=f[i-1][x];
				y=f[i-1][y];
				break;
			}
	}
	if(x==y)return x;
	else return f[0][x];	
}
int main(){
	int m,cnt=4,l=2,r=3,ans=2;
	scanf("%d",&m);
	add(1,2),add(1,3),add(1,4);
	dfs(1,1);
	for(int i=1;i<=m;i++){
		int z;
		scanf("%d",&z);
		dfs(++cnt,z),dfs(++cnt,z);
		int p1=lca(l,cnt),p2=lca(r,cnt);
		if(dep[l]+dep[cnt]-2*dep[p1]>ans){
			ans=dep[l]+dep[cnt]-2*dep[p1];
			r=cnt;
		}
		else if(dep[r]+dep[cnt]-2*dep[p2]>ans){
			ans=dep[r]+dep[cnt]-2*dep[p2];
			l=cnt;
		}
		printf("%d\n",ans);
	}
}
```
## 谢谢观看

---

## 作者：yewanxingkong (赞：1)

题意大概就是要 $m$ 次操作后询问树的直径。

如果要是每一次询问都求一次树的直径的话百分百会炸，所以正解肯定是从其他地方考虑。

首先树有着一个性质，那就是一个树中到这个点最远的的点一定是这个树的直径的一个端点。还有另一个性质就是增加树的一个端点导致树的直径的改变，只会改变原直径的一个端点。

于是我们就可以考虑记录下树的直径的两个端点，用两次 $lca$ 判断新加的点到两端点的距离，一旦大于原先记录的直径就更新直径以及新的端点。

有些人考虑到树的直径有多条，但是多条树的直径的条件很严苛，所有直径必须交于一点且这一点为这些直径的中点。所以多条树的直径不会形成一些奇怪的形状，也不会影响我们的答案，我们只要维护一条就够了。

下面是程序
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int m,f[1000010][20],x,y,dep[1000010],n=4,da,db,chu=2;
int sou(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;--i)
    	if(dep[x]- (1<<i) >= dep[y]) 
    		x=f[x][i];
	if(x==y) return x;
	for(int i=19;i>=0;--i){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
inline int read(){
	register int date=0,w=1;register char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int main(){
	m=read();
	f[2][0]=f[3][0]=f[4][0]=1;
	dep[1]=1;
	dep[2]=dep[3]=dep[4]=2;
	da=2,db=3;
	for(int i=1;i<=m;++i){
		int ru=read();
		f[++n][0]=ru;
		dep[n]=dep[ru]+1;
		f[++n][0]=ru;
		dep[n]=dep[ru]+1;
		for(int j=1;j<=19;++j)
			f[n][j]=f[f[n][j-1]][j-1],f[n-1][j]=f[f[n-1][j-1]][j-1];
		int sa=sou(da,n),sb=sou(db,n);
		if(dep[da]+dep[n]-2*dep[sa]>chu){
			chu=dep[da]+dep[n]-2*dep[sa];
			db=n;
		}
		else if(dep[db]+dep[n]-2*dep[sb]>chu){
			chu=dep[db]+dep[n]-2*dep[sb];
			da=n;
		}
		printf("%d\n",chu);
	}
	return 0;
}
```


---

## 作者：极寒神冰 (赞：1)

将 $dis(u,v)$表示点$u$到点$v$的距离,可以看成$u->lca$的距离和$v->lca$距离之和

可以发现，如果要加一个点$x$，那么只会有两种情况

1.直径$dis(s,t)$不变

2.直径变为$dis(x,t)$或者$dis(s,x)$

那么我们只需要维护两个端点$s,t$即可

```
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int dep[N],dp[N][23];
int maxx,n,s,t;
inline void init_lca()
{
	n=4;s=2;t=4;
	dep[2]=dep[3]=dep[4]=1;
	dp[2][0]=dp[3][0]=dp[4][0]=1;
	for(int j=1;j<=22;j++)
	{
		for(int i=1;i<=4;i++)
		{
			dp[i][j]=dp[dp[i][j-1]][j-1];
		}
	}
}
inline int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	int del=dep[x]-dep[y];
	for(int i=0;i<=22;i++) if(del&(1<<i)) x=dp[x][i];
	if(x==y) return x;
	for(int i=22;i>=0;i--)
	{
		if(dp[x][i]!=dp[y][i])
		{
			x=dp[x][i];
			y=dp[y][i];
		}
	}
	return dp[x][0];
}
inline int dis(int x,int y)
{
	return dep[x]+dep[y]-(dep[lca(x,y)]*2);
}
inline void add(int fa,int u)
{
	dep[u]=dep[fa]+1;
	dp[u][0]=fa;
	for(int i=1;i<=22;i++) dp[u][i]=dp[dp[u][i-1]][i-1];
	int diss=dis(s,u),dist=dis(t,u);
	if(diss>maxx&&diss>dist){maxx=diss;t=u;}
	if(dist>maxx&&diss<=dist){maxx=dist;s=u;}
}
int _;
signed main()
{
	init_lca();
	for(_=read();_;_--)
	{
		int u=read();
		n++;add(u,n);n++;add(u,n);
		cout<<maxx<<endl;
	}
}
```


---

## 作者：zhengrunzhe (赞：1)

显然大力$LCT$啊

有个性质就是比如原来直径两端记作$a,b$

新进来个叶子$c$

比较$dis(a,b),dis(a,c),dis(b,c)$

选个最大的就是新直径，同时更新$a,b$

然后动态树上路径长度显然直接lct啊

然后这题就做完了

有个坑点就是总点数是$2q+4$

~~一开始我只开了5e5+10的空间然后爆了~~
```cpp
#include<cstdio>
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)out=-out,putchar('-');
	write(out);
	putchar('\n');
}
template<class type>inline const void swap(type &a,type &b)
{
	type c=a;a=b;b=c;
}
const int N=1e6+10;
class Link_Cut_Tree
{
	private:
		struct tree
		{
			bool rev;
			int size,son[2],fa;
			inline const void reverse()
			{
				rev^=1;
				swap(son[0],son[1]);
			}
		}t[N];
		inline const bool identity(int p)
		{
			return t[t[p].fa].son[1]==p;
		}
		inline const bool nroot(int p)
		{
			return t[t[p].fa].son[0]==p||identity(p);
		}
		inline const void pushup(int p)
		{
			t[p].size=t[t[p].son[0]].size+1+t[t[p].son[1]].size;
		}
		inline const void pushdown(int p)
		{
			if (t[p].rev)
				t[t[p].son[0]].reverse(),
				t[t[p].son[1]].reverse(),
				t[p].rev=0;
		}
		inline const void rotate(int p)
		{
			bool f=identity(p);
			int fa=t[p].fa,gfa=t[fa].fa,q=t[p].son[f^1];
			if (nroot(fa))t[gfa].son[identity(fa)]=p;
			t[t[p].son[f^1]=fa].son[f]=q;
			t[t[t[q].fa=fa].fa=p].fa=gfa;
			pushup(fa);
		}
		inline const void relieve(int p)
		{
			if (nroot(p))relieve(t[p].fa);
			pushdown(p);
		}
		inline const void splay(int p)
		{
			relieve(p);
			for (int fa;nroot(p);rotate(p))
				if (nroot(fa=t[p].fa))
					rotate(identity(p)^identity(fa)?p:fa);
			pushup(p);
		}
		inline const void access(int x)
		{
			for (int y=0;x;x=t[y=x].fa)
				splay(x),t[x].son[1]=y,pushup(x);
		}
		inline const void makeroot(int x)
		{
			access(x);splay(x);t[x].reverse();
		}
		inline const void split(int x,int y)
		{
			makeroot(x);access(y);splay(y);
		}
	public:
		inline const void link(int x,int y)
		{
			makeroot(x);t[x].fa=y;
		}
		inline const int distance(int x,int y)
		{
			split(x,y);return t[y].size-1;
		}
}lct;
int m,da,db,d,n=4;
int main()
{
	read(m);
	d=da=2;db=3;
	lct.link(1,2);
	lct.link(1,3);
	lct.link(1,4);
	while (m--)
	{
		int x;
		read(x);
		lct.link(x,++n);
		int d1=lct.distance(n,da),d2=lct.distance(n,db);
		if (d1<=d&&d2<=d);
		else if (d1>d2)db=n,d=d1;
			 else da=n,d=d2;
		lct.link(x,++n);
		d1=lct.distance(n,da);d2=lct.distance(n,db);
		if (d1<=d&&d2<=d);
		else if (d1>d2)d=d1,db=n;
			 else da=n,d=d2;
		writeln(d);
	}
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：1)

~~我实在不太明白这题为什么是个黑题，我看顶多紫题吧。。~~

每一次修改过后，直径**的长度**有可能会变，当然也有可能不会变

分类讨论

长度不变，那啥也不用动

如果变了，那么是什么影响到了直径长度的变化？

对，就是那两个点（或者其中一个）！

如果这两个点（或者其中一个）没有被添加到新的直径上，那直径长度肯定不会变

然后你会发现，因为添加的是叶子，所以如果直径长度变了，那么两个点（或者其中一个）一定是直径的端点（或之一）

那么一开始的直径就是 2 - 4 （当然您喜欢 2 - 3 , 3 - 4 也行）

我们每次记录直径的两个端点 $U-V$，记新加的两个点为 $n_1,n_2$，记 $dis_{u,v}$ 为 $u,v$ 之间的距离

那么每次的新直径就是 $dis_{U,V}$   , $dis_{U,n_1}$ , $dis_{U,n_2}$ , $dis_{n_1,V}$ , $dis_{n_2,V}$ , $dis_{n_1,n_2}$，这6个中最大的那个

$dis_{u,v}$ 可以直接倍增lca求，然后新加入2个点因为是叶子，直接可以添加到倍增数组里

所以复杂度 $O(q\log q)$，~~大概~~

```cpp
// This code writed by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int MaxN=1000050;
int up[MaxN][21];
struct Node
{
	int len,s,t;
	inline bool operator < (const Node &nt) const
	{
		return len>nt.len;
	}
};
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
int n=1;
int dep[MaxN];
int S,T,Len;
inline void InitLca(int u)
{
	for(int k=1;k<21;++k)
		up[u][k]=up[up[u][k-1]][k-1];
	return;
}
inline void addnode(int fa)
{
	++n;
	dep[n]=dep[fa]+1;
	up[n][0]=fa;
	InitLca(n);
	return;
}
inline void Init()
{
	dep[1]=1;
	InitLca(1);
	addnode(1);
	addnode(1);
	addnode(1);
	S=2;T=3;Len=2;
	return;
}
inline int lca(int u,int v)
{
	if(dep[u]<dep[v])
		swap(u,v);
	if(u!=v)
		for(int k=20;k>=0;--k)
			if(dep[up[u][k]]>=dep[v])
				u=up[u][k];
	if(u==v)
		return u;
	for(int k=20;k>=0;--k)
		if(up[u][k]!=up[v][k])
			u=up[u][k],v=up[v][k];
	return up[u][0];
}
inline int getdis(int u,int v)
{
	return dep[u]+dep[v]-2*dep[lca(u,v)];
}
signed main(void)
{
	Init();
	reg int q,pos;
	cin>>q;
	while(q--)
	{
		read(pos);
		addnode(pos);
		addnode(pos);
		vector<Node> dr;
		dr.push_back((Node){getdis(S,n-1),S,n-1});
		dr.push_back((Node){getdis(T,n-1),n-1,T});
		dr.push_back((Node){getdis(S,n),S,n});
		dr.push_back((Node){getdis(T,n),n,T});
		dr.push_back((Node){getdis(S,T),S,T});
		sort(dr.begin(),dr.end());
		S=dr.begin()->s;
		T=dr.begin()->t;
		Len=dr.begin()->len;
		printf("%d\n",Len);
	}
	return 0;
}
```



---

## 作者：PtrZ (赞：0)

## New Year Tree
[题目传送门](https://www.luogu.com.cn/problem/CF379F)

题外话：~~本题是本蒟蒻的首A黑题。~~

思路：因为每次询问时会增加两个点所以每次的直径只能产生在这两个点和之前的点中，而我们的树上 ST 表就可以查询 LCA（不懂[戳这](https://www.luogu.com.cn/blog/shjdgufd/post-mu-ban-zui-jin-gong-gong-zu-xian-lca)）那么两个点到 LCA 的距离就是直径，那么ST表的值就可以从父节点上面继承过来，这样时间复杂度就 $O(n \log n)$ 。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1000001][21],d[1000001];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int LCA(int u,int v){
	if(d[u]>d[v]) swap(u,v);
	int h=d[v]-d[u];
	for(int i=20;i>=0;i--){
		if(h&(1<<i)) v=f[v][i];
	}
	if(u==v) return u;
	for(int i=20;i>=0;i--){
		if(f[u][i]!=f[v][i]) {
			u=f[u][i];
			v=f[v][i];
		}
	}
	return f[u][0];
}
signed main()
{
	int n=4,len,a,b;
	f[2][0]=f[3][0]=f[4][0]=1;
	d[1]=0; d[2]=d[3]=d[4]=1;
	len=a=2; b=3;
	int q=read();
	for(int i=1;i<=q;i++){
		int u=n+1;
		int v=n+2;
		n+=2;
		int x=read();
		d[u]=d[v]=d[x]+1;
		f[u][0]=f[v][0]=x;
		for(int j=1;(1<<j)<=n;j++){
			f[u][j]=f[f[u][j-1]][j-1];
			f[v][j]=f[f[v][j-1]][j-1];
		} 
		int lca=LCA(a,u);
		if(d[u]+d[a]-d[lca]-d[lca]>len){
			b=u; len++;
		}
		else{
			int lca=LCA(b,u);
			if(d[u]+d[b]-d[lca]-d[lca]>len){
				a=u; len++;
			}
		}
		printf("%d\n",len);
	}
	return 0;
}
```


---

