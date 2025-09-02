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
这些题解主要围绕贪心算法解决工作调度问题，多数采用带反悔的贪心策略，借助优先队列（小根堆或大根堆）维护已选工作的价值信息。部分题解使用树状数组、并查集等数据结构优化查找空位或时间的操作。

### 所选题解
- **作者：Taduro（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细阐述了带反悔贪心的思路，通过小根堆动态调整工作选择，使总利润最大。
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
    - **核心实现思想**：先按截止时间排序，遍历工作，若有时间做则做并将价值入小根堆；若没时间但当前工作价值大于堆顶，放弃堆顶工作，做当前工作。

- **作者：Ace_Heart（4星）**
    - **关键亮点**：详细解释了错误贪心思路及改进方法，手动实现小根堆，适合深入理解堆的操作。
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
    - **核心实现思想**：按截止时间排序工作，用手动实现的小根堆维护已选工作价值，根据工作截止时间和堆顶价值决定是否替换工作。

- **作者：Imakf（4星）**
    - **关键亮点**：采用逆向思维，按时间从大到小扫描，用大根堆维护可选工作价值，优化了时间复杂度。
    - **核心代码**：
```cpp
#include<cstdio>
#include<queue>
#include<algorithm>

#define rg register
#define MX (100000 + 5)
#define ll long long
#define int long long

std::priority_queue<int> q;

struct WORK{
    int pos,val;
    bool operator <(const WORK &B)const{return pos == B.pos? val > B.val : pos > B.pos;}
}P[MX];

signed main(){
    int n = read();
    for(rg int i = 1,p,v ; i <= n ; ++i){
        p = read(); v = read();
        P[i] = (WORK){p,v};
    }
    std::sort(P + 1,P + 1 + n);
    P[n + 1] = (WORK){0,0};
    ll Ans = 0;
    for(rg int i = 1 ; i <= n ; ){
        while(true){
            q.push(P[i++].val);
            if(P[i].pos!= P[i - 1].pos)    break;
        }
        int cnt = P[i - 1].pos - P[i].pos;
        while(!q.empty() && cnt--){
            Ans += q.top();
            q.pop();
        }
    }
    printf("%lld\n",Ans);
    return 0;
}
```
    - **核心实现思想**：按截止时间从大到小排序工作，从大到小扫描时间，将相同截止时间的工作价值入大根堆，在时间差内取堆顶元素累加利润。

### 最优关键思路或技巧
- **带反悔的贪心策略**：先按截止时间排序工作，用优先队列（小根堆）维护已选工作价值，遇到价值更高但没时间做的工作时，放弃堆顶工作，选择当前工作。
- **逆向思维**：按时间从大到小扫描，将相同截止时间的工作价值入大根堆，在时间差内取堆顶元素累加利润，优化时间复杂度。
- **数据结构优化**：使用树状数组、并查集等数据结构优化查找空位或时间的操作。

### 可拓展之处
同类型题如商品销售问题、任务分配问题等，都可采用带反悔的贪心策略，用优先队列维护已选元素信息。类似算法套路还有反悔堆、决策包容性贪心等。

### 推荐题目
- [P1484 种树](https://www.luogu.com.cn/problem/P1484)
- [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)
- [P3093 [USACO13DEC]Milk Scheduling S](https://www.luogu.com.cn/problem/P3093)

### 个人心得摘录与总结
- **作者：Ace_Heart**：先想到简单贪心思路只能拿40分，意识到前期做低报酬工作后期可能后悔，从而改进为带反悔的贪心，用小根堆维护最低报酬工作。
- **作者：EarthGiao**：尝试用单调队列无果，改用优先队列很快AC，提醒做题时不要局限于标签，可根据题目特点灵活选择数据结构。
- **作者：_lfxxx_**：定义堆时注意两个大于号不要被认为是位运算，同时强调结果可能很大要开`long long`。 

---
处理用时：52.17秒