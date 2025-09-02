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

**Qpwoeirut 与城市**

**题目描述**

Qpwoeirut 决定投身建筑行业，并雄心勃勃地决定改造他的城市。

Qpwoeirut 的城市可以描述为一排 $n$ 座建筑，第 $i$ 座（$1 \le i \le n$）建筑有 $h_i$ 层高。假设每层楼的高度相同，因此建筑 $i$ 比建筑 $j$ 高当且仅当建筑 $i$ 的层数 $h_i$ 大于建筑 $j$ 的层数 $h_j$。

如果建筑 $i$ 比其相邻的建筑 $i-1$ 和建筑 $i+1$ 都高（且这两个建筑都存在），则称建筑 $i$ 是“酷的”。注意，第 $1$ 座和第 $n$ 座建筑不可能是“酷的”。

为了改造城市，Qpwoeirut 需要最大化“酷的”建筑的数量。为此，他可以在任何建筑的顶部建造额外的楼层以增加其高度。注意，他不能移除已经存在的楼层。

由于建造新楼层非常昂贵，Qpwoeirut 希望最小化他需要建造的楼层数。请找出 Qpwoeirut 需要建造的最小楼层数，以最大化“酷的”建筑的数量。

**说明/提示**

在第一个测试用例中，Qpwoeirut 最优的做法是在第二座建筑上建造 $2$ 层，使其比相邻的两座建筑都高。最终的建筑高度为 $[2, \underline{3}, 2]$。

在第二个测试用例中，“酷的”建筑的数量已经最大化，因此 Qpwoeirut 不需要做任何操作。

在第三个测试用例中，Qpwoeirut 最优的做法是在第三座和第五座建筑上分别建造 $2$ 层和 $1$ 层，使其成为“酷的”建筑。最终的建筑高度为 $[3, 1, \underline{6}, 5, \underline{6}, 2]$。

可以证明，不可能使超过 $2$ 座建筑成为“酷的”，也不可能用少于 $3$ 层来使 $2$ 座建筑成为“酷的”。

在第四个测试用例中，Qpwoeirut 可以选择使第二座建筑或第三座建筑成为“酷的”。无论哪种方式，他都需要建造 $3$ 层，并最大化“酷的”建筑的数量。最终的建筑高度为 $[4, 2, \underline{4}, 3, 5, 3, 6, 1]$ 或 $[4, \underline{5}, 1, 3, 5, 3, 6, 1]$。

### 题解分析与结论

#### 题解对比与总结

1. **Burnling 的题解（5星）**
   - **关键亮点**：详细分析了奇数和偶数情况下的最优解，并提出了前缀和与后缀和的优化方法，代码清晰且高效。
   - **核心思想**：
     - 对于奇数情况，直接计算偶数位置的建筑需要增加的楼层数。
     - 对于偶数情况，使用前缀和和后缀和来枚举不同分组方式的最小代价。
   - **代码实现**：
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

2. **happy_dengziyue 的题解（4星）**
   - **关键亮点**：简洁明了地处理了奇数和偶数情况，并通过前缀和优化了偶数情况的计算。
   - **核心思想**：
     - 对于奇数情况，直接计算偶数位置的建筑需要增加的楼层数。
     - 对于偶数情况，使用前缀和枚举不同分组方式的最小代价。
   - **代码实现**：
     ```cpp
     if(n&1){
         for(int i=2;i<n;i+=2)ans+=max(0ll,max(a[i-1],a[i+1])-a[i]+1);
         printf("%lld\n",ans);
     }
     else{
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

3. **ExplodingKonjac 的题解（4星）**
   - **关键亮点**：通过动态规划处理偶数情况，思路清晰，代码简洁。
   - **核心思想**：
     - 对于奇数情况，直接计算偶数位置的建筑需要增加的楼层数。
     - 对于偶数情况，使用动态规划枚举不同分组方式的最小代价。
   - **代码实现**：
     ```cpp
     if(n%2){
         ans=f[n-1];
     }else{
         for(int i=2;i<n;i++) ans=min(ans,f[i-1]+g[i+1]);
     }
     ```

#### 最优关键思路与技巧

- **奇数情况**：直接计算偶数位置的建筑需要增加的楼层数，确保每个偶数位置的建筑比相邻建筑高。
- **偶数情况**：使用前缀和与后缀和或动态规划来枚举不同分组方式的最小代价，确保在分组中选择最优的“酷的”建筑。

#### 可拓展之处

- 类似的问题可以通过分组和前缀和/后缀和来优化计算，尤其是在需要枚举多种情况时。
- 动态规划在处理分组问题时也非常有效，尤其是在需要选择最优子结构时。

#### 推荐题目

1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

这些题目都涉及到分组和优化问题，与本题的解题思路有相似之处。

---
处理用时：50.84秒