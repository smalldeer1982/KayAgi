# 题目信息

# Gifts by the List

## 题目描述

Sasha lives in a big happy family. At the Man's Day all the men of the family gather to celebrate it following their own traditions. There are $ n $ men in Sasha's family, so let's number them with integers from $ 1 $ to $ n $ .

Each man has at most one father but may have arbitrary number of sons.

Man number $ A $ is considered to be the ancestor of the man number $ B $ if at least one of the following conditions is satisfied:

- $ A=B $ ;
- the man number $ A $ is the father of the man number $ B $ ;
- there is a man number $ C $ , such that the man number $ A $ is his ancestor and the man number $ C $ is the father of the man number $ B $ .

Of course, if the man number $ A $ is an ancestor of the man number $ B $ and $ A≠B $ , then the man number $ B $ is not an ancestor of the man number $ A $ .

The tradition of the Sasha's family is to give gifts at the Man's Day. Because giving gifts in a normal way is boring, each year the following happens.

1. A list of candidates is prepared, containing some (possibly all) of the $ n $ men in some order.
2. Each of the $ n $ men decides to give a gift.
3. In order to choose a person to give a gift to, man $ A $ looks through the list and picks the first man $ B $ in the list, such that $ B $ is an ancestor of $ A $ and gives him a gift. Note that according to definition it may happen that a person gives a gift to himself.
4. If there is no ancestor of a person in the list, he becomes sad and leaves the celebration without giving a gift to anyone.

This year you have decided to help in organizing celebration and asked each of the $ n $ men, who do they want to give presents to (this person is chosen only among ancestors). Are you able to make a list of candidates, such that all the wishes will be satisfied if they give gifts according to the process described above?

## 说明/提示

The first sample explanation:

- if there would be no $ 1 $ in the list then the first and the third man's wishes would not be satisfied $ (a_{1}=a_{3}=1) $ ;
- if there would be no $ 2 $ in the list then the second man wish would not be satisfied $ (a_{2}=2) $ ;
- if $ 1 $ would stay before $ 2 $ in the answer then the second man would have to give his gift to the first man, but he wants to give it to himself $ (a_{2}=2) $ .
- if, at the other hand, the man numbered $ 2 $ would stay before the man numbered $ 1 $ , then the third man would have to give his gift to the second man, but not to the first $ (a_{3}=1) $ .

## 样例 #1

### 输入

```
3 2
1 2
2 3
1 2 1
```

### 输出

```
-1```

## 样例 #2

### 输入

```
4 2
1 2
3 4
1 2 3 3
```

### 输出

```
3
2
1
3
```

# AI分析结果

### 题目内容
# 按列表送礼物

## 题目描述
萨沙生活在一个幸福的大家庭中。在男人节这一天，家里所有的男性都会聚在一起，按照他们自己的传统来庆祝。萨沙家有 $n$ 个男性，因此我们用从 $1$ 到 $n$ 的整数给他们编号。

每个男性最多有一个父亲，但可以有任意数量的儿子。

如果满足以下至少一个条件，那么编号为 $A$ 的男性被认为是编号为 $B$ 的男性的祖先：
- $A = B$；
- 编号为 $A$ 的男性是编号为 $B$ 的男性的父亲；
- 存在编号为 $C$ 的男性，使得编号为 $A$ 的男性是他的祖先，并且编号为 $C$ 的男性是编号为 $B$ 的男性的父亲。

当然，如果编号为 $A$ 的男性是编号为 $B$ 的男性的祖先且 $A≠B$，那么编号为 $B$ 的男性就不是编号为 $A$ 的男性的祖先。

萨沙家的传统是在男人节送礼物。因为以普通方式送礼物很无聊，所以每年都会发生以下事情：
1. 准备一份候选人名单，其中包含 $n$ 个男性中的一些（可能是全部），按某种顺序排列。
2. $n$ 个男性中的每个人都决定送一份礼物。
3. 为了选择送礼物的对象，男性 $A$ 会浏览名单，并选择名单上第一个是他祖先的男性 $B$，然后把礼物送给他。注意，根据定义，有可能一个人把礼物送给自己。
4. 如果名单中没有一个人的祖先，他就会难过，然后离开庆祝活动，不送给任何人礼物。

今年你决定帮忙组织庆祝活动，并询问了 $n$ 个男性中的每一个人，他们想把礼物送给谁（这个人只能从祖先中选择）。你是否能够制定一份候选人名单，使得如果他们按照上述过程送礼物，所有的愿望都能得到满足？

## 说明/提示
第一个样例解释：
- 如果名单中没有 $1$，那么第一个和第三个男性的愿望就无法满足（$a_{1}=a_{3}=1$）；
- 如果名单中没有 $2$，那么第二个男性的愿望就无法满足（$a_{2}=2$）；
- 如果 $1$ 在答案中排在 $2$ 之前，那么第二个男性就必须把礼物送给第一个男性，但他想送给自己（$a_{2}=2$）。
- 另一方面，如果编号为 $2$ 的男性排在编号为 $1$ 的男性之前，那么第三个男性就必须把礼物送给第二个男性，而不是第一个男性（$a_{3}=1$）。

## 样例 #1
### 输入
```
3 2
1 2
2 3
1 2 1
```
### 输出
```
-1```

## 样例 #2
### 输入
```
4 2
1 2
3 4
1 2 3 3
```
### 输出
```
3
2
1
3
```

### 算法分类
图论

### 题解综合分析与结论
这三道题解都围绕如何构造满足条件的候选人列表展开。water_tomato 的题解利用拓扑排序和建反图的方式，先确定必要的点，再通过拓扑序遍历判断方案是否可行；封禁用户的题解基于一个结论，即一个结点和其所有祖先拥有同一个喜欢的人，通过自底而上对自恋的人入表来构造方案；xzggzh1 的题解证明了对于甲的祖先里和甲不是同一个目标的人乙必有甲的目标不是乙的祖先这一条件，并基于此从 0 入度点遍历构造方案。三道题解思路各有特点，water_tomato 的方法较为常规通用，封禁用户和 xzggzh1 的方法基于对题目条件挖掘出的特殊结论，相对巧妙。

### 所选的题解
- **作者：water_tomato（5星）**
    - **关键亮点**：思路清晰，利用拓扑排序结合正反图构建，逻辑严谨，通用性强。先通过建反图拓扑排序得到可能的方案，再通过正图遍历标记实际送礼物目标并与原要求对比，全面且完整地解决问题。
    - **重点代码 - 核心实现思想**：通过 `add` 函数分别构建反图和正图；`topo` 函数进行拓扑排序；`dfs` 函数通过正图遍历标记实际送礼物目标；最后在 `main` 函数中进行条件判断和结果输出。
```cpp
// 建图函数
inline void add(int x,int y){//反图为 next，正图为 pre。 
    e[++cnt].to=y;
    e[cnt].next=head[x];
    e[cnt].from=x;
    e[cnt].pre=prehead[y];
    head[x]=cnt;
    prehead[y]=cnt;
}
// 拓扑排序函数
inline void topo(){//找拓扑序 
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(!ru[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        tp[++tot]=u;
        q.pop();
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].to;
            ru[v]--;
            if(!ru[v]) q.push(v);
        }
    }
}
// 标记实际送礼物目标函数
void dfs(int u, int f) {
    if (fa[u]) {
        return;
    }
    fa[u] =f;
    for (int i=prehead[u];i;i=e[i].pre) {
        int v=e[i].from;
        dfs(v,f);
    }
}
// main函数
int main() {
    scanf("%d%d",&n,&m);
    for (int i=1,x,y;i<=m;i++) {
        scanf("%d%d",&x,&y);
        add(y,x);
        ru[x]++;
    }
    for (int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        inans[a[i]]=true;
    }
    topo();
    for (int i=1;i<=n;i++) {
        if (inans[tp[i]]) {
            dfs(tp[i],tp[i]);
            ans[++Cnt]=tp[i];
        }
    }
    for (int i=1;i<=n;i++) {
        if (fa[i]!=a[i]) {
            cout<<-1;
            return 0;
        }
    }
    printf("%d\n",Cnt);
    for (int i=1;i<=Cnt;i++) 
        printf("%d\n",ans[i]);
    return 0;
}
```
- **作者：封禁用户（4星）**
    - **关键亮点**：通过挖掘出的特殊结论 “一个结点和自己的所有祖先拥有同一个喜欢的人” 简化问题，直接对自恋的人入表，代码简洁高效。
    - **重点代码 - 核心实现思想**：`dfs` 函数自底而上遍历，将自恋的人加入队列，同时检查是否满足条件；`main` 函数构建图并调用 `dfs` 函数，最后输出结果。
```cpp
// dfs函数
void dfs(int x, int fa)
{
    for (int v : g[x])
        dfs(v, x);
    if (want[x] == x)
        qwq.push(x);
    else if (want[x]!= want[fa])
        cout << "-1\n", exit(0);
}
// main函数
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        deg[v]++;
    }
    for (int i = 1; i <= n; i++)
        cin >> want[i];
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            dfs(i, 0);
    cout<<qwq.size()<<'\n';
    while (!qwq.empty()) {
        cout << qwq.front() << '\n';
        qwq.pop();
    }
    return 0;
}
```
- **作者：xzggzh1（4星）**
    - **关键亮点**：证明并利用 “对于甲的祖先里和甲不是同一个目标的人乙必有甲的目标不是乙的祖先” 这一条件，从 0 入度点开始遍历构造方案，思路独特。
    - **重点代码 - 核心实现思想**：`dfs` 函数遍历图，将满足条件的点加入答案数组，同时检查是否满足条件；`main` 函数构建图并调用 `dfs` 函数，最后输出结果。
```cpp
// dfs函数
inline void dfs(int pos,int father)
{
    For(pos) dfs(to[k],pos); 
    if(aim[pos]==pos) ans[++top]=pos;
    else if(aim[pos]!=aim[father]){
        puts("-1");exit(0);
    }
}
// main函数
int main()
{
    n=R();m=R();int x,y;
    for(int i=1;i<=m;i++)
    {
        x=R();y=R();
        add(x,y);
    }
    for(int i=1;i<=n;i++) aim[i]=R();
    for(int i=1;i<=n;i++) if(!ind[i]) dfs(i,0);
    printf("%d\n",top);
    for(int i=1;i<=top;i++) printf("%d\n",ans[i]);
}
```

### 最优关键思路或技巧
挖掘题目隐藏条件并转化为图论性质是关键。如封禁用户和 xzggzh1 通过对题目条件深入分析，得出 “一个结点和自己的所有祖先拥有同一个喜欢的人” 以及 “对于甲的祖先里和甲不是同一个目标的人乙必有甲的目标不是乙的祖先” 这样的关键结论，简化问题求解过程。water_tomato 利用拓扑排序结合正反图构建，通用性强，是解决此类拓扑关系问题的常用方法。

### 可拓展思路
此类题目属于图论中基于拓扑关系和条件限制的构造问题。类似套路包括深入挖掘题目条件中的隐藏关系，转化为图的性质，利用拓扑排序、DFS、BFS 等图论算法解决。同类型题可关注涉及家族关系、继承关系等基于拓扑结构且有条件限制的构造类图论题。

### 推荐洛谷题目
- [P1993 小 K 的农场](https://www.luogu.com.cn/problem/P1993)：通过差分约束系统构建图，利用图论算法解决不等式组问题，与本题类似之处在于都需根据题目条件构建图并利用图的性质求解。
- [P3386 【模板】二分图匹配](https://www.luogu.com.cn/problem/P3386)：经典的图论匹配问题，通过匈牙利算法解决二分图匹配，与本题同属图论范畴，可加深对图论算法应用的理解。
- [P2761 软件补丁问题](https://www.luogu.com.cn/problem/P2761)：通过状态压缩建图，利用最短路算法解决问题，与本题类似在于需根据问题特点构建合适的图结构并选择合适算法求解。

### 个人心得
无。 

---
处理用时：106.54秒