# 题目信息

# Optimizer

## 题目描述

A process RAM is a sequence of bytes that are indexed from 1 to $ n $ . Polycarpus's program contains such instructions as "memset", that is, the operations of filling memory cells on a segment with some value. The details are: the code only contains $ m $ instructions that look like "set13 a\_i l\_i". Instruction $ i $ fills a continuous memory segment of length $ l_{i} $ , starting from cell number $ a_{i} $ , (that it cells with numbers $ a_{i},a_{i}+1,...,a_{i+li}-1 $ ) with values 13.

In Polycarpus's code, the optimizer's task is to remove the maximum number of instructions from his code in such a way that the remaining instructions set value 13 in all the memory bytes that got this value from the code before the optimization. Also, the value 13 should be set only in the memory bytes that got this value from the code before the optimization. Your task is to implement the optimizer for such program.

## 样例 #1

### 输入

```
10 4
3 3
3 1
4 1
9 2
```

### 输出

```
2
2 3 ```

## 样例 #2

### 输入

```
1 1
1 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Optimizer
## 题目描述
一个进程内存（RAM）是一个字节序列，其索引从1到$n$。Polycarpus的程序包含诸如“memset”这样的指令，即对一段内存单元填充某个值的操作。具体细节如下：该代码仅包含$m$条形如“set13 $a_i$ $l_i$”的指令。指令$i$会将从内存单元编号$a_i$开始，长度为$l_i$的连续内存段（即编号为$a_i, a_i + 1, \ldots, a_{i + l_i - 1}$的单元）填充为值13。

在Polycarpus的代码中，优化器的任务是从他的代码中移除尽可能多的指令，使得剩余指令对内存字节的填充结果与优化前代码对内存字节填充为13的结果相同。同时，值13应仅设置在优化前代码中被设置为13的内存字节中。你的任务是为这样的程序实现优化器。
## 样例 #1
### 输入
```
10 4
3 3
3 1
4 1
9 2
```
### 输出
```
2
2 3 
```
## 样例 #2
### 输入
```
1 1
1 1
```
### 输出
```
0
```
### 算法分类
贪心
### 综合分析与结论
这几道题解均采用贪心算法解决问题，核心思路都是对区间进行处理，通过合理选择区间来保留最少数量且能达成相同结果的指令。它们的主要区别在于实现细节和数据结构的使用上。

题解1使用优先队列来对区间按左端点从小到大、左端点相同则右端点从大到小排序；题解2通过记录每个左端点出发能到达的最远右端点，并按顺序枚举左端点来判断操作是否多余；题解3则是通过记录每个左端点对应的最大右端点，在枚举端点过程中贪心选择右端点尽量大的线段。

### 所选的题解
- **作者：ztxtjz (赞：3)  星级：4星**
  - **关键亮点**：利用优先队列巧妙实现区间排序，代码逻辑清晰，对贪心策略的实现简洁明了。
  - **重点代码**：
```cpp
#include <cstdio>
#include <queue>
int n,m,ans,a[200005],b[200005];
bool vis[2000005],first;
std::priority_queue<int> q[2000005];  //从大到小排序
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&a[i],&b[i]),q[a[i]].push(a[i]+b[i]);  //a[i]为左端点位置，a[i]+b[i]为右端点位置
    for(int i=1;i<=n;i++)
    {
        if(!first)  //第一次操作选取左端点最靠左的一条线段
        {
            for(;q[i].empty();i++);
            first=1;
        }
        int maxr=q[i].top(),k;  //若当前左端点开始有多条线段，q[i].top（）选出右端点最靠右的那条线段
        for(int j=i+1;j<=q[i].top()&&j<=n;j++)  //从左端点向右寻找下一线段的左端点
        {
            if(!q[j].empty())
            {
                if(q[j].top()>maxr)  //若下一线段的右端点＞maxr，更新maxr和序号k
                {
                    k=j;
                    maxr=q[j].top();
                }
            }
        }
        vis[i]=1;  //当前线段左端点已使用过
        ans++;  //使用操作加一
        if(maxr>q[i].top())  //如果循环中更新过，即在当前线段的范围中存在一条不被完全包含的线段
        {
            i=k-1;
        }
        else  //从当前线端右端点寻找下一条线段，因为循环中i<=n+1，没有下一条线段会退出所有循环
        {
            for(i=q[i].top()+1;q[i].empty()&&i<=n+1;i++);
            i--;
        }
    }
    printf("%d\n",m-ans);  //总操作数减去已使用操作数
    for(int i=1;i<=m;i++)
    {
        if(vis[a[i]])  //当前线段的左端点被使用过
        {
            if(a[i]+b[i]!=q[a[i]].top())  //不是那条被使用过的线段
                printf("%d ",i);
            else
                vis[a[i]]=0;  //防止相同操作的存在
        }
        else printf("%d ",i);  //没有使用过
    }
    return 0;
}
```
  - **核心实现思想**：通过优先队列按规则排序区间，每次从左端点开始，选择右端点最大的线段，并在该线段覆盖范围内寻找下一个能更新右端点的线段，从而确定必要操作，最后输出多余操作。
- **作者：ZolaWatle (赞：1)  星级：4星**
  - **关键亮点**：通过预处理每个左端点出发能到达的最远右端点，在枚举左端点时进行贪心判断，逻辑清晰易懂，对边界条件处理细致。
  - **重点代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int N=2e6+1,M=2e5+1;
int n,m,cnt,hav,a[M],b[M],l[M],used[N],siz[N],mx[N];

inline int rint()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}

int main()
{
    n=rint(),m=rint();
    for(int i=1;i<=m;i++)
    {
        a[i]=rint(),l[i]=rint();
        b[i]=a[i]+l[i];
        siz[a[i]]++;  //这个记录的是以a[i]为左端点的操作的个数，如果siz=0，则代表没有操作 
        mx[a[i]]=max(mx[a[i]],a[i]+l[i]);
    }
        
    for(int i=1;i<=n;i++)
    {
        if(!hav) 
        {
            while(!siz[i])
                i++;
            hav=1;
        }//找到第一个有操作的左端点 
        
        used[i]=1;
        cnt++;  //做标记，记录“必要操作”的个数 
        
        int r,k=0,flg=0;
        r=mx[i];  //最远能扩展到的点最初是以i为左端点最远能覆盖到的点 
        for(int j=i+1;j<=mx[i]&&j<=n;j++)  //我们还要防止越界 
            if(siz[j]&&mx[j]>r)  //有操作且能更新右端点 
            {
                k=j;
                r=mx[j];
                flg=1;  //记录已被更新过 
            }
        
        if(flg)  //如果被更新过 
            i=k-1;  //由于存的是右端点右边的第一个点，需要-1得到新的左端点 
        else
        {
            i=mx[i]+1;
            while(!siz[i]&&i<=n+1)  //这里也是跳过没有操作的节点 
                i++;
            i--;  //+1-1的理由同上述 
        }
    }
    
    printf("%d\n",m-cnt);  //多余操作=总操作-必要操作 
    for(int i=1;i<=m;i++)
    {
        if(used[a[i]])
        {
            if(b[i]!=mx[a[i]])
                printf("%d ",i);
            else
                used[a[i]]=0;
        }
        else
            printf("%d ",i);
    }
    
    return 0;
}
```
  - **核心实现思想**：先预处理每个左端点对应的最远右端点 `mx` 数组和以每个点为左端点的操作个数 `siz` 数组。从第一个有操作的左端点开始，标记该点，在其可覆盖范围内寻找能更新最远右端点的点，从而确定必要操作，最后输出多余操作。
- **作者：UperFicial (赞：0)  星级：4星**
  - **关键亮点**：代码简洁，直接在枚举端点过程中贪心选择右端点尽量大的线段，通过差分数组判断点是否被覆盖，实现高效。
  - **重点代码**：
```cpp
int main()
{
    n=read(),m=read();
    rep(i,1,m)
    {
        int l=read(),x=read();
        int r=x+l-1;
        if(mx[l]<r) mx[l]=r,id[l]=i; 
        d[l]++,d[r+1]--;
    }
    rep(i,1,n) d[i]+=d[i-1];
    int maxr=0,R=0,p=0;
    rep(i,1,n)
    {
        if(maxr<mx[i]) maxr=mx[i],p=id[i];
        if(d[i]&&i>R) flag[p]=true,R=maxr;
    }
    rep(i,1,m) if(!flag[i]) G.push_back(i);
    printf("%d\n",(int)G.size());
    for(auto x:G) printf("%d ",x);
    return 0;
}
```
  - **核心实现思想**：首先记录每个左端点对应的最大右端点 `mx` 和对应的操作序号 `id`，通过差分数组 `d` 判断每个点是否被覆盖。在枚举端点过程中，更新最大右端点和对应序号，标记选择的线段，最后输出未标记的线段序号即多余操作。
### 最优关键思路或技巧
这几种解法的关键思路都是基于贪心策略，按照区间左端点排序（左端点相同则按右端点排序），每次选择右端点尽量大的区间，以确保在满足覆盖要求的前提下保留最少的区间（操作）。在实现上，有的利用优先队列方便排序和选取，有的通过预处理数组来快速判断和更新，有的借助差分数组判断点是否被覆盖，这些数据结构和技巧的运用优化了算法实现。
### 同类型题或类似算法套路
此类题目属于区间贪心问题，常见套路是对区间按某种规则排序（如左端点、右端点等），然后基于贪心思想选择满足条件的区间。类似题目通常围绕区间的覆盖、合并、选取等操作展开，需要根据具体问题确定贪心策略。
### 洛谷题目推荐
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：同样是区间覆盖问题，需要选择尽量多的不相交区间。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：通过贪心策略安排生产顺序，以达到最短时间，与本题贪心选择区间操作类似。
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据排序后贪心求解，和本题对区间排序后贪心选择有相似的思维方式。 

---
处理用时：104.59秒