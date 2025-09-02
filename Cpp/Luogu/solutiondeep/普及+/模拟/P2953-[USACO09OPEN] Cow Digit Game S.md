# 题目信息

# [USACO09OPEN] Cow Digit Game S

## 题目描述

Bessie is playing a number game against Farmer John, and she wants you to help her achieve victory.

Game i starts with an integer N\_i (1 <= N\_i <= 1,000,000). Bessie goes first, and then the two players alternate turns. On each turn, a player can subtract either the largest digit or the smallest non-zero digit from the current number to obtain a new number. For example, from 3014 we may subtract either 1 or 4 to obtain either 3013 or 3010, respectively. The game continues until the number becomes 0, at which point the last player to have taken a turn is the winner.

Bessie and FJ play G (1 <= G <= 100) games. Determine, for each game, whether Bessie or FJ will win, assuming that both play perfectly (that is, on each turn, if the current player has a move that will guarantee his or her win, he or she will take it).

Consider a sample game where N\_i = 13. Bessie goes first and takes 3, leaving 10. FJ is forced to take 1, leaving 9. Bessie takes the remainder and wins the game.

贝茜和约翰在玩一个数字游戏．贝茜需要你帮助她．

游戏一共进行了G(1≤G≤100)场．第i场游戏开始于一个正整数Ni(l≤Ni≤1,000,000)．游

戏规则是这样的：双方轮流操作，将当前的数字减去一个数，这个数可以是当前数字的最大数码，也可以是最小的非0数码．比如当前的数是3014，操作者可以减去1变成3013，也可以减去4变成3010．若干次操作之后，这个数字会变成0．这时候不能再操作的一方为输家．    贝茜总是先开始操作．如果贝茜和约翰都足够聪明，执行最好的策略．请你计算最后的赢家．

比如，一场游戏开始于13.贝茜将13减去3变成10．约翰只能将10减去1变成9．贝茜再将9减去9变成0．最后贝茜赢．


## 说明/提示

For the first game, Bessie simply takes the number 9 and wins. For the second game, Bessie must take 1 (since she cannot take 0), and then FJ can win by taking 9.


## 样例 #1

### 输入

```
2 
9 
10 
```

### 输出

```
YES 
NO 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕博弈论展开，通过分析每个数字状态的后继状态来判断先手（贝茜）是否必胜。思路上，均先明确1 - 9为必胜态，0为必败态，之后从10开始遍历每个数，依据后继状态确定当前数的胜负态。算法要点在于找出每个数的最大和最小非零数位，并据此更新状态数组。解决难点在于理解博弈论中必胜态和必败态的转换关系，即必胜态至少有一个后继是必败态，必败态的所有后继都是必胜态。

### 所选的题解
- **作者：konjacq（5星）**
  - **关键亮点**：思路清晰，先阐述博弈论结论，代码简洁明了，还给出更快方法，虽因洛谷限制无法提交，但提供了优化思路。
  - **个人心得**：无
  ```cpp
  // 第一种方法
  #include <cstdio>
  using namespace std;

  int q,n;
  bool f[1000020];

  inline int fmax(int x)
  {
      int m=0;
      while (x) {if (x%10>m) m=x%10; x/=10;}
      return m;
  }

  inline int fmin(int x)
  {
      int m=10;
      while (x) {if (x%10<m&&x%10) m=x%10; x/=10;}
      return m;
  }

  int main()
  {
      //f[0]=false 不做处理（因为f默认为false）
      for (int i=1;i<10;i++) f[i]=true;
      for (int i=10;i<1000001;i++)
      {
          if (f[i-fmax(i)]&&f[i-fmin(i)])；//不做处理（因为f默认为false）
          else f[i]=true;
      }
      scanf ("%d",&q);
      for (int i=0;i<q;i++)
      {
          scanf ("%d",&n);
          if (f[n]) printf ("YES\n");
          else printf ("NO\n");
      }
      return 0;
  }
  ```
  核心实现思想：先初始化1 - 9为必胜态，然后从10开始遍历到1000000，对每个数i，通过fmax和fmin函数获取最大和最小非零数位，若i减去这两个数位后对应的状态都为必胜态，则i为必败态（因f数组默认false，此处不做处理），否则i为必胜态。最后根据输入的数字查询f数组输出结果。
- **作者：UperFicial（4星）**
  - **关键亮点**：对博弈论的阐述详细，不仅给出常规做法，还提出两种优化方法，并考虑到预处理范围优化，对时间和空间复杂度分析清晰。
  - **个人心得**：因审错题意WA了多次，强调审题重要性。
  ```cpp
  // 优化后的代码
  #include<bits/stdc++.h>
  using namespace std;
  int maxval;
  bool dp[1000005];
  inline int getmin(int x) {
      int res = 10;
      while(x) {
          if(x % 10 && x % 10 < res) res = x % 10;
          x /= 10;
      }
      return res;
  }
  inline int getmax(int x) {
      int res = 0;
      while(x) {
          if(x % 10 > res) res = x % 10;
          x /= 10;
      }
      return res;
  }
  int main() {
      int t; cin >> t;
      vector<int> a(t);
      for(int i = 0; i < t; i++) {
          cin >> a[i];
          maxval = max(maxval, a[i]);
      }
      for(int i = 1; i <= 9; i++) dp[i] = true;
      for(int i = 10; i <= maxval; i++) {
          int minn = getmin(i), maxn = getmax(i);
          dp[i] = (dp[i - minn] & dp[i - maxn]) ^ 1;
      }
      for(int i = 0; i < t; i++) {
          if(dp[a[i]]) cout << "YES\n";
          else cout << "NO\n";
      }
      return 0;
  }
  ```
  核心实现思想：先读入所有询问并记录最大值maxval，初始化1 - 9为必胜态。从10到maxval遍历，通过getmin和getmax函数获取每个数的最小非零数位和最大数位，利用`dp[i] = (dp[i - minn] & dp[i - maxn]) ^ 1`进行状态转移，最后根据dp数组输出每个询问结果。
- **作者：Exber（4星）**
  - **关键亮点**：直接给出状态转移方程，代码简洁，清晰展示DP思路。
  - **个人心得**：无
  ```cpp
  for(int i=1;i<=9;i++)
  {
      win[i]=true; // 初始化，一位数时贝茜一定能赢
  }
  for(int i=10;i<=1000003;i++)
  {
      int maxx=1,minn=9,tmp=i;
      while(tmp)
      {
          // 求最大数码和最小数码
          int k=tmp%10;
          tmp/=10;
          if(k>maxx)
          {
              maxx=k;
          }
          if(k!=0&&k<minn)
          {
              minn=k;
          }
      }
      if(!win[i-maxx]||!win[i-minn]) // 状态转移
      {
          win[i]=true;
      }
  }
  ```
  核心实现思想：先初始化1 - 9为必胜态，从10开始遍历到1000003，对每个数i求出其最大数码maxx和最小非零数码minn，根据状态转移方程`win[i] =!win[i - maxx] ||!win[i - minn]`更新win数组，确定每个数的胜负态。

### 最优关键思路或技巧
1. **状态转移**：依据博弈论中必胜态和必败态的转换关系进行状态转移，这是解决此类博弈问题的核心思路。
2. **预处理优化**：如UperFicial通过记录询问中的最大值，缩小预处理范围，减少不必要计算，优化时间复杂度。
3. **代码实现技巧**：使用inline函数加快获取最大、最小数位的速度，以及利用位运算简化状态转移判断，如`dp[x]=(dp[x - minn]&dp[x - maxn])^1`。

### 可拓展之处
此类题目属于博弈论中的状态转移类型，类似套路是先确定初始状态的胜负，再根据规则确定状态转移关系。同类型题可考虑一些基于数字操作或棋盘移动的博弈场景，例如在棋盘上按特定规则移动棋子，判断谁先到达特定位置等。

### 相似知识点洛谷题目
1. [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)：通过对两个数进行辗转相减操作，判断先手是否必胜，考察博弈论和状态分析。
2. [P2148 [SDOI2009]E&D](https://www.luogu.com.cn/problem/P2148)：在给定序列上进行取数操作，涉及博弈论和动态规划思想。
3. [P2252 取石子游戏II](https://www.luogu.com.cn/problem/P2252)：取石子的博弈问题，需要分析不同取石子规则下的胜负情况，锻炼博弈论思维。

### 个人心得摘录与总结
UperFicial提到因审错题意WA多次，强调了认真审题在解题中的重要性，读题时需准确理解题目规则和条件，避免因粗心大意导致错误。 

---
处理用时：52.29秒