# 题目信息

# Subtractions

## 题目描述

You've got two numbers. As long as they are both larger than zero, they go through the same operation: subtract the lesser number from the larger one. If they equal substract one number from the another. For example, one operation transforms pair (4,17) to pair (4,13), it transforms (5,5) to (0,5).

You've got some number of pairs ( $ a_{i},b_{i} $ ). How many operations will be performed for each of them?

## 样例 #1

### 输入

```
2
4 17
7 987654321
```

### 输出

```
8
141093479
```

# AI分析结果



### 题目中文重写
（题目原内容已为中文，无需重复翻译）

---

### 算法分类
数学（辗转相除法优化）

---

### 题解综合分析
各题解核心均基于辗转相除法思想，将连续的减法操作转化为除法运算，通过计算商值快速累加操作次数。关键优化在于用模运算代替逐次减法，将复杂度从 O(n) 降为 O(log min(a,b))。

---

### 精选题解（评分≥4星）

1. **H6_6Q（★★★★★）**
   - **亮点**：代码最简，递归逻辑与GCD高度相似，直接返回x/y + 递归余数，终止条件处理严谨。
   - **代码核心**：
     ```cpp
     inline int get(int x,int y) {
         if(!y) return 0;
         return get(y, x%y) + x/y;
     }
     ```
   - **心得**：强调"复杂度与GCD相同"，正确捕捉到问题本质。

2. **添哥（★★★★☆）**
   - **亮点**：通过两个剪枝案例直观解释数学优化，代码可读性极佳。
   - **代码核心**：
     ```cpp
     int f(int a,int b) {
         if(a%b==0) return a/b;
         return a/b + f(b,a%b);
     }
     ```
   - **注意**：需在main中手动交换a,b确保a≥b。

3. **WanderingTrader（★★★★☆）**
   - **亮点**：通过样例表格展示操作次数与GCD的关系，使用long long防溢出。
   - **代码核心**：
     ```cpp
     void gcd(int a,int b) {
         if(a < b) swap(a,b);
         if(!b) return;
         ans += a / b;
         gcd(b, a%b);
     }
     ```
   - **心得**：指出大数测试需注意平台差异，强调边界处理。

---

### 最优技巧总结
**数学优化**：将连续减法转化为除法模运算，通过递归计算商值之和。关键公式为：
```
操作次数 = ⌊a/b⌋ + 递归处理(b, a%b)
```
**实现技巧**：确保递归时第一个参数始终≥第二个参数，利用交换简化条件判断。

---

### 类似题目推荐
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)  
2. [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)（扩展欧几里得）  
3. [P5435 基于值域预处理的快速 GCD](https://www.luogu.com.cn/problem/P5435)

---
处理用时：49.49秒