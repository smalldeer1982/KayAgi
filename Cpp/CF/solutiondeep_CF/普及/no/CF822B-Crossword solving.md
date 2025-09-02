# 题目信息

# Crossword solving

## 题目描述

Erelong Leha was bored by calculating of the greatest common divisor of two factorials. Therefore he decided to solve some crosswords. It's well known that it is a very interesting occupation though it can be very difficult from time to time. In the course of solving one of the crosswords, Leha had to solve a simple task. You are able to do it too, aren't you?

Leha has two strings $ s $ and $ t $ . The hacker wants to change the string $ s $ at such way, that it can be found in $ t $ as a substring. All the changes should be the following: Leha chooses one position in the string $ s $ and replaces the symbol in this position with the question mark "?". The hacker is sure that the question mark in comparison can play the role of an arbitrary symbol. For example, if he gets string $ s $ ="ab?b" as a result, it will appear in $ t $ ="aabrbb" as a substring.

Guaranteed that the length of the string $ s $ doesn't exceed the length of the string $ t $ . Help the hacker to replace in $ s $ as few symbols as possible so that the result of the replacements can be found in $ t $ as a substring. The symbol "?" should be considered equal to any other symbol.

## 样例 #1

### 输入

```
3 5
abc
xaybz
```

### 输出

```
2
2 3 
```

## 样例 #2

### 输入

```
4 10
abcd
ebceabazcd
```

### 输出

```
1
2 
```

# AI分析结果



# Crossword solving

## 题目描述

Erelong Leha 在计算两个阶乘的最大公约数时感到无聊，决定解决一些填字游戏。众所周知，这虽然有时非常困难，但也是一项非常有趣的活动。在解决其中一个填字游戏时，Leha 遇到了一个简单的任务。你也能做到，不是吗？

Leha 有两个字符串 $s$ 和 $t$。黑客希望通过以下方式修改字符串 $s$，使得修改后的 $s$ 可以在 $t$ 中以子串形式找到。所有修改应满足：Leha 选择字符串 $s$ 中的一个位置，并将该位置的符号替换为问号 "?"。黑客确信问号可以起到任意符号的作用。例如，如果他得到字符串 $s$ ="ab?b"，则它将以子串形式出现在 $t$ ="aabrbb" 中。

保证字符串 $s$ 的长度不超过 $t$ 的长度。请帮助黑客以最少的符号替换次数完成修改，并输出需要修改的位置。符号 "?" 应被视为与任何其他符号相等。

## 样例 #1

### 输入

```
3 5
abc
xaybz
```

### 输出

```
2
2 3 
```

## 样例 #2

### 输入

```
4 10
abcd
ebceabazcd
```

### 输出

```
1
2 
```

## 算法分类
枚举

---

## 题解综合分析

所有题解均采用暴力枚举思路，时间复杂度 O(n(m-n+1))。核心思路为：枚举 t 中所有可能匹配的起始位置，计算 s 与对应子串的差异字符数量，维护最小修改次数及其位置。

### 关键思路总结
1. **枚举范围控制**：外层循环的起始位置 i 必须满足 1 ≤ i ≤ m-n+1（以 1-based 计）
2. **差异统计方式**：通过双重循环直接比较每个对应位置的字符
3. **最优解维护**：动态记录最小修改次数，并在发现更优解时即时更新答案数组
4. **位置存储优化**：使用动态数组（vector）避免固定数组的冗余存储

---

## 优质题解推荐

### 1. Dream__Sky（4.5星）
**核心亮点**：
- 清晰的变量命名和代码结构
- 使用 vector 动态管理修改位置
- 正确处理字符串索引偏移问题
```cpp
for(int i=1;i<=m-n+1;i++) {
    int sum=0;
    vector<int> tmp;
    for(int j=1,k=i; j<=n; j++,k++) {
        if(s[j]!=t[k]) sum++;
    }
    if(sum < daan) {
        daan = sum;
        v = tmp; // 动态更新答案数组
    }
}
```

### 2. xuduang（4星）
**核心亮点**：
- 简洁的代码实现
- 使用固定数组优化访问速度
- 直观的位置映射计算
```cpp
for(int j=0;j<n;j++) {
    if(s[j+1]!=t[i+j]) ans++;
}
if(ans<cnt) {
    cnt=ans;
    for(...) a[...]=j+1; // 直接记录原始位置
}
```

### 3. LaDeX（4星）
**个人心得**：
> "要注意枚举开头位置是从 1 枚举到 m-n+1（字符串第一个字符下标为 1），不然第 27 个点会炸掉"

**优化技巧**：
- 使用 memset 快速重置临时数组
- 显式处理字符串索引偏移
```cpp
for(int i=1;i<=m-n+1;i++){
    LL cnt=0;
    memset(tmp,0,sizeof(tmp));
    for(int j=1;j<=n;j++){
        if(T[i+j-1]!=S[j]) tmp[++cnt]=j;
    }
}
```

---

## 同类题目推荐
1. [P2957 字符串匹配计数](https://www.luogu.com.cn/problem/P2957) - 基础字符串匹配
2. [P3375 KMP字符串匹配](https://www.luogu.com.cn/problem/P3375) - 进阶匹配算法
3. [P1143 子串判断](https://www.luogu.com.cn/problem/P1143) - 带通配符的匹配问题

---
处理用时：63.22秒