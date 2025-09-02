# 题目信息

# Rooks Defenders

## 题目描述

You have a square chessboard of size $ n \times n $ . Rows are numbered from top to bottom with numbers from $ 1 $ to $ n $ , and columns — from left to right with numbers from $ 1 $ to $ n $ . So, each cell is denoted with pair of integers $ (x, y) $ ( $ 1 \le x, y \le n $ ), where $ x $ is a row number and $ y $ is a column number.

You have to perform $ q $ queries of three types:

- Put a new rook in cell $ (x, y) $ .
- Remove a rook from cell $ (x, y) $ . It's guaranteed that the rook was put in this cell before.
- Check if each cell of subrectangle $ (x_1, y_1) - (x_2, y_2) $ of the board is attacked by at least one rook.

Subrectangle is a set of cells $ (x, y) $ such that for each cell two conditions are satisfied: $ x_1 \le x \le x_2 $ and $ y_1 \le y \le y_2 $ .

Recall that cell $ (a, b) $ is attacked by a rook placed in cell $ (c, d) $ if either $ a = c $ or $ b = d $ . In particular, the cell containing a rook is attacked by this rook.

## 说明/提示

Consider example. After the first two queries the board will look like the following picture (the letter $ R $ denotes cells in which rooks are located, the subrectangle of the query of the third type is highlighted in green):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/ed156665629e711ee2ed4626477b94d3794c1b66.png)Chessboard after performing the third and the fourth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/287c91194903b3f438014966a1c3ab50aa3053b1.png)Chessboard after performing the fifth and the sixth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/2450d8ada954d98a57be494097290cacc9d47393.png)Chessboard after performing the seventh and the eighth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/860ee139e8d85a9e953e6218af254f9a2b04a395.png)Chessboard after performing the last two queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/fa48f4457088559fa8b50c796cacdd0ae0609075.png)

## 样例 #1

### 输入

```
8 10
1 2 4
3 6 2 7 2
1 3 2
3 6 2 7 2
1 4 3
3 2 6 4 8
2 4 3
3 2 6 4 8
1 4 8
3 2 6 4 8```

### 输出

```
No
Yes
Yes
No
Yes```

# AI分析结果

### 题目中文重写
# 车的防御者

## 题目描述
你有一个大小为 $n \times n$ 的正方形棋盘。行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $n$。因此，每个单元格都用一对整数 $(x, y)$ 表示（$1 \le x, y \le n$），其中 $x$ 是行号，$y$ 是列号。

你需要执行 $q$ 个类型的查询：
- 在单元格 $(x, y)$ 中放置一个新的车。
- 从单元格 $(x, y)$ 中移除一个车。保证之前在这个单元格中放置过车。
- 检查棋盘的子矩形 $(x_1, y_1) - (x_2, y_2)$ 中的每个单元格是否至少被一个车攻击。

子矩形是一组单元格 $(x, y)$，使得对于每个单元格都满足两个条件：$x_1 \le x \le x_2$ 且 $y_1 \le y \le y_2$。

回顾一下，如果 $a = c$ 或 $b = d$，则单元格 $(a, b)$ 会被放置在单元格 $(c, d)$ 中的车攻击。特别地，包含车的单元格会被这个车攻击。

## 说明/提示
考虑示例。在前两个查询之后，棋盘将如下所示（字母 $R$ 表示放置车的单元格，第三个查询的子矩形用绿色突出显示）：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/ed156665629e711ee2ed4626477b94d3794c1b66.png)

执行第三和第四个查询后的棋盘：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/287c91194903b3f438014966a1c3ab50aa3053b1.png)

执行第五和第六个查询后的棋盘：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/2450d8ada954d98a57be494097290cacc9d47393.png)

执行第七和第八个查询后的棋盘：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/860ee139e8d85a9e953e6218af254f9a2b04a395.png)

执行最后两个查询后的棋盘：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/fa48f4457088559fa8b50c796cacdd0ae0609075.png)

## 样例 #1
### 输入
```
8 10
1 2 4
3 6 2 7 2
1 3 2
3 6 2 7 2
1 4 3
3 2 6 4 8
2 4 3
3 2 6 4 8
1 4 8
3 2 6 4 8
```
### 输出
```
No
Yes
Yes
No
Yes
```

### 综合分析与结论
这些题解的核心思路都是通过数据结构来维护棋盘上每行和每列是否有车，以此判断子矩形是否被车完全攻击。主要使用的数据结构有树状数组和线段树。

#### 思路对比
- **树状数组**：维护每行和每列车的存在情况，通过前缀和查询区间内车的数量，判断是否覆盖子矩形的所有行或列。
- **线段树**：同样维护行和列，通过区间查询判断子矩形的行或列是否都有车。

#### 算法要点
- **树状数组**：单点修改和区间查询，时间复杂度 $O(q \log n)$。
- **线段树**：单点修改和区间查询，时间复杂度 $O(q \log n)$。

#### 解决难点
- **重复放置和移除**：使用额外数组记录每行和每列车的数量，避免重复操作对数据结构的错误更新。
- **判断覆盖**：通过判断区间内车的数量是否等于区间长度来确定是否覆盖。

### 所选题解
- **panyanppyy（4星）**
    - **关键亮点**：思路清晰，代码简洁，详细给出了树状数组和线段树两种方案，并实现了树状数组的代码。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) x.begin(),x.end()
using namespace std;
const int N=1e5+1;
int n,m,fx[N],fy[N];
inline int low(int x){return-x&x;}
struct qjc{
    int t[N];
    inline void update(int x,int k){for(;x<=n;x+=low(x))t[x]+=k;}
    inline int query(int x){int res=0;for(;x;x-=low(x))res+=t[x];return res;}
    inline int Q(int x,int y){return query(y)-query(x-1);}
}_x,_y;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,op,x,y,X,Y;i<=m;i++){
        scanf("%d%d%d",&op,&x,&y);
        switch(op){
            case 1:
                fx[x]++,fy[y]++;
                if(fx[x]==1)_x.update(x,1);
                if(fy[y]==1)_y.update(y,1);
                break;
            case 2:
                fx[x]--,fy[y]--;
                if(!fx[x])_x.update(x,-1);
                if(!fy[y])_y.update(y,-1);
                break;
            case 3:
                scanf("%d%d",&X,&Y);
                if(_x.Q(x,X)==X-x+1||_y.Q(y,Y)==Y-y+1)puts("YES");
                else puts("NO");
                break;
        }
    }
    return 0;
}
```
核心实现思想：使用两个树状数组分别维护行和列，`fx` 和 `fy` 数组记录每行和每列车的数量，在放置和移除车时更新树状数组，查询时判断子矩形的行或列是否都有车。

- **Anguei（4星）**
    - **关键亮点**：思路清晰，代码规范，详细解释了判断子矩形被攻击的条件，使用树状数组实现。
    - **核心代码**：
```cpp
struct Fenwick {
    int n;
    std::vector<int> v;
    Fenwick(int n) : n(n), v(n + 1) {}
    int lowbit(int x) { return x & -x; }
    void add(int x, int y) {
        for (; x <= n; x += lowbit(x)) v[x] += y;
    }
    int sum(int x) {
        int res = 0;
        for (; x; x -= lowbit(x)) res += v[x];
        return res;
    }
    int rangeSum(int l, int r) { return sum(r) - sum(l - 1); }
};

void solution() {
    int n, q;
    read(n, q);
    std::vector<int> row(n + 1, 0), col(n + 1, 0);
    Fenwick bitRow(n), bitCol(n);
    while (q--) {
        int opt;
        read(opt);
        if (opt == 1) {
            int x, y;
            read(x, y);
            ++row[x];
            ++col[y];
            if (row[x] == 1) bitRow.add(x, 1);
            if (col[y] == 1) bitCol.add(y, 1);
        } else if (opt == 2) {
            int x, y;
            read(x, y);
            --row[x];
            --col[y];
            if (row[x] == 0) bitRow.add(x, -1);
            if (col[y] == 0) bitCol.add(y, -1);
        } else {
            int x1, y1, x2, y2;
            read(x1, y1, x2, y2);
            int rowLen = x2 - x1 + 1, colLen = y2 - y1 + 1;
            bool ok = false;
            if (bitRow.rangeSum(x1, x2) == rowLen) ok = true;
            if (bitCol.rangeSum(y1, y2) == colLen) ok = true;
            std::cout << (ok ? "YES" : "NO") << "\n";
        }
    }
}
```
核心实现思想：自定义 `Fenwick` 类实现树状数组，`row` 和 `col` 数组记录每行和每列车的数量，在放置和移除车时更新树状数组，查询时判断子矩形的行或列是否都有车。

- **Rnfmabj（4星）**
    - **关键亮点**：思路清晰，代码简洁，详细解释了使用树状数组的原因，实现了树状数组的代码。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define R read()
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout)
using namespace std;
inline ll read() {
    ll s=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')f*=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*f;
}
const ll maxn=1e5+5;
ll t1[maxn],t2[maxn];
ll n,m;
ll lb(ll x){
    return x&-x;
}
void add_1(ll p,ll x){
    while(p<=n){
        t1[p]+=x;
        p+=lb(p); 
    }
}
void add_2(ll p,ll x){
    while(p<=n){
        t2[p]+=x;
        p+=lb(p); 
    }
}
ll sum_1(ll x){
    ll res=0;
    while(x>0){
        res+=t1[x];
        x-=lb(x);
    }
    return res;
}
ll sum_2(ll x){
    ll res=0;
    while(x>0){
        res+=t2[x];
        x-=lb(x);
    }
    return res;
}
ll cnt_1[maxn],cnt_2[maxn];
signed main(){
    n=R,m=R;
    for(ll i=1;i<=m;i++){
        ll opt=R;
        if(opt==1){
            ll x=R,y=R;
            if(!cnt_1[x])add_1(x,1);
            if(!cnt_2[y])add_2(y,1);
            cnt_1[x]++,cnt_2[y]++;
        }
        if(opt==2){
            ll x=R,y=R;
            if(cnt_1[x]==1)add_1(x,-1);
            if(cnt_2[y]==1)add_2(y,-1);
            cnt_1[x]--,cnt_2[y]--;
        }
        if(opt==3){
            ll ans=0,flag=0,fl=0;
            ll x=R,y=R,l=R,r=R;
            ans=sum_1(l)-sum_1(x-1);
            if(ans<l-x+1)flag=1;
            ans=sum_2(r)-sum_2(y-1);
            if(ans<r-y+1)fl=1;
            if(flag==1&&fl==1)cout<<"NO"<<endl;
            else cout<<"YES"<<endl;
        }
    }
    return 0;
}
```
核心实现思想：使用两个树状数组分别维护行和列，`cnt_1` 和 `cnt_2` 数组记录每行和每列车的数量，在放置和移除车时更新树状数组，查询时判断子矩形的行或列是否都有车。

### 最优关键思路或技巧
- **数据结构选择**：树状数组和线段树都能高效解决单点修改和区间查询问题，树状数组代码更简洁，线段树更通用。
- **辅助数组**：使用额外数组记录每行和每列车的数量，避免重复操作对数据结构的错误更新。

### 可拓展之处
同类型题或类似算法套路：
- 二维矩阵的区间修改和查询问题，可使用二维树状数组或二维线段树。
- 动态维护区间信息的问题，如区间最值、区间和等，可使用线段树或树状数组。

### 推荐题目
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
- [P2068 统计和](https://www.luogu.com.cn/problem/P2068)

### 个人心得摘录与总结
- **a1co0av5ce5az1cz0ap_**：线段树卡了 1 小时，提醒我们在使用线段树时要注意细节，合理设置初始值和更新逻辑。
- **Shunpower**：尝试二维线段树失败，WA #3，提醒我们在选择数据结构时要充分考虑问题的特点，避免盲目尝试。

---
处理用时：68.39秒