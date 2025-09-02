# 题目信息

# Songs Compression

## 题目描述

Ivan has $ n $ songs on his phone. The size of the $ i $ -th song is $ a_i $ bytes. Ivan also has a flash drive which can hold at most $ m $ bytes in total. Initially, his flash drive is empty.

Ivan wants to copy all $ n $ songs to the flash drive. He can compress the songs. If he compresses the $ i $ -th song, the size of the $ i $ -th song reduces from $ a_i $ to $ b_i $ bytes ( $ b_i < a_i $ ).

Ivan can compress any subset of the songs (possibly empty) and copy all the songs to his flash drive if the sum of their sizes is at most $ m $ . He can compress any subset of the songs (not necessarily contiguous).

Ivan wants to find the minimum number of songs he needs to compress in such a way that all his songs fit on the drive (i.e. the sum of their sizes is less than or equal to $ m $ ).

If it is impossible to copy all the songs (even if Ivan compresses all the songs), print "-1". Otherwise print the minimum number of songs Ivan needs to compress.

## 说明/提示

In the first example Ivan can compress the first and the third songs so after these moves the sum of sizes will be equal to $ 8 + 7 + 1 + 5 = 21 \le 21 $ . Also Ivan can compress the first and the second songs, then the sum of sizes will be equal $ 8 + 4 + 3 + 5 = 20 \le 21 $ . Note that compressing any single song is not sufficient to copy all the songs on the flash drive (for example, after compressing the second song the sum of sizes will be equal to $ 10 + 4 + 3 + 5 = 22 > 21 $ ).

In the second example even if Ivan compresses all the songs the sum of sizes will be equal $ 8 + 4 + 1 + 4 = 17 > 16 $ .

## 样例 #1

### 输入

```
4 21
10 8
7 4
3 1
5 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 16
10 8
7 4
3 1
5 4
```

### 输出

```
-1
```

# AI分析结果



# Songs Compression

## 题目描述

Ivan 的手机上有 $n$ 首歌曲，第 $i$ 首歌曲的原始大小为 $a_i$ 字节。他有一个最多能存储 $m$ 字节的 U 盘，初始为空。

Ivan 想将所有歌曲拷贝到 U 盘。他可以对任意数量的歌曲进行压缩，压缩后第 $i$ 首歌曲的大小会从 $a_i$ 减少到 $b_i$ 字节（保证 $b_i < a_i$）。需要求出满足总存储量不超过 $m$ 的前提下，最少需要压缩多少首歌曲。若无法满足条件（即使压缩全部歌曲），则输出 "-1"。

## 说明/提示

样例1中压缩前两首歌后总大小为 $20 \le 21$。样例2中即使压缩所有歌曲总大小仍为 $17 > 16$，故输出 -1。

---

**算法分类**：贪心

---

### 综合题解分析

所有题解均采用贪心策略：按歌曲压缩空间 $(a_i - b_i)$ 降序排序，优先压缩节省空间最多的歌曲。关键步骤如下：
1. 特判：若所有歌曲压缩后总和仍超过 $m$ → 输出 -1
2. 若未压缩时总和已满足 → 输出 0
3. 排序后逐步压缩，直到总大小 ≤ $m$，记录压缩次数

#### 最优思路与技巧
- **贪心排序**：按 $(a_i - b_i)$ 降序选择
- **数据类型**：总和可能超过 int 范围，需用 long long
- **特判优化**：优先处理边界情况避免无效计算

---

### 精选题解（评分≥4星）

#### 题解1 - Pethly_Cat（5星）
**亮点**：
- 完整处理边界条件与数据类型问题
- 代码结构清晰，注释明确
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,sum1,sum2;
struct node { long long x,y; } a[100001];
bool cmp(node a, node b) { return a.x - a.y > b.x - b.y; }

int main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        cin >> a[i].x >> a[i].y;
        sum1 += a[i].y;   // 压缩后的总和
        sum2 += a[i].x;   // 原始总和
    }
    if(sum1 > m) { cout << -1; return 0; }
    
    sort(a+1, a+n+1, cmp);
    for(int i=1; i<=n; i++) {
        if(sum2 <= m) { cout << i-1; return 0; }
        sum2 -= a[i].x - a[i].y; // 压缩当前歌曲
    }
    cout << n; // 全部压缩才满足条件
}
```

#### 题解2 - FQR_（4星）
**亮点**：
- 变量命名直观（sum表示当前总和）
- 精简处理排序逻辑
```cpp
struct node{ int a,b; } songs[100001];
bool cmp(node x, node y) { return x.a-x.b > y.a-y.b; }

int main() {
    long long sum = 0;
    for(int i=0; i<n; i++) sum += songs[i].a;
    sort(songs, songs+n, cmp);
    
    int cnt = 0;
    while(sum > m && cnt < n) {
        sum -= songs[cnt].a - songs[cnt].b;
        cnt++;
    }
    cout << (sum <= m ? cnt : -1);
}
```

#### 题解3 - Apro1066（4星）
**亮点**：
- 使用结构体存储数据，增强可读性
- 单独计算"空间差"变量优化判断
```cpp
typedef struct { ll a,b,dc; } lxydl;
lxydl song[100001];
bool cmp(lxydl a, lxydl b) { return a.dc > b.dc; }

int main() {
    ll space = sum1 - m; // 需要减少的总空间
    sort(song+1, song+n+1, cmp);
    for(int i=1; i<=n; i++) {
        if(s >= space) break;
        s += song[i].dc; // 累计节省的空间
        cnt++;
    }
    cout << cnt;
}
```

---

### 关键实现总结
1. **排序核心**：`sort(a, a+n, [](x,y){ return x.a-x.b > y.a-y.b; })`
2. **逐步压缩**：从最大节省开始，逐次减少总大小
3. **边界处理**：特判全压缩和无需压缩的情况

---

### 拓展建议
类似贪心问题可练习：
1. [P1209 修理牛棚](https://www.luogu.com.cn/problem/P1209) - 区间选择策略
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 优先队列优化
3. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995) - 极值交替选择

---
处理用时：54.28秒