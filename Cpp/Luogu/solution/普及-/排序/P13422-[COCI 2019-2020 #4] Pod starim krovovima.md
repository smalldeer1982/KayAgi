# [COCI 2019/2020 #4] Pod starim krovovima

## 题目描述

背景：传奇的萨格勒布小酒馆 Kod Žnidaršića。

时间：1936 年。

剧情简介：Franjo 和朋友们正在酒吧里一边喝酒一边讨论阿比西尼亚的时事。他的儿子，小 Perica，坐在酒吧角落的一张小桌子旁。在 Perica 面前，有 $N$ 个玻璃杯，编号为 $1$ 到 $N$。每个玻璃杯的容量（单位为纳升）已知，杯中当前的液体量也已知。

问题：小 Perica 想知道，通过在玻璃杯之间相互倒液体，最多能让多少个玻璃杯变空。他可以任意多次将任意整数纳升的液体从一个杯子倒到另一个杯子，只要没有液体溢出即可。

你的任务是输出最多能变空的玻璃杯数量，以及一种可能的所有玻璃杯中液体的分布方案。如果有多种分布方案能达到相同数量的空杯，输出任意一种即可。注意，不要求最小化倒液体的次数。


## 说明/提示

对第二个样例的说明：一种可能的倒液体方案如下：
1. 把第 1 个杯子的液体全部倒入第 2 个杯子。
2. 把第 2 个杯子的液体全部倒入第 4 个杯子。
3. 把第 3 个杯子的 4 纳升液体倒入第 4 个杯子，把第 3 个杯子的 1 纳升倒入第 5 个杯子。
此时，第 1、2、3 号杯子都为空。

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
5
2 6
1 6
0 6
6 6
5 6```

### 输出

```
2
6 6 2 0 0```

## 样例 #2

### 输入

```
5
4 5
2 7
5 5
0 10
7 9```

### 输出

```
3
0 0 0 10 8```

## 样例 #3

### 输入

```
8
2 6
3 4
1 1
9 10
0 10
4 5
6 8
3 9
```

### 输出

```
5
0 0 0 9 10 0 0 9```

# 题解

## 作者：bayiran (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13422)

## 题意
有 $N$ 个杯子，最大容量已知，每个杯子的装水量也已知，求经过任意多次没有水溢出的倒水操作后最多能有几个空杯子，并输出此时每个杯子的装水量。
## 分析
毕竟这是水，又不是[猫猫](https://www.luogu.com.cn/problem/P10483)（猫猫那么可爱，为什么要劈猫猫 qwq），而且没有次数限制，故把水的数量加起来看能装满几个杯子就行了。

考虑如何使剩余空杯子更多，显然应该尽量装满容量大的杯子来节省空间，故对杯子按容量进行排序。但是最后要求我们按给出的顺序输出，故考虑使用 `pair` 类型（结构体也可以）。

定义 `pair<int,int>` 来存储杯子的信息，其中第一关键字表示杯子容量，第二关键字表示杯子位置，定义 `cmp` 函数对第一关键字排序。

```cpp
bool cmp(pair<int,int> a,pair<int,int> b){
    return a.first > b.first;
}
```

排序后，模拟从容量最大的水杯开始倒水，倒满后找第二大的水杯，一直模拟直到水倒光为止。模拟同时记录倒满的杯子的数量 `k`，倒满就加一，注意输出时要把 `k` 再加一（因为现在倒的杯子虽然没倒满但不是空的）。

```cpp
long long sum = 0;
int k = 0;
for(k;k<n;k++) {
    sum += g[k].first;
    if (sum >= tot){
        break;
    }
}
k++;
cout<<n-k<<endl;
```

最后是输出每个杯子的装水量，为节省时间只遍历容量前 `k` 大的杯子，装水量是剩余水量与容量的较小值。在建立一个数组 `res` 按第二关键字存储装水量。

```cpp
int res[1024];
memset(res,0,sizeof(res));
for(int i=0;i<k;i++){
   int idx = g[i].second;
   int p = min(tot,(long long)g[i].first);
    res[idx] = p;
    tot -= p;
}
```

最后输出即可。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int,int> a,pair<int,int> b){
    return a.first > b.first;
}
int main() {
    int n;
    cin>>n;
    pair<int,int> g[1024];
    int c[1024];
    long long int tot = 0;
    for(int i=0;i<n;i++){
        cin>>c[i]>>g[i].first;
        g[i].second = i;
        tot += c[i];
    }
    sort(g,g+n,cmp);
    long long sum = 0;
    int k = 0;
    for(k;k<n;k++) {
        sum += g[k].first;
        if (sum >= tot){
            break;
        }
    }
    k++;
    cout<<n-k<<endl;
    int res[1024];
    memset(res,0,sizeof(res));
    for(int i=0;i<k;i++){
        int idx = g[i].second;
        int p = min(tot,(long long)g[i].first);
        res[idx] = p;
        tot -= p;
    }
    for(int i=0;i<n;i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：lczhouzihao (赞：1)

我的做法是**贪心**。

题目让我们输出最多能变空的玻璃杯数量，其实可以用答案数组计算。

原理很简单，算出全部液体量，接着将容器的容量从大到小排序，算出按最优策略下容器里的液体量，记到答案数组即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
    int t,z,ii;
}a[1005];
bool cmp(node x,node y){
    return x.z>y.z;
}
int x[1005];
int main(){
    cin>>n;
    long long sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i].t>>a[i].z;
        a[i].ii=i;
        sum+=a[i].t;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n&&sum;i++){
        if(sum>=a[i].z){
            sum-=a[i].z;
            x[a[i].ii]=a[i].z;
        }
        else{
            x[a[i].ii]=sum;
            sum=0;
        }
    }
    int k=0;
    for(int i=1;i<=n;i++){
        if(x[i]==0)k++;
    }
    cout<<k<<endl;
    for(int i=1;i<=n;i++){
        cout<<x[i]<<" ";
    }
    return 0;
}
```

~不喜勿喷~

---

## 作者：Doraeman (赞：1)

简单贪心题。

## 思路
为了使空杯子更多，要尽可能**将酒**（就假设小 Perica 在倒酒）**都放进更少的杯子里**。  
如果酒的总量不变，想用更少的杯子装酒，就要**使用容量更大的杯子**。

由于**不限制倒酒的次数**，所以**不妨假设把所有酒都“拿出来”**，最后再统一装进各个杯子中，不影响整体实现效果。

所以，**按照容量从大到小**对所有杯子**排序**。然后将酒依次放入杯子中，直到所有酒都被放进杯子里。

最后，计算各个杯子里的酒并输出。

## 细节
### 求特殊值
假设有整体处理酒之后有 $M$ 个杯子不空，那么**前 $(M-1)$ 个杯子一定都是满的**（否则第 $M$ 个杯子就不会有酒了），直接输出它们的**杯子容量**即可。

但是，第 $M$ 个杯子并不一定是满的，怎么计算它的液体量呢？

可以先用 $sum_1$ 统计所有 $N$ 个杯子的液体量，再用 $sum_2$ 统计排序后前 $M-1$ 个杯子的总容量（也即倒酒后前 $M-1$ 个杯子里的总液体量），到第 $M$ 个杯子时还剩下 $(sum_1-sum_2)$ 纳升酒。

### 输出答案
建议输入时使用结构体，并用 $id$ 记录输入顺序。  
因为最后输出答案时要求按照杯子的输入顺序输出液体量，所以输出前还要进行排序，按照 $id$ 从小到大排序。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
typedef long long LL;

int n, t;
struct Glass{
    int id, z, rest = 0;
}a[N];
LL sum1, sum2, cnt;

// 两种排序方式 
bool cmp1(Glass x, Glass y){
    return x.z > y.z;
}
bool cmp2(Glass x, Glass y){
    return x.id < y.id;
}

int main(){
    cin >> n;
    for(int i=1; i<=n; i++){
        cin >> t >> a[i].z;
        sum1 += t; a[i].id = i;
    }
    sort(a + 1, a + n + 1, cmp1);

    int m = 0; // 求M 
    for(int i=1; i<=n; i++){
        cnt += a[i].z, m++;
        if(cnt >= sum1) break;
    }

    // 更新液体量, 求sum2 
    for(int i=1; i<m; i++)
        a[i].rest = a[i].z,
        sum2 += a[i].rest;
    a[m].rest = sum1 - sum2;

    sort(a + 1, a + n + 1, cmp2);

    cout << n - m << '\n';
    for(int i=1; i<=n; i++)
        cout << a[i].rest << ' ';
}
```

---

## 作者：b__b (赞：1)

简单贪心。

因为我们可以任意调节杯子里面的水（只要没有液体溢出即可），因此问题转换为用最少的杯子装满所有的水。

于是我们直接贪心即可。按照杯子的体积从大到小排序，从头开始遍历直到当前的杯子总体积大于水的总体积，最后还原杯子的顺序即可。

注意：$1 \leq N \leq 1\,000$，$0 \leq T_i \leq 10^9$，$1 \leq Z_i \leq 10^9$。因此我们需要开 long long。

代码：
```cpp
#include <cstdio>
#include <algorithm>
int tmp[1005];
struct p {int t, z, ind; bool operator<(const p &b) const {return z > b.z;}} bottle[1005];
typedef long long ll;
int main() {
    int N;
    scanf("%d", &N);
    ll all = 0; //存储水的总体积
    for (int i = 0; i < N; ++i)
        scanf("%d%d", &bottle[i].t, &bottle[i].z), bottle[i].ind = i, all += bottle[i].t;
    std::sort(bottle, bottle + N);
    int i = 0;
    for (ll sum = 0; sum < all; ++i) bottle[i].t = std::min((ll) bottle[i].z, all - sum), sum += bottle[i].z;
    printf("%d\n", N - i); //这时i是需要的杯子的编号+1，因为杯子编号从0开始，因此其实就是需要的杯子的数量
    //这里还原有水的杯子
    for (int j = 0; j < i; ++j) tmp[bottle[j].ind] = bottle[j].t;
    //还原有水的杯子后剩下的都是没有水的杯子
    for (int j = i; j < N; ++j) tmp[bottle[j].ind] = 0;
    for (int j = 0; j < N; ++j) printf("%d ", tmp[j]);
}
```

---

## 作者：Objective (赞：0)

## 思路与算法

### 思路

由于这道题我们需要尽可能的使用剩余的杯子多，所以反过来看，就是使的使用了的杯子尽量少。我们不难看出，由于杯子数量是一定的，我们只需要使得大杯子装的更多就可以了。

于是，不难想出，我们需要用到排序。但是，我们怎么知道每个杯子有多少酒，同时，我们怎么知道每个杯子应该在哪个位置呢？

这里，就有结构体的好处了。我们定义一个结构体，使得它能存下一个酒杯中现在的酒量，酒杯的最大容积，以及它输入时的序号。这时候，我们只要从小到大依照它输入时的序号排序即可。

由于最开始的酒量并不重要，于是我们可以将总的酒量单独存在变量 $sum$ 中，在计算时方便进行分配。

不过不要忘了，使用 `sort()` 函数排序时，需要自己写比较函数哦！

## 代码

```cpp
#include <bits/stdc++.h>
#define file(s) \
    std::freopen(#s".in", "r", stdin), std::freopen(#s".out", "w", stdout)

// 科普一下：缩写
using i64 = long long;
using ull = unsigned long long;
using f32 = double;
using ldb = long double;

inline int read() {
    register int x = 0, sign = 1;
    register char ch = getchar_unlocked();
    for (; !isdigit(ch); ch = getchar_unlocked()) {
        if (ch == '-') {    
            sign = -1;
        }
        if (ch == EOF) {
            return EOF;
        }
    }
    for (; isdigit(ch); ch = getchar_unlocked()) {
        x = x * 10 + ch - '0';
    }
    return x * sign;
}

constexpr int N = 1e3 + 5;

// 定义的结构体
struct cup{
    // 现在杯子中有的酒量、杯子容积、被子序号
    int wine, size, id;
}c[N];
bool sz_cmp(cup a, cup b) {
    return a.size > b.size;
}
bool id_cmp(cup a, cup b) {
    return a.id < b.id;
}

int n;
i64 sum = 0;

int main() {
    n = read();
    for (int i = 1; i <= n; i++) {
        int t = read(), z = read();
        sum += t;
        c[i] = (cup){0, z, i};
    }
    std::sort(c+1, c + 1 + n, sz_cmp);
    int i = 1;
    while (sum > 0) {
        if (c[i].size <= sum) {
            sum -= c[i].size;
            c[i].wine = c[i].size;
        } else {
            c[i].wine = sum;
            sum = 0;
        }
        i++;
    }
    std::sort(c + 1, c + 1 + n, id_cmp);
    printf("%d\n", n - (i - 1));
    for (i = 1; i <= n; i++) {
        printf("%d ", c[i].wine);
    }
    return 0;
}
```

代码中的一些小注意点：

- 因为我的下标是从 $1$ 开始存的，所以我在 `while()` 循环中用的也是从 $1$ 开始；

- 如果剩余的酒不能填满杯子时，我们在这个杯子里装下剩余的酒；


- 由于我们需要输出的第一个数据是剩余的杯子数量，由于我们的 $i$ 的值是使用了的杯子的数量加 $1$（原来就是 $1$，每次使用加了 $1$），所以我们最终要返回去，输出总杯子数减去已使用的杯子数（`n - (i - 1)`）。

---

## 作者：lcliruiyan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13422)

## 题目大意
有 $N$ 个玻璃杯，每个杯子有当前液体量 $T_i$ 和容量 $Z_i$。通过在杯子间倒液体（每次可倒任意整数升，但是不能溢出），问最多能让多少个杯子变空，并输出一种可行的最终液体分布方案。

## 题目思路

想要让空杯子的数量尽量多，就要让尽可能多的液体聚集到尽可能少的杯子里。我们可以用贪心算法做这道题。

首先，我们按杯子的容量对杯子进行排序。

然后，依次选择未选的杯子中容量最大的杯子，直到所有液体都可以被装进已选的杯子中，剩下的杯子就是最终可以变空的杯子。

最后，将液体按杯子容量从大到小倒进杯子里，输出即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long s=0,sum,r,res[1005];
struct G
{
    int i;
    long long t,z;
}g[1005];
bool cmp(G a,G b)
{
    return a.z>b.z;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        g[i].i=i;
        cin>>g[i].t>>g[i].z;
        s+=g[i].t;
    }
    sort(g+1,g+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        if(sum+g[i].z>=s)
        {
            k=i;
            break;
        }
        sum+=g[i].z;
    }
    r=s;
    for(int i=1;i<=k;i++)
    {
        long long p=min(r,g[i].z);
        res[g[i].i]=p;
        r-=p;
    }
    cout<<n-k<<endl;
    for(int i=1;i<=n;i++)
        cout<<res[i]<<" ";
    return 0;
}
```
注意：杯子的容量和编号要使用结构体存储，因为最后要按输入顺序输出。

---

