# [USACO05JAN] Muddy Fields G

## 题目描述

大雨侵袭了奶牛们的牧场。

牧场是一个 $R \times C$ 的矩形，其中 $1 \leq R,C \leq 50$。大雨将没有长草的土地弄得泥泞不堪，可是小心的奶牛们不想在吃草的时候弄脏她们的蹄子。为了防止她们的蹄子被弄脏，约翰决定在泥泞的牧场里放置一些木板。每一块木板的宽度为 $1$ 个单位，长度任意，每一个板必须放置在平行于牧场的泥地里。 

约翰想使用最少的木板覆盖所有的泥地．一个木板可以重叠在另一个木板上，但是不能放在草地上。

## 样例 #1

### 输入

```
4 4
*.*.
.***
***.
..*.```

### 输出

```
4```

# 题解

## 作者：Miko35 (赞：57)

此题重点在二分图的建图。

考虑放置木板的决策，由于可以重复覆盖，所以对于两个可以选择的区间 $a,b$，若 $b$ 被 $a$ 覆盖，那么选择 $a$ 一定优于选择 $b$。

解释如图：泥地为黄色，草地为绿色

![](https://i.loli.net/2020/10/05/6Xcy1QAImGVW7qh.png)

显然，木板 $A$ 一定比木板 $B$ 更优，因为橙色部分可以重复覆盖。

由此易得所有的木板两头都是没有泥地的：若有，则增长此木板一定比原方案更优。

得到这个结论，我们可以先预处理出所有可能放置木板的位置，也就是在每行每列连续的泥地的位置。如图所示：所有木板可能放置的位置是下图的十个。

![](https://i.loli.net/2020/10/05/2Kz3QrDuPWJlqvd.png)

对于每一个点，要么被横着覆盖，要么被竖着覆盖。举例来讲，$(3,3)$ 在行上会被横木板 $3$ 覆盖，在列上会被竖木板 $4$ 覆盖。而我们要让所有的点都被覆盖，也就是需要满足下图所示的所有条件：

![](https://i.loli.net/2020/10/05/xJb7FqRIX6POMgw.png)

我们需要选出最少的木板满足这样的若干个约束条件。**我们把每一个泥地看成一条边，左端点为其对应的横木板，右端点为其对应的竖木板。** 显然这是一个二分图，左边全部为横木板，右边全部为竖木板。

![](https://i.loli.net/2020/10/05/p69WzRj7N8fJMOs.png)

考虑我们**放置一个木板**，相当于满足所有包含它的约束条件，**也就是将其所连的边进行染色**。 而对于每一个泥地（也就是边），**如果它被染色，就证明这个格子的约束条件已被满足**。

所以这个问题转化为：**一次操作可以选择一个点，将所连的边染色，目的是让所有边被染色。**

即为二分图最小点覆盖。

而最小点覆盖等于最大匹配，故建图跑匈牙利即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int cnt1,cnt2;
bool a[1002][1002];
int match[1002];
int ans;
bool visit[1002];
bool dfs(int x){
	for(int i=1;i<=cnt2;i++){
		if(a[x][i]&&!visit[i]){
			visit[i]=1;
			if(!match[i]||dfs(match[i])){
				match[i]=x;
				return 1;
			}
		}
	}
	return 0;
}
char ch[1002][1002];
int h[1002][1002];
int c[1002][1002];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){//统计横向木板 
		cin>>ch[i]+1;
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='*'){
				if(j==1||ch[i][j-1]!='*'){
					h[i][j]=++cnt1;
				}
				else h[i][j]=cnt1;
			}
		}
	}
	for(int i=1;i<=m;i++){//统计竖向木板 
		for(int j=1;j<=n;j++){
			if(ch[j][i]=='*'){
				if(j==1||ch[j-1][i]!='*'){
					c[j][i]=++cnt2;
				}
				else c[j][i]=cnt2;
				a[h[j][i]][c[j][i]]=1;
			}
		}
	}
	for(int i=1;i<=cnt1;i++){//跑匈牙利 
		memset(visit,0,sizeof visit);
		ans+=dfs(i);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：xh39 (赞：17)

## algorithm
以下是本题解用到的算法,请先掌握以下算法再来看此题解。

1.二分图最大匹配。(本题解用的是匈牙利。)

2.konig定理(二分图最小点覆盖==二分图最大匹配) 。

3.链式前向星存图。
## solution
> 每一块木板的宽度为1个单位,长度任意。

> 每一个板必须放置在平行于牧场的泥地里。

所以一个木板子要么是横向的,要么是纵向的。这样我们就可以建立二分图,一个表示横向的,一个表示纵向的。

假设所有的木板都是横向的,我们记录下哪几个是同一块木板的(用数组记录,相同的数字相同,不同的数字不同)。

由于全部是横向的,那么可以采用贪心策略。即找出所有**连续**的横泥地,在同一个**连续**的横泥地里它们就可以用同一块木板覆盖。

竖着的木板和横着的木板思路一样。

对于样例,相同的数字表示共用一块木板。

下面是拿样例具体说明过程,建议同学们自己画图理解。
```cpp
4 4  横   纵
*.*. 1020 1040 
.*** 0333 0345
***. 4440 2340
..*. 0050 0040
```
我们横竖木板至少要选其中的1个。我们就可以建立二分图。求最小点覆盖。
二分图(为方便看,不同的边用了不同的颜色):
![](https://cdn.luogu.com.cn/upload/image_hosting/maro0y0i.png)

最小点覆盖是$1l,2r,3l,4l$($l$表示左边的点,$r$表示右边的点。)

好了,具体说明在代码↓里了。
## ac.code
```cpp
#include<iostream>
using namespace std;
#include<cstring>
int kkksc03[1000005]; //kkksc03表示此点匹配的是什么。
bool mark[1000005]; //mark标记数组。
//----邻接表存图(准确的说是链式前向星吧)。-----
struct xyq{ 
	int v,next;
}_[1000005];
int head[1000005],tot=1;
void add(int u,int v){
	_[tot].v=v;
	_[tot].next=head[u];
	head[u]=tot;
	++tot;
}
//------------------
bool dfs(int iakioi){ //二分图匹配。这里不多做解释。
	int i;
	for(i=head[iakioi];i;i=_[i].next){
		if(mark[_[i].v]){ 
			continue;
		}
		mark[_[i].v]=1;
		if(!kkksc03[_[i].v]||dfs(kkksc03[_[i].v])){
			kkksc03[_[i].v]=iakioi;
			return true;
		}
	}
	return false;
}
char a[1005][1005];
int x[1005][1005],y[1005][1005];
int main(){
	int n,m,i,j,sumx=1,sumy=1,sum=0;
	cin>>n>>m;
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			cin>>a[i][j];
			if(a[i][j]=='*'){
				x[i][j]=a[i-1][j]=='*'?x[i-1][j]:sumx++; //如果没有断开,就可以使用同一块木板。
				y[i][j]=a[i][j-1]=='*'?y[i][j-1]:sumy++; //同上。
				add(x[i][j],y[i][j]); 
			}
		}
	}
	for(i=1;i<sumx;++i){ //二分图最大匹配。
		memset(mark,0,sizeof(mark));
		sum+=dfs(i);
	}
	cout<<sum;//二者使用其一,求最小点覆盖。
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：9)

# [Muddy Fields G](https://www.luogu.com.cn/problem/P6062)
**希望**能比其他题解更让人理解一点。
![image.png](https://public.noi.top/image/1584447213418.png)
蓝色/白色的点都是非泥坑点。绿色的点是泥坑点。

## 捕捉要素建模

首先，作为一个稍微见识过一些转图论的题目的OIer，你应该先想到这是图论题。

我们捕捉到题目中发现有**要覆盖所有泥地**，珂以猜出是个覆盖问题或SAT问题（当然这是面对此题夭折的算法）。然后被覆盖的对象应该是泥坑。然后发现数据范围较小，于是珂以把对象具体为每个小泥坑。

## 泥坑作为点

我们先看泥坑作为点。


从上图我们珂以看到，一个点要么被一个**纵向木板**覆盖，要么被一个**横向木板**覆盖，由于模板一盖肯定是盖满整个泥坑块，所以就是一定要选择自己处于的**最长纵向泥坑块**和自己处于的**最长横向泥坑块**其中的一个。~~好像2-SAT问题啊。~~


是的你没错，这就是2-SAT —— 等等题目要求的是最少放多少……再见了2-SAT。

想法夭折。

## 泥坑作为边

我们把带有每个泥坑的纵连通块和横连通块的图放出来。
![image.png](https://public.noi.top/image/1584452637826.png)

根据前面的经验，这无非就是把一个泥坑块想象成一条边，所在的横向和纵向泥坑块是点，遇到一个泥坑点就把横向泥坑块所对应的点和纵向泥坑块所对应的点连起来。

整理一下，点是每一个横/纵向泥坑连通块作为一个点，然后每一个小泥坑作为边连接两个点，求最小点覆盖。

由于这是一个二分图（纵连通块不能连纵连通块，横连通块也不能连横连通块），所以珂以用 König 定理转换为二分图做。

> 二分图的最小点覆盖数= 二分图的最大匹配数。

所以转换边后这就是二分图匹配。

## 算法分解

首先我们要找横连通块，遍历每一个行，然后用```while```去找横连通块

纵连通块同上

然后遍历每一个泥坑，去建边。建好边后跑一个 Dinic 或者 Hungary 去做二分图即可。二分图就不多讲了

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=109,M=109*109*2;
int n,m; char c[N][N]; int cnt1,cnt2,h[N][N],l[N][N],ans;
struct edge{int to,nxt;}e[M]; int hd[M],tot;		//申明变量没啥好说的 
void add(int u,int v){
	e[++tot]=(edge){v,hd[u]}; hd[u]=tot;
}
bool vst[M*2]; int cc[M*2];
bool hungary(int u){								//匈牙利（用dinic也行 
	for(int i=hd[u],v;i;i=e[i].nxt)
		if(!vst[v=e[i].to])
			if(cc[v]==(!(vst[v]=1))||hungary(cc[v]))
				return cc[v]=u,1;
	return 0; 
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",c[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(c[i][j]=='*') ++cnt1;    //新的连通块 
			while(c[i][j]=='*') h[i][j++]=cnt1; //横向连通块 
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			if(c[i][j]=='*') ++cnt2;	//新的连通块 
			while(c[i][j]=='*') l[i++][j]=cnt2,l[i-1][j]+=cnt1; //纵向连通块 
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(c[i][j]=='*') add(h[i][j],l[i][j]),add(l[i][j],h[i][j]); //建边 
	for(int i=1;i<=cnt1;i++) memset(vst,0,sizeof(vst)),ans+=hungary(i);
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：happy_dengziyue (赞：1)

### 1 思路

这道题求二分图最大匹配。

对于一块木板 $A$，如果存在一块面积比它大还能整个覆盖它的木板 $B$，那么不可能选木板 $A$。

我们将不存在“木板 $B$”的“木板 $A$”称作“极大木板”。特别地，面积为 $1$ 的木板也有可能（但不一定）成为“极大木板”。

我们可以找出所有极大木板并编号。

我们可以将极大木板分成两类：横着的和竖着的。以下简称“横板”和“竖板”。

显然，横板的左右两边都是草地或边界，同理，竖板上下两边也都是草地或边界。

显然，对于任意一个泥地，有且仅有一个横板覆盖它，同时有且仅有一个竖板覆盖它。

我们可以记录下每个泥地被哪块横板和哪块竖板覆盖，然后连一条从横板到竖板的容量为 $1$ 边。

于是这道题就变成了：选择几个点，使得所有的边的端点都是它们之一（或之二）。也就是二分图最小点覆盖，也就是二分图最大匹配。

然后，从源点向每个横板连容量为 $1$ 的边，从每个竖板向汇点连容量为 $1$ 的边，加上之前连的边，记得建反边，跑一遍带上优化的 `dinic` 网络流就好了。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int n;
int m;
#define s 0
#define t 5200
bool g[52][52];
struct L{
	int x1,y1,x2,y2;
	bool k;//0 x 1 y
}l[5200];
int li=0;
int x[52][52];
int y[52][52];
struct E{
	int v,w,a,nx;
}e[1000002];
int ei=0;
int fir[5202];
int cur[5202];
int de[5202];
int ans=0;
inline void addedge(int u,int v,int w){
	++ei; e[ei].v=v; e[ei].w=w; e[ei].a=ei+1; e[ei].nx=fir[u]; fir[u]=ei;
	++ei; e[ei].v=u; e[ei].w=0; e[ei].a=ei-1; e[ei].nx=fir[v]; fir[v]=ei;
}
bool bfs(){
	memset(de,0,sizeof(de));
	queue<int>q;
	de[s]=1;
	q.push(s);
	int u;
	while(!q.empty()){
		u=q.front();
		q.pop();
		for(int i=fir[u],v;i;i=e[i].nx){
			v=e[i].v;
			if(e[i].w&&!de[v]){
				de[v]=de[u]+1;
				q.push(v);
			}
		}
	}
	return de[t];
}
inline int mi(int a,int b){
	return a<b?a:b;
}
int dfs(int u,int f){
	if(u==t||!f)return f;
	int res=0;
	for(int i=cur[u],v,w;i;i=e[i].nx){
		cur[u]=i;
		v=e[i].v;
		if(e[i].w&&de[u]+1==de[v]){
			w=dfs(v,mi(f,e[i].w));
			if(w){
				e[i].w-=w;
				e[e[i].a].w+=w;
				res+=w;
				f-=w;
				if(!f)break;
			}
		}
	}
	return res;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P6062_1.in","r",stdin);
	freopen("P6062_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		char c[52];
		scanf("%s",c+1);
		for(int j=1;j<=m;++j){
			if(c[j]=='.')g[i][j]=false;
			else g[i][j]=true;
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1,k;j<=m;++j){
			if(!g[i][j-1]&&g[i][j]){
				for(k=j+1;k<=m&&g[i][k];++k);
				--k;
				l[++li]=(L){i,j,i,k,0};
			}
		}
	}
	for(int j=1;j<=m;++j){
		for(int i=1,k;i<=n;++i){
			if(!g[i-1][j]&&g[i][j]){
				for(k=i+1;k<=n&&g[k][j];++k);
				--k;
				l[++li]=(L){i,j,k,j,1};
			}
		}
	}
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	for(int i=1;i<=li;++i){
		if(!l[i].k){
			for(int j=l[i].y1;j<=l[i].y2;++j){
				x[l[i].x1][j]=i;
			}
		}
		else{
			for(int j=l[i].x1;j<=l[i].x2;++j){
				y[j][l[i].y1]=i;
			}
		}
	}
	memset(fir,0,sizeof(fir));
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(x[i][j]&&y[i][j]){
				addedge(x[i][j],y[i][j],1);
			}
		}
	}
	for(int i=1;i<=li;++i){
		if(!l[i].k)addedge(s,i,1);
		else addedge(i,t,1);
	}
	while(bfs()){
		memcpy(cur,fir,sizeof(fir));
		ans+=dfs(s,0x3f3f3f3f);
	}
	printf("%d\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/56830036)

By **dengziyue**

---

## 作者：Godzilla (赞：1)

### 题目大意 :

给定一个 $R \times C$ 的矩阵，其中有一些特殊的矩形，请问至少可以用任意长度，宽度为1矩形恰好覆盖。

#### 必须平行与矩阵，且恰好覆盖。


------------


### 前置知识 :

1.二分图最小点覆盖

------------

### 思路 :

二分图最小点覆盖 ：每条边有2个端点，且二者至少选择一个，称之为“二要素”。

二分图最小点覆盖点数 $=$ 二分图最大匹配边数

（出自算法竞赛进阶指南)

[二分图与网络流学习 xht37](https://www.xht37.com/%E4%BA%8C%E5%88%86%E5%9B%BE%E4%B8%8E%E7%BD%91%E7%BB%9C%E6%B5%81-%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/#lwptoc19)

-------------------------------

考虑一块1$\times$1的矩形，只能被横着的矩形，或者竖着的矩形覆盖，这就符合了“二要素”。 并且要使得覆盖的矩形最少，那么只需覆盖一次就好，这就符合了“二分图最小点覆盖”的特征。

如果就这样连边，跑匈牙利算法的话，是错的。

因为覆盖的是矩形，不可以覆盖到非特殊点，且同行或同列的矩形可以被同一块矩形覆盖到。那么，就可一贪心的想，对于一个1$\times$1的特殊矩形$(i,j)$，如果与之同行且在它前面一个的矩形$(i,j-1)$，那么就可以与它连边，因为覆盖了$(i,j-1)$那么就覆盖了$(i,j)$。列的话，同理。





------------
定义 :

$num1 , num2$为行，列的当前编号。

$cnt[i][j][0/1]$ 为 $(i,j)$的行的编号与列的编号。

$match[i]$ 为列 $i$的匹配行。


------------


### 代码 :
```

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

const int kN=105;
const int kMax=5e3+5;

int r,c;
int to[kMax],nex[kMax],head[kMax],tot;
int match[kMax],ans;
int cnt[kN][kN][2];//(i,j)行的编号与列的编号
int num1,num2;//行的编号与列的编号

char a[kN][kN];

bool v[kMax];

void Add(int x,int y){to[++tot]=y;nex[tot]=head[x];head[x]=tot;}//链式前向星

bool Dfs(int x){//求二分图最大匹配边数 = 二分图最小点覆盖
	for(int i=head[x];i;i=nex[i]){
		int ar=to[i];
		if(v[ar]){continue;}
		v[ar]=1;
		if(!match[ar]||Dfs(match[ar])){
			match[ar]=x;return 1;
		}
	}
	return 0;
}

int main(){
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r;++i){
		for(int j=1;j<=c;++j){
			cin>>a[i][j];
			if(a[i][j]=='*'){
				if(a[i][j-1]!='*'){cnt[i][j][0]=++num1;}//无法与相邻点在同一行覆盖
				else{cnt[i][j][0]=cnt[i][j-1][0];}//可以在同一行覆盖
				if(a[i-1][j]!='*'){cnt[i][j][1]=++num2;}//无法与相邻点在同一列覆盖
				else{cnt[i][j][1]=cnt[i-1][j][1];}//可以在同一列覆盖
				Add(cnt[i][j][0],cnt[i][j][1]);//建边
			}
		}
	}
	for(int i=1;i<=num1;++i){//以行为左部端点
		fill(v,v+kN,0);
		ans+=(Dfs(i));
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：逃离地球 (赞：1)

[更好的阅读](https://yangqianrui.github.io/post/Luogu-P6062-Solution/)

[**题目链接**](https://www.luogu.com.cn/problem/P6062)

首先有一个显然的事实，就是一块木板在延伸到最长的情况下一定是更优的。

![图挂了？](https://i.loli.net/2020/03/13/ODSInzclxEWwLmJ.png)

如图所示，覆盖 $(2,2),(2,3),(2,4)$ 的木板一定会优于仅覆盖 $(2,2),(2,3)$ 的木板，所以此题只需要考虑使用能延伸到最长的木板即可。也就是说，此题木板可能存在的位置是确定的，就是每行的连通块和每列的连通块，如图所示：

![图挂了？](https://i.loli.net/2020/03/13/Wu9HdKDMftyeZ2o.png)

蓝线和绿线是木板可能存在的位置。

对于每个泥泞的格子，都至少要被自己所在的行连通块或列连通块的其中一个覆盖。让人~~情不自禁地~~想到二分图的最小点覆盖[1]。

考虑把行连通块和列连通块分别看作左部节点和右部节点，每个泥泞的格子看作一条边，连接这个格子所在的行连通块和列连通块。那么这个二分图的最小点覆盖就是答案。

由 Konig 定理[2]，只需求出该二分图的最大匹配即可。

**相关解释：**

1. 最小点覆盖：选出一个最小的点集，使得二分图的所有边都有至少一个端点属于这个点集。

2. Konig定理：Konig定理于1913年由匈牙利数学家柯尼希（D.Konig）首先陈述，定理的内容是二分图中的最大匹配数等于这个图中的最小点覆盖数。

**代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, b1[105][105], b2[105][105], num1, num2, vis[10005], match[10005], ans = 0;
// b1 表示所在行联通块编号，b2 表示所在列连通块编号
vector<int> head[10005];

bool dfs(int x) {
    for (auto q : head[x]) {
        if (!vis[q]) {
            vis[q] = 1;
            if (!match[q] || dfs(match[q])) {
                match[q] = x;
                return true;
            }
        }
    }
    return false;
}
// 匈牙利算法

char c[105][105];
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        scanf("%s",c[i] + 1);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (c[i][j] == '*') num1++;
            while (c[i][j] == '*') b1[i][j] = num1, ++j;
        }
    } // 找行连通块

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (c[j][i] == '*') num2++;
            while (c[j][i] == '*') b2[j][i] = num2, ++j;
        }
    } // 找列连通块

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (c[i][j] == '*') head[b1[i][j]].push_back(b2[i][j]);
    // 建图

    for (int i = 1; i <= num1; ++i) {
        memset(vis, 0, sizeof(vis));
        ans += dfs(i);
    }
    // 匈牙利算法

    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：CG__HeavenHealer (赞：0)

# 【题解】 P6062 [USACO05JAN]Muddy Fields G

### 题意

有一个 $n$ 行 $m$ 列的矩形，其中的格子有两种类型，一种是草地，上面不能放木板；另一种是泥地，上面可以放木板。一个木板最长可以覆盖整行或整列，求最少的木板数。

---

### 解法

因为木板在一行或一列上可能不能完全覆盖，所以我们可以把整个图的行、列重新定义一下：在原图中，每一行连续的泥地标记为同一行，列同理，所以我们可以得到这样一张新的图：（以样例为例）

[![WvFyrD.png](https://z3.ax1x.com/2021/07/31/WvFyrD.png)](https://imgtu.com/i/WvFyrD)

这部分可以这样处理：

```cpp
 	for (ri i = 1; i <= n; i++)
        for (ri j = 1; j <= m; j++) {
            if (s[i][j] == '.') continue;
            if (j == 1 || s[i][j - 1] == '.') cntx++;
            a[i][j].x = cntx;
        }
    for (ri j = 1; j <= m; j++)
        for (ri i = 1; i <= n; i++) {
            if (s[i][j] == '.') continue;
            if (i == 1 || s[i - 1][j] == '.') cnty++;
            a[i][j].y = cnty;
        }
// 要注意区分好行和列，不要弄混
```

要求的就是怎样用最少的木板覆盖整张图

我们可以对行和列连边建出一张图，因为行和列无关，所以其内部不会连边，即**建出来的图一定是二分图**。建好的图如图：

[![WvArHe.png](https://z3.ax1x.com/2021/07/31/WvArHe.png)](https://imgtu.com/i/WvArHe)

要令整张图被覆盖，就要让每块泥地都被覆盖。以第一张图 $(1,1)$ 这个点为例：要么由第 $1$ 块竖着的木板覆盖它，要么由第 $1$ 块横着的木板覆盖它。换言之，这个点要么在左部，要么在右部，而且一定要关联一条边。用最小的木板数覆盖所有泥地，其实就等价于**求出一个最小的点集，令每条边都至少有一个端点出现在这个点集中。**

这不就是**二分图最小点覆盖吗**？

而由 Konig 定理可知：**二分图最小点覆盖顶点数等于最大匹配** 

这样，问题就迎刃而解了：把每块泥地的行向列连边，求最大匹配即可

~~匈牙利应该在座都会吧~~

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ri register int
const int N = 1010;
inline int read() {
    ri x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f * x;
}
struct Edge {
    int to, nxt;
} e[N << 1];
int head[N], cnt;
inline void add(int u, int v) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
int match[N];
bool vis[N];
bool dfs(int u) {
    for (ri i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (vis[v]) continue;
        vis[v] = true;
        if (!match[v] || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}
char s[N][N];
struct node {
    int x, y;
} a[N][N];
signed main() {
    int n = read(), m = read(), ans = 0;
    int cntx = 0, cnty = 0;
    for (ri i = 1; i <= n; i++) scanf("%s", s[i] + 1);
    for (ri i = 1; i <= n; i++)
        for (ri j = 1; j <= m; j++) {
            if (s[i][j] == '.') continue;
            if (j == 1 || s[i][j - 1] == '.') cntx++;
            a[i][j].x = cntx;
        }
    for (ri j = 1; j <= m; j++)
        for (ri i = 1; i <= n; i++) {
            if (s[i][j] == '.') continue;
            if (i == 1 || s[i - 1][j] == '.') cnty++;
            a[i][j].y = cnty;
        }
    for (ri i = 1; i <= n; i++)
        for (ri j = 1; j <= m; j++)
            if (s[i][j] == '*') add(a[i][j].x, a[i][j].y);
    // for (ri i = 1; i <= n; i++)
    //     for (ri j = 1; j <= m; j++)
    //         printf("i=%lld,j=%lld:x-%lld,y-%lld\n", i, j, a[i][j].x,
    //         a[i][j].y);
    for (ri i = 1; i <= cntx; i++) {
        memset(vis, false, sizeof(vis));
        ans += dfs(i);
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：Martian148 (赞：0)

# Link
[P6062 [USACO05JAN]Muddy Fields G](https://www.luogu.com.cn/problem/P6062)

# Solve

每块泥地$(i,j)$要么被第$i$行的一块木板横着覆盖，要么被第$j$列的一块竖着覆盖，二者至少选其一，满足最小点覆盖的2要素。

因为不满不能覆盖草地，所以横着的木板只能放在同一行连续的泥地上，竖着同理，我们把这些连续的泥地分别称为"行泥泞块"和"列泥泞块"。

所以我们把"行泥泞块"作为二分图的左端点，"列泥泞块"作为二分图的右端点，对于每块泥地就是它所属的"行泥泞块"和"列泥泞块"之间连边

求出二分图的最小覆盖就是用最少的木板覆盖所有的泥地

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=105,maxm=10005,maxe=20005;
int N,M,a[maxn][maxn],b[maxn][maxn],cnt1,cnt2,ans,match[maxm],vis[maxm];
int lnk[maxm],son[maxe],nxt[maxe],cnt;
char c[maxn][maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
bool DFS(int x){
	for(int j=lnk[x];j;j=nxt[j]){
		if(!vis[son[j]]){
			vis[son[j]]=1;
			if(!match[son[j]]||DFS(match[son[j]])){
				match[son[j]]=x;
				return 1;
			}
		}
	}
	return 0;
}
inline void add_e(int x,int y){son[++cnt]=y;nxt[cnt]=lnk[x];lnk[x]=cnt;}
int main(){
	freopen("P6062.in","r",stdin);
	freopen("P6062.out","w",stdout);
	N=read();M=read();
	for(int i=1;i<=N;i++)scanf("%s",c[i]+1);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++){
			if(c[i][j]=='*')++cnt1;
			while(c[i][j]=='*')a[i][j++]=cnt1;
		}
	for(int j=1;j<=M;j++)
		for(int i=1;i<=N;i++){
			if(c[i][j]=='*')++cnt2;
			while(c[i][j]=='*'){b[i++][j]=cnt2;b[i-1][j]+=cnt1;}
		}
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++){
			if(c[i][j]=='*'){add_e(a[i][j],b[i][j]);add_e(b[i][j],a[i][j]);}
		}
	for(int i=1;i<=cnt1;i++){
		memset(vis,0,sizeof vis);
		ans+=DFS(i);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：JK_LOVER (赞：0)

## 题意
一个 $R\times C$ 的网格图，求最小需要多少个宽度为 $1$ 的矩形完美覆盖，可以重叠。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-p6062)
## 分析
我们发现如果有一个横着的矩形右边仍然有泥地，那么完全可以延长这个矩形。即使这个泥地已经被其他矩形覆盖了，这是不会使答案变劣的。

- 有了上面的分析，我们就可以很轻松的想到一个泥地只能被两种矩形覆盖 $1$：横着的，$2$：竖着的。

- 而横着和竖着的矩形只需要一个就可以了，这个就是标准的二分图模型了，那么根据最大流最小割定理，只要把覆盖到同一方格的两个矩形连边。跑最大流就完成了。

- 小细节：虽然 $R,C\le50$ 但矩形种类可能达到 $R\times C$ 级别的，数组一定要开够。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 101210;
int read(){int x;scanf("%d",&x);return x;}
struct Edge{int to,nxt,flow,cap;}e[N<<1];
int cnt = 1,R,C,S,T,cur[N],head[N],dis[N];
queue<int> Q;
void add(int x,int y,int cap){
	e[++cnt].nxt = head[x];e[cnt].to = y;e[cnt].flow = 0;e[cnt].cap = cap;head[x] = cnt;
	e[++cnt].nxt = head[y];e[cnt].to = x;e[cnt].flow = 0;e[cnt].cap = 0;head[y] = cnt;
}
bool bfs(int s,int t){
	while(!Q.empty()) Q.pop();
	memset(dis,0,sizeof(dis));dis[s] = 1;Q.push(s);
	while(Q.size()){
		int x = Q.front();Q.pop();
		for(int i = head[x];i;i = e[i].nxt){
			if(!dis[e[i].to] && e[i].cap > e[i].flow){
				Q.push(e[i].to);dis[e[i].to] = dis[x] + 1;
				if(e[i].to == t) return true;
			}
		}
	}
	return false;
}
int dfs(int x,int a,int t){
	if(x == t|| a == 0) return a;
	int flow = 0,f;
	for(int i = cur[x];i;i = e[i].nxt){
		int y = e[i].to;
		if(dis[y] == dis[x] + 1 && (f=dfs(y,min(a,e[i].cap-e[i].flow),t))>0)		
		{
			e[i].flow += f;e[i^1].flow -= f;flow += f;a -= f;cur[x] = i;
			if(!a) break; 
		}
	}
	return flow;
}
char ch[55][55];
int col[550][550][2],Colx,Coly,vis[550][510];
int main()
{
	R = read();C = read();
	for(int i = 1;i <= R;i++){
		for(int j = 1;j <= C;j++){
			cin>>ch[i][j];
			if(ch[i][j]=='*' && ch[i-1][j] == '*') 
			col[i][j][1] = col[i-1][j][1];
			else if(ch[i][j]=='*')col[i][j][1] = ++Colx;
			if(ch[i][j]=='*' && ch[i][j-1] == '*') 
			col[i][j][0] = col[i][j-1][0];
			else if(ch[i][j]=='*')col[i][j][0] = ++Coly;
		}
	}
	S = 0;T = Colx+Coly+1;
	for(int i = 1;i <= Colx;i++) add(S,i,1);
	for(int i = 1;i <= Coly;i++) add(i+Colx,T,1);
	for(int i = 1;i <= R;i++){
		for(int j = 1;j <= C;j++){	
			if(ch[i][j]=='.') continue;
			int y = col[i][j][0],x = col[i][j][1];
			if(!vis[x][y]) add(x,y+Colx,1),vis[x][y] = 1;
		}
	}
	int maxflow = 0;
	while(bfs(S,T)){
		for(int i = 0;i < T;i++) cur[i] = head[i];
		maxflow += dfs(S,0x3f3f3f3f,T);
	}
	printf("%d\n",maxflow);
	return 0;
}

```



---

## 作者：Night_Bringer (赞：0)

* [原博客食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14076469.html)

# 题目大意
在一个 $R×C$ 的矩阵中，每个点有两个状态：草地和泥地。你需要在泥地里铺 $1×k$ 木块， $k$ 为任意整数，求最少要多少木块。
# 思路
两个横向木块不会互相干扰，两个竖向木块不会互相干扰，且一个点的覆盖方法只有横向木块覆盖与竖向木块两种覆盖方法，不难想到[二分图的最小点覆盖](https://www.cnblogs.com/C202202chenkelin/p/14070458.html)。

设每个点 $i$ 的竖向木板的编号为 $belong1[i]$ ，横向木板的编号为 $belong2[i]$ ，则这个点可能会被 $belong1[i]$ 与 $belong2[i]$ 任意一个所覆盖，所以将 $belong1[i]$ 与 $belong2[i]$ 连接一条边。

最后在求出最小点覆盖，就是最少需要木板的个数。

# C++代码
```cpp
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
void Quick_Read(int &N) {
	N = 0;
	int op = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')
			op = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		N = (N << 1) + (N << 3) + (c ^ 48);
		c = getchar();
	}
	N *= op;
}
const int MAXN = 5e3 + 5;
const int MAXM = 55;
vector<int> v[MAXN];
int belong1[MAXM][MAXM], belong2[MAXM][MAXM];
char Mp[MAXM][MAXM];
int twin[MAXN];
bool vis[MAXN];
int r, c, n, m;
bool Hungary(int now) {//匈牙利算法
	int SIZ = v[now].size();
	for(int i = 0; i < SIZ; i++) {
		int next = v[now][i];
		if(!vis[next]) {
			vis[next] = true;
			if(!twin[next] || Hungary(twin[next])) {
				twin[next] = now;
				return true;
			}
		}
	}
	return false;
}
int Match() {//匹配
	int res = 0;
	for(int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if(Hungary(i))
			res++;
	}
	return res;//二分图中最小点覆盖就等于最大匹配
}
void Build() {
	n = 1;
	for(int i = 1; i <= r; i++) {//求出横向木板
		bool last = false;
		for(int j = 1; j <= c; j++) {
			if(Mp[i][j] == '*') {
				belong1[i][j] = n;
				last = true;
			}
			else {
				if(last)
					n++;
				last = false;
			}
		}
		if(last)
			n++;
	}
	m = n + 1;
	n--;
	for(int j = 1; j <= c; j++) {//求出竖向模板
		bool last = false;
		for(int i = 1; i <= r; i++) {
			if(Mp[i][j] == '*') {
				belong2[i][j] = m;
				last = true;
			}
			else {
				if(last)
					m++;
				last = false;
			}
		}
		if(last)
			m++;
	}
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
			if(Mp[i][j] == '*')
				v[belong1[i][j]].push_back(belong2[i][j]);//建图
}
void Read() {
	Quick_Read(r);
	Quick_Read(c);
	for(int i = 1; i <= r; i++)
		scanf("%s", Mp[i] + 1);
}
int main() {
	Read();
	Build();
	printf("%d", Match());
	return 0;
}
```

---

## 作者：恶灬心 (赞：0)

本题 在李煜东《算法竞赛进阶指南》第二版·二分图的覆盖与独立集 中有收录。  
也可以参考 xht的二分图学习笔记。 [博客链接](https://www.xht37.com/%e4%ba%8c%e5%88%86%e5%9b%be%e4%b8%8e%e7%bd%91%e7%bb%9c%e6%b5%81-%e5%ad%a6%e4%b9%a0%e7%ac%94%e8%ae%b0/#lwptoc10)

所以对于二分图最小覆盖部分就不赘述了。


------------

首先，在这道题中寻找“2要素”，即每条边有两个端点，二者至少选择一个。  

观察题面，我们对于任意一个泥泞点都可以选择用一个横向或丛向板覆盖。那么很容易就能将两个板作为端点，那么它们连边，就可以构建二分图最小覆盖的模型了。

现在考虑如何计算板。

横向：如果左边的点有板，必定可以覆盖这个点，于是直接覆盖，没有就另开一个覆盖。

纵向：如果上边的点有板，必定可以覆盖这个点，于是直接覆盖，没有就另开一个覆盖。

那么本题完结。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    while(ch!='*'&&ch!='.') ch=getchar();
    return ch=='*'?1:0;
}
const int N = 1e6;
const int M = 52;
int head[N],ver[N],Next[N],tot;
void add(int x,int y) { ver[++tot]=y,Next[tot]=head[x],head[x]=tot; }
int n,m;
int d[M][M],h[M][M],l[M][M],toh,tol;
int vis[N],used[N];
bool dfs(int x)
{
    for(register int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(!vis[y])
        {
            vis[y]=1;
            if(!used[y]||dfs(used[y]))
            {
                used[y]=x; return 1;
            }
        }
    }
    return 0;
}
int main()
{
    scanf("%d %d",&n,&m);
    for(register int i=1;i<=n;i++)
        for(register int j=1;j<=m;j++)
            d[i][j]=read();
    for(register int i=1;i<=n;i++)
        for(register int j=1;j<=m;j++)
            if(d[i][j])
            {
                h[i][j]=(h[i][j-1]?h[i][j-1]:(++toh));
                l[i][j]=(l[i-1][j]?l[i-1][j]:(++tol));
            }
    for(register int i=1;i<=n;i++)
        for(register int j=1;j<=m;j++)
            if(h[i][j]&&l[i][j])
                add(h[i][j],l[i][j]+toh),add(l[i][j]+toh,h[i][j]);
    int ans=0;
    for(register int i=1;i<=toh;i++)
    {
        memset(vis,0,sizeof(vis));
        ans+=dfs(i);
    }
    cout<<ans;
    return 0;
}

```


---

