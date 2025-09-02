# 题目信息

# Elections

## 题目描述

You are running for a governor in a small city in Russia. You ran some polls and did some research, and for every person in the city you know whom he will vote for, and how much it will cost to bribe that person to vote for you instead of whomever he wants to vote for right now. You are curious, what is the smallest amount of money you need to spend on bribing to win the elections. To win elections you need to have strictly more votes than any other candidate.

## 样例 #1

### 输入

```
5
1 2
1 2
1 2
2 1
0 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
1 2
1 2
2 1
0 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1
100000 0
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 选举

## 题目描述
你正在俄罗斯的一个小城市竞选州长。你进行了一些民意调查和研究，对于城市中的每个人，你都知道他会投票给谁，以及贿赂这个人转而投票给你而非他原本想投的人需要花费多少钱。你很好奇，为了赢得选举，你需要花费的最小贿赂金额是多少。要赢得选举，你需要获得比其他任何候选人都严格更多的选票。

## 样例 #1
### 输入
```
5
1 2
1 2
1 2
2 1
0 0
```
### 输出
```
3
```

## 样例 #2
### 输入
```
4
1 2
1 2
2 1
0 0
```
### 输出
```
2
```

## 样例 #3
### 输入
```
1
100000 0
```
### 输出
```
0
```

### 算法分类
二分 + 贪心

### 综合分析与结论
这些题解的核心思路都是通过二分法确定最终获胜所需的票数 \(x\)，再结合贪心策略计算获取 \(x\) 张票的最小花费。具体要点为：对每个候选人，将票数大于等于 \(x\) 的对手的票买走，优先选择花费少的；若买完这些票后还不够 \(x\) 张，则从剩下的票中继续选择花费少的购买。解决难点在于理解不能单纯正向贪心买最便宜的票，而是要逆向考虑削弱对手票数。不同题解在代码实现细节上略有不同，如数据结构的使用、输入输出方式、二分的具体实现等。

### 所选的题解
- **作者：Computer1828 (5星)**
  - **关键亮点**：思路清晰，代码简洁高效。使用 `vector` 存储数据，通过 `check` 函数计算获取特定票数的花费，二分查找最优票数。
  - **核心代码**：
```cpp
inline int check(int u){//返回需要u张票要花多少钱
    int ans = 0,tot = a[0].size();
    vector<int> nti;//剩下的票池
    for(int i = 1;i<=N;++i){
        int j = 0,k = a[i].size();
        while(k>=u) ans += a[i][j++],--k,++tot;//把票数大于等于u的人的票买掉
        while(j<a[i].size()) nti.push_back(a[i][j++]);
    }
    sort(nti.begin(),nti.end());
    for(int i = 0;i<nti.size();++i){
        if(tot>=u) break;//如果够票了，就退出
        ans += nti[i],++tot;//不够票就继续买
    }
    return ans;
}
int main(){
    scanf("%d",&n);
    int u,v;
    for(int i = 1;i<=n;++i) scanf("%d%d",&u,&v),a[u].push_back(v);
    for(int i = 1;i<=N;++i) sort(a[i].begin(),a[i].end());
    int l = 1,r = n;
    while(l<=r){
        int mid = (l+r)/2;
        if(check(mid) < check(mid+1)) r = mid-1;
        else l = mid+1;
    }
    printf("%d",check(l));
    return 0;
}
```
  - **核心实现思想**：`check` 函数遍历每个候选人，先买走票数大于等于 \(u\) 的对手的票，剩余票放入 `nti` 中，排序后再从中买票直到达到 \(u\) 张。主函数中二分查找最优票数 \(l\)，输出获取 \(l\) 张票的花费。

- **作者：AladV (4星)**
  - **关键亮点**：代码注释详细，对题意和做法分析清晰。使用结构体存储数据，通过 `check` 函数判断给定票数下的最小花费，二分查找最优解。
  - **核心代码**：
```cpp
int check(int x)
{
    memset(cnt,0,sizeof(cnt));
    int mine=0;
    int res=0;
    for(int i=1;i<=n;i++)
    {
        if(!a[i].tar) mine++,alli[i]=true;
        else alli[i]=false,cnt[a[i].tar]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(!alli[i] && cnt[a[i].tar]>=x) 
        {
            cnt[a[i].tar]--;
            mine++;
            res+=a[i].val;
            alli[i]=true;
        }
    }
    if(mine<x)
    {
        for(int i=1;i<=n;i++)
        {
            if(!alli[i]) 
            {
                mine++;
                res+=a[i].val;
            }
            if(mine==x) return res;
        }
    }
    else return res;
    return 1e18;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i].tar=read(),a[i].val=read();
    sort(a+1,a+n+1,cmp);
    l=1,r=0x3f3f3f3f;
    int ans=0x3f3f3f3f;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        int curans=check(mid);
        if(check(mid+1)>=curans) r=mid-1,ans=curans;
        else l=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}
```
  - **核心实现思想**：`check` 函数先统计初始状态下自己的票数 `mine` 和各对手票数 `cnt`，然后遍历选民，若对手票数大于等于 \(x\) 则买走该选民票，若最后自己票数小于 \(x\)，继续从剩余选民买票直到达到 \(x\)。主函数中二分查找最优票数对应的最小花费。

- **作者：傅思维666 (4星)**
  - **关键亮点**：点明与类似题目的联系，思路明确。使用 `vector` 存储数据，通过 `check` 函数计算买 \(x\) 张选票的花费，二分查找最优票数。
  - **核心代码**：
```cpp
ll check(int x)//买x张选票能否更优
{
    ll ret=0;
    int tot=0;
    vector<int> tmp;
    for(int i=1;i<=m;++i)
    {
        int j=0,k=v[i].size();
        while(k>=x) 
            ret+=v[i][j++],--k,++tot;
        while(j<v[i].size()) 
            tmp.push_back(v[i][j++]);
    }
    sort(tmp.begin(),tmp.end());
    for(int i=0;i<tmp.size();++i)
    {
        if(tot>=x) 
            break;
        ret+=tmp[i],++tot;
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int p,c;
        scanf("%d%d",&p,&c);
        v[p].push_back(c);
    }
    for(int i=1;i<=m;i++)
        sort(v[i].begin(),v[i].end());
    for(int i=0;i<v[1].size();i++)
        v[1][i]=0;
    int l=1,r=n;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)<check(mid+1))
            r=mid-1;
        else
            l=mid+1;
    }
    printf("%lld\n",check(l));
    return 0;
}
```
  - **核心实现思想**：`check` 函数遍历每个候选人，买走票数大于等于 \(x\) 的对手的票，剩余票放入 `tmp` 中，排序后再从中买票直到达到 \(x\) 张。主函数中二分查找最优票数 \(l\)，输出获取 \(l\) 张票的花费。

### 最优关键思路或技巧
通过二分法确定最终获胜票数，将原问题转化为已知票数求最小花费问题，再利用贪心策略，优先选择花费少的票进行购买，有效降低了时间复杂度。在实现过程中，合理使用数据结构如 `vector` 存储数据，方便数据处理和操作。

### 可拓展之处
同类型题通常围绕选举、竞争等场景，涉及到资源分配与策略选择，核心是通过某种策略优化目标值。类似算法套路为：在难以直接求解最优解时，考虑能否通过二分等方法缩小问题规模，再结合贪心等策略解决子问题。

### 推荐洛谷题目
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：通过贪心策略解决删数求最小值问题，与本题贪心思想类似。
- [P2672 推销员](https://www.luogu.com.cn/problem/P2672)：结合贪心与堆优化，与本题通过策略优化目标值思路类似。
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：利用贪心策略对数据分组，锻炼贪心思维。

### 个人心得
暂未发现题解中有个人心得相关内容。 

---
处理用时：67.65秒