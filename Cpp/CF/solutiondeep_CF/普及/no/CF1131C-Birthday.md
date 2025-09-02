# 题目信息

# Birthday

## 题目描述

Cowboy Vlad has a birthday today! There are $ n $ children who came to the celebration. In order to greet Vlad, the children decided to form a circle around him. Among the children who came, there are both tall and low, so if they stand in a circle arbitrarily, it may turn out, that there is a tall and low child standing next to each other, and it will be difficult for them to hold hands. Therefore, children want to stand in a circle so that the maximum difference between the growth of two neighboring children would be minimal possible.

Formally, let's number children from $ 1 $ to $ n $ in a circle order, that is, for every $ i $ child with number $ i $ will stand next to the child with number $ i+1 $ , also the child with number $ 1 $ stands next to the child with number $ n $ . Then we will call the discomfort of the circle the maximum absolute difference of heights of the children, who stand next to each other.

Please help children to find out how they should reorder themselves, so that the resulting discomfort is smallest possible.

## 说明/提示

In the first example, the discomfort of the circle is equal to $ 1 $ , since the corresponding absolute differences are $ 1 $ , $ 1 $ , $ 1 $ and $ 0 $ . Note, that sequences $ [2, 3, 2, 1, 1] $ and $ [3, 2, 1, 1, 2] $ form the same circles and differ only by the selection of the starting point.

In the second example, the discomfort of the circle is equal to $ 20 $ , since the absolute difference of $ 10 $ and $ 30 $ is equal to $ 20 $ .

## 样例 #1

### 输入

```
5
2 1 1 3 2
```

### 输出

```
1 2 3 2 1
```

## 样例 #2

### 输入

```
3
30 10 20
```

### 输出

```
10 20 30
```

# AI分析结果

【题目内容】
# 生日

## 题目描述

Cowboy Vlad今天过生日！有$n$个孩子来参加庆祝活动。为了迎接Vlad，孩子们决定围成一个圈站在他周围。来参加的孩子中有高有矮，如果随意站成一个圈，可能会出现高矮相邻的情况，这样他们很难牵手。因此，孩子们希望站成一个圈，使得相邻两个孩子身高差的最大值尽可能小。

形式化地，我们将孩子们从$1$到$n$编号，形成一个环形顺序，即对于每个$i$，编号为$i$的孩子与编号为$i+1$的孩子相邻，且编号为$1$的孩子与编号为$n$的孩子相邻。我们称这个圈的不适感为相邻两个孩子身高差的绝对值的最大值。

请帮助孩子们找到一个排列顺序，使得最终的不适感最小。

## 说明/提示

在第一个样例中，圈的不适感为$1$，因为对应的绝对差值为$1$、$1$、$1$和$0$。注意，序列$[2, 3, 2, 1, 1]$和$[3, 2, 1, 1, 2]$形成相同的圈，只是起始点不同。

在第二个样例中，圈的不适感为$20$，因为$10$和$30$的绝对差值为$20$。

## 样例 #1

### 输入

```
5
2 1 1 3 2
```

### 输出

```
1 2 3 2 1
```

## 样例 #2

### 输入

```
3
30 10 20
```

### 输出

```
10 20 30
```

【算法分类】  
贪心

【题解分析与结论】  
本题的核心目标是将孩子们的身高排列成一个环形，使得相邻两个孩子身高差的最大值最小。通过观察样例和分析，可以发现最优的排列方式是将身高排序后，奇数位和偶数位分别按顺序和逆序排列，形成一个“山峰”形状。这样可以确保相邻孩子的身高差最小。

【评分较高的题解】  
1. **作者：封禁用户 (赞：2)**  
   - **星级：4星**  
   - **关键亮点**：通过排序后，奇数位和偶数位分别按顺序和逆序排列，形成一个“山峰”形状，确保相邻孩子的身高差最小。代码简洁明了，逻辑清晰。
   - **代码核心实现**：
     ```cpp
     for(int i=1;i<=n;i+=2) cout<<a[i]<<" "; //输出奇数位置 
     if(n%2==0) for(int i=n;i>=2;i-=2) cout<<a[i]<<" "; //长度为偶，从n开始 
     else for(int i=n-1;i>=2;i-=2) cout<<a[i]<<" "; //长度为奇，从n-1开始 
     ```

2. **作者：_VEGETABLE_OIer_xlc (赞：0)**  
   - **星级：4星**  
   - **关键亮点**：通过构造“山峰”形状的排列，确保相邻孩子的身高差最小。代码实现简单，逻辑清晰。
   - **代码核心实现**：
     ```cpp
     for(int i=1;i<=n;i++)
         if(i%2==1)
             cout<<a[i]<<" "; 
     for(int i=n;i>=1;i--)
         if(i%2==0)
             cout<<a[i]<<" ";
     ```

3. **作者：zhouzihe (赞：0)**  
   - **星级：4星**  
   - **关键亮点**：通过排序后，奇数位和偶数位分别按顺序和逆序排列，形成一个“山峰”形状，确保相邻孩子的身高差最小。代码简洁，逻辑清晰。
   - **代码核心实现**：
     ```cpp
     for(int i=1;i<=n;i++){
         if(i%2==1){
             cout<<a[i]<<" ";
         }
     }
     for(int i=n;i>=1;i--){
         if(i%2==0){
             cout<<a[i]<<" ";
         }
     }
     ```

【最优关键思路或技巧】  
通过排序后，奇数位和偶数位分别按顺序和逆序排列，形成一个“山峰”形状，确保相邻孩子的身高差最小。这种贪心策略能够有效降低相邻身高差的最大值。

【可拓展之处】  
类似的问题可以扩展到其他环形排列问题，例如将物品排列成环形，使得相邻物品的某种属性差值最小。这类问题通常可以通过排序和贪心策略来解决。

【推荐题目】  
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)  
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：35.62秒