# 题目信息

# Chess Tourney

## 题目描述

Berland annual chess tournament is coming!

Organizers have gathered $ 2·n $ chess players who should be divided into two teams with $ n $ people each. The first team is sponsored by BerOil and the second team is sponsored by BerMobile. Obviously, organizers should guarantee the win for the team of BerOil.

Thus, organizers should divide all $ 2·n $ players into two teams with $ n $ people each in such a way that the first team always wins.

Every chess player has its rating $ r_{i} $ . It is known that chess player with the greater rating always wins the player with the lower rating. If their ratings are equal then any of the players can win.

After teams assignment there will come a drawing to form $ n $ pairs of opponents: in each pair there is a player from the first team and a player from the second team. Every chess player should be in exactly one pair. Every pair plays once. The drawing is totally random.

Is it possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing?

## 样例 #1

### 输入

```
2
1 3 2 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1
3 3
```

### 输出

```
NO
```

# AI分析结果



# Chess Tourney

## 题目描述

Berland年度国际象棋锦标赛即将到来！

组委会已经聚集了 $2·n$ 名棋手，需要将他们分成两个各含 $n$ 人的队伍。第一队由BerOil赞助，第二队由BerMobile赞助。显然，组委会需要保证BerOil赞助的队伍必胜。

因此，组委会需要将 $2·n$ 名棋手分成两个各含 $n$ 人的队伍，使得第一队在随机配对时总能获胜。每位棋手有一个评分 $r_i$，评分高的选手总能击败评分低的选手，若评分相同则胜负随机。问是否存在这样的分组方式？

---

## 题解分析与结论

所有题解均基于以下核心思路：将选手按评分排序后，将前半 $n$ 人分到第二队，后半 $n$ 人分到第一队。若第二队的最大值（排序后的第 $n$ 项）严格小于第一队的最小值（排序后的第 $n+1$ 项），则满足条件。

### 关键思路
1. **排序分界法**：将选手评分排序后，通过比较中间两个元素（第 $n$ 项和第 $n+1$ 项）的大小关系判断可行性。
2. **贪心思想**：最优分组方式是将较大的 $n$ 人作为第一队，较小的 $n$ 人作为第二队，此时只需保证分界线处严格递增即可。

---

## 精选题解（评分≥4星）

### 题解作者：ShineEternal（★★★★☆）
**亮点**：代码简洁高效，直接排序后比较关键分界点。  
**关键代码**：
```cpp
sort(a+1,a+2*n+1);
if(a[n]<a[n+1]) printf("YES\n");
else printf("NO\n");
```

### 题解作者：王炸拆开打（★★★★☆）
**亮点**：指出两种等价判断条件（`a[n] != a[n+1]` 与 `a[n] < a[n+1]`），启发对排序性质的思考。  
**心得**：首次提交因未排序导致错误，提醒读者注意排序的必要性。  
**关键代码**：
```cpp
sort(q+1,q+n+n+1);
if(q[n]!=q[n+1]) printf("YES");
else printf("NO");
```

### 题解作者：Elma_（★★★★☆）
**亮点**：通过数学证明强化思路正确性，明确分界条件。  
**关键代码**：
```cpp
sort(a+1, a+2*n+1);
if(a[n] == a[n+1]) cout<<"NO"<<endl;
else cout<<"YES"<<endl;
```

---

## 拓展与同类题目
- **类似题目套路**：利用排序后的分界性质解决分组问题，如「纪念品分组」「切绳子」等。
- **推荐题目**：
  1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)  
  2. [P1577 切绳子](https://www.luogu.com.cn/problem/P1577)  
  3. [P1152 欢乐的跳](https://www.luogu.com.cn/problem/P1152)

---

## 核心代码实现
```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
int a[210];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + 2 * n + 1);
    printf(a[n] < a[n + 1] ? "YES\n" : "NO\n");
    return 0;
}
```

---
处理用时：114.90秒