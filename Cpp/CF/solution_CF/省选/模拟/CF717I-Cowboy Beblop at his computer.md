# Cowboy Beblop at his computer

## 题目描述

给定三维空间内的两个**平面多边形**，即每一个给出的多边形上的所有点共面，两个多边形不一定是凸多边形，它们所在的面不一定与 $x,y,z$ 轴垂直。

你需要确定：将其中一个多边形的边按照逆时针顺序定向，其自上而下穿过另一个多边形的次数与自下而上穿过另一个多边形的次数是否相等。

## 说明/提示

$3 \leq n , m \leq 100000$，$0 \leq |x| , |y| , |z| \leq 10^6$

## 样例 #1

### 输入

```
4
0 0 0
2 0 0
2 2 0
0 2 0
4
1 1 -1
1 1 1
1 3 1
1 3 -1
```

### 输出

```
YES
```

# 题解

## 作者：EMT__Mashiro (赞：3)

设$poly_i(i\in\{0,1\})$有$n_i$个顶点，按顺序为$a_{i,0},\cdots,a_{i,n_i}(a_{i,n_i}=a_{i,0})$，法向量为$\overrightarrow{p_i}$，所在平面为$flat_i$。

#### step.1

计算出$\overrightarrow x=\overrightarrow{p_0}\times\overrightarrow{p_1}$，这是$l=flat_0\cap flat_1$的方向。   
如果$|\overrightarrow x|=0$那么$flat_0\parallel flat_1$。

#### step.2

考虑计算$poly_0$的边与$flat_1$的交点及方向。   
可以用$o_{0,i}=\operatorname{sgn}(\cos<\overrightarrow{a_{0,i}-a_{1,0}},\overrightarrow{p_1}>)=\operatorname{sgn}(\overrightarrow{a_{0,i}-a_{1,0}}\cdot\overrightarrow{p_1})$表示$a_{0,j}$与$flat_1$的位置关系。  
$o_{0,i}=\begin{cases}1&\text{above}\\0&\text{on}\\-1&\text{below}\end{cases}$  
那么$e_{0,i}=o_{0,i}-o_{0,i+1}$就可以表示$\operatorname{seg}(a_{0,i},a_{0,i+1})$与$flat_1$的位置关系。  
$|e_{0,i}|=\begin{cases}2&\text{intersect}\\1&\text{tangent}\\0&\text{apart}\end{cases}$  
$\operatorname{sgn}(e_{0,i})=\begin{cases}1&\text{down}\\0&\text{apart}\\-1&\text{up}\end{cases}$  
对于$e_{0,i}\ne0$，计算得到$\operatorname{seg}(a_{0,i},a_{0,i+1})\cap flat_1=y_{0,i}=a_{0,i}+\frac{\overrightarrow{a_{0,i}-a_{1,0}\cdot}\overrightarrow{p_1}}{\overrightarrow{a_{0,i}-a_{1,0}}\cdot\overrightarrow{p_1}}\overrightarrow{a_{0,i+1}-a_{0,i}}$。

同理求出所有$e_{1,i},y_{1,i}(e_{1,i}\ne0)$。

#### step.3

很显然所有$y_{t,i}$都在$l$上，且因为相切的交点计算了两次，所以两个多边形与$l$的交点个数都是偶数。     
计算出$y_{t,i}$按在$\overrightarrow x$方向上的坐标$pos_{t,i}=\overrightarrow{y_{t,i}}\times\overrightarrow x$。   
那么$[y_{0,i}\in poly_1]=|\sum\limits_{pos_{1,j}<pos_{0,i}}e_{1,j}|$。

这样我们就成功地判断了$y_{0,i}$与$poly_1$的位置关系，结合$e_{0,i}$即可算出$poly_0$从上往下和从下往上穿过$poly_1$的次数。

#### app.
如何得到$y_{t,i}$的计算式？  
设$y_{0,i}=a_{0,i}+k_i\overrightarrow{a_{0,i+1}-a_{0,i}}$，则$\overrightarrow{y_{0,i}-a_{1,0}}=\overrightarrow{a_{0,i}-a_{1,0}}+k_i\overrightarrow{a_{0,i+1}-a_{0,i}}$。  
两边同时对$\overrightarrow{p_1}$点积得到$k_i=\frac{\overrightarrow{a_{0,i}-a_{1,0}\cdot}\overrightarrow{p_1}}{\overrightarrow{a_{0,i}-a_{1,0}}\cdot\overrightarrow{p_1}}$。  
$y_{1,i}$同理。

```c++
#include<cstdio>
#include<vector>
#include<utility>
#include<algorithm>
using std::pair;
using db=long double;
using i64=long long;
const int N=100007;
struct vec{i64 x,y,z;}a[2][N],p[2],x;
vec operator-(const vec&a,const vec&b){return {a.x-b.x,a.y-b.y,a.z-b.z};}
vec operator*(const vec&a,const vec&b){return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};}
i64 operator^(const vec&a,const vec&b){return a.x*b.x+a.y*b.y+a.z*b.z;}
int n[2],o[N],s,t;
std::vector<pair<db,pair<int,int>>>vec;
int read(){int x;scanf("%d",&x);return x;}
int sgn(i64 x){return x<0? -1:x? 1:0;}
int main()
{
    freopen("1.in","r",stdin);
    for(int t=0;t<2;++t)
    {
	n[t]=read();
	for(int i=0;i<n[t];++i) a[t][i]={read(),read(),read()};
	a[t][n[t]]=a[t][0],p[t]=(a[t][1]-a[t][0])*(a[t][2]-a[t][0]);
    }
    if(x=p[0]*p[1],!(x^x)) return !puts("NO");
    for(int t=0;t<2;++t)
    {
	for(int i=0;i<=n[t];++i) o[i]=sgn((a[t][i]-a[t^1][0])^p[t^1]);
	for(int i=0;i<n[t];++i)
	    if(o[i]^o[i+1])
		vec.push_back({(a[t][i]^x)+((a[t][i+1]-a[t][i])^x)*(db)(p[t^1]^(a[t][i]-a[t^1][0]))/(p[t^1]^(a[t][i]-a[t][i+1])),{t,o[i]-o[i+1]}});
    }
    std::sort(vec.begin(),vec.end());
    for(auto x:vec) x.second.first? s+=t*x.second.second:t+=x.second.second;
    puts(s? "YES":"NO");
}
```

---

