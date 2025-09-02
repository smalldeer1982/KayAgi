# 题目信息

# Belted Rooms

## 题目描述

In the snake exhibition, there are $ n $ rooms (numbered $ 0 $ to $ n - 1 $ ) arranged in a circle, with a snake in each room. The rooms are connected by $ n $ conveyor belts, and the $ i $ -th conveyor belt connects the rooms $ i $ and $ (i+1) \bmod n $ . In the other words, rooms $ 0 $ and $ 1 $ , $ 1 $ and $ 2 $ , $ \ldots $ , $ n-2 $ and $ n-1 $ , $ n-1 $ and $ 0 $ are connected with conveyor belts.

The $ i $ -th conveyor belt is in one of three states:

- If it is clockwise, snakes can only go from room $ i $ to $ (i+1) \bmod n $ .
- If it is anticlockwise, snakes can only go from room $ (i+1) \bmod n $ to $ i $ .
- If it is off, snakes can travel in either direction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1428B/76fac914463a158de3ff2f71ea695b0a2d793a84.png)Above is an example with $ 4 $ rooms, where belts $ 0 $ and $ 3 $ are off, $ 1 $ is clockwise, and $ 2 $ is anticlockwise.

Each snake wants to leave its room and come back to it later. A room is returnable if the snake there can leave the room, and later come back to it using the conveyor belts. How many such returnable rooms are there?

## 说明/提示

In the first test case, all rooms are returnable except room $ 2 $ . The snake in the room $ 2 $ is trapped and cannot exit. This test case corresponds to the picture from the problem statement.

 In the second test case, all rooms are returnable by traveling on the series of clockwise belts.

## 样例 #1

### 输入

```
4
4
-><-
5
>>>>>
3
<--
2
<>```

### 输出

```
3
5
3
0```

# AI分析结果

### 题目内容
# 环形房间

## 题目描述
在蛇类展览中，有$n$个房间（编号从$0$到$n - 1$）呈环形排列，每个房间里都有一条蛇。房间之间由$n$条传送带相连，第$i$条传送带连接房间$i$和$(i + 1) \bmod n$。换句话说，房间$0$和$1$、$1$和$2$、$\ldots$、$n - 2$和$n - 1$、$n - 1$和$0$之间都通过传送带相连。

第$i$条传送带处于以下三种状态之一：
- 如果是顺时针状态，蛇只能从房间$i$前往$(i + 1) \bmod n$。
- 如果是逆时针状态，蛇只能从房间$(i + 1) \bmod n$前往$i$。
- 如果是关闭状态，蛇可以双向通行。

![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1428B/76fac914463a158de3ff2f71ea695b0a2d793a84.png)
上图是一个有$4$个房间的示例，其中传送带$0$和$3$处于关闭状态，$1$是顺时针状态，$2$是逆时针状态。

每条蛇都想离开自己所在的房间，然后再回到该房间。如果一条蛇能够离开所在房间，并通过传送带回到该房间，那么这个房间就是可返回的。请问这样的可返回房间有多少个？

## 说明/提示
在第一个测试用例中，除了房间$2$之外，所有房间都是可返回的。房间$2$里的蛇被困住，无法离开。这个测试用例与题目描述中的图片相对应。

在第二个测试用例中，通过一系列顺时针的传送带，所有房间都是可返回的。

## 样例 #1
### 输入
```
4
4
-><-
5
>>>>>
3
<--
2
<>
```
### 输出
```
3
5
3
0
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解的核心思路都是围绕传送带状态与房间可返回性的关系展开。大部分题解都发现了关键性质：当不存在方向相反的单向传送带（即全为顺时针或全为逆时针，可夹杂双向传送带）时，所有房间都可返回；当存在方向相反的单向传送带时，只有与双向传送带相邻的房间可返回。
- **思路方面**：多数题解通过遍历传送带状态进行判断，部分题解从图论角度找环来判断可返回房间，但相对复杂。
- **算法要点**：关键在于准确判断传送带状态组合对房间可返回性的影响，并正确统计可返回房间数量。
- **解决难点**：处理环形结构以及不同传送带状态组合的判断，部分题解还需注意避免重复统计。

### 所选的题解
- **作者：jun头吉吉（5星）**
  - **关键亮点**：思路清晰简洁，直接抓住问题本质，通过统计不同传送带状态的数量来判断所有房间是否都可返回，对于存在方向相反单向传送带的情况，利用数组标记与双向传送带相邻的房间，代码实现简洁明了。
  - **个人心得**：无
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t,n;char str[300000+100];
  signed main(){
      scanf("%d",&t);
      while(t--){
          scanf("%d",&n);
          scanf("%s",str+1);
          int n1=0,n2=0,n3=0;
          for(int i=1;i<=n;i++)
              if(str[i]=='<')n1++;
              else if(str[i]=='-')n2++;
              else if(str[i]=='>')n3++;
          if(n1==0||n3==0)printf("%d\n",n);
          else{
              vector<bool>can(n,false);
              for(int i=1;i<=n;i++)
                  if(str[i]=='-')
                      can[i-1]=true,can[i%n]=true;
              int cnt=0;
              for(int i=0;i<n;i++)
                  cnt+=can[i];
              printf("%d\n",cnt);
          }
      }
      return 0;
  }
  ```
- **作者：chichichichi（4星）**
  - **关键亮点**：通过细致的分类讨论，清晰地梳理出不同传送带状态下房间的类型及可返回性，逻辑严谨，代码实现符合分类讨论的思路，易于理解。
  - **个人心得**：无
  ```cpp
  #include<cstdio>
  #include<cstring>
  #include<iostream>
  #include<string>
  using namespace std;
  const int maxn=312345;
  int t,n;
  char x[maxn];
  int main(){
      scanf("%d",&t);
      for(int i=1;i<=t;i++)
      {
          scanf("%d",&n);
          scanf("%s",x);
          int m1=0,m2=0;
          int cnt1=0,cnt2=0,cnt3=0;
          int len=strlen(x);
          for(int i=0;i<len;i++)
          {
              if(x[i]=='<')
              m1=1;
              if(x[i]=='>')
              m2=1;
              if(x[i]=='-'||x[(i+1)%len]=='-')
              {
                  cnt1++;
                  continue;
              }
              if(x[i]==x[(i+1)%len]&&x[i]=='>')
              cnt3++;
              
              if(x[i]==x[(i+1)%len]&&x[i]=='<')
              cnt2++;
          }
          if(m1==1&&m2==0)
          {
              cnt1+=cnt2;
          }
          if(m1==0&&m2==1)
          {
              cnt1+=cnt3;
          }
          printf("%d\n",cnt1);
      }
      return 0;
  } 
  ```
- **作者：smallfang（4星）**
  - **关键亮点**：从整体连通性角度思考，对于不同情况的处理思路清晰，在统计双向传送带影响时，通过标志位避免重复统计，代码实现巧妙且简洁。
  - **个人心得**：无
  ```cpp
  #include <iostream>
  #include <cstdio>
  #include <algorithm>
  #include <cmath>
  #include <string>
  #include <cstring>

  using namespace std;

  const int N = 3e5 + 5;

  bool a[N];

  int main()
  {
      ios::sync_with_stdio(false);
      int t;
      cin >> t;
      while (t -- )
      {
          int n;
          cin >> n;
          bool flag = false, flag2 = false, l = false, first = false;
          int res = 0;
          for (int i = 0; i < n; i ++ )
          {
              char op;
              cin >> op;
              if (op == '-')
              {
                  if (i == 0)
                  {
                      first = true;
                  }
                  if (i == n - 1)
                  {
                      res -= first;
                  }
                  if (l == false)
                  {
                      res += 2;
                      l = true;
                  }
                  else
                  {
                      res ++;
                  }
              }
              else if (op == '>')
              {
                  flag = true;
                  l = false;
              }
              else
              {
                  flag2 = true;
                  l = false;
              }
              
          }
          if ((flag xor flag2) == true)
          {
              cout << n << endl;
          }
          else
          {
              cout << res << endl;
          }
      }
      return 0;
  }
  ```

### 最优关键思路或技巧
1. **状态判断**：通过统计不同传送带状态（`<`、`>`、`-`）的数量，快速判断所有房间是否都可返回，如`jun头吉吉`的题解。
2. **标志位处理**：在统计与双向传送带相邻房间时，利用标志位避免重复统计，像`smallfang`的题解中通过`l`、`first`等标志位实现。

### 拓展
同类型题通常围绕路径规划与连通性判断，类似套路是分析不同条件下的可达性，并根据条件进行分类统计。例如给定不同类型的边组成的图，判断从某些点出发能否回到原点等。

### 洛谷相似题目推荐
1. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合判断是否为质数，与本题遍历判断可返回房间类似。
2. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：简单的动态规划，判断不同菜品组合能否达到一定价格，与本题判断不同传送带组合下房间可返回性思路类似。
3. [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过枚举不同包装铅笔购买方案，选择最优解，与本题通过遍历传送带状态判断可返回房间数量思路有相似之处。 

---
处理用时：70.28秒