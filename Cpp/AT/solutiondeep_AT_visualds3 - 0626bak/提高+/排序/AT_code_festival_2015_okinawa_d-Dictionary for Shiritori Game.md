# 题目信息

# Dictionary for Shiritori Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-okinawa-open/tasks/code_festival_2015_okinawa_d



## 说明/提示

### Problem

In a country where $ N $ different kinds characters are being used, there is a dictionary that contains $ M $ entries, each entry is a definition for a word. All the kinds of characters are listed as character $ 1 $, character $ 2 $, ..., character $ N $. The $ i_{th} $ entry (as a word) of this dictionary begins with the letter $ p_i $, and ends with the letter $ q_i $.

 Cat Snuke and Wolf Sothe will use this dictionary to play a game called **Shiritori** . (Please note that Shiritori in this game is different from a normal Shiritori game.)

- The first move will be made by Cat Snuke, then two players will move alternately.
- For the first move, the player in turn has to say a word the begins with character $ 1 $. If there are no any words that begin with character $ 1 $, the player in turn loses.
- For the rest moves, the player of that turn has to say any word that begins with the last character of the word being said in the previous move from the dictionary. If there is not any appropriate word, the player in turn loses.
- **Any word can be said any number of times** .

There should be some dictionaries that two players can not change the result of the game even if they tried their best. For these dictionaries, in this case, we want to find out if the first player or the second player will win, or even the game will never halt.

All the words in the dictionary will be given. We can assume that the two players will try their best. Please decide if the first player (Cat Snuke) or the second player (Wolf Sothe) will win, or even the game will never halt.

### Sample Explanation 1

\- For the first move, Cat Snuke has to say the first word. - For the second move, if Wolf Sothe said the 6th word, Cat Snuke will have no appropriate word to say for the next move, thus Wolf Sothe wins.

### Sample Explanation 4

Please note that for the first move it is possible that there is no appropriate word that can be said.

## 样例 #1

### 输入

```
6 5

1 2

2 3

3 4

4 2

2 5```

### 输出

```
Sothe```

## 样例 #2

### 输入

```
6 6

1 2

2 3

3 4

4 2

2 5

5 6```

### 输出

```
Draw```

## 样例 #3

### 输入

```
6 8

1 2

1 3

3 4

3 5

2 1

4 5

4 6

5 6```

### 输出

```
Snuke```

## 样例 #4

### 输入

```
4 8

2 3

2 3

3 4

4 1

3 1

2 2

4 2

4 3```

### 输出

```
Sothe```

# AI分析结果



# 算法分类：博弈论与图论（反向图拓扑排序）

---

## 题解思路与难点分析

**核心思路**  
将每个字符视为图的节点，单词视为边。游戏规则转化为：从节点1出发，两人轮流沿边移动。无法移动者输。需判断先手胜负或平局。

**算法要点**  
1. **反向图构建**：将原边 `p→q` 转换为反向边 `q→p`，便于从终局状态逆推。
2. **拓扑排序**：初始化出度为0的节点为必败态，通过队列处理状态传播。
3. **必胜/必败态判定**：
   - 若当前节点必败，则其前驱节点必胜。
   - 若某节点的所有出边都指向必胜态，则该节点必败。

**解决难点**  
- 环的处理：未参与拓扑排序的节点状态未定，对应无限循环的平局情况。
- 高效状态传播：通过队列和入度计数实现O(m+n)时间复杂度。

---

## 题解评分（≥4星）

1. **Daniel_7216（4.5星）**  
   - **亮点**：简洁的BFS实现，明确状态转移条件。
   - **代码**：反向图处理清晰，`vis`数组直接表示状态。
2. **AutumnKite（4.5星）**  
   - **亮点**：拓扑排序与反向图结合，状态标记系统严谨。
   - **代码**：使用`f`数组区分三种状态，注释详细。
3. **YY_rainbow（4星）**  
   - **亮点**：与洛谷P6560双倍经验，变量命名直观。
   - **代码**：`deg`数组维护入度，处理逻辑与注释对应。

---

## 最优思路与技巧

**关键技巧**  
- **反向图拓扑排序**：避免环干扰，确保确定态节点优先处理。
- **入度计数优化**：通过入度归零判断是否所有出边已处理。
- **状态传播规则**：必败态触发前驱必胜，必胜态触发前驱入度减少。

**代码实现（Daniel_7216版核心逻辑）**  
```cpp
void bfs() {
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : G[x]) { // 反向图中x的后继（原图前驱）
            if (vis[x] == 1) cnt[y]--; // 必胜态触发前驱入度减
            if (vis[y] != -1) continue;
            if (cnt[y] == 0) { // 前驱入度归零，必败
                vis[y] = 0; q.push(y);
            }
            if (vis[x] == 0) { // 当前必败，前驱必胜
                vis[y] = 1; q.push(y);
            }
        }
    }
}
```

---

## 类似题目与算法套路

1. **洛谷P6560**：几乎相同题意，直接套用反向图拓扑解法。
2. **DAG上的博弈动态规划**：如P4017（食物链计数），利用拓扑序递推。
3. **SG函数应用**：如NIM游戏变种，将节点状态与SG值关联。

---

## 推荐题目

1. **P6560**（反向图拓扑排序，双倍经验）
2. **P3183**（DAG拓扑排序与路径计数）
3. **P2572**（博弈SG函数与状态分析）

---

## 可视化算法设计

**动画方案**  
- **Canvas绘制**：网格布局，节点用不同颜色（红：必败，绿：必胜，灰：未定）。
- **步进控制**：单步显示队列处理节点，高亮当前节点与传播边。
- **状态更新**：用箭头标记反向边，动态显示入度减少过程。

**复古像素风格**  
- **8位音效**：节点入队时播放“滴”声，状态确定时播放“嘟”声。
- **自动演示模式**：模拟AI决策路径，背景播放FC风格音乐。

**交互功能**  
- 速度调节：滑动条控制动画速度。
- 环高亮：点击环节点时闪烁提示平局条件。

---

## 核心代码（Daniel_7216完整版）

```cpp
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n, m, vis[100001], cnt[100001];
vector<int> G[100001];
queue<int> q;

void bfs() {
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int y : G[x]) {
            if (vis[x] == 1) cnt[y]--;
            if (vis[y] != -1) continue;
            if (cnt[y] == 0) {
                vis[y] = 0; q.push(y);
            }
            if (vis[x] == 0 && vis[y] == -1) {
                vis[y] = 1; q.push(y);
            }
        }
    }
}

int main() {
    memset(vis, -1, sizeof(vis));
    scanf("%d%d", &n, &m);
    for (int i=0, a,b; i<m; ++i) {
        scanf("%d%d", &a, &b);
        G[b].push_back(a); // 反向建边
        cnt[a]++; // 原图出度计数
    }
    for (int i=1; i<=n; ++i)
        if (cnt[i] == 0) { // 原图出度0，必败
            vis[i] = 0; q.push(i);
        }
    bfs();
    if (vis[1] == 1) printf("Snuke");
    else if (vis[1] == 0) printf("Sothe");
    else printf("Draw");
    return 0;
}
```

---
处理用时：189.92秒