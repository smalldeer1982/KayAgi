# 题目信息

# [USACO23DEC] Target Practice S

## 题目描述

Bessie 是一只仿生牛。在一条数轴上，她正尝试命中 $T$（$1 \leq T \leq 10^5$）个位于不同位置的靶子。Bessie 在位置 $0$ 开始行动，并遵循一个长度为 $C$（$1 \leq C \leq 10^5$）的命令序列，序列由 `L`、`F` 和 `R` 组成：

- `L`：Bessie 向左移动一个单位距离。
- `R`：Bessie 向右移动一个单位距离。
- `F`：Bessie 开枪。如果有一个靶子在 Bessies 当前的位置，这个靶子将被命中并摧毁。它不可以再次被命中。

如果在 Bessie 开始前，你被允许修改序列中的至多一条命令，Bessie 最多可以命中多少靶子？

## 说明/提示

### 样例解释 1

如果你对命令序列不做任何修改，Bessie 将命中两个靶子。

| 命令 | 位置 | 命中的靶子数目 |
| :----------- | :----------- | :----------- |
| Start | 0 | 0 |
| L | -1 | 0 |
| F | -1 | 1 |
| F | -1 | 1（无法摧毁靶子超过 1 次） |
| R | 0 | 1 |
| F | 0 | 2 |
| R | 1 | 2 |
| R | 2 | 2 |

如果你将最后一条命令由 `R` 修改为 `F`，Bessie 将命中三个靶子：

| 命令 | 位置 | 命中的靶子数目 |
| :----------- | :----------- | :----------- |
| Start | 0 | 0 |
| L | -1 | 0 |
| F | -1 | 1 |
| F | -1 | 1（无法摧毁靶子超过 1 次） |
| R | 0 | 1 |
| F | 0 | 2 |
| R | 1 | 2 |
| F | 1 | 3 |

### 样例解释 2

如果命令序列不修改，在位置 $0$ 的唯一一个靶子将被命中。

由于一个靶子不能被多次摧毁，答案为 $1$。

### 测试点性质

- 测试点 $4-6$ 满足 $T,C \le 1000$。
- 测试点 $7-15$ 没有额外限制。

## 样例 #1

### 输入

```
3 7
0 -1 1
LFFRFRR```

### 输出

```
3```

## 样例 #2

### 输入

```
1 5
0
FFFFF```

### 输出

```
1```

## 样例 #3

### 输入

```
5 6
1 2 3 4 5
FFRFRF```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过枚举修改命令的位置和修改方式，计算不同情况下命中靶子的数量，从而找出最大值。各题解在具体实现上有所差异，主要体现在数据结构的选择和计算命中靶子数量的方法上。部分题解使用了数组、`set`、`map`、`bitset` 等数据结构来记录靶子位置、命中情况和偏移量等信息。

### 所选题解
- **作者：naoliaok_lovely (赞：13)，4星**
    - **关键亮点**：思路清晰，通过多个函数分别处理不同的修改情况，代码结构清晰，易于理解。使用指针技巧将下标值域从 `[0,2N)` 变为 `[-N,N)`，方便处理负数位置。
- **作者：Nuyoah_awa (赞：12)，4星**
    - **关键亮点**：详细分析了题目，通过枚举修改点，利用 `set` 和 `map` 记录开火点和靶子信息，考虑了各种细节，时间复杂度为 $\mathcal{O}(C \log C)$。
- **作者：0000pnc (赞：3)，4星**
    - **关键亮点**：先预处理出未修改时的答案，然后枚举偏移长度，从右往左扫描，直接维护命中靶子的数量，时间复杂度为 $\mathcal{O}(c)$。

### 重点代码及核心实现思想
#### 作者：naoliaok_lovely
```cpp
void get()
{
    pos = res = 0;
    memset(Cnt, 0, sizeof(Cnt));
    for(int i = 1; i <= m; i++)
        if(c[i] == 'L') pos--;
        else if(c[i] == 'R') pos++;
        else if(++cnt[pos] == 1 && x[pos]) res++;
    ans = max(res, ans);
}

void get_l_to_r()
{
    get();
    for(int i = m; i; i--)
        if(c[i] == 'L') pos++, ans = max(ans, res);
        else if(c[i] == 'R') pos--;
        else
        {
            if(!--cnt[pos] && x[pos]) res--;
            if(++cnt[pos + 2] == 1 && x[pos + 2]) res++;
        }
}
// 其他修改情况的函数类似
```
核心思想：`get` 函数计算不修改命令时命中的靶子数量，`get_l_to_r` 等函数分别处理不同的修改情况，通过更新 `pos` 和 `cnt` 数组来计算命中的靶子数量。

#### 作者：Nuyoah_awa
```cpp
for(int i = 1;i <= c;i++)
{
    if(s[i] == 'L')
    {
        now--;
    }
    else if(s[i] == 'R')
    {
        now++;
    }
    else
    {
        if(mp[now - 2]) st[1][now - 2]++, se[1].insert(now - 2);
        if(mp[now - 1]) st[2][now - 1]++, se[2].insert(now - 1);
        if(mp[now]) st[3][now]++, se[3].insert(now);
        if(mp[now + 1]) st[4][now + 1]++, se[4].insert(now + 1);
        if(mp[now + 2]) st[5][now + 2]++, se[5].insert(now + 2);
    }
}
ans = max(ans, (int)(se[3].size()));
st[3].clear(), se[3].clear();
now = 0;
for(int i = 1;i <= c;i++)
{
    if(s[i] == 'L')
    {
        ans = max(ans, (int)(se[3].size() + max(se[4].size() + (mp[now] && se[3].count(now) == 0 && se[4].count(now) == 0), se[5].size())));
        now--;
    }
    else if(s[i] == 'R')
    {
        ans = max(ans, (int)(se[3].size() + max(se[1].size(), se[2].size() + (mp[now] && se[3].count(now) == 0 && se[2].count(now) == 0))));
        now++;
    }
    else
    {
        se[1].erase(now);
        se[2].erase(now);
        se[4].erase(now);
        se[5].erase(now);
        if(--st[1][now-2] <= 0) se[1].erase(now-2);
        if(--st[2][now-1] <= 0) se[2].erase(now-1);
        if(--st[4][now+1] <= 0) se[4].erase(now+1);
        if(--st[5][now+2] <= 0) se[5].erase(now+2);
        ans = max(ans, (int)(se[3].size() + max(se[2].size(), se[4].size())));
        if(mp[now]) st[3][now]++, se[3].insert(now);
    }
}
```
核心思想：先预处理出偏移量为 `1~2` 的开火点的集合，然后枚举修改点，根据修改点的命令类型更新答案，同时注意删除已命中的靶子和“过期”的开火点。

#### 作者：0000pnc
```cpp
void init() {
    memset(buc, 0, sizeof buc);
    int now = c + 10; cnt = 0;
    for (int i = 1; i <= c; i++) {
        if (s[i] == 'L') now--;
        if (s[i] == 'R') now++;
        if (s[i] == 'F') {
            if (vis[now]) {
                if (!buc[now]) cnt++;
                buc[now]++;
            }
        }
        pos[i] = now;
    }
}

int work2() { // 2
    init(); int ans = 0;
    for (int i = c; i; i--) {
        if (s[i] == 'F') {
            buc[pos[i]]--;
            if (!buc[pos[i]]) cnt--;
            if (vis[pos[i] + 2]) {
                if (!buc[pos[i] + 2]) cnt++;
                buc[pos[i] + 2]++;
            }
        }
        if (s[i] == 'L') ans = max(ans, cnt);
    }
    return ans;
}
// 其他偏移情况的函数类似
```
核心思想：`init` 函数预处理出未修改时的答案，`work2` 等函数枚举偏移长度，从右往左扫描，通过更新 `buc` 数组来计算命中的靶子数量。

### 最优关键思路或技巧
- **枚举修改情况**：通过枚举修改命令的位置和修改方式，计算不同情况下命中靶子的数量，找出最大值。
- **预处理和维护信息**：预处理出未修改时的答案和偏移量为 `1~2` 的开火点的集合，在枚举修改点时，根据修改点的命令类型更新答案，同时注意删除已命中的靶子和“过期”的开火点。
- **使用合适的数据结构**：使用数组、`set`、`map`、`bitset` 等数据结构来记录靶子位置、命中情况和偏移量等信息，方便计算和更新。

### 可拓展之处
同类型题可能会有更多的命令类型、更多的修改次数或更复杂的规则。类似算法套路可以是枚举所有可能的操作，预处理出一些信息，然后在枚举过程中根据操作类型更新信息，计算最终结果。

### 推荐题目
- [P1002 [NOIP2002 普及组] 过河卒](https://www.luogu.com.cn/problem/P1002)
- [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)

### 个人心得
- **作者：Nuyoah_awa**：纯开 `5` 个 `set` 然后删的话，会获得 `70 ~ 76` pts 的成绩，需要注意维护后面的 `set` 时不仅要把之前打过的删掉，还要把“过期”的部分删掉，对于将 `L` 或 `R` 改成 `F`，当前这个点需要计入答案，要注意判断条件。
- **作者：strcmp**：usaco 的评测机比较慢，`bitset` 赛时会 T，在洛谷上没到 `500ms`，可以通过优化后缀状态的计算来降低时间复杂度。

---
处理用时：63.10秒