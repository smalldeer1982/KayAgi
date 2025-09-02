# 题目信息

# [ABC309F] Box in Box

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc309/tasks/abc309_f

$ N $ 個の箱があります。 $ i $ 番目の箱は高さ・幅・奥行きがそれぞれ $ h_i,w_i,d_i $ の直方体の形をしています。

二つの箱であって、必要ならば回転させることで片方の高さ・幅・奥行きがもう片方の高さ・幅・奥行きをそれぞれ上回るようなものが存在するかを判定してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ h_i,w_i,d_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 2 $ 番目の箱を回転させて高さと奥行きを入れ替えると、$ 3 $ 番目の箱が高さ・幅・奥行きをそれぞれ上回ります。

## 样例 #1

### 输入

```
3

19 8 22

10 24 12

15 25 11```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3

19 8 22

10 25 12

15 24 11```

### 输出

```
No```

## 样例 #3

### 输入

```
2

1 1 2

1 2 2```

### 输出

```
No```

# AI分析结果

### 题目内容重写
【题目描述】
有 $N$ 个盒子，第 $i$ 个盒子的高、宽、深分别为 $h_i, w_i, d_i$。你可以通过旋转盒子来调整其高、宽、深的顺序。问是否存在两个盒子，使得通过旋转后，其中一个盒子的高、宽、深分别严格大于另一个盒子的高、宽、深。

### 算法分类
树状数组、离散化、排序

### 综合分析与结论
本题的核心在于判断是否存在两个盒子，通过旋转后，一个盒子的三个维度分别严格大于另一个盒子的三个维度。由于盒子可以旋转，因此我们可以将每个盒子的三个维度排序，转化为三维偏序问题。由于题目只要求判断存在性，因此可以使用树状数组结合离散化的方法，将复杂度降低到 $O(n \log n)$。

### 所选题解
#### 1. 作者：DengDuck (赞：9)
- **星级**：5星
- **关键亮点**：通过排序和离散化，将问题转化为二维偏序问题，利用树状数组维护最小值，判断是否存在满足条件的盒子。代码简洁，思路清晰。
- **个人心得**：考场上一眼看出是三维偏序问题，但通过优化转化为二维偏序，大大简化了问题。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6+5;
struct node { LL a,b,c; } a[N];
LL n,cnt,t[N];
LL lowbit(LL x) { return x&-x; }
LL query(LL x) {
    LL mn=t[0];
    while(x) { mn=min(mn,t[x]); x-=lowbit(x); }
    return mn;
}
void upd(LL x,LL k) {
    while(x<=cnt) { t[x]=min(t[x],k); x+=lowbit(x); }
}
map<LL,LL> ma;
bool cmp(node x,node y) { return x.b<y.b; }
bool cmp2(node x,node y) { return x.a<y.a; }
int main() {
    memset(t,127,sizeof(t));
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) {
        scanf("%lld%lld%lld",&a[i].a,&a[i].b,&a[i].c);
        if(a[i].a>a[i].b) swap(a[i].a,a[i].b);
        if(a[i].b>a[i].c) swap(a[i].c,a[i].b);
        if(a[i].a>a[i].b) swap(a[i].a,a[i].b);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) {
        if(a[i].b!=a[i-1].b) ma[a[i].b]=++cnt;
    }
    for(int i=1;i<=n;i++) a[i].b=ma[a[i].b];
    sort(a+1,a+n+1,cmp2);
    for(int i=1;i<=n;i++) {
        LL l=i,r=i;
        while(a[r+1].a==a[l].a) r++;
        for(int j=l;j<=r;j++) {
            if(query(a[j].b-1)<a[j].c) {
                puts("Yes");
                return 0;
            }
        }
        for(int j=l;j<=r;j++) upd(a[j].b,a[j].c);
        i=r;
    }
    puts("No");
    return 0;
}
```

#### 2. 作者：Pengzt (赞：6)
- **星级**：4星
- **关键亮点**：通过排序和树状数组维护最小值，判断是否存在满足条件的盒子。思路清晰，代码简洁。
- **个人心得**：考试时写的是线段树 + set，虽然常数较大，但通过优化依然能够通过。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6+5;
struct node { LL a,b,c; } a[N];
LL n,cnt,t[N];
LL lowbit(LL x) { return x&-x; }
LL query(LL x) {
    LL mn=t[0];
    while(x) { mn=min(mn,t[x]); x-=lowbit(x); }
    return mn;
}
void upd(LL x,LL k) {
    while(x<=cnt) { t[x]=min(t[x],k); x+=lowbit(x); }
}
map<LL,LL> ma;
bool cmp(node x,node y) { return x.b<y.b; }
bool cmp2(node x,node y) { return x.a<y.a; }
int main() {
    memset(t,127,sizeof(t));
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) {
        scanf("%lld%lld%lld",&a[i].a,&a[i].b,&a[i].c);
        if(a[i].a>a[i].b) swap(a[i].a,a[i].b);
        if(a[i].b>a[i].c) swap(a[i].c,a[i].b);
        if(a[i].a>a[i].b) swap(a[i].a,a[i].b);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) {
        if(a[i].b!=a[i-1].b) ma[a[i].b]=++cnt;
    }
    for(int i=1;i<=n;i++) a[i].b=ma[a[i].b];
    sort(a+1,a+n+1,cmp2);
    for(int i=1;i<=n;i++) {
        LL l=i,r=i;
        while(a[r+1].a==a[l].a) r++;
        for(int j=l;j<=r;j++) {
            if(query(a[j].b-1)<a[j].c) {
                puts("Yes");
                return 0;
            }
        }
        for(int j=l;j<=r;j++) upd(a[j].b,a[j].c);
        i=r;
    }
    puts("No");
    return 0;
}
```

#### 3. 作者：qzhwlzy (赞：3)
- **星级**：4星
- **关键亮点**：通过排序和树状数组维护最小值，判断是否存在满足条件的盒子。代码简洁，思路清晰。
- **个人心得**：通过排序和离散化，将问题转化为二维偏序问题，利用树状数组维护最小值，判断是否存在满足条件的盒子。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 200005
using namespace std;
int n,a,b,c,uni[maxn],len,pos=1; struct node{int a,b,c; bool operator<(node x)const{return a<x.a;}}f[maxn];
int tr[maxn]; int lowbit(int x){return x&(-x);} void modify(int p,int v){for(;p<=len;p+=lowbit(p)) tr[p]=min(tr[p],v);}
int query(int p){int res=2000000000; for(;p>=1;p-=lowbit(p)) res=min(tr[p],res); return res;}
int main(){
    scanf("%d",&n); for(int i=1;i<=n;i++){
        scanf("%d%d%d",&a,&b,&c); f[i].a=min(min(a,b),c); f[i].c=max(max(a,b),c);
        f[i].b=a+b+c-f[i].a-f[i].c; uni[i]=f[i].b; tr[i]=2000000000;
    } sort(f+1,f+1+n); sort(uni+1,uni+1+n); len=unique(uni+1,uni+1+n)-uni-1;
    for(int i=1;i<=n;i++) f[i].b=lower_bound(uni+1,uni+1+len,f[i].b)-uni;
    for(int i=1;i<=n;i++){
        if(f[i].a>f[i-1].a) while(pos<i){modify(f[pos].b,f[pos].c); pos++;}
        if(query(f[i].b-1)<f[i].c){printf("Yes"); return 0;}
    }
    printf("No"); return 0;
}
```

### 最优关键思路或技巧
1. **排序与离散化**：通过将盒子的三个维度排序，并离散化处理，将问题转化为二维偏序问题，大大简化了问题复杂度。
2. **树状数组维护最小值**：利用树状数组维护最小值，快速判断是否存在满足条件的盒子，时间复杂度为 $O(n \log n)$。
3. **批量处理相同维度**：在处理相同维度的盒子时，批量更新树状数组，避免重复操作，提高效率。

### 可拓展之处
类似的问题可以扩展到更高维度的偏序问题，或者扩展到需要统计满足条件的盒子数量的情况。此外，树状数组和离散化的技巧在解决其他偏序问题时也非常有用。

### 推荐题目
1. [P3810 陌上花开](https://www.luogu.com.cn/problem/P3810) - 三维偏序问题，统计满足条件的盒子数量。
2. [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972) - 利用树状数组解决区间查询问题。
3. [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368) - 树状数组的基本应用，区间修改与单点查询。

---
处理用时：63.80秒