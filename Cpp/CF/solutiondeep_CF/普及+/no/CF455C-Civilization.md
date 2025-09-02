# 题目信息

# Civilization

## 题目描述

给出一个由 $n$ 个点，$m$ 条边组成的森林，有 $q$ 组询问

1. 给出点 $x$，输出点 $x$所在的树的直径  
2. 给出点 $x,y$，（如果 $x,y$ 在同一棵树中则忽略此操作）选择任意两点 $u,v$，使得 $u$ 跟 $x$ 在同一棵树中且 $v$ 跟 $y$ 在同一棵树中。将 $u,v$ 之间连一条边，使得连边后的到的新树的直径最小

## 说明/提示

$1 \le m < n \le 3\cdot 10^5$  
$1 \le q \le 3 \cdot 10^5$  
感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
6 0 6
2 1 2
2 3 4
2 5 6
2 3 2
2 5 3
1 1
```

### 输出

```
4
```

# AI分析结果

### 题目内容
# Civilization

## 题目描述
给出一个由 $n$ 个点，$m$ 条边组成的森林，有 $q$ 组询问：
1. 给出点 $x$，输出点 $x$ 所在的树的直径。
2. 给出点 $x,y$，（如果 $x,y$ 在同一棵树中则忽略此操作）选择任意两点 $u,v$，使得 $u$ 跟 $x$ 在同一棵树中且 $v$ 跟 $y$ 在同一棵树中。将 $u,v$ 之间连一条边，使得连边后得到的新树的直径最小。

## 说明/提示
$1 \le m < n \le 3\cdot 10^5$  
$1 \le q \le 3 \cdot 10^5$  
感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1
### 输入
```
6 0 6
2 1 2
2 3 4
2 5 6
2 3 2
2 5 3
1 1
```
### 输出
```
4
```

### 算法分类
并查集

### 综合分析与结论
所有题解的核心思路都是利用并查集维护森林中树的连通性，同时通过树形DP或两次DFS求出每棵树的直径。对于操作2，关键在于证明连接两棵树直径的中点能使新树直径最小，并推导出合并后新树直径的计算公式。各题解在代码实现上略有差异，如求树直径的具体方式、向上取整的处理等，但整体思路一致。

### 所选的题解
- **作者：Priori_Incantatem (5星)**
    - **关键亮点**：思路清晰，详细解释了合并后树直径公式的推导过程，并通过图示说明，代码实现简洁明了，对向上取整采用了巧妙的位运算优化。
    - **个人心得**：强调了在计算合并后树直径时要考虑原两棵树直径的重要性，否则会导致得分不全。
    - **重点代码 - 核心实现思想**：通过树形DP的dfs函数求树的直径，calc函数调用dfs并记录每棵树的直径，在main函数中处理询问，操作2中利用并查集合并两棵树并更新直径。
```cpp
void dfs(int x,int fa) // 树形DP求树的直径
{
    int m1=-1,m2=-1;
    for(int i=0;i<e[x].size();++i)
    {
        int y=e[x][i];
        if(y==fa)continue;
        dfs(y,x);
        int tmp=d[y]+1;
        d[x]=max(d[x],tmp);
        if(tmp>m1)m2=m1,m1=tmp;
        else if(tmp>m2)m2=tmp;
    }
    g[x]=max(max(0,m1+m2),max(m1,m2));
    len=max(len,g[x]);
}
void calc(int x) // 寻找树的直径
{
    len=0;
    dfs(x,0);
    c[x]=len;
}
int main()
{
    n=read(),m=read(),q=read();

    for(int i=1;i<=n;++i)
        f[i]=i;

    for(int i=1;i<=m;++i)
    {
        int x=read(),y=read();
        f[find(x)]=find(y);
        e[x].push_back(y);
        e[y].push_back(x);
    }

    for(int i=1;i<=n;++i)
    {
        if(f[i]!=i || vis[i])continue;
        calc(i);
        vis[i]=1;
    }

    while(q--)
    {
        int opt=read(),x=read();
        if(opt==1)
        {
            printf("%d\n",c[find(x)]);
            continue;
        }
        int y=read();
        x=find(x),y=find(y);
        if(x==y)continue;
        int tmp=((c[x]+1)>>1)+((c[y]+1)>>1)+1; //一个巧妙的向上取整的方法

        tmp=max(tmp,max(c[x],c[y]));

        f[find(x)]=find(y);
        c[find(x)]=tmp;
    }

    return 0;
}
```
- **作者：IGA_Indigo (4星)**
    - **关键亮点**：代码简洁，采用两次DFS求树的直径，在合并树时利用性质优化常数，避免TLE。
    - **重点代码 - 核心实现思想**：通过dfs函数两次搜索求树直径，hb函数用于合并两棵树并更新直径，main函数处理输入和询问。
```cpp
void dfs(int x,int sum,int fa){
    if(sum>maxx){
        maxx=sum;
        maxb=x;
    }
    for(auto v:s[x]){
        if(v==fa){
            continue ;
        }
        dfs(v,sum+1,x);
    }
}
void hb(int x,int y){
    int maxxx=max(wei[x],wei[y]);
    fa[x]=y;
    wei[y]=max(maxxx,(wei[x]+1)/2+(wei[y]+1)/2+1);
} 
int main(){
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        s[x].push_back(y);
        s[y].push_back(x);
        fa[find(x)]=find(y);
    }
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            maxb=i; 
            maxx=0;
            dfs(i,0,0);
            maxx=0;
            dfs(maxb,0,0);
            wei[i]=maxx;                
        }
    }
    for(int i=1;i<=q;i++){
        int t;
        scanf("%d",&t);
        if(t==1){
            int x;
            scanf("%d",&x);
            int xfa=find(x);
            cout<<wei[xfa]<<'\n';
        }
        if(t==2){
            int x,y;
            scanf("%d%d",&x,&y);
            int xf=find(x),yf=find(y);
            if(xf!=yf){
                hb(xf,yf);
            }
        }
    }
    return 0;
}
```
- **作者：yty2010 (4星)**
    - **关键亮点**：代码结构清晰，分部分详细阐述了并查集构建、树直径求解和操作处理的过程，对每个部分的代码都有详细注释。
    - **重点代码 - 核心实现思想**：find函数用于并查集查找祖宗节点，dfs函数两次搜索求树直径，merge函数合并两棵树并更新直径，main函数处理输入、初始化并查集、计算树直径以及处理询问。
```cpp
int find(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x]=find(fa[x]);
}
void dfs(int k,int sum,int pre)
{
    if(sum>maxn)
    {
        maxn=sum;
        maxs=k;
    }
    for(int i=0;i<vec[k].size();i++)
    {
        int v=vec[k][i];
        if(v==pre)
            continue;
        dfs(v,sum+1,k);
    }
}
void merge(int x,int y)
{
    int lx=siz[x];
    int ly=siz[y];
    fa[x]=y;
    siz[y]=max(max(lx,ly),(lx+1)/2+(ly+1)/2+1);
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        fa[find(x)]=find(y);
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    for(int i=1;i<=n;i++)
    {
        if(i==find(i))
        {
            maxs=i;
            maxn=0;
            dfs(i,0,0);
            maxn=0;
            dfs(maxs,0,0);
            siz[i]=maxn;
        }
    }
    while(q--)
    {
        int t;
        cin>>t;
        if(t==1)
        {
            int x;
            cin>>x;
            cout<<siz[find(x)]<<endl;
        }
        else
        {
            int x,y;
            cin>>x>>y;
            int fx=find(x),fy=find(y);
            if(fx!=fy)
                merge(fx,fy);
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **数据结构**：利用并查集高效维护森林中树的连通性，快速判断两点是否在同一棵树中，并在合并树时更新相关信息。
2. **算法优化**：通过树形DP或两次DFS求树的直径，在合并树时，证明并利用连接两棵树直径中点能使新树直径最小这一结论，推导出新树直径的计算公式，避免了暴力枚举带来的高复杂度。
3. **代码实现技巧**：在计算向上取整时，采用位运算 `(x + 1) >> 1` 等方式优化代码，提高运行效率。

### 同类型题或类似算法套路
此类题目通常围绕树或森林结构，结合并查集维护连通性，同时需要对树的某些性质（如直径、深度等）进行分析和计算。常见的套路是先预处理出每棵树的相关属性，再根据题目要求进行操作，操作过程中利用并查集合并树，并通过推导得出的公式更新树的属性。

### 相似知识点的洛谷题目
1. **P3367 【模板】并查集**：基础的并查集模板题，用于熟悉并查集的基本操作。
2. **P2195 HXY造公园**：与本题类似，涉及树的合并以及直径相关问题，可进一步巩固相关知识点。
3. **P1551 亲戚**：通过并查集判断亲戚关系，加深对并查集在实际问题中应用的理解。

### 个人心得摘录与总结
- Priori_Incantatem提到在计算合并后树直径时，要考虑原两棵树的直径，否则会导致得分不全，这强调了全面考虑问题的重要性，在处理复杂问题时不能忽略边界情况或原有的重要信息。 

---
处理用时：109.55秒