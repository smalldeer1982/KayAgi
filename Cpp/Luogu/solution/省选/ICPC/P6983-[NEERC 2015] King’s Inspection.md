# [NEERC 2015] King’s Inspection

## 题目描述

国王 Karl 是一位负责且勤勉的统治者。每年他都会在全国各地巡游，以确保所有城市都运转良好。

他的国家有 $n$ 个城市和 $m$ 条道路。为了控制旅行者，每条道路都是单向的，即从城市 $a$ 到城市 $b$ 的道路不能从 $b$ 到 $a$ 通过。

Karl 想要沿着这些道路旅行，他希望从首都出发，恰好访问每个非首都城市一次，并最终回到首都。

作为交通部长，你有责任找到这样一条路线，或者确定这样的路线不存在。

## 说明/提示

时间限制：10 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 6
1 4
4 1
4 2
2 1
3 4
1 3
```

### 输出

```
1 3 4 2 1
```

## 样例 #2

### 输入

```
4 3
1 4
1 4
2 2
```

### 输出

```
There is no route, Karl!
```

# 题解

## 作者：Su_Zipei (赞：5)

首先发现这题要求的是哈密顿回路，然后一看是NPC问题瞬间劝退。。其实是有特点的，对于这道题来说，特点就是合法的图中出度大于2的点不会很多，最多只有$20$个，而对于出度为$1$的点是没必要去跑的，因为知道走上去之后的结果，所以事实上只需要对这二十个点跑一下就行，那么可以把所有的链都缩起来，这样时间复杂度的极限也才$20*2^{20}$，可以通过。

```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e5+10;
struct Edge{
	int to,nxt;
}e[N<<1];
int n,m;
int h[N],idx,nxt[N],d[N];
void Ins(int a,int b){
	e[++idx].to=b;e[idx].nxt=h[a];h[a]=idx;
}
vector<int> vec;
bool vis[N],inq[N];
bool check(){
	memset(inq,0,sizeof(inq));
	for(int i=1,now=1;i<=n;i++,now=nxt[now]){
		if(inq[now])return 0;
		inq[now]=1;
	}
	return 1;
}
void dfs(int u){
	if(u==vec.size()){
		if(check()){
			for(int i=1,now=1;i<=n;i++,now=nxt[now])
				printf("%d ",now);
			printf("1 ");
			exit(0);
		}
		return;
	}
	int now=vec[u];
	for(int i=h[now];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v])continue;
		vis[v]=1;
		nxt[now]=v;
		dfs(u+1);
		vis[v]=0;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		Ins(a,b);d[a]++;
	}
	for(int i=1;i<=n;i++){
		if(d[i]>=2)vec.push_back(i);
		else if(d[i]==0)return puts("There is no route, Karl!"),0;
		else {
			int v=e[h[i]].to;
			if(vis[v])return puts("There is no route, Karl!"),0;
			vis[v]=1;
			nxt[i]=v;
		}
	}
	dfs(0);
	return puts("There is no route, Karl!"),0;
}
```

---

## 作者：RAND_MAX (赞：0)

一看到这个题感觉非常不可做，但是一看数据范围 $m\le n+20$，这说明至多有二十个点有**多于一条**出边。这启发我们进行暴搜。

我们对于每一个出度为一的点记一个后继 $nxt$，随后暴力枚举每一个出度大于一的点的后继并判断是否合法，实现细节不多。不过需注意若是存在出度为零的点需直接判无解，否则容易超时。


```cpp
#include<bits/stdc++.h>
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
#define N 100010
int n,m,vis[N],in[N],vv[N],nxt[N],tot;
vector<int>g[N],v;
void check()
{
	int i;
	for(i=1;i<=n;i++) vis[i]=0;
	i=nxt[1];
	while(i!=1)
	{
		if(vis[i]) return;
		vis[i]=1,i=nxt[i];
	}
	vis[i]=1;
	for(i=1;i<=n;i++) if(!vis[i]) return;
	write(1,' ');
	i=nxt[1];
	while(i!=1)
	{
		write(i,' '),i=nxt[i];
	}
	write(1,' ');
	exit(0);
}
void fzs(int x)
{
	if(x==v.size()) check();
	else
	{
		for(int i:g[v[x]]) 
		{
			if(vv[i]) continue;
			nxt[v[x]]=i,vv[i]=1,fzs(x+1),vv[i]=0;;
		}
	}
}
signed main()
{
	n=R,m=R;
	for(int i=1,x,y;i<=m;i++) x=R,y=R,g[x].push_back(y),in[x]++,in[y]++;
	for(int i=1;i<=n;i++)
	{
		if(!in[i])
		{
			puts("There is no route, Karl!");
			return 0;
		}
		else if(in[i]==1) nxt[i]=g[i][0];
		else v.push_back(i);
	}
	fzs(0);
	puts("There is no route, Karl!");
 	return 0;
}

```

---

## 作者：hexz01 (赞：0)

# 题解 P6983 [NEERC2015] King’s Inspection

~~一道紫题，当场吓懵。~~

## 题意

给定一个 $n$ 个点，$m$ 条边的有向图，求一条恰好经过每个点的一条回路。

## 思考

这道题首先想到 dfs，可是复杂度 $O(n \times m)$ 貌似不太靠谱。

接着观察到数据范围，发现 $m$ 竟然只比 $n$ 大 20，于是考虑从这个地方入手。

因为最难的地方就是怎么处理出度大于 1 的点，也就是下一步有很多选择的点，然而最多只有 20 个点出度大于 1，所以可以分类处理。

首先每个点可以分三种情况：
1. 出度为 0，也就是说到达不了任何点，但是要求的这条回路上任意一个点都有后继，所以无解，输出 ```There is no route, Karl!```。
2. 出度为 1，此时这个点只能走向一个点，没有其他选择，所以走这条边。
3. 出度大于 1，此时把这个点加入 dfs 点集，进行 dfs。

dfs 时就枚举出边，最后跳 suf（后继）验证就好了。

## Code:
``` cpp
#include <iostream>
using namespace std;
const int N=1e5+7, M=N+20;
int n, m;
int head[N], nxt[M], to[M], out[N], tot=0;//邻接表和出度数组
int tool[N], tot2=0, suf[N];//tool:dfs数组   suf:后继数组，用来找路径
bool flag[N], vis[N];
void add(int u, int v){
	tot++;
	nxt[tot]=head[u];
	head[u]=tot;
	to[tot]=v;
	out[u]++;
}
bool check(){
	for(int i=1;i<=n;i++)
		flag[i]=0;
	int i;
	for(i=1;suf[i]!=1;i=suf[i]){
		if(flag[i])
			return 0;
		flag[i]=1;
	}
	flag[i]=1;
	for(i=1;i<=n;i++)
		if(!flag[i])
			return 0;
	return 1;
}
bool dfs(int x){
	if(x==tot2+1){
		if(check()){
			int i;
			for(i=1;suf[i]!=1;i=suf[i])
				cout<<i<<" ";
			cout<<i<<" "<<1<<endl;
			return 1;
		}else
			return 0;
	}
	for(int i=head[tool[x]];i;i=nxt[i]){
		if(vis[to[i]])
			continue;
		vis[to[i]]=1;
		suf[tool[x]]=to[i];
		if(dfs(x+1))
			return 1;
		suf[tool[x]]=0;
		vis[to[i]]=0;
	}
	return 0;
}
int main(){
	cin>>n>>m;
	while(m--){
		int u, v;
		cin>>u>>v;
		add(u, v);
	}
	for(int i=1;i<=n;i++){
		if(out[i]==0){
			cout<<"There is no route, Karl!"<<endl;
			return 0;
		}else if(out[i]==1){
			int v=to[head[i]];
			if(vis[v]){
				cout<<"There is no route, Karl!"<<endl;
				return 0;
			}
			vis[v]=1;
			suf[i]=v;//选择后继
		}else{
			tool[++tot2]=i;
		}
	}
	if(!dfs(1))
		cout<<"There is no route, Karl!"<<endl;
	return 0;
}
```

---

