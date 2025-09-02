# 勤劳的蜜蜂 Bee Breeding

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=749

[PDF](https://uva.onlinejudge.org/external/8/p808.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA808/9bab4a64afdd472dc2664e3eff03743e904c3d4a.png)

## 样例 #1

### 输入

```
19 30
0 0```

### 输出

```
The distance between cells 19 and 30 is 5.```

# 题解

## 作者：Peter0701 (赞：5)

**写在前面：**
鄙人不才，略知一二，让大家见笑了

注：本题分析需要使用高中数学知识（AK IOI dalao可以无视）

------------
~~说正事专用分割线~~
## 题目分析：
首先，题面大家已经了解了，要求两个蜂房间的最短路径。明显是一道数学题。

那么应该怎么做呢？

显然，以1蜂巢为原点建立坐标系求解是很直观的

![建立坐标系](https://cdn.luogu.com.cn/upload/pic/34765.png)

高中数学里，我们学到：任意一个空间平面可以由空间一点及两个不共线的向量表示出来（如图）

因此，我们就可以借助这样一个坐标系来表示出所有的蜂巢

这样，我们可以推出蜂巢内任意一个点与原点之间的距离了（如图）

![距离公式](https://cdn.luogu.com.cn/upload/pic/34767.png)

那么，问题也就迎刃而解啦！（注意递推边界可靠找规律计算出来哦，具体方法请自行思考）



------------

~~防偷看分割线~~

**AC代码如下：**

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=10000;
struct Point
{
	int x, y;
	Point(int x=0, int y=0):x(x), y(y) {}
}p[maxn+330];
int dx[]={-1,-1,0,1,1,0};//六个方向
int dy[]={0,1,1,0,-1,-1};
int pos;
void cal(int dir,int l)//按照dir方向递推l个格子的坐标
{
    pos++;
    while(l--)
    {
        p[pos]=Point(p[pos-1].x+dx[dir],p[pos-1].y+dy[dir]);
        pos++;
    }
    pos--;
}
void Init()
{
    p[2]=Point(1,-1);
    pos=2;
    for(int l=1;l<=58;++l)
    {
        for(int dir=0;dir<4;++dir)	cal(dir,l);
        cal(4,l+1);
        cal(5,l);
    }
}
int main()
{
    Init();
    int n,m;
    while(scanf("%d%d",&n,&m)==2&&n)
    {
        int x=p[n].x-p[m].x;
        int y=p[n].y-p[m].y;
        int ans;
        if(x<0&&y>0||x>0&&y<0)ans=max(abs(x),abs(y));
        else ans=abs(x+y);
        printf("The distance between cells %d and %d is %d.\n",n,m,ans);
    }
    return 0;
}
```
欢迎在评论区提出疑问，找出错误，乐意解答，非常感谢大家的支持！

---

## 作者：ekatsim (赞：3)

补充一种和前面 dalao 殊途同归的思路。
# 题目
[勤劳的Bee](https://www.luogu.com.cn/problem/UVA808)
# 思路
由于蜂窝中一个点有 6 种转移方法（上、下、左上、左下、右上、右下），如果我们选择去根据转移方法来设计相应的数据结构，初始构造的时候会很麻烦，很明显这不是一个明智的选择。~~(其实是蒟蒻不会写)~~

所以，换个思路，我们不去设计数据结构，而是尝试把图存进熟悉的二维数组里，用“特殊”的方法来实现点的转移。

可以考虑把原图转化成以下形式：
![图片](https://cdn.luogu.com.cn/upload/image_hosting/8jhmqg52.png)
这个时候，我们按数字的顺序构造就方便多了。(具体构造方法见代码)

再仔细观察一下，原图中 1 号格子能直接到达的只有 2--7 号格子，转移后我们也需要保证这种转移成立，结合变换后的图我们能归纳出一个结论：

**在变换后的图上，一个格子仅能向上、下、左、右、左下、右上方移动。**

看到这里你或许已经恍然大悟了：如果两个格子互在二四象限这样的位置时，由于不能向右下方和左上方移动，那么最近距离应该是两点间的**曼哈顿距离**，即：
$abs(x_1-x_2)+abs(y_1-y_2)$。

若在其他位置时，两个格子间的最近距离应为两点间的**切比雪夫距离**，即：$\max(abs(x_1-x_2),abs(y_1-y_2))$。

辣么剩下的就是代码 Time~
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
int mat[maxn][maxn];
pair<int,int>loc[20005];//保存数字i转化后在二位数组的坐标。
int main()
{
    int x=500,y=500;
    loc[1]={x,y};
    mat[x][y]=1;
    x++;
    loc[2]={x,y};
    mat[x][y]=2;
    int next=2,len=0;
    while(next<=10000)//构造对应的二维数组
    {
        len++;
        for(int i=1;i<=len;i++)//向左移动并构造len个数字
            mat[x][--y]=++next,loc[next]={x,y};
        for(int i=1;i<=len;i++)//向上移动并构造len个数字
            mat[--x][y]=++next,loc[next]={x,y};
        for(int i=1;i<=len;i++)//向右上移动并构造len个数字
            mat[--x][++y]=++next,loc[next]={x,y};
        for(int i=1;i<=len;i++)//向右移动并构造len个数字
            mat[x][++y]=++next,loc[next]={x,y};
        for(int i=1;i<=len+1;i++)//向下移动并构造len+1个数字
            mat[++x][y]=++next,loc[next]={x,y};
        for(int i=1;i<=len;i++)//向左下移动并构造len个数字
            mat[++x][--y]=++next,loc[next]={x,y};
    }
    int a,b;
    while(scanf("%d %d",&a,&b),a)
    {
        printf("The distance between cells %d and %d is ",a,b);
        if((loc[a].first>loc[b].first&&loc[a].second>loc[b].second)||(loc[a].first<loc[b].first&&loc[a].second<loc[b].second))
            printf("%d.\n",abs(loc[a].first-loc[b].first)+abs(loc[a].second-loc[b].second));//曼哈顿距离
        else
            printf("%d.\n",max(abs(loc[a].first-loc[b].first),abs(loc[a].second-loc[b].second)));//切比雪夫距离
    }
    return 0;
}

```


---

## 作者：Aw顿顿 (赞：2)

## 简单距离

绕着 $1$ 的第一圈，即一步就能到达的位置，是 $2\sim 7$，也就是 $(1+1)\sim (1+1\times 6)$。

那再到外面去呢？

由于同时考虑一个区间比较复杂，我们考虑找一找「开头」的奥妙。

距离为 $1$ 的开头是 $2$，距离为 $2$ 的开头是 $8$，距离为 $3$ 的开头是 $20$，距离为 $4$ 的开头是 $38$……

有任何的关系么？有，对于距离为 $n$ 的，其开头是：

$$3n^2-3n+2$$

知道了开头，就可以判断结尾了。我们知道一圈的数量 $6n$，那么代入发现 $n$ 步的区间就是：

$$3n^2-3n +2\le x\le 3n^2+3n+1$$

之所以在结尾处减一，是因为起点算了两次。

## 所求距离

我们已经求出来的，是他们距离 $1$ 也就是起始点的距离。

其实剩下的内容挺好推断的，只要判断象限，然后使用适合于蜂巢图的距离就可，大概是某种意义上的曼哈顿距离。

---

## 作者：hewo (赞：0)

这里提供一个更直观 ~~(暴力)~~ 的生成坐标的方法：

我们将这个图分成许多层：

![](https://cdn.luogu.com.cn/upload/image_hosting/6y5x6uh9.png)

找规律可以发现：

第一层: $1$ 个

第二层: $6=6*1$ 个

第三层: $12=6*2$ 个

稍加思考下就可以获得:

第 $n$ 层: $6*(n-1)$ 个

这个 $6$ 代表的就是 $6$ 个方向，它们每次出现的顺序是固定的:

```cpp
int fx[6]={-1,-1,0,1,1,0};
int fy[6]={0,1,1,0,-1,-1};
```

而且我们还可以发现，每一层走完后，下一层第一个都在这一层最后一个的正下方。

按照这样就可以直接暴力生成了：

```cpp
inline void csh()
{
	int x,y;
	x=0,y=0;
	int id=0;
	q[++id]={x,y};
	int num=1;
	for(int i=1;i<=80;i++)
	{
		y--;//走到正下面一格来
		q[++id]={x,y};
		for(int j=0;j<6;j++)//枚举6个方向
		{
			if(j==0)
			{
				for(int k=1;k<=num-1;k++)//对于第一个方向，因为已经赋过一个的值了，所以只枚举 num-1 个
				{
					x=x+fx[j],y=y+fy[j];
					q[++id]={x,y};
				}
				continue;
			}
			for(int k=1;k<=num;k++)//枚举每一步
			{
				x=x+fx[j],y=y+fy[j];
				q[++id]={x,y};
			}
		}
		num++;
	}
}
```
生成好坐标系后其他的就可以按另外两位大佬的思路来做了

#### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MX=2*100000+1000;
#define LL long long
#define inf 0x3f3f3f3f

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

struct tDL
{
	int x,y;
}q[MX];

int fx[6]={-1,-1,0,1,1,0};
int fy[6]={0,1,1,0,-1,-1};

inline void csh()
{
	int x,y;
	x=0,y=0;
	int id=0;
	q[++id]={x,y};
	int num=1;
	for(int i=1;i<=80;i++)
	{
		y--;//走到正下面一格来
		q[++id]={x,y};
		for(int j=0;j<6;j++)//枚举6个方向
		{
			if(j==0)
			{
				for(int k=1;k<=num-1;k++)//对于第一个方向，因为已经赋过一个的值了，所以只枚举 num-1 个
				{
					x=x+fx[j],y=y+fy[j];
					q[++id]={x,y};
				}
				continue;
			}
			for(int k=1;k<=num;k++)//枚举每一步
			{
				x=x+fx[j],y=y+fy[j];
				q[++id]={x,y};
			}
		}
		num++;
	}
}

int main(int argc, char const *argv[])
{
//	freopen("debug.out","w",stdout);
	csh();
//	for(int i=1;i<=233;i++)
//    {
//    	printf("i: %d	x: %d	y: %d\n",i,q[i].x,q[i].y);
//    }
	int ans;
	do
	{
		int n,m;
		n=read(),m=read();
		if(n==0&&m==0) return 0;
		int nx=q[n].x,ny=q[n].y;
		int mx=q[m].x,my=q[m].y;
		int x=nx-mx,y=ny-my;//相当于换的原点
		if((x>0&&y>0)||(x<0&&y<0)) ans=abs(x+y);
		else ans=max(abs(x),abs(y));
		printf("The distance between cells %d and %d is %d.\n",n,m,ans);
	}
	while(1);
	return 0;
}
```

---

