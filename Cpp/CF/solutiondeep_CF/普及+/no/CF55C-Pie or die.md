# 题目信息

# Pie or die

## 题目描述

Volodya and Vlad play the following game. There are $ k $ pies at the cells of $ n×m $ board. Each turn Volodya moves one pie to the neighbouring (by side) cell. If the pie lies at the border of the board then Volodya can move it outside the board, get the pie and win. After Volodya's move, Vlad bans some edge at the border of the board of length 1 (between two knots of the board) so that Volodya is not able to move the pie outside the board through this edge anymore. The question is: will Volodya win this game? We suppose both players follow the optimal strategy.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF55C/31b302de1bb09a87c0444ab4f4b5165ba7e60f5d.png)

## 样例 #1

### 输入

```
2 2 1
1 2
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 4 0
```

### 输出

```
NO```

## 样例 #3

### 输入

```
100 50 2
50 25
50 25
```

### 输出

```
NO```

# AI分析结果

### 题目内容
# 要么得派，要么失败

## 题目描述
沃洛佳（Volodya）和弗拉德（Vlad）玩以下游戏。在一个 \(n×m\) 的棋盘格子上有 \(k\) 个派。每一轮，沃洛佳将一个派移动到相邻（边相邻）的格子。如果派位于棋盘的边界，那么沃洛佳可以将它移出棋盘，得到这个派并获胜。在沃洛佳移动之后，弗拉德禁止棋盘边界上长度为1的某条边（棋盘节点之间的边），这样沃洛佳就不能再通过这条边将派移出棋盘。问题是：沃洛佳能赢得这个游戏吗？我们假设双方都遵循最优策略。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF55C/31b302de1bb09a87c0444ab4f4b5165ba7e60f5d.png)

## 样例 #1
### 输入
```
2 2 1
1 2
```
### 输出
```
YES```

## 样例 #2
### 输入
```
3 4 0
```
### 输出
```
NO```

## 样例 #3
### 输入
```
100 50 2
50 25
50 25
```
### 输出
```
NO```

### 算法分类
数学（博弈论）

### 题解综合分析与结论
所有题解思路核心一致，均围绕博弈论展开。要点在于明确若派到达角落且两个出口未被挡住则先手（沃洛佳）胜，后手（弗拉德）会在派到达边界前尽量封堵角落，由于棋盘最多四个角落，后手封堵四个角落需四步，所以先手若能在四步内将派移动到边界就能获胜，即判断派到边界的距离是否小于等于4。各题解在思路清晰度和代码简洁度上有所差异。

### 所选的题解
- **作者：WinterRain208（5星）**
  - **关键亮点**：思路阐述清晰，先点明题目是博弈论类型，再逐步分析游戏中的关键事实，如边缘派、角落派的处理等，最后给出简洁代码。
  - **个人心得**：遇到此类题可拿样例找规律或纸笔分析。
  ```cpp
  #include<bits/stdc++.h>
  #define F(i,j,r) for(int i=j;i<=r;++i)

  using namespace std;

  int n,m,k;
  int x,y,flag=1;
  int main(){
      scanf("%d%d%d",&n,&m,&k);
      F(i,1,k){
          scanf("%d%d",&x,&y);
          if(x-1<=4||y-1<=4||4>=n-x||4>=m-y)
              flag=0;
      }
      puts(flag?"NO":"YES");
      return 0;
  }
  ```
  - **核心代码实现思想**：遍历每个派的坐标，通过判断派到棋盘四条边界的距离是否小于等于4 ，来确定先手是否能获胜，最后根据标志变量 `flag` 输出结果。
- **作者：abensyl（4星）**
  - **关键亮点**：结合图示说明派在角落且两边未被堵时先手获胜的情况，思路清晰，代码简洁明了，在判断出先手获胜时直接结束程序节省时间。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,m,k,x,y;
  bool flag;
  int main(){
      scanf("%d%d%d",&n,&m,&k);
      for(int i=1;i<=k;i++){
          scanf("%d%d",&x,&y);
          if(x-1<=4||y-1<=4||4>=n-x||4>=m-y){
              flag=0;
              puts("YES");
              return 0;
          }
      }
      puts("NO");
      return 0;
  }
  ```
  - **核心代码实现思想**：循环读入每个派的坐标，判断其到边界距离是否满足获胜条件，若满足则输出 “YES” 并结束程序，否则继续循环，若所有派都不满足则输出 “NO”。
- **作者：COsm0s（4星）**
  - **关键亮点**：从关键信息出发，将题目转化为后手需在棋子到达边界前让四个角落都至少有一块挡板的条件，逻辑推导清晰，代码规范且有自定义输入输出函数。
  ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  typedef long long ll;
  inline ll read(){
      ll x = 0, m = 1;
      char ch = getchar();
      while(!isdigit(ch)){
          if(ch == '-') m = -1;
          ch = getchar();
      }
      while(isdigit(ch)){
          x = (x << 1) + (x << 3) + (ch ^ 48);
          ch = getchar();
      }
      return x * m;
  }
  inline void write(ll x){
      if(x < 0){
          putchar('-');
          write(-x);
          return;
      }
      if(x >= 10) write(x / 10);
      putchar(x % 10 + '0');
  }   
  signed main(){
      int n = read(), m = read(), k = read();
      while(k --) {
          int x = read(), y = read();
          if(x < 6 || y < 6 || n - x < 5 || m - y < 5) 
              puts("YES"), exit(0);
      }
      puts("NO");
      return 0;
  }
  ```
  - **核心代码实现思想**：通过自定义输入函数读入棋盘参数和派的坐标，判断派到边界的距离，若满足条件则输出 “YES” 并结束程序，否则循环结束后输出 “NO”。

### 最优关键思路或技巧
利用博弈论思维，抓住角落位置对于先手获胜的关键作用，将问题转化为判断先手能否在有限步数（后手封堵四个角落所需步数）内将派移动到边界，通过简单的坐标距离计算来解决问题。

### 可拓展之处
此类博弈论题目关键在于分析双方最优策略下的必胜条件，类似套路如分析双方操作对局面的影响、寻找关键位置或步数限制等。同类型题通常围绕两人博弈展开，可通过改变棋盘形状、棋子移动规则、获胜条件等拓展。

### 洛谷相似题目推荐
- [P1288 取数游戏II](https://www.luogu.com.cn/problem/P1288)
- [P2197 模板 - Nim游戏](https://www.luogu.com.cn/problem/P2197)
- [P2252 取石子游戏](https://www.luogu.com.cn/problem/P2252) 

---
处理用时：78.73秒