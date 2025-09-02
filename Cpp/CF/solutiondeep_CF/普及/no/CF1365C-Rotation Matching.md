# 题目信息

# Rotation Matching

## 题目描述

After the mysterious disappearance of Ashish, his two favourite disciples Ishika and Hriday, were each left with one half of a secret message. These messages can each be represented by a permutation of size $ n $ . Let's call them $ a $ and $ b $ .

Note that a permutation of $ n $ elements is a sequence of numbers $ a_1, a_2, \ldots, a_n $ , in which every number from $ 1 $ to $ n $ appears exactly once.

The message can be decoded by an arrangement of sequence $ a $ and $ b $ , such that the number of matching pairs of elements between them is maximum. A pair of elements $ a_i $ and $ b_j $ is said to match if:

- $ i = j $ , that is, they are at the same index.
- $ a_i = b_j $

His two disciples are allowed to perform the following operation any number of times:

- choose a number $ k $ and cyclically shift one of the permutations to the left or right $ k $ times.

A single cyclic shift to the left on any permutation $ c $ is an operation that sets $ c_1:=c_2, c_2:=c_3, \ldots, c_n:=c_1 $ simultaneously. Likewise, a single cyclic shift to the right on any permutation $ c $ is an operation that sets $ c_1:=c_n, c_2:=c_1, \ldots, c_n:=c_{n-1} $ simultaneously.

Help Ishika and Hriday find the maximum number of pairs of elements that match after performing the operation any (possibly zero) number of times.

## 说明/提示

For the first case: $ b $ can be shifted to the right by $ k = 1 $ . The resulting permutations will be $ \{1, 2, 3, 4, 5\} $ and $ \{1, 2, 3, 4, 5\} $ .

For the second case: The operation is not required. For all possible rotations of $ a $ and $ b $ , the number of matching pairs won't exceed $ 1 $ .

For the third case: $ b $ can be shifted to the left by $ k = 1 $ . The resulting permutations will be $ \{1, 3, 2, 4\} $ and $ \{2, 3, 1, 4\} $ . Positions $ 2 $ and $ 4 $ have matching pairs of elements. For all possible rotations of $ a $ and $ b $ , the number of matching pairs won't exceed $ 2 $ .

## 样例 #1

### 输入

```
5
1 2 3 4 5
2 3 4 5 1```

### 输出

```
5```

## 样例 #2

### 输入

```
5
5 4 3 2 1
1 2 3 4 5```

### 输出

```
1```

## 样例 #3

### 输入

```
4
1 3 2 4
4 2 3 1```

### 输出

```
2```

# AI分析结果

### 题目重写
# 旋转匹配

## 题目描述

在Ashish神秘失踪后，他的两个最喜欢的弟子Ishika和Hriday各自留下了一半的秘密信息。这些信息可以表示为大小为$n$的排列，分别称为$a$和$b$。

注意，一个大小为$n$的排列是一个由数字$a_1, a_2, \ldots, a_n$组成的序列，其中每个数字从1到$n$恰好出现一次。

通过排列$a$和$b$的某种排列，可以解码信息，使得它们之间的匹配元素对的数量最大。元素对$a_i$和$b_j$被认为是匹配的，如果：

- $i = j$，即它们在相同的索引位置。
- $a_i = b_j$

他的两个弟子可以执行以下操作任意次数：

- 选择一个数字$k$，并将其中一个排列向左或向右循环移动$k$次。

对任何排列$c$的单个循环左移操作是将$c_1:=c_2, c_2:=c_3, \ldots, c_n:=c_1$同时设置。同样，对任何排列$c$的单个循环右移操作是将$c_1:=c_n, c_2:=c_1, \ldots, c_n:=c_{n-1}$同时设置。

帮助Ishika和Hriday找到在执行操作任意（可能为零）次数后，匹配元素对的最大数量。

## 说明/提示

对于第一个样例：$b$可以向右移动$k = 1$次。结果排列将是$\{1, 2, 3, 4, 5\}$和$\{1, 2, 3, 4, 5\}$。

对于第二个样例：不需要操作。对于$a$和$b$的所有可能旋转，匹配元素对的数量不会超过1。

对于第三个样例：$b$可以向左移动$k = 1$次。结果排列将是$\{1, 3, 2, 4\}$和$\{2, 3, 1, 4\}$。位置2和4有匹配的元素对。对于$a$和$b$的所有可能旋转，匹配元素对的数量不会超过2。

## 样例 #1

### 输入

```
5
1 2 3 4 5
2 3 4 5 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
5 4 3 2 1
1 2 3 4 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
1 3 2 4
4 2 3 1
```

### 输出

```
2
```

### 算法分类
数学

### 题解分析与结论
本题的核心在于通过计算每个元素在$a$和$b$中的位置差，找到使得匹配元素对最多的旋转次数。所有题解都采用了类似的方法，即通过记录每个元素在$a$和$b$中的位置，计算它们之间的距离，并统计每个距离的出现次数，最终找到出现次数最多的距离。

### 所选题解
#### 题解1：作者：lianchanghua (赞：10)
**星级：5**
**关键亮点：**
- 使用数组记录每个元素在$a$和$b$中的位置。
- 通过计算位置差并统计每个差值的出现次数，找到最大匹配数。
- 代码简洁，思路清晰。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    cin>>b[i];
    bb[b[i]]=i;
    ans[(bb[b[i]]-aa[b[i]]+n)%n]++;
}
sort(ans,ans+1+n);
cout<<ans[n]<<endl;
```

#### 题解2：作者：Refined_heart (赞：2)
**星级：4**
**关键亮点：**
- 通过记录每个元素在$a$和$b$中的位置，计算旋转次数。
- 使用数组统计每个旋转次数的出现次数，找到最大值。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
for(int i=1;i<=n;++i){
    scanf("%d",&b[i]);
    if(i<=pos[b[i]])cnt[pos[b[i]]-i]++;
    else{
        cnt[n-i+pos[b[i]]]++;
    }
}
int mx=-1;
for(int i=0;i<=n;++i)mx=max(mx,cnt[i]);
printf("%d\n",mx);
```

#### 题解3：作者：L_shadow (赞：1)
**星级：4**
**关键亮点：**
- 使用桶记录每个元素在$a$和$b$中的位置差。
- 在记录的同时更新最大值，避免了额外的循环。
- 代码简洁，效率高。

**核心代码：**
```cpp
for(int i=1; i<=n; i++) {
    scanf("%d",&b[i]);
    nowb[(i-nowa[b[i]]+n)%n]++;
    ans=max(ans,nowb[(i-nowa[b[i]]+n)%n]);
}
cout<<ans;
```

### 最优关键思路或技巧
- **位置差统计法**：通过记录每个元素在$a$和$b$中的位置，计算它们之间的距离，并统计每个距离的出现次数，最终找到出现次数最多的距离。
- **桶排序**：使用桶记录每个距离的出现次数，避免排序操作，提高效率。

### 可拓展之处
- 类似的问题可以扩展到多维数组或多重排列的匹配问题。
- 可以进一步优化空间复杂度，例如使用哈希表代替数组。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

### 个人心得
- **调试经历**：在计算位置差时，需要注意负数的情况，可以通过加上$n$再取模来避免负数。
- **顿悟感想**：通过记录位置差并统计出现次数，可以高效地找到最大匹配数，这种方法在类似问题中具有通用性。

---
处理用时：42.62秒