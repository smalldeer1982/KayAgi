# 题目信息

# Restore Permutation

## 题目描述

An array of integers $ p_{1},p_{2}, \ldots,p_{n} $ is called a permutation if it contains each number from $ 1 $ to $ n $ exactly once. For example, the following arrays are permutations: $ [3,1,2], [1], [1,2,3,4,5] $ and $ [4,3,1,2] $ . The following arrays are not permutations: $ [2], [1,1], [2,3,4] $ .

There is a hidden permutation of length $ n $ .

For each index $ i $ , you are given $ s_{i} $ , which equals to the sum of all $ p_{j} $ such that $ j < i $ and $ p_{j} < p_{i} $ . In other words, $ s_i $ is the sum of elements before the $ i $ -th element that are smaller than the $ i $ -th element.

Your task is to restore the permutation.

## 说明/提示

In the first example for each $ i $ there is no index $ j $ satisfying both conditions, hence $ s_i $ are always $ 0 $ .

In the second example for $ i = 2 $ it happens that $ j = 1 $ satisfies the conditions, so $ s_2 = p_1 $ .

In the third example for $ i = 2, 3, 4 $ only $ j = 1 $ satisfies the conditions, so $ s_2 = s_3 = s_4 = 1 $ . For $ i = 5 $ all $ j = 1, 2, 3, 4 $ are possible, so $ s_5 = p_1 + p_2 + p_3 + p_4 = 10 $ .

## 样例 #1

### 输入

```
3
0 0 0
```

### 输出

```
3 2 1
```

## 样例 #2

### 输入

```
2
0 1
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
5
0 1 1 1 10
```

### 输出

```
1 4 3 2 5
```

# AI分析结果

### 题目内容翻译
## 恢复排列

### 题目描述
一个整数数组 $ p_{1},p_{2}, \ldots,p_{n} $ 被称为一个排列，当且仅当它包含从 $ 1 $ 到 $ n $ 的每个数字恰好一次。例如，以下数组是排列：$ [3,1,2] $、$ [1] $、$ [1,2,3,4,5] $ 和 $ [4,3,1,2] $ 。以下数组不是排列：$ [2] $、$ [1,1] $、$ [2,3,4] $ 。

现在有一个长度为 $ n $ 的隐藏排列。

对于每个索引 $ i $ ，给定 $ s_{i} $ ，$ s_{i} $ 等于所有满足 $ j < i $ 且 $ p_{j} < p_{i} $ 的 $ p_{j} $ 的和。换句话说，$ s_i $ 是第 $ i $ 个元素之前且小于第 $ i $ 个元素的所有元素的和。

你的任务是恢复这个排列。

### 说明/提示
在第一个样例中，对于每个 $ i $ ，都不存在满足两个条件的索引 $ j $ ，因此 $ s_i $ 始终为 $ 0 $ 。

在第二个样例中，当 $ i = 2 $ 时，$ j = 1 $ 满足条件，所以 $ s_2 = p_1 $ 。

在第三个样例中，对于 $ i = 2, 3, 4 $ ，只有 $ j = 1 $ 满足条件，所以 $ s_2 = s_3 = s_4 = 1 $ 。对于 $ i = 5 $ ，所有 $ j = 1, 2, 3, 4 $ 都满足条件，所以 $ s_5 = p_1 + p_2 + p_3 + p_4 = 10 $ 。

### 样例 #1
#### 输入
```
3
0 0 0
```
#### 输出
```
3 2 1
```

### 样例 #2
#### 输入
```
2
0 1
```
#### 输出
```
1 2
```

### 样例 #3
#### 输入
```
5
0 1 1 1 10
```
#### 输出
```
1 4 3 2 5
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕如何根据给定的 $s_i$ 数组恢复出原始的排列。题解的思路大致分为两类：
1. **倒序枚举 + 树状数组**：从后往前确定排列中的每个数，利用树状数组维护剩余可选数的前缀和，通过特定方法找到满足条件的数，时间复杂度一般为 $O(n\log n)$。
2. **找最后一个 0 + 线段树**：每次找到序列中最后一个为 0 的位置，该位置对应的数即为当前最小的数，用线段树维护区间修改和查询最小值，时间复杂度一般为 $O(n\log n)$。

### 所选题解
- **兮水XiShui丶（5星）**
    - **关键亮点**：思路清晰，详细推导了利用树状数组解决问题的过程，通过倒序枚举和树状数组的结合，优化了查找满足条件数的过程。
    - **个人心得**：作者第一次写这么长的题解，感觉很累，但详细地阐述了自己的思考过程。
- **Tx_Lcy（4星）**
    - **关键亮点**：思路易懂，从最后一个位置的值可以首先确定这一特性出发，考虑从后往前填写排列，通过二分和树状数组动态维护前缀和来求解。
- **yinqf（4星）**
    - **关键亮点**：提出了优化思路，从 $O(n^2)$ 优化到 $O(n\log n)$，采用倍增思想，边倍增边计算答案，提高了效率。

### 重点代码
#### 兮水XiShui丶的核心代码
```cpp
inline int lowbit(int x){
    return (x&-x);
}
void add(int x, int delta){
    while(x<=n){
        tree[x]+=delta;
        x+=lowbit(x);
    }
    return;
}
int query(int x){
    int sum = 0;
    while(x){
        sum+=tree[x];
        x-=lowbit(x);
    }
    return sum;
}
int find(int x){
    int num = 0 , sum=0;
    for(int i=log2(n)+1;i>=0;i--)
        if((num+(1<<i)<=n)&&(sum+tree[num+(1<<i)]<=x)){
            num+=(1<<i);
            sum+=tree[num];
        }
    return num + 1;
}
```
**核心实现思想**：`lowbit` 函数用于计算二进制下最低位 1 所代表的值。`add` 函数用于更新树状数组，`query` 函数用于查询前缀和。`find` 函数通过枚举树状数组的每一层，找到满足条件的数。

#### Tx_Lcy的核心代码
```cpp
struct Tree_Array{
    int c[N];
    inline int lowbit(int x){return x&-x;}
    inline void update(int x,int v){while (x<=n) c[x]+=v,x+=lowbit(x);}
    inline int query(int x){int res=0;while (x) res+=c[x],x-=lowbit(x);return res;}
}T;
inline int check(int x){return (x+1)*x/2-T.query(x);}
inline int qry(int x){
    int l=0,r=n;
    while (l<r){
        if (l+1==r){
            if (check(r)<=x) ++l;
            break;
        }
        int mid=(l+r)>>1;
        if (check(mid)>x) r=mid-1;
        else l=mid;
    }
    return l+1;
}
```
**核心实现思想**：定义了树状数组结构体 `Tree_Array`，包含更新和查询前缀和的函数。`check` 函数用于计算当前数的理论前缀和与树状数组中实际前缀和的差值。`qry` 函数通过二分查找满足条件的数。

#### yinqf的核心代码
```cpp
int lowbit(int x)
{
    return x&(-x);
}
void upd(int pos,int k)
{
    while(pos<=n)
    {
        f[pos]+=k;
        pos+=lowbit(pos);
    }
}
int find(int x)
{  
    int ret=0,sum=0;
    for(int i=lg[n];i>=0;i--)
    {
        if(ret+(1<<i)<=n&&sum+f[ret+(1<<i)]<=x)
        {
            ret=ret+(1<<i);
            sum+=f[ret];
        }
    }
    return ret+1;
}
```
**核心实现思想**：`lowbit` 函数计算最低位 1 所代表的值。`upd` 函数用于更新树状数组，`find` 函数通过倍增思想，边倍增边计算答案，找到满足条件的数。

### 最优关键思路或技巧
- **倒序枚举**：从后往前确定排列中的每个数，因为后面的数确定后，对前面数的影响可以通过树状数组或线段树进行维护。
- **树状数组/线段树**：利用树状数组或线段树高效地维护前缀和、区间修改和查询最小值等操作，将时间复杂度从 $O(n^2)$ 优化到 $O(n\log n)$。
- **倍增思想**：在树状数组上使用倍增思想，边倍增边计算答案，进一步优化查找满足条件数的过程。

### 可拓展之处
同类型题或类似算法套路：
- 其他需要根据某些条件恢复序列或数组的构造题。
- 涉及区间修改、查询的问题，都可以考虑使用线段树或树状数组来优化。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 个人心得总结
兮水XiShui丶作者第一次写长题解感觉很累，但详细地阐述了思考过程，说明在写题解时要注重思路的清晰表达，这样有助于自己和他人更好地理解问题和解决方法。

---
处理用时：60.05秒