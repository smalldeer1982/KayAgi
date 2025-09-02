# Bicycle Race

## 题目描述

Maria participates in a bicycle race.

The speedway takes place on the shores of Lake Lucerne, just repeating its contour. As you know, the lake shore consists only of straight sections, directed to the north, south, east or west.

Let's introduce a system of coordinates, directing the $ Ox $ axis from west to east, and the $ Oy $ axis from south to north. As a starting position of the race the southernmost point of the track is selected (and if there are several such points, the most western among them). The participants start the race, moving to the north. At all straight sections of the track, the participants travel in one of the four directions (north, south, east or west) and change the direction of movement only in bends between the straight sections. The participants, of course, never turn back, that is, they do not change the direction of movement from north to south or from east to west (or vice versa).

Maria is still young, so she does not feel confident at some turns. Namely, Maria feels insecure if at a failed or untimely turn, she gets into the water. In other words, Maria considers the turn dangerous if she immediately gets into the water if it is ignored.

Help Maria get ready for the competition — determine the number of dangerous turns on the track.

## 说明/提示

The first sample corresponds to the picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF659D/d384618c4de83253addcd24088af2096098ca28a.png)The picture shows that you can get in the water under unfortunate circumstances only at turn at the point $ (1,1) $ . Thus, the answer is $ 1 $ .

## 样例 #1

### 输入

```
6
0 0
0 1
1 1
1 2
2 2
2 0
0 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
16
1 1
1 5
3 5
3 7
2 7
2 9
6 9
6 7
5 7
5 3
4 3
4 4
3 4
3 2
5 2
5 1
1 1
```

### 输出

```
6
```

# 题解

## 作者：Seth (赞：4)

### 分析
根据题意分析可得，当遇到 $270 \degree$ 的拐角时就要转弯，求转弯几次也就是求在一个 $n$ 边形中，有几个 $270 \degree$ 的角。
多边形内角和公式为 $\theta=$ $180 \degree \times (n-2) $.

设在此多边形中有 $x$ 个 $270 \degree$ 的角，可以列出方程：

$90\degree$ $(n-x)+270\degree$ $x$ $=$ $180\degree(n-2)$.

解得 $x = \dfrac{n-4}{2}$.

### Code
```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	int n;
	cin>>n;
	cout<<(n - 4) / 2;
	return 0;
}
```


---

## 作者：引领天下 (赞：4)

竟然没有C++党题解？

数论楼下已证明过，我只是来一发代码

代码太简单就不写注释了

```cpp
#include <cstdio>
int n;
int main(void){
    scanf ("%d",&n);
    printf ("%d",(n-4)/2);
}
```

---

## 作者：Little_Jian (赞：3)

　　第一反应就是搞搞向量。
　　角度强制是直角，肯定有特殊性。
　　先画一个矩形，然后再在矩形上加点。
　　1. 在角上扣去一个矩形，会多出一个90° 和270° 的角。
　　2. 在边上扣去一个矩形，会多出一对90° 和270° 的角。
　　因为90° 和270° 成对出现，所以可以猜测这题的答案只和点数(n)有关，等于$$(n-4)/2$$。
　　证明：
　　设有$$x$$个90° 角，则有$$n-x$$个270° 角。
　　可以根据内角和列方程：$$90x+270(n-x)=180(n-2)$$
　　所以$$x=(n-4)/2$$
　　所以这题就能$$O(1)$$求了
``` pascal
program cf_659D;
var
  n:longint;
begin
  readln(n);
  writeln((n-4) div 2);
end.
```
日常宣传[博客](http://www.chenhowe.me)

---

## 作者：封禁用户 (赞：0)

一道水题，看到题解区现只有 Pascal 和 C++ 的两篇题解，那我也来凑波热闹，丢个 Python 题解吧～  
题目传送>>[CF659D](https://www.luogu.com.cn/problem/CF659D)。  
### 题意简述：  
- 一人环一 $n$ 边的四四方方的湖骑行，且给出每拐角的坐标，每到一拐角即拐弯，如不拐弯会径直冲湖的拐角为 “危险拐角”，求 “危险拐角 ” 数。  
- $4 \le n \le 1000$ ，$-10000 \le x_i,y_i \le 10000$。  

### 题目分析：  
![TuLi](https://cdn.luogu.com.cn/upload/vjudge_pic/CF659D/d384618c4de83253addcd24088af2096098ca28a.png)  
结合题意及图例我们可以发现，湖就是一个四四方方的 $n$ 边形，其“危险拐角” 处的内角为 $270 \degree$，所以我们只需求这个 $n$ 边形中角度为 $270 \degree$ 的内角数量即可，即只需读入第一行的 $n$ 即可，余下各拐角坐标根本无需读入。  
关于求 $n$ 边形中角度为 $270 \degree$ 的内角数量:  
设这个 $n$ 边形的 $n$ 个内角中有 $x$ 个角度为 $270 \degree$ 的内角，  
据题意结合多变形内角和公式：$\theta = 180 \degree ×(n-2)$ 可列方程：  
$$270x+90(n-x)=180(n-2)$$  
解得：$x= \frac {(n-4)}{2}$。  
### Code：  
```python
print((int(input())-4)//2)
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/95lt33el.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF659D) & [原题链接](http://codeforces.com/problemset/problem/659/D)

~~这题连入门都算不上吧……~~

---

**题意**

>一个人围着一个湖骑车，湖的角都是 $90^\circ$ 或 $270^\circ$，给定角的个数和每个角的坐标，求有多少个点不转弯会掉进湖里。

我们转化一下题意：求一个湖的角度为 $270^\circ$ 的个数。

---

**思路：**

其实这题是一道数学题。

首先，我们可以吧湖看做一个多边形。而多边形的内角和公式是：

$$\theta=180^\circ \times (n-2)$$

然后，我们设有 $x$ 个 $270^\circ$ 的角（其实 $x$ 就是答案啊），那么我们可以列出方程：

$$90^\circ(n-x)+270^\circ x=180(n-2)$$

$$(n-x)+3x=2(n-2)$$

$$n+2x=2n-4$$

$$2x=n-4$$

$$\boxed{x=(n-4)\div2}$$

得出最终式子后，你会惊讶地发现，竟然只需要 $n$ ，其他坐标就是废的！

---

我们直接把 $x=(n-4)\div2$ 写进代码，就可以 AC 啦！

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin>>n;
	cout<<(n-4)/2;	//直接套式子就行啦
	return 0;
}
```

---

## 作者：zjyqwq (赞：0)

### CF659D Bicycle Race题解


------------
#### 解题思路

鲁迅曾经说过：CF659D这题只有 $90$ 和 $270 $ 度的角。

他又说过：只有遇到 $270$ 度的角才会掉下去。

小学奥数老师曾经说过， $n$ 边形的内角和为 $180(n-2)$ 度。

这时，我们就可以解方程了：

解，设共有 $x$ 个 $270$ 度 的角。
$$90(n-x)+270x=180(n-2)$$
$$x=(n-4)/2$$


------------
代码就不放了。

---

