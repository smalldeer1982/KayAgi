# 题目信息

# [USACO10OCT] Soda Machine G

## 题目描述

To meet the ever-growing demands of his N (1 &amp;lt;= N &amp;lt;= 50,000) cows, Farmer John has bought them a new soda machine. He wants to figure out the perfect place to install the machine.

The field in which the cows graze can be represented as a one-dimensional number line. Cow i grazes in the range A\_i..B\_i (1 &amp;lt;= A\_i &amp;lt;= B\_i; A\_i &amp;lt;= B\_i &amp;lt;= 1,000,000,000) (a range that includes its endpoints), and FJ can place the soda machine at any integer point in the range 1..1,000,000,000.  Since cows are extremely lazy and try to move as little as possible, each cow would like to have the soda machine installed within her grazing range.

Sadly, it is not always possible to satisfy every cow's desires. Thus FJ would like to know the largest number of cows that can be satisfied.

To demonstrate the issue, consider four cows with grazing ranges 3..5, 4..8, 1..2, and 5..10; below is a schematic of their grazing ranges:

```cpp

         1   2   3   4   5   6   7   8   9  10  11  12  13
         |---|---|---|---|---|---|---|---|---|---|---|---|-...
                 aaaaaaaaa
                     bbbbbbbbbbbbbbbbb
         ccccc           ddddddddddddddddddddd
```
As can be seen, the first, second and fourth cows share the point 5, but the third cow's grazing range is disjoint.  Thus, a maximum of 3 cows can have the soda machine within their grazing range.


有N个人要去膜拜JZ，他们不知道JZ会出现在哪里，因此每个人有一个活动范围，只要JZ出现在这个范围内就能被膜拜，

伟大的JZ当然希望膜拜他的人越多越好，但是JZ不能分身，因此只能选择一个位置出现，他最多可以被多少人膜拜呢，

这个简单的问题JZ当然交给你了


## 说明/提示

If the soda machine is placed at location 5, cows 1, 2, and 4 can be satisfied. It is impossible to satisfy all four cows.


## 样例 #1

### 输入

```
4 
3 5 
4 8 
1 2 
5 10 
```

### 输出

```
3 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何找出一个点，使其被最多的区间覆盖这一问题展开。由于区间端点范围大（$10^9$），而区间数量相对较小（$5\times10^4$），离散化成为解决内存和时间复杂度问题的关键手段。差分思想则用于将区间修改转化为单点修改，降低时间复杂度。部分题解还运用了线段树、树状数组等数据结构来辅助求解。

### 所选题解
- **作者：Starria的脑残粉（5星）**
    - **关键亮点**：思路简洁，直接使用差分思想，代码实现简单高效，无需离散化处理复杂逻辑。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,ans;
struct lsg{int x,y;}a[2000000];
bool pd(lsg x,lsg y){return x.x<y.x||x.x==y.x&&x.y>y.y;}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;for (int i=1;i<=n;i++)cin>>a[i].x>>a[i+n].x,a[i].y=1,a[i+n].y=-1;
    sort(a+1,a+1+n*2,pd);
    for (int i=1;i<=n*2;i++)sum+=a[i].y,ans=max(ans,sum);
    cout<<ans<<endl;
}
```
    - **核心思想**：将每个区间的左右端点分别存储，左端点标记为 1，右端点标记为 -1，排序后遍历，累加标记值并记录最大值。

- **作者：fls233666（5星）**
    - **关键亮点**：思路清晰，详细阐述了离散化和差分的步骤及原因，代码注释丰富，可读性强。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#define ll long long
#define rgt register int
#define qmx(a,b) a<b?b:a
using namespace std;

const int mxn = 5e4+4;

int b[mxn<<1],l[mxn],r[mxn],c[mxn<<1];
int n,ans,lb;

inline int q(int x){   
    return lower_bound(b+1,b+1+lb,x)-b;
}

int main(){
    scanf("%d",&n);
    for(rgt i=1;i<=n;i++){
        scanf("%d%d",&l[i],&r[i]);
        lb++;
        b[lb]=l[i];
        lb++;
        b[lb]=r[i];
    }
    sort(b+1,b+lb+1);
    lb=unique(b+1,b+lb+1)-(b+1);
    for(rgt i=1;i<=n;i++){
        c[q(l[i])]++;
        c[q(r[i])+1]--;
    }
    for(rgt i=1;i<=lb;i++){
        c[i]+=c[i-1];
        ans=qmx(c[i],ans);
    }
    printf("%d",ans);
    return 0;
}
```
    - **核心思想**：先将所有区间端点存入数组，排序去重实现离散化，再对离散化后的区间进行差分操作，最后求前缀和得到每个点被覆盖的次数，取最大值。

- **作者：Celebrate（4星）**
    - **关键亮点**：提供了暴力解法和优化解法，展示了优化思路的演变过程，对理解差分和前缀和的应用有帮助。
    - **核心代码（优化后）**：
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read(){
    int x=0,f=0;char s=getchar();
    while(!isdigit(s))f|=s=='-',s=getchar();
    while( isdigit(s))x=(x<<1)+(x<<3)+s-48,s=getchar();
    return f==0?x:-x;
}
const int N=5e4+10;
struct LSnode{
    int x,z,p;
    inline bool operator<(const LSnode &k)const{
        return x<k.x;
    }
}b[N<<1];int a[N<<1];
int n;
int sum[N<<1];
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        b[2*i-1].x=read();
        b[2*i  ].x=read();
        b[2*i-1].p=2*i-1;
        b[2*i  ].p=2*i;
    }
    sort(b+1,b+2*n+1);
    b[1].z=1;
    for(int i=2;i<=(n<<1);i++){
        if(b[i].x==b[i-1].x)b[i].z=b[i-1].z;
        else b[i].z=b[i-1].z+1;
    }
    for(int i=1;i<=(n<<1);i++)a[b[i].p]=b[i].z;
    int maxx=0;
    for(int i=1;i<=n;i++){
        sum[a[2*i-1]]++;
        sum[a[2*i]+1]--;
    }
    int s=0;
    for(int i=1;i<=b[n<<1].z;i++)s+=sum[i],maxx=max(maxx,s);
    printf("%d\n",maxx);
    return 0;
}
```
    - **核心思想**：先对区间端点进行离散化，将每个区间的起始点和结束点 +1 位置分别标记为 1 和 -1，最后通过前缀和还原数组并找出最大值。

### 最优关键思路或技巧
- **离散化**：将大范围内的区间端点映射到较小的范围内，解决内存和时间复杂度问题。
- **差分思想**：将区间修改转化为单点修改，把 $O(n)$ 的区间修改操作降为 $O(1)$ 的单点修改和一次 $O(n)$ 的前缀和操作。

### 可拓展之处
同类型题如区间覆盖问题、区间修改单点查询问题等，都可以考虑使用离散化和差分思想。类似算法套路包括扫描线算法，可用于处理二维平面上的区间覆盖问题。

### 推荐洛谷题目
- P1083 借教室：涉及区间修改和单点查询，可使用差分解决。
- P3372 【模板】线段树 1：经典的区间修改和区间查询问题，可练习线段树的使用。
- P2357 守墓人：同样是区间修改和单点查询，可巩固差分和前缀和的应用。

### 个人心得摘录与总结
- **作者：Watermatter**：提到考试时未离散化导致只有 40 分，强调了离散化在处理大数据范围时的重要性。
- **作者：jgvccc**：指出右端点需向右移动一位，否则会出问题，提醒在处理区间边界时要谨慎。
- **作者：Celebrate**：分享了从暴力解法到优化解法的思路演变，体现了在解题过程中不断思考优化的重要性。 

---
处理用时：47.94秒