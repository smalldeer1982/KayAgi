# 题目信息

# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
3 100
50 50 100
```

### 输出

```
5
2
```

## 样例 #3

### 输入

```
2 50
50 50
```

### 输出

```
-1
0
```

# AI分析结果

### 题目内容重写
#### Greg 和朋友们

##### 题目描述
一天，Greg 和他的朋友们在森林里散步。总共有 $n$ 个人，包括 Greg。不久，他们来到了一条河边。大家决定过河。幸运的是，河边正好有一条船，船的载重最多为 $k$ 公斤。

Greg 立即拿出一张纸，列出了所有人的体重（包括他自己）。他发现每个人的体重要么是 50 公斤，要么是 100 公斤。现在，Greg 想知道最少需要多少次渡船才能将所有人运到对岸。船至少需要一个人来操作。每次渡船时，船上可以有任意数量的人，只要他们的总重量不超过 $k$ 公斤。

此外，Greg 还想知道在最少渡船次数的情况下，有多少种不同的运输方案。如果某次渡船时船上的人员不同，则认为这是两种不同的方案。

帮助 Greg 解决这个问题。

##### 说明/提示
在第一个测试中，Greg 独自一人，因此只需要一次渡船。

在第二个测试中，你应该按照以下计划进行：
1. 运送两个 50 公斤的人；
2. 运送一个 50 公斤的人回来；
3. 运送一个 100 公斤的人；
4. 运送一个 50 公斤的人回来；
5. 运送两个 50 公斤的人。

总共需要 5 次渡船。根据第二步选择不同的人，可以得到两种不同的方案。

##### 样例 #1
###### 输入
```
1 50
50
```
###### 输出
```
1
1
```

##### 样例 #2
###### 输入
```
3 100
50 50 100
```
###### 输出
```
5
2
```

##### 样例 #3
###### 输入
```
2 50
50 50
```
###### 输出
```
-1
0
```

### 题解分析与结论
#### 综合分析
1. **动态规划与组合数学**：大多数题解都采用了动态规划（DP）的思路，结合组合数学来计算方案数。通过定义状态表示当前岸上 50kg 和 100kg 的人数，以及船的位置，进行状态转移。
2. **广度优先搜索（BFS）**：部分题解结合了 BFS 来寻找最短渡船次数，同时利用 DP 来计算方案数。这种方法在保证最短路径的同时，也能高效计算方案数。
3. **状态转移与边界条件**：所有题解都详细定义了状态转移方程和边界条件，确保 DP 的正确性。特别是对于船的位置（出发岸或对岸）的处理，是解题的关键。

#### 最优题解推荐
1. **作者：gesong (赞：4)**
   - **星级**：4.5
   - **关键亮点**：结合了 BFS 和 DP，通过枚举每次渡船的人数，确保最短渡船次数的同时，利用组合数计算方案数。代码结构清晰，状态转移方程明确。
   - **核心代码**：
     ```cpp
     for (int i=1;i<=4*n;i++)
         for (int j=0;j<=x;j++)
             for (int k=0;k<=min(y,n-j);k++){
                 if (i&1){
                     for (int a=0;a<=x-j;a++)
                         for (int b=0;b<=y-k;b++)
                             if (!(a==0&&b==0)&&50*a+100*b<=m)
                                 f[i][j][k]=(f[i][j][k]+f[i-1][j+a][k+b]*C[j+a][a]%mod*C[k+b][b]%mod)%mod;
                     if (f[i][0][0]){
                         cout <<i<<endl<<f[i][0][0];
                         return 0;
                     }
                 }
                 else{
                     for (int a=0;a<=j;a++)
                         for (int b=0;b<=k;b++)
                             if (!(a==0&&b==0)&&50*a+100*b<=m)
                                 f[i][j][k]=(f[i][j][k]+f[i-1][j-a][k-b]*C[x-j+a][a]%mod*C[y-k+b][b]%mod)%mod;
                 }
             }
     ```

2. **作者：zztqwq (赞：3)**
   - **星级**：4
   - **关键亮点**：通过定义船的位置（出发岸或对岸）来简化状态转移，利用组合数计算方案数。代码简洁，思路清晰。
   - **核心代码**：
     ```cpp
     for (int i=1;i<=4*n;i++){
         for (int j=0;j<=tot5;j++)
             for (int k=0;k<=tot1;k++)
                 f[i&1][j][k]=0;
         for (int j=0;j<=tot5;j++){
             for (int k=0;k<=tot1;k++){
                 if (i&1){
                     for (int c5=0;c5<=tot5-j;c5++){
                         for (int c1=0;c1<=tot1-k;c1++){
                             if (!c5&&!c1)continue;
                             if (50*c5+100*c1>K) continue;
                             f[1][j+c5][k+c1]+=(long long)binom(tot5-j,c5)*binom(tot1-k,c1)%mod*f[0][j][k]%mod;
                             f[1][j+c5][k+c1]%=mod;
                         }
                     }
                 }
                 else{
                     for (int c5=0;c5<=j;c5++){
                         for (int c1=0;c1<=k;c1++){
                             if (!c5&&!c1)continue;
                             if (50*c5+100*c1>K) continue;
                             f[0][j-c5][k-c1]+=(long long)binom(j,c5)*binom(k,c1)%mod*f[1][j][k]%mod;
                             f[0][j-c5][k-c1]%=mod;
                         }
                     }
                 }
             }
         }
         if (f[i&1][tot5][tot1]){
             printf("%d\n%d",i,f[i&1][tot5][tot1]);
             return 0;
         }
     }
     ```

3. **作者：SevenDawns (赞：3)**
   - **星级**：4
   - **关键亮点**：结合了 BFS 和 DP，通过枚举每次渡船的人数，确保最短渡船次数的同时，利用组合数计算方案数。代码结构清晰，状态转移方程明确。
   - **核心代码**：
     ```cpp
     void bfs(ll i1,ll j1,ll wh){
         ll l,r;
         l=0;r=0;
         sh[l].i=i1;
         sh[l].j=j1;
         sh[l].k=wh;
         r++;
         while (l<r){
             ll nowi,nowj,nowh;
             nowi=sh[l].i;
             nowj=sh[l].j;
             nowh=sh[l].k;
             l++;
             if (nowh==1)
             for (ll x=0;x<=nowi;x++){
                 for (ll y=0;y<=nowj;y++){
                     if (50*x+100*y>w || (x==0 && y==0))
                       continue;
                     ll xi,xj,xwh;
                     xi=nowi-x;
                     xj=nowj-y;
                     xwh=1-nowh;
                     if (step[xi][xj][xwh]!=0){
                         if (step[nowi][nowj][nowh]+1<step[xi][xj][xwh])
                           step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
                         if (step[nowi][nowj][nowh]+1==step[xi][xj][xwh]){
                             dp[xi][xj][xwh]+=(b[nowi+1][x+1]%mod)*(b[nowj+1][y+1]%mod)*(dp[nowi][nowj][nowh]%mod);
                             dp[xi][xj][xwh]%=mod;
                         }
                     }
                     else{
                         dp[xi][xj][xwh]=(b[nowi+1][x+1]%mod)*(b[nowj+1][y+1]%mod)*(dp[nowi][nowj][nowh]%mod);
                         dp[xi][xj][xwh]%=mod;
                         step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
                         sh[r].i=xi;
                         sh[r].j=xj;
                         sh[r].k=xwh;
                         r++;
                     }
                 }
             }
             if (nowh==0)
             for (ll x=0;x<=t50-nowi;x++){
                 for (ll y=0;y<=t100-nowj;y++){
                     if (50*x+100*y>w || (x==0 && y==0))
                       continue;
                     ll xi,xj,xwh;
                     xi=nowi+x;
                     xj=nowj+y;
                     xwh=1-nowh;
                     if (step[xi][xj][xwh]!=0){
                         if (step[nowi][nowj][nowh]+1<step[xi][xj][xwh])
                           step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
                         if (step[nowi][nowj][nowh]+1==step[xi][xj][xwh]){
                             dp[xi][xj][xwh]+=(b[t50-nowi+1][x+1]%mod)*(b[t100-nowj+1][y+1]%mod)*(dp[nowi][nowj][nowh]%mod);
                             dp[xi][xj][xwh]%=mod;
                         }
                     }
                     else{
                         dp[xi][xj][xwh]=(b[t50-nowi+1][x+1]%mod)*(b[t100-nowj+1][y+1]%mod)*(dp[nowi][nowj][nowh]%mod);
                         dp[xi][xj][xwh]%=mod;
                         step[xi][xj][xwh]=step[nowi][nowj][nowh]+1;
                         sh[r].i=xi;
                         sh[r].j=xj;
                         sh[r].k=xwh;
                         r++;
                     }
                 }
             }
         }
     }
     ```

### 最优关键思路与技巧
1. **状态定义与转移**：通过定义当前岸上 50kg 和 100kg 的人数以及船的位置，进行状态转移。这是解决此类问题的核心。
2. **组合数学**：利用组合数计算每次渡船的可能方案数，确保方案数的正确性。
3. **BFS 与 DP 结合**：通过 BFS 寻找最短渡船次数，同时利用 DP 计算方案数，确保高效性和正确性。

### 可拓展之处
1. **类似问题**：可以扩展到其他类似的运输问题，如不同载重限制、不同人数限制等。
2. **优化技巧**：可以通过剪枝或记忆化搜索进一步优化 DP 的效率。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

---
处理用时：89.31秒