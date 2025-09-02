# [USACO4.1] 篱笆回路Fence Loops

## 题目描述

农夫布朗的牧场上的篱笆已经失去控制了。它们分成了1~200英尺长的线段。只有在线段的端点处才能连接两个线段，有时给定的一个端点上会有两个以上的篱笆。结果篱笆形成了一张网分割了布朗的牧场。布朗想将牧场恢复原样，出于这个考虑，他首先得知道牧场上哪一块区域的周长最小。 布朗将他的每段篱笆从1到N进行了标号（N=线段的总数）。他知道每段篱笆有如下属性：

该段篱笆的长度

该段篱笆的一端所连接的另一段篱笆的标号

该段篱笆的另一端所连接的另一段篱笆的标号

幸运的是，没有篱笆连接它自身。对于一组有关篱笆如何分割牧场的数据，写一个程序来计算出所有分割出的区域中最小的周长。

例如，标号1~10的篱笆由下图的形式组成（下面的数字是篱笆的标号）：

```cpp
           1
   +---------------+
   |\             /|
  2| \7          / |
   |  \         /  |
   +---+       /   |6
   | 8  \     /10  |
  3|     \9  /     |
   |      \ /      |
   +-------+-------+
       4       5
```    
上图中周长最小的区域是由2，7，8号篱笆形成的。


## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 4.1


## 样例 #1

### 输入

```
10
1 16 2 2
2 7
10 6
2 3 2 2
1 7
8 3
3 3 2 1
8 2
4
4 8 1 3
3
9 10 5
5 8 3 1
9 10 4
6
6 6 1 2 
5 
1 10
7 5 2 2 
1 2
8 9
8 4 2 2
2 3
7 9
9 5 2 3
7 8
4 5 10
10 10 2 3
1 6
4 9 5```

### 输出

```
12```

# 题解

## 作者：ivorLin (赞：19)

思考这么一个问题：通过并查集建图非常麻烦。

那么，我们能不能偷懒，把边看成点呢？

应该可以。

从这种方向走下去，我们就要把边权看成点权，之后floyd最小环。

这样的话，（边改点后的）两点间的最短路就是两点间经过的点权和的最小值。

如何解决边界？

**容斥原理。**把端点点权加上，合并时把连上的中间端点的权减掉一次。
~~（脱水缩合）~~

还有一个细节：

![区别](https://cdn.luogu.com.cn/upload/pic/25554.png)

//黑色为原图，红色为边改点后的图。

需要判断一下三边是否交于一点，解决方法详见代码。

这种方式时间复杂度$O(n^3)$,优点是代码复杂度非常低。

放代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=123,inf=0x3f3f3f3f;
int n,len[N]/*新图点权*/,minc=inf/*最小环*/,dist[N][N],g[N][N],rec[N];
bool f[N][N]/*邻接矩阵*/,jg[N][N][N];/*判断三边是否交于一点*/

int main(){
	scanf("%d",&n);
	#define jj(x,y,z) jg[rec[x]][rec[y]][rec[z]]
	for(int inp,ns[3],s,i=1;i<=n;i++){
		scanf("%d",&s);
		scanf("%d%d%d",&len[s],&ns[1],&ns[2]);
		rec[0]=s;
		for(int h=1;h<=2;h++){
			for(int j=1;j<=ns[h];j++){
				scanf("%d",&inp);
				f[s][inp]=f[inp][s]=true;
				rec[j]=inp;//记录边交于一点的编号
				for(int k=1;k<j;k++){
					for(int l=0;l<k;l++){
						jj(j,k,l)=jj(j,l,k)=jj(l,k,j)=jj(l,j,k)=jj(k,l,j)=jj(k,j,l)=true;
					}
				}
			}
		}
	}
	memset(dist,0x3f,sizeof dist);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(f[i][j])dist[i][j]=g[i][j]=len[i]+len[j];
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<k;i++){
			if(f[i][k]){
				for(int j=i+1;j<k;j++){
					if(f[k][j]&&!jg[i][j][k]){
						minc=min(minc,dist[i][j]+g[i][k]+g[k][j]-len[k]-len[i]-len[j]);
					}
				}
			}		
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]-len[k]);
			}
		}
	}
	printf("%d\n",minc);
	return 0;
}
```

---

## 作者：juicyyou (赞：17)

# P2738 \[USACO4.1]篱笆回路Fence Loops

这个题的难点主要在于建图, 只要图建好了, 找一下最小环就好。所以我们主要考虑怎么建图。

注意到这题的输入是按边来输入的, 所以我们可以先假定编号为 $ i $ 一条边的两个端点是是 $2i - 1$ 和 $2i$ 并且规定 $2i - 1$ 是其输入时的第一个端点。那么我们就分别存一下两个端点与哪些边相交, 然后枚举 $i$ 和 $j$, 判断 $i$ 的哪个端点与 $j$ 的哪个端点是同一个端点, 然后去重即可。

那如何去重呢？注意到两个点相同这样的信息可以使用并查集维护, 于是我们可以在枚举发现两个端点相同时将这两个端点所在的集合合并, 最后给剩下的每个根节点重新编号, 然后每条边的两个端点改成其所在集合的根节点的编号即可。

图建完了之后就剩下跑最小环了, 可以用Floyd来算, 不过由于我Floyd的方法不知道为什么写炸了, 所以我就改成枚举每条边, 然后对每条边从一个端点出发跑 SPFA (不过这里要注意一下, 跑 SPFA 时要特判走的边是否就是枚举的这条边)再加上这条边的长度就好。

复杂度大概在 $O(n^{2})$ 左右。

下面是我的Code:
```cpp
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 2e2 + 5;
int n, x, y, z, l, r, cur, cure, cant;
int fa[maxn], dy[maxn], head[maxn], nex[maxn], to[maxn], val[maxn], dis[maxn];
bool al[maxn];
queue<int> q;
struct node{ //存每条边的信息 
	int u, v, w;
	bool ltmp[maxn], rtmp[maxn];
}ep[maxn];
void init(){ // 并查集初始化 
	for(int i = 0;i < maxn;i++){
		fa[i] = i;
	}
	return ;
}
int find(int x){ // 找一个集合根节点 
	if(fa[x] == x){
		return x;
	}
	return fa[x] = find(fa[x]);
}
void merge(int x, int y){ // 合并两个集合 
	fa[find(x)] = find(y);
	return ;
}
void add(int u, int v, int w){ // 链式前向星 
	nex[++cure] = head[u];
	to[cure] = v;
	val[cure] = w;
	head[u] = cure;
	return ;
}
void spfa(int s){ // SPFA 
	memset(dis, 0x3f, sizeof(dis));
	memset(al, 0, sizeof(al));
	q.push(s);
	dis[s] = 0;
	al[s] = 1;
	while(!q.empty()){
		int fr = q.front();
		q.pop();
		al[fr] = 0;
		for(int i = head[fr];i;i = nex[i]){
			int t = to[i];
			int k = val[i];
			if(dis[fr] + k < dis[t]){
            	if(i == cant || i == cant + 1){ // 这里的 cant 就是不能走的边的编号
            		continue; 					// 由于是无向图，所以cant + 1就是其反向边 
            	}
			    dis[t] = dis[fr] + k; 							
				if(al[t]){
					continue;
				}
				q.push(t);
				al[t] = 1;
			}
		}
	}
	return ;
}
int main(){
	init();
	scanf("%d", &n);
	for(int i = 1;i <= n;i++){
		scanf("%d %d %d %d", &x, &z, &l, &r); // 输入 
		ep[x].u = 2 * x - 1;
		ep[x].v = 2 * x;
		ep[x].w = z;
		for(int j = 1;j <= l;j++){
			scanf("%d", &y);
			ep[x].ltmp[y] = 1; // 记录与那些边相交 
		}
		for(int j = 1;j <= r;j++){
			scanf("%d", &y);
			ep[x].rtmp[y] = 1;
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			if(i == j){
				continue;
			}
			if(ep[i].ltmp[j] && ep[j].ltmp[i]){
				merge(ep[i].u, ep[j].u);  		// 并查集维护 
			}
			if(ep[i].ltmp[j] && ep[j].rtmp[i]){
				merge(ep[i].u, ep[j].v);
			}
			if(ep[i].rtmp[j] && ep[j].ltmp[i]){
				merge(ep[i].v, ep[j].u);
			}
			if(ep[i].rtmp[j] && ep[j].rtmp[i]){
				merge(ep[i].v, ep[j].v);
			}
		}
	}
	for(int i = 1;i <= 2 * n;i++){
		if(fa[i] == i){
			dy[fa[i]] = ++cur; // 给剩下的集合根节点重新编号 
		}
	}
	for(int i = 1;i <= n;i++){
		ep[i].u = dy[find(ep[i].u)]; // 去重 
		ep[i].v = dy[find(ep[i].v)];
		add(ep[i].u, ep[i].v, ep[i].w); // 加边 
		add(ep[i].v, ep[i].u, ep[i].w);
	}
	int ans = 0x3f3f3f3f;
	for(int i = 1;i <= cure;i += 2){ // 由于 i + 1 就是其反向边所以没有必要再枚举一次, 让其直接跳过 
		int j = (i + 1) / 2;
		cant = i; // 记录不能走的边的编号 
		spfa(ep[j].v); // 从一个端点跑 SPFA 
		ans = min(ans, ep[j].w + dis[ep[j].u]); // 更新答案 
	}
	printf("%d", ans); // 输出 
	return 0;
} 

---

## 作者：momo5440 (赞：15)

这题就是弗洛伊德判最小环，但是建图非常恶心。所以我要讲一下我的建图方法，首先我把数据读入，然后枚举它的旁边（字面意思），如果他的左节点没有编号就给他定个新编号，如果有的话就跳过去，对右边也一样，但是问题就来了，你并不知道那边是左那边是右，所以需要判断，在这里我用了stl里的set，虽说就算不用也肯定不会TLE但用后肯定会快，废话不多说，详情请见代码
```cpp
#include <iostream>
#include <cstring>
#include <set>
#include <vector>
using namespace std;
struct fense{//结构体 
	int rc,lc,value;//分辨对应 左节点编号 右节点编号 值 
	set <int> sl;//临边的编号（供他人查询的） 
	set <int> sr;
	vector <int> vl;//临边的编号（供自己查询的） 
	vector <int> vr;
};
fense a[20005]; 
int dp[105][105],f[105][105];
int main(){
	int n,id,value,t1,t2,tp,temp=0;//temp表示当前下一个节点应该表示的编号 
	cin>>n;
	for (int i=1;i<=n;i++){//初始化 
		a[i].rc=0; 
		a[i].lc=0;
	}
	for(int i=1;i<=n;i++){//读入数据 
		cin>>id;
		cin>>a[id].value>>t1>>t2;
		for (int j=1;j<=t1;j++){
			cin>>tp;
			a[id].sl.insert(tp);
			a[id].vl.push_back(tp);
		}
		for (int j=1;j<=t2;j++){
			cin>>tp;
			a[id].sr.insert(tp);
			a[id].vr.push_back(tp);
		}
	}
	for (int i=1;i<=n;i++){//最外层循环枚举每条边 
		if (a[i].lc==0) {//如果左边节点没编号 
			a[i].lc=++temp;//给予编号 
			for (int j=0;j<a[i].sl.size();j++){//枚举临边 
				tp=a[i].vl[j];
				if (a[tp].sr.count(i)==1) a[tp].rc=a[i].lc;//判断左右 
				if (a[tp].sl.count(i)==1) a[tp].lc=a[i].lc;
			}
		} 
		if (a[i].rc==0) {//右侧同理 
			a[i].rc=++temp;
			for (int j=0;j<a[i].sr.size();j++){
				tp=a[i].vr[j];
				if (a[tp].sr.count(i)==1) a[tp].rc=a[i].rc;
				if (a[tp].sl.count(i)==1) a[tp].lc=a[i].rc;
			}
		}
		
	}
	memset(dp,0x3f,sizeof(dp));
	memset(f,0x3f,sizeof(f));
	int ans=dp[1][1];
	//建图 
	for (int i=1;i<=n;i++){
		int lc=a[i].lc;
		int rc=a[i].rc;
		dp[lc][rc]=a[i].value;
		dp[rc][lc]=a[i].value;
		f[lc][rc]=a[i].value;
		f[rc][lc]=a[i].value;
	}
	//弗洛伊德判最小环 
	for (int i=1;i<=temp;i++){
		dp[i][i]=0;
		f[i][i]=0;
	}
	
	for (int k=1;k<=temp;k++){
		for (int i=1;i<=k-1;i++){
			for (int j=i+1;j<=k-1;j++) ans=min(ans,f[i][k]+f[k][j]+dp[i][j]);
		}
		for (int i=1;i<=temp;i++){
			for (int j=1;j<=temp;j++) dp[i][j]=min(dp[i][k]+dp[k][j],dp[i][j]);
		}
	}
	cout<<ans;
} 
```


---

## 作者：啊嘞嘞嘞嘞 (赞：8)

来个稍微麻烦点但没毛病的做法：建图后直接跑最小环，所有点一共8ms，和那些0ms的相比可能有些慢

最小环不说了，用Floyd比较简单，这里麻烦的是建图，根据边找出点有点困难，我用的是并查集（有大佬提到，这里再说一下）

题目给了$m$条边，先假定第$i$条边的两端点为$2i-1,2i$，并记录第$i$条边和第$j$条边的交点为$connect[i][j]$（不直连就为0），这样读完数据后会得到很多连接关系。

由于题目中**不存在重边或自环**，那么就有：$connect[i][j]$与$connect[j][i]$表示的是同一个顶点（而根据上述方法，显然这2个值不等）。如何维护相等关系？很自然地会想到并查集，直接合并两个点即可。

接下来根据并查集中不同顶点的fa，可以得到实际上不同的顶点，但是需要将其离散一下。离散的过程很简单，这里提一下。初始化$n$和$nid[]$为0（$nid[]$用于映射），对于点$i∈[1,2m]$，考察它的fa，如果$nid[fa[i]]==0$，那么这个点没被加入图中，$nid[i]=++n$，否则$nid[i]=nid[fa[i]]$。然后循环每条边，连接点$nid[i*2-1]$,$nid[i*2]$即可

```cpp
#include <cstdio>
#include <cstring>
#define MAXN 210
using namespace std;
int n,m,l[MAXN],g[MAXN][MAXN],dist[MAXN][MAXN];
int connect[MAXN][MAXN]; //两条边的交点
struct union_find_set { //超级简洁的并查集
	int n,fa[MAXN];
	void init(int N) {
		n=N;
		for (int i=1;i<=n;i++) fa[i]=i;
	}
	int getFather(int u) {
		while (u=fa[u]=fa[fa[u]],u!=fa[u]);
		return u;
	}
	bool set_union(int u,int v) {
		return (u=getFather(u))==(v=getFather(v)) ? false : fa[v]=u;
	}
} ufs;
inline int min(int a,int b) {
	return a<b ? a : b;
}
int main() {
	scanf("%d",&m);
	//一开始默认有2m个点，后面进行合并
	for (int i=0;i<m;i++) {
		int s,L,n1,n2,x; //标号，长度
		scanf("%d%d%d%d",&s,&L,&n1,&n2);
		l[s]=L;
		for (int i=0;i<n1;i++) {
			scanf("%d",&x);
			connect[s][x]=s*2-1;
		}
		for (int i=0;i<n2;i++) {
			scanf("%d",&x);
			connect[s][x]=s*2;
		}
	}
	//合并
	int nn=m*2,nid[MAXN]={};
	ufs.init(m*2);
	for (int i=1;i<=m;i++) {
		for (int j=1;j<=m;j++) {
			if (connect[i][j]) ufs.set_union(connect[i][j],connect[j][i]);
		}
	}
	//离散化  加边
	for (int i=1;i<=nn;i++) {
		int fa=ufs.getFather(i);
		nid[i]=nid[fa] ? nid[fa] : nid[fa]=++n;
	}
	//建图
	memset(dist,0x0f,sizeof dist);
	memset(g,0x0f,sizeof g);
	for (int i=1;i<=m;i++) {
		int u=nid[i*2-1],v=nid[i*2];
		g[u][v]=g[v][u]=dist[u][v]=dist[v][u]=l[i];
	}
	//求解
	int ans=1<<20;
	for (int i=1;i<=n;i++) dist[i][i]=0;
	for (int k=1;k<=n;k++) {
		for (int i=1;i<k;i++) {
			for (int j=i+1;j<k;j++) {
				ans=min(ans,dist[i][j]+g[j][k]+g[k][i]);
			}
		}
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=n;j++) {
				dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Drinkwater (赞：5)

这道题实际上难在建图，图建好了就可以了，我们设篱笆有左右两个端点，然后我们遇到一个点我们就去枚举跟他有关的边，然后存入数组，细节比较多，然后建完图后FLOYD判最小环，就可以了，不知道FLOYD判最小环的看这篇博客<http://blog.csdn.net/BroDrinkWater/article/details/62416723>











```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
#define REP(i,a,b) for(register int i = (a), i##_end_ =  (b); i <= i##_end_; ++i)
inline int read()
{
    char c = getchar();register int fg = 1, sum = 0;
    while(c < '0' || c > '9')
    {
        if(c == '-')fg = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
    {
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return fg * sum;
}
const int maxn = 500;
int n;
struct T
{
    int s,len,ls,rs;
    int l[maxn],r[maxn];
    int l_id,r_id;
}a[maxn];
int dis[maxn][maxn],map[maxn][maxn];
int id[maxn][maxn],num;
#define inf 0x3f3f3f3f
int main()
{
    n = read();
    REP(i,1,n)
    {
        a[i].s = read();
        int ID = a[i].s;a[ID].len = read();a[ID].ls = read();a[ID].rs = read();
        REP(j,1,a[ID].ls)
            a[ID].l[j] = read();
        REP(j,1,a[ID].rs)
            a[ID].r[j] = read();
    }
    int mina = inf;
    REP(i,1,n)
    {
        REP(j,1,n)
        {
            if(i == j)continue;
            dis[i][j] = map[i][j] = inf;
        }
    }
    REP(i,1,n)
    {
        if(!a[i].l_id)a[i].l_id = ++num;
        REP(j,1,a[i].ls)
        {
            int x = a[i].l[j];bool flag = 0;
            REP(k,1,a[x].ls)
                if(a[x].l[k] == i){flag = 1;break;}
            if(flag)a[x].l_id = a[i].l_id;
            else a[x].r_id = a[i].l_id;
        }
        if(!a[i].r_id)a[i].r_id = ++num;
        REP(j,1,a[i].rs)
        {
            int x = a[i].r[j];bool flag = 0;
            REP(k,1,a[x].ls)
                if(a[x].l[k] == i){flag = 1;break;}
            if(flag)a[x].l_id = a[i].r_id;
            else a[x].r_id = a[i].r_id;
        }
    }
    REP(i, 1, n)
    {
        int L_id = a[i].l_id;
        int R_id = a[i].r_id;
        int len = a[i].len;
        map[R_id][L_id] = map[L_id][R_id] = len;
        dis[R_id][L_id] = dis[L_id][R_id] = len;
    }
    REP(k,1,num)
    {
        REP(i,1,k-1)
        {
            REP(j,i+1,k-1)
            {
                mina = min(mina,dis[i][j] + map[i][k] + map[k][j]);
            }
        }
        REP(i,1,num)
        {
            REP(j,1,num)
            {
                dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
            }
        }
    }
    printf("%d\n",mina);
    return 0;
}
```

---

## 作者：Celebrate (赞：4)

这一道题有3个难点：

（1）每一条边都有编号，感觉有些麻烦：

认真看题可以发现“边的标号s(1<=s<=N)”，也就是说只是把边

的顺序打乱而已，我们就不用管这么多，直接放上去边的编号，然后搜索的时候1-n

（2）这一道题的主要难点————找最小的环的大小：

这个dfs或者bfs都可以，不过bfs每一个队列都要用结构体带一个数组，但是dfs是一次搜到底，所以采用dfs来做

这里还要注意一个细节，查找只用找一边，因为环是两面想通的，所以找一边即可

首先在主函数里面for（i=1;i<=n;i++），优化一下每次搜索完

开始的那一条边就把这一条边设置为不能走，因为以后搜索

到这一条又会把以前搜过的再搜一次，浪费了很多时间

（3）边的方向：

因为这是无向边，所以得注意一下方向.

输入的时候把左边的变设置为1，右边的边设置为2

搜索的时候假如在边的左边必须到右边去，右边就必须到左边去，每次走都要加上距离

从一条边的左边走到另一条边，你还是在你现在所在的边的左边

代码如下：

```cpp
#include<bits/stdc++.h>
#define MAXN 110
using namespace std;
typedef long long ll;
ll n;
ll a[MAXN][MAXN],d[MAXN],ans=0,minn=LONG_MAX;
bool v[MAXN],bk[MAXN];
void dfs(ll k,ll t,ll flag)//k记录当前所在的边，t表示左或右，flag表示开头 
{
    if(ans>=minn) return;//如果已经超出了最小值，就肯定不用管了 
    if(k==flag)//如果走到了起点 
    {
        minn=ans;//赋值然后返回 
        return;
    }
    for(ll i=1;i<=n;i++)//枚举所有的边 
    {
        if(v[i]==true && bk[i]==true && a[k][i]==3-t)//如果可以走的话，3-t就是在另外一个点 
        {
            v[i]=false;ans=ans+d[i];//记为不可以走 
            dfs(i,a[i][k],flag);//往下搜索 
            v[i]=true;ans=ans-d[i];//回溯 
        }
    }
}
int main()
{
    ll i,j,t,t1,x,y;
    scanf("%lld",&n);
    for(i=1;i<=n;i++)//输入 
    {
        scanf("%lld",&t);
        scanf("%lld%lld%lld",&d[t],&x,&y);
        for(j=1;j<=x;j++)//记录位置 
        {
            scanf("%lld",&t1);
            a[t][t1]=1;
        }
        for(j=1;j<=y;j++)
        {
            scanf("%lld",&t1);
            a[t][t1]=2;
        }
    }
    memset(bk,true,sizeof(bk));//一开始每一条边都是可以走的 
    for(i=1;i<=n;i++)
    {
        memset(v,true,sizeof(v));
        ans=0;
        for(j=i+1;j<=n;j++)//我不想判断开头，就直接这样了，i+1是一个优化 
        { 	
            if(a[i][j]==1)//如果在左边，因为不想两边都找，所以只找一边 
            //如果愿意的话，完全可以改成右边，只是要注意一下ans该加什么 
            {
                v[j]=false;ans=ans+d[j];
                dfs(j,a[j][i],i);//开始dfs 
                v[j]=true;ans=ans-d[j];
            }
        }
        bk[i]=false;
    }
    printf("%lld\n",minn);
    return 0;
}
```

如果我的题解有不对的地方或者您又不懂的地方，欢迎大家发邮件给我

---

## 作者：Vin_1999 (赞：3)

就是很裸很裸的求最小环。

百度了三种题解，我来给大家分析一下。

解法一：dfs(m^2)

解法二：floyd(n^3)

dfs固然简单，但如果这题数据量调大而且是稠密图的话就不行了。

至于针对点操作的floyd。我只想说

题目的输入太恶心了。

对于怎么把边集转换成点集我也看到两种方法（所以说三种题解）

一是用并查集。二是直接把两个重合的点加一条边权为0的边。

至于用并查集的方法，本蒟蒻感觉又麻烦又耗时。还不如直接加边好使。

原址在此http://blog.sina.com.cn/s/blog\_84438fd70100t6f2.html(我都引了原址了博主应该不会打我了吧）

至于为什么floyd的判断是d[i]]j]>0，因为我们采取了比较特殊的构图，在floyd中，第k点肯定要与前两个点都有边连，那就肯定有一条是值为0的边。如果d[i][j]==0，那三个点就重合了。

最后附上我丑陋的代码owo







    


```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<climits>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
const int maxm=110,maxn=220;
static int G[maxn][maxn],v[maxm][maxm],d[maxn][maxn];
int ans=1<<30,n,scnt;
inline void init()
{
    memset(G,30,sizeof(G));
    memset(d,30,sizeof(d));
    memset(v,-1,sizeof(v));
    int x,y,len,t1,t2;
    scanf("%d",&n);
    rep(i,1,n)
    {
        scanf("%d%d%d%d",&x,&len,&t1,&t2);
        G[2*x-1][2*x]=G[2*x][2*x-1]=len;
        rep(j,1,t1)
        {
            scanf("%d",&y);
            v[x][y]=1;    //1 left,0 right
        }
        rep(j,1,t2)
        {
            scanf("%d",&y);
            v[x][y]=0;
        }
    }
    rep(i,1,n-1)
      rep(j,i+1,n)
        if(v[i][j]>=0)
        {
              G[i*2-v[i][j]][j*2-v[j][i]]=0;
              G[j*2-v[j][i]][i*2-v[i][j]]=0;
        }
}
inline void mcfloyd()
{
    memcpy(d,G,sizeof(G));
    rep(k,1,2*n)
    {
        rep(i,1,k-1)
          rep(j,i+1,k-1)
            if(d[i][j]) ans=min(ans,d[i][j]+G[j][k]+G[k][i]); 
    rep(i,1,2*n)
      rep(j,1,2*n)
      {
          d[i][j]=min(d[i][j],d[i][k]+d[k][j]); 
            }
    }
}
int main()
{
  freopen("e:/in.txt","r",stdin);
     init();
     mcfloyd();
     printf("%d",ans);
}
//by lyyz-ljy
那这三个点就重合了，就求不了最小值了
```

---

## 作者：pocafup (赞：1)

这题是我期中测试的一题水题,然而英文题目太长了不想读...后面考完被同学提醒后20分钟切了(心塞)

切完看了波题解,发现貌似我的方法跟大家都不一样呢...

常规做法: $Floyd$

这个有三页的题解了,本蒟蒻在此不多讲

时间复杂度 $O(n^3)$

我的解法: $queue+dijkstrra$

可以发现,如果一个点绕了一圈后跑回远点,那么他所跑的路就是一圈周长

用这个思路,我们暴力枚举每个点跑 $dijkstra$ .每次绕了一圈回到原点的时候(肯定比原点要大),我们更新答案,不更新原点(~~本来也不需要更新~~)

问题来了, $dijkstra$ 不会从自己一条边出发,再从对吗跑回自己呢?

我们可以观察到一个点:左边端点所连的边跟右边端点所连的边没有任何关系.基于此,不管我们在点 $i$ 的哪一个端点,我们只要确认去的点 $j$ 跟点 $i$ 所连接的端点的位置.例如我们在他的左端点,我们只将右端点放入队列.反之依然.(记得不要在端点之间建边)

```cpp
  int to = 1;//假设他在右端点(1为右端点,0为左端点)
  for (int k : adj[v][0]) if (k==qf) goto abcd;假设在左端点找到,那么就之间下一步(因为如果他在左端点,他要去的地方是右端点,to表示的不是他现在的地方,而是要去的地方)
  to = 0;//如果搜遍左端点都没找到,那么证明他现在在右端点,要去左端点
  abcd:;
  if (dist[v][to]>dist[qf][qs]+len[v]){//裸的dijkstra
      dist[v][to] = dist[qf][qs]+len[v];
      if (!inq[v][to]){inq[v][to] = true;q.push(make_pair(v,to));}
	}
```

最后的答案更新方法:(在 $dijkstra$ 里面更新)

```cpp
if (v==pos && to==curr) {
        ans = min(ans,dist[qf][qs]+len[pos]);
      }
```

完整代码:

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define pp pair<int,int>
#define f first
#define s second
int n;
int len[105],ans = 1e9;
int dist[105][2];
bool inq[105][2];
vector<int> adj[105][2];
void dfs(int pos,int curr){
  queue<pp> q;
  memset(dist,0x3f3f,sizeof(dist));
  dist[pos][curr] = 0;
  q.push(make_pair(pos,curr));//起点(记得将起点状态放进去
  while(!q.empty()){
    int qf = q.front().f,qs = q.front().s;q.pop();
    inq[qf][qs] = false;
    for (int v : adj[qf][qs]){
      int to = 1;
      for (int k : adj[v][0]) if (k==qf) goto abcd;
      to = 0;
      abcd:;//上面讲的转移方式
      if (dist[v][to]>dist[qf][qs]+len[v]){
        dist[v][to] = dist[qf][qs]+len[v];
        if (!inq[v][to]){inq[v][to] = true;q.push(make_pair(v,to));}
      }
      if (v==pos && to==curr) {
        ans = min(ans,dist[qf][qs]+len[pos]);
      }//如果他现在要去原点,那么更新答案
    }
  }
}
int main(){
  cin >> n;
  for (int i=0;i<n;i++){
    int a,b,c,d; cin >> a >> b >> c >> d;
    len[a] = b;
    for (int j=0;j<c;j++) {
      int t; cin >> t;
      adj[a][0].push_back(t);
    }
    for (int j=0;j<d;j++){
      int t; cin >> t;
      adj[a][1].push_back(t);
    }//分开左右端点建边
  }
  for (int i=1;i<=n;i++) {dfs(i,0);dfs(i,1);}
  cout << ans;
}

```

复杂度仍然是 $O(n^3)$

为什么呢?其实就是一个小地方:在寻找左右端点的时候最坏情况会做n次.这个转移用数组可以优化成 $O(1)$ .加两行代码后可以变成 $O(n^2)$ ~~然而过了就懒得改了~~

接下来将那位Java大佬的思路了(已得到授权):
[大佬的地址](https://www.luogu.com.cn/user/232274)

其实区别也不大,就是将 $queue$ 改成了 $priority$ $queue$ ,再加上一些小细节的区别

存图方法: 用 $hashset$ 来代替数组,保证能在 $O(logn)$ 的速度找到这个数

更新答案方式:他将每个点的距离改为 $inf$ (包括原点),在原点出发时直接更新而不是取最小值.跑完之后只需要取原点的距离就是最终答案
求是否在端点上:
```java
if(j==i) {//去左端点
	if(!seg[i].hs2.contains(e.v))continue;//这个点不在右端点就不做
	dist[i] = Math.min(dist[i], seg[i].l+e.w);}//看看自己能不能更新
	if(seg[j].l+e.w < dist[j]) {
		dist[j] = seg[j].l + e.w;
		pq.add(new Status(e.v,j,dist[j]));
	}//pq更新下一个数
}
```

完整代码:
```java
import java.io.*;
import java.util.*;
public class Main {
	private static StreamTokenizer st;
	private static int nextInt()throws IOException{
		st.nextToken();
		return (int)st.nval;
	}
	public static void main(String args[]) throws IOException{
		st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
		int N = nextInt();
		Segment[] seg = new Segment[N];
		for(int i = 0; i < N; ++i) {
			int s = nextInt()-1, l = nextInt(), n1 = nextInt(), n2 = nextInt();
			seg[s] = new Segment(l);
			for(int j = 0; j < n1; ++j)seg[s].hs1.add(nextInt()-1);
			for(int j = 0; j < n2; ++j)seg[s].hs2.add(nextInt()-1);
		}//记图
		//bfs
		PriorityQueue<Status> pq = new PriorityQueue<>();
		int ans = Integer.MAX_VALUE;
		for(int i = 0; i < N; ++i) {
			//go from hs1 and back to hs2
			int dist[] = new int[N];
			Arrays.fill(dist, Integer.MAX_VALUE);
			for(int j : seg[i].hs1) {
				pq.add(new Status(i,j,seg[j].l));
				dist[j] = seg[j].l;
			}
			while(!pq.isEmpty()) {
				Status e = pq.poll();
				if(e.w != dist[e.v])continue;
				if(seg[e.v].hs1.contains(e.u)) {
					//往右端点走的情况
					for(int j : seg[e.v].hs2) {
						if(j==i) {
							if(!seg[i].hs2.contains(e.v))continue;
							dist[i] = Math.min(dist[i], seg[i].l+e.w);
						}
						if(seg[j].l+e.w < dist[j]) {
							dist[j] = seg[j].l + e.w;
							pq.add(new Status(e.v,j,dist[j]));
						}
					}
				}else {
					//往左端点走的情况 
					for(int j : seg[e.v].hs1) {
						if(j==i) {
							if(!seg[i].hs2.contains(e.v))continue;
							dist[i] = Math.min(dist[i], seg[i].l+e.w);
						}
						if(seg[j].l+e.w < dist[j]) {
							dist[j] = seg[j].l + e.w;
							pq.add(new Status(e.v,j,dist[j]));
						}
					}
				}
			}
			ans = Math.min(ans, dist[i]);
		}
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		pw.println(ans);
		pw.close();
	}
	private static class Segment{
		int l;
		HashSet<Integer> hs1, hs2;
		public Segment(int l) {
			this.l = l;
			hs1 = new HashSet<>();
			hs2 = new HashSet<>();
		}
	}
	private static class Status implements Comparable<Status>{
		int u, v, w;
		public Status(int u, int v, int w) {
			this.u = u;
			this.v = v;
			this.w = w;
		}
		@Override
		public int compareTo(Status o) {
			return w-o.w;
		}
	}
}
```
复杂度 $O(n^2log^2n)$ 第一个 $log $在 $pq$ ,第二个 $log$ 在 $set$.然而由于 $priority$ $queue$ $dijkstra$ 的性质,在正常情况下跑不满这个时间,预估时间 $O(n^2)$.

~~然而这位大佬用的java,于是在洛谷时间被虐的体无完肤~~

---

## 作者：vinvor (赞：1)

我的习惯总是直接写hash作为函数或者变量名...然后每次都CE...就是提醒大家注意保留字的问题。DEV C++写hash是没有问题的，洛谷要求更加严格，也有助于好习惯。

做法一

求无向图中的最小环。算法很简单，就是做m 遍dijkstra——每次找到一条边，拿掉，求这条边两个顶点之间的最短路，那么如果这两点间存在最短路，则这条路径与原来的边就构成了一个环。这样所有环中最小的一个就是答案。问题是题目给出的是边连通的信息而非点连通。也就是说我们得到的信息无法按照常规的方法（邻接矩阵，邻接表）来构图。这里就需要一个转化。由于我想不到什么好的算法，所以就用了一个复杂度为O(n^2)的转化。首先将每条边的两个顶点都看作单独的点（也就是说假设所有边都不连通，为了方便，可以分别设第i 条边的两个顶点编号为i\*2-1 和i\*2），然后对于两条连通的边，将连通这两条边的点并在一起。具体做法就是将其中一个点的连通情况全部赋给另一个点，并修改图中其他与该点连通的点信息使得合并成立。这里我借助了并查集，使得每次查找的时间都近似为常数，所以总的时间复杂度就是O(n^2)。其中n 是合并后总的点的个数经过上述转化以后，再用m遍dijkstra，总的算法时间复杂度就是O(mn^2)。

做法二

这道题给的数据是边之间的关系，首先想到的是构图，然后套经典的最短路做.但是这道题的数据输入会使按点构图很麻烦，其实这道题搜索即可，而且加剪枝后很快.由v条边开始搜索在它b方向的边，重复这个过程，直到回到v 而且是由a方向回到的，为了判断环可以加个判重，一个剪枝:对于路径长度大于已知最小环的可剪。

做法三

一种比较诡异的方法。就是把边变成“点”。在把“边”的长度设定为边两端的“点”（既原来的边）的长度的和。用由floyed算法改进的求最小环的算法求最小环。注意的是枚举“点”时，注意“点”连接的两“点”要是分别连接到该“点”代表的边的两个端点。这个复杂度为O(n^3)。超级快。证明略，有兴趣的自己想一下。

做法四

仍然是求最小环，先将边邻接矩阵转为点邻接矩阵，再dfs 求出所有环。可以证明时间复杂度为O(n^3)，所以能快速AC。

下附参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long a[303][303]={0},n=0,m=0,l[303]={0},ans=LONG_MAX,y=0;
bool hahash[303]={false},kk[303]={0};
void dfs(long goal,long u,long t){
    if(goal==u){
        if(y<ans)ans=y;
            return;
    }
    if(y>=ans)return;
    for(long i=1;i<=n;i++)
        if(!hahash[i]&&!kk[i]&&a[u][i]==3-t){
            kk[i]=true;
            y+=l[i];
            dfs(goal,i,a[i][u]);
            y-=l[i];
            kk[i]=false;
        }
}
int main(){
    cin>>n;
    for(long i=1;i<=n;i++){
        long temp,l1,l2;
        cin >>temp;cin >>l[temp]>>l1>>l2;
        for(long j=1;j<=l1;j++){
            long p=0;cin>>p;
            a[temp][p]=1;
        }
        for(long j=1;j<=l2;j++){
            long p=0;cin>>p;
            a[temp][p]=2;
        }
    }
    for(long i=1;i<=n;i++){
        y=0;
        memset(kk,0,sizeof kk);
        for(long j=1;j<=n;j++)
            if(a[i][j]==1&&!hahash[j]){
                kk[j]=true;
                y+=l[j];
                dfs(i,j,a[j][i]);
                kk[j]=false;
                y-=l[j];
            }
        hahash[i]=true;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：rq_kyz (赞：0)

# P2738 [USACO4.1] 篱笆回路Fence Loops 题解

### 传送门

[P2738 [USACO4.1] 篱笆回路Fence Loops](https://www.luogu.com.cn/problem/P2738)

---

### 题意

给定一个篱笆的形状，问篱笆围成的最小的环的长度是多少。

---

### 分析

本题最麻烦的是转换，因为输入是按照每条篱笆左右分别相邻的篱笆编号输入的，所以我们需要将其转换成每条篱笆的左右端点为节点，篱笆为边的无向图。我们可以先将第 $i$ 条篱笆的左右两个端点的编号设为 $2\times i-1$ 和 $2\times i$，这样所有的端点编号都不会重复。接着我们按照端点的编号设置并查集，并且将不同端点编号、但是其实是同一个端点的点合并，再进行离散化，就转换完成了。

接着，我们需要找最小环。楼上大佬们有很多都是用的 Floyd、Dijkstra 和 SPFA，但其实本题只使用最无脑、最暴力的 DFS 即可。详细请见代码。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a[101];//存篱笆的长度
ll b[101][2][101];//存储每条篱笆左右两边分别于哪些篱笆相邻
ll bcj[201];//并查集，下标表示的是节点的下标，因为节点最多200个，所以这里需要开200，以及下面的200都是一样
void init(ll n){
	for(ll i=1;i<=n;i++)
		bcj[i]=i;
}
ll getfather(ll x){
	if(x==bcj[x])
		return x;
	return bcj[x]=getfather(bcj[x]);
}
void hb(ll x,ll y){
	bcj[getfather(y)]=getfather(x);
}
ll t[201];//用来将最开始的编号（按照边来排的）对应成建图时的编号（离散化之后的）
ll last[201];
struct s{
	ll t,to,l;
}nxet[201];//这里的200是因为边是双向的
ll cd=0;
void lj(ll x,ll y,ll l){
	nxet[++cd].t=last[x];
	nxet[cd].to=y;
	nxet[cd].l=l;
	last[x]=cd;
}
bool vis[201];//记录节点有没有被走到过
ll dfs(ll x,ll st,ll sum,ll bs){//分别表示当前在的点、目标节点（开始节点）、路径总长度和走过的路径数量
	if(bs>=3 && x==st)
		return sum;
	if(vis[x])
		return 1e18;
	vis[x]=1;
	ll ans=1e18;
	for(ll j=last[x];j;j=nxet[j].t){
		ll y=nxet[j].to;
		ans=min(ans,dfs(y,st,sum+nxet[j].l,bs+1));
	}
	vis[x]=0;
	return ans;
}
int main(){
	ll n;
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){//输入，并将其存储
		ll x;
		scanf("%lld",&x);
		scanf("%lld%lld%lld",&a[x],&b[x][0][0],&b[x][1][0]);
		for(ll j=1;j<=b[x][0][0];j++){
			ll y;
			scanf("%lld",&y);
			b[x][0][y]=1;
		}
		for(ll j=1;j<=b[x][1][0];j++){
			ll y;
			scanf("%lld",&y);
			b[x][1][y]=1;
		}
	}
	init(2*n);
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++){//枚举边，若两条边有公共节点，则合并并查集
			if(i==j || (!b[i][0][j] && !b[i][1][j]))
				continue;
			ll x=(b[i][0][j]?2*i-1:2*i),y=(b[j][0][i]?2*j-1:2*j);
			hb(x,y);
		}
	for(ll i=1;i<=2*n;i++)//记录哪些节点的编号被保留了
		t[getfather(i)]=1;
	ll m=0;//合并后节点的数量
	for(ll i=1;i<=2*n;i++)
		if(t[i])
			t[i]=++m;//离散化
	for(ll i=1;i<=n;i++){
		ll x=t[getfather(2*i-1)],y=t[getfather(2*i)];
		lj(x,y,a[i]);//建边
		lj(y,x,a[i]);
	}
	ll ans=1e18;
	for(ll i=1;i<=m;i++)
		ans=min(ans,dfs(i,i,0,0));//从每个节点出发，跑DFS
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：abandentsky (赞：0)

思路：就是求一个最小环。难点是题目给你给出的是边的信息，现在我们需要将边的信息转化到点上面来，换句话说，我们需要给边分配节点。有一点需要注意：a->b如果两条边都是这样的。也就是他俩是重边，这种边是头接头，尾接尾。之后就是建图，然后用Floyd跑出最小环了。（第一次做这种最小环的题目，建图还是参考的楼下大佬的思路。）我看到网上还有一些说CLZ算法求解最小环的。希望有大佬能写一篇
```c
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define MAXN 10010
#define maxnode 2000005
#define sigma_size 26
#define md 12345678
//#define INF 0x3f3f3f3f
#define INF 10000000
using namespace std;
typedef long long LL;

struct Edge
{
    int Ln,Rn,len;
    int cl[MAXN],cr[MAXN];
    int id_l,id_r;
};
Edge P[20020];
int n,ncnt;
int mp[110][110],cc[110][110];

void init()
{
    for(int i=1;i<=n;i++)                         //处理出左边节点
    {
        if(!P[i].id_l)                                      //看这个边的左边端点是不是已经被标记
           P[i].id_l=++ncnt;                            //没有就给他分配一个编号
        for(int j=1;j<=P[i].Ln;j++)
        {
            int x=P[i].cl[j];                                 //枚举出i边的左边的边
            bool flag=false;
            for(int k=1;k<=P[x].Ln;k++)
            {
                int y=P[x].cl[k];
                if(y==i)
                {
                    flag=true;
                    break;
                }
            }
            if(flag)                                           //这两条边a->b，是一样的，所以是头接头，尾接尾
                P[x].id_l=P[i].id_l;
            else
                P[x].id_r=P[i].id_l;                //这个是头接尾，尾接头
        }
    }
    for(int i=1;i<=n;i++)
        {if(!P[i].id_r)                                                   //如果这个节点还没有被编号
            P[i].id_r=++ncnt;                                         //分配编号
        for(int j=1;j<=P[i].Rn;j++)
        {
            int x=P[i].cr[j];
            bool flag=false;
            for(int k=1;k<=P[x].Rn;k++)
            {
                int y=P[x].cr[k];
                if(y==i)
                {
                    flag=true;
                    break;
                }
            }
            if(flag)
                P[x].id_r=P[i].id_r;                             //头接上头
            else
                P[x].id_l=P[i].id_r;                             //首尾相接
          }
    }
    for(int i=1;i<=ncnt;i++)                             //初始情况设置为正无穷
    {
        for(int j=1;j<=ncnt;j++)
        {
            mp[i][j]=mp[j][i]=INF;
            cc[i][j]=cc[j][i]=INF;
        }
    }
    for(int i=1;i<=n;i++)
    {
        mp[P[i].id_l][P[i].id_r]=mp[P[i].id_r][P[i].id_l]=cc[P[i].id_l][P[i].id_r]=cc[P[i].id_r][P[i].id_l]=P[i].len;
    }
}

int main()
{
    scanf("%d",&n);
    int id;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&id);
        scanf("%d %d %d",&P[id].len,&P[id].Ln,&P[id].Rn);
        for(int j=1;j<=P[id].Ln;j++)
            scanf("%d",&P[id].cl[j]);
        for(int j=1;j<=P[id].Rn;j++)
            scanf("%d",&P[id].cr[j]);
    }
    init();                                                                   //完成答对节点的编号
    for(int i=1;i<=ncnt;i++)                                  //自己到自己的边权值为0
        mp[i][i]=cc[i][i]=0;
    int ans=INF;
    for(int i=1;i<=ncnt;i++)
    {
        for(int j=1;j<i;j++)
        {
            for(int k=j+1;k<i;k++)
            {
                if(cc[i][j]+cc[i][k]+mp[j][k]<INF)
                    ans=min(ans,cc[i][j]+cc[i][k]+mp[j][k]);
            }
        }
        for(int j=1;j<=ncnt;j++)
        {
            for(int k=1;k<=ncnt;k++)
                mp[j][k]=min(mp[j][k],mp[j][i]+mp[i][k]);
        }
    }
    printf("%d\n",ans);
    return 0;
}

```



---

## 作者：caidzh (赞：0)

这题是个裸的$Floyd$求最小环，但是建图非常毒瘤

下面给出一种与其他题解不同的建图思路（应该不一样吧）

考虑一个点，它存在一个与其他点都不一样的特征，即连它的篱笆编号一定是唯一的，因此可以考虑用与这个点相连的篱笆来表示这个点。

注意到一个点的度最多为$9$，篱笆数量不超过$100$，因此可以考虑用一个$longlong$类型的整数来储存这个点（即一个$100$进制整数），再进行一次离散化。

至于连边，只需要在读入时直接将两个产生的点连上就行了

最后跑最小环即可。

下面的代码是瞎写的，很多地方都没有做到最优，能过就行啦QAQ，这种方法的优点在于相当好写，缺点是扩展性不强（毕竟度一大就要高精然后$GG$）

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
#define INF 2147483647
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
int n,num[2],tot;
map<long long,int>m;
int dis[210][210],Map[210][210],ans=INF;
int main()
{
	memset(dis,0x3f,sizeof(dis));memset(Map,0x3f,sizeof(Map));
	n=read();
	for(int i=1;i<=n;i++){
		int K=read(),a[10],len=read();num[0]=read(),num[1]=read();
		long long sum[2]={0,0};
		for(int j=0;j<=1;j++){
			for(int k=1;k<=num[j];k++)a[k]=read();a[num[j]+1]=K;
			sort(a+1,a+num[j]+2);
			for(int k=1;k<=num[j]+1;k++)sum[j]=sum[j]*100+a[k]-1;
			if(m[sum[j]]==0)m[sum[j]]=++tot;
		}dis[m[sum[0]]][m[sum[1]]]=Map[m[sum[0]]][m[sum[1]]]=len;
		dis[m[sum[1]]][m[sum[0]]]=Map[m[sum[1]]][m[sum[0]]]=len;
	}
	for(int k=1;k<=n;k++){
	    for(int i=1;i<k;i++)
	        for(int j=i+1;j<k;j++)
	        	if((long long)dis[i][j]+Map[j][k]+Map[k][i]<ans){
	        		ans=dis[i][j]+Map[j][k]+Map[k][i];
				}
		for(int i=1;i<=n;i++)
		    for(int j=1;j<=n;j++)
		        if(dis[i][j]>dis[i][k]+dis[k][j])dis[i][j]=dis[i][k]+dis[k][j];
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：逆流之时 (赞：0)

这题最简单的方法是什么？  
开始我按普通的思路dfs建图。  
```cpp
bool pd[110];
void dfs(int ln,int le,int flag)
{
	#define edge a[flag][le][i]
	#define node vis[le][flag]
	if(!node)node=++n;
	pd[le]=1;
	d[ln][node]=d[node][ln]=v[le];
	//printf("%d %d\n",le,node);
	for(int i=0;edge;i++)
		vis[edge][isf[edge][le]]=node;
	for(int i=0;edge;i++)
		if(!pd[edge])
			dfs(node,edge,!isf[edge][le]);
	#undef edge
}
```
结果发现非常难调，主程序还有很多细节，最初10+bug，浪费了三个小时，所以我就换成了迭代建图，线性时间，简单高效，而且竟然还没人写过。  
当然，Floyd最小环也要注意。（我就因为不熟悉，直接抄Floyd最小环模板，还抄错了，结果这个最简单的bug找了一个多小时）  
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool isf[110][110];//isf[i][j]：边i在边j的左边(0)还是右边(1)
int n,no,t1,t2,m;
int a[2][110][10],v[110],vis[110][2];//a[][][]:一条边的左右都有哪些边；vis[][]:一条边左右两点的序号。
int d[210][210],ans=1<<30,dis[210][210];
int main()
{
	memset(dis,32,sizeof(dis));
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		dis[i*2-1][i*2-1]=dis[i*2][i*2]=0;//m条边的图最多可能有2*m个节点
		scanf("%d",&no);
		scanf("%d%d%d",&v[no],&t1,&t2);
		while(t1--)scanf("%d",&a[0][no][t1]);
		while(t2--)scanf("%d",&a[1][no][t2]),isf[no][a[1][no][t2]]=1;
	}
	for(int i=1;i<=m;i++)
	{
		#define edge a[j][i][k]//当前边
		#define node vis[edge][isf[edge][i]]//当前点
		for(int j=0;j<2;j++)
		{
			if(!vis[i][j])vis[i][j]=++n;
			for(int k=0;edge;k++)node=vis[i][j];
		}
		dis[vis[i][0]][vis[i][1]]=dis[vis[i][1]][vis[i][0]]=v[i];
	}
	memcpy(d,dis,sizeof(dis));
	//printf("--------------------\n");
	//for(int i=1;i<=m;i++)printf("%d %d\n",vis[i][0],vis[i][1]);
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<k;i++)
			for(int j=i+1;j<k;j++)
				ans=min(ans,d[i][j]+dis[i][k]+dis[j][k]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<i;j++)
				d[j][i]=d[i][j]=min(d[i][j],d[i][k]+d[k][j]);//d[j][i]原本我漏写了，自己添加的优化自己还搞出了bug
	}
	printf("%d",ans);
	return 0;
}
```
本来还可以再优化，但这份代码已经相当高效了。  
那么，还有什么优化可以用呢？  
一是内存。Floyd常用邻接矩阵，而这题要计算的就是点的个数。上面说到m条边的图最多有2m个点（相当于m条没有公共端点的线段），然而这题还有一个限制条件：1<=n1s,1<=n2s。  
这个条件说明了每个点至少连接两条边，所以最多有100个点，邻接矩阵只用开到100$\times$100，空间复杂度就被优化到了1/4。  
然后是时间的优化。迭代时对于每个新点，它所有连接的边都在加入这个点时就判断过了，所以那一部分可以这么改：  
```cpp
for(int j=0;j<2;j++)
	if(!vis[i][j])
	{
		vis[i][j]=++n;
		for(int k=0;edge;k++)node=n;
	}
```
这样优化之后快了6ms（优化后30ms）。  
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool isf[110][110];
int n,no,t1,t2,m;
int a[2][110][10],v[110],vis[110][2];
int d[110][110],ans=1<<30,dis[110][110];
int main()
{
	memset(dis,32,sizeof(dis));
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		dis[i][i]=0;
		scanf("%d",&no);
		scanf("%d%d%d",&v[no],&t1,&t2);
		while(t1--)scanf("%d",&a[0][no][t1]);
		while(t2--)scanf("%d",&a[1][no][t2]),isf[no][a[1][no][t2]]=1;
	}
	for(int i=1;i<=m;i++)
	{
		#define edge a[j][i][k]
		#define node vis[edge][isf[edge][i]]
		for(int j=0;j<2;j++)
			if(!vis[i][j])
			{
				vis[i][j]=++n;
				for(int k=0;edge;k++)node=n;
			}
		dis[vis[i][0]][vis[i][1]]=dis[vis[i][1]][vis[i][0]]=v[i];
	}
	memcpy(d,dis,sizeof(dis));
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<k;i++)if(dis[i][k]!=dis[0][0])//这里我也添加了一个优化，i与k连通时才更新ans
			for(int j=i+1;j<k;j++)
				ans=min(ans,d[i][j]+dis[i][k]+dis[j][k]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<i;j++)
				d[j][i]=d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	}
	printf("%d",ans);
	return 0;
}
```
我永远喜欢迭代！

---

## 作者：tangyifei009 (赞：0)

这道题的难点在于如何存储这张图。本题麻烦之处在于未给出点的编号！

本题给出了每条边的编号，每条边的左端点、右端点所连接的边的编号。求的是最小环长度。如何将边化成点是一个难点。

我采用离线算法，对于每条边Edge(i) = v，假设编号为i的边左右节点编号分别为i<<1和i<<1|1（即Edge(i) = (i<<1, i<<1|1) = v），并用邻接表建立该边，将所有信息全部存下来。

在输入结束后，对每条边（设编号为i），可做如下处理：

*对于每个左节点（编号为i<<1）所连接的边（设编号为tar），搜寻i出现在tar的左边还是右边。

**若出现在左边，则建边(i<<1, tar<<1) = 0；

**若出现在右边，则建边(i<<1, tar<<1|1) = 0；

*对于每个右节点（编号为i<<1|1）所连接的边（设编号为tar），搜寻i出现在tar的左边还是右边。

**若出现在左边，则建边(i<<1|1, tar<<1) = 0；

**若出现在右边，则建边(i<<1|1, tar<<1|1) = 0；


由此一来，只需对每条边（设编号为i）进行如下处理即可：
1.	暂时删去(i<<1, i<<1|1)这条边
2.	Dijkstra(i<<1)  ans = min{ans, i<<1|1}



代码如下： 

```cpp
#include<iostream>
#include<cstdio>
#define N 205
#define INF 0xfffffff
using namespace std;

int n, head[N], cnt, edge_value[N], dis[2*N], ans = INF;
bool vis[2*N];

struct Edge
{
    int to, nxt, val;
} e[N*2];

struct Node
{
    int lnum, rnum, ln[10], rn[10];
} edge[N];

void make_edge(int from, int to, int val);
void dijkstra(int start);

int main(int argc, char const *argv[])
{
    int x, u, v, ln, rn;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &x, &v);
        edge_value[x] = v;
        make_edge(x<<1, x<<1|1, v);
        make_edge(x<<1|1, x<<1, v);
        scanf("%d%d", &edge[x].lnum, &edge[x].rnum);
        for(int j = 1; j <= edge[x].lnum; j++)
            scanf("%d", &edge[x].ln[j]);
        for(int j = 1; j <= edge[x].rnum; j++)
            scanf("%d", &edge[x].rn[j]);
    }
    
    for(int i = 1; i <= n; i++)// fence_num
    {
        for(int j = 1; j <= edge[i].lnum; j++)// make edge for every left point
        {
            int tar = edge[i].ln[j];
            for(int k = 1; k <= edge[tar].lnum; k++)
            {
                if(edge[tar].ln[k] == i)
                {
                    make_edge(i<<1, tar<<1, 0);
                    break;
                }
            }
            for(int k = 1; k <= edge[tar].rnum; k++)
            {
                if(edge[tar].rn[k] == i)
                {
                    make_edge(i<<1, tar<<1|1, 0);
                    break;
                }
            }
        }

        for(int j = 1; j <= edge[i].rnum; j++)// make edge for every right point
        {
            int tar = edge[i].rn[j];
            for(int k = 1; k <= edge[tar].lnum; k++)
            {
                if(edge[tar].ln[k] == i)
                {
                    make_edge(i<<1|1, tar<<1, 0);
                    break;
                }
            }
            for(int k = 1; k <= edge[tar].rnum; k++)
            {
                if(edge[tar].rn[k] == i)
                {
                    make_edge(i<<1|1, tar<<1|1, 0);
                    break;
                }
            }
        }
    }

    for(int i = 2; i <= 2 * n; i += 2)
    {
        dijkstra(i);
        ans = min(ans, dis[i|1] + edge_value[i>>1]);
        // printf("%d:%d\n", i/2, dis[i|1] + edge_value[i>>1]);
    }
    
    printf("%d\n", ans);
    return 0;
}

void make_edge(int from, int to, int val)
{
    // printf("(%d, %d) = %d\n", from, to, val);
    e[++cnt].nxt = head[from];
    e[cnt].to = to;
    e[cnt].val = val;
    head[from] = cnt;
}

void dijkstra(int start)
{
    for(int i = 2; i <= n*2+1; i++)
    {
        dis[i] = (i == start) ? 0 : INF;
        vis[i] = 0;
    }
    for(int i = 2; i <= n*2+1; i++)
    {
        int minnum = -1, minval = INF;
        for(int j = 2; j <= n*2+1; j++)
        {
            if(minval > dis[j] && !vis[j])
            {
                minval = dis[j];
                minnum = j;
            }
        }
        // printf("->%d(%d)", minnum, minval);
        if(minnum == -1 || minval == INF || minnum == (start|1)) return;
        vis[minnum] = 1;
        for(int j = head[minnum]; j; j = e[j].nxt)
        {
            int t = e[j].to;
            if(t == (start | 1) && i == 2) continue; 
            // if((t == (start | 1)) && edge_value[start] == minval + e[j].val) continue;
            if(dis[t] > minval + e[j].val)
            {
                dis[t] = minval + e[j].val;
                // printf("dis[%d]=%d  ", t, dis[t]);
            }
        }
    }
}

```

---

## 作者：dltzr6662019 (赞：0)

宣传下自己的博客：https://www.luogu.org/blog/cdttzr666/

本蒟蒻有两种写法，下面来一一介绍：

1. 直接爆搜每条边，看看构不构成最小环。
```cpp
#include<iostream>	//头文件
using namespace std;	//名字空间
const int MAXN=110;		//定义常量,是个好习惯
int n,s,ans=1000000,start,ls[MAXN],num[MAXN][2],a[MAXN][2][10];		
//a数组第一维表示该篱笆编号，
//第二维表示链接左端还是右端，
//第三维表示连接篱笆的编号。
int checkdir(int s,int t) {		//当前边，现在搜到的编号
	for (int i=1; i<=num[t][0]; i++) {	//遍历总数
		if (a[t][0][i]==s) return 0; 	//返回右端
	}
	return 1;	//返回左端
}
void dfs(int u, int dir, int sum) {		//开始爆搜，变量下面调用时解释过了
	if (sum>ans) return;	//ans是最优解,如果当前大于它了，就没必要继续进行
	if (u==start && sum>0) {	//重又回到起点，即形成环路
		ans=sum;		//记录最优解
		return;			//返回
	}
	for (int i=1; i<=num[u][dir]; i++) {	//遍历该端链接的每条边
		dfs(a[u][dir][i],1-checkdir(u,a[u][dir][i]),sum+ls[u]);		//搜下去，中间的checkdir是用来确认现在该走哪一端了
	}
}
int main() {	//主函数
	cin>>n;		//读入总边数
	for (int zz=1; zz<=n; zz++) {	//for循环读入
		cin>>s;		//当前边的编号
		cin>>ls[s]>>num[s][0]>>num[s][1];		//该边的长度,左端连的总个数,有端连的总个数
		for (int i=1; i<=num[s][0]; i++) cin>>a[s][0][i];		//读入左端连的编号
		for (int i=1; i<=num[s][1]; i++) cin>>a[s][1][i];		//读入右端连的编号
	}
	for (start=1; start<=n; start++) {	//爆搜每条边
		dfs(start,0,0);		//起边为start,当前是哪一端，当前总长度
	}
	cout<<ans<<endl;		//输出答案
	return 0;		//返回
}
```

1. 就是用floyed判最小环，楼下说的很清楚了，直接看代码，（只写了少量注释）
```cpp
#include<iostream>
#include<algorithm>
#include<map>
#include<cstring>
using namespace std;
const int MAXN=110;
const int INF=10000000;
struct Node {		//结构体里直接排序
	int s[9];
	Node() {
		memset(s,0,sizeof(s));
	}
	bool operator==(const Node& a) const {
		for (int i=0; i<9; i++) {
			if (s[i]!=a.s[i]) return false;
		}
		return true;
	}
	bool operator<(const Node& a) const {
		for (int i=0; i<9; i++) {
			if (s[i]<a.s[i]) return true;
			else if (s[i]>a.s[i]) return false; 
		}
		return false;
	}
}; 
int G[MAXN][MAXN],n,s,ls,n1s,n2s,cnt,dis[MAXN][MAXN];
map<Node,int> mp;		//map,C++的好帮手,直接不同类型变量转换
int floyed() {
	int ans=INF;
	memcpy(dis,G,sizeof(G));
	for (int k=1; k<=cnt; k++) {	//先更新ans，再求最短路
		for (int i=1; i<k; i++) {
			for (int j=i+1; j<k; j++) {
				ans=min(ans,dis[i][j]+G[i][k]+G[k][j]);
			}
		}
		for (int i=1; i<=cnt; i++) {	
			for (int j=1; j<=cnt; j++) {
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	return ans;
}
int main() {
	cin>>n;
	for (int i=0; i<MAXN; i++) {
		fill(G[i],G[i]+MAXN,INF);
	}
	int sta,des;
	for (int i=1; i<=n; i++) {		//读入，给点编号，这样容易floyed
		Node f1,f2;
		cin>>s>>ls>>n1s>>n2s;
		f1.s[8]=f2.s[8]=s;
		while (n1s--) cin>>f1.s[n1s];
		sort(f1.s,f1.s+9);
		if (mp[f1]==0) mp[f1]=++cnt;
		while (n2s--) cin>>f2.s[n2s];
		sort(f2.s,f2.s+9);
		if (mp[f2]==0) mp[f2]=++cnt;
		sta=mp[f1];
		des=mp[f2];
		G[sta][des]=G[des][sta]=ls;
	}
	cout<<floyed()<<endl;	//直接floyed
	return 0;
}
```

---

## 作者：饮溪 (赞：0)

总结该题的两种方法。

**1.Floyd求最小环。**

  建图真的是非常非常非常非常麻烦。
  
  用到集合map还有结构体重载运算符…
  
  还有结构体中的s数组一定要初始化！之前样例跑不过就  是因为少加了这句。
  
  不过图建好了就是floyd算最小环。
  
**2.dfs求最小环。**

  简单粗暴的搜索加上简单粗暴的输入。
  
  稍微麻烦的地方是dfs的参数，特别是dir。
  
  总体来说思路和代码都比第一种简单。
  
**法1：**
```cpp
#include<iostream>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

#define MAXN 110
#define INF 99999999

struct node {
	int s[9];
	node() {
		memset(s,0,sizeof(s));
	}
	//重载==运算符，用于map 
	bool operator==(const node &a) const {
		for (int i=0;i<9;i++) {
			if (s[i]!=a.s[i]) return false;
		}
		return true;
	}
	//重载<运算符，用于sort 
	bool operator<(const node &a) const {
		for (int i=0;i<9;i++) {
			if (s[i]<a.s[i]) return true;
			else if (s[i]>a.s[i]) return false;
		}
		return false;
	}
};

int n,s,ls,n1s,n2s,cnt;//cnt为顶点个数 
int G[MAXN][MAXN];
map<node,int> mp; 
int d[MAXN][MAXN];
int ans=INF;

void floyd() {
	//d数组赋初值，直接拷贝G数组的值 
	memcpy(d,G,sizeof(G));
	for (int k=1;k<=cnt;k++) {
		//求最小环 
		//这时d[i][j]表示：中转点为1~k-1时，所求出的i到j的最短路径
		//那么d[i][j]再加上i~k和j~k的距离，即为环的周长
		//将该值取min，最后求得的就是最小环的周长 
		for (int i=1;i<k;i++) {
			for (int j=i+1;j<k;j++) {
				ans=min(ans,d[i][j]+G[i][k]+G[k][j]);
			} 
		}
		//下面是floyd的板子 
		for (int i=1;i<=cnt;i++) {
			for (int j=1;j<=cnt;j++) {
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			}
		}
	} 
} 

int main() {
	for (int i=0;i<MAXN;i++) {
		fill(G[i],G[i]+MAXN,INF);
	}
	cin>>n;
	for (int i=1;i<=n;i++) {
		node f1,f2;
		cin>>s>>ls>>n1s>>n2s;
		f1.s[8]=f2.s[8]=s;
		while (n1s--) {
			cin>>f1.s[n1s];//下标顺序无所谓，一会儿还要排序 
		}
		sort(f1.s,f1.s+9);//将序列排序，便于比较序列是否相等 
		if (mp[f1]==0) mp[f1]=++cnt;//若集合中还没有f1这个序列，则新建一个
		while (n2s--) {
			cin>>f2.s[n2s];
		} 
		sort(f2.s,f2.s+9);
		if (mp[f2]==0) mp[f2]=++cnt;
		//顶点编号完成，开始建图
		int s,e;
		s=mp[f1];
		e=mp[f2];
		G[s][e]=G[e][s]=ls;	 
	}
	//Floyd求最小环 
	floyd();
	cout<<ans<<endl;
	return 0;
}
```

**法2：**
```cpp
#include<iostream>
using namespace std;

#define MAXN 110

int n,s,ls[MAXN],num[MAXN][2],a[MAXN][2][10]; //人为定义0为向左，1为向右
int ans,start;

int checkdir(int s,int t) {//判断下一条边的方向 
	for (int i=1;i<=num[t][0];i++) {//遍历下一条边所连的边 
		if (a[t][0][i]==s) return 0;//如果向左搜索，某一条边连向了当前边，那么return 0说明不可以往0方向走 
	}
	return 1;//反之，就不可以往1方向走（因为新的边一定有一个方向会连向当前边） 
}

void search(int u,int dir,int sum) { //u:当前边的编号 dir:表示边的方向 sum:路径的累加 
	if (sum>ans) return;//最优性剪枝 
	if (u==start && sum>0) {//当发现当前搜到的边刚好是起始边，则说明形成了环，更新答案 
		ans=min(ans,sum);
		return;
	}
	for (int i=1;i<=num[u][dir];i++) {
		int v=a[u][dir][i];//搜索的下一条边 
		search(v,1-checkdir(u,v),sum+ls[u]);//因为checkdir()返回的是不可以往哪边走，那么1-checkdir()就是将0变为1，1变为0，刚好算出相反的方向 
	}
}

int main() {
	ans=99999999;
	cin>>n;
	for (int i=1;i<=n;i++) {
		cin>>s;
		cin>>ls[s]>>num[s][0]>>num[s][1];
		for (int j=1;j<=num[s][0];j++) {
			cin>>a[s][0][j];
		}
		for (int j=1;j<=num[s][1];j++) {
			cin>>a[s][1][j];
		}
	} 
	//深搜求最小环 
	for (start=1;start<=n;start++) {
		//每一条边都搜一遍 
		search(start,0,0);
	} 
	cout<<ans<<endl;
 	return 0;
} 
```

---

## 作者：ergeda (赞：0)

来一发建图最短代码最短的代码，直接爆搜判环即可

```cpp
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 999999999
using namespace std;
const int maxn = 100010;
int Begin[maxn],to[maxn],Next[maxn],e;
void add(int x,int y){
    to[++e] = y;
    Next[e] = Begin[x];
    Begin[x] = e;
}
int minn(int x,int y){return x < y ? x : y;}
int n,a[maxn],p[maxn],sign[maxn],link[500][500],min_ans = inf,nowid,tmp;
//a是每条边的权值
void dfs(int h,int des,int ans){//分别是当前节点，终点，经过路的长度
    if(ans >= min_ans)return;//如果已搜到的答案小于当前的长度直接剪掉
    for(int i=Begin[h];i;i=Next[i]){
        if(!p[to[i]]){
            p[to[i]] = 1;
            if(link[to[i]][(tmp=h>n?h-n:h)])dfs(to[i]+n,des,ans+a[to[i]]);//判断是to[i]这条边的哪个端点与h这个端点重合，若是to[i]这个端点，就从to[i]的另一个端点to[i]+n开始搜
            else dfs(to[i],des,ans+a[to[i]]);
            p[to[i]] = 0;
        }
        else{
            if(to[i] == nowid){
                if(link[des][(tmp=h>n?h-n:h)]){//如果访问过且终点与h所在的边有路，就搜到环了
                    min_ans = minn(min_ans , ans);
                    return;
                }
            }
        }
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("bigwest.in","r",stdin);
    freopen("bigwest.out","w",stdout);
#endif
    int x,id,len,len1,len2;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
                //每条边的两个端点分别编号为i和i+n；
        scanf("%d%d%d%d",&id,&len,&len1,&len2);a[id] = len;
        for(int j=1;j<=len1;++j)scanf("%d",&x),add(id,x),link[id][x]=1;//把当前这个端点和另一条边建立联系
        for(int j=1;j<=len2;++j)scanf("%d",&x),add(id+n,x),link[id+n][x]=1;//同上
    }
    for(int i=1;i<=n;++i){
        nowid = i;memset(p,0,sizeof(p));//nowid是当前搜的边的编号
        p[i] = 1;dfs(i,n+i,a[i]);
    }
    printf("%d\n",min_ans);
    return 0;
}
```

---

## 作者：Jason_Yvan (赞：0)

用Floyd搜最小环

Floyd搜最小环详情请见博客：

[http://blog.csdn.net/wzw1376124061/article/details/69870161](http://blog.csdn.net/wzw1376124061/article/details/69870161)

读入的时候啰嗦点

重点在于把边的编号转换为端点的编号

详情见代码：

代码内解释详细：

代码C++如下：

/*************************************************************************

    > Author: wzw-cnyali
    > Created Time: 2017/4/9 19:07:01
************************************************************************/




















```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define EREP(i, a) for(register int i = (be[a]); i != -1; i = nxt[i])
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template <class T>
T read(T sum = 0, T fg = 0)
{
    char c = getchar();
    while(c < '0' || c > '9') { fg |= c == '-'; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return fg ? -sum : sum;
}
const int inf = 0x3f3f3f3f;
const int Size = 100000;
const int maxn = 10;
const int maxm = 1000;
struct node
{
    int L_id, R_id; //该条路的左右端点编号
    int L[maxn], R[maxn]; //左右端点连接的路
    int Lsum, Rsum;
    int len; //该路的长度
}line[Size];
int id_cnt; //编号
int map[maxm][maxm];
int dist[maxm][maxm];
int floyd() //floyd求最小环
{
    int minCircle = inf;
    REP(k, 1, id_cnt)
    {
        REP(i, 1, k - 1) REP(j, 1, i - 1)
            chkmin(minCircle, dist[i][j] + map[i][k] + map[k][j]);
        REP(i, 1, id_cnt) REP(j, 1, id_cnt)
            chkmin(dist[i][j], dist[i][k] + dist[k][j]);
    }
    return minCircle;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    int n = read<int>();
    REP(i, 1, n)
    {
        int id = read<int>();
        line[id].len = read<int>();
        line[id].Lsum = read<int>();
        line[id].Rsum = read<int>();
        REP(j, 1, line[id].Lsum)
            line[id].L[j] = read<int>();
        REP(j, 1, line[id].Rsum)
            line[id].R[j] = read<int>();
    }
    REP(i, 1, n) //枚举每一个端点
    {
        if(!line[i].L_id) line[i].L_id = ++id_cnt; //第i条边左端点编号
        REP(j, 1, line[i].Lsum) //枚举第i条边左端点连接的边j
        {
            int x = line[i].L[j]; bool flag = 0;
            REP(k, 1, line[x].Lsum) //判断第j条边在第i条边的左边还是右边
                if(line[x].L[k] == i) { flag = 1; break; }
            if(flag) line[x].L_id = line[i].L_id;
            else line[x].R_id = line[i].L_id;
        }
        //第i条边右端点编号,处理相同
        if(!line[i].R_id) line[i].R_id = ++id_cnt;
        REP(j, 1, line[i].Rsum)
        {
            int x = line[i].R[j]; bool flag = 0;
            REP(k, 1, line[x].Lsum)
                if(line[x].L[k] == i) { flag = 1; break; }
            if(flag) line[x].L_id = line[i].R_id;
            else line[x].R_id = line[i].R_id;
        }
    }
    mem(dist, inf);
    mem(map, inf);
    REP(i, 1, n) //每条路存入map中
    {
        int L_id = line[i].L_id;
        int R_id = line[i].R_id;
        int len = line[i].len;
        map[R_id][L_id] = map[L_id][R_id] = len;
        dist[R_id][L_id] = dist[L_id][R_id] = len;
    }
    printf("%d\n", floyd());
    return 0;
}

```

---

## 作者：巨型方块 (赞：0)

唉，蒟蒻只会用爆搜；

因为给出的信息是关于边的所以左右两端就十分必要；

但我一开始以为左右之分对爆搜来讲没有事情；

爆搜时，我搞了一关于爆搜顺序的前坠和，如果爆搜到x边且x边已经被访问过了，那么出现了一个环，就可以用前坠和算出当前的环的长度

所以从一个点开始爆搜，就可以遍历所有的环；

所以我们一定要保证爆搜时路径是一条线，不可以分叉，一单分叉了，前坠和就萎了；

怎么防止分叉呢

假如当前访问到x段，是从y段访问过来的；

x段有两个端点z1,z2；

如果z1链接着y，那么z1这个点不能爆搜；

z2同理

因为至少3条线段连成圈，所以z1,z2一定有一点可以搜下去，对于起点则有两点可以搜（貌似只搜一点也可以

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;
struct cs{//链表啦 
    int to,next;
}a[1000];
int head[200],hea[200],v[200],sum[200];//两个head，表示两个端点，v[i]是第i段的长,sum[i]是爆搜到i段时，前面线段的总长，不包括v[i] 
bool vi[200];
int n,m,x,y,z,num,ll,ans;
void init(int x,int y){
    ll++;
    a[ll].to=y;
    a[ll].next=head[x];
    head[x]=ll;
}
void ini(int x,int y){
    ll++;
    a[ll].to=y;
    a[ll].next=hea[x];
    hea[x]=ll;
}
bool check1(int x,int y){//检查x点是否链接线段y 
    int k=head[x];
    while(k){
        if(a[k].to==y)return 0;
        k=a[k].next;
    }
    return 1;
}
bool check2(int x,int y){
    int k=hea[x];
    while(k){
        if(a[k].to==y)return 0;
        k=a[k].next;
    }
    return 1;
}
void dfs(int x,int y,int s){
    if(vi[x]){
        int temp=s-sum[x];
        ans=min(ans,temp);
        return;
    }
    vi[x]=1;
    sum[x]=s;
    if(check1(x,y)){
    int k=head[x];
    while(k){
        if(a[k].to!=y)dfs(a[k].to,x,s+v[x]);
        k=a[k].next;
    }}
    if(check2(x,y)){
    int k=hea[x];
    while(k){
        if(a[k].to!=y)dfs(a[k].to,x,s+v[x]);
        k=a[k].next;
    }}
    vi[x]=0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&num,&z,&x,&y);
        v[num]=z;
        for(int i=1;i<=x;i++){
            scanf("%d",&z);
            init(num,z);
        }
        for(int i=1;i<=y;i++){
            scanf("%d",&z);
            ini(num,z);
        }
    }
    ans=1e9;
    dfs(1,-1,0);
    printf("%d",ans);
}
```

---

## 作者：herofox (赞：0)

感觉下面的神犇都非常厉害，我这里弱弱地简述一下我的方法

我没有用太多行处理输入，主要是感觉数据范围比较弱，所以直接把点当成边，把边当成点，点上有权值

然后暴力深搜，每次判断是否可以从这边出去(依据为上一次进来的点是不是在这边的连接里)，如果不行就从另一边出去

[codec]

/\*
ID: herofox1

LANG: C++

TASK: fence6

\*/







```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int inf = 2147483647;
int n;
vector<int> g[2][110];
int Ls, Ns, Is, l[110];
int xx, ans = inf;
bool visit[110];
struct E{
    int l, num;
}e[110];
inline void open()
{
    freopen("fence6.in", "r", stdin);
    freopen("fence6.out", "w", stdout);
}
inline void close()
{
    fclose(stdin);
    fclose(stdout);
}
inline int read(){
    char ch;
    bool flag = false;
    int a=0;
    while(!((((ch=getchar())>='0') && (ch<='9')) || (ch=='-')));
    if(ch!='-'){
        a *= 10;
        a += ch - '0';
    }
    else{
        flag = true;
    }
    while(((ch=getchar())>='0')&& (ch<='9')){
        a *= 10;
        a += ch - '0';
    }
    if(flag){
        a = -a;
    }
    return a;
}
inline bool cmp(E a, E b)
{
    return a.l < b.l;
}
inline void scanff()
{
    n = read();
    for(int i = 0;i < n;++i)
    {
        e[i].num = read();Ls = read();e[i].l = Ls;l[e[i].num] = Ls;
        Ns = read();Is = read();
        for(int kk = 0;kk < Ns;++kk)
        {
            xx = read();
            g[0][e[i].num].push_back(xx);//存一端的边
        }
        for(int kk = 0;kk < Is;++kk)
        {
            xx = read();
            g[1][e[i].num].push_back(xx);//存另一端的边
        }
    }
    sort(e, e + n, cmp);//排序长度
}
inline void dfs(int xxx, int dis, int last)
{
    //cout<<xxx<<" "<<bb<<" "<<dis<<endl;
    //cout<<"-------"<<endl;
    int bb1 = 0;
    bool flag = 0;
    for(int i = 0;i < g[bb1][xxx].size();++i)
    {
        if(g[bb1][xxx][i] == last)
        {
            flag = 1;
            break;
        }
```
}//判断是否可以从“0”端出，不行就改为“1”端


```cpp
    if(flag == 1)
        bb1 = 1;
    //cout<<g[bb1][xxx].size()<<endl;
    for(int i = 0;i < g[bb1][xxx].size();++i)
    {
        if(visit[g[bb1][xxx][i]] == 1)
        {
            //cout<<"1"<<endl;
            if(ans > dis + l[xxx])
                ans = dis + l[xxx];
        }
        else
        {
            //cout<<"2"<<endl;
            //cout<<g[bb1][xxx][i]<<endl;
            visit[g[bb1][xxx][i]] = 1;
            dfs(g[bb1][xxx][i], dis + l[xxx], xxx);
            visit[g[bb1][xxx][i]] = 0;
        }
    }
}
inline void printff()
{
    printf("%d\n", ans);
}
int main()
{
    open();
    scanff();
    for(int i = 0;i < n;++i)
    {
        if(e[i].l > ans)//如果这次要搜的边本身长度就比之前找到的环要长说明没有更优解
            break;
        visit[e[i].num] = 1;
        dfs(e[i].num, 0, 0);
        visit[e[i].num] = 0;
    }
    printff();
    close();
}
```
[/codec]
祝大家愉快地AC


---

## 作者：约修亚_RK (赞：0)

这题的输入真是恶心，整整用掉了75行代码来输入图...果然我还是太弱了Orz

显然，这题是无向图求最小环。假设我们已经把这个图存了起来。

求最小环怎么求呢……其实也很好理解，对于每条边(u, v)，在删除它之后求u到v的最短路，这个最短路长度（如果找得到的话）加上(u, v)的长度就是一个环的长度。找一下最小值就可以了。

所以我们可以选择跑m次的Dijkstra或者SPFA，还可以在跑Floyd的时候顺便找最小环。我是跑的Dijkstra，对于这题来说时间倒是很富裕。

然后我们回来考虑一下怎么处理输入……

之前的同学已经讲过两种方法了，但是我用的既不是并查集也不是加边，而是朴素的模拟。**仅供参考，建议还是去学习一下更好写的写法，的不过我只想出来这个。**

怎么个模拟法？

对于每条边，记录的有它的权值，左端点和右端点的编号（当然，这要我们自己生成），以及两端分别连着的边集，还有一个mode（当mode为true，左端点是与边集2的交点；否则，是与边集1的交点）。

用一个build函数来dfs。build(e)的作用为，确定第e条边的左右端点编号，并同时更新两端连着的所有边的对应端点编号，此时也能够确定这些边的mode了。

在跑完之后，记得把这些边复制一遍，因为是无向图。


```cpp
/* P2738
 * Au: SJoshua
 */
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct edge {
    int u, v, w;
} edges[300];

struct node {
    int u, d;
    bool operator < (const node &p) const {
        return d > p.d;
    }
};

set <int> nearl[101], nearr[101];
vector <int> map[101];
int proc[101], m, p;
bool mode[101], vis[101];

void dfs(int e = 1) {
    vis[e] = true;
    if (!edges[e].u) {
        edges[e].u = ++p;
        if (mode[e]) {
            for (set <int> :: iterator it = nearr[e].begin(); it != nearr[e].end(); it++) {
                if (!edges[*it].u) {
                    edges[*it].u = p;
                    if (nearr[*it].find(e) != nearr[*it].end()) {
                        mode[*it] = true;
                    }
                } else {
                    edges[*it].v = p;
                }
            }
        } else { 
            for (set <int> :: iterator it = nearl[e].begin(); it != nearl[e].end(); it++) {
                if (!edges[*it].v) {
                    edges[*it].v = p;
                    if (nearl[*it].find(e) != nearl[*it].end()) {
                        mode[*it] = true;
                    }
                } else {
                    edges[*it].u = p;
                }
            }
        }
    }
    if (!edges[e].v) {
        edges[e].v = ++p;
        if (!mode[e]) {
            for (set <int> :: iterator it = nearr[e].begin(); it != nearr[e].end(); it++) {
                if (!edges[*it].u) {
                    edges[*it].u = p;
                    if (nearr[*it].find(e) != nearr[*it].end()) {
                        mode[*it] = true;
                    }
                } else {
                    edges[*it].v = p;
                }
            }
        } else { 
            for (set <int> :: iterator it = nearl[e].begin(); it != nearl[e].end(); it++) {
                if (!edges[*it].v) {
                    edges[*it].v = p;
                    if (nearl[*it].find(e) != nearl[*it].end()) {
                        mode[*it] = true;
                    }
                } else {
                    edges[*it].u = p;
                }
            }
        }
    }
    for (set <int> :: iterator it = nearl[e].begin(); it != nearl[e].end(); it++) {
        if (!edges[*it].u || !edges[*it].v) {
            dfs(*it);
        }
    }
    for (set <int> :: iterator it = nearr[e].begin(); it != nearr[e].end(); it++) {
        if (!edges[*it].u || !edges[*it].v) {
            dfs(*it);
        }
    }
}

int dijkstra(int s, int t) {
    priority_queue <node> pq;
    int dis[200];
    bool visited[200];
    memset(dis, 0x3f, sizeof(dis));
    memset(visited, false, sizeof(visited));
    dis[s] = 0;
    pq.push((node){s, 0});
    while (!pq.empty()) {
        node p = pq.top();
        pq.pop();
        if (visited[p.u]) {
            continue;
        }
        visited[p.u] = true;
        for (unsigned int k = 0; k < map[p.u].size(); k++) {
            edge &e = edges[map[p.u][k]];
            if (!visited[e.v] && !((e.u == s && e.v == t) || (e.u == t && e.v == s))) {
                if (p.d + e.w < dis[e.v]) {
                    pq.push((node){e.v, dis[e.v] = p.d + e.w});
                }
            }
        }
    }
    return dis[t];
}

int main(void) {
    scanf("%d", &m); 
    for (int k = 1; k <= m; k++) {
        int s, leftn, rightn;
        scanf("%d", &s);
        scanf("%d %d %d", &edges[s].w, &leftn, &rightn); 
        for (int i = 0; i < leftn; i++) {
            int v;
            scanf("%d", &v);
            nearl[s].insert(v);
        }
        for (int i = 0; i < rightn; i++) {
            int v;
            scanf("%d", &v);
            nearr[s].insert(v);
        }
    }
    dfs(); 
    for (int k = 1; k <= m; k++) {
        edges[k+m] = (edge){edges[k].v, edges[k].u, edges[k].w};
        map[edges[k].u].push_back(k);
        map[edges[k].v].push_back(k+m);
    }
    int ans = 0x7fffffff;
    for (int k = 1; k <= m; k++) {
        ans = min(ans, dijkstra(edges[k].u, edges[k].v)+edges[k].w);
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：kczno1 (赞：0)

求无向图最小环，可用floyd,枚举中间点，在更新最短路前先尝试以之为环的最大点找环。

问题是读入的是每条边的邻边，所以要自己造点，对每个点都求出所连的最小的两条边的编号，再记录这两个编号对应的点，即可判断哪些点是一个点了。


---

