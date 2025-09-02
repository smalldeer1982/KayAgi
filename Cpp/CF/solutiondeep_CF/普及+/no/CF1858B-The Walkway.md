# 题目信息

# The Walkway

## 题目描述

There are $ n $ benches near the Main Walkway in Summer Infomatics School. These benches are numbered by integers from $ 1 $ to $ n $ in order they follow. Also there are $ m $ cookie sellers near the Walkway. The $ i $ -th ( $ 1 \le i \le m $ ) cookie sellers is located near the $ s_i $ -th bench.

Petya is standing in the beginning of the Walkway. He will pass near all benches starting from the $ 1 $ -st bench and ending with the $ n $ -th bench. Petya passes the distance between two consecutive benches in $ 1 $ minute. He has a knapsack with an infinite amount of cookies. Petya is going to eat cookies from his knapsack and buy them from cookie sellers during the walk.

Petya eats cookies only near the benches according to the following rule: he will eat the cookie near the $ i $ -th ( $ 1 \le i \le n $ ) bench if and only if at least one of the following conditions holds:

- There is a cookie seller near the $ i $ -th bench. Then Petya will buy a cookie from cookie seller and eat it immediately.
- Petya has not yet eaten a cookie. Then Petya will take a cookie from his knapsack and eat it immediately.
- At least $ d $ minutes passed since Petya ate the previous cookie. In other words, Petya has not eaten a cookie near the benches $ i-1, i-2, \ldots, \max(i-d+1, 1) $ . Then Petya will take a cookie from his knapsack and eat it immediately.

You may assume that Petya eats cookies instantly. Petya will not eat two or more cookies near the same bench.

You want to minimize the number of cookies Petya will eat during his walk. In order to do this, you will ask the administration of the Summer Informatics School to remove exactly one cookie seller from the Walkway before Petya starts his walk.

Please determine the minimum possible number of cookies Petya can eat after removing exactly one cookie seller. Also determine the number of cookie sellers, such that if you remove one of them, Petya will eat the minimum possible number of cookies.

## 说明/提示

In the first test case $ n=6 $ , $ m=2 $ , $ d=2 $ and $ s=[2, 5] $ . If no cookie seller is removed, then Petya will eat $ 4 $ cookies during his walk (note that you have to remove exactly one cookie seller; this case is explained only to show how Petya decides whether to eat a cookie):

- Petya will eat a cookie near the $ 1 $ -st bench since he has not yet eaten a cookie.
- Petya will eat a cookie near the $ 2 $ -nd bench since there is a cookie seller near this bench.
- Petya will not eat a cookie near the $ 3 $ -rd bench since only $ 1<d $ minute passed since he ate a cookie.
- Petya will eat a cookie near the $ 4 $ -th bench since $ 2\ge d $ minutes passed since he ate a cookie.
- Petya will eat a cookie near the $ 5 $ -th bench since there is a cookie seller near this bench.
- Petya will not eat a cookie near the $ 6 $ -th bench since only $ 1<d $ minute passed since he ate a cookie.

If the $ 1 $ -st cookie seller is removed, Petya will eat $ 3 $ cookies (near the benches $ 1 $ , $ 3 $ and $ 5 $ ). If the $ 2 $ -nd cookie seller is removed, Petya will eat $ 4 $ cookies (near the benches $ 1 $ , $ 2 $ , $ 4 $ and $ 6 $ ).

Thus, the minimum number of cookies Petya will eat is $ 3 $ ; there is only one cookie seller such that removing it results in minimizing the number of cookies Petya will eat.

In the second test case

- the removal of the $ 1 $ -st or the $ 2 $ -nd cookie seller results in Petya eating $ 5 $ cookies near the benches $ 1 $ , $ 3 $ , $ 5 $ , $ 7 $ , $ 8 $ ;
- the removal of the $ 3 $ -rd cookie seller results in Petya eating $ 4 $ cookies near the benches $ 1 $ , $ 3 $ , $ 5 $ , $ 7 $ .

Note that the second integer you should output is the number of (that is, amount) cookie sellers, not the index of a cookie seller to remove. Thus, the answer to the second test case is 4 1 because there is only one cookie seller such that removing it results in Petya eating four cookies, which is the minimum possible.

In the third test case Petya will eat $ 4 $ cookies no matter what cookie seller is removed.

Note that Petya is not interested in minimizing the number of cookies he will eat, so he eats cookies whenever it is possible under the rule from the statement.

## 样例 #1

### 输入

```
8
6 2 2
2 5
8 3 2
3 5 8
10 4 9
2 8 9 10
30 5 8
6 8 15 24 29
30 5 8
6 8 12 20 27
8 8 3
1 2 3 4 5 6 7 8
2 2 2
1 2
1000000000 3 20000000
57008429 66778899 837653445```

### 输出

```
3 1
4 1
4 4
6 4
5 2
7 7
1 1
51 1```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

在夏季信息学学校的主步行道旁有 $n$ 个长椅，这些长椅按顺序编号为 $1$ 到 $n$。步行道旁还有 $m$ 个卖饼干的人，第 $i$ 个（$1 \le i \le m$）卖饼干的人位于第 $s_i$ 个长椅旁。

Petya 站在步行道的起点，他将从第 $1$ 个长椅开始，依次经过所有长椅，直到第 $n$ 个长椅。Petya 经过两个相邻长椅之间的距离需要 $1$ 分钟。他有一个装有无限多饼干的背包，Petya 在步行过程中会从背包中吃饼干，并从卖饼干的人那里购买饼干。

Petya 只在长椅旁吃饼干，遵循以下规则：

1. 如果第 $i$ 个长椅旁有卖饼干的人，Petya 会从卖饼干的人那里购买一个饼干并立即吃掉。
2. 如果 Petya 还没有吃过饼干，他会从背包中拿出一个饼干并立即吃掉。
3. 如果距离 Petya 上次吃饼干已经过去了至少 $d$ 分钟，即 Petya 没有在第 $i-1, i-2, \ldots, \max(i-d+1, 1)$ 个长椅旁吃饼干，他会从背包中拿出一个饼干并立即吃掉。

假设 Petya 吃饼干的时间可以忽略不计，且他不会在同一个长椅旁吃多个饼干。

你的目标是最小化 Petya 在步行过程中吃的饼干数量。为此，你可以在 Petya 开始步行之前，请求学校管理部门移除恰好一个卖饼干的人。

请确定在移除一个卖饼干的人后，Petya 吃饼干的最小可能数量，并计算有多少个卖饼干的人，移除他们后 Petya 吃的饼干数量达到最小值。

### 算法分类
贪心

### 题解分析与结论

本题的核心是通过移除一个卖饼干的人来最小化 Petya 吃的饼干数量。各题解的思路主要集中在如何计算移除每个卖饼干的人后 Petya 吃的饼干数量，并找到最小值及其对应的方案数。

#### 题解对比
1. **SunnyYuan的题解**：通过分段计算每两个卖饼干的人之间的饼干数量，并利用公式计算移除某个卖饼干的人后的饼干数量。思路清晰，代码实现简洁。
2. **I_am_kunzi的题解**：通过计算两个卖饼干的人之间的距离，并利用公式计算移除某个卖饼干的人后的饼干数量。思路与SunnyYuan类似，但代码实现稍显复杂。
3. **信息向阳花木的题解**：通过观察发现移除一个卖饼干的人最多只能减少一次饼干数量，并利用前缀和后缀数组进行计算。思路简单，但代码实现较为复杂。

#### 最优关键思路
1. **分段计算**：将步行道分为多个区间，每个区间对应两个卖饼干的人之间的部分，计算每个区间内 Petya 吃的饼干数量。
2. **移除影响**：移除一个卖饼干的人后，只影响其前后两个区间的饼干数量，因此只需重新计算这两个区间的饼干数量。
3. **最小化计算**：通过遍历所有卖饼干的人，计算移除每个卖饼干的人后的饼干数量，找到最小值及其对应的方案数。

### 精选题解

#### 1. SunnyYuan的题解（5星）
**关键亮点**：
- 通过分段计算每两个卖饼干的人之间的饼干数量，思路清晰。
- 利用公式计算移除某个卖饼干的人后的饼干数量，代码实现简洁。

**核心代码**：
```cpp
int cnt(int l, int r) {
    int sz = r - l;
    if (sz % d == 0) return sz / d;
    return sz / d + 1;
}

void solve() {
    cin >> n >> m >> d;
    for (int i = 1; i <= m; i++) cin >> s[i];
    bool flag = true;
    if (s[1] != 1) {
        flag = false;
        m++;
        for (int i = m; i >= 2; i--) s[i] = s[i - 1];
        s[1] = 1;
    }
    m++;
    s[m] = n + 1;
    
    int init = 0;
    for (int i = 2; i <= m; i++) init += cnt(s[i - 1], s[i]);
    
    int minn = 0x3f3f3f3f3f3f3f3f, ans = 0;
    for (int i = 2; i < m; i++) {
        int g = init - cnt(s[i - 1], s[i]) - cnt(s[i], s[i + 1]) + cnt(s[i - 1], s[i + 1]);
        if (g < minn) {
            minn = g;
            ans = 1;
        }
        else if (g == minn) ans++;
    }
    if (init < minn && flag) minn = init, ans = 1;
    else if (init == minn && flag) minn = init, ans++;
    cout << minn << ' ' << ans << '\n';
}
```

#### 2. I_am_kunzi的题解（4星）
**关键亮点**：
- 通过计算两个卖饼干的人之间的距离，并利用公式计算移除某个卖饼干的人后的饼干数量。
- 思路与SunnyYuan类似，但代码实现稍显复杂。

**核心代码**：
```cpp
int z1 = cookie[i] - cookie[i - 1] - 1;
int z2 = cookie[i + 1] - cookie[i] - 1;
int z3 = cookie[i + 1] - cookie[i - 1] - 1;
int z4 = z3 / d - z1 / d - z2 / d;
if (z4 < minn) {
    minn = z4;
    possible_minn.clear();
}
if (z4 == minn) {
    possible_minn.push_back(i);
}
```

### 可拓展之处
1. **区间合并**：类似的问题可以通过区间合并的思想来解决，适用于需要计算多个区间内某种操作的影响。
2. **贪心算法**：在需要最小化或最大化某种操作时，贪心算法是一种常用的策略。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：56.58秒