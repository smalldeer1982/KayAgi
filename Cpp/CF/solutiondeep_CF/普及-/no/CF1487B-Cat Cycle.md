# 题目信息

# Cat Cycle

## 题目描述

Suppose you are living with two cats: A and B. There are $ n $ napping spots where both cats usually sleep.

Your cats like to sleep and also like all these spots, so they change napping spot each hour cyclically:

- Cat A changes its napping place in order: $ n, n - 1, n - 2, \dots, 3, 2, 1, n, n - 1, \dots $ In other words, at the first hour it's on the spot $ n $ and then goes in decreasing order cyclically;
- Cat B changes its napping place in order: $ 1, 2, 3, \dots, n - 1, n, 1, 2, \dots $ In other words, at the first hour it's on the spot $ 1 $ and then goes in increasing order cyclically.

The cat B is much younger, so they have a strict hierarchy: A and B don't lie together. In other words, if both cats'd like to go in spot $ x $ then the A takes this place and B moves to the next place in its order (if $ x < n $ then to $ x + 1 $ , but if $ x = n $ then to $ 1 $ ). Cat B follows his order, so it won't return to the skipped spot $ x $ after A frees it, but will move to the spot $ x + 2 $ and so on.

Calculate, where cat B will be at hour $ k $ ?

## 说明/提示

In the first and second test cases $ n = 2 $ , so:

- at the $ 1 $ -st hour, A is on spot $ 2 $ and B is on $ 1 $ ;
- at the $ 2 $ -nd hour, A moves to spot $ 1 $ and B — to $ 2 $ .

 If $ n = 3 $ then: - at the $ 1 $ -st hour, A is on spot $ 3 $ and B is on $ 1 $ ;
- at the $ 2 $ -nd hour, A moves to spot $ 2 $ ; B'd like to move from $ 1 $ to $ 2 $ , but this spot is occupied, so it moves to $ 3 $ ;
- at the $ 3 $ -rd hour, A moves to spot $ 1 $ ; B also would like to move from $ 3 $ to $ 1 $ , but this spot is occupied, so it moves to $ 2 $ .

In the sixth test case:

- A's spots at each hour are $ [5, 4, 3, 2, 1] $ ;
- B's spots at each hour are $ [1, 2, 4, 5, 2] $ .

## 样例 #1

### 输入

```
7
2 1
2 2
3 1
3 2
3 3
5 5
69 1337```

### 输出

```
1
2
1
3
2
2
65```

# AI分析结果

### 题目内容
# Cat Cycle

## 题目描述
假设你和两只猫：A 和 B 一起生活。有 $n$ 个午睡地点，两只猫通常都在这些地方睡觉。

你的猫喜欢睡觉，也喜欢所有这些地点，所以它们每小时会循环更换午睡地点：
- 猫 A 按以下顺序更换午睡地点：$n, n - 1, n - 2, \dots, 3, 2, 1, n, n - 1, \dots$。换句话说，在第一个小时它在地点 $n$，然后按降序循环；
- 猫 B 按以下顺序更换午睡地点：$1, 2, 3, \dots, n - 1, n, 1, 2, \dots$。换句话说，在第一个小时它在地点 $1$，然后按升序循环。

猫 B 年轻得多，所以它们有严格的等级制度：A 和 B 不会躺在一起。换句话说，如果两只猫都想去地点 $x$，那么 A 会占据这个位置，B 会移动到它顺序中的下一个位置（如果 $x < n$，则移动到 $x + 1$，但如果 $x = n$，则移动到 $1$）。猫 B 遵循它的顺序，所以它不会在 A 离开后回到跳过的地点 $x$，而是会移动到地点 $x + 2$ 等等。

计算，在第 $k$ 小时猫 B 会在哪里？

## 说明/提示
在第一个和第二个测试用例中，$n = 2$，所以：
- 在第 $1$ 小时，A 在地点 $2$，B 在 $1$；
- 在第 $2$ 小时，A 移动到地点 $1$，B 移动到 $2$。

如果 $n = 3$，那么：
- 在第 $1$ 小时，A 在地点 $3$，B 在 $1$；
- 在第 $2$ 小时，A 移动到地点 $2$；B 想从 $1$ 移动到 $2$，但这个位置被占据了，所以它移动到 $3$；
- 在第 $3$ 小时，A 移动到地点 $1$；B 也想从 $3$ 移动到 $1$，但这个位置被占据了，所以它移动到 $2$。

在第六个测试用例中：
- A 在每个小时的地点是 $[5, 4, 3, 2, 1]$；
- B 在每个小时的地点是 $[1, 2, 4, 5, 2]$。

## 样例 #1
### 输入
```
7
2 1
2 2
3 1
3 2
3 3
5 5
69 1337
```
### 输出
```
1
2
1
3
2
2
65
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是通过分析 $n$ 的奇偶性来找规律从而避免模拟带来的超时问题。
 - **思路方面**：当 $n$ 为偶数时，所有题解都发现两只猫不会相遇，猫 B 的位置可通过简单取模得到。当 $n$ 为奇数时，题解都意识到两只猫会相遇，且相遇存在一定周期，需要根据相遇次数来调整猫 B 的位置。
 - **算法要点**：偶数情况直接计算 $(k - 1) \bmod n + 1$ 得出猫 B 位置；奇数情况先确定相遇周期 $T = \frac{n - 1}{2}$，再根据相遇次数计算猫 B 额外移动距离，最后通过取模得出位置。
 - **解决难点**：难点在于发现 $n$ 的奇偶性对猫 A 和猫 B 相遇情况的影响，并准确找出奇数情况下的相遇周期以及猫 B 位置变化规律。各题解在表述和具体公式推导上略有不同，但本质思路一致。

### 所选的题解
 - **作者：7KByte (5星)**
    - **关键亮点**：思路清晰，代码简洁高效。对奇数偶数情况的公式推导准确且直接，在代码实现中对奇数情况的计算步骤清晰，先对 $k$ 进行预处理，再分别计算周期数、起始位置等，最终得出结果。
    - **重点代码**：
```cpp
void solve(){
    scanf("%d%d",&n,&k);
    if(n&1){
        k--;
        int w=(n-1)>>1,mid=(n+1)>>1;
        int now=k/w;k%=w;
        int st=(now*mid)%n+1;
        printf("%d\n",(st-1+k)%n+1);
    }
    else{
        printf("%d\n",(k-1)%n+1);
    }
}
```
    - **核心实现思想**：先判断 $n$ 的奇偶性。奇数时，先将 $k$ 减 1，计算出周期 $w$ 和每次相遇 B 猫位置增加量 $mid$，得到周期数 $now$ 和剩余时间 $k$，算出起始位置 $st$，再结合剩余时间得到最终位置；偶数时直接按公式计算位置。
 - **作者：张语诚ZYC (4星)**
    - **关键亮点**：对题意回顾详细，分析过程通过列举 $n = 2$、$n = 4$、$n = 3$ 等具体例子，结合图形，直观清晰地展示规律的推导过程，便于理解。
    - **重点代码**：无（题解未完整给出代码）
    - **核心实现思想（总结）**：同样根据 $n$ 奇偶性分类讨论。偶数时，通过具体例子得出猫 B 位置为 $k \bmod n$；奇数时，通过观察例子发现相遇规律，推出猫 B 位置与移动次数 $t$ 的关系。
 - **作者：dalao_see_me (4星)**
    - **关键亮点**：令 $m = k - 1$ 简化后续公式表达，对奇数偶数两种情况的规律总结清晰明了，代码实现简洁，逻辑连贯。
    - **重点代码**：
```cpp
int main(){
    _=read();
    while(_--){
        n=read();k=read();
        k--;
        if(n&1){
            int p=n-1>>1,Move=k/p;
            printf("%d\n",(Move+k)%n+1);
        }
        else printf("%d\n",k%n+1);
    }
    return 0;
}
```
    - **核心实现思想**：先读入数据并对 $k$ 减 1，判断 $n$ 奇偶性。奇数时计算相遇间隔时间 $p$ 和额外移动距离 $Move$，得出最终位置；偶数时直接按公式计算位置。

### 最优关键思路或技巧
通过对 $n$ 奇偶性分类讨论找规律是解决本题的关键技巧。在分析过程中，通过列举具体小数据例子（如 $n = 2$、$n = 3$ 等），结合图形来直观地发现猫 A 和猫 B 的相遇规律以及猫 B 位置变化规律，从而避免复杂的模拟过程，提高算法效率。

### 可拓展思路
此类题目属于通过找规律解决循环移动且存在位置冲突的问题。类似套路是先观察数据特点（如奇偶性、倍数关系等），通过列举小数据找规律，再推广到一般情况。同类型题通常会在移动顺序、冲突处理规则等方面做变化。

### 洛谷相似题目推荐
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析日常生活中的时间安排规律来解决问题，与本题找规律思路类似。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔价格和所需铅笔数量找最优购买方案，需要分析数据规律并进行计算，和本题一样避免暴力枚举。
 - [P2669 金币](https://www.luogu.com.cn/problem/P2669)：通过找规律计算一定天数内获得金币总数，同样是对循环规律数据的处理。

### 个人心得摘录与总结
无。 

---
处理用时：68.00秒