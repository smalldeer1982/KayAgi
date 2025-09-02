# 题目信息

# Wasted Time

## 题目描述

Mr. Scrooge, a very busy man, decided to count the time he wastes on all sorts of useless stuff to evaluate the lost profit. He has already counted the time he wastes sleeping and eating. And now Mr. Scrooge wants to count the time he has wasted signing papers.

Mr. Scrooge's signature can be represented as a polyline $ A_{1}A_{2}...\ A_{n} $ . Scrooge signs like that: first it places a pen at the point $ A_{1} $ , then draws a segment from point $ A_{1} $ to point $ A_{2} $ , then he draws a segment from point $ A_{2} $ to point $ A_{3} $ and so on to point $ A_{n} $ , where he stops signing and takes the pen off the paper. At that the resulting line can intersect with itself and partially repeat itself but Scrooge pays no attention to it and never changes his signing style. As Scrooge makes the signature, he never takes the pen off the paper and his writing speed is constant — $ 50 $ millimeters per second.

Scrooge signed exactly $ k $ papers throughout his life and all those signatures look the same.

Find the total time Scrooge wasted signing the papers.

## 样例 #1

### 输入

```
2 1
0 0
10 0
```

### 输出

```
0.200000000```

## 样例 #2

### 输入

```
5 10
3 1
-5 6
-2 -1
3 2
10 0
```

### 输出

```
6.032163204```

## 样例 #3

### 输入

```
6 10
5 0
4 0
6 0
3 0
7 0
2 0
```

### 输出

```
3.000000000```

# AI分析结果



# Wasted Time

## 题目描述

守财奴 Mr. Scrooge 想要计算他在签署文件时浪费的时间。他的签名由折线 $ A_{1}A_{2}...A_{n} $ 组成，每个签名完全一致。已知：
- 签名速度为 50 毫米/秒
- 共签署了 $k$ 次文件
求总耗时。

## 算法分类
数学

---

### 综合题解分析
核心逻辑为计算折线总长度，乘以签名次数后除以速度。关键点在于正确处理浮点坐标和精确计算欧式距离。以下为优质题解：

---

### 精选题解

#### 1. 作者：codemap（★★★★☆）
**亮点**  
- 全程使用 `double` 类型存储坐标，避免整数截断问题
- 边输入边计算，节省内存空间
- 代码可读性极佳，关键步骤注释清晰

**核心代码**  
```cpp
double dis(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

int main() {
    int n;
    double k, x[101], y[101], s = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) 
        cin >> x[i] >> y[i];
    for(int i = 2; i <= n; i++) 
        s += dis(x[i], y[i], x[i-1], y[i-1]);
    printf("%.9f", s * k / 50.0);
}
```

#### 2. 作者：Eason_AC（★★★★☆）
**亮点**  
- 采用预计算速度转换（除以 50），提升计算效率
- 通过数组存储坐标，逻辑清晰
- 使用数学公式直接表达核心逻辑

**核心实现**  
```cpp
double dist(int i, int j) {
    return sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2)) / 50.0;
}

for(int i = 1; i < n; ++i) 
    ans += dist(i, i+1);
ans *= k; // 最终时间计算
```

---

### 关键思路总结
1. **浮点精度处理**：必须使用 `double` 类型存储坐标，避免整数输入误判
2. **公式优化**：提前将距离除以速度（50）可减少最终运算量
3. **空间优化**：动态更新前一点坐标（而非存储全部点）可节省内存

---

### 举一反三
- **同类问题**：路径长度计算（如 [P1359 租用游艇](https://www.luogu.com.cn/problem/P1359)）
- **优化技巧**：预处理常用计算（如速度转换）、内存优化策略

---

### 推荐练习题
1. [P1359 租用游艇](https://www.luogu.com.cn/problem/P1359)（最短路径计算）
2. [P1515 旅行](https://www.luogu.com.cn/problem/P1515)（几何路径规划）
3. [P1665 正方形计数](https://www.luogu.com.cn/problem/P1665)（几何公式应用）

---
处理用时：137.28秒