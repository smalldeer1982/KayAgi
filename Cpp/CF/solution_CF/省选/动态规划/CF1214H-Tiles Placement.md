# Tiles Placement

## 题目描述

莫斯科市中心的新步行区由 $n$ 个广场组成，这些广场通过 $n-1$ 条人行道相连。我们定义一条简单路径为一系列广场的序列，序列中没有任何广场重复出现，并且序列中任意相邻的两个广场都通过一条人行道直接相连。简单路径的大小为其中包含的广场数。人行道的设计保证了任意两个不同的广场之间恰好有一条简单路径。

在为莫斯科城市日做准备时，市议会决定为所有 $n$ 个广场更换地砖。共有 $k$ 种不同颜色的地砖，编号为 $1$ 到 $k$。每个广场必须选择且仅选择一种地砖类型来铺设。为了让市中心的步行体验更加有趣，要求为每个广场选择地砖类型，使得任意一条大小恰好为 $k$ 的简单路径都包含所有 $k$ 种不同颜色的地砖。

你需要判断是否存在一种地砖铺设方案满足上述要求。

## 说明/提示

下图展示了第一个和第二个样例中步行区的结构。第二张图还展示了 $k=4$ 时的一种可能的颜色分配方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1214H/c0d5efd67b9d15df565c5a3d663c646a354f9abe.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 4
1 3
2 3
3 4
4 5
5 6
5 7
```

### 输出

```
Yes
1 1 2 3 4 1 1
```

## 样例 #2

### 输入

```
7 3
1 3
2 3
3 4
4 5
5 6
5 7
```

### 输出

```
No
```

# 题解

## 作者：Leap_Frog (赞：4)

### P.S.
没 G 题难 ![](//xn--9zr.tk/ll)

### Description.
略

### Solution.
首先找到直径。  
如果直径 $<K$ 直接随便填就可以了。  
如果直径 $\ge K$，那直径上所有数已经确定了，本质是循环同构的。  
如果左边支链和左边主链能形成 $\ge K$ 的链，直接无解，右边同理。  
**证明**：（显然）这条支链要同时满足右边主链和左边主链，显然不能同时满足。  
否则，让直径左边的支链和同深度主链相同，右边同理。  
这样可以让左边支链和右边主链、支链完美匹配。  

大体上是这样。  
但是！  

Corner Case 1：$K=2$ 必然有解，上文不一定，需要特判。  
Corner Case 2：不存在支链，特判一下即可。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int N=200005;int dep[N],mxd,dw,rt,f[N];char ban[N];
struct edge{int to,nxt;}e[N<<1];int et,head[N],n,K,rs[N],dg[N];
inline void adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et,dg[x]++;}
inline void dfs0(int x,int fa)
{
	dep[x]=dep[fa]+1,f[x]=fa;if(mxd<dep[x]) mxd=dep[x],dw=x;
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) dfs0(e[i].to,x);
}
struct $
{
	int fs,sc,mx;
	inline $ operator+(int b) {return($){fs+b,sc+b,mx};}
	inline $ operator+($ b)
	{
		int a[4]={fs,sc,b.fs,b.sc};sort(a,a+4);
		return ($){a[0],a[1],max(mx,b.mx)};
	}
}d[N];
inline void clor(int x,int fa,int dx)
{
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa)
		rs[e[i].to]=(rs[x]+dx-1)%K+1,clor(e[i].to,x,dx);
}
inline int fndmx(int x,int fa,int dep)
{
	int rs=0;for(int i=head[x];i;i=e[i].nxt)
		if(e[i].to!=fa&&!ban[e[i].to]) rs=max(rs,fndmx(e[i].to,x,dep+1));
	return max(rs,dep);
}
inline char get(int x,int fa)
{
	int sn=0,fg=0;for(int i=head[x];i;i=e[i].nxt)
		if(e[i].to!=fa) sn++,fg|=get(e[i].to,x);
	return sn>=2||fg;
}
int main()
{
	read(n,K);for(int i=1,x,y;i<n;i++) read(x,y),adde(x,y),adde(y,x);
	if(K==2)
	{
		rs[1]=1,clor(1,0,1),puts("Yes");
		for(int i=1;i<=n;i++) printf("%d%c",rs[i],i==n?'\n':' ');
		return 0;
	}
	mxd=dw=0,dfs0(1,0),rt=dw,mxd=dw=0,dfs0(rt,0);
	int dx=dw,md=(dep[dw]-1)>>1;for(int i=md;i;i--,dx=f[dx]);
	if(!(dep[dw]&1))
	{
		int d1,d2,f1=get(dx,f[dx]),f2=get(f[dx],dx);
		ban[f[dx]]=1,d1=fndmx(dw,0,1),ban[f[dx]]=0;
		ban[dx]=1,d2=fndmx(rt,0,1),ban[dx]=0;
		if((d1>=K&&f1)||(d2>=K&&f2)) return puts("No"),0;
		rs[dx]=1,rs[f[dx]]=K,clor(dx,f[dx],1),clor(f[dx],dx,K-1),puts("Yes");
		for(int i=1;i<=n;i++) printf("%d%c",rs[i],i==n?'\n':' ');
	}
	else
	{
		ban[f[dx]]=1;int d=fndmx(dw,0,1);if(d>=K&&get(dx,f[dx])) return puts("No"),0;
		rs[dx]=1,rs[f[dx]]=K,clor(dx,f[dx],1),clor(f[dx],dx,K-1),puts("Yes");
		for(int i=1;i<=n;i++) printf("%d%c",rs[i],i==n?'\n':' ');
	}return 0;
}
```

---

## 作者：whiteqwq (赞：4)

[CF1214H Tiles Placement](https://www.luogu.com.cn/problem/CF1214H)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1747190)

## 题意
- 给定一棵$n$个点的树，可以用$k$种颜色染色；
- 你需要判断是否存在一种染色方案满足任意长度为$k$的链必须包含$k$种颜色；
- 若有方案，则输出"Yes"，并任意输出一种方案；否则输出"No"。
- $1\leqslant n\leqslant 2\cdot 10^5,2\leqslant k\leqslant n$。

## 分析
最近听了一个神仙讲了这道题，就来做一做。

一道找规律神题，~~现场推出了和正解等价的规律，但是还是不会~~。

先给出结论：

- $k=2$时，一定存在这样的染色方案，只需要按照深度交替染色就可以了；
- $k>2$时，若存在$3$个点距离大于等于$k$，那么不存在染色方案。

$k=2$时，结论显然成立。

$k>2$时，我们看一看图：

![](https://fp1.fghrsh.net/2020/10/08/7700b412c89bab2b2cd0c832b3d4922c.png)

设$a$到$x$距离为$len_a$，$b$到$x$距离为$len_b$，$c$到$x$距离为$len_c$。

如果$len_a+len_b\geqslant k$，$len_a+len_c\geqslant k$，$len_b+len_c\geqslant k$，那么我们任取$a$到$x$链上一点$p$，$b$到$x$链上一点$q$，$c$到$x$链上一点$r$，使$p$到$q$的距离为$k$，$q$到$r$的距离为$k$。

我们令$p$到$q$链上已经确定了染色方案，那么$p$到$x$的染色方案递推到$r$的方案，一定与$q$到$x$的染色方案递推到$r$的方案不同，于是我们推出了矛盾。

因此结论成立。

我们考虑取出直径（这里取出直径主要是为了解决第二问），求出每个点不向直径扩展的最长链和次长链，并对于直径上的点和直径外的点分类讨论：
（下面的最长链与次长链均指不向直径扩展的链）

- 对于所有的$x$，如果最长链与次长链合并后长度大于等于$k$，那么不能构造方案。（设最长链的链底为$p_1$，次长链的链底为$p_2$，则直径两个端点中的一个一定可以与$p_1$和$p_2$构成两两距离大于等于$k$的三个点）
- 若$x$在直径上，如果最长链与$x$分隔开的直径两段合并后长度均大于等于$k$，那么不能构造方案。（最长链链底和直径的两端可以构成两两距离大于等于$k$的三个点）

这样，我们就判断出了是否可以进行构造。

构造方法比较显然：

首先，因为在满足上述要求下，长度大于等于$k$的链一定都在直径上，所以我们先对直径进行染色。

我们考虑剩下的点如何染色——剩下的点一定可以从直径上的颜色地推下来。

但是有一点细节要注意：

![](https://fp1.fghrsh.net/2020/10/08/67063642e456f8bbb146ec1e147d77a4.png)

如图，$k=4$，此时假设我们选择的直径为$(1,6)$，那么$(1,7),(3,6),(3,7)$这些路径的染色搭配也要考虑。

我们可以取直径中点$mid$，直径上$mid$左边的点可以采用颜色不断加$1$的染色策略，$mid$及右边的点可以采用颜色不断减$1$的染色策略，这样$mid$左右两点产生的路径我们都可以满足条件了。

复杂度：$O(n)$。

## 代码
代码找了好久错，结果是$\text{getlen}$的递归调用了$\text{dfs}$（捂脸）。

注意特判$\text{m=2}$
```
#include<stdio.h>
#define inf 1000000000
const int maxn=200005,maxm=maxn<<1;
int n,m,e,s1,s2,s,maxx,col,flg,mid;
int start[maxn],to[maxm],then[maxm];//链式前向星
int dep[maxn],f[maxn],ans[maxn],flen[maxn],slen[maxn];//深度，递归时的父亲，染的颜色，最长链，次长链
inline void add(int x,int y){//加边
	then[++e]=start[x],start[x]=e,to[e]=y;
}
void dfs(int x,int last){
	f[x]=last,dep[x]=dep[last]+1;
	flen[x]=slen[x]=0;
	if(dep[x]>maxx)
		maxx=dep[x],s=x;
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last)
			continue;
		dfs(y,x);
	}
}
void getlen(int x,int last){
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last||ans[y])
			continue;
		getlen(y,x);
		if(flen[y]+1>flen[x])
			slen[x]=flen[x],flen[x]=flen[y]+1;
		else if(flen[y]+1>slen[x])
			slen[x]=flen[y]+1;
		if(slen[y]+1>slen[x])
			slen[x]=slen[y]+1;
	}
}
void solve(int x,int c,int t){//染色，其中t=1时颜色为父亲的颜色+1，t=-1时相反
	ans[x]=c;
	c=(c+t+m-1)%m+1;
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(ans[y]!=0)
			continue;
		solve(y,c,t);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	maxx=-inf,dfs(1,0),s1=s;//s1为直径一个端点
	maxx=-inf,dfs(s,0),s2=s;//s2为直径另一端点
	if(m==2){//特判m=2
		puts("Yes");
		for(int i=1;i<=n;i++)
			printf("%d%c",dep[i]%2+1,i==n? '\n':' ');
		return 0;
	}
	for(int i=s2;i!=0;i=f[i]){//对直径染色
		col=col%m+1;
		if((dep[s1]+dep[s2])/2==dep[i])//找到中点
			mid=i;
		ans[i]=col;
	}
	for(int i=s2;i!=0;i=f[i]){//直径上的点向它不向直径扩展的子树中求最长/次长链
		getlen(i,0);
		if(ans[i]&&flen[i]&&dep[i]+flen[i]>=m&&(dep[s2]-dep[i]+1)+flen[i]>=m){
			puts("No");
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
		if(flen[i]+slen[i]+1>=m){
			puts("No");
			return 0;
		}
	for(int i=s2;i!=mid;i=f[i])//直径前半段染色
		solve(i,ans[i],-1);
	for(int i=mid;i!=0;i=f[i])//直径后半段染色
		solve(i,ans[i],1);
	puts("Yes");
	for(int i=1;i<=n;i++)
		printf("%d%c",ans[i],i==n? '\n':' ');
	return 0;
}
```

---

