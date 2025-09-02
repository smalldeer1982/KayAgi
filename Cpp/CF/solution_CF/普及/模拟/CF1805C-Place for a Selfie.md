# Place for a Selfie

## 题目描述

The universe is a coordinate plane. There are $ n $ space highways, each of which is a straight line $ y=kx $ passing through the origin $ (0, 0) $ . Also, there are $ m $ asteroid belts on the plane, which we represent as open upwards parabolas, i. e. graphs of functions $ y=ax^2+bx+c $ , where $ a > 0 $ .

You want to photograph each parabola. To do this, for each parabola you need to choose a line that does not intersect this parabola and does not touch it. You can select the same line for different parabolas. Please find such a line for each parabola, or determine that there is no such line.

## 说明/提示

In the first test case, both parabolas do not intersect the only given line $ y=1\cdot x $ , so the answer is two numbers $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1805C/18de32de6fde4236646d351f878d2be05006f8bc.png)In the second test case, the line $ y=x $ and the parabola $ 2x^2+5x+1 $ intersect, and also the line $ y=4x $ and the parabola $ x^2+2x+1 $ touch, so these pairs do not satisfy the condition. So for the first parabola, the answer is $ 1 $ ( $ y=1x $ ), and for the second parabola — $ 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1805C/58b8a5a9448e772cebadc5139da584db388c8262.png)In the third test set, the line and the parabola intersect, so the answer is "NO".

## 样例 #1

### 输入

```
5
1 2
1
1 -1 2
1 -1 3
2 2
1
4
1 2 1
2 5 1
1 1
0
1 0 0
1 1
100000000
100000000 100000000 100000000
2 3
0
2
2 2 1
1 -2 1
1 -2 -1```

### 输出

```
YES
1
YES
1

YES
1
YES
4

NO

YES
100000000

YES
0
NO
NO```

# 题解

## 作者：spider_oyster (赞：4)

~~水一波 tj。~~

纯纯数学题。考虑 $y=ax^2+bx+c$ 与 $y=kx$ 没有交点，则方程 $ax^2+(b-k)x+c=0$ 的 $\Delta=(b-k)^2-4ac<0$。

我们把给的 $k$ 排序，用 $x=\frac{-b\pm \sqrt \Delta}{2a}$ 算出 $k$ 的两个解，二分查找一下即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N=1e5+5;
ll n,m,k[N];
 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>k[i];
		sort(k+1,k+1+n);
		for(int i=1;i<=m;i++)
		{
			ll a,b,c;cin>>a>>b>>c;
			long double aa=b*b-4*a*c,bb=b*2;//感觉会爆long long 
			if(bb*bb-4*aa<0) {cout<<"NO\n";continue;}//Delta<0 直接没解。 
			ll x=(bb+sqrtl(bb*bb-4*aa))/2,y=(bb-sqrtl(bb*bb-4*aa))/2;//算 (b-k)^2-4ac=0 的 k，再枚举一下
			x=lower_bound(k+1,k+1+n,x)-k,y=lower_bound(k+1,k+1+n,y)-k;
			int p=-1;
			for(int i=max(1ll,x-1);i<=min(n,x+1);i++) if((b-k[i])*(b-k[i])-4*a*c<0) {p=i;break;}
			for(int i=max(1ll,y-1);i<=min(n,y+1);i++) if((b-k[i])*(b-k[i])-4*a*c<0) {p=i;break;}
			if(p==-1) cout<<"NO\n";
			else cout<<"YES\n"<<k[p]<<'\n';
		}
		cout<<'\n';
	}
}
```


---

## 作者：快乐的大童 (赞：3)

### 题目大意
给定 $n$ 个正比例函数 $y=kx$，再给出 $m$ 个下凸二次函数 $y=ax^2+bx+c(a>0)$，对于每个二次函数，从给定中找出一个一次函数，使得两函数图像没有交点。

$\sum n,\sum m\le 10^5$，$a,|b|,|c|,|k|\le 10^8$。
### 思路
此做法不需要二次函数的下凸性质，且几乎不需要初四课本内容。

初一老师告诉我们，二次函数 $y=ax^2+bx+c$ 和正比例函数 $y=kx$ 相交当且仅当 $ax^2+bx+c=kx$ 有解（其他函数也是这样）。

而题目让我们求不相交的函数，那么就是让方程 $ax^2+bx+c=kx$ 无解（准确来说是无实根，以下沿用无解），即 $ax^2+(b-k)x+c=0$ 无解。

初三老师告诉我们，二元一次方程无解的充要条件是 $b^2-4ac<0$。体现在原方程上就是 $(b-k)^2-4ac<0$。

将式子转化一下（其实可以不转化）成 $b^2-4ac-(2bk-k^2)$，发现 $b^2-4ac$ 是定值，如果我们要让这串东西小于 $0$，相当于要让 $2bk-k^2$ 更大。

由于 $y=2bk-k^2$（$b$ 为常数）是上凸二次函数，所以可以保证是单峰的。将一次函数数组排序去重后二分出使 $2bk-k^2$ 更大的那个 $k$，将这个 $k$ 代入 $(b-k)^2-4ac$ 验证是否小于 $0$，这题就做完了。
### 代码
```cpp
//仅提供主要部分
//read()快读，writeln()快输+换行
//注意开longlong
int calc(int x){
	if(x==0||x==n+1) return -maxllinf;//就是longlong下自己定义的极小值
	x=k[x];
	return 2*b*x-x*x;
}
void solve_the_problem(){
	n=R(),m=R();rep(i,1,n)k[i]=R();
	sort(k+1,k+n+1);
	n=unique(k+1,k+n+1)-(k+1);//注意去重！
	rep(i,1,m){
		a=R(),b=R(),c=R();
		int l=1,r=n,ans=0;
		while(l<=r){
			int mid=l+r>>1;
			if(calc(mid-1)<=calc(mid)&&calc(mid)>=calc(mid+1)){
				ans=mid;
				break;
			}
			if(calc(mid-1)<=calc(mid)&&calc(mid)<=calc(mid+1)) l=mid+1;
			else r=mid-1;
		}
		if(b*b-4*a*c-calc(ans)<0&&ans) PY,writeln(k[ans]);
		else PN;
	}
	puts("");
}
```


---

## 作者：Mr_Gengar (赞：2)

一道小清新数学题。

考虑联立两函数求交点，列出方程 $ax^2+bx+c=kx$。

移项，将方程变形为 $ax^2+(b-k)x+c=0$。

若无交点则原方程无实数解，根据一元二次方程基础知识，此时 $\Delta<0$，即 $(b-k)^2-4ac<0$。

因为对于同一个二次函数 $4ac$ 显然为定值，为使 $\Delta<0$，我们需要最小化 $(b - k)^2$，即令 $\lvert b - k \rvert$ 尽量小。

考虑对给定正比例函数排序后使用二分解决问题。

单次询问时间复杂度为 $O(m \log n)$，可以通过此题。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int kMaxN = 3e5 + 1;

LL t, n, m, k, a, b, c;
vector<LL> d;

bool C(int x) {
  return (b - d[x]) * (b - d[x]) < 4 * a * c;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n >> m, d.clear();
    for (int i = 1; i <= n; i++) {
      cin >> k, d.push_back(k);
    }
    sort(d.begin(), d.end());
    for (int i = 1; i <= m; i++) {
      cin >> a >> b >> c;
      k = lower_bound(d.begin(), d.end(), b) - d.begin();
      if (k < n && C(k)) {
        cout << "Yes\n"
             << d[k] << "\n";
      } else if (k && C(k - 1)) {
        cout << "Yes\n"
             << d[k - 1] << "\n";
      } else {
        cout << "No\n";
      }
    }
  }
  return 0;
}
```

---

## 作者：BLuemoon_ (赞：1)

[link](https://www.luogu.com.cn/problem/CF1805C)

## 思路

两个函数 $f(x),g(x)$ 没有交点，即 $f(x) \ne g(x)$ 对于每一个 $x$ 均成立。

在本题中，这个方程为 $ax^2 + bx + c \ne kx$。

移项得：$ax^2 + (b - k)x + c \ne 0$。

设 $f(x) = ax^2 + (b - k)x + c$，那么函数 $f(x)$ 与 $x$ 轴无交点。

根据二次函数的定义，则 $\Delta = (b-k)^2 - 4ac < 0$。

再次移项得：$(b-k)^2 < 4ac$。

因为平方有非负性，所以 $k$ 越接近 $b$，不等式就越可能成立。

那么二分与 $b$ 最接近的 $k$，如果最接近的都不行，那么只能输出 `NO` 了。

单次时间复杂度 $O(m \log n)$。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 1e5 + 5;

LL t, n, m, k[kMaxN], a, b, c;

int main() {
  for (cin >> t; t; t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> k[i];
    }
    sort(k + 1, k + n + 1);
    for (; m; m--) {
      cin >> a >> b >> c;
      int x = lower_bound(k + 1, k + n + 1, b) - k;
      if (x != n + 1 && (b - k[x]) * (b - k[x]) < 4 * a * c) {
        cout << "YES\n" << k[x] << '\n';
      } else if (x != 1 && (b - k[x - 1]) * (b - k[x - 1]) < 4 * a * c) {
        cout << "YES\n" << k[x - 1] << '\n';
      } else {
        cout << "NO\n";
      }
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：atomic_int (赞：1)

### Analysis

如果 $y=ax^2+bx+c$ 和 $y=kx$ 有交点，说明存在 $x$ 使得 $ax^2+bx+c=kx$。移项后为 $ax^2+(b-k)x+c=0$，$\Delta = (b-k)^2-4ac$，当 $\Delta < 0$ 的时候方程无解，也就没有交点。最小化 $(b-k)^2$，将 $k$ 排序后二分查找 $\ge b$ 的最小的数和 $< b$ 的最大的数，其中一个满足要求即可。

### Code

```cpp
void solve() {
  int n, m;
  cin >> n >> m;
  vector<ll> k(n);
  for (int i = 0; i < n; i++) {
    cin >> k[i];
  }
  sort(k.begin(), k.end());
  for (int i = 0; i < m; i++) {
    ll a, b, c;
    cin >> a >> b >> c;
    bool ok = false;
    int p = lower_bound(k.begin(), k.end(), b) - k.begin();
    for (auto x : {p - 1, p}) {
      if (x < 0 || x >= n) {
        continue;
      }
      ll h = k[x];
      if ((b - h) * (b - h) - 4ll * a * c < 0) {
        ok = true;
        cout << "YES\n" << h << "\n";
        break;
      } 
    }
    if (!ok) {
      cout << "NO\n";
    }
  }
  cout << "\n";
}
```

---

## 作者：zhangslover (赞：0)

# CF1805C
**本题解用的是初高中知识，以初二牲的方式思考编写**

## 题目描述

给定 $n$ 个正比例函数 $y=kx$，再给出 $m$ 个下凸二次函数 $y=ax^2+bx+c(a>0)$，对于每个二次函数，从给定中找出一个一次函数，使得两函数图像没有交点。

$\sum n,\sum m\le 10^5$，$a,|b|,|c|,|k|\le 10^8$。

**核心知识：一元二次方程无解的条件，一次函数，二次函数，二分。**

-----------

## 思路

首先，二次函数 $y=ax^2+bx+c$ 与一次函数 $y=kx$ 的交点的横坐标就是方程 $ax^2+bx+c=kx$ 的解。

我们将原方程移项，提公因式，可以变为 $ax^2+(b-k)x+c=0$ 的一元二次方程。

（其中 $a=a,b=b-k,c=c$ ) 

而题目要求两函数图像无交点，即这个方程无实数解。

为什么呢？我们来回想一下数轴能表示的数的范围：实数。

也就是说，数轴不能表示虚数。而平面直角坐标系是由两条数轴组成的，两条函数又交在这个坐标系里。


**言外之意，两函数交点的横坐标不可能为复数**

现在来让我们回想一下一元二次方程解的三种情况：

1. 当 $\Delta>0$，方程有两个不相等的实数根。
2. 当 $\Delta=0$，方程有两个相等的实数根。
3. 当 $\Delta<0$，方程在虚数范围内有两个共轭复根。（如果没学过，可以视为无解）

其中 $\Delta=b^2-4ac$.

回到题目的条件，要是使方程 $ax^2+(b-k)x+c=0$ 无解，只需要使 $\Delta<0$ 就可以了。

而这个式子的 $\Delta$ 化简即为

$$ (b^2-4ac)-(2bk-k^2)$$

而由于 $(b^2-4ac)$ 是定值，要想使这一串式子最小，那么就让 $(2bk-k^2)$ 最大就可以了。

我们设一个以 $k$ 为自变量的函数 $y=-k^2+2bk$, 因为二次项系数 $-1<0$,所以抛物线开口向下。

且通过配方我们可以把这个式子化成形如 $y=a(x-h)^2+k$ 的式子（由二次函数图像性质我们知道 $h$ 为对称轴，顶点坐标为 $(h,k)$）:

$$ y=a(x+\frac{b}{2a})^2+\frac{4ac-b^2}{4a}$$

$$  =a(x-\frac{2b}{2})^2+\frac{4b^2}{4}$$

$$  =a(x-b)^2+b^2 $$

其中 $h=b,k=b^2$

所以：

1. 当 $k<h$ 时，$y$ 随 $k$ 的增大而增大。
2. 当 $k>h$ 时，$y$ 随 $k$ 的增大而减小。


得到了这样的一个关系之后，我们就可以二分找出使函数最大的 $k$ 的值，带入 $\Delta$ 验证是否小于 $0$ 即可


---

## 作者：Clay_L (赞：0)

### 题意简述

由于翻译太明了并且我太菜了，所以就不写了。

### 算法分析

~~这不纯纯小学二年级学的判断函数是否相交吗？~~

由小学二年级学的判断函数是否相交的方法得：要使两条函数 $f\left(x\right)$ 和 $g\left(x\right)$ 不相交，当且仅当 $f\left(x\right)=g\left(x\right)$ 无解。

然后推式子：

设 $f\left(x\right)=ax^2+bx+c,g\left(x\right)=kx$，则有 $ax^2+bx+c=kx$ 无解，即 $ax^2+\left(b-k\right)x+c=0$ 无解，所以 $\Delta=\left(b-k\right)^2-4ac<0$，即 $\left(b-k\right)^2<4ac$。

当 $4ac\le0$ 时，易证 $\Delta\ge0$；

当 $4ac>0$ 时，由 $\left(b-k\right)^2<4ac$ 得 $-\sqrt{4ac}<b-k<\sqrt{4ac}$，即 $b-\sqrt{4ac}<k<b+\sqrt{4ac}$。

$k$ 的取值范围推出来之后就好办了：二分求一下：

$$
\min_{1\le i\le n\wedge k_i>b-\sqrt{4ac}}{k_i}
$$

然后判断刚才求的 $k$ 值是否满足 $b-\sqrt{4ac}<k<b+\sqrt{4ac}$ 即可。

---

## 作者：xyzqwq (赞：0)

水水数学题，但我做复杂了（）

本题有更简单做法，在此提供一种数学含量较高的做法。

**题意分析**

题目要求对每个抛物线求一个不交的正比例函数，如图

![](https://cdn.luogu.com.cn/upload/image_hosting/n1022n8w.png)

图中列出了斜率在 $[-1,3]$ 区间内的正比例函数，而 $y=-x$ 和 $y=3x$ 两个函数与 $y=x^2+x+1$ 相切。

这使我们很容易看出，若存在两个与抛物线相切的正比例函数 $y_1=k_1 x$，$y_2=k_2 x$，则斜率在 $(\min(k_1,k_2),\max(k_1,k_2))$ 区间内的正比例函数都与抛物线不交。

现在的工作就转为推导与抛物线相切的正比例函数。

**公式推导**

首先设抛物线上任意一点为 $P(x_0,ax_0^2+bx_0+c)$，此刻在 P 处的切线公式为 

$$y=(2ax_0+b)x+[ax_0^2+bx_0+c-(2ax_0+b)x_0]=(2ax_0+b)x-ax_0^2+c$$


若欲这个切线是正比例函数，只需令它的非线性部分为 0，即

$$
-ax_0^2+c=0
$$

解出抛物线切的两条正比例函数的 x 坐标分别为

$$
x_1=\sqrt{\frac{c}{a}},x_2=-\sqrt{\frac{c}{a}}
$$

所以两条切抛物线的正比例函数斜率分别为

$$
k_1=-2a\sqrt{\frac{c}{a}}+b

\\

k_2=2a\sqrt{\frac{c}{a}}+b
$$

**核心代码**

只需二分找出一个斜率在 $(k_1,k_2)$ 区间内的正比例函数即可，若无，即说明无解，核心代码如下

```cpp
double k1=-2*a*sqrt(c/a)+b;
double k2=2*a*sqrt(c/a)+b;
int k=lower_bound(v+1,v+1+n,k1)-v;
if(v[k]<k2&&v[k]>k1) cout<<"YES\n"<<(int)v[k]<<endl;
else cout<<"NO\n";
```

---

## 作者：aCssen (赞：0)

### Solution
纯数学题。

两个函数图像没有交点，当且仅当方程 $ax^2+bx+c=kx$ 无解，证明显然。

因为方程 $ax^2+bx+c=kx$ 等价于 $ax^2+(b-k)x+c=0$，所以当 $(b-k)^2-4ac<0$ 时有我们需要的函数。

上式可以化为 $k^2-2kb<4ac-b^2$，令 $f_b(x)=x^2-2bx$，则原式等价于 $f_b(k) <4ac-b^2$，基于贪心的策略，我们想要 $f_b(x)$ 最小。

因为函数 $f_b(x)=x^2-2bx$ 的二次项系数大于 $0$，所以当 $x=\frac{-2b}{-2}=b$ 时，$f_b(x)$ 取到最小值，而 $|k-b|$ 越小，$f_b(x)$ 也就越小。

所以我们对于每个二次函数，我们找 $k$ 中 $b$ 的前驱和后继，这一步可以用二分做，选取更接近 $b$ 的那个，检查是否满足上式即可。

时间复杂度 $\mathcal{O}(\sum m \log n)$。

细节比较多，具体见注释。
### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1e5+5;
int k[maxn],n,m;
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&k[i]);
	sort(k+1,k+n+1);
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		int p2=lower_bound(k+1,k+n+1,b)-k;//第一个大于等于 b 的数即 b 的后继
		int p1=p2-1;//前一个位置即是 b 的前驱
		if(!p1&&p2>n){//既没有前驱，也没有后继
			printf("No\n");
			continue;
		}
     //用 p1 作最终位置
		if(b-k[p1]>k[p2]-b&&p2<=n&&p1) p1=p2;//如果 p2 离 p1 更近且 p1,p2 都存在，用 p2 更新 p1
		if(!p1) p1=p2;//如果没有 p1，也用 p2 更新，p1,p2 都没有的情况已经判过了
		p1=k[p1];//把位置换成真实的 k 值
		if(1ll*p1*p1-2ll*p1*b<4ll*a*c-1ll*b*b) printf("Yes\n%d\n",p1);//检查，记得开 long long
		else printf("No\n");
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

