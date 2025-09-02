# 题目信息

# The number on the board

## 题目描述

Some natural number was written on the board. Its sum of digits was not less than $ k $ . But you were distracted a bit, and someone changed this number to $ n $ , replacing some digits with others. It's known that the length of the number didn't change.

You have to find the minimum number of digits in which these two numbers can differ.

## 说明/提示

In the first example, the initial number could be $ 12 $ .

In the second example the sum of the digits of $ n $ is not less than $ k $ . The initial number could be equal to $ n $ .

## 样例 #1

### 输入

```
3
11
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
99
```

### 输出

```
0
```

# AI分析结果



# 板子上的数字

## 题目描述

某个自然数被写在板子上，其各位数字之和不小于 $k$。但当你分心时，有人将这个数改成了 $n$，且位数保持不变。你需要找出这两个数在最少多少位上不同。

## 说明/提示

第一个样例中，原数可能是 $12$。
第二个样例中 $n$ 的数字和已经不小于 $k$，原数可能与 $n$ 相同。

## 样例 #1

### 输入
```
3
11
```

### 输出
```
1
```

## 样例 #2

### 输入
```
3
99
```

### 输出
```
0
```

---

## 题解综合分析

所有题解均采用贪心策略：**优先修改数值最小的位为9**，使得每次操作带来的数字和增量最大化。关键步骤如下：
1. 计算当前数字各位和
2. 若不足则排序各位数字
3. 从小到大依次改为9直到满足条件

### 高星题解推荐

#### 作者：wyk0247（★★★★★）
**核心思路**  
- 直接对字符数组排序，实现贪心修改
- 代码逻辑清晰，包含详细注释
- 正确处理了字符串转数字的边界问题

**关键代码**  
```cpp
sort(a, a+len); // 从小到大排序
for(int i=0; i<len; i++) {
    he += 9 - a[i]; // 每次最大化增加和值
    if(he >= k) break;
    ans = i + 1; // 记录操作次数
}
```

#### 作者：kbzcz（★★★★☆）
**实现亮点**  
- 使用字符直接排序避免额外数组
- 变量命名简洁，循环条件明确
- 代码风格紧凑，适合快速理解

**代码片段**  
```cpp
sort(a+1, a+1+n); // 排序数字位
for(int i=1; i<=n; i++) {
    sum = sum - a[i] + 9; // 直接修改数组元素
    if(sum >= k) return printf("%d",i);
}
```

#### 作者：LegendaryGrandmaster（★★★★☆）
**技巧亮点**  
- 使用绝对值简化差额计算
- 通过字符串操作减少内存占用
- 循环中动态计算差额更直观

**关键逻辑**  
```cpp
c = abs(k - sum); // 计算需要增加的差额
for(int i=0; i<s.size(); i++) {
    c -= (9 - (s[i]-'0')); // 动态更新剩余差额
    if(c <= 0) return cout << i+1;
}
```

---

## 关键技巧总结
1. **贪心排序**：将数字按位从小到大排序，确保每次修改收益最大
2. **字符处理**：直接操作字符串避免大数问题
3. **即时终止**：当满足条件时立即退出循环，提升效率
4. **边界处理**：特判初始和已满足条件的情况

---

## 同类题目推荐
1. P1090 [合并果子] - 贪心+优先队列
2. P1223 [排队接水] - 时间调度贪心
3. P4995 [跳跳！] - 极值交替贪心策略

---

## 调试心得摘录
> "CF的题面真是令人看不懂哇！" —— LiteratureCollege  
> 总结：需仔细分析样例理解题意，明确题目中的"修改次数"指代原数与新数的差异位数，而非直接的操作次数。

> "十年OI一场空，不开long long见祖宗" —— a2358972980  
> 经验：即使题目未明确数据范围，对累加操作仍需注意溢出风险。

> "注意cin后换行符的处理" —— ice_fish01  
> 教训：输入数字后读取字符串时，需清空缓冲区避免读取残留换行符。

---
处理用时：94.73秒