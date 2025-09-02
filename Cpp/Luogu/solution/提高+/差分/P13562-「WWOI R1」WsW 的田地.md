# 「WWOI R1」WsW 的田地

## 题目背景

WsW 是会开心和生气的。

## 题目描述

WsW 和 bln 分别有一块田地。这两块田地都由 $n\times m$ 个格子组成，其中左上角格子的坐标为 $(1,1)$，右下角格子的坐标为 $(n,m)$。  

最开始，WsW 的田地里坐标为 $(x,y)$ 的格子中长着一株生长度为 $a_{x,y}$ 的禾苗；bln 的田地里坐标为 $(x,y)$ 的格子中长着一株生长度为 $b_{x,y}$ 的禾苗。  

在之后的每一天的开始，都会有一个小精灵在 **WsW 或 bln 的田地**中坐标为 $(x_0,y_0)$ 的格子上使用药水，药水分为三种：

- 药水 $1$，包括 $3$ 个参数，可以使这片田地内满足 $x=x_0$ **或** $y=y_0$ 的格子 $(x,y)$ 中禾苗的生长度增加 $k$。  
- 药水 $2$，包括 $5$ 个参数，可以使这片田地内满足 $x_0\le x\le x_0+u$ 且 $y_0\le y\le y_0+v$ 的格子 $(x,y)$ 中禾苗的生长度增加 $k$。  
- 药水 $3$，包括 $5$ 个参数，可以使这片田地内满足 $x_0\le x\le x_0+u$ 且 $y_0+x-x_0\le y\le y_0+x-x_0+v$ 的格子 $(x,y)$ 中禾苗的生长度增加 $k$。  

药水不会影响田地外的区域。  
**药水瞬间生效，且效果在一天结束后不会消失。**  

小精灵使用药水后，WsW 会查看自己和 bln 的田地。如果 WsW 的田地与 bln 的田地坐标相同的格子中禾苗的生长度都相等，那么 WsW 将会很开心；否则 WsW 会很生气。  



## 说明/提示

### 【样例 1 解释】
红色数字表示当天发生改变的格子中的生长值。  
![](https://cdn.luogu.com.cn/upload/image_hosting/xpcmfh4l.png)

可以发现，只有第 $1$ 天和第 $5$ 天两块田地中对应格子的生长值相同。

### 【数据范围】

**本题采用捆绑测试**。

对于所有测试数据，保证:
* $1\le n,m\le 800$，$1\le q\le 5\times 10^5$。
* 对于所有 $a_{x,y},b_{x,y}$，均有 $|a_{x,y}|,|b_{x,y}|\le 5\times 10^5$。
* $t\in \{1,2,3\}$，$f\in \{0,1\}$。
* $1\le x_0\le n$，$1\le y_0\le m$，$|k| \le 5\times 10^5$，$0\le u\le n$，$0\le v\le m$。  

|子任务编号|$n,m\le$|$q\le$| $\lvert a_{i,j}\rvert,\lvert b_{i,j}\rvert,\lvert k\rvert\le$ |特殊限制|分数|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$| $100$ | $100$ | $100$ |保证没有 $t=3$ 的情况|$10$|
|$2$| ^ | ^ | ^ | 无 |$20$|
|$3$| $800$ | $5\times10^5$ | $5\times10^5$ |保证没有 $t=3$ 的情况|$30$|
|$4$| ^ | ^ | ^ | 无 |$40$|

## 样例 #1

### 输入

```
2 3
1 1 4
5 1 4
0 0 3
5 0 4
5
1 1 1 2 1
1 0 1 1 4
1 1 1 3 4
2 1 2 1 4 0 1
2 0 2 2 4 0 1```

### 输出

```
Happy
Angry
Angry
Angry
Happy```

## 样例 #2

### 输入

```
3 3
1 9 1
9 8 1
3 0 5
3 11 1
9 10 3
3 0 5
1
3 1 1 1 -2 1 1```

### 输出

```
Happy```

# 题解

## 作者：WsW_ (赞：4)

### 前言

这是出题人题解。  

---
### 思路
题意实际上是，给定两个矩阵，每次对矩阵进行一些操作，问每次操作后两个矩阵是否相等。两个矩阵相等，等价于两个矩阵对应位置相减均为 $0$，这样就将两个矩阵上的操作转化为了一个矩阵上的操作。  

想判断一个矩阵是否每个点均为 $0$ 太困难了，我们希望能找到一个更简洁的方法来描述这个矩阵，最好可以只使用一个整数。  
哈希算法就是用于将一个复杂的、不好描述的信息，映射为一个简洁的、容易描述的信息。  

接下来使用随机赋权哈希解决这个问题。  

我们将相减后矩阵上每个点减出来的数字成为这个点上的数值。  
一个很简单的想法是，我们可以将所有数值加起来作为这个矩阵的哈希值，当哈希值为 $0$ 时我们认为矩阵每个位置上的数值均为 $0$。但实际上这样有较大的可能出错，因为每个点对哈希值的影响都是一样的。  
如何让每个点对哈希值的影响不同呢？可以对矩阵的每个点随机赋权，将所有点上数值乘以权值的积加起来，作为哈希值。  
当哈希值为 $0$ 时，这个矩阵大概率每个点上的数值均为 $0$。每个点上的数值均为 $0$ 时，哈希值必定为 $0$。  

我们可以把哈希值为 $0$ 这个必要，但小概率不充分的条件，看做矩阵上每个点的数值均为 $0$ 的充要条件。  

接下来考虑如何求出药水作用区间点的权值之和。  
对于药水 $1$，作用区间是个十字，只需要预处理每行、每列的权值和即可。  
对于药水 $2$，作用区间是个矩形，只需要用二维前缀和计算即可。  
对于药水 $3$，作用区间是个平行四边形，可以将第 $i$ 行向左平移 $i$ 个单位，发现作用区间就变成了矩形。只需要在平移后的矩阵上用二维前缀和计算即可。下图中用红色表示药水 $3$ 的作用区间，以及其平移后的样子。  
![](https://cdn.luogu.com.cn/upload/image_hosting/qbgdnhou.png)

时间复杂度为 $O(nm+q)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n,m,q;
ull p[805][805];
ull sum[2][805][1605];
ull now;
mt19937_64 rng(time(0));

ull getsum(int xx,int yy,int x,int y,bool f){
	xx=min(n,xx); x=min(n,x);
	yy=min(m+n,yy); y=min(m+n,y);
	return sum[f][xx][yy]+sum[f][x-1][y-1]-sum[f][xx][y-1]-sum[f][x-1][yy];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			p[i][j]=rng();
			int x; cin>>x;
			now+=x*p[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x; cin>>x;
			now-=x*p[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m+n;j++){
			sum[0][i][j]=p[i][j]+sum[0][i-1][j]+sum[0][i][j-1]-sum[0][i-1][j-1];
			sum[1][i][j-i+n]=p[i][j]+sum[1][i-1][j-i+n]+sum[1][i][j-i+n-1]-sum[1][i-1][j-i+n-1];
		}
	}
	cin>>q;
	while(q--){
		int t,f,x0,y0,k;
		cin>>t>>f>>x0>>y0>>k;
		f=(f?-1:1);
		if(t==1)now+=(getsum(x0,m,x0,1,0)+getsum(n,y0,1,y0,0)-p[x0][y0])*f*k;
		if(t==2){
			int u,v;cin>>u>>v;
			now+=getsum(x0+u,y0+v,x0,y0,0)*f*k;
		}
		if(t==3){
			int u,v;cin>>u>>v;
			now+=getsum(x0+u,y0+v+n-x0,x0,y0+n-x0,1)*f*k;
		}
		if(now)cout<<"Angry";
		else cout<<"Happy";
		if(q)cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Manki23333333 (赞：0)

> 文章名称：基于异形前缀和的异形图形优化。
>
>  类别：题解。
>
>  属于：P13562 「WWOI R1」WsW 的田地。

---

#### 简化题意

给定三个对矩阵的操作。

- 将一个极大的十字架增加 $k$。
- 将一个矩形增加 $k$。
- 将一个平行四边形增加 $k$。

#### 说在前面

本做法不需要哈希，使用异形前缀和维护。

#### 大致思路

如果我们考虑这样的前缀和 / 差分：

$$s_{i, j} = s_{i - 1, j - 1} + a_{i, j}\\
c_{i,j} = a_{i-1,j-1} - a_{i, j}$$

那么维护平行四边形将极为方便。

具体地，我们在此差分下如此维护平行四边形：

![](https://cdn.luogu.com.cn/upload/image_hosting/xzj96jst.png)

而我们在差分下如此维护矩形：

![](https://cdn.luogu.com.cn/upload/image_hosting/sdfeephq.png)

而十字只需要三个矩形拼起来即可。

不难注意到，这些只需要维护矩阵上的矩形就可以了。

那么我们在此差分的基础上进行普通的二维差分即可。

关于输出答案，数组全为 $0$ 当且仅当差分数组也全为 $0$，无论多少阶。所以我们在单点修改的时候顺便记录有多少个 $0$，当 $0$ 的个数等于 $mn$ 就说明可以。

时间复杂度 $O(mn+qk)$，其中 $k$ 是较大的常数，本实现中 $k=8$。（尽管如此，本做法仍然需要卡常才能通过本题。）

#### Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

int n, m, a [805] [805], x, sum [805] [805], s [805] [805];
int ans = 0;
void add (int x, int y, int k) {
    if (x < 1 || x > n || y < 1 || y > m) return ;
    if (s [x] [y] == 0) ans --;
    s [x] [y] += k;
    if (s [x] [y] == 0) ans ++;
}
void rec (int sx, int sy, int ex, int ey, int k) {
    add (sx, sy, k);
    add (sx + 1, sy + 1, -k);
    add (ex + 1, sy, -k);
    add (ex + 2, sy + 1, k);
    add (sx, ey + 1, -k);
    add (sx + 1, ey + 2, k);
    add (ex + 1, ey + 1, k);
    add (ex + 2, ey + 2, -k);
}
void cp (int sx, int sy, int w, int h, int k) {
    add (sx, sy, k);
    add (sx, sy + w + 1, -k);
    add (sx + 1, sy, -k);
    add (sx + 1, sy + w + 1, k);
    add (sx + h + 1, sy + w + 1, -k);
    add (sx + h + 2, sy + w + 1, k);
    add (sx + h + 1, sy + w + h + 2, k);
    add (sx + h + 2, sy + w + h + 2, -k);
}
void Turn () {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i ++)
        for (int j = 1 ; j <= m ; j ++) {
            cin >> x;
            a [i] [j] += x;
        }
    for (int i = 1 ; i <= n ; i ++)
        for (int j = 1 ; j <= m ; j ++) {
            cin >> x;
            a [i] [j] -= x;
            sum [i] [j] = a [i] [j] - a [i - 1] [j - 1];
            s [i] [j] = sum [i] [j] - sum [i - 1] [j] - sum [i] [j - 1] + sum [i - 1] [j - 1];
            if (s [i] [j] == 0) ans ++;
        }
    int q; cin >> q;
    while (q --) {
        int t, f, x0, y0, k, u, v;
        // for (int i = 1 ; i <= n ; i ++) {
        //     for (int j = 1 ; j <= m ; j ++) {
        //         cout << s [i] [j] << ", ";
        //     }
        //     cout << endl;
        // }
        cin >> t >> f;
        if (t == 1) {
            cin >> x0 >> y0 >> k;
            k *= 1 - 2 * f;
            rec (x0, 1, x0, m, k);
            rec (1, y0, n, y0, k);
            rec (x0, y0, x0, y0, -k);
        } else if (t == 2) {
            cin >> x0 >> y0 >> k >> u >> v;
            k *= 1 - 2 * f;
            rec (x0, y0, x0 + u, y0 + v, k);
        } else {
            cin >> x0 >> y0 >> k >> u >> v;
            k *= 1 - 2 * f;
            cp (x0, y0, v, u, k);
        }

        if (ans == n * m) {
            cout << "Happy\n";
        } else {
            cout << "Angry\n";
        }

        // for (int i = 1 ; i <= n ; i ++) {
        //     for (int j = 1 ; j <= m ; j ++) {
        //         cout << s [i] [j] << ", ";
        //     }
        //     cout << endl;
        // }
    }
}

int _; void Init () {
   ios :: sync_with_stdio (0); cin. tie (0); cout. tie (0);  // 卡常
    _ = 1;
//    freopen (".in", "r", stdin);
//    freopen (".out", "w", stdout);
//    cin >> _;
}

    signed main () { Init ();
    while (_ --> 0)
    Turn (); return 0; }
```

---

