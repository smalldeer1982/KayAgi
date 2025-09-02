# [USACO19OPEN] Cow Steeplechase II S

## 题目描述

在过去，Farmer John曾经构思了许多新式奶牛运动项目的点子，其中就包括奶牛障碍赛，是奶牛们在赛道上跑越障碍栏架的竞速项目。他之前对推广这项运动做出的努力结果喜忧参半，所以他希望在他的农场上建造一个更大的奶牛障碍赛的场地，试着让这项运动更加普及。

Farmer John为新场地精心设计了 $ N $ 个障碍栏架，编号为 $ 1 \ldots 
 N $ （ $ 2 \leq N \leq 10^5 $ ），每一个栏架都可以用这一场地的二维地图中的一条线段来表示。这些线段本应两两不相交，包括端点位置。

不幸的是，Farmer John在绘制场地地图的时候不够仔细，现在发现线段之间出现了交点。然而，他同时注意到只要移除一条线段，这张地图就可以恢复到预期没有相交线段的状态（包括端点位置）。

请求出Farmer John为了恢复没有线段相交这一属性所需要从他的计划中删去的一条线段。如果有多条线段移除后均可满足条件，请输出在输入中出现最早的线段的序号。

## 说明/提示

注意：由于线段端点坐标数值的大小，在这个问题中你可能需要考虑整数类型溢出的情况。

## 样例 #1

### 输入

```
4
2 1 6 1
4 0 1 5
5 6 5 5
2 7 1 3```

### 输出

```
2```

# 题解

## 作者：crashed (赞：12)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P5428)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;计算几何第一题，然后~~不负众望地~~爆炸了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考场上一个很简单的优化居然都没有想到......太菜了。    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这道题其实是扫描线+$set$维护。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先，我们来一个预备知识点——线段判交。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看[博客](https://blog.csdn.net/qq_39627843/article/details/81170316)吧。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;有了这个知识之后我们就可以开始题解了。    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们的主要思路就是先找出任意两条相交的线段，此时答案就在两条之间，接下来再搞就容易了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是我们的目标就是优化第一步。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;先对所有的**点**排序，按照$x$优先$y$次后的顺序。然后扫描点的序列。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在这之前，我们得了解这个$set$到底存的什么。简单来说，当当前位置为$pos$时，$set$维护的就是**在x轴的投影上包含了$pos$这个点的不相交线段的集合**。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;所以根据这个原则，我们可以按如下方法维护：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.如果当前的点是一个线段的起点，我们就可以在$set$中找出当前线段相对的前后线段。如果找出的前后线段中的一个和当前线段有交点，就取出相交的一对检查答案；否则就插入当前线段。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.如果当前的点是一个线段的终点，我们先在$set$中找出当前线段的前驱后继。如果找到的两个线段有交点，就取出来检查答案；否则就删除当前线段。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其实所有线段检查的操作都是为了避免在更新后集合中出现相交的线段，把握这一点的话就不难写了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;另外，由于$set$中的线段不相交，所以说**两个在$set$中的线段的上下关系不会变**，我们可以利用这一点来对线段进行排序。   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;图例：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;插入一个线段：  
![insert.png](https://i.loli.net/2019/08/15/JWj4fRnPvN7xb5w.png)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;删除一个线段：  
![delete.png](https://i.loli.net/2019/08/15/TA5p8ijFZn6mOzx.png)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;找出相交：    
![searched.png](https://i.loli.net/2019/08/15/eAGhFZcVdwqzyPW.png)    
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;以及喜闻乐见的代码。  
# 代码
```cpp
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
} 

double pos;

struct point
{
	LL x, y;
	int indx;
	point(){}
	point( const LL X, const LL Y, const int Indx )
	{
		x = X, y = Y;
		indx = Indx;
	}
	bool operator < ( const point & other ) const
	{
		return x < other.x || ( x == other.x && y < other.y );
	}
	bool operator > ( const point & other ) const
	{
		return x > other.x || ( x == other.x && y > other.y );
	}
	point operator - ( const point & other ) const
	{
		return point ( x - other.x, y - other.y, 0 );
	}
}P[MAXN * 2];

struct Vector
{
	LL x, y;
	Vector(){}
	Vector( const LL X, const LL Y )
	{
		x = X, y = Y;
	}
	Vector( const point p )
	{
		x = p.x, y = p.y;
	}
};

struct segment
{
	point l, r;
	int indx;
	double endVal() const 
	{
		if( l.x == r.x ) return l.y;
		return l.y + 1.0 * ( r.y - l.y ) * 1.0 * ( pos - l.x ) / ( r.x - l.x );
	}
	bool operator < ( const segment & other ) const
	{
		return indx != other.indx && endVal() < other.endVal();
	}
	bool operator == ( const segment & other ) const
	{
		return indx == other.indx;
	}
}seg[MAXN];

typedef set<segment> :: iterator iter;

set<segment> s;

int cnt[MAXN];
int N;

LL mul( const Vector & fir, const Vector & sec )
{
	return fir.x * sec.y - fir.y * sec.x;
}

int sign( const LL x )
{
	return ! x ? 0 : ( x < 0 ? -1 : 1 );
}

bool chk( const segment x, const segment y )
{
	Vector xl_yr = Vector( y.r - x.l ), xl_xr = Vector( x.r - x.l ), xl_yl = Vector( y.l - x.l );
	LL m1 = mul( xl_xr, xl_yr ), m2 = mul( xl_xr, xl_yl );
	LL mu1 = sign( m1 ) * sign( m2 );
    //这里转sign是因为直接乘的话会爆long long
	if( mu1 > 0 ) return false;
	Vector yl_xr = Vector( x.r - y.l ), yl_yr = Vector( y.l - y.r ), yl_xl = Vector( x.l - y.l );
	LL m3 = mul( yl_yr, yl_xr ), m4 = mul( yl_yr, yl_xl );
	LL mu2 = sign( m3 ) * sign( m4 );
	if( mu2 > 0 ) return false;
	return true;
}

int main()
{
//	freopen( "jump.in", "r", stdin );
//	freopen( "jump.out", "w", stdout );
	point lp, rp;
	int x1, x2, y1, y2;
	read( N );
	for( int i = 1 ; i <= N ; i ++ )
	{
		read( x1 ), read( y1 ), read( x2 ), read( y2 );
		seg[i].indx = i;
		seg[i].l = point( x1, y1, i );
		seg[i].r = point( x2, y2, i );
		P[2 * i - 1] = seg[i].l;
		P[2 * i] = seg[i].r;
	}
	sort( P + 1, P + 1 + 2 * N );
	int fir, sec, ind;
	for( int i = 1 ; i <= 2 * N ; i ++ )
	{
		pos = P[i].x;
		ind = P[i].indx;
		iter it = s.find( seg[ind] );
		if( it != s.end() )
		{
			iter pre = it, succ = it; succ ++;
			if( pre != s.begin() && succ != s.end() )
			{
				pre--;
				if( chk( seg[pre->indx], seg[succ->indx] ) )
				{
					fir = pre->indx, sec = succ->indx;
					break;
				}
			}
			s.erase( it );
		}
		else
		{
			it = s.lower_bound( seg[ind] );
			if( it != s.end() && chk( seg[it->indx], seg[ind] ) )
			{
				fir = ind, sec = it->indx;
				break;
			}
			if( it != s.begin() )
			{	
				it --;
				if( chk( seg[it->indx], seg[ind] ) )
				{
					fir = ind, sec = it->indx;
					break;
				}	
			}
			s.insert( seg[ind] );
		}
	}
	if( fir > sec ) fir ^= sec, sec ^= fir, fir ^= sec;
	int cnt = 0;
	for( int i = 1 ; i <= N ; i ++ )
	{
		if( i ^ sec && chk( seg[i], seg[sec] ) ) cnt ++;
	}
	write( cnt > 1 ? sec : fir ), putchar( '\n' );
	return 0;
}
```

---

## 作者：我去 (赞：7)

# P5428 [USACO19OPEN]Cow Steeplechase II S

## 题目

$\bullet$ 给定$n$条线段，问去掉哪条线段使得剩下的线段没有交点，多种答案输出编号最小的一条，保证有解

## 前置知识：判定线段是否相交

$\bullet$ 将线段表示为函数形式，带公式求交点，判断交点是否在两条直线上，会爆精度

$\bullet$ 使用**快速排斥实验 + 跨立实验**（说白了就是向量）

&emsp; &emsp; $\circ$ 快速排斥实验：

![pic](https://cdn.luogu.com.cn/upload/image_hosting/00vmsgzl.png)

&emsp; &emsp; &emsp; &emsp; $\diamond$ 快速排斥实验即初步判定两线段是否相交，将线段看做两个矩形的对角线判断两矩形是否相交

&emsp; &emsp; &emsp; &emsp; $\diamond$ 快速排斥实验不能判定线段是否相交，还需进行跨立实验

&emsp; &emsp; $\circ$ 跨立实验：

![pic](https://cdn.luogu.com.cn/upload/image_hosting/3zryxalr.png)

&emsp; &emsp; &emsp; &emsp; $\diamond$ 跨立实验即判断两条线段是否互相跨立（互相跨越，即相交）
 
&emsp; &emsp; &emsp; &emsp; $\diamond$ 由图可知，当两线段互相跨立时，从线段$x$的起点$A$出发向线段$y$的起点$C$和终点$D$构造向量$\overrightarrow{AC}，\overrightarrow{AD}$，显然$\overrightarrow{AC}，\overrightarrow{AD}$应该分别在线段$x$的两侧，对线段$y$同理。只要两线段中有一条不满足则两线段不相交。

&emsp; &emsp; &emsp; &emsp; $\diamond$ 对与如何判断两向量是否在另一个向量的两侧，可以使用向量的叉乘。即同一方向的叉积正负性一样，所以对两向量分别与另一向量求叉积，若线段相交，那么两个叉积的积应该为正

## 分析

$\bullet$ 因为只要移除一条线段，这张地图就可以恢复到预期没有相交线段的状态，所以只要找出**任意两条相交的线段，答案就是两条之一**，暴力检查一下即可。于是转化为**如何快速找到两条相交的线段**
 	
$\bullet$ 注意到两条线段相交的先决条件是**这两条线段在x轴上的投影有交集**

$\bullet$ 定义一个$set$来维护**在$x$轴的投影上包含了$now$这个点的不相交线段**
 	$\bullet$ 因为在$set$中线段不相交，所以**线段的上下关系不会改变**，可以用某条直线与线段交点的高度对线段排序

## 算法流程

$\bullet$ 对于输入的$2n$个点, 以$x$为第一关键字, $y$为第二关键字, 从小到大排序，并标记好该点属于哪一条线段
	
$\bullet$ 依次扫描每个点，设该点所在的线段为$seg$，这个点所在的$x$轴即为上面说的那条直线

&emsp; &emsp; $\circ$ 若$seg$不在$set$内：二分找到$seg$应该插入的位置，并判断该位置上下的线段是否与$seg$相交。若相交，保存两条相交的线段下标并退出。否则，将$seg$加入$set$

&emsp; &emsp; $\circ$ 若$seg$在$set$内：如果$seg$上下都有线段，找到这两条线段，判断它们是否相交。若相交，保存两条线段下标并退出。否则，将$seg$从$set$中删除
 			$\diamond$ 为什么在删除的时候需要再判断一次？ 因为在加入的时候之判断了新加入的线段与上下的关系，而并没有判断上下之间的关系，如下图
            
![pic](https://cdn.luogu.com.cn/upload/image_hosting/bglgeh7h.png)

## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cctype>
#include<set>
using namespace std;

typedef long long ll;
#define it set<segment>::iterator
const int MAXN = 1e5+5;

template <typename T>
inline void read(T&x){
	x=0; char temp=getchar(); bool f=false;
	while(!isdigit(temp)){if(temp=='-') f=true; temp=getchar();}
	while(isdigit(temp)){x=(x<<1)+(x<<3)+temp-'0'; temp=getchar();}
	if(f) x=-x;
}
template <typename T>
void print(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

//basic
int n;

//Point
int cnt;
struct point{
	ll x,y;
	int belong;
	inline bool operator <(const point &a)const{return x!=a.x? x<a.x:y<a.y;}
	inline point operator -(const point &a){return (point){x-a.x,y-a.y};}
}p[MAXN<<1];

//Segment
ll now;
struct segment{
	point l,r;
	int tag;
	inline double calc()const{if(l.x==r.x) return l.y; return 1.0*l.y+1.0*(r.y-l.y)*1.0*(now-l.x)/(1.0*(r.x-l.x));}//计算当前线段（看做函数）在now处的取值，注意特判与x轴垂直的情况
	inline bool operator <(const segment &a)const{return calc()<a.calc();}
}l[MAXN];
set<segment> s;

inline ll CrossMul(point a,point b,point c){a=a-c,b=b-c; ll res=a.x*b.y-a.y*b.x; return res==0? 0:res>0? 1:-1;}

inline bool Cross(segment a,segment b){
	if(!(min(a.l.x,a.r.x)<max(b.l.x,b.r.x)&&min(b.l.x,b.r.x)<max(a.l.x,a.r.x)&&min(a.l.y,a.r.y)<max(b.l.y,b.r.y)&&min(b.l.y,b.r.y)<max(a.l.y,a.r.y))) return false;//快速排斥实验
	return CrossMul(b.l,a.r,a.l)*CrossMul(a.r,b.r,a.l)>0&&CrossMul(a.l,b.l,b.r)*CrossMul(b.l,a.r,b.r)>0;//跨立实验
}

int main(){
	read(n);
	for(register int i=1;i<=n;i++){
		ll x1,y1,x2,y2; read(x1),read(y1),read(x2),read(y2);
		p[++cnt]=(point){x1,y1,i},p[++cnt]=(point){x2,y2,i};
		l[i]=(segment){p[cnt-1],p[cnt],i};
	}
	sort(p+1,p+cnt+1);
	
	int first=0,second=0;//任意两条相交的线段编号
	for(register int i=1;i<=cnt;i++){//依次扫描每个点
		now=p[i].x;//更新now以便重载小于
		int id=p[i].belong;
		it seg=s.find(l[id]);
		if(seg!=s.end()){
			it pre=seg,next=seg; next++;
			if(pre!=s.begin()&&next!=s.end()){//找到seg的上线两条线段pre与next
				pre--;
				if(Cross(*pre,*next)){first=pre->tag,second=next->tag; break;}//上下相交了，退出
			}
			s.erase(seg);
		}
		else{
			it pos=s.lower_bound(l[id]);
			if(pos!=s.end()&&Cross(*pos,l[id])){first=pos->tag,second=id; break;}//当前与后一条相交了，退出
			if(pos!=s.begin()){
				pos--;
				if(Cross(*pos,l[id])){first=pos->tag,second=id; break;}//当前与前一条相交了，退出
			}
			s.insert(l[id]);
		}
	}
	
	if(first>second) swap(first,second);
	int temp=0;
	for(register int i=1;i<=n;i++)
		if(i!=second&&Cross(l[i],l[second])) temp++;
	print(temp>1? second:first);
	return 0;
}
```

---

## 作者：p9t6g (赞：7)

非正解乱切毒瘤题祭

# 题外话

这题正解当然是$set$+扫描线,没什么好说的,但是我最开始做这道题的时候觉得就一个silver,怎么可能这么毒,于是开始用~~noip~~csp的思维乱$yy$,结果想出来了一个理论$n^2$但是实际上及其优秀的算法233

# 分析一波

首先,绝对$n^2$的算法应该不难对吧

这里我们考虑进行优化

可以看出来对于每一条线段,与其相交的线段都是有一定关联的,那么我们就将这样关联的线段集中在一起

> 对于一条线段,左右端点交换不会对其产生影响,所以我们进行调整
> 我们维护这样一个关系:$y_1\le y_2$当$y_1 = y_2$的时候，维护$x_1 < x_2$

> 再对于所有线段，我们以$y_1$为第一关键字,$x_1$为第二关键字排序

这里我们可以轻易的发现:对于任何一条线段$Seg_i$,只有可能与$Seg_j$相交,（这里$Seg_j$保证$Seg_j\text{->}y1 \le Seg_i\text{->}y2$

这就是一个连续的区间了（虽然还是理论$O(n^2)$但是实际上飞快）

# 基本操作

剩下的都是些基本操作了

## 线段相交

这里我并没有使用计算几何,而是非常单纯而~~noip~~暴力地用平面几何芝士进行判定

>  **tips:这里需要特别注意线段竖直与两线段交点的判定**

```c++
db Gety(Segment a,db x){
    //计算直线a在x的y值
	db k=(a.y2-a.y1)/(a.x2-a.x1),b=a.y1-k*a.x1;
	return k*x+b;
}
db CrossPointx(Segment a,Segment b){
	if(a.x1>a.x2)swap(a.x1,a.x2),swap(a.y1,a.y2);
	if(b.x1>b.x2)swap(b.x1,b.x2),swap(b.y1,b.y2);
	db k1=(a.y2-a.y1)/(a.x2-a.x1);db b1=a.y1-k1*a.x1;
	db k2=(b.y2-b.y1)/(b.x2-b.x1);db b2=b.y1-k2*b.x1;
    //平行return -1是因为原题中所有坐标维护在x正半轴,y正半轴和第二象限内
	if(k1==k2)return -1;
	return (b2-b1)/(k1-k2);
}
bool Cross(ll aa,ll bb){
	Segment a=seg[aa],b=seg[bb];db tmp;
    //两条线段都竖直
	if(a.x1==a.x2&&b.x1==b.x2)return a.y1<b.y2&&a.y2>=b.y1&&a.x1==b.x1;
    //第一条竖直
	if(a.x1==a.x2){
		tmp=Gety(b,a.x1);
		return tmp>=a.y1&&tmp<=a.y2&&tmp>=b.y1&&tmp<=b.y2;
	}
    //第二条竖直
	if(b.x1==b.x2){
		tmp=Gety(a,b.x1);
		return tmp>=a.y1&&tmp<=a.y2&&tmp>=b.y1&&tmp<=b.y2;
	}
    //两条都不特殊
	tmp=CrossPointx(a,b);//交点x坐标
	return tmp>=Min(a.x1,a.x2)&&tmp<=Max(a.x1,a.x2)&&tmp>=Min(b.x1,b.x2)&&tmp<=Max(b.x1,b.x2);
}
```

# 算法本体简述

首先按上述方式给线段排序

然后找出相交的任意两条线段(记为$x,y$)

分别求出与这两条线段相交的线段条数,记为$num_x,num_y$

这里可以发现如果两个$num$不同,则答案必定是$num$大的那一条线段,证明如下

> 这里使用反证法,假设我们要选择的是$num$小的那条线段y
>
> 那么与x相交的$num_x$条线段中必然有一些线段仍然与x相交
>
> 所以不能选$y$

(这里给的证明有点口胡,如果搞不懂的话请直接手推,这个结论很好推)

如果$num$相同的话就输出编号小的咯

# ~~喜闻乐见的~~代码

```c++
#include<bits/stdc++.h>
#define ll long long
#define db double
#define maxn 100005
#define Max(a,b) (((a)>(b))?(a):(b))
#define Min(a,b) (((a)<(b))?(a):(b))
using namespace std;
ll read(){
	ll a=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){a=a*10+c-'0';c=getchar();}
	return a*f;
}
struct Segment{db x1,y1,x2,y2,id;}seg[maxn];
int cmp(Segment a,Segment b){
	if(a.y1!=b.y1)return a.y1<b.y1;
	return a.x1<b.x1;
}
db Gety(Segment a,db x){
	db k=(a.y2-a.y1)/(a.x2-a.x1),b=a.y1-k*a.x1;
	return k*x+b;
}
db CrossPointx(Segment a,Segment b){
	if(a.x1>a.x2)swap(a.x1,a.x2),swap(a.y1,a.y2);
	if(b.x1>b.x2)swap(b.x1,b.x2),swap(b.y1,b.y2);
	db k1=(a.y2-a.y1)/(a.x2-a.x1);db b1=a.y1-k1*a.x1;
	db k2=(b.y2-b.y1)/(b.x2-b.x1);db b2=b.y1-k2*b.x1;
	if(k1==k2)return -1;
	return (b2-b1)/(k1-k2);
}
bool Cross(ll aa,ll bb){
	Segment a=seg[aa],b=seg[bb];db tmp;
	if(a.x1==a.x2&&b.x1==b.x2)return a.y1<b.y2&&a.y2>=b.y1&&a.x1==b.x1;
	if(a.x1==a.x2){tmp=Gety(b,a.x1);return tmp>=a.y1&&tmp<=a.y2&&tmp>=b.y1&&tmp<=b.y2;}
	if(b.x1==b.x2){tmp=Gety(a,b.x1);return tmp>=a.y1&&tmp<=a.y2&&tmp>=b.y1&&tmp<=b.y2;}
	tmp=CrossPointx(a,b);
	return tmp>=Min(a.x1,a.x2)&&tmp<=Max(a.x1,a.x2)&&tmp>=Min(b.x1,b.x2)&&tmp<=Max(b.x1,b.x2);
}
ll n;
ll Check(ll x){
	ll ret=0;
	for(int i=1;i<=n;i++){
		if(i==x)continue;
		ret+=Cross(Min(i,x),Max(i,x));
	}
	return ret;
}
int main(){
	n=read();
	for(int i=1,x1,x2,y1,y2;i<=n;i++){
		x1=read();y1=read();
		x2=read();y2=read();
		if(y1>y2){swap(x1,x2);swap(y1,y2);}
		if(y1==y2&&x1>x2){swap(x1,x2);}
		seg[i]=(Segment){x1,y1,x2,y2,i};
	}
	sort(seg+1,seg+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(seg[j].y1>seg[i].y2)break;
			if(Cross(i,j)){
				ll num1=Check(i),num2=Check(j);
				if(num1==num2)cout<<Min(seg[i].id,seg[j].id);
				else cout<<(num1>num2?seg[i].id:seg[j].id);
				return 0;
			}
		}
	}
	return 0;
}
/*
5
7 1 4 0
2 1 2 6
1 4 4 2
3 2 4 3
5 2 5 5
*/
/*
9
9 6 6 8
8 5 6 5
8 4 4 1
4 9 4 5
8 3 7 0
0 7 1 2
7 4 9 5
6 9 6 4
2 1 7 7
*/
```

(下面代码最后给出了我调代码的时候$hack$自己的数据)

# 结尾

如果写了这种方法的童鞋请还是去练一练正解,毕竟时间玄学不太好233

(求各位大佬不要卡我)



---

## 作者：DrBit (赞：3)

[题面](https://www.luogu.com.cn/problem/P5428)

前置知识：[判断两个线段是否相交](https://blog.csdn.net/zhouzi2018/article/details/81871875)

首先 $O(N^2)$ 的做法很好想。

仔细分析题目性质之后可以发现我们只需要找出一对相交线段就可以了，答案必是其中之一。

我们把每个线段的端点按 x 坐标排序，每遇到一个起点将对应线段加到 set 里，遇到终点将对应线段从 set 里删掉。这样如果当前的扫到了横坐标在 $X$ 的端点，可以保证 set 中的所有线段都经过 $x=X$ 这条直线。

假设 set 里已经维护了若干不相交的线段集合，那么这些线段“相对平行”。现在往里面加入一条线段，假设这条线段与另一条线段相交，那么可以分两种情况讨论：

1.这两条线段在直线 $x=X$ 上的交点中间没有其他线段

2.这两条线段在直线 $x=X$ 上的交点中有其他线段

所以加入一条线段时 check 一下与其他两条交点相邻线段的相交关系就可以解决情况 1。

上面这条也提示我们 set 内的大小关系要根据与 $x=X$ 的交点纵坐标大小来判断。（因为 set 内的线段“相对平行”，所以 $x$ 移动时线段的上下关系并不会改变）

情况 2 在删除时处理。

假设线段 a、b、c 从上到下排成了下图所示的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/uhvjza45.png)

可以发现情况 2 的相交情况只有这一种可能。（两条相交的长线段中间夹了一条短线段）

那么我们删除 b 肯定早于删除 a 和 c，在删除 b 时 check 一下 a 和 c 的相交关系即可。

整理一下：

1.插入一条线段时，check 它和相邻两条线段的相交关系。

2.删除一条线段时，check 它相邻两条线段之间的相交关系。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#define int long long
#define it set<seg>::iterator
using namespace std;
const int MAXN = 2e5 + 50;
int N, X;
struct po
{
    int x, y, id;
    po(){}
    po(int a, int b) 
    {
        x = a;
        y = b;
    }
    bool operator<(const po &tmp) const
    {
        if (x == tmp.x)
            return y < tmp.y;
        return x < tmp.x;
    }
    po operator-(const po &tmp) const
    {
        return po(x - tmp.x, y - tmp.y);
    }
    int operator*(const po &tmp) const
    {
        return x * tmp.y - tmp.x * y;
    }
} poi[MAXN * 2];
struct seg
{
    po a, b;
    int id;
    double calc() const
    {
        if (b.x == a.x)
            return a.y;
        double k = 1.0 * (b.y - a.y) / (1.0 * (b.x - a.x));
        return a.y + 1.0 * k * (X - a.x);
    }
    bool operator<(const seg &tmp) const
    {
        return calc() < tmp.calc();
    }
    double operator*(const seg &tmp) const
    {
        return 1.0 * (b.x - a.x) * (tmp.b.y - tmp.a.y) - 1.0 * (tmp.b.x - tmp.a.x) * (b.y - a.y);
    }
} l[MAXN];
bool check(seg a, seg b)
{
    int tag = 0;
    if ((min(a.a.x, a.b.x) < max(b.a.x, b.b.x) && min(b.a.x, b.b.x) < max(a.a.x, a.b.x) && min(a.a.y, a.b.y) < max(b.a.y, b.b.y) && min(b.a.y, b.b.y) < max(a.a.y, a.b.y)))
    {
        // cout << a.id << " " << b.id << ":" << "yes" << endl;
        if (((b.a - a.a) * (a.b - a.a)) * ((b.b - a.a) * (a.b - a.a)) <= 0 && ((a.a - b.a) * (b.b - b.a)) * ((a.b - b.a) * (b.b - b.a)) <= 0)
            tag = 1;
    }
    // cout << a.id << " " << b.id << ":" << tag << endl;
    return tag;
}
int fir, sec;
set<seg> S;
void solve()
{
    for (int i = 1; i <= 2 * N; ++i)
    {
        X = poi[i].x;
        int id = poi[i].id;
        it pos = S.find(l[id]);
        if (pos == S.end())
        {
            it a = S.lower_bound(l[id]);
            it b = S.lower_bound(l[id]);
            if (b != S.end() && check(l[id], *b))
            {
                fir = id;
                sec = b->id;
                return;
            }
            if (a != S.begin())
            {
                a--;
                if (check(l[id], *a))
                {
                    fir = id;
                    sec = a->id;
                    return;
                }
            }
            S.insert(l[id]);
        }
        else
        {
            it a = pos;
            it b = pos;
            if (b != S.end())
                b++;
            if (a != S.begin())
                a--;
            if (b != S.end() && check(*a, *b))
            {
                fir = a->id;
                sec = b->id;
                return;
            }
            S.erase(l[id]);
        }
    }
}
signed main()
{
    scanf("%lld", &N);
    for (int i = 1; i <= N; ++i)
    {
        scanf("%lld%lld%lld%lld", &poi[i * 2 - 1].x, &poi[i * 2 - 1].y, &poi[i * 2].x, &poi[i * 2].y);
        poi[i * 2 - 1].id = poi[i * 2].id = i;
        l[i].a = poi[i * 2 - 1];
        l[i].b = poi[i * 2];
        l[i].id = i;
    }
    sort(poi + 1, poi + 2 * N + 1);
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            check(l[i], l[j]);
    solve();
    if (fir > sec)
        swap(fir, sec);
    int cnt = 0;
    for (int i = 1; i <= N; ++i)
        if (i != sec && check(l[i], l[sec]))
            cnt++;
    if (cnt > 1)
        swap(fir, sec);
    printf("%lld\n", fir);
    return 0;
}
```


---

## 作者：StayAlone (赞：2)

### 题外话
多年没写过题解了，~~社贡还没降~~，所以来写一篇感觉有些难度的题解。  

### 思路

- 把每一个端点放到一个数组内，按照 $x$ 为第一关键字，$y$ 为第二关键字排序。
- 开一个存线段的 set，按照与扫描线的交点的 $y$ 值从小到大排序了。扫描线顺序移动到每一个端点。
	- 如果该端点为右端点，说明该线段已经在 set 内。比较 set 内它前后的两条线段，因为只需要找到一对相交的线段，如果相交，存下相交的线段的编号并 break。反之，删除该线段。
    - 同理，如果该线段是左端点，说明该线段未在 set 内，加入该线段，然后比较两次：第一次是它后一个线段和它本身，第二次是它后一个线段和它本身。这里的比较就是指上面的判断线段是否相交并记录和 break。
- 现在设相交的两条线段为 $a1,a2$，先保证 $a1 < a2$，有与 $a2$ 相交的线段的数量大于 $1$ 时，与 $a1$ 相交的线段数量必为 $1$。设与 $a2$ 相交的线段数量为 $cnt$，则 $cnt > 1$ 时输出 $a2$，反之输出 $a1$。  

关于如何判断两条线段是否相交，[here](https://blog.csdn.net/qq_39627843/article/details/81170316)。

在判断扫描线与某条线段的交点时，我太蒟了看不懂其他大佬的方法。所以是先求出 $y = kx + b$ 中的 $k,b$ 然后带入扫描线的 $x$ 坐标求交点。

```cpp
il double val() const // 求该线段与 x = now 的交点 
{
	if (l.fst == r.fst) return l.snd;
	double k = (l.snd - r.snd) * 1.0 / (l.fst - r.fst), b = l.snd - k * l.fst;
	/*
	y1 = kx1 + b (1)
	y2 = kx2 + b (2)
	(1) - (2) 得 k(x1 - x2) = y1 - y2
	k = (y1 - y2) / (x1 - x2)
	b = y1 - kx1
	*/ 
	// 求出该线段的解析式：y = kx + b 
	return k * now + b; // 将 k 和 b 带入，求出交点 
//		return l.snd + 1.0 * (r.snd - l.snd) * 1.0 * (now - l.fst) / (r.fst - l.fst); 这里是其他大佬的方法，看不懂
}
```

[AC code记录](https://www.luogu.com.cn/record/59500755)

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (int i = j; i >= int(n); --i)
#define ptc putchar
#define il inline
#define fst first
#define snd second
#define rout return 0
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 1e5 + 10;
namespace stupid_lrc
{
	template <typename T>
	il void read(T &x)
	{
		x = 0; T f = 1; char ch;
		while (!isdigit(ch = getchar())) f -= 2 * (ch == '-');
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar(); x *= f;
	}
	
	template <typename T>
	il void write(T x)
	{
		if (x < 0) ptc('-'), x = -x;
		if (x > 9) write(x / 10);
		ptc(x % 10 + '0');
	}
}
using namespace stupid_lrc;
int n;

struct point
{
	int idx; pii ps;
	il bool operator < (const point &r) const
	{
		return ps < r.ps;
	}
}pt[MAXN << 1];

int now;

struct segment
{
	pii l, r; int idx;
	il double val() const // 求该线段与 x = now 的交点 
	{
		if (l.fst == r.fst) return l.snd;
		double k = (l.snd - r.snd) * 1.0 / (l.fst - r.fst), b = l.snd - k * l.fst;
		/*
		y1 = kx1 + b (1)
		y2 = kx2 + b (2)
		(1) - (2) 得 k(x1 - x2) = y1 - y2
		k = (y1 - y2) / (x1 - x2)
		b = y1 - kx1
		*/ 
		// 求出该线段的解析式：y = kx + b 
		return k * now + b; // 将 k 和 b 带入，求出交点 
//		return l.snd + 1.0 * (r.snd - l.snd) * 1.0 * (now - l.fst) / (r.fst - l.fst);
	}
	il bool operator < (const segment &r) const
	{
		return val() < r.val();
	}
	il bool operator == (const segment &r) const
	{
		return idx == r.idx;
	}
}seg[MAXN];
typedef set<segment> :: iterator iter;
set<segment> s;

il int cross(pii a, pii b, pii c) // 求向量 AB 和 AC 的差积 
{
	ll ans = 1ll * (b.fst - a.fst) * (c.snd - a.snd) - 1ll * (c.fst - a.fst) * (b.snd - a.snd);
	return ans ? (ans < 0 ? -1 : 1) : 0; // 由于只需要知道是否异号，所以其本身的值不重要，知道正负就够了。
}

il bool check(pii a, pii b, pii c, pii d) // 判断 AB 是否与 CD 相交 
{
	if (my_min(a.fst, b.fst) > my_max(c.fst, d.fst) ||
	my_min(c.fst, d.fst) > my_max(a.fst, b.fst) ||
	my_min(a.snd, b.snd) > my_max(c.snd, d.snd) ||
	my_min(c.snd, d.snd) > my_max(a.snd, b.snd)) return false;
	return cross(a, b, c) * cross(a, b, d) < 0 && cross(c, d, a) * cross(c, d, b) < 0;
}

int main()
{
	read(n);
	rep1(i, 1, n)
	{
		read(seg[i].l.fst), read(seg[i].l.snd);
		read(seg[i].r.fst), read(seg[i].r.snd);
		seg[i].idx = i;
		pt[(i << 1) - 1].ps = seg[i].l;
		pt[(i << 1)].ps = seg[i].r;
		pt[(i << 1) - 1].idx = pt[(i << 1)].idx = i;
	}
	sort(pt + 1, pt + 1 + (n << 1));
	int a1 = -1, a2 = -1;
	rep1(i, 1, n << 1)
	{
		now = pt[i].ps.fst; int inw = pt[i].idx;
		iter it = s.find(seg[inw]);
		if (it != s.end()) // 如果 it 存在，说明此时该线段已经处理过 
		{
			iter pre = it, suc = it;
			if (pre != s.begin() && suc != s.end()) // 如果 it 的前驱和后继存在 
			{
				pre--; suc++; 
				if (check(pre->l, pre->r, suc->l, suc->r)) // 比较它们，若相交 
				{
					a1 = pre->idx; a2 = suc->idx; // 则记录 a1 a2，跳出循环
					break;
				}
			}
			s.erase(it); // 删除 it 
		}
		else // 说明此时该线段还没处理 
		{
			s.insert(seg[inw]); it = s.find(seg[inw]); // 插入，查找 
			iter pre = it, suc = it; 
			if (pre != s.begin()) // 比较它和他的前驱 
			{
				pre--;
				if (check(pre->l, pre->r, it->l, it->r))
				{
					a1 = pre->idx; a2 = it->idx;
					break;
				}
			}
			if (suc != s.end()) // 比较它和它的后继 
			{
				suc++;
				if (check(it->l, it->r, suc->l, suc->r))
				{
					a1 = it->idx; a2 = suc->idx;
					break;
				}
			}
		}
	}
	if (a1 > a2) swap(a1, a2);
	int cnt = 0;
	rep1(i, 1, n)
		if (i^a2 && check(seg[i].l, seg[i].r, seg[a2].l, seg[a2].r)) cnt++;
	write(cnt > 1 ? a2 : a1);
	rout;
}
```

---

## 作者：Rainybunny (赞：2)

( 本文也作$8.15$考试题解, 附[题目链接](https://www.luogu.org/problem/P5428). )  
这道题比较有挑战性, 大概是蓝题到紫题的水平吧.  

首先, 一定要理解这句题面:  
- 只要移除一条线段，这张地图就可以恢复到预期没有相交线段的状态.  

也就是说, **一旦我们发现两条线段有交点, 答案就必为其中一条**.  
因此, 本题也就转化为**如何快速找到两条相交的线段**.  

我们需要一种判断两条线段是否相交的算法. 引入两个实验:  
- 快速排斥实验  
设以线段$A_1A_2$和线段$B_1B_2$为对角线的矩形为$M,N$;  
若$M,N$不相交, 则两个线段显然不相交;  

- 跨立实验  
若两线段相交, 则两线段必然相互跨立对方. 若$A_1A_2$跨立$B_1B_2$, 则矢量$\vec{A_1B_1}$和$\vec{A_2B_1}$位于矢量$\vec{B_2B_1}$的两侧.  

结合两种实验, 我们才能判断包括共线在内的所有相交情况.  
( 推荐一篇讲解本算法的$Blog$: [传送门](https://blog.csdn.net/tianwei0822/article/details/82118463). )  

接下来, 由于发现$O(n^2)$的查找算法显然是不可取的, 介绍一种$O(n\log_2n)$的算法: 扫描线$+set$.  
引入$set$, 用于保存线段. 每找到一个端点, 若其所在线段不在$set$中, 将该线段压入$set$, 否则将该线段弹出$set$. 目的是**保证$set$内的线段在$x$轴上的投影两两有交集**, 这是线段相交的先决条件.  
难点在于$set$的'$<$'重载与使用. 我们按照**扫描线与线段交点的$y$值为关键字排序**.  
这样排序, 是为能快速取得与某一条线段上下相邻的线段. 维护出来的$set$应形如:  
![jump1.PNG](https://i.loli.net/2019/08/15/GS2N14KFiOPqxbQ.png)  
算法流程如下:  
1. 对于输入的$2n$个点, 以$x$为第一关键字, $y$为第二关键字, 从小到大排序.  

2. 依次遍历每个点, 分两种情况讨论:  
	- 该点所在线段不在$set$内.  
利用$lower\_bound$函数二分取得该线段应该插入的位置, 并判断该位置上下的线段是否与该线段相交. 若相交, 保存两条线段下标并结束算法. 否则, 将该线段压入$set$.  
注意, 由于**扫描线与线段交点$y$值的相对大小是不会改变的**, 故只需要在'$<$'重载中在线计算$y$值即可.  

	- 该点所在线段在$set$内.  
 若该线段上下都有线段, 检查这两条线段是否相交. 若相交, 记录其下标并结束算法. 否则, 弹出该线段.  

算法结束, 由题意, 我们一定会取得两条相交的线段下标$Indxa,Indxb$, 不妨设$Indxa<Indxb$. 我们考虑是否有其它线段与线段$Indxb$相交, 若有, 则必须删除线段$Indxb$. 否则, 删除线段$Indxa$. 程序结束.  

值得注意的, 在线计算$y$值时特判与$x$轴垂直的线段.  
代码实现有一定难度, 已给出详细注释.
```cpp
#include <set> 
#include <cstdio>
#include <assert.h>
#include <iostream>
#include <algorithm>

#define Int register int
#define mkpii( fir, sec ) make_pair ( fir, sec )

using namespace std;

typedef long long int LL;
typedef pair<int, int> pii;

const int MAXN = 100000;
int n, X, Indxa, Indxb;

inline int rint () { // 输入量较大, 注意快读 
	Int x = 0, f = 1; register char s = getchar ();
	for ( ; s < '0' || '9' < s; s = getchar () ) f = s == '-' ? -f : f;
	for ( ; '0' <= s && s <= '9'; s = getchar () ) x = ( x << 3 ) + ( x << 1 ) + ( s ^ '0' );
	return x * f;
}

LL mul ( const pii a, const pii b, const pii c ) { // 跨立实验叉乘判断 
	return 1LL * ( b.first - a.first ) * ( c.second - a.second ) - 1LL * ( c.first - a.first ) * ( b.second - a.second );
}

struct Point { // 用于排序的2n个点, IsSec记录是否此时的线段已入set 
	int x, y, id, IsSec;
	inline bool operator < ( const Point Other ) const {
		if ( x < Other.x ) return true;
		if ( x > Other.x ) return false;
		return y < Other.y;
	}
} pt[MAXN << 1 | 1] = {};

struct Segment { // 线段 
	int x_1, y_1, x_2, y_2, id;
	friend inline bool operator == ( const Segment a, const Segment b ) {
		return a.id == b.id;
	}
	friend inline bool operator < ( const Segment a, const Segment b ) { // y值比较, 特判x1=x2, 取较大的y2 
		const double ya = a.x_1 == a.x_2 ? a.y_2 : a.y_1 + 1.0 * ( X - a.x_1 ) * ( a.y_2 - a.y_1 ) / ( a.x_2 - a.x_1 );
		const double yb = b.x_1 == b.x_2 ? b.y_2 : b.y_1 + 1.0 * ( X - b.x_1 ) * ( b.y_2 - b.y_1 ) / ( b.x_2 - b.x_1 );
		return ya < yb;
	}
	inline bool Check ( const Segment b ) const { // 判断线段a, b是否相交 
		const Segment a = *this;
		const pii as = mkpii ( a.x_1, a.y_1 ), bs = mkpii ( b.x_1, b.y_1 );
		const pii ae = mkpii ( a.x_2, a.y_2 ), be = mkpii ( b.x_2, b.y_2 );
		return min ( a.x_1, a.x_2 ) <= max ( b.x_1, b.x_2 )
			&& max ( a.x_1, a.x_2 ) >= min ( b.x_1, b.x_2 )
			&& min ( a.y_1, a.y_2 ) <= max ( b.y_1, b.y_2 )
			&& max ( a.y_1, a.y_2 ) >= min ( b.y_1, b.y_2 ) // 快速排斥实验 
			&& mul ( bs, as, be ) * mul ( bs, be, ae ) >= 0
			&& mul ( as, bs, ae ) * mul ( as, ae, be ) >= 0; // 跨立实验 
	}
} Seg[MAXN + 5] = {};

typedef set<Segment> :: iterator setiter;

set<Segment> S;

inline void Intersect () {
	sort ( pt + 1, pt + ( n << 1 | 1 ) );
	for ( Int i = 1; i <= n << 1; ++ i ) {
		if ( pt[i].IsSec ) { // 情况2, 需要弹出该线段 
			setiter it = S.find ( Seg[pt[i].id] ), _upper = it, _lower = it; // _upper与_lower分别表示上方线段与下方线段 
			++ _upper; // 很伤心的是, iterator不支持'+''-'运算 
			if ( _upper != S.end () && _lower != S.begin () ) {
				-- _lower;
				if ( Seg[_lower -> id].Check ( Seg[_upper -> id] ) ) { // 两线段相交 
					assert ( _lower != _upper ); // 检查是否出现异常: 是同一条线段 
					Indxa = _lower -> id, Indxb = _upper -> id; // 记录下标 
					return ; // 结束 
				}
			}
			S.erase ( it ); // 删除该线段 
		} else { // 情况1 
			X = pt[i].x; // 更新扫描线位置 
			setiter it = S.lower_bound ( Seg[pt[i].id] ); // 取得插入位置 
			if ( it != S.end () && Seg[pt[i].id].Check ( Seg[it -> id] ) ) { // 是否与上方线段相交 
				Indxa = pt[i].id, Indxb = it -> id;
				return ;
			}
			if ( it != S.begin () && Seg[pt[i].id].Check ( Seg[( -- it ) -> id] ) ) { // 是否与下方线段相交 
				Indxa = pt[i].id, Indxb = it -> id;
				return ;
			}
			S.insert ( Seg[pt[i].id] ); // 插入该线段 
		}
	}
}

inline void Work () {
	n = rint ();
	for ( Int i = 1, x_1, y_1, x_2, y_2; i <= n; ++ i ) {
		scanf ( "%d %d %d %d", &x_1, &y_1, &x_2, &y_2 );
		if ( x_1 > x_2 || ( x_1 == x_2 && y_1 > y_2 ) ) { // 保证(x1,y1)会先被找到 
			x_1 ^= x_2, x_2 ^= x_1, x_1 ^= x_2;
			y_1 ^= y_2, y_2 ^= y_1, y_1 ^= y_2;
		}
		Seg[i] = Segment { x_1, y_1, x_2, y_2, i };
		pt[i - 1 << 1 | 1] = Point { x_1, y_1, i, false };
		pt[i << 1] = Point { x_2, y_2, i, true };
	}
	Intersect ();
	if ( Indxa > Indxb ) Indxa ^= Indxb, Indxb ^= Indxa, Indxa ^= Indxb;
	for ( Int i = 1; i <= n; ++ i ) {
		if ( i ^ Indxa && i ^ Indxb && Seg[Indxb].Check ( Seg[i] ) ) { // 是否有线段与Seg[Indxb]相交 
			printf ( "%d\n", Indxb );
			return ;
		}
	}
	printf ( "%d\n", Indxa );
}

int main () {
//	freopen ( "jump.in", "r", stdin );
//	freopen ( "jump.out", "w", stdout );
	Work ();
	return 0;
}
```

---

## 作者：wyl_AC (赞：1)

这道题一看可知是要求出相连的的最前面两个，因为最多3个连在一起，甚至有时候3个也不行，所以求出相连两条即可退出。

首先想到n^{2}复杂度做法，但明显超时，需要优化，所以采取扫描线进行优化至nlog(n)。

现将每个点（注意，分开了，但要标记属于那条线）按照x轴从小到大排序，x坐标相同的按y坐标从大到小。用set进行存储，

在左端点出现后，让这条线进入集合，与两边的线进行检查是否相交，注意，set有排序功能，所以你要重载小于，要注意比较方式，求出相邻两条边在同一x坐标y坐标大小，因为这个x坐标会随扫描线移动。

在右端点出现后，让这条线出集合，因为扫描线已经扫过了。这是还要检查一遍左右两条线是否相交

，因为左右可能变化了。

注:这道题需熟练用于set的各种函数。

比较也需要技巧：对立叉乘实验

![](https://img-blog.csdnimg.cn/20190816070614702.png)

p1和p2是两条线段，且左端点处于同一位置（0,0）右端点分别为(x1,y1),(x2,y2),

线段p1和p2的叉乘结果为p1Xp2=x1*y2-x2*y1

如若结果大于0，则p2在p1的顺时针180度以内，如果小于零，在逆时针180度以内。

要判断是否交叉，可以取p1线上一端点连上p2线的两个端点，得到两条条线，再分别与p1进行叉乘实验。

再可以取p2线上一端点连上p1线的两个端点，得到两条条线，再分别与p2进行叉乘实验。

就可以知道是否p1两点在p2两边,p2两点在p1两边。

就能得到答案了
上代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
#define LL long long
#define M 100005
void read(LL &x){
	x=0;LL f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')
			f=-f;
		c=getchar();
	} 
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	x*=f;
	return ;
}
double x;
LL n,ans1,ans2;
struct edge{
	LL x,y,id;
	bool operator <(edge b)const{
		return x==b.x?y<b.y:x<b.x;
	}
}t[M<<1];
struct node{
	edge a,b;
	LL id;
	bool operator ==(node k)const{
		return	id==k.id;
	}
}p[M];
double eval(node op){
	if(op.a.x==op.b.x)
		return op.a.y;
	return op.a.y+(op.b.y-op.a.y)*(x-op.a.x)/(op.b.x-op.a.x);
}
bool operator <(node u,node v){
	return u.id!=v.id&&eval(u)<eval(v);
}
set<node>s;
LL sum[M];
LL sign(LL x){
	if(!x)
		return 0ll;
	if(x>0)
		return +1ll;
	return -1ll;
}
LL operator* (edge u,edge v){
	return sign(u.x*v.y-u.y*v.x);
}
edge operator- (edge u,edge v){
	edge k1={u.x-v.x,u.y-v.y};
	return k1; 
}
bool cmp(node u,node v){
	edge &a1=u.a,&a2=v.a,&b1=u.b,&b2=v.b;
	return ((b2-a1) * (b1-a1)) * ((b1-a1) * (a2-a1))>=0&&((b1-a2) * (b2-a2)) * ((b2-a2) * (a1-a2))>=0;
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(p[i].a.x),read(p[i].a.y),read(p[i].b.x),read(p[i].b.y);
		t[(i<<1)-1]=p[i].a;
		t[i<<1]=p[i].b;
		p[i].a.id=p[i].b.id=p[i].id=t[(i<<1)-1].id=t[i<<1].id=i;
	}
	sort(t+1,t+1+(n<<1));
	for(int i=1;i<=n<<1;i++){
		set<node>::iterator it;
		LL k=t[i].id;
		ans1=k;
		x=t[i].x;
		it=s.find(p[k]);
		if(it!=s.end()){
			set<node>::iterator a_it=it,b_it=it;b_it++;
			if(a_it!=s.begin()&&b_it!=s.end()){
				a_it--;
				if(cmp(p[a_it->id],p[b_it->id])){
					ans1=a_it->id,ans2=b_it->id;
					break;
				}
			}
			s.erase(it);
		}else{
			set<node>::iterator new_it=s.lower_bound(p[k]);
			if(new_it!=s.end()&&cmp(p[new_it->id],p[k])){
				ans2=new_it->id;
				break;
			}
			if(new_it!=s.begin()){
				new_it--;
				if(cmp(p[new_it->id],p[k])){
					ans2=new_it->id;
					break;
				}
			}
			s.insert(p[k]);
		}
	}
	LL ans=0;
	if(ans1>ans2)
		swap(ans1,ans2);
	for(int i=1;i<=n;i++)
		if(p[i].id!=ans2&&cmp(p[i],p[ans2]))
			ans++;
	printf("%lld",ans>1?ans2:ans1);
	return 0;
}
```


---

