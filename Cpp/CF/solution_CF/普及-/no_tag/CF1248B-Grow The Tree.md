# Grow The Tree

## 题目描述

Gardener Alexey teaches competitive programming to high school students. To congratulate Alexey on the Teacher's Day, the students have gifted him a collection of wooden sticks, where every stick has an integer length. Now Alexey wants to grow a tree from them.

The tree looks like a polyline on the plane, consisting of all sticks. The polyline starts at the point $ (0, 0) $ . While constructing the polyline, Alexey will attach sticks to it one by one in arbitrary order. Each stick must be either vertical or horizontal (that is, parallel to $ OX $ or $ OY $ axis). It is not allowed for two consecutive sticks to be aligned simultaneously horizontally or simultaneously vertically. See the images below for clarification.

Alexey wants to make a polyline in such a way that its end is as far as possible from $ (0, 0) $ . Please help him to grow the tree this way.

Note that the polyline defining the form of the tree may have self-intersections and self-touches, but it can be proved that the optimal answer does not contain any self-intersections or self-touches.

## 说明/提示

The following pictures show optimal trees for example tests. The squared distance in the first example equals $ 5 \cdot 5 + 1 \cdot 1 = 26 $ , and in the second example $ 4 \cdot 4 + 2 \cdot 2 = 20 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248B/7db20a2c52bb98904e15a368693f20c8c6e11756.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248B/f37e132abb11c10bbc7a671b08b806fa38567869.png)

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
26```

## 样例 #2

### 输入

```
4
1 1 2 2
```

### 输出

```
20```

# 题解

## 作者：Meatherm (赞：6)

样例中已经给的很明显了。我们要 $X^2+Y^2$ 尽可能大，那么一定不会让 $X$ 更接近 $Y$ 而是让 $X$ 或 $Y$ 尽可能大。

那么就是一个很简单的问题了。

我们将数组的前半部分之和作为 $X$，将后半部分之和作为 $Y$。容易发现这样 $X^2+Y^2$ 一定最大。

```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N=100010;
int a[N];
int n;
signed main(void){
	scanf("%I64d",&n);
	for(rr int i=1;i<=n;++i){
		scanf("%I64d",&a[i]);
	}
	std::sort(a+1,a+1+n);
	int cnta=0,cntb=0;
	for(rr int i=1;i<=n/2;++i){
		cnta+=a[i];
	}
	for(rr int i=n/2+1;i<=n;++i){
		cntb+=a[i];
	}
	printf("%I64d",cnta*cnta+cntb*cntb);
	return 0;
}
```

---

## 作者：Teal_ (赞：2)

## $CodeForces \ 1248B$

本题意思其实十分明确，就是要你构造一个三角形，使得斜边最大

大概先感性理解，会想到类如什么“正方形对角线、三角形三边关系、正余弦定理……”

然后再思考本题，可以发现，三角形两短边之和已经确定，所以考虑用三角形三边关系来做

下面给出一个引理：
#### 对于一个三角形，其两边之和一定大于第三边
设最终点为 $(A, B)$

则有 $A + B > C$

其中 $Sum(A, B)$ 为定值

则当三角形锐角 $\alpha \rightarrow 0$ 时， $C \rightarrow Sum(A, B)$

![CF1248B](https://cdn.luogu.com.cn/upload/image_hosting/t0u3rywv.png)

可知为使 $\{A, B \}$ 中一边最大，应使 $Max(Sum_X - Sum_Y)$

所以我们可以先对木棍排序，每次交替使用第一个和最后一个，使差值最大

用一个指针实现就可以了，注意一下最后一根木棍，因为偶数和奇数根木棍放下来，最后一根木棍是竖着还是横着使不一样的

##### $Code \ for \ CF1248B$

```cpp
#include <set>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define inf (0x3f3f3f3f)
#define N (100010)
#define int long long
const int mod = 1e9 + 7;
int n, a[N], x, y;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		ch == '-' ? f = -1, ch = getchar() : ch = getchar();
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}

signed main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);
	int itL = 1, itR = n;
	while (itL <= itR) {
		x += a[itL++];
		y += a[itR--];
	}
	if (n & 1) x -= a[(n + 1) / 2];
	printf("%lld\n", x * x + y * y);
	return 0;
}

```


---

## 作者：Loser_Syx (赞：0)

## 思路

这题其实很淼，要求问最后一条木棍的终点距离 $(0,0)$ 点最远的距离的平方最大是多少，其实就是要让直角三角形斜边的平方最大，如何让直角三角形的斜边的平方最大呢？就是要使两条直角边的平方加起来最大，要使平方和最大，这里只需要让其中一条边最长就可以了。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
#define int long long//不开longlong见祖宗
int a[114514];
main(){
    int n;
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    std::sort(a + 1, a + 1 + n);//排序，然后从小到大加
    int x = 0, y = 0;//x是最短的那条，y是最长的那条
    for(int i = 1; i <= n / 2; i++){
        x += a[i];
    }
    for(int i = n / 2 + 1; i <= n; i++){
        y += a[i];
    }
    printf("%lld", x * x + y * y);
    return 0;
}
```

[记录](https://www.luogu.com.cn/record/101776189)

---

## 作者：tommychen (赞：0)

### 题面
[洛谷题面](https://www.luogu.com.cn/problem/CF1248B)

[CF题面](https://codeforces.ml/contest/1248/problem/B)

### 题意
给定 $n$ 根木条，从 $(0,0)$ 点开始，将这些木条组成折线，求最后一根木条到$(0,0)$点的最远距离。

### 思路
要使得最后一根木条的 $x^2$ 和 $y^2$ 之和最大，也就是让直角三角形斜边的平方最大，而直角三角形中斜边的平方又等于什么呢？ 等于两条直角边的平方（勾股定理）。

由此，我们仅仅需要构造出直角三角形中两条直角边，使得他们平方的和最大即可。

现在，我们只要将 $n$ 条木条两组，让他们的差值最大，平方和也就最大。（当两个数和不变时，两数差越大，平方和越大）。

现在只要将 $n$ 条木条从小到大排序，输出先一半的平方加后一半的平方和即可。
### 代码
一定要开 `long long`!
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
using namespace std;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//MessageBox(GetForegroundWindow(),"标题","内容",MB_YESNO);
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int sum=0,ans=0;
	int tot=n/2;
	for(int i=1;i<=tot;i++){
		sum+=a[i];
	}
	for(int i=tot+1;i<=n;i++){
		ans+=a[i];
	}
	cout<<sum*sum+ans*ans<<endl;
	return 0;
}

```


---

## 作者：夙愿扬 (赞：0)

### CF1248B

有$n$个木棍，从$(0,0)$点开始，每次你可以选一根木棍平行于$x$轴或$y$轴的摆，但不能有连续两个或以上的木棍是选择同一状态的（只能横竖横竖或竖横竖横地摆）。每次木棍摆的起始位置是上一根木棍的结束位置，问最后一条木棍的终点距离$(0,0)$点最远的距离的平方最大是多少。

###### 这是一道比较经典的数学问题（
首先我们发现无论这几根木棍怎么摆，总长度一定是相等的，在这个前提下，我们要求出的最大值是将这些木棍分为两组，这两组的和的平方的和。因为无论怎么分，都可以将摆的木棍平移，使所有的木棒成为一个没有斜边的直角三角形，而我们就要使斜边的长度最大，就要用到一个数学推论：
- 对于$a+b=k(k$为定值$)$，要使$(a^2+b^2)$尽可能大，则$|a-b|$尽可能小。

这样的话，我们只需要将最短的$\lfloor \frac{n}{2} \rfloor$个木棍放在一条边，最长的$\lceil \frac{n}{2} \rceil$个木棍放在一条边，这样就能保证斜边最大。

代码记得排序然后注意一下上下取整（~~其实不需要~~），对了！还要介绍一个函数：

~~sort（误~~
```
pow(x,a);
```
其中$x$为底数，$a$为指数，可计算出$x^a$的值。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100010],tot=0,ans=0;
signed main ()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    scanf("%lld",&a[i]);
    sort(a+1,a+1+n);
    for(int i=1;i<=n/2;i++)
    ans+=a[i];
    tot+=pow(ans,2);
    ans=0;
    for(int i=n/2+1;i<=n;i++)
    ans+=a[i];
    tot+=pow(ans,2);
    printf("%lld",tot);
    return 0;
}
```
##### The End--2019/10/24 21:03

---

## 作者：小元勋 (赞：0)

- 可以直接跟着题意模拟。

- 要使最终的$x^{2}+y^{2}$最大，因为$x,y$方向上的增加必须交替进行。所以我们可以每次使$x$加上当前序列中最大的数，$y$加上最小的数，这样最后得到的答案是最优的，为什么呢$?$

- 假设我们已经求出了答案$x^{2}+y^{2}$，且$x>=y$，而我们可以调整两条边使得答案变为：

 $$(x+1)^{2}+(y-1)^{2}=x^{2}+y^{2}+2(x-y+1)$$
 
- 由于$x>=y$，所以这样调整之后会更优，调整到不能调整就是最优。

- 时间复杂度$O(n\log{n})$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL int

int n,xx;
long long x,y;

inline LL read_() {
	LL x_=0,f_=1;char c_=getchar();
	while(c_<'0'||c_>'9') {if(c_=='-') f_=-1;c_=getchar();}
	while(c_>='0'&&c_<='9') {x_=(x_<<1)+(x_<<3)+c_-'0';c_=getchar();}
	return x_*f_;
}

multiset < int > a;
multiset < int > :: iterator it;

void readda_() {
	n = read_();
	for(int i = 1;i <= n;++i) {
		xx = read_();
		a.insert(xx);
	}
	int cnt = 0;
	x = 0;y = 0;
	while( ! a.empty() ) {
		++cnt;
		if( cnt & 1 ) {
			it = a.end();
			--it;
			xx = * it;
			x += (long long ) xx;
			a.erase( a.find( xx ) );
		}
		else {
			it = a.begin();
			xx = * it;
			y += (long long) xx;
			a.erase( a.find( xx ) );
		}
		cnt %= 2;
	}
	printf("%lld", x * x + y * y);
}

int main() {
//	freopen("a.txt","r",stdin);
	//freopen("ac.txt","w",stdout);
	readda_();
	return 0;
}
```
 

---

## 作者：yizr_cnyali (赞：0)

感性理解,当直角三角形的直角边之和一定时,它们的差越大则斜边越长。    
因此,可以考虑贪心:给木棍按长度排序,取前50%作为平行y轴的直角边,另外50%作为平行x轴的直角边,此时,平行x轴的直角边与平行y轴的直角边的长度之差达到最大
```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define mp make_pair
 
using namespace std;
 
typedef long long LL;
typedef pair<int, int> pii;
 
template <typename T> inline int Chkmax (T &a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline int Chkmin (T &a, T b) { return a > b ? a = b, 1 : 0; }
 
template <typename T> inline T read(){
    T sum = 0;
    int fl = 1,ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') fl = -1;
    for(; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + ch - '0';
    return sum * fl;
}
 
const int maxn = 100000 + 5;
 
int n;
int a[maxn];
 
inline void Solve (){
	sort(a + 1,a + n + 1);
	int x = 0,y = 0;
	for(int i = 1; i <= n / 2; i++){
		y += a[i];
	}
	for(int i = n / 2 + 1; i <= n; i++){
		x += a[i];
	}
	printf("%lld\n",x * x + y * y);
}
 
inline void Input (){
	n = read<int>();
	for(int i = 1; i <= n; i++){
		a[i] = read<int>();
	}
}
 
signed main(){
	Input();
	Solve();
	return 0;
}
```


---

