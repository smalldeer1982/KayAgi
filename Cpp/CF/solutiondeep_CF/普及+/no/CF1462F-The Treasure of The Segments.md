# 题目信息

# The Treasure of The Segments

## 题目描述

$Polycarp$有$n$个数字区间，每个区间有两个参数$l[i]$（起始），$r[i]$（结束）。

$Polycarp$对一个好集合的定义是：

你在所有元素中选取部分元素组成这个集合。

你可以在这个集合中找到一个元素$p[i]$，使这个集合中每个元素都至少含有$p[i]$左右区间涵盖的数字之一。

题目给的样例$[[1,4],[2,3],[3,6]]$是一个好集合。$[[1,2],[2,3],[3,5],[4,5]]$则不是一个好集合。

现在给你$n$个数字区间，让你求从中至少删去多少个元素，才能使该集合为一个好集合。

## 样例 #1

### 输入

```
4
3
1 4
2 3
3 6
4
1 2
2 3
3 5
4 5
5
1 2
3 8
4 5
6 7
9 10
5
1 5
2 4
3 5
3 8
4 8```

### 输出

```
0
1
2
0```

# AI分析结果

### 题目翻译
#### 线段的宝藏

##### 题目描述
$Polycarp$ 有 $n$ 个数字区间，每个区间有两个参数 $l[i]$（起始），$r[i]$（结束）。

$Polycarp$ 对一个好集合的定义是：
你在所有元素中选取部分元素组成这个集合。
你可以在这个集合中找到一个元素 $p[i]$，使这个集合中每个元素都至少含有 $p[i]$ 左右区间涵盖的数字之一。

题目给的样例 $[[1,4],[2,3],[3,6]]$ 是一个好集合。$[[1,2],[2,3],[3,5],[4,5]]$ 则不是一个好集合。

现在给你 $n$ 个数字区间，让你求从中至少删去多少个元素，才能使该集合为一个好集合。

##### 样例 #1
###### 输入
```
4
3
1 4
2 3
3 6
4
1 2
2 3
3 5
4 5
5
1 2
3 8
4 5
6 7
9 10
5
1 5
2 4
3 5
3 8
4 8
```
###### 输出
```
0
1
2
0
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是将问题转化为求与其他线段相交最多的一条线段，用总线段数减去与之相交的线段数即为要删除的线段数。不同题解的实现方式有所不同，主要区别在于处理不相交线段数量的统计方法。

部分题解使用二分查找来确定位置，利用排序后的左右端点数组快速计算不相交线段数量；部分题解采用离散化和前缀和的方法，将值域较大的端点进行离散化处理，再用前缀和优化统计过程；还有题解使用树状数组、莫队算法等数据结构和算法来实现。

### 所选题解
- **mot1ve（4星）**
    - **关键亮点**：思路巧妙简单，不需要离散化和任何数据结构，通过排序和二分查找确定不相交线段的位置，代码实现简洁明了。
- **Eibon（4星）**
    - **关键亮点**：思路清晰，利用 vector 维护左右端点，通过 lower_bound 查找不相交线段数量，代码实现简洁。
- **JustinXiaoJunyang（4星）**
    - **关键亮点**：思路与 mot1ve 类似，先排序再用二分确定位置，代码结构清晰，易于理解。

### 重点代码
#### mot1ve 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
struct node{
    int x,y;
}a[1000010];
vector<int> l,r;
int main()
{
    cin>>T;
    while(T--)
    {
        int n;
        scanf("%d",&n);
        l.clear();
        r.clear();
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&a[i].x,&a[i].y);
            l.push_back(a[i].x);
            r.push_back(a[i].y);
        }
        sort(l.begin(),l.end());
        sort(r.begin(),r.end());
        int ans=1e9;
        for(int i=1;i<=n;i++)
        {
            int res=0;
            int dl=upper_bound(l.begin(),l.end(),a[i].y)-l.begin();
            res+=(n-dl+1);
            int dr=lower_bound(r.begin(),r.end(),a[i].x)-r.begin();
            res+=(dr-1);
            ans=min(ans,res);
        }
        cout<<ans<<endl;
    } 
    return 0;
} 
```
**核心实现思想**：先将所有线段的左右端点分别存储在两个 vector 中并排序，然后枚举每条线段，通过二分查找确定左端点大于当前线段右端点的线段数量和右端点小于当前线段左端点的线段数量，两者之和即为与当前线段不相交的线段数量，取最小值即为答案。

#### Eibon 的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int T,n,res,ans;
struct node
{
    int l,r;
};
node a[maxn];
vector<int>l,r;
signed main()
{
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        l.clear();r.clear();
        for(int i=1;i<=n;i++){
            scanf("%lld%lld",&a[i].l,&a[i].r);
            l.push_back(a[i].l);
            r.push_back(a[i].r);
        }
        sort(l.begin(),l.end());
        sort(r.begin(),r.end());
        ans=1e18;
        for(int i=1;i<=n;i++){
            int ll=lower_bound(l.begin(),l.end(),a[i].r+1)-l.begin();
            int rr=lower_bound(r.begin(),r.end(),a[i].l)-r.begin();
            ans=min(ans,n+rr-ll);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```
**核心实现思想**：同样将左右端点存储在 vector 中并排序，枚举每条线段，利用 lower_bound 查找左端点大于当前线段右端点加 1 的线段位置和右端点大于等于当前线段左端点的线段位置，通过计算得到不相交线段数量，取最小值为答案。

#### JustinXiaoJunyang 的题解
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node
{
    int x, y;
} a[1000005];
vector <int> l, r;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        l.clear();
        r.clear();
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].x >> a[i].y;
            l.push_back(a[i].x);
            r.push_back(a[i].y);
        }
        sort(l.begin(), l.end());
        sort(r.begin(), r.end());
        int ans = 1e9;
        for (int i = 1; i <= n; i++)
        {
            int res = 0;
            int t1 = upper_bound(l.begin(), l.end(), a[i].y) - l.begin();
            res += (n - t1 + 1);
            int t2 = lower_bound(r.begin(), r.end(), a[i].x) - r.begin();
            res += (t2 - 1);
            ans = min(ans, res);
        }
        cout << ans << endl;
    } 
    return 0;
}
```
**核心实现思想**：与 mot1ve 的思路一致，先排序再用二分查找确定不相交线段数量，取最小值作为答案。

### 最优关键思路或技巧
- 排序和二分查找：将线段的左右端点分别排序，利用二分查找快速确定不相交线段的位置，时间复杂度为 $O(n \log n)$。
- 问题转化：将求至少删除多少条线段使集合为好集合的问题转化为求与其他线段相交最多的一条线段，简化问题求解。

### 可拓展之处
同类型题或类似算法套路：
- 区间覆盖问题：给定多个区间，求最少需要多少个区间才能覆盖某个特定区间。
- 区间合并问题：将多个有重叠的区间合并成尽可能少的区间。
- 区间查询问题：查询某个区间内满足特定条件的元素数量。

### 推荐题目
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
- [P2082 区间覆盖](https://www.luogu.com.cn/problem/P2082)
- [P1712 [NOI2016] 区间](https://www.luogu.com.cn/problem/P1712)

### 个人心得
部分题解提到本题有一定难度，如 mango2011 提到做出了 *2200 的感觉，说明本题需要一定的思维和算法基础。在实现过程中，需要注意离散化、二分查找等操作的细节，避免出错。同时，不同的算法实现方式可能会有不同的时间复杂度和空间复杂度，需要根据具体情况选择合适的算法。

---
处理用时：56.09秒