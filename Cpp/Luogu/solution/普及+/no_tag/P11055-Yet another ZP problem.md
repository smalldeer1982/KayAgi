# Yet another ZP problem

## 题目描述

从左到右排列着 $n$ 个点，编号分别为 $1,2,\dots,n$。

你要在他们之间连一些边，记边集为 $E=\{(x,y)\ |\ 1\leq x<y\leq n\}$。

我们称边集 $E$ 满足限制 $[l,r]$，当且仅当存在 $(x,y)\in E$ 使得 $[x\in[l,r]]+[y\in[l,r]]=1$。

基础地，我们希望对所有 $1\leq i\leq n$ 满足限制 $[i,i]$。

在此基础上，输入还给定了额外的 $m$ 个限制 $[l_i,r_i]$（$1\leq l_i<r_i\leq n$ 并且 $[l_i,r_i]\neq [1,n]$）。

请问 $|E|$ 最小是多少，在此基础上给出一组合法构造。可以证明，合法的 $E$ 总是存在的。

对于形如 $[P]$ 的表达式，当且仅当命题 $P$ 为真时其取值为 $1$，否则取值为 $0$。

## 说明/提示

### 样例解释

对于限制 $[1, 1]$，存在边 $(1, 4)$ 使得 $[1 \in [1, 1]] + [4 \in [1, 1]] = 1$。

对于限制 $[3, 4]$，存在边 $(1, 4)$ 使得 $[1 \in [3, 4]] + [4 \in [3, 4]] = 1$。

对于限制 $[2, 2]$，存在边 $(2, 3)$ 使得 $[2 \in [2, 2]] + [3 \in [2, 2]] = 1$。

### 数据范围

对于所有数据，保证 $3\leq n\leq 10^4$，$0\leq m\leq 10^5$，$1\le l_i<r_i\le n$，$[l_i,r_i]\ne [1,n]$。

| 测试点编号 | 特殊性质 |
| :----------: | :----------: |
| $1\sim 5$ | $n,m\le 5$ |
| $6\sim 7$ | $m=0$ |
| $8\sim 11$ | $r_i<l_{i+1}$ |
| $12\sim 14$ | $l_i=1$ |
| $15\sim 20$ | 无 |

**对于第 $i$ 个测试点，保证 $n$ 的奇偶性与 $i$ 的奇偶性相同，$m$ 的奇偶性与 $\lfloor\frac{i}{2}\rfloor+1$ 的奇偶性相同。**

## 样例 #1

### 输入

```
4 3
1 2
3 4
1 2```

### 输出

```
2
1 4
2 3```

# 题解

## 作者：Milthm (赞：12)

赛时被创飞了，所以我仔细地思考了一下这种题应该怎么做。

首先出题人比较良心，在题目名就告诉我们这是一道诈骗题，当然这不能成为我们做题的依据。

读完题，我们发现这道题是构造题，所以先想想这个最小的局面在什么时候会产生。因为这题的基础限制，每个数都至少要被用一次，所以答案最少也就是 $\lceil \frac{n}2 \rceil$。

到这里我们可能会想到根据给定的特殊限制去做，但是经过尝试之后发现这很难，因为多个限制之间的相交很难处理。那么这个题要么是我太菜了不会处理，要么这个方向是错的。

如果不是前面那种情况的话，那基本上就只剩一种可能了，就是这个特殊限制其实没用，也就是说存在一种构造使得任意的特殊限制都能满足。

从最理想的情况（即答案为 $\lceil \frac{n}2 \rceil$）考虑，那么我们这 $\lceil \frac{n}2 \rceil$ 对整数必须要有一些特殊的性质才可以。看看分母上这个 $2$，再想想这个“只有一个端点在区间内”的限制，发现其实可以用很多个小区间（长度小于等于 $\frac{n}2$）依次盖住这 $n$ 个点，这样对于每个特殊限制总有一个小区间的左或右端点在区间之内。

又因为小区间的数量要尽可能小，所以我们只需要输出所有满足 $1\le i \le \lfloor \frac{n}2 \rfloor $ 的 $(i,i+\lfloor \frac{n}2 \rfloor)$ 即可（奇数的话还要补一个 $(1,n)$）。

然后我们就以时空复杂度均 $O(n)$ 的。短到难以置信的代码 AC 了这道题，这就是诈骗题的魅力，~~下次别出了~~。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	cout<<(n+1)/2<<'\n';
	for(int i=1;i<=n/2;++i)cout<<i<<" "<<i+n/2<<'\n';
	if(n&1)cout<<1<<" "<<n<<'\n';
	return 0;
}
```

~~当然，这种题能猜到结论更好，但这并不是每个人都能做到的。~~

---

## 作者：yuxuzhehuan (赞：5)

# [P11055](https://www.luogu.com.cn/problem/P11055)
# 题目描述
从左到右排列着 $n$ 个点，编号分别为 $1,2,\dots,n$。

你要在他们之间连一些边，记边集为 $E=\{(x,y)\ |\ 1\leq x<y\leq n\}$。

我们称边集 $E$ 满足限制 $[l,r]$，当且仅当存在 $(x,y)\in E$ 使得 $[x\in[l,r]]+[y\in[l,r]]=1$。

基础地，我们希望对所有 $1\leq i\leq n$ 满足限制 $[i,i]$。

在此基础上，输入还给定了额外的$m$个限制 $[l_i,r_i]$（$1\leq l_i<r_i\leq n$ 并且 $[l_i,r_i]\neq [1,n]$）。

请问 $|E|$ 最小是多少，在此基础上给出一组合法构造。可以证明，合法的 $E$ 总是存在的。

对于形如 $[P]$ 的表达式，当且仅当命题 $P$ 为真时其取值为 $1$ ，否则取值为 $0$。
# 分析
## Step1 通解
比赛时毫无想法，后来想到可以构造一个通解。
$$
mid=\lceil\frac{n}{2}\rceil,cnt=\lfloor\frac{n}{2}\rfloor
\\
E=\{(x,x+mid)\ |x \in [1,cnt] 且 x\in Z\}
$$
若 $n$ 为奇数，$E$ 再加上 $(1,mid)$ 即可。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,mid,cnt;
signed main()
{	cin>>n;
	mid=ceil(1.0*n/2),cnt=n/2;
	printf("%d\n",mid);
	if(n%2==1)	printf("%d %d\n",1,mid);
	for(int i=1;i<=cnt;i++)	printf("%d %d\n",i,i+mid);
	return 0;
}
```
## Step2 证明
考虑限制 $[l,r]$，令 $len=r-l+1$，由于 $[l_i,r_i]\ne [1,n]$，故 $len<n$。
### 当 $len<mid$
至多覆盖了一条边，即 $n$ 为奇数时的 $(1,mid)$，而此时 $1$ 必定与 $mid+1$ 连边，故满足限制。
### 当 $len \ge mid$
此时必有一条边在区间中。

假如不满足限制。

这必然满足 $r-mid-(l+mid)=-1$，则 $len=2\times mid$ ，将 $mid=\lceil\frac{n}{2}\rceil\ge\frac{n}{2}$ 带入可得 $len\ge n$，假设不成立。

综上该通解成立。

如果有误，请各位大佬指出。

---

## 作者：dyc2022 (赞：4)

首先求出答案的下界，显然是 $\lceil \frac{n}{2}\rceil$，原因是每一个节点至少要连一条边，一条边连接两个节点。

接下来，由于这是一道诈骗题，所有我们考虑就构造通解。

**结论：对于 $i \le \lceil \frac{n}{2}\rceil$，有 $i$ 向 $i+\lfloor \frac{n}{2}\rfloor$ 连边。**

因为对于任意不等于 $[1,n]$ 的区间，都一定有 $i$ 使得 $i+\lfloor \frac{n}{2}\rfloor$ 或 $i-\lfloor \frac{n}{2}\rfloor$ 不在区间内。

这样一来，所有的区间都可以满足，且每一个点一定有连到边。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int n;
main()
{
    scanf("%lld",&n);
    printf("%lld\n",n+1>>1);
    for(int i=1;i<=n+1>>1;i++)printf("%lld %lld\n",i,i+(n>>1));
    return 0;
}
```

---

## 作者：fish_love_cat (赞：4)

赛时猜结论秒了，但是考虑证明。

---

构造：

对于每一个 $1\le i\le\left \lceil \frac{n}{2} \right \rceil$，我们将 $(i,i+\min(\left \lceil \frac{n}{2} \right \rceil,n))$ 加入边集。总共 $\lceil\frac{n}{2}\rceil$ 条边。

容易发现这样是最优的。

---

证明：

对于每一条边，我们把其两端的点染上同一个颜色（如果被染了两次就有两个颜色）。

容易发现，在上面的构造中任意同色两点中间都夹着至少 $\lfloor\frac{n}{2}\rfloor$ 种颜色。

为了使该构造不合法，必须要将剩下 $\lfloor \frac{n}{2}\rfloor$ 种颜色配对的点加进限制区间。

然后你就发现加进来以后区间必然变成了 $[1,n]$。这是不合法的。

构造成立。

---

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<n/2+n%2<<endl;
    for(int i=1;i<=n/2+n%2;i++)
    cout<<i<<' '<<min(n,i+n/2+n%2)<<endl;
    return 0;
}
```

---

ZP problem = 诈骗题？

骗了我四十分钟（大哭）

---

## 作者：xuan_gong_dong (赞：3)

好难的一道题，看到机房一车的大佬只读入了 $n$ 和 $m$ 就把这题秒了直接让我成小呆呆了。
## 题面
[P11055 Yet another ZP problem](https://www.luogu.com.cn/problem/P11055)
## 分析
记录每一个点作为起点的区间最右段在哪里。

考虑如果该点被某个区间覆盖，该点与区间最右段的后一位连边，如果区间之外的右边全部都被连完了就从头开始找最前面第一个没有连过的点。

但是上述思路可能会重复浪费，考虑如果区间右边连完了且前面也连完了的时候替换掉前面某一个不在该区间的一个匹配好了的点（因为如果不替换掉该点只能与区间里面的点连线了，这包出问题），被替换的点再被标记为未连过就好了。

然后将剩下的没连过的点随便互相连连就可以了。

如果剩下单独剩一个点，随便找个点连都可以。

细节有点多，考场一下就想到做法了，但是代码还是调了老半天。


## Code

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
namespace fasthys{
	inline int read()
	{
		int x(0),f(0);
		char c(getchar());
		while(!isdigit(c))
		{
			f|=c=='-';
			c=getchar(); 
		}
		while(isdigit(c))
		{
			x=(x<<3)+(x<<1)+(c^48);
			c=getchar();
		}
		return f?-x:x;
	}
	inline void write(int x)
	{
		if(x<0)putchar('-'),x=-x;
		if(x>9)write(x/10);
		putchar(x%10+'0');
	}
}
using namespace fasthys; 
int n,m;
int hys[100010];
int book[100010];
pair<int,int>ans[100010];
int tot;
int main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)
	{
		int id,r;
		scanf("%d%d",&id,&r);
		hys[id]=max(hys[id],r);
	}
	int R=0;
	for(int i=1;i<=n;i++)
	{
		while(hys[i]==0||book[i])
		{
			i++;
			if(i>n)break;
		}
		if(i>n)break;	
		R=max(R,hys[i]+1);
		while(book[R]&&R<=n)R++;
		if(R>n)R=1;
		while(book[R])R++;
		if(R==i)
		{
			int tt=ans[1].second;
			int ff=ans[1].first;
			ans[1]=make_pair(tt,R);
			book[R]=1;
			book[ff]=0;
			continue;
		}
		book[i]=1;
		ans[++tot]=make_pair(i,R);
//		cout<<"q"<<i<<R<<endl;
		book[R]=1;
	}
	R=0;
	for(int i=1;i<=n;i++)
	{
		while(book[i])i++;
		R=max(R,i+1);
		while(book[R])R++;
//		cout<<i<<R<<endl;
		if(R<=n)
		{
			ans[++tot]=make_pair(i,R);	
			book[i]=book[R]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(!book[i])	ans[++tot]=make_pair(i,i==n?1:i+1);	
	}
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++)
	{
		if(ans[i].first>ans[i].second)swap(ans[i].first,ans[i].second);
		printf("%d %d\n",ans[i].first,ans[i].second);
	}
	return 0;
}
/*


6
5
1 2
2 3
3 4
4 5
5 6

*/
```

---

## 作者：Double_Light (赞：2)

容易发现是一道构造题。如果要满足基础条件，至少需要 $\lceil\dfrac{n}{2}\rceil$ 条边，保证每个点都有边覆盖。

然后考虑构造一种方案使得加尽量少的边就可以满足额外限制。让我们从加 $0$ 条边开始考虑。

对于 $n$ 为偶数的情况，对于任意的 $1\leq i\leq\dfrac{n}{2}$，$i$ 和 $\dfrac{n}{2}+i$ 连一条边一定是最优的。至于怎么想出来的，一共不就几种看上去可行的结论，一个一个试试呗。

首先发现这个连法一共就只有 $\dfrac{n}{2}$ 条边，所以一定最优。而正确性证明如下：

对于区间 $[l,r]$，如果长度大于等于 $\dfrac{n}{2}$，自然包含了所有边。那么只要 $[l,r]≠[1,n]$，就一定存在一条边只被包含一个点。否则由于长度小于 $\dfrac{n}{2}$，对于任意包含的点 $i$，肯定没有包含 $i+\dfrac{n}{2}$（或 $i-\dfrac{n}{2}$），故得证。

对于 $n$ 为奇数，多连一条 $(1,n)$ 就可以了，证明与上面类似。

---

## 作者：_O_v_O_ (赞：2)

不是哥们。

结论：

对于每个 $\forall1\le i\le \lfloor \frac{n}{2}\rfloor$，$i$ 向 $i+\lfloor\frac{n}{2}\rfloor$ 连一条边，如果 $n\bmod 2=1$，那么 $1$ 再向 $n$ 连一条边。

证明：

很显然这样构造边数是最小的且基本条件已经满足，关键在于正确性。

对于 $n\bmod 2=0$，我们对于每一个 $(l,r)$ 来分类讨论：

- $l\ge \lfloor\frac{n}{2}\rfloor$ 有边 $(l,l-\lfloor \frac{n}{2}\rfloor)$；
- $r\le \lfloor\frac{n}{2}\rfloor$ 有边 $(r,r+\lfloor \frac{n}{2}\rfloor)$；
- $l<\frac{n}{2}$ 且 $r> \lfloor\frac{n}{2}\rfloor$，若 $l\neq 1$ 有边 $(1,\lfloor\frac{n}{2}\rfloor)$，否则有 $(\lfloor\frac{n}{2}\rfloor,n)$。

对于 $n\bmod 2=1$，前 $n-1$ 个已经可以按上面的方法证明了，然后我们就只剩 $r=n$ 的情况了，因为 $(l,r)\neq (1,n)$ 所以直接选择边 $(1,n)$ 就行了。

证毕，代码短的一批：


```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	cout<<ceil(n/2.0)<<endl;
	for(int i=1;i<=n/2;i++) cout<<i<<' '<<i+n/2<<endl;
	if(n&1) cout<<1<<' '<<n<<endl;
	return 0;
}
```

---

## 作者：zyn_ (赞：1)

原来是一道数学题。

### 题面

给定 $n$。设 $E$ 中的每个元素都形如二元组 $(x,y)$（$1\le x\lt y\le n$，$x,y$ 为正整数）。称 $E$ 满足限制 $[l,r]$，当且仅当存在 $(x,y)\in E$ 使得 $[x\in[l,r]]+[y\in[l,r]]=1$。

基础地，我们希望对所有 $1\leq i\leq n$ 满足限制 $[i,i]$。在此基础上，还有额外的 $m$ 个限制 $[l_i,r_i]$（$1\leq l_i<r_i\leq n$ 并且 $[l_i,r_i]\neq [1,n]$）。

证明，对任意指定的 $l_i,r_i$，满足所有限制的 $E$ 的大小的最小值为 $\lceil\dfrac{n}{2}\rceil$。

### 解答

首先由于满足限制 $[i,i]$ 知 $E$ 中的二元组必然包含了所有 $1,2,\dots,n$ 的数，故 $|E|\ge \lceil\dfrac{n}{2}\rceil$。

事实上，令 $k=\lfloor\dfrac{n}{2}\rfloor$，取 $E=\{(1,1+k),(2,2+k),\dots,(n-k,n)\}$ 就能满足所有限制。

对于一个限制 $[l_i,r_i]$，若 $1\notin[l_i,r_i]$，则 $r_i\le k$ 时取 $(r_i,r_i+k)\in E$，$r_i\ge k+1$ 时取 $(1,k+1)\in E$，则这个限制被满足。

若 $n\notin [l_i,r_i]$，同理知限制 $[l_i,r_i]$ 被满足。

若以上两种情况均不成立，则 $1\in [l_i,r_i]$ 且 $n\in [l_i,r_i]$，故 $[l_i,r_i]=[1,n]$，与题设矛盾！

综上，命题得证。

```cpp
#include<iostream>
using namespace std;
int n,ans;
int main(){
    cin>>n;
    cout<<(ans=((n+1)>>1))<<endl;
    for(int i=1;i<=ans;++i)cout<<i<<" "<<i+(n>>1)<<endl;
    return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

验题人报到。

~~lqy：“这个题只用输入 $n$ 和 $m$，那时限开大一点吧”~~

首先因为要求满足所有 $[i,i]$，也就是说每个点都至少连出去一条边，所以至少会有 $\lceil\dfrac n2\rceil$ 条边。

先看偶数的情况，因为你很懒，所以你想要找一种能够满足任何非 $[1,n]$ 的限制的连边方案。

以 $n=4$ 为例。样例输出不行，因为选区间 $[2,3]$ 就挂掉了。这启示我们思考一下挂掉的条件是什么。

如果存在一个区间与所有边都是包含或者不交的关系，那么这个区间就会是一个使得这个方案挂掉的区间。

那只要我们的所有区间两两相交就能解决这个问题（？）

反正经过一顿研究发现 $[1,3],[2,4]$ 这个连边是满足条件的，于是推广到其他偶数的情况，就是连接所有 $[i,i+\frac n2]$。

好像还真是对的！！！

那奇数呢？直接把 $n$ 连到 $n-1$，别的跟偶数一样连就可以了。

~~所以这题只需要读入 $n$ 就够了，lqy 你怎么骗人啊~~

---

## 作者：Union_Find (赞：0)

虽然我没打这场比赛，但是我会。

# 题意

给定 $m$ 条限制，每条的要求是在集合 $E$ 中存在 $(x,y)$ 满足一个在 $[l_i,r_i]$ 中，另一个不在。求 $E$ 大小的最小值，并输出方案。注意，所有数字都要出现。

# 思路

突破口在所有数字都要出现。这条限制告诉我们答案至少是 $\left \lceil \frac{n}{2} \right \rceil$。我们就要考虑是否有这样的构造。

最容易想到的是 $(x,x+1)$，但是很容易 hack。所以要考虑其他的。因为题目告诉我们一定有解，所以就有通解。

考虑到要以个在区间内，一个在区间外，所以可以尝试让长度一样。也就是 $(x,x+mid)$，其中 $mid = \left \lceil \frac{n}{2} \right \rceil$。

我们发现这样构造在 $n$ 为偶数时好像 hack 不掉，所以尝试证明。

# 证明

我们可以分类讨论。

### $r_i - l_i + 1 < mid$

因为我们那样构造可以使一定有一个在区间内，另一个因为距离是 $mid$。所以另一个在区间外，满足条件。

### $r_i - l_i + 1 \ge mid$

这样子，如果 $r_i = n$，那么根据条件，$l_i \ne 1$，所以就有 $(1, mid + 1)$ 满足，因为当长度比 $mid$ 大时，一定经过 $mid$ 和 $mid + 1$。

如果 $r_i \ne n$，那么 $(n - mid, n)$，也就是 $(mid, n)$ 就符合条件。

# 注意

上述是当 $n$ 为偶数时，当 $n$ 为奇数时，有可能最中间的数字不被覆盖到，要补充一个 $(1, mid)$。

# Code

```cpp
int main(){
	printf ("%lld\n", (n + 1) / 2);
	for (int i = 1; i + i <= n; i++) printf ("%lld %lld\n", i, i + (n + 1) / 2);
	if (n & 1) printf ("%lld %lld\n", 1, (n + 1) / 2);
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：0)

奇数很容易就想到了，考虑第一个连最后，第二个连倒数第二个……直到最后剩下一个数。

然后你考虑这样子不止剩下一个数，如果有一个区间，他卡在中间，就寄了。

你考虑卡在中间一定不会覆盖点 $1$ 和点 $n$，所以你拿第一个和中间那个连一下就好了。

再来看看偶数，考虑偶数这样子做没有中间的点，你就把第一个点孤立出来，然后后面做奇数情况，中间多出来的点和第一个点连就好了。

注意第一个点的编号必须比第二个点的编号要小，场上调了若干分钟。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int lt,rt;
        scanf("%d%d",&lt,&rt);
    }
    if(n&1){
        printf("%d\n",(n+1)/2);
        for(int i=1;i*2<=n;i++){
            printf("%d %d\n",i,n-i+1);
        }
        printf("%d %d\n",1,n/2+1);

    }
    else{
        printf("%d\n",n/2);
        printf("%d %d\n",1,n/2+1);
        for(int i=2;i*2<=n;i++){
            printf("%d %d\n",i,n-i+2);
        }
    }
    return 0;
}
```

---

## 作者：luxiaomao (赞：0)

## [P11055](https://www.luogu.com.cn/problem/P11055) 逆天诈骗题

赛时无限接近正解但是没想出来，原因是正解长得太像骗分的了，诈骗题好好玩。

## Problem

有 $n$ 个点排成一列，要求在这些点上连边，满足：

- 若干个限制 $[l,r]$，要求至少有一条边，这条边只有一个端点在 $[l,r]$ 内。

- 每个点都最少被一条边连过，且不能出现自环。

（吐槽抽象形式化题目）

## Solution

$10^5$ 个限制实在有点难以处理，况且彼此之间还会有交集重叠，对于 $r_i < l_{i+1}$ 一类的部分分我们还可以贪心，否则我们似乎可以直接忽视限制，构造一组通解。

### 通解一（假）

这么连边：

```
___________
| _______ |
| | ___ | |
| | | | | |
1 2 3 4 5 6
```

如果 $n$ 为奇数，再连上 $1$ 和 $\lfloor \dfrac{n}{2} \rfloor + 1$。

这样能拿 $80$ 分，这是我的赛时做法。（但是只拿了 $65$ 嘤嘤嘤）

### 通解二（真）

对于 $n$ 个点：

- $1$ 连 $1 + \lfloor \dfrac{n}{2} \rfloor$。

- $2$ 连 $2 + \lfloor \dfrac{n}{2} \rfloor$。

- ……

- $\lfloor \dfrac{n}{2} \rfloor$ 连 $\lfloor \dfrac{n}{2} \rfloor + \lfloor \dfrac{n}{2} \rfloor$。

如果 $n$ 为奇数，再连上 $1$ 和 $n$。

就这么不明不白的过了。（当然这种构造是有详细证明的，具体请看出题人题解）

## Code

没错，只用输入一个 $n$，鹅鹅鹅。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;

int main()
{
	scanf("%d",&n);
	printf("%d\n",n/2+n%2);
	for(int i = 1;i <= n/2;i++)
		printf("%d %d\n",i,i+n/2);
	if(n&1)printf("1 %d\n",n);
	return 0;
}
```

---

