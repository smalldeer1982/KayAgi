# Candies for Children

## 题目描述

在儿童节上，孩子们围成一圈跳舞。当音乐停止时，孩子们依然站成一个圆圈。这时，Lena 想起她的父母送给她一盒正好有 $k$ 颗“Wilky May”糖果的糖果盒。Lena 并不贪心，于是她决定把所有糖果都送给圈中的朋友们。

Lena 知道她的一些朋友是“甜食控”，而其他人不是。每个甜食控如果盒中至少有两颗糖果，就会拿出两颗，否则只拿一颗。其余的朋友每次只会从盒中拿出一颗糖果。

在分糖果之前，Lena 先离开了圆圈，此时圈中正好剩下 $n$ 个人。Lena 按顺时针方向用正整数给她的朋友们编号，从 $1$ 开始，其中编号 $1$ 分配给她最好的朋友 Roma。

最初，Lena 把糖果盒交给编号为 $l$ 的朋友，然后从编号 $l$ 的朋友开始，每个人按顺时针顺序从盒中取糖果并把盒子传给下一个人。这个过程一直持续到编号为 $r$ 的朋友取走最后一颗（或两颗）糖果并拿到空盒为止。请注意，可能有些朋友多次从盒中取糖果，也就是说，糖果盒可能在圈中转了好几圈才被拿空。

Lena 并不知道哪些朋友是甜食控，但她想知道，最多有多少个朋友可能是甜食控。如果这种情况根本不可能发生，请告诉她她的观察是错误的。

## 说明/提示

在第一个样例中，任意两位朋友都可以是甜食控，这样每个人都会拿到糖果盒两次，最后一位拿糖果的是第 $4$ 位朋友。

在第二个样例中，甜食控可以是任意三位朋友，除了第 $3$ 位朋友。

在第三个样例中，只有一位朋友会拿糖果，但他可以是甜食控，只是无法拿到两颗糖果。圈中的其他朋友也可以是甜食控，只是他们一次糖果都拿不到。

在第四个样例中，Lena 的观察是错误的，这种情况不可能发生。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 1 4 12
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 3 4 10
```

### 输出

```
3
```

## 样例 #3

### 输入

```
10 5 5 1
```

### 输出

```
10
```

## 样例 #4

### 输入

```
5 4 5 6
```

### 输出

```
-1
```

# 题解

## 作者：xlpg0713 (赞：2)

考虑如果枚举了有 $x$ 个人会拿两颗糖果，经过若干轮的传递后会剩下 $k\bmod (n+x)$ 颗糖果，令 $m$ 为起点到终点的距离，那么这个 $x$ 合法当且仅当 $k\bmod (n+x)\in[m,m+\min(x,m)]$。

看到 $k\bmod (n+x)$，套路化地，对 $\lfloor\frac{k}{n+x}\rfloor$ 整除分块，那么就是 $k-a(n+x)\in[m,m+\min(x,m)]$。$a$ 为整除分块中 $\lfloor\frac{k}{n+x}\rfloor$。

对 $x,m$ 的大小进行分类讨论，注意到左面的式子是一个一次函数，易于 $O(1)$ 计算令它满足限制的 $x$ 的范围。

时间复杂度 $O(\sqrt k)$。

---

## 作者：skyskyCCC (赞：2)

## 前言。
数学题，这篇题解尽量讲得详细点。
## 分析。
令 $len$ 为当前 $l$ 到 $r$ 的人数范围，如果 $l>r$ 则是一个回环。令 $a_1$ 为所有人拿的糖的数量的和。同时相应的，我们令 $a_2$ 为 $l$ 到 $r$ 的人拿的糖的数量。

看到数据范围，我就明白这道题不能乱搞。但是我们可以先搞个暴力分找找规律。枚举答案，我们考虑时间限制所以直接令 $n\leq 10^8$ 的情况，此时能在 $1$ 秒的时限内完成答案。这个部分的判断还是很简单的，就是判断一下 $l$ 到 $r$ 的这些人是否能拿走 $k \bmod\left(ans+n\right)$ 个糖果即可。同时我们需要注意到，他们这些人拿走的糖果数必须满足在一个区间内，这个区间我们定为 $\left[x_1,x_2\right]$ 则有下面的几个约束条件：
$$\begin{cases}x_1\geq ans-n+len+1\\x_i\geq 0\\x_2\leq ans\\x_2\leq len\end{cases}$$

以上的约束条件不难证明。此时我们就可以按照这个方法枚举每一种情况，然后找到答案即可。这样我们成功拿到的部分分。

考虑大于 $10^8$ 的情况，显然我们不能再枚举了。我们既然不能确定每个人拿走糖的数量，那我们就可以去找最少的那个糖的数量在哪个人的的手里。这样我们通过它去找那些贪心的人即可。其中我们令拥有的糖最少的那个人手中的糖有 $c$ 个，这里给出推导过程：

首先注意到范围，此时前文中的 $x_1$ 满足的条件是
$$\begin{cases}x_1\geq a_1-n\times 2+len\times 2-1\\x_i\geq len\end{cases}$$

前文中的 $x_2$ 满足的条件是
$$\begin{cases}x_2\leq a_1-n+len\\x_2\leq len\times 2\end{cases}$$

同时必须满足 $x_1\leq a_2\leq x_2$ 存在。

开始推导：显然有 $c\times a_1+a_2=k$ 则由部分分的思路存在 $x_1\leq k\leq x_2$。
该不等式两边同时加上一个相同的数得到：
$$x_1+c\times a_1\leq k\leq x_2+c\times a_1$$

提出左边，将 $x_1$ 换成最小值，得到：
$$\left(a_1-n\times 2+len\times 2-1\right)+c\times a_1\leq k$$
化简得到
$$len+c\times a_1\leq k$$

同理提出原不等式的右边，换成最大值，化简得到：
$$len\times 2+c\times a_1\geq k$$

联立解 $k_1$ 同时联系上面的 $k$ 的取值范围与其他变量的范围，将前面的刚刚的从不等式 $x_1+c\times a_1\leq k\leq x_2+c\times a_1$ 中提出来的 $a_1$ 最原始的未化简形式，得到
$$\begin{cases}a_1\leq\frac{k-len}{i}\\a_1\geq\frac{k-len\times 2}{i}\\a_1\leq\frac{k-len\times 2+n\times 2+1}{i+1}\\a_1\geq\frac{k-len+n}{i+1}\end{cases}$$

现在我们已经推导完了 $a_1$ 的取值范围，那么我们只需要在这个范围内找到最大的 $a_1$ 即可。因为 $a_1$ 越大，贪心多拿糖果的人一定多。

代码如下，仅供参考：
```
#include<cmath>
#include<algorithm>
#include<iostream>
#define ll long long
using namespace std;
ll n,k,l,r;
ll len,cut,cnt,sum,ans=-0x3f3f3f3f;
int main(){
	cin>>n>>l>>r>>k;
	if(r>=l) len=r-l+1;
	else len=n-l+1+r;
	if(n<=100000000){
		for(int i=n;i<=2*n;i++){
			sum=k%i;
			if(sum==0) sum=i;
			sum-=len;
			if(sum>=max(i-n-(n-len)-1,0ll)){
				if(sum<=min(len,i-n)){
				    ans=max(ans,i-n);
				}
			}
		}
	}
	else{
		if(k>=len&&k<=2*len){
			if(k==2*len){
				ans=max(ans,n);
			}
			else ans=max(ans,n+k-len*2+1);
		}
		for(int i=1;i<=k/n;i++){
			ll cnt=min((k-2*len+2*n+1)/(i+1),(k-len)/i);
			ll cut=max((k-len+n+i)/(i+1),(k-2*len+i-1)/i);
			if(cut<=cnt) ans=max(ans,cnt-n);
		}
	}
	if(ans==-0x3f3f3f3f){
		ans=-1;
	}
	cout<<ans<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Dancepted (赞：2)

思路：

题目中的数据范围是1e11，这个数据很微妙（1e11 = 1e5 * 1e6），所以分两种情况讨论：

① n < 2e6 ：

　　 这时候可以直接跑答案。

　　对于给定的p，y有很多取值，但是可以直接取模算出y的满足p、d约束最大值。O(n)复杂度。

② n > 2e6 ：

　　 这时候跑圈数i，每个对应的圈数可以求出最大的喜欢甜食的人数：

　　1、(p + n) * i + y + d = k

　　2、p - y <= n - d

　　联立这个就可以求p的最大值。（其中d表示l跑到r的人数，y表示d中的喜甜人数）然后处理一下细节就可以O(k/n)。

　　然后暴力跑就好了。注意一个点就是最后一个人可以喜欢甜食但是只拿一个。
  ```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll X = 2e6 + 5;

int main()
{
    ll n, l, r, k;
    cin >> n >> l >> r >> k;
    ll d = (r - l + n) % n + 1;

    ll ans = -1;
    if (n < X) {
        for (ll p = n; p >= 0; p--) {
            ll y = (k - 1)%(n + p) + 1 - d;
            if (y < 0 || y > p || y > d || d-(y+1) > n-p)
                continue;
            ll y2 = y+1;
            if (y2 <= p && y2 <= d) {
                ans = max(ans , p);
            }
            if (d-y <= n-p) {
                ans = max(ans, p);
            }
        }
    }
    else {
        for (ll i = 0; i <= k/n; i++) {
            ll p = (k - 2*d - (i-1)*n + 1) / (i+1);
            ll y = k - i*(n+p) - d;
            if (y < 0) {
                if (i == 0)
                    continue;
                ll dis = (-y - 1) / i + 1;
                y += i*dis;
                p -= dis;
            }
            if (p > n) {
                y += (p-n) * i;
                p == n;
            }
            if (y < 0 || y > p || y > d || d-(y+1) > n-p)
                continue;
            ll y2 = y+1;
            if (y2 <= p && y2 <= d) {
                ans = max(ans , p);
            }
            if (d-y <= n-p) {
                ans = max(ans, p);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：蹲在丛中笑 (赞：1)




没想到标算做法，推简单的式子推得头昏眼花。。

已知人数$n$，特殊要重复走的人数$w=r-l+1$（模n意义下），糖数$k$

设走一整轮需要的糖数为$s$，糖银（sweet teeth）的数量为$p$，则$s=n+p$

则走了若干轮后剩余的糖果数$k\ \text{mod}\ s$

这剩余的糖果数要满足：
$$k \ \text{mod}\ s-w\ge 0 \cdots \cdots\cdots\cdots  \cdots(1)$$
$$k \ \text{mod}\ s-w\le w \cdots \cdots\cdots\cdots  \cdots(2)$$
$$k \ \text{mod}\ s-w\ge p-(n-w)-1 \cdots  \cdots(3)$$
即区间里的糖银数>=总的糖银数-区间外最多有的糖银数-1 (-1来自最后一个糖银只吃一个糖）;
$$k \ \text{mod}\ s-w\le p \cdots \cdots  \cdots\cdots\cdots(4)$$
即区间里的糖银数<=总糖银数;

转化成
$$ \left\{
\begin{aligned}
w\le k\ \text{mod}\ s\le 2w \\
n-w\le s- k\ \text{mod}\ s\le 2n-2w+1  \\
\end{aligned}
\right. $$

再把mod拆开，转化成
$$\left\{
\begin{aligned}
\lfloor \frac k s\rfloor & \le & \lfloor \frac{k-w} s \rfloor \\
\lfloor \frac k s\rfloor & \ge & \lceil \frac{k-2w} s \rceil \\
\lfloor \frac k s\rfloor & \le & \lfloor \frac{2n-2w+k+1} s \rfloor-1 \\
\lfloor \frac k s\rfloor & \ge & \lceil \frac{n-w+k} s \rceil-1 \\

\end{aligned}
\right.$$

把上取整改成下取整，变成了这样：
$$\left\{
\begin{aligned}
\lfloor \frac k s\rfloor & \le & \lfloor \frac{k-w} s \rfloor \\
\lfloor \frac k s\rfloor & \ge & \lfloor \frac{k-2w-1} s \rfloor+1 \\
\lfloor \frac k s\rfloor & \le & \lfloor \frac{2n-2w+k+1} s \rfloor-1 \\
\lfloor \frac k s\rfloor & \ge & \lfloor\frac{n-w+k-1} s \rfloor \\

\end{aligned}
\right.$$

把s作为变量，显然每个东西都能整除分块，只有$O(\sqrt{n})$个取值，

题目要求最大的s-n，所以显然要从大到小枚举s，则每一个取值相同的分块里只要把右端点存下来

把五种$\lfloor \cdots\rfloor$各$O(\sqrt{n})$个区间的右端点存到数组里sort一下，然后一边遍历一边check有没有出现同时满足上面4个不等式，即可

。。另外，要特判$s|k$的情况，这种情况直接满足题意
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const int N=1e7;
ll n,w,k,siz,c[5],v[5];
pll Q[N];
void ins(ll id) {
	if(c[id]<0) return void(v[id]=-1);
	for(ll l=n,r;l<=2*n&&l<=c[id];l=r+1) {
		r=min(c[id]/(c[id]/l),2*n);
		Q[++siz]={r,id};
	}
}
bool chk() {
	return v[0]<=v[1]
		&&v[0]>=v[2]+1
		&&v[0]<=v[3]-1
		&&v[0]>=v[4];
}
void upd() {
	ll s=Q[siz].fi,id=Q[siz].se;
	--siz;
	v[id]=c[id]/s;
	if(w==n&&k%s==0) cout<<s-n,exit(0);
}
int main() {
	ll x,y;
	cin>>n>>x>>y>>k;
	w=(y-x+n)%n+1;
	c[0]=k;
	c[1]=k-w;
	c[2]=k-2*w-1;
	c[3]=2*n-2*w+1+k;
	c[4]=n-w+k-1;
	ins(0);
	ins(1);
	ins(2);
	ins(3);
	ins(4);
	sort(Q+1,Q+siz+1);
	while(siz) {
		do upd(); while(siz&&Q[siz].fi==Q[siz+1].fi);
		if(chk()) return cout<<Q[siz+1].fi-n,0;
	}
	cout<<-1;
}
```

---

