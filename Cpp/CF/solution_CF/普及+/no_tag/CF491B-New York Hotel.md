# New York Hotel

## 题目描述

Think of New York as a rectangular grid consisting of $ N $ vertical avenues numerated from $ 1 $ to $ N $ and $ M $ horizontal streets numerated $ 1 $ to $ M $ . $ C $ friends are staying at $ C $ hotels located at some street-avenue crossings. They are going to celebrate birthday of one of them in the one of $ H $ restaurants also located at some street-avenue crossings. They also want that the maximum distance covered by one of them while traveling to the restaurant to be minimum possible. Help friends choose optimal restaurant for a celebration.

Suppose that the distance between neighboring crossings are all the same equal to one kilometer.

## 样例 #1

### 输入

```
10 10
2
1 1
3 3
2
1 10
4 4
```

### 输出

```
6
2
```

# 题解

## 作者：EternalHeart1314 (赞：8)

### [题目传送门](https://www.luogu.com.cn/problem/CF491B)

# 题意

有 $c$ 个酒店和 $h$ 个餐馆，要求选择其中一个餐馆，使与这个餐馆最远的酒店离它最近。

# 思路

对于每个餐馆，离它最远的酒店一定是在最左下方或最左上方或最右下方或最右上方（~~有点绕~~）。

假设酒店在 $(a, b)$，餐馆在 $(x, y)$，则：

+ 如果酒店在餐馆的左下方，即 $a < x, b < y$，两点间的距离为 $x - a + y - b$。

+ 如果酒店在餐馆的左上方，即 $a < x, b > y$，两点间的距离为 $x - a + b - y$。

+ 如果酒店在餐馆的右下方，即 $a > x, b < y$，两点间的距离为 $a - x + y - b$。

+ 如果酒店在餐馆的右上方，即 $a > x, b > y$，两点间的距离为 $a - x + b - y$。

+ 如果酒店就在餐馆，即 $a = x, b = y$，取上面任意一种情况都可以。


而这四个最角上的酒店一直都不会变，所以把这四个角的酒店求出来后扫一遍所有的餐馆求出最小值即可。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m, c, h, x, y, mi = 1e18, id, mx1 = -1e18, mx2 = -1e18, mx3 = -1e18, mx4 = -1e18;

signed main() {
	cin >> n >> m >> c;
	for(int i = 1; i <= c; i++) {
		cin >> x >> y;
		mx1 = max(mx1, x + y);
		mx2 = max(mx2, x - y);
		mx3 = max(mx3, y - x);
		mx4 = max(mx4, -x - y);
	}		//记录最边上的四个角 
	cin >> h;
	for(int i = 1; i <= h; i++) {
		cin >> x >> y;
		if(max({mx1 - x - y, mx2 - x + y, mx3 - y + x, mx4 + x + y}) < mi) {
			mi = max({mx1 - x - y, mx2 - x + y, mx3 - y + x, mx4 + x + y});
            		//对应上面的四个公式，但 + 和 - 的位置变了
			id = i;
		}	//如果更优则更新 
	}
	cout << mi << endl << id << endl;
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：liu_yi (赞：3)

## 思路

对于某一个餐厅，我们分别思考对于它的左上方，右上方，左下方，右下方的贡献，显然是最靠近四个角最好。可为什么这样正确呢?

证明：

对于某个餐厅的坐标 $(x,y)$，某个酒店的坐标 $(a,b)$：

1. 当酒店在餐厅的左上方时。$a < x$，$b < y$，两点间的距离为 $x + y - a - b$
2. 当酒店在餐厅的右上方时。$a < x$，$y < b$，两点间的距离为 $x - y - a + b$
3. 当酒店在餐厅的左下方时。$x < a$，$b < y$，两点间的距离为 $y - x + a - b$
4. 当酒店在餐厅的右下方时。$x < a$，$y < b$，两点间的距离为 $- x - y + a + b$

不难看出，如果把某一种情况判成另外一种情况，结果一定更劣。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,C,H,ans=INT_MAX,x,y,tmp[5]={0,INT_MIN,INT_MIN,INT_MIN,INT_MIN},pos,k;
inline int read(){
	int step=1,s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
	    if(ch=='-')step=-1;
	    ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
	    s=(s<<1)+(s<<3)+(ch^48);
	    ch=getchar();
	}
	return step*s;
}
int main(){
    n=read(),m=read(),C=read();
    while(C--){
        x=read(),y=read();
        tmp[1]=max(tmp[1],x+y);
        tmp[2]=max(tmp[2],x-y);
        tmp[3]=max(tmp[3],y-x);
        tmp[4]=max(tmp[4],-x-y);
    }
    H=read();
    for(int i=1;i<=H;i++){
        x=read(),y=read();
        k=max({tmp[1]-x-y,tmp[2]-x+y,tmp[3]-y+x,tmp[4]+x+y});
        if(ans>k)ans=k,pos=i;
    }
    printf("%d\n%d",ans,pos);
    return 0;
}
```

---

## 作者：CWzwz (赞：2)

**这是一篇思路不同，但复杂度较劣的题解。**

（模拟赛成绩截图）

![](https://cdn.luogu.com.cn/upload/image_hosting/bjhlm56w.png)

------------

求最大值最小，想到二分，并考虑判断：**是否存在一个餐厅，可以使得距离最大值 $\leq x$**。

如何实现？如果餐厅 $(a,b)$ 合法（最大距离 $\leq x$），对于任意一个住处 $(x_i, y_i)$，距离必然也小于等于 $x$，即

$$|x_i-a|+|y_i-b|\leq x$$

考虑拆掉绝对值，因为取绝对值后，值不减，所以

$$\pm(x_i-a)\pm(y_i-b)\leq x$$

解得

$$\begin{cases}
a+b-x\leq x_i+y_i\leq a+b+x\\
a-b-x\leq x_i-y_i\leq a-b+x
\end{cases}$$

也就是说，对于餐厅 $(a, b)$，如果所有人的住处 $(x_i, y_i)$ 均满足上面这个不等式组，这个餐厅就是合法的。离散化后前缀和维护即可，是 $O(n\log n)-O(\log n)$ 的。

然后就做完了，二分后顺序枚举餐厅，对每个餐厅查询满足上面不等式组的住处个数，如果等于 $c$（全部满足），那么这个餐厅合法，返回它的编号。没有合法的话返回 $0$。

时间复杂度 $O(c\log c\log V)$，$V$ 是坐标值域。500ms 喜提最劣解。

[Submission](https://codeforces.com/contest/491/submission/251647742)

---

## 作者：gcwixsxr (赞：2)

这是关于曼哈顿距离的一道题。难度大约只有普及。

我们先来研究一下曼哈顿距离。假设有两个点，分别为 $A(x_1,y_1)$ 和 $B(x_2,y_2)$。那么它们的曼哈顿距离 $dis_{A,B}=|x_1-x_2|+|y_1-y_2|$。下面分类讨论：

 - 如果有$(x_1-x_2)\ge0,(y_1-y_2)\ge0$，则有
 
 $dis_{A,B}=x_1-x_2+y_1-y_2=x_1+y_1-(x_2+y_2)$
 
 - 同理，如果有$(x_1-x_2)\ge0,(y_1-y_2)<0$, $dis_{A,B}=x_1-y_1-(x_2-y_2)$
 - 如果有$(x_1-x_2)<0,(y_1-y_2)\ge0$, $dis_{A,B}=x_2-y_2-(x_1-y_1)$
 - 如果有$(x_1-x_2)<0,(y_1-y_2)<0$, $dis_{A,B}=x_2+y_2-(x_1+y_1)$
 
 简而言之即
 
 $$
 
 dis_{A,B}=
 \begin{cases}|(x_1+y_1)-(x_2+y_2)|,&(x_1-x_2)\times(y_1-y_2)\ge0\\
|(x_1-y_1)-(x_2-y_2)|,&(x_1-x_2)\times(y_1-y_2)<0\end{cases}
 
 $$
 
 回到这道题，要求距离当前点最远点的曼哈顿距离。那么我们记录一下所有酒店中$x+y$的最大值和最小值，以及$x-y$的最大值和最小值（这四个极值所对应的酒店就是四个可能的最远点，可以证明距离餐厅的最远点一定在这四个酒店中）。对于每一个餐厅的坐标，算出它到四个可能最远点的距离，最后再取最大值即可。
 
 可以证明，当$(x_1-x_2)\times(y_1-y_2)\ge0$时，$|(x_1-y_1)-(x_2-y_2)|\le|(x_1+y_1)-(x_2+y_2)|$.
 
 当$(x_1-x_2)\times(y_1-y_2)<0$时，$|(x_1-y_1)-(x_2-y_2)|>|(x_1+y_1)-(x_2+y_2)|$.
 
 贴个码：
 
 ```cpp
 #include<bits/stdc++.h>
using namespace std;
const int inf=0x7fffffff;
int amax=-inf,bmax=-inf,amin=inf,bmin=inf;
int n,m,c,h;
int ans=inf,bestid; 
signed main(){
	cin>>n>>m;
	cin>>c;
	for(int i=1;i<=c;i++){
		int x,y;
		cin>>x>>y;
		amax=max(amax,x+y);
		amin=min(amin,x+y);
		bmax=max(bmax,x-y);
		bmin=min(bmin,x-y);
	}
	cin>>h;
	for(int i=1;i<=h;i++){
		int x,y;
		cin>>x>>y;
		int temp=0;
		temp=max(temp,max(abs(amin-(x+y)),abs(amax-(x+y))));
		temp=max(temp,max(abs(bmin-(x-y)),abs(bmax-(x-y))));
		if(ans>temp){
			ans=temp;
			bestid=i;
		}
	}
	cout<<ans<<endl<<bestid<<endl;
	return 0;
}

```


---

## 作者：Barewalk (赞：1)

[CF491B New York Hotel](https://www.luogu.com.cn/problem/CF491B)

### Praface

其实这题并没有绿题那么高，与 [AT_abc178_e](https://www.luogu.com.cn/problem/AT_abc178_e) 差不多，应该只有黄。

### Description

给定两个点集 $\{E_1,E_2\}$，求两个属于不同点集的点之间的最大曼哈顿距离。

### Solution

见到曼哈顿距离，便要想到转化成切比雪夫距离。

#### 引理

将每一个点 $(x, y)$ 转化成 $(x +y, x - y)$，新坐标系下的切比雪夫距离即为原坐标系下的曼哈顿距离。

#### 证明

两个点 $A(x_1, y_1)$ 与 $B(x_2, y_2)$ 之间的曼哈顿距离为：

$$
\begin{aligned}
d(A,B) &= \left\vert x_1 - x_2\right\vert + \left\vert y_1 - y_2\right\vert \\
&=\max\{x_1 - x_2 +y_1 - y_2, x_2 - x_1 +y_2 - y_1, x_1 - x_2 +y_2 - y_1, x_2 - x_1 + y_1 - y_2\} \\
&=\max\{\left\vert (x_1 + y_1) - (x_2  +y_2)\right\vert, \left\vert (x_1 - y_1) - (x_2 - y_2)\right\vert\}
\end{aligned}
$$

即 $(x_1 + y_1, x_1 - y_1),(x_2 +y_2, x_2 - y_2)$ 两点的切比雪夫距离。

证毕。

于是本题转化成求 $\max\limits_{i \in E_1,j \in E_2}\{\max\{\left\vert x_i - x_j\right\vert\ , \left\vert y_i - y_j\right\vert\}\}$。

那么分别找出的两个点集的最大、最小横纵坐标，四个可能取最大即可。

不过这样变量太复杂，可以只求出第一个点集的最大、最小横纵坐标，与第二个点集的每个点都比较一次更新答案即可。

总时间复杂度 $O(n)$，顺利通过本题。

### Codetime

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>
#define maxN 100100
#define pii pair<int, int>
using ll = long long;
constexpr int inf = 0x7f7f7f7f, mod = 1e9 + 7;
using namespace std;
int n, m, c, h, ans = inf, id;
int minX = inf, maxX = -inf, minY = inf, maxY = -inf;
int max(int a, int b, int c, int d) {
	return max(max(a, b), max(c, d));
}
int main() {
	cin.tie(nullptr) -> sync_with_stdio(false);
	cin >> n >> m;
	cin >> c;
	for (int i = 1; i <= c; ++ i) {
		int a, b, x, y;
		cin >> a >> b;
		x = a + b, y = a - b;
		minX = min(minX, x), maxX = max(maxX, x);
		minY = min(minY, y), maxY = max(maxY, y);
	}
	cin >> h;
	for (int i = 1; i <= h; ++ i) {
		int a, b, x, y;
		cin >> a >> b;
		x = a + b, y = a - b;
		int s = max(abs(x - minX), abs(x - maxX), abs(y - maxY), abs(y - minY));
		if (s < ans) {
			ans = s, id = i;
		}
	}
	cout << ans << '\n' << id << '\n';
	return 0;
}
```

---

## 作者：bluewindde (赞：1)

考场上 chr 巨佬写出了 K-D Tree 的解法，很暴力，但就是过了。

将酒店的位置建树，每读入一个餐厅就查询一次离这个餐厅最远的点并更新答案。（作为一种最坏 $O(n)$ 查询的数据结构，K-D Tree 还是可以被卡的，见 [OI-Wiki](https://oi-wiki.org/ds/kdt/)）

注意最大可能的距离为 $2\times10^9$，直接用 `int mid=(l+r)>>1` 可能会炸，所以要开 `long long`。

```cpp
// CodeForces 可以开火车头
#pragma GCC optimize(3)
#pragma GCC target("avx2")
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

int n,m,c,h;

struct tree { // K-D Tree 真可爱
	int x,y;
} s[100005];

int L[1000005];
int R[1000005];
int D[1000005];
int U[1000005];
int lc[1000005];
int rc[1000005];
int ans;
static inline bool cmp1(const tree &a,const tree &b) {
	return a.x<b.x;
}
static inline bool cmp2(const tree &a,const tree &b) {
	return a.y<b.y;
}
static inline void pushup(int x) {
	L[x]=R[x]=s[x].x;
	D[x]=U[x]=s[x].y;
	if(lc[x]) {
		L[x]=min(L[x],L[lc[x]]);
		R[x]=max(R[x],R[lc[x]]);
		D[x]=min(D[x],D[lc[x]]);
		U[x]=max(U[x],U[lc[x]]);
	}
	if(rc[x]) {
		L[x]=min(L[x],L[rc[x]]);
		R[x]=max(R[x],R[rc[x]]);
		D[x]=min(D[x],D[rc[x]]);
		U[x]=max(U[x],U[rc[x]]);
	}
}
static inline void build(int &x,int l,int r,bool op) {
	if(l>r) return ;
	int mid=(l+r)>>1;
	if(op) nth_element(s+l,s+mid,s+r+1,cmp1);
	else nth_element(s+l,s+mid,s+r+1,cmp2);
	x=mid;
	build(lc[x],l,mid-1,op^1);
	build(rc[x],mid+1,r,op^1);
	pushup(x);
}
static inline int f(int p,int a,int b) {
	if(!p) return -2e9-1;
	return max(abs(L[p]-a),abs(R[p]-a))+max(abs(U[p]-b),abs(D[p]-b));
}
static inline int dist(int p,int x,int y) {
	return abs(s[p].x-x)+abs(s[p].y-y);
}
static inline void query(int p,int x,int y) {
	if(!p) return ;
	ans=max(ans,dist(p,x,y));	
	int lt=lc[p],rt=rc[p];
	if(f(lt,x,y)>f(rt,x,y)) {
		if(ans<f(lt,x,y)) query(lt,x,y);
		if(ans<f(rt,x,y)) query(rt,x,y);
	}
	else {
		if(ans<f(rt,x,y)) query(rt,x,y);
		if(ans<f(lt,x,y)) query(lt,x,y);
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	cin>>c;
	for(int i=1;i<=c;++i) {
		int x,y;
		cin>>x>>y;
		s[i].x=x;
		s[i].y=y;
	}
	int rt=0;
	int minv=2e9+1;
	int mini;
	build(rt,1,c,0);
	cin>>h;
	for(int i=1;i<=h;++i) {
		int x,y;
		cin>>x>>y;
		ans=0;
		query(rt,x,y);
		if(ans<minv) {
			minv=ans;
			mini=i;
		}
	}
	cout<<minv<<endl;
	cout<<mini<<endl;
	return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

[博客食用更佳。](https://www.cnblogs.com/Jh763878/p/18145024)

~~最简洁易懂的代码。~~

这题很明显就是[曼哈顿距离](https://answer.baidu.com/answer/land?params=9Ihn90J6NJ6NbfwxUZYd4TbVjDF87p%2BAFphlIxJyBeQTlhKu5bix1kv14NQsfNiBK%2FjmbYC2H3N7M1G%2B4MT6FNLGMwvj9e5RYGBuPfR4tk1z%2F1nNbADeHmwLSjiZReB9rP%2BVIwbf0R5%2BI8laGf3vFwYBRjaovTaoPO7uTchEH2FsA0R0k%2BR4KCz6%2FpFBWkqjJ9TVo8VVq6uTw7XERUa6%2Bw%3D%3D&from=dqa&lid=edd8d7cc00c7b560&word=%E6%9B%BC%E5%93%88%E9%A1%BF%E8%B7%9D%E7%A6%BB)转[切比雪夫距离](https://answer.baidu.com/answer/land?params=snu2y58x5L1l93b3kDub3eRQJvaAH6HbCj2a3FrMGmHAhFPJb%2BIoVs903cE9AGZuAa0f716hBFe5zDNN6UHDla%2FOF6sLdjJuExrO1T3E%2Ftcdtv%2Bh%2F4M19LrPRDzlYyB2ADH75j9IV6MDIZgXJZZXuFHfodiWrs7KXBSx5kmHzjKjSzYrZyvrZIcOb1%2BpK9ZFMiWAI1sh0pZ9WhuIcbR%2BBw%3D%3D&from=dqa&lid=9bd49b5b004671ba&word=%E5%88%87%E6%AF%94%E9%9B%AA%E5%A4%AB%E8%B7%9D%E7%A6%BB)。

设点 $A=(x,y)$，$B=(xx,yy)$ 则 $Dis(A,B)=\vert x-xx\vert +\vert y-yy\vert$。

观察上面这个式子，不太好求，考虑转化为一堆数取最大的形式。

设 $x_1=x+y$，$y_1=x-y$，$x_2=xx+yy$，$y_2=xx-yy$。

则 $Dis(A,B)=\max(x_1-x_2,y_1-y_2)$，自己可以分讨算一下。

那么直接记录 $n $ 个人的位置中最小和最大的 $x_1$，$y_1$。

（二）

记得开 long long。

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e18;
int x,y,n,m,mnx=inf,mxx=-inf,mxy=-inf,mny=inf,ans=inf,ansid;
signed main(){
	scanf("%lld%lld",&x,&y);
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x,&y);
		mnx=min(mnx,x+y),mxx=max(mxx,x+y);
		mny=min(mny,x-y),mxy=max(mxy,x-y);
	}
	scanf("%lld",&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		int xx=x,yy=y;
		x=xx+yy,y=xx-yy;
		int s=max(max(abs(x-mnx),abs(x-mxx)),max(abs(y-mny),abs(y-mxy)));
		if(s<ans)ans=s,ansid=i;
	}
	printf("%lld\n%lld\n",ans,ansid);
	return 0;
} 
```

---

## 作者：mountain_climber (赞：0)

题目其实就是让你求对于餐厅 $b_{i}$ 距离它最远的酒店有多远。

此时我们可以发现，能成为一个餐厅的最远酒店的酒店只可能有四个，也就是右上、左上、右下、左下的四个酒店。这个结论是易证的。

但是此时我们发现比较难搞，就是这四个点比较难找。

考虑对于所有的餐馆来说，距离最大的酒店也只有可能在这个餐馆的右上、左上、右下、左下。分讨一下：

假设这个餐馆的坐标是 $(x_{i},y_{i})$，距离最大的酒店的坐标是 $(x_{j},y_{j})$。

当酒店在餐馆右上时，距离为：$x_{j}-x_{i}+y_{j}-y_{i}$，$-x_{i}-y_{i}+x_{j}+y_{j}$。

当酒店在餐馆左上时，距离为：$x_{i}-x_{j}+y_{j}-y_{i}$，$x_{i}-y_{i}-x_{j}+y_{j}$。

当酒店在餐馆右下时，距离为：$x_{j}-x_{i}+y_{i}-y_{j}$，$-x_{i}+y_{i}+x_{j}-y_{j}$。

当酒店在餐馆左下时，距离为：$x_{i}-x_{j}+y_{i}-y_{j}$，$x_{i}+y_{i}-x_{j}-y_{j}$。

还有一种特殊情况就是重合，可以被认为是上述四种的任意一种。

将最开始的结论和式子结合，然后就发现，只需要求一遍最大值就行了。

[AC记录](https://codeforces.com/contest/491/submission/238346903)

---

## 作者：Sad_Rex (赞：0)

一、**思路**：

十分简单，请你不要看完后说脏话。

对于每个餐厅我们想距离餐厅最远的一定是最靠近四个角落的。

易证，对于每个餐厅，我们用它的坐标可以分成 $4$ 个部分

![](https://cdn.luogu.com.cn/upload/image_hosting/bg9vmu1z.png?x-oss-process=image/resize,m_lfit,h_1700,w_2025)

显然，对于每一个餐厅，它的答案就是离中心最远的点，换句话说就是离四个角落最近的点。

于是我们就可以在输入预处理。

时间复杂度 $O(n)$。

但是我们需要注意细节：

![](https://cdn.luogu.com.cn/upload/image_hosting/z0fllydk.png?x-oss-process=image/resize,m_lfit,h_1700,w_2025)

对于靠上面的餐厅（橙球 $1$），我们发现俩个酒店距离角落的距离是一样的，但是他们对橙球 $1$ 的答案的贡献是一样的，所以我们要求出两个靠近角落的分别是靠近角落的两条边的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int  long long
#define kg putchar(' ')
#define endl puts("")
inline int read(){
    int vis=1,ans=0;
    char x=getchar();
    while(x<'0'||x>'9'){
        if(x=='-')vis=-1;
        x=getchar();
    }
    while(x>='0'&&x<='9'){
        ans=ans*10+x-'0';
        x=getchar();
    }
    return vis*ans;
}
inline void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
const int N=1e5+90;
int x[N],y[N];
int n,m,c,h;
int nx[N],ny[N];
struct Max1{
    int x,y,val;
}leup,ledn,riup,ridn;
struct Max2{
    int x,y,val;
}leup1,ledn1,riup1,ridn1;
int maxn=1e18,id;
signed main(){
	// freopen("city.in","r",stdin);
    // freopen("city.out","w",stdout);
    n=read(),m=read();
    c=read();
    leup.val=ledn.val=riup.val=ridn.val=1e18;
    for(int i=1;i<=c;i++){
        x[i]=read(),y[i]=read();
        if(leup.val>x[i]+y[i]-1-1||leup.val==x[i]+y[i]-1-1&&abs(x[i]-1)<abs(leup.x-1)){
            leup.val=x[i]+y[i]-2;
            leup.x=x[i],leup.y=y[i];
        }
        if(ledn.val>abs(x[i]-n)+abs(y[i]-1)||ledn.val==abs(x[i]-n)+abs(y[i]-1)&&abs(x[i]-n)<abs(ledn.x-n)){
            ledn.val=abs(x[i]-n)+abs(y[i]-1);
            ledn.x=x[i],ledn.y=y[i];
        }
        if(ridn.val>abs(x[i]-n)+abs(y[i]-m)||ridn.val==abs(x[i]-n)+abs(y[i]-m)&&abs(x[i]-n)<abs(ridn.x-n)){
            ridn.val=abs(x[i]-n)+abs(y[i]-m);
            ridn.x=x[i],ridn.y=y[i];
        }
        if(riup.val>abs(x[i]-1)+abs(y[i]-m)||riup.val==abs(x[i]-1)+abs(y[i]-m)&&abs(x[i]-1)<abs(riup.x-1)){
            riup.val=abs(x[i]-1)+abs(y[i]-m);
            riup.x=x[i],riup.y=y[i];
        }
    }
    leup1.val=ledn1.val=riup1.val=ridn1.val=1e18;
    for(int i=1;i<=c;i++){
        if(leup1.val>x[i]+y[i]-1-1||leup1.val==x[i]+y[i]-1-1&&abs(y[i]-1)<abs(leup1.y-1)){
            leup1.val=x[i]+y[i]-2;
            leup1.x=x[i],leup1.y=y[i];
        }
        if(ledn1.val>abs(x[i]-n)+abs(y[i]-1)||ledn1.val==abs(x[i]-n)+abs(y[i]-1)&&abs(y[i]-1)<abs(ledn1.y-1)){
            ledn1.val=abs(x[i]-n)+abs(y[i]-1);
            ledn1.x=x[i],ledn1.y=y[i];
        }
        if(ridn1.val>abs(x[i]-n)+abs(y[i]-m)||ridn1.val==abs(x[i]-n)+abs(y[i]-m)&&abs(y[i]-m)<abs(ridn1.y-m)){
            ridn1.val=abs(x[i]-n)+abs(y[i]-m);
            ridn1.x=x[i],ridn1.y=y[i];
        }
        if(riup1.val>abs(x[i]-1)+abs(y[i]-m)||riup1.val==abs(x[i]-1)+abs(y[i]-m)&&abs(y[i]-m)<abs(riup1.y-m)){
            riup1.val=abs(x[i]-1)+abs(y[i]-m);
            riup1.x=x[i],riup1.y=y[i];
        }
    }
    h=read();
    for(int i=1;i<=h;i++){
        nx[i]=read(),ny[i]=read();
        int ans=-1e18;
        if(abs(nx[i]-leup.x)+abs(ny[i]-leup.y)>ans)ans=abs(nx[i]-leup.x)+abs(ny[i]-leup.y);
        if(abs(nx[i]-riup.x)+abs(ny[i]-riup.y)>ans)ans=abs(nx[i]-riup.x)+abs(ny[i]-riup.y);
        if(abs(nx[i]-ledn.x)+abs(ny[i]-ledn.y)>ans)ans=abs(nx[i]-ledn.x)+abs(ny[i]-ledn.y);
        if(abs(nx[i]-ridn.x)+abs(ny[i]-ridn.y)>ans)ans=abs(nx[i]-ridn.x)+abs(ny[i]-ridn.y);
        if(abs(nx[i]-leup1.x)+abs(ny[i]-leup1.y)>ans)ans=abs(nx[i]-leup1.x)+abs(ny[i]-leup1.y);
        if(abs(nx[i]-riup1.x)+abs(ny[i]-riup1.y)>ans)ans=abs(nx[i]-riup1.x)+abs(ny[i]-riup1.y);
        if(abs(nx[i]-ledn1.x)+abs(ny[i]-ledn1.y)>ans)ans=abs(nx[i]-ledn1.x)+abs(ny[i]-ledn1.y);
        if(abs(nx[i]-ridn1.x)+abs(ny[i]-ridn1.y)>ans)ans=abs(nx[i]-ridn1.x)+abs(ny[i]-ridn1.y);
        if(maxn>ans)maxn=ans,id=i;
    }
    print(maxn),endl,print(id);
    return 0;
}
```


---

