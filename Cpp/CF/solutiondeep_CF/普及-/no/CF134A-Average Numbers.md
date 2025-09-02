# 题目信息

# Average Numbers

## 题目描述

You are given a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Find all such indices $ i $ , that the $ i $ -th element equals the arithmetic mean of all other elements (that is all elements except for this one).

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1
3 ```

## 样例 #2

### 输入

```
4
50 50 50 50
```

### 输出

```
4
1 2 3 4 ```

# AI分析结果



# Average Numbers

## 题目描述

给定一个正整数序列 $a_{1},a_{2},...,a_{n}$，找出所有满足条件的索引 $i$，使得第 $i$ 个元素等于其他所有元素的算术平均值（即除去该元素外的所有元素的平均值）。

## 样例 #1

### 输入
5
1 2 3 4 5

### 输出
1
3 

## 样例 #2

### 输入
4
50 50 50 50

### 输出
4
1 2 3 4 

---

**算法分类**：数学

---

### 题解综合分析

各题解核心思路均为计算总和后遍历判断，差异主要体现在避免浮点精度误差的数学处理方式。最优解法通过代数变形将判断式转换为整数运算，有效规避了浮点误差问题。

---

### 精选题解（4星以上）

#### 1. 清清老大（5星）
**关键亮点**：  
- 通过数学变形将判断条件转化为整数运算：$n \times a_i = sum$
- 完全规避浮点数精度问题  
- 代码简洁高效，时间复杂度 O(n)

**核心代码**：
```cpp
int sum = 0;
for(int i=1; i<=n; i++) sum += a[i];
for(int i=1; i<=n; i++)
    if(a[i] * n == sum) // 整数运算判断
```

#### 2. cyrxdzj（4星）
**关键亮点**：  
- 提前判断sum是否被n整除以过滤无效情况  
- 使用整数除法减少计算量  
- 包含特殊情况的提前返回优化

**核心代码**：
```cpp
average = sum/n; // 仅当sum%n==0时进行后续判断
if(sum%n != 0) {
    printf("0\n");
    return 0;
}
```

#### 3. 2132B（4星）
**关键亮点**：  
- 显式类型转换保证浮点运算准确性  
- 双重循环结构清晰易读  
- 正确处理全零输出的格式

**核心代码**：
```cpp
double sum = 0;
for(int i=1; i<=n; i++)
    if(a[i] == sum/n) // 显式浮点转换
```

---

### 最优思路提炼
**关键技巧**：  
将判断条件转化为整数运算：  
$$ a_i = \frac{sum - a_i}{n-1} \Rightarrow n \times a_i = sum $$  
该变形消除了分母，避免浮点运算，同时将时间复杂度稳定在 O(n)。

---

### 同类拓展题目
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036) - 组合数求和判断质数  
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044) - 数学递推关系应用  
3. [P1051 谁拿了最多奖学金](https://www.luogu.com.cn/problem/P1051) - 多条件数学计算

---

### 题解心得摘录
- **cyrxdzj**：  
  "当sum无法被n整除时直接返回0，节省后续无效判断"  
- **氷スイカ233**：  
  "UKE问题源于浮点精度处理不当，改用整数运算后解决"  
- **hensier**：  
  "必须加1.0强制类型转换，否则整数除法会导致判断错误"  

---

### 核心实现代码
```cpp
// 最优解法核心代码
#include<bits/stdc++.h>
using namespace std;
int a[200010], sum;

int main() {
    int n, cnt = 0;
    cin >> n;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    vector<int> ans;
    for(int i=1; i<=n; i++) {
        if(a[i] * n == sum) // 整数运算判断
            ans.push_back(i);
    }
    cout << ans.size() << endl;
    for(int x : ans) cout << x << " ";
}
```

---
处理用时：45.93秒