# 题目信息

# Watch the Videos

## 题目描述

Monocarp wants to watch $ n $ videos. Each video is only one minute long, but its size may be arbitrary. The $ i $ -th video has the size $ a_i $ megabytes. All videos are published on the Internet. A video should be downloaded before it can be watched. Monocarp has poor Internet connection — it takes exactly $ 1 $ minute to download $ 1 $ megabyte of data, so it will require $ a_i $ minutes to download the $ i $ -th video.

Monocarp's computer has a hard disk of $ m $ megabytes. The disk is used to store the downloaded videos. Once Monocarp starts the download of a video of size $ s $ , the $ s $ megabytes are immediately reserved on a hard disk. If there are less than $ s $ megabytes left, the download cannot be started until the required space is freed. Each single video can be stored on the hard disk, since $ a_i \le m $ for all $ i $ . Once the download is started, it cannot be interrupted. It is not allowed to run two or more downloads in parallel.

Once a video is fully downloaded to the hard disk, Monocarp can watch it. Watching each video takes exactly $ 1 $ minute and does not occupy the Internet connection, so Monocarp can start downloading another video while watching the current one.

When Monocarp finishes watching a video, he doesn't need it on the hard disk anymore, so he can delete the video, instantly freeing the space it occupied on a hard disk. Deleting a video takes negligible time.

Monocarp wants to watch all $ n $ videos as quickly as possible. The order of watching does not matter, since Monocarp needs to watch all of them anyway. Please calculate the minimum possible time required for that.

## 样例 #1

### 输入

```
5 6
1 2 3 4 5```

### 输出

```
16```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5```

### 输出

```
17```

## 样例 #3

### 输入

```
4 3
1 3 2 3```

### 输出

```
12```

# AI分析结果

### 题目内容中文重写
# 观看视频

## 题目描述
Monocarp 想要观看 $ n $ 个视频。每个视频时长仅 1 分钟，但其大小可以是任意的。第 $ i $ 个视频的大小为 $ a_i $ 兆字节。所有视频都发布在互联网上。视频必须先下载才能观看。Monocarp 的网络连接很差，下载 1 兆字节的数据恰好需要 1 分钟，因此下载第 $ i $ 个视频需要 $ a_i $ 分钟。

Monocarp 的电脑有一个容量为 $ m $ 兆字节的硬盘。硬盘用于存储下载的视频。一旦 Monocarp 开始下载一个大小为 $ s $ 的视频，硬盘上会立即预留 $ s $ 兆字节的空间。如果剩余空间小于 $ s $ 兆字节，则在释放所需空间之前无法开始下载。由于对于所有的 $ i $ 都有 $ a_i \le m $，因此每个单个视频都可以存储在硬盘上。一旦下载开始，就不能中断。不允许同时运行两个或更多的下载任务。

一旦视频完全下载到硬盘上，Monocarp 就可以观看它。观看每个视频恰好需要 1 分钟，并且不占用网络连接，因此 Monocarp 可以在观看当前视频的同时开始下载另一个视频。

当 Monocarp 看完一个视频后，他不再需要该视频存储在硬盘上，因此他可以立即删除该视频，瞬间释放其占用的硬盘空间。删除视频所需的时间可以忽略不计。

Monocarp 希望尽快观看所有 $ n $ 个视频。观看顺序无关紧要，因为无论如何他都需要观看所有视频。请计算完成此操作所需的最短时间。

## 样例 #1
### 输入
```
5 6
1 2 3 4 5
```
### 输出
```
16
```

## 样例 #2
### 输入
```
5 5
1 2 3 4 5
```
### 输出
```
17
```

## 样例 #3
### 输入
```
4 3
1 3 2 3
```
### 输出
```
12
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过合理安排视频的下载和观看顺序，利用观看视频时可同时下载其他视频的特性，来减少总时间消耗。大部分题解都先对视频大小进行排序，再使用双指针或其他方法寻找可同时进行下载和观看的视频对，以达到时间的优化。

各题解的思路和要点如下：
- **Alex_Wei**：先算出观看和下载所有视频的总时间，再通过排序和双指针找到可同时进行下载和观看的视频对，减少总时间。
- **hanjinghao**：证明了存在一种最优方案使硬盘中不超过两个视频，通过排序和分类讨论，模拟视频的下载和观看过程。
- **jiayixuan1205**：将问题转化为构造一种序列使相邻两项尽可能有重叠，对双指针算法进行改装，在不能匹配时跳过大数。
- **ybc2026lhy**：排序后从最大值开始考虑，根据最大值和最小值的和与硬盘容量的关系，使用双指针处理子问题。
- **qwq___qaq**：将问题等价为对视频重排，求相邻视频大小和不超过硬盘容量的数量，使用双端队列和大配小的思路。
- **aeiouaoeiu**：通过连边表示在观看一个视频时下载另一个视频，将视频转化为单向链，用 multiset 查找可连边的点。

### 所选题解
- **Alex_Wei（4星）**：
  - 关键亮点：思路清晰，直接指出节省时间的关键在于同时观看和下载，通过排序和双指针的方法高效解决问题，且提到了二分检查的思路，有一定的拓展性。
- **hanjinghao（4星）**：
  - 关键亮点：对最优方案进行了证明，使思路更严谨，通过分类讨论模拟视频的下载和观看过程，代码实现逻辑清晰。
- **jiayixuan1205（4星）**：
  - 关键亮点：对双指针算法进行了改装，解决了直接双指针扫描可能出现的问题，证明了当前策略的最优性，时间复杂度低。

### 重点代码
#### Alex_Wei（思路代码）
```plaintext
将 a 从小到大排序，假设有 k 对这样的 i，选择最小的 k + 1 个数构造 k + 1, 1, k, 2, ... 是最优的，它保证了相邻两个数之和的 max 最小。二分检查即可。简化二分过程，可以双指针做到除排序外 O(n)。
```
核心实现思想：先排序，再利用双指针寻找可同时进行下载和观看的视频对，减少总时间。

#### hanjinghao
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, a[N];
long long ans;

int main()
{
    // 输入部分省略
    if (n == 1)
    {
        writeln(a[1] + 1);
        return 0;
    }
    sort(a + 1, a + n + 1);
    int l = 1, r = n, cur = 0;
    while (1)
    {
        if (l > r) break;
        if (cur)
        {
            if (cur + a[r] <= m)
            {
                ans += a[r];
                cur = a[r];
                --r;
                continue;
            }
            if (cur + a[l] <= m)
            {
                ans += a[l];
                cur = a[l];
                ++l;
                continue;
            }
            ++ans;
            ans += a[r];
            cur = a[r];
            --r;
            continue;
        }
        ans += a[r];
        cur = a[r];
        --r;
    }
    if (cur) ++ans;
    writeln(ans);
    return 0;
}
```
核心实现思想：先排序，用三个变量表示已下载的视频范围和硬盘中当前视频的大小，通过分类讨论模拟视频的下载和观看过程。

#### jiayixuan1205
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5+10;
int n,m;
int a[N];
int ans=0,tot=0;
int last=0;

inline bool cmp(int x,int y)
{
    return x>y;
}

signed main()
{
    // 输入部分省略
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) ans+=a[i]+1;
    int l=1,r=n;
    while(l<r)
    {
        if(last==0)
        {
            if(a[l]+a[r]<=m)
            {
                l++;
                tot++;
                last=1;
            }
            else
            {
                l++;
            }
        }
        else
        {
            if(a[l]+a[r]<=m) 
            {
                r--;
                tot++;
                last=0;
            }
            else
            {
                l++;
            }
        }
    }
    cout<<ans-tot<<'\n';
    return 0;
}
```
核心实现思想：先排序，对双指针算法进行改装，在可以匹配时一大一小交叉匹配，不能匹配时跳过大数，最后用总时间减去重叠的时间。

### 最优关键思路或技巧
- 对视频大小进行排序，方便后续寻找可同时进行下载和观看的视频对。
- 使用双指针算法，高效地遍历视频序列，找到满足条件的视频对。
- 对双指针算法进行改装，解决直接双指针扫描可能出现的问题，保证策略的最优性。

### 拓展思路
同类型题可能会改变一些条件，如增加视频的属性（如优先级、截止时间等），或者改变硬盘的特性（如存在多个硬盘、硬盘有不同的读写速度等）。类似算法套路可以是在资源有限的情况下，通过合理安排任务顺序，使总时间或总代价最小，通常可以使用贪心算法，结合排序和双指针等方法解决。

### 推荐洛谷题目
1. P1803 凌乱的yyy / 线段覆盖
2. P2240 食草的奶牛
3. P1090 合并果子

### 个人心得
题解中未包含个人心得。

---
处理用时：54.09秒