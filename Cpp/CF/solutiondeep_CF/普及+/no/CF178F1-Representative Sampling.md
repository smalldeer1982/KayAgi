# 题目信息

# Representative Sampling

## 题目描述

The Smart Beaver from ABBYY has a long history of cooperating with the "Institute of Cytology and Genetics". Recently, the Institute staff challenged the Beaver with a new problem. The problem is as follows.

There is a collection of $ n $ proteins (not necessarily distinct). Each protein is a string consisting of lowercase Latin letters. The problem that the scientists offered to the Beaver is to select a subcollection of size $ k $ from the initial collection of proteins so that the representativity of the selected subset of proteins is maximum possible.

The Smart Beaver from ABBYY did some research and came to the conclusion that the representativity of a collection of proteins can be evaluated by a single number, which is simply calculated. Let's suppose we have a collection $ {a_{1},...,a_{k}} $ consisting of $ k $ strings describing proteins. The representativity of this collection is the following value:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178F1/c7b3873e6751582bb5e2ad2c1deb58138ab9c543.png)where $ f(x,y) $ is the length of the longest common prefix of strings $ x $ and $ y $ ; for example, $ f( $ "abc", "abd" $ )=2 $ , and $ f( $ "ab", "bcd" $ )=0 $ .

Thus, the representativity of collection of proteins $ { $ "abc", "abd", "abe" $ } $ equals $ 6 $ , and the representativity of collection $ { $ "aaa", "ba", "ba" $ } $ equals $ 2 $ .

Having discovered that, the Smart Beaver from ABBYY asked the Cup contestants to write a program that selects, from the given collection of proteins, a subcollection of size $ k $ which has the largest possible value of representativity. Help him to solve this problem!

## 样例 #1

### 输入

```
3 2
aba
bzd
abq
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
eee
rrr
ttt
qqq
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 3
aaa
abba
abbc
abbd
```

### 输出

```
9
```

# AI分析结果

### 题目内容
# 代表性采样

## 题目描述
来自 ABBYY 的聪明海狸与“细胞学与遗传学研究所”有着长期的合作历史。最近，该研究所的工作人员给海狸出了一个新问题。问题如下。

有一个包含 $n$ 个蛋白质（不一定不同）的集合。每个蛋白质是一个由小写拉丁字母组成的字符串。科学家们给海狸的问题是从初始蛋白质集合中选择一个大小为 $k$ 的子集合，使得所选蛋白质子集的代表性尽可能大。

来自 ABBYY 的聪明海狸做了一些研究，并得出结论，蛋白质集合的代表性可以通过一个简单计算的单一数字来评估。假设我们有一个由描述蛋白质的 $k$ 个字符串组成的集合 $\{a_{1},...,a_{k}\}$ 。这个集合的代表性是以下值：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178F1/c7b3873e6751582bb5e2ad2c1deb58138ab9c543.png)其中 $f(x,y)$ 是字符串 $x$ 和 $y$ 的最长公共前缀的长度；例如，$f($ “abc”, “abd” $)=2$ ，$f($ “ab”, “bcd” $)=0$ 。

因此，蛋白质集合 $\{ $ “abc”, “abd”, “abe” $ \}$ 的代表性等于 $6$ ，集合 $\{ $ “aaa”, “ba”, “ba” $ \}$ 的代表性等于 $2$ 。

发现这一点后，来自 ABBYY 的聪明海狸要求 Cup 参赛者编写一个程序，从给定的蛋白质集合中选择一个大小为 $k$ 的子集合，该子集合具有最大可能的代表性值。帮助他解决这个问题！

## 样例 #1
### 输入
```
3 2
aba
bzd
abq
```
### 输出
```
2
```

## 样例 #2
### 输入
```
4 3
eee
rrr
ttt
qqq
```
### 输出
```
0
```

## 样例 #3
### 输入
```
4 3
aaa
abba
abbc
abbd
```
### 输出
```
9
```

### 算法分类
动态规划

### 综合分析与结论
这几道题解主要围绕如何高效计算从给定蛋白质集合中选取 $k$ 个蛋白质的最大代表性值。题解一采用暴力枚举子集的方式，虽然简单直接但时间复杂度较高；题解二、三、四均利用字典树（Trie）结构，结合树上背包的思想来优化计算。其中，题解二使用重剖优化空间，题解三利用虚树思想减少实际计算节点，题解四则是在字典树上直接进行背包计算。

### 所选的题解
- **题解二（lfxxx）**：
  - **星级**：4星
  - **关键亮点**：设计状态 $dp_{u,i}$ 表示以点 $u$ 为根的子树中选了 $i$ 个字符串的贡献，通过重剖优化空间，将空间复杂度从 $O(n^2 |S_i|)$ 优化到 $O(n \log n + n \log |S_i|)$，时间复杂度为 $O(n |S_i| + n^2)$。
  - **核心代码片段**：
```cpp
void dfs(int u){
    int hson=0;
    for(int i=0;i<26;i++) if(sz[son[u][i]]>sz[hson]) hson=son[u][i];
    if(hson!=0){
        dep[hson]=dep[u]+1;
        dfs(hson);
        pos[u]=pos[hson];
        node[pos[u]]=u;
    }
    for(int i=0;i<26;i++){
        if(son[u][i]==hson) continue;
        if(son[u][i]==0) continue;
        dep[son[u][i]]=dep[u]+1;
        int lst=C;
        dfs(son[u][i]);
        for(int j=sz[u]-sz[son[u][i]];j>=0;j--)
            for(int k=sz[son[u][i]];k>=0;k--) dp[pos[u]][j+k]=max(dp[pos[u]][j+k],dp[pos[u]][j]+dp[pos[son[u][i]]][k]+1ll*j*k*dep[u]);
        for(int j=lst+1;j<=C;j++){
            for(int k=1;k<=sz[node[j]];k++) dp[j][k]=-inf;
            dp[j][0]=0;
        }
        C=lst;
    }
    if(pos[u]==0&&cnt[u]>0) pos[u]=++C,node[C]=u;
    for(int i=sz[u]-cnt[u];i>=0;i--){
        for(int j=cnt[u];j>=0;j--) dp[pos[u]][i+j]=max(dp[pos[u]][i+j],dp[pos[u]][i]+1ll*j*(j-1)/2*dep[u]+1ll*i*j*dep[u]);
    }
}
```
  - **核心实现思想**：先找出重儿子进行 dp 并合并结果，再对轻儿子进行 dp 并回收空间，最后处理单词节点，通过这种方式优化空间。

- **题解三（wosile）**：
  - **星级**：4星
  - **关键亮点**：利用虚树思想，在 Trie 树上进行背包。对于只有一个孩子的节点简单处理答案，使得实际需要计算的节点为 $O(n)$ 个，时间复杂度优化到 $O(kn)$。
  - **核心代码片段**：
```cpp
for(int i=tot;i>=0;i--){
    int cnt=0,son=0;
    for(int j=0;j<26;j++)if(tr[i][j]){
        ++cnt,++tag[id[tr[i][j]]];
        son=tr[i][j];
    }
    if(cnt==0)id[i]=++qwq;
    else if(cnt==1)id[i]=id[son];
    else{
        id[i]=++qwq;
        for(int j=0;j<26;j++)if(tr[i][j]){
            int v=id[tr[i][j]];
            upd(v);
            for(int k=sz[qwq];k>=0;k--)for(int l=0;l<=sz[v];l++)f[qwq][k+l]=max(f[qwq][k+l],f[qwq][k]+f[v][l]);
            sz[qwq]+=sz[v];
        }
    }
    if(buc[i]>0){
        upd(id[i]);
        for(int j=sz[id[i]];j<sz[id[i]]+buc[i];j++)f[id[i]][j+1]=max(f[id[i]][j+1],f[id[i]][j]);
        sz[id[i]]+=buc[i];
    }
}
```
  - **核心实现思想**：根据节点孩子数量不同进行不同处理，通过 `tag` 记录虚点到当前位置深度更新 dp 值，合并不同子树的 dp 结果。

- **题解四（xiaohaoaibiancheng66）**：
  - **星级**：4星
  - **关键亮点**：在字典树上计算每个节点的 $f$ 值，将“经过节点的字符串个数”当作“重量”，$f$ 值当作“权值”进行背包，还特判了所有字符串均相等的情况。
  - **核心代码片段**：
```cpp
void jisuan(int n)
{
    if(n==-1)return;
    for(int i=0;i<26;i++)jisuan(zds[n].child[i]);
    zds[n].f=0;
    for(int i=0;i<26;i++)
    {
        int child=zds[n].child[i];
        if(child==-1)continue;
        zds[n].f+=zds[child].f;
    }
    if(n)zds[n].f+=zds[n].size*(zds[n].size-1)/2;
}
 
void dp(int n)
{
    if(n==-1)return;
    for(int i=0;i<26;i++)dp(zds[n].child[i]);
    for(int i=0;i<2023;i++)zds[n].dp[i]=-oo;
    zds[n].dp[0]=0;
    for(int i=0;i<26;i++)
    {
        int child=zds[n].child[i];
        if(child==-1)continue;
        for(int j=zds[n].size;j>0;j--)
            for(int i=j;i>0;i--)
                if(zds[n].dp[j]<zds[n].dp[j-i]+zds[child].dp[i])
                {
                    zds[n].dp[j]=max(zds[n].dp[j],zds[n].dp[j-i]+zds[child].dp[i]);
                }
    }
    for(int i=0;i<2023;i++)zds[n].dp[i]+=i*(i-1)/2;
    zds[n].dp[zds[n].size]=max(zds[n].dp[zds[n].size],zds[n].f);
}
```
  - **核心实现思想**：先递归计算每个节点的 $f$ 值，再在字典树上进行背包更新 dp 值。

### 最优关键思路或技巧
利用字典树（Trie）结构来处理字符串前缀问题，并结合树上背包的思想进行动态规划。通过不同方式优化空间或时间复杂度，如重剖优化空间、虚树思想减少计算节点等。

### 可拓展之处
此类题目属于字符串集合选取优化问题，类似套路是遇到前缀相关问题考虑字典树结构，在树上进行动态规划时可根据题目特点优化空间或时间复杂度。例如在处理大规模数据时，考虑如何减少冗余计算和存储空间。

### 洛谷相似题目推荐
- [P3802 小魔女帕琪](https://www.luogu.com.cn/problem/P3802)：同样是在树上进行背包问题，可锻炼树上动态规划能力。
- [P2014 选课](https://www.luogu.com.cn/problem/P2014)：经典的树上背包问题，有助于理解背包在树上的应用。
- [P1273 有线电视网](https://www.luogu.com.cn/problem/P1273)：通过在树上进行背包解决收益最大化问题，与本题思路类似。 

---
处理用时：116.16秒