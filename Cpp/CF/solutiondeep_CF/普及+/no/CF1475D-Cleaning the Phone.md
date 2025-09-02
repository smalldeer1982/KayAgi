# 题目信息

# Cleaning the Phone

## 题目描述

Polycarp often uses his smartphone. He has already installed $ n $ applications on it. Application with number $ i $ takes up $ a_i $ units of memory.

Polycarp wants to free at least $ m $ units of memory (by removing some applications).

Of course, some applications are more important to Polycarp than others. He came up with the following scoring system — he assigned an integer $ b_i $ to each application:

- $ b_i = 1 $ — regular application;
- $ b_i = 2 $ — important application.

According to this rating system, his phone has $ b_1 + b_2 + \ldots + b_n $ convenience points.

Polycarp believes that if he removes applications with numbers $ i_1, i_2, \ldots, i_k $ , then he will free $ a_{i_1} + a_{i_2} + \ldots + a_{i_k} $ units of memory and lose $ b_{i_1} + b_{i_2} + \ldots + b_{i_k} $ convenience points.

For example, if $ n=5 $ , $ m=7 $ , $ a=[5, 3, 2, 1, 4] $ , $ b=[2, 1, 1, 2, 1] $ , then Polycarp can uninstall the following application sets (not all options are listed below):

- applications with numbers $ 1, 4 $ and $ 5 $ . In this case, it will free $ a_1+a_4+a_5=10 $ units of memory and lose $ b_1+b_4+b_5=5 $ convenience points;
- applications with numbers $ 1 $ and $ 3 $ . In this case, it will free $ a_1+a_3=7 $ units of memory and lose $ b_1+b_3=3 $ convenience points.
- applications with numbers $ 2 $ and $ 5 $ . In this case, it will free $ a_2+a_5=7 $ memory units and lose $ b_2+b_5=2 $ convenience points.

Help Polycarp, choose a set of applications, such that if removing them will free at least $ m $ units of memory and lose the minimum number of convenience points, or indicate that such a set does not exist.

## 说明/提示

In the first test case, it is optimal to remove applications with numbers $ 2 $ and $ 5 $ , freeing $ 7 $ units of memory. $ b_2+b_5=2 $ .

In the second test case, by removing the only application, Polycarp will be able to clear only $ 2 $ of memory units out of the $ 3 $ needed.

In the third test case, it is optimal to remove applications with numbers $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , freeing $ 10 $ units of memory. $ b_1+b_2+b_3+b_4=6 $ .

In the fourth test case, it is optimal to remove applications with numbers $ 1 $ , $ 3 $ and $ 4 $ , freeing $ 12 $ units of memory. $ b_1+b_3+b_4=4 $ .

In the fifth test case, it is optimal to remove applications with numbers $ 1 $ and $ 2 $ , freeing $ 5 $ units of memory. $ b_1+b_2=3 $ .

## 样例 #1

### 输入

```
5
5 7
5 3 2 1 4
2 1 1 2 1
1 3
2
1
5 10
2 3 2 3 2
1 2 1 2 1
4 10
5 1 3 4
1 2 1 2
4 5
3 2 1 2
2 1 2 1```

### 输出

```
2
-1
6
4
3```

# AI分析结果

### 题目内容中文重写
# 清理手机

## 题目描述
Polycarp 经常使用他的智能手机。他已经在上面安装了 $n$ 个应用程序。编号为 $i$ 的应用程序占用 $a_i$ 单位的内存。

Polycarp 想至少释放 $m$ 单位的内存（通过删除一些应用程序）。

当然，有些应用程序对 Polycarp 来说比其他应用程序更重要。他想出了以下评分系统 —— 他为每个应用程序分配了一个整数 $b_i$：
- $b_i = 1$ —— 普通应用程序；
- $b_i = 2$ —— 重要应用程序。

根据这个评分系统，他的手机有 $b_1 + b_2 + \ldots + b_n$ 个便利点。

Polycarp 认为，如果他删除编号为 $i_1, i_2, \ldots, i_k$ 的应用程序，那么他将释放 $a_{i_1} + a_{i_2} + \ldots + a_{i_k}$ 单位的内存，并损失 $b_{i_1} + b_{i_2} + \ldots + b_{i_k}$ 个便利点。

例如，如果 $n = 5$，$m = 7$，$a = [5, 3, 2, 1, 4]$，$b = [2, 1, 1, 2, 1]$，那么 Polycarp 可以卸载以下应用程序集（并非所有选项都列在下面）：
- 编号为 $1$、$4$ 和 $5$ 的应用程序。在这种情况下，它将释放 $a_1 + a_4 + a_5 = 10$ 单位的内存，并损失 $b_1 + b_4 + b_5 = 5$ 个便利点；
- 编号为 $1$ 和 $3$ 的应用程序。在这种情况下，它将释放 $a_1 + a_3 = 7$ 单位的内存，并损失 $b_1 + b_3 = 3$ 个便利点。
- 编号为 $2$ 和 $5$ 的应用程序。在这种情况下，它将释放 $a_2 + a_5 = 7$ 单位的内存，并损失 $b_2 + b_5 = 2$ 个便利点。

帮助 Polycarp 选择一组应用程序，使得删除它们后至少释放 $m$ 单位的内存，并且损失的便利点最少，或者表明这样的集合不存在。

## 说明/提示
在第一个测试用例中，最优的做法是删除编号为 $2$ 和 $5$ 的应用程序，释放 $7$ 单位的内存。$b_2 + b_5 = 2$。

在第二个测试用例中，通过删除唯一的应用程序，Polycarp 只能清理 $2$ 单位的内存，而需要清理 $3$ 单位。

在第三个测试用例中，最优的做法是删除编号为 $1$、$2$、$3$ 和 $4$ 的应用程序，释放 $10$ 单位的内存。$b_1 + b_2 + b_3 + b_4 = 6$。

在第四个测试用例中，最优的做法是删除编号为 $1$、$3$ 和 $4$ 的应用程序，释放 $12$ 单位的内存。$b_1 + b_3 + b_4 = 4$。

在第五个测试用例中，最优的做法是删除编号为 $1$ 和 $2$ 的应用程序，释放 $5$ 单位的内存。$b_1 + b_2 = 3$。

## 样例 #1
### 输入
```
5
5 7
5 3 2 1 4
2 1 1 2 1
1 3
2
1
5 10
2 3 2 3 2
1 2 1 2 1
4 10
5 1 3 4
1 2 1 2
4 5
3 2 1 2
2 1 2 1
```
### 输出
```
2
-1
6
4
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是利用 $b_i$ 只能取 $1$ 或 $2$ 这个特殊条件，将应用按 $b_i$ 的值分为两类，再结合贪心和排序的思想来解决问题。
- **思路对比**：部分题解采用直接贪心选择的策略，每次比较两个 $b_i = 1$ 的应用和一个 $b_i = 2$ 的应用的价值，选择价值大的；另一些题解则是枚举使用 $b_i = 1$ 的应用的数量，再通过二分查找确定使用 $b_i = 2$ 的应用的最小数量。
- **算法要点**：所有题解都对两类应用按价值从大到小排序，以保证优先选择价值大的应用。直接贪心的题解在循环中不断比较并选择；枚举 + 二分的题解则通过前缀和数组来快速计算价值总和。
- **解决难点**：主要难点在于如何在满足释放内存要求的前提下，使损失的便利点最少。通过分类、排序和贪心策略，有效地解决了这个问题。

### 所选题解
- **作者：jianhe (赞：3)，4星**
  - **关键亮点**：思路清晰，代码简洁，详细解释了贪心的过程，提醒了多测清空的重要性。
  - **个人心得**：做题前要好好看数据范围，先判断自己的算法时间复杂度对不对，再写代码，否则容易出错。
- **作者：Cutest_Junior (赞：3)，4星**
  - **关键亮点**：对贪心策略的证明和解释较为详细，逻辑严谨。
  - **个人心得**：考场上没有想出这么显然的贪心策略，说明还需要加强练习。
- **作者：Carotrl (赞：2)，4星**
  - **关键亮点**：结合了枚举和二分的思想，通过前缀和数组优化计算，代码实现较为规范。

### 重点代码
#### 作者：jianhe
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10;
ll T,n,m,a[N],b,t1,t2,q1[N],q2[N],ct,ans,h1,h2;
bool cmp(ll l,ll r){
    return l>r;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i];
        t1=t2=ct=ans=0,h1=h2=1;
        for(int i=1;i<=n;i++){
            cin>>b;
            if(b==1) q1[++t1]=a[i];
            else q2[++t2]=a[i];
        }
        sort(q1+1,q1+t1+1,cmp);
        sort(q2+1,q2+t2+1,cmp);
        while(ct<m){//贪心取最大值
            if(!q1[h1]&&!q2[h2]){ans=-1;break;}//q1和q2都取完了,总价值还没达到m
            if(ct+q1[h1]>=m){ans++;break;}//取q1[h1]后达到
            if(q1[h1]+q1[h1+1]>=q2[h2]) ct+=q1[h1++],ans++;//取q1
            else ct+=q2[h2++],ans+=2;//取q2
        }
        cout<<ans<<"\n";
        for(int i=1;i<=n;i++) q1[i]=q2[i]=0;
    }
    return 0;
}
```
**核心实现思想**：先将应用按 $b_i$ 的值分为两类，分别存储在 `q1` 和 `q2` 数组中，然后对这两个数组按价值从大到小排序。在循环中，不断比较两个 $b_i = 1$ 的应用和一个 $b_i = 2$ 的应用的价值，选择价值大的，直到释放的内存达到要求或无法继续选择。

#### 作者：Cutest_Junior
```cpp
#include <cstdio>
#include <iterator>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
const int N = 2e5 + 5;
 
int arr[N];
int que1[N], tot1;
int que2[N], tot2;
 
void run() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        if (x == 1) {
            que1[tot1] = arr[i];
            ++tot1;
        }
        else {
            que2[tot2] = arr[i];
            ++tot2;
        }
    }
    sort(que1, que1 + tot1, greater<int>());
    sort(que2, que2 + tot2, greater<int>());
    int cnt1 = 0, cnt2 = 0;
    int h1 = 0, h2 = 0;
    while (cnt1 < m) {
        if (que1[h1] == 0 && que2[h2] == 0) {
            cnt2 = -1;
            break;
        }
        if (cnt1 + que1[h1] >= m) {
            ++cnt2;
            break;
        }
        if (que2[h2] >= que1[h1] + que1[h1 + 1]) {
            cnt1 += que2[h2];
            cnt2 += 2;
            ++h2;
        }
        else {
            cnt1 += que1[h1];
            ++cnt2;
            ++h1;
        }
    }
    printf("%d\n", cnt2);
    tot1 = 0, tot2 = 0;
    memset(que1, 0, sizeof que1);
    memset(que2, 0, sizeof que2);
}
 
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        run();
    }
}
```
**核心实现思想**：与上一个题解类似，先分类、排序，然后在循环中比较并选择，直到满足条件或无法继续选择。

#### 作者：Carotrl
```cpp
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;
struct P{
    int x,v;
}q1[200005],q2[200005];
bool cmp(P p,P q){
    return p.v>q.v;
}
void in(int &x){
    int f=1;x=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-')c=getchar();
    if(c=='-')f=-1,c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    x*=f;
}
void out(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)out(x/10);
    putchar(x%10+'0');
}
long long sum1[200005],sum2[200005];
int t,n,m,x,v,n1,n2,a[200005],b[200005];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        n1=0;n2=0;
        for(int i=1;i<=n;i++)in(a[i]);
        for(int i=1;i<=n;i++)in(b[i]);
        for(int i=1;i<=n;i++){
            if(b[i]==1)q1[++n1].v=a[i],q1[n1].x=1;
            else q2[++n2].v=a[i],q2[n2].x=2;
        }
        sort(q1+1,q1+n1+1,cmp);
        sort(q2+1,q2+n2+1,cmp);
        sum1[0]=0;sum2[0]=0; 
        for(int i=1;i<=n1;i++)sum1[i]=sum1[i-1]+q1[i].v;
        for(int i=1;i<=n2;i++)sum2[i]=sum2[i-1]+q2[i].v;
        if(sum1[n1]+sum2[n2]<m){
            puts("-1");continue;
        }
        long long ans=0x3f3f3f3f;
        for(int i=0;i<=n1;i++){
            long long sum=i; 
            long long now=m-sum1[i];
            int k=0;
            if(now>0){
                k=lower_bound(sum2+1,sum2+1+n2,now)-sum2;
                if(k>n2)continue;
            }
            sum+=k*2;
            ans=min(ans,sum);
        }
        if(ans==0x3f3f3f3f)printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：先分类、排序，然后计算前缀和数组 `sum1` 和 `sum2`。枚举使用 $b_i = 1$ 的应用的数量，通过前缀和数组快速计算已释放的内存，再用二分查找在 `sum2` 数组中找到满足剩余内存需求的最小位置，更新最小损失的便利点。

### 最优关键思路或技巧
- **分类存储**：将应用按 $b_i$ 的值分为两类，便于后续处理。
- **排序**：对两类应用按价值从大到小排序，保证优先选择价值大的应用。
- **贪心策略**：比较两个 $b_i = 1$ 的应用和一个 $b_i = 2$ 的应用的价值，选择价值大的，以达到损失便利点最少的目的。
- **前缀和与二分**：通过前缀和数组快速计算价值总和，结合二分查找确定使用 $b_i = 2$ 的应用的最小数量，优化时间复杂度。

### 可拓展之处
同类型题可能会有不同的价值和重量限制，或者有更多的分类情况。类似的算法套路可以应用于资源分配、物品选择等问题，关键在于根据题目条件找到合适的贪心策略或优化方法。

### 推荐洛谷题目
- P1223 排队接水（https://www.luogu.com.cn/problem/P1223）
- P1094 纪念品分组（https://www.luogu.com.cn/problem/P1094）
- P2240 部分背包问题（https://www.luogu.com.cn/problem/P2240）

### 个人心得总结
- 做题前要仔细看数据范围，判断算法的时间复杂度是否可行，避免走弯路。
- 对于有特殊条件的题目，要善于从特殊条件入手，寻找解题的突破口。
- 考场上要冷静思考，加强对贪心等算法的练习，提高解题能力。

---
处理用时：105.81秒