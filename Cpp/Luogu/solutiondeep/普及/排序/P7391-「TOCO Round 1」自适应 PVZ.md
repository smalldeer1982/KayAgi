# 题目信息

# 「TOCO Round 1」自适应 PVZ

## 题目背景

爆切今天的毒瘤三维计算几何后，$\color{black}\texttt{Q}\color{red}\texttt{wQcOrZ}$ 打开了某个有趣的 exe 文件。

## 题目描述

可怜的 $\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 在草坪上遇到了 $n$ 只僵尸，第 $i$ 只僵尸在 $l_i$ 时刻出现，会在 $r_i$ 时刻走进房子。

$\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 手头有 $m$ 个豌豆射手。若一个豌豆射手在 $l_i$ 至 $r_i$ 时刻（不包括两个端点）持续攻击 $i$ 僵尸则可以杀死 $i$ 僵尸，但在攻击过程中不能攻击另外两只僵尸且攻击的僵尸不能更换。

现在 $\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 想知道在合理的安排下，最少有几只僵尸会进入他的房子。

## 说明/提示

对于 $30\%$ 的数据，$n,m\leq 6$。  
对于 $60\%$ 的数据，$n,m\leq 10^3$。  
对于另外 $20\%$ 的数据，$m\geq n$。  
对于 $100\%$ 的数据，$1\leq n,m\leq 2\times 10^5$，$1\leq l_i<r_i\leq 10^9$。

## 样例 #1

### 输入

```
2 1
1 2
3 4```

### 输出

```
0```

## 样例 #2

### 输入

```
3 2
1 3
1 3
2 4```

### 输出

```
1```

## 样例 #3

### 输入

```
2 1
1 3
3 5```

### 输出

```
0```

# AI分析结果

### 综合分析与结论
本题核心是在给定僵尸出现和消失时间以及豌豆射手数量的情况下，通过合理安排攻击，使进入房子的僵尸数量最少。各题解主要采用贪心算法，结合不同数据结构（如 multiset、平衡树等）实现。

### 所选题解
- **作者：吴思诚（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 multiset 高效解决问题，复杂度低。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,ans;
multiset<int>s;
struct zombie{
    int l,r;
}z[200001];
bool cmp(zombie x,zombie y){
    return x.r<y.r;
}
int main(){
    multiset<int>::iterator it;
    scanf("%d%d",&n,&m);
    if(m>=n){
        printf("0");
        return 0;
    }
    for(i=1;i<=n;i++)
        scanf("%d%d",&z[i].l,&z[i].r);
    sort(z+1,z+1+n,cmp);
    for(i=1;i<=n;i++){
        it=s.upper_bound(z[i].l);
        if(it!=s.begin()){
            it--;
            s.erase(it);
            s.insert(z[i].r);
        }
        else{
            if(s.size()+1>m)
                ans++;
            else
                s.insert(z[i].r);	
        }
    }
    printf("%d",ans);
    return 0;
}
```
    - **核心思想**：按僵尸右端点排序，用 multiset 维护豌豆射手上次攻击时间，对每个僵尸找合适射手，若无则判断能否新增射手，否则僵尸进入房子。

- **作者：_zhx（4星）**
    - **关键亮点**：思路明确，代码简洁易懂，同样使用 multiset 实现贪心策略。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s=0;
multiset<int>ms;
struct PVZ{int l,r;}a[200001];
bool cmp(PVZ x,PVZ y){return x.r<y.r;}
int main()
{
    scanf("%d%d",&n,&m);
    if(m>=n) cout<<"0",exit(0);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].l,&a[i].r);
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        auto it=ms.upper_bound(a[i].l);
        if(it!=ms.begin()) ms.erase(--it),ms.insert(a[i].r);
        else if(ms.size()<m) ms.insert(a[i].r);
        else s++;	
    }
    cout<<s;
    return 0;
}
```
    - **核心思想**：将僵尸按右端点排序，用 multiset 维护豌豆射手状态，遍历僵尸找可攻击的射手，若没有且射手数满则僵尸进入房子。

- **作者：liaoxingrui（4星）**
    - **关键亮点**：思路清晰，使用 multiset 结合二分查找，代码实现简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,ans;
multiset<int> q;
struct node{
    int l,r;
}a[N];
inline bool cmp(node x,node y){
    return x.r<y.r;
} 
int main(){
    multiset<int>::iterator it;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i].l>>a[i].r;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        it=q.upper_bound(a[i].l);
        if(it!=q.begin()){
            it--;
            q.erase(it);
            q.insert(a[i].r);
        }
        else if(q.size()==m)
            ans++;
        else
            q.insert(a[i].r);
    } 
    cout<<ans;
    return 0;
}
```
    - **核心思想**：按僵尸右端点排序，用 multiset 存储豌豆射手攻击结束时间，对每个僵尸二分查找合适射手，若没有且射手用完则僵尸进入房子。

### 最优关键思路与技巧
- **贪心策略**：按僵尸右端点从小到大排序，优先攻击右端点小的僵尸，使后续僵尸有更多攻击机会。
- **数据结构**：使用 multiset 维护豌豆射手上次攻击时间，可快速查找合适射手，时间复杂度低。

### 拓展思路
同类型题可拓展为多条件约束的任务分配问题，如每个任务有不同难度、收益等，算法套路仍可采用贪心结合合适数据结构。

### 推荐题目
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
2. [P2255 [USACO14JAN] Recording the Moolympics S](https://www.luogu.com.cn/problem/P2255)
3. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)

### 个人心得摘录与总结
- **作者：xkcdjerry**：本题提交通过率低，使用替罪羊树需调平衡因子才能通过，提醒在使用复杂数据结构时要注意参数调整。
- **作者：Lian_zy**：将本题与类似的 USACO 题联系，指出暴力搜索复杂度高，需用 set 或平衡树优化，强调数据结构对优化算法复杂度的重要性。 

---
处理用时：41.14秒