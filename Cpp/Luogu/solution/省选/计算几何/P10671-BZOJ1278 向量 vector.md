# BZOJ1278 向量 vector

## 题目描述

一个二维向量 $(x,y)$ 的权定义为 $x^2+y^2$。已知一个由 $n$ 个二维向量组成的集合，求该集合的一个子集，使该子集中的向量和的权尽可能大。

## 说明/提示

数据保证，$1\leq n\leq 100000$。

## 样例 #1

### 输入

```
3
1 1
1 0
0 -1```

### 输出

```
5.000```

# 题解

## 作者：Purslane (赞：7)

# Solution

典题，似乎做过。

结论：必定能找到一条直线，使得选取这条直线某一侧的所有点达到答案最大。（严格意义上同一侧，这条线上的点不选）

假设最终的向量是 $\vec v$，我们取垂直于它的直线 $l$。显然不可能有向量严格与 $l$ 重合，否则随便调整会使长度增加；如果 $l$ 和 $\vec v$ 同侧有一个向量没有被选中，选上他会让 $\vec v$ 增加，矛盾；如果 $l$ 和 $\vec v$  异侧有一个向量被选中了，将他取反就相当于撤销，这时候发现也是不优的。

-----------

如何找到 $l$？

一种想法是直接随机化，我不是很懂其正确性。

确定性做法是考虑双指针，将向量极角排序后维护两个指针 $l$ 和 $r$，使得排序后的第 $l$ 个向量和第 $r$ 个向量夹角严格小于 $\pi$。

这样一定会覆盖所有满足要求的集合。取最大值即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100000+10;
int n;
struct VEC {double x,y;}v[MAXN<<1],s;
double ans;
int getsq(VEC v) {
	if(v.x>=0&&v.y>=0) return 1;
	if(v.x<0&&v.y>=0) return 2;
	if(v.x<0&&v.y<0) return 3;
	return 4;	
}
bool operator <(VEC a,VEC b) {
	if(getsq(a)!=getsq(b)) return getsq(a)<getsq(b);
	return a.x*b.y-a.y*b.x>0;
}
VEC operator +(VEC A,VEC B) {return {A.x+B.x,A.y+B.y};}
VEC operator -(VEC A,VEC B) {return {A.x-B.x,A.y-B.y};}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>v[i].x>>v[i].y;
	VEC vc={0,0};
	ffor(i,1,n) vc=vc+v[i];
	sort(v+1,v+n+1);
	ffor(i,1,n) v[i+n]=v[i];
	int l=1,r=1; s=v[1],ans=max(ans,s.x*s.x+s.y*s.y);
	while(v[l].x*v[r+1].y-v[l].y*v[r+1].x>0) {
		r++,s=s+v[r],ans=max(ans,s.x*s.x+s.y*s.y);
	}	
	ffor(i,2,n) {
		l++,s=s-v[l-1];
		if(r<l) s=v[l],r=l;
		ans=max(ans,s.x*s.x+s.y*s.y);
		while(v[l].x*v[r+1].y-v[l].y*v[r+1].x>0) {
			r++,s=s+v[r],ans=max(ans,s.x*s.x+s.y*s.y);
		}
	}
	cout<<fixed<<setprecision(3)<<ans;
	return 0;
}
```

---

## 作者：Dr_April (赞：1)

### 题意

有 $n$ 个二维向量，要求选取向量集合的一个子集使得这个子集中向量和的 $x$ 坐标与 $y$ 坐标的平方和最大。
### 思路

这个题有一个结论：你一定能找到一个直线，让这个直线的某一侧的所有点答案最大。

现在题目就转化为找到这条直线。怎么找？我的想法就是直接随机化。

首先按极角排序，然后我们循环 $180$ 次，每次旋转向量一度，这样就相当于枚举过原点的直线，因为是旋转的向量，相当于在旋转 $y$ 轴，然后就把 $y$ 轴当做这条直线，按 $y$ 坐标的正负分成两个集合，然后计算答案。

显然，直线是有可能不过原点的，但是，这种看数据的方法的确过了。所以才叫随机化~~数据~~。

（代码？~~随机化都不会还当甚么 OIer~~)

---

## 作者：OIer_ACMer (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P5955)

# Solution
首先，我们可以把所有的向量想象成一种运动方案。

为方便统计，我们可以将运动方向选择后，连续选择符合条件的运动方案，毕竟根据向量性质，不同的加减方式，在选择的集合一定时，得到的结果一样。

由于我们要找距离源点最远的的运动结果，可以发现**只有在答案向量方向投影为正的向量**，才会对结果产生贡献，我们就要保证一开始的出发方案，与之后的每一次方案的夹角不会超过平角。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
struct node
{
    int x, y;
    double jiao;
} xian[1000009];
int n;
const double pi = acos(-1.0);
signed main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        cin >> xian[i].x >> xian[i].y;
        if (!xian[i].x && !xian[i].y)
        {
            i--;
            n--;
            continue;
        }
        xian[i].jiao = atan2(xian[i].y, xian[i].x);
    }
    sort(xian + 1, xian + n + 1, [](node a, node b) { return a.jiao < b.jiao; });
    double dx = 0, dy = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        xian[i + n] = xian[i];
        xian[i + n].jiao += 2 * pi;
    }
    for (int l = 1, r = 1; l <= n; l++)
    {
        while (r < n + n && xian[r].jiao - xian[l].jiao < pi + 1e-10)
        {
            dx += xian[r].x;
            dy += xian[r].y;
            r++;
            ans = max(ans, dx * dx + dy * dy);
            // cout << "ans=" << ans << endl;
        }
        dx -= xian[l].x;
        dy -= xian[l].y;
        ans = max(ans, dx * dx + dy * dy);
    }
    // double res = sqrt(ans);
    cout << fixed << setprecision(3) << ans << endl;
    return 0;
}
```

---

## 作者：WorldMachine (赞：0)

为了使答案最大，肯定只会选择在答案向量上投影为正的向量，也即选取的所有向量在同一半平面内。

于是考虑枚举半平面，这可以通过双指针实现。由于不一定要选出半平面中所有的点，因此要在移动右端点的过程中统计答案。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
const double pi = acos(-1);
int n;
ll Sx, Sy, sx, sy, ans;
struct point { int x, y; } a[N];
double angle(point a) { return atan2(a.y, a.x); }
bool cmp(point a, point b) { return angle(a) < angle(b); }
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y, Sx += a[i].x, Sy += a[i].y;
	sort(a + 1, a + 1 + n, cmp);
	for (int l = 1, r = 1; l <= n; l++) {
		while (r <= n && angle(a[r]) - angle(a[l]) < pi + 1e-8) sx += a[r].x, sy += a[r].y, ans = max({ans, sx * sx + sy * sy, (Sx - sx) * (Sx - sx) + (Sy - sy) * (Sy - sy)}), r++;
		sx -= a[l].x, sy -= a[l].y;
		ans = max({ans, sx * sx + sy * sy, (Sx - sx) * (Sx - sx) + (Sy - sy) * (Sy - sy)});
	}
	cout << ans;
}
```

---

