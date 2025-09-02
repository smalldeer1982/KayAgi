# 题目信息

# 378QAQ and Mocha's Array

## 题目描述

Mocha likes arrays, so before her departure, 378QAQ gave her an array $ a $ consisting of $ n $ positive integers as a gift.

Mocha thinks that $ a $ is beautiful if there exist two numbers $ i $ and $ j $ ( $ 1\leq i,j\leq n $ , $ i\neq j $ ) such that for all $ k $ ( $ 1 \leq k \leq n $ ), $ a_k $ is divisible $ ^\dagger $ by either $ a_i $ or $ a_j $ .

Determine whether $ a $ is beautiful.

 $ ^\dagger $ $ x $ is divisible by $ y $ if there exists an integer $ z $ such that $ x = y \cdot z $ .

## 说明/提示

In the first test case, any two numbers in the array are coprime, so the answer is "No".

In the second test case, we can pick $ i=2 $ and $ j=1 $ . Since every number in the array is divisible by $ a_i = 1 $ , the answer is "Yes".

In the third test case, we can pick $ i=3 $ and $ j=5 $ . $ 2 $ and $ 4 $ is divisible by $ a_i = 2 $ while $ 3 $ , $ 6 $ and $ 12 $ is divisible by $ a_j = 3 $ , so the answer is "Yes".

## 样例 #1

### 输入

```
4
3
7 3 8
5
7 1 9 3 5
5
4 12 2 6 3
5
7 49 9 3 1000000000```

### 输出

```
No
Yes
Yes
No```

# AI分析结果

### 题目内容重写

#### 题目描述

Mocha 喜欢数组，因此在离开前，378QAQ 给了她一个由 $n$ 个正整数组成的数组 $a$ 作为礼物。

Mocha 认为 $a$ 是美丽的，如果存在两个数 $i$ 和 $j$（$1 \leq i, j \leq n$，$i \neq j$），使得对于所有 $k$（$1 \leq k \leq n$），$a_k$ 能被 $a_i$ 或 $a_j$ 整除。

判断 $a$ 是否是美丽的。

#### 说明/提示

- 在第一个测试用例中，数组中的任何两个数都是互质的，因此答案是 "No"。
- 在第二个测试用例中，可以选择 $i=2$ 和 $j=1$。由于数组中的每个数都能被 $a_i = 1$ 整除，因此答案是 "Yes"。
- 在第三个测试用例中，可以选择 $i=3$ 和 $j=5$。$2$ 和 $4$ 能被 $a_i = 2$ 整除，而 $3$、$6$ 和 $12$ 能被 $a_j = 3$ 整除，因此答案是 "Yes"。

#### 样例 #1

##### 输入

```
4
3
7 3 8
5
7 1 9 3 5
5
4 12 2 6 3
5
7 49 9 3 1000000000
```

##### 输出

```
No
Yes
Yes
No
```

### 题解综合分析与结论

#### 思路总结

1. **最小数必选**：由于最小的数无法被其他数整除，因此必须选择最小的数作为其中一个数。
2. **第二个数的选择**：在排除能被最小数整除的数后，选择剩余数中的最小数作为第二个数。
3. **验证条件**：检查数组中的所有数是否都能被这两个数中的至少一个整除。

#### 最优关键思路

- **排序与最小数选择**：通过排序快速找到最小数，并利用最小数的特性简化问题。
- **最大公约数（GCD）**：在处理剩余数时，使用GCD来找到这些数的公约数，进一步简化判断过程。

#### 推荐题解

1. **作者：hcy1117**（评分：4星）
   - **关键亮点**：通过排序和GCD的结合，高效地解决了问题，代码清晰且逻辑严谨。
   - **核心代码**：
     ```cpp
     sort(a+1,a+n+1);
     int num,cnt=0;
     bool flag=0;
     for(int i=1;i<=n;i++) {
         if(a[i]%a[1]!=0) {
             if(!flag)num=a[i],flag=1;
             else num=gcd(num,a[i]);
         } else ++cnt;
     }
     flag=0;
     for(int i=1;i<=n;i++) {
         if(a[i]%a[1]!=0) {
             if(num%a[i]==0)flag=1;
         }
     }
     if(flag||cnt==n)cout<<"Yes"<<endl;
     else cout<<"No"<<endl;
     ```

2. **作者：FXLIR**（评分：4星）
   - **关键亮点**：简洁明了地实现了最小数和第二个数的选择，并通过遍历验证条件，代码可读性强。
   - **核心代码**：
     ```cpp
     sort(a+1,a+n+1);
     for(int i=1;i<=n;i++) {
         if(a[i]%a[1]){
             k=a[i];
             break;
         }
     }
     for(int i=1;i<=n;i++) {
         if(a[i]%a[1]!=0&&a[i]%k!=0){
             f=1;
             break;
         }
     }
     cout<<(f?"No\n":"Yes\n");
     ```

3. **作者：lyhqwq**（评分：4星）
   - **关键亮点**：通过排序和简单的遍历，快速找到并验证两个数，代码简洁且高效。
   - **核心代码**：
     ```cpp
     sort(a+1,a+1+n);
     int x=1,y=2;
     for(int i=1;i<=n;i++){
         if(a[i]%a[x]!=0){
             y=i;
             break;
         }
     }
     int ok=1;
     for(int i=1;i<=n;i++) if(a[i]%a[x]!=0&&a[i]%a[y]!=0) ok=0;
     puts(ok?"Yes":"No");
     ```

#### 拓展思路

- **类似题目**：可以扩展到多组数的选择，或者扩展到更复杂的整除条件。
- **优化技巧**：在处理大规模数据时，可以考虑使用更高效的排序算法或并行计算来加速处理。

#### 推荐题目

1. [P10443 消消乐](https://www.luogu.com.cn/problem/P10443)
2. [P1975 最大公约数](https://www.luogu.com.cn/problem/P1975)
3. [P10444 最小公倍数](https://www.luogu.com.cn/problem/P10444)

---
处理用时：39.37秒