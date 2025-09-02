# 题目信息

# Numbers

## 题目描述

Furik loves writing all sorts of problems, especially such that he can't solve himself. You've got one of his problems, the one Furik gave to Rubik. And Rubik asks you to solve it.

There is integer $ n $ and array $ a $ , consisting of ten integers, indexed by numbers from 0 to 9. Your task is to count the number of positive integers with the following properties:

- the number's length does not exceed $ n $ ;
- the number doesn't have leading zeroes;
- digit $ i $ $ (0<=i<=9) $ occurs in the number at least $ a[i] $ times.

## 说明/提示

In the first sample number 9 meets the requirements.

In the second sample number 10 meets the requirements.

In the third sample numbers 10, 110, 210, 120, 103 meet the requirements. There are other suitable numbers, 36 in total.

## 样例 #1

### 输入

```
1
0 0 0 0 0 0 0 0 0 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 1 0 0 0 0 0 0 0 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 1 0 0 0 0 0 0 0 0
```

### 输出

```
36
```

# AI分析结果

### 题目翻译
#### 数字

#### 题目描述
Furik 喜欢编写各种问题，尤其是那些他自己都无法解决的问题。你拿到了他的一个问题，这是 Furik 给 Rubik 的问题，而 Rubik 请你解决它。

给定一个整数 $n$ 和一个由十个整数组成的数组 $a$，数组下标从 0 到 9。你的任务是计算满足以下条件的正整数的数量：
- 数字的长度不超过 $n$；
- 数字没有前导零；
- 数字中数位 $i$（$0\leq i\leq 9$）出现的次数至少为 $a[i]$ 次。

#### 说明/提示
在第一个样例中，数字 9 满足要求。
在第二个样例中，数字 10 满足要求。
在第三个样例中，数字 10、110、210、120、103 满足要求。还有其他合适的数字，总共有 36 个。

#### 样例 #1
##### 输入
```
1
0 0 0 0 0 0 0 0 0 1
```
##### 输出
```
1
```

#### 样例 #2
##### 输入
```
2
1 1 0 0 0 0 0 0 0 0
```
##### 输出
```
1
```

#### 样例 #3
##### 输入
```
3
1 1 0 0 0 0 0 0 0 0
```
##### 输出
```
36
```

### 综合分析与结论
这两道题解都使用动态规划来解决问题，通过合理设计状态和转移方程来计算满足条件的数字个数。

#### 思路对比
- **TM_Sharweek**：先尝试了复杂的状态设计，发现有重复计数问题后，通过规定限制满足的严格顺序来避免重复，从 9 往小逐个满足限制。
- **HBWH_zzz**：直接设 $f_{i,j}$ 表示只用 $j\sim 9$ 的数填满 $i$ 位，根据不同数位的插入情况推导转移方程。

#### 算法要点对比
- **TM_Sharweek**：状态 $f_{i,j}$ 表示考虑到前 $i$ 位数，已经满足了 $a_j$ 至 $a_9$，此后不会再添加数位 $j$ 至 $9$，没有添加 $0$ 至 $j - 1$ 的方案数。转移时使用组合数，注意 0 不能在首位。
- **HBWH_zzz**：状态 $f_{i,j}$ 表示只用 $j\sim 9$ 的数填满 $i$ 位。转移时同样使用组合数，0 不能在首位时组合数有所变化。

#### 解决难点对比
- **TM_Sharweek**：主要解决了重复计数问题，通过规定限制满足顺序来避免。
- **HBWH_zzz**：重点在于合理设计状态和转移方程，处理 0 不能在首位的情况。

### 题解选择
- **TM_Sharweek**：4 星。关键亮点在于详细展示了状态设计的优化过程，对重复计数问题的分析和解决思路清晰。
- **HBWH_zzz**：4 星。关键亮点在于思路简洁直接，代码实现使用记忆化搜索，可读性较好。

### 重点代码
#### TM_Sharweek
```cpp
for (int i = 0; i <= n; i++) {
    for (int j = 9; j >= 1; j--) {
        for (int k = 0; k <= i-a[j]; k++) {
            f[i][j] = (f[i][j] + f[k][j + 1] * c[i-k][i] % P) % P;
        }
    }
    for (int k = 0; k <= i-a[0]; k++) {
        f[i][0] = (f[i][0] + f[k][1] * c[i-k][i - 1] % P) % P;
    }
}
```
核心思想：通过三重循环进行状态转移，根据不同数位的情况和组合数计算方案数。

#### HBWH_zzz
```cpp
ll dp(int i,int j){
    if(j==9)
        return (i>=a[9]);
    if(f[i][j]!=-1)
        return f[i][j];
    if(j!=0){
        ll ret=0;
        for(int k=a[j];k<=i;++k){
            ret=(ret+dp(i-k,j+1)*C[i][k])%mod;
        }
        return f[i][j]=ret;
    }
    ll ret=0;
    for(int k=a[0];k<=i;++k){
        ret=(ret+dp(i-k,1)*C[i-1][k])%mod;
    }
    return f[i][j]=ret;
}
```
核心思想：使用记忆化搜索进行状态转移，根据不同数位的情况和组合数计算方案数。

### 最优关键思路或技巧
- 对于计数问题，合理设计动态规划状态是关键，要考虑避免重复计数。
- 当遇到重复计数问题时，可以通过规定某些操作的顺序来解决。
- 处理 0 不能在首位的情况时，组合数的计算需要特殊处理。

### 可拓展之处
同类型题可以是类似的数位计数问题，例如改变数字的限制条件、增加数位范围等。类似算法套路包括使用动态规划解决计数问题，通过合理设计状态和转移方程，结合组合数进行计算。

### 洛谷题目推荐
- P1088 [火星人](https://www.luogu.com.cn/problem/P1088)
- P1137 [旅行计划](https://www.luogu.com.cn/problem/P1137)
- P1434 [滑雪](https://www.luogu.com.cn/problem/P1434)

### 个人心得
- **TM_Sharweek**：在设计状态和转移方程时，要注意避免重复计数问题，当发现原思路有问题时，要及时更换思路。例如本题中，最初的状态设计会导致重复计数，经过思考后通过规定限制满足的顺序解决了该问题。

---
处理用时：33.24秒