# 题目信息

# Renting Bikes

## 题目描述

A group of $ n $ schoolboys decided to ride bikes. As nobody of them has a bike, the boys need to rent them.

The renting site offered them $ m $ bikes. The renting price is different for different bikes, renting the $ j $ -th bike costs $ p_{j} $ rubles.

In total, the boys' shared budget is $ a $ rubles. Besides, each of them has his own personal money, the $ i $ -th boy has $ b_{i} $ personal rubles. The shared budget can be spent on any schoolchildren arbitrarily, but each boy's personal money can be spent on renting only this boy's bike.

Each boy can rent at most one bike, one cannot give his bike to somebody else.

What maximum number of schoolboys will be able to ride bikes? What minimum sum of personal money will they have to spend in total to let as many schoolchildren ride bikes as possible?

## 说明/提示

In the first sample both schoolchildren can rent a bike. For instance, they can split the shared budget in half (5 rubles each). In this case one of them will have to pay 1 ruble from the personal money and the other one will have to pay 2 rubles from the personal money. In total, they spend 3 rubles of their personal money. This way of distribution of money minimizes the amount of spent personal money.

## 样例 #1

### 输入

```
2 2 10
5 5
7 6
```

### 输出

```
2 3
```

## 样例 #2

### 输入

```
4 5 2
8 1 1 2
6 3 7 5 2
```

### 输出

```
3 8
```

# AI分析结果

### 题目内容
# 租自行车

## 题目描述
有一群$n$个男学生决定骑自行车。由于他们中没人有自行车，所以这些男孩需要租车。

租车点为他们提供了$m$辆自行车。不同自行车的租车价格不同，租第$j$辆自行车需要$p_j$卢布。

男孩们的公共预算总计为$a$卢布。此外，每个男孩都有自己的零花钱，第$i$个男孩有$b_i$卢布零花钱。公共预算可以任意分配给这些学生，但每个男孩的零花钱只能用于租自己的自行车。

每个男孩最多只能租一辆自行车，且不能把自己租的自行车给别人。

最多有多少个男孩能够骑自行车？为了让尽可能多的男孩骑自行车，他们总共最少需要花费多少零花钱？

## 说明/提示
在第一个样例中，两个学生都可以租到自行车。例如，他们可以将公共预算平分（每人5卢布）。在这种情况下，其中一人需要从零花钱中拿出1卢布，另一人需要从零花钱中拿出2卢布。总共，他们花费3卢布零花钱。这种分配方式使零花钱的花费量最小。

## 样例 #1
### 输入
```
2 2 10
5 5
7 6
```
### 输出
```
2 3
```
## 样例 #2
### 输入
```
4 5 2
8 1 1 2
6 3 7 5 2
```
### 输出
```
3 8
```

### 算法分类
二分 + 贪心

### 综合分析与结论
这些题解的核心思路均采用二分答案结合贪心策略。对于第一问，利用二分查找确定最多能租到自行车的男孩数量，通过贪心策略匹配人和车，即让钱最多的男孩按钱数从少到多的顺序去租最便宜的车，以保证尽可能多的人能租到车。对于第二问，在确定第一问的答案后，贪心地选择开销最小的车，用这些车的总花费减去公共预算，得到最少的个人零花钱花费。

不同题解在具体实现细节上略有差异，如排序方式、二分边界处理、check函数的写法等，但整体思路一致。

### 所选的题解
- **作者：Allanljx (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，详细展示了二分和贪心结合的过程，对check函数的实现和二分边界处理得当。
    - **重点代码**：
```cpp
bool check(int x)
{
    sort(b+1,b+x+1);
    int sum=0;
    for(int i=1;i<=x;i++)//便宜的车和钱少的人匹配 
    {
        sum+=max(0ll,p[i]-b[i]);
    }
    if(sum>k) return 0;
    else return 1;
}
signed main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
    }
    for(int i=1;i<=m;i++)
    {
        cin>>p[i];
    }
    sort(p+1,p+m+1);
    int l=0,r=min(n,m);
    while(l<=r)//二分 
    {
        sort(b+1,b+n+1,greater<int>());
        int mid=(l+r)/2;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans<<' ';
    int sum=0;
    for(int i=1;i<=ans;i++) sum+=p[i];
    cout<<max(0ll,sum-k);
}
```
    - **核心实现思想**：`check`函数中，先对钱数进行排序，计算租$x$辆车所需额外花费（车价减去个人钱数，若个人钱数够则为0），与公共预算比较判断是否可行。主函数中，二分查找能租车的最大人数，最后计算并输出第二问答案。
- **作者：Doubeecat (4星)**
    - **关键亮点**：对贪心策略的证明详细，代码结构清晰，check函数逻辑明确，对二分和贪心的结合讲解到位。
    - **重点代码**：
```cpp
bool check(int x) {
    int nk = k;
    int pos = x; 
    for (int i = 1;i <= x;++i) {
        if (b[i] < p[pos--]) {
            nk = nk + b[i] - p[pos+1] ;
        }
        if (nk < 0) return 0;
    }
    return nk >= 0? 1 : 0 ;
}
int main() {
    read(n,m,k);
    for (int i = 1;i <= n;++i) read(b[i]);
    for (int i = 1;i <= m;++i) read(p[i]);
    sort(b+1,b+1+n,cmp);sort(p+1,p+1+m);
    int l = 0,r = min(n,m),ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid,l = mid + 1;
        else r = mid - 1;
    }
    int sum = 0;
    for (int i = 1;i <= ans;++i) sum += p[i];
    printf("%d %d",ans,max(0,sum - k));
}
```
    - **核心实现思想**：`check`函数中，从钱最多的$x$个人和最便宜的$x$辆车进行匹配，若个人钱不够则用公共预算填补，判断公共预算是否足够。主函数二分查找答案并计算输出第二问结果。
- **作者：tallnut (4星)**
    - **关键亮点**：对第一问贪心思路的解释形象，以“田忌赛马”为例说明匹配策略，代码注释详细，对二分和贪心的实现过程展示清晰。
    - **重点代码**：
```cpp
bool check(int x)
{
    //把钱最多的x个人进行从小到大排序，钱最多的k个人中钱比较少的与便宜的车匹配
    sort(b + 1,b + x + 1);
    long long sum = 0;
    for (int i = 1;i <= x;i++)
        if (p[i] > b[i]) sum += p[i] - b[i];
    return sum <= a;
}
//从大到小排序
bool cmp(int c,int d) { return c > d; }
int main()
{
    cin >> n >> m >> a;
    for (int i = 1;i <= n;i++)
        cin >> b[i];
    for (int i = 1;i <= m;i++)
        cin >> p[i];
    //对每辆车的价格从小到大排序，贪心地选择
    sort(p + 1,p + m + 1);
    //对每个人的钱数从大到小排序，贪心地选择
    for (int i = 1;i <= n;i++)
        tmpb[i] = b[i];
    sort(tmpb + 1,tmpb + n + 1,cmp);
    //二分模板
    l = 0;
    r = min(n,m);
    while (l <= r)
    {
        //还原到从大到小排序的状态
        for (int i = 1;i <= n;i++)
            b[i] = tmpb[i];
        mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    cout << ans << ' ';
    //求解第二问
    long long sum = 0;
    for (int i = 1;i <= ans;i++)
        sum += p[i];
    if (sum > a) cout << sum - a;
    else cout << 0;
}
```
    - **核心实现思想**：`check`函数计算租$x$辆车所需额外花费与公共预算比较。主函数中先对车价和个人钱数排序，二分查找最多能租车的人数，最后计算输出第二问答案。

### 最优关键思路或技巧
1. **二分答案**：利用答案的单调性，通过二分查找快速确定最多能租到自行车的人数，减少时间复杂度。
2. **贪心匹配**：让钱最多的男孩按钱数从少到多的顺序去租最便宜的车，保证在有限预算下尽可能多的人租到车，并且能方便地计算出最少的个人零花钱花费。

### 拓展
同类型题通常涉及资源分配、数量最大化或最小化等场景，可运用二分 + 贪心策略解决。类似算法套路是先分析问题是否具有单调性，若有则考虑二分答案，再针对每个二分的结果采用贪心策略判断可行性。

### 推荐题目
1. **P1182 数列分段 Section II**：通过二分答案确定分段的最大和，结合贪心判断是否满足分段条件。
2. **P2678 [NOIP2015 提高组] 跳石头**：二分答案确定最短跳跃距离，贪心计算移走石头的数量来判断可行性。
3. **P3853 [TJOI2007] 路标设置**：二分答案确定路标间的最小距离，贪心计算需要增加的路标数量判断是否可行。 

---
处理用时：89.76秒