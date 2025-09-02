# 题目信息

# [USACO23DEC] Haybale Distribution G

## 题目描述

Farmer John 正在农场上分发干草堆。

Farmer John 的农场上有 $N$（$1 \le N \le 2\cdot 10^5$）座谷仓，分别位于数轴上的整点 $x_1,\ldots,x_N$（$0 \le x_i \le 10^6$）。Farmer John 正计划将 $N$ 车干草堆运输到整点 $y$（$0 \le y \le 10^6$），然后为每一座谷仓运输一车干草堆。

不幸的是，Farmer John 的运输系统浪费了很多干草堆。具体来说，给出一些 $a_i,b_i$（$1 \le a_i,b_i \le 10^6$），每车干草堆每向左移动一单位距离，$a_i$ 堆干草堆会被浪费；每车干草堆每向右移动一单位距离，$b_i$ 堆干草堆会被浪费。形式化地，一车干草堆从整点 $y$ 运动到位于 $x$ 的谷仓，被浪费的干草堆堆数如下：

$$\begin{cases}a_i\cdot (y-x) & \text{if} \ y>x \\ b_i\cdot(x-y)&\text{if}\ x>y\end{cases}$$

给出 $Q$（$1 \le Q \le 2 \cdot 10^5$）组相互独立的询问，每组询问给出一组 $(a_i,b_i)$ 的值，帮助 Farmer John 计算当按照最佳方案选择 $y$，最少有多少堆干草堆被浪费。

## 说明/提示

### 样例解释 1

样例中第二个询问，最佳方案为选择 $y=2$，被浪费的干草堆数量为 $2(2-1)+2(2-2)+1(3-2)+1(4-2)+1(10-2)=1+0+1+2+8=13$。

### 测试点性质

- 测试点 $2$ 满足 $N,Q \le 10$。
- 测试点 $3$ 满足 $N,Q \le 500$。
- 测试点 $4-6$ 满足 $N,Q \le 5000$。
- 测试点 $7-16$ 没有额外限制。

## 样例 #1

### 输入

```
5
1 4 2 3 10
4
1 1
2 1
1 2
1 4```

### 输出

```
11
13
18
30```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何找到使干草堆浪费最少的 $y$ 值展开，多数题解先证明目标函数是单谷函数，再采用三分法、二分法或数学推导求解。部分题解通过预处理前缀和来优化计算损耗的时间复杂度。不同题解在思路和实现上各有特色，有的侧重于数学推导，有的则利用算法特性进行搜索。

### 所选题解
- **作者：RDFZchenyy（5星）**
    - **关键亮点**：思路清晰，采用偏数学的方法，通过分析 $d$ 变化时答案的增量，推导出满足条件的最小 $k$，并结合前缀和优化计算，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005

int n,q,u;
long long x[MAXN],sum[MAXN];
long long a,b;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i];
    }	
    sort(x+1,x+n+1);
   
    for(int i=1;i<=n;i++){ // 预处理前缀和
        sum[i]=sum[i-1]+x[i];
    }
   
    cin>>q;
    for(int i=1;i<=q;i++){
        cin>>a>>b;
        u=(int)(ceil((long double)b*n/(a+b))); // 为了保证精度如此操作
        cout<<(x[u]*(u)-sum[u])*a+(sum[n]-sum[u]-x[u]*(n-u))*b<<endl;
        // 此处计算答案时带入前缀和
    }
	
    return 0;
}
```
    - **核心实现思想**：先对谷仓位置排序并预处理前缀和，对于每组询问，计算满足 $\Delta= k\times (a+b)\ge n\times b$ 的最小 $k$，然后根据 $k$ 计算答案。

- **作者：听取MLE声一片（4星）**
    - **关键亮点**：将问题转化为若干个一次函数求最小值，通过维护上凸壳找对应直线，思路独特，虽然代码复杂，但具有创新性。
    - **核心代码**：
```cpp
// 部分核心代码
for(int i=1;i<=n;i++){
    int x=read();
    a[x]++;
    b[x]+=x;
}
// 计算前缀和
for(int i=0;i<=M;i++){
    if(i){
        f[i]=f[i-1]+a[i];
        g[i]=g[i-1]+b[i];
    }
    else{
        f[i]=a[i];
        g[i]=b[i];
    }
    s1[i]=i*f[i]-g[i];
}
// 计算后缀和
f[M+1]=g[M+1]=0;
for(int i=M;i>=0;i--){
    f[i]=f[i+1]+a[i];
    g[i]=g[i+1]+b[i];
    s2[i]=g[i]-i*f[i];
}
// 维护上凸壳
for(int i=1;i<=k;i++){
    while(top){
        double x=(E[st[top]].y-E[i].y)*1.0/(E[i].x-E[st[top]].x);
        if(pos[top]>=x){
            top--;
            continue;
        }
        st[++top]=i;
        pos[top]=x;
        break;
    }
    if(!top){
        st[++top]=i;
        pos[top]=0;
    }
}
```
    - **核心实现思想**：先计算每个位置左右谷仓到其的距离之和，将问题转化为一次函数求最小值，通过对斜率排序、去重，按与上一条直线相交位置建单调栈维护上凸壳，最后二分查找对应直线计算答案。

- **作者：mRXxy0o0（4星）**
    - **关键亮点**：通过分析 $x$ 移动时增量的单调性，证明函数的单谷性，实现上规避了浮点数，代码简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int n,m;
ll f[N],g[N],a[N];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%lld",&a[i]);
    }
    sort(a+1,a+1+n);
    for(int i=2;i<=n;++i){
        f[i]=f[i-1]+(i-1)*(a[i]-a[i-1]);
    }
    for(int i=n-1;i;--i){
        g[i]=g[i+1]+(n-i)*(a[i+1]-a[i]);
    }
    scanf("%d",&m);
    while(m--){
        ll x,y;
        scanf("%lld%lld",&x,&y);
        int l=1,r=n-1,res=1;
        while(l<=r){
            int mid=l+r>>1;
            if(x*mid-y*(n-mid)<=0) res=mid+1,l=mid+1;
            else r=mid-1;
        }
        printf("%lld\n",f[res]*x+g[res]*y);
    }
    return 0;
}
```
    - **核心实现思想**：先对谷仓位置排序，预处理左右距离和，对于每组询问，二分查找使增量非负的位置，然后计算答案。

### 最优关键思路或技巧
- **数学推导**：如 RDFZchenyy 的题解，通过分析 $d$ 变化时答案的增量，推导出满足条件的最小 $k$，将问题转化为数学计算，避免了复杂的搜索过程。
- **前缀和优化**：多数题解都采用了前缀和预处理，将计算损耗的时间复杂度从 $O(n)$ 优化到 $O(1)$。
- **函数特性利用**：通过证明目标函数是单谷函数，使用三分法或二分法快速找到最小值。

### 可拓展之处
同类型题可能会改变运输规则、增加限制条件或改变数据范围。类似算法套路可用于解决其他具有单谷性质的函数求最值问题，如一些优化问题、决策问题等。

### 推荐题目
- [P1047 [NOIP2005 普及组] 校门外的树](https://www.luogu.com.cn/problem/P1047)：涉及区间处理和前缀和思想。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：使用二分法解决最值问题。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：同样利用二分法求解最优解。

### 个人心得
部分题解提到不太会三分所以用二分，这说明在面对算法选择时，可以根据自己的掌握情况灵活变通，选择熟悉的算法解决问题。同时，也提醒我们要不断学习和掌握更多的算法，以应对不同的题目。 

---
处理用时：47.87秒