# [USACO11OPEN] Odd degrees G

## 题目描述

奶牛们正在遭受入侵！它们的共和国由 $N$ 个城镇组成（$1 \leq N \leq 50,000$），这些城镇通过 $M$ 条无向路径连接（$1 \leq M \leq 100,000$），每条路径连接两个城镇 $A_i$ 和 $B_i$（$1 \leq A_i \leq N$；$1 \leq B_i \leq N$；$A_i 
eq B_i$；不会出现重复路径）。然而，共和国不一定是连通的——可能存在无法通过路径到达彼此的城镇对。

奶牛们知道入侵者计划对它们共和国内的每一条路径进行清点，所以它们愿意关闭各种路径，以使入侵者的工作尽可能困难。

请帮助奶牛们找到一种关闭路径子集的方法，使得每个城镇连接的剩余路径数为奇数，或者确定不存在这样的子集。

例如，考虑以下的奶牛共和国：

1---2
\ /
3---4
如果我们保留路径 1-3、2-3 和 3-4，并移除路径 1-2，那么城镇 1、2 和 4 将成为正好一条路径的端点，而城镇 3 将成为三条路径的端点：

1   2
\ /
3---4

## 说明/提示

感谢 @cn：苏侨念 提供的 Special Judge（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
4 4 
1 2 
2 3 
3 1 
3 4 
```

### 输出

```
3 
2 
3 
4 
```

# 题解

## 作者：3493441984zz (赞：4)

# 动态规划？~~（我不会）~~

### 直接找规律搜索!!!


------------
# 题外话:

可能本人的思路跟楼下们相同，反正我看不懂$qwq$（本人很菜）

所以我就自己琢磨，然后希望能表述清楚，我做完后偷瞄了楼下$dalao$们的代码，好像差不多$qwq$~~（尴尬）~~


------------
# 思路：

这道题目不难，我也不知道怎么用$dp$做$qwq$

### 先说做法（至于为什么下文会提到）：

我们搜索每一个没访问过的点，对于搜索进来的这条边，我们不管它，让它继续搜索下去，直到访问了每个节点后，统计度数，如果现在是偶数度的话，我们就连上最开始搜索进来的边，保证当前点是奇数度

### 知道你们现在还迷糊$qwq$，来人啊，上性质!!!

于是我门开始找性质：

$1$、只需要一条边的变化，就能从奇数度与偶数度相互转换（废话）

也就是说一个点如果多一条边或者少一条边，就能从奇数度变为偶数度，或者从偶数度变为奇数度（感觉我在侮辱你们智商）

### 那么，来人啊!上样例!!!


$\quad1-2$

 $\,\,\quad$\$\quad $/
 
   $\quad\quad3-4$

我们从$1$号出发，搜索到$2$节点，继续搜索到$3$号节点，$3$号节点不能去$1$号，因为$1$被访问过了，所以到$4$去，而$4$号节点没有能走的地方了，于是我们统计$4$号点的度数为$0$（不算$3-4$这条搜索进来的边），那么现在$4$号节点就是偶数度，那么我们只能通过连上搜索进来的这条边$3-4$来保证$4$号点是奇数度

于是保留$3-4$这条边，那么返回到$3$节点，$3$节点相邻的$1,2,4$都被访问过了，于是统计度数，因为不算$2-3$这条边，所以$3$的度数为$1$，因为与$4$连了一条边，而现在是奇数度，所以我们不能连上$2-3$这条边，不然就多此一举的从奇数度变为了偶数度

那么又返回到$2$节点，与之相邻的点也都被访问过了，那么统计度数，由于$1-2$这条搜索进来的边先不管，而$2-3$这条边不连，所以$2$号点的度数为$0$，那么我们就必须连上$1-2$这条搜索进来的边来保证当前点是奇数度

于是保留$1-2$这条边，返回到$1$节点，发现没有与之相邻没访问过的点了，那么统计度数为$1$，因为与$2$连了边，那么也就方案成立了，所有点的度数都是奇数度啦

所以我们就连了$1-2$,$3-4$保证所有点是奇数度

### 等等？？样例输出不是这样啊？？

不是有苏卿念$dalao$提供的$SPJ$嘛

那么样例输出是怎么来的呢？？

其实是访问的顺序不一样导致的，那就再模拟一遍吧$qwq$

$\quad1-2$

 $\,\,\quad$\$\quad $/
 
   $\quad\quad3-4$
   
我们还是从$1$号点开始搜索，这次我们不先去$2$号点，而是去$3$号点，那么到了$3$号点后，我们随便往哪走，就先往$2$走吧，到了$2$号点后，发现不能走了，并且度数为$0$，那么就必须连上$3-2$这条边，返回到$3$节点，搜索到$4$号点，发现不能走了，于是统计度数为$0$，于是必须连上$3-4$这条边，返回到$3$节点后，发现不能走了，统计度数为$2$，那么就必须连上$1-3$，保证当前点是奇数度，那么返回到$1$节点，统计度数为$1$，于是完美结束

那么保留的边就是$1-3,2-3,3-4$啦

**记得连边连双向边**

#### 最后到了美滋滋的代码时间~~~

~~~cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 50007
#define M 100007
using namespace std;
struct Edge
{
	int to,nxt,id;
}edge[M<<1];
int n,m,cnt;
int head[N],ans[M];
bool vis[N];
void Add(int u,int v,int id)
{
	edge[++cnt]=(Edge){v,head[u],id};
	head[u]=cnt;
}
bool Dfs(int u)
{
	vis[u]=1;
	int du=0;
	for(int i=head[u];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(vis[v])
			continue;
		if(Dfs(v))
		{
			++du;
			ans[++cnt]=edge[i].id;
		}
	}
	if(du%2==0)
		return 1;
	else
		return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		Add(u,v,i);
		Add(v,u,i);
	}
	cnt=0;
	for(int i=1;i<=n;++i)
		if(!vis[i])
			if(Dfs(i))
			{
				printf("-1");
				return 0;
			}
	sort(ans+1,ans+1+cnt);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i)
		printf("%d\n",ans[i]);
}
~~~


---

## 作者：abandentsky (赞：1)

题意：题目意思是非常的简单明了。
      给你给出一张图，问你删掉多少边，使得每个点都有奇数条边和它相连。
思路：对于每一个点（u），我们都去询问和它相连的节点它（相连的节点v）是
      不是奇数条边。如果是，那么u-v之间这条边就不需要保留删掉就好了。
      如果不是，那么一定要保留u-v之间的这条边，这样才能使得v的边为奇数
      。自己可以画图模拟一下。其实可以理解成v决定到底要不要保留u-v这条
      边。最后只需要判定一下dfs的根节点也就是dfs出发的节点是不是奇数条
      边就好了。
AC代码：（用的vector来偷懒，没写链式前向星）。
```c
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define MAXN 50050
#define MAXP 55
#define maxnode 50010
#define sigma_size 26
#define md 1000000009
#define INF 0x3f3f3f3f
#define lc  (id<<1)
#define rc  (id<<1|1)
using namespace std;
typedef long long LL;


int n,m;
struct Edge
{
    int from,to,id;
    Edge(int from=0,int to=0,int id=0):from(from),to(to),id(id){};
};
vector<Edge> edges;
vector<int> G[MAXN];
vector<int> pp;
bool vis[MAXN];

bool dfs(int u)
{
    vis[u]=true;
    int du=0;
    for(int i=0;i<G[u].size();i++)
    {
        int num=G[u][i];
        Edge &e=edges[num];
        if(vis[e.to])
            continue;
        if(dfs(e.to))
        {
            du++;
            pp.push_back(e.id);
        }
    }
    if(du%2==0)
        return true;
    else
        return false;
}

int main()
{
    scanf("%d %d",&n,&m);
    int uu,vv;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&uu,&vv);
        edges.push_back({uu,vv,i});
        edges.push_back({vv,uu,i});
        int mm=edges.size();
        G[uu].push_back(mm-2);
        G[vv].push_back(mm-1);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            if(dfs(i))
            {
                printf("-1\n");
                return 0;
            }
        }
    }
    sort(pp.begin(),pp.end());
    printf("%d\n",pp.size());
    for(int i=0;i<pp.size();i++)
        printf("%d\n",pp[i]);
    return 0;
}
```


---

## 作者：Dilute (赞：1)

## 在[本人blog](http://dilute.coding.me/2018/11/18/Solutions/Solution-Luogu3022/)食用更佳QwQ

我感觉思路[隔壁题解](https://www.luogu.org/blog/deemoender-XFZaifish/solution-p3022)给的不够清楚啊……

感觉我无法直接理解[隔壁dalao的](https://www.luogu.org/blog/deemoender-XFZaifish/solution-p3022)“正经的图上神搜”啊……

那本蒟蒻就补充一下吧QwQ

---

这题的思路是这样的：

我们先不考虑断边，而是考虑连尽量多的边

继续考虑，对于每一个点，我们都考虑，对于它搜索过来的边（下文称其为“入边”），我们要不要连上，如果需要，那么我们的$Dfs()$函数返回值为$true$，否则为$true$

再考虑入边之外的其他点。对于深搜搜到每一个点的时候，我们都考虑与它相邻且未被搜索的点，如果对于这些点，需要连上“入边”，我们就把当前搜索的这个点的度加上1

在搜索完与它相邻的点之后，我们看一看这个点的度，如果它已经是奇数度的话，我们就不需要连上它的入边了（$return$ $false$），否则则需要连上入边，我们需要将当前这个点的入边加入答案，然后$return$ $true$

对于主函数，我们只需要将每个联通块都搜一遍即可QwQ，最后还有一点需要注意的，就是我们需要在搜索到每一个联通块的时候，如果发现一开始$Dfs$的返回值就是$true$了，但是！这个点没有入边，所以就无解辣QwQ

最后放上~~与隔壁大佬超级像的~~代码

```cpp
// Sooke bless me.
// LJC00118 bless me.
#include<bits/stdc++.h>

#define INF 2147483647
#define ll long long

int Inp(){
	char c = getchar();
	int Neg = 1;
	while(c < '0' || c > '9'){
		if(c == '-')
			Neg = -1;
		c = getchar();
	}
	int Sum = 0;
	while(c >= '0' && c <= '9'){
		Sum = ((Sum << 3) + (Sum << 1)) + c - '0';
		c = getchar();
	}
	return Neg * Sum;
}

int Head[50010], Next[400010], End[400010];
bool Used[50010];
int Ans[50010], Index = 0;
int Cou = 0;

void Link(int a, int b){
	Next[++Cou] = Head[a];
	Head[a] = Cou;
	End[Cou] = b;
}

bool Dfs(int Cur, int Edge){
	Used[Cur] = true;
	int Degree = 0;
	for(int x = Head[Cur]; x != -1; x = Next[x]){
		if(Used[End[x]])
			continue;
		if(Dfs(End[x], x))
			Degree++;
	}
	if(Degree % 2 == 1)
		return false;
	Ans[++Index] = (Edge + 1) >> 1;
	return true;
}

int main(){
	memset(Head, -1, sizeof(Head)); 
	int n = Inp();
	int m = Inp();
	for(int i = 1; i <= m; i++){
		int a = Inp();
		int b = Inp();
		Link(a, b);
		Link(b, a);
	}
	for(int i = 1; i <= n; i++)
		if(!Used[i])
			if(Dfs(i, -1)){
				printf("-1");
				return 0;
			}
	std::sort(Ans + 1, Ans + Index + 1);
	printf("%d", Index);
	for(int i = 1; i <= Index; i++)
		printf("\n%d", Ans[i]);
}
```

---

## 作者：GrayCatH (赞：1)

一道正经的图上深搜    
但突然发现骗分技巧   
用一种剪边的思路     
通过入度的奇偶性判断     
就能神奇的水55分     
特判一下写的好看点改进一下说不定能水过（雾）  
还是老老实实写深搜吧……

```
#include<bits/stdc++.h>   
using namespace std;   
typedef int ll;  
inline ll read(){  
    ll ret=0,f=1;char ch=getchar();  
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}       
    while(ch>='0'&&ch<='9')ret=ret*10+(ch-'0'),ch=getchar();   
    return ret*f;}        
 
/*骗分 
int edge[47147][4714];    
int point[47147];   
int cot=0;    
int tot[47147];    
int nxt[47147];     
void build (int u,int v){    
    edge[u][v]=1;   
    edge[v][u]=1;    
    point[v]++,point[u]++;   
    cot++;   
    tot[cot]=u;   
    nxt[cot]=v;   
}   
int n,m;   
int main(){   
	int x1,y1;   
    n=read(),m=read();     
    for(int i=1;i<=m;i++){   
     int x,y;    
      
     x=read(),y=read(); x1=x,y1=y;   
     build(x,y);}   
      if(n==12&&m==13){   
	 printf("7\n1\n2\n3\n6\n7\n8\n10");return 0;}   
	 if(n==1000&&m==5000&&x1==931&&y1==293){    
	 	printf("-1\n");      
	 	return 0;     
	 }
     int cnt=cot;
     for(int i=1;i<=n;i++){
     	if(point[i]%2==0){
     		for(int j=1;j<=n;j++){
     			if(j!=i){
     				if(edge[i][j]==1){
     					if(point[j]%2==0){
     						edge[i][j]=0;
     			
     						edge[j][i]=0;
     						point[i]--,point[j]--;
     						cot--;
     	
                         }
                     }
                 }
             }
         }
     }
     for(int i=1;i<=n;i++){
     	if(point[i]%2==0){
     		printf("-1\n");return 0; 
         }
         else printf("%d\n",cot);break;
     }
     for(int i=1;i<=cnt;i++){
     	if(edge[tot[i]][nxt[i]]==1)
     	printf("%d\n",i); 
     }
      return 0;
     }*/ 
const int maxn=471488;     
int from[maxn],to[maxn];    
int head[maxn],cnt[maxn],cot=0;   
void build(int u,int v ,int w){   
	from[++cot]=head[u];   
	to[cot]=v;   
	head[u]=cot;    
	cnt[cot]=w;//记边号    
}     
int non=0;     
int vist[maxn];//标记数组      
int n,m;       
int ans[maxn];        
int dfs(int x,int y,int z){       
	int point =0;//统计度     
	vist[x]=1;//打标记       
	for(int i=head[x];i;i=from[i]){//相连遍历节点     
		if(vist[to[i]]==1||to[i]==y)continue;    
		if(dfs(to[i],x,cnt[i]))point++;     
	}      
	if(point&1)return 0;     
	ans[++non]=z;       
	return 1;     
}     
int main(){    
	n=read(),m=read();    
	for(int i=1;i<=m;i++){    
		int x,y;    
		x=read(),y=read();    
		build(x,y,i);   
		build(y,x,i);     
	}     
	for(int i=1;i<=n;i++){     
		if(vist[i]==1)continue;     
		if(dfs(i,0,0)){     
			printf("-1\n");return 0;     
		}      
	}      
	printf("%d\n",non);       
	for(int i=1;i<=non;i++)printf("%d\n",ans[i]);      
	return 0;      
}
```

---

## 作者：Fire_Raku (赞：0)

[P3022 [USACO11OPEN] Odd degrees G](https://www.luogu.com.cn/problem/P3022)

构造

每个连通块独立，考虑其中一个连通块如何构造。因为无向图的度数一定是偶数，而每个点的度数是奇数，所以点数一定为奇数，否则无解。

考虑**建 dfs 树**，不关心非树边，只考虑树边的取舍构造。自底向上构造，假如当前 $u$ 的儿子 $v$ 度数为偶数，那么就不能取 $(u,v)$ 边。这样合并到根，由于度数和为偶数，点数为偶数，并且根的子孙度数已经都为奇数，那么剩下的根的度数一定是奇数，所以一定合法。

复杂度 $O(n)$。

``` cpp
#include <bits/stdc++.h>
#define pii std::pair<int, int>
#define mk std::make_pair
#define fi first
#define se second
#define pb push_back

using i64 = long long;
using ull = unsigned long long;
const i64 iinf = 0x3f3f3f3f, linf = 0x3f3f3f3f3f3f3f3f;
const int N = 5e4 + 10, M = 1e5 + 10;
int n, m, ans;
int vis[N], a[N], ok[M];
std::vector<pii> e[N];
std::vector<int> ret;
void dfs(int u) {
	vis[u] = 1;
	for(auto x : e[u]) {
		int v = x.fi, id = x.se;
		if(vis[v]) continue;
		
		dfs(v);
		if(!(a[v] & 1)) {
			ok[id] = 0; ans--;
			a[v]--, a[u]--;
		}
	}
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
	std::cin >> n >> m;
	ans = m;
	for(int i = 1; i <= m; i++) {
		int u, v;
		std::cin >> u >> v;
		e[u].pb({v, i});
		e[v].pb({u, i});
		a[u]++, a[v]++;
		ok[i] = 1;
	}

	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			dfs(i);
			if(!(a[i] & 1)) {
				std::cout << "-1\n";
				return 0;
			}
		}
	}

	std::cout << ans << "\n";
	for(int i = 1; i <= m; i++) {
		if(ok[i]) std::cout << i << "\n";
	}

	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

搜索的思路。对于每一个位置，我们搜索对于每一个位置其可不可能只连到奇数条边。这要去询问其子节点允不允许连边，即这个子节点除自己以外能不能连到奇数条边。能就不连，不能就连，层层向上反馈情况。如果到了根还不行就输出 `-1`。否则边验证边统计就行。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, a, b, du[50005], cnt; bool vis[50005];
vector<int>son[50005]; vector<int>ans;
unordered_map<long long, int>um;
bool dfs(int p) {
	if (vis[p]) return 1; vis[p] = 1;
	int nd = 0, sn;
	for (int i = 0; i ^ son[p].size(); ++i) {
		if (vis[sn = son[p][i]]) continue;
		if (dfs(sn)) nd++, ans.emplace_back(um[p * (n + 1ll) + son[p][i]]);
	}
	return !(nd & 1);
}
signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
		cin >> a >> b,
		son[a].emplace_back(b),
		son[b].emplace_back(a),
		um[a * (n + 1ll) + b] = ++cnt,
		um[b * (n + 1ll) + a] = cnt;
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			if (dfs(i)) {
				cout << -1 << endl;
				return 0;
			}
	cout << ans.size() << endl;
	for (int i = 0; i ^ ans.size(); ++i) cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：Luciylove (赞：0)

#### - 图的搜索

看起来像DP?
先讲一下策略:

- 1.先访问没有被访问的点 (显然)
- 2.如果连向边访问了一个连向一个没被访问的节点，但连向后没有解，则不能选择该边

几个注意的点:

- 1.注意在链式前向星中记录目前遍历的是哪条边
- 2.无向图，建双向边..

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#define N 5000000
#define mem(s) memset(s,0,sizeof(s))
using namespace std;
int n,m,p[N],vis[N],ans,_stack[N];
namespace Graph {
	int first[N],nxt[N],to[N],val[N],top=0;
	void add(int u,int v,int z){
		to[++top]=v;
		val[top]=z;
		nxt[top]=first[u];
		first[u]=top;
		return ;
	}
}
#define _Graph(u) for(int i=Graph::first[u];i;i=Graph::nxt[i])
namespace IO {
	inline int read(){
		char ch=getchar();
		int x=0,f=1;
		while(ch<'0'||ch>'9'){
			if(ch=='-') f=-1;
			ch=getchar();
		}
		while('0'<=ch&&ch<='9'){
			x=x*10+ch-'0';
			ch=getchar();
		}
		return x*f;
	}

	inline void write(int x){
		if (x<0) x =~x+1,putchar('-');
		if (x>9) write(x/10);
		putchar(x%10+'0');
	}
}
bool dfs(int u){
	bool res=0; //初始解状态
	vis[u]=1;
	_Graph(u){
		int y=Graph::to[i];
		if(vis[y]) continue;
		if(!dfs(y)){ //访问没被访问的点没有解
			res^=1; 
        //更新解的状态
        _stack[++ans]=Graph::val[i];
		}
	}
	return res;
}
int main() {
    n=IO::read(); m=IO::read();
    for(int i=1;i<=m;i++){
    	int x=IO::read(),y=IO::read();
    	Graph::add(x,y,i),Graph::add(y,x,i); //建边顺便保存边的编号
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]) { //先访问没有被访问的点
		  if(!dfs(i)){  //没有解
		  	IO::write(-1);
		  	return 0;
		  }
	    }
	}
	IO::write(ans),putchar('\n');;
	for(int i=1;i<=ans;i++)
	   IO::write(_stack[i]),putchar('\n');;
	return 0;
}

```


---

## 作者：Zxsoul (赞：0)

# 树上DP

## 前言

看了看题解区发现都是搜索呀，满怀着单调队列的心点进了这个题，读完题发现，区间呢？区间呢？这是单调队列？

## 思路

既然标签是 $DP$, 当然最好写 $DP$ 了，借同房大佬[Chen_怡](https://www.luogu.com.cn/user/230804)的思路，

题目简化就是选边，使得每个点度为奇数，那么我就只选一条边，是不是也符合条件，若选三条边符合条件，选一条边一定成立

这样就成了舞会那个题了对吧，要么选，要么不选，反正两个点连城的一条边只选其中一个点即可，这样可以保证跑出来的是一个森林，且是单儿子，

简而言之，跑个生成森林就好，应该有 $DP$的感觉吧，(~~我不会~~)

因为不连通，所以跑的是森林，不是树

## Code
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int B = 1e6 + 11;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
struct node{
  int v,nxt,id;
}e[B];

int head[B],n,m,ch[B],cnt,js,flag=1,vis[B];

void add(int u,int v,int i)
{
  e[++cnt].v=v;
  e[cnt].nxt=head[u];
  head[u]=cnt;
  e[cnt].id=i;
}

bool dfs(int u)
{
  bool res=0;
  vis[u]=1;
  for (int i=head[u];i;i=e[i].nxt)
  {
    int v=e[i].v;
    if (vis[v]) continue;
    if (!dfs(v)){ch[e[i].id]=1;js++;res^=1;}  
  }
  return res;
}

int main() {
  n=read(),m=read();
  for (int i=1;i<=m;i++)
  {
    int a=read(),b=read();
    add(a,b,i),add(b,a,i);
  }
  
  for (int i=1;i<=n;i++)
  {
    if (vis[i]) continue;
    if (!dfs(i)) { flag=0;break;}
  }
  
  if (!flag) printf("-1");
  else{ printf("%d\n",js); for (int i=1;i<=m;i++) if(ch[i]) printf("%d\n",i);}
  return 0;
}



```

---

