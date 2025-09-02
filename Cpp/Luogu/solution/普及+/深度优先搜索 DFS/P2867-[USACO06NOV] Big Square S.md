# [USACO06NOV] Big Square S

## 题目背景

[English version](https://www.luogu.com.cn/paste/x781adew)

## 题目描述

农民 John 的牛参加了一次和农民 Bob 的牛的竞赛。他们在区域中画了一个$N\times N$ 的正方形点阵，两个农场的牛各自占据了一些点。当然不能有两头牛处于同一个点。农场的目标是用自己的牛作为$4$个顶点，形成一个面积最大的正方形 （不必须和边界平行） 。 除了 Bessie 以外，John其他的牛都已经放到点阵中去了，要确定Bessie放在哪个位置，能使得John的农场得到一个最大的正方形(Bessie不是必须参与作为正方形的四个顶点之一)。

## 样例 #1

### 输入

```
6
J*J***
******
J***J*
******
**B***
******```

### 输出

```
4```

# 题解

## 作者：_____hzf_____ (赞：22)

更良好的阅读体验，在[博客](https://www.cnblogs.com/hzf29721/p/9461204.html)食用更佳~QAQ

#### 题意：
有一块n*n的区域，给你一些FJ的点和Bob的点，现在让你添加一个点，使FJ的点构成的正方形最大（不能添加在Bob的点上）。

样例解释：

![](https://cdn.luogu.com.cn/upload/pic/46149.png )

样例输入为一个$6 \times 6$的地图，橙色点为FJ的奶牛，绿色点为Bob的奶牛，白色点为未占用区域，能够成的最大正方形为ABOC，面积为$2x2=4$。

其实添加一个点能够成的最大的正方形是BCED，面积为$2 \times 2+2 \times 2=8$，可是点E是Bob的奶牛，两头奶牛不能放在同一个点上，所以只能选择前一种方案，输出4。
### 题解

一般来说，想要构造正方形，枚举边有两种情况，一种上方，一种下方，如图：

![]( https://cdn.luogu.com.cn/upload/pic/46150.png )

枚举A，B两点的坐标，若是以A，B为正方形的边长，会枚举出两个正方形， 正方形ABCD 和 正方形ABFE ，这时就不利于我们进行很好的计算。若是以A，B为正方形的对角线呢？

![](https://cdn.luogu.com.cn/upload/pic/46151.png )

如图，我们枚举A，B两点为 正方形ACBD 的对角线，只能画出唯一一个正方形，我们的最基本的目的达到了——保证正方形的唯一性。

接下来，知道了A，B两点的坐标，如何得出C，D两点的坐标呢？

通过观察，我们发现，

A，B横坐标差=HG=HE=AE-AH；

A，B纵坐标差=AE+BF=AE+AH；

两式相加减后得：

2DH=(A，B纵坐标差)+(A，B横坐标差)；

2AH=(A，B纵坐标差)-(A，B横坐标差)；

所以

DH=CF=((A，B纵坐标差)+(A，B横坐标差))/2；

AH=BF=((A，B纵坐标差)-(A，B横坐标差))/2；

D点坐标即为(AX+DH,AY+AH);

C点坐标即为(BX-CF,BY-BF);

值得注意的是，现在C，D的坐标还没定下来，因为有可能出现另一种情况：

![](https://cdn.luogu.com.cn/upload/pic/46152.png )

即将上一个图轴对称过来，这时按刚刚的方程得出来的是Q，R两点，并不是我们想要的正方形，这时只需要将方程变动一下就好了：

L点坐标即为(JX+JP,JY+PL);

I点坐标即为(KX-NK,KY-NI);

正方形构造好了，接下来就只需要统计最大的就行了，因为FJ可以往点阵里添加一个点，所以只需要四个顶点中有>=3个点就能构造成。

最后贴上通俗易懂的代码：


```c
#include<bits/stdc++.h>
#define F(i,j,n) for(register int i=j;i<=n;i++)
using namespace std;
int n,s=0,ans=0,a1,a2,a3,a4,a5,a6,a7,a8;
char a[105][105];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}
	return x*f;
}
inline int solve(int Sum,int Minus,char Kind){
	if(Kind=='+')
		return (Sum+Minus)>>1;
	if(Kind=='-')
		return (Sum-Minus)>>1;
}
int main(){
	n=read();
	F(i,1,n)
		scanf("%s",a[i]+1);
	F(i,1,n)/*枚举右下的点的横坐标*/
		F(j,1,n)/*枚举右下的点的纵坐标*/
			F(k,1,i)/*枚举左上的点的横坐标*/
				F(tt,1,j){/*枚举左上的点的纵坐标*/
					if(a[i][j]=='B'||a[k][tt]=='B')/*如果有Bob的牛就continue*/
						continue;
					int Sum=max(i-k,j-tt),Minus=min(i-k,j-tt);
					if((Sum&1)!=(Minus&1))/*细节！判断奇偶性是否相同*/ 
						continue;
					int px=solve(Sum,Minus,'+'),py=solve(Sum,Minus,'-');/*计算出两式和与差*/
					int p=k+px,q1=tt+py,u=i-px,v=j-py;/*得出剩下两点*/
					if(((p-u)*(p-u)+(q1-v)*(q1-v))!=(Sum*Sum+Minus*Minus))/*考虑轴对称的情况*/
						p=k+py,q1=tt+px,u=i-py,v=j-px;
					if(p>=1&&q1>=1&&u>=1&&v>=1&&p<=n&&q1<=n&&u<=n&&v<=n)
						if(a[i][j]!='B'&&a[k][tt]!='B'&&a[p][q1]!='B'&&a[u][v]!='B'){
							s=0;
							if(a[i][j]=='J')
								s++;
							if(a[k][tt]=='J')
								s++;
							if(a[p][q1]=='J')
								s++;
							if(a[u][v]=='J')
								s++;
							if(s>=3&&px*px+py*py>ans){
								ans=px*px+py*py;
								a1=i;a2=j;a3=u;a4=v;
								a5=k;a6=tt;a7=p;a8=q1;
							}
						}
				}
	printf("%d\n",ans);
	//printf("\n\n%d %d\n%d %d\n%d %d\n%d %d\n",a1,a2,a3,a4,a5,a6,a7,a8);
	return 0;
}
```

---

## 作者：Yuanchenpu (赞：6)

数据比较小，可以暴力水过。

可以枚举正方形同一条边上的两个点，计算得出另外两个点（画个图就知道了），判断是否符合条件即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN = 105;

int n, ans;
int a[MAXN][MAXN];

bool inMap(int x, int y) {return x >= 1 && x <= n && y >= 1 && y <= n;} 	//判断是否在地图中

int main() {
	char c;
	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			c = getchar();
			if (c == '\n')
				c = getchar();
			if (c == 'J') {
				a[i][j]++;
			}
			if (c == 'B') {
				a[i][j] = -1;
			}
		}
	}
	int x1, y1, x2, y2, s;
	for (register int i = 1; i <= n; i++) {
		for (register int j = 1; j <= n; j++) {
			for (register int x = i; x <= n; x++) {
				for (register int y = j; y <= n; y++) {
					x1 = x - y + j;		//计算坐标
					x2 = i - y + j;
					y1 = y + x - i;
					y2 = j + x - i;
					if (inMap(x1, y1) && inMap(x2, y2)) {
						if (a[i][j] < 0 || a[x][y] < 0 || a[x1][y1] < 0 || a[x2][y2] < 0) continue;
						if ((a[i][j] + a[x][y] + a[x1][y1] + a[x2][y2]) >= 3) { 	//因为Bessie可以占一个点，所以只用≥3
							s = (x - i) * (x - i) + (y - j) * (y - j);		//勾股定理计算面积
							ans = max(ans, s);
						}
					}
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：littlesnake (赞：4)

先看题，$n$ 只有 100，这样的话，暴力就可以水过？

但是，也是得讲点优化滴，枚举正方形上面**同一条边**的两个顶点（~~奶牛顶点~~），这样就可以算出另外两个点（思路和各位大佬们差不多）。

```cpp
#include <iostream>
#include <cstdio>
#define MAXN 110//个人习惯：能用define就不用const
using namespace std;
int a[MAXN][MAXN];
int n,ans;
char c;
bool check(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=n;
} 
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			c=getchar();
			if(c=='\n')c=getchar();
			if(c=='J')a[i][j]++;
			if(c=='B')a[i][j]=-1;
		}
	}
	int x1,y1,x2,y2,s;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++){
			for(register int x=i;x<=n;x++){
				for(register int y=j;y<=n;y++){
					x1=x-y+j,x2=i-y+j,y1=y+x-i,y2=j+x-i;
					if(check(x1,y1)&&check(x2,y2)){
						if(a[i][j]<0||a[x][y]<0||a[x1][y1]<0||a[x2][y2]<0)continue;
						if((a[i][j]+a[x][y]+a[x1][y1]+a[x2][y2])>=3){ 	
							s=(x-i)*(x-i)+(y-j)*(y-j);//不想写pow()	
							ans=max(ans,s);
						}
					}
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```
完结撒花~

---

## 作者：Zory (赞：3)

那个，推广一下个人网站。。这篇文章用到了公式，所以去那里会更好看


http://zory.cf/2017-12/大广场.html

## 来源和评测点

USACO06 NOV


[Luogu2867](https://daniu.luogu.org/problemnew/show/2867)

## 题目

**【题目大意】**

农民 John 的牛参加了一次和农民 Bob 的牛的竞赛。

他们在区域中画了一个N乘N 的正方形点阵，两个农场的牛各自占据了一些点。

当然不能有两头牛处于同一个点。

农场的目标是用自己的牛作为4个顶点，

形成一个面积最大的正方形(不必须和边界平行) 。

除了 Bessie 以外，FJ其他的牛都已经放到点阵中去了，

要确定bessie放在哪个位置，

能使得农民约翰的农场得到一个最大的正方形

(Bessie不是必须参与作为正方形的四个顶点之一)。

**【输入格式】**

第一行是N

接下来是一个N乘N的矩阵，

字符解释:

'J' John 的牛,

'B' Bob 的牛,

'\*' 空点。

数据保证至少一个空点

**【输出格式】**

面积，如果没有就输出0

**【输入样例】**

```cpp
6
J*J***
******
J***J*
******
**B***
******
```
**【输出样例】**

4

## 分析

随便用暴力做，居然过了……

难点就是已知对角线上两个点求出正方形另外两个点


膜师兄时大概用了高中向量的知识，但也挺好理解的，

就是“固定方向固定距离”？


假如有两个点$(a,b)和(c,d)$，把他们作为对角线

先计算出中点$(mx=\frac{a+c}{2},my=\frac{b+d}{2})$

计算出两点间向量$(fx=\frac{a-c}{2},fy=\frac{b-d}{2})$

向量反转，另外两点分别为$(qx=mx+(-fy),qy=my+(fx))和(mx+(fy),my+(-fx))$

面积则是$( \sqrt{ (a-qx)^2+(b-qy)^2 })^2=(a-qx)^2+(b-qy)^2$


## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int mymax(int x,int y) {return x>y?x:y;}

const int MAXN=150;

struct nod
{
    int x,y;
}p[MAXN*MAXN];//已经使用的点
int ptn=0;//数量

int mp[MAXN][MAXN];

int n;

//判断x是不是整数y，我随便打的。。不是很严谨
bool dint(double x,int y)
{
    double ty=y;
    return ty-0.001<=x and x<=ty+0.001;//在大致区间内
}

int ans=0;
void solve()
{
    for(int i=1;i<=ptn;i++)
    {
        for(int j=1;j<=i-1;j++)//枚举互为对角线的点
        {
            double a=p[i].x,b=p[i].y;//点1
            double c=p[j].x,d=p[j].y;//点2
            
            double mx=(a+c)/2.0,my=(b+d)/2.0;//中点
            double fx=(a-c)/2.0,fy=(b-d)/2.0;//向量
            
            double qx=mx+(-fy),qy=my+(fx);
            if(qx<1 or qx>n) continue;if(qy<1 or qy>n) continue;
            double wx=mx+(fy),wy=my+(-fx);
            if(wx<1 or wx>n) continue;if(wy<1 or wy>n) continue;
            //理论做法：取中间向量，并应用在中点上
            //由于初三还没正式学向量，不严谨
            if(qx==wx and qy==wy) continue;
            int ax=int(qx+0.5),ay=int(qy+0.5);//注意四舍五入
            int bx=int(wx+0.5),by=int(wy+0.5);
            if(!dint(qx,ax)) continue;//不是整点
            if(!dint(qy,ay)) continue;//不是整点
            if(!dint(wx,bx)) continue;//不是整点
            if(!dint(wy,by)) continue;//不是整点
            
            int qm=mp[ax][ay],wm=mp[bx][by];//状态
            if(qm==1 or wm==1) continue;//被占用
            if(qm==0 and wm==0) continue;//贝西只有一个……
            double sq=(a-qx)*(a-qx)+(b-qy)*(b-qy);//面积
            ans=mymax(sq,ans);
        }
    }
}

char s[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s+1);
        for(int j=1;j<=n;j++)
        {
            if(s[j]=='*') mp[i][j]=0;
            if(s[j]=='B') mp[i][j]=1;
            if(s[j]=='J') 
            {
                ptn++;
                p[ptn].x=i;p[ptn].y=j;
                mp[i][j]=2;
            }
        }
    }
    solve();
    printf("%d",ans);
}
```

---

## 作者：mairuisheng (赞：2)

题目分析：

输入一个 $N\times N$ 的矩阵，包含 `J`，`B` 和 `*`，至多再放置一个 `J`（不能放置在 `B` 上），求用 `J` 的作顶点正方形最大面积是多少（正方形可以不与边界平行）。

算法：枚举

算法分析：

每次枚举正方形两个顶点的横坐标与纵坐标，相应的得出另外两个顶点的横坐标与纵坐标。

先判断这两个点是否在地图内，然后判断这些点是否被 `Bob` 的牛占领。

如果这两个点都在地图内且没被 `Bob` 的牛占领，那么接着统计这四个点上是否是 `John` 的牛，如果有大于等于三个点是 `John` 的牛（第四个点可以是 `Bessie`，所以是 $4-1=3$ 个牛），就更新最大面积。

面积公式：

$(x_1-x_2)^2+(y_1-y_2)^2$

其中，$(x_1,y_1)$ 表示第一个顶点的坐标，$(x_2,y_2)$ 表示第二个顶点的坐标。

时间复杂度：
$O(N^4)$，$N\le100$，不超时。

代码：
```cpp
#include<cstdio>
#include<cmath>//pow要用到cmath库 
#define mp(x,y) if(mp[x][y]=='J')++cnt;
using namespace std;
inline int read()//快读 
{
	int x=0,f=1;
	char s;
	s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-')f=-f;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<3)+(x<<1)+(s-48);
		s=getchar();
	}
	return x*f;
}
const int N=101;
int n;
int ans;//ans记录最大面积 
char mp[N][N];
int area(int x,int y,int x2,int y2)
{
	return pow(x-x2,2)+pow(y-y2,2);//面积公式 
}
int max(int x,int y)//自定义max 
{
	return x>y?x:y;
}
bool check(int x,int y)
{
	return (x>0&&x<=n)&&(y>0&&y<=n);//判断是否在地图范围内 
}
int main()
{
	int i,j,k,l,x,y,x2,y2,cnt,r;
	n=read();//读入
	for(i=1;i<=n;++i)
	{
		for(j=1;j<=n;++j)
		{
			mp[i][j]=getchar();//读入
			if(mp[i][j]=='\n')mp[i][j]=getchar();
      		//因为getchar()会读入换行符，所以要特判，不读入换行符。
		}
	}
	for(i=1;i<=n;++i)//枚举第一个顶点的横坐标
	{
		for(j=1;j<=n;++j)//枚举第一个顶点的纵坐标
		{
			if(mp[i][j]!='B')//判断是否被Bob的牛占领 
			{
				for(k=i;k<=n;++k)//枚举第二个顶点的横坐标，从i开始，避免重复计算
				{
					for(l=j;l<=n;++l)//枚举第二个顶点的纵坐标，从j开始，避免重复计算
					{
						if(mp[k][l]!='B')//判断是否被Bob的牛占领 
						{
							cnt=0;//记录有多少个顶点被John的牛占领
							x=k-l+j;//第三个顶点的横坐标 
							y=l+k-i;//第三个顶点的纵坐标 
							x2=i-l+j;//第四个顶点的横坐标 
							y2=j+k-i;//第四个顶点的纵坐标 
							if(check(x,y)&&check(x2,y2))//判断是否在地图范围内 
							{ 
								if(mp[x][y]!='B'&&mp[x2][y2]!='B')//判断是否被Bob的牛占领 
								{ 
									mp(i,j);//统计这个顶点是否被John的牛占领，详见第三行define 
									mp(k,l)//统计这个顶点是否被John的牛占领 
									mp(x,y);//统计这个顶点是否被John的牛占领 
									mp(x2,y2);//统计这个顶点是否被John的牛占领
                                    //因为Bessie可以成为顶点之一，所以三个点符合要求就可以(4-1=3)。
									if(cnt>=3)ans=max(ans,area(i,j,k,l));//更新答案 
								}
							}
						}
					}
				}
			}
		}
	}
	printf("%d",ans);//输出答案 
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意
给定一个二维棋盘可以添加一个 FarmerJohn 的点，使得所有 FarmerJohn 的点构成的正方形最大，但不能添加在 Bob 的点上。
### 题目分析
观察数据范围 $2 \le N \le 100$。

发现 $N$ 并不大，可以考虑暴力求解。

由于是正方形，我们知道正方形有如下两条性质：

- 所有角都是直角（$90°$）。

- 四条边都相等。

于是我们可以通过三个点确定一个正方形。

我们的枚举思路就是：

- 枚举两个点，根据这条线段可以确定整个正方形有两种可能。

- 对于每种正方形，我们可以通过已知的两个点算出四个点的位置，只需要满足有一个点原本就属于 FarmerJohn，且另一个点不属于 Bob，我们可以将点添加在那里构成正方形。

- 对于每个可以构成的正方形，如果最开始枚举的两点为$( x_1, y_1 )$ 和 $(x_2, y_2)$，根据勾股定理，面积为 $S = (x_1 - x_2) ^ 2 + (y_1 - y_2) ^2$。

特殊地，答案初始值不能设为负无穷，我们将其设为 $0$，这样如果无法形成正方形，答案为 $0$。

---

## 作者：zyc____ (赞：2)

## USACO06NOV Big Square

### 进入正题

### 题意

农夫约翰想要在他的正方形农场上建造一座正方形大牛棚。他讨厌在他的农场中砍树，想找一个能够让他在空旷无树的地方修建牛棚的地方。我们假定，他的农场划分成 N x N 的方格。输入数据中包括有树的方格的列表。你的任务是计算并输出，在他的农场中，不需要砍树却能够修建的最大正方形牛棚。牛棚的边必须和水平轴或者垂直轴平行。

### 分析

枚举矩形的两个端点（同一条边上的），然后求出剩下的两个端点，判断是否合法，并更新答案。

### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,n,mp[110][110],ans;
struct data{
    int x,y;
}a[110*110];
int cmp(data a,data b)
{
    return a.x<b.x||a.x==b.x&&a.y<b.y;
}
int pow(int x)
{
    return x*x;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        char s[110];
        scanf("%s",s+1);
        for (int j=1;j<=n;j++) {
            if (s[j]=='B') mp[i][j]=-1;
            if (s[j]=='J') a[++cnt].x=i,a[cnt].y=j,mp[i][j]=1;
        }
    }
    for (int x1=1;x1<=n;x1++)
        for (int y1=1;y1<=n;y1++)
            for (int x2=x1+1;x2<=n;x2++)
                for (int y2=1;y2<=y1;y2++){
                    if (mp[x1][y1]==-1||mp[x2][y2]==-1) continue;
                    int cnt=0;
                    int len1=abs(x1-x2); int len2=abs(y1-y2);
                    int x3=x1+len2; int y3=y1+len1;
                    int x4=x2+len2; int y4=y2+len1;
                    if (x3<1||y3<1||x3>n||y3>n) continue;
                    if (x4<1||y4<1||x4>n||y4>n) continue;
                    if (mp[x4][y4]==-1||mp[x3][y3]==-1) continue;
                    cnt=mp[x1][y1]+mp[x2][y2]+mp[x3][y3]+mp[x4][y4];
                    if (cnt<3) continue;
                    ans=max(ans,pow(len1)+pow(len2));
                }
    printf("%d\n",ans);
}
```


---

## 作者：tzyt (赞：1)

update：2022/4/17 增加了博客地址和题目链接

[博客](https://ttzytt.com/2021/11/P2867/)中观看体验更佳

[题目链接](https://www.luogu.com.cn/problem/P2867)

# 1：理解题意：
给定一个 $N\times N$ 的区域，并且这个区域内有两类点，J 类与 B 类。现在让你在区域中添加一个J类点（也可以不添加，并且添加时不能添加到已经存在 B 类点的地方），然后找出最大的由 J 类点构成的正方形。

# 2：分析
## 2.1：概括
因为数据较小 $(N<100)$，并且我们可以通过一条J边来确定正方形的剩下两条边，所以可以尝试通过枚举J边，并且加以判断的方法找到最大的正方形。
## 2.2：一点点数学
假设我们通过两点 $P_1$ 和 $P_2$ 确定了一条直线，并且 $P_1$ 的纵坐标总是比 $P_2$ 高，那么我们可以画出下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/e02vw603.png)
可是我们如何计算出 $P_3$ 和 $P_4$ 的坐标呢？


首先通过观察，我们可以发现图中的四个三角形都是全等的，我们只要计算出三角形的长直角边和短直角边的长度（或者说是两个不同的直角边，只是在这种特殊情况下，长边和短边的位置是图中的样式），再加上一个偏移量，就可以得到 $P_3$ 和 $P_4$ 的坐标了。

三角形的长直角边: 
$$L_{\triangle}= b_1 - b_2$$

三角形的短直角边: 
$$S_{\triangle}= a_1 - a_2$$

通过观察，我们可以从上面两个式子得出 $P_3$ 和 $P_4$ 的坐标
$$P_3 = (a_2 + L_{\triangle}, b_2 - S_{\triangle})$$
$$P_4 = (a_1 + L_{\triangle}, b_1 - S_{\triangle})$$

除了现在图中的样式，通过 $P_1P_2$ 这条直线还能确定另一种正方形：

![](https://cdn.luogu.com.cn/upload/image_hosting/15u65844.png)

当然，我们还是可以通过刚刚的方法得到 $P_5$ 和 $P_6$ 的坐标。我们刚刚是在一个偏移量的基础上加上或是减去三角形的两个不同边的长度 $(L_{\triangle}$ 以及 $S_{\triangle})$ 来得到 $P_3$ 和 $P_4$ 的坐标，通过观察，我们可以发现只要在偏移量上进行相反的操作，就可以得到 $P_5$ 和 $P_6$ 的坐标了。

$$P_5 = (a_2 - L_{\triangle}, b_2 + S_{\triangle})$$
$$P_6 = (a_1 - L_{\triangle}, b_1 + S_{\triangle})$$

因为此需要我们计算的是正方形的面积，所以我们可以用以下方法计算出面积：
$$\text{area} = (a_1 - a_2)^2 + (b_1 - b_2)^2$$

## 2.3：程序思路
通过刚刚的方法，我们已经能够得到 $P_{3\sim6}$ 的坐标了，接下来我们需要判断通过一条边确定的这两个正方形是否合法。

因为我们可以自由的放置一个 J 点，所以整个正方形中可以只有三个现成的 J 点，当然，这一个 J 点必须放置在没有被占用的点上。

因此只要以 $P_{1\sim4}$ 组成的正方形符合:

$$(P_3 \in \text{J} \quad \text{AND}\quad P_4 \notin \text{B})\ \text{OR} \ (P_3 \notin \text{B} \quad\text{AND}\quad P_4 \in \text{J})$$
注：J 表示的是 J 类点的集合，B 表示的是 B 类点的集合

我们就可以说这一个正方形是合法的。由 $P_{1,2,5,6}$ 组成的正方形同理

# 3：程序实现以及程序的改进过程
## 3.1：第一次尝试
想到思路之后迅速的打出了代码，结果两个点 T 了。。。

[提交](https://www.luogu.com.cn/record/63664093)
```cpp
#include <bits/stdc++.h>
using namespace std;
int mp[120][120];
#define debug false
struct node
{
    int x, y;
};
vector<node> jc; //J类点

int n;
void input()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char temps[110];
        scanf("%s", temps);
        for (int j = 0; temps[j]; j++)
        {
            if (temps[j] == 'J')
            {
                mp[i][j] = 1;
                jc.push_back(node{i, j});
            }
            else if (temps[j] == 'B')
            {
                mp[i][j] = -1;
            }
            else if (temps[j] == '*')
            {
                mp[i][j] = 0;
            }
        }
    }
}

int main()
{
    input();
    int ans = 0;
    for (auto t1 : jc)
    {
        for (auto t2 : jc)
        {
            if (t1.x == t2.x && t1.y == t2.y)
            {
                continue;
            }
            if (debug)
                printf("1x %d 1y %d 2x %d 2y %d\n", t1.x, t1.y, t2.x, t2.y);
            node p3, p4;
            node p1 = t1, p2 = t2;
            if (p1.y < p2.y)
            {
                swap(p1, p2);
            }
            p3.x = (p2.x + (p1.y - p2.y));
            p3.y = (p2.y - (p1.x - p2.x));

            p4.x = (p1.x + (p1.y - p2.y));
            p4.y = (p1.y - (p1.x - p2.x));
            if (debug)
                printf("3x %d 3y %d 4x %d 4y %d\n", p3.x, p3.y, p4.x, p4.y);

            if (p3.x >= 0 && p3.y >= 0 && p4.x >= 0 && p4.y >= 0 && p3.x < n && p3.y < n && p4.x < n && p4.y < n)
            {
                if ((mp[p3.x][p3.y] == 1 && mp[p4.x][p4.y] != -1) || (mp[p3.x][p3.y] != -1 && mp[p4.x][p4.y] == 1))
                {
                    ans = max(ans, ((p1.y - t2.y) * (p1.y - p2.y) + (p1.x - p2.x) * (p1.x - p2.x)));
                }
            }
            p3.x = (p2.x - (p1.y - p2.y));
            p3.y = (p2.y + (p1.x - p2.x));
            p4.x = (p1.x - (p1.y - p2.y));
            p4.y = (p1.y + (p1.x - p2.x));
            if (p3.x >= 0 && p3.y >= 0 && p4.x >= 0 && p4.y >= 0 && p3.x < n && p3.y < n && p4.x < n && p4.y < n)
            {
                if ((mp[p3.x][p3.y] == 1 && mp[p4.x][p4.y] != -1) || (mp[p3.x][p3.y] != -1 && mp[p4.x][p4.y] == 1))
                {
                    ans = max(ans, ((p1.y - t2.y) * (p1.y - t2.y) + (p1.x - p2.x) * (p1.x - p2.x)));
                }
            }
        }
    }
    printf("%d", ans);
    system("pause");
}
```
## 3.2：第二次尝试
我们可以发现这个代码做了大量的无用计算，因为我们假设了 $P_1$ 的纵坐标总是比 $P_2$ 高，所以在程序中通过一个判断来确保我们的假设成立。
```cpp
            if (p1.y < p2.y)
            {
                swap(p1, p2);
            }
```
我们实现枚举边的方法是用两个循环枚举所有的J点，所以会有重复枚举的情况（比如 $P_1$ 和 $P_2$ 实际相同，但是换了个顺序）。对于这样的情况，我们完全可以直接跳过这次循环来节省时间。

所以我们可以把代码改为:
```cpp
        if ((p1.x == p2.x && p1.y == p2.y) || (p1.y < p2.y))
        {
            continue;
        }
```
这样进入后续判断正方形合法性环节的点就都符合我们的假设了，也减少了之前的重复计算。

再仔细分析程序，我们可以发现，其实在循环内部只是做了判断正方形合法性的工作，如果在枚举的时候我们发现一个正方形的面积比我们目前得到的答案还要小，那么就没必要继续判断合法性了，直接跳过就可以了。

所以我们可以把代码改为：

```cpp
            if ((p1.x == p2.x && p1.y == p2.y) || (p1.y < p2.y) || (((p1.y - p2.y) * (p1.y - p2.y) + (p1.x - p2.x) * (p1.x - p2.x)) <= ans))
            {
                continue;
            }
```

经过这次改进，我们就可以愉快的 AC 了：

[AC提交记录](https://www.luogu.com.cn/record/63664242)


完整代码以及注释如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int mp[120][120];
#define debug false
struct node
{
    int x, y;
};
vector<node> jc; //J类点的集合

int n;
void input()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char temps[110];
        scanf("%s", temps);
        for (int j = 0; temps[j]; j++)
        {
            if (temps[j] == 'J')
            {
                mp[i][j] = 1;
                jc.push_back(node{i, j});
            }
            else if (temps[j] == 'B')
            {
                mp[i][j] = -1;
            }
            else if (temps[j] == '*')
            {
                mp[i][j] = 0;
            }
        }
    }
}

int main()
{
    input();
    int ans = 0;
    int cnt = 0;
    for (auto p1 : jc)
    {
        for (auto p2 : jc)//通过枚举两个点来实现对于边的枚举
        {

            if ((p1.x == p2.x && p1.y == p2.y) || (p1.y < p2.y) || (((p1.y - p2.y) * (p1.y - p2.y) + (p1.x - p2.x) * (p1.x - p2.x)) <= ans))
            {
                // printf("temp area %d ans^2 %d ans %d\n", (t1.y - p2.y) * (t1.y - p2.y) + (t1.x - p2.x) * (t1.x - p2.x),ans*ans,ans);
                continue;
            }
            cnt++;
            if (debug)
                printf("1x %d 1y %d 2x %d 2y %d\n", p1.x, p1.y, p2.x, p2.y);
            //通过一条边确定的第一种正方形
            node p3;
            p3.x = (p2.x + (p1.y - p2.y));
            p3.y = (p2.y - (p1.x - p2.x));
            node p4;
            p4.x = (p1.x + (p1.y - p2.y));
            p4.y = (p1.y - (p1.x - p2.x));
            if (debug)
                printf("3x %d 3y %d 4x %d 4y %d\n", p3.x, p3.y, p4.x, p4.y);
            if (p3.x >= 0 && p3.y >= 0 && p4.x >= 0 && p4.y >= 0 && p3.x < n && p3.y < n && p4.x < n && p4.y < n)//判断合法性
            {
                if ((mp[p3.x][p3.y] == 1 && mp[p4.x][p4.y] != -1) || (mp[p3.x][p3.y] != -1 && mp[p4.x][p4.y] == 1))
                {
                    ans = max(ans, (p1.y - p2.y) * (p1.y - p2.y) + (p1.x - p2.x) * (p1.x - p2.x));
                }
            }
            //通过一条边确定的第二种正方形
            p3.x = (p2.x - (p1.y - p2.y));
            p3.y = (p2.y + (p1.x - p2.x));

            p4.x = (p1.x - (p1.y - p2.y));
            p4.y = (p1.y + (p1.x - p2.x));
            if (p3.x >= 0 && p3.y >= 0 && p4.x >= 0 && p4.y >= 0 && p3.x < n && p3.y < n && p4.x < n && p4.y < n)//判断合法性
            {
                if ((mp[p3.x][p3.y] == 1 && mp[p4.x][p4.y] != -1) || (mp[p3.x][p3.y] != -1 && mp[p4.x][p4.y] == 1))
                {
                    ans = max(ans, (p1.y - p2.y) * (p1.y - p2.y) + (p1.x - p2.x) * (p1.x - p2.x));
                }
            }
        }
    }
    printf("%d\n", ans);
    if (debug)
        printf("%d", cnt);
    system("pause");
}


---

## 作者：Otomachi_Una_ (赞：1)

### 题意
给你一个 $n\times n$ 的方阵，把一个 `*` 换成 `J`。求以 `J` 为顶点的正方形面积最大值。

### 思路
考虑到 $n$ 比较小，我们可以进行暴力枚举。因为在原方阵中想要围成 `J` 正方形，必须有三个顶点已经是 `J`，且剩下那个顶点不能是 `B`。

有两个顶点就可以确定一个正方形了，读者可以试一下画个图，枚举其余两个顶点的位置。

上代码：

```cpp
#include<iostream>
using namespace std;
const int MAXN=1e2+5;
int n,m,ans=0;
char c[MAXN][MAXN];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>c[i][j];
	for(int x1=1;x1<=n;x1++)
		for(int y1=1;y1<=n;y1++)
			if(c[x1][y1]=='J')
				for(int x2=1;x2<=n;x2++)
					for(int y2=1;y2<=n;y2++)
						if(c[x2][y2]=='J'){
							int x3=x2-y2+y1,y3=y2+x2-x1;
							int x4=x1-y2+y1,y4=y1+x2-x1;
							if((1<=x3&&x3<=n&&1<=x4&&x4<=n&&1<=y3&&y3<=n&&1<=y4&&y4<=n)
							&&(c[x3][y3]=='J'||c[x4][y4]=='J')
							&&(c[x3][y3]!='B'&&c[x4][y4]!='B'))
								ans=max(ans,(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
						} 
	cout<<ans;
	return 0;
}
```


---

## 作者：sinsop90 (赞：1)

简要题意:

一个 $n\times n$ 的范围, 有两种点, 一种属于 John, 另一种属于 Bob。

现在让你在 $n\times n$ 的范围中选一个点, 让这个点属于 John, 使得 John 拥有的点组成的正方形的面积最大。

我们考虑一个思路, 枚举两个属于 John 的点, 考虑以这两个点为顶点的正方形可取的最大面积。

我们发现, 对于两个点, 我们可以确定以这两个点为顶点的正方形的另外两个点的位置。

而包括这两个点的正方形有三种情况, 如下图:

![](https://s2.loli.net/2021/12/10/Kg8rHJBVe7TLaDu.png)

A, B 是我们已经确定的点, C, D 是以 A, B 为顶点的正方形的另外两个顶点。

注意到左边的正方形和右边的正方形边长均为 AB, 而中间的正方形对角线为 AB, 因此对于 A, B 这两个点, 他们可以组成的正方形最大面积就是左边和右边的正方形的面积。

于是, 我们现在来求解另一个子问题:如何求出 C, D 点的坐标。

让我们翻开初二的数学课本, 我们发现了我们可爱的全等三角形, 如下图:

![](https://s2.loli.net/2021/12/10/PktTSV4UmLlGcrZ.png)

若 AE 垂直于 EF, CF 也垂直于 EF, 四边形 ABCD 为正方形, 我们可以得出三角形 AEB 全等于 三角形 BFC。

因此 AE = BF, EB = CF, 由于 A, B 的坐标是已知的, 我们可以顺理成章地得出 C 的坐标了, 类似的, D 也如此。

因此代码如下:

```
#include <bits/stdc++.h>
#define maxn 105
using namespace std;
int n, tot, m, ans = 0;
char mp[maxn][maxn];
struct cows {
	int x, y;
}e[maxn * maxn];
bool cmp(cows a, cows b) {
	return a.x < b.x;
}
bool check(int x, int y, int xx, int yy) {//判断是否合法
	if(!(x >= 1 && x <= n && xx >= 1 && xx <= n && yy >= 1 && yy <= m && y >= 1 && y <= m)) return false;
	if(mp[x][y] == 'B' || mp[xx][yy] == 'B') return false;
	if(mp[x][y] == 'J' || mp[xx][yy] == 'J') return true;
	return false;
}
int main() {
	scanf("%d", &n);
	m = n;
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= m;j++) {
			cin >> mp[i][j];
			if(mp[i][j] == 'J') {
				e[++tot].x = i;
				e[tot].y = j;
			}
		}
	}
	sort(e + 1, e + 1 + tot, cmp);//可以对x进行排序, 以免重复计算
	for(int i = 1;i <= tot;i++) {
		for(int j = i + 1;j <= tot;j++) {
			int x = e[i].x, y = e[i].y, xx = e[j].x, yy = e[j].y;
			int bx = xx - x, by = yy - y;
			int ax = xx - by, ay = yy + bx, aax = x - by, aay = y + bx;
			if(check(ax, ay, aax, aay)) ans = max(ans, bx * bx + by * by);
			ax = xx + by, ay = yy - bx, aax = x + by, aay = y - bx;
			if(check(ax, ay, aax, aay)) ans = max(ans, bx * bx + by * by);
		}
	}
	cout << ans << endl;
}
```


---

## 作者：LittleAcbg (赞：0)

对一个正方形 $ABCD$，假设 $A\rightarrow B\rightarrow C\rightarrow D$ 是顺时针转一圈的顺序，如果我们知道了 $A$ 的坐标 $(x,y)$ 和向量 $\overrightarrow{AB}=(dx,dy)$，我们就可以唯一地确定正方形的位置，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/cd207vu4.png)

命题：对于每个正方形，必定有至少一条边 $(dx,dy)$ 满足 $dx\ge0,dy>0$。

证明如下：观察上图，四条边对应的向量分别为 $(dx,dy),(dy,-dx),(-dx,-dy),(-dy,dx)$，显然其中必定有一个满足 $dx>0,dy>0$。唯一特殊的情况就是边平行于边界的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/8nd03x5z.png)

如图，如果边平行于边界，上面的一条 $(0,a)$ 的边满足 $dx=0,dy>0$。

由此我们知道，所有正方形都有至少一条边 $(dx,dy)$ 满足 $dx\ge0,dy>0$。

我们考虑枚举正方形，那么我们只需要枚举一条边 $(dx,dy)$ 和一个顶点的坐标 $(x,y)$，并且只需要考虑 $dx\ge0,dy>0$ 的情况即可。

题解的第一张图中已经提供了四个顶点的计算方式。更多细节见代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 109;
int n,num,ans;
bool legal;
char mp[N][N];
void work(int x, int y) // 对顶点 (x,y) 进行操作
{
    if (x < 1 || x > n || y < 1 || y > n) // 边界外，不合法
    {
        legal = 0;
        return;
    }
    if (mp[x][y] == 'B') legal = 0; // 有对方，不合法
    else if (mp[x][y] == 'J') ++num; // 统计我方奶牛
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> mp[i][j]; // 输入 n*n 字符矩阵
    for (int dx = 0; dx <= n - 1; ++dx)
        for (int dy = 1; dy <= n - 1; ++dy)
        // 枚举向量 (dx,dy)
        {
            // 最优性剪枝
            if (dx * dx + dy * dy <= ans) continue;
            for (int x = 1; x <= n; ++x)
                for (int y = 1; y <= n; ++y) // 枚举一个顶点 (x,y)
                {
                    num = 0;
                    legal = 1;
                    // num 表示该正方形顶点上 J 的数量
                    // legal 表示该正方形是否有顶点在边界外/有B
                    work(x, y);
                    work(x + dx, y + dy);
                    work(x + dx + dy, y + dy - dx);
                    work(x + dy, y - dx);
                    if (legal && num >= 3)
                        ans = max(ans, dx * dx + dy * dy);
                    // 只要合法并且有至少三个我方奶牛就更新答案
                    // 有四个时就是合法正方形
                    // 有三个时放 Bessie
                }
        }
    cout << ans << endl;
    return 0;
}
```

---

