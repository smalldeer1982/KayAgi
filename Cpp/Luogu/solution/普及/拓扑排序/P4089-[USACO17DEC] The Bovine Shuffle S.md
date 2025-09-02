# [USACO17DEC] The Bovine Shuffle S

## 题目描述

Farmer John 坚信快乐的奶牛能产更多的奶，因此他在谷仓里安装了一个巨大的迪斯科球，并计划教他的奶牛跳舞！

在查阅了流行的奶牛舞蹈后，Farmer John 决定教他的奶牛“Bovine Shuffle”。Bovine Shuffle 包括他的 $N$ 头奶牛（$1 \leq N \leq 100,000$）以某种顺序排成一行，然后进行连续的“洗牌”，每次洗牌可能会重新排列奶牛的顺序。为了让奶牛更容易找到自己的位置，Farmer John 为他的奶牛队伍标记了位置 $1 \ldots N$，因此队伍中的第一头奶牛位于位置 1，第二头位于位置 2，依此类推，直到位置 $N$。

一次洗牌由 $N$ 个数字 $a_1 \ldots a_N$ 描述，其中位于位置 $i$ 的奶牛在洗牌期间移动到位置 $a_i$（因此，每个 $a_i$ 都在 $1 \ldots N$ 范围内）。每头奶牛在洗牌期间都会移动到它的新位置。不幸的是，所有的 $a_i$ 不一定互不相同，因此多只奶牛可能会在洗牌期间尝试移动到同一位置，之后它们将在所有剩余的洗牌中一起移动。

Farmer John 注意到，无论进行多少次洗牌，他的队伍中某些位置始终会有奶牛。请帮助他计算这样的位置数量。

## 样例 #1

### 输入

```
4
3 2 1 3```

### 输出

```
3
```

# 题解

## 作者：QAQ永动机 (赞：26)

## 首先，我们理解一下题意
每一个位置上都有一个牛。每头牛都会变换

给你n个数，分别是a1，a2……an。ai表示每一次变换位置为i的牛会变到位置为ai的地方。变换后，有的位置上有多个牛，那么他们下一次变换，这个位置上的所有牛都会这么变。

问无论几次变化后，一共有多少个位置上有牛

## 看看样例：

in:

```
4
3 2 1 3
```

out:
```
3
```

### 画个图，理解一下

![](https://cdn.luogu.com.cn/upload/pic/62456.png)

$\tiny\texttt{箭头表示从位置几跳到位置几}$

**欸？这不就是个有向图吗？**

#### 我们来画一画：

![](https://cdn.luogu.com.cn/upload/pic/62459.png)
#### 结合样例，我们来看看

输出了3，是哪3个？是1，2，3三个位置。那么为什么4号没有牛呢？我们可以发现因为1，2，3入度都大于0，唯独4小于0.哦？难道和入度有关？

## 猜想

我们不妨有一个猜想：如果有一个点，他的收入可以维持他的支出，那么这个点上一直有牛。也就是

```cpp
if(入度-出度>=0){
	ans++;
 }
 ```
 
 这就对了吗？我们欣喜的发现样例过了。提交一下——WA
 
 这是为什么呢？来看看这组数据——
 
 in:
 ```
 1 1 2
 ```
 
 
输出应该是1，可是以我们这样判断就是2
 
~~QAQ泪奔~~

## 猜想2

我们可以发现，导致这种错误的原因是第一轮3给了2一头牛，可是第二轮3没有牛了，从而让2后面每轮得到的牛为0。**就是因为3入度为0，所以"养不起"2**

所以我们可以猜想：如果一个点入度为0，那么这个点指向的点入度--。（大家听起来应该很费劲，用伪代码给大家理解)

```cpp
if(in[f[i]]==0)
{
	in[i]--;
{
```

f[i]存储的是指向自己的点

可是f[i]里可能有多个点，怎么存呢？

我们用一个队列存储入度为0的点，然后一个循环减去，最后找到入度不为0的就好了。

**这不就是拓扑吗？**

## 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans;
int out[100005],in[100005];
queue<int> q;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		
		in[a[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(in[i]==0){
			q.push(i);
		}
	}
    
	while(!q.empty())
	{
		int tmp=q.front();
		q.pop();
		in[a[tmp]]--;
		if(in[a[tmp]]==0)
		{
			q.push(a[tmp]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(in[i]!=0)
		{
			ans++;
		}
	}

	cout<<ans;
   return 0;
}
```

---

## 作者：Kirisame_Marisa_ (赞：7)

看题，可以想象成是有N个点，每个点的出度都为1(可能有自环?)，每个节点开始都有1只(头?)牛，每回合每个节点上**所有**的牛都沿着该节点**唯一的出边**走向~~死亡~~下一个节点，求该图中无论过了几回合后都一直拥有至少1只牛。

该图中**所有的环的长度之和**即为答案。

分析：首先我们来想一下为什么答案不会是0。如果答案为0，就意味着每个节点都在某个(不同)回合没有了牛。因为所有节点的出度都=1，所以从节点A到节点B的路(无论是直接还是间接)**有且仅有一条**，并且节点A在**最多一个环**中。所以如果节点A一旦失去了所有的牛，那么就再也不会有任何的牛到达节点A。

举一个例子。设想节点A。如果想要A失去所有牛之后再获得牛，那么我们可以知道至少有一个节点(记为B)有一条到A的有向边(记为B->A)。因为我们需要让A先失去牛，所以当A有牛时，B必然没有牛(因为B不能再向其他节点连边)，而下一个回合，A失去牛之后，B又要拥有牛。回到初始状态，**所有节点都有一只牛**，因此不会出现A(或B)先失去牛又获得牛的情况。

那么现在知道了如果节点A一直都拥有牛，那么A必定在一个环内。

所以，对于该有向图，只要去除所有不在环内的点，然后判环出答案就可以了。
Main Code:
```cpp
int n,to[200005],id[200005],ans=0;
bool inring[200005],useless[200005];
int dfs(int now)
{
    if(inring[now])return 0;
    inring[now]=1;
    return dfs(to[now])+1;
}
void dfs2(int now)
{
    useless[now]=1;
    --id[to[now]];
    if(!id[to[now]])dfs2(to[now]);
}
int main()
{
    int a;
    cin>>n;for(int i=1;i<=n;++i){cin>>a;to[i]=a;++id[a];}
    for(int i=1;i<=n;++i)if(!id[i]&&!useless[i])dfs2(i);
    for(int i=1;i<=n;++i)if(!inring[i]&&!useless[i])ans+=dfs(i);
    cout<<ans<<endl;
    return 0;
}
//将该代码小改后可以A掉NOIP2015的“信息传递”(P2661)
```

---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定 $n$ 个数的 $a$ 序列，其中每个 $a_i$ 表示现在在 $i$ 位置上的牛会变到位置为 $a_i$ 的地方。有时候，经过变换一个位置上可能有很多个牛，那么下一次这些牛的变换方式就是一样的。问无论经过多少次变换一共有多少个位置上有牛。

#### 题目分析


------------
首先考虑在何种情况下可以保证这个位置上最终一定有牛。

- 将题目给出的条件抽象为一张图，每个 $i$ 向 $a_i$ 连一条**有向**边
- 观察样例不难发现当图中出现环的时候，环上的每一个位置都必定有牛存在

根据以上分析可以将本问题转化为：给定一张图，询问共有多少个点在环上。

#### 解题思路


------------
解决此类问题通常使用**拓扑排序**。

拓扑排序的实现方式分为一下几步：

- 存储每一个点的入度并将入度为 $0$ 的点放入队列中。
- 当队列不为空时，将取出的元素 $i$ 对应的 $a_i$ 的入度 $-1$。
- 重复以上操作知道队列为空，此时入度仍不为 $0$ 的点即为环上的点。

正确性也是比较容易理解，可以考虑一个点不在环上，那么该点所指向的点也不在环上。重复当前操作可以找出所有的入度为 $0$ 的点，即为不在环上的点。反之，若一个点在环上，那么该点的入度必不为 $0$。

#### 代码实现
 

------------
 ```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>

using namespace std;
const int N = 100010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
int n,a[N],ans,in[N];
queue<int> q;
int main(){
	n = read();
	for(int i=1;i<=n;i++){
		a[i] = read();
		in[a[i]] ++;
	}
	for(int i=1;i<=n;i++){
		if(in[i] == 0){
			q.push(i); 
		}
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		in[a[u]]--;
		if(in[a[u]] == 0){
			q.push(a[u]); 
		}
	} 
	for(int i=1;i<=n;i++){
		if(in[i] != 0){
			ans++;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：翼德天尊 (赞：2)

## 【Part 1】 简述题意

本题的题意其实可以抽象理解为：

一共有 $n$ 个包裹，$n$ 个座位，刚开始每个座位上都有一个包裹。而每个座位都会贴一个标签，上面写着坐这个座位的包裹下一次应该坐到哪个座位上。无限循环。问最终有几个座位上有包裹。

## 【Part 2】 理理思路

根据上述题意，我们可以来思考这样一个问题：什么时候才能保证座位上最终一定能有包裹呢？

我们不妨将该问题抽象为一个图，每一个座位向它标签上的座位连一条有向边。

例如，对于样例来说，我们可以构建这样一幅图：



根据图形，我们不难发现，如果图中出现了环，那么环上的每一个座位最终一定有包裹。

所以问题就转化成了：给你一幅图，一共有多少个节点在环上？

是不是简单多了？

## 【Part 3】 讨论做法

那怎么求出有多少个节点在环上呢？对，我们可以使用【拓扑排序】。

我们存储每一个点的入度，然后现将入度为 $0$ 的点放入队列，用一个 $while$ 循环，只要队列不为空，就将取出来的节点所指向的座椅的入度 $-1$。最终入度依然不为 $0$ 的节点即为环上的点。

为什么这样正确？我们可以想到，如果一个节点不在环上，那么它被指向的节点也一定不在环上，所以说这条链的起点入度一定为 $0$，最终，沿着这条链，我们一定也可以将该节点变成 $0$。而如果几个节点在一个环上，那么他们就不会有任何一个节点的入度刚开始为 $0$，所以最终环上的点一定会保证入度不为 $0$。 ~~有一种链上一人犯错就会被一锅端的感觉。~~
## 【Part 4】 AC代码及注释

```cpp
#include<cstdio>
#include<queue>
using namespace std;
int n,a[100005],ans,in[100005];
queue<int> q;
int read(){
	int w=0;
	char c=getchar();
	while (c>'9'||c<'0') c=getchar();
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w;
}
int main(){
	n=read();//读入
	for(int i=1;i<=n;i++)
		in[(a[i]=read())]++;//处理初始入度
	for(int i=1;i<=n;i++)
		if(in[i]==0) q.push(i); //将入度为0的点放入队列
	while(!q.empty()){
		int now=q.front();//不断取出入度为0节点
		q.pop();
		in[a[now]]--;//将它指向的节点入度-1
		if(!in[a[now]]) q.push(a[now]);//如果入度为0了，继续放入队列
	}
	for(int i=1;i<=n;i++)
		if(in[i]) ans++;//最终入度不为0的点说明在环上
	printf("%d\n",ans);
    return 0;
}
```

**谢谢大家的观看！**

---

## 作者：Na2PtCl6 (赞：2)

## 分析题目
题意提炼后就是：把题目中给出的位置关系建成一个图，然后找出其中**在环上的点的个数**。

如样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/kei5df2w.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

点 1，3 在一个环上；点 2 在一个环上。共有 3 个点在环上。

因为在 `DAG` 上的点一定不在环上（废话），所以我们可以**用拓扑排序数出不在环上的点的个数**，然后用图上点的总数减去不在环上的点的个数即可求出答案。

## 代码实现
拓扑排序模板
```cpp
void tpsort(){
	for(int i=1;i<=n;i++)
		if(!in[i]){  //从入度为0的点开始遍历
			q.push(i);
			++res;
		}
	while(!q.empty()){
		int t=q.front();
		q.pop();
		//这个点能被取出来是因为它少了一个通向它的节点,故入度减一 
		--in[a[t]];   
		if(!in[a[t]]){  //继续遍历入度为0的点 
			++res;
			q.push(a[t]);
		}
	}
}
```

完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100004;
int n,res,a[maxn],in[maxn];
queue < int > q;

void tpsort(){
	for(int i=1;i<=n;i++)
		if(!in[i]){  //从入度为0的点开始遍历
			q.push(i);
			++res;
		}
	while(!q.empty()){
		int t=q.front();
		q.pop();
		//这个点能被取出来是因为它少了一个通向它的节点,故入度减一 
		--in[a[t]];   
		if(!in[a[t]]){  //继续遍历入度为0的点 
			++res;
			q.push(a[t]);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		++in[a[i]];  //记录入度 
	}
	tpsort();
	printf("%d",n-res);
	return 0;
}
```

---

## 作者：StudyingFather (赞：2)

其实有一种很暴力的方法，就是模拟。

把整个过程模拟上一定次数，然后判断各个位置上是否有奶牛即可。

~~（我才不会告诉你们，这个真的要靠RP，模拟次数少了容易WA，次数多了会TLE）~~

```cpp
#include <stdio.h>
#include <string.h>
int a[100005],b[100005],c[100005];
int main()
{
 int n;
 scanf("%d",&n);
 for(int i=1;i<=n;i++)
  a[i]=1;
 for(int i=1;i<=n;i++)
  scanf("%d",&c[i]);
 for(int i=1;i<=500;i++)//这个在最慢的点上跑了328ms
 {
  for(int i=1;i<=n;i++)
   b[c[i]]+=a[i];
  memset(a,0,sizeof(a));
  for(int i=1;i<=n;i++)
   a[c[i]]+=b[i];
  memset(b,0,sizeof(b));
 }
 int ans=0;
 for(int i=1;i<=n;i++)
  if(a[i])ans++;
 printf("%d",ans);
 return 0;
}
```

---

## 作者：used_to_be (赞：1)

~~惊奇地发现这题居然还能提交题解。。~~

1. 题意： $n$ 头奶牛，开始时第 $i$ 头站在 $i$ 位置，随后每次变换站在 $i$ 位置上的奶牛会换到 $a_i$ 的位置。问的是对于所有的 $i \in n$，有多少个位置始终有奶牛。

2. 思路：如果考虑用图的方式来存，那么这个图是个有向图，且每个点 $u$ **有且仅有 $1$ 个后代** $v$ ，即指向 $v$ 。我们发现，如果图中存在环，则在环上每个点的奶牛怎么也拐不出去，就会出现情况：环上的每个点总是有奶牛的。答案即是所有环上点的个数。这个过程可以用拓扑排序来解决，看到已经有很多拓扑的题解了，在这里就介绍一下环套树的做法。

3. 算法：先建立一个数组 pre ，用来记录每个点被访问的时间戳，即 Dt (Dfstime) 。每次访问到一个点时， ++Dt ，并把 pre 里点的位置设为 Dt 。这样访问过的点就都有值，反之没有被访问过的点就没有值。当在 dfs 的时发现他的子节点已经被访问过了，则说明出现环了。现在的点 $u$ 到子节点 $v$ 的边 $(u,v)$ ，环上点的个数就是 $pre_u-pre_v+1$ 。把所有环的结果加起来就是答案。

4. 代码：先循环遍历每一个点，如果这个点的 $pre_i$ 值为 $0$ ，就开始一次新的遍历。由于每次遍历颜色要不同，遍历前要把颜色加 $1$ 。 dfs 的时候把点的时间戳和颜色标好。如果后代节点未被遍历，递归遍历；反之判断如果当前节点的颜色和子节点的颜色相同，说明两个点在一个环上，就累计答案。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,Dt=0,Dc=0,ans=0;
int nxt[100001],pre[100001],clr[100001];
void dfs(int now){
	pre[now]=++Dt,clr[now]=Dc;
	if(pre[nxt[now]]==0){
		dfs(nxt[now]);
	}
	else if(clr[now]==clr[nxt[now]]){
		ans+=pre[now]-pre[nxt[now]]+1;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&nxt[i]);
	}
	for(int i=1;i<=n;i++){
		if(pre[i]==0){
			Dc++,dfs(i);//一定要注意是每次染色后 Dc++ ，而不是找到环后 Dc++ 
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：COUPDETAT (赞：1)

## Tarjan缩点
根据题意 找环

缩完点后 枚举点  把自环统计为一  统计scc_size>1的

将答案加上该scc的size即可
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mN=100100;
int dfn[mN], low[mN], dfncnt, s[mN], tp, head[mN],ans;
struct edge
{
	int t,nex,fr;
}e[0x3f3f3f],ed[0x3f3f3f];
int h[100100],N;
void add(int x,int y)
{
	e[++N].t=y;
	e[N].nex=head[x];
	e[N].fr=x;
	head[x]=N;
}
int poi[10010];
int scc[mN], sc ,sz[mN]; 
void tarjan(int u) 
{
	low[u] = dfn[u] = ++dfncnt, s[++tp] = u;
	for (int i = head[u]; i; i = e[i].nex) 
	{
		const int &v = e[i].t;
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (!scc[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) 
	{
//		ans++;
//		fir[ans] = u;
		while (s[tp] != u) scc[s[tp]] = u, sz[u]++, --tp;
		scc[s[tp]] = u,sz[u]++,--tp;	
	}
}
int n,m;
int si,a[100100];
int main()
{
//z	freopen("A.in","r",stdin);
//	freopen("B.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		a[i]=x;
		add(i,x);
	}
	for (int i=1;i<=n;i++)
    if (!dfn[i]) tarjan(i);
    int cnt=0;
	for(int i = 1; i <= n; i++)
	{
		if(sz[i] > 1) cnt += sz[i];
		if(sz[i] == 1 && a[i] == scc[i]) cnt++;
	}
	cout<<cnt;
}
```


---

## 作者：NTG_Adiord (赞：1)

SPFA跑环(反正n条边n个点，不会出现环套环的情况)
ans就是所有环的总长
代码如下

```cpp
#include <cstdio>
#include <queue>
using namespace std;
int n;
int to[100001];
int hea[100001];
int nex[100001];
int voi[100001];
int al[100001];
int gt;
int ll;
int ans;
int q=0;
queue<int> rea;
void bl(int u,int v){
	to[++ll]=v;nex[ll]=hea[u];hea[u]=ll;
}
void spfa(int nn,int np){//跑spfa,np记录深度
	voi[nn]=np;
	al[nn]=q;
	for(int w=hea[nn];nn;nn=nex[nn]){
		if(al[to[w]]==0||al[to[w]]==q){
				if(voi[to[w]]==0)spfa(to[w],np+1);
				else if(voi[to[w]]<=np)ans+=np-voi[to[w]]+1;
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int w=1;w<=n;w++){
		scanf("%d",&gt);
		bl(w,gt);
		rea.push(w);//先push
	}
	while(!rea.empty()){
		while(!rea.empty()&&voi[rea.front()]!=0)rea.pop();//判断一下这个点是否跑过了，如果跑过了就弹出
		if(!rea.empty()){
			q++;//不是一个环就不用算了
			spfa(rea.front(),1);
			rea.pop();
		}
	}
	printf("%d",ans);
}

```

---

## 作者：Genius_Star (赞：0)

### 思路

答案肯定是**在环上的点的个数**，而且答案是不为 $0$ 的。

首先我们来想一下为什么答案不会是 $0$。

如果答案为 $0$，就意味着每个节点都在某个（不同）回合没有了牛。

因为所有节点的出度都等于 $1$，所以从节点 $A$ 到节点 $B$ 的路（无论是直接还是间接）有且仅有一条，并且节点 $A$ 在最多一个环中。

所以如果节点 $A$ 一旦失去了所有的牛，那么就再也不会有任何的牛到达节点 $A$。

举一个例子：

假设有一个节点 $A$，如果想要 $A$ 失去所有牛之后再获得牛，那么我们可以知道至少有一个节点（记为 $B$）有一条到 $A$ 的有向边（记为 $B \to A$）。

因为我们需要让 $A$ 先失去牛，所以当 $A$ 有牛时，$B$ 必然没有牛（因为 $B$ 不能再向其他节点连边），而下一个回合，$A$ 失去牛之后，$B$ 又要拥有牛。

回到初始状态，所有节点都有一只牛，因此不会出现 $A$（或 $B$）先失去牛又获得牛的情况。

那么现在知道了如果节点 $A$ 一直都拥有牛，那么 $A$ 必定在一个环内。

关于怎么求环嘛！

不难发现这是一个内向树（其实是森林），然后很好证明内向树里面的环肯定是自环或者大小不为 $1$ 的强联通分量，所以跑一跑 ``tarjan`` 求出大小不为 $1$ 的强联通分量，然后特判求自环就好啦！

~~其实可以排除不在环内的点再判环输出答案，比我的做法不知道高到哪儿去了。~~

### 完整代码：

```cpp
#include <stack>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 20;
inline int read()
{
	int x = 0; char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int N;
int a[MAXN], ans = 0;

namespace SCC
{
	stack<int> sta;
	int low[MAXN], dfn[MAXN];
	bool ins[MAXN];

	int tarjan(int cur){
		static int dfnclock = 0;
		dfn[cur] = low[cur] = ++dfnclock;
		sta.push(cur), ins[cur] = true;

		int v = a[cur];
		if(!dfn[v]) low[cur] = min(low[cur], tarjan(v));
		else if(ins[v]) low[cur] = min(low[cur], dfn[v]);

		if(dfn[cur] == low[cur]){
			int cnt = 0;
			do{
				v = sta.top(); sta.pop();
				ins[v] = false; ++cnt;
			}while(v != cur);
			if(cnt > 1) ans += cnt;
		}
		return low[cur];
	}

	void solve(){
		for(int i = 1; i <= N; i++) if(!dfn[i]) tarjan(i);
		for(int i = 1; i <= N; i++) if(a[i] == i) ++ans;
	}
}


int main()
{
	cin>>N;
	for(int i = 1; i <= N; i++) a[i] = read();
	SCC::solve();
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：LHQing (赞：0)

### 题目分析：

既然题目要求经过无论多少次，问至少始终有多少点还有奶牛在。显然，题目只有两种情况，一种是大环，那么在这个环上的奶牛会不断绕圈（包括自环），无论合适，这个环上奶牛只增不减。增的情况就是有些边指入这个环，而某只奶牛进入时这个点恰好没奶牛。这个环数上奶牛数量就增加了。所以，我们只需要经过无限多次，所有非环边的奶牛都会进入环边，这样奶牛数就稳定下来。

我们需要一个能快速跳跃的数据结构，我考虑了 st 表，类似最近公共祖先的转移。即 $st_{i,j}$ 表示 $i$ 点跳 $2^{j}-1$ 次，$st_{i,j}=st_{st_{i,j-1},j-1}$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd push_back
#define all(x) x.begin(),x.end()
#define Clear(x,n) for(int i=0;i<=n;i++)x[i]=0;
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10);}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
	void DeNum(int x){printf("%d\n",x);}
}
//==============================================================================
const int N=1e5+10;
int st[N][40];
int n;
vector<int> a[N];
int p[N];
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&st[i][0]);
    for(int j=1;j<=30;j++)
    	for(int i=1;i<=n;i++)
    		st[i][j]=st[st[i][j-1]][j-1];
    for(int i=1;i<=n;i++)
    	p[st[i][30]]++;
    int ans=0;
    for(int i=1;i<=n;i++)
    	ans+=p[i]!=0;
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：zmnjkl (赞：0)

本人水的第二篇题解哦，写的不好请指出~

------------
### 题意：

一共 $N$ 头牛和 $N$ 个位置，每次下标 $i$ 的牛去到 $r_i$ 位置。某些位置经过无限次操作后永远有牛，求出所有这样的位置的数量。

### 分析：

这道题可以从入度和出度的角度来思考，将所有牛进入到位置 $i$ 的数量记录为 $i$ 的入度，入度为 $0$ 的则不符合要求。因为每个位置要保证有牛必须有牛进入，而当某个位置没有进入的牛时，这个位置最终也就不成立，并且这个位置去到的出度点的入度也会减少。最终重复删点剩余的所有点都将形成个环，环里点的数量就是最终答案。

### 思路：

这其实就是个简单的拓扑排序，每次删除所有入度为 $0$ 的点并减去对应点的入度，加入队列并重复此操作。最终求出所有入度不为 $0$ 的点的数量输出为答案（本人其实没有学过真正的拓扑排序，是通过 BFS 推出来的）。

### 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,num[114514],cnt[114514],ans;//num储存每个点的去到的对应点，cnt储存每个点的入度
int main(){
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> num[i],cnt[num[i]]++;//保存每个点的入度
	queue<int>q;
	for(int i=1;i<=n;i++)
		if(!cnt[i])q.push(i);//将入度为0的点加入队列
	while(!q.empty()){
		int t=q.front();
		q.pop();
		cnt[num[t]]--;//将每个对应点的入度-1，并查找这个点是否有入度
		if(!cnt[num[t]])q.push(num[t]);//如果有则继续加入队列，重复此操作
	}
	for(int i=1;i<=n;i++)
		if(cnt[i]!=0)ans++;//最终答案为所有入度不为0的点
	cout << ans;
} 

```


---

## 作者：_Sushi (赞：0)

#### 题目：
[P4089](https://www.luogu.com.cn/problem/P4089)
#### 分析：
最开始想到的算法肯定是暴力，但一看数据范围 $1 \le N \le 10^5$，肯定超时。考虑把牛之间的位置关系看成一张有向图，把每一个位置看成一个点，把 $a_i$ 看成从 $i$ 到 $a_i$ 的一条有向边。对于每一个点，如果它的入度为 $0$，也就是说没有牛会转移到这个点上，那么这个位置上下一次 ```shuffle``` 必然不会有牛。如果连接到某个点的所有点在经过一定次数的 ```shuffle``` 过后都会被空置，那么这个点未来也一定会被空置。是不是有点绕？看下面这个例子：         
这是一组样例：
```
6
6 1 1 2 2 3
```
表示在图上就是这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/xf89rwu7.png)
$4$、$5$ 两头牛所在的点的入度为零，一轮过后就空了，那么图就变成了这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/1aki2oou.png)
$4$、$5$ 两头牛此时所在的点虽然开始时入度不为 $0$，但连接到它的所有点在经过一次的 ```shuffle``` 过后都被空置了，因此此时它的入度也变成了 $0$，下一轮过后就空了，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/r4a0vsfm.png)
而右侧的三个点形成了一个环，入度一直大于 $0$，上面一直有牛，所以这组样例的答案就是 $3$。         
经过一次模拟，我们得出了一个结论：如果一个点上永久存在牛，那么这个点满足所有指向它的点中，至少有一个点上永久存在牛。换句话来说，就是这个点处在一个环中。       
所以，问题就转换成了求出处在环之中的点的个数，一个简单的拓扑排序判断环就可以搞定。有不懂拓扑排序的同学可以看其他几篇题解，我就不过多阐述了。
#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
int ans;
int a[500000];
int s[500000];
queue<int> q;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
    	scanf("%d",&a[i]);
    	s[a[i]]++;    //计算入度
	}
	for(int i=1;i<=n;i++)
	    if(!s[i]) q.push(i);     //先把入度为0的节点放入队列
	while(!q.empty())
	{
		x=q.front();        //从队列中取出一个节点
		q.pop();
	    if(s[a[x]]>0)
	    {
	    	s[a[x]]--;        //将这个节点指向的节点入度减一
	    	if(!s[a[x]]) q.push(a[x]);  //如果入度变为零，放入队列
		}
	}
	for(int i=1;i<=n;i++)
		if(s[i])
			ans++;      //统计入度不为0的点数（也就是处在环中的点的个数）
	printf("%d\n",ans);			
	return 0;
}
```

---

## 作者：信守天下 (赞：0)

## [洛谷传送门](https://www.luogu.com.cn/problem/P4089)
## 思路
如果一个位置不会被任何位置到达，那么一轮操作后它上面就没有奶牛了。

所以可以将这个位置删除。

然后不断重复这个过程，剩下的位置上就是始终有奶牛的。

对上述发现进行下归纳，就是只有环上始终有奶牛。

由于每个位置只会到达另外一个位置，所以不会有两个点同时属于一个环。

因此，我们只要找到所有的环即可。

可以依次从每个点出发去寻找环，为了避免重复计算，遇到已经找过的点则停止。

## 复杂度分析
### 时间复杂度
每个点只会找一次，总共$O(N)$ 。
### 空间复杂度
标记环$O(N)$ 。
## $code$
~~~cpp
#include <cstdio>
#include <iostream>

using namespace std;

const int kMaxN = 1e5 + 1;

int a[kMaxN], b[kMaxN], s[kMaxN];
int n, p, ans;

void S(int x) {  // 搜索到x
  if (s[x]) {    // x已经在栈中，找到环
    p = x;       // 记录环的起点
    return;
  }
  if (!b[x]) {        // 当前点没有到达过才处理
    b[x] = s[x] = 1;  // 标记到达、标记入栈
    S(a[x]);          // 搜索下一个点
    s[x] = 0;         // 标记出栈
    ans += p != 0;    // 找到环且还在环中
    if (p == x) {     // 到达起始点，离开环
      p = 0;
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {  // 枚举点
    S(i);                         // 找环
  }
  cout << ans;
  return 0;
}

~~~

---

## 作者：SzTC (赞：0)

### 题目大意
给定一个有向图，判断这个图中所有环上的点的数量。
### 分析做法
第一眼看到这个题目，就大概能联想到是个图论题；但是正解的拓扑排序对于我这样的蒟蒻来说又很难在考场上想到。所以，考虑用比较暴力的方法判断环。  
#### 1.纯暴力做法  
用 for 循环 + while 循环的方式，先用 for 枚举每一个点，再用 while 模拟每一个点上的牛将会怎样行动，如果到了以前到过的点，那么这段区间的点（以前到过的这个点到现在到的这个点）就都在环内，进行标记。最后再统计一下标记的点的个数。  
联系样例来理解：  
```plain
4
3 2 1 3
```
$1$ 的行动过程：$1\to3\to1$  
则将 $1,3 $标记为环  
$2$ 的行动过程：$2\to2$  
则将 $2$ 标记为环  
$3$ 的行动过程：$3\to1\to3$  
则将 $3,1$ 标记为环  
$4$ 的行动过程：$4\to3\to1\to3$  
则将 $3,1$ 标记为环  
所以最后的答案为 $3$   
#### 2.优化
观察上面的样例分析不难发现，若一个点已经在环内，那么这个点就不需要再使用 while 再进行重复标记了；若一个点将通往一个环内的点，那么这个点一定不在一个环中。  
这样优化下来，每个点只会被进行一次操作，时间复杂度为 $O(n)$ 。
### 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[111111];
int mark[111111];
int mark2[111111];
queue<int>que;//使用队列实现环的标记
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
	}
	for(int i=1;i<=n;i++)
	{
		if(mark[i] || mark2[i])continue;//如果这个点被操作过了（在环内或通向环）
		int k=i;
		while(!que.empty())que.pop();//初始化，清空队列
		while(!mark[a[k]])//在下一个点不在环内时执行
		{
			if(mark2[a[k]])//下一个点已经被走过了
			{
				int kkk=0;
				while(!que.empty())
				{
					int kk=que.front();
					que.pop();
					if(kk==a[k])kkk=1;//上一次到达这个点的时候
					if(kkk)mark[kk]=1;//剩下的点标记为环
				}
				break;
			}
			mark2[a[k]]=1;
			que.push(a[k]);
			k=a[k];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)if(mark[i])ans++;//统计答案
	cout<<ans;
	return 0;
}
```

---

