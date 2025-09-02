# [CCC 2008 S2] Pennies in the Ring

## 题目描述

游戏“环中的便士”通常由厌倦了玩纸牌的无聊计算机程序员玩。目标是看看可以在一个圆中放多少便士。圆画在一个网格上，其中心在坐标 $(0, 0)$。在每个整数网格坐标（例如，$(1, 1)$，$(1, 2)$ 等）上放置一个便士，该坐标位于圆内或圆上。这不是一个非常刺激的游戏，但非常适合消磨时间。你的目标是计算给定半径的圆需要多少便士。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
3
4
0```

### 输出

```
13
29
49```

# 题解

## 作者：ivyjiao (赞：1)

怎么没找到 $T$ 的数据范围啊？在这里钦定 $1\leq T\leq 25000$ 吧。

根据初中数学可以得出，原问题等于求： $x^2+y^2\leq n^2$ 的整数对 $(x,y)$ 的有序对数。

这题我想了 1h 的线性做法，~~然后发现好像没有~~。

这题我们显然可以打一个 $O(Tn^2)$ 的暴力出来：

```
#include<bits/stdc++.h>
using namespace std;
int n,sum,a[25001];
int main(){
    while(cin>>n&&n){
        if(!a[n]){
            sum=0;
            for(int i=1;i<=n;i++){
                for(int j=1;i*i+j*j<=n*n;j++) sum++;
            }
            a[n]=4*sum+4*n+1;
            cout<<4*sum+4*n+1<<endl;
        }
        else cout<<a[n]<<endl;
    }
}
```

这样显然是不行的，$T$ 取 $25000$ 然后每个 $n$ 不同分分钟可以给你卡到 $n^3$ 级别，根本过不了。

[~~哎？怎么过了？~~](https://www.luogu.com.cn/record/135429423)肯定是因为数据水，我们接着考虑怎么优化：

容易发现每次的内层循环中，$i^2$ 的值是一定的，$j^2$ 的值可以通过预处理整出来，然后每次二分求解，所以内层可以被优化到 $\log n$ 级别。

时间复杂度 $O(Tn\log n)$。

```
#include<bits/stdc++.h>
using namespace std;
int n,sum,a[25001],b[25001];
int main(){
    for(int i=1;i<=25000;i++) b[i]=i*i;
    while(cin>>n&&n){
        if(!a[n]){
            sum=0;
            for(int i=1;i<=n;i++){
                int l=0,r=25000;
                while(l<r){
                    int mid=l+r+1>>1;
                    if(b[mid]<=n*n-i*i) l=mid;
                    else r=mid-1;
                }
                sum+=l;
            }
            a[n]=4*sum+4*n+1;
            cout<<4*sum+4*n+1<<endl;
        }
        else cout<<a[n]<<endl;
    }
}
```

然而这种做法似乎也过不去，因为还是那样，如果 $T$ 取 $25000$ 然后每个 $n$ 不同分分钟可以给你卡满，而卡满的情况下大约需要跑 $10^{10}$ 次，也过不了。

[~~哎？怎么又过了？~~](https://www.luogu.com.cn/record/135436469)肯定是因为数据水，我们接着考虑怎么优化：

这时候肯定就有人说了：你前面说没有线性做法，现在又说单 $\log$ 过不去，难道除了线性有什么东西比单 $\log$ 还快吗？

确实没有，但是我们充分发扬人类智慧，直观感受一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/wc64odrg.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

我们感觉到：在矩形中，包含在圆里的点的数量一定比不包含在圆里的点的数量多很多，也就是说，设 $m=n\times 2+1$，最终的答案一定是 $m^2-4\times$ 一个很小的数字。

我们考虑枚举每一个不在圆里的点，也就是找出那个很小的数字，这个跟那个暴力差不多，时间复杂度 $O(Tn^2)$，但是严重跑不满，最终过了。

```
#include<bits/stdc++.h>
using namespace std;
int n,sum,a[25001];
int main(){
    while(cin>>n&&n){
        if(!a[n]){
            sum=0;
            for(int i=1,j=n;i<=n;i++){
				j=n;
                while(i*i+j*j>n*n) sum++,j--;
            }
            a[n]=(n*2+1)*(n*2+1)-4*sum;
            cout<<(n*2+1)*(n*2+1)-4*sum<<endl;
        }
        else cout<<a[n]<<endl;
    }
}
```

附[极限数据一组](https://www.luogu.com.cn/problem/U382938)，供大佬们调试用。

---

## 作者：xiangyanhao (赞：0)

暴力做法：枚举 $x\in[-r,r],y\in[-r,r]$ 的所有整数点 $(x,y)$，会 TLE。

利用公式 $x^2+y^2=r^2$，可以优化掉一层循环，然后就可以 AC 了。核心代码如下：

```cpp
int ans = 0;
for(int x = -r;x <= r;x++){
	double y = sqrt(r*r-x*x);
	ans += floor(y)*2+1;
}
cout << ans << endl;
```

---

## 作者：noi2077 (赞：0)

我们只需要求一个 $\frac 14$ 圆的答案，然后乘以 $4$ 再加 $1$ 就是答案（加 $1$ 是因为圆心也在圆内）。

点 $(x,y)$ 在圆内就是 $x^2+y^2\le r^2$，我们枚举每个 $x$，不难发现对应的 $y$ 的个数为 $\sqrt{r^2-x^2}$，然后求和就行。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
    long long r;
    while(cin >> r, r)
    {
        long long ans = 0;
        for(int i = 0; i <= r; i++)
        {
            ans += sqrtl(r*r-i*i);
        }
        cout << ans*4+1 << endl;
    }
    return 0;
}
```

---

