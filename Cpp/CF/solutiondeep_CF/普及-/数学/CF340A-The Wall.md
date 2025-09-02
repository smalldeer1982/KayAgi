# 题目信息

# The Wall

## 题目描述

Iahub and his friend Floyd have started painting a wall. Iahub is painting the wall red and Floyd is painting it pink. You can consider the wall being made of a very large number of bricks, numbered $ 1 $ , $ 2 $ , $ 3 $ and so on.

Iahub has the following scheme of painting: he skips $ x-1 $ consecutive bricks, then he paints the $ x $ -th one. That is, he'll paint bricks $ x $ , $ 2·x $ , $ 3·x $ and so on red. Similarly, Floyd skips $ y-1 $ consecutive bricks, then he paints the $ y $ -th one. Hence he'll paint bricks $ y $ , $ 2·y $ , $ 3·y $ and so on pink.

After painting the wall all day, the boys observed that some bricks are painted both red and pink. Iahub has a lucky number $ a $ and Floyd has a lucky number $ b $ . Boys wonder how many bricks numbered no less than $ a $ and no greater than $ b $ are painted both red and pink. This is exactly your task: compute and print the answer to the question.

## 说明/提示

Let's look at the bricks from $ a $ to $ b $ $ (a=6,b=18) $ . The bricks colored in red are numbered 6, 8, 10, 12, 14, 16, 18. The bricks colored in pink are numbered 6, 9, 12, 15, 18. The bricks colored in both red and pink are numbered with 6, 12 and 18.

## 样例 #1

### 输入

```
2 3 6 18
```

### 输出

```
3```

# AI分析结果

### 题目内容重写

#### 题目描述

Iahub和他的朋友Floyd开始粉刷一堵墙。Iahub将墙刷成红色，Floyd将墙刷成粉色。你可以认为这堵墙由无数块砖组成，编号为1, 2, 3, 依此类推。

Iahub的粉刷方案如下：他跳过$x-1$块连续的砖，然后粉刷第$x$块。也就是说，他会粉刷编号为$x$, $2x$, $3x$, 依此类推的砖为红色。同样，Floyd跳过$y-1$块连续的砖，然后粉刷第$y$块。因此，他会粉刷编号为$y$, $2y$, $3y$, 依此类推的砖为粉色。

经过一整天的粉刷，男孩们发现有些砖被同时刷成了红色和粉色。Iahub有一个幸运数字$a$，Floyd有一个幸运数字$b$。男孩们想知道，编号不小于$a$且不大于$b$的砖中有多少块被同时刷成了红色和粉色。这正是你的任务：计算并打印出这个问题的答案。

#### 说明/提示

让我们看一下从$a$到$b$的砖（$a=6$, $b=18$）。被刷成红色的砖编号为6, 8, 10, 12, 14, 16, 18。被刷成粉色的砖编号为6, 9, 12, 15, 18。被同时刷成红色和粉色的砖编号为6, 12和18。

#### 样例 #1

##### 输入

```
2 3 6 18
```

##### 输出

```
3
```

### 题解分析与结论

#### 综合分析

这道题的核心是求在区间$[a, b]$内，同时是$x$和$y$的倍数的砖的数量。由于$x$和$y$的倍数关系可以通过它们的最小公倍数（LCM）来表示，因此问题转化为求区间$[a, b]$内LCM的倍数的数量。

大多数题解都采用了以下思路：
1. 计算$x$和$y$的最大公约数（GCD）。
2. 通过公式$LCM(x, y) = \frac{x \times y}{GCD(x, y)}$计算最小公倍数。
3. 计算区间$[a, b]$内LCM的倍数的数量，通常通过$\left\lfloor \frac{b}{LCM} \right\rfloor - \left\lfloor \frac{a-1}{LCM} \right\rfloor$得到。

#### 最优关键思路

1. **GCD与LCM的关系**：利用$LCM(x, y) = \frac{x \times y}{GCD(x, y)}$，将问题转化为求GCD和LCM。
2. **区间计数**：通过$\left\lfloor \frac{b}{LCM} \right\rfloor - \left\lfloor \frac{a-1}{LCM} \right\rfloor$计算区间内LCM的倍数的数量，避免了暴力枚举，提高了效率。

#### 推荐题解

1. **作者：Quit**（评分：4星）
   - **关键亮点**：详细解释了GCD和LCM的计算方法，并提供了完整的代码实现。代码简洁且易于理解。
   - **代码片段**：
     ```cpp
     ll gcd(ll x,ll y){ 
         if(x%y==0) return y;
         return gcd(y,x%y);
     }
     int main(){
         ll x,y,a,b,l,r;
         cin>>x>>y>>a>>b;
         ll lcm=x*y/gcd(x,y);
         if(a%lcm==0) l=a/lcm;
         else l=a/lcm+1;
         r=b/lcm;    
         cout<<r-l+1<<endl;
         return 0;
     }
     ```

2. **作者：BetaCutS**（评分：4星）
   - **关键亮点**：使用了容斥原理来解释区间计数的公式，思路清晰，代码简洁。
   - **代码片段**：
     ```cpp
     signed main()
     {
         int x=read(),y=read(),a=read(),b=read(),z=x*y/__gcd(x,y);
         printf("%d",b/z-(a-1)/z);
         return 0;
     }
     ```

3. **作者：Qerucy**（评分：4星）
   - **关键亮点**：代码简洁，直接使用了GCD和LCM的公式，并使用了`long long`来避免溢出问题。
   - **代码片段**：
     ```cpp
     int gcd(int x,int y){return !(x%y)?y:gcd(y,x%y);}
     int lcm(int x,int y){return x*y/gcd(x,y);}
     signed main(){
         scanf("%lld%lld%lld%lld",&x,&y,&a,&b);
         printf("%lld",b/lcm(x,y)-a/lcm(x,y)+1);
         return 0;
     }
     ```

#### 拓展思路与推荐题目

- **拓展思路**：类似的问题可以通过转化为GCD和LCM来解决，例如求多个数的最小公倍数或最大公约数。
- **推荐题目**：
  1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
  2. [P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)
  3. [P1888 最大公约数和最小公倍数](https://www.luogu.com.cn/problem/P1888)

#### 个人心得摘录

- **Quit**：强调了使用`long long`来避免溢出问题，并提醒了暴力枚举会超时。
- **BetaCutS**：通过容斥原理简化了区间计数的公式，使得代码更加简洁。
- **Qerucy**：直接使用了GCD和LCM的公式，代码简洁且易于理解。

### 结论

这道题的核心在于理解GCD和LCM的关系，并通过数学公式将问题转化为简单的区间计数问题。推荐的题解都提供了清晰的思路和简洁的代码实现，适合学习和参考。

---
处理用时：43.29秒