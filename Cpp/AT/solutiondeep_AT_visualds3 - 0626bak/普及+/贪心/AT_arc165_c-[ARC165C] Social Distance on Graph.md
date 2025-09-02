# 题目信息

# [ARC165C] Social Distance on Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc165/tasks/arc165_c

頂点に $ 1 $ から $ N $ の番号が付いた $ N $ 頂点からなる単純連結無向グラフがあります。グラフには重みを持つ辺が $ M $ 本あり、$ i $ 番目の辺は頂点 $ A_i,B_i $ を結ぶ重みが $ W_i $ の辺です。また、$ 2 $ 頂点を結ぶ単純パスの重みを、単純パスが含む辺の重みの総和とします。

各頂点に対し赤、青のいずれかの色を塗ります。以下の条件を満たす塗り分け方が存在するような整数 $ X $ の最大値を求めてください。

- 同じ色で塗られた相異なる $ 2 $ 頂点を結ぶどの単純パスについても、単純パスの重みは $ X $ 以上である。
 
  単純パスとは グラフ $ G $ 上の頂点 $ X,Y $ に対して、頂点列 $ v_1,v_2,\ \ldots,\ v_k $ であって、 $ v_1=X $, $ v_k=Y $ かつ、$ 1\leq\ i\leq\ k-1 $ に対して $ v_i $ と $ v_{i+1} $ が辺で結ばれているようなものを頂点 $ X $ から頂点 $ Y $ への **ウォーク** と呼びます。 さらに、$ v_1,v_2,\ \ldots,\ v_k $ がすべて異なるようなものを頂点 $ X $ から頂点 $ Y $ への **単純パス** (あるいは単に **パス**) と呼びます。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min(\frac{N(N-1)}{2},2\ \times\ 10^5) $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ 1\ \leq\ W_i\ \leq\ 10^9 $
- 与えられるグラフは単純連結無向グラフ
- 入力される値はすべて整数
 
### Sample Explanation 1

$ X=11 $ としたときに条件を満たす色の塗り方が存在するか考えます。頂点 $ 1,3 $ を赤、頂点 $ 2 $ を青で塗った場合、同じ色の頂点を結ぶ単純パス $ 1-2-3 $ の重みが $ 5+6=11 $ となります。これが同じ色の頂点を結ぶ単純パスの重みの最小値となるのでこの塗り分け方は条件を満たしています。 $ X $ が $ 12 $ 以上のとき、条件を満たす塗り分け方が存在しないことが示せます。よって答えは $ 11 $ となります。

## 样例 #1

### 输入

```
3 3

1 2 5

2 3 6

1 3 12```

### 输出

```
11```

## 样例 #2

### 输入

```
10 20

7 10 982219000

3 10 968366179

2 4 992330437

5 6 984414664

2 8 897295423

7 9 155604979

6 8 958833005

2 3 973209957

3 7 985173062

6 10 963895817

2 10 986243534

4 5 721724794

1 3 657562445

1 6 566370694

1 4 988050146

1 9 967817807

4 9 796531581

5 9 983960054

1 10 964450079

8 9 959369491```

### 输出

```
952136560```

## 样例 #3

### 输入

```
10 20

5 6 871895994

8 10 873709822

3 5 454175869

6 10 980782191

2 6 901290987

1 8 298092290

4 8 693116157

4 5 947939338

7 8 934395075

7 9 759563833

5 8 779870031

4 6 919637355

2 9 822858749

4 10 855497285

3 7 954942051

1 2 950411658

4 7 665939990

3 4 634533617

5 7 908372507

1 9 591466693```

### 输出

```
759563833```

# AI分析结果



## 唯一算法分类
二分答案 + 二分图判定

## 综合分析与结论

### 核心思路
题目要求找到最大的X，使得存在一种黑白染色方案，使得同色顶点间所有简单路径的边权和≥X。采用二分答案框架：

1. **预处理上界**：每个顶点记录两个最小边权，其和的最小值作为二分初始右边界。该步骤保证任何两条相邻边权之和≥X。
2. **二分判定**：对于mid值，构建边权<mid的子图，若该图是二分图则mid可行，否则不可行。

### 算法流程
1. **预处理**：遍历所有边，维护每个顶点的最小和次小边权。
2. **二分框架**：初始右边界为所有顶点两个最小边权之和的最小值。
3. **判定函数**：用DFS/BFS对边权<mid的子图进行二分图染色，若存在奇环则判定失败。

### 可视化设计
- **动画效果**：以像素风格展示顶点染色过程，不同颜色用不同像素块表示。边权<mid的边高亮显示，判定失败时播放失败音效。
- **交互面板**：允许调节二分区间与mid值，单步执行染色过程，观察奇环检测逻辑。
- **音效触发**：每次成功染色顶点播放"滴"声，发现冲突边时播放"警告"声。

## 题解清单（≥4星）

### 翼德天尊（5星）
- **亮点**：代码结构清晰，预处理部分用双数组维护最小次小值，DFS染色逻辑简洁。
- **核心代码**：
```cpp
void chan(int u,int w){
    if(w<minn[u]) cmin[u]=minn[u],minn[u]=w;
    else if(w<cmin[u]) cmin[u]=w;
}
bool check(ll x){
    for(int i=1;i<=n;i++) col[i]=0;
    for(int i=1;i<=n;i++)
        if(!col[i]) col[i]=1,dfs(i,x);
    return flag;
}
```

### reclusive（4星）
- **亮点**：并查集实现二分图判定，预处理函数封装规范。
- **核心代码**：
```cpp
void solve(LL x,LL c){
    if(c<minn[x]) next_minn[x]=minn[x],minn[x]=c;
    else if(minn[x]<=c&&c<next_minn[x]) next_minn[x]=c;
}
bool dfs(LL x,LL mid,LL c){
    color[x]=c;
    for(LL k=last[x];k;k=a[k].pre){
        if(a[k].c>=mid)continue;
        LL y=a[k].y;
        if(color[x]==color[y]) return false;
        if(!color[y]&&!dfs(y,mid,3-c)) return false;
    }
    return true;
}
```

### _sunkuangzheng_（4星）
- **亮点**：BFS实现染色，预处理排序优化。
- **核心代码**：
```cpp
bool bfs(int s,int x){
    queue<int> q;
    q.push(s),col[s] = 0;
    while(!q.empty()){
        int u = q.front();q.pop();
        for(auto [w,v] : g[u]){
            if(w >= x) continue;
            if(col[v] == -1) col[v] = col[u] ^ 1,q.push(v);
            else if(col[u] == col[v]) return 0;
        }
    }return 1;
}
```

## 最优思路提炼
1. **二分答案框架**：将极值问题转化为判定问题。
2. **双最小边预处理**：通过O(m)预处理确定二分上界。
3. **二分图性质应用**：将边权约束转化为图的二分性判定。

## 相似题目推荐
1. [CF862B - Mahmoud and Ehab and the bipartiteness](https://codeforces.com/problemset/problem/862/B)
2. [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)
3. [P3385 判断负环](https://www.luogu.com.cn/problem/P3385)

## 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,minn[N],cmin[N],col[N];
struct Edge{ int to,next,val; } e[N<<1];
int head[N],tot;

void add(int u,int v,int w){
    e[++tot]={v,head[u],w};
    head[u]=tot;
}

void update(int u,int w){
    if(w<minn[u]) cmin[u]=minn[u], minn[u]=w;
    else if(w<cmin[u]) cmin[u]=w;
}

bool dfs(int u,ll x,int color){
    col[u]=color;
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to, w=e[i].val;
        if(w >=x) continue;
        if(col[v]==color) return false;
        if(!col[v] && !dfs(v,x,3-color)) return false;
    }
    return true;
}

bool check(ll x){
    memset(col,0,sizeof(col));
    for(int i=1;i<=n;++i)
        if(!col[i] && !dfs(i,x,1)) 
            return false;
    return true;
}

int main(){
    scanf("%d%d",&n,&m);
    fill(minn,minn+N,1e9+5);
    fill(cmin,cmin+N,1e9+5);
    while(m--){
        int u,v,w; scanf("%d%d%d",&u,&v,&w);
        add(u,v,w); add(v,u,w);
        update(u,w); update(v,w);
    }
    ll l=0, r=2e18;
    for(int i=1;i<=n;++i)
        if(cmin[i]!=1e9+5) 
            r = min(r, (ll)minn[i]+cmin[i]);
    ll ans=0;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid)) ans=mid, l=mid+1;
        else r=mid-1;
    }
    printf("%lld\n",ans);
    return 0;
}
```

## 可视化算法演示
### 核心流程
1. **顶点染色**：用红蓝两色表示顶点状态，初始为灰色。
2. **边权筛选**：动态显示当前mid值，红色高亮边权<mid的边。
3. **冲突检测**：当发现相邻顶点同色且边权<mid时，触发闪烁警示。

### 复古风格实现
```html
<canvas id="game" width="800" height="600"></canvas>
<script>
const palette = ["#000","#f00","#00f","#0f0","#fff"];
class Visualizer {
    constructor(nodes, edges) {
        this.nodes = nodes; // {id,x,y}
        this.edges = edges; // {u,v,w}
        this.ctx = document.getElementById("game").getContext("2d");
    }
    
    draw(mid) {
        this.ctx.fillStyle = palette[0];
        this.ctx.fillRect(0,0,800,600);
        // Draw edges
        this.edges.forEach(e => {
            this.ctx.strokeStyle = e.w < mid ? palette[3] : palette[4];
            drawLine(this.nodes[e.u], this.nodes[e.v]);
        });
        // Draw nodes
        this.nodes.forEach(n => {
            this.ctx.fillStyle = n.color ? palette[n.color] : palette[4];
            drawPixel(n.x, n.y, 8);
        });
    }
}
</script>
```

---
处理用时：98.27秒