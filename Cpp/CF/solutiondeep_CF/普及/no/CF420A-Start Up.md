# 题目信息

# Start Up

## 题目描述

Recently, a start up by two students of a state university of city F gained incredible popularity. Now it's time to start a new company. But what do we call it?

The market analysts came up with a very smart plan: the name of the company should be identical to its reflection in a mirror! In other words, if we write out the name of the company on a piece of paper in a line (horizontally, from left to right) with large English letters, then put this piece of paper in front of the mirror, then the reflection of the name in the mirror should perfectly match the line written on the piece of paper.

There are many suggestions for the company name, so coming up to the mirror with a piece of paper for each name wouldn't be sensible. The founders of the company decided to automatize this process. They asked you to write a program that can, given a word, determine whether the word is a 'mirror' word or not.

## 样例 #1

### 输入

```
AHA
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
Z
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
XO
```

### 输出

```
NO
```

# AI分析结果



# Start Up

## 题目描述

最近，F市某州立大学两名学生创立的初创公司获得了惊人的知名度。现在到了创办新公司的时候了，但该取什么名字呢？

市场分析师提出了一个聪明的方案：公司名称必须与镜中倒影完全相同！换句话说，如果我们将公司名称用大写英文字母在一张纸上横向书写（从左到右），然后将这张纸放在镜子前，名称在镜中的倒影必须与纸上书写的文字完美匹配。

由于有很多候选名称，为每个名称都拿纸去照镜子并不现实。公司创始人决定自动化这一过程，请你编写程序判断给定单词是否为"镜像词"。

## 样例 #1

### 输入
```
AHA
```

### 输出
```
YES
```

## 样例 #2

### 输入
```
Z
```

### 输出
```
NO
```

## 样例 #3

### 输入
```
XO
```

### 输出
```
NO
```

---

**算法分类**：字符串

---

## 题解分析与结论

### 核心思路
所有题解均围绕两个必要条件展开：
1. **轴对称字符检查**：只允许使用`AHIMOTUVWXY`这11个轴对称字符
2. **回文串验证**：字符串必须完全对称

### 解决难点对比
1. 字符检查方式：
   - 直接条件判断（主流选择，O(1)时间复杂度）
   - 预存字符串+二分查找（`andyli`解法，适合字符集较大时）
2. 回文验证方法：
   - 反转字符串后整体比较（`我和鱼过不去`解法，代码简洁）
   - 双指针同步遍历（多数解法采用，空间效率更优）
3. 优化技巧：
   - 提前终止检查（发现非法字符立即返回）
   - 同步验证字符合法性与对称性（`Eason_AC`解法）

---

## 精选题解

### 题解1：我和鱼过不去（⭐⭐⭐⭐）
**核心亮点**：
1. 使用`reverse`函数实现字符串反转，代码简洁直观
2. 分步检查逻辑清晰，便于维护
3. 提前终止检查优化效率

```cpp
string a;
// 检查轴对称字符
for(char c : a) {
    if(!is_mirror_char(c)) return NO;
}
// 检查回文
string reversed = a;
reverse(reversed.begin(), reversed.end());
return a == reversed ? YES : NO;
```

### 题解2：Eason_AC（⭐⭐⭐⭐）
**核心亮点**：
1. 双指针同步检查字符合法性与回文性
2. 单次遍历完成全部检查，空间效率最优
3. 条件表达式高度优化

```cpp
for(int i=0, j=len-1; i<=j; ++i,--j) {
    if(!(a[i]==a[j] && is_mirror_char(a[i]))) 
        return NO;
}
```

### 题解3：jijidawang（⭐⭐⭐⭐）
**亮点总结**：
1. 循环条件处理巧妙，兼容奇偶长度
2. 同时验证对称位置字符合法性
3. 详细注释提升可读性

```cpp
for(int i=0; i+i <= len; i++) {
    int j = len-i-1;
    verify_char(a[i]);
    verify_char(a[j]);
    check_palindrome(a[i], a[j]);
}
```

---

## 关键技巧总结
1. **双指针同步验证**：同时检查对称位置字符的合法性和对称性，减少循环次数
2. **短路优化**：发现非法字符立即返回，避免无效计算
3. **字符集预验证**：将11个合法字符硬编码检查，效率最高

---

## 同类题目推荐
1. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217) - 回文与质数双重验证
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308) - 字符串匹配与边界处理
3. [P2010 回文日期](https://www.luogu.com.cn/problem/P2010) - 日期格式与回文结合

---
处理用时：56.77秒