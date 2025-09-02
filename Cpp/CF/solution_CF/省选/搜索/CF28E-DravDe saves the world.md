# DravDe saves the world

## 题目描述

多么可怕啊！银河鸡帝国试图征服美丽的Z城，他们建造了一个巨大的孵化器，每天孵化出数百万只小鸡，然后用他们围住$Z$城。巨大的培养箱看起来像一个有$n$个顶点的平面上的多边形。很自然地，DravDe不能闲着，他想摧毁银河鸡帝国。当然，他会从孵化器入手。

DravDe现在在孵化器之外的$A(x_a,y_a)$点,并且想要进入孵化器杀死所有在里面工作的鸡。但是这需要他做很多事情！问题是，DravDe最近去滑旱冰，摔断了双腿. 他将乘坐自己的喷气式飞机LEVAP-41进入孵化器。

LEVAP-41以$V(x_v,y_v,z_v)$的速度高速飞行。DravDe可以在$A$点上飞机，飞一段时间，然后自己空降。DravDe很重，所以他的掉落速度是$F_{down}$, 但在每一次自由落体时，DravDe都能打开降落伞。从他打开伞的那一刻起，他就开始以$U(x_u,y_v,z_u)$的速度下落直到他着陆。不幸的是，DravDe不擅长数学，你会帮助这个贫穷世界的救世主DravDe设计一个方案，让他降落在孵化器的领土上吗? 如果答案不是唯一的，DravDe想要找到飞行时间最短的方案。如果答案仍然是不唯一的的，他希望在打开降落伞之前找到自由落体时间最短的那个。

## 样例 #1

### 输入

```
4
0 0
1 0
1 1
0 1
0 -1
1 0 1
-1
0 1 -1
```

### 输出

```
1.00000000 0.00000000
```

## 样例 #2

### 输入

```
4
0 0
0 1
1 1
1 0
0 -1
-1 -1 1
-1
0 1 -1
```

### 输出

```
-1.00000000 -1.00000000
```

## 样例 #3

### 输入

```
4
0 0
1 0
1 1
0 1
0 -1
1 1 1
-1
1 1 -1
```

### 输出

```
0.50000000 0.00000000
```

# 题解

## 作者：Euler_Pursuer (赞：3)

# 题目大意

平面上给定一个多边形，你从多边形外部某一 $A$ 点起飞，在 $t_1$ 秒跳下飞机，进行 $t_2$ 秒自由落体，之后打开降落伞跳下飞机。给定飞机飞行速度向量 $V$，给定降落伞滑翔速度向量 $U$，给定自由落体速度 $F$，给定起飞点 $A$ 坐标。求出最小 $t_1$，若有多解 $t_1$，取 $t_2$ 最小者，输出 $t_1, t_2$。

注意这里给的 $z_v,F$ 都是负数，注意处理。

# 题解

## 找到可行区域

首先考虑我们可以降落在哪些地方。我们假设一直飞产生的轨迹在平面上的投影为**航线**，毫无疑问如果 $U$ 和 $V$ 在平面上的投影不共线，那么要使得偏离航线足够远，我们跳下飞机的瞬间就得打开降落伞了。那么如果有一段时间的自由落体，我们是无法越过那条最远偏航线的。因此，可行解必须落在如图所示的绿色区域内：

![可行区域](https://cdn.luogu.com.cn/upload/image_hosting/xtlecyn1.png)


但是要**注意**：由于 $U$ 和 $V$ 的 $z$ 方向分量不同，我们必须将它们同比放大或缩小成 $z$ 方向分量相同，这样才能确定出最远可以到达的边界。

## 确定可能的答案集合

先说结论：答案只可能取在最远偏航边界与多边形的交点处或者多边形的顶点上。

为什么呢？分几组情况。

### 情况一

此情况就是最近的点跳下去的时候，降落伞终点落到的是一条边上。

![可能可行解1](https://cdn.luogu.com.cn/upload/image_hosting/fym6ytzq.png)

### 情况二

降落伞终点落在的是一个点上。

![可能可行解2](https://cdn.luogu.com.cn/upload/image_hosting/6lnvu3pz.png)

此时就需要利用自由落体来削减偏航距离了。

### 情况三

航线直接与多边形相交。

![可能可行解4](https://cdn.luogu.com.cn/upload/image_hosting/xvs839v7.png)

这时我们就可以直接降落。

## 如果 $U,V$ 共线

这里看起来简单了，但是也要注意坑点，也分两个情况：

### 情况一

$U,V$ 方向相同。注意这里 $U$ 都是同比缩放后的。

![同向向量](https://cdn.luogu.com.cn/upload/image_hosting/2c9c0wwc.png)

这个时候我们只需要考虑多边形与直线交点是不是在 $V$ 方向这一侧就行了。

### 情况二

$U,V$ 方向相反。

![反向向量](https://cdn.luogu.com.cn/upload/image_hosting/l0tru7dy.png)

这个时候我们需要再分两小点讨论：

- $V$ 更大：只需考虑自由落体即可，因为这样一定是 $t_1$ 最小；
- $U$ 更大：需要考虑 $U$ 造成的反向飞行以及仅考虑自由落体两种情况。

至此，我们将所有情况讨论完毕，所需要的计算几何工具就是点的相关操作（包括点乘和叉乘），然后是直线相交，判断点是否在线段上，这几个就 $OK$ 了。

# 主要代码

```
int n;
Polygon<db> ps;
P<db> A, U, V, UV;
db zu, zv, f, calcf, calcuv;
db T1 = infit, T2 = infit;

inline void update(db t1, db t2)
{
    int r1 = cmp(t1, T1), r2 = cmp(t2, T2);
    if(r1 > 0) return;
    if(r1 < 0) { T1 = t1, T2 = t2; return; }
    if(r2 < 0) T2 = t2;
}

inline void getans(P<db> nw)
{
    int r1 = sign(V.det(UV)), r2 = sign(V.det(nw-A)), r3 = sign((nw-A).det(UV));
    if(r2 && r2 != r1) return;
    if(r3 && r3 != r1) return;
    //nw.write();
    P<db> iuv = isLL(nw, nw+U, A, A+UV);
    //iuv.write();
    update((iuv-A).abs()/calcuv, (nw-iuv).abs()/calcf);
    // Here we assume that he will reach the most further line
    // And if he don't need to get there
    // The recent point to the assuming point will consume during droping
}

int main()
{
    cin >> n;
    ps.resize(n);
    for(auto &p : ps)
        p.read();
    A.read();
    V.read();
    cin >> zv;
    cin >> f;
    U.read();
    cin >> zu;
    zu *= -1;
    f *= -1; // Negative number is not good for thinking
    calcf = U.abs()*f/zu;
    U = U*zv/zu;
    UV = U+V;
    //UV.write();
    calcuv = UV.abs();
    if(sign(U.det(V))) // U is not collinear with V
    {
        for(auto p : ps) getans(p); // Check all endpoints, Case 1
        for(int i = 0; i < n; i += 1)
        {
            P<db> cur;
            if(chkLL(A, A+UV, ps[i], ps[(i+1)%n])) // Check lines not parallel
            {
                cur = isLL(A, A+UV, ps[i], ps[(i+1)%n]); // Case 2
                if(onSeg(ps[i], ps[(i+1)%n], cur))
                    getans(cur);
            }
            if(chkLL(A, A+V, ps[i], ps[(i+1)%n]))
            {
                cur = isLL(A, A+V, ps[i], ps[(i+1)%n]); // Case 3
                if(onSeg(ps[i], ps[(i+1)%n], cur))
                    getans(cur);
            }
        }
    }
    else
    {
        if(sign(U.dot(V)) >= 0) // Same side
        {
            for(int i = 0; i < n; i += 1)
            {
                P<db> cur;
                if(chkLL(A, A+UV, ps[i], ps[(i+1)%n]))
                {
                    cur = isLL(A, A+UV, ps[i], ps[(i+1)%n]);
                    if(onSeg(ps[i], ps[(i+1)%n], cur) && sign(UV.dot(cur-A)) >= 0)
                        update((cur-A).abs()/calcuv, 0.0);
                }
            }
        }
        else // Different side
        {
            int isv = sign(V.abs()-U.abs());
            if(isv >= 0) // V is bigger
            {
                for(int i = 0; i < n; i += 1)
                {
                    P<db> cur;
                    if(chkLL(A, A+V, ps[i], ps[(i+1)%n]))
                    {
                        cur = isLL(A, A+V, ps[i], ps[(i+1)%n]);
                        if(onSeg(ps[i], ps[(i+1)%n], cur))
                        {
                            if(sign(V.dot(cur-A)) >= 0)
                            {
                                db t1 = (cur-A).abs()/V.abs();
                                update(t1, zv*t1/f);
                            }
                        }
                    }
                }
            }
            else
            {
                for(int i = 0; i < n; i += 1)
                {
                    P<db> cur;
                    if(chkLL(A, A+V, ps[i], ps[(i+1)%n]))
                    {
                        cur = isLL(A, A+V, ps[i], ps[(i+1)%n]);
                        if(onSeg(ps[i], ps[(i+1)%n], cur))
                        {
                            if(sign(V.dot(cur-A)) < 0) // Backway!
                                update((cur-A).abs()/calcuv, 0.0);
                            else
                            {
                                db t1 = (cur-A).abs()/V.abs();
                                update(t1, zv*t1/f);
                            }
                        }
                    }
                }
            }
        }
    }
    if(T1 > 1e9)
        cout << -1 << ' ' << -1;
    else
        cout << fixed << setprecision(7) << T1 << ' ' << T2;
    return 0;
}
```



---

