# 题目信息

# Flag 2

## 题目描述

According to a new ISO standard, a flag of every country should have, strangely enough, a chequered field $ n×m $ , each square should be wholly painted one of 26 colours. The following restrictions are set:

- In each row at most two different colours can be used.
- No two adjacent squares can be painted the same colour.

Pay attention, please, that in one column more than two different colours can be used.

Berland's government took a decision to introduce changes into their country's flag in accordance with the new standard, at the same time they want these changes to be minimal. By the given description of Berland's flag you should find out the minimum amount of squares that need to be painted different colour to make the flag meet the new ISO standard. You are as well to build one of the possible variants of the new Berland's flag.

## 样例 #1

### 输入

```
3 4
aaaa
bbbb
cccc
```

### 输出

```
6
abab
baba
acac
```

## 样例 #2

### 输入

```
3 3
aba
aba
zzz
```

### 输出

```
4
aba
bab
zbz
```

# AI分析结果

### 题目内容重写

#### 题目描述

根据新的ISO标准，每个国家的国旗都应该有一个奇特的棋盘式图案，大小为 $n×m$，每个方格必须完全涂成26种颜色中的一种。以下是设定的限制条件：

- 每一行最多只能使用两种不同的颜色。
- 相邻的两个方格不能涂成相同的颜色。

请注意，在一列中可以使用超过两种不同的颜色。

Berland政府决定根据新标准对其国旗进行修改，同时希望这些修改尽可能少。根据给定的Berland国旗描述，你需要找出使国旗符合新ISO标准所需的最小涂色方格数，并构建一种可能的新的Berland国旗。

#### 样例 #1

##### 输入

```
3 4
aaaa
bbbb
cccc
```

##### 输出

```
6
abab
baba
acac
```

#### 样例 #2

##### 输入

```
3 3
aba
aba
zzz
```

##### 输出

```
4
aba
bab
zbz
```

### 题解分析与结论

#### 综合分析与结论

本题的核心在于如何通过动态规划（DP）来最小化涂色次数，同时满足每行最多使用两种颜色且相邻方格颜色不同的条件。大多数题解都采用了类似的DP思路，即通过枚举每行的两种颜色，并确保与上一行的颜色不冲突，从而进行状态转移。以下是各题解的主要思路和优化点：

1. **DP状态设计**：大多数题解使用 `dp[i][j][k]` 表示第 `i` 行的第一个颜色为 `j`，第二个颜色为 `k` 时的最小涂色次数。
2. **状态转移**：通过枚举上一行的颜色 `j'` 和 `k'`，确保与当前行的颜色 `j` 和 `k` 不冲突，进行状态转移。
3. **预处理**：部分题解通过预处理 `cost[i][j][k]` 来减少计算量，表示将第 `i` 行涂成 `j` 和 `k` 的代价。
4. **回溯输出**：通过记录转移路径，回溯输出最终的涂色方案。

#### 精选题解

1. **作者：幽理家的男人 (评分：4星)**
   - **关键亮点**：清晰的DP状态设计和转移方程，预处理 `cost` 数组优化了计算效率。
   - **个人心得**：作者提到虽然时间复杂度较高，但通过优化成功AC，体现了对问题的深入理解。

   ```cpp
   for(int i=1;i<=n;++i){
       for(int j=0;j<26;++j){
           for(int k=0;k<26;++k){
               if(j==k) continue;
               for(int o=0;o<26;++o){
                   if(o==j) continue; 
                   for(int p=0;p<26;++p){
                       if(p==k||p==o) continue;
                       dp[i][j][k]=min(dp[i][j][k],dp[i-1][o][p]+cost[i][j][k]);
                   }
               }
           } 
       }
   }
   ```

2. **作者：封禁用户 (评分：4星)**
   - **关键亮点**：详细的优化介绍，包括内存抖动优化和卡常技巧，提升了代码效率。
   - **个人心得**：作者分享了调试经历，提到通过将记忆化搜索改为DP来避免TLE，体现了对问题的深入思考。

   ```cpp
   for(int i=1;i<=n;i++){
       for(int j1=0;j1<=25;j1++){	
           for(int k1=0;k1<=25;k1++){
               if(j1!=k1){
                   for(int j2=0;j2<=25;j2++){
                       if(j1!=j2){
                           for(int k2=0;k2<=25;k2++){
                               if(k1!=k2 && j2!=k2){
                                   dp[i][j2][k2]=min(dp[i][j2][k2],dp[i-1][j1][k1]+cost[i][j2][k2]);
                               }
                           }
                       }
                   }
               }
           }
       }
   }
   ```

3. **作者：Svemit (评分：4星)**
   - **关键亮点**：简洁的DP实现，清晰的回溯输出方案，代码可读性强。
   - **个人心得**：作者提到通过递归回溯输出方案，体现了对问题的全面考虑。

   ```cpp
   void output(int x, int fst, int scd) {
       if(!x) return;
       int lst = f[x][fst][scd] - cost[x][fst][scd];
       rep(i, 0, 25) rep(j, 0, 25)	{
           if(i == fst || j == scd || i == j) continue;
           if(f[x - 1][i][j] == lst) {
               output(x - 1, i, j); 
               goto ed;
           }	
       }
       ed:;
       rep(i, 1, m) 
           if(i & 1) cout << (char)('a' + fst);
           else cout << (char)('a' + scd);
       cout << '\n';
   }
   ```

### 最优关键思路与技巧

1. **DP状态设计**：使用 `dp[i][j][k]` 表示第 `i` 行的颜色组合 `(j, k)` 的最小涂色次数。
2. **预处理优化**：通过预处理 `cost[i][j][k]` 来减少重复计算，提升效率。
3. **回溯输出**：通过记录转移路径，回溯输出最终的涂色方案，确保输出正确。

### 可拓展之处

本题的DP思路可以拓展到类似的棋盘涂色问题，尤其是涉及行与行之间颜色限制的场景。类似的题目可以考察如何通过DP和状态转移来优化涂色方案。

### 推荐题目

1. [P1854 花店橱窗布置](https://www.luogu.com.cn/problem/P1854)
2. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)

---
处理用时：57.09秒