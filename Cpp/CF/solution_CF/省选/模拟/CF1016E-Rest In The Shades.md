# Rest In The Shades

## 题目描述

在第四象限有一个从 $A$ 沿线段 $AB$ 运动到 $B$ 的光源，速度为 $1$ 个单位/秒，在 $x$ 轴正半轴上有 $n$ 条互不重叠的线段，这些线段会遮挡住光线，在动点的运动过程中如图所示产生阴影，给你 $q$ 个第一象限内的点，询问每个点在阴影内的时间为多少秒。

## 样例 #1

### 输入

```
-3 1 6
2
2 4
6 7
5
3 1
1 3
6 1
6 4
7 6
```

### 输出

```
5.000000000000000
3.000000000000000
0.000000000000000
1.500000000000000
2.000000000000000
```

# 题解

## 作者：under_the_time (赞：2)

## 题意

> 平面上有一个点光源 $s$ 并以每秒 $1$ 单位长度的速度从点 $(a,sy)$ 移动到点 $(b,sy)$，其中 $sy<0$；在 $x$ 轴正方向上有 $n$ 不相交、不接触的挡板，第 $i$ 个档板挡住了 $x$ 轴上 $[l_i,r_i]$ 的部分。对于点 $(x,y)$，当它与 $s$ 的连线被某个挡板相交或接触时，我们说 $(x,y)$​ 在阴影中。
>
> 现在给定 $q$ 个平面上的点，求出这些点在 $s$ 移动过程中处于阴影内的总时间。

## 解法

![](https://cdn.luogu.com.cn/upload/image_hosting/a7l7jkx0.png)

- 黑色部分为 $x$ 轴，蓝色部分为挡板，红色部分为 $s$ 的移动范围。

如图，对于一个点 $P$，连接点 $P$ 和 $A,B$ 交 $x$ 轴于两点 $A',B'$（灰色粗线）。我们求出 $[A',B']$ 中挡板的占比后，就可以通过**相似三角形**（灰色、青色部分）求出 $[A,B]$ 上能让 $P$ 处于阴影中的总距离（深红色线）。我们将给定挡板按照 $x$ 坐标排序，两次二分求出 $A'$ 和 $B'$ 附近的挡板。预处理出挡板长度的前缀和统计这个点的贡献即可。具体见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
const double eps = 1e-9;
struct Nodes { // 同时表示 A,B 两个点和挡板左右边界。
    double x,y;
    Nodes (double u = 0, double v = 0) {
        x = u, y = v;
    }
} X,Y,a[maxn],now;
int n; double sum[maxn];
int Q;
int main() {
    scanf("%lf%lf%lf%d",&X.y,&X.x,&Y.x,&n);
    n ++, Y.y = X.y;
    for (int i = 2;i <= n;i ++)
        scanf("%lf%lf",&a[i].x,&a[i].y),
        sum[i] = sum[i - 1] + (a[i].y - a[i].x);
    a[++ n] = Nodes{1e18,1e18}, sum[n] = sum[n - 1];
    scanf("%d",&Q);
    while (Q --) {
        scanf("%lf%lf",&now.x,&now.y);
        double k = now.y / (now.y - X.y); // 相似三角形
        double L = (X.x - now.x) * k + now.x, R = (Y.x - now.x) * k + now.x;
        if (L <= a[1].x || R >= a[n].y) { // 特判
            printf("%.6f\n",0);
            continue;
        }
        // 两边二分求左右的挡板
        int l = 1, r = n; 
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a[mid].x <= L) l = mid;
            else r = mid - 1;
        }
        double ans = max(0.0,a[l].y - L) - sum[l];
        l = 1, r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (a[mid].y >= R) r = mid;
            else l = mid + 1;
        }
        ans += sum[r] - min(a[l].y - R, a[l].y - a[l].x);
        printf("%.7lf\n",ans * (Y.x - X.x) / (R - L)); 
    }
    return 0;
}
```

---

## 作者：lzyqwq (赞：1)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17545869.html)**

**[链接](https://www.luogu.com.cn/problem/CF1016E "链接")**

> - 给出第四象限的线段 $AB:y=s_y(a\le x\le b)$ 还有 $x$ 轴正半轴上 $n$ 条不相交的线段 $L_iR_i:y_i=0(l_i\le x\le r_i)$，以及 $q$ 个第一象限的整点 $P_i(x_i,y_i)$，有一动点 $Q$ 在 $AB$ 上，速度为 $1$ 单位每秒。称点 $P_i$ 在阴影内，当且仅当 $P_iQ$ 与任意一条 $L_jR_j$ 相交。求 $Q$ 运动过程中，每个点在阴影内的时间。
>
> - $n,q\le2\times 10^5$。

记从 $x$ 轴左到右第 $i$ 个端点为 $p_i$。

显然可以先算出挡住一个点的线段的总长度，然后平行线之间相似算对应 $Q$ 的路程以及时间。考虑 $Q$ 位于端点的情况，用待定系数法算出对应的 $P_iA,P_iB$ 与 $x$ 轴的交点 $x_1,x_2$，然后就是求 $[x_1,x_2]$ 与栅栏的交。先二分出**完全包含在** $[x_1,x_2]$ 内的左右两个端点 $ql,qr$。设 $s_i$ 为 $x$ 轴上 $x\in [0,p_i]$ 区间内线段总长，因为线段不相交所以若 $p_i$ 为左端点，则 $s_i=s_{i-1}$；否则 $s_i=s_{i-1}+r_{\frac{i}{2}}-l_{\frac{i}{2}}$。那么可以先计算 $[ql,qr]$ 内的长度为 $s_{qr}-s_{ql}$。最后判一下 $ql,qr$ 是左端点还是右端点，以 $ql$ 为例，如果 $ql$ 是右端点，则 $[x_1,ql]$ 也是被线段覆盖的，需要计算上。另一边同理。

时间复杂度为 $\mathcal{O}(q\log n)$，空间复杂度为 $\mathcal{O}(n+q)$。开了一堆 `double`，所以很慢。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
int n,q,cnt;
double sy,a,b,s[N],p[N];
double jiaox(double u,double v,double p,double q){
    return u==p?u:u-v*(p-u)/(q-v);
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>sy>>a>>b>>n;
    for(int i=1,l,r;i<=n;++i){
        cin>>l>>r;
        p[++cnt]=l;
        s[cnt]=s[cnt-1];
        p[++cnt]=r;
        s[cnt]=s[cnt-1]+r-l;
    }
    cin>>q;
    for(int i=1;i<=q;++i){
        double x,y;
        cin>>x>>y;
        double l=jiaox(a,sy,x,y),r=jiaox(b,sy,x,y);
        int ql=lower_bound(p+1,p+1+cnt,l)-p,qr=upper_bound(p+1,p+cnt+1,r)-p-1;
        if(ql>qr){
            cout<<fixed<<setprecision(16)<<(qr&1?b-a:0)<<'\n';
        }else{
            cout<<fixed<<setprecision(16)<<(s[qr]-s[ql]+(ql&1?0:p[ql]-l)+(qr&1?r-p[qr]:0))*(b-a)/(r-l)<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：Wisdom (赞：1)

相似

![](https://images2018.cnblogs.com/blog/1130834/201808/1130834-20180810102742853-526383341.png)

红色的长度等于（y - s） /  y 倍的 A' 和 B' 之间的 fence的长度

A' 是 p 和 A 连线和 x 轴交点， B'同理

交点也可以用相似求，然后lower_bound找到交点在哪里，然后通过预处理的fence长度的前缀和就可以求了，处理好边界
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize(4)
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pi acos(-1.0)
#define LL long long
//#define mp make_pair
#define pb push_back
#define ls rt<<1, l, m
#define rs rt<<1|1, m+1, r
#define ULL unsigned LL
#define pll pair<LL, LL>
#define pii pair<int, int>
#define piii pair<pii, int>
#define pdd pair<double, double>
#define mem(a, b) memset(a, b, sizeof(a))
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define fopen freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
//head

const int N = 2e5 + 5;
pdd f[N];
double sum[N];
int main() {
    int n, q, l, r;
    double s, a, b, x, y;
    scanf("%lf %lf %lf", &s, &a, &b);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf %lf", &f[i].fi, &f[i].se);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + f[i].se - f[i].fi;
    }
    scanf("%d", &q);
    while(q--) {
        scanf("%lf %lf", &x, &y);
        double c1 = (a*y - s*x)/(y - s);
        double c2 = (b*y - s*x)/(y - s);
        int t = lower_bound(f+1, f+n+1, pdd(c1, 0)) - f;
        double ans = 0;
        if(t == 1) l = 1;
        else {
            l = t;
            if(c1 < f[t-1].se) ans += f[t-1].se - c1;
        }
        int tt = lower_bound(f+1, f+n+1, pdd(c2, 0)) - f;
        if(tt == 1) r = tt-1;
        else {
            r = tt-1;
            if(c2 < f[tt-1].se) ans -= f[tt-1].se - c2;
        }
        if(r >= l) ans += sum[r] - sum[l-1];
        printf("%.10f\n", ans * (y - s) / y);
    }
    return 0;
}
```

---

## 作者：大菜鸡fks (赞：0)

注意到造成阴影的栅栏区间是连续的，二分解决边界。之后相似三角形算贡献

注意二分的时候添加哨兵

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+5;
const double eps=1e-9,INF=1e9;
double sy,a,b,sum[N],l[N],r[N];
int n;
inline void init(){
	scanf("%lf%lf%lf",&sy,&a,&b);
	scanf("%d",&n); n++;
	l[1]=r[1]=0; 
	for (int i=2;i<=n;i++){
		scanf("%lf%lf",&l[i],&r[i]);
		sum[i]=sum[i-1]+(r[i]-l[i]);
	}
	l[++n]=r[n]=INF;
	sum[n]=sum[n-1];
} 
int q;
inline void solve(){
	scanf("%d",&q); 
	for (int i=1;i<=q;i++){
		double x,y;
		scanf("%lf%lf",&x,&y);
		double sfb=y/(y-sy);
		double pax=a-x,pbx=b-x;
		pax*=sfb; pbx*=sfb;
		pax+=x; pbx+=x;
		if (pbx<=l[1]){
			printf("0.00000000\n");
			continue;
		}
		if (pax>=r[n]){
			printf("0.00000000\n");
			continue;
		}
		double ans=0;
		int L=1,R=n; 
		while (L<R){
			int mid=(L+R+1)>>1;
			if (l[mid]<=pax) L=mid;
				else R=mid-1;
		}
		ans-=sum[L]-max(0.0,r[L]-pax);
		L=1,R=n;
		while (L<R){
			int mid=(L+R)>>1;
			if (r[mid]>=pbx) R=mid;
				else L=mid+1;
		}
		ans+=sum[R];
		ans-=min(r[L]-pbx,r[L]-l[L]);
		ans=ans*(b-a)/(pbx-pax); 
		printf("%.7lf\n",ans);
	}
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

