# 题目信息

# Robot Bicorn Attack

## 题目描述

Vasya plays Robot Bicorn Attack.

The game consists of three rounds. For each one a non-negative integer amount of points is given. The result of the game is the sum of obtained points. Vasya has already played three rounds and wrote obtained points one by one (without leading zeros) into the string $ s $ . Vasya decided to brag about his achievement to the friends. However, he has forgotten how many points he got for each round. The only thing he remembers is the string $ s $ .

Help Vasya to find out what is the maximum amount of points he could get. Take into account that Vasya played Robot Bicorn Attack for the first time, so he could not get more than 1000000 ( $ 10^{6} $ ) points for one round.

## 说明/提示

In the first example the string must be split into numbers 1, 2 and 34.

In the second example the string must be split into numbers 90, 0 and 0.

In the third example the string is incorrect, because after splitting the string into 3 numbers number 00 or 09 will be obtained, but numbers cannot have leading zeroes.

## 样例 #1

### 输入

```
1234
```

### 输出

```
37
```

## 样例 #2

### 输入

```
9000
```

### 输出

```
90
```

## 样例 #3

### 输入

```
0009
```

### 输出

```
-1
```

# AI分析结果



# Robot Bicorn Attack

## 题目描述

Vasya 在玩《机器双角兽攻击》游戏。游戏由三轮组成，每轮获得非负整数点数，总分为三轮得分之和。Vasya 将三轮得分按顺序（无前导零）拼接成字符串 $s$，但忘记各轮具体得分。请根据该字符串计算可能的最大总分，要求每轮得分不超过 $10^6$。

## 样例

### 样例 #1
输入：`1234`  
输出：`37`  
解释：拆分为 1 + 2 + 34 = 37

### 样例 #2
输入：`9000`  
输出：`90`  
解释：拆分为 90 + 0 + 0 = 90

### 样例 #3
输入：`0009`  
输出：`-1`  
解释：无法合法拆分

---

### 算法分类
枚举

---

## 题解综合分析

所有题解均采用暴力枚举两个分割点的思路，核心差异在于：
1. **前导零处理**：通过判断子串首字符为0且长度>1来过滤
2. **数值越界处理**：在转换时实时判断是否超过1e6
3. **优化手段**：部分题解提前过滤总长度>21的情况（3*7位）

---

## 精选题解（评分≥4星）

### 题解1 - Rosmarinus（4.5星）
**亮点**：
- 函数式处理数值转换与边界检查
- 清晰的分割点枚举逻辑
- 直接返回非法值进行过滤

```cpp
int f(int l, int r) {
    int t = 0;
    for(int i = l; i <= r; i++) {
        t = t * 10 + s[i] - '0';
        if(t > 1e6) return -99999999; // 越界标记
    }
    return (s[l] == '0' && l != r) ? -99999999 : t; // 前导零检查
}
```

### 题解2 - Dongliang1（4星）
**亮点**：
- 将字符串转为数组处理
- 使用独立检查函数
- 分段式逻辑判断

```cpp
int check(int l, int r) {
    if(a[l] == 0 && l != r) return -1; // 前导零判断
    int sum = 0;
    for(int i = l; i <= r; i++) {
        sum = sum * 10 + a[i];
        if(sum > 1e6) return -1; // 实时越界检查
    }
    return sum;
}
```

### 题解3 - VitrelosTia（4星）
**心得亮点**：
- 使用substr切割字符串
- 单独转换函数处理边界
- 强调数值转换时可能溢出的问题

```cpp
int f(string s) {
    if(s[0] == '0' && s.size() > 1) return -1;
    int ans = 0;
    for(auto ch : s) {
        ans = ans * 10 + ch - '0';
        if(ans > 1e6) return -1;
    }
    return ans;
}
```

---

## 关键思路总结
1. **分割点枚举**：两层循环枚举两个分割点（时间复杂度O(n²)）
2. **实时转换检查**：在字符串转数值时实时判断是否超过1e6
3. **前导零处理**：允许单个0但禁止多位数前导零
4. **优化技巧**：当总长度>21时直接返回-1（3×7=21）

---

## 拓展应用
类似题目可考虑：
1. 字符串分割为不同段数
2. 附加更多数值限制条件
3. 求分割方式数量而非极值

---

## 推荐练习题
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 二维枚举覆盖
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012) - 字符串组合排序
3. [P1022 计算器的改良](https://www.luogu.com.cn/problem/P1022) - 字符串解析与方程处理

---
处理用时：78.07秒