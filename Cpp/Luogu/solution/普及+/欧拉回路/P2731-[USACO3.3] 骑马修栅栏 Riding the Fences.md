# [USACO3.3] 骑马修栅栏 Riding the Fences

## 题目背景

Farmer John 每年有很多栅栏要修理。他总是骑着马穿过每一个栅栏并修复它破损的地方。

## 题目描述

John 是一个与其他农民一样懒的人。他讨厌骑马，因此从来不两次经过一个栅栏。

John 的农场上一共有 $m$ 个栅栏，每一个栅栏连接两个顶点，顶点用 $1$ 到 $500$ 标号（虽然有的农场并没有那么多个顶点）。一个顶点上至少连接 $1$ 个栅栏，没有上限。两顶点间可能有多个栅栏。所有栅栏都是连通的（也就是你可以从任意一个栅栏到达另外的所有栅栏）。John 能从任何一个顶点（即两个栅栏的交点）开始骑马，在任意一个顶点结束。

你需要求出输出骑马的路径（用路上依次经过的顶点号码表示)，使每个栅栏都恰好被经过一次。如果存在多组可行的解，按照如下方式进行输出：如果把输出的路径看成是一个 $500$ 进制的数，那么当存在多组解的情况下，输出 $500$ 进制表示法中最小的一个 （也就是输出第一位较小的，如果还有多组解，输出第二位较小的，以此类推）。

输入数据保证至少有一个解。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq m \leq 1024,1 \leq u,v \leq 500$。

题目翻译来自NOCOW。

USACO Training Section 3.3

## 样例 #1

### 输入

```
9
1 2
2 3
3 4
4 2
4 5
2 5
5 6
5 7
4 6```

### 输出

```
1
2
3
4
2
5
4
6
5
7```

# 题解

## 作者：EarthGiao (赞：327)

~~简单的开始~~ 
## 完美の开始
这里数组什么的用来干什么后面标注的清楚了

------------
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int map[10001][10001];//记录两个点之间的路径个数 
int du[10001];//辅助记录奇点 
int lu[10001];//记录路径 
int n,x,y,js=0;//输入的数据和计数器
int maxn=0;
```
------------
## 正题开始QWQ
先说思路：
很简单和一本通上的例题一笔画没什么差别就是多了一个点可能会重复出现罢了。


------------
可以按正常的输入然后存入map数组（PS：如果你用的是万能头就不要定义map数组啦，可以定义一个f数组什么的)这里就出现和一本通上一笔画的差距了，是累减，每次记录就加一而不是赋值为1
。。。。因为后面很多地方需要用到点的个数，但是却没有输入所以专门定义一个maxn来找输入的最大值就是点的个数啦

------------

注意这里要定义一个数组记录出现次数，在输入的时候每次一出现就加一然后在后面单独找，看看谁不是2的倍数记录下来结束循环

------------
```cpp
scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&x,&y);
		map[x][y]++;
		map[y][x]++;
		du[x]++;
		du[y]++;//记录出现的次数 
		maxn=max(maxn,max(x,y));
	}
	int start=1;//默认奇点是1 
	for(int i=1;i<=maxn;++i)
	{
		if(du[i]%2)//找到奇点 
		{
			start=i;//记录奇点
			break;//然后结束循环 
		}
	}
	find(start);//从奇点开始找 
	for(int i=js;i>=1;i--)
	{
		printf("%d\n",lu[i]);//挨个输出路径并且换行 
	}
	return 0;
```

------------
然后就说函数部分了，也就是上面的find函数QWQ.这里很好想的，就是模板改一下，变为0改为减一QWQ简单的我不想多说
函数代码


------------

```cpp
void find(int i)//
{
	int j;
	for(j=1;j<=maxn;++j)//而且这里不是n而是maxn因为n不是点的个数而是下面有多少行 
	{
		if(map[i][j]>=1)
		{
			map[i][j]--;//删去边一次吗避免重复 
			map[j][i]--;//z这里和一笔画不一样这里是累减而一笔画直接变成0 
			find(j);
		}
	}
	lu[++js]=i;
}
```


------------

## 话不多说完整代码

------------

```cpp
//防伪标识
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int map[10001][10001];//记录两个点之间的路径个数 
int du[10001];//辅助记录奇点 
int lu[10001];//记录路径 
int n,x,y,js=0;
int maxn=0;
void find(int i)//
{
	int j;
	for(j=1;j<=maxn;++j)//而且这里不是n而是maxn因为n不是点的个数而是下面有多少行 
	{
		if(map[i][j]>=1)
		{
			map[i][j]--;//删去边一次吗避免重复 
			map[j][i]--;//z这里和一笔画不一样这里是累减而一笔画直接变成0 
			find(j);
		}
	}
	lu[++js]=i;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&x,&y);
		map[x][y]++;
		map[y][x]++;
		du[x]++;
		du[y]++;//记录出现的次数 
		maxn=max(maxn,max(x,y));
	}
	int start=1;//默认奇点是1 
	for(int i=1;i<=maxn;++i)
	{
		if(du[i]%2)//找到奇点 
		{
			start=i;//记录奇点
			break;//然后结束循环 
		}
	}
	find(start);//从奇点开始找 
	for(int i=js;i>=1;i--)
	{
		printf("%d\n",lu[i]);//挨个输出路径并且换行 
	}
	return 0;
}
```

综上所述，已AC
# 完美の结束
（看的这么累，不点个赞再走QWQ）

---

## 作者：Mogu (赞：111)

## 作者的写作背景？
虽然大佬们讲的很好了！！但是自己在实际做的时候还是有一些奇奇怪怪的自我思考，特别是在最后两个点WA之后，倒腾了一晚上。终于发现了**正着输出**和**用栈去存路径**，最后倒着输出答案的区别！前方多图有助于大家理解，为什么这样做是对的！想看这部分的同学可直接下拉
#### ps：欧拉回路问题，有时候也叫一笔画问题

## 入手
我们看到题目，先把模型抽出来。要修栅栏，栅栏连通了两个点，得出结论，**是个无向图**，且找到一种遍历方法，**只经过每条边一次，也就是一气呵成的走完所有边！**知道的同学已经懂了，是个欧拉回路问题，不知道的给大家补充下概念。

## 概念
欧拉路：从任意一个点，走到任意一个点结束，**且每条边只通过一次**

欧拉回路：其实是欧拉路衍生出来的，起点和终点一样的欧拉路。形象的说，走一圈又回来了的路径

给大家看看最简单的模型![欧拉路和欧拉回路](https://cdn.luogu.com.cn/upload/pic/41002.png)

## 再度审题，并且进一步思考

**要遍历图，必先存图。**

我们找到的这个路径，题目要求很明了，字典序最小。

**离开数据范围的题目都是流氓**

边数 F(1 <= F <= 1024)

点 (1 <= i,j <= 500)，500

看见这么小的数据，再加上我们遍历应该要优先选序号小的点遍历。为什么优先选最小的啊？你想啊，你不贪心，你要把每条路径都遍历一遍再比吗！！！~~TLE~~

于是我们自然而然的想到，邻接矩阵存图。我们可以很快的优先选择小的遍历
```cpp
void dfs(int u){
	//请把题目的细节一遍遍读，不要想当然，
    //最小节点和最大节点我们都是不知道的，以防万一，请在读入的时候就处理完minn和maxn
    for(int v = minn; v <= maxn; v++){
       if(g[u][v]){
       	//dosomething
	   } 
    } 
}
```
至于邻接表，由于读入时的顺序不同，在遍历时的先后会不同，这里不做拓展，想不明白的同学可以先不看！当然，这题可以用邻接表来，~~但是不要为难自己~~

#### 那么真正的问题来了，怎么走才能一笔画完这个图呢？

这里就要用到欧拉路的一些性质

**先讨论无向图里**，如果一个图，存在欧拉路的话，那么这个图，一定有两个奇点（奇数点，即度为奇数的点，度就是连这个点的边的数量）。为什么是两个？

先不看起点和终点!对于中间的所有点，我们**肯定要从一条边进去**，进去之后，因为不是终点，**肯定要再出去**，所以中间的点都是偶数点。那么对于起点，我们只能出去，对于终点，我们只能进来。很愉快的证明出只有两个奇点，这样我们不仅解决了**路径的起点**，还找到了判断是否为欧拉路的方法，虽然这题不需要我们判断。
![欧拉路](https://cdn.luogu.com.cn/upload/pic/41005.png)

欧拉回路呢？简单，把上图 1-4连起来，按欧拉路的逻辑推理一下，每个点都要进一次出一次，自然所有点都是偶数点

这里关于有向图的欧拉路问题的性质也是差不多的，感兴趣的可以自己思考一下，是几乎一样的证明法。。。

### 那我们又得出了，我们应当从哪个点开始遍历
```cpp
scanf("%d",&m); //m个边
    
    int u,v;
    int minn = 666,max = 0;
    for(int i = 1; i <= m; i++){
        scanf("%d%d",&u,&v);
        g[u][v]++;
        g[v][u]++;
        dree[u]++;
        dree[v]++;
        //注意，题目没说两个点之间只有一条边，那我们就一定不能写g[u][v] = 1这种代码
        minn = min(minn,min(u,v));
        maxn = max(maxn,max(u,v));
    }

 	int s = minn; 
    for(int i = minn;i <= maxn;i++)
        if(dree[i]&1) //dree如果是奇数的话，我们从i开始搜
        {
            s = i;
            break;
        }
//欧拉回路从哪开始都可以搜，欧拉路要从奇点开始
    dfs(s);

```
### 但是！这图错综复杂，实际上不是单纯的欧拉路或者欧拉回路，而是套在一起的东西！![套娃](https://cdn.luogu.com.cn/upload/pic/41009.png)
比如这个，我们可以发现，1、2、3、4可以说是欧拉路，3、5、6又是个欧拉回路。那么，我们还可以从奇点开始搜吗？可以！

第一种，如果是欧拉回路套欧拉回路，没什么好说的都是偶点，哪里开始都可以。

第二，像上图这种欧拉路套欧拉回路的，我们可以把每个欧拉回路的部分，想象成一个点，因为**欧拉路，从起点走，一定回到终点**，大家闭上眼睛感受一下，我们完全可以把图就当成一个欧拉路

到这里就基本做完了这道题，我们在遍历的时候，把走过的路删掉，这样就不会重复走了，而且省去了反复横跳的风险
```cpp
void dfs(int u){
	//cout<<u<<endl;
    for(int v = minn; v <= maxn; v++){
       if(g[u][v]){
       		g[u][v]--;
       		g[v][u]--;
       		dfs(v);
	   } 
    }
    S.push(u);
}

while(!S.empty()){
	cout<<S.top()<<endl;
    S.pop();
}
```

## 事实上是正戏，大家注意到了吧，上面注释代码里，两种不同的输出路径的方式！

我们可以闭上眼睛感性理解一下，嗯，用数组存，或者说栈吧，然后倒序输出是对的。但是，递归开始时就直接输出，为什么不行呢？

dfs明明是纯天然无污染的栈啊！
![套娃](https://cdn.luogu.com.cn/upload/pic/41009.png)
看见了吗，这其实是题目特性导致的，或者说，基本上求问路径的题目，回溯时候记录会更加稳妥。

比如4这个节点，我们贪心的进去了，并且贪心的输出了个4，然而，我们一眼就知道，此时我们回不去了，无法走完那个欧拉回路。事实上，dfs还在继续，他最后输出
1 2 3 4 6 5 3

在回溯记录的情况下，我们也先到4，4的搜索子树已经没了，4入栈，回到3，继续往6走，5, 3，回到 2， 1

最后结果是这样的

4 3 5 6 3 2 1

倒序一下是这样

1 2 3 6 5 3 4

## 最后理性的总结
因为我们在遍历的时候，还要考虑点是否符合某个条件，在符合某个条件下我们进入了一个点，一般来说是可以直接输没错。但是这里我们的判定条件，仅仅是序号优先而已，并不保证这个是对的，是符合要求的。我们应该在搜完符合要求的点后，回溯时记录，此时这个顺序是 符合情况下的倒序。

第一次写题解还这么长QAQ，求过

---

## 作者：Misaka_Azusa (赞：66)

这个题是欧拉回路的模板题，那么在这里给出一个hierholzer的做法。

对于求欧拉回路的问题，有Fluery算法和Hierholzers算法，两种算法。

后面一种算法无论是编程复杂度还是时间复杂度好像都比前种算法复杂度更优，但前者的应用广泛性好像比后者更高。

对于Hierholzers算法，前提是假设图G存在欧拉回路，即有向图任意
点的出度和入度相同。从任意一个起始点v开始遍历，直到再次到达
点v，即寻找一个环，这会保证一定可以到达点v，因为遍历到任意一
个点u，由于其出度和入度相同，故u一定存在一条出边，所以一定可
以到达v。将此环定义为C，如果环C中存在某个点x，其有出边不在环
中，则继续以此点x开始遍历寻找环C’，将环C、C’连接起来也是一个
大环，如此往复，直到图G中所有的边均已经添加到环中。

举个例子

![](https://cdn.luogu.com.cn/upload/pic/15207.png)

在手动寻找欧拉路的时候，我们从点 4 开始，一笔划到达了点 5，形成路径 4-5-2-3-6-5。此时我们把这条路径去掉，则剩下三条边，2-4-1-2 可以一笔画出。

这两条路径在点 2 有交接处（其实点 4 也是一样的）。那么我们可以在一笔画出红色轨迹到达点 2 的时候，一笔画出黄色轨迹，再回到点 2，把剩下的红色轨迹画完。

~~既然是模板题..那么当然选择好写的~~

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;
const int maxn = 1031;
int G[maxn][maxn], du[maxn];
int n,m;
stack<int> S;//用一个栈来保存路径
void dfs(int u)
{
    for(int v=1; v<=n; v++)
        if(G[u][v])
		{
            G[u][v]--;
            G[v][u]--;
            dfs(v);    
        }
    S.push(u);
}
int main(){
   
    cin>>m;
    int u,v;
    for(int i=1; i<=m; i++){
	    cin>>u>>v;
	    n = max(n,u);
		n = max(n,v); 
        G[u][v]++;
        G[v][u]++;
        du[u]++;
        du[v]++;
    }//用邻接矩阵记录图
    int s = 1;
    for(int i=1; i<=n; i++)
        if(du[i]%2==1) 
		{	
			s=i;
			break;
	    }//寻找起点
    dfs(s);
    while(!S.empty()){
        cout<<S.top()<<endl;
        S.pop();
    }
    return 0;
}
```
在 DFS 的过程中不用恢复边，靠出栈记录路径。

---

## 作者：Froggy (赞：35)

### 一个更优秀的欧拉回路~

---

大家的欧拉回路都是 时间: $O(n^2)$ ,空间:$O(n^2)$ 的 ,其实可以优化到 时间:$O(nlogn)$, 空间$O(n)$

首先拒绝使用邻接矩阵,但由于用邻接表不好处理字典序最小的限制,所以使用  **vector** 是存图是必然选择

然后怎么让一条双向边不回走两次呢??

开个二维vis数组??这样的话空间就不是 $O(n)$ 的了QAQ

开个 **map** 就解决了吖!! ( **注:** 如果题目是单向边就不需要map啦)

其实可以加边的时候再存个编号(从$2$开始),根据开一个一位的vis数组,反向边就是 [当前边的编号^1]

不过由于vector内部的排序导致时间复杂度已经是 $O(nlogn)$ ,所以这个优化不要也无妨

*code:*

```cpp
#include<iostream>
#include<algorithm> 
#include<cstdio>
#include<map>
#include<vector>
#include<cstring>
using namespace std;
#define N 1010
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,st,du[N],m,tmp[N],ans[N<<3],top;
map<pair<int,int>,int> mp; //(u,v)
vector<int> edge[N];
void Euler(int u){
	while(1){
		while(tmp[u]<edge[u].size()&&!mp[make_pair(u,edge[u][tmp[u]])])tmp[u]++;//如果反向边被走过就不走了
		if(tmp[u]>=edge[u].size())break;
		int v=edge[u][tmp[u]];
		mp[make_pair(u,v)]--;
		mp[make_pair(v,u)]--;//标记反向边
		++tmp[u];
		Euler(v);
	}
	ans[++top]=u;
}
int main(){
	m=read();st=n=550;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		edge[u].push_back(v);
		edge[v].push_back(u);
		du[u]++,du[v]++;
		st=min(st,min(u,v));	
		mp[make_pair(u,v)]++,mp[make_pair(v,u)]++;	
	}
	for(int i=1;i<=n;++i){
		if(du[i]&1){
			st=i;
			break;
		}
	}
	for(int i=1;i<=n;i++){
		sort(edge[i].begin(),edge[i].end());//按编号从小到大排序
	}
	Euler(st);
	while(top)printf("%d\n",ans[top--]); //倒序输出
	return 0;
}

```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!


---

## 作者：逆流之时 (赞：32)

这题关于为什么不能在递归同时输出的问题很多题解都没有解释，唯一解释了的题解里面的图也挂了，所以我再来写一遍吧。  
先给出两种输出路径方法：  
错误的：
```cpp
void dfs(int x)
{
	for(int i=1;i<=n;i++)if(a[i][x])
	{
		printf("%d\n",x);
		a[i][x]--;a[x][i]--;
		dfs(i);
	}
}
int main()
{
	//……
    printf("%d",&s);//s是起点
    dfs(s);
}
```
正确的：  
```cpp
void dfs(int x)
{
	for(int i=1;i<=n;i++)if(a[i][x])
	{
		a[i][x]--;a[x][i]--;
		dfs(i);
	}
	p[size++]=x;
}
int main()
{
	//……
	dfs(s);
	for(int i=size-1;i>=0;i--)printf("%d\n",p[i]);
	return 0;
}
```
这里的关键问题就是前面所说的：为什么不能在递归的同时输出路径？  
通过下面的例子可以很清楚地看出原因：  
```cpp
4
1 3
1 4
3 4
1 2
```
图形：
```cpp
3\
| 1-2
4/
```
可以发现，当用第一种方法时，程序会首先往2号点走，然后输出1 2，但直接往2号节点走就会被卡住。而出栈记录路径的方法就能避开这一点，往2走之后栈里的顺序是2 1，走完后会按2 1 3 4 1的方式正确地输出。由于是输出栈顶，所以2号节点也会最后输出。  
那为什么出栈输出的方式适用于所有状态呢？  
分两种情况讨论：  
1.整个图是欧拉回路，递归时输出和出栈输出两种方法的效果一样，都采用的是贪心的方法遍历图。  
2.整个图是欧拉路但不是欧拉回路，这时图可以被起点分为一个欧拉回路的子图与一个欧拉路的子图。当按出栈方法遍历时，假设欧拉路是上面的会在遍历完整张图前被卡住的情况：  
如果欧拉回路的优先级低，程序会遍历完整张图才开始从最后一层函数返回，输出顺序是先欧拉回路再欧拉路；  
如果欧拉路的遍历优先级低，则会先遍历欧拉路，当被卡住时返回，此时欧拉路上的节点都在栈的最低层，然后开始遍历欧拉回路，此时欧拉回路的节点都在栈顶部，所以输出顺序仍然是正确的欧拉回路再欧拉路。  
所以，出栈的方法输出总是正确的。  
这题也提醒了我们：即使做的是模板题，也要结合自己的想法思考算法的每一个细节，这样才能真正看懂算法，也能解决自己开始时对算法的不明白处。  

最后上代码：（注释里的是错误范例）  
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[505][505];
int m,x,y,cnt[505],s=1024,n,p[1030],size;
void dfs(int x)
{
	for(int i=1;i<=n;i++)if(a[i][x])
	{
		//printf("%d\n",x);
		a[i][x]--;a[x][i]--;
		dfs(i);
	}
	p[size++]=x;
}
int main()
{
	for(scanf("%d",&m);m--;)
	{
		scanf("%d%d",&x,&y);
		a[x][y]++;a[y][x]++;//a[x][y]=a[y][x]=1;
		cnt[x]++;cnt[y]++;
		n=max(n,max(y,x));
		s=min(s,min(x,y));
	}
	for(int i=1;i<=n;i++)
		if(cnt[i]&1)
		{
			s=i;
			break;
		}
	//printf("%d\n",s);
	dfs(s);
	for(int i=size-1;i>=0;i--)printf("%d\n",p[i]);
	return 0;
}
```

---

## 作者：Adove (赞：19)

欧拉回路板子+计数就可以了，数组记得开大点，听同学说开到1025就够了





```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int g[1501][1501],du[1501],cu[1501];//一开始数组开500WA了最后一个
int n,e,ctp,i,j,x,y,st=1,m,mi,p;
void f(int i)
{
    for(int j=mi;j<=m;++j)
        if(g[i][j])
        {
            g[i][j]--;
            g[j][i]--;//要计数的，可能两点之间很多条边；
            f(j);
        }
    cu[++ctp]=i;
}
//欧拉回路板子
int main()
{
    scanf("%d",&e);
    for(i=1;i<=e;++i)
    {
        scanf("%d%d",&x,&y);
        ++g[y][x];
        ++g[x][y];
        du[x]++;
        du[y]++;//欧拉回路的统计环节
        m=max(m,x);
        m=max(m,y);
        mi=min(mi,x);
        mi=min(mi,y);
}
//我怕数据不从1开始就统计了最大和最小QAQ，但貌似只需要统计最大值就好了
    for(i=mi;i<=m;++i)
        if(du[i]%2)
            {
                st=i;
                break;
}
//找到最小的奇点就跳出循环并开始搜索
    f(st);
    for(i=ctp;i>=1;--i)//记得反序输出
        printf("%d\n",cu[i]);
    return 0;
}
```

---

## 作者：任梦华 (赞：16)

```cpp
/*
	本蒟蒻的欧拉路径做法，请大家看完别喷
	本人能力还有待提高
	谢谢
	仔细看过题目的人会发现本题目其实并不是很难 
	要注意的是每一条边都要走一次（只有一次，而每个点可以重复走） 
	我们可以用欧拉路的方法做（欧拉路指遍历图的每一条边，不懂人可以上网查一下欧拉路）
	然后一个难点是要以排序最小输出 
	其实我们可以找到一个最小的起点（0个度为奇数找最小（欧拉回路），2个度为奇数找最小的一个奇数点（欧拉路）） 
*/
#include<bits/stdc++.h>//蒟蒻的万能头文件 
using namespace std;
int n;
int g[1010][1010];//记录g的俩个下标的关系 
int du[100000];//记录下标的度 
int ans[100000];//记录答案 
int ss;
int s=1000000,d=1000000;
void find(int x)
{
    for(int i=1;i<=500;i++)//因为排序要最小 ，所以从小往大找 
    if(g[x][i])//如果有路就走，因为数据保证有解所以不用回溯等判断 
    {
        g[x][i]--;//x,i之间少了一条路 
        g[i][x]--;
        find(i);
    }
    ans[ss--]=x;//当我们找完所有路再存入数组 
}
int main()
{
    cin>>n;
    ss=n+1;//输出f+1行 
    for(int i=1;i<=n;i++)
    {
        int a,b;
        cin>>a>>b;//a,b连接 
        g[a][b]++;//表示a，b的连接关系（a,b之间可能不止一条边） 
        g[b][a]++;
        du[a]++;
        du[b]++;//度也变大 
        s=min(s,min(a,b));//找回路情况的最小 
    }
    for(int i=1;i<=500;i++)
    if(du[i]&1)//位运算做法，比正常做法快一些，相当于du[i]%2==1。 
    {
        d=min(i,d);//找是否有奇数点，并找其中最小 
    }
    if(d<1000000)//如果d变了为非回路 
    { 
        find(d);
    } 
	else//为回路 
    { 
		find(s);
    } 
	for(int i=1;i<=n+1;i++)
        cout<<ans[i]<<endl;
    /*
	这是本人第一次提交题解
	如有不到位的地方请多多包涵
	再次谢谢您耐心的看完本蒟蒻的题解 
	*/ 
}
```

---

## 作者：Sooke (赞：12)

没有人使用 STL 中的 vector，那么我补一发。

既然是找欧拉回路（下面的大佬们已经说的很清楚了，如果还不够懂问度娘是个好选择）。输入每条边的时候，我们刚好可以用 vector 来储存每一个点能到达的其他点，这样做的好处主要有以下三点：

- 1 . 显然，我们不需要再用一个数组来储存每个点的出入度，直接用 vector.size() 即可。在寻找 欧拉回路 的起点时，我们扫一遍每个顶点的 vector，先找 size 为奇数的开始遍历，如果没有则找 size 大于 1 的（谁知道第 1 个点在数据中存不存在呢……）。

- 2 . 我们可以使用 r [ i ] [ j ] 表示点 i 到点 j 连接了多少边，如果我们在递归的过程中，用 for 循环从第 1 个顶点到第 n 个顶点寻找点 i 可以到达的点，未免有点慢，刚好，我们已经把点 i 所能到达的所有点储存在对应的 vector 中，先用 for 循环尝试 vector 中的每一个元素，再判断 r [ i ] [ j ]，可以节省一些不必要的复杂度。

- 3 . 由于输出要按题目所要求的排列，因此我们可以用 vector 的迭代器来给每一个顶点的 vector 排序，以找到最优答案。

不多说了，主要部分还是效仿楼下各位大佬的，本人只是加了个 vector 优化了而已：

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

vector < int > V[501]; // vector 数组，每一个顶点对应每一个 vector 
int n , m = 0 , x , y , r[501][501] , ans[1080] , f = 0 , l = 0;

void NextStep(int p){
    for(int i = 0 ; i < V[p].size() ; i++)
        if(r[p][V[p][i]] > 0){
            r[p][V[p][i]]-- , r[V[p][i]][p]--;
            NextStep(V[p][i]);
        }
    ans[++l] = p; // 记录目前答案 
}

int main(){
    scanf("%d" , &n);
    for(int i = 1 ; i <= n ; i++)
        scanf("%d%d" , &x , &y) , V[x].push_back(y) , V[y].push_back(x),
        m = max(m , max(x , y)) , r[x][y]++ , r[y][x]++; // 连边 
    for(int i = 1 ; i <= m ; i++)
        sort(V[i].begin() , V[i].end()); // 运用迭代器给每一个顶点的 vector 进行排序 
    for(int i = 1 ; i <= m ; i++)
        if(V[i].size() % 2){
            NextStep(i) , f = 1; // 寻找可能存在的第一个奇数点 
            break;
        }
    if(!f) // 如果不存在奇数点，寻找第一个有效点 
    for(int i = 1 ; i <= m ; i++)
        if(V[i].size()){
            NextStep(i);
            break;
        }
    for(int i = l ; i >= 1 ; i--)
        printf("%d\n" , ans[i]); // 输出最优答案 
    return 0;
}
```

---

## 作者：Konnyaku_LXZ (赞：6)

### 简述题意
  给你F条边，叫你输出一种路径，使得该路径恰好经过每条边一次，并且路径的字典序最小。

这很明显是个欧拉路的题了，要想解决这道题，我们得先来了解一下欧拉路。
## 什么是欧拉路
在一幅图中，**恰好**经过每条边**一次**的路径叫做欧拉路。
## 什么是欧拉回路
如果一条欧拉路的**起点与终点相同**，我们就称这条路为欧拉回路。
## 欧拉路有什么性质
不难得出，一幅图如果存在欧拉路，则一定**除起点和终点外**，所有结点的**度都为偶数**，因为这些节点进来一遍，就一定会出去一遍，而起点只出不进，终点只进不出。
## 欧拉回路有什么性质
欧拉回路**所有结点**的**度都为偶数**。因为欧拉回路要求起点必须同时也是终点，所以对于任意的一点，都是进来一遍又出去一遍，度一定为偶数。
### 思路分析
知道了这些性质之后，我们该如何去解题呢？

不难得出，一幅图如果存在**欧拉路**，则欧拉路的起点一定是**度数为奇数的点**，我们管这类点叫做**奇点**。而如果存在**欧拉回路**，则起点可以为**任意点**，因为题目要求字典序最小，所以起点为**1号结点**。

所以我们现在要做的就是找到这个起点，然后进行一遍 $dfs$ 就行了。

如何找起点呢？

我们令 $e_i$ 表示结点i的度，则每次读入一条从结点 $u$ 到结点 $v$ 的栅栏， $e_u$++ ， $e_v$++。读完所有栅栏之后，遍历一遍所有的结点，若 $e_i$%2==1，则返回结点 $i$ 即为起点，若未找到一个满足条件的 $e_i$ ，则返回结点1为起点。

最后 $dfs$ 一遍，记录路径，输出即可。

**注意：该题有重边**

### AC代码如下：
	#include<iostream>
	#include<cstdio>
	#include<cstring>
	using namespace std;
	int farm[550][550];//farm[i][j]表示i到j之间有几条边 
	int e[550];//e[i]表示i结点的度 
	int out[1050],h=0;//out记录输出序列，h为out的下标 
	int maxn=0;//最大结点，因输入中未告知，所以要自己找 
	int f;//栅栏数 
	int find_ji(){//找奇点 
	for(int i=1;i<=maxn;i++)
		if(e[i]%2==1)
			return i;
	return 1;//没有则返回1 
	}
	void dfs(int now){
		for(int i=1;i<=maxn;i++)
			if(farm[now][i]){
				farm[now][i]--;//走过一条边 
				farm[i][now]--;
				dfs(i);//继续递归i结点 
			}
		out[++h]=now;//记录输出序列 
	}
	int main()
	{
		memset(farm,false,sizeof(farm));
		memset(e,0,sizeof(e));
		scanf("%d",&f);
		int a,b;
		for(int i=1;i<=f;i++){
			scanf("%d%d",&a,&b);
			farm[a][b]++;//a和b之间的边数++ 
			farm[b][a]++;
			e[a]++;//a，b的度++ 
			e[b]++;
			maxn=max(maxn,max(a,b));//找最大结点 
		}
		int ji=find_ji();
		dfs(ji);//从奇点开始 
		for(int i=h;i>=1;i--)//因为我们是倒序记录路径的，所以要倒序输出 
			printf("%d\n",out[i]);
		return 0;
	}

---

## 作者：lxzy_ (赞：6)

## ~~第一次写绿题题解，各位大佬见谅QwQ~~

---

$\color{blue}\text{蒟蒻先来说说欧拉回路：}$

~~以下废话极多，巨佬们可以跳过~~

欧拉回路，是~~窝们伟大的~~欧拉巨佬在$1736$年发现的一个很有趣的东西。

在东普鲁士哥尼斯堡，有一条大河，河中有两个小岛。全城被大河分割成四块陆地，河上架有七座桥，把四块陆地联系起来，见以下~~抽象~~图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fsx0obkl.png)

这时候人们就想：“能否从某地出发，不重不漏地走过每一座桥梁后回到原点呢？”

欧拉在经过几番思索，将七桥转化为下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/aq65tiw6.png)

进而把问题转化为：

> 能否笔不离开纸，一口气画成整个图形，且一条线段只能经过一次。

显然是不可能的。

## 为什么？


> ~~即得易见平凡，仿照上例显然，留作习题答案略，读者自证不难~~


因为，对于一个不是终点也不是起点的点来讲，我们从一条路走到它时，必须由另外一条路走出去：

![](https://cdn.luogu.com.cn/upload/image_hosting/a3t5mnsa.png)

对于点B，窝们从A进入B后，必须有一条与之对应的路，以便走出B。每经过一次B，就要出去一次。**所以，与B(这里代指所有非起点和终点的点)连接的线段数必须为偶数。**

回到七桥问题，窝们可以看到，途中每一个点都是有奇数条线段相连，因此走进一个点就出不来了，所以七桥问题最终答案是：不能。

---

于是乎，窝们所学习的OI知识内，多了一个名词：

## 欧拉回路

而满足欧拉回路的图有如下要求：

1. 连通。~~废话~~
2. 所有点的度(就是与这个点相连的线段的总数)都为偶数。

更多关于欧拉回路的知识请

[点这里](https://www.cnblogs.com/abc1604831024/p/9077112.html)

[或这里](https://baijiahao.baidu.com/s?id=1594654125138224284&wfr=spider&for=pc)

---

好的，再让窝们康康题面，有这么一句话：

 他讨厌骑马，**因此从来不两次经过一个栅栏**。你必须编一个程序，读入栅栏网络的描述，并计算出一条修栅栏的路径，**使每个栅栏都恰好被经过一次**。


~~很显然，这是一道欧拉回路的题目。~~

---

解决欧拉回路，有$Fluery$和$Hierholzer$算法，由于~~窝不会Fluery算法~~$Hierholzer$算法使用更加广泛，所以窝们就用$Hierholzer$吧。

$Hierholzer$，说通俗一点就是深搜，先找好起点，然后对于每一个经过的点，遍历它所有可以到达的点，然后一点点枚举，待到回溯的时候，将经过的点记录下来即可。这里重点说说找起点。

找起点其实不难，上面说过，**所有非起点&终点的点的度都必须是偶数**，又因为题目说必定有解，所以**窝们只需找到度为奇数的点即可**。

那万一全部点都是偶数呢？

~~反之亦然同理，推论自然成立~~

**那我们就找一个编号最小的点呗**，因为只要所有点的度都为偶数，那么我们从任何一个出发都有解。而题目说让我们找一个$500$进制表示法最小的一个（其实就是字典序最小的一个，~~不过出题人为了装|3，写的很玄乎~~），那肯定就是找编号最小的点嘛。QwQ

---

说了这么多，上代码吧。。。

```cpp
#include<cstdio>
#include<iomanip>
#include<stack>
using namespace std;
const int N=1301;

int G[N][N];
int a[N];
stack<int> s;//定义储存答案的栈，由于我们在回溯的时候存的答案，因此所储存的答案是反着的，在最后我们将其倒过来输出
int m,x,y;
int mine=0x7f7f7f7f;//定义编号最小的起点

void hierholzer(int u)
{
    for(int i=1;i<=500;i++)//枚举编号1——500的农场
    {
        if(G[u][i])//如果编号为i的农场与编号为u的农场相连通
        {
            G[u][i]--;//标记这条路走过了
            G[i][u]--;
            
            hierholzer(i);//继续 深搜（划掉）hierholzer
        }
    }
    s.push(u);//回溯时把当前点加进栈
}
int main()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		G[x][y]++;//由于可能会有重边，窝们采用++的方式而不是=1的方式
        G[y][x]++;
        
        a[x]++;//储存每个点的度
        a[y]++;
        
        mine=min(mine,min(x,y));//由于出题人毒瘤（划掉），编号最小的不一定是1，窝们就得找到编号最小的那个点
    }
    
    int st=mine;//查找度为奇数且编号最小的点
    for(int i=1;i<=500;i++)
    {
    	if(a[i]%2==1)//如果当前点的度为奇数
    	{
    		st=i;//赋值完不用再找了，退出
			break;
		}
	}
	hierholzer(st);//开始 深搜（划掉）hierholzer算法
    
    while(!s.empty())//倒着输出
    {
    	printf("%d\n",s.top());
        s.pop();
    }
    return 0;
}
```

---

PS:代码可能会和一些大佬的雷同，纯属巧合。~~毕竟这题hierholzer就这么一种写法。。。~~

# 完结（撒花）\(^o^)/~

---

## 作者：mjc24268 (赞：5)

来简单介绍一下欧拉回路与欧拉路径

1.在一个图中，能从一个点出发，走完所有的边，并且每条边只能走一次，最后回到出发点，这样的路径就叫做欧拉回路，有欧拉回路的路径就叫欧拉图。
在欧拉图中，所有点连接的边都为偶数条。

2.在一个图中，能从一个点出发，走完所有的边，并且每条边只能走一次，这样的路径就叫做欧拉路径（不一定回到起点），有欧拉路径的路径就叫半欧拉图。
在半欧拉图中，有两个点连接的边数为奇数条边（这两个点是路径的起点和终点），其余所有点连接的边都为偶数条。

3.
在题目中，往往需要你判断到底是求欧拉路还是欧拉回路，这时候，你就需要记录下每个点连的边的数量（例如下面代码中的b数组），从而确定dfs的起点。如果所有的点连接的边都是偶数，就可以设置起点为1.

4.求欧拉路径的主要思路是dfs,也可以用栈优化dfs,dfs部分还是比较简单的。不过有一个需要注意的地方就是，在存图和搜索的时候，存入边和删除边都是**双向的**。

5.本蒟蒻在做欧拉函数的模板题中遇到了一个问题，这个输出的路径必须是按字典序从小到大排列，~~但是蒟蒻的我并不会用栈~~，所以我想到了一个方法

例如在一个三个点的环中 我们的程序默认输出 1321
这个输出的原因应该很好理解 就是 我们在循环过程中 是从1到n 的 所以最后输出的是n，所以我开始思考可不可以把循环变成n到1。
经过测试发现输出确实变成了1231，但是在遇上更强的数据时还是会出现一些问题。

```cpp
int f( long i)
{
	int j;
	for (j=500; j>=1; j--)//这是改动过的地方
	if (a[i][j]==1) 
	{
		a[i][j]=0;
		a[j][i]=0;
		f(j);
	}
		s=s+1;
		c[s]=i;
	
}
```
6.
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int f(long i);
int a[1000][1000],b[1000],c[1000],n,m,s=0,t,i,j,y,z;;
int main ()
{
	cin>>n>>m;
	for (i=1; i<=1000; i++)
	  for (j=1; j<=1000; j++)
	  a[i][j]=0;
	for (i=1; i<=m; i++)
	{
		cin>>y>>z;
		a[y][z]=1;
		a[z][y]=1;
		b[y]++;
		b[z]++;
    }
	t=1;
	for (i=1; i<=n; i++)
	{
			if (b[i]%2==1) t=i; 	}
	f(t);
	for (i=1; i<=s; i++)
		cout<<c[i]<<" ";
}
int f( long i)
{
	int j;
	for (j=1; j<=1000; j++)
	if (a[i][j]==1) 
	{
		a[i][j]=0;
		a[j][i]=0;
		f(j);
	}
		s=s+1;
		c[s]=i;
	
}


```

---

## 作者：封禁用户 (赞：5)

这就是一道~~很水~~的一笔划问题

```
//P2731
#include<bits/stdc++.h>//懒人最爱，大家别学 
using namespace std;
int e[510][510],ot[510],m,n,u,v,st[60000],top=0;
```

函数部分：

```
int dfs(int u){
    for(int i=1;i<=n;i++){
        if(e[u][i]){//判断 
            e[u][i]--;
            e[i][u]--;
            dfs(i);
        }
    }
    st[++top]=u;
    return 0;
}
```

主函数

```
int main(){
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>v;//读入 
        ot[u]++;
		ot[v]++;
        if(u>n)n=u;
		if(v>n)n=v;
        e[u][v]++;
		e[v][u]++;
    }
    bool flag=0;
    for(int i=1;i<=n;i++){
    	if((ot[i]&1)==1){
		    dfs(i);
			flag=1;
			break;
		}
	}
    if(!flag)dfs(1);
    while(top)cout<<st[top--]<<endl;//输出
	return 0;//完美结束 
}
```

谢谢观看

蒟蒻的题解，如果有任何问题，欢迎提出，看不懂的就看看别人的吧

---

## 作者：34ytw8ew7ft (赞：3)

## 前置技能
在解释这道题前，我认为有必要解释一下欧拉回路和欧拉通路是什么。
### 背景
在18世纪，哥尼斯堡的一个公园里，有七座桥将普雷格尔河中两个岛及岛与河岸连接起来(如图)。问是否可能从这四块陆地中任一块出发，恰好通过每座桥一次，再回到起点？  
![1](https://cdn.luogu.com.cn/upload/pic/57092.png)  
### 证明
这个问题是不可能实现的，我们先把这个地图抽象成一个无向图：  
![2](https://cdn.luogu.com.cn/upload/pic/57095.png)  
除了起点以外，每一次当由一条边进入一个点时，同时也由另一条边离开此点。所以每行经一点时，计算两条边，从起点离开的边与最后回到始点的边亦计算两条，**因此每一个点的度必为偶数。**  然而在这个图里，每个点的度均为奇数，所以无法实现。  
这是当时的大数学家欧拉给出的证明，为了纪念他，我们把**可以从一个点开始遍历，每条边只经过一次且能回到终点的图叫做欧拉回路，可以从一个点开始遍历，每条边只经过一次但不能回到终点的图叫做欧拉通路。**
### 判定
首先，这个图必须是**联通的！**  

欧拉回路：
- 一个所有结点的度都是偶数的无向图。
- 一个所有结点的入度等于出度的有向图。 

欧拉通路:
- 一个有且仅有两个节点的度是奇数的无向图，这两个点可以分别作起点与终点。
- 一个有且仅有两个点，其入度不等于出度，其中一个入度比出度大1，为路径的起点；另外一个出度比入度大1，为路径的终点的有向图。  

掌握了这些，做出这道题就没问题了。
## 做法
提前说一句，我用矩阵存的。
### 读题+解析
题目中总会有很多关键信息~

> 所有栅栏都是连通的(也就是你可以从任意一个栅栏到达另外的所有栅栏)

这个图是连通无向图。

> 输入数据保证至少有一个解。  

这说明我们不用判定这个图是欧拉图。

> John能从任何一个顶点(即两个栅栏的交点)开始骑马，在任意一个顶点结束。

这说明这个图可能是欧拉回路，也可能是欧拉通路，需要写一个判定的算法。  
因为数据范围比较小，像我这种蒟蒻就直接遍历，找奇数点，找到一个就改值，跳出，代码如下：
```cpp
//专门有一个数组是存每个点的度的
void find_start()
{
    for(int i=1;i<=500;i++)//暴力出奇迹
        if(du[i]%2==1)//找到了一个奇数点
        {
                start=i;//改值
                return;//跳出
        }
}
```



>你的程序必须输出骑马的路径(用路上依次经过的顶点号码表示)。我们如果把输出的路径看成是一个500进制的数，那么当存在多组解的情况下，输出500进制表示法中最小的一个 (也就是输出第一位较小的，如果还有多组解，输出第二位较小的，等等)。   

我们要输出骑马的路径……等等，这个五百进制表示法是什么鬼呀！  
理解简单一点：输出路径编号最小的一个。  

至于为什么要提五百进制表示法，~~因为这样在算法标签中就能加一个  _进制_  tag啊(滑稽）~~  

那么这个要求如何去实现呢？咱们分类讨论。  

如果是欧拉回路的话，由于我这里的遍历方式是dfs，只要从第一个点可以保证是最小的，那么路径序号必然是最小的。如果是欧拉通路的话，我们用遍历的方式，能保证第一个找到的点就是最小的。  

### 代码
下面就是代码啦，题目中会有一些坑，在代码里面也会给出注释。
```cpp
#include <bits/stdc++.h>
using namespace std;

int f;
int G[510][510];//存图
int du[510];//存点的度
int start;//存起点
int minnum=0x3f3f3f3f;
stack<int> ans;
//由于我们输出要求是正序输出，
//我个人比较喜欢用栈，方便点。
//当然数组的时空复杂度更为优秀，但是在这道题中可以忽视。

void dfs(int n)//裸dfs
{
    for(int i=1;i<=500;i++)
    {
        if(G[n][i])
        {
            G[n][i]--;
            G[i][n]--;
            dfs(i);
        }
    }
    ans.push(n);//找到就加栈
}

void find_start()//找起点
{
    for(int i=1;i<=500;i++)//直接遍历
        if(du[i]%2==1)//找到一个奇数点
        {
                start=i;//赋值
                return;//跳出
        }
}

int main()
{
    cin>>f;//常规读入
    for(int i=0;i<f;i++)
    {
        int a,b;
        cin>>a>>b;
        G[a][b]++;
        G[b][a]++;
        minnum=min(minnum,min(a,b));
  		//这里是唯一一个能算上坑的点
  		//题目并没有保证最小的标号是1
  		//所以要加个找最小值的判定
        du[a]++;
        du[b]++;
    }
    find_start();
    if(start==0)
        dfs(minnum);
    else
        dfs(start);
        
    while(!ans.empty())//输出
    {
        cout<<ans.top()<<endl;
        ans.pop();
    }
    return 0;		
}
```


---

## 作者：灵乌路空 (赞：3)

##### //这个题目比较特殊,与一本通例题一笔画大概有这些不同： 

------------

##### //首先，一条路径可能会出现多次

------------

##### //其次，输出答案的顺序 是按照节点编号排序，不是一笔画的奇怪顺序XD 

------------

##### //虽然是一笔画模板题,但是要做一些改动



------------

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int map[1110][1110];//存某两个点之间有的路径数 
int ans[1100];//存答案的数组 
int oe[1100];//储存每个节点的路径的数, 用来计算奇点 
int bian[1100];//存输入的各个节点 
bool hao[1100];//用来判断某数是否存在,用来放止bian数组存下重复的节点 
int num,num1;//存ans的元素数量  和  输入节点的数量 
int n,m;
void dfs(int i)//以i节点为起点搜索 
{
	for(int j=1;j<=num1;j++)//在num1个节点中找 
	  {
	  	if(map[i][bian[j]] > 0)//如果i与bian[j]之间还有路 
	  	  {
			map[i][bian[j]]-=1;//路径数减一 
			map[bian[j]][i]-=1;//反向路径也减一 
	  	  	dfs(bian[j]);//以新的节点为起点,开始搜 
		  }
	  }
	ans[++num]=i;//跳出循环后,给ans赋值 
}
int main()
{
	scanf("%d",&n);
	int x,y;
	for(int i=1;i<=n;i++)//完美潇洒の输入 
	  {
	  	cin>>x>>y; 
	  	if(!hao[x])//如果x之前没有出现 
		  bian[++num1]=x;//就把他放到bian数组里 
	  	if(!hao[y])//如果y之前没有出现 
		  bian[++num1]=y;//同上,扔进去 
	  	hao[x]=hao[y]=1;//把hao数组置一,表示x,y出现过 
	  	map[x][y]++;//x,y之间,正向反向的路径数都+1; 
		map[y][x]++;
	  	oe[x]++;//与x相连的边加一 
	  	oe[y]++;//同上 
	  }
	sort(bian+1,bian+num1+1);//对bian数组中节点进行升序排序,来找到题目要求的,编号最小的起点. 
	int start=1;//dfs的起点 
	int joe=0;//辅助找到第一个偶点的变量 
	for(int i=1;i<=num1;i++)//找num1个节点 
	  { 
	    if(oe[bian[i]]%2 == 1)//若能找到第一个奇点 
	      {
	        start=bian[i];
	        break;//停下来 
		  }
		if(oe[bian[i]]%2==0 && joe++==0)//找到第一个偶点,并不继续找偶点 
		  start=bian[i];
	  }
	dfs(start);//以找到的点为起点,开始搜 
	for(int j=num;j>=1;j--)
	  printf("%d\n",ans[j]);//因为dfs递归中反向赋值,起点在最后,所以要再反向输出来 
	printf("\n");
	return 0;//完美潇洒の结束 
}


---

## 作者：Mr_浓氨 (赞：3)

这道题是一道欧拉路径题，什么是欧拉路径呢，简单来说就是一笔画

欧拉路就是从一个顶点出发，不重复的经过每一条路径的一条路，而欧拉回路

就是起点与终点重合的欧拉路，这道题其实就是一笔画，可以走重复的路。

欧拉回路存在的条件是全部都是偶数点，而欧拉路就是只有两个奇数点。

所以，其实一个深搜就行了，只是要把经过的路删掉。

代码奉上

```
#include<bits/stdc++.h>
using namespace std;
int a[1025][1025],b[1025],c[1025];
int n,m,s;
void dfs(int i)//欧拉路的主要代码
{
    for(int j=1;j<=500;j++)
        if(a[i][j]>0)
            a[i][j]--,a[j][i]--,dfs(j);
    s++,c[s]=i;
}
int main()//开始了主程序
{
    cin>>m;
    memset(a,0,sizeof(a));//要养成初始化的好习惯
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        a[x][y]++;
        a[y][x]++;
        b[x]++;
        b[y]++;//奇特的输入——后面是判断奇数点偶数点的
    }
    int t=1;
    for(int i=1;i<=500;i++)
        if(b[i]%2==1)
        {
            t=i;//从奇数点开始
            break;
        }
    dfs(t);//欧拉来了
    for(int i=s;i>=1;i--)
        cout<<c[i]<<endl;//美妙的换行输出
    return 0;
}

```

---

## 作者：zhjshell (赞：3)

我来发一个用STL的multiset求欧拉回路的解法。

1、用multiset来保存邻接表，multiset是已经排好序的，begin总是指向当前邻接的最小编号的顶点。访问完的边在邻接表中删除，当empty时该顶点的边所连接的边已访问完毕，保存到输出stack。

2、用stack来保存顶点的输出。

在访问中，没有多余的判断。

```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int> g[501];  //邻接表 
stack<int> ans;        //ans保存输出 
int n,mi=501,mx=0;     //mi,mx分别记录最小和最大的顶点编号 
void dfs(int u){       //dfs方式访问图 
  while(!g[u].empty()){   //该节点有边相连 
      int v=*g[u].begin();      //下一个顶点 
      g[u].erase(g[u].begin()); //访问过的边删掉 
      g[v].erase(g[v].find(u));
      dfs(v);
  }
  ans.push(u);                  //访问完记录输出 
}
int main(){
  cin>>n;
  for(int i=1;i<=n;i++){
      int x,y;                 //边的两个顶点  
      cin>>x>>y;
      g[x].insert(y);          //添加到邻接表 
      g[y].insert(x);
      mi=min(mi,min(x,y));
      mx=max(mx,max(x,y));
  }
  int p=mi;                  //最小的顶点 
  for(int i=mi;i<=mx;i++)
    if(g[i].size()%2) {p=i;break;}  //最小的度数为奇的顶点 
  dfs(p);                           //找欧拉路径 
  while(!ans.empty()) cout<<ans.top()<<endl,ans.pop();  //输出路径 
  return 0;
}

```

---

## 作者：小燚狼 (赞：2)


一个欧拉路径的模板题，如果有两个奇点的话就是欧拉路，0个就是欧拉回路

用深搜遍历即可

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,h[1025][1025],d[1025],c[1026],cnt;
void xx(int x)
{
	for(int i=1;i<=500;i++)
	if(h[x][i])//表示x-i有路 
	{
		h[x][i]--;//将这条路删除，以免重复 
		h[i][x]--;//同上 
		xx(i);//递归查找 
	}
	c[++cnt]=x;//存值 
}
int main()
{
	cin>>n;//n条相邻的边 
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;//a,b相邻 
		h[a][b]++;//表示a-b的路的条数 
		h[b][a]++;//同上 
		d[a]++;//算出每个点的度 
		d[b]++;//同上 
	}
	int z=1;//初始值为1，因为可能是欧拉回路，没有奇点，所以可以从任何地方开始搜索 
	for(int i=1;i<=500;i++)//因为最多只有500个顶点 
	if(d[i]%2==1)
	{
		z=i;
		break;//如果这个点的度为奇数的话，那他就是奇点，找到一个就可以结束了 
	}
	xx(z);
	for(int i=n+1;i>=1;i--)//n条边相邻，所以有n+1个点
	//因为是从起点开始，递归查找，所以前面找到的实际上是后面的，所以倒着输出 
	cout<<c[i]<<endl;
} 
```

---

## 作者：「QQ红包」 (赞：2)

题解by：redbag

原题解地址：http://redbag.duapp.com/?p=1458

若有错误/描述得不清楚的地方欢迎指出。

欧拉回路模板题。


关于是否存在欧拉回路：


无向图：一个点的度数（连的边的条数）如果为奇数，那么这个点为奇点。一个连通的无向图，若有0个或者2个奇点，则存在欧拉回路。如果是0个奇点，从任意一个点出发都能回到该点。如果是2个奇点，从其中一个奇点出发能够到达另一个奇点。


有向图：0个或者2个点出度不等于入度的，即存在欧拉回路。


话说只有一个点出度不等于入度的图是画不出来的。设出边为n，所以入边为n。即出边条数等于入边条数。若其他点的出度均等于入度，那么该点的出度也只可能为入度。


框架：

```cpp
void euler(int u)
{
    for(int i=1;i<=n;i++)
    if (a[u][i]>0)//还有边
    {
        printf("%d %d\n",u,i);
        //打印顺序如果是逆序的则改成将u,i压入栈。
        a[u][i]--;//没走的边的条数-1
        a[i][u]--;//有向图的话就不要这一句
        euler(i);
    }
}
```
扯回这题。两顶点间可能有多个栅栏，于是我们就要统计2个点之间的栅栏条数（好坑啊）。注意：输出的话是输出最小的。然后打印的时候注意一点就好了。

```cpp
/*
ID: ylx14274
PROG: fence
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int m,n,u,v,k;
int i,j;
int a[501][501];//存边的
int s[501];
stack<int> t;
void euler(int u)
{
    int v;
    for (v=1;v<=n;v++)
        if (a[u][v]>=1)//有没搜过的边 
        {
            a[u][v]--;//标记 
            a[v][u]--;//双向边就都要标记
            euler(v);//继续搜 
        } 
    t.push(u);//压入栈中
    return; 
} 
int main() 
{
    freopen("fence.in","r",stdin);
    freopen("fence.out","w",stdout); 
    scanf("%d\n",&m);
    for (i=1;i<=m;i++)//读入边
    {
         scanf("%d%d",&u,&v);
         a[u][v]++;//加边条数 
         a[v][u]++;//这是双向边
         s[u]++;//存边的条数的，用来确定起点的。 
         s[v]++;
         n=max(n,u);
         n=max(n,v);//n:节点数
    }
    k=0;//标记
    for (i=1;i<=n;i++)
        if (s[i]%2==1)//最小的奇点 
        {
            k=i;//标记 
            break;//跳出 
        }
    if (k==0)//如果没奇点
    {
        for (i=1;i<=n;i++)
        if (s[i]>0)//找到最小的有边的点 
        {
            k=i;//标记 
            break;//跳出 
        }
    } 
    euler(k);//从k点开始求 
    do
    {
        printf("%d\n",t.top());
        t.pop();
    } while (!t.empty());//倒着输出
    return 0;
}
```

---

## 作者：JasonZRY (赞：1)

# 这是一道用欧拉回路就能A的一笔画问题

样例的图如下

![](https://cdn.luogu.com.cn/upload/pic/75043.png)

下面是一种合适的走法

![](https://cdn.luogu.com.cn/upload/pic/75044.png)

# 我们都知道，一幅图如果想要一笔画，奇点数必须为0或者2，而且一幅图不可能有奇数个奇点。

如果不懂奇点是什么东东的看下面：

奇点是指只有奇数条边与其相连的点

![](https://cdn.luogu.com.cn/upload/pic/75047.png)

图中，1和3是奇点，但2和4却不是

我们只要找到一个合适的点，然后往下深搜，并用一个类似栈的数组来存图，并再开一个数组存边，这道题就基本解决了

下面就剩下代码问题了

```
#include<bits/stdc++.h>
using namespace std;
int e[510][510]/*存边*/,ot[510]/*表示每个点是奇点还是偶点*/,m,n,st[60000]/*用法跟栈类似的数组*/,top,u,v;
bool flag=0;
int dfs(int u){
    for(int i=1;i<=n;i++){
        if(e[u][i]){
            e[u][i]--;                          //去除u和i之间的一条边 
            e[i][u]--;                          //同上 
            dfs(i);                             //继续搜 
        }
    }
    st[++top]=u;                                //把u存入栈 
    return 0;
}
int main(){
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        ot[u]++;                                //点u的边数+1 
		ot[v]++;                                //同上 
        if(u>n)n=u;                             //如果u比n大则说明u现在为最大点，总点数就是u，所以要把点数n赋值为u 
		if(v>n)n=v;                             //同上 
        e[u][v]++;                              //u和v之间有一条边 
		e[v][u]++;                              //同上 
    }
    for(int i=1;i<=n;i++){
    	if((ot[i]&1)==1){
	        dfs(i);                             //如果这是一个奇点就开始从第i个点开始搜索
		    flag=1;                             //标记为已搜 
		    break;
	    }
	}
    if(!flag)dfs(1);                            //如果没搜过就从1开始搜 
    while(top)cout<<st[top--]<<endl;            //把每个点的经过次数从栈里输出 
    return 0;
}
```

---

## 作者：Tanktt (赞：0)

这道题在题面中就已经告诉我们算法了：“并计算出一条修栅栏的路径，使每个栅栏都恰好被经过一次。”即欧拉回路，而且是模板题。只是有几个注意点~~我也WA了几次~~
1. 枚举点的时候，终值应是点值的最大值而不是n。
1. 两个点之间有可能有多个栅栏，需要记录数值而不是布尔类型。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,x,y,top,stack[10012],id,in[1012],mx;
int e[1012][1012]; 
inline void dfs(int u)
{
	for (int i=1; i<=mx; i++)
	if (e[u][i])
	{
		e[u][i]--;e[i][u]--;
		dfs(i);
	}
	stack[++top]=u;
}
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	{
		scanf("%d%d",&x,&y);
		mx=max(mx,y);
		in[x]++;in[y]++;
		e[x][y]++;e[y][x]++;
	}
	id=1;
	for (int i=1; i<=mx; i++)
	if (in[i]&1)
	{
		id=i;
		break;
	}
	dfs(id);
	while (top) printf("%d\n",stack[top--]);
	return 0;
}
```

---

## 作者：Celebrate (赞：0)

这一道题就用dfs来解就可以了，不过要注意一个细节，比如说这个数据：
```cpp
2
2 3
3 2
```
如果st一开始为1，枚举完后直接dfs会出现问题，所以枚举完以后还要再找一次

这一题没有距离，就直接找点x到点y边的个数

如果想优化可以用最短路spfa算法的建边来做

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int len,a[2100];
int bk[2100],f[2100][2100];
void dfs(int x)//用这一个点 
{
	for(int y=1;y<=n;y++)//枚举点 
	{
		if(f[x][y]>0)//如果有边 
		{
			f[x][y]--;f[y][x]--;//因为是无向边 
			dfs(y);//到下一个点 
		}
	}
	len++;a[len]=x;//记录这一个点 
}
int main()
{
	int i;
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
	 	int x,y;scanf("%d%d",&x,&y);
	 	n=max(n,max(x,y));//n找最大的数 
	 	bk[x]++;bk[y]++;//增加点出现的数量 
	 	f[x][y]++;f[y][x]++;
	}
	int st=1;//枚举起点 
	for(i=1;i<=n;i++)
	{
		if(bk[i]%2==1)//这里这样打是因为如果是双数边的话出去再进来就走不了了，单数边出去、进来、又可以出去 
		{
			st=i;break;
		}
	}
	if(st==1) for(i=1;i<=n;i++) if(bk[i]>0){st=i;break;}//如果实在不行的话就找最小可以走的边 
	dfs(st);//把这一个点当作起点，往下搜索 
	for(i=len;i>=1;i--) printf("%d\n",a[i]);//最后要反正输出 
	return 0;
}
```

---

## 作者：秋日私语 (赞：0)







```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int maxn,m,num_edge,length;
int x,y,head[5010],num[10500],circuit[10500];
struct Edge{
    int next; //下一条边 
    int to;  //指向的点 
    bool flag; //标记这条边是否走过 
};
Edge edge[10500];
/*void print(int a)
{
    if (a!=282) return;
    for (int i=head[a]; i!=0; i=edge[i].next)
        printf(" %d ",edge[i].to);
    printf("\n");
}*/
void add_edge(int from,int to)
{
    edge[++num_edge].next=head[from];
    edge[num_edge].to=to;
    head[from]=num_edge;
    num[from]++;//度 
}
void find_circuit(int i)
{
    while (1)
    {
        int minnow=head[i];
        for (int j=head[i]; j!=0; j=edge[j].next)//j=edge[i] X
            if (!edge[j].flag&&(edge[j].to<edge[minnow].to||edge[minnow].flag))//||edge[minnow].flag)是为了防止下一个点没有比当前点大的，且这条边已经在之前标记过了 
                minnow=j; //最小的下一个节点 
        if (edge[minnow].flag) break;//所有的边都走过了，就跳出 
        edge[minnow].flag=true;//将来时的边标记为走过 
        for (int j=head[edge[minnow].to]; j!=0; j=edge[j].next)//以minnow指向的第一个点（head）为起点,遍历与这个点相邻的所有的点,到来时的点 
            if (edge[j].to==i&&!edge[j].flag)//&&!edge[j].flag用来防止两点之间有多条边，但每次都标记同一条边 
            { //将这条边也记为走过 (i为起点) 
                edge[j].flag=true; break;
            } 
        find_circuit(edge[minnow].to);
    }
    circuit[++length]=i;//无路可走时，将该点存到数组里 
}
int main()
{
//    freopen("lijiaxun.in","r",stdin);
//    freopen("out.txt","w",stdout);
    scanf("%d",&m);
    for (int i=1; i<=m; i++)
    {
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);//无向图 
        int maxnn=max(x,y);
        maxn=max(maxn,maxnn); //找最大的点 
    }
    int start=1;
    for (int i=1; i<=maxn; i++)
        if (num[i]%2==1) //度只用作找起点 
        {
            start=i; break;//不要漏掉break 
        }
    find_circuit(start);
    for (int i=length; i>=1; i--)//倒序输出 
        printf("%d\n",circuit[i]);
    return 0;
}
```

---

## 作者：slyzzsc (赞：0)

**感谢三楼大哥提供的思路，我添加了一些个人的理解，希望大家能够明白并自己编写出来**

//这道题要求不重复走同一个栅栏也就是说走的路是欧拉路甚至欧拉回路

//通过邻接矩阵（因为数据量小可以使用邻接矩阵）建立边之间的关系，然后通过搜索，走过的边及时删除并记录即可

//对于欧拉回路需要有一个特判，即没有奇点的情况下，从任一点开始都可以到达

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
int path[2005],g[505][505],n,k;
int maxn,minx;
void dfs(int v)//开始搜索 
{
    int i;
    for (i=minx; i<=maxn; ++i)//逐一查找 
      {
            if (g[v][i]!=0)//如果有边相连 
              {
                  g[v][i]--;
                g[i][v]--;//删除这条边，继续向下搜索 
                dfs(i);//向下搜索    
            }
      }
    path[k++]=v;//保存路径  
}
int main()
{
    memset(g,0,sizeof(g));
    memset(path,0,sizeof(path));
    minx=505;
    maxn=0;
    k=0;//变量、数组初始化 
    int i,j,a,b;
    cin>>n;//读入有几条路 
    for (i=1; i<=n; ++i)
      {
            cin>>a>>b;//读入相连两条边的端点 
            g[a][b]++; 
            g[b][a]++;//利用邻接矩阵进行对图的存储 
            g[a][0]++;
            g[b][0]++;//计算两个端点的奇点 
            maxn=max(maxn,max(a,b));//求出端点之间的最大值 
            minx=min(minx,min(a,b));//求出端点之间的最小值
      }
    for (i=minx; i<=maxn; ++i)//逐一查找 
      {
           if (g[i][0]%2==1)//如果存在奇点说明可以向下搜索 
           {
                 dfs(i);//向下搜索 
                 break;
           }  
      }  
    if (i==maxn+1)//如果一直没有找到说明没有奇点也就是说是欧拉回路 
      dfs(1);//欧拉回路的话从任一端点出发都可以到达所以从1开始查找 
    for (j=k-1; j>=0; j--)//输出path数组，也就是路径 
      cout<<path[j]<<endl;
    return 0;      
}
```

---

## 作者：zk1431043937 (赞：0)

很久没有pascal题解了，来一发。

来做这题的真正原因是半年多以前做过这题竟然没AC。

现在做了才发现当时很多小细节没注意。

本题是一笔画问题的判断构造，整体思路不难，主要是找到度为奇数的点，再按字典序最小输出。

具体思路在代码里看：

```cpp
program p2731;
  var g:array[0..2000,0..2000]of longint;
      d,ans:array[0..2000]of longint;
      a,b,i,n,lo,minv,maxv,start:longint;
procedure find(x:longint);
  var i:longint;
begin
  for i:=minv to maxv do
  if g[x,i]>=1 then
  begin
    dec(g[x,i]);
    dec(g[i,x]);
    find(i);
  end;//将连通的边去掉并递归。
  inc(lo);
  ans[lo]:=x;//这样保证了字典序最小输出。
end;
function max(a,b:longint):longint;
begin
  if a>b then exit(a) else exit(b);
end;
function min(a,b:longint):longint;
begin
  if a<b then exit(a) else exit(b);
end;
begin
  readln(n);
  minv:=1000000;
  for i:=1 to n do
  begin
    readln(a,b);
    inc(g[a,b]);
    inc(g[b,a]);
    inc(d[a]);
    inc(d[b]);
    minv:=min(a,minv);
    minv:=min(b,minv);
    maxv:=max(a,maxv);
    maxv:=max(b,maxv);
  end;//将能连通的边累加，同时累加点的度，将标号最小和标号最大的点找出来。
  start:=1;
  for i:=1 to 500 do
  if (d[i] mod 2=1) then
  begin
    start:=i;
    break;
  end;//找到第一个入度为奇数的点开始一笔画递归。
  lo:=0;
  find(start);//找路线。
  for i:=lo downto 1 do
  writeln(ans[i]);//打印路线。
end.
```

---

## 作者：Paperback_Writer (赞：0)

欧拉路问题，题目规定有解，所以只需确定是一个奇点还是两个，两个的话再找出输出第一个数较小的解。

找出欧拉路的方法就是采用深搜的方式，对于当前的点，把所有点从小到大的搜索，找到和它相连的，找到一个之后删除它们之间的连线，并去搜索新的那个点，如果没有找到点和它相连，那么就把这个点加入输出队列。

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int path[2005],g[505][505],n,k;
int maxn,minx;
void dfs(int v)//深搜
{
    int i;
    for(i=minx;i<=maxn;i++){
        if(g[v][i])
        {
            g[v][i]--;
            g[i][v]--;
            dfs(i);
        }
    }
    path[k++]=v;
}
int main()
{
    int i;
    int a,b;
    scanf("%d",&n);
    memset(g,0,sizeof(g));
    memset(path,0,sizeof(path));
    minx=505;
    maxn=0;
    k=0;
    for(i=0;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        g[a][b]++;
        g[b][a]++;
        g[a][0]++;//a的度
        g[b][0]++;//b的度
        maxn=(a<b?b:a)<maxn?maxn:(a<b?b:a);
        minx=minx<(a<b?a:b)?minx:(a<b?a:b);
    }
    for(i=minx;i<=maxn;i++)
    {
              if(g[i][0]%2)//找偶数个度的点
          {
                  dfs(i);
                  break;
              }
    }
    if(i==maxn+1)
    {
        dfs(1);
    }
    for(int j=k-1;j>=0;j--)
            printf("%d\n",path[j]);
    return 0;
}

```

---

## 作者：约修亚_RK (赞：0)

显然，这道题是让我们来求欧拉通路（Eulerian Path）。

我们有两个算法可以用，分别是Fleury's algorithm和Hierholzer's algorithm。后者的效率比较高，是O(|E|)的，这里就用它来实现。
简单地描述一下这个算法，充分性和必要性就不证了：

```cpp
Hierholzer(u):
    While (Exist (u, v)):
        Delete (u, v)
        Hierholzer (v);
    Path[++pathSize] = u;
```
就是这么简单。此外，我们要选择这条路径的第一个点。在无向图中，存在欧拉回路的必要条件是所有顶点度数均为偶，存在欧拉路径的必要条件是有且仅有两个顶点度数为奇。由于数据保证存在欧拉路径，只要选择第一个度数为奇数的点（如果找不到的话，就用第一个度数为偶数的点）作为路径的第一个点就可以了。

具体实现的时候，我使用了multiset来保存图。这是出于题目要求优先选择较小的点访问，而set自带排序的考虑。使用multiset而非set的原因是，可能存在重边。

另外，Path应反向输出。

```cpp
/* P2731
 * Au: SJoshua
 */
#include <cstdio>
#include <set>

using namespace std;

multiset <int> map[501];

int degree[501], pathSize = 0, path[1025];

void solve(int u) {
    while (map[u].begin() != map[u].end()) { 
        multiset <int> :: iterator it = map[u].begin();
        int v = *it;
        map[u].erase(it);
        map[v].erase(map[v].find(u)); 
        solve(v); 
    }
    path[++pathSize] = u;
}

int main(void) {
    int m;
    scanf("%d", &m);
    for (int k = 0; k < m; k++) {
        int u, v;
        scanf("%d %d", &u, &v);
        map[u].insert(v);
        map[v].insert(u);
        degree[u]++;
        degree[v]++;
    }
    int start = 0;
    for (int k = 1; k <= 500; k++) {
        if (degree[k] && !start) {
            start = k;
        }
        if (degree[k] % 2) {
            start = k;
            break;
        }
    }
    solve(start);
    for (int k = pathSize; k > 0; k--) {
        printf("%d\n", path[k]); 
    }
    return 0;
}
```

---

## 作者：Skywalker_David (赞：0)

这道题是要求我们求出一条欧拉路，所以我们要首先判断图中是否有欧拉路。对于一个无向图，如果它每个点的度都是偶数，那么它存在一条欧拉回路；如果有且仅有2个点的度为奇数，那么它存在一条欧拉路；如果超过2个点的度为奇数，那么它就不存在欧拉路了。


由于题目中说数据保证至少有1个解，所以一定存在欧拉路了。但是我们还要选一个点作为起点。如果没有点的度为奇数，那么任何一个点都能做起点。如果有2个奇点，那么就只能也这两个点之一为起点，另一个为终点。但是我们要注意，题目要求我们输出的是进行进制转换之后最小的（也就是输出第一个数较小的，如果还有多组解，输出第二个数较小的，等等），所以我们要以最小的点做起点。






```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
#include<queue>
#include<climits>
#include<vector>
using namespace std;
int Max(int a,int b)    {   return a>b?a:b;  }
int Min(int a,int b)    {   return a<b?a:b;  }
int map[505][505];
int path[1050];
int pathnum;
int minv=INT_MAX,maxv=0;
void Euler_circle_u(int v)
{
    for (int i=minv;i<=maxv;i++)
        while(map[i][v]>0)
        {
            map[i][v]--;
            map[v][i]--;
            Euler_circle_u(i);
        }
    path[pathnum++]=v;
}
int main(){
    int f;
    cin>>f;
    memset(map,0,sizeof(map));
    for (int i=0;i<f;i++)
    {
        int a,b;
        cin>>a>>b;
        minv=Min(a,minv);
        minv=Min(b,minv);
        maxv=Max(a,maxv);
        maxv=Max(b,maxv);
        map[a][0]++;
        map[b][0]++;
        map[a][b]++;
        map[b][a]++;
    }
    int k=minv;
    for (int i=minv;i<=maxv;i++)
        if (map[i][0]%2==1)
        {
            k=i;
            break;
        }
    Euler_circle_u(k);
    for (int i=pathnum-1;i>=0;i--)
        cout<<path[i]<<endl;
    return 0;
}
```

---

## 作者：梦景 (赞：0)

明显的搜索+欧拉图

有点暴力 。。可能优化不够完善

附代码（其实还是比较简单的）

 
 
```cpp
var edge:array[1..500,1..500] of integer;
    t:array[1..500] of integer;
    ans:array[1..1024] of integer;
    f,k,v,max:integer;
function init():integer;
  var i,s,e:integer;
  begin
    fillchar(edge,sizeof(edge),0);
    fillchar(t,sizeof(t),0);
    max:=0;
    readln(f);
    for i:=1 to f do
      begin
        readln(s,e);
        inc(edge[s,e]);
        inc(edge[e,s]);
        inc(t[s]);
        inc(t[e]);
        if s>max then max:=s;
        if e>max then max:=e;
      end;
    for i:=1 to max do
      if odd(t[i]) then exit(i);
    exit(1);
  end;
procedure search(n:integer);
  var i:integer;
  begin
    for i:=1 to max do
      if edge[n,i]>0 then
        begin
          dec(edge[n,i]);
          dec(edge[i,n]);
          search(i);
        end;
    v:=v+1;
    ans[v]:=n;
  end;
procedure print;
  var i:integer;
  begin
    for i:=v downto 1 do
      writeln(ans[i]);
  end;
begin
  k:=init();
  v:=0;
  search(k);
  print;
end.
```

---

