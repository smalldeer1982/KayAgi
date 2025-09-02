# 题目信息

# Increasing Sequence with Fixed OR

## 题目描述

You are given a positive integer $ n $ . Find the longest sequence of positive integers $ a=[a_1,a_2,\ldots,a_k] $ that satisfies the following conditions, and print the sequence:

- $ a_i\le n $ for all $ 1\le i\le k $ .
- $ a $ is strictly increasing. That is, $ a_i>a_{i-1} $ for all $ 2\le i\le k $ .
- $ a_i\,|\,a_{i-1}=n $ for all $ 2\le i\le k $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 样例 #1

### 输入

```
4
1
3
14
23```

### 输出

```
1
1
3
1 2 3
4
4 10 12 14
5
7 18 21 22 23```

# AI分析结果

### 题目中文重写
## 固定按位或的递增序列

### 题目描述
给定一个正整数 $n$。找出满足以下条件的最长正整数序列 $a = [a_1, a_2, \ldots, a_k]$，并输出该序列：
- 对于所有 $1\leq i\leq k$，有 $a_i\leq n$。
- 序列 $a$ 严格递增。即对于所有 $2\leq i\leq k$，有 $a_i > a_{i - 1}$。
- 对于所有 $2\leq i\leq k$，有 $a_i\,|\,a_{i - 1} = n$，其中 $|$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

### 样例 #1
#### 输入
```
4
1
3
14
23
```
#### 输出
```
1
1
3
1 2 3
4
4 10 12 14
5
7 18 21 22 23
```

### 题解综合分析与结论
这些题解大多围绕二进制展开思路，因为题目中的按位或运算与二进制紧密相关。核心要点是通过对 $n$ 的二进制表示进行操作来构造满足条件的序列。

#### 思路对比
- 多数题解采用贪心策略，让序列元素尽可能大或尽可能小来满足长度最大的要求。
- 部分题解从二进制位的变化规律入手，如每次将 $n$ 的一个二进制位 $1$ 变为 $0$ 来构造序列。

#### 算法要点
- 计算 $n$ 的二进制表示中 $1$ 的个数（`popcount`），这决定了序列的最大长度（通常为 `popcount(n) + 1`）。
- 利用位运算（如 `lowbit`、`xor` 等）来修改 $n$ 的二进制位，得到序列中的元素。

#### 解决难点
- 处理 $n$ 为 $2$ 的整数次幂的特殊情况，此时序列长度为 $1$。
- 保证构造的序列严格递增且相邻元素按位或结果为 $n$。

### 评分较高的题解
- **作者：Dioretsa（5星）**
    - **关键亮点**：思路清晰，通过具体例子详细解释了构造方法，代码简洁且使用 `lowbit` 优化，可读性高。
    - **核心代码**：
```cpp
long long lowbit(long long x){
    return x&-x;
}
int main() {
    cin>>T;
    while(T--){
        cin>>n;
        m=n,tmp=0,cnt=1,ans[1]=n;
        while(m!=0){
            tmp=lowbit(m);
            if(n-tmp>0) ans[++cnt]=n-tmp;
            m-=tmp;
        }
        cout<<cnt<<endl;
        for(int i=cnt;i>=1;i--) cout<<ans[i]<<" ";
        cout<<endl;
    }
    return 0;
}
```
核心思想：通过 `lowbit` 函数找到 $n$ 二进制表示中最低位的 $1$，将其变为 $0$ 得到序列中的元素。

- **作者：Alex_Wei（4星）**
    - **关键亮点**：从理论上分析了序列的性质和上界，给出了严谨的证明，时间复杂度分析清晰。
    - **核心思路**：当 $k > 1$ 时，所有 $a_i$ 在二进制下是 $n$ 的子集，答案不超过 $\mathrm{popcount}(n) + 1$，构造 $[n - 2 ^ {p_c}, \cdots, n - 2 ^ {p_1}, n]$ 达到该上界。

- **作者：Special_Tony（4星）**
    - **关键亮点**：提供了两种代码实现方法，思路直接，代码结构清晰，对特殊情况处理明确。
    - **核心代码（方法1）**：
```cpp
int main () {
    cin >> t;
    while (t --) {
        cin >> n;
        if (n == (n & -n)) {
            cout << "1\n" << n << '\n';
            continue ;
        }
        m = 0;
        for (int i = 62; ~i; -- i)
            if (n >> i & 1)
                a[++ m] = n ^ (1ll << i);
        a[++ m] = n;
        cout << m << '\n';
        for (int i = 1; i <= m; ++ i)
            cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}
```
核心思想：从高到低枚举 $n$ 的二进制位，将 $n$ 与对应位的 $1$ 进行异或操作得到序列元素。

### 最优关键思路或技巧
- **二进制思维**：将问题转化为二进制位的操作，通过分析 $n$ 的二进制表示来构造序列。
- **贪心策略**：在构造序列时，每次选择最优的二进制位变化，以保证序列长度最大。
- **位运算优化**：使用 `lowbit`、`xor` 等位运算，提高代码效率。

### 拓展思路
同类型题目可能会改变条件，如将按位或运算改为其他位运算，或者增加序列元素的其他限制条件。解题的关键仍然是对二进制表示的分析和操作。

### 洛谷相似题目推荐
- [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)
- [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)
- [P2312 [NOIP2014 提高组] 解方程](https://www.luogu.com.cn/problem/P2312)

### 个人心得摘录与总结
- **作者：Guchenxi0971**：提到“一定要加 `1ll`，不然会像某人一样吃 4 发罚时”，强调了在处理大整数时使用 `1ll` 的重要性，避免因数据类型问题导致错误。
- **作者：EricWan**：提到“不开 `long long` 见祖宗”，提醒在处理可能较大的整数时要使用 `long long` 类型，防止溢出。
- **作者：Chillturtle**：提到“特别注意：当 $n$ 为 $1$ 的时候要进行特判。~~其实也可以在循环内判断~~。不开 `long long` 见祖宗”，指出了特殊情况的处理和数据类型的重要性。 

---
处理用时：35.93秒