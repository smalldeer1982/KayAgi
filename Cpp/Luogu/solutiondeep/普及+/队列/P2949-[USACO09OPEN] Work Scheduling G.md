# 题目信息

# [USACO09OPEN] Work Scheduling G

## 题目描述

Farmer John has so very many jobs to do! In order to run the farm efficiently, he must make money on the jobs he does, each one of which takes just one time unit.

His work day starts at time 0 and has 1,000,000,000 time units (!).  He currently can choose from any of N (1 <= N <= 100,000) jobs

conveniently numbered 1..N for work to do. It is possible but

extremely unlikely that he has time for all N jobs since he can only work on one job during any time unit and the deadlines tend to fall so that he can not perform all the tasks.

Job i has deadline D\_i (1 <= D\_i <= 1,000,000,000). If he finishes job i by then, he makes a profit of P\_i (1 <= P\_i <= 1,000,000,000).

What is the maximum total profit that FJ can earn from a given list of jobs and deadlines?  The answer might not fit into a 32-bit integer.




## 说明/提示

Complete job 3 (1,7) at time 1 and complete job 1 (2,10) at time 2 to maximize the earnings (7 + 10 -> 17).


## 样例 #1

### 输入

```
3 
2 10 
1 5 
1 7 
```

### 输出

```
17 
```

# AI分析结果

### 综合分析与结论
这些题解大多采用贪心算法解决该工作调度问题，核心在于如何在满足截止时间的条件下获取最大利润。多数题解使用优先队列（小根堆或大根堆）来维护已选工作的信息，通过比较和替换来实现反悔贪心，部分题解使用树状数组、并查集等数据结构进行优化。不同题解的主要差异在于排序方式、贪心策略的具体实现以及数据结构的选择。

### 所选题解
- **作者：Taduro (赞：70)  4星**
    - **关键亮点**：思路清晰，直接阐述带反悔贪心的核心思想，代码简洁易懂，使用小根堆维护已选工作的最小利润，便于进行反悔操作。
    - **核心代码**：
```cpp
#include<queue>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
    int tim,mny;
}w[100001];
int n,i;
long long ans;
priority_queue<int,vector<int>,greater<int> > q;
bool cmp(node a,node b){
    return a.tim<b.tim;
}
int main(){
    scanf("%d",&n);
    for (i=1; i<=n; i++)
        scanf("%d%d",&w[i].tim,&w[i].mny);
    sort(w+1,w+n+1,cmp);
    for (i=1; i<=n; i++){
        if (w[i].tim<=q.size()){
            if (w[i].mny>q.top()){
                ans-=q.top();
                q.pop(); q.push(w[i].mny);
                ans+=w[i].mny;
            }
        }
        else{
            q.push(w[i].mny);
            ans+=w[i].mny;
        }
    }
    printf("%lld",ans);
    return 0;
}
```
    - **核心思想**：先按截止时间排序，遍历工作，若当前工作截止时间大于已选工作数量，直接做并将利润加入小根堆；若小于等于，比较当前工作利润与堆顶，若更大则替换堆顶。

- **作者：Ace_Heart (赞：37)  4星**
    - **关键亮点**：详细解释了贪心思路的逐步优化过程，从错误的贪心策略到正确的反悔贪心，逻辑清晰，代码中手动实现小根堆，有助于理解堆的原理。
    - **核心代码**：
```cpp
struct work
{
    ll d;
    ll p;
};
work a[N];
bool cmp(work x,work y)
{
    if(x.d==y.d)
        return x.p>y.p;
    return x.d<y.d;
}
ll day=0;
ll d[N];
void Add(ll x)
{
    day++;
    int son=day;
    int father=son/2;
    while(x<d[father] && father)
    {
        d[son]=d[father];
        son=father;
        father=son/2;
    }
    d[son]=x;
}
ll Del()
{
    ll ret=d[1];
    int father=1;
    int son=father*2;
    if(son+1<day && d[son+1]<d[son])
    {
        son++;
    }
    while(son<day && d[son]<d[day])
    {
        d[father]=d[son];
        father=son;
        son=father*2;
        if(son+1<day && d[son+1]<d[son])
            son++;
    }
    d[father]=d[day];
    day--;
    return ret;
}
int main()
{
    ll n;
    n=read();
    for(ll i=1;i<=n;i++)
    {
        a[i].d=read();
        a[i].p=read();
    }
    sort(a+1,a+1+n,cmp);
    ll money=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i].d>day)
        {
            Add(a[i].p);
            money+=a[i].p;
        }
        else
        {
            if(a[i].p>d[1])
            {
                Add(a[i].p);
                money+=a[i].p-Del();
            }
        }
    }
    cout<<money;
    return 0;
}
```
    - **核心思想**：按截止时间排序，用手动实现的小根堆维护已选工作的最小利润，根据截止时间和利润大小决定是否选择当前工作或替换堆顶工作。

- **作者：Imakf (赞：24)  4星**
    - **关键亮点**：采用逆向思维，从时间大到小扫描，利用大根堆维护可选择的工作，通过计算时间差减少不必要的枚举，优化了时间复杂度。
    - **核心代码**：
```cpp
std::priority_queue<int> q;
struct WORK{
    int pos ,val;
    bool operator <(const WORK &B)const{return pos == B.pos ? val > B.val : pos > B.pos;}
}P[MX];
signed main(){
    int n = read();
    for(rg int i = 1 ,p ,v ; i <= n ; ++i){
        p = read(); v = read();
        P[i] = (WORK){p ,v};
    }
    std::sort(P + 1 ,P + 1 + n);
    P[n + 1] = (WORK){0 ,0};
    ll Ans = 0;
    for(rg int i = 1 ; i <= n ; ){
        while(true){
            q.push(P[i++].val);
            if(P[i].pos != P[i - 1].pos)
                break;
        }
        int cnt = P[i - 1].pos - P[i].pos;
        while(!q.empty() && cnt--){
            Ans += q.top();
            q.pop();
        }
    }
    printf("%lld\n" ,Ans);
    return 0;
}
```
    - **核心思想**：按截止时间从大到小排序，扫描每个截止时间，将该时间的工作利润加入大根堆，计算相邻截止时间的时间差，在时间差内从大根堆中取最大利润的工作。

### 最优关键思路或技巧
- **反悔贪心**：在贪心过程中，当遇到更优的选择时，放弃之前的选择，用新的选择替换，通过优先队列（小根堆或大根堆）来快速找到可替换的元素。
- **逆向思维**：从时间大到小扫描，将截止时间转换为开始时间，简化问题的处理。
- **数据结构优化**：使用树状数组、并查集等数据结构优化查找和更新操作，减少时间复杂度。

### 可拓展之处
同类型题如资源分配、任务调度等问题，都可以考虑使用反悔贪心的思想。类似算法套路包括使用优先队列维护最优解、利用逆向思维简化问题等。

### 推荐题目
- [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)
- [UVA1316 Supermarket](https://www.luogu.com.cn/problem/UVA1316)
- [P3093 [USACO13DEC]Milk Scheduling S](https://www.luogu.com.cn/problem/P3093)

### 个人心得摘录与总结
- **Ace_Heart**：提到一开始用简单贪心只能拿40分，通过分析错误原因，想到可以改变过去的选择，从而引入反悔贪心的思想，强调了对错误贪心策略的反思和改进。
- **EarthGiao**：尝试用单调队列写题失败，最后用优先队列解决问题，提醒我们不要局限于标签，要根据题目特点选择合适的数据结构。
- **_lfxxx_**：提醒定义堆时注意两个大于号不要被认为是位运算，以及结果可能很大要开 `long long`，避免因细节问题出错。 

---
处理用时：50.20秒