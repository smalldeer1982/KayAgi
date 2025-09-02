# 题目信息

# Pashmak and Parmida's problem

## 题目描述

Parmida is a clever girl and she wants to participate in Olympiads this year. Of course she wants her partner to be clever too (although he's not)! Parmida has prepared the following test problem for Pashmak.

There is a sequence $ a $ that consists of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Let's denote $ f(l,r,x) $ the number of indices $ k $ such that: $ l<=k<=r $ and $ a_{k}=x $ . His task is to calculate the number of pairs of indicies $ i,j $ $ (1<=i&lt;j<=n) $ such that $ f(1,i,a_{i})&gt;f(j,n,a_{j}) $ .

Help Pashmak with the test.

## 样例 #1

### 输入

```
7
1 2 1 1 2 2 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Pashmak和Parmida的问题

## 题目描述
Parmida是个聪明的女孩，她想参加今年的奥林匹克竞赛。当然，她希望她的搭档也很聪明（尽管他实际上并不聪明）！Parmida为Pashmak准备了以下测试题。

有一个序列$a$，由$n$个整数$a_{1},a_{2},\cdots,a_{n}$组成。我们定义$f(l,r,x)$为满足以下条件的索引$k$的数量：$l\leq k\leq r$且$a_{k}=x$。他的任务是计算索引对$i,j$  $(1\leq i<j\leq n)$的数量，使得$f(1,i,a_{i})>f(j,n,a_{j})$。

请帮助Pashmak完成这个测试。

## 样例 #1
### 输入
```
7
1 2 1 1 2 2 1
```
### 输出
```
8
```

## 样例 #2
### 输入
```
3
1 1 1
```
### 输出
```
1
```

## 样例 #3
### 输入
```
5
1 2 3 4 5
```
### 输出
```
0
```

### 算法分类
树状数组

### 综合分析与结论
所有题解的核心思路都是先预处理出$f(1,i,a_i)$和$f(j,n,a_j)$，再通过类似逆序对的求解方式得出结果。由于$a_i$值域较大，离散化是必要步骤。预处理时，借助桶或树状数组来统计每个数出现的次数从而得到$f$值。在求解阶段，大多题解使用树状数组，也有使用权值线段树的，通过倒序枚举，每次将$f(j,n,a_j)$插入数据结构，查询小于$f(1,i - 1,a_i)$的数量并累加得到答案。

### 所选的题解
 - **作者：MeowScore（5星）**
    - **关键亮点**：思路清晰，详细阐述了从题意分析到利用线段树求解的全过程，代码注释详细。
    - **重点代码**：
```cpp
// 线段树单点修改
void add(int root,int l,int r,int x){
    if(l==r){
        st[root]++;
        return;
    }
    int mid=(l+r)/2;
    if(mid>=x)
        add(root*2,l,mid,x);
    else
        add(root*2+1,mid+1,r,x);
    st[root]=st[root*2]+st[root*2+1];
}
// 线段树区间查询
void ask(int root,int l,int r,int x,int y){
    if(l>=x&&r<=y){
        res+=st[root];
        return;
    }
    int mid=(l+r)/2;
    if(mid>=x)
        ask(root*2,l,mid,x,y);
    if(mid+1<=y)
        ask(root*2+1,mid+1,r,x,y);
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        b[i]=a[i];
    }
    // 离散化
    sort(b+1,b+n+1,cmp);
    int m=unique(b+1,b+n+1)-(b+1);
    for(int i=1;i<=n;i++){
        int x=lower_bound(b+1,b+n+1,a[i])-b;
        a[i]=x;
    }
    // 预处理pre数组
    for(int i=1;i<=n;i++){
        t[a[i]]++;
        pre[i]=t[a[i]];
    }
    memset(t,0,sizeof(t));
    // 预处理suf数组
    for(int i=n;i>=1;i--){
        t[a[i]]++;
        suf[i]=t[a[i]];
    }
    // 倒序枚举求解
    for(int i=n;i>=2;i--){
        add(1,1,n,suf[i]);
        res=0;
        if(pre[i-1]-1)
            ask(1,1,n,1,pre[i-1]-1);
        ans+=res;
    }
    cout<<ans;
    return 0;
}
```
核心实现思想：先离散化，再正反遍历原数组预处理出$pre$和$suf$数组，倒序枚举$suf$数组，每次将其值插入权值线段树，查询小于$pre$数组对应值的数量累加答案。

 - **作者：_雪绒花_（4星）**
    - **关键亮点**：详细说明了思路从逆序对出发，结合预处理和树状数组求解，代码注释丰富，便于理解。
    - **重点代码**：
```cpp
// 树状数组单点修改
void update(ll x) {
    while (x <= n) {
        sum[x]++;
        x += lowbit(x);
    }
}
// 树状数组区间查询
ll query(ll x) {
    ll result = 0;
    while (x) {
        result += sum[x];
        x -= lowbit(x);
    }
    return result;
}
int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        b[i] = a[i];
    }
    // 离散化
    sort(b + 1, b + n + 1);
    ll len = unique(b + 1, b + n + 1) - b - 1;
    for (ll i = 1; i <= n; i++) {
        a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
    }
    // 预处理pre数组
    for (ll i = 1; i <= n; i++) {
        pre[i] = ++cnt[a[i]];
    }
    for (ll i = 1; i <= len; i++) {
        cnt[i] = 0;
    }
    // 预处理suc数组
    for (ll i = n; i >= 1; i--) {
        suc[i] = ++cnt[a[i]];
    }
    // 树状数组求逆序对数量
    ll ans = 0;
    for (ll i = n; i >= 1; i--) {
        ans += query(pre[i] - 1);
        update(suc[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
```
核心实现思想：离散化后，正反遍历预处理出$pre$和$suc$数组，倒序枚举，每次查询树状数组中小于$pre$数组对应值的数量并累加，同时将$suc$数组对应值插入树状数组。

 - **作者：MVP_Harry（4星）**
    - **关键亮点**：对思路和步骤的描述较为清晰，代码简洁明了，对树状数组操作有清晰体现。
    - **重点代码**：
```cpp
// 树状数组单点修改
void update(int x, int k) {
    while (x <= N) {
        t[x] += k;
        x += lowbit(x);
    }
}
// 树状数组区间查询
int sum(int x) {
    int ans = 0;
    while (x!= 0) {
        ans += t[x];
        x -= lowbit(x);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i, 1, N) {
        cin >> a[i];
        b[i] = a[i];
    }
    // 离散化
    sort(b + 1, b + N + 1);
    int len = unique(b + 1, b + N + 1) - b - 1;
    rep(i, 1, N) a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
    // 预处理occurence数组
    rep(i, 1, N) {
        occurence[i][0] = ++cnt[a[i]];
    }
    memset(cnt, 0, sizeof cnt);
    per(i, N, 1) {
        occurence[i][1] = ++cnt[a[i]];
    }
    // 树状数组求解
    per(i, N, 1) {
        ans += sum(occurence[i][0] - 1);
        update(occurence[i][1], 1);
    }
    cout << ans << "\n";
    return 0;
}
```
核心实现思想：离散化后，通过正反遍历预处理出$occurence$数组，倒序枚举，利用树状数组查询小于$occurence$数组第一维对应值的数量并累加，同时将第二维对应值插入树状数组。

### 最优关键思路或技巧
离散化处理大数据值域，通过正反遍历预处理$f(1,i,a_i)$和$f(j,n,a_j)$，利用树状数组或权值线段树高效解决类似逆序对问题，优化时间复杂度到$O(nlogn)$。

### 同类型题或类似算法套路拓展
此类题目通常涉及对序列中元素出现次数的统计，结合区间查询的需求，通过预处理和特定数据结构（如树状数组、线段树）来优化时间复杂度。常见套路为离散化处理大值域，将原问题转化为逆序对或类似逆序对问题求解。

### 推荐洛谷题目
 - [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)：树状数组区间修改、区间查询模板题，有助于巩固树状数组操作。
 - [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：经典逆序对问题，可加深对逆序对求解方法的理解。
 - [P2361 yyy loves Maths VI (mode版)](https://www.luogu.com.cn/problem/P2361)：涉及统计区间内出现次数相关问题，需结合离散化和树状数组求解。 

---
处理用时：75.50秒