# 题目信息

# Orac and Game of Life

## 题目描述

Please notice the unusual memory limit of this problem.

Orac likes games. Recently he came up with the new game, "Game of Life".

You should play this game on a black and white grid with $ n $ rows and $ m $ columns. Each cell is either black or white.

For each iteration of the game (the initial iteration is $ 0 $ ), the color of each cell will change under the following rules:

- If there are no adjacent cells with the same color as this cell on the current iteration, the color of it on the next iteration will be the same.
- Otherwise, the color of the cell on the next iteration will be different.

Two cells are adjacent if they have a mutual edge.

Now Orac has set an initial situation, and he wants to know for the cell $ (i,j) $ (in $ i $ -th row and $ j $ -th column), what will be its color at the iteration $ p $ . He may ask you these questions several times.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1349C/4db31c297e8a6314da42c884c8f60724b3ebcd9e.png)For the first example, the picture above shows the initial situation and the color of cells at the iteration $ 1 $ , $ 2 $ , and $ 3 $ . We can see that the color of $ (1,1) $ at the iteration $ 1 $ is black, the color of $ (2,2) $ at the iteration $ 2 $ is black, and the color of $ (3,3) $ at the iteration $ 3 $ is also black.

For the second example, you can prove that the cells will never change their colors.

## 样例 #1

### 输入

```
3 3 3
000
111
000
1 1 1
2 2 2
3 3 3```

### 输出

```
1
1
1```

## 样例 #2

### 输入

```
5 2 2
01
10
01
10
01
1 1 4
5 1 4```

### 输出

```
0
0```

## 样例 #3

### 输入

```
5 5 3
01011
10110
01101
11010
10101
1 1 4
1 2 3
5 5 3```

### 输出

```
1
0
1```

## 样例 #4

### 输入

```
1 1 3
0
1 1 1
1 1 2
1 1 3```

### 输出

```
0
0
0```

# AI分析结果

### 题目中文重写
请注意本题不同寻常的内存限制。

Orac 喜欢游戏。最近他想出了一个新游戏，“生命游戏”。

你需要在一个有 $n$ 行和 $m$ 列的黑白网格上玩这个游戏。每个单元格要么是黑色，要么是白色。

对于游戏的每一次迭代（初始迭代为 $0$），每个单元格的颜色将根据以下规则变化：
- 如果在当前迭代中没有与该单元格颜色相同的相邻单元格，那么它在下一次迭代中的颜色将保持不变。
- 否则，该单元格在下一次迭代中的颜色将不同。

如果两个单元格有一条公共边，则它们相邻。

现在 Orac 设定了一个初始状态，他想知道对于单元格 $(i,j)$（第 $i$ 行和第 $j$ 列），在第 $p$ 次迭代时它的颜色是什么。他可能会多次问你这些问题。

### 算法分类
广度优先搜索 BFS

### 综合分析与结论
这些题解的核心思路都是通过广度优先搜索（BFS）来解决问题。首先观察到同色连通块的颜色变化规律，即同色连通块每次迭代颜色取反，且会将周围颜色不同的格子并入。然后利用 BFS 求出每个点被并入某个连通块的时刻，最后根据查询的迭代次数 $p$ 和该时刻来判断该点的颜色。

各题解的算法要点基本一致，都是先找出初始的连通块，将其加入队列进行 BFS 扩展，记录每个点被扩展到的时间。在查询时，根据该时间和查询的迭代次数判断颜色是否改变。

解决的难点在于发现同色连通块的变化规律以及如何高效地求出每个点被并入连通块的时间，BFS 算法很好地解决了这个问题。

### 所选题解
- **CYJian（4星）**
    - **关键亮点**：思路清晰，对同色连通块的变化规律解释详细，代码实现简洁明了。
- **VenusM1nT（4星）**
    - **关键亮点**：代码结构清晰，通过设置初值和 BFS 过程，能很好地实现对每个点变化时间的记录。
- **juicyyou（4星）**
    - **关键亮点**：通过构造矩阵 $B$ 来分析格子的变化情况，思路独特，代码实现规范。

### 重点代码
#### CYJian 的核心代码
```cpp
int n, m, q;
char s[1010][1010];
int bel[1010][1010];
int tim[1010][1010];

struct Node {
    int x, y;

    Node() {}
    Node(int x, int y):x(x), y(y) {}
};

queue<Node>Q;

inline int chk(Node x) {
    return 1 <= x.x && x.x <= n && 1 <= x.y && x.y <= m;
}

int main() {
    memset(bel, -1, sizeof(bel));

    scanf("%d%d%d", &n, &m, &q);
    for(int i = 1; i <= n; i++)
        scanf("%s", s[i] + 1);

    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= m; j++) {
            int tmp = 0;
            tmp |= s[i][j] == s[i - 1][j];
            tmp |= s[i][j] == s[i + 1][j];
            tmp |= s[i][j] == s[i][j - 1];
            tmp |= s[i][j] == s[i][j + 1];
            if(tmp) {
                bel[i][j] = s[i][j] - 48;
                Q.push(Node(i, j));
            }
        }

    while(!Q.empty()) {
        Node x = Q.front(); Q.pop();
        Node t;
        t = Node(x.x + 1, x.y);
        if(chk(t) && bel[t.x][t.y] == -1) Q.push(t), bel[t.x][t.y] = bel[x.x][x.y], tim[t.x][t.y] = tim[x.x][x.y] + 1;
        t = Node(x.x - 1, x.y);
        if(chk(t) && bel[t.x][t.y] == -1) Q.push(t), bel[t.x][t.y] = bel[x.x][x.y], tim[t.x][t.y] = tim[x.x][x.y] + 1;
        t = Node(x.x, x.y + 1);
        if(chk(t) && bel[t.x][t.y] == -1) Q.push(t), bel[t.x][t.y] = bel[x.x][x.y], tim[t.x][t.y] = tim[x.x][x.y] + 1;
        t = Node(x.x, x.y - 1);
        if(chk(t) && bel[t.x][t.y] == -1) Q.push(t), bel[t.x][t.y] = bel[x.x][x.y], tim[t.x][t.y] = tim[x.x][x.y] + 1;
    }

    while(q--) {
        int x = ri, y = ri;
        ll k = rl;
        if(bel[x][y] == -1 || k < tim[x][y]) putchar(s[x][y]);
        else putchar(48 | (bel[x][y] ^ (k & 1)));
        puts("");
    }
    return 0;
}
```
**核心实现思想**：先初始化 `bel` 数组为 -1，然后找出初始的连通块，将其 `bel` 设为对应颜色并加入队列。接着进行 BFS 扩展，更新每个点的 `bel` 和 `tim`。最后根据查询的迭代次数和 `tim` 判断颜色。

#### VenusM1nT 的核心代码
```cpp
#include<bits/stdc++.h>
#define MAXN 1005
#define M 10000000
#define reg register
#define inl inline
#define int long long
using namespace std;
struct Node
{
    int x,y;
};
queue <Node> q;
int n,m,Q,a[MAXN][MAXN];
char ch[MAXN][MAXN];
signed main()
{
    memset(a,60,sizeof(a));
    scanf("%lld %lld %lld",&n,&m,&Q);
    for(reg int i=1;i<=n;i++) scanf("%s",ch[i]+1);
    for(reg int i=1;i<=n;i++)
    {
        for(reg int j=1;j<=m;j++)
        {
            if(ch[i][j]==ch[i-1][j] || ch[i][j]==ch[i+1][j] || ch[i][j]==ch[i][j-1] || ch[i][j]==ch[i][j+1])
            {
                a[i][j]=0;
                q.push((Node){i,j});	
            }
        }
    }
    while(!q.empty())
    {
        reg Node now=q.front();
        q.pop();
        reg int i=now.x,j=now.y;
        if(i+1<=n && a[i+1][j]>M)
        {
            a[i+1][j]=a[i][j]+1;
            q.push((Node){i+1,j});
        }
        if(j+1<=m && a[i][j+1]>M)
        {
            a[i][j+1]=a[i][j]+1;
            q.push((Node){i,j+1});
        }
        if(i-1>=1 && a[i-1][j]>M)
        {
            a[i-1][j]=a[i][j]+1;
            q.push((Node){i-1,j});
        }
        if(j-1>=1 && a[i][j-1]>M)
        {
            a[i][j-1]=a[i][j]+1;
            q.push((Node){i,j-1});
        }
    }
    while(Q--)
    {
        reg int x,y,t;
        scanf("%lld %lld %lld",&x,&y,&t);
        if(a[x][y]>t) printf("%c\n",ch[x][y]);
        else
        {
            reg int p=t-a[x][y];
            if(p&1) printf("%c\n",ch[x][y]=='0'?'1':'0');
            else printf("%c\n",ch[x][y]);
        }
        
    }
    return 0;
}
```
**核心实现思想**：将 `a` 数组初始化为一个很大的值，找出初始连通块将其 `a` 设为 0 并加入队列。进行 BFS 扩展，更新每个点的 `a` 值。查询时根据 `a` 值和查询迭代次数判断颜色。

#### juicyyou 的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e5 + 5;
const ll maxm = 1e3 + 5;
inline void qread(){}
template<class T1, class ...T2>
inline void qread(T1 &IEE, T2&... ls){
    register T1 __ = 0, ___ = 1;
    register char ch;
    while(!isdigit(ch = getchar())) ___ = (ch == '-') ? -___ : ___;
    do{
        __ = (__ << 1) + (__ << 3) + (ch ^ 48);
    }while(isdigit(ch = getchar()));
    __ *= ___;
    IEE = __;
    qread(ls...);
    return ;
}
ll n, m, k, aa, b, c;
const ll dar[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char ch;
int a[maxm][maxm], d[maxm][maxm];
bool p[maxm][maxm];
queue<pair<ll, ll> > q;
int main(){
    qread(n, m, k);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> ch;
            a[i][j] = ch - '0';
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            for(int k = 0;k < 4;k++){
                ll tx = i + dar[k][0], ty = j + dar[k][1];
                if(tx > n || tx < 1 || ty > m || ty < 1) continue;
                if(a[tx][ty] == a[i][j]){
                    p[i][j] = 1;
                }
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(p[i][j]){
                q.push(make_pair(i, j));
            } 
        }
    }
    bool flag = 0;
    if(q.empty()) flag = 1;
    while(!q.empty()){
        ll x = q.front().first, y = q.front().second;
        q.pop();
        for(int i = 0;i < 4;i++){
            ll tx = x + dar[i][0], ty = y + dar[i][1];
            if(tx > n || tx < 1 || ty > m || ty < 1) continue;
            if(p[tx][ty]) continue;
            d[tx][ty] = d[x][y] + 1;
            p[tx][ty] = 1;
            q.push(make_pair(tx, ty));
        }
    }
    while(k--){
        qread(aa, b, c);
        if(flag == 1){
            cout << a[aa][b] << endl;
            continue;
        }
        if(c < d[aa][b]){
            cout << a[aa][b] << endl;
            continue;
        }
        c -= d[aa][b];
        cout << (a[aa][b] + c) % 2;
        puts("");
    }
    return 0;
}
```
**核心实现思想**：先读取输入，找出初始连通块标记在 `p` 数组中并加入队列。进行 BFS 扩展，更新每个点的 `d` 值。查询时根据 `d` 值和查询迭代次数判断颜色。

### 最优关键思路或技巧
- **连通块合并思想**：将同色的格子缩成一个点，利用连通块的变化规律来简化问题。
- **BFS 算法**：通过 BFS 高效地求出每个点被并入连通块的时间。

### 拓展思路
同类型题可能会有不同的网格变化规则，或者在更高维度的空间中进行类似的变化。类似算法套路可以应用于其他网格类的状态变化问题，通过观察规律，利用 BFS 或 DFS 来求解。

### 推荐题目
- P1162 填涂颜色
- P1443 马的遍历
- P1747 好奇怪的游戏

### 个人心得
题解中未包含个人心得内容。

---
处理用时：80.85秒