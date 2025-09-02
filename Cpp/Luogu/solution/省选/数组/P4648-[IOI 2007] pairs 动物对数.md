# [IOI 2007] pairs 动物对数

## 题目描述

Mirko 和 Slavko 正在玩动物玩具的游戏。 首先，他们要在下图给出的三种玩具模板中选择一种。三种模板分别由一维、二维和三维的网格点（在图中用圆圈表示）组成。 

![](https://cdn.luogu.com.cn/upload/pic/20672.png )

接下来Mirko 把 $N$ 个小动物玩具放到选中的模板的网格点上。

动物玩具可以走一步到达与它相邻的网格点上（在图中相邻的点之间有一条小短线相连）。两个网格点之间的距离定义为**从一个网格点到另一个网格点所需要移动的最小步数**。

如果两个动物之间的距离小于等于$D$，则它们之间可以互相听见。Slavko 的任务是计算在模板上有多少对动物可以互相听得见。

给定模板的类型、所有动物的位置以及数字$D$，写一个程序计算有多少对动物可以互相听得见。 

## 说明/提示

在30分的测试数据中, 动物数目 $N$ 最多是 $1 000$。

如果成功通过了某一种模板（一维、二维或者三维）的全部测试数据，将会得到至少30分。

对于input 1的解释： 假设动物按给出的顺序编号为$1$到$6$。$4$对互相能够听得到的动物分别是:
- 1-5 ( 距离是5)
- 1-6 ( 距离是2)
- 2-3 ( 距离是0)
- 5-6 ( 距离是3)

对于input 2 的解释：$8$对动物分别是:
- 1-2 ( 距离是2)
- 1-4 ( 距离是4)
- 1-5 ( 距离是3)
- 2-3 ( 距离是3)
- 2-4 ( 距离是4)
- 3-4 ( 距离是3)
- 3-5 ( 距离是4)
- 4-5 ( 距离是3)

## 样例 #1

### 输入

```
1 6 5 100 
25 
50 
50 
10 
20 
23 ```

### 输出

```
4```

## 样例 #2

### 输入

```
2 5 4 10 
5 2 
7 2 
8 4 
6 5 
4 4 ```

### 输出

```
8```

## 样例 #3

### 输入

```
3 8 10 20 
10 10 10 
10 10 20 
10 20 10 
10 20 20 
20 10 10 
20 10 20 
20 20 10 
20 20 20 ```

### 输出

```
12```

# 题解

## 作者：圣嘉然 (赞：25)

一个目前没人写在题解区的做法。

$B = 1$ 和 $B = 2$ 的部分就不展开说了，这里放一下一句话题解和代码。

##### $B = 1$ 时：

从前往后扫，维护滑动窗口即可。

```cpp
namespace sub1 {
    const int N = 1e5 + 5;
    int p[N];

    inline void main(int n, int d, int m) {
        for (int i = 1; i <= n; ++i) 
            p[i] = read();
        std::sort(p + 1, p + n + 1);
        i64 res = 0;
        for (int i = 1, j = 1; i <= n; ++i) {
            while (j < i && p[i] - p[j] > d) ++j;
            res += i - j;
        }
        write(res);
    }
}
```

##### $B = 2$ 时：

二维曼哈顿距离转切比雪夫距离，按照 $x$ 排序后维护 $x$ 的滑动窗口，接下来变成 $y$ 这一维的区间求和，可以用 bit 维护。

```cpp
namespace sub2 {
    const int N = 1e5 + 5, M = 75010;
    struct Node {
        int x, y;
    } p[N];

    int c[M * 2];
    inline void upd(int x, int v) {
        for (; x < M * 2; x += x & -x) 
            c[x] += v;
    }
    inline int qry(int x) {
        x = std::min(x, M * 2 - 1);
        int res = 0;
        for (; x > 0; x -= x & -x) 
            res += c[x];
        return res;
    }

    inline void main(int n, int d, int m) {
        for (int i = 1; i <= n; ++i) {
            int x = read(), y = read();
            p[i].x = x + y, p[i].y = x - y; // m -> q 
        }
        std::sort(p + 1, p + n + 1, [&](Node a, Node b) { return a.x < b.x; });
        i64 res = 0;
        for (int i = 1, j = 1; i <= n; ++i) {
            while (j < i && p[i].x - p[j].x > d) upd(p[j].y + m, -1), ++j;
            res += qry(p[i].y + d + m) - qry(p[i].y - d - 1 + m);
            upd(p[i].y + m, 1);
        }
        write(res);
    }
}

```

##### $B = 3$ 时：

因为有了 $B = 2$ 的做法，自然是想着能不能把三维曼哈顿距离转切比雪夫距离。

尝试推广，三维曼哈顿距离如下：

$$
|x1−x2|+|y1−y2|+|z1−z2|
$$

考虑暴力拆出 8 个 max，也就是暴力讨论每个绝对值的正负，这时候你发现三个绝对值全负和全正是一样的，不过是加了一个负号，而切比雪夫的距离公式中包含绝对值，所以可以把两项合并，于是最终两两合并，我们可以得到这个式子就等于：

$$

\max \{
|(x_1 + y_1 + z_1) - (x_2 + y_2 + z_2)|,
|(x_1 + y_1 - z_1) - (x_2 + y_2 - z_2)|,
|(x_1 - y_1 + z_1) - (x_2 - y_2 + z_2)|,
|(x_1 - y_1 - z_1) - (x_2 - y_2 - z_2)|
\}

$$

于是如果将 $(x, y, z)$ 映射到 $(x + y + z, x + y - z, x - y + z, x - y - z)$，那么新的切比雪夫距离就是原来的曼哈顿距离。

按照第一维排序，剩下的问题就是查询一个三维立方体内部点的个数，~~树套树套树~~，考虑三维树状数组维护三维前缀和，查询的时候大力三维差分求立方体内部点个数。

为了让值域更小，可以把最后一维改成 $-x + y + z$，这样我们的值域就是 $[-m, 2m]$ 了。

```cpp
namespace sub3 {
    const int N = 1e5 + 5, M = 83;
    struct Node {
        int a, b, c, d;
    } p[N];
    int c[M * 3][M * 3][M * 3]; // 三维 bit 
    inline void upd(int x, int y, int z, int v) {
        for (int i = x; i < M * 3; i += i & -i) {
            for (int j = y; j < M * 3; j += j & -j) {
                for (int k = z; k < M * 3; k += k & -k) {
                    c[i][j][k] += v;
                }
            }
        }
    }
    inline int qry(int x, int y, int z) {
        x = std::min(x, M * 3 - 1), y = std::min(y, M * 3 - 1), z = std::min(z, M * 3 - 1);
        int res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                for (int k = z; k > 0; k -= k & -k) {
                    res += c[i][j][k];
                }
            }
        }
        return res;
    }
    inline int ask(int lx, int rx, int ly, int ry, int lz, int rz) {
        int res = qry(rx, ry, rz); // 全集 需要减去 左面, 下面, 前面 的并集, 使用容斥
        res -= qry(lx, ry, rz) + qry(rx, ly, rz) + qry(rx, ry, lz);
        res += qry(lx, ly, rz) + qry(lx, ry, lz) + qry(rx, ly, lz);
        res -= qry(lx, ly, lz);
        // bug: 容斥这里写错两次 ... 传进来的就是 -1, 此处不需要 -1, -= 里面应该用 + 连接而非 - 
        return res;
    }

    inline void main(int n, int d, int m) {
        for (int i = 1; i <= n; ++i) {
            int x = read(), y = read(), z = read();
            p[i].a = x + y + z, p[i].b = x + y - z, p[i].c = x - y + z, p[i].d = -x + y + z;
        }
        std::sort(p + 1, p + n + 1, [&](Node a, Node b) { return a.a < b.a; });
        i64 res = 0;
        for (int i = 1, j = 1; i <= n; ++i) {
            while (j < i && p[i].a - p[j].a > d) {
                upd(p[j].b + m, p[j].c + m, p[j].d + m, -1), ++j;
            }
            res += ask(p[i].b - d - 1 + m, p[i].b + d + m, p[i].c - d - 1 + m, p[i].c + d + m, p[i].d - d - 1 + m, p[i].d + d + m);

            upd(p[i].b + m, p[i].c + m, p[i].d + m, 1);
        }
        write(res);
    }
}
```

---

## 作者：Ynoi (赞：18)

很显然是将一维，二维，三维的情况分类讨论

一维：

排序后，维护一个单调指针即可

代码（每一维我写在一个namespace里，Orz就当是这个namespace的主函数，而且我`#define int long long了`下同）

```
    int a[MAXN],d;
    void Orz() {
        scanf("%lld%lld%lld",&n,&d,&m);
        for(int i = 1; i <= n; i ++)
            scanf("%lld",&a[i]);
        sort(a+1,a+n+1);
        int j = 1;
        LL ans = 0;
        for(int i = 1; i <= n; i ++) {
            while(a[i] - a[j] > d && j < i) j ++;
            ans += i-j;
        }
        cout<<ans;
    }

```

二维：
先将曼哈顿距离转化为切比雪夫距离

[不会的见这篇候选队里的日报](https://www.luogu.org/blog/xuxing/Distance-Algorithm)

下面的x,y自动视为在切比雪夫距离下的

之后我们就将点按照y排序

然后扫描每个点

设该点坐标(x,y)

用树状数组维护坐标为对于每个$x_i$, (y-d <= $y_i$)的点数，同时排序后$(x_i,y_i)$要在$(x,y)$前面

然后查询在$[x-d,x+d]$的点数

```
struct aa
    {
        int x,y; 
    }a[MAXN];
    int d;

    bool cmp(aa a,aa b) {
        return a.y < b.y ;
    }

    void rd()
    {
        scanf("%lld%lld%lld",&n,&d,&m);
        for(int i = 1; i <= n; i ++)
        { 
        int x,y;
            scanf("%lld%lld",&x,&y);
            a[i].x = x+y;
            a[i].y = x-y; 
        }
        sort(a+1,a+n+1,cmp);
    }

    int c[MAXN*2];
    void jia(int x,int y)
    {
        while(x <= 2*m) {
            c[x] += y;
            x += lowbit(x);
        }
    }

    int he(int x)
    {
    	if(x > 2*m) x = 2*m; 
        int ans = 0;
        while(x > 0) {
            ans += c[x];
            x -= lowbit(x);
        } 
        return ans;
    }

    void Orz()
    {
        rd();
        int j = 1;
        LL ans = 0;
        for(int i = 1; i <= n; i ++) 
        {
            while(mabs(a[i].y - a[j].y) > d)  {//听说abs不资瓷long long？窝写了一个mabs
                jia(a[j].x,-1);
                j ++;
            }
            ans += he(a[i].x + d) - he(a[i].x - d-1);
            cout<<ans<<"\n";
            jia(a[i].x,1);
        }
        cout<<ans;
    }

```


三维：

注意到此时m很小，$m <= 75$

我们可先将$x,y$两维转切比雪夫距离

然后转换后$(x_1,y_1,z_1)$ $(x_2,y_2,z_2)$距离就变成了

$max(x_1 - x_2,y_1 - y_2) + (z_1 - z_2)$

然后我们将点按照z排序

之后我们对于一个点 $(x_a,y_a,z_a)$

求出所有  $z_a-d <= z <= z_a$，$x+z_a - z <= d,y+z_a - z <= d$的点数

我们可以维护每一个面，点的个数的二维前缀和

然后枚举每个面 查询一个正方形点的个数即可

为了防止 a点 -> b点 b点->a点 重复枚举

建议在同一个面的情况特殊处理

```
    struct aa {
        int x,y,z;
    } a[MAXN];
    int n,m;
    
    signed c[82][505][505];
    LL s[82][505][505];

    LL zfx(int i,int x,int y,int d)//[x-d,x+d][y-d,y+d]的正方形点数
    {
return s[i][x+d][y+d+75] - s[i][max((LL)0,x-d-1)][y+d+75]
- s[i][x+d][max((LL)0,y-d-1+75)] + s[i][max((LL)0,x-d-1)][max((LL)0,y-d-1+75)];
    } 
    LL ans = 0;
    void Orz()
    {
        scanf("%lld%lld%lld",&n,&d,&m);
        for(int i = 1; i <= n; i ++) {
            int x,y;
            scanf("%lld%lld%lld",&x,&y,&a[i].z);
            a[i].x = (x+y);
            a[i].y = x-y;
        
            c[a[i].z][a[i].x][a[i].y+75] ++;//因为a[i].y会有 < 0情况，所以加了75
  
        }
        //getchar();
        for(int i = 1; i <= m; i ++)
            for(int j = 0; j <= m*5+5; j ++)
                for(int k = -75; k <= m*5+5; k ++)
                {
                    s[i][j][k+75] = c[i][j][k+75] + s[i][j][k-1+75] + s[i][j-1][k+75] - s[i][j-1][k-1+75]; 
                }
        LL an = 0;
        for(int i = 1; i <= n; i ++) {
            for(int j = 1; j < a[i].z; j ++)
            if(a[i].z - j <= d)
			{
                ans += zfx(j,a[i].x,a[i].y,d - (a[i].z - j));//同一个面的情况
            }
            int ro = i;

            an += zfx(a[i].z,a[i].x,a[i].y,d);

            an --;
        }
        cout<<ans + (an>>1);	
    }
```


---

## 作者：清远学会 (赞：6)

这题好像没有通法，所以我选择分部来写

**1.暴力**

对于$n \le 1000$ ,O($n ^ 2$)枚举点不多讲

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 200500
using namespace std;

inline int read() {
	int x = 0,f = 1; char s = getchar();
	while(s < '0' || s > '9') {if(s == '-') f = -1; s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0'; s = getchar();}
	return x * f;
}

int n,m,B,D;
int b[N][4];

inline int DD(int x) {return x < 0 ? -x : x;}

inline bool Calc(int x,int y) {
	int x1 = b[x][0],y1 = b[x][1],z1 = b[x][2];
	int x2 = b[y][0],y2 = b[y][1],z2 = b[y][2];
	if(DD(x1 - x2) + DD(y1 - y2) + DD(z1 - z2) <= D) return true;
	return false;
}

int main() {
	B = read(),n = read(),D = read(),m = read();
	
	int ans = 0;
	for(int i = 1;i <= n;i ++)
		for(int j = 0;j < B;j ++)
			b[i][j] = read();
	for(int i = 1;i <= n;i ++)
		for(int j = i + 1;j <= n;j ++)
			if(Calc(i,j)) ans ++;
	printf("%d\n",ans);
	
	return 0;
}
```

 **2.B == 1 的情况**

一维可以考虑下权值线段树，$M$过大可以考虑动态开点

具体怎么实现呢：

对于点$i$,设它坐标为$x[i]$，那么，对答案有影响的是（$x[i]-D$,$x[i]+D$）的范围

所以，对于前$i -1$ 个点，用权值线段树来维护（$x[i]-D$,$x[i]+D$）区间上点的个数，

统计完成后，在将次点插入到线段树中即可

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 200500
using namespace std;

inline int read() {
	int x = 0,f = 1; char s = getchar();
	while(s < '0' || s > '9') {if(s == '-') f = -1; s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0'; s = getchar();}
	return x * f;
}

int n,m,B,D;
struct node {
	int x,y,z;
}a[N];

inline int DD(int x) {return x < 0 ? -x : x;}

struct Tree {
	int l,r;
	long long tag;
} tr[N * 50];
int tot,root;

inline void Insert(int &k,int l,int r,int a) {
	if(!k) k = ++ tot;
	if(l == r) {
		tr[k].tag ++;
		return ;
	}
	int mid = (l + r) >> 1;
	if(a <= mid) Insert(tr[k].l,l,mid,a);
	else Insert(tr[k].r,mid + 1,r,a);
	tr[k].tag = tr[tr[k].l].tag + tr[tr[k].r].tag;
}

inline long long Ask(int k,int l,int r,int a,int b) {
	if(!k) return 0;
	if(a <= l && r <= b) return tr[k].tag;
	int mid = (l + r) >> 1; long long res = 0;
	if(a <= mid) res += Ask(tr[k].l,l,mid,a,b);
	if(b > mid) res += Ask(tr[k].r,mid + 1,r,a,b);
	return res;
}

int main() {
	B = read(),n = read(),D = read(),m = read();
	
    if(B == 1) {
		long long ans = 0;
		for(int i = 1;i <= n;i ++)
			a[i].x = read();
		for(int i = 1;i <= n;i ++) {
			ans += Ask(root,1,m,a[i].x - D,a[i].x + D);
			Insert(root,1,m,a[i].x);
		}
		printf("%lld\n",ans); return 0;
	}
    
	return 0;
}
```

**3.B == 2 的情况**

这就比较自闭了

由题意得，距离公式为$dis=|x_1- x_2|+|y_1-y_2|$

要使$dis \le D$ ,发现以$i$为中心，$2*D$的对角线长的菱形为覆盖矩阵（不懂得可以画画图）

发现，难以维护菱形中的点的个数；

所以，我们要旋转坐标系，$dis$为曼哈顿距离，也就是转为切比雪夫公式就行了

具体的证明（不太会，我的理解）就是：

重写便曼哈顿距离：$dis=|x_1- x_2|+|y_1-y_2|$

把绝对值拆开:

 1.$dis$ = $x_1$ - $x_2$ + $y_1$ - $y_2$ ($x_1\ge x_2$ 且$y_1 \ge y_2$)

 2.$dis$ = $x_2$ - $x_1$ + $y_1$ - $y_2$ ($x_1 \le x_2$ 且$y_1 \ge y_2$)

 3.$dis$ = $x_1$ - $x_2$ + $y_2$ - $y_1$ ($x_1 \ge x_2$ 且$y_1 \le y_2$)

 4.$dis$ = $x_2$ - $x_1$ + $y_2$ - $y_1$ ($x_1 \le x_2$ 且$y_1 \le y_2$)

发现：$1与4$互为绝对值，$2与3$互为绝对值

在把柿子组合下：$dis = max(|(x_1 + y_1) - (x_2 + y_2)|,|(x_1+y_2) - (x_2 + y_1)|)$

这个和切比雪夫公式对比下：$dis = max(|x_1-x_2|,|y_1-y_2|)$

发现对于坐标$(x_i,y_i)$,可以转化为$(x_i+y_i,x_i-y_i)$

具体的操作是，对于转化后的点：

先按$x$为关键字排序，$O(n)$扫描，再用一个指针来记录$i$这个点的最远的距离，设为$tail$

那么，对于$tail->i$的区间，再符合$y_i$的坐标范围就行啦；可以用上文提到的权值线段树维护$y_i$

代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 200500
using namespace std;

inline int read() {
	int x = 0,f = 1; char s = getchar();
	while(s < '0' || s > '9') {if(s == '-') f = -1; s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0'; s = getchar();}
	return x * f;
}

int n,m,B,D;
struct node {
	int x,y,z;
}a[N];

inline int DD(int x) {return x < 0 ? -x : x;}

struct Tree {
	int l,r;
	long long tag;
} tr[N * 50];
int tot,root;

inline void Insert(int &k,int l,int r,int a,int b) {
	if(!k) k = ++ tot;
	if(l == r) {
		tr[k].tag += b;
		return ;
	}
	int mid = (l + r) >> 1;
	if(a <= mid) Insert(tr[k].l,l,mid,a,b);
	else Insert(tr[k].r,mid + 1,r,a,b);
	tr[k].tag = tr[tr[k].l].tag + tr[tr[k].r].tag;
}

inline long long Ask(int k,int l,int r,int a,int b) {
	if(!k) return 0;
	if(a <= l && r <= b) return tr[k].tag;
	int mid = (l + r) >> 1; long long res = 0;
	if(a <= mid) res += Ask(tr[k].l,l,mid,a,b);
	if(b > mid) res += Ask(tr[k].r,mid + 1,r,a,b);
	return res;
}

inline bool cmp1(const node &a,const node &b) {
	return a.x < b.x;
}

int main() {
	B = read(),n = read(),D = read(),m = read();
	
	if(B == 2) {
		long long ans = 0;
		for(int i = 1;i <= n;i ++)
			a[i].x = read(),a[i].y = read();
		for(int i = 1;i <= n;i ++) {
			int x = a[i].x,y = a[i].y;
			a[i].x = x + y; 
			a[i].y = x - y;
		}
		sort(a + 1,a + n + 1,cmp1); 
		int tl = 1; Insert(root,-m,m,a[1].y,1);
		for(int i = 2;i <= n;i ++) {
			while(DD(a[tl].x - a[i].x) > D)
				Insert(root,-m,m,a[tl].y,-1),tl ++;
			ans += Ask(root,-m,m,a[i].y - D,a[i].y + D);
			Insert(root,-m,m,a[i].y,1);
		}
		printf("%lld\n",ans); return 0;
	}
	
	return 0;
}
```

**3.B==3的情况**

观察到$M\le75$ ,显然可以乱搞

其实也不是乱搞；

借鉴下$B==2$的情况，可以想到$B==2$时时一个平面

而对于此情况可以把维度提高，也就是多个平面

再次提及$M\le75$，所以对于每层开个桶；

之后对于每层求二维前缀和，这样就可以$O(1)$求此面的任意大小的矩形中点的个数

不妨设$i$号所在层数为$z$

那么可以强制选$z$层以下的，这样可以不会算重

对于$z$这一层要单独来算贡献，因为计算时会记录自己，并且同层会记录两边，所以要单独计算

具体见代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 200500
using namespace std;

inline int read() {
	int x = 0,f = 1; char s = getchar();
	while(s < '0' || s > '9') {if(s == '-') f = -1; s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0'; s = getchar();}
	return x * f;
}

int n,m,B,D;
struct node {
	int x,y,z;
}a[N];
int buk[100][155][155];

inline int DD(int x) {return x < 0 ? -x : x;}

int main() {
	B = read(),n = read(),D = read(),m = read();
	
	if(B == 3) {
		for(int i = 1;i <= n;i ++)
			a[i].x = read(),a[i].y = read(),a[i].z = read();
		for(int i = 1;i <= n;i ++) {
			int x = a[i].x,y = a[i].y;
			a[i].x = x + y;
			a[i].y = x - y + m;
		}
		for(int i = 1;i <= n;i ++) 
			buk[a[i].z][a[i].x][a[i].y] ++;
		for(int k = 1;k <= m;k ++) {
			for(int i = 1;i <= m * 2;i ++)
				for(int j = 1;j <= m * 2;j ++)
					buk[k][i][j] += buk[k][i - 1][j] + buk[k][i][j - 1] - buk[k][i - 1][j - 1];
		}
		long long ans1 = 0,ans2 = 0;
		for(int i = 1;i <= n;i ++) {
			for(int j = max(1,a[i].z - D);j < a[i].z;j ++) {
				int d = D - (a[i].z - j);
				int x1 = max(1,a[i].x - d),x2 = min(m * 2,a[i].x + d);
				int y1 = max(1,a[i].y - d),y2 = min(m * 2,a[i].y + d);
				ans1 += buk[j][x2][y2] - buk[j][x2][y1 - 1] - buk[j][x1 - 1][y2] + buk[j][x1 - 1][y1 - 1];
			}
			int d = D;
			int x1 = max(1,a[i].x - d),x2 = min(m * 2,a[i].x + d);
			int y1 = max(1,a[i].y - d),y2 = min(m * 2,a[i].y + d);
			ans2 += buk[a[i].z][x2][y2] - buk[a[i].z][x2][y1 - 1] - buk[a[i].z][x1 - 1][y2] + buk[a[i].z][x1 - 1][y1 - 1];
		}
		ans1 += (ans2 - n) / 2;
		printf("%lld\n",ans1); return 0;
	}
	
	return 0;
}
```

最后，放上AC代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 200500
using namespace std;

inline int read() {
	int x = 0,f = 1; char s = getchar();
	while(s < '0' || s > '9') {if(s == '-') f = -1; s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0'; s = getchar();}
	return x * f;
}

int n,m,B,D;
struct node {
	int x,y,z;
}a[N];
int buk[100][155][155];

inline int DD(int x) {return x < 0 ? -x : x;}

struct Tree {
	int l,r;
	long long tag;
} tr[N * 50];
int tot,root;

inline void Insert(int &k,int l,int r,int a,int b) {
	if(!k) k = ++ tot;
	if(l == r) {
		tr[k].tag += b;
		return ;
	}
	int mid = (l + r) >> 1;
	if(a <= mid) Insert(tr[k].l,l,mid,a,b);
	else Insert(tr[k].r,mid + 1,r,a,b);
	tr[k].tag = tr[tr[k].l].tag + tr[tr[k].r].tag;
}

inline long long Ask(int k,int l,int r,int a,int b) {
	if(!k) return 0;
	if(a <= l && r <= b) return tr[k].tag;
	int mid = (l + r) >> 1; long long res = 0;
	if(a <= mid) res += Ask(tr[k].l,l,mid,a,b);
	if(b > mid) res += Ask(tr[k].r,mid + 1,r,a,b);
	return res;
}

inline bool cmp1(const node &a,const node &b) {
	return a.x < b.x;
}

int main() {
	B = read(),n = read(),D = read(),m = read();
	
	if(B == 1) {
		long long ans = 0;
		for(int i = 1;i <= n;i ++)
			a[i].x = read();
		for(int i = 1;i <= n;i ++) {
			ans += Ask(root,1,m,a[i].x - D,a[i].x + D);
			Insert(root,1,m,a[i].x,1);
		}
		printf("%lld\n",ans); return 0;
	}
	
	if(B == 2) {
		long long ans = 0;
		for(int i = 1;i <= n;i ++)
			a[i].x = read(),a[i].y = read();
		for(int i = 1;i <= n;i ++) {
			int x = a[i].x,y = a[i].y;
			a[i].x = x + y; 
			a[i].y = x - y;
		}
		sort(a + 1,a + n + 1,cmp1); 
		int tl = 1; Insert(root,-m,m,a[1].y,1);
		for(int i = 2;i <= n;i ++) {
			while(DD(a[tl].x - a[i].x) > D)
				Insert(root,-m,m,a[tl].y,-1),tl ++;
			ans += Ask(root,-m,m,a[i].y - D,a[i].y + D);
			Insert(root,-m,m,a[i].y,1);
		}
		printf("%lld\n",ans); return 0;
	}
	
	if(B == 3) {
		for(int i = 1;i <= n;i ++)
			a[i].x = read(),a[i].y = read(),a[i].z = read();
		for(int i = 1;i <= n;i ++) {
			int x = a[i].x,y = a[i].y;
			a[i].x = x + y;
			a[i].y = x - y + m;
		}
		for(int i = 1;i <= n;i ++) 
			buk[a[i].z][a[i].x][a[i].y] ++;
		for(int k = 1;k <= m;k ++) {
			for(int i = 1;i <= m * 2;i ++)
				for(int j = 1;j <= m * 2;j ++)
					buk[k][i][j] += buk[k][i - 1][j] + buk[k][i][j - 1] - buk[k][i - 1][j - 1];
		}
		long long ans1 = 0,ans2 = 0;
		for(int i = 1;i <= n;i ++) {
			for(int j = max(1,a[i].z - D);j < a[i].z;j ++) {
				int d = D - (a[i].z - j);
				int x1 = max(1,a[i].x - d),x2 = min(m * 2,a[i].x + d);
				int y1 = max(1,a[i].y - d),y2 = min(m * 2,a[i].y + d);
				ans1 += buk[j][x2][y2] - buk[j][x2][y1 - 1] - buk[j][x1 - 1][y2] + buk[j][x1 - 1][y1 - 1];
			}
			int d = D;
			int x1 = max(1,a[i].x - d),x2 = min(m * 2,a[i].x + d);
			int y1 = max(1,a[i].y - d),y2 = min(m * 2,a[i].y + d);
			ans2 += buk[a[i].z][x2][y2] - buk[a[i].z][x2][y1 - 1] - buk[a[i].z][x1 - 1][y2] + buk[a[i].z][x1 - 1][y1 - 1];
		}
		ans1 += (ans2 - n) / 2;
		printf("%lld\n",ans1); return 0;
	}
	
	return 0;
}
```

撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：TernaryTree (赞：2)

曼哈顿距离转切比雪夫距离板子题。

---

### $B=1$

排序一下直接双指针维护即可。

```cpp
int l = 1, r = 0;
while (r < n) {
	++r;
	while (l <= r && a[r][0] - a[l][0] > d) ++l;
	ans += r - l;
}
cout << ans << endl;
```

复杂度 $\Theta(n)$。

---

### $B=2$

二维曼哈顿转切比雪夫。

将 $(x,y)$ 映射到 $(p,q)=(x+y,x-y)$，则原来两点的曼哈顿距离变为切比雪夫距离（即由各维坐标差绝对值之和转换为最大值）。

按 $p$ 排序，套上 $B=1$ 时的双指针，相当于消掉了一维的限制；只需要查询 $[l,r]$ 区间内有多少个 $q$ 与当前的 $q$ 距离差不超过 $d$，可以使用权值树状数组维护。

```cpp
int l = 1, r = 0;
while (r < n) {
	++r;
	while (l <= r && a[r][0] - a[l][0] > d) tr.add(a[l++][1], -1);
	ans += tr.query(a[r][1] + d) - tr.query(a[r][1] - d - 1);
	tr.add(a[r][1], 1);
}
cout << ans << endl;
```

复杂度 $\Theta(n\log m)$。

---

### $B=3$

三维曼哈顿转切比雪夫：需要升维，$(x,y,z)$ 映射到 $(i,j,k,l)=(x+y+z,x+y-z,x-y+z,-x+y+z)$。同理此时两点距离是各维坐标差绝对值中的最大值。

继续使用双指针消掉第一维，则剩下的操作相当于三维空间内单点修改，查询一个立方体的和。使用三维树状数组维护之。

```cpp
int l = 1, r = 0;
while (r < n) {
	++r;
	while (l <= r && a[r][0] - a[l][0] > d) rt.add(a[l][1], a[l][2], a[l][3], -1), l++;
	ans += rt.query(a[r][1] - d, a[r][1] + d, a[r][2] - d, a[r][2] + d, a[r][3] - d, a[r][3] + d);
	rt.add(a[r][1], a[r][2], a[r][3], 1);
}
cout << ans << endl;
```

复杂度 $\Theta(n\log^3 m)$。

---

### $B\ge 4 \text{?}$

事实上也是可以做的。

我们考虑三维的映射，发现其曼哈顿转切比雪夫很显然可以推广。注意到映射到的每一维的系数应为 $\pm 1$ 的组合去掉正负对称的，所以我们就可以把一个 $B$ 维空间的点映射到一个 $2^{B-1}$ 维的坐标上实现曼哈顿转切比雪夫了。双指针消掉一维后继续使用高维树状数组维护，复杂度应该是 $\Theta(n\cdot 2^{B-1}+n\log ^{2^{B-1}-1}m)$。

---

## Code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e6 + 10;
const int maxm = 301;
const int of1 = 3e5;
const int of2 = 1e2;

int b, n, d, m, qwq, ans;
vector<int> a[maxn];

struct bit {
	int n, b[maxn] = {};
	void add(int p, int x) { 
//		cout << p << " " << x << endl;
		while (p <= n) b[p] += x, p += p & -p; 
	}
	int query(int p) {
		if (p < 0) return 0;
		int y = 0;
		while (p) y += b[p], p -= p & -p;
		return y;
	}
};

struct tib {
	int n;
	signed b[maxm][maxm][maxm] = {};
	void add(int x, int y, int z, int p) {
		for (int i = x; i <= n; i += i & -i) {
			for (int j = y; j <= n; j += j & -j) {
				for (int k = z; k <= n; k += k & -k) {
					b[i][j][k] += p;
				}
			}
		}
	}
	int query(int x, int y, int z) {
		x = max(x, 0ll), x = min(x, n);
		y = max(y, 0ll), y = min(y, n);
		z = max(z, 0ll), z = min(z, n);
		int p = 0;
		for (int i = x; i; i -= i & -i) {
			for (int j = y; j; j -= j & -j) {
				for (int k = z; k; k -= k & -k) {
					p += b[i][j][k];
				}
			}
		}
		return p;
	}
	int query(int il, int ir, int jl, int jr, int kl, int kr) {
		return query(ir, jr, kr) 
			- query(il - 1, jr, kr) - query(ir, jl - 1, kr) - query(ir, jr, kl - 1)
			+ query(ir, jl - 1, kl - 1) + query(il - 1, jr, kl - 1) + query(il - 1, jl - 1, kr)
			- query(il - 1, jl - 1, kl - 1);
	}
};

bit tr;
tib rt;

signed main() {
	tr.n = 1e6;
	rt.n = 300;
	cin >> b >> n >> d >> m;
	qwq = 1 << b - 1;
	for (int i = 1; i <= n; i++) {
		a[i].resize(qwq);
		for (int j = 0; j < b; j++) cin >> a[i][j];
		if (b == 2) {
			int x = a[i][0], y = a[i][1];
			a[i] = {x + y + of1, x - y + of1};
		} else if (b == 3) {
			int x = a[i][0], y = a[i][1], z = a[i][2];
			a[i] = {x + y + z + of2, x + y - z + of2, x - y + z + of2, - x + y + z + of2};
		}
	}
	sort(a + 1, a + 1 + n);
	if (b == 1) {
		int l = 1, r = 0;
		while (r < n) {
			++r;
			while (l <= r && a[r][0] - a[l][0] > d) ++l;
			ans += r - l;
		}
		cout << ans << endl;
	} else if (b == 2) {
		int l = 1, r = 0;
		while (r < n) {
			++r;
			while (l <= r && a[r][0] - a[l][0] > d) tr.add(a[l++][1], -1);
			ans += tr.query(a[r][1] + d) - tr.query(a[r][1] - d - 1);
			tr.add(a[r][1], 1);
		}
		cout << ans << endl;
	} else {
		int l = 1, r = 0;
		while (r < n) {
			++r;
			while (l <= r && a[r][0] - a[l][0] > d) rt.add(a[l][1], a[l][2], a[l][3], -1), l++;
			ans += rt.query(a[r][1] - d, a[r][1] + d, a[r][2] - d, a[r][2] + d, a[r][3] - d, a[r][3] + d);
			rt.add(a[r][1], a[r][2], a[r][3], 1);
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：liaoz123 (赞：1)

这道题可以帮助你更好地理解曼哈顿距离和切比雪夫距离的转化。核心结论是：$n$ 维空间下的曼哈顿距离可以转化成 $2^{n-1}$ 维下的切比雪夫距离。若原坐标系中的点的坐标为 $(a_1,a_2,\cdots,a_{n-1},a_n)$，则新坐标系中，点的坐标的为 $a_1+\sum_{i=2}^n(\pm a_i)$，共 $2^{n-1}$ 维，其中维的顺序并不重要，某一维整体的正负并不重要，只和坐标是否覆盖了所有的元素的相对正负关系有关。因为切比雪夫距离可以表达曼哈顿距离的关键是考虑到了曼哈顿距离表达式中，每个绝对值内的正负性，每一个维度就会增加 $2$ 中相对的正负关系，必须全部考虑进去才行。

对于本题，$B=1$ 的情况是容易的，排序后二分即可。

$B=2$ 时，由于曼哈顿坐标系中的“圆”呈现一个旋转 $45$ 度后的正方形的形状，并不好计数。因此考虑转化成切比雪夫坐标系，原先坐标为 $(x,y)$ 的点转变为 $(\frac{x+y}{2},\frac{x-y}{2})$。从而两点间的曼哈顿距离等于新坐标系下对应维度的差的较大值，两点距离不超过 $d$ 就等价于新坐标系下两个点两维的坐标之差都不超过 $d$。那么对其中一维进行扫描线，另一维的限制就变成了一个区间，可以使用树状数组计数。

$B=3$ 时，同上，转化成切比雪夫距离，点 $(x,y,z)$ 在新坐标系下的坐标为 $(x+y+z,x-y+z,x+y-z,x-y-z)$。注意到此时坐标非常小，我们可以同样地对其中一位进行扫描线，用三维树状数组维护另外三维即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,d,m,B;ll ans=0;
namespace sub1{
	const int N=1e6+5;
	int a[N];
	void main(){
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			int pos=lower_bound(a+1,a+n+1,a[i]-d)-a;
			ans+=i-pos;
		}
		cout<<ans<<endl;
	}
}
namespace sub2{
	const int N=1e6+5;
	int t[N];
	struct node{
		int x,y;
		bool operator <(const node aa)const{
			return x<aa.x;
		}
	}a[N];
	void insert(int x,int y){
		for(int i=x;i<=3*m;i+=(i&(-i)))
		t[i]+=y;
	}
	int sum(int x){
		int ss=0;x=min(x,3*m);
		if(x<=0)return 0;
		for(int i=x;i;i-=(i&(-i)))
		ss+=t[i];return ss;
	}
	void main(){
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i].x,&a[i].y);
			int x=a[i].x,y=a[i].y;
			a[i].x=x+y+m,a[i].y=x-y+m;
		}
		sort(a+1,a+n+1);
		int now=1;
		for(int i=1;i<=n;i++){
			while(now<=n&&a[i].x-a[now].x>d)
			insert(a[now].y,-1),now++;
			ans+=sum(a[i].y+d)-sum(a[i].y-d-1);
			insert(a[i].y,1);
		}
		cout<<ans<<endl;
	}
}
namespace sub3{
	const int N=1e6+5;
	int t[301][301][301];
	struct node{
		int a,x,y,z;
		bool operator <(const node aa)const{
			return a<aa.a;
		}
	}a[N];
	void insert(int x,int y,int z,int d){
		for(int i=x;i<=3*m;i+=(i&(-i)))
		for(int j=y;j<=3*m;j+=(j&(-j)))
		for(int c=z;c<=3*m;c+=(c&(-c)))
		t[i][j][c]+=d;
	}
	int sum(int x,int y,int z){
		int ss=0;
		if(x<=0||y<=0||z<=0)return 0;
		x=min(x,3*m);y=min(y,3*m);z=min(z,3*m);
		for(int i=x;i;i-=(i&(-i)))
		for(int j=y;j;j-=(j&(-j)))
		for(int c=z;c;c-=(c&(-c)))
		ss+=t[i][j][c];return ss;
	}
	int query(int x,int y,int z,int a,int b,int c){
		int ss=0;
		ss+=sum(x,y,z);ss-=sum(a,y,z);ss-=sum(x,b,z);ss-=sum(x,y,c);
		ss+=sum(a,b,z);ss+=sum(a,y,c);ss+=sum(x,b,c);ss-=sum(a,b,c);
		return ss;
	}
	void main(){
		for(int i=1;i<=n;i++){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			a[i].a=x+y+z;
			a[i].x=x+y-z+m;
			a[i].y=x-y+z+m;
			a[i].z=y+z-x+m;
		}
		sort(a+1,a+n+1);
		int now=1;
		for(int i=1;i<=n;i++){
			while(now<=n&&a[i].a-a[now].a>d)
			insert(a[now].x,a[now].y,a[now].z,-1),now++;
			ans+=query(a[i].x+d,a[i].y+d,a[i].z+d,a[i].x-d-1,a[i].y-d-1,a[i].z-d-1);
			insert(a[i].x,a[i].y,a[i].z,1);
		}
		cout<<ans<<endl;
	}
}
int main(){
	cin>>B;scanf("%d%d%d",&n,&d,&m);m++;
	if(B==1)sub1::main();
	if(B==2)sub2::main();
	if(B==3)sub3::main();
	return 0;
}
```

---

## 作者：Fzrcy (赞：1)

按 $B$ 的大小分类讨论：

- $B=1$ 时：直接排序，双指针计算即可。
- $B=2$ 时：因为曼哈顿距离不好统计，考虑将曼哈顿距离转为切雪比夫距离，则点 $x$ 可达的位置在一个以 $x$ 为中心、边长为 $2D$ 且平行于坐标轴的正方形。问题变为矩阵求和，差分计算即可，具体的可以看代码。
- $B=3$ 时：将 $y,z$ 维转为切雪比夫距离，由于值域很小，可以对每个点 $s$ 暴力枚举 $x$ 维的值 $i$ ，统计 $x=i$ 且和点 $s$ 的距离小于 $D$ 的点数，因为值域很小，可以对 $x=i$ 的平面二维前缀和预处理。

```cpp
// qwq
#include <bits/stdc++.h>
#define rep(I,A,B) for(int I=(A);I<=(B);I++)
using namespace std;
typedef long long ll;
constexpr int N=5e5+6;
namespace Task1{
    int n,D,a[N],m;
    ll ans;
    int Main(){
        cin>>n>>D>>m;
        rep(i,1,n)cin>>a[i];
        sort(a+1,a+n+1);
        for(int i=1,j=1;i<=n;i++){
            while(a[i]-a[j]>D)j++;
            ans+=i-j;
        }
        cout<<ans;
        return 0;
    }
}
namespace Task2{
    struct SegTree{
        int s[N<<2];
        void ins(int k,int l,int r,int x){
            s[k]++;if(l==r)return;int mid=l+r>>1;
            if(x<=mid)ins(k<<1,l,mid,x);
            else ins(k<<1|1,mid+1,r,x);
        }
        int Q(int k,int l,int r,int x,int y){
            if(x>r||y<l)return 0;
            if(l>=x&&r<=y)return s[k];int mid=l+r>>1,e=0;
            if(x<=mid)e=Q(k<<1,l,mid,x,y);
            if(y>mid)e+=Q(k<<1|1,mid+1,r,x,y);
            return e;
        }
    }tr;
    struct node{int x,y;}a[N];
    int n,m,D,ans[N],c[N];
    vector<int>id[N],Id[N];
    int Main(){
        cin>>n>>D>>m;
        for(int i=1,x,y;i<=n;i++){
            cin>>x>>y,a[i]={x+y,x-y};
            int l=a[i].x-D-1,r=a[i].x+D;
            if(l>0)id[l].push_back(i);
            r=min(r,2*m),id[r].push_back(i);
            Id[a[i].x].push_back(i);
        }
        for(int i=1;i<=2*m;i++){
            for(auto j:Id[i])tr.ins(1,-m,m,a[j].y);
            for(auto j:id[i])
                ans[j]=tr.Q(1,-m,m,a[j].y-D,a[j].y+D)-ans[j];
        }
        ll res=0;
        for(int i=1;i<=n;i++)res+=ans[i]-1;
        cout<<res/2;
        return 0;
    }
}
namespace Task3{
    struct node{int x,y,z;}A[N];
    int a[77][155][155];
    int n,m,D;
    int calc(int g,int x,int y,int r){
        if(r<0)return 0; int X=x+r,Y=y+r;x-=r,y-=r;y+=m,Y+=m;
        x=max(x,1),y=max(y,1),X=min(X,2*m),Y=min(Y,2*m);
        if(X<x||Y<y)return 0;
        return a[g][X][Y]+a[g][x-1][y-1]-a[g][x-1][Y]-a[g][X][y-1];
    }
    int Main(){
        cin>>n>>D>>m;
        for(int i=1,x,y,z;i<=n;i++)cin>>x>>y>>z,A[i]={x,y+z,y-z},a[x][y+z][y-z+m]++;
        for(int i=1;i<=m;i++) for(int j=1;j<=2*m;j++) for(int k=1;k<=2*m;k++)
            a[i][j][k]+=a[i][j][k-1]+a[i][j-1][k]-a[i][j-1][k-1];
        ll ans=0;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
            ans+=calc(j,A[i].y,A[i].z,D-abs(j-A[i].x));
        ans-=n;ans/=2;
        cout<<ans;
        return 0;
    }
}
int main(){
    int B;
    cin>>B;
    if(B==1)Task1::Main();
    if(B==2)Task2::Main();
    if(B==3)Task3::Main();
    return 0;
}
```



---

## 作者：Daniel_yao (赞：0)

# Problem
给定模板 $B(1\le B \le 3)$，代表 $B$ 维空间。其中有 $n$ 个点，给出坐标与坐标上限 $M$，求 $n$ 个点中曼哈顿距离 $\le D$ 的对数。

# Solve

## $B = 1$

考虑将问题化简成：求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^{i-1}[dis(i,j)\leq D]$。其中 $dis(i,j)$ 表示第 $i,j$ 个点的距离。

然后考虑将一维坐标排序，枚举 $i$。发现每一次 $i$ 做出贡献的位置 $j<i$ 且 $dis(i,j)\leq D$，所以每次将 $i$ 加入队列中，如果队首对应坐标与当前坐标距离大于 $D$，就不停的弹队首，直至满足条件。然后将队列长度加入答案贡献（此时队列里的所有对应坐标都能与 $i$ 一起贡献答案）。

时间复杂度 $O(n)$。

```cpp
namespace Solve1 {
  int a[N], q[N], h = 1, t = 0, ans = 0;
  void work() {
    For(i,1,n) cin >> a[i];
    sort(a + 1, a + n + 1);
    For(i,1,n) {
      while(t - h + 1 > 0 && a[i] - a[q[h]] > d) h++;
      ans += (t - h + 1);
      q[++t] = i;
    }
    cout << ans << '\n';
  }
}
```

## $B=2$

考虑降位。

第一维可以参考 $B = 1$ 的情况排序后扫掉，第二维可以树状数组进行维护。

但是我们注意到，答案贡献的领域是一个斜 $45^\circ$ 正方形（因为距离是按曼哈顿距离来统计的）。

所以我们只需要将曼哈顿距离转成且切比雪夫距离，这样答案贡献的领域就是一个正的，长度为 $2D$ 的正方形了。

考虑如何转：

$$
\begin{aligned}
d(x,y)&=|x_1-x_2|+|y_1-y_2|\\
&=\max\{x_1-x_2+y_1-y_2, x_1-x_2-y_1+y_2,-x_1+x_2+y_1-y_2,-x_1+x_2-y_1+y_2\}\\
&=\max\{|(x_1+y_1)-(x_2+y_2)|, |(x_1-y_1)-(x_2-y_2)|\}
\end{aligned}
$$

于是将原坐标 $(x,y)$ 转成 $(x+y,x-y)$，在新坐标下维护操作即可。

时间复杂度 $O(n\log M)$。

```cpp
namespace Solve2 {
  struct Node {
    int x, y;
  } a[N];
  int q[N], h = 1, t = 0, Ans = 0;
  
  Int T[N * 2] = {0};
  
  bool cmp(Node x, Node y) {
    return (x.x == y.x ? x.y < y.y : x.x < y.x);
  }

  int lb(int x) {
    return x & -x;
  }

  void add(int x, int k) {
    for (int i = x; i <= 2 * m; i += lb(i)) {
      T[i] += k;
    }
  }

  int ask(int x) {
    int ans = 0;
    for (int i = min(2 * m, x); i; i -= lb(i)) {
      ans += T[i];
    }
    return ans;
  }

  void work() {
    For(i,1,n) cin >> a[i].x >> a[i].y;
    For(i,1,n) {
      int x = (a[i].x - a[i].y), y = (a[i].x + a[i].y);
      a[i].x = x, a[i].y = y;
    }
    sort(a + 1, a + n + 1, cmp);
    For(i,1,n) {
      while(t - h + 1 > 0 && a[i].x - a[q[h]].x > d) {
        add(a[q[h]].y, -1);
        h++;
      }
      Ans += (ask(a[i].y + d) - ask(max(0ll, a[i].y - d - 1)));
      add(a[i].y, 1);
      q[++t] = i;
    }
    cout << Ans << '\n';
  }
}
```

## $B = 3$

发现 $M\le 75$，于是可以往高维树状数组想。

与 $B=2$ 一样，先将曼哈顿距离转成且切比雪夫距离，对于三维。

考虑如何转：

$$
\begin{aligned}
d(x,y)&=|x_1-x_2|+|y_1-y_2|+|z_1-z_2|\\
&=\max\{\\
&(x_1-x_2+y_1-y_2+z_1-z_2),\\
&(x_1-x_2+y_1-y_2-z_1+z_2),\\
&(x_1-x_2-y_1+y_2+z_1-z_2),\\
&(x_1-x_2-y_1+y_2-z_1+z_2),\\
&(-x_1+x_2+y_1-y_2+z_1-z_2),\\
&(-x_1+x_2+y_1-y_2-z_1+z_2),\\
&(-x_1+x_2-y_1+y_2+z_1-z_2),\\
&(-x_1+x_2-y_1+y_2-z_1+z_2)\\
\}\\
&=\max\{\\
&|(x_1+y_1+z_1)-(x_2+y_2+z_2)|,\\
&|(x_1-y_1-z_1)-(x_2-y_2-z_2)|,\\
&|(x_1+y_1-z_1)-(x_2+y_2-z_2)|,\\
&|(x_1-y_1+z_1)-(x_2-y_2+z_2)|\\
\}
\end{aligned}
$$

是将原坐标 $(x,y,z)$ 转成 $(x-y-z,x+y+z,x+y-z,x-y+z)$，扫第一维，然后用三维树状数组维护前缀和即可。

时间复杂度 $O(n\log^3 M)$。

```cpp
namespace Solve3 {
  const int L = 76;

  struct Node {
    int x, y, z, l;
  } a[N];
  int q[N], h = 1, t = 0, Ans = 0;
  
  Int T[226][305][305] = {0};
  
  bool cmp(Node x, Node y) {
    return (x.x == y.x ? x.y < y.y : x.x < y.x);
  }

  int lb(int x) {
    return x & -x;
  }

  void add(int x, int y, int z, int X) {
    for (int i = x; i <= 3 * m; i += lb(i)) {
      for (int j = y; j <= 3 * m + L; j += lb(j)) {
        for (int k = z; k <= 3 * m + L; k += lb(k)) {
          T[i][j][k] += X;
        }
      }
    }
  }

  int ask(int x, int y, int z) {
    int ans = 0;
    for (int i = min(3 * m, x); i; i -= lb(i)) {
      for (int j = min(3 * m + L, y); j; j -= lb(j)) {
        for (int k = min(3 * m + L, z); k; k -= lb(k)) {
          ans += T[i][j][k];
        }
      }
    }
    return ans;
  }

  void work() {
    For(i,1,n) cin >> a[i].x >> a[i].y >> a[i].z;
    For(i,1,n) {
      int x = (a[i].x - a[i].y - a[i].z), y = (a[i].x + a[i].y + a[i].z), 
          z = (a[i].x + a[i].y - a[i].z) + L, l = (a[i].x - a[i].y + a[i].z) + L;
      a[i].x = x, a[i].y = y, a[i].z = z, a[i].l = l;
    }
    sort(a + 1, a + n + 1, cmp);
    For(i,1,n) {
      while(t - h + 1 > 0 && a[i].x - a[q[h]].x > d) {
        add(a[q[h]].y, a[q[h]].z, a[q[h]].l, -1);
        h++;
      }
      int x1 = a[i].y + d, y1 = a[i].z + d, z1 = a[i].l + d;
      int x2 = max(0ll, a[i].y - d - 1), y2 = max(0ll, a[i].z - d - 1), z2 = max(0ll, a[i].l - d - 1);
      Ans += (ask(x1, y1, z1) - ask(x2, y1, z1) - ask(x1, y2, z1) - ask(x1, y1, z2)
      + ask(x2, y1, z2) + ask(x1, y2, z2) + ask(x2, y2, z1) - ask(x2, y2, z2));
      add(a[i].y, a[i].z, a[i].l, 1);
      q[++t] = i;
    }
    cout << Ans << '\n';
  }
}
```

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define Int int
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 1e5 + 10;

int B, n, d, m;

namespace Solve1 {
  int a[N], q[N], h = 1, t = 0, ans = 0;
  void work() {
    For(i,1,n) cin >> a[i];
    sort(a + 1, a + n + 1);
    For(i,1,n) {
      while(t - h + 1 > 0 && a[i] - a[q[h]] > d) h++;
      ans += (t - h + 1);
      q[++t] = i;
    }
    cout << ans << '\n';
  }
}

namespace Solve2 {
  struct Node {
    int x, y;
  } a[N];
  int q[N], h = 1, t = 0, Ans = 0;
  
  Int T[N * 2] = {0};
  
  bool cmp(Node x, Node y) {
    return (x.x == y.x ? x.y < y.y : x.x < y.x);
  }

  int lb(int x) {
    return x & -x;
  }

  void add(int x, int k) {
    for (int i = x; i <= 2 * m; i += lb(i)) {
      T[i] += k;
    }
  }

  int ask(int x) {
    int ans = 0;
    for (int i = min(2 * m, x); i; i -= lb(i)) {
      ans += T[i];
    }
    return ans;
  }

  void work() {
    For(i,1,n) cin >> a[i].x >> a[i].y;
    For(i,1,n) {
      int x = (a[i].x - a[i].y), y = (a[i].x + a[i].y);
      a[i].x = x, a[i].y = y;
    }
    sort(a + 1, a + n + 1, cmp);
    For(i,1,n) {
      while(t - h + 1 > 0 && a[i].x - a[q[h]].x > d) {
        add(a[q[h]].y, -1);
        h++;
      }
      Ans += (ask(a[i].y + d) - ask(max(0ll, a[i].y - d - 1)));
      add(a[i].y, 1);
      q[++t] = i;
    }
    cout << Ans << '\n';
  }
}

namespace Solve3 {
  const int L = 76;

  struct Node {
    int x, y, z, l;
  } a[N];
  int q[N], h = 1, t = 0, Ans = 0;
  
  Int T[226][305][305] = {0};
  
  bool cmp(Node x, Node y) {
    return (x.x == y.x ? x.y < y.y : x.x < y.x);
  }

  int lb(int x) {
    return x & -x;
  }

  void add(int x, int y, int z, int X) {
    for (int i = x; i <= 3 * m; i += lb(i)) {
      for (int j = y; j <= 3 * m + L; j += lb(j)) {
        for (int k = z; k <= 3 * m + L; k += lb(k)) {
          T[i][j][k] += X;
        }
      }
    }
  }

  int ask(int x, int y, int z) {
    int ans = 0;
    for (int i = min(3 * m, x); i; i -= lb(i)) {
      for (int j = min(3 * m + L, y); j; j -= lb(j)) {
        for (int k = min(3 * m + L, z); k; k -= lb(k)) {
          ans += T[i][j][k];
        }
      }
    }
    return ans;
  }

  void work() {
    For(i,1,n) cin >> a[i].x >> a[i].y >> a[i].z;
    For(i,1,n) {
      int x = (a[i].x - a[i].y - a[i].z), y = (a[i].x + a[i].y + a[i].z), 
          z = (a[i].x + a[i].y - a[i].z) + L, l = (a[i].x - a[i].y + a[i].z) + L;
      a[i].x = x, a[i].y = y, a[i].z = z, a[i].l = l;
    }
    sort(a + 1, a + n + 1, cmp);
    For(i,1,n) {
      while(t - h + 1 > 0 && a[i].x - a[q[h]].x > d) {
        add(a[q[h]].y, a[q[h]].z, a[q[h]].l, -1);
        h++;
      }
      int x1 = a[i].y + d, y1 = a[i].z + d, z1 = a[i].l + d;
      int x2 = max(0ll, a[i].y - d - 1), y2 = max(0ll, a[i].z - d - 1), z2 = max(0ll, a[i].l - d - 1);
      Ans += (ask(x1, y1, z1) - ask(x2, y1, z1) - ask(x1, y2, z1) - ask(x1, y1, z2)
      + ask(x2, y1, z2) + ask(x1, y2, z2) + ask(x2, y2, z1) - ask(x2, y2, z2));
      add(a[i].y, a[i].z, a[i].l, 1);
      q[++t] = i;
    }
    cout << Ans << '\n';
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> B >> n >> d >> m;
  if(B == 1) {
    Solve1::work();
  } else if(B == 2) {
    Solve2::work();
  } else {
    Solve3::work();
  }
  return 0;
}
```

---

## 作者：pengyule (赞：0)

https://www.luogu.com.cn/problem/P4648

观察题设方式，不难想到针对 $B=1,2,3$ 单独作答。

---

### $B=1,O(N)$

直接排序+双指针即可。

```cpp
namespace ST1 {
	int a[N]; ll ans;
	void main(){
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=1,j=1;i<=n;i++){
			while(j<=n&&a[j]-a[i]<=d)j++;
			ans+=j-i-1;
		}
		cout<<ans;
	}
}
```

### $B=2,O(N\log 3M)$


> 在平面直角坐标系中，两个点 $(x_1,y_1),(x_2,y_2)$ 之间的曼哈顿距离 = $(x_1+y_1,x_1-y_1),(x_2+y_2,x_2-y_2)$ 之间的切比雪夫距离。

本题是一个不等式的限制，容易想到曼转切，将每个点 $(x,y)\to (x+y,x-y)$。


#### 先讲一个暴力思路
我们其实就是要对每个点 $(x,y)$ 求平面上 $(x-d,y-d)\to (x+d,y+d)$ 子矩阵和 $-1$（因为会包含 $(x,y)$ 自身）。
#### 更好的思路
可以沿用上面的，以 $x$ 关键字排序+双指针（下面记左右指针为 $i,j$），原因是切比雪夫距离 $\max(x_j-x_i,y_j-y_i)\le d$ 成立的条件之一是 $x_j-x_i\le d$。  
$i,j$ 之间的 $y$，每到一个就加入桶，则转为求值域上 $[x_i-d,x_i+d]$ 的和。容易用树状数组维护。注意值域可能为负，统一加上 $M$ 即可。

```cpp
namespace ST2 {
	int c[V+5]; ll ans;
	struct P{int x,y;}a[N];
	bool operator<(P a,P b){return a.x<b.x;}
	void add(int x,int y){for(;x<=V;x+=x&-x)c[x]+=y;}
	int ask(int x){int s=0;for(;x;x-=x&-x)s+=c[x];return s;}
	void main(){
		for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y,a[i].x+=a[i].y,a[i].y=a[i].x-2*a[i].y,a[i].x+=vm,a[i].y+=vm;
		sort(a+1,a+n+1);
		for(int i=1,j=1;i<=n;i++){
			add(a[i].y,-1);
			while(j<=n&&a[j].x-a[i].x<=d)add(a[j].y,1),j++;
			ans+=ask(min(a[i].y+d,3*vm))-ask(max(a[i].y-d,1)-1);
		}
		cout<<ans;
	}
}
```
### $B=3,O(9M^2+N\cdot M)$
当你从 $B=2$ 看到 $B=3$ 时，你会发现 $M$ 一下子减到了 $75$，这意味着 $B=2$ 的暴力可以用在这里，其实是题目给我们减少了代码量！

对 $(x,y,z)$ 的前二维曼转切，并将每个点看成 $z$ 平面上的点，平面与平面之间分开。  
对于每个点 $(x_i,y_i,z_i)$，枚举另一个点的 $z_j$，则所求即 $z_j$ 平面上的 $(x_i-l,y_i-l)\to(x_i+l,y_i+l)$ 子矩阵和 $-[z_i=z_j]$。  
每个平面大小很小，预处理出二维前缀和。

```cpp
namespace ST3 {
	int s[U][U][U]; ll ans;
	struct P{int x,y,z;}a[N];
	void main(){
		for(int i=1;i<=n;i++)cin>>a[i].x>>a[i].y>>a[i].z,a[i].x+=a[i].y,a[i].y=a[i].x-2*a[i].y,a[i].x+=vm,a[i].y+=vm,s[a[i].z][a[i].x][a[i].y]++;
		for(int c=1;c<=vm;c++)
			for(int i=1;i<=3*vm;i++)
				for(int j=1;j<=3*vm;j++)
					s[c][i][j]+=s[c][i-1][j]+s[c][i][j-1]-s[c][i-1][j-1];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=vm;j++){
				int l=d-abs(a[i].z-j);
				if(l<0)continue;
				//(a[i].x-l,a[i].y-l)->(a[i].x+l,a[i].y+l)
				int X1=max(a[i].x-l,1),Y1=max(a[i].y-l,1),X2=min(a[i].x+l,3*vm),Y2=min(a[i].y+l,3*vm);
				ans+=s[j][X2][Y2]-s[j][X1-1][Y2]-s[j][X2][Y1-1]+s[j][X1-1][Y1-1]-(a[i].z==j);
			}
		}
		cout<<ans/2;
	}
}
```

### 主函数

```cpp
using namespace std;
const int N=1e5+5,V=75e4*3,U=75*3+5;
typedef long long ll;
int B,n,d,vm;
int main(){
	cin>>B>>n>>d>>vm;
	if(B==1)ST1::main();
	if(B==2)ST2::main();
	if(B==3)ST3::main();
}
```

### 易错点
- long long
- 加上 $M$ 后值域为 $3M$

---

