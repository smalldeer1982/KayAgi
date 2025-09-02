# [USACO08DEC] Trick or Treat on the Farm G

## 题目描述

每年，在威斯康星州，奶牛们都会穿上衣服，收集农夫约翰在 $N(1\le N\le 100,000)$ 个牛棚隔间中留下的糖果，以此来庆祝美国秋天的万圣节。

由于牛棚不太大，FJ 通过指定奶牛必须遵循的穿越路线来确保奶牛的乐趣。为了实现这个让奶牛在牛棚里来回穿梭的方案，FJ 在第 $i$ 号隔间上张贴了一个 “下一个隔间：$next_i(1\le next_i\le N)$” 的标语，告诉奶牛要去的下一个隔间。这样，为了收集它们的糖果，奶牛就会在牛棚里来回穿梭了。

FJ 命令奶牛 $i$ 应该从 $i$ 号隔间开始收集糖果。如果一只奶牛回到某一个她已经去过的隔间，她就会停止收集糖果。

在被迫停止收集糖果之前，计算一下每头奶牛要前往的隔间数（包含起点）。

## 样例 #1

### 输入

```
4 
1 
3 
2 
3 
```

### 输出

```
1 
2 
2 
3 
```

# 题解

## 作者：cjrsacred (赞：241)

做完以后粗略翻了下题解，发现都是 $Tarjan$ 或记忆化搜索，总之逃不出 $dfs$，所以我就把我的非递归方法贡献一下吧。

事实上，这道题用 $Tarjan$ 是大材小用了。此题不需要任何算法，两层简单的循环就能解决。

首先我们需要注意到一点，虽然此题也是一张有向图，但是每个点的出度有且只有 “1”。这说明什么？不需要递归，直接沿着这条唯一的路径走下去就行了......

### 一、为了实现这一方法，我们对每个点设置两个属性：

1、颜色 $(color)$ ： 此节点第一次被访问时，这条访问他的路径是由那个节点发出的（起点）。

2、时间戳 $(dfn)$ ：此节点第一次被访问时，他到发出这条路径的起点的距离（发出节点的 $dfn = 0$，第二个被访问的节点的 $dfn = 1$，第三个 $dfn = 2$ ......）

有了这两个属性，我们就可以计算环的大小，方法如下：

1、从某一节点发出路径

2、走到某个节点上（包括起点），如果这个节点没有被染色，那么染成自己的颜色，并标记上 $dfn$

3、走到某个节点上，如果这个节点已经被染成了自己的颜色，那么环的大小就出来了：当前时间 $(cnt)$ $-$ 此节点 $dfn$

到了这一步，实际上已经解决了另一个更简单的问题：[NOIP2015 信息传递](https://www.luogu.org/problemnew/show/P2661)。 接下来就是本题特色了

### 二、对于每一只奶牛（或者说每一个起点、颜色、路径），我们记录如下两个属性：

1、环的大小 $(minc)$ ：每条路径最终都会进入环中，或者起点本身就在环中，我们记录下这个环的大小为之后服务

2、入环时间戳 $(sucdfn)$ ：这条路径什么时候会进入环中，同样是为之后服务的一个属性

首先讲解一下如果得到这两个属性：

1、在上一节中我们已经讲了如何初步获取环的大小，入环时间戳只要记录为那个交点的时间戳即可

2、如果走到了之前走过的节点，那么新的路径必然进入之前路径的环中，直接把这个环的大小要过来就行了。入环时间戳则分两种情况：

i. 如果这个节点不在环中，“原路径的入环时间戳 $-$ 原路径中此节点的时间戳 +　新路径当前时间”　即为新路径的入环时间戳;

ii. 而如果这个节点在环中，直接就是新路径当前时间。

iii. 判断方法则是 “原路径的入环时间戳 $-$ 原路径中此节点的时间戳” 是否大于 $0$，综合起来就是：“$max($原路径的入环时间戳 $-$ 原路径中此节点的时间戳$, \;0)$ +　新路径当前时间”

### 三、把上面的问题都解决了，出答案就太简单了：

1、第一节中的发现环的大小之后，答案就是“当前时间”

2、第二节中与之间走过的节点相遇并记录完信息后，答案是 “入环时间戳 + 环的大小”

至此本题已经完美解决，且没有用到任何算法。贴代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn = 100000 + 5;

int n;
int nxt[maxn];
int color[maxn];
int sucdfn[maxn];
int dfn[maxn];
int minc[maxn];

void Init()
{
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> nxt[i];
	memset(color, 0, sizeof(color));
	memset(dfn, 0, sizeof(dfn));
	memset(minc, 0, sizeof(minc));
}

void Solve()
{
	for(int cow = 1; cow <= n; ++cow) 
	{
		for(int i = cow, cnt = 0; ; i = nxt[i], ++cnt)
		{
			if(!color[i]) {
				color[i] = cow;
				dfn[i] = cnt;
			}
			else if(color[i] == cow) {
				minc[cow] = cnt - dfn[i];
				sucdfn[cow] = dfn[i];
				cout << cnt << endl;
				break;
			}
			else {
				minc[cow] = minc[color[i]];
				sucdfn[cow] = cnt + max(sucdfn[color[i]] - dfn[i], 0);
				cout << sucdfn[cow] + minc[cow] << endl;
				break;
			}
		}
	}
} 

int main()
{
	Init();
	Solve();
	return 0;
}
```

---

## 作者：一剑缥缈 (赞：67)

水过这题一看题解发现大部分都是Tarjan之类~~我不会~~复杂的算法，要不就是一些不够优良、不够易懂的算法。于是发这篇题解，希望帮助一下和我一样的蒟蒻。

---


在做提高试炼场时看到了这题:

![shilianchang](https://s2.ax1x.com/2019/07/30/eG4szD.png)

（~~实在找不到没有通过的图片了~~）

作为一个板块里的题，自然是连着做的，于是产生了一种神奇的惯性思维。在看到题面的第一眼就发现这道题与[P2611 信息传递](https://www.luogu.org/problem/P2661)十分相像，就尝试使用与信息传递类似的方法来求解。

根据题意，一只奶牛停止的条件是来到她所经过过的房间，所以奶牛想要停下来必须要找到一个环。我们从一个点开始搜索的时候用s数组记录下依次到达每个房间的糖果数并用vis数组记录访问过的房间，在找到已经访问过的房间的时候，用现在到达这个房间应该得到的糖果数s[n]减去已经上次来到时得到的糖果数s[m]，用h数组记录下来，就可以得知这个环上获得的糖果数。

```cpp
void dfs(int now,int nowc)
{
    if(vis[now]==true) //如果已经访问过
    {
        h[now]=nowc-s[now]; //环上的糖果数
        return;
    }
    vis[now]=true; //记录访问过
    s[now]=nowc; //记录现在的糖果数
    dfs(a[now],nowc+1);
    return;
}
```
那记录下环上的糖果数有什么用呢？你看这里有一个又大又圆的环：

![huan](https://s2.ax1x.com/2019/07/30/eGT4BQ.jpg)

因为一个房间通向的房间都是唯一的，不难发现一但来到环上的任何一个房间，必定会绕这个环一圈回到原点。则对于每一个环上的房间，之后会获得的糖果数就是确定的。所以我们可以根据这个特点，标记环上的每一个房间，一但到达这些房间就直接返回环上的糖果数。

```cpp
int dfs(int now,int nowc)
{
    if(h[now]!=0) return nowc-1+h[now]; //如果这个房间在环上，直接返回环上糖果数
    if(vis[now]==true)
    {
        h[now]=nowc-s[now];
        flag=now; //记录现在环上的终点
        return nowc-1; //返回现在的糖果数
    }
    vis[now]=true;
    s[now]=nowc;
    int ans=dfs(d[now],nowc+1); //因为还需要标记所以不直接返回值
    if(flag!=0) //如果房间还在环上
    {
        if(now==flag) flag=0; //如果回到起点，就清空记录
        else h[now]=h[flag]; //否则标记这个房间在环上
    }
    vis[now]=false //清除记录，省好多个memset()
    return ans;
}
```
然后开开心心交一发。

![tle](https://s2.ax1x.com/2019/07/30/eG7IKO.png)

![heiren](https://s2.ax1x.com/2019/07/30/eG7HVH.jpg)

好像有些不对劲，果然蓝题不是那么好水的。。。仔细一想原因应该是可能出现有好多小环的情况，这样的情况下基本就等同于暴力。

于是我开动我的小脑瓜，发现TLE的原因正是思考的不够全面。既然一个房间通向的房间是唯一的，那么来到任意一个房间，接下来的结局都是固定哒！！！所以我们只要在回溯的时候对于不在环上的房间记录下之后获得的糖果数，在下一次到达的时候直接返回即可。

```cpp
int dfs(int now,int nowc)
{
    if(h[now]!=0) return nowc-1+h[now];
    if(vis[now]==true)
    {
        h[now]=nowc-s[now];flag=now;
        return nowc-1;
    }
    vis[now]=true;s[now]=nowc;
    int ans=dfs(d[now],nowc+1);
    if(flag!=0)
    {
        if(now==flag) flag=0;
        else h[now]=h[flag];
    }
    else h[now]=h[d[now]]+1; //如果不在环上就记录下一个房间的糖果数加1
    vis[now]=false;
    return ans;
}
```

轻轻的敲上一行代码，再一次提交。

![ac](https://s2.ax1x.com/2019/07/30/eGOvDK.png)

这回就舒服了，比之前高到不知道哪里去了。忍不住看了一发最优解，结果发现竟然只排在第9页？仔细一看前面，竟然都加快读和开O2，哼哼，那就由不得我了。经过一番尝试，终于搞到了第2页的第一个，才敢来发题解。

完整代码

```cpp
// 快读请自行添加
#include <iostream>
#include <cstdio>
using namespace std;
int n,d[100008],s[100008],h[100008],flag;
bool vis[100008];
int dfs(int now,int nowc)
{
    if(h[now]!=0) return nowc-1+h[now];
    if(vis[now]==true)
    {
        h[now]=nowc-s[now];flag=now;
        return nowc-1;
    }
    vis[now]=true;s[now]=nowc;
    int ans=dfs(d[now],nowc+1);
    if(flag!=0)
    {
        if(now==flag) flag=0;
        else h[now]=h[flag];
    }
    else h[now]=h[d[now]]+1;
    vis[now]=false;
    return ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    for(int i=1;i<=n;i++) printf("%d\n",dfs(i,1));
    return 0;
}
```

---

## 作者：_Lemon_ (赞：61)

##solution

###首先看到这题，题目要求回到经过的点，那么很明显是形成了一个环，那么很容易想到是Tarjan，仔细一想，一个点只有两种情况，要么在环中，要么通过一条链与环相接。那么思路便很明显了，先缩点，记录各个环的大小，在环内的点的Ans值便是环的大小，在环外的点的Ans=点到环的最短距离+环的大小。
但注意要特判环大小为1的情况。
##贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=100005;
int next[Maxn];
int ans[Maxn];
int head[Maxn],cnt;
struct road
{
    int to,next;
}e[Maxn*2];
void add(int a,int b)
{
    cnt++;
    e[cnt].to=b;
    e[cnt].next=head[a];
    head[a]=cnt;
}
int sum,color[Maxn],low[Maxn],ins[Maxn],tim[Maxn],sta[Maxn],top=1,col;
int Lemon[Maxn];
void Tarjan(int x)
{
    sum++;
    tim[x]=low[x]=sum;
    sta[top]=x;
    top++;
    ins[x]=1;
    for(int i=head[x];i!=0;i=e[i].next)
    {
        if(ins[e[i].to]==0)
        {
            Tarjan(e[i].to);
            low[x]=min(low[x],low[e[i].to]);
        }
        else if(ins[e[i].to]==1)
             	low[x]=min(low[x],tim[e[i].to]);
    }
    if(tim[x]==low[x])
    {
        col++;
        do
        {
            top--;
            color[sta[top]]=col;
            ins[sta[top]]=-1;
        }while(sta[top]!=x);
    }
    return ;
}
void search(int root,int x,int step)
{
    if(ans[x]!=0) {
                    ans[root]=ans[x]+step;
                    return ;
                  }
    else search(root,next[x],step+1);
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&next[i]);
        add(i,next[i]);
        if(next[i]==i) ans[i]=1;//注意特判环为1的情况。
    }
    for(int i=1;i<=n;i++)
        if(ins[i]==0) Tarjan(i);
    for(int i=1;i<=n;i++)
    	Lemon[color[i]]++;//记录环的大小
    for(int i=1;i<=n;i++)
    	if(Lemon[color[i]]!=1) ans[i]=Lemon[color[i]];//处理在环内的点
    for(int i=1;i<=n;i++)
    	if(ans[i]==0) search(i,next[i],1);//处理在环外的点。
    for(int i=1;i<=n;i++)
    	printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：backup_noob (赞：46)

考虑到这个图每个点只有一条出边，可以把扫出答案的思路简化一下，分**简单环**和**链**稍微讨论一下，可以较大程度减小代码量。
```
#include<cstdio>
#include<iostream>
using namespace std;
const int N=1e5+5;
int n,to[N],rd[N],w[N],dep[N],mk[N];char vis[N],ins[N];
int dfs(int x){
    int t=to[x];vis[x]=ins[x]=1;
    if(!vis[t]){dep[t]=dep[x]+1;w[x]=dfs(t);w[x]+=(mk[t]?(mk[x]=(mk[x]!=2?1:0),0):1);}
    else if(ins[t])w[x]=dep[x]-dep[t]+1,mk[x]=1,mk[t]=(x==t?0:2);
    else w[x]=w[t]+1;
    ins[x]=0;return w[x];
}
int main(){
    ios::sync_with_stdio(false);cin>>n;int x;
    for(int i=1;i<=n;++i)cin>>to[i],++rd[to[i]];
    for(int i=1;i<=n;++i)if(!rd[i])w[i]=1,dfs(i);
    for(int i=1;i<=n;++i)if(!vis[i])dfs(i);//totally a cycle
    for(int i=1;i<=n;++i)cout<<w[i]<<endl;
    return 0;
}
```
~~这么点代码我居然调了一下午~~

---

## 作者：pantw (赞：37)

做法类似于NOIP2015 D1T2 message。

拓扑排序删链 → 对环上的点计算答案 → dfs计算其他点的答案。

环上的点答案都一样，可以一遍dfs跑出来；

其他点的答案在dfs返回的时候+1即可。

实现细节详见代码。


```cpp
#include <cstdio>
#define maxn 100010

int next[maxn], in[maxn], ans[maxn];
bool vis[maxn];

void del(int cur) {
    vis[cur] = true;
    in[next[cur]]--;
    if(!in[next[cur]]) del(next[cur]);
}

int calccircle(int cur, int depth) {
    ans[cur] = depth;
    if(ans[next[cur]]) return depth;
    else return ans[cur] = calccircle(next[cur], depth + 1);
}

int calc(int cur) {
    if(ans[cur]) return ans[cur];
    else return ans[cur] = calc(next[cur]) + 1;
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", next + i), in[next[i]]++;
    for(int i = 1; i <= n; i++) if(!in[i] && !vis[i]) del(i);
    for(int i = 1; i <= n; i++) if(in[i] && !ans[i]) calccircle(i, 1);
    for(int i = 1; i <= n; i++) if(!in[i] && !ans[i]) calc(i);
    for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
}
```

---

## 作者：xiejinhao (赞：35)

# P2921 在农场万圣节 题解
## 并查集 题解
### 然发现题解都是$Tarjan$ ~~而本人并不会写（这就是这篇题解的来历）~~
附赠并查集模板题：[[模板]并查集](https://www.luogu.org/problemnew/show/P3367)

Part 1：题目分析
------------

- 看到这个题目，每个房间都会对应一个所要去的房间，说明**这是一张有向图，我们也可以理解成一片带环的森林**。既然这里说到了环，那么很自然地想到$Tarjan$，**但是，并查集不也是可以求环的吗？**

并查集可以硬套，但是我们需要另开一个数组记录这个节点的父节点，这样，在我们找到环之后我们就可以原样退回，依次赋值。

**因为在一个环上的房间走一圈经过的房间数是一样的！**

那么为什么要另外记录父节点？因为我们**路径压缩**了，这样**每个点全部指向根节点，我们就回不去了**。


Part 2：问题解决
------------

### 解决环

搜索环就很简单了，那么环上还有一些支链怎么解决呢？我们画图会发现，对于一个节点只有两种情况：
1. **在环上**
1. **在通向环的路上**

那么如果我们把环的大小定义为环上的节点数，**那么：**

**定理一**：**链上各点走到有走过的点所经过的节点数就都等于环的大小**

**定理二**：**链上各点走到有走过的点所经过的节点数就等于该节点到环上的距离+环的大小**

所以我们对每个节点全部加入并查集走一遍，并且这种方法是在线的，我们不需要储存数据：

```cpp
  //f存储在哪个集合，fa存储父节点，并查集操作是对f的操作
  //i是循环变量，当前到第i个房间，走到第m个房间
  //并查集别忘了数组初始化
    int m;
    scanf("%d",&m);
    Find(m,i);
    
  int Get(int x) {
    if(x==f[x]) return x;
    return f[x]=Get(f[x]);
  }
  void Find(int p,int q) {
    if(Get(p)==Get(q)) {//找到环了
      int cnt=1;//最后会少一个，这里初值设为1
      //回退
      for(int i=p;i!=q;i=fa[i]) cnt++;//累加环的长度
      for(int i=p;i!=q;i=fa[i]) E[i]=cnt;
      //定理一
      E[q]=cnt;
      return;
      //E数组是答案数组
    }
    //没找到环
    //并查集集合合并，可以写成merge函数形式
    //值得注意的是，这里是以当前房间为父节点合并的
    f[Get(q)]=Get(p);
    fa[q]=p; //记录父节点
    /*
    merge函数：
    void merge(int x,int y) {
      f[get(x)]=get(y);
    }
    */
  }
```
这里作个解释，为什么Get(p)==Get(q)就是找到环了？首先，这个算法是在线的，一开始$f[i]$的初始值都为$i$，那么如果$i$(第$i$个房间)，$x$(要去的房间)指向同一个祖先，那就说明$i$与$x$在同一个集合内，这里的集合指什么？就是我们所说的环，因此并查集可以解决环的问题。

**这就是并查集：查询元素是否在同一个集合内，并且支持将两个元素同时放到一个集合内。**

### 环解决完了，下面需要解决链

**我们在解决环的时候，已经把环上的点都赋予了答案，那么剩下没答案的就是链了**。因此我们只需要用$O(n)$的时间找一下还有那些没答案的，再用一个循环找到它到所在环的距离就行了。总复杂度大概$O(2n)?$

```cpp
  for(int i=1;i<=n;i++) {
    if(!E[i]) {//找到链，处理链上的节点
      int cnt=1,j;
      for(j=fa[i];!E[j];j=fa[j]) cnt++;
      //同理，链的长度
      E[i]=cnt+E[j];
    }
    //输出答案
    printf("%d\n",E[i]);
  }
```
不理解的话我还特意给了张图(~~感谢几何画板的支持~~)：
![](https://i.loli.net/2019/06/05/5cf79a0d7a28114585.jpg)

Part 3：AC
------------

好了，上面已经解决完本题了，别忘了**并查集初始化**：

```cpp
  for(int i=1;i<=n;i++) f[i]=i;
```
下面整理一下关键代码片段：

**数组、定义交代：**
```cpp
  int E[SIZE],f[SIZE],fa[SIZE];
  //E答案数组，f并查集数组，fa父节点数组
```


**1. 并查集部分：**

```cpp
  int get(int x) {
    if(x==f[x]) return x;
    return f[x]=get(f[x]);
  }
  int merge(int x,int y) {
    f[get(x)]=get(y);
  }
```
**2. 找环：**

```
  for(int i=1;i<=n;i++) {
    int m;
    scanf("%d",&m);
    Find(m,i);
  }
  //函数位置自己看着办
  void Find(int p,int q) {
  if(get(p)==get(q)) {//找到环
    int cnt=1;
    for(int i=p;i!=q;i=fa[i]) cnt++; //找环的长度
    for(int i=p;i!=q;i=fa[i]) E[i]=cnt;
    E[q]=cnt;
    return;
  }
  //没找到，合并
  merge(q,p);
  fa[q]=p;
}
```
**3. 找链&输出答案：**

```cpp
  for(int i=1;i<=n;i++) {
    if(!E[i]) {
      int cnt=1,j;
      for(j=fa[i];!E[j];j=fa[j]) cnt++;
      //找链的长度
      E[i]=cnt+E[j];
    }
    printf("%d\n",E[i]);
  }
```
**4. $End$**

```cpp
  return 0;//比赛忘了写后果自负
```
~~剩下部分自己补充了，有问题私聊~~


$END$
------------

## 最后祝大家$NOIP2019 RP++$

（~~这样可以点赞了吧？~~）


---

## 作者：sigland (赞：22)

发篇蒟蒻至极的题解...(不懂缩点,tarjan.jpg)
首先这题n点n边还tmd连通,那显然这题就是一棵n个树上多了一条奇奇怪怪的边(返祖边),既然只有一条返祖的边,那么也就等价于这棵树上有且仅有一个环.所以直接讨论一个点是否在环上,如果在则答案与它指向点相同,不然就等于它指向点答案+1,具体就直接大力dfs,每个点最多访问一次,故总复杂度为O(n).(这里注意下dfs不一定只跑一遍就能访问所有的点,但显然跑一次dfs一定可以处理掉环)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,to[100010],dp[100010],deep[100010];
bool vis[100010];//是否访问 
void dfs(int pos,int dep)
{
	vis[pos]=1;deep[pos]=dep;
	if(dp[to[pos]])dp[pos]=dp[to[pos]]+1;//如果已求得指向点答案,那么它与指向点不可能同在环上,故答案为指向点+1 
	else if(deep[to[pos]])//如果跑到这次dfs已访问过的点,说明找到环了,暴力更新环上所有点答案 
	{
		dp[pos]=(deep[pos]-deep[to[pos]]+1);
		int nw=to[pos];
		while(nw!=pos)
		{
			dp[nw]=dp[pos];
			nw=to[nw];
		}
	}
	else //如果跑完指向点而它本身答案没有更新,那么说明它不在环上,答案为指向点+1 
	{
		dfs(to[pos],dep+1);
		if(!dp[pos])dp[pos]=dp[to[pos]]+1;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&to[i]);
	for(int i=1;i<=n;i++)
		if(!vis[i])dfs(i,0);//没访问过就dfs 
	for(int i=1;i<=n;i++)
		printf("%d\n",dp[i]);	//输出 
}
```


---

## 作者：租酥雨 (赞：19)

本质上是一道图论题，但是由于其题面的特殊性可以做一些简化。

若一个点u的后继节点是v，那么我们就在图中连一条**(u,v)的有向边**。求每头奶牛能到达的节点数，就可以对这张图跑**Tarjan缩点**，然后再用**拓扑+DP**或是**记忆化搜索**实现。

**简化：**

可知每个点出度为一，so...我们就不需要用邻接表存边了！而且从每个点出发后路径是唯一的，因此在缩点后，每个强联通分量的出度也至多为一。

我们设dp[u]表示从u号强联通分量(重新标号)出发可以到达的节点数，设u的出边指向v，可知**dp[u]=dp[v]+sz[u]**（其中sz[u]为u强联通分量的大小）。记搜转移即可。

代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int _ = 100005;
int n,to[_],dfn[_],low[_],tot,stack[_],top,vis[_],col[_],scc,out[_],sz[_],dp[_];
int gi()
{
    int x=0,w=1;char ch=getchar();
    while ((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if (ch=='-') w=0,ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return w?x:-x;
}
void Tarjan(int u)
{
    dfn[u]=low[u]=++tot;
    stack[++top]=u;vis[u]=1;
    int v=to[u];
    if (!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
    else if (vis[v]) low[u]=dfn[v];
    if (dfn[u]==low[u])
    {
        scc++;//强联通分量的标号
        do
        {
            v=stack[top--];
            vis[v]=0;
            col[v]=scc;//某点所在的强联通分量的标号
            sz[scc]++;//大小
        }while (u!=v);
    }
}
int dfs(int u)
{
    if (!u||dp[u]) return dp[u];
    return dp[u]=dfs(out[u])+sz[u];
}
int main()
{
    n=gi();
    for (int i=1;i<=n;i++)
        to[i]=gi();
    for (int i=1;i<=n;i++)
        if (!dfn[i]) Tarjan(i);
    for (int i=1;i<=n;i++)
        if (col[i]!=col[to[i]])
            out[col[i]]=col[to[i]];
    for (int i=1;i<=n;i++)
        printf("%d\n",dfs(col[i]));
    return 0;
}

```

---

## 作者：陈刀仔 (赞：16)

# Tarjan
首先，拿到题目，先来分析一下这个图的大致模样。
我们会发现，**每一头奶牛有多条入边，但只有至多一条出边。** 所以，这个图大致是这样的（假设不存在自环）![](https://cdn.luogu.com.cn/upload/pic/56558.png )

形如这样，有n条边，n个结点，且每个节点有且仅有一条出边的图，被称为**基环内向树**

不难看出，和外向树一样，**每个内向树只有一个环，即每个结点一定有它唯一对应的环。** 

然而按照这道题目的意思，**我们只需找到每个点对应的环，统计从该结点到达环的路径的长度，再加上环的大小，就是答案。而对于环上的点，它所属的环的大小就是答案。**

但是，直接这样子实现显然要超时，因为你在不断地走重复的结点。**所以我们应该用Tarjan求出强连通分量后，将边反向，将强连通分量上的点的对应子树进行一次简单的树形DP，** 就可以在 O(N) 的时间复杂度里求解了。（因为此时变成了外向树）

同时，**还要注意自环。**

```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;
const int maxn=100050,maxm=100050;
inline int read(){	//快读 
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int cnt;	//边数 
int head[maxn],next[maxm],to[maxm];		//正向图 
int head1[maxn],next1[maxn],to1[maxn];	//反向图 
inline void add(int x,int y)	//连边 
{
    cnt++;
    to[cnt]=y;
    next[cnt]=head[x];
    head[x]=cnt;
    to1[cnt]=x;
    next1[cnt]=head1[y];
    head1[y]=cnt;
}
int low[maxn],dfn[maxn],tp,tot,s[maxn],n,m;	//tarjan 
bool vis[maxn];
int k,scc[maxn],bel[maxn],ans[maxn];
// scc[i]  编号为i的强连通分量的大小 
// bel[i]  i结点所属的强连通分量
// ans[i]  每个结点的答案 
void tarjan(int u)
{
    tp++;
    tot++;
    dfn[u]=low[u]=tot;
    s[tp]=u;
    vis[u]=1;
    for(int i=head[u];i;i=next[i])
    {
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v])
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u])
    {
        k++;
        do{
            scc[k]++;
            bel[s[tp]]=k;
            vis[s[tp]]=0;
            tp--;
        }while(u!=s[tp+1]);
    }
}
void dfs(int u)	//对反向图中每一个子树求解 
{
    for(int i=head1[u];i;i=next1[i])
    {
		int v=to1[i];
		if(!ans[v])
		{
			ans[v]=ans[u]+1;
			dfs(v);
		}
	}
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        int x;
        x=read();
        add(i,x);
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++)
    {
		if(to[head[i]]==i)	//自环 
		{
			ans[i]=1;
		}
		if(scc[bel[i]]>1)	//是一个强连通分量上的点 
		{
			ans[i]=scc[bel[i]];
		}
	}
    for(int i=1;i<=n;i++)
    {
		if(scc[bel[i]]>1||to[head[i]]==i)	//注意自环 
		{
			ans[i]=scc[bel[i]];
			dfs(i);
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<endl;
	}
    return 0;
}

```


---

## 作者：EricWay1024 (赞：10)

这题与其说是个图论题，不如说是个模拟题……

在任何时刻，一只奶牛都只有两种可能的状态：

1. 在一个环上

1. 在通往一个环的路上


***所以我不妨大步向前走去，向着我自以为可以走去的路。——鲁迅***

我们选定了一个点，就只管走。在这一过程中，也只会发生两件事：

1. 碰到了一个点，这个点的最终答案我已经知道了

1. 碰到了一个点，这个点我刚刚走过了

**第一种**情况，我们只需往回走，同时对路径上的点标记答案：**每个点的答案是它的下一个点的答案+1.**所以我们需要一个before数组，来告诉我们如何往回走。

**第二种**情况，这表明我们已经发现了一个之前没有发现的环。我们只需做两件事：

1. 标记从起点开始，通往环的路径上点的答案。这和第一种情况是一样的。

1. 标记环上每个点的答案。只需要在访问每个点的时候记录一下“时间戳”，两次访问同一个点的时间戳相减就可以得到环的大小。

每个点都走了且只走了两遍。时间复杂度O(N).

```cpp
//
//Author EricWay1024
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<deque>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector>
#define INF 0x3f3f3f3f
#define N 101234
using namespace std;

int n, next[N];
int vis[N];
int ans[N];
int before[N];

inline int read(){
    int x=0; int sign=1; char c=getchar();
    while(c>'9' || c<'0') {if (c=='-') sign=-1;c=getchar();}
    while(c>='0' && c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*sign;
}

void walk_back(int u, int num){
    while(!ans[u]){
        ans[u]=num++;
        u=before[u];
    }
} 

void walk_ring(int u, int num){
    while(!ans[u]){
        ans[u]=num;
        u=next[u];
    }
} 

void walk(int u){
    memset(vis, 0, sizeof(vis));
    memset(before, 0, sizeof(before));
    int num=1; 
    while(1){
        if (ans[u]){
            if (before[u]) walk_back(before[u], ans[u]+1); 
            break;
        }
        if (vis[u]){
            ans[u]=num-vis[u];
            if (before[u]) walk_back(before[u], ans[u]+1);
            walk_ring(next[u], ans[u]);
            break;
        }
        vis[u]=num++;
        if (!vis[next[u]])before[next[u]]=u; //注意这里的if。这是为了防止通往环的路径被覆盖
        u=next[u];
    }
}

int main(){
#ifdef ERIC
    freopen("2921.in","r",stdin);
    double TIMEA=clock();
#endif
    n=read();
    for (int i=1; i<=n; i++) next[i]=read();
    
    for (int i=1; i<=n; i++){
        if (!ans[i]) walk(i);
    }
    for (int i=1; i<=n; i++){
        cout<<ans[i]<<"\n";
    }


#ifdef ERIC
    double TIMEB=clock();
    printf("\nTime consumed: %.3fs.\n", (TIMEB-TIMEA)/1000);
#endif
    return 0;
}


```

---

## 作者：CuriousCat (赞：5)

这是一个每个点出度为1的有向图，自己玩玩就发现是环上挂了很多树，然后答案就是每个点的深度加上环的size。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 50;
int n, nxt[N], ctim, tim[N], f[N], cirl, cirr;
void dfs(int v) {
    tim[v] = ++ctim;
    if (tim[nxt[v]] == 0) { 
        dfs(nxt[v]);
        if (cirl <= tim[v] && tim[v] <= cirr) f[v] = cirr - cirl + 1;
        else f[v] = f[nxt[v]] + 1;
    } else if (tim[nxt[v]] > 0) {
        cirr = tim[v]; cirl = tim[nxt[v]];
        f[v] = cirr - cirl + 1;
    } else f[v] = f[nxt[v]] + 1;
    tim[v] = -1;
}
int main(int argc, char *argv[]) {
    int i; scanf("%d", &n);
    for (i = 1;i <= n;++i) scanf("%d", &nxt[i]);
    for (i = 1;i <= n;++i) if (!tim[i]) { cirr = cirl = ctim = 0; dfs(i); }
    for (i = 1;i <= n;++i) printf("%d\n", f[i]);
    return 0;
}
```

---

## 作者：ifyml (赞：4)

## tarjan缩点


------------
1. 先用tarjan找到一个环或者是一个点，用sum把这个环的点数保存。
2. 奶牛会出现两种走法：1)在自己环里采集糖果。2)去别人环里采集糖果。
1. 当奶牛现在在一个环里，采集完这个环里的所有糖果后，就结束了。


```cpp
#include<iostream>
#include<cstdio>
#define NN 100001
using namespace std;
int N,t,top,co;
int l[NN],head[NN],q[NN],col[NN],dfn[NN],low[NN],stack[NN],sum[NN],f[NN];
void tarjan(int u)
{
    dfn[u]=low[u]=++t;
    stack[++top]=u;
    int v=q[u];
    if(!dfn[v])
    {
        tarjan(v);
        low[u]=min(low[u],low[v]);
    }
    else if(!col[v])low[u]=min(low[u],low[v]);
    if(dfn[u]==low[u])
    {
        co++;
        while(1)
        {
            int t=stack[top];top--;
            col[t]=co;
            sum[co]++;//统计环里有多少糖果
            if(t==u)break;
        }
    }
}
int sl(int x,int s)
{
    if(col[x]==col[s])return 0;
    //如果现在这个点和上一个点都在一个环里，就退出。
    if(f[x])return f[x];//记忆化搜索，不然会超时...
    int a=sum[col[x]],v=q[x];
    return f[x]=a+sl(v,x);
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&l[i]);
        q[i]=l[i];//q[i]是i的下一个点
    }
    for(int i=1;i<=N;i++)
     if(!dfn[i])tarjan(i);
    for(int i=1;i<=N;i++)
     printf("%d\n",sl(i,0));
    return 0;//OK.
}
```

---

## 作者：Jayne (赞：4)

这道题本来想的是dfs遍历整张图分别统计答案，之后考虑时间复杂度n<=1e5显然需要一个O（n）或者nlogn的算法。观察题目，发现每个点的出度一定为1，这时候统计这个点所到达的最多的点数其实就可以表示成链+环的形式，而每个环上的点的答案显然都是一样的。可以使用拓扑排序找出所有的环，记录答案，然后使用记忆化搜索或者dp来找出答案。dfs(i)=dfs(a[i])+1,使用记忆化搜索来进行维护。


```cpp
    #include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<functional>
#define ll long long
#define N 100001 
using namespace std;
inline int read(){
    int X=0,w=1;char ch=0;
    while(ch>'9'||ch<'0'){
        if(ch=='-'){
            w=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        X=(X<<1)+(X<<3)+ch-'0';
        ch=getchar();
    }
    return X*w;
}
int a[N],n;
int dp[N];
int rd[N];
int vis[N];
int num=0;
int dfs1(int x){
    if(vis[x])return 0;
    num++;
    vis[x]=1;
    dfs1(a[x]);
}
int exist[N];
int dfs2(int x){
    if(exist[x])return 0;
    dp[x]=num;exist[x]=1;
    dfs2(a[x]);
}
int dfs(int x){
    if(dp[x])return dp[x];
    dp[x]=dfs(a[x])+1;
    return dp[x];
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        rd[a[i]]++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(!rd[i]){
            q.push(i);
            vis[i]=1;
        }
    }
    while(!q.empty()){
        int x=q.front();
        q.pop();
        rd[a[x]]--;
        if(!rd[a[x]]){
            q.push(a[x]);
            vis[a[x]]=1;
        }
    }
    for(int i=1;i<=n;i++){
        num=0;
        if(!vis[i]){
            dfs1(i);
            dfs2(i);
        }
    }
    for(int i=1;i<=n;i++){
        printf("%d\n",dfs(i)); 
    }
    return 0;
}

```

---

## 作者：zfz04 (赞：4)

# 纯记忆化搜索

~~菜鸡写给新手看的~~

本蒟蒻表示不会什么Tarjan缩点；只会打打暴搜；~~(本蒟蒻自己写出的第一道蓝题）.~~

 **暴搜思路：**

- 首先这道题的图是一条带环的链（可能是不连通的，但这点在代码实现的时候可以不考虑），那就先构造出这条链，然后再在链里dfs；
- 一个环里的隔间能够到达的隔间总数是相同的，是等于这个环里的结点个数的；找环可以在dfs的过程中找，具体如何操作看代码；
- 如果这个结点不属于任何一个环，那它能去到的总隔间数会等于它去到的下一个隔间能去到的隔间数加1；
------------
**思路有了，你可以先去试试自己完善代码，如果还不行，那再看下面的代码也不迟；**

**代码+实现过程：**~~本蒟蒻代码能力不强，可能还可以优化，如果可以还请评论告诉我~~
```cpp
#include<iostream>
#include<cstring>
using namespace std;
bool c[100004],h[100004];//dfs遍历中c数组判断是否遍历过；h判断这个结点是否在环里 
int father[100004];//下一个隔间 ； 
int n;
int d[100005];//最终答案； 
void dfs(int x)
{
	if(c[x]){//当dfs遇到经过的结点时，从这个结点开始往后一定会构成一个环；为什么呢，可以想象当一个像一个6一样的图，从头部开始dfs，那当你遇到第一个走过的点时，那就代表你能从这个点走回这个点，那不就是一个环吗； 
		int t=x,k=1;
		x=father[x];
		while(x!=t){//记录结点数，存环； 
			k++;
			h[x]=1;
			x=father[x];
		}
		h[x]=1;//代码冗杂部分，哪位大佬可以解决一下；（其实就是懒，不想改了）； 
		d[x]=k;
		x=father[x];
		while(x!=t){//存答案； 
			d[x]=k;
			x=father[x];
		}
		return;
	}
	if(d[x]){//下一个点遍历过，那就返回；为什么不直接用c数组呢？因为下面数组归零了；那为什么要归零呢？ 因为我们判环是用的c，如果c不归零，那就会出现错判环；所以这里我们用d的值是否改变过来判断； 
		return;
	}
	c[x]=true;
	dfs(father[x]);
	if(!h[x]){//如果不是在环里的，那他能到的总隔间数就会等于它能去到的下一个隔间能去到的隔间数加1； 
		d[x]=d[father[x]]+1;
	}
	return;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>father[i];
	}
	for(int i=1;i<=n;i++){
		memset(c,0,sizeof(c));//c归零，dfs里解释了为什么； 
		if(!d[i])//要不要都无所谓； 
		dfs(i);
	}
	for(int i=1;i<=n;i++){
		cout<<d[i]<<endl;
	}
	return 0;
}
```


------------
题解只是提供个思路，在代码实现这方面还是要靠自己，所以当你下次看题解的时候不妨就只看思路，再自己实现代码，这样可能对你提升你的代码能力会更加有所帮助；

---

## 作者：寒鸽儿 (赞：4)

### 使用记忆化搜索解决问题。
### 处理vis数组使用col，不同的数字代表不同次的搜索，因而可以简单地判断情况。
### rnk数组储存每一次搜索中搜到的点的时间戳，先根据vis的col判断是否在同一遍的搜索中，如果是，则用两次时间戳的差代表环的大小。
### 使用全局变量cot来控制搜索，用它来表示回溯后的情况(是在环上还是在链上)。
### 除去以上搜索的技巧，剩余的就是模拟辣～

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

int vis[100010], rnk[100010], res[100010], target[100010], col = 1, cnt = 1, cot;

int search(int cur) {
	if(vis[cur]) {
		if(vis[cur] == col)
			return cot = cnt - rnk[cur];
		else {
			cot = 0; return res[cur];
		}
	}
	
	vis[cur] = col; rnk[cur] = cnt++;
	int t = search(target[cur]);
	
	if(cot) {
		cot--; return res[cur] = t;
	}
	else
		return res[cur] = t+1;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", target+i);
	for(int i = 1; i <= n; i++)
		if(!res[i]) {
			search(i);
			col++; cnt = 1;
		}
	for(int i = 1; i <= n; i++) printf("%d\n", res[i]);
	return 0;
}
```

---

## 作者：king_more (赞：3)

看了好多篇题解，勉勉强强懂了一点，来讲一下。

首先一个容易理解的点就是一个点要么在一条链上，要么在一个环上，所以我们分两种情况，如果在链上可以沿着找下去，直到找到一个环，加上环的值，如果一个环，直接输出就可以了。

难点在于如何找环，我们可以用tarjan算法，如果找到一个根节点，就代表发现一个新的环，将这个环里面所有的点归到这个环。

详见代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int M = 100000;
int low[M + 5],way[M + 5];
int col;
int sum;
int next[M + 5];
int ans[M + 5];
int sta[M + 5];
int top = 1;
int sh[M + 5];
int ins[M + 5];
int color[M + 5];
void tarjan(int x){
	sta[top] = x;
	top ++;
	sum ++;
	low[x] = sum;
	way[x] = sum;
	ins[x] = 1;
	if(ins[next[x]] == 0){
		tarjan(next[x]);
		low[x] = min(low[x],low[next[x]]);
	}
	else{
		if(ins[next[x]] == 1){
			low[x] = min(low[x],way[next[x]]);
		}
	}
	if(low[x] == way[x]){//如果找到一个环
		col ++;//环数量加一
		do{
			top --;
			ins[sta[top]] = -1;//已经搜过
			sh[sta[top]] = col;//全归到这个环
		}while(sta[top] != x);
		return;
	}
}
void search(int root,int x,int b){
	if(ans[x] != 0){
		ans[root] = ans[x] + b;//找到环的数目 + 已经走的步数
		return;
	}
	search(root,next[x],b + 1);
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d",&next[i]);
		if(i == next[i]){
			ans[i] = 1;//单个成环，特判
		}
	}
	for(int i = 1;i <= n;i ++){
		if(! ins[i]){//如果没有搜过就搜一下
			tarjan(i);
		}
	}
	for(int i = 1;i <= n;i ++){//统计一个环的数量
		color[sh[i]] ++;
	}
	for(int i = 1;i <= n;i ++){
		if(color[sh[i]] != 1){//如果这个环的大小不为1，说明i属于这个环。
			ans[i] = color[sh[i]];
		}
	}
	for(int i = 1;i <= n;i ++){
		if(! ans[i]){//如果ans == 0，说明ans不在环内，搜
			search(i,next[i],1);
		}
	}
	for(int i = 1;i <= n;i ++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：fy0123 (赞：3)

首先tarjan缩点，之后提供一种不用记忆化搜索的思路。

我们将缩点后的图反向地建边，由于是DAG，做一次类似拓扑排序的dp就好了。正确性显然，可手推计算一下。

（其实和记忆化也差不多的感觉。。）

贴代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<map>
#include<cctype>
#define F first
#define S second
#define pb push_back
#define mp make_pair
using namespace std;
 
const int INF = 1e9;
const double EPS = 1e-8;
 
inline int read()
{
    char ch = getchar(); int x = 0, flag = 1;
    while (!isdigit(ch)){ if (ch == '-') flag = -1; ch = getchar(); }
    while (isdigit(ch)){ x = x*10+ch-'0'; ch = getchar(); }
    return x*flag;
}
 
inline void write(int a){ if (!a) return; write(a/10); putchar('0'+a%10); }
inline void writeln(int a){ write(a); puts(""); }
 
const int N = 100010;
int n, m, cnt = 0, clk = 0, top = 0, num = 0;
int head[N], dfn[N], low[N], s[N], bel[N], w[N], x[N], in[N], dis[N];
 
struct Edge{
    int to, nex;
}e[N];
 
inline void add(int x, int y){ e[++ cnt].to = y; e[cnt].nex = head[x]; head[x] = cnt; }
 
inline void dfs(int u)
{
    dfn[u] = low[u] = ++ clk; s[++ top] = u;
    for (int i = head[u]; i; i = e[i].nex){
        int v = e[i].to;
        if (!dfn[v]){
            dfs(v);
            dfn[u] = min(dfn[u], dfn[v]);
        } else if (!bel[v]) dfn[u] = min(dfn[u], low[v]);
    }
    if (dfn[u] != low[u]) return;
    num ++;
    while (s[top] != u){
        bel[s[top --]] = num;
        w[num] ++;
    }
    bel[s[top --]] = num; w[num] ++;
}
 
int main()
{
    n = read();
    for (int i = 1; i <= n; i ++){
        x[i] = read(); add(i, x[i]);
    }
    for (int i = 1; i <= n; i ++)
        if (!dfn[i]) dfs(i);
    cnt = 0; memset(head, -1, sizeof head);
    for (int i = 1; i <= n; i ++){
        if (bel[i] == bel[x[i]]) continue;
        add(bel[x[i]], bel[i]); in[bel[i]] ++;
    }
    queue<int> q;
    for (int i = 1; i <= num; i ++)
        if (!in[i]){
            q.push(i);
            dis[i] = w[i];
        }
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].nex){
            int v = e[i].to; in[v] --;
            dis[v] = dis[u]+w[v];
            if (!in[v]) q.push(v);
        }
    }
    for (int i = 1; i <= n; i ++) writeln(dis[bel[i]]);
    return 0;
}
```

---

## 作者：CYJian (赞：3)

显然可以跑一边Tarjan缩点然后记忆化爆搜。。

虽然可以不用Tarjan，

那就当是重新练练Tarjan了。

直接贴代码。

下面有注释。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100000;

int n;
int to[N + 1];
int col[N + 1];
int dis[N + 1];
int dnf[N + 1];
int low[N + 1];
int nex[N + 1];
int res[N + 1];
bool in[N + 1];
int S[N + 1];
int top;
int tot;
int T;

void Tarjan(int x) {
	S[++top] = x;
	in[x] = 1;
	dnf[x] = low[x] = ++T;
	if(!dnf[to[x]]) {
		Tarjan(to[x]);
		low[x] = min(low[x], low[to[x]]);
	}
	else if(in[to[x]])
		low[x] = min(low[x], dnf[to[x]]);
	if(dnf[x] == low[x]) {
		int f = 0;
		tot++;
		while(f != x) {
			f = S[top--];
			dis[tot]++;
			in[f] = 0;
			col[f] = tot;
		}
	}
}//Tarjan缩点

int get_res(int x) {
    if(nex[x] == x) return dis[x];
    if(res[x]) return res[x];
    return res[x] = dis[x] + get_res(nex[x]);
}//记忆化，如果之前已经算过答案了就直接return

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &to[i]);
	for(int i = 1; i <= n; i++) if(!dnf[i]) Tarjan(i); //缩点
	for(int i = 1; i <= n; i++) nex[col[i]] = col[i]; //反正缩点后就是DAG，直接当做并查集来搞
	for(int i = 1; i <= n; i++) if(col[i] != col[to[i]]) nex[col[i]] = col[to[i]];//类似并查集的“认父亲”
	for(int i = 1; i <= n; i++) if(!res[col[i]]) res[col[i]] = get_res(col[i]);//查找每一个缩过点的答案
	for(int i = 1; i <= n; i++) printf("%d\n", res[col[i]]);//每一个环里的点的答案都是一样的
	return 0;
}
```

---

## 作者：_Nova (赞：2)

[[USACO08DEC]在农场万圣节Trick or Treat on the Farm](https://www.luogu.org/problemnew/show/P2921 "[USACO08DEC]在农场万圣节Trick or Treat on the Farm")

- 题目大意:

从图中第$i$号节点开始遍历,每个节点存有下一步要去的节点,当遍历的路径出现环时结束遍历并输出路径长度(边权默认为一)

~~其实是做完了题才反应过来这是张图可以跑tarjan~~(逃)

每次直接遍历肯定会$T$,考虑优化.
比较合适的优化方法就是在图上遍历的时候加个记忆化,在遍历到终点时保存路径上所有节点的答案.

考虑怎么计算这样的答案.

- 路径一定是由一条链加上一个环构成,分情况来讨论.

对于环上的节点,从任一节点出发,想要回到一个去过的节点,只能回到他自己,因为本题中每个节点至多只有一条出边,所以要走的路径长就是环的长度.

对于链上的节点,答案很显然就是从起始节点到终点的路径长减去从起始节点到路径上第i个节点的距离.

关于环的判定:用一个栈存遍历时经过的节点,当遍历到已经经过的节点时就弹栈直到便利到的节点被弹出,弹栈弹出的所有节点即为环上的节点.

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
inline ll read(){
    ll s=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
    while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
int n;
int nxt[N],cnt[N],ans[N],vis[N];	
stack<int> s;
vector<int> nd;
int dfs(int from,int now,int cnt){
    if(ans[now]) return ans[now];
    vis[now]=1;
    s.push(now);
    if(ans[nxt[now]]) {
    	for(int i=from,j=0;!ans[i];i=nxt[i],j++)
        	ans[i]=cnt+ans[nxt[now]]-j;		//遇到已经保存过答案的节点就能保存目前路径上节点的答案并退出
        return ans[from]=cnt+ans[nxt[now]];
    }
    if(vis[nxt[now]]){
        int tmp=0,node;
        do{
            node=s.top();
            nd.push_back(node);
            s.pop();
            tmp++;
        }while(node!=nxt[now]);
        for(int i=0;i<nd.size();i++){
            ans[nd[i]]=tmp;		//保存环上节点的答案
        }
        for(int i=from,j=0;!ans[i];i=nxt[i],j++){
        	ans[i]=cnt-j;	//保存链上节点的答案
        }
        return ans[from]=cnt;
    }
    return dfs(from,nxt[now],cnt+1);
}
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        nxt[i]=read();
    }
    for(int i=1;i<=n;i++){
        nd.clear();
        int ans=dfs(i,i,1);
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Register (赞：2)

### 解题思路

对于每一个点，入度有且仅有$1$

因此每一个点必定会在$1$个环或能够到$1$个环上

对于每个点的答案：

- 如果在环上，就是这个环的大小（循环完一圈回到自己）

- 不在环上，就是先到这个环上再绕一圈回到环的起点，即改点到环的距离加上那个环的大小

### 实现方法

- 首先枚举每一个点，找它所对应的环，记录该环大小，环打上标记，搜过的环不用再搜

设链总长为$k$，则时间复杂度为:$\Theta(kn)$

- 接着也是枚举每一个点，让它枚举找环，有找到的直接返回

时间复杂度也同样是:$\Theta(kn)$

该算法瓶颈为$k$，因此最坏会被卡到:$\Theta(n^2)$

所以本题数据还是水了点

### $hack$数据

https://www.luogu.org/paste/xsn8gjnc

### 代码

```cpp
#include <cstdio>
int n,s,sum,a[100001],ans[100001];
bool vis[100001],in[100001],b[100001];
int read(){
    char ch=getchar();int res=0,w=1;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
    return res*w;
}
void dfs1(int x){
	vis[x]=true;in[x]=true;
	if(vis[a[x]]&&(in[a[x]]||b[a[x]])) s=a[x];
	else dfs1(a[x]);
	in[x]=false;
}
void dfs2(int x){
	b[x]=true;sum++;
	if(!b[a[x]]) dfs2(a[x]);
	ans[x]=sum;
}
void dfs3(int x){
	if(!ans[a[x]]) dfs3(a[x]);
	ans[x]=ans[a[x]]+1;
}
int main(){
	n=read();
	for(register int i=1;i<=n;i++) a[i]=read();
	for(register int i=1;i<=n;i++)
		if(!vis[i])
		{
			dfs1(i);
			if(!b[s]) {sum=0;dfs2(s);}
		}
	for(register int i=1;i<=n;i++)
		if(!ans[i]) dfs3(i);
	for(register int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：huainan_marquis (赞：2)

昨天写了篇题解却因【重复的解法】被拒绝了，太羞耻了。

这次我思路应该不会有重复的，粗略的地看了看大家都比较长。我的代码比较短吧。

思路如下：两个数组，一个vis[],一个dat[]，vis用来存储的是深度，dat用来储存答案。这个题实际上是由一些环和一些树根挂在环上的树组成的。

不断递归，如果发现深度每次+1赋给vis，如果发现当前vis上有值，那么把他的dat赋为d-vis；把huan这个全局变量赋为true，此时每次return dat[u]；再次走到原位置（判断方法很多，这里我是采用回到原位置时已经有dat来判断）把huan这个全局变量赋为false，此时return dat[u]+1;

递归前也有个判断，如果dat有值，那么返回dat[u]+1;


```cpp
#include <iostream>
#include <cstdio>
#include <memory.h>

using namespace std;
const int maxn = 100010;

int n;
int da[maxn],vis[maxn],dat[maxn];
bool huan =false;

int dfs(int u,int d){
    if(dat[u]) return dat[u]+1;
    if(vis[u]){
        dat[u] = d- vis[u];
        huan = true;
        return dat[u];
    }
    vis[u] = d;
    int res = dfs(da[u],d+1);
    if(dat[u]) huan = false;
    if(huan) return dat[u] = res;
    return (dat[u] = res)+1;
}

int main()
{
    memset(vis,0,sizeof(vis));
    memset(dat,0,sizeof(dat));
    cin>>n;
    for(int i =1;i<=n;i++) cin>>da[i];
    for(int i =1;i<=n;i++) if(!vis[i]) dfs(i,1);
    for(int i =1;i<=n;i++) cout<<dat[i]<<endl;
    return 0;
}

```



---

## 作者：若玉 (赞：2)

## **前置**
看了几篇题解都发现不怎么能看懂  
最后也就只能自己瞎逼逼，~~而且还AC了~~...
### **题解**
接下来让我们步入正题  
~~粗略~~阅读题目我们会发现：  
每个点都只有一个出边  
  
那么我们可以发现：**其实对于每个连通图都只有一个环!!!** 
（为什么说连通图呢?因为~~仔细~~观察样例，发现并不是所有的点都是连起来的.）

一个环的话，我们就可以不用缩点等高深的算法了.  
  
1、我们先要找出每个环，并且只将这个环里面的所有点的贡献赋为环的长度。（**不用管除了环外的点**）  
（这很好处理，我们只需要一遍dfs即可）  
2、然后就是询问答案了.  
对于每个点有两种情况.  
one:本身处于环中.  
two:不处于环中.  
（~~这不是废话么~~.）  
对于one,我们直接输出刚才dfs出的长度即可.  
对于two,我们就一直找它所指向的位置,直到那个点属于一个环.  
这样我们就可以在O(n)的时间里面AC啦。
#### 代码
```.cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,len,dp[N],a[N],x,p,to[N];
bool vis[N]; 
void dfs(int t) //找环
{
	vis[t]=true;
	len++;
	a[len]=t; //a数组表示遍历过的点
	if (vis[to[t]]) //发现已经遍历过
	{
		p=len;
		x=1;
		while(a[len]!=to[t] && len>0)//x表示环的长度
		{
			x++;
			len--;
		}
		if (a[len]!=to[t]) return;
		for (int i=len;i<=p;i++) //将环里的每一个点都赋成环的长度
		  dp[a[i]]=x;
	}
	else 
	  dfs(to[t]);
}
int work(int t) //计算答案
{
	if (dp[t]) return dp[t];
	return 1+work(to[t]);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	  scanf("%d",&to[i]);
	for (int i=1;i<=n;i++)
	  if (vis[i]==false)
	  { 
	    len=0;
	    dfs(i);
	  }
	for (int i=1;i<=n;i++)
	  printf("%d\n",dp[i]=work(i));
	return 0;
}
```

	  printf("%d\n",dp[i]=work(i));
      对于这句话大家可能有疑问  
      为什么要dp[i]=work(i)呢？
      因为当前这个点的答案统计出来后，别的点如果遍历到这个点  
      就可以直接统计答案了。  
      （这也是为什么复杂度是O（n）的原因）
这样就愉快的结束了。
~~记得好评哦，亲~~~~~~

---

## 作者：可怜的小白 (赞：2)

啊，第一次写题解。。写的不大好请见谅！！
进入正题：
看完题目我们会注意到
1. 对于每一个点，它只有一个出度，一个或零个或多个入度；

1. 环在题目中的意思很凸显；

那么我们再把图画一画我们就可以得到一个~~惊天大秘密~~小结论：
其实图就是很多条链，这条链以一个环为结束，形象一点的就相当于一端是一个结的绳子，OK那么我们跑一个tarjan缩点最终我们可以把图处理成很多条普通的链，答案也很显而易见了。环上的点的答案自然等于环的大小，环外的点的答案=环的大小+环到这个点的距离。讲到这里很显然可以(个人觉得tarjan很好用)tarjan+dfs跑答案了。

我的做法是，tarjan缩点 然后 从环开始反向dfs那么就可以一次dfs跑出一条链的所有答案啦！

放AC代码~~（这才是重点）~~
```cpp
#include<bits/stdc++.h>//万能头也不大推荐。。。
//这题我之前脑残的用了邻接表存图 大家可以不模仿
using namespace std;
int n,m,num,h[1000000],fin[1000000],id[1000000],dfn[1000000],low[1000000],t,in[1000000],loop[1000000],gg,ans[1000000];
stack <int> p;//跑tarjan用
struct edge 
{
    int to,next,rev;//终点 下一条边的地址（在这题没用） 是否是反边
}e[10000000];
void readdata()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        num++;//反向存图
        e[num].to=i;
        e[num].next=h[x];
        h[x]=num;
        e[num].rev=1;//这是反边
        num++;//正向存图
        e[num].to=x;
        e[num].next=h[i];
        h[i]=num;
        e[num].rev=0;//这是正边
    }
}
void tarjan(int s)
{
    dfn[s]=low[s]=++t;//时间戳记录
    p.push(s);//进去
    in[s]=1;//标记该点已在队列 
    for(int i=h[s];i;i=e[i].next)
    {
        if(!e[i].rev)//跑正边
        {
            int o=e[i].to;
            if(!dfn[o])//还没发现 
            {
                tarjan(o);
                low[s]=min(low[s],low[o]);
            }
            else if(in[o]) low[s]=min(low[s],dfn[o]);//如果o点已经在队列中 
        }
    }
    if(dfn[s]==low[s])//则s是强连通分量的根 
    {
        gg++;
        int k;
        do
        {
            k=p.top();
            p.pop();
            in[k]=0;
            id[k]=gg;//id i 表示i点在哪一个圈内
            loop[gg]++;//将一个分量中的元素染成一色 loop 表示圈的大小
        }while(s!=k);
    }
}
void dfs_findans(int x,int fa)//当前点 点的爸爸
{
    fin[x]=1;
    if(id[x] == id[fa])//如果在同一个圈内
        ans[x]=ans[fa];//那么他们都等于圈的大小
    if(id[x] != id[fa])//如果不在同一个圈内
        ans[x]=ans[fa]+1;
    for(int i=h[x];i;i=e[i].next)
    {
        if(e[i].rev==1)//在这里跑反边
        {
            int p=e[i].to;
            if(!fin[p])//记录已经完成
            {
                dfs_findans(p,x);
			}
        }
    }
}
int main()
{
    readdata();
    for(int i=1;i<=n;i++)//跑tarjan
        if(!dfn[i])
        tarjan(i);
    for(int i=1;i<=n;i++)//这里是为了处理一下自环和只有一个点的情况
        if(loop[id[i]]==1)
            for(int j=h[i];j;j=e[j].next)
            {
                if(!e[j].rev)
                {
                    int o=e[j].to;
                    if(o!=i)//如果不是自环
                        loop[id[i]]--;//把不是自环loop的记录成0
                }
            }
    for(int i=1;i<=n;i++)
    {
        if(loop[id[i]]>=1 && !fin[i])//如果它是一个环 那么我就从他开始反向跑图记录答案
        {
            ans[i]=loop[id[i]];//直接等于环的大小
            dfs_findans(i,i);
        }
    }
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：zery (赞：2)

## 我把它单纯当模拟题来写了 （==）
  

------------
- 我们首先理解题意：牛顺着房间指示往下跑，跑到它曾经到的房间就停。首先搞定，一定有环对吧，不然不会停下。
- 理解完题意就可以开始模拟了，到过的到过的房间全部标记，并标记最先到这个房间的是哪一头牛，这样记录有什么用呢？这可以用来区分是自环还是最后一定是陷入他环，这很重要。
- 好的，策略拟定好，我们用暴力来实现这个策略，何时开始搜，房间没有牛来过就搜呗，然后下一个一个房间如果没牛到过，那头牛就去那，以此类推，最后一定会遇到下一个房间曾经有牛来过.
- 无路可走了，我们这个时候就可以判断了：(1)  如果是自己到过的，我们就找到了环内的一点po，而且是牛最早来的点，该点的ans[po]就是这个环的大小，我们记录下它的位置即可，以便等等把这个环上的值统一为ans[po];（2）如果是别的牛走过了，我们这头聪明的牛为啥要再走一遍做同样的事情馁，而且这个点的ans一定更新过，直接加上ans[next[x]]走人了。


------------

代码：（从主程序开始看吧）

```
#include<iostream>
#include<cstdlib>
#include<memory.h>
#include<math.h>
#include<stdio.h>
using namespace std;
const long N=100001;
long next[N],n,ans[N]={0},snum=0,num[N]={0},po;
bool b[N]={0};//记录有没牛来过
void read()
{
	cin>>n;
	for(long i=1;i<=n;++i)
	{
		cin>>next[i];
		ans[i]=1;  //初始化都是1；
		if(next[i]==i) //还没开始就结束的点直接筛掉
		{
		b[i]=1;
		}
	}
}
long search(long x)
{
   long res;
  res=1; //初始值是1；
  if(b[next[x]]==0)//可以往下跑
  {
  	b[next[x]]=1;//标记有牛
  	num[next[x]]=snum;//是这头牛跑的
  	res+=search(next[x]);//累加答案
  }
  else//下一个房间有牛来过
  {
  	if(num[next[x]]==num[x])//是自己跑的
  	{
  	  po=next[x];//下一个房间就是环头，ans[po]=环的大小；
		return 1;//返回
  	}
  	else
  	{
  		res+=ans[next[x]];//不是自己跑的，直接累加答案
  	}
  }
  ans[x]=res;//记忆一下，有牛跑过的房间就有值，且最优；
  return res;//返回
  
}
void doit()
{ long now;
	for(long i=1;i<=n;++i)
	{
		if(b[i]==0)//有没牛来过的点
		{
			b[i]=1; //这里得先处理，以免这就是换上点；
			snum++;//跑起来的第几头牛；
		     po=0;//记录环上点的计数器归零
		     num[i]=snum;//这个房间是第几头跑起来的牛来的
			ans[i]=search(i);//计算答案
			if(po>0)//有环！！！
			{  
				now=next[po];
				while(now!=po)//跑环并更新环
				{
					ans[now]=ans[po];
					now=next[now];
				}
			}
		}
	}
}
void print()//输出
{
	for(long i=1;i<=n;++i)
	{
		cout<<ans[i]<<endl;
	} 
}
int main()
{  
read();
doit();
print();
return 0;
} 
```

---

## 作者：LZWei (赞：2)

是一题不算太难的记忆化搜索；

先用强联通将彼此是next的点连在一起；

然后再进行记忆化搜索；

代码如下（代码不算难看）；

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define M 100010
using namespace std;
int n,a[M],ans[M],b[M],bo[M];
struct edge
{
    int to;
    int next;
};
edge e[M],e2[M];
int head[M],num;
void add(int from,int to)
{
    e[++num].to=to;
    e[num].next=head[from];
    head[from]=num;
}
int head2[M],num2;
void add2(int from,int to)
{
    e2[++num2].to=to;
    e2[num2].next=head2[from];
    head2[from]=num2;
}
int low[M],dfn[M],sta[M],vis[M],blo[M],depth,cnt,top;
void tarjan(int x)//强联通
{
    dfn[x]=low[x]=++depth;
    vis[x]=1;
    sta[++top]=x;
    for(int i=head[x];i!=0;i=e[i].next)
    {
        int to=e[i].to;
        if(dfn[to]==0)
        {
            tarjan(to);
            low[x]=min(low[x],low[to]);
        }
        else
        {
            if(vis[to]==1)
                low[x]=min(low[x],dfn[to]);
        }
    }
    if(low[x]==dfn[x])
    {
        cnt++;int j;
        while(j!=x)
        {
            j=sta[top--];
            vis[j]=0;
            blo[j]=cnt;
            b[cnt]+=1;
        }
    }
}
int dfs(int x)
{
    ans[x]=b[x];
    for(int i=head2[x];i!=0;i=e2[i].next)
    {
        int to=e2[i].to;
        if(ans[to]==0)
            ans[x]+=dfs(to);//记忆化搜索这一步，应该不算难懂；
        else
        {
            ans[x]+=ans[to];
            break;
        }
    }
    return 0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        if(i!=a[i]) add(i,a[i]);
    }
    for(int i=1;i<=n;i++)
        if(dfn[i]==0) tarjan(i);
    for(int i=1;i<=n;i++)
    {
        if(blo[i]!=blo[a[i]])
            add2(blo[i],blo[a[i]]);//以缩点建图
    }
    memset(bo,0,sizeof(bo));
    for(int i=1;i<=cnt;i++) dfs(i);
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[blo[i]]);
    return 0;
}
```

---

## 作者：反手一只MJJ (赞：2)

# Tarjan什么的我不喜欢哦。
#### **[题目传送门，冲冲冲！](https://www.luogu.org/problemnew/show/P2921)**
### 翻了一下题解,好多大佬都用了Tarjan缩点qwq，原谅我这个LJ蒟蒻不会Tarjan。
- 尽管如此，瞄了一眼题目，外加一点思考，~~发现很水~~，不用Tarjan直接走记忆化搜索okk。
- 在介绍方法前，请先过目一边下面的代码awa：
```cpp
#include<cstdio>
using namespace std;
const int N=100005;
int room[N],to[N];
int stack[N],tot=0;
int dfn[N],depth;
int sign=0;
bool ds[N];
int n;
int move(int x){
	if(room[x])return room[x];
	stack[++tot]=x;
	if(ds[x]){
		sign=++depth-dfn[x];
		return 0;
	}
	dfn[x]=++depth;
	ds[x]=true;
	room[x]=1+move(to[x]);
	ds[x]=false;
	return room[x];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&to[i]);
	for(int i=1;i<=n;++i){
		depth=0,tot=0,sign=0;
		printf("%d\n",move(i));
		if(sign==1)continue;
		int tail=stack[tot--];
		room[tail]=sign;
		while(tot&&stack[tot]!=tail){
			room[stack[tot]]=sign;
			--tot;
		}
	}
	return 0;
}
```
- 要认真浏览一遍哦，这样做是为了更好的理解下面的解释。
# 接下来是代码剖析：

```
/*变量声明(从上往下):
    N 题目最大牛棚数+5
    room[n]-n号牛棚的答案
    to[n]---n号牛棚连接的下一个牛棚的号
    stack[]-栈(纯手打,从[1]开始存)
    tot-----栈中元素数量
    dfn[n]--n号牛棚在栈中的位置
    depth---与dfn[]搭配使用，++depth来递增位置
    sign----回到某个去过的牛棚时 记下的一个标签
           (stack[],dfn[],sign搭配使用代替 Tarjan !)
    ds[n]---布尔数组 记录n号牛棚是否去过了 去过的为true
           (因为不想用memset()归false,ds[]需要回溯)
    n-------一共n个牛棚
    move(x)-当前在x号牛棚
*/
```
### <以题目的数据点为例>[题目传送门](https://www.luogu.org/problemnew/show/P2921)·如图：
![](https://cdn.luogu.com.cn/upload/pic/64520.png)

```cpp
int main(){
	scanf("%d",&n);//输入一共n个牛棚
	for(int i=1;i<=n;++i)scanf("%d",&to[i]);//输入去向
	for(int i=1;i<=n;++i){/*i号牛棚的牛开始从i号牛棚出发*/ 
		depth=0,tot=0,sign=0;//归零
		printf("%d\n",move(i));//输出答案
		if(sign==1)continue;//sign==1意味着G号牛棚连接自己G号牛棚 G∈[1,n]
		int tail=stack[tot--];//记下栈尾的牛棚号数
		room[tail]=sign;//这个牛棚的答案是sign,下面详解
		while(tot&&stack[tot]!=tail){
			room[stack[tot]]=sign;
			--tot;
		}
	}
	return 0;
}
```
### 我们来看看核心函数move():
```cpp
int move(int x){//当前在x号牛棚
	if(room[x])return room[x];//记忆化搜索
	stack[++tot]=x;//来到一个牛棚，牛棚号数压入栈中
	if(ds[x]){//判断这个牛棚来过没,来过为true
		sign=++depth-dfn[x];//记录差
		return 0;//回到去过的牛棚啦，结束i号牛的搜糖过程
	}
	dfn[x]=++depth;//如果没来过，记下x号牛棚在栈中的位置，即i号牛第dfn[x]次来到的是x号牛棚。
	ds[x]=true;
	room[x]=1+move(to[x]);//搜下一个连接的牛棚返回的值+1，同时记忆化搜索。
	ds[x]=false;//qwq回溯
	return room[x];//返回x号牛棚的答案
}
```
#### 没看懂？下面详解：
- 以1号牛棚为例：
- 1号牛从1号牛棚出发啦，所谓的出发，是先到达自己的牛棚:
- move(1)
- room[1]==0没记忆过，压入栈(如图)，来过了1号牛棚ds[1]=true。去下一个牛棚:move(to[1]),把下一个牛棚的答案(room[to[1]])加上自己当前的牛棚(+1)得到room[1]。
- ![image](https://cdn.luogu.com.cn/upload/pic/64536.png)
- to[1]=1,move(to[1])即move(1);
- room[1]==0没记忆过，压入栈(如图)，ds[1]为true意味牛牛来过了1号牛棚。sign记录上次到达1号牛棚到这次到达1号牛棚的路程(sign=1),return 0 表示旅程结束。
- ![image](https://cdn.luogu.com.cn/upload/pic/64543.png)
#### 结束i=1的牛牛的旅程。
- 以4号牛棚为例：(假设运行完i=1，直接走i=4，i=2,3未运行，room[2,3]未记忆)
- 4号牛从4号牛棚出，是先到达自己的牛棚:
- move(4)
- room[4]==0,4入栈，因为ds[4]==false,所以ds[4]=true。to[4]=3,走move(3)
- room[3]==0,3入栈，因为ds[3]==false,所以ds[3]=true。to[3]=2,走move(2)
- room[2]==0,2入栈，因为ds[2]==false,所以ds[2]=true。to[2]=3,走move(3)
- room[3]==0,3入栈，因为ds[3]==true,回到了3号牛棚。sign记录上次到达3号牛棚到这次到达3号牛棚的路程(即3所在的环的长度sign=++depth-dfn[3]=2),return 0 表示旅程结束。
- 最后得到下图，表示4号牛回到去过的3号牛棚时：
- ![image](https://cdn.luogu.com.cn/upload/pic/64548.png)
#### 结束i=4的牛牛的旅程。
#### 注意！结束了4号牛的旅程还要更新本次寻找到的环中所有牛棚的room[]。即后半部分：

```cpp
    ...
    printf("%d\n",move(i));//i=4
		if(sign==1)continue;//sign==意味着G号牛棚连接自己G号牛棚 G∈[1,n]，无需更新
		int tail=stack[tot--];//记下栈尾的牛棚号数
		room[tail]=sign;//这个牛棚的答案是sign
		while(tot&&stack[tot]!=tail){//把环中所有牛棚room[]=sign
			room[stack[tot]]=sign;
			--tot;
		}
	}
	return 0;
}
```
## 算法的正确性：
- 我们题中的环满足性质：n个点,n条(有向)边首尾相连成环如图：我们称他为 圈。（图中n-1改为n）
- ![image](https://cdn.luogu.com.cn/upload/pic/64561.png)
- 我们常说的环，即Tarjan求的环如图：
- ![image](https://cdn.luogu.com.cn/upload/pic/64563.png)
- 所以呢，我觉得可以不用Tarjan求怪可怜的'圈'，用栈就可以了。（其实和Tarjan中的栈很像）
- 补充一个小点：
- ![image](https://cdn.luogu.com.cn/upload/pic/64565.png)

---
### 蒟蒻恳求各位指点qwq
### ~~(广告,本蒟蒻开始建设Blog了awa:[点我](https://www.luogu.org/blog/134593/))~~

---

## 作者：Danny_boodman (赞：2)

首先这是一个有向图，求从一个点出发能经过的最大点数，本蒟蒻马上想到了爆搜。

但爆搜的复杂度是n方的，会T掉，所以考虑记忆化搜索。

但本题的图是有向有环图，不是有向无环图，不能直接跑搜索，所以考虑tarjan缩点重构图形成一个DAG，就可以愉快地跑记搜啦（想学tarjan的，宣传一下我的[tarjan的博客](https://www.luogu.org/blog/sincereactor/)）


顺便偷偷告诉你这题还有个好基友叫[缩点](https://www.luogu.org/problemnew/show/P3387)


```
#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
struct ss{
	int next,to;
};ss data[200010];
int n,p,timeclock,top,cnt,nex[200010];
int head[200010],dfn[200010],low[200100],instack[200010],stack[200010],belong[200010],sum[200010];
int f[200010];
void add(int a,int b)
{
	data[++p].next=head[a];
	data[p].to=b;
	head[a]=p;
}
void tarjan(int a)                        //tarjan的详解可以看我的博客哦 
{
	dfn[a]=low[a]=++timeclock;
	instack[a]=1;
	stack[++top]=a;
	for(int i=head[a];i;i=data[i].next)
	{
		int v=data[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[a]=min(low[a],low[v]);
		}
		else
		if(instack[v])
		low[a]=min(low[a],dfn[v]);
	}
	if(dfn[a]==low[a])
	{
		cnt++;
		while(stack[top+1]!=a)
		{
			belong[stack[top]]=cnt;
			instack[stack[top--]]=0;
			sum[cnt]++;
		}
	}
}
void dfs(int a)                            //f[a]表示第i个点能到达的点数 
{
	if(f[a]) return;                       //如果搜过了，就退出 
    f[a]=sum[a];
    int maxsum=0;
    for(int i=head[a];i;i=data[i].next)
    {
        if(!f[data[i].to]) dfs(data[i].to);
        maxsum=max(maxsum,f[data[i].to]);
    }
    f[a]+=maxsum;                          //记忆化 
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&nex[i]);
		add(i,nex[i]);
	}
	for(int i=1;i<=n;i++)
	if(!dfn[i])
	tarjan(i);
	memset(data,0,sizeof(data));
	memset(head,0,sizeof(head));
	p=0;
	//printf("cnt=%d\n",cnt);
	for(int i=1;i<=n;i++)           
	{
		if(belong[i]!=belong[nex[i]])     //缩点操作，将有向有环图转化为有向无环图，方便我们记搜 
		add(belong[i],belong[nex[i]]);
	}
	for(int i=1;i<=n;i++)
	{
		dfs(belong[i]);
		printf("%d\n",f[belong[i]]);
	}
	return 0;
}
```

---

## 作者：王鹏PRO (赞：1)


**来一篇Java的题解，相同的思路，受限于不同于C/C++特性，代码实现不一样。**

------------
1. 题意
- 带环无权有向图，求每个点能够访问到点的数量（包括自己），用dp[i]表示
- 标签是：动归、记忆化搜索

2. 思路
- 图中的点，分为两种 **_环上_** 和 **_环外_** 
- **_环上_** 的点，dp[i]是相同的，可用并查集合并点。
- **_环外_** 的点，dp[i]是点到环的距离+环中点的数量

所以
- 先使用拓扑排序（Topological Order）区分两种点 **_环上_** 和 **_环外_**
- 再使用并查集合并 **_环上_** 点同时计算环中的点的数量
- 然后记忆化dfs，计算 **_环外_** 的点到环的距离，从而算出dp[i]

------------
3. 不同
- 本题，N值为100,000 所以使用Java的题解不能像C/C++那样dfs使用方法递归，而要使用stack递归。 

------------
4. 注解
- 双端队列ArrayDeque<Integer> deque，我的代码中既要使用队列进行拓扑排序，又要使用栈进行递归，所以使用了ArrayDeque，既可以当队列又可以当栈使用。
- 数组idr[]保存，每个点的入度，拓扑排序从 入度为0的进行
```java
        for (int i = 1; i <= N; i++) {
            if (idr[i] == 0) deque.add(i);
        }
        while (!deque.isEmpty()) {
            int n = deque.poll();
            dp[n] = -1;//标记为环外的点
            if (--idr[path[n]] == 0) deque.add(path[n]);
        }
```
- 并查集，合并点，统计环中的点数
```java
    for (int i = 1; i <= N; i++) 
	 if(dp[i] != -1 && dp[path[i]] != -1)  union(i, path[i]);
 
  
  
    private static int find(int c) {
        if (p[c] == c) return c;
        return p[c] = find(p[c]);
    }

    private static void union(int c1, int c2) {
        int p1 = find(c1);
        int p2 = find(c2);
        if (p1 != p2) {
            p[p1] = p2;
            dp[p2] += dp[p1];
        }
    }  
```
- 记忆化dfs，计算 **_环外_** 的点到环的距离，从而算出dp[i]
```java
   for (int i = 1; i <= N; i++) if (dp[i] == -1) dfs(i);
                         
                         
   private static void dfs(int n) {
        deque.add(n);
        int num;
        while (!deque.isEmpty()) {
            num = deque.peekLast();
            if (dp[find(path[num])] > 0) {
                dp[num] = dp[find(path[num])] + 1;
                deque.pollLast();
            } else {
                deque.add(path[num]);
            }
        }
    }
```

------------
5.完全代码
```java
import java.io.*;
import java.util.ArrayDeque;

/*
1. TopologyOlder 去除链上（环外）的点
2. 并查集 算出环中的点
3. 链上（环外）的点 dfs 到环
* */
public class Main {
    private static int[] path;
    private static int[] dp;
    private static int[] p;
    private static final ArrayDeque<Integer> deque = new ArrayDeque<>();

    public static void main(String[] args) throws IOException {
       StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
        in.nextToken();
        int N = (int) in.nval;
        path = new int[N + 1];
        dp = new int[N + 1];
        int[] idr = new int[N + 1];
        p = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            in.nextToken();
            path[i] = (int) in.nval;
            idr[path[i]]++;
            p[i] = i;
            dp[i] = 1;
        }
        //Topology
        for (int i = 1; i <= N; i++) {
            if (idr[i] == 0) deque.add(i);
        }
        while (!deque.isEmpty()) {
            int n = deque.poll();
            dp[n] = -1;
            if (--idr[path[n]] == 0) deque.add(path[n]);
        }
        for (int i = 1; i <= N; i++) if (dp[i] != -1 && dp[path[i]] != -1) union(i, path[i]);
        for (int i = 1; i <= N; i++) if (dp[i] == -1) dfs(i);

        StringBuilder ans = new StringBuilder();
        for (int i = 1; i <= N; i++) ans.append(dp[find(i)]).append('\n');
        System.out.print(ans.toString());
    }

    private static int find(int c) {
        if (p[c] == c) return c;
        return p[c] = find(p[c]);
    }

    private static void union(int c1, int c2) {
        int p1 = find(c1);
        int p2 = find(c2);
        if (p1 != p2) {
            p[p1] = p2;
            dp[p2] += dp[p1];
        }
    }

    private static void dfs(int n) {
        deque.add(n);
        int num;
        while (!deque.isEmpty()) {
            num = deque.peekLast();
            if (dp[find(path[num])] > 0) {
                dp[num] = dp[find(path[num])] + 1;
                deque.pollLast();
            } else {
                deque.add(path[num]);
            }
        }
    }
}



```


---

## 作者：jhdonghj (赞：1)

##### **不用Tarjan，不用递归，不用dfn！！！**

首先，不难发现，这题的意思是求出一个有向图中的所有环的大小，并且用求出来的环的大小来更新相邻的点的最近距离，而这个最近距离就是所求的答案。

我们用d[i]表示第i只奶牛回到某一个她已经去过的隔间的最近距离。

我们可以有以下结论：

(1)环上的任何点的最近距离都是这个环的大小

d[i] = i所在的环的大小

(2)所有不在环上的点的最近距离等于这个点的下一个节点的最近距离+1

d[i] = d[nxt[i]]+1

有了这两个结论，我们就可以顺利地AC这题~~召唤神龙~~了

最后贴上代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int nxt[maxn], n, d[maxn], st[maxn], vis[maxn];
\\st为模拟栈
int dfs(int v0) {
	st[0] = 0;
	st[++st[0]] = v0;
	int v = v0, size, vt;
	while (!vis[v]) {\\如果访问到了访问过的节点，那么就是找到了环
		vis[v] = 1;
		v = nxt[v];
		st[++st[0]] = v;\\节点入栈
	}
	if (!d[v]) {\\如果这个环没有被访问过
		size = 1, vt = nxt[v];\\size记录环的大小
		while (vt != v) {\\计算环的大小
			vt = nxt[vt];
			size++;
		}
		d[vt] = size;\\标记第一个访问的节点
        \\如果单独标记，这个节点可能被漏过
		while (st[--st[0]] != v) {\\标记其他环上的节点
			vt = st[st[0]];
			d[vt] = size;\\结论(1)
		}
	}
	while (st[0] > 1) {\\标记入栈但未被访问的节点
		vt = st[st[0]];
		v = st[--st[0]];
		d[v] = d[vt] + 1;\\结论(2)
	}
	return d[v];
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> nxt[i];
	for (int i = 1; i <= n; i++)
		cout << dfs(i) << endl;
	return 0;
}

```


---

## 作者：御·Dragon (赞：1)

# 这题妥妥的并查集，看很多人用tarjan，有点大材小用了。
## 第一眼感觉题目好水，递归next去算，一分钟打出暴力代码：

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10;
int next[MAXN];
bool b[MAXN];
int n;
int num,x,y;
void work(int now){
    if(b[now])return;
    b[now] = true;
    num++;
    work(next[now]);
}
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n; i++){
        scanf("%d",&next[i]);
    }
    for(int i = 1;i <= n; i++){
        num = 0;
        memset(b,false,sizeof(b));
        work(i);
        printf("%d\n",num);
    }
    return 0;
}
```
### ~~自己%%%orz~~一提交，40QWQ

## 直入主题。既然要求路径长度，用并查集压缩就会WA。很多大佬于是都不压缩。那么蒟蒻介绍一种压缩且效率高过不压缩的方法。

# 思路：我们不难想到，对于FJ的农场，只有两种情况：

__$\color{Red}\text{一：只有环。}$__

__$\color{Red}\text{一：有环有尾巴。}$__

# 我们只要每次输入next的时候判断是否形成了环。
# 形成了环，则环中的隔间中的牛的答案就是环的大小，只要找环即可。
# 最后循环找没有答案的隔间，即不再环中而没有更新答案，那么我们可以算出：


__$\color{Blue}\text{在环外面的尾巴的答案就是：它第一个入环的祖先到它的距离加上环的距离即可}$__

## 我们虽然压缩了，但是依然要记录直接父亲，以便之后算尾巴的答案。

## 代码


```
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300000 + 10;
int dis[MAXN], fa[MAXN];
int num[MAXN], ans[MAXN];
//dis记录到祖先的距离
//fa记录直接祖先
//num记录压缩后的祖先 
int n, next; 

inline int read(){//快速读入，欢迎复制 
    int f = 1, x = 0;
    char c = getchar();

    while (c < '0' || c > '9'){
        if (c == '-')
            f = -1;
        c = getchar();
    }

    while (c >= '0' && c <= '9'){
        x = x * 10 + c - '0';
        c = getchar();
    }

    return f * x;
}

int find(int x) {//查函数 
    if(num[x] == x){//到达祖先返回 
    	return x;
	}
	//这里是路径压缩必备的
	int p = num[x];//记录原本祖先 
    num[x] = find(num[x]);//压缩 
    dis[x] += dis[p];//加上到新祖先的距离 
    return num[x];//返回 
}

int work(int x){//递归找到环 
	if(ans[x] != 0)return x;//一旦它的值不为0即已在环内，则返回 
	int p = work(fa[x]);//继续递归 
	ans[x] = ans[fa[x]] + 1;//更新到第一个入环的距离 
	return p;
}

int main() {
    n = read();//读入n 

    for(int i = 1; i <= n + 10; i++){
    	num[i] = i;//初始化自己为自己的父亲 
	}

    for(int i = 1; i <= n; i++) {
        next = read();//读入一个i的下隔间 
        if(find(next) == i) {//如果形成环 
            ans[i] = dis[next] + 1;//则在环内的点的答案即是环的大小 
            while(next != i){//更新所有在环上的点的答案 
            	ans[next] = ans[i];//记录答案 
            	next = fa[next];//到下一位 
			}
        } else {//否则不形成环 
            num[i] = next;//认祖先 
            fa[i] = next;//认爸爸 
            dis[i]++;//到祖先的距离 
        }
    }
	
	for(int i = 1;i <= n; i++){
		if(ans[i] == 0){//如果不在环内 
			work(i);//找第一个入环的点并更新 
		}
	}
	
	for(int i = 1;i <= n; i++){
		cout<<ans[i]<<"\n";//输出 
	}
	
	return 0;//end 
}
```


---

## 作者：残血夕阳 (赞：1)

本题可用tanjan先找环，
```
void tarjan(int u){
	dfn[u]=low[u]=++ti;
	stack[++top]=u;
	int v=to[u];
	if (!dfn[v]){
		tarjan(v);
		low [u]=min(low[u],low[v]);
	}else if (!col[v])low [u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]){
		col[u]=++co;
		si[co]++;
		while (stack[top]!=u){
			si[co]++;
			col[stack[top--]]=co;
		}
		top--;
	}
	return ;
}
```
接着进行记忆化搜索
```
int ans[N];
void work (int u){
	if (si[col[u]]>1) {
		ans[u]=si[col[u]];
		return;
	}
	int ne=to[u];
	int ans1=1;
	int p=0;
	while (1){
		if (ne==u){
			ans[u]=ans1;
			return;
		}
		if (ans[ne]){
			ans[u]=ans1+ans[ne];
			return;
		}
		if (si[col[ne]]>1){
			ans[u]=ans1+si[col[ne]];
			return;
		}
		ans1++;
		ne=to[ne];
//		cout<<++p<<" "<<ne<<endl;
	}
}
```
有一点需要注意的，有的边存在自环，即环大小为1，在上述的代码中将可能无限循环，我就被卡了两个点；
解决方法是读入时直接识别出来并上色，对应的ans[i]为1；

完整代码：
```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;
	char s=getchar();
	while (s<'0' or s>'9'){
		if (s=='-') f=-1;
		s=getchar();
	}
	while (s>='0'and s<='9'){
		x=(x<<3)+(x<<1)+s-'0';
		s=getchar();
	}
	return x*f;
}
const int N=200010;
const int M=200010;
int to[M];
int col[N],si[N],stack[N],top,ti,co;
int dfn[N],low[N];
void tarjan(int u){
	dfn[u]=low[u]=++ti;
	stack[++top]=u;
	int v=to[u];
	if (!dfn[v]){
		tarjan(v);
		low [u]=min(low[u],low[v]);
	}else if (!col[v])low [u]=min(low[u],dfn[v]);
	if(low[u]==dfn[u]){
		col[u]=++co;
		si[co]++;
		while (stack[top]!=u){
			si[co]++;
			col[stack[top--]]=co;
		}
		top--;
	}
	return ;
}
int ans[N];
void work (int u){
	if (si[col[u]]>1) {
		ans[u]=si[col[u]];
		return;
	}
	int ne=to[u];
	int ans1=1;
	int p=0;
	while (1){
		if (ne==u){
			ans[u]=ans1;
			return;
		}
		if (ans[ne]){
			ans[u]=ans1+ans[ne];
			return;
		}
		if (si[col[ne]]>1){
			ans[u]=ans1+si[col[ne]];
			return;
		}
		ans1++;
		ne=to[ne];
//		cout<<++p<<" "<<ne<<endl;
	}
}
int n,m;
int main(){
//	freopen("testdata.in","r",stdin);
//	freopen("ans.txt","w",stdout);
	n=read();
	int inf=N;
	for (int i=1;i<=n;i++){
		to[i]=read();
		if (to[i]==i) ans[i]=1,col[i]=++inf,si[col[i]]=1;
	}
	for (int i=1;i<=n;i++){
		if (col[i])continue;
		tarjan(i);
	}
//	for (int i=1;i<=n;i++){
//		cout<<i<<" "<<col[i]<<" "<<si[col[i]]<<endl;
//	}
	for (int i=1;i<=n;i++){
		if (ans[i]){
			printf("%d\n",ans[i]);
			continue;
		}
		work(i);
		printf("%d\n",ans[i]);
	}
	return 0;
}
```
上述代码应该还有优化的空间，欢迎指教

---

## 作者：yxchar (赞：1)

对于任何一个节点x，记它的后继节点为to[x]，若x在一个环中，则ans[x]=ans[to[x]]，若x不在环中，则ans[x]=ans[to[x]]+1，可以用dfs的方法遍历一条的路径，如果某个节点的后继在这条路径中已经被访问过，则说明这条路径可以形成环，由此求出这条路径上所有节点的答案，若某个节点的后继的答案已被求出，则这条路径上没有环，可以往前递推求出路径上所有节点的答案。
代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int ans[100010],vis[100010],to[100010],cir,rec[100010],totr;
void getans(int x){
	while(1){
	rec[++totr]=x; vis[x]=totr;
	if (ans[to[x]]){
		ans[x]=ans[to[x]]+1;
		break;
	}
	if (vis[to[x]]){
		cir=totr-vis[to[x]]+1;
		ans[x]=cir; break; 
	}
	x=to[x];
	}
	for (int i=totr-1;i>=1;i--){
		if (i>=totr-cir+1) ans[rec[i]]=ans[rec[i+1]];
		else ans[rec[i]]=ans[rec[i+1]]+1;
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d",&to[i]);
	for (int i=1;i<=n;i++)
		if (!ans[i]){
			cir=totr=0;
			memset(vis,0,sizeof(vis));
			getans(i);
		}
	for (int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：zbwer (赞：0)

算法： tarjan缩点+记忆化搜索    

分析：  
+ 为什么要用tarjan缩点呢？    

很显然题目给出的数据是一条带有环的链，位于环上的隔间都可以被奶牛走过，所以要是奶牛经过了这个环，那么这个环对答案的贡献就是环上点的个数，我们可以用tarjan先将环处理出来。

个人看法：是即缩点模板题之后的一道练手题

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define Mi return
#define manchi 0

using namespace std;
const int N = 100500;

inline int read()
{
	int num=0,w=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)) num=(num<<1)+(num<<3)+ch-'0',ch=getchar();
	Mi num*w;
}

int n,tot,Time,tot_,ans[N];bool vis[N];
int ver[N],Next[N],head[N],from[N];
int ver_[N],Next_[N],head_[N];
int dfn[N],low[N],scc[N],stac[N],cnt,num[N];

inline void add(int x,int y)
{
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
	from[tot]=x;
}

inline void tarjan(int x)
{
	low[x]=dfn[x]=++Time;
	stac[++stac[0]]=x;vis[x]=1;
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i];
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y]) 
			low[x]=min(low[x],low[y]);
	}
	if(dfn[x]==low[x])
	{
		cnt++;//cnt为缩点后点的个数 
		for(int y=stac[stac[0]--];y;y=stac[stac[0]--])
		{
			scc[y]=cnt;vis[y]=0;num[cnt]++;//num[cnt]即当前这个环(点)上有几个点
			if(y==x) break;
		}
	}
 } 

inline int dfs(int x)
{
	ans[x]=num[x];//初始贡献为环上点的个数 
	for(int i=head_[x];i;i=Next_[i])
	{
		int y=ver_[i];
		if(!ans[y])//如果没搜过就往下搜 
			ans[x]+=dfs(y);
		else{ans[x]+=ans[y];break;}	//搜过了就累加答案然后结束搜索 
	 }
	 return 0;
}

int main()
{
	n=read();
	for(int i=1,x;i<=n;i++)
		x=read(),add(i,x);
	
	//tarjan scc缩点 
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	
	//建新图 
	for(int i=1;i<=n;i++)
	{
		int x=scc[from[i]],y=scc[ver[i]];
		if(x==y) continue;
		ver_[++tot_]=y;
		Next_[tot_]=head_[x];
		head_[x]=tot_;
	}
	
	//在新图上记忆化搜索 
	for(int i=1;i<=cnt;i++)
		dfs(i);
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[scc[i]]);
	//注意输出的时候 应该是输出ans[scc[i]]即缩点后的答案 
	Mi manchi;
 }
//typed by zbwer 2019-10-31
```


---

## 作者：SummerMing (赞：0)

思路：

这个题目我们可以先把强连通分量求出来，（强连通分量：在该子图中如果v->u，那么u->v一定成立）。

然后如果一个强连通分量的点数大于等于2，说明该强连通分量成环，而等于1的强连通分量，

要么自己成环，要么直接或间接连着一个环。

那么我们先用tarjan求强连通分量，然后处理下缩点后的有向无环图就好解决了。

------------
```c
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <cmath>
#include <iomanip>
using namespace std;

typedef long long LL;
#define inf (1LL << 25)
#define rep(i,j,k) for(int i = (j); i <= (k); i++)
#define rep__(i,j,k) for(int i = (j); i < (k); i++)
#define per(i,j,k) for(int i = (j); i >= (k); i--)
#define per__(i,j,k) for(int i = (j); i > (k); i--)

const int N = 100010;
int DFN[N];
int LOW[N];
bool insta[N];
int sccno[N]; //NO.x 编号
int sccdeep[N]; //分量深度
int head[N];
bool visscc[N]; //缩点后的有向无环图
stack<int> sta;
vector<int> scc[N];
int scccnt,dfn,cnt;
int n;

struct Edge{
	int loc;
	int to;
	int next;
}e[N];

void add(int u,int v){
	e[cnt].loc = u;
	e[cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt++;
}

void tarjan(int u){

	
	DFN[u] = LOW[u] = ++dfn;
	sta.push(u);
	insta[u] = true;

	for(int o = head[u]; ~o; o = e[o].next){
		int v = e[o].to;

		if(!DFN[v]){
			tarjan(v);
			LOW[u] = min(LOW[u],LOW[v]);
		}
		else if(insta[v]){
			LOW[u] = min(LOW[u],DFN[v]);
		}
	}

	if(LOW[u] == DFN[u]){
		++scccnt;
		scc[scccnt].clear();
		while(1){	
			int v = sta.top();
			sta.pop();
			sccno[v] = scccnt; //缩点
			insta[v] = false;
			scc[scccnt].push_back(v); //缩点
			
			if(v == u) break;
		}

		sccdeep[scccnt] = scc[scccnt].size(); //包含几个点
		// cout << scccnt << " num " << sccdeep[scccnt] << endl;
	}
}

void dfs(int ucnt){

	//xcnt  属于哪一块分量

	int u = scc[ucnt][0]; //该点
	visscc[ucnt] = true;
	for(int o = head[u]; ~o; o = e[o].next){
		int v = e[o].to; //去的点
		int vcnt = sccno[v]; 
		if(v == u) break;//自己成环
		if(visscc[vcnt]) sccdeep[ucnt] += sccdeep[vcnt];
		else{
			dfs(vcnt);
			sccdeep[ucnt] += sccdeep[vcnt];
		}

		/*这里给一组数据方便理解
			5
			2
			3
			5
			1
		*/	
	}
}

void print(){

	rep(i,1,n){
		cout << sccdeep[sccno[i]] << endl;
	}
}

int main(){

	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	rep(i,1,n) head[i] = -1; //头
	cnt = 0; //边数
	int v;
	rep(u,1,n){
		cin >> v;
		add(u,v);
	}

	// rep(i,1,n){
	// 	for(int o = head[i]; ~o; o = e[o].next)
	// 		cout << i << ' ' << e[o].to << endl;
	// }

	rep(i,1,n) insta[i] = sccno[i] = DFN[i] = LOW[i] = sccdeep[i] = 0;
	scccnt = dfn = 0;
	rep(i,1,n) if(!DFN[i]){
		tarjan(i);
	}


	rep(i,1,scccnt) if(sccdeep[i] >= 2) visscc[i] = true; //点数超过2个的分量是环，先处理了
	rep(i,1,scccnt) if(!visscc[i]){
		dfs(i);
	}

	print();

	getchar(); getchar();
	return 0;
}
```


---

## 作者：Binwens (赞：0)

# 这题可以不用Tarjan!
# 可以用kosaraju！
#### 不过我更喜欢tarjan！
## 所以我们还是用Tarjan
这题是我们模拟考试的题目 还是比较好想的 
大概15分钟出正解
#### 思路：分析停止的情况：由于每个点只有一条出边，那么只有可能成环(不论是自环还是简单环）
1.暴力：从每个点出发跑dfs，直到停止，代码简单，分数困难。

### 2.Tarjan+dfs 正解
#### 对该有向图进行Tarjan缩点。
分析:SCC.SIZE>1的点，SIZE即为答案(该点**必定且仅能**经过该环上的所有点)

SCC.SIZE=1时，说明该点可以**继续向下走**，那么我们就朴素DFS,**直到碰到SCC.size>1的节点停止**。

代码可读性应该比较高，就是代码中的w数组即为size;
剩下的就是Tarjan和DFS模板了，自己揣摩下还是不难的。
上代码:(可能比较繁琐，反正考试也没想那么多，~~将就看~~)
```cpp
//a zj
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<stack>
using namespace std;
const int N=1e5+250;
inline int read() {
	int ans=0;
	char c;
	bool flag=true;
	for(; c>'9'||c<'0'; c=getchar())if(c=='-')flag=false;
	for(; c>='0'&&c<='9'; c=getchar())ans=ans*10+c-'0';
	return flag ? ans : -ans;
}
int dfn[N],low[N],cloc,c[N],cnt,w[N];
namespace G1 {
	struct Edge {
		int to,nxt;
	} edge[N];
	int head[N],tot=1;
	void add(int x,int y) {
		edge[++tot].to=y;
		edge[tot].nxt=head[x];
		head[x]=tot;
	}
	stack<int>st;
	bool ins[N];
	void tarjan(int u) {
		st.push(u),ins[u]=1;
		dfn[u]=low[u]=++cloc;
		for(int i=head[u]; i; i=edge[i].nxt) {
			int v=edge[i].to;
			if(!dfn[v]) {
				tarjan(v);
				low[u]=min(low[v],low[u]);
			} else if(ins[v]) {
				low[u]=min(low[u],dfn[v]);
			}
		}
		if(low[u]==dfn[u]) {
			int tp;
			cnt++;
			do {
				tp=st.top();
				st.pop();
				ins[tp]=0;
				w[cnt]++;
				c[tp]=cnt;
			} while(tp!=u);
		}
	}
}
int summ;
namespace G2 {
	struct Edge {
		int to,nxt;
	} edge[N];
	int head[N],tot=1;
	void add(int x,int y) {
		edge[++tot].to=y;
		edge[tot].nxt=head[x];
		head[x]=tot;
	}
	void dfs(int u) {
		if(w[u]==1)summ++;
		else {
			summ+=w[u];
			return ;
		}
		for(int i=head[u]; i; i=edge[i].nxt) {
			int v=edge[i].to;
			dfs(v);
		}
	}
}
int n;
int main() {
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout); 
	n=read();
	for(int i=1; i<=n; i++) {
		int t=read();
		if(t==i)continue;
		G1::add(i,t);
	}
	for(int i=1; i<=n; i++)if(!dfn[i])G1::tarjan(i);
	for(int u=1; u<=n; u++) {
		for(int i=G1::head[u]; i; i=G1::edge[i].nxt) {
			int v=G1::edge[i].to;
			if(c[u]!=c[v])
				G2::add(c[u],c[v]);

		}
	}
	for(int i=1; i<=n; i++)
		if(w[c[i]]==1) {
			summ=0;
			G2::dfs(c[i]);
			w[c[i]]=summ;
		}
	for(int i=1; i<=n; i++)printf("%d\n",w[c[i]]);
	return 0;
}
/*
5
3
4
2
5
3
*/
```


---

## 作者：lian_sama (赞：0)

此题有两种找环法，一种是用tarjan，一种是用记忆化搜索。

## tarjan

判断 原路径的入环dfn -− 原路径中此节点的dfn 是否大于 0

 如果这个节点不在环中，原路径的入环dfn-− 原路径中此节点的dfn +　新路径当前时间　即为新路径的入环dfn;
 
 而如果这个节点在环中，设为新路径起点。
 
 ```cpp
#include<cstdio>
#include<iostream>
#include<string.h>
#include<vector>
#include<stack>
using namespace std;
const int N=100005;
int n,anxt[N],f[N],dfn[N],low[N],last[N],acnt[N],fa[N],aa[N],tot=0,num=0,last2[N],aans[N];
bool vis[100005];
stack<int> stk;
struct node{
    int frm,to,prev;
}edge[N];
inline void add(int a, int b){
    edge[++tot]=node{a,b,last[a]};
    last[a]=tot;
}
void tarjan(int u){
    int v;
    dfn[u]=low[u]=++num;
    stk.push(u);
    vis[u]=1;
    for(int i=last[u];i;i=edge[i].prev){
        v=edge[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]){low[u]=min(low[u],dfn[v]);}
    }
    if(dfn[u]==low[u]){
        int cnt=0;  
        do{
            cnt++;
            v=stk.top();
            stk.pop();
            vis[v]=0;
            fa[v]=u; 
        }while(u!=v);
        acnt[u]=cnt; 
    }
}
int dfs(int x,int rt){
    if(fa[x]==fa[rt])return 0; 
    if(aans[x])return aans[x];
    return aans[x]=acnt[fa[x]]+dfs(anxt[x],x);
}
int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;i++){
		int num;
		scanf("%d",&num);
		add(i,num); 
		anxt[i]=num;		
	}
	for(register int i=1;i<=n;i++){
		if(!fa[i])tarjan(i);
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",dfs(i,0));		
	}
	return 0;
}

```


## 记忆化搜索

很简单不说了，找环后动规更新

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100005;
int n,anxt[N]/*点的下一个点的序号*/,aans[N]/*此点搜索经历点数*/,adep[N]/*此点深度*/;
void dfs(int t,int dep/*深度*/){
	adep[t]=dep;
	if(aans[anxt[t]]){
		aans[t]=aans[anxt[t]]+1;//记忆化搜索 
		return;
	}
	if(adep[anxt[t]]){//找到环 
		aans[t]=adep[t]-adep[anxt[t]]+1;
		int k=anxt[t];
		while(k!=t) aans[k]=aans[t],k=anxt[k]; //处理环 
	}
	else{//没找到 
		dfs(anxt[t],dep+1);
		if(!aans[t]) aans[t]=aans[anxt[t]]+1;//动规，若子树没有找到环没更新，在子树个数上加一 
	}
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>anxt[i];
	}
	for(int i=1;i<=n;i++){
		if(adep[i]==0){//如果已经搜索过的联通块里没有搜到
			dfs(i,1);//以该点为起点继续搜 
		} 
	}
	for(int i=1;i<=n;i++){
		cout<<aans[i]<<endl;//输出个数 
	}
	return 0;
}

```


---

## 作者：Social_Zhao (赞：0)

这道题就类似于某“信息传递”

我们首先用$tarjan$缩点。剩下的分类讨论

$\text{1：}$

该点在某环中。这种情况直接``cout<<cnt[col[u]];``

$\text{2：}$

该点是链结点。我们跑$dfs$

关键部分：

```cpp
void dfs(int u)
{
	if(!f[v[u]]) {//它的目标也是链
		dfs(v[u]);//继续dfs
		f[u]+=f[v[u]]+1;//加起来
	}
	else f[u]+=f[v[u]]+1;//如果他的目标不是链的话就直接加起来
}
```

其他的就没什么难点了。

先缩点，然后$dfs$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
stack<int>st;
int dfn[maxn],low[maxn],col[maxn],cn[maxn],ins[maxn];
int tim=0,cnt=0;
struct Edge {
	int to,nxt;
}edge[2*maxn];
int head[maxn];
int k=1;
int n;
int f[maxn];
int v[maxn];
void add(int from,int to)
{
	edge[k].to=to;
	edge[k].nxt=head[from];
	head[from]=k++;
}
void tj(int u)//tarjan
{
	dfn[u]=low[u]=++tim;
	st.push(u);
	ins[u]=1;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(!dfn[v]) {
			tj(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v]) {
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]) {
		col[u]=++cnt;
		cn[cnt]++;
		while(st.top()!=u) {
			col[st.top()]=cnt;
			cn[cnt]++;
			st.pop();
		}
		st.pop();
	}
}
void dfs(int u)
{
	if(!f[v[u]]) {
		dfs(v[u]);
		f[u]+=f[v[u]]+1;
	}
	else f[u]+=f[v[u]]+1;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>v[i];
		add(i,v[i]);
		if(i==v[i]) f[i]=1;//自环，不加则wa（10）
	}
	for(int i=1;i<=n;i++) {
		if(!dfn[i]) tj(i);
	}
	for(register int i=1;i<=n;i++) {
		if(cn[col[i]]!=1) f[i]=cn[col[i]];
	}
	for(register int i=1;i<=n;i++) {
		if(!f[i]) dfs(i);//dfs
		cout<<f[i]<<endl;//输出
	}
}
```

---

## 作者：Tanktt (赞：0)

尽管这道题有很多解法，但我扫了一遍题解发现我打的是最复杂的Tarjan缩点+拓扑+DP。

这道题我一开始没有缩点，结果连样例都没有过。第二天再看才知道需要缩点，记录每个点中牛棚的个数。然后我们就可以拓扑，求出从每个牛棚开始，能经过牛棚的个数。注意我们在缩点之后的连边需要反向。

其实这道题也比较水，思路比较明细，代码也几乎是模板，大家应该也能用这种~~垃圾~~方法顺利解决QWQ~~
```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=100012;
queue<int> q;
int ti,dfn[N],low[N],stack[N],top,n,in[N];
int edge,nex[N],head[N],vet[N],edge1,nex1[N],head1[N],vet1[N];
int ans[N],belong[N],col;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') x=x*10+c-48,c=getchar();
	return x*f;
}
inline void addedge(int u,int v)
{
	nex[++edge]=head[u];
	head[u]=edge;
	vet[edge]=v;
}
inline void dfs(int u)//缩点
{
	dfn[u]=low[u]=++ti;
	stack[++top]=u;
	int e,v;
	for (e=head[u];v=vet[e],e;e=nex[e])
	{
		if (!dfn[v])
		{
			dfs(v);
			low[u]=min(low[u],low[v]);
		}
		else if (!belong[v]) low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]==low[u])
	{
		belong[u]=++col;
		ans[col]++;
		while (stack[top]!=u)
		{
			belong[stack[top]]=col;
			ans[col]++;
			top--;
		}
		top--;
	}
}
inline void addedge1(int u,int v)
{
	nex1[++edge1]=head1[u];
	head1[u]=edge1;
	vet1[edge1]=v;
}
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	addedge(i,read());
	for (int i=1; i<=n; i++)
	if (!belong[i]) dfs(i);
	for (int i=1; i<=n; i++)
	{
		int e,v;
		for (e=head[i];v=vet[e],e;e=nex[e])
		if (belong[i]!=belong[v])
		{
			addedge1(belong[v],belong[i]);//是从v连到i
			in[belong[i]]++;
		}
	}
	for (int i=1; i<=col; i++)
	if (!in[i]) q.push(i);
	int u;
	while (!q.empty())
	{
		int e,v,u=q.front();q.pop();
		for (e=head1[u];v=vet1[e],e;e=nex1[e])
		{
			ans[v]+=ans[u];
			in[v]--;
			if (!in[v]) q.push(v);
		}
	}
	for (int i=1; i<=n; i++) 
    printf("%d\n",ans[belong[i]]);
    //ans存储的是缩点之后的点个数，所以是belong[i]
}
```

---

## 作者：vct170017 (赞：0)

单纯觉得代码好看而已

做法跟noip2015那道是一回事，处理答案注意下

然后stack。。别用queue。。就行了
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<stack>
const int N=100010;
using namespace std;
int link[N],vis[N],ans[N],n,cnt;
stack<int>Q;
void Q_pop(int u)
{
	int res=0;stack<int>P;
	while(Q.top()!=u)P.push(Q.top()),Q.pop(),res++;
	P.push(Q.top()),Q.pop(),res++;
	while(!P.empty())ans[P.top()]=res,P.pop();
}
void dfs(int u)
{
	Q.push(u);
	vis[u]=cnt;
	if(!vis[link[u]])dfs(link[u]);
	if(!ans[link[u]] && vis[link[u]]==cnt){Q_pop(link[u]);return ;}
	if(!ans[u])ans[u]=ans[link[u]]+1;
	return ;
}
void solve()
{
	for(int i=1;i<=n;i++)
	if(!vis[i])
	{
		++cnt;
		dfs(i);
	}
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
}
void In()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&link[i]);
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	In();solve();
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```

---

## 作者：cn_lemon (赞：0)

我们可以用栈来维护

走一格就进栈一个，如果下一个在栈中就出现了环，而且不可能出现环套环（每一个点只有一个出度）那么就把这个环全部出栈，统计数量，并清空栈，每一个元素的权值是其后继加一。如果下一个元素不在栈中但已经访问过，那么就更新权值（后继加一）并清空栈。
//代码颜值较低，大家绕一绕就知道数组里面是什么了嘿嘿嘿

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e5+10;
int n;
int nex[maxn];
int s[maxn],l;
int vis[maxn];
int ans[maxn],fun[maxn],ansl;
void fuck()
{
	for(register int i=1;i<=n;++i)
	if(!vis[i])
	{
		s[++l]=i;
		while(l)
		{
			int u=s[l];
			if(!vis[nex[u]])
			{
				vis[s[l]]=1;
				s[++l]=nex[u];
				continue;
			}
			else if(vis[nex[u]]==1)
			{
				int t=nex[u];
				++ansl;
				while(t!=s[l])
				{
					fun[s[l]]=ansl;
					vis[s[l]]=2;
					++ans[ansl];
					--l;
				}
				fun[t]=ansl;
				++ans[ansl];
				vis[t]=2;
				--l;
				while(l)
				{
					++ansl;
					fun[s[l]]=ansl;
					vis[s[l]]=2;
					ans[ansl]=1+ans[fun[nex[s[l]]]];
					--l;
				}
			}
			else if(vis[nex[u]]==2)
			{
				while(l)
				{
					++ansl;
					fun[s[l]]=ansl;
					vis[s[l]]=2;
					ans[ansl]=1+ans[fun[nex[s[l]]]];
					--l;
				}
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
		scanf("%d",&nex[i]);
	fuck();
	for(register int i=1;i<=n;++i)
		printf("%d\n",ans[fun[i]]);

	return 0;
}


```

---

## 作者：lemonaaaaa (赞：0)

#此题也可以用tarjan缩点#

由题意可得每个牛到了一个牛棚后下一个只能去后继牛棚

那么我们可以用tarjan先预处理出来，然后再用记忆化搜索统计答案

**一定要用记忆化搜索，否则会超时6个点**

代码如下“

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=200005;
int n,x,k=0,head[maxn],dfn[maxn],low[maxn],color_num=0,dfs_num=0;
bool visit[maxn];int ans[maxn];
int stack[maxn],top=0,val[maxn],head_new[maxn],color[maxn];
struct node
{
    int to,next;
} edge[maxn<<1],edge_new[maxn<<1];
void add(int u,int v)
{
    edge[++k].to=v;
    edge[k].next=head[u];
    head[u]=k;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++dfs_num;
    visit[x]=true;stack[++top]=x;
    for(int i=head[x];i;i=edge[i].next)
    {
        if(!dfn[edge[i].to])
        {
            tarjan(edge[i].to);
            low[x]=min(low[x],low[edge[i].to]);
        }
        else if(visit[edge[i].to]) low[x]=min(low[x],dfn[edge[i].to]);
    }
    if(low[x]==dfn[x])
    {
        visit[x]=false;color_num++;
        while(stack[top+1]!=x)
        {
            val[color_num]++;
            visit[stack[top]]=false;
            color[stack[top]]=color_num;
            top--;
        }
    }
}

void add_new(int u,int v)
{
    edge_new[++k].to=v;
    edge_new[k].next=head_new[u];
    head_new[u]=k;
}
void dfs(int x)
{
    if(ans[x]) return;
    ans[x]+=val[x];
    for(int i=head_new[x];i;i=edge_new[i].next)
    {
        dfs(edge_new[i].to);
        ans[x]+=ans[edge_new[i].to];
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        add(i,x);
    }
    k=0;
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++)
    {
        for(int j=head[i];j;j=edge[j].next)
        {
            if(color[i]!=color[edge[j].to])
            {
                add_new(color[i],color[edge[j].to]);
            }
        }
    }
    for(int i=1;i<=n;i++) dfs(color[i]);
    for(int i=1;i<=n;i++) printf("%d\n",ans[color[i]]);
    return 0;
}
```

---

## 作者：万弘 (赞：0)

由于每个点恰有一条出度，所以这是一片基环内向树森林

>  基环内向树：一个恰有一个环且其他点都指向该环的连通图

显然，对其拓扑排序后就只剩下环了（觉得不够显然可以私信我），然后求剩余的环的长度，对于不在环上的点记搜即可

```cpp
#include<cstdio>
#include<vector>

typedef long long ll;
ll read()
{
    ll f=1,x=0;
    char c;
    do
    {
        c=getchar();
        if(c=='-')f=-1;
    }while(c<'0'||c>'9');
    do
    {
        x=x*10+c-'0';
        c=getchar();
    }while(c>='0'&&c<='9');
    return f*x;
}

#define maxn 100010
#define INF (1ll<<58)

ll n;
ll v[maxn],din[maxn],f[maxn];//到达的点，入度，每个点的答案

ll q[maxn],h=1,t=1;
void topo()//拓扑排序
{
    for(ll i=1;i<=n;++i)
        if(!din[i])q[t++]=i;
    while(h<t)
    {
        ll u=q[h++];
        if(!--din[v[u]])q[t++]=v[u];
    }
}

void calc(ll u)//求环长
{
    ll t=v[u],cnt=1;
    while(t!=u)
    {
        t=v[t];
        ++cnt;
    }
    f[u]=cnt;
    t=v[u];
    while(t!=u)
    {
        f[t]=cnt;
        t=v[t];
    }
}
ll dfs(ll u)//处理不在环上的点
{
    if(f[u])return f[u];
    else return f[u]=dfs(v[u])+1;
}
int main()
{
    n=read();
    for(ll i=1;i<=n;++i)
    {
        ll t=read();
        v[i]=t;
        ++din[t];
    }
    topo();
    for(ll i=1;i<=n;++i)
        if(din[i]&&!f[i])
            calc(i);
    for(ll i=1;i<=n;++i)
        if(!din[i])
            dfs(i);
    for(ll i=1;i<=n;++i)
        printf("%lld\n",f[i]);
    return 0;
}
```

---

## 作者：smzzl (赞：0)

#  题解tarjan？？？

### 这题直接就记忆化dfs嘛

### 观察可以发现，不存在环套环

### 那就非常简单了啊就有一个手动栈来做环就好了，遇到栈里出现的就把这位到栈顶的全出来计入size然后计入ans数组

### 然后我代码里面那个对k取负数就是记录前面是因为记忆化的答案还是因为遇环跳出




    
```cpp
#include<iostream>
using namespace std;
int sta[100004],l;
int temp[100005],tl;
int b[100005];
int n;
int _next[100005];
int ans[100005];
int dfs(int);
int main()
{
    cin>>n; 
    for (int i=1;i<=n;i++) cin>>_next[i];
    for (int i=1;i<=n;i++)
        {
            if (b[i]==0)
               {
                     dfs(i);
               }
        }
    for (int i=1;i<=n;i++) cout<<ans[i]<<endl;
}
int dfs(int k)
{
    if (ans[k]!=0) return ans[k];//记忆化
    if (b[k]==1) return -1*k;//遇环
    sta[++l]=k;//手动栈
    b[k]=1;
    int sp=dfs(_next[k]);
    int size=0;
    if (sp<0) 
       {
            if (-1*sp!=k) return sp;
            if (-1*sp==k)
               {
                   while (sta[l]!=k)
                      {
                           temp[++tl]=sta[l];
                           l--;
                           size++;
                   }
                //cout<<k<<" "<<size<<endl;
                temp[++tl]=sta[l];
                l--;
                size++;
                for (int i=1;i<=tl;i++) ans[temp[i]]=size;
                tl=0;
            }
        return size;//记录size录进ans答案数组
       }
    if (sp>=0) return ans[k]=sp+1;//如果是因为找到答案则直接返回
}
```

---

## 作者：ZGS_WZY (赞：0)

如果这个点在环中的话，那么对于这个点的答案就是换的大小
(**~~显而易见~~**)

如果这个点不在环中的话，那么对于这个点的答案就是它到环的距离再加上该换的大小（可以证明这样的点最多只能到达得了一个环）

（的确和楼上那位大佬的想法差不多，~~但实现的就不一样了~~）

具体细节可以看程序

如果还有疑问或想hack的当然欢(**ju**)迎(**jue**)
```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
using namespace std;
int ans[100010];

struct wzy{
    int nxt,vertice;
}edge[100010];
int head[100010];int len=0;
void add_edge(int x,int y){
    edge[++len].nxt=head[x];edge[len].vertice=y;
    head[x]=len;return;
}

int temp=0;int tempx=0;
queue<int>v;
bool vis[100010];
void dfs(int x){
    vis[x]=1;
    for(int i=head[x];i;i=edge[i].nxt){
        int nop=edge[i].vertice;
        if(nop==x){ans[nop]=1;continue;}
        if(ans[nop]){ans[x]=ans[nop]+1;continue;}
        if(vis[nop]){
            temp=1;tempx=nop;v.push(tempx);
            return;
        }
        dfs(nop);
        if(tempx){temp++;v.push(nop);}
        if(tempx==x){
            while(!v.empty()){
                ans[v.front()]=temp;v.pop();
            }   
            tempx=0;temp=0;
            continue;
        }
        if(!ans[x])ans[x]=ans[nop]+1;
    }
    vis[x]=0;
    return;
}
int main(){
    int n;scanf("%d",&n);
    rep(i,1,n){
        int x;scanf("%d",&x);
        add_edge(i,x); 
    }

    rep(i,1,n){
        if(!ans[i])dfs(i);
    }

    rep(i,1,n){
        printf("%d\n",ans[i]);
    }
    return 0;
}
```

---

