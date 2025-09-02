# [ABC232H] King's Tour

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc232/tasks/abc232_h

縦横 $ H\ \times\ W $ のチェス盤と $ 1 $ 個のキングの駒があります。  
 チェス盤のマスのうち、上から $ i $ 行目 $ (1\ \leq\ i\ \leq\ H) $ で左から $ j $ 行目 $ (1\ \leq\ j\ \leq\ W) $ のマスを $ (i,\ j) $ と表します。  
 キングは置かれているマスから周囲 $ 1 $ マスに動かすことができます。より厳密には、チェス盤のマス目の組 $ (i,\ j) $, $ (k,\ l) $ が $ \max(|i-k|,|j-l|)\ =\ 1 $ を満たすとき、かつその時に限り $ (i,j) $ に置かれているキングを $ (k,\ l) $ に動かすことができます。

次の条件を満たすようにキングを縦横 $ H\ \times\ W $ のチェス盤上で動かすことを「ツアー」と定めます。

- はじめ、$ (1,\ 1) $ にキングを置く。そのあと、キングが全てのマスにちょうど $ 1 $ 回ずつ置かれるようにキングを動かす。

たとえば、$ H\ =\ 2,\ W\ =\ 3 $ のとき、$ (1,1)\ \to\ (1,2)\ \to\ (1,\ 3)\ \to\ (2,\ 3)\ \to\ (2,\ 2)\ \to\ (2,\ 1) $ の順にキングを動かしたものは条件を満たします。

チェス盤上の $ (1,1) $ 以外のマス $ (a,\ b) $ が与えられます。ツアーのうち最後にキングが置かれているマスが $ (a,b) $ となるものを $ 1 $ つ構成して出力してください。この問題の制約下において解は必ず存在することが証明できます。

## 说明/提示

### 制約

- $ 2\ \leq\ H\ \leq\ 100 $
- $ 2\ \leq\ W\ \leq\ 100 $
- $ 1\ \leq\ a\ \leq\ H $
- $ 1\ \leq\ b\ \leq\ W $
- $ (a,\ b)\ \neq\ (1,\ 1) $
- 入力はすべて整数である。

### Sample Explanation 1

キングは $ (1,\ 1)\ \to\ (1,\ 2)\ \to\ (2,\ 1)\ \to\ (2,\ 2)\to\ (3,\ 1)\ \to\ (3,\ 2) $ と移動して、これは確かに $ (3,2) $ を終点とするツアーとなっています。 条件を満たすツアーは他にもいくつかあり、たとえば以下の $ 3 $ つの移動が挙げられます。 - $ (1,\ 1)\ \to\ (1,\ 2)\ \to\ (2,\ 2)\ \to\ (2,\ 1)\ \to\ (3,\ 1)\ \to\ (3,\ 2) $ - $ (1,\ 1)\ \to\ (2,\ 1)\ \to\ (1,\ 2)\ \to\ (2,\ 2)\ \to\ (3,\ 1)\ \to\ (3,\ 2) $ - $ (1,\ 1)\ \to\ (2,\ 2)\ \to\ (1,\ 2)\ \to\ (2,\ 1)\ \to\ (3,\ 1)\ \to\ (3,\ 2) $

## 样例 #1

### 输入

```
3 2 3 2```

### 输出

```
1 1
1 2
2 1
2 2
3 1
3 2```

# 题解

## 作者：TKXZ133 (赞：7)

[King's Tour](https://www.luogu.com.cn/problem/AT_abc232_h)

### 题面大意

在 $n\times m$ 的网格中构造一种从 $(1,1)$ 走到 $(a,b)$ 的方案，要求经过所有格子恰好一次，格子之间八联通。

### 思路分析

模拟赛题，赛时写了一个半小时过了（

思路不是很复杂，但是需要一些分类讨论。

---

- 引理：对于任意大小的矩形，一定存在从左上走到右下的方案。

- 证明：

若长宽中有一个是奇数，那么我们可以按照如下方案构造：

![](https://user-images.githubusercontent.com/110758650/274826940-d4c7e746-d2c8-49dc-ade6-04e7d57c3725.png)

否则，我们可以按照如下方案构造：

![](https://user-images.githubusercontent.com/110758650/274826964-a719f1a7-984e-4d56-a6d4-1a5bf9cc61d0.png)

---

那么同理，我们只需要将矩形翻转就可以得到从矩形一个角走到对角的方案。

设 `walk(x1, y1, x2, y2)` 表示输出从 $(x_1,y_1)$ 走到 $(x_2,y_2)$，填满以 $(x_1,y_1)$ 和 $(x_2,y_2)$ 作为对角线的矩形的方案。

而当我们考虑从 $(1,1)$ 走到 $(a,b)$ 时，我们进行分类讨论，下面是图示和代码实现：

（蓝色边表示用引理的方案填满整个矩形，绿色边表示实际走的边。）

- $a=n,b=m$：

![](https://user-images.githubusercontent.com/110758650/274827041-d380f960-8143-4c61-9b55-af72cadb7b07.png)

```cpp
walk(1, 1, a, b)
```

- $a=1,b=m$：

![](https://user-images.githubusercontent.com/110758650/274827033-fc7e1e76-edcd-4a50-ae9e-17588c48e5a4.png)

```cpp
walk(1, 1, n, m - 1);
walk(n, m, a, b);
```

- $a=n,b=1$：

![](https://user-images.githubusercontent.com/110758650/274827024-fea9901b-f1ff-4ff0-a2ea-299d17f6f818.png)

```cpp
walk(1, 1, n - 1, m);
walk(n, m, a, b);
```

- $a=1,b\not =m$：

![](https://user-images.githubusercontent.com/110758650/274826972-02ddc788-572e-4735-b2c7-b99ebf283626.png)

```cpp
walk(1, 1, n, b - 1);
walk(n, b, 2, m);
walk(1, m, a, b);
```

- $b=1,a\not =n$：

![](https://user-images.githubusercontent.com/110758650/274826995-199a9f30-2460-40cb-ad54-b2e408c0ada9.png)

```cpp
walk(1, 1, a - 1, m);
walk(a, m, n, 2);
walk(n, 1, a, b);
```

- $a=n,b\not =1$：

![](https://user-images.githubusercontent.com/110758650/274826982-c49e5b28-7227-4222-890e-65f3a2fef516.png)

```cpp
walk(1, 1, n, b - 1);
walk(n - 1, b, 1, b);
walk(1, b + 1, n - 1, m);
walk(n, m, a, b);
```

- $b=m,a\not =1$：

![](https://user-images.githubusercontent.com/110758650/274827013-fbaa5250-dabd-4585-b92d-43c925af6b5c.png)

```cpp
walk(1, 1, a - 1, m);
walk(a, m - 1, n - 1, 1);
walk(n, 1, n, m);
walk(n - 1, m, a, b);
```

- $a\in[2,n-1],b\in[2,m-1]$：

![](https://user-images.githubusercontent.com/110758650/274827057-3c31d98b-e746-4283-9927-f6e31eb12a66.png)

```cpp
walk(1, 1, a - 1, m);
walk(a, m, n, b + 1);
walk(n, b, a + 1, 1);
walk(a, 1, a, b);
```

那么这题就愉快的结束了，时间复杂度显然是 $O(n^2)$。

### 代码

（109 行，3.5k）

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int N = 200200;
#define inf 0x3f3f3f3f

int n, m, a, b;

namespace SOL{
    void walk(int x1, int y1, int x2, int y2){
        int dir;
        if (x1 <= x2 && y1 <= y2) dir = 1;
        if (x1 > x2 && y1 <= y2) dir = 3;
        if (x1 <= x2 && y1 > y2) dir = 2;
        if (x1 > x2 && y1 > y2) dir = 4;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        int n = x2 - x1 + 1, m = y2 - y1 + 1;
        vector <pair<int, int>> v; 
        if ((n & 1) || (m & 1)) {
            if (n & 1) {
                int x = 1, y = 0, d = 1;
                for (int i = 1; i <= n * m; i ++) {
                    y += d;
                    if (y == m + 1) y = m, x ++, d = -d;
                    if (y == 0)  y = 1, x ++, d = -d;
                    v.push_back({x, y});
                }
            }
            else {
                int x = 0, y = 1, d = 1;
                for (int i = 1; i <= n * m; i ++) {
                    x += d;
                    if (x == n + 1) x = n, y ++, d = -d;
                    if (x == 0)  x = 1, y ++, d = -d;
                    v.push_back({x, y});
                }
            }
        }
        else {
            int x = 1, y = 0, d = 1;
            for (int i = 1; i <= (n - 2) * m; i ++) {
                y += d;
                if (y == m + 1) y = m, x ++, d = -d;
                if (y == 0)  y = 1, x ++, d = -d;
                v.push_back({x, y});
            }
            for (int i = 1; i <= m; i ++) {
                v.push_back({n - 1, i});
                v.push_back({n, i});
            } 
        }
        if (dir == 2) for (auto &it : v) it.second = m - it.second + 1;
        if (dir == 3) for (auto &it : v) it.first = n - it.first + 1;
        if (dir == 4) for (auto &it : v) it.first = n - it.first + 1, it.second = m - it.second + 1;
        for (auto it : v) cout << it.first + x1 - 1 << ' ' << it.second + y1 - 1 << '\n';
    }
    void work(){
        if (a == n && b == m) {
            walk(1, 1, n, m);
        }
        else if (a == n && b == 1) {
            walk(1, 1, n - 1, m);
            walk(n, m, a, b);
        }
        else if (a == 1 && b == m) {
            walk(1, 1, n, m - 1);
            walk(n, m, a, b);
        }
        else if (a == 1) {
            walk(1, 1, n, b - 1);
            walk(n, b, 2, m);
            walk(1, m, a, b);
        } 
        else if (b == m) {
            walk(1, 1, a - 1, m);
            walk(a, m - 1, n - 1, 1);
            walk(n, 1, n, m);
            walk(n - 1, m, a, b);
        }
        else if (a == n) {
            walk(1, 1, n, b - 1);
            walk(n - 1, b, 1, b);
            walk(1, b + 1, n - 1, m);
            walk(n, m, a, b);
        }
        else if (b == 1) {
            walk(1, 1, a - 1, m);
            walk(a, m, n, 2);
            walk(n, 1, a, b);
        }
        else {
            walk(1, 1, a - 1, m);
            walk(a, m, n, b + 1);
            walk(n, b, a + 1, 1);
            walk(a, 1, a, b);
        }
    }
}

int main(){
    scanf("%d %d %d %d", &n, &m, &a, &b);
    return SOL::work(), 0;
}
```

---

## 作者：qianxinyu (赞：3)

# [[ABC232H] King's Tour ](https://www.luogu.com.cn/problem/AT_abc232_h)

## 题目大意
在 $ h \times w $ 的棋盘了，构造一条从 $(1,1)$ 到 $(a,b)$ 的路，使它经过棋盘所有格子，且每个格子只经过一次。

## 思路
可以想到一种 $h=2$ 时的构造。


如果从起点开始先向下，再向右上。

这样可以完成一列。

然后重复几次。我们就可以到达终点附近。

在这里后我们往空的那个位子走。

这时只有两行，终点在下面，绕一圈就可以解决。

终点位置在上面也是一样的。

代码：
```cpp
if(h==2)
{
    for(int i=1;i<=b-1;i++)push(1,i),push(2,i);
    push(3-a,b);
    for(int i=b+1;i<=w;i++)push(1,i);
    for(int i=w;i>=b+1;i--)push(2,i);
    push(a,b);
    return;
}
```
然后，当 $w=2$ 时，我们可以换一下长和宽起到相同的效果。

代码：
```cpp
int now=cnt;
solve(w,h,b,a);
for(int i=now+1,q;i<=cnt;i++)q=X[i],X[i]=Y[i],Y[i]=q;
```

如果没有等于 $2$ 的，那怎么处理呢？

其实可以往竖直下跑一段路，到底后转弯，构成另一个相似于初始状态的情况。

把这里的可以把下面到的点看成起点。然后重复相同的操作。

等到只有两列时开始进行，一开始的特殊操作。

但是会有特殊情况，~~其实并不特殊~~。

也就是向下时发现终点挡路了，可是我们又不能提前经过终点。

不过我们可以换一个方向，让它向下不经过终点。

可以证明大于 $2$ 的方格中不会有两个方向都行不通的方案。
且官方保证必有解。

在执行代码时，我们可以在处理子方阵假装从 $(1,1)$ 开始，处理完后再整体修改。

也就是在处理完下一级后，挨个修该其位子，使它符合上一级

代码：
```cpp
int now=cnt;
solve(h,w-1,h+1-a,b-1);
for(int i=now+1;i<=cnt;i++)X[i]=h+1-X[i],Y[i]++;
```
处理向下。
```
int now=cnt;
solve(w,h,b,a);
for(int i=now+1,q;i<=cnt;i++)q=X[i],X[i]=Y[i],Y[i]=q;
```
处理换方向。

## 整理成完整代码
```cpp
#include"cstdio"
int h,w,a,b;
int X[20010],Y[20010],cnt;
void push(int x,int y)
{
    X[++cnt]=x;Y[cnt]=y;
}
void solve(int h,int w,int a,int b)
{
    if(h==2)
    {
        for(int i=1;i<=b-1;i++)push(1,i),push(2,i);
        push(3-a,b);
        for(int i=b+1;i<=w;i++)push(1,i);
        for(int i=w;i>=b+1;i--)push(2,i);
        push(a,b);
        return;
    }
    if(h>2&&w==2||b==1||a==h&&b==2)
    {
        int now=cnt;
        solve(w,h,b,a);
        for(int i=now+1,q;i<=cnt;i++)q=X[i],X[i]=Y[i],Y[i]=q;
        return;
    }
    for(int i=1;i<=h;i++)push(i,1);
    int now=cnt;
    solve(h,w-1,h+1-a,b-1);
    for(int i=now+1;i<=cnt;i++)X[i]=h+1-X[i],Y[i]++;
    return;
}
int main()
{
    scanf("%d%d%d%d",&h,&w,&a,&b);
    solve(h,w,a,b);
    for(int i=1;i<=cnt;i++)
    {
        printf("%d %d\n",X[i],Y[i]);
    }
    return 0;
}
```


---

## 作者：sunzz3183 (赞：3)

# [ABC232H] King's Tour 题解

## 题意

[见题目](https://www.luogu.com.cn/problem/AT_abc232_h)

## 分析

我们先考虑 $a=h,b=w$ 的情况。显然，对于任意的 $h,w$ 都可以通过下图的方法走到：

![](https://cdn.luogu.com.cn/upload/image_hosting/lu18t1kr.png)

但是这个代码不好写，我们考虑换一种方法：

显然对于 $h$ 或 $w$ 为奇数的情况，我们可以这样走：

![](https://cdn.luogu.com.cn/upload/image_hosting/g7h0eqze.png)

而对于 $h,w$ 都为偶数的情况，我们需要这样走：

![](https://cdn.luogu.com.cn/upload/image_hosting/xvqj6r33.png)

于是，我们可以写出代码：

```cpp
int x=sx,y=sy;
if((ty-sy+1)&1){
    for(;y<=ty;y++){
        if(x==tx){for(;x>=sx;x--)printf("%lld %lld\n",x,y);x++;}
        else {for(;x<=tx;x++)printf("%lld %lld\n",x,y);x--;}
    }
}
else if((tx-sx+1)&1){
    for(;x<=tx;x++){
        if(y==ty){for(;y>=sy;y--)printf("%lld %lld\n",x,y);y++;}
        else {for(;y<=ty;y++)printf("%lld %lld\n",x,y);y--;}
    }
}
else{
    for(;y<=ty-2;y++){
        if(x==tx){for(;x>=sx;x--)printf("%lld %lld\n",x,y);x++;}
        else {for(;x<=tx;x++)printf("%lld %lld\n",x,y);x--;}
    }
    printf("%lld %lld\n",x,y);
    while(x!=tx||y!=ty){
        if(y==ty)x++,y--;
        else y++;
        printf("%lld %lld\n",x,y);
    }
}
```

然后我们考虑，对于其他任意一种情况，我们可以把图切割成几个矩形，然后对每个矩形考虑，从一个角走到对角，最后使得从 $(1,1)$ 走到 $(a,b)$。

我们对 $(a,b)$ 的位置分类考虑：

首先，是 $(a,b)$ 在角上

- $a=h,b=w$ 见上图。

- $a=1,b=w$ 或 $a=h,b=1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/rp4ixtq9.png)

其次，$(a,b)$ 在边上

- $a=1$ 或 $b=1$：

![](https://pic.imgdb.cn/item/6528d6b3c458853aefcaaa62.png)

- $a=h$ 或 $b=w$：

![](https://pic.imgdb.cn/item/6528d6b1c458853aefcaa365.png)

最后其他情况：

![](https://pic.imgdb.cn/item/6528d72ac458853aefcc44d8.png)

由此，我们可以用矩形拼合来求出来方案。

## 代码

注意：由于另外几种情况，导致矩形走的方向（比如还可以从左下角走到右上角）不同，所以作者写了 $4$ 种不同方式来处理，本质上都是相同的，只不过是复制粘贴然后更改一些细节而已。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
int h,w,a,b;
inline void letgo(int sx,int sy,int tx,int ty){
    if(sy<=ty&&sx<=tx){//左上到右下
        int x=sx,y=sy;
        if((ty-sy+1)&1){
            for(;y<=ty;y++){
                if(x==tx){for(;x>=sx;x--)printf("%lld %lld\n",x,y);x++;}
                else {for(;x<=tx;x++)printf("%lld %lld\n",x,y);x--;}
            }
        }
        else if((tx-sx+1)&1){
            for(;x<=tx;x++){
                if(y==ty){for(;y>=sy;y--)printf("%lld %lld\n",x,y);y++;}
                else {for(;y<=ty;y++)printf("%lld %lld\n",x,y);y--;}
            }
        }
        else{
            for(;y<=ty-2;y++){
                if(x==tx){for(;x>=sx;x--)printf("%lld %lld\n",x,y);x++;}
                else {for(;x<=tx;x++)printf("%lld %lld\n",x,y);x--;}
            }
            printf("%lld %lld\n",x,y);
            while(x!=tx||y!=ty){
                if(y==ty)x++,y--;
                else y++;
                printf("%lld %lld\n",x,y);
            }
        }
    }
    else if(sy>=ty&&sx<=tx){//右上到左下
        int x=sx,y=sy;
        if((sy-ty+1)&1){
            for(;y>=ty;y--){
                if(x==tx){for(;x>=sx;x--)printf("%lld %lld\n",x,y);x++;}
                else {for(;x<=tx;x++)printf("%lld %lld\n",x,y);x--;}
            }
        }
        else if((tx-sx+1)&1){
            for(;x<=tx;x++){
                if(y==ty){for(;y<=sy;y++)printf("%lld %lld\n",x,y);y--;}
                else {for(;y>=ty;y--)printf("%lld %lld\n",x,y);y++;}
            }
        }
        else{
            for(;y>=ty+2;y--){
                if(x==tx){for(;x>=sx;x--)printf("%lld %lld\n",x,y);x++;}
                else {for(;x<=tx;x++)printf("%lld %lld\n",x,y);x--;}
            }
            printf("%lld %lld\n",x,y);
            while(x!=tx||y!=ty){
                if(y==ty)x++,y++;
                else y--;
                printf("%lld %lld\n",x,y);
            }
        }
    }
    else if(sy<=ty&&sx>=tx){//左下到右上
        int x=sx,y=sy;
        if((ty-sy+1)&1){
            for(;y<=ty;y++){
                if(x==tx){for(;x<=sx;x++)printf("%lld %lld\n",x,y);x--;}
                else {for(;x>=tx;x--)printf("%lld %lld\n",x,y);x++;}
            }
        }
        else if((sx-tx+1)&1){
            for(;x>=tx;x--){
                if(y==ty){for(;y>=sy;y--)printf("%lld %lld\n",x,y);y++;}
                else {for(;y<=ty;y++)printf("%lld %lld\n",x,y);y--;}
            }
        }
        else{
            for(;y<=ty-2;y++){
                if(x==tx){for(;x<=sx;x++)printf("%lld %lld\n",x,y);x--;}
                else {for(;x>=tx;x--)printf("%lld %lld\n",x,y);x++;}
            }
            printf("%lld %lld\n",x,y);
            while(x!=tx||y!=ty){
                if(y==ty)x--,y--;
                else y++;
                printf("%lld %lld\n",x,y);
            }
        }
    }
    else if(sy>=ty&&sx>=tx){//右下到左上
        int x=sx,y=sy;
        if((sy-ty+1)&1){
            for(;y>=ty;y--){
                if(x==tx){for(;x<=sx;x++)printf("%lld %lld\n",x,y);x--;}
                else {for(;x>=tx;x--)printf("%lld %lld\n",x,y);x++;}
            }
        }
        else if((sx-tx+1)&1){
            for(;x>=tx;x--){
                if(y==ty){for(;y<=sy;y++)printf("%lld %lld\n",x,y);y--;}
                else {for(;y>=ty;y--)printf("%lld %lld\n",x,y);y++;}
            }
        }
        else{
            for(;y>=ty+2;y--){
                if(x==tx){for(;x<=sx;x++)printf("%lld %lld\n",x,y);x--;}
                else {for(;x>=tx;x--)printf("%lld %lld\n",x,y);x++;}
            }
            printf("%lld %lld\n",x,y);
            while(x!=tx||y!=ty){
                if(y==ty)x--,y++;
                else y--;
                printf("%lld %lld\n",x,y);
            }
        }
    }
    return;
}
signed main(){
    h=read();w=read();a=read();b=read();
    if(a==h&&b==w){
        letgo(1,1,a,b);
        return 0;
    }
    if(a==h&&b==1){
        letgo(1,1,1,w);
        letgo(2,w,a,b);
        return 0;    
    }
    if(a==1&&b==w){
        letgo(1,1,h,1);
        letgo(h,2,a,b);
        return 0;
    }
    if(a==1){
        letgo(1,1,h,b-1);
        letgo(h,b,2,w);
        letgo(1,w,a,b);
        return 0;
    }
    if(b==1){
        letgo(1,1,a-1,w);
        letgo(a,w,h,2);
        letgo(h,1,a,b);
        return 0;
    }
    if(a==h){
        letgo(1,1,h,b-1);
        letgo(h-1,b,1,b);
        letgo(1,b+1,h-1,w);
        letgo(h,w,a,b);
        return 0;
    }
    if(b==w){
        letgo(1,1,a-1,w);
        letgo(a,w-1,a,1);
        letgo(a+1,1,h,w-1);
        letgo(h,w,a,b);
        return 0;
    }
    letgo(1,1,h,b-1);
    letgo(h,b,a+1,w);
    letgo(a,w,1,b+1);
    letgo(1,b,a,b);
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

神经病构造题。

题目没告诉你无解该咋办，所以肯定有解。所以我们可以直接做这样一个假设：给定任何一个 $n \times m$ 的网格，可以从 $(1,1)$ 走到 $\forall (i,j) \neq (1,1)$。

其他题解都是神秘构造，我们考虑归纳。也就是说，不断地让 $n$ 或 $m$ 减少 $1$，并且保证有解。

当 $n$ 或 $m$ 等于 $2$ 时（归纳奠基），考虑证明一定有解。这个就是分类讨论几下就行：

![](https://s21.ax1x.com/2025/05/06/pEqjasH.png)

![](https://s21.ax1x.com/2025/05/06/pEqjdLd.md.png)

![](https://s21.ax1x.com/2025/05/06/pEqjBdI.md.png)

![](https://s21.ax1x.com/2025/05/06/pEqjDot.png)

当 $n,m \ge 3$ 的时候，如果点离上或左（认为 $(1,1)$ 在左上角）边界中的一个距离 $\ge 2$，就可以直接归纳。

否则，发现只剩下 $(1,2)$、$(2,1)$、$(2,2)$，还是能够直接归纳。

所以设 `solve(n,m,px,py)` 表示处理 $n \times m$ 的矩形，从 $(1,1) \to (px,py)$ 的一个解，返回路径。递归的时候旋转拼凑一下即可。

考虑分析一下复杂度。会递归 $n+m$ 层，所以暴力复杂度为 $O(n^3)$，哎还行吧。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
int n,m,px,py; 
vector<pair<int,int>> solve(int n,int m,int px,int py) {
	if(n==2) {
		vector<pair<int,int>> ans;
		if(px==1&&py%2==0) {
			ans.push_back({1,1});
			ans.push_back({2,1});
			int tpos=2;
			while(tpos<py) ans.push_back({2,tpos}),ans.push_back({1,tpos}),tpos++,ans.push_back({1,tpos}),ans.push_back({2,tpos}),tpos++;
			ffor(i,tpos,m) ans.push_back({2,i});
			roff(i,m,tpos) ans.push_back({1,i});
		}
		else if(px==1&&py%2==1) {
			ans.push_back({1,1});
			ans.push_back({2,1});
			ans.push_back({1,2});
			ans.push_back({2,2});
			int tpos=3;
			while(tpos<py) ans.push_back({2,tpos}),ans.push_back({1,tpos}),tpos++,ans.push_back({1,tpos}),ans.push_back({2,tpos}),tpos++;
			ffor(i,tpos,m) ans.push_back({2,i});
			roff(i,m,tpos) ans.push_back({1,i});
		}
		else if(px==2&&py%2==0) {
			ans.push_back({1,1});
			ans.push_back({2,1});
			ans.push_back({1,2});
			int tpos=2;
			while(tpos<py) ans.push_back({2,tpos}),tpos++,ans.push_back({2,tpos}),ans.push_back({1,tpos}),tpos++,ans.push_back({1,tpos});	
			ffor(i,tpos+1,m) ans.push_back({1,i});
			roff(i,m,tpos) ans.push_back({2,i});
		}
		else {
			int tpos=1;
			ans.push_back({1,1});
			while(tpos<py) ans.push_back({2,tpos}),tpos++,ans.push_back({2,tpos}),ans.push_back({1,tpos}),tpos++,ans.push_back({1,tpos});
			ffor(i,tpos+1,m) ans.push_back({1,i});
			roff(i,m,tpos) ans.push_back({2,i});	
		}
		return ans;
	}
	else if(m==2) {
		auto vc=solve(m,n,py,px);
		ffor(i,0,vc.size()-1) swap(vc[i].first,vc[i].second);
		return vc;	
	}
	if(px>2||px==2&&py==2||px==2&&py==1) {
		vector<pair<int,int>> ans;
		auto vc=solve(n-1,m,px-1,m-py+1);
		ffor(i,1,m) ans.push_back({1,i});
		for(auto pr:vc) ans.push_back({pr.first+1,m-pr.second+1});
		return ans;
	}
	if(py>2||px==1&&py==2) {
		vector<pair<int,int>> ans;
		auto vc=solve(n,m-1,n-px+1,py-1);
		ffor(i,1,n) ans.push_back({i,1});
		for(auto pr:vc) ans.push_back({n-pr.first+1,pr.second+1});	
		return ans;
	}
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>px>>py;
	vector<pair<int,int>> ans=solve(n,m,px,py);
	for(auto pr:ans) cout<<pr.first<<' '<<pr.second<<'\n';
//	assert(st.size()==n*m&&ans.size()==n*m);
	return 0;
}
```

---

## 作者：Presentation_Emitter (赞：0)

~~其实下面做法比官方题解复杂很多，因为是赛时思路。~~

## 题意

一个夫乔巴尔戈在 $(1,1)$，他每次可以走到八连通的格子，求他遍历所有格子并最终到达 $(a,b)$ 处的一种可行方案。

## 正文

对终点的位置分类讨论。如图：![](https://cdn.luogu.com.cn/upload/image_hosting/k8qy620u.png)

为方便起见，若 $b=1$ 或 $a=h$（即 `F,G,H`），则翻转横纵坐标，这样就只剩下 `A~E` 五类了。

接下来我们定义两种矩阵：

- `H` 型：起点与终点同侧，即下图与下图经过若干次翻转后的所有结果。记起点与终点的距离为 $d$。`S` 表示起点，`E` 表示终点，保证起点与终点都在角落，下同。

|S|$\ \ $|E|
|:-:|:-:|:-:|:-:|
|$\ $|$\ $|$\ $|
|$\ $|$\ $|$\ $|

- `T` 型：起点与终点异侧。记起点与终点的水平距离为 $d$。

|S|$\ \ $|$\ \ $|
|:-:|:-:|:-:|:-:|
|$\ $|$\ $|$\ $|
|$\ $|$\ $|**E**|

不难发现：所有 $d \ge 2$ 的 `H` 型与所有 `T` 型均有从起点到终点且遍历所有格子的方案。

具体而言：

- 所有 $d \ge 2$ 的 `H` 型都可以拆成两个 `T` 型；
- 所有 $d \ge 3$ 的 `T` 型可以拆成若干个 $d=2$ 的 `H` 型和一个 $d \le 2$ 的 `T` 型；
- $d=2$ 的 `H` 型与 $d=1$ 的 `T` 型方案显然。$d=2$ 的一种 `T` 型方案如下（`R` 表示右，`LU` 表示左上，其它 `T` 型方案显然）：

|[R]|$E$|
|:-:|:-:|
|**...**|**...**|
|**[R]**|**[LU]**|
|$S$**[R]**|**[LU]**|

将所有 $5$ 类分成若干个 `H` 和 `T` 的矩阵。

- `A` 类（红表示 $(1,1)$，橙表示 $(a,b)$，数字表示遍历顺序，下同）：

![](https://cdn.luogu.com.cn/upload/image_hosting/kl75ho6q.png)

- `B` 类：显然是一个 `H` 型。

- `C` 类：显然是一个 `T` 型。

- `D` 类：显然分成 `T1+H2`。

- `E` 类：

![](https://cdn.luogu.com.cn/upload/image_hosting/4mu5g001.png)

为了处理方便，可以把所有 `H` 拆成 `T`。

Code:

```cpp
ll h,w,a,b,x[10005],y[10005],c,f;il void mv(ll a,ll b){x[++c]=a,y[c]=b;}
il void tra(ll x1,ll y1,ll x2,ll y2)
{
	ll d1=x2-1,d2=y1-1,l1=x1-x2+1,l2=y2-y1+1,d=l2-2*!(l2&1);
	for(int i=2;i<=d;i+=2)
	{
		for(int j=l1;j>=1;--j)mv(j+d1,i+d2-1);
		for(int j=1;j<=l1;++j)mv(j+d1,i+d2);
	}
	if(l2&1)for(int i=x1;i>=x2;--i)mv(i,y2);
	else for(int i=x1;i>=x2;--i)mv(i,y2-1),mv(i,y2);
}
il void trb(ll x1,ll y1,ll x2,ll y2)
{
	ll d1=x1-1,d2=y1-1,l1=x2-x1+1,l2=y2-y1+1,d=l2-2*!(l2&1);
	for(int i=2;i<=d;i+=2)
	{
		for(int j=1;j<=l1;++j)mv(j+d1,i+d2-1);
		for(int j=l1;j>=1;--j)mv(j+d1,i+d2);
	}
	if(d&1)for(int i=x1;i<=x2;++i)mv(i,y2);
	else for(int i=x1;i<=x2;++i)mv(i,y2-1),mv(i,y2);
}
il void trc(ll x1,ll y1,ll x2,ll y2)
{
	ll tmp=c+1;swap(x1,x2);swap(y1,y2);tra(x1,y1,x2,y2);
	reverse(x+tmp,x+c+1);reverse(y+tmp,y+c+1);
}
il void trd(ll x1,ll y1,ll x2,ll y2)
{
	ll tmp=c+1;swap(x1,x2);swap(y1,y2);trb(x1,y1,x2,y2);
	reverse(x+tmp,x+c+1);reverse(y+tmp,y+c+1);
}
il void wka(){trb(1,1,h,b-1);tra(h,b,a+1,w);trd(a,w,1,b+1);trc(1,b,a,b);}
il void wkd(){trb(1,1,h,b-1);tra(h,b,a+1,w);trc(a,w,a,b);}
il void wke()
{trb(1,1,a-1,b);trc(a,b-1,a,1);trb(a+1,1,h,w-1);tra(h,w,a,b);}
int main()
{
	h=rd();w=rd();a=rd();b=rd();
	if(b==1||a==h)swap(a,b),swap(h,w),f=1;
	if(a>1&&b<w)cerr<<"A",wka();
	else if(a==1&&b==w)cerr<<"B",trb(1,1,h,w-1),tra(h,w,a,b);
	else if(a==h&&b==w)cerr<<"C",trb(1,1,a,b);
	else if(a==1&&b<w)cerr<<"D",wkd();
	else if(a>1&&b==w)cerr<<"E",wke();
	if(f)for(int i=1;i<=c;++i)prt(y[i],' '),prt(x[i]);
	else for(int i=1;i<=c;++i)prt(x[i],' '),prt(y[i]);
	ret 0;
}
```

## Reference

- [lowiro. Arcaea - New Dimension Rhythm Game](https://arcaea.lowiro.com)

---

