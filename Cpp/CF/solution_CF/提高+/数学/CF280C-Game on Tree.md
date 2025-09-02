# Game on Tree

## 题目描述

给定一棵有根树，结点编号从 $1$ 到 $n$。根结点为 $1$ 号结点。

对于每一次操作，等概率的选择一个**尚未被删去**的结点并将它及其子树全部删去。当所有结点被删除之后，游戏结束；也就是说，删除 $1$ 号结点后游戏即结束。

要求求出删除所有结点的期望操作次数。

## 说明/提示

### 样例解释

在第一个样例中，有两种情况：

一种是直接删除根（即 $1$ 号结点），另一种是先删去 $2$ 号结点，再删除 $1$ 号结点。

操作次数的期望是 $1\times \dfrac12+2\times\dfrac12=1.5$。

在第二个样例中，情况更为复杂。其中有两种情况会将问题转化成第一个样例，而剩下的一种情况会一次全部删除。

操作次数的期望是 $1\times\dfrac13+(1+1.5)\times\dfrac23=\dfrac13+\dfrac53=2$。
### 数据范围
$1\le n\le 10^5,1\le a_i,b_i\le n,a_i\neq b_i$

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
1.50000000000000000000
```

## 样例 #2

### 输入

```
3
1 2
1 3
```

### 输出

```
2.00000000000000000000
```

# 题解

## 作者：逃离地球 (赞：92)

**[题目链接](https://www.luogu.com.cn/problem/CF280C)**

这题感觉其他的题解写的都不是很清楚（也可能是因为我太弱），导致我并没有看懂。我于是请教了 THU 学长 [Mr_Wu](https://www.luogu.com.cn/user/62308)，然后他用了 $1^{-10}$ 秒就切了这道题，并且教会了我。

### 简单题意

给出一棵树，每次随机等概率选择一未染黑的点，将它及其子树染黑。问期望多少次操作可以将树全部染黑。

### 题解

设 $f_i$ 表示 $i$ 号点表示点 $i$ 被选中的次数（显然只可能是 0 或 1）。

则要求的答案就是 $E[\sum f_i]$，即 $f_i$ 的和的期望，

由期望的可加性，有 $E[\sum f_i]=\sum E[f_i]$。

由于 $f_i$ 的取值只能是 0 或 1，则 $f_i$ 的期望就等于 $f_i$ 等于 1 的概率，设为 $p_i$.

则答案为 $\sum p_i$，即每个球被选中的概率的和。
考虑随机生成一个操作序列，找到序列中第一个未被染色的节点，并染色这个节点和它的子树中的所有节点，重复这个操作，直到序列中所有节点都被染色。

那么 $i$ 号节点被选中的前提就是在序列中，$i$ 号节点的祖先都在 $i$ 号节点的后面。否则，就会在选择 $i$ 号节点之前选择它的祖先，并且 $i$ 节点就会被染色，而不会被选中。

由于 $i$ 号节点共有 $dep_i-1$ 个祖先，故 $i$ 号节点在这个随机序列中排在所有祖先前面的概率是 $\dfrac 1 {dep[i]}$，故 $i$ 号球被选中的概率是 $\dfrac 1 {dep[i]}$.

故答案为 $\sum\dfrac 1 {dep[i]}$.

代码是个人都会写，就不放了。



---

## 作者：messuarez (赞：24)

不知道是不是有人和我一样不理解为什么每个点对答案的贡献是1/（dep+1）  
所以我给一个严谨的想法（网上看的）  
原问题等价于：  
我们随机生成一个1～n的排列，  
然后从左到右枚举点，如果没有被染黑就把它染黑，次数+1  
则答案即为次数的期望（易证）  
根据期望的线性性：总次数的期望=每个点被染黑次数的期望的和  
由于每个点只会被染黑一次，所以求出每个点被染黑的概率即可  
一个点被染黑当且仅当它的祖先结点都排在它的后面  
设这个点祖先结点个数为dep（不包括本身），概率即为：1/（dep+1）


---

## 作者：tommymio (赞：20)

引入《算法导论》中的指示器随机变量确实非常好用，几乎可以以模板化的方式解决一类问题。

### 约定

$Pr\{X\}$ 为事件 $X$ 发生的概率。

$E[X]$ 为 $X$ 的期望值。

$I\{X\}$ 为事件 $X$ 的指示器随机变量。当事件 $X$ 发生时，$I\{X\}$ 的值为 $1$，当事件 $X$ 不发生时，值为 $0$。

### 分析

设 $X_i$ 为事件 $T$ 的指示器随机变量，其中事件 $T$ 为节点 $i$ 被选中。那么总共选出的节点数为 $X=\sum\limits_{i=1}^n X_i$。对等式两边同时期望，得到 $E[X]=E\left[\sum\limits_{i=1}^n X_i\right]$。根据期望的线性性质 $E[Y+Z]=E[Y]+E[Z]$，可以得到 $E[X]=\sum\limits_{i=1}^nE[X_i]$。

又因为 $E[X_i]$ 的值非 $0$ 即 $1$，根据期望的定义式，可以得到 $\forall i,E[X_i]=Pr\{T\}\times 1+Pr\{\bar{T}\}\times 0=Pr\{T\}$，即 $E[X_i]$ 的值为节点 $i$ 被选中的概率。

本题中，只要解决了节点 $i$ 被选中的概率，问题便迎刃而解。观察题目可以发现，如果节点 $i$ 的祖先被选中了，节点 $i$ 便不可能再被选中，也就是说，节点 $i$ 一定要先于它的祖先被选中。那么，节点 $i$ 被选中的概率就为 $\frac{1}{dep_i}$，总共期望选出的节点数即为 $\sum\limits_{i=1}^n\frac{1}{dep_i}$。

### 总结

这类题目，使用指示器随机变量求解就是三部曲：

- 设事件 $T$ 的指示器随机变量。

- 利用指示器随机变量和期望的线性性质分化问题。

- 求解事件 $T$ 发生的概率。

使用指示器随机变量可以让我们迅速看清问题的本质。

关于指示器随机变量的更多应用和介绍可以看另一篇题解（[戳这里](https://www.luogu.com.cn/blog/infinity-dimension/solution-uva12004)），有时间的话我可能会整理出指示器随机变量的各种应用（

### 代码

```cpp
#include<cstdio>
double ans=0.00;
int cnt=0;
int h[100005],to[200005],ver[200005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void dfs(int x,int dep,int fa) {
    ans+=1.00/dep;
    for(register int i=h[x],y;i;i=ver[i]) {if((y=to[i])==fa) continue; dfs(y,dep+1,x);}
}
int main() {
    int n=read();
    for(register int i=1,x,y;i<n;++i) {x=read();y=read();add(x,y);add(y,x);}
    dfs(1,1,-1); printf("%.6lf\n",ans);
    return 0;
}
```

---

## 作者：aiyougege (赞：17)

#### Solution
　　因为每个点都必须被删掉, 所以需要考虑一个点被删掉对答案的贡献. 假设点删掉点i, 它的深度为$\text{depth}_i$.

　　它被删掉可能是因为$\text{depth}_i$种方式,_
  - 点 i 的老祖先(根节点)被删掉
  - 点 i 的次老祖先(根的儿子)被删掉
  - ......
  - 点 i 的父亲节点被删掉
  
　　因此一个点被删掉会对答案产生$\frac{1}{\text{depth}_i}$的贡献（删除一个点的代价为 1 , 乘以概率）.

　　根据期望的线性性, 简单来说就是$E(x+y)=E(x)+E(y),E(ax)=aE(x),a\in \mathbb R$, 其中$E(x)$表示期望. 这个性质是没有条件的, 无论事件是否独立都成立.

　　所以总次数期望为各点期望之和, 即答案为$$\sum_{i=1}^n\frac{1}{\text{depth}_i}$$

#### Code
```c++
#include<cstdio>
#define N 500005
using namespace std;

struct Edge{
    int v,nxt;
}e[N];
int head[N],tot;
int dep[N];
void AddEdge(int u,int v){
    e[++tot]={v,head[u]};head[u]=tot;
    e[++tot]={u,head[v]};head[v]=tot;
}
void dfs(int x,int f){
    dep[x]=dep[f]+1;
    for(int i=head[x];i;i=e[i].nxt){
        if(e[i].v==f)continue;
        dfs(e[i].v,x);
    }
}
int main(){
    int n,a,b;
    scanf("%d",&n);
    for(int i=1;i<n;++i){
        scanf("%d%d",&a,&b);
        AddEdge(a,b);
    }
    dep[1]=1;
    dfs(1,0);
    double ans=0.0;
    for(int i=1;i<=n;++i)
        ans+=1.0/dep[i];
    printf("%.7f",ans);
    return 0;
}
```

 


---

## 作者：木xx木大 (赞：7)

[CF280C Game on Tree](https://www.luogu.com.cn/problem/CF280C)

根据期望的线性性，我们可以把每个点的贡献拆开算。设 $f_i$ 表示 $i$ 号点被选中的次数，显然 $f_i$ 只可能为0或1。设 $p_i$ 表示 $f_i=1$ 的概率，那么 $f_i$ 的期望= $p_i$ 。$ans=\sum f_i=\sum p_i$ 。

由题，一个点被选中后，它子树内的所有点都不可能再被选中。那么一个点被选中，当且仅当它的祖先都在它之后被选。那么$p_i$= **$i$ 在 $i$ 的所有祖先之前被选的概率**。设 $dep_i$ 表示1到 $i$ 的路径上点的个数（包括 $i$ 自己），那么在这 $dep_i$ 个点中， $i$ 第一个被选的概率即为 $\frac 1{dep_i}$ （考虑一个长为 $dep$ 的排列，$i$ 在第一个位置有 $(dep_i-1)!$ 种情况， 在第一个位置的概率即为 $\frac{(dep_i-1)!}{dep_i!}=\frac 1{dep_i}$ ）。$ans= \sum p_i=\sum \frac 1{dep_i}$ 

感觉这题难度全点在思维上了，代码极其好写

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace FGF
{
	int n,m;
	const int N=1e5+5;
	struct edg{
		int to,nxt;
	}e[N<<1];
	int cnt,head[N];
	double ans;
	void add(int u,int v)
	{
		cnt++;
		e[cnt].to=v;
		e[cnt].nxt=head[u];
		head[u]=cnt;
	}
	void dfs(int u,int f,double dep)
	{
		ans+=1.0/dep;
		for(int i=head[u];i;i=e[i].nxt)
			if(e[i].to!=f)dfs(e[i].to,u,dep+1);
	}
	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v),add(v,u);
		}
		dfs(1,0,1);
		printf("%.8f",ans);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

## 作者：SimonSu (赞：4)


在写题解之前我们先介绍一下期望是个啥

#### 期望是什么？

如果X是一个离散的随机变量，输出值为x1,x2,...，xk 和输出值相应的概率为p1,p2,...pk（概率和为 1）, 那么期望值：

####  E(x)=∑ p[i] * x[i] (i<=k)



------------


#### 期望具有线性性质

对于任意随机变量 X 和 Y 以及常量 a 和 b 有：

#### E(aX + bY) = aE(X) + bE(Y)

当两个随机变量 X 和 Y 独立且各自都有一个已定义的期望时 有：

#### E(XY) = E(X)E(Y)

------------


题目是要求树上每一个节点都要被染色

那么 E 就是每个节点都被染色

那么 随机变量 X 就是某个节点被染色

而 X 的总和即是 E

那么每个节点自己染色的贡献有 1/dep （因为每个祖先节点染色都会对自己有影响）

所以代码就是

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
#include<stack>
#include<cmath>
#define LL long long
using namespace std;
inline void read(int &x){
	x=0;int f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();	}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x*=f;
}
struct node{
	int nxt,v;
}e[200010];
int head[100010],tot;
inline void add(int x,int y)
{
	tot++;
	e[tot].v = y;
	e[tot].nxt = head[x];
	head[x]=tot;
}
int n,a,b,d[100010];
inline void dfs(int x,int fa)
{
	d[x]=d[fa]+1;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,x);
	}
}
int main()
{
	read(n);
	for(int i=1;i<n;i++) read(a),read(b),add(a,b),add(b,a);
	d[1]=1;
	dfs(1,0);
	double ans=0.0;
	for(int i=1;i<=n;i++) ans+=1.0/d[i];
	printf("%.20lf",ans);
	return 0;
}
```




---

## 作者：友利奈绪 (赞：3)

（看起来没人写题解……那juruo Rem_Inory就先补上题解了）

这道题是概率与期望的一道比较入门的题目，首先来看一看数学期望的定义吧。

1.数学期望（或均值），即随机变量在概率已以下的平均值：

E(x)= $\sum_{i=1}^n X_ip_i$ 

这个式子什么意思呢？
我们可以把数学期望理解成加权平均值一样的东西，就是对于每种情况将它们的权值和这种情况的概率乘积之和。

2.期望的线性性：对于任意随机变量X和Y，满足

E[aX+bY]=aE[X]+bE[Y]
期望的线性性是始终成立的，无论两随机变量是否独立。
这个性质也就决定了我们在解这个问题时可以将把所有点染黑的期望转化为染黑每个点的期望次数之和。

好，我们接下来就转为了求某个点期望的问题。
为什么说这道题基础？因为这道题的操作权值是1，也就是说我们只需要求选中每个点的概率是多少即可。而一个点自己把自己删除的概率是要在它有祖先的那棵树看的，这个概率是在那棵树上它优先被删除的概率。显然，当n=1时，概率就是1。依次往下推，它的概率应当是深度的倒数，存一下这个树的深度最后把它们相加就是结果。
注意double和保留小数点后位数，另外要存双向的边，否则会WA最后一个点。

最后%一下Oven
我存树的方法非常弱，~~但很容易看懂不是吗~~，求大佬们不要耻笑。
谨拜代码以闻
```cpp
#include<cstdio>
#include<iostream>
#define maxn 500500
using namespace std;
int depth[maxn],to[maxn],head[maxn],nnext[maxn],team[maxn];
bool b[maxn]; 
int tot;
int n,s=0,t=0;
double ans;
void add(int x,int y)
{
	tot++;
	nnext[tot]=head[x];
	head[x]=tot;
	to[tot]=y;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	depth[1]=1;
	team[t]=1;
	b[1]=true;
	t++;
	while(s!=t)
	{
		int now=team[s];
		s++;
		for(int i=head[now];i;i=nnext[i])
		{
			int x=to[i];
			if(b[x]==false)
			{
				b[x]=true;
				depth[x]=depth[now]+1;
				team[t]=x;
				t++;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		ans+=1.0*1/depth[i];
	}
	printf("%.20lf\n",ans);
	return 0;
} 
```


---

## 作者：漠寒 (赞：2)

## 题意

给出一棵含 $n$ 个白点的有根树,每次随机选择一个还没有被染黑的节点,将这个节点和这个节点子树中的所有点染黑。

问期望操作多少次后所有点都被染黑。

## 分析

由题意可得，如果一个节点的祖先被选中了，那么这个节点就已经被染黑了，不会再被选中。

因此对于每个节点，只考虑这个节点和它的所有祖先，其他点的选中并不会影响该点被选中的概率，相当于我们不断地选择，直到选中了这个点或者它的某一个祖先时，这个点才会被染色。

总结一下，如果某一点有 $x$ 个祖先，那么这 $(x+1)$ 个点中，每个点最先被选出的概率是相等的。

所以我们 $dfs$ 求出每个点的深度即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,head[100005],tot;
double ans;
struct node{
	int to,next;
}a[200005];
void dfs(int u,int fr,int dep){
	ans+=1.0/dep;
	for(int i=head[u];i;i=a[i].next){
		int v=a[i].to;
		if(v==fr)continue;
		dfs(v,u,dep+1);
	}
}
void add(int q,int m){
	a[++tot].to=m;
	a[tot].next=head[q];
	head[q]=tot;
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	dfs(1,0,1);
	printf("%.8lf",ans);
	return 0;
}
```


---

## 作者：whiteqwq (赞：2)

[CF280C Game on Tree](https://www.luogu.com.cn/problem/CF280C)

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1752631)

## 题意
- 给定一棵$n$个点的树，每次随机将一个未染黑的结点的子树全部染黑，求将整棵树染黑的期望次数。
- 数据范围：$1\leqslant n\leqslant 10^5$。

## 分析
有些题解关于排列解释的不清楚（不能保证不存在两种本质相同的排列），这里用一种更简单的方法解释：

考虑一个点什么时候才可以染色：它的所有祖宗结点没有染过色。

由于不在$x$到根节点路径上的点的染色与$x$的染色情况相互独立，所以我们$x$需要染色的概率就是$\frac{1}{dep_x}$（$dep_1=1$）。

解释一下，我们考虑随机从$x$到根节点的路径上选出一个点，那么选出$x$的概率就是$\frac{1}{dep_x}$（如果没有选出$x$，那么$x$就不能进行染色）。

因为选择$x$对步数的贡献为$1$，所以$x$对步数期望的贡献为$\frac{1}{dep_x}$。

根据期望的可加性，因此$ans=\sum_{x=1}^n E(x)=\sum_{x=1}^n\frac{1}{dep_x}$。

## 代码
```
#include<stdio.h>
const int maxn=100005,maxm=200005;
int n,e;
int start[maxn],to[maxm],then[maxm],dep[maxn];
double ans;
inline void add(int x,int y){
	then[++e]=start[x],start[x]=e,to[e]=y;
}
void dfs(int x,int last){
	dep[x]=dep[last]+1;
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last)
			continue;
		dfs(y,x);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
		ans+=1.0/dep[i];
	printf("%.20f\n",ans);
	return 0;
}

---

## 作者：字如其人 (赞：2)

期望入门题（~~显然我就过了这一道期望题~~）

很容易想到，每个子节点对答案的贡献都为1。

那么这个点有多少概率被选到呢？

我们再回到题意。

要是这个点被染色了，这个点的子树就都被染色了。

那么要是这个点被染色了，他或者他的祖先就被染色了。

那么这个节点自己先被染色的概率就为 1/（自己的祖先节点数+1（自己））。

那么我们就用一个bfs来求它有几个祖先。
```cpp
while(s!=t)
	{
		int u=tt[s];
		s++;
		for(int i=head[u];i;i=nxt[i])
		{
			int x=to[i];
			if(v[x]==false)
			{
				v[x]=true;
				depth[x]=depth[u]+1;
				tt[t]=x;
				t++;
			}
		}
	}
```

现在剩下的代码就很简单了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,head[200005],nxt[200005],to[200005],tot,tt[200005],t=1,depth[100005],s;
double ans;
bool v[200005];
void add(int x,int y){
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
//邻接表 
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	//输入 
	depth[1]=1;
	tt[0]=1;
	v[1]=true;
	//初始化 
	while(s!=t)
	{
		int u=tt[s];
		s++;
		for(int i=head[u];i;i=nxt[i])
		{
			int x=to[i];
			if(v[x]==false)
			{
				v[x]=true;
				depth[x]=depth[u]+1;
				tt[t]=x;
				t++;
			}
		}
	}
	//bfs 
	for(int i=1;i<=n;i++)ans+=1.0/depth[i];
	printf("%.20lf",ans);
	//输出 
	return 0;
}
```


---

## 作者：Tony102 (赞：1)

[link](https://www.luogu.com.cn/problem/CF280C)

[更好的阅读体验My Blog](https://tony102.xyz/index.php/2020/10/29/cf280c-game-on-tree/)


### Description

给出一棵树，每次随机等概率选择一未染黑的点，将它及其子树染黑。问期望多少次操作可以将树全部染黑。



### Solution

考虑一个点和它的子树被删除的方式

如果这个点被删除了，只有可能是它的父亲一直到根的儿子节点的路径上的某一条边被删除了。

假设现在要删的点是$u$, 深度为$dep_u$, 选中这条路上的边有$dep_u$条

因为我们只要删这条路上的一条边就可以把这个点删掉，所以期望是$E(u) = \frac{1}{dep_u} * 1$

所以答案是: $\sum_{u} \frac{1}{dep_u}$

注意$dep_{root}$要设成$1$



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int SIZE = 1e5 + 5;

int n, num;
int head[SIZE], dep[SIZE];
double ans, har[SIZE];

struct node {
	int to, nxt;
} edge[SIZE << 1];

inline int read()
{
	char ch = getchar();
	int f = 1, x = 0;
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
	return x * f;
}

inline void addEdge(int u, int v)
{
	edge[++ num].to = v, edge[num].nxt = head[u];
	head[u] = num;
}

inline void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	ans = ans + har[dep[u]];
	for (int i = head[u]; i; i = edge[i].nxt) {
		int v = edge[i].to;
		if (v == fa) continue;
		dfs(v, u);
	}
}

signed main()
{
	n = read();
	for (int i = 1, u, v; i < n; ++ i) {
		u = read(), v = read();
		addEdge(u, v); addEdge(v, u);
	}
	dep[1] = 1;
	for (int i = 1; i <= n; ++ i) {
		har[i] = 1.00 / i;
	}
	dfs(1, 0);
	printf("%.6lf\n", ans);
	return 0;
}
```





---

