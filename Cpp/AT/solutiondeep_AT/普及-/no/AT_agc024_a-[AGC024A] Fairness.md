# 题目信息

# [AGC024A] Fairness

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc024/tasks/agc024_a

高橋君、中橋君、低橋君は、それぞれ整数 $ A,B,C $ を持っています。 以下の操作を $ K $ 回行った後、高橋君の持っている整数から中橋君の持っている整数を引いた値を求めてください。

- $ 3 $ 人は同時に、他の $ 2 $ 人の持っている整数の和を求める。その後、自分の持っている整数を求めた整数で置き換える。

ただし、答えの絶対値が $ 10^{18} $ を超える場合は、代わりに `Unfair` と出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ A,B,C\ \leq\ 10^9 $
- $ 0\ \leq\ K\ \leq\ 10^{18} $
- 入力はすべて整数である

### Sample Explanation 1

$ 1 $ 回の操作後、高橋君、中橋君、低橋君の持っている整数はそれぞれ $ (5,4,3) $ となります。$ 5-4=1 $ を出力します。

## 样例 #1

### 输入

```
1 2 3 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2 3 2 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
1000000000 1000000000 1000000000 1000000000000000000```

### 输出

```
0```

# AI分析结果

### 题目内容重写
高橋君、中橋君、低橋君分别持有整数 $A, B, C$。进行 $K$ 次操作后，求高橋君的整数减去中橋君的整数的值。每次操作中，三人同时计算其他两人整数的和，并用该和替换自己的整数。如果结果的绝对值超过 $10^{18}$，则输出 `Unfair`。

### 算法分类
递推

### 题解分析与结论
各题解的核心思路都是通过递推公式推导出 $A_k - B_k$ 的表达式，发现其为一个公比为 $-1$ 的等比数列，最终结果取决于 $K$ 的奇偶性。所有题解都避免了直接模拟操作，而是通过数学推导得出简洁的公式，从而在 $O(1)$ 时间复杂度内解决问题。

### 精选题解
1. **作者：billzd (5星)**
   - **关键亮点**：简洁明了地推导出 $A_k - B_k = (-1)^k \times (A_0 - B_0)$，并直接根据 $K$ 的奇偶性输出结果。
   - **代码实现**：
     ```cpp
     #include<stdio.h>
     long long a,b,c,k;
     int main(){
         scanf("%lld%lld%lld%lld",&a,&b,&c,&k);
         printf("%lld\n",(a-b)*((k&1)?-1:1));
         return 0;
     }
     ```

2. **作者：Otue (5星)**
   - **关键亮点**：清晰地展示了递推过程，并指出 $C_i$ 对结果无影响，进一步简化了问题。
   - **代码实现**：
     ```cpp
     #include<bits/stdc++.h>
     using namespace std;
     long long a,b,c,k;
     int check(int i){
         if(i%2==0) return 1;
         return -1;
     }
     int main(){
         cin>>a>>b>>c>>k;
         cout<<(a-b)*check(k)<<endl;
     }
     ```

3. **作者：MattL (4星)**
   - **关键亮点**：详细推导了递推公式，并解释了为什么不需要考虑 `Unfair` 的情况。
   - **代码实现**：
     ```cpp
     #include <bits/stdc++.h>
     using namespace std;
     typedef long long ll;
     inline ll read(){
        ll s=0,w=1;
        char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
        while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
        return s*w;
     }
     void write(long long out){
         if(out<0){putchar('-');out=abs(out);}
         if(out>9)write(out/10);
         printf("%d",out%10);
     }
     int A0,B0,C0,k;
     int main(){
         A0=read();
         B0=read();
         C0=read();
         k=read();
         write(((k&1)?(-1):(1))*(A0-B0));
         puts("");
         return 0;
     }
     ```

### 最优关键思路
通过递推公式 $A_k - B_k = (-1)^k \times (A_0 - B_0)$，直接根据 $K$ 的奇偶性输出结果，避免了复杂的模拟操作，极大地简化了问题。

### 可拓展之处
类似的问题可以通过寻找递推关系或数学规律来简化计算，避免直接模拟。例如，某些数列问题或状态转移问题也可以通过类似的思路进行优化。

### 推荐题目
1. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：24.17秒