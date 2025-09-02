# 题目信息

# Yuhao and a Parenthesis

## 题目描述

One day, Yuhao came across a problem about checking if some bracket sequences are correct bracket sequences.

A bracket sequence is any non-empty sequence of opening and closing parentheses. A bracket sequence is called a correct bracket sequence if it's possible to obtain a correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, the sequences "(())()", "()" and "(()(()))" are correct, while the bracket sequences ")(", "(()" and "(()))(" are not correct.

Yuhao found this problem too simple for him so he decided to make the problem harder. You are given many (not necessarily correct) bracket sequences. The task is to connect some of them into ordered pairs so that each bracket sequence occurs in at most one pair and the concatenation of the bracket sequences in each pair is a correct bracket sequence. The goal is to create as many pairs as possible.

This problem unfortunately turned out to be too difficult for Yuhao. Can you help him and solve it?

## 说明/提示

In the first example, it's optimal to construct two pairs: "(( )())" and "( )".

## 样例 #1

### 输入

```
7
)())
)
((
((
(
)
)
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
(
((
(((
(())
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
(())
()
```

### 输出

```
1
```

# AI分析结果

### 题目内容重写
# Yuhao和括号

## 题目描述

有一天，Yuhao遇到了一个关于检查某些括号序列是否为正确括号序列的问题。

一个括号序列是由任意非空的开括号和闭括号组成的序列。如果一个括号序列可以通过插入字符"+"和"1"来形成一个正确的算术表达式，那么它被称为一个正确的括号序列。例如，序列"(())()", "()"和"(()(()))"是正确的，而序列")(", "(()"和"(()))("则不是正确的。

Yuhao觉得这个问题对他来说太简单了，所以他决定让问题变得更难。你被给出了许多（不一定是正确的）括号序列。任务是将其中一些序列连接成有序对，使得每个括号序列最多出现在一个对中，并且每对中的括号序列的串联是一个正确的括号序列。目标是创建尽可能多的对。

这个问题对Yuhao来说太难了。你能帮助他解决这个问题吗？

## 说明/提示

在第一个例子中，最优的构造是两个对："(( )())"和"( )"。

## 样例 #1

### 输入

```
7
)())
)
((
((
(
)
)
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
(
((
(((
(())
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
(())
()
```

### 输出

```
1
```

### 算法分类
字符串

### 题解分析与结论
题目要求将多个括号序列配对，使得每对序列的串联是一个正确的括号序列，并且要最大化配对的数量。核心思路是通过计算每个序列的净余括号数量，然后根据净余括号数量进行配对。

### 所选高分题解
#### 题解1：Zechariah (5星)
**关键亮点**：
- 通过前缀和计算净余括号数量，使用桶记录不同净余值的序列数量。
- 特别处理净余为0的序列，直接计算其配对数量。
- 代码实现简洁高效，逻辑清晰。

**核心代码**：
```cpp
rg int n = fast_IO::read(), tot = 0;
for (rg int i = 1; i <= n; ++i)
{
    rg string t; cin >> t;
    rg int len = 0, top = 0; tt[1] = 0;
    for (rg int j = 0; j != t.size(); ++j)
    {
        if (t[j] == '(')++top;
        else if (top)--top;
        else tt[++len] = ')';
    }
    while (top--)tt[++len] = '(';
    if (tt[1] == ')'&&tt[len] == '(')continue;
    for (rg int j = 1; j <= len; ++j)a[i] += tt[j] == '(' ? 1 : -1;
    a[i] += 500000;
    if (a[i] > 500000)++tong[a[i]]; else if (a[i] < 500000)++tong2[a[i]];
    else ++tot;
}
rg int l = 500000 - 1, r = 500000 + 1;
rg ll ans = ((ll)tot >> 1);
while (l >= 0)
{
    ans += fast_IO::min(tong[r], tong2[l]);
    --l; ++r;
}
fast_IO::write(ans);
```

#### 题解2：TPJX (4星)
**关键亮点**：
- 使用哈希表记录净余括号数量为正和为负的序列数量。
- 通过遍历哈希表计算配对数量，逻辑清晰。
- 代码简洁，易于理解。

**核心代码**：
```cpp
int main() {
    int n;
    cin >> n;
    string s;
    unordered_map<int, int> start, end;
    int vld = 0; 
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int bal = 0, min_bal = 0;
        for (char c : s) {
            if (c == '(') bal++;
            else bal--;
            min_bal = min(min_bal, bal);
        }
        if (bal == 0 && min_bal >= 0) vld++;
        else if (bal > 0 && min_bal >= 0) 
            start[bal]++;
        else if (bal < 0 && min_bal >= bal) 
            end[-bal]++;
    }
    int pairs = vld / 2;
    for (auto p : start) {
        int b = p.first, cnt = p.second;
        pairs += min(cnt, end[b]);
    }
    cout << pairs << endl;
    return 0;
}
```

### 最优关键思路
- **净余括号计算**：通过计算每个序列的净余括号数量，将序列分类为正净余、负净余和净余为0的序列。
- **配对策略**：正净余序列与负净余序列进行配对，净余为0的序列直接计算配对数量。
- **数据结构**：使用哈希表或桶记录不同净余值的序列数量，便于快速查找和配对。

### 可拓展之处
- **类似问题**：可以扩展到其他类型的括号匹配问题，如多种括号混合匹配。
- **算法优化**：可以考虑使用更高效的数据结构来优化配对过程，如平衡树。

### 推荐题目
1. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
3. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)

---
处理用时：36.04秒