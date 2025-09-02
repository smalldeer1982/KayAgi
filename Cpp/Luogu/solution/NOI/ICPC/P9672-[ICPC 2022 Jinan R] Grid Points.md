# [ICPC 2022 Jinan R] Grid Points

## 题目描述

在笛卡尔平面的第一个象限中，您会得到一个简单的多边形。这意味着多边形中任何点的坐标$（x，y）$满足$x>0$和$y>0$。



考虑多边形中的所有网格点。按\textbf｛斜率｝的递增顺序排列。按此顺序输出第$k$个网格点。



网格点是一个点$（x，y）$，使得$x$和$y$是整数。多边形边界上的一个点被认为在多边形中。点$（x，y）$的斜率为$y/x$。如果两个点具有相同的斜率，则它们首先按字典顺序排列$x$，然后按$y$。换句话说，如果$（x_1<x_2）\vee（x_1=x_2\wedge y_1<y_2）$，则点$（x_1，y_1）$在字典上小于$（x_2，y_2）。

## 样例 #1

### 输入

```
4
3 3
1 1
3 1
3 3
4 500000000000000000
1 1
1000000000 1
1000000000 1000000000
1 1000000000
9 22
9 6
6 7
9 7
10 10
6 9
3 9
1 6
1 5
7 3
5 22447972861454999
270353376 593874603
230208698 598303091
237630296 255016434
782669452 568066304
654623868 958264153```

### 输出

```
3 2
500000000 500000000
7 8
730715389 644702744```

# 题解

## 作者：Rainbow_qwq (赞：3)

![](https://cdn.luogu.com.cn/upload/image_hosting/yjvg811n.png)

考虑二分斜率 $k$，用斜率为 $k$ 的直线切简单多边形，要计算在直线之下，在多边形区域内的整点数量之和。

把每条边向 $x$ 轴做垂线，差分成求若干个直角梯形的整点数，对每个梯形用类欧计算即可。

你以为这就完了？那就想的太简单了。

在简单多边形的边界上，每条边上的点、每个角上的点的贡献是极难处理的，而且这题切完后会变成多个简单多边形，并不能简单判断应该取正还是取负贡献。下面的做法来自 std 的实现方式（

考虑一种“毕克定理”式的贡献计算方式：假设在每个点放了一个半径可以看作 $0$ 的圆盘，对于一个简单多边形，我们计算在多边形内的圆盘的重量之和，其中严格在内部的点贡献 $1$，边上的点贡献 $\frac 12$，角上的点贡献 $\frac {\alpha}{2\pi}$。

这个“重量”的贡献差分到每个梯形上，是可以简单加减的。

我们看看在这种计算方式下会算出什么：假设取的斜率 $k$ 是极远处的一个坐标互质的点，这条“新线”切多边形的任何线都不产生整点。

- 内部整点的贡献是正确的。
- 边上的点的贡献为 $\frac 12$，需要枚举每条原始多边形上的边加上贡献。
- 角上的点的贡献之和为 $\frac{n}{2}-1$（多边形内角和），其中 $n$ 为这个多边形的点数。而我们需要的点数是 $n-2$（新的线切出来的两个点一定不是整点），把 $\frac{n}{2}-1$ 乘上 $2$ 就对了。

我们通过把贡献拆到每个角度和边上，就完美解决了边界的问题！

最后是一些二分的细节，我们可以取大于 $V^2$ 的一个大质数 $P$，取出 $(P,i),(i,P)$ 点列作为斜率进行二分。

最后对于斜率相等的点还要二分是第几个，需要二分 $x$ 并且实现数坐标 $\le x$ 的所有点，这个在数点的函数里加一个限制就行。

时间复杂度 $O(n\log^2 V)$。

```cpp
// what is matter? never mind. 
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2") 
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define ll long long
#define int long long
#define ull unsigned long long
#define i128 __int128
#define SZ(x) ((int)((x).size()))
#define ALL(x) (x).begin(),(x).end()
using namespace std;

#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;
 
#define maxn 500005
#define inf 0x3f3f3f3f

// i=[0..n] (a*i+b)/c
i128 floor_sum(i128 n,i128 a,i128 b,i128 c){
	i128 res=0;
//	For(i,0,n)res+=(a*i+b)/c;return res;
	res=(n+1)*(b/c)+n*(n+1)/2*(a/c);
	a%=c,b%=c;
	if(a<0)a+=c,res-=n*(n+1)/2;
	if(b<0)b+=c,res-=n+1;
	if(!a)return res+(n+1)*(b/c);
//	i128 m=(a*n+b)/c;
//	i128 t=floor_sum(m-1,c,c-b-1,a);
//	res=n*m-t;
	i128 t=a*(n+1)+b;
	if(t>=c) res+=floor_sum(t/c-1,c,t%c,a);
	return res;
}

i128 floor_sum(i128 a,i128 b,i128 c,i128 l,i128 r){
	return floor_sum(r,a,b,c)-floor_sum(l-1,a,b,c);
}

#define double long double
typedef double db;
const db eps=1e-10,pi=3.14159265358979323846;

struct P{
	int x,y;
	P(int x=0,int y=0):x(x),y(y){}
	P&operator +=(P o){return x+=o.x,y+=o.y,*this;}
	P&operator -=(P o){return x-=o.x,y-=o.y,*this;}
	P&operator *=(int o){return x*=o,y*=o,*this;}
	P&operator /=(int o){return x/=o,y/=o,*this;}
	friend P operator +(P a,P b){return a+=b;}
	friend P operator -(P a,P b){return a-=b;}
	friend P operator *(P a,int b){return a*=b;}
	friend P operator /(P a,int b){return a/=b;}
	friend bool operator <(P a,P b){return a.x==b.x?a.y<b.y:a.x<b.x;}
	friend int operator %(P a,P b){return a.x*b.x+a.y*b.y;} // dot
	friend int operator *(P a,P b){return a.x*b.y-a.y*b.x;} // cross
	
	inline double ang(){return atan2(y,x);}
	inline double l(){return sqrt((*this)*(*this));}
	
	void read(){cin>>x>>y;}
	void out(){cout<<"("<<x<<","<<y<<")"<<endl;}
};


const int W=1000000000,V=W*W+W+1;
pii getid(int x){
	if(x<=V)return mkp(x,V);
	return mkp(V,V*2-x);
}

int gcd(int x,int y){
	x=abs(x),y=abs(y);
	return __gcd(x,y);
}

int n,k;
P a[maxn];
db ang[maxn],ang2[maxn];

int tmp[maxn];

bool isin(P a,int k1,int k2,int xl){
	return a.x<=xl && (i128)a.y*k2<=(i128)a.x*k1;
}

i128 Div(i128 a,i128 b){
	if(a>=0) return a/b;
	return (a-b+1)/b;
}
int gclamp(i128 x){
	return (int)max(min(x,(i128)V),-(i128)V);
}
void clamp(int&l,int&r,i128 k,i128 b){
	if(k==0){
		if(b<0)l=1,r=0;
		return;
	}
	if(k>0){
		i128 t=Div(b,k);
		r=min(r,gclamp(t));
	}else{
		i128 t=Div((-b)+(-k)-1,-k);
		l=max(l,gclamp(t));
	}
}

int seg(P u,P v,int k1,int k2,int xl){
	if(u.x>v.x)swap(u,v);
	int d=gcd(v.x-u.x,v.y-u.y);
	int l=1,r=d-1;
	i128 dx=(v.x-u.x)/d,dy=(v.y-u.y)/d;
	clamp(l,r,dx,xl-u.x);
	clamp(l,r,dy*k2-dx*k1,(i128)u.x*k1-(i128)u.y*k2);
	return max(0ll,r-l+1);
}

pair<int,db>calc(P u,P v,int id,int k1,int k2,int xl){
	int res1=0; db res2=0;
	if(u.x==v.x)return mkp(res1,res2);
	if(u.x>v.x)swap(u,v);
	
	int l=u.x+1,r=min(v.x-1,xl);
	int a=v.y-u.y,c=v.x-u.x,b=u.y*c-u.x*a-1;
	clamp(l,r,(i128)k2*a-(i128)k1*c,-(i128)b*k2);
//	cout<<"l,r "<<l<<" "<<r<<"\n";
	if(l<=r) res1+=2*(floor_sum(a,b,c,l,r));//cout<<"a,b,c "<<a<<" "<<b<<" "<<c<<"\n";
//	cout<<"res1 "<<res1<<"\n";
	
	l=u.x+1,r=min(v.x-1,xl);
	clamp(l,r,(i128)k1*c-(i128)k2*a,(i128)b*k2-1);
	a=k1,b=0,c=k2;
//	cout<<"l,r "<<l<<" "<<r<<"\n";
	if(l<=r) res1+=2*(floor_sum(a,b,c,l,r));//cout<<"a,b,c "<<a<<" "<<b<<" "<<c<<"\n";
//	cout<<"res1 "<<res1<<"\n";
	
//	cout<<"res1 "<<res1<<"\n";
	res1+=seg(P(u.x,0),u,k1,k2,xl);
	res1+=seg(P(v.x,0),v,k1,k2,xl);
	res1+=tmp[id];
//	cout<<"res1 "<<res1<<"\n";
	
	if(isin(u,k1,k2,xl)) res2+=ang[id];
	if(isin(v,k1,k2,xl)) res2+=1-ang[id];
	return mkp(res1,res2);
}

int counts(int k1,int k2,int xl){
//	cout<<"count "<<k1<<" "<<k2<<" "<<xl<<"\n";
	int res1=0; db res2=0;
	For(i,0,n-1){
		P u=a[i],v=a[(i+1)%n];
		tmp[i]=seg(u,v,k1,k2,xl);
		if(u.x==v.x)continue;
		auto [c1,c2]=calc(u,v,i,k1,k2,xl);
		if(u.x<v.x) res1-=c1,res2-=c2;
		else res1+=c1,res2+=c2;
	}
	For(i,0,n-1){
		if(isin(a[i],k1,k2,xl)) res2+=ang2[i];
	//	res1+=seg(a[i],a[(i+1)%n],k1,k2,xl);
		res1+=tmp[i];
	}
	int res=res1+round(res2);
//	cout<<"Res "<<res<<"\n";
	res/=2;
	return res;
}

void work()
{
	n=read(),k=read();
	For(i,0,n-1)a[i].read();
	For(i,0,n-1){
		P u=a[i]-a[(i+n-1)%n],v=a[i]-a[(i+1)%n];
		ang2[i]=atan2(u*v,u%v);
		if(ang2[i]<0) ang2[i]+=2*pi;
		ang2[i]/=pi;
		u=a[i],v=a[(i+1)%n];
		if(u.x>v.x)swap(u,v);
		if(u.x==v.x)ang[i]=0;
		else ang[i]=((v-u).ang()+pi/2)/pi;
	}
	int l=0,r=2*V;
	while(l+1!=r){
		int mid=l+r>>1;
		pii kk=getid(mid);
		if(counts(kk.fi,kk.se,W)>=k)r=mid;
		else l=mid;
	}
	pii k1=getid(l),k2=getid(r);
	int rk=k-counts(k1.fi,k1.se,W);
	l=0,r=W;
	while(l+1!=r){
		int mid=l+r>>1;
		if(counts(k2.fi,k2.se,mid)-counts(k1.fi,k1.se,mid)>=rk)r=mid;
		else l=mid;
	}
	int ry=(((i128)r*k2.fi)/k2.se);
	cout<<r<<" "<<ry<<"\n";
}

signed main()
{
	int T=read();
	while(T--)work();
	return 0;
}
/*

*/
```

---

