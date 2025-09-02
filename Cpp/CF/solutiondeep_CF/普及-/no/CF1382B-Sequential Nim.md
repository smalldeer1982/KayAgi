# 题目信息

# Sequential Nim

## 题目描述

There are $ n $ piles of stones, where the $ i $ -th pile has $ a_i $ stones. Two people play a game, where they take alternating turns removing stones.

In a move, a player may remove a positive number of stones from the first non-empty pile (the pile with the minimal index, that has at least one stone). The first player who cannot make a move (because all piles are empty) loses the game. If both players play optimally, determine the winner of the game.

## 说明/提示

In the first test case, the first player will win the game. His winning strategy is:

1. The first player should take the stones from the first pile. He will take $ 1 $ stone. The numbers of stones in piles will be $ [1, 5, 4] $ .
2. The second player should take the stones from the first pile. He will take $ 1 $ stone because he can't take any other number of stones. The numbers of stones in piles will be $ [0,         5, 4] $ .
3. The first player should take the stones from the second pile because the first pile is empty. He will take $ 4 $ stones. The numbers of stones in piles will be $ [0, 1, 4] $ .
4. The second player should take the stones from the second pile because the first pile is empty. He will take $ 1 $ stone because he can't take any other number of stones. The numbers of stones in piles will be $ [0, 0, 4] $ .
5. The first player should take the stones from the third pile because the first and second piles are empty. He will take $ 4 $ stones. The numbers of stones in piles will be $ [0, 0,         0] $ .
6. The second player will lose the game because all piles will be empty.

## 样例 #1

### 输入

```
7
3
2 5 4
8
1 1 1 1 1 1 1 1
6
1 2 3 4 5 6
6
1 1 2 1 2 2
1
1000000000
5
1 2 2 1 1
3
1 1 1```

### 输出

```
First
Second
Second
First
First
Second
First```

# AI分析结果

### 题目内容
# 顺序尼姆游戏

## 题目描述
有$n$堆石子，其中第$i$堆有$a_i$个石子。两人进行游戏，轮流取石子。
在一轮操作中，玩家可以从第一个非空堆（即索引最小且至少有一个石子的堆）中取出正整数个石子。第一个无法进行操作（因为所有堆都为空）的玩家输掉游戏。如果双方都采取最优策略，确定游戏的获胜者。

## 说明/提示
在第一个测试用例中，第一个玩家将赢得游戏。他的获胜策略如下：
1. 第一个玩家应该从第一堆中取石子。他取$1$个石子。此时各堆石子数变为$[1, 5, 4]$。
2. 第二个玩家应该从第一堆中取石子。因为没有其他选择，他取$1$个石子。此时各堆石子数变为$[0, 5, 4]$。
3. 因为第一堆为空，第一个玩家应该从第二堆中取石子。他取$4$个石子。此时各堆石子数变为$[0, 1, 4]$。
4. 因为第一堆为空，第二个玩家应该从第二堆中取石子。因为没有其他选择，他取$1$个石子。此时各堆石子数变为$[0, 0, 4]$。
5. 因为第一堆和第二堆都为空，第一个玩家应该从第三堆中取石子。他取$4$个石子。此时各堆石子数变为$[0, 0, 0]$。
6. 第二个玩家将输掉游戏，因为所有堆都为空。

## 样例 #1
### 输入
```
7
3
2 5 4
8
1 1 1 1 1 1 1 1
6
1 2 3 4 5 6
6
1 1 2 1 2 2
1
1000000000
5
1 2 2 1 1
3
1 1 1
```
### 输出
```
First
Second
Second
First
First
Second
First
```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要围绕如何根据石子堆的数量分布来确定获胜者。大部分题解通过分析发现影响结果的关键在于前缀1的数量及所有堆是否都为1的情况。不同题解在分析过程和实现方式上有所差异，有的从策略角度直接推导，有的利用SG函数等方法。

### 所选的题解
- **作者：Rainy7 (5星)**
  - **关键亮点**：思路清晰简洁，直接从游戏策略出发，分析得出影响结果的是前缀1的数量，代码实现简单明了。
  - **重点代码核心思想**：统计前缀1的数量，根据数量的奇偶性及是否全为1的情况判断获胜者。
  ```cpp
  #include<iostream>
  #include<cstdio>
  #include<cstring>
  using namespace std;
  const int Maxn=1e5+5;
  int T,n,a[Maxn];
  int main()
  {	
      scanf("%d",&T);
      while(T--)
      {	
          int cnt=0,i;
          scanf("%d",&n);
          for(i=1;i<=n;i++)
              scanf("%d",&a[i]);
          for(i=1;i<=n;i++)
              if(a[i]==1)cnt++;
              else break;
          if(i==n+1)
          {	
              if(cnt%2==0)printf("Second\n");
              else printf("First\n");
          }
          else{
              if(cnt%2==0)printf("First\n");
              else printf("Second\n");
          }
      }
      return 0;
  }
  ```
- **作者：gaozitao1 (4星)**
  - **关键亮点**：通过对不同情况（全是1、没有1、开头有1、开头没有1）分别进行详细分析，逐步引导出最终的解题思路，易于理解。
  - **重点代码核心思想**：先找到第一个不是1的位置，根据前缀1的数量及是否全是1判断输赢。
  ```cpp
  #include<cstdio>
  #include<iostream>
  const int N=100000;
  int a[N+1];
  int main()
  {
  	register int i,n,t;
  	scanf("%d",&t);
  	while(t--)
  	{
  		scanf("%d",&n);
  		for(i=1; i<=n; ++i)
  			scanf("%d",&a[i]);
  		for(i=1; i<=n; ++i)
  			if(a[i]!=1)
  				break;
  		--i;
  		if(i<n)
  			if(i%2)
  				puts("Second");
  			else
  				puts("First");
  		else
  			if(n%2)
  				puts("First");
  			else
  				puts("Second");
  	}
  	return 0;
  }
  ```
- **作者：LRL65 (4星)**
  - **关键亮点**：从样例入手，详细分析取法和特殊情况“1”对先手的影响，推理过程清晰，便于读者理解为何只需要考虑前缀1。
  - **重点代码核心思想**：遍历统计前缀1的数量，根据其奇偶性判断获胜者。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t,n,m,a[100005];
  int main() {
      cin>>t;
      while(t--) {
          cin>>n;
          for(int i=1;i<=n;i++)cin>>a[i];
          int s=0;
          for(int i=1;i<=n;i++) {
              if(a[i]==1)s++;
              else {
                  s++;break;
              }
          }
          if(s%2==0)cout<<"Second"<<endl;
          else cout<<"First"<<endl;
      }
  }
  ```

### 最优关键思路或技巧
通过对游戏规则的深入分析，发现前缀1的数量是决定胜负的关键因素。利用这一规律，通过简单的计数和奇偶性判断即可得出结果，避免了复杂的搜索或状态计算。

### 可拓展之处
此类题目属于博弈论范畴，类似的题目通常需要深入分析游戏规则，找到影响胜负的关键因素。常见的拓展方向有改变取石子的规则，如可以从多个非空堆取，或者对取的石子数量进行更复杂的限制等。

### 洛谷相似题目
- [P2197 【模板】nim游戏](https://www.luogu.com.cn/problem/P2197)
- [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)
- [P3185 [HNOI2007] 分裂游戏](https://www.luogu.com.cn/problem/P3185)

### 个人心得摘录与总结
作者LRL65提到在比赛中思考15分钟后一遍通过本题，强调了从样例和题目说明入手分析问题的重要性，通过对样例的细致观察，总结出取石子的规律以及特殊情况“1”对游戏的影响，为解决问题提供了清晰的思路。 

---
处理用时：54.41秒