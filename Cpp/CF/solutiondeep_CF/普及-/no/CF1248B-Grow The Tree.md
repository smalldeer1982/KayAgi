# 题目信息

# Grow The Tree

## 题目描述

Gardener Alexey teaches competitive programming to high school students. To congratulate Alexey on the Teacher's Day, the students have gifted him a collection of wooden sticks, where every stick has an integer length. Now Alexey wants to grow a tree from them.

The tree looks like a polyline on the plane, consisting of all sticks. The polyline starts at the point $ (0, 0) $ . While constructing the polyline, Alexey will attach sticks to it one by one in arbitrary order. Each stick must be either vertical or horizontal (that is, parallel to $ OX $ or $ OY $ axis). It is not allowed for two consecutive sticks to be aligned simultaneously horizontally or simultaneously vertically. See the images below for clarification.

Alexey wants to make a polyline in such a way that its end is as far as possible from $ (0, 0) $ . Please help him to grow the tree this way.

Note that the polyline defining the form of the tree may have self-intersections and self-touches, but it can be proved that the optimal answer does not contain any self-intersections or self-touches.

## 说明/提示

The following pictures show optimal trees for example tests. The squared distance in the first example equals $ 5 \cdot 5 + 1 \cdot 1 = 26 $ , and in the second example $ 4 \cdot 4 + 2 \cdot 2 = 20 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248B/7db20a2c52bb98904e15a368693f20c8c6e11756.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248B/f37e132abb11c10bbc7a671b08b806fa38567869.png)

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
26```

## 样例 #2

### 输入

```
4
1 1 2 2
```

### 输出

```
20```

# AI分析结果

### 题目内容
# 种树

## 题目描述
园丁阿列克谢教高中生学习竞技编程。为了在教师节向阿列克谢表示祝贺，学生们送给他一堆木棍，每根木棍都有一个整数长度。现在阿列克谢想用它们种一棵树。

这棵树看起来像平面上的一条折线，由所有木棍组成。折线从点(0, 0)开始。在构造折线时，阿列克谢将按任意顺序一根一根地连接木棍。每根木棍必须是垂直或水平的（即平行于OX或OY轴）。不允许连续两根木棍同时水平或同时垂直。请参考下图以作说明。

阿列克谢希望以这样一种方式制作折线，使得其终点离(0, 0)尽可能远。请帮助他以这种方式种树。

注意，定义树形状的折线可能有自相交和自接触，但可以证明最优解不包含任何自相交或自接触。

## 说明/提示
以下图片展示了示例测试的最优树。在第一个示例中，平方距离等于5×5 + 1×1 = 26，在第二个示例中为4×4 + 2×2 = 20。

![示例1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248B/7db20a2c52bb98904e15a368693f20c8c6e11756.png) 
![示例2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248B/f37e132abb11c10bbc7a671b08b806fa38567869.png)

## 样例 #1
### 输入
```
3
1 2 3
```
### 输出
```
26
```

## 样例 #2
### 输入
```
4
1 1 2 2
```
### 输出
```
20
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是基于数学原理，即当两数和一定时，两数差越大，其平方和越大。通过对木棍长度数组进行排序，将其分成两部分，使这两部分长度和的差值最大，以此得到最大的$X^2 + Y^2$值。不同题解在具体实现上略有差异，有的通过指针交替取木棍，有的直接将前半部分和后半部分分别求和。整体思路较为清晰，代码实现也相对简单。

### 所选的题解
 - **作者：Meatherm (赞：6)  星级：4星**
    - **关键亮点**：思路清晰简洁，直接表明将数组前半部分之和作为$X$，后半部分之和作为$Y$，$X^2 + Y^2$一定最大，代码实现简洁明了。
    - **重点代码**：
```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N=100010;
int a[N];
int n;
signed main(void){
	scanf("%I64d",&n);
	for(rr int i=1;i<=n;++i){
		scanf("%I64d",&a[i]);
	}
	std::sort(a+1,a+1+n);
	int cnta=0,cntb=0;
	for(rr int i=1;i<=n/2;++i){
		cnta+=a[i];
	}
	for(rr int i=n/2+1;i<=n;++i){
		cntb+=a[i];
	}
	printf("%I64d",cnta*cnta+cntb*cntb);
	return 0;
}
```
核心实现思想：先读入木棍数量和长度，对长度数组排序，然后分别计算前半部分和后半部分木棍长度之和，最后输出两部分长度和的平方和。
 - **作者：Teal_ (赞：2)  星级：4星**
    - **关键亮点**：通过三角形三边关系和引理进行分析，从另一个角度阐述了使斜边最大的原理，代码实现中使用指针交替取木棍，考虑了木棍数量奇偶性对结果的影响。
    - **重点代码**：
```cpp
#include <set>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define inf (0x3f3f3f3f)
#define N (100010)
#define int long long
const int mod = 1e9 + 7;
int n, a[N], x, y;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		ch == '-'? f = -1, ch = getchar() : ch = getchar();
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}

signed main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);
	int itL = 1, itR = n;
	while (itL <= itR) {
		x += a[itL++];
		y += a[itR--];
	}
	if (n & 1) x -= a[(n + 1) / 2];
	printf("%lld\n", x * x + y * y);
	return 0;
}
```
核心实现思想：先读入数据并排序，通过两个指针从数组两端交替取木棍累加至$x$和$y$，最后根据木棍数量的奇偶性调整$x$的值，输出$x$和$y$的平方和。

### 最优关键思路或技巧
利用数学原理“两数和一定时，两数差越大，平方和越大”，通过排序和分组计算，简化问题求解过程。

### 可拓展之处
此类题目属于基于数学原理的构造类问题，类似套路是通过数学分析找到最优的构造方式。同类型题常涉及几何图形的构造与最值求解，关键在于发现问题背后隐藏的数学规律。

### 相似知识点洛谷题目
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录与总结
无。 

---
处理用时：69.34秒