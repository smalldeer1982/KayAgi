# [ABC389D] Squares in Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc389/tasks/abc389_d

在二维坐标平面上，无限铺满了 $ 1 \times 1 $ 的正方形。

若以某个正方形的中心为圆心绘制一个半径为 $ R $ 的圆，则完全被该圆包含的正方形有多少个？

更严格地说，请统计满足以下条件的整数对 $(i, j)$ 的个数：四个点 $(i+0.5, j+0.5)$、$(i+0.5, j-0.5)$、$(i-0.5, j+0.5)$、$(i-0.5, j-0.5)$ 到原点的距离均不超过 $ R $。

## 说明/提示

### 约束条件

- $ 1 \leq R \leq 10^{6} $
- 输入数值均为整数

### 样例解释 1

以圆心与正方形中心重合的正方形及其相邻的 4 个正方形共计 5 个正方形完全被圆包含。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2```

### 输出

```
5```

## 样例 #2

### 输入

```
4```

### 输出

```
37```

## 样例 #3

### 输入

```
26```

### 输出

```
2025```

# 题解

## 作者：Hughpig (赞：10)

考虑 $R=2$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/8a0jmkuv.png)

发现中心的横坐标为 $1$ 的正方形，两条垂直于 $y$ 轴的边分别为直线 $x=\dfrac{1}{2}$ 和直线 $x=\dfrac{3}{2}$。

考虑更靠右的边，直线 $x=\dfrac{3}{2}$。在 $x$ 轴及上方放一个正方形，最高点的纵坐标为 $1-0.5=0.5$（第一个正方形有一半在 $x$ 轴下方)，放两个正方形最高点纵坐标为 $2-0.5=1.5$。以此类推，放 $n$ 个正方形最高点纵坐标为 $n-0.5$。

在圆上 $x=\dfrac{3}{2}$ 时，$0.5<y=\sqrt{2^2-(\dfrac{3}{2})^2}=\dfrac{\sqrt{7}}{2}<1.5$。

所以中心横坐标为 $1$ 的正方形在 $x$ 轴及 $x$ 轴上方能最多放 $1$ 个，在 $x$ 轴及 $x$ 轴下方也能最多放 $1$ 个。还有个重合的在 $x$ 轴上的情况，所以要减去 $1$ 个。

因此中心的横坐标为 $1$ 的正方形在 $R=2$ 的圆最多能放 $1$ 个。中心的横坐标为 $-1$ 的正方形同理。

推广开来，中心的横坐标为 $p\ (p\ge 0)$ 的正方形最多可以放 $2\times\lfloor\sqrt{R^2-(p+0.5)^2}+0.5\rfloor-1$ 个。$p<0$ 的正方形可以同理取更靠左的边计算。

然后枚举并计算即可，注意中心为 $0$ 的正方形不要算 $2$ 次。

代码：

```cpp
/*
*Author: Hughpig
*made in China
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll r,ans;

int main()
{
	cin>>r;
	for(int i=-r;i<r;++i){
		if(i==0)continue;
		double x=i+0.5;
		double y=r*r-x*x;
		y=sqrtl(y)+0.5;
		ans+=2*(floor(y))-1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ny_Dacong (赞：6)

# 思路

听说可以用数学 $O(1)$ 做，不知道是不是真的。不过作为数学蒟蒻，这里贡献一篇用二分 $O(R \log R)$ 的做法。

首先发现 $R \le 10^6$，因此想到二分。如果我们确定了 $x$ 坐标，那么我们可以二分 $y$ 坐标，看看 $x$ 坐标处最高的且处于圆内的方格的 $y$ 坐标是多少。比它低的方格一定在圆内，比它高的方格一定在圆外。所以对于 $x$ 这一列有多少个合法的方格就出来了。

实现的时候暴力枚举 $x$，发现圆上下对称，所以先计算上半轴，然后翻过来即可得出下半轴。

注意边界情况。处于 $x$ 轴上的方格（也就是 $y$ 坐标等于 $0$ 的方格）会在翻过来的时候计算两次，注意要减去重复贡献。

还有如果这一列没有方格在圆内，需要特判。

# AC 代码

一遍过，嘻嘻。

```cpp
#include<bits/stdc++.h>
using namespace std;
double n;
double dx[] = {0.5,0.5,-0.5,-0.5};
double dy[] = {-0.5,0.5,-0.5,0.5};
long long ans = 0;
double getdis(double x,double y){
	double res = -114;
	double tpa,tpb;
	for(long long i = 0; i <= 3; i++){
		tpa = x+dx[i],tpb = y+dy[i];
		res = max(res,sqrt(tpa*tpa+tpb*tpb));
	}
	return res;
}
long long erfen(long long x){
	long long l = 0,r = n,mid,res = -1;
	double tp;
	while(l <= r){
		mid = l+((r-l)>>1);
		tp = getdis(x,mid);
		if(tp <= n){
			res = mid;
			l = mid+1;
		}else{
			r = mid-1;
		}
	}
	return res;
}
int main(){
	scanf("%lf",&n);
	for(long long i = -n; i <= n; i++){
		static long long j;
		j = erfen(i);
		if(j == -1){
			continue;
		}
		ans += (j+1)*2-1;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Zilljy258 (赞：5)

[[ABC389D] Squares in Circle](https://www.luogu.com.cn/problem/AT_abc389_d)

感觉这个题介于黄题和橙题之间。

### 思路：

![](https://cdn.luogu.com.cn/upload/image_hosting/h4g95z9b.png)

首先，十字架上的正方形很好数，一边有 $R-1$ 个，共有四条边。（图中红色的部分）

然后我们可以递推剩余的蓝色部分。

设一个 $r$，初始值 $r=R-1$。

例如从圆心沿着红色向右走，每次判断当前位置向上 $r$ 个位置的正方形是否被包含在圆内。若果不行 $r \larr (r-1)$，如果可以就统计答案，然后继续向右走一步。

最后别忘加上圆心！

由于 $r$ 从 $R$ 逐渐减少为 $0$，因此时间复杂度为 $O(R)$。

---

## 作者：TainityAnle (赞：3)

### 题意

有一个无限的由 $1\times 1$ 网格构成的平面。现在要在一个格的中心（可以当成在 $(0.5,0.5)$ ）画一个半径为 $r$ 的圆，问有多少个格被完全包含在圆里。

### 思路

数学题，需要推一个式子。

对于一个圆，我们可以给它分成两个部分，蓝色的和橙色的。

![](https://cdn.luogu.com.cn/upload/image_hosting/77a9sykl.png)

因为 $(0.5,0.5)$ 的确很难看，所以我们把蓝色的正方形看作坐标轴，右上角的定为第一象限，以此类推。

根据对称性容易发现四个象限的数量一定是相同的，单独处理一个象限即可。

枚举每一个格，计算出枚举的格数应该是 $\lfloor r-0.5\rfloor$。每一个列上合法的格数的计算方式：根据不等式 $ (i + 0.5)^2 + (j + 0.5)^2 \leq r^2 $，解得 $ i \leq \sqrt{r^2 - (j + 0.5)^2} - 0.5 $。其中 $j$ 表示现在枚举到第 $j$ 列，$i$ 是第 $j$ 列上的格数。这样就可以 $O(r)$ 算出一个象限上的格数。再乘 $4$ 就是橙色点的个数。

坐标轴的长度计算可得是 $\lfloor \sqrt{r^2-0.25}-0.5\rfloor$。将这个值乘 $4$，再加上中心的 $1$，就是最终的答案。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int calc(int j, int R) {
    return floor(sqrt(R-pow(j+0.5,2))-0.5);
}
int r,R,cnt=0,m,ans;
signed main(){
    cin>>r,R=r*r,m=floor(r-0.5);
    for(int j=1; j<=m; j++) {
        int cur=calc(j,R);
        if(cur>=1) cnt+=cur;
    }
    int tmp=floor(sqrt(R-0.25)-0.5);
    ans=4*cnt+4*tmp+1;
    cout<<ans;
    return 0;
}
```

---

## 作者：songge888 (赞：3)

数学题。

### 题意

给你一个铺满单位长度为 $1$ 的平面，给你一个圆的半径 $r$，求以一个正方形的中心为圆心，以 $r$ 为半径的圆，最多可以包含几个完整的正方形。

### 思路

假设有这样一个图：
![QQ20250119-081733.png](https://s2.loli.net/2025/01/19/cDNp6SjqTyLKx8d.png)

如果以 $B$ 点为圆心，半径是 $4$ 的话，图就长这样：

![QQ5119-081733.png](https://s2.loli.net/2025/01/19/CFy9DsIhb6LgQZJ.png)

可以发现，中间有个十字的部分是一定会被包含的。

![444.png](https://s2.loli.net/2025/01/19/sC3SgWw5rKZeUqY.png)

记答案为 $ans$，不妨先把 $ans$ 加上 $4\times (r-1)+1$。

然后发现剩下可以分成完全相同的四部分，我们已左下角的来举例：

第一层 `for` 循环，表示横着是第 $i$ 排。

第二层 `for` 循环，表示竖着是第 $j$ 排。

![445.png](https://s2.loli.net/2025/01/19/JEL9RqSyZlu5k3Y.png)

想这样，发现复杂度是 $O(r^2)$ 的，会超时，考虑优化。

发现随着 $i$ 增大，$j$ 是单调递减的。

所以可以记录一个 $pos$ 每次减一下，就不用每次都重新算了。

每次判断 $(pos+0.5)^2+(i+0.5)^2$ 和 $r^2$ 的大小就可以了。

时间复杂度 $O(r)$。

### Code

```c++
#include<bits/stdc++.h>
#define int long long
#define bug cout<<"___songge888___"<<'\n';
using namespace std;
int r;
int ans=1;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>r;
	ans+=4*(r-1);
	int pos=r-1;
	int ans1=0;
	for(int i=1;i<r;i++){
		while((pos*1.0+0.5)*(pos*1.0+0.5)+(i*1.0+0.5)*(i*1.0+0.5)>r*r&&pos>0){
			pos--;
			
		}
		ans1+=pos;
	}
	ans+=4*ans1;
	cout<<ans;
	return 0;
}
```

---

## 作者：hjyowl (赞：3)

### 思路

首先，这个圆的四个象限的答案一定是堆成的。

也就是我们只需要计算第一象限然后对答案乘上 $4$ 加一。

然后，我们只需要来对于一个固定的 $x$ 坐标，去二分 $y$，单调性显然，也就是越靠后的越可能属于这个圆。

然后我们只需要用二分做，把答案加起来，乘上 $4$ 加一就行了。

至于判断函数，直接正常判断即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long R;
bool checker(long long x,long long y){
	double d1 = sqrt((x + 0.5) * (x + 0.5) + (y + 0.5) * (y + 0.5));
	double d2 = sqrt((x + 0.5) * (x + 0.5) + (y - 0.5) * (y - 0.5));
	double d3 = sqrt((x - 0.5) * (x - 0.5) + (y + 0.5) * (y + 0.5));
	double d4 = sqrt((x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5));
	if (d1 <= R && d2 <= R && d3 <= R && d4 <= R){
		return 1;
	}
	return 0;
}
int main(){
	cin >> R;
	long long res = 0;
	for (long long i = -R; i <= 0; i ++ ){
		long long l = -R,r = 0;
		while (l < r){
			long long mid = l + r >> 1;
			if (checker(i,mid)){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		res += (0 - l);
	}
	cout << res * 4 + 1;
	return 0;
}
```

---

## 作者：lam_dyr (赞：2)

## 题意
题目要求我们计算在二维平面上，以原点为圆心，半径为 $R$ 的圆内，完全包含的正方形数量。这些正方形的边长为 $1$，中心点坐标为整数 $(i,j)$。

## Solution
由于正方形中心坐标为 $(i, j)$，则正方形的四个顶点坐标为 $(i \pm 0.5, j \pm 0.5)$。

要使正方形完全包含在半径为 $R$ 的圆内，需要满足 $\sqrt{(i \pm 0.5)^2 + (j \pm 0.5)^2} \le R$。等式两边同时平方，得 $(i + 0.5)^2 + (j + 0.5)^2 \le R^2$。

为了避免浮点数损失精度，我们还可以再进行简化，将不等式两边乘以 $4$，得到 $(2i + 1)^2 + (2j + 1)^2 \le 4R^2$。

同时，由于圆的对称性，我们只需要计算第一象限内的正方形数量，然后乘以 $4$ 即可。

设 $maxj$ 为 $j$ 的最大值，分类讨论如下：
- 当 $i=0$ 时，表示在 $y$ 轴上的正方形，此时 $j$ 的取值范围是 $0$ 到 $maxj$，总共有 $2\times maxj+1$ 个正方形（包括中心点）。
-  当 $i>0$ 时，表示不在 $y$ 轴上的正方形，此时 $j$ 的取值范围也是 $0$ 到 $maxj$，由于对称性，总共有 $4\times maxj+2$ 个正方形。

至此，问题转化成了一个可以直接计算的代数问题。时间复杂度 $O(R)$。

具体细节见代码。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll solve(ll R){
	ll ans=0;
	ll r=4*R*R;//4*R^2
	ll maxx=floor(R-0.5);
	for(ll i=0;i<=maxx;++i){
		ll cur=(2*i+1)*(2*i+1);//(2i+1)^2
		ll rem=r-cur;//剩下可以用于j的平方和。
		if(rem<0) continue;
		ll maxj=floor((sqrt((double)rem)-1.0)/2.0);//计算j的最大值 
		if(maxj<0) continue;
		//分类讨论
		if(i==0) ans+=(maxj>0)?2*maxj+1:1;
		else ans+=(maxj>0)?4*maxj+2:2;
	}
	return ans;
}
int main(){
	ll R;
	cin>>R;
	cout<<solve(R);
	return 0;
}
```

---

## 作者：dg114514 (赞：2)

提供一种投机取巧的方法。\
首先，我们看到输入只有一个 $n$，大胆猜是一个数列。\
所以我们暴力 $O(n^2)$ 求出前 $10$ 项，直接输进 [oeis.org](oeis.org)，发现是 [A373193](https://oeis.org/A373193)，然后根据公式 `a(n) = 4*Sum_{k=1..n-1} floor(sqrt(n^2 - (k+1/2)^2) - 1/2) + 4*n - 3` 直接算即可。\
代码就不放了。

---

## 作者：XCDRF_ (赞：1)

# AT_abc389_d \[ABC389D] Squares in Circle

[原题传送门](https://atcoder.jp/contests/abc389/tasks/abc389_d)

[更好的阅读体验](https://www.luogu.com.cn/article/3w6pkuiv)

## 题目大意

求出整数对 $(x,y)$ 的数量，使得所有四个点 $(x+0.5,y+0.5)$ 、 $(x+0.5,y-0.5)$ 、 $(x-0.5,y+0.5)$ 和 $(x-0.5,y-0.5)$ 距离原点的距离最多为 $R$ 。

## 解题思路

看到这个题，首先想到暴力枚举每个点，看看是否在半径为 $R$ 的圆内。时间复杂度 $O(n^2)$。

当然这个算法不符合要求，不妨先用它打表找一下规律：

|$1$|$2$|$3$|$4$|$5$|$6$|$7$|$8$|$9$|$10$|$\dots$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$1$|$5$|$21$|$37$|$61$|$89$|$129$|$177$|$221$|$277$|$\dots$|

这是啥啊，差值没有规律，差值的差值没有规律，差值的差值的差值也没有规律……

既然找规律行不通，那不妨从圆本身出发。

我们都知道，圆可以写成一个表达式 $x^2+y^2=r^2$，现在半径知道了，那么只需要枚举 $x$，$y$ 的范围不就有了吗？

因为整个圆是对称的，所以只需要算第一象限（包括 $x$ 轴和 $y$ 轴）内的点，就能推广到整个圆中，这样时间复杂度为 $O(n)$。

注：本题正方形的边界都是小数，注意一下范围。

## 参考代码

```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
int n,ans;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
    	int cnt=sqrt(n*n-(i+0.5)*(i+0.5))-0.5;
    	cnt*=2;
    	cnt++;
    	if(i==0) ans+=cnt;
    	else ans+=cnt*2;
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc389/submissions/61831081)

---

## 作者：jimmy0926 (赞：1)

## 题解：AT_abc389_d [ABC389D] Squares in Circle

### Upd
- 2025/3/23 更正代码注释。

### 解题思路
题目没有给出较明确的算法，先根据数据范围来猜算法。

观察到 $R\le 10^6$，可以满足 $\Theta(R \log R)$ 不超时。

我们发现上下是对称的，同时左右也是对称的，可以只考虑左上部。

$\log R$ 可以想到二分。  
我们可以通过二分来确定左上的格子个数。

设现在在第 $i$ 行（格子正中间的坐标，从上至下对应从 $R$ 到 $1$），二分左界 $l = 0.5$，右界 $r = R + 0.5$，中值 $mid = \frac{l+r}{2}$，若 $(i - 0.5, mid)$ 到原点的距离 $ \le R$，则令 $l = mid$，否则令 $r = mid$。  
最后取 $\lfloor \frac{l + r}{2}-0.5 \rfloor \times 2 + 1$ 为第 $i$ 行的个数，累加一下就好了 qwq。

### 代码实现
```cpp
#include <bits/stdc++.h>
int R;
unsigned long long ans;
double l, r;

inline double dist(double x, double y) {
	return sqrt(x * x + y * y);
}

int main() {
	scanf("%d", &R);
	for (int i = R; i > 0; --i) {
		l = 0.5, r = R + 0.5;
		for (int j = 1; j <= 100; ++j) {    //while (r - l > eps) {
			double mid = (l + r) / 2.0;
			if (dist(i - 0.5, mid) <= R)
				l = mid;
			else
				r = mid;
		}
		ans += (int)((l + r) / 2.0 - 0.5) * 2 + 1;
	}
	printf("%llu\n", ans * 2 - (R * 2 - 1));
	return 0;
}
```
Tips：记得开 ```long long```。

完结撒花~

---

## 作者：Yuexingfei_qwq (赞：1)

赛时极限AC。
## 思路  
找规律题，但是公式比较难想~~毕竟用了我一个多小时~~。  

通过观察可以发现每次包含在圆内的正方形增加的都是在原来图形的基础上再在外面大概地围一圈。  
于是可以将第一象限的方块完整在圆内、$\frac{1}{2}$ 在圆内和 $\frac{1}{4}$ 在圆内的面积加起来，乘以 $4$ 得到四个象限的答案，最后加上中间四条轴后减去 $3$，就是答案。  

**公式**：记输入为 $R$ 时的答案为 $ans_{R}$，则
$$
ans_{R} = \sum_{i = 1}^{R - 1} \lfloor \sqrt{R^2 - (i + 0.5)^2} - 0.5 \rfloor \times 4 + R \times 4 - 3
$$
## AC CODE
赛时代码。
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int r;

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> r;
	int s = 0;
	F(i, 1, r - 1, 1) {
		double x = std::sqrt(r * r - (i + 0.5) * (i + 0.5)) - 0.5;
		s += (int)(std::floor(x));
	}
	cout << 4 * s + 4 * r - 3 << el;
	r0;
}
```

[AC记录](https://atcoder.jp/contests/abc389/submissions/61832597)

---
完结~~不~~散花。

---

## 作者：zaolong (赞：1)

## 思路

给大家分享一种 $O(n)$ 的做法。我们把圆心看作坐标为 $(0,0)$ 的点然后从圆心沿着横坐标不断扩展，在依次用勾股定理求出纵坐标上的正方形个数。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int r,ans; 
main(){
	cin>>r;
	//沿着横坐标扩展。 
	for(int i=0;i<=r;i++){
		int x,s;
		x=(i+0.5)*(i+0.5);
		//如果再扩展超过了圆就退出。 
		if(x>r*r) break;
		//逆向勾股定理：已知斜边(r)和短边(i)求长边。 
		s=floor(sqrt(r*r-x)-0.5);
		//我们要四个方向都算上 
		ans+=4*s;
	}
	//还有圆心的一个 
	cout<<ans+1;
} 
```

---

## 作者：small_lemon_qwq (赞：1)

枚举题意中 $(i,j)$ 的每个 $i$ 有多少个对应的 $j$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int r,ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>r;
	for(int i=0;i<r;i++){
		ans+=((int)(sqrt(r*r-(i+0.5)*(i+0.5))-0.5)*2)+1;
	}
	for(int i=-r+1;i<0;i++){
		ans+=((int)(sqrt(r*r-(i-0.5)*(i-0.5))-0.5)*2)+1;
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：zzwdsj (赞：1)

### 题目大意
从原点画一个半径为 $r$ 的圆，求有几个整数点在圆内。整数点 $(i,j)$ 在圆内的条件是 $(i+0.5,j+0.5),(i+0.5,j-0.5),(i-0.5,j+0.5),(i-0.5,j-0.5)$ 这四个点距离原点的距离均不大于 $r$。
### 思路
由于四个象限在圆内的点数都是相同的，我们这考虑第一象限。枚举 $y$ 坐标，二分得出这个 $y$ 坐标对应的点 $x,y$ 最远在哪。那么 $0,y$ 到 $x,y$ 全部在圆内，共 $x+1$ 个点。设第一象限在圆内的点数为 $a$。则答案为 $(a-r)\times 4+1$。复杂度 $O(n\log n)$
### code
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
using namespace std;
#define int long long
double dis(double x,double y){return sqrt((x+0.5)*(x+0.5)+(y+0.5)*(y+0.5));}
int n,ans;
int hs(int i,int l,int r)
{
	if(l+1==r)return l;
	int mid=(l+r)/2;
	if(dis(i,mid)<=n)return hs(i,mid,r);//(mid,i) 在圆内
	else return hs(i,l,mid);//(mid,i) 在圆外
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++)ans+=hs(i,0,n)+1;
	cout<<(ans-n)*4+1;
	return 0;
}
```

---

## 作者：lilong (赞：0)

考场上读成数所有正方形的个数了，过了好久才发现是简单题。

考虑除了圆心所在行和列以外的格子分布状况。由圆的对称性可知，只需求出 $\frac{1}{4}$ 个圆的格子个数即可。不难发现当横坐标确定时，最大的纵坐标也是确定的。于是可以直接枚举横坐标，并二分确定最大的纵坐标，即可获得该行的格子数量。将每行的结果累加并乘 $4$，再算上与圆心同行或同列的格子即为答案。

时间复杂度 $O(R\log R)$，具体细节见代码。


```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

double R;
int l,r,mid,ans,p;

double dis( double x1 , double y1 , double x2 , double y2 )
{
	return ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 );
}

signed main()
{
	cin >> R;
	for( int i = 1 ; i <= R ; i ++ )
	{
		l = 1,r = R,p = -1;
		while( l <= r )
		{
			mid = ( l + r ) / 2;
			if( dis( i + 1 , mid + 1 , 0.5 , 0.5 ) > R * R ) r = mid - 1;
			else l = mid + 1,p = mid;//cout << dis( double( i + 0.5 ) , double( mid + 0.5 ) , 0.5 , 0.5 ) << '\n';
		}
		if( p == -1 )
			continue;
		ans += p * 4;
	}
	ans += ( R - 1 ) * 4 + 1;
	cout << ans;
	return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## [[ABC389D] Squares in Circle](https://atcoder.jp/contests/abc389/tasks/abc389_d)

## 思路

发现 $n$ 比较小，考虑枚举每一行并二分求该行的方块数。

因为原点往上的方块数与原点往下的方块数是相等的，所以只需要枚举向上或向下的方块数，将方块数乘 $2$ 减去中间多算的方块数即可。

设原点为 $(-0.5,-0.5)$，每次二分该行最右边方块的右上角（该点为这行距离原点最远的点之一）的 $x$ 坐标，则该点到原点的距离为 $\sqrt{(x+0.5)^2+(y+0.5)^2}$，通过二分求出坐标后，这行的方块数即为 $(2\times x-1)$。



## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,tot;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=0;i<n;i++){
		int l=0,r=n-1,mid,res=-1;
		while(l<=r){
			mid=(l+r)/2;
			if(sqrt((mid+0.5)*(mid+0.5)+(i+0.5)*(i+0.5))>n)
				r=mid-1;
			else
				l=mid+1,res=mid;
		}
		tot+=res*2+1;
	}
	cout<<tot*2-2*n+1;
	return 0; 
}
```

---

## 作者：long_long__int (赞：0)

# 题目翻译：

在二维坐标平面上，有一个由 $1 \times 1$ 个正方形组成的无限平面。

考虑以其中一个正方形的中心为圆心，画一个半径为 $R$ 的圆。有多少个正方形完全包含在圆内？

更精确地说，求使所有四个点 $(i+0.5,j+0.5)$ 、 $(i+0.5,j-0.5)$ 、 $(i-0.5,j+0.5)$ 和 $(i-0.5,j-0.5)$ 与原点的距离最多为 $R$ 的整数对 $(i,j)$ 的个数。

# 题目解法

可以把圆切成 $4$ 块。只需计算一块即可。（切法见图片，沿粗线切）

![](https://cdn.luogu.com.cn/upload/image_hosting/wc4hab6i.png)

对于每个大于 $0$ 的 $x$，二分最大的 $y$，累加所有的 $y+1$，再乘四，加一（中间的），就是答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/odvscm8d.png)

没看懂的看图，红色的点为二分后最大的 $y$，分别是 $3,2,1$，则一共有 $(3+1)+(2+1)+(1+1)=9$ 个点满足条件。这个图只是圆的 $\frac{1}{4}$，所以还要乘 $4$，加上中间的点。

时间复杂度 $O(R \log R)$。

还没看懂的看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int R;
long long t;
bool check(long long x,long long y){//距离是否小于等于 R
	return x*x+y*y+x+y+0.5<=t;
//上面的等价于 return sqrt(pow(x+0.5,2)+pow(y+0.5,2))<=R^2;
}
long long bis(int x){//二分每个 x
	long long l=0,r=R+1;
	if(!check(x,l)) return 0;
	long long ans=0;
	while(l<=r){
		long long mid=l+((r-l)>>1);
		if(check(x,mid)){
			l=mid+1;
			ans=mid+1;
		}else{
			r=mid-1;
		}
	}
	return ans;
}
signed main(){
	cin>>R;
	t=R*R;
	long long ans=0;
	for(long long x=1;x<=R+1;x++){//枚举 x
		ans+=bis(x);
	}
	printf("%lld\n",ans*4+1);
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

题意：在平面直角坐标系中，平铺满了边长为 $1 \times 1$ 的正方形，边与坐标轴平行，中心的一个正方形的中心为 
$(0,0)$，原点有一个半径为$R$ 的圆，问能完全覆盖的正方形个数。       
**注意是在正方形的中间。这为画图带来了不少难度。**    

![](https://cdn.luogu.com.cn/upload/image_hosting/kj5xagzu.png)     

赛时画的图。不难看出一个圆包括的正方形共有 $2 \times R-1$ 行，每一行的个数是不同的。        
那么我们尝试求出每一行有多少个。    
考虑最右边的一个正方形顶点。连接圆心、最边上一个相切点，并作水平线和铅垂线，构造直角三角形（如图中红色和黄色部分）。它的斜边为半径长，铅垂直角边的长度也是知道的（数格子可知，与当前是第几层有关）。根据勾股定理可以求出另一条直角边，就可以得到包括的完整的最远正方形的位置，继而得到这一层正方形个数。     
举个例子，最上方竖起来的红色三角形，位于第一排（圆半径为 $6$），铅垂直角边长度为 $0.5+(6-1)=5.5$，斜边长度为 $6$，水平直角边长度为 $\sqrt {6^2-5.5 ^2} \le 2.4$。
![](https://cdn.luogu.com.cn/upload/image_hosting/l0grxpy6.png)
如图，$AB \le 2.4$。     
由于铅垂线把正方形切成了两半，所以 $AC=0.5$，即 $BC \le 1.9 \le 2$。     
所以 $AB$ 中间有一个完整的正方形。对称得到两边共有两个正方形，加上点 $A$ 所在的那个被劈成两半的，共有 $3$ 个正方形。     
把每一行求出的数据求和就是答案。    
```cpp
// LUOGU_RID: 199108977
#include<bits/stdc++.h>
using namespace std;
int n;long long ans;
int main()
{
	scanf("%d",&n);
	if(n==1) return printf("1"),0;
	if(n==2) return printf("5"),0;
	for(int i=1;i<n;i++)
	{
		double c=n,a=n-i+0.5;
		double b=sqrt(c*c-a*a);
		ans+=1+floor(b-0.5)*2;
	}ans+=2*n-1;
	for(int i=n+1;i<=2*n-1;i++)
	{
		double c=n,a=i-n+0.5;
		double b=sqrt(c*c-a*a);
		ans+=1+floor(b-0.5)*2;
	}printf("%lld",ans);
}
```

---

## 作者：PDAFX (赞：0)

## 题目大意

在一个直角坐标系上，分布着一个个边长为 $1$ 的正方形，
以一个正方形的中心为圆心，画一个边长为 $R$ 的圆，问可以覆盖多少个正方形。
更加准确的说：
求 $(i,j)$，四个点 $(i+0.5,j+0.5)$、$(i+0.5,j-0.5)$、$(i-0.5,j+0.5)$ 和 $(i-0.5,j-0.5)$ 都满足它们与原点的距离不超过 $R$ 的个数。

## 思路

我们可以将正方形按照题目意思转化为点，然后根据勾股定理，求得点的个数 $\lfloor\sqrt{r^2-(i-0.5)^2}\rfloor$, 因为圆心位于正方形中间，所以要在 $i$ 的基础上减去 $0.5$。

但这里只处理了圆的一部分，但因为圆是对称的，所以将结果 $\times 4$, 但因为中间还有一块格子，所以 $+1$ 即可。

时间复杂度 $O(n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long sum;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		long long x=max((int)(sqrt(n*n-(i-0.5)*(i-0.5))-0.5),0);
		sum+=x;
	//	cout<<sum<<endl;
	}
	cout<<sum*4+1;
}
```

---

## 作者：_xxxxx_ (赞：0)

找规律比较难吧，考虑 $O(r)$ 的做法。

我们把它先补成一个边长为 $r+r-1$ 的正方形，再去减掉四个角。

因为四个角缺的地方都相同，考虑统计左上的个数。

一个正方形只有在或不在，考虑二分，找到最后一个左上端点，计算答案。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
inline int read()
{
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-'){ w = -1;} ch = getchar();}
	while(ch >= '0' && ch <= '9') s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
	return s * w;
}
int R;
signed main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> R;
	int ans = 0;
	for(int i = R - 1; i; i--)//纵 
	{
		int l = 0, r = R - 1;
		int pos = 0;//横 
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			long double dis = (mid + 0.5) * 1.0 * ((mid + 0.5) * 1.0) + (i + 0.5) * 1.0 * ((i + 0.5) * 1.0);
			//两点距离 
			if(dis <= R * R) pos = mid, l = mid + 1;
			else r = mid - 1;
		}
//		cout << pos << endl;
		ans += (R - pos - 1);
	}
	cout << (R + R - 1) * (R + R - 1) - 4 * ans << endl;
	return 0;
}
```

---

## 作者：xk2013 (赞：0)

题目传送门：[AT_abc389_d [ABC389D] Squares in Circle](/problem/AT_abc389_d)

## 前置知识
- 二分答案；
- 距离计算。

## 题意简述
本题要求我们求出半径为 $r$ 的圆内完整地包含了几个中心在整数点上的边长为 $1$ 的正方形。

## 解题思路
考虑二分。我们枚举坐标的 $x$，二分最大的 $y$，这样我们就能通过 $y$ 的位置计算 $x$ 行对答案的贡献了。

由于 $\operatorname{check}$ 函数的时间复杂度为 $O(1)$，所以总时间复杂度为 $O(r \times \log_2r \times 1) = O(r \log_2 r)$，$r \le 10^6$ 的情况下不会超时。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
#include <cstdio>

typedef long long int ll;
ll r, ans;
bool check(ll x, ll y);

int main(void)
{
	scanf("%lld", &r);
	
	for (int x = -r + 1; x <= r - 1; x++) // 枚举 x
	{
		ll l = -r + 1, rr = r - 1, mid = -1;
		
		while (l < rr) // 二分 y
		{
			mid = (l + rr + 1) >> 1;
			
			if (check(x, mid))
			{
				l = mid;
			}
			else
			{
				rr = mid - 1;
			}
		}
		
		ans += l * 2 + 1; // 统计答案
	}
	
	printf("%lld", ans);
	return 0;
}

bool check(ll x, ll y)
{
	return (x + 0.5) * (x + 0.5) + (y + 0.5) * (y + 0.5) <= r * r && (x + 0.5) * (x + 0.5) + (y - 0.5) * (y - 0.5) <= r * r && (x - 0.5) * (x - 0.5) + (y + 0.5) * (y + 0.5) <= r * r && (x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5) <= r * r; // 判断四个角是否都在圆内
}
// 最后两分钟极限过 D！
```
----------------------
这是本五年级蒟蒻小学生的第 25 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2025/01/19：初版。

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

在平面直角坐标系中给定 $R$，求出点 $(x,y)$ 满足 $(x+0.5,y+0.5),(x+0.5,y-0.5),(x-0.5,y+0.5),(x-0.5,y-0.5)$ 到 $(0,0)$ 的距离均不超过 $R$ 的数量，数据范围 $R\le 10^6$。

## 解题思路

因为 $R$ 很小，考虑使用 $O(R)$ 的复杂度枚举每一个 $x\in(-R,R)$，然后用 $O(1)$ 的时间统计满足条件的 $y$ 的数量。考虑推公式，对于点 $(x+0.5,y+0.5)$ 来说，根据题意它满足 $\sqrt{(x+0.5)^2+(y+0.5)^2}\le R$，可解得 $y\le\left\lfloor\sqrt{R^2-(X+0.5)^2}-0.5\right\rfloor$。因为对于四个公式都要满足一个条件，所以最后 $y$ 的取值范围就是四个不等式的解集取并，即要满足 $\left\lfloor\sqrt{R^2-(X\pm 0.5)^2}\pm 0.5\right\rfloor$ 最小，可得 $-\left\lfloor\sqrt{R^2-(X+0.5)^2}-0.5\right\rfloor\le y\le\left\lfloor\sqrt{R^2-(X+0.5)^2}-0.5\right\rfloor$，所以 $y$ 的数量即为区间 $\left[-\left\lfloor\sqrt{R^2-(X+0.5)^2}-0.5\right\rfloor,\left\lfloor\sqrt{R^2-(X+0.5)^2}-0.5\right\rfloor\right]$ 内的整数数量，可得 $y$ 的数量为 $2\left\lfloor\sqrt{R^2-(X+0.5)^2}-0.5\right\rfloor+1$，统计答案即可。

## AC 代码

```cpp
// LUOGU_RID: 199101206
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll x,y,ans;

int main()
{
	x=read();
	for(R int i=1-x; i<x; ++i)
	ans+=((ll)(sqrt(x*x-(abs(i)+0.5)*(abs(i)+0.5))-0.5)<<1)+1;
    write(ans);
    return 0;
}
```

---

## 作者：PDAST (赞：0)

## 思路
思路非常简单，我们只需要枚举每行正方形的 $y$ 坐标，并计算该行正方形数即可，公式为：
$$
4 \times (R+\sum_{i=1}^{R} \lfloor \sqrt{R^{2} - (i+0.5)^{2}}  \rfloor ) - 3
$$
证明十分简单，可以从构造一个高为 $i+0.5$ 斜边长 $R$ 的三角形用勾股定理求底边长，底边长向下取整即为该行非中间十字的方块数。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int r,ans=0;
	cin>>r;
	for(int i=1;i<r;i++){
		double t=i+0.5;
		ans+=(int)(sqrt(r*r-t*t)-0.5);
	}
	ans+=(r-1);
	ans*=4;
	ans++;
	cout<<ans;
}
```

---

