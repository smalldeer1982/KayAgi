# 题目信息

# [USACO20OPEN] Social Distancing II B

## 题目描述

由于高传染性的牛传染病 COWVID-19 的爆发，Farmer John 非常担忧他的奶牛们的健康。

尽管他尽了最大努力使他的 $N$ 头奶牛们（$1\le N\le 1000$）践行“社交距离”，还是有许多奶牛不幸染上了疾病。编号为 $1\ldots N$ 的奶牛们分别位于一条长直道路上的不同位置（相当于一维数轴），奶牛 $i$ 位于位置 $x_i$。Farmer John 知道存在一个半径 $R$，任何与一头被感染的奶牛距离不超过 $R$ 单位的奶牛也会被感染（然后会传染给与其距离 $R$ 单位内的奶牛，以此类推）。

不幸的是，Farmer John 并不确切知道 $R$ 的值。他只知道他的哪些奶牛被感染了。给定这个数据，求出起初感染疾病的奶牛的最小数量。 

## 说明/提示

### 样例解释 1

在这个例子中，我们知道 $R<3$，否则位于位置 $7$ 的奶牛会传染给位于位置 $10$ 的奶牛。所以，至少 $3$ 头奶牛初始时已被感染：位于位置 $1$ 和 $3$ 的两头奶牛中的一头，位于位置 $6$ 和 $7$ 的两头奶牛中的一头，以及位于位置 $15$ 的奶牛。 

## 样例 #1

### 输入

```
6
7 1
1 1
15 1
3 1
10 0
6 1```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
这些题解大多采用贪心算法解决问题，核心思路为：先对奶牛按位置排序，再根据健康奶牛与感染奶牛的位置关系确定感染半径 $R$ 的最大值，最后依据 $R$ 找出初始感染的最少奶牛数量。

各题解的算法要点和难点对比：
- **算法要点**：均包含排序、确定 $R$ 和统计初始感染奶牛数这三个关键步骤。确定 $R$ 时，通过比较健康奶牛与相邻感染奶牛的距离取最小值；统计初始感染奶牛数时，判断相邻感染奶牛的距离与 $R$ 的大小关系。
- **解决难点**：确定最大的 $R$ 值是关键，需考虑所有健康奶牛与相邻感染奶牛的距离。部分题解还需注意边界条件和特殊情况的处理。

### 高评分题解
1. **作者：Gilbert1206（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，注释详细，对贪心算法的实现步骤解释明确。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct health{
    int x;
    int y;
}a[1000];
int ans(health a,health b){
    return a.x<b.x;
}

int main() {
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y; 
    }
    sort(a+1,a+n+1,ans);
    int minn=10000000;
    for(int i=1;i<=n;i++){
        if(a[i].y==0){
            if(minn>a[i].x-a[i-1].x&&a[i-1].y!=0){
                minn=a[i].x-a[i-1].x;
            }
            if(minn>a[i+1].x-a[i].x&&a[i+1].y!=0){
                minn=a[i+1].x-a[i].x;
            }
        }
    }
    int abb=0;
    for(int i=1;i<=n;i++){
        if(a[i].y==1){
            if(a[i-1].y==1&&a[i].x-a[i-1].x<minn){
                continue;
            }
            abb++;
        }
    }
    cout<<abb;
    return 0;
}
```
    - **核心实现思想**：先对奶牛按位置排序，然后遍历找出健康奶牛与相邻感染奶牛的最小距离作为 $R$，最后再次遍历，若相邻感染奶牛距离小于 $R$ 则跳过，否则计数加一。

2. **作者：yangjinqian（4星）**
    - **关键亮点**：思路清晰，使用 `pair` 存储奶牛信息，代码简洁，对贪心过程的描述详细。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define f first
#define s second
#define pii pair<int, int>
using namespace std;
const int N = 1010;
int n, minn = 0x3f3f3f3f, ans;
pii a[N];
int flag[N];
bool cmp(pii c, pii d){
    return c.f < d.f;
}
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].f >> a[i].s;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 2; i < n; i++)
        if (!a[i].s){
            if (a[i - 1].s) minn = min(minn, a[i].f - a[i - 1].f);
            if (a[i + 1].s) minn = min(minn, a[i + 1].f - a[i].f);
        }
    for (int i = 1; i <= n; i++)
        if (a[i].s)
            if (!a[i - 1].s || a[i].f - a[i - 1].f >= minn)
                ans++;
    cout << ans;
    return 0;
}
```
    - **核心实现思想**：先对奶牛按位置排序，遍历找出 $R$ 的最大值，再遍历统计初始感染奶牛数，若当前奶牛感染且上一头未感染或距离大于等于 $R$，则计数加一。

3. **作者：dabenBbx（4星）**
    - **关键亮点**：思路清晰，对算法的关键步骤解释详细，代码结构清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,mind=1000006;
struct node{
    int d,z;
}a[1005];
bool cmp(node x,node y){
    return x.d<y.d;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].d>>a[i].z;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        if (a[i].z == 0)
        {
            if (i > 1 && a[i - 1].z == 1) 
                mind= min(mind, a[i].d - a[i - 1].d);
            if (i < n && a[i + 1].z == 1)
                mind = min(mind, a[i + 1].d - a[i].d);
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i].z==1){
            if(a[i-1].z==1&&a[i].d-a[i-1].d<mind)
                continue;
            ans++;
        } 
    }
    cout<<ans;
    return 0;
} 
```
    - **核心实现思想**：先对奶牛按位置排序，遍历找出 $R$ 的最大值，再遍历统计初始感染奶牛数，若相邻感染奶牛距离小于 $R$ 则跳过，否则计数加一。

### 最优关键思路与技巧
- **贪心策略**：要使初始感染奶牛数量最少，需让感染半径 $R$ 尽可能大。通过比较健康奶牛与相邻感染奶牛的距离确定 $R$ 的最大值。
- **排序处理**：对奶牛按位置排序，方便后续计算相邻奶牛的距离。

### 可拓展之处
同类型题或类似算法套路：
- 传染病传播范围问题：可改变传播规则，如二维平面上的传播，或传播有时间限制等。
- 区间覆盖问题：类似确定一个最大的覆盖半径，使覆盖的区间最少。

### 推荐题目
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
2. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)

### 个人心得
题解中未包含个人心得。

---
处理用时：39.44秒