# 题目信息

# [NERC 2018] Easy Chess

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) E 题。

## 题目描述

Elma 正在学习象棋。

Elma 是个新手，她还不特别了解象棋是如何下的，所以，为了更好地让她了解象棋，她的奶奶让她从一个棋盘（如下图）中进行 $n$ 次移动，每次移动只能是水平或垂直地移动若干个格子的，且每个点只能到达一次，使得从 a1 到 h8 处。

![](https://cdn.luogu.com.cn/upload/image_hosting/zlooykdb.png)

## 说明/提示

对于所有数据保证 $2 \leq n \leq 63$ 且保证存在至少一种合法方案。

## 样例 #1

### 输入

```
4```

### 输出

```
a1 f1 c1 c8 h8```

# AI分析结果

### 算法分类
深度优先搜索 DFS

### 综合分析与结论
本题要求从棋盘左下角 a1 移动到右上角 h8，且每个点只能经过一次，恰好走 n 步。由于棋盘较小（8x8），且 n 的范围在 2 到 63 之间，DFS 是一个合适的算法选择。大多数题解都采用了 DFS 的思路，通过枚举每一步的移动方向和步数，回溯寻找合法路径。部分题解还结合了打表或数学构造的方法来优化性能。

### 所选题解

#### 1. 题解作者：Spark_King (赞：6)
- **星级**: 4.5
- **关键亮点**: 使用了标准的 DFS 算法，代码结构清晰，注释详细，且对步数限制的处理非常到位。
- **个人心得**: 作者提到“步数超过要求时返回”这一点非常重要，否则容易超时。
- **核心代码**:
```cpp
void dfs(int x, int y) {
    if (x == 8 && y == 8 && cnt == n) {
        for (int i = 1; i <= n; i++) {
            char c = 'a' + (char)(step[i][1] - 1);
            cout << c << step[i][2] << " ";
        }
        flag = 1;
        return;
    }
    if (cnt == n) return;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 7; j++) {
            int kx = x + dx[i] * j, ky = y + dy[i] * j;
            if (kx > 8 || kx < 1 || ky > 8 || ky < 1) continue;
            if (mp[kx][ky] == 0) {
                mp[kx][ky] = 1;
                cnt++;
                step[cnt][1] = kx, step[cnt][2] = ky;
                dfs(kx, ky);
                cnt--;
                mp[kx][ky] = 0;
                if (flag == 1) return;
            }
        }
    }
    return;
}
```

#### 2. 题解作者：lbh666 (赞：2)
- **星级**: 4
- **关键亮点**: 通过数学分析和蛇形方阵的构造，将问题分为三种情况处理，代码简洁且高效。
- **核心代码**:
```cpp
void solve() {
    while (m--) {
        if (!flag) y++;
        else y--;
        if (y > 8) y = 8, flag = 1, x++;
        if (y < 1) y = 1, flag = 0, x++;
        print(x, y);
    }
}
```

#### 3. 题解作者：linyukun (赞：0)
- **星级**: 4
- **关键亮点**: 通过分类讨论，将问题分为三种情况，分别处理，思路清晰且易于理解。
- **核心代码**:
```cpp
if (n <= 50) {
    for (int i = 1; i <= n - 1; i++) {
        cout << s1[i] << " ";
    }
    cout << s1[n - 1][0] << "8 h8";
} else if (n <= 56) {
    for (int i = 1; i <= 49; i++) {
        cout << s1[i] << " ";
    }
    cout << "g8 ";
    n -= 50;
    for (int i = 1; i <= n; i++) {
        cout << char('g' - i) << "8 ";
    }
    cout << "h8";
} else {
    for (int i = 1; i <= 6; i++) {
        if (i & 1) {
            for (int j = 'a'; j <= 'h'; j++) {
                cout << char(j) << i << " ";
            }
        } else {
            for (int j = 'h'; j >= 'a'; j--) {
                cout << char(j) << i << " ";
            }
        }
    }
    cout << "a7 b7 c7 d7 e7 f7 h7 g7 g8 ";
    n -= 57;
    for (int i = 1; i <= n; i++) {
        cout << char('g' - i) << "8 ";
    }
    cout << "h8";
}
```

### 最优关键思路或技巧
1. **DFS 回溯**: 通过 DFS 枚举每一步的移动方向和步数，回溯寻找合法路径。
2. **数学构造**: 通过数学分析和蛇形方阵的构造，将问题分为几种情况处理，减少搜索空间。
3. **分类讨论**: 根据 n 的不同范围，采用不同的策略，提高算法效率。

### 可拓展之处
- **类似问题**: 类似的问题可以扩展到更大的棋盘或更复杂的移动规则，如国际象棋中的其他棋子移动方式。
- **优化思路**: 对于更大的棋盘，可以考虑使用 A* 算法或其他启发式搜索算法来优化性能。

### 推荐题目
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
2. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

---
处理用时：32.77秒