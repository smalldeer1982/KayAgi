# Ryoku 的探索

## 题目背景

Ryoku 对自己所处的世界充满了好奇，她希望能够在她「死」之前尽可能能多地探索世界。

这一天，Ryoku 得到了一张这个世界的地图，她十分高兴。然而，Ryoku 并不知道自己所处的位置到底在哪里，她也不知道她会什么时候死去。她想要知道如何才能尽可能多的探索这个世界。

## 题目描述

Ryoku 所处的世界可以抽象成一个有 $n$ 个点， $n$ 条边的带权无向连通图 $G$。每条边有美观度和长度。

Ryoku 会使用这样一个策略探索世界：在每个点寻找一个**端点她未走过**的边中**美观度最高**的走，如果没有边走，就沿着她前往这个点的边返回，类似于图的**深度优先遍历**。

探索的一个方案的长度是这个方案所经过的所有边长度的和（返回时经过的长度不用计算）。

她想知道，对于每一个起点 $s=1,2,\cdots,n$，她需要走过的长度是多少？



## 说明/提示

**【样例 1 说明】**

以下为输入输出样例 1 中的图： （边上红色数组为 $p$，黑色为 $w$）

![](https://cdn.luogu.com.cn/upload/image_hosting/rmk07281.png)

若起点为 $1$，顺序为 $1\to3\to5\to2\to4$，长度之和为 $7$。  
若起点为 $2$，顺序为 $2\to3\to5\to1\to4$，长度之和为 $7$。  
若起点为 $3$，顺序为 $3\to5\to1\to2\to4$，长度之和为 $8$。  
若起点为 $4$，顺序为 $4\to1\to3\to5\to2$，长度之和为 $7$。  
若起点为 $5$，顺序为 $5\to3\to1\to2\to4$，长度之和为 $8$。  

---

**【数据规模与约定】**

对于 $40\%$ 的数据，$n\le 10^3$。    
对于 $100\%$ 的数据，$3 \le n \le 10^6$，$1 \le u,v,p \le n$，$0\le w\le 10^9$，保证 $p$ 互不相同。

## 样例 #1

### 输入

```
5
4 1 2 1
1 2 3 2
3 1 1 4
3 5 2 5
2 3 2 3
```

### 输出

```
7
7
8
7
8```

# 题解

## 作者：xiejinhao (赞：35)

# P6033 [Ryoku 的探索] 题解

声明：转载本文或文中内容（包括图片）请注明出处，否则本人保留依法追究其责任的权力。

## 吐槽

为啥我觉得很简单但是很多人说很难？

其实出题人这一题没有出的太难，因为只需要找一个结论就好。

## 正文

既然上面已经提到是结论题了，那么结论是什么呢？

题目说到，这是一张 $n$ 点 $n$ 边的无向连通图，大家手画一下就可以知道这是一棵基环树（带一个简单环的“树”）。然后题目还提到了行走的方式，即：**一条边的一个端点走过了就不走**，否则优先走美观度大的边。

我们分析一下这句话，什么情况下一个端点会走过？就是走到环上了。画张图就明白了：

![ex.png](https://i.loli.net/2020/01/31/gUcfdqT2nobQRF1.png)

（一棵环为 $\{1,3,4,5\}$ 的基环树）

由上图可见，无论从哪个点进入环，环上总会有一条边不能经过（因为总会有一个端点被访问过），所以我们现在先考虑环上的点会忽略哪些边。

### step1：对环上节点的处理

以上面那幅图为例，假设从 $2$ 进行**深度优先遍历**，这个时候有可能访问到节点 $6$，因为他不在环上是没有影响的（访问完 $6$ 及其相关子树又会回到 $2$），所以我们考虑继续遍历。接下来遍历到 $\{1,5\}$ 其中一者，假设遍历到 $5$，同理继续遍历 $3$、$1$，当遍历到 $1$ 时你会发现，$2$ 访问过了，因此可以确定 $\{2,5,3,1\}$ 在环上，在回溯的时候我们就以进行操作。

同时，你会发现如果我们从 $2$ 先遍历到 $5$，那么 $(1,2)$ 这条边就不会再次访问，简言之，对于环上节点 $i$ 及其相邻的两条环边（在环上的边） $e_1,e_2$，若**按照美观度先访问了 $e_1$**，（也就是 $p_1>p_2$），那么就会少走 $e_2$ 这条边，也就是少走了 $w_2$ 的长度。 

因此对于环上的节点，我们可以把所有边的 $w$ 加起来，最后去判断要减去那一条环边即可。（刚刚已经提到，一个环上的节点恰好有两条环边）这样计算的复杂度就为 $O(1)$，加上找环，总的复杂度就为 $O(N)$。

如果你觉得比较懵，我们综合代码来理解：

~~~cpp
if(vis[x]) { 
	一些内容;
	return true;
} vis[x] = 1;
~~~

上面这段代码的意思时：执行遍历的时候，我们用 $vis$ 记录每个点是否走过，如果走到了一个走过的节点，就意味着这个节点在环上，我们可以用一个 $vector$ 把整个环存下来。

刚刚提到了，存环需要回溯的时候实现，我们不妨把 $dfs$ 变为 $bool$ 的返回值类型，这样就更好判断。

先定义一些数组、变量：

~~~cpp
int head[N], ver[M], Next[M], e[M], p[M];
// 边表

bool vis[N]; int End, Ep, Ee;
vector<int> ring;
long long ans[N];
// ans 答案   ring 存环用   vis 标记访问
// End 环的终止 Ep 终边的美观度 Ee 终边的长度
// 对于 End Ep Ee 下面还会解释
~~~

下面为整个找环过程的完整代码：

~~~cpp
bool vis[N]; int End, Ep, Ee;
vector<int> ring;
long long ans[N];

bool dfs(int x, int fa, int fp, int fe) {
	if(vis[x]) { 
		End = x, Ep = fp, Ee = fe;
		return true;
	}
	vis[x] = 1;
	for(int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if(y == fa) continue;
		if(dfs(y, x, p[i], e[i])) {
			if(x != End) 
				ans[x] -= fp > p[i] ? e[i] : fe;
			else  ans[x] -= p[i] > Ep ? Ee : e[i];
			ring.push_back(x);
			return x != End;
		}
	}
	return false;
}
~~~

请你观察回溯部分，如果回溯时这个点还在环上，即不是我们标记的环的 $End$（结尾，这个标记在第一个 $if$ 语句内），那么我们就可以一直往回标记，所以只要 $x ≠End$，说明环还没找完要一直返回真以便记录。

继续观察第一个 $if$ 语句以及回溯部分，你会发现，当你回溯的时候，除了标记的 $End$ 节点外，根据**深度优先遍历**的性质，一个节点的两条环边恰好连接了这个节点的父亲和儿子。因此除了 $End$ 节点，我们可以直接执行判断，对于一个点的环边，美观度小的边长需要从全集（即所有边长相加）中扣掉。

那么 $End$ 节点怎么解决呢？其实我们在第一个 $if$ 语句的时候恰好遍历了一条 $End$ 节点的环边，回溯过程又会遍历另一条，因此可以记录，然后按照上面的方法解决。

（还有不理解可以看代码或者私信我）

对于 $End$ 节点的执行深度优先遍历的时候可能有边不在环上的例子，可以看上图，从 $4$ 遍历，那么 $1$ 的父节点就为 $4$。

### step2：对环外节点的处理

再次观察上面的结论，我们只解决了环上节点，那么环外节点呢？其实这就很简单了。**比如对于节点 $4$，不论它先访问 $1$ 还是先访问 $8$，都要从 $1$ 进入环，其余非环上的边恰好都会经过一次**，所以得出结论：对于环外节点，以环为根进行遍历，每个环上节点对应的子树内答案与该节点相等。

不信？不懂？那好，我们举个例子。假设从 $4$ 进行遍历，我们可以访问 $8$，然后回来访问 $1$，那么 $(1,4),(4,8)$ 均要经过；$1$ 可以先进行环的访问，这样必定会少经过一条边（就和从 $1$ 进入执行访问时一样的），然后回来再访问 $7$，$(1,7)$ 一定会经过；同理可知环外的边都一定会经过，那么 $8,4,7$ 作为起点的答案均与 $1$ 作为起点的答案相同。

那么就可以对环上节点一一遍历，将环看为根，给其子树一一赋值。

~~~cpp
void dfs(int x) {
	vis[x] = 1;
	for(int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		if(vis[y]) continue;
		ans[y] = ans[x];
		dfs(y);
	}
}
~~~

以上就是赋值。赋值前把 $vis$ 清空并把环上节点全部标记为已访问即可。那么这一题也就解决了。

## 代码

（~~我知道你们只看这个~~）

（~~但是我的解释都在正文中，这是一份裸的代码~~）

~~~cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;

const int N = 1e6 + 10;
const int M = 2e6 + 10;

int head[N], ver[M], Next[M], e[M], p[M];

void add(reg int x, reg int y, reg int edge, reg int pi) {
	static int cnt = 0;
	ver[++cnt] = y, Next[cnt] = head[x], head[x] = cnt;
	e[cnt] = edge, p[cnt] = pi;
	
	ver[++cnt] = x, Next[cnt] = head[y], head[y] = cnt;
	e[cnt] = edge, p[cnt] = pi;
}

bool vis[N]; int End, Ep, Ee;
vector<int> ring;
long long ans[N];

bool dfs(reg int x, reg int fa, reg int fp, reg int fe) {
	if(vis[x]) { 
		End = x, Ep = fp, Ee = fe;
		return true;
	}
	vis[x] = 1;
	for(reg int i = head[x]; i; i = Next[i]) {
		reg int y = ver[i];
		if(y == fa) continue;
		if(dfs(y, x, p[i], e[i])) {
			if(x != End) 
				ans[x] -= fp > p[i] ? e[i] : fe;
			else  ans[x] -= p[i] > Ep ? Ee : e[i];
                        // 减去不会经过的边的答案
			ring.push_back(x);
			return x != End;
		}
	}
	return false;
}

void dfs(reg int x) { // 给子树赋值
	vis[x] = 1;
	for(reg int i = head[x]; i; i = Next[i]) {
		reg int y = ver[i];
		if(vis[y]) continue;
		ans[y] = ans[x];
		dfs(y);
	}
}

int read() {
	static char c;
	static int x;
	while(!isdigit(c = getchar()));
	x = c ^ 48;
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + (c ^ 48);
	return x;
}

int main() {
	reg int n = read();
	reg long long sum = 0;
	for(reg int i = 1, x, y, e, p; i <= n; i++) {
		x = read(), y = read();
		e = read(), p = read();
		add(x, y, e, p);
		sum += e; // 把所有边权叠加
	}
	dfs(1, 0, 0, 0); memset(vis, 0, sizeof vis);
	for(reg int i = 0; i < (int)ring.size(); i++) 
		vis[ring[i]] = 1, ans[ring[i]] += sum;
       // 计算环上的答案
	for(reg int i = 0; i < (int)ring.size(); i++) 
		dfs(ring[i]);
	for(reg int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
~~~

因为 $vector$ 常数比较大，输入文件也比较大，因此使用了寄存器和快速读入卡个常。

# 后记

感谢大家阅读了我的题解，同时也再次重申：若要转载，请注明出处。谢谢大家的观看和理解。

如果题解中有存在错误或者不理解的地方，请私信我（洛谷）。

（**~~不知道可不可以无耻地要个赞~~**）

---

## 作者：Zvelig1205 (赞：29)

## 基环树

### 闲话

同机房的 dalao 在学 Treap 和 splay ，然后他们派我去看看他们 plan 里的基环树。

### [例题](https://www.luogu.com.cn/problem/P6037)

做完之后发现题解不多，于是来写一篇。

### 思路

#### 暴力

题干明确说，找 **没走过的点** 且 **经过的边美观度最大** 。

那我们可以用 `vector` 存一下每个点发出的边，然后按照 `beautiful` 排一下，方便每次找美观度最大的。

最后跑 n 遍 `dfs` ，求出答案。

就像这样：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
int re()
{
	int s=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		s=s*10+ch-48,ch=getchar();
	return s*f;
}
void wr(long long s)
{
	if(s<0)putchar('-'),s=-s;
	if(s>9)wr(s/10);
	putchar(s%10+48);
}
const int inf=1e6+7;
int n;
long long ans;
bool vis[inf];
struct egde{
	int poi;
	int val,bea;
};
vector<egde>e[inf];
void ins(int x,int y,int z1,int z2)
{
	egde data;data.poi=y;
	data.val=z1;data.bea=z2;
	e[x].push_back(data);
}
bool cmp(egde a,egde b){return a.bea>b.bea;}
void dfs(int now)
{
	vis[now]=1;
	for(int i=0;i<e[now].size();i++)
	{
		int p=e[now][i].poi;
		if(vis[p])continue;
		ans+=e[now][i].val;
		dfs(p);
	}
}
int main()
{
	n=re();
	for(int i=1;i<=n;i++)
	{
		int u=re(),v=re(),w=re(),p=re();
		ins(u,v,w,p);ins(v,u,w,p);
	}
	for(int i=1;i<=n;i++)
		sort(e[i].begin(),e[i].end(),cmp);
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		ans=0;dfs(i);
		wr(ans),putchar('\n');
	}
	return 0;
}
```

实测 40 分，后六个点 T 到飞起。

#### 正解

很显然， N 点 N 边，这是一个基环树。

基环树的基本处理方式有两种：

* 先处理环，再处理环上点的子树。

* 将基环树转化为树和一条非树边。

然后对于具体的题在具体分析。

这题（我）选择用第一种方法。

##### 环上

分析题干可以发现，最终的 ans 就是比遍历整个图少一条边。

那么在建图的时候，将所有的边权记录下来。

先用一个 `dfs` 找环，用 `vector` 将环存下来：

```cpp
bool dfs(int now,int from,int val_,int bea_)
{
	if(vis[now])
	{//找到了环但还未处理终点
		end_=now;end_v=val_;end_b=bea_;
		return 1;
	}
	vis[now]=1;
	for(int i=fir[now];i;i=nex[i])
	{
		int p=poi[i];
		if(p==from)continue;
		if(dfs(p,now,val[i],bea[i]))
		{//环还没有找完或未处理终点
			if(now!=end_)
			{//环没有找完
				if(bea_>bea[i])
					ans_[now]-=val[i];
				else ans_[now]-=val_;
				huan.push_back(now);
				return 1;
			}
			else
			{//未处理终点
				if(end_b>bea[i])
					ans_[now]-=val[i];
				else ans_[now]-=end_v;
				huan.push_back(now);
				return 0;
			}
		}
	}
	return 0;//找到叶节点，不在环上
}
```

`ans_` 代表最终的结果，因为我们会选择美观度较大的边走，所以美观度较小的边就直接被减去了。

然后环上每个都加上 `sum` （即所有边权和）。

到这里，环上就算处理完了。

##### 环外

经过分析，环外的点如果遍历图的话，必然经过环上的一个点，那么从这个点出发就和从环上出发的结果相同。

再用一个 `dfs` 找到环上的点的子树，子树上的点的答案就可以直接赋过去了。

```cpp
void dfs(int now)
{
	vis[now]=1;
	for(int i=fir[now];i;i=nex[i])
	{
		int p=poi[i];
		if(vis[p])continue;
		ans_[p]=ans_[now];
		dfs(p);
	}
}
```

最后， AC Code:

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define int long long
using namespace std;
int re()
{
	int s=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		s=s*10+ch-48,ch=getchar();
	return s*f;
}
void wr(int s)
{
	if(s<0)putchar('-'),s=-s;
	if(s>9)wr(s/10);
	putchar(s%10+48);
}
const int inf=1e6+7;
int n,ans;
bool vis[inf];
struct egde{
	int poi;
	int val,bea;
};
vector<int>huan;
int cnt,sum;
int fir[inf],nex[inf<<1],poi[inf<<1];
int val[inf<<1],bea[inf<<1];
void ins(int x,int y,int z1,int z2)
{
	nex[++cnt]=fir[x];
	poi[cnt]=y;
	val[cnt]=z1;
	bea[cnt]=z2;
	fir[x]=cnt;
}
int ans_[inf];
int end_,end_v,end_b;
bool dfs(int now,int from,int val_,int bea_)
{
	if(vis[now])
	{
		end_=now;end_v=val_;end_b=bea_;
		return 1;
	}
	vis[now]=1;
	for(int i=fir[now];i;i=nex[i])
	{
		int p=poi[i];
		if(p==from)continue;
		if(dfs(p,now,val[i],bea[i]))
		{
			if(now!=end_)
			{
				if(bea_>bea[i])
					ans_[now]-=val[i];
				else ans_[now]-=val_;
				huan.push_back(now);
				return 1;
			}
			else
			{
				if(end_b>bea[i])
					ans_[now]-=val[i];
				else ans_[now]-=end_v;
				huan.push_back(now);
				return 0;
			}
		}
	}
	return 0;
}
void dfs(int now)
{
	vis[now]=1;
	for(int i=fir[now];i;i=nex[i])
	{
		int p=poi[i];
		if(vis[p])continue;
		ans_[p]=ans_[now];
		dfs(p);
	}
}
signed main()
{
	n=re();
	for(int i=1;i<=n;i++)
	{
		int u=re(),v=re(),w=re(),p=re();
		ins(u,v,w,p);ins(v,u,w,p);
		sum+=w;
	}
	dfs(1,0,0,0);
	memset(vis,0,sizeof(vis));
	for(int i=0;i<huan.size();i++)
	{
		vis[huan[i]]=1;
		ans_[huan[i]]+=sum;
	}
	for(int i=0;i<huan.size();i++)
		dfs(huan[i]);
	for(int i=1;i<=n;i++)
		wr(ans_[i]),putchar('\n');
	return 0;
}
```

有一首诗，我觉得写的很好。

~~一年 OI 一场空，不开 long long 见祖宗。~~

---

## 作者：Smallbasic (赞：11)

显然n个点n条边是基环树。

先考虑是个树的情况，显然无论从哪个点都会遍历到所有的边和点，因此就是所有边权之和。

那是棵基环树呢？

我们设环上有m个点，以这m个点为根的树（树不包括环上除根以外的点）构成一个森林

## 1.从一个根出发

显然它子树上的边&点都会被访问到，环上第一步只会访问它左右两个边中美观度最高的边，显然会绕着这个环一只转到其他的所有根和根的子树，最后到达它左右两个点中没访问到的一个，也就是只没有走到它左右两个点中美观度低的那条边，所以边权之和减去那条边即可。

## 2.从不是根的点出发

显然他会遍历完它所在的那棵子树，并最后回到根节点

因此这种情况等于从它所在树的根节点出发就行了。

========================下面是写代码环节==================

1.找环：

这里dfn表示dfs顺序，vis[i]=1表示i点在环里，fa[i]表示i在搜索树里的父节点。

显然如果从udfs到一个已经dfs过的点v且v在u后又被访问，那说明一定存在环，且u和v在环上还是环上相邻的两个点。

那就相当于搜索从u开始dfs了大半个环到达了一个相邻的点，即从v开始搜索树上的父节点和父节点的父节点以此类推直到u都在环上。

代码：

```
inline void getloop(int now) {
	dfn[now] = ++top;
	for (int i = ed[now].head; i; i = ed[i].nxt) {
		int v = ed[i].to; if (v == fa[now]) continue;//防止回溯到父节点
		if (dfn[v]) {//已经dfs过v
			if (dfn[v] < dfn[now]) continue; //保证v在u后被访问
			vis[v] = 1;
			while (v != now) { //沿着父亲找环
				vis[fa[v]] = 1;
				v = fa[v];
			}
		} else fa[v] = now, getloop(v);//否则继续搜索
	}
}
```

2.找每个点所在的树树根。

为了省空间（方便）这里就重用了之前的fa数组

不从每个点开始，而是从每个根开始在除去环的区域里搜索，搜到的点所在树的根就是这个根。

代码：

```cpp
inline void dfs(int rt, int now) { //rt是从哪个根开始，now是现在所在的点
	fa[now] = rt; vis2[now] = 1;
	for (int i = ed[now].head; i; i = ed[i].nxt) {
		int v = ed[i].to; if (vis2[v] || vis[v]) continue;//防止搜索到环上或已经搜过的点
		dfs(rt, v);
	}
}
```

3.找到每个根在环上连的两条边美观度较低的边

还是为了省空间（方便）就重用dfn数组

用dfn表示

这个有了环就很简单了吧。。。

```cpp
for (int i = 1; i <= n; ++i) {
	if (vis[i]) {
    	dfs(i, i);//上一步找根
      	int ip = 0x3f3f3f3f;//当前最低美观度
	  	for (int j = ed[i].head; j; j = ed[j].nxt)
			if (vis[ed[j].to] /*边一定要在环上*/&& ed[j].p < ip) dfn[i] = ed[j].val, ip = ed[j].p;
	}
}
```

总代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

inline int read() {
	int s = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) s = (s << 1) + (s << 3) + (ch & 15), ch = getchar();
	return s;
}

struct edge {
	int head, to, nxt, val, p;
}ed[2000005];

int n, en = 0, u, v, w, p, fa[1000005], dfn[1000005], top; 
long long ans = 0;
bitset<1000005> vis, vis2;

inline void addedge(int from, int to, int val, int p) {
	ed[++en].to = to; ed[en].nxt = ed[from].head; ed[en].val = val; ed[from].head = en;
	ed[en].p = p;
}

inline void getloop(int now) {
	dfn[now] = ++top;
	for (int i = ed[now].head; i; i = ed[i].nxt) {
		int v = ed[i].to; if (v == fa[now]) continue;
		if (dfn[v]) {
			if (dfn[v] < dfn[now]) continue;
			vis[v] = 1;
			while (v != now) {
				vis[fa[v]] = 1;
				v = fa[v];
			}
		} else fa[v] = now, getloop(v);
	}
}

inline void dfs(int rt, int now) {
	fa[now] = rt; vis2[now] = 1; //cout << now << endl;
	for (int i = ed[now].head; i; i = ed[i].nxt) {
		int v = ed[i].to; if (vis2[v] || vis[v]) continue;
		dfs(rt, v);
	}
}

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		u = read(); v = read(); w = read(); p = read();
		addedge(u, v, w, p); addedge(v, u, w, p); ans += w;
	} getloop(1);
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) {
    		dfs(i, i);//上一步找根
     	 	int ip = 0x3f3f3f3f;//当前最低美观度
	  		for (int j = ed[i].head; j; j = ed[j].nxt)
				if (vis[ed[j].to] /*边一定要在环上*/&& ed[j].p < ip) dfn[i] = ed[j].val, ip = ed[j].p;
		}
	} for (int i = 1; i <= n; ++i) printf("%lld\n", ans - (long long)dfn[fa[i]]);
	return 0;
}
```

---

## 作者：wangjinbo (赞：6)

这道题的暴力很好想，就是按照题意，从 $1-n$ 出发各走一遍，每次遍历的时间为 $O(n)$，因为是走 $n$ 次，所以总时间复杂度为 $O(n^2)$，可以通过 $n \le 10^3$ 的点，得到 $40$ 分。

再仔细分析一下这道题，就会发现有一个条件特别好，就是 $n=m$。这个条件说明所给的图一定是基环树。那么我们就可以想到，要遍历一棵基环树，就要走过他的 $n-1$  条边，也就是说只有一条边是走不到的，那么求答案时只需要用总长度减去这一条边的长度就可以了。然后，自己模拟一下样例，就会得出一个结论：无论从哪里开始走，都会进入一个环，进入环后会有两条环中的边，这时选择美观度高的那一条，另一条就是不会走到的那一条。显而易见这个结论是正确的。

所以，解决这道题就分成了以下几步：

### 1.求出哪些点在环中
要在基环树中求环，自然是用拓扑排序（当然肯定有乱搞做法），排序后剩下的点就是环中的点。
```
while(!q.empty())
	{
		int x=q.front();
		q.pop();
		p[x]=1;//标记为环外
		for(int i=head[x];i;i=a[i].next)
		{
			int u=a[i].to;
			de[u]--;
			if(de[u]==1)q.push(u);
		}
	}
```
### 2.求出每个点进入环的位置
从环中每个点开始遍历，遍历到的点即为从此处进入环的点。
```
void dfs1(int now,int fa)
{
	vis[now]=1;
	in[now]=fa;//in数组记录从何处入环
	for(int i=head[now];i;i=a[i].next)
	{
		int u=a[i].to;
		if(!p[u]||vis[u])continue;
		dfs1(u,fa);
	}
	vis[now]=0;
}
```
### 3.求出进入环后放弃的一条边
根据分析暴力模拟即可。
```
void check(int now)
{
	int maxw,maxp=-1,num;
	for(int i=head[now];i;i=a[i].next)
	{
		int u=a[i].to;
		if(!p[u]){
			num++;//记录找到了几条环上边
			if(a[i].p>maxp){
				maxp=a[i].p;
				maxw=a[i].w;
			}
			if(num==2){//找到两条后保存并退出
				C[now]=maxw;
				return;
			}
		}
	}
}
```
### 4.输出答案
对每一个 $i$ 输出答案即可。

复杂度分析：每一步的复杂度都是 $O(n)$，所以总复杂度是 $O(n)$。

###  AC代码
```
#include<bits/stdc++.h>
using namespace std;
struct edge{
	long long next,to,p,w;
}a[2000010];
int head[1000010],cnt,de[1000010],p[1000010];
long long in[1000010],sum,C[1000010];
bool vis[1000010];
void add(int x,int y,int w,int p)
{
	a[++cnt].next=head[x];
	a[cnt].to=y;
	a[cnt].p=p;
	a[cnt].w=w;
	head[x]=cnt;
}
void dfs1(int now,int fa)
{
	vis[now]=1;
	in[now]=fa;
	for(int i=head[now];i;i=a[i].next)
	{
		int u=a[i].to;
		if(!p[u]||vis[u])continue;
		dfs1(u,fa);
	}
	vis[now]=0;
}
void check(int now)
{
	int maxw,maxp=0x3f3f3f3f,num=0;
	for(int i=head[now];i;i=a[i].next)
	{
		int u=a[i].to;
		if(!p[u]){
			num++;
			if(a[i].p<maxp){
				maxp=a[i].p;
				maxw=a[i].w;
			}
			if(num==2){
				C[now]=maxw;
				return;
			}
		}
	}
}
int main()
{
	queue<int> q;
	long long n;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		long long x,y,w,p;
		scanf("%lld %lld %lld %lld",&x,&y,&w,&p);
		sum+=w; 
		de[x]++;de[y]++;
	    add(x,y,w,p);
	    add(y,x,w,p);
	}
	for(int i=1;i<=n;i++)
	if(de[i]==1)q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		p[x]=1;
		for(int i=head[x];i;i=a[i].next)
		{
			int u=a[i].to;
			de[u]--;
			if(de[u]==1)q.push(u);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!p[i]){
			check(i);
			dfs1(i,i);
		}
	}
	for(int i=1;i<=n;i++)
	printf("%lld\n",sum-C[in[i]]);
	return 0;
}
```


---

## 作者：NBest (赞：3)

### 闲话
当我看见这道绿题的时候，一时没有任何思路（没有看懂作者让我们干什么），看过一些题解的题意分析的我还是不是很清楚（语文太差了），于是，通过对样例的分析，我终于看懂了，题意明白后代码还是好写的（自己模拟才是最靠谱的）。

## 题意分析
其实不难看出其实题目让我们求的是从每个点开始进行按照美观度 $p$ 优先和走过的边优先于没走过但是两端点都去过的边的原则来遍历求走过的路程。

如果真的按照这个思路去写， $10^6$ 的数据显然是不会让你过的，看着样例整齐的数据，我陷入了沉思。

![](https://cdn.luogu.com.cn/upload/image_hosting/rmk07281.png)(图片来源于原题)

从 $4$ 出发，先到达处于环内的 $1$ 中，此时根据 $p$ 的优先级，我们显然是要选择走到 $3$ 的，剩下的路就没有选择了，只能除了 $1$ 到 $2$ 的路以外全走。

同样，我们从 $1$ 出发，结果与从 $4$ 出发相同，从 $5$ 出发，到 $3$ 进行选择，$p_1>p_2$ 于是选择走到 $1$ 剩下的除了 $2$ 到 $3$ 以外的路全走。
从 $3$ 出发与从 $5$ 出发结果无异。

那么我们不难得出一个结论：**在非环上的点，我们是不需要选择的，也就是非环的路必然要走**。

而且，该点进入环中就算是选择，也是在刚进入环时就根据 $p$ 选择去掉一条边，剩下的边也都要选。

也就是说，所有和环上点连接的非环上点的答案都与环上点相同（都是在该环上点选择去掉一条边），于是解决本题的方法就出来了。

记录所有路的长度之和 $tot$，找到环，遍历所有环上点，在与之相连的所有环上点中选择一条 $p$ 最小的去掉，用 $tot$ 减去该边的长度即为该环上点的答案，然后再去深搜遍历与该点相连的非环上点，将答案传递。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read(){
    int x=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    return x*f;
}
struct Edge{
	int to,w,p,next;
}edge[2000006];  //我用的链式前向星 
int n,pd[1000006],ent,head[1000006]; //因为我用的是拓扑，这个pd表示每个点的度 
ll tot,ans[1000006];//总长度和每个点的答案 ，最好开long long 
bool vis[1000006];//最后遍历树的时候防止重复赋值 
queue<int>Q;//拓扑的队列 
inline void add(int u,int v,int w,int p){
	edge[++ent].to=v;
	edge[ent].w=w;
	edge[ent].p=p;
	edge[ent].next=head[u];
	head[u]=ent;
	return;
}
inline void dfs(int x){
	for(int i=head[x];i;i=edge[i].next){
		int y=edge[i].to;
		if(pd[y]<2&&!vis[y]){//度为一就是只有一条边连接，是非环节点 
			ans[y]=ans[x];//赋值 
			vis[y]=1;
			dfs(y);
		}
	}
}
int main(void){
    n=read();
    for(int i=1;i<=n;i++){
    	int u=read(),v=read(),w=read(),p=read();
    	add(u,v,w,p),add(v,u,w,p);
    	pd[u]++,pd[v]++;//度数加 
    	tot+=w;//累加答案 
	}
	for(int i=1;i<=n;i++){
		if(pd[i]==1)Q.push(i);//叶子节点就push 
	}
	while(!Q.empty()){//没什么好说的 
		int x=Q.front();
		Q.pop();
		for(int i=head[x];i;i=edge[i].next){
			int y=edge[i].to;
			if(--pd[y]==1){
				Q.push(y);
			}
		}
	}
	for(int x=1;x<=n;x++){
		if(pd[x]>=2){// 度超过一说明在环上 
			int minn=0x3f3f3f3f,jian;
			for(int i=head[x];i;i=edge[i].next){
				int y=edge[i].to;
				if(pd[y]>=2&&edge[i].p<minn){//去找同样是环上的最小p的边删除 
					minn=edge[i].p;
					jian=edge[i].w;
				}
			}
			ans[x]=tot-jian;//得到删除这条边后的答案 
			dfs(x);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

如果还没看懂建议自己模拟一下就知道了。

---

## 作者：邈云汉 (赞：2)

图是一棵基环树，有且仅有一个环。

易知：

1.不管从那个点开始，都有一条边不会被访问。

2.这条边在环上。

那么到底怎么找到这条边呢？

首先，要找到环：
```cpp
void dfs1(int x)
{
	dfn[x]=++tot;
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i].to;
		if(v==fa[x])continue;
		if(dfn[v])
		{
			if(dfn[v]<dfn[x])continue;
			l[v]=true;
			while(v!=x)
			{
				l[fa[v]]=true;
				v=fa[v];
			}
		}
		else
		{
			fa[v]=x;
			dfs1(v);
		}
	}
}
```
至于为什么是对的，楼下已经说的很清楚了，这里不再赘述。

然后，你可以想象把环删掉，那么图就变成了森林。从每个树根出发，执行一次深度优先遍历，记录子树中每个点的祖先为根节点。

对于任意点的祖先节点，在环上都有两条边与之相连，这两条边中美观度较低的边不会被访问。

最后，上代码：
```cpp
#include<cstdio>
#include<vector>
using namespace std;
const int N=3e6+1;
struct node{
	int to;
	int w;
	int p;
}temp;
vector<node>g[N];
int fa[N];
bool l[N];
int res[N];
int dfn[N];
void dfs(int s,int x)
{
	dfn[x]=1;
	fa[x]=s;
	for(int i=0;i<g[x].size();i++)
	{
		if(!dfn[g[x][i].to]&&!l[g[x][i].to])
		{
			fa[g[x][i].to]=s;
			dfs(s,g[x][i].to);
		}
	}
}
int tot=0;
void dfs1(int x)
{
	dfn[x]=++tot;
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i].to;
		if(v==fa[x])continue;
		if(dfn[v])
		{
			if(dfn[v]<dfn[x])continue;
			l[v]=true;
			while(v!=x)
			{
				l[fa[v]]=true;
				v=fa[v];
			}
		}
		else
		{
			fa[v]=x;
			dfs1(v);
		}
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		temp.to=b,temp.w=c,temp.p=d;
		ans+=(long long)c;
		g[a].push_back(temp);
		temp.to=a;
		g[b].push_back(temp);
	}
	dfs1(1);
	for(int i=1;i<=n;i++)
	{
		fa[i]=0,dfn[i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		if(l[i])
		{
			dfs(i,i);
			int MIN=2e9;
			for(int j=0;j<g[i].size();j++)
			{
				if(l[g[i][j].to])
				{
					if(MIN>g[i][j].p)
					{
						MIN=g[i][j].p;
						res[i]=g[i][j].w;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",ans-(long long)res[fa[i]]);
	}
	return 0;
}
```


---

## 作者：VIOLET__FOREVER (赞：2)

题目[传送门](https://www.luogu.com.cn/problem/P6037)
## 思路提供
首先，我们从题目中可以看到，存在 $n$ 个点 $n$ 条边，所以此题考查的是基环树，那么什么是基环树——

基环树是一个 $n$ 个点 $n$ 条边的图，比树多出现一个环。

因此，这棵树上是存在一个环的（而且很重要），所以我们要先找出这个环，基环树找环有两种基本的算法，一种是 `DFS` 而另一种就是我这次用的改编版的**拓扑排序**，即每次将连边数位 $1$ 的点加入队列，再每次取出队头，遍历它所连的所有边，将它的所有连点的连边数都减去 $1$ 再将连边数为 $1$ 的点加入队列，如此往复，直到队列变空，由于环中的点都至少有两条连边，而且不会有点被加入队列，所以在循环结束后边数大于 $1$ 的点就是环中的数。
```cpp
//求环
void qh(){
	for(int i=1;i<=n;i++){
		if(lb[i]==1) q.push(i);
	}
	while(!q.empty()){
		int w=q.front();
		q.pop();
		for(int i=head[w];i!=0;i=edge[i].next){
			int xx=edge[i].to;
			lb[xx]--;
			if(lb[xx]==1) q.push(xx);
		}
	}
}
```
接下来，我们可以将这个环看作整个树的中心（即树的根节点），而每棵子树与环的连边只有一条，即这棵子树中的任意点的答案和它连接的环的点的答案是一样的，所以我们只要求出每个环中点的答案，再将其向各自的子树子树扩展就可以（可以利用 `DFS` ）
```cpp
//为子树染色
void rs(int x){
	for(int i=head[x];i!=0;i=edge[i].next){
		int xx=edge[i].to;
		if(lb[xx]<=1 && !vis[xx]){
			ans[xx]=ans[x];
			vis[xx]=1;
			rs(xx);
		}
	}
}
```
最后最关键的就是求环中每个答案，我们可以先看一下题目中所给的样例的图——
![](https://cdn.luogu.com.cn/upload/image_hosting/rmk07281.png)

假如以 $1$ 为出发点，它会先选取（$1,4$）这条边，再由 $3$ 这个点进行扩展，而由于是 `DFS` 所以 $3$ 会遍历完所以它连的边再回溯到 $1$ ，即环中剩下的 $2$ 也会被遍历到，所以 $1$ 和 $2$ 之间的连边就无效了（即不会被便利到）。

然后我们再以 $3$ 为出发点，按照规律它会先选择 $5$ 回溯后选择 $1$ 而因为同上是 `DFS` 所以要遍历完 $1$ 的所有可能才会回溯到 $3$ 所以 $2$ 会在 $1$ 遍历所有连点的时候就被遍历过了，所以 $3$ 和 $2$ 之间的连边也无效了。

这样我们就可以发现一个规律——

环中的点与他在环中连接到两条边中美观值最小的边不会被遍历到，所以它的答案值就是总的长度减去那条不会被遍历到的边的长度（不理解可以根据样例再研究一下）。
```cpp
//求环中点的答案值
void solve(){
	for(int i=1;i<=n;i++){
		if(lb[i]>1){
			int minn=1e9,flag;
			for(int j=head[i];j!=0;j=edge[j].next){
				int xx=edge[j].to;
				if(lb[xx]>1 && edge[j].beat<minn){
					minn=edge[j].beat;
					flag=edge[j].value;
				}
			}
			vis[i]=1;
			ans[i]=tot-flag;
			rs(i);
		}
	}
}
```
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//一年 OI 一场空，不开 long long 见祖宗
const int N=1000005;
struct node{
	int to,next,value,beat;
}edge[N<<1];//前向星存边（记得双倍空间） 
int head[N],cnt,vis[N],ans[N],n,lb[N],tot;//tot记录总长度，vis表示有无被访问过，ans存储当前点的答案，lb表示当前点的连边数 
queue<int> q;//拓扑排序用的队列 
void add(int x,int y,int v,int b){
	cnt++;
	edge[cnt].to=y;
	edge[cnt].value=v;
	edge[cnt].beat=b;
	edge[cnt].next=head[x];
	head[x]=cnt;
}//前向星的加边函数 
//拓扑求环
void qh(){
	for(int i=1;i<=n;i++){
		if(lb[i]==1) q.push(i);
	}//将连边数为1的点（即叶子节点）加入队列 
	while(!q.empty()){
		int w=q.front();
		q.pop();//每次去出队头 
		for(int i=head[w];i!=0;i=edge[i].next){
			int xx=edge[i].to;
			lb[xx]--;
			if(lb[xx]==1) q.push(xx);//将符合要求的点加入队列 
		}
	}
}
//为子树染色
void rs(int x){
	for(int i=head[x];i!=0;i=edge[i].next){
		int xx=edge[i].to;
		if(lb[xx]<=1 && !vis[xx]){//必须是子树上的节点，要避免是环上的 
			ans[xx]=ans[x];
			vis[xx]=1;
			rs(xx);//继续向下遍历 
		}
	}
}
//求环中点的答案值
void solve(){
	for(int i=1;i<=n;i++){
		if(lb[i]>1){
			int minn=1e9,flag;//给minn赋值为极大 
			for(int j=head[i];j!=0;j=edge[j].next){
				int xx=edge[j].to;
				if(lb[xx]>1 && edge[j].beat<minn){
					minn=edge[j].beat;//求最小美观值 
					flag=edge[j].value;//求最小美观值边的长度 
				}
			}
			vis[i]=1;//DFS的准备 
			ans[i]=tot-flag;//先将环中点的答案值更新 
			rs(i);
		}
	}
}
signed main(){
	std::ios::sync_with_stdio(false);//可以是cin和cout的速度加快，不加会T一个点 
	cin>>n;
	for(int i=1;i<=n;i++){
		int x,y,p,b;
		cin>>x>>y>>p>>b;
		add(x,y,p,b),add(y,x,p,b);
		lb[x]++,lb[y]++;//将两个节点的连边数都加上1 
		tot+=p;//计算总值 
	}
	qh();
	solve();
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;//按顺序输出答案 
	return 0;
} 
```


---

## 作者：xia0ji233 (赞：1)

## 浅谈基环树(环套树)

在题目开始之前，就唠一唠这个叫基环树的结构。准确来说，基环树它已经不是树了，我们知道，树一定是由 $n$ 点和 $n-1$ 条边组成的。而基环树是由 $n$ 点与 $n$ 边组成。但是因为它跟树还是很像，并且在保证连通的情况下有且仅有一个简单环，因此得名。如果不连通，那么它会成为基环树森林。

![1](https://xia0ji233.pro/2022/02/11/%E6%B4%9B%E8%B0%B7P6037%E9%A2%98%E8%A7%A3/1.png)

比如上图就是一个基环树。我们可以很清楚的看出来，点 $2,1,3,7$ 形成了环，断开任意一条属于环中的边都会使这个棵基环树成为树。一般情况下都是将环和环连接的子树进行分开讨论。如何求环呢？我们只需要 dfs 一遍就行了，如果遇到被访问过的点，那就依次返回路径上的所有点，直到我遇到的那个点为止。

举个例子，在上图中，我从 $6$ 开始 dfs，假设它经历了 $6 \to 2 \to 1 \to 3 \to 7$ 的顺序。那么接下来在搜索 7 的时候就会发现与它相连的点 $2$ 已经被访问过，那么我返回值给个 2，依次回溯，回溯过程中将点入栈或者入一个 vector 都可以。直到回溯到 2 这个点为止。环就被我们求出来了。

能求出环我们就会很好做这类的题目了，那么我们具体看看这题吧。

## 题目描述

Ryoku 所处的世界可以抽象成一个有 $n$ 个点， $n$ 条边的带权无向连通图 G。每条边有美观度和长度。

Ryoku 会使用这样一个策略探索世界：在每个点寻找一个**端点她未走过**的边中**美观度最高**的走，如果没有边走，就沿着她前往这个点的边返回，类似于图的**深度优先遍历**。

探索的一个方案的长度是这个方案所经过的所有边长度的和（返回时经过的长度不用计算）。

她想知道，对于每一个起点 $s=1,2,\cdots,n$，她需要走过的长度是多少？

---

$n$ 个点 $n$ 条边的连通图，那么肯定就是基环树了然后它会根据美观度与深度优先的一种搜索策略，即遇到分支先沿一条分支走完再走另一条分支，并且多条分支优先搜索美观度高的分支。回溯走的路不算，问你以不同的点为起点搜索完所有的点需要走多少长度。

我们不难得出，如果要遍历 $n$ 个点，我们只需要走过 $n-1$ 条边。而对于一棵树而言，对它深度优先搜索一定会遍历树上所有的边。因此如果把基环树拆开称为一个环和若干个子树，我们就只需要在环上讨论情况，子树的所有边一定是都会走过的。对于同一个环，我先向右边遍历和先向左边遍历走的路径是完全不一样的，如果先向右边那必然导致它左边不会被走过，同理先走左边那右边就不会被走过。

再根据题中的策略，对于环上的点，我们只需要循环一遍环上的所有点，观察与它连接的在环上的边的美观度哪个比较大，那么答案就是所有图的边权减去那个美观度较小的边权。对于不在环上的点我们可以观察它所在的子树连接在环的哪个点，因为从那个点遍历出来最终也会从它所在的子树走向环的那个点，然后情况就变成了在换上对应的点遍历的情况了。

所以我们先大致描述一下算法流程：

- 将边按照出点读入 vector 当中，并且按美观度排序
- dfs 跑出环上的点将其标记
- 对环上所有的点进行答案计算
- 对环上的点再跑一次dfs，然后搜索策略为非环上的点，将搜索到的点标记为环上对应的那个点
- 最后答案就出来了



## 标程

```c++
#include<bits/stdc++.h>
#define maxn 3000005
using namespace std;
struct eee{
	int to;
	int w;
	int p;
};
int visited[maxn],ans[maxn],n;
long long sum_len,res[maxn];//不开long long见祖宗
vector<eee>edge[maxn];//用vector数组保存边方便排序
vector<int>s;//保存环上的点
bool in_stack[maxn];//因为我原来使用栈保存的因此命名这个，表示点是否在环上
void add(int x,int y,int w,int p){
	eee e;
	e.to=y;
	e.w=w;
	e.p=p;
	edge[x].push_back(e);
}
int cmp(eee a,eee b){//按美观度排序
	return a.p>b.p;
}
int dfs(int u,int pre){
	
	if(visited[u]){//如果搜索到了被标记过的点则说明遇到环了
		return u;
	}
	visited[u]=1;
	int value=0;
	for(auto it=edge[u].begin();it!=edge[u].end();it++){
		int v=it->to;
		if(v==pre||in_stack[v])continue;//防止逆搜索，并防止对环重新搜索
        //从环的起点开始，假如我顺时针跑出了环，那么它下一条边将会逆时针跑环
        //可以看到仅仅限制条件v!=pre是远远不够的。
		int tmp=dfs(v,u);
		if(tmp){//若返回结果不为0则说明遇到环，并且本点也在换上，就保存。
			value=tmp;
			if(value==u){
                //我判断出环的那个点一定是环的起点，如果回溯过程中遇到了说明环已经保存完了
                //再往前回溯的点就不属于环了
				value=0;
			}
			s.push_back(u);
			in_stack[u]=1;
		}
	}
	return value;
}
void dfs2(int u,int pre,int flag){//这里搜索环的子树，将子树上所有点标记为子树与环直接相连的一个点
	for(auto it=edge[u].begin();it!=edge[u].end();it++){
		int v=it->to;
		if(v==pre||in_stack[v])continue;//这里我们排除环上的点遍历的一定就都是子树
		ans[v]=flag;//ans保存本点答案与哪个点的答案一致。
		dfs2(v,u,flag);
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	//freopen("1.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		int x,y,w,p;
		cin>>x>>y>>w>>p;
		add(x,y,w,p);
		add(y,x,w,p);
		sum_len+=w;//读入边，将边权之和保存。
	}
	
	for(int i=1;i<=n;i++){
		sort(edge[i].begin(),edge[i].end(),cmp);
	}
	dfs(1,0);
	for(auto i=s.begin();i!=s.end();i++){//给子树标记
		dfs2(*i,0,*i);
		ans[*i]=*i;
	}
	for(auto i=s.begin();i!=s.end();i++){
		for(auto j=edge[*i].end()-1;j!=edge[*i].begin()-1;j--){
			if(in_stack[j->to]){//因为我们是按照美观度从大到小排序的，所以从后面开始找到第一个在环上的点一定是美观度较小的边，答案就是减去美观度较小的边权。
				res[*i]=sum_len-(j->w);//res数组保存答案
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld\n",res[ans[i]]);
	}

	return 0;
}
```



---

## 作者：老官童鞋gogo (赞：1)

[博客体验更佳](http://laoguantx.nov.vin/?p=257)

---

## 题解

### 题目理解与强调

题目给出的是一个 $n$ 个点 $n$ 条边的无向连通图， $n$ 个点 $n$ 条边可以看出这是一个**基环树**，树上每个点都有两种权值，分别表示美观度和长度，我们从一个点出发的时候，要找**美观度最大**的一条边走，**如果那个点已经被走过了**，**就不走了**，换向另一条边，过程类似于 **DFS** 。

### 思路分析

既然是在一棵基环树上遍历每个点，走过这 $n$ 个点需要经过 $n-1$ 条边，用总长度边权减去剩下的那一条没走的边的长度，就是每个点的答案，因为在这个图中有且仅有一个环，那么我们那一条没有走的边一定在环上，如果这一条没走过的边不在环上，至少一个点就不会被遍历到，因为不在环上的点只有一个方向可以到达。

对于判断环，采用拓扑排序，将所有入度为 $1$ （原图是无向图）的点加入队列，队列为空时，剩下的部分就是环，因为环上的每个点的入度至少为 $2$ 。

为了尽可能减少实际时间复杂度，不去以每个点为起点遍历整张图，而是以环上的点为起点遍历整张图，因为取环上的点为起点遍历部分图，假如环上的一个点 $x$ ，它的周围有两个在环上的点 $u$ 和 $v$ ，如果点 $x$ 到 $u$ 的边上的美观度大于点 $x$ 到 $v$ 上的美观度，那么下一次走的边就是 $x→u$ 这一条，另一条 $x→v$ 就是第一段中分析的不会经过的边，统计答案的时候减去这条边的长度即可。

那么在整张图上有哪些点会用到我们当前点上算出的答案？我们想象将环上的每一条边都断开，整张图会成为一个森林，规定原先在环上的点为每一棵树上的根节点，每棵树上的所有节点答案都与根节点算出的答案相同。因为每棵树上除了根节点，其他的点都不在环上，而它们走到环上去遍历其他点的路径只有一条，就是经过它们的根节点，所以它们没有走过的边与它们根节点没有走过的边是相同的，答案也是相同的。至此，问题解决。

### 时间复杂度分析

第一步拓扑排序：$O(n)$

第二步计算答案：$O(n)$

总复杂度：

$$ O(n) $$

---
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define reg register
#define PI acos(-1.0)
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define fi first
#define se second
#define pr(x) cerr<<#x<<"="<<(x)<<endl
#define pri(x,lo) {cerr<<#x<<"={";for (int ol=0;ol<=lo;ol++)cerr<<x[ol]<<",";cerr<<"}"<<endl;}
#define inf 100000000
#define N 1000
#define M 1000001
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct Node
{
	int to,nxt,w,p;
}e[3000001];
int g[3000001],nxt,n,inp[3000001];
bool cir[3000001],vis[3000001];
ll ans[3000001],sum;
queue<int>q;
void add(int x,int y,int w,int p)
{
	e[++nxt].to=y;
	e[nxt].nxt=g[x];
	g[x]=nxt;
	e[nxt].w=w;
	e[nxt].p=p;
}
void find_circle()
{
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		cir[x]=1;
		for(int k=g[x];k;k=e[k].nxt)
		{
			int y=e[k].to;
			inp[y]--;
			if(inp[y]==1)
				q.push(y);
		}
	}
}
void dfs(int x,ll Minw)
{
	// pr(x);
	ll Minp=1e18;
	if(cir[x]==0)
		for(int k=g[x];k;k=e[k].nxt)
		{
			if(Minp>e[k].p&&cir[e[k].to]==0)
			{
				Minp=e[k].p;
				Minw=e[k].w;
			}
		}
	ans[x]=sum-Minw;
	for(int k=g[x];k;k=e[k].nxt)
	{
		int y=e[k].to;
		if(vis[k]==0&&cir[y]!=0)
		{
			vis[k]=1;
			dfs(y,Minw);
		}
	}
}
int main()
{
	int n=read();
	for(int i=1;i<=n;i++)
	{
		int x=read(),y=read(),w=read(),p=read();
		add(x,y,w,p);
		add(y,x,w,p);
		inp[y]++;
		inp[x]++;
		sum+=w;
	}
	for(int i=1;i<=n;i++)
	{
		if(inp[i]==1)
			q.push(i);
	}
	find_circle();
	for(int i=1;i<=n;i++)
	{
		if(cir[i]==0)
			dfs(i,0);
	}
	for(int i=1;i<=n;i++)
	{
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```
1.51s 124.12MB

我的代码空间复杂度并不理想，开了 $O2$ 勉强过，若有更优方法请在评论中指出。

---

