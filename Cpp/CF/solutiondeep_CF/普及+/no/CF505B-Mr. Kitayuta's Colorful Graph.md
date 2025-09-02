# 题目信息

# Mr. Kitayuta's Colorful Graph

## 题目描述

给出一个 $n$ 个点，$m$ 条边的无向图，每条边上是有颜色的。有 $q$ 组询问

对于第 $i$ 组询问，给出点对 $u_i,v_i$。求有多少种颜色 $c$ 满足：有至少一条 $u_i$ 到 $v_i$ 路径，满足该路径上的所有边的颜色都为 $c$

## 说明/提示

$2 \le n \le 100$  
$1 \le m,q \le 100$  
$1\le x_i,y_i,u_i,v_i \le n$  
$1 \le c_i \le m$  
感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
4 5
1 2 1
1 2 2
2 3 1
2 3 3
2 4 3
3
1 2
3 4
1 4
```

### 输出

```
2
1
0
```

## 样例 #2

### 输入

```
5 7
1 5 1
2 5 1
3 5 1
4 5 1
1 2 2
2 3 2
3 4 2
5
1 5
5 1
2 5
1 5
1 4
```

### 输出

```
1
1
1
1
2
```

# AI分析结果

### 题目内容
# Mr. Kitayuta的多彩图

## 题目描述
给出一个有\(n\)个点、\(m\)条边的无向图，每条边都有颜色。有\(q\)组询问。
对于第\(i\)组询问，给出点对\(u_i\)、\(v_i\)。求有多少种颜色\(c\)满足：存在至少一条从\(u_i\)到\(v_i\)的路径，该路径上所有边的颜色都为\(c\)。

## 说明/提示
\(2 \leq n \leq 100\)  
\(1 \leq m,q \leq 100\)  
\(1\leq x_i,y_i,u_i,v_i \leq n\)  
\(1 \leq c_i \leq m\)  
感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1
### 输入
```
4 5
1 2 1
1 2 2
2 3 1
2 3 3
2 4 3
3
1 2
3 4
1 4
```
### 输出
```
2
1
0
```

## 样例 #2
### 输入
```
5 7
1 5 1
2 5 1
3 5 1
4 5 1
1 2 2
2 3 2
3 4 2
5
1 5
5 1
2 5
1 5
1 4
```
### 输出
```
1
1
1
1
2
```

### 算法分类
并查集

### 题解综合分析与结论
这几道题解主要围绕并查集、弗洛伊德算法、DFS 等方法来解决问题。大部分题解使用并查集，原因在于题目重点是维护两点间连通性，且数据范围较小，适合并查集。各题解思路、要点及难点如下：
 - **并查集常规做法**：开二维并查集，`fa[i][j]` 或 `f[i][j]` 表示点 `i` 在连通色为 `j` 的集合中的祖先节点。对每条边按颜色将两端点在对应颜色的并查集中合并。询问时枚举颜色，判断两点在该颜色并查集中祖先是否相同来统计满足条件的颜色数。其难点在于理解二维并查集含义及构建。
 - **分块优化并查集**：先按颜色排序存边并离线询问。对每种颜色边数分块讨论，边数大于等于 \(\sqrt{n}\) 直接对颜色边做并查集扫询问统计；边数小于 \(\sqrt{n}\) 对边连点做并查集，用 `map` 统计点对贡献。难点在于分块处理及 `map` 运用。
 - **弗洛伊德算法**：在普通弗洛伊德状态基础上加入颜色选择，`dis[u][v][c]` 表示 \(u \longrightarrow v\) 且边权为 `c` 的边存在。通过弗洛伊德算法更新，询问时统计满足条件颜色数。难点在于状态设计及弗洛伊德算法结合颜色处理。
 - **DFS做法**：对每种颜色建图，每次询问从起点 `DFS` 标记可达点，通过统计终点对每种颜色的可达情况得答案，询问完需重置标记数组。难点在于多次建图及标记处理。

整体看，常规并查集做法思路和代码较简洁清晰，分块优化并查集在大数据量下有优势，弗洛伊德和 DFS 做法相对复杂且复杂度较高。

### 所选的题解
 - **作者：封禁用户 (赞：3)  星级：4星**
    - **关键亮点**：思路简洁清晰，直接采用并查集解决问题，代码实现简洁明了，很好体现并查集在该问题中的应用。
```cpp
void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            fa[i][j] = i;
        }
    }
}
int fnd(int u, int color) {
    if (fa[u][color] == u) {
        return u;
    }
    return fa[u][color] = fnd(fa[u][color], color);
}

void add(int u,int v,int c) {
    fa[fnd(u, c)][c] = fnd(v, c);
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        add(x,y,c);
    }
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int res = 0;
        for (int i = 1; i <= m; i++) {
            if (fnd(u, i) == fnd(v, i)) {
                res++;
            }
        }
        cout << res << endl;
    }
}
```
核心实现思想：`init` 函数初始化二维并查集；`fnd` 函数查找祖先节点并路径压缩；`add` 函数合并节点；`solve` 函数读入数据、处理边和询问，通过遍历颜色判断两点连通性统计答案。

 - **作者：Priori_Incantatem (赞：3)  星级：4星**
    - **关键亮点**：对二维并查集含义解释清晰，通过具体例子帮助理解，代码逻辑清晰，易于学习。
```cpp
int find(int x,int i) //二维并查集
{
    if(f[x][i]==x)return x;
    return f[x][i]=find(f[x][i],i);
}
int main()
{
    n=read(),m=read();

    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            f[i][j]=i; // 并查集初始化
    for(int i=1;i<=m;++i)
    {
        int x=read(),y=read(),c=read();
        f[find(x,c)][c]=find(y,c); // 维护并查集
    }
    q=read();

    while(q--)
    {
        int x=read(),y=read(),tot=0;
        for(int i=1;i<=m;++i)
            if(find(x,i)==find(y,i))++tot;
        printf("%d\n",tot);
    }

    return 0;
}
```
核心实现思想：`find` 函数查找祖先并路径压缩；主函数中初始化二维并查集，读入边维护并查集，读入询问通过遍历颜色判断两点在对应颜色并查集中是否连通统计答案。

 - **作者：ahawzlc (赞：0)  星级：4星**
    - **关键亮点**：采用分块思想优化并查集，对不同数量的颜色边采用不同策略，在大数据量下能有效降低复杂度。
```cpp
int find(int x) {//并查集
    return f[x]==x?x:f[x]=find(f[x]);
}
void merge(int x,int y) {
    x=find(x),y=find(y);
    if(x!=y) {
        if(d[x]<d[y]) swap(x,y);
        f[y]=x;
        if(d[x]==d[y]) d[x]++;
    }
}
int main() {
    n=read(),m=read();
    for(int i=1; i<=n; i++) f[i]=i;
    for(int i=1; i<=m; i++) {
        e[i].x=read(),e[i].y=read(),e[i].z=read();
        if(e[i].x>e[i].y) swap(e[i].x,e[i].y);//确保x<y 
    }
    sort(e+1,e+m+1);//按颜色排序 
    q=read();
    for(int i=1,j=1; i<=m; i=++j) {
        while(e[j].z==e[j+1].z) j++;//j的位置是最后一条该颜色的边 
        for(int k=i; k<=j; k++) merge(e[k].x,e[k].y);//做并查集 
        int tot=j-i+1; 
        if(tot<sqrt(m)) {//分块 
            siz=0;
            for(int k=i; k<=j; k++) tmp[++siz]=e[k].x,tmp[++siz]=e[k].y;//记录该颜色边所连接的点 
            sort(tmp+1,tmp+siz+1);
            siz=unique(tmp+1,tmp+siz+1)-tmp-1;//去重 
            for(int x=1; x<siz; x++)
                for(int y=x+1; y<=siz; y++)
                    if(find(tmp[x])==find(tmp[y])) p[mp(tmp[x],tmp[y])]++;//在同一连通块，往点对上添加答案 
        } else for(int k=1; k<=q; k++) ans[k]+=(find(qx[k])==find(qy[k]));//直接扫询问统计答案 
        for(int k=i; k<=j; k++) f[e[k].x]=e[k].x,f[e[k].y]=e[k].y,d[e[k].x]=d[e[k].y]=0;//清空 
    }
    for(int i=1; i<=q; i++) {
        if(p.find(mp(qx[i],qy[i]))!=p.end()) ans[i]+=p[mp(qx[i],qy[i])];//统计点对对答案的贡献 
        printf("%d\n",ans[i]);
    }
    return 0;
}
```
核心实现思想：`find` 函数查找祖先并路径压缩，`merge` 函数按秩合并。主函数中读入数据并按颜色排序，遍历颜色边，根据边数分块处理，对边做并查集，用 `map` 统计点对贡献或直接扫询问统计答案，最后输出答案。

### 最优关键思路或技巧
并查集是解决本题关键，尤其是二维并查集的使用，能高效维护不同颜色下点的连通性。分块优化并查集根据颜色边数量不同采用不同策略，在大数据量下优化效果显著，值得学习。

### 可拓展思路
此类题目拓展方向多为增加数据规模或改变图结构。类似算法套路是遇到维护连通性问题且数据范围不大时，优先考虑并查集；若数据规模大，可思考如分块等优化策略。

### 洛谷相似题目推荐
 - [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：基础并查集应用，通过并查集判断亲戚关系。
 - [P1197 星球大战](https://www.luogu.com.cn/problem/P1197)：并查集与图结合，在动态删点过程中维护连通块数量。
 - [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)：并查集模板题，可巩固并查集基本操作。

### 个人心得摘录及总结
暂无题解包含个人心得。 

---
处理用时：131.82秒