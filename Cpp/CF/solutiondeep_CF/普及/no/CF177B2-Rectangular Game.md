# 题目信息

# Rectangular Game

## 题目描述

The Smart Beaver from ABBYY decided to have a day off. But doing nothing the whole day turned out to be too boring, and he decided to play a game with pebbles. Initially, the Beaver has $ n $ pebbles. He arranges them in $ a $ equal rows, each row has $ b $ pebbles ( $ a>1 $ ). Note that the Beaver must use all the pebbles he has, i. e. $ n=a·b $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF177B2/72b3400d0a6aa691e5c49fe273a750815ff16b58.png) 10 pebbles are arranged in two rows, each row has 5 pebbles Once the Smart Beaver has arranged the pebbles, he takes back any of the resulting rows (that is, $ b $ pebbles) and discards all other pebbles. Then he arranges all his pebbles again (possibly choosing other values of $ a $ and $ b $ ) and takes back one row, and so on. The game continues until at some point the Beaver ends up with exactly one pebble.

The game process can be represented as a finite sequence of integers $ c_{1},...,c_{k} $ , where:

- $ c_{1}=n $
- $ c_{i+1} $ is the number of pebbles that the Beaver ends up with after the $ i $ -th move, that is, the number of pebbles in a row after some arrangement of $ c_{i} $ pebbles ( $ 1<=i<k $ ). Note that $ c_{i}>c_{i+1} $ .
- $ c_{k}=1 $

The result of the game is the sum of numbers $ c_{i} $ . You are given $ n $ . Find the maximum possible result of the game.

## 说明/提示

Consider the first example ( $ c_{1}=10 $ ). The possible options for the game development are:

- Arrange the pebbles in 10 rows, one pebble per row. Then $ c_{2}=1 $ , and the game ends after the first move with the result of 11.
- Arrange the pebbles in 5 rows, two pebbles per row. Then $ c_{2}=2 $ , and the game continues. During the second move we have two pebbles which can be arranged in a unique way (remember that you are not allowed to put all the pebbles in the same row!) — 2 rows, one pebble per row. $ c_{3}=1 $ , and the game ends with the result of 13.
- Finally, arrange the pebbles in two rows, five pebbles per row. The same logic leads us to $ c_{2}=5,c_{3}=1 $ , and the game ends with the result of 16 — the maximum possible result.

## 样例 #1

### 输入

```
10
```

### 输出

```
16
```

## 样例 #2

### 输入

```
8
```

### 输出

```
15
```

# AI分析结果



【题目翻译】
# 矩形游戏

## 题目描述

聪明的海狸决定休息一天。他将$n$个鹅卵石排列成$a$行$b$列的矩形（$a>1$），每次操作后取走其中一行（$b$个），重复操作直至剩下1个石子。求所有操作中剩余石子数的最大总和。

## 样例 #1

### 输入
10

### 输出
16

【算法分类】
贪心

【题解对比与结论】
各题解核心思路一致：贪心策略下，每次分解取最小质因数使剩余石子最大化。正确实现需处理质数情况，在最后一步加上1。部分题解未正确处理质数导致错误。

【优质题解推荐】
1. zhangyuanxiao（★★★★★）
- 亮点：数学证明贪心策略正确性，代码处理质数边界清晰。
- 代码核心：
```cpp
while(n!=1){
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            n /= i;
            ans += n;
            break;
        }
    }
    if(!flag) n=1,ans+=1; // 处理质数情况
}
```

2. yanxingyu0910（★★★★☆）
- 亮点：代码简洁，循环外补1的写法巧妙。
- 代码核心：
```cpp
while(n>1){
    for(i=2;i<=sqrt(n);i++){
        if(n%i==0){
            n /= i;
            sum += n;
            break;
        }
    }
    if(!x) break;
}
cout << sum+1; // 补最后1个石子
```

3. Rosemary_dream（★★★★☆）
- 亮点：详细注释分解过程，强调质数处理。
- 代码核心：
```cpp
for(int i=2;i<=sqrt(n);i++){
    if(n%i==0){
        ans += (n /= i);
        break;
    }
}
if(!flag) break;
cout << ans+1; // 补最后1个石子
```

【关键思路总结】
- **贪心选择**：每次取当前数的最小质因数分解，确保剩余石子最大。
- **质数处理**：当无法分解时，将n作为行数取最后1个石子。
- **循环终止**：当剩余石子数为1时结束，总和需加上最后一步的1。

【拓展套路】
- 类似问题可转化为质因数分解求最优路径，如LeetCode 650 2 Keys Keyboard。
- 质数快速判定法（试除法）在分解过程中的应用。

【相似题目】
1. P1029 最大公约数和最小公倍数问题（分解因数应用）
2. P1075 质因数分解（质数处理）
3. P1412 经营与开发（贪心策略）

---
处理用时：294.29秒