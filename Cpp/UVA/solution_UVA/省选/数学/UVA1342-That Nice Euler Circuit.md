# That Nice Euler Circuit

## 题目描述

给出一个平面上$n-1$个点的回路，第$n$个顶点与第$1$个顶点相同，求它把整个平面分成了几个部分（包括内部围起来的部分和外面的无限大的区域）。

## 说明/提示

数据组数$\leqslant 25$

$4\leqslant n\leqslant 300$

$-300\leqslant x_i,y_i\leqslant 300$

感谢@AThousandMoon 提供的翻译

# 题解

## 作者：wangbinfeng (赞：2)

[![](https://img.shields.io/badge/题目-UVA1342_That_Nice_Euler_Circuit-green)
![](https://img.shields.io/badge/难度-省选/NOI−-purple)
![](https://img.shields.io/badge/考点-二维几何-blue)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/UVA1342)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-yellow)](https://www.luogu.com.cn/user/387009) 

------------
作为没有爬样例的 UVA 题目，在题解最开始放一个样例是个好习惯。
```
.in:
5
0 0 0 1 1 1 1 0 0 0
7
1 1 1 5 2 1 2 5 5 1 3 5 1 1
0
.ans:
Case 1: There are 2 pieces.
Case 2: There are 5 pieces.
```

样例有点水，再附赠一个以便调试（感谢 uDebug）：
```
.in:
268
-209 -268 35 202 173 70 -192 -201 -96 51 39 -97 132 299 123 20 288 -79 282 98 -169 215 -116 -152 204 14 -163 16 16 49 -121 -218 -49 243 94 261 -176 -1 -154 -190 204 144 212 -265 -66 -150 -68 200 196 -236 249 -296 -297 185 76 -35 -179 119 -84 123 273 48 0 -89 -77 -267 -263 295 -181 179 214 178 -297 245 -68 164 -264 75 216 149 -168 -152 147 -28 259 257 -135 -131 -76 163 -27 -54 182 -177 -78 -222 -74 -268 -48 -223 181 -144 275 56 -219 -23 -129 43 -220 -103 -78 -110 -78 -127 -50 285 -129 -120 228 57 132 12 55 292 147 291 -101 125 252 112 -97 -296 -168 -142 251 146 210 296 -288 -226 217 -121 246 47 -160 162 -210 -44 -187 -122 -20 -25 22 -175 -101 -291 -164 168 -267 141 3 -120 -164 177 -51 -23 -100 -20 247 -2 -293 -239 159 206 -47 -135 -7 195 124 -113 -188 -21 93 -2 -56 -152 -91 258 -164 33 220 136 -84 -186 -51 177 250 84 139 194 46 -27 37 9 -42 -75 211 34 -220 196 -125 -40 125 -293 188 -163 -190 -209 218 121 248 -150 184 -125 21 -163 -256 141 134 -2 165 60 269 -289 163 269 171 84 209 -283 146 -142 35 259 -261 -84 -145 -109 -98 73 94 163 -248 252 -235 -35 -177 -177 -188 -276 -112 182 -291 14 140 -34 -198 -84 88 -24 -60 103 -280 250 226 140 -22 151 -218 -276 -63 61 197 -296 -21 18 -122 -272 222 128 -268 -198 50 -92 -69 -210 23 174 171 -56 74 -269 293 251 -80 -178 77 160 5 -146 -108 -29 203 -155 -211 64 -33 -147 99 37 267 -214 126 122 21 174 203 267 122 170 234 56 255 -5 94 143 -109 69 243 -133 -8 128 -96 -263 -134 -160 -268 127 -132 -289 132 15 136 -249 -83 100 -280 -46 10 -281 -193 155 -34 -208 -198 -114 -182 -287 -237 -109 261 299 -45 73 106 221 -128 -72 -32 -297 163 28 -67 -193 -54 266 -17 95 -169 78 299 226 50 -239 288 -173 253 182 127 117 -136 206 -1 -204 -283 -191 -117 277 216 7 233 -66 0 162 -280 -285 191 -8 213 -290 -181 -65 42 0 8 218 37 128 291 87 124 277 286 212 202 126 243 233 -234 -102 73 -15 144 218 -57 116 -94 -101 13 -260 138 -282 267 289 143 -167 -183 286 -205 -278 -94 -228 -29 -144 -156 155 137 166 -207 -248 116 58 -96 149 -179 -96 -76 212 56 39 -194 -14 232 141 141 103 -161 -12 214 190 38 -79 291 -190 229 275 41 25 -166 4 108 157 222 -129 20 -95 174 -153 -95 0 275 -279 56 -15 19 205 115 50 232 -180 -27 -206 -111 -91 -144 34 -65 286 1 -177 -135 -128 231 49 -209 -268
0
.ans:
Case 1: There are 8443 pieces.
```
首先本题需要知道欧拉定理，具体地，
> 欧拉定理：设平面图的顶点数、边数和面数分别为 $V,E,F$，则有 $V+F-E=2$。

知道了这个公式，本题也就没了难度。统计一下顶点数、边数即可。难点在于如果有三点共线则需要减掉，判断一下点在不在已有线段上就好了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
//此处是点类和向量类的模板，具体可见：https://www.luogu.com/article/p0k8bxnp
const int maxn=309;
Point<double>p[maxn],v[maxn*maxn];
int n;
signed main(){
	static int Case=1;
	if(scanf("%d",&n)!=1 || !n)return 0;
	printf("Case %d: ",Case++);
	for(int i=0;i<n;i++)scanf("%lf%lf",&p[i].x,&p[i].y),v[i]=p[i];
	n--;
	int c=n,e=n;
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(segmentProperIntersection(p[i],p[i+1],p[j],p[j+1]))
		v[c++]=getLineIntersection(p[i],p[i+1]-p[i],p[j],p[j+1]-p[j]);
	std::sort(v,v+c);
	c=std::unique(v,v+c)-v;
	for(int i=0;i<c;i++)for(int j=0;j<n;j++)if(v[i].onSegment(p[j],p[j+1]))e++;
	printf("There are %d pieces.\n",e+2-c);
	main(); 
}
```

---

## 作者：liumuxin (赞：0)

参考书上的思路和代码
### 前置知识：欧拉定理
设平面图的定点数，边数和面数分别为V,E和F，则V+F-E=2

### 思路
若是直接找出所有区域，会非常麻烦，而且非常容易出错，但是用欧拉定理可以转化这个问题，更加容易解决  
该平面图的节点由两部分组成，即原来的节点和新增的节点，由于三点共线会影响计算，所以需要删除重复的点

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Point{
	double x,y;
	Point(double X=0,double Y=0){
		x=X;
		y=Y;
	}
};
typedef Point Vector;
Vector operator +(Vector A,Vector B){
	return Vector(A.x+B.x,A.y+B.y);
}
Vector operator -(Point A,Point B){
	return Vector(A.x-B.x,A.y-B.y);
}
Vector operator *(Vector A,double p){
	return Vector(A.x*p,A.y*p);
}
Vector operator /(Vector A,double p){
	return Vector(A.x/p,A.y/p);
}
bool operator <(const Point& a,const Point& b){
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
const double eps=1e-10;
int dcmp(double x){
	if(fabs(x)<eps)return 0;
	else return x<0?-1:1;
} 
bool operator ==(const Point& a,const Point& b){
	return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
}
double Dot(Vector A,Vector B){
	return A.x*B.x+A.y*B.y;
}
double Length(Vector A){
	return sqrt(Dot(A,A));
}
double Angle(Vector A,Vector B){
	return acos(Dot(A,B)/Length(A)/Length(B));
}
double Cross(Vector A,Vector B){
	return A.x*B.y-A.y*B.x;
}
Vector Rotate(Vector A,double rad){
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w){
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
	double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);
	double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
	return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}
bool OnSegment(Point p,Point a1,Point a2){
	return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<0;
}
Point P[1000],V[100000];
int main(){
	int n,cnt=0;
	while(scanf("%d",&n)==1&&n){
		for(int i=0;i<n;i++){
			cin>>P[i].x>>P[i].y;
			V[i]=P[i];
		}
		n--;
		int c=n,e=n;
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				if(SegmentProperIntersection(P[i],P[i+1],P[j],P[j+1]))
				V[c++]=GetLineIntersection(P[i],P[i+1]-P[i],P[j],P[j+1]-P[j]);
			}
		}
		sort(V,V+c);
		c=unique(V,V+c)-V;
		for(int i=0;i<c;i++){
			for(int j=0;j<n;j++){
				if(OnSegment(V[i],P[j],P[j+1]))e++; 
			}
		}
		printf("Case %d: There are %d pieces.\n",++cnt,e+2-c); 
	}
	return 0;
}
```


---

