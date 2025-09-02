# 题目信息

# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 2 1 16
```

### 输出

```
4
```

# AI分析结果

### 题目内容重写

Vasya 有一个由 $n$ 个整数 $a_1, a_2, \dots, a_n$ 组成的序列 $a$。Vasya 可以进行以下操作：选择序列中的某个数，并交换其二进制表示中的任意两位。例如，Vasya 可以将数字 $6$（$00000000110_2$）转换为 $3$（$00000000011_2$）、$12$（$000000001100_2$）、$1026$（$10000000010_2$）等。Vasya 可以在序列中的任何数上使用此操作任意次（包括零次）。

Vasya 称一个序列为“好序列”，如果通过上述操作，他可以得到一个序列，使得所有元素的[按位异或](https://en.wikipedia.org/wiki/Exclusive_or)结果为 $0$。

对于给定的序列 $a_1, a_2, \ldots, a_n$，Vasya 想要计算满足 $1 \le l \le r \le n$ 且序列 $a_l, a_{l + 1}, \dots, a_r$ 是“好序列”的整数对 $(l, r)$ 的数量。

### 说明/提示

在第一个样例中，$(2, 3)$ 和 $(1, 3)$ 是有效的。$(2, 3)$ 有效是因为 $a_2 = 7 \rightarrow 11$，$a_3 = 14 \rightarrow 11$，且 $11 \oplus 11 = 0$，其中 $\oplus$ 表示按位异或。$(1, 3)$ 有效是因为 $a_1 = 6 \rightarrow 3$，$a_2 = 7 \rightarrow 13$，$a_3 = 14 \rightarrow 14$，且 $3 \oplus 13 \oplus 14 = 0$。

在第二个样例中，$(1, 2)$、$(2, 3)$、$(3, 4)$ 和 $(1, 4)$ 是有效的。

### 样例 #1

#### 输入

```
3
6 7 14
```

#### 输出

```
2
```

### 样例 #2

#### 输入

```
4
1 2 1 16
```

#### 输出

```
4
```

---

### 题解分析与结论

#### 题解对比与评分

1. **开始新的记忆 (4星)**
   - **关键亮点**：使用前缀和和滑动窗口优化，时间复杂度为 $O(n \times 64)$，代码简洁易懂。
   - **个人心得**：通过滑动窗口处理最大值问题，避免了复杂的数据结构。

2. **蒟酱 (4星)**
   - **关键亮点**：利用前缀和和桶优化，时间复杂度为 $O(n \times 60)$，代码简洁且高效。
   - **个人心得**：通过枚举长度小于60的子串，避免了复杂的数据结构，代码实现简洁。

3. **Jsxts_ (4星)**
   - **关键亮点**：使用笛卡尔树和启发式合并，时间复杂度为 $O(n \log n)$，代码实现较为复杂但效率高。
   - **个人心得**：通过笛卡尔树处理最大值问题，结合启发式合并优化时间复杂度。

#### 最优关键思路

1. **前缀和与滑动窗口**：通过前缀和快速计算区间和，结合滑动窗口处理最大值问题，时间复杂度为 $O(n \times 64)$。
2. **桶优化**：利用桶记录前缀和的奇偶性，结合枚举长度小于60的子串，时间复杂度为 $O(n \times 60)$。
3. **笛卡尔树与启发式合并**：通过笛卡尔树处理最大值问题，结合启发式合并优化时间复杂度，时间复杂度为 $O(n \log n)$。

#### 可拓展之处

1. **类似问题**：可以扩展到其他需要处理区间最大值和区间和的问题，如区间最小值、区间乘积等。
2. **数据结构优化**：可以结合其他数据结构如线段树、树状数组等进一步优化时间复杂度。

#### 推荐题目

1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)

#### 个人心得摘录

- **开始新的记忆**：通过滑动窗口处理最大值问题，避免了复杂的数据结构，代码实现简洁。
- **蒟酱**：通过枚举长度小于60的子串，避免了复杂的数据结构，代码实现简洁且高效。
- **Jsxts_**
  - 通过笛卡尔树处理最大值问题，结合启发式合并优化时间复杂度，代码实现较为复杂但效率高。
  - 调试过程中发现最大值处理较为复杂，最终通过笛卡尔树解决了问题。

### 核心代码片段

#### 开始新的记忆

```cpp
for(int i=1;i<=n;++i)
{
    long long x;
    cin>>x;
    while(x>0)
    {
        num[i]+=(x%2);
        x/=2;
    }
    anss[i]=anss[i-1]+num[i];
    ans+=cnt[anss[i]%2];
    for(int j=i,k=i+1,maxn=0;j>=1 && j>=i-64;--j)
    {
        while(k>j) 
            maxn=max(maxn,num[--k]);
        if(maxn*2>anss[i]-anss[j-1] && anss[i]%2==anss[j-1]%2) 
            --ans;
    }
    ++cnt[anss[i]%2];
}
```

#### 蒟酱

```cpp
for(int l=1;l<=n;l++){
    ans+=cnt[(sum+=a[l])&1]++;
    for(int r=l,max=0,num=0;r<=std::min(n,l+58);r++)
        max=std::max(max,a[r]),
        ans-=(num+=a[r])%2==0&&2*max>num;
}
```

#### Jsxts_

```cpp
for(int i=1;i<=n;i++){
    while(top&&a[i]>stk[top].val)L[i]=stk[top--].id;
    if(top)R[stk[top].id]=i;
    stk[++top]={a[i],i};
}
for(int i=1;i<=n;i++)fa[L[i]]=fa[R[i]]=i;
for(int i=1;i<=n;i++)if(!fa[i])rt=i;
dfs(rt);
```

---
处理用时：58.18秒