# [USACO18JAN] Blocked Billboard II B

## 题目描述

Bessie the cow used to have such a nice view from her barn, looking across road at a set of two billboards advertising delicious looking cow feed. Unfortunately, one of these billboards has recently been updated so it now advertises "Farmer Larry's Lawnmowers". Bessie is not a fan of lawnmowers since their only purpose, as far as she can tell, is cutting back the grass in her field that she finds so tasty (if you haven't noticed, much of Bessie's thought process revolves around food).

Fortunately, the remaining cow feed billboard is situated in front of the lawnmower billboard, potentially obscuring it.

Bessie, determined to remove the offensive lawnmower billboard completely from her view, hatches a risky plan. She plans to steal a large rectangular tarp from the barn and sneak out late at night to cover the remaining portion of the lawnmower billboard, so that she can no longer see any part of it.

Given the locations of the two billboards, please help Bessie compute the minimum area of the tarp she will need. Since the only tarps available in the barn are rectangular in size, Bessie observes that she may conceivably need a tarp whose area is slightly larger than the exposed area of the lawnmower billboard, as illustrated in the example below. The tarp may only be placed such that its sides are parallel to those of the other billboards (i.e., it cannot be "tilted"). 

## 说明/提示

### Sample Explanation 1

Here, the cow feed billboard obscures the lower right corner of the lawnmower billboard, but this doesn't really help, since Bessie still needs to use a tarp whose size is as large as the entire lawnmower billboard. 

## 样例 #1

### 输入

```
2 1 7 4
5 -1 10 3```

### 输出

```
15```

# 题解

## 作者：cff_0102 (赞：21)

怎么题解区都是暴力，来点不一样的做法。

第二个矩形在第一个矩形上方，那么它覆盖的有效度只有以下可能：

1. 第二个矩形对结果没有任何贡献，题面中的大布仍然要盖住整个第一个矩形。

![](https://cdn.luogu.com.cn/upload/image_hosting/cz7m5bvo.png)

2. 第二个矩形成功盖住了第一个矩形的一条边，大布只需要盖住剩下的面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/79si6ce6.png)

3. 第二个矩形很大，能直接盖住第一个矩形。那么此时不需要大布，那就输出 `0`。

![](https://cdn.luogu.com.cn/upload/image_hosting/qxv50qt9.png)

可以看到，大布面积不需要达到第一个矩形那么大的可能性比较小，可以直接从后到前判断当前两个矩形的状态，然后输出对应的答案。

### 1. 第二个矩形完全包含第一个矩形

题面中没有给第二个矩形的坐标标号，那就仿照第一个矩形的坐标把输入的四个变量命名成 $x_1',y_1',x_2',y_2'$ 好了。

此时知道第一个矩形（小矩形）两条竖线的 $x$ 坐标分别是 $x_1,x_2$，第二个矩形（大矩形）两条竖线的 $x$ 坐标分别是 $x_1',x_2'$，设 $x_1<x_2,x_1'<x_2'$，那么根据上面的图片可以看到此时必须满足 $x_1'\le x_1<x_2\le x_2'$，同理，还要满足 $y_1'\le y_1<y_2\le y_2'$。如果这两个条件同时满足，那么就是第二个矩形完全包含第一个矩形的情况，输出 $0$。

```cpp
if(x1_<=x1 && x2<=x2_ && y1_<=y1 && y2<=y2_) cout<<0,exit(0);
```

### 2. 第二个矩形能够完全包含第一个矩形的一条边

有如下四种可能。

![](https://cdn.luogu.com.cn/upload/image_hosting/7mlysgny.png)

其实这四种差不多，分析完第一种，就能同理得出剩下三种可能的判断方法和答案。

分析第一种，可以发现它要求第二个矩形的上下两边要夹住第一个矩形的上下两边，即 $y_1'\le y_1<y_2\le y_2'$。接下来看图可得，第二个矩形的左边那条边在第一个矩形左右两边之间，而第二个矩形右边那条边在第一个矩形右边那条边的右边。所以此时 $x_1<x_1'<x_2\le x_2'$。

判断出现在两个矩形属于这种情况之后，还需要输出大布的最小面积。此时大布需要完全盖住露出来的那个绿色区域。这个区域左边那条边是第一个矩形左边那条边，即 $x$ 坐标是 $x_1$ 的那条边，右边那条边是第二个矩形左边那条边，即 $x$ 坐标是 $x_1'$ 的那条边，上面那条边和下面那条边跟第一个矩形一样，即它们 $y$ 坐标分别为 $y_2$ 和 $y_1$。最后输出的答案应该是 $(x_1'-x_1)\times(y_2-y_1)$。

剩下三个也可以同理推出：

- 当 $x_1'\le x_1<x_2\le x_2',y_1<y_1'<y_2\le y_2'$，答案为 $(x_2-x_1)\times(y_1'-y_1)$；
- 当 $x_1'\le x_1<x_2'<x_2,y_1'\le y_1<y_2\le y_2'$，答案为 $(x_2-x_2')\times(y_2-y_1)$；
- 当 $x_1'\le x_1<x_2\le x_2',y_1'\le y_1<y_2'<y_2$，答案为 $(x_2-x_1)\times(y_2-y_2')$。

```cpp
if(x1<x1_ && x1_<x2 && x2<=x2_ && y1_<=y1 && y2<=y2_) cout<<(x1_-x1)*(y2-y1),exit(0);
if(x1_<=x1 && x2<=x2_ && y1<y1_ && y1_<y2 && y2<=y2_) cout<<(x2-x1)*(y1_-y1),exit(0);
if(x1_<=x1 && x1<x2_ && x2_<x2 && y1_<=y1 && y2<=y2_) cout<<(x2-x2_)*(y2-y1),exit(0);
if(x1_<=x1 && x2<=x2_ && y1_<=y1 && y1<y2_ && y2_<y2) cout<<(x2-x1)*(y2-y2_),exit(0);
```

### 3. 上面两种情况都不是

那就是刚开始讨论的第一种情况，答案是第一个矩形的面积，即 $(x_2-x_1)\times(y_2-y_1)$。

```cpp
cout<<(x2-x1)*(y2-y1);
```

### 完整代码：

- 还有什么需要注意的？

1. 由题面中“... are the coordinates of the **lower-left and upper-right corners** of the ...”可以看出，本题已经默认了 $x_1<x_2$，剩下的变量也一样。但是有的题目并没有给你排好序，需要注意一下。
2. `y0,y1,yn,j0,j1,jn` 是 `cmath` 头文件的函数。如果要避免变量名冲突，可以给 `y1` 改个名字或者只 `#include<iostream>`，而不 `#include<bits/stdc++.h>`。

```cpp
#include<iostream>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int x1,y1,x2,y2,x1_,y1_,x2_,y2_;
	cin>>x1>>y1>>x2>>y2>>x1_>>y1_>>x2_>>y2_;
	if(x1_<=x1 && x2<=x2_ && y1_<=y1 && y2<=y2_)cout<<0,exit(0);
	if(x1<x1_ && x1_<x2 && x2<=x2_ && y1_<=y1 && y2<=y2_)cout<<(x1_-x1)*(y2-y1),exit(0);
	if(x1_<=x1 && x2<=x2_ && y1<y1_ && y1_<y2 && y2<=y2_)cout<<(x2-x1)*(y1_-y1),exit(0);
	if(x1_<=x1 && x1<x2_ && x2_<x2 && y1_<=y1 && y2<=y2_)cout<<(x2-x2_)*(y2-y1),exit(0);
	if(x1_<=x1 && x2<=x2_ && y1_<=y1 && y1<y2_ && y2_<y2)cout<<(x2-x1)*(y2-y2_),exit(0);
	cout<<(x2-x1)*(y2-y1);
	return 0;
}
```

相较于平方复杂度的暴力，这份 $O(1)$ 代码的 Pascal 版本[获得了本题的最优解](https://www.luogu.com.cn/record/143190186)。

---

## 作者：qw1234321 (赞：5)

#### 一眼，暴力。

坐标范围挺小，可以直接暴力求解，把割草机广告坐标全染色为 $1$，饲料广告设染色为 $2$。

然后暴力寻找未被盖到的坐标的最大最小值。

最后直接用暴力求到的左上角和右下角两个点的坐标计算面积即可。

贴个部分代码：

```cpp
const int N = 2e3 + 10, INF = 1e9;
int s[2][4];
int g[N][N];
//初始化，最小值初始化为正无穷,最大值初始化为负无穷 
int x1 = INF, y1 = INF, x2 = -INF, y2 = -INF;

int main(){
    for (int i = 0; i < 2; i++) for (int j = 0; j < 4; j++) cin >> s[i][j];
    for (int k = 0; k < 2; k++){
        for (int i = s[k][0]; i < s[k][2]; i++){
            for (int j = s[k][1]; j < s[k][3]; j++){
                g[i][j] = k + 1;//把割草机广告坐标全染色为 1，饲料广告染色为 2
            }
        }
    }
    //寻找未被盖到的坐标的最大最小值
    for (int i = s[0][0]; i < s[0][2]; i++){
        for (int j = s[0][1]; j < s[0][3]; j++){
            if (g[i][j] == 1){
                x1 = min(x1, i);
                x2 = max(x2, i);
                y1 = min(y1, j);
                y2 = max(y2, j);
            }
        }  
    }
    //计算面积 
    if (x2 >= x1 && y2 >= y1) cout << (x2 - x1 + 1) * (y2 - y1 + 1);
    else cout << 0;
```

RE 撒花！

那究竟是为什么 RE 呢？发现在用到的数组下标 $i$ 也许是负数，$j$ 同理。所以吧 $i,j$ 同时加上 $1000$ 就行啦！

这样 AC 代码就很简单了，请读者自行在原 RE 的代码上改改，思考思考。(~~好像都不用思考耶~~)

---

## 作者：Silent1019 (赞：4)

## 思路

#### 坐标的数据范围在 $-1000$ 到 $1000$ 内，很容易想到直接暴力的方法。

那么可以用二维数组 $vis$ 存有哪些点割草机广告牌是暴露在外的，再进行暴力找到最左上角点 $(x,y)$，即所有 $vis[x][y]$ 为真时，$x$ 的最小值和 $y$ 的最小值组成的点。同理找到最右下角点。

最后就可以直接通过左上角点和右下角点计算防水布最小的面积了。

## 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a1,a2,b1,b2,c1,c2,d1,d2;
bool vis[2005][2005];
int mx1,my1,mx2,my2;
int main()
{
	scanf("%d%d%d%d",&a1,&b1,&c1,&d1);
	scanf("%d%d%d%d",&a2,&b2,&c2,&d2);
	for(int i=a1+1;i<=c1;i++)
		for(int j=b1+1;j<=d1;j++)
			vis[i+1000][j+1000]=true;
	for(int i=a2+1;i<=c2;i++)
		for(int j=b2+1;j<=d2;j++)
			vis[i+1000][j+1000]=false;
        //暴力处理割草机广告牌暴露的点
	mx1=2001; my1=2001; mx2=-1; my2=-1;
	for(int i=0;i<=2000;i++)
		for(int j=0;j<=2000;j++)
			if(vis[i][j]) mx1=min(mx1,i),my1=min(my1,j);
        //暴力找出左上角点
	for(int i=0;i<=2000;i++)
		for(int j=0;j<=2000;j++)
			if(vis[i][j]) mx2=max(mx2,i),my2=max(my2,j);
        //暴力找出右上角点
	if(mx1==2001&&my1==2001&&mx2==-1&&my2==-1) printf("0\n");
	else printf("%d\n",(mx2-mx1+1)*(my2-my1+1));
	return 0;
}
```

---

## 作者：crzcqh (赞：2)

## 思路：

All coordinates are in the range $-1000$ to $+1000$.

也就是说 $|n|\le 1000$，那么 $O(n^2)$ 刚好可以过，容易想到暴力模拟。用一个数组记录，将饲料和除草机广告的矩阵打上不同的标记，最后 $n^2$ 遍历找出矩阵能贴的的最靠左上的左上角和最靠右下的右下角，输出时算出面积即可。

注意：

- $-1000\le |n|\le 1000$，如果单存这样做会出现数组越界的情况，所以可以加上 $1000$ 作为下标。

- 最后要特判，不然会 WA。

## CODE

```cpp
#include<bits/stdc++.h> 
#define s 1000
using namespace std;
int sa1,sb1,sa2,sb2,ea1,eb1,ea2,eb2; 
int a1=INT_MAX,b1=INT_MAX,a2=-1,b2=-1;
int f[2005][2005];
int main(){
	cin>>sa1>>sb1>>sa2>>sb2>>ea1>>eb1>>ea2>>eb2;
	//标记 
	for(int i=sa1+1;i<=sa2;i++)
		for(int j=sb1+1;j<=sb2;j++)
			f[i+s][j+s]=1; // 加 s 防止负数 RE 
	for(int i=ea1+1;i<=ea2;i++)
		for(int j=eb1+1;j<=eb2;j++)
			f[i+s][j+s]=0;
	//遍历 
	for(int i=0;i<=s*2;i++) // 0 为 -1000，2000 为 1000 
		for(int j=0;j<=s*2;j++)
			if(f[i][j]==1){
				a1=min(a1,i),b1=min(b1,j);
			}  
	for(int i=0;i<=s*2;i++) // 0 为 -1000，2000 为 1000 
		for(int j=0;j<=s*2;j++)
			if(f[i][j]==1){
				a2=max(a2,i),b2=max(b2,j);//这里括号内改成a2/b2 
			}  
	if(a1==INT_MAX&&b1==INT_MAX&&a2==-1&&b2==-1) cout<<0;//这里b1和a2调换位置 ,||换成&& 
	else cout<<(a2-a1+1)*(b2-b1+1);//加else 
	return 0;
}
```





---

## 作者：WydnksqhbD (赞：2)

# [P1696 [USACO18JAN] Blocked Billboard II B](https://www.luogu.com.cn/problem/P1696) 题解
## 题意
现有 $2$ 个矩形 $A,B$，用 $B$ 盖住一部分 $A$，问剩下的面积为多少？
## 思路
首先看数据范围：
$$-1000\le x_1,x_2,x_3,x_4,y_1,y_2,y_3,y_4\le 1000$$
于是我们可以上暴力。

创建一个二维数组，长宽均为 $2005$。

首先将 $A$ 盖住的赋值为 $1$，$B$ 盖住的赋值为 $2$。注意这里有可能将已赋值为 $1$ 的地方改为 $2$。

接下来将整个图形扫一遍，设现在扫到了 $(i,j)$。（数组下标，从 $1$ 开始）

+ 若该点为 $1$，那么就是没有被盖住的。所以刷新 $\text{ans}_1,\text{ans}_2,\text{ans}_3,\text{ans}_4$。（这是什么？记录左上角和右下角的端点在哪个位置）
+ 否则该点要么没有，要么已经被 $B$ 给盖住了。不用做任何事。

最后输出 $(\text{ans}_2-\text{ans}_1+1)\times(\text{ans}_4-\text{ans}_3+1)$ 即可。

代码如下：

```cpp
#include<cstdio>
using namespace std;
int x1,y1,x2,y2,x3,y3,x4,y4;
int ans1=-1000,ans2=1000,ans3=-1000,ans4=1000;
int a[2005][2005];
int max(int x,int y){return x>y?x:y;}
int min(int x,int y){return x<y?x:y;}
int main()
{
	scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
	for(int i=x1+1;i<=x2;i++)
	{
		for(int j=y1+1;j<=y2;j++)
		{
			a[i+1000][j+1000]=1;
		}
	}
	for(int i=x3+1;i<=x4;i++)
	{
		for(int j=y3+1;j<=y4;j++)
		{
			a[i+1000][j+1000]=2;
		}
	}
	int ans1=2010,ans2=-2010,ans3=2010,ans4=-2010;
	for(int i=0;i<=2000;i++)
	{
		for(int j=0;j<=2000;j++)
		{
			if(a[i][j]==1)
			{
				ans1=min(ans1,i);
				ans2=max(ans2,i);
				ans3=min(ans3,j);
				ans4=max(ans4,j);
			}
		}
	}
	if(ans2>=ans1&&ans4>=ans3)
	{
		printf("%d",(ans2-ans1+1)*(ans4-ans3+1));
	}
	else
	{
		printf("0");
	}
}
```
## 复杂度分析
时间复杂度 $O(n^2)$。这里 $n$ 是确定的，值为 $2000$。

空间复杂度 $O(n^2)$，因为开了一个二维数组。

**最后温馨提示：不要用万能头文件，不然会与函数名重复！**

**还要注意的是：你没用万能头，就得手打函数！**

[Accepted 记录](https://www.luogu.com.cn/record/143705349)

---

## 作者：sto__Liyhzh__orz (赞：2)

[传送门](https://www.luogu.com.cn/problem/P1696)

题意：

$A$ 矩形覆盖住了 $B$ 矩形，现在还要一个矩形 $C$ 完全覆盖 $B$ 矩形，求这个矩形面积的最小值。

思路：

这道题如果采用数学的方式的话是十分难做的（虽然可以做），

我们看一下数据范围：$-1000$ 到 $1000$，完全可以采用标记数组的方式模拟这道题。

首先将 $A$ 的面积标记上去，再把 $B$ 的面积标记一下。

那么我们只需要求一下 $A$ 和 $B$ 的横坐标和纵坐标的最小值和最大值，就可以求出大布的左下角和右上角了。

最后很容易就能求出 $C$ 的面积了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[2020][2020];
int main()
{
    int x1,y1,x2,y2,x3,y3,x4,y4;
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    for(int i=x1+1;i<=x2;i++)
    {
        for(int j=y1+1;j<=y2;j++)
        {
            f[i+1000][j+1000]=1;
        }
    }
    for(int i=x3+1;i<=x4;i++)
    {
        for(int j=y3+1;j<=y4;j++)
        {
            f[i+1000][j+1000]=2;
        }
    }
    int ans1=2010,ans2=-2010,ans3=2010,ans4=-2010;
    for(int i=0;i<=2000;i++)
    {
        for(int j=0;j<=2000;j++)
        {
            if(f[i][j]==1)
            {
                ans1=min(ans1,i);
                ans2=max(ans2,i);
                ans3=min(ans3,j);
                ans4=max(ans4,j);
            }
        }
    }
    if(ans2>=ans1&&ans4>=ans3)
    {
        printf("%d",(ans2-ans1+1)*(ans4-ans3+1));
    }
    else
    {
        printf("0");
    }
    return 0;
}
```

---

## 作者：sssscy_free_stdio (赞：2)

想知道为什么这题只有这么点提交……

这题其实就是将两个广告牌分别标出来，先标出割草机的广告牌，再标出牛饲料的广告牌，这样牛饲料的广告牌就会将割草机的广告牌挡住一部分。

然后就分枚举出现在割草机的广告牌还能看见的 $i$ 和 $j$ 的最小值和最大值，就可以求出大布的左上角和右下角，然后就可以求面积了。

注意，这里的坐标有可能是负数，因此要每个坐标加上 $1000$。

AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int ax,ay,bx,by,cx,cy,dx,dy,mi1=10000,mi2=10000,mx1=-10000,mx2=-10000,cnt[10010][10010];
int main(){
	scanf("%d%d%d%d%d%d%d%d",&ax,&ay,&bx,&by,&cx,&cy,&dx,&dy);
	ax+=1000,ay+=1000,bx+=1000,by+=1000,cx+=1000,cy+=1000,dx+=1000,dy+=1000;//每个坐标加上1000
	for(int i=ax+1;i<=bx;i++){
		for(int j=ay+1;j<=by;j++){
			cnt[i][j]=1;//标记割草机的广告牌
		}
	}for(int i=cx+1;i<=dx;i++){
		for(int j=cy+1;j<=dy;j++){
			cnt[i][j]=2;//标记牛饲料的广告牌
		}
	}for(int i=0;i<=2000;i++){
		for(int j=0;j<=2000;j++){
			if(cnt[i][j]==1){
				mi1=min(mi1,i),mi2=min(mi2,j),mx1=max(mx1,i),mx2=max(mx2,j);//求大布的左上角和右下角
			}
		}
	}printf("%d",mx1==-10000&&mx2==-10000&&mi1==10000&&mi2==10000?0:(mx1-mi1+1)*(mx2-mi2+1));
	return 0;
}
```

---

## 作者：_little_Cabbage_ (赞：1)

# P1696 [USACO18JAN] Blocked Billboard II B 题解

~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-cf1916b)~~

这是一道暴力水题。

我们可以先把割草机公告板覆盖的地方标记为 $1$，再把奶牛饲料公告板覆盖的地方标记为 $2$，然后看标记为 $1$ 的地方的左上角与右下角，最后计算面积即可。

但是，千万不要用 map 来标记，[后果](https://www.luogu.com.cn/record/142326826)。

AC 代码
```cpp
#include<bits/stdc++.h>
#define ge 1
#define liao 2
using namespace std;
int f[2020][2020];
int main()
{
	int x1,y1,x2,y2,x3,y3,x4,y4;
	cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
	for(int i=x1+1;i<=x2;i++)
	{
		for(int j=y1+1;j<=y2;j++)
		{
			f[i+1000][j+1000]=ge;
		}
	}
	for(int i=x3+1;i<=x4;i++)
	{
		for(int j=y3+1;j<=y4;j++)
		{
			f[i+1000][j+1000]=liao;
		}
	}
	int ans1=2010,ans2=-2010,ans3=2010,ans4=-2010;
	for(int i=0;i<=2000;i++)
	{
		for(int j=0;j<=2000;j++)
		{
			if(f[i][j]==ge)
			{
				ans1=min(ans1,i);
				ans2=max(ans2,i);
				ans3=min(ans3,j);
				ans4=max(ans4,j);
			}
		}
	}
	if(ans2>=ans1&&ans4>=ans3)
	{
		printf("%d",(ans2-ans1+1)*(ans4-ans3+1));
	}
	else
	{
		printf("0");
	}
}
```
[AC 记录](https://www.luogu.com.cn/record/142327211)

---

## 作者：wei2013 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P1696)
## 题目大意：
用一个**长方形**覆盖一个牌子，在这个牌子前面，还有一个牌子，问这个**长方形**的**面积**最少是多少。
## 思路
坐标在 $-1000$ 到 $1000$ 之内，那么就不需要任何优化，直接暴力就好了。

纯暴力寻找长方形四个角的位置最小在计算面积即可，特别的，题目中坐标有负数，那么实行起来很麻烦，我们最好是将这个坐标加 $1000$，这样无论如何都是正整数，同时呢数组也要开到 $2000$，以免 RE。
## code：
```
#include <bits/stdc++.h>
using namespace std;
bool flag[2005][2005];
int main(){
    int x1,x2,y1,y2,x3,y3,x4,y4;
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    for(int i=x1+1;i<=x2;i++){
    	for(int j=y1+1;j<=y2;j++){
    		flag[i+1000][j+1000]=1;
		}
	}
	for(int i=x3+1;i<=x4;i++){
    	for(int j=y3+1;j<=y4;j++){
    		flag[i+1000][j+1000]=0;
		}
	}
	int sx1=2000,sy1=2000,sx2=0,sy2=0;
	for(int i=0;i<=2000;i++){
		for(int j=0;j<=2000;j++){
			if(flag[i][j]){
				sx1=min(sx1,i);
				sy1=min(sy1,j);
			}
		}
	}
	for(int i=0;i<=2000;i++){
		for(int j=0;j<=2000;j++){
			if(flag[i][j]){
				sx2=max(sx2,i);
				sy2=max(sy2,j);
			}
		}
	}
	if(sx1==2000 && sy1==2000 && sx2==0 && sy2==0){
		cout<<0;
		return 0;
	}
	cout<<(sx2-sx1+1)*(sy2-sy1+1);	
    return 0;
}
```


望审核通过！

---

## 作者：Pyrf_uqcat (赞：1)

### 题意分析
题目中提到了广告牌以及矩阵大布进行遮盖，并不是那么好理解，所以我们换一种思维方式：把广告牌和布都当做长方形。

易懂的题意：已知长方形 $Y$ 覆盖了长方形 $X$，又有一个长方形 $Z$ 覆盖了长方形 $Y$，问长方形 $Z$ 的最小面积。
### 思路
输入格式的最后一句话告诉了我们**数据范围是 $-1000$ 到 $1000$ 以内**，范围小，首选**枚举**（也就是暴力）。反推一下，最后要求 $Z$ 的最小面积，求最小面积可以去寻找 $Z$ 的左上角点和右上角点，进行求值就可以了（找到点之后求值很简单，不说了）。
### 方法
**核心：标记数组**

把 $X$ 所占的点标成 $1$，$Y$ 所占的点标成 $2$。最后遍历找左上点和右下点，时间复杂度 $O(n^2)$。

但是，你以为就结束了吗？范围虽小，但是 $-1000$ 是负数，必 RE。所以，把所有数组下标都加上 $1000$，避免数组越界（产生负数）。

代码就不放了，考验大家动手打代码和思维能力（~~真正的防抄袭~~）。

---

## 作者：xzz_0611 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P1696)
# 分析
这道题很明显可以暴力。

我们可以先定义一个整形二维数组，把割草机广告所在的区域的值都改成 $1$，再把牛饲料广告所在的区域的值都改成 $2$，再找到值为 $1$ 的区域的左上角和右下角的下标，即可计算布所至少需要的面积。
# code
```cpp
#include<iostream>
using namespace std;
int color[2005][2005],ax1,ay1,ax2,ay2,bx1,by1,bx2,by2;
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>ax1>>ay1>>ax2>>ay2>>bx1>>by1>>bx2>>by2;
	ax1+=1000,ay1+=1000,ax2+=1000,ay2+=1000,bx1+=1000,by1+=1000,bx2+=1000,by2+=1000;
	//这几个坐标的只可能是负数，但是数组下标不能是负数，所以要将它们的值加上1000，使它们成为正数，否则会RE
	for(int i=ax1+1;i<=ax2;++i) for(int j=ay1+1;j<=ay2;++j) color[i][j]=1;
	for(int i=bx1+1;i<=bx2;++i) for(int j=by1+1;j<=by2;++j) color[i][j]=2;
	//覆盖数组的值
	int x1=2010,x2=0,y1=2010,y2=0;
	for(int i=0;i<=2000;i++)
		for(int j=0;j<=2000;j++)
			if(color[i][j]==1) {
				x1=min(x1,i);
				x2=max(x2,i);
				y1=min(y1,j);
				y2=max(y2,j);
			}
	//找到最上面、最下面、最左边、最右边的点
	if(x2>=x1&&y2>=y1) cout<<(x2-x1+1)*(y2-y1+1);
	else cout<<0;
	//上面这个if语句一定不能少了，因为在不需要添加布的时候x1>x2、y1>y2，所以此时(x2-x1+1)*(y2-y1+1)的结果会是负数，而实际的结果应该为0
	return 0;
}
```

---

## 作者：Lovely_Elaina (赞：0)

暴力枚举或分类讨论，提供时间复杂度为 $O(1)$ 的分讨代码。

---

首先通过对比大小得到矩形**左上端点和右下端点**。

### 暴力

因为坐标有负数，考虑从 $(-1001,-1001)$ 为原点建立新的平面直角坐标系进行计算，这样可以保证点全部位于第一象限（即 $x,y> 0$），方便使用二维数组存储。

然后先后遍历染色（可覆盖），默认 $0$，割草机广告牌的染成 $1$，另一个染成 $0$。

最后查找格子为 $1$ 的坐标最值。

大小为 $(\max x-\min x)\times (\max y -\min y)$。

### 分讨

- 可以被全部覆盖；
- 不可以全部覆盖：
	- 没被覆盖部分呈矩形；
    - 没被覆盖部分不呈矩形；
    - 没被覆盖部分呈多个矩形。
- 没被覆盖。

设割草机广告的左上角坐标为 $(gx_1,gy_1)$，右下角坐标为 $(gx_2,gy_2)$。

设牛饲料广告的左上角坐标为 $(nx_1,ny_1)$，右下角坐标为 $(nx_2,ny_2)$。

定义两个条件：

- 条件一：$nx_1\le gx_1\le gx_2 \le nx_2$ 且 $ny_1\ge gy_1\ge ny_2$ 或 $ny_1\ge gy_2\ge ny_2$；
- 条件二：$ny_1\ge gy_1\ge gy_2 \ge ny_2$ 且 $nx_1\le gx_1\le nx_2$ 或 $nx_1\le gx_2 \le nx_2$。

然后就能枚举出所有情况：

1. 当前仅当满足两个条件时，割草机广告被完全覆盖，易得此时不需要布。
2. 满足任意一个条件时，没被覆盖部分呈矩形。
3. 都不满足时，没背覆盖或没被覆盖部分不呈矩形或呈多个矩形，易得此时布需要覆盖全部的割草机广告。

```cpp
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;

int lx,ly,rx,ry;
int lx_,ly_,rx_,ry_;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> lx >> ly >> rx >> ry;
	cin >> lx_ >> ly_ >> rx_ >> ry_;

	if(lx > rx) swap(lx,rx);
	if(ly < ry) swap(ly,ry);
	if(lx_ > rx_) swap(lx_,rx_);
	if(ly_ < ry_) swap(ly_,ry_);

	if(lx_ <= lx && rx <= rx_ && ly_ >= ly && ry >= ry_){
		cout << 0 << endl;
		return 0;
	}

	if(lx_ <= lx && rx <= rx_ && (ly_ >= ly && ly >= ry_ || ly_ >= ry && ry >= ry_)){
		if(ly_ >= ly && ly >= ry_) cout << abs((rx-lx)*(ry_-ry)) << endl;
		else if(ly_ >= ry && ry >= ry_) cout << abs((rx-lx)*(ly-ly_)) << endl;
		else cout << abs((rx-lx)*(ry-ly)) << endl;
	}else if(ly_ >= ly && ry >= ry_ && (lx_ <= lx && lx <= rx_ || lx_ <= rx && rx <= rx_)){
		if(lx_ <= lx && lx <= rx_) cout << abs((rx-rx_)*(ry-ly)) << endl;
		else if(lx_ <= rx && rx <= rx_) cout << abs((lx_-lx)*(ry-ly)) << endl;
		else cout << abs((rx-lx)*(ry-ly)) << endl;
	}else cout << abs((rx-lx)*(ry-ly)) << endl;
	return 0;
}
```

但感觉上述代码多少有点繁琐，不妨把我们推导出来的东西优化一下。

- 条件一：$nx_1\le gx_1\le nx_2$；
- 条件二：$nx_1\le gx_2\le nx_2$；
- 条件三：$ny_1\ge gy_1\ge ny_2$；
- 条件四：$ny_1\ge gy_2\ge ny_2$。

然后就显而易见了。

- 全满足时为全覆盖；
- 满足一二或三四时，如果满足剩下条件任意一条，则未被覆盖部分呈矩形；
- 剩下为无用。

```cpp
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;

int lx,ly,rx,ry;
int lx_,ly_,rx_,ry_;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> lx >> ly >> rx >> ry;
	cin >> lx_ >> ly_ >> rx_ >> ry_;

	if(lx > rx) swap(lx,rx);
	if(ly < ry) swap(ly,ry);
	if(lx_ > rx_) swap(lx_,rx_);
	if(ly_ < ry_) swap(ly_,ry_);

	bool b1 = (lx_ <= lx && lx <= rx_);
	bool b2 = (lx_ <= rx && rx <= rx_);
	bool b3 = (ly_ >= ly && ly >= ry_);
	bool b4 = (ly_ >= ry && ry >= ry_);

	if(b1 && b2 && b3 && b4) cout << 0 << endl;
	else if(b1 && b2 && b3) cout << abs((rx-lx)*(ry_-ry)) << endl;
	else if(b1 && b2 && b4) cout << abs((rx-lx)*(ly-ly_)) << endl;
	else if(b3 && b4 && b1) cout << abs((rx-rx_)*(ry-ly)) << endl;
	else if(b3 && b4 && b2) cout << abs((lx_-lx)*(ry-ly)) << endl;
	else cout << abs((rx-lx)*(ry-ly)) << endl;
	return 0;
}
```

---

## 作者：LZYAC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P1696)
### 题目大意
一号矩形覆盖住了二号矩形，现在还要一个矩形完全覆盖二号矩形，求这个矩形面积的最小值。
### 思路
标记数组模拟，求出覆盖后矩形纵横坐标最小值和最大值，求出面积即可。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int x1,x2,y,y2,minx=114514,maxx=-114514,miny=114514,maxy=-114514;
int mp[2010][2010];
int main(){
	cin>>x1>>y>>x2>>y2;x1+=1000;y+=1000;x2+=1000;y2+=1000;
	for(int i=x1;i<x2;i++){
		for(int j=y;j<y2;j++){
			mp[i][j]=1;
		}
	}
	cin>>x1>>y>>x2>>y2;x1+=1000;y+=1000;x2+=1000;y2+=1000;
	for(int i=x1;i<x2;i++){
		for(int j=y;j<y2;j++){
			mp[i][j]=2;
		}
	}
	for(int i=0;i<2002;i++){
		for(int j=0;j<2002;j++){
			if(mp[i][j]==1){
				minx=min(minx,i);
				maxx=max(maxx,i);
				miny=min(miny,j);
				maxy=max(maxy,j);
			}
		}
	}
	if(maxx==-114514) puts("0");
	else if(minx==-114514) puts("0");
	else if(maxy==-114514) puts("0");
	else if(miny==-114514) puts("0");
	else printf("%d",(maxx-minx+1)*(maxy-miny+1));
	return 0;
}
```
### 提醒
有可能出现负数下标。所以要让所有坐标加上一个值来保证没有负数下标。

---

## 作者：xu_zhihao (赞：0)

### 题目理解：

   - 本题只用暴力枚举最小与最大没有被牛饲料广告覆盖的两种坐标，又因遮盖的布只能为矩形，所以只需要用公式 $(max_x-min_x+1)\times(max_y-min_y+1)$ 即可算出矩形大小（$max_x$ 为最大没有被牛饲料广告覆盖的横坐标，$min_x$ 为最小没有被牛饲料广告覆盖的横坐标，$max_y$ 为最大没有被牛饲料广告覆盖的纵坐标，$min_y$ 为最大没有被牛饲料广告覆盖的纵坐标。）还需要判断是否有原本所有割草机广告牌是否已被全部覆盖，如是输出 $0$，否则输出矩形大小。
   
   
### AC 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;

int flag[2020][2020];
int main()
{
	int x1,y1,x2,y2,x3,y3,x4,y4;
	cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
	for(int i=x1+1;i<=x2;i++)
	{
		for(int j=y1+1;j<=y2;j++)
		{
			flag[i+1000][j+1000]=1;
		}
	}
	
	for(int i=x3+1;i<=x4;i++)
	{
		for(int j=y3+1;j<=y4;j++)
		{
			flag[i+1000][j+1000]=2;
		}
	}
	int xmn=1e9,ymn=1e9,xmx=-1e9,ymx=-1e9;
	for(int i=0;i<=2010;i++)
	{
		for(int j=0;j<=2010;j++)
		{
			if(flag[i][j]==1)
			{
				xmn=min(xmn,i);
				xmx=max(xmx,i);
				ymn=min(ymn,j);
				ymx=max(ymx,j);
			}
		}
	}
	//cout<<xmn<<" "<<ymn<<endl<<xmx<<" "<<ymx<<endl;
	if(xmn==1e9 && ymn==1e9 && xmx==-1e9 && ymx==-1e9)
	{
		cout<<0;
		return 0;
	}
	 cout<<(xmx-xmn+1)*(ymx-ymn+1);
}
```



---

## 作者：yhx0322 (赞：0)

## Description
给你 $8$ 个整数 $(x_1,y_1),(x_2,y_2),(x_3,y_3),(x_4,y_4)$。分别代表了“割草机广告牌”、“奶牛饲养广告牌”的左上角与右下角的坐标。

“奶牛饲养广告牌”会将“割草机广告牌”遮住一部分，不过剩下的部分需要用一块长方形的布来完全遮住。

现在求长方形布的面积。

## Solution
由于坐标都在 $[-1000,1000]$ 的范围内，于是思考暴力。

做两次循环，每次分别将割草机广告牌所覆盖的位置标记为 `0`，将奶牛饲养广告牌所覆盖的位置标记为 `1`，这样剩余的 `0` 便是割草机广告牌剩下的面积。

然后循环最大范围，造出最小的左上角点和最大的右下角点，计算面积即可。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1000;
int f[(N << 1) + 20][(N << 1) + 20];
int a1, a2, b1, b2;
int main() {
    memset(f, 0x3f, sizeof(f));
    int x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    for (int i = x1 + 1; i <= x2; i++) {
        for (int j = y1 + 1; j <= y2; j++) {
            f[i + N - 10][j + N - 10] = 0;
        }
    }
    for (int i = x3 + 1; i <= x4; i++) {
        for (int j = y3 + 1; j <= y4; j++) {
            f[i + N - 10][j + N - 10] = 1;
        }
    }
    a1 = b1 = INT_MAX, a2 = b2 = INT_MIN;
    for (int i = 0; i <= (N << 1); i++) {
        for (int j = 0; j <= (N << 1); j++) {
            if (f[i][j] == 0) a1 = min(a1, i), b1 = min(b1, j);
        }
    }
    for (int i = 0; i <= (N << 1); i++) {
        for (int j = 0; j <= (N << 1); j++) {
            if (f[i][j] == 0) a2 = max(a2, i), b2 = max(b2, j);
        }
    }
    if (a1 == INT_MAX && b1 == INT_MAX && a2 == INT_MIN && b2 == INT_MIN) cout << 0 << '\n';
    else cout << (a2 - a1 + 1) * (b2 - b1 + 1) << '\n';
    return 0;
}
```

---

