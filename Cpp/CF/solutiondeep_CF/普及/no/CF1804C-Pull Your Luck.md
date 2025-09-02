# 题目信息

# Pull Your Luck

## 题目描述

While James is gone on business, Vesper takes her time and explores what the legendary Casino Royale has to offer to people who are fond of competitive programming.

Her attention was grabbed by the very new "Pull Your Luck" roulette which functions in a pretty peculiar way. The roulette's wheel consists of $ n $ sectors number from $ 0 $ to $ n - 1 $ . There is no ball and the winning sector is determined by a static arrow pointing to one of the sectors. Sectors' indexes go in the natural order and the wheel always spins in the direction of indexes increment. That means that sector $ i + 1 $ goes right after sector $ i $ for all $ i $ from $ 0 $ to $ n - 2 $ , and sector $ 0 $ goes right after sector $ n - 1 $ .

After a bet is made, the player is allowed to pull the triggering handle herself and cause the wheel to spin. If the player's initial pull is made with the force equal to positive integer $ f $ , the wheel will spin for $ f $ seconds. During the first second it will advance $ f $ sectors, the next second it will advance $ f - 1 $ sectors, then $ f - 2 $ sectors, and so on until it comes to a complete stop. After the wheel comes to a complete stop, the sector which the arrow is pointing to is the winning one.

The roulette's arrow currently points at sector $ x $ . Vesper knows that she can pull the handle with any integer force from $ 1 $ to $ p $ inclusive. Note that it is not allowed to pull the handle with force $ 0 $ , i. e. not pull it all. The biggest prize is awarded if the winning sector is $ 0 $ . Now Vesper wonders if she can make sector $ 0 $ win by pulling the triggering handle exactly once?

## 说明/提示

In the first example, the only possible way to pull the handle is with force $ 1 $ . That is not enough to make the arrow point at sector $ 0 $ , at least force $ 2 $ is required to do so.

In the second example, Vesper can pull the handle with the force $ 2 $ so the wheel will spin $ 2 + 1 = 3 $ sectors ahead and the arrow will point at sector $ 0 $ .

In the third example, Vesper can pull the handle with the force $ 4 $ so the wheel will spin $ 4 + 3 + 2 + 1 = 10 $ sectors and will point at sector $ 0 $ again.

In the fourth example, Vesper can pull the handle with the force $ 5 $ so the wheel will spin $ 5 + 4 + 3 + 2 + 1 = 15 $ sectors. That will make the wheel make one full turn plus $ 4 $ more sectors.

In the fifth example, whatever force Vesper chooses to pull the handle with, she can only make sectors $ 1 $ and $ 2 $ win.

## 样例 #1

### 输入

```
7
5 2 1
5 2 2
10 0 100
11 7 100
3 1 1000
31 0 10
100 49 7```

### 输出

```
No
Yes
Yes
Yes
No
No
No```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

当詹姆斯出差时，Vesper 趁机探索了传说中的 Casino Royale，看看它对那些喜欢竞争性编程的人有什么吸引力。

她的注意力被一个非常新的“Pull Your Luck”轮盘吸引了，它的运作方式非常奇特。轮盘的轮子由 $n$ 个扇区组成，编号从 $0$ 到 $n - 1$。轮盘没有球，获胜的扇区由一个静态的箭头指向其中一个扇区。扇区的索引按自然顺序排列，轮盘总是按索引递增的方向旋转。这意味着对于所有 $i$ 从 $0$ 到 $n - 2$，扇区 $i + 1$ 紧接在扇区 $i$ 之后，而扇区 $0$ 紧接在扇区 $n - 1$ 之后。

在下注后，玩家可以自己拉动触发手柄，使轮盘旋转。如果玩家初始拉动的力等于正整数 $f$，轮盘将旋转 $f$ 秒。在第一秒，它将前进 $f$ 个扇区，下一秒前进 $f - 1$ 个扇区，然后是 $f - 2$ 个扇区，依此类推，直到完全停止。轮盘完全停止后，箭头指向的扇区就是获胜的扇区。

轮盘的箭头当前指向扇区 $x$。Vesper 知道她可以用从 $1$ 到 $p$ 之间的任何整数力拉动手柄。注意，不允许用 $0$ 的力拉动手柄，即完全不拉动。最大的奖品是在获胜扇区为 $0$ 时颁发。现在 Vesper 想知道，她是否可以通过拉动触发手柄恰好一次，使扇区 $0$ 获胜？

#### 说明/提示

在第一个示例中，唯一可能的拉动方式是用力 $1$。这不足以使箭头指向扇区 $0$，至少需要用力 $2$ 才能做到。

在第二个示例中，Vesper 可以用力 $2$ 拉动手柄，使轮盘旋转 $2 + 1 = 3$ 个扇区，箭头将指向扇区 $0$。

在第三个示例中，Vesper 可以用力 $4$ 拉动手柄，使轮盘旋转 $4 + 3 + 2 + 1 = 10$ 个扇区，箭头将再次指向扇区 $0$。

在第四个示例中，Vesper 可以用力 $5$ 拉动手柄，使轮盘旋转 $5 + 4 + 3 + 2 + 1 = 15$ 个扇区。这将使轮盘旋转一整圈，再加上 $4$ 个扇区。

在第五个示例中，无论 Vesper 选择用什么力拉动手柄，她只能使扇区 $1$ 和 $2$ 获胜。

#### 样例 #1

##### 输入

```
7
5 2 1
5 2 2
10 0 100
11 7 100
3 1 1000
31 0 10
100 49 7
```

##### 输出

```
No
Yes
Yes
Yes
No
No
No
```

### 算法分类
数学

### 题解分析与结论

本题的核心是通过数学推导找到轮盘旋转后指向扇区 $0$ 的条件。由于轮盘的旋转方式是一个等差数列的求和问题，因此可以通过数学公式来简化计算。

#### 关键思路
1. **等差数列求和**：轮盘旋转的总扇区数可以通过等差数列求和公式计算，即 $S = \frac{f(f+1)}{2}$。
2. **模运算**：由于轮盘是循环的，最终指向的扇区可以通过 $(x + S) \bmod n$ 计算。
3. **循环节**：当 $f = 2n$ 时，$S$ 是 $n$ 的倍数，因此轮盘的指向会回到初始位置。因此，只需要枚举 $f$ 从 $1$ 到 $\min(2n, p)$ 即可。

#### 评分较高的题解

1. **LOVE_Ynoi (5星)**
   - **关键亮点**：通过数学推导发现当 $f = 2n$ 时，轮盘的指向会回到初始位置，从而将枚举范围缩小到 $\min(2n, p)$，时间复杂度为 $O(n)$。
   - **代码实现**：
     ```cpp
     void solve(){
         cin>>n>>k>>w;
         int t = 0;
         for(int i = 1;i<=min(2 * n,w);i++){
             t += i;
             if((k + t) % n == 0){
                 cout<<"YES"<<endl;
                 return;
             } 
         }
         cout<<"NO"<<endl;
     }
     ```

2. **Withershine (4星)**
   - **关键亮点**：通过高斯求和公式简化计算，并进一步推导出 $p$ 的上界为 $2n$，避免了不必要的枚举。
   - **代码实现**：
     ```cpp
     fr(i , 1 , min(p , 2 * n - x)){
         ll now = (1 + i) * i / 2;
         if((x + now) % n == 0){
             cout << "Yes" << '\n'; 
             flag = 1;
             break;
         }
     }
     ```

3. **_GJM_ (4星)**
   - **关键亮点**：通过观察发现当 $f = 2n$ 时，轮盘的指向会回到初始位置，从而将枚举范围缩小到 $\min(2n, p)$。
   - **代码实现**：
     ```cpp
     for(long long i=1;i<=min(2*n,p);i++){
         if(((i+1)*i/2)%n==(n-x)%n){
             cout << "Yes\n";
             flag=1;
             break;
         }
     }
     ```

### 最优关键思路或技巧
通过数学推导发现当 $f = 2n$ 时，轮盘的指向会回到初始位置，从而将枚举范围缩小到 $\min(2n, p)$，时间复杂度为 $O(n)$。

### 可拓展之处
类似的问题可以通过数学推导找到循环节或周期性，从而减少不必要的计算。例如，在模运算中，周期性是一个常见的优化点。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

---
处理用时：46.88秒