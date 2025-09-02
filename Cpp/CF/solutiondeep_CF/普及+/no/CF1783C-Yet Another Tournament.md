# 题目信息

# Yet Another Tournament

## 题目描述

You are participating in Yet Another Tournament. There are $ n + 1 $ participants: you and $ n $ other opponents, numbered from $ 1 $ to $ n $ .

Each two participants will play against each other exactly once. If the opponent $ i $ plays against the opponent $ j $ , he wins if and only if $ i > j $ .

When the opponent $ i $ plays against you, everything becomes a little bit complicated. In order to get a win against opponent $ i $ , you need to prepare for the match for at least $ a_i $ minutes — otherwise, you lose to that opponent.

You have $ m $ minutes in total to prepare for matches, but you can prepare for only one match at one moment. In other words, if you want to win against opponents $ p_1, p_2, \dots, p_k $ , you need to spend $ a_{p_1} + a_{p_2} + \dots + a_{p_k} $ minutes for preparation — and if this number is greater than $ m $ , you cannot achieve a win against all of these opponents at the same time.

The final place of each contestant is equal to the number of contestants with strictly more wins $ + $ $ 1 $ . For example, if $ 3 $ contestants have $ 5 $ wins each, $ 1 $ contestant has $ 3 $ wins and $ 2 $ contestants have $ 1 $ win each, then the first $ 3 $ participants will get the $ 1 $ -st place, the fourth one gets the $ 4 $ -th place and two last ones get the $ 5 $ -th place.

Calculate the minimum possible place (lower is better) you can achieve if you can't prepare for the matches more than $ m $ minutes in total.

## 说明/提示

In the first test case, you can prepare to all opponents, so you'll win $ 4 $ games and get the $ 1 $ -st place, since all your opponents win no more than $ 3 $ games.

In the second test case, you can prepare against the second opponent and win. As a result, you'll have $ 1 $ win, opponent $ 1 $ — $ 1 $ win, opponent $ 2 $ — $ 1 $ win, opponent $ 3 $ — $ 3 $ wins. So, opponent $ 3 $ will take the $ 1 $ -st place, and all other participants, including you, get the $ 2 $ -nd place.

In the third test case, you have no time to prepare at all, so you'll lose all games. Since each opponent has at least $ 1 $ win, you'll take the last place (place $ 6 $ ).

In the fourth test case, you have no time to prepare, but you can still win against the first opponent. As a result, opponent $ 1 $ has no wins, you have $ 1 $ win and all others have at least $ 2 $ wins. So your place is $ 4 $ .

## 样例 #1

### 输入

```
5
4 401
100 100 200 1
3 2
1 2 3
5 0
1 1 1 1 1
4 0
0 1 1 1
4 4
1 2 2 1```

### 输出

```
1
2
6
4
1```

# AI分析结果

### 题目内容重写

#### 题目描述

你正在参加“又一场比赛”。共有 $n + 1$ 名参赛者：你和 $n$ 名其他对手，编号从 $1$ 到 $n$。

每两名参赛者将进行一场比赛。如果对手 $i$ 与对手 $j$ 比赛，那么当且仅当 $i > j$ 时，对手 $i$ 获胜。

当对手 $i$ 与你比赛时，情况会稍微复杂一些。为了赢得与对手 $i$ 的比赛，你需要至少准备 $a_i$ 分钟——否则，你将输给该对手。

你总共有 $m$ 分钟的时间来准备比赛，但你一次只能准备一场比赛。换句话说，如果你想战胜对手 $p_1, p_2, \dots, p_k$，你需要花费 $a_{p_1} + a_{p_2} + \dots + a_{p_k}$ 分钟来准备——如果这个数字大于 $m$，你就无法同时战胜所有这些对手。

每位参赛者的最终排名等于获胜次数严格大于他的参赛者人数加 $1$。例如，如果有 $3$ 名参赛者各获得 $5$ 场胜利，$1$ 名参赛者获得 $3$ 场胜利，$2$ 名参赛者各获得 $1$ 场胜利，那么前 $3$ 名参赛者将获得第 $1$ 名，第 $4$ 名参赛者获得第 $4$ 名，最后两名参赛者获得第 $5$ 名。

计算你在总准备时间不超过 $m$ 分钟的情况下，能够获得的最小可能排名（排名越小越好）。

### 算法分类

贪心

### 题解分析与结论

本题的核心在于通过贪心策略最大化获胜次数，并通过调整策略来优化排名。大多数题解都采用了类似的思路：首先通过贪心选择花费时间最少的对手，尽可能多地获胜；然后考虑是否可以通过调整选择来战胜关键对手，从而进一步优化排名。

### 精选题解

#### 题解1：作者：liujy_ (赞：8)

- **星级**：★★★★★
- **关键亮点**：通过两次贪心选择，分别计算直接贪心和强制选择关键对手的排名，取较小值作为最终结果。思路清晰，代码实现简洁。
- **代码核心**：
  ```cpp
  sort(a+1,a+n+1); // 按准备时间排序
  for(int i=1;i<=n;i++){
      if(m<a[i].x)t[a[i].id]++;
      else m-=a[i].x,cnt++;
  }
  // 计算直接贪心的排名
  int tot=0,x=0;
  for(int i=1;i<=n;i++){
      if(t[i]>cnt)tot++;
      t[i]=i-1;
      if(a[i].id-1==cnt)x=i;
  }
  cnt=0;ans=tot+1;m=tmp;
  if(m>=a[x].x)m-=a[x].x,a[x].x=m+1000,t[a[x].id]--,cnt++;
  for(int i=1;i<=n;i++){
      if(m<a[i].x)t[a[i].id]++;
      else m-=a[i].x,cnt++;
  }
  // 计算强制选择关键对手的排名
  tot=0;
  for(int i=1;i<=n;i++)
      if(t[i]>cnt)tot++;
  printf("%d\n",min(ans,tot+1));
  ```

#### 题解2：作者：AllenKING_RED (赞：6)

- **星级**：★★★★
- **关键亮点**：通过贪心选择最大获胜次数，并判断是否可以通过替换已选择的对手来战胜关键对手，从而优化排名。
- **代码核心**：
  ```cpp
  sort(pr+1,pr+n+1,cmp); // 按准备时间排序
  for(int i=1;i<=n;i++){
      if(m>=pr[i].sum){
          ans++;
          m-=pr[i].sum;
          vis[pr[i].id]=1;
      }
  }
  int last=ans;
  int sum=n-ans+1;
  if((vis[ans+1]||m>=(a[ans+1]-pr[last].sum))&&sum>1)--sum;
  cout<<sum<<endl;
  ```

#### 题解3：作者：Air_Color5 (赞：4)

- **星级**：★★★★
- **关键亮点**：通过贪心选择最大获胜次数，并通过分类讨论判断是否可以通过调整选择来战胜关键对手，从而优化排名。
- **代码核心**：
  ```cpp
  sort(b.begin(), b.end()); // 按准备时间排序
  for(int i=0;i<n&&m>=b[i];i++)
      m-=b[i],x++;
  if(x>0&&x<n&&m+b[x-1]-a[x]>=0)x++;
  printf("%d\n",n-x+1);
  ```

### 最优关键思路

1. **贪心选择**：优先选择花费时间最少的对手，尽可能多地获胜。
2. **调整策略**：在确保获胜次数不变的前提下，尝试战胜关键对手，以优化排名。

### 拓展思路

本题的贪心策略可以应用于类似的资源分配问题，如背包问题、任务调度等。通过贪心选择最优解，并通过调整策略进一步优化结果。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

---
处理用时：46.19秒