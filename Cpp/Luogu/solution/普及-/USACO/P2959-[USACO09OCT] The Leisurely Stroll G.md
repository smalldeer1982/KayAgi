# [USACO09OCT] The Leisurely Stroll G

## 题目描述

Bessie looks out the barn door at the beautiful spring day and thinks to herself, 'I'd really like to enjoy my walk out to the pastures for the tender spring grass.' She knows that once she leaves the barn, she will traverse a path for a while, take one of two choices that lead to other paths, follow one of them, take one of two other choices, and continue on until the path leads to a verdant pasture.

She decides to make the set of path choices that enables her to walk over the greatest number of cow paths on her way to breakfast. Given the description of these paths, determine how many cow paths she traverses, presuming that she commences choosing various paths as soon as she leaves the barn.

The farm has P (1 <= P <= 1,000) pastures that are lead to by P-1 choice-nodes (range 1..P-1) connected by paths. From the barn (which is node 1), only one set of path traversals exists to reach any choice-node or pasture.

Consider this set of paths (lines), pastures ('%'), and the highlighted ('#') route to a pasture on the right:

```cpp

                 %                             %
                /                             /
      2----%   7----8----%          2----%   7####8----%
     / \      /      \             # #      #      #
    1   5----6        9----%      1   5####6        9----%
     \   \    \        \           \   \    \        #
      \   %    %        %           \   %    %        %
       \                             \
        3-----%                       3-----%
         \                             \
          4----%                        4----%
           \                             \
            %                             %
```
The pasture reached from choice-node 9 is one of two that enable Bessie to traverse seven different cowpaths on the way to breakfast. These are the 'furthest' pastures from node 1, the barn.

Three integers describe each node: Cn, D1, and D2. Cn is the

nodenumber (1 <= Cn <= P-1); D1 and D2 are the destinations from that node (0 <= D1 <= P-1; 0 <= D2 <= P-1). If D1 is 0, the node leads to a pasture in that direction; D2 has the same property.

POINTS: 100

Bessie透过牛棚的大门向外望去。发现今天是一个美丽的春季早晨。她想，“我真的好想好想沐浴着春风，走在草地之中，感受嫩草温柔地抚摸四蹄地的感觉。”她知道一旦她离开了牛棚，她将沿着一条小径走一段路，然后就会出现一个三岔路口，她必须在两条小径中选择一条继续走下去。然后她又会遇到更多的三岔路口，进行更多的选择，知道她到达一个青翠的牧场为止。

她决定作一个选择使得她在去吃早草的路途中可以走过最多的小径。给你这些小径的描述，求出Bessie最多可以走过多少条小径。假定Bessie一出牛棚就有2条路径，Bessie需要从中选择一条。

农场中有P-1 (1 <= P <= 1,000) 个分岔节点（范围是1..P），引向P片草地，它们之间由小径连接。对任意一个节点来说，只有一条从牛棚（被标记为节点1）开始的路径可以到达。

考虑下面的图。线段表示小径，"%"表示草地。右边的图中的"#"表示一条到达草地的高亮的路径。

从分岔节点9到达的草地是两个可以让Bessie走过最多小径的草地之一。在去吃早草的路上Bessie将走过7条不同的小径。这些草地是离牛棚也就是节点1最“远”的。

由3个整数来表示每一个节点：Cn, D1和D2，Cn是节点的编号(1 <= Cn <= P-1); D1和D2是由该节点引出的两条小径的终点(0 <= D1 <= P-1; 0 <= D2 <= P-1)。如果D1为0，表示这条小径引向的是一片牧草地；D2也一样。


## 说明/提示

This input describes the example farm layout in the task description.


1-2-5-6-7-8-9-P is one of the longest routes.


## 样例 #1

### 输入

```
10 
7 8 0 
5 0 6 
9 0 0 
6 0 7 
3 4 0 
2 5 0 
8 0 9 
4 0 0 
1 2 3 
```

### 输出

```
7 
```

# 题解

## 作者：Alex_Wei (赞：36)

### 题解 P2959 【[USACO09OCT]悠闲漫步The Leisurely Stroll】

一道对DFS新手比较友好的题目

#### 题目其实就是问Bessie最多能走过多少分岔节点

### 思路：DFS（BFS也可以），边搜索边更新答案

#### 具体思路见~~（一份对DFS新手比较友好的）~~代码：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int p,a[1010],b[1010],c,n;//a[x],b[x]是分岔节点x通向的两块区域，n是答案 
void dfs(int m,int s)//到达分岔节点m，共走过了s个分岔节点
{
	if(a[m]!=0)dfs(a[m],s+1);//如果不是牧场就前往这个分岔节点
	if(b[m]!=0)dfs(b[m],s+1);//同上
	n=max(n,s);//更新答案
}
int main()
{
	cin>>p;
	for(int x=1;x<p;x++)cin>>c,cin>>a[c]>>b[c];//输入 
	dfs(1,1),cout<<n;//输出 
	return 0;
}
```
#### 如果有错误欢迎在右侧——>评论区指正

~~求赞QWQ~~

---

## 作者：zy小可爱ღ (赞：5)

hello，隔了好长时间，我又来发我的蒟蒻题解了   
~~我才不会告诉你我寒假时间都用来玩了嘞~~  
咳咳，回归正题，开始说题目  
这道题目并不难，应该说只要会DFS都应该会~~我知道肯定有人会想打我~~  
题目表述比较清晰，但图比较唬人，一直我刚做的时候还数了一下每条路径的长短，之后编程考虑细节的时候发现根本没用，直接当成1就好了    
好，不说废话，直接上代码：   
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int n,ans=-1;
int a[1500][5];//用来记录哪两个点之间有路径

int ma(int a,int b){//用来比较两数大小，和max相同，但速度较快，纯属个人习惯
	return a>b?a:b;
}

void dfs(int t,int an){//t表示当前访问的顶点编码，an表示当前答案
	if(a[t][1]==0){//如果有一条路径通往草地，更新答案
		ans=ma(an+1,ans);//因为还要走一条路，所以an要加1
	}
	else{//不然继续循环
		dfs(a[t][1],an+1);
    }
	if(a[t][2]==0){//因为有两条路，判断两边，其余同上
		ans=ma(an+1,ans);
	}
	else{
		dfs(a[t][2],an+1);
    }//懒得加return
}

int main(){
	scanf("%d",&n);//读入不解释
	for(int i=1;i<n;i++){
		int s;
		scanf("%d",&s);//先读入顶点编号
		scanf("%d%d",&a[s][1],&a[s][2]);//读入此顶点与哪两个顶点相连
	}
	dfs(1,0);//DFS
	printf("%d\n",ans);//输出答案
	return 0;
}
```
放抄袭的手段我就不做了，无非就是换中文字符之类的，真心建议DFS新手做一下，题目虽然不难，但还是有一定帮助的   
祝大家AC！！

---

## 作者：Shiloh (赞：4)

```cpp
//嘛，虽然题面看起来有些吓人，实际上本题还是一道很水的搜索。
//需要注意的都写在注释里了。
#include <iostream>
#include <algorithm>

using namespace std;

inline int dfs(register int n, register int tot, register int* path1, register int* path2)
//register随便加，反正寄存器一般用不完，inline也随便加，编译器会自己判断。
{
    static int ans = 0; //声明成静态来保存数据。
    if(a[m] != 0)
    {
        ans = dfs(path1[n], tot+1, path1, path2);//到path1的这个分叉
    }
    if(b[m] != 0)
    {
        ans = dfs(path2[n], tot+1, path1, path2);//到path1的这个分叉
    }
    return max(ans, tot);
}
signed main(void)//signed是为了万一要用typedf int long long的时候容错。
				 //加void是写工程的好习惯。
{
    register int l = 0, t = 0, path1[1000] = {}, path2[1000] = {}; //初始化每个变量是好习惯。
    std::cin >> l;//加std::也是写工程的好习惯。
    for(register int x = 1; x < l; ++x)
    {
        std::cin >> t >> path1[t] >> path2[t];
    }
    std::cout << dfs(1, 1, path1, path2) << std::endl;//加endl刷新缓冲区也是好习惯。
    return 0;
}
```

---

## 作者：清风我已逝 (赞：4)

SPFA最长路

```cpp
#include<bits/stdc++.h>
#define N 101010

using namespace std;

void in(int &x){
	register char c=getchar();x=0;int f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	x*=f;
}

int n,head[N],ans,tot;
struct node{
	int to,next;
}e[N];

void add(int u,int v){
	e[++tot].to=v;e[tot].next=head[u];head[u]=tot;
}

int d[N];bool vis[N];
queue<int>Q;

void spfa(int s){
	memset(vis,0,sizeof(vis));
	for(int i=0;i<=n;i++) d[i]=-101010;
	d[s]=0;vis[s]=1;Q.push(s);
	while(!Q.empty()){
		int u=Q.front();Q.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to;//由于有0号节点，所以必须这样写，要不然错误会让你崩溃。
			if(d[u]+1>d[v]){
				d[v]=d[u]+1;
				if(!vis[v]){
					Q.push(v);vis[v]=1;
				}
			}
		}
	}
}

int main()
{
	in(n);
	for(int i=1;i<n;i++){
		int u,v,t;
		in(u);in(v);in(t);
		add(u,v);add(u,t);
	}spfa(1);
	printf("%d\n",d[0]);
	return 0;
}
```

---

## 作者：荷叶下 (赞：2)

## 蒟蒻の第一篇题解

#### update 2020/10/10 应@Qing_s要求，加了一些注释
------------
## 一道简单的BFS

### 存图时如果是草地则不存
![](https://cdn.luogu.com.cn/upload/image_hosting/bu3iv08p.png)
### 详解见代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

namespace Heyexia
{
	#define ll long long
	using std::getchar ;
	using std::putchar ; 
	using std::freopen ;
	
	using std::cin ;
	using std::cout ;
	using std::queue ;
	
	int read_() 
	{
		int s = 0 , w = 1 ;
		char ch = getchar() ;
		while( ch == ' ' || ch == '\n' )
			ch = getchar() ;
		while( ch < '0' || ch > '9' )
		{
			if( ch == '-' )
				w = -1 ;
			ch = getchar() ;
		}
		while( ch >= '0' && ch <= '9' )
		{
			s = s * 10 + ch - '0' ;
			ch = getchar() ;
		}
		return s * w ;
	} 
	void print_( int x ) 
	{
		if( x < 0 )
		{
			x = -x ;
			putchar( '-' ) ;
		}
		if( x > 9 )
			print_( x / 10 ) ;
		putchar( x % 10 + '0' ) ;
	}
	int max_( int x , int y )
	{
		return x > y ? x : y ;
	}
}
using namespace Heyexia ; //花 里 胡 哨 

struct node
{
	int from , w ;
}; //结构体存图
int n , max = -0x7fffffff ;
int mapp[2020][2020] ;
bool vis[2020] ;
queue < node > q ; 

node make_node( int x , int y )
{
	node x_ ;
	x_ .from = x ;
	x_.w = y ;
	return x_ ;
}
void bfs( int s )
{
	q.push( make_node( s , 1 ) ) ;  //等于q.push({s , 1});
	while( !q.empty() )
	{
		node x = q.front() ; q.pop() ;
		if( vis[x.from] )
			continue ;
		vis[x.from] = true ;
		max = max_( x.w , max ) ; //更新最大值 
		for( int i = 1 ; i <= n ; ++i )
		{
			if( mapp[x.from][i] )  //枚举每个点 如果能走就入队
				q.push( make_node( i , x.w + 1 ) ) ;
		}
	}
}

int main()
{
 ;
	n = read_() ;
	for( int i = 1 ; i < n ; ++i )
	{
		int x = read_() , y = read_() , z = read_() ;
		if( y != 0 )
			mapp[x][y] = true , mapp[y][x] = true ; //如果不是草地就存图 
		if( z != 0 )	
			mapp[x][z] = true , mapp[z][x] = true ;
	}
	for( int i = 1 ; i <= n ; ++i )
		bfs(i) ; //每个点bfs一遍
	print_( max ) ;
	return 0 ;
}
```
### ~~一次过~~
![](https://cdn.luogu.com.cn/upload/image_hosting/4w8ox8bi.png)

## 说句闲话 研究BFS的最好办法是
#### A了这道题
### 祝你们成功（滑稽


---

## 作者：0606x (赞：2)

### 第一次写题解 小紧张~

~~看完一楼的代码发现自己的好菜啊~~

用结构体存储数据，输入后排序（~~其实没必要，当时不知道怎么想的~~）

再翻出自己~~八二年~~的深搜基本代码，先从第一个开始找，不断递归，同时用

ans存储答案。

这题也比较简单，应该学过深搜就比较容易写出来的吧。

~~不然本蒟蒻怎么能水题解呢~~~

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct muu
{
	int a;
	int b;
	int c;
}x[1001];
int n,ans;
bool cmp(muu y,muu z)
{
	return y.a<z.a;
}
void dfs(int s,int step)
{
	if(x[s].b!=0) dfs(x[s].b,step+1);
	if(x[s].c!=0) dfs(x[s].c,step+1);
	ans=max(ans,step);
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++) cin>>x[i].a>>x[i].b>>x[i].c;
	sort(x+1,x+n,cmp);
	dfs(1,1);
	cout<<ans;
	return 0;
}
```
#### （~~审核大大辛苦啦~~）

---

## 作者：xwmwr (赞：2)

读题， Bessie实际是在一棵二叉树上行走， 出发点是一号节点。

Bessie想要走过最多的小径（边）， 也就是走过最多的节点。

包含最多节点的从树根开始的路径长度等于树高， 于是这道题可以

先建立二叉树， 再求树高。

树高的算法是这样的：

$$node(i).height = max(i.lc.height , i.rc.height) + 1$$

lc 为左孩子， rc为右孩子。

最多路径条数就是树高 - 1啦。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int lc, rc;
    int height;
}node[1001];
//以上是节点的定义， height为子树高
int p;
//p如题意
void replace(int u) {
    if(u == 0) {
        return;
    }
    
    replace(node[u].lc);
    replace(node[u].rc);
    //如以上提到的公式。
    node[u].height = max(node[node[u].lc].height, node[node[u].rc].height) + 1;
    
    return;
}

int main() {
    scanf("%d", &p);
    
    for(int i = 1; i < p; ++i) {
        int x;
        scanf("%d", &x);
        scanf("%d%d", &node[x].lc, &node[x].rc);
    }
    
    //初始化零号节点
    node[0].height = 1;
    replace(1);
    
    cout << node[1].height - 1;
    
    return 0;
}
```


---

## 作者：chlchl (赞：2)

## 题目描述及解释
[题目传送门](https://www.luogu.com.cn/problem/P2959) 

相信很多人跟我一样，看完题目后一脸懵：**这题到底在说啥？** 

遇到这种题目难懂的题目，如果有样例解释，我们可以**模拟一下样例**。将每个点及其边画出来后，发现是一棵**无根树**。对于无根树，我们可以找**任意一个点作为其根**，方便分析。结合样例输出，我们可以发现：这道题目让我们求的是**这棵树的深度**。
## 题目思路
既然是求深度，第一反应应该就是**深度优先搜索（DFS）**。 

我们先用vector把树存储下来，然后遍历它所有子结点（可以加一个变量，防止它走回头路），然后递归并将深度+1。

### 注意：输出时需把求到的答案 +1 再输出，因为还要走到牧场的草地上QAQ。

那么，经过我~~或许不清楚~~的解释，大家应该可以把代码写出来了吧！以下是参考代码。

$code:$
```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int> tree[1001];
int p, n, d, x, y, ans;

void dfs(int res, int father, int dep){//res是当前搜到的点
	ans = max(ans, dep);//更新答案
	for(int i=0;i<tree[res].size();i++){//遍历所有儿子
		int v = tree[res][i];
		if(v == father)	continue;//防止走回头路
		dfs(v, res, dep + 1);//递归求解
	}
}

int main(){
	cin >> p;
	for(int i=1;i<p;i++){
		cin >> n >> x >> y;
                //这本质上是一棵二叉树，只有左儿子和右儿子
		if(x != 0){//如果有左儿子
			tree[n].push_back(x);
			tree[x].push_back(n);
		}
		if(y != 0){//如果有右儿子
			tree[n].push_back(y);
			tree[y].push_back(n);
		}
	}
	dfs(1, -1, 0);
	cout << ans + 1 << endl;
	return 0;
}
```

好了，本人第二篇题解就写到这里了，如果有什么错误，请在评论区指出。
### 拜拜

---

## 作者：封禁用户 (赞：1)

这题虽然题目有点难懂，但做起来还是挺简单的。

首先让我来简单说一下题意。

从前有一头牛，它住的农场是一个**二叉树**，每个**叶子节点**是青青草地，它所在的牛棚是节点1，也就是根节点。其他牛棚分别为节点2至p。有一天它想要到**距离牛棚最远的草地**去吃草，问经过了多少条**边**。

------------

最先想到的应该是**暴力枚举法**。

枚举每一个**草地**，求距离，取**最大值**输出。

时间复杂度 $O(N^2)$ 。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int f[2005];//记录父亲节点（这里把草地也给编号了，所以要开两倍大小，不然会RE）

int main(){
    int p,u,v1,v2,n,x,res=0,ans=0;
    cin>>p;
    n=p;//要把草地也编号
    for(int i=1;i<=p;++i){
        cin>>u>>v1>>v2;
        if(!v1) v1=++n;
        if(!v2) v2=++n;
        f[v1]=f[v2]=u;
    }
    for(int i=p+1;i<=n;++i){//枚举草地
        //计算距离
        x=i;
        res=0;
        while(x!=1){
            x=f[x];
            ++res;
        }
        ans=max(ans,res);//取距离最大值
    }
    cout<<ans<<endl;
    return 0;
}
```
这样虽然可以过，但不够好。

------------

我们可以把**所有的边**用数组记录下来，然后用dfs计算每个节点到根节点的距离。

时间复杂度 $O(N)$ 。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int g[1010][2];//记录二叉树
int ans;//记录答案
void dfs(int x,int res){
    if(!x){//如果是草地就刷新答案
        ans=max(ans,res);
        return;
    }
    ++res;//如果不是就要加上一条边（去到左或者右儿子的）
    dfs(g[x][0],res);//左
    dfs(g[x][1],res);//右
}

int main(){
    int p,u,v1,v2;
    cin>>p;
    for(int i=1;i<=p;++i){
        cin>>u>>v1>>v2;
        g[u][0]=v1;//记录去左儿子的边
        g[u][1]=v2;//记录去右儿子的边
    }
    dfs(1,0);//dfs
    cout<<ans<<endl;
    return 0;
}
```
完结撒花~

---

## 作者：_•́へ•́╬_ (赞：1)

### 这题我用了记忆化搜索~~不过好像不用也行~~
```cpp
#include<bits/stdc++.h>
#define rpt(n) for(register int ttxyc=0;ttxyc<n;++ttxyc)//宏定义
using namespace std;
struct node
{
	int l,r;
}a[1001];
int p,ans[1001];
int dfs(int i)
{
	if(i==0)return 0;//这个是牧场，为0
	if(ans[i])return ans[i];//以前保存过答案的，不过这题似乎不用。。。删掉也行
	return ans[i]=1+max(dfs(a[i].l),dfs(a[i].r));//两个子节点取最大，+1
}
main()
{
    scanf("%d",&p);
    rpt(p-1)
    {
    	int i;
    	scanf("%d",&i);//i为父亲节点
    	scanf("%d%d",&a[i].l,&a[i].r);//读入孩子节点
	}
	printf("%d",dfs(1));//从1开始
}
```

---

## 作者：RagnaLP (赞：1)

不得不说这道题的图有点吓人，~~**但实际上很多都没有用**~~

通过题上说的“三岔路口”（对于每一个节点有三条连接，其中一条连接父节点，另外两条连接子节点）和数据，可以那些乱七八糟的路和牧场看成是一棵**二叉树**，又因为 “对任意一个节点来说，只有一条从节点1开始的路径可以到达” ，所以可以把1作为根节点。从而将题目转化为**求一棵以1为节点的二叉树的深度**。

核心算法：DFS

注意：

1.根节点的深度在此题中应该为**1**（节点1的实际意义是一个要算入答案的一个牧场）

2.有n个节点，他们之间的连接数应该为n-1

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<cmath>
typedef long long ll;
using namespace std;
struct Node{
	int id,l,r;
	Node(){
		l=r=0;
	}
}tr[1010];//保存二叉树
int p,dep[1010],ans=0;//个数，节点深度，答案（树的深度）
void addedge(int i,int r,int l){
	tr[i].id=i;
	tr[i].l=l;
	tr[i].r=r;
}//编号为i的接点的左节点l，右节点r
void Init() {
	scanf("%d",&p);
	int a,b,c;
	for(int i=1;i<p;i++){
		scanf("%d%d%d",&a,&b,&c);
		addedge(a,b,c);
	}
	dep[1]=1;//注意初始化
}
void DFS(int i){
	if(tr[i].l){//如果左节点不为0
		dep[tr[i].l]=dep[i]+1;//左节点的深度
		ans=max(ans,dep[i]+1);//更新树的深度
		DFS(tr[i].l);//接着左节点向下找
	}
	if(tr[i].r){//同理
		dep[tr[i].r]=dep[i]+1;
		ans=max(ans,dep[i]+1);
		DFS(tr[i].r);
	}
}
int main() {
	Init();
	DFS(1);
	printf("%d",ans);
	return 0;
}
```

---

