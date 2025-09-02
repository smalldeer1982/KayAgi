# [ABC130F] Minimum Bounding Box

## 题目描述

平面上有 $N$ 个点，第 $i$ 个点的坐标是 $(x_i, y_i)$。现在，每个点开始沿着 $x$ 轴或 $y$ 轴方向以 $1$ 格每秒的速度移动。字符 $d_i$ 表示第 $i$ 个点的方向：

* 如果 $d_i=$`R`，第 $i$ 个点沿 $x$ 轴正方向移动；
* 如果 $d_i=$`L`，第 $i$ 个点沿 $x$ 轴负方向移动；
* 如果 $d_i=$`U`，第 $i$ 个点沿 $y$ 轴正方向移动；
* 如果 $d_i=$`D`，第 $i$ 个点沿 $y$ 轴负方向移动；

点开始移动后，你可以选择任意一个时刻（包括刚刚开始的那个时刻）停止所有点。停止后，分别记 $x_{max},x_{min}$ 为 $N$ 个点中 $x$ 坐标的最大值、最小值；同样，记 $y_{max},y_{min}$ 为 $N$ 个点中 $y$ 坐标的最大值、最小值。

你需要找出 $(x_{max}-x_{min})\times(y_{max}-y_{min})$ 的最小值并输出这个值。

## 说明/提示

* $1 \le N \le 10^5$。
* $-10^8 \le x_i, y_i \le 10^8$。
* $x_i,y_i$ 都是整数。
* $d_i$ 是 `R`、`L`、`U`、`D` 的其中之一。


#### 样例 1/样例 4

第 $3$ 秒，两点在原点相遇，此时的答案是 $0$。

#### 样例 2/样例 5

答案也许不是整数。

## 样例 #1

### 输入

```
2
0 3 D
3 0 L```

### 输出

```
0```

## 样例 #2

### 输入

```
5
-7 -10 U
7 -6 U
-8 7 D
-3 3 D
0 -6 R```

### 输出

```
97.5```

## 样例 #3

### 输入

```
20
6 -10 R
-4 -9 U
9 6 D
-3 -2 R
0 7 D
4 5 D
10 -10 U
-1 -8 U
10 -6 D
8 -5 U
6 4 D
0 3 D
7 9 R
9 -4 R
3 10 D
1 9 U
1 -6 U
9 -8 R
6 7 D
7 -3 D```

### 输出

```
273```

# 题解

## 作者：CarroT1212 (赞：4)

### 题目大意

平面上有 $N$ 个点，初始位置为 $(x_i,y_i)$，分别给定它们的运动方向（有上下左右四种），每个点可以在一单位时间内向给定的方向移动一格。设它们开始运动之后，$x_{\max}$ 为所有点中横坐标的最大值，$x_{\min}$ 为所有点中横坐标的最小值，$y_{\max},y_{\min}$ 同理，问 $(x_{\max}-x_{\min})(y_{\max}-y_{\min})$ 的最小值是多少。（$1 \le N \le 10^5$，$|x_i|,|y_i|\le 10^8$）

### 解法分析

模拟赛遇到这题，做法太臭没写完，赛后发现弱智了，写篇题解纪念一下。

赛场上想的是把 $x_{\max},x_{\min},y_{\max},y_{\min}$ 变化的分段函数解析式求出来，然后就能把 $(x_{\max}-x_{\min}),(y_{\max}-y_{\min})$ 的解析式也求出来，最后再把 $(x_{\max}-x_{\min})(y_{\max}-y_{\min})$ 解析式求出来并对每一段三分求它们乘积的最小值。但是细节极多，每一次复合两个函数都会使段数翻几倍，而且并不是往每一个方向走的点都有，特殊情况能装一车，场上打出来大概是别想了。

这时其实应该考虑这些值的变化本身有什么性质。

以 $x_{\max}$ 为例，它的变化有这几种：

+ 被一个竖着走的点全程霸占。（全程不变）
+ 被一个向右走的点全程霸占。（全程持续增加）
+ 被一个向左走的点全程霸占。（全程持续减小）
+ 一个竖着走的点霸占一段时间后被另一个往右走的点抢了。（初始不变，一段时间后转为持续增加）
+ 一个往左走的点霸占一段时间后被一个竖着走的点抢了。（初始持续减小，一段时间后转为不变）
+ 一个往左走的点霸占一段时间后被一个往右走的点抢了。（初始持续减小，一段时间后转为持续增加）
+ 一个往左走的点霸占一段时间后被一个竖着走的点抢了然后又被一个往右走的点抢了。（初始持续减小，一段时间后转为不变，又一段时间后转为持续增加）

可以发现，它们变化的过程其实都可以看作是一个先减少后增加的函数（暂且把没减少或者没增加的也算进去罢）。同理，$x_{\min}$ 变化的过程可以看作是一个先增加后减少的函数。那它们一减不就又是一个先减后增的函数了？

同理，$(y_{\max}-y_{\min})$ 变化的过程也是一个先减后增的函数。

那这俩一乘，因为 $(x_{\max}-x_{\min}),(y_{\max}-y_{\min})$ 都始终是非负数，那整个 $(x_{\max}-x_{\min})(y_{\max}-y_{\min})$ 也就还是一个先减后增的函数。可能不是很严谨，但意思对就行。

所以直接对整个 $(x_{\max}-x_{\min})(y_{\max}-y_{\min})$ 三分就行了……

另外本题卡精度比较恶心，建议三分 $500$ 次，少了可能会 WA，多了可能会 T。

------------

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vo void()
using namespace std;
const ll N=1e5+7;
ll n;
ld cx[N],cy[N];
char d[N][2];
ld chk(ld mid) {
	ld xx=-1e18,xn=1e18,yx=-1e18,yn=1e18;
	for (ll i=1;i<=n;i++) {
		ld x=cx[i],y=cy[i];
		if (d[i][0]=='U') y+=mid;
		else if (d[i][0]=='D') y-=mid;
		else if (d[i][0]=='L') x-=mid;
		else if (d[i][0]=='R') x+=mid;
		xx=max(xx,x),xn=min(xn,x),yx=max(yx,y),yn=min(yn,y);
	}
	return (xx-xn)*(yx-yn);
}
int main() {
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++) scanf("%Lf%Lf%s",&cx[i],&cy[i],d[i]);
	ld l=0,r=2e8,mid1,mid2;
	for (ll i=0;i<500;i++) {
		mid1=(l*2+r)/3,mid2=(l+r*2)/3;
		if (chk(mid1)<chk(mid2)) r=mid2;
		else l=mid1;
	}
	printf("%.15Lf",chk(mid1));
	return 0;
}
```

---

## 作者：Acfboy (赞：2)

这题分讨略有点恶心啊。

题面给了一堆运动的点，要求一个时刻时正着覆盖所有点的最小矩形最小。

脑补了一下觉得这是一个单峰函数，于是想着三分，但是又不太确定，所以没写。

模拟一下可以发现，很多点其实是对答案没有影响的，因为它们的运行速度都一样，所以在同一个方向上运行的点只有最左边和最右边（最上最下）的是有用的。  
那么就把四个方向上的点都单独拿出来，然后找出最两边的来考虑就行了。

数据范围已经缩小到了 $n=4 \times 2 = 8$ 了，怎么实现呢？  
再次观察运动过程，其实答案在最小的时候肯定是两个点并到一块儿了。考虑两个的相对运动，互相远离的一定不可能让答案变小，而一个变大一个变小的要么最后一个维度减到 $0$，要么一个维度被其它的给约束住，只剩下一个维度的变化，所以肯定是两个点撞在同一水平或竖直线的时候。

那么就变成一道大力分讨题了，讨论所有相撞的时间然后代入验证就可以了。

需要讨论的相撞：

1. 两点在水平方向上相向运动。
2. 两点在竖直方向上相向运动。
3. 一个往上，一个往左。
4. 一个往上，一个往右。
5. 一个往下，一个往左。
6. 一个往下，一个往右。

我开始没有想得很清楚，实现很不精细，调来调去后才过的。代码在[这里](https://atcoder.jp/contests/abc130/submissions/24592222)供参考。

---

## 作者：cyq32ent (赞：0)

关于三分法的题解已经讲的很详细了，这里提供一种常数更小的做法——优选法。

在三分法中，假如我们要计算函数 $f(x)$ 在单峰区间 $[l,r]$ 的峰值，那么就要选定三等分点 $p,q$ 计算 $f(p)$ 和 $f(q)$。假如我们将区间缩小至 $[l,q]$，那么我们计算的 $f(p)$ 的值在接下来的计算中就不会被用到了。反之，如果区间缩小至 $[p,r]$，那么 $f(q)$ 在以后的计算中也不会被用到。如果某个实验点能够重复利用，就会减少计算量。

优选法与三分法类似，但是实验点并不是三等分点。在优选法中，我们选取区间 $[l,r]$ 的黄金分割点 $p=\frac{\sqrt{5}-1}{2}l+\frac{3-\sqrt{5}}{2}r$ 以及 $q=\frac{\sqrt{5}-1}{2}r+\frac{3-\sqrt{5}}{2}l$。假如我们最终选定了区间 $[l,q]$，那么 $p$ 仍然是区间 $[l,q]$ 的黄金分割点，可以继续使用先前计算的 $f(p)$。选定区间 $[p,r]$ 时同理。这样，我们每次遇到一个区间时，只需要计算一次 $f(x)$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long double
#define MX(a,b) a=max(a,b);
#define MN(a,b) a=min(a,b);
signed n,pn=1,qn=1;char d[114514];
int x[114514],y[114514],l=0,r=1e9+7,p,q,C=500,pr,qr;
const int A=0.61803398874989484820458683436564,B=0.38196601125010515179541316563436;
int calc(int t){
	int xmx=-1e18-114514.,ymx=xmx,xmn=1e18+114514.,ymn=xmn;
	for(signed i=1;i<=n;i++){
		int X=x[i],Y=y[i];
		switch (d[i]) {
		case 'R':
			X+=t;
			break;
		case 'L':
			X-=t;
			break;
		case 'U':
			Y+=t;
			break;
		case 'D':
			Y-=t;
			break;
		}
		MX(xmx,X)MX(ymx,Y)MN(xmn,X)MN(ymn,Y)
	}
	return (xmx-xmn)*(ymx-ymn);
}
signed main(){
	cin>>n;
	for(signed i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		while(!isalpha(d[i]=getchar()));
	}
	while(C--){
		p=B*r+A*l;q=A*r+B*l;
		if(pn)pr=calc(p);if(qn)qr=calc(q);
		pn=qn=1;
		if(pr<qr){
			r=q;
			qr=pr;
			qn=0;
		}else{
			l=p;
			pr=qr;
			pn=0;
		}
	}if(pr<0.2)pr=0;printf("%.15Lf",pr);
	return 0;
}
```

---

## 作者：xukehg (赞：0)

简单题。

手模一下样例可以发现 $x_{max} - x_{min}$ 和 $y_{max} - y_{min}$ 都是先增后减的，于是猜测三分。

由于每个点的速度一样，实际上当所有往左的点在往右的点左边时，$x_{max} - x_{min}$ 必然单调递增。如果时间允许负数，当所有往右的点在往左的点右边时，$x_{max} - x_{min}$ 必然单调递减，所以 $x_{max} - x_{min}$ 可三分，同理 $y_{max} - y_{min}$ 可三分。

然后就可以愉快的通过了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const double eps = 0.000000000001;

int n;
struct node{
	int x,y,opt;
}dot[N];
double countt_x[N],countt_y[N];
double dx[4] = {0,0,-1,1},dy[4] = {1,-1,0,0};
double f(double times){
	double maxnx = -3e8,minnx = 3e8,maxny = -3e8,minny = 3e8;
	for (int i = 1;i <= n;i++){
		countt_x[i] = (double)(dot[i].x * 1.0 + times * 1.0 * dx[dot[i].opt]);
		countt_y[i] = (double)(dot[i].y * 1.0 + times * 1.0 * dy[dot[i].opt]);
		if (countt_x[i] - maxnx > eps) maxnx = countt_x[i];
		if (countt_x[i] - minnx < eps) minnx = countt_x[i];
		if (countt_y[i] - maxny > eps) maxny = countt_y[i];
		if (countt_y[i] - minny < eps) minny = countt_y[i];
	}
	return (maxnx - minnx) * (maxny - minny);
}
double find(){
	double l = 0,right = 2000000000.0,mmid,lmid,rmid;
	for (int i = 1;i <= 1000;i++){
		mmid = (right - l) / 3,lmid = l + mmid,rmid = right - mmid;
		if (f(rmid) - f(lmid) >= eps) right = rmid - eps;
		else l = lmid + eps;
	}
	return lmid;
}
signed main(){
	cin >> n;
	char op;
	for (int i = 1,x,y;i <= n;i++){
		cin >> x >> y >> op;
		dot[i].x = x,dot[i].y = y;
		if (op == 'U') dot[i].opt = 0;
		if (op == 'D') dot[i].opt = 1;
		if (op == 'L') dot[i].opt = 2;
		if (op == 'R') dot[i].opt = 3;
	}
	double x = find();
	printf("%0.10f",f(x));
}

---

## 作者：truly_handsome (赞：0)

看到输出是小数时，可以想到模拟退火。但是，由于我菜，模拟退火没调出来，所以就只能想其他办法。

发现 $\Delta x$ 和 $\Delta y$ 是两个一次函数，乘起来就是二次函数，所以可以三分。

如果怕 $T$ 的话，可以先把有用的点处理出来。

```cpp
# include <bits/stdc++.h>
# define pb push_back
# define int long long
# define db long double
using namespace std;

int n, mnx = 1e18, mxx = -1e18, mny = 1e18, mxy = -1e18, arr[15];

db mind(db x, db y){
	return x < y ? x : y;
}

db maxd(db x, db y){
	return x > y ? x : y; 
}

db calc(db x){
	db mnx_ = (db)mnx, mxx_ = (db)mxx, mny_ = (db)mny, mxy_ = (db)mxy;
	if (arr[1] != 1e18) mnx_ = mind(mnx_, (db)arr[1]+x), mxx_ = maxd(mxx_, (db)arr[1]+x);
	if (arr[2] != 1e18) mnx_ = mind(mnx_, (db)arr[2]+x), mxx_ = maxd(mxx_, (db)arr[2]+x);
	if (arr[3] != 1e18) mnx_ = mind(mnx_, (db)arr[3]-x), mxx_ = maxd(mxx_, (db)arr[3]-x);
	if (arr[4] != 1e18) mnx_ = mind(mnx_, (db)arr[4]-x), mxx_ = maxd(mxx_, (db)arr[4]-x);
	if (arr[5] != 1e18) mny_ = mind(mny_, (db)arr[5]+x), mxy_ = maxd(mxy_, (db)arr[5]+x);
	if (arr[6] != 1e18) mny_ = mind(mny_, (db)arr[6]+x), mxy_ = maxd(mxy_, (db)arr[6]+x);
	if (arr[7] != 1e18) mny_ = mind(mny_, (db)arr[7]-x), mxy_ = maxd(mxy_, (db)arr[7]-x);
	if (arr[8] != 1e18) mny_ = mind(mny_, (db)arr[8]-x), mxy_ = maxd(mxy_, (db)arr[8]-x);
	db ret = (mxx_ - mnx_) * (mxy_ - mny_);
	return ret;
}


signed main(){
	for (int i = 0;i < 15;i++) arr[i] = 1e18;
	set <int> s1, s2, s3, s4;
	scanf("%lld", &n);
	for (int i = 1;i <= n;i++){
		int x, y; char d;
		scanf("%lld%lld %c", &x, &y, &d);
		if (d == 'R'){
			mny = min(mny, y);
			mxy = max(mxy, y);
			s1.insert(x);
		}
		else if (d == 'L'){
			mny = min(mny, y);
			mxy = max(mxy, y);
			s2.insert(x);
		}
		else if (d == 'U'){
			mnx = min(mnx, x);
			mxx = max(mxx, x);
			s3.insert(y);
		}
		else{
			mnx = min(mnx, x);
			mxx = max(mxx, x);
			s4.insert(y);
		}
	}
	if (s1.size() > 0){arr[1] = *s1. begin();}
	if (s1.size() > 1){arr[2] = *s1.rbegin();} 
	if (s2.size() > 0){arr[3] = *s2. begin();}
	if (s2.size() > 1){arr[4] = *s2.rbegin();} 
	if (s3.size() > 0){arr[5] = *s3. begin();}
	if (s3.size() > 1){arr[6] = *s3.rbegin();} 
	if (s4.size() > 0){arr[7] = *s4. begin();}
	if (s4.size() > 1){arr[8] = *s4.rbegin();} 
	db l = 0.0, r = 1e18+5;
	for (int i = 1;i <= 500;i++){
		db m1 = (l*2+r) / 3.0;
		db m2 = (l+r*2) / 3.0;
		if (calc(m1) < calc(m2)) r = m2;
		else l = m1;
	}
	printf("%.16Lf", calc(l));
	return 0;
} 

/*
2

*/
```

---

