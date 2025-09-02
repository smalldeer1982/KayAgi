# Gerald is into Art

## 题目描述

Gerald bought two very rare paintings at the Sotheby's auction and he now wants to hang them on the wall. For that he bought a special board to attach it to the wall and place the paintings on the board. The board has shape of an $ a_{1}×b_{1} $ rectangle, the paintings have shape of a $ a_{2}×b_{2} $ and $ a_{3}×b_{3} $ rectangles.

Since the paintings are painted in the style of abstract art, it does not matter exactly how they will be rotated, but still, one side of both the board, and each of the paintings must be parallel to the floor. The paintings can touch each other and the edges of the board, but can not overlap or go beyond the edge of the board. Gerald asks whether it is possible to place the paintings on the board, or is the board he bought not large enough?

## 说明/提示

That's how we can place the pictures in the first test:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF560B/a420fb4a39004e44f1aae29f62afa4982709f4ea.png)

And that's how we can do it in the third one.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF560B/c256a9120b8a1034b03a87f01ea4cc344f10e71d.png)

## 样例 #1

### 输入

```
3 2
1 3
2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 5
3 3
3 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 2
2 3
1 2
```

### 输出

```
YES
```

# 题解

## 作者：Alex_Wei (赞：4)

我来水题解了$\rm{.jpeg}$。

题意简述：给定三个矩形，长和宽分别为 $a_1,b_1,a_2,b_2,a_3,b_3$，求是否有一种方案能将后两个矩形不重叠地放入第一个矩形，且这三个矩形相互平行。

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF560B) & [CF题面传送门](http://codeforces.com/problemset/problem/560/B)

---

如果 $a_2+a_3\leq a_1$ 且 $\max(b_2,b_3)\leq b_1$，那么两幅画就能放到框里面。

因为三个矩形都可以旋转，所以我们把 $8$ 种情况全部枚举一遍就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a1,a2,a3,b1,b2,b3; 
int main(){
	cin>>a1>>b1>>a2>>b2>>a3>>b3;
	if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);
	swap(a2,b2);
	if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);
	swap(a3,b3);
	if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);
	swap(a2,b2);
	if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);
	swap(a1,b1);
	if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);
	swap(a2,b2);
	if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);
	swap(a3,b3);
	if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);
	swap(a2,b2);
	if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);
	puts("NO");
	return 0;
}
```

求赞 qwq

---

## 作者：Tommyshizichen (赞：1)

一道水黄
### 题目大意
给定 $3$ 个长方形，每个长方形均可竖直或水平放置，问能否将后两个长方形放入第一个长方形中。
### 解决方法
枚举即可，总共就 $8$ 种可能。
1. 横 横 横
2. 横 横 竖
3. 横 竖 横
4. 横 竖 竖
5. 竖 横 横
6. 竖 横 竖
7. 竖 竖 横
8. 竖 竖 竖
### code
很简单，就不放了。

---

## 作者：Eterna (赞：1)

###  题意

判断两个矩形是否可以放入一个矩形边框内。

### 思路

直接模拟即可。

只要两个矩形的长小于等于边框的长则正确，否则计算下一种情况，也就是旋转一个矩形。

最多枚举 $8$ 次。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a1,a2,a3,b1,b2,b3;
bool is(){if(a2+a3<=a1&&max(b2,b3)<=b1)puts("YES"),exit(0);} 
int main()
{
	cin>>a1>>b1>>a2>>b2>>a3>>b3;
	is(),swap(a2,b2),is(),swap(a3,b3),is(),swap(a2,b2),is(),swap(a1,b1),is(),swap(a2,b2),is(),swap(a3,b3),is(),swap(a2,b2),is();
	puts("NO");
	return 0;
}
```

---

## 作者：Xssion37_XY (赞：1)

### 前情提要

[题目链接](https://www.luogu.com.cn/problem/CF560B)

[更好的阅读体验](https://www.luogu.com.cn/blog/778802/solution-cf560b)

### 题目大意

给定三个矩形，长和宽分别为 $a_1,b_1,a_2,b_2,a_3,b_3$，求是否有一种方案能将后两个矩形不重叠放入第一个矩形，且这三个矩形能相互平行。

### 实际分析

当然只需要枚举就可以了。

判断能不能放进去，那么后两个矩形的长要小于等于第一个矩形的长。

即 $a_2 + a_3 \le a_1$。

宽也同理。

当然题目中还说矩形可以旋转，这个怎么解决？

其实很好理解，旋转过后，长和宽都是颠倒过来的，你只需要把长当成宽，宽当成长来判断就可以了。

因为有 $3$ 个矩形，所以需要枚举 $8$ 次。

### 代码部分

```
#include <iostream>
using namespace std;
const int MAXX = 10000001;
int a1, b1, a2, b2, a3, b3;
int check() {// 枚举 8 种情况 
	if(a1 >= a2 + a3 and b1 >= b2 and b1 >= b3) {
		return 1;
	}
	if(a1 >= a2 + b3 and b1 >= b2 and b1 >= a3) {
		return 1;
	}
	if(a1 >= b2 + a3 and b1 >= a2 and b1 >= b3) {
		return 1;
	}
	if(a1 >= b2 + b3 and b1 >= a2 and b1 >= a3) {
		return 1;
	}
	if(b1 >= a2 + b3 and a1 >= b2 and a1 >= a3) {
		return 1;
	}
	if(b1 >= b2 + a3 and a1 >= a2 and a1 >= b3) {
		return 1;
	}
	if(b1 >= a2 + a3 and a1 >= b2 and a1 >= b3) {
		return 1;
	}
	if(b1 >= b2 + b3 and a1 >= a2 and a1 >= a3) {
		return 1;
	}
	return 0;
}
int main() {
	cin >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;
	if(check()) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
```

完结撒花！

---

## 作者：ZSYhaouuan (赞：0)

发现一个可以写题解的题。

给出三个长方形，问后两个长方形能否放进第一个长方形中？

很容易发现最好的方法是把长方形放在角落里，这样可以最大利用好空间。

我们把三个长方形的长和宽分别设为 $a_1,a_2,b_1,b_2,c_1,c_2$ 长。因为我们只能通过旋转，又只有三个三角形，很容易发现实际上只有 $2^3$ 种情况。分别是：

```cpp
//1号正，2号正，3号正
//1号正，2号正，3号斜
//1号正，2号斜，3号正
//1号正，2号斜，3号斜
//1号斜，2号正，3号正
//1号斜，2号正，3号斜
//1号斜，2号斜，3号正
//1号斜，2号斜，3号斜
```

这里的号指三个长方形，正和斜分别指每旋转和旋转过了的情况。

有了上面的基础，我们只需要动手画画图，写八个判断即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a1,a2,b1,b2,c1,c2;
//三个长方形的八种情况：
//1号正，2号正，3号正
//1号正，2号正，3号斜
//1号正，2号斜，3号正
//1号正，2号斜，3号斜
//1号斜，2号正，3号正
//1号斜，2号正，3号斜
//1号斜，2号斜，3号正
//1号斜，2号斜，3号斜
int main(){
	cin>>a1>>a2>>b1>>b2>>c1>>c2;
	if(b2<=a2&&c2<=a2&&c1+b2<=a1) cout<<"YES";
	else if(b2<=a2&&c1<=a2&&b1+c2<=a1) cout<<"YES";
	else if(b1<=a2&&c2<=a2&&c1+b2<=a1) cout<<"YES";
	else if(b1<=a2&&c1<=a2&&c2+b2<=a1) cout<<"YES";
	else if(b2<=a1&&c2<=a1&&c1+b2<=a2) cout<<"YES";
	else if(b2<=a1&&c1<=a1&&b1+c2<=a2) cout<<"YES";
	else if(b1<=a1&&c2<=a1&&c1+b2<=a2) cout<<"YES";
	else if(b1<=a1&&c1<=a1&&c2+b2<=a2) cout<<"YES";
	else cout<<"NO";
	return 0;
}

```

---

## 作者：JHR100330 (赞：0)

# 题解：CF560B Gerald is into Art

[传送门](https://www.luogu.com.cn/problem/CF560B)

## Solution

本题主要考察贪心/分支结构。

先说贪心，若将两个方块放置在左上角/右下角，或左下角/右上角则不会浪费空间。

其次，根据 $3$ 长方形/边框的旋转情况（旋转/不旋转），一共需要 $2^3 = 8$ 次判断。

按上下拼接的方法来看，在拼接时，两长方形宽 $x_2,x_3$ 长度之和要小于等于边框的长度 $x_1$，两长方形的长 $y_2,y_3$ 都要小于等于边框的长 $y_1$（定义长方形/边框上下边为长，左右边为宽）才能成功拼接，即 $x_2 + x_3 \le x_1$ 且 $\max \lbrace y_2,y_3 \rbrace \le y_1$ 才可成功放入，通过旋转情况枚举 $x_1,x_2,x_3,y_1,y_2,y_3$ 的值即可。

## Example

以下分别拿 $3 \times 4$，$1 \times 2$，$1 \times 2$ 大小的长方形左上/右下放入举例：

![00](https://cdn.luogu.com.cn/upload/image_hosting/7bbgftkb.png)

1. 不旋转/不旋转/不旋转：

![01](https://cdn.luogu.com.cn/upload/image_hosting/x3pu4te9.png)

`if(a2 + a3 <= a1 && max(b2, b3) <= b1){puts("YES"); return 0;}`

2. 不旋转/不旋转/旋转：

![02](https://cdn.luogu.com.cn/upload/image_hosting/o6b0c8p3.png)

`if(a2 + a3 <= b1 && max(b2, b3) <= a1){puts("YES"); return 0;}`

3. 不旋转/旋转/不旋转：

![03](https://cdn.luogu.com.cn/upload/image_hosting/f7pnitw9.png)

`if(a2 + b3 <= a1 && max(b2, a3) <= b1){puts("YES"); return 0;}`

4. 不旋转/旋转/旋转：

![04](https://cdn.luogu.com.cn/upload/image_hosting/o1i59ufe.png)

`if(a2 + b3 <= b1 && max(b2, a3) <= a1){puts("YES"); return 0;}`

5. 旋转/不旋转/不旋转：

![05](https://cdn.luogu.com.cn/upload/image_hosting/4ki9f50n.png)

`if(b2 + a3 <= a1 && max(a2, b3) <= b1){puts("YES"); return 0;}`

6. 旋转/不旋转/旋转：

![06](https://cdn.luogu.com.cn/upload/image_hosting/57gc24m5.png)

`if(b2 + a3 <= b1 && max(a2, b3) <= a1){puts("YES"); return 0;}`

7. 旋转/旋转/不旋转：

![07](https://cdn.luogu.com.cn/upload/image_hosting/f3bm6pal.png)

`if(b2 + b3 <= a1 && max(a2, a3) <= b1){puts("YES"); return 0;}`

8. 旋转/旋转/旋转：

![08](https://cdn.luogu.com.cn/upload/image_hosting/z1lv2ekc.png)

`if(b2 + b3 <= b1 && max(a2, a3) <= a1){puts("YES"); return 0;}`

如果不满足这八种情况，就代表无法放入边框，输出 `NO` 即可。

`puts("NO");`

## AC Code:
```cpp
#include<bits/stdc++.h>

using namespace std;

int a1, b1, a2, b2, a3, b3;

int main(){
	cin >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;
	if(a2 + a3 <= a1 && max(b2, b3) <= b1){puts("YES"); return 0;}
	if(a2 + a3 <= b1 && max(b2, b3) <= a1){puts("YES"); return 0;}
	if(a2 + b3 <= a1 && max(b2, a3) <= b1){puts("YES"); return 0;}
	if(a2 + b3 <= b1 && max(b2, a3) <= a1){puts("YES"); return 0;}
	if(b2 + a3 <= a1 && max(a2, b3) <= b1){puts("YES"); return 0;}
	if(b2 + a3 <= b1 && max(a2, b3) <= a1){puts("YES"); return 0;}
	if(b2 + b3 <= a1 && max(a2, a3) <= b1){puts("YES"); return 0;}
	if(b2 + b3 <= b1 && max(a2, a3) <= a1){puts("YES"); return 0;}
	puts("NO");
	return 0;
}
```

---

## 作者：niaoji (赞：0)

##  题意
给一个大矩形和两个小矩形，判断能否通过旋转使小矩形**不重叠，不歪斜**地放入大矩形中。
## 分析
读完题目后，思路其实很清晰，直接模拟出所有的旋转情况即可。
## 情况讨论
1. 两个矩形的旋转情况，有 4 种：上上、上下、下下、下上。（上下表示一个矩形旋转 $90$ 度）

1. 另外，还有两个矩形相对位置的变化，分别是：左右相邻、上下相邻。

- 用**乘法原理**可得，一共有 8 种情况，只要任意一种情况满足，每个小矩形的任意一边之和要小于大矩形的长或宽，且每一个矩形的另外一边要同时小于大矩形的长或宽。（附上代码以便理解）
## 关键代码
```c
bool judge (int x2,int y2,int x3,int y3)
{
    if (x2<=a1&&x3<=a1&&y2+y3<=b1)
    return true;
    if (y2<=b1&&y3<=b1&&x2+x3<=a1)
    return true;
    return false;
}
```

---

## 作者：louliu (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF560B)

### 分析

首先一看到类似于摆方块的题，明显就是大模拟！

怎么模拟才是重点。

我们可以将大方型与两个小方形的每一条边都可以旋转，那么可以放下的情况就是  $ 2  \times  2  \times  2   =   8 $ 。

代码那就出来了，不停不停的转（晕都晕了）。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a1,a2,a3,b1,b2,b3;
bool k;
int s(){
	cout<<"YES";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a1>>b1>>a2>>b2>>a3>>b3;
	if(a1 >= a2 + a3 && b1 >= b2 && b1 >= b3) {
		s();
	}
	else if(a1 >= a2 + b3 && b1 >= b2 && b1 >= a3) {
		s();
	}
	else if(a1 >= b2 + a3 && b1 >= a2 && b1 >= b3) {
		s();
	}
	else if(a1 >= b2 + b3 && b1 >= a2 && b1 >= a3) {
		s();
	}
	else if(b1 >= a2 + b3 && a1 >= b2 && a1 >= a3) {
		s();
	}
	else if(b1 >= b2 + a3 && a1 >= a2 && a1 >= b3) {
		s();
	}
	else if(b1 >= a2 + a3 && a1 >= b2 && a1 >= b3) {
		s();
	}
	else if(b1 >= b2 + b3 && a1 >= a2 && a1 >= a3) {
		s();
	}
	else{
		cout<<"NO";
	}
	return 0;
}

```

---

## 作者：_Kimi_ (赞：0)

# CF560B题解

### 题意

有一个大矩阵和两个小矩阵，给出三个矩阵的长和宽，问是否可以把两个小矩阵放入大矩阵内（小矩阵不能歪斜，不能重合，不能相交，可以重边）。

### 思路

这题比较简单，枚举出所有的摆法即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/dyp2lo7z.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/cpw1qdxd.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/blr42lr6.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/swk78h0q.png)

以上是矩阵摆在左上和右下的摆法，左下和右上同理，共有 $8$ 种摆法。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a1, b1, a2, b2, a3, b3;
bool panduan(){
	if(a1 >= a2 + a3 && b1 >= b2 && b1 >= b3) return true;
	if(b1 >= a2 + a3 && a1 >= b2 && a1 >= b3) return true;
	if(a1 >= a2 + b3 && b1 >= b2 && b1 >= a3) return true;
	if(b1 >= a2 + b3 && a1 >= b2 && a1 >= a3) return true;
	if(a1 >= b2 + a3 && b1 >= a2 && b1 >= b3) return true;
	if(b1 >= b2 + a3 && a1 >= a2 && a1 >= b3) return true;
	if(a1 >= b2 + b3 && b1 >= a2 && b1 >= a3) return true;
	if(b1 >= b2 + b3 && a1 >= a2 && a1 >= a3) return true;
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;
	if(panduan()) puts("YES");
	else puts("NO");
	return 0;
}
```


---

