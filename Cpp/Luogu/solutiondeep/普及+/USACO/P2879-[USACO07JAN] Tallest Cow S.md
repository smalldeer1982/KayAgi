# 题目信息

# [USACO07JAN] Tallest Cow S

## 题目描述

FarmerJohn 有n头牛，它们按顺序排成一列。FarmerJohn 只知道其中最高的奶牛的序号及它的高度，其他奶牛的高度都是未知的。现在 FarmerJohn 手上有 $R$ 条信息，每条信息上有两头奶牛的序号（$a$ 和 $b$），其中 $b$ 奶牛的高度一定大于等于 $a$ 奶牛的高度，且 $a, b$之间的所有奶牛的高度都比 $a$ 小。现在 FarmerJohn 想让你根据这些信息求出每一头奶牛的可能的最大的高度。（数据保证有解）

## 说明/提示

$1 \le n \le 10000$，$1 \le h \le 1000000$，$0 \le R \le 10000$

Translate provided by @酥皮

## 样例 #1

### 输入

```
9 3 5 5
1 3
5 3
4 3
3 7
9 8```

### 输出

```
5
4
5
3
4
4
5
5
5```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何根据给定的奶牛对视信息求出每头奶牛可能的最大高度展开。多数题解采用了差分和前缀和的思想，通过对区间操作的优化，将时间复杂度降低。同时，都注意到了信息重复的问题，采用不同方式进行判重。部分题解还使用了线段树、拓扑排序等复杂数据结构和算法，但整体上差分和前缀和的方法更为简洁高效。

### 所选题解
- **作者：追梦_Chen (赞：25)  ★★★★**
  - **关键亮点**：思路清晰，详细解释了差分和前缀和的运用，使用 `map` 进行判重，避免了二维数组超空间的问题，代码简洁易懂。
  - **个人心得**：详细解释了 `d[i]` 数组的含义，即相邻两头牛之间的高度差，通过对区间端点操作代替对区间操作，节约时间。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>	
#include <utility>
using namespace std;
int d[100005];      			 //牛
int n,l,h,r;
int x,y;
map<pair<int,int>,bool>book;   //由两个Int类型的映射bool数组

int main(){
    scanf("%d%d%d%d",&n,&l,&h,&r);
    for(int i=1;i<=r;i++){
        scanf("%d%d",&x,&y);    
        if(x>y)  swap(x,y);   //当x>y时记得交换
        if(book[make_pair(x,y)])    continue;  //判重
        d[x+1]--;   //前缀和操作
        d[y]++;    
        book[make_pair(x,y)]=true;
    }
    for(int i=1;i<=n;i++){
        d[i]=d[i-1]+d[i];            
        printf("%d\n",h+d[i]);
    }
    return 0;
}
```
- **作者：maple_tzc (赞：4)  ★★★★**
  - **关键亮点**：参考多位大佬博客，思路清晰，同样运用差分和前缀和优化，使用 `map` 判重，代码简洁。
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[10010],d[10010];
map<pair<int ,int>,bool> eee;
int main(){
    int n,p,h,m;
    scanf("%d%d%d%d",&n,&p,&h,&m);
    for (int i=1; i<=m; i++){
        int a,b;
        scanf("%d%d",&a,&b);
        if(a>b) swap(a,b);
        if (eee[make_pair(a,b)]) continue;
        d[a+1]--,d[b]++;
        eee[make_pair(a,b)]=true;
    }
    for (int i=1; i<=n; i++){
        c[i]=c[i-1]+d[i];
        printf("%d\n",h+c[i]);
    }
    cout<<endl;
    return 0;
}
```
- **作者：木木！ (赞：2)  ★★★★**
  - **关键亮点**：对题目条件进行深入分析，证明了 `b >= a` 条件不影响答案，提供了线段树建边 + 拓扑排序和朴素暴力算法两种思路，并给出了差分优化的代码。
```cpp
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;

int loi[10005];

map<int,map<int,bool> > mmp;

int main()
{
    int n,i,h,r;
    scanf("%d%d%d%d",&n,&i,&h,&r);
    for(int i=1; i<=r; ++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(a>b)
        {
            swap(a,b);
        }

        if(!mmp[a][b])
        {
            mmp[a][b] = 1;
            --loi[a+1];
            ++loi[b];
        }
    }

    int cur = 0;
    for(int i=1; i<=n; ++i)
    {
        cur += loi[i];
        printf("%d\n",h+cur);
    }
}
```

### 最优关键思路或技巧
- **差分和前缀和思想**：将对区间的操作转化为对区间端点的操作，通过前缀和快速计算每个点的值，时间复杂度从 $O(N * M)$ 优化到 $O(N + M)$。
- **判重技巧**：使用 `map` 或自定义结构体结合 `set` 进行判重，避免重复操作。

### 可拓展之处
同类型题如区间修改、区间查询问题，可使用差分和前缀和思想优化。类似算法套路包括使用线段树、树状数组等数据结构处理区间问题。

### 推荐题目
- P3372 【模板】线段树 1
- P3368 【模板】树状数组 2
- P1438 无聊的数列

### 个人心得摘录与总结
- **追梦_Chen**：详细解释 `d[i]` 数组含义，强调通过对区间端点操作代替对区间操作可节约时间。
- **木木！**：对题目条件进行深入分析，证明 `b >= a` 条件不影响答案，为解题提供了更清晰的思路。 

---
处理用时：40.65秒