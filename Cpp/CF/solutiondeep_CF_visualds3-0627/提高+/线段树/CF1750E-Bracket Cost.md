# 题目信息

# Bracket Cost

## 题目描述

Daemon Targaryen decided to stop looking like a Metin2 character. He turned himself into the most beautiful thing, a bracket sequence.

For a bracket sequence, we can do two kind of operations:

- Select one of its substrings $ ^\dagger $ and cyclic shift it to the right. For example, after a cyclic shift to the right, "(())" will become ")(()";
- Insert any bracket, opening '(' or closing ')', wherever you want in the sequence.

We define the cost of a bracket sequence as the minimum number of such operations to make it balanced $ ^\ddagger $ .

Given a bracket sequence $ s $ of length $ n $ , find the sum of costs across all its $ \frac{n(n+1)}{2} $ non-empty substrings. Note that for each substring we calculate the cost independently.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

 $ ^\ddagger $ A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters $ + $ and $ 1 $ . For example, sequences "(())()", "()", and "(()(()))" are balanced, while ")(", "(()", and "(()))(" are not.

## 说明/提示

In the first test case, there is the only substring ")". Its cost is $ 1 $ because we can insert '(' to the beginning of this substring and get a string "()", that is a balanced string.

In the second test case, the cost of each substring of length one is $ 1 $ . The cost of a substring ")(" is $ 1 $ because we can cyclically shift it to right and get a string "()". The cost of strings ")()" and "()(" is $ 1 $ because its enough to insert one bracket to each of them. The cost of substring ")()(" is $ 1 $ because we can cyclically shift it to right and get a string "()()". So there are $ 4 + 2 + 2 + 1 = 9 $ substring of cost $ 1 $ and $ 1 $ substring of cost $ 0 $ . So the sum of the costs is $ 9 $ .

In the third test case,

- "(", the cost is $ 1 $ ;
- "()", the cost is $ 0 $ ;
- "())", the cost is $ 1 $ ;
- ")", the cost is $ 1 $ ;
- "))", the cost is $ 2 $ ;
- ")", the cost is $ 1 $ .

So the sum of the costs is $ 6 $ .

## 样例 #1

### 输入

```
5
1
)
4
)()(
3
())
5
(((((
10
)(())))())```

### 输出

```
1
9
6
35
112```

# AI分析结果



---

## 算法分类
**前缀和与数学变换**

---

## 综合分析与结论

### 核心思路
每个子串的 cost 定义为使其平衡的最小操作次数，可拆解为 `max(L,R) - X`，其中：
- `L/R` 为子串中左/右括号数
- `X` 为已有匹配括号对数

通过数学变换 `max(L,R) = (L+R + |L-R|)/2`，将问题分解为三部分求和：
1. **所有子串的 L+R 总和**：即各子串长度之和
2. **所有子串的 |L-R| 总和**：通过前缀和数组排序后线性计算
3. **所有匹配括号对的 X 总和**：利用栈维护括号匹配

### 难点解析
1. **绝对值项求和**：  
   将前缀和数组排序后，利用 `Σ(i*a[i] - 前缀和)` 快速计算所有子串的绝对值和。
2. **匹配括号贡献计算**：  
   用栈记录左括号位置，当遇到右括号时统计 `(左括号位置+1) * (右括号右侧长度)` 作为该对括号的贡献。

### 可视化设计
- **动画方案**：  
  1. 在 Canvas 上绘制前缀和曲线，动态展示排序过程
  2. 高亮当前操作的括号对，用不同颜色标记已匹配的括号
  3. 步进控制：可单步查看栈操作和前缀和计算
- **复古风格**：  
  1. 使用 8-bit 音效：匹配成功时播放 "ping"，错误时播放 "buzz"
  2. 像素化展示前缀和数组排序前后的对比
  3. 积分系统：每正确统计一个括号对得 10 分

---

## 题解清单（≥4星）

1. **dottle（5星）**  
   - 亮点：数学推导清晰，线性时间完成所有计算  
   - 代码简洁，巧妙利用排序优化绝对值计算

2. **MSqwq（4星）**  
   - 亮点：详细推导公式，代码结构清晰  
   - 不足：部分变量命名不够直观

---

## 最优思路提炼

### 关键技巧
1. **前缀和转换**：将括号序列转换为 ±1 序列，前缀和数组反映括号平衡度
2. **排序优化绝对值求和**：通过排序将绝对值和转化为线性计算
3. **栈维护匹配对**：实时记录未匹配左括号，快速计算匹配贡献

### 代码实现
```cpp
// 核心代码：dottle 题解的关键片段
vector<int> a(1); // 前缀和数组
int sum = 0;
for(int i=0; i<n; i++){
    sum += (s[i]=='(' ? 1 : -1);
    a.push_back(sum);
}
sort(a.begin(), a.end());

// 计算绝对值和
int res = 0, ns = 0;
for(int i=0; i<=n; i++){
    res += i*a[i] - ns; // |L-R| 部分
    res += i*(n-i+1);   // L+R 部分
    ns += a[i];
}
res /= 2;

// 计算匹配括号贡献
stack<int> stk;
for(int i=0; i<n; i++){
    if(s[i] == '(') stk.push(i);
    else if(!stk.empty()){
        res -= (stk.top()+1) * (n - i);
        stk.pop();
    }
}
```

---

## 相似题目推荐
1. **CF3D Least Cost Bracket Sequence**（平衡括号最小代价）
2. **LeetCode 32. Longest Valid Parentheses**（最长有效括号子串）
3. **洛谷 P5658 括号树**（树形结构括号匹配）

---

## 个人心得摘录
> "比赛时卡在绝对值项的计算，看到排序后线性求解的解法，瞬间顿悟数学变换的精妙。" —— dottle

---

## 同类型题套路
- **前缀和+单调性**：处理区间和绝对值时，排序或单调栈是常用优化手段
- **括号匹配模板**：栈维护未匹配括号，时空复杂度均为 O(n)
- **贡献法拆分**：将复杂公式拆解为可独立计算的子项

---
处理用时：88.99秒