# 题目信息

# Expected Median

## 题目描述

Arul has a binary array $ ^{\text{∗}} $ $ a $ of length $ n $ .

He will take all subsequences $ ^{\text{†}} $ of length $ k $ ( $ k $ is odd) of this array and find their median. $ ^{\text{‡}} $

What is the sum of all these values?

As this sum can be very large, output it modulo $ 10^9 + 7 $ . In other words, print the remainder of this sum when divided by $ 10^9 + 7 $ .

 $ ^{\text{∗}} $ A binary array is an array consisting only of zeros and ones.

 $ ^{\text{†}} $ An array $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by the deletion of several (possibly, zero or all) elements. Subsequences don't have to be contiguous.

 $ ^{\text{‡}} $ The median of an array of odd length $ k $ is the $ \frac{k+1}{2} $ -th element when sorted.

## 说明/提示

In the first test case, there are four subsequences of $ [1,0,0,1] $ with length $ k=3 $ :

- $ [1,0,0] $ : median $ = 0 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [1,0,1] $ : median $ = 1 $ .
- $ [0,0,1] $ : median $ = 0 $ .

 The sum of the results is $ 0+1+1+0=2 $ .In the second test case, all subsequences of length $ 1 $ have median $ 1 $ , so the answer is $ 5 $ .

## 样例 #1

### 输入

```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1```

### 输出

```
2
5
0
16
4
7
0
333606206```

# AI分析结果

### 题目中文重写
# 期望中位数

## 题目描述

阿鲁有一个长度为 $n$ 的二进制数组 $a$。

他将取出这个数组的所有长度为 $k$（$k$ 为奇数）的子序列，并求出它们的中位数。

所有这些中位数的和是多少？

由于这个和可能非常大，需要对 $10^9 + 7$ 取模。换句话说，打印这个和除以 $10^9 + 7$ 的余数。

$^{\text{∗}}$ 二进制数组是仅由 $0$ 和 $1$ 组成的数组。

$^{\text{†}}$ 如果数组 $b$ 可以通过删除数组 $a$ 中的若干（可能为零个或全部）元素得到，则称数组 $b$ 是数组 $a$ 的子序列。子序列不必是连续的。

$^{\text{‡}}$ 长度为奇数 $k$ 的数组的中位数是排序后的第 $\frac{k + 1}{2}$ 个元素。

## 说明/提示

在第一个测试用例中，$[1, 0, 0, 1]$ 长度为 $k = 3$ 的子序列有四个：
- $[1, 0, 0]$：中位数 $ = 0$。
- $[1, 0, 1]$：中位数 $ = 1$。
- $[1, 0, 1]$：中位数 $ = 1$。
- $[0, 0, 1]$：中位数 $ = 0$。

结果的和是 $0 + 1 + 1 + 0 = 2$。在第二个测试用例中，所有长度为 $1$ 的子序列的中位数都是 $1$，所以答案是 $5$。

## 样例 #1

### 输入
```
8
4 3
1 0 0 1
5 1
1 1 1 1 1
5 5
0 1 0 1 0
6 3
1 0 1 0 1 1
4 3
1 0 1 1
5 3
1 0 1 1 0
2 1
0 0
34 17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出
```
2
5
0
16
4
7
0
333606206
```

### 综合分析与结论
这些题解的核心思路都是利用组合数学来解决问题。由于数组是二进制的，只有中位数为 $1$ 时才会对答案有贡献，所以关键在于找出中位数为 $1$ 的子序列的数量。具体做法是枚举子序列中 $1$ 的个数 $i$，计算从所有 $1$ 中选 $i$ 个和从所有 $0$ 中选 $k - i$ 个的组合数之积，再对满足条件的 $i$ 求和。

算法要点：
1. **统计 $0$ 和 $1$ 的个数**：遍历数组，统计其中 $0$ 和 $1$ 的数量。
2. **预处理阶乘和逆元**：为了快速计算组合数，需要预处理阶乘和阶乘的逆元。
3. **枚举 $1$ 的个数**：根据中位数的定义，$1$ 的个数至少为 $\frac{k + 1}{2}$，枚举这个范围内的 $i$，计算组合数并求和。

解决难点：
1. **组合数计算**：在模运算下，除法需要用逆元来处理，因此要掌握逆元的计算方法。
2. **边界条件处理**：在枚举 $1$ 的个数时，要注意 $i$ 不能超过 $1$ 的总数，$k - i$ 不能超过 $0$ 的总数。

### 高评分题解
- **作者：aeiouaoeiu（5星）**
    - **关键亮点**：思路清晰，代码规范，详细说明了组合数的计算方法和求和公式，时间复杂度分析准确。
    - **核心代码**：
```cpp
ll qpow(ll a,ll b){ll E=1; for(;b;b>>=1,a=a*a%p)if(b&1) E=E*a%p; return E;}
ll C(ll a,ll b){return (a<b||b<0)?0:frac[a]*inv[b]%p*inv[a-b]%p;}
//...
for(int i=m;i<=k;i++) ans=(ans+C(cnt,i)*C(n-cnt,k-i)%p)%p;
```
核心实现思想：通过快速幂计算逆元，预处理阶乘和逆元后，利用组合数公式计算从 $c$ 个 $1$ 中选 $i$ 个和从 $n - c$ 个 $0$ 中选 $k - i$ 个的组合数，最后求和。

- **作者：Pink_Cut_Tree（4星）**
    - **关键亮点**：思路清晰，代码简洁，对组合数的计算和求和公式有详细解释，同时提供了题目和提交链接。
    - **核心代码**：
```cpp
int ksm(int a,int b){ //快速幂求逆元
    int ans=1;
    while(b){
        if(b&1){ 
            ans=ans*a%mod;
        }
        a=a*a%mod;
        b>>=1;
    }
    return ans%mod;
}
int C(int n,int m){
    if(n<m){
        return 0;
    }
    return f[n]*ksm(f[m],mod-2)%mod*ksm(f[n-m],mod-2)%mod; //乘法逆元
}
//...
for(int i=m;i<=min(k,cnt);i++){
    ans+=C(cnt,i)*C(n-cnt,k-i)%mod; ans%=mod;
}
```
核心实现思想：用快速幂求逆元，预处理阶乘数组，根据组合数公式计算组合数并求和，注意边界条件。

- **作者：cjh20090318（4星）**
    - **关键亮点**：对题意和分析有清晰的阐述，代码简洁，时间复杂度分析明确。
    - **核心代码**：
```cpp
int C(const int n,const int m){return n<m?0:(LL)f[n]*v[m]%mod*v[n-m]%mod;}//组合数。
//...
for(int i=(k+1)>>1,mi=s<k?s:k;i<=mi;i++) ans=(ans+(LL)C(s,i)*C(n-s,k-i)%mod)%mod;
```
核心实现思想：预处理阶乘和逆元，利用组合数公式计算组合数并求和，取模得到最终结果。

### 最优关键思路或技巧
- **转化问题**：将求所有子序列中位数之和的问题转化为求中位数为 $1$ 的子序列的数量，简化了问题。
- **组合数学**：利用组合数公式计算从 $0$ 和 $1$ 中选取元素的方案数，避免了枚举所有子序列。
- **预处理阶乘和逆元**：通过预处理阶乘和逆元，将组合数的计算复杂度从 $O(n)$ 降低到 $O(1)$。

### 拓展思路
同类型题或类似算法套路：
- 其他组合数学问题，如计算满足特定条件的排列组合数。
- 涉及模运算和逆元的问题，如在模意义下的除法运算。

### 洛谷题目推荐
1. [P1869 愚蠢的组合数](https://www.luogu.com.cn/problem/P1869)
2. [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)
3. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)

### 个人心得摘录与总结
- **wizard**：提到题目翻译问题，建议学习逆元知识，强调了逆元在组合数计算中的重要性。
- **wmrqwq**：给出了一些编程时的调试建议，如检查数组大小、考虑算法复杂度等。 

---
处理用时：42.35秒