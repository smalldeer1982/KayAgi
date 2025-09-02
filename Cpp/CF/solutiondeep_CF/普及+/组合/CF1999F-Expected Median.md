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

### 题目翻译
## 预期中位数

### 题目描述
阿鲁有一个长度为 $n$ 的二进制数组 $a$。

他将取出这个数组中所有长度为 $k$（$k$ 为奇数）的子序列，并求出它们的中位数。

所有这些中位数的和是多少？

由于这个和可能非常大，将结果对 $10^9 + 7$ 取模。换句话说，打印这个和除以 $10^9 + 7$ 的余数。

注：
 - 二进制数组是仅由 $0$ 和 $1$ 组成的数组。
 - 若数组 $b$ 可以通过删除数组 $a$ 中的若干（可能为零个或全部）元素得到，则称数组 $b$ 是数组 $a$ 的子序列。子序列不必是连续的。
 - 长度为奇数 $k$ 的数组的中位数是排序后的第 $\frac{k + 1}{2}$ 个元素。

### 说明/提示
在第一个测试用例中，$[1, 0, 0, 1]$ 长度为 $k = 3$ 的子序列有四个：
 - $[1, 0, 0]$：中位数 $ = 0$。
 - $[1, 0, 1]$：中位数 $ = 1$。
 - $[1, 0, 1]$：中位数 $ = 1$。
 - $[0, 0, 1]$：中位数 $ = 0$。

结果的总和是 $0 + 1 + 1 + 0 = 2$。在第二个测试用例中，所有长度为 $1$ 的子序列的中位数都是 $1$，所以答案是 $5$。

### 样例 #1
#### 输入
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

#### 输出
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
这些题解的核心思路一致，均利用组合数学解决问题。由于是 $01$ 数组，仅中位数为 $1$ 时对答案有贡献，所以通过枚举子序列中 $1$ 的个数 $i$，计算从所有 $1$ 中选 $i$ 个、从所有 $0$ 中选 $k - i$ 个的方案数，再将满足条件的方案数累加得到结果。

算法要点：
 - 统计数组中 $0$ 和 $1$ 的个数。
 - 预处理阶乘和逆元，以便 $O(1)$ 计算组合数。
 - 枚举 $1$ 的个数 $i$，范围通常是从 $\frac{k + 1}{2}$ 到 $\min(k, c_1)$（$c_1$ 为数组中 $1$ 的个数），计算 $\binom{c_1}{i}\binom{c_0}{k - i}$ 并累加。

解决难点：
 - 组合数计算：涉及除法，在模运算下需用逆元处理，多数题解通过快速幂求逆元。
 - 枚举范围确定：要保证 $1$ 的个数足够使中位数为 $1$，同时不超过数组中 $1$ 的总数和子序列长度。

### 高评分题解
- **作者：aeiouaoeiu（5星）**
    - **关键亮点**：思路清晰，代码规范，详细注释了各部分功能，时间复杂度分析明确。
    - **核心代码**：
```cpp
ll qpow(ll a,ll b){ll E=1; for(;b;b>>=1,a=a*a%p)if(b&1) E=E*a%p; return E;}
ll C(ll a,ll b){return (a<b||b<0)?0:frac[a]*inv[b]%p*inv[a-b]%p;}
//...
for(int i=m;i<=k;i++) ans=(ans+C(cnt,i)*C(n-cnt,k-i)%p)%p;
```
核心思想：先预处理阶乘和逆元，然后枚举 $1$ 的个数 $i$，计算组合数乘积并累加。

- **作者：Pink_Cut_Tree（4星）**
    - **关键亮点**：思路解释详细，给出了题目链接和提交记录，方便参考。
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
核心思想：通过快速幂求逆元，预处理阶乘数组，枚举 $1$ 的个数计算答案。

- **作者：cjh20090318（4星）**
    - **关键亮点**：分析过程清晰，指出了若数组不是 $01$ 序列的思考方向。
    - **核心代码**：
```cpp
int C(const int n,const int m){return n<m?0:(LL)f[n]*v[m]%mod*v[n-m]%mod;}//组合数。
//...
for(int i=(k+1)>>1,mi=s<k?s:k;i<=mi;i++) ans=(ans+(LL)C(s,i)*C(n-s,k-i)%mod)%mod;
```
核心思想：预处理阶乘和逆元，枚举 $1$ 的个数，计算组合数并累加。

### 最优关键思路或技巧
 - **组合数学转化**：将求子序列中位数之和问题转化为计算满足条件的子序列组合数之和，利用组合数公式求解。
 - **预处理阶乘和逆元**：通过预处理阶乘和逆元，将组合数计算复杂度降为 $O(1)$，提高整体效率。

### 可拓展之处
同类型题或类似算法套路：
 - 其他涉及子序列计数的组合数学问题，如求满足特定条件（如元素和、元素乘积等）的子序列个数。
 - 多维数组或其他类型数组的子序列问题，可能需要更复杂的组合分析和状态表示。

### 洛谷推荐题目
 - [P1833 樱花](https://www.luogu.com.cn/problem/P1833)：涉及组合数计算和动态规划。
 - [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)：直接考察组合数的计算和应用。
 - [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)：需要运用组合数学和快速幂解决计数问题。

### 个人心得摘录与总结
部分题解提到了学习逆元的建议，如 “不会求逆元或者没看懂的，建议你[去学习一下](https://www.luogu.com.cn/article/y49px6kk)”，强调了逆元在组合数计算中的重要性。还有题解提到看数据范围找思路，如 “当你没有思路的时候就要去看数据范围”，这是解决算法问题的常用策略。 

---
处理用时：43.53秒