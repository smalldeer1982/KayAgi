# 题目信息

# Qpwoeirut And The City

## 题目描述

Qpwoeirut has taken up architecture and ambitiously decided to remodel his city.

Qpwoeirut's city can be described as a row of $ n $ buildings, the $ i $ -th ( $ 1 \le i \le n $ ) of which is $ h_i $ floors high. You can assume that the height of every floor in this problem is equal. Therefore, building $ i $ is taller than the building $ j $ if and only if the number of floors $ h_i $ in building $ i $ is larger than the number of floors $ h_j $ in building $ j $ .

Building $ i $ is cool if it is taller than both building $ i-1 $ and building $ i+1 $ (and both of them exist). Note that neither the $ 1 $ -st nor the $ n $ -th building can be cool.

To remodel the city, Qpwoeirut needs to maximize the number of cool buildings. To do this, Qpwoeirut can build additional floors on top of any of the buildings to make them taller. Note that he cannot remove already existing floors.

Since building new floors is expensive, Qpwoeirut wants to minimize the number of floors he builds. Find the minimum number of floors Qpwoeirut needs to build in order to maximize the number of cool buildings.

## 说明/提示

In the first test case, it is optimal for Qpwoeirut to make the second building cool by building $ 2 $ additional floors on top of it, making it taller than both of its adjacent buildings. The final heights of buildings will be $ [2, \underline{3}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/5b747d1e682e5f282bdd90fc1247bc9f2859b4d3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/c25e1e8b92772ee4d6c001b5263ad32fc0bed1d3.png)In the second test case, the number of cool buildings is already maximized, so Qpwoeirut does not need to do anything.

In the third test case, it is optimal for Qpwoeirut to make the third and fifth buildings cool by building $ 2 $ additional floors onto the third building and $ 1 $ additional floor onto the fifth building. The final heights of buildings will be $ [3, 1, \underline{6}, 5, \underline{6}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/d8dd96553e5aa6fe2bbad7a9bf1dc528da32254c.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/6d7185baf1e5e2a187bb01c943d100104f7de6bc.png)It can be shown that it is impossible to make more than $ 2 $ of the buildings cool, or to make $ 2 $ buildings cool using fewer than $ 3 $ additional floors.

In the fourth test case, Qpwoeirut can either make the second building cool, or he can make the third building cool. Either way, he will be building $ 3 $ additional floors and maximizing the number of cool buildings. The final heights of buildings will be $ [4, 2, \underline{4}, 3, 5, 3, 6, 1] $ or $ [4, \underline{5}, 1, 3, 5, 3, 6, 1] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/27f107a434b26468932a928c7c16fd0abda918f0.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/4e2e7951e438027228057e8a21e8bea81f160a32.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/8e41aee337358c3f261ed9626c0e19808d3f7d2c.png)

## 样例 #1

### 输入

```
6
3
2 1 2
5
1 2 1 4 3
6
3 1 4 5 5 2
8
4 2 1 3 5 3 6 1
6
1 10 1 1 10 1
8
1 10 11 1 10 11 10 1```

### 输出

```
2
0
3
3
0
4```

# AI分析结果

### 题目内容重写

Qpwoeirut 决定改造他的城市。城市可以描述为一排 $n$ 座建筑，第 $i$ 座建筑有 $h_i$ 层。假设每层的高度相同，因此建筑 $i$ 比建筑 $j$ 高当且仅当 $h_i > h_j$。

建筑 $i$ 是“凉爽的”当且仅当它比相邻的两座建筑都高（且这两座建筑都存在）。注意第 $1$ 座和第 $n$ 座建筑不可能是“凉爽的”。

Qpwoeirut 希望通过增加建筑的层数来最大化“凉爽的”建筑数量。由于增加层数成本高昂，他希望找到在最大化“凉爽的”建筑数量的前提下，最小化需要增加的层数。

### 样例输入输出

**输入：**
```
6
3
2 1 2
5
1 2 1 4 3
6
3 1 4 5 5 2
8
4 2 1 3 5 3 6 1
6
1 10 1 1 10 1
8
1 10 11 1 10 11 10 1
```

**输出：**
```
2
0
3
3
0
4
```

### 题解分析与结论

#### 综合分析与结论

1. **问题核心**：最大化“凉爽的”建筑数量，同时最小化增加的层数。关键在于如何选择哪些建筑需要增加层数，以达到最优解。
2. **奇偶性分析**：
   - **奇数情况**：直接选择所有偶数位置的建筑，计算需要增加的层数。
   - **偶数情况**：需要枚举所有可能的“凉爽的”建筑组合，找到最小增加层数的方案。
3. **优化技巧**：使用前缀和和后缀和来快速计算不同组合的层数增加量，避免重复计算。
4. **时间复杂度**：对于每个测试用例，时间复杂度为 $O(n)$，适用于 $n \leq 10^5$ 的规模。

#### 精选题解

1. **作者：Burnling (5星)**
   - **关键亮点**：详细分析了奇偶情况的不同处理方式，使用前缀和和后缀和优化了偶数情况的计算，代码清晰且高效。
   - **代码核心**：
     ```cpp
     if(N & 1){ // N为奇数
         for(int i = 2;i<N;i+=2){
             int M = max(B[i-1],B[i+1]);
             if(B[i] <= M){
                 ans += (M+1-B[i]);
             }
         }
     }else{
         memset(A1,0ll,sizeof(A1));
         memset(A2,0ll,sizeof(A2));
         int cnt = 1;
         for(int i = 2;i<N-1;i+=2){
             int M = max(B[i-1],B[i+1]);
             if(B[i] <= M){
                 A1[cnt] = A1[cnt-1] + (M+1-B[i]);
             }else{
                 A1[cnt] = A1[cnt-1];
             }
             cnt++;
         }
         cnt = (N>>1)-1;
         for(int i = N-1;i>2;i-=2){
             int M = max(B[i-1],B[i+1]);
             if(B[i] <= M){
                 A2[cnt] = A2[cnt+1] + (M+1-B[i]);
             }else{
                 A2[cnt] = A2[cnt+1];
             }
             cnt--;
         }
         int r = (N >> 1);
         ans = 1e17;
         for(int i = 1;i<=r;i++){
             ans = min(ans,A1[i-1]+A2[i]);
         }
     }
     ```

2. **作者：wsx248 (4星)**
   - **关键亮点**：使用动态规划处理偶数情况，思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     if(n&1){
         long long ans = 0;
         for(int i=2;i<n;i+=2) ans += add[i];
         cout<<ans<<endl;
     }else{
         memset(dp, 0x3f, sizeof dp);
         dp[1] = 0;
         dp[2] = add[2];
         dp[3] = add[3];
         for(int i=4;i<n;i++){
             if(i&1) dp[i] = min(dp[i-2], dp[i-3]) + add[i];
             else dp[i] = dp[i-2] + add[i];
         }
         cout<<min(dp[n-1], dp[n-2])<<endl;
     }
     ```

3. **作者：happy_dengziyue (4星)**
   - **关键亮点**：通过枚举间断点来优化偶数情况的计算，代码实现简洁。
   - **代码核心**：
     ```cpp
     if(n&1){
         for(int i=2;i<n;i+=2)ans+=max(0ll,max(a[i-1],a[i+1])-a[i]+1);
         printf("%lld\n",ans);
     }else{
         s1[0]=s2[n+1]=0;
         for(int i=2;i<n;i+=2)s1[i]=s1[i-2]+max(0ll,max(a[i-1],a[i+1])-a[i]+1);
         for(int i=n-1;i>1;i-=2)s2[i]=s2[i+2]+max(0ll,max(a[i-1],a[i+1])-a[i]+1);
         ans=inf;
         for(int i=0;i<n;i+=2){
             if(i>=n-2)ans=min(ans,s1[i]);
             else ans=min(ans,s1[i]+s2[i+3]);
         }
         printf("%lld\n",ans);
     }
     ```

### 最优关键思路与技巧

1. **奇偶性分析**：根据 $n$ 的奇偶性分别处理，奇数情况直接计算，偶数情况需要枚举所有可能的组合。
2. **前缀和与后缀和**：在偶数情况下，使用前缀和和后缀和来快速计算不同组合的层数增加量，避免重复计算。
3. **动态规划**：在偶数情况下，使用动态规划来优化计算过程，减少时间复杂度。

### 拓展与举一反三

1. **类似题目**：
   - [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
   - [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)
   - [P1060 [NOIP2006 提高组] 开心的金明](https://www.luogu.com.cn/problem/P1060)

2. **个人心得**：
   - **调试经历**：在处理偶数情况时，枚举所有可能的组合容易出错，需要仔细验证每个组合的计算结果。
   - **踩坑教训**：在计算前缀和和后缀和时，注意边界条件的处理，避免数组越界或计算错误。
   - **顿悟感想**：通过奇偶性分析，可以将复杂问题简化，提高解题效率。

---
处理用时：55.70秒