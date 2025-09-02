# [POI 2013] LUK-Triumphal arch

## 题目描述

The king of Byteotia, Byteasar, is returning to his country after a victorious battle.

In Byteotia, there are ![](http://main.edu.pl/images/OI20/luk-en-tex.1.png) towns connected with only ![](http://main.edu.pl/images/OI20/luk-en-tex.2.png) roads.

It is known that every town can be reached from every other town by a unique route,    consisting of one or more (direct) roads.

    (In other words, the road network forms a tree).

The king has just entered the capital.

Therein a triumphal arch, i.e., a gate a victorious king rides through, has been erected.

Byteasar, delighted by a warm welcome by his subjects, has planned a    triumphal procession to visit all the towns of Byteotia, starting with the capital he is currently in.

The other towns are not ready to greet their king just yet -    the constructions of the triumphal arches in those towns did not even begin!

But Byteasar's trusted advisor is seeing to the issue.

    He desires to hire a number of construction crews.

    Every crew can construct a single arch each day, in any town.

    Unfortunately, no one knows the order in which the king will visit the towns.

The only thing that is clear is that every day the king will travel from the city he is currently in to a neighboring one.

The king may visit any town an arbitrary number of times    (but as he is not vain, one arch in each town will suffice).

Byteasar's advisor has to pay each crew the same flat fee, regardless of how many arches this crew builds.

Thus, while he needs to ensure that every town has an arch when it is visited by the king, he wants to hire as few crews as possible.

Help him out by writing a program that will determine the minimum number    of crews that allow a timely delivery of the arches.


给一颗 $n$ 个节点的树（$n \le 3 \times 10^5$），初始时 $1$ 号节点被染黑，其余是白的。两个人轮流操作，一开始 B 在 $1$ 号节点。每一轮，A 选择 $k$ 个点染黑，然后 B 走到一个相邻节点，如果 B 当前处于白点则 B 胜，否则当 A 将所有点染为黑点时 A 胜。求能让 A 获胜的最小的 $k$ 。


## 说明/提示

给一颗树，1号节点已经被染黑，其余是白的，两个人轮流操作，一开始B在1号节点，A选择k个点染黑，然后B走一步，如果B能走到A没染的节点则B胜，否则当A染完全部的点时，A胜。求能让A获胜的最小的k

## 样例 #1

### 输入

```
7
1 2
1 3
2 5
2 6
7 2
4 1
```

### 输出

```
3
```

# 题解

## 作者：vectorwyx (赞：91)

又是一道没看任何提示（包括标签）一遍过的dp题，写篇题解纪念一下。

首先看出 $k$ 具有单调性，因此采用二分答案将最优性问题转化为判定性问题。

其次，B 一定不会走回头路。因为走回头路就说明 B 的某一次选择不是所有选择中最优的，那 B 为啥不在那次选择时就采取最优策略呢？走回头路只会多给 A 染色的机会，那 B 的胜算就更小了。

既然 B 不会走回头路，那么当 B 走到结点 $i$ 时，A 必须在 B 做下一次选择之前把结点 $i$ 的所有儿子染成黑色，不然 B  下一次走的时候走到结点 $i$ 没来得及染成黑色的儿子就胜利了。但是只**用一次染色可能无法让结点 $i$ 的所有儿子都变成黑色**，这时候就要未雨绸缪，**在之前几次染色时提前把这些没法染成黑色的儿子染成黑色**。换句话说，我们需要向“上一级”申请支援，因为以 $i$ 为根的子树内部已经无法“消化”掉需要染黑的结点了。

那未雨绸缪的时机又该如何确定呢？假设在 B 走到结点 $j$ 时我们发现结点 $j$ 的儿子数小于 $k$，也就是说染色的次数会产生剩余，那我们就需要看一下结点 $j$ 的儿子里有没有需要支援的，把剩余的次数分配给它们。如果剩余的次数仍然够，那就又要向 $j$ 的“上一级”求援了。

令 $f_{i}$ 表示以 $i$ 为根的子树（不包括 $i$）需要多少次数的支援，$f_{i}=cnt_{i}-k+\sum \max(f_{p},0)$。 其中 $cnt_{i}$ 为 $i$ 的儿子数量，$p$ 为 $i$ 的儿子结点。如果 $f_{1}\le 0$，那么当前二分到的 $k$ 就是合法的，否则就是不合法的。

二分的复杂度为 $O(\log v)$，$v$ 为值域。一次 $dp$ 复杂度为 $O(n)$，总复杂度为 $O(n\log v)$。这里我又对值域做了个小优化，因为结点 $1$ 的所有儿子在第一次染色中一定要全被染成黑色而且不可能有支援，因此二分答案的下界可以取 $cnt_{1}$。同时，如果 $a$ 不小于任一结点的儿子数量，那么 $k=a$ 一定是一个合法的答案，二分答案的上界只需要取到 $a$。加了这个优化后我的代码拿到了最优解 rk1 /cy。

代码如下（给个赞再走吧QAQ，谢谢您！）：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){ int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') fh=-1; ch=getchar(); } while(isdigit(ch)){ x=(x<<1)+(x<<3)+ch-'0'; ch=getchar(); } return x*fh; }

const int N=3e5+5;
struct Edge{
	int to,next;
}e[N<<1];
int f[N],n,head[N],tot,k,son[N];

void connect(int x,int y){
	e[++tot]=(Edge){y,head[x]};
	head[x]=tot; 
} 

void _dfs(int now,int from){
	for(int i=head[now];i;i=e[i].next){
		int p=e[i].to;
		if(p==from) continue;
		son[now]++;
		_dfs(p,now);
	}
}

void dfs(int now,int from){
	f[now]=son[now]-k;
	for(int i=head[now];i;i=e[i].next){
		int p=e[i].to;
		if(p==from) continue;
		dfs(p,now);
		if(f[p]>0) f[now]+=f[p];
	}
}

int main(){
	cin>>n;
	fo(i,1,n-1){
		int x=read(),y=read();
		connect(x,y);
		connect(y,x); 
	}
	_dfs(1,0);
	int L=son[1],R=0,ans;
	fo(i,1,n) R=max(R,son[i]);
	while(L<=R){
		k=(L+R)>>1;
		dfs(1,0);
		if(f[1]<=0) R=k-1,ans=k;
		else L=k+1;
	}
	cout<<ans;
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：Captain_Paul (赞：12)

因为所求的值类似于一个覆盖范围，所以无法直接求解

用二分转化为判定性问题

然后就是树形$dp$了

可以看出B一定只会从根节点走到叶子结点，不会走回头路

（走回头路相当于自己啥也没干还让A多染了几次色）

设$f[i]$表示在$i$的子树中（不包括$i$）还需要染色的次数

转移就是求出$i$的子节点的$f$值总和，记为$sum$

然后$f[i]=max(0,sum+d[i]-mid)$

$d[i]$表示$i$的度数（不包括它的父节点）

每一次二分都做一次dp

如果$f[1]==0$，则答案可行

关于数据范围：bzoj是3e5，luogu没给，但是1e5可以过

~~我先在luogu做的交到bzoj还RE了一发~~

```
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define reg register
using namespace std;
const int N=3e5+5;
struct node
{
	int to,nxt;
}edge[N<<1];
int n,num,head[N],f[N],mid;
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while (!isdigit(c)&&c!='-') c=getchar();
	if (c=='-') c=getchar(),w=-1;
	while (isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*w;
}
inline void add_edge(int from,int to)
{
	edge[++num]=(node){to,head[from]};
	head[from]=num;
}
void dfs(int k,int fa)
{
	int sum=0;
	for (reg int i=head[k];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (v==fa) continue;
		dfs(v,k); sum+=f[v]+1;
	}
	f[k]=max(sum-mid,0);
}
int main()
{
	n=read();
	if (n==1) {puts("0"); return 0;}
	for (reg int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add_edge(x,y); add_edge(y,x);
	}
	int l=1,r=n-1,ans=0;
	while (l<=r)
	{
		memset(f,0,sizeof(f));
		mid=(l+r)>>1; dfs(1,0);
		if (!f[1]) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：S_S_H (赞：9)

### 一道很好的练树形DP的题 ，思维含量真的高

先挂上体面吧：

让·夏格伦会玩一个叫“凯旋门”的游戏：现在有一棵n个节点的树，表示一个国

家，1号点代表这个国家的首都 。

这个游戏由两个人一起玩 一个玩家扮演视察国家的国王，另一个扮演建立凯旋门的建筑师 。

一开始只有首都有凯旋门 国王每次会从当前所在城市移动到一个相
邻的城市。

在国王每次移动前，建筑师可以选择国家内任意不超过k个城市建造出凯旋门。

如果在任意一个时刻，国王所在的城市没有凯旋门 那么国王会很生气，扮演
建筑师的玩家就输了。

如果所有的城市都建立起了凯旋门而国王一直没有走到没有凯旋门的城市，那么建筑师就胜利了。

Foreseeable不会建筑，所以他扮演国王，而让·夏格伦则“扮演”建筑师（他本来就是建筑师不需要扮演）。

容易发现k的大小非常影响游戏有趣度…… 如果k太大，那么建筑师可以在国王行动前就在所有城市建出凯旋门，那么国王就没有胜利的希望了，这样Foreseeable会掀桌不玩。

如果k太小，那么Foreseeable很有可能会发挥自己所剩无几的智商走到一个没有凯旋门的地方  让·夏格伦想享受虐Foreseeable的快感 所以你要帮他确定最小的k，使得在这个游戏中，如果建筑师足够聪明的话，建筑师必胜



------------

有没有发现如果看这个题面很容易发现可以二分答案？毕竟在题面的末尾给了你提示。

二分答案log级，数据范围原题是3e5,也就是还需要一个O(n)级算法

树的话......考虑树形DP，毕竟它是O(n)级的

先考虑题目中说了，B很有可能会发挥自己所剩无几的智商

这其实就是变相的告诉我们B一定会向叶子节点走，不会往回走

因为B要赢，而走回头路相当于自己啥也没干还让A多染了几次色

这样当B走到一个节点时，假设之前A已染完B所以的祖先(与之前状态无关)

那么状态便只与它的子树有关

我们设状态dp[i]为在i号节点的子树中还需要多染色的点

考虑一下：

如果i有m个儿子，而m<k的话，毫无疑问B可以向下走

若m>k呢？显然B会走m-k中的一个顶点，获胜

这是不是说只要有儿子节点个数>k的，就不行呢...显然不是

因为A可以在m<k是，将k-m个多余节点分配下去

所以对于一个状态，我们需要同时考虑它的贡献和代价

就可以递归从叶子节点开始找

每次计算一下i的子树中有多少节点还需要染色，如果加上i的贡献还是不行

的话，就记录状态，和父节点合并

反之如果可行甚至有剩余，就返回0，因为既然我这颗子树不需要领导批钱

(QAQ)就没代价，而且儿子节点肯定不能给父亲节点贡献啊。

我们发现这样树形DP的一套体系就已经出来了，是不是很神奇？！！！

这也是树形DP的妙处所在，和状压不同，它更考察思维。你会感觉完成的

DFS函数完美无缺，多一行都累赘，思维美妙(陶醉)

DFS函数：

```cpp
void dfs(int now,int fa,int k){
	int sum=0;
	for(int i=head[now];i;i=e[i].next){
		if(e[i].to==fa) continue;
		dfs(e[i].to,now,k);
		sum+=dp[e[i].to]+1;
	}
	dp[now]=max(sum-k,0);
}
```
最后给出两种二分板子，个人认为挺常见的

一：
```cpp
while(l<=r){
	int mid=l+((r-l)>>1);
	if(check(mid)){
		ans=mid;
		r=mid-1;
	}
	else l=mid+1;
}
```
我最开始用的板子，mid=l+((r-l)>>1)......就是快一点点防爆int

二：
```cpp
while(l<r){
	int mid=l+((r-l)>>1);
	if(check(mid)){
		ans=mid;
		r=mid;
	}
	else l=mid+1;
}
```
一样没什么区别

虽然简单，但是不得不说二分真的很容易敲挂...落个-1，+1，=号什么的

(只是我比较弱)

完整代码：

```cpp
#include<iostream>
#include<cstdio>
#include<memory.h>
const int maxn=301000;
using namespace std;
int n,etot,head[maxn],ans,dp[maxn];
struct node{
	int to,next;
}e[maxn];
void add(int u,int v){
	e[++etot].to=v;
	e[etot].next=head[u];
	head[u]=etot;
}
void dfs(int now,int fa,int k){
	int sum=0;
	for(int i=head[now];i;i=e[i].next){
		if(e[i].to==fa) continue;
		dfs(e[i].to,now,k);
		sum+=dp[e[i].to]+1;
	}
	dp[now]=max(sum-k,0);
}
bool check(int k){
	dfs(1,0,k);
	if(dp[1]==0) return true;
	else return false;
}
int main(){
	scanf("%d",&n);
	if(n==1){
		printf("0");
		return 0;
	}
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	int l=1,r=(1<<30);
	while(l<=r){
		int mid=l+((r-l)>>1);
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
} 
```
## 最后祝大家CSP NOI XXXOI RP++! ! !


---

## 作者：Ryan_ (赞：6)

不懂得看这里，个人认为自己写的题解比较容易看懂  ~~可能是自己比较菜吧~~

**思路：**

**二分+树形dp**

输入被卡了五分钟有点烦，下次要记得数的读边只需读入n-1条边（低级错误）

**代码的关键部分**


```
inline void dfs(int u,int fa) {
	int sum=0;
	for(int i=first[u]; i; i=nxt[i]) {
		int v=go[i];
		if(v==fa)continue;
		dfs(v,u);
		sum+=f[v]+1;
	}
  f[u]=max(sum-mid,0);

}
```

关于这个方程解释一下


```
f[u]=max(sum-mid,0);
```

---


我们不断搜索去边，然后回溯更新每一个阶段需要被染色的数量；

假设需要被染色的节点数量不足k，即sum-mid<0,那我们取0，原因是每次染色的机会是从后往前推的，即使仍然有染色的机会也不能更新前面的状态；

而如果需要染色的节点数量大于k，即sum-mid>0，那么我们显然可以累加到父亲节点，在回溯到父亲节点的时候再统一处理，因为在B点在父亲时是可以对儿子节点进行染色的（前提是sum-mid>0，即仍有染色次数），此处区别于上面那种情况；

所以我们每次二分mid

如果f[1]=0，显然是合法的，我们就缩小mid




**AC代码如下：**


```
#include<bits/stdc++.h>
using namespace std;
const int N=2000005;
int first[N],nxt[N],go[N],tot,f[N],mid;
void add(int x,int y) {
	nxt[++tot]=first[x];
	first[x]=tot;
	go[tot]=y;
}
inline void dfs(int u,int fa) {
	int sum=0;
	for(int i=first[u]; i; i=nxt[i]) {
		int v=go[i];
		if(v==fa)continue;
		dfs(v,u);
		sum+=f[v]+1;
	}
	f[u]=max(sum-mid,0);
}
int main() {
	int n;
	scanf("%d",&n);
	if(n==1)printf("0"),exit(0);
	for(int i=1,x,y; i<n; i++) {
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	int l=1,r=1<<30,ans=0;
	while (l<r) {
		memset(f,0,sizeof(f));
		mid=(l+r)>>1;
		dfs(1,0);
		if (!f[1])r=mid;
		else l=mid+1;
	}
	printf("%d\n",r);
	return 0;
}
```



---

## 作者：Adove (赞：3)

此题的答案k具有可二分性

那么我们可以二分答案k，然后跑一个树形DP

令$dp[i]$表示到节点$i$时需要再多染色的点数

那么有$dp[i]=\max(\sum_{fa[j]=i} (dp[j]+1)-k,0)$

若$dp[1]=0$则答案k可行

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1e5+5;

int n,np;
int h[MAXN],f[MAXN];
struct rpg{
	int li,nx;
}a[MAXN<<1];

void add(int ls,int nx)
{
	a[++np]=(rpg){h[ls],nx};h[ls]=np;
	a[++np]=(rpg){h[nx],ls};h[nx]=np;
}

void dfs(int x,int fa,int mid)
{
	int sum=0;f[x]=0;
	for(int i=h[x];i;i=a[i].li){
		if(a[i].nx!=fa){
			dfs(a[i].nx,x,mid);
			sum+=f[a[i].nx]+1;
		}
	}f[x]=max(sum-mid,0);
	return;
}

bool check(int mid)
{
	int sum=0;f[1]=0;
	for(int i=h[1];i;i=a[i].li){
		dfs(a[i].nx,1,mid);
		sum+=f[a[i].nx]+1;
	}f[1]=max(sum-mid,0);
	return !f[1];
}

int main()
{
	scanf("%d",&n);for(int i=1;i<n;++i){int x,y;scanf("%d%d",&x,&y),add(x,y);}
	int l=0,r=n;
	while(l<r){
		int mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}printf("%d\n",l);
	return 0;
}
```

---

## 作者：Forever_Lin (赞：3)

二分答案+树形dp

对于dp的过程

dp[i]表示当B在点i时，A要提前染色i的直接儿子中的个数

son[i]表示i的直接儿子个数,j是i的直接儿子

则$dp[i]=max(\sum_{j}dp[j]+son[i]-mid,0)$

如果dp[1]==0 满足条件

继续二分

---

## 作者：Isprime (赞：2)

仔细阅读题面可以发现 B 只会以最优策略从上往下走。（如果没发现请仔细阅读题面（？））所以染色一定是一层层从上往下染。

第一眼看到这题觉得是求一棵树中儿子最多的结点的儿子个数，交上去发现获得了 $30pts$ 的好成绩。

然后发现这解法是个完全错误的解法，能混三十分是要怒骂出题人的。为什么呢？

看下面这组数据。

![](https://cdn.luogu.com.cn/upload/image_hosting/udfil50g.png)

答案是 $2$，但是如果按照上面的解法求出来是 $3$。

我们看看这个答案是怎么来的。首先 A 把 $2,3$ 号结点染色，B 走向 $2$ 号节点，A 把 $4,5$ 号结点染色，A 胜利。

于是我们可以发现另一个很重要的事：给每一结点的儿子们染色时**如果可染色数大于这一结点的儿子数则要继续下去给儿子的儿子染色**，这是一个虽然很显然但是很容易被忽略的事情。

我们考虑一个从下往上的树形 dp 来判断一个 $k$ 是否可行：设 $f_i$ 表示 $i$ 结点需要上层结点的多余染色的数量，则有 $f_i=tot+\Sigma f_j-k$，其中 $tot$ 表示一个结点的儿子总数。

感性理解一下，一个结点需要染色的结点包括它自身的儿子和它的子树中需要上层多余染色的结点。这样如果对于结点 $i$ 有 $f_i\leq0$ 则以 $i$ 为根的子树在染色数为 $k$ 时可以让 A 胜利。我们只需要对 $1$ 号结点进行判断即可。

至于 $k$，可以二分答案，下界为 $0$（如果你获得了 $90pts$ 的好成绩并且 WA#2 那么请检查你的下界是不是设成一了，因为如果这棵树只有根节点它是不需要染色的），上界为 $n$（显然 $k=n$ 时一次染完整棵树，A 一定可以赢）。

Code 
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	int res=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') {res=res*10+ch-'0'; ch=getchar();}
	return res*f;
}
const int MAXN=300005;
int n,ecnt,ans;
int f[MAXN];
int id[MAXN];
int head[MAXN];
int l,r,mid;
struct Edge{
	int next,to;
}e[MAXN<<1];
inline void add(int u,int v) {
	e[++ecnt].next=head[u];
	e[ecnt].to=v;
	head[u]=ecnt;
}
inline void dfs(int x,int fa) {
	int tot=0,cnt=0;
	for(register int i=head[x];i;i=e[i].next) {
		if(e[i].to==fa) continue;
		dfs(e[i].to,x);
		tot++;
		cnt+=f[e[i].to];
	}
	f[x]=max(0,tot-mid+cnt);
}
signed main() {
	n=read();
	for(register int u,v,i=1;i<n;++i) {
		u=read(); v=read();
		add(u,v); add(v,u);
	}
	l=0; r=n;
	while(l<=r) {
		mid=(l+r)>>1;
		dfs(1,0);
		if(!f[1]) r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P3554)

首先，我们可以发现这题的可行方案具有单调性，所以可以考虑用 二分 + $\mathcal O(n)$ check 来寻找最优答案

显然，我们只需要考虑从根往下走的情况下，也就是不需要考虑回头  
因为在回溯的时候可以“无压力”地染色，回溯后再往下走 肯定比 直接往下走的代价小。所以，如果我们已经计算过了所有直接往下走的代价，就已经覆盖了所有的答案。

设 $f_i$ 表示 $i$ 的子树内（不包括 $i$）需要祖先来染色的节点个数，也就是说这些节点在 B 走到 $i$ 的祖先的时候就需要被染色  
$k$ 为当前二分到的，一次操作可以染色的节点个数

转移方程：$f_x=\lbrace\sum f_y \rbrace+d_x-k$  
其中 $d_x$ 为 $x$ 的子节点个数，$y$ 为 $x$ 的儿子

在求出 $f$ 数组后，如果 $f_1=0$ 说明可行，否则不可行

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=300010;
const int Maxm=Maxn<<1;
int nxt[Maxm],to[Maxm];
int head[Maxn],d[Maxn],f[Maxn];
int n,val,ans,edgecnt;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
inline void add(int x,int y)
{
    ++edgecnt;
    nxt[edgecnt]=head[x];
    to[edgecnt]=y;
    head[x]=edgecnt;
}
void dfs(int x,int fa)
{
    int tot=d[x]-val;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==fa)continue;
        dfs(y,x),tot+=f[y];
    }
    f[x]=max(0,tot);
}
bool check()
{
    memset(f,0,sizeof(f));
    dfs(1,0);
    return f[1]==0;
}
int main()
{
    // freopen("in.txt","r",stdin);
    n=read();
    for(int i=1;i<n;++i)
    {
        int x=read(),y=read();
        add(x,y),add(y,x);
        ++d[x],++d[y];
    }
    for(int i=2;i<=n;++i)
    --d[i];
    int l=0,r=n-1;
    while(l<r)
    {
        int mid=(l+r)>>1;val=mid;
        if(check())r=mid;
        else l=mid+1;
    }
    printf("%d\n",l);
    return 0;
}
```

---

## 作者：lgswdn_SA (赞：2)

### [$\texttt{POI-Triumphal arch}$](https://www.luogu.com.cn/problem/P3554)

由于一旦 B 进入了一个子树，那么他就不会出来（因为不会免费赠送 A 一个涂色的机会）。所以这个问题仍然适用和子树相关的树形 $dp$。

我们对 $k$ 进行二分答案。

对于一个节点 $u$，如果 B 走到了 $u$，那么在下一步前必须保证 $u$ 的所有儿子节点都被染色。完成染色有两种方法：第一种，在下一步前赶快把这几个点全部染上；第二种，在 B 走到 $u$ 前就染上这里的一些点。当然，如果可以选择第一种，那么就没有必要选择第二种，我们总是希望可以独立完成任务然后造福后人。

所以我们可以设立状态，表示这个节点需要自己的祖先提前染色多少节点才能覆盖住整个子树。

最终要求根节点为 $0$。

对于转移，一个节点需要的，即给自己的儿子节点染色所需要的和来自自己儿子子树的求助。因为儿子没法帮助祖先，所以如果发现自己还有很多空余的染色机会没用或者正好用完，那么 $f_u=0$

要注意 $n=1$ 时需要特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300009;
vector<int>e[N];
int f[N];
int dp(int u,int fa,int k) {
	for(int i=0,v;i<e[u].size();i++)
		if((v=e[u][i])!=fa) {
			dp(v,u,k);
			f[u]+=(1+f[v]);
		}
	f[u]=max(0,f[u]-k);
}
int main() {
	int n; scanf("%d",&n);
	if(n==1) return puts("0"),0;
	for(int i=1,u,v;i<n;i++) 
		scanf("%d%d",&u,&v),e[u].push_back(v),e[v].push_back(u);
	int l=1,r=n-1,k,ans;
	while(l<=r) {
		k=(l+r)/2;
		memset(f,0,sizeof(f)), dp(1,0,k);
		if(f[1]==0) r=k-1,ans=k;
		else l=k+1;
	} 
	printf("%d",ans);
	return 0;
}
```

---

## 作者：HC20050615 (赞：1)

# 思路
首先我们知道B一定不会走回头路,他只会朝着叶节点的方向走，因为他往回走一定没有他一开始就选择往回的另一条路走更优，只会让A多染几个黑点。因此，我们知道，当B走到某一个节点的时候，我们只需要涂该结点的子树，因为我们知道B并不会回头，所以该子树外的点他一定是走不到的。只要我们将其逼死（让他走到一个涂黑的叶子节点上去），我们就可以慢慢来涂其他的点了。

然后我们发现若直接求最小值一定很困难，可以利用二分，将最优性问题变为存在性问题。

我们考虑A失败的原因，一定是B走到了某一个节点，而这次涂色无法将其所有的子节点全部染黑（因为B一定会找那个白点走，然后获胜），那这是否意味着我们只要让 $k$ 大于儿子最多的节点的儿子个数就行了呢？其实并不是的。因为之前涂色时，并不是每一次涂色都一定会将所有的涂色次数全部用完，会留一些来让我们提前涂以后的点，让本来无法解决的点也能得到解决。有位大佬的用词很好，这叫做“未雨绸缪”。

那我们该如何安排这些机会去尽可能的保证获胜呢？

我们可以令数组 $f[i]$ 表示 $i$ 号点所需要的提前涂色的次数，则有以下转移式：
$$
f[i]=\max(0,child[i]+\sum{f[v[i]]}-k)
$$

上式中 $child[i]$ 指节点 $i$ 的儿子个数。$v[i]$ 指 $i$ 的所有儿子。

简单理解一下，就是将每个节点涂色后多余的涂色机会给他的儿子。

注意，有人可能会会问（~~还是说只有我会不知道~~），B向下走后不就不用再考虑其他的子树了吗，为什么是取所有的和呢？因为在B走这一步的时候，他会看你那个子树的防守最薄弱（涂色少）的去走，如果你只让一个子树绝对安全，他走其它的路就会导致A输掉。木桶原理大家都懂。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int v[300001];
int nxt[300001];
int d[300001];
int children[300001];
int tot;
inline void add(int x,int y)
{
	v[++tot]=y;
	nxt[tot]=d[x];
	d[x]=tot;
	return ;
}
int f[300001];
int mid;
inline void get_children(int now,int last)
{
	for(int i=d[now];i;i=nxt[i])
	{
		if(v[i]!=last)
		{
			get_children(v[i],now);
			children[now]++;
		}
	}
	return ;
}
inline void dfs(int now,int last)
{
	for(int i=d[now];i;i=nxt[i])
	{
		if(v[i]!=last)
		{
			dfs(v[i],now);
			f[now]+=f[v[i]];
		}
	}
	f[now]=max(f[now]+children[now]-mid,0);
	return ;
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	get_children(1,-1);
	int left=0,right=0;
	for(int i=1;i<=n;i++)
	{
		right=max(right,children[i]);
	}
	while(left<right)
	{
		mid=(left+right)>>1;
		memset(f,0,sizeof(f));
		dfs(1,-1);
		if(f[1])
		{
		    left=mid+1;
		}
		else
		{
			right=mid;
		}
	}
	cout<<left<<endl;
	return 0;
}
```


---

## 作者：风羽跃 (赞：0)

题目翻译得已经很清晰了。

求“让 A 获胜的最小的 $k$ ”，容易想到**二分答案**，再由 $n$ 的范围可以进一步确认为 $O(n\log n)$ 的算法。这样我们只需要解决判定的问题了。

考虑运用贪心思想扮演 A 和 B:

1. B 在移动的时候**一定不会走回头路**，因为 B 走回头路说明之前决策不是最佳决策，一定存在最佳决策能替换现有决策（楼上几篇也都有提到）；

2. A 一定会优先考虑把 B 所在节点的儿子们涂黑（因为如果儿子们有没涂黑的 B 接着就能踩上），然后多余的“颜料”留给 B 所在节点的儿子的儿子，以此类推……发现我们只关心每个子树需要父亲的多少支援，这个信息是可以自低向上递推的，满足最优子结构，因此可以用树形 DP 在 $O(n)$ 时间内判定。

说一下程序实现的主要坑点：

1. 二分答案时要注意 $l$ 和 $r$ 的奇偶性问题，否则容易写成死循环；

2. 如果一个子树所需的支援小于 $0$，即子树有多余的颜料，直接扔掉，该子树的 $f$ 值设成 $0$，因为儿子不能支援父亲！

3. $1$ 号根节点已经被涂黑；

4. 注意二分要左开右闭（满足条件的情况下尽量缩小 $k$）；

5. 链式前向星存图边数组要开 $2$ 倍。

AC代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>

#define maxn 300005
#define INF 0x3f3f3f3f

using namespace std;

int n,m;

int cnt,head[maxn],nxt[maxn<<1],to[maxn<<1];
int ans;
int f[maxn];

inline void add(int u,int v)
{
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}

inline void dp(int x,int fa,int k)
{
	f[x]=-k;
	int cnt=0;
	for(int e=head[x];e;e=nxt[e]){
		int y=to[e];
		if(y==fa) continue;
		cnt++;
		dp(y,x,k);
		f[x]+=f[y];
	}
	f[x]+=cnt;
	f[x]=max(0,f[x]);
}

inline bool check(int k)
{
	dp(1,0,k);
	return f[1]<=0;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n-1;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	int l=1,r=n-1;
	while(l<r){
		int mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<r<<endl;
	return 0;
}
```


---

## 作者：程门立雪 (赞：0)

# LUK-Triumphal arch

~~(学长推荐的，说是好欺负的题)~~

首先，答案$k$具有单调性， $k$越大, 正确的可能性越大，所以考虑二分$k$.

然后，用树形DP进行检查。

1. 一定要把$B$ 所在节点的所有儿子都涂上色。但是有时可能无法一次让该节点的儿子全都涂黑，所以可以提前将部分点涂黑。
2. $B$一定不会走回头路，等于白给了$A$涂色的机会。

$f[i]$表示在$i$的子树中（不包括$i$），染色$k$个后还需要的染色次数。

$son[i]$表示$i$点儿子的个数，$sum$表示$f[i$ 的子节点 $]$ 的和。

$f[i] = max(0, sum + son[i] - k)$

对于每次二分$k$值，进行一次DP，如果$f[1] <= 0$,说明答案可行。
```c
#include <cstdio>
#include <iostream>
#define orz cout << "AK IOI" <<"\n"

using namespace std;
const int maxn = 3e5 + 10;

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48);ch = getchar();}
	return x * f;
}
int n;
struct node{
	int u, v, nxt;
}e[maxn << 1];
int js, head[maxn];
void add(int u, int v)
{
	e[++js] = (node){u, v, head[u]};
	head[u] = js;
}
int son[maxn], f[maxn];
void dfs(int u, int fa)
{
	for(int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == fa) continue;
		son[u]++;
		dfs(v, u);
	}
}
void dfs2(int u, int fa, int mid)
{
	f[u] = son[u] - mid;
	for(int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == fa) continue;
		dfs2(v, u, mid);
		if(f[v] > 0) f[u] += f[v];
	}
}
int main()
{
    //freopen(".in","r",stdin); 
    //freopen(".out","w",stdout);
    n = read();
    for(int i = 1; i < n; i++)
    {
    	int u = read(), v = read();
    	add(u, v), add(v, u);
	}
	dfs(1, 0);
	int l = son[1], r = 0, ans;
	for(int i = 1; i <= n; i++) r = max(r, son[i]);
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		dfs2(1, 0, mid);
		if(f[1] <= 0) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d", ans);
	return 0;
}

```


---

## 作者：漠寒 (赞：0)

## 分析

对于 $A$ 来说，最坏情况即 $B$ 一路走到他最不好拦下的叶子结点，因为 $B$ 不可能往回走，否则就浪费了，任 $A$ 宰割。

对于每一个节点来说， $A$ 需要确保两个事情，一个是保住它的所有子节点，二是用剩余的力量去提前处理它的后代们的问题。易得这是一个树形 $DP$ ，而我们可以二分列举 $A$ 的力量，然后用它去解决问题，判断是否能处理。

对于 $dp$ 的转移式，我们通过上述分析可以得出对于某个节点，它对祖先们只有需要分担和不需要两种状态，不会去帮祖先分担，因此 $dp$ 值要么为0，要么为它需要祖先帮忙分担的力量。

因此，我们可以得到核心转移式。

```
sum+=f[v]+1;

f[u]=max(0,sum-mid);
```

有了这个，最后只要得到 $f_1=0$ ，即根节点有该条件就能完美地处理所有节点的问题，不需要某个神秘力量在帮根节点分担，说明 $mid$ 可行，存入 $ans$ 并更新 $right$ ，查找更小答案，否则更新 $left$ ，不断缩短，得出答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[300001],le,ri,mid,ans,head[300001],tot;
struct node{//邻接表 
	int to,next;
}a[600001];
void check(int u,int fr,int k){//深搜 
	int sum=0;
	for(int i=head[u];i;i=a[i].next){
		int v=a[i].to;
		if(v==fr)continue;//判断父节点 
		check(v,u,k);
		sum+=f[v]+1;//染色子节点，并帮忙分担 
	}
	f[u]=max(0,sum-k);//如果能力超出需要，只说明不需要祖先帮忙分担，无法做出更多贡献 
}
void read(int &res){
	res=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+c-48;c=getchar();}
}
void add(int q,int m){
	a[++tot].to=m;
	a[tot].next=head[q];
	head[q]=tot;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		read(x);read(y);
		add(x,y);
		add(y,x);
	}
	le=0;ri=n;
	while(le<=ri){
		int mid=(le+ri)>>1;
		check(1,0,mid);
		if(f[1]==0){//可行，更新答案 
			ans=mid;
			ri=mid-1;
		}
		else le=mid+1;
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：Mine_King (赞：0)

首先很好想到的一点是，如果 $k$ 满足要求，那么 $k+1$ 一定也满足要求。  
于是可以用二分答案求解。  

求一个答案 $k$ 是否可行需要树形DP来解决。

首先要知道两点：

- $A$ 每次都要把 $B$ 当前节点的儿子都染掉，否则 $B$ 找一个白色的儿子就获胜了
- $B$ 不会走回头路，因为走回头路相当于啥都没干还让 $A$ 多染了一次色

设 $f_i$ 表示 $B$ 在 $i$ 的子树中（不包括 $i$），当前染完后剩下的未被染色的点的个数。  
为什么不包括 $i$ 呢？因为 $B$ 每次都必须走一步，就算它在点 $i$，走完一步也会到它的子树中。  
可以推出  
$$f_i=max(0,(\sum f_j+1)-k)$$  
其中 $j$ 表示 $i$ 的子节点。  

解释一下：未被染色的点的个数自然是其所有子树未被染色的点的总和，因为 $f_j$ 中未包含 $j$，所以有个 $+1$。然后，我们再用一次染色，就是 $-k$。这时，如果都染完了，甚至还会多一些点（也就是当前染色剩下的点不足 $k$ 个），$f_i$ 就会变为负数，此时应该让它变成 $0$，防止影响后面的答案。

如果这个 $k$ 满足条件，那么最后 $f_1$ 就会变成 $0$。

**code:**
```cpp
#include<cstdio>
using namespace std;
int n,l=1,r,mid,f[300005];
struct graph
{
	int tot;
	int hd[300005];
	int nxt[600005],to[600005];
	void add(int u,int v)
	{
		tot++;
		nxt[tot]=hd[u];
		hd[u]=tot;
		to[tot]=v;
		return ;
	}
}g;
void dfs(int now,int fa)
{
	f[now]=0;//注意初始化！
	for(int i=g.hd[now];i;i=g.nxt[i])
		if(g.to[i]!=fa)
		{
			dfs(g.to[i],now);
			f[now]+=f[g.to[i]]+1;
		}
	f[now]-=mid;
	if(f[now]<0) f[now]=0;
	return ;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g.add(u,v);
		g.add(v,u);
	}
	r=n-1;//每次B必定要走一步，所以1不用染色，所以k的最大值只能是n-1,第一步也就是除了1其他点都染完，B无论怎么走都会进黑色，再把1染掉即可。
	while(l<r)
	{
		mid=(l+r)/2;
		dfs(1,0);
		if(f[1]==0) r=mid;
		else l=mid+1;
	}
	printf("%d\n",r);
	return 0;
}
```

---

## 作者：_Anchor (赞：0)

# 题意

[传送门](https://www.luogu.com.cn/problem/P3554)

# 分析

容易发现答案$k$具有单调性，$k$越大越容易满足答案正确，$k$越小越有可能错误

那么我们考虑二分答案$k$，问题转化为判断一次染$k$个点是否可行

$tip1:$容易发现，$B$不会走回头路，因为如果走了在回去不就相当于白送$A$一次染色机会

考虑$dp$来检验：

设状态$dp[x]$表示$x$所以子树内（不包括$x$）需要多少次 **"额外"** 的染色

$tip2:$**"额外"** 的定义：因为我们走到子树中本身每一步都是在轮次中的，此时$A$也可以染色，这里指的是本身可以给予的染色机会不够了，必须 **"借用"** 其它地方的染色机会的点的个数

转移方程：

$$
\Large dp[x]=max(0,\sum_{y \in son[x]} +d[x]−mid)
$$

其中$d[x]$是指$x$的子树个数，$mid$是二分出来的那个答案$k$

那么$dp$完了过后，如果$dp[1]==0$，那么此时这个$mid$就是可行解，我们可以寻找更小的答案$（r=mid）$，否则我们只能往更劣处找$（l=mid）$

$tip3:$此时$dp[1]==0$的含义：整个树当中没有需要 **"额外"** 步数的结点，而$1$号结点作为根节点，不可能接受到其它地方的 **"帮助"**，所以必须要求这个点不能有额外的贡献

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
template <typename T>
inline void print(T x){write(x),putchar(' ');}
#define ll long long
#define ull unsigned long long
#define inc(x,y) (x+y>=MOD?x+y-MOD:x+y)
#define dec(x,y) (x-y<0?x-y+MOD:x-y)
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
const int N=3e5+5,M=1e6+5,MOD=1e9+7;
int n,mid;
int head[N],nex[M],to[M],idx;
int dp[N],d[N];
void add(int u,int v){
	nex[++idx]=head[u];
	to[idx]=v;
	head[u]=idx;
	return ;
}
void dfs(int x,int fa){
	dp[x]=0;int sum=0;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa) continue;
		dfs(y,x);
		sum+=dp[y]+1;
	}
	dp[x]=max(dp[x],sum-mid);
	return ;
}
int main(){
	read(n);
    if(n==1){
        puts("0");
        return 0;
    }
	int u,v;
	for(int i=1;i<n;i++){
		read(u,v);
		add(u,v);
		add(v,u);
	}
	int l=0,r=n;
	while(l+1<r){
		mid=(l+r)>>1;
		dfs(1,0);
		if(dp[1]==0) r=mid;
		else l=mid;
	}
	write(r);
	system("Pause");
	return 0;
}
```

---

## 作者：When (赞：0)

#### 题意补充

+ 事实上，$A$每次能染的$k$个节点并不一定与$B$所在节点相邻，换言之，$A$可以提前染一些节点使得$B$以后走不到。
+ 数据范围：$1 \leq n \leq 300000$

#### 算法

二分答案 + 树形DP

#### 思路

二分每次染的节点个数$k$，再用树形DP检查；

设$f_u$为以$u$节点为根的子树（不含$u$）全部染完**除了$k$以外**还需要的次数，那么：

$$ f_u = max(\sum{f_v} \; +siz_u - k, 0) $$

其中，$siz_u$为$u$的儿子数量。最后当$f_1 = 0$时即为合法。

注意要从儿子往父亲推，这样才能避免不知道先处理哪一个儿子的情况。

**为什么贪心是错的：**

考虑这种情况：有一个节点有大量儿子，而它的兄弟节点们只有一个儿子，显然，贪心是不好处理的。

#### 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 3e5 + 10;
int n,head[maxn << 1],num;
struct Edge{
    int then,to;
}e[maxn << 1];

void add(int u, int v){e[++num] = (Edge){head[u], v}; head[u] = num;}

int f[maxn];
void DFS(int u, int fa, int ch){
    int cnt = 0;
    for(int i = head[u]; i; i = e[i].then){
        int v = e[i].to;
        if(v != fa){
            cnt ++;
            DFS(v, u, ch);
            f[u] += f[v];
        }
    }
    f[u] = max(0, f[u] + cnt - ch);
}

int check(int p){
    memset(f,0,sizeof(f));
    DFS(1, 1, p);
    return (f[1] <= 0);
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; ++ i){
        int u,v; scanf("%d%d", &u, &v);
        add(u, v); add(v, u);
    }
    int l = 0, r = maxn;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", r + 1);
    return 0;
}
```

**福利数据**

```
7
1 2
1 3
2 5
2 6
7 2
4 1
ans:3
```







---

## 作者：Piwry (赞：0)

数据范围貌似是 $3\cdot 10^5$

## 解析

我们发现在第一次到达叶子结点前 B 一定不会走回头路，因为当 B 回到之前的某个结点时，A 下一次可以染色的结点数仍为 $k$，此时还多了一堆已经被染色的点

我们还发现，若 B 在到达叶子结点前无法获胜，则在这之后 B 也仍旧无法获胜，证明方法基本同上

若 B 在结点 $u$，可以想到这一步 A 一定要至少将 $u$ 的所有儿子节点（有边直接相连）染色；但染完色后可能还有多余的染色次数。由于 $k$ 是全局的，直接做最小值可能会非常困难，因此考虑二分 $k$ 仅检验

&nbsp;

可能有人会想到一种错误的贪心检验法：优先染色深度浅的结点。当游戏开始 $t$ 时刻后，A 一共有累积 $tk$ 次染色机会，B 最多只能走至深度为 $t$ 的结点，此时检验前 $t$ 层的结点是否能全部染色即可

这种贪心有一个比较简单的反例：

```
7
1 2
1 3
2 4
2 5
3 6
3 7
```

（其实就是一颗完全二叉树）

对于 $k=2$，贪心会认为不行，但实际上是可以的

非形式化的解释，可能是因为当 B 进入一颗子树时，就不需要考虑子树外的染色情况了

&nbsp;

于是考虑 dp，我们设 $dp(u)$，其含义为 B 从 $u$ 出发且只能往该子树内走，需要至少提前染该子树内多少个结点（且假设 $u$ 已染色）

至于转移，由于我们不清楚 B 究竟会往哪个儿子走，因此我们必须满足所有儿子的染色要求：

$dp(u)=\sum (dp(v)+1)-k$，其中 $v$ 是 $u$ 的儿子。$+1$ 是因为我们假设出发的这个结点已经染色

但注意 $dp(u)$ 有时**可能为负值**，这时我们应将其设为 $0$。这是因为其实际含义为：我们进入 $u$ 子树后甚至少染几次色也能满足要求；但这并不能实际给我们提供额外的染色次数

## CODE

注意答案可能为 $0$

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using std::min;
using std::max;

const int MAXN =3e5+50;

/*------------------------------Map------------------------------*/

int first[MAXN], tote;
struct edge{
	int net, to;
}e[MAXN<<1];

inline void addedge(int u, int v){
	++tote;
	e[tote].to =v, e[tote].net =first[u];
	first[u] =tote;
	++tote;
	e[tote].to =u, e[tote].net =first[v];
	first[v] =tote;
}

/*------------------------------Dfs------------------------------*/

int dp[MAXN];/*从 u 出发且只能往该子树内走，需要至少染多少个结点 ( 假设 u 已染色 )*/

void dfs(int u, int fa, int k){
	int sum =0;
	for(int l =first[u]; l; l =e[l].net)
		if(e[l].to != fa){
			dfs(e[l].to, u, k);
			sum +=dp[e[l].to]+1;
		}
	dp[u] =max(sum-k, 0);/*注意不能为负值*/
}

bool check(int k){
	memset(dp, 0, sizeof(dp));
	dfs(1, 0, k);
	return (dp[1] == 0);
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	int n =read();
	for(int i =0; i < n-1; ++i){
		int u =read(), v =read();
		addedge(u, v);
	}
	int l =0, r =n, ans =n;
	while(l <= r){
		int mid =(l+r)>>1;
		if(check(mid))
			ans =min(ans, mid), r =mid-1;
		else
			l =mid+1;
	}
	printf("%d", ans);
}
```

---

## 作者：xcxc82 (赞：0)

# P3554 [POI2013]LUK-Triumphal arch 题解


## [间隙](https://www.luogu.com.cn/problem/P3554)

## 知识点
 - ## 树形$DP$ , 二分答案

## 分析

题意翻译里已经写的很清楚了,这里就不重复一遍了

首先这里的答案$k$具有可二分性,考虑二分答案

当$B$走到一个节点$u$时,第一步要做的肯定是把$u$的儿子全部都涂色

如果一个节点的儿子数大于当前的$k$,则无论怎么涂都会输

反之,说明除了涂自己的儿子外还可以"**提前**"涂其他的节点

设$f[i]$为以$i$根节点的子树需要**其祖先"提前"染色多少个点才能覆盖整个子树**

易得状态转移方程:$f[u] = max(0  , \sum f[v]+1-k)$

具体解释$:$

![](https://cdn.luogu.com.cn/upload/image_hosting/i6tgjcmc.png)

## 代码实现

直接二分答案$k$,对于每一个$k$进行$dp$

如果$f[1]$为$0$,则说明可行

反之说明不可行


```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+10;
int n;
struct e{
	int to,next;
}edge[MAXN<<1];
int head[MAXN<<1],cnt = 0;
int f[MAXN];
void add(int u,int v){//前向星
	edge[++cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}
void dfs(int u,int fa,int k){
	int sum = 0;
	for(int i=head[u];i;i=edge[i].next){
		int v = edge[i].to;
		if(v==fa) continue;
		dfs(v,u,k);
		sum=sum+f[v]+1;//记录
	}
	f[u] = max(0,sum-k);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	int l = 0,r = 10e10;
	int ans = -1;
	while(l<=r){//二分答案
		memset(f,0,sizeof(f));
		int mid = (l+r)>>1;
		dfs(1,0,mid);//dp
		if(f[1]==0){//如果f[1]为0 说明可行
			ans = mid;
			r = mid-1;
		}反之,不可行
		else l = mid+1;
	}
	printf("%d",ans);
}
```



---

## 作者：cirnovsky (赞：0)

## 题意简述

见题意翻译。

## 题解

没有什么好的方法求 $k$ 的值，我们考虑二分。

这个二分的单调性是显然的，考虑怎么判断。

可以通过树形DP的方式来判断。

设 $F_{i}$ 为以 $i$ 为根节点的子树最少还需多染几个节点可以使得A获胜。

那么容易得出转移方程：

$$
F_{u}=\max\{\sum_{v\in son(u)}(F_{v}+1)-k\}
$$

其中 $k$ 为当前的二分值。

可知只要 $F_{1}=0$ 就是一个可行方案。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int Maxn = 3e5 + 5;
int n, dp[Maxn];
vector < int > G[Maxn];

void dfs(int x, int fa, int k)
{
	dp[x] = 0;
	for (unsigned i = 0; i < G[x].size(); ++i)
	{
		int y = G[x][i];
		if (y == fa)	continue;
		dfs(y, x, k);
		dp[x] += dp[y] + 1;
	}
	dp[x] = max(dp[x] - k, 0);
}

bool Check_Feasic(int x)
{
	dfs(1, 0, x);
	if (dp[1] == 0) 	return 1;
	else 	return 0;
}

int Binary_Search(int l, int r)
{
	int ans = l;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (Check_Feasic(mid))	ans = mid, r = mid - 1;
		else	l = mid + 1;
	}
	return ans;
}

signed main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	printf("%d\n", Binary_Search(0, n));
	return 0;
}
```

---

