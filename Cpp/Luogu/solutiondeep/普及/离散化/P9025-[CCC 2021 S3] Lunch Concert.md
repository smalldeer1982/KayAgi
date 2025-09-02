# 题目信息

# [CCC 2021 S3] Lunch Concert

## 题目描述

有 $N$ 个人，第 $i$ 个人的速度为 $W_i$ **秒每米**，听力为 $D_i$，即能听见距离他不超过 $D_i$ 米处的音乐，初始在 $P_i$ 位置。

你要在 $c$ 位置处开音乐会，这个 $c$ 由你决定且为整数。这 $N$ 个人都会靠近你直到能听到你。你要最小化每个人移动的时间之和。

## 说明/提示

$$1\leq N\leq 200000,0\leq P_i\leq 10^9,1\leq W_i\leq 1000,0\leq D_i\leq 10^9$$

译自 [CCC2021 S3](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

###### 2023.8.10 新增一组 hack 数据。

## 样例 #1

### 输入

```
1
0 1000 0
```

### 输出

```
0```

## 样例 #2

### 输入

```
2
10 4 3
20 4 2
```

### 输出

```
20```

## 样例 #3

### 输入

```
3
6 8 3
1 4 1
14 5 2
```

### 输出

```
43```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何确定音乐会位置 $c$ 以最小化所有人移动时间之和展开，采用了不同的算法思路。
- **分段函数与离散化差分**：将每个人转化为线段，得到分段函数，利用离散化和差分求和取最小值。
- **三分法**：证明答案是单谷函数，通过三分法不断缩小范围找到最小值。
- **动态维护断点**：分析函数断点，动态维护断点答案取最小值。
- **模拟退火**：使用随机化算法模拟退火求解。
- **前缀和与单调性优化**：将人看作线段，排序后用前缀和与后缀和优化，利用单调性求解。

### 所选题解
- **作者：_•́へ•́╬_（5星）**
    - **关键亮点**：思路清晰，利用离散化和差分处理分段函数，代码实现简洁高效。
    - **核心代码**：
```cpp
inline void add(const int&l,const int&r,const int&x,const long long&y)
    {a[l]+=x;a[r+1]-=x;b[l]+=y;b[r+1]-=y;}
for(int i=0;i<n;++i)
{
    read(p[i]);read(w[i]);read(d[i]);
    lsh[m++]=p[i]-d[i];
    lsh[m++]=p[i]+d[i];
}
sort(lsh,lsh+m);m=unique(lsh,lsh+m)-lsh;
for(int i=0,x;i<n;++i)
{
    x=p[i]-d[i];
    add(0,lower_bound(lsh,lsh+m,x)-lsh,-w[i],(long long)(w[i])*x);
    x=p[i]+d[i];
    add(upper_bound(lsh,lsh+m,x)-lsh,m,w[i],-(long long)(w[i])*x);
}
ans=a[0]*lsh[0]+b[0];
for(int i=1;i<=m;++i)
{
    a[i]+=a[i-1];b[i]+=b[i-1];
    if(a[i]>>63)min(ans,a[i]*lsh[i]+b[i]);
    else min(ans,a[i]*lsh[i-1]+b[i]);
}
```
核心思想是先将每个人对应的线段端点离散化，然后通过差分标记每个端点的变化，最后遍历端点计算最小值。

- **作者：wjh2011（4星）**
    - **关键亮点**：清晰证明答案是单谷函数，使用三分法求解，代码简洁易懂。
    - **核心代码**：
```cpp
int work(int x){
    int ans=0;
    for(int i=1;i<=n;i++){
        if(p[i]+d[i]<x) ans+=w[i]*(x-p[i]-d[i]);
        if(p[i]-d[i]>x) ans+=w[i]*(p[i]-d[i]-x);
    }
    return ans;
}
int l=-1e9,r=1e9;
while(l<=r){
    int lmid=(2*l+r)/3,rmid=(l+2*r)/3;
    int lans=work(lmid),rans=work(rmid);
    if(lans<=rans){
        ans=min(ans,lans);
        r=rmid-1;
    }
    if(lans>rans){
        ans=min(ans,rans);
        l=lmid+1;
    }
}
```
核心思想是定义一个计算特定位置 $x$ 下移动时间之和的函数 `work`，然后通过三分法不断缩小范围找到最小值。

- **作者：small_john（4星）**
    - **关键亮点**：同样利用三分法，思路清晰，代码简洁。
    - **核心代码**：
```cpp
int f(int x)
{
    int res = 0;
    for(int i = 1;i<=n;i++)
        if(x<p[i]-d[i]) res+=(p[i]-d[i]-x)*w[i];
        else if(x>p[i]+d[i]) res+=(x-p[i]-d[i])*w[i];
    return res;
}
int l = -1e9,r = 1e9;
while(l<=r)
{
    int mid1 = (2*l+r)/3,mid2 = (l+2*r)/3,f1 = f(mid1),f2 = f(mid2);
    ans = min({ans,f1,f2});
    if(f1<=f2) r = mid2-1;
    else l = mid1+1;
}
```
核心思想是定义函数 `f` 计算特定位置的移动时间之和，通过三分法缩小范围找到最小值。

### 最优关键思路或技巧
- **离散化与差分**：将复杂的分段函数通过离散化和差分处理，降低计算复杂度。
- **三分法**：证明函数为单谷函数后，使用三分法高效找到最小值。

### 可拓展之处
同类型题或类似算法套路：
- 涉及函数最值求解且函数为单峰或单谷的问题，可考虑三分法。
- 对于有多个区间影响结果的问题，可尝试离散化和差分处理。

### 推荐题目
- [P3382 【模板】三分法](https://www.luogu.com.cn/problem/P3382)
- [P1883 函数](https://www.luogu.com.cn/problem/P1883)
- [P2571 [SCOI2010]传送带](https://www.luogu.com.cn/problem/P2571)

### 个人心得
- **作者：nr0728**：模拟赛做过此题，提到模拟退火时退火次数太少会 WA，建议退到即将超过时限再输出，还指出答案是单峰函数也可用爬山算法或三分求解。总结为在使用模拟退火算法时要注意退火次数，同时可根据函数特性选择其他合适算法。 

---
处理用时：33.82秒