# 题目信息

# Tiling with Hexagons

## 题目描述

Several ages ago Berland was a kingdom. The King of Berland adored math. That's why, when he first visited one of his many palaces, he first of all paid attention to the floor in one hall. The floor was tiled with hexagonal tiles.

The hall also turned out hexagonal in its shape. The King walked along the perimeter of the hall and concluded that each of the six sides has $ a $ , $ b $ , $ c $ , $ a $ , $ b $ and $ c $ adjacent tiles, correspondingly.

To better visualize the situation, look at the picture showing a similar hexagon for $ a=2 $ , $ b=3 $ and $ c=4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF216A/3f981143d696c9bb68234ae6ba7b4116d86bd7a4.png)According to the legend, as the King of Berland obtained the values $ a $ , $ b $ and $ c $ , he almost immediately calculated the total number of tiles on the hall floor. Can you do the same?

## 样例 #1

### 输入

```
2 3 4
```

### 输出

```
18```

# AI分析结果

### 题目内容
# 用六边形平铺

## 题目描述
很久以前，伯兰是一个王国。伯兰国王酷爱数学。因此，当他第一次参观众多宫殿中的一座时，首先注意到的是一个大厅的地面。地面是用六边形瓷砖铺成的。

大厅本身也是六边形的。国王沿着大厅的周边走了一圈，得出六条边分别与 \(a\)、\(b\)、\(c\)、\(a\)、\(b\) 和 \(c\) 块相邻瓷砖相接。

为了更好地理解这种情况，请看这张图，它展示了 \(a = 2\)、\(b = 3\) 和 \(c = 4\) 时的类似六边形。

![六边形示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF216A/3f981143d696c9bb68234ae6ba7b4116d86bd7a4.png)

传说中，当伯兰国王得到 \(a\)、\(b\) 和 \(c\) 的值后，几乎立刻就算出了大厅地面瓷砖的总数。你能做到同样的事吗？

## 样例 #1
### 输入
```
2 3 4
```
### 输出
```
18
```

### 算法分类
数学

### 题解综合分析与结论
大部分题解思路相似，都是通过将六边形分割为平行四边形来求解。先计算三个平行四边形面积之和 \(ab + bc + ca\)，然后考虑到分割线上的六边形被重复计算，减去 \(a + b + c\)，又因中间六边形被多减一次，需再加 \(1\)，从而得出公式 \(ab + bc + ca - a - b - c + 1\)。部分题解直接给出公式，未详细阐述推导过程；部分题解从分割图形、容斥原理等角度详细说明。还有题解采用割补法，将六边形看成大三角形减去三个小三角形，通过预处理数组 \(f\) 计算；另一种解法是按层计算，时间复杂度较高但更易懂。

### 所选的题解
- **作者：chlchl（4星）**
  - **关键亮点**：思路清晰，先阐述题意，再详细说明通过分割六边形为平行四边形求解的思路，对重复计算部分的分析详细，还提及容斥原理，并给出提取公因数后的代码形式。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int a, b, c; 

int main(){
    scanf("%d%d%d", &a, &b, &c);
    printf("%d\n", a * (b - 1) + c * (a - 1) + b * (c - 1) + 1);
    return 0;
}
```
核心实现思想：根据推导公式，输入 \(a\)、\(b\)、\(c\) 后，按提取公因数后的公式计算并输出结果。
- **作者：zhangyuhao9（4星）**
  - **关键亮点**：简洁明了，先概括题目大意，直接给出分割图形的思路及推导出的公式，代码简洁。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,c;
    cin>>a>>b>>c;
    cout<<a*b+b*c+a*c-a-b-c+1<<endl; 
    return 0;
}
```
核心实现思想：输入 \(a\)、\(b\)、\(c\)，按照推导出的公式直接计算并输出六边形瓷砖总数。

### 最优关键思路或技巧
将不规则六边形分割为平行四边形来计算面积，利用容斥原理处理重复计算部分，从而得出简洁的计算公式，这是一种有效的几何与数学结合的思维方式。

### 拓展思路
此类题目属于几何图形计数问题，类似套路是通过合理分割图形，转化为熟悉的图形进行计算，并注意处理重复部分。对于更复杂的图形，可能需要更巧妙的分割方法或结合其他数学原理。

### 洛谷相似题目推荐
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：涉及数学运算和高精度计算。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：需要利用数学知识分析和解决问题。
- [P1226 【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)：考察数学中的幂运算及取余相关知识。 

---
处理用时：44.44秒