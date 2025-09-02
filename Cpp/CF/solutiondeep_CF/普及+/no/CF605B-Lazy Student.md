# 题目信息

# Lazy Student

## 题目描述

给定 $n, m, a _ {1, \cdots, m}, b _ {1, \cdots, m}$，构造一个无重边自环的 $n$ 个点 $m$ 条边的无向连通图，满足第 $i$ 条边边权为 $a _ i$，且所有 $b _ i = 1$ 的边 $i$ 组成了该图的一棵最小生成树。

$2 \le n \le 10 ^ 5, n - 1 \le m \le \min(\frac{n(n - 1)}{2}, 10 ^ 5)$。

## 样例 #1

### 输入

```
4 5
2 1
3 1
4 0
1 1
5 0
```

### 输出

```
2 4
1 4
3 4
3 1
3 2
```

## 样例 #2

### 输入

```
3 3
1 0
2 1
3 1
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 懒惰的学生

## 题目描述
给定 \(n, m, a_{1,\cdots,m}, b_{1,\cdots,m}\) ，构造一个无重边自环的 \(n\) 个点 \(m\) 条边的无向连通图，满足第 \(i\) 条边边权为 \(a_i\) ，且所有 \(b_i = 1\) 的边 \(i\) 组成了该图的一棵最小生成树。

\(2 \leq n \leq 10^5, n - 1 \leq m \leq \min(\frac{n(n - 1)}{2}, 10^5)\) 。

## 样例 #1
### 输入
```
4 5
2 1
3 1
4 0
1 1
5 0
```
### 输出
```
2 4
1 4
3 4
3 1
3 2
```

## 样例 #2
### 输入
```
3 3
1 0
2 1
3 1
```
### 输出
```
-1
```

### 算法分类
构造

### 综合分析与结论
这几道题解思路大致相同，均是基于贪心思想，通过倒推Kruskal算法来构造满足条件的图。先将所有边按边权从小到大排序，边权相同则树边在前。对于树边，新开节点与1号点相连构造菊花图；对于非树边，在已有的节点内连边。难点在于如何确保非树边的连接不会产生重边且满足图的连通性要求，各题解通过设定特定的连边规则和条件判断来解决此难点。

### 所选的题解
- **作者：Leap_Frog (5星)**
  - **关键亮点**：思路清晰，代码简洁高效，直接通过倒推Kruskal算法实现构造，利用排序和特定规则处理树边与非树边。
  - **重点代码核心思想**：按边权和是否为树边排序后，树边新开节点，非树边按特定规则在已有节点内连边，最后按原输入顺序输出。
```cpp
struct node{int w,id,fr,tw;char fg;}a[100005];int n,m,l=2,r=3,id=1;
int main()
{
    read(n),read(m);for(int i=1;i<=m;i++) read(a[i].w),read(a[i].fg),a[i].id=i;
    sort(a+1,a+m+1,[](node a,node b){return a.w<b.w||(a.w==b.w&&a.fg>b.fg);});
    for(int i=1;i<=m;i++)
    {
        if(a[i].fg) {a[i].fr=1,a[i].tw=++id;continue;}
        if(r>id) return puts("-1"),0;
        a[i].fr=l++,a[i].tw=r;if(l==r) r++,l=2;
    }sort(a+1,a+m+1,[](node a,node b){return a.id<b.id;});
    for(int i=1;i<=m;i++) printf("%d %d\n",a[i].fr,a[i].tw);
    return 0;
}
```
- **作者：Aisaka_Taiga (5星)**
  - **关键亮点**：同样采用菊花图构造方式，代码逻辑清晰，通过计数器和特定指针操作处理树边与非树边的连接。
  - **重点代码核心思想**：排序后，树边与1号点相连并增加计数器，非树边按规则在已有节点内连边，判断无解情况后按原序输出。
```cpp
int n,m,cnt=1,u=2,v=3,flag=1;
struct sb{int u,v,w,id,flag;}e[N];
inline int cmp1(sb a,sb b){if(a.w==b.w)return a.flag>b.flag;return a.w<b.w;}
inline int cmp2(sb a,sb b){return a.id<b.id;}
signed main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++)e[i].w=read(),e[i].flag=read(),e[i].id=i;
    sort(e+1,e+m+1,cmp1);
    for(int i=1;i<=m;i++)
    {
        if(e[i].flag)e[i].u=1,e[i].v=++cnt;
        else
        {
            if(v>cnt){flag=0;break;}
            e[i].u=u++;e[i].v=v;
            if(u==v)v++,u=2;
        }
    }
    if(!flag){cout<<"-1"<<endl;return 0;}
    sort(e+1,e+m+1,cmp2);
    for(int i=1;i<=m;i++)cout<<e[i].u<<" "<<e[i].v<<endl;
    return 0;
}
```
- **作者：osfly (5星)**
  - **关键亮点**：对Leap_Frog大佬的题解进行详细补充，通过图文并茂的方式解释构造过程，代码清晰易读。
  - **重点代码核心思想**：与上述类似，排序后树边连接1号点并增加已开节点数，非树边按特定规则在已有节点内连边，判断无解后按原序输出。
```cpp
int n,m;
struct edge
{
    int u;
    int v;
    int w;
    int id;
    int yes;
}e[100010];
int tot=1;
bool cmp1(edge a,edge b)
{
    if(a.w==b.w) return a.yes>b.yes;
    return a.w<b.w;
}
bool cmp2(edge a,edge b)
{
    return a.id<b.id;
}
int u=2,v=3;
bool flag=1;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&e[i].w,&e[i].yes);
        e[i].id=i;
    }
    sort(e+1,e+1+m,cmp1);
    for(int i=1;i<=m;i++)
    {
        if(e[i].yes) e[i].u=1,e[i].v=++tot;
        else
        {
            if(v>tot)
            {
                flag=0;
                break;
            }
            e[i].u=u++;
            e[i].v=v;
            if(u==v) v++,u=2;
        }
    }
    if(!flag) printf("-1");
    else
    {
        sort(e+1,e+1+m,cmp2);
        for(int i=1;i<=m;i++) printf("%d %d\n",e[i].u,e[i].v);
    }
    return 0;
}
```

### 最优关键思路或技巧
- **排序与贪心**：按边权和是否为树边进行双关键字排序，贪心选择边权小且树边优先的策略，保证了最小生成树的构造符合要求。
- **菊花图构造**：以1号点为中心构造菊花图，对于树边直接与1号点相连，简化了图的构造过程，方便处理非树边的连接。
- **非树边连接规则**：设定特定的指针移动规则来连接非树边，确保不产生重边且能充分利用已有的节点，同时通过判断节点数量是否足够来处理无解情况。

### 同类型题或类似算法套路拓展
同类型题通常围绕图的构造展开，给定一些关于图的性质（如最小生成树、最短路径等），要求构造出满足条件的图。类似算法套路是从已知的图算法（如Kruskal、Prim等）逆向思考，结合贪心策略进行图的构造。在构造过程中，要注意边的连接规则以及各种特殊情况（如重边、自环、无解等）的处理。

### 洛谷相似题目推荐
- **P1195 口袋的天空**：同样涉及图的最小生成树相关构造问题，通过连接边使得图满足一定的连通性和最小生成树条件。
- **P3366 【模板】最小生成树**：基础的最小生成树问题，可作为此类问题的基础练习，理解最小生成树算法原理有助于解决本题类型的构造问题。
- **P2820 [NOIP2016 提高组] 运输计划**：结合了图的连通性、路径查询以及最小生成树相关知识，通过对图的操作和分析来解决问题，与本题在图的处理和分析上有相似之处。 

---
处理用时：74.07秒