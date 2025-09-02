# 题目信息

# Squares

## 题目描述

Vasya has found a piece of paper with a coordinate system written on it. There are $ n $ distinct squares drawn in this coordinate system. Let's number the squares with integers from 1 to $ n $ . It turned out that points with coordinates $ (0,0) $ and $ (a_{i},a_{i}) $ are the opposite corners of the $ i $ -th square.

Vasya wants to find such integer point (with integer coordinates) of the plane, that belongs to exactly $ k $ drawn squares. We'll say that a point belongs to a square, if the point is located either inside the square, or on its boundary.

Help Vasya find a point that would meet the described limits.

## 样例 #1

### 输入

```
4 3
5 1 3 4
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
3 1
2 4 1
```

### 输出

```
4 0
```

## 样例 #3

### 输入

```
4 50
5 1 10 2
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 正方形

## 题目描述
瓦夏发现了一张写有坐标系的纸。在这个坐标系中绘制了 $n$ 个不同的正方形。让我们用从 1 到 $n$ 的整数给这些正方形编号。结果发现，坐标为 $(0, 0)$ 和 $(a_{i}, a_{i})$ 的点是第 $i$ 个正方形的对角顶点。

瓦夏想找到平面上这样一个整点（具有整数坐标），它恰好属于 $k$ 个绘制的正方形。我们说一个点属于一个正方形，如果该点位于正方形内部或其边界上。

帮助瓦夏找到满足上述条件的点。

## 样例 #1
### 输入
```
4 3
5 1 3 4
```
### 输出
```
2 1
```
## 样例 #2
### 输入
```
3 1
2 4 1
```
### 输出
```
4 0
```
## 样例 #3
### 输入
```
4 50
5 1 10 2
```
### 输出
```
-1
```

### 算法分类
排序

### 综合分析与结论
这些题解的核心思路都是基于所有正方形左下角顶点都在 $(0, 0)$ 这一特点，得出如果一个点在较小的正方形中，那么它一定在比其面积大的正方形中的结论。所以要找恰好属于 $k$ 个正方形的点，只需要对正方形按边长排序，然后根据 $k$ 和 $n$ 的关系来确定答案。若 $k > n$，则无解输出 $-1$；否则输出第 $n - k + 1$ 大的正方形的顶点坐标。各题解思路基本一致，主要差异在于代码实现细节和表述清晰度。

### 所选的题解
 - **作者：codemap (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了，先排序后根据 $n$ 和 $k$ 的关系输出结果，符合一般解题逻辑。
    - **重点代码**：
```c
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,k,a[51],i;
    cin>>n>>k;
    for(i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+n+1);
    if(n<k)
    {
        cout<<-1;
        return 0;
    }
    cout<<a[n-k+1]<<" "<<a[n-k+1];
    return 0;
}
```
    - **核心实现思想**：读入数据后对边长数组排序，判断 $n$ 和 $k$ 的大小关系，若 $n < k$ 输出 $-1$，否则输出第 $n - k + 1$ 大的正方形顶点坐标。

 - **作者：Eason_AC (4星)**
    - **关键亮点**：解题思路阐述清晰，代码简洁，使用自定义输入宏 `getint` 有一定代码风格特点。
    - **重点代码**：
```cpp
int n, k, a[57];

int main() {
	getint(n), getint(k);
	_for(i, 1, n)	getint(a[i]);
	if(k > n)	return printf("-1"), 0;
	sort(a + 1, a + n + 1);
	printf("%d 0", a[n - k + 1]);
	return 0;
}
```
    - **核心实现思想**：读入 $n$ 和 $k$ 及各正方形边长，判断 $k$ 是否大于 $n$，若大于则输出 $-1$，否则排序后输出第 $n - k + 1$ 大的正方形顶点横坐标（纵坐标为 0 ）。

 - **作者：Allanljx (4星)**
    - **关键亮点**：对思路的解释较为详细，从原理上说明了为什么要输出第 $n - k + 1$ 小的正方形边长，代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55];
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	if(k>n) cout<<-1;
	else cout<<a[n-k+1]<<' '<<a[n-k+1];
	return 0;
}
```
    - **核心实现思想**：读入数据并排序，判断 $k$ 和 $n$ 的大小关系，若 $k > n$ 输出 $-1$，否则输出第 $n - k + 1$ 大的正方形顶点坐标。

### 最优关键思路或技巧
利用所有正方形左下角顶点固定在 $(0, 0)$ 的特性，通过排序确定第 $n - k + 1$ 大的正方形顶点作为答案，简化了问题求解过程。

### 可拓展之处
同类型题可拓展到其他规则图形包含关系的判断，类似算法套路是利用图形之间的包含关系，通过排序等方式快速定位符合条件的解。

### 洛谷相似题目推荐
 - [P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)：同样涉及到对数据排序后取特定位置元素的操作。
 - [P1093 [NOIP2007 普及组] 奖学金](https://www.luogu.com.cn/problem/P1093)：需要对学生成绩等数据排序并按要求输出特定名次学生信息。
 - [P1165 日志分析](https://www.luogu.com.cn/problem/P1165)：通过排序等操作处理数据，找到符合条件的信息，和本题思路有一定相似性。

### 个人心得摘录与总结
无。 

---
处理用时：54.69秒