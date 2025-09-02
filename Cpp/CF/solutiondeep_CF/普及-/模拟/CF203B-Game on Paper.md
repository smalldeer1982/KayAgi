# 题目信息

# Game on Paper

## 题目描述

One not particularly beautiful evening Valera got very bored. To amuse himself a little bit, he found the following game.

He took a checkered white square piece of paper, consisting of $ n×n $ cells. After that, he started to paint the white cells black one after the other. In total he painted $ m $ different cells on the piece of paper. Since Valera was keen on everything square, he wondered, how many moves (i.e. times the boy paints a square black) he should make till a black square with side $ 3 $ can be found on the piece of paper. But Valera does not know the answer to this question, so he asks you to help him.

Your task is to find the minimum number of moves, till the checkered piece of paper has at least one black square with side of $ 3 $ . Otherwise determine that such move does not exist.

## 样例 #1

### 输入

```
4 11
1 1
1 2
1 3
2 2
2 3
1 4
2 4
3 4
3 2
3 3
4 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
4 12
1 1
1 2
1 3
2 2
2 3
1 4
2 4
3 4
3 2
4 2
4 1
3 1
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 纸上游戏

## 题目描述
在一个并不特别美好的夜晚，瓦莱拉感到非常无聊。为了给自己找点乐子，他想出了以下游戏。

他拿了一张由 $n×n$ 个格子组成的方形白色方格纸。之后，他开始逐个将白色格子涂成黑色。他总共在这张纸上涂了 $m$ 个不同的格子。由于瓦莱拉热衷于一切方形的东西，他想知道，他需要进行多少次操作（即多少次将一个方格涂成黑色），才能在这张纸上找到一个边长为 $3$ 的黑色正方形。但瓦莱拉不知道这个问题的答案，所以他请你帮忙。

你的任务是找出最少的操作次数，使得方格纸上至少有一个边长为 $3$ 的黑色正方形。否则，确定不存在这样的操作次数。

## 样例 #1
### 输入
```
4 11
1 1
1 2
1 3
2 2
2 3
1 4
2 4
3 4
3 2
3 3
4 1
```
### 输出
```
10
```

## 样例 #2
### 输入
```
4 12
1 1
1 2
1 3
2 2
2 3
1 4
2 4
3 4
3 2
4 2
4 1
3 1
```
### 输出
```
-1
```

### 综合分析与结论
这些题解主要围绕如何高效判断在 $n\times n$ 的矩阵中，经过 $m$ 次将指定格子涂黑的操作后，最少第几次操作能形成 $3\times 3$ 的黑色矩阵这一问题展开。
- **思路对比**：
    - 部分题解采用暴力枚举，每次操作后遍历整个矩阵判断是否有 $3\times 3$ 黑色矩阵，时间复杂度为 $O(n^2m)$，会超时。
    - 多数题解进行了优化，利用每次操作只影响当前格子及其周围 $8$ 个格子的特点，判断以这些格子为中心是否形成 $3\times 3$ 黑色矩阵，将时间复杂度优化到 $O(m)$。
    - 还有题解先存储所有操作，再遍历矩阵找出 $3\times 3$ 黑色矩阵中操作步数的最大值的最小值。
- **算法要点**：
    - 优化题解多使用方向数组来遍历周围格子。
    - 部分题解用二维数组记录格子状态和操作步数。
- **解决难点**：主要解决了暴力枚举时间复杂度高的问题，通过缩小判断范围，减少不必要的计算。

### 评分较高的题解
- **作者：qpzc（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用方向数组清晰地遍历周围格子，时间复杂度优化到 $O(m)$。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool mp[1002][1002];
const int dir[9][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y,mp[x][y]=true;
        for(int j=0;j<9;j++){
            int xx=x+dir[j][0],yy=y+dir[j][1];
            bool ok=true;
            for(int k=0;k<9;k++){
                int xxx=xx+dir[k][0],yyy=yy+dir[k][1];
                if(!mp[xxx][yyy]){ok=false;break;}
            }   
            if(ok){cout<<i;return 0;}
        }
    }
    cout<<-1;
    return 0;
}
```
核心思想：每次操作标记当前格子为黑色，然后遍历当前格子及其周围 $8$ 个格子，判断以它们为中心是否形成 $3\times 3$ 黑色矩阵，若形成则输出当前操作次数。

- **作者：xvl_（4星）**
    - **关键亮点**：代码结构清晰，同样使用方向数组优化判断过程，时间复杂度为 $O(m)$。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, m;
int dx[9] = {1, 1, 1, -1, -1, -1, 0, 0, 0};
int dy[9] = {0, -1, 1, 0, -1, 1, 0, -1, 1};
bool vis[1005][1005];
bool check(int x, int y) {
    for (int i = 0; i < 9; i++) {
        if (!vis[x + dx[i]][y + dy[i]]) return 0;
    }
    return 1;
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        vis[x][y] = 1;
        for (int j = 0; j < 9; j++) {
            if (check(x + dx[j], y + dy[j])) {
                cout << i;
                return 0;
            }
        }
    }
    cout << -1;
    return 0;
}
```
核心思想：每次操作标记当前格子为黑色，通过 `check` 函数判断以当前格子及其周围 $8$ 个格子为中心是否形成 $3\times 3$ 黑色矩阵，若形成则输出当前操作次数。

- **作者：Ice_lift（4星）**
    - **关键亮点**：思路明确，代码实现简洁，利用方向数组和 `check` 函数优化判断，时间复杂度为 $O(m)$。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3000 + 5;
int n, m, a[MAXN][MAXN], x, y;
int dx[10] = {1, 1, 1, -1, -1, -1, 0, 0, 0};
int dy[10] = {0, -1, 1, 0, -1, 1, 0, -1, 1};
bool check(int x, int y) {
    for (int i = 0; i < 9; i++) {
        if (!a[x + dx[i]][y + dy[i]]) {
            return false;
        }
    }
    return true;
}
signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%lld%lld", &x, &y);
        a[x][y] = 1;
        for (int j = 0; j < 9; j++) {
            if (check(x + dx[j], y + dy[j])) {
                printf("%lld", i);
                return 0;
            }
        }
    }
    printf("-1");
    return 0;
}
```
核心思想：每次操作标记当前格子为黑色，通过 `check` 函数判断包含当前格子的 $3\times 3$ 子矩阵是否为全 $1$ 子矩阵，若为全 $1$ 子矩阵则输出当前操作次数。

### 最优关键思路或技巧
- **缩小判断范围**：每次操作只影响当前格子及其周围 $8$ 个格子，只需判断以这些格子为中心是否形成 $3\times 3$ 黑色矩阵，避免每次操作后遍历整个矩阵。
- **使用方向数组**：通过方向数组可以方便地遍历当前格子周围的格子，简化代码实现。

### 拓展思路
同类型题可能会改变矩阵大小、目标子矩阵大小或操作方式，解题思路类似，关键是找到每次操作影响的范围，缩小判断范围以优化时间复杂度。

### 洛谷相似题目推荐
- [P1319 压缩技术](https://www.luogu.com.cn/problem/P1319)
- [P1320 压缩技术（续集版）](https://www.luogu.com.cn/problem/P1320)
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

### 个人心得摘录与总结
题解中未包含个人心得相关内容。

---
处理用时：42.20秒