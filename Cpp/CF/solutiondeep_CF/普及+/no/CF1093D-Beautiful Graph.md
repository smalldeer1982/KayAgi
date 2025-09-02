# 题目信息

# Beautiful Graph

## 题目描述

You are given an undirected unweighted graph consisting of $ n $ vertices and $ m $ edges.

You have to write a number on each vertex of the graph. Each number should be $ 1 $ , $ 2 $ or $ 3 $ . The graph becomes beautiful if for each edge the sum of numbers on vertices connected by this edge is odd.

Calculate the number of possible ways to write numbers $ 1 $ , $ 2 $ and $ 3 $ on vertices so the graph becomes beautiful. Since this number may be large, print it modulo $ 998244353 $ .

Note that you have to write exactly one number on each vertex.

The graph does not have any self-loops or multiple edges.

## 说明/提示

Possible ways to distribute numbers in the first test:

1. the vertex $ 1 $ should contain $ 1 $ , and $ 2 $ should contain $ 2 $ ;
2. the vertex $ 1 $ should contain $ 3 $ , and $ 2 $ should contain $ 2 $ ;
3. the vertex $ 1 $ should contain $ 2 $ , and $ 2 $ should contain $ 1 $ ;
4. the vertex $ 1 $ should contain $ 2 $ , and $ 2 $ should contain $ 3 $ .

In the second test there is no way to distribute numbers.

## 样例 #1

### 输入

```
2
2 1
1 2
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
4
0
```

# AI分析结果

### 题目内容
# 美丽的图

## 题目描述
给定一个无向无权图，包含$n$个顶点和$m$条边。

你需要在图的每个顶点上写一个数字。每个数字应为$1$、$2$或$3$。如果对于每条边，连接该边的顶点上数字之和为奇数，则该图变得美丽。

计算在顶点上写数字$1$、$2$和$3$以使图变得美丽的可能方法数。由于这个数字可能很大，将其对$998244353$取模后输出。

注意，你必须在每个顶点上恰好写一个数字。

该图没有任何自环或重边。

## 说明/提示
第一个测试用例中分配数字的可能方法：
1. 顶点$1$应包含$1$，顶点$2$应包含$2$；
2. 顶点$1$应包含$3$，顶点$2$应包含$2$；
3. 顶点$1$应包含$2$，顶点$2$应包含$1$；
4. 顶点$1$应包含$2$，顶点$2$应包含$3$。

在第二个测试用例中，没有分配数字的方法。

## 样例 #1
### 输入
```
2
2 1
1 2
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```
### 输出
```
4
0
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路均基于二分图的性质。由于要求每条边连接的两个顶点数字之和为奇数，可知相连顶点的数字奇偶性必须不同，这等价于判断图是否为二分图。对于每个连通块，通过二分图染色来确定是否存在合法的数字分配方式，若能成功染色，统计两种颜色顶点的数量，根据乘法原理计算每个连通块的方案数，再将所有连通块的方案数相乘得到最终结果。不同题解在实现细节上略有差异，如使用的搜索方式（BFS或DFS）、数据结构（邻接表或邻接矩阵）以及代码的优化程度等。

### 所选的题解
- **作者：LJC00118 (5星)**
    - **关键亮点**：思路清晰，代码简洁高效，采用BFS染色，通过位运算实现快速幂，避免使用可能导致超时的memset函数。
    - **重点代码**：
```cpp
inline int mul(int x, int y) { return (ll)x * y % mod; }
inline int add(int x, int y) {
    x += y;
    if(x >= mod) x -= mod;
    return x;
}
inline int fpow(int x, int y) {
    int ans = 1;
    while(y) {
        if(y & 1) ans = mul(ans, x);
        y >>= 1; x = mul(x, x);
    }
    return ans;
}
queue <int> q;
vector <int> adj[N];
int f[N];
int T, n, m, cnt1, cnt2, ans;
int main() {
    read(T); while(T--) {
        read(n); read(m); ans = 1;
        for(register int i = 1; i <= n; i++) f[i] = -1, adj[i].clear();
        for(register int i = 1; i <= m; i++) {
            int a, b; read(a); read(b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        for(register int i = 1; i <= n; i++) {
            if(~f[i]) continue;
            cnt1 = 1; cnt2 = 0; f[i] = 1; q.push(i);
            while(!q.empty()) {
                int u = q.front(); q.pop();
                for(register int j = 0; j < (int)adj[u].size(); j++) {
                    int v = adj[u][j];
                    if(f[v] == -1) {
                        f[v] = 3 - f[u];
                        if(f[v] == 1) cnt1++; else cnt2++;
                        q.push(v);
                    } else if(f[v]!= 3 - f[u]) {
                        ans = 0; break;
                    }
                }
            }
            if(!ans) break;
            ans = mul(ans, add(fpow(2, cnt1), fpow(2, cnt2)));
        }
        print(ans, '\n');
    }
    return 0;
}
```
    - **核心实现思想**：通过BFS对每个连通块进行染色，在染色过程中统计两种颜色顶点的数量，利用快速幂计算$2$的幂次方，进而得出每个连通块的方案数并相乘。
- **作者：fmj_123 (4星)**
    - **关键亮点**：详细阐述思路，从题目大意分析到具体算法实现，逻辑连贯，使用数组模拟邻接表，代码易读。
    - **重点代码**：
```cpp
void addedge(int u,int v)
{
    cc++;
    to[cc]=v;net[cc]=fr[u];fr[u]=cc;
}
long long p(int x)
{
    long long ans=1,kk=2;
    while (x)
    {
        if (x&1) 
        {
            ans*=kk;
            ans%=mod;
        }
        kk*=kk;
        kk%=mod;
        x>>=1;
    }
    return ans;
}
int main()
{
    scanf("%d",&ttt);
    for (int tt=1;tt<=ttt;tt++)
    { 
      scanf("%d%d",&n,&m);
      for (int i=1;i<=m;i++)
      {
      	 scanf("%d%d",&u,&v);
      	 addedge(u,v);
      	 addedge(v,u);
      }
      int bb=1;ans=1;
      while (1)
      {
      	 h=1;t=1;q[1]=bb;vis[bb]=1;color[bb]=1;cnt1=1;
      	 while (h<=t)
      	 {
      	 	 for (int i=fr[q[h]];i;i=net[i])
      	 	 {
      	 	 	int y=to[i];
      	 	 	if (!vis[y])
      	 	 	{
      	 	 		color[y]=3-color[q[h]];
      	 	 		if (color[y]==1) cnt1++; 
      	 	 		q[++t]=to[i];
      	 	 		vis[y]=1;
      	 	 	}
      	 	 	else
      	 	 	{
      	 	 		if (color[y]!=3-color[q[h]]) ans=0;
      	 	 	}
      	 	 }
      	 	 h++;
      	 }
      	 ans*=(p(cnt1)%mod+p(t-cnt1)%mod)%mod;
      	 ans%=mod;
      	 for (int i=bb+1;i<=n;i++)
      	 {
      	 	 if (!vis[i]) {bb=i;break;}
      	 }
      	 if (bb==q[1]) break;
      }
      for (int i=1;i<=n;i++)
        fr[i]=0,vis[i]=false,color[i]=0;
      cc=0;
      printf("%d\n",ans%mod);
    }
    return 0;
}
```
    - **核心实现思想**：通过自定义函数`addedge`构建邻接表，使用BFS进行染色，在染色过程中统计奇数顶点数量，利用快速幂计算方案数并累乘。
- **作者：轻绘 (4星)**
    - **关键亮点**：直接点明算法为二分图染色，思路阐述结合相关知识点链接，便于读者深入理解，代码使用DFS进行染色。
    - **重点代码**：
```cpp
inline void dfs(int now,int fa){
    for(int i=h[now];i;i=nex[i]){
        if(v[i]==fa)	continue;
        if(num[v[i]]==num[now]){
            f=1,k=0;
            return;
        }
        if(used[v[i]])	continue;
        used[v[i]]=1,++all;
        if(num[now]==1)	num[v[i]]=2;
        else	num[v[i]]=1,++k; 
        dfs(v[i],now);
        if(f)	return;
    }
}
int pu,w;
inline int pw(int a,int b){
    pu=1,w=a;
    while(b){
        if(b&1)	pu=(pu%p*w%p)%p;
        w=(w*w)%p;
        b>>=1;
    }
    return pu%p;
}
signed main(){
    t=read();
    while(t--){
        n=read(),m=read();
        for(int i=1;i<=m;++i){
            int x=read(),y=read();
            add(x,y),add(y,x);
        }
        for(int i=1;i<=n;++i){
            if(used[i])	continue;
            k=1,f=0,all=1;
            used[i]=1,num[i]=1;
            dfs(i,i);
            if(k)
                k=(pw(2,k)%p+pw(2,all-k)%p)%p;
            k=k%p;
            ans=(k%p*ans%p)%p;
        }
        for(int i=1;i<=tot;++i)
            nex[i]=0,v[i]=0;
        for(int i=1;i<=n;++i)
            h[i]=0,num[i]=0,used[i]=0;
        tot=0;
        printf("%lld\n",ans%p);
        ans=1;
    }	
    return 0;
} 
```
    - **核心实现思想**：利用DFS对每个连通块进行染色，在染色过程中判断是否出现矛盾，统计奇数顶点数量，通过快速幂计算每个连通块方案数并相乘。

### 最优关键思路或技巧
- **二分图性质的应用**：将问题转化为二分图的判定与染色，通过判断图是否为二分图来确定是否存在合法方案，利用二分图染色结果计算方案数。
- **快速幂优化**：为高效计算$2$的幂次方，采用快速幂算法，通过位运算减少计算次数，提高效率。
- **避免全局memset**：由于多组数据，使用全局memset可能导致超时，题解中采用局部初始化或其他方式替代，如清空数组或使用更高效的数据结构操作。

### 同类型题或类似算法套路
此类题目通常围绕图的性质与数字分配规则展开，关键在于发现题目条件与二分图性质的联系。类似套路包括：
- 给定图的某种限制条件（如顶点或边的属性约束），判断图是否满足特定结构（如二分图、连通图等），并基于此计算方案数或进行其他操作。
- 对于多组数据的情况，注意优化初始化操作，避免时间复杂度高的全局操作。

### 洛谷题目推荐
- **P3386 【模板】二分图匹配**：经典的二分图匹配问题，通过匈牙利算法解决，与本题同样涉及二分图相关概念。
- **P1330 封锁阳光大学**：需要对图进行黑白染色，判断是否为二分图，并根据染色结果进行后续计算，与本题思路相似。
- **P1640 序列**：通过分析条件构建二分图模型，利用二分图匹配求解，有助于加深对二分图应用的理解。

### 个人心得摘录与总结
- **作者：灵光一闪**：调试过程中发现误以为图是连通图的错误，同时意识到`ans`初值设为$0$是错误的，强调了对图连通性的判断以及变量初始化的重要性。 

---
处理用时：98.68秒