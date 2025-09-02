# [POI 2014] FAR-FarmCraft

## 题目描述

在一个叫做比特村的小村庄中，有 $n-1$ 条路连接着这个村庄中的全部 $n$ 个房子。

每两个房子之间都有一条唯一的通路。这些房子的编号为 $1$ 至 $n$。

$1$ 号房子属于村庄的管理员比特安萨尔。

为了提升村庄的科技使用水平，$n$ 台电脑被快递到了比特安萨尔的房子。每个房子都应该有一台电脑，且分发电脑的任务就落在了比特安萨尔的肩上。

比特村的居民一致同意去玩农场物语这个游戏的最新快照版，而且好消息是他们很快就要得到他们最新的高配置电脑了。

比特安萨尔将所有电脑都装在了他的卡车上，而且他准备好完成这个艰巨的任务了。

**他的汽油恰好够走每条路两遍。**

在每个房子边，比特安萨尔把电脑贴心的配送给居民，且立即前往下一个房子。（配送过程不花费任何时间）

只要每间房子的居民拿到了他们的新电脑，它们就会立即开始安装农场物语。安装农场物语所用的时间根据居民的科技素养而定。幸运的是，每间房子中居民的科技素养都是已知的。

在比特安萨尔配送完所有电脑后，他会回到他自己的 $1$ 号房子去安装他自己的农场物语。

用卡车开过每条路的时间恰好是 $1$ 分钟，而居民开电脑箱的时间可以忽略不计。（因为他们太想玩农场物语了）

请你帮助比特安萨尔算出从开始配送到所有居民都玩上了农场物语的最少时间。

## 样例 #1

### 输入

```
6
1 8 9 6 3 2
1 3
2 3
3 4
4 5
4 6
```

### 输出

```
11
```

# 题解

## 作者：nofind (赞：45)

题意:https://www.luogu.org/problem/P3574

$f[x]$表示$x$子树内的最大值,$size[x]$表示走完$x$的子树后回到$x$的总时间

$f[x]=max(f[x],f[y]+size[x]+1)$($size[x]$存的是走完y之前的子树后回到$x$的时间)($+1$是从$x$到$y$的花费)

但是这样f的取值和遍历子树的顺序有关,于是考虑贪心

对于两个相邻(遍历时)的子树$y$和$z$,$y$前,$z$后

不交换:

$f[x]=max(f[x],size[x]+max(f[y],f[z]+size[y]+2)+1)$

交换:

$f[x]=max(f[x],size[x]+max(f[z],f[y]+size[z]+2)+1)$

如果交换比不交换优:

$max(f[z],f[y]+size[z]+2)<max(f[y],f[z]+size[y]+2)$

由于$f[z]<f[z]+size[y]+2,f[y]<f[y]+size[z]+2$

所以上式即为:

$f[y]+size[z]\not{+\not2}<f[z]+size[y]\not{+\not2}$

转化一下即为:$size[z]-f[z]<size[y]-f[y]$

排序即可

注意最后和size[1]+val[1]取max

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=5000010;
int n,cnt;
int val[maxn],head[maxn],f[maxn],size[maxn],tmp[maxn];
struct edge
{
	int to,nxt;
}e[maxn<<1];
inline bool cmp(int x,int y){return size[x]-f[x]<size[y]-f[y];}
inline void add(int u,int v)
{
	e[++cnt].nxt=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}
void dfs(int x,int fa)
{
	if(x!=1)f[x]=val[x];
	for(int i=head[x];i;i=e[i].nxt)if(e[i].to!=fa)dfs(e[i].to,x); 
	int tot=0;
	for(int i=head[x];i;i=e[i].nxt)if(e[i].to!=fa)tmp[++tot]=e[i].to;
	sort(tmp+1,tmp+tot+1,cmp);
	for(int i=1;i<=tot;i++)f[x]=max(f[x],f[tmp[i]]+size[x]+1),size[x]+=size[tmp[i]]+2;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dfs(1,0);
	printf("%d",max(f[1],size[1]+val[1]));
	return 0;
}
```

---

## 作者：SunnyYuan (赞：42)

UPDATE 2024/9/27：

1. 修复图片。
2. 修复公式。

---

洛谷上面的题解写的真的不太好，有很多错误，我来谈谈自己的理解。

设 $f(i)$ 表示**以 $i$ 为根节点的子树**中（包括节点 $i$）的所有人安装好游戏所需要的时间（与下面的 $g(i)$ 并没有包含关系，管理员也没有强制性要求要回到根节点，比如会出现下图情况）。

设 $g(i)$ 表示从 $i$ 开始往下走，兜一圈又回到 $i$ 所需要的时间。

**实际上 $f(i)$ 可能小于 $g(i)$，比如当出现如下情况的时候：**

假设下图中所有人的安装时间为 $1$，

那么当管理员兜了一个圈，第二次到达 $3$ 的时候，

所有人都已经安装完成了。

所以在此图中 $f(1) < g(1)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/m5c03ame.png)

那我们先访问那个节点呢？

分为两种情况考虑，即 $f(i) - g(i) \geq 0$ 和 $f(i) - g(i) < 0$ 两种情况。

>  如果管理员回到了起点，那些人还没有装完（即 $f(i) - g(i) \geq 0$），那么就需要等待 $f(i) - g(i)$ 的时间所有人才能安装好。
>
>  根据常识，在等待的这段时间我们可以去下一家，以减少所需的总时间。
>
> 这里我们利用贪心，让需要等待时间最久的作为第一个访问的节点，
>
> 这样可以让管理员在那漫长的安装时间内将电脑送给其他人。

>  而如果出现了像上图一样的情况（即 $f(i) - g(i) < 0$） 的情况，
>
> **根本就不需要等待，**
>
> **也就不用排序，**
>
> 随机访问即可，
>
> 但为了简单起见，
>
> 排了序也没有什么问题。

所以我们可以对 $f(i) - g(i)$ 从大到小进行排序。

再挨个访问即可。

然后就是利用 $f$ 和 $g$ 来用子树信息更新父亲节点。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/zyfj80k9.png)

先说结论：只安装到 $i$ 点会需要 $\sum (g(j) + 2) + 1 + f(i)$ 的时间能完成安装，其中 $j$ 为比 $i$ 先遍历到的同一层的节点（如上图）。

为什么是这样呢？

第一部分的 $\sum (g(j) + 2)$ 表示遍历完所有 $j$ 子树的节点，每次都回到根节点（所以要 $+2$）。

第二部分的 $+1$ 表示从根节点走到 $i$ 所需要的步骤（即为 $1$ 步）。

最后一部分的 $f(i)$ 表示把 $i$ 子树内所有的游戏装好了需要花的时间。

总时间取 $\max$ 即可， 即 $f(\text{root}) = \max\{\sum (g(j) + 2) + f(i) + 1\}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 500010;

struct edge {
	int to, next;
}e[N * 2];

int head[N], idx;

void add(int a, int b) {
	idx++;
	e[idx].to = b;
	e[idx].next = head[a];
	head[a] = idx;
}

int n, t[N];
int f[N], g[N];

void dfs(int u, int fa) {
	vector<int> wait;
	for (int i = head[u]; i; i = e[i].next) {
		int to = e[i].to;
		if (to == fa) continue;
		dfs(to, u);
		wait.push_back(to);
	}
	sort(wait.begin(), wait.end(), [](const int& a, const int& b) { return f[a] - g[a] > f[b] - g[b]; });
	for (int i = 0; i < wait.size(); i++) {
		f[u] = max(f[u], g[u] + 1 + f[wait[i]]);
		g[u] += g[wait[i]] + 2;
	}
	if (t[u] > g[u] && u != 1) f[u] = max(f[u], t[u]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (int i = 1; i <= n; i++) cin >> t[i];
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		add(a, b), add(b, a);
	}
	dfs(1, 0);
	cout << max(f[1], g[1] + t[1]) << '\n';
	return 0;
}
```

---

## 作者：Blue_wonders (赞：19)

## 一个不基于数学式子的贪心
#### 以小推大，基于图的贪心

## 思路
1. 看完题我们会发现这是颗树，每条路都会走两遍，所以路径长度我们可以最后计算
2. 然后我们不难想到答案肯定是(路径长度*2+遍历完成后还没有安装完的时间)

------------


## 推导
![](https://cdn.luogu.com.cn/upload/image_hosting/y5qw1mbi.png)

如果题目的图是这样的，那么我们很好考虑，肯定让安装时间长的子树先遍历(遍历顺序为:1->3->1->2->1)，这个顺序是一定的，我们稍微想一下就可以知道，如果不这么做，遍历的总时间一定，大的点如果后遍历就会超过遍历时间越多，从而使答案增大

但是手玩之后我们发现答案(11)并不是3号点贡献的，而是2号点

所以我们必须要考虑**选择最大点之后还会遍历其他点**

所以我们需要记录一个edge数组 代表这个点之后有多少条边

然后每遍历一个子节点，就要更新安装时间的最大值
```
过程大概是：
3最大，所以3先到1，3号点安装时间剩下8，
然后他需要遍历一遍2以及（1-2）这条边
那么只剩下6单位的安装时间
而后遍历的2号点到1号点之后会剩下7单位的时间
将7返回到1节点
因为1号点最后装，所以超过时间是max(7,1)
所以答案=（边数*2+超过遍历的时间）=>>((2*2)+7)=11
```
![](https://cdn.luogu.com.cn/upload/image_hosting/nh5pup9l.png)

我们再看这个图，是在1号点之后再加上一个点

我们的遍历顺序一定是(1->2->4->2>-3->2->1)并且2一定是从第一次遍历到开始计算，这一点很显然，既然送电脑不耗时间，所以到了2不送白不送

所以2号的子节点超出的安装时间返回的时候应该和父节点超出的安装剩余时间做一个比较

2号点先被遍历，然后经过了3,4子节点的运送，所以2号剩余的时间应该为(2号点的安装时间-2号点下面的边数*2)

这样就可以求出2号点以及2号点的所有子节点遍历完成后所剩下的最大值

再将这个值返回到1节点，完成遍历
```
和第一次差不多
3,4节点返回了7
2号点本来是8，但是遍历了2号点，3号点，剩余了4
max(7,4)=7;
将7返回，
传到1号点时只有6了
再与最后安装的1号点比较
最终答案为（3*2）+6=12
```
![](https://cdn.luogu.com.cn/upload/image_hosting/usx46d0k.png)

附赠样例的图

------------


### 代码写法:
先mdfs:是求出每个点之后的所有边的条数

然后dfs：从叶节点开始每一个点都贪心用priority_queue从剩余安装时间最大的点开始遍历，每遍历一次找就和子节点取大，最后和父节点的剩余时间取大，返回，即可求得遍历完所有子树后最大的未完成安装的时间

最后和1的安装时间比较(因为1要最后安装)


------------


[AC详情](https://www.luogu.org/record/26124328)

(nlongn)复杂度

```
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#define re register int
#define oo 500010
using namespace std;
int read(){//快读，不加应该可以过
	int xxx=0,fu=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fu=-fu;ch=getchar();}
	while(ch>='0'&&ch<='9')xxx=xxx*10+ch-'0',ch=getchar();
	return xxx*fu;
}
int n,a,b,u;
vector<int>p[oo];//用可变数组双向记录边 
pair<int,int>pp;//配合priority使用，pair可以把两个值组合成一个，省去重载结构体小于号 
//本题中把子节点的权值和字节点的序号一起放入堆，自动按照权值排序
int g[oo],edge[oo];//g[i]代表每一个人的安装时间，edge[i]代表i之后所有的边的和

int mdfs(int s,int f){//dfs形式
	if(p[s].size()==1&&p[s][0]==f)return 1;
	//叶节点往后没有边，所以不赋值，但他的父节点和他有一条边，所以返回1
	for(re i=0;i<p[s].size();i++){
		if(p[s][i]==f)continue;//由于双向边所以会有一条边指向父亲，所以特判一下
		edge[s]+=mdfs(p[s][i],s);//不断累加子节点边数
	}
	return edge[s]+1;//返回他的所有子节点的边的和加上他和他父亲的那条边 
}

int ddfs(int s,int f){//dfs形式，求出每个点遍历第二遍时的权值(他及其子节点的最大安装剩余时间)
	priority_queue<pair<int,int> >q;//小根堆，贪心求最小值用 
	int ans,ansnum,u,unum;//ans，ans num是最小值及其序号，u，u num是第二小值及其序号
	if(p[s].size()==1&&p[s][0]==f)return g[s];
	//如果没有儿子,那么遍历完这个点就直接回去，所以安装时间就是权值
	for(re i=0;i<p[s].size();i++){
		if(p[s][i]==f)continue;//把指向父亲的边特判出来
		q.push(make_pair(ddfs(p[s][i],s),p[s][i]));//每个子节点的权值(最大剩余安装时间)和序号放入堆中
	}
	ans=q.top().first;ansnum=q.top().second;q.pop();//把堆中最小值赋给ans
		ans-=1;//因为ans是子节点的权值，道达父节点要走1长度的道路，所以ans--;
	while(q.size()!=0){//由于贪心，我们知道要从最大的开始遍历
		u=q.top().first;unum=q.top().second;q.pop();//把第二小的值赋给u
		u--;//同理u--;
		ans-=(edge[unum]+1)*2;
		//因为遍历完权值最大的点要去遍历权值第二大的
		//遍历第二大的点时最大的点一直会安装，权值会减小(遍历第二大的点的时间) 
		if(ans<u){//如果遍历完第二大点的时候 原来最大的点安装时间 已经小于 第二大的点
			ans=u;//那么就将最大值改为原来第二大值
			ansnum=unum;
		}
	}
	return max(ans,g[s]-(2*edge[s]));//因为贪心，所以先遍历根节点
	//所以再返回到根节点的时候 安装时间已经减少了(边的条数*2)，再和子节点取max，得出权值 
}


int main(){
	n=read();
	for(re i=1;i<=n;i++)
		g[i]=read();
	for(re i=1;i<n;i++){
		a=read();b=read();
		p[a].push_back(b);
		p[b].push_back(a);
	}//读入不多说
	mdfs(1,0);//求出edge[i](每个点之后的所有边)
	g[1]=max(ddfs(1,0),g[1]);
	//ddfs是求出遍历节点后第二次回到节点数剩余安装时间的最大值 
	//因为1节点要最后安装，所以说返回值的取max不够大，所以再和1节点的安装时间取max
	printf("%d",g[1]+2*n-2);//输出走的路径时间+剩余安装时间 
	return 0;
}
```


---

## 作者：Vocalise (赞：15)

首先这题有两个因素：遍历的顺序，和本身的权。

然后我们注意到每条边都只遍历一次，所以这就是一个 $\operatorname{Dfs}$ 序的遍历了。因此，每颗子树是相互独立的。

所以我们自然地想到树形 $\operatorname{DP}$。

然后我们尝试设计状态。一个自然的想法就是：

$g_x$ 表示从 $x$ 这棵树遍历开始经过 $g_x$ 个单位后所有人都安装完成游戏**并且，当然需要保证已经回到** $x$ 的最小值。

**注意这里表示的是从首次抵达 $x$ 计数，当然也很好理解。**

然后我们想要推出状态方程。

我们发现，一个子树的最大值可以从两个方向取到：一个是根，一个是各个子树的最大值。设当时的根是 $v$。

根的贡献自然就是本身的权，就是 $c_v$了。各个子树的最大值可以直接拿来用吗？显然不行。所以我们必须想想方程式了，看看从方程中会有什么发现。

一步步想。我们可以发现，一个子树（设为 $u$）的答案在 $v$ 的参考系下会变化的值就是遍历在 $u$ 之前的所有子树**在路上花费的时间** $+1$ 加上 $g_u$。

> 这里详细讲一下那个 $+1$ 的来头。单纯考虑从 $v$ 开始遍历其他子树然后回到 $v$ 点，这一部分我们提前考虑进在路上花费的时间了；然后花费一个单位时间从 $v$ 点到 $u$ 点。然后就进入 $g_u$ 的统计范围了。为什么从 $u$ 点回到 $v$ 点的一个时间不计入呢？这里我们有必要引入 $f_x$ 表示 从 $x$ 点开始遍历回到 $x$ 点在路上花费的时间。那么可以看出，$g_u$ 一定是 $> f_u$ 的，除非某个点的 $c$ 为 $0$，当然这是不可能的。所以，加上的一个项其实是 $\max(g_u,f_u + 1)$ 后者表示走完回去 $v$ 的时间，但是可以忽略后一项的影响。**总而言之，回去的一个时间被 $g_u$ 覆盖掉了。**

得到状态转移方程：

$$g_v=\max(c_v,g_u+f_v+1)$$

其中 $f_v$ 的推导也很简单，给出式子：

$$f_v=f_v+f_u+2$$

$+2$ 因为 $v$ 到 $u$ 一条路走两遍。

但是这样就结束了吗？并不的，$f_v$ 的值是由遍历顺序决定的。

因为是顺序问题，考虑直接上式子来推贪心方式。

设在遍历序中，$x$ 和 $y$ 是相邻的，且 $f_v$ 表示两者都未走过时的 $f_v$。

先走 $x$ 点再走 $y$ 点的贡献：

$$\max(g_x+f_v+1,g_y+(f_v+f_x+2)+1)$$

先走 $y$ 点再走 $x$ 点的贡献：

$$\max(g_y+f_v+1,g_x+(f_v+f_y+2)+1)$$

若要使 $x$ 在 $y$ 前遍历，要使上式小于下式。

$$\max(g_x+f_v+1,g_y+(f_v+f_x+2)+1)<\max(g_y+f_v+1,g_x+(f_v+f_y+2)+1)$$

$$f_v+1+\max(g_x,g_y+f_x+2)<f_v+1+\max(g_y,g_x+f_y+2)$$

$$\max(g_x,g_y+f_x)<\max(g_y,g_x+f_y)$$

当然直接用这个式子去 `sort` 也是没有问题的，不过我们可以接着分析。

若 $\max(g_x,g_y+f_x)=g_x$，则 $\because$ $g_x+f_y>g_x$ 不等式恒成立。

反之，则 $\because$ $g_y+f_x>g_y$，只需比较 $g_y+f_x$ 和 $g_x+f_y$ 了，若 $g_y+f_x<g_x+f_y$ 则原等式成立，$x$ 在前比 $y$ 在前优。

把这玩意扔进 `sort` 里面即可。在代码里写成 $g_x-f_x>g_y-f_y$

> 其实这个式子还有一种理解：就是使 $g_x-f_x$ 大的先走，因为 $g_x-f_x$ 可以说成是额外等它的时间。

到这里基本上讲完了。不过题目中有一个特殊点： $1$，即管理员的家。它并非一开始就装，而是遍历完再装。

所以进行微调，当 $v=1$ 时，方程为

$$g_v=\max(c_v+f_v,g_u+f_v+1)$$

即可。

然后就是这么麻烦的了。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

const int MAXN = 500001;

int n,c[MAXN],f[MAXN],g[MAXN];

std::vector <int> vec[MAXN];

bool cmp(const int &x,const int &y) {
	return g[x] - f[x] > g[y] - f[y];
}

void Dfs(int v,int fa) {
	std::vector <int>::iterator i;
	for(i = vec[v].begin();i != vec[v].end();i++) {
		if(*i == fa) continue;
		Dfs(*i,v);
	}
	std::sort(vec[v].begin(),vec[v].end(),cmp);
	if(v != 1) g[v] = c[v];
	for(i = vec[v].begin();i != vec[v].end();i++) {
		int u = *i; if(u == fa) continue;
		g[v] = std::max(g[v],g[u] + f[v] + 1);
		f[v] += f[u] + 2;
	}
	return;
}

int main() {
	n = read();
	for(int i = 1;i <= n;i++) c[i] = read();
	for(int i = 2,v,u;i <= n;i++) {
		v = read(), u = read();
		vec[v].push_back(u);
		vec[u].push_back(v);
	}
	Dfs(1,0);
	std::printf("%d\n",std::max(g[1],f[1] + c[1]));
    return 0;
}
```

不用开 `long long`。为了排序方便使用 `vector` 存图。

---

## 作者：liuyz11 (赞：5)

这题直接贪心显然不可行.

考虑树形dp，用 $dp_i$ 表示到 $i$ 人后，以 $i$ 为根的所有人安装完的最短时间.

对于一个节点 $u$,	假设拜访子节点的顺序为$v_1,v_2,...,v_m$，那么得到转移方程.

$dp_u = max(dp_{v_i} + 	\sum\limits_{j=1}^{i-1} sum_j)$ 

其中 $sum_i$ 表示拜访完以 $i$ 为根的子树的所有人所花的时间,即 $(size_i - 1)\cdot 2$

拜访的顺序考虑贪心

对于两个相邻整数$i,j$,必须满足$dp_j + \sum\limits_{k=1}^{j-1} sum_k < dp_i + \sum\limits_{k=1}^{i-1} sum_k + sum_j$.

$=>dp_j + sum_i < dp_i + sum_j$

$=>dp_j - sum_j < dp_i - sum_i$

所以只要将 $dp_i - sum_i$ 从大到小排序即可.

参考代码：

```cpp
#include <bits/stdc++.h>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define mp make_pair
#define clr(x, y) memset(x, y, sizeof(x))
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
const int MAXN = 500005;
const int MAXM = 1000005;

pii num[MAXN];
int cnt;
int a[MAXN], sze[MAXN], dp[MAXN], head[MAXN], nxt[MAXM], to[MAXM];

bool cmp(pii a, pii b){
	return a.fi > b.fi;
}

void addedge(int u, int v){
	nxt[cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
	cnt++;
}

void dfs(int u, int fa){
	int tot = 0, sum = 0;
	sze[u] = 1;
	dp[u] = a[u];
	for(int e = head[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if(v == fa) continue;
		dfs(v, u);
		sze[u] += sze[v];
	}
	for(int e = head[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if(v == fa) continue;
		num[++tot] = mp(dp[v] - 2 * sze[v], v);
	}
	sort(num + 1, num + tot + 1, cmp);
	rep(i, 1, tot){
		dp[u] = max(dp[u], dp[num[i].se] + sum + 1);
		sum += 2 * sze[num[i].se];
	}
}

int main(){
	clr(head, -1);
	int n;
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d", &a[i]);
	rep(i, 1, n - 1){
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y);
		addedge(y, x);
	}
	dfs(1, -1);
	printf("%d\n", max(a[1] + 2 * (n - 1), dp[1]));
	return 0;
}
```

---

## 作者：xcxcli (赞：5)

UPD:fixed bugs

[[POI2014]FAR-FarmCraft](https://www.luogu.com.cn/problem/P3574)

---
前置问题：$n$个电脑，管理员送达花费的时间是$a_i$，管理员只能一个个用户地送电脑。用户安装程序花费的时间是$b_i$，安排送电脑的顺序，使最晚安装完电脑的用户花费的时间最短。（[P1080国王游戏](https://www.luogu.com.cn/problem/P1080)的简化版）

这里对于贪心给出更严格的证明。

令$s_i$表示$a_i$的前缀和，对于序列中两个相邻的点$i,j$，

$ans=\max(s_{i-1}+b_i,s_{i-1}+a_i+b_j)=\max(b_i,a_i+b_j)+s_{i-1}$

交换两点后，

$ans'=\max(b_j,a_j+b_i)+s_{i-1}$

因为$a_i+b_j>b_j,a_j+b_i>b_i$，所以单独$b_i,b_j$与$ans$与$ans'$的大小关系无关。

就可以得到：若$a_i+b_j<a_j+b_i$，则$ans<ans'$

所以最终答案中相邻的两点必定满足$a_i-b_i<a_j-b_j$，否则交换两点可以使答案变优。

按$a_i-b_i$排序即可。

---
可以证明，当管理员进入子树$u$后，会遍历整个子树后再退出子树。

设$sz_u$表示遍历子树$u$花费的时间，$f_u$表示管理员从点$u$开始，子树中所有用户安装完程序的最小值。

对于$u$的所有子树$v$，发现其实就是解决前置问题，其中$sz_v+2$是$a_i$，$f_v$是$b_i$。

记录所有儿子并按$sz_v-f_v$排序即可。

细节：

1.不能dfs一个儿子后马上记录这个儿子，这样会被下一个儿子的儿子覆盖

2.管理员最后才给自己的电脑安装程序

3.~~不用开long long~~

```cpp
#include<stdio.h>
#include<algorithm>
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=500001;
int Max(int x,int y){return x>y?x:y;}
struct E{int v,nxt;}e[N<<1];
int n,head[N],cnt,u,v,a[N],f[N],sz[N],p[N];
bool cmp(int x,int y){return sz[x]-f[x]<sz[y]-f[y];}
void add(int u,int v){e[++cnt].v=v,e[cnt].nxt=head[u],head[u]=cnt;}
void dfs(int u,int fa){
	if(u!=1)f[u]=a[u];//管理员最后才给自己的电脑安装程序
	for(int i=head[u];i;i=e[i].nxt)if(e[i].v!=fa)dfs(e[i].v,u);
    //不能dfs一个儿子后马上记录这个儿子，这样会被下一个儿子的儿子覆盖
	int T=0;
	for(int i=head[u];i;i=e[i].nxt)if(e[i].v!=fa)p[++T]=e[i].v;//记录儿子
	std::sort(p+1,p+T+1,cmp);
	for(int i=1;i<=T;++i)f[u]=Max(f[u],f[p[i]]+sz[u]+1),sz[u]+=sz[p[i]]+2;
    //计算f[u]
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<n;++i)u=rd(),v=rd(),add(u,v),add(v,u);
	dfs(1,0),printf("%d\n",Max(f[1],sz[1]+a[1]));
    //管理员最后才给自己的电脑安装程序
	return 0;
}
```

---

## 作者：ww3113306 (赞：5)

某大佬说这题很水，而本蒟蒻，，，，做了很久，，，QAQ果然还是太弱了么

（感觉题面那一小段中文根本看不懂啊，好多条件都没讲，直接就是安装也要一个时间啊，，，明明不止啊！~~还好有百度翻译。。。。。。~~）

题意：一棵树，一开始在1号节点（root），边权都为1，每个点有点权，要最小化max(点权+到达时间） <---所有点的

首先这看起来就是一道DP题，但是根据直觉，，，应该跟贪心挂钩，因为感觉耗时久的要前去是吧

但是我们发现并不能这么弄，因为去一棵子树就要走完它，这个时候再去别的树的时候可能已经很晚了，所以就不一定优了

不过我们可以发现，从一个点出发，去节点的顺序就决定了答案

于是我们考虑排序

但是节点太多比较难以分析，因此我们先以两个儿子为例分析。

f[i]代表以i为根的最大时长，

于是目的就是最小化f[1],size[i]代表遍历这个点要多久，

因为要遍历完这个子树才可以去另一棵，于是就有转移方程：

f[i]=max(f[a],f[b] + size[a] + 2),其中a，b为两棵子树，+2是去a的那条边来回的时间，这个是先去a的，

f[i]=max(f[b],f[a] + size[b] + 2),然后就是最小化这4个式子中的最大值，

PS:等等，，，貌似是f[a]+1????，懒得改了，，，大家自行脑补成f[a]+1吧，不影响结果

于是先按照国王游戏里面的方法来推导一下:

首先设先去a比较优，

那么有max(f[a],f[b] + size[a] + 2) < max(f[b],f[a] + size[b] + 2)

因为f[a] + size[b] + 2 > f[a],f[b] + size[a] + 2 > f[b],

所以这4个式子的最大值不可能会是f[a] or f[b],

所以要使得等式成立就只能寄希望于

f[b] + size[a] + 2 < f[a] + size[b] + 2

所以以这个为条件排序即可

各种细节QAQ调了好久

```cpp
#include<bits/stdc++.h>
using namespace std;
#define R register int
#define AC 501000
#define getchar() *o++
#define LL long long
char READ[40001000],*o=READ;
int n,ans;//t;
int cost[AC],size[AC];
int date[AC * 2],Next[AC * 2],Head[AC],tot;//前向星,error!!!是双向边啊
struct point{
	int size;
	LL f;
}p[AC];
LL f[AC];
inline int read()
{
    int x=0;char c=getchar();
    while(c > '9' || c < '0') c=getchar();
    while(c >= '0' && c <= '9') x=x*10+c-'0',c=getchar();
    return x;
}

inline void add(int f,int w)
{
    date[++tot]=w,Next[tot]=Head[f],Head[f]=tot;
    date[++tot]=f,Next[tot]=Head[w],Head[w]=tot;
}

inline bool cmp(point a,point b)
{
	return b.f + a.size < a.f + b.size;
}

void pre()
{
    R a,b;
    n=read();
    for(R i=1;i<=n;i++) cost[i]=read();
    for(R i=1;i<n;i++)
    {
        a=read(),b=read();
        add(a,b);
    }
}

void DFS(int x,int fa)//还是要传father，不然的话下面加入队列的部分就判断不了了，因为这时下面都已经访问过了
{
	int now,tot=0;
	if(x != 1) f[x] = cost[x];//至少自己要装啊,但是注意第一个是最后装的
	for(R i=Head[x]; i ;i=Next[i])
	{
		now=date[i];
		if(now == fa) continue;
		DFS(now,x);
		//p[++tot].f=f[now],p[tot].size=size[now];
	//	size[x]+=size[now] + 2;
    }
    for(R i=Head[x]; i ;i=Next[i]) 
    {
    	now=date[i];
    	if(now != fa) 
    		p[++tot]=(point) {size[now],f[now]};//不能在上面加，因为一旦下一次调用了DFS，队列里就乱了
    }
    //size[x]=size[x] * 2 - 2;//因为现在还是存的有几个点，所以要改成真正的size
   // if(!size[x]) return ;//???
  //  printf("!!!%d %d\n",x,size[x]);
    sort(p+1,p+tot+1,cmp);
   // t=0;
    for(R i=1;i<=tot;i++)
    {
    	f[x]=max(f[x],p[i].f + size[x] + 1);
		//t+=p[i].size + 2;
		size[x] += p[i].size + 2;//反正这样也是统计了一样的东西
	}
	//printf("???%d\n",t);
}

int main()
{
	freopen("in.in","r",stdin);
    fread(READ,1,40000000,stdin);
    pre();
    DFS(1,0);
    printf("%lld\n",max(f[1],(LL)(n * 2 - 2 + cost[1])));
	//for(R i=1;i<=n;i++) printf("%lld\n",f[i]);
	//printf("time used... %lf\n",(double)clock()/CLOCKS_PER_SEC);
	fclose(stdin);
    return 0;
}
```

---

## 作者：dztlb (赞：3)

P3574

一个有N个节点的树，遍历整棵树一遍，在每个节点打开开关自动进行一次ti时间的操作，开开关不算时间，求最终用的最短时间。

考虑，肯定是花时间ti长的让它先开始，同时在遍历一个点时，保证这个点的父节点已经开始运行。

在具体贪心时，则：

设f(i)表示遍历i的子树所需时间。

g(i)表示遍历i的子树，且所有人都装好软件所需的最少时间。

贪心按照g(i)- f(i)从大到小的顺序遍历儿子即可。

g(i)- f(i)意为完成那棵子树多出的自由时间，这时间越长显然越优。最后回家加上根节点的值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int Max(int x,int y){return x>y?x:y;}
int n,a[500001],g[500001],f[500001],son[500001];
bool cmp(int x,int y){
	return g[x]-f[x]>g[y]-f[y];
}
int ver[1000001],nxt[1000001],h[500001];
int tot=0;
inline void add(int x,int y){
	tot++;
	ver[tot]=y;
	nxt[tot]=h[x];
	h[x]=tot;
}
inline void dfs(int u,int fa){
	if(u!=1){
		g[u]=a[u];//记录本身
	}
	for(int i=h[u];i;i=nxt[i]){
		if(ver[i]!=fa)dfs(ver[i],u);//预处理出所有子节点的f和g
	}
	int cnt=0;
	for(int i=h[u];i;i=nxt[i]){
		if(ver[i]!=fa){
			son[++cnt]=ver[i];//保存当前点的所有子节点编号
		}
	}
	sort(son+1,son+1+cnt,cmp);//按照自由时间降序排列
	for(int i=1;i<=cnt;i++){
		g[u]=Max(g[u],g[son[i]]+f[u]+1);//依次计算每一个子树再回来的时间，取最大值，因为每一家的游戏是在同时安装的，f[u]相当于是在开始遍历这颗子树时，已经遍历的其他子树所用的时间（这时只考虑走路径的时间，因为更新游戏的时间是重合的）
		f[u]+=f[son[i]]+2;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}	
	int x,y;
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	printf("%d",Max(g[1],f[1]+a[1]));//同时这个人自己需要回家装游戏
	return 0;
}
```
tips:链式前向星存图数组要开2*N



---

## 作者：wurzang (赞：2)

牛逼的 dp 题，完全做不来/kk


题意翻译翻译

$\sf wyq$ 的学校可以看做一颗树，学校的每个节点上都有一个 mm，而只有 $1$ 号点是 $\sf wyq$ 所在的出发点，$\sf wyq$ 可以走路去学校每个点给 mm 发贺卡，每个 mm 被发到贺卡后就可以收获到 $\sf wyq$ 的多项式计数法学习来学习 $c_i$ 秒钟，而 $\sf wyq$ 在给每个 mm 发完贺卡后就回自己的点去学习多项式计数法。走一条边需要消耗 $1$ 秒种，每条边至多只能走两次，问怎样走才能使大家全部学完多项式计数法的时间最小。



设状态 $f_i$ 为走出 $i$ 点之后还需要多少时间来学完多项式计数法。

很容易发现有转移方程 $f_i=\max \limits_{son \in i} (f_i-(sz_{son}-1) \times 2,f_{son}-1)$

其中前一项是表示一边走一边学习，于是剩下的时间减少，后一项是子树走上来走了1秒，这一秒是边走边学习的，于是减掉。

代码是这样的：

```cpp
	for(int i=0;i<v.size();++i)
		f[x]=max(f[x]-((sz[v[i]])<<1),max(f[v[i]]-1,0));
	f[x]=max(f[x],0);
```


那么初值就是

$$
f_i =\begin{cases}0 \ (i=1)\\ c_i \ (\operatorname{otherwise}) \end{cases}
$$

答案就是 $\max(f_1,c_1)+2 \times (n-1)$，这些都比较显然。

然后我们发现 $f_i$ 的大小其实是按照子树的转移顺序来的。然后也很显然，如果把 $i$ 的子树按 $f$ 逆序排序的话就是最优秀的。因为如果一个子树它的学习时间多的话，我们可以把它先走，剩下的子树我们可以一边走一边让它学习，这样的话我们就让一边走一边学习的时间更多，这样显然就更加高效，答案也就更加优秀。


代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500000+5;
struct edge{
	int nxt,to;
}e[N<<1];
int head[N],cnt;
void add(int x,int y){
	e[++cnt].to=y; e[cnt].nxt=head[x]; head[x]=cnt;
}
int f[N],sz[N],a[N];
bool cmp(int i,int j){
	return f[i]>f[j];
}
void dfs(int x,int fath){
	sz[x]=1;
	if(x!=1) f[x]=a[x];
	vector<int> v;
	for(int i=head[x];i;i=e[i].nxt){
		if(e[i].to==fath) continue;
		dfs(e[i].to,x);
		sz[x]+=sz[e[i].to];
		v.push_back(e[i].to);
	}
	sort(v.begin(),v.end(),cmp);
	for(int i=0;i<v.size();++i)
		f[x]=max(f[x]-((sz[v[i]])<<1),max(f[v[i]]-1,0));
	f[x]=max(f[x],0);
}
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}
int main(){
	int n,u,v;
	read(n);
	for(int i=1;i<=n;++i) read(a[i]);
	for(int i=1;i<n;++i)
		read(u),read(v),add(u,v),add(v,u);
	dfs(1,0);
	cout<<max(f[1],a[1])+2*(n-1);
	return 0;
}
```


---

## 作者：Shawk (赞：2)

[博客食用效果更佳](https://www.cnblogs.com/Z8875/p/12659848.html)

[题目传送门](https://www.luogu.com.cn/problem/P3574)

我在和[ghosh__](https://www.luogu.com.cn/user/93659)大佬讨论之后进行了一些改动

这道题可以想到是树状DP，但是具体怎么写不是很好想

每一个节点都是要遍历的，现在就是要求按什么顺序遍历最后所需的时间最少

要注意在进行各个子节点的遍历时，时间不是相加的的，可以同步进行，也就是说在进行安装的时候可以走到别的地方进行安装
这样，在选择先进入哪个子节点的时候就用到了贪心的思想，
总时间当然就是安装的时间加上走路的时间

走路的时间肯定是越来越大，要使总时间最小，如果先从等待时间短的开始，总时间就是最大安装时间再加上最大的走路时间，这个很显然，以为两个加数都是单增的

所以，先走等待时间最长的点才能使决策最优

那就把每个儿子记录下来，按等待时间从长到短排序，再进行运算

详细内容看代码注释


```
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
struct side {
    int t, next;
}e[N*2];
int head[N], tot;
void add(int x, int y) {
    e[++tot].next = head[x];
    head[x] = tot;
    e[tot].t = y;
}
int n, t[N], f[N], g[N], s[N], cnt;
//g[i]表示遍历i为根的子树的最短时间
//f[i]表示遍历完以i为跟的子树，且每人装好游戏的最短时间
bool judge(int x, int y) {
    return f[x] - g[x] > f[y] - g[y];
    //f[i]−g[i]表示等待的时间
}
void dfs(int x, int fx) {//树状DP
    if (x != 1) f[x] = t[x];//t[i]是读入的每个人安装游戏所需时间
    //1号点在第一次进入的时候是不安装游戏的，其余的点都是一进入就安装
    for(int i = head[x]; i; i = e[i].next)
        if (e[i].t != fx) dfs(e[i].t, x);
    //先遍历一边子节点
    cnt = 0;
    for(int i = head[x]; i; i = e[i].next)
        if (e[i].t != fx) s[++cnt] = e[i].t;
    //s数组记录x的儿子
    sort(s+1, s+cnt+1, judge);
    //将儿子按等待时间从大到小排序
    for(int i = 1; i <= cnt; i++) {
        f[x] = max(f[x], f[s[i]] + 1 + g[x]);
        //i=1时g[x]=0，f[s[i]]是遍历并安装完s[i]的子树的时间，
        //1是过去所用的时间，g[x]是走过前面子节点的时间，由于回去的1包含在了安装时间里（安装时间>=1）所以这里不是加2
        g[x] += g[s[i]] + 2;
        //一来一回走两遍，+2
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &t[i]);
    for(int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
        //存边
    }
    dfs(1, -1);
    printf("%d\n", max(f[1], g[1] + t[1]));
    //f[1]是完除自己外所有人安装完游戏并回到1的时间
    //g[1]+t[1]是走遍全村在安装完自己的游戏的时间
    return 0;
}
```
***
有的人可能会这样写 ~~就是我~~，但这样在递归的时候s存的就是子树所有的节点
```
    for(int i = head[x]; i; i = e[i].next)
        if (e[i].t != fx) dfs(e[i].t, x), s[++cnt] = e[i].t;
```
还有人想到在函数里定义局部变量，但这样递归下去会十分费内存，会MLE的


---

## 作者：小塘空明 (赞：2)

~~这题翻译十分感人，推荐看大视野的翻译~~

因为一条边只能经过两次，所以我们去往一个子节点就必须遍历完该子节点的子树。

所以我们可以发现，当来到一个节点x后，设f[x]表示该节点子树内的最大答案，siz[x]表示遍历完该子树所花的时间（不是大小）。显然f[x]只能被子节点y的选择顺序所影响。

所以我们就可以用贪心的思想来做这道题了。

假设遍历顺序中第i，i+1位为a，b，a在前面更优，因为1到i-1遍历总时间不会受影响，交换第i，i+1位也不会对到达第i+2个子节点的时间产生影响，所以我们可以考虑它的最优子结构。

之前遍历所花的时间为当前的siz[x]，先去a节点对f[x]的更新值为siz[x]+max（f[a]+1，f[b]+1+siz[a]+2）；先去b节点对f[x]的更新值为siz[x]+max（f[b]+1，f[a]+1+siz[b]+2）；

很明显答案不可能被f[b]+1或f[a]+1影响，因为a更优，所以以f[b]+siz[a]<f[a]+siz[b]作为排序条件对子节点进行排序。每计算完一个节点就对siz[x]进行更新。

~~我把cnt定义成全局坑了我好久。~~



---

## 作者：Su_Zipei (赞：1)

## 题意
翻译其实已经很明确了
## 分析
这题一眼就是贪心啊，但贪心的方法要思索一下，首先是考虑先走时间多的子树，但不太现实，因为时间跟点的个数也有关系，而且很有可能另外一棵子树不去走会闲置很长时间，就是这棵子树本来可以走一遍然后在子树装软件的时候去走别的树，所以不能这么贪心。那，要怎么办呢？

对于一棵子树，我们必须要走的是跑路时间，而安装可以在去别的子树走的时候干，所以我们肯定要先弄安装时间-跑路时间最大的子树，因为这样的话，我们就可以在它安装的时候去弄别的子树，证明用反证法，先弄别的子树最后时长一定大于先弄它，所以跑完每一个子树后，把它的安装时间和跑路时间扔到堆里，最后把堆取完，就完了。

状态转移方程$DP[u]=max(DP[son]+g[u]+1)$，g数组记录的跑路时间。
## 细节问题
首先呢，longlong不需要，爆不掉。

然后是加边，加单向边会出问题，加完从一号点开始可能不能走遍整张图，所以只能加双向边，加双向边数组要开2倍啊啊啊啊啊，本蒟蒻忘开然后RE了，接着我把5e5改成了6e5，还RE，然后我以为递归炸了，调了半天，我是不是傻。。。。
```
#include<iostream>
#include<algorithm>
using namespace std;
const int N=6e5+10;
struct Edge{
    int nxt,to;
}e[N<<1];
int Head[N],len;
void Ins(int a,int b){
    e[++len].to=b;e[len].nxt=Head[a];Head[a]=len;
}
struct Node{
    int f,siz;
    Node(){}
    Node(int a,int b){f=a,siz=b;}     
    bool operator < (const Node&A)const{
        return f-siz<A.f-A.siz;
    }
};
int dp[N],g[N],val[N],que[N];
void dfs(int u,int fa){
    priority_queue<Node> q;
    if(u-1)dp[u]=val[u];
    for(int i=Head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa)continue;
        dfs(v,u);q.push(Node(dp[v],g[v]));
    }
    while(!q.empty()){
        Node now=q.top();q.pop();
        dp[u]=max(dp[u],now.f+g[u]+1);
        g[u]+=now.siz+2;
    }
}
int main(){
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>val[i];
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        Ins(a,b);Ins(b,a);
    }
    dfs(1,0);
    cout<<max(dp[1],val[1]+g[1]);
    return 0;
}
```

---

## 作者：ykuouzf (赞：1)

### 来一发不一样的贪心

~~qwq调了两天才过，谨以此题解纪念一番~~

首先观察题面，可知题目给出的是一棵树，再看到（$n <= 5e5$）的数据范围，明显是不能用暴力算，考虑如何优化

再分析题意：**他的汽油恰好够走每条路两遍**

什么意思呢？若是要从根节点出发，遍历所有的节点再回到根，每条路径至少要走两遍，此处是 “ 恰好 ” ，也就是说明这样一个意思：**当访问一个子节点时，必须将以这个子节点为根的子树走完才能返回**

再看题目所求：**到达时间 + 安装时间的最大值最小**

前文已经得知每条路恰好要走两遍，可知 “ 到达时间 ” 这一条件为定值（$n - 1$）$ × 2$，那么**所求即为遍历完整棵树后剩下还未完成安装的时间**。可知以每个子节点为根的子树都能求出这样一个解

这一点就符合**每个子节点都是一个子问题**这一条件，可以想到树形$DP$：用$f(x)$表示以$x$为根的子树遍历完回到$x$剩下还未安装完成的时间

如何转换呢？考虑贪心$\Rightarrow$**从每棵子树的根节点出发，一定是先走剩余时间最大的子节点**，可以保证情况最优，请读者自行思考

又考虑到在先走这一子节点之后还需走$Size(x) - 1$（$Size(x)$指以$x$为根的子树的子节点个数）个节点，在走这些节点的时候，安装剩余时间是一直在减短的，每条路走两遍，便是$2*(Size(x)-1)$的时间，再加上从该节点走回根的时间$1$，共是$2*(Size(x)-1)+1=2*Size(x)-1$。也可以这么考虑，走完以$x$为根的子树共需$2×Size(x)$的时间，除走向该子节点的第一步外，其余都会为其减短时间，故为$2×Size(x)-1$

以此写出转移方程：$f(x)=max(f(x),f(y))(y\in son(x))-(2×Size(x)-1)$

然而这只适用于叶子节点的转换，还要考虑到根节点的情况。因根节点在一开始就遍历到了，减短的安装时间就为$2×Size(x)$，故方程：$f(x)=max(f(x),c(x)-2*Size(x))$

代码就很好写了：

```
#include <bits/stdc++.h>

#define re register
#define li inline

li int read() {
	re int f, j; re char c;
	for (f = 1, c = getchar(); !isdigit(c); f = c == '-' ? -1 : 1, c = getchar());
	for (j = 0; isdigit(c); j = (j << 1) + (j << 3) + (c ^ 48), c = getchar());
	return f * j;
}

li void write(re int x) {
	if (x < 0) { putchar('-'); x = -x; }
	if (x > 9) { write(x / 10); } putchar(x % 10 + '0');
}

const int N = 5e5 + 10;

struct Edge {
	int next, to;
} e[N << 1];

int n, tot;
int head[N], c[N], Size[N], f[N];

li void add(re int x, re int y) { //链式前向星不多说 
	e[++tot].to = y; e[tot].next = head[x]; head[x] = tot;
	e[++tot].to = x; e[tot].next = head[y]; head[y] = tot;
}

li void update(re int x, re int fa) { //求Size[]
	for (re int i = head[x]; i; i = e[i].next) {
		re int y = e[i].to;
		if (y == fa) { continue; }
		update(y, x);
		Size[x] += Size[y] + 1;
	}
}

li void dfs(re int x, re int fa) {
	for (re int i = head[x]; i; i = e[i].next) {
		re int y = e[i].to;
		if (y == fa) { continue; }
		dfs(y, x);
		f[x] = std::max(f[x], f[y]);
	} if(x != 1) { //特判x = 1的情况（因1是最后安装的
    	f[x] = std::max(f[x] - 2 * Size[x] + 1, c[x] - 2 * Size[x]);
   	}
}

signed main() {
	n = read();
	for (re int i = 1; i <= n; i++) { c[i] = read(); }
	for (re int i = 1; i < n; i++) {
		re int x = read(), y = read(); add(x, y);
	} update(1, 1); dfs(1, 1);
	write(std::max(f[1] - 1, c[1]) + (n - 1) * 2); //这里的-1是减去从1的子节点走回1的这步 
	return 0;
}
```

可这是错误的，只有[30分](https://www.luogu.com.cn/record/37024725)

那么问题出在哪里呢？来看这样一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fe2uh0lo.png)

如若是按上述的计算，答案应为$9-2×3+1=4$，可实质上最大剩余时间应为$7-1=6$，由4号节点提供。可知上述推论从大到小遍历的思想并没有错，**答案却不一定来源于最大的子节点**，因此，还需将根$x$所有的子节点按从大到小的顺序排序，再进行比较。于是我们就会想到这玩意$\downarrow$

$priority-queue < pair <int, int> > q;$

若是开$q[5e5]$的局部数组会直接炸锅，$priority-queue$（优先队列）可以自动按从大到小的顺序排列，而$pair<,>$（二元组）正好可以存下$f(y)$和$y$两个量（在这里可能会疑惑为什么要存下变量$y$呢？请见下文$\downarrow$）

接下来看转移方程的改动：

当$i=1$时（当前子节点为$y_1$，$f(y_1)$最大时）：方程仍为：$f(x)=max(f(x),f(y_1)-(2×Size(x)-1))$

当$i=2$时（当前子节点为$y_2$，$f(y_2)$第二大时）：因以$x$的最大的子节点为根的子树已经遍历过，故当前节点减短的时间为总共能减短的时间$2*Size(x)$，减去以$y_1$为根的子树共能减短的时间$2*Size(y_1)$（这便是上文用$pair$存下两个变量的原因了，各个$x$的子节点的编号在这里有用），再减去走向$y_1$节点来回未能算入的$2$，及上文提及的走向该节点的一步，整理即为：$f(x)=max(f(x),f(y_2)-(2*(Size(x)-Size(y_1)-1)-1))$

当$i=3$时（分别为$y_3$，$f(y3)$时）：同理需分别减去以$y_1$，$y_2$为根的子树，方程为：$f(x)=max(f(x),f(y_3)-(2*(Size(x)-Size(y_1)-Size(y_2)-2)-1))$

怎么样，是不是发现些规律了？

注意在减去$\sum\limits_{j=1}^kSize(y_j)(1<=k<Size(x))$后所减的值，当$i=1$时，所减为$0$；$i=2$，所减为$1$；$i=3$，所减为$2$。故我们可以用$i-1$替换这些数字到方程中去。再设一个变量$s$，记$s=\sum_{y\in son(x)}Size(y)$，以此来表示在这之前已经遍历过的子节点之和。最终方程如下：

$f(x)=max(f(x),f(y)-(2×(Size(x)-s-i)+1))$

最后放上完整代码：

```
#include <bits/stdc++.h>

#define re register
#define li inline

li int read() {
	re int f, j; re char c;
	for (f = 1, c = getchar(); !isdigit(c); f = c == '-' ? -1 : 1, c = getchar());
	for (j = 0; isdigit(c); j = (j << 1) + (j << 3) + (c ^ 48), c = getchar());
	return f * j;
}

li void write(re int x) {
	if (x < 0) { putchar('-'); x = -x; }
	if (x > 9) { write(x / 10); } putchar(x % 10 + '0');
}


const int N = 5e5 + 10;

struct Edge {
	int next, to;
} e[N << 1];

int n, tot;
int head[N], c[N], Size[N], f[N];

li void add(re int x, re int y) { //链式前向星不多说 
	e[++tot].to = y; e[tot].next = head[x]; head[x] = tot;
	e[++tot].to = x; e[tot].next = head[y]; head[y] = tot;
}

li void update(re int x, re int fa) { //求Size[] 
	for (re int i = head[x]; i; i = e[i].next) {
		re int y = e[i].to;
		if (y == fa) { continue; }
		update(y, x);
		Size[x] += Size[y] + 1;
	}
}

li bool cmp(std::pair <int, int> x, std::pair <int, int> y) { return x.first > y.first; } //按f(y)从大到小排序 

li void dfs(re int x, re int fa) {
	std::priority_queue < std::pair <int, int> > q; //定义优先队列 
	re int tmp, s = 0;
	for (re int i = head[x]; i; i = e[i].next) {
		re int y = e[i].to;
		if (y == fa) { continue; }
		dfs(y, x); q.push(std::make_pair(f[y], y)); //插入 
	} tmp = q.size();
	for (re int i = 1; i <= tmp; i++) {
		s += Size[q.top().second]; // 累加前子节点之和 
		f[x] = std::max(f[x], q.top().first - ((Size[x] - s - i) * 2 + 1)); //dp转换 
		q.pop(); //弹出队首 
	} f[x] = std::max(f[x], c[x] - 2 * Size[x]); //实际上不特判x = 1也可以（因为在最后输出的时候还有一次max 
}

signed main() {
	n = read();
	for (re int i = 1; i <= n; i++) { c[i] = read(); }
	for (re int i = 1; i < n; i++) {
		re int x = read(), y = read(); add(x, y);
	} update(1, 1); dfs(1, 1);
	write(std::max(f[1], c[1]) + (n - 1) * 2);
	return 0;
}
```

如若有什么问题或讲的不清楚的地方，也可以向我提出噢

~~别喷我码风啊~~

####  给管理员大大的说明：前文不是有意要给出错误的解法的，大多说的是思想，错误仅仅是发生在答案的统计上。因下文的正解是在上文的基础上推理的，整篇题解也是本人做此题由错到对的心路历程，读者或许能更好的理解。

---

## 作者：YouXam (赞：0)

[Blog](https://www.cnblogs.com/youxam/p/P3574-FAR-FarmCraft.html)

# 分析

前几天刚写过salesman,一看这题就觉得有点相似,主要是DFS的过程

对于一棵子树的根节点来说,已知遍历时间和装软件时间,我们该怎么分配遍历的顺序?

首先明确,要输出的答案是遍历所有子树且所有子树安装好软件的时间,那么,有没有可能比特安萨尔已经遍历完成,但是因为某些技术水平不高的居民而不得不继续等待耗费时间的情况?有可能,那么为了尽可能减少这个时间,我就先遍历那些技术水平不高的居民.

注意,如果安装时间最长,但需要遍历的时间也很长,不一定需要先遍历,因为遍历是一定需要遍历的,这些时间不能节省,遍历是比特安萨尔去遍历,一个人同时只能干一件事情,但安装是居民安装,可以同时多个居民同时安装.

如果本来可以同时安装但我让他尽可能多地同时安装,就会浪费时间.

所以我们应该先遍历的是总时间减遍历时间最大的,这些时间就是从DFS完成,回溯开始到软件安装完成的时间.这些时间可以用来遍历别的子树.

看一下这个图:

![](https://img2020.cnblogs.com/blog/1975074/202004/1975074-20200406223546744-2069295504.png)

每一行代表一个居民的时间分配.

黄色是遍历时间,蓝色是安装时间.黄色首尾相接代表只能同时遍历一棵子树,蓝色可以重叠表示居民可以同时安装,

上面一块是没有优化的版本,可以看出来4号居民的安装时间大大拖慢了总体时间

下面是优化过的,可以看出来4号居民长长的安装时间是和遍历同时进行的,没有拖慢时间.

所以更新子树时,根据总时间减遍历时间从大到小排序即可.

# 代码

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 500001;
struct Edge {
    int to, next;
} edges[maxn<<1];
int n, head[maxn], cnt, u, v, a[maxn], dp[maxn], dis[maxn], son[maxn];
bool cmp(int x, int y) { return dp[x] - dis[x] > dp[y] - dis[y]; }
void add(int u, int v) { edges[++cnt].to = v, edges[cnt].next = head[u], head[u] = cnt; }
void dfs(int root, int fa) {
    if (root != 1) dp[root] = a[root];
    for (int i = head[root]; i; i = edges[i].next)
        if (edges[i].to != fa) dfs(edges[i].to, root);
    int sonn = 0;
    for (int x = head[root]; x; x = edges[x].next)
        if (edges[x].to != fa) son[++sonn] = edges[x].to;
    sort(son + 1, son + sonn + 1, cmp);
    for (int i = 1; i <= sonn; ++i)    
        dp[root] = max(dp[root], dp[son[i]] + dis[root] + 1), dis[root] += dis[son[i]] + 2;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    printf("%d\n", max(dp[1], dis[1] + a[1]));
    return 0;
}
```

---

## 作者：hzoi_liuchang (赞：0)

## 分析
我们设f[x]为遍历完以x为根的子树且将这棵子树上所有的电脑都安装完毕最终又回到x的最小安装时间
 

对于一棵子树，根节点所需要的安装时间自然是它本身的价值
 

那么各个子节点的价值可以直接拿来用吗？显然是不可以的
 

因为你从根节点遍历到子节点需要花费时间
 

所以这时就有遍历优先级的问题了
 

我们是先遍历安装时间最长的子树吗？这样是不可以的，比如下面这幅图
![](https://cdn.luogu.com.cn/upload/image_hosting/0eor65gy.png)
那我们该怎么办呢，我们可以发现，

![](https://cdn.luogu.com.cn/upload/image_hosting/dut742pl.png)
## 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn=1000005;
struct Edge{
    int next,to;
}e[maxn];
int head[maxn],len;
void Ins(int a,int b){
    e[++len].to=b;e[len].next=head[a];head[a]=len;
}
struct Node{
    int f,siz;
    Node(){}
    Node(int a,int b){f=a,siz=b;}     
    bool operator < (const Node&A)const{
        return f-siz<A.f-A.siz;
    }
};
int dp[maxn],g[maxn],val[maxn],que[maxn];
void dfs(int u,int fa){
    priority_queue<Node> q;
    if(u-1)dp[u]=val[u];
    for(int i=head[u];i!=-1;i=e[i].next){
        int v=e[i].to;
        if(v==fa)continue;
        dfs(v,u);q.push(Node(dp[v],g[v]));
    }
    while(!q.empty()){
        Node now=q.top();q.pop();
        dp[u]=max(dp[u],now.f+g[u]+1);
        g[u]+=now.siz+2;
    }
}
int main(){
    memset(head,-1,sizeof(head));
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&val[i]);
    for(int i=1;i<n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        Ins(a,b);Ins(b,a);
    }
    dfs(1,0);
    printf("%d\n",max(dp[1],val[1]+g[1]));
    return 0;
}
```


---

## 作者：DarthVictor (赞：0)

## 题目
[原题链接](https://www.luogu.com.cn/problem/P3574)
## 解说
首先可以明确一个点的安装时间等于走到这个点的时间+安装时间，最后总时间就是所有点的时间中最长的。

刚开始做这道题时深受昨天的[Salesman](https://www.luogu.com.cn/blog/DarthVictor/bzoj4472-shu-xing-dp-salesman)影响，觉得还是需要贪心思想（虽然确实是用贪心，但最开始走偏了……），结合样例一想，突发奇想觉得时间长的肯定是需要先走，那么我就把所有儿子的时间排个序，先走时间长的，再走时间短的，走下一个的时间中再加上之前走兄弟的子树的时间即可。

然后呢？喜提$38$分。

再仔细想想这个贪心确实不对啊。万一有一个时间很短的儿子，但是这个儿子下面却还有时间很长的后代，那么它还是应该先选的。

这不就尴尬了吗……~~（万恶的样例）~~

那么既然这样，我们就不能先给儿子排序再遍历，而是应该先遍历每个儿子再根据遍历结果排序。

（下文中$f_i$代表$i$节点所有子树中最长的时间，$a_i$代表$i$节点的时间，$size_i$代表$i$子树的规模）

假设$u$节点有儿子$x$和$y$，则如果先走$x$的话$u$的时间就为$max(f_x+1,f_y+2 \times size_x+1)$；同理，先走$y$的话$u$的时间就为$max(f_y+1,f_x+2 \times size_y+1)$，若先安装$x$合适，则必有$2 \times size_x+f_y+1>2 \times size_y+f_x+1$，即$f_x-2 \times size_y<f_y-2 \times size_x$，既然这样，我们就按照$f_i-size_i$排序即可。

（下面的代码里还有部分解说）
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=500000+5;
int t,a[maxn],head[maxn],n,tot,f[maxn],size[maxn],q[maxn];
struct node{
    int to,next;
}e[2*maxn];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
bool cmp(int x,int y){//比较函数 
    return f[x]-2*size[x]>f[y]-2*size[y];
}
void Add(int from,int to){
    e[tot].to=to;
    e[tot].next=head[from];
    head[from]=tot;
    tot++;
}
void dfs(int u,int fa){
    int cnt=0,sum=1;//sum为走u子树目前的总时间
    //cnt为儿子的数量 
    if(u==1) f[u]=0;
    else f[u]=a[u];
    size[u]=1;//叶子节点没有子树size就会存为1 
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to;
        if(v!=fa){
            dfs(v,u);
            size[u]+=size[v];//统计规模 
        }
    }
    for(int i=head[u];i;i=e[i].next) if(e[i].to!=fa) q[++cnt]=e[i].to; 
    //q数组一定要用一个，不要一个dfs开一个，会直接爆掉（亲身经历） 
    sort(q+1,q+1+cnt,cmp);//贪心排序 
    for(int i=1;i<=cnt;i++){
        f[u]=max(f[u],f[q[i]]+sum);
        sum+=2*size[q[i]];
    }
}
int main(){
    tot=1;
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n-1;i++){
        int x=read(),y=read();
        Add(x,y);
        Add(y,x);
    }
    dfs(1,0);
    printf("%d",max(f[1],a[1]+2*(n-1)));
    return 0;
}
```


---

## 作者：RikoHere (赞：0)

题面里只有一个$n$和可取极大值的$c_i$，先尝试分析一下题目吧...

设:$f(x)$为从$x$节点出发回到$x$节点后安装完毕牧场物语的最短时间，$s(x)$为以$x$为根节点的树的节点数量，$e_i$为$x$的若干个子节点...(这个写法会意就行 > <)

显然若$f(e_i)$越小，$f(x)$不会增加，所以很显然子问题是独立出来的，很显然的东西就不证 > <

现在我们有若干个$f(e_i),s(e_i)$,且$f(x)$的最终取值和遍历若干子树的顺序有关系，现在随意排好若干个子节点

$$f(x)=\max\{2*[\sum\limits_{k=1}^{i-1}s(e_k)]+f(e_i)+1,\ \ (s(x)-1)*2, c_i\}$$

上诉式子第一项就表示为遍历若干子树后时间和加当前子树的$f(x)$所取得的最大值，后一个式子表示遍历完所有子树的同时游戏都装，最后一个就表示遍历完子树自己的游戏都没装好...

后两个显然只和自己有关，现在我们要求出最优的序列来使$\max\{2*[\sum\limits_{k=1}^{i-1}s(e_k)]+f(e_i)+1\}$尽可能小以让$f(x)$尽可能小，排序相关问题贪心用微扰法...现在连续两个的子节点$i,j$，要让交换前衡不大于交换后，即下式衡成立
$\max\{f(i), f(j)+s(i)* 2\} \leq\max\{f(j),f(i)* s(j)* 2\}$

显然左右两式可化简为$f(j)-s(j)* 2\leq f(i)-s(i)* 2$，那这样只要排个序就能保证了嘛...若$i,j$不连续也是同理，对于菊花图，该算法的复杂度为跑满的$O(n\log^n)$，在$n\leq500,000$的数据下跑的够呛...好在没什么常数...

注意一下`1`号节点的游戏居然是最后装的...

```

//2019/10/5->Riko->AtZB->luoguP3574
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;
namespace Rikopack {
	#define LL long long
	bool digit (int ch) { return (ch <= '9' and ch >= '0');}
	inline int in () {
		int x = 0, base = 1, ch = getchar();
		while (!digit(ch)) { base = (ch == '-')? -1: 1; ch = getchar();}
		while (digit(ch)) { x = x*10+ch-'0'; ch = getchar();}
		return x*base;
	}
	template <class T> inline void smax (T& x, T y) { x = max(x, y);}
	template <class T> inline void smin (T& x, T y) { x = min(x, y);}
	inline void print (int x) { printf("debug:%d\n", x);}
}
using namespace Rikopack;

const int N = 505000;
struct node {
	int sz, val;
	node (int x, int y): sz(x), val(y) {}
	friend bool operator < (node a, node b) {
		return (a.val-a.sz*2) > (b.val-b.sz*2);
	}
};
int n, root = 1;
int f[N], size[N], insta_t[N];
int nxt[N<<1], to[N<<1], head[N], index_edge;
inline void add (int u, int v) {
	int i = ++index_edge;
	nxt[i] = head[u]; to[i] = v; head[u] = i;
}
vector <node> s[N];

void dfs (int x, int fa) {
	size[x] = 1; f[x] = insta_t[x];
	for (int i = head[x]; i; i = nxt[i]) {
		int e = to[i];
		if (e == fa) continue;
		dfs(e, x);
		size[x] += size[e];
		s[x].push_back(node(size[e], f[e]));
	}
	if (!s[x].empty()) sort(s[x].begin(), s[x].end());
	int p = s[x].size(), seg = 0;
	for (int i = 0; i < p; ++i) {
		smax(f[x], seg*2+s[x][i].val+1);
		seg += s[x][i].sz;
	}
	smax(f[x], seg*2);
	//printf("%d %d\n", x, f[x]);
}
void work () {
	dfs(root, 0);
	printf("%d", max(f[root], (n-1)*2+insta_t[root]));
}
void prepare () {
	n = in();
	for (int i = 1; i <= n; ++i) { insta_t[i] = in();}
	for (int i = 1; i < n; ++i) {
		int u = in(), v = in();
		add(u, v); add(v, u);
	}
	work();
}

int main () {
	prepare();
}

```

---

## 作者：inku (赞：0)


 [P3574 [POI2014]FAR-FarmCraft](https://www.luogu.com.cn/problem/P3574)


 ![https://gitee.com/inkuniverse/picture_bed/raw/master/img/20200721220526.png](https://gitee.com/inkuniverse/picture_bed/raw/master/img/20200721220526.png)

# 状态设计
设 f(i) 表示遍历 i 的子树所需时间。
g(i) 表示遍历 i 的子树，且所有人都装好软件所需的最少时间。
贪心按照 g(i) − f(i) 从大到小的顺序遍历儿子即可。
需要注意的是转移的方程。应该这样写：
# 方程的注意点

`for(int i=0;i<cnt;i++) f[u]=max(f[u],f[v]+g[u]+1),g[u]+=g[v]+2;`

+1 是因为自己也要算进去.

# 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=500010;
int f[N],g[N],son[N],n,cnt,tot,ver[N],nxt[N],h[N],a[N];
inline void add(int x,int y){ver[++tot]=y,nxt[tot]=h[x],h[x]=tot;}
inline bool cmp(int x,int y){return f[x]-g[x]>f[y]-g[y];}
inline void dfs(int u,int fa)
{
	if(u!=1) f[u]=a[u];
	for(int i=h[u];i;i=nxt[i]) if(ver[i]!=fa) dfs(ver[i],u);
	cnt=0;
	for(int i=h[u];i;i=nxt[i]) if(ver[i]!=fa) son[cnt++]=ver[i];
	sort(son,son+cnt,cmp);
	for(int i=0;i<cnt;i++) f[u]=max(f[u],f[son[i]]+g[u]+1),g[u]+=g[son[i]]+2;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	printf("%d",max(f[1],g[1]+a[1]));
	return 0;
}
```



---

