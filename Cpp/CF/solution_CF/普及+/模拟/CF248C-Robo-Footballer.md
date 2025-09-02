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

# 题解

## 作者：Call_me_Eric (赞：2)

### 题意

在平面直角坐标系上有一个半径为 $r$，圆心坐标为 $(x_b,y_b)$ 的球，直线 $y=y_w$ 为一面墙。

在 $y$ 轴上有一个 $[y_1,y_2]$ 的球门，$(0,y_1),(0,y_2)$ 是球门的两个立柱。

现在你希望寻找一个角度，使得这个球在墙上反弹且仅反弹一次并在不触碰 $y$ 轴上 $[0,y_1],[y_2,y_w]$位置的前提下将球射进门，我们认为球的圆心在 $(a,b)$ 时触碰到一个点 $(x,y)$ 当且仅当 $\sqrt{(x-a)^2+(y-b)^2}\le r$。

你只需要输出球与墙反弹时圆心的横坐标 $x_w$ 即可，如果有多个解输出任意一个，误差不允许超过 $10^{-8}$，无解输出 $-1$。

### 题解

纯纯数学平面几何题，与OI基本没什么关系。

看这篇题解之前请确保你已经完全读懂题意。

看下面这张图（做的不好勿喷）。

![ ](https://cdn.luogu.com.cn/upload/image_hosting/pojag3u9.png)

数学常用手段，希望这个圆不与 $(0,y_1),(0,y_2)$ 相碰撞（设 $M:(0,y_1),N:(0,y_2)$），那么就以这两个点分别做一个半径相等的圆，同时将 $y_w\gets y_w-r$，这样一个圆的移动就转化成了一个点的移动。

不难发现，如果希望存在一个路径满足条件，需要对于直线 $l_1:(y_w-y_a)x-x_wy+y_ax_w=0$，有 $\forall A\in l_1,MA>r,NA>r$。

不难发现，让 $MA>r$ 是很好办的，直接让 $y_a=y_1+r$ 即可。

然后看绿色和橙色的三角形，是不是有 $\triangle DEF\sim\triangle CEG$。

然后就有 $$\frac{EF}{DF}=\frac{EG}{GC}$$
$$\iff\frac{y_w-y_1-2\times r}{x_w}=\frac{y_w-y_b-r}{x_b-x_w}$$
$$\iff x_w=x_b\times\frac{y_w-y_1-2\times r}{2\times y_w-y_1-y_b-3\times r}$$
这个时候，$D:(0,y_a),E:(x_w,y_w)$ 都已经已知，可以算出直线 $DE$ 的解析式，即上文提到的 $l_1$。

接下来，根据点到直线距离公式，有
$$d=\frac{|-x_w\times y_2+y_a\times x_w|}{\sqrt{(y_w-y_a)^2+{x_w}^2}}$$
算出 $N$ 到 $l_1$ 的距离是 $d$。

然后只需要比一下 $d$ 与 $r$ 的关系即可，如果大于则有解，否则无解。

### 代码

~~~cpp
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
~~~

---

## 作者：开始新的记忆 (赞：2)

题目大意：给出发射点，问反弹之后能不能到达Y1-Y2之间。（QWQ原本就给了个代码不给过QWQ）

![](https://img-blog.csdnimg.cn/20190810105911964.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xhbnNoYW4xMTEx,size_16,color_FFFFFF,t_70)
PS：图片来源于网络

先求出X坐标，根据 两个角度的正切值成比例解出X值，然后利用这个X值，看这个红线的大三角与靠近y轴的小三角是相似的，利用T/(Y2-Y1-R)==X/(SQRT(X*X+U*U))解出T，U=yw-y1-2*r，判断T和R的关系即可。

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


---

