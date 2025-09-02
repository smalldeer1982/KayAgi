# 题目信息

# [KSN2021] Binary Land

## 题目描述

给定一张 $N$ 个点的图，每个点有权值 $A_i$ 和价值 $B_i$。

两个点 $x,y$ 之间存在一条无向边当且仅当 $A_x\text{ xor }A_y>\max(A_x,A_y)$。

你需要对于 $i=1,2,\cdots n$ 依次求出点 $i$ 所在连通块中所有点的价值和。

## 说明/提示

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（8 points）：只存在一组数据，满足 $N=8$，$A=[6,39,11,63,3,39,1,43]$，$B=[4,8,3,7,9,1,2,2]$。
- Subtask 2（13 points）：保证 $N \leq 200$。
- Subtask 3（10 points）：保证 $N \leq 2000$。
- Subtask 4（4 points）：保证 $A_1=A_2=\cdots=A_n$。
- Subtask 5（7 points）：保证存在非负整数 $k$ 使得 $A_i=2^k$。
- Subtask 6（19 points）：$A_i\leq 2^{12}-1$。
- Subtask 7（39 points）：无特殊限制。

对于所有数据，$1 \leq N \leq 10^5$，$1 \leq A_i \leq 2^{30}-1$，$1 \leq B_i \leq 10^9$。

## 样例 #1

### 输入

```
3
2 1 1
20 30 10```

### 输出

```
60
60
60```

## 样例 #2

### 输入

```
4
5 4 4 5
10 20 30 40```

### 输出

```
10
20
30
40```

## 样例 #3

### 输入

```
5
1 2 1 7 11
20 10 30 100 100```

### 输出

```
60
60
60
200
200```

# AI分析结果

### 综合分析与结论
这些题解的核心思路均围绕对条件 $A_x \oplus A_y > \max(A_x, A_y)$ 的分析，将其转化为二进制位的关系，再利用并查集维护连通块信息，计算每个点所在连通块的价值和。各题解在具体实现和优化细节上有所不同，但整体方向一致。

### 所选题解
- **作者：EXODUS (赞：28) - 4星**
    - **关键亮点**：思路清晰，对条件的二进制分析详细，通过多维护 30 个并查集优化连边过程，代码实现简洁明了。
- **作者：Jairon314 (赞：5) - 4星**
    - **关键亮点**：对条件的等价命题证明严谨，使用启发式合并优化并查集，复杂度分析准确。
- **作者：NATO (赞：2) - 4星**
    - **关键亮点**：对不同子任务有针对性的分析，按位考虑并利用并查集合并连通块，思路简洁高效。

### 重点代码及核心实现思想
#### EXODUS 的题解
```cpp
int find(int i){while(i!=fa[i])i=fa[i]=fa[fa[i]];return i;}
void merge(int x,int y){x=find(x),y=find(y);if(x==y)return;fa[x]=y,sum[y]+=sum[x];}
// ...
for(int i=1;i<=n;i++){
    for(int j=bit,flag=1;~j;j--){
        if((a[i]&(1<<j))&&flag)vis1[j]=1,flag=0,hib[i]=j;
        if((!(a[i]&(1<<j)))&&(!flag))vis2[j]=1;
    }
}
for(int i=1;i<=n;i++){
    if(vis2[hib[i]])merge(i,hib[i]+n+1);
    for(int j=hib[i],flag=1;~j;j--){
        if(!(a[i]&(1<<j))&&vis1[j])merge(i,j+n+1);
    }
}
```
**核心思想**：先预处理每个数的最高位和有 0 的位，再根据条件合并对应的并查集，最后输出每个点所在并查集的价值和。

#### Jairon314 的题解
```cpp
struct dsu{
    int Siz;
    vii par,siz,val;
    dsu(){}
    dsu(int n):Siz(n),par(n+1),siz(n+1),val(n+1){ FOR(i,1,n){ siz[i]=1,par[i]=i,val[i]=B[i]; } }
    int find(int x){ return x==par[x]?par[x]:par[x]=find(par[x]); }
    bool same(int u,int v){ return find(u)==find(v); }
    int count(int x){ return siz[find(x)]; }
    int get_val(int x){ return val[find(x)]; }
    void unite(int u,int v){
        u=find(u),v=find(v);
        if(u==v){ return; }
        if(siz[u]<siz[v]){ swap(u,v); }
        val[u]+=val[v]; siz[u]+=siz[v]; par[v]=u;
        return;
    }
};
// ...
ROF(bit,31,1){
    vii vec; bool flag=false,FLAG=false;
    FOR(i,1,n){ if( dig(A[i],bit)==1 && A[i]<(1<<(bit)) ){   vec.pb(i); FLAG=true; } }
    FOR(i,1,n){ if( dig(A[i],bit)==0 && A[i]>(1<<(bit-1)) ){ vec.pb(i); flag=true; } }
    if(!flag||!FLAG){ continue; } FOR(i,1,(int)vec.size()-1){ uf.unite(vec[i],vec[i-1]); }
}
```
**核心思想**：定义并查集结构体，枚举每一位，找到满足条件的点加入向量，若该位同时存在满足不同条件的点，则合并向量中的点。

#### NATO 的题解
```cpp
ll find(ll x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}
void merge(ll a,ll b)
{
    if(find(a)==find(b))return;
    sum[find(b)]+=sum[find(a)];cv[find(b)]|=cv[find(a)];f[find(a)]=find(b);
}
// ...
sort(a+1,a+1+n);
for(ll i=1;i<=n;++i)
{
    f[i]=i;sum[i]=a[i].b;
    ll cnt=0,now=1;
    while(now*2<=a[i].a)now*=2,++cnt;
    cv[i]=now;
    for(ll j=cnt;j>=0;--j)
        if(((a[i].a>>j)&1)==0)
        {
            for(auto it:h[j])merge(it,i);
            h[j].clear();
        }
    for(ll j=cnt;j>=0;--j)
        if((cv[find(i)]>>j)&1)
        h[j].emplace_back(find(i));
}
```
**核心思想**：先对所有点按权值排序，然后遍历每个点，根据其二进制位的情况合并连通块，同时更新连通块信息。

### 最优关键思路或技巧
- **二进制分析**：将条件 $A_x \oplus A_y > \max(A_x, A_y)$ 转化为二进制位的关系，如 $\text{zero}(A_x,\text{highbit}(A_y)) = 1$，简化判断过程。
- **并查集优化**：多维护多个并查集或使用启发式合并，减少连边的复杂度。

### 可拓展之处
同类型题可能会改变图的连边条件，或在连通块的计算上增加更多要求，如求连通块的数量、最大连通块的大小等。类似算法套路可用于处理其他涉及位运算和图连通性的问题，如最小生成树、图的遍历等。

### 推荐题目
- P1197 [JSOI2008]星球大战
- P1525 [NOIP2010 提高组] 关押罪犯
- P3367 [模板] 并查集

### 个人心得
- **ycy1124**：考场想到正解然后因为细节挂了 50 分。
**总结**：即使想到了正确的思路，也不能忽视细节，在实现代码时要仔细检查，避免因小错误导致丢分。

---
处理用时：43.30秒