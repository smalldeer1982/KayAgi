# 题目信息

# Permutations

## 题目描述

You are given a permutation $ p $ of numbers $ 1,2,...,n $ . Let's define $ f(p) $ as the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513B2/01b3997850b3844bd3627bf7c28ebf2176a4c489.png)Find the lexicographically $ m $ -th permutation of length $ n $ in the set of permutations having the maximum possible value of $ f(p) $ .

## 说明/提示

In the first example, both permutations of numbers {1, 2} yield maximum possible $ f(p) $ which is equal to 4. Among them, $ (2,1) $ comes second in lexicographical order.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 3 2 
```

# AI分析结果

### 题目内容
# 排列

## 题目描述
给定一个由数字 $1,2,\cdots,n$ 组成的排列 $p$ 。定义 $f(p)$ 为如下求和式：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF513B2/01b3997850b3844bd3627bf7c28ebf2176a4c489.png)在所有使 $f(p)$ 取得最大值的长度为 $n$ 的排列集合中，找出字典序第 $m$ 大的排列。

## 说明/提示
在第一个样例中，数字 $\{1, 2\}$ 的两个排列都能使 $f(p)$ 取得最大值，该最大值为 $4$ 。在字典序中，$(2,1)$ 排在第二个。

## 样例 #1
### 输入
```
2 2
```
### 输出
```
2 1 
```

## 样例 #2
### 输入
```
3 2
```
### 输出
```
1 3 2 
```

### 算法分类
数学

### 综合分析与结论
两题解思路均基于对使 $f(p)$ 最大的排列规律的探索。“Wf_yjqd”题解通过打表和证明得出规律，进而用递归构造排列；“enyyyyyyy”题解虽简洁但思路阐述不充分，且正确性存疑，未严格证明其与题目要求的一致性。

### 所选的题解
 - **作者**：Wf_yjqd
 - **星级**：4星
 - **关键亮点**：先通过打表观察规律，再严格证明使 $f(p)$ 最大的排列特征，即每个数放在剩余位置的最左或最右边，利用 $2$ 的幂次与 $m$ 对比递归构造出目标排列，思路清晰，代码实现完整。
 - **个人心得**：建议先做暴力版本题目辅助理解，通过打表找规律。

### 重点代码核心实现思想
通过递归函数 `dfs` 来确定每个位置的数字。每次递归时，根据当前剩余数字个数对应的 $2$ 的幂次与 $m$ 的大小关系，决定当前数字放在左边还是右边，直到确定整个排列。

### 核心代码片段
```cpp
void dfs(ll now,ll l,ll r,ll th){
    if(l==r){//边界
        ans[l]=now;
        return ;
    }
    if(th<=poww[r-l-1]){//左
        ans[l]=now;
        dfs(now+1,l+1,r,th);
        return ;
    }
    ans[r]=now;//右
    dfs(now+1,l,r-1,th-poww[r-l-1]);
    return ;
}
```

### 最优关键思路或技巧
通过打表观察和数学证明找到使 $f(p)$ 最大的排列规律，利用 $2$ 的幂次来确定每个数在排列中的位置，巧妙地将问题转化为递归构造排列。

### 可拓展之处
此类题目属于组合数学中关于排列规律探索的问题，类似套路是先通过小数据打表找规律，再进行数学证明，最后根据规律构造结果。

### 推荐题目
 - [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
 - [P1338 末日的传说](https://www.luogu.com.cn/problem/P1338)
 - [P1851 奇怪的电梯](https://www.luogu.com.cn/problem/P1851)

---
处理用时：45.20秒