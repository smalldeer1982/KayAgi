# 题目信息

# Measuring Lengths in Baden

## 题目描述

Lengths are measures in Baden in inches and feet. To a length from centimeters it is enough to know that an inch equals three centimeters in Baden and one foot contains 12 inches.

You are given a length equal to $ n $ centimeters. Your task is to convert it to feet and inches so that the number of feet was maximum. The result should be an integer rounded to the closest value containing an integral number of inches.

Note that when you round up, 1 cm rounds up to 0 inches and 2 cm round up to 1 inch.

## 样例 #1

### 输入

```
42
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
5
```

### 输出

```
0 2
```

# AI分析结果



# 巴登的长度测量

## 题目描述

在巴登地区，长度的测量使用英寸和英尺。已知1英寸等于3厘米，1英尺等于12英寸。给定一个长度为$n$厘米的物体，将其转换为最大可能的整英尺数和剩余的整英寸数，要求结果四舍五入到最接近的整英寸值。  
特别说明：当四舍五入时，1厘米舍入到0英寸，2厘米舍入到1英寸。

## 样例 #1

### 输入
```
42
```

### 输出
```
1 2
```

## 样例 #2

### 输入
```
5
```

### 输出
```
0 2
```

**算法分类**：数学

---

### 题解综合分析
所有题解核心思路均为先将厘米转换为英寸并进行四舍五入，再计算英尺和英寸。主要差异在于四舍五入的实现方式：

1. **直接加1法**：通过 `(n+1)/3` 利用整数除法特性实现四舍五入（Alex_Wei、Ybocean_s）
2. **浮点运算+修正**：使用 `floor(n/3.0 + 0.5)` 进行精确的四舍五入（封禁用户、信守天下）
3. **余数判断法**：根据 `n%3` 的余数单独处理（Zhoumy）

---

### 高分题解推荐

#### 1. Alex_Wei（⭐⭐⭐⭐⭐）
**关键亮点**：通过 `(n+1)/3` 实现四舍五入，代码简洁高效（O(1)时间复杂度）  
**核心思想**：利用整数除法自动向下取整的特性，加1后除法等价于四舍五入
```cpp
int main() {
    int n, c;
    cin >> n;
    c = (n + 1) / 3; // 四舍五入计算总英寸
    cout << c / 12 << " " << c % 12;
}
```

#### 2. 信守天下（⭐⭐⭐⭐）
**关键亮点**：使用 `floor(n/3.0 + 0.5)` 显式四舍五入，适合理解浮点运算机制  
**调试心得**：强调四舍五入必须在厘米转英寸阶段完成，否则后续计算会累积误差
```cpp
int main() {
    int n = 42;
    int m = floor(n / 3.0 + 0.5); // 显式四舍五入
    cout << m / 12 << " " << m % 12;
}
```

---

### 最优思路总结
**核心技巧**：`(n + 1) / 3` 通过整数运算实现四舍五入，避免浮点运算的精度问题  
**算法优势**：代码简洁、运算高效（无需类型转换和函数调用）  
**思维启示**：利用数值特性简化条件判断，如通过数学变换将除法与取整结合

---

### 拓展练习
1. [P1021 邮票面值设计](https://www.luogu.com.cn/problem/P1021) - 数学构造与进制转换  
2. [P1051 谁拿了最多奖学金](https://www.luogu.com.cn/problem/P1051) - 条件判断与数值处理  
3. [P1426 小鱼会有危险吗](https://www.luogu.com.cn/problem/P1426) - 区间计算与临界值处理

---

### 题解心得摘录
- **封禁用户**：  
  "四舍五入时需注意`floor`和`ceil`的特性，负数与正数处理方式不同"  
- **CSP_Sept**：  
  "手写四舍五入函数更通用，避免依赖C++11的`round`函数"  
- **Zhoumy**：  
  "通过余数直接判断是否进位，减少计算步骤"

---
处理用时：38.66秒