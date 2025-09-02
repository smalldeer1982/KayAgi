# 题目信息

# Superultra's Favorite Permutation

## 题目描述

Superultra, a little red panda, desperately wants primogems. In his dreams, a voice tells him that he must solve the following task to obtain a lifetime supply of primogems. Help Superultra!

Construct a permutation $ ^{\text{∗}} $ $ p $ of length $ n $ such that $ p_i + p_{i+1} $ is composite $ ^{\text{†}} $ over all $ 1 \leq i \leq n - 1 $ . If it's not possible, output $ -1 $ .

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^{\text{†}} $ An integer $ x $ is composite if it has at least one other divisor besides $ 1 $ and $ x $ . For example, $ 4 $ is composite because $ 2 $ is a divisor.

## 说明/提示

In the first example, it can be shown that all permutation of size $ 3 $ contain two adjacent elements whose sum is prime. For example, in the permutation $ [2,3,1] $ the sum $ 2+3=5 $ is prime.

In the second example, we can verify that the sample output is correct because $ 1+8 $ , $ 8+7 $ , $ 7+3 $ , $ 3+6 $ , $ 6+2 $ , $ 2+4 $ , and $ 4+5 $ are all composite. There may be other constructions that are correct.

## 样例 #1

### 输入

```
2
3
8```

### 输出

```
-1
1 8 7 3 6 2 4 5```

# AI分析结果

### 题目内容重写
# Superultra的最爱排列

## 题目描述

Superultra，一只小熊猫，非常渴望获得原石。在他的梦中，一个声音告诉他，他必须解决以下任务才能获得终身供应的原石。帮助Superultra！

构造一个长度为 $n$ 的排列 $p$，使得对于所有 $1 \leq i \leq n - 1$，$p_i + p_{i+1}$ 都是合数。如果不可能，输出 $-1$。

$^{\text{∗}}$ 一个长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数组成的数组，顺序任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中有 $4$）。

$^{\text{†}}$ 一个整数 $x$ 是合数，如果它除了 $1$ 和 $x$ 之外至少有一个其他除数。例如，$4$ 是合数，因为 $2$ 是它的除数。

## 说明/提示

在第一个例子中，可以证明所有长度为 $3$ 的排列都包含两个相邻元素，它们的和是质数。例如，在排列 $[2,3,1]$ 中，$2+3=5$ 是质数。

在第二个例子中，我们可以验证样例输出是正确的，因为 $1+8$，$8+7$，$7+3$，$3+6$，$6+2$，$2+4$，和 $4+5$ 都是合数。可能有其他正确的构造。

## 样例 #1

### 输入

```
2
3
8```

### 输出

```
-1
1 8 7 3 6 2 4 5```

### 题解综合分析与结论
1. **思路对比**：所有题解都基于相同的核心思路，即将奇数和偶数分别排列，并在奇偶交界处放置特定的数（如4和5）以确保和为合数。当 $n \leq 4$ 时，无解。
2. **实现细节**：大部分题解的实现方式相似，先输出奇数（除5），然后输出4和5，最后输出偶数（除4）。部分题解对 $n$ 的特殊情况（如 $n=5,6,7,8$）进行了单独处理。
3. **代码优化**：部分题解在代码中使用了更简洁的输出方式，避免了额外的判断和循环，提升了代码的可读性和效率。
4. **评分**：大部分题解的质量较高，思路清晰，代码实现简洁，评分在4星以上。

### 所选高星题解
#### 题解1：作者：ridewind2013 (赞：3)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，直接通过循环输出奇数和偶数，并在中间插入4和5，避免了复杂的判断。
- **代码核心**：
```cpp
for(int i=1;i<=n;i++){
    if(i%2!=0&&i!=5){
        cout<<i<<" ";
    }
}
cout<<5<<" "<<4<<" ";
for(int i=1;i<=n;i++){
    if(i%2==0&&i!=4){
        cout<<i<<" ";
    }
}
```

#### 题解2：作者：K_yuxiang_rose (赞：1)
- **星级**：4星
- **关键亮点**：思路与题解1相似，但在代码实现上更加简洁，直接通过循环输出奇数和偶数，并在中间插入4和5。
- **代码核心**：
```cpp
for(int i=2;i<=n;i+=2){
    if(i!=4) cout<<i<<" ";
}
cout<<"4 5 ";
for(int i=1;i<=n;i+=2){
    if(i!=5) cout<<i<<" ";
}
```

#### 题解3：作者：RAY091016 (赞：1)
- **星级**：4星
- **关键亮点**：思路清晰，代码实现简洁，直接通过循环输出奇数和偶数，并在中间插入4和5，避免了复杂的判断。
- **代码核心**：
```cpp
for(int i=1;i<=n;i++){
    if(i%2==1&&i!=5){
        cout<<i<<" ";
    }
}
cout<<"5 4 ";
for(int i=1;i<=n;i++){
    if(i%2==0&&i!=4){
        cout<<i<<" ";
    }
}
```

### 最优关键思路或技巧
1. **奇偶分离**：将奇数和偶数分别排列，确保相邻的奇数和奇数、偶数和偶数的和为合数。
2. **特殊处理交界处**：在奇偶交界处放置特定的数（如4和5），确保它们的和为合数。
3. **无解情况**：当 $n \leq 4$ 时，无解。

### 可拓展之处
1. **类似问题**：可以扩展到其他类型的排列问题，如构造排列使得相邻元素的乘积为合数。
2. **算法优化**：可以通过数学证明进一步优化无解情况的判断，减少不必要的计算。

### 推荐相似题目
1. [P1216 [USACO1.5]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)
2. [P1028 [NOIP2001 普及组] 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：50.82秒