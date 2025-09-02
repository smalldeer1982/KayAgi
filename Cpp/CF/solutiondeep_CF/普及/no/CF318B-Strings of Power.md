# 题目信息

# Strings of Power

## 题目描述

Volodya likes listening to heavy metal and (occasionally) reading. No wonder Volodya is especially interested in texts concerning his favourite music style.

Volodya calls a string powerful if it starts with "heavy" and ends with "metal". Finding all powerful substrings (by substring Volodya means a subsequence of consecutive characters in a string) in a given text makes our hero especially joyful. Recently he felt an enormous fit of energy while reading a certain text. So Volodya decided to count all powerful substrings in this text and brag about it all day long. Help him in this difficult task. Two substrings are considered different if they appear at the different positions in the text.

For simplicity, let us assume that Volodya's text can be represented as a single string.

## 说明/提示

In the first sample the string "heavymetalisheavymetal" contains powerful substring "heavymetal" twice, also the whole string "heavymetalisheavymetal" is certainly powerful.

In the second sample the string "heavymetalismetal" contains two powerful substrings: "heavymetal" and "heavymetalismetal".

## 样例 #1

### 输入

```
heavymetalisheavymetal
```

### 输出

```
3```

## 样例 #2

### 输入

```
heavymetalismetal
```

### 输出

```
2```

## 样例 #3

### 输入

```
trueheavymetalissotruewellitisalsosoheavythatyoucanalmostfeeltheweightofmetalonyou
```

### 输出

```
3```

# AI分析结果



# 题目中文翻译

# 强字符串

## 题目描述

Volodya 喜欢听重金属音乐，偶尔也喜欢阅读。因此他对涉及重金属音乐风格的文本特别感兴趣。

Volodya 将满足以下条件的字符串称为强字符串：以 "heavy" 开头并以 "metal" 结尾。帮助他统计给定文本中所有满足条件的子串数量（子串必须由连续字符组成）。不同位置的子串视为不同。

## 说明/提示

样例1中字符串 "heavymetalisheavymetal" 包含两次 "heavymetal" 作为强子串，同时整个字符串本身也是强子串。

样例2中字符串 "heavymetalismetal" 包含两个强子串："heavymetal" 和 "heavymetalismetal"。

## 样例 #1

### 输入
`heavymetalisheavymetal`

### 输出
`3`

## 样例 #2

### 输入
`heavymetalismetal`

### 输出
`2`

# 算法分类
**字符串/递推**

# 题解分析与结论

### 核心思路
通过线性扫描维护前缀 "heavy" 的计数器，每个 "metal" 出现时将当前计数器累加到答案。时间复杂度 O(n)，空间 O(1)。

### 关键技巧
1. **前缀累加机制**：每个 "metal" 的贡献值为其前方所有 "heavy" 的数量
2. **子串快速匹配**：使用 substr 或字符逐位比较快速识别关键词
3. **数据类型控制**：使用 long long 避免计数器溢出

---

# 精选题解

## 作者：_tommysun_（⭐⭐⭐⭐⭐）
**亮点**  
• 代码简洁直观，使用标准库函数  
• 逻辑清晰体现核心算法思想  
**代码核心**  
```cpp
for (int i=0;i+4<s.size();i++) {
    sub=s.substr(i,5);
    if (sub=="heavy") heavy++;
    if (sub=="metal") ans += heavy;
}
```

## 作者：_Jonny_404（⭐⭐⭐⭐）
**亮点**  
• 通过错误案例展示思维过程，强化顺序概念  
• 手动字符比较提升运行效率  
**调试心得**  
> "发现 metal 出现在 heavy 前会导致错误匹配，修正为动态累加前序 heavy 数"

## 作者：Zaku（⭐⭐⭐⭐）
**亮点**  
• 新手友好型注释说明  
• 强调数据范围隐患  
**警语**  
> "不开 long long 见祖宗！"  

---

# 同类题目推荐
1. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102)  
   - 相似点：前缀计数与差值统计
2. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)  
   - 相似点：滑动窗口与子串特征统计
3. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)  
   - 相似点：区间贡献值累计计算

---
处理用时：62.88秒