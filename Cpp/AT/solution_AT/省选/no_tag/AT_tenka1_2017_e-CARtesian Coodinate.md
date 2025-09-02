# CARtesian Coodinate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2017/tasks/tenka1_2017_e

$ xy $ 平面上に直線が $ N $ 本あります。$ i $ 本目の直線は、$ A_ix+B_iy=C_i $ で表される直線です。 これら $ N $ 直線と、$ x $ 軸、$ y $ 軸を合わせた合計 $ N+2 $ 本の直線のうちどの相異なる $ 2 $ 本をとっても、ちょうど $ 1 $ 点で交わります。

全ての $ 1\ \leq\ i\ <\ j\ \leq\ N $ に対し、$ i $ 本目の直線と $ j $ 本目の直線の交点に車を配置します。 $ 3 $ 直線以上が一点で交わる場合も、各直線の組に対して独立に車を配置します。すなわち、$ k $ 本の直線の交点には、 $ k(k-1)/2 $ 台の車が配置されていることになります。

車は全てとても古くなっているため、各車は、$ x $ 軸または $ y $ 軸に平行な方向にのみ動くことができます。

骨董品の車の展覧会を開催したい高橋君は、$ xy $ 平面上に会場を $ 1 $ つ設けることになりました。 車マニアの高橋君は、今にも壊れそうな車たちをなるべく壊さないように、 全ての車を会場に移動するときの移動距離の合計が最も小さくなるような地点に会場を設けることにしました。 もしそのような地点が一意に定まらないなら、上の条件を満たす地点のうち $ x $ 座標の最も小さい地点に、 それでも一意に定まらないなら、上の $ 2 $ 条件に加えて $ y $ 座標も最も小さい地点に高橋君は会場を設けます。

高橋君が会場を設ける地点の座標を求めてください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 4\ ×\ 10^4 $
- $ 1\ ≦\ |A_i|,|B_i|\ ≦\ 10^4(1\ ≦\ i\ ≦\ N) $
- $ 0\ ≦\ |C_i|\ ≦\ 10^4(1\ ≦\ i\ ≦\ N) $
- 与えられるどの $ 2 $ 直線も平行でない
- 入力は全て整数である

### Sample Explanation 1

!\[\](https://img.atcoder.jp/tenka1-2017/650fff486341589a0388efff446acf0a.png) 図の青丸の地点に一台ずつ車が存在します。求める座標は、図の紫丸の地点になります。

## 样例 #1

### 输入

```
3
1 1 1
2 -1 2
-1 2 2```

### 输出

```
1.000000000000000 1.000000000000000```

## 样例 #2

### 输入

```
4
1 1 2
1 -1 0
3 -1 -2
1 -3 4```

### 输出

```
-1.000000000000000 -1.000000000000000```

## 样例 #3

### 输入

```
7
1 7 8
-2 4 9
3 -8 -5
9 2 -14
6 7 5
-8 -9 3
3 8 10```

### 输出

```
-1.722222222222222 1.325000000000000```

# 题解

## 作者：lanos212 (赞：2)

设 $m=\frac{n(n-1)}{2}$。

假设你已知这些交点的坐标分别为 $(x_1,y_1),(x_2,y_2),\cdots,(x_{m},y_{m})$，考虑如何求答案。

你需要求出一个坐标 $(X,Y)$，使得下式尽可能小：

$$\sum_{i=1}^{m}|X-x_i|+|Y-y_i|$$

注意到两个轴的贡献是独立的，这里我们只考虑 $Y$ 的最优取值求法，$X$ 只需要将所有直线 $A_i,B_i$ 交换再求一遍即可。

现在我们要让这个式子尽可能小：

$$\sum_{i=1}^{m} |Y-y_i|$$

结论是将 $y$ 从小到大排序，那么 $Y\in [y_{\lfloor\frac{m+1}{2}\rfloor},y_{\lfloor\frac{m}{2}\rfloor+1}]$。

证明考虑放到数轴上，$Y$ 在这个区间内移动，对于所有点的距离之和不变，而往区间外移动，距离之和一定变大。

由于题目要求输出最小的 $Y$，那么就是 $y_{\lfloor\frac{m+1}{2}\rfloor}$ 的值。

---

设 $k=\frac{m+1}{2}$。

现在要求所有交点 $y$ 坐标中，第 $k$ 小的值为多少。

考虑二分，那么问题转化为判断 $y=mid$ 这条直线下方的交点数是否 $\ge k$。

把 $y=mid$ 画出来看看！

![AT_tenka1_2017_e.png](https://s2.loli.net/2024/12/12/goLaiKhlXI2ZE34.png)

考虑两条直线，浅色直线与 $y=mid$ 的交点靠左。

那么我们可以发现，当图中夹角满足 $\alpha > \beta$ 时，这两条直线交点在 $y=mid$ 下方，否则在上方。

那么两条直线相交在下方的条件是一个逆序对的形式，直接用树状数组数逆序对个数即可。

外层有二分，时间复杂度 $O(n \log n (\log |V|+|\log \epsilon|))$。

由于这题数据范围满足直线两两有交，且不与坐标轴平行，不存在任何实现细节。

两条直线与 $y=mid$ 交点相同也是不用考虑的，因为外层有二分，这只会让答案出现极小范围的偏差，在精度范围内是允许的。

code


```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;

const double PI=acos(-1);
int n;
int A[100001],B[100001],C[100001],rk[100001];
double tmp[100001];
pair<double,int> tmp_sort[100001];

struct BIT{
	int s[100001];
	inline void upd(int x,int z){while (x<=n) s[x]+=z,x+=x&-x;}
	inline int query(int x){int sum=0; while (x) sum+=s[x],x-=x&-x; return sum;}
}cat;

inline double solve(){
	
	for (int i=1;i<=n;++i){
		tmp[i]=atan2(-(double)A[i]/B[i],1);
		if (tmp[i]<0) tmp[i]+=PI;
		tmp_sort[i]={tmp[i],i};
	}
	
	sort(tmp_sort+1,tmp_sort+n+1);
	for (int i=1;i<=n;++i) rk[tmp_sort[i].second]=i;
	
	double lt=-1e9,rt=1e9;
	while ((rt-lt)>1e-10){
		double mid=(lt+rt)*0.5;
		for (int i=1;i<=n;++i) tmp_sort[i]={(C[i]-B[i]*mid)/A[i],i};
		sort(tmp_sort+1,tmp_sort+n+1);
		int cnt=0;
		for (int i=1;i<=n;++i) cat.s[i]=0;
		for (int i=1;i<=n;++i) cnt+=cat.query(rk[tmp_sort[i].second]),cat.upd(rk[tmp_sort[i].second],1);
		int k=n*(n-1)/4+1;
		if (cnt>=k) lt=mid;
		else rt=mid;
	}
	return lt;
	
}

signed main(){
	std::ios::sync_with_stdio(false),cin.tie(0);
	
	cin>>n;
	for (int i=1;i<=n;++i) cin>>A[i]>>B[i]>>C[i];
	
	for (int i=1;i<=n;++i) swap(A[i],B[i]);
	cout<<fixed<<setprecision(14)<<solve()<<' ';
	for (int i=1;i<=n;++i) swap(A[i],B[i]);
	cout<<fixed<<setprecision(14)<<solve()<<'\n';
	
	return 0;
}
```

---

