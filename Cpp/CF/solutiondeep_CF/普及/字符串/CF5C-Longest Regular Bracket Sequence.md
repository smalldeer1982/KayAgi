# 题目信息

# Longest Regular Bracket Sequence

## 题目描述

This is yet another problem dealing with regular bracket sequences.

We should remind you that a bracket sequence is called regular, if by inserting «+» and «1» into it we can get a correct mathematical expression. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

You are given a string of «(» and «)» characters. You are to find its longest substring that is a regular bracket sequence. You are to find the number of such substrings as well.

## 样例 #1

### 输入

```
)((())))(()())
```

### 输出

```
6 2
```

## 样例 #2

### 输入

```
))(
```

### 输出

```
0 1
```

# AI分析结果

### 题目翻译
# 最长合法括号序列

## 题目描述
这是另一个关于合法括号序列的问题。

我们应该提醒你，如果通过在括号序列中插入 «+» 和 «1» 可以得到一个正确的数学表达式，那么这个括号序列就被称为合法的。例如，序列 «(())()»、«()» 和 «(()(()))» 是合法的，而 «)(»、«(()» 和 «(()))(» 则不是。

给定一个由 «(» 和 «)» 字符组成的字符串。你需要找到它的最长子串，该子串是一个合法的括号序列。同时，你还需要找出这样的子串的数量。

## 样例 #1
### 输入
```
)((())))(()())
```
### 输出
```
6 2
```

## 样例 #2
### 输入
```
))(
```
### 输出
```
0 1
```

### 综合分析与结论
这些题解主要围绕寻找最长合法括号子串及其数量展开，核心在于处理括号匹配问题。思路大致可分为两类：一类是利用栈标记匹配的括号，再求最长连续匹配的括号子串；另一类是运用动态规划，通过记录以每个位置结尾的合法括号序列长度来求解。

### 算法要点与难点对比
1. **栈 + 标记法**：
    - **要点**：用栈存储左括号的位置，遇到右括号时若栈非空则弹出栈顶元素，并标记这对括号匹配成功。最后求标记数组中最长连续的匹配部分。
    - **难点**：准确标记匹配的括号，避免遗漏或错误标记。
2. **动态规划法**：
    - **要点**：定义状态数组（如 `dp[i]` 表示以 `i` 结尾的合法括号序列长度），根据括号匹配情况更新状态数组，同时记录最大长度及其出现次数。
    - **难点**：状态转移方程的推导和理解，特别是处理连续合法括号序列的拼接情况。

### 评分较高的题解
- **LuckyCloud (4星)**：
    - **关键亮点**：思路清晰，通过栈和标记数组的结合，简单直观地解决了问题。代码实现简洁易懂，注释较少但逻辑清晰。
    - **核心代码**：
```cpp
for (int i=0;i<len;i++)
{
    if (s[i]=='(') stack[++top]=i;
    else {if (top){a[stack[top]]=true;a[i]=true;top--;}}
}
for (int i=0;i<=len;i++)
    if (a[i]) w++;
    else {ans=max(w,ans);w=0;}
for (int i=0;i<=len;i++)
    if (a[i]) w++;
    else {if (w==ans)tot++;w=0;}
```
- **linyinuo2008 (4星)**：
    - **关键亮点**：详细分析了题目，明确指出使用线性动规思想，代码结构清晰，变量命名规范，便于理解。
    - **核心代码**：
```cpp
for(i=0;i<len;i++)
{
    if(c[i]=='(')
    {
        p++;
        st[p]=i;
    }
    else
    {
        if(p!=0)
        {
            a[st[p]]=1;
            a[i]=1;
            p--;
        }
    }
}
for(i=0;i<=len;i++)
{
    if(a[i])
    {
        sum++;
    }
    else
    {
        ans=maximum(ans,sum);
        sum=0;
    }
}
for(i=0;i<=len;i++)
{
    if(a[i])
    {
        sum++;
    }
    else
    {
        if(sum==ans)
        {
            num++;
        }
        sum=0;
    }
}
```
- **Loner_Knowledge (4星)**：
    - **关键亮点**：明确指出这是一道动态规划题，通过栈和动态规划数组结合，巧妙地处理了括号匹配和连续合法括号序列的问题。
    - **核心代码**：
```cpp
for(int i=0;s[i];++i) {
    if(s[i]==')') {
        if(!head)
            continue;
        head--;
        ans[i]=i-sta[head]+1+ans[sta[head]-1];
        if(ans1==ans[i])
            ans2++;
        else if(ans1<ans[i]) {
            ans1=ans[i];
            ans2=1;
        }
    }
    else
        sta[head++]=i;
}
```

### 最优关键思路或技巧
- **栈的运用**：栈是处理括号匹配问题的常用数据结构，通过栈可以方便地找到匹配的括号对。
- **标记数组**：使用标记数组记录匹配的括号，将问题转化为求最长连续的匹配部分，简化了问题的处理。
- **动态规划**：通过定义状态数组和状态转移方程，能够高效地处理连续合法括号序列的拼接情况。

### 可拓展之处
同类型题如包含多种括号（如 `[]`、`{}` 等）的匹配问题，或要求找出所有合法括号子串的问题。类似算法套路可用于处理其他匹配问题，如字符串匹配、表达式求值等。

### 推荐洛谷题目
1. P1739 表达式括号匹配
2. P1449 后缀表达式
3. P3310 括号序列

### 个人心得摘录与总结
- **linyinuo2008**：多次未通过该题，意识到有很多点需要注意，如合法序列的定义、字符串长度的处理等。总结经验，提醒自己和他人在做题时要仔细分析题目要求。

---
处理用时：42.44秒