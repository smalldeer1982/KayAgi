# 题目信息

# Candles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/snuke21/tasks/snuke21_a

# AI分析结果

### 题目翻译
#### 题目描述
Snuke 想知道，他要摆几排蜡烛就可以摆出正好 $n$ 根蜡烛。蜡烛的排布方式是：第 $i$ 排摆 $i$ 根蜡烛。如果无解，输出 $-1$。

### 算法分类
数学

### 题解分析与结论
本题的核心是通过数学推导找到满足条件的 $k$，使得 $1 + 2 + \cdots + k = n$。大多数题解都基于等差数列求和公式，通过数学推导得出 $k$ 的表达式，并通过开方和乘法验证是否满足条件。

#### 最优思路总结
1. **数学推导**：利用等差数列求和公式 $n = \frac{k(k+1)}{2}$，推导出 $k^2 < 2n < (k+1)^2$，进而得到 $k = \lfloor \sqrt{2n} \rfloor$。
2. **验证条件**：通过判断 $k(k+1) == 2n$ 来验证 $k$ 是否满足条件。
3. **优化**：直接使用数学公式，避免了暴力枚举或二分查找，时间复杂度为 $O(1)$。

### 推荐题解
1. **作者：xiaoshumiao (5星)**
   - **关键亮点**：思路清晰，代码简洁，直接使用数学公式推导并验证，时间复杂度最优。
   - **代码片段**：
     ```cpp
     #include<cstdio>
     #include<cmath>
     using namespace std;
     int main() {
       long long n;
       scanf("%lld",&n);
       int k=sqrt(2*n);
       if(1LL*k*(k+1)==2*n)
         printf("%d",k);
       else
         printf("-1");
       return 0;
     }
     ```

2. **作者：xuchuhan (4星)**
   - **关键亮点**：代码简洁，使用 `long long` 避免溢出，思路清晰。
   - **代码片段**：
     ```cpp
     #include<bits/stdc++.h>
     #define int long long
     using namespace std;
     int k;
     signed main(){
       cin>>k;
       k*=2;
       int x=sqrt(k);
       if(x*(x+1)==k)
         cout<<x;
       else
         cout<<-1;
       return 0;
     }
     ```

3. **作者：Mason123456 (4星)**
   - **关键亮点**：提供了朴素做法和正解，对比明显，思路清晰。
   - **代码片段**：
     ```cpp
     #include <bits/stdc++.h>
     using namespace std;
     int main(){
       unsigned long long n;
       cin>>n;
       unsigned long long p = sqrt(2 * n);
       if(p * (p+1) == 2 * n){
         cout<<p<<"\n";
         return 0;
       }
       cout<<-1<<"\n";
     }
     ```

### 扩展思路
- **类似题目**：可以扩展到其他需要数学推导的题目，如求解平方数、立方数等。
- **优化技巧**：在涉及大数运算时，使用 `long long` 或 `__int128` 避免溢出。

### 推荐题目
1. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
2. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：21.56秒