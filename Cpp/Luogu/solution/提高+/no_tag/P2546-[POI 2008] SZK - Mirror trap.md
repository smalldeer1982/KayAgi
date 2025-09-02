# [POI 2008] SZK - Mirror trap

## 题目描述

$N$ 个点的多边形相邻边垂直，边长为整数，边平行坐标轴。要在多边形的点上放一些激光发射器和接收器。满足下列要求：

 - 发射器和接收器不能放置在同一点；
 - 发射器发出激光可以沿壁反射，最终到达一个接收器；
 - 发射器只能沿角平分线发射激光。

求：最多可放置多少对发射器和接收器？$4\leq N\leq 10^5$，**多边形周长不超过 $3\times 10^5$**。

## 样例 #1

### 输入

```
10
1 1
3 1
3 -2
-3 -2
-3 0
-1 0
-1 -1
2 -1
2 0
1 0```

### 输出

```
5
10 5
1 7
2 9
3 8
4 6```

# 题解

## 作者：SuperJvRuo (赞：8)

### 第一问

物理题，一个点射出的光线只能射到一个点上，由于光路可逆，所以反过来的点也只有一个。因此答案为$n\div2$。

### 第二问

模拟题，可以模拟出所有的光线得到匹配。先走一遍路记录边上所有的整点坐标。将图逆时针旋转$45\degree$使得正方向与光线平行，按照坐标排序。先以$x$为第一关键字，$y$为第二关键字排序，求出竖直光线；再以$y$为第一关键字，$x$为第二关键字排序，求出竖直光线。

![](http://wx1.sinaimg.cn/mw690/0060lm7Tly1fqtbkapksmg304604ljsa.gif)

最后在图上走路即可。

```
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAX=1e6;

struct point
{
	int x,y,ver,num;
};

bool cmp1(point a,point b)
{
	return a.x!=b.x?a.x<b.x:a.y<b.y;//按旋转后的横坐标排序 
}

bool cmp2(point a,point b)
{
	return a.y!=b.y?a.y<b.y:a.x<b.x;//按旋转后的纵坐标排序 
}

int len[MAX];
int next[MAX][2];
point side[MAX];//边上的点 
int n,m,akt,a,b,c,p;

void make_next(int wh)
{
	std::sort(side,side+n,wh?cmp2:cmp1);
	akt=(-1);
	for(int i=0;i<n;++i)
	{
		if ((side[i].ver>=0)&&((side[i].ver&1)!=wh))
		//发现这个点是顶点 凸的方向与扫的方向不同 
		{
			next[side[i].num][wh]=(-side[i].ver/2-1);//便于输出的一个处理 
			continue;//跳过 
		}
		if (akt<0)
		{
			akt=i;
		}
		else
		{	//可以射过光线，配对 
			next[side[akt].num][wh]=side[i].num;
			next[side[i].num][wh]=side[akt].num;
			akt=(-1);
		}
	}
}

void insert()
{
	side[n].x=a-b;//相当于把图形逆时针旋转了45° 
	side[n].y=a+b;
	side[n].ver=(-1);
	side[n].num=n;
	n++;
}

void find(int fr)
{
	p=fr;
	akt=((next[fr][0]>=0)?0:1);
	while(next[p][akt]>=0)//直到找到一个顶点 
	{
		p=next[p][akt];
		akt^=1;//横竖交替走路 
	}
	p=(next[p][akt]*=(-1));
}

int pp(int k)
{
	return k>=0?k:(m-1);
}

int main()
{
	scanf("%d",&m);
	printf("%d\n",m>>1);
	for(int i=0;i<m;++i)
	{
		scanf("%d %d",&a,&b);
		len[i]=a+b;
	}
	c=len[m-1];
	for(int i=m-1;i>=1;--i)
	{
		len[i]-=len[i-1];
	}
	len[0]-=c;//预处理每条边的长度和方向 
	a=0;
	b=0;
	for(int i=0;i<m;++i)//走路 
	{
		if (i%2)//横向的边 
		{
			if (len[i]>0)//往正方向走路 
			{
				for(int j=0;j<len[i];++j)
				{
					insert();//把点加进去 
					a++;
				}
				side[n-len[i]].ver=((len[pp(i-1)]>0)?(2*i+1):(2*i));
				//根据走路方向加上这个1，表示旋转后这个点向左或右凸出 
				//否则即为向上或下凸 
			}
			else//往负方向走路 
			{
				for(int j=0;j<-len[i];++j)
				{
					insert();
					a--;
				}
				side[n+len[i]].ver=((len[pp(i-1)]<0)?(2*i+1):(2*i));
			}
		}
		else//纵向的边 
		{
			if (len[i]>0)//往正方向走路
			{
				for(int j=0;j<len[i];++j)
				{
					insert();
					b++;
				}
				side[n-len[i]].ver=((len[pp(i-1)]>0)?(2*i+1):(2*i));
			}
			else//往负方向走路 
			{
				for(int j=0;j<-len[i];++j)
				{
					insert();
					b--;
				}
				side[n+len[i]].ver=((len[pp(i-1)]<0)?(2*i+1):(2*i));
			}
		}
	}
	//连光线 
	make_next(0);
	make_next(1);
	for(int i=0;i<n;++i)
	{
		if ((next[i][0]<0)||(next[i][1]<0))//有一个小于0，是顶点 
		{
			find(i);//找到和它唯一对应的顶点 
			printf("%d %d\n",pp(((next[i][0]<0)?(next[i][0]*(-1)):(next[i][1]*(-1)))-2)+1,pp(p-2)+1);
		}
	}
	return 0;
}
```

---

## 作者：Nasaepa (赞：2)

为什么题解区只有一篇题解？我来写一篇。

---

称在输入数据中输入的点为**顶点**。可以确定，多边形上的每一个顶点一定都可以找到另一个顶点与它匹配，且匹配方案唯一。

由于多边形的周长很小，可以直接用数组存储多边形边上的每一个点。

一条光线从一点射向另一点可以看作在图上在这两点之间建无向边。我们可以用 dsu 维护两点的可到达性。如果两个顶点之间是联通的，那么这两个顶点就可以匹配。

把多边形逆时针转 $45^{\circ}$，这样光线会平行于坐标轴。将所有点以 $x$ 为第一关键字，$y$ 为第二关键字排序尝试靠竖的光线连边，再将所有点以 $y$ 为第一关键字，$x$ 为第二关键字排序尝试靠横的光线连边，这样我们就能找到所有匹配。

另外，光线在某些情况下可以从顶点中穿过去而不被接收，例如样例中从 $10$ 号顶点射出的光线穿过了 $8$ 号顶点。这种情况需要特判。具体方法就是求出顶点的朝向然后看顶点在这个朝向能不能接到光。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define N 300010
#define INF 0x3f3f3f3f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
#define cpx complex<double>
#define poly vector<ll>
#define get(x) (x?x:n)
int n,x,y,len[N],la;
struct node{int x,y,v,idx;}a[N];
inline bool cmp(const node &n1,const node &n2){return (n1.x!=n2.x)?n1.x<n2.x:n1.y<n2.y;}
inline bool cmp1(const node &n1,const node &n2){return (n1.y!=n2.y)?n1.y<n2.y:n1.x<n2.x;}
inline void insert(){
    ++la,a[la] = {x-y,x+y,-1,la};
}
int dad[N],dep[N],f[N];
int find(const int &x){return (dad[x]==x?x:(dad[x] = find(dad[x])));}
inline void merge(int x,int y){
    x = find(x),y = find(y);
    if(x == y)return ;
    // printf("merging %d %d\n",x,y);
    if(dep[x]<dep[y])swap(x,y);
    dad[y] = x,dep[x] = max(dep[x],dep[y]+1); 
    if(f[x]&&f[y])cout << f[x] << ' ' << f[y] << "\n";
    else if(f[x]||f[y])f[x] += f[y];
}
inline void solve(const int &op){
    sort(a+1,a+la+1,op?cmp1:cmp);
    int last = 0;
    for(int i = 1;i <= la;++i){
        if((op && a[i].y != a[i-1].y) || (!op && a[i].x != a[i-1].x))last = 0;
        if(a[i].v >= 0 && (a[i].v)!=op)continue;
        if(!last)last = a[i].idx;
        else merge(a[i].idx,last),last = 0;
    }
}

// 主函数
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n;
    for(int i = 1;i <= n;++i)cin >> x >> y,len[i] = x+y;
    int tmp = len[n];
    for(int i = n;i >= 2;--i)len[i] = len[i]-len[i-1];len[1] = len[1] - tmp;
    x = 0,y = 0;
    for(int i = 1;i <= n;++i){
        if(i & 1){// 动 x
            if(len[i] > 0){
                for(int j = 0;j < len[i];++j)insert(),++x;
                a[la-len[i]+1].v = (len[get(i-1)]>0),f[la-len[i]+1] = get(i-1);
            }else{
                for(int j = 0;j < -len[i];++j)insert(),--x;
                a[la+len[i]+1].v = (len[get(i-1)]<0),f[la+len[i]+1] = get(i-1);
            }
        }else{
            if(len[i] > 0){
                for(int j = 0;j < len[i];++j)insert(),++y;
                a[la-len[i]+1].v = (len[get(i-1)]>0),f[la-len[i]+1] = get(i-1);
            }else{
                for(int j = 0;j < -len[i];++j)insert(),--y;
                a[la+len[i]+1].v = (len[get(i-1)]<0),f[la+len[i]+1] = get(i-1);
            }
        }
    }
    cout << (n>>1) << '\n';
    for(int i = 1;i <= la;++i)dad[i] = i,dep[i] = 1;
    a[0] = {-INF,-INF,-INF,-INF};
    solve(0),solve(1);
    return 0;
}
```

---

