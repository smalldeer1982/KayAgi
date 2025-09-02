# Magic Ship

## 题目描述

坐标系上有一只小船，现在想从 $(x_1,y_1)$ 去 $(x_2,y_2)$ 。每时刻都有风，会把船往对应的风向吹一个单位（比如北风会把船往南吹），风是循环的，吹完 $s_1 \sim s_n$ 就又会从 $s_1$ 开始。船在每一时刻都可以向指定方向移动一个单位。求船到目的地的最少时间，如果不能到达输出 **-1** 。

## 样例 #1

### 输入

```
0 0
4 6
3
UUU
```

### 输出

```
5
```

## 样例 #2

### 输入

```
0 3
0 0
3
UDD
```

### 输出

```
3
```

## 样例 #3

### 输入

```
0 0
0 1
1
L
```

### 输出

```
-1
```

# 题解

## 作者：George1123 (赞：13)

[$\Huge\textrm{In Cnblogs.}$](https://www.cnblogs.com/Wendigo/p/12819305.html)

---
> [Magic Ship](https://www.luogu.com.cn/problem/CF1117C)

> 你在 $(x_1,y_1)$，要到点 $(x_2,y_2)$。风向周期为 $n$，一个字符串 $s\{n\}$ 表示风向（每轮上下左右），每轮你都会被风向吹走一格。你可以在被风吹得被动移动的基础上选择每轮移动一格或不移动。求最少几轮可以到达终点。

> 数据范围：$0\le x_1,y_1,x_2,y_2\le 10^9$，$1\le n\le 10^5$。

---
**一句话题解：在最优行进策略中，人离终点的距离与风周期数之间的函数单调递减；二分答案轮数。**

---
**蒟蒻的前置准备：**

先通过坐标系平移简化计算：将起点 $start$ 置为原点，则终点 $end$ 为 $(x_2-x_1, y_2-y_1)$。

风向字符 $s_i$ 对应的四个字符 $'U'$，$'D'$，$'L'$，$'R'$ 分别表示上下左右走一格，对应位移向量 $\textrm{w}$ 为：

$\textrm{w}('U')=(0,1)$，$\textrm{w}('D')=(0,-1)$，$\textrm{w}('L')=(-1,0)$，$\textrm{w}('R')=(1,0)$，字符 $s_i$ 对应的位移向量 $\vec{m_i}=\textrm{w}(s_i)$。

令位移前缀和为：$\vec{ad_i}=\sum_{j=1}^i \vec{m_i}$，则一个风周期的总位移为 $\vec{ad_n}$。

上式表明：**尽管在一个长度为 $n$ 轮的风周期内，人被移动的轨迹是复杂的，但每个风周期对人的轨迹影响是恒定的。因此按风周期来看，人的移动与风周期之间的关系是线性的。**

---
**设当前走了 $k$ 轮：**

假如不考虑人主动的走动，只考虑风吹人动，那么人的位置为 $\left(ad_{k\bmod n}+ad_{n}\cdot \lfloor\frac kn\rfloor\right)$：

![lowd1.jpg](https://i.loli.net/2020/05/02/Ek1taWZgvINdjCz.jpg)

这时再考虑**人的主动走动，在 $k$ 轮中人最多走 $k$ 步**。

令 $\textrm{dis}(a,b)$ 表示 $a$ 和 $b$ 两点间的**曼哈顿距离**（$x$ 轴距离与 $y$ 轴距离之和）。

所以如果 $\textrm{dis}(end,now)\le k$，那么 $k$ 轮以内即可到达终点。

---
**找到单调性：**

对于式子 $\left(ad_{k\bmod n}+ad_{n}\cdot \lfloor\frac kn\rfloor\right)$：

**如果枚举 $i=k\bmod n$，则点 $now$ 的移动轨迹可以是一条直线。**

![lowd2.jpg图炸了回复反馈](https://i.loli.net/2020/05/02/RGnsAhpmwXOgca9.jpg)

**这时单独考虑 $\textrm{dis}(end,now)$：**

![lowd3.jpg图炸了回复反馈](https://i.loli.net/2020/05/02/xsXrwJQu8vBMPU7.jpg)

**可以发现 $\lfloor\frac kn\rfloor\leftrightarrow\textrm{dis}(end,now)$ 的函数图像如下：**（如果随风就能飘到终点，折线能与 $\lfloor\frac kn\rfloor$ 轴相切）

![lowd4.jpg图炸了回复反馈](https://i.loli.net/2020/05/02/AUxpwM6ZjS1zGLB.jpg)

**因为最终要比较 $\textrm{dis}(end,now)$ 和 $k$，所以作函数 $\lfloor\frac kn\rfloor\leftrightarrow\textrm{dis}(end,now)-k$：**

![lowd5.jpg图炸了回复反馈](https://i.loli.net/2020/05/02/Q8K74ons39jRw5u.jpg)

这时有个问题：这折线是否单调递减？蒟蒻拿图说服你你肯定不信，但是可以这么想：

**目的是距离终点更近，风力和人力相等，所以就算风再捣乱，如果人走得和风对着干，与终点的距离也不会变大。**

所以这个折线是单调递减的。

可是其实还有一种情况——**该折线有平行于 $\lfloor\frac kn\rfloor$ 轴的一段且与 $\lfloor\frac kn\rfloor$ 轴没有交点，便说明对于当前的 $i=k\bmod n$ 无解。**

---
上文提到：

> 如果 $\textrm{dis}(end,now)\le k$，那么 $k$ 轮以内即可到达终点。

**所以可以先如上文枚举 $i=k\bmod n$，然后二分 $\lfloor\frac kn\rfloor$，得到 $\lfloor\frac kn\rfloor\leftrightarrow\textrm{dis}(end,now)-k$ 图像上 $\le 0$ 的临界点整数 $\lfloor\frac kn\rfloor$，$k$ 就是对于这个 $i$ 的答案。总答案是对于每个 $i$ 的答案的最小值，如果对于每个 $i$ 都无解，输出 $-1$。**

如上图，$\lfloor\frac kn\rfloor=2$，可以通过 $i$ 推算出 $k$。

---
好了，小蒟蒻成功写出了一篇没人看得懂的题解。还是放代码吧（其实很短）：

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
#define lng long long
#define db double
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define rz resize
#define sz(x) (int)((x).size())
const int inf=0x3f3f3f3f;
const lng INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5;
int n; char s[N+7];
lng ans=INF;

//Point
typedef pair<lng,lng> point;
point st,ed,ad[N+7];
lng dis(point x,point y){return abs(x.fi-y.fi)+abs(x.se-y.se);}
point operator-(const point x,const point y){return mk(x.fi-y.fi,x.se-y.se);}
point operator+(const point x,const point y){return mk(x.fi+y.fi,x.se+y.se);}
point operator*(const point x,const lng y){return mk(x.fi*y,x.se*y);}

//Main
int main(){
	scanf("%lld%lld%lld%lld%d%s",&st.fi,&st.se,&ed.fi,&ed.se,&n,&s[1]);
	ed=ed-st;
	if(ed.fi==0&&ed.se==0) return puts("0"),0;
	for(int i=1;i<=n;i++)
		if(s[i]=='U') ad[i]=ad[i-1]+mk(0,1);
		else if(s[i]=='D') ad[i]=ad[i-1]+mk(0,-1);
		else if(s[i]=='L') ad[i]=ad[i-1]+mk(-1,0);
		else if(s[i]=='R') ad[i]=ad[i-1]+mk(1,0);
	for(int i=1;i<=n;i++){
		lng l=-1,r=1e12+1;
		while(l<r-1){
			lng mid((l+r)>>1);
			if(dis(ad[i]+ad[n]*(mid),ed)-mid*n-i<=0) r=mid;
			else l=mid;
		}
		if(dis(ad[i]+ad[n]*r,ed)-r*n-i<=0) ans=min(ans,r*n+i);
	}
	if(ans==INF) puts("-1");
	else printf("%lld\n",ans);
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1117C)

### 思路

对于小船每一次移动的位置，我们可以用类似前缀和的思想预处理每一次小船的位置。接着就可以**二分答案**，对于每一次判断的数 $mid$，计算它新的坐标，并判断其曼哈顿距离是否 $\le mid$。

`check` 函数展示：

```cpp
bool check(long long mid){
	//该代码中的px和py是预处理后的小船坐标位置
	long long sx=x1+px[n]*(mid/n)+px[mid%n];//计算新的x坐标
	long long sy=y1+py[n]*(mid/n)+py[mid%n];//计算新的y坐标
	return abs(sx-x2)+abs(sy-y2)<=mid;//判断它是否<=mid
}
```

**注意事项**

- 不开 `long long` 见祖宗。

- 二分的右边界一定要足够大，本人建议 $2^{60}$。

---

## 作者：_djc_ (赞：5)

## 题目分析

这是一道二分的经典例题。

首先想一想，如果没有风，那么船走到目的地的最短时间，其实就是船与目的地的曼哈顿距离，即为：船的起点为 $(x_1, y_1)$ ，终点为 $(x_2, y_2)$ ，则曼哈顿距离为 $|x_1 - x_2| + |y_1 - y_2|$ ，此即为最短时间。

那么现在有风了，应该怎么处理呢？我们不妨假设我们已经知道了需要多少天，那么我们可以预处理出船经过风的影响偏移了多少距离，然后让初始距离加上偏移量，求新的出发坐标与终点的曼哈顿距离。

那么我们应该如何求出天数呢？如果用 $x$ 天可以到达，那么在第二天逆风开船后仍然在终点，因此 $x + 1$ 天也可以到达，于是这个答案就可以二分。

二分判定时首先算出这几天风导致的船的位移，然后计算曼哈顿距离即可

## 代码实现

最后贴上代码，注释中有详细解释。

```cpp
#include<bits/stdc++.h>
#define maxn 100005
#define int long long
using namespace std;
int x_1, y_1, x_2, y_2;	//注意万能头毒瘤
int n;
int sumx, sumy;
int mo[maxn][2];	//这是要预处理风向的数组
bool check(int day){	//二分的判断函数：是否可在 mid 天到达
	int dayt = day;
	int xs = x_1, ys = y_1;
	if(day >= n){			//计算在day天时的偏移量，先处理构成循环的，再处理还未构成循环的
		int tmp = day / n;
		day %= n;
		xs += tmp * sumx;
		ys += tmp * sumy;
	}
	for(int i = 1; i <= day; i++){
		xs += mo[i][1];
		ys += mo[i][0];
	}
	int as = abs(xs - x_2) + abs(ys - y_2);	//现在所需天数
	if(as > dayt) return false;
	else return true;
}
int ans = 1e15;
signed main(){
	cin >> x_1 >> y_1 >> x_2 >> y_2 >> n;
	for(int i = 1; i <= n; i++){	//预处理风向
		char c;
		cin >> c;
		if(c == 'U') mo[i][0] = 1, mo[i][1] = 0;
		else if(c == 'D') mo[i][0] = -1, mo[i][1] = 0;
		else if(c == 'L') mo[i][0] = 0, mo[i][1] = -1;
		else if(c == 'R') mo[i][0] = 0, mo[i][1] = 1;
		sumy += mo[i][0], sumx += mo[i][1];
	}
	int l = 1, r = 1e15;	//本题数据较大，注意二分时左右开大一些
	while(l < r){	//二分
		int mid = l + r >> 1;
		if(check(mid)){
			r = mid;
			ans = min(ans, mid);
		}
		else l = mid + 1;
	}
	if(l != 1e15) cout << l;	//如果 l == 1e15，说明1-1e15之间的天数都不满足。我们天数开大一点已经保证测试数据的天数可包含在其内，所以l == 1e15时说明无解
	else cout << -1;
	
}
```


---

## 作者：elbissoPtImaerD (赞：2)

联合省选 2024 D1T1 弱化版。  
贝省选形式化题意创到了。

将位移拆成两类考虑：一类是风被动产生的，一类是人主动产生的。

不妨设前者起点为 $T(x_2-x_1,y_2-y_1)$，后者起点为 $S(0,0)$。

设答案为 $m$，枚举 $i = m \bmod n$，记 $N = \lfloor\frac mn \rfloor$。

不难发现若存在余数为 $i$ 的合法步数，等价于存在正整数 $N$ 使得 $|Fx(N)| + |Fy(N)| \le Fn(N)$ ，其中 $Fx,Fy,Fn$ 均为关于 $N$ 的一次函数。具体地，记前 $i$ 步位移为 $s$，一轮 $n$ 步位移为 $S$，$Fx(N) = S_xN + s_x + T_x$，$Fy(N) = S_yN + s_y + T_y$，$Fn(N) = Nn + i$。

将绝对值拆开解一元一次不等式即可求出 $N$ 的范围，从而得到余数为 $i$ 时的最小 $m$。

细节看代码：
```cpp
#define int long long
const map<char,pii>dr={{'U',{0,1}},{'D',{0,-1}},{'L',{-1,0}},{'R',{1,0}}};
il pii operator+(pii x,pii y){return pii(x.x+y.x,x.y+y.y);}
il pii operator+=(pii&x,pii y){return x=x+y;}
il pii operator-(pii x,pii y){return pii(x.x-y.x,x.y-y.y);}
il pii operator-=(pii&x,pii y){return x=x-y;}
il pii operator*(pii x,pii y){return pii(max(x.x,y.x),min(x.y,y.y));} // cap
il pii operator*=(pii&x,pii y){return x=x*y;}
const int inf=1LL<<60;
il void Solve()
{
  pii S,T;rd(S.x),rd(S.y),rd(T.x),rd(T.y),T-=S;
  int n;rd(n);
  str s;rd(s);
  pii d=T,ds{};
  for(int i=0;i<n;++i) ds-=dr.at(s[i]);
  int ans=inf;
  for(int i=0;i<=n;++i) {
    pii fx(ds.x,d.x),fy(ds.y,d.y),fn(n,i),rag(0,inf);
    // |fx(N)| + |fy(N)| \le fn(N)
    auto F=[&](pii x)->pii // g(x) \ge 0 => x \in [l,r]
    {
      if(x.x) {
        if(x.x>0) return pii(ceil((db)-x.y/x.x),inf);
        else return pii(-inf,floor((db)-x.y/x.x));
      }
      else return x.y<0?pii(inf,-inf):pii(-inf,inf);
    };
    for(pii g:{fn-fx-fy,fn-fx+fy,fn+fx-fy,fn+fx+fy}) rag*=F(g);
    if(rag.x<=rag.y) {
      cn(ans,rag.x*n+i);
    }
    if(i<n) d-=dr.at(s[i]);
  }
  wrt(ans<inf?ans:-1);
  return;
}
```

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1117/submission/249298233)

---

## 作者：LAICZ (赞：2)

### 题目大意
从 $(x_1,y_1)$ 出发前往 $(x_2,y_2)$，途中的风循环，为 $s_{1\cdots n}$，$\forall c\in s,c\in\{\texttt{U,D,L,R}\}$。问到达的最小时刻（从 $0$ 开始）。
### 题目解法
#### 预先准备
用 point 型存储点的坐标和位移，重载运算符，整体程序会变简洁许多。
```cpp
...
struct point{
	int x,y;
	friend point operator + (point a,point b){
		return (point){a.x + b.x,a.y + b.y};
	}
	friend point operator * (int a,point b){
		return (point){a * b.x,a * b.y};
	}
...
```
- ```+``` 运算符表示两点横、纵坐标之和
- ```*``` 运算符表示用一数依次乘一点横、纵坐标

例如，令 $a(1,1),b(2,-1),c=3$，

则 $a+b=(1+2,1+(-1))=(3,0)$，

$a*c=(3\times1,3\times 1)=(3,3)$。

#### 简单分析
**为方便，令 $\text{dis}(a,b)$ 为点对 $(a,b)$ 的曼哈顿距离,$sum_{x(t)}$，表示前 $t$ 时刻风对 $x$ 的位移；同理，$sum_{y(t)}$，表示前 $t$ 时刻风对 $y$ 的位移；$sum_t$ 表示前 $t$ 时刻风对坐标的位移（使用 point 型表示）。**

若现在是 $t$ 时刻，并且当前是可以到达终点的。那么，可以到达终点的原因，是因为在前 $t$ 时刻风导致的位移与起点的和与终点的曼哈顿距离不超过 $t$。

即 $\text{dis}((x_1 + sum_{x(t)},y_1 + sum_{y(t)}),(x_2,y_2)) \le t$，

你肯定觉得很绕~~我也觉得~~，那么举个通俗的例子：

比如样例 #1，

输入 #1
```
0 0
4 6
3
UUU
```
输出 #1
```
5
```
为什么第 $5$ 时刻的时候可以到达终点呢？前 $5$ 时刻风把我们往上吹 $5$ 格，用 point
 即 $(0,5)$。它与起点的和为 $(0,5)$，$\text{dis}((0,5),(4,6)))=5\le5$，所以是可以到达的。

也就是判断 $t$ 时刻能否到达的关键，就是求前 $t$ 时刻风导致的位移的和（由于曼哈顿距离是 $O(1)$，起点终点恒定，所以唯一的变量就在 $t$ 了）。

同时观察不等式  $\text{dis}((x_1 + sum_{x(t)},y_1 + sum_{y(t)}),(x_2,y_2)) \le t$。若 $t \gets t + 1$，左边 $+1$，右边**最多** $+1$(右边 $+1$ 的情况是 $s_{t+1}$ 是终点的方向；右边 $-1$ 的情况是除了右边 $+1$ 以外的情况)，也就是说若不等式在 $t=x$ 时成立，那么 $\forall x'(x'\ge x)$ 不等式也成立。

这样我们同时处理了两个问题：能否到达与 $t$ 的关系，以及进一步证明了随着 $t$ 的增加，能否到达是具有单调性的。

既然具有单调性，不难想到二分答案。

```cpp
int l = 0,r = maxt,mid;
while(l <= r){
	mid = (l + r) >> 1;
	if(check(mid)) r = mid;
	else l = mid + 1;
	if(l == mid) break;
}
if(l >= maxt) 
	cout<<-1<<endl;
else
	cout<<l<<endl;
```

问题来了，$maxt$（最极端情况下，需要多少时间到达）的取值是多少？假如起点终点分别在左下和右上角，并且 $s$ 为 $\texttt{DDDDDD...U}$($10^5-1$ 个 $\texttt{D}$ 后 $1$ 个 $\texttt{U}$)。那么 $maxt \approx 10^{13}$。为保证结果更加准确，可以添加适当的冗余，所以取 $maxt=10^{18}$。
#### 算法流程
- 输入 $x_1,y_1,x_2,y_2,n,s$。

- 预处理 $sum_i$ 表示前 $i$ 时刻风导致位移（先前用 $sum_x$ 和 $sum_y$ 是因为美观。此处已经定义点相加，则直接使用）。

- 二分答案

- 输出答案

当然这不一定考虑到细节，还需要自己调试。
#### 算法细节
- 一些结尾为 $1$ 的变量（如 y1）是 c++ 关键字，不能用。

- $l = 0,r = 10^{18}$。

- 二分的具体实现要搞懂细节，或参考题目解法-简单分析。

- check 的写法，将前 $t$ 时刻的位移拆解为 $a\cdot sum_n +sum_b$ 的位移。

- 边界，最大值不要多打少打 $0$。
#### 算法复杂度
空间复杂度，显然 $O(n)$，是处理位移前缀和时使用的。时间复杂度，求前缀和 $O(n)$，二分 $O(\log n)$，check $O(1)$。所以总的时间复杂度为 $O(n)$。
### 代码实现
内有注释，结合食用更好消化。


```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#define maxn 100005
#define maxt 1000000000000000005
#define int long long
using namespace std;

int a1,b1,a2,b2,n;
//(a1,b1) 起点，(a2,b2) 终点 
char s[maxn];
//s{n} 表示风的位移（题目中） 

struct point{
	int x,y;
	friend point operator + (point a,point b){
		return (point){a.x + b.x,a.y + b.y};
	}
	friend point operator * (int a,point b){
		return (point){a * b.x,a * b.y};
	}
	//点加，点乘 
}sum[maxn],d[200],p1,p2;
//sum[i] 表示前 i 时刻风导致的位移
//d['U','D','L','R'] 分别表示该指令的位移
//p1,p2 表示起点终点 

int dis(point a,point b){
	//表示 a 和 b 的曼哈顿距离 
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool check (int t){
	//检查 t 时刻可不可以到达终点 
	int a,b;
	a = t / n,b = t % n;
	//拆分为 a * sum[n] + sum[b] 
	point oft = a * sum[n] + sum[b];
	//前 t 时刻偏移量 
	point realstart = p1 + oft;
	//realstart:真实的起点，计算其与终点的曼哈顿距离 
	if(dis(realstart,p2) <= t)
		return true;
	else 
		return false;
}

signed main(){
	scanf("%lld%lld%lld%lld%lld%s",&a1,&b1,&a2,&b2,&n,s+1);
	p1 = {a1,b1},p2 = {a2,b2};
	d['U'] = {0,1},d['D'] = {0,-1};
	d['L'] = {-1,0},d['R'] = {1,0};
	//d['U','D','L','R'] 分别表示该指令的位移
	for(int i = 1;i <= n;i++){
		sum[i] = sum[i - 1] + d[s[i]];
		//前缀和 
	}
	
	int l = 0,r = maxt,mid;
	while(l <= r){
		mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
		if(l == mid) break;
	}
	if(l >= maxt)
	    //如果比最大的时间还大，那么肯定不可能到达 
		cout<<-1<<endl;
	else
		//输出的是最小时间 
		cout<<l<<endl;
	
	return 0;
}
```

### AC 记录
附上 AC 记录：
![](https://cdn.luogu.com.cn/upload/image_hosting/rx1e7ake.png)

---

## 作者：cike_bilibili (赞：1)

显然如果 $t$ 这个时刻是合法答案，那么 $t+1$ 时一定可以重新移动将风的移动抵消，从而回到 $t$ 时刻，那么 $t+1$ 一定也是合法答案，答案满足单调性，考虑二分。

处理风序列的前缀和，设当前二分答案为 $m$，从而快速求出 $m$ 时刻的坐标并判断与终点的曼哈顿距离是否小于 $m$ 即可。
```cpp
#include <bits/stdc++.h>
#define y1 y3
#define int long long
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int x1,x2,y1,y2;
int n;
char ch[1000005];
int pre_x[1000005],pre_y[1000005];
int x,y;
signed main(){
	x1=read(),y1=read(),x2=read(),y2=read();
	n=read();
	string s;
	cin>>s;
	for(int i=1;i<=n;i++)ch[i]=s[i-1];
	for(int i=1;i<=n;i++){
		pre_x[i]=pre_x[i-1],pre_y[i]=pre_y[i-1];
		if(ch[i]=='U')pre_y[i]++,y++;
		if(ch[i]=='D')pre_y[i]--,y--;
		if(ch[i]=='L')pre_x[i]--,x--;
		if(ch[i]=='R')pre_x[i]++,x++;
	}
	int L=0,R=1e18;
	int ans=-1;
	while(L<=R){
		int mid=L+R>>1;
		int tx=x1+(mid/n)*x+pre_x[mid%n];
		int ty=y1+(mid/n)*y+pre_y[mid%n];
		if(abs(x2-tx)+abs(y2-ty)<=mid)ans=mid,R=mid-1;
		else L=mid+1;
	}
	cout<<ans<<'\n';
}
```

---

## 作者：dyc2022 (赞：1)

## 题意描述：

给定 $(x_1,y_1)$ 与 $(x_2,y_2)$，有一只小船在 $(x_1,y_1)$ 位置。现在每一个时刻小船都可以向上或下或左或右移动一步，或者站着不动。同时每一个时刻都会有周期性的风，会将小船往上下左右中的一个方向吹一格。现在求小船从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 的最短时间。

## 题目分析：

这是一个求最小值的问题，所以选择使用二分答案进行求解。

我们还知道，在一段时间中小船移动的距离等于小船自身移动的距离加上风给小船带来的偏移量。

因此，我们先将起点设为原点，则终点的坐标为 $(x_2-x_1,y_2-y_1)$。然后使用一个前缀和记录偏移量。设终点坐标为 $e$，风带来的偏移量为 $w$。则我们需要做的就是在无风条件下走到 $e-w$。最后判断能否在特定时间内走到 $e-w$ 即可。具体实现是使用 `pair` 进行重载，然后就可以很方便操作。

具体代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int sx,sy,ex,ey,n,l=1,r=1e15;
char ch[100006];
pair<int,int> sum[100006];
pair<int,int> operator +(pair<int,int> x,pair<int,int> y){return make_pair(x.first+y.first,x.second+y.second);}
pair<int,int> operator -(pair<int,int> x,pair<int,int> y){return make_pair(x.first-y.first,x.second-y.second);}
pair<int,int> operator *(pair<int,int> x,int y){return make_pair(x.first*y,x.second*y);}
pair<int,int> dire(char ch)
{
	switch(ch)
	{
		case 'U':return make_pair(0,1);
		case 'D':return make_pair(0,-1);
		case 'L':return make_pair(-1,0);
		case 'R':return make_pair(1,0);
	}
}
int judge(int tim)
{
	pair<int,int> chng=make_pair(ex,ey)-(sum[n]*floor(tim*1.0/n)+sum[tim%n]);
	return abs(chng.first)+abs(chng.second)<=tim;
}
main()
{
	scanf("%lld%lld%lld%lld%lld%s",&sx,&sy,&ex,&ey,&n,ch+1);
	ex-=sx,ey-=sy;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+dire(ch[i]);
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(judge(mid))r=mid;
		else l=mid+1;
	}
	if(l==1e15)printf("-1");
	else printf("%lld",l);
	return 0;
}
```

---

## 作者：Cappuccino_mjj (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1117C)
题目意思：

坐标系上有一只小船，想从 $(x_1,y_1)$ 的位置去 $(x_2,y_2)$。然后会有风，风会把船往对应的方向吹一个单位。问船最少用多长时间到达终点，到不了输出 ``-1``。

---

思路：

思路其实是比较容易想到的。

这道题所用到的方法是二分答案。

首先我们定义四个数组，分别记录小船将会移动的方向和次数，进行预处理。

接着二分枚举移动的次数。因为 $x$ 和 $y$ 最大是 $10^9$，所以我们定义二分的最右边时数值要开得大一点。

那么我们二分的函数该怎么写呢？首先定义两个新的坐标变量，用现在小船的坐标加上当前会被风吹多远的格子数。这里我们将一组重复循环的风一次性加上，剩下的再单独加。

用预处理的数组算小船会被风吹到哪里后，再算出小船到终点的曼哈顿距离。如果这个曼哈顿距离比我们枚举的次数还小，就返回真；否则是假。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n,x,y,xx,yy,sumx[N],sumy[N],ans,l,r;
string s;
bool check(int id)//计算偏移的位置
{
	int sx=x+sumx[n]*(id/n)+sumx[id%n];//计算新的坐标
	int sy=y+sumy[n]*(id/n)+sumy[id%n];
	return abs(sx-xx)+abs(sy-yy)<=id;//判断曼哈顿距离
}
signed main()
{
	cin>>x>>y>>xx>>yy;
	cin>>n>>s;
	s=" "+s;
	for(int i=1;i<=n;i++)
	{
		sumx[i]=sumx[i-1],sumy[i]=sumy[i-1];
		if(s[i]=='U')sumy[i]++;//预处理会偏移多少
		else if(s[i]=='D')sumy[i]--;
		else if(s[i]=='L')sumx[i]--;
		else if(s[i]=='R')sumx[i]++;
	}
	l=0,r=1ll<<60,ans=-1;//由于x，y很大，所以r要开大点
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid))
			ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}
```
---

完美撒花~

---

## 作者：1234567890sjx (赞：0)

没思维含量的题。考虑季风。

可以发现若 $x$ 时刻可行则 $x+1$ 时刻也可行。因此二分答案。每一次先计算出循环节的数量然后剩下的散块暴力计算即可。时间复杂度为 $O(n\log n)$。

下面给出二分判断的部分：

```cpp
bool chk(int px){
    int x=0,y=0;
    F(i,1,n){
        if(s[i]=='U')++y;
        else if(s[i]=='D')--y;
        else if(s[i]=='L')--x;
        else ++x;
    }
    x*=px/n,y*=px/n;
    F(i,1,px%n){
        if(s[i]=='U')++y;
        else if(s[i]=='D')--y;
        else if(s[i]=='L')--x;
        else ++x;
    }
    return abs(x-x2)+abs(y-y2)<=px;
}
signed main(){
    //输入
    y2-=y1,x2-=x1;
    //二分
}

```

---

## 作者：gesong (赞：0)

题目传送门：[CF1117C](https://www.luogu.com.cn/problem/CF1117C)。
# 思路
首先我们可以发现，如果 $x$ 时刻可以到达目的地，那么 $x+1$ 时刻一定也可以到达，因此我们可以先进行二分答案。

考虑判断 $x$ 时刻是否可行：首先我们可以把船的移动与风的移动分开，我们可以让风先吹 $x$ 时刻，然后我们再移动 $x$ 时刻，这时候判断合法性就很容易了，我们只需要判断风吹完时的位置到目的地的曼哈顿距离是否小于等于 $x$ 即可。

上述想法已经非常优秀了，但是如果直接枚举风的移动就会导致时间复杂度太高，但我们发现风的移动是循环的，我们可以花 $O(n)$ 的代价求出 $1$ 次循环的偏移量 $dx$ 和 $dy$，然后将起点的位置加上偏移量的 $\lfloor \frac{x}{n}\rfloor$ 倍，最后枚举剩下的不足一次循环的风的移动单独加上即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n;string s;
inline bool check(int sx,int sy,int zx,int zy,int mid){
	int dx=0,dy=0;
	for (int i=1;i<=n;i++){
		if (s[i]=='U') dy++;
		if (s[i]=='D') dy--;
		if (s[i]=='L') dx--;
		if (s[i]=='R') dx++;
	}
	sx+=mid/n*dx,sy+=mid/n*dy;
	for (int i=1;i<=mid%n;i++){
		if (s[i]=='U') sy++;
		if (s[i]=='D') sy--;
		if (s[i]=='L') sx--;
		if (s[i]=='R') sx++;
	}
	return abs(sx-zx)+abs(sy-zy)<=mid;
}
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	int sx=read(),sy=read(),zx=read(),zy=read();
	n=read();cin>>s;s=" "+s;
	int l=0,r=1e18,ans=-1;
	while(l<=r){
		int mid=l+r>>1;
		if (check(sx,sy,zx,zy,mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
    return 0;
}



```

---

