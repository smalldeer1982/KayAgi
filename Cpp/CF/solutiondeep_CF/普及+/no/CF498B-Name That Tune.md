# 题目信息

# Name That Tune

## 题目描述

It turns out that you are a great fan of rock band AC/PE. Peter learned that and started the following game: he plays the first song of the list of $ n $ songs of the group, and you have to find out the name of the song. After you tell the song name, Peter immediately plays the following song in order, and so on.

The $ i $ -th song of AC/PE has its recognizability $ p_{i} $ . This means that if the song has not yet been recognized by you, you listen to it for exactly one more second and with probability of $ p_{i} $ percent you recognize it and tell it's name. Otherwise you continue listening it. Note that you can only try to guess it only when it is integer number of seconds after the moment the song starts playing.

In all AC/PE songs the first words of chorus are the same as the title, so when you've heard the first $ t_{i} $ seconds of $ i $ -th song and its chorus starts, you immediately guess its name for sure.

For example, in the song Highway To Red the chorus sounds pretty late, but the song has high recognizability. In the song Back In Blue, on the other hand, the words from the title sound close to the beginning of the song, but it's hard to name it before hearing those words. You can name both of these songs during a few more first seconds.

Determine the expected number songs of you will recognize if the game lasts for exactly $ T $ seconds (i. e. you can make the last guess on the second $ T $ , after that the game stops).

If all songs are recognized faster than in $ T $ seconds, the game stops after the last song is recognized.

## 样例 #1

### 输入

```
2 2
50 2
10 1
```

### 输出

```
1.500000000
```

## 样例 #2

### 输入

```
2 2
0 2
100 2
```

### 输出

```
1.000000000
```

## 样例 #3

### 输入

```
3 3
50 3
50 2
25 2
```

### 输出

```
1.687500000
```

## 样例 #4

### 输入

```
2 2
0 2
0 2
```

### 输出

```
1.000000000
```

# AI分析结果

### 题目重写
# 猜歌名

## 题目描述
原来你是摇滚乐队AC/PE的超级粉丝。彼得得知后，开启了如下游戏：他播放乐队 $n$ 首歌曲列表中的第一首歌，你需要猜出歌名。在你说出歌名后，彼得会立即按顺序播放下一首歌，依此类推。

AC/PE的第 $i$ 首歌具有可识别度 $p_{i}$ 。这意味着，如果这首歌你尚未识别出来，你会再听一秒，且有 $p_{i}$% 的概率识别出它并说出歌名。否则，你会继续听。请注意，只有在歌曲开始播放整数秒后，你才能尝试猜测歌名。

在AC/PE的所有歌曲中，副歌的第一句歌词与歌名相同，所以当你听到第 $i$ 首歌的前 $t_{i}$ 秒且副歌开始时，你肯定能立即猜出歌名。

例如，在歌曲《Highway To Red》中，副歌出现得很晚，但这首歌的可识别度很高。另一方面，在歌曲《Back In Blue》中，歌名中的歌词在歌曲开头附近就出现了，但在听到这些歌词之前很难猜出歌名。你可以在最初的几秒内猜出这两首歌的歌名。

确定如果游戏持续 $T$ 秒（即你可以在第 $T$ 秒进行最后一次猜测，之后游戏停止），你预计能识别出多少首歌曲。

如果所有歌曲在不到 $T$ 秒的时间内都被识别出来，游戏会在最后一首歌被识别出来后停止。

## 样例 #1
### 输入
```
2 2
50 2
10 1
```
### 输出
```
1.500000000
```
## 样例 #2
### 输入
```
2 2
0 2
100 2
```
### 输出
```
1.000000000
```
## 样例 #3
### 输入
```
3 3
50 3
50 2
25 2
```
### 输出
```
1.687500000
```
## 样例 #4
### 输入
```
2 2
0 2
0 2
```
### 输出
```
1.000000000
```

### 算法分类
动态规划

### 题解综合分析与结论
所有题解均采用动态规划解决该问题，核心思路是通过状态转移方程计算在不同时间识别不同歌曲的概率，进而得出期望识别歌曲数。状态定义基本围绕在第 $j$ 秒识别出第 $i$ 首歌的概率（如 $f[i][j]$）。主要难点在于优化初始 $O(nT^2)$ 的时间复杂度。各题解优化思路类似，利用前缀和思想，通过维护一个变量保存相关前缀和，在状态转移时减去超出范围的部分，从而将时间复杂度降至 $O(nT)$。同时，部分题解提到注意空间优化（如滚动数组）以及卡常技巧（如使用 `pow` 计算幂、避免使用 `cin` 等）。

### 所选的题解
- **作者：Exschawasion (5星)**
    - **关键亮点**：思路清晰，详细阐述状态转移方程各项意义，对优化思路解释到位，代码简洁明了。
    - **重点代码核心实现思想**：通过双重循环枚举歌曲和时间，利用一个变量 `sum` 维护前缀和，根据时间与每首歌固定识别时间 `t[i]` 的关系，在转移时进行累加和减去多余项操作，从而实现状态转移。
    ```cpp
    for(int i=1;i<=n;i++){
        db sum=0;
        int id=i,rid=i-1;
        for(int j=i;j<=T;j++){
            sum=sum*(1.0-p[i])+f[rid][j-1];//累加前缀和
            if(j>t[i])sum-=f[rid][j-t[i]-1]*qpow(1.0-p[i],t[i]);//去除多余项
            if(j>=t[i])f[id][j]+=f[rid][j-t[i]]*qpow(1.0-p[i],t[i]);//注意边界
            f[id][j]+=sum*p[i];//转移
        }
    }
    ```
- **作者：sxyugao (4星)**
    - **关键亮点**：展示了两种状态定义下的DP思路，从 $O(n^3)$ 思路出发，通过调整状态定义并利用前缀和优化得到 $O(nT)$ 解法，过程详细。
    - **重点代码核心实现思想**：外层循环枚举歌曲，内层循环枚举时间，使用 `sum` 变量维护前缀和，根据时间与 `t[i]` 的关系进行状态转移，同时在转移过程中处理好重复计算部分。
    ```cpp
    for (int i = 1; i <= n; i++) {
        double sum = 0;
        double lst = pow(1 - p[i], t[i] - 1);
        for (int j = 1; j <= T; j++) {
            sum *= 1 - p[i];
            sum += f[i - 1][j - 1] * p[i];
            if (j >= t[i]) {
                sum -= f[i - 1][j - t[i]] * lst * p[i];
                f[i][j] += f[i - 1][j - t[i]] * lst;
            }
            f[i][j] += sum;
            ans += f[i][j];
        }
    }
    ```
- **作者：Lgx_Q (4星)**
    - **关键亮点**：将题意转化为数组填充问题，便于理解。对状态转移方程的推导和优化过程讲解清晰，还提及空间优化（滚动数组）和卡常注意事项。
    - **重点代码核心实现思想**：利用滚动数组 `f[2][maxn]` 优化空间，通过循环枚举歌曲和时间，在状态转移时根据时间与 `t[i]` 的关系，维护前缀和 `sum`，进行累加和减去多余项操作实现状态转移。
    ```cpp
    for(int i=1;i<=n;i++)
    {
        sum=0;
        pw=pow(1-p[i],t[i]);
        int _i=i&1,_i2=_i^1;
        int _t=t[i];
        double t1=p[i],t2=1-t1;
        for(int j=0;j<=T;j++)
        {
            if(j<i)
            {
                f[_i][j]=0;
                continue;
            }
            sum=sum*t2+f[_i2][j-1];
            if(j>=_t+1) sum-=f[_i2][j-_t-1]*pw;
            if(j>=_t) f[_i][j]=f[_i2][j-_t]*pw;
            else f[_i][j]=0;
            f[_i][j]+=sum*t1;
            ans+=f[_i][j];
        }
    }
    ```

### 最优关键思路或技巧
- **状态定义与转移**：合理定义状态，如 $f[i][j]$ 表示在第 $j$ 秒识别出第 $i$ 首歌的概率，基于此构建状态转移方程，全面考虑歌曲识别的不同情况。
- **前缀和优化**：利用前缀和思想，通过维护一个变量来保存与状态转移相关的前缀和，在状态转移时根据时间与每首歌固定识别时间的关系，减去超出范围的部分，有效降低时间复杂度。
- **空间优化**：采用滚动数组优化空间，减少内存消耗，尤其在处理较大数据规模时。

### 可拓展之处
同类型题通常围绕概率与期望，结合动态规划求解。类似套路是先合理定义状态，根据题目条件列出状态转移方程，若初始复杂度较高，考虑通过前缀和、单调队列等方式优化。例如，一些关于物品收集概率、事件发生期望次数等问题，都可尝试用类似思路解决。

### 洛谷相似题目推荐
- [P1290 欧几里德的游戏](https://www.luogu.com.cn/problem/P1290)：通过博弈过程，利用动态规划求解最优策略，涉及状态定义与转移。
- [P1464 Function](https://www.luogu.com.cn/problem/P1464)：需要根据函数定义，运用递归或动态规划方法计算函数值，锻炼状态转移的思维。
- [P1896 [SCOI2005]互不侵犯](https://www.luogu.com.cn/problem/P1896)：在棋盘放置棋子问题中，通过状态压缩动态规划解决，与本题类似，需合理定义状态和转移方程。

### 个人心得摘录与总结
- **Exschawasion**：提到数组空间可能吃紧，建议使用滚动数组优化，避免开 `long double` 导致 MLE，强调空间优化和数据类型选择的重要性。
- **Lgx_Q**：指出本题十分卡常，计算 $(1 - p_i)^{t_i}$ 时要用 `pow`，别枚举，总结卡常经验。 

---
处理用时：73.84秒