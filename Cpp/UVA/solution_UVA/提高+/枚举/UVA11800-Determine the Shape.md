# Determine the Shape

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=226&page=show_problem&problem=2900

[PDF](https://uva.onlinejudge.org/external/118/p11800.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11800/a432d36e486b05289dc5e158f596f11b15abc707.png)

## 样例 #1

### 输入

```
6
0 0
2 0
2 2
0 2
0 0
3 0
3 2
0 2
0 0
8 4
5 0
3 4
0 0
2 0
3 2
1 2
0 0
5 0
4 3
1 3
0 0
5 0
4 3
1 4```

### 输出

```
Case 1: Square
Case 2: Rectangle
Case 3: Rhombus
Case 4: Parallelogram
Case 5: Trapezium
Case 6: Ordinary Quadrilateral```

# 题解

## 作者：Onana_in_XMFLS (赞：2)

![](https://cdn.luogu.com.cn/upload/image_hosting/vqbqlzb4.png)

**前言：呜呜呜孩子一道计算几何蓝题调了两天，实在是太可怜了，我一定要写篇题解来帮助和我一样的可怜人QwQ。**

**Part 0:题意**

给定坐标系中的**四**个点，判断这四个点能组成怎样的四边形（**正方形、矩形、菱形、平行四边形、梯形、普通四边形**）。

**Part1:思路**

只要学过初二几何的肯定都知道，**矩形和菱形都是特殊的平行四边形**，而**正方形又是缝合了矩形和菱形的缝合怪**，所以我们就找到了第一部分的分类，把平行四边形和非平行四边形先区分开来。

怎么区分呢？

这里我选择的是平行四边形的一条判定：**平行四边形的两组对边分别相等**。所以我们只需要找到两组对边，再判相等即可。

可对边如何找呢？

我们如果把输入的四个点编号为 $A$、$B$、$C$、$D$ 的话，我们就可以发现，一个四边形，包括对角线，就只有三种组合情况： $AB-CD$、$AC-BD$、$AD-BC$ 这样我们只要逐一枚举，除去相交的一组是对角线外，其他的就是两组对边啦！`

代码如下

```cpp

double ab = Distance(A,B),ac = Distance(A,C),ad = Distance(A,D);
double cd = Distance(C,D),bd = Distance(B,D),bc = Distance(B,C);
int ABCD = 0,ACBD = 0,ADBC = 0;
if(Cross_segment(A,B,C,D)) ABCD = 1;
if(Cross_segment(A,C,B,D)) ACBD = 1;
if(Cross_segment(A,D,B,C)) ADBC = 1; 
if((ABCD && ac == bd && ad == bc) //平行四边形
          || (ACBD && ab == cd && ad == bc)
          || (ADBC && ab == cd && ac == bd)) 
```
这样我们便区分开来了平行四边形与非平行四边形。

之后非平行四边形的处理便非常简单啦，梯形有一组对边互相平行，所以我们只要枚举上文提到的三组边是否平行即可，平行函数可借助叉积完成（具体见下文完整代码）。

之后便是平行四边形内的具体判断,具体见流程图（~~用 ppt 画的，很丑勿喷~~）

![](https://cdn.luogu.com.cn/upload/image_hosting/mnpj73p8.png)。

**Part 3：代码**

```cpp
#include <bits/stdc++.h>
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
#define mem(arr,val) memset((arr),(val),(sizeof(arr)))
#define INT vector<int>
using namespace std;
const double eps = 1e-8;
const int INF = 0x3f3f3f;
inline int sgn(int x) {return !x?0:(x<0?-1:1);}
struct Point
{
    int x,y;
    Point(){}
    Point(int x,int y):x(x),y(y){}
    Point operator+(const Point p) {return Point(x+p.x,y+p.y);}
    Point operator-(const Point p) {return Point(x-p.x,y-p.y);}
};
typedef Point Vector;
inline double Distance(Point A,Point B) {return hypot(A.x-B.x,A.y-B.y)*hypot(A.x-B.x,A.y-B.y);}
inline int Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y;}
inline int Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
inline bool Parallel(Vector A,Vector B) {return !Cross(A,B);}
inline bool Cross_segment(Point a,Point b,Point c,Point d)
{
    int c1 = Cross(b-a,c-a),c2 = Cross(b-a,d-a);
    int d1 = Cross(d-c,a-c),d2 = Cross(d-c,b-c);
    return sgn(c1)*sgn(c2) <= 0 && sgn(d1)*sgn(d2) <= 0;
}
int main(int argc,char *argv[])
{
    // freopen("sb.txt","r",stdin);
    // ios::sync_with_stdio(false);
    // cin.tie(NULL),cout.tie(NULL);
    int T,i = 0;cin>>T;
    while(T--)
    {
        Point A,B,C,D;
        scanf("%d%d%d%d%d%d%d%d",&A.x,&A.y,&B.x,&B.y,&C.x,&C.y,&D.x,&D.y);
        double ab = Distance(A,B),ac = Distance(A,C),ad = Distance(A,D);
        double cd = Distance(C,D),bd = Distance(B,D),bc = Distance(B,C);
        int ABCD = 0,ACBD = 0,ADBC = 0;
        if(Cross_segment(A,B,C,D)) ABCD = 1;
        if(Cross_segment(A,C,B,D)) ACBD = 1;
        if(Cross_segment(A,D,B,C)) ADBC = 1; 
        if((ABCD && ac == bd && ad == bc) //平行四边形
        || (ACBD && ab == cd && ad == bc)
        || (ADBC && ab == cd && ac == bd)) 
        {
            if(ab == cd && ac == bd && ad == bc) //矩形
            {
                if((ABCD && !Dot(B-A,D-C)) || (ACBD && !Dot(C-A,D-B)) || (ADBC && !Dot(D-A,C-B))) printf("Case %d: Square\n",++i);
                else printf("Case %d: Rectangle\n",++i);
            } 
            else
            {
                if((ABCD && !Dot(B-A,D-C)/*判断90度*/) || (ACBD && !Dot(C-A,D-B)) || (ADBC && !Dot(D-A,C-B))) printf("Case %d: Rhombus\n",++i);
                else printf("Case %d: Parallelogram\n",++i);
            }
        }
        else
        {
            if(Parallel(B-A,D-C) || Parallel(C-A,D-B) || Parallel(D-A,C-B)) printf("Case %d: Trapezium\n",++i);
            else printf("Case %d: Ordinary Quadrilateral\n",++i);
        }
        
    }
    return 0;
}
```
完结撒花！

~~这篇题解很用心地写了，管理求过，观者求赞awa。~~

---

## 作者：__Octhyccc__ (赞：0)

好，翻了翻题解区没一个比我的代码更长，不过爆切计算几何真的很爽！

题意：在平面直角坐标系中给定 $4$ 个点，保证任意其中 $3$ 个点不在一条直线上，求这 $4$ 个点构成了哪种四边形。

看到这道题，我立马想到了任意 $2$ 点之间连线，有 $C_4^2=6$ 条线段，其中 $4$ 条为这个四边形的边，另外 $2$ 条构成了对角线。

考虑将这 $6$ 条线段所在的直线转化成解析式的形式，以一条经过 $(s,t),(m,n)$ 的直线为例。

将 $(s,t),(m,n)$ 带入 $y=kx+b$ 中：

$$\begin{cases}
  t=sk+b &A \\n=mk+b &B
\end{cases}$$

$A-B$：

$$t-n=(s-m)k$$

求出 $k$：

$$k=\bigg(\frac{t-n}{s-m}\bigg)$$

将 $k$ 带入后得出 $b$：

$$b=t-s\bigg(\frac{t-n}{s-m}\bigg)$$

注意，对于常数函数（$y=q,q\in \Reals$）以及 $x=q,q\in \Reals$ 这类的应该特判。

这部分代码（最重要的）：

```cpp
cfunction construct(point x1,point x2,int x3,int x4){//x3,x4 为点的编号
	if(x1.x!=x2.x && x1.y!=x2.y){
		pair<ll,ll>f,b;
		f.first=x1.y-x2.y;
		f.second=x1.x-x2.x;
		f=fsh(f);
		b=fsminu({x1.y,1},fstimes({x1.x,1},f));
		return (cfunction){0,f,b,x3,x4,distance(x1,x2)};
	}
	else if(x1.x==x2.x)return (cfunction){1,{INT_MAX-1,INT_MAX-1},{x1.x,1},x3,x4,distance(x1,x2)};
	else return (cfunction){2,{INT_MAX-1,-INT_MAX+1},{x1.y,1},x3,x4,distance(x1,x2)};
}
```

上文出现了分数，我为了不掉精度特意写了一个分数库。所以导致码量很大。

然后求出每条边的边长，比较一下有多少不同的边长（两点间距离公式是 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$），并且浮点数的比较最好不要直接用 `==`。应该定义一个 $eps=10^{-5}$，看看它们俩的差是否超过该值。

当只有 $2$ 种不同的边长时，一定是正方形（即 $4$ 条边长相等和 $2$ 条对角线相等）。

当有 $3$ 种不同的边长时：

大乱炖。除了正方形啥都有。

- 菱形其中 $4$ 条边相等，如果发现在这 $6$ 条边中有 $4$ 条相等，那一定是菱形。

- 所有的长方形。具体判断方法是有 $2$ 组边互相平行，对边相等。但是有特殊的反例。如下图的平行四边形（在正常时平行四边形有 $4$ 个不同边长）：

![](https://cdn.luogu.com.cn/upload/image_hosting/7w9ezhfu.png)

可以发现虽然有 $3$ 种不同的边长，但是不是长方形。

判断方法：

取 $3$ 个顶点，分别检查这 $3$ 个顶点相连的边是否有相等的情况，有就是平行四边形，没有就是长方形（当然全验一遍当然没有问题）。

- 特殊的梯形，方法和上文类似，不过只有 $1$ 组边互相平行罢了。

- 平行四边形讲过了。

- 其余的为普通四边形。

当有 $4$ 种不同的边时：

- 平行四边形，验证一下是否有 $2$ 组边互相平行即可。

- 等腰梯形，只需要 $1$ 组。

- 其余的为普通四边形。

当有 $5$ 或 $6$ 种时：

- 梯形，$1$ 组平行即可。

- 普通四边形。

验证两条边平行，就是看他们所在的直线的解析式中 $k$（即斜率）是否相等。

至此，你已经 AC 了此题。

代码（有很多无用注释，Debug 用的）：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double eps=1e-4;
namespace frac{
	//typedef string str;
	ll lcm(ll a,ll b){return a*b/__gcd(a,b);}
	bool fscmp(pair<ll,ll>x,pair<ll,ll>y){
		ll a=lcm(x.second,y.second);
		if(x.first*(a/x.second)>=y.first*(a/x.second))return 1;
		else return 0;
	}
	pair<ll,ll> fsh(pair<ll,ll>x){
		return {x.first/__gcd(x.first,x.second),x.second/__gcd(x.first,x.second)};
	}
	pair<ll,ll> fsplus(pair<ll,ll>x,pair<ll,ll>y){
		ll a=lcm(x.second,y.second);
		x.first*=a/x.second;
		y.first*=a/y.second;
		ll b=x.first+y.first;
		pair<ll,ll>f=make_pair(b,a);
		f.first/=__gcd(f.first,f.second);
		f.second/=__gcd(f.first,f.second);
		return f;
	}
	pair<ll,ll> fsminu(pair<ll,ll>x,pair<ll,ll>y){
		ll fz=x.first*y.second-x.second*y.first;
		ll fm=x.second*y.second;
		pair<ll,ll>f=make_pair(fz,fm);
		return fsh(f);
	}
	pair<ll,ll> fstimes(pair<ll,ll>x,pair<ll,ll>y){
		ll a=__gcd(x.first*y.first,x.second*y.second);
		pair<ll,ll>f;
		f.first=x.first*y.first/a;
		f.second=x.second*y.second/a;
		return f;
	}
	pair<ll,ll> fsdiv(pair<ll,ll>x,pair<ll,ll>y){
		swap(y.first,y.second);
		return fstimes(x,y);
	}
	pair<ll,ll>fsqdiv(pair<ll,ll>x,ll y){
		y*=x.second;
		ll c=x.first/y;
		pair<ll,ll>f1={x.first-c*y,x.second};
		ll a=__gcd(f1.first,f1.second);
		if(a==0)a=1;
		return {f1.first/a,f1.second/a};
	}
	ll fsceil(pair<ll,ll>x){
		pair<ll,ll>f1=fsqdiv(x,1);
		x.first+=f1.first;
		return x.first/x.second;
	}
}
using namespace frac;
struct cfunction{
	int k1;
	pair<ll,ll> k,b;//y=kx+b;
	int pointidx,pointidy;
	double dist;
	bool intersect(cfunction x,cfunction y){
		return x.k!=y.k;
	}
	bool angle(cfunction x,cfunction y){
		pair<ll,ll>f=fstimes(x.k,y.k);
		if(f.first==-1 && f.second==1)return 1;
		else return 0;
	}
	friend bool operator<(cfunction x,cfunction y){
		return x.dist<y.dist;
	}
}fu[7];
struct point{
	ll x,y;
}p[4];
struct line{
	int pointidx,pointidy;
	double dist;
	friend bool operator<(line xxx,line yyy){
		return xxx.dist<yyy.dist;
	}
}l[6];
double distance(point x1,point y2){
	return sqrt((x1.x-y2.x)*(x1.x-y2.x)+(x1.y-y2.y)*(x1.y-y2.y));
}
vector<line>v[4];
cfunction construct(point x1,point x2,int x3,int x4){
	if(x1.x!=x2.x && x1.y!=x2.y){
		pair<ll,ll>f,b;
		f.first=x1.y-x2.y;
		f.second=x1.x-x2.x;
		f=fsh(f);
		b=fsminu({x1.y,1},fstimes({x1.x,1},f));
		return (cfunction){0,f,b,x3,x4,distance(x1,x2)};
	}
	else if(x1.x==x2.x)return (cfunction){1,{INT_MAX-1,INT_MAX-1},{x1.x,1},x3,x4,distance(x1,x2)};
	else return (cfunction){2,{INT_MAX-1,-INT_MAX+1},{x1.y,1},x3,x4,distance(x1,x2)};
}
bool equal(double x,double y){
	if(x+eps>=y && y+eps>=x)return 1;
	else return 0;
}
/*bool square(){
	int k2=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			for(int p=j+1;p<3;p++){
				if(equal(v[i][j].dist,v[i][p].dist))k2++;
			}
		}
		if(k2!=1)return 0;
		k2=0;
	}
}*/
map<pair<ll,ll>,int>m;
vector<int>dif;
void be(){
	dif.clear();
	m.erase(m.begin(),m.end());
	for(int i=0;i<4;i++){
		v[i].clear();
	}
	return;
}
int main(){
	//freopen("x.in","r",stdin);
	//freopen("x.out","w",stdout);
	ll t,f=0;
	scanf("%lld",&t);
	while(t--){
		int use=0;
		for(int i=0;i<4;i++)scanf("%lld %lld",&p[i].x,&p[i].y);
		//cout<<"E";
		for(int i=0;i<4;i++){
			for(int j=i+1;j<4;j++){
				//cout<<"E";
				fu[use]=construct(p[i],p[j],i,j);
				//cout<<fu[use].k.first<<" "<<fu[use].k.second<<"\n";
				//cout<<"E";
				l[use]={i,j,distance(p[i],p[j])};
				use++;
			}
		}
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(i!=j)v[i].push_back((line){i,j,distance(p[i],p[j])});
			}
		}
		sort(l,l+6);sort(fu,fu+6);
		/*
		for(int i=0;i<6;i++){
			//cout<<l[i].dist<<" ";
			cout<<fu[i].k1<<" ";
		}
		puts("");
		*/
		int t=1;
		for(int i=1;i<6;i++){
			if(equal(l[i].dist,l[i-1].dist))t++;
			else{
				dif.push_back(t);
				t=1;
			}
			//printf("%.6f %.6f\n",l[i].dist,l[i-1].dist);
		}
		dif.push_back(t);
		//printf("%d\n",dif.size());
		if(dif.size()==2 && dif[0]==4 && dif[1]==2){
			printf("Case %d: Square\n",++f);be();
			continue;
		}
		else if(dif.size()==3){
			//特殊的普通四边形，长方形，菱形，特殊平行四边形，特殊等腰梯形 
			bool j=0;
			for(int i=0;i<3;i++){
				if(dif[i]==4){
					printf("Case %d: Rhombus\n",++f);
					j=1;
				}
			}
			if(j){be();continue;}
			int px=0;
			for(int i=0;i<6;i++){
				for(int j=i+1;j<6;j++){
					if((fu[i].k1==1 && fu[j].k1==1) || (fu[i].k1==2 && fu[j].k1==2) || (fu[i].k==fu[j].k))px++;
					//cout<<fu[i].k.first<<" "<<fu[i].k.second<<"\n";
					//cout<<fu[j].k.first<<" "<<fu[j].k.second<<"\n";
				}
				//cout<<fu[i+1].k.first<<" "<<fu[i+1].k.second<<"\n";
			}
			//cout<<px<<'\n';
			if(px==1)printf("Case %d: Trapezium\n",++f);
			else if(px>=2){
				bool fff=0;
				for(int i=0;i<4;i++){
					if(equal(v[i][0].dist,v[i][1].dist) || equal(v[i][1].dist,v[i][2].dist) || equal(v[i][2].dist,v[i][0].dist)){
						printf("Case %d: Parallelogram\n",++f);
						fff=1;break;
					}
				}
				if(!fff)printf("Case %d: Rectangle\n",++f);
			}
			else printf("Case %d: Ordinary Quadrilateral\n",++f);
		}
		else if(dif.size()==4){
			for(int i=0;i<6;i++){
				m[fu[i].k]++;
				//cout<<fu[i].k.first<<" "<<fu[i].k.second<<"\n";
			}
			int gs=0;
			for(map<pair<ll,ll>,int>::iterator it=m.begin();it!=m.end();++it){
				if(it->second==2)gs++;
			}
			if(gs==2)printf("Case %d: Parallelogram\n",++f);
			else if(gs==1)printf("Case %d: Trapezium\n",++f);
			else printf("Case %d: Ordinary Quadrilateral\n",++f);
		}
		else{
			for(int i=0;i<6;i++)m[fu[i].k]++;
			int gs=0;
			for(map<pair<ll,ll>,int>::iterator it=m.begin();it!=m.end();++it){
				if(it->second==2)gs++;
			}
			if(gs==1)printf("Case %d: Trapezium\n",++f);
			else printf("Case %d: Ordinary Quadrilateral\n",++f);
		}
		be();
	}
	return 0;
}
```

---

## 作者：walk_alone (赞：0)

首先说一下这题的大致思路：

1.调整点的顺序

2.按照“平行四边形->菱形/矩形->正方形”的顺序进行判断。（因为这个顺序是存在包含关系的，例如是正方形一定是矩形/菱形，也一定是平行四边形）

首先来说第一个难点：调整点的顺序

有以下三种点的顺序

![](https://cdn.luogu.com.cn/upload/image_hosting/q7h13dy9.png)

![完全倒序](https://cdn.luogu.com.cn/upload/image_hosting/xaukhak1.png)

![部分倒序](https://cdn.luogu.com.cn/upload/image_hosting/43hwgwv8.png)

首先来观察一下这三个图的特征：

第一个图就是我们想要的顺序，对角线AC与BD交叉；

第二个图是AB这条边都不存在了，AC与BD不交叉；

第三个图就是CD顺序反了，AC与BD不交叉。

为什么我想到了交叉这个判断条件呢？是因为这个题中四边形可以认为是凸四边形（凹四边形可以转化过来，下文会说），而没有任何其他的条件。所以只有交叉条件是所有点序正确的凸四边形都满足的条件。

所以，**第一步就是判断AC是否与BD交叉**，来筛选出第一种图来。

那如何区分下面两个图呢？

显然我们可以考虑交换BD两点（此处也可交换CD两点，同理可得），这样第二个图就变成了第一个图，而第三个图因为BD等价而没有改变。因此交换完BD之后继续判断AC与BD是否相交。这样就筛选出了第二张图。最后只能的第三种只需要将CD两点交换即可。（同理就是BD）

那么怎么判断相交呢？

这里我采用的方法是向量叉积。（作为一只大一萌新自学了一点点高数发现了这个方法）

**向量叉积是不满足交换律的**。这是这个不成熟方法的核心。

例如：$\vec{a} \times \vec{b}=-\vec{b} \times \vec{a}$。这是因为叉积运算结果仍然为向量，垂直于两向量决定的平面，方向朝上朝下是由右手定则决定，顺时针旋转为正，逆时针旋转为负，因此乘的顺序决定方向，在坐标运算中，我们得到的是这个向量的模或者其相反数，正则朝上负则朝下。

所以考察以下情况：

1.

![](https://cdn.luogu.com.cn/upload/image_hosting/uv5mf8y4.png)

此时AC与BD两线段交叉，那么$\vec{AC} \times \vec{AD}$与$\vec{AC} \times \vec{AB}$的正负性是相反的（注意我乘的顺序）。因为$\vec{AC}$是顺时针转向$\vec{AD}$，而$\vec{AC}$是逆时针转向$\vec{AB}$，所以得到的两个数正负性相反。

2.
![](https://cdn.luogu.com.cn/upload/image_hosting/cw5kxsjx.png)

此时AC与BD不相交。$\vec{AC}$是逆时针转向$\vec{AD}$，而$\vec{AC}$也是逆时针转向$\vec{AB}$，所以同正同负。

但是这会有例外，而这也是凹四边形的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/exqqvky2.png)

首先这种情况不可能是凸四边形了，按题意应该是Orinary Quadrilateral。但是输入的时候并不知道凹凸性。于是也是要进行调整点顺序的。这里规定**C在中央的顺序**为正。(不是随意规定的)

如果我们按照刚刚的方法，我们会得出：AC与BD相交。因为这与图一完全一样，只是AC的长度发生了变化。其实有方法可以排除，但是这里是没有必要的。

如果不是标准情况呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/3wfg4yq8.png)

AC与BD“不相交”了，于是交换BD，依旧不相交，交换CD，回到正序。D在中央同理。所以这个不完美的方法适用于所有四边形。

接下来就是第二步，判断四边形。

首先在这里找到各个四边形的特征：

平行四边形：一组对边平行且相等，即$\vec{AB}=\vec{DC}$

梯形：只有一组对边平行，即$\vec{AB}=\lambda\vec{CD}$ 或 $\vec{AD}=\lambda\vec{BC}$

菱形：平行四边形基础上再有对角线垂直，即$\vec{AC}\cdot\vec{BD}=0$

矩形：有一个角是直角，即$\vec{AB}\cdot\vec{AD}=0$

正方形：在菱形基础上再有一个角是直角，或在矩形基础上对角线垂直。本文采用前者。

那么向量平行怎么办呢？还是向量叉积！

向量叉积的定义式是：$\vec{a} \times \vec{b}=|\vec{a}|\cdot|\vec{b}|\cdot sin\theta$。平行时$\theta$为0或$\pi$，$sin\theta=0$，所以叉积为0。

判断的时候，只需先判断对边平行且相等，不成立的话判断对边平行，再次不成立就是普通四边形，成立就是梯形；平行四边形先判断对角线垂直，成立继续判断直角，成则正方形不成则菱形；之后判断直角，成就是矩形不成就是平行四边形。

对于凹四边形，显然不会出现平行，于是在上述流程中会被归入普通四边形中。

剩下的就是惊天大模拟了。

附带几个坐标运算公式：

向量点积：$(x_1,y_1)\cdot(x_2,y_2)=x_1x_2+y_1y_2$

向量叉积（可以用来计算三角形面积）：$(x_1,y_1) \times (x_2,y_2)=x_1y_2-x_2y_1$

剩下就是惊天大模拟了，代码如下，思路完全按照上述在走，因而偷懒不写批注了。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
    long long x;
    long long y;
};
struct node A,B,C,D;
struct vec
{
    long long x;
    long long y;
};
vec cal(node a,node b)
{
    vec now;
    now.x=b.x-a.x;
    now.y=b.y-a.y;
    return now;
}
long long operator *(vec a,vec b)
{
    return a.x*b.y-a.y*b.x;
}
long long operator /(vec a,vec b)
{
    return a.x*b.x+a.y*b.y;
}
bool is_equal(vec a,vec b)
{
    if(a.x==b.x && a.y==b.y)
        return 1;
    if(a.x+b.x==0 && a.y+b.y==0)
        return 1;
    return 0;
}
bool is_parallel(vec a,vec b)
{
    if(a*b==0)
        return 1;
    return 0;
}
int main()
{
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    for(int o=1;o<=t;o++)
    {
        scanf("%lld%lld%lld%lld%lld%lld%lld%lld",&A.x,&A.y,&B.x,&B.y,&C.x,&C.y,&D.x,&D.y);
        printf("Case %d: ",o);
        vec AC=cal(A,C);
        vec AB=cal(A,B);
        vec AD=cal(A,D);
        if((AC*AD)*(AC*AB)>0)
        {
            swap(B,C);
            AC=cal(A,C);
            AB=cal(A,B);
            AD=cal(A,D);
            if((AC*AD)*(AC*AB)>0)
                swap(C,D);
        }
        AB=cal(A,B);
        AD=cal(A,D);
        vec CD=cal(C,D);
        vec BC=cal(B,C);
        if(is_equal(AB,CD))
        {
            AC=cal(A,C);
            vec BD=cal(B,D);
            if(AC/BD==0)
            {
                if(AB/AD==0)
                    printf("Square\n");
                else
                    printf("Rhombus\n");
            }
            else
            {
                if(AB/AD==0)
                    printf("Rectangle\n");
                else
                    printf("Parallelogram\n");
            }
        }
        else
        {
            if(is_parallel(AB,CD) || is_parallel(AD,BC))
                printf("Trapezium\n");
            else
                printf("Ordinary Quadrilateral\n");
        }
    }
    return 0;
}
```


---

## 作者：throusea (赞：0)

计算几何的入门题。

~~大家应该学过了平行四边形了吧。~~（默认已经会二维计算几何了）

判定方法如下：

1. 平行四边形： 对角线互相平分或者用定义。

2. 梯形： 有一组对边平行，一组对边不平行。

   在已知平行四边形的情况下

3. 矩形： 对角线长度相等或用定义。

4. 菱形： 对角线互相垂直（数量积为0）或用定义。

5. 正方形： 即是矩形又是菱形。

题目只是给你几个点的坐标，并不知道那些点能组成对角线。所以枚举组合加上两线段是否相交的判定即可。

找到那两条对角线后，就可以~~随便乱搞~~用上面的判定了。

我用的主要是对角线的判定。坐标虽然只有（-10000～10000），但WA的经历告诉我要开long long.

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#define LL long long
using namespace std;
struct Point {
    int x,y;
    Point(int x=0,int y=0) : x(x),y(y) { }
};

typedef Point Vector;

Point p[5];
int a[5];
string s[] = {"Ordinary Quadrilateral","Trapezium","Parallelogram","Rhombus","Rectangle","Square"};

Vector operator + (Vector A,Vector B) {
    return Vector(A.x+B.x,A.y+B.y);
}

Vector operator - (Point A,Point B) {
    return Vector(A.x-B.x,A.y-B.y);
}

bool operator == (Point A,Point B) {
    return A.x == B.x && A.y == B.y;
}

LL Cross(Vector A,Vector B) {
    return (LL)A.x*B.y - A.y*B.x;
}

LL Dot(Vector A,Vector B) {
    return (LL)A.x*B.x + A.y*B.y;
}

LL dis(Point A,Point B) {
    return (LL)(A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}

bool intersection(Point a1,Point a2,Point b1,Point b2) {
    LL c1 = Cross(a1-a2,b1-a2),c2 = Cross(a1-a2,b2-a2),
        c3 = Cross(b1-b2,a1-b2),c4 = Cross(b1-b2,a2-b2);
    return (LL)c1 * c2 < 0 && c3 * c4 < 0;
}

bool para(Vector A,Vector B) {
    return A.x * B.y == A.y * B.x;
}

int main() {
    int T,Case = 0;
    scanf("%d",&T);
    while(T--) {
        int shape;
        for(int i = 1; i <= 4; i++)
        scanf("%d%d",&p[i].x,&p[i].y);
        if(intersection(p[1],p[2],p[3],p[4])) {
            a[1] = 1; a[2] = 2; a[3] = 3; a[4] = 4;
        }
        if(intersection(p[1],p[3],p[2],p[4])) {
            a[1] = 1; a[2] = 3; a[3] = 2; a[4] = 4;
        }
        if(intersection(p[1],p[4],p[2],p[3])) {
            a[1] = 1; a[2] = 4; a[3] = 2; a[4] = 3;
        }
        // 对角线
        if(p[a[1]] + p[a[2]] == p[a[3]] + p[a[4]]) {
            shape = 2;
            if(Dot(p[a[2]]-p[a[1]],p[a[4]]-p[a[3]]) == 0)
            shape = 3;
            if(dis(p[a[1]],p[a[2]]) == dis(p[a[3]],p[a[4]]))
            if(shape == 3) 
              shape = 5;
            else shape = 4;
            // 平行四边形部分
        }else {
            if(para(p[a[1]]-p[a[3]],p[a[2]]-p[a[4]]) || para(p[a[1]]-p[a[4]],p[a[2]]-p[a[3]]))
              shape = 1;
            else shape = 0;
            // 非平行四边形
        }
        printf("Case %d: ",++Case);
        cout<<s[shape]<<endl;
    }
    return 0;
}
```

---

