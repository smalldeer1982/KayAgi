# Come Together

## 题目描述

Bob and Carol hanged out with Alice the whole day, but now it's time to go home. Alice, Bob and Carol live on an infinite 2D grid in cells $ A $ , $ B $ , and $ C $ respectively. Right now, all of them are in cell $ A $ .

If Bob (or Carol) is in some cell, he (she) can move to one of the neighboring cells. Two cells are called neighboring if they share a side. For example, the cell $ (3, 5) $ has four neighboring cells: $ (2, 5) $ , $ (4, 5) $ , $ (3, 6) $ and $ (3, 4) $ .

Bob wants to return to the cell $ B $ , Carol — to the cell $ C $ . Both of them want to go along the shortest path, i. e. along the path that consists of the minimum possible number of cells. But they would like to walk together as well.

What is the maximum possible number of cells that Bob and Carol can walk together if each of them walks home using one of the shortest paths?

## 说明/提示

In all pictures, red color denotes cells belonging only to Bob's path, light blue color — cells belonging only to Carol's path, and dark blue color — cells belonging to both paths.

One of the optimal routes for the first test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1845B/c85b53d9d1c53dba5706a67df1e77b327570237d.png)  Bob's route contains $ 5 $ cells, Carol's route — $ 7 $ cells, and they will visit $ 3 $ cells together.The optimal answer for the second test case is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1845B/50a4de29eccf387d8021b4c4d1c44c0fb0d1aede.png)  Bob's route contains $ 4 $ cells, Carol's route — $ 3 $ cells, and they will visit only $ 1 $ cell together.One of the optimal answers for the third test case is shown below:

 ![](https://espresso.codeforces.com/c353903c5672ef730d834c0e4d58e6d3554a4b1b.png)  Bob's route contains $ 6 $ cells, Carol's route — $ 9 $ cells, and they will visit $ 6 $ cells together.

## 样例 #1

### 输入

```
3
3 1
1 3
6 4
5 2
2 2
7 2
1 1
4 3
5 5```

### 输出

```
3
1
6```

# 题解

## 作者：Shadow_T (赞：1)

题目大意：两个人在一个二维方格平面上，他们每次只能从一个格子走到一个相邻的格子，现在他们要从起始的格子 $A$ 分别走到他们想要去的格子 $B,C$，问他们共同经过的格子最多有多少。

人物只能横着走或竖着走，所以对于 $(x_1,y_1)$ 和 $(x_2,y_2)$ 他们的距离就是：
$$|x_1-x_2|+|y_1-y_2|$$

也就是说，当坐标改变的值的符号相同，两者能一起走，设横坐标改变的值是 $s_x$，竖坐标是 $s_y$，则长度 $ans$ 加上 $\min(|s_x|,|s_y|)$。

最后别忘了起点 $A$，输出 $ans+1$。

代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int t,ax,ay,bx,by,cx,cy;
		cin>>ax>>ay>>bx>>by>>cx>>cy;
		int ans=min(abs(ax-bx),abs(ax-cx))*((ax-bx>0)==(ax-cx>0))+min(abs(ay-by),abs(ay-cy))*((ay-by>0)==(ay-cy>0))+1;
		cout<<ans<<endl;
	}
}
```

---

## 作者：qwq___qaq (赞：1)

分类讨论：

- 若 $B,C$ 同在 $A$ 上方，即 $\min\{x_b,x_c\}>x_a$。那么他们可以一起往上走，即走 $\min\{x_b,x_c\}-x_a$ 步。

- 若 $B,C$ 同在 $A$ 下方，即 $\max\{x_b,x_c\}<x_a$。那么他们可以一起往上走，即走 $x_a-\max\{x_b,x_c\}$ 步。

- 若 $B,C$ 同在 $A$ 右方，即 $\min\{y_b,y_c\}>y_a$。那么他们可以一起往上走，即走 $\min\{y_b,y_c\}-y_a$ 步。

- 若 $B,C$ 同在 $A$ 左方，即 $\max\{y_b,y_c\}<y_a$。那么他们可以一起往上走，即走 $y_a-\max\{y_b,y_c\}$ 步。

最后还要注意，根据样例解释，$A$ 本身还要再算一步。

时间复杂度 $O(T)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,xa,ya,xb,yb,xc,yc;
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
    	cin>>xa>>ya>>xb>>yb>>xc>>yc;
    	int ans=0;
    	if(min(xb,xc)>xa)
  			ans+=min(xb,xc)-xa;
  		if(max(xb,xc)<xa)
  			ans+=xa-max(xb,xc);
  		if(min(yb,yc)>ya)
  			ans+=min(yb,yc)-ya;
  		if(max(yb,yc)<ya)
  			ans+=ya-max(yb,yc);
  		cout<<ans+1<<endl;
	}
	return 0;
}
```

---

## 作者：cff_0102 (赞：1)

给定无限大的网格图中 $A$，$B$，$C$ 三点的横纵坐标，求出从 $A$ 分别到 $B$ 与 $C$ 的最短路径最大有多少格点重合。

首先，计算出从 $A$ 到 $B$，从 $A$ 到 $C$ 需要在横纵坐标上分别走的距离。比如，样例中的第一组数据 $A(3,1),B(1,3),C(6,4)$，从 $A$ 到 $B$ 就需要在 $x$ 上 $-2$，在 $y$ 上 $+2$，从 $A$ 到 $C$ 就需要在 $x$ 上 $+3$，在 $y$ 上 $+3$。

- 从 $A$ 到 $B$，从 $A$ 到 $C$ 的 $x$ 坐标变化量一正一负，无法重合。
- 从 $A$ 到 $B$，从 $A$ 到 $C$ 的 $y$ 坐标变化量都是正数，其中 $2$ 次移动可以重合。
- 最后再加上 $A$ 点一定重合，答案就是 $2+1=3$。

这样，计算逻辑就出来了：先计算出从 $A$ 到 $B$，从 $A$ 到 $C$ 在 $x$（$y$）上的变化量 $\Delta x_B,\Delta y_B,\Delta x_C,\Delta y_C$。假如变化量同号，$ans$ 就加上 $\min{(|\Delta x_B|,|\Delta x_C|)}$（$\min{(|\Delta y_B|,|\Delta y_C|)}$）。假如变化量异号，$ans$ 不变。最后，输出 $ans+1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int cal(long long db,long long dc){//计算 ans 应该加的值 
	if(db*dc<0)return 0;//相乘小于 0 则不同号
	return min(abs(db),abs(dc));//同号取更小的绝对值 
}
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;//数据组数 
	while(t--){
		int xa,xb,xc,ya,yb,yc;
		cin>>xa>>ya>>xb>>yb>>xc>>yc;//输入三个坐标 
		int dxb=xb-xa,dyb=yb-ya,dxc=xc-xa,dyc=yc-ya;//计算 ΔxB,ΔyB,ΔxC,ΔyC
		int ans=0;
		ans+=cal(dxb,dxc);
		ans+=cal(dyb,dyc);
		cout<<ans+1<<endl;//实际上也可以将 ans 初始化为 1 
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

# 题目描述

[Come Together](https://www.luogu.com.cn/problem/CF1845B)

# 算法思路

本题中人物只能横向或纵向移动，所以从一点到另一点的最短距离，肯定是横向走一段距离，再纵向走一段距离。所以，我们只要求出 $A$ 到 $B$ 和 $A$ 到 $C$ 中，横向和纵向移动相同的部分。

#### 结论

当横纵坐标改变的值是一正一负时，两人不能一起走；

当横纵坐标改变的值是两正或两负时，两人能一起走，长度为横纵坐标改变的值的最小值；

最后还得加一。（起点 $A$ 也要算进去）

### 时间复杂度：$O(t)$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
ll t,ax,ay,bx,by,cx,cy;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>t;
	while(t--)//t组数据 
	{
		cin>>ax>>ay>>bx>>by>>cx>>cy;
		cout<<min(abs(ax-bx),abs(ax-cx))*((ax-bx>0)==(ax-cx>0))+min(abs(ay-by),abs(ay-cy))*((ay-by>0)==(ay-cy>0))+1<<"\n";
		//本题精髓 
	}
	return 0;
}
```


---

## 作者：WsW_ (赞：1)

## 思路：
由于是在网格中移动，所以只有上、下、左、右四个方向。简单地说，只存在横向和纵向的两种移动。  
因此，从 $A$ 到其他一点，肯定是横向移动一定距离（使横坐标相等）且纵向移动一定距离（使纵坐标相等）。显而易见，在网格中这是最短的路线。  
综上，移动共分为两步：横向移动（横坐标 $+X$），和纵向移动（纵坐标 $+Y$）。
因此，我们只需要求出 $A$ 到 $B$ 和 $A$ 到 $C$ 中，横向移动与纵向移动相同的部分，注意，起点 $A$ 也算在相同部分之内，不要漏了。 
## 例子：
将以上思路用于样例第一个测试点：  
从 $A$ 到 $B$ 横坐标 $-2$，纵坐标 $+2$；  
从 $A$ 到 $C$ 横坐标 $+3$，纵坐标 $+3$。  
横坐标两条路线显然无交集，纵坐标可以一起向上走两格（$+2$）。
## 结论：
当横坐标改变值为一正一负时，横向两者不能一起走。  
当横坐标改变值为同正或同负时，两者可以一起走，走的长度为绝对值较小的改变值。  
纵坐标同理。  
最后，统计横纵总共可以一起走的，并加上起点 $A$。
## 精简代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int xa,ya,xb,yb,xc,yc;
int x,y;
int main(){
	cin>>t;
	while(t--){
		scanf("%d%d%d%d%d%d",&xa,&ya,&xb,&yb,&xc,&yc);
		printf("%d\n",min(abs(xa-xb),abs(xa-xc))*((xa-xb>0)==(xa-xc>0))+min(abs(ya-yb),abs(ya-yc))*((ya-yb>0)==(ya-yc>0))+1);
        	/*
        	min(abs(xa-xb),abs(xa-xc))*((xa-xb>0)==(xa-xc>0))
            	此部分为横向，前面min函数内的为求较小的绝对值
                后面部分为判断改变值是否同号，如果不同号，那么后半部分的值为0，乘起来整体为0
                当有一个横向移动距离为0时，整体为0，不用特判
                */
	}
	return 0;
}
```

---

## 作者：AllenKING_RED (赞：1)

### 题目大意

两个人在一个二维方格平面上，他们每次只能从一个格子走到一个相邻的格子，现在他们要从起始的格子 $A$ 分别走到他们想要去的格子 $B$、$C$，问他们共同经过的格子最多有多少。

### 基本思路

设题目中 $A$ 点的坐标为 $(x_A,y_A)$，$B$ 点的坐标为 $(x_B,y_B)$，$C$ 点的坐标为 $(x_C,y_C)$。

不难发现，若 $x_B \leq x_A$， 并且 $x_C \leq x_A$，那么两个人的路径必然有一部分横坐标相同，通过平移可以发现，在最优情况下，这一段横坐标相同的路径必然可以做到重合，其答案则是 $x_A$ 减去剩下两个坐标的较大者。

以此类推，$x_A \leq x_B$ 的情况和纵坐标的情况也可以求出答案，将合法状态下的答案累计即可。

但是这种情况会漏算一个值：

计算的共同部分不包括起始点 $A$，所以最终答案要加一。

所以加一后正确答案就出来了。

### 代码实现

以下为赛时代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(void)
{
	cin>>T;
	while(T--)
	{
		int xa,ya,xb,yb,xc,yc;
		cin>>xa>>ya>>xb>>yb>>xc>>yc;
		int ans=0;
		if((xb>=xa&&xc>=xa)||(xb<=xa&&xc<=xa))
		{
			ans+=min(abs(xb-xa),abs(xc-xa)); 
		}
		if((yb>=ya&&yc>=ya)||(yb<=ya&&yc<=ya))
		{
			ans+=min(abs(yb-ya),abs(yc-ya)); 
		}		
		++ans;
		cout<<ans<<endl;
	}
	return 0;
}
```





---

## 作者：_zqh_ (赞：0)

# 思路简述

**本题是一道规律题。**

本题的重点在于如何将重复路程最大化，也就是求出图中的紫色部分。

![题](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1845B/c85b53d9d1c53dba5706a67df1e77b327570237d.png)

不难想到，总共的相交部分为 $x$ 坐标的相交部分与 $y$ 坐标的相交部分之和。

而如果两目的地的 $x$ 或 $y$ 坐标在起点的两侧，则忽略不计。

最后还要再算上起点，也就是还要加一。

不难推出公式：

$$
\min\{|B_x-A_x|,|C_x-A_x|\} + \min\{|B_y-A_y|,|C_y-A_y|\}
$$

不过两者前提都是不分布在起点两侧。

思路部分完结。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)
// #pragma GCC optimize(2)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<ll, ll>
#define il inline
using namespace std;

int main() {
    ios;
    cin >> T;
    while (T--) {
        ll x, y, hx1, hy1, hx2, hy2, ans = 0;
        cin >> x >> y >> hx1 >> hy1 >> hx2 >> hy2;
        if ((hx1 >= x && hx2 >= x) || (hx1 <= x && hx2 <= x)) {//判断x坐标的位置
            ans += min(abs(hx1 - x), abs(hx2 - x));
        }
        if ((hy1 >= y && hy2 >= y) || (hy1 <= y && hy2 <= y)) {//同理，判断y坐标的位置
            ans += min(abs(hy1 - y), abs(hy2 - y));
        }
        cout << ans + 1 << "\n";
    }
    return 0;
}
```

---

## 作者：猜一猜我是谁 (赞：0)

# 题意简述
一共 $T$ 组数据，每组数据给定平面直角坐标系上的三个点 $A,B,C$ 的横纵坐标，求 $A$ 到 $B,C$ 最短路径上最多有多少个点重合。

# 分析
![](https://cdn.luogu.com.cn/upload/image_hosting/aqpbviwe.png?x-oss-process=image/resize,m_lfit,h_15000,w_15000)

如图，在平面直角坐标系中，$A(6,0)$，$B(0,2)$，$C(3,4)$。重合的部分长度即为 $AD+DE=2+3=5$。

其中，$AD$ 的长就是 $B,C$ 中最小的纵坐标与 $A$ 的纵坐标的差，$DE$ 的长就是 $B,C$ 中最大的横坐标与 $A$ 的横坐标的差。

这种情况是 $B,C$ 都位于 $A$ 的上边和左边。若 $B,C$ 都位于 $A$ 的上边但一个在左一个在右，那么公共部分 就只有 $AD$。

由此引申还可得到：

- 当 $B,C$ 都位于 $A$ 的下边，公共部分长度是 $B,C$ 中最大的纵坐标与 $A$ 的纵坐标的差
- 当 $B,C$ 都位于 $A$ 的右边，公共部分长度是 $B,C$ 中最小的横坐标与 $A$ 的横坐标的差

注意：题目要求的是公共点数，所以最后要 +1。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a1,a2,b1,b2,c1,c2;
int main(){
    cin>>t;
    while(t--){
        cin>>a1>>a2>>b1>>b2>>c1>>c2;
        int ans=0;
        if(b2>a2&&c2>a2) ans+=min(b2-a2,c2-a2);//都在上边
        if(b1>a1&&c1>a1) ans+=min(b1-a1,c1-a1);//都在右边
        if(b2<a2&&c2<a2) ans+=min(a2-b2,a2-c2);//都在下边
        if(b1<a1&&c1<a1) ans+=min(a1-b1,a1-c1);//都在左边
        cout<<ans+1<<endl;
    }
}
```

---

## 作者：haozinojc (赞：0)

很明显的一道**规律**题。

# 思路：

首先，通过初中数学，我们可以知道，这种走格子的最短距离是 $\left\vert x_a-x_b \right\vert+\left\vert y_a-y_b \right\vert$。

然后，我们分**横坐标和纵坐标**两种情况讨论。

## 横坐标：

- 当 $a$ 点横坐标在 $b$、$c$ 横坐标之中时，那么 $a$ 点不得不分左右两条路走，即没有共同路径。

- 反之，最短距离就是：$\min(\left\vert x_a-x_b \right\vert,\left\vert x_a-x_c \right\vert)$。

## 纵坐标：

同上。

- 当 $a$ 点纵坐标在 $b$、$c$ 纵坐标之中时，那么 $a$ 点不得不分上下两条路走，即没有共同路径。

- 反之，最短距离就是：$\min(\left\vert y_a-y_b \right\vert,\left\vert y_a-y_c \right\vert)$。

最后将两个结果综合一下就行了。

**注：初始点本身也算。**

# 代码：

```cpp

#include<bits/stdc++.h>
#define cin(x) scanf("%d",&x);
using namespace std;
int t,xa,ya,xb,yb,xc,yc,ans;
signed main(){
	cin(t);
	while(t--){
		ans=1;
		cin(xa);cin(ya);cin(xb);cin(yb);cin(xc);cin(yc);
		if((xb>=xa&&xc>=xa)||(xb<=xa&&xc<=xa))ans+=min(abs(xb-xa),abs(xc-xa));
		if((yb>=ya&&yc>=ya)||(yb<=ya&&yc<=ya))ans+=min(abs(yb-ya),abs(yc-ya));
		cout<<ans<<"\n";
	}
	return 0;
} 

```

---

## 作者：sz_jinzikai (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1845B)&[CF传送门](https://codeforces.com/problemset/problem/1845/B)

# 思路

从 $A$ 点走到 $B$ 点和 $C$ 点，一定是横着走或者竖着走的，不会出现斜着走的情况。这说明了最长的重合部分也一定是横着和竖着的。所以，我们可以把重合部分分成横着的部分和竖着的部分分开考虑：

横着的部分中，也可以分两种情况考虑：

1. $B$ 点和 $C$ 点分别在 $A$ 点的两侧。举个栗子，$B$ 点在 $A$ 左边，而 $C$ 点在 $A$ 的右边，则横着的部分只有 $A$ 点一个点。

2. $B$ 点和 $C$ 点分别在 $A$ 点的同一侧。举个栗子，$B$ 点在 $A$ 左边，而 $C$ 点也在 $A$ 的左边，则横着的部分有 $A$ 点与 $B$ 点的横坐标之差和 $A$ 点与 $C$ 点的距离中的最小值。

当然，竖着的部分中，也可以分两种情况考虑，这里就不展开讲了

# 代码

```cpp
# include <bits/stdc++.h> //万能头
int t, xa, xb, xc, ya, yb, yc; //定义数据组数和 3 个节点的坐标
int main () { //主函数
	cin >> t; //输入数据组数
	while (t --) { //t 组数据的经典写法
		cin >> xa >> ya >> xb >> yb >> xc >> yc; //读入点的坐标
		xb -= xa, xc -= xa; //算出
		yb -= ya, yc -= ya; //算出 BC 两点与 A 点的纵坐标之差
		cout << min (abs (xb), abs (xc)) * (xb > 0 == xc > 0) + //算出 BC 两点与 A 点的横坐标之差最小值，并且判断是属于以上哪种情况
				min (abs (yb), abs (yc)) * (yb > 0 == yc > 0) + //算出 BC 两点与 A 点的纵坐标之差最小值，并且判断是属于以上哪种情况
        	 1 << '\n'; //最后别忘了加上 1 和换行！！！
	}
	return 0; //结束程序
}
```

---

## 作者：Convergent_Series (赞：0)

因为是网格图，所以最短路径 ${}=|x_1-x_2|+|y_1-y_2|$，横纵坐标可以分开考虑。

先看横坐标：

+ 若 $b,c$ 在 $a$ 的同侧，则可以先一起走到较近的一个点的横坐标，即为重合距离。
+ 若 $b,c$ 在 $a$ 的异侧，则无重合距离。

纵坐标也一样。

把两个距离相加即为重合距离。因为题目求的是重合格点，所以要加 $1$。

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,xa,xb,xc,ya,yb,yc,ans;
int main(){
    cin>>t;
    while(t--){
        ans=0;
        cin>>xa>>ya>>xb>>yb>>xc>>yc;
        if((xa-xb)*(xa-xc)>0) ans+=min(abs(xa-xb),abs(xa-xc));//横
        if((ya-yb)*(ya-yc)>0) ans+=min(abs(ya-yb),abs(ya-yc));//纵
        cout<<ans+1<<"\n";
    }
 
    return 0;
}
```

---

## 作者：Furina_Hate_Comma (赞：0)

一道**数学**题。

我们可以分别计算出两人向上走和向下走的需求量(反方向时为负数)。 

然后如果某个分享的需求量同时为负数，就一起乘上 $-1$(相当于反过来)。 

最后如果同一方向的需求量同正负，答案就加上较小值(相当于一个人陪另一个人走一段共有的路)。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int x,y,x1,y1,x2,y2,ans=1;
		cin>>x>>y>>x1>>y1>>x2>>y2; 
		int dx1=x1-x,dx2=x2-x,dy1=y1-y,dy2=y2-y;
		if(dx1<0&&dx2<0)dx1=-dx1,dx2=-dx2;
		if(dy1<0&&dy2<0)dy1=-dy1,dy2=-dy2;
		if(dx1>0&&dx2>0)ans+=min(dx1,dx2);
		if(dy1>0&&dy2>0)ans+=min(dy1,dy2);
		cout<<ans<<endl;
	}
	return 0;
} 
``` 

---

## 作者：_O_v_O_ (赞：0)

简单的分类讨论题。

先看横向坐标：如果 $B$ 和 $C$ 点在 $A$ 点的同侧，假设 $x1$ 为 $B$ 点到 $A$ 点的横向距离，假设 $x2$ 为 $C$ 点到 $A$ 点的横向距离，则横向坐标重合部分为 $\min(x1,x2)$。竖向坐标同侧亦是如此。

如果 $B$ 点和 $C$ 点在 $A$ 点的横向不同侧，那么横向它们不可能重合。竖向坐标同侧亦是如此。

最后，因为它们一定会在 $A$ 点重合，所以输出还要 $+1$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long  //不开 long long 见祖宗。

int t,ax,ay,bx,by,cx,cy;  //后面几个代表各点坐标

signed main(){
	cin>>t;
	while(t--){
		cin>>ax>>ay>>bx>>by>>cx>>cy;
		int x=bx-ax,y=by-ay,x2=cx-ax,y2=cy-ay,ans=1;
		if(x*x2>0) ans+=min(abs(x),abs(x2));
		if(y*y2>0) ans+=min(abs(y),abs(y2));
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：Night_sea_64 (赞：0)

在网格图中，两个点间的最短路就是它们的**曼哈顿距离**。$(x_1,y_1)$ 和 $(x_2,y_2)$ 之间的曼哈顿距离是 $|x_1-x_2|+|y_1-y_2|$。

我们计算出 $A$ 点到 $B,C$ 两点，$x,y$ 坐标相差多少格（带正负号的）。只要 $x,y$ 坐标向正确的方向移动了那么多格就可以了，并不要求顺序。

既然不要求顺序，那就很容易发现：如果两个路径中，$x$ 坐标移动的方向相同，那么最多重合的距离就是两个 $x$ 坐标移动距离的较小值；方向不同，重合距离为 $0$；$y$ 坐标同理。

但是刚才算的是重合距离，题目问的是重合点数，就是距离 $+1$ 的值。

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int xa,ya,xb,yb,xc,yc;
        cin>>xa>>ya>>xb>>yb>>xc>>yc;
        int dx1=xb-xa,dx2=xc-xa;
        int dy1=yb-ya,dy2=yc-ya;
        cout<<(dx1*dx2>0?min(abs(dx1),abs(dx2)):0)+(dy1*dy2>0?min(abs(dy1),abs(dy2)):0)+1<<endl;
    }
    //dx1*dx2>0 求的是 dx1 和 dx2 是否同正或同负，即 x 坐标是否向同一方向移动。y 坐标同理。
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

我们可以发现，一个人的回家路线可以被概括为一共往上或下走 $x$ 格，往左或右走 $y$ 格。

我们可以让这俩人尽可能先走在一起，再分道扬镳。那么，我们分别考虑上下移动和左右移动。如果两人一上一下则无法重叠，否则取 $x$ 最小的那个，左右移动同理。

别忘了加上起点那一个点。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int t;
int xa,ya;
int xb,yb;
int xc,yc;
int askans(int a,int b,int c){
	if(a<=b&&a>=c)return 0;
	if(a<=c&&a>=b)return 0;
	return min(abs(a-b),abs(a-c));
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1845B_1.in","r",stdin);
	freopen("CF1845B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d%d%d",&xa,&ya,&xb,&yb,&xc,&yc);
		printf("%d\n",askans(xa,xb,xc)+askans(ya,yb,yc)+1);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/113565486)

**By dengziyue**

---

## 作者：cyrxdzj (赞：0)

### 一、思路

题中要求每个人回家都得走最短路径。换句话说，一个人在垂直方向（上下）和水平方向（左右）上最多分别选择一个方向。

因此，我们可以分别判断这两个人的家在垂直方向和水平方向上是不是一个方向（可能不是很好理解，参见代码）。如果是，那就意味着这两个人在这个方向上可以同走一段路。

最后别忘了原来的点 $A$ 也是要计入路径长度的。

### 二、代码

```cpp
// Author: cyrxdzj
// Problem: B. Come Together
// Contest: Educational Codeforces Round 151 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1845/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int x,y,x1,y1,x2,y2;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&x,&y);//读入3个点。
        scanf("%d%d",&x1,&y1);
        scanf("%d%d",&x2,&y2);
        int ans=0;
        if((x1>=x&&x2>=x)||(x1<=x&&x2<=x))//都在左边或都在右边
        {
            ans+=min(abs(x1-x),abs(x2-x));
        }
        if((y1>=y&&y2>=y)||(y1<=y&&y2<=y))//都在上边或都在下边
        {
            ans+=min(abs(y1-y),abs(y2-y));
        }
        ans++;//别忘了原来的点
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Register_int (赞：0)

小分讨。

分别考虑 $B$，$C$ 点分别在横、纵坐标上相对于 $A$ 的位置：

- $x$ 坐标同侧，$y$ 坐标同侧

即题目中第三个图的情况。我们可以找到最远的一个点，使得这个点位于以 $A$，$C$、$A$，$B$ 为对角顶点的矩形内，将横纵坐标距离分别取最小值即为答案。

- $x$ 坐标异侧，$y$ 坐标同侧

此时为题目中第一个图的情况，路线也和图中一样，沿着 $y$ 轴方向走，可以让重合的格数尽量多。

- $x$ 坐标同侧，$y$ 坐标异侧

旋转 $90^{\circ}$ 后与上一种情况相同。

- $x$ 坐标同侧，$y$ 坐标同侧

说明路线方向完全相反，答案为 $1$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int t; ll ax, ay, bx, by, cx, cy;

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%lld%lld%lld%lld%lld%lld", &ax, &ay, &bx, &by, &cx, &cy);
		if (min(bx, cx) <= ax && ax <= max(bx, cx)) {
			if (min(by, cy) <= ay && ay <= max(by, cy)) puts("1");
			else printf("%lld\n", min(abs(ay - by), abs(ay - cy)) + 1);
		} else if (min(by, cy) <= ay && ay <= max(by, cy)) printf("%lld\n", min(abs(ax - bx), abs(ax - cx)) + 1);
		else printf("%lld\n", min(abs(ax - bx), abs(ax - cx)) + min(abs(ay - by), abs(ay - cy)) + 1);
	}
}
```

---

