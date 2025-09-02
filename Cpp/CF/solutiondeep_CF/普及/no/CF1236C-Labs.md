# 题目信息

# Labs

## 题目描述

In order to do some research, $ n^2 $ labs are built on different heights of a mountain. Let's enumerate them with integers from $ 1 $ to $ n^2 $ , such that the lab with the number $ 1 $ is at the lowest place, the lab with the number $ 2 $ is at the second-lowest place, $ \ldots $ , the lab with the number $ n^2 $ is at the highest place.

To transport water between the labs, pipes are built between every pair of labs. A pipe can transport at most one unit of water at a time from the lab with the number $ u $ to the lab with the number $ v $ if $ u > v $ .

Now the labs need to be divided into $ n $ groups, each group should contain exactly $ n $ labs. The labs from different groups can transport water to each other. The sum of units of water that can be sent from a group $ A $ to a group $ B $ is equal to the number of pairs of labs ( $ u, v $ ) such that the lab with the number $ u $ is from the group $ A $ , the lab with the number $ v $ is from the group $ B $ and $ u > v $ . Let's denote this value as $ f(A,B) $ (i.e. $ f(A,B) $ is the sum of units of water that can be sent from a group $ A $ to a group $ B $ ).

For example, if $ n=3 $ and there are $ 3 $ groups $ X $ , $ Y $ and $ Z $ : $ X = \{1, 5, 6\}, Y = \{2, 4, 9\} $ and $ Z = \{3, 7, 8\} $ . In this case, the values of $ f $ are equal to:

- $ f(X,Y)=4 $ because of $ 5 \rightarrow 2 $ , $ 5 \rightarrow 4 $ , $ 6 \rightarrow 2 $ , $ 6 \rightarrow 4 $ ,
- $ f(X,Z)=2 $ because of $ 5 \rightarrow 3 $ , $ 6 \rightarrow 3 $ ,
- $ f(Y,X)=5 $ because of $ 2 \rightarrow 1 $ , $ 4 \rightarrow 1 $ , $ 9 \rightarrow 1 $ , $ 9 \rightarrow 5 $ , $ 9 \rightarrow 6 $ ,
- $ f(Y,Z)=4 $ because of $ 4 \rightarrow 3 $ , $ 9 \rightarrow 3 $ , $ 9 \rightarrow 7 $ , $ 9 \rightarrow 8 $ ,
- $ f(Z,X)=7 $ because of $ 3 \rightarrow 1 $ , $ 7 \rightarrow 1 $ , $ 7 \rightarrow 5 $ , $ 7 \rightarrow 6 $ , $ 8 \rightarrow 1 $ , $ 8 \rightarrow 5 $ , $ 8 \rightarrow 6 $ ,
- $ f(Z,Y)=5 $ because of $ 3 \rightarrow 2 $ , $ 7 \rightarrow 2 $ , $ 7 \rightarrow 4 $ , $ 8 \rightarrow 2 $ , $ 8 \rightarrow 4 $ .

Please, divide labs into $ n $ groups with size $ n $ , such that the value $ \min f(A,B) $ over all possible pairs of groups $ A $ and $ B $ ( $ A \neq B $ ) is maximal.

In other words, divide labs into $ n $ groups with size $ n $ , such that minimum number of the sum of units of water that can be transported from a group $ A $ to a group $ B $ for every pair of different groups $ A $ and $ B $ ( $ A \neq B $ ) as big as possible.

Note, that the example above doesn't demonstrate an optimal division, but it demonstrates how to calculate the values $ f $ for some division.

If there are many optimal divisions, you can find any.

## 说明/提示

In the first test we can divide $ 9 $ labs into groups $ \{2, 8, 5\}, \{9, 3, 4\}, \{7, 6, 1\} $ .

From the first group to the second group we can transport $ 4 $ units of water ( $ 8 \rightarrow 3, 8 \rightarrow 4, 5 \rightarrow 3, 5 \rightarrow 4 $ ).

From the first group to the third group we can transport $ 5 $ units of water ( $ 2 \rightarrow 1, 8 \rightarrow 7, 8 \rightarrow 6, 8 \rightarrow 1, 5 \rightarrow 1 $ ).

From the second group to the first group we can transport $ 5 $ units of water ( $ 9 \rightarrow 2, 9 \rightarrow 8, 9 \rightarrow 5, 3 \rightarrow 2, 4 \rightarrow 2 $ ).

From the second group to the third group we can transport $ 5 $ units of water ( $ 9 \rightarrow 7, 9 \rightarrow 6, 9 \rightarrow 1, 3 \rightarrow 1, 4 \rightarrow 1 $ ).

From the third group to the first group we can transport $ 4 $ units of water ( $ 7 \rightarrow 2, 7 \rightarrow 5, 6 \rightarrow 2, 6 \rightarrow 5 $ ).

From the third group to the second group we can transport $ 4 $ units of water ( $ 7 \rightarrow 3, 7 \rightarrow 4, 6 \rightarrow 3, 6 \rightarrow 4 $ ).

The minimal number of the sum of units of water, that can be transported from one group to another is equal to $ 4 $ . It can be proved, that it is impossible to make a better division.

## 样例 #1

### 输入

```
3
```

### 输出

```
2 8 5
9 3 4
7 6 1
```

# AI分析结果

【题目内容】
# Labs

## 题目描述

为了进行一些研究，$ n^2 $ 个实验室被建在山的不同高度上。我们用从 $ 1 $ 到 $ n^2 $ 的整数来编号这些实验室，编号为 $ 1 $ 的实验室位于最低处，编号为 $ 2 $ 的实验室位于第二低处，依此类推，编号为 $ n^2 $ 的实验室位于最高处。

为了在实验室之间运输水，每对实验室之间都建立了管道。如果 $ u > v $，则管道可以从编号为 $ u $ 的实验室向编号为 $ v $ 的实验室运输最多一单位的水。

现在需要将这些实验室分成 $ n $ 组，每组应包含恰好 $ n $ 个实验室。不同组之间的实验室可以互相运输水。从组 $ A $ 到组 $ B $ 可以发送的水的总单位数等于满足以下条件的实验室对 $(u, v)$ 的数量：编号为 $ u $ 的实验室来自组 $ A $，编号为 $ v $ 的实验室来自组 $ B $，且 $ u > v $。我们将这个值记为 $ f(A,B) $（即 $ f(A,B) $ 是从组 $ A $ 到组 $ B $ 可以发送的水的总单位数）。

例如，如果 $ n=3 $ 且有 $ 3 $ 组 $ X $、$ Y $ 和 $ Z $：$ X = \{1, 5, 6\}, Y = \{2, 4, 9\} $ 和 $ Z = \{3, 7, 8\} $。在这种情况下，$ f $ 的值为：

- $ f(X,Y)=4 $，因为 $ 5 \rightarrow 2 $，$ 5 \rightarrow 4 $，$ 6 \rightarrow 2 $，$ 6 \rightarrow 4 $，
- $ f(X,Z)=2 $，因为 $ 5 \rightarrow 3 $，$ 6 \rightarrow 3 $，
- $ f(Y,X)=5 $，因为 $ 2 \rightarrow 1 $，$ 4 \rightarrow 1 $，$ 9 \rightarrow 1 $，$ 9 \rightarrow 5 $，$ 9 \rightarrow 6 $，
- $ f(Y,Z)=4 $，因为 $ 4 \rightarrow 3 $，$ 9 \rightarrow 3 $，$ 9 \rightarrow 7 $，$ 9 \rightarrow 8 $，
- $ f(Z,X)=7 $，因为 $ 3 \rightarrow 1 $，$ 7 \rightarrow 1 $，$ 7 \rightarrow 5 $，$ 7 \rightarrow 6 $，$ 8 \rightarrow 1 $，$ 8 \rightarrow 5 $，$ 8 \rightarrow 6 $，
- $ f(Z,Y)=5 $，因为 $ 3 \rightarrow 2 $，$ 7 \rightarrow 2 $，$ 7 \rightarrow 4 $，$ 8 \rightarrow 2 $，$ 8 \rightarrow 4 $。

请将实验室分成 $ n $ 组，每组大小为 $ n $，使得所有不同组对 $ A $ 和 $ B $（$ A \neq B $）的 $ f(A,B) $ 的最小值最大化。

换句话说，将实验室分成 $ n $ 组，每组大小为 $ n $，使得对于每一对不同组 $ A $ 和 $ B $（$ A \neq B $），从组 $ A $ 到组 $ B $ 可以发送的水的总单位数的最小值尽可能大。

注意，上面的示例并不展示最优的分组方式，但它展示了如何计算某些分组方式下的 $ f $ 值。

如果有多个最优分组方式，可以输出任意一个。

## 说明/提示

在第一个测试中，我们可以将 $ 9 $ 个实验室分成组 $ \{2, 8, 5\}, \{9, 3, 4\}, \{7, 6, 1\} $。

从第一组到第二组可以运输 $ 4 $ 单位的水（$ 8 \rightarrow 3, 8 \rightarrow 4, 5 \rightarrow 3, 5 \rightarrow 4 $）。

从第一组到第三组可以运输 $ 5 $ 单位的水（$ 2 \rightarrow 1, 8 \rightarrow 7, 8 \rightarrow 6, 8 \rightarrow 1, 5 \rightarrow 1 $）。

从第二组到第一组可以运输 $ 5 $ 单位的水（$ 9 \rightarrow 2, 9 \rightarrow 8, 9 \rightarrow 5, 3 \rightarrow 2, 4 \rightarrow 2 $）。

从第二组到第三组可以运输 $ 5 $ 单位的水（$ 9 \rightarrow 7, 9 \rightarrow 6, 9 \rightarrow 1, 3 \rightarrow 1, 4 \rightarrow 1 $）。

从第三组到第一组可以运输 $ 4 $ 单位的水（$ 7 \rightarrow 2, 7 \rightarrow 5, 6 \rightarrow 2, 6 \rightarrow 5 $）。

从第三组到第二组可以运输 $ 4 $ 单位的水（$ 7 \rightarrow 3, 7 \rightarrow 4, 6 \rightarrow 3, 6 \rightarrow 4 $）。

可以证明，这种分组方式是最优的，无法找到更好的分组方式。

## 样例 #1

### 输入

```
3
```

### 输出

```
2 8 5
9 3 4
7 6 1
```

【算法分类】构造

【题解分析与结论】
该题的核心在于如何将 $n^2$ 个实验室分成 $n$ 组，每组 $n$ 个实验室，使得不同组之间的传输量尽可能均衡。题解中主要采用了“蛇形”分配法，即奇数列递增，偶数列递减的构造方式。这种方法能够保证每组中的实验室编号分布均匀，从而使得不同组之间的传输量最小值的最大化。

【评分较高的题解】
1. **作者：wlj_55 (赞：10)**
   - **星级：5星**
   - **关键亮点**：详细分析了构造矩阵的规律，并给出了数学证明，证明了该构造方式的最优性。代码实现简洁明了。
   - **代码核心思想**：通过奇数列递增、偶数列递减的方式构造矩阵，确保每组中的实验室编号分布均匀。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++){
         if(i&1){
             for(int j=1;j<=n;j++){
                 f[j][i]=++cnt;
             }
         }
         else{
             for(int j=n;j>=1;j--){
                 f[j][i]=++cnt;
             }
         }
     }
     ```

2. **作者：Lazy_Labs (赞：1)**
   - **星级：4星**
   - **关键亮点**：通过找规律的方式构造矩阵，并提供了 checker 来验证构造的正确性。代码实现简洁，适合快速理解。
   - **代码核心思想**：采用蛇形分配法，奇数列递增，偶数列递减，确保每组中的实验室编号分布均匀。
   - **核心代码**：
     ```cpp
     int x=1,y=1,now=1;
     while(x!=n||y!=n){
         g[x][y]=now++;
         if(y&1){
             if(x!=n)x++;
             else y++;
         }
         else {
             if(x!=1)x--;
             else y++;
         }
     }
     g[n][n]=n*n;
     ```

3. **作者：Hutao__ (赞：0)**
   - **星级：4星**
   - **关键亮点**：通过构造矩阵的方式，详细分析了奇数列和偶数列的分配规律，并给出了数学证明。代码实现简洁。
   - **代码核心思想**：采用奇数列递增、偶数列递减的方式构造矩阵，确保每组中的实验室编号分布均匀。
   - **核心代码**：
     ```cpp
     for (int i = 1 ; i <= n ; i ++){
         if (i % 2 == 1){
             for (int j = 1;j <= n ; j ++){
                 f[j][i] = ++cnt;
             }
         }else{
             for (int j = n;j >= 1 ; j --){
                 f[j][i] = ++cnt;
             }
         }
     }
     ```

【最优关键思路或技巧】
- **蛇形分配法**：通过奇数列递增、偶数列递减的方式构造矩阵，确保每组中的实验室编号分布均匀，从而使得不同组之间的传输量最小值的最大化。
- **数学证明**：通过数学推导证明该构造方式的最优性，确保构造的正确性。

【可拓展之处】
- 类似的问题可以通过构造矩阵的方式来优化，尤其是在需要均匀分配资源或任务的情况下。
- 该题的构造思路可以应用于其他需要分组优化的场景，如任务分配、资源调度等。

【推荐题目】
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

【个人心得摘录】
- **wlj_55**：通过构造矩阵的方式，详细分析了奇数列和偶数列的分配规律，并给出了数学证明，确保构造的正确性。
- **Lazy_Labs**：通过找规律的方式构造矩阵，并提供了 checker 来验证构造的正确性，适合快速理解。
- **Hutao__**：通过构造矩阵的方式，详细分析了奇数列和偶数列的分配规律，并给出了数学证明，代码实现简洁。

---
处理用时：68.28秒