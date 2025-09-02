# 题目信息

# [USACO23JAN] Moo Route S

## 题目描述

Farmer Nhoj dropped Bessie in the middle of nowhere! At time $t=0$, Bessie is located at $x=0$ on an infinite number line. She frantically searches for an exit by moving left or right by $1$ unit each second. However, there actually is no exit and after $T$ seconds, Bessie is back at $x=0$, tired and resigned.

Farmer Nhoj tries to track Bessie but only knows how many times Bessie crosses $x=0.5,1.5,2.5, \cdots ,(N−1).5$, given by an array $A_0,A_1, \cdots ,A_{N−1} (1 \le N \le 10^5, 1 \le A_i \le 10^6, \sum A_i \le 10^6)$. Bessie never reaches $x>N$ nor $x<0$.

In particular, Bessie's route can be represented by a string of $T= \sum\limits_{i=0}^{N-1}A_i$
$L$s and $R$s where the $i$-th character represents the direction Bessie moves in during the ith second. The number of direction changes is defined as the number of occurrences of $LR$s plus the number of occurrences of $RL$s.

Please help Farmer Nhoj find any route Bessie could have taken that is consistent with A
and minimizes the number of direction changes. It is guaranteed that there is at least one valid route. 

## 说明/提示

### Explanation for Sample 1

There is only $1$ valid route, corresponding to the route $0 \rightarrow 1 \rightarrow 2 \rightarrow 1 \rightarrow 2 \rightarrow 1 \rightarrow 0$. Since this is the only possible route, it also has the minimum number of direction changes. 

### Explanation for Sample 2

There are $3$ possible routes:

RRLRRLRLLL  
RRRLRLLRLL  
RRRLLRRLLL  

The first two routes have $5$ direction changes, while the last one has only $3$. Thus the last route is the only correct output.

### Scoring

 - Inputs $3-5$: $N \le 2$
 - Inputs $3-10$: $T=A_0+A_1+ \cdots +A_{N−1} \le 5000$
 - Inputs $11-20$: No additional constraints.

## 样例 #1

### 输入

```
2
2 4```

### 输出

```
RRLRLL```

## 样例 #2

### 输入

```
3
2 4 4```

### 输出

```
RRRLLRRLLL```

# AI分析结果

### 综合分析与结论

本题的核心在于通过贪心算法最小化方向改变次数，同时满足给定的交叉次数条件。所有题解均采用了贪心策略，但在具体实现细节和优化程度上有所不同。以下是各题解的对比与总结：

1. **FFTotoro** 和 **Yujinhe469** 的题解较为相似，都通过标记数组来判断是否可以继续往左或右走，避免了不必要的转向。FFTotoro的代码实现更为简洁，而Yujinhe469的代码则更详细地处理了边界情况。
2. **Xy_top** 的题解思路清晰，但未提供具体代码实现，仅描述了贪心策略。
3. **Demeanor_Roy** 的题解提出了“不经过第二个剩余经过次数为1的连通块”的思路，但代码实现较为复杂。
4. **yujinning** 的题解提供了两种解法，第一种解法较为简明，第二种解法与第一种类似，但代码实现较为冗长。
5. **__11jiang08__** 的题解使用了树状数组来优化判断右边是否还有未走的次数，但代码复杂度较高。

### 所选高星题解

#### 1. FFTotoro (4星)
- **关键亮点**：通过标记数组判断是否可以继续往左或右走，代码简洁且高效。
- **代码核心思想**：使用标记数组 `r` 来记录哪些点的次数未消耗完，从而决定是否继续往左或右走。

```cpp
while(x<n){
    if(a[x]>=2)a[x]--,x++,cout<<'R'; // 还可以往右走
    else break; // 次数没了，不需要继续往右走
}
while(1){
    if(x<n&&(a[x]>1||r[x+1]))r[x]=true; // 右边还有没消耗完的次数
    if(x&&(!r[x]||a[x-1]>1))a[--x]--,cout<<'L'; // 可以往左走
    else break; // 还要回去
}
```

#### 2. Yujinhe469 (4星)
- **关键亮点**：详细处理了边界情况，代码逻辑清晰。
- **代码核心思想**：通过方向变量 `d` 记录当前行走方向，并根据剩余次数决定是否转向。

```cpp
if(d==0){
    if(a[i]==1){
        if(a[i+1]==0){
            cout<<"L";
            a[i]--;
            i--;
        }
        else{
            cout<<"R";
            i++;
            a[i]--;
            d=1;
        }
    }
    else{
        cout<<"L";
        a[i]--;
        i--;
    }
}
```

### 最优关键思路与技巧

- **贪心策略**：尽量保持当前方向，减少转向次数。
- **标记数组**：通过标记数组记录哪些点的次数未消耗完，从而决定是否继续往左或右走。
- **边界处理**：详细处理边界情况，确保算法正确性。

### 可拓展之处

- **类似问题**：可以扩展到其他需要最小化操作次数的路径规划问题，如迷宫寻路、机器人路径规划等。
- **优化技巧**：使用树状数组或线段树等数据结构来优化判断过程，提高算法效率。

### 推荐题目

1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

### 个人心得摘录

- **FFTotoro**：通过标记数组来判断是否可以继续往左或右走，避免了不必要的转向，代码实现简洁高效。
- **Yujinhe469**：详细处理了边界情况，确保算法在各种情况下都能正确运行，代码逻辑清晰。

通过这些题解，可以更好地理解贪心算法在路径规划问题中的应用，并掌握如何通过标记数组和边界处理来优化算法。

---
处理用时：31.39秒