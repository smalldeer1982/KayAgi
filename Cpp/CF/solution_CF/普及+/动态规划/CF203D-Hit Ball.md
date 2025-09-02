# Hit Ball

## 题目描述

瓦莱拉在体育场踢足球时，突然天降大雨。他躲进了看台下的走廊，躲避雨水。然而，他对足球的热爱丝毫未减，于是决定在走廊里练习踢球。在离门距离足够远的地方，他放好球并用力踢了出去。球在墙壁、天花板和地板上四处反弹，最后撞在了出口的门上。由于球是湿的，在门上留下了一个印记。瓦莱拉现在想确切地知道这个印记的位置。

我们可以将这个情景抽象化为一个几何模型。球可以被看作是空间中的一个点。走廊的门是一个位于平面 $xOz$ 上的矩形，其中左下角位于点 $(0,0,0)$，右上角位于点 $(a,0,b)$。走廊本身是一个垂直于 $y$ 轴无限延伸的长方体。在走廊中，地板是平面 $xOy$，而天花板则是一个平行于 $xOy$ 的平面，经过点 $(a,0,b)$。同样，一面墙是平面 $yOz$，另一面墙与此平面平行，经过点 $(a,0,b)$。

当球的 $y$ 坐标为 $0$ 时，我们称之为球撞到了门。因此，印记的坐标是 $(x_{0}, 0, z_{0})$，其中 $0 \le x_{0} \le a$ 且 $0 \le z_{0} \le b$。为了踢出球，瓦莱拉在距离门 $m$ 的位置将球放置在走廊中心点 $\left(\frac{a}{2}, m, \frac{b}{2}\right)$。击球后，球以速度 $(v_{x}, v_{y}, v_{z})$ 移动。也就是说，如果球当前在 $(x, y, z)$ 位置，那么一秒钟后它将移动到 $(x+v_{x}, y+v_{y}, z+v_{z})$。

请参考注释中的图像以获得更清晰的理解。

球在撞到天花板、地板或走廊墙壁时，会根据反射定律（入射角等于反射角）进行反弹。在这个问题中，我们运用了理想物理模型，也就是说不考虑空气阻力、摩擦力或能量损失。

## 样例 #1

### 输入

```
7 2 11
3 -11 2
```

### 输出

```
6.5000000000 2.0000000000
```

## 样例 #2

### 输入

```
7 2 11
4 -3 3
```

### 输出

```
4.1666666667 1.0000000000
```

# 题解

## 作者：ZLCT (赞：0)

# CF203D Hit Ball
~~一道很好的物理题~~
## 题目大意
给定一个正方体长宽高分别在 $x,y,z$ 轴上且长度分别为 $a,m,b$。现在有一个球（可看作质点）位于 $(\frac{a}{2},m,0)$ 点。现在在 $x,y,z$ 方向分别有初始速度 $v_x,v_y,v_z(v_y<0,v_z>0)$。问若球遵循反射规律（反射角等于入射角），则球 $y=0$ 时的 $x,z$ 坐标。\
$(1\le a,b,m\le100)$\
$(v_x,v_y,v_z\in\mathbb{Z})$
### *A Simple Observation*
由于我们发现 $v_y\ge1$ 而 $m\le100$，于是我们便可以模拟球的路径，算出每一次球改变方向后朝三个方向碰到墙壁的时间，取最小时间并进行运动。由于数据范围很小，所以是可以过的。
#### *code*
```cpp
#include<bits/stdc++.h>
using namespace std;
double x,y,z,vx,vy,vz;
bool flag=true;
struct node{
    double xi,yi,zi;
}ball;
struct hittime{
    int type;
    double tim;
}tx,ty,tz,tall;
hittime minl(hittime m1,hittime m2){
    if(m1.tim<m2.tim)return m1;
    return m2;
}
void gettime(){
    if(vx>0){
        tx.tim=(x-ball.xi)/vx;
    }else{
        if(vx==0)tx.tim=114514;
        else tx.tim=ball.xi/(-vx);
    }
    if(vz>0){
        tz.tim=(z-ball.zi)/vz;
    }else{
        if(vz==0)tz.tim=114514;
        else tz.tim=ball.zi/(-vz);
    }
    ty.tim=ball.yi/(-vy);
}
int main(){
    cin>>x>>z>>y;
    cin>>vx>>vy>>vz;
    tx.type=1;ty.type=2;tz.type=3;
    ball.xi=x/2.0;
    ball.yi=y;
    ball.zi=0;
    while(flag){
        gettime();
        tall=minl(tx,minl(ty,tz));
        if(tall.type==1){
            ball.xi+=vx*tall.tim;
            ball.yi+=vy*tall.tim;
            ball.zi+=vz*tall.tim;
            vx=-vx;
        }else if(tall.type==2){
            flag=0;
            ball.xi+=vx*tall.tim;
            ball.zi+=vz*tall.tim;
            ball.yi=0;
        }else{
            ball.xi+=vx*tall.tim;
            ball.yi+=vy*tall.tim;
            ball.zi+=vz*tall.tim;
            vz=-vz;
        }
    }
    printf("%.10lf %.10lf\n",ball.xi,ball.zi);
    return 0;
}

```
### *another solution*
因为最终球停止时间只受 $m,v_y$ 影响，所以我们可以求出球停止时的时刻。而我们将球的运动拆分为 $x,z$ 轴两个维度，对于每一个维度，只要运动的距离达到两倍物体长度限制就会回到原点。于是我们可以算出球运动 $t$ 秒后的有效位移。这样的复杂度为 $O(1)$，是此题最优解法。
#### *code by <u>ivan100sic</u>*
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cerr.tie(nullptr);

	ld a, b, m;
	cin >> a >> b >> m;
	ld vx, vy, vz;
	cin >> vx >> vy >> vz;

	ld t = -m / vy;

	ld x = a/2 + vx * t;
	ld z = 0 + vz * t;

	x = fmod(x, 2*a);
	if (x < 0)
		x += 2*a;
	if (x >= a)
		x = 2*a-x;

	z = fmod(z, 2*b);
	if (z < 0)
		z += 2*b;
	if (z >= b)
		z = 2*b-z;

	cout.precision(20);
	cout << fixed;

	cout << x << ' ' << z;
}
```
~~感觉这题通过人数少的原因一半在没翻译~~

---

