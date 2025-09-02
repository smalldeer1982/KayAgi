# 题目信息

# Bear and Strings

## 题目描述

The bear has a string $ s=s_{1}s_{2}...\ s_{|s|} $ (record $ |s| $ is the string's length), consisting of lowercase English letters. The bear wants to count the number of such pairs of indices $ i,j $ $ (1<=i<=j<=|s|) $ , that string $ x(i,j)=s_{i}s_{i+1}...\ s_{j} $ contains at least one string "bear" as a substring.

String $ x(i,j) $ contains string "bear", if there is such index $ k $ $ (i<=k<=j-3) $ , that $ s_{k}=b $ , $ s_{k+1}=e $ , $ s_{k+2}=a $ , $ s_{k+3}=r $ .

Help the bear cope with the given problem.

## 说明/提示

In the first sample, the following pairs $ (i,j) $ match: $ (1,4),(1,5),(1,6),(1,7),(1,8),(1,9) $ .

In the second sample, the following pairs $ (i,j) $ match: $ (1,4),(1,5),(1,6),(1,7),(1,8),(1,9),(1,10),(1,11),(2,10),(2,11),(3,10),(3,11),(4,10),(4,11),(5,10),(5,11),(6,10),(6,11),(7,10),(7,11) $ .

## 样例 #1

### 输入

```
bearbtear
```

### 输出

```
6
```

## 样例 #2

### 输入

```
bearaabearc
```

### 输出

```
20
```

# AI分析结果



# Bear and Strings

## 题目描述

小熊有一个由小写英文字母组成的字符串 $s = s_1s_2...s_{|s|}$（其中 $|s|$ 表示字符串长度）。小熊想要统计满足以下条件的所有索引对 $(i,j)$（$1 \leq i \leq j \leq |s|$）的数量：子串 $x(i,j) = s_i s_{i+1}...s_j$ 中至少包含一个子串 "bear"。

具体来说，子串 $x(i,j)$ 包含 "bear" 当且仅当存在索引 $k$（$i \leq k \leq j-3$），使得 $s_k = b$，$s_{k+1} = e$，$s_{k+2} = a$，$s_{k+3} = r$。

---

**算法分类**：组合数学

---

### 题解综合分析

所有题解均采用组合数学思想，通过遍历字符串寻找每个"bear"位置，计算其对答案的贡献。核心思路是：
1. **乘法原理**：每个"bear"左侧有`i+1`种起点选择，右侧有`len-i-3`种终点选择。
2. **去重处理**：使用变量记录前一个"bear"的位置，减去重叠区间的重复计算。
3. **线性扫描**：时间复杂度$O(n)$，仅需一次遍历即可完成计算。

---

### 精选题解

#### 1. 作者：nxd_oxm（⭐⭐⭐⭐⭐）
**关键亮点**：
- 图示辅助说明重复区间的处理方法
- 引入`last`变量记录前驱位置，清晰展现去重逻辑
- 代码简洁且变量命名直观

**核心代码**：
```cpp
int ans=0,last=0;
for(int i=0;i+3<a.size();i++){
    if(a.substr(i,4)=="bear"){
        ans += (i+1)*(a.size()-i-3) - last*(a.size()-i-3);
        last = i+1;
    }
}
```

#### 2. 作者：IAKIOI123（⭐⭐⭐⭐）
**关键亮点**：
- 数学公式直击问题本质
- 通过`sum`和`ans`的差值计算展现动态更新过程
- 代码高度精简，无冗余操作

**核心代码**：
```cpp
sum += (i+1)*(len-3-i) - ans*(len-3-i);
ans = i+1;
```

#### 3. 作者：naroto2022（⭐⭐⭐⭐）
**个人心得**：
> "千万千万要去重！"  
> 强调重复计算是本题最大陷阱，通过变量`c`记录前驱位置实现去重。

**代码亮点**：
- 变量`c`命名体现"前驱"含义
- 注释说明每个变量的作用

---

### 最优思路总结
1. **贡献计算**：对每个"bear"位置$i$，其贡献为$(i+1) \times (len-i-3)$，即左侧可扩展起点数 × 右侧可扩展终点数。
2. **重叠处理**：若前一个"bear"结束于位置$p$，则当前需减去$p \times (len-i-3)$，避免重复计算重叠区间的子串。

---

### 拓展应用
类似问题可通过以下模式解决：
1. **逆向思维**：总合法数 = 所有可能数 - 非法数
2. **滑动窗口**：维护合法区间端点，动态计算贡献值
3. **模式匹配**：结合KMP等算法快速定位关键子串

---

### 推荐习题
1. [P2003 最少操作数](https://www.luogu.com.cn/problem/P2003) - 区间贡献计算
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 贪心选择与组合优化
3. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678) - 二分答案与区间处理

---
处理用时：59.84秒