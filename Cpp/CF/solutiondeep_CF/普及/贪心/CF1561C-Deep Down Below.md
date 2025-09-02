# 题目信息

# Deep Down Below

## 题目描述

In a certain video game, the player controls a hero characterized by a single integer value: power. The hero will have to beat monsters that are also characterized by a single integer value: armor.

On the current level, the hero is facing $ n $ caves. To pass the level, the hero must enter all the caves in some order, each cave exactly once, and exit every cave safe and sound. When the hero enters cave $ i $ , he will have to fight $ k_i $ monsters in a row: first a monster with armor $ a_{i, 1} $ , then a monster with armor $ a_{i, 2} $ and so on, finally, a monster with armor $ a_{i, k_i} $ .

The hero can beat a monster if and only if the hero's power is strictly greater than the monster's armor. If the hero can't beat the monster he's fighting, the game ends and the player loses. Note that once the hero enters a cave, he can't exit it before he fights all the monsters in it, strictly in the given order.

Each time the hero beats a monster, the hero's power increases by $ 1 $ .

Find the smallest possible power the hero must start the level with to be able to enter all the caves in some order and beat all the monsters.

## 说明/提示

In the first test case, the hero has to beat a single monster with armor $ 42 $ , it's enough to have power $ 43 $ to achieve that.

In the second test case, the hero can pass the level with initial power $ 13 $ as follows:

- enter cave $ 2 $ : 
  - beat a monster with armor $ 12 $ , power increases to $ 14 $ ;
  - beat a monster with armor $ 11 $ , power increases to $ 15 $ ;
- enter cave $ 1 $ : 
  - beat a monster with armor $ 10 $ , power increases to $ 16 $ ;
  - beat a monster with armor $ 15 $ , power increases to $ 17 $ ;
  - beat a monster with armor $ 8 $ , power increases to $ 18 $ .

## 样例 #1

### 输入

```
2
1
1 42
2
3 10 15 8
2 12 11```

### 输出

```
43
13```

# AI分析结果

### 题目内容重写（中文）

在某个游戏中，玩家控制一个英雄，英雄有一个整数属性：力量（power）。英雄需要击败怪物，每个怪物也有一个整数属性：护甲（armor）。

在当前关卡中，英雄面对 $n$ 个洞穴。要通关，英雄必须按某种顺序进入所有洞穴，每个洞穴恰好一次，并且安全地离开每个洞穴。当英雄进入第 $i$ 个洞穴时，他需要连续击败 $k_i$ 个怪物：首先是护甲为 $a_{i,1}$ 的怪物，然后是护甲为 $a_{i,2}$ 的怪物，依此类推，最后是护甲为 $a_{i,k_i}$ 的怪物。

英雄能够击败一个怪物，当且仅当英雄的力量严格大于怪物的护甲。如果英雄无法击败他正在战斗的怪物，游戏结束，玩家失败。注意，一旦英雄进入一个洞穴，他必须按照给定的顺序击败所有怪物，不能提前退出。

每次英雄击败一个怪物，他的力量会增加 $1$。

请找出英雄通关所有洞穴所需的最小初始力量。

### 说明/提示

在第一个测试用例中，英雄需要击败一个护甲为 $42$ 的怪物，初始力量为 $43$ 即可。

在第二个测试用例中，英雄可以以初始力量 $13$ 通关，具体如下：

- 进入洞穴 $2$：
  - 击败护甲为 $12$ 的怪物，力量增加到 $14$；
  - 击败护甲为 $11$ 的怪物，力量增加到 $15$；
- 进入洞穴 $1$：
  - 击败护甲为 $10$ 的怪物，力量增加到 $16$；
  - 击败护甲为 $15$ 的怪物，力量增加到 $17$；
  - 击败护甲为 $8$ 的怪物，力量增加到 $18$。

### 样例 #1

#### 输入

```
2
1
1 42
2
3 10 15 8
2 12 11
```

#### 输出

```
43
13
```

---

### 题解综合分析与结论

本题的核心在于如何确定英雄进入每个洞穴所需的最小初始力量，并找到最优的洞穴进入顺序，使得英雄能够以最小的初始力量通关所有洞穴。各题解的主要思路如下：

1. **预处理每个洞穴的最小初始力量**：通过遍历每个洞穴中的怪物，计算进入该洞穴所需的最小初始力量。
2. **贪心策略**：将洞穴按照所需的最小初始力量从小到大排序，依次进入洞穴，并在力量不足时补充初始力量。
3. **二分查找优化**：部分题解使用二分查找来优化初始力量的确定过程。

### 评分较高的题解

#### 题解1：作者：sunzz3183 (赞：8)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，预处理和贪心策略结合得很好，时间复杂度较低。
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;i++){
      q[i]=i;
      scanf("%d",&k[i]);
      int a,num;
      scanf("%d",&a);
      d[i]=num=a+1;
      for(int j=2;j<=k[i];j++){
          num++;
          scanf("%d",&a);
          if(a>=num){
              int t=num;
              num=a+1;
              d[i]+=(num-t);
          }
      }
  }
  sort(q+1,q+n+1,cmp);
  sum=ans=d[q[1]];
  for(int i=2;i<=n;i++){
      sum+=k[q[i-1]];
      if(sum<d[q[i]])
          ans+=(d[q[i]]-sum),sum+=(d[q[i]]-sum);
  }
  ```

#### 题解2：作者：LinkZelda (赞：4)
- **星级**：4星
- **关键亮点**：使用二分查找优化初始力量的确定，思路清晰，代码可读性较好。
- **核心代码**：
  ```cpp
  bool check(int val,int id){
      for(int i=0;i<(int)v[id].size();i++){
          int x=v[id][i];
          if(val>x)val++;
          else return 0;
      }
      return 1;
  }
  ```

#### 题解3：作者：KSToki (赞：2)
- **星级**：4星
- **关键亮点**：贪心策略清晰，代码简洁，预处理和排序结合得很好。
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;i++){
      b[i].k=read();
      b[i].a=0;
      for(int j=0;j<b[i].k;j++){
          x=read();
          chkmax(b[i].a,x-j);
      }
  }
  sort(b+1,b+n+1,cmp);
  int ans=0,now=0;
  for(int i=1;i<=n;i++){
      if(now<=b[i].a){
          ans+=b[i].a+1-now;
          now=b[i].a+1;
      }
      now+=b[i].k;
  }
  ```

### 最优关键思路与技巧

1. **预处理每个洞穴的最小初始力量**：通过遍历每个洞穴中的怪物，计算进入该洞穴所需的最小初始力量。
2. **贪心策略**：将洞穴按照所需的最小初始力量从小到大排序，依次进入洞穴，并在力量不足时补充初始力量。
3. **二分查找优化**：使用二分查找来优化初始力量的确定过程，减少时间复杂度。

### 可拓展之处

本题的贪心策略和预处理技巧可以应用于类似的资源分配问题，例如任务调度、背包问题等。通过预处理和排序，可以有效地优化问题的解决过程。

### 推荐题目

1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

### 个人心得摘录

- **sunzz3183**：通过预处理和贪心策略的结合，能够有效地减少问题的复杂度，代码简洁且易于理解。
- **LinkZelda**：二分查找的引入使得初始力量的确定更加高效，代码可读性较好，适合初学者学习。
- **KSToki**：贪心策略清晰，代码简洁，预处理和排序结合得很好，适合用于类似的资源分配问题。

---
处理用时：46.99秒