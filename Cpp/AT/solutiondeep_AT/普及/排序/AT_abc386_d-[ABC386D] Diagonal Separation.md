# 题目信息

# [ABC386D] Diagonal Separation

## 题目描述

有一个 $N \times N$ 的网格，高桥君希望将每个格子涂成黑色或白色，并满足以下条件：

- 对于每一行，存在一个整数 $i$（$0 \leq i \leq N$），该行从左到右的前 $i$ 个格子是黑色，其余的为白色。
- 对于每一列，存在一个整数 $i$（$0 \leq i \leq N$），该列从上到下的前 $i$ 个格子是黑色，其余的为白色。

目前已有 $M$ 个格子被涂上了颜色。具体来说，第 $i$ 个被涂色的格子位于第 $X_i$ 行、第 $Y_i$ 列。如果 $C_i$ 为 `B`，表示该格子已经被涂黑；如果 $C_i` 为 `W`，则表示该格子已经被涂白。

请判断剩下的 $N^2 - M$ 个格子是否可以通过适当选择颜色来满足上述所有条件。

## 说明/提示

- $1 \leq N \leq 10^9$
- $1 \leq M \leq \min(N^2, 2 \times 10^5)$
- $1 \leq X_i, Y_i \leq N$
- 任意两个不同的 $i$，$(X_i, Y_i) \neq (X_j, Y_j)$
- $C_i$ 为 `B` 或 `W`

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 3

4 1 B

3 2 W

1 3 B```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2

1 2 W

2 2 B```

### 输出

```
No```

## 样例 #3

### 输入

```
1 1

1 1 W```

### 输出

```
Yes```

## 样例 #4

### 输入

```
2289 10

1700 1083 W

528 967 B

1789 211 W

518 1708 W

1036 779 B

136 657 B

759 1497 B

902 1309 B

1814 712 B

936 763 B```

### 输出

```
No```

# AI分析结果

### 题目内容（已为中文，无需重写）
有一个 $N \times N$ 的网格，高桥君希望将每个格子涂成黑色或白色，并满足以下条件：

- 对于每一行，存在一个整数 $i$（$0 \leq i \leq N$），该行从左到右的前 $i$ 个格子是黑色，其余的为白色。
- 对于每一列，存在一个整数 $i$（$0 \leq i \leq N$），该列从上到下的前 $i$ 个格子是黑色，其余的为白色。

目前已有 $M$ 个格子被涂上了颜色。具体来说，第 $i$ 个被涂色的格子位于第 $X_i$ 行、第 $Y_i$ 列。如果 $C_i$ 为 `B`，表示该格子已经被涂黑；如果 $C_i$ 为 `W`，则表示该格子已经被涂白。

请判断剩下的 $N^2 - M$ 个格子是否可以通过适当选择颜色来满足上述所有条件。

### 说明/提示
- $1 \leq N \leq 10^9$
- $1 \leq M \leq \min(N^2, 2 \times 10^5)$
- $1 \leq X_i, Y_i \leq N$
- 任意两个不同的 $i$，$(X_i, Y_i) \neq (X_j, Y_j)$
- $C_i$ 为 `B` 或 `W`

### 综合分析与结论
各题解核心思路均围绕判断是否存在白色方块右下方有黑色方块这一条件展开，以下是详细对比：
|作者|思路|算法要点|解决难点|
| ---- | ---- | ---- | ---- |
|xiaoke2021|按行从小到大、白色在前排序，维护最靠左白色方块列值，判断黑色方块合法性|结构体排序、枚举方块|避免因枚举顺序导致白色方块列值未统计而误判|
|LionBlaze|分析黑白方块影响范围，按 $x$ 坐标排序，用最大值数组优化判断|排序、最大值数组、指针枚举|优化暴力枚举的时间复杂度|
|Drifty|按 $x$ 为第一关键字、$y$ 为第二关键字排序，取当前纵坐标最大白色点判断|排序、贪心|简化判断过程|
|Yuexingfei_qwq|排序后处理白色点 $y$ 坐标最小值数组和黑色点 $y$ 坐标最大值数组，遍历判断|排序、数组预处理、遍历|高效处理黑白点关系|
|_zqh_|枚举白点，二分找横坐标不小于白点的黑点，用后缀最大值维护纵坐标最大值|二分、后缀最大值|快速定位黑点并判断覆盖情况|
|Emplace|按 $x$ 从小到大排序，枚举时取白点 $y$ 最小值判断黑点合法性|排序、枚举|判断黑点左上角是否有白点|
|K_yuxiang_rose|分别记录黑白格子，排序并统计后缀纵坐标最大值，二分判断白格子合法性|排序、后缀最大值、二分|高效判断白格子是否被黑格子覆盖|
|lyas145|CDQ 分治，按纵坐标排序，离散化横坐标，用树状数组维护|CDQ 分治、排序、离散化、树状数组|处理格子位置关系|
|_anll_|处理黑色点成后缀 max 问题，排序白色点遍历判断|排序、后缀最大值、遍历|判断白色点是否在黑色矩形内|

### 评分
|作者|评分|
| ---- | ---- |
|xiaoke2021|5星|
|LionBlaze|4星|
|Yuexingfei_qwq|4星|
|Drifty|3星|
|_zqh_|3星|
|Emplace|3星|
|K_yuxiang_rose|3星|
|lyas145|3星|
|_anll_|3星|

### 所选题解
- **xiaoke2021（5星）**
    - 关键亮点：思路清晰，通过简单排序和枚举解决问题，代码可读性高。
    - 核心代码：
```cpp
struct T{
    int x,y;
    char c;
}node[200000+5];
int n,m;
int wy=2147483647; 
bool cmp(T a,T b){
    if(a.x==b.x) return a.y<b.y;
    else return a.x<b.x;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>node[i].x>>node[i].y>>node[i].c;
    }
    sort(node+1,node+1+m,cmp); 
    for(int i=1;i<=m;i++){
        if(node[i].c=='W') wy=min(wy,node[i].y); 
        else if(node[i].y>=wy){ 
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes";
    return 0;
}
```
核心实现思想：将所有方块按行从小到大、白色在前排序，枚举方块，维护最靠左白色方块列值，若黑色方块列值大于等于该值则不合法。
- **LionBlaze（4星）**
    - 关键亮点：详细分析黑白方块影响范围，使用最大值数组和指针优化判断，时间复杂度较低。
    - 核心代码：
```cpp
class black
{
public:
    int x, y;
} blacks[200005];
class white
{
public:
    int x, y;
} whites[200005];
int ymax[200005];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int bcur = 0, wcur = 0;
    for(int i=1;i<=m;i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        getchar();
        char c = getchar();
        if(c == 'B') blacks[++bcur] = {x, y};
        else whites[++wcur] = {x, y};
    }
    sort(blacks + 1, blacks + bcur + 1, [](const black &x, const black &y) { return x.x < y.x; });
    sort(whites + 1, whites + wcur + 1, [](const white &x, const white &y) { return x.x < y.x; });
    for(int i=bcur;i>=1;i--)
    {
        if(blacks[i].y > ymax[i+1]) ymax[i] = blacks[i].y;
        else ymax[i] = ymax[i+1];
    }
    blacks[bcur+1].x = 2147483647;
    int bptr = 0;
    for(int i=1;i<=wcur;i++)
    {
        while(blacks[bptr].x < whites[i].x)
        {
            bptr++;
        }
        if(ymax[bptr] >= whites[i].y)
        {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
    return 0;
}
```
核心实现思想：分别记录黑白格子，按 $x$ 坐标排序，预处理黑色格子纵坐标最大值数组，枚举白色格子，用指针定位黑色格子，判断是否合法。
- **Yuexingfei_qwq（4星）**
    - 关键亮点：通过预处理白色点 $y$ 坐标最小值数组和黑色点 $y$ 坐标最大值数组，遍历判断，逻辑清晰。
    - 核心代码：
```cpp
struct Info {
    int x, y;
    char c;
} a[210000];
inline bool cmp(Info x, Info y) {
    if (x.x!= y.x) {
        return x.x < y.x;
    }
    return x.y < y.y;
}
int p[210000], s[210000];
signed main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        cin >> a[i].x >> a[i].y >> a[i].c;
    }
    std::sort(a + 1, a + m + 1, cmp);
    for(int i = 0; i <= m + 1; i++) {
        p[i] = inf;
        s[i] = -inf;
    }
    for(int i = 1; i <= m; i++) {
        p[i + 1] = p[i];
        if (a[i].c == 'W') {
            p[i + 1] = std::min(p[i + 1], a[i].y);
        }
    }
    for (int i = m; i; i--) {
        s[i] = s[i + 1];
        if (a[i].c == 'B') {
            s[i] = std::max(s[i], a[i].y);
        }
    }
    for(int i = 1; i <= m + 1; i++) {
        if (p[i] <= s[i]) {
            cout << "No" << el;
            return 0;
        }
    }
    cout << "Yes" << el;
    return 0;
}
```
核心实现思想：将所有点排序，预处理白色点 $y$ 坐标最小值数组和黑色点 $y$ 坐标最大值数组，遍历数组判断是否存在白色方块右下方有黑色方块的情况。

### 最优关键思路或技巧
- 排序：通过合理排序（如按行、$x$ 坐标等），可以简化后续判断过程。
- 数组维护：使用最大值数组、最小值数组、后缀最大值等，高效记录关键信息，减少重复计算。
- 贪心与枚举：结合贪心思想，枚举方块或格子，快速判断合法性。

### 拓展思路
同类型题可拓展到更高维度的网格或更复杂的颜色规则，类似算法套路有排序优化、二分查找、数据结构维护（如树状数组）等。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可使用归并排序或树状数组解决，与本题排序和数据结构维护思路类似。
2. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)：涉及平衡树的操作，可通过排序和数据结构优化查找过程。
3. [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)：需要分析元素之间的关系，与本题分析黑白方块影响范围思路类似。

### 个人心得摘录与总结
- **Yuexingfei_qwq**：赛时没过，以篇纪念。总结：比赛中可能因紧张或思路不清晰导致题目未通过，赛后应及时总结经验。
- **_anll_**：感觉比 E 难写，一开始没理解题错了好几发。总结：理解题意是解题的关键，遇到难题可多花时间分析题目条件。

---
处理用时：67.96秒