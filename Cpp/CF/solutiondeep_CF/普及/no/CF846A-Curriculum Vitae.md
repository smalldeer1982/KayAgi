# 题目信息

# Curriculum Vitae

## 题目描述

Hideo Kojima has just quit his job at Konami. Now he is going to find a new place to work. Despite being such a well-known person, he still needs a CV to apply for a job.

During all his career Hideo has produced $ n $ games. Some of them were successful, some were not. Hideo wants to remove several of them (possibly zero) from his CV to make a better impression on employers. As a result there should be no unsuccessful game which comes right after successful one in his CV.

More formally, you are given an array $ s_{1},s_{2},...,s_{n} $ of zeros and ones. Zero corresponds to an unsuccessful game, one — to a successful one. Games are given in order they were produced, and Hideo can't swap these values. He should remove some elements from this array in such a way that no zero comes right after one.

Besides that, Hideo still wants to mention as much games in his CV as possible. Help this genius of a man determine the maximum number of games he can leave in his CV.

## 样例 #1

### 输入

```
4
1 1 0 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
0 1 0 0 1 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
1
```

# AI分析结果



# Curriculum Vitae

## 题目描述

小岛秀夫刚刚从科乐美离职，现在需要制作一份简历。他的职业生涯中有 $n$ 款游戏，用 0（失败）和 1（成功）表示。要求删除若干游戏后，剩余序列中不能出现 0 在 1 之后的情况。求最多能保留的游戏数量。

## 算法分类
前缀和

---

### 综合分析与结论
题目要求将序列分割为全0前缀和全1后缀的组合。核心思路是通过前缀和快速计算每个分割点左侧的0数量与右侧的1数量之和。最优解法使用两次前缀和预处理，时间复杂度 $O(n)$。

---

### 精选题解

#### 泠小毒（4星）
**亮点**：双前缀和预处理，直观高效  
- 预处理 `suml[i]` 记录前i个元素中0的数量  
- 预处理 `sumr[i]` 记录第i个元素之后1的数量  
- 遍历所有分割点取最大值  

**核心代码**：
```cpp
int suml[110], sumr[110];
for(int i=1;i<=n;i++) suml[i] = suml[i-1] + (a[i]==0); // 前i个0的数量
for(int i=n;i>=1;i--) sumr[i] = sumr[i+1] + (a[i]==1); // i之后1的数量
for(int i=1;i<=n;i++) ans = max(ans, suml[i] + sumr[i]);
```

#### 刘子懿（4星）
**亮点**：单前缀和数学推导，代码简洁  
- 利用总和公式推导：保留数 = 总1数 + 左0数 - 左1数  
- 遍历范围包含0到n的边界情况  

**核心代码**：
```cpp
int add[120]; // 前缀和数组存储1的数量
for(int i=0; i<=n; i++) 
    ans = max(ans, i + add[n] - 2*add[i]); // i-add[i]为左0数，add[n]-add[i]为右1数
```

---

### 关键思路
1. **分割点枚举**：每个位置作为0序列和1序列的分界点  
2. **前缀和优化**：预处理O(1)获取任意区间的0/1计数  
3. **数学变形**：将左右区间计算转化为线性代数式

---

### 拓展建议
类似分界点问题可参考：  
1. 最大子段和（洛谷 P1115）  
2. 最长递增子序列变种（需前递减后递增）  
3. 分割平衡字符串（LeetCode 1221）  

---

### 相似题目推荐
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
2. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)（前缀和统计区间访问次数）  
3. [P3662 区块](https://www.luogu.com.cn/problem/P3662)（分段最优化问题）

---
处理用时：235.14秒