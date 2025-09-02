# Inna and Huge Candy Matrix

## 题目描述

Inna and Dima decided to surprise Sereja. They brought a really huge candy matrix, it's big even for Sereja! Let's number the rows of the giant matrix from $ 1 $ to $ n $ from top to bottom and the columns — from $ 1 $ to $ m $ , from left to right. We'll represent the cell on the intersection of the $ i $ -th row and $ j $ -th column as $ (i,j) $ . Just as is expected, some cells of the giant candy matrix contain candies. Overall the matrix has $ p $ candies: the $ k $ -th candy is at cell $ (x_{k},y_{k}) $ .

The time moved closer to dinner and Inna was already going to eat $ p $ of her favourite sweets from the matrix, when suddenly Sereja (for the reason he didn't share with anyone) rotated the matrix $ x $ times clockwise by 90 degrees. Then he performed the horizontal rotate of the matrix $ y $ times. And then he rotated the matrix $ z $ times counterclockwise by 90 degrees. The figure below shows how the rotates of the matrix looks like.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400C/168ff7db18e226cd45113b10da5f3c7fbd5680f5.png)Inna got really upset, but Duma suddenly understood two things: the candies didn't get damaged and he remembered which cells contained Inna's favourite sweets before Sereja's strange actions. Help guys to find the new coordinates in the candy matrix after the transformation Sereja made!

## 说明/提示

Just for clarity. Horizontal rotating is like a mirroring of the matrix. For matrix:

`<br></br>QWER      REWQ <br></br>ASDF  ->  FDSA<br></br>ZXCV      VCXZ<br></br>`

## 样例 #1

### 输入

```
3 3 3 1 1 9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
```

### 输出

```
1 3
1 2
1 1
2 3
2 2
2 1
3 3
3 2
3 1
```

# 题解

## 作者：I_like_magic (赞：5)

这道题其实不难，只是一道非常简单的模拟题。

我们发现，每顺时针转动 $4$ 次、镜面对称 $2$ 次、逆时针旋转 $4$ 次，就变回原来的样子了。

所以，在操作前，我们可以让 $x\gets x\bmod4$，$y\gets y\bmod2$，$z\gets z\bmod4$。

接下来，只需在草稿纸上画一画，即可知道顺时针转一次，一个点的 $x$ 值会变为原来的 $y$ 值，$y$ 值会变为原来的 $n-x+1$ 的值；镜面对称一次，一个点的 $y$ 值会变为原来的 $m-y+1$ 的值；逆时针转一次，一个点的 $y$ 值会变为原来的 $x$ 值，$x$ 值会变为原来的 $m-y+1$ 的值。要注意，两个旋转操作后要交换 $n$ 和 $m$。

---

This problem is not difficult, it's just a very simple simulation problem.

We found that every $4$ clockwise rotations, $2$ mirror symmetry rotations, and $4$ counterclockwise rotations, it returns to its original state.

So, before proceeding, we can set $x\gets x\bmod4$, $y\gets y\bmod2$, and $z\gets z\bmod4$.

Next, just draw a picture on the draft paper to know that if you turn it clockwise once, the $x$ value of a point will become the original $y$ value, and the $y$ value will become the original $n-x+1$ value; Once the mirror is symmetrical, the $y$ value of a point will change to the original $m-y+1$ value; Rotate counterclockwise once, and the $y$ value of a point will become the original $x$ value, and the $x$ value will become the original $m-y+1$ value. Note that after two rotation operations, $n$ and $m$ need to be swapped.

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,z,p;
struct e{
	int x,y;
}d[100005];
void fun1(int t){
	while(t--){
		for(int i=1;i<=p;i++){
			int o=d[i].x;
			d[i].x=d[i].y;
			d[i].y=n-o+1;
		}
		swap(n,m); //记得交换
	}
}
void fun2(int t){
	while(t--){
		for(int i=1;i<=p;i++){
			d[i].y=m-d[i].y+1;
		}
	}
}
void fun3(int t){
	while(t--){
		for(int i=1;i<=p;i++){
			int o=d[i].y;
			d[i].y=d[i].x;
			d[i].x=m-o+1;
		}
		swap(n,m);
	}
}
int main(){
	cin>>n>>m>>x>>y>>z>>p;
	x%=4;y%=2;z%=4; //记得模一下
	for(int i=1;i<=p;i++)cin>>d[i].x>>d[i].y;
	fun1(x);fun2(y);fun3(z);
	for(int i=1;i<=p;i++)cout<<d[i].x<<" "<<d[i].y<<"\n";
	return 0;
} 
```

---

## 作者：digby (赞：2)

一个非常简单的模拟题

从下面几张图可以看出这个几个特点↓
[![1sUf5d.gif](https://s2.ax1x.com/2020/02/05/1sUf5d.gif)](https://imgchr.com/i/1sUf5d)
[![1sURVe.gif](https://s2.ax1x.com/2020/02/05/1sURVe.gif)](https://imgchr.com/i/1sURVe)
[![1sUgbD.gif](https://s2.ax1x.com/2020/02/05/1sUgbD.gif)](https://imgchr.com/i/1sUgbD)

###### 得出以下结论

1. ##### X与X%4的结果相同

2. ##### Y与Y%2的结果相同

3. ##### Z与Z%4的结果相同

``` C++
#include<iostream>
using namespace std;
int N, M, x, y, z, p;
struct fz{
    int x, y;
} ;
fz E[100010];
void turn_x(){
    for(int i = 1; i <= p; i++){
        int t = N + 1 - E[i].x;
        E[i].x = E[i].y;
        E[i].y = t;
    }
    swap(N, M);
}
void turn_y(){
    for(int i = 1; i <= p; i++)
        E[i].y = M + 1 - E[i].y;
}
void turn_z(){
    for(int i = 1; i <= p; i++){
        int t = M + 1 - E[i].y;
        E[i].y = E[i].x;
        E[i].x = t;
    }
    swap(N, M);
}
int main (){
    cin >> N>>M;
    cin >>x>>y>>z;
    cin>>p;
    for(int i = 1; i <= p; i++){
        cin >>E[i].x>>E[i].y;
    }
    x %= 4;//处理x，y，z；
    y %= 2;
    z %= 4;
    
    for(int i = 1; i <= x; i++){
      turn_x(); //处理x
    }
    if(y){ //
        turn_y();//处理y
     }
    
    for(int i = 1; i <= z; i++){
        turn_z();//处理z
    }
    
    for(int i = 1; i <= p; i++){
        cout << E[i].x<<' '<<E[i].y<<endl;
    }
    return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF400C)

一道模拟题。

先看数据范围，$x,y,z \le 10^9$ 显然会超时。不难看出，顺时针或逆时针旋转 $4$ 次和镜面对称 $2$ 次后会恢复原样，所以我们先对 $x,y,z$ 进行取余。

$$x\bmod 4,z\bmod4,y\bmod2$$

然后我们观察一个矩阵顺时针旋转后坐标的变化，当你在第 $x$ 行第 $y$ 列时，旋转后应该在第 $y$ 行第 $n - x + 1$ 的位置。即 $(x, y) \to (y, n - x + 1)$。

接下来观察镜面对称与逆时针旋转，可以分别得出 $(x, y) \to (x, m - y + 1)$ 和 $(x, y) \to (m - y + 1, x)$

值得注意的是，在顺时针或逆时针旋转后，$n$ 和 $m$ 的值需要进行交换，别忘了。


### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, m, x, y, z, p;
int X[100005], Y[100005];
void solve_x() {
    for (int i = 1; i <= p; i++) {
        int tmp = X[i];
        X[i] = Y[i];
        Y[i] = n - tmp + 1; 
    }
    swap(n, m); // 交换
}
void solve_y() {
    for (int i = 1; i <= p; i++) Y[i] = m - Y[i] + 1;
}
void solve_z() {
    for (int i = 1; i <= p; i++) {
        int tmp = Y[i];
        Y[i] = X[i];
        X[i] = m - tmp + 1;
    }
    swap(n, m); // 交换
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m >> x >> y >> z >> p;
    x %= 4, y %= 2, z %= 4; // 注意取模
    for (int i = 1; i <= p; i++) cin >> X[i] >> Y[i];
    for (int i = 1; i <= x; i++) solve_x();
    for (int i = 1; i <= y; i++) solve_y();
    for (int i = 1; i <= z; i++) solve_z();
    for (int i = 1; i <= p; i++) cout << X[i] << " " << Y[i] << "\n";
    return 0;
}

/*
观察过程
1 2 3    7 4 1
4 5 6 -> 8 5 2
7 8 9    9 6 3
(1, 1) -> (1, 3) -> (3, 3) -> (3, 1) -> (1, 1)
……
1 2 3    3 2 1
4 5 6 -> 6 5 4
7 8 9    9 8 7
(1, 1) -> (1, 3) -> (1, 1)
……
1 2 3    3 6 9
4 5 6 -> 2 5 8
7 8 9    1 4 7
(1, 1) -> (3, 1) -> (3, 3) -> (1, 3) -> (1, 1)
……
*/

```


---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，发现只需要根据题意模拟即可。  

我们还知道，一个图形顺时针或逆时针旋转 $4$ 次等于没操作，一个图形镜面对称 $2$ 次也等于没操作，所以我们可以将 $x \bmod 4$，$y \bmod 2$，$z \bmod 4$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,z,p,xpos[100005],ypos[100005];
void to_x(){
	for(int i=1;i<=p;i++){
		int a=n+1-xpos[i];
		xpos[i]=ypos[i];
		ypos[i]=a;
	}
	swap(n,m);
}
void to_y(){
	for(int i=1;i<=p;i++){
		ypos[i]=m-ypos[i]+1;
	}
}
void to_z(){
	for(int i=1;i<=p;i++){
		int a=m+1-ypos[i];
		ypos[i]=xpos[i];
		xpos[i]=a;
	}
	swap(n,m);
}
int main(){
	cin>>n>>m>>x>>y>>z>>p;
	x%=4;
	y%=2;
	z%=4;
	for(int i=1;i<=p;i++){
		cin>>xpos[i]>>ypos[i];
	}
	for(int i=1;i<=x;i++){
		to_x();
	}
	for(int i=1;i<=y;i++){
		to_y();
	}
	for(int i=1;i<=z;i++){
		to_z();
	}
	for(int i=1;i<=p;i++){
		cout<<xpos[i]<<" "<<ypos[i]<<endl;
	}
	return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

（一）

题目翻译：

给你一个 $(N,M)$ 的表格和 $p$ 个坐标。

把它顺时针旋转 $x$ 次，镜面翻转 $y$ 次，逆时针旋转 $y$ 次。

求 $p$ 个坐标操作后的对应坐标。

（二）

说明：

这里的坐标不是平面直角坐标系里的，而是二维数组里的**行和列**。

~~方便起见，~~ 设原坐标为 $(a,b)$ ，变化后坐标为 $(a',b')$。

$1.$ 

顺时针。

![logo](https://cdn.luogu.com.cn/upload/image_hosting/zt07gtel.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

因为是顺时针，那么**同种颜色的圈的长度相同**。

所以可以得出：

$\begin{cases}
  a'=b \\
  b'=n-a+1
\end{cases}$

$2.$

镜面翻转。

![logo](https://cdn.luogu.com.cn/upload/image_hosting/m7qfxv0i.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

因为是镜面翻转，那么**同种颜色的圈的长度相同**。

所以可以得出：

$\begin{cases}
  a'=a \\
  b'=m-b+1
\end{cases}$

$3.$

逆时针。

![logo](https://cdn.luogu.com.cn/upload/image_hosting/wnsd8s9e.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

因为是镜面翻转，那么**同种颜色的圈的长度相同**。

所以可以得出：

$\begin{cases}
  a'=m-b+1 \\
  b'=a
\end{cases}$

$4.$

减少时间。

由于是三种操作依次进行，我们发现：

### 旋转四次和原来一样，镜面两次和原来一样。

那么 

$\begin{cases}
 x=x \bmod 4 \\
  y=y \bmod 2\\
  z=z \bmod 4
\end{cases}$

（三）

**注意：旋转后要将 $n,m$ 交换。** 

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,z,p;
int main(){
	cin>>n>>m>>x>>y>>z>>p;
	x%=4;
	y%=2;
	z%=4;
	for(int i=1;i<=p;i++){
		int a,b,n1=n,m1=m;
		cin>>a>>b;
		for(int j=1;j<=x;j++){
			int p=b;
			b=n1-a+1;
			a=p;
			swap(n1,m1);
		}
		for(int j=1;j<=y;j++){
			b=m1-b+1;
		}	
		for(int j=1;j<=z;j++){
			int p=b;
			b=a;
			a=m1-p+1;
			swap(n1,m1);
		}
		cout<<a<<" "<<b<<endl;
	}
	return 0;
}
```


---

