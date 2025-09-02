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

### 题目内容重写
# 固定OR的递增序列

## 题目描述

给定一个正整数 $n$。找到满足以下条件的最长正整数序列 $a=[a_1,a_2,\ldots,a_k]$，并输出该序列：

- 对于所有 $1\le i\le k$，$a_i\le n$。
- $a$ 是严格递增的，即对于所有 $2\le i\le k$，$a_i>a_{i-1}$。
- 对于所有 $2\le i\le k$，$a_i\,|\,a_{i-1}=n$，其中 $|$ 表示按位或运算。

## 样例 #1

### 输入

```
4
1
3
14
23
```

### 输出

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

---

### 题解分析与结论

#### 综合分析
本题的核心在于构造一个严格递增的序列，使得相邻元素的按位或结果等于给定的 $n$。大多数题解都采用了二进制分解的思路，通过将 $n$ 的二进制表示中的某些位从 $1$ 变为 $0$ 来构造序列。关键点在于如何选择这些位，以确保序列的严格递增性和最大化序列长度。

#### 最优思路
1. **二进制分解**：将 $n$ 分解为二进制，记录所有为 $1$ 的位。
2. **构造序列**：从最高位开始，依次将每个 $1$ 变为 $0$，并生成对应的数，最后将 $n$ 本身加入序列。
3. **特判**：如果 $n$ 是 $2$ 的整数次幂（即二进制表示中只有一个 $1$），则直接输出 $n$。

#### 关键技巧
- **lowbit 函数**：用于快速找到最低位的 $1$，便于二进制分解。
- **倒序构造**：从最高位开始构造序列，确保序列严格递增。

#### 可拓展之处
- **类似问题**：可以扩展到其他位运算（如与、异或等）的序列构造问题。
- **优化思路**：进一步优化二进制分解的效率，减少不必要的计算。

#### 推荐题目
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---

### 所选高分题解

#### 题解1：Dioretsa (5星)
**关键亮点**：
- 详细解释了二进制分解和序列构造的过程。
- 使用了 lowbit 函数来高效地找到二进制位。
- 代码简洁且易于理解。

**核心代码**：
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

#### 题解2：Alex_Wei (4星)
**关键亮点**：
- 从理论角度分析了序列长度的上限。
- 提供了时间复杂度分析，确保算法效率。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
int main() {
    cin>>T;
    while(T--){
        cin>>n;
        if(n==(n&-n)){
            cout<<"1\n"<<n<<'\n';
            continue;
        }
        m=0;
        for(int i=62;~i;--i)
            if(n>>i&1)
                a[++m]=n^(1ll<<i);
        a[++m]=n;
        cout<<m<<'\n';
        for(int i=1;i<=m;++i)
            cout<<a[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
```

#### 题解3：sangshang (4星)
**关键亮点**：
- 通过贪心策略构造序列，确保序列长度最大化。
- 详细解释了每一步的构造思路，易于理解。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
int main() {
    int T;
    cin >> T;
    while (T--) {
        long long n;
        scanf("%lld", &n);
        tot = 0;
        for (int i = 0; (1LL << i) <= n; ++i) {
            if ((1LL << i)&n) {
                vec[++tot] = i;
            }
        }
        if (tot == 1) {
            printf("1\n");
            printf("%lld\n", n);
        } else {
            printf("%d\n", tot + 1);
            for (int i = tot; i >= 1; --i) {
                printf("%lld ", n - (1LL << vec[i]));
            }
            printf("%lld\n", n);
        }
    }
    return 0;
}
```

---

### 个人心得摘录
- **调试经历**：在处理二进制位时，需要注意位的顺序，确保从最高位开始处理，以避免序列不严格递增。
- **踩坑教训**：在特判 $n$ 为 $2$ 的整数次幂时，容易忽略直接输出 $n$ 的情况，导致序列长度计算错误。
- **顿悟感想**：通过二进制分解和 lowbit 函数，可以高效地解决此类位运算问题，进一步理解了位运算的灵活性和强大功能。

---
处理用时：43.06秒