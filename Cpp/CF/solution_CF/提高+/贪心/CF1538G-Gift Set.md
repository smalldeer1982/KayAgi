# Gift Set

## 题目描述

Polycarp有$x个$红糖和$y$个蓝糖，现在他想用这些糖果做一些礼品盒（gift set），但规定每个礼品盒里必须有$a$个红糖、$b$个蓝糖或$b$个红糖、$a$个蓝糖。现在求他最多能做成多少个礼品盒。

## 样例 #1

### 输入

```
9
10 12 2 5
1 1 2 2
52 311 13 27
1000000000 1000000000 1 1
1000000000 1 1 1000000000
1 1000000000 1000000000 1
1 2 1 1
7 8 1 2
4 1 2 3```

### 输出

```
3
0
4
1000000000
1
1
1
5
0```

# 题解

## 作者：7KByte (赞：12)

交换令 $x\le y$，$a\le b$。

那么一定是选择若干个二元组 $(a,b)$，再选择若干个二元组 $(a+b,a+b)$。

选择一个 $(a,b) $能使 $x,y$ 的差减小 $(b-a)$，所以我们先选择 $\left\lfloor\dfrac{y-x}{b-a}\right\rfloor$ 个 $(a,b)$。剩下的全部选 $(a+b,a+b)$。

为避免特判，再计算一下选择 $\left\lfloor\dfrac{y-x}{b-a}\right\rfloor+1$ 个 $(a,b)$ 的情况。

但还是要特判 $a=b$ 的情况，这种情况答案为 $\left\lfloor\dfrac{\min(x,y)}{a}\right\rfloor$。

时间复杂度 $\mathcal{O}(1)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
using namespace std;
int x,y,a,b;
void solve(){
	scanf("%d%d%d%d",&x,&y,&a,&b);
	if(x>y)swap(x,y);if(a>b)swap(a,b);
	if(x<a||y<b){puts("0");return ;}
	int res=y-x,lim=b-a;
	if(!lim){
		printf("%d\n",min(x,y)/a);
		return ;
	}
	int cur=min(res/lim,min(x/a,y/b));
	x-=cur*a,y-=cur*b;int ans=cur+min(x,y)/(a+b)*2;
	if(x>=a&&y>=b)x-=a,y-=b,cur++;
	printf("%d\n",max(ans,cur+min(x,y)/(a+b)*2));
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：10)

2021/7/17:规范了格式

2021/7/15:增加了句号与空格

2021/7/9:修改了表达更严谨

2021/6/21:增加了 $LaTeX$

~~良心题解 管理员求过~~

### 题意简述
X 和 Y 两个背包，容量分别为 $x$ 和 $y$，每次操作在背包不溢出的条件下二选一：

* op1： 将体积为 $a$ 的物体放入 X，将体积为 $b$ 的物体放入 Y

* op2： 将体积为 $b$ 的物体放入 X，将体积为 $a$ 的物体放入 Y

求操作数的最大值（设为 $ans$ ）。

### 题目分析

**开始的开始先膜拜题解中 $O(1)$ 的大佬 SharpnessV。**

~~但其实没有必要跑这么快,这篇题解写给像我这样不太会或没时间数学推理的蒟蒻。~~

设 $f(x)$ 为 op1 恰有 $x$ 次时最大操作数。

有一个非常有用的性质：

**$f(x)$ 一定是上凸函数。**

感性理解一下，（不妨设 $a\leq b$ ）若全是 op1 ，则 X 还有大量空间没有利用，若全是 op2 ，则 Y 还有大量空间没有利用，在 op1 数量在增加的过程中，$ans$ 先增加，之后达到峰值（X 和 Y 利用率均衡），最后 $ans$ 下降。

样例 testcase1（ $f(x)=-1$ 表示无解）:

![](https://cdn.luogu.com.cn/upload/image_hosting/y319iihj.png)

求单峰函数的最值怎么办？

爬山（套用模拟退火代码）！

没学过模拟退火的[戳这里](https://www.cnblogs.com/rvalue/p/8678318.html)看奆佬 rvalue 博客。

$\mathcal{O}(K\log T)$ 时间复杂度($K$ 为常数,$T$ 为初始温度)。

### Code
```cpp
#include<bits/stdc++.h>
#define down 0.96//下降速率
using namespace std;
typedef long long ll;
void setio(string);

int n,m,a,b;
double ans;
double check(double x){
	if(x<0)return -1;
	if(n-a*x<0 || m-b*x<0)return -1;
	double y=min((n-a*x)/b,(m-b*x)/a);
	return x+y;
}
ll check2(ll x){
	if(x<0)return -1;
	if(n-a*x<0 || m-b*x<0)return -1;
	ll y=min((n-a*x)/b,(m-b*x)/a);
	return x+y;
}
void SA() { //模拟退火
	double t=1000000;//初始温度
	while (t>1e-15) { //略大于0
		double aa=ans+(rand()*2-RAND_MAX)*t;
		double pan=check(aa);
		double de=pan-check(ans);
		if(de>0) { //如果此答案更优,就接受
			ans=aa;
		}
		t*=down;
	}
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>m>>a>>b;
		ans=0;
		SA();
		SA();
		SA();
		SA();
		cout<<max(check2(ans),check2(ans+1))<<endl;
	}
	return 0;
}

```


---

## 作者：V1mnkE (赞：6)

我来提供一种二分的做法。
## 思路
交换使 $x\leq y,a\leq b$，设有 $A$ 个礼品盒里有 $a$ 个红糖、$b$ 个蓝糖， $B$ 个礼品盒里有 $b$ 个红糖、$a$ 个蓝糖，由题意可得不等式：
$$\begin{cases}
Aa+Bb\leq x\\
Ab+Ba\leq y
\end{cases}$$
将一式和二式相加，得 $A+B\leq \frac{x+y}{a+b}$，显然 $A+B$ 即为礼品盒总数，在值域 $[0,\frac{x+y}{a+b}]$ 之间二分即可。

**check 函数实现**：

令传入的参数为 $k$，可以算出至少要 $ak$ 个红糖，则会剩 $x-ak$ 个红糖，尝试将尽量多的盒子里面的红糖换成 $b$ 个，就可以得出蓝糖的最小使用数量，检验其是否大于 $y$ 即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = getchar();
    }
    return x * f;
}
inline void write(int x) {
    static char buf[20];
    static int len = -1;
    if (x < 0) putchar('-'), x = -x;
    do buf[++len] = x % 10, x /= 10;
    while (x);
    while (len >= 0) putchar(buf[len--] + '0');
    putchar('\n');
}
int t, a, b, x, y;
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
bool check(int k) {
    int les = x - k * a;
    if (les < 0) return false;
    int p = 0;
    if (a != b) p = les / (b - a);
    if (p * a + (k - p) * b <= y) return true;
    return false;
}
int main() {
    t = read();
    while (t--) {
        x = read(), y = read(), a = read(), b = read();
        if (x > y) swap(x, y);
        if (a > b) swap(a, b);
        int l = 0, r = (x+y)/(a+b), mid = l + r >> 1;
        int ans = 0;
        while (l < r) {
            mid = l + r >> 1;
            if (check(mid)) {
                ans = max(ans, mid);
                l = mid + 1;
            } else
                r = mid - 1;
        }
        if (check(r)) ans = max(ans, r);
        //if (!check(mid)) mid--;
        //if (check(mid + 1)) mid++;
        cout << ans << endl;
     //   cout << mid << endl;
    }
    // system("PAUSE");
}
```

---

## 作者：WeLikeStudying (赞：4)

- 被一位大佬推荐做了这题。
- ~~既然这样那就先不看题解。~~

**题意**
- [原题](https://www.luogu.com.cn/problem/CF1538G)。
- 给定正整数 $m,n,a,b$。
- 最大化 $x+y$，满足约束：
$$\begin{cases}ax+by\le m\\bx+ay\le n\end{cases}$$
- 另外，还有约束 $x,y\in \mathbf{N}$。
- ~~整数线性规划，NPC石锤。~~
- $1\le m,n,a,b\le 10^9$，测试组数不大于 $10^4$。

**蒟蒻的思路**
- ~~笔者显然不会解整数线性规划。~~
- 不过这题的图很有规律啊。
![](https://cdn.luogu.com.cn/upload/image_hosting/exbcz703.png)
- 当然也存在退化的情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/gz7ybiap.png)
- 这个时候可以直接出解，方法就是判断交点是否在第一象限。
- 否则，解方程组（求交点）（这里假设 $a\ne b$，事实上它在可以在之前判掉）得：

$$\begin{cases}x=\dfrac{ma-nb}{a^2-b^2}\\y=\dfrac{na-mb}{a^{2}-b^{2}}\end{cases}$$

- 显然的上界：$\lfloor x+y\rfloor=\left\lfloor\dfrac{m+n}{a+b}\right\rfloor$，但它不一定可行，例子：
![](https://cdn.luogu.com.cn/upload/image_hosting/nycq0b1p.png)
- 显然的下界：$\lfloor x\rfloor+\lfloor y\rfloor$，但它不一定最优，例子：
![](https://cdn.luogu.com.cn/upload/image_hosting/0i7dbjsa.png)
- 这两个值最多只相差 $1$，已经很接近了，难道这样还要把整个轮廓线检查一遍？
- haha，其实并不用，你只需要发现一个简单的事实，最优解要么横坐标值为 $\lfloor x\rfloor$，要么纵坐标值为 $\lfloor y\rfloor$。
- 为啥？考虑上半条直线（比较平缓的那条），可行点往左移一格（尽量向上），横坐标减 $1$，但由于直线的斜率，纵坐标绝对加不到 $1$，下半条直线同理。
- 所以就可以单次 $O(1)$ 解决该问题，尽管用了很多图但思路还是很直接的。
- [代码实现](https://www.luogu.com.cn/paste/fdwjrg59)。

**大佬的思路**
- 大佬首先想到了一个贪心，如果 $m<n$，$a<b$ 优先将 $a$ 分配给 $m$，$b$ 分配给 $y$ 不会更优。
- 不过直接这样搞肯定会超时，但大佬发现，第一次让 $m>n$ 之后，$|m-n|\le|a-b|$ 总是成立，也就是大小关系会反复换过来。
- 所以一定是分别分配 $a,b$，再将 $a+b$ 平均分配，通过这样的思路，就可以 $O(1)$ 出解啦。
- 好处就是思路直接且不需要开长整型。
- [代码实现](https://www.luogu.com.cn/paste/2wecxjs7)。

**后记**
- 似乎想到了不一样的做法呢，发个题解吧。

---

## 作者：gargantuar (赞：4)

先% $O(1)$ 神仙

#### 题目分析
蒟蒻考场不容易想到 $O(1)$ ，所以用的是二分，应该比其他题解的三分和模拟退火好写一点

我们改变一下问题，你有两个 [candy box](https://candybox2.github.io) ，每次可以从一个里取 $a$ 个糖并从另一个里取 $b$ 个糖，问最多取几次。

二分答案，对于一个答案 $c$ ，表示从一个盒子里取 $c$ 次，我们先随便选一个盒子取 $c$ 次，并且最大化这个盒子取出糖的数量，这样就能最小化从另一个盒子中取出糖的数量，之后判断另一个盒子能不能取 $c$ 次糖，通过上一步我们已经知道了第一个盒子取几次 $a$ ，取几次 $b$ ，所以这一步是      $O(1)$ 的，然后二分即可

#### 代码

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
ll x,y,a,b,l,r;
int main() {
	ios::sync_with_stdio(false);
	ll tx;
	cin>>tx;
	while(tx--) {
		l=0,r=1e9+3;
		cin>>x>>y>>a>>b;
		if(a<b)swap(a,b);
		if(a==b) {
			cout<<min(x,y)/a<<endl;
			continue;
		}
		ll ca=a-b;
		while(l<r-1) {
			ll mid=((l+r)>>1),z=0;
			if(x-b*mid<0) {
				r=mid;
				continue;
			}
			z=x-b*mid;
			z=min(z/ca,mid)
			if(z*b+(mid-z)*a>y) {
				r=mid;
			}else l=mid;
		}
		cout<<l<<endl;
	}
}
```


---

## 作者：Yansuan_HCl (赞：4)

为了方便描述，令 **A 组礼物** 为 $a$ 个红糖， $b$ 个蓝糖的组合， **B 组礼物** 则相反。

设装 $x$ 个 A 组礼物，剩下糖果尽量装 B 组礼物，能装 $y$ 组礼物。

首先，~~根据小学知识~~可以得到：在**全部装 A 组礼物**与**全部装 B 组礼物**这两个极端之间， $y$ 一定会有一个区间单调递增，在某个 $x$ 达到顶峰，之后随 $x$ 增大而递减。即：若我们减少选用一个 A 组礼物，那么剩下的糖果就会对 B 组礼物的个数造成影响（可能增加 1 个，甚至增加 0.3 或者 1.2 等非整数个）。

所以 $y$ 是一个单峰函数，可以使用三分法求解。关于三分法的内容可以参考[三分法板子 P3382](https://www.luogu.com.cn/problem/P3382) 。

代码注意：要保证算出来的值连续，请使用 `long double` 来计算 $y$ 。 否则，会出现 $y$ 值不连续而无法判断往哪个方向走。

```cpp
#include <bits/stdc++.h>
#define ms(x, v) memset(x, v, sizeof(x))
#define rg register
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
inline void rd(int& i) {
	scanf("%d", &i);
}
inline void rd(ll& l) {
	scanf("%lld", &l);
}

ll x, y, a, b;

// 要保证函数是连续的所以使用double以免无法判断增减
long double calc(long double k) {
    // min((x - a * k) / b, (y - b * k) / a) 为: 剩下的糖果可组成几套 B 组礼物
	return k + min((x - a * k) / b, (y - b * k) / a);
}
ll check() {
	ll l = 0, r = min(x / a, y / b);
	if (!r) return calc(l);
	while (l < r) {
		ll mid = (l + r) >> 1;
		if (r - l <= 5000) { // 丑陋的，避免死循环的写法
			long double mxx = -1145141919.00;
			for (; r >= l; --r)
				mxx = max(mxx, calc(r));
			return mxx;
		}
		if (calc(mid - 1) <= calc(mid) && calc(mid) <= calc(mid + 1)) { // 函数在"爬升", 单调增
			l = mid; // 左端点向极值点靠近
		} else if (calc(mid - 1) >= calc(mid) && calc(mid) >= calc(mid + 1)) { // 函数在"下降", 单调减
			r = mid; // 右端点向极值点靠近
		} else if (calc(mid - 1) <= calc(mid) && calc(mid) >= calc(mid + 1)) { // 函数值在 mid 达到顶峰
			return calc(mid);
		}
	}
}

void solve() {
	printf("%lld\n", check());
}

int main() {
	ll t; rd(t);
	while (t--) {
		rd(x); rd(y); rd(a); rd(b);
		solve();
	}
	return 0;
}
```

---

## 作者：Ak_hjc_using (赞：1)

更好的阅读体验：[this](https://www.cnblogs.com/oierhjc114514/p/18750633)

由于题目没有规定 $x < y$ 且 $a < b$，故交换使得 $x < y$ 且 $a < b$。

本篇题解使用算法：**二分**。

很明显的单调性，故可以直接二分求解，二分最大可以实现的礼盒数，其中 $l$ 与 $r$ 的范围需要稍微推导一下公式，$l$ 毋庸置疑，为 $0$，$r$ 的范围即为不管是否可以实现，理论最大的礼盒数，即 $x$ 与 $y$ 的总和去除以 $a$ 与 $b$ 的总和，故 $[l, r]$ 为 $[0, \displaystyle \frac{x+y}{a+b}]$。

Check 函数实现：

判断是否合法即可，传入参数 $k$ 为当前需要检查的礼盒数，判断是否可以使得所有的糖果可以装满这 $k$ 个礼盒即可。

[Code](https://www.luogu.com.cn/paste/kqgnjb89)。

---

## 作者：Super_Cube (赞：1)

# Solution

红糖与蓝糖等价，所以令 $x\le y,a\le b$。

特判 $a=b$，此时答案为 $\left\lfloor\dfrac{x}{a}\right\rfloor$。

做一次 $a,b$ 再做一次 $b,a$ 使得红蓝均减少 $a+b$ 是很好的策略，所以先想办法使得 $x$ 与 $y$ 接近。每做一次 $a,b$ 会使 $x$ 与 $y$ 的差值减少 $b-a$，于是先做 $c=\min\left\{\left\lfloor\dfrac{y-x}{b-a}\right\rfloor,\left\lfloor\dfrac{x}{a}\right\rfloor,\left\lfloor\dfrac{y}{b}\right\rfloor\right\}$ 次操作，再做 $d=\left\lfloor\dfrac{x-ca}{a+b}\right\rfloor$ 次均匀减少。

现在还剩下 $x-ca-d(a+b)$ 个红糖，$y-cb-d(a+b)$ 个蓝糖，此时有可能还可以再做一次操作，需要判断下。

# Code

```cpp
#include<bits/stdc++.h>
int T,n,m,x,y,a,b;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d",&n,&m,&x,&y);
		if(n>m)std::swap(n,m);
		if(x==y){
			printf("%d\n",n/x);
			continue;
		}
		if(x>y)std::swap(x,y);
		a=std::min((m-n)/(y-x),std::min(n/x,m/y));
		b=(n-a*x)/(x+y);
		if(n-a*x-b*(x+y)>=x&&m-a*y-b*(x+y)>=y)++a;
		printf("%d\n",a+(b<<1));
	}
	return 0;
}
```

---

## 作者：BHDwuyulun (赞：0)

### 1 [题目传送门](https://www.luogu.com.cn/problem/CF1538G)
### 2 大体思路
通过二分搜索寻找一个最大的礼品盒数量 $mid$，使得在该数量下，红糖和蓝糖的搭配满足题目要求。

首先处理特殊情况：如果 $a$ 等于 $b$，直接输出 $\min(\frac{x}{a},\frac{y}{a})$。

调整输入数据，确保 $x\le y$ 且 $a\le b$。初始化二分搜索的上下界，$l$ 为 $0$，$r$ 为 $y$。通过二分搜索，每次取中间值 $mid$，调用函数确定是否能制作出 $mid$ 个礼品盒。  
函数中计算红糖和蓝糖的最大最小数量，确保能够满足糖果数量的要求。  
如果红糖最大数量不小于蓝糖最小数量，则当前 $mid$ 值有效，将 $l$ 调整到 $mid$。  
否则，需要减小 $mid$ 的值，将 $r$ 调整到 $mid-1$。重复以上步骤，直到 $l$ 大于 $r$，输出最终结果 $l$。
### 3 AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define bug printf("---OK---")
#define pa printf("A: ")
#define pr printf("\n")
#define pi acos(-1.0)
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
ll x,y,a,b;
int check(int mid){
	int l=ceil(1.0*(x-b*mid)/(a-b));
	int r=floor(1.0*(y-a*mid)/(b-a));
	l=max(l,0);
	r=min(r,mid);
	return l<=r;
}
void solve(){
	cin>>x>>y>>a>>b;
	if(a==b){
		cout<<min(x/a,y/a);
		return;
	}
	if(x>y){
		swap(x,y);
	}
	if(a>b){
		swap(a,b);
	}
	ll l=0,r=y;
	while(l<r){
		ll mid=(l+r+1)>>1;
		if(check(mid)){
			l=mid;
		}
		else{
			r=mid-1;
		}
	}
	cout<<l;
}
int main(){
	ll t;
	cin>>t;
	while(t--){
		solve();pr;
	}
	return 0;
}
```

---

