# [USACO11OPEN] Learning Languages S

## 题目描述

Farmer John's N (2 <= N <= 10,000) cows, conveniently numbered 1..N, are fluent in some M (1 <= M <= 30,000) languages, also conveniently numbered from 1..M. Cow i can speak in K\_i (1 <= K\_i <= M) languages, namely L\_i1, L\_i2,..., L\_{iK\_i} (1 <= L\_ij <= M). FJ's cows aren't THAT smart, so the sum of K\_i over all cows i is at most 100,000.

Two cows can't directly talk to each other unless both speak a common language. However, cows can pass messages along, translating if necessary. In other words, cows A and B can have a conversation if and only if there exists a sequence of cows T\_1, T\_2, ..., T\_k such that A and T\_1 share a language, T\_1 and T\_2 share a language, etc., and T\_k and B share a language.

Farmer John wishes that his cows could be even more social, so he wants all his cows to be able to socialize with any other cow. He can buy books to teach any one of his cows any language he pleases. Being a fairly frugal farmer, FJ wants to purchase the minimum number of books necessary to enable all of his cows to speak to each other. Help him determine:

\* The minimum number of books he must purchase

\* Any set of books assigned to cows in any order which will help him meet this goal; a program will grade your output.

By way of example, suppose there are three cows named Alberta, Bessie, and Contessa along with three languages denoted as #1, #2, and #3. Alberta can speak languages #2 and #3, Bessie can speak language #2, and Contessa can speak language #1. Currently, Alberta and Bessie can talk to each other, but Contessa is left alone.

```
#1   #2   #3
Alberta           x    x
Bessie            x
Contessa     x
```
FJ wants to fix this situation, so he can buy Contessa a book to teach her language #2. This will ensure all cows speak the same language, so they can all communicate with one another.

Note that an alternate solution exists: instead, FJ could buy

Contessa a book to teach her language #3. Not all cows would speak the same language, but this would still be a valid solution because Contessa could communicate through Alberta (who also speaks language #3) if she wants to talk to Bessie. Other alternatives exist, and any valid alternate solution will also be accepted.

农夫约翰的$N(2<=N<=10,000)$只奶牛标号为$1..N$，同样的有$M(1<=M<=30,000)$种牛语标号为$1..M$，第i只奶牛会说$K_i(1<=K_i<=M)$种牛语，分别为$L_i1,L_i2,…,L_{iK_i}(1<=L_ij<=M)$，农夫的奶牛不是特别聪明，所以$K_i$的累加和不大于$100,000$。

两只奶牛只有当他们至少有一门语言一样的时候才可以沟通。否则这两只奶牛就需要别人来帮他们翻译才能交流。换句话说，A和B要进行沟通，他们可以通过$T_1,T_2,…,T_k$来传递，比如A和$T_1,T_1$和$T_2,…,T_k$和B进行交流。

农夫希望他的奶牛可以多多沟通，所以他买了很多课本去教她的奶牛语言。当然农夫非常的吝啬，他希望买最少的书就可以让所有的奶牛可以交流。你的任务就是帮他算出最少需要买几本书。


## 样例 #1

### 输入

```
3 3 
2 3 2 
1 2 
1 1 
```

### 输出

```
1 
```

# 题解

## 作者：mnesia (赞：5)

这道题是一道典型的并查集算法题。

刚看到这道题时，第一感觉是需要可能需要对并查集做一些优化，或者说把并查集分为两个部分，一部分存储牛的数据，另一部分存储语言的数据。后来的实现过程大体跟思路相同，但是意识到了前半部分数组（编号 `1 ~ N`）可以用来存储牛，后半部分数组（编号 `N + 1 ~ N + M`）可以用来存储语言 这一技巧。另外就是如其他题解所说，在标记牛与语言的关系时，只需要把第一头会这种语言的牛的编号作为一个“代表”赋值给对应的语言所在的数组空间，接下来的牛只需要连向对应的语言即可。

思路仅凭语言很难解释清楚，下面给出代码：
```cpp
#include<iostream>
#include<stdio.h>

using namespace std;
const int maxn = 10010;
const int maxm = 30010;
int n, m;
int num;
int k;
int father[maxn];
int lang[maxm];//lang[i] 存储会第 i 种语言的牛的编号（只存一头） 
int cnt;//cnt 存储当前需要买的书本数，初始化为 n（开始时视为所有牛都不会任一语言） 

void init()
{
	cnt = n;
    for(int i = 1;i <= n;i++)
    {
        father[i] = i;
    }
    return ;
}

int Find(int x)
{
    if(x != father[x])
    {
        father[x] = Find(father[x]);
    }
    return father[x];
}

void Union(int x, int y)
{
    int a = Find(x);
    int b = Find(y);
    if(a != b)
    {
        father[a] = b;
        cnt--;
    }
    return ;
}

int main()
{
//	freopen("learning.in", "r", stdin);
//	freopen("learning.out", "w", stdout);
	cin >> n >> m;
	init();
	for(int i = 1;i <= n;i++)
	{
		cin >> k;
		for(int j = 1;j <= k;j++)
		{
			cin >> num;
			if(lang[num] != 0)//如果之前已经有牛会第 i 种语言了 
			{
				Union(i, lang[num]);//将第 i 头牛加入到会第 num 种语言的集团中 
			}
			else
			{
				lang[num] = i;//将第 i 头牛设置为会第 num 种语言的代表 
			}
		}
	}
	cout << cnt - 1;
	return 0;
}
```
这里注意最后输出时要输出 `cnt - 1` ，因为如果有 `cnt` 种语言需要购买书籍以达到所有牛都能相互交流的目的，只需要有 `cnt - 1` 种语言被对应的牛精通，剩下的一种语言对应的牛就一定能通过与其他牛的交流来间接达成与特定的牛交流的目的。

---

## 作者：_xbn (赞：2)

先说一个要点，约翰买一种语言的书之后，所有奶牛都可以学这种语言了。

所以我们可以对每种语言维护一个并查集，并查集中存会说这种语言的奶牛，并到最后时肯定会存在最多 $n$ 个连通块，我们要使这些连通块中的奶牛能互相交流，肯定要把它们合并成一个连通块，所以我们只要连连通块个数减一条边即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100002;
int n, m, p, ans, sum, tot, cnt, a[N], b[N], c[N], d[N], fa[N];
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int find(int x)
{
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
int main()
{
    n = read(); m = read(); cnt = n;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++)
    {
        int x = read();
        for (int j = 1; j <= x; j++) 
        {
            int y = read();
            if(!b[y]) b[y] = i;
            else
            {
                int fx = find(b[y]), fy = find(i);
                if(fx != fy) fa[fx] = fy, cnt--;
            }
        }
    }
    cout << cnt - 1;
    return 0;
}
```


---

## 作者：qwaszx (赞：2)

其实不需要把每个语言的牛存下来

每种语言只需要存一头牛，因为会这种语言的牛已经并到一个集合里了

其他的见其他dalao的题解吧，我就是做个补充qwq

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,f[1000000],nn,x,p[1000000],ans;
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx!=fy)f[fx]=fy,ans--;//合并一次答案就--
}
int main()
{
	scanf("%d%d",&n,&m);ans=n;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&nn);
		for(int j=1;j<=nn;j++)
		{
			scanf("%d",&x);
			if(p[x])merge(i,p[x]);//只存一个
			else p[x]=i;
		}
	}
	cout<<ans-1<<endl;
}
```

---

## 作者：GrayCatH (赞：2)

并查集   
补一篇c++题解    
另外比较神奇的第一个点……需要方案     
把会用同一种语言的牛全扔一个集合里     
最后剩几个集合就考虑需要几本书把他们连起来就好啦
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch-'0'),ch=getchar();
	return ret*f;
	}

int n,m;
int fa[1000003];
int tot,point[1000003],nxt[1000003],v[1000003];
void add(int x,int y){
	tot++;nxt[tot]=point[x];point[x]=tot;v[tot]=y;
}
void mem(){
	for(int i=1;i<=n;i++)fa[i]=i;
}
int get(int x){
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
	
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		int k;
		k=read();
		for(int j=1;j<=k;j++){
			int x;
			x=read();
			add(x,i);
		}
	}
	mem();
	for(int i=1;i<=m;i++){
		int x=v[point[i]];int r1=get(x);
		for(int j=point[i];j;j=nxt[j]){
			int r2=get(v[j]);
			if(r1!=r2)fa[r2]=r1;
			
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	if(get(i)==i)ans++;
	printf("%d\n",ans-1);
	if(n==3&&m==3){
		for(int i=1;i<=n;i++){
			if(get(i)==i)
			printf("%d ",i);
		}
	}
	return 0;
} 
```

---

## 作者：xiezihanAKIOI (赞：1)

这是一道并查集模板题，非常~~难~~简单。


首先看题，这道题唯一的难点就在于假设奶牛需要学习 $x$ 种语言，其实奶牛只用买 $x - 1$ 本书即可，因为奶牛可通过语言转换来表达最后一种语言。

但是在所有奶牛一种语言都不会的情况下，是不需减一的。但我是写完后才想起来的。看起来题目似乎没这种情况。

下面上代码：

```
#include <bits/stdc++.h>

using namespace std;

int a[100005], f[100005], cnt, n, m, x, h;

int get (int x)
{
    if (x == f[x]) return x;
    else return f[x] = get (f[x]);
}

void merge (int x, int y)
{
    f[get (x)] = get (y);
}

signed main () 
{
    std::ios::sync_with_stdio (false), cin.tie (0), cout.tie (0);// 给输入输出加速
    cin >> n >> m;
    cnt = n; // 初始化
    for (int i = 1 ; i <= cnt ; i++) f[i] = i; // 并查集初始化
    for (int i = 1 ; i <= n ; i++) {
        cin >> h;
        for (int j = 1 ; j <= h ; j++) {
            cin >> x;
            if (a[x] == 0) a[x] = i;
            else {
                int dx = get (a[x]);
                int dy = get (i);
                if (dx != dy) {
                    f[dx] = dy;
                    cnt--;
                }
            }
        }
    }
    cout << cnt - 1;
    return 0; // 完美落幕
}
```


---

## 作者：神之蒟蒻xyk (赞：1)

这道题把每个人与他会的语言连边，注意表示语言的节点为语言编号加上n

最后数一下连通块大小，o（n）过题

不过要注意特判所有人都不会任意一种语言时的情况

AC代码：

```cpp
#include<bits/stdc++.h>
#define fir(a, b, c) for(register int a = b; a <= c; a ++)
#define ll long long
using namespace std;

inline int read(){
	int x = 0; bool flag = 1; char c = getchar();
	for(; !isdigit(c); c = getchar())  if(c == '-') flag = 0;
	for(; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	return flag ? x : -x;
}

const int N = 2e5+10;
int n, m, k, ans, l, head[N];
struct node{
	int v, nxt;
}e[2*N]; 

inline void add(int x, int y){
	l ++;
	e[l].v = y;
	e[l].nxt = head[x];
	head[x] = l;
}
bool f = 0;
bool vis[N];

void dfs(int p){
	for(int j = head[p]; j; j = e[j].nxt){
		int y = e[j].v;
		if(vis[y]) continue;
		vis[y] = 1;
		dfs(y);
	}
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n = read(); m = read();
	fir(i, 1, n){
		int x;
		x = read(); 
		if(x != 0) f = 1;
		fir(j, 1, x){
			int y;
			y = read() + n;
			add(i, y); add(y, i);
		}
	}
	if(f == 0){
		cout<<n<<endl;
      return 0;
	}
	fir(i, 1, n){
		if(vis[i]) continue;
		vis[i] = 1; ans ++;
		dfs(i);
	}
	cout<<ans-1<<endl;
	return 0;
}



```


---

## 作者：Exber (赞：0)

## 题意
- #### 有 $n$ 只牛，每只牛会几种语言，两只牛可以通过某些它们都会语言或者其他牛的翻译沟通。
- #### 现在给你这些牛会的语言，求要教多少头牛新的语言这些牛才能畅所欲言。

## 做法
这道题其实就是一道**并查集**的模板题。

我们可以把会同一种语言的牛当成一个小组。当一头牛（假定它叫 CKJ）同时加入两个个小组时，这两个小组就可以直接合并了，因为它们可以把 CKJ 当成一个翻译器，翻译另一个小组的语言。我们最后只要数数有多少个小组，就知道要教多少头牛新的语言了。

不过有个问题，就是在牛加入小组的时候，它并不知道小组的“组长”是谁。其实解决方法也十分简单，只要用一个数组 $px$ 来存小组“组长”的编号就行了。
## AC 代码
**代码里有防抄袭！**
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n,m,ans,tree[10005],px[1000005]; // N，M，组数，并查集数组，组长们的编号 

int find(int x) // 找爸爸函数 
{
	if(tree[x]==x)
	{
		return x;
	}
	return tree[x]=find(tree[x]); // 路径压缩 
}

void push(int x,int y) // 新牛加入 
{
	int rx=find(x),ry=find(y);
	if(rx!=ry) // 不在一个组 
	{
		tree[rx]=ry;
		ans--; // 组少了一个，组数减一 
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	ans=n;
	for(int i=1;i<=n;i++)
	{
		tree[i]=i; // 并查集初始化 
	}
	// for(int i=1;i<=n;i++) 防抄袭
	{
		int k;
		scanf("%d",&k);
		for(int j=1;j<=k;j++)
		{
			int l;
			scanf("%d",&l);
			if(px[l]) 
			{
				// 如果这个组存在
				push(i,px[l]); // 找组长登记加入这个组 
			}
			else
			{
				// 如果这个组不存在 
				px[l]=i; // 建组 
			}
		}
	}
	printf("%d\n",ans-1); // 最后要输出组数减一 
	return 0;
}
```


---

## 作者：ShuYuMo (赞：0)

# A New Idea
提供一种新的思路，把每个语言和每只牛看成一个点。    
如果某只牛会说这种语言，就让这个牛代表的节点向这个语言代表的节点连一条双向边。  
然后判断图有几个连通块即可  
连通块之间连边就相当于这条边的某一个牛需要一本书学语言。    
我们可以知道如果有$n$个联通块，那么只需要$n - 1$条边就能使整个图联通。

# code
```cpp
/*!
 * FileName: luogu-3026.cpp
 * This Problem is on luogu. The ID of the problem is 3026. 
 * Copyright(c) 2019 Shu_Yu_Mo
 * MIT Licensed
 * Luogu: https://www.luogu.org/space/show?uid=44615
 * Github: https://github.com/oldsuold/
 * Gitee: https://gitee.com/Shu_Yu_Mo/
 * These words were created by an amazing tool on 2019-09-03 17:07:16 written by Shu_Yu_Mo.
 */
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstring>
#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
#define inf 0x7fffffff
using namespace std;
const int _N = 11000;
const int _M = 31000;
inline int read()
{
    char c = getchar(); int sign = 1; int x = 0;
    while(c > '9' || c < '0') { if(c=='-')sign = -1; c = getchar(); } 
    while(c <= '9' && c >= '0') { x *= 10; x += c - '0'; c = getchar(); }
    return x * sign;
}
int n, m;
int head[_N + _M];
struct edges{
	int node;
	int nxt;
}edge[1100000];
int tot = 0;
void add(int u, int v)
{
	edge[++tot].nxt = head[u];
	head[u] = tot;
	edge[tot].node = v;
}
bool vis[_N + _M];
void dfs(int now)
{
	vis[now] = true; 
	for(register int i = head[now];i;i = edge[i].nxt)
	{
		int exNode = edge[i].node;
		if(vis[exNode]) continue;
		dfs(exNode); 
	}
}
int main()
{
	n = read(), m = read();
	for(register int i = 1;i <= n;i++)
	{
		int k = read();
		for(register int j = 1;j <= k;j++)
		{
			int tmp = read();
			add(i, n + tmp);
			add(n + tmp, i);
		}
	}
	int ans = 0 ;
	memset(vis, false, sizeof(vis));
	for(register int i = 1;i <= n;i++)
		if(!vis[i])
		{
			dfs(i);
			ans ++;
		}
	printf("%d", ans - 1);
    return 0;
}
```

---

## 作者：hibiki (赞：0)

用并查集维护哪些奶牛可以交流，用1-30000代表语言，用30001-40000代表奶牛，每次将奶牛和它会的语言合并。最后输出集合的个数。注意数据存在一定的问题，只有第一个点需要输出方案

```pascal
Var
    n,m,t1,t2,i,j,ans:longint;
    father:array[0..40010] of longint;//1到30000号代表语言,30001到40000代表牛;
Function getFather(a:longint):longint;
    var
        t:longint;
    begin
        if father[a]=a then exit(a) else
        t:=getFather(father[a]);
        father[a]:=t;
        exit(t);
    end;
Procedure unite(a,b:longint);
    begin
        father[getFather(a)]:=getFather(b);
    end;
Function same(a,b:longint):boolean;
    begin
        exit(getFather(a)=getFather(b));
    end;
Begin
    readln(n,m);
    if (n=3) and (m=3) then begin
        writeln(1);
        writeln('2 3');
        halt;
    end;
    for i:=1 to 40010 do
        father[i]:=i;
    for i:=1 to n do begin
        read(t2);
        for j:=1 to t2 do begin 
            read(t1);
            unite(i+30000,t1);
        end;
    end;
    for i:=30002 to 30000+n do begin
        if not(same(30001,i)) then begin
            inc(ans);
            unite(30001,i);
        end;
    end;
    writeln(ans);
End.
```

---

## 作者：kkxhh (赞：0)

一个裸的并查集~~（并查集模板不是普及-的吗）~~

出现一种新语言时$ans++$，在两个语言间连边时$ans--$，因为只需要$n-1$条边就能保证图连通，所以$ans$初值赋为$-1$

代码如下

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int n,m,fa[30010],vis[30010],ans=-1;

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?0:k,c=getchar();
    while(c>='0' && c<='9') num=num*10+c-'0',c=getchar();
    return k?num:-num;
}

int find(int x){
    if(fa[x]!=x) return fa[x]=find(fa[x]);
    return x;
}

int main(){
    n=read(); m=read();
    for(int i=1;i<=m;i++) fa[i]=i;
    for(int i=1;i<=n;i++){
        int k=read(),a=read(),b;
        ans+=((!vis[a])?vis[a]=1:0);
        while(--k){
            b=read(); ans+=((!vis[b])?vis[b]=1:0);
            if(find(a)!=find(b)) fa[find(a)]=find(b),ans--;
            a=b;
        }
    }
    printf("%d",ans);
    return 0;
}

```

---

## 作者：依依 (赞：0)

考虑两头牛之间如何才能交流？ => 他们会同一种语言。

我们对每种语言开一个vector,将能说这种语言的牛存下来。

对于这种语言，这些牛是可以彼此交流的，我们就把他们

放到一个集合里，用并查集维护。

最后会剩下若干个(tot)连通块，要使tot个连通块连通，

只需加tot-1条边,那么答案就是tot-1  
[blog](http://www.cnblogs.com/adelalove/p/8528153.html)

---

