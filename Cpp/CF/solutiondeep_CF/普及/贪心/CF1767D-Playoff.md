# 题目信息

# Playoff

## 题目描述

$ 2^n $ teams participate in a playoff tournament. The tournament consists of $ 2^n - 1 $ games. They are held as follows: in the first phase of the tournament, the teams are split into pairs: team $ 1 $ plays against team $ 2 $ , team $ 3 $ plays against team $ 4 $ , and so on (so, $ 2^{n-1} $ games are played in that phase). When a team loses a game, it is eliminated, and each game results in elimination of one team (there are no ties). After that, only $ 2^{n-1} $ teams remain. If only one team remains, it is declared the champion; otherwise, the second phase begins, where $ 2^{n-2} $ games are played: in the first one of them, the winner of the game " $ 1 $ vs $ 2 $ " plays against the winner of the game " $ 3 $ vs $ 4 $ ", then the winner of the game " $ 5 $ vs $ 6 $ " plays against the winner of the game " $ 7 $ vs $ 8 $ ", and so on. This process repeats until only one team remains.

The skill level of the $ i $ -th team is $ p_i $ , where $ p $ is a permutation of integers $ 1 $ , $ 2 $ , ..., $ 2^n $ (a permutation is an array where each element from $ 1 $ to $ 2^n $ occurs exactly once).

You are given a string $ s $ which consists of $ n $ characters. These characters denote the results of games in each phase of the tournament as follows:

- if $ s_i $ is equal to 0, then during the $ i $ -th phase (the phase with $ 2^{n-i} $ games), in each match, the team with the lower skill level wins;
- if $ s_i $ is equal to 1, then during the $ i $ -th phase (the phase with $ 2^{n-i} $ games), in each match, the team with the higher skill level wins.

Let's say that an integer $ x $ is winning if it is possible to find a permutation $ p $ such that the team with skill $ x $ wins the tournament. Find all winning integers.

## 样例 #1

### 输入

```
3
101```

### 输出

```
4 5 6 7```

## 样例 #2

### 输入

```
1
1```

### 输出

```
2```

## 样例 #3

### 输入

```
2
01```

### 输出

```
2 3```

# AI分析结果

### 题目内容重写

$ 2^n $ 支队伍参加一场淘汰赛。比赛共有 $ 2^n - 1 $ 场比赛。比赛过程如下：在第一阶段，队伍被分成对：队伍 $ 1 $ 对阵队伍 $ 2 $，队伍 $ 3 $ 对阵队伍 $ 4 $，依此类推（因此，第一阶段有 $ 2^{n-1} $ 场比赛）。当一支队伍输掉比赛时，它将被淘汰，每场比赛都会淘汰一支队伍（没有平局）。之后，只剩下 $ 2^{n-1} $ 支队伍。如果只剩下一支队伍，它将被宣布为冠军；否则，第二阶段开始，进行 $ 2^{n-2} $ 场比赛：在第一场比赛中，比赛“ $ 1 $ vs $ 2 $”的胜者对阵比赛“ $ 3 $ vs $ 4 $”的胜者，然后比赛“ $ 5 $ vs $ 6 $”的胜者对阵比赛“ $ 7 $ vs $ 8 $”的胜者，依此类推。这个过程重复进行，直到只剩下一支队伍。

第 $ i $ 支队伍的能力值为 $ p_i $，其中 $ p $ 是 $ 1 $ 到 $ 2^n $ 的整数排列（排列是一个数组，其中从 $ 1 $ 到 $ 2^n $ 的每个元素恰好出现一次）。

给定一个由 $ n $ 个字符组成的字符串 $ s $。这些字符表示每阶段比赛的结果如下：

- 如果 $ s_i $ 等于 0，则在第 $ i $ 阶段（进行 $ 2^{n-i} $ 场比赛），在每场比赛中，能力值较低的队伍获胜；
- 如果 $ s_i $ 等于 1，则在第 $ i $ 阶段（进行 $ 2^{n-i} $ 场比赛），在每场比赛中，能力值较高的队伍获胜。

我们说一个整数 $ x $ 是获胜的，如果存在一个排列 $ p $，使得能力值为 $ x $ 的队伍赢得比赛。找出所有获胜的整数。

### 样例 #1

#### 输入

```
3
101
```

#### 输出

```
4 5 6 7
```

### 样例 #2

#### 输入

```
1
1
```

#### 输出

```
2
```

### 样例 #3

#### 输入

```
2
01
```

#### 输出

```
2 3
```

### 题解分析与结论

#### 综合分析

本题的核心在于通过给定的比赛规则，确定哪些能力值的队伍可能成为最终的冠军。题解中主要采用了动态规划和数学归纳的方法，通过计算每个阶段的可能排名范围，最终确定获胜队伍的能力值区间。

#### 最优关键思路

1. **动态规划与数学归纳**：通过自底向上的动态规划，计算每个阶段的可能排名范围，最终确定根节点的可能排名范围。
2. **分层处理**：将比赛过程分层处理，每层的规则决定了该层节点的排名计算方式。
3. **连续区间**：通过归纳法证明，获胜队伍的能力值排名是连续的，因此只需计算最小和最大可能排名即可。

#### 推荐题解

1. **作者：Leasier (赞：9)**  
   - **星级：5星**  
   - **关键亮点**：通过分层处理，简洁地计算了获胜队伍的最小和最大排名，代码简洁且高效。
   - **核心代码**：
     ```cpp
     int main(){
         int n, x = 0, up;
         scanf("%d", &n);
         scanf("%s", &s[1]);
         for (int i = 1; i <= n; i++){
             if (s[i] == '1') x++;
         }
         up = (1 << n) - (1 << (n - x)) + 1;
         for (int i = 1 << x; i <= up; i++){
             printf("%d ", i);
         }
         return 0;
     }
     ```

2. **作者：pineappler (赞：4)**  
   - **星级：4星**  
   - **关键亮点**：通过递推方法证明了获胜队伍的能力值区间，并给出了详细的推导过程。
   - **核心代码**：
     ```cpp
     int main(){
         int n;
         scanf("%d",&n);
         scanf("%s",c+1);
         int cnt1=0,cnt0=0;
         for(int i=1;i<=n;i++){
             if(c[i]=='0') cnt0++;
             else cnt1++;
         }
         for(int i=quickpow(2,cnt1);i<=quickpow(2,n)-quickpow(2,cnt0)+1;i++){
             printf("%d ",i);
         }
         return 0;
     }
     ```

3. **作者：CashCollectFactory (赞：1)**  
   - **星级：4星**  
   - **关键亮点**：通过打表法验证了获胜队伍的能力值区间，并给出了详细的推导过程。
   - **核心代码**：
     ```cpp
     int main(){
         int n;
         string s;
         cin>>n>>s;
         int cnt=0;
         for(int i=0;i<n;i++) if(s[i]=='1') cnt++;
         int l=(1<<cnt);
         cnt=n-cnt;
         int r=(1<<n)-(1<<cnt)+1;
         for(int i=l;i<=r;i++) cout<<i<<" ";
         return 0;
     }
     ```

#### 扩展思路

本题的思路可以推广到其他类似的淘汰赛问题，尤其是涉及多层规则和动态规划的问题。通过分层处理和数学归纳，可以有效地解决这类问题。

#### 推荐题目

1. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：42.73秒