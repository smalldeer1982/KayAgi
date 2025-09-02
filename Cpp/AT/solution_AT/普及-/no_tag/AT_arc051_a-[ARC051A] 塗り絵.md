# [ARC051A] 塗り絵

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc051/tasks/arc051_a

白く塗られた二次元平面を考えます。

まず、$ (x_1,\ y_1) $ からの距離が $ r $ 以下の部分を赤く塗ります。

そのあと、 $ x_2\ ≦\ x\ ≦\ x_3,\ y_2\ ≦\ y\ ≦\ y_3 $ を満たす $ (x,\ y) $ を青く塗ります。

なお、赤く塗られた後、更に青く塗られた部分は紫色になるとします。

赤く塗られた部分と青く塗られた部分が存在するかどうかをそれぞれ判定してください。

## 说明/提示

### 制約

- $ -100\ ≦\ x_1,\ y_1\ ≦\ 100 $
- $ -100\ ≦\ x_2\ <\ x_3\ ≦\ 100 $
- $ -100\ ≦\ y_2\ <\ y_3\ ≦\ 100 $
- $ 1\ ≦\ r\ ≦\ 100 $
- 与えられる数は全て整数である。

### Sample Explanation 1

!\[A\_img1\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis1.png) 赤い部分も青い部分もあります

### Sample Explanation 2

!\[A\_img2\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis2.png) 赤く塗られた部分は存在しません。

### Sample Explanation 3

!\[A\_img3\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis3.png) 青く塗られた部分は存在しません。

### Sample Explanation 4

!\[A\_img4\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis4.png) 円と長方形が重なっていますが赤く塗られた部分も青く塗られた部分も存在します。

### Sample Explanation 5

!\[A\_img5\](https://arc051.contest.atcoder.jp/img/arc/051/tonarinokyakuhayokukakikuukyakuda/axis5.png)

## 样例 #1

### 输入

```
-1 -1 2
2 3 4 5```

### 输出

```
YES
YES```

## 样例 #2

### 输入

```
0 1 1
-2 0 4 3```

### 输出

```
NO
YES```

## 样例 #3

### 输入

```
0 0 5
-2 -2 2 1```

### 输出

```
YES
NO```

## 样例 #4

### 输入

```
0 0 2
0 0 4 4```

### 输出

```
YES
YES```

## 样例 #5

### 输入

```
0 0 5
-4 -4 4 4```

### 输出

```
YES
YES```

# 题解

## 作者：nbtngnllmd (赞：2)

### 题目大意：

 已知有一个半径为 $r$ 的圆，其原点坐标为$ (x,y) $,给出一个矩形，其左下角的坐标$(a,b)$,右下角的坐标的为$(c,d)$，圆将被涂成红色，矩形将被涂成蓝色，一个区域如果被涂成红色和蓝色，就会变成紫色。

 求是否会有蓝色和红色区域。

### 分析时间:

 首先我们可以先判断是否有红色区域。如果圆被矩形完全覆盖，即近似求出矩形的内切圆，如果不符合，则可以直接输出NO，我们设圆的外接四边形四个顶点坐标为$s1,s2,s3,s4$。
 
 $ s1 $=$ y +r $,$ s2 = x - r $,$ s3 = x+r $,   $s4=y-r$。
 
如下图：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT1867/a87a2acfa58b6eb060f246fe521732bdbe361df3.png)



接下来再来求出蓝色区域，众所周知圆外一点到圆心的最小距离为圆的半径 $r$ ,即如果矩形内任意一点到圆心的距离如果大于半径则证明一定会有蓝色区域。

 矩形左下角的坐标 $ (a,b) $ ,左上角 $ (a,d)  $,右下角$ (c,b) $。这里用到了一个数学公式（勾股定理）求直角三角形斜边长：两个直角边边长的平方加起来等于斜边长的平方。
矩形四个顶点到圆心的距离是$ x1,x2,x3,x4 $。
 分别求出四个顶点到圆心的距离如果任意一条边到圆心的距离大于（不能包含等于）半径，输出YES，反之输出NO 。

如下图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT1867/781ddcfa265c5ae304977fa358e26eaedeec58f8.png)

### 易错点：
 如果直接判断矩形右上角的坐标是否会超出圆的范围，样例会给出HACK数据，这时就只能考虑点到半径的距离了如图下：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT1867/9776ff894e149bc1ff6b34ae14a3bcd55b4a89fc.png)

##  $ AC code $


------------

```cpp

#include<bits/stdc++.h>

using namespace std;

int main(){
    double x,y,r;cin>>x>>y>>r;
    double a,b,c,d;cin>>a>>b>>c>>d;
    double x1 =sqrt(pow(abs(x-a),2)+pow(abs(d-y),2)),x2 = sqrt(pow(abs(c-x),2)+pow(abs(d-y),2)),x3 = sqrt(pow(abs(x-c),2)+pow(abs(y-b),2)),x4 = sqrt(pow(abs(x-a),2)+pow(abs(y-b),2));//x1,x2,x3,x4为四点到圆心距离
    int s1 = y + r ,s2 = x - r ,s3 = x + r , s4 = y - r ; //s1,s2,s3,s4为圆的外接四边形的四个xy坐标
    if(s1<=d&&s2>=a&&s4>=b&&s3<=c ) cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
    if(x1>r||x2>r||x3>r||x4>r){
        cout<<"YES"<<endl;
    }
    else cout<<"NO"<<endl;
    return 0;
}
  
```



---

## 作者：Kvaratskhelia (赞：1)

**题目大意**

有一个被涂成白色的平面，首先将圆心坐标为 $(x_1,y_1)$ ，半径为 $r$ 的圆涂成红色，再将左上角坐标为 $(x_1,y_1)$ ，右上角坐标为 $(x_1,y_1)$ 的矩形涂成蓝色，如果一个区域被涂了红色和蓝色，这里就会变成紫色。

试判断涂色后是否还存在红色或蓝色区域。

**分析**

首先分析这个圆是否在矩形内。对于一个圆来说，最小的能过完全覆盖这个圆的矩形就是它的圆外接正方形，即以圆心为中心，直径为对角线的正方形，此时可以推断出这个正方形的左上角，右下角顶点坐标分别是 $(x_1-r,y_1-r)$ ， $(x_1+r,y_1+r)$ 。然后只要判断一下题目给出的矩形是否有部分在正方形外即可。

然后是分析矩形是否在圆内，只要矩形的顶点都在圆内，那么这个圆心也一定在圆内，所以求出顶点和圆心的距离再和半径比较即可。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,r,a,b,c,d;
int main()
{	
	cin>>x>>y>>r;
	cin>>a>>b>>c>>d;
	if(x-r<a||x+r>c||y-r<b||y+r>d) cout<<"YES";
	else cout<<"NO";
	cout<<endl;
	if(max((a-x)*(a-x),(c-x)*(c-x))+max((b-y)*(b-y),(d-y)*(d-y))>r*r) cout<<"YES";
	else cout<<"NO";
	cout<<endl;
	return 0;
}
```


---

## 作者：luo_shen (赞：0)

**题意**  
有一个红色的圆和一个蓝色的矩形，二者相覆盖的部分会变色。求最后是否剩余红色的部分和是否剩余蓝色的部分。

**分析**  
你可以尝试画一个和圆重合的矩形，很明显，这是不可能的。~~如果你画出来了，那还叫矩形吗~~。所以只会有三种情况：
- 有红色的部分，没有蓝色的部分
- 没有红色的部分，有蓝色的部分
- 蓝色的部分和红色的部分都有。  

故我们只需判断矩形是否包含圆和圆是否包含矩形即可。

**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int x_1,y_1,r,x_2,y_2,x_3,y_3;//x_1,y_1为圆心坐标，x_2,y_2为矩形左下角坐标（翻译错了），x_3,y_3为矩形右上角坐标
int main(){
    cin>>x_1>>y_1>>r;
    cin>>x_2>>y_2>>x_3>>y_3;
    if(max((x_2-x_1)*(x_2-x_1),(x_3-x_1)*(x_3-x_1))+max((y_2-y_1)*(y_2-y_1),(y_3-y_1)*(y_3-y_1))<=r*r){//若矩形上距圆心最远的点到圆心的距离小于半径，则该矩形被圆包含
        puts("YES");
        puts("NO");
    }
    else if(x_2<=x_1-r&&x_3>=x_1+r&&y_2<=y_1-r&&y_3>=y_1+r){
        //若矩形四边均与圆相离，则该矩形包含该圆
        puts("NO");
        puts("YES");
    }
    else{//矩形和圆没有相互包含
        puts("YES");
        puts("YES");
    }
    return 0;
}
```
完结撒花

---

