# 题目信息

# Sport Mafia

## 题目描述

Each evening after the dinner the SIS's students gather together to play the game of Sport Mafia.

For the tournament, Alya puts candies into the box, which will serve as a prize for a winner. To do that, she performs $ n $ actions. The first action performed is to put a single candy into the box. For each of the remaining moves she can choose from two options:

- the first option, in case the box contains at least one candy, is to take exactly one candy out and eat it. This way the number of candies in the box decreased by $ 1 $ ;
- the second option is to put candies in the box. In this case, Alya will put $ 1 $ more candy, than she put in the previous time.

Thus, if the box is empty, then it can only use the second option.

For example, one possible sequence of Alya's actions look as follows:

- put one candy into the box;
- put two candies into the box;
- eat one candy from the box;
- eat one candy from the box;
- put three candies into the box;
- eat one candy from the box;
- put four candies into the box;
- eat one candy from the box;
- put five candies into the box;

This way she will perform $ 9 $ actions, the number of candies at the end will be $ 11 $ , while Alya will eat $ 4 $ candies in total.

You know the total number of actions $ n $ and the number of candies at the end $ k $ . You need to find the total number of sweets Alya ate. That is the number of moves of the first option. It's guaranteed, that for the given $ n $ and $ k $ the answer always exists.

Please note, that during an action of the first option, Alya takes out and eats exactly one candy.

## 说明/提示

In the first example, Alya has made one move only. According to the statement, the first move is always putting one candy in the box. Hence Alya ate $ 0 $ candies.

In the second example the possible sequence of Alya's actions looks as follows:

- put $ 1 $ candy,
- put $ 2 $ candies,
- eat a candy,
- eat a candy,
- put $ 3 $ candies,
- eat a candy,
- put $ 4 $ candies,
- eat a candy,
- put $ 5 $ candies.

This way, she will make exactly $ n=9 $ actions and in the end the box will contain $ 1+2-1-1+3-1+4-1+5=11 $ candies. The answer is $ 4 $ , since she ate $ 4 $ candies in total.

## 样例 #1

### 输入

```
1 1
```

### 输出

```
0```

## 样例 #2

### 输入

```
9 11
```

### 输出

```
4```

## 样例 #3

### 输入

```
5 0
```

### 输出

```
3```

## 样例 #4

### 输入

```
3 2
```

### 输出

```
1```

# AI分析结果

### 题目内容
# 运动黑手党

## 题目描述
每天晚饭后，SIS的学生们聚在一起玩运动黑手党游戏。
为了举办锦标赛，阿利亚会往盒子里放糖果，作为获胜者的奖品。为此，她会进行n次操作。第一次操作是往盒子里放一颗糖果。对于其余的每次操作，她有两种选择：
 - 第一种选择：如果盒子里至少有一颗糖果，那么取出并吃掉恰好一颗糖果。这样盒子里的糖果数量就会减少1颗。
 - 第二种选择：往盒子里放糖果。在这种情况下，阿利亚放入的糖果数量比上一次放的多1颗。
因此，如果盒子是空的，就只能使用第二种选择。
例如，阿利亚的一种可能的操作序列如下：
 - 往盒子里放1颗糖果；
 - 往盒子里放2颗糖果；
 - 从盒子里吃掉1颗糖果；
 - 从盒子里吃掉1颗糖果；
 - 往盒子里放3颗糖果；
 - 从盒子里吃掉1颗糖果；
 - 往盒子里放4颗糖果；
 - 从盒子里吃掉1颗糖果；
 - 往盒子里放5颗糖果；
这样她将进行9次操作，最后盒子里糖果的数量为11颗，而阿利亚总共吃掉了4颗糖果。
已知操作的总次数n和最后盒子里糖果的数量k。需要求出阿利亚吃掉的糖果总数，即第一种操作的次数。题目保证对于给定的n和k，答案总是存在的。
请注意，在第一种操作中，阿利亚取出并吃掉恰好一颗糖果。

## 说明/提示
在第一个示例中，阿利亚只进行了一次操作。根据题目描述，第一次操作总是往盒子里放一颗糖果。因此阿利亚吃了0颗糖果。
在第二个示例中，阿利亚可能的操作序列如下：
 - 放1颗糖果，
 - 放2颗糖果，
 - 吃1颗糖果，
 - 吃1颗糖果，
 - 放3颗糖果，
 - 吃1颗糖果，
 - 放4颗糖果，
 - 吃1颗糖果，
 - 放5颗糖果。
这样，她将恰好进行n = 9次操作，最后盒子里将包含1 + 2 - 1 - 1 + 3 - 1 + 4 - 1 + 5 = 11颗糖果。答案是4，因为她总共吃了4颗糖果。

## 样例 #1
### 输入
```
1 1
```
### 输出
```
0```

## 样例 #2
### 输入
```
9 11
```
### 输出
```
4```

## 样例 #3
### 输入
```
5 0
```
### 输出
```
3```

## 样例 #4
### 输入
```
3 2
```
### 输出
```
1```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕通过建立数学方程求解问题，部分题解采用暴力枚举或二分查找优化。核心是设放入糖果操作次数为变量，根据操作规则和最终糖果数建立方程。难点在于准确建立方程并求解，不同方法在复杂度和实现难度上有差异。

### 所选的题解
- **作者：Lily_White (5星)**
  - **关键亮点**：通过解方程直接得出答案，时间复杂度为O(1)，效率高。
  - **重点代码核心实现思想**：根据题目条件列出方程并化简求解，利用`sqrt`函数计算结果，注意处理大数输出精度。
  ```cpp
  int main()
  {
      long long n, k;
      cin >> n >> k;
      if (n == 1)cout << 0 << endl,exit(0);
      cout << fixed << setprecision(0);
      cout << n - (-3 + round(sqrt(4 * (2 * n + 2 * k) + 9))) / 2 << endl;
      return 0;
  }
  ```
- **作者：Meatherm (4星)**
  - **关键亮点**：采用二分枚举放黄油蛋糕的次数，将时间复杂度降低到O(log2 (n)) 。
  - **重点代码核心实现思想**：二分过程中，根据当前放蛋糕次数计算放入和吃掉蛋糕数，与目标值比较调整二分区间。
  ```cpp
  int main(void){
      scanf("%I64d%I64d",&n,&k);
      if((1+n)*n/2==k){
          printf("0");
          return 0;
      }
      long long l=1,r=n;
      long long sum=0;
      while(l<=r){
          long long mid=(l+r)>>1;
          sum=(1+mid)*(mid)/2;
          if(sum-(n-mid)==k){
              printf("%I64d",n-mid);
              return 0;
          }
          if(sum-(n-mid)>k){
              r=mid-1;
          }
          else l=mid+1;
      }
      return 0;
  }
  ```
- **作者：_SkyLine_ (4星)**
  - **关键亮点**：清晰分析出操作二的次数与最终糖果数的关系，通过解一元二次方程得出答案，逻辑清晰。
  - **重点代码核心实现思想**：设操作二次数为变量列出方程，求解方程并舍去负根，最后输出操作一的次数。
  ```cpp
  int main()
  {
      ios::sync_with_stdio(false);
      cin.tie(0);
      cout.tie(0);
      cin >> n >> k;
      x=(ll)(-3+(ll)(sqrt(1LL*9-1LL*4*(-2*1LL*n-2*1LL*k))))/(2*1LL);
      cout<<(ll)(n-x);
      return 0; 
  }
  ```

### 最优关键思路或技巧
直接建立数学方程求解是最优思路，能达到O(1)的时间复杂度。设放入糖果操作次数为x，根据等差数列求和公式得出放入糖果总数为$\frac{x(x + 1)}{2}$，再结合总操作次数n和最终糖果数k建立方程$\frac{x(x + 1)}{2}-(n - x)=k$，求解方程得出x，进而算出吃掉糖果的次数n - x 。

### 拓展
此类题目属于根据操作规则建立数学模型求解的类型。类似算法套路是遇到有规律的操作和结果要求时，尝试通过设变量，依据规则建立等式关系，再利用数学知识求解。

### 推荐题目
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析日常生活中的时间安排规则建立数学关系求解。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：需要利用斐波那契数列性质建立数学等式求解。
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)：根据题目给定的金币获取规则建立数学模型来计算结果。 

---
处理用时：72.45秒