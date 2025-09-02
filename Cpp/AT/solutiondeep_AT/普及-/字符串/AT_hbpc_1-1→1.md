# 题目信息

# 1→1

## 题目描述

$m$表示变化规则的数量，$n$表示要生成$1$的数量。

对于生成规则$a_{i},b_{i}$而言，它表示可以将原字符串中的$a_{i}$个$1$变为$b_{i}$个$1$。例如，$a_{i}=2,b_{i}=3$，表示原字符串中$11$可以变为$111$

现在，原字符串中只有$1$个$1$，要求你使用最少的变化次数将字符串变成$n$个$1$。

## 说明/提示

- $1≤m≤300^{2}$
- $1≤n≤10000$
- $1≤a_{i},b_{i}≤300$
- 当$i≠j$时保证$a_{i}≠a_{j}$且$b_{i}≠b_{j}$


### 样例$1$

规则为：

$1->11$

$111->11111$

那么一个$1$变成$11111$需要经过下面这些步骤：

1->11

11->111

111->1111

变化次数为$3$，故答案为$4$。

### 样例$2$

规则为：

$1->111$

$11111->111$

那么一个$1$不可能变成$111111$，故答案为$-1$。

# AI分析结果

### 题解综合分析与结论
这些题解都采用广度优先搜索（BFS）算法解决问题。思路上，均从初始的 1 个 1 开始，利用队列存储状态，不断根据变化规则扩展新状态，直至达到目标的 n 个 1 或队列为空。

#### 算法要点
- **状态表示**：使用结构体存储当前 1 的数量和变化次数。
- **队列操作**：利用队列实现 BFS 的逐层扩展。
- **判重处理**：使用布尔数组标记已访问的状态，避免重复搜索。
- **剪枝优化**：当 1 的数量超过 `n + 300` 时，不再继续扩展。

#### 解决难点
- **特判初始状态**：由于搜索从初始状态扩展，需单独处理 `n = 1` 的情况。
- **避免死循环**：通过判重数组确保每个状态只被访问一次。
- **控制搜索范围**：利用剪枝减少不必要的搜索，提高效率。

### 评分较高的题解
- **作者：翼德天尊（5 星）**
    - **关键亮点**：思路清晰，详细解释了 BFS 算法的原理和使用原因，代码注释完整，易于理解。
    - **个人心得**：作者提到刚开始把 `300²` 看成 300，导致多次提交错误，提醒我们要仔细审题。
```cpp
#include <bits/stdc++.h>
using namespace std;
int m,n,a[90001],b[90001],v[20000];
struct node{
    int l,x;
};
node ydn;
queue<node> q;
int main() {
    scanf("%d %d",&m,&n);
    for (int i=1;i<=m;i++){
        scanf("%d %d",&a[i],&b[i]);
    }
    if (n==1){
        printf("1\n");
        return 0;
    }
    ydn.l=1;ydn.x=1;
    q.push(ydn);
    v[1]=1;
    while (!q.empty()){
        node no=q.front();
        q.pop();
        for (int i=1;i<=m;i++){
            if (no.x>=a[i]){
                node noo;
                noo.l=no.l+1;
                noo.x=no.x-a[i]+b[i];
                if (v[noo.x]==0&&noo.x<=n+300){
                    if (noo.x==n){
                        printf("%d\n",noo.l);
                        return 0;
                    }
                    v[noo.x]=1;
                    q.push(noo);
                }
            }
        }
    }
    printf("-1\n");
    return 0;
}
```
核心实现思想：使用结构体 `node` 存储当前状态，队列 `q` 进行 BFS 扩展。在每次扩展时，判断当前状态是否满足变化规则，若满足则生成新状态，若新状态未访问且在范围内，将其加入队列。

- **作者：EuphoricStar（4 星）**
    - **关键亮点**：代码简洁，思路明确，使用 `ios::sync_with_stdio(0)` 优化输入输出，同时强调了判重和剪枝的重要性。
```cpp
#include <bits/stdc++.h>
using namespace std;

struct rule
{
    int a, b;
} rules[90090];
struct point
{
    int cur, step;
};
int m, n, ans;
queue<point> q;
bool vis[10000000];

int main()
{
    ios::sync_with_stdio(0);
    cin >> m >> n;
    for (int i = 0; i < m; ++i) cin >> rules[i].a >> rules[i].b;
    q.push({1, 1});
    vis[1] = 1;
    while (!q.empty())
    {
        int cur = q.front().cur, step = q.front().step;
        q.pop();
        if (cur == n) { cout << step << endl; return 0; }
        for (int i = 0; i < m; ++i)
        {
            int a = rules[i].a, b = rules[i].b, nn = cur;
            if (cur >= a) nn += b - a;
            if (vis[nn]) continue;
            if (nn > n + 300) continue;
            vis[nn] = 1;
            q.push({nn, step + 1});
        }
    }
    cout << -1 << endl;
    return 0;
}
```
核心实现思想：定义结构体 `rule` 存储变化规则，`point` 存储当前状态。使用队列 `q` 进行 BFS 搜索，每次从队列取出一个状态，根据规则生成新状态，若新状态未访问且在范围内，将其加入队列。

- **作者：FlyfishO25（4 星）**
    - **关键亮点**：提供了无优化和优化两个版本的代码，优化思路为对变化规则按所需 1 的数量排序，减少不必要的搜索。
```cpp
// 版本二优化代码
#include<bits/stdc++.h>
using namespace std;

struct change{
    int first;
    int second;
}c[90001];
struct one{
    int x, change_time;
};

bool cmp(const change &a, const change &b){
    return a.first < b.first;
}

queue<one> Q;
int n, m;
bool vis[20000];

int main(){
    cin>>m>>n;
    for(int i = 1;i <= m;++i){
        cin>>c[i].first>>c[i].second;
    }
    if(n == 1){
        cout<<1<<endl;
        return 0;
    }
    sort(c+1, c+m+1, cmp);
    Q.push((one){1, 1});
    vis[1] = true;
    while(!Q.empty()){
        one tmp = Q.front();
        Q.pop();
        for(int i = 1;i <= m;++i){
            if(tmp.x >= c[i].first){
                one tp;
                tp.change_time = tmp.change_time + 1;
                tp.x = tmp.x-c[i].first+c[i].second;
                if(!vis[tp.x] && tp.x < n+300){
                    if(tp.x == n){
                        cout<<tp.change_time<<endl;
                        return 0;
                    }
                    vis[tp.x] = true;
                    Q.push(tp);
                }
            }
            else{
                break;
            }
        }
    }
    cout<<-1<<endl;
    return 0;
}
```
核心实现思想：先对变化规则按所需 1 的数量排序，在 BFS 扩展时，若当前状态不满足某规则，后续规则也无需判断。

### 最优关键思路或技巧
- **使用 BFS 算法**：由于要求最少变化次数，BFS 能逐层扩展，确保首次到达目标状态时的步数最少。
- **判重数组**：避免重复搜索，防止陷入死循环。
- **剪枝优化**：当 1 的数量超过 `n + 300` 时停止扩展，减少不必要的计算。
- **规则排序**：对变化规则按所需 1 的数量排序，在搜索时提前终止不必要的判断。

### 可拓展之处
同类型题如迷宫最短路径、状态转换最少步数等，都可使用 BFS 算法解决。类似算法套路是确定起始状态、终止状态和状态转移规则，利用队列进行逐层扩展，同时做好判重和剪枝优化。

### 洛谷相似题目推荐
1. **P1135 奇怪的电梯**（https://www.luogu.com.cn/problem/P1135）：给定电梯每层可上下的层数，求从起始层到目标层的最少步数。
2. **P1605 迷宫**（https://www.luogu.com.cn/problem/P1605）：在迷宫中寻找从起点到终点的最短路径。
3. **P1332 血色先锋队**（https://www.luogu.com.cn/problem/P1332）：给定感染源和地图，求每个点被感染的最短时间。

### 个人心得摘录与总结
- **翼德天尊**：审题要仔细，避免因看错数据范围导致多次提交错误。
- **lzxhdxx**：注意操作的方向性，如 `1 -> 2` 不能反向变为 `2 -> 1`。
- **Max_Leo**：要注意特判目标为 1 的情况，以及输出格式需符合题目要求。 

---
处理用时：50.60秒