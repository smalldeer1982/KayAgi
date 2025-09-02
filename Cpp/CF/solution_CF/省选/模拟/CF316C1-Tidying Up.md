# Tidying Up

## 题目描述

Smart Beaver is careful about his appearance and pays special attention to shoes so he has a huge number of pairs of shoes from the most famous brands of the forest. He's trying to handle his shoes carefully so that each pair stood side by side. But by the end of the week because of his very active lifestyle in his dressing room becomes a mess.

Smart Beaver from ABBYY is not only the brightest beaver in the area, but he also is the most domestically oriented. For example, on Mondays the Smart Beaver cleans everything in his home.

It's Monday morning. Smart Beaver does not want to spend the whole day cleaning, besides, there is much in to do and it’s the gym day, so he wants to clean up as soon as possible. Now the floors are washed, the dust is wiped off — it’s time to clean up in the dressing room. But as soon as the Smart Beaver entered the dressing room, all plans for the day were suddenly destroyed: chaos reigned there and it seemed impossible to handle, even in a week. Give our hero some hope: tell him what is the minimum number of shoes need to change the position to make the dressing room neat.

The dressing room is rectangular and is divided into $ n×m $ equal squares, each square contains exactly one shoe. Each pair of shoes has a unique number that is integer from $ 1 $ to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316C1/62bb55bec1337f59eb380936fd7dc7362196cf87.png), more formally, a square with coordinates $ (i,j) $ contains an integer number of the pair which is lying on it. The Smart Beaver believes that the dressing room is neat only when each pair of sneakers lies together. We assume that the pair of sneakers in squares $ (i_{1},j_{1}) $ and $ (i_{2},j_{2}) $ lies together if $ |i_{1}-i_{2}|+|j_{1}-j_{2}|=1 $ .

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316C1/2823182c4be943059776014a228f872fe4a1c1ae.png) The second sample.

## 样例 #1

### 输入

```
2 3
1 1 2
2 3 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 4
1 3 2 6
2 1 5 6
4 4 5 3
```

### 输出

```
4
```

# 题解

## 作者：yuzhechuan (赞：3)

比较套路但又有点意思的二分图带权匹配题

---

### 题解：

如果去考虑哪些位置匹配哪些颜色本题是很难做下去的

所以考虑转换思路

设点$(i,j)$为奇点假如$i+j$为奇数，否则为偶点

容易想象出来，所有鞋子按规则摆完后肯定都可以被抽象成一个个类似多米诺骨牌的$1\times 2$的矩形，然后我们发现一个矩形正好覆盖一个奇点一个偶点

将矩形转化成匹配关系，而是否原先就已相同转化成匹配代价

将每个奇点向自己的四周连边，就构成了一个二分图

用费用流跑一遍最小匹配就好了

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
#ifdef ONLINE_JUDGE
#define getchar gc
inline char gc(){
	static char buf[1<<16],*p1=buf,*p2=buf;
	if(p1==p2){
		p2=(p1=buf)+fread(buf,1,1<<16,stdin);
		if(p2==p1) return EOF;
	}
	return *p1++;
}
#endif
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

const int N=6405,M=5e5+5,P=85;
int en=1,h[N],dis[N],mc,mf,n,m,a[P][P],id[P][P],idn;
bool v[N];

struct edge{
	int n,v,f,w;
}e[M<<1];

struct fafafa{
	int fa,id;
}pre[N];

void add(int x,int y,int f,int w){
	e[++en]=(edge){h[x],y,f,w};
	h[x]=en;
}

bool spfa(int s,int t){
	memset(v,0,sizeof v);
	memset(pre,0,sizeof pre);
	memset(dis,0x3f,sizeof dis);
	queue<int> q;
	q.push(s);
	v[s]=1;
	dis[s]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=h[x];i;i=e[i].n){
			int y=e[i].v;
			if(e[i].f&&dis[x]+e[i].w<dis[y]){
				dis[y]=dis[x]+e[i].w;
				pre[y]=(fafafa){x,i};
				if(!v[y]){
					v[y]=1;
					q.push(y);
				}
			}
		}
		v[x]=0;
	}
	return dis[t]^0x3f3f3f3f;
}

void mcmf(int s,int t){
	while(spfa(s,t)){
		int flow=INT_MAX;
		for(int i=t;i^s;i=pre[i].fa)
			flow=min(flow,e[pre[i].id].f);
		for(int i=t;i^s;i=pre[i].fa){
			e[pre[i].id].f-=flow;
			e[pre[i].id^1].f+=flow;
		}
		mf+=flow;
		mc+=flow*dis[t];
	}
}

void exadd(int x,int y,int f,int w){
	add(x,y,f,w);
	add(y,x,0,-w);
}
//以上是模板
signed main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) id[i][j]=++idn,read(a[i][j]); //每个点的编号
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(i+j&1){ //奇点
				exadd(0,id[i][j],1,0);
				if(id[i-1][j]) exadd(id[i][j],id[i-1][j],1,a[i][j]!=a[i-1][j]); //向四周连边
				if(id[i+1][j]) exadd(id[i][j],id[i+1][j],1,a[i][j]!=a[i+1][j]);
				if(id[i][j-1]) exadd(id[i][j],id[i][j-1],1,a[i][j]!=a[i][j-1]);
				if(id[i][j+1]) exadd(id[i][j],id[i][j+1],1,a[i][j]!=a[i][j+1]);
			}
			else exadd(id[i][j],idn+1,1,0); //偶点
		}
	mcmf(0,idn+1);
	write(mc);
}
```

---

## 作者：AC_love (赞：0)

挺有意思的一道题。

很多人容易陷入这样一个误区：认为本题是最小割，把一只鞋子向它匹配的鞋子周围的格子连边。然后发现这样做怎么都做不出来，寄了。

本题要求一个最小值，但是最小割没法做，于是考虑最小费用最大流。

我们希望每个格子周围都有一个点与它匹配，那么我们可以认为：每个格子都应该向汇点流 $1$ 的流量。对方格进行黑白染色，我们从源点向每个黑点连边，再从每个白点向汇点连边，容量都为 $1$，然后每个黑点向相邻的四个点连边，容量为 $1$。如果两个点颜色相同，则费用为 $0$，否则为 $1$。然后在图上跑最小费用最大流，答案为最小费用。

这样做为什么是对的呢？

注意到：任何一种方案都可以转化为用 $1 \times 2$ 的多米诺骨牌对矩阵进行密铺的方案。方案的答案等于两个格子颜色不同的骨牌数。在跑最小费用最大流时，会尽可能匹配最多的相邻颜色相同的骨牌，那么就可以最小化两个格子颜色不同的骨牌数，也就能最小化调整次数。

---

