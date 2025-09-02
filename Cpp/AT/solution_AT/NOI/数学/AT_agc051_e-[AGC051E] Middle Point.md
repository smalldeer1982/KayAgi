# [AGC051E] Middle Point

## 题目描述

平面上最初有 $N$ 个点 $(x_1, y_1),\ \ldots,\ (x_N, y_N)$。すぬけ君可以进行任意有限次如下操作：

- 选择已经被打上的两个点，打上它们的中点（仅当该点尚未被打上时）。中点不要求是格子点。

操作结束后，所有被打上的格子点（包括最初的 $N$ 个点）的数量即为すぬけ君的得分。请计算能够获得的最高得分。

## 说明/提示

### 限制条件

- $3 \leq N \leq 100$
- $0 \leq x_i, y_i \leq 10^9$
- 任意三点不共线。
- 输入中的所有值均为整数。

### 样例解释 1

获得最高得分的一种方法如下：

- 最初，打上了 $4$ 个点 $(0, 0), (0, 2), (2, 0), (2, 2)$。
- 打上 $(0, 0)$ 和 $(0, 2)$ 的中点 $(0, 1)$。
- 打上 $(0, 0)$ 和 $(0, 1)$ 的中点 $(0, 0.5)$。
- 打上 $(0, 0)$ 和 $(2, 0)$ 的中点 $(1, 0)$。
- 打上 $(0, 0)$ 和 $(2, 2)$ 的中点 $(1, 1)$。
- 打上 $(0, 2)$ 和 $(2, 2)$ 的中点 $(1, 2)$。
- 打上 $(2, 0)$ 和 $(2, 2)$ 的中点 $(2, 1)$。
- 这样共打上了 $10$ 个点：$(0, 0), (0, 0.5), (0, 1), (0, 2), (1, 0), (1, 1), (1, 2), (2, 0), (2, 1), (2, 2)$。其中 $9$ 个点是格子点，因此可以获得 $9$ 分。

### 样例解释 2

可以证明，除了最初的 $N$ 个点外，无法再打上其他格子点。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
0 0
0 2
2 0
2 2```

### 输出

```
9```

## 样例 #2

### 输入

```
4
0 0
0 3
3 0
3 3```

### 输出

```
4```

# 题解

## 作者：Rainbow_qwq (赞：8)

首先考虑弱化的情况：在一维坐标轴上有若干个点，做题目中取中点的操作。

经过暴力打表的验证，能取到的点是：取 $D$ 表示所有点之间两两距离的 $\gcd$，设 $d=\dfrac{D}{2^{\text{lowbit}(D)}}$，要满足：

1. 在最左和最右的点之间。
2. 与最左的点距离为 $d$ 的整数倍。

为什么这个结论是正确的？考虑一下这个结论的本质。

有趣的地方正在于 $\gcd$。把最左的点到其他的点看做若干个向量 $(x,0)$。可以看做可以从最左的点开始，任意加减这些向量，能够得到的所有点，并且要在最左和最右的点之间。

对应到二维平面上来猜测结论，假设固定一个点 $A$，把从 $A$ 到其他点的向量集合称作 $\{(x,y)\}$，能得到的点就是从 $A$ 开始，任意加减这些向量，能够得到的所有点，并且要在所有点的凸包内。

最终结论是，能得到的点要满足

1. 要在所有点的凸包之内。
2. 在凸包边上的点，结论与一维的相同。由于没有三点共线，每条边上数量就是 $2$ 的若干次方。
3. 在凸包内的点，能得到的条件是它到某个点 $A$ 的距离是一堆向量的线性组合。

我们知道在二维平面上也是可以求向量的 $\gcd$ 的：

首先，向量 $A,B$ 和向量 $A+kB,B$ 能线性组合表出的向量集是相同的，那向量就可以做辗转相除。

假设手中已经有两个向量 $(a,b),(0,c)$，现在多加一个 $(x,y)$，首先可以把 $(a,b)$ 和 $(x,y)$ 辗转相除成 $(t_1,t_2),(0,t_3)$，然后让 $(0,c)\to (0,\gcd(c,t_3))$。

写成代码就是这样：

```cpp
struct P{
	int x,y;
};

void work(P&a,P&b){
	while(b.x){
		int t=a.x/b.x;
		a.x-=t*b.x,a.y-=t*b.y;
		swap(a,b);
	}
}

P a=p[1],b=p[2];
work(a,b);
For(i,3,n-1){
	P c=p[i];
	work(a,c),b.y=__gcd(b.y,c.y);
}
```

那能被表出的点变成了 $A+k_1\times(a,b)+k_2\times(0,c)$，然后以得到的两个向量 $(a,b),(0,c)$ 为基，变换一下坐标系，然后数凸包内整点数。

但这样还是数漏了，因为可以加中点。在一维问题里做的变换是 $d\to \dfrac{d}{2^{\text{lowbit}(d)}}$，在二维里同样可以做变换：

先把 $c\to \dfrac{c}{2^{\text{lowbit}(c)}}$，这样 $c$ 变成奇数。

然后把 $a,b$ 不断同除以二。如果 $a$ 变成奇数，那就无法再化简。如果 $a$ 是偶数 $b$ 是奇数，那就把 $b$ 加上 $c$ 变成偶数，继续除以二。容易发现这样能得到最简。

之后变换坐标系就变成了数凸包内整点个数，可以用 Pick 定理解决。

[代码](https://atcoder.jp/contests/agc051/submissions/39218379)，注意开 `__int128`。

当然上面只是用猜结论的方式解决本题，证明结论可以去看官方题解。

---

## 作者：jun头吉吉 (赞：5)

## 题意
有 $N$ 个点，每次可以选择两个点，把中点画上去。

问有限步内最多得到多少个整点。

$3\le N\le 100,0\le x_i,y_i\le10^9$。

不存在三点共线。

## 题解
首先 $Q$ 能被搞出来的条件是存在一组 $w_i$ 形如 $*/2^*$，且 $w_i\ge 0$，$\sum w_i=1$，$\sum w_iP_i=Q$。

然后我们给出如下结论：

- 凸包外面的点不可能构成
- 凸包边界的点只能用两边的点构成
- 凸包内部的点可以忽略 $w_i\ge0$ 的限制。

前两点是显然的。考虑第三点。不妨假设我们要构成的点是 $Q$，且 $Q$ 是原点。（否则平移到原点）

那么我们的目的是证明：

- 存在一组非负整数 $c_i$ 满足 $\sum c_iP_i=0$ 且 $\sum c_i$ 为 $2$ 的幂

和

- 存在一组整数 $d_i$ 满足 $\sum d_iP_i=0$ 且 $\sum d_i$ 为 $2$ 的幂

等价。也就是说我们需要找到一个用 $d_i$ 构造 $c_i$ 的方法。官方题解的方法是找到一组正整数 $e_i$ 满足 $\sum e_iP_i=0$，因为在凸包内部所以必然能找到一组正有理数解，乘上分母的 $\rm lcm$ 就是正整数解。找一个足够大的 $t$ 使得 $s\sum d_i+t\sum e_i$ 是 $2$ 的幂，且 $sd_i+te_i\ge0$。

总之通过上面的构造我们知道内部的点不需要限制 $w_i\ge 0$。我们还知道如果把一个点移到原点我们还不需要限制 $\sum w_i=1$。

如果 $w_i$ 都是整数可以构造出哪些点？这个问题可以用辗转相除得到两个向量 $A=(a,b),B=(c,0)$ 使得 $\{\sum w_iP_i|w_i\in\mathbb Z\}$ 和 $\{Am+Bn|m,n\in\mathbb Z\}$ 是相同的。具体的实现流程可以看代码。

但是 $w_i$ 可以是 $*/2^*$ 的形式，不难发现把 $\mathbb Z$ 换成 $W=\{a/2^b|a\in\mathbb Z,b\in\mathbb N\}$ 上面两个集合还是相同的。

以 $B,A$ 为基底建立新坐标系，新坐标系的点 $(x,y)$ 在原来的坐标系中是 $xB+yA$，也就是 $(ay+cx,by)$。

记 $\alpha=\mathrm{ord}_2a,\beta=\mathrm{ord}_2b,\theta=\mathrm{ord}_2c$，我们希望在原坐标系中也是整数，所以首先 $by$ 要是整数，也就是说 $y$ 是 $2^{-\beta}$ 的倍数。但是 $ay+cx$ 不好处理。考虑如果 $\alpha\ge\beta$，那么 $by$ 为整数时 $ay$ 也一定为整数，所以只要考虑 $cx$ 也就是 $x$ 是 $2^{-\theta}$ 的倍数。

但是如果 $\alpha<\beta$，但是 $\theta\le\alpha$，我们可以不断给 $A$ 加上 $B$ 使得最终的 $\alpha\ge\beta$。

但是如果 $\alpha<\min(\beta,\theta)$ 咋办呢？一个很高妙的方法就是交换 $x$ 轴和 $y$ 轴对 $A,B$ 重新辗转相除，可以断定之后一定会有 $\alpha\ge \min(\beta,\theta)$。

然后我们只需要考虑新的坐标系下，凸包内部有多少 $x$ 是 $2^{-\theta}$ 的倍数，$y$ 是 $2^{-\beta}$ 的倍数的点即可。

横坐标乘 $2^{\theta}$，纵坐标乘 $2^{\beta}$，就是要求凸包内部有多少整点。

这个问题是简单的。用皮克定理即可计算内部的整点数量。

时间复杂度 $\mathcal O(n\log n)$。

## 代码
```cpp
const int N=210;
int n,tp;struct point{
	ll x,y;point(ll x=0,ll y=0):x(x),y(y){}
	point operator+(const point rhs)const{return point(x+rhs.x,y+rhs.y);}
	point operator-(const point rhs)const{return point(x-rhs.x,y-rhs.y);}
	ll operator*(const point rhs)const{return x*rhs.y-y*rhs.x;}
	point operator*(const ll a)const{return point(a*x,a*y);}
	bool operator<(const point rhs)const{return x==rhs.x?y<rhs.y:x<rhs.x;}
}p[N],st[N],A,B;
void convexhull(){
	for(int i=1;i<=n;i++){while(tp>=2&&(p[i]-st[tp-1])*(st[tp]-st[tp-1])<=0)tp--;st[++tp]=p[i];}
	int _=tp;
	for(int i=n-1;i;i--){while(tp>_&&(p[i]-st[tp-1])*(st[tp]-st[tp-1])<=0)tp--;st[++tp]=p[i];}
}
signed main(){
	read(n);for(int i=1;i<=n;i++)read(p[i].x,p[i].y);
	sort(p+1,p+1+n);for(int i=n;i;i--)p[i]=p[i]-p[1];
	convexhull();
	for(int i=2;i<=n;i++){
		if(!p[i].y){B.x=__gcd(B.x,p[i].x);continue;}
		if(!A.y){A=p[i];continue;}
		while(p[i].y){
			A=A-p[i]*(A.y/p[i].y);
			swap(A,p[i]);
		}
		B.x=__gcd(B.x,p[i].x);
	}
	ll ans=0;
	for(int i=1;i<tp;i++){
		point _=st[i]-st[i+1];
		ans+=lowbit(__gcd(abs(_.x),abs(_.y)));
	}
	if(lowbit(A.x)<lowbit(A.y)&&lowbit(A.x)<lowbit(B.x)){
		swap(A.x,A.y);swap(B.x,B.y);
		while(B.y){A=A-B*(A.y/B.y);swap(A,B);}
		for(int i=1;i<=tp;i++)swap(st[i].x,st[i].y);
	}
	while(lowbit(A.x)<lowbit(A.y))A=A+B*(lowbit(A.x)/lowbit(B.x));
	ll beta=lowbit(A.y),theta=lowbit(B.x);
	for(int i=1;i<=tp;i++){
		point&p=st[i];
		p.y/=A.y;
		p.x=(p.x-p.y*A.x)/B.x;
		p.y*=beta;p.x*=theta;
	}
	ll in=0;
	for(int i=1;i<tp;i++){
		point _=st[i]-st[i+1];
		in-=__gcd(abs(_.x),abs(_.y));
	}
	for(int i=2;i<tp;i++)in+=abs(st[i]*st[i+1]);
	in/=2;in++;
	ans+=in;
	writeln(ans);
}
```

---

## 作者：Purslane (赞：4)

# Solution

有人往 NOI 模拟赛 T1 放这个。


祝搬题人和他的家人们身体健康，万事如意，天天开心！

--------

定义有理数 $r$ 是合法的，当前仅当存在整数 $p$ 使得 $2^p r \in \mathbb Z$。

本质上给你若干个向量（凸包上的），然后求这些凸包的线性组合，要求系数和 $=1$ 且所有系数都是合法的非负有理数。

凸包边界上的情况是容易处理的，考虑内部的点。内部的整点当然可以直接 pick 定理算，但是显然不是所有的整点都能构造到。

有结论：我们将一个向量移动到 $(0,0)$ 之后，只需要要求所有系数是好的。证明略。

合法有理数关于 $\pm$ 运算封闭，所以你可以做辗转相除。对于两个向量 $(a,b)$ 和 $(c,d)$，我们一定会变为 $(\gcd(a,c),\square)$ 和 $(0,\triangle)$ 的形式。

所有 $(0,\triangle)$ 依然可以辗转相除。也就是我们最后是 $(a,b)$ 和 $(0,c)$。

合法有理数关于 $\times$ 运算仍然封闭，所以我们可以让向量乘上 $0.5$。所以不妨设 $c$ 是奇数。

如果 $a$ 是奇数，那么彻底结束了（显然 $a$ 取到了 $\gcd \Delta_x$ 的不含 $2$ 的最大公因数）。否则，如果 $b$ 是奇数那么 $(a,b) \leftarrow (a,b+c)$。这样 $b$ 是偶数，发现可以让 $a$ 和 $b$ 同时除以 $2$。感性理解这样做是对的，不过确实不太会证明，先这样吧。

这样坐标变换之后变成求凸包内整点个数。上面已经提到了可以用 pick 定理直接算。

大家觉得这个适合放在 T1 吗。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
int n,x[MAXN],y[MAXN],tot=0,ans;
struct Node {__int128 x,y;}st[MAXN*2],nst[MAXN*2];
Node A;
__int128 B;
__int128 dabs(__int128 v) {
	return (v>=0)?v:-v;
}
__int128 calc(Node A,Node B,Node C) {
	__int128 x=B.x-A.x,y=B.y-A.y;
	__int128 X=C.x-A.x,Y=C.y-A.y;
	return dabs(X*y-x*Y);
}
signed main() {
	freopen("aka.in","r",stdin);
	freopen("aka.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>x[i]>>y[i];
	vector<pair<int,int>> vc;
	ffor(i,1,n) vc.push_back({x[i],y[i]});
	sort(vc.begin(),vc.end());
	ffor(i,1,n) x[i]=vc[i-1].first,y[i]=vc[i-1].second;
	int lst=1;
	ffor(i,1,n) {
		while(tot>lst&&(y[i]-st[tot].y)*(st[tot].x-st[tot-1].x)>(st[tot].y-st[tot-1].y)*(x[i]-st[tot].x)) --tot;
		st[++tot]={x[i],y[i]};
	}
	roff(i,n-1,1) {
		while(tot>lst&&(y[i]-st[tot].y)*(st[tot].x-st[tot-1].x)>(st[tot].y-st[tot-1].y)*(x[i]-st[tot].x)) --tot;
		st[++tot]={x[i],y[i]};
	}
	ffor(i,1,tot-1) {
		__int128 dt=__gcd(dabs(st[i].x-st[i+1].x),dabs(st[i].y-st[i+1].y));
		ans+=dt&-dt;
	}
	__int128 sx=st[1].x,sy=st[1].y;
	A={x[2]-sx,y[2]-sy};
	ffor(i,3,n) {
		Node AA={x[i]-sx,y[i]-sy};
		while(A.x&&AA.x) {
			__int128 del=A.x/AA.x;
			A.x-=AA.x*del,A.y-=AA.y*del;
			swap(A,AA);
		}
		if(AA.x) swap(A,AA); 
		B=__gcd(B,dabs(AA.y));
	}
	if(B) B/=(B&-B);
	while(1) {
		while(A.x%2==0&&A.y%2==0) A.x/=2,A.y/=2;
		if(A.x%2) break ;
		if(B) A.y+=B;
		else break ;
	}
	ffor(i,1,tot) {
		__int128 nx=(st[i].x-st[1].x),ny=(st[i].y-st[1].y);
		nst[i].x=nx/A.x;
		ny-=(nx/A.x)*A.y;
		if(ny) nst[i].y=ny/B;
	}
	__int128 S=0;
	ffor(i,2,tot-2) S+=calc(nst[1],nst[i],nst[i+1]);
	S=S+2;
	ffor(i,1,tot-1) S-=__gcd(dabs(nst[i+1].x-nst[i].x),dabs(nst[i+1].y-nst[i].y));
	cout<<(int)(S/2+ans);
	return 0;
}
```

---

