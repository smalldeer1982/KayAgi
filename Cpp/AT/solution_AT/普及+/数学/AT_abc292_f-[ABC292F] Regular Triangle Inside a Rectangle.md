# [ABC292F] Regular Triangle Inside a Rectangle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc292/tasks/abc292_f

縦の長さが $ A $、横の長さが $ B $ の長方形の内部に描ける正三角形の一辺の長さの最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ A,B\ \leq\ 1000 $
- $ A,B $ は整数
 
### Sample Explanation 1

下図のように描くのが最適で、一辺の長さが $ \sqrt{6}\ -\ \sqrt{2} $ になります。 ![image](https://img.atcoder.jp/abc292/2cd44ddc3d8241e510a356be9533631f.png) なお、この出力例の値は $ \sqrt{6}-\ \sqrt{2} $ と厳密には一致しませんが、誤差が $ 10^{-9} $ 以下なので正解として扱われます。

## 样例 #1

### 输入

```
1 1```

### 输出

```
1.03527618041008295791```

# 题解

## 作者：_Imaginary_ (赞：11)

竟然没有人 $O(1)$ 解决，MOer 狂喜。

## Problem

[Regular Triangle Inside a Rectangle](https://atcoder.jp/contests/abc292/tasks/abc292_f).

~~是不是很有道理？~~

## Solution

结论我想应该是大家最关心的，所以我先扔一个结论。

不妨设 $A\le B$，那么当 $B\ge \frac{2}{\sqrt 3}A$ 时，答案是 $\frac{2}{\sqrt 3}A$。

否则，答案是 $2\sqrt{A^2-\sqrt{3}AB+B^2}$。

## Proof

首先，很容易想到的是正三角形三个顶点，一个是矩形顶点，另两个在边上，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/f6pq84wu.png)

但是如果矩形过长，那么这样构造出的正三角形会有一个顶点在边的延长线上，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/9b0z5jyt.png)

这时，我们可以证明，最大的正三角形高是 $A$。

接下来，回到第一种非平凡情况，计算一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/2yx6qyjb.png)

大体思路就是说，$AC=\frac{2}{\sqrt{3}}A=\frac{2}{\sqrt 3}a+(B-\frac{1}{\sqrt 3}a)$，借助这个，再利用正三角形的对称性，就解决了。

因此，这道题就 $O(1)$ 解决了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
int A,B;
int main()
{
	scanf("%d%d",&A,&B);
	if(A>B) swap(A,B);
	if(4*A*A<=3*B*B)
	{
		printf("%.15Lf",(ld)(2*A)/(ld)(sqrt(3)));
		return 0;
	}
	printf("%.15Lf",(ld)sqrt((ld)(4*B*B+4*A*A)-(ld)(4*A*B)*sqrt(3)));
	return 0;
}


```

---

## 作者：b6e0_ (赞：6)

[题目](/problem/AT_abc292_f)

感觉别的题解都好复杂啊。

首先，显然最优三角形至少有两个顶点在矩形的边上。因为如果不是，那么选择三角形一条两端都不在矩形边上的边，将它平移并按比例扩大直到它的一点在边上，可以使三角形变大。

此时，我们不妨平移三角形使得它的一个顶点与正方形的一个顶点重合。

![](https://cdn.luogu.com.cn/upload/image_hosting/rswvvg99.png)

不妨设 $A$ 是长方形的宽，$B$ 是长。如图，将长方形放入坐标系中，我们选择的等边三角形是 $\triangle AEF$。设 $BE=x$，那么 $AE=\sqrt{A^2+x^2}$，所以我们想让三角形的边长 $AE$ 尽可能大，就需要让 $x$ 尽可能大。

现在在坐标系中，我们能写出点 $E$ 的坐标 $(x,A)$。点 $F$ 就是点 $E$ 绕原点顺时针旋转 $60\degree$ 得到的点，根据[转轴公式](https://baike.baidu.com/item/%E8%BD%AC%E8%BD%B4%E5%85%AC%E5%BC%8F/22777145)，点 $F$ 的坐标为 $\left(\dfrac{\sqrt3}2A+\dfrac12x,\dfrac12A-\dfrac{\sqrt3}2x\right)$。它需要满足的要求仅仅为在矩形内，即：
$$\begin{cases}\dfrac{\sqrt3}2A+\dfrac12x\le B\\\dfrac12A-\dfrac{\sqrt3}2x\ge0\end{cases}$$
解得：
$$\begin{cases}x\le2B-\sqrt3A\\x\le\dfrac A{\sqrt3}\end{cases}$$
取 $x$ 为这两个东西的 $\min$ 就是最大值。

于是做完了。代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	double A,B;
	cin>>A>>B;
	if(A>B)
		swap(A,B);
	double x=min(2*B-sqrt(3)*A,A/sqrt(3));
	cout<<fixed<<setprecision(10)<<sqrt(A*A+x*x);
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：4)

题意：给定长方形长为 $A$，宽为 $B$，$A,B\in[1,1000]\cap\mathcal{Z}$，求最大的等边三角形使其可以放在长方形内，输出边长。

容易发现答案具有单调性，所以可以二分三角形边长。

这里有一个结论，就是一定存在某一顶点与长方形端点重合的最优解，因为如果不是则可以将三角形平移至某一顶点与长方形端点重合且边长不变，仍在长方形内。

而且最优解的另外两个顶点也一定在长方形的边上。

所以考虑如何检验答案合法性，这里参考题面上的图：

![](https://img.atcoder.jp/abc292/2cd44ddc3d8241e510a356be9533631f.png)

发现该三角形的两侧会形成两个直角三角形，假如我们已经知道三角形边长，那么我们就知道了两侧直角三角形的角度，事实上，只要两个角度之和不超过 $\dfrac\pi 6$ 就是合法的，因为此时中间的夹角不低于 $\dfrac\pi 3$，可以缩小至 $\dfrac\pi 3$ 使其成为等边三角形。

于是我们在 $O(\log(\dfrac{\max\{A,B\}}\Delta))$ 的时间复杂度内得到了答案：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
using pr=pair<int,int>;
const int N=1e6+6;
int n,m,T,a[N],d[N],ans;
basic_string<int>lk[N];
int q[N],l,r;
bitset<N>vs;
int main(){
    ios::sync_with_stdio(false);
    int i,j,k,l,r,x,y;
    int A,B;
    cin>>A>>B;
    function<bool(ld)>ck=[&](ld d){
        ld L=d<A?0:acosl(A/d),R=d<B?0:acosl(B/d);
        ld res=acosl(-1)/2;
        res-=L,res-=R;
        return res>acosl(-1)/3;
    };
    ld L=min(A,B),R=10000,md,rl;
    while(R-L>1e-15){
        md=(L+R)/2;
        if(ck(md))rl=md,L=md+1e-17;
        else R=md-1e-17;
    }
    printf("%.15Lf\n",rl);
    return 0;
}
```

---

## 作者：Hell0_W0rld (赞：3)

# [ABC292F](https://www.luogu.com.cn/problem/AT_abc292_f) 题解
第一次在赛场上切掉 F，祭之。
## 题目大意
$A\times B$ 的矩阵内，求最大正三角形面积。
## 解题思路
这题有亿点数学。

我们发现，正三角形一定有一个顶点处于正方形的端点上。证明显然：不满足的都可以平移过来，结果不会更优秀。

设长方形为 $ABCD$，其中 $AB=a,BC=b$。并且正三角形为 $\triangle AEF$。

引理：正三角形的其中一条边 $AE$ 与长方形的边 $AB$ 的夹角 $\angle EAB$ 越大，$AE$ 也就越长。
+ 证明：设存在角度 $\angle EAB > \alpha$ 不满足上述条件。
+ 在 $AB$ 上取点 $E'$，联结 $AE'$，并使得 $\angle E'AB=\alpha$。
+ 因为 $\angle EAB > \alpha$，所以点 $E'$ 在 $BE$ 上，即 $BE'<BE$。
+ $AE'=\sqrt{a^2+(BE')^2},AE=\sqrt{a^2+(BE)^2}$，显然 $AE>AE'$。
+ 假设不成立，原命题成立。

所以我们可以二分 $\angle EAB$ 的大小：$0\degree\sim 30\degree$。

接着问题转换为：已知 $\angle EAB=\alpha$，求这个正三角形是否完全被长方形 $ABCD$ 包含。
### 转换后的解
我们可以通过 $\alpha$ 来得出正三角形的边长。

因为我们知道，根据余弦 $\cos$ 的定义，有 $\cos(\alpha)=\frac{a}{AE}$。于是 $AE=\frac{a}{\cos(\alpha)}$。

显然有 $\angle FAD=\beta=30\degree-\alpha$。

我们过 $F$ 做 $FG\perp AD$ 交 $AD$ 于 $G$。如果满足条件显然有 $FG<b$。

而 $FG$ 的值可以依赖 $\cos(\beta)$：$FG=EF\times \cos(\beta)$。而 $EF=AF$。于是本题就解完了。

注意当 $a<b$，需要进行 `swap` 操作；最后输出要转换为边长；`C++` 默认弧度制，需要用 $rad=\frac{\alpha\pi}{180}$ 转换。
### 图片

![](https://cdn.luogu.com.cn/upload/image_hosting/n3gfsybd.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/sutcy5rf.png)
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define repD(i,u,E) for(register ll i=hd[u];i;i=E[i].nxt)
#define all(x) x.begin(),x.end()
using namespace std;
void upd_s(ll&x,ll v){x=min(x,v);}
void upd_b(ll&x,ll v){x=max(x,v);}
ll a,b;
const ld pi=3.1415926535897,ERR=1e-12;
ld len(ld alpha,ld x){
	return 1.0/cos(alpha)*x;
}
bool OK(ld alpha){
	ld at=len(alpha,a);
	ld beta=pi/6-alpha;
	ld bt=1.0*cos(beta)*at;
	return b*1.0-bt>=ERR;
}
int main(){
	cin>>a>>b;
	if(a>b)swap(a,b);
	ld l=0,r=pi/6;
	ld ans=l;
	cout<<fixed<<setprecision(12);
	while(r-l>=ERR){
		ld mid=(l+r)/2.0;
		if(OK(mid))l=ans=mid;
		else r=mid;
	}
	ld at=len(ans,a);
	cout<<at<<endl;
	return 0;
}
```

---

## 作者：iiiiiyang (赞：3)

[逆天的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17179780.html)

[题目链接](https://www.luogu.com.cn/problem/AT_abc292_f)

不妨设 $a \le b$。显然当三角形三个点都在矩形边上的时候可以得到答案。

通过手玩我们可以发现，当正方形推广到矩形的过程中，我们将一边拉长，三角形就可以不断往下放来增长。直到达到一个临界值三角形一边和矩形一边重合，此时限制在于短边。不难得出这个临界值为 $b = \frac{2 \sqrt{3}}{3} a$。

![图片.png](https://s2.loli.net/2023/03/05/Cbp68uHP3nMYGLk.png)

定义三角形和 $a$ 边的夹角为 $\theta$，三角形边长为 $l$，由上可以得出：
$$
\theta
\begin{cases}
= 15^{\circ} \; (a = b) \\
\in (15^{\circ},30^{\circ}) \; (a < b < \frac{2 \sqrt{3}}{3} a) \\
= 30^{\circ} \; (a = \frac{2 \sqrt{3}}{3}) \\
\end{cases}
$$

当 $b \in (a,\frac{2 \sqrt{3}}{3} a)$ 时，我们可以得到方程：
$$
\frac{b}{\cos{30^{\circ} - \theta}} = \frac{a}{\cos{\theta}}
$$

易得出 $\frac{b}{a} = \frac{\sqrt{3}}{2} + \frac{1}{2} \tan{\theta}$。

从而有 $\tan{\theta} = \frac{2b}{a} - \sqrt{3}$。

进而得出 $\frac{1}{\cos^2{\theta}} = \tan^2{\theta} + 1 = \frac{4b^2}{a^2} - \frac{4 \sqrt{3} b}{a} + 4$。

由 $l^2 = \frac{a^2}{cos^2{\theta}}$ 得到 $l$。

综上：
$$
l = 
\begin{cases}
2 \sqrt{b^2 - \sqrt{3}ab + a^2} \; (a \le b \le \frac{2 \sqrt{3}}{3} a) \\
\frac{2 \sqrt{3}}{3} a \; (b > \frac{2 \sqrt{3}}{3} a) \\
\end{cases}
$$

---

## 作者：ケロシ (赞：1)

## 解题思路

这道题最先想到的是二分，可以二分边长，角度，在赛时可以打地非常快。

但是，我需要追求 $O(1)$ 的解法。

直接讨论 $\frac{2\sqrt{3}}{3}b > a > \frac{\sqrt{3}}{2}b$ 的情况。

首先设正三角形边长为 $x$，随后根据勾股定理通过图中三个直角三角形列出方程。

$(b-\sqrt{x^2-a^2})^2+(a-\sqrt{x^2-b^2})^2=x^2$       
接下来就设 $y = x^2$，然后推式子。    
$ (b-\sqrt{y-a^2})^2+(a-\sqrt{y-b^2})^2=y $    
$ b^2 + y - a^2 - 2b\sqrt{y-a^2} + a^2 + y - b^2 - 2a\sqrt{y-b^2} = y $    
$y = 2a\sqrt{y-b^2} + 2b\sqrt{y-a^2} $    
$ y - 2a\sqrt{y-b^2} = 2b\sqrt{y-a^2} $    
$y^2 + 4a^2(y-b^2)- 4ay\sqrt{y-b^2} = 4b^2(y-a^2) $    
$ y^2 + 4a^2(y-b^2)- 4b^2(y-a^2) = 4ay\sqrt{y-b^2} $    
$ y^2+4(a^2-b^2)y=4ay\sqrt{y-b^2} $    
$ y+4(a^2-b^2)=4a\sqrt{y-b^2} $    
$ y^2+8(a^2-b^2)y+16(a^2-b^2) = 16a^2(y-b^2) $    
$y^2-8(a^2+b^2)y+16(a^4-a^2b^2+b^4)=0$   
$ y=\frac{8(a^2+b^2)\pm \sqrt{64(a^2+b^2)^2-64(a^4-a^2b^2+b^4)}}{2}  $   
$ y=\frac{8(a^2+b^2)\pm 8\sqrt{3}ab}{2}  $       
$ y=4(a^2+b^2 \pm \sqrt{3}ab)  $    
$x = 2\sqrt{a^2+b^2 \pm \sqrt{3}ab}$    
检验一下，得出：$x = 2\sqrt{a^2+b^2 - \sqrt{3}ab}$。    

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b;
void solve(){
    cin >> a >> b;
    if(a < b) swap(a, b);
    if(a > b * 2./sqrt(3)) cout << b * 2 / sqrt(3);
    else cout << 2 * sqrt(a * a + b * b - sqrt(3) * a * b);
}
int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    solve();
    return 0;
}
```



---

## 作者：robinyqc (赞：1)

数学题，但是不会纯数学做法 QAQ。

这篇题解的前置知识：三角函数与反三角函数的定义。

### 题意简述

有一个边长为 $a$ 和 $b$ 的长方形。求这个长方形内能放置的正三角形的最大边长。

### 解题思路

不妨令 $a<b$。设长方形为矩形 $ABCD$，$|AB|=|CD|=a,|AD|=|BC|=b$。我们很容易看出，正三角形的一个点在矩形的顶点上，另一个点在边 $AD$ 或 $BC$ 上。不妨令一个点在点 $B$，另一个点（$P$）在边 $AD$ 上。剩下的那个点叫 $Q$。

令 $x=|AP|$，我们发现正三角形的边长 $|BP|$ 为 $\sqrt{x^2+a^2}$。因为 $x\geq 0$，$f(x)=\sqrt{x^2+k}$（$k$ 是一个常数） 在 $[0,+\infty]$ 上单调递增，故应让 $x$ 越大越好。

但是点 $Q$ 一定会抵到边上，因此 $x$ 是有个限度的。$Q$ 可能抵到 $BC$，也可能抵到 $CD$。分类讨论一下即可。

1. $Q$ 在 $BC$ 上。因为 $B,Q,C$ 三点共线，故三角形的边长为：$\frac {2a}{\sqrt3}$。

2. $Q$ 在 $CD$ 上。过 $Q$ 向 $AB$ 作垂线交 $AB$ 于 $M$，此时 $|QM|=b$。
	
    设在任意情况下 $|QM|=y$，我们要找 $y=b$ 时对应的 $x$。通过三角函数与反三角函数我们可以得知 $x$ 与 $y$ 的关系：设 $\theta=\arctan(\frac x a)$，那么 $y=|BP|\cdot \sin(\frac\pi 3+\theta)$。由于 $\theta\in[0,\frac \pi 2]$，$\theta$ 随 $x$ 的增加而增加。又由于 $y=\sin x$ 在 $x\in[0,\frac \pi 2]$ 具有单调性，可以二分 $x$ 得答案。

### 解题代码

```cpp
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#define int long long
using namespace std;
const double pi=3.1415926535897;
signed main(){
	int A,B;
	double gh3=sqrt(3ll);//gh3 就是根号 3
	cin>>A>>B;
	if(A>B) swap(A,B);
	if(A*A*4.0/3.0<=B*B) {//如果 Q 在 BC 上
		printf("%.10lf",2.0*A/gh3);
		return 0;
	}
	double l=0,r=A*2/gh3,dt=1e-11,x;
	while(r-l>dt) {//实数域上二分
		x=(r+l)/2;
		double alp=atan(x/A);
		double bet=alp+pi/3.0;
		double h=sin(bet)*sqrt(x*x+A*A);
		if(h>B) r=x;
		else l=x;
	}for(int i=0;i<100;i++) {//这么做是为了保证精度
		x=(r+l)/2;
		double alp=atan(x/A);
		double bet=alp+pi/3.0;
		double h=sin(bet)*sqrt(x*x+A*A);
		if(h>B) r=x;
		else l=x;
	}
	printf("%.10lf",sqrt(l*l+A*A));
	return 0;
}
```

---

## 作者：heaksicn (赞：1)

## 1 description

求在一个边长为 $a,a$ 的长方形中放入的最大正三角形边长。

## 2 solution

令较短的边为 $a$，较长的边为 $a$。

由于要求的是最大的边长，考虑二分。

通过观察样例可以发现，最大正三角形的一个顶点与长方形顶点重合。那么，可以以这个点为原点，以长方形的短边为 $x$ 轴，长边为 $y$ 轴，建立平面直角坐标系。

此时，正三角形的一个顶点确定为 $O(0,0)$。

再次观察样例，发现正三角形的三点都在长方形边上。于是，假设第二个点在 $x=a$ 上，可以考虑二分这个点的纵坐标。

接下来就是要考虑当前二分出的纵坐标是否可行。

假设当前二分出的纵坐标为 $t$，那么此时正三角形的第二个点就是 $A(a,t)$。

根据小学数学可知，正三角形的一个顶点在另外两个顶点连线的中垂线上。

那么先求出 $OA$ 的中点 $C(\frac{a}{2},\frac{t}{2})$，再求出 $OA$ 的解析式 $y=\frac{t}{a}x$。根据两条直线垂直时它们的斜率之积为 $-1$，可以求出这条中垂线的解析式为 $y=-\frac{a}{t}x+\frac{t}{2}+\frac{a^2}{2t}$。

这条中垂线与 $y$ 轴的纵坐标（长方形的长边）交于 $(0,\frac{t}{2}+\frac{a^2}{2t})$。

但是， 当 $\frac{t}{2}+\frac{a^2}{2t}>b$ 时，这条线的中垂线应该先与直线 $y=b$（长方形的短边）相交，坐标为 $(\frac{t^2}{2a}+\frac{a}{2}-\frac{bt}{a},b)$。

假设这个交点为 $D$。

当 $OD>OA$ 时,此时正三角形的第三个顶点 $B$ 应该在线段 $CD$ 长，符合在长方形内部的要求。

否则这个正三角形的第三个顶点就在长方形外，不符合题意。

根据这个规则计算然后二分即可。

## 3 code

```
//Man always remember love because of romance only!
#include<bits/stdc++.h>
using namespace std;
#define int long double
signed main(){
	long double a,b;
	cin>>a>>b;
	long double x=min(a,b),y=max(a,b);//x为短边，y为长边
	int ans=x;
	int l=0,r=y;
	while(r-l>=fabs(1e-15)){
		int mid=(l+r)/2;
		//(0,0)为点O
		//(x,mid)为点A
//		cout<<x<<" "<<mid<<endl;
		int dis=x*x+mid*mid;//OA的距离
		int mx=(0+x)/2,my=(0+mid)/2;
		//(mx,my)为中点C
//		cout<<mx<<" "<<my<<endl;
		int k=mid/x;//直线OA的斜率
		k=-1/k;//OA中垂线的斜率
		int ty=my-mx*k;
		//(0,ty) 
		//y=kx+ty为中垂线的解析式
		//x=(ty-y)/k
		int ex,ey;
		if(ty>y){
			ex=(y-ty)/k,ey=y;
		}else ex=0,ey=ty;//(ex,ey)为点D的坐标
		int ds=ex*ex+ey*ey;//OD的距离
		if(sqrt(ds)>sqrt(dis)) l=mid,ans=sqrt(dis);
		else r=mid;
	}
	cout<<setprecision(20)<<fixed<<ans;
	return 0;
}
```


---

## 作者：ダ月 (赞：1)

### 题意概要：

给定一个 $A\times B$ 的矩形，求能在矩形内画的最大边长的正三角形。输出边长。

### 题目分析：

不妨令 $A\le B$。

首先，要明白，一个三角形的摆放方式应当与 $\frac{B}{A}$ 有关。

当 $\frac{B}{A}$ 比较小时，显然，就像题目样例那样摆放，即一个点与矩形顶点重合，另外两个点分别在矩形两条边上。

当 $\frac{B}{A}$ 比较大时，我们只需要让正三角形的高为 $A$,高所对应的直线在 $B$ 上。

显然 $\frac{B}{A}$ 应当有个临界值。

结论 $1$：$\frac{B}{A}$ 的临界值是 $\frac{2}{\sqrt 3}$。

当三角形为第二种情况时，应当满足 $\frac{2}{\sqrt 3}A\le B$。所以临界值是这个。

结论 $2$：当 $\frac{B}{A}$ 小于 $\frac{2}{\sqrt 3}$ 时，三角形的边长为 $\frac{B}{\cos(|\arctan(2(-\frac{A}{B}+\frac{\sqrt3}{2}))|)}$。

证明如下：

令 $\angle ABE=x$，$\therefore \angle FBC=30\degree-x$。

由几何关系得，$B\cos x=A\cos(30\degree-x)$。

$\therefore \cos30\degree \cos x+\sin 30\degree \sin x-\frac{B}{A}\cos x=0$。

$\therefore \frac{1}{2}\sin x+(\frac{\sqrt3}{2}-\frac{B}{A})\cos x=0$。

由辅助角公式可得，$\sqrt{(\frac{1}{2})^2+(\frac{\sqrt3}{2}-\frac{B}{A})^2}\sin(x+\arctan(\frac{\frac{\sqrt3}{2}-\frac{B}{A}}{\frac{1}{2}}))=0$

$\therefore x=-\arctan(\frac{\frac{\sqrt3}{2}-\frac{B}{A}}{\frac{1}{2}})$。

因为 $0< x<90\degree$，为了不必要的错误，就对 $x$ 取绝对值。

$\cos x$ 乘上 $B$ 就是答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/zrcfauvb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

结论 $3$：当 $\frac{B}{A}$ 大于等于 $\frac{2}{\sqrt 3}$ 时，正三角形边长为 $\frac{2}{\sqrt3}A$。

结论显然。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
double A,B;
const double pi=acos(-1);
int main(){
	cin>>A>>B;
	if(A>B) swap(A,B);
	double tem=A*2.0/sqrt(3);
	if(B>=tem) cout<<fixed<<setprecision(18)<<tem;
	else cout<<fixed<<setprecision(18)<<B/cos(abs(atan(((-A/B)+sqrt(3)/2.0)*2.0)));
	return 0;
}
```

时间复杂度：$O(1)$。

一道纯纯的数学题。

---

