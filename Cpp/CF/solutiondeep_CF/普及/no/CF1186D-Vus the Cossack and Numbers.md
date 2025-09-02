# 题目信息

# Vus the Cossack and Numbers

## 题目描述

Vus the Cossack has $ n $ real numbers $ a_i $ . It is known that the sum of all numbers is equal to $ 0 $ . He wants to choose a sequence $ b $ the size of which is $ n $ such that the sum of all numbers is $ 0 $ and each $ b_i $ is either $ \lfloor a_i \rfloor $ or $ \lceil a_i \rceil $ . In other words, $ b_i $ equals $ a_i $ rounded up or down. It is not necessary to round to the nearest integer.

For example, if $ a = [4.58413, 1.22491, -2.10517, -3.70387] $ , then $ b $ can be equal, for example, to $ [4, 2, -2, -4] $ .

Note that if $ a_i $ is an integer, then there is no difference between $ \lfloor a_i \rfloor $ and $ \lceil a_i \rceil $ , $ b_i $ will always be equal to $ a_i $ .

Help Vus the Cossack find such sequence!

## 说明/提示

The first example is explained in the legend.

In the second example, we can round the first and fifth numbers up, and the second and third numbers down. We can round the fourth number neither up, nor down.

## 样例 #1

### 输入

```
4
4.58413
1.22491
-2.10517
-3.70387
```

### 输出

```
4
2
-2
-4
```

## 样例 #2

### 输入

```
5
-6.32509
3.30066
-0.93878
2.00000
1.96321
```

### 输出

```
-6
3
-1
2
2
```

# AI分析结果

### 题目内容重写

**题目描述**

Vus the Cossack 有 $n$ 个实数 $a_i$。已知所有数的和为 $0$。他希望选择一个大小为 $n$ 的序列 $b$，使得所有数的和为 $0$，并且每个 $b_i$ 要么是 $\lfloor a_i \rfloor$，要么是 $\lceil a_i \rceil$。换句话说，$b_i$ 等于 $a_i$ 向上或向下取整后的值。不需要四舍五入到最近的整数。

例如，如果 $a = [4.58413, 1.22491, -2.10517, -3.70387]$，那么 $b$ 可以等于 $[4, 2, -2, -4]$。

注意，如果 $a_i$ 是整数，那么 $\lfloor a_i \rfloor$ 和 $\lceil a_i \rceil$ 没有区别，$b_i$ 将始终等于 $a_i$。

帮助 Vus the Cossack 找到这样的序列！

**说明/提示**

第一个例子在题目描述中已经解释。

在第二个例子中，我们可以将第一个和第五个数向上取整，第二个和第三个数向下取整。第四个数字既不需要向上取整，也不需要向下取整。

**样例 #1**

### 输入

```
4
4.58413
1.22491
-2.10517
-3.70387
```

### 输出

```
4
2
-2
-4
```

**样例 #2**

### 输入

```
5
-6.32509
3.30066
-0.93878
2.00000
1.96321
```

### 输出

```
-6
3
-1
2
2
```

### 算法分类
**构造**

### 题解分析与结论

本题的核心思路是通过先对所有数进行向下取整，然后根据总和与0的差值，选择部分数进行向上取整，以使得最终总和为0。难点在于如何处理负数的取整以及如何选择哪些数进行向上取整。

### 所选高星题解

#### 题解1：灵茶山艾府 (5星)
**关键亮点**：
- 简洁的证明方法，利用介值定理的思想，从$\sum\lfloor a_i\rfloor$到$\sum\lceil a_i\rceil$必然存在一个时刻达到0。
- 代码简洁，逻辑清晰，直接通过判断是否需要向上取整来调整结果。

**核心代码**：
```go
for _, v := range a {
    f := Floor(v)
    if s < 0 && v != f {
        s++
        Fprintln(out, f+1)
    } else {
        Fprintln(out, f)
    }
}
```

#### 题解2：Meatherm (4星)
**关键亮点**：
- 详细解释了负数的取整处理，特别是负数的向下取整需要额外减1。
- 通过字符串处理输入，避免了浮点数精度问题。

**核心代码**：
```cpp
for(rr int i=1;i<=n;++i){
    if(!need||!can[i]){
        cout<<Floor[i]<<endl;
    }
    else{
        --need,cout<<Floor[i]+1<<endl;
    }
}
```

#### 题解3：BYWYR (4星)
**关键亮点**：
- 明确指出了需要向上取整的个数为$\left|0-\sum{\left\lfloor{a_i}\right\rfloor}\right|$。
- 代码结构清晰，逻辑简单，易于理解。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(num_ceil==0) break;
    if(ceil(a[i])==a[i]||floor(a[i])==a[i]) continue;
    else ans[i]=ceil(a[i]),num_ceil--;
}
```

### 最优关键思路
1. **先向下取整**：将所有数先向下取整，计算总和。
2. **调整向上取整**：根据总和与0的差值，选择部分数进行向上取整，以使得最终总和为0。
3. **处理负数**：特别注意负数的向下取整需要额外减1。

### 可拓展之处
类似的问题可以通过先进行某种操作（如取整、取模等），然后根据总和或某种条件进行调整。这种思路在构造类问题中非常常见。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得摘录
- **Meatherm**：在处理负数时，特别强调了负数的向下取整需要额外减1，这一点在调试时容易被忽略。
- **BYWYR**：通过明确需要向上取整的个数，简化了问题的解决思路，代码实现更加简洁。

---
处理用时：38.25秒