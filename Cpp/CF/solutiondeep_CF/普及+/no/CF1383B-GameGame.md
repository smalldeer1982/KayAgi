# 题目信息

# GameGame

## 题目描述

Koa the Koala and her best friend want to play a game.

The game starts with an array $ a $ of length $ n $ consisting of non-negative integers. Koa and her best friend move in turns and each have initially a score equal to $ 0 $ . Koa starts.

Let's describe a move in the game:

- During his move, a player chooses any element of the array and removes it from this array, xor-ing it with the current score of the player.  More formally: if the current score of the player is $ x $ and the chosen element is $ y $ , his new score will be $ x           \oplus y $ . Here $ \oplus $ denotes [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).
  
   Note that after a move element $ y $ is removed from $ a $ .
- The game ends when the array is empty.

At the end of the game the winner is the player with the maximum score. If both players have the same score then it's a draw.

If both players play optimally find out whether Koa will win, lose or draw the game.

## 说明/提示

In testcase $ 1 $ of the first sample we have:

 $ a = [1, 2, 2] $ . Here Koa chooses $ 1 $ , other player has to choose $ 2 $ , Koa chooses another $ 2 $ . Score for Koa is $ 1 \oplus 2 = 3 $ and score for other player is $ 2 $ so Koa wins.

## 样例 #1

### 输入

```
3
3
1 2 2
3
2 2 3
5
0 0 0 2 2```

### 输出

```
WIN
LOSE
DRAW```

## 样例 #2

### 输入

```
4
5
4 1 5 1 3
4
1 0 1 6
1
0
2
5 4```

### 输出

```
WIN
WIN
DRAW
WIN```

# AI分析结果

### 题目翻译
考拉 Koa 和她最好的朋友想玩一个游戏。

游戏开始时，有一个长度为 $n$ 的数组 $a$，数组由非负整数组成。Koa 和她最好的朋友轮流行动，初始时两人的分数均为 $0$。Koa 先行动。

下面描述一下游戏中的行动：
- 在轮到某个玩家行动时，该玩家选择数组中的任意一个元素，并将其从数组中移除，然后将该元素与玩家当前的分数进行异或运算。更正式地说：如果玩家当前的分数是 $x$，选择的元素是 $y$，那么他的新分数将是 $x \oplus y$。这里 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。
  注意，行动结束后，元素 $y$ 会从数组 $a$ 中移除。
- 当数组为空时，游戏结束。

游戏结束时，分数最高的玩家获胜。如果两名玩家的分数相同，则为平局。

如果两名玩家都采取最优策略，请判断 Koa 是会赢、会输还是会平局。

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是按位分析数组元素，根据每一位上 1 的个数的奇偶性来判断对游戏结果的影响。
- **思路**：从高位到低位逐位分析，若某一位 1 的个数为偶数，则对结果无影响；若为奇数，则需进一步根据 1 的个数的形式（$4k + 1$ 或 $4k + 3$）以及 0 的个数的奇偶性来判断胜负。若所有位上 1 的个数均为偶数，则平局。
- **算法要点**：先对数组元素进行异或运算，若结果为 0 则平局；否则找到最高位的 1，统计该位上 1 的个数，根据上述规则判断胜负。
- **解决难点**：主要难点在于分析不同情况下（1 的个数的形式和 0 的个数的奇偶性）玩家的最优策略以及对胜负的影响。

### 所选题解
- **灵茶山艾府（5星）**：
  - **关键亮点**：思路清晰，代码简洁，对不同情况的分析全面且准确。
- **Bronya18C（4星）**：
  - **关键亮点**：通过具体例子引入，便于理解，代码实现较为直观。
- **FxorG（4星）**：
  - **关键亮点**：对按位分析的思路解释详细，代码实现规范。

### 重点代码
#### 灵茶山艾府的代码
```cpp
void run() {
    int n;
    cin >> n;
    vector<int> a(n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s ^= a[i];
    }
    if (s == 0) { 
        cout << "DRAW" << '\n';
        return;
    }
    for (int b = 30;; b--) {
        if (s >> b & 1) { 
            int ones = 0;
            for (int v: a) if (v >> b & 1) ones++;
            int zeros = n - ones;
            cout << (ones % 4 == 3 && zeros % 2 == 0 ? "LOSE" : "WIN") << '\n';
            return;
        }
    }
}
```
**核心实现思想**：先对数组元素异或，若结果为 0 则平局；否则找到最高位的 1，统计该位上 1 的个数和 0 的个数，根据规则判断胜负。

#### Bronya18C 的代码
```cpp
int lowbit(int u){
    return u&(-u);
}
int main(){ 
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        sum=0;g=0;
        for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]),sum=sum xor a[i];
        if(sum==0){
            puts("DRAW");
            continue;
        }
        while(sum-lowbit(sum)!=0)sum-=lowbit(sum);
        for(int i=1;i<=n;i++)
            if(a[i]&sum)g++;
        if(g%4==1){
            puts("WIN");
        }
        else{
            if(n%2==1)puts("LOSE");
            else puts("WIN");
        }
    }
    return 0;
}
```
**核心实现思想**：先对数组元素异或，若结果为 0 则平局；否则只保留最高位的 1，统计有该位 1 的元素个数，根据规则判断胜负。

#### FxorG 的代码
```cpp
int main() {
    t=rd();
    while(t--) {
        n=rd(); int S=0;
        for(int i=1;i<=n;i++) a[i]=rd(),S^=a[i];
        bool fl=0;
        for(int i=30;i>=0;i--) {
            if((S>>i)&1) {
                int tot=0;
                for(int j=1;j<=n;j++) tot+=(a[j]>>i)&1;
                if((n-tot)%2==0&&tot%4==3) fl=1,puts("LOSE");
                else fl=1,puts("WIN");
            }
            if(fl) break;
        }
        if(!fl) puts("DRAW");
    }	
    return 0;
}
```
**核心实现思想**：先对数组元素异或，若结果为 0 则平局；否则从高位到低位找 1，统计该位上 1 的个数，根据规则判断胜负。

### 最优关键思路或技巧
按位分析的思维方式，从高位到低位逐位判断对结果的影响，通过异或运算和统计 1 的个数来简化问题。

### 拓展思路
同类型题或类似算法套路：涉及异或运算的博弈问题，通常可以采用按位分析的方法，根据每一位的情况来确定最优策略。

### 洛谷题目推荐
1. [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)
2. [P2197 【模板】nim 游戏](https://www.luogu.com.cn/problem/P2197)
3. [P4151 [WC2011]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)

### 个人心得
无。

---
处理用时：41.60秒