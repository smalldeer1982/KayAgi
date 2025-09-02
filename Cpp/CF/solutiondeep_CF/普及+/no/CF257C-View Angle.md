# 题目信息

# View Angle

## 题目描述

Flatland has recently introduced a new type of an eye check for the driver's licence. The check goes like that: there is a plane with mannequins standing on it. You should tell the value of the minimum angle with the vertex at the origin of coordinates and with all mannequins standing inside or on the boarder of this angle.

As you spend lots of time "glued to the screen", your vision is impaired. So you have to write a program that will pass the check for you.

## 说明/提示

Solution for the first sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/52a22a58227cc8e3cd175061056d878bb5e11b91.png)Solution for the second sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/ec228a55fc379b89df62107b0fadfa9651c34033.png)Solution for the third sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/477a3f097accae6f2425e7d37a546ed3af1f9885.png)Solution for the fourth sample test is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/8ce489535c5d9f609dbb5be22269ebed1502e2d2.png)

## 样例 #1

### 输入

```
2
2 0
0 2
```

### 输出

```
90.0000000000
```

## 样例 #2

### 输入

```
3
2 0
0 2
-2 2
```

### 输出

```
135.0000000000
```

## 样例 #3

### 输入

```
4
2 0
0 2
-2 0
0 -2
```

### 输出

```
270.0000000000
```

## 样例 #4

### 输入

```
2
2 1
1 2
```

### 输出

```
36.8698976458
```

# AI分析结果

### 题目内容
# 视角

## 题目描述
Flatland最近引入了一种新的驾照视力检查方式。检查过程如下：有一个平面，上面站着一些人体模型。你需要给出以坐标原点为顶点，且所有人体模型都位于这个角内部或边界上的最小角度值。

由于你长时间“盯着屏幕”，视力受损。所以你必须编写一个程序来帮你通过这个检查。

## 说明/提示
第一个样例测试的解决方案如下图所示：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/52a22a58227cc8e3cd175061056d878bb5e11b91.png)
第二个样例测试的解决方案如下图所示：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/ec228a55fc379b89df62107b0fadfa9651c34033.png)
第三个样例测试的解决方案如下图所示：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/477a3f097accae6f2425e7d37a546ed3af1f9885.png)
第四个样例测试的解决方案如下图所示：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF257C/8ce489535c5d9f609dbb5be22269ebed1502e2d2.png)

## 样例 #1
### 输入
```
2
2 0
0 2
```
### 输出
```
90.0000000000
```

## 样例 #2
### 输入
```
3
2 0
0 2
-2 2
```
### 输出
```
135.0000000000
```

## 样例 #3
### 输入
```
4
2 0
0 2
-2 0
0 -2
```
### 输出
```
270.0000000000
```

## 样例 #4
### 输入
```
2
2 1
1 2
```
### 输出
```
36.8698976458
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路核心均为将平面上点的坐标转化为与原点的夹角，通过排序找相邻夹角最大值，用360度减去该最大值得到结果。主要难点在于角度计算及处理。不同题解在角度计算函数选择及边界处理上有差异，部分题解还涉及代码实现细节如精度控制、输入输出优化等。

### 所选的题解
- **作者：Special_Tony（4星）**
    - **关键亮点**：清晰阐述将平面看作圆，切除部分角度的思路，点明`atan2`函数计算夹角优势及弧度转角度方法。
    - **重点代码核心思想**：利用`atan2`函数计算各点与原点夹角，排序后找相邻夹角最大值并处理边界夹角，最终得出结果。
- **作者：Y_QWQ_Y（4星）**
    - **关键亮点**：代码简洁明了，直接利用C++库函数解决问题，在代码中体现了角度计算、排序、找最大夹角及结果输出的完整过程。
    - **重点代码核心思想**：读入点坐标，用`atan2`计算角度并存入数组，排序后遍历找相邻角度差最大值及首尾角度差，用360度减该值输出。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
double x, y, a[100005], ans;
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
	{
		cin >> x >> y;
		a[i] = atan2 (y, x) * 180 / acos (- 1);
	}
	sort (a, a + n);
	ans = 360 - a[n - 1] + a[0];
	for (int i = 0; i < n - 1; ++ i)ans = max (ans, a[i + 1] - a[i]);
	cout << fixed << setprecision (12) << 360 - ans;
	return 0;
}
```
- **作者：迟暮天复明（4星）**
    - **关键亮点**：提出正难则反思路，将原问题转化为求不包含所有点部分的最大角度，贪心得出射线必经过相邻点的结论。
    - **重点代码核心思想**：与其他题解类似，通过`atan2`计算角度，排序后遍历找相邻角度差最大值，用360度减该值。

### 最优关键思路或技巧
利用`atan2`函数可方便计算点与原点夹角，避免复杂象限判断；采用正难则反思路，将求包含所有点的最小角度问题转化为求不包含点的最大角度问题，简化逻辑；排序后找相邻元素关系，有效解决问题。

### 可拓展之处
同类型题常涉及平面几何中角度、距离等计算，类似套路为将几何问题转化为代数问题，利用数学函数和算法解决。例如给定多个点求多边形内角、给定线段求夹角等。

### 洛谷相似题目推荐
- P1082 [同余方程](https://www.luogu.com.cn/problem/P1082)，考察数论中同余方程求解，与本题一样需运用数学知识解决问题。
- P2613 [【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)，涉及数学中有理数取余运算及相关数学处理。
- P1579 [哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)，需要运用数论知识，通过一定数学分析和算法实现求解。 

---
处理用时：52.96秒