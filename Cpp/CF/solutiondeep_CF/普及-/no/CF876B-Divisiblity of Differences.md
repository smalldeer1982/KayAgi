# 题目信息

# Divisiblity of Differences

## 题目描述

You are given a multiset of $ n $ integers. You should select exactly $ k $ of them in a such way that the difference between any two of them is divisible by $ m $ , or tell that it is impossible.

Numbers can be repeated in the original multiset and in the multiset of selected numbers, but number of occurrences of any number in multiset of selected numbers should not exceed the number of its occurrences in the original multiset.

## 样例 #1

### 输入

```
3 2 3
1 8 4
```

### 输出

```
Yes
1 4 ```

## 样例 #2

### 输入

```
3 3 3
1 8 4
```

### 输出

```
No```

## 样例 #3

### 输入

```
4 3 5
2 7 7 7
```

### 输出

```
Yes
2 7 7 ```

# AI分析结果

### 题目内容中文重写
# 差的整除性

## 题目描述
给定一个包含 $n$ 个整数的多重集。你需要从中恰好选择 $k$ 个数，使得其中任意两个数的差都能被 $m$ 整除，若无法做到则输出 `No`。

在原始多重集和所选数字的多重集中，数字可以重复，但所选数字多重集中任何数字的出现次数不应超过其在原始多重集中的出现次数。

## 样例 #1
### 输入
```
3 2 3
1 8 4
```
### 输出
```
Yes
1 4
```

## 样例 #2
### 输入
```
3 3 3
1 8 4
```
### 输出
```
No
```

## 样例 #3
### 输入
```
4 3 5
2 7 7 7
```
### 输出
```
Yes
2 7 7
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路均是利用同余定理，即若两个整数 $a$ 和 $b$ 满足 $(a - b)$ 能被 $m$ 整除，则 $a \equiv b \pmod m$，也就是 $a \bmod m = b \bmod m$。所以只要找到 $k$ 个模 $m$ 余数相同的数即可。

各题解的主要区别在于实现细节和优化程度：
- **yutong_Seafloor**：将输入和判断结合，一旦找到满足条件的 $k$ 个数就输出结果，减少不必要的计算，代码简洁。
- **Fengyiwei1234**：先统计所有余数的个数，再遍历判断，时间复杂度为 $O(n^2)$。
- **yxy666**：使用数组记录余数个数，思路清晰，但代码相对复杂。
- **sssscy_free_stdio**：与 Fengyiwei1234 思路类似，使用 `exit(0)` 提前结束程序。
- **ssSSSss_sunhaojia**：使用快速输入输出优化，整体逻辑与其他题解相同。
- **oceanfish**：使用宏定义和数组记录余数个数，实现基本思路。
- **qfpjm**：在 yxy666 的基础上进行空间优化，去掉不必要的数组。
- **WuMin4**：使用 `vector` 存储余数相同的数，方便输出。

### 所选的题解
- **yutong_Seafloor（4星）**：
  - 关键亮点：代码简洁，将输入和判断结合，减少不必要的计算。
  - 个人心得：强调注意输出格式，以及 `++b[a[i]%m]` 的重要性，否则会爆零。

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m,i,j,pd,a[10000010],b[10000010];
int main(){
    cin>>n>>k>>m;
    for(i=1;i<=n;i++){
        cin>>a[i];
        if(++b[a[i]%m]==k){//这里++b[a[i]%m]就是桶排
            cout<<"Yes"<<endl;
            for(j=1;j<=i;j++)
            if(a[j]%m==a[i]%m) cout<<a[j]<<" ";
            return 0;
        }
    }
    cout<<"No";
    return 0;
}//by·yutong_Seafloor 
```
**核心实现思想**：使用桶排的思想，用数组 `b` 记录每个余数的出现次数。在输入过程中，若某个余数的出现次数达到 $k$，则输出 `Yes` 并输出对应的 $k$ 个数；若遍历完所有数都未找到，则输出 `No`。

### 关键思路或技巧
- **同余定理的应用**：利用同余定理将判断两数差能否被 $m$ 整除转化为判断两数模 $m$ 的余数是否相同。
- **桶排思想**：使用数组记录每个余数的出现次数，方便统计和判断。
- **提前终止**：在输入过程中一旦找到满足条件的 $k$ 个数就输出结果，减少不必要的计算。

### 拓展思路
同类型题目通常会围绕数论中的同余性质展开，例如判断多个数之间的某种关系是否满足特定条件。解题的关键在于灵活运用同余定理，将复杂的条件转化为余数的关系，再通过合适的数据结构（如数组、`vector` 等）进行统计和判断。

### 推荐题目
1. [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：简单的模拟题，考察基本的输入输出和条件判断。
2. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)：基础的编程入门题，熟悉输入输出格式。
3. [P1421 小玉买文具](https://www.luogu.com.cn/problem/P1421)：涉及简单的数学计算和数据类型转换。

---
处理用时：32.43秒