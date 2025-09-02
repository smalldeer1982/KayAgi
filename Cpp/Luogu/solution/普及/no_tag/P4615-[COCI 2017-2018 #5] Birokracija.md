# [COCI 2017/2018 #5] Birokracija

## 题目描述

Mirko是一家大公司的CEO。该公司由$N$人组成，编号为1到N，Mirko编号为$1$。公司的结构像一棵树一样，每个员工（Mirko除外）都有老板，我们说这个员工是该老板的助手。每个老板都可以有多名助手。Mirko没有老板，但有他的助手。

之后会有一些任务，Mirko会将该任务委托给他编号最小的助手。然后，该助手也将任务委托给他编号最小的助手，并且这个过程重复进行，直到任务被发送给没有助手的人，然后他必须亲自完成任务。

执行任务的人获得1个硬币，那个人的老板获得2个硬币，那个人的老板获得3个硬币，依此类推，一直到Mirko。之后，真正完成工作的员工意识到系统的不公平并感到伤心，并且不会再执行任务（也就是辞职）。

当公司收到的下一个任务时，因为少了一个人，所以薪水可能更少，但工作必须继续。任务是无限多的（直到公司倒闭），因此整个过程（分配新任务，执行任务，划分薪水和执行任务人员的退出）重复进行，最后Mirko独自留在公司并完成他的第一个（也是他的最后一个）任务。

当然，在此之前，Mirko将积累相当多的财富，但他也想知道每个员工赚了多少钱。

## 样例 #1

### 输入

```
3
1 1```

### 输出

```
5 1 1```

## 样例 #2

### 输入

```
5
1 2 2 4```

### 输出

```
13 8 1 3 1```

# 题解

## 作者：momentous (赞：10)

这道题的恶心内存与恶心数据导致存图 **~~只~~** 不只能用**链式前向星**(个人不常用STL),于是......

### 永远喜欢链式前向星!!!

## Code:
```
#include<cstdio>
#define reg register
#define ll long long
using namespace std;
inline int Read(){//快读,优化时间
    reg int x=0,f=1;reg char ch=getchar();
    while((ch<'0' || ch>'9') && ch!='-') ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    while(ch>='0' && ch<='9'){
        x=(x<<3)+(x<<1)+(ch&15);
        ch=getchar();
    }
    return x*f;
}
inline void Print(const ll x){//快输,也是优化时间
    if(x<0){putchar('-');Print(-x);}
    if(x<10) putchar(x+48);
    else{Print(x/10);putchar(x%10+48);}
}
inline void Println(const ll x){Print(x);putchar('\n');}
ll b[200105],c[200105];
int n,head[200105],top;//上司关系不会超过人数,所以可以用int
struct p{
    int to,nxt;
}e[200105];//链式前向星存图
inline void dfs(const int Number){
    b[Number]=1;
    for(reg int i=head[Number];i;i=e[i].nxt){
        reg int some=e[i].to;
        dfs(some);//统计他的助手
        c[Number]+=c[some];
        b[Number]+=b[some];
    }
    c[Number]+=b[Number];
}
inline void add(int u,int v){//链式前向星建边
    e[++top].to=v;
    e[top].nxt=head[u];
    head[u]=top;
}
int main(){
    n=Read();
    for(reg int i=2;i<=n;++i){
    	reg int x=Read();
        add(x,i);
    }
    dfs(1);//慢慢统计吧......
    for(reg int i=1;i<=n;++i){
        Print(c[i]);putchar(' ');
    }
    putchar('\n');
    return 0;
}
```

链式前向星是解决图论问题的利器,大家一定要学会哦

---

## 作者：B天选之子B (赞：7)

## 题目描述如下

每个人都会做一次任务,做完任务就会离开。

做任务的人会得到一个硬币。上司得到两个，上司的上司得到三个，以此类推直到上司就是自己的人结束。

最后求的就是每个人的硬币总和。

## 解题思路
**因为做一次任务，上司得到的钱比下属多一个硬币，所以总结到了一下三点。**

- 每个人的硬币数量等于所有下属的钱的和加上能够得到钱的份数的数量。

- 每个人钱的份数的数量等于所有下属的钱的份数的数量的和加一。

- 做任务的人可以得到一份钱。

**最后解题方法就是用深搜求下属钱的份数和下属总共得的钱**

## 注意事项

-  记得不要忘了加一的。

-  此题用并查集的注意不要合并每个点。

-  如果公司成一字链，那么最多的钱就得用 ```long long```  才可以存下。

## 奉上代码
```
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL ans[200100],gs[200100];//ans存每个人的钱 gs存每个人能得到的钱的份数
int N,per[200100],SS;//per存每个人的上司
int main() {
    scanf("%d",&N);
    for(int i=1; i<=N; i++) per[i]=i;
    for(int i=2; i<=N; i++) {
        scanf("%d",&SS);
        per[i]=SS;
    }
    for(int i=N; i>1; i--) {  //题目中说ai<i，所以大胆从后往前枚举
        ans[i]=1;
        gs[i]++;              //每个人都会做一次任务，所以至少有一份钱
        gs[per[i]]+=gs[i];    //上司钱的份数等于每个下属的份数之和加一
    }
    for(int i=N; i>1; i--) {  //算出每个人的钱数
        ans[i]=ans[i]+gs[i]-1;
        ans[per[i]]+=ans[i];
    }
    ans[1]=ans[1]+gs[1]+1;
    for(int i=1; i<=N; i++)
        printf("%lld ",ans[i]);
    return 0;
}
```

---

## 作者：烛木 (赞：6)

这题难点在怎么处理父亲结点与其子结点的关系

由题目描述可以得知：**每一个人的金币数是其各个儿子的金币数还有以其为根的子树的结点数的和**

解释：

1.儿子金币和：由于每做一次任务就会有一个结点被删除，，因此**每一次操作这条链上的点到最底端距离都减1**，因此一个儿子会加上的金币数一个父亲也会加一遍。

2.以其为根的子树结点和：由题意可知每一次任务父亲所获得金币数与其编号最小的儿子获得的金币数差为1,而有多少个这样的1呢？ 就是**以其为根的子树的大小**，所以每一次前向星完就要加上这个树的大小。

code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
#define int long long
#define MAXN 5000086
int n,tot,ans[MAXN],size[MAXN];
struct node
{
	int first,next,go;
}p[MAXN];
inline void star(int a,int b)
{
	p[++tot].next=p[a].first;
	p[a].first=tot;
	p[tot].go=b;
}
inline void dfs(int x)
{
	ans[x]=0,size[x]=1;
	for(int i=p[x].first;i;i=p[i].next)
	{	
		int y=p[i].go;
		dfs(y);
		size[x]+=size[y];
		ans[x]+=ans[y];
	}
	ans[x]+=size[x];
}
signed main()
{
	scanf("%lld",&n);
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%lld",&x);
		star(x,i);
	}
	dfs(1);
	for(int i=1;i<=n;i++) printf("%lld ",ans[i]);
	return 0;
}
```


---

## 作者：Register (赞：4)

### 题意描述
有一个$n$人的公司，呈树形结构，父亲表示结点上司，儿子结点表示下属

有一个任务，每次会从$CEO$（即$1$号根结点）出发，有下属的派给编号最小的下属，没有的则自己执行

每次亲自执行任务的得到$1$枚硬币，他的上司得到$2$枚，他上司的上司得到$3$枚，以此类推

不过每次亲自执行任务的人会意识到公司的不公，马上离开公司

最后所有人都离开公司后，求每个人各获得多少硬币
### 解题思路
-  一棵子树是否有人离开，并不会影响另一棵子树的硬币价格，因此编号并不需要考虑最小

- 每一个人都会离开公司，因此一棵子树的执行任务者，即叶结点就是这棵子树的结点数

- 一个结点的硬币数是它所有儿子的硬币加上任务数（包括自己的）（所有任务汇上来，原先的加上$1$的差距）

> **那么，我们就得到了最重要的式子：**

$$ans_u=size_u+\sum{ans_v}$$
### 注意事项
- 记得开```long long```，比如一条链的情况，$CEO$就会得到$\frac{n\times(n-1)}{2}$枚硬币，而$n$最大是$200000$

- 最后$CEO$自己也会执行一次任务，不要忽略

### 代码

```cpp
#include <cstdio>
#include <vector>
#define int long long
using namespace std;
int n,ans[200001],sz[200001];
vector<int> e[200001];
int read(){
    char ch=getchar();int res=0,w=1;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
    return res*w;
}
void dfs(int x){
	sz[x]=ans[x]=1;
	for(register int i=0;i<e[x].size();i++) {dfs(e[x][i]);ans[x]+=ans[e[x][i]]+sz[e[x][i]];sz[x]+=sz[e[x][i]];}
}
signed main(){
	n=read();
	for(register int i=1;i<n;i++) e[read()].push_back(i+1);
	dfs(1);
	for(register int i=1;i<=n;i++) printf("%lld ",ans[i]);
	puts("");
    return 0;
}
```


---

## 作者：Lazy_Labs (赞：3)

## 题目大意

有一个 $n$ 人的公司，呈树形结构，父亲表示结点上司，儿子结点表示下属。

有一个任务，每次会从 $CEO$ （即 $1$ 号根结点）出发，有下属的派给编号最小的下属，没有的则自己执行。

每次亲自执行任务的得到 $1$ 枚硬币，他的上司得到 $2$ 枚，他上司的上司得到 $3$ 枚，以此类推。

不过每次亲自执行任务的人会意识到公司的不公，马上离开公司。

最后所有人都离开公司后，求每个人各获得多少硬币。

[参考](https://www.luogu.com.cn/blog/shrshrshr/solution-p4615)
## 分析
有一棵树（如下图所示，按照题目样例2，用红色数字表示收到的硬币数）

![first题解1](https://ftp.bmp.ovh/imgs/2021/06/e028c66f09a1a46b.png)

易知，每个节点获得的硬币数就是**所有**子节点的 $($ 硬币数量 $+$ 加数个数 $)+1$。

如节点 $2$ 获得的硬币数量就是 $(4$ 的硬币数量 $+4$ 的加数个数 $)+(3$ 的硬币数量 $+3$ 的加数个数 $)=(3+2)+(2+1)=5+3=8$ 与题目描写的相同。

又因为我们可以知道节点 $i$ 的加数个数等于以节点 $i$ 为根的树的节点个数，令它为 $Size_i$ ，且令这个节点获得的硬币数量为 $Coin_i$ 。

所以我们得到一个好公式：

$Coin_n=(\sum\limits_{x=Son(n)}{Coin_x})+Size_i$

而 $Size_n=(\sum\limits_{x=Son(n)}{Size_x})+1$

于是我们可以考虑从子节点向根节点进行树形DP。

这时我们就可以考虑进行DFS扫一遍来确定 $Size$ 和 $Coin$ 。

## DFS

DFS我就不讲了，不会的自行看其他题解 。

## 做法
注意到题目中**输入输出格式中**有提到 $1\le a_i< i$ 所以我们的从**子节点到根节点**就可以直接从 $n$ 更新$Coin$ 和 $Size$ 到 $1$。

DP过程如下：(`size`即 $Size$ ,`f`即 $Coin$ ,`fa`即储存父节点编号。)

```cpp
for(int i=n;i>=1;i--)
{
	size[i]++;
	size[fa[i]]+=size[i];
	f[i]+=size[i];
	f[fa[i]]+=f[i];
}
```
于是我们就可以愉快的A了这道题了！
## 代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define ll long long
const int MAXN=2e5+10;
inline int read()
{
 	int x(0),f(1);char c=getchar();
    while(c>'9'||c<'0')f=c=='-'?-1:1,c=getchar();
    while(c>='0'&&c<='9')x=x*10+c-48,c=getchar();
    return f*x;
}
int fa[MAXN];
ll f[MAXN];
ll size[MAXN]; 
int main()
{
	int n=read();
	for(int i=2;i<=n;i++)
	fa[i]=read();
	for(int i=n;i>=1;i--)
	{
		size[i]++;
		size[fa[i]]+=size[i];
		f[i]+=size[i];
		f[fa[i]]+=f[i];
	}
	for(int i=1;i<=n;i++)
	printf("%lld ",f[i]);
	return 0;
} 
```


![改成.rar](https://ftp.bmp.ovh/imgs/2021/06/26eb38e6f0e29dd7.jpg)

本蒟蒻第一次写题解，有问题请在博客中提问QWQ。

---

## 作者：WZKQWQ (赞：1)

### 我爱 STL，即使它慢

典型树上 DP。

思维难度比较大。

这题我们可以知道每一个人都至少自己做一次工作，

这次工作获得的金币为 1。

所以 $f[x] = 1$。

一个人的老板肯定比这个人收入多。

对于每次工作一个人的老板一定收入比助手多 1。

而一个人能参与的工作的次数，

就是他的助手数（包括助手的助手）。

我们令 $se[x]$ 表示x的助手数（包括助手的助手）。

那么 $f[x] += f[y] + se[y]$。

这样做时间空间复杂度都是 $O(n)$。

编程复杂度极低。

最后 AC 代码（30 行搞定）：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
#define int long long
vector <int> a[N];
int n,se[N],f[N];
void build(int x){
    se[x] = 1;
    for(int i = 0;i < a[x].size();i++){
        build(a[x][i]);
        se[x] += se[a[x][i]];
    }
}
void dfs(int x){
    f[x] = 1;
    for(int i = 0;i < a[x].size();i++){
        dfs(a[x][i]);
        f[x] += f[a[x][i]] + se[a[x][i]];
    }
}
signed main(){
    scanf("%lld",&n);
    for(int i = 2,o;i <= n;i++){
        scanf("%lld",&o); 
        a[o].push_back(i);
    }
    build(1),dfs(1);
    for(int i = 1;i <= n;i++) printf("%lld ",f[i]);
    return 0;
}
```




---

## 作者：亦笙箫 (赞：1)

这道题其实非常简单.  
把题目中的关系简化为一棵树,领导为父亲,下属为儿子,这样就可以清楚的得到.  
一个节点的答案(能获得的钱数),就是我们的答案了.  
而且每个不同子树中的节点不会互相影响,  
所以每个节点的答案就是它的所有儿子的答案之和再加上它的儿子个数,即可得出答案.  
## $Code$

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

#define ll long long
#define Pll pair<long long,long long>

const int MAXX = 2*1e5;

int n;

ll dis[MAXX+5];

vector<ll> g[MAXX+5];

Pll dfs(ll x)
{
	Pll a={0,0},b={1,1};
	for(int i=0;i<(int)g[x].size();i++)
	{
		a=dfs(g[x][i]);
		b.first+=a.first+a.second;
		b.second+=a.second;
	}
	dis[x]=b.first;
	return b;
}

int main()
{
//	freopen("birokracija.in","r",stdin);
//	freopen("birokracija.out","w",stdout);
	scanf("%d",&n);
	for(int i=2,x;i<=n;i++)
		scanf("%d",&x),
		g[x].push_back(i);
	dfs(1);
	for(int i=1;i<=n;i++)
		printf("%lld ",dis[i]);
	return 0;
}
```


---

## 作者：RainFestival (赞：1)

这道题题解太少了，我来发一篇吧

首先，我们可以总结出一个规律

设ci为第i个员工的总收入

bi为第i个员工的总任务（包括Ta的下属）

我们可以发现：

ci=Ta的所有下属的收入+Ta的所有下属的任务数+1

bi=Ta的所有下属的任务数+1

题目中要求编号的问题，其实不成问题

下面是代码：

```cpp
#include<cstdio>
long long c[200005],b[200005],l[200005];
int a[200005][55];
int n;
void dfs(int v)
{
    if (l[v]==0) return;
    for (int i=1;i<=l[v];i++)
        dfs(a[v][i]);
    for (int i=1;i<=l[v];i++)
    {
        c[v]=c[v]+c[a[v][i]]+b[a[v][i]];
        b[v]=b[v]+b[a[v][i]];
    }
        
}
int main()
{
    scanf("%d",&n);
    for (int i=2;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        l[x]++;
        a[x][l[x]]=i;
    }
    for (int i=1;i<=n;i++)
        b[i]=c[i]=1;
    dfs(1);
    for (int i=1;i<=n;i++)
        printf("%lld ",c[i]);
    printf("\n");
    return 0;
}
```

用时1118ms,内存57148kb,代码长度0.5kb

谢谢大佬们的观赏

---

## 作者：ysy666 (赞：1)

好久没写题解了，这里来一发

题目中说这是一棵树，所以我们可以用dfs来解决

自己画个图玩一下，不难发现子节点与父节点的关系：每个儿子结点对父节点的贡献就是自身的答案加上自己的sum值（具体看代码注释）

放代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#define N 200010
#define LL long long
using namespace std;
int n;
vector<int> e[N];//vector存图简单粗暴,数据小不用担心超时 
LL ans[N],sum[N];//ans是答案,sum记录该节点贡献了几枚硬币 
inline int read()
{
	int x,t=1;
	char c;
	while(c=getchar(),c<'0' || c>'9')  if(c=='-')  t=-1;
	x=c-'0';
	while(c=getchar(),c>='0' && c<='9')  x=x*10+c-'0';
	return x*t;
}
inline void dfs(int x)
{
	sum[x]=1; 
	for(register int i=e[x].size()-1;i>=0;i--)
	{
		int to=e[x][i];
		dfs(to);
		ans[x]+=ans[to],sum[x]+=sum[to];
	}
	ans[x]+=sum[x];//每个儿子结点对父节点的贡献就是自身的答案加上自己的sum值
}
int main()
{
	n=read();
	for(register int i=2;i<=n;i++)
	{
		int x=read();
		e[x].push_back(i);
	}
	dfs(1);//从根节点开始 
	for(register int i=1;i<=n;i++)  printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：Foreverxxx (赞：0)

由题意可以看出领导的下属是按照从小到大的顺序输入的，
那么我们只需要从老板开始深度优先搜索一次就可以了，并不需要排序！！！

为了做题简便，可以选择直接开 vector 记录领导的下属。 （本人感觉很方便）

由题意可以推出，每一个人的金币数是其所有下属的金币数还有以其为根的子树的结点数的和。
那么一个简单的树规代码就出来了。

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,xx,tot=0;
long long coin[200004],s[200004];
vector<int> son[200004];
inline int read(){
    int sss=0,www=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-')www=-1;
		ch=getchar();
	}
    while(ch>='0'&&ch<='9') sss=sss*10+ch-'0',ch=getchar();
    return sss*www;
}
void dfs(int x){
	s[x]=1;
	coin[x]=1;
	for(int i=0;i<son[x].size();i++){
		dfs(son[x][i]);
		coin[x]+=coin[son[x][i]]+s[son[x][i]];
		s[x]+=s[son[x][i]];
	}
}
int main(){
	n=read();
	for(int i=2;i<=n;i++){
		xx=read();
		son[xx].push_back(i);
	}
	dfs(1);
	for(int i=1;i<=n;i++)cout<<coin[i]<<" ";
	return 0;
}
```

---

## 作者：XL4453 (赞：0)


------------
解题思路：

首先可以知道两个不同子树是互相不干涉的，每一个节点的值只和其子树有关，由此想到树形DP。

然后可以发现每一个节点都会把所有子树做过的任务价值的总和，然后再在每一个任务的基础上加一，也就相当于最终加上子节点数量之和，意味着每有一个节点就会做一次任务。

所以DP时记录下子树总价值和子树大小即可。

所以方程为 $F_i=size_i+\sum F_{son_i}$

------------
```
#include<cstdio>
using namespace std;
const int MAXN=200005;
long long head[MAXN],next[MAXN*2],num[MAXN*2],n,x,tot,f[MAXN],size[MAXN];
void add(int x,int y){
	next[++tot]=head[x];head[x]=tot;num[tot]=y;
}
void dfs(int now,int fa){
	for(int i=head[now];i;i=next[i])
	if(num[i]!=fa){
		dfs(num[i],now);
		f[now]+=f[num[i]];
		size[now]+=size[num[i]];
	}
	size[now]++;
	f[now]+=size[now];
}
int main(){
	scanf("%lld",&n);
	for(int i=2;i<=n;i++){
		scanf("%lld",&x);
		add(i,x);add(x,i);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){
		printf("%lld ",f[i]);
	}
	return 0;
}
```


---

## 作者：SmallTownKid (赞：0)

简单树形dp题 遇到这种题根据经验一般先预处理出每个节点的深度信息和子树大小。

然后分析一波，~~瞎搞出状态转移方程~~。

对于一个点 $now$ 获得的金币数 $f[now]=f[v]+size[v]+1$

因为金币数是从下往上一个一个加的， $v$ 点的深度比 $now$ 小 $1$ ，所以它的子树的每一个点都多贡献一个金币，$+1$ 是因为它自己也会工作。

可以直接在初始化里把 $f$ 数组赋成 $1$ ，这样在转移方程里就不用 $+1$ 了。
``` 
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n;
struct node{
	int nxt,to;
}edge[400010];
int size[400010],head[400010];
long long f[400010];
int idx;
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
void dfs(int now,int fath)
{
	f[now]=1;
	size[now]=1;
	for(int i=head[now];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(v==fath)
		continue;
		dfs(v,now);
		size[now]+=size[v];
		f[now]+=f[v]+size[v];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		int v;
		scanf("%d",&v);
		add(i,v);
		add(v,i);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		printf("%lld ",f[i]);
	}
	return 0;
}

---

## 作者：Phykyer (赞：0)

观察题意：本题给出了一棵树，每个节点从自己开始往上跳至根，对于至根路径上的每一个点贡献从一开始增值为 $1$ 的贡献最后要求输出每个点获得的贡献。  

每个点只会贡献一次，数据范围又达到了 $2e5$ ，直接一眼树形 $dp$ 。  

然后开始考虑如何转移，思考之后我们可以发现这样一个性质：即对于一个点 $x$ ，和它的一个子节点 $y$ ， $x$ 从 $y$ 及其子树中获得贡献为 $y$ 的贡献加上 $y$ 的子树大小。因为 $x$ 的深度比 $y$ 第一层，所以 $y$ 及其子树内的所有点向它们的父亲做贡献时，给到 $x$ 的贡献肯定比给到 $y$ 的多一。  

由这条性质就可以得出非常显然的转移方程了：  
$f[x] = f[y] + size[y] + 1$  
$f[i]$ 表示 $i$ 获得的总贡献（钱）， $size[i]$ 为 $i$ 的子树大小，这里 $+ 1$ 是因为自己也要做一次任务。  
对于这个方程，在树上跑一遍 $dfs$ 即可统计出全部答案，细节看代码  

以下为代码部分  

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int N = 200010;

int n;
int head[N], ver[N], Next[N], cnt;
ll f[N], size[N];

inline void add(int x, int y) {
	ver[++cnt] = y; Next[cnt] = head[x]; head[x] = cnt;
}

inline void dfs(int x) {
	f[x] = 1;
	size[x] = 1;
	// size，f均需初始化为 1（自己要做一次任务）
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i];
		dfs(y);
		size[x] += size[y];
		f[x] += f[y] + size[y];
		// 累加答案
	}
}

inline int read() {
	int x = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int main() {
	n = read();
	int x;
	for (int i = 2; i <= n; i++) x = read(), add(x, i);
	// 给出了父子关系保存单向边即可
	dfs(1);
	for (int i = 1; i <= n; i++) printf("%lld ", f[i]);
	return 0;
}
```


---

