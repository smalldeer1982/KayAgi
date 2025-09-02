# 题目信息

# [POI 2013] GRA-Tower Defense Game

## 题目描述

Bytie is playing the computer game Tower Defense.

His aim is to construct guard towers, so that they protect all of his domain.

There are multiple towns in Bytie's domain, some of which are linked by  bidirectional roads.

If Bytie erects a guard tower in a city, then the tower protects its city and  all the cities directly linked with it by roads.

Just as Bytie was pondering over the placement of guard towers in his domain,  his elder sister Bytea entered the room.  She glanced at the map displayed on  the screen, and after a moment exclaimed:

"Oi, what is there to think about, clearly $k$ towers suffice!".

Angered by his sister spoiling the fun, Bytie showed his sister the door,  and began wondering what to do next.

Pride will not let him construct more than $k$ towers.

He has an up his sleeve though:

he can research a technology that will allow him to construct improved guard towers.

An improved guard tower protects not only the town it was erected in and its  immediate neighbors but also the towns that are further away.

Formally, an improved guard tower built in the town $u$ protects the town $v$ if either of the following holds:

- $u=v$;

- there is a direct road from $u$ to $v$;

- or there is such a town $w$ that there are direct roads from $u$ to $w$ and from $w$ to $v$.

Of course, Bytie still strives to erect at most $k$ towers,  but he has no qualms about making these the improved guard towers.

有一个n个点m条边的图，每条边距离是1，已知用k个攻击距离为1的塔可以打到整个地图，让构造一个方案使得用小于等于k个攻击距离为2的塔打到整个地图


## 说明/提示

有一个n个点m条边的图，每条边距离是1，已知用k个攻击距离为1的塔可以打到整个地图，让构造一个方案使得用小于等于k个攻击距离为2的塔打到整个地图


## 样例 #1

### 输入

```
9 8 3
1 2
2 3
3 4
1 4
3 5
4 6
7 8
8 9
```

### 输出

```
3
1 5 7 
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路较为一致，均基于已知能用k个攻击距离为1的塔覆盖全图这一条件，得出每次选择一个未被覆盖的点放置攻击距离为2的塔，最终能用不超过k个塔覆盖全图的结论。
 - **思路方面**：多数题解通过分析放置攻击距离为2的塔在不同位置（原攻击距离为1的塔的位置或其他位置）时的覆盖情况，证明该策略的正确性。
 - **算法要点**：采用深度优先搜索（DFS）或直接遍历邻接表的方式标记被塔覆盖的点，实现对图的遍历和覆盖操作。
 - **解决难点**：主要难点在于证明为何选择未被覆盖的点放置攻击距离为2的塔一定能满足要求且不会超过k个塔。各题解通过与原攻击距离为1的塔覆盖方案对比，利用覆盖范围的关系进行证明。

### 所选的题解
#### 作者：EXODUS (5星)
 - **关键亮点**：思路清晰，先提出猜想，再从放置塔的位置与原方案的关系出发，严谨证明结论，代码实现简洁明了，注释详细。
 - **个人心得**：作者表达了对构造题的喜爱，认为用大胆思考、严谨证明和简洁代码解决构造题，正是其魅力所在。
```cpp
// 核心代码实现思路：通过DFS标记距离所选点不超过2的点
void dfs(int now,int stp){
    vis[now]=1;
    if(stp==2)return;
    for(int i=head[now];i;i=e[i].nxt){
        dfs(e[i].to,stp+1);
    }
}

int main(){
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            ans[++tot]=i;
            dfs(i,0);
        }
    }
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++){
        printf("%d ",ans[i]);
    }
    return 0;
}
```
#### 作者：ycy1124 (4星)
 - **关键亮点**：先清晰分析出原方案中炮台的分布特点，进而阐述攻击距离为2的炮台放置策略的原理，逻辑连贯，代码简洁且注释完整。
```cpp
// 核心代码实现思路：通过DFS标记距离所选点不超过2的点
inline void dfs(int p,int f,int w){
    bj[p]=1;
    if(w==2){
        return;
    }
    for(auto it:a[p]){
        if(it==f){
            continue;
        }
        dfs(it,p,w+1);
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!bj[i]){
            ans.push_back(i);
            dfs(i,0,0);
        }
    }
    cout<<ans.size()<<'\n';
    for(auto it:ans){
        cout<<it<<' ';
    }
    return 0;
}
```
#### 作者：Helloworldwuyuze (4星)
 - **关键亮点**：先明确结论，再从原方案中任意点与攻击距离为1的塔的距离关系出发，详细证明结论的正确性，并分析复杂度，逻辑严谨。
```cpp
// 核心代码实现思路：通过DFS标记距离所选点不超过2的点
void dfs(int x, int st){
    vis[x] = true;
    if(st == 2)	return ;
    for(int y:g[x])	dfs(y, st+1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1,x,y;i<=m;++i)	cin>>x>>y, g[x].pb(y), g[y].pb(x);
    for(int i=1;i<=n;++i)
        if(!vis[i])	ans.pb(i), dfs(i, 0);
    cout<<ans.size()<<endl;
    for(int x:ans)	cout<<x<<" ";
    cout<<endl;
    return 0;
}
```

### 最优关键思路或技巧
 - **思维方式**：从原问题（攻击距离为1的塔覆盖全图）出发，类比分析新问题（攻击距离为2的塔覆盖全图），通过证明新策略（每次选未覆盖点放塔）与原方案的关系，得出可行性结论。
 - **代码实现技巧**：利用DFS遍历图，简洁高效地标记被塔覆盖的点，控制遍历深度为2以满足攻击距离为2的要求。

### 同类型题或类似算法套路拓展
此类题目属于图的构造类型，通常基于图的某种已有性质（如本题中攻击距离为1的塔能覆盖全图），构造满足新条件（攻击距离为2的塔覆盖全图）的方案。类似套路包括分析新条件与原条件的差异，通过类比、归纳等方法得出构造策略，并证明其正确性。

### 推荐题目
 - [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及图的节点覆盖问题，与本题类似，需考虑如何选择节点以满足特定覆盖条件。
 - [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)：关于树的构造问题，根据给定条件构造符合要求的树结构，锻炼构造思路。
 - [P2895 [USACO08FEB]Meteor Shower S](https://www.luogu.com.cn/problem/P2895)：在图上进行搜索并构造路径，满足特定的时间和位置条件，与本题在图的操作和条件满足方面有相似之处。 

---
处理用时：33.93秒