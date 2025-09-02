# 题目信息

# Doremy's Pegging Game

## 题目描述

Doremy has $ n+1 $ pegs. There are $ n $ red pegs arranged as vertices of a regular $ n $ -sided polygon, numbered from $ 1 $ to $ n $ in anti-clockwise order. There is also a blue peg of slightly smaller diameter in the middle of the polygon. A rubber band is stretched around the red pegs.

Doremy is very bored today and has decided to play a game. Initially, she has an empty array $ a $ . While the rubber band does not touch the blue peg, she will:

1. choose $ i $ ( $ 1 \leq i \leq n $ ) such that the red peg $ i $ has not been removed;
2. remove the red peg $ i $ ;
3. append $ i $ to the back of $ a $ .

Doremy wonders how many possible different arrays $ a $ can be produced by the following process. Since the answer can be big, you are only required to output it modulo $ p $ . $ p $ is guaranteed to be a prime number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png) game with $ n=9 $ and $ a=[7,5,2,8,3,9,4] $ and another game with $ n=8 $ and $ a=[3,4,7,1,8,5,2] $

## 说明/提示

In the first test case, $ n=4 $ , some possible arrays $ a $ that can be produced are $ [4,2,3] $ and $ [1,4] $ . However, it is not possible for $ a $ to be $ [1] $ or $ [1,4,3] $ .

## 样例 #1

### 输入

```
4 100000007```

### 输出

```
16```

## 样例 #2

### 输入

```
1145 141919831```

### 输出

```
105242108```

# AI分析结果

### 题目翻译
# 多雷米的钉桩游戏

## 题目描述
多雷米有 $n + 1$ 个桩子。有 $n$ 个红色桩子排列成一个正 $n$ 边形的顶点，按逆时针顺序从 $1$ 到 $n$ 编号。在多边形的中心还有一个直径稍小的蓝色桩子。一根橡皮筋绕在红色桩子上。

多雷米今天非常无聊，决定玩一个游戏。最初，她有一个空数组 $a$。当橡皮筋没有碰到蓝色桩子时，她将进行以下操作：
1. 选择 $i$（$1 \leq i \leq n$），使得红色桩子 $i$ 尚未被移除；
2. 移除红色桩子 $i$；
3. 将 $i$ 追加到数组 $a$ 的末尾。

多雷米想知道通过上述过程可以产生多少种不同的数组 $a$。由于答案可能很大，你只需要输出答案对 $p$ 取模的结果。$p$ 保证是一个质数。

![$n = 9$ 且 $a = [7, 5, 2, 8, 3, 9, 4]$ 的游戏以及 $n = 8$ 且 $a = [3, 4, 7, 1, 8, 5, 2]$ 的另一个游戏](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764D/39b25225514736b577fbcbcd5d0b5bf29ecc4db4.png)

## 说明/提示
在第一个测试用例中，$n = 4$，一些可能产生的数组 $a$ 是 $[4, 2, 3]$ 和 $[1, 4]$。然而，$a$ 不可能是 $[1]$ 或 $[1, 4, 3]$。

## 样例 #1
### 输入
```
4 100000007
```
### 输出
```
16
```

## 样例 #2
### 输入
```
1145 141919831
```
### 输出
```
105242108
```

### 综合分析与结论
- **思路对比**：
    - VinstaG173：利用钉子位置对称，先求 $a_k = n$ 的情况，再乘 $n$。通过枚举 $s + t$，结合组合数计算方案数。
    - honglan0301：假设最终状态是 $1$ 与 $1 + i$ 之间的数被删完，定义 $f(i, j)$ 表示情况数，计算求和后乘 $n$，同时对 $n$ 为偶数的特殊情况特判。
    - Alex_Wei：枚举最终绑在两侧的点的距离 $i$ 和绑在两侧的点之间保留的数的个数 $j$，根据 $n$ 的奇偶性确定 $r$ 的值，计算答案。
    - MortisM：枚举连续被删段的长度 $l$ 和其他位置选的个数 $x$，根据组合数和排列数计算方案数。
    - james1BadCreeper：同样利用对称性，枚举实际被删掉的 $l$ 和其他位置选择的个数 $x$，结合组合数和全排列计算方案数。
- **算法要点**：各题解均使用了组合数学的知识，如组合数的计算，部分题解还涉及阶乘和阶乘逆元的预处理。
- **解决难点**：主要难点在于对操作停止条件的转化，以及如何避免重复计算。各题解通过不同的枚举方式和状态定义来解决这些问题。

### 所选题解
- **VinstaG173（5星）**
    - **关键亮点**：思路清晰，对问题进行了巧妙的转化，通过枚举 $s + t$ 简化了计算过程。代码中对阶乘和阶乘逆元的预处理提高了计算效率。
    - **核心代码**：
```cpp
int n,ntf;ll res,tmp;
ll fac[5003];
ll fic[5003];
inline ll C(int m,int b){
    return fac[m]*fic[b]%ntf*fic[m-b]%ntf;
}
void solve(){
    rd(n);rd(ntf);res=0;
    fac[0]=1;for(rg int i=1;i<=n;++i)fac[i]=fac[i-1]*i%ntf;
    fic[n]=qpw(fac[n]);for(rg int i=n;i;--i)fic[i-1]=fic[i]*i%ntf;
    for(rg int m=n/2-1;m<n-2;++m){
        tmp=0;for(rg int i=0;i<=n-m-3;++i){
            tmp=(tmp+fac[m+i]*C(n-m-3,i))%ntf;
        }
        res=(res+(n-(n&1)-1-m)*tmp)%ntf;
    }
    res=(res+(1-(n&1))*fac[n-2]%ntf)%ntf;
    printf("%lld\n",res*n%ntf);
}
```
核心实现思想：先预处理阶乘和阶乘逆元，然后枚举 $m$ 和 $i$，计算组合数和排列数，最后累加结果并乘 $n$ 得到最终答案。

- **honglan0301（4星）**
    - **关键亮点**：通过定义状态 $f(i, j)$ 来解决问题，思路较为直观。对 $n$ 为偶数的特殊情况进行了特判，考虑全面。
    - **核心代码**：
```cpp
for(int i=n/2+1;i<=n-1;i++)
{
    for(int j=i-1;j<=n-2;j++)
    {
        dp[i][j]=n/2+n/2-i+1;
        dp[i][j]*=c[n-i-1][j-i+1];
        dp[i][j]%=mod;
        dp[i][j]*=jc[j-1];
        ans+=dp[i][j];
        ans%=mod;
    }
}
if(n%2==0)
{
    dp[n][n-1]=1;
    dp[n][n-1]*=jc[n-2];
    ans+=dp[n][n-1];
    ans%=mod;
}
ans*=n;
ans%=mod;
```
核心实现思想：通过两层循环枚举 $i$ 和 $j$，计算 $dp[i][j]$ 的值并累加，对 $n$ 为偶数的情况进行特判，最后结果乘 $n$ 取模。

### 最优关键思路或技巧
- **利用对称性**：多数题解都利用了钉子位置的对称性，先计算一种情况的方案数，再乘 $n$ 得到最终答案，简化了计算。
- **枚举与状态定义**：通过合理的枚举方式（如枚举连续段长度、两侧点距离等）和状态定义（如 $f(i, j)$），将复杂问题转化为可计算的子问题。
- **预处理**：预处理阶乘和阶乘逆元，提高组合数计算的效率。

### 可拓展之处
同类型题可能会改变操作停止条件或增加其他限制，类似算法套路包括利用对称性简化问题、枚举关键变量、定义合适的状态以及预处理常用数据等。

### 洛谷题目推荐
1. [P1865 A % B Problem](https://www.luogu.com.cn/problem/P1865)：涉及组合数学和取模运算。
2. [P2822 组合数问题](https://www.luogu.com.cn/problem/P2822)：主要考察组合数的计算和递推。
3. [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)：需要运用组合数学和快速幂等知识。

### 个人心得摘录与总结
- MortisM：提到这是一道简单题，但赛时没调出来，说明在比赛中即使题目本身难度不大，也可能因为紧张等原因出现问题，提醒我们要注重平时的调试训练。

---
处理用时：42.36秒