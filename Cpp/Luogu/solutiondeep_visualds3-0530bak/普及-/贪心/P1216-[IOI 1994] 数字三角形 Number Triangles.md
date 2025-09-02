# 题目信息

# [IOI 1994] 数字三角形 Number Triangles

## 题目描述

观察下面的数字金字塔。


写一个程序来查找从最高点到底部任意处结束的路径，使路径经过数字的和最大。每一步可以走到左下方的点也可以到达右下方的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/95pzs0ne.png)

在上面的样例中，从 $7 \to 3 \to 8 \to 7 \to 5$ 的路径产生了最大权值。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le r \le 1000$，所有输入在 $[0,100]$ 范围内。

题目翻译来自NOCOW。

USACO Training Section 1.5

IOI1994 Day1T1

## 样例 #1

### 输入

```
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5 
```

### 输出

```
30
```

# AI分析结果



# [IOI 1994] 数字三角形 Number Triangles

**算法分类：动态规划**

---

## 题解思路与难点分析

### 核心算法流程
- **逆向动态规划**：从倒数第二层开始，每个节点选择左下/右下节点中的较大值累加，最终顶部节点即为答案
- **状态转移方程**：`dp[i][j] += max(dp[i+1][j], dp[i+1][j+1])`
- **空间优化**：使用一维数组代替二维数组，通过逆序遍历避免覆盖问题

### 解决难点对比
1. **正向 vs 逆向递推**  
   正向递推需最后遍历底层找最大值，逆向递推直接获取顶部结果  
2. **二维数组 vs 滚动数组**  
   原数组直接修改节省空间，一维数组优化至O(n)空间复杂度  
3. **输入优化**  
   边读入边处理，减少内存占用（如iwprc的题解）

---

## 高星题解推荐（≥4★）

### 1. linlin1024（5★）
- **核心思路**：自底向上递推，直接修改输入数组  
- **亮点**：图示清晰，逐步推导状态更新过程  
- **代码片段**：
```cpp
for(int i=n-2;i>=0;i--)
    for(int j=0;j<=i;j++)
        a[i][j] += max(a[i+1][j], a[i+1][j+1]);
```

### 2. iwprc（4.5★）
- **核心思路**：一维数组空间优化 + 逆序处理  
- **亮点**：将空间复杂度降至O(n)  
- **代码片段**：
```cpp
for(i=n-1;i;i--)
    for(j=i;j<=n;j++)
        a[j] = max(a[j],a[j+1]) + p;
```

### 3. EternalAlexander（4★）
- **核心思路**：输入优化 + 滚动数组  
- **亮点**：结合快读提升IO效率  
- **关键代码**：
```cpp
inline int read() {
    int x=0; char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x;
}
```

---

## 最优技巧提炼

### 关键技巧
1. **逆向状态转移**  
   从底层开始消除后效性，避免重复计算路径
2. **就地修改数组**  
   直接利用输入数组存储中间结果，节省内存
3. **滚动数组优化**  
   仅维护当前层和下一层数据，空间复杂度O(n)

### 同类型题拓展
- 矩阵最小路径和（LC 64）
- 下降路径最小和（LC 931）
- 三角形最小路径和（LC 120）

---

## 洛谷相似题目
1. P1002 过河卒（路径计数DP）
2. P1434 滑雪（记忆化搜索）
3. P1140 相似基因（二维线性DP）

---

## 算法可视化设计

### 动画方案
1. **像素风格渲染**  
   - 使用16色调色板，每个数字块显示为8x8像素方块  
   - 当前处理节点高亮黄色，路径箭头显示为红色  
2. **步进演示**  
   ```javascript
   function animateStep(layer, speed) {
       highlightCurrentNode(layer, i, j);
       await sleep(speed);
       drawPathArrow(i, j, i+1, maxDir);
       updateNumber(layer, i, j, newValue);
   }
   ```
3. **音效设计**  
   - 节点更新时播放"哔"声（Web Audio API）  
   - 路径选择时播放"咔嗒"声

---

## 核心代码实现

### 动态规划（一维数组优化）
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int dp[1005], n;

int main() {
    cin >> n;
    for(int i=1; i<=n; i++){
        for(int j=i; j>=1; j--){ // 逆序关键
            int x; cin >> x;
            dp[j] = max(dp[j], dp[j-1]) + x;
        }
    }
    cout << *max_element(dp+1, dp+n+1);
    return 0;
}
```

---

通过逆向思维与空间优化技巧，该问题可高效解决。建议通过可视化工具观察每个节点的数值更新过程，理解动态规划的状态转移本质。

---
处理用时：60.46秒