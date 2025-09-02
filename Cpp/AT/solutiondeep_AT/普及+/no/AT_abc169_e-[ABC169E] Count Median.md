# 题目信息

# [ABC169E] Count Median

## 题目描述

有 $N$ 个整数 $X_1, X_2, X_3,\cdots,X_N $，满足 $A_i \le X_i \le B_i$。

求 $X_1，X_2,\cdots,X_N$ 的中位数可能的不同值的数量。

## 样例 #1

### 输入

```
2

1 2

2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3

100 100

10 10000

1 1000000000```

### 输出

```
9991```

# AI分析结果

【题目内容】
# [ABC169E] Count Median

## 题目描述

有 $N$ 个整数 $X_1, X_2, X_3,\cdots,X_N $，满足 $A_i \le X_i \le B_i$。

求 $X_1，X_2,\cdots,X_N$ 的中位数可能的不同值的数量。

## 样例 #1

### 输入

```
2

1 2

2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3

100 100

10 10000

1 1000000000```

### 输出

```
9991```

【算法分类】
数学

【题解分析与结论】
本题的核心在于通过排序后确定中位数的取值范围，并根据 $N$ 的奇偶性分类讨论。所有题解都采用了类似的思路：首先对 $A$ 和 $B$ 进行排序，然后根据 $N$ 的奇偶性计算中位数的可能取值范围。对于奇数 $N$，中位数的取值范围是 $[A_{(n+1)/2}, B_{(n+1)/2}]$；对于偶数 $N$，中位数的取值范围是 $[\frac{A_{n/2} + A_{n/2+1}}{2}, \frac{B_{n/2} + B_{n/2+1}}{2}]$，且中位数可以是整数或半整数。

【评分较高的题解】

1. **作者：FL_sleake (5星)**
   - **关键亮点**：详细推导了中位数的取值范围，特别是对偶数情况的处理进行了清晰的数学推导，代码简洁明了。
   - **代码示例**：
     ```cpp
     #include<bits/stdc++.h>
     using namespace std; 
     #define int long long
     int n,a[200010],b[200010]; 
     signed main() {
         cin>>n;
         for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
         sort(a+1,a+n+1);
         sort(b+1,b+n+1);
         if(n%2==1) cout<<b[n/2+1]-a[n/2+1]+1<<endl;
         else cout<<(b[n/2+1]+b[n/2])-(a[n/2+1]+a[n/2])+1<<endl;
         return 0;
     }
     ```

2. **作者：lym12 (4星)**
   - **关键亮点**：对奇偶情况进行了分类讨论，代码简洁，逻辑清晰。
   - **代码示例**：
     ```cpp
     #include <bits/stdc++.h>
     #define int long long
     using namespace std;

     const int N = 2e5 + 5;
     int a[N], b[N];

     signed main(){
         int n;
         cin >> n;
         for (int i = 1; i <= n; i ++) cin >> a[i] >> b[i];
         sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
         cout << (
                 n % 2 == 1
             ?  (b[n / 2 + 1] - a[n / 2 + 1] + 1) 
             :  ((b[n / 2 + 1] + b[n / 2]) 
             -  (a[n / 2 + 1] + a[n / 2]) + 1)
         );
     }
     ```

3. **作者：Symbolize (4星)**
   - **关键亮点**：通过数学推导得出中位数的取值范围，代码简洁，逻辑清晰。
   - **代码示例**：
     ```cpp
     #include<bits/stdc++.h>
     #define int long long
     using namespace std;
     int n,a[N],b[N];
     signed main() {
         n=read();
         rep1(i,1,n) a[i]=read(),b[i]=read();
         sort(a+1,a+n+1);
         sort(b+1,b+n+1);
         int ans;
         if(n&1) ans=b[n/2+1]-a[n/2+1]+1;
         else ans=b[n/2+1]+b[n/2]-a[n/2+1]-a[n/2]+1;
         cout<<ans<<endl;
         return 0;
     }
     ```

【最优关键思路或技巧】
- **排序**：首先对 $A$ 和 $B$ 进行排序，以便快速找到中位数的取值范围。
- **分类讨论**：根据 $N$ 的奇偶性分别计算中位数的取值范围，特别注意偶数情况下中位数可以是整数或半整数。
- **数学推导**：通过数学公式推导出中位数的取值范围，确保计算的准确性。

【可拓展之处】
- 类似的问题可以扩展到其他统计量的计算，如众数、平均数等。
- 可以进一步探讨在多个约束条件下如何计算中位数的取值范围。

【推荐题目】
1. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
2. [P3871 [TJOI2010]中位数](https://www.luogu.com.cn/problem/P3871)
3. [P1137 旅行计划](https://www.luogu.com.cn/problem/P1137)

---
处理用时：33.32秒