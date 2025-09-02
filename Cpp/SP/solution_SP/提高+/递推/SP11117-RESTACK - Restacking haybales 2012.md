# RESTACK - Restacking haybales 2012

## 题目描述

Farmer John has just ordered a large number of bales of hay. He would like  
to organize these into N piles (1 <= N <= 100,000) arranged in a circle,  
where pile i contains B\_i bales of hay. Unfortunately, the truck driver  
delivering the hay was not listening carefully when Farmer John provided  
this information, and only remembered to leave the hay in N piles arranged  
in a circle. After delivery, Farmer John notes that pile i contains A\_i  
bales of hay. Of course, the A\_i's and the B\_i's have the same sum.

Farmer John would like to move the bales of hay from their current  
configuration (described by the A\_i's) into his desired target  
configuration (described by the B\_i's). It takes him x units of work to  
move one hay bale from one pile to a pile that is x steps away around the  
circle. Please help him compute the minimum amount of work he will need to  
spend.

# 题解

## 作者：桃夭 (赞：12)

## **这题是一道……奥数~~水~~题啊qwq**
**解题思路来源于之前看到过的一个博客qwq，很巧妙的解法，网址忘记了QAQ若有侵权请私信我。**

### **[更好的阅读体验请戳 ~~爆~~ 我quq](https://www.luogu.org/blog/lison-lql/solution-sp11117)**

### ** 【题目大意】**

**FJ买了一些干草堆，他想把这些干草堆分成N堆(1<=N<=100,000)摆成一圈，其中第i堆有B_i数量的干草。不幸的是，负责运货的司机由于没有听清FJ的要求，只记住分成N堆摆成一圈这个要求，而每一堆的数量却是A_i(1<=i<=N)。当然A_i的总和肯定等于B_i的总和。**

**FJ可以通过移动干草来达到要求，即使得A_i=B_i，已知把一个干草移动x步需要消耗x数量的体力，相邻两个干草堆之间的步数为1。**

**请帮助FJ计算最少需要消耗多少体力才能完成任务。**

### 【解法】

**设Fi为从i到i+1运Fi堆草，Fn为n~1运的草的数目。
Ai为放错的草堆，Bi为正确的草堆。**

**可以得出递推式：**

	A1-F1+Fn=B1
	A2-F2+F1=B2
	A3-F3+F2=B3
    ............
	An-Fn+F1=Bn
**移项，整理成Fi的式子：**

	F1=A1-B1+Fn
	F2=A2-B2+F1
	F3=A3-B3+F2
	..........
	Fｎ=An-Bn+F1
**代入，得：（注意Fn要特殊处理）**

	F1=A1-B1+Fn
	F2=A2-B2+A1-B1+Fn
	F3=A3-B3+A2-B2+A1-B1+Fn
	..........
	Fｎ=Fn
**令Gi=Ai-Bi（i=1，2，3......n）的累加值，并加上绝对值：**

	|F1|=|A1-B1-(-Fn)|
	|F2|=|G(i)-(-Fn)| (1<=i<=2)
	|F3|=|G(i)-(-Fn)| (1<=i<=3)
	.......
	|Fn|=|Fn|
**G(i)可以由一个递推式得到：G(i)=G(i-1)+Ai-Bi,特别的，令G(0)=0。接下来，因为|X-Y|(X,Y∈Z)的几何意义为数轴上X的点到Y点的距离。累加可得：Ans=|G1-(-Fn)|+|G2-(-Fn)|+|G3-(-Fn)|+......+|G(n-1)-(-Fn)|+|0-(-Fn)|
就变成了在数轴上求一个点，使得该点到各点的距离之和最小。**
# 接下来就很nice了
**这个点，很~~巧妙~~的，就是这组数据的中位数，易得，中位数为-Fn，答案就出来了。时间复杂度O（N log N+N）**
# ~~整齐的~~Code
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a,b,f;
int g[100010];
long long ans=0;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d",&a,&b);
        g[i]=g[i-1]+a-b;//递推求Gi
    }
    sort(g+1,g+n+1);
    f=-g[(n/2)+1];//求中位数
    for (int i=1;i<=n;++i)
    {
        ans+=abs(g[i]+f);//累加
    }
    cout<<ans<<"\n";
    return 0;
}

```
## **留个赞可好qwq**

---

## 作者：Sincerin (赞：1)

[题目传送门！](https://www.luogu.com.cn/problem/SP11117)

[更好的阅读体验？](https://www.luogu.com.cn/blog/sincerin520/solution-sp11117)

题外话：[双倍经验](https://www.luogu.com.cn/problem/P3051)。

## 题意

雪豹的农场里有 $n$ 个仓库围成了一个**环**，每个仓库都有一个编号 $i \in [1,n]$。他买了一些干草堆，希望在第 $i$ 号仓库存放 $B_i$ 堆干草。奈何司机师傅表示这是另外的价钱，然后胡乱卸完货就走人了，于是雪豹只能自己花时间调整。现在第 $i$ 号仓库有 $A_i$ 堆干草，雪豹只能在第 $i$ 号仓库左右相邻的两个仓库中拿取干草堆来调整 $i$ 号仓库的数量，每运送一堆干草，雪豹要消耗 $1$ 点体力。求使得 $\forall i \in [1,n]$，仓库 $i$ 存放干草堆数变为 $B_i$ 的最小体力。

- $1 \leq n \leq 100000 \ , 1 \leq A_i,B_i \leq 1000$。

- 保证 $\sum_{i=1}^n{A_i}=\sum_{i=1}^n{B_i}$。

## 解析

这题算是环形均分纸牌的加强版。虽然不是均分了，但还是老套路（没做过均分纸牌的同学可以先看看[P2512](https://www.luogu.com.cn/problem/P2512)）。

我们只考虑向前传递的过程，我们可以进行贪心：

设第 $i$ 号仓库向 第 $i-1$ 号仓库运了 $C_i$ 堆干草， $i+1$ 号仓库向 第 $i$ 号仓库运了 $C_{i+1}$ 堆干草。

运之前 $i$ 号仓库有 $A_i$ 堆干草，现在有 $B_i$ 堆，可得：

$$A_i-C_i+C_{i+1}=B_i$$

移项，得：

$$C_{i+1}-C_i=B_i-A_i$$

观察柿子，容易发现：

$$C_{2}-C_1=B_1-A_1 $$

$$C_{3}-C_2=B_2-A_2 $$

$$\dots$$
$$C_{k}-C_{k-1}=B_{k-1}-A_{k-1} $$


对上述柿子求和，可得：

$$C_{k}-C_{1}=\sum_{i=1}^{k-1}(B_i-A_i)$$

即

$$C_{k}=C_{1}- \sum_{i=1}^{k-1}(A_i-B_i)$$

使用前缀和优化一下：

我们不妨设 $S_k=\sum_{i=1}^{k}(A_i-B_i)$，此时 $C_{k}=C_{1}- S_{k-1}$。

我们发现要使 $\sum{\left| C \right|}$ 最小化，实际上就是一个[货仓选址](https://www.acwing.com/problem/content/106/)问题，当 $C_1$ 为序列 $S$ 的中位数时，$\sum{\left| C \right|}$ 最小。证明可以看看[这里](https://www.luogu.com.cn/blog/wzcwj/p3051-ti-xie)。

静态区间第 $k$ 小其实是可以通过归并和快排过程中进行比较的思想达到 $\Theta(n)$ 的，`C++ STL` 的 `nth_element()` 就是这么实现的。但是我比较懒，直接排序了。

时间复杂度 $\Theta(n \log n)$。

#### 注意：

- 中位数需要上取整，即 $\lceil \frac{n}{2}\rceil$。

- 对于取在中位数左边或右边，$C_i$ 会出现对应的正数或负数取值，最后统计的时候要取绝对值。

- 最后统计的序列应该是 $\sum_{i=2}^{n+1}{\mid C_i\mid}$，$C_i$ 是 $i$ 号仓库向 $i-1$ 号仓库运的堆干草，$\mid C_{n+1} \mid$ 也可以表示 $1$ 和 $n$ 之间的运输关系。若想使用 $\sum_{i=1}^{n}{\mid C_i\mid}$ 来统计，应该重新开一个数组保存前缀和，因为排序会改变前缀和顺序。

对于第 $3$ 条，在此解释一下：

因为 $\sum_{i=1}^n{A_i}=\sum_{i=1}^n{B_i}$，所以 $S_n=\sum_{i=1}^n{(A_i-B_i)}=0$，排序后会来到 $S_1$ 的位置，导致答案少统计一个原来的 $S_1$，同时少统计一个排序后的 $S_n$。

## AC Code

```cpp
//C++20 O2 925B 90ms 6.60MB
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cmath>
#define _ 1
using namespace std; 
#define int long long//防止见祖宗 
#define ri register int
const int N=100001;
int n,k,a[N],b[N],c[N],s[N],ans,res;
inline void read(int &n)
{
	register bool f=false;
	register char c=getchar();
	while(c<'0'||c>'9'){f^=(c=='-');c=getchar();}
	while(c>='0'&&c<='9'){n=(n<<3)+(n<<1)+(c^48);c=getchar();}
	if(f) n=-n;
}
inline void print(int n)
{
	if(n<0){n=-n;putchar('-');}
	if(n>9) print(n/10); 
	putchar(n%10+'0');
}
signed main(void)
{
	read(n);
	for(ri i=1;i<=n;++i)
	{
		read(a[i]); read(b[i]); 
		a[i]+=a[i-1];//前缀和 of a
		b[i]+=b[i-1];//前缀和 of b
		s[i]=a[i]-b[i];//前缀和 of a-b
	}  
	sort(s+1,s+n+1);//排序 
	k=(n+1)>>1; c[1]=s[k];//中位数上取整 
	for(ri i=2;i<=n+1;++i) 
	{
		c[i]=c[1]-s[i-1]; //计算Ci 
		ans+=abs(c[i]);//统计
	}
	print(ans);
	putchar('\n'); 
	return !(0^_^0);//完结撒花！ 
}
```
[AC Record](https://www.luogu.com.cn/record/129572364)


另一种写法：

```cpp
signed main(void)
{
	read(n);
	for(ri i=1;i<=n;++i)
	{
		read(a[i]);
		read(b[i]); 
		a[i]+=a[i-1];
		b[i]+=b[i-1];
		d[i]=s[i]=a[i]-b[i];//d=s
	}  
	sort(s+1,s+n+1);
	k=(n+1)>>1; c[1]=s[k];
	for(ri i=1;i<=n;++i) 
	{
		c[i]=c[1]-d[i-1];//原来的前缀和d
		ans+=abs(c[i]);
	}
	print(ans);
	putchar('\n'); 
	return !(0^_^0);
}
```

看明白了吗？来做做[练习题](https://www.luogu.com.cn/discuss/639580)吧！

---

## 作者：zzhbpyy (赞：0)

这道题和[糖果传递](https://www.luogu.com.cn/problem/P2512)思路类似。假设第 $i$ 个人给第 $i+1$ 个人 $x_i$ 数量的干草，特别的第 $n$ 个人给第 $1$ 个人 $x_n$ 数量干草，所以答案为 $\sum_{i=1}^nx_i$。

设 $m_i$ 为 $a_i-b_i$，容易得出 $m_{i+1}=x_i-x_{i+1},i\in [1,n-1]$。

经过移项代入可得：
$$
x_i=x_1-\sum_{j=1}^{i-1}m_j
$$
令 $m$ 的前缀和数组为 $M$，则答案为 $\left|x_1\right|+\sum_{i=1}^{n-1}\left|x_1-M_i\right|$。

由初中绝对值知识可以知道当 $x_1$ 为 $0,M_1,M_2,M_3,\cdots,M_{n-1}$ 的中位数时取最值。

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m[100005],c[100005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n;
	for(int i=1,a,b;i<=n;i++){
		cin>>a>>b;m[i]=b-a;
	}
	c[1]=0;
	for(int i=2;i<=n;i++)c[i]=c[i-1]+m[i-1];
	sort(c+1,c+n+1);
	int x=c[(n+1)/2],ans=0;
	for(int i=1;i<=n;i++){
		ans+=abs(c[i]-x);
	}cout<<ans;
}
```

---

## 作者：chl090410 (赞：0)

## The Solution to SP11117 RESTACK - Restacking haybales 2012

题外话：七倍经验

[
SP11117 RESTACK - Restacking haybales 2012](https://www.luogu.com.cn/problem/SP11117)

[P2125 图书馆书架上的书](https://www.luogu.com.cn/problem/P2125)

[UVA11300 Spreading the Wealth](https://www.luogu.com.cn/problem/UVA11300)

[P5817 分金币](https://www.luogu.com.cn/problem/P5817)

[P2512 糖果传递](https://www.luogu.com.cn/problem/P2512)

[P4016 负载平衡问题](https://www.luogu.com.cn/problem/P2512)

[P3051 Haybale Restacking G](https://www.luogu.com.cn/problem/P3051)

### Description

[题目传送门](https://www.luogu.com.cn/problem/SP11117)

### Solution

设第 $i$ 堆草要向第 $i+1$ 堆草运送 $q_i$ 个干草，摆错的第 $i$ 堆草有 $a_i$ 个干草，FJ 希望第 $i$ 堆草有 $b_i$ 个干草。

于是就有以下式子：$b_i=a_i-q_i+q_{i-1}$，即 $a_i-b_i=q_i-q_{i-1}$（特别的，$a_1-b_1=q_1-q_n$）。

我们令 $i=2$ 即可得 $q_2=q_1+(a_2-b_2)$。

同理，$q_3=q_2+a_3-b_3=q_1+(a_2-b_2)+(a_3-b_3)$

我们令 $x_1=0$，其余的 $x_i=a_i-b_i$，而数组 $s$ 为数组 $x$ 的前缀和数组。

于是就有 $q_i=q_1+s_i$，但无论往哪个方向搬所消耗的体力值均大于 $0$，所以处理第 $i$ 堆干草消耗的体力值为 $|q_1+s_i|$。

而要求所消耗的体力值的最小值，即为求 $\large\sum_{i=1}^{n} |q_1+s_i|$ 的最小值，而这个最小值在 $q_1$ 等于 $s$ 数组的中位数时取到。

总时间复杂度为 $O(n\times\log n)$（对 $s$ 数组的排序也算了）。

### AC code 如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,p,k,u,x,y,z,a[1000005],q[1000005],ls[1000005];
signed main() {
	cin>>n; 
	for(int i=1;i<=n;i++){
	   	cin>>a[i]>>ls[i];
	}
	q[1]=0;
	for(int i=2;i<=n;i++){
	   	q[i]=q[i-1]+(a[i]-ls[i]);
	}
	sort(q+1,q+n+1);
	for(int i=1;i<=n;i++){
	   	y+=abs(-q[(n+1)/2]+q[i]);
	}
	cout<<y;
    return 0;
}

---

## 作者：mayike (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/SP11117)

~~没做[**此题**](https://www.luogu.com.cn/problem/P1031)的不要看~~

## 题意
有 $n$ 个干草堆组成一个环，在第 $i$ 个位置有 $a[i]$ 个干草堆，可以将任意位置的干草堆向前或向后移动若干个，使第 $i$ 个位置有 $b[i]$ 个干草堆，询问最少需要移动多少个干草堆。

## 思路

实则就是[**均分纸牌**](https://www.luogu.com.cn/problem/P1031)的升级版，其贪心思想也是本题要用到的。

即可规定一个方向，这里我规定向左，每堆牌都向左传，变成 $b[i]$ 个，若本不足 $b[i]$ 个咋办呢，那就向左索要，其实等价于传负数个，详细看这位大佬的 [**blog**](https://blog.csdn.net/qq_46105170/article/details/103790633)。

---

##### 注：以上链接博客均非本人所有

---

那么我们可设每个位置原有 $a[i]$ 个，要变成 $b[i]$ 个，向左传递（左右都可以，单一方向即可，这里规定向左）$x[i]$ 个。

则所求值为 $\sum _ {i = 1}^n\min(| x[i] |)$。

由题意我们可知：

$$b[1]=a[1]+x[2]-x[1]$$

$$b[2]=a[2]+x[3]-x[2]$$

依次推得当 $1 \le i < n$ 时：

$$b[i]=a[i]+x[i+1]-x[i]$$

$$b[n]=a[n]+x[1]-x[n]$$

可得：

$$x[2]=b[1]+x[1]-a[1]$$

$$x[3]=b[2]+x[2]-a[2]=b[2]+(b[1]+x[1]-a[1])-a[2]$$

$$b[2]+(b[1]+x[1]-a[1])-a[2]=(b[1]+b[2])-a[1]-a[2]+x[1]$$

即：

$$x[3]=(b[1]+b[2])-a[1]-a[2]+x[1]$$

对于 $2 \le i \le n$ 有：

$$x[i]=\sum_{j=1}^{i-1}(b[j]-a[j]) + x[1]$$

$$x[1]=\sum_{j=1}^{n}(b[j]-a[j]) + x[1]$$

不妨设：

$$c[1]=a[1]-b[1]$$

$$c[2]=a[1]+a[2]-(b[1]+b[2])$$

对于 $1 \le i \le n$ 则有：

$$c[i]=\sum_{j=1}^{i}(a[j]-b[j])$$

即可知道：

$$x[2]=x[1]-c[1]$$

$$x[3]=x[1]-c[2]$$

当 $2 \le i \le n$ 时：

$$x[i]=x[1]-c[i-1]$$

$$x[1]=x[1]-c[n]$$

所以：

$$\sum _ {i = 1}^n\min(| x[i] |)$$

等价于：

$$\sum _ {i = 1}^n\min(| x[1]-c[i] |)$$

放在数轴上来讲就是点 $x[1]$ 到 $c[i]$ 的距离和的最小值，此处 $1 \le i \le n$。

那么 $x[1]=c[\frac{n+1}{2}]$ 时就一定可取最小值，这个就不说明了，自己思考一下为什么。

对于 $1 \le i \le n$，$c[i]$ 我们是已知的。那么，本题~~完~~。

等等，还有代码！

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c[100001],mid;long long ans;
int main(){
	//经验: p2512 UVA11300 p3051 p4016 p2125 p5817 SP11117
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){cin>>a>>b;c[i]=c[i-1]+a-b;}
	sort(c+1,c+1+n);mid=c[(n+1)/2];
	for(int i=1;i<=n;i++)ans+=abs(mid-c[i]);
	cout<<ans<<'\n';
}
```

---

## 作者：ReeChee (赞：0)

## Problem

[题目链接](https://www.luogu.com.cn/problem/SP11117)

有 $n$ 个干草堆组成一个环，在第 $i$ 个位置有 $A_i$ 个干草堆，可以将任意位置的干草堆向前或向后移动若干个，使第 $i$ 个位置有 $B_i$ 个干草堆，询问最少需要移动多少个干草堆。

$1\leq n\leq10^5$，$1\leq A_i,B_i\leq10^3$。

## Algorithm #1 网络流 WA

考虑到 $n$ 的范围，会寄掉。

## Algorithm #2 贪心 AC

由[均分纸牌](https://www.luogu.com.cn/problem/P1031)可知，在推式的时候可以忽略接下来的干草堆的数量变成负数的问题。

由于组成了一个环，我们可以指定一个方向传递干草堆。

设 $T_i$ 为向左传递干草堆的数量。

则有 $B_i=A_i+T_{i+1}-T_i$。

转化一下 $T_{i+1}=B_i-A_i+T_i$。

$$
\begin{cases}
T_2=B_1-A_1+T_1=\sum^{1}_{i=1}{(B_i-A_i)}\\
T_3=B_2-A_2+T_2=B_2-A_2+(B_1-A_1+T_1)=\sum^{2}_{i=1}{(B_i-A_i)}+T_1\\
\cdots
\end{cases}
$$

那么当 $2\leq i\leq n$ 时，有 $T_i=T_1+\sum^{i-1}_{j=1}{(B_j-A_j)}$。

用 $P_i$ 表示 $\sum^{i-1}_{j=1}{(A_j-B_j)}$，特别规定 $P_1=0$。

则 $T_i=T_1-P_i$。

答案即为：

$$
\begin{aligned}

ans&=\sum_{i=1}^{n}{\left |T_i\right |}\\
&=\sum_{i=1}^{n}{\left |T_1-P_i\right |}

\end{aligned}
$$

由于有些向左传，有些向右传，所以答案可能为负数，要加绝对值号。

现在我们需要取 $T_1$ 的值使答案最小，而由[输油管道问题](https://www.luogu.com.cn/problem/P1862)可知，当 $T_1$ 为 $P$ 的中位数时答案最小。

## Code

```
// 省略了 1kb 的火车头
ll n, a[N], p[N], b[N], sum, ans;
int main() {
  n = read();
  F(i, 1, n) 
    a[i] = read(), b[i] = read();
  F(i, 1, n) {
    p[i] = sum;
    sum += a[i] - b[i];
  }
  sort(p + 1, p + 1 + n);
  F(i, 1, n)
  ans += abs(p[(n + 1) / 2] - p[i]);
  printf("%lld\n", ans);
  return 0;
}
```

---

