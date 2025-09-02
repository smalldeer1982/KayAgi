# Two Arithmetic Progressions

## 题目描述

You are given two arithmetic progressions: $ a_{1}k+b_{1} $ and $ a_{2}l+b_{2} $ . Find the number of integers $ x $ such that $ L<=x<=R $ and $ x=a_{1}k'+b_{1}=a_{2}l'+b_{2} $ , for some integers $ k',l'>=0 $ .

## 样例 #1

### 输入

```
2 0 3 3 5 21
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 4 3 0 6 17
```

### 输出

```
2
```

# 题解

## 作者：w23c3c3 (赞：15)

怎么都是数论做法（

那我就来一个不用推式子的简单做法吧

因为这里$x>b_1,x>b_2$（这个题目翻译中没有体现，但原题是有的，我被坑了好久），不难想到直接将$l=max(l,b_1,b_2)$

我们考虑分块思想

1.当$max(a_1,a_2)<1000$的时候

$\quad\quad$考虑$x\in[l,l+a_1a_2)$，只要知道$x≡m(mod\quad a_1a_2)$，那么就能求出这种情况下$x$的个数（其实就是$[x,r]$之间有多少个和$x$关于$a_1a_2$同余于$m$（$ans_m=[\dfrac{r-x}{a_1a_2}]+1$)

$\quad\quad$枚举$x$，对于每个符合条件的$x$都进行一遍上述操作（求$m,ans_m$）,最终相加就可以了

$\quad\quad$复杂度$O(a_1a_2)$

2.当$max(a_1,a_2)≥1000$的时候

$\quad\quad$不妨设$a_2≥a_1$

$\quad\quad$那么很显然，因为$r-l≤4\times 10^9$，所以满足第二个条件的数个数不会超过$\dfrac{r-l}{a_2}≤4\times 10^6$个，直接暴力枚举所有的满足第二个条件的数，判断一下是否可行就可以了

$\quad\quad$不过这里有$b_1,b_2$的影响，枚举的范围加大一点就可以了（我开大了$10$倍）

$\quad\quad$理论复杂度可以达到$O(\dfrac{r-l}{a_2})$

综合上述两种情况，我们发现两种情况都能在各自的范围内跑过去

于是这题我们就解决了

（好像没有数论方法好写不过没关系）

贴下代码（我码风不好，这个代码我处理过稍微好看一点）

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long a1,b1,a2,b2,l,r,i,k,ans;
int main(){
	scanf("%lld%lld%lld%lld%lld%lld",&a1,&b1,&a2,&b2,&l,&r);
	if(b1>l)l=b1;if(b2>l)l=b2;
	if(a1>a2)swap(a1,a2),swap(b1,b2);
	if(a2<1000)
		for(i=l;i<=min(l+a1*a2-1,r);i++)
			if((i%a1+a1)%a1==(b1%a1+a1)%a1 && (i%a2+a2)%a2==(b2%a2+a2)%a2)
				ans+=(r-i)/(a1*a2)+1;
	if(a2>=1000){
		for(i=-int(2e10/a2);i<=2e10/a2;i++){
			k=i*a2+b2;
			if((k%a1+a1)%a1==(b1%a1+a1)%a1)
				if(k>=l && k<=r && k>=b1 && k>=b2)ans++;
		}
	}
	printf("%lld\n",ans);
}
```

---

## 作者：CheemsaDoge (赞：11)

# [CF710D Two Arithmetic Progressions](https://www.luogu.com.cn/problem/CF710D)

## 根号分治薄纱数论

> 看日报学习的根号分治：[暴力美学——浅谈根号分治 - paulzrm 的博客](https://www.luogu.com.cn/blog/Amateur-threshold/pu-li-mei-xue-qian-tan-gen-hao-fen-zhi#)。
>
> ~~开始想学[ODT的映射思想的推广 - 金珂拉 的博客](https://www.luogu.com.cn/blog/jinkel/odt-di-ying-ye-sai-xiang-di-tui-guang)，结果先学了 `ODT`，又学了根号分治，才搞懂前置知识。~~

1. 什么是根号分治

   > 根号分治，是暴力美学的集大成体现。与其说是一种算法，我们不如称它为一个常用的 trick。

   其实就是将两个极端的暴力算法融合，根据不同数据选择更优的暴力，即可保证复杂度始终在可接受范围内。

2. 如何使用根号分治

   即写出两个不同暴力算法（通常是在小范围内很快的和在大范围内很快的），之后确定一个阈值，在不同范围选择不同暴力。

大概根号分治就是这样，具体请看[暴力美学——浅谈根号分治 - paulzrm 的博客](https://www.luogu.com.cn/blog/Amateur-threshold/pu-li-mei-xue-qian-tan-gen-hao-fen-zhi#)。

在这道题中，我们需要思考两种方法（定 $t$ 为阈值，默认 $a_1\ge a_2$，默认 $l=\max(l,\max(b_1,b_2))$）：

1. $a_1\le t$，则 $a_2\le t$。以 $\text{lcm}(a_1,a_2)$ 为一个循环节，显然的，一个循环节内至多有一个数同时出现在两个数列中。因此暴力枚举 $[\ l,\min(l+\text{lcm},r)\ ]$ 中的每一个数，若有 $i$ 使得 $i\in \text{数列1}\ \text{and}\ i \in \text{数列2}$，则可知共有 $\frac{(r-i)}{\text{lcm}+1}$ 个满足条件的值；反之没有所求值，输出 `0`。

2. $a_1\gt t$。则可以暴力枚举 $\text{数列1}$ 中的每一个处于 $[\ l,r\ ]$ 的数，若它同时处于 $\text{数列2}$ 则 `ans++`。

之后，我们进行复杂度分析：

1. 对于暴力1：时间复杂度为 $O(\text{lcm}(a_1,a_2))$。
2. 对于暴力2：时间复杂度为 $O(\frac{r-l+1}{a_1})$。

以下内容不保证正确性（数学太差了~~哭~~）：

> 故期望复杂度 $O(\text{lcm}(a_1,a_2)+(\frac{r-l+1}{a_1}))$，即 $O((t\times  a_2)+(\frac{2e9}{t}))$，对于 $a_2$ 有限制 $a_2\le t$，使 $a_2=t$，则可算出阈值 $t=\sqrt[3]{2e9}$。约 $1259$。

对于阈值的计算并不准确，如果有更优方法欢迎指正。

代码：

```cpp
//pre
const int t=1259;
signed main() {
	LL ans=0;
	LL a1,b1,a2,b2,l,r;
	read(a1,b1,a2,b2,l,r);
	if(b1>l) l=b1;
	if(b2>l) l=b2;	//保证l的大小为 b_1,b_2,l 中的最大值
	if(a2>a1) swap(a1,a2),swap(b1,b2); //保证 a_1>a_2
	LL lcm=a2*a1/__gcd(a1,a2);	//计算lcm  (lcm(a,b)*gcd(a,b)=a*b)
	if(a1<t) { 	//a_1 小于阈值
		for(int i=l;i<=min(l+lcm,r);i++) {
			if((i-b1)%a1==(i-b2)%a2&&(i-b2)%a2==0) {	//若满足题意
				ans=(r-i)/lcm+1;	//剩下有几个循环节并加上当前位置的一个
				break;
			}
		}
	}
	else {
		LL x;
		if(b1>=l) x=b1;
		else x=b1+ceil(1.00*(l-b1)/a1)*a1;//确定从哪里开始枚举（起始点要属于数列1）
		for(;x<=r;x+=a1) if((x-b2)%a2==0&&(x-b2)/a2>=0) ++ans;	//满足题意则ans++
	}
	write(ans); //输出
	return 0;	//好习惯捏
}
```

> `pre` 前的内容为头文件与快读快写，如果需要[戳这里](https://www.luogu.com.cn/paste/m6eedhaa)。

---

## 作者：UperFicial (赞：6)

只胡不写选手。

对于式子 $a_1k_1+b_1=a_2k_2+b_2$，可以写成 $a_1k_1-a_2k_2=b_2-b_1$。

这是一个不定方程的形式，所以我们设 $A=a_1,B=-a_2$，$C=b_2-b_1$，则可以写出不定方程：

$$Ak_1+Bk_2=C$$

求一组**特解**是简单的，设 $g=\gcd(A,B)$，则可以通过 exgcd 求出 $Ax_0+By_0=g$ 的一组特解，然后两边同时乘以 $\frac{C}{g}$ 得到 $A\frac{Cx_0}{g}+B\frac{Cy_0}{g}=C$，然后就得到了特解。

但我们的目的是求**通解**，对于一个整数 $p$，考虑到 $A\frac{Bp}{g}-B\frac{Ap}{g}=0$，所以我们可以把它加到上面。

于是得到 $A\frac{Cx_0+Bp}{g}+B\frac{Cy_0-Bp}{g}=C$，求出了通解 $k_1,k_2$。

然后就可以列出不等式了：

- $k_1,k_2\ge 0$。

- $L\le a_1k_1+b_1\le R$。

- $L\le a_2k_2+b_2\le R$。

然后求出 $p$ 的范围后，也就是 $x$ 的取值个数。

注意一下对于正数和负数，向下取整和向上取整的写法就好了。


---

## 作者：jianhe (赞：4)

### 前言：
纪念自己推出来的一道数论题。

并 [警示后人，如果你 WA on test 25](https://www.luogu.com.cn/discuss/945896)。

### 思路：

设 $p$ 在两个等差数列中都出现过，$k_1,k_2$ 均为整数。

对于第一个等差数列，$p$ 可以表示为 $b_1+k_1 a_1$。

对于第二个等差数列，$p$ 可以表示为 $b_2+k_2 a_2$。

得到 $b_1+k_1 a_1 = b_2+k_2 a_2$，变形得 $a_1 k_1 - a_2 k_2 = b_2 - b_1$。

令 $A \leftarrow a_1$，$B \leftarrow -a_2$，$C \leftarrow b_2-b_1$，则得到 $A k_1 + B k_2 = C$。

很明显是 `exgcd` 的形式，根据裴蜀定理先特判无解的情况。

于是求出一组特解，设为 $x_0,y_0$。

则通解为 $x=x_0+kB,y=y_0+kA$，其中 $k$ 为整数。

带回 $p=b_1+k_1 a_1$ 得 $p=b_1+(x_0+kB)a_1$。

由 $L \le p \le R$，得 $L \le b_1+(x_0+kB)a_1 \le R$。

推一下得 $\frac{L-b_1-a_1x_0}{a_1B} \le k \le \frac{R-b_1-a_1x_0}{a_1B}$。

算一下即可。


### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a1,a2,b1,b2,L,R,l,r,d,deltax,deltay,A,B,C,x,y,k;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1,y=0;return a;}
	ll ct=exgcd(b,a%b,y,x);y-=a/b*x;
	return ct;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>a1>>b1>>a2>>b2>>L>>R;
	A=a1,B=-a2,C=b2-b1;
	if(C%__gcd(A,B)){cout<<"0";return 0;}
	d=exgcd(A,B,x,y);x*=C,x/=d;//求出特解
	deltax=abs(a2/d),deltay=abs(a1/d);
	x=(x%deltax+deltax)%deltax,y=(C-A*x)/B;
	if(y<0) y=(y%deltay+deltay)%deltay,x=(C-B*y)/A;
    //调整 x,y 为正整数
	l=max((L-b1-A*x+A*deltax-1)/(A*deltax),0ll);
	r=floor(1.*(R-b1-A*x)/(A*deltax));//注意！
	cout<<max(r-l+1,0ll);
	return 0;
}
```

---

## 作者：_determination_ (赞：3)

根号分治真好玩！

考虑设根号分治的阈值为 $B$，以下为方便，称两个等差数列为 $A$ 和 $B$。

1. $a_1>B$

此种情况下你可以暴力列举 $A$ 在区间内的数并验证该数是否在 $B$ 中，可以发现这样复杂度是 $O(\dfrac{R-L}{a_1})$ 的。

2. $a_1\leq B$

发现当两个等差数列出现第一次重合之后，每加上 $\operatorname{lcm}(a_1,a_2)$ 后还是符合要求的。

现在考虑求出比 $L$ 大且同时在 $A$ 和 $B$ 中出现的最小的数。

首先将 $b_2$ 放大到比 $L$ 和 $b_1$ 都大，这个操作可以用简单的乘除法实现。之后考虑扩大 $b_2$。

我们可以直接暴力扩大，最多跳 $a_1$ 次即可。之后就是简单计算了。复杂度 $O(a_1)$。

当 $B$ 取 $\sqrt{R-L}$ 的时候复杂度最优。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int inf=0x3f3f3f3f3f3f3f3f;
void debug(){cout << "debug" << endl;}
const int B=50000;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	int a1,b1,a2,b2,l,r;
	cin >> a1 >>b1 >> a2 >>b2 >>l >>r;
	if(a1>B)
	{
		int ans=0;
		for ( int i = b1 ; i <= r ; i+=a1 )
		{
			if((i-b2)%a2==0&&i>=l&&i>=b2)ans++;
		}
		cout << ans << endl;
	}else{
//		for ( int i = -B*2 ; i <= B*2 ; i++ )
//		{
//			int x=i*a1+b1;
//			if((b2-x)%a2==0)
//			{
//				int lcm=a1*a2/__gcd(a1,a2);
//				int beg=max(max(b1,b2),l);
//				if(x<=beg)
//				{
//					x+=((beg-x)/lcm+1)*lcm;
//				}
//				x=beg+(x-beg)%lcm;
//				if(r<x)continue;
//				cout << (r-x)/lcm+1;
//				return 0;
//			}
//		}
//		cout << 0;
		int lcm=a1*a2/__gcd(a1,a2);
		if(b2<b1)b2=(max(b1,l)-b2+a2-1)/a2*a2+b2;
//		cout << b2 << endl;
		for ( int i = 0 ; i <= a1 ; i++ )
		{
			if((b2-b1)%a1==0&&b2>=b1)break;
			b2+=a2;
		}
		if((b2-b1)%a1||b2>r)return cout << 0,0;
		int mn=(l-b2+lcm-1)/lcm*lcm+b2;
		mn=max(mn,b2);
//		cout << b2 << endl;
		cout << (r-mn)/lcm+1 << endl;
	}
	return 0;
}
/*
2 0 4 2 -39 -37
3 81 5 72 -1761 501
34 64314 836 5976 591751179 605203191
1000000000 1 2000000000 0 -2000000000 200000000
3 -1164702220 906446587 -1868913852 222249893 1493113759
*/
```

---

## 作者：Xy_top (赞：3)

看了根分的日报来做的这一题，然后独立想出来了，感觉不配紫，顶多蓝了吧。

考虑对于 $a1$ $a2$ 进行根号分治，如果它们中一个大于等于 $40$，就能通过 $O(1)$ 公式得到第一个合法的解后暴力枚举。

如果它们都小于 $40$，那么我想两个解之间的差距应该不会超过 $1600$ 或者就是无解。

枚举要从 $\max(L,b1,b2)$ 开始，前面的一定无解可以判掉。

枚举到两个解之后就可以退出了。手推模拟啥的就能发现两个相邻解之间的差是相等的，于是就能 $O(1)$ 了。

代码也是很好写：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int a1, b1, a2, b2;
int ans, L, R;
void solve () {
	cin >> a1 >> b1 >> a2 >> b2 >> L >> R;
	if (a1 < a2) {
		swap (a1, a2);
		swap (b1, b2);
	}
	if (a1 >= 40) {
		int x;
		if (b1 >= L) x = b1;
		else x = b1 + ceil ( (L - b1) * 1.0 / a1) * a1;
		for (; x <= R; x += a1) if ( (x - b2) % a2 == 0 && (x - b2) / a2 >= 0) ++ ans;
		cout << ans;
	} else {
		int ans1, ans2, cnt = 0;
		For (i, max (L, max (b1, b2) ), R) {
			if (i - max (L, max (b1, b2) ) >= 10000) {
				cout << 0;
				return;
			}
			if ( (i - b1) % a1 == 0 && i >= b1 && (i - b2) % a2 == 0 && i >= b2) {
				++ cnt;
				if (cnt == 1) ans1 = i;
				else ans2 = i;
				if (cnt == 2) break; 
			}
		}
		if (cnt < 2) cout << cnt;
		else cout << 2 + ( (R - ans2) / (ans2 - ans1) );
	}
}
signed main () {
	ios :: sync_with_stdio (false);
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：hgzxwzf (赞：3)

因为 $x=a_1\times k_1+b_1,x=a_2\times k_2+b_2$，所以 $a_1\times k_1-a_2\times k_2=b_2-b_1$，不妨设 $b_2>b_1$。

可以用 exgcd 求解 $k_1,k_2$（无解就没有答案），为了方便，可以转化为求 $a_1\times k_1+a_2\times k_2=b_2-b_1$。

设通解为 $x'=x+\frac{a_2}{\gcd(a_1,a_2)}\times k,y'=y-\frac{a_1}{\gcd(a_1,a_2)}\times k$。

代入方程得到 $a_1\times (x+\frac{a_2}{\gcd(a_1,a_2)})\times k-a_2\times (\frac{a_1}{\gcd(a_1,a_2)}-y)\times k=b_2-b_1$。

所以 $k_1=(x+\frac{a_2}{\gcd(a_1,a_2)})\times k,k_2=a_2\times (\frac{a_1}{\gcd(a_1,a_2)}-y)\times k$。

要保证 $k_1\ge 0,k_2\ge 0,l\le k_1\times a_1+b_1\le r,l\le k_2\times a_2+b_2\le r$，可以通过四个不等式求出整数 $k$ 的范围。

因为一个 $k$ 对应着一个 $k_1$ 和 一个 $k_2$，所以一个 $k$ 对应一个 $x$，$k$ 的不同取值的数量就是答案。
```cpp
int exgcd(int a,int b,int &x,int &y)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	int gcd=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return gcd;
}

int mceil(int a,int b)
{
	return ceil(1.0*a/b);
}

int mfloor(int a,int b)
{
	return floor(1.0*a/b);
}

signed main()
{
	int a1,a2,b1,b2,l,r;
	scanf("%lld%lld%lld%lld%lld%lld",&a1,&b1,&a2,&b2,&l,&r);
	if(b1>b2)
	{
		swap(a1,a2);
		swap(b1,b2);
	}
	int x,y,gcd;
	gcd=exgcd(a1,a2,x,y);
	if((b2-b1)%gcd) return puts("0"),0;
	int b=a2/gcd,a=a1/gcd;
	x*=(b2-b1)/gcd,y*=(b2-b1)/gcd;
    
	int l1=mfloor(mfloor(l-b1,a1)-x,b),
   	r1=mfloor(mfloor(r-b1,a1)-x,b),
   	l2=mceil(mceil(l-b2,a2)+y,a),
    	r2=mfloor(mfloor(r-b2,a2)+y,a);
        
	l=max(l1,l2),r=min(r1,r2);
	int k=max(mceil(-x,b),mceil(y,a));
	printf("%lld",max(0ll,r-max(l,k)+1));
	return 0;
}
```


---

## 作者：kkxacj (赞：2)

#### 前言

根号分治泰裤辣。

#### 思路

想到两种暴力做法。

1. 选其中一个数假设选第一个，每次加 $a_1$ 看是否在 $L \sim R$ 之间且能被另一个数表示出来，复杂度是 $O\left(\frac{\left(R-b_1 \right)}{a_1} \right)$。

2. 假设 $b_1+a_1\times p = b_2+a_2\times q$，那么在此之后它们的循环节是 $\lim \left (a_1,a_2 \right)$，考虑找出一个数使得 $b_1+a_1\times p$ 是 $b_2$ 这个数列上的数，那么就找到第一个在 $b_1,b_2,L$ 前面的且满足条件的数，算贡献就行了，复杂度是 $O\left(\lim \left (a_1,a_2 \right)\right)$。

容易想到当 $a_1 \le \sqrt{10^9\times 4}$ 时，用第二个，否则用第一个，那么时间复杂度就是 $\sqrt{10^9\times 4}$ 的了，可以通过。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int a,b,a1,b1,l,r,t,ans,f,p,L;
signed main()
{
	t = sqrt(4e9);
	read(a),read(b),read(a1),read(b1),read(l),read(r);
	if(a < a1) swap(a,a1),swap(b,b1);
	if(a <= t)
	{
		for(int i = -2*t;i <= 2*t;i++)
		{
			p = b+a*i;
			if(abs(b1-p) % a1 == 0)
			{
				f = a*a1/__gcd(a,a1);
				L = max(max(b,l),b1);
				if(p < L) 
				{
					p += (L-p)/f*f+f; 
					p = L + (p-L)%f;
				}
				else p = L + (p-L)%f;
				if(p > r) pc('0');
				else print(((r-p)/f+1));
				flush();
				return 0;
			}
		}
		pc('0');
		flush();
	}
	else
	{
		for(int i = b;i <= r;i += a) 
			if(l <= i && i>=b1 && (i-b1) % a1 == 0) ans++;
		print(ans);
		flush();
	}
	return 0;
}
```

---

## 作者：Forever1507 (赞：2)

不会 excrt 的朋友请先去你谷的板子题或者 [OIwiki](https://oiwiki.org) 学一下。

坑巨多无比。

首先对于 $a_1,b_1,a_2,b_2$ 可以上 excrt 先求出最小整数解，然后得出最在 $[L,R]$ 范围内的最小和最大解（公差为 $\operatorname{lcm}(a_1,a_2)$）,最后利用等差数列算项数即可。

然后 WA on #3

数据：

`2 0 4 2 -39 -37`

这个时候我回去读了一遍英文题面，发现原来这个 $x$ 不能小于 $\max(b_1,b_2)$ （就是 $k',l'>=0$ 这一句，顺带一提，$b_1,b_2$ 要提前存起来，不然的话原来的值在 excrt 里会被更改）

然后我的输出部分从

`cout<<(r-l)/lcm+1;`

变成了
```
l=max(l,max(b1,b2));
if(l>r)cout<<0;
else cout<<(r-l)/lcm+1;
```
然后激情 WA on #28 （

数据：

`2 0 2 1 0 1000000000`

我寻思着这不无解吗，然后我跑回去一看我的 excrt 函数返回 `-1` 的时候我应该直接输出 $0$ 然后 `return` 但是我没有（

然后再交了一遍，终于过了（）

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005],b[100005];
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b,x,y),x0=x,y0=y;
	x=y0;
	y=x0-a/b*y0;
	return d;
}
int inv(int x,int p){
	int x0,y0;
	exgcd(x,p,x0,y0);
	return x0;
}
int excrt(){
	int lcm=a[1];
	int ans=b[1];
	for(int i=2;i<=n;++i){
		b[i]=((b[i]-ans)%a[i]+a[i])%a[i];
		int x0,y0;
		int d=exgcd(lcm,a[i],x0,y0);
		if(b[i]%d)return -1;
		int k=(a[i]+b[i]/d*x0%a[i])%a[i];
		ans=ans+k*lcm;
		lcm=lcm/d*a[i];
		ans=(ans+lcm)%lcm;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	n=2;	
	int b1,b2;//提前存一下
	for(int i=1;i<=2;++i){
		cin>>a[i]>>b[i];
		if(i==1)b1=b[1];
		else b2=b[2];
		b[i]=(b[i]%a[i]+a[i])%a[i];
	}
	int lt,rt;
	cin>>lt>>rt;
	int cur=excrt(),lcm=a[1]/__gcd(a[1],a[2])*a[2];
	if(cur==-1){//无解
		cout<<0;
		return 0;
	}
	int l=(lt-cur)/lcm*lcm+cur;
	if(l<lt)l+=lcm;//首项
	int r=(rt-cur)/lcm*lcm+cur;
	if(r>rt)r-=lcm;//末项
//	cout<<l<<' '<<r<<'\n';
	l=max(l,max(b1,b2));
	if(l>r)cout<<0;
	else cout<<(r-l)/lcm+1;
	return 0;
}
```


---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF710D) & [CodeForces题目页面传送门](https://codeforces.com/contest/710/problem/D)

>有$2$个等差数列$A:A_i=a_1i+b_1(i\in\mathbb N),B:B_i=a_2i+b_2(i\in\mathbb N)$。给定$l,r$，求有多少个整数$n\in[l,r]$满足$n$既在$A$内又在$B$内。

>$a_1,a_2\in\left(0,2\times10^9\right]\cap\mathbb Z,b_1,b_2,l,r\in\left[-2\times10^9,2\times10^9\right]\cap\mathbb Z,l\leq r$。

设$n$在$A$中是第$x\in\mathbb N$项，在$B$中是第$y\in\mathbb N$项，则可以列出不定方程
$$a_1x+b_1=a_2y+b_2$$
转化成标准形式，得
$$a_1x-a_2y=b_2-b_1$$
这个显然可以用Exgcd先确定无解并输出$0$走人，或确定有解并得到一组特解$\begin{cases}x=x'\\y=y'\end{cases}$。令$\Delta x=\dfrac{a_2}{\gcd(a_1,a_2)},\Delta y=\dfrac{a_1}{\gcd(a_1,a_2)}$，则通解是$\begin{cases}x=x'+k\Delta x\\y=y'+k\Delta y\end{cases}(k\in\mathbb Z)$。但对于$x,y$还有一个特殊的条件，就是$x,y\in\mathbb N$。不难发现$x,y$同增同减，不妨找到使得$x,y$都最小的一组解$\begin{cases}x=x''\\y=y''\end{cases}$。$x,y$都最小，当且仅当$x-\Delta x<0$或$y-\Delta y<0$，于是分别令$x''=x'\bmod \Delta x,y''=y'\bmod \Delta y$，每次带入原方程解出另一个变量看是否$\geq0$，必有一次合法。

现在知道了$x'',y''$，通解就变成了$\begin{cases}x=x''+k\Delta x\\y=y''+k\Delta y\end{cases}(k\in \mathbb N)$。将$x=x''+k\Delta x$带入$a_1x+b_1\in[l,r]$得
$$a_1(x''+k\Delta x)+b_1\in[l,r]$$
即
$$a_1x''+a_1k\Delta x+b_1\in[l,r]$$
即
$$a_1k\Delta x\in[l-a_1x''-b_1,r-a_1x''-b_1]$$
即
$$k\in\left[\dfrac{l-a_1x''-b_1}{a_1\Delta x},\dfrac{r-a_1x''-b_1}{a_1\Delta x}\right]$$
又因为$k\in\mathbb N$，所以
$$k\in\left[\max\left(0,\left\lceil\dfrac{l-a_1x''-b_1}{a_1\Delta x}\right\rceil\right),\left\lfloor\dfrac{r-a_1x''-b_1}{a_1\Delta x}\right\rfloor\right]$$
然后算出$k_{\min},k_{\max}$，$\max(0,k_{\max}-k_{\min}+1)$就是答案。

最后吐槽一下，C++中的`/`号是向零取整，也就是$<0$时上取整、$\geq0$时下取整，$k$的解集中如果直接用`/`号算会WA~~，然后心态爆炸~~。所以必须要将被除数和除数统一取绝对值，然后利用$\left\lfloor\dfrac ab\right\rfloor+\left\lceil\dfrac {-a}b\right\rceil=0$这个原理计算，最后该取相反数取相反数：
```cpp
int div_floor(int x,int y){return (x<0)^(y<0)?-(abs(x)+abs(y)-1)/abs(y):x/y;}
int div_ceil(int x,int y){return (x<0)^(y<0)?-abs(x)/abs(y):(x+y-1)/y;}
```
下面贴AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int div_floor(int x,int y){return (x<0)^(y<0)?-(abs(x)+abs(y)-1)/abs(y):x/y;}//下取整 
int div_ceil(int x,int y){return (x<0)^(y<0)?-abs(x)/abs(y):(x+y-1)/y;}//上取整 
int exgcd(int a,int b,int &x,int &y){//Exgcd 
	if(!b)return x=1,y=0,a;
	int d=exgcd(b,a%b,y,x);
	return y-=a/b*x,d;
}
int a1,a2,b1,b2,l,r;//题目给的参数 
signed main(){
	cin>>a1>>b1>>a2>>b2>>l>>r;
	int x,y,gcd=exgcd(a1,-a2,x,y);
	if((b2-b1)%gcd)return puts("0"),0;//无解 
	x*=(b2-b1)/gcd;y*=(b2-b1)/gcd;//找到特解 
	int dx=abs(a2/gcd),dy=abs(a1/gcd); 
	((x%=dx)+=dx)%=dx;y=(a1*x-(b2-b1))/a2;
	if(y<0)((y%=dy)+=dy)%=dy,x=(a2*y+(b2-b1))/a1;//找到使x,y都最小的解 
	int l0=max(0ll,div_ceil(l-a1*x-b1,a1*dx)),r0=div_floor(r-a1*x-b1,a1*dx);//k[min],k[max] 
	cout<<max(0ll,r0-l0+1);//答案 
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：1)

[更好的阅读体验](http://blog.cyx2009.top/archives/259/)

# 前言

这是今天粉兔杯每日一题，也是根分日报例题，补一下。

[暴力美学——浅谈根号分治 - paulzrm 的博客 - 洛谷博客](https://www.luogu.com.cn/blog/Amateur-threshold/pu-li-mei-xue-qian-tan-gen-hao-fen-zhi)

# 题目翻译

给出两个等差数列，求在 $[L,R]$ 之间的交集大小。

等差数列形式为 $ak+b$。

$1\leq a_1,a_2\leq 2\times 10^9,-2\times 10^9 \leq b_1,b_2,L,R \leq 2\times 10^9,L \le R$。

# 题目思路

观察到 $a$ 大，等差数列在 $[L,R]$ 之间的项数就很少。反之亦然。

所以考虑根号分治。显然阈值 $B=\sqrt{2\times 10^9}\approx44722$。

为了方便，另 $a_1\geq a_2$。

- $a_1\leq B$

循环节长度为 $\operatorname{lcm}(a_1,a_2)$ 很显然，那么我们找到第一个重复出现的数即可。

又因为循环节长度为 $\operatorname{lcm}(a_1,a_2)$，所以我们枚举前 $\dfrac{\operatorname{lcm}}{a_1}$ 个在 $a_1k+b_1$ 中的数即可找到第一个重复的数。我一开始实现的时候保守了枚举了 $a_2$ 个，但是我们令 $a_1\geq a_2$，所以其实范围是差不多的。

知道重复的数 $x$ 之后，答案就是 $\lceil\dfrac{R-x+1}{\operatorname{lcm}}\rceil$。

- $a_1\gt B$

这是很简单的，因为公差大，所以项数不多，直接枚举 $a_1k+b_1$，判断是否在 $a_2k+b_2$ 中即可。

---

实现的时候注意一下开始的位置应该是 $\max\{b_1,b_2,L\}$。然后自己微调一下变成等差数列中的某个数就行。

开始循环的位置是 `ll start = (max({b1, b2, L}) - b1 + a1 - 1) / a1 * a1 + b1;`。

# 完整代码

$15\ \tt{ms}$ 是目前 CF 最优解了。正解是 exgcd。

[CF submission 247832379](https://codeforces.com/contest/710/submission/247832379)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int B = 44722;
ll a1, b1, a2, b2;
ll L, R;
int main()
{
    cin >> a1 >> b1 >> a2 >> b2 >> L >> R;
    if (a1 <= a2)
        swap(a1, a2), swap(b1, b2);
    ll start = (max({b1, b2, L}) - b1 + a1 - 1) / a1 * a1 + b1;
    if (a1 <= B)
    {
        ll Lcm = a1 / __gcd(a1, a2) * a2;
        for (ll i = start, j = 1; i <= R && j <= Lcm / a1 + 5; i += a1, j++)
        {
            if ((i - b2) % a2)
                continue;
            return cout << ((R - i + 1) + (Lcm - 1)) / Lcm << endl, 0;
        }
        cout << 0 << endl;
    }
    else
    {
        int ans = 0;
        for (ll i = start; i <= R; i += a1)
            ans += !((i - b2) % a2);
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：LYYY (赞：1)

## 这是一道扩展欧几里德算法裸题.

### STEP1

由题目中的式子

$$a_{1}k' + b_{1} = a_{2}l' + b_{2}$$

可得

$$a_{1}k' - a_{2}l' = b_{2} - b_{1}$$

然后我们就可以套用exgcd了.不过我为了方便令exgcd的参数不能是负数,所以要进一步转化为

$$a_{1}k' + a_{2}l'' = b_{2} - b_{1}$$

其中

$$l'' = -l'$$

然后不要忘记根据裴蜀定理检验是否存在整数解.

### STEP2

接下来就是细节的处理了(蒟蒻我在这里挂了无数次).

我们设$kk$表示$k'$的最小改变量,使存在一个整数$y'$使等式依然成立.同理,也设$yy$为$y'$的最小改变量.

我们发现,$k'$每增加$kk$,$l'$就增加$ll$.

所以,目前所有的限制条件就变成了

$$max\left \{  \frac{L-b_{1}}{a_{1}},0\right \} \leq k' \leq \frac{R-b_{1}}{a_{1}}$$

$$max\left \{  \frac{L-b_{2}}{a_{2}},0\right \} \leq l' \leq \frac{R-b_{2}}{a_{2}}$$

所以只要同时满足以上条件就行了.(反正写起来很恶心就对了QAQ)

代码:

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long LL;

//-----------------------------------------函数↓
LL exgcd(LL a,LL b,LL &x,LL &y)
{
	if(!b){return x=1,y=0,a;}
	LL dd=exgcd(b,a%b,y,x);
	return y-=a/b*x,dd;
}

//-----------------------------------------main()↓
int main()
{
	LL a1,a2,b1,b2,L,R,k,l,kk,ll,l1,r1,l2,r2,x,gcd,lcm;
	
	//-----------------------------------------STEP1↓
	scanf("%I64d%I64d%I64d%I64d%I64d%I64d",&a1,&b1,&a2,&b2,&L,&R);
	gcd=exgcd(a1,a2,k,l),lcm=a1*a2/gcd;
	if((b2-b1)%gcd)
	{
		puts("0");
		return 0;
	}
	
	//-----------------------------------------STEP2↓
	k*=(b2-b1)/gcd,kk=lcm/a1;
	l*=(b1-b2)/gcd,ll=lcm/a2;
	
	l1=max(0ll,(L-b1)/a1+(L-b1>0?(!!((L-b1)%a1)):0)),r1=(R-b1)/a1-(R-b1<0?(!!((R-b1)%a1)):0);
	l2=max(0ll,(L-b2)/a2+(L-b2>0?(!!((L-b2)%a2)):0)),r2=(R-b2)/a2-(R-b2<0?(!!((R-b2)%a2)):0);
	/*
	l1,r1是k的两个限制,l2,r2是l的两个限制.
	
	两个'!'的意思是说:不为0就变成1,为0则还是0.
	
	不能-1后取模后+1的方法,因为有负数!
	*/
	
	x=max((l1-k)/kk,(l2-l)/ll);//优先满足更严格的限制.
	k+=x*kk,l+=x*ll;
	if(k<l1||l<l2) k+=kk,l+=ll;//上面的方法求出来的有可能小于下限,所以还要调整.
	if(k>r1||l>r2)
	{
		puts("0");
		return 0;
	}
	printf("%I64d",min((r1-k)/kk,(r2-l)/ll)+1);//优先满足更严格的限制.
	return 0;
}
```

 _谢谢阅览！_ 

---

## 作者：Mashu77 (赞：0)

题意：求在 $[L,R]$ 之间有多少个整数 $K$ 满足 $K=a_1x+b_1=a_2y+b_2$，其中 $x,y$ 为自然数，即是正数。

题解：
很容易想到将等式移项，变为 $a_1x+a_2(−y)=b_2−b_1$。

那么很明显可以用扩欧来求出一组 $x,y$ 的特解，并将特解移至自然数范围内的最小解。

因为原式是等式，接下来我们只需要关注其中一个解，例如 $x$。

设扩欧求出的 $x$ 的通解为 $x_0+k×dx$，其中 $dx=a_2/\gcd$，因为特解 $x_0$ 是摸 $dx$ 下最小自然数解，所以 $k$ 也为自然数。



题目要求的是 $[L,R]$ 之间有多少个整数 $K$ 满足 $K=a_1x+b_1$，

将通解代入，即求 $[L,R]$ 之间有多少个整数 $K$ 满足 $K=(a_1dx)k+a_1x_0+b_1$。

那么最后就是求有多少 $k$ 能让整数落于 $[L,R]$，因为 $k$ 连续，

所以直接算不大于 $R$ 的最大 $k$ 和不小于 $L$ 的最小 $k$ 即可。

写成公式就是 $⌊R−(a_1x_0+b_1)a_1dx⌋−⌈L−(a_1x_0+b_1)a_1dx⌉+1$。

但要注意可能会除出来负数，因为 $k$ 为自然数，所以必须 $k\ge 0$。

```cpp
#include "stdafx.h"
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define int long long
#define PII pair<int,int>
#define ff long double
int n, m, k, T;
int a1, a2, b1, b2, l, r;
// 辗转相除法求最大公因数
int gcd(int a,int b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

int _gcd(int a1, int a2)
{
	if(a1<a2) return gcd(a1,a2%a1);
	else return gcd(a2,a1%a2);
}
// 辗转相除法求最大公因数，加系数x，y
int exgcd(int a,int b,int &x,int &y) {
    int ret, tmp;
    if (!b) {x = 1, y = 0; return a;}
    ret = exgcd(b, a % b, x ,y);
    tmp = x; x = y; y = tmp - a / b * y;
    return ret;
}
void solve() {
    cin >> a1 >> b1 >> a2 >> b2 >> l >> r;
    if ((b2 - b1) % _gcd(a1, a2)) {		// 无解
        cout << 0; return;
    }
    // a1 * x + b1 = a2 * y + b2
    // a1 * x - a2 * y = b2 - b1;
    int x, y;
    int d = exgcd(a1, -a2, x, y);
    x *= (b2 - b1);// y *= (b2 - b1);
    x /= d;// y /= d;
	// 此时， x，y为一组特解
	cout<<"d="<<d<<",x="<<x<<", y="<<y<<endl;
    int dx = abs(a2 / d), dy = abs(a1 / d);
	cout<<" dx="<<dx<<endl;
	//x = (x % dx + dx) % dx;//先让x落于自然数范围,x>0
    ((x %= dx) += dx) %= dx;
	cout<<" dx="<<dx<<", dy="<<dy<<endl;
    y = (a1 * x - b2 + b1) / a2;
    if (y < 0)	// 即是 b1 - b2 <0
        ((y %= dy) += dy) %= dy, x = (a2 * y + b2 - b1) / a1;
	// 已知a1>0,a2>0,  又 b2 - b1>0, 故此时x，y均为正数
	// x为最小正整数解，通解中 x+k*dx,  必须k>0, 因为题目要求k'=x+k*dx>=0
    int L = max(0ll, (int)ceil((l - a1 * x - b1) * 1.0 / (a1 * dx)));// 所以必须 L>=0
    int R = (int)(floor(1.0 * (r - a1 * x - b1) / (a1 * dx)));
	cout<<"L="<<L<<",x="<<x<<", y="<<y<<endl;
    cout << max(0ll, R - L + 1);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	FILE *fi;
	freopen_s(&fi,"CF710Din.txt","r",stdin);
    solve();
    return 0;
}

---

