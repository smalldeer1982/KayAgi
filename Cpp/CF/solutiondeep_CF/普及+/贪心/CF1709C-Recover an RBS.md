# 题目信息

# Recover an RBS

## 题目描述

A bracket sequence is a string containing only characters "(" and ")". A regular bracket sequence (or, shortly, an RBS) is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)");
- bracket sequences ")(", "(" and ")" are not.

There was an RBS. Some brackets have been replaced with question marks. Is it true that there is a unique way to replace question marks with brackets, so that the resulting sequence is an RBS?

## 说明/提示

In the first testcase, the only possible original RBS is "(())".

In the second testcase, there are multiple ways to recover an RBS.

In the third and the fourth testcases, the only possible original RBS is "()".

In the fifth testcase, the original RBS can be either "((()()))" or "(())()()".

## 样例 #1

### 输入

```
5
(?))
??????
()
??
?(?)()?)```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果



# Recover an RBS 题解分析

## 题目重述
给定一个可能包含问号的括号序列，判断是否只有一种方式将问号替换为括号，使得结果成为合法括号序列（RBS）。保证至少存在一种合法替换方式。

### 输入格式
- 多组测试数据
- 每组数据包含一个由 '(', ')', '?' 组成的字符串

### 输出格式
- 对每组数据输出 YES/NO，表示是否唯一解

## 题解综合分析

### 最优解题思路
1. **贪心构造基础解**：优先将前 L 个问号替换为 '('，剩余替换为 ')'
2. **唯一性验证**：交换最后一个被填 '(' 的问号与第一个被填 ')' 的问号，验证新序列是否合法
3. **合法性快速判断**：构造后的序列若存在前缀和负数则非法

### 高分题解推荐

#### 1. Jr_Zlw 的贪心构造法（⭐⭐⭐⭐⭐）
**核心思路**：
- 先构造最贪心解（前 L 个问号填 '('）
- 尝试交换最后一个 '(' 问号和第一个 ')' 问号
- 验证交换后序列是否合法

**关键代码**：
```cpp
void Solve() {
    // 构造基础解
    for(int i=1;i<=n;i++) {
        if(c[i]=='?' && cnt_left) a[i]=1, cnt_left--;
        else if(c[i]=='?') a[i]=-1;
    }

    // 寻找交换点
    int last_left = 0, first_right = 0;
    for(int i=n;i>=1;i--) if(c[i]=='?' && a[i]==1) {last_left=i; break;}
    for(int i=1;i<=n;i++) if(c[i]=='?' && a[i]==-1) {first_right=i; break;}

    // 交换并验证
    swap(a[last_left], a[first_right]);
    int sum = 0;
    for(int i=1;i<=n;i++) {
        sum += a[i];
        if(sum < 0) return puts("YES");
    }
    puts(sum==0 ? "NO" : "YES");
}
```

#### 2. BigSmall_En 的前缀和动态判断法（⭐⭐⭐⭐）
**核心思路**：
- 维护当前确定括号的平衡值 cnt 
- 维护未处理问号数 qry
- 当 cnt + qry == 1 时强制确定问号为 '('

**关键代码**：
```cpp
for(int i=1;i<=n;++i){
    if(s[i]=='(') ++cnt;
    else if(s[i]==')') --cnt;
    else ++qry;
    
    if(cnt + qry == 1){ // 必须确定为左括号
        cnt = 1;
        qry = 0;
    }
}
if(abs(cnt) == qry) puts("YES");
```

#### 3. 2018ljw 的ST表验证法（⭐⭐⭐）
**核心思路**：
- 预处理前缀和数组的区间最小值
- 二分查找可交换的括号对
- 使用ST表快速验证区间约束

**亮点**：通过数据结构优化验证过程

## 拓展与总结

### 关键技巧
1. **贪心构造原则**：优先填充左括号保证前缀合法性
2. **交换验证法**：通过交换极值点快速判断多解存在性
3. **前缀和动态维护**：实时跟踪括号平衡状态

### 相似题目推荐
1. [P5658 括号树](https://www.luogu.com.cn/problem/P5658) - 树形结构的括号序列分析
2. [P7914 括号序列](https://www.luogu.com.cn/problem/P7914) - 带通配符的合法序列计数 
3. [CF3D Least Cost Bracket Sequence](https://codeforces.com/problemset/problem/3/D) - 带权括号序列构造

### 调试经验
- **边界处理**：在交换验证时需考虑全为同种括号的情况
- **前缀和清零**：每次构造新序列后必须重新计算前缀和
- **复杂度优化**：贪心构造法时间复杂度 O(n) 最优，适合处理 2e5 级数据

通过掌握贪心构造与交换验证的核心思路，可高效解决此类括号序列唯一性问题。

---
处理用时：48.58秒