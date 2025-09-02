# 题目信息

# Suit and Tie

## 题目描述

Allen is hosting a formal dinner party. $ 2n $ people come to the event in $ n $ pairs (couples). After a night of fun, Allen wants to line everyone up for a final picture. The $ 2n $ people line up, but Allen doesn't like the ordering. Allen prefers if each pair occupies adjacent positions in the line, as this makes the picture more aesthetic.

Help Allen find the minimum number of swaps of adjacent positions he must perform to make it so that each couple occupies adjacent positions in the line.

## 说明/提示

In the first sample case, we can transform $ 1 1 2 3 3 2 4 4 \rightarrow 1 1 2 3 2 3 4 4 \rightarrow 1 1 2 2 3 3 4 4 $ in two steps. Note that the sequence $ 1 1 2 3 3 2 4 4 \rightarrow 1 1 3 2 3 2 4 4 \rightarrow 1 1 3 3 2 2 4 4 $ also works in the same number of steps.

The second sample case already satisfies the constraints; therefore we need $ 0 $ swaps.

## 样例 #1

### 输入

```
4
1 1 2 3 3 2 4 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
1 1 2 2 3 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
3 1 2 3 1 2
```

### 输出

```
3
```

# AI分析结果

### 题目内容重写

**题目描述**

Allen正在举办一个正式的晚宴派对。$2n$个人以$n$对（情侣）的形式来到这个活动。经过一晚的欢乐后，Allen想让所有人排成一排拍一张最后的照片。$2n$个人排成了一排，但Allen不喜欢这个排列。Allen更喜欢每对情侣占据相邻的位置，因为这样照片看起来更美观。

帮助Allen找到他必须执行的最少相邻位置交换次数，使得每对情侣占据相邻的位置。

**说明/提示**

在第一个样例中，我们可以将$1\ 1\ 2\ 3\ 3\ 2\ 4\ 4$变换为$1\ 1\ 2\ 3\ 2\ 3\ 4\ 4$，再变换为$1\ 1\ 2\ 2\ 3\ 3\ 4\ 4$，共两步。注意，序列$1\ 1\ 2\ 3\ 3\ 2\ 4\ 4$变换为$1\ 1\ 3\ 2\ 3\ 2\ 4\ 4$，再变换为$1\ 1\ 3\ 3\ 2\ 2\ 4\ 4$也只需要两步。

第二个样例已经满足条件，因此需要$0$次交换。

**样例 #1**

**输入**

```
4
1 1 2 3 3 2 4 4
```

**输出**

```
2
```

**样例 #2**

**输入**

```
3
1 1 2 2 3 3
```

**输出**

```
0
```

**样例 #3**

**输入**

```
3
3 1 2 3 1 2
```

**输出**

```
3
```

### 题解分析与结论

#### 题解对比与总结

1. **Karry5307的题解**
   - **思路**：贪心算法，每次找到最左边的元素，然后找到其配对的元素，通过交换将它们放到一起。
   - **难点**：贪心策略的证明，即为什么每次选择最左边的元素进行交换是最优的。
   - **代码实现**：通过双重循环找到配对元素，然后进行交换并统计交换次数。
   - **评分**：4星。思路清晰，代码简洁，但贪心策略的证明略显简略。

2. **小张的8424的题解**
   - **思路**：贪心算法，每次找到最右边的元素，然后找到其配对的元素，通过交换将它们放到一起。
   - **难点**：贪心策略的证明，即为什么每次选择最右边的元素进行交换是最优的。
   - **代码实现**：通过循环找到配对元素，然后进行交换并统计交换次数。
   - **评分**：4星。思路清晰，代码简洁，贪心策略的证明较为详细。

3. **fengyuxuan的题解**
   - **思路**：贪心算法，每次找到一对数的第一个数，然后找到其配对的元素，通过交换将它们放到一起。
   - **难点**：贪心策略的证明，即为什么每次选择第一个数进行交换是最优的。
   - **代码实现**：通过循环找到配对元素，然后进行交换并统计交换次数。
   - **评分**：3星。思路清晰，代码简洁，但贪心策略的证明较为简略。

4. **Piwry的题解**
   - **思路**：贪心算法，每次找到最右侧的元素，然后找到其配对的元素，通过交换将它们放到一起。
   - **难点**：贪心策略的证明，即为什么每次选择最右侧的元素进行交换是最优的。
   - **代码实现**：通过循环找到配对元素，然后进行交换并统计交换次数。
   - **评分**：4星。思路清晰，代码简洁，贪心策略的证明较为详细。

#### 最优关键思路或技巧

- **贪心策略**：每次选择最左或最右的元素进行交换，确保每次交换都能最大限度地减少后续的交换次数。
- **交换次数统计**：通过模拟交换过程，统计每次交换的次数，确保最终结果为最小值。

#### 可拓展之处

- **类似问题**：类似的问题可以扩展到其他需要将特定元素配对或排列的题目，如将相同颜色的球放在一起等。
- **算法优化**：可以考虑使用更高效的数据结构来优化查找和交换的过程，如哈希表等。

#### 推荐题目

1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

#### 个人心得摘录

- **Karry5307**：提到差点没看数据范围，提醒我们在解题时要注意数据范围。
- **小张的8424**：提到在比赛中通过吃苹果灵光一闪，强调了放松和灵感的重要性。
- **Piwry**：提到证明可能有些细节问题，但大体思路正确，强调了证明的重要性。

### 所选高分题解

#### 1. Karry5307的题解（4星）

**关键亮点**：贪心策略清晰，代码简洁，适合初学者理解。

**代码片段**：
```cpp
for(register int i=1;i<=n;i+=2)
{
    for(register int j=i+1;j<=n;j++)
    {
        if(x[j]==x[i])
        {
            pos=j;
            break;
        }
    }
    for(register int j=pos;j>i+1;j--)
    {
        swap(x[j],x[j-1]),res++;
    }
}
```

#### 2. 小张的8424的题解（4星）

**关键亮点**：贪心策略详细，代码简洁，适合进阶学习。

**代码片段**：
```cpp
while(n!=0)
{
    for(i=0;i<n-1;i++)
        if(a[i]==a[n-1])
            break;
    tot+=n-i-2;
    for(j=i;j<n-1;j++)
        swap(a[j],a[j+1]);
    n-=2;
}
```

#### 3. Piwry的题解（4星）

**关键亮点**：贪心策略详细，代码简洁，适合深入学习。

**代码片段**：
```cpp
while(end >= 1){
    int pos =end-1;
    while(a[pos] != a[end])
        --pos;
    ans +=end-pos-1;
    for(int i =pos; i < end; ++i)
        a[i] =a[i+1];
    end -=2;
}
```

---
处理用时：50.53秒