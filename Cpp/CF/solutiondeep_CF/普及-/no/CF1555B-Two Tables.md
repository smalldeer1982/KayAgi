# 题目信息

# Two Tables

## 题目描述

You have an axis-aligned rectangle room with width $ W $ and height $ H $ , so the lower left corner is in point $ (0, 0) $ and the upper right corner is in $ (W, H) $ .

There is a rectangular table standing in this room. The sides of the table are parallel to the walls, the lower left corner is in $ (x_1, y_1) $ , and the upper right corner in $ (x_2, y_2) $ .

You want to place another rectangular table in this room with width $ w $ and height $ h $ with the width of the table parallel to the width of the room.

The problem is that sometimes there is not enough space to place the second table without intersecting with the first one (there are no problems with tables touching, though).

You can't rotate any of the tables, but you can move the first table inside the room.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1555B/148c3af8c708a59f4665d57c0e4342daba4e07ae.png)Example of how you may move the first table.What is the minimum distance you should move the first table to free enough space for the second one?

## 说明/提示

The configuration of the first test case is shown in the picture. But the movement of the first table is not optimal. One of the optimal movement, for example, is to move the table by $ (0, -1) $ , so the lower left corner will move from $ (2, 1) $ to $ (2, 0) $ . Then you can place the second table at $ (0, 3)-(4, 5) $ .

In the second test case, there is no way to fit both tables in the room without intersecting.

In the third test case, you can move the first table by $ (0, 2) $ , so the lower left corner will move from $ (0, 3) $ to $ (0, 5) $ .

## 样例 #1

### 输入

```
5
8 5
2 1 7 4
4 2
5 4
2 2 5 4
3 3
1 8
0 3 1 6
1 5
8 1
3 0 6 1
5 1
8 10
4 5 7 8
8 5```

### 输出

```
1.000000000
-1
2.000000000
2.000000000
0.000000000```

# AI分析结果

### 题目内容
# 两张桌子

## 题目描述
你有一个坐标轴对齐的矩形房间，宽为 \(W\)，高为 \(H\)，所以左下角位于点 \((0, 0)\)，右上角位于 \((W, H)\)。

房间里有一张矩形桌子。桌子的边与墙壁平行，左下角位于 \((x_1, y_1)\)，右上角位于 \((x_2, y_2)\)。

你想在这个房间里再放置一张宽为 \(w\)，高为 \(h\) 的矩形桌子，且新桌子的宽与房间的宽平行。

问题是，有时没有足够的空间在不与第一张桌子相交的情况下放置第二张桌子（不过桌子接触没有问题）。

你不能旋转任何一张桌子，但你可以在房间内移动第一张桌子。

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1555B/148c3af8c708a59f4665d57c0e4342daba4e07ae.png) 这是一个你可以如何移动第一张桌子的示例。你应该将第一张桌子移动的最小距离是多少，才能为第二张桌子腾出足够的空间？

## 说明/提示
第一个测试用例的配置如图片所示。但第一张桌子的移动不是最优的。例如，一种最优移动是将桌子移动 \((0, -1)\)，这样左下角将从 \((2, 1)\) 移动到 \((2, 0)\)。然后你可以将第二张桌子放置在 \((0, 3)-(4, 5)\)。

在第二个测试用例中，没有办法在不相交的情况下将两张桌子都放入房间。

在第三个测试用例中，你可以将第一张桌子移动 \((0, 2)\)，这样左下角将从 \((0, 3)\) 移动到 \((0, 5)\)。

## 样例 #1
### 输入
```
5
8 5
2 1 7 4
4 2
5 4
2 2 5 4
3 3
1 8
0 3 1 6
1 5
8 1
3 0 6 1
5 1
8 10
4 5 7 8
8 5
```
### 输出
```
1.000000000
-1
2.000000000
2.000000000
0.000000000
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是基于枚举来解决问题。大家都意识到第一张桌子只能横向或纵向移动，且新桌子放在原桌子的上下左右四个方向的角落位置可能出现最优解。各题解的主要区别在于代码实现方式和细节处理。难点在于全面考虑各种情况，包括无解的情况以及如何准确计算移动距离。

### 题解1
 - **星级**：4星
 - **关键亮点**：思路清晰，简洁明了地列举出四种最优放置情况，代码实现简洁高效，通过 `min` 和 `max` 函数巧妙计算移动距离。
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=0;char c=getchar();while(c<'0'||c>'9')f|=c=='-',c=getchar();while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();return f?-x:x;}
signed main(){
	 int T=1; T=read();
	 while(T--){
		int W=read(),H=read();
		int x1=read(),y1=read(),x2=read(),y2=read();
		int w=read(),h=read();
		int ans=1000000000;
		int le=x2-x1,hi=y2-y1;
		if(w+le<=W){
			ans=min(ans,max(0,w-x1));
			ans=min(ans,max(0,x2-W+w));
		}
		if(h+hi<=H){
			ans=min(ans,max(0,h-y1));
			ans=min(ans,max(0,y2-H+h));
		}
		if(ans==1000000000) puts("-1");
		else printf("%lf\n",1.0*ans); 
				 
	 }
	return 0;
}
```
核心实现思想：先读取房间和两张桌子的尺寸信息，初始化最小移动距离 `ans` 为极大值。然后分别判断在宽度和高度方向上能否放置新桌子，如果可以，计算并更新最小移动距离。最后根据 `ans` 的值输出结果。

### 题解2
 - **星级**：4星
 - **关键亮点**：先判断无解情况，逻辑清晰。在判断有解时，分别处理水平和竖直方向的移动情况，代码结构清晰，可读性强。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
   int t, W, H, x1, y1, x2, y2, w, h, ansx, ansy;
   scanf("%d", &t);
   while(t--)
   {
      scanf("%d%d%d%d%d%d%d%d", &W, &H, &x1, &y1, &x2, &y2, &w, &h);
      if(x2-x1+w > W) ansx = -1;
      else if(x1 >= w || W-x2 >= w) ansx = 0;
      else ansx = min(w-x1, w+x2-W);
      // ansx 如果水平平移不能满足条件值为 -1，否则为水平平移的答案。
      if(y2-y1+h > H) ansy = -1;
      else if(y1 >= h || H-y2 >= h) ansy = 0;
      else ansy = min(h-y1, h+y2-H);
      // ansy 同理
      if(ansx == -1 & ansy == -1) puts("-1");
      else if(ansx == -1) printf("%d\n", ansy);
      else if(ansy == -1) printf("%d\n", ansx);
      else printf("%d\n", min(ansx, ansy));
   }
   return 0;
}
```
核心实现思想：先读取输入数据，然后分别判断水平和竖直方向上放置新桌子的情况。如果水平方向放不下，`ansx` 设为 `-1`，否则计算水平方向最小移动距离；竖直方向同理。最后根据 `ansx` 和 `ansy` 的值输出结果。

### 题解3
 - **星级**：4星
 - **关键亮点**：代码简洁，通过自定义 `read` 函数读取数据，在 `get` 函数中完成主要逻辑，将判断和计算过程整合在一起，思路清晰。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
void read(){}
template<typename _Tp,typename... _Tps>
void read(_Tp &x,_Tps &...Ar){
	x=0;char c=getchar();bool flag=0;
	while(c<'0'||c>'9')flag|=(c=='-'),c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(flag)x=-x;
	read(Ar...);
}
int a,b,x1,x2,y1,y2,a1,b1,a2,b2;
int get(){
	read(a,b,x1,y1,x2,y2,a2,b2);a1=x2-x1;b1=y2-y1;
	if(a1+a2>a&&b1+b2>b)return printf("-1\n"),0;
	int ans=0x3f3f3f3f;
	if(a1+a2<=a){
		if(x1>=a2||x2+a2<=a)ans=0;
		else ans=min(ans,min(a2-x1,x2+a2-a));
	}
	if(b1+b2<=b){
		if(y1>=b2||y2+b2<=b)ans=0;
		else ans=min(ans,min(b2-y1,y2+b2-b));
	}
	return printf("%d.000000000\n",ans),0;
}
int main(){
	int T;read(T);while(T--)get();
	return 0;
}
```
核心实现思想：通过自定义 `read` 函数读取房间和两张桌子的尺寸信息。在 `get` 函数中，先判断是否无解，若有解则分别在水平和竖直方向上判断能否放置新桌子并计算最小移动距离，最后输出结果。

### 最优关键思路或技巧
1. **枚举方向**：明确第一张桌子只能横向或纵向移动，新桌子放在原桌子上下左右四个方向角落位置枚举可能的最优解，全面考虑各种放置情况。
2. **边界判断**：仔细判断在不同方向上放置新桌子时，原桌子是否需要移动以及如何移动，通过 `min` 和 `max` 函数准确计算移动距离，同时注意判断无解的情况。

### 拓展思路
此类题目属于几何布局类问题，通常可通过分析物体在空间中的位置关系，利用枚举、贪心等策略解决。类似题目可能会改变物体形状（如圆形桌子）、增加物体数量或对移动方式加以限制，解题时需根据具体条件灵活运用枚举、贪心等方法，分析各种可能的布局情况。

### 相似知识点洛谷题目
1. [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过枚举每天的活动安排，计算并找出满足条件的结果，与本题枚举思路类似。
2. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：可通过枚举子段起点和终点来计算最大子段和，涉及对各种可能情况的分析，与本题全面考虑各种放置情况的思路有相通之处。
3. [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：通过枚举天数来判断小玉是否能到达对岸，同样是基于枚举思想解决问题。 

---
处理用时：99.93秒