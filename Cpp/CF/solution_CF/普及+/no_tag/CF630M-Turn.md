# Turn

## 题目描述

Vasya开始在某城的机器视觉公司工作。Vasya 的团队开发了通过脸部识别人的软件和硬件。这个项目的诀窍之一就是在拍摄时摄像机绕着光轴旋转。人们看到一个引人注目的小玩意ーー一个旋转的照相机ーー走到它面前，以便更好地观察它，观察它。照相机拍下了他们的照片。还有什么能更好地进行高质量的鉴定呢? 但不是每件事都这么简单。来自相机的图片也出现了旋转(在顺时针相机旋转框架内容成为逆时针旋转)。但是这种识别算法只适用于略微偏离垂直方向的人脸。 vasya 负责纠正这种情况ーー旋转捕捉到的图像，使图像与垂直方向的偏差微乎其微。要求很严格。首先，图片应该只旋转角度可分为90度，不失去一点点的信息，图像。其次，由于摄像机的帧数太大，帧数太大，只有硬件 fpga 解决方案才能提供足够的旋转速度。这种溶液只能顺时针旋转90度。当然，一个人可以使用90度旋转几次，但为了性能起见，旋转的次数应该是最少的。帮助 vasya 实现这个程序，根据给定的相机旋转角度，可以确定90度顺时针旋转的最小次数，从而得到一张垂直方向偏离最小的图片。箭头指向“ true up”。

![abc](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630M/0a70d06294ba14cf6932d88e73f7104a80a47ffd.png)下图显示了 fpga 硬件90度顺时针旋转。

![bcd](https://cdn.luogu.com.cn/upload/vjudge_pic/CF630M/27415d2b40a093696eff613b76f89792e0d969f3.png)

## 样例 #1

### 输入

```
60
```

### 输出

```
1
```

## 样例 #2

### 输入

```
-60
```

### 输出

```
3
```

# 题解

## 作者：very_easy (赞：1)

# 思路
这一题可以将题目的意思简化一下：

要把一张歪掉的照片通过旋转扶正。

很明显，可以对旋转角度进行分类，分情况讨论。

1. $<45$ 直接 $\bmod 4$ 就可以了 $(180 \equiv 0 \pmod {45})$。
2. $>45$ $+1$ 之后再除以 $4$。
3. $=45$ 这个要看是顺时针还是逆时针，两种情况都算一下取一个较小值即可。

# 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long x,m;
	cin>>x;
	if(x==0){
		cout<<0;
		return 0;
	}
	x=(abs(x)%360)*(x/abs(x));
	if(x<0){
		x+=360;
	}
	m=abs(x)/90;
	x-=m*90;
	if(x<45){
		cout<<m%4;
	}
	if(x>45){
		cout<<(m+1)%4;
	}
	if(x==45){
		cout<<min((m+1)%4,m%4);
	}
	return 0;
}
```

---

## 作者：€€£ (赞：1)

容易发现这道题在可以通过加减若干个 $360°$ 使 $x \in [0,2 \pi )$（单位：度），该过程不计入步数（角度其实没有改变）

之后暴力枚举 $m$，从 $0$ 到 $3$，暴力判断即可。

代码：

```cpp
# include <stdio.h>
# include <algorithm>
# include <math.h>
int main()
{
	int i,j;
	long long n,m;
	scanf("%lld",&n);
	if(n==0)
	{
		printf("0");
		return 0;
	}
	n=(abs(n)%360)*(n/abs(n));
	if(n<0)
		n=n+360;
	m=abs(n)/90;
	n-=m*90;
	if(n<45)
		printf("%lld",m%4);
	if(n>45)
		printf("%lld",(m+1)%4);
	if(n==45)
		printf("%lld",std::min((m+1)%4,m%4));
	return 0;
}
```

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF630M)

# 题意
$\,\,\,\,\,\,\,\,\,\,$给定一个摄像机的旋转角度 $x\degree$，需要经过多少次 $90\degree$ 的顺时针旋转使得相机照出来的照片与垂直方向夹角最小。

# 分析
看数据范围我们知道，$x$ 的范围不仅局限于 $[0\degree,360\degree]$，范围是非常大的，有 $[-10^{18},10^{18}]$，那么我们有必要对于这么大范围的 $x$ 进行判断吗？

**答案是：没必要。**

那么我们如何处理呢？

## 角
### 角的静态定义
初中数学中对角的定义是，由 $2$ 条有公共端点的射线组成的几何对象,这个公共端点叫做角的顶点，这 $2$ 条射线叫做角的两条边。就像下图，$\angle ABC$ 就是一个角，$A$ 是 $\angle ABC$ 的顶点，$AB,AC$ 就是 $\angle ABC$ 的边。

![角](https://cdn.luogu.com.cn/upload/image_hosting/tthgrk5m.png)

然而，这样的定义是有缺陷的。它可以表示
 $[0\degree,360\degree]$ 内的所有角，但是问题来了：

**如何表示大于 $360\degree$ 的角和负角呢？**

### 角的动态定义
一条射线绕着它的端点从一个位置旋转到另一个位置所形成的图形叫做角。所旋转射线的端点叫做角的顶点，开始位置的射线叫做角的始边，终止位置的射线叫做角的终边。

下面这个图，$\angle ABC$ 可以看作边 $AB$ 从 $AC$ 旋转一圈又旋转到到 $AB$ 现在的位置，$AB$ 所旋转的度数可以为正也可以为负，可以大于 $360\degree$，这样我们就实现了角度的任意定义。

![角2](https://cdn.luogu.com.cn/upload/image_hosting/7203pguw.png)

$$\text{一个}\,453.3\degree\,\text{的角}$$

### 角的转化

![角3](https://cdn.luogu.com.cn/upload/image_hosting/1lmwlakx.png)

$$\text{上面这个图，既可以表示}\,453.3\degree \,\text{的角，也可以表示}\,73.3\degree \,\text{的角}$$

形式化的，我们定义和角 $\alpha$ 终边相同的角的集合为
$$A = {\alpha + 360\degree \times k},k \in Z$$

那么这道题中，我们要用到的角只有 $[0\degree,360\degree]$，所以这些大于 $360\degree$ 的角或小于 $0\degree$ 的角要转化为 $[0\degree,360\degree]$ 的角

**那么如何转化呢？**

分为三种情况：

$$
\beta =
\begin{cases} \alpha \bmod 360\degree & \alpha > 0\degree \\
0\degree & \alpha = 0\degree\\
360\degree + \alpha \bmod 360\degree & \alpha < 0\degree \\
\end{cases}
$$

由此，我们便完成了题目中角的转换。

## 相机的旋转

由于我们之前的旋转，已经得到一个位于 $[0\degree,360\degree]$ 的角，那么旋转 $0\sim3$ 次就一定会得到答案，所以答案必定介于 $0\sim3$ 之间。

![坐标轴](https://cdn.luogu.com.cn/upload/image_hosting/o3xhm2xp.png)

我们将平面直角坐标系沿 $y = x$ 与 $y = -x$ 分为 $8$ 部分。

![坐标轴2](https://cdn.luogu.com.cn/upload/image_hosting/vqe6meu2.png)

$$\text{射线} \,AB\, \text{为} \,0 \degree\,$$

如果位于位置 $1$，那么旋转第一个 $90\degree$ 会转到 $3$，第二个 $90\degree$ 会转到 $5$，第三个 $90\degree$ 会转到 $7$，转到 $3$ 离 $0\degree$ 方向最近，那么答案就是 $1$；

如果位于位置 $1$ 与 $2$ 的交界处，那么旋转第一个 $90\degree$ 会转到 $3$ 与 $4$ 的交界处，第二个 $90\degree$ 会转到 $5$ 与 $6$ 的交界处，第三个 $90\degree$ 会转到 $7$ 与 $8$ 的交界处，转 $0$ 次与转 $1$ 次均可，取最小值 $0$，那么答案就是 $0$；

$\cdots\cdots$

如此，我们可以推理出每个位置以及 $y = x$ 与 $y = -x$ 上的点所对应的答案。

$$
ans =
\begin{cases} 
0 & 0\degree \leq \alpha \leq 45\degree \,\,\,\,or \,\,\,\,315\degree \leq \alpha \leq 360\degree \\
1 & 45\degree < \alpha \leq 135\degree \\
2 & 135\degree < \alpha \leq 225\degree  \\
3 & 225\degree < \alpha < 315\degree  \\
\end{cases}
$$

按照以上分析，模拟即可得出答案。

# 代码
下面是 AC 代码：[AC 代码](https://www.luogu.com.cn/paste/1fcv0btk)
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long x,m;
	cin >> x;
	if(x > 0) x = x % 360;
	else x = 360 + (x % 360);
	if(x > 45 && x <= 135) cout << "1" << endl;
	else if(x > 135 && x <= 225) cout << "2" << endl;
	else if(x > 225 && x < 315) cout << "3" << endl;
	else if(x >= 315 || x <= 45) cout << "0" << endl;
	return 0;
}
```


---

## 作者：andyli (赞：0)

模拟，每次循环顺时针旋转 $90^{\circ}$，直到 $0\leq x \leq 45$ 或 $315 \leq x < 360$，输出次数。

```cpp
#include "lib/all.hpp"

int main() {
    dR(i64, x);
    x = (x % 360 + 360) % 360;
    int ans = 0;
    while (!(0 <= x && x <= 45 || 315 <= x && x < 360)) {
        ans++;
        x = (x + 270) % 360;
    }
    writeln(ans);
    return 0;
}
```

---

