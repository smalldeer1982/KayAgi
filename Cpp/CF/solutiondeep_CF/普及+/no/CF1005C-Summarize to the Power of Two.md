# 题目信息

# Summarize to the Power of Two

## 题目描述

A sequence $ a_1, a_2, \dots, a_n $ is called good if, for each element $ a_i $ , there exists an element $ a_j $ ( $ i \ne j $ ) such that $ a_i+a_j $ is a power of two (that is, $ 2^d $ for some non-negative integer $ d $ ).

For example, the following sequences are good:

- $ [5, 3, 11] $ (for example, for $ a_1=5 $ we can choose $ a_2=3 $ . Note that their sum is a power of two. Similarly, such an element can be found for $ a_2 $ and $ a_3 $ ),
- $ [1, 1, 1, 1023] $ ,
- $ [7, 39, 89, 25, 89] $ ,
- $ [] $ .

Note that, by definition, an empty sequence (with a length of $ 0 $ ) is good.

For example, the following sequences are not good:

- $ [16] $ (for $ a_1=16 $ , it is impossible to find another element $ a_j $ such that their sum is a power of two),
- $ [4, 16] $ (for $ a_1=4 $ , it is impossible to find another element $ a_j $ such that their sum is a power of two),
- $ [1, 3, 2, 8, 8, 8] $ (for $ a_3=2 $ , it is impossible to find another element $ a_j $ such that their sum is a power of two).

You are given a sequence $ a_1, a_2, \dots, a_n $ . What is the minimum number of elements you need to remove to make it good? You can delete an arbitrary set of elements.

## 说明/提示

In the first example, it is enough to delete one element $ a_4=5 $ . The remaining elements form the sequence $ [4, 7, 1, 4, 9] $ , which is good.

## 样例 #1

### 输入

```
6
4 7 1 5 4 9
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
16
```

### 输出

```
1
```

## 样例 #4

### 输入

```
4
1 1 1 1023
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 幂次求和

## 题目描述
一个序列 $a_1, a_2, \dots, a_n$ 被称为好序列，如果对于每个元素 $a_i$ ，都存在一个元素 $a_j$（$i \neq j$），使得 $a_i + a_j$ 是2的幂次方（即对于某个非负整数 $d$，有 $2^d$）。

例如，以下序列是好序列：
- $[5, 3, 11]$（例如，对于 $a_1 = 5$ ，我们可以选择 $a_2 = 3$ 。注意它们的和是2的幂次方。类似地，对于 $a_2$ 和 $a_3$ 也能找到这样的元素），
- $[1, 1, 1, 1023]$ ，
- $[7, 39, 89, 25, 89]$ ，
- $[]$ 。

注意，根据定义，空序列（长度为0）是好序列。

例如，以下序列不是好序列：
- $[16]$（对于 $a_1 = 16$ ，不可能找到另一个元素 $a_j$ ，使得它们的和是2的幂次方），
- $[4, 16]$（对于 $a_1 = 4$ ，不可能找到另一个元素 $a_j$ ，使得它们的和是2的幂次方），
- $[1, 3, 2, 8, 8, 8]$（对于 $a_3 = 2$ ，不可能找到另一个元素 $a_j$ ，使得它们的和是2的幂次方）。

给定一个序列 $a_1, a_2, \dots, a_n$ 。你需要删除最少多少个元素才能使它成为好序列？你可以删除任意一组元素。

## 说明/提示
在第一个示例中，删除一个元素 $a_4 = 5$ 就足够了。剩下的元素形成序列 $[4, 7, 1, 4, 9]$ ，这是一个好序列。

## 样例 #1
### 输入
```
6
4 7 1 5 4 9
```
### 输出
```
1
```

## 样例 #2
### 输入
```
5
1 2 3 4 5
```
### 输出
```
2
```

## 样例 #3
### 输入
```
1
16
```
### 输出
```
1
```

## 样例 #4
### 输入
```
4
1 1 1 1023
```
### 输出
```
0
```

• **算法分类**：枚举
• **综合分析与结论**：这些题解的核心思路都是围绕对于每个数 $a_i$ ，通过枚举2的幂次方 $2^d$ ，判断是否存在另一个数 $a_j$ 使得 $a_i + a_j = 2^d$ 。算法要点在于如何高效地存储和查找数，不同题解采用了 `map`、`unordered_map`、`multiset` 等数据结构。解决难点在于优化查找过程，避免不必要的重复计算，同时要处理好边界情况，比如某个数自身能否与自身匹配等。整体来看，多数题解思路清晰，但在代码可读性和优化程度上有所差异。
• **所选的题解**：
  - **作者：Peiyuan (赞：14)，星级：4星**
    - **关键亮点**：思路清晰，利用 `map` 统计每个数出现的次数，在遍历每个数时，通过枚举2的幂次方并结合 `map` 判断是否存在匹配数，逻辑简洁明了。
    - **重点代码 - 核心实现思想**：遍历数组，对每个数先从 `map` 中减1模拟拿走该数，枚举2的幂次方判断是否有匹配数，若没有则答案加1，最后再将该数放回 `map`。
```cpp
for(ll i=1; i<=n; i++){
    bool f=1;
    m[a[i]]--; 
    ll d=1;
    while(d<=2e9){ 
        if(m[d-a[i]]>0){ 
            f=0; break;
        }
        d*=2; 
    }
    if(f) ans++; 
    m[a[i]]++; 
}
```
  - **作者：EdenSky (赞：4)，星级：4星**
    - **关键亮点**：同样利用 `unordered_map` 实现匹配，代码简洁，通过将原式转化为 $a_j = 2^p - a_i$ ，枚举 $p$ 判断匹配情况，时间复杂度控制较好。
    - **重点代码 - 核心实现思想**：遍历数组，对每个数先从 `unordered_map` 中减1，枚举2的幂次方判断是否有匹配数，若没有则答案加1，最后再将该数放回 `unordered_map`。
```cpp
for(gg i=1;i<=n;i++){
    s[a[i]]--;
    gg p=1;
    bool flag=true;
    while(p<=INF){
        if(s[p-a[i]]>0)	flag=false;
        p<<=1;
    }
    if(flag)	ans++;
    s[a[i]]++;
}
```
  - **作者：基建160282 (赞：4)，星级：4星**
    - **关键亮点**：详细解释了题目大意和样例，便于理解。利用 `map` 实现桶的功能，在处理每个数时，先减1避免自身匹配，通过枚举合适的2的幂次方来判断是否存在匹配数。
    - **重点代码 - 核心实现思想**：遍历数组，对每个数先从 `map` 中减1，找到比该数大的第一个2的幂次方，从此处开始枚举2的幂次方判断是否有匹配数，若没有则答案加1，最后再将该数放回 `map`。
```cpp
for(int i = 1; i <= n; ++i){
    --mp[a[i]]; 
    int q = 0;
    while((1 << q) <= a[i]) ++q; 
    bool flag = true;
    for(; q <= 30; ++q){ 
        if(mp[(1 << q) - a[i]])
            flag = false; 
    }
    if(flag) ++ans; 
    ++mp[a[i]];
}
```
• **最优关键思路或技巧**：利用哈希表（如 `map` 或 `unordered_map`）来高效存储和查找数，通过枚举2的幂次方来判断每个数是否能找到匹配数，这种方法能有效降低时间复杂度。同时在处理过程中，注意临时移除当前处理的数以避免自身匹配的情况。
• **可拓展之处**：同类型题通常围绕数字组合满足特定数学关系展开，类似算法套路是通过合理的数据结构优化枚举过程，比如在其他需要判断数字组合是否满足某种运算结果的题目中，也可借鉴这种利用哈希表加速查找的方式。
• **推荐题目**：
  - [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)，通过枚举子段起点和终点来寻找最大子段和，与本题枚举匹配数思路类似。
  - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)，枚举不同包装铅笔的购买数量来找到最小花费，涉及枚举优化。
  - [P1036 选数](https://www.luogu.com.cn/problem/P1036)，通过枚举数字组合判断是否为质数，同样是枚举数字组合满足特定条件。 

---
处理用时：49.29秒