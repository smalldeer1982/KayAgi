# Bear and Bowling 4

## 题目描述

Limak is an old brown bear. He often goes bowling with his friends. Today he feels really good and tries to beat his own record!

For rolling a ball one gets a score — an integer (maybe negative) number of points. Score for the $ i $ -th roll is multiplied by $ i $ and scores are summed up. So, for $ k $ rolls with scores $ s_{1},s_{2},...,s_{k} $ , the total score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF660F/dc22606298d977fae92bc67b7a4815c447193831.png). The total score is $ 0 $ if there were no rolls.

Limak made $ n $ rolls and got score $ a_{i} $ for the $ i $ -th of them. He wants to maximize his total score and he came up with an interesting idea. He can say that some first rolls were only a warm-up, and that he wasn't focused during the last rolls. More formally, he can cancel any prefix and any suffix of the sequence $ a_{1},a_{2},...,a_{n} $ . It is allowed to cancel all rolls, or to cancel none of them.

The total score is calculated as if there were only non-canceled rolls. So, the first non-canceled roll has score multiplied by $ 1 $ , the second one has score multiplied by $ 2 $ , and so on, till the last non-canceled roll.

What maximum total score can Limak get?

## 说明/提示

In the first sample test, Limak should cancel the first two rolls, and one last roll. He will be left with rolls $ 1,-3,7 $ what gives him the total score $ 1·1+2·(-3)+3·7=1-6+21=16 $ .

## 样例 #1

### 输入

```
6
5 -1000 1 -3 7 -8
```

### 输出

```
16
```

## 样例 #2

### 输入

```
5
1000 1000 1001 1000 1000
```

### 输出

```
15003
```

## 样例 #3

### 输入

```
3
-60 -70 -80
```

### 输出

```
0
```

# 题解

## 作者：sunzh (赞：8)

设$val_{i,j}$为区间$[l,r]$的答案

根据题意，我们可以维护$a_i$和$i* a_i$的前缀和$sum1,sum2$

$val_{l,r}=sum2[r]-sum2[l-1]-(l-1)*(sum1[r]-sum1[l-1])$

我们枚举$r$

对于所有$val_{l',r}\le val_{l,r}$，有

$(l'-1)*sum1_{l'-1}-sum2_{l'-1}-(l'-1)*sum1_r\le (l-1)*sum1_{l-1}-sum2_{l-1}-(l-1)*sum1_r$

我们发现这个式子可以斜率优化

斜率优化一般把我们要的最大值/最小值也就是这里的$val_{l,r}$放在$b$里面，那么$(l-1)*sum1_{l-1}-sum2_{l-1}-(l-1)*sum1_r$就可以表示成$y-kx$，

把跟$r$有关的放在$k$里面，$k=sum1_r$

于是$b=val_{l,r}-sum_r,x=l-1,y=(l-1)*sum1_{l-1}$

因为是最大值，我们维护一个上凸壳每次二分找到第一个斜率小于$sun1_r$的位置，然后更新答案即可

~~以下代码仅供参考~~
```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<set>
#include<vector>
#include<cmath>
#define PII pair<int,int>
#define pb push_back
#define ep emplace_back
#define mp make_pair
#define fi first
#define se second
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f==1?x:-x;
}
inline void print(int x){
	if(x<0) putchar('-'),x=~x+1;
	if(x>=10) print(x/10);
	putchar((x%10)|48);
}
const double eps=1e-12;
int n;
int a[200010]; 
int sum1[200010],sum2[200010];
int stk[200010];
int top;
double getx(int id){
	if(id==0) return 0;
	return id-1;
}
double gety(int id){
	if(id==0) return 0;
	return (id-1)*(sum1[id-1])-sum2[id-1];
}
double getslope(int x,int y){
	return (gety(y)-gety(x))/(getx(y)-getx(x)+eps);
}
int calc(int l,int r){
	return sum2[r]-sum2[l-1]-(l-1)*(sum1[r]-sum1[l-1]);
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) sum1[i]=sum1[i-1]+a[i],sum2[i]=sum2[i-1]+a[i]*i;
	int ans=0;
	for(int i=1;i<=n;++i){
		if(top>1){
			while(top>1&&getslope(stk[top-1],stk[top])<getslope(stk[top-1],i)) --top;
			stk[++top]=i;
		}
		else{
			stk[++top]=i;
		}
		int l=2,r=top;
		double k=sum1[i];
		int res=1;
		while(l<=r){
			int mid=l+r>>1;
			if(getslope(stk[mid-1],stk[mid])>=k)res=mid,l=mid+1;
			else r=mid-1;
		}
		ans=max(ans,calc(stk[res],i));
	}
	print(ans);
} 
```


---

## 作者：幻影星坚强 (赞：6)

先考虑普通的dp。

设 $num1_i$为前i个数的和，$num2_i$为前i个$j*a_j$的和。

则      
$v_{i, j} = sum2_i-sum2_j-j*(sum1_i-sum1_j)$   
$dp_i = max(v_i)$

这样是$O(n^2)$的。

于是对于$v$我们考虑将含i的都移到左边。

$v_{i, j} - sum2_i + j * sum1_i = -sum2_j + j * sum1_j$

发现可以使用斜率优化，即

$x = j$   
$y = -sum2_j + j * sum1_j$   
$k = sum1_i$   
$b = v_{i, j} - sum2_i$

$x,y$是单调递增的   

所以直接维护上凸壳来找到第一个斜率大于$sum1_i$的即为在当前i的dp值。最终答案就是最大的dp值

```
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10;
long long a[N], num1[N], num2[N], ans;
int n;
int st[N], num;
#define x(i) (i)
#define y(i) ((long long)(i) * num1[i] - num2[i])
long long gk(int i, int j)
{
	return (y(i) - y(j)) / (x(i) - x(j));
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%lld", &a[i]);
		num1[i] = num1[i - 1] + a[i];
		num2[i] = num2[i - 1] + a[i] * (long long)i;
	}
	for (int i = 1; i <= n; ++ i)
	{
		int l = 0, r = num;
		for (; l < r;)
		{
			int mid = (l + r) >> 1;
			if(gk(st[mid], st[mid + 1]) > num1[i])
				l = mid + 1;
			else r = mid;
		}
		ans = max(ans, num2[i] - num2[st[l]] - (long long)st[l] * (num1[i] - num1[st[l]]));
		while(num >= 1 && gk(st[num - 1], st[num]) < gk(st[num], i))-- num;
		st[++ num] = i;
	}
	printf("%lld\n", ans);
}
```


---

## 作者：Fracture_Dream (赞：5)

# 简述题意

给一个长度为$n$ 的序列 $a$ ，选取一个连续子序列$\{a_x,a_{x+1},\dots ,a_{x+k-1}\}$ 使得$\sum_{i=1}^k i\cdot a_{x+i-1}$ 最大。

- $1\leq n\leq 2\times 10^5,|a_i|\leq 10^7$ 

# 思路
对于这种下标乘权值的式子，一般都会进行以下处理：
令 $pre1$ 表示 $a_i$ 的前缀和，$pre2$ 表示 $a_i \times i$ 的前缀和，那么一个子序列 $[i,j]$ 的价值即为：

$$w(i,j) = pre2_i - pre2_{j-1} - (j - 1) \times (pre1_i - pre1_{j-1})$$

不妨令 $dp_i$ 表示以 $i$ 结尾的子序列中的最大价值，显然有：

$$dp_i = \max\{(j-1) \times pre1_{j-1}-pre2_{j-1}-(j-1) \times pre1_i\}+pre2_i$$

这个式子很显然是可以斜率优化的。按照套路，把与 $j$ 无关的归到等式左边，$i \times j$ 形式的看成 $k \times x$，只与 $j$ 有关的就是 $x,y$。
那么可得：
$b = dp_i-pre2_i,k=pre1_i,x=j-1,y=(j-1) \times pre1_{j-1} - pre2_{j-1}$

将 $j$ 视为坐标为 $(x,y)$ 的点，由于我们要最大化截距 $b$，所以维护上凸包（斜率单减）即可。
对于一般的斜率优化，单调队列即可。但是注意到，此题虽然 $x$ 单增，但是 $k$ 不一定是单调的（$a_i$ 有负数），所以可以用二分/平衡树/CDQ/李超线段树解决。

~~当然肯定挑简单的二分写。~~ 

# 代码
如果你 $\text{Wrong answer on test 6}$，注意子序列左端不能为 $0$。
如果你 $\text{Wrong answer on test 47}$，注意初始答案为 $\max\{a_1,a_2,a_3,...,a_n\}$，因为可以只选一个元素。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e6 + 5;
int n , pre1[MAXN] , pre2[MAXN] , a[MAXN] , q[MAXN] , head = 1 , tail , ans;
int w(int l , int r) {return pre2[r] - pre2[l - 1] - (l - 1) * (pre1[r] - pre1[l - 1]);}
int X(int i) {return i - 1;}
int Y(int i) {return (i - 1) * pre1[i - 1] - pre2[i - 1];}
long double Slope(int a , int b) {return (Y(a) - Y(b)) * 1.0 / (X(a) - X(b));}
int Find(int x) {
	if (head > tail) return 0;
	int l = head , r = tail;
	while(l < r) {
		int mid = l + r + 1 >> 1;
		if (Slope(q[mid - 1] , q[mid]) >= pre1[x]) l = mid;
		else r = mid - 1;
	}
	return q[l];
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	cin >> n;
	for (int i = 1 ; i <= n ; i ++) {
		cin >> a[i];
		ans = max(ans , a[i]);
		pre1[i] = pre1[i - 1] + a[i] , pre2[i] = pre2[i - 1] + i * a[i];
	}
	for (int i = 1 ; i <= n ; i ++) {
		int j = Find(i);
		if (j) ans = max(ans , w(j , i));
		while(head < tail && Slope(i , q[tail]) >= Slope(q[tail] , q[tail - 1])) tail --;
		q[++ tail] = i;
	}
	cout << ans;
    return 0;
}
```

---

## 作者：周小涵 (赞：3)

为了方便，先将序列翻转，设 $s_i = \sum_{j=1}^{i}{a_j}$，那么枚举区间的右端点 $i$，那么对于一个左端点 $i$，设 $t_x=\sum_{k=x+1}^{i}s_k$，那么这个区间的权值就是 $t_{x+1}-(i-x)s_x$，我们把每个 $x$ 看成一个 $k=-s_x,b=t_{x+1}+xs_x$ 的线段，李超线段树维护最值即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
const ll INF=1e18;
int n,a[N],t[N<<2];
ll s[N],k[N<<2],b[N<<2],tag;
ll calc(int p,int x){
    if(p==-1)return -INF;
    return k[p]*x+b[p]+tag;
}
void change(int p,int l,int r,int v){
    if(calc(t[p],l)<calc(v,l)&&calc(t[p],r)<calc(v,r))return t[p]=v,void();
    if(calc(t[p],l)>=calc(v,l)&&calc(t[p],r)>=calc(v,r))return;
    if(l==r)return;int mid=l+r>>1;
    change(p<<1,l,mid,v);change(p<<1|1,mid+1,r,v);
}
ll ask(int p,int l,int r,int x){
    if(l==r)return calc(t[p],x);
    int mid=l+r>>1;ll ret=calc(t[p],x);
    if(x<=mid)ret=max(ret,ask(p<<1,l,mid,x));
    else ret=max(ret,ask(p<<1|1,mid+1,r,x));
    return ret;
}
int main(){
    memset(t,-1,sizeof(t));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    reverse(a+1,a+n+1);
    for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
    ll ans=0;k[0]=0;b[0]=0;
    change(1,0,n,0);
    for(int i=1;i<=n;i++){
        tag+=s[i];
        ans=max(ans,ask(1,0,n,i));
        k[i]=-s[i];b[i]=i*s[i]-tag;
        change(1,0,n,i);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Melo_DDD (赞：2)

当时 lxl 上课讲的题，现在终于会了斜率优化，补一补。

首先我们发现原式需要 $\Theta(1)$ 求，所以用类似前缀和的东西搞一下，规定：

$$
sum_i=\sum_{j=1}^{i}a_j,s_i=\sum_{j=1}^{i}j\times a_j
$$

那么原式可以简化为：
$$val(j,i)=s_i-s_{j-1}-(j-1)\times(sum_i-sum_{j-1})$$

上面这个展开一下就知道为什么了。

很显然的，我们不妨设 $dp_i$ 表示 $\displaystyle\max_{j=1}^{i-1}val(j,i)$，最终的答案需要对所有 $dp_i$ 取最大值。

即：$dp_i=\max\{s_i-s_{j-1}-(j-1)\times(sum_i-sum_{j-1})\}(j\in[1,i-1])$，这个一看就可以斜率优化。

式子可以变化为：

$$dp_i-s_i=\max\{-s_{j-1}-(j-1)\times sum_i+(j-1)\times sum_{j-1}\}$$

符合斜率优化的形式，其中 $b=dp_i-s_i$、$k=sum_i$、$x=j-1$、$y=-s_{j-1}+(j-1)\times sum_{j-1}$，目标转化为求 $b$ 的最大值。

可以看出 $x$ 单增，所以维护凸壳的时候不需要平衡树什么的，当然你想用也没问题。

考虑几何意义，我们对于每个位置 $i$ 按照上述方式找到一个点 $(x_i,y_i)$ 代表他，那么求最大的 $b$ 的过程可以看做：刚开始截距无限大，逐渐把这个图像向下移动，直到有一个点在图像上，这个时候就找到最大的 $b$ 了。

根据上面的过程可以发现，每次找到的点一定在当前点集的上凸壳上，用单调栈维护即可。

如果暴力遍历的话仍然不可接受，可以用李超线段树或者 cdq 来降低复杂度，但是我不会，所以用二分。

这个单调性好像并没有这么显然。

考虑何时选取点 $i$ 比选点 $i-1$ 得到的 $b$ 更优，可以有式子 $y_i-k\times x_i>y_{i-1}-k\times x_{i-1}$，不难得到 $\frac{y_i-y_{i-1}}{x_i-x_{i-1}}>k$，即点 $i$ 和 $i-1$ 位于的那条直线的斜率比 $k$ 更大。

我们发现上凸壳具有一个美好的性质，就是上面的线从左到右斜率严格单减，那么可以二分求得上凸壳上最后一个满足条件的点 $ans$ 就是最优的了。

为了避免使用浮点数导致的精度损失，我没有使用除法，移项就可以了。

代码：


```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = - x : 0 ;
}
using ll = long long ;
const int N = 2e5 + 7 ;
int n ,stk[N] ,stop ; ll a[N] ,ans ,sum[N] ,s[N] ;
struct point { 
	ll x ,y ;
	inline ll cross (const point &a) {
		return x * a.y - a.x * y ;
	} // 向量叉积
	point () { x = 0 ,y = 0 ;} // 没用
} p[N] ;
inline point operator - (const point &a ,const point &b) {
	point t ;
	t.x = a.x - b.x ,t.y = a.y - b.y ;
	return t ;
}
namespace melo { 
	inline int bin (int L ,int R ,ll k) {
		if (L > R) return 0 ;
		int l = L + 1 ,r = R ,ans = 1 ;
		while (l <= r) {
			int mid = l + r >> 1 ;
			point t = p[stk[mid]] - p[stk[mid - 1]] ;
			if (t.y > k * t.x) {
				ans = mid ;
				l = mid + 1 ;
			} else r = mid - 1 ;
		}
		return stk[ans] ;
	} // 千万记住是在 stk 数组里查找
	inline void convhull () {
		f (i ,1 ,n ,1) {
			int loc = bin (1 ,stop ,sum[i]) ; // sum[i] 是斜率
			ans = std :: max (ans ,p[loc].y - sum[i] * p[loc].x + s[i]) ; // 别忘了求出来的 b 加上 s[i] 才是我们想要的
			p[i].x = i - 1 ,p[i].y = - s[i - 1] + (i - 1) * sum[i - 1] ;  
			while (stop >= 2 && 
			(p[i] - p[stk[stop]]).cross (p[stk[stop]] - p[stk[stop - 1]]) <= 0) stop -- ;
			stk[++ stop] = i ; // 维护上凸壳
		}
	}
}
int main () {
	read (n) ;
	f (i ,1 ,n ,1) {
		read (a[i]) ;
		ans = std :: max (ans ,a[i]) ; // 我们没有考虑只取一个点的情况，所以提前预处理
		sum[i] = sum[i - 1] + a[i] ;
		s[i] = s[i - 1] + (ll) i * a[i] ;
	}
	melo :: convhull () ;
	std :: cout << ans << '\n' ;
	return 0 ;
}
// 由样例 3 可知是可以不选的，所以 ans 初始化成 0 而不是 - inf
```

---

## 作者：Hoks (赞：2)

## 前言
lxl 上课讲的题，还是补个题解吧。

有点难写。
## 思路分析
首先看题目的式子，发现这个式子非常复杂，甚至是带乘法的。

考虑把这个式子优化一下，优化成能 $O(1)$ 计算的。

令 $s1_i=\sum\limits_{j=1}^i a_j$，$s2_i=\sum\limits_{j=1}^i j\cdot a_j$ 。

那么区间 $l,r$ 的答案 $ans_{l,r}$ 即为 $s2_r-s2_{l-1}-(l-1)\cdot(s1_r-s1_{l-1})$。

接着我们就是要求这个东西的最大值。

考虑 dp，令 $f_i$ 为 $r=i$ 的最大值。

那么就可以得到正常的方程式：
$$f_i=\max(ans_{j,i})$$
这样显然是 $O(n^2)$ 的，考虑来优化这个东西。

因为含有乘法，所以来考虑斜率优化。

把前面的那个式子拆开：

$$s2_r-s2_{l-1}-(l-1)\cdot s1_r+(l-1)\cdot s1_{l-1}$$

因为枚举的是 $i$ 也就是 $r$，所以 $r$ 与斜率无关，直接扔掉，重新整理得：

$$s2_r-s1_r\cdot(l-1)+(l-1)\cdot s1_{l-1}-s2_{l-1}$$

这下形式就出来了，$y=s2_r,k=s1_r,x=l-1,b=(l-1)\cdot s1_{l-1}-s2_{l-1}$。

接着维护下这个上凸壳就行了？

发现 $a_i$ 有负数，所以 $k$ 不单调，这个时候就要二分/CDQ/李超线段树了。

因为我傻所以我用李超，用李超线段树要记得把 $k,x$ 翻转下。

如果和我一样用板子的记得把 double 改掉，不然会精度误差。
## 代码
```cpp
#include<bits/stdc++.h>
#define get(x) (lower_bound(b+1,b+1+m,x)-b)
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,ans,a[N],b[N],s[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
struct Li_Chao_Segment_Tree
{
    #define ls (p<<1)
    #define rs (ls|1)
    #define mid ((l+r)>>1)
    const int eps=1e-9;
    struct line{int k,b;line(){k=b=0;}};
    vector<line>l;vector<int>t;int L,R,tot;
    void init(int s,int e){L=s,R=e;t=vector<int>((e-s+10)<<2);l=vector<line>((e-s+10)<<2);}
    int calc(int u,int x){return l[u].k*b[x]+l[u].b;}
    void mdf(int p,int l,int r,int x)
    {
        if(p==1) l=L,r=R;
        if(l==r){if(calc(x,l)>calc(t[p],l)) t[p]=x;return;}
        if(calc(x,mid)>calc(t[p],mid)) swap(t[p],x);
        if(calc(x,l)>calc(t[p],l)) mdf(ls,l,mid,x);
        if(calc(x,r)>calc(t[p],r)) mdf(rs,mid+1,r,x);
    }
    int query(int p,int l,int r,int x)
    {
        if(p==1) l=L,r=R;int res=calc(t[p],x);if(l==r) return res;
        if(x<=mid) return max(res,query(ls,l,mid,x));
        return max(res,query(rs,mid+1,r,x));
    }
    #undef ls
    #undef rs
    #undef mid
}sgt;
inline void solve()
{
    n=read();for(int i=1,x;i<=n;i++) b[i]=a[i]=a[i-1]+(x=read()),s[i]=s[i-1]+i*x;
    sort(b+1,b+1+n);m=unique(b+1,b+1+n)-b-1;sgt.init(1,m);sgt.l[0].b=-INF;
    for(int i=1;i<=n;i++)
    {
        sgt.l[i].k=1-i,sgt.l[i].b=a[i-1]*(i-1)-s[i-1];
        sgt.mdf(1,0,0,i);ans=max(ans,sgt.query(1,0,0,get(a[i]))+s[i]);
    }print(ans);
}
signed main()
{
    int T=1;while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：_cyle_King (赞：2)

# CF660F 题解

## 题意

定义一个长度为 $m$ 的序列 $b$ 的价值为 $\sum^m_{i=1}ib_i$，给出一个序列 $a$，长度为 $n$，求 $a$ 的所有连续子序列的最大价值。

#### 数据范围

$1\leq n\leq2\times10^5,1\leq |a_i|\leq10^7$

## 分析

### 推式子

考虑以 $i$ 结尾的连续子序列的价值 $ans_i$。

默认 $a_0=0$，设 $sum_i=\sum^i_{j=0}a_j$，假设现在已经考虑的连续子序列开头是 $j$。再向左扩展一个，就加上 $sum_i-sum_{j-2}$ 的价值。可以发现以 $j$ 开头，以 $i$ 结尾的连续子序列的价值为:
$$
(i-j+1)sum_i-\sum^{i-1}_{k=j-1}sum_k
$$
用数学归纳法不难证明，理解起来应该也不难吧。

于是维护 $sum$ 的前缀和，设 $s_i=\sum^i_{j=0}sum_i$。则上述式子可化为
$$
(i-j+1)sum_i-(s_{i-1}-s_t)
$$
其中 $t=\max\{j-2,0\}$。

于是 
$$
ans_i=\max_{1\leq j\leq i}\{(i-j+1)sum_i-sum(s_{i-1}-s_t)\}
$$
显然是 $O(n)$ 的，枚举每一个 $i$，时间复杂度为 $O(n^2)$，过不去。

### 优化

那个式子非常有斜率优化的感觉。将 $\max$ 函数拆开，移项可变为
$$
(j-1)sum_i+ans_i+s_{i-1}-isum_i=s_t
$$
则有
$$
\begin{aligned}
x=(j-1),y=s_t\\
k=sum_i,b=ans_i+s_{i-1}-isum_i
\end{aligned}
$$
就是斜率优化的板子题了，取最大值维护一个上凸壳即可。注意到斜率 $k$ 单调但是 $y$ 不单调，需要在单调栈内二分第一个斜率小于 $k$ 的位置。

时间复杂度 $O(n\log n)$。

### Code

```cpp
#include<bits/stdc++.h>

#define rep(i,x,y) for(int i=(x), _=(y); i<=_; i++)
#define per(i,x,y) for(int i=(x), _=(y); i>=_; i--)

using namespace std;
template <class T1, class T2>inline bool cmax(T1 &a, T2 b) {return a < b ? a = b, 1 : 0;}
template <class T1, class T2>inline bool cmin(T1 &a, T2 b) {return b < a ? a = b, 1 : 0;}
typedef pair<int, int> pii;
typedef pair<int, long long> pil;
typedef pair<long long, int> pli;
typedef pair<long long, long long> pll;
typedef long long LL;

const int N = 2e5 + 10;
const LL Inf = 0x3f3f3f3f3f3f3f3f;

int n, a[N + 1];
LL sum[N + 1], s[N + 1];
int stac[N + 1], top;

inline double
slope(int i, int j) {
	return double(s[max(i - 1, 0)] - s[max(j - 1, 0)]) / (i - j);
}

inline LL
calc(int i, int j) {
	return (i - j) * sum[i] - s[max(i - 1, 0)] + s[max(j - 1, 0)];
}

int
main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) sum[i] = sum[i - 1] + a[i];
	rep(i, 1, n) s[i] = s[i - 1] + sum[i];
	LL ans = max(0ll, sum[1]);
	stac[++ top] = 0, stac[++ top] = 1;
	rep(i, 2, n) {
		int l = 1, r = top, mid, res = stac[top];
		while(l <= r) {
			mid = (l + r) >> 1;
			double slp = slope(stac[mid], stac[mid + 1]);
			if(slp <= sum[i]) res = stac[mid], r = mid - 1;
			else l = mid + 1;
		}
		LL temp = calc(i, res);
		cmax(ans, temp);
		while(top > 1 && slope(stac[top - 1], stac[top]) <= slope(stac[top], i)) top --;
		stac[++ top] = i;
	}
	cout << ans << endl;
	return 0;
}

```







# End















---

## 作者：_Aurore_ (赞：1)

## 题目描述

给一个长度为 $n$ 的序列,第 $i$ 个数是 $a_i$，选取一个连续子序列 $\{a_x,a_{x+1},\dots ,a_{x+k-1}\}$ 使得 $\sum_{i=1}^k i\cdot a_{x+i-1}$ 最大。

其中 $1\leq n\leq 2\times 10^5,|a_i|\leq 10^7$ 

## 思路点拨

考虑一个区间 $[l,r]$ 的贡献：

$$\sum_{i=l}^r a_i \times (i-l+1)=\sum_{i=l}^r ia_i +(1-l)\sum_{i=l}^r a_i$$

我们令 $A_i=\sum_{i=1}^i a_i$,$B_i = \sum_{i=1}^i ia_i$。那么答案就是：

$$(B_r-B_{l-1})+(1-l)(A_r-A_{l-1})$$

现在，我们考虑暴力的求解，也就是 $O(n^2)$ 枚举左端点，那么对于一个右端点 $r$:

$$\max_{i=1}^r\{B_r-B_{l-1}+(1-l)(A_r-A_{l-1})\}$$

对于这个 $(B_r-B_{l-1})+(1-l)(A_r-A_{l-1})$ 而言，$B_r$ 是常数，我们不考虑，所以答案：

$$B_r+\max_{i=1}^r\{-B_{l-1}+(1-l)(A_r-A_{l-1})\}$$

我们考虑一个一次函数 $kx+b$，对应到式子就是

$k=(1-l),b=-B_{l-1}-(1-l)A_{l-1},x=A_r$ 

所以可以使用李超线段树维护。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	} 
	return x*f;
} 
const int MAXN=3e5+10;
int n,sum[MAXN],a[MAXN],b[MAXN],t[MAXN<<2];
struct node{
	int k,b;
}p[MAXN];
int fun(int pos,int x){
	if(!pos) return -1e15;
	return p[pos].k*sum[x]+p[pos].b;
}
void update(int i,int l,int r,int k){
	if(!k) return ;
	if(l==r){
		if(fun(t[i],l)<fun(k,l))
			swap(t[i],k);
		return ;
	}
	int mid=l+r>>1;
	if(fun(t[i],mid)<fun(k,mid)) swap(t[i],k);
	if(fun(t[i],l)<fun(k,l)) update(i<<1,l,mid,k);
	if(fun(t[i],r)<fun(k,r)) update(i<<1|1,mid+1,r,k);
}
int query(int i,int l,int r,int k){	
	if(r<k||l>k||!t[i]) return -1e15; 
	if(l==r) return fun(t[i],k);
	int mid=l+r>>1;
	return max(fun(t[i],k),max(query(i<<1,l,mid,k),query(i<<1|1,mid+1,r,k)));
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		int x=read();
		sum[i]=b[i]=sum[i-1]+x;
		a[i]=a[i-1]+i*x;
	}
	sort(sum+1,sum+n+1);
	int m=unique(sum+1,sum+n+1)-sum-1;
	int ans=0;
	for(int i=1;i<=n;i++){
		int pos=lower_bound(sum+1,sum+m+1,b[i])-sum;
		p[i].k=1-i,p[i].b=(i-1)*b[i-1]-a[i-1];
		update(1,1,m,i);
		ans=max(ans,a[i]+query(1,1,m,pos));
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：wcyQwQ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF660F)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/03/24/CF660F%20Bear%20and%20Bowling%204/)

DP？DS！

首先考虑如何 $O(1)$ 计算每个区间的结果，记 $A_i = \sum_{j = 1}^i j \cdot a_j$，$B_i = \sum_{j = 1}^i a_j$，那么选择 $[l, r]$ 的答案即为
$$
\sum_{i = l}^r (i - l + 1)a_i = \sum_{i = l}^r i \cdot a_i - (l - 1)\sum_{i = l}^r a_i = A_r - A_{l - 1} - (l - 1)(B_r - B_{l - 1})
$$
这样是 $O(n^2)$ 的，于是我们考虑进行数据结构优化。

记 $f_i$ 为以 $a_i$ 为结尾的最大值，那么我们容易得到
$$
f_i = A_i + \max_{j \in [1, i]}\left\{ (1 - j) \cdot B_i + (j - 1)B_{j - 1} - A_{j - 1}\right\}
$$
这很像李超线段树的形式，于是我们令 $k_i = 1 - i$，$b_i = (i - 1)B_{i - 1} - A_{i - 1}$

然后式子就变成了
$$
f_i = A_i + \max_{j \in [1, i]} \left\{k_jB_i + b_j\right\}
$$
直接李超线段树维护最大值即可。

```c++
#include <bits/stdc++.h>
#define L(i, j, k) for(int i = (j); i <= (k); i++)
#define R(i, j, k) for(int i = (j); i >= (k); i--)
#define G(i, u) for (int i = h[(u)]; ~i; i = ne[i])
#define ll long long
#define ld long double
#define ull unsigned long long

using namespace std;
const int N = 2e5 + 10;
const ll INF = 1e18;
ll a[N], b[N], c[N];
struct Func {
    ll k, b;
} line[N];
int s[N << 2];

inline int read() {
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline ll calc(int i, int x) {
    return line[i].k * c[x] + line[i].b;
}

inline void change(int p, int l, int r, int x) {
    if (l == r) {
        if (calc(x, l) > calc(s[p], l)) s[p] = x;
        return;
    }
    int mid = (l + r) >> 1; 
    if (calc(x, mid) > calc(s[p], mid)) swap(x, s[p]);
    calc(x, l) > calc(s[p], l) ? change(p << 1, l, mid, x) : change(p << 1 | 1, mid + 1, r, x);
}

inline ll query(int p, int l, int r, int x) {
    if (l == r) return calc(s[p], x);
    int mid = (l + r) >> 1;
    return max(calc(s[p], x), x <= mid ? query(p << 1, l, mid, x) : query(p << 1 | 1, mid + 1, r, x));
}

int main() {
    int n = read();
    L(i, 1, n) {
        int x = read();
        a[i] = a[i - 1] + 1ll * i * x, b[i] = b[i - 1] + x, c[i] = b[i];
    }
    sort(c + 1, c + n + 1);
    int len = unique(c + 1, c + n + 1) - c - 1;
    line[0].b = -INF;
    ll res = 0;
    L(i, 1, n) {
        int pos = lower_bound(c + 1, c + len + 1, b[i]) - c;
        line[i] = {1 - i, b[i - 1] * (i - 1) - a[i - 1]};
        change(1, 1, len, i);
        res = max(res, query(1, 1, len, pos) + a[i]);
    }
    printf("%lld\n", res);
    return 0;
}
```



---

## 作者：ollo (赞：0)

# 题目大意

给一个长度为 $n$ 的序列，第 $i$ 个数是 $a_i$，选取一个连续子序列 $\{a_x,a_{x+1},\dots ,a_{x+k-1}\}$ 使得 $\sum_{i=1}^k i\cdot a_{x+i-1}$ 最大。

其中$1\leq n\leq 2\times 10^5,|a_i|\leq 10^7$

# 大致思路

考虑如何快速计算这个贡献，观察可得原式等价于 $\sum_{i=l}^r (i-l+1)\cdot a_i$，拆开后有 $\sum_{i=l}^r i\cdot a_i-(l-1)\cdot a_i$。

维护两个前缀数组 $sum1_i=sum1_{i-1}+i\cdot a_i$，$sum2=sum2_{i-1}+a_i$，则原式等价于 $(sum1_r-sum1_{l-1})-(l-1)(sum2_r-sum2_{l-1})$。

考虑钦定右端点 $r$，此时可以将 $sum1_r$ 提出，则我们要找一个左端点 $l$ 满足 $-sum1_{l-1}+(1-l)(sum2_r-sum2_{l-1})$ 最小。不妨考虑一次函数 $y=kx+b$，显然有：

$$
\left\{\begin{matrix} 
   k=1-l\\
   b=-sum1_{l-1}+(1-l)(sum2_r-sum2_{l-1})\\
   x=a_r
\end{matrix}\right. 
$$

李超线段树维护即可，注意要将 $a$ 离散化。

# code

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 10, inf = 1e18;

int n;
int sum[N];
int c[N], b[N];

struct line{
	int k, b;
}li[N];

int tr[N << 2];

int calc(int i, int id){return li[i].k * c[id] + li[i].b;}

void change(int x, int l, int r, int w){
	if(l == r){
		if(calc(w, l) > calc(tr[x], l)) tr[x] = w;
		return ;
	}
	int mid = l + r >> 1;
	if(calc(w, mid) > calc(tr[x], mid)){swap(tr[x], w);}
	if(calc(w, l) > calc(tr[x], l)) change(x << 1, l, mid, w);
	if(calc(w, r) > calc(tr[x], r)) change(x << 1 | 1, mid + 1, r, w);
}

int query(int x, int l, int r, int L){
	if(l == r){return calc(tr[x], L);}
	int mid = l + r >> 1;
	if(L <= mid) return max(calc(tr[x], L), query(x << 1, l, mid, L));
	else return max(calc(tr[x], L), query(x << 1 | 1, mid + 1, r, L));
}

signed main(){
	cin >> n;
	for(int x, i = 1; i <= n; i++) cin >> x, sum[i] = sum[i - 1] + x * i, b[i] = b[i - 1] + x, c[i] = b[i];
	sort(c + 1, c + n + 1);
	int m = unique(c + 1, c + n + 1) - c - 1;
	li[0].b = -inf;int num = 0;
	for(int i = 1; i <= n; i++){
		int id = lower_bound(c + 1, c + m + 1, b[i]) - c;
		li[i] = (line){1 - i, b[i - 1] * (i - 1) - sum[i - 1]};
		change(1, 1, m, i);
		int w = query(1, 1, m, id) + sum[i];
		num = max(num, w);
	}
	cout << num << endl;
	return 0;
}
```

---

## 作者：天命之路 (赞：0)

传送门:[CF660F](https://www.luogu.com.cn/problem/CF660F)

用分治和李超线段树过掉此题的我看着一堆线性做法流下了眼泪。

首先，问题是在序列中选取一段不定长的区间，使得权值最大

对于这种问题，分治其实是个一般性的思路，设 $solve(l,r)$ 表示区间 $[l,r]$ 的答案，我们取 $mid = \frac{l + r}{2}$，则所求可以被化为三部分：

1. 区间 $[l,mid]$ 的答案
2. 区间 $[mid+1,r]$ 的答案
3. 在区间 $[l,r]$ 中，经过点 $mid$ 的区间的答案

显然前两部分可以递归下去，重点在第三部分

我们利用分治框架，以复杂度多个 $\log$ 为代价，给原问题加了个"必须经过点 $mid$ " 的限制，这就是这个方法的原理。

我们考虑把答案按 $mid$ 分成左右两部分

这是我们如果枚举端点，复杂度还是 $\Theta(n^2)$

但注意到只有 $\Theta(r-l)$ 个可能的左半段，$\Theta(r - l)$ 个可能的右半段

不难想到把所有右半段的信息插入一个数据结构，然后对于每个左半段快速寻求答案

设一个右半段的区间和为 $sum$ ，答案为 $ans$

我们对于现在考虑的左半段，其答案为 $ansl$ ,长度为 $len$ ，我们就是要求 $ansl + \max\limits_{sum,ans}(sum \times len + ans)$

如果把每个右半段的 $sum,ans$ 看做一条直线 $y = sum \cdot x + ans$

那每次询问就是查询 $x = len$ 时与各直线交点的最高处

![](https://cdn.luogu.com.cn/upload/image_hosting/0kiwxwm1.png?x-oss-process=image/resize,m_lfit,h_220,w_300)

就像这张图中，红色的直线为 $x = len$ ，$W$ 点就为所求

熟悉李超线段树的朋友都知道，这就是个板子

于是问题解决了

注意线段树的清空问题，建议开个垃圾桶，记录被访问到的节点。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
typedef double db;
int n,a[N];ll sum[N];
/*
先分治，处理出右半边每个端点的 sum 和 ans
那对于左半边每个端点 i,长度为 len ,答案为 ansl ，就是求 ansl + max(sum * len + ans)
对于每个 len 需要十分快速 O(polylog) 的回答询问
如果把一条直线 y = sum * x + ans 加进去，那么答案就是他在 x = len 处的最大值
不，只要凸包就行，很好的 O(nlog^2n)
不对，凸包如果把两个大向量叉起来，就得爆炸，答案可能达到 1e17
李超只需要比较取值，不存在这种事
*/
// struct Vec{
// 	db x,y;
// 	Vec(){}
// 	Vec(const db _x,const db _y):x(_x),y(_y){}
// 	Vec operator + (const Vec &rhs) const { return Vec(x+rhs.x,y+rhs.y);}
// 	Vec operator - (const Vec &rhs) const { return Vec(x-rhs.x,y-rhs.y);}
// 	Vec operator * (const db &rhs) const { return Vec(x*rhs,y*rhs);}
// 	db operator * (const Vec &rhs) const { return this->x*rhs.y-this->y*rhs.x;}
// };
// struct line{
// 	Vec u,v;
// 	db angle;
// 	line(){}
// 	line(const Vec &_u,const Vec &_v):u(_u),v(_v){angle = atan2(_v.y-_u.y,_v.x-_u.x);}
// };
// const db eps = 1e-9,PI = acos(-1.0);
// inline int dcmp(const db &a,const db &b)
// {
// 	if(fabs(a - b) < eps)
// }
long long K[N],B[N],tot;
int tag[N << 2];
int bac[N << 5],baccnt = 0;
inline ll calc(int i,int x) { return K[i] * x + B[i];}
#define ls k<<1
#define rs k<<1|1
void change(int k,int l,int r,int x)
{
	bac[++baccnt] = k;
	if(l == r)
	{
		if((calc(tag[k],l) < calc(x,l))) tag[k] = x;
		return;
	}
	if(!tag[k]) tag[k] = x;
	else
	{
		int mid = l + r >> 1;
		ll y1 = calc(tag[k],mid),y2 = calc(x,mid);
		if(K[tag[k]] < K[x])
		{
			if(y1 <= y2) { change(ls,l,mid,tag[k]);tag[k] = x;}
			else change(rs,mid+1,r,x);
		}
		else if(K[tag[k]] > K[x])
		{
			if(y1 <= y2) { change(rs,mid+1,r,tag[k]);tag[k] = x;}
			else change(ls,l,mid,x);
		}
		else if(B[tag[k]] < B[x]) tag[k] = x;

	}
}
ll Qry(int k,int l,int r,int x)
{
	if(l == r) return calc(tag[k],x);
	int mid = l + r >> 1;
	ll res = calc(tag[k],x);
	if(x <= mid) res = max(res,Qry(ls,l,mid,x));
	else res = max(res,Qry(rs,mid+1,r,x));
	return res;
}
inline void clear()
{
	while(baccnt) tag[bac[baccnt --]] = 0;
}
ll solve(int l,int r)
{
	if(l == r) return max(0,a[l]);
	int mid = l + r >> 1;
	ll res = max(solve(l,mid),solve(mid+1,r));
	tot = 0;
	ll nowsum = 0,nowans = 0;
	++tot;K[tot] = 0;B[tot] = 0;
	change(1,1,n,tot);
	for(int i = mid + 1;i <= r;i++)
	{
		nowsum += a[i];
		nowans += 1ll * (i - mid) * a[i];
		++tot;K[tot] = nowsum;B[tot] = nowans;
		// if(l == 1 && r == n) printf("%lld,%lld\n",nowsum,nowans);
		change(1,1,n,tot);
	}
	nowsum = 0;nowans = 0;
	for(int i = mid;i >= l;i--)
	{
		int len = mid - i + 1;
		nowans += sum[mid] - sum[i - 1];
		res = max(res,nowans + Qry(1,1,n,len));
	}
	clear();
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]),sum[i] = sum[i-1] + a[i];
	printf("%lld\n",solve(1,n));
	return 0;
}
```


---

