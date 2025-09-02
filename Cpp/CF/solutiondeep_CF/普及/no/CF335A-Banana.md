# 题目信息

# Banana

## 题目描述

Piegirl is buying stickers for a project. Stickers come on sheets, and each sheet of stickers contains exactly $ n $ stickers. Each sticker has exactly one character printed on it, so a sheet of stickers can be described by a string of length $ n $ . Piegirl wants to create a string $ s $ using stickers. She may buy as many sheets of stickers as she wants, and may specify any string of length $ n $ for the sheets, but all the sheets must be identical, so the string is the same for all sheets. Once she attains the sheets of stickers, she will take some of the stickers from the sheets and arrange (in any order) them to form $ s $ . Determine the minimum number of sheets she has to buy, and provide a string describing a possible sheet of stickers she should buy.

## 说明/提示

In the second example, Piegirl can order 3 sheets of stickers with the characters "nab". She can take characters "nab" from the first sheet, "na" from the second, and "a" from the third, and arrange them to from "banana".

## 样例 #1

### 输入

```
banana
4
```

### 输出

```
2
baan
```

## 样例 #2

### 输入

```
banana
3
```

### 输出

```
3
nab
```

## 样例 #3

### 输入

```
banana
2
```

### 输出

```
-1
```

# AI分析结果



【中文题目重写】

# Banana

## 题目描述

Piegirl 正在为项目购买贴纸。贴纸以纸张形式出售，每张纸恰好包含 $n$ 张贴纸。每张贴纸印有一个字符，因此一张纸可以用长度为 $n$ 的字符串描述。Piegirl 希望用这些贴纸拼出字符串 $s$。她可以购买任意数量的纸张，且所有纸张的字符排列必须完全相同。确定需要购买的最小纸张数，并给出一种可行的纸张设计方案。若无法完成，输出 `-1`。

## 说明/提示

样例2解释：购买3张"nab"纸张，可拆解出"nab"+"na"+"a"得到"banana"。

## 输入输出样例（略）

【算法分类】
构造、贪心

【题解对比与分析】

两位题解均采用贪心策略结合优先队列实现，核心思路为：
1. 统计字符频率，若不同字符数 >n 直接无解
2. 初始时每个字符在纸张中至少出现1次
3. 剩余位置优先分配给使当前最大需求降低最多的字符
4. 使用优先队列维护字符需求优先级

sysong的题解（★★★★☆）：
- 亮点：结构体封装字符状态，代码结构清晰，正确实现余数处理
- 关键结构：`ch::st()` 计算当前需求，优先队列比较该值
- 代码实现：通过字符拼接直接构造答案字符串

A_small_WA的题解（★★★★☆）：
- 亮点：使用pair简化实现，直接维护需求值
- 注意点：显式处理余数对需求值的影响
- 不足：变量命名和注释略简

【最优题解关键代码】

sysong的核心实现：
```cpp
struct ch{
    int k,a; // 总需求数，当前分配数
    char c;
    int st(){ return (k-1)/a +1; } // 关键：正确计算需求
};
priority_queue<ch> q;

// 分配剩余位置
for(n-=q.size();n;--n){
    ch c=q.top(); q.pop();
    c.a++; // 增加当前字符分配数
    q.push(c);
}
// 最终需求最大值即为答案
```

【拓展与总结】
- 同类问题：任务调度中机器负载均衡、合并果子问题（洛谷P1090）
- 优化思维：动态维护最值场景优先考虑优先队列
- 注意点：初始必须包含所有字符，余数处理需准确

【推荐习题】
1. P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）
2. P4059 [代码联赛]爸爸的游戏（字符分配优化）
3. P1233 木棍加工（二维贪心优化）

---
处理用时：76.99秒