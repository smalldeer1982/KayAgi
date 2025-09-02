# 题目信息

# Mysterious Crime

## 题目描述

Acingel is a small town. There was only one doctor here — Miss Ada. She was very friendly and nobody has ever said something bad about her, so who could've expected that Ada will be found dead in her house? Mr Gawry, world-famous detective, is appointed to find the criminal. He asked $ m $ neighbours of Ada about clients who have visited her in that unlucky day. Let's number the clients from $ 1 $ to $ n $ . Each neighbour's testimony is a permutation of these numbers, which describes the order in which clients have been seen by the asked neighbour.

However, some facts are very suspicious – how it is that, according to some of given permutations, some client has been seen in the morning, while in others he has been seen in the evening? "In the morning some of neighbours must have been sleeping!" — thinks Gawry — "and in the evening there's been too dark to see somebody's face...". Now he wants to delete some prefix and some suffix (both prefix and suffix can be empty) in each permutation, so that they'll be non-empty and equal to each other after that — some of the potential criminals may disappear, but the testimony won't stand in contradiction to each other.

In how many ways he can do it? Two ways are called different if the remaining common part is different.

## 说明/提示

In the first example, all possible common parts are $ [1] $ , $ [2] $ , $ [3] $ and $ [2, 3] $ .

In the second and third examples, you can only leave common parts of length $ 1 $ .

## 样例 #1

### 输入

```
3 2
1 2 3
2 3 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 6
1 2 3 4 5
2 3 1 4 5
3 4 5 1 2
3 5 4 2 1
2 3 5 4 1
1 2 3 4 5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 2
1 2
2 1
```

### 输出

```
2
```

# AI分析结果

### 题目内容
# 神秘的犯罪

## 题目描述
阿辛格尔是一个小镇。这里只有一位医生——艾达小姐。她非常友善，从来没有人说过她的坏话，所以谁能想到艾达会被发现死在自己家中呢？世界著名侦探高里先生被任命来找出罪犯。他询问了艾达的$m$位邻居，关于在那个不幸的日子里拜访过她的病人。让我们将病人从$1$到$n$编号。每位邻居的证词都是这些数字的一个排列，描述了被询问邻居看到病人的顺序。

然而，一些事实非常可疑——怎么会根据一些给定的排列，某个病人在早上被看到，而在其他排列中他却在晚上被看到呢？“早上肯定有些邻居在睡觉！”——高里想——“而晚上天太黑，看不清某人的脸……”现在他想在每个排列中删除一些前缀和一些后缀（前缀和后缀都可以为空），这样在那之后它们将是非空的且彼此相等——一些潜在的罪犯可能会消失，但证词不会相互矛盾。

他有多少种方法可以做到这一点呢？如果剩余的公共部分不同，则两种方法称为不同。

## 说明/提示
在第一个例子中，所有可能的公共部分是$[1]$，$[2]$，$[3]$ 和 $[2, 3]$。

在第二个和第三个例子中，你只能留下长度为$1$的公共部分。

## 样例 #1
### 输入
```
3 2
1 2 3
2 3 1
```
### 输出
```
4
```

## 样例 #2
### 输入
```
5 6
1 2 3 4 5
2 3 1 4 5
3 4 5 1 2
3 5 4 2 1
2 3 5 4 1
1 2 3 4 5
```
### 输出
```
5
```

## 样例 #3
### 输入
```
2 2
1 2
2 1
```
### 输出
```
2
```

### 算法分类
枚举

### 综合分析与结论
这几道题解均围绕如何高效找出满足条件的公共子串方案数展开。各题解思路和方法有所不同，有的通过暴力枚举优化，有的利用排列性质，有的借助后缀数组等。它们从不同角度解决问题，都有各自的优点和需要注意的地方。

### 所选的题解
 - **作者：skyskyCCC（4星）**
    - **关键亮点**：针对$n$和$m$取值范围小的特点，采用暴力枚举优化策略。以第一个人的字符串为基准，枚举子串作为目标，然后基于此枚举其他排列，利用匹配位置优化下次枚举起点，计算方案数。代码实现简洁明了，思路直接易懂。
    - **个人心得**：因读入量过大，采用快读优化。
    - **核心代码片段**：
```cpp
for (long long i=1;i<=n;i++){
    long long fangan=1;
    while(fangan<=n-i){
        long long st_str=a[1][i+fangan];
        bool flag=true;
        for (long long j=2;j<=m;j++){
            long long k=t[j][a[1][i]]+fangan;
            if(a[j][k]==st_str){
                continue;
            }
            else flag=false;
        }
        if(flag==false){
            break;
        }
        fangan++;
    }
    i+=(fangan-1);
    ans+=fangan*(fangan+1)/2;
}
```
核心思想：从第一个排列的每个位置开始，尝试扩展子串，检查其他排列在对应位置是否能匹配，若匹配则继续扩展，统计满足条件的子串长度，根据长度计算对方案数的贡献。

 - **作者：ZLCT（4星）**
    - **关键亮点**：利用排列的双向映射性质，记录每个排列中值为$j$的下一个值。以第一个排列为基准，通过判断所有排列中对应位置下一个值是否相等来确定连续区间是否合法，进而计算方案数。这种方法巧妙利用排列特性，优化了暴力枚举的复杂度。
    - **核心代码片段**：
```cpp
bool check(int x){
    for(int i=2;i<=m;++i){
        if(d[i][x]!=d[1][x])return 0;
    }
    return 1;
}
//...
for(;i<=n;++i){
    for(j=i;j<=n;++j){
        if(!check(a[1][j]))break;
    }
    j=min(j,n);
    ans+=(j-i+1)*(j-i+2)/2;
    i=j;
}
```
核心思想：通过`check`函数检查所有排列中某个值的下一个值是否一致，从第一个排列的每个位置开始，不断扩展区间，若区间合法则计算该区间对方案数的贡献。

### 最优关键思路或技巧
利用排列的特殊性质，如双向映射关系，避免对所有可能的前缀和后缀组合进行暴力枚举，通过优化枚举方式或检查条件来降低时间复杂度。例如ZLCT题解中利用记录下一个值并检查其一致性的方法，以及skyskyCCC题解中根据匹配位置优化枚举起点的方式。

### 同类型题或类似算法套路拓展
此类题目通常围绕序列的公共子串或子序列问题，可拓展到其他涉及字符串或序列匹配、寻找公共部分的题目。类似算法套路包括利用序列特性优化枚举过程，或借助数据结构（如后缀数组、后缀自动机等）来高效处理字符串匹配问题，但要根据数据范围选择合适方法。

### 洛谷相似题目推荐
 - [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)：经典字符串匹配问题，可加深对字符串匹配算法的理解。
 - [P5410 【模板】扩展KMP](https://www.luogu.com.cn/problem/P5410)：扩展KMP问题，进一步拓展字符串匹配相关知识。
 - [P2408 不同子串个数](https://www.luogu.com.cn/problem/P2408)：通过后缀数组等方法解决计算不同子串个数问题，与本题在利用数据结构处理字符串问题上有相似之处。 

---
处理用时：43.75秒