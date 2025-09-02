# 题目信息

# Complex Market Analysis

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609C/18b254da391d541c237ec2ae3c537650bfbdb064.png)While performing complex market analysis William encountered the following problem:

For a given array $ a $ of size $ n $ and a natural number $ e $ , calculate the number of pairs of natural numbers $ (i, k) $ which satisfy the following conditions:

- $ 1 \le i, k $
- $ i + e \cdot k \le n $ .
- Product $ a_i \cdot a_{i + e} \cdot a_{i + 2 \cdot e} \cdot \ldots \cdot a_{i + k \cdot e}  $ is a prime number.

A prime number (or a prime) is a natural number greater than 1 that is not a product of two smaller natural numbers.

## 说明/提示

In the first example test case two pairs satisfy the conditions:

1. $ i = 2, k = 1 $ , for which the product is: $ a_{2} \cdot a_{5} = 2 $ which is a prime number.
2. $ i = 3, k = 1 $ , for which the product is: $ a_{3} \cdot a_{6} = 19 $ which is a prime number.

In the second example test case there are no pairs that satisfy the conditions.

In the third example test case four pairs satisfy the conditions:

1. $ i = 1, k = 1 $ , for which the product is: $ a_{1} \cdot a_{4} = 2 $ which is a prime number.
2. $ i = 1, k = 2 $ , for which the product is: $ a_{1} \cdot a_{4} \cdot a_{7} = 2 $ which is a prime number.
3. $ i = 3, k = 1 $ , for which the product is: $ a_{3} \cdot a_{6} = 2 $ which is a prime number.
4. $ i = 6, k = 1 $ , for which the product is: $ a_{6} \cdot a_{9} = 2 $ which is a prime number.

In the fourth example test case there are no pairs that satisfy the conditions.

In the fifth example test case five pairs satisfy the conditions:

1. $ i = 1, k = 1 $ , for which the product is: $ a_{1} \cdot a_{2} = 2 $ which is a prime number.
2. $ i = 1, k = 2 $ , for which the product is: $ a_{1} \cdot a_{2} \cdot a_{3} = 2 $ which is a prime number.
3. $ i = 1, k = 3 $ , for which the product is: $ a_{1} \cdot a_{2} \cdot a_{3} \cdot a_{4} = 2 $ which is a prime number.
4. $ i = 2, k = 1 $ , for which the product is: $ a_{2} \cdot a_{3} = 2 $ which is a prime number.
5. $ i = 2, k = 2 $ , for which the product is: $ a_{2} \cdot a_{3} \cdot a_{4} = 2 $ which is a prime number.

In the sixth example test case there are no pairs that satisfy the conditions.

## 样例 #1

### 输入

```
6
7 3
10 2 1 3 1 19 3
3 2
1 13 1
9 3
2 4 2 1 1 1 1 4 2
3 1
1 1 1
4 1
1 2 1 1
2 2
1 2```

### 输出

```
2
0
4
0
5
0```

# AI分析结果

### 题目内容重写
# 复杂市场分析

## 题目描述

在进行复杂的市场分析时，William遇到了以下问题：

给定一个大小为 $n$ 的数组 $a$ 和一个自然数 $e$，计算满足以下条件的自然数对 $(i, k)$ 的数量：

- $1 \le i, k$
- $i + e \cdot k \le n$ 。
- 乘积 $a_i \cdot a_{i + e} \cdot a_{i + 2 \cdot e} \cdot \ldots \cdot a_{i + k \cdot e}  $ 是一个质数。

质数（或素数）是大于1的自然数，且不是两个较小自然数的乘积。

## 说明/提示

在第一个示例测试用例中，有两个满足条件的对：

1. $i = 2, k = 1$ ，乘积为：$a_{2} \cdot a_{5} = 2$ ，这是一个质数。
2. $i = 3, k = 1$ ，乘积为：$a_{3} \cdot a_{6} = 19$ ，这是一个质数。

在第二个示例测试用例中，没有满足条件的对。

在第三个示例测试用例中，有四个满足条件的对：

1. $i = 1, k = 1$ ，乘积为：$a_{1} \cdot a_{4} = 2$ ，这是一个质数。
2. $i = 1, k = 2$ ，乘积为：$a_{1} \cdot a_{4} \cdot a_{7} = 2$ ，这是一个质数。
3. $i = 3, k = 1$ ，乘积为：$a_{3} \cdot a_{6} = 2$ ，这是一个质数。
4. $i = 6, k = 1$ ，乘积为：$a_{6} \cdot a_{9} = 2$ ，这是一个质数。

在第四个示例测试用例中，没有满足条件的对。

在第五个示例测试用例中，有五个满足条件的对：

1. $i = 1, k = 1$ ，乘积为：$a_{1} \cdot a_{2} = 2$ ，这是一个质数。
2. $i = 1, k = 2$ ，乘积为：$a_{1} \cdot a_{2} \cdot a_{3} = 2$ ，这是一个质数。
3. $i = 1, k = 3$ ，乘积为：$a_{1} \cdot a_{2} \cdot a_{3} \cdot a_{4} = 2$ ，这是一个质数。
4. $i = 2, k = 1$ ，乘积为：$a_{2} \cdot a_{3} = 2$ ，这是一个质数。
5. $i = 2, k = 2$ ，乘积为：$a_{2} \cdot a_{3} \cdot a_{4} = 2$ ，这是一个质数。

在第六个示例测试用例中，没有满足条件的对。

## 样例 #1

### 输入

```
6
7 3
10 2 1 3 1 19 3
3 2
1 13 1
9 3
2 4 2 1 1 1 1 4 2
3 1
1 1 1
4 1
1 2 1 1
2 2
1 2```

### 输出

```
2
0
4
0
5
0```

### 算法分类
质数

### 题解分析与结论
本题的核心在于如何高效地计算满足条件的数对 $(i, k)$，使得乘积为质数。由于质数的性质，乘积为质数的条件是序列中恰好有一个质数，其余均为1。因此，题解的主要思路是枚举每个质数，并计算其左右连续的1的个数，从而得到满足条件的数对数量。

### 所选高分题解
#### 题解1：智子 (5星)
- **关键亮点**：通过预处理质数和左右连续的1的个数，高效计算满足条件的数对数量。代码清晰，时间复杂度为 $O(n + w)$，其中 $w$ 是值域大小。
- **代码核心思想**：使用线性筛预处理质数，然后预处理每个位置左右连续的1的个数，最后枚举每个质数，计算贡献。
```cpp
void init(int n = MAXN - 1) {
    vis[1] = true;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            pri[++tot] = i;
        }
        for(int j = 1; j <= tot && i * pri[j] <= n; j++) {
            vis[i * pri[j]] = true;
            if(i % pri[j] == 0) {
                break;
            }
        }
    }
}
```

#### 题解2：XL4453 (4星)
- **关键亮点**：将问题转化为分组处理，从每个质数开始向两边拓展，计算满足条件的数对数量。代码简洁，时间复杂度为 $O(n)$。
- **代码核心思想**：预处理质数，然后对于每个质数，计算其左右连续的1的个数，并根据乘法原理计算贡献。
```cpp
void work(){
	for(int i=1;i<=cnt;i++){
		if(c[num[i]]==0){
			int cnt1=0,cnt2=0;
			for(int j=i-1;j>=1;j--){	
				if(num[j]==1)cnt1++;
				else break;
			}
			for(int j=i+1;j<=cnt;j++){
				if(num[j]==1)cnt2++;
				else break;
			}
			ans+=cnt1*cnt2+cnt1+cnt2;
		}
	}
}
```

#### 题解3：czh___ (4星)
- **关键亮点**：通过预处理质数，计算每个质数前后连续的1的个数，并根据公式计算贡献。代码简洁，时间复杂度为 $O(n)$。
- **代码核心思想**：预处理质数，然后对于每个质数，计算其前后连续的1的个数，并根据公式计算贡献。
```cpp
void init(){
	f[0] = f[1] = 1;
	n=1e6+1;
	for(int i=2;i<=n;i++)
		if(f[i]) 
			continue;
		else
			for(int j=i+i;j<=n;j+=i) 
				f[j]=1;
}
```

### 最优关键思路或技巧
1. **预处理质数**：使用线性筛预处理质数，方便后续判断。
2. **预处理连续的1**：通过预处理每个位置左右连续的1的个数，快速计算满足条件的数对数量。
3. **乘法原理**：利用乘法原理计算每个质数对答案的贡献，避免重复计算。

### 可拓展之处
类似的问题可以扩展到其他数论问题，如计算乘积为某个特定数的数对数量，或者计算满足其他数论条件的数对数量。

### 推荐题目
1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
3. [P1075 [NOIP2012 普及组] 质因数分解](https://www.luogu.com.cn/problem/P1075)

---
处理用时：48.12秒