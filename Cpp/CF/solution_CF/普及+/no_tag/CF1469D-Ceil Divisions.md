# Ceil Divisions

## 题目描述

You have an array $ a_1, a_2, \dots, a_n $ where $ a_i = i $ .

In one step, you can choose two indices $ x $ and $ y $ ( $ x \neq y $ ) and set $ a_x = \left\lceil \frac{a_x}{a_y} \right\rceil $ (ceiling function).

Your goal is to make array $ a $ consist of $ n - 1 $ ones and $ 1 $ two in no more than $ n + 5 $ steps. Note that you don't have to minimize the number of steps.

## 说明/提示

In the first test case, you have array $ a = [1, 2, 3] $ . For example, you can do the following:

1. choose $ 3 $ , $ 2 $ : $ a_3 = \left\lceil \frac{a_3}{a_2} \right\rceil = 2 $ and array $ a = [1, 2, 2] $ ;
2. choose $ 3 $ , $ 2 $ : $ a_3 = \left\lceil \frac{2}{2} \right\rceil = 1 $ and array $ a = [1, 2, 1] $ .

 You've got array with $ 2 $ ones and $ 1 $ two in $ 2 $ steps.In the second test case, $ a = [1, 2, 3, 4] $ . For example, you can do the following:

1. choose $ 3 $ , $ 4 $ : $ a_3 = \left\lceil \frac{3}{4} \right\rceil = 1 $ and array $ a = [1, 2, 1, 4] $ ;
2. choose $ 4 $ , $ 2 $ : $ a_4 = \left\lceil \frac{4}{2} \right\rceil = 2 $ and array $ a = [1, 2, 1, 2] $ ;
3. choose $ 4 $ , $ 2 $ : $ a_4 = \left\lceil \frac{2}{2} \right\rceil = 1 $ and array $ a = [1, 2, 1, 1] $ .

## 样例 #1

### 输入

```
2
3
4```

### 输出

```
2
3 2
3 2
3
3 4
4 2
4 2```

# 题解

## 作者：georgehe (赞：5)

------------
# 题意简介

有 t 组数据，每组数据有 n 个正整数，分别是 1，2...n。每次运算可以选择数组中任意两个数 a 和 b。并进行 $a=\left\lceil\dfrac{a}{b}\right\rceil$。要求在至多 $n + 5$ 次操作后把整个数组转换有 n - 1 个 1 和 1 个 2。


------------
## 大概思路

用 n 举例：
1.  如果进行 $\dfrac{n}{n-1}$ 操作，向上取整会得到 2 。
2.  如果进行 $\dfrac{n}{n+1}$ 操作，向上取整会得到 1 。

因为我们想要最小化步数，数组中只会留一个 2，所以优先把数组中大部分数都转换成 1。那么优先要进行操作 2。

如果我们对整个 1 到 n 的全排列数组进行 $n - 3$ 次操作，每次操作都是用数组中一个数除以 n。那么我们会得到 $n - 3$ 个 1，一个 2 和一个 n。这时候如果重复进行 $\left\lceil\dfrac{n}{2}\right\rceil$ 操作，假设 n 是 200,000，那么把 n 变成 1 需要 18 次操作，而我们只剩下 8 次操作。这时候需要考虑如果减少操作次数。

我们可以想到的更快的操作是进行 $\sqrt{n}$ 操作。每遇到一个接近 n 的根的时候更新一下 n 的值。因为 n 最大是 200,000，所以不会用超过 8 次就能得到 n - 1 个 1，1 个 2 的数组。

具体实现：
```cpp
if(cur/i>=i)
{
  if(cur%i==0)
    cur/=i;
  else
    cur=cur/i+1;
  ans[++cnt].a=n;
  ans[cnt].b=i;
}
```
cur 是用来记录 n 实时变化的变量。如果 $\dfrac{cur}{i}\ge i$，我们就找到了第一个小于等于 $\sqrt{cur}$ 的整数，cur 就被减少到很接近 i 的值了。这样就成功将 cur 的平方根的值赋值到了 cur 里面。

------------
## 上代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 200010
int t,n;
struct step{
  int a,b;
}ans[maxn];

int main()
{
  cin>>t;
  while(t--)
  {
    cin>>n;
    int cnt=0;
    int cur=n;
    for(int i=n-1;i>=3;i--)
    {
      if(cur/i>=i)
      {
        if(cur%i==0)
          cur/=i;
        else
          cur=cur/i+1;
        ans[++cnt].a=n;
        ans[cnt].b=i;
      }
      ans[++cnt].a=i;
      ans[cnt].b=n;
    }
    while(cur>=2)
    {
      if(cur%2==0)
        cur/=2;
      else
        cur=cur/2+1;
      ans[++cnt].a=n;
      ans[cnt].b=2;
    }
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++)
      cout<<ans[i].a<<" "<<ans[i].b<<endl;
  }
  return 0;
}

```


---

## 作者：DLYdly1105 (赞：4)

### CF1469D Ceil Divisions

感觉是很巧妙的一题？

一开始想到，对于任何小于 $n$ 的数 $x$，直接对它除以 $n$ 可以得到 $1$。那么对 $3\sim n-1$ 做完此操作后，还剩下 $1$、$2$、$n$。将 $n$ 变成 $1$ 要花费 $\log n$ 次，显然总操作次数超过了 $n+5$ 次。

进一步地，发现瓶颈在于把 $n$ 变成 $1$，于是利用根号，用 $\sqrt{n}$ 对 $n$ 进行两次除操作就可以把 $n$ 变成 $1$ 了。

极限数据 $2e5$ 最多开 $5$ 次根号，每次开根号就有一次多余的操作，恰好满足 $n+5$ 的限制。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,tot,ans[N][2];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        tot=0;
        scanf("%d",&n);
        while(n>2)
        {
            int p=sqrt(n);
            if(p*p<n)p++;
            for(int i=p+1;i<n;i++)ans[++tot][0]=i,ans[tot][1]=n;
            ans[++tot][0]=n,ans[tot][1]=p;
            ans[++tot][0]=n,ans[tot][1]=p;
            n=p;
        }
        printf("%d\n",tot);
        for(int i=1;i<=tot;i++)printf("%d %d\n",ans[i][0],ans[i][1]);
    }
    return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：2)

> $\mathtt{TAG}$： 构造

# First. $2$ 的位置

首先，题目要求操作次数在 $n + 5$ 以内，那么我们的构造的次数肯定是越小越好。

由于序列是一个排列，为了减少次数，不妨让初始的 $2$ 即为最终的 $2$，将其余数全部归 $1$。

# Second. 如何次数更小地形成 $1$

从最大数 $n$ 开始考虑，我们希望尽可能地让这个数让越多数变成 $1$，又得让剩余的数让它变成 $1$ 的次数更小。

设 $x\sim n - 1$ 为，$n$ 的操作范围，那么操作次数即为：$n - x + n \log_{x - 1}$。

当 $x = \sqrt{n} + 1$ 时，该式取得最小值。

所以，对于 $\sqrt{n} + 1 \sim n$ 的这一段区间需要的次数即为：$n - \sqrt{n} + 2$，比区间长度多 $1$。

我们只需要一直进行这个操作，使得 $3 \sim n$ 这段区间全部归 $1$。

而每次操作，量级缩小至 $\sqrt{n}$，而达到 $3$，极限范围最多只需要 $4$ 次操作，所以，每次最多多使用 $4$ 次，所以不会超出 $n + 5$ 次，所以这种构造方式是可行的。

# Code

```cpp
#include <bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while(t --) {
		cin >> n;
		vector< pair<int, int> > ans;
		for (int i = n; i >= 3; i --) {
			int div = ceil(sqrt(i));
			for (int j = div + 1; j < i; j ++) ans.push_back({j, i});
			ans.push_back({i, div}), ans.push_back({i, div});
			i = div + 1;
		}
		cout << ans.size() << endl;
		for (auto opt : ans) cout << opt.first << ' ' << opt.second << endl;
	}
	return 0; 
}
```

---

## 作者：wo_hen_la (赞：1)

## 思路

首先要尽可能地让每个数进行一次，那么我们把大于 $2$（$a_1$ 和 $a_2$ 不用变）的数都除以 $n$，得到 $1$。但是问题来了，这时候除了 $n$ 以外没有较大的数，就不能用很少的次数把 $a_n$ 变成 $1$。

但注意到 $n \le 200000$ ，刚好有个数 $12$，它的 $5$ 次方是 $248832$，比 $200000$ 大一点，那么我们可以保留它，让它在后面被 $n$ 除，$n$ 最多被除 $5$ 次变成 $1$。

那 $12$ 该怎么变成 $1$？又发现 $12$ 可以除以 $3$ 再除以 $4$ 得到 $1$，为了这个操作要先不操作 $3$ 和 $4$。现在只剩下 $3$ 和 $4$ 了，先让 $3$ 除以 $4$ 变 $1$，再让 $4$ 两次除以 $2$ 变 $1$。

到此操作就结束了，算一下总操作数是 $(n-6)+5+2+1+2=n+4$ ，刚好满足题目要求。

## 代码

先把 $n \le 5$ 的部分特判一下比较方便。

剩下的如果 $n \le 12$ 把原本的被 $n$ 除的 $12$ 改成 $n-1$，防止越界。

最后剩下的就是正常部分。


```cpp
vector<int> ans1,ans2;
void solve()
{
	ans1.clear();ans2.clear();
	int n;
	cin>>n;
	int id=12,cnt=0;
	if(n<=5){
		if(n==3){
			cout<<2<<"\n"<<"3 2\n"<<"3 2\n";
		}
		else if(n==4){
			cout<<3<<"\n"<<"3 4"<<"\n"<<"4 2\n"<<"4 2\n";
		}
		else{
			cout<<6<<"\n";
			cout<<5<<" "<<4<<"\n";
			cout<<5<<" "<<4<<"\n";
			cout<<4<<" "<<3<<"\n";
			cout<<4<<" "<<3<<"\n";
			cout<<3<<" "<<2<<"\n";
			cout<<3<<" "<<2<<"\n";
		}
		return;
	}
	if(n<=12) id=n-1;
	for(int i=5;i<=n-1;i++){
		if(i==id) continue;
		ans1.pb(i),ans2.pb(n);
		cnt++;
	}
	int x=n;
	while(1){//除以id变成1
		x=ceil(1.0*x/id);
		ans1.pb(n),ans2.pb(id);
		cnt++;
		if(x<=1){
			break;
		}
	}
	cnt+=5;
	cout<<cnt<<"\n";
	for(int i=0;i<ans1.size();i++){
		cout<<ans1[i]<<" "<<ans2[i]<<"\n";
	}
	cout<<id<<" "<<3<<"\n";
	cout<<id<<" "<<4<<"\n";
	cout<<3<<" "<<4<<"\n";
	cout<<4<<" "<<2<<"\n";
	cout<<4<<" "<<2<<"\n";
}
```

---

## 作者：Presentation_Emitter (赞：1)

观察到数组前两项为 $1,2$，因此我们可以保留这两项。同时，对于 $[3,n)$ 中的每一个数 $i$，我们都能用 $1$ 次操作将 $i$ 变为 $\lceil \frac{i}{\texttt{大于}i\texttt{的数}} \rceil=1$。但是我们还需要考虑 $n$。把 $n$ 直接处理变为 $1$ 的花费是极大的（$\log n$），因此我们需要从 $[3,n)$ 中选出几项单独处理。

~~因为这是道绿题，所以~~我们可以假定单独处理的方法只有一种。设单独处理的几项（包括 $n$）组成的集合为 $S$，我们可以得到关于操作次数 $t$ 的一个式子：

$$t=n-2-|S|+cost(S)$$

其中 $n-2-|S|$ 为用 $1$ 次操作处理的数的个数，$cost(S)$ 为对 $S$ 进行处理的花费之和。为方便起见，我们可以把 $2$ 也加进 $S$。

因为给出的操作是除法操作，所以对**相邻两项**的处理必然较优。设 $tms$ 表示每处理一次（将两项中的一项变为 $1$）的次数，$x,y(x \lt y)$ 表示待处理的两个数（事实上要处理的必定是 $y$，因为如果处理 $x$ 就与用 $1$ 次操作处理的方法无异）。考虑 $x$ 与 $y$ 的各种关系：

|$relation$|$\lvert S \rvert$|$tms$|
|:-:|:-:|:-:|
|$x=\sqrt{y}$|$\frac{\log_{2}{n}}{2}$|$2$|
|$x=y^{\frac{1}{3}}$|$\frac{\log_{2}{n}}{3}$|$3$|
|$x=\lceil \log_{2}{y} \rceil$|$\le 5$|较大|
|…|…|…|

考虑 $x=\sqrt{y}$ 即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define neinf 0xc0c0c0c0c0c0c0c0ll
#define inf 0x3f3f3f3f3f3f3f3fll
#define uint unsigned int
#define ull unsigned ll
#define ll long long
#define reg register
#define db double
#define il inline
#define gc getchar
#define pc putchar
#ifdef ONLINE_JUDGE
#undef pc
#define pc(a) fputc(a,stderr)
#endif
#define HgS 1000000007
il ll rd()
{
	reg ll res=0,lab=1;
	reg char ch=gc();
	while((ch<'0'||ch>'9')&&ch!=EOF)
	{if(ch=='-')lab=-lab;ch=gc();}
	while(ch>='0'&&ch<='9')
		res=(res<<3)+(res<<1)+(ch&15),ch=gc();
	return res*lab;
}
il void prt(ll x,char t='\n')
{
	char ch[70];int tp=0;
	if(!x){pc('0');if(t)pc(t);return;}
	if(x<0)pc('-'),x=-x;
	while(x)ch[++tp]=(x%10)^48,x/=10;
	while(tp)pc(ch[tp--]);
	if(t)pc(t);
}
il ll umax(ll a,ll b){return a>b?a:b;}
il ll umin(ll a,ll b){return a<b?a:b;}
ll T,n,x[200010],y[200010],op,s[200010],tp;
bool tb[200010];
int main()
{
	T=rd();
	while(T --> 0)
	{
		n=rd();op=0;tp=0;memset(tb,0,sizeof(tb));
		ll tmp=n,ltp;
		s[++tp]=n;
		while(tmp>2)
		{
			ltp=tmp;
			tmp=(ll)(sqrt(tmp)+1e-4);
			while(tmp*tmp<ltp)++tmp;
			s[++tp]=tmp;
			tb[tmp]=1;
		}
		for(int i=3;i<n;++i)if(!tb[i])x[++op]=i,y[op]=i+1;
		for(int i=1;i<tp;++i)
			for(int j=1;j<=2;++j)
				x[++op]=s[i],y[op]=s[i+1];
		prt(op);
		for(int i=1;i<=op;++i)prt(x[i],' '),prt(y[i]);
	}
	return 0;
}

```

---

## 作者：Eason_AC (赞：1)

## Content
你有一个长度为 $n$ 的数组 $a$，初始时，$\forall i\in[1,n]$，$a_i=i$。

每次操作选择两个数 $x,y(1\leqslant x,y\leqslant n,x\neq y)$，然后将 $a_x$ 转换为 $\left\lceil\dfrac{a_x}{a_y}\right\rceil$。你需要执行不超过 $n+5$ 次操作将数组 $a$ 转换为一个包含 $n-1$ 个 $1$ 和 $1$ 个 $2$ 的数组。请给出一个构造方案。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 10^3$，$3\leqslant n,\sum n\leqslant 2\times 10^5$。**
## Solution
不难想到的做法是，$\forall i\in[3,n)$，每次将 $a_i$ 转换为 $\left\lceil\dfrac{a_i}{a_{i+1}}\right\rceil$。可以证明，由于 $a_i<a_{i+1}$，所以转换的结果必然为 $1$。然后我们再用剩下的 $2$ 不断的去除 $n$ 直到 $n$ 变成 $1$ 为止。操作数约为 $n+\log n$，而 $\log n$ 最大值显然会超过 $5$，因此是不可行的。考虑如何优化这个操作方案。

我们发现，拿 $\left\lceil\sqrt{n}\right\rceil$ 去除 $n$ 最多仅需 $2$ 次就可以将 $n$ 变成 $1$，因此，我们不妨把 $[\left\lceil\sqrt{n}\right\rceil,n]$，$[\left\lceil\sqrt{\left\lceil\sqrt{n}\right\rceil}\right\rceil,\left\lceil\sqrt{n}\right\rceil]$，$\dots$ 等部分分成一段（注意 $1,2$ 不能被分到任何一段中去），对于每一段，我们先把中间的所有元素全拿最后一个元素去除使它门全部都变成 $1$，然后再去拿最左边的元素去除以最右边的元素 $2$ 次，即可做到使一段里面的元素全部变成 $1$。

然后这道题目就可以过了。
## Code
```cpp
namespace Solution {
	const int N = 2e5 + 7;
	int n;
	struct node {int x, y;};
	vector<node> ans;
	
	ii checksq(int x) {
		int sqrtx = sqrt(x);
		return sqrtx * sqrtx == x;
	}
	
    iv Main() {
		MT {
			read(n), ans.clear();
			int cur = sqrt(n) + !checksq(n), precur = n, fl = 0;
			while(precur > 2) {
				F(int, i, cur + 1, precur - 1) ans.push_back((node){i, precur});
				F(int, i, 1, 2) ans.push_back((node){precur, cur});
				precur = cur, cur = sqrt(precur) + !checksq(precur);
			}
			int cnt = ans.size(); println(cnt);
			F(int, i, 0, cnt - 1) printf("%d %d\n", ans[i].x, ans[i].y);
		}
		return;
	}
}
```

---

## 作者：Zwb0106 (赞：0)

**[原题链接](https://codeforces.com/contest/1469/problem/D)**

------------
## 题意

给定正整数 $n$，表示存在一个长为 $n$ 的序列 ${a_n}$，且对于 $\forall i\in \left[ 1,n \right]$，均有 $a_i=i$。现在每次可对序列进行一次操作：选定 $i,j(i\neq j)$，令 $a_i$ 变为 $\lceil \dfrac{a_i}{a_j} \rceil$。你需要构造一种操作数不超过 $n+5$ 次的方案，使得变换后的序列恰有 $n-1$ 个 $1$ 和 $1$ 个 $2$。

对于 $\text{100\%}$ 的数据，$3\le n\le 2\times 10^5$。

------------
## 思路

一个确定的想法是，序列中的大部分数都应当通过一次操作就变成 $1$。

由于上取整的性质，当且仅当操作中选定的 $i,j$ 满足 $a_i\le a_j$。容易想到，可以使 $a_3,a_4,...,a_{n-1}$ 对 $a_n$ 进行操作，最后再使 $a_n$ 对 $a_2$ 进行操作，这样的次数应当是 $n+\log_2{n}$ 级别的。

考虑这个看上去较优的办法出现了什么问题：事实上，每次对一个 $a_i$ 进行操作时，仅需要保证选取的 $j$ 满足 $a_i\le a_j$ 即可，而不必让 $a_n$ 的值始终为 $n$，这会使最后单独对 $a_n$ 做处理时的操作数多出不少。

那么，有了上面的分析，就可以考虑对序列中的元素从后到前进行操作，每次枚举到一个 $i$ 满足 $\lceil \dfrac{a_n}{a_i} \rceil \ge a_i$，就直接对 $a_n$ 进行一次操作。这样操作**对于 $a_n$ 规模的缩减是开根级别的**，于是，操作的总数就得以减少至可接受的范围内了。

**注意：枚举至 $a_3$ 时即应停止，此时的 $a_n$ 不等于 $1$，应继续用 $a_2$ 进行操作，直至 $a_n=1$。**

时间复杂度 $O(n)$。

------------
## 代码

```cpp
#include<iostream>
#include<cstdio>
#define in inline
#define re register
using namespace std;
const int N=2e5+5;
int T,n,cnt,a[N],ans1[N],ans2[N];
in int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	}
	return x;
}
void print(int x)
{
	if(x>9)print(x/10);
	putchar(x%10+48);
}
int main()
{
	T=read();
	while(T--)
	{
		n=read(),cnt=0;
		for(re int i=1;i<=n;++i)a[i]=i;
		for(re int i=n-1;i>=3;--i)
		{
			if(a[n]/a[i]>=a[i])
			{
				a[n]=(a[n]+a[i]-1)/a[i];
				ans1[++cnt]=n,ans2[cnt]=i;
			}
			a[i]=1,ans1[++cnt]=i,ans2[cnt]=n;
		}
		while(a[n]>=2)
		{
			a[n]=(a[n]+1)/2;
			ans1[++cnt]=n,ans2[cnt]=2;
		}
		print(cnt),putchar('\n');
		for(re int i=1;i<=cnt;++i)
		{
			print(ans1[i]),putchar(' ');
			print(ans2[i]),putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：LXH5514 (赞：0)

## CF1469D Ceil Divisions

### 题目大意

给出一个$1$~ $n$ 的序列，让你通过操作使得这个序列变成 $n-1$ 个1和 $1$ 个 $2$。

操作：选出两个数 $x$，$y$ ，$x=\lceil \frac{x}{y} \rceil $，操作次数$\leq n+5$。

（$n\le 2*1e5$ ）

### 思路

很显而易见，由于除是向上取整，因此如果 $x\leq y$ ，那么$x=1$ ，我的第一个想法就是用 $n$ 将其他数都变成1（2除外），那么此时需要 $n-3$ 次操作，还剩下 $8$ 次，那么我们也就只能处理 $n\thickapprox 2^8$ （因为是向上取整，懒得认真算，直接约等于）。

但这距离 $n\le 2*1e5$ 的数据还遥遥无期，这是为什么呢？很显然，由于我们只剩下 $2$ ，远小于 $n$ ，要把 $n$ 这么大的数变成 $1$ ，效率是极低的，因此我们需要保留一个较大的数 $x$ ，用 $x$ 来干 $n$，从而提高效率。

我们再来分析一次操作次数：$n-4+log_2 x+log_x n \le n+5$ ，（这里的log并不是真的 $log$  ，因为有向上取整）移项可得$log_2 x+log_x n<=9$。

然后我就 $n=2*1e5$ 打表找 $x$，

在 1~1000 这个范围内只有$8,12 \backsim 16,22  \backsim 32,59 \backsim 64$ ，然后我选了 $8$ 。

当然你也可以选比较大的数，然后多选几个$a_1,a_2 ...a_x$，（$a_1<a_2<a_3 ...$）然后 $n$ 用 $a_x$ 来除，$a_x$ 用 $a_{x-1}$ 来除，当然一定要满足效率更优的情况下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000;
int read()
{
	int f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
int t,n;
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		if(n>8)
		{
			int sum=0;
		int x=n;
		while(x>=2)
		{
			if(x%8==0)x/=8;
			else x=(x/8)+1;
			sum++;
		}
		printf("%d\n",sum+n-4+3);
		for(int i=3;i<=n-1;i++)
		{
			if(i==8)continue;
			printf("%d %d\n",i,n);
		}
		for(int i=1;i<=sum;i++)
			printf("%d 8\n",n);
			for(int i=1;i<=3;i++)
			printf("8 2\n");
		}
		else
		{
			int sum=0;
		int x=n;
		while(x>=2)
		{
			if(x%2==0)x/=2;
			else x=(x/2)+1;
			sum++;
		}
		printf("%d\n",sum+n-1-2);
		for(int i=3;i<=n-1;i++)
		printf("%d %d\n",i,n);
		for(int i=1;i<=sum;i++)
			printf("%d 2\n",n);
		}
	}
	return 0;
}
```



---

## 作者：pyyyyyy (赞：0)

> 你有一个数组 $1,2,3,4,....,n$。每次可以选择$x$和$y(x≠y)$，使得$a_x = \left\lceil \frac{a_x}{a_y} \right\rceil$，你的目标是在**不超过$n+5$步**的情况下使数组由$n-1个1$和$1$个$2$组成。输出每一步

- 方法一

容易发现，我们可以比较简单的把$[3,n)$变成$1$，只需要把他们都除以$n$(上取整)即可

此时只剩下$1,2,1,...,n$，已经用了$n-3$步，现在我们要处理掉$n$，只能$n/2$，需要$log_2n$次，不符合题目步数限制。

我们可以考虑如何处理$n$,注意到$\sqrt{n}$最多才$5$次，所以可以把$\sqrt{n}$求出来，单独放到一个集合$b$里面，对于$[3, n) \cap \complement_{\mathrm{U}} b$直接除以$n$，$b$中元素(注意除去$2$)和前一个除两次变成$1$，

- 方法二

一个更简单的方法

首先通过$i$除以$n$的方法把$[3,n)$变成$1$（注意不包括8)，然后把$n$除以$8$，把$n$变成$1$，最后对$8$进行3次除以$2$，把$8$变成$1$

一共需要：第一步$n-4$次+第二步$6$次($n_{max}=2e5<262144$)+第$3$步$3$次$=n+5$

参考代码~~非常不简洁~~。

```cpp
const int N = 2e5 + 15;
int T, n;
struct node{
	int x, y;
}ans[N];

int main()
{
	T = read();
	while(T--){
		n = read();
		if(n <= 8){
			int cnt = 0;
			if(n == 3){
				printf("2\n3 2\n3 2\n");
				continue;
			}
			for(int i = 3; i <= n - 1; ++i){
				ans[++cnt].x = i;
				ans[cnt].y = n;
			}
			int tmp = n;
			while(tmp != 1){
				tmp = ceil(tmp * 1.0 / 2.0);
				ans[++cnt].x = n;
				ans[cnt].y = 2;
			}
			cout << cnt << '\n';
			for(int i = 1; i <= cnt; ++i)
				printf("%d %d\n", ans[i].x, ans[i].y);
		}
		else{
			int cnt = 0;
			for(int i = 3; i <= n - 1; ++i){
				if(i == 8) continue;
				ans[++cnt].x = i;
				ans[cnt].y = n;
			}
			int tmp = n;
			while(tmp != 1){
				tmp = ceil(tmp * 1.0 / 8.0);
				ans[++cnt].x = n;
				ans[cnt].y = 8;
			}
			for(int i = 1; i <= 3; ++i){
				ans[++cnt].x = 8;
				ans[cnt].y = 2;
			}
			cout << cnt << '\n'; 
			for(int i = 1; i <= cnt; ++i)
				printf("%d %d\n", ans[i].x, ans[i].y);
		}
	}
	return 0;
}

```

---

## 作者：zjjws (赞：0)

首先，有一个非常 Simple 的策略：

直接将 $[3,n)$ 范围内的所有整数和 $n$ 进行一次操作。这样我们可以用 $n-3$ 次达到 $n-2$ 个 $1$，$1$ 个 $2$ 和 $1$ 个 $n$ 的局面。

而后你需要 $\log n$ 次操作来将 $n$ 变成 $1$，你会发现这样的话步数非常的多。

考虑改进。既然 $\log$ 不行，$\sqrt .$ 呢？

我们计算一下：

$200000 \to 448 \to 22 \to 5 \to 3\to 2$

对于这些数，我们设它们的集合为 $\alpha$，先将 $[3,n)\cap \complement_{\mathbb U}\alpha$ 的所有元素进行一次除 $n$ 操作，然后再对 $\alpha$ 中的所有元素（除 $2$ 外）用刚好比它小的那一个数，进行两次除法操作，即可将其变成 $1$。

其中 $\mathbb U$ 为全集，即 $[1,n]\cap \mathbb Z$。

因为这里是向上取整，所以我们在处理 $\alpha$ 中的元素时，需要将 $x\to \lceil \sqrt x \rceil$。

这样的话，步数是够的。


```cpp
#include <stdio.h>
#include <cmath>
#define LL long long
using namespace std;
const int N=2e5+3;
inline LL rin()
{
    LL s=0;
    bool bj=false;
    char c=getchar();
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')bj=true,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)s=-s;
    return s;
}

bool vit[N];
int d[N];
struct gyq
{
    int x,y;
    gyq(int x_=0,int y_=0){x=x_;y=y_;}
}ans[N<<1];
inline void work()
{
    int n=rin();
    if(n<=2){puts("0");return;}
    int tail=0;
    int cutt=0;
    for(int i=1;i<=n;i++)vit[i]=false;
    for(int i=n;i>2;i=ceil(sqrt(i)))vit[i]=true,d[++tail]=i;
    d[++tail]=2;vit[2]=true;
    for(int i=2;i<=n;i++)if(!vit[i])ans[++cutt]=gyq(i,n);
    for(int i=1;i<tail;i++)ans[++cutt]=gyq(d[i],d[i+1]),ans[++cutt]=gyq(d[i],d[i+1]);
    printf("%d\n",cutt);
    for(int i=1;i<=cutt;i++)printf("%d %d\n",ans[i].x,ans[i].y);
    return;
}
int main()
{
    int i,j;
    for(int T=rin();T;T--)work();
    return 0;
}
```

---

