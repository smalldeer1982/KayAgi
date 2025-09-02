# 题目信息

# Case of Fugitive

## 题目描述

有$n$个区间，分别为$[l_i,r_i]$，$r_i<l_{i+1}$



有$m$条线段，长度分别为$a_i$，当线段的两个端点分别在两个相邻的区间内是，线段可以连接这两个区间。



询问能否将所有区间联通。

## 说明/提示

$2\le n\le2\times10^5,1\le m\le2\times10^5$



$1\le l_i\le r_i\le10^{18},1\le a_i\le10^{18}$

## 样例 #1

### 输入

```
4 4
1 4
7 8
9 10
12 14
4 5 3 8
```

### 输出

```
Yes
2 3 1 
```

## 样例 #2

### 输入

```
2 2
11 14
17 18
2 9
```

### 输出

```
No
```

## 样例 #3

### 输入

```
2 1
1 1
1000000000000000000 1000000000000000000
999999999999999999
```

### 输出

```
Yes
1 
```

# AI分析结果

### 题目内容
# 追捕案例

## 题目描述
有$n$个区间，分别为$[l_i,r_i]$，且$r_i<l_{i + 1}$。

有$m$条线段，长度分别为$a_i$，当线段的两个端点分别在两个相邻的区间内时，线段可以连接这两个区间。

询问能否将所有区间联通。

## 说明/提示
$2\le n\le2\times10^5$，$1\le m\le2\times10^5$。

$1\le l_i\le r_i\le10^{18}$，$1\le a_i\le10^{18}$。

## 样例 #1
### 输入
```
4 4
1 4
7 8
9 10
12 14
4 5 3 8
```
### 输出
```
Yes
2 3 1 
```

## 样例 #2
### 输入
```
2 2
11 14
17 18
2 9
```
### 输出
```
No
```

## 样例 #3
### 输入
```
2 1
1 1
1000000000000000000 1000000000000000000
999999999999999999
```
### 输出
```
Yes
1 
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是将原问题转化为用给定长度的点（线段长度）去覆盖一些区间（相邻区间可连接的线段长度范围）的问题，然后通过贪心策略解决。
 - **思路方面**：多数题解先计算出相邻区间可连接的线段长度范围，再对区间和点分别排序。在选择点覆盖区间时，都遵循贪心原则，但具体实现方式有差异。
 - **算法要点**：排序操作是为了方便后续的贪心选择，数据结构的选择影响实现的效率，如优先队列、set等。
 - **解决难点**：难点在于证明贪心策略的正确性，以及选择合适的数据结构优化操作。例如，为什么选择右端点最小且大于当前点坐标的区间能保证最优解。

### 所选的题解
 - **作者：Plozia（5星）**
    - **关键亮点**：思路清晰，详细阐述了题意转化过程和贪心策略，代码实现简洁明了，使用优先队列维护区间，逻辑严谨。
    - **核心代码片段**：
```cpp
int main()
{
    n = Read(), m = Read();
    for (int i = 1; i <= n; ++i) l[i] = Read(), r[i] = Read();
    for (int i = 1; i <= m; ++i) q[i].d = Read(), q[i].id = i;
    for (int i = 1; i < n; ++i) a[i].l = l[i + 1] - r[i], a[i].r = r[i + 1] - l[i], a[i].id = i;
    std::sort(a + 1, a + n, cmp1); std::sort(q + 1, q + m + 1, cmp2);
    int j = 1;
    for (int i = 1; i <= m; ++i)
    {
        while (j < n && a[j].l <= q[i].d) pq.push(a[j++]);
        if (pq.empty()) continue ;
        if (pq.top().r < q[i].d) { printf("No\n"); return 0; }
        node1 x = pq.top(); pq.pop(); ans[x.id] = q[i].id;
    }
    if (!pq.empty() || j!= n) { printf("No\n"); return 0; }
    printf("Yes\n");
    for (int i = 1; i < n; ++i) printf("%lld ", ans[i]); printf("\n"); return 0;
}
```
    - **核心实现思想**：先读入数据并转化为可连接区间范围和线段长度，排序后，遍历线段长度，将符合左端点条件的区间加入优先队列，从优先队列中取出合适区间并用当前线段覆盖，最后判断是否所有区间都被覆盖。
 - **作者：jianhe（4星）**
    - **关键亮点**：提出了一种不同的贪心排序方式，按相邻区间总长度和两者之间距离排序，使用set实现快速二分和删除操作，代码简洁高效。
    - **核心代码片段**：
```cpp
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y;
    for(int i=1;i<=m;i++) cin>>x,s.insert({x,i});
    for(int i=1;i<n;i++) a[i].v=p[i+1].x-p[i].y,a[i].i=i,a[i].up=p[i+1].y-p[i].x;
    sort(a+1,a+n);
    for(int i=1;i<n;i++){
        auto it=s.lower_bound({a[i].v,0});
        if(it==s.end()){cout<<"No";return 0;}
        ll x=it->x;
        if(x>a[i].up){cout<<"No";return 0;}
        ans[a[i].i]=it->i;s.erase(it);
    }
    cout<<"Yes\n";
    for(int i=1;i<n;i++) cout<<ans[i]<<" ";
    return 0;
}
```
    - **核心实现思想**：读入区间和线段数据，计算相邻区间可连接范围并排序，遍历区间，在set中查找符合长度范围的线段，若找到则记录并删除，否则输出No。
 - **作者：Tx_Lcy（4星）**
    - **关键亮点**：思路清晰，同样是转化问题后进行排序，利用小根堆维护区间，代码注释详细，易于理解。
    - **核心代码片段**：
```cpp
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i) cin>>l[i]>>r[i];
    for (int i=1;i<n;++i) a[i].l=l[i+1]-r[i],a[i].r=r[i+1]-l[i],a[i].id=i;
    sort(a+1,a+n,cmp);
    for (int i=1;i<=m;++i) cin>>w[i].x,w[i].id=i;
    if (n-1>m) return cout<<"No\n",0;
    sort(w+1,w+m+1,cmp1);
    int l=0;priority_queue<
    pair<int,int>,deque< pair<int,int> >,
    greater< pair<int,int> > >q;
    int solved=0;
    for (int i=1;i<=m;++i){
        while (a[l+1].l<=w[i].x && l+1<n) ++l,q.push({a[l].r,a[l].id});
        if (q.empty()) continue;
        if (q.top().first<w[i].x) return cout<<"No\n",0;
        b[q.top().second]=w[i].id;
        q.pop();++solved;
    }
    if (q.size() || solved!=n-1) return cout<<"No\n",0;
    cout<<"Yes\n";
    for (int i=1;i<n;++i) cout<<b[i]<<' ';cout<<'\n';
    return 0;
}
```
    - **核心实现思想**：读入数据并转化为区间和点，排序后，遍历点，将符合左端点条件的区间加入小根堆，从堆中取出合适区间并用当前点覆盖，最后判断是否所有区间都被覆盖。

### 最优关键思路或技巧
 - **问题转化**：将原问题转化为点覆盖区间问题，使问题更易于解决。
 - **贪心策略**：按一定规则对区间和点排序后，每次选择右端点最小且大于当前点坐标的区间进行覆盖，能保证最优解。
 - **数据结构选择**：如使用优先队列维护区间，利用其自动排序特性，方便取出符合条件的区间；使用set实现快速二分查找和删除操作，提高效率。

### 拓展思路
同类型题可考察不同的贪心场景，如区间选点、活动安排等。类似算法套路是先对数据进行合理排序，再基于贪心思想选择合适的数据结构进行操作。

### 洛谷题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)
 - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)

### 个人心得摘录与总结
 - **作者jianhe**：在本题中疯狂 `CE`（编译错误）喜提 $-23$，提醒在做题时要注意代码编译问题，如语法错误、头文件引用等。 

---
处理用时：68.64秒