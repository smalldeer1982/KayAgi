# Letter A

## 题目描述

Little Petya learns how to write. The teacher gave pupils the task to write the letter $ A $ on the sheet of paper. It is required to check whether Petya really had written the letter $ A $ .

You are given three segments on the plane. They form the letter $ A $ if the following conditions hold:

- Two segments have common endpoint (lets call these segments first and second), while the third segment connects two points on the different segments.
- The angle between the first and the second segments is greater than $ 0 $ and do not exceed $ 90 $ degrees.
- The third segment divides each of the first two segments in proportion not less than $ 1/4 $ (i.e. the ratio of the length of the shortest part to the length of the longest part is not less than $ 1/4 $ ).

## 样例 #1

### 输入

```
3
4 4 6 0
4 1 5 2
4 0 4 4
0 0 0 6
0 6 2 -4
1 1 0 1
0 0 0 5
0 5 2 -1
1 2 0 1
```

### 输出

```
YES
NO
YES
```

# 题解

## 作者：Limit (赞：9)

呀，第二篇CF的计算几何题解终于出来了QAQ...
这题比CF1C难了一点，但还是计算几何的基础题QAQ
```cpp
//代码看起来比较长
#include<iostream>//头文件
#include<cstdio>
#include<cmath>
#include<string.h>
#include<algorithm>
using namespace std;
int i,j,k,i1,i2,i3,t;
bool pd;
double X1[4],Y1[4],X2[4],Y2[4];//记录下每一条边
bool ans(bool a,bool b)//判断答案
{
  if(a)return a;else return b;
}
double sqr(double a)//平方
{
  return a*a;
}
double far(double X1,double Y1,double X2,double Y2)//计算两点之间距离
{
  return sqrt(sqr(X1-X2)+sqr(Y1-Y2));
}
bool yes(double X1,double Y1,double X2,double Y2,double X3,double Y3)//判断(X3,Y3)是否在(X1,Y1)-(X2,Y2)这条线段上
{
  double a,b;
  if(X3>max(X1,X2)||X3<min(X1,X2))return false;//判断X3是否在X1和X2之间
  if(Y3>max(Y1,Y2)||Y3<min(Y1,Y2))return false;//判断Y3是否在Y1和Y2之间
  if(X1==X2)return X1==X3;//如果改线段是垂直于X轴
  if(Y1==Y2)return Y1==Y3;//如果改线段是垂直于Y轴
  a=(Y1-Y2)/(X1-X2);//通过正切算出改一次函数斜率
  b=Y1-X1*a;//带入算出b
  return abs(a*X3+b-Y3)<=0.001;//带入该解析式，判断是否成立
}
bool solve(int a,int b,int c)//核心代码
{
  double dx,dy,long1,long2,long3;
  bool pd=false;
  //看着比较烦，判断a,b两线段是否是从同一个出发
  if((X1[a]==X1[b])&&(Y1[a]==Y1[b]))
  {dx=X1[a];dy=Y1[b];pd=!(pd);long3=far(X2[a],Y2[a],X2[b],Y2[b]);}
  if((X1[a]==X2[b])&&(Y1[a]==Y2[b]))
  {dx=X1[a];dy=Y2[b];pd=!(pd);long3=far(X2[a],Y2[a],X1[b],Y1[b]);}
  if((X2[a]==X1[b])&&(Y2[a]==Y1[b]))
  {dx=X2[a];dy=Y1[b];pd=!(pd);long3=far(X1[a],Y1[a],X2[b],Y2[b]);}
  if((X2[a]==X2[b])&&(Y2[a]==Y2[b]))
  {dx=X2[a];dy=Y2[b];pd=!(pd);long3=far(X1[a],Y1[a],X1[b],Y1[b]);}
  if(!(pd))return 0;else pd=0;//不是则退出
  long1=far(X1[a],Y1[a],X2[a],Y2[a]);//计算出a的长
  long2=far(X1[b],Y1[b],X2[b],Y2[b]);//计算出b的长
  if(sqr(long3)>sqr(long1)+sqr(long2))return 0;//利用...定理判断角度
  if(yes(X1[a],Y1[a],X2[a],Y2[a],X1[c],Y1[c])//判断c是否在a,b上
  &&yes(X1[b],Y1[b],X2[b],Y2[b],X2[c],Y2[c]))
  {
    pd=!(pd);
    //算出截出的两节的长
    long1=far(X1[a],Y1[a],X1[c],Y1[c]);
    long2=far(X2[a],Y2[a],X1[c],Y1[c]);
    if(long1<=0)return 0;
    if(long2<=0)return 0;
    if(min(long1,long2)*4<max(long1,long2))return false;//判断是否成立
    long1=far(X1[b],Y1[b],X2[c],Y2[c]);
    long2=far(X2[b],Y2[b],X2[c],Y2[c]);
    if(long1<=0)return 0;
    if(long2<=0)return 0;
    if(min(long1,long2)*4<max(long1,long2))return false;
  }
  if(yes(X1[a],Y1[a],X2[a],Y2[a],X2[c],Y2[c])//c的两端反一下再判断
  &&yes(X1[b],Y1[b],X2[b],Y2[b],X1[c],Y1[c]))
  {
    pd=!(pd);
    long1=far(X1[a],Y1[a],X2[c],Y2[c]);
    long2=far(X2[a],Y2[a],X2[c],Y2[c]);
    if(long1<=0)return 0;
    if(long2<=0)return 0;
    if(min(long1,long2)*4<max(long1,long2))return false;
    long1=far(X1[b],Y1[b],X1[c],Y1[c]);
    long2=far(X2[b],Y2[b],X1[c],Y1[c]);
    if(long1<=0)return 0;
    if(long2<=0)return 0;
    if(min(long1,long2)*4<max(long1,long2))return false;
  }
  //如果都符合则返回true
  return pd;
}
int main()
{
  cin>>t;
  for(i=1;i<=t;i++)
  {
  	pd=false;
  	for(j=1;j<=3;j++)
    cin>>X1[j]>>Y1[j]>>X2[j]>>Y2[j];
    //读入
    if(!(pd))
    {
      //枚举a,b两边
      for(i1=1;i1<=2;i1++)
      for(i2=i1+1;i2<=3;i2++)
      pd=ans(pd,solve(i1,i2,6-i1-i2));
    }
    else
    pd=false;
    if(pd)cout<<"YES"<<endl;else cout<<"NO"<<endl;//输出
  }
  return 0;
}
```
调了好久呀...


---

## 作者：Battereamer (赞：4)

很好的一道计算几何入门题。

#### 写一下做题之前需要的准备吧：

1.能熟练运用解析几何的一些简单公式。

2.对计算机的计算几何有一定了解，这道题主要用到的是角度判断和截线段公式，如果不会的话可以先去学习学习。

3.细心和耐心，我们可以感性的把计算几何理解为要运用公式的大模拟。所以一定不要嫌弃代码长，判断语句多这些令人烦恼的问题。

### 如果你拥有了计算几何的基础知识，那么按照题意慢慢写，你一定可以成功的！

我就直接给代码了，哪一步在做什么代码里面有注释：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
ll dis(ll x,ll y,ll x1,ll y1) {return (x-x1)*(x-x1)+(y-y1)*(y-y1);}
struct node {
ll x[2],y[2];
}data[3];

int main() {
    int ca;
    cin>>ca;
   	while(ca--) {
       	bool sign=false;
       	for(int i=0;i<3;i++)
       	cin>>data[i].x[0]>>data[i].y[0]>>data[i].x[1]>>data[i].y[1];
       	for(int i=0;i<3;i++)
       	if(data[i].x[0]==data[i].x[1]&&data[i].y[0]==data[i].y[1]) {      //如果出现不是线段，也就是两个endpoint一样了，输出NO
       	    sign=true;
       	    break;
       	}
       	if(sign) {cout<<"NO"<<endl;continue;}
       	sign=false;
       	int flagi=0,flagj=0;
       	int signi=0,signj=0;
       	ll xt,yt;
       	for(int i=0;i<3;i++)
       		for(int k=i+1;k<3;k++)
       			for(int j=0;j<2;j++)
       				for(int l=0;l<2;l++){
			       	    if(data[i].x[j]==data[k].x[l]&&data[i].y[j]==data[k].y[l]) {
			       	        if(!sign) {
				       	        flagi=i,flagj=k;
				       	        signi=j,signj=l;
				       	        xt=data[i].x[j],yt=data[i].y[j];
				       	        sign=true;
			       	        }
			       	        else sign=false;//如果出现两个点以上的重复坐标，输出NO
			       	    }
       				}
       	if(!sign) {cout<<"NO"<<endl;continue;}
       	sign=false;
       	ll a=xt,b=yt,c=data[flagi].x[signi^1],d=data[flagi].y[signi^1],e=data[flagj].x[signj^1],f=data[flagj].y[signj^1];//(a,b)为顶点,(c,d),(e,f)为
       	int flagk;         //另两个顶点
       	ll g,h,m,n;   //查找第三条边，并将在(a,b)-(c,d)边上的点赋值为(g,h)，在(a,b)-(e,f)边上的点赋值为(m,n)
       	for(int i=0;i<3;i++)
       	   	if(i!=flagi&&i!=flagj) {
				  flagk=i;
				  break;
			}
       	   	for(int i=0;i<2;i++) {
       	       	if(((data[flagk].x[i]-a)*(d-b)==(data[flagk].y[i]-b)*(c-a))&&((data[flagk].x[i^1]-a)*(f-b)==(data[flagk].y[i^1]-b)*(e-a))) {
       	           g=data[flagk].x[i],h=data[flagk].y[i],m=data[flagk].x[i^1],n=data[flagk].y[i^1];
       	           sign=true;
       	           break;
       	       	}
       	   	}
       	   	if(((g<min(a,c)||g>max(a,c))||(h<min(b,d)||h>max(b,d)))||((m<min(a,e)||m>max(a,e))||(n<min(b,f)||n>max(b,f)))) {cout<<"NO"<<endl;continue;}
				        //若第三条边的两个端点有一个不在前两条边上，输出NO
       	   	if(g==m&&h==n) sign=false;
       	   	if((abs((g-m)*(d-b))==abs((h-n)*(c-a)))||(abs((g-m)*(f-b))==abs((h-n)*(e-a)))) sign=false;//如果第三条边的两个点都在前两条边的某条边上，输出NO
       	   	if(!sign) {cout<<"NO"<<endl;continue;}
       	   	sign=false;
       		if(dis(a,b,c,d)+dis(a,b,e,f)>=dis(c,d,e,f)) {     //判断夹角
		       	ll minedge[2],maxedge[2];                //一下判断较长边是否小于等于4倍的较短边
		       	if(dis(g,h,a,b)>dis(g,h,c,d)) {
		       	    minedge[0]=dis(g,h,c,d);
		       	    maxedge[0]=dis(g,h,a,b);
		       	} else {
		       	    minedge[0]=dis(g,h,a,b);
		       	    maxedge[0]=dis(g,h,c,d);
		      	}
		      	if(dis(m,n,a,b)>dis(m,n,e,f)) {
		       	    minedge[1]=dis(m,n,e,f);
		       	    maxedge[1]=dis(m,n,a,b);
		       	} else {
		           minedge[1]=dis(m,n,a,b);
		           maxedge[1]=dis(m,n,e,f);
		       	}
		       	if(minedge[0]*16>=maxedge[0]&&minedge[1]*16>=maxedge[1])
		            sign=true;
       		}
       		if(sign) cout<<"YES"<<endl;
       		else cout<<"NO"<<endl;
   	}
    return 0;
}
```

（为了让代码看起来清楚一些，我竟然没有打空格）

祝大家早日A题。

---

## 作者：hxhhxh (赞：3)

~~这原本是一道很水的黑题。~~
## 题意
给定平面上的三条线段，求它们能否组成“ A ”；多组数据。
#### 组成“ A ”的条件：
1. 两条线段有公共端点（设为线段 $ a $ 和线段 $ b $ ），且夹角为锐角或直角。

2. 第三条线段 $ c $ 的两个端点分别在线段 $ a $ 和线段 $ b $ 上。

3. $ c $ 在 $ a $ 上截出的线段中， $ \frac{\text{ 短 }}{\text{ 长 }}\leq \frac{1}{4} $ ，在 $ b $ 上同理。

## 思路
这是一道**计算几何**题，对于每组输入，依次判断是否满足每一个条件。

只要有初中的一次函数知识+知道余弦定理就可以做了。

对于第一条限制，只需要枚举任意两个线段有没有公共端点并判断角度就行了。
```cpp
a1=(a.l==b.l);
a2=(a.l==b.r);
a3=(a.l==c.l);
a4=(a.l==c.r);
a5=(a.r==b.l);
a6=(a.r==b.r);
a7=(a.r==c.l);
a8=(a.r==c.r);
a9=(b.l==c.l);
a10=(b.l==c.r);
a11=(b.r==c.l);
a12=(b.r==c.r);
int ggdds=a1+a2+a3+a4+a5+a6+a7+a8+a9+a10+a11+a12;
if(ggdds>=2||ggdds==0){
	printf("NO\n");
	continue;
}

```
对于角度的判断。由余弦定理得：

$$ a^2+b^2=c^2-2ab\times\cos\space\gamma $$

$$ c^2=a^2+b^2+2ab\times\cos\space\gamma $$

当 $ \cos\space\gamma\geq 0 $ 时满足条件（ $ \gamma $ 为锐角或直角），此时 $ c^2\geq a^2+b^2 $ 。
```cpp
if(lenf(a)+lenf(b)<lenf((lll){a.r,b.r})) printf("NO\n");
//lenf(a)表示线段a的长度的平方
```

第一条限制就做完了。

------------

对于第二条限制，只需要判断三点共线，就像这样：

$$ \frac{cc.y-aa.y}{cc.x-aa.x}=\frac{bb.y-aa.y}{bb.x-aa.x} $$

点 $ cc $ 与点 $ aa $ 之间的斜率和点 $ bb $ 与点 $ aa $ 之间的斜率一样。

但这样做肯定会爆精度，所以我们移个项：

 $$ (cc.y-aa.y)\times(bb.x-aa.x)=(cc.x-aa.x)\times(bb.y-aa.y) $$

还要判断横纵坐标大小关系。
```cpp
bool sdgx(point aa,point bb,point cc){
	if((cc.y-aa.y)*(bb.x-aa.x)==(bb.y-aa.y)*(cc.x-aa.x)) return true;//叉积 
	return false;
}
bool on(point cccc,lll aa){
	if((cccc.x-aa.l.x)*(cccc.x-aa.r.x)>0) return false;
	if((cccc.y-aa.l.y)*(cccc.y-aa.r.y)>0) return false;
	if(!sdgx(aa.l,aa.r,cccc)) return false;
	return true;
}
```
------------
对于第三条限制，可以直接算出长度：

 $$ lena=\sqrt{(s.l.x-s.r.x)^2+(s.l.y-s.r.y)^2} $$
 
 $$ \min(lena,lenb)\times4\leq\max(lena,lenb) $$

对， 还是 **精度的问题**。

把上面的式子平方可得：

$$ lena^2=(s.l.x-s.r.x)^2+(s.l.y-s.r.y)^2 $$

$$ \min(lena^2,lenb^2)\times16\leq\max(lena^2,lenb^2) $$

就可以这样写了

```cpp
int u=lenf((lll){a.l,c.l}),d=lenf((lll){a.r,c.l});
if(u>d*16||u*16<d){
	printf("NO\n");
	continue;
}
```
## 注意事项

很多地方都**会爆**`int`**！！**

## 完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
struct point{//点 
	int x,y;
	bool operator ==(const point rees)const{
		return x==rees.x&&y==rees.y;
	}
};
struct lll{//线 
	point l,r;
	bool operator ==(const lll rees)const{
		return (l==rees.l&&r==rees.r)||(l==rees.r&&r==rees.l);
	}
}a,b,c;
int lenf(lll s){//长度的平方 
	return (s.l.x-s.r.x)*(s.l.x-s.r.x)+(s.l.y-s.r.y)*(s.l.y-s.r.y);
}
bool sdgx(point aa,point bb,point cc){//判断三点是否共线
    if((cc.y-aa.y)*(bb.x-aa.x)==(bb.y-aa.y)*(cc.x-aa.x)) return true;//叉积 
    return false;
}
bool on(point cccc,lll aa){//一个点是否在线段上
	if((cccc.x-aa.l.x)*(cccc.x-aa.r.x)>0) return false;
	if((cccc.y-aa.l.y)*(cccc.y-aa.r.y)>0) return false;
	if(!sdgx(aa.l,aa.r,cccc)) return false;
	return true;
}
bool a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",&a.l.x,&a.l.y,&a.r.x,&a.r.y,&b.l.x,&b.l.y,&b.r.x,&b.r.y,&c.l.x,&c.l.y,&c.r.x,&c.r.y);
		if(a==b||b==c||c==a){//有两个（三个）一模一样的线段 
			printf("NO\n");
			continue; 
		}
		if(a.l==a.r||b.l==b.r||c.l==c.r){//a（或者b，c）不是一条线段 
			printf("NO\n");
			continue; 
		}
		a1=(a.l==b.l);
		a2=(a.l==b.r);
		a3=(a.l==c.l);
		a4=(a.l==c.r);
		a5=(a.r==b.l);
		a6=(a.r==b.r);
		a7=(a.r==c.l);
		a8=(a.r==c.r);
		a9=(b.l==c.l);
		a10=(b.l==c.r);
		a11=(b.r==c.l);
		a12=(b.r==c.r);
		//判断哪两个线段有公共端点 
		int ggdds=a1+a2+a3+a4+a5+a6+a7+a8+a9+a10+a11+a12;
		if(ggdds>=2||ggdds==0){
			printf("NO\n");//特判三角形，没有公共顶点的线段等情况 
			continue;
		} 
		if(a2) swap(b.l,b.r);
		if(a3) swap(b,c);
		if(a4) swap(c.l,c.r),swap(b,c);
		if(a5) swap(a.l,a.r);
		if(a6) swap(a.l,a.r),swap(b.l,b.r);
		if(a7) swap(a.l,a.r),swap(b,c);
		if(a8) swap(a.l,a.r),swap(c.l,c.r),swap(b,c);
		if(a9) swap(a,c);
		if(a10) swap(c.l,c.r),swap(a,c);
		if(a11) swap(a,c),swap(b.l,b.r);
		if(a12) swap(c.l,c.r),swap(b.l,b.r),swap(a,c);
		//这里可以保证a.l==b.l
		if(lenf(a)+lenf(b)<lenf((lll){a.r,b.r})) printf("NO\n");//由余弦定理判定是否为钝角 
		else if(sdgx(a.l,a.r,b.r)) printf("NO\n");
		else{
			if(!(on(c.l,a)||on(c.l,b))) printf("NO\n");//c.l不在a或b上 
			else if(!(on(c.r,a)||on(c.r,b))) printf("NO\n");//c.r不在a或b上 
			else if(on(c.l,a)&&on(c.r,a)) printf("NO\n");//c与a重合 
			else if(on(c.l,b)&&on(c.r,b)) printf("NO\n");//c与b重合 
			else{
				if(on(c.r,a)) swap(c.l,c.r);
				//这里可以保证c.l在a上，c.r在b上 
				int u=lenf((lll){a.l,c.l}),d=lenf((lll){a.r,c.l});
				if(u>d*16||u*16<d){
					printf("NO\n");
					continue;
				}
				u=lenf((lll){b.l,c.r}),d=lenf((lll){b.r,c.r});
				if(u>d*16||u*16<d){
					printf("NO\n");
					continue;
				}
				printf("YES\n");
			}
		}
	}
	return 0;
}
```
送一组样例：

Input:
```
2
0 0 10 10
10 10 20 0
4 4 6 6
0 0 0 5
0 5 2 0
1 2 0 1
```
Output:
```
NO
NO
```

---

## 作者：Fido_Puppy (赞：2)

余弦定理是这道题最难的一个点，

得用这个高中的知识来解决两条线段夹角的问题 ~~（我同桌说他小学学过？）~~。

![](https://cdn.luogu.com.cn/upload/image_hosting/cmgqphk1.png)

首先，我们用余弦定理可得：

$$\cos\alpha=\frac{b^2+c^2-a^2}{2bc}$$

接着，对于 $\cos\alpha$：


$$ \left\{
\begin{aligned}
\alpha & < 90\degree &\cos\alpha>0 \\
\alpha & = 90\degree& \cos\alpha=0 \\
\alpha & > 90\degree& \cos\alpha<0
\end{aligned}
\right.
$$

当然这道题还得注意一下精度的问题，不要用 $sqrt$ 运算，尽量都用整数来运算，最后函数返回结果时可以用除法运算。

然后就没有然后了……

## Talk is cheap, show your code.

```cpp
//Always realize that ZCH is yyds!!!
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
LL t;
LL xs[4],ys[4],xf[4],yf[4];
inline LL dis(LL a,LL b,LL c,LL d) {
	return (a-c)*(a-c)+(b-d)*(b-d);
}
inline bool angle(LL x,LL y,LL a,LL b,LL c,LL d) {
	if ((long double)(x-a)/(long double)(y-b)==(long double)(x-c)/(long double)(y-d)) return false;
	LL D=dis(x,y,a,b)+dis(x,y,c,d)-dis(a,b,c,d);
	if (D>=0) return true;else return false;
}
inline bool on(LL x,LL y,LL a,LL b,LL c,LL d) {
	if (x>max(a,c)||x<min(a,c)) return false;
	if (y>max(b,d)||y<min(b,d)) return false;
	if (x==a&&y==b||x==c&&y==d) return false;
	if (x==a&&x==c||y==b&&y==d) return true;
	if ((long double)(x-a)/(long double)(c-x)==(long double)(y-b)/(long double)(d-y)) return true;
	else return false; 
}
inline bool segment(LL x,LL y,LL a,LL b,LL c,LL d,LL e,LL f,LL g,LL h) {
	if (on(e,f,x,y,a,b)) {
		if (!on(g,h,x,y,c,d)) return false;
		LL long1=dis(e,f,x,y),long2=dis(e,f,a,b),long3=dis(g,h,x,y),long4=dis(g,h,c,d);
		LL Max1=max(long1,long2),Min1=min(long1,long2);
		LL Max2=max(long3,long4),Min2=min(long3,long4);
		if (Max1>Min1*16) return false;
		if (Max2>Min2*16) return false;
		return true;
	}
	else if (on(g,h,x,y,a,b)) {
		if (!on(e,f,x,y,c,d)) return false;
		LL long1=dis(g,h,x,y),long2=dis(g,h,a,b),long3=dis(e,f,x,y),long4=dis(e,f,c,d);
		LL Max1=max(long1,long2),Min1=min(long1,long2);
		LL Max2=max(long3,long4),Min2=min(long3,long4);
		if (Max1>Min1*16) return false;
		if (Max2>Min2*16) return false;
		return true;
	}
	else return false;
}
signed main() {
	cin>>t;
	while (t--) {
		for(LL i=1;i<=3;i++) cin>>xs[i]>>ys[i]>>xf[i]>>yf[i];
		bool flag=false;
		for(LL i=1;i<3;i++)
			for(LL j=i+1;j<=3;j++) {
				LL k=6-i-j;
				if (xs[i]==xs[j]&&ys[i]==ys[j]) {
					if (angle(xs[i],ys[i],xf[i],yf[i],xf[j],yf[j])
					&&segment(xs[i],ys[i],xf[i],yf[i],xf[j],yf[j],xs[k],ys[k],xf[k],yf[k]))
						flag=true;
				}
				if (xs[i]==xf[j]&&ys[i]==yf[j]) {
					if (angle(xs[i],ys[i],xf[i],yf[i],xs[j],ys[j])
					&&segment(xs[i],ys[i],xf[i],yf[i],xs[j],ys[j],xs[k],ys[k],xf[k],yf[k]))
						flag=true;
				}
				if (xf[i]==xs[j]&&yf[i]==ys[j]) {
					if (angle(xf[i],yf[i],xs[i],ys[i],xf[j],yf[j])
					&&segment(xf[i],yf[i],xs[i],ys[i],xf[j],yf[j],xs[k],ys[k],xf[k],yf[k]))
						flag=true;
				}
				if (xf[i]==xf[j]&&yf[i]==yf[j]) {
					if (angle(xf[i],yf[i],xs[i],ys[i],xs[j],ys[j])
					&&segment(xf[i],yf[i],xs[i],ys[i],xs[j],ys[j],xs[k],ys[k],xf[k],yf[k]))
						flag=true;
				}
			}
		if (flag) cout<<"Licykocyyds"<<endl;else cout<<"Hoveryyyds"<<endl;
	}
	return 0;
}
```

完结撒花！ の_^

---

## 作者：liuyifan (赞：2)

## 模拟+简单的计算几何
个人认为我的代码是目前最简单的,注释见下面

code:
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")//玄学优化
#define reg register
#define ll long long
#define y1 liuifan_y1
#define inf 0x3f3f3f3f
#define iinf 0x3f3f3f3f3f3f3f3f
#define data liuyifan_data
#define next liuyifan_next
#define ture true
#define flase false
#define lowbit(x) x&(-x)
using namespace std;
struct data
{
    int x,y,z,zz;
}a[10];//存边 
int t,x,y,m,n,p,q,x1,y1,x2,y2,c1,c2,flag;
inline int pd1(int a,int b,int c,int d,int e,int f)//判断是否三点共线
{
    if((ll)(f-b)*(c-a)==(ll)(d-b)*(e-a))
        return 1;
    return 0;
}
inline int pd2(int x,int y,int a,int b,int p,int q)//判断两线段的夹角是否在0~90之间
{
    if((ll)(a-x)*(p-x)+(ll)(b-y)*(q-y)<0)
        return 0;
    return 1;
}
inline int pd3(int x,int y,int m,int n,int a,int b)//判断分割的线段是否长：短<0.25
{
    if(x!=a)
    {
        if(a>x)
        {
            if((a-x)*5<(m-x)) return 0;
            if((a-x)*5>(m-x)*4) return 0;
            return 1;
        }
        else
        {
            if((x-a)*5<(x-m)) return 0;
            if((x-a)*5>(x-m)*4) return 0;
            return 1;
        }
    }
    else
    {
        if(b>y)
        {
            if((b-y)*5<(n-y))return 0;
            if((b-y)*5>(n-y)*4)return 0;
            return 1;
        }
        else
        {
            if((y-b)*5<(y-n))return 0;
            if((y-b)*5>(y-n)*4)return 0;
            return 1;
        }
    }
}
int main()
{
    while(scanf("%d",&t)==1)//多组数据 
    {
        while(t--)//每组数据的个数 
        {
            for(reg int i=1;i<=3;i++)scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].z,&a[i].zz);
            for(reg int i=1;i<=2;i++)//开始模拟 
            for(reg int j=i+1;j<=3;j++)
            {
                if(a[i].x==a[j].x&&a[i].y==a[j].y)
                {
                    x=a[i].x,y=a[i].y;
                    m=a[i].z,n=a[i].zz;
                    p=a[j].z,q=a[j].zz;
                    c1=i;
                    c2=j;
                }
                else if(a[i].x==a[j].z&&a[i].y==a[j].zz)
                {
                    x=a[i].x,y=a[i].y;
                    m=a[i].z,n=a[i].zz;
                    p=a[j].x,q=a[j].y;
                    c1=i;
                    c2=j;
                }
                else if(a[i].z==a[j].z&&a[i].zz==a[j].zz)
                {
                    x=a[i].z,y=a[i].zz;
                    m=a[i].x,n=a[i].y;
                    p=a[j].x,q=a[j].y;
                    c1=i;
                    c2=j;
                }
                else if(a[i].z==a[j].x&&a[i].zz==a[j].y)
                {
                    x=a[i].z,y=a[i].zz;
                    m=a[i].x,n=a[i].y;
                    p=a[j].z,q=a[j].zz;
                    c1=i;
                    c2=j;
                }
            }
        	for(reg int i=1;i<=3;i++)
            if(i!=c1&&i!=c2)
            {
                x1=a[i].x,y1=a[i].y,x2=a[i].z,y2=a[i].zz;
                break;
            }
            flag=1;//注意初始化 
	        if(pd2(x,y,m,n,p,q)==0)flag=0;
	        if(flag)
	        {
	            if(pd1(x,y,m,n,x1,y1)&&pd1(x,y,p,q,x2,y2))
	            {
	                if(pd3(x,y,m,n,x1,y1)==0)flag=0;
	                if(pd3(x,y,p,q,x2,y2)==0)flag=0;
	            }
	            else if(pd1(x,y,p,q,x1,y1)&&pd1(x,y,m,n,x2,y2))
	            {
	                if(pd3(x,y,m,n,x2,y2)==0)flag=0;
	                if(pd3(x,y,p,q,x1,y1)==0)flag=0;
	            }
	            else flag=0;
	        }
	        puts(flag?"YES":"NO");//puts自带换行
    	}
    }
    return 0;
}
```

---

## 作者：hyman00 (赞：1)

# CF13B题解

## 01 前言

参(chao)考(xi)了几篇题解，终于明白了。

计算几何：照着题目说的写，注意不能用 `double` ，精度会出锅！

## 02 解法

我们可以把 $3$ 条线段打乱顺序，再把每条的 $2$ 个端点打乱顺序，就不用考虑顺序了。

- 要求 1.1 

直接判断；

- 要求 1.2 

用斜率计算( $\frac{\Delta x}{\Delta y}$ )是否在所在直线上 + 比大小判断是否在线段上；

- 要求 2 

设三角形三边长度为 $a,b,c$ ，$c$ 的对角 $\le 90$ 当且仅当 $a^2+b^2\le c^2$ ；

- 要求 3 

线段最多 4 倍，平方最多 16 倍。

## 03 代码
```c++
using namespace std;
int a[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}},b[2][2]={{0,1},{1,0}};
pii c[3][2],d[3][2];

double dis(pii a,pii b){ // 线段ab长度平方 
	return (double)((a.F-b.F)*(a.F-b.F)+(a.S-b.S)*(a.S-b.S));
}

bool in(pii a,pii b,pii c){ // 点a是否在线段bc上 
	return (a.F-b.F)*(b.S-c.S)==(a.S-b.S)*(b.F-c.F);
}

signed main()
{
	int tc;
	cin>>tc;
	while(tc--){
		rep(i,3)rep(j,2)cin>>c[i][j].F>>c[i][j].S;
		int ok=1;
      
		rep(msk,48){
			rep(i,3)rep(j,2)
				d[i][j]=c[a[msk/8][i]][b[(msk>>a[msk/8][i])&1][j]];
                                // 重新排列
			if(d[0][0]!=d[1][0])continue;
				// 要求1.1：其中的两条线段有共同的端点
			if(!in(d[2][0],d[0][0],d[0][1])||min(d[0][0].F,d[0][1].F)>d[2][0].F
				||d[2][0].F>max(d[0][0].F,d[0][1].F))continue;
			if(!in(d[2][1],d[1][0],d[1][1])||min(d[1][0].F,d[1][1].F)>d[2][1].F
				||d[2][1].F>max(d[1][0].F,d[1][1].F))continue;
				// 要求1.2：第三条线段的端点分别在这两条不同的线段上
			if(dis(d[0][0],d[0][1])+dis(d[1][0],d[1][1])<dis(d[0][1],d[1][1]))continue;
				// 要求2：夹角必须大于0度小于等于90度
			int dis1=dis(d[0][0],d[2][0]),dis2=dis(d[0][1],d[2][0]);
			if(dis1>16*dis2||dis2>16*dis1)continue;
			dis1=dis(d[1][0],d[2][1]),dis2=dis(d[1][1],d[2][1]);
			if(dis1>16*dis2||dis2>16*dis1)continue;
				// 要求3：第三条线段截得的另外两条线段的较小长度与较大长度的比值必须大于等于1/4
			cout<<"YES\n";ok=0;break;
				// 满足条件，输出
		}
		if(ok)cout<<"NO\n";
			// 不满足条件，输出 
	}
	return 0;
}
```

---

## 作者：cancan123456 (赞：1)

其实我第一次写完的时候就已经是正解了，但是被卡精度了……

思路：模拟。

让我们按照题目一步一步来：

给定三条线段，请你判断这三条线段能否组成字母 ```A```。

判定条件：

1. 其中的两条线段有共同的端点（我们称它们为第一条，第二条线段），第三条线段的端点分别在这两条不同的线段上。

2. 第一条和第二条线段的夹角必须大于 0 度小于等于 90 度。

3. 第三条线段截得的另外两条线段的较小长度与较大长度的比值必须大于等于 $\dfrac{1}{4}$。

首先我们定义几个有用的函数：

```cpp
bool __InRange(ll a, ll b, ll c) {
	return a <= b && b <= c;
}
bool InRange(ll a, ll b, ll c) { // 判断 b 是否在 a 和 c 之间 
	return __InRange(a, b, c) || __InRange(c, b, a);
}
```

还有两个结构体（点和线段），方便处理：

```cpp
struct Point {
	ll x, y;
	Point(ll x = 0, ll y = 0): x(x), y(y) {}
	void input() { // 输入 
		scanf("%lld %lld", &x, &y);
	}
};
bool operator == (const Point & a, const Point & b) { // 两个点是否相同 
	return a.x == b.x && a.y == b.y;
}
Point operator + (const Point & a, const Point & b) { // 向量加法 
	return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point & a, const Point & b) { // 向量减法 
	return Point(a.x - b.x, a.y - b.y);
}
ll operator * (const Point & a, const Point & b) { // 向量点积 
	return a.x * b.x + a.y * b.y;
}
ll operator & (const Point & a, const Point & b) { // 向量叉积 
	return a.x * b.y - a.y * b.x;
}
struct Segment {
	Point a, b;
	void input() { // 输入 
		a.input();
		b.input();
	}
} s1, s2, s3; // 输入的三条线段 
bool OnSegment(const Segment & s, const Point & a) { // 判断点是否在线段上 
	if (InRange(s.a.x, a.x, s.b.x) && InRange(s.a.y, a.y, s.b.y)) {
		if (((s.a - a) & (s.b - a)) == 0) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
```

然后就可以开始模拟了！

首先输入：

```cpp
s1.input();
s2.input();
s3.input();
```

处理第一个条件：是否存在两条线段的两个端点相同，这里我分了 12 种情况讨论：

```
s1.a 与 s2.a
s1.a 与 s2.b
s1.b 与 s2.a
s1.b 与 s2.b
s1.a 与 s3.a
s1.a 与 s3.b
s1.b 与 s3.a
s1.b 与 s3.b
s2.a 与 s3.a
s2.a 与 s3.b
s2.b 与 s3.a
s2.b 与 s3.b

```

另外，为了方便下面的处理，如果满足第一个条件，我们通过交换线段与端点使得 ```s1``` 和 ```s2``` 分别为第一和第二条线段，且 ```s1.a``` 与 ```s2.a``` 相同。

转换成代码：

```cpp
if (s1.a == s2.a) {
	swap(s1, s1);
	swap(s2, s2);
	swap(s1.a, s1.a);
	swap(s2.a, s2.a);
} else if (s1.a == s2.b) {
	swap(s1, s1);
	swap(s2, s2);
	swap(s1.a, s1.a);
	swap(s2.b, s2.a);
} else if (s1.b == s2.a) {
	swap(s1, s1);
	swap(s2, s2);
	swap(s1.b, s1.a);
	swap(s2.a, s2.a);
} else if (s1.b == s2.b) {
	swap(s1, s1);
	swap(s2, s2);
	swap(s1.b, s1.a);
	swap(s2.b, s2.a);
} else if (s1.a == s3.a) {
	swap(s1, s1);
	swap(s3, s2);
	swap(s1.a, s1.a);
	swap(s2.a, s2.a);
} else if (s1.a == s3.b) {
	swap(s1, s1);
	swap(s3, s2);
	swap(s1.a, s1.a);
	swap(s2.b, s2.a);
} else if (s1.b == s3.a) {
	swap(s1, s1);
	swap(s3, s2);
	swap(s1.b, s1.a);
	swap(s2.a, s2.a);
} else if (s1.b == s3.b) {
	swap(s1, s1);
	swap(s3, s2);
	swap(s1.b, s1.a);
	swap(s2.b, s2.a);
} else if (s2.a == s3.a) {
	swap(s2, s1);
	swap(s3, s2);
	swap(s1.a, s1.a);
	swap(s2.a, s2.a);
} else if (s2.a == s3.b) {
	swap(s2, s1);
	swap(s3, s2);
	swap(s1.a, s1.a);
	swap(s2.b, s2.a);
} else if (s2.b == s3.a) {
	swap(s2, s1);
	swap(s3, s2);
	swap(s1.b, s1.a);
	swap(s2.a, s2.a);
} else if (s2.b == s3.b) {
	swap(s2, s1);
	swap(s3, s2);
	swap(s1.b, s1.a);
	swap(s2.b, s2.a);
} else {
	printf("NO\n");
	return;
}
```

接下来，判断 ```s3``` 的两个端点是否在 ```s1``` 和 ```s2``` 上：

```cpp
if (OnSegment(s1, s3.a)) {
	swap(s3.a, s3.a);
} else if (OnSegment(s1, s3.b)) {
	swap(s3.b, s3.a);
} else {
	printf("NO\n");
	return;
}
if (not OnSegment(s2, s3.b)) {
	printf("NO\n");
	return;
}
```

另外，为了方便下面的处理，如果满足上面的条件，我们通过交换线段的顶点使得使 ```s3.a``` 在 ```s1``` 上，```s3.b``` 在 ```s2``` 上。

第二个条件：判断 ```s1``` 和 ```s2``` 的夹角是否大于 0 度且小于 90 度。

这里我用了向量点积计算夹角的余弦值。

```cpp
ll cosangle = (s1.b - s1.a) * (s2.b - s2.a);
if (cosangle < 0) {
	printf("NO\n");
	return;
}
```

第三个条件：第三条线段截得的另外两条线段的较小长度与较大长度的比值必须大于等于 $\dfrac{1}{4}$。

首先画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ujlkw2w7.png)

我们假设较长的线段是 $a$，较短线段是 $b$，根据题意，得：

$$\dfrac{b}{a}\ge\dfrac{1}{4}$$

整理得：

$$4b\ge a$$

$$5b\ge a+b$$

即：线段长度 $\le5b$，这就说明了较小线段的长度至少是 $AB$ 长度的 $\dfrac{1}{5}$。

那么我们判断的思路就出来了：

首先分别计算出 $x, y$ 的最小值和最大值，与 ```s3``` 的端点进行比较。

具体实现：

```cpp
ll min5x, max5x;
ll min5y, max5y;
```

这四个变量代表 $x, y$ 的最小值和最大值 $\times5$（因为 ```double``` 会被卡精度导致过不了，多以需要乘 5 变成整数）。

```cpp
min5x = s1.a.x * 4 + s1.b.x;
max5x = s1.a.x + s1.b.x * 4;
min5y = s1.a.y * 4 + s1.b.y;
max5y = s1.a.y + s1.b.y * 4;
```

根据我们刚刚的结果计算出它们。

```cpp
if (not (InRange(min5x, s3.a.x * 5, max5x) and InRange(min5y, s3.a.y * 5, max5y))) {
	printf("NO\n");
	return;
}
```

判断 ```s3.a``` 是否位于区间内。

```s3.b``` 的判断也一样：

```cpp
min5x = s2.a.x * 4 + s2.b.x;
max5x = s2.a.x + s2.b.x * 4;
min5y = s2.a.y * 4 + s2.b.y;
max5y = s2.a.y + s2.b.y * 4;
if (not (InRange(min5x, s3.b.x * 5, max5x) and InRange(min5y, s3.b.y * 5, max5y))) {
	printf("NO\n");
	return;
}
```

然后，如果这三条线段经过了上面的诸多判断之后仍然没有问题，那么我们就

```cpp
printf("YES\n");
```

~~庆祝一下！~~
输出结果！

最后，给出完整代码：

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
bool __InRange(ll a, ll b, ll c) {
	return a <= b && b <= c;
}
bool InRange(ll a, ll b, ll c) {
	return __InRange(a, b, c) || __InRange(c, b, a);
}
struct Point {
	ll x, y;
	Point(ll x = 0, ll y = 0): x(x), y(y) {}
	void input() {
		scanf("%lld %lld", &x, &y);
	}
};
bool operator == (const Point & a, const Point & b) {
	return a.x == b.x && a.y == b.y;
}
Point operator + (const Point & a, const Point & b) {
	return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point & a, const Point & b) {
	return Point(a.x - b.x, a.y - b.y);
}
ll operator * (const Point & a, const Point & b) {
	return a.x * b.x + a.y * b.y;
}
ll operator & (const Point & a, const Point & b) {
	return a.x * b.y - a.y * b.x;
}
struct Segment {
	Point a, b;
	void input() {
		a.input();
		b.input();
	}
} s1, s2, s3;
bool OnSegment(const Segment & s, const Point & a) {
	if (InRange(s.a.x, a.x, s.b.x) && InRange(s.a.y, a.y, s.b.y)) {
		if (((s.a - a) & (s.b - a)) == 0) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
void inline Solve() {
	s1.input();
	s2.input();
	s3.input();
	if (s1.a == s2.a) {
		swap(s1, s1);
		swap(s2, s2);
		swap(s1.a, s1.a);
		swap(s2.a, s2.a);
	} else if (s1.a == s2.b) {
		swap(s1, s1);
		swap(s2, s2);
		swap(s1.a, s1.a);
		swap(s2.b, s2.a);
	} else if (s1.b == s2.a) {
		swap(s1, s1);
		swap(s2, s2);
		swap(s1.b, s1.a);
		swap(s2.a, s2.a);
	} else if (s1.b == s2.b) {
		swap(s1, s1);
		swap(s2, s2);
		swap(s1.b, s1.a);
		swap(s2.b, s2.a);
	} else if (s1.a == s3.a) {
		swap(s1, s1);
		swap(s3, s2);
		swap(s1.a, s1.a);
		swap(s2.a, s2.a);
	} else if (s1.a == s3.b) {
		swap(s1, s1);
		swap(s3, s2);
		swap(s1.a, s1.a);
		swap(s2.b, s2.a);
	} else if (s1.b == s3.a) {
		swap(s1, s1);
		swap(s3, s2);
		swap(s1.b, s1.a);
		swap(s2.a, s2.a);
	} else if (s1.b == s3.b) {
		swap(s1, s1);
		swap(s3, s2);
		swap(s1.b, s1.a);
		swap(s2.b, s2.a);
	} else if (s2.a == s3.a) {
		swap(s2, s1);
		swap(s3, s2);
		swap(s1.a, s1.a);
		swap(s2.a, s2.a);
	} else if (s2.a == s3.b) {
		swap(s2, s1);
		swap(s3, s2);
		swap(s1.a, s1.a);
		swap(s2.b, s2.a);
	} else if (s2.b == s3.a) {
		swap(s2, s1);
		swap(s3, s2);
		swap(s1.b, s1.a);
		swap(s2.a, s2.a);
	} else if (s2.b == s3.b) {
		swap(s2, s1);
		swap(s3, s2);
		swap(s1.b, s1.a);
		swap(s2.b, s2.a);
	} else {
		printf("NO\n");
		return;
	}
	if (OnSegment(s1, s3.a)) {
		swap(s3.a, s3.a);
	} else if (OnSegment(s1, s3.b)) {
		swap(s3.b, s3.a);
	} else {
		printf("NO\n");
		return;
	}
	if (not OnSegment(s2, s3.b)) {
		printf("NO\n");
		return;
	}
	ll cosangle = (s1.b - s1.a) * (s2.b - s2.a);
	if (cosangle < 0) {
		printf("NO\n");
		return;
	}
	ll min5x, max5x;
	ll min5y, max5y;
	min5x = s1.a.x * 4 + s1.b.x;
	max5x = s1.a.x + s1.b.x * 4;
	min5y = s1.a.y * 4 + s1.b.y;
	max5y = s1.a.y + s1.b.y * 4;
	if (not (InRange(min5x, s3.a.x * 5, max5x) and InRange(min5y, s3.a.y * 5, max5y))) {
		printf("NO\n");
		return;
	}
	min5x = s2.a.x * 4 + s2.b.x;
	max5x = s2.a.x + s2.b.x * 4;
	min5y = s2.a.y * 4 + s2.b.y;
	max5y = s2.a.y + s2.b.y * 4;
	if (not (InRange(min5x, s3.b.x * 5, max5x) and InRange(min5y, s3.b.y * 5, max5y))) {
		printf("NO\n");
		return;
	}
	printf("YES\n");
}
int main() {
	int T;
	scanf("%d", &T);
	while (T -- != 0) {
		Solve();
	}
	return 0;
}
```

---

## 作者：Argon_Cube (赞：1)

* **【题目链接】**

[Link:CF13B](https://www.luogu.com.cn/problem/CF13B)

* **【解题思路】**

首先，这里是我解题方法的实现版本：

1. 首先，可以判断是否有两个以上的点相同。这是一个小优化，如果符合直接输出`No`。在此过程中，可以顺便确定线段 $1,2,3$ 的下标与交点，不用全排列枚举，减小常数。

2. 条件一中判定点是否在线上，我用斜率。

3. 条件二的判定在于勾股定理。只要判断线段 $3$ 与两线段的交点与线段 $1,2$ 的交点构成的三角形中，两段边之和是否不大于第三边即可。不符合输出`No`。

4. 条件三用两点之间距离公式即可。

第一点不用我说了，解决第二点。

这里校正一下$\color{orange}\mathsf{Limit}$的题解中用了斜率（其他人都用了叉积），给出的容错精度为 $10^{-3}$。

**这是远远不够的。**

比如说：

```
Input:
1
0 0 100000000 3
0 0 2 2
1 1 66666667 2
Output:
NO
```

要避免这种情况，容错精度得开到 $10^{-9}$ 才行。

这里我给出一种新的、针对本题的、不会丢失精度的用斜率实现的方法。

首先，题目里说：**所有坐标均为整数。**

其次，斜率必定是有理数，即可以表示成 $\frac{a}{b}$ 的形式。这里我们默认，$a,b$ 互质。

既然所有坐标均为整数，那么我们只要判该线段在该点横坐标上，纵坐标是否为整数即可。显然，该点横坐标与线段任意端点横坐标之差，应该可以约掉 $b$。即，设这个差为 $x$，$b|x$。判断余数是否为 $0$ 即可，剩下的都是整数运算，无需担心精度。

现在解决第四点（第三点上面概括了）。先说一句，```STL```大法好。

这里我们要用到```complex```，使用```norm```函数（**这是全局函数！**）求坐标距离原点的距离的平方。公式：

$$x^2+y^2$$

显然结果是整数（为什么用```norm```而不是```abs```呢？还是精度问题）。

既然距离平方了，那两线段长的最小比值也要平方吧？

于是最小比值现在变成了 $\frac{1}{16}(0.0625)$。

现在所有问题都解决了。

* **【实现代码】**

```cpp
#include <iostream>
#include <complex>
#include <array>

using namespace std;

template<typename type>
type gcd(type a,type b)
{
	return b?gcd(b,a%b):a;
}

bool check(pair<complex<long long>,complex<long long>> line,complex<long long> point)//上面提到的第二点
{
	if(point.real()<min(line.first.real(),line.second.real())||point.imag()<min(line.first.imag(),line.second.imag())||
		point.real()>max(line.first.real(),line.second.real())||point.imag()>max(line.first.imag(),line.second.imag()))
		return true;
	if(line.first.real()==line.second.real())
		return point.real()!=line.first.real();
	if(line.first.imag()==line.second.imag())
		return point.imag()!=line.first.imag();
	long long num=line.first.imag()-line.second.imag(),den=line.first.real()-line.second.real(),gcdnd=gcd(num,den);
	num/=gcdnd,den/=gcdnd;
	if((point.real()-line.first.real())%den)
		return true;
	return line.first.imag()+num*(point.real()-line.first.real())/den!=point.imag();
}

int main(int argc,char *argv[],char *envp[])
{
	array<pair<complex<long long>,complex<long long>>,3> lines;
	complex<long long> intersection,ufind(2147483647,2147483647);
	int cnt,line_1,line_2,line_3;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>cnt;
	int xpos1,xpos2,ypos1,ypos2;
	while(cnt--)
	{
		for(int i=0;i<3;i++)
			cin>>xpos1>>ypos1>>xpos2>>ypos2,lines[i].first={xpos1,ypos1},lines[i].second={xpos2,ypos2};
		intersection=ufind;
		//上面所提到的第一点
		for(int i=0;i<2;i++)
			for(int j=i+1;j<3;j++)
				if(lines[i].first==lines[j].first)
					if(lines[i].second==lines[j].second)
					{
						cout<<"NO";
						goto nextcase;
					}
					else
						if(intersection!=ufind)
						{
							cout<<"NO";
							goto nextcase;
						}
						else
							line_1=i,line_2=j,line_3=3-i-j,intersection=lines[i].first;
				else if(lines[i].first==lines[j].second)
					if(lines[i].second==lines[j].first)
					{
						cout<<"NO";
						goto nextcase;
					}
					else
						if(intersection!=ufind)
						{
							cout<<"NO";
							goto nextcase;
						}
						else
							line_1=i,line_2=j,line_3=3-i-j,intersection=lines[i].first;
				else if(lines[i].second==lines[j].second)
					if(lines[i].first==lines[j].first)
					{
						cout<<"NO";
						goto nextcase;
					}
					else
						if(intersection!=ufind)
						{
							cout<<"NO";
							goto nextcase;
						}
						else
							line_1=i,line_2=j,line_3=3-i-j,intersection=lines[i].second;
				else if(lines[i].second==lines[j].first)
					if(lines[i].first==lines[j].second)
					{
						cout<<"NO";
						goto nextcase;
					}
					else
						if(intersection!=ufind)
						{
							cout<<"NO";
							goto nextcase;
						}
						else
							line_1=i,line_2=j,line_3=3-i-j,intersection=lines[i].second;
		if(intersection==ufind)
		{
			cout<<"NO";
			goto nextcase;
		}
		//上面所提到的第二点
		if(check(lines[line_1],lines[line_3].first))
			swap(lines[line_3].first,lines[line_3].second);
		if(check(lines[line_1],lines[line_3].first)||check(lines[line_2],lines[line_3].second))
		{
			cout<<"NO";
			goto nextcase;
		}
		//上面所提到的第四点
		if(norm(lines[line_1].first-lines[line_3].first)/(long double)norm(lines[line_1].second-lines[line_3].first)>16||
			norm(lines[line_1].first-lines[line_3].first)/(long double)norm(lines[line_1].second-lines[line_3].first)<0.0625||
			norm(lines[line_2].first-lines[line_3].second)/(long double)norm(lines[line_2].second-lines[line_3].second)>16||
			norm(lines[line_2].first-lines[line_3].second)/(long double)norm(lines[line_2].second-lines[line_3].second)<0.0625)
		{
			cout<<"NO";
			goto nextcase;
		}
		//上面所提到的第三点
		if(norm(intersection-lines[line_3].first)+norm(intersection-lines[line_3].second)<norm(lines[line_3].first-lines[line_3].second))
		{
			cout<<"NO";
			goto nextcase;
		}
		cout<<"YES";
		nextcase:cout<<'\n';
	}
 	return 0;
}
```

---

## 作者：AsunderSquall (赞：1)

update：远古题解一大堆格式错误，试图一个个修复。  
~~hoho！恭喜你发现一道 CF\*2000 的水黑~~  
完全没有计算几何基础的人把这道题当模拟题来做的人前来报道。  
想法很 simple，勿喷。  

# 题意  
给你  $ 3 $  条线段，让你判断这三条线段是否能组成字母 `A`。  

# 题解  
这个判断比较麻烦，因为限制比较多，而且不限制顺序，不过没有关系，我们可以大力枚举。  
```cpp
struct seg
{
    int x[3],y[3];
    void get()
    {
        rd(x[1]);rd(y[1]);rd(x[2]);rd(y[2]);
    }
    void put()//调试用的
    {
        printf("%lld %lld %lld %lld\n",x[1],y[1],x[2],y[2]);
    }
}S[4];

bool chk(seg s1,seg s2,seg s3)
{
    //这个时候钦定
    //s1.1和s2.1为相同的点.
    //s3.1在s1上,s3.2在s2上
}

seg A(seg s1) {return s1;}
seg B(seg s1) {swap(s1.x[1],s1.x[2]);swap(s1.y[1],s1.y[2]);return s1;
}
bool check(seg s1,seg s2,seg s3)
{
    bool flag=0;
    flag|=chk(A(s1),A(s2),A(s3));
    flag|=chk(A(s1),A(s2),B(s3));
    flag|=chk(A(s1),B(s2),A(s3));
    flag|=chk(A(s1),B(s2),B(s3));
    flag|=chk(B(s1),A(s2),A(s3));
    flag|=chk(B(s1),A(s2),B(s3));
    flag|=chk(B(s1),B(s2),A(s3));
    flag|=chk(B(s1),B(s2),B(s3));
    return flag;
}
signed main()
{
    rd(T);
    while (T--)
    {
        bool flag=0;
        S[1].get();
        S[2].get();
        S[3].get();
        flag|=check(S[1],S[2],S[3]);
        flag|=check(S[1],S[3],S[2]);
        flag|=check(S[2],S[1],S[3]);
        flag|=check(S[2],S[3],S[1]);
        flag|=check(S[3],S[1],S[2]);
        flag|=check(S[3],S[2],S[1]);
        if (flag) puts("YES");
        else puts("NO");
    }
}

```  
（其实应该多枚举了一遍，不过懒得去掉了）  
这样我们就把顺序问题解决掉了，接下来就方便很多。  
考虑这个 `chk` 函数怎么写。  
我们把限制一个个列出来。

-----------
> 其中的两条线段有共同的端点。  

这个显然：
```cpp
if (s1.x[1]==s2.x[1] && s1.y[1]==s2.y[1])
{
//do something
}
else return 0;
``` 
----------
> 第三条线段的端点分别在这两条不同的线段上。  
> 第三条线段截得的另外两条线段的较小长度与较大长度的比值必须大于等于  $ \frac{1}{4} $ 。  

我们把这两条限制条件放在一起做，弄一个 `onseg` 函数，表示判断一个点和一条线段是否符合条件。  
考虑这样符合什么限制：  
- 这个点在线段所在直线上。  
- 这个点的横坐标在线段的两个端点之间。  
- 这个点的纵坐标在线段的两个端点之间。  
- 这个点与线段两端点的横坐标之差的绝对值大的不超过小的的  $ 4 $  倍。  
- 这个点与线段两端点的纵坐标之差的绝对值大的不超过小的的  $ 4 $  倍。  

解释一下，第二点和第三点有重复是因为可能会有与坐标轴平行的直线，两个都判一下可以不用特判，比较方便。第四点和第五点同理。  

考虑怎么用代码实现：`bool onseg(seg s1,int x,int y)`  
第 $ 2 $ 点和第 $ 3 $ 点：  
```cpp
if ((x-s1.x[1])*(x-s1.x[2])>0) return 0;
if ((y-s1.y[1])*(y-s1.y[2])>0) return 0;
```  
第 $ 1 $ 点：  
```cpp
if ((x-s1.x[1])*(y-s1.y[2])!=(x-s1.x[2])*(y-s1.y[1])) return 0;
```  
解释一下这段代码：  
我们只需要使得点与线段两端点之间的斜率一样即可，即  
 $ \dfrac{y-s.y_1}{x-s.x_1}=\dfrac{y-s.y_2}{x-s.y_2} $   
然后交叉相乘就是上面的式子。  
第 $ 4 $ 点和第 $ 5 $ 点：  
```cpp
int dx1=abs(x-s1.x[1]),dx2=abs(x-s1.x[2]);
int dy1=abs(y-s1.y[1]),dy2=abs(y-s1.y[2]);
if (max(dx1,dx2)<=min(dx1,dx2)*4 && max(dy1,dy2)<=min(dy1,dy2)*4) return 1;
```  
完整代码：
```cpp
bool onseg(seg s1,int x,int y)
{
    if ((x-s1.x[1])*(x-s1.x[2])>0) return 0;
    if ((y-s1.y[1])*(y-s1.y[2])>0) return 0;
    if ((x-s1.x[1])*(y-s1.y[2])!=(x-s1.x[2])*(y-s1.y[1])) return 0;
    int dx1=abs(x-s1.x[1]),dx2=abs(x-s1.x[2]);
    int dy1=abs(y-s1.y[1]),dy2=abs(y-s1.y[2]);
    if (max(dx1,dx2)<=min(dx1,dx2)*4 && max(dy1,dy2)<=min(dy1,dy2)*4) return 1;
    return 0;
}
```  
---------
> 2.第一条和第二条线段的夹角必须大于 $ 0 $ 度小于等于 $ 90 $ 度。  

这个好像很多人都用了计算几何，其实没有必要，只需要高中向量的知识就行了。  
我们知道  $ \vec{v_1}\cdot \vec{v_2}=||\vec{v_1}|\cdot|\vec{v_2}|\cos \theta| $   
然后  $ -\dfrac{\pi}{2}\leq\theta+2k\pi<0\ \ \  or\ \ \ 0<\theta+2k\pi \leq \dfrac{\pi}{2},k \in \mathbb{Z} \ \Leftrightarrow0\leq\cos \theta<1 $。   
那么我们只要求出  $ \cos \theta $。   
我们用坐标轴表示向量，这样点积就很好算了。  
`bool leq90(int X1,int Y1,int X2,int Y2)`  
设向量分别为  $ (x_1,y_1),(x_2,y_2) $。   
点积为  $ \cos \theta =\dfrac{x_1x_2+y_1y_2}{\sqrt{x_1^2+y_1^2}\cdot\sqrt{x_2^2+y_2^2}} $。   
考虑怎么简化代码。  
显然下面那个东西是正的，那么只要上面那个东西是负的就`return 0`。    
```cpp
int aaa=X1*X2+Y1*Y2;
int bbb=(X1*X1+Y1*Y1)*(X2*X2+Y2*Y2);
if (aaa<0) return 0;//钝角
```  
然后我们已经保证了  $ \cos \theta $  非负，就将上下同时平方。  
如果 `aaa=0` 说明是直角，`return 1`（其实应该不用特判，为了保险）。  
如果 `aaa*aaa=bbb` 说明是 0°，`return 0`。  
剩下的情况都是锐角，`return 1`。  
完整代码：
```cpp
bool leq90(int X1,int Y1,int X2,int Y2)
{
    int aaa=X1*X2+Y1*Y2;
    int bbb=(X1*X1+Y1*Y1)*(X2*X2+Y2*Y2);
    if (aaa<0) return 0;//钝角
    if (aaa==0) return 1;//直角
    if (aaa*aaa==bbb) return 0;//0°
    return 1;//锐角
}
```  

--------

最后把他们拼接在一起即可：  
```cpp

#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=3e5+5;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int T;
struct seg
{
    int x[3],y[3];
    void get()
    {
        rd(x[1]);rd(y[1]);rd(x[2]);rd(y[2]);
    }
    void put()
    {
        printf("%lld %lld %lld %lld\n",x[1],y[1],x[2],y[2]);
    }
}S[4];
bool onseg(seg s1,int x,int y)
{
    if ((x-s1.x[1])*(x-s1.x[2])>0) return 0;
    if ((y-s1.y[1])*(y-s1.y[2])>0) return 0;
    if ((x-s1.x[1])*(y-s1.y[2])!=(x-s1.x[2])*(y-s1.y[1])) return 0;
    int dx1=abs(x-s1.x[1]),dx2=abs(x-s1.x[2]);
    int dy1=abs(y-s1.y[1]),dy2=abs(y-s1.y[2]);
    if (max(dx1,dx2)<=min(dx1,dx2)*4 && max(dy1,dy2)<=min(dy1,dy2)*4) return 1;
    return 0;
}
bool leq90(int X1,int Y1,int X2,int Y2)
{
    int aaa=X1*X2+Y1*Y2;
    int bbb=(X1*X1+Y1*Y1)*(X2*X2+Y2*Y2);
    if (aaa<0) return 0;//钝角
    if (aaa==0) return 1;//直角
    if (aaa*aaa==bbb) return 0;//0°
    return 1;//锐角
}
bool chk(seg s1,seg s2,seg s3)
{
    //这个时候钦定
    //    s1.1和s2.1为相同的点.
    //    s3.1在s1上,s3.2在s2上
    if (s1.x[1]==s2.x[1] && s1.y[1]==s2.y[1])
    {
        if (onseg(s1,s3.x[1],s3.y[1])) 
        {
            if (onseg(s2,s3.x[2],s3.y[2]))
            {
                int XX=s1.x[2]-s1.x[1];
                int YY=s1.y[2]-s1.y[1];
                int XXX=s2.x[2]-s2.x[1];
                int YYY=s2.y[2]-s2.y[1];
                if (leq90(XX,YY,XXX,YYY)) return 1;
                else return 0;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}
seg A(seg s1) {return s1;}
seg B(seg s1) {swap(s1.x[1],s1.x[2]);swap(s1.y[1],s1.y[2]);return s1;
}
bool check(seg s1,seg s2,seg s3)
{
    bool flag=0;
    flag|=chk(A(s1),A(s2),A(s3));
    flag|=chk(A(s1),A(s2),B(s3));
    flag|=chk(A(s1),B(s2),A(s3));
    flag|=chk(A(s1),B(s2),B(s3));
    flag|=chk(B(s1),A(s2),A(s3));
    flag|=chk(B(s1),A(s2),B(s3));
    flag|=chk(B(s1),B(s2),A(s3));
    flag|=chk(B(s1),B(s2),B(s3));
    return flag;
}
signed main()
{
    rd(T);
    while (T--)
    {
        bool flag=0;
        S[1].get();
        S[2].get();
        S[3].get();
        flag|=check(S[1],S[2],S[3]);
        flag|=check(S[1],S[3],S[2]);
        flag|=check(S[2],S[1],S[3]);
        flag|=check(S[2],S[3],S[1]);
        flag|=check(S[3],S[1],S[2]);
        flag|=check(S[3],S[2],S[1]);
        if (flag) puts("YES");
        else puts("NO");
    }
}
```  


---

## 作者：_slb (赞：0)

似乎没有用向量的计算几何的题解，我来水一发（

## Description

给定三条线段，判断能否构成 A，即是否满足以下条件：

1. 有两条线段有公共点（下称“第一、二条线段”，另一条线段称“第三条线段”）；

2. 第三条线段的两个端点分别在第一、二条线段上；

3. 第一、二条线段夹角大于 $0$，小于 $\dfrac{\pi}{2}$；

4. 第三条线段分别将第一、二条线段截成两段，较短的线段与较长的线段的长度比不小于 $\dfrac14$。


## Solution

这是道计算几何的水题。~~想水黑题的快来~~

其实只需要暴力模拟即可，每组数据时间复杂度 $O(1)$，总时间复杂度 $O(T)$。

我用的纯计算几何的做法，用向量进行计算。因此把向量封装了，代码还算简单。

第一个要求直接暴力枚举，找有没有相同的点即可。

第二个要求也是计算几何基本操作：先用向量叉积是否为 $0$ 判断三点是否共线，再看点是否在以线段为对角线的矩形内部。

第三个要求本来想用叉积的几何意义配合反三角函数搞，但我不知道为啥一直挂，后来意识到是因为这个做法没法判断钝角。于是用余弦定理，就过了。

第四个要求很简单，就用向量做减法然后算一下验证就行。

感觉比起解析几何要省点脑子。

## Code

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using std::max;
using std::min;

const double pi = 3.141592653589793;
const double eps = 1e-10;

class Vector // 向量（也用来存点）
{
public:
    long long x, y;
    Vector() { x = y = 0; }
    Vector(long long a, long long b) { x = a, y = b; }
    bool operator==(const Vector &b) const { return x == b.x && y == b.y; }
    Vector operator+(const Vector &b) const { return Vector(x + b.x, y + b.y); }
    Vector operator-(const Vector &b) const { return Vector(x - b.x, y - b.y); }
    long long operator*(const Vector &b) const { return x * b.x + y * b.y; }
    long long operator&(const Vector &b) const { return x * b.y - b.x * y; } // 向量叉积
    Vector operator=(const Vector &b)
    {
        x = b.x, y = b.y;
        return *this;
    }
    long long dis_pow() { return (long long)x * x + y * y; }
    double dis() { return sqrt((double)x * x + y * y); }
} p[7];

bool in_seg(Vector a, Vector b, Vector x) // 判断点 x 是否在 线段ab 上
{
    if (((x - a) & (a - b)) != 0) // 叉乘为 0
        return false;
    return min(a.x, b.x) <= x.x && x.x <= max(a.x, b.x) && min(a.y, b.y) <= x.y && x.y <= max(a.y, b.y);
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        Vector s;
        for (int i = 1; i <= 6; i++)
            std::cin >> p[i].x >> p[i].y;
        
        int a = -1, b = -1, c = -1; // 第一、二条线段为 a、b，第三条线段为 c
        
        for (int i = 1; i <= 5; i++)
            for (int j = i + 1; j <= 6; j++)
                if (p[i] == p[j]) // 找到三条线段
                {
                    a = (i - 1) / 2 + 1;
                    b = (j - 1) / 2 + 1;
                    c = 6 - a - b;
                    s = p[i]; // s 为相同的端点
                    break;
                }
        if (a == -1) // 没有相同的点
        {
            puts("NO");
            continue;
        }
        
        Vector a1 = p[a * 2 - 1], a2 = p[a * 2], b1 = p[b * 2 - 1], b2 = p[b * 2], c1 = p[c * 2 - 1], c2 = p[c * 2]; // 6 个点分别用向量表示
        Vector _d1, _d2, _d3, _d4; // 第三条线段端点到到其所在线段两个端点的向量
        // 分两种情况：第三条线段一个端点在 a 上，另一个在 b 上，或者相反
        if (in_seg(a1, a2, c1) && in_seg(b1, b2, c2))
            _d1 = c1 - a1, _d2 = c1 - a2, _d3 = c2 - b1, _d4 = c2 - b2;
        else if (in_seg(a1, a2, c2) && in_seg(b1, b2, c1))
            _d1 = c2 - a1, _d2 = c2 - a2, _d3 = c1 - b1, _d4 = c1 - b2;
        else
        {
            puts("NO");
            continue;
        }
        
        Vector _a = a1 - s + a2 - s, _b = b1 - s + b2 - s; // 第一、二条线段的向量，这里的写法避免了分类讨论
        Vector a_b = _a - _b; // a、b线段组成三角形的另一条边
        if (_a.dis_pow() + _b.dis_pow() < a_b.dis_pow()) // 余弦定理判断夹角
        {
            puts("NO");
            continue;
        }
        
        double d1 = _d1.dis(), d2 = _d2.dis(), d3 = _d3.dis(), d4 = _d4.dis();
        if (d1 > d2)
            std::swap(d1, d2);
        if (d3 > d4)
            std::swap(d3, d4);
        // 这题似乎不卡精度，我就直接用 double 比较了，其实最好用距离的平方之比与 16 比较
        if (d2 / d1 - 4 <= eps && d4 / d3 - 4 <= eps)
            puts("YES");
        else
            puts("NO");
    }
}
```



---

## 作者：傅思维666 (赞：0)

## 题解：

~~本蒟蒻人生中的第一道黑题~~

一道复杂的模拟，其中掺杂了许些计算几何的风情。

其实涉及到的计算几何就是一点点的解析几何，判断三点共线，判断夹角小于90°，判断线段差分比例小于$\frac{1}{4}$。

求角小于90°的时候运用了叉积，需要平面向量的相关知识，不懂的同学请自行百度。

比较恶心的判断是差分比例小于$\frac{1}{4}$。让我来讲一下——

算了不讲了，看代码吧，模拟的思想还是比较简单的，相信大家能看明白。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node
{
    int x,y,j,k;
}a[10];
int t,x,y,m,n,p,q,x1,yy,x2,y2,c1,c2,flag;
int check_oneline(int a,int b,int c,int d,int e,int f)
{
    if((ll)(f-b)*(c-a)==(ll)(d-b)*(e-a))
        return 1;
    return 0;
}
int check_angle(int x,int y,int a,int b,int p,int q)
{
    if((ll)(a-x)*(p-x)+(ll)(b-y)*(q-y)<0)
        return 0;
    return 1;
}
int check_subseg(int x,int y,int m,int n,int a,int b)
{
    if(x!=a)
    {
        if(a>x)
        {
            if((a-x)*5<(m-x)) 
                return 0;
            if((a-x)*5>(m-x)*4) 
                return 0;
            return 1;
        }
        else
        {
            if((x-a)*5<(x-m)) 
                return 0;
            if((x-a)*5>(x-m)*4)
                return 0;
            return 1;
        }
    }
    else
    {
        if(b>y)
        {
            if((b-y)*5<(n-y))
                return 0;
            if((b-y)*5>(n-y)*4)
                return 0;
            return 1;
        }
        else
        {
            if((y-b)*5<(y-n))
                return 0;
            if((y-b)*5>(y-n)*4)
                return 0;
            return 1;
        }
    }
}
int main()
{
    scanf("%d",&t);
    while(t--) 
    {
        for(int i=1;i<=3;i++)
            scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].j,&a[i].k);
        for(int i=1;i<=2;i++) 
            for(int j=i+1;j<=3;j++)
            {
                if(a[i].x==a[j].x&&a[i].y==a[j].y)
                {
                    x=a[i].x,y=a[i].y;
                    m=a[i].j,n=a[i].k;
                    p=a[j].j,q=a[j].k;
                    c1=i,c2=j;
                }
                else if(a[i].x==a[j].j&&a[i].y==a[j].k)
                {
                    x=a[i].x,y=a[i].y;
                    m=a[i].j,n=a[i].k;
                    p=a[j].x,q=a[j].y;
                    c1=i,c2=j;
                }
                else if(a[i].j==a[j].j&&a[i].k==a[j].k)
                {
                    x=a[i].j,y=a[i].k;
                    m=a[i].x,n=a[i].y;
                    p=a[j].x,q=a[j].y;
                    c1=i,c2=j;
                }
                else if(a[i].j==a[j].x&&a[i].k==a[j].y)
                {
                    x=a[i].j,y=a[i].k;
                    m=a[i].x,n=a[i].y;
                    p=a[j].j,q=a[j].k;
                    c1=i,c2=j;
                }
            }
        for(int i=1;i<=3;i++)
            if(i!=c1&&i!=c2)
            {
                x1=a[i].x,yy=a[i].y,x2=a[i].j,y2=a[i].k;
                break;
            }
        flag=1; 
        if(check_angle(x,y,m,n,p,q)==0)
            flag=0;
        if(flag)
        {
            if(check_oneline(x,y,m,n,x1,yy)&&check_oneline(x,y,p,q,x2,y2))
            {
                if(check_subseg(x,y,m,n,x1,yy)==0)
                    flag=0;
                if(check_subseg(x,y,p,q,x2,y2)==0)
                    flag=0;
            }
            else if(check_oneline(x,y,p,q,x1,yy)&&check_oneline(x,y,m,n,x2,y2))
            {
                if(check_subseg(x,y,m,n,x2,y2)==0)
                    flag=0;
                if(check_subseg(x,y,p,q,x1,yy)==0)
                    flag=0;
            }
            else 
                flag=0;
        }
        printf(flag?"YES\n":"NO\n");
    }
    return 0;
}
```


---

