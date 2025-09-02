# 题目信息

# Divisibility by Eight

## 题目描述

You are given a non-negative integer $ n $ , its decimal representation consists of at most $ 100 $ digits and doesn't contain leading zeroes.

Your task is to determine if it is possible in this case to remove some of the digits (possibly not remove any digit at all) so that the result contains at least one digit, forms a non-negative integer, doesn't have leading zeroes and is divisible by 8. After the removing, it is forbidden to rearrange the digits.

If a solution exists, you should print it.

## 样例 #1

### 输入

```
3454
```

### 输出

```
YES
344
```

## 样例 #2

### 输入

```
10
```

### 输出

```
YES
0
```

## 样例 #3

### 输入

```
111111
```

### 输出

```
NO
```

# AI分析结果



# Divisibility by Eight

## 题目描述

给定一个最多有 100 位的非负整数 $n$，其十进制表示不含前导零。判断是否能通过删除若干数字（可以不删除）得到一个不含前导零且能被 8 整除的非负整数。若存在解，输出该数；否则输出 NO。

---

## 题解对比与结论

### 最优题解亮点总结
所有题解均基于关键数学性质：**若数的最后三位能被8整除，则整个数能被8整除**。通过暴力枚举1位、2位、3位组合即可覆盖所有情况。优先处理存在0的特殊情况可大幅简化问题。

#### 关键技巧
1. **分层检查**：优先检查单数字0/8 → 两位组合 → 三位组合
2. **前导零处理**：存在0时直接返回"0"（样例2的特殊处理）
3. **短路返回**：发现可行解立即终止程序，避免无效计算

---

## 精选题解（评分≥4星）

### 1. 灵光一闪（5星）
**核心思路**：  
1. 优先检测是否存在0  
2. 三层循环分别检测3位/2位/1位组合  
3. 保持原数字顺序，确保合法子序列

```cpp
// 核心代码片段
if(s.find('0') < s.size()) { /* 处理0的情况 */ }
for(int i=0; i<s.size(); i++){ // 1位
    if((s[i]-'0')%8 ==0)...
    for(int j=i+1; j<s.size(); j++){ // 2位
        if((组合值)%8 ==0)...
        for(int k=j+1; k<s.size(); k++){ // 3位
            if((组合值)%8 ==0)...
```

**亮点**：代码结构清晰，覆盖所有可能性层，注释说明临界条件处理

---

### 2. FuriousC（4星）
**核心思路**：  
相同数学原理，代码实现更紧凑  
```cpp
// 核心优化点
for(int i=0; i<str.size(); i++) {
    a = 当前数字; // 单数字检查
    for(int j=i+1; j<str.size(); j++) {
        // 两位检查
        for(int k=j+1; k<str.size(); k++) { 
            // 三位检查
```

**亮点**：变量命名清晰，逻辑分层明确，适合快速理解算法流程

---

### 3. 封禁用户（4星）
**创新点**：预生成所有8的倍数，查找子序列  
```cpp
const string mult8[] = {/* 所有8的倍数 */};
for(auto &k : mult8) {
    // 根据k长度进行不同位数匹配
    if(k.length()==1)...
    else if(k.length()==2)... 
    else...
}
```
**亮点**：理论时间复杂度最优，但实现复杂度较高，适合拓展思维

---

## 扩展与总结

### 举一反三
1. **整除3/9**：数字之和的倍数性质  
2. **子序列构造**：如CF977F（最长连续子序列）
3. **数位DP应用**：当位数极大时的动态规划解法

### 推荐习题
1. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217) - 数位处理与数学性质结合  
2. [P1030 求先序排列](https://www.luogu.com.cn/problem/P1030) - 序列子结构处理  
3. [CF550D Regular Bridge](https://codeforces.com/problemset/problem/550/D) - 数论与构造技巧

### 调试心得
1. **前导零陷阱**：样例2的10→0需特殊处理  
2. **短路优化**：发现可行解立即返回，避免超时  
3. **边界测试**：全1序列、末尾三位有效等极端情况  

> "本题本质是数学性质与暴力枚举的完美结合，小学数学知识在算法竞赛中依然大放异彩" —— 灵光一闪题解心得

---
处理用时：59.51秒