# Contact

## 题目描述

小 Petya 正在准备他和外星人的第一次沟通。他知道，外星人的宇宙飞船上都有一面是非退化（不共线三点构成的）三角形，并且这次只会来 4 艘。为飞船设计的着陆平台可以由在一个二维坐标系上，由 3 个特殊的塔，构成一个可以在旋转、平移和反射（沿边缘的对称性）上都可以和飞船上的三角形相吻合的三角形着陆平台。着陆后，飞船可以重叠。

每一个塔都可以用来着陆不止一艘飞船，举个例子：如果有两艘一模一样的飞船，咱们不用造 6 个塔，3 个就够了。Petya 想知道最少造几个塔就可以让他们的四艘飞船全部着陆。

## 说明/提示

在第一组样例中，塔可以放在 (0,0),(1,0),(3,0),(1,2)。第二艘船可以降落在后面的三个塔上。

在第二组样例中，可以选择 (0,0),(0,1),(1,0),(0,2),(2,0),(0,5),(5,0),(0,17),(17,0) 这几个点。用 9 个以下的塔是不可能的。

## 样例 #1

### 输入

```
0 0 1 0 1 2
0 0 0 2 2 2
0 0 3 0 1 2
0 0 3 0 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
0 0 0 1 1 1
0 0 0 2 2 2
0 0 0 5 5 5
0 0 0 17 17 17
```

### 输出

```
9
```

# 题解

## 作者：feecle6418 (赞：1)

问题其实就是怎么枚举才不会漏解。

显然答案至多是 $9$。如果直接枚举每个三角形是哪些点，再排除不可能的情况，可能是可做的；但最终需要解决“给定平面上一些点之间的距离 问存不存在解”，这个问题好像本身不可做。

接着来复读官方题解了。首先去掉全等的三角形。

考虑三角形作为点，有几个公共点 作为两点间边的条数，构成的图。枚举这个图长什么样子（其实不全是）。

图上一条重边意味着共边的三角形。一个三元环 / 四元环意味着图长成中间一个三角形 / 四边形，外面挂了一些三角形。

特判整个图就是个四元环的情况。以下假设要么没有环要么有三元环。

首先加一个三角形。加入下一个三角形有几种方式。

- 随便乱加（只有，也只要一个公共点）。
- 与目前的点相互连接形成的线段可以构成公共边。对于每条公共边至多有 $4$ 种情况，分别枚举。（可以完美嵌入的情况也包含在内）
- 加一个三元环。字面意思，枚举是哪三个三角形、分别用哪条边。

容易发现，上面已经讨论到了所有情况。其实强制先加三元环（应该是只用加一个三元环）再加公共边应该也没问题。

最终的实现方式：只允许加环（且环有顺序性，3->2），不允许随便乱加，但是对 $15$ 个子集都求出只允许加环的答案。最后状压 dp 合并。

下面这份代码实现复杂度有点问题（枚举了中间的三元环作为 核 之后，应该强制这三条边分别属于三个三角形，这样复杂度才正确，否则会随便配，导致算到很多不合法的不优秀情况），但是莫名其妙过了，懒得改了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const db eps=1e-8;
struct point{db x,y;void in(){cin>>x>>y;}}a[12];
db Dot(point x,point y){return x.x*y.x+x.y*y.y;}
db Cross(point x,point y){return x.x*y.y-x.y*y.x;}
db Dis(point x,point y){return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));}
point operator +(point x,point y){return {x.x+y.x,x.y+y.y};}
point operator -(point x,point y){return {x.x-y.x,x.y-y.y};}
point operator *(db x,point y){return {x*y.x,x*y.y};}
point operator *(point y,db x){return {x*y.x,x*y.y};}
//逆时针旋转 
point Rotate(point x,db y){return {x.x*cos(y)-x.y*sin(y),x.y*cos(y)+x.x*sin(y)};}
struct triangle{db l[3];db &operator [](const int k){return l[k];}}t[4];
int f[20],ff[20],m;
vector<point> Findp(point x,point y,db r1,db r2){
	db dis=Dis(x,y),len[5]={dis,r1,r2};
	vector<point> ret;
	if(fabs(dis-r1-r2)<eps){
		ret.push_back(x+(y-x)*(r1/dis));
		ret.push_back(x+(y-x)*(r2/dis));
		return ret;
	}
	if(r1<r2)swap(r1,r2);
	if(fabs(r1-dis-r2)<eps){
		ret.push_back(x+(x-y)*(r2/dis));
		ret.push_back(y+(y-x)*(r2/dis));
		return ret;
	}
	db ang=acos((dis*dis+r1*r1-r2*r2)/(2*dis*r1));
	point t=Rotate(y-x,ang);
	ret.push_back(x+t*(r1/dis));
	t=Rotate(y-x,-ang);
	ret.push_back(x+t*(r1/dis));
	if(fabs(r1-r2)>eps){
		t=Rotate(x-y,ang);
		ret.push_back(y+t*(r1/dis));
		t=Rotate(x-y,-ang);
		ret.push_back(y+t*(r1/dis));
	}
	return ret;
}
void Add(point o){
	for(int i=1;i<=m;i++)if(fabs(o.x-a[i].x)<eps&&fabs(o.y-a[i].y)<eps)return ;
	a[++m]=o;
}
void dfs(int cur,int to){
	if(m>=ff[to])return ;
	if(cur==to)return ff[to]=min(ff[to],m),void();
	for(int i=0;i<4;i++){
		if((cur&(1<<i))||!(to&(1<<i)))continue;
		for(int j=0;j<3;j++){
			for(int k=1;k<=m;k++){
				for(int l=k+1;l<=m;l++){
					if(fabs(Dis(a[k],a[l])-t[i][j])>eps)continue;
					int tm=m,p,q;
					if(j==0)p=1,q=2;
					else if(j==1)p=0,q=2;
					else p=0,q=1;
					auto vec=Findp(a[k],a[l],t[i][p],t[i][q]);
					for(auto o:vec)Add(o),dfs(cur|(1<<i),to),m=tm;
				}
			}
		}
	}
}
void Solve(int S){
	for(int i=0;i<4;i++){
		if(!(S&(1<<i)))continue;
		for(int j=i+1;j<4;j++){
			if(!(S&(1<<j)))continue;
			for(int k=j+1;k<4;k++){
				if(!(S&(1<<k)))continue;
				for(int p=0;p<3;p++){
					for(int q=0;q<3;q++){
						for(int r=0;r<3;r++){
							db len[5]={t[i][p],t[j][q],t[k][r]};
							sort(len,len+3);
							if(len[0]+len[1]+eps<len[2])continue;
							m=0,a[++m]={0,0},a[++m]={0,len[0]};
							auto vec=Findp(a[1],a[2],len[1],len[2]);
							a[++m]=vec[0],dfs(0,S);
						}
					}
				}
			}
		}
		m=0,a[++m]={0,0},a[++m]={0,t[i][0]};
		auto vec=Findp(a[1],a[2],t[i][1],t[i][2]);
		a[++m]=vec[0],dfs(1<<i,S);
	}
}
int main(){
	memset(f,0x3f,sizeof(f)),memset(ff,0x3f,sizeof(ff)),f[0]=0;
	for(int i=0;i<4;i++){
		point x,y,z;
		x.in(),y.in(),z.in();
		t[i][0]=Dis(x,y),t[i][1]=Dis(x,z),t[i][2]=Dis(y,z);
	}
	for(int i=1;i<16;i++)Solve(i);
	for(int i=1;i<16;i++)for(int j=i;j;j=(j-1)&i)f[i]=min(f[i],f[i-j]+ff[j]-(bool)(i-j));
	int u=9;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				for(int l=0;l<3;l++){
					db len[5]={t[0][i],t[1][j],t[2][k],t[3][l]};
					sort(len,len+4);
					if(len[0]+len[1]+len[2]+eps>len[3])u=8;
				}
			}
		}
	}
	cout<<min(f[15],u);
}
```



---

