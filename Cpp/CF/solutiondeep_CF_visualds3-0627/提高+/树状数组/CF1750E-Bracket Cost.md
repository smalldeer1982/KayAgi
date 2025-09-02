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
**前缀和与排序、栈应用**

---

## 题解思路与难点分析

### **核心公式推导**
所有子串的代价可拆分为：  
`总代价 = Σ(max(L,R) - X)`  
其中：
- `max(L,R)`：子串中左右括号数量的较大值  
- `X`：子串中已匹配的括号对数  

**关键分解**：
1. **max(L,R) 的拆分**：  
   `max(L,R) = (L+R + |L-R|)/2`  
   - `L+R` 为子串长度，总和可通过等差数列求和公式计算  
   - `|L-R|` 转化为前缀和的绝对值之和，通过排序前缀和数组高效计算  

2. **X 的计算**：  
   利用栈匹配原串中的括号对，统计每对括号在所有子串中的贡献次数  

### **实现难点与优化**
- **绝对值部分的高效计算**：  
  将前缀和数组排序后，利用有序性质快速计算每对前缀和的差值之和  
- **已匹配括号对的统计**：  
  栈记录左括号位置，遇到右括号时弹出并计算该对的贡献 `(左位置+1) * (n - 右位置)`  

### **对比题解**
- **dottle 的题解**：  
  - 思路清晰，直接拆解公式，利用排序和栈实现 O(n) 时间复杂度  
  - 代码简洁，仅需一次排序和栈遍历  
- **lkytxdy 的题解**：  
  - 使用单调栈处理前缀和的最小值，计算复杂但同样高效  
  - 更适合处理更复杂的前缀和极值问题  

---

## 题解评分（≥4星）

1. **dottle 的题解（★★★★★）**  
   - **亮点**：公式拆解直观，代码简洁高效，时间复杂度最优  
   - **代码可读性**：结构清晰，关键步骤注释明确  

2. **MSqwq 的题解（★★★★☆）**  
   - **亮点**：详细推导公式，结合前缀和与栈的实践  
   - **优化点**：代码稍显冗长，但逻辑完整  

3. **lkytxdy 的题解（★★★★☆）**  
   - **亮点**：单调栈处理极值，提供另一种计算视角  
   - **适用场景**：需要处理区间极值的类似问题  

---

## 最优思路提炼

### **核心步骤**
1. **前缀和预处理**：  
   将括号序列转换为前缀和数组（左括号+1，右括号-1）  
2. **计算 Σ|L-R|**：  
   排序前缀和数组，利用有序性质快速计算所有区间差的绝对值之和  
3. **计算 ΣX**：  
   用栈匹配原串中的括号对，累加每对括号的贡献次数  

### **代码片段**
```cpp
// 计算前缀和并排序
vector<int> a(1);
int sum = 0;
for (char c : s) {
    sum += (c == '(' ? 1 : -1);
    a.push_back(sum);
}
sort(a.begin(), a.end());

// 计算排序后的绝对值部分总和
int res = 0, ns = 0;
for (int i = 0; i <= n; i++) {
    res += i * a[i] - ns;
    ns += a[i];
}
res /= 2;

// 栈统计已匹配括号对
stack<int> stk;
for (int i = 0; i < n; i++) {
    if (s[i] == '(') stk.push(i);
    else if (!stk.empty()) {
        res -= (stk.top() + 1) * (n - i);
        stk.pop();
    }
}
```

---

## 类似题目推荐
1. **LeetCode 678. Valid Parenthesis String**  
   （处理通配符的括号匹配问题）  
2. **CodeForces 5C. Longest Regular Bracket Sequence**  
   （求最长合法括号子串及其出现次数）  
3. **洛谷 P1944 最长括号匹配**  
   （利用栈处理最长合法子串）

---

## 可视化设计

### **动画演示方案**
1. **前缀和生成**：  
   - 横向展示原括号序列，下方动态生成前缀和折线图  
   - 颜色标记当前字符（红色为右括号，绿色为左括号）  
2. **排序过程**：  
   - 将前缀和数组元素以柱状图排列，动态排序并高亮交换的元素  
3. **栈匹配过程**：  
   - 栈结构可视化，左括号入栈时弹出动画，匹配时高亮对应括号位置  

### **复古像素风格**
- **颜色方案**：8位色调色板（绿、红、蓝为主）  
- **音效设计**：  
  - 入栈/出栈时播放短促“哔”声  
  - 匹配成功时播放上升音阶  
  - 错误操作（如栈空弹出）时播放低沉音效  

### **交互功能**
- **步进控制**：空格键单步执行，方向键调节速度  
- **自动演示**：AI模式自动运行，展示排序和栈匹配的关键步骤  

---

## 总结
通过拆解公式和高效数据结构，将复杂问题转化为可计算的三个部分。前缀和排序和栈的应用是该题的核心技巧，类似问题可借鉴这种分治统计思想。

---
处理用时：67.08秒