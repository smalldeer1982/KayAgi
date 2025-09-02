# 题目信息

# [USACO17FEB] Why Did the Cow Cross the Road I S

## 题目描述

Farmer John 的奶牛们正在学习如何有效地过马路。回想起古老的“鸡为什么要过马路？”笑话，他们认为鸡一定是过马路的专家，于是去寻找鸡来帮助它们。

事实上，鸡是非常忙碌的生物，它们只有有限的时间来帮助奶牛。农场上有 $C$ 只鸡（$1 \leq C \leq 20,000$），方便地用编号 $1 \ldots C$ 标识，每只鸡 $i$ 只愿意在确切的时间 $T_i$ 帮助一头奶牛。奶牛们从不着急，它们的日程安排更加灵活。农场上有 $N$ 头奶牛（$1 \leq N \leq 20,000$），方便地用编号 $1 \ldots N$ 标识，其中奶牛 $j$ 能够在时间 $A_j$ 到时间 $B_j$ 之间过马路。考虑到“伙伴系统”是最好的方式，每头奶牛 $j$ 理想情况下希望找到一只鸡 $i$ 来帮助她过马路；为了使它们的日程安排兼容，$i$ 和 $j$ 必须满足 $A_j \leq T_i \leq B_j$。

如果每头奶牛最多只能与一只鸡配对，每只鸡也最多只能与一头奶牛配对，请计算可以构建的最大奶牛-鸡配对数。

## 样例 #1

### 输入

```
5 4
7
8
6
2
9
2 5
4 9
0 3
8 13```

### 输出

```
3```

# AI分析结果

• 综合分析与结论：
    - 思路：多数题解采用贪心策略，将鸡（点）和牛过马路时间区间进行排序后匹配。排序方式有按区间右端点升序（多数题解）、按区间左端点升序等。
    - 算法要点：通过排序后，遍历区间找匹配点，有朴素枚举、利用数据结构优化查找匹配点等方式。
    - 解决难点：朴素做法时间复杂度高，优化难点在于如何在匹配过程中高效查找可匹配点并避免重复匹配，同时要保证贪心策略的正确性。部分题解通过二分查找、使用multiset、堆等数据结构优化，也有通过并查集等方式优化标记删除操作。
    - 总体来看，各题解在思路清晰度、代码可读性和优化程度上各有差异。

所选的题解：
  - **作者：Cutest_Junior（5星）**
    - **关键亮点**：思路清晰，先阐述朴素贪心思路及证明，后提出$O(N\log N)$优化做法。代码注释详细，展示了优化过程。
    - **个人心得**：分享了朴素做法的优化历程，遇到数组删点复杂度高、二分可能退化等问题，最终使用multiset解决。
    - **核心代码（$O(N\log N)$做法）**：
```cpp
#include <cstring>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;
#define ll long long
#define ri register int

//...读入优化代码省略...

const int N = 20010;
multiset <int> s;

struct inter {
    int l,r;
    friend inline bool operator < (const inter & a,const inter &b) {
        return a.r == b.r? a.l > b.l : a.r < b.r;
    }
}a[N];

int n,m,x[N],ans;
multiset<int>::iterator it;

signed main() {
    n = read(),m = read();
    for (int i = 1;i <= n;++i) x[i] = read(),s.insert(x[i]);
    for (int i = 1;i <= m;++i) a[i].l = read(),a[i].r = read();
    sort(a+1,a+1+m);
    for (int i = 1;i <= m;++i) {
        it = s.lower_bound(a[i].l);
        if (it!= s.end()) {
            if (*it <= a[i].r) ++ans,s.erase(it);
        }
    }
    printf("%d\n",ans);
	return 0;
}
```
    - **核心实现思想**：将区间按右端点排序，用multiset存储鸡的时间点。遍历区间，对每个区间用lower_bound查找第一个大于等于左端点的点，若该点在区间内则匹配并从multiset中删除。
  - **作者：StudyingFather（4星）**
    - **关键亮点**：提出朴素贪心思路后，给出基于堆优化的$O(n \log n)$做法，代码简洁明了。
    - **核心代码**：
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct seg
{
 int l,r;
 bool operator<(const seg&a)const
 {
  return r>a.r;
 }
}s[20005];
int a[20005],vis[20005];
priority_queue<seg> q;
bool cmp(const seg&a,const seg&b)
{
 return a.l<b.l;
}
int main()
{
 int c,n;
 scanf("%d%d",&c,&n);
 for(int i=1;i<=c;i++)
  scanf("%d",&a[i]);
 sort(a+1,a+c+1);
 for(int i=1;i<=n;i++)
  scanf("%d%d",&s[i].l,&s[i].r);
 sort(s+1,s+n+1,cmp);
 int cur=1,ans=0;
 for(int i=1;i<=c;i++)
 {
  while(cur<=n&&s[cur].l<=a[i])
   q.push(s[cur++]);
  while(!q.empty()&&q.top().r<a[i])
   q.pop();
  if(!q.empty())ans++,q.pop();
 }
 printf("%d\n",ans);
 return 0;
}
```
    - **核心实现思想**：将区间按左端点排序，鸡时间点排序。遍历鸡时间点，把左端点小于当前鸡时间点的区间入堆，弹出右端点小于当前鸡时间点的区间，堆顶区间与当前鸡匹配。
  - **作者：MyukiyoMekya（4星）**
    - **关键亮点**：提出用并查集优化二分查找的方式维护鸡的匹配，在保证$O(n\log n)$复杂度同时降低常数。
    - **核心代码**：
```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define ln puts("")
using namespace std;
const int MaxN=20050;
struct Node
{
 int l,r;
 inline bool operator < (const Node &nt) const
 {
  return r<nt.r;
 }
}a[MaxN];
//...读入优化代码省略...
int f[MaxN],b[MaxN],cnt[MaxN];
inline int getf(int x)
{
 return f[x]==x?x:f[x]=getf(f[x]);
}
signed main(void)
{
 int n,m;read(n,m);
 for(int i=1;i<=n;++i)
  read(b[i]);
 sort(b+1,b+n+1);
 cnt[1]=1;
 {
  reg int top=1;
  for(int i=2;i<=n;++i)
   if(b[i]!=b[i-1])
    b[++top]=b[i],cnt[top]=1;
   else
    ++cnt[top];
  n=top;
 }
 for(int i=1;i<=n+1;++i)
  f[i]=i;
 b[n+1]=1e9;
 for(int i=1;i<=m;++i)
  read(a[i].l,a[i].r);
 sort(a+1,a+m+1);
 reg int Ans=0;
 for(int i=1;i<=m;++i)
 {
  reg int l=1,r=n,ans=n+1,mid;
  while(l<=r)
  {
   mid=(l+r)>>1;
   if(b[mid]>=a[i].l)
    ans=mid,r=mid-1;
   else
    l=mid+1;
  }
  if(b[getf(ans)]<=a[i].r)
  {
   ++Ans,--cnt[getf(ans)];
   if(!cnt[getf(ans)])
    f[getf(ans)]=getf(ans)+1;
  }
 }
 write(Ans),ln;
 return 0;
}
```
    - **核心实现思想**：将区间按右端点排序，鸡时间点排序并去重。二分查找满足区间左端点的鸡时间点，通过并查集判断该点是否已匹配，若匹配则跳转到下一个未匹配点，匹配成功后更新并查集。

最优关键思路或技巧：利用数据结构优化匹配过程，如使用multiset可在$O(\log N)$时间内完成查找和删除操作；使用堆可以动态维护可匹配区间，快速找到右端点最小的区间；利用并查集优化二分查找中的标记删除操作，降低常数复杂度。

可拓展之处：此类题目属于区间匹配问题，类似套路是对区间和点进行合理排序，利用数据结构优化查找和匹配过程。相似题目如区间选点问题，给定多个区间，在数轴上选取最少的点使得每个区间内至少有一个点，思路也是通过排序和贪心策略解决。

推荐洛谷题目：
1. P1803 凌乱的yyy / 线段覆盖：经典区间覆盖问题，与本题类似，需对区间排序后贪心求解。
2. P1248 加工生产调度：涉及任务调度，可通过排序和贪心策略安排任务顺序。
3. P1080 [NOIP2012 提高组] 国王游戏：通过合理排序和贪心思想解决分配问题。 

---
处理用时：63.69秒