# CNF 2

## 题目描述

“在布尔逻辑中，如果一个公式是子句的合取，则其处于合取范式（CNF）或子句范式中，其中子句是文字的析取”（引自 https://en.wikipedia.org/wiki/Conjunctive_normal_form）。

换句话说，CNF 是形如 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF571C/da94d4e24134d35cc07e6645e48c609e19333457.png) 的公式，其中 $\&$ 表示逻辑“与”（合取），$|$ 表示逻辑“或”（析取），$v_{ij}$ 是某些布尔变量或其否定。括号中的每个语句称为一个子句，$v_{ij}$ 称为文字。

给定一个包含变量 $x_{1}, \ldots, x_{m}$ 及其否定的 CNF。已知每个变量在最多两个子句中出现（包括被否定和未被否定的情况）。你的任务是判断该 CNF 是否可满足，即是否存在一组变量赋值使得 CNF 的值为真。如果 CNF 可满足，则还需确定使 CNF 为真的变量赋值。

保证每个变量在每个子句中至多出现一次。

## 说明/提示

在第一个样例中，公式为 $(x_1 | \neg x_2) \& (x_2 | \neg x_1)$。一种可能的答案为 $x_{1} = \text{TRUE}$，$x_{2} = \text{TRUE}$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2 2
2 1 -2
2 2 -1
```

### 输出

```
YES
11
```

## 样例 #2

### 输入

```
4 3
1 1
1 2
3 -1 -2 3
1 -3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 6
2 1 2
3 1 -2 3
4 -3 5 4 6
2 -6 -4
1 5
```

### 输出

```
YES
100010
```

# 题解

## 作者：xcxcli (赞：1)

[链接](https://www.luogu.com.cn/problem/CF571C)

题目就是求使 $c_i$ 为真的方案。

我们考虑将含有 $b_k$ 的 $c_i$ 连一条边，可以发现一条边能使对应的两个点之一满足条件。

对于只出现一次的 $b_k$，它对应的 $c_i$ 显然能满足条件。我们先将这些点和边忽略。可以发现如果剩下的某个联通块是树，那么一定无解。

我们可以把类树的部分忽略，剩下图的都是环，接下来只用让每条边满足一个对应点就好了。

```cpp
#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;
int rd(){
	int k(0),f(1);char c(getchar());
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-48,c=getchar();
	return f?k:-k;
}
const int N=200001;
struct E{int v,w,nxt;}e[N<<1];
int n,m,_,x,en=1,head[N],ok[N],ans[N],I[N];vector<int>V[N];queue<int>q;
/*
ans: b_i 的取值
ok:  第 i 个限制是否已经满足
I:   点的度数
*/
void add(int u,int v,int w){e[++en]={v,w,head[u]},head[u]=en;}
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v,w=e[i].w;
		if(ans[w]<0&&!ok[v])ans[w]=(i&1)^1,ok[v]=1,dfs(v);
	}
}
int search(int u){//找一个没满足要求的联通点
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v,w=e[i].w;
		if(ans[w]<0&&!ok[v]){ans[w]=i&1,ok[u]=1;return v;}
	}
	return-1;
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd(),m=rd();
	for(int i=1;i<=m;++i)ans[i]=-1;
	for(int i=1;i<=n;++i){
		_=rd();
		while(_--){
			x=rd();
			if(x>0)V[x].push_back(i);
			else V[-x].push_back(-i);
		}
	}
	for(int i=1;i<=m;++i){
		if(V[i].empty())continue;
		sort(V[i].begin(),V[i].end());
		if(V[i].front()>0){//都是 b_i
			ans[i]=1;
			for(auto j:V[i])ok[j]=1;
		}
		else if(V[i].back()<0){//都是 !b_i
			ans[i]=0;
			for(auto j:V[i])ok[-j]=1;
		}
		else{//一个 b_i 一个 !b_i
			int u=-V[i][0],v=V[i][1];
			add(u,v,i),add(v,u,i),++I[u],++I[v];
		}
	}
	for(int i=1;i<=n;++i)if(ok[i])dfs(i);
	for(int i=1;i<=n;++i)if(!ok[i]&&I[i]==1)q.push(i);
	while(!q.empty()){
		int u=q.front(),v=search(u);q.pop();
		if(v<0){puts("NO");return 0;}
		if(--I[v]==1)q.push(v);
	}
	for(int u=1;u<=n;++u)if(!ok[u]){//找环
		if(search(u)<0){puts("NO");return 0;}
		dfs(u);
	}
	puts("YES");
	for(int i=1;i<=m;++i)putchar(ans[i]==0?'0':'1');
	return 0;
}
```


---

## 作者：chenzida (赞：0)

这个题解主要是对第一篇的补充，思路请看楼上。  
主要就是规划一下每个点对应哪一条边，我主要说一下代码细节~~毕竟我调了一年~~

$1.$ 当有一个 $b_k$ 只出现 $1$ 次或者出现的两次同号的话，可以用一个 $flag$ 标记一下。之后用拓扑排序的形式把所有可以直接满足的都找出来，然后剩下的再做常规处理。

$2.$ 找环的时候，首先我们以任意点为起点，$\text{dfs}$ 一遍，找到任意环上的点，之后以那个点为起点再 $\text{dfs}$ 一遍找方案。

$3.$ 第二遍 $dfs$ 的时候，每个点要找一条出边，我们可以找出一棵搜索树，然后每个点和它连向父亲的边匹配，然后根就和环上的另一条边匹配。所以我们要保证给根节点留一条边，但是还不能直接留 $\text{head}$，因为可能这条边正好不在环上。所以我们在找环时记录一条环上的边，然后搜答案的时候先把这条边和根匹配，之后再做之后的搜索。

$4.$ 边的数量比较大，要开两倍（我开了 $10^6$ 能过）。

$5.$ 遍历时最好统一一下，一个边的权值和这条边的哪个端点有关，要不然会调死。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e6+10;
void Min(int& x,int y){x=min(x,y);}
void Max(int& x,int y){x=max(x,y);}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m;
int ki[NR];
vector<int>v[NR];
int num[NR][2],op[NR][2];
int to[NR<<1],val[NR<<1],nxt[NR<<1],head[NR],tot=1;
void add(int x,int y,int z){
	to[tot]=y,val[tot]=z,nxt[tot]=head[x],head[x]=tot++;
}
bool FFFF[NR];
bool flag[NR];
int ans[NR],Ans[NR];
int Num[NR];
int vis[NR];
bool F[NR],ff[NR];
void dfs1(int x,int col,int la){
	if(vis[x]==col){if(!Num[col])Num[col]=x,FFFF[la]=FFFF[la*2-(la^1)]=1;return;}
	vis[x]=col;
	for(int i=head[x];i;i=nxt[i]){
		if(ff[i])continue;
		ff[i]=ff[i*2-(i^1)]=1;
		dfs1(to[i],col,i);
	}
}
void dfs2(int x,int col)
{
	vis[x]=col;int pos=0;
	for(int i=head[x];i;i=nxt[i])
		if(x==col&&!ans[x]&&FFFF[i]){ans[x]=val[i]*-1;pos=i;break;}
	for(int i=head[x];i;i=nxt[i]){
		if(ff[i]||i==pos)continue;ff[i]=ff[i*2-(i^1)]=1;
		if(!vis[to[i]])ans[to[i]]=val[i],dfs2(to[i],col);
	}
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		ki[i]=read();
		for(int j=1,x,X;j<=ki[i];j++){
			x=read(),X=abs(x);v[i].push_back(x);
			if(num[X][0])num[X][1]=i,op[X][1]=(x==X);
			else num[X][0]=i,op[X][0]=(x==X);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(!num[i][0])continue;
		if(!num[i][1])flag[num[i][0]]=1,Ans[i]=op[i][0];
		if(op[i][0]==op[i][1])flag[num[i][0]]=flag[num[i][1]]=1,Ans[i]=op[i][0];
	}
	queue<int>q;
	for(int i=1;i<=n;i++)if(flag[i])q.push(i);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(int i=0;i<ki[x];i++){
			int t=abs(v[x][i]);
			if(num[t][0]==x&&!flag[num[t][1]]&&num[t][1])flag[num[t][1]]=1,q.push(num[t][1]),Ans[t]=op[t][1];
			else if(num[t][1]==x&&!flag[num[t][0]]&&num[t][0])flag[num[t][0]]=1,q.push(num[t][0]),Ans[t]=op[t][0];
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(!num[i][0])continue;
		if(flag[num[i][0]]||flag[num[i][1]])continue;
		add(num[i][0],num[i][1],i*(op[i][1]?1:-1)),add(num[i][1],num[i][0],i*(op[i][0]?1:-1));
	}
	for(int i=1;i<=n;i++)if(!vis[i]&&!flag[i])dfs1(i,i,-1),F[i]=1;
	for(int i=1;i<=n;i++)if(!flag[i]&&F[i]&&!Num[i]){puts("NO");return 0;}
	memset(ff,0,sizeof(ff)),memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)if(!flag[i]&&F[i])dfs2(Num[i],Num[i]);
	for(int i=1;i<=n;i++)if(!flag[i])Ans[abs(ans[i])]=(ans[i]>0);
	puts("YES");for(int i=1;i<=m;i++)printf("%d",Ans[i]);
	return 0;
}
```

---

