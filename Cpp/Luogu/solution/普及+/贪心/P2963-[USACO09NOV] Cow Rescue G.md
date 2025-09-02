# [USACO09NOV] Cow Rescue G

## 题目描述

Bessie is trapped in a triangular maze with N rows (1 <= N <= 1,000,000). A three row maze is shown below:

The i'th row of the maze contains 2\*i-1 triangles. Numbering from the left, the triangles are named (i,1), (i,2), and so on.

Bessie can travel to the (often three) triangles which share an edge with her current triangle. For example, if she is at (3, 3), she can travel to (3, 2), (3, 4) and (4, 4). Bessie takes one minute to travel from one triangle to the next.

FJ has learned the Bessie is trapped and knows by tracking her iPhone that she starts her exit trek at triangle (Si,Sj). FJ's love for Bessie knows no bounds so he wants her back in the minimum possible time.

The maze has M (1 <= M <= 10,000) exits found in locations throughout the set of triangles. Any one of these will enable Bessie to escape. Once she enters an exit triangle, she leaves the maze in just one more minute.

Find the minimum time in minutes, T, required for Bessie to exit the maze and report the optimal exit location she uses, (OUTi, OUTj). If more than one location requires only T minutes, output the location with the smallest row. If two optimal rows are the same, output the one with smaller column.

贝希被困在一个三角形的迷宫之中。这个迷宫有 $N$ 行（$1 \le N \le 1000000$）。比如下图是一个 $3$ 行的迷宫。  迷宫的第 $i$ 行有 $2i-1$ 个三角形，从左到右分别编号为 $(i, 1)$、$(i, 2)$ 等等。

贝希每次可以从一个三角形走到任意一个一个跟当前的三角形有邻边的三角形。

比如说，如果她目前处于三角形 $(3, 3)$，那么，她可以走到三角形 $(3, 2)$、$(3, 4)$ 和 $(4, 4)$。贝希每次需要一分钟的时间来移动到下一个三角形。

农夫约翰发现贝希被困了！于是她跟踪贝希的iPhone手机（可怜的触摸屏～），得知贝希目前处于三角形 $(S_i, S_j)$。

因为约翰对贝希有著无穷无尽的浓浓爱意，所以他希望贝希能尽可能快地回到他的身边。 在迷宫的三角形之中，有 $M$（$1 \le M \le 10000$）个是出口。在任何一个出口都可以让贝希逃离迷宫。一旦贝希进入一个作为出口的三角形，她用多一分钟就可以逃离这个迷宫。 找到一个可以让贝希逃离迷宫最小时间 $T$，并输出她应该从哪一个出口逃离迷宫，这个出口记为 $(\text{OUT}_i, \text{OUT}_j)$。

如果有多个出口同时需要时间 $T$，输出那个行的编号小的出口，如果仍然有多个出口，输出那个列的编号小的。


## 样例 #1

### 输入

```
4 2 
2 1 
3 5 
4 4 
```

### 输出

```
4 4 
4 
```

# 题解

## 作者：chenly8128 (赞：2)

# 一、大体思路
## 方法一：单源最短路算法

这是最好想的方法，广度优先搜索跑一遍，预处理每一格离出发点的距离，然后每个出口比较一下，比出距离最小的。时间复杂度 $O(n^2+m)$，空间复杂度 $O(n^2)$，显然按照本题的数据规模是过不了的，~~大概能骗个部分分吧~~。

## 方法二：

从第一个方法可以发现：计算一个出口距离出发点的距离是关键！！！于是有一个如果能 $O(1)$ 计算距离，就有总复杂度为 $O(m)$ 的方法可以解决问题。

### 计算距离的方法

本题麻烦就麻烦在由三角形构成这个条件上，首先画个图～～
![](https://cdn.luogu.com.cn/upload/image_hosting/undhrav6.png)
#### 垂直方向上的移动

易得共需起点和终点的「纵坐标相差量」次垂直移动，记「纵坐标相差量」为 $x$。

#### 非垂直方向上的移动
1. 这张图为我自己画的样例解释图，可以发现，每当贝希进行垂直移动 $x$ 次时（很明显不走回头路），至少需要进行 $x-1$ 次非垂直移动。
2. 三角形可以分为两类，一类是尖叫朝上的，另一类是尖角朝下的。尖角朝上的三角形不能向上移动，尖角朝下的三角形不能向下运动。所以如果起始位置无法按照需要的方向进行垂直运动，那么非垂直移动需要量多一次；同理，如果结束位置无法按照需要的方向进行垂直运动，那么非垂直移动需要量多一次。记需要量的总增加量为 $t$。
3. 对于任意两点，它们之间的路径至少有「横坐标相差量」次非垂直移动。记「横坐标相差量」为 $k$。

综合 1、2、3，得**非垂直移动需要 $\max(k,x-1+t)$ 次。**

总结一下，$AB$ 两点之间的距离为 $\max(k,x-1+t) + x$ 具体实现见代码！

### 坑点

**请注意！！！贝希要离开迷宫还需要一分钟，要加一！**

### 代码

[AC 最优解记录](https://www.luogu.com.cn/record/146636341)
```cpp

#include <iostream>
using namespace std;
const int MAXM = 10000+10;
const int INF = 0x3f3f3f3f;
int n,m;
int sx,sy;
int ex[MAXM],ey[MAXM];
bool flag;
int ans = INF,res = INF,sum;
int main(void) {
    ios::sync_with_stdio(false);
    cin >> n >> m >> sx >> sy;
    if (sy&1) flag = true;
    else flag = false;
    for (int j = 1;j <= m;j++) {
        cin >> ex[j] >> ey[j];
        
        sum = -1;
        if ((ey[j] & 1) ^ (ex[j] <= sx)) sum++;
        if (flag ^ (ex[j] >= sx)) sum++; // 这三行，计算需要量的总增加量
        
        sum += abs(ex[j] - sx);		// 纵坐标的差
        sum = max(sum,abs(-ex[j] + ey[j] + sx - sy)/*此段为横坐标差的计算*/) + abs(ex[j]-sx)+1;			// 总距离计算
        
        if (sum < ans) {	//更新答案
            ans = sum;
            res = j;
        }
    }
    cout << ex[res] << ' ' << ey[res] << '\n' << ans;
    return 0;
}

```

---

## 作者：Tracy_Loght (赞：1)

## 题目大意：

求多点在三角字形塔中的距离。

## 分析：

找规律，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6es4ablb.png)

~~（你看看我多好，还不点个赞）~~

有一个容易得到的结论:

![](https://cdn.luogu.com.cn/upload/image_hosting/uuka1c9e.png)

比如我们要从 $6$，$6$ 走到 $4$ 行的任意一个位置，则一定可以用三到四步之间走到。

- $3$ 步：第二个坐标为奇数。

- $4$ 步：第二个坐标为偶数。

映射到所有的情况，从 $a$，$b$ 到 $x$，$y$ 且 $(a > x)$，则 $y$ 如果在区间 $[b - ( a - x ) \times 2，b]$ 内只需要 $( a - x ) \times 2$ 或 $( a - x ) \times 2 +1$ 次破壁，具体看奇偶性。

如果不在这个区间内呢？

答案是两点之间，直线最短，计算区间里目标的最短距离即可（直线上不需要说了吧）。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,s,x,y,jl=99999999;
long long mx,my;
int dpzc_jf(int a,int b,int x,int y){
	int l,r,p=(a-x)*2;
	if(b%2==1) {l=b-p;r=b;}
	else {l=(b+1)-p;p--;r=b-1;}
	if(l<=0) l=1; if(r>x*2-1) r=x*2-1;
	if(l<=y&&y<=r) return y%2==1?p:p+1;
	else if(y>r) return p+y-r;else return p+l-y;
}
int main(){
	ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0); 
	cin>>n>>m>>x>>y;
	while(m--){
		long long a,b,as;cin>>a>>b;
		if(a>x) as=dpzc_jf(a,b,x,y);
		else as=dpzc_jf(x,y,a,b);
		if(as+1<jl) mx=a,my=b;
		jl=min(jl,as+1);
	}
	cout<<mx<<" "<<my<<"\n";
	cout<<jl;
	return 0;
}

```

---

## 作者：zjo_2001 (赞：1)

肯定是先将所有的出口按字典序排序,从小到大枚举终点,然后要O(1)的算出起点和终点的距离.

考虑到这些三角形很不好搞,可以把每一行复制一遍,然后把三角形的每一行都往前推一下,就像这样:

O
O
OO
OO
OOO
OOO
OOOO
这是n=4的情况.

可以发现,在这个新图里面,每个点都可以往上下走,奇数行的可以往右下方走,偶数行的可以往左上方走.

那么就可以贪心了.

先求出起点和终点在新图中的对应编号.

假设终点在下面.

首先先让终点一直往正上方走,知道走到和起点同行.

还可以算出走到上面的过程中最多可以往左边走多少.

那么判断一下起点和终点的列的关系.

若起点的列在终点的列的右边,那么就要一上一下的往右走.

若在左边,那么再判断一下是否可以在往上走的过程中可以走到.

若不能走到,也要一上一下的往左边走.

不知道标签为什么会有一个逆元


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<complex>
#include<queue>
#include<stack>
#include<cmath>
#include<set>
#include<vector>
#define maxn 10010
using namespace std;
struct data{
  int x,y;
}t[maxn],ans;
inline bool cmp(const data &A,const data &B){
  return A.x==B.x?A.y<B.y:A.x<B.x;
}
int main(){
  int n,m,sx,sy,zx=1<<30;
  scanf("%d%d%d%d",&n,&m,&sx,&sy);
  if(sy&1) sx=2*sx-1;else sx=2*sx-2;
  sy=(sy+1)/2;
  for(int i=1;i<=m;i++){
    scanf("%d%d",&t[i].x,&t[i].y);
  }
  sort(t+1,t+m+1,cmp);
  for(int i=1;i<=m;i++){
    int x1=t[i].x,x2=sx,y1=t[i].y,y2=sy,tmp;
    if(y1&1) x1=2*x1-1;else x1=2*x1-2;
    y1=(y1+1)/2;
    if(x1>x2) swap(x1,x2),swap(y1,y2);
    tmp=x2-x1;int can=(x2-x1+(bool)(x2&1))/2;
    if(y1>=y2) tmp+=(y1-y2)*2;
    
    else{
      y2-=can;
      if(y2>y1)tmp+=(y2-y1)*2;
    }
    if(tmp+1<zx) zx=tmp+1,ans=t[i];
  }
  printf("%d %d\n%d",ans.x,ans.y,zx);
  return 0;
}

```

---

## 作者：_Weslie_ (赞：0)

另类做法。

感谢 @chenly8128 提供的图片。

## 思路

首先我们对每个点坐标重新标号。即原来的 $(x,y)$ 变为 $(x,n-x+y)$。变更完后坐标如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zt4apvdi.png)

然后我们需要对于起点，画 $2$ 条线，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/hdtr8ux1.png)

这两条线把整个平面分成了 $4$ 部分。

首先，在同一直线上的点 $(x_1,y_1)$ 与 $(x_2,y_2)$，它们的距离为 $|x_1-x_2|+|y_1-y_2|$。

同一纵坐标的点也有性质：对于点 $(x_1,y)$ 与 $(x_2,y)$，它们的距离为 $|x_1-x_2|$。

然后对于 $2$ 和 $4$ 两个区域的点，不难发现 $(x,y)$ 与 $(sx,sy)$ 的距离就是 $|sx-x|+|sy-y|$，这个手搓几组就能发现。

关键是对于另外两个区域的求解，以区域 $3$ 为例。

研究两条直线的性质，发现：从左下到右上的线途径的点横纵坐标之和只有两个值，这样我们就可以用 $(a,b)$（其中 $a<b$）表示一条直线。例如上图中的左下到右上的线，我们可以用 $(5,6)$ 表示。

从左上到右下线上的点也满足一个性质：横纵坐标差为定值（此处的横纵坐标差默认为 $x-y$）。可以用 $(c,d)$ 表示这种直线（$c>d$）。例如上图的直线，就是 $(0,-1)$。

手搓一下就会发现：$a$ 为奇数，$b$ 为偶数，$c$ 为偶数，$d$ 为奇数。

这样，我们可以 $\operatorname{O}(1)$ 地通过一个点求解一条直线的表示。

![](https://cdn.luogu.com.cn/upload/image_hosting/r0txgg6i.png)

假如我们要求 $(4,3)$ 到 $(2,3)$ 的距离，如何求呢？

首先要明确一个事实：如果 $x$ 和 $y$ 都是整数，且 $x+y$ 为奇数，则 $x-y$ 是奇数。

不难发现交点有 $2$ 个，一个横纵坐标相加是奇数，一个是偶数。

我们选取奇数的求解交点坐标 $(x,y)$。

按照上面的性质：

> $a$ 为奇数，$b$ 为偶数，$c$ 为偶数，$d$ 为奇数。

可以发现 $(x,y)$ 满足一个方程组：

$$\begin{cases}
x+y=a\\
x-y=d
\end{cases}$$

显然 $x=\dfrac{a+d}{2}$，$y=a-\dfrac{a+d}{2}$。

然后就可以用直线上点的坐标公式求距离了。假设起点是 $(sx,sy)$，终点是 $(tx,ty)$，那么经过 $(x,y)$ 由 $(sx,sy)$ 到 $(tx,ty)$ 的距离是 $|sx-x|+|sy-y|+|tx-x|+|ty-y|$。

到这里我们就做完了。证明在代码下面。

注意一个细节：Bessie 逃出迷宫还要再花 $1$ 秒。

另一个细节：我们在前面转化了横纵坐标，但是题目中要求输出的不是这个，所以要转回去。原来是 $y_0$，现在变成了 $y=n-x+y_0$，自然 $y_0=y-n+x$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,m,x[10005],y[10005],ansx,ansy,ans=2147483647,sx,sy,nans;
int abss(int _){
	if(_>0)return _;
	return -_;
}
int main(){
	cin>>n>>m>>sx>>sy;
	sy=n-sx+sy;
	int a,b,c,d;
	if((sx+sy)%2==1){
		a=sx+sy;
		b=a+1;
	}
	else{
		b=sx+sy;
		a=b-1;
	}
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
		y[i]=n-x[i]+y[i];
	}
	for(int i=1;i<=m;i++){
		int hc=abss(sx-x[i]),zc=abss(sy-y[i]);
		if(hc<=zc){
			nans=hc+zc;
		}
		else{
			if((x[i]-y[i])%2==0){
				c=y[i]-x[i];
				d=c+1;
			}
			else{
				d=y[i]-x[i];
				c=d-1;
			}
			int jx,jy;
			jx=(a-d)/2;
			jy=a-jx;
			nans=abss(jx-x[i])+abss(jx-sx)+abss(jy-y[i])+abss(jy-sy);
		}
		if(nans<ans){
			ansx=x[i];
			ansy=y[i];
			ans=nans;
		}
	}
	cout<<ansx<<' '<<(ansy-n+ansx)<<endl<<ans+1;
	return 0;
}
```

## 证明

如何证明上面的做法是正确的？

其实我们可以把这个三角形矩阵抽象成一个正方形矩阵：

![](https://cdn.luogu.com.cn/upload/image_hosting/qabvpipw.png)

黑色代表可以走，红色则代表不能走。

不难发现我们在原图中画的每一条线（即两条蓝线和一条绿线）都是正好绕过了每一个不能走的边。

首先对于区域 $2$ 和区域 $4$（即线外面的区域），如果只能 $90^{\circ}$ 转弯，那么很显然我们可以把这条折线平移成只拐一次弯的折线，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/nd6vlor4.png)

再加上同一纵坐标上的移动，这一条线实质上是绕着长方形边框走了一圈，显然最优。

再看线内：

![](https://cdn.luogu.com.cn/upload/image_hosting/qabvpipw.png)

我们显然希望绕过的红边最少最优，因为每绕过一个红边就要多走两步。

而我们在前面提到我们在原图中画的每一条线（即两条蓝线和一条绿线）都是正好绕过了每一个不能走的边，也就是意味着它走了每一条可以走的边。

或者可以这么理解：我们如果沿着绿线从 $(4,3)$ 往上走，在不向右走的情况下，到达同一纵坐标的横坐标最大，也就是最靠右。如果这个点就是前文提到的交点，那么我们就可以沿着另一条线直接到达。

所以这样的路线一定是最优的。

---

