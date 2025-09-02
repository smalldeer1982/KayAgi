# Summer Earnings

## 题目描述

Many schoolchildren look for a job for the summer, and one day, when Gerald was still a schoolboy, he also decided to work in the summer. But as Gerald was quite an unusual schoolboy, he found quite unusual work. A certain Company agreed to pay him a certain sum of money if he draws them three identical circles on a plane. The circles must not interfere with each other (but they may touch each other). He can choose the centers of the circles only from the $ n $ options granted by the Company. He is free to choose the radius of the circles himself (all three radiuses must be equal), but please note that the larger the radius is, the more he gets paid.

Help Gerald earn as much as possible.

## 样例 #1

### 输入

```
3
0 1
1 0
1 1
```

### 输出

```
0.50000000000000000000
```

## 样例 #2

### 输入

```
7
2 -3
-2 -3
3 0
-3 -1
1 -2
2 -2
-1 0
```

### 输出

```
1.58113883008418980000
```

# 题解

## 作者：MatrixCascade (赞：8)

又是一道简单 `*2500`。。

注意到这个题面非常诈骗，实际上选三个点得到的答案就是三个点两两的欧几里得距离的最小值/2。

那么先把所有距离存下来，对于一个 $(i,j)$ 的边时，如果存在 $(i,k),(k,j)$ ，使得这两条边都大于等于 $(i,j)$，那么 $(i,j)$ 就是一个可行的答案。

然后就可以用 [CF632F](https://www.luogu.com.cn/problem/CF632F) 的套路，先把边从大到小排序，然后遍历所有边，遍历到一条边后就先判断存不存在 $(i,k)$ 和 $(k,j)$ 都被标记过，然后再把 $(i,j)$ 和 $(j,i)$ 打上标记。

注意到这样做是 $n^3$ 的，bitset 优化即可，复杂度 $n^3/w$。

代码：

```
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
int x[3030],y[3030];
bitset<3030>b[3030];
int tot=0;
struct node
{
	int x,y;
	double w;
}e[10101000];
int cmp(node a,node b)
{
	return a.w>b.w;
}
signed main()
{
	int T=1;
	while(T--)
	{
		rdn;
		upn
		{
			rd(x[i]),rd(y[i]);
		}
		upn
		{
			up(j,i+1,n)
			{
				e[++tot]=(node){i,j,(double)sqrt((double)((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])))/2};
			//	printf("%.7lf",e[tot].w);edl;
			}
		}
		sort(e+1,e+tot+1,cmp);
		double ans=0;
		up(i,1,tot)
		{
			 int x=e[i].x,y=e[i].y;
			 if((b[x]&b[y]).count()!=0)
			 {
			 	ans=e[i].w;
			 	break;
			 }
			 b[x][y]=b[y][x]=1;
		}
		printf("%.7lf",ans);
	}
}
```


---

## 作者：diqiuyi (赞：6)

貌似是一种全新的做法。

**思路**

显然所求为三点之间距离的最小值的最大值。

直接枚举应该是 $O(n^3)$ 的，虽然时限宽裕但还是无法通过。于是考虑二分答案，然后考虑如何检验。

容易想到的方法先处理每个点在距离限制外所能到达的点，然后枚举两点，利用 bitset 计算交，这样做是 $O(\dfrac{n^3\log V}{w})$ 的，还不如直接暴力。

由余弦定理可知，

$c=\sqrt{a^2+b^2-2ab\cos C}\ge\sqrt{a^2+b^2-\cos C(a^2+b^2)}=\sqrt{(a^2+b^2)(1-\cos C)}$.

如果保证 $a,b\ge v$，那么当 $\cos C \ge \dfrac{1}{2}$ 时，即 $C \ge \dfrac{\pi}{3}$ 时，也有 $c \ge v$。

于是我们考虑对于每个点，建立以它为原点，坐标轴平行于题目给定的坐标系的坐标轴，单位长度不变的坐标系，在各个象限内维护这个点与其他点的连边中与 x 轴正方向的夹角中最大的与最小的，共八个角。这些角的度数可以用反三角函数计算。

对于每个点所建的坐标系，我们考虑统计每个象限中最大角与最小角的差，相邻象限中最大角与最小角的差，看最大值是否超过 $\dfrac{\pi}{3}$，最后再看是否存在相对象限使得两个象限都有点。过程中注意特判一下第一象限与第四象限所夹的角不能直接简单相减即可，具体细节可以参照代码。

显然不合法的三个点不会被统计。

又因为三角形的内角和为 $\pi$，故任意一个三角形总有一个角 $\ge \dfrac{\pi}{3}$，所以任意一个满足三边均 $\ge v$ 的三角形都会在至少一个角产生贡献，即合法的三个点一定会被统计。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
int n,x[3005],y[3005],dis[3005][3005],mxdis;
double eps=1e-8,l,r,ag[3005][3005],oho[3005][8],pie=acos(-1),sixty=acos(0.5),rt=acos(0);
//这三个角分别是 180 度、60 度、90 度
//oho 数组存的是以该点为原点，各个象限的最大角与最小角
//ag 数组存的是每两个点之间与 x 轴正方向所夹的角
inline void Add(int p,int q){
	if(ag[p][q]<rt) oho[p][0]=min(oho[p][0],ag[p][q]),oho[p][1]=max(oho[p][1],ag[p][q]);
	else if(ag[p][q]<pie) oho[p][2]=min(oho[p][2],ag[p][q]),oho[p][3]=max(oho[p][3],ag[p][q]);
	else if(ag[p][q]<rt+pie) oho[p][4]=min(oho[p][4],ag[p][q]),oho[p][5]=max(oho[p][5],ag[p][q]);
	else oho[p][6]=min(oho[p][6],ag[p][q]),oho[p][7]=max(oho[p][7],ag[p][q]);
}//分类讨论
bool check(double p){
	for(int i=1;i<=n;i++)
		for(int j=0;j<8;j+=2)
			oho[i][j]=114,oho[i][j+1]=-114;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(dis[i][j]>=p*p)
				Add(i,j),Add(j,i);//加入满足条件的角
	for(int i=1;i<=n;i++)
		if(oho[i][1]-oho[i][0]>=sixty||oho[i][3]-oho[i][2]>=sixty||oho[i][5]-oho[i][4]>=sixty
		||oho[i][7]-oho[i][6]>=sixty||oho[i][3]-oho[i][0]>=sixty||oho[i][5]-oho[i][2]>=sixty||
		oho[i][7]-oho[i][4]>=sixty||pie*2+oho[i][1]-oho[i][6]>=sixty||(oho[i][1]+1>0&&oho[i][5]+1>0)||
		(oho[i][3]+1>0&&oho[i][7]+1>0))//大力分讨
			return 1;
	return 0;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)
		x[i]=read(),y[i]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dis[i][j]=dis[j][i]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]),mxdis=max(mxdis,dis[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(y[i]==y[j]) ag[i][j]=pie*(x[i]>x[j]);//特判一手，也许不特判也可以但是懒得管了
			else{
				if(y[i]<y[j])
					if(x[i]<x[j])
						ag[i][j]=atan(1.0*(y[i]-y[j])/(x[i]-x[j]));
					else ag[i][j]=atan(1.0*(y[i]-y[j])/(x[i]-x[j]))+pie;
				else
					if(x[i]<x[j])
						ag[i][j]=atan(1.0*(y[i]-y[j])/(x[i]-x[j]))+pie*2;
					else ag[i][j]=atan(1.0*(y[i]-y[j])/(x[i]-x[j]))+pie;
			}//利用反三角函数预处理角度
	r=sqrt(mxdis);
	while(r-l>eps){
		double mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}//二分板子
	cout<<fixed<<setprecision(8)<<l/2<<'\n';//注意距离要除以 2
    return 0;
}
```

---

## 作者：Grisses (赞：6)

[题面](https://www.luogu.com.cn/problem/CF333E)

对于平面上任意 3 个点，设其坐标分别为 $(x_1,y_1),(x_2,y_2),(x_3,y_3)$。因为要求所作的圆互不相交，但可以相切，所以圆的最大半径只能是这 3 点的距离的最小值的一半。我们可以贪心地选择，优先选择距离最远的点对。如果我们第一次找到一个点对，它们与同一个点的距离大于这对点的距离，那这就是答案了。但是，这样的时间复杂度会达到 $O(n^3)$。我们还需要用 bitset 优化一下。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,x,y,tot;
  bitset<3005>f[3005];//优化判断是否已经取过这个点对
  struct node{
      int x,y;
  }a[3005];//存储每个点的坐标
  double Len(int x,int y){return sqrt(1.0*(a[x].x-a[y].x)*(a[x].x-a[y].x)+1.0*(a[x].y-a[y].y)*(a[x].y-a[y].y));}//求距离
  struct edge{//存储点对
      int x,y;//两点
      double len;//距离
      edge(){}
      edge(int a,int b){
          x=a,y=b;
          len=Len(a,b);
      }
      bool operator<(const edge &t)const{return len>t.len;}//重载运算符
  }e[5000005];
  int main()
  {
      scanf("%d",&n);
      for(int i=1;i<=n;i++){
          scanf("%d%d",&a[i].x,&a[i].y);
          for(int j=1;j<i;j++){
              e[++tot]=edge(i,j);//建立点对
          }
      }
      sort(e+1,e+tot+1);//排序
      for(int i=1;i<=tot;i++){
          int c=e[i].x,d=e[i].y;
          f[c][d]=f[d][c]=1;//标记
          if((f[c]&f[d]).count()){
              printf("%.7lf",e[i].len/2);//输出
              break;
          }
      }
      return 0;
  }
```

---

## 作者：hzoi_liuchang (赞：3)

### 分析
对于平面上的三个点，我们可以将其分为两种情况

一种情况是三个点都位于一条直线上

此时我们的最大直径只能是三点当中距离最小的两点的距离

还有一种情况是三个点不在同一条直线上

此时我们的最大直径也只能是三点当中距离最小的两点的距离

因为我们要保证圆只能相切，不能相交

如果直径再大一点，势必会出现相交的情况

所以我们可以先预处理出任意两点间的距离，然后按距离从小到大排好序

每次取出两个点，我们就判断一下它们是否和同一个点已经连到一起

如果已经连到一起，我们就输出当前答案，否则继续寻找

而判断两个点是否和同一个点连到一个我们可以用$bitset$解决

### 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
typedef double dd;
const int maxn=3005;
dd jlx[maxn],jly[maxn];
bitset<maxn> g[maxn];
struct asd{
    int from,to;
    dd da;
}b[maxn*maxn];
dd solve(int aa,int bb){
    return (dd)sqrt((jlx[aa]-jlx[bb])*(jlx[aa]-jlx[bb])+(jly[aa]-jly[bb])*(jly[aa]-jly[bb]));
}
bool cmp(asd aa,asd bb){
    return aa.da>bb.da;
}
int main(){
    int n,cnt=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf",&jlx[i],&jly[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(i==j) continue;
            b[++cnt].da=solve(i,j);
            b[cnt].from=i;
            b[cnt].to=j;
        }
    }
    sort(b+1,b+1+cnt,cmp);
    for(int i=1;i<=cnt;i++){
        int aa=b[i].from,bb=b[i].to;
        g[aa][bb]=1,g[bb][aa]=1;
        if((g[aa] & g[bb]).count()){
            printf("%.20lf\n",b[i].da/2.0);
            exit(0);
        }
    }
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：2)

我们选三个圆，首先，考虑贪心，就必须保证全部不相交，并且有一组圆相切。

那么，我们容易得出，答案就是 $3$ 个点对中最短距离除以 $2$。

这个 $2$ 是常数，所以我们的重点在于这个最短距离。

$O(n^3)$ 的枚举显然不行，那么我们考虑优化。

首先，有一个明显的贪心思路，先选最大的边，再选其他边。

但这个贪心思路是不成立的。如果你选了最大的边，那么第二小的边中，如果形成了等边三角形，最大边不能连接第二小的。那么我们可以发现，如果选择第二小的边，就比选择最大边更优。

此时，这个贪心就是错的。

此时，我们可以发现一种奇妙的做法：首先，把所有的点之间的距离从大到小排序，然后每次加边。如果加上一组边后，它的两个端点都和一个点有边，那么我们可以发现这条边就是最小值，因为其它组合都在它后面，所以最小值都比它小。

现在关键点在于联通。

首先，我们知道，边数 $m$ 大约在 $n^2$ 这个级别，也就是说，如果我们枚举所有的点，那么复杂度就仍然是 $O(n^3)$。

此时，我们可以考虑 `bitset` 来表示两点之间的关系，如果两个端点的 `bitset` 做与运算后有位置为 `true`，那么就会有一个点到两边都联通。

这样，我们的时间复杂度就减小了一个常数，最后时间复杂度为 $O(\dfrac{n^3}{w})$，时限比较大，可以过。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3005;
struct node{
	int from,to,len;
	inline bool operator <(const node &t) const{
		return len>t.len;
	}
};
vector<node> v;
bitset<maxn> Bit[maxn];
int n,x[maxn],y[maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=i;++j)
			v.push_back(node({i,j,(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])}));//注意精度问题，所以此处采取平方，后面再来开根
	stable_sort(v.begin(),v.end());//排序
	for(int i=0;i<v.size();++i){
		int qwq=v[i].from,qaq=v[i].to,awa=v[i].len;
		Bit[qwq][qaq]=Bit[qaq][qwq]=1;//加边
		if((Bit[qwq]&Bit[qaq]).count()){//有至少一个点联通
			printf("%.10lf",sqrt(awa)/2.0);
			return 0;
		}
	}
	return 0;
} 
```

---

## 作者：Su_Zipei (赞：2)

## 题意
在一个平面内给出$n$个点的坐标，任选其中三个为圆心作半径相同的圆，要求这三个圆不能相交但可以相切，求能画出的圆中的最大半径。
## 分析
首先要知道任取三个点，符合题意的最大半径是多少。

先考虑三点不共线的情况，由数学知识可以知道这三点能构成一个三角形。
因为三个圆最多只能相切，所以最大的直径就是最小的边。

三点共线的时候是一种特殊情况，但也和这个一样，最大的半径是任意两点间的最小距离的一半。

所以这个问题就简化成了，找出三个点连成三条边，使得这三条边中的最小值最大。这个比较好解决，把边权从大到小排一边序，当第一次有三个点连通时输出答案就行。

下面就是怎么判断三点是否连通，直接枚举三个点的话肯定会T掉，这时我们就要用到暴力神器$bitset$，$bitset$存储二进制的状态，用
第$i$个$bitset$的第$j$个二进制位表示$i$与$j$是否连通，然后我们枚举边，设边的起点为$u$终点为$v$，如果能找到第三点$k$使得$u$与$k$连通，$v$与$k$连通，那么加上这条边的时候，这三点就连通了，否则把相应的二进制位设置成1。看起来很繁琐但是$bitset$的两个函数$count$和$set$能帮助我们很好的解决问题，前者的作用看名字就能看出来，$set$是将某位置设置成1，于是此题得解。

```
#include<cstdio>
#include<cmath>
#include<bitset>
#include<algorithm>
using namespace std;
const int N=3010;
struct Edge{
    int fro,to;double val;
    bool operator <(const Edge&A)const{
        return val>A.val;
    }
    Edge(){}
    Edge(int a,int b,double t){
        fro=a;to=b;val=t;
    }
}e[N*N];int len;
struct Node{
    int x,y;
}point[N];
double dis(int x,int y,int xx,int yy){
    return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
}
bitset<N> q[N];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&point[i].x,&point[i].y);
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            e[++len]=Edge(i,j,dis(point[i].x,point[i].y,point[j].x,point[j].y));
    sort(e+1,e+len+1);
    for(int i=1;i<=len;i++){
        int u=e[i].fro,v=e[i].to;
        if((q[u]&q[v]).count()){
            printf("%.20lf\n",e[i].val/2.0);
            return 0;
        }
        q[u].set(v);
        q[v].set(u);
    }
}
```

---

## 作者：MattL (赞：2)

一个全新做法，无二分，无 bitset。

首先，把问题转换为求所有三角形中最短边的最大值。

注意到枚举一个点，以这个点为顶点找角，若这个角大于 $60\degree$，则不用考虑第三边，只需要对这个角的两条边取最小值。

所以枚举一个点，以这个点为原点，以 x 轴为一条边，以另外的点构成的任意角排序。排序后，枚举每一个点，问题转换为形成的角为大于 $60\degree$ 的一个角度区间中与原点距离的 $\max$。此为静态区间 $\max$ 问题，用 st 表等算法即可。求出来答案后再和枚举的这个点取 $\min$。

$$ans=\max_{i=1}^{n}\max_{j=1}^{n}\min\{\operatorname{dis}(i,j),\max_{1\leq k\leq n\wedge0\degree\leq\angle JIK\leq60\degree}\operatorname{dis}(i,k)\}$$

时间复杂度 $\mathcal O(n^2\log n)$。

---

## 作者：S00021 (赞：1)

不知道为何做到了这道题。

题意：在一个平面内给出 $n$ 个点的坐标，任选其中三个为圆心作半径相同的圆，要求这三个圆不能相交但可以相切，求能画出的圆中的最大半径。

看到这题第一反应是计算几何，然后发现半平面交凸包那套理论根本就不能套到这题上来。

所以第一步还是观察，发现这个圆是多余的，题目真正想说的是：在一个平面内给出 $n$ 个点的坐标，任选其中三点，求三点间两两欧几里得距离最小值的一半（这个时候恰好有两圆相切，一圆与另外两圆相切或相离）。

考虑 $\mathcal{O}(n^2)$ 计算出所有点对欧几里得距离，并按欧几里得距离将所有的点对从大到小排序，最终如果扫描到一个点对 $(x_i,y_i) , (x_j,y_j)$ 满足有一点 $(u,v)$ 使得 $(u,v)$ 到 $(x_i,y_i)$ 与 $(x_j,y_j)$ 的欧几里得距离均大于 $(x_i,y_i) , (x_j,y_j)$ 的欧几里得距离，那么这时候的答案一定取到了最大值。

这个可以用 bitset 维护。

代码：

```cpp
#include<bits/stdc++.h>
#define MAXN 3000
#define pf(x) ((x)*(x))
using namespace std;
bitset<MAXN+5>f[MAXN+5];
struct point{int x,y;}p[MAXN+5]; int n;
struct node{int xi,yi;double di;}b[MAXN*MAXN+5];
bool cmp(node x,node y){return x.di>y.di;}
signed main(){
	scanf("%d",&n); int numcnt=0;
	for(int i=1;i<=n;i++) scanf("%d%d",&p[i].x,&p[i].y);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			if(i==j) continue;
			b[++numcnt].xi=i,b[numcnt].yi=j;
			b[numcnt].di=sqrt(1.0*pf(p[i].x-p[j].x)+1.0*pf(p[i].y-p[j].y));
		}sort(b+1,b+numcnt+1,cmp);
	for(int i=1;i<=numcnt;i++){
		int x=b[i].xi,y=b[i].yi;
		f[x][y]=f[y][x]=1;	
		if((f[x]&f[y]).any()) return !printf("%.10lf",b[i].di/2);	
	}
	return 0;
}
```

---

## 作者：Light_in_Dark (赞：0)

## CF333E Summer Earnings 题解

**请注意**！**千万不要**被题目描述所迷惑！其实要找到这个**最大直径**就是找这三个点的**距离的最小值**，而半径就是直径的一半，于是，我们就可以写出如下 $O(n^3)$ 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 3e3 + 5;
int x[inf], y[inf], n, ans;
int f(int x) { return x * x; } //计算平方 
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d %d", &x[i], &y[i]);
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			for (int k = j + 1; k <= n; ++k) { //枚举三个点 
				int len1, len2, len3;
				len1 = f(x[i] - x[j]) + f(y[i] - y[j]);
				len2 = f(x[i] - x[k]) + f(y[i] - y[k]);
				len3 = f(x[j] - x[k]) + f(y[j] - y[k]); //计算出三条边的长度的平方
				ans = max(ans, min(len1, min(len2, len3))); //找出最小的一条边，并更新答案 
			}
		}
	}
	printf("%.20Lf", sqrt((long double) ans) / 2); //输出答案 
	return 0;
} 
```

于是，我们就可以光荣地 `T` 掉了。。。

[附图](https://www.luogu.com.cn/record/68331747)

那有没有其它的方法呢？我们可以发现，我们最后更新答案时是用**最小值**，但我们要求的时这些**最小值的最大值**。于是可以很自然地想出先预处理出所有的边，再**从大到小**排序，再暴力枚举，如果这条边的两个端点与一个其他的点在**之前遍历的边**中有连线，直接输出这条边的长度除以二，即使最大值。

但这还不是 $n^3$ ？别慌，我们可以发现，之前的那个条件判断可以用 `bitset` 来维护，那么时间复杂度就骤降到 $O(\frac{n^3}{w})$~~（好像也不是骤降）~~。于是，便有如下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 3e3 + 5;
int x[inf], y[inf], n, cnt;
bitset <inf> tong[inf];
struct node {
	int x, y, len;
	inline bool operator < (const node & asdf) const { //从大到小排序 
		return len > asdf.len;
	}
} a[inf * inf];
int f(int x) { return x * x; } //平方函数 
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d %d", &x[i], &y[i]);
	for (int i = 1; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			a[++cnt].x = i; //加边 
			a[cnt].y = j;
			a[cnt].len = f(x[i] - x[j]) + f(y[i] - y[j]);
		}
	}
	stable_sort(a + 1, a + 1 + cnt);
	for (int i = 1; i <= cnt; ++i) {
		tong[a[i].x][a[i].y] = 1, tong[a[i].y][a[i].x] = 1; //把这条边在 bitset 中连起来 
		if ((tong[a[i].x] & tong[a[i].y]).count()){ //判断是否有点可以连接 
			printf("%.20Lf", sqrt((long double) a[i].len) / 2); //输出答案 
			return 0;
		}
	}
	return 0;
} 
```

---

## 作者：zzw4257 (赞：0)

评分`2500`,**未**看题解

看着题意简单然后就做了结果真的水？？

收藏一道扫了一眼体面觉得很奇怪的题[CF925](https://www.luogu.com.cn/problem/CF925E)翻译估计是错了

> 在一个平面内给出$n$个点的坐标，任选其中三个为圆心作半径相同的圆，要求这三个圆不能相交但可以相切，求能画出的圆中的最大半径。

 换一下说法

> 给你一些点，求这些点中所有合法三角形(可共线)的最短边最大值

考虑边数是刚刚好在范围内的

不如枚举这条最短边$x\rightarrow y$，考虑只要对$x,y$存在一个点$z$,$x\rightarrow z,y\rightarrow z\geqslant x\rightarrow y$即可

换句话说从大到小枚举边$x\rightarrow y$若$x,y$有一个相同端点则可行，否则加入集合

$bitset$即可

```cpp
sort(q+1,q+tot+1);
for(i=1;i<=tot;++i){
    if((vis[x=q[i].x]&vis[y=q[i].y]).any())return printf("%.10lf\n",sqrt(q[i].len)/2.),0;
    vis[x].set(y),vis[y].set(x);
}
```


---

## 作者：DengDuck (赞：0)

题目含义不多阐述。

显然，在本题中，对于任意三点，半径最大可以是三点中最近的两点的距离的一半。

我们考虑建成一个图，点两两连边。

我们可以想到这样一个方法：按照边的长度从大到小枚举边，假设这个边是三条边中的最短一条，然后看看是否合法。

如何判断呢？设边的两个点是 $x$ 和 $y$,我们可以找找有没有一个点 $z$ 使得 $xy \leq xz$ 且 $xy\leq yz$。如果有的话，当前的边就是合法的。

这样我们要枚举一条边和一个点，效率太低了，时间复杂度 $O(n^3)$,会时间超限，如何优化呢？

我们稍微改一下，我们再搞一个图(称之为复制图)，点的位置和原图一样，但是不连边。

然后还是按照边的长度从大到小枚举边，枚举到某一边时，就复制图中连上对应的边。

这样有什么好处？我们想想，对于枚举到的某一条边，比它大的边恰好都在复制图，我们只需看看在复制图中，该边的两个端点 $x$ 和 $y$ 是否有 $z$ 使得 $x$ 和 $z$ , $y$ 和 $z$ 都有边相连。

这不还是要枚举 $z$ 吗？别急，想一下，我们用邻接矩阵表示复制图中点与点是否相连(注意只保存是否相连，所以是 01 矩阵)，然后将边的两个端点对应的两行求与运算，看看是否有 1。 

显然，如果有 1，就说明存在上述的点 $z$，该边合法。

这个邻接矩阵可以用 `bitset`，这样复杂度更加优秀, 应该是 $O(\frac{n^3}{w})$ 的，为什么会这样这里不作解释，可以自行了解 `bitset`。

贴一下我的代码，码风比较丑。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	long long s,t;//边的起点和重点
	double w;
}a[5000005];
long long n,x[3005],y[3005],t;
bitset<3005>b[3005];
double cal(long long a,long long b)//求编号为a，b的两点的距离
{
	return sqrtl(1.0*(x[a]-x[b])*(x[a]-x[b])+1.0*(y[a]-y[b])*(y[a]-y[b]));
}
void add(long long x,long long y,double w)
{//加边
	t++;
	a[t].s=x;
	a[t].t=y;
	a[t].w=w;
}
bool cmp(node a,node b)
{
	return a.w<b.w;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
		for(int j=1;j<i;j++)
		{
			add(i,j,cal(i,j));
			//cout<<cal(i,j)<<endl; 
		} 
	}
	sort(a+1,a+t+1,cmp);
	for(int i=t;i>=1;i--)
	{
		b[a[i].s][a[i].t]=1;
		b[a[i].t][a[i].s]=1;
		if((b[a[i].t]&b[a[i].s]).count())
		{
			printf("%.10lf",a[i].w/2);
			return 0; 
		} 
	}	
	cout<<0<<endl;
} 
```

---

## 作者：Others (赞：0)

这题很有技巧。

首先是求最大的圆的半径，因为这里没有边界，所以圆的半径只与三个点间的距离相关，用心想想当两个圆相切时半径肯定最大，而三点间有三个距离，我们肯定取最小的。

然后就是哪三个点，看到 $n$ 的范围是 $n\le3000$，所以先想到的肯定是 $O(n^2)$，就是枚举两个点然后决定第三个点，因为第三个点不确定，所以三个点间最短距离我们期望是确定的两点间的最短距离，这要求第三个点和这两个点的距离均大于这两个点的距离，而且我们需要快速地求出第三个点存不存在（小于 $O(n)$）。

我们将每两个点间的距离预处理，然后从大到小枚举，每次将两个点互相连边，在枚举到一条边时就只需要判断之前有没有一个点同时与这两个点连边，这东西我们维护一个 `bitset` 来优化一个 $w$。

总时间复杂度 $O(\frac{n^3}{w})$。

**code**

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=3001;
struct Node{
	int x, y;
	inline int get_long(const Node &p)const{return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);}
}a[3005];
struct node{
	int x, y, z;
	inline bool operator<(const node &p)const{return z > p.z;}
};
vector<node> vec;
int n;
bitset<3005> edge[3005],tmp;
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d", &a[i].x, &a[i].y);
		for(int j = i - 1; j; j--){
			vec.push_back(node{i, j, a[i].get_long(a[j])});
		}
	}
	stable_sort(vec.begin(), vec.end());
	for(auto &p: vec) {
		edge[p.x][p.y] = 1, edge[p.y][p.x] = 1;
		if((edge[p.x]&edge[p.y]).any()) {
			printf("%.20lf", sqrt(p.z) / 2.0);
			return 0;
		}
	}
	return 0;
}

```

---

