# 题目信息

# Cow and Snacks

## 题目描述

The legendary Farmer John is throwing a huge party, and animals from all over the world are hanging out at his house. His guests are hungry, so he instructs his cow Bessie to bring out the snacks! Moo!

There are $ n $ snacks flavors, numbered with integers $ 1, 2, \ldots, n $ . Bessie has $ n $ snacks, one snack of each flavor. Every guest has exactly two favorite flavors. The procedure for eating snacks will go as follows:

- First, Bessie will line up the guests in some way.
- Then in this order, guests will approach the snacks one by one.
- Each guest in their turn will eat all remaining snacks of their favorite flavor. In case no favorite flavors are present when a guest goes up, they become very sad.

Help Bessie to minimize the number of sad guests by lining the guests in an optimal way.

## 说明/提示

In the first example, Bessie can order the guests like this: $ 3, 1, 2, 4 $ . Guest $ 3 $ goes first and eats snacks $ 1 $ and $ 4 $ . Then the guest $ 1 $ goes and eats the snack $ 2 $ only, because the snack $ 1 $ has already been eaten. Similarly, the guest $ 2 $ goes up and eats the snack $ 3 $ only. All the snacks are gone, so the guest $ 4 $ will be sad.

In the second example, one optimal ordering is $ 2, 1, 3, 5, 4 $ . All the guests will be satisfied.

## 样例 #1

### 输入

```
5 4
1 2
4 3
1 4
3 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 5
2 3
2 1
3 4
6 5
4 5
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写

#### 奶牛和零食

##### 题目描述

传奇农夫约翰正在举办一场盛大的派对，来自世界各地的动物们都在他家聚会。他的客人们饿了，于是他让他的奶牛贝西拿出零食！哞！

有 $n$ 种零食口味，编号为 $1, 2, \ldots, n$。贝西有 $n$ 种零食，每种口味各有一个。每个客人都有两种最喜欢的口味。吃零食的过程如下：

- 首先，贝西将以某种方式排列客人。
- 然后，客人将按此顺序依次接近零食。
- 每个客人在轮到他们时，会吃掉所有剩余的他们最喜欢的口味的零食。如果某个客人在轮到他们时没有他们喜欢的零食，他们会变得非常难过。

帮助贝西通过优化排列客人的顺序，最小化难过的客人的数量。

##### 说明/提示

在第一个例子中，贝西可以这样排列客人：$3, 1, 2, 4$。客人 $3$ 先来，吃掉零食 $1$ 和 $4$。然后客人 $1$ 来，只吃掉零食 $2$，因为零食 $1$ 已经被吃掉了。类似地，客人 $2$ 来，只吃掉零食 $3$。所有零食都被吃完了，所以客人 $4$ 会难过。

在第二个例子中，一个最优的排列是 $2, 1, 3, 5, 4$。所有客人都会满意。

##### 样例 #1

###### 输入

```
5 4
1 2
4 3
1 4
3 4
```

###### 输出

```
1
```

##### 样例 #2

###### 输入

```
6 5
2 3
2 1
3 4
6 5
4 5
```

###### 输出

```
0
```

### 算法分类
并查集

### 题解分析与结论

这道题的核心是通过并查集来统计图中的连通块数量，进而计算难过的客人的数量。每个连通块中的客人数目可以通过连通块的大小减去1来得到，最终难过的客人数目为总客人数减去满足的客人数。

### 评分较高的题解

#### 题解1：SIGSEGV (赞：15)
- **星级**：5星
- **关键亮点**：清晰地解释了如何通过并查集统计连通块数量，并给出了简洁的代码实现。
- **代码核心思想**：使用并查集合并客人喜欢的零食，最后统计连通块数量并计算难过的客人数。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n,kk,f[N],sz[N];
int getf(int v) {if (f[v] != v) f[v] = getf(f[v]);return f[v];}
int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> kk;
    int t1,t2;
    for (int i = 1;i <= n;i++) f[i] = i;
    for (int i = 1;i <= kk;i++)
    {
        cin >> t1 >> t2;
        f[getf(t1)] = getf(t2);
    }
    int cnt = 0;
    for (int i = 1;i <= n;i++) if (f[i] == i) ++cnt;
    cout << kk - (n - cnt);
    return 0;
}
```

#### 题解2：微香玉烛暗 (赞：8)
- **星级**：4星
- **关键亮点**：直接使用并查集判断是否在同一集合中，代码简洁易懂。
- **代码核心思想**：每次将客人喜欢的零食进行合并，如果已经在同一集合中，则难过的客人数加一。
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=100005;
int n,k,x,y,ans,f[N];

int find (int x) {
    return f[x]==x?x:find(f[x]);
}

int main () {
    scanf ("%d%d",&n,&k);
    for(int i=1;i<=n;i++) f[i]=i;
    while(k--){
        scanf ("%d%d",&x,&y);
        int r1=find(x),r2=find(y);
        if (r1!=r2)
            f[r1]=r2;
        else ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```

#### 题解3：翟翟 (赞：5)
- **星级**：4星
- **关键亮点**：详细解释了如何通过连通块的大小计算满足的客人数，并给出了清晰的代码实现。
- **代码核心思想**：使用并查集合并客人喜欢的零食，最后统计连通块数量并计算难过的客人数。
```cpp
#include<cstdio>
const int N=1e5+1; 
int n,k,x,y,f[N],ans;
inline int find(int x){
    return f[x]^x?f[x]=find(f[x]):x;
}
int main(){
    scanf("%d%d",&n,&k);
    for(register int i=1;i<=n;++i)f[i]=i;
    for(register int i=0;i<k;++i){
        scanf("%d%d",&x,&y);
        x=find(x),y=find(y),f[x]=y;
    }
    for(register int i=1;i<=n;++i)
        if(f[i]==i)++ans;
    printf("%d\n",k-n+ans);
    return 0;
}
```

### 最优关键思路或技巧
- **并查集**：通过并查集统计图中的连通块数量，进而计算难过的客人的数量。
- **连通块分析**：每个连通块中的客人数目可以通过连通块的大小减去1来得到。

### 可拓展之处
- **类似问题**：可以扩展到其他需要统计连通块数量的问题，如社交网络中的朋友圈、图中的连通分量等。

### 推荐题目
1. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
2. [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)
3. [P1197 [JSOI2008]星球大战](https://www.luogu.com.cn/problem/P1197)

---
处理用时：46.82秒