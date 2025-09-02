# 题目信息

# Russian Roulette

## 题目描述

After all the events in Orlando we all know, Sasha and Roma decided to find out who is still the team's biggest loser. Thankfully, Masha found somewhere a revolver with a rotating cylinder of $ n $ bullet slots able to contain exactly $ k $ bullets, now the boys have a chance to resolve the problem once and for all.

Sasha selects any $ k $ out of $ n $ slots he wishes and puts bullets there. Roma spins the cylinder so that every of $ n $ possible cylinder's shifts is equiprobable. Then the game starts, the players take turns, Sasha starts: he puts the gun to his head and shoots. If there was no bullet in front of the trigger, the cylinder shifts by one position and the weapon is given to Roma for make the same move. The game continues until someone is shot, the survivor is the winner.

Sasha does not want to lose, so he must choose slots for bullets in such a way as to minimize the probability of its own loss. Of all the possible variant he wants to select the lexicographically minimal one, where an empty slot is lexicographically less than a charged one.

More formally, the cylinder of $ n $ bullet slots able to contain $ k $ bullets can be represented as a string of $ n $ characters. Exactly $ k $ of them are "X" (charged slots) and the others are "." (uncharged slots).

Let us describe the process of a shot. Suppose that the trigger is in front of the first character of the string (the first slot). If a shot doesn't kill anyone and the cylinder shifts, then the string shifts left. So the first character becomes the last one, the second character becomes the first one, and so on. But the trigger doesn't move. It will be in front of the first character of the resulting string.

Among all the strings that give the minimal probability of loss, Sasha choose the lexicographically minimal one. According to this very string, he charges the gun. You have to help Sasha to charge the gun. For that, each $ x_{i} $ query must be answered: is there a bullet in the positions $ x_{i} $ ?

## 说明/提示

The lexicographical comparison of is performed by the < operator in modern programming languages. The $ a $ string is lexicographically less that the $ b $ string, if there exists such $ i $ ( $ 1<=i<=n $ ), that $ a_{i}&lt;b_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ a_{j}=b_{j} $ .

## 样例 #1

### 输入

```
3 1 3
1
2
3
```

### 输出

```
..X```

## 样例 #2

### 输入

```
6 3 6
1
2
3
4
5
6
```

### 输出

```
.X.X.X```

## 样例 #3

### 输入

```
5 2 5
1
2
3
4
5
```

### 输出

```
...XX```

# AI分析结果

### 题目内容
# 俄罗斯轮盘赌

## 题目描述
在奥兰多发生的所有事件之后，我们都知道，萨沙和罗曼决定弄清楚谁仍然是团队中最大的失败者。幸运的是，玛莎在某个地方找到了一把左轮手枪，其旋转弹膛有$n$个子弹槽，恰好能容纳$k$发子弹，现在男孩们有机会一劳永逸地解决这个问题。

萨沙从$n$个槽中选择任意$k$个他想要的槽，并在那里装上子弹。罗曼旋转弹膛，使得$n$种可能的弹膛转动位置中的每一种出现的概率相等。然后游戏开始，玩家轮流进行，萨沙先开始：他将枪对准自己的头并开枪。如果扳机前没有子弹，弹膛就移动一个位置，然后武器交给罗曼进行同样的操作。游戏继续进行，直到有人中枪，幸存者就是赢家。

萨沙不想输，所以他必须选择装子弹的槽，以使自己失败的概率最小。在所有可能的方案中，他想选择字典序最小的那个，其中空槽在字典序上小于装弹的槽。

更正式地说，能容纳$k$发子弹的$n$个子弹槽的弹膛可以表示为一个由$n$个字符组成的字符串。其中恰好有$k$个是“X”（装弹的槽），其他的是“.”（未装弹的槽）。

让我们描述一下开枪的过程。假设扳机在字符串的第一个字符（第一个槽）前面。如果开枪没有打死任何人并且弹膛移动，那么字符串向左移动。所以第一个字符变成最后一个字符，第二个字符变成第一个字符，依此类推。但是扳机不会移动。它将在结果字符串的第一个字符前面。

在所有能使失败概率最小的字符串中，萨沙选择字典序最小的那个。根据这个字符串，他给枪装弹。你必须帮助萨沙给枪装弹。为此，对于每个$x_{i}$查询，都必须回答：位置$x_{i}$处有子弹吗？

## 说明/提示
字典序比较是通过现代编程语言中的<运算符执行的。如果存在这样的$i$（$1 \leq i \leq n$），使得$a_{i} < b_{i}$，并且对于任何$j$（$1 \leq j < i$），$a_{j} = b_{j}$，则字符串$a$在字典序上小于字符串$b$。

## 样例 #1
### 输入
```
3 1 3
1
2
3
```
### 输出
```
..X
```

## 样例 #2
### 输入
```
6 3 6
1
2
3
4
5
6
```
### 输出
```
.X.X.X
```

## 样例 #3
### 输入
```
5 2 5
1
2
3
4
5
```
### 输出
```
...XX
```

### 算法分类
贪心

### 题解综合分析与结论
三道题解都围绕如何让先开枪者萨沙失败概率最小且字典序最小来解决问题。
 - **smyslenny题解**：通过分析得出三个性质，基于弹槽数奇偶及子弹数与弹槽数一半的关系分类讨论。奇数时先转化为偶数情况，子弹数大于弹槽数一半筛去偶数位计算，子弹数小于等于弹槽数一半筛去奇数位计算。代码实现围绕check函数判断位置是否有子弹。
 - **_Violet_Evergarden题解**：思路是让“.”后接“X”使概率最大，奇数时调整放置方式保证字典序最小，不预处理直接询问时输出答案。代码通过对$n$奇偶、询问位置奇偶及子弹数量关系判断输出。
 - **wind_whisper题解**：通过观察样例发现从后往前隔一个放子弹是好方案，特殊情况调整子弹位置使字典序更小，根据$2k$与$n$关系及$(n - 2k)$奇偶等分类处理询问。

三道题解中，smyslenny题解思路清晰，先总结性质再分类讨论，代码注释详细，可读性高；_Violet_Evergarden题解思路表述稍简略，代码实现简洁但逻辑稍难理解；wind_whisper题解对特殊情况分析较细致，但代码可读性一般。综合考虑，smyslenny题解质量最高。

### 所选的题解
 - **smyslenny题解** - 星级：5星
    - **关键亮点**：先提炼出关键性质，再根据子弹数与弹槽数关系详细分类讨论，逻辑清晰，代码注释丰富，可读性强。
    - **重点代码**：
```c
bool check(int x,int n,int k)
{
    if(n&1) { 
        if(x==n && k) 
            return true;
        n--;
        k--; 
    }
    if(k-n/2>0)
    {
        if(x%2==0) 
            return true;
        k-=n/2;
        x=x/2+1;
        k=n/2-k;
        if(x>k) return true;
        return false;
    }
    else
    {
        if(x&1) return false;
        x=x/2;
        k=n/2-k;
        if(x>k) return true;
        return false;
    }
}
```
核心实现思想：根据弹槽数奇偶及子弹数与弹槽数一半关系，判断查询位置是否有子弹。奇数时先处理最后一位，再根据子弹数与弹槽数一半关系，对偶数或奇数位置分别判断。

### 最优关键思路或技巧
通过分析题目性质，利用贪心策略，根据子弹数与弹槽数的数量关系进行分类讨论，确定子弹放置规律，从而解决问题。

### 可拓展思路
此类题目属于概率与贪心结合问题，类似套路是先分析使目标概率最优的放置规律，再考虑字典序等附加条件。同类型题可考虑其他概率场景下的物品放置优化问题。

### 推荐洛谷题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248) 

---
处理用时：60.65秒