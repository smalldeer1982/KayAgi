# Andryusha and Colored Balloons

## 题目描述

题意:

有一颗n个节点的树,进行有限制染色,问染色的最少颜色数,以及每个点的颜色(从1标号,标号不能超过颜色数).
限制:相邻三个点的颜色不能相同.

## 说明/提示

n:[3,2e5]

## 样例 #1

### 输入

```
3
2 3
1 3
```

### 输出

```
3
1 3 2 ```

## 样例 #2

### 输入

```
5
2 3
5 3
4 3
1 3
```

### 输出

```
5
1 3 2 5 4 ```

## 样例 #3

### 输入

```
5
2 1
3 2
4 3
5 4
```

### 输出

```
3
1 2 3 1 2 ```

# 题解

## 作者：zhaoyp (赞：7)

## Solution
首先明确一下树上的距离，对于任一结点：
1. 它到它父亲的距离为 $1$。
1. 它到它任意儿子的距离为 $1$。
1. 它到它父亲的父亲的距离为 $2$。
1. 它到它的兄弟距离为 $2$。

考虑以 $1$ 为根节点进行搜索，当对某一节点染色后，不妨对它的所有儿子进行染色，由于它的父亲一定已经被染色，它的儿子以下的节点都没有被染色，所以只需让它的儿子与它和它父亲的颜色不同即可。当然为了防止它已染色的兄弟的干扰，在染一个节点时将颜色值设为上一个被染色兄弟的颜色值加 $1$（如果没有则为 $1$），再判断是否符合条件即可。总颜色数为所有节点颜色的最大值。
## code
下面给出DFS实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,ans,col[200005],fa[200005];
vector <int> G[200005];
void input()
{
	scanf("%d",&n);
	for(int i = 1;i < n;i++)
		scanf("%d%d",&x,&y),G[x].push_back(y),G[y].push_back(x);
}
void dfs(int k)
{
	int x = 1;//初始颜色值 
	for(int i = 0;i < G[k].size();i++)//对它的所有儿子进行染色
	{
		if(G[k][i] == fa[k])
			continue;
		while(x == col[k]||x == col[fa[k]])//与它和它父亲的颜色相同，则将颜色值++ 
			x++;
		col[G[k][i]] = x,x++;
		fa[G[k][i]] = k;//记录父节点 	
	}
	ans = max(ans,x - 1);
	for(int i = 0;i < G[k].size();i++)
		if(G[k][i] != fa[k])
			dfs(G[k][i]);
}
void output()
{
	printf("%d\n",ans);
	for(int i = 1;i <= n;i++)
		printf("%d ",col[i]);
}
int main()
{
	input();
	col[1] = 1;
	dfs(1);
	output();
	return 0;
}
```

---

## 作者：Shikita (赞：6)

# 这是一道DFS/BFS的题目
就是先建图，然后再根据其他节点来判断的题目，具体代码里说

## 下面直接放上代码
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
const int N=200005;
int n,tot,ans;
int d[N],head[N],Next[N*2],ver[N*2],c[N];
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9'){if(c=='-')flag=1;   c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return flag?-x:x;
}
void add(int x,int y)
{
   ++tot;Next[tot]=head[x]; head[x]=tot; ver[tot]=y;
}//链式前向星建图
void dfs(int x,int fa)//x表示当前节点，fa表示父亲节点
{
	int now=0;
	for(int i=head[x];i;i=Next[i])
	{
		if(ver[i]!=fa)//把所以相邻的边涂色
		{
			++now;
			while(now==c[fa]||now==c[x]) ++now;
			c[ver[i]]=now;
		}
	}
	for(int i=head[x];i;i=Next[i])
	if(ver[i]!=fa) dfs(ver[i],x);//一种分层的思想？？？
}
int main()
{
	n=read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read();
		add(x,y),add(y,x);
		++d[x],++d[y];
		ans=max(ans,d[x]),ans=max(ans,d[y]);//因为连接边数最大的边的儿子也必定最多，而一个节点的儿子互不相同，所以每个儿子都要一种颜色，最后加上自己颜色
	}
	cout<<ans+1<<endl;
	c[1]=1;
	dfs(1,0);
	for (int i=1;i<=n;++i) printf("%d%c",c[i]," \n"[i==n]);//最后那个是来自老师的特判写法
}
```
借鉴于YWHS官方刷题网站，思想来自于HJF老师

---

## 作者：陆巷北NorthAlley (赞：4)

~~众所周知CF的题目一般都会被恶意评分~~

### 题意

染色，每相邻三点颜色不同

问：无了吗？

答：无了

### 思路

一看，暴力

不信，再看，暴力

还不信，还看，还是暴力

对，就是暴力

### 核心算法

$dfs$的时候判断，然后顺次输出就可以了

```cpp
//在搜当前节点的时候，记录父亲节点的颜色和自己的颜色
//然后一个个搜儿子的颜色并记录往下搜就可以了
void dfs(int now,int fa){
	int i;
	int son = fir[now];		//前向星
	if(to[son] == fa) son = nxt[son];
	for(i = 1;son;i++){  //自认为巧妙的循坏，我赶脚还不错
		if(i == tmp[now] || i == tmp[fa]) continue;
		tmp[to[son]] = i;
		dfs(to[son],now);
		son = nxt[son];
		Ans = max(Ans,i); 	//Ans记录最多的颜色
		if(to[son] == fa) son = nxt[son];
	}
}
```

好像，就这么讲完了？

时间复杂度$O(N)$√

希望这篇题解能对您有帮助，如果这亚子的话，就不要吝啬您免费的赞了呦

我的$Blog$传送门[Lu_Mingの宅](https://www.luogu.org/blog/Lu-Ming/)

### CF62ms算法

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAX = 200020;
int n,fir[MAX],to[MAX << 1],nxt[MAX << 1],num,tmp[MAX],Ans;

void read(int &x);
void add(int u,int v);
void init();
void dfs(int now,int fa);

int main(void){
	init();
	tmp[1] = 1;
	dfs(1,0);
	printf("%d\n",Ans);
	for(int i = 1;i <= n;i++){
		printf("%d ",tmp[i]);
	}
	printf("\n");
	return 0;
}

void read(int &x){
	x = 0;
	bool flag = false;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') flag = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + ch - '0';
		ch = getchar();
	}
	if(flag) x = -x;
}
void add(int u,int v){
	nxt[++num] = fir[u];
	to[num] = v;
	fir[u] = num;
}
void init(){
	read(n);
	int x,y;
	for(int i = 1;i < n;i++){
		read(x);
		read(y);
		add(x,y);
		add(y,x);
	}
}
void dfs(int now,int fa){
	int i;
	int son = fir[now];
	if(to[son] == fa) son = nxt[son];
	for(i = 1;son;i++){
		if(i == tmp[now] || i == tmp[fa]) continue;
		tmp[to[son]] = i;
		dfs(to[son],now);
		son = nxt[son];
		Ans = max(Ans,i);
		if(to[son] == fa) son = nxt[son];
	}
}
```


---

## 作者：Dzhao (赞：3)

# 题解 CF780C
题意已经很明确了，我就不再说了。

我们根据题意直接入手本题：

## $\texttt{Part one}$
因为三个相邻的点的颜色互不相同，所以以一个点为中心向外扩散的菊花图里的点的颜色一定是互不相同的，于是我们就可以去找这棵树中菊花图的最大大小，来解决最少要染几种颜色。

## $\texttt{Part two}$
因为一个菊花图中心染什么颜色，对这个菊花图外的点是没有影响的（前提是最大菊花图），所以我们就可以从根节点往下递推，然后染色。染色过程中，我们只要判断这个点和他的父亲和爷爷的颜色一不一样就行了。具体详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void rd(T &x)
{
	x=0;bool f=0;char c=getchar();
	while(!isdigit(c)) {if(c=='-') f=1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;
}
const int N=2e5+5; 
int n,ver[N<<1],nxt[N<<1],h[N],tot,ans,col[N<<1];
inline void add(int x,int y) {ver[++tot]=y,nxt[tot]=h[x],h[x]=tot;}
void dfs(int u,int fa)
{
	int cnt=0;
	for(int i=h[u];i;i=nxt[i])
		if(ver[i]!=fa) 
		{
			cnt++; //叶子结点个数 
			while(cnt==col[u] || cnt==col[fa]) cnt++; //和父亲或爷爷一样的颜色就跳过 
			col[ver[i]]=cnt; //给当前节点染上色 
		}
	ans=max(ans,cnt);
	for(int i=h[u];i;i=nxt[i])
		if(ver[i]!=fa) dfs(ver[i],u); //向下染色 
}

int main()
{
	rd(n);
	for(int i=1;i<n;i++)
	{
		int x,y;rd(x),rd(y);
		add(x,y),add(y,x);
	}
	col[1]=1;dfs(1,0);
	printf("%d\n",ans);
	for(int i=1;i<=n;i++) printf("%d ",col[i]);
	return 0;
}
```
### $\color{skyblue}\texttt{Thanks for wathcing}$

---

## 作者：lukelin (赞：2)

### 前言
更好的阅读体验？**[我的博客](https://www.cnblogs.com/linzhengmin/p/11298270.html)**
### 题意简述
给相邻的三个节点颜色不能相同的树染色所需的最小颜色数。
### 题解
这道题目很显然可以用深搜。  
考虑题目的限制，如果当前搜索到的点为u，  
显然u的父亲节点，u本身和u的所有儿子不能同色(因为兄弟之间相差为2)。  
由于DFS解题，所以搜索到u时，u本身和u的父亲肯定已经有颜色了，那么现在要结局的使u的所有儿子的颜色，那么根据贪心的思想对于每个u的儿子，颜色能往小取就往小取，在选取颜色的时候应当注意，选取的颜色不能与u和u的父亲节点的颜色相同。  
最后的答案就是DFS中使用过的最大的颜色。
### 代码
~~去掉fread快读其实很短~~  
```cpp
#include <cstdio>
#include <algorithm>

using namespace std; 

namespace fast_IO{
    const int IN_LEN = 10000000, OUT_LEN = 10000000;
    char ibuf[IN_LEN], obuf[OUT_LEN], *ih = ibuf + IN_LEN, *oh = obuf, *lastin = ibuf + IN_LEN, *lastout = obuf + OUT_LEN - 1;
    inline char getchar_(){return (ih == lastin) && (lastin = (ih = ibuf) + fread(ibuf, 1, IN_LEN, stdin), ih == lastin) ? EOF : *ih++;}
    inline void putchar_(const char x){if(oh == lastout) fwrite(obuf, 1, oh - obuf, stdout), oh = obuf; *oh ++= x;}
    inline void flush(){fwrite(obuf, 1, oh - obuf, stdout);}
    int read(){
        int x = 0; int zf = 1; char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar_();
        if (ch == '-') zf = -1, ch = getchar_();
        while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar_(); return x * zf;
    }
    void write(int x){
        if (x < 0) putchar_('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar_(x % 10 + '0');
    }
}

using namespace fast_IO;

struct Edge{
    int to, next;
} edges[400005];

int head[200005], edge_num = 0;

inline void addEdge(int u, int v){
    edges[++edge_num] = (Edge){v, head[u]};
    head[u] = edge_num;
}

int clr[200005];
int ans = 0;

void DFS(int u, int fa){
	int v, cnt = 1;
	for (int c_e = head[u]; c_e; c_e = edges[c_e].next){
		v = edges[c_e].to;
		if (v != fa){
			while (cnt == clr[u] || cnt == clr[fa])
				++cnt;
			clr[v] = cnt++;
			DFS(v, u);
		}
	}
	ans = max(ans, cnt - 1);
}

int main(){
	int n = read();
	for (int i = 1; i < n; ++i){
		int u = read(), v = read();
		addEdge(u, v), addEdge(v, u);
	}
	clr[1] = 1; DFS(1, 1);
	write(ans); putchar_('\n');
	for (int i = 1; i <= n; ++i)
		write(clr[i]), putchar_(' ');
	flush(); return 0;
} 
```

---

## 作者：过往梦魇之殇 (赞：2)

### 来弹一发题解啦 ~~（好久没写，没感觉了$qwq$）~~

题意装换：给你几个连通的节点，现在想让你染色，且每个节点的颜色与和这个节点的父节点和爷爷节点的颜色不同，想让你计算最少需要用到几个颜色。

因为是连通的问题，所以用到$vector$容器，用$push$_$back()$压入，然后因为对节点的颜色有要求，所以用$bfs$，从节点$1$开始，染色每次都从颜色$1$开始搜索并且判断其父节点和爷爷节点的颜色是否相同，若相同则颜色$+1$继续判断，直到不相同为止，由此可以得到最少需要用到几个颜色，并且记录每个颜色对应的节点。

输出时记得要边输出边清空$vector$哦$awa$

接下来放代码：~~（思路挺好理解的，不明白的康康代码就大概懂了）~~

```cpp
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cmath>
#include<ctime>
#include<iomanip>
#include<complex>
#include<climits>
#define re register
#define in inline
#define pi acos(-1.0)
#define inf 2147483640
#define cd complex<double>
using namespace std;
in int read()
{
    int sum=0,negative=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')negative=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum*negative;
}
in void write(int X)
{
    if(X<0)putchar('-'),X=-X;
    if(X>=10)write(X/10);
    putchar(X%10+'0');
}
const int maxn=2e5+10;
vector<int>mapp[maxn];
int n,c[maxn],c1[maxn],ans,m,now,noww;
void solve(){
	memset(c,0,sizeof(c));
	ans=1;
	queue<int>q;
	q.push(ans);
	c[1]=c1[1]=1;
	while(!q.empty()){
		m=1;
		now=q.front();
		q.pop();
		for(re int i=0;i<mapp[now].size();i++){
			noww=mapp[now][i];
			if(!c[noww]){
				c1[noww]=c[now];
				while(c[now]==m||c1[now]==m){
					++m;
				}
				c[noww]=m++;
				q.push(noww);
			}
		}
		ans=max(ans,m-1);
	}
}
int main()
{
	scanf("%d",&n);
	for(re int i=0;i<n-1;i++){
		int u,v;
		u=read();
		v=read();
		mapp[u].push_back(v);
		mapp[v].push_back(u);
	}
	solve();
	write(ans);
	printf("\n");
	for(re int i=1;i<n;i++){
		mapp[i].clear();
		write(c[i]);
		printf(" ");
	}
	write(c[n]);
	puts("");
    return 0;
}
```

>Thanks For Watching!

---

## 作者：Bai_R_X (赞：1)

## 思路
以任何节点开始搜索并不会改变需要的颜色，于是我们以 $1$ 为根节点。

对于每个节点，其颜色必须与父节点和祖父节点不同，并且与兄弟节点也要不同。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,i,k,head[200005],tot,color[200005]={0,1};
struct Edge
{
	int v,nxt;
}e[400005];
void add(int u,int v)
{
	e[++tot].v=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
void dfs(int u,int fa)
{
	int Color=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		while(Color==color[u]||Color==color[fa])Color++;
		color[v]=Color++;
		dfs(v,u);
	}
}
signed main()
{
    cin>>n;
    for(i=1;i<n;i++)
    {
    	cin>>x>>y;
    	add(x,y);
    	add(y,x);
	}
	dfs(1,0);
	for(i=1;i<=n;i++)k=max(k,color[i]);
	cout<<k<<endl;
	for(i=1;i<=n;i++)cout<<color[i]<<" ";
    return 0;
}
```

---

## 作者：fuwei123 (赞：0)

首先，不要被本题标签吓到，这只是一道普通的 dfs 罢了。

### 求方案
我们发现，任意节点 $i$ 的颜色，只要和它的父亲，它父亲的父亲颜色不一样，并且和它的兄弟节点颜色不一样，就是合法的。显然，$i$ 的颜色**越小越好**。那么，我们就不断枚举一个颜色值 $now$，直到它合法为止。

当然，每次我们遍历 $i$ 的子节点时，都要令 $now+1$，因为这样才能保证子节点间**颜色不一样**。

### 求最小的颜色数
我们只要记录一个 $cnt$ 表示答案，每次染色时都用 $now$ 更新 $cnt$ 即可，因为我们是从小到大枚举 $now$，所以当前的 $now$ 就是可以涂的最小颜色，也就是目前最少的颜色数。

下面是 AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[200005], n, cnt = 1;
vector<int>t[200005];
bool vis[200005];//记录每一个点有没有被枚举到

void dfs(int pos, int pre){ 
	int now = 1;
	vis[pos] = 1;
	for(int i = 0;i < t[pos].size();i++){
		if(vis[t[pos][i]] == 1)continue;
		while(now == a[pre] || now == a[pos])
			now++;
		a[t[pos][i]] = now;
		cnt = max(cnt, now);
		dfs(t[pos][i], pos);
		now++;
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1;i < n;i++){
		int u, v;
		cin >> u >> v;
//		cout << u << " " << v << "\n";
		t[u].push_back(v);
		t[v].push_back(u);
	}
	a[1] = 1;
	dfs(1, 0);
	cout << cnt << "\n";
	for(int i = 1;i <= n;i++)cout << a[i] << " ";
	return 0;
}
```


---

## 作者：Enzyme125 (赞：0)

拿到这题，一脸图染色....
然后想起曾经一道题$O(3^n)$ 状压

然后看一下数据 $ n \leq 2 \cdot 10^5 $

~~不可做不可做~~

我在草稿本上画了一棵树，观察发现：

1. 菊花图答案必定为 n
2. 可以递归处理 , 子树和子树之间不相互影响，只需要根的颜色不同就行了


所以就得到这题的解了，对树进行dfs ， 对于每一个节点，保存其父亲的颜色，和自己的颜色。 然后把颜色分配给儿子节点，然后递归处理

~~好简单啊~~

思路自然，写法自然，不是很毒瘤


AC代码：

```C++
#include<cstdio>
#include<cctype>
#include<algorithm>
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

inline char nc(){ static char buf[100000] , *p1,*p2; return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,100000,stdin),p1 == p2) ? EOF : *p1++;}
template<class T>inline void rd(T & x) { x = 0;char ch = nc(); for(;!isdigit(ch);ch = nc()); for(;isdigit(ch);ch = nc()) x = x * 10 + ch - 48;}

const int inf = 0x3f3f3f3f;
const int maxn = 3e5 + 7;


struct edge{
	int v,next;
	edge(int v = 0,int next = 0) : v(v) , next(next) {} 
} e[maxn * 2];
int hd[maxn] , ek = 1;
inline void adde(int u,int v){
	e[ek] = edge(v,hd[u]);
	hd[u] = ek++;
}
int ans  = 0;
int col[maxn];
void dfs(int u,int fa,int curc,int fac){
	col[u] = curc;
	int alc = 0; 
	for(int i = hd[u];i;i = e[i].next){
		
		int v = e[i].v;
		if(v == fa) continue;
		++alc;
		while(alc == curc || alc == fac) {
			++alc;
		}
		if(alc > ans) ans = alc;
		dfs(v,u,alc,curc);
	}
}

int main(){
	int n;
	rd(n);
	for(int i = 1;i < n;i++){
		int u,v; rd(u); rd(v);
		adde(u,v);
		adde(v,u);
	}
	dfs(1,-1,1,inf);
	printf("%d\n",ans);
	for(int i = 1;i <= n;i++){
		printf("%d ",col[i]);
	}
} 
```

这份代码全CF最快(62ms)，可能是因为玄学读优的原因吧，~~不加读优跑400ms~~

---

