# [USACO16DEC] Lots of Triangles P

## 题目描述

Farmer John 正在考虑出售他的一部分土地以赚取一些额外收入。他的财产包含 $N$ 棵树（$3 \leq N \leq 300$），每棵树由二维平面中的一个点描述，且任意三棵树不共线。FJ 正在考虑出售由三棵树作为顶点定义的三角形地块；显然，他可以考虑的此类地块数量为 $L = \binom{N}{3}$，基于他财产中所有可能的三棵树组合。

一个三角形地块的价值为 $v$，如果它的内部恰好包含 $v$ 棵树（顶点上的树不计入，且由于没有三棵树共线，边界上也没有树）。对于每个 $v = 0 \ldots N-3$，请帮助 FJ 确定他的 $L$ 个潜在地块中有多少个地块的价值为 $v$。

## 样例 #1

### 输入

```
7
3 6
17 15
13 15
6 12
9 1
2 7
10 19```

### 输出

```
28
6
1
0
0```

# 题解

## 作者：ouuan (赞：15)

本题要用到容斥原理+简单的计算几何

最重要的一步在于如下图的容斥：
![](http://r.photo.store.qq.com/psb?/V11ZEfn30LVDI9/iYk4HaO36Uvi6SZ.cwah*v*u5JJkqeOsvouMgfoCL3w!/r/dC4BAAAAAAAA)

其中，L,S,R分别代表三角形三条边的正下方的树的数量

可以看出，三角形中树的数量就是|L+R-S|

因此只要预处理出每条边正下方点的数量，再枚举每个三角形就可以算出答案了

以下是各种细节，对于这道题来说，看懂上面的容斥之后建议自行完成所有细节，遇到问题再来看这篇题解：

1.一个点在一条线段的正下方⇔横坐标在线段两端点之间&&该点在该线段所在直线的下方，而点在直线下方可以用两点式+点斜式判断。

以点C和线段AB为例：

直线AB解析式为y=(yA-yB)/(xA-xB)*(x-xA)+yA

过C作AB平行线y=(yA-yB)/(xA-xB)*(x-xC)+yC

比较C与AB的位置关系即比较yA-xA*(yA-yB)/(xA-xB)和yC-xC*(yA-yB)/(xA-xB)的大小关系

2.每条线段的正下方应该不包括端点（否则边界会重合），并单独计算有点在公共端点下方的情况（否则边界会遗漏），然而若三角形有一边和y轴平行则不应计算有点在公共端点下方的情况，否则会将三角形的一个顶点算入答案中

3.如右图所示，如果中间的点在另两个点所组成的线段的下方，中间的点会被算入，因此在预处理每条边正下方点的数量的同时也要预处理每个点和每条线段的位置关系（当然最后计算的时候再算一遍也行，毕竟是O(1)的也不用重复计算），如果中间的点在另两个点所组成的线段的下方要将答案加1

最后代码如下：
```
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int n,x[310],y[310],f[310][310],ans[310]; //f用来存每条边正下方点的数量，ans存答案
bool down[310][310][310]; //存每条边和每个点的位置关系

int main()
{
    int i,j,k;
    long double kkk;
    
    cin>>n;
    
    for (i=1;i<=n;++i)
    {
        cin>>x[i]>>y[i];
    }
    
    for (i=1;i<n;++i) //预处理每条边正下方点的数量
    {
        for (j=i+1;j<=n;++j)
        {
            if (x[i]==x[j]) //记录有点在公共端点下方的情况，并且如果出现这种情况就不用判断这条线段和其它点的位置关系了
            {
                if (y[i]<y[j])
                {
                    ++f[0][j];
                }
                else
                {
                    ++f[0][i];
                }
            }
            else
            {
                for (k=1;k<=n;++k)
                {
                    if (i!=k&&j!=k&&x[k]>min(x[i],x[j])&&x[k]<max(x[i],x[j])) //判断点和线段的位置关系
                    {
                        kkk=1.0*(y[i]-y[j])/(x[i]-x[j]);
                        if (y[i]-kkk*x[i]>y[k]-kkk*x[k])
                        {
                            ++f[i][j];
                            down[i][j][k]=true;
                        }
                    }
                }
            }
        }
    }
    
    for (i=1;i<=n-2;++i)
    {
        for (j=i+1;j<n;++j)
        {
            for (k=j+1;k<=n;++k)
            {
                if (x[i]<=x[j]&&x[i]>=x[k]||x[i]>=x[j]&&x[i]<=x[k]) //找出横坐标在中间的点是哪个
                {
                    if (x[i]==x[j]||x[i]==x[k]) //判断是否有边和y轴平行
                    {
                        ++ans[abs(f[i][j]+f[i][k]-f[j][k]+down[j][k][i])];
                    }
                    else
                    {
                        ++ans[abs(f[i][j]+f[i][k]+f[0][i]-f[j][k]+down[j][k][i])];
                    }
                }
                else if (x[j]<=x[i]&&x[j]>=x[k]||x[j]>=x[i]&&x[j]<=x[k])
                {
                    if (x[i]==x[j]||x[j]==x[k])
                    {
                        ++ans[abs(f[i][j]+f[j][k]-f[i][k]+down[i][k][j])];
                    }
                    else
                    {
                        ++ans[abs(f[i][j]+f[j][k]+f[0][j]-f[i][k]+down[i][k][j])];
                    }
                }
                else
                {
                    if (x[i]==x[k]||x[j]==x[k])
                    {
                        ++ans[abs(f[i][k]+f[j][k]-f[i][j]+down[i][j][k])];
                    }
                    else
                    {
                        ++ans[abs(f[i][k]+f[j][k]+f[0][k]-f[i][j]+down[i][j][k])];
                    }
                }
            }
        }
    }
    
    for (i=0;i<n-2;++i)
    {
        cout<<ans[i]<<endl;
    } 
    
    return 0;
}
```

---

## 作者：yqw2486 (赞：7)

最开始想着暴力搞一下，
1. 先按照x升序排列各个点
2. 枚举三角形的三个点A(x1,y1),B(x2,y2),C(x3,y3)且x1≤x2≤x3
3. 枚举AC之间的所有点，判断该点是否在△ABC内

不难看出时间复杂度O(n^4)，不出意外可能会TLE，说不定数据小可以过5-6组数据呢？抱着侥幸心理提交后……~~现实总是这么残酷~~

翻了翻题解，只有[ouuan](https://www.luogu.com.cn/user/49742)大佬写了一篇：容斥原理+简单计算几何，好吧原来如此简单，是我太弱鸡了

![图片](https://cdn.luogu.com.cn/upload/image_hosting/7lrgvlc1.png)

先将ABC在x轴的投影搞出来，
大佬的思想也可以用来求面积：S△ABC =abs( S四边形ABED + S四边形BCFE - S四边形ACFD )

本题和求面积基本一样的，找出AB,BC,AC正下方有多少颗树，然后根据上面的公式计算一下即可，

易错点：图中的(1)和（2）中会把B点算入三角形中去，题目明确说明不包含顶点。所以这种情况需要把B点去掉。

实现：
1. 按照x升序排列各点
2. 预处理任意两点正下方有多少棵树down[a][b]
3. 枚举三角形三点A(x1,y1),B(x2,y2),C(x3,y3)且x1≤x2≤x3
4. 根据公式计算abs(down[A][B]+down[B][C]-down[A][C]),当然这里需要判断中间点B在AC上方还是下方，如果下方则还需要 -1

判断点线关系，假设A(x1,y1),B(x2,y2),C(x3,y3)，判断C与线段AB的关系，根据AB两点求出k以及表达式f(x)，最后比较y3与f(x3)大小即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
struct node{
	int x,y;
	bool operator<(node a)const{
		if(x==a.x)return y<a.y;
		return x<a.x;
	}
}pos[N];
int sub(int a,int b,int c){//判断c在直线AB的正下方 
	if(pos[c].x<pos[a].x||pos[c].x>pos[b].x)return 0;
	double dx=pos[b].x-pos[a].x,dy=pos[b].y-pos[a].y;
	double y=dy*(pos[c].x-pos[a].x)/dx +pos[a].y;
	return y>pos[c].y; 
}
int n,down[N][N],ans[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&pos[i].x,&pos[i].y);
	sort(pos+1,pos+1+n);//按照x排序 
	for(int a=1;a<n;a++)
		for(int b=a+1;b<=n;b++)//计算ab正下方有多少个点 
			for(int c=a+1;c<b;c++) 
				down[a][b]+=sub(a,b,c);
	for(int a=1;a<n-1;a++)//a是三角形最靠左的顶点 
		for(int b=a+1;b<n;b++)//b是三角形的中间点 
			for(int c=b+1;c<=n;c++)//c是三角形最靠右的顶点 
				ans[abs(down[a][b]+down[b][c]-down[a][c]+sub(a,c,b))]++;
	for(int i=0;i<n-2;i++)
		printf("%d\n",ans[i]);
	return 0;
} 
```








---

## 作者：Starrykiller (赞：3)

如果你往面积去想很可能就倒闭了。

$\gdef \vec {\overrightarrow}$

显然，点 $O$ 在 $\triangle ABC$ 内部的充要条件是：$O$ 在 $\vec {AB},\vec {BC},\vec {CA}$ 右侧。显然可以直接做到 $\Theta(n^4)$，但是过不去。

考虑求出 $f_{\vec{AB}}$ 表示在向量 $\overrightarrow{AB}$ 右侧的点集（不含 $A,B$）。那么三角形 $\triangle ABC$ 内部的点的数量就是三个点集之交。

使用 $\texttt{std::bitset}$ 维护，时间复杂度 $\Theta(n^4/w)$。

---

## 作者：Cx114514 (赞：1)

### 题目链接：[[USACO16DEC] Lots of Triangles P](https://www.luogu.com.cn/problem/P1715)

萌萌计算几何题。

![](https://cdn.luogu.com.cn/upload/image_hosting/byn3yts5.png)

如图，我们过三角形的三个顶点分别作垂直于 $x$ 轴的直线，我们可以发现，三角形 $=$ 大直角梯形 $-$ 两个小直角梯形。而两点确定一个这样的梯形。我们枚举梯形是 $O\left(n^2\right)$ 的。

判断一个点是否在梯形内部，只要判断一个点横坐标是否在该梯形两个底边之间，并且是否在斜线下方。

因此我们可以 $O\left(n^3\right)$ 求出一个梯形包含的点数。

然后我们就可以 $O\left(1\right)$ 求出每个三角形包含的点数。

总时间复杂度 $O\left(n^3\right)$。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read()
{
	int f = 1;
	char c = getchar();
	while (!isdigit(c))
	{
	    if (c == '-') f = -1;
	    c = getchar();
    }
	int x = 0;
	while (isdigit(c))
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int buf[15];

void write(int x)
{
	int p = 0;
	if (x < 0)
	{
	    putchar('-');
	    x = -x;
	}
	if (x == 0) putchar('0');
	else
	{
		while (x)
		{
			buf[++p] = x % 10;
			x /= 10;
		}
		for (int i = p; i >= 1; i--)
			putchar('0' + buf[i]);
	}
}

const double eps = 1e-18;

int n, x[305], y[305], ans[305], cnt[305][305];

bool down(int x1, int y1, int x2, int y2, int x3, int y3)
{
	double k, b;
	k = (y2 - y1) * 1.0 / (x2 - x1);
	b = y1 * 1.0 - x1 * 1.0 * k;
	if (x3 * k + b - y3 > eps) return 1;
	return 0;
}

signed main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		x[i] = read(), y[i] = read();
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			int x1 = x[i], y1 = y[i], x2 = x[j], y2 = y[j];
			if (x1 > x2)
			{
				swap(x1, x2);
				swap(y1, y2);
			}
			for (int k = 1; k <= n; k++)
			{
				if (k == i || k == j) continue;
				if (x[k] > x1 && x[k] <= x2) 
				{
					cnt[i][j] += down(x1, y1, x2, y2, x[k], y[k]); 
					cnt[j][i] += down(x1, y1, x2, y2, x[k], y[k]);
				}
			}
		}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
		{
			int x1 = x[i], y1 = y[i], x2 = x[j], y2 = y[j];
			if (x1 > x2)
			{
				swap(x1, x2);
				swap(y1, y2);
			}
			for (int k = 1; k <= n; k++)
			{
				if (k == i || k == j) continue;
				if (x[k] > x1 && x[k] <= x2 && down(x1, y1, x2, y2, x[k], y[k]))
				{
					int tot = cnt[i][j] - cnt[i][k] - cnt[j][k] - 1;
					ans[tot]++;
				}
				if (x[k] >= x1 && x[k] < x2 && !down(x1, y1, x2, y2, x[k], y[k]))
				{
					int tot = cnt[i][k] + cnt[j][k] - cnt[i][j];
					ans[tot]++;
				}
			}
		}
	for (int i = 0; i <= n - 3; i++)
	{
		write(ans[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：1)

## Description

[**Link**](https://www.luogu.com.cn/problem/P1715)

## Solution

不难想到枚举四个点的 $O(n^4)$ 做法。

如果你学过用容斥求平面直角坐标系中任意三角形的面积，你也许学过以下方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/8nlygp3v.png)

同理，我们也可以用这种方法求出任意三角形包括的点数。

令 $b_{A,B}$ 为点 $(A_x,A_y),(A_x,0),(B_x,B_y),(B_x,0)$ 四个点形成的直角梯形中有的点数，可以先枚举两个点，再枚举异于这两个点的点，检查它是否在这两个点与其映射点形成的直角梯形内。

关于检查一个点是否在直角梯形内，可以先检查点是否在左右两边之间，然后看它是否在 $a,b$ 两点形成的一次函数下即可。

具体代码：

```cpp
// 两点求一次函数 y = kx + b，返回 k 和 b
pair<double, double> Get(P a, P b) {
    double k = (1.0 * (a.y - b.y) / (a.x - b.x));
    return {k, (1.0 * a.y - k * a.x)};
}

// 点 p 是否在 y = kx + b 下方
bool isBelow(double k, double b, P p) {
    return p.y < (k * p.x + b);
}

// c 点是否在由 a，b 两点形成的直角梯形内
bool isInArea(P a, P b, P c) { 
    auto [k, b0] = Get(a, b);
    return a.x <= c.x && c.x <= b.x && isBelow(k, b0, c);
}
```

然后考虑怎么统计点数。

枚举三个点组成三角形，令 $A,B,C$ 为三角形的三个点，按 $x$ 升序排序，通过上图讨论，三角形内的点数显然是 $|b_{A,B} + b_{B, C} - b_{A, C}|$。

但如果 $B$ 在 $AC$ 上方，根据计算公式，顶点 $B$ 会被多计算一次，由于题目要求不能包含顶点，点数需要减 $1$。

最后对于每个三角形，算完点数后统计进答案，输出三角形内点数为 $0 \sim n-3$ 的三角形个数即可。

## Code

```cpp
// PikachuQAQ 2024/08/08

#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 302;

struct P {
    int x, y;
    friend bool operator < (P p1, P p2) {
        return (p1.x == p2.x) ? (p1.y < p2.y) : (p1.x < p2.x);
    }
} a[kMaxN];

int n, b[kMaxN][kMaxN], ans[kMaxN];

// 两点求一次函数 y = kx + b，返回 k 和 b
pair<double, double> Get(P a, P b) {
    double k = (1.0 * (a.y - b.y) / (a.x - b.x));
    return {k, (1.0 * a.y - k * a.x)};
}

// 点 p 是否在 y = kx + b 下方
bool isBelow(double k, double b, P p) {
    return p.y < (k * p.x + b);
}

// c 点是否在由 a，b 两点形成的直角梯形内
bool isInArea(P a, P b, P c) { 
    auto [k, b0] = Get(a, b);
    return a.x <= c.x && c.x <= b.x && isBelow(k, b0, c);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = i + 1; k < j; k++) {
                b[i][j] += isInArea(a[i], a[j], a[k]);
            }
        }
    }
    for (int i = 1; i <= n - 2; i++) {
        for (int j = i + 1; j <= n - 1; j++) {
            for (int k = j + 1; k <= n; k++) {
                auto [k0, b0] = Get(a[i], a[k]);
                ans[abs(b[i][j] + b[j][k] - b[i][k] + isBelow(k0, b0, a[j]))]++;
            }
        }
    }
    for (int i = 0; i <= n - 3; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
```

---

## 作者：RYANGSJ (赞：1)

题目要求求出三角形内的点个数，我们可以通过容斥转化成求两条直线之间的点的个数：

![](https://cdn.luogu.com.cn/upload/image_hosting/b0mr44s8.png)

记绿色部分点的个数为 $a$,记红色部分点的个数为 $b$,记蓝色部分点的个数为 $c$，那么三角形内点的个数即为$\frac{a+b+c+s_1+s_2+s_3-(n-3)}{2}$（三角形内的部分被算了三遍）。

然后再来考虑如何求出两直线之间点的个数，我们可以枚举一个点 $(x_i,y_i)$，以 $(x_i,y_i)$ 为坐标原点建坐标系，然后对每个点进行极角排序，再枚举两个点 $(x_j,y_j),(x_k,y_k) \ (j<k)$，我们可以得到两条交于 $(x_i,y_i)$ 的直线，这两条直线之间的点的个数即为 $j-i-1$。

上述过程中我们只能求出红色、绿色、蓝色区域的点的个数，为了求出 $s_1,s_2,s_3$ 内点的个数，我们需要在枚举 $(x_i,y_i)$ 后多对于每个 $(x_j,y_y)$ 加一个不被算贡献的虚点 $(-x_i,-y_i)$，然后计算两直线之间点的个数时，只用类型相同的两个点计算，并且不数虚点就可以了。



~~~c++
#include<bits/stdc++.h>
//#include<windows.h>
// #define double long double
// #define int long long
#define PII pair<int,int>
using namespace std;
namespace _IO{inline int read(){char ch=getchar();int f=1,res=0;while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){res*=10;res+=ch-'0';ch=getchar();}return res*f;}inline void write(int x){if(x<0){putchar('-');write(-x);}else if(x<10){putchar(x+'0');}else{write(x/10);putchar((x%10)+'0');}return;}}
namespace _Min{inline int Min(int x,int y){return x<=y?x:y;}inline int Max(int x,int y){return x>=y?x:y;}}

using namespace _IO;
using namespace _Min;

int n;
int ans[2000005];
struct Point{
	int x,y,id,k;
}a[2000005],b[2000005];
int sx,sy,tot;
int to[305][305][305];
bool cmp(Point x,Point y){//极角排序
	return atan2(x.y,x.x)<atan2(y.y,y.x);
}
void upd(int x,int y,int z,int v){
	if(x>y)swap(x,y);
	if(x>z)swap(x,z);
	if(y>z)swap(y,z);
	to[x][y][z]+=v;
	return;
}
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read(),a[i].id=i;
	}
	for(int i=1;i<=n;i++){
		tot=0;
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			a[j].x-=a[i].x,a[j].y-=a[i].y;
			tot++,b[tot]={a[j].x,a[j].y,a[j].id,1};
			tot++,b[tot]={-a[j].x,-a[j].y,a[j].id,0};
		}
		sort(b+1,b+1+tot,cmp);
		for(int j=1;j<=tot;j++){
			int now=0;
			int pos=j+1;
			while(1){
				if(pos==tot+1)pos=1;
				if(b[j].id==b[pos].id){
					break;
				}
				if(b[j].k==b[pos].k){
					upd(a[i].id,b[j].id,b[pos].id,now);
				}
				now+=b[pos].k;
				pos++;
			}
		}
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			a[j].x+=a[i].x,a[j].y+=a[i].y;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			for(int k=j+1;k<=n;k++){
				ans[(to[i][j][k]-(n-3))/2]++;
			}
		}
	}
	for(int i=0;i<=n-3;i++){
		write(ans[i]),puts("");
	}
	return 0;
}
~~~

---

## 作者：ACPCWATLEMLE (赞：0)

~~听说这个题普及组做的会比 NOI 的选手快。~~

发现 $C^3_n$ 可枚举，考虑枚举每一个三元组然后 $O(1)$ 查询。

我们可以预处理出每条线段下端的点的个数，然后查询的时候容斥原理就行了。

注意细节。
# code

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=302;
pair <double,double > dx[N];
int n,ans[N],cnt[N][N],f[N];
bool check(int i,int j,int id)
{
    if((dx[id].second-dx[i].second)*(dx[j].first-dx[id].first)<(dx[j].second-dx[id].second)*(dx[id].first-dx[i].first))
        return true;
    return false;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&dx[i].first,&dx[i].second);
    sort(dx+1,dx+1+n);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            for(int l=i+1;l<=n;l++)
                if(dx[l].first>dx[i].first&&dx[l].first<dx[j].first&&check(i,j,l))
                    cnt[i][j]++;
        }
    for(int i=1;i<=n;i++)
        if(dx[i].first==dx[i-1].first)
            f[i]=f[i-1]+(dx[i].second==dx[i-1].second?0:1);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            for(int l=j+1;l<=n;l++)
            {
                if(check(i,l,j))//在下面
                {
                    if(dx[i].first==dx[j].first||dx[l].first==dx[j].first)
                        ans[cnt[i][l]-cnt[i][j]-cnt[j][l]]++;
                    else
                        ans[cnt[i][l]-cnt[i][j]-cnt[j][l]-1-f[j]]++;
                }
                else
                {
                    if(dx[i].first==dx[j].first||dx[l].first==dx[j].first)
                        ans[cnt[i][j]+cnt[j][l]-cnt[i][l]]++;
                    else
                        ans[cnt[i][j]+f[j]+cnt[j][l]-cnt[i][l]]++;
                }
            }
    for(int i=0;i<=n-3;i++)
        printf("%d\n",ans[i]);
    return 0;
}



```

---

## 作者：baoyangawa (赞：0)

提供一篇极为麻烦的分讨做法。

## Part 1

我们先把所有点按照横坐标排序。

我们称呼点 $i$ 与点 $j$ 之间的线段为 $i-j$。

枚举两个点 $i, j$，我们能够以这两个点为锐角顶点，构造出两个直角三角形，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5inof0ul.png)

形象的，我们称呼它们分别为**上 / 下三角**。

可以计算出每个三角内部的点数（不包含边界。不妨假定 $y_i > y_j$）。

枚举一个 $k \in [i + 1, j - 1]$，先判断是否有 $y_i > y_k > y_j$，再通过线段 $i-j$，线段 $i-k$ 的斜率比较出 $k$ 处于上 / 下三角中的哪一个。

这部分的复杂度为 $O(n^3)$。

## Part 2

我们通过大减小计算三角形内点数。

### 锐角 / 直角三角形

![](https://cdn.luogu.com.cn/upload/image_hosting/60j08db2.png)（图一）

先粘一张图。我们可以考虑把三角形放进这样的一个矩形中计算。

我们用大矩形内部（不含边界）点数，分别减掉三个小直角三角形内的点数，就得到了以 $i,j,k$ 三个点构成的三角形内部，出现了多少个点。

### 钝角三角形

如果 $i,j,k$ 中存在两个点 $a,b$，满足 $x_a=x_b$ 或 $y_a=y_b$，就可以当做上面一种情况处理。

最恶心的就是下面的：

![](https://cdn.luogu.com.cn/upload/image_hosting/ywwysiol.png)（图二）

这种钝角三角形，不仅要减掉三个红色直角三角形，还要减掉那个绿色矩形内的点！！！！！

于是我们得到了一个整体的思路：先计算出每两个点之间的上 / 下三角点数，再把所有大矩形和绿色矩形拉出来跑一个二维数点，最后再加加减减一通处理就完了。

## Part 3

提几嘴细节实现：

首先是判断 Part 2 中的三角形，每条边应该选择上 / 下三角中的哪一个。这部分的判断对于任意三角形都成立。

当然一条边不是水平 / 竖直时才会产生这类贡献。

1. $i-j$ 边与 $j-k$ 边：当 $i-j$ 边的斜率（竖直线的斜率视作 $\infty$）大于 $j-k$ 边的斜率时，选择上三角，反之选择下三角。

2. $i-k$ 边：若 $j$ 点处于 $i-k$ 这条线段的上方，减去 $i-k$ 的下三角；反之减去其上三角。

以上面两张图举例，图一中 $j$ 处于 $i-k$ 的下方，故 $i-k$ 选择上三角；图二中 $j$ 处于 $i-k$ 的上方，故 $i-k$ 选择下三角。

关于二维数点部分，本质不同的询问最多只有 $2n\times2n$ 种，我们把每个点的 $x$ 和 $x-1$ 离散化一下，纵坐标同理，这样算上树状数组的复杂度，二维数点共 $O(n^2\log n)$。当然也可以直接把树状数组替换成暴力数点，复杂度 $O(n^3)$ 也能接受。

处理绿色矩形差分出来的四个坐标，我把钝角三角形按照纵坐标递增 / 递减，$j$ 在 $i-k$ 的上 / 下方，分了四种情况分别讨论，导致代码屎长。（因为不敢在枚举三角形时带上离散化查询的 $log$，模拟赛里开的 $500ms$，导致 $O(n^3\log n)$ 不敢跑）。

时间复杂度：$O(n^3 + n^2\log n)$

[参考代码](https://www.luogu.com.cn/paste/nl9fuq45)

---

## 作者：homo_snow (赞：0)

# 数学题

## 翻译

在一个直角坐标系内，有 $n$ 个点，每三个点可以围成的三角形内部的点的数量称为这个三角形的价值（三角形面积严格大于 $0$，边上的点不算。），求每一种价值对应的三角形的数量。

## 解法

显然的，直接求每个三角形内部点的数量十分的麻烦。

让我们回想一下数学老师给我们教的知识：如何在直角坐标系内求三角形面积？

~~行列式秒了。~~

老师教过我们一种办法叫割补法。

对于一个三角形 $\triangle ABC$，对 $A$、$B$、$C$ 分别做关于 $x$ 轴的垂线，垂足分别为 $D$、$E$、$F$。

不难得出，$S_{\triangle ABC} = |S_{ABED}-S_{ACFD}-S_{BCFE}|$。

同样的，这一招也可以作用到这题上。

直接暴力遍历每一条边，求出在这条边下面的点的数量，就可以套用上面的公式求出任意一个三角形 $\triangle ABC$ 的价值 $v$，将对应的 $v$ 的数量增加即可求出答案

但是，由于这一种容斥不会排除掉边上的点，所以需要顺便记录边上有哪些点，减掉即可。


---

