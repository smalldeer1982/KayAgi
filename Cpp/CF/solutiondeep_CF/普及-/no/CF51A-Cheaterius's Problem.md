# 题目信息

# Cheaterius's Problem

## 题目描述

Cheaterius is a famous in all the Berland astrologist, magician and wizard, and he also is a liar and a cheater. One of his latest inventions is Cheaterius' amulets! They bring luck and wealth, but are rather expensive. Cheaterius makes them himself. The technology of their making is kept secret. But we know that throughout long nights Cheaterius glues together domino pairs with super glue to get squares $ 2×2 $ which are the Cheaterius' magic amulets!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF51A/5f1914bbdaa36d78b7400d8ccae8395b8432e5c5.png)That's what one of Cheaterius's amulets looks likeAfter a hard night Cheaterius made $ n $ amulets. Everyone of them represents a square $ 2×2 $ , every quarter contains 1 to 6 dots. Now he wants sort them into piles, every pile must contain similar amulets. Two amulets are called similar if they can be rotated by 90, 180 or 270 degrees so that the following condition is met: the numbers of dots in the corresponding quarters should be the same. It is forbidden to turn over the amulets.

Write a program that by the given amulets will find the number of piles on Cheaterius' desk.

## 样例 #1

### 输入

```
4
31
23
**
31
23
**
13
32
**
32
13
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
51
26
**
54
35
**
25
61
**
45
53
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
# Cheaterius的问题

## 题目描述
Cheaterius是全Berland著名的占星家、魔术师和巫师，但他也是个骗子。他最近的发明之一是Cheaterius的护身符！它们能带来好运和财富，但价格相当昂贵。Cheaterius自己制作这些护身符，其制作技术是保密的。但我们知道，在漫长的夜晚里，Cheaterius会用强力胶水把多米诺骨牌对粘在一起，制成 $2×2$ 的正方形，这些就是Cheaterius的魔法护身符！

![这是Cheaterius的一个护身符的样子](https://cdn.luogu.com.cn/upload/vjudge_pic/CF51A/5f1914bbdaa36d78b7400d8ccae8395b8432e5c5.png)

经过一个艰苦的夜晚，Cheaterius制作了 $n$ 个护身符。每个护身符都是一个 $2×2$ 的正方形，每个小方格包含1到6个点。现在他想把它们分成几堆，每堆必须包含相似的护身符。如果两个护身符可以旋转90度、180度或270度，使得对应小方格中的点数相同，则称这两个护身符是相似的。禁止翻转护身符。

编写一个程序，根据给定的护身符，找出Cheaterius桌子上的堆数。

## 样例 #1

### 输入
```
4
31
23
**
31
23
**
13
32
**
32
13
```

### 输出
```
1
```

## 样例 #2

### 输入
```
4
51
26
**
54
35
**
25
61
**
45
53
```

### 输出
```
2
```

### 算法分类
模拟

### 综合分析与结论
- **思路对比**：
    - Ba_creeper：使用三维数组存储每个护身符，边读入边与之前存储的护身符比较，通过旋转枚举所有可能情况判断是否相似。
    - MeowScore：将每个护身符的四种状态压成四位数，利用桶标记状态，若所有状态都未标记则为新的护身符。
    - Accepted_Z：使用四维数组标记每个护身符的四种状态，若某种状态未出现过则答案加一。
    - codemap：使用两层循环比较所有护身符对，用布尔数组标记重复的护身符，最后统计未标记的个数。
- **算法要点**：核心在于模拟护身符的旋转过程，判断两个护身符是否相似。不同题解采用了不同的数据结构（三维数组、四维数组、桶、布尔数组等）来存储和标记护身符状态。
- **解决难点**：主要难点在于准确模拟护身符的旋转，并高效地判断两个护身符是否相似。各题解通过枚举旋转状态和使用合适的数据结构来解决这一难点。

### 题解评分与选择
- **Ba_creeper**：4星。思路清晰，代码注释详细，通过三维数组存储和枚举旋转状态，容易理解。
- **MeowScore**：4星。采用状态压缩的方法，将护身符状态压成四位数，利用桶标记，代码简洁。
- **Accepted_Z**：3星。使用四维数组标记状态，思路简单，但代码中使用万能头文件，可移植性稍差。
- **codemap**：3星。使用两层循环比较，代码冗长，且输入处理方式较复杂。

### 所选题解
- **Ba_creeper（4星）**：
    - **关键亮点**：思路清晰，代码注释详细，通过三维数组存储护身符，枚举旋转状态判断相似性。
- **MeowScore（4星）**：
    - **关键亮点**：采用状态压缩的方法，将护身符状态压成四位数，利用桶标记，代码简洁高效。

### 重点代码
#### Ba_creeper
```c++
// 枚举旋转状态判断是否相似
for(int j=1;j<=k;++j) {
    if(a==f[1][1][j] && b==f[1][2][j] && c==f[2][1][j] && d==f[2][2][j]) {
        ok=1;
        break;
    }
    if(c==f[1][1][j] && a==f[1][2][j] && d==f[2][1][j] && b==f[2][2][j]) {
        ok=1;
        break;
    }
    if(d==f[1][1][j] && c==f[1][2][j] && b==f[2][1][j] && a==f[2][2][j]) {
        ok=1;
        break;
    }
    if(b==f[1][1][j] && d==f[1][2][j] && a==f[2][1][j] && c==f[2][2][j]) {
        ok=1;
        break;
    }
}
```
**核心实现思想**：遍历之前存储的所有护身符，枚举当前护身符的四种旋转状态，判断是否与之前的某个护身符相似。

#### MeowScore
```c++
// 生成四位数表示护身符状态
int f(int a,int b,int c,int d){
    return 1000*a+100*b+10*c+d;
}
// 判断是否为新的护身符
if(!t[p1]&&!t[p2]&&!t[p3]&&!t[p4])
    t[p1]=1,maxn=max(maxn,p1);
```
**核心实现思想**：将护身符的四个数字组合成四位数表示其状态，利用桶标记状态，若所有状态都未标记则为新的护身符。

### 最优关键思路或技巧
- **状态压缩**：如MeowScore的题解，将护身符的状态压成四位数，利用桶标记状态，简化了判断过程，提高了效率。
- **枚举旋转状态**：通过枚举护身符的四种旋转状态，判断两个护身符是否相似，是解决本题的关键。

### 拓展思路
同类型题可能会涉及更多的图形变换（如翻转、缩放等），或者在更高维度上进行判断。类似算法套路可以应用于图形匹配、图像识别等领域。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：简单的模拟题，锻炼代码实现能力。
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)：涉及字符串处理和模拟，需要考虑多种情况。
- [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)：模拟内存管理过程，使用队列或数组实现。

### 个人心得
题解中未包含个人心得。

---
处理用时：37.72秒