# 题目信息

# Obtaining the String

## 题目描述

You are given two strings $ s $ and $ t $ . Both strings have length $ n $ and consist of lowercase Latin letters. The characters in the strings are numbered from $ 1 $ to $ n $ .

You can successively perform the following move any number of times (possibly, zero):

- swap any two adjacent (neighboring) characters of $ s $ (i.e. for any $ i = \{1, 2, \dots, n - 1\} $ you can swap $ s_i $ and $ s_{i + 1}) $ .

You can't apply a move to the string $ t $ . The moves are applied to the string $ s $ one after another.

Your task is to obtain the string $ t $ from the string $ s $ . Find any way to do it with at most $ 10^4 $ such moves.

You do not have to minimize the number of moves, just find any sequence of moves of length $ 10^4 $ or less to transform $ s $ into $ t $ .

## 说明/提示

In the first example the string $ s $ changes as follows: "abcdef" $ \rightarrow $ "abdcef" $ \rightarrow $ "abdcfe" $ \rightarrow $ "abdfce" $ \rightarrow $ "abdfec".

In the second example there is no way to transform the string $ s $ into the string $ t $ through any allowed moves.

## 样例 #1

### 输入

```
6
abcdef
abdfec
```

### 输出

```
4
3 5 4 5 
```

## 样例 #2

### 输入

```
4
abcd
accd
```

### 输出

```
-1
```

# AI分析结果



# Obtaining the String 的题目翻译

## 题目描述

给定两个长度为 $n$ 的字符串 $s$ 和 $t$，字符编号从 $1$ 到 $n$。你可以对 $s$ 进行任意次相邻字符交换操作。要求通过不超过 $10^4$ 次操作将 $s$ 变为 $t$，输出操作步骤或判定无解。

## 输入格式
- 第一行输入整数 $n$（$1 \le n \le 50$）
- 第二行输入字符串 $s$
- 第三行输入字符串 $t$

## 输出格式
- 若无解输出 $-1$
- 若有解，第一行输出操作次数 $k$，第二行输出交换的位置序列（按操作顺序）

## 样例 #1
### 输入
```
6
abcdef
abdfec
```
### 输出
```
4
3 5 4 5 
```

## 样例 #2
### 输入
```
4
abcd
accd
```
### 输出
```
-1
```

---

# 题解分析与结论

## 算法要点总结
1. **无解判定**：当且仅当两个字符串字符出现频次不同
2. **贪心构造**：从左到右逐位对齐，每次将所需字符通过相邻交换移动到目标位置
3. **时间复杂度**：$O(n^2)$，通过冒泡式交换保证操作次数在 $10^4$ 内

---

## 高分题解推荐（评分≥4星）

### 题解1：Hutao__（5星）
**关键亮点**：
- 代码简洁直观，核心逻辑仅20行
- 采用即时交换策略，无需预处理序列
- 完美处理相同字符的定位问题

**核心代码**：
```cpp
for(int i=0;i<n;i++){
    if(a[i]!=b[i]){
        int l;
        for(int j=i+1;j<n;j++){
            if(a[j]==b[i]){
                l=j; break;
            }
        }
        for(int k=l;k>i;k--){
            swap(a[k],a[k-1]);
            ans[++cnt]=k;
        }
    }
}
```

### 题解2：chatoudp（4星）
**关键亮点**：
- 使用双循环定位字符
- 采用字符串直接修改方式
- 包含详细注释说明

**调试心得**：
> "注意：如果当前s2的字符与s1这个位置的字符相等，直接跳过（我就被这坑了）"

**核心代码**：
```cpp
for(int i=0;i<x;i++){
    bool f=0;
    if(s2[i]==s1[i]) continue;
    for(int j=i+1;j<x;j++){
        if(s1[j]==s2[i]){
            f=1; pos=j; break;
        }
    }
    for(int j=pos;j>i;j--){
        swap(s1[j-1],s1[j]);
        a[++n]=j;
    }
}
```

### 题解3：SUNCHAOYI（4星）
**创新思路**：
- 通过建立目标序列映射进行冒泡排序
- 预处理字符位置关系
- 提供完整的合法性检查

**核心思想**：
```cpp
// 建立字符位置映射
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        if(s[j]==t[i] && !vis[j]){
            seq[j]=i;
            vis[j]=1;
            break;
        }
    }
}
// 冒泡排序记录交换
for(int i=0;i<n-1;i++){
    for(int j=0;j<n-1-i;j++){
        if(seq[j]>seq[j+1]){
            swap(seq[j],seq[j+1]);
            ans.push_back(j+1);
        }
    }
}
```

---

# 最优技巧总结
**关键思路**：贪心逐位修正策略
1. 从左到右处理每个目标位置
2. 在源字符串中找到最近的匹配字符
3. 通过相邻交换将其移动到当前位置
4. 总操作次数不超过 $n(n-1)/2$

**实现技巧**：
- 使用双指针避免重复扫描
- 即时修改字符串状态
- 用vector动态记录操作步骤

---

# 相似题目推荐
1. P1106 删数问题（贪心构造最小数）
2. P1321 单词覆盖（字符串操作与贪心策略）
3. P1090 合并果子（操作步骤记录与优化）

---

# 个人心得摘录
1. **调试经验**："在交换过程中必须即时修改字符串状态，否则会重复处理相同字符" —— chatoudp
2. **优化启示**："建立目标序列映射可以将问题转化为经典排序问题" —— SUNCHAOYI
3. **易错提醒**："注意字符频次检查必须单独处理，不能依赖操作步骤中的失败判断" —— Hutao__

---
处理用时：52.05秒