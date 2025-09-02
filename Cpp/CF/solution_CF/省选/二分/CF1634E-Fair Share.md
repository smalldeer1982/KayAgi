# Fair Share

## 题目描述

Even a cat has things it can do that AI cannot.

— Fei-Fei Li



You are given $ m $ arrays of positive integers. Each array is of even length.

You need to split all these integers into two equal multisets $ L $ and $ R $ , that is, each element of each array should go into one of two multisets (but not both). Additionally, for each of the $ m $ arrays, exactly half of its elements should go into $ L $ , and the rest should go into $ R $ .

Give an example of such a division or determine that no such division exists.

## 说明/提示

In the first array, we add the first element to $ R $ and the second to $ L $ . Now $ L = \{2\} $ , and $ R = \{1\} $ .

In the second array, we add the first and third elements to $ L $ and the rest to $ R $ . Now $ L = \{1, 2, 3\} $ and $ R = \{1, 2, 3\} $ .

In the third array, we add elements 2, 3, and 6 to $ L $ , and others — to $ R $ . As a result, $ L = R = \{1, 1, 2, 2, 3, 3\} $ .

## 样例 #1

### 输入

```
3
2
1 2
4
1 2 3 3
6
1 1 2 2 3 3```

### 输出

```
YES
RL
LRLR
RLLRRL```

# 题解

## 作者：dingcx (赞：23)

给出一篇和官方题解不同的题解。

## 思路

### 铺垫

在编造样例试验的过程中，很容易有这样的想法：如果之前把一个数放在了 $L$ 中，就在下一次遇到这个数时把它放在 $R$ 中；如果一个数组里有很多个数已经放在 $L$ 了，剩下的数就尽量放在 $R$ 中。

由此可能生出各种贪心做法，不过都是错的。以下样例可能会卡掉很多人的贪心：

```
1 2
3 4
5 6
7 8
1 3 5 7
2 4 6 8
```

多进行几次尝试可能还能得到一些信息，比如确定一个数放在 $L$ 后，就会跟着确定一些数放进哪个集合，然后剩下的数又可以随意放，接着确定一个数，又能确定一些数……这似乎和连通块很像。

结合以上的思考，就能~~灵光乍现~~得出一种奇妙的思路了。

### 解法

把每个数想象成一个点，考虑如何**建边**，使得只要连边的两个点不在同一个集合内，这种划分就成立。

那么如何建边呢？这既需要考虑同样的数之间的关系，也需要考虑一个序列中的数之间的关系。最终建出来的图还需要每个连通块都是一个环（也就是说每个点的度数都为 $2$），并且每个环都有偶数个点。

于是想到，第 $1,2$ 个，第 $3,4$ 个等**相同的数之间连一条边**，序列中第 $1,2$ 个，第 $3,4$ 个等**相邻的数之间连一条边**。

连完后的样子大概是这样（担心没讲清楚）（红色的边是连的边）：

![](https://cdn.luogu.com.cn/upload/image_hosting/8kqd1krq.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/0yscyv1g.png)

（第 $1$ 个出现的 $1$ 和第 $2$ 个出现的 $1$ 连边，第 $3$ 个出现的 $1$ 和第 $4$ 个出现的 $1$ 连边……每个序列第 $1$ 个数和第 $2$ 个数连边，第 $3$ 个数和第 $4$ 个数连边……）

那么现在需要证明这样建图满足所有要求。

首先这显然能满足两个集合相等，且每个集合分给 $L,R$ 的个数相同。不过为什么这样每个点的度数都为 $2$，且每个环都是偶环呢？如果把连接同一个数的边看作“纵边”，连接一个序列中两个数的边看作“横边”，那么一个点一定连出去一条纵边和一条横边，所以度数为 $2$，而且在这个环内，这两种边交替出现，所以一定会有偶数条边。

于是，在建边之后，对每个环先确定一个点加入的集合，然后遍历整个环让每个点进入的集合与上一个不同即可。

然后在建边的时候需要存每个数上一个点的位置，不过 $a_i \le 10^9$，所以需要离散化或用 ```map```（个人认为 ```map``` 更好写）。

最后说一下什么情况下无解：无解当且仅当有一个点没有连“纵边”，其实也就是有一个数出现了奇数次。

时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include<cstdio>
#include<map>
#include<vector>
using namespace std;
const int MAXN=2e5+10;
map<int,int> mp; //记录每个数上一个点的位置
vector<int> e[MAXN<<1]; //边
bool vis[MAXN];
int n[MAXN],ans[MAXN];
int read(){ //快读
	int num=0,sign=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num*sign;
}
void dfs(int u,int num){ //对一个环进行划分，num 表示这个点进入哪个集合
	ans[u]=num,vis[u]=1; //记录答案、来过
	if(!vis[e[u][0]]) dfs(e[u][0],num^1);
	else if(!vis[e[u][1]]) dfs(e[u][1],num^1);
}
int main(){
	int m=read(),tot=0;
	for(int i=1;i<=m;i++){
		n[i]=read();
		for(int j=1;j<=n[i];j++){
			tot++;
			int x=read();
			if(j%2==0) e[tot].push_back(tot-1),
				e[tot-1].push_back(tot); //序列中的第偶数个点，与它左边的点连边
			if(mp[x]>0) e[tot].push_back(mp[x]),
				e[mp[x]].push_back(tot),mp.erase(x); //第偶数次出现这个数，与上一次出现这个数的位置连边
			else mp[x]=tot; //第奇数次出现这个数，记录位置，等待连边
		}
	}
	if(mp.size()){ //判断无解
		printf("NO\n");
		return 0;
	}
	for(int i=1;i<=tot;i++)
		if(!vis[i]) dfs(i,0); //对每个环划分
	int tott=0;
	printf("YES\n");
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n[i];j++)
			tott++,printf("%c",ans[tott]?'L':'R');
		printf("\n");
	}
	return 0; //华丽结束
}
```

看完不要忘记点赞~

---

## 作者：I_am_Accepted (赞：9)

## Preface

我考场上怎么也没想到这是一道图论题 qwq。

Algorithm(1) 是官方做法，但本人认为 Algorithm(2) 更加巧妙且好写。

## Algorithm(1)

### Analysis

如果有的值出现了奇数次，那显然是不行的。否则，我们下面构造一种分 $\text{L,R}$ 的方案来说明一定可行。

将数组和每种数值都看作图中的点，每次数值 $x$ 在第 $y$ 个数组出现，在 $x,y$ 分别对应的点之间连一条无向边（边上记得存位置，以便最终答案的输出）。这样构成的无向图（不一定简单，不一定连通），每个点的度都是偶数，所以每个连通分量必然存在一条欧拉回路。

欧拉回路的[知识点](https://baike.baidu.com/item/%E6%AC%A7%E6%8B%89%E8%B7%AF%E5%BE%84/23162222)和[算法](https://www.luogu.com.cn/problem/P7771)不再赘述。

将每条边按欧拉回路的方向定向。

这样，每个代表数值的点和代表数组的点的出入度相等了。我们只需要将 数组 $\to$ 数值 的那些位置放入 $\text{L}$，将 数值 $\to$ 数组 的那些位置放入 $\text{R}$ 即可。

### Detail

最方便的是前向星，因为要存反向边是否被遍历过。

### Code

[Link](https://codeforces.com/contest/1634/submission/145658088)

## Algorithm(2)

### Analysis

当然，通往广场的路不止一条。

有解的条件仍然是：每种值都出现偶数次。

我们将数组中的每一个数看作点。边有两种——值边 和 位边。

值边只连接两个值相同的点：想象着将每种值相同的位置存入数组 $\{p\}$（长度必定为偶数），将 $p_{2i-1},p_{2i}$ 之间连边。

![](https://cdn.luogu.com.cn/upload/image_hosting/c0wkixfd.png)

位边只连接在数组中位置相邻的两个点：设这个数组为 $\{a\}$（长度必定为偶数），将 $a_{2i-1},a_{2i}$ 之间连边。

![](https://cdn.luogu.com.cn/upload/image_hosting/a82swrj6.png)

发现最后这是一张二分图，因为不存在奇环。因为如果有奇环，必然有两个值边 或 两个位边 相邻（有公共端点）。而每个点有且仅有 一条值边 和 一条位边 连出去，矛盾，原命题得证。

这样，我们将这个二分图黑白染色，染黑的去 $\text{L}$，染白的去 $\text{R}$ 即可。

### Code

[Link](https://codeforces.com/contest/1634/submission/145800932)

---

## 作者：ethan0328 (赞：2)

## 思路

其实这是一道图论题。

考虑哪些点不能放在同一集合中，在它们之间连一条边，最后二分图染色判求出两个集合。

对于每一种数，肯定一半个数放在 $L$ 中，另一半放在 $R$ 中。所以我们把这种数第一次出现位置与第二次出现位置连线，把第三次出现位置与第四次出现位置连线，等等。

对于每个数组，因为有一半放入 $L$，一半放入 $R$。所以也把数组相邻两个数相连边。

## 注意事项
- $m$ 个数组直接存会炸掉。
- 数据要先离散化。

## 代码

```cpp
#include<bits/stdc++.h>
#define fir first
#define sec second
#define mkp(a,b) make_pair(a,b)
using namespace std;
const int N=2e5+10,M=1e6+10;
struct edge
{
	pair<int,int> to;
	int next;
};
int m,ind,len,n[N],b[M];
pair<int,int> lst[M];
map<pair<int,int>,int> col,head;
vector<int> a[N];
edge e[M];
void add(pair<int,int> x,pair<int,int> y)
{
	e[++len].to=y;
	e[len].next=head[x];
	head[x]=len;
}
void dfs(pair<int,int> x,int color)
{
	pair<int,int> y;
	col[x]=color;
	for(int i=head[x];i;i=e[i].next)
	{
		y=e[i].to;
		if(col[y]!=0)
		{
			continue;
		}
		dfs(y,3-color);
	}
}
int main()
{
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>n[i];
		for(int j=1;j<=n[i];j++)
		{
			cin>>b[++ind];
			a[i].push_back(b[ind]);
		}
	}
	sort(b+1,b+ind+1);
	ind=unique(b+1,b+ind+1)-b-1;
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<a[i].size();j++)
		{
			a[i][j]=upper_bound(b+1,b+1+ind,a[i][j])-b-1;
		}
	}
	for(int i=1;i<=ind;i++)
	{
		lst[i]=mkp(0,0);
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<a[i].size();j++)
		{
			if(lst[a[i][j]]!=mkp(0,0))
			{
				add(lst[a[i][j]],mkp(i,j+1));
				add(mkp(i,j+1),lst[a[i][j]]);
				lst[a[i][j]]=mkp(0,0);
			}else
			{
				lst[a[i][j]]=mkp(i,j+1);
			}
		}
	}
	for(int i=1;i<=ind;i++)
	{
		if(lst[i]!=mkp(0,0))
		{
			cout<<"NO";
			return 0;
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n[i];j++)
		{
			if(j&1)
			{
				add(mkp(i,j),mkp(i,j+1));
				add(mkp(i,j+1),mkp(i,j));
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n[i];j++)
		{
			if(col[mkp(i,j)]==0)
			{
				dfs(mkp(i,j),1);
			}
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n[i];j++)
		{
			if(col[mkp(i,j)]==1)
			{
				cout<<"L";
			}else
			{
				cout<<"R";
			}
		}
		cout<<endl;
	}
}
```


---

## 作者：Ezis (赞：2)

**题意：**

有 $m$ 个数组，每个数组长度为 $n_i$。
要在每组间恰好划分一半进可重集 $L$，剩下的进 $R$。
要求判断能否找出一组划分方式，使 $L$ 和 $R$ 相同。

**思路：**

题目要求最终的 $L$，$R$ 相同，考虑转化成数据中的一些互相对立的关系，从而想到建图后黑白染色。

容易发现，只有所有数都出现了偶数次才有解，于是可以先把 No 给判掉。

考虑按如下方式建图：
定义“一组”表示一个数组中相邻两元素。

1. 在两个相邻的，值相同的数之间连边。
2. 在每一组之间连边。

可知若两数之间有边，则它们所对应的组也一定联通。

所以在最终的图中，不会出现长度为奇数的环，即它是一个二分图。

这样再黑白染色一下就可以了。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mk(a,b) make_pair(a,b)
const int maxn=400005;
int head[maxn],mx,tim,edgenum,m,color[maxn],n[maxn],b[maxn],d[maxn],cnt[maxn];
map<pair<int,int>,int>mat;
vector<pair<int,int> >c[maxn];
vector<int>a[maxn];
struct node{
	int to,nxt;
}edge[maxn];
void add(int u,int v){
	edgenum++;
	edge[edgenum].to=v;
	edge[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int u,int col){
	color[u]=col;
	for(int e=head[u];e;e=edge[e].nxt){
		int v=edge[e].to;
		if(color[v]) continue;
		dfs(v,(col==1?2:1));
	}
}
int main(){
	scanf("%d",&m);
	int tot=0;
	for(int i=1;i<=m;i++){
		scanf("%d",&n[i]);
		for(int j=1;j<=n[i];j++)
			scanf("%d",&b[++tot]),a[i].push_back(b[tot]);
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=m;i++)
		for(int j=0;j<a[i].size();j++)
			a[i][j]=lower_bound(b+1,b+tot+1,a[i][j])-b;
	tot=0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n[i];j++)
			mat[mk(i,j)]=++tim;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n[i];j++){
			if(j%2==0){
				add(mat[mk(i,j-1)],mat[mk(i,j)]);
				add(mat[mk(i,j)],mat[mk(i,j-1)]);
			}
			cnt[a[i][j-1]]++;
			c[a[i][j-1]].push_back(mk(i,j));
			d[++mx]=a[i][j-1];
		}
	}
	for(int i=1;i<=mx;i++) 
		if(cnt[d[i]]%2!=0){
			printf("NO");
			return 0;
		}
	for(int i=1;i<=mx;i++)
		for(int j=0;j<c[i].size();j++){
			if(j%2==1){
				add(mat[c[i][j-1]],mat[c[i][j]]);
				add(mat[c[i][j]],mat[c[i][j-1]]);
			}
		}
	for(int i=1;i<=tim;i++)
		if(!color[i]) dfs(i,1);
	printf("YES\n");
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n[i];j++){
			int id=mat[mk(i,j)];
			if(color[id]==1) printf("L");
			else printf("R");
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2400}$
---
### 解题思路：

不是很简单的图论构造。

题目的限制有两个，一个是每一个数组中必须一半在左边一半在右边，另一个是左右两边的各个数的数量一样。

如果出现某一个数的数量为奇数，那么一定不可能有合法的构造。反之一定有方案构造出解。

考虑将左右两边数的数量一样转化为每两个连续的相同的数不在同一个集合中。类似地，将一半在左一半在右的条件转换成每两个数中一定有一个在左边一个在右边。

然后将所有的不能放在一个集合的数连上一条边，如果连成后的图是一个二分图，那么跑一个二分图黑白染色就能得出答案了。

---
然后关键问题就是证明这个转化后的图是一个二分图了。

对于每一个数，它会链接，且仅会链接 $2$ 条边，一条边由两个相邻的位置形成，称为位边，另一条则是由于相同的数值，称为值边（如果有数值没有连边，说明某一个数出现了奇数次，直接忽略。）。

二分图的充分必要条件是没有奇环，假设出现了一个奇环，则说明至少有一个点连接了两条位边或者两条值边，这与之前的条件矛盾，故原命题不成立，也就是一定是二分图。

---
### 代码：
```cpp
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=400005;
map <int,int> mp;
int head[MAXN],nxt[MAXN],to[MAXN],n,m[MAXN],num[MAXN],cnt,x,tot,v[MAXN];
void add(int x,int y){nxt[++cnt]=head[x];head[x]=cnt;to[cnt]=y;}
void dfs(int now,int col){
	v[now]=col;
	if(col==1)col=2;
	else col=1;
	for(int i=head[now];i;i=nxt[i])
	if(v[to[i]]==0)dfs(to[i],col);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&m[i]);
		for(int j=1;j<=m[i];j++){
			scanf("%d",&num[++tot]);
			if((j&1)==0){
				add(tot,tot-1);
				add(tot-1,tot);
			}
			if(mp[num[tot]]==0)mp[num[tot]]=tot;
			else{
				add(mp[num[tot]],tot);
				add(tot,mp[num[tot]]);
				mp[num[tot]]=0;
			}
		}
	}
	for(int i=1;i<=tot;i++){
		if(mp[num[i]]!=0){
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	for(int i=1;i<=tot;i++)
	if(v[i]==0)dfs(i,1);
	tot=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m[i];j++){
			if(v[++tot]==1)printf("L");
			else printf("R");
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Nightingale_OI (赞：1)

## CF1634E Fair Share

### 大意

给定 $ m $ 个数组，第 $ i $ 个数组 $ a_i $ 长度为 $ n_i $ ，保证是偶数。

需要从每个数组里取一半的数放在可重集 $ L $ 中，另一半放在可重集 $ R $ 中。

求使得最终 $ L = R $ 的一种方案或确定不存在方案。

### 思路

首先，加两个强条件：

1. 数组中第 $ 2i - 1 $ 个元素和第 $ 2i $ 个元素不在一个集合中。

2. 第 $ 2i - 1 $ 次出现的数（整体上看）和第 $ 2i $ 次出现的数不在一个集合中。

把不在一个集合中的关系当成一条边，那么当且仅当全图只存在偶环时存在答案。

称第 $ 1 $ 种边为邻边，第 $ 2 $ 种边为延展边。

发现如果存在环，一定是邻边和延展边交替，则一定是偶环。

由于每个点都有邻边，若一点不在环内，则其没有延展边，所以该值出现奇数次。

有值出现奇数次是一定无解的。

综上，该强条件存在解时原条件一定存在，不存在时原条件一定不存在。

构造答案时使连边的两点不在一个集合中即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,p,n) for(register int i=p;i<=n;++i)
#define g(i,p,n) for(register int i=p;i>=n;--i)
int n,m,s,l;
int a[202020];
int v[202020];
map<int,int>mp;
int ans[202020];
vector<int>q[404040];
void dfs(int x,int t){
	v[x]=1;
	ans[x]=t;
	if(!v[q[x][0]])dfs(q[x][0],t^1);
	else if(!v[q[x][1]])dfs(q[x][1],t^1);
}
int main(){
	cin>>n;
	f(i,1,n){
		scanf("%d",&a[i]);
		f(j,1,a[i]){
			scanf("%d",&s);
			++m;
			if(!(j&1)){
				q[m].push_back(m-1),
				q[m-1].push_back(m);
			}
			if(mp[s]){
				q[m].push_back(mp[s]);
				q[mp[s]].push_back(m);
				mp.erase(s);
			}else{
				mp[s]=m;
			}
		}
	}
	if(mp.size()){
		printf("NO\n");
		return 0;
	}
	f(i,1,m)if(!v[i])dfs(i,0);
	printf("YES\n");
	f(i,1,n)f(j,1,a[i]){
		if(ans[++l])putchar('L');
		else putchar('R');
		if(j==a[i])putchar('\n');
	}
	return 0;
}
```

---

## 作者：enucai (赞：1)

## Preface

赛后参考了@[ZJ_yiran](https://www.luogu.com.cn/user/371898) 的解法，个人认为甚是巧妙，但是我不会证，所以只留做法（即 Analysis1），证明留白。

## Analysis1

已知，如果有一种数的个数是奇数个，则答案为 `NO`。

否则答案为 `YES`。让**每个数组**中第 $2i$ 与 $2i+1$ 个数放在不同的集合中，让**每种数**的第 $2i$ 与 $2i+1$ 个放在不同集合中。构造答案即可。

构造答案只需建一张 以每个位置为点 的图即可，最后让图上相邻的点染不同颜色。

[Codeforces Status](https://codeforces.com/contest/1634/submission/145550137)

## Analysis

以 **数** 与 **数组** 分别作为点，以数与数组的关系作为边（即：一种数 $x$ 在某数组 $i$ 中出现了 $k$ 次，则在 数的点 $x$ 与 数组的点 $i$ 之间连 $k$ 条边）。

如果有**任何一个**数出现了奇数次，则答案为 `NO`，很好理解，因为两边的可重集合不可能相等了。

否则每个作为数的点的度为**偶数**，每个作为数组的点的度也为**偶数**。现在图是无向的。接下来我们要将无向图变为有向图。

由于每个点的度都是偶数，所以一定能做到让有向图中每个点的**入度** $=$ **出度**，就成了一个**有向欧拉回路**。让每条由 数组 指向 数 的边的**终点的数**放入左边集合，每条由 数 指向 数组 的边的**起点的数**放入右边集合。DFS 构造答案即可。

写代码时注意，因为每条边都只会**经过一次**，所以走一条边之间把这条边**弹掉**，用 $vis$ 数组标记会 TLE。

[Codeforces Status](https://codeforces.com/contest/1634/submission/145655627)

---

## 作者：lfxxx (赞：0)

首先如果一种数出现次数为奇数一定无解。

否则由于是划分为两个集合，我们考虑加一些形如 $x,y$ 不能处于同一集合中的限制，使得 $x,y$ 连边后构成二分图再染色构造方案。

首先对于一个数组中的数，我们两两配对，每对之间连边。

对于相同颜色的数，还是两两配对，每对之间连边。

我们发现总共有两类边，并且同一类边之间点集两两不交，因此任意一个环上的边一定是两类边交替，故一定是偶环。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int tot;
vector<int> id[maxn];
vector<int> col[maxn];
char color[maxn];
vector<int> E[maxn];
void dfs(int u,int ty){
	color[u]=(ty==0?'L':'R');
	for(int v:E[u]){
		if(color[v]==0) dfs(v,ty^1);
	}
}
int m,n[maxn];
map<int,int> lsh;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>n[i];
		for(int j=1;j<=n[i];j++){
			tot++;
			int c;
			cin>>c;
			if(lsh[c]==0) lsh[c]=lsh.size()+1;
			c=lsh[c];
			col[c].push_back(tot);
			id[i].push_back(tot);
		}
	}
	for(int i=1;i<=tot;i++){
		if(col[i].size()%2!=0){
			cout<<"NO\n";
			return 0;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=m;i++){
		for(int j=0;j<n[i];j+=2) E[id[i][j]].push_back(id[i][j+1]),E[id[i][j+1]].push_back(id[i][j]);
	}
	for(int i=1;i<=tot;i++){
		for(int j=0;j<col[i].size();j+=2) E[col[i][j]].push_back(col[i][j+1]),E[col[i][j+1]].push_back(col[i][j]);
	}
	for(int i=1;i<=tot;i++){
		if(color[i]==0) dfs(i,0);
	}	
	for(int i=1;i<=m;i++){
		for(int j=0;j<n[i];j++) cout<<color[id[i][j]];
		cout<<'\n';
	}
	return 0;
}
 
```

---

