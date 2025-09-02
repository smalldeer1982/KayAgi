# 题目信息

# Resource Distribution

## 题目描述

One department of some software company has $ n $ servers of different specifications. Servers are indexed with consecutive integers from $ 1 $ to $ n $ . Suppose that the specifications of the $ j $ -th server may be expressed with a single integer number $ c_j $ of artificial resource units.

In order for production to work, it is needed to deploy two services $ S_1 $ and $ S_2 $ to process incoming requests using the servers of the department. Processing of incoming requests of service $ S_i $ takes $ x_i $ resource units.

The described situation happens in an advanced company, that is why each service may be deployed using not only one server, but several servers simultaneously. If service $ S_i $ is deployed using $ k_i $ servers, then the load is divided equally between these servers and each server requires only $ x_i / k_i $ (that may be a fractional number) resource units.

Each server may be left unused at all, or be used for deploying exactly one of the services (but not for two of them simultaneously). The service should not use more resources than the server provides.

Determine if it is possible to deploy both services using the given servers, and if yes, determine which servers should be used for deploying each of the services.

## 说明/提示

In the first sample test each of the servers 1, 2 and 6 will will provide $ 8 / 3 = 2.(6) $ resource units and each of the servers 5, 4 will provide $ 16 / 2 = 8 $ resource units.

In the second sample test the first server will provide $ 20 $ resource units and each of the remaining servers will provide $ 32 / 3 = 10.(6) $ resource units.

## 样例 #1

### 输入

```
6 8 16
3 5 2 9 8 7
```

### 输出

```
Yes
3 2
1 2 6
5 4```

## 样例 #2

### 输入

```
4 20 32
21 11 11 12
```

### 输出

```
Yes
1 3
1
2 3 4
```

## 样例 #3

### 输入

```
4 11 32
5 5 16 16
```

### 输出

```
No
```

## 样例 #4

### 输入

```
5 12 20
7 8 4 11 9
```

### 输出

```
No
```

# AI分析结果

### 题目内容
# 资源分配

## 题目描述
某软件公司的一个部门有 $n$ 台不同规格的服务器。服务器用从 $1$ 到 $n$ 的连续整数进行编号。假设第 $j$ 台服务器的规格可以用一个人工资源单位的整数 $c_j$ 来表示。

为了使生产能够进行，需要部署两个服务 $S_1$ 和 $S_2$，使用该部门的服务器来处理传入的请求。处理服务 $S_i$ 的传入请求需要 $x_i$ 个资源单位。

上述情况发生在一家先进的公司，因此每个服务不仅可以使用一台服务器，还可以同时使用多台服务器。如果服务 $S_i$ 使用 $k_i$ 台服务器进行部署，那么负载将平均分配到这些服务器上，每台服务器只需要 $x_i / k_i$（可能是一个分数）个资源单位。

每台服务器可以完全不使用，或者仅用于部署其中一个服务（但不能同时用于两个服务）。服务使用的资源不应超过服务器提供的资源。

确定是否可以使用给定的服务器部署这两个服务，如果可以，确定应该使用哪些服务器来部署每个服务。

## 说明/提示
在第一个示例测试中，服务器 1、2 和 6 每台将提供 $8 / 3 = 2.(6)$ 个资源单位，服务器 5、4 每台将提供 $16 / 2 = 8$ 个资源单位。

在第二个示例测试中，第一台服务器将提供 $20$ 个资源单位，其余每台服务器将提供 $32 / 3 = 10.(6)$ 个资源单位。

## 样例 #1
### 输入
```
6 8 16
3 5 2 9 8 7
```
### 输出
```
Yes
3 2
1 2 6
5 4
```

## 样例 #2
### 输入
```
4 20 32
21 11 11 12
```
### 输出
```
Yes
1 3
1
2 3 4
```

## 样例 #3
### 输入
```
4 11 32
5 5 16 16
```
### 输出
```
No
```

## 样例 #4
### 输入
```
5 12 20
7 8 4 11 9
```
### 输出
```
No
```

### 算法分类
构造

### 题解综合分析与结论
两题解均将原问题转化为更易理解的形式，通过分析条件找到解题思路。
- **S00021题解**：先证明将 $c_i$ 排序后，每个服务使用的服务器资源在排序后是连续一段，进而贪心确定若钦定一个服务占用区间在前，另一个服务应占用其后较大值区间，且前一个服务从前向后扫描尽量少用服务器。通过两次尝试不同顺序（交换 $x_1$ 和 $x_2$）来检查是否有解并输出方案。
- **gcx12012题解**：把问题转化为物品放入背包问题，对物品价值 $val$ 降序排序，对每个 $d\in[1,n]$ 分别处理出两个背包在对应 $\lceil\frac{c}{d}\rceil$ 条件下最多能放入物品数，找出第一个背包满足条件的最小 $d$，再对第二个背包找到合适 $d$ 使存在合法解。

### 所选的题解
- **S00021题解**：
  - **星级**：4星
  - **关键亮点**：通过微扰法证明服务器资源使用的连续性，基于此贪心构造方案，代码简洁高效。
```cpp
#include<bits/stdc++.h>
#define MAXN 1000000
#define int long long
using namespace std;
int n,x1,x2,used[MAXN+5];
struct node{
    int v,id;
}c[MAXN+5];
bool cmp(node x,node y){return x.v<y.v;}
bool check(int fl){
    int k1=-1; for(int i=1;i<=n;i++) used[i]=0;
    int k2=-1,ln=0,ti=0;
    for(int i=n;i;i--){
        used[i]=2,++ln;
        if((x2+ln-1)/ln<=c[i].v){k2=ln,ti=i; break;}
    }if(k2==-1) return 0; int pln=0; 
    for(int i=ti-1;i;i--){
        used[i]=1; ++pln;
        if((x1+pln-1)/pln<=c[i].v){k1=pln; break;}
    }if(k1==-1) return 0;
    int t1=1,t2=2;
    if(fl) swap(k1,k2),swap(t1,t2); 
    printf("Yes\n%lld %lld\n",k1,k2);
    for(int i=1;i<=n;i++){
        if(used[i]==t1) printf("%lld ",c[i].id);
    }puts(""); for(int i=1;i<=n;i++) if(used[i]==t2) printf("%lld ",c[i].id); puts("");
    exit(0); return 1;
}signed main(){
    scanf("%lld%lld%lld",&n,&x1,&x2);
    for(int i=1;i<=n;i++) scanf("%lld",&c[i].v),c[i].id=i;
    sort(c+1,c+n+1,cmp); int l=1,r=n;
    check(0); swap(x1,x2); check(1);
    puts("No");
    return 0;
}
```
核心实现思想：check函数尝试一种服务顺序的分配方案，先从后往前找满足 $x_2$ 需求的服务器数量及位置，再从该位置前找满足 $x_1$ 需求的服务器数量，若都满足则输出方案。main函数通过两次调用check函数，尝试两种服务顺序来确定是否有解。

- **gcx12012题解**：
  - **星级**：4星
  - **关键亮点**：将问题转化为背包问题，利用双指针思想处理每个背包可放入物品数，通过排序和二分查找优化，还给出了 $O(n)$ 的基数排序优化版本。
```cpp
// LUOGU_RID: 154368021
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 300010
#define For(i,a,b) for(ll i=a;i<=b;i++)
#define Rof(i,a,b) for(ll i=a;i>=b;i--)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
struct node{
    int val,bh;
}a[N];
int b1[N],b2[N];
int n,x1,x2;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}


int main()
{
    n=read(),x1=read(),x2=read();
    For(i,1,n) a[i].val=read(),a[i].bh=i;
    sort(a+1,a+n+1,[&](node x,node y){return x.val>y.val;});
    int now=1;
    For(i,1,n){
        while(now<=n && a[now].val>=x1/i+(x1%i>0)) now++;
        b1[i]=now-1;
    }
    now=1;
    For(i,1,n){
        while(now<=n && a[now].val>=x2/i+(x2%i>0)) now++;
        b2[i]=now-1;
    }
    For(i,1,n) if(b1[i]<i) b1[i]=0;
    For(i,1,n) if(b2[i]<i) b2[i]=0;
    int p=1919810;
    For(i,1,n){
        if(b1[i]!=0){
            p=i;
            break;
        }
    }
    For(i,1,n){
        if(!b2[i]) continue;
        if(b2[i]-i>=p){
            printf("Yes\n%d %d\n",p,i);
            For(j,1,p) printf("%d ",a[j].bh);
            printf("\n");
            For(j,p+1,p+i) printf("%d ",a[j].bh);
            printf("\n");
            return 0;
        }
    }
    p=1919810;
    For(i,1,n){
        if(b2[i]!=0){
            p=i;
            break;
        }
    }
    For(i,1,n){
        if(!b1[i]) continue;
        if(b1[i]-i>=p){
            printf("Yes\n%d %d\n",i,p);
            For(j,p+1,p+i) printf("%d ",a[j].bh);
            printf("\n");
            For(j,1,p) printf("%d ",a[j].bh);
            printf("\n");
            return 0;
        }
    }
    printf("No");
    return 0;
}
```
核心实现思想：先对服务器资源降序排序，通过双指针确定每个背包在不同 $d$ 下可放入的最大物品数，再寻找满足条件的 $d$ 组合以确定放置方案。

### 最优关键思路或技巧
- **排序**：两题解都对服务器资源进行排序，方便后续处理和分析，简化问题求解过程。
- **贪心与构造**：S00021题解通过贪心确定服务使用服务器的区间，构造出可行方案；gcx12012题解从背包容量和物品价值关系出发，构造满足条件的放置方案。

### 可拓展之处
此类构造题常需将实际问题转化为熟悉模型，通过分析条件找到关键限制，进而构造方案。类似题目通常围绕资源分配、任务调度等场景，可拓展到多服务多资源限制的情况，解题思路类似，需深入挖掘条件间关系。

### 洛谷相似题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：同样涉及物品分组，需根据一定条件对物品进行分配，考查贪心和构造能力。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：关于区间选择和覆盖问题，与本题在如何选择合适元素满足条件上思路类似。
- [P2893 [USACO08FEB] Making the Grade G](https://www.luogu.com.cn/problem/P2893)：通过调整序列元素满足特定条件，在构造满足条件的序列方面与本题有相似思维方式。

### 个人心得摘录与总结
无个人心得。 

---
处理用时：82.48秒