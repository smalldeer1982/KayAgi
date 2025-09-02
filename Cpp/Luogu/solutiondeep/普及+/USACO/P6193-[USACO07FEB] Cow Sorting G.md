# 题目信息

# [USACO07FEB] Cow Sorting G

## 题目描述

Farmer John 的 $n$（$1 \leq n \leq 10^5$）头牛一字排开。每头奶牛都有一个“脾气暴躁”水平，范围在 $1 \ldots 10^5$，且任意两头奶牛的脾气暴躁值不相同。由于脾气暴躁的奶牛更有可能损坏 FJ 的挤奶设备，因此 FJ 希望对奶牛进行重新排序，以便按照脾气暴躁程度依此提升的顺序排列它们。

在此过程中，任何两头奶牛（不一定相邻）的位置都可以互换。由于脾气暴躁的母牛难以移动，因此 FJ 总共需要 $X + Y$ 单位的时间来交换两只脾气暴躁程度为 $X$ 和 $Y$ 的母牛。请帮助 FJ 计算将奶牛按脾气暴躁程度的升序排序所需的最短时间。

## 样例 #1

### 输入

```
3 
2 
3 
1```

### 输出

```
7```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是基于置换的概念，将奶牛的排序问题转化为置换的循环节问题。对于每个循环节，考虑两种交换策略：一是仅在循环节内部，用循环节内最小代价的牛进行交换；二是当循环节内最小代价的牛代价过大时，借助整个数列中最小代价的牛进行交换，最后取两种策略的最小值累加得到总最小时间。

### 所选题解
- **作者：Purslane (赞：1) 4星**
    - **关键亮点**：思路清晰，代码简洁规范，使用了常见的宏定义和循环结构，便于理解和实现。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+20;
int n,val=INT_MAX,a[MAXN],b[MAXN],p[MAXN],vis[MAXN],ans;
signed main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;ffor(i,1,n) cin>>a[i];val=*min_element(a+1,a+n+1);
    ffor(i,1,n) b[i]=a[i];sort(b+1,b+n+1);
    ffor(i,1,n) p[i]=lower_bound(b+1,b+n+1,a[i])-b;
    ffor(i,1,n) if(!vis[i]) {
        int tot=0,sum=0,MN=INT_MAX,u=i;
        do {vis[u]=1,tot+=a[u],sum++,MN=min(MN,a[u]),u=p[u];}while(u!=i);
        int meth1=tot+(sum-2)*MN,meth2=(tot-MN+val)+(sum-2)*val+2*(MN+val);
        ans+=min(meth1,meth2);
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：先读取输入，找到整个数列的最小值`val`，对数组排序得到目标顺序，通过`lower_bound`找到每个元素在目标顺序中的位置。然后遍历每个未访问的元素，找出循环节，计算循环节内元素的总和`tot`、元素个数`sum`和最小值`MN`，分别计算两种交换策略的代价`meth1`和`meth2`，取最小值累加到`ans`中。

- **作者：crescentic (赞：1) 4星**
    - **关键亮点**：思路阐述详细，代码结构清晰，使用`vector`存储每个循环节的元素，便于处理。
    - **核心代码**：
```cpp
#include<cstdio>
#include<vector> 
#include<algorithm>
using namespace std;
#define ll long long
const int N = 1e5 + 5, inf = 1e5;
int n,a[N],b[N],id[N],bel[N],tot,mi,sz;
ll ans;
vector<int> G[N];
int main() {
    scanf("%d",&n);
    for(int i = 1; i <= n; i ++) scanf("%d",&a[i]), b[i] = a[i];
    sort(b + 1,b + 1 + n);
    for(int i = 1; i <= n; i ++) id[b[i]] = i;
    int node,nex;
    for(int i = 1; i <= n; i ++) {
        node = id[a[i]];
        if(bel[node]) continue;
        nex = id[a[node]], bel[node] = ++tot;
        while(nex != node) {
            bel[nex] = tot;
            nex = id[a[nex]];
        }
    }
    for(int i = 1; i <= n; i ++) G[bel[id[a[i]]]].push_back(a[i]);
    for(int i = 1; i <= tot; i ++) {
        mi = inf, sz = G[i].size();
        for(int j = 0; j < sz; j ++) {
            ans += G[i][j], mi = min(mi,G[i][j]);
        }
        ans -= mi, ans += min((sz - 1) * mi,b[1] * (sz + 1) + mi * 2); 
    }
    printf("%lld",ans);
    return 0;
}
```
**核心实现思想**：先读取输入并排序，通过`id`数组记录每个元素在排序后的位置。然后找出所有循环节，用`bel`数组标记元素所属的循环节。将每个循环节的元素存储在`vector`中，遍历每个循环节，计算元素总和和最小值，分别计算两种交换策略的代价并取最小值累加到`ans`中。

- **作者：zdy111111 (赞：0) 4星**
    - **关键亮点**：代码简洁，思路清晰，通过`id`数组和`nt`数组建图，方便处理循环节。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],id[100005],nt[100005];
long long ans;
bool vis[100005];
bool cmp(int x,int y){return a[x]<a[y];}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),id[i]=i;
    sort(id+1,id+1+n,cmp);
    long long Min1=a[id[1]];
    for(int i=1;i<=n;i++) nt[id[i]]=i;
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        int p=i;
        long long Min2=(long long)1<<62,cnt=0,sum=0;
        do{
            cnt++;sum+=a[p];
            Min2=min(Min2,(long long)a[p]);
            vis[p]=1;p=nt[p];
        }while(p!=i);
        ans+=min((cnt-2)*Min2+sum,(cnt+1)*Min1+sum+Min2);
    }
    printf("%lld\n",ans);
    return 0;
} 
```
**核心实现思想**：先读取输入，对`id`数组按照暴躁程度排序，找到全局最小值`Min1`，通过`nt`数组建图。然后遍历每个未访问的元素，找出循环节，计算循环节内元素的总和`sum`、元素个数`cnt`和最小值`Min2`，分别计算两种交换策略的代价并取最小值累加到`ans`中。

### 最优关键思路或技巧
- **置换与循环节**：将奶牛的排序问题转化为置换的循环节问题，每个循环节内的元素相互交换，不同循环节之间独立。
- **贪心策略**：对于每个循环节，考虑两种交换策略，取最小值，即仅在循环节内部用最小代价的牛交换和借助全局最小代价的牛交换。

### 可拓展之处
同类型题或类似算法套路：涉及置换、循环节和贪心策略的排序优化问题，如一些排列调整的最小代价问题。

### 推荐题目
- [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)
- [P2827 蚯蚓](https://www.luogu.com.cn/problem/P2827)
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)

### 个人心得
这些题解中未包含个人心得（调试经历、踩坑教训、顿悟感想等）。

---
处理用时：52.40秒