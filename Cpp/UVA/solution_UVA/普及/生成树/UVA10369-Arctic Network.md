# Arctic Network

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1310

[PDF](https://uva.onlinejudge.org/external/103/p10369.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10369/b3c41b35e81b308ad9ef5826dfa39b5f526836c1.png)

## 样例 #1

### 输入

```
1
2 4
0 100
0 300
0 600
150 750```

### 输出

```
212.13```

# 题解

## 作者：有朋自远方来 (赞：12)

#### 题面：
北极的某区域共有 n 座村庄，每座村庄的坐标用一对整数 (x,y) 表示。为了加强联系，决定在村庄之间建立通讯网络。通讯工具可以是无线电收发机，也可以是卫星设备。所有的村庄都可以拥有一部无线电收发机， 且所有的无线电收发机型号相同。但卫星设备数量有限，只能给一部分村庄配备卫星设备。

不同型号的无线电收发机有一个不同的参数 d，两座村庄之间的距离如果不超过 d 就可以用该型号的无线电收发机直接通讯，d 值越大的型号价格越贵。拥有卫星设备的两座村庄无论相距多远都可以直接通讯。

现在有 k 台卫星设备，请你编一个程序，计算出应该如何分配这 k 台卫星设备，才能使所拥有的无线电收发机的 d 值最小，并保证每两座村庄之间都可以直接或间接地通讯。

例如，对于下面三座村庄：

![](https://cdn.luogu.com.cn/upload/pic/65088.png)

其中 |AB|=10,|BC|=20,|AC|=10√5≈22.36
如果没有任何卫星设备或只有 1 台卫星设备 (k=0 或 k=1)，则满足条件的最小的 d=20，因为 A 和 B，B 和 C 可以用无线电直接通讯；而 A 和 C 可以用 B 中转实现间接通讯 (即消息从 A 传到 B，再从 B 传到 C)；

如果有 2 台卫星设备 (k=2)，则可以把这两台设备分别分配给 B 和 C ，这样最小的 d 可取 10，因为 A 和 B 之间可以用无线电直接通讯；B 和 C 之间可以用卫星直接通讯；A 和 C 可以用 B 中转实现间接通讯。

如果有 3 台卫星设备，则 A,B,C 两两之间都可以直接用卫星通讯，最小的 d 可取 0。

~~上面来自某爆零一本通~~

### 其实这么一大堆题面只是告诉我们：求一张图，求这张图的最小生成树，去掉K条最长边，剩下的第K+1长的边. 
  
 #### 做法：
当正向思考受阻时，逆向思维可能有奇效。本题就是这样。知道卫星设备的数量，求最小的收发距离，可能比较困难；

但如果知道距离求数量，就很简单了。把所有可以互相通讯的村庄连接起来，构成一个图。卫星设备的台数就是图的连通支的个数。

   问题转化为：找到一个最小的d，使得把所有权值大于d的边去掉之后，连通支的个数小于等于k。

   先看一个定理。定理2：如果去掉所有权值大于d的边后，最小生成树被分割成为k个连通支，图也被分割成为k个连通支。

####    证明：

用反证法。假设原图被分割成k’ (k'≠k)个连通支，显然不可能k’>k，所以k’<k。因此在某一图的连通支中，最小生成树被分成了至少两部分，不妨设其为T1,T2。因为T1和T2同属于一个连通支，所以一定存在x∈T1，y∈T2，w(x,y)≤d。又因为在整个最小生成树中，所以x到y的路径中一定存在一条权值大于d的边(u,v)（否则x和y就不会分属于T1和T2了），w(x,y)≤d<w(u,v)，所以把(x,y)加入，把(u,v)去掉，将得到一棵总权值比最小生成树还小的生成树。这显然是不可能的。所以，原命题成立。（证毕）

   有了这个定理，很容易得到一个构造算法：最小生成树的第k长边就是问题的解。

   首先，d取最小生成树中第k长的边是可行的。如果d取第k长的边，我们将去掉最小生成树中前k-1长的边，最小生成树将被分割成为k部分。由定理2，原图也将分割成为k部分。（可行性）

   其次，如果d比最小生成树中第k长的边小的话，最小生成树至少被分割成为k+1部分，原图也至少被分割成为k+1部分。与题意不符。（最优性）

   综上所述，最小生成树中第k长的边是使得连通支个数≤k的最小的d，即问题的解
   
   
 下面不哆嗦了，贴代码（我相信各位大佬都不需要代码）：
 
 ```
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>

using namespace std;

int n,T,k,m,f[505],cnt;
double x[505],y[505],ans[505*505];
struct node
{
	int x,y; 
	double d;	
}p[505*505];

double dist(double x1,double y1,double x2,double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

bool cmp(node a,node b)
{
	return a.d<b.d;
}

int getf(int x)
{
	return x==f[x]?x:f[x]=getf(f[x]);
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&k,&n);
		if(k>=n) 
		{
			printf("0.00\n");
			continue;
		} 
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf",&x[i],&y[i]);
			f[i]=i;
		}
		
		m=0;
		for(int i=1;i<=n;i++)
		  for(int j=i+1;j<=n;j++)
		    p[++m]=(node){i,j,dist(x[i],y[i],x[j],y[j])};
		    
		sort(p+1,p+m+1,cmp);
		
		cnt=0;
		for(int i=1;i<=m;i++)
		{
			int fa=getf(p[i].x),fb=getf(p[i].y);
			double d=p[i].d;
			if(fa!=fb)
			{
				f[fa]=fb;
				ans[++cnt]=d;
			}
		}
		
		printf("%.2lf\n",ans[cnt-k+1]);
	}
	return 0;
}
```


---

## 作者：Phoenix_chaser (赞：5)

# 本题其实可以转为最小生成树

首先，做题的第一步就是审题,看到此题目

![](https://cdn.luogu.com.cn/upload/image_hosting/mbwi1ctz.png?x-oss-process=image/resize,m_lfit,h_1900,w_2250)

？？？？

所以到底什么是瓶颈生成树，其实如果我们再去仔细思考一下

求的是边权的最大值最小，而像kruskal这种算法，本身是把边排个序，按道理来说应该生成的树的 _**最大值是最小的**_ 

可以得出这样的结论

### 无向图的最小生成树一定是瓶颈生成树

那反过来呢

![](https://cdn.luogu.com.cn/upload/image_hosting/6zkc5p0q.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

绿色是瓶颈生成树，红色是最小生成树，可以得出

### 瓶颈生成树不一定是最小生成树。

简单来说，本题就是让求最小生成树

再去简化一下，题目说只能建k个基站

###  _那我们可以把所有都建上_ 

###  _然后找第（总边数减k+1）条边_ 

上代码



```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int fa[509],n,m,k,ans,vis,t;
double a1,x,y;
double b[509],c[509],ans2[250250];
double suan(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
struct node{
	int x,y;
	double w;
}a[250250];
int fd(int x){
	if(fa[x]==x) return x;
	fa[x]=fd(fa[x]);
	return fa[x];
}
int cmp(node e1,node e2){
	return e1.w<e2.w;
}
int main(){
	scanf("%d",&t);
	while(t--){
	ans=1;
	vis=0;
	scanf("%d%d",&k,&n);
	if(k>=n) 
   	{printf("0.00\n");
   	continue;
   	} 
	for(int i=1;i<=n;i++)
	scanf("%lf%lf",&b[i],&c[i]);
	for(int i=1;i<=n;i++)
	fa[i]=i;
	for(int i=1;i<=n;i++){
	for(int j=i+1;j<=n;j++)
	{
		a[ans].x=i;
		a[ans].y=j;
		a[ans].w=suan(b[i],c[i],b[j],c[j]);
		ans++;
	}
}	
	sort(a+1,a+ans,cmp);
	for(int i=1;i<=ans-1;i++)
	{
		int x1=fd(a[i].x);
		int y1=fd(a[i].y);
		if(x1!=y1) {
			fa[y1]=x1;
			vis++;
			ans2[vis]=a[i].w;
		}
		}
  	printf("%.2lf\n",ans2[vis-k+1]);
	}

	return 0;
}
```
## 谢谢观看
### THE END

---

## 作者：George1123 (赞：3)

[${\color{orange}\text{欢迎拜访我这个蒟蒻的博客}}$](https://www.luogu.org/blog/wzc-wwwwd/)

题意：某地区共有$n$座村庄，每座村庄的坐标有一对整数$(x,y)$表示现在要在村庄间建立通讯网络。

通讯工具有两种，分别是需要铺设的普通线路和无线通讯的卫星设备。

只能给$k$个村庄配备卫星设备，拥有卫星设备的村庄互相间直接通讯。

铺设了线路的村庄之间也可以通讯。但是由于技术原因，两个村庄之间线路长度最多不能超过$d$，否则就会由于信号衰减导致通讯不可靠。要想增大$d$值，则会导致要投入更多的设备(成本)。

首先有测试数据组数$t$，已知所以村庄的坐标$(x,y)$，卫星设备数量$k$。

问如何分配卫星设备，才能是各个村庄之间能直接或间接地通讯，并且$d$的值最小？求出$d$的最小值。

数据范围：$0\leq k<n \leq 500$


此题做法：最小生成树：

（1）选择Kruskal算法；

（2）将$\frac{(n-1) \times  n}{2}$条边排序；

（3）从前向后遍历边，加上能连接两个未联通点的边；

（4）加的第$n-k$条边的长度就是答案。 因为:
${\color{red}\text {一个图的两棵最小生成树，}}$
${\color{red}\text {边的权值序列排序后结果相同。}}$


 我犯的错误是：把边数算成了$\frac{(n+1) \times  n}{2}$

### 以下是完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int t,n,m,k,tot;
double ans;
struct point{
	int x,y;
}p[510];
struct edge{
    int x,y,z;
}a[125000];
struct BCJ{
	int pre[510];
	void build(){
		for(int i=1;i<=n;i++)
			pre[i]=i;
	} int find(int x){
	    if(pre[x]==x) return x;
		return pre[x]=find(pre[x]);
	} bool same(int x,int y){
		return (find(y)==find(x));
	} void uni(int x,int y){
		pre[find(y)]=find(x);
	}
}B;
bool cmp(edge a,edge b){
    return a.z<b.z;
} int f(point a,point b){
	return (a.x-b.x)*(a.x
	-b.x)+(a.y-b.y)*(a.y-b.y);
}  void Kruskal(){
    int e=n;
    for(int i=1;i<=m;i++){
        if(!B.same(a[i].x,a[i].y)){
            B.uni(a[i].x,a[i].y);
            e--;
            if(e<=k){
            	ans=sqrt(1.0*a[i].z);
            	break;
			}
        }
    }
} int main(){
	scanf("%d",&t);
	while(t--){
		tot=0;
		scanf("%d%d",&k,&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",
			&p[i].x,&p[i].y);
	    B.build();
	    m=(n-1)*n/2;
	    for(int i=1;i<=n;i++){
	    	for(int j=1;j<i;j++){
	    		a[++tot].x=i;
	    		a[tot].y=j;
	    		a[tot].z=f(p[i],p[j]);
			}
		} sort(a+1,a+m+1,cmp);
	    Kruskal();
	    printf("%.2lf\n",ans);
	}
    return 0;
}
```

用Kruskal算法解此题的复杂度为$O(t \times n^2 \log n)$，用Prim算法的复杂度为$O(t \times n^2)$，但用Kruskal算法更直观。


---

## 作者：ALLTOZERO (赞：2)

无聊写题解, 建议不通过

最小生成树裸题

输出除去免费的m条边后最长的一条边即可

```cpp
#include<bits/stdc++.h>

using namespace std;

struct point1
{
	double x, y;
};
double GG(point1 x, point1 y)
{
	return sqrt((x.x - y.x) * (x.x - y.x) + (y.y - x.y) * (y.y - x.y));
}
int T, S, P;
struct edge
{
	int x, y;
	double v;
	bool operator < (edge gsyyc)
	{
		return v < gsyyc.v;
	}
};
vector<edge> e;
vector<edge> use;
point1 *po;
int *fa;
int t, n;
int get(int x)
{
	return x == fa[x] ? x : fa[x] = get(fa[x]);
}
void _merge_(int x, int y)
{
	fa[get(x)] = get(y);
}
int main()
{
	iostream::sync_with_stdio(false);
	ios::sync_with_stdio(false);
	cin >> T;
	while(T--)
	{
		cin >> S >> P;
		po = new point1[P + 1];
		for(int i = 1; i <= P; i++)
		{
			cin >> po[i].x >> po[i].y;
		}
		for(int i = 1; i <= P; i++)
		{
			for(int j = i + 1; j <= P; j++)
			{
				edge tmp;
				tmp.x = i;
				tmp.y = j;
				tmp.v = GG(po[i], po[j]);
				e.push_back(tmp);
			}
		}
		sort(e.begin(), e.end());
		fa = new int[P + 10];
		for(int i = 1; i <= P; i++)
		{
			fa[i] = i;
		}
		for(int i = 0; i < e.size(); i++)
		{
			int x = get(e[i].x);
			int y = get(e[i].y);
			if(x == y)
			{
				continue;
			}
			_merge_(x, y);
			use.push_back(e[i]);
		}
		sort(use.begin(), use.end());
		cout << fixed << setprecision(2) << use[use.size() - S].v << endl;
		delete []po;
		delete []fa;
		use.clear();
		e.clear();
	}
	return 0;
}
/**
 * Description
 * The Department of National Defence (DND) wishes to connect several northern outposts by a wireless network.
 * Two different communication technologies are to be used in establishing the network:
 * every outpost will have a radio transceiver and some outposts will in addition have a satellite channel.
 * Any two outposts with a satellite channel can communicate via the satellite,
 * regardless of their location.
 * Otherwise, two outposts can communicate by radio only if the distance
 * between them does not exceed D,
 * which depends of the power of the transceivers.
 * Higher power yields higher D but costs more.
 * Due to purchasing and maintenance
 * considerations, the transceivers at the outposts must be identical;
 * that is, the value of D is the same for every pair of outposts.
 * Your job is to determine the minimum D required for the transceivers.
 * There must be at least one communication path (direct or indirect) between every pair of outposts.
 * Input
 * The first line of input contains N, the number of test cases.
 * The first line of each test case contains 1 <= S <= 100,
 * the number of satellite channels, and S < P <= 500, the number
 * of outposts. P lines follow,
 * giving the (x,y) coordinates of each outpost in km (coordinates are integers between 0 and 10,000).
 * Output
 * For each case, output should consist of a single line giving the minimum D required to connect the network.
 * Output should be specified to 2 decimal points.
 * Sample Input
 * Language: Default
 *
 * 1
 * 2 4
 * 0 100
 * 0 300
 * 0 600
 * 150 750
 * Sample Output
 * 212.13
 * Source
 * Waterloo local 2002.09.28
 */
 ```

---

## 作者：404_notfound (赞：2)

看了半天题目没看懂~~（可能因为我太弱了）~~……手动翻译了一下

题目大意就是求一张图，有m次机会把一条边的权值变为0，求这张图的最小生成树的最长边

于是……

只需要跑一遍最小生成树，记录下选中的每条边的权值就可以了

我用了克鲁斯卡尔，因为排序后依次选中的边会越来越长，就把后面m条边看成免费的

然后就解决了2333

code：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 505
#define maxm 505*505
using namespace std;

struct edge{//存储边 
	int x,y;
	double val;
}e[maxm];

int fa[maxm],per[maxm],n,m;
double ans[maxm];

int cmp(edge a,edge b)
{
	return a.val<b.val;
}
int find(int x)//并查集 
{
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}

double Get(double x1,double y1,double x2,double y2)//求平面直角坐标系中两点的距离 
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double jx[maxn],jy[maxn];
int mian()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&m,&n);
		for(int i=0;i<=n*n;i++)//初始化并查集 
			fa[i]=i,per[i]=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf",&jx[i],&jy[i]);
		}
		int q=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(i!=j)//题目只给了点，需要再次建边，把每两个点间都建出一条边 
				{
					e[q].x=i;
					e[q].y=j;
					e[q++].val=Get(jx[i],jy[i],jx[j],jy[j]);
				}
			}
		}
		sort(e,e+q,cmp);//重载运算符也可以的，只是我太弱了不会写。。。 
		int ss=0;
		for(int i=0;i<q;i++)//普通的克鲁斯卡尔 
		{
			int x=e[i].x;
			int y=e[i].y;
			int f1=find(x);
			int f2=find(y);
			if(f1!=f2)
			{
				if(per[f1]>per[f2])fa[f2]=f1;
				else 
				{
					if(per[f1]==per[f2])
						per[f2]++;
					fa[f1]=f2;
				}
			    ans[ss++]=e[i].val;//把每次选择的边的权值记录下来 
			}
		}
		printf("%.2f\n",ans[ss-m]);//除去免费的m条边后最长的一条边 
	}
}
```

---

## 作者：xxzjbd (赞：1)

## 题意分析
第一次见瓶颈成生树，**最大边权在所有生成树中最小**，想想最小生成树的定义，发现**最小生成树一定是瓶颈生成树**，所以本题先求出最小生成树，答案一定在最小生成树中。

**注意：瓶颈生成树不一定是最小生成树，如四条边权 $2$ $2$ $2$ $2$的瓶颈生成树与 $2$ $2$ $2$ $1$ 的最小生成树都满足最大边权最小。**

$n$ 个点的树中有 $n - 1$ 条边。接下来考虑基站的作用，通过安装基站，可将基站间的边权变为 $0$ , $k$ 个基站可以构成 $k - 1$ 条边，把最小生成树中最大的 $k - 1$ 条边变成 $0$ ，那么答案就是第 $n - 1 - ( k - 1 )$ 条边，在 $kruskal$ 建树过程中输出即可。
## 代码如下
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
struct node{
	int x,y;
}q[1010];
int tot;
struct edge{
	int x,y;
	double l;
}e[1000010];
double dis(int u,int v){
	return sqrt((q[u].x-q[v].x)*(q[u].x-q[v].x)+(q[u].y-q[v].y)*(q[u].y-q[v].y));
}
bool cmp(edge x,edge y){
	return x.l<y.l;
}
int fa[1010],v[1010];
int fi(int x){
	if(fa[x]==x)return x;
	else return fa[x]=fi(fa[x]);
}
void add(int x,int y){
	fa[fi(y)]=fi(x);
}
int main(){
	int n,s,p;
	scanf("%d",&n);
	while(n--){
		tot=0;
		scanf("%d%d",&s,&p);
		if(s>=p){
			printf("0.00\n");
			continue;
		}
		for(int i=1;i<=p;i++){
			scanf("%d%d",&q[i].x,&q[i].y);
			fa[i]=i;
		}
		for(int i=1;i<=p;i++)
			for(int j=i;j<=p;j++){
				if(i==j)continue;
				e[++tot].x=i;
				e[tot].y=j;
				e[tot].l=dis(i,j); 
			}
		sort(e+1,e+tot+1,cmp);
		int cnt=0;	
		for(int i=1;i<=tot;i++){
			int xx=e[i].x,yy=e[i].y;
			if(fi(xx)!=fi(yy)){
				add(xx,yy);
				cnt++;
			}
			if(cnt==p-s){
				printf("%.2lf\n",e[i].l);
				break;
			}
		}	
	}
}
```
多组数据记得清零
## 谢谢观赏

---

## 作者：pufanyi (赞：1)

由于只关心生成树的最大值，我们可以将边从小到大排序，依次加入（若构成环则不加入），直到构成一颗生成树。

相信你已经发现了：这不就是Kruskal算法吗？

于是，我们得出结论：**无向图的最小生成树一定是瓶颈生成树。**

如果你仍然感到怀疑，那么我们再用反证法证明：

假设存在一张无向图的最小生成树$T$不是瓶颈生成树，那么我们找到该最小生成树的权值最大边$e$，我们选取该图中的一颗瓶颈生成树$T_1$，则有：对于$T_1$中的任何边$e_1$，存在$V_{e_1} <V_{e}$。删除$T$中的$e$，我们得到两棵树$T_a,T_b$。由于$T_1$是一颗生成树，必有一条边$e_{ab}$连接$T_a,T_b$，用$e_{ab}$替换$e$，可以得到更小的生成树，与$T$是最小生成树矛盾。证毕。

顺便提一句，无向图瓶颈生成树一定是最小生成树吗？

看一看下图就知道了：

![反例](https://github.com/pfypfypfy/images-in-blogs/blob/master/20180512001.png?raw=true)

由于本题是稠密图，最好用Prim解决（然而懒到家的我还是用了Kruskal）。

听说有一种复杂度更优的算法叫[Camerini's algorithm](https://en.wikipedia.org/wiki/Minimum_bottleneck_spanning_tree#Camerini's_algorithm_for_undirected_graphs)（然而我并不会），如果有大神会的话也可以教导我一下。

### 代码

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 5005;

struct City
{
	double x, y;//注意是小数（开float似乎也行）
} city[maxn];

struct Edge
{
	int from, to;
	double dist;

	bool operator < (const Edge& other) const
	{
		return dist < other.dist;
	}
} edge[maxn*maxn];

int n, m, S;

inline double sqr(double a)
{
	return a*a;
}

inline double make_dist(City a, City b)
{
	return sqrt(sqr(a.x-b.x) + sqr(a.y-b.y));
}

inline void add_edge(City a, City b, int ai, int bi)
{
	double dist = make_dist(a, b);
	m++;
	edge[m].from = ai;
	edge[m].to = bi;
	edge[m].dist = dist;
}

inline void read()
{
	scanf("%d%d", &S, &n);
	S = n-S;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%lf%lf", &city[i].x, &city[i].y);
		for(int j = 1; j < i; ++j)
			add_edge(city[i], city[j], i, j);
	}
}

struct UN_set
{
	int fa[maxn];

	inline void init(int n)
	{
		for(int i = 1; i <= n; ++i)
			fa[i] = i;
	}

	inline int getfa(int x)
	{
		return fa[x] == x ? x : fa[x] = getfa(fa[x]);
	}
} un;

inline double Kruskal()//其实最好还是用prim
{
	int tmp = 0;
	m = 0;
	read();
	sort(edge+1, edge+m+1);
	un.init(n);
	for(int i = 1; i <= m; ++i)
	{
		int ff = un.getfa(edge[i].from);
		int tf = un.getfa(edge[i].to);
		if(ff != tf)
		{
			un.fa[ff] = tf;
			tmp++;
			if(tmp == S)
				return edge[i].dist;
		}
	}
	return -1;
}

int main()
{
	int nnn;
	scanf("%d", &nnn);
	while(nnn--)
		printf("%.2f\n", Kruskal());//直接求最小生成树即可
	return 0;
}
```

[在我的博客上查看](http://www.cnblogs.com/pfypfy/p/9028655.html)

---

## 作者：licn (赞：0)

## **题目分析：**

其实就是在问最小生成树上的第 $s+1$ 大边。

## **做法：**
没两个点都连边，用 Kruskal 跑最小生成树，用 $h$ 数组记录边权，最后直接输出第 $s+1$ 大的。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5100;
int n,m,t,tot;
double x[N],y[N],fa[N];
struct node
{
	int x,y;
	double dis;
}a[N*N];
bool cmp(node sh,node jy)
{
	return sh.dis<jy.dis;
}
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void Kruskal()
{
	int num=0,v[N]={0};
	double h[N];
	for(int i=1;i<=tot;i++)
	{
		int x=find(a[i].x),y=find(a[i].y);
		if(x==y)continue;
		fa[x]=y;
		num++;
		h[num]=a[i].dis;
		if(num==m-1)break;
	}
	printf("%.2lf\n",h[num-n+1]);
}
int main(){
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)scanf("%lf%lf",&x[i],&y[i]);
		tot=0;
		for(int i=1;i<=m;i++)
			for(int j=i+1;j<=m;j++)
				tot++,a[tot].x=i,a[tot].y=j,a[tot].dis=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		sort(a+1,a+1+tot,cmp);
		for(int i=1;i<=m;i++)fa[i]=i;
		Kruskal();
	}
	return 0;
}

---

## 作者：flangeborg (赞：0)

一道不错的最小生成树题

## 题目大意

给定 $n$ 个点和它们分别的坐标 $(x_i,y_i)$，每个点之间都互相连通，连接它们的边的权值为它们的欧拉距离。现给你 $s$ 个装置，每个装置都能够把两点间的距离改为 $0$。现在要使这 $n$ 个点都连通，连接这 $n$ 个点最大的边权值最小是多少？

## 问题分析

不难看出来这道题是要让我们去求这 $n$ 个点的最小生成树，这样我们得到的数的权值是一定最小的，并且，我们还有 $s$ 次修改机会，将任意一条边的权值修改为 $0$，为了保证最大边权值最小，我们应该把最大的 $s$ 条边的边权修改为 $0$，这时候用 kruskal 算法更方便，因为此算法本身就是以边权来排序再构建最小生成树的，并且方便编写代码，更易理解（prim 算法复杂度相对于其更低，但是更加难以编写）。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int s,n,k,t,f[505];
double res; // 答案 
struct tow{int x,y;}tower[505]; // 每个点的坐标 
double dis(tow a,tow b) {return sqrt((a.x - b .x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));} // 计算两点之间距离 
struct node{
	int l,r;
	double val;
}edge[300005]; // 记录边 
bool cmp(node a,node b) {return a.val < b.val;}
int find(int now)
{
	if(f[now] == now) return now;
	return f[now] = find(f[now]);
} // 路径压缩并查集 
int main()
{
	ios::sync_with_stdio(0);
	cin >> t;
	while(t--)
	{
		cin >> s >> n;
		for(int i = 1; i <= n; i++) f[i] = i; // 初始化并查集 
		for(int i = 1; i <= n; i++)
			cin >> tower[i].x >> tower[i].y;	
		int m = 0;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				if(i == j) continue;
				edge[++m].l = i;
				edge[m].r = j;
				edge[m].val = dis(tower[i],tower[j]);
			} // 建边 
		}
		k = 0;
		double res;
		// kruskal 算法实现 
		sort(edge + 1,edge + m + 1,cmp);
		for(int i = 1; i <= m; i++)
		{
			if(k == n - s) break; // 连到第 n - s 条边时推出循环，此时 res 值即答案 
			int x = edge[i].l,y = edge[i].r;
			double d = edge[i].val;
			if(find(x) != find(y))
			{
				f[find(x)] = find(y);
				res = d;
				k++;
			}
		}
		printf("%.2lf\n",res);
	}
	return 0;
}
```


---

## 作者：Emp7iness (赞：0)

题目要求瓶颈生成树，那就看看定义。

无向图 $G$ 的一颗瓶颈生成树是这样的一颗生成树：它最大的边权值在 $G$ 的所有生成树中是最小的。瓶颈生成树的值为 $T$ 中最大权值边的权。

再看看最小生成树的定义。

无向连通图的最小生成树为边权和最小的生成树。

发现最小生成树一定是瓶颈生成树，但是瓶颈生成树不一定是最小生成树。

那我们可以先把最小生成树求出来，再在最小生成树中找答案。

再考虑基站。基站可以把一条边的边权变成 $0$。题目要求最多安装 $k$ 个基站，就可以将 $k-1$ 条边的边权变成 $0$。我们把最小生成树中最大的 $k-1$ 条边的边权变成 $0$，剩下的最大的那条边就是答案。

代码：

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<iomanip>
using namespace std;
struct edge
{
	int u,v;
	double w;
}e[255005];
int N,s,p,n,k,a[505],b[505],f[505];
double ans;
bool cmp(edge x,edge y)
{
	return x.w<y.w;
}
int fd(int x)
{
	if(f[x]==x)	return x;
	else	return f[x]=fd(f[x]);
}
void hb(int x,int y)
{
	f[fd(y)]=fd(x);
	return;
}
int main()
{
	cin>>N;
	while(N--)
	{
		k=0; n=0;
		fill(f,f+505,0);
		cin>>s>>p;
		for(int i=1;i<=p;i++)
		{
			cin>>a[i]>>b[i];
			f[i]=i;
			for(int j=1;j<i;j++)
			{
				n++;
				e[n]={i,j,sqrt((a[i]-a[j])*(a[i]-a[j])+(b[i]-b[j])*(b[i]-b[j]))};
			}
		}
		sort(e+1,e+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			if(fd(e[i].u)!=fd(e[i].v))
			{
				hb(e[i].u,e[i].v);
				ans=e[i].w;
				k++;
				if(k>=p-s)
				{
					cout<<fixed<<setprecision(2)<<ans<<endl;
					break;
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：Gorenstein (赞：0)

**简化一下题意**

在一个村庄里面有一些房子，房子的位置给出坐标。先在 $k$ 个村庄之间连边，使得接着连边直到全部连通之后，后面继续连的边中最长的一条边最短。求这条边的长度。

------------
略加分析发现，这些村庄最终形成一棵生成树。

假设我们已经求出了这棵生成树，先贪心地思考一下要把前 $k-1$ 条边放在哪里。很显然，这些边需要是整棵生成树中长度最长的那些边，这样才可以使剩下的边中最长的一条长度最短。

同时根据上述描述，极其显然我们要求一棵瓶颈生成树。

我们知道一个广为人知的结论，也就是一棵最小生成树一定是瓶颈生成树。**因此其实这题就是让我们求一棵最小生成树，然后输出第 $E-k+1$ 条边（其中 $E$ 为总边数）。**

------------
我们可以对坐标系中的每一个点与其他点都建边，然后给边排序，跑Kruskal。$T$ 组数据，每组数据中边的条数为 $\frac{n(n-1)}{2}$，对这些边排序需要一只 $\log$。求生成树的过程中假设并查集能够 $O(1)$ 完成，那么总共需要 $O(n^2)$ 的复杂度可以完成。所以最终时间复杂度为 $O(T\,n^2\log n^2)$，可以通过此题。~~数据组数的范围好像没给？~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
}
const int SIZE=1005;
struct node{
	int x,y;double val;	
}a[505*505];
bool cmp(node a,node b){return a.val<b.val;}
int t,n,k,fa[SIZE],tot1,tot2;
double x[SIZE],y[SIZE],ans[SIZE<<10];
inline double dis(double x_1,double y_1,double x_2,double y_2){
	return sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2));
}
int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
int main(){
	t=read();
	while(t--){
		k=read(),n=read(),tot1=0,tot2=0;
		if(k>=n){printf("0.00\n");continue;} 
		for(int i=1;i<=n;i++)x[i]=read(),y[i]=read();
		for(int i=1;i<=n;i++)fa[i]=i;
		//所有的点一一连边 
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				a[++tot1].x=i,a[tot1].y=j,
				a[tot1].val=dis(x[i],y[i],x[j],y[j]);
		//Kruskal求最小生成树 
		sort(a+1,a+tot1+1,cmp);
		for(int i=1;i<=tot1;i++){
			int A=find(a[i].x),B=find(a[i].y);
			double now=a[i].val;
			if(A!=B)fa[A]=B,ans[++tot2]=now;
		}
		printf("%.2lf\n",ans[tot2-k+1]);
	}
	return 0;
}
```

---

## 作者：C_Cong (赞：0)


## 本题为最小生成树裸题，直接套模版按题意修改就行了

### 本题与P1991相同，但要注意本题有多组数据，而P1991只有一组

题意：

给出n个节点的坐标，S个卫星，每个节点相互之间连通且边权为两点间距离，求这个图的最小生成树，输出最小生成树中第S-1长的边的边权，保留两位小数。

注意：S个卫星相当于S-1条边权值为0的边。

这题我是用$Prim$做的，由于看到大家发的都是Kruskal的题解，所以我就补充一篇$Prim$的。

记得存边权的变量要用double

###  AC代码（只能借鉴，不能抄哦）：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstring>
#define INF 100000000
const int maxn1=10002;
const int maxn2=600;
using namespace std;
int star,n,x[maxn2],y[maxn2],h=0;
bool vis[maxn2];//已经处理过的点的标记
double road[maxn2],f[maxn2];//road为最小生成树中各边的边权

struct edge
{
	int v;//下一个点
	double w;//边权
};

vector<edge> G[maxn2];

double TPD(int xa,int ya,int xb,int yb)//求两点距离（在本题即两点间的边的边权）
{
	return sqrt((double)((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)));
}

int main()
{
	int T;
	cin>>T;
	for(int a=1;a<=T;a++)
	{
		h=0;//初始化
		memset(G,0,sizeof(G));//初始化
		memset(vis,false,sizeof(vis));//初始化
		scanf("%d%d",&star,&n);
		for(int b=1;b<=n;b++)
		{
			scanf("%d%d",&x[b],&y[b]);
		}
		for(int b=1;b<=n;b++)
		{
			for(int c=1;c<=n;c++)
			{
				if(b==c)
				{
					continue;
				}
				else//邻接表建图
				{
					edge cmp;
					cmp.v=c;
					cmp.w=TPD(x[b],y[b],x[c],y[c]);
					G[b].push_back(cmp);
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			f[i]=INF;//初始化f[]
		}
        /*                    下方开始Prim                  */
		for(int i=0;i<G[1].size();i++)//找节点1连接到另一节点的最小边
		{
			int v=G[1][i].v;
			double w=G[1][i].w;
			f[v]=min(f[v],w);
		}
		vis[1]=true;
		for(int i=1;i<=n-1;i++)
		{
			double W=INF;
			int V;
			for(int j=1;j<=n;j++)
			{
				if(vis[j])
				{
					continue;
				}
				if(f[j]<W)//更新
				{
					W=f[j];
					V=j;
				}
			}
			vis[V]=true;//标记已经处理过
			h++;
			road[h]=W;//存最小生成树的边
			for(int j=0;j<G[V].size();j++)//找节点V连接到另一节点的最小边
			{
				int v=G[V][j].v;
				double w=G[V][j].w;
				f[v]=min(f[v],w);
			}
		}
		sort(road,road+h+1);//最小生成树边权排序
		printf("%.2lf\n",road[h-star+1]);//输出第S-1长的边
	}
	
}
```

本题似乎可以在建图时把卫星作为节点处理，用于替换普通节点，不过要设置两卫星间边权为0。

欢迎大家到我的博客食用：[链接](https://dgsyrc.github.io/2019/08/09/%E6%B4%9B%E8%B0%B7%E9%A2%98%E8%A7%A3-UVA10369-%E3%80%90Arctic%20Network%E3%80%91/#more)


---

## 作者：pipi (赞：0)

**不知道有没有人和我一样，看完翻译就有点蒙**

**事实上，这道题就是可以允许有S个树，需要给出这些树中最大的边权的最小值**

那么，考虑一下Kruskal算法，就相当于先排个序，然后用并查集等连边，因为可以有S个树，那么只需要连（P - S）个边就可以了；

至于排序，为了稳定一点，我们选择用stl中的堆来做

可以用结构体的重载运算符简单地运用↓↓↓↓↓↓↓
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
#include<queue>
#define B cout << "here" << endl;
#define M 10080
using namespace std;
struct lin{
    int aa,bb;
    double w;
    bool operator < (const lin & b)const{
        return w > b.w;
    }
}z;
double dis(int a,int b,int c,int d){
    return (double)sqrt((c - a) * (c - a) + (d - b) * (d - b));
}
int o[M];
int fi(int f){return o[f] = o[f] - f ? fi(o[f]) : f;}
void asdf(){
    priority_queue<lin>q;
    int a,b,opx[M],opy[M];
    double ans = 0;
    scanf("%d%d",&a,&b);
    for(int i = 1;i <= b;i++)o[i] = i;
    for(int i = 1;i <= b;i++)scanf("%d%d",&opx[i],&opy[i]);
    for(int i = 1;i <= b;i++)
        for(int j = 1;j <= b;j++){
            if(i == j)continue;
            z.w = dis(opx[i],opy[i],opx[j],opy[j]);
            z.aa = i;
            z.bb = j;
            q.push(z);
        }
    for(int i = 1;i <= b - a;i++){
        z = q.top();
        q.pop();
        if(fi(z.aa) == fi(z.bb)){i--;continue;}
    //	printf("%d--%d  %d--%d  %.2lf\n",z.aa,fi(z.aa),z.bb,fi(z.bb),z.w);
        ans = max(ans,z.w);
        o[fi(z.aa)] = o[fi(z.bb)];
    }
    printf("%.2lf\n",ans);
}
int main(){
    int k;
    scanf("%d",&k);
    for(int i = 1;i <= k;i++)asdf();
}
```


---

