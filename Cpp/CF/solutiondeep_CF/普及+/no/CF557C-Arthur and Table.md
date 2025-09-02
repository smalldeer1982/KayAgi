# 题目信息

# Arthur and Table

## 题目描述

Arthur has bought a beautiful big table into his new flat. When he came home, Arthur noticed that the new table is unstable.

In total the table Arthur bought has $ n $ legs, the length of the $ i $ -th leg is $ l_{i} $ .

Arthur decided to make the table stable and remove some legs. For each of them Arthur determined number $ d_{i} $ — the amount of energy that he spends to remove the $ i $ -th leg.

A table with $ k $ legs is assumed to be stable if there are more than half legs of the maximum length. For example, to make a table with $ 5 $ legs stable, you need to make sure it has at least three (out of these five) legs of the maximum length. Also, a table with one leg is always stable and a table with two legs is stable if and only if they have the same lengths.

Your task is to help Arthur and count the minimum number of energy units Arthur should spend on making the table stable.

## 样例 #1

### 输入

```
2
1 5
3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
2 4 4
1 1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6
2 2 1 1 3 3
4 3 5 5 2 1
```

### 输出

```
8
```

# AI分析结果

### 题目内容
# 亚瑟和桌子

## 题目描述
亚瑟把一张漂亮的大桌子搬进了他的新公寓。当他回到家时，亚瑟注意到这张新桌子不稳。

亚瑟买的桌子总共有 $n$ 条腿，第 $i$ 条腿的长度为 $l_{i}$ 。

亚瑟决定让桌子稳定下来，于是要移除一些桌腿。对于每条腿，亚瑟确定了数字 $d_{i}$ ，即移除第 $i$ 条腿所花费的能量。

如果长度为最长的腿的数量超过总腿数的一半，那么有 $k$ 条腿的桌子就被认为是稳定的。例如，对于一张有 $5$ 条腿的桌子，要使其稳定，至少需要有三条（在这五条腿中）长度为最长的腿。此外，只有一条腿的桌子总是稳定的，有两条腿的桌子当且仅当它们长度相同时是稳定的。

你的任务是帮助亚瑟，计算出使桌子稳定所需花费的最小能量值。

## 样例 #1
### 输入
```
2
1 5
3 2
```
### 输出
```
2
```

## 样例 #2
### 输入
```
3
2 4 4
1 1 1
```
### 输出
```
0
```

## 样例 #3
### 输入
```
6
2 2 1 1 3 3
4 3 5 5 2 1
```
### 输出
```
8
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路大多围绕枚举最长腿的长度展开，主要差异在于处理删除腿的选择方式。部分题解利用排序、后缀和、桶、动态规划数组等预处理信息，快速确定删除腿的数量及具体选择。有的使用权值线段树、主席树等数据结构优化查找，有的则运用贪心策略直接选择。整体上，各题解都基于贪心思想，通过不同方式解决如何选择删除腿以最小化能量花费的问题。

### 所选的题解
- **作者：gesong (赞：12)  星级：5星 关键亮点：采用正难则反思路，将最小化移走腿的能量值转化为最大化保留腿的能量值，利用vector和multiset简化操作，代码简洁高效**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N],b[N];
multiset<int,greater<int> >s;
vector<int>c[N];
inline int read(){
    char c=getchar();
    int f=1,ans=0;
    while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
    while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
    return ans*f;
}
main(){
    int n=read(),sum=0,ans=1e18;
    for (int i=1;i<=n;i++) a[i]=read();
    for (int i=1;i<=n;i++) b[i]=read(),sum+=b[i],s.insert(b[i]);
    for (int i=1;i<=n;i++) c[a[i]].push_back(b[i]);
    for (int i=1;i<N;i++) sort(c[i].begin(),c[i].end(),greater<int>());
    for (int i=N;i>0;i--) if (!c[i].empty()){
        for (auto j:c[i]) s.erase(s.find(j));
        int sum1=0;
        for (auto j:c[i]) sum1+=j;
        int len=c[i].size()-1;
        if (s.size()<=len){
            for (auto i:s) sum1+=i;
            ans=min(ans,sum-sum1);
        } 
        else{
            for (auto i:s){
                if (!len) break;
                sum1+=i;
                len--;
            } 
            ans=min(ans,sum-sum1);
        }
    }
    cout <<ans;
    return 0;
}
```
核心实现思想：先将相同长度腿的能量值存入vector，从大到小枚举腿的长度，对每种长度，将其能量值从multiset中移除并累加，根据剩余可选择腿的数量在multiset中选择能量值累加，最后用总能量值减去保留腿的能量值得到最小移除能量。

- **作者：yzh_Error404 (赞：0)  星级：4星 关键亮点：通过两个优先队列（小根堆和大根堆）维护当前长度之前的能量，利用堆的特性快速选择附带桌腿的能量，思路清晰，代码实现简洁**
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5;
struct node
{
    int l,d;
}e[MAXN];
priority_queue<int,vector<int>,greater<int> >q1;
priority_queue<int,vector<int>,less<int> >q2;
inline bool cmp(node a,node b)
{
    if(a.l==b.l)return a.d<b.d;
    return a.l<b.l;
}
ll n,eg,ans,sum=0;
signed main()
{
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++)
        scanf("%d",&e[i].l);
    for(register int i=1;i<=n;i++)
        scanf("%d",&e[i].d),eg+=e[i].d;
    ans=eg-e[1].d;
    for(register int i=1;i<=n;i++)
        ans=min(ans,eg-e[i].d);
    sort(e+1,e+1+n,cmp);
    for(register int i=1;i<=n;)
    {
        int j=i,now=e[i].d;
        while(e[j+1].l==e[i].l&&j+1<=n)now+=e[++j].d;
        ans=min(ans,eg-now);
        int len=j-i;//这是可以附带的桌腿数
        while(q1.size()<len&&!q2.empty()){q1.push(q2.top());sum+=q2.top();q2.pop();}
        while(q1.size()>len){q2.push(q1.top());sum-=q1.top();q1.pop();}//通过插入和弹出来使小根堆中恰好有len个数
        ans=min(ans,eg-now-sum);
        for(register int k=i;k<=j;k++)
        {
            if(q2.empty()||e[k].d>q2.top())q1.push(e[k].d),sum+=e[k].d;//依旧要满足小根堆中的所有数大于大根堆中的所有数
            else q2.push(e[k].d);
        }
        i=j+1;
    }
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：先按腿长排序，枚举每种长度，计算该长度腿的能量和，通过调整大小根堆，使小根堆中元素个数为可附带桌腿数，累加小根堆元素能量，与总能量减去当前长度腿能量和比较取最小值。

- **作者：Hisaishi_Kanade (赞：0)  星级：4星 关键亮点：利用桶记录能量值分布，结合后缀和计算删除腿的花费，通过巧妙的统计和更新方式，在较小值域情况下有效降低时间复杂度**
```cpp
#include <stdio.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
//using ll=long long;
const int V=205;
int t[V],v[V],tt[100005];
class Etinorally
{
public:
    int x,y;
    inline const bool operator<(const Etinorally &other)const
    {
        return x<other.x;
    } 
}e[100005]; 
inline int solve(int divv)
{
    if(divv<=0)
        return 0;
    int i,ret=0;
    rep(i,1,V)
    {
        if(t[i]>divv)
        {
            ret+=divv*i;
            return ret;
        }else
        {
            ret+=t[i]*i;
            divv-=t[i];
        }
//		printf("::%d %d\n",i,divv);
    }
    return ret;
}
//cnt-t[div]+1<=t[i]
int n,i,j,ret;
#include <algorithm>
inline int min(int x,int y){return x<y?x:y;}
int main()
{ 
    int sum=0;
    ret=1<<25;
    scanf("%d",&n);
    rep(i,1,V)
        t[i]=0;
    rep(i,1,100000)
        tt[i]=0;
    rep(i,1,n)
        scanf("%d",&e[i].x);
    rep(i,1,n)
        scanf("%d",&e[i].y);
    rep(i,1,n)
        ++tt[e[i].x];
    std::sort(e+1,e+n+1);
    rep(i,1,n)
        sum+=e[i].y;
    rep(i,1,n)
    {
        sum-=e[i].y;
        if(e[i].x==e[i+1].x)
            continue;
//			printf("%d %d\n",sum,i-2*tt[e[i].x]);
        ret=min(ret,sum+solve(i-2*tt[e[i].x]+1));
        rep(j,i-tt[e[i].x]+1,i)
            ++t[e[j].y];
    }
    printf("%d\n",ret);
    return 0;
}
```
核心实现思想：先按腿长排序，在腿长变化时统计答案，通过后缀和计算大于当前腿长的删除花费，利用桶统计小于当前腿长的能量分布，从小到大扫桶计算需删除的最小花费。

### 最优关键思路或技巧
1. **正难则反思路**：如gesong题解，将最小化移除腿的能量转化为最大化保留腿的能量，简化问题求解。
2. **数据结构运用**：如使用multiset、优先队列、桶、权值线段树等数据结构，优化查找和选择删除腿的过程，提高算法效率。
3. **预处理与贪心策略结合**：通过排序、后缀和、计数等预处理，结合贪心选择删除腿，使算法逻辑清晰，实现高效。

### 同类型题或类似算法套路
此类题目通常围绕满足特定条件下的最优选择问题，常需结合贪心思想，通过枚举关键变量（如本题最长腿长度），利用合适的数据结构或预处理信息，快速确定最优选择。类似套路可应用于资源分配、任务调度等场景的题目。

### 推荐洛谷题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：同样运用贪心策略，通过合并操作最小化总代价。
2. [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要根据题目条件进行贪心选择，以达到最优结果。
3. [P1080 [NOIP2012 提高组] 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据排序并贪心选择，解决最大化收益问题。

### 个人心得
无。 

---
处理用时：131.95秒