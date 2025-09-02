# 题目信息

# River Locks

## 题目描述

Recently in Divanovo, a huge river locks system was built. There are now $ n $ locks, the $ i $ -th of them has the volume of $ v_i $ liters, so that it can contain any amount of water between $ 0 $ and $ v_i $ liters. Each lock has a pipe attached to it. When the pipe is open, $ 1 $ liter of water enters the lock every second.

The locks system is built in a way to immediately transfer all water exceeding the volume of the lock $ i $ to the lock $ i + 1 $ . If the lock $ i + 1 $ is also full, water will be transferred further. Water exceeding the volume of the last lock pours out to the river.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1700D/400a916b7267c9571228203513add48062776ecc.png)The picture illustrates $ 5 $ locks with two open pipes at locks $ 1 $ and $ 3 $ . Because locks $ 1 $ , $ 3 $ , and $ 4 $ are already filled, effectively the water goes to locks $ 2 $ and $ 5 $ .Note that the volume of the $ i $ -th lock may be greater than the volume of the $ i + 1 $ -th lock.

To make all locks work, you need to completely fill each one of them. The mayor of Divanovo is interested in $ q $ independent queries. For each query, suppose that initially all locks are empty and all pipes are closed. Then, some pipes are opened simultaneously. For the $ j $ -th query the mayor asks you to calculate the minimum number of pipes to open so that all locks are filled no later than after $ t_j $ seconds.

Please help the mayor to solve this tricky problem and answer his queries.

## 说明/提示

There are $ 6 $ queries in the first example test.

In the queries $ 1, 3, 4 $ the answer is $ -1 $ . We need to wait $ 4 $ seconds to fill the first lock even if we open all the pipes.

In the sixth query we can open pipes in locks $ 1 $ , $ 3 $ , and $ 4 $ . After $ 4 $ seconds the locks $ 1 $ and $ 4 $ are full. In the following $ 1 $ second $ 1 $ liter of water is transferred to the locks $ 2 $ and $ 5 $ . The lock $ 3 $ is filled by its own pipe.

Similarly, in the second query one can open pipes in locks $ 1 $ , $ 3 $ , and $ 4 $ .

In the fifth query one can open pipes $ 1, 2, 3, 4 $ .

## 样例 #1

### 输入

```
5
4 1 5 4 1
6
1
6
2
3
4
5```

### 输出

```
-1
3
-1
-1
4
3```

## 样例 #2

### 输入

```
5
4 4 4 4 4
6
1
3
6
5
2
4```

### 输出

```
-1
-1
4
4
-1
5```

# AI分析结果

### 题目内容翻译
## 河闸

### 题目描述
最近，在迪瓦诺沃建造了一个巨大的河闸系统。现在有 $n$ 个河闸，第 $i$ 个河闸的容积为 $v_i$ 升，因此它可以容纳 $0$ 到 $v_i$ 升之间的任意水量。每个河闸都连接着一根水管。当水管打开时，每秒有 $1$ 升水进入河闸。

河闸系统的设计方式是，一旦第 $i$ 个河闸的水量超过其容积，多余的水将立即转移到第 $i + 1$ 个河闸。如果第 $i + 1$ 个河闸也已满，水将继续向后转移。超过最后一个河闸容积的水将流入河中。

![此处插入图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1700D/400a916b7267c9571228203513add48062776ecc.png)
该图展示了 $5$ 个河闸，其中第 $1$ 个和第 $3$ 个河闸的水管处于打开状态。由于第 $1$、$3$ 和 $4$ 个河闸已经满了，实际上水会流向第 $2$ 个和第 $5$ 个河闸。
请注意，第 $i$ 个河闸的容积可能大于第 $i + 1$ 个河闸的容积。

为了使所有河闸正常工作，需要将每个河闸都完全填满。迪瓦诺沃市市长有 $q$ 个独立的询问。对于每个询问，假设最初所有河闸都是空的，所有水管都是关闭的。然后，同时打开一些水管。对于第 $j$ 个询问，市长要求你计算在不超过 $t_j$ 秒的时间内将所有河闸填满所需打开的最少水管数量。

请帮助市长解决这个棘手的问题并回答他的询问。

### 说明/提示
在第一个示例测试中有 $6$ 个询问。

在询问 $1$、$3$、$4$ 中，答案为 $-1$。即使打开所有水管，也需要等待 $4$ 秒才能填满第一个河闸。

在第六个询问中，我们可以打开第 $1$、$3$ 和 $4$ 个河闸的水管。$4$ 秒后，第 $1$ 个和第 $4$ 个河闸将被填满。在接下来的 $1$ 秒内，$1$ 升水将转移到第 $2$ 个和第 $5$ 个河闸。第 $3$ 个河闸由其自身的水管填满。

类似地，在第二个询问中，可以打开第 $1$、$3$ 和 $4$ 个河闸的水管。

在第五个询问中，可以打开第 $1$、$2$、$3$、$4$ 个河闸的水管。

### 样例 #1
#### 输入
```
5
4 1 5 4 1
6
1
6
2
3
4
5
```
#### 输出
```
-1
3
-1
-1
4
3
```

### 样例 #2
#### 输入
```
5
4 4 4 4 4
6
1
3
6
5
2
4
```
#### 输出
```
-1
-1
4
4
-1
5
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕计算在给定时间内填满所有河闸所需的最少水管数量展开。各题解的核心思路相近，先判断是否有解，再计算答案。判断无解的关键在于计算前 $i$ 个河闸在所有水管都打开的情况下的最短填满时间，若给定时间小于这个最短时间，则无解；有解时，答案为 $\lceil \frac {\sum v}{t} \rceil$。部分题解使用二分法优化求解过程。

### 所选题解
- **作者：dottle (赞：23)，4星**
    - **关键亮点**：思路清晰，先指出直接计算 $\lceil \frac {\sum v}{t} \rceil$ 可能存在的问题，然后通过计算前 $i$ 个河闸的最短填满时间得到 $t$ 的下界，逻辑严谨。代码简洁，实现了核心思路。
- **作者：lingfunny (赞：4)，4星**
    - **关键亮点**：从水龙头安装位置的角度分析，得出水龙头全装在前面几个水槽是最优构造，简化了问题。通过判断 $it<s_i$ 来确定无解情况，思路简洁明了。
- **作者：happy_dengziyue (赞：2)，4星**
    - **关键亮点**：通过视频题解辅助理解，思路清晰，先计算打开全部管道装满水所需的最短时间，不满足此条件的直接输出 $-1$，有解时输出 $\lceil\dfrac{s[n]}{t}\rceil$，易于理解和实现。

### 重点代码
#### dottle 的代码
```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1005000;
using namespace std;

int n,q,a[N];
int res;

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
    for(int i=1;i<=n;i++)res=max(res,(a[i]+i-1)/i);
    cin>>q;
    for(int i=1;i<=q;i++){
        int x;cin>>x;
        cout<<(x<res?-1:(a[n]+x-1)/x)<<'\n';
    }
}

main(){
    ios::sync_with_stdio(0);
    solve();
}
```
**核心实现思想**：先计算前缀和数组 `a`，再计算前 $i$ 个河闸的最短填满时间的最大值 `res`，对于每个询问，若给定时间 `x` 小于 `res`，则无解，否则输出 $\lceil \frac {a[n]}{x} \rceil$。

#### lingfunny 的代码
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 2e5+10;

int n, q, v[mxn];
LL s[mxn];
double MX;

signed main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", v+i), s[i] = s[i-1] + v[i];
    for(int i = 1; i <= n; ++i) MX = max(MX, (double)s[i]/i);
    scanf("%d", &q);
    while(q--) {
        int t; scanf("%d", &t);
        if(MX - t > 1e-7) { puts("-1"); continue; }
        printf("%lld\n", (t-1+s[n])/t);
    }
    return 0;
}
```
**核心实现思想**：计算前缀和数组 `s`，并计算 $\frac{s_i}{i}$ 的最大值 `MX`，对于每个询问，若给定时间 `t` 小于 `MX`，则无解，否则输出 $\lceil \frac {s[n]}{t} \rceil$。

#### happy_dengziyue 的代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
#define inf 2e15
int n;
int q;
long long a[max_n+2];
long long s[max_n+2];
long long need;//最少需要时间
int ans;
long long divll(long long x,long long y){
    return (x+y-1)/y;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%lld",a+i);
    s[0]=0;
    for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i];
    need=a[1];
    for(int i=2;i<=n;++i)need=max(need,divll(s[i],i));
    scanf("%d",&q);
    for(int i=1;i<=q;++i){
        long long x;
        scanf("%lld",&x);
        if(x<need)printf("-1\n");
        else printf("%lld\n",divll(s[n],x));
    }
    return 0;
}
```
**核心实现思想**：计算前缀和数组 `s`，并计算打开全部管道装满水所需的最短时间 `need`，对于每个询问，若给定时间 `x` 小于 `need`，则无解，否则输出 $\lceil \frac {s[n]}{x} \rceil$。

### 最优关键思路或技巧
- 发现水龙头放在前面的河闸是最优的，因为水满后会往后流，这样可以减少水的浪费。
- 通过计算前 $i$ 个河闸在所有水管都打开的情况下的最短填满时间，得到 $t$ 的下界，用于判断无解情况。

### 可拓展之处
同类型题目可能会改变河闸的连接方式、水管的进水速度等条件，但核心思路仍然是判断是否有解，再计算所需的最少资源。类似算法套路包括先分析问题的限制条件，找到关键的边界值，然后根据边界值进行判断和计算。

### 推荐题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径规划和数学计算，与本题的逻辑推理和计算有一定相似性。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：需要通过递推或动态规划计算最优解，锻炼逻辑思维和计算能力。
- [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)：经典的动态规划问题，与本题的思路分析和计算有一定的相似性。

### 个人心得摘录与总结
无明显个人心得内容。

---
处理用时：66.84秒