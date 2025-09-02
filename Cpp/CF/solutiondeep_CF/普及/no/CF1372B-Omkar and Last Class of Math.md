# 题目信息

# Omkar and Last Class of Math

## 题目描述

In Omkar's last class of math, he learned about the least common multiple, or $ LCM $ . $ LCM(a, b) $ is the smallest positive integer $ x $ which is divisible by both $ a $ and $ b $ .

Omkar, having a laudably curious mind, immediately thought of a problem involving the $ LCM $ operation: given an integer $ n $ , find positive integers $ a $ and $ b $ such that $ a       + b = n $ and $ LCM(a, b) $ is the minimum value possible.

Can you help Omkar solve his ludicrously challenging math problem?

## 说明/提示

For the first test case, the numbers we can choose are $ 1, 3 $ or $ 2, 2 $ . $ LCM(1, 3) = 3 $ and $ LCM(2, 2) = 2 $ , so we output $ 2 \ 2 $ .

For the second test case, the numbers we can choose are $ 1,       5 $ , $ 2, 4 $ , or $ 3, 3 $ . $ LCM(1, 5) = 5 $ , $ LCM(2, 4)       = 4 $ , and $ LCM(3, 3) = 3 $ , so we output $ 3 \ 3 $ .

For the third test case, $ LCM(3, 6) = 6 $ . It can be shown that there are no other pairs of numbers which sum to $ 9 $ that have a lower $ LCM $ .

## 样例 #1

### 输入

```
3
4
6
9```

### 输出

```
2 2
3 3
3 6```

# AI分析结果

### 题目内容重写
# Omkar 和最后一节数学课

## 题目描述

在 Omkar 的最后一节数学课上，他学习了最小公倍数，即 $LCM$。$LCM(a, b)$ 是能被 $a$ 和 $b$ 整除的最小正整数 $x$。

Omkar 有着强烈的好奇心，立刻想到了一个关于 $LCM$ 操作的问题：给定一个整数 $n$，找到正整数 $a$ 和 $b$，使得 $a + b = n$，并且 $LCM(a, b)$ 的值尽可能小。

你能帮助 Omkar 解决这个极具挑战性的数学问题吗？

## 说明/提示

对于第一个测试用例，我们可以选择的数字是 $1, 3$ 或 $2, 2$。$LCM(1, 3) = 3$，$LCM(2, 2) = 2$，所以我们输出 $2 \ 2$。

对于第二个测试用例，我们可以选择的数字是 $1, 5$，$2, 4$，或 $3, 3$。$LCM(1, 5) = 5$，$LCM(2, 4) = 4$，$LCM(3, 3) = 3$，所以我们输出 $3 \ 3$。

对于第三个测试用例，$LCM(3, 6) = 6$。可以证明，没有其他数字对的和为 $9$ 且 $LCM$ 更小。

## 样例 #1

### 输入

```
3
4
6
9
```

### 输出

```
2 2
3 3
3 6
```

### 算法分类
数学

### 题解分析与结论
本题的核心是通过数学分析找到使得 $LCM(a, b)$ 最小的 $a$ 和 $b$，且 $a + b = n$。大多数题解都基于以下思路：
1. **质因数分解**：通过找到 $n$ 的最小质因数，将 $n$ 分解为 $a$ 和 $b$，使得 $LCM(a, b)$ 最小。
2. **倍数关系**：通过分析 $a$ 和 $b$ 的倍数关系，推导出 $a$ 和 $b$ 的表达式，从而找到最小的 $LCM$。

### 高星题解推荐
1. **作者：lingfunny (4星)**
   - **关键亮点**：通过质因数分解找到 $n$ 的最小质因数，直接输出 $a$ 和 $b$，思路清晰，代码简洁。
   - **代码实现**：
     ```cpp
     #include <cstdio>
     int T;
     int main(){
         scanf("%d", &T);
         while(T--){
             int n; scanf("%d", &n);
             int key = n;
             for(int i=2;i*i<=n;++i)
             if(n%i == 0){
                 key = i;
                 break;
             }
             printf("%d %d\n", n/key, n-n/key);
         }
         return 0;
     }
     ```

2. **作者：Allen_lml (4星)**
   - **关键亮点**：通过枚举 $n$ 的因数，找到最小的 $LCM$，代码简洁，思路清晰。
   - **代码实现**：
     ```cpp
     #include<iostream>
     #include<cstdio>
     using namespace std;
     int t,n;
     int a,b;
     void LCM(int k){
         a=0,b=0;
         for(int i=2;i*i<=k;i++)
             if(!(k%i)){
                 a=k/i;
                 b=k-a;
                 return ;
             }    
         a=1,b=k-a;
         return ;
     }
     int main(){
         scanf("%d",&t);
         while(t--){
             scanf("%d",&n);
             LCM(n);
             printf("%d %d\n",a,b);
         }
         return 0;
     }
     ```

3. **作者：Werner_Yin (4星)**
   - **关键亮点**：通过线性筛法预处理质数，找到 $n$ 的最小质因数，输出 $a$ 和 $b$，代码实现较为复杂但思路清晰。
   - **代码实现**：
     ```cpp
     #include <bits/stdc++.h>
     #define lol long long
     #define GDB(x) cout<<"DATA "<<#x<<" :"<<x<<endl; 
     #define mes(x) memset(x,0,sizeof(x))
     using namespace std;
     template <typename T>
     void re(T &x){
         #define ge getchar() 
         x = 0;int sgn = 1;char ch = ge;
         for(;!isdigit(ch);ch = ge) if(ch == '-') sgn = -1;
         for(;isdigit(ch);ch = ge) x = (x<<1)+(x<<3)+(ch^48);
         x *= sgn;
     }
     template <typename T>
     void write(T x){
         if(x == 0) putchar(48);
         else if(x < 0) putchar('-');
         int k = 0,que[20];
         while(x > 0){
             que[++k]=x % 10;
             x /= 10;
         }
         for(int i = k;i > 0;i--) putchar(que[i] + 48);
         return;
     }
     const int MAXN = 1e5 + 10;
     int PrimeNum = 0,Prime[MAXN];
     bool IsNotPrime[MAXN];
     void shai (){
         for(int i = 2;i < MAXN;i++){
             if(!IsNotPrime[i]){
                 Prime[PrimeNum++] = i;
             }
             for(int j = 0;j < PrimeNum && Prime[j] * i < MAXN;j++){
                 IsNotPrime[Prime[j] * i] = 1;
                 if(i % Prime[j])break;
             }
         }
     }
     int main (){
         shai();
         int T;
         re(T);
         while(T--){
             int n;
             re(n);
             int minn = -1;
             for(int i = 0;i < PrimeNum ;i++){
                 if(n % Prime[i] == 0){
                     minn = Prime[i];
                     break;
                 }
             }
             int mul = n / minn;
             if(minn == -1||mul == 1) {write(1);write(n-1);}
             else{write ( 1 * mul);write( (minn-1)*mul);}
             putchar('\n');
         }
         return 0;
     }
     ```

### 最优关键思路
通过找到 $n$ 的最小质因数，将 $n$ 分解为 $a$ 和 $b$，使得 $LCM(a, b)$ 最小。这一思路的核心在于利用质因数分解和倍数关系，确保 $a$ 和 $b$ 的 $LCM$ 最小。

### 可拓展之处
类似的问题可以通过质因数分解和倍数关系来解决，例如在分解数对时，寻找最大公约数或最小公倍数的问题。

### 推荐题目
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P1069 最小公倍数](https://www.luogu.com.cn/problem/P1069)
3. [P1072 最大公约数](https://www.luogu.com.cn/problem/P1072)

---
处理用时：46.77秒