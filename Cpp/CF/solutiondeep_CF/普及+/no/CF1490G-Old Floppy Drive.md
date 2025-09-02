# 题目信息

# Old Floppy Drive

## 题目描述

Polycarp was dismantling his attic and found an old floppy drive on it. A round disc was inserted into the drive with $ n $ integers written on it.

Polycarp wrote the numbers from the disk into the $ a $ array. It turned out that the drive works according to the following algorithm:

- the drive takes one positive number $ x $ as input and puts a pointer to the first element of the $ a $ array;
- after that, the drive starts rotating the disk, every second moving the pointer to the next element, counting the sum of all the elements that have been under the pointer. Since the disk is round, in the $ a $ array, the last element is again followed by the first one;
- as soon as the sum is at least $ x $ , the drive will shut down.

Polycarp wants to learn more about the operation of the drive, but he has absolutely no free time. So he asked you $ m $ questions. To answer the $ i $ -th of them, you need to find how many seconds the drive will work if you give it $ x_i $ as input. Please note that in some cases the drive can work infinitely.

For example, if $ n=3, m=3 $ , $ a=[1, -3, 4] $ and $ x=[1, 5, 2] $ , then the answers to the questions are as follows:

- the answer to the first query is $ 0 $ because the drive initially points to the first item and the initial sum is $ 1 $ .
- the answer to the second query is $ 6 $ , the drive will spin the disk completely twice and the amount becomes $ 1+(-3)+4+1+(-3)+4+1=5 $ .
- the answer to the third query is $ 2 $ , the amount is $ 1+(-3)+4=2 $ .

## 样例 #1

### 输入

```
3
3 3
1 -3 4
1 5 2
2 2
-2 0
1 2
2 2
0 1
1 2```

### 输出

```
0 6 2 
-1 -1 
1 3```

# AI分析结果

### 题目翻译
Polycarp 正在清理他的阁楼，在那里发现了一个旧的软盘驱动器。驱动器中插入了一张圆形磁盘，上面写着 $n$ 个整数。

Polycarp 将磁盘上的数字写入了数组 $a$ 中。结果发现，该驱动器按照以下算法工作：
- 驱动器接收一个正整数 $x$ 作为输入，并将指针指向数组 $a$ 的第一个元素；
- 之后，驱动器开始旋转磁盘，每秒将指针移动到下一个元素，并计算指针所指元素的总和。由于磁盘是圆形的，在数组 $a$ 中，最后一个元素之后紧接着是第一个元素；
- 一旦总和至少达到 $x$，驱动器就会关闭。

Polycarp 想更多地了解驱动器的工作原理，但他完全没有空闲时间。因此，他向你提出了 $m$ 个问题。要回答第 $i$ 个问题，你需要找出如果将 $x_i$ 作为输入，驱动器将工作多少秒。请注意，在某些情况下，驱动器可能会无限期工作。

例如，如果 $n = 3$，$m = 3$，$a = [1, -3, 4]$ 且 $x = [1, 5, 2]$，则问题的答案如下：
- 第一个查询的答案是 $0$，因为驱动器最初指向第一个元素，初始总和为 $1$。
- 第二个查询的答案是 $6$，驱动器将磁盘完全旋转两次，总和变为 $1 + (-3) + 4 + 1 + (-3) + 4 + 1 = 5$。
- 第三个查询的答案是 $2$，总和为 $1 + (-3) + 4 = 2$。

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是先计算数组的前缀和以及前缀和的最大值，然后根据查询的目标值 $x$ 进行分类讨论。如果在第一轮就能达到目标值，直接通过二分查找找到满足条件的位置；如果第一轮达不到，且数组一个周期的和小于等于 0，则无法达到目标值，输出 -1；如果和大于 0，则计算需要循环的次数，再在剩余的目标值中通过二分查找满足条件的位置。

各题解的区别主要在于实现细节和代码风格，有的使用 `map` 存储信息，有的使用数组存储前缀和及前缀和最大值，但整体的算法框架是一致的。

### 所选题解
- **作者：henrytb (赞：8)  4星**
    - **关键亮点**：使用 `map` 存储蜗牛在一次循环内能到达的正数所需的最短时间，通过 `lower_bound` 进行查找，思路清晰，代码实现简洁。
- **作者：绝顶我为峰 (赞：1)  4星**
    - **关键亮点**：详细地阐述了每一步的思路，通过二分圈数和在 `maxn` 数组上二分查找，逻辑严谨。
- **作者：Special_Tony (赞：1)  4星**
    - **关键亮点**：使用数组存储前缀和的最大值，通过简单的判断和二分查找解决问题，代码简洁易懂。

### 重点代码
#### henrytb 的代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,m;
int a[200005];
map<int,int> tim;
signed main() {
    for(scanf("%lld",&_);_;--_) {
        tim.clear();
        scanf("%lld%lld",&n,&m);
        int row=0,mx=0,mxid=0;
        rep(i,1,n) {
            scanf("%lld",&a[i]);
            row+=a[i];
            if(row>mx) mx=row,mxid=i,tim[mx]=i;
        }
        rep(i,1,m) {
            int x;
            scanf("%lld",&x);
            map<int,int>::iterator ii=tim.lower_bound(x);
            if(ii==tim.end()&&row<=0) {printf("-1 ");continue;}
            else if(ii==tim.end()){
                map<int,int>::iterator lst=tim.end();--lst;
                int ned=(x-lst->first+row-1)/row;
                ii=tim.lower_bound(x-ned*row);
                printf("%lld ",ii->second+ned*n-1);
            } else {
                printf("%lld ",ii->second-1);
            }
        }
        puts("");
    }
    return 0;
}
```
**核心实现思想**：先计算数组的前缀和，将一次循环中能到达的正数所需的最短时间存入 `map` 中。对于每个查询，先在 `map` 中查找第一轮能否到达目标值，若不能，根据数组一个周期的和是否大于 0 进行分类讨论，计算需要循环的次数，再在 `map` 中查找剩余目标值对应的位置。

#### 绝顶我为峰的代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int t,n,m,a[200001],sum[200001],maxn[200001];
signed main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld",&n,&m);
        maxn[0]=-1e18;
        sum[0]=0;
        for(register int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            sum[i]=sum[i-1]+a[i];
            maxn[i]=-1e18;
            maxn[i]=max(maxn[i-1],sum[i]);
        }
        while(m--)
        {
            int x;
            scanf("%lld",&x);
            if(maxn[n]>=x)
            {
                printf("%lld ",(long long)(lower_bound(maxn+1,maxn+n+1,x)-maxn-1));
                continue;
            }
            if(sum[n]<=0&&x>0)
            {
                printf("-1 ");
                continue;
            }
            int l=0,r=1e9,mid,ans=1e9;
            while(l<r)
            {
                mid=(l+r)>>1;
                if(mid*sum[n]+maxn[n]>=x)
                {
                    r=mid;
                    ans=mid;
                }
                else
                    l=mid+1;
            }
            printf("%lld ",(long long)(ans*n+(long long)(lower_bound(maxn+1,maxn+n+1,x-ans*sum[n])-maxn-1)));
        }
        puts("");
    }
    return 0;
}
```
**核心实现思想**：先计算数组的前缀和以及前缀和的最大值。对于每个查询，先判断第一轮能否到达目标值，若不能，且数组一个周期的和小于等于 0，则输出 -1；否则，通过二分圈数找到满足条件的最小圈数，再在 `maxn` 数组上二分查找剩余目标值对应的位置。

#### Special_Tony 的代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, m;
ll a[200005], sum, x, s;
int main () {
    ios::sync_with_stdio (0);
    cin.tie (0);
    cout.tie (0);
    cin >> t;
    while (t --) {
        cin >> n >> m;
        sum = 0;
        for (int i = 1; i <= n; ++ i)
            cin >> a[i], a[i] = max (a[i - 1], sum += a[i]);
        while (m --) {
            cin >> x;
            if (x <= a[n])
                s = 0;
            else if (sum > 0)
                s = (x - a[n] + sum - 1) / sum;
            else {
                cout << "-1 ";
                continue ;
            }
            x -= s * sum;
            cout << lower_bound (a + 1, a + 1 + n, x) - a - 1 + s * n << ' ';
        }
        cout << '\n';
    }
    return 0;
}
```
**核心实现思想**：先计算数组的前缀和的最大值。对于每个查询，先判断第一轮能否到达目标值，若不能，且数组一个周期的和小于等于 0，则输出 -1；否则，计算需要循环的次数，再在数组中二分查找剩余目标值对应的位置。

### 最优关键思路或技巧
- 计算前缀和以及前缀和的最大值，便于快速判断第一轮能否到达目标值。
- 利用二分查找来快速定位满足条件的位置，提高效率。
- 对数组一个周期的和进行分类讨论，判断是否能达到目标值。

### 拓展思路
同类型题或类似算法套路：
- 循环数组相关问题，如循环数组的最大子数组和等。
- 涉及多次循环累加并查找满足条件位置的问题，可以借鉴本题的前缀和与二分查找的思路。

### 推荐洛谷题目
- P1115 最大子段和
- P2671 [NOIP2015 普及组] 求和
- P1714 切蛋糕

### 个人心得摘录与总结
- **清烛**：赛时在处理 $s_i$ 不满足单调性，无法使用二分查找时卡住了。后来发现可以把不满足单调性的部分直接舍弃，取 $s_i$ 单调递增的部分进行二分查找。总结就是在遇到数组不满足单调性但需要二分查找的情况时，可以考虑舍弃不满足条件的部分，构造出单调的数组进行查找。 

---
处理用时：68.29秒