# 题目信息

# Burning Midnight Oil

## 题目描述

有一天，Vasy被委托了一个非常重要的任务:在一个晚上写一个程序。该程序由n行代码组成。Vasya已经筋疲力尽了，所以他这样工作：首先他写v行代码，喝一杯茶，然后他写![](https://cdn.luogu.org/upload/vjudge_pic/CF165B/be8d069d652d51f8329016702f7c81645767ac06.png)行代码，再喝一杯茶，然后他再写![](https://cdn.luogu.org/upload/vjudge_pic/CF165B/4e3353b53aaa8dff17e86fc64d74d2d54f694513.png)v行......以此类推。

![](https://cdn.luogu.org/upload/vjudge_pic/CF165B/ff48225f7f772c08409f2d464b02c44cf20620e2.png)，表示a除以b后向下取整。若当前![](https://cdn.luogu.org/upload/vjudge_pic/CF165B/ff48225f7f772c08409f2d464b02c44cf20620e2.png)的值等于0，Vasya会睡着，但此之前他必须先完成程序。

Vasya想知道，在睡着之前，允许他写出不少于n行代码的最小值v可以取多少。

## 样例 #1

### 输入

```
7 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
59 9
```

### 输出

```
54
```

# AI分析结果



# Burning Midnight Oil

## 题目描述

有一天，Vasy被委托了一个非常重要的任务：在一个晚上写一个程序。该程序由n行代码组成。Vasya已经筋疲力尽了，所以他这样工作：首先他写v行代码，喝一杯茶，然后他写⌊v/k⌋行代码，再喝一杯茶，然后他再写⌊v/k²⌋行......以此类推。当当前⌊v/k^i⌋的值等于0时，Vasya会睡着，但此之前他必须先完成程序。请找出允许他写出不少于n行代码的最小v值。

## 样例 #1

### 输入
```
7 2
```

### 输出
```
4
```

## 样例 #2

### 输入
```
59 9
```

### 输出
```
54
```

**算法分类**：二分

---

### 题解综合分析

所有题解均采用二分答案法，核心思路为：
1. **单调性证明**：v越大总行数越大，答案具有单调性
2. **二分范围**：左界1，右界取n（最优）或1e9
3. **check函数**：计算v + ⌊v/k⌋ + ⌊v/k²⌋ + ... ≥n
4. **防溢出处理**：使用long long类型，循环终止条件优化

#### 高分题解亮点（4★）

1. **题解作者：tallnut**（4★）
   - 亮点：最简洁的check函数实现，使用tmpk *=k的循环结构
   - 代码片段：
   ```cpp
   bool check(long long x) {
       unsigned long long sum = x;
       unsigned long long tmpk = k;
       while (tmpk <= x) {
           sum += x / tmpk;
           tmpk *= k;
       }
       return sum >= n;
   }
   ```

2. **题解作者：暮光闪闪**（4★）
   - 亮点：数学推导证明上界取n，优化二分范围
   - 心得："当v≥n时必然满足条件，因此右界设为n即可"
   - 代码片段：
   ```cpp
   bool check(ll x){
       ll sum = x, cnt = k;
       while(x >= cnt){
           sum += x / cnt;
           cnt *= k;
       }
       return sum >= n;
   }
   ```

3. **题解作者：李至擎**（4★）
   - 亮点：详细解释二分边界设定原理，强调long long的重要性
   - 代码特点：使用递归式二分结构，适合Pascal学习者参考

---

### 关键实现技巧

1. **循环终止条件**：当v/k^i=0时停止（等价于k^i >v）
2. **溢出预防**：使用unsigned long long类型存储累加值
3. **二分优化**：将右界设为n而非1e9，减少无效搜索

```cpp
// 典型二分框架
int l = 1, r = n;
while (l < r) {
    int mid = (l + r) / 2;
    if (check(mid)) r = mid;
    else l = mid + 1;
}
```

---

### 拓展应用

类似问题可考虑：
1. 二分答案+数学公式验证的组合
2. 几何级数相关的分治问题
3. 向下取整特性的应用

**推荐练习**：
1. [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)
2. [P1873 砍树](https://www.luogu.com.cn/problem/P1873)
3. [P1678 烦恼的高考志愿](https://www.luogu.com.cn/problem/P1678)

---

### 题解心得摘录

1. "当k=1时要特判，否则会进入死循环"（fls233666调试经验）
2. "v的初始值包含在总和中，check函数要先sum = v"（李至擎代码注释）
3. "使用mid=(r-l)/2+l而非(l+r)/2可防止整数溢出"（zxh923实现技巧）

---
处理用时：49.05秒