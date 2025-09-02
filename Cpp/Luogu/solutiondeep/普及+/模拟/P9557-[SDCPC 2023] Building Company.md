# 题目信息

# [SDCPC 2023] Building Company

## 题目描述

您是一家建筑公司的老板。一开始，公司共有 $g$ 类员工，每一类员工都属于一个工种。第 $i$ 类员工的工种编号为 $t_i$，共有 $u_i$ 人。

市场上共有 $n$ 项工程等待承接。想要承接第 $i$ 项工程，您的公司需要满足 $m_i$ 项要求，其中第 $j$ 项要求您的公司至少有工种编号为 $a_{i, j}$ 的员工 $b_{i, j}$ 人。承接该工程后，您的公司将会更加有名，并吸引 $k_i$ 类员工加入公司，其中第 $j$ 类员工的工种编号为 $c_{i, j}$，共有 $d_{i, j}$ 人。

您可以按任意顺序承接任意数量的工程，每项工程最多只能被承接一次。求最多能承接多少工程。

请注意：员工不是消耗品。承接一项工程后，员工的数量不会减少。

## 样例 #1

### 输入

```
2 2 1 1 2
5
1 3 1
0
2 1 1 2 1
2 3 2 2 1
3 1 5 2 3 3 4
1 2 5
3 2 1 1 1 3 4
1 1 3
0
1 3 2```

### 输出

```
4```

# AI分析结果

### 综合分析与结论
这些题解的核心思路均基于贪心策略，即只要能承接工程就承接，因为承接工程只会增加员工数量，对后续承接工程有益。
- **思路**：均是通过优化对工程承接条件的判断和员工数量变化的处理来提高效率。如CashCollectFactory题解中提到的标签思想，将对某类员工有需求的工程序号和需求数量用标签维护；WhitD题解利用堆和队列维护工程的承接状态；LIUYC_C题解将工程限制条件拆开，类似拓扑排序的方式处理。
- **算法要点**：大多采用数据结构辅助，如unordered_map或map存储员工数量（因员工工种编号值域大），优先队列或set维护工程对员工需求的最小值，队列维护可承接的工程。
- **解决难点**：主要是优化暴力枚举工程的 $O(n^3)$ 时间复杂度。通过对每个工程的需求和奖励分别处理，只关注员工数量变化影响到的工程，从而降低时间复杂度。

综合质量来看，CashCollectFactory的题解思路清晰，代码注释详细，优化思路阐述完整，可评5星；WhitD和LIUYC_C的题解思路表述较清晰，代码实现也正确，但在思路阐述完整性和代码注释方面略逊一筹，可评4星。

### 所选题解
#### CashCollectFactory（5星）
- **关键亮点**：提出标签思想，为每类员工开标签数组，存储对该类员工有需求的工程序号与需求数量，结合unordered_map维护员工数量，栈或队列维护可实施工程，时间复杂度优化到 $O(n)$ 或 $O(n \log n)$（离散化时）。
```cpp
struct tagy{
    int gongcid,wnum;
    bool operator < (const tagy &x) const {
        return (wnum==x.wnum)? gongcid<x.gongcid : wnum<x.wnum;
    }
    tagy(int G,int W){
        gongcid=G,wnum=W;
    }
};
struct rwd{
    int kd,nm;
    rwd(int K,int N){
        kd=K,nm=N;
    }
};
int n,m,tn1,tn2,ans;
int cnt[500005];
unordered_map<int,int> ar; 
stack<int> s;
map<int,set<tagy> > tgm; 
vector<rwd> v[500005];
int main(){
    scanf("%d",&n);
    while(n--){
        scanf("%d%d",&tn1,&tn2);
        ar[tn1]=tn2;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&n);
        int t=0;
        while(n--){
            scanf("%d%d",&tn1,&tn2);
            if(ar[tn1]>=tn2) continue; 
            tgm[tn1].insert(tagy(i,tn2));
            t++;
        }
        if(!t) s.push(i);
        cnt[i]=t;
        scanf("%d",&n);
        while(n--){
            scanf("%d%d",&tn1,&tn2);
            v[i].push_back(rwd(tn1,tn2));
        }
    }
    while(s.size()){
        ans++; n=s.top(); s.pop();
        for(int i=0;i<v[n].size();i++){
            ar[v[n][i].kd]+=v[n][i].nm;
            while(1){
                if(tgm[v[n][i].kd].size()==0) break; 
                set<tagy>::iterator IT;
                IT=tgm[v[n][i].kd].begin();
                if((IT->wnum) > ar[v[n][i].kd]) break;
                cnt[IT->gongcid]--;
                if(cnt[IT->gongcid]==0) s.push(IT->gongcid);
                tgm[v[n][i].kd].erase(IT);
            }
        }
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：通过结构体tagy记录工程序号和需求员工数量，rwd记录奖励员工信息。用unordered_map ar维护员工数量，map tgm维护每个员工类型对应的需求标签，stack s存储可实施工程。读入数据时，初始化员工数量和工程需求、奖励信息，之后不断从栈中取出可实施工程，更新员工数量并检查是否有新工程满足条件入栈，最后输出可实施工程总数。

#### WhitD（4星）
- **关键亮点**：利用堆维护每项工程还有多少条件没有满足，队列维护所有要求都被满足的工程。从队列取出工程代表承接，添加新员工后，查找含有新员工编号相关条件的工程并判断是否可加入队列。
```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define ll long long
#define p_ priority_queue<pi,vector<pi>,greater<pi>>
using namespace std;
const int N=100005;
int g,n,t[N],u[N],m[N],ans;
vector<pi> a[N];
queue<int> q;
map<int,ll> tot;
map<int,p_> um;
void add(int t,int u)
{
    ll &v=tot[t];v+=u;
    p_ &_q=um[t];
    while(!_q.empty())
    {
        pi i=_q.top();
        if(i.first>v)
            break;
        _q.pop();
        if(!(--m[i.second]))
            q.push(i.second);
    }
}
int main()
{
    cin>>g;
    for(int i=1;i<=g;i++)
        cin>>t[i]>>u[i];
    cin>>n;
    for(int i=1,k;i<=n;i++)
    {
        cin>>m[i];
        if(!m[i])
            q.push(i);
        for(int j=1,a,b;j<=m[i];j++)
            cin>>a>>b,um[a].push(pi(b,i));
        cin>>k;
        for(int j=1,c,d;j<=k;j++)
            cin>>c>>d,a[i].push_back(pi(c,d));
    }
    for(int i=1;i<=n;i++)
        add(t[i],u[i]);
    while(!q.empty()&&(++ans))
    {
        int x=q.front();
        q.pop();
        for(auto i:a[x])
            add(i.first,i.second);
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：定义add函数用于更新员工数量并检查相关工程条件是否满足。main函数中，读入初始员工信息和工程信息，将无需求工程入队，处理初始员工数量影响，之后从队列不断取出工程，更新员工数量并检查新工程是否满足条件入队，最终输出承接工程总数。

#### LIUYC_C（4星）
- **关键亮点**：把工程限制条件拆开，用优先队列实现每次取出对某工种人数需求最小的工程，类似拓扑排序，把限制总数为0的工程入队处理。
```cpp
#define int long long
const int N=101010;
typedef pair<int,int> PLL;

unordered_map<int,int> has;
unordered_map<int,priority_queue<PLL,vector<PLL>,greater<PLL> >>hashs;
int n,g;

int idx=0;
int zl[N];
unordered_map<int,int> st;

int xz[N];
vector<PLL> gx[N];

queue<int> q;
int ans=0;

void topu(){
    while(q.size()){
        int p=q.front();
        q.pop();
        ans++;
        
        idx=0;
        for(auto u:gx[p]){
            zl[++idx]=u.first;
            has[u.first]+=u.second;
        }
        
        for(int i=1;i<=idx;i++){
            if(hashs[zl[i]].size()){
                int t=hashs[zl[i]].top().second;
                int sl=hashs[zl[i]].top().first;
                while(sl<=has[zl[i]]&&hashs[zl[i]].size()){
                    xz[t]--;
                    if(xz[t]==0){
                        q.push(t);
                    }
                    hashs[zl[i]].pop();
                    t=hashs[zl[i]].top().second;
                    sl=hashs[zl[i]].top().first;
                }
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);

    cin>>g; 
    for(int i=1;i<=g;i++){
        int x,y;
        cin>>x>>y;
        has[x]+=y;
    }
    
    cin>>n;
    for(int i=1;i<=n;i++){
        int m;
        cin>>m;
        xz[i]=m;

        for(int j=1;j<=m;j++){
            int x,y;
            cin>>x>>y;
            hashs[x].push({y,i});
            if(!st[x]){
                st[x]=true;
                zl[++idx]=x;
            }
        }

        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int x,y;
            if(!st[x]){
                st[x]=true;
                zl[++idx]=x;
            }
            gx[i].push_back({x,y});
        }
    }
    
    for(int i=1;i<=idx;i++){
        if(hashs[zl[i]].size()){
            int t=hashs[zl[i]].top().second;
            int sl=hashs[zl[i]].top().first;
            while(sl<=has[zl[i]]&&hashs[zl[i]].size()){
                xz[t]--;
                hashs[zl[i]].pop();
                t=hashs[zl[i]].top().second;
                sl=hashs[zl[i]].top().first;
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(xz[i]==0){
            q.push(i);
        }
    }

    topu();

    cout<<ans<<endl;

    return 0;
} 
```
核心实现思想：定义topu函数进行类似拓扑排序操作。main函数读入初始员工和工程信息，初始化工程限制总数和对各工种需求的优先队列，处理初始可承接工程入队，在topu函数中不断从队列取出工程，更新员工数量并检查相关工程限制总数是否为0，为0则入队，最后输出承接工程总数。

### 最优关键思路或技巧
- **数据结构选择**：针对员工工种编号值域大的问题，使用unordered_map或map存储员工数量，既解决值域问题，又能高效查找和更新。利用优先队列维护对某工种需求最小的工程，快速判断工程是否满足条件。
- **局部更新思想**：不每次遍历所有工程判断是否可承接，而是仅关注员工数量变化影响到的工程，通过维护工程的待满足需求数，当需求数为0时处理该工程，大大减少不必要的计算。

### 可拓展思路
此类题目属于资源分配与任务承接类型，可拓展到其他资源限制和任务奖励相关场景。类似算法套路是通过合理的数据结构优化对资源和任务条件的维护与判断，利用贪心策略在满足条件时尽可能获取奖励。例如，任务承接条件变为资源消耗且有不同收益，可考虑动态规划结合贪心策略求解。

### 相似知识点洛谷题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心策略结合数据排序，与本题贪心选择可承接工程思路类似。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及到对数据的分析和策略选择，类似本题对工程承接条件分析和贪心选择。
- [P2089 烤鸡](https://www.luogu.com.cn/problem/P2089)：通过枚举和条件判断求解，与本题处理工程需求和承接判断有相似之处。

### 个人心得摘录与总结
CashCollectFactory题解中提到“标签思想是OI界的重要思想之一，本题更是体现的淋漓尽致。观察到保证 $m_i$ 与 $k_i$ 之和均不超过 $10^5$，我们应当以此为着手点进行代码迭代，发力数据规模痛点，对题目需求进行归因分析，从而打出一套组合拳，完成对此题目的降维打击！”，强调了对题目数据规模特点的观察和利用重要思想优化代码的重要性。 

---
处理用时：96.85秒