# 题目信息

# Uncle Bogdan and Country Happiness

## 题目描述

Uncle Bogdan is in captain Flint's crew for a long time and sometimes gets nostalgic for his homeland. Today he told you how his country introduced a happiness index.

There are $ n $ cities and $ n−1 $ undirected roads connecting pairs of cities. Citizens of any city can reach any other city traveling by these roads. Cities are numbered from $ 1 $ to $ n $ and the city $ 1 $ is a capital. In other words, the country has a tree structure.

There are $ m $ citizens living in the country. A $ p_i $ people live in the $ i $ -th city but all of them are working in the capital. At evening all citizens return to their home cities using the shortest paths.

Every person has its own mood: somebody leaves his workplace in good mood but somebody are already in bad mood. Moreover any person can ruin his mood on the way to the hometown. If person is in bad mood he won't improve it.

Happiness detectors are installed in each city to monitor the happiness of each person who visits the city. The detector in the $ i $ -th city calculates a happiness index $ h_i $ as the number of people in good mood minus the number of people in bad mood. Let's say for the simplicity that mood of a person doesn't change inside the city.

Happiness detector is still in development, so there is a probability of a mistake in judging a person's happiness. One late evening, when all citizens successfully returned home, the government asked uncle Bogdan (the best programmer of the country) to check the correctness of the collected happiness indexes.

Uncle Bogdan successfully solved the problem. Can you do the same?

More formally, You need to check: "Is it possible that, after all people return home, for each city $ i $ the happiness index will be equal exactly to $ h_i $ ".

## 说明/提示

Let's look at the first test case of the first sample:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/001794ade043a3f0f7ed603305eb551246689207.png)At first, all citizens are in the capital. Let's describe one of possible scenarios:

- a person from city $ 1 $ : he lives in the capital and is in good mood;
- a person from city $ 4 $ : he visited cities $ 1 $ and $ 4 $ , his mood was ruined between cities $ 1 $ and $ 4 $ ;
- a person from city $ 3 $ : he visited cities $ 1 $ and $ 3 $ in good mood;
- a person from city $ 6 $ : he visited cities $ 1 $ , $ 3 $ and $ 6 $ , his mood was ruined between cities $ 1 $ and $ 3 $ ;

 In total, - $ h_1 = 4 - 0 =         4 $ ,
- $ h_2 = 0 $ ,
- $ h_3 = 1 - 1 = 0 $ ,
- $ h_4 = 0 - 1 = -1 $ ,
- $ h_5 = 0 $ ,
- $ h_6 = 0 - 1 = -1 $ ,
- $ h_7 = 0 $ .

The second case of the first test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/a9264c4828a85c9989a95ed8604e23cfb9f3dcda.png)All people have already started in bad mood in the capital — this is the only possible scenario.

The first case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/b8bbd8cbfa8f12355a17c596fd18bc65433a619c.png)The second case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/5c48a1551b8fe0dc0edc02bc5782fb0068b84587.png)It can be proven that there is no way to achieve given happiness indexes in both cases of the second test.

## 样例 #1

### 输入

```
2
7 4
1 0 1 1 0 1 0
4 0 0 -1 0 -1 0
1 2
1 3
1 4
3 5
3 6
3 7
5 11
1 2 5 2 1
-11 -2 -6 -2 -1
1 2
1 3
1 4
3 5```

### 输出

```
YES
YES```

## 样例 #2

### 输入

```
2
4 4
1 1 1 1
4 1 -3 -1
1 2
1 3
1 4
3 13
3 3 7
13 1 4
1 2
1 3```

### 输出

```
NO
NO```

# AI分析结果

### 题目翻译
#### 博格丹叔叔与国家幸福指数

### 题目描述
博格丹叔叔在弗林特船长的船员队伍里已经很长时间了，有时他会怀念自己的祖国。今天他给你讲述了他的国家是如何引入幸福指数的。

这个国家有 $n$ 个城市和 $n - 1$ 条无向道路，这些道路连接着不同的城市对。任何一个城市的居民都可以通过这些道路到达其他任何城市。城市从 $1$ 到 $n$ 编号，且城市 $1$ 是首都。换句话说，这个国家的城市结构呈树状。

这个国家有 $m$ 位居民。第 $i$ 个城市有 $p_i$ 个人居住，但他们都在首都工作。傍晚时分，所有居民都会沿着最短路径回到自己的家乡城市。

每个人都有自己的心情：有些人离开工作岗位时心情很好，但有些人已经心情不佳。此外，任何人在回家的路上都可能心情变差。如果一个人心情不佳，他的心情不会变好。

每个城市都安装了幸福探测器，用于监测每个经过该城市的人的幸福状况。第 $i$ 个城市的探测器会计算一个幸福指数 $h_i$，即心情好的人数减去心情差的人数。为了简单起见，假设一个人的心情在城市内部不会改变。

幸福探测器仍在研发中，因此在判断一个人的幸福状况时可能会出现错误。一天深夜，当所有居民都成功回到家中后，政府要求博格丹叔叔（该国最优秀的程序员）检查收集到的幸福指数是否正确。

博格丹叔叔成功解决了这个问题。你能做到同样的事情吗？

更正式地说，你需要检查：“是否有可能在所有居民回家后，每个城市 $i$ 的幸福指数恰好等于 $h_i$”。

### 说明/提示
让我们来看第一个样例的第一个测试用例：
（此处省略图片描述）
起初，所有居民都在首都。让我们描述一种可能的场景：
 - 来自城市 $1$ 的人：他住在首都，心情很好；
 - 来自城市 $4$ 的人：他经过了城市 $1$ 和 $4$，他的心情在城市 $1$ 和 $4$ 之间变差了；
 - 来自城市 $3$ 的人：他经过城市 $1$ 和 $3$ 时心情很好；
 - 来自城市 $6$ 的人：他经过了城市 $1$、$3$ 和 $6$，他的心情在城市 $1$ 和 $3$ 之间变差了；

 总体而言：
 - $h_1 = 4 - 0 = 4$；
 - $h_2 = 0$；
 - $h_3 = 1 - 1 = 0$；
 - $h_4 = 0 - 1 = -1$；
 - $h_5 = 0$；
 - $h_6 = 0 - 1 = -1$；
 - $h_7 = 0$。

 第一个测试的第二个用例：
（此处省略图片描述）
所有居民在首都时就已经心情不佳——这是唯一可能的场景。

 第二个测试的第一个用例：
（此处省略图片描述）
第二个测试的第二个用例：
（此处省略图片描述）
可以证明，在第二个测试的两个用例中，都无法达到给定的幸福指数。

### 样例 #1
#### 输入
```
2
7 4
1 0 1 1 0 1 0
4 0 0 -1 0 -1 0
1 2
1 3
1 4
3 5
3 6
3 7
5 11
1 2 5 2 1
-11 -2 -6 -2 -1
1 2
1 3
1 4
3 5
```
#### 输出
```
YES
YES
```

### 样例 #2
#### 输入
```
2
4 4
1 1 1 1
4 1 -3 -1
1 2
1 3
1 4
3 13
3 3 7
13 1 4
1 2
1 3
```
#### 输出
```
NO
NO
```

### 题解综合分析与结论
这些题解主要围绕如何判断给定的幸福指数是否合法展开，核心思路都是基于树结构进行深度优先搜索（DFS）。

#### 思路对比
- 多数题解先通过一次 DFS 计算经过每个城市的人数，再根据幸福指数公式计算好心情和坏心情的人数，最后通过第二次 DFS 检查幸福指数的合法性。
- 部分题解将问题转换为反向思考，从叶子节点向上合并，尽可能让更多人伤心，再结合幸福指数判断是否合理。

#### 算法要点
- **计算经过人数**：利用 DFS 回溯计算子树权值和，得到经过每个城市的人数。
- **计算心情人数**：根据幸福指数公式 $good + bad = 总人数$，$good - bad = h[i]$，计算好心情和坏心情的人数。
- **合法性检查**：检查幸福指数的绝对值是否超过总人数、总人数与幸福指数的奇偶性是否相同、子节点好心情人数总和是否超过父节点等。

#### 解决难点
- **处理心情变化规则**：根据“心情好可以变差，但心情差不能变好”的规则，确保子节点好心情人数总和不超过父节点。
- **边界条件判断**：判断总人数与幸福指数的奇偶性、好心情和坏心情人数是否为负数等边界条件。

### 高评分题解
- **作者：fls233666（5星）**
    - **关键亮点**：思路清晰，详细阐述了判断幸福指数不合法的三条规则，并给出了完整的代码实现，代码注释丰富，可读性强。
    - **核心代码**：
```cpp
void dfs1(int rp){  //第一轮深度优先搜索
    for(rgt i=lst[rp];i;i=nxt[i]){
        if(!fw[to[i]]){
            fw[to[i]]=true;
            dfs1(to[i]);
            p[rp]+=p[to[i]];
        }
    }
}

void ck(int rp){   //第二轮深度优先搜索
    if(h[rp]>=0)
        hp[rp]+=h[rp];
    else
        h[rp]=-h[rp];
    if(h[rp]>p[rp]){
        ans=false;
        return;
    }
    if((p[rp]-h[rp])%2){
        ans=false;
        return;
    }else{
        hp[rp]+=(p[rp]-h[rp])/2;
        int s=0;
        for(rgt i=lst[rp];i;i=nxt[i]){
            if(!fw[to[i]]){
                fw[to[i]]=true;
                ck(to[i]);
                if(!ans) return;
                s+=hp[to[i]];
            }
        }
        if(hp[rp]-s<0){
            ans=false;
            return;
        }
    }
}
```
- **作者：F_Mu（4星）**
    - **关键亮点**：将问题转换为反向思考，从叶子节点向上合并，思路独特，代码简洁，使用了 C++ 的一些高级特性进行优化。
    - **核心代码**：
```cpp
pii dfs(int now, int pre) {
    if (!flag)
        return {0, 0};
    pii p = {0, a[now]};
    for (auto &to:v[now]) {
        if (to == pre)
            continue;
        pii tmp = dfs(to, now);
        p.first += tmp.first;
        p.second += tmp.second;
    }
    int x = p.first + p.second + h[now];
    if (x & 1) {
        flag = false;
        return {0, 0};
    }
    x /= 2;
    if (x < p.first || x > p.first + p.second) {
        flag = false;
        return {0, 0};
    }
    return pii{x, p.first + p.second - x};
}
```
- **作者：Isshiki_Hugh（4星）**
    - **关键亮点**：详细说明了两遍 DFS 的作用和实现过程，对计算好心情和坏心情人数的公式进行了明确推导，代码结构清晰。
    - **核心代码**：
```cpp
inline void dfs(int now,int father){
    val[now] = p[now];
    for(int i = head[now];i;i = next[i]){
        if(ver[i] == father) continue;
        dfs(ver[i],now);
        val[now] += val[ ver[i] ];
    }
}

inline bool check(int now,int father,int num_H){
    bool flag = true;
    int num_happy,num_unhappy,num_now = val[now];
    num_now -= h[now];
    if(num_now % 2 || num_now < 0) return false;
    else num_now /= 2;
    num_happy = num_now + h[now], num_unhappy = num_now;
    back[father] += num_happy;
    if(num_happy > num_H || num_happy < 0 || num_unhappy < 0) return false;
    for(int i = head[now];i;i = next[i]){
        if(ver[i] == father) continue;
        flag &= check(ver[i],now,num_happy);
        if(!flag) return false;
    }
    if(back[now] > num_happy) return false;
    return true;
}
```

### 最优关键思路或技巧
- **深度优先搜索**：利用 DFS 遍历树结构，计算经过每个城市的人数和检查幸福指数的合法性。
- **数学推导**：通过幸福指数公式计算好心情和坏心情的人数，并利用奇偶性和边界条件进行合法性检查。
- **反向思考**：将问题转换为反向思考，从叶子节点向上合并，简化问题的处理。

### 拓展思路
同类型题或类似算法套路包括树的遍历、树上差分、贪心算法等。在处理树结构问题时，可以考虑使用 DFS 或 BFS 进行遍历，结合数学推导和贪心策略解决问题。

### 推荐题目
- [P1364 医院设置](https://www.luogu.com.cn/problem/P1364)：考察树的遍历和距离计算。
- [P1122 最大子树和](https://www.luogu.com.cn/problem/P1122)：涉及树的动态规划和子树权值计算。
- [P2016 战略游戏](https://www.luogu.com.cn/problem/P2016)：需要运用树的遍历和贪心算法解决问题。

### 个人心得摘录与总结
- **作者：两年打铁**：一开始看错了题目，以为每个人出发时都是开心的，直到经过一条边后才可以变。这提醒我们在做题时要仔细阅读题目，避免因理解错误而浪费时间。
- **作者：白鲟**：考场上一开始拿到这道题的时候是蒙的，做了 D 题之后回来猛然发现一个事实：知道人数和好坏情绪人数之差时，是可以直接算出坏情绪人数的。这说明在遇到难题时，可以先尝试做其他题目，换个思路后可能会有新的发现。

---
处理用时：58.33秒