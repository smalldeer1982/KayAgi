# 题目信息

# Lexicographically Largest

## 题目描述

Stack has an array $ a $ of length $ n $ . He also has an empty set $ S $ . Note that $ S $ is not a multiset.

He will do the following three-step operation exactly $ n $ times:

1. Select an index $ i $ such that $ 1 \leq i \leq |a| $ .
2. Insert $ ^\dagger $ $ a_i + i $ into $ S $ .
3. Delete $ a_i $ from $ a $ . Note that the indices of all elements to the right of $ a_i $ will decrease by $ 1 $ .

Note that after $ n $ operations, $ a $ will be empty.

Stack will now construct a new array $ b $ which is $ S $ sorted in decreasing order. Formally, $ b $ is an array of size $ |S| $ where $ b_i $ is the $ i $ -th largest element of $ S $ for all $ 1 \leq i \leq |S| $ .

Find the lexicographically largest $ ^\ddagger $ $ b $ that Stack can make.

 $ ^\dagger $ A set can only contain unique elements. Inserting an element that is already present in a set will not change the elements of the set.

 $ ^\ddagger $ An array $ p $ is lexicographically larger than a sequence $ q $ if and only if one of the following holds:

- $ q $ is a prefix of $ p $ , but $ p \ne q $ ; or
- in the first position where $ p $ and $ q $ differ, the array $ p $ has a larger element than the corresponding element in $ q $ .

Note that $ [3,1,4,1,5] $ is lexicographically larger than $ [3,1,3] $ , $ [\,] $ , and $ [3,1,4,1] $ but not $ [3,1,4,1,5,9] $ , $ [3,1,4,1,5] $ , and $ [4] $ .

## 说明/提示

In the first test case, select $ i=1 $ in the first operation, insert $ a_1 + 1 = 3 $ in $ S $ , and delete $ a_1 $ from $ a $ . After the first operation, $ a $ becomes $ a=[1] $ . In the second operation, we select $ i=1 $ again and insert $ a_1 + 1 = 2 $ in $ S $ . Thus $ S=\{2, 3\} $ , and $ b = [3, 2] $ .

Note that if you select $ i=2 $ in the first operation, and $ i=1 $ in the second operation, $ S=\{3\} $ as $ 3 $ will be inserted twice, resulting in $ b=[3] $ .

As $ [3,2] $ is lexicographically larger than $ [3] $ , we should select $ i=1 $ in the first operation.

In the second test case, in each operation, select the last element.

## 样例 #1

### 输入

```
3
2
2 1
5
1 100 1000 1000000 1000000000
3
6 4 8```

### 输出

```
3 2 
1000000005 1000004 1003 102 2 
11 7 6```

# AI分析结果

### 题目内容重写
# 字典序最大

## 题目描述

Stack 有一个长度为 $n$ 的数组 $a$。他还有一个空集合 $S$。注意，$S$ 不是多重集合。

他将执行以下三步操作恰好 $n$ 次：

1. 选择一个索引 $i$，满足 $1 \leq i \leq |a|$。
2. 将 $a_i + i$ 插入到 $S$ 中。
3. 从 $a$ 中删除 $a_i$。注意，$a_i$ 右边的所有元素的索引将减少 $1$。

注意，经过 $n$ 次操作后，$a$ 将为空。

Stack 现在将构造一个新数组 $b$，它是 $S$ 按降序排序后的结果。形式上，$b$ 是一个大小为 $|S|$ 的数组，其中 $b_i$ 是 $S$ 中第 $i$ 大的元素，对于所有 $1 \leq i \leq |S|$。

找到 Stack 可以构造的字典序最大的 $b$。

$^\dagger$ 集合只能包含唯一元素。插入一个已经存在于集合中的元素不会改变集合的元素。

$^\ddagger$ 一个数组 $p$ 字典序大于数组 $q$，当且仅当以下条件之一成立：

- $q$ 是 $p$ 的前缀，但 $p \ne q$；或者
- 在 $p$ 和 $q$ 第一个不同的位置，$p$ 的元素大于 $q$ 的对应元素。

注意，$[3,1,4,1,5]$ 字典序大于 $[3,1,3]$、$[\,]$ 和 $[3,1,4,1]$，但不大于 $[3,1,4,1,5,9]$、$[3,1,4,1,5]$ 和 $[4]$。

## 说明/提示

在第一个测试用例中，第一次操作选择 $i=1$，将 $a_1 + 1 = 3$ 插入 $S$，并从 $a$ 中删除 $a_1$。第一次操作后，$a$ 变为 $a=[1]$。第二次操作再次选择 $i=1$，将 $a_1 + 1 = 2$ 插入 $S$。因此 $S=\{2, 3\}$，且 $b = [3, 2]$。

注意，如果第一次操作选择 $i=2$，第二次操作选择 $i=1$，则 $S=\{3\}$，因为 $3$ 会被插入两次，导致 $b=[3]$。

由于 $[3,2]$ 字典序大于 $[3]$，我们应该在第一次操作中选择 $i=1$。

在第二个测试用例中，每次操作都选择最后一个元素。

## 样例 #1

### 输入

```
3
2
2 1
5
1 100 1000 1000000 1000000000
3
6 4 8```

### 输出

```
3 2 
1000000005 1000004 1003 102 2 
11 7 6```

### 题解分析与结论

#### 题解1：JiuZhE66666 (5星)
- **关键亮点**：通过直接对 $a_i + i$ 进行降序排序，并处理重复元素，确保字典序最大。代码简洁高效。
- **核心实现**：对 $a_i + i$ 进行降序排序，然后处理重复元素，确保每个元素尽可能大。
```cpp
sort(a+1,a+1+n,greater<int>());
for(int i=2;i<=n;i++) a[i]=min(a[i],a[i-1]-1);
```

#### 题解2：HomuraAkemi (4星)
- **关键亮点**：通过归纳法证明了任意符合条件的序列 $c$ 都可以被构造出来，并利用 `std::set` 维护已用和未用元素。
- **核心实现**：使用两个 `set` 维护已用和未用元素，确保每次插入的元素尽可能大。
```cpp
set<ll> vis,now;
for(int i=1;i<=n;i++){
    ll v;
    if(!vis.count(a[i])) v = a[i];
    else{
        auto it = now.upper_bound(a[i]);it--;
        v = *it;
    }
    sol.pb_(v);
    vis.insert(v);now.erase(v);
    if(!vis.count(v-1)) now.insert(v-1);
}
```

#### 题解3：M1saka16I72 (4星)
- **关键亮点**：通过分析每个元素的下标减少次数，确保字典序最大，并使用 `set` 维护已用和未用元素。
- **核心实现**：使用两个 `set` 维护已用和未用元素，确保每次插入的元素尽可能大。
```cpp
set<ll> vis,now;
for(int i=1;i<=n;i++){
    ll v;
    if(!vis.count(a[i])) v = a[i];
    else{
        auto it = now.upper_bound(a[i]);it--;
        v = *it;
    }
    sol.pb_(v);
    vis.insert(v);now.erase(v);
    if(!vis.count(v-1)) now.insert(v-1);
}
```

### 最优关键思路或技巧
1. **直接排序法**：对 $a_i + i$ 进行降序排序，并处理重复元素，确保字典序最大。
2. **归纳法与 `set` 维护**：通过归纳法证明序列的可行性，并使用 `set` 维护已用和未用元素，确保每次插入的元素尽可能大。

### 可拓展之处
- **类似问题**：可以扩展到其他需要构造字典序最大或最小序列的问题，如字符串排序、数组重组等。
- **数据结构**：`set` 的使用可以扩展到其他需要维护唯一元素或快速查找的场景。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P3378 堆](https://www.luogu.com.cn/problem/P3378)

### 个人心得摘录
- **JiuZhE66666**：通过直接排序和处理重复元素，代码简洁高效，适合快速解决问题。
- **HomuraAkemi**：通过归纳法证明序列的可行性，并使用 `set` 维护元素，确保每次插入的元素尽可能大。
- **M1saka16I72**：通过分析每个元素的下标减少次数，确保字典序最大，并使用 `set` 维护已用和未用元素。

---
处理用时：49.98秒