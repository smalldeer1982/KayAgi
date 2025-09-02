# 题目信息

# Swaps in Permutation

## 题目描述

You are given a permutation of the numbers $ 1,2,...,n $ and $ m $ pairs of positions $ (a_{j},b_{j}) $ .

At each step you can choose a pair from the given positions and swap the numbers in that positions. What is the lexicographically maximal permutation one can get?

Let $ p $ and $ q $ be two permutations of the numbers $ 1,2,...,n $ . $ p $ is lexicographically smaller than the $ q $ if a number $ 1<=i<=n $ exists, so $ p_{k}=q_{k} $ for $ 1<=k&lt;i $ and $ p_{i}&lt;q_{i} $ .

## 样例 #1

### 输入

```
9 6
1 2 3 4 5 6 7 8 9
1 4
4 7
2 5
5 8
3 6
6 9
```

### 输出

```
7 8 9 4 5 6 1 2 3
```

# AI分析结果

### 题目内容
# 排列中的交换

## 题目描述
给定数字1, 2,..., n的一个排列，以及m对位置$(a_{j},b_{j})$。
在每一步中，你可以从给定的位置对中选择一对，并交换该位置上的数字。通过这些交换能得到的字典序最大的排列是什么？
设p和q是数字1, 2,..., n的两个排列。如果存在一个数字$1 \leq i \leq n$，使得对于$1 \leq k < i$有$p_{k}=q_{k}$，且$p_{i}<q_{i}$，则称p在字典序上小于q。

## 样例 #1
### 输入
```
9 6
1 2 3 4 5 6 7 8 9
1 4
4 7
2 5
5 8
3 6
6 9
```
### 输出
```
7 8 9 4 5 6 1 2 3
```

### 算法分类
并查集

### 综合分析与结论
这些题解的核心思路都是利用并查集将可相互交换位置的数字划分到同一个集合（连通块）中，然后在每个集合内对数字进行从大到小排序，最后按照原位置顺序输出，从而得到字典序最大的排列。不同点主要在于数据结构的使用和具体实现细节。有的使用优先队列简化排序操作，有的使用vector存储连通块内元素；在代码风格上，有的注重代码简洁，有的注释较为详细。

### 所选的题解
- **作者：Yizhixiaoyun (5星)**
    - **关键亮点**：思路清晰，代码注释详细，使用优先队列简化排序操作，无需手动排序，优化了代码实现。
    - **重点代码**：
```cpp
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-48;
        c=getchar();
    }
    return x*f;
}
const int maxn=1e6+5;
int n,m;
int a[maxn];
int f[maxn];
priority_queue<int> q[maxn];
int find(int x){
    if(x!=f[x]) f[x]=find(f[x]);
    return f[x];
}
void unity(int x,int y){f[find(x)]=find(y);}
inline void init(){
    n=read();m=read();
    for(register int i=1;i<=n;++i) f[i]=i;
    for(register int i=1;i<=n;++i) a[i]=read();
    while(m--){
        int u=read(),v=read();
        unity(u,v);
    }
}
int main(){
    init();
    for(register int i=1;i<=n;++i) q[find(i)].push(a[i]);
    for(register int i=1;i<=n;++i){
        int fi=find(i);
        printf("%d ",q[fi].top());q[fi].pop();
    }
}
```
    - **核心实现思想**：通过`read`函数读取输入，`init`函数初始化并查集和读入数据，在`main`函数中，先将每个元素根据其并查集的根节点放入对应的优先队列，最后按顺序输出优先队列中的元素，即得到字典序最大的排列。
- **作者：wkjwkj (4星)**
    - **关键亮点**：详细介绍了`vector`的基本用法，代码逻辑清晰，注释丰富，对并查集和`vector`的使用讲解细致。
    - **重点代码**：
```cpp
int get(int x)
{
    if(fa[x]==x)return x;
    return fa[x]=get(fa[x]);
}
vector<int> h[1000005];
vector<int> p[1000005];
int ans[1000005];
bool b[1000005];
bool cmp(int x,int y)
{
    return x>y;
}
int main()
{
    memset(b,0,sizeof b); 
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x=get(x),y=get(y);
        fa[x]=y;
    }
    for(int i=1;i<=n;i++)
    {
        int x=get(i);
        h[x].push_back(a[i]);
        p[x].push_back(i);
    }
    for(int i=1;i<=n;i++)
    {
        int x=get(i);
        if(b[x])continue;
        sort(h[x].begin(),h[x].end(),cmp);
        sort(p[x].begin(),p[x].end());
        for(int i=1;i<=h[x].size();i++)ans[p[x][i-1]]=h[x][i-1];
        b[x]=1;
    }
    for(int i=1;i<=n;i++)printf("%d ",ans[i]);
}
```
    - **核心实现思想**：`get`函数实现并查集路径压缩，在`main`函数中，先初始化并查集和读入数据，然后将每个元素根据其并查集的根节点分别存入`h`（存元素）和`p`（存下标），接着对每个集合内的元素和下标分别排序，最后按顺序将元素放回原位置得到结果。
- **作者：世末OIer (4星)**
    - **关键亮点**：代码简洁明了，清晰展示了并查集的基本操作，对于每个祖宗节点，将其儿孙压入`vector`后排序输出。
    - **重点代码**：
```cpp
int a[1000006],n,m,fa[1000006],sz[1000006];
vector<int> v[1000006];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    int i,j,x,y;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;++i) scanf("%d",a+i),fa[i]=i;
    for(i=1;i<=m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        fa[find(x)]=find(y);
    }
    for(i=1;i<=n;++i) v[find(i)].push_back(a[i]);
    for(i=1;i<=n;++i) sort(v[i].begin(),v[i].end()),sz[i]=v[i].size();
    for(i=1;i<=n;++i) printf("%d ",v[find(i)][--sz[find(i)]]);
}
```
    - **核心实现思想**：通过`find`函数查找根节点，在`main`函数中，先初始化并查集和读入数据，然后将每个元素根据其并查集的根节点放入对应的`vector`，对每个`vector`排序后，按顺序输出每个`vector`的最后一个元素，即得到字典序最大的排列。

### 最优关键思路或技巧
使用并查集来划分可相互交换位置的数字集合，利用优先队列（如Yizhixiaoyun的题解）或`vector`结合排序（其他部分题解）对每个集合内的数字进行从大到小排序，从而得到字典序最大的排列。这种方法有效利用了并查集的特性，快速确定可交换元素的集合，简化了问题的处理。

### 拓展思路
此类题目属于并查集结合贪心策略的类型，类似题目通常会给出一些元素间的关系，要求通过这些关系对元素进行某种最优排列或分组。常见的拓展方向包括增加限制条件，如交换次数限制；或者改变元素性质，如元素变为字符串等。

### 洛谷题目推荐
- [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：经典的并查集应用题目，判断给定的两个人是否有亲戚关系。
- [P1197 [JSOI2008] 星球大战](https://www.luogu.com.cn/problem/P1197)：结合图论和并查集，在动态删除节点的情况下，求解连通块的数量。
- [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)：并查集模板题，涵盖了并查集的基本操作，适合巩固基础。

### 个人心得摘录
暂未发现题解中有个人心得相关内容。 

---
处理用时：70.00秒