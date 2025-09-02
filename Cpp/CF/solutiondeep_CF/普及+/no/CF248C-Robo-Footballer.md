# 题目信息

# Robo-Footballer

## 题目描述

It's a beautiful April day and Wallace is playing football with his friends. But his friends do not know that Wallace actually stayed home with Gromit and sent them his robotic self instead. Robo-Wallace has several advantages over the other guys. For example, he can hit the ball directly to the specified point. And yet, the notion of a giveaway is foreign to him. The combination of these features makes the Robo-Wallace the perfect footballer — as soon as the ball gets to him, he can just aim and hit the goal. He followed this tactics in the first half of the match, but he hit the goal rarely. The opposing team has a very good goalkeeper who catches most of the balls that fly directly into the goal. But Robo-Wallace is a quick thinker, he realized that he can cheat the goalkeeper. After all, they are playing in a football box with solid walls. Robo-Wallace can kick the ball to the other side, then the goalkeeper will not try to catch the ball. Then, if the ball bounces off the wall and flies into the goal, the goal will at last be scored.

Your task is to help Robo-Wallace to detect a spot on the wall of the football box, to which the robot should kick the ball, so that the ball bounces once and only once off this wall and goes straight to the goal. In the first half of the match Robo-Wallace got a ball in the head and was severely hit. As a result, some of the schemes have been damaged. Because of the damage, Robo-Wallace can only aim to his right wall (Robo-Wallace is standing with his face to the opposing team's goal).

The football box is rectangular. Let's introduce a two-dimensional coordinate system so that point ( $ 0 $ , $ 0 $ ) lies in the lower left corner of the field, if you look at the box above. Robo-Wallace is playing for the team, whose goal is to the right. It is an improvised football field, so the gate of Robo-Wallace's rivals may be not in the middle of the left wall.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF248C/c1dbb8ae6934c9cbdf30e94b8dc5e9e775d1d074.png)In the given coordinate system you are given:

- $ y_{1} $ , $ y_{2} $ — the $ y $ -coordinates of the side pillars of the goalposts of robo-Wallace's opponents;
- $ y_{w} $ — the $ y $ -coordinate of the wall to which Robo-Wallace is aiming;
- $ x_{b} $ , $ y_{b} $ — the coordinates of the ball's position when it is hit;
- $ r $ — the radius of the ball.

A goal is scored when the center of the ball crosses the $ OY $ axis in the given coordinate system between ( $ 0 $ , $ y_{1} $ ) and ( $ 0 $ , $ y_{2} $ ). The ball moves along a straight line. The ball's hit on the wall is perfectly elastic (the ball does not shrink from the hit), the angle of incidence equals the angle of reflection. If the ball bounces off the wall not to the goal, that is, if it hits the other wall or the goal post, then the opposing team catches the ball and Robo-Wallace starts looking for miscalculation and gets dysfunctional. Such an outcome, if possible, should be avoided. We assume that the ball touches an object, if the distance from the center of the ball to the object is no greater than the ball radius $ r $ .

## 说明/提示

Note that in the first and third samples other correct values of abscissa $ x_{w} $ are also possible.

## 样例 #1

### 输入

```
4 10 13 10 3 1
```

### 输出

```
4.3750000000
```

## 样例 #2

### 输入

```
1 4 6 2 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 10 15 17 9 2
```

### 输出

```
11.3333333333
```

# AI分析结果

### 题目内容
# 机器足球运动员

## 题目描述
这是一个美好的四月天，华莱士正在和他的朋友们踢足球。但他的朋友们不知道，华莱士实际上和格罗米特待在家里，派了他的机器人替身去踢球。机器华莱士相较于其他人有一些优势。例如，他可以将球直接踢到指定的点。而且，他完全没有传球的概念。这些特点的结合，让机器华莱士成为了完美的足球运动员——只要球到了他脚下，他就能瞄准并射门。在比赛的上半场，他遵循这个策略，但很少能射中球门。对方球队有一个非常出色的守门员，能接住大多数直接射向球门的球。但机器华莱士思维敏捷，他意识到自己可以骗过守门员。毕竟，他们是在一个有坚固墙壁的足球场地踢球。机器华莱士可以把球踢到另一侧，这样守门员就不会试图去接球。然后，如果球从墙上反弹后飞进了球门，那么就能得分了。

你的任务是帮助机器华莱士找到足球场地墙壁上的一个点，机器人应该把球踢向这个点，使得球反弹一次且仅反弹一次，然后直接飞进对方球门。在上半场比赛中，机器华莱士头部被球击中，受到了严重撞击。结果，一些程序受损。由于受损，机器华莱士只能瞄准他右边的墙（机器华莱士正面向对方球队的球门站立）。

足球场地是长方形的。让我们引入一个二维坐标系，这样点 $(0, 0)$ 位于场地的左下角（当你从上方看这个场地时）。机器华莱士所在球队的球门在右边。这是一个临时足球场，所以机器华莱士对手的球门可能不在左边墙的正中间。

在给定的坐标系中，你会得到以下信息：
 - $y_1$，$y_2$ —— 机器华莱士对手球门门柱的 $y$ 坐标；
 - $y_w$ —— 机器华莱士瞄准的墙壁的 $y$ 坐标；
 - $x_b$，$y_b$ —— 球被踢时球的位置坐标；
 - $r$ —— 球的半径。

当球的中心在给定坐标系中穿过 $y$ 轴上 $(0, y_1)$ 和 $(0, y_2)$ 之间时，就算进球得分。球沿直线运动。球与墙壁的碰撞是完全弹性的（球碰撞后不会变形），入射角等于反射角。如果球从墙上反弹后没有飞向球门，也就是说，如果它击中了另一堵墙或门柱，那么对方球队就会接住球，机器华莱士就会开始寻找计算失误的地方，然后出现故障。如果可能的话，应该避免这种结果。我们假设，如果球的中心到物体的距离不大于球的半径 $r$，则球接触到了该物体。

## 说明/提示
注意，在第一个和第三个样例中，横坐标 $x_w$ 的其他正确值也是可能的。

## 样例 #1
### 输入
```
4 10 13 10 3 1
```
### 输出
```
4.3750000000
```

## 样例 #2
### 输入
```
1 4 6 2 2 1
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
3 10 15 17 9 2
```
### 输出
```
11.3333333333
```

### 算法分类
数学

### 题解综合分析与结论
两道题解思路相似，均通过相似三角形的性质来计算球与墙反弹时圆心的横坐标 $x_w$，并通过点到直线距离公式或相似三角形比例关系判断球是否能在不触碰 $y$ 轴上特定位置的前提下射进球门。

### 题解1
 - **星级**：4星
 - **关键亮点**：思路清晰，先将圆与点的碰撞问题转化为点与点的碰撞问题，通过相似三角形得出横坐标 $x_w$ 的计算公式，再利用点到直线距离公式判断是否有解。
 - **个人心得**：无

```cpp
#include<bits/stdc++.h>
using namespace std;
double y1, y2, yw, xb, yb, r, xw;
signed main(){
    scanf("%lf%lf%lf%lf%lf%lf",&y1,&y2,&yw,&xb,&yb,&r);
    double a = yw - y1 - 2.0 * r,b = yw - yb - r,x = a * xb / (a + b),l = sqrt(x * x + a * a),ans =x * (y2 - y1 - r) / l;
    if(r > ans)puts("-1");
    else printf("%.10lf\n",x);
    return 0;
}
```
核心实现思想：根据相似三角形得出横坐标 $x_w$ 的计算公式 `a * xb / (a + b)`，通过点到直线距离公式的变形计算距离 `x * (y2 - y1 - r) / l`，并与半径 `r` 比较判断是否有解。

### 题解2
 - **星级**：4星
 - **关键亮点**：简洁明了，通过相似三角形比例关系直接求解横坐标 $x_w$，并利用相似三角形对应边成比例判断球是否能射进球门。
 - **个人心得**：无

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;

int main()
{
    double y1,y2,y,xx,yy,r;
    cin>>y1>>y2>>y>>xx>>yy>>r;
    double a=y-y1-2*r,b=y-yy-r,x=a*xx/(a+b),l=sqrt(x*x+a*a),ans=x*(y2-y1-r)/l;
    if(r-ans>0)
		cout<<"-1"<<endl;
    else 
		printf("%.10lf",x);
}
```
核心实现思想：与题解1类似，通过相似三角形计算横坐标 `a*xx/(a + b)`，利用相似三角形比例关系计算距离 `x*(y2 - y1 - r)/l` 并与半径比较判断是否有解。

### 最优关键思路或技巧
利用相似三角形的性质来计算球反弹点的横坐标，并通过点到直线距离公式或相似三角形比例关系判断球能否成功射进球门，将实际问题转化为数学几何问题求解。

### 拓展
此类题目属于几何计算与判断类型，相似套路为将实际场景中的物体运动、碰撞等问题转化为几何图形的性质和关系进行求解。类似题目可关注平面几何中关于图形位置关系、运动轨迹、碰撞判断等方面的问题。

### 洛谷相似题目推荐
 - [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)：涉及几何图形的构建与计算。
 - [P2678 [NOIP2015 普及组] 跳石头](https://www.luogu.com.cn/problem/P2678)：需要通过数学方法分析跳跃距离与石头位置关系。
 - [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)：利用数学方法在区间内寻找最值。 

---
处理用时：54.99秒