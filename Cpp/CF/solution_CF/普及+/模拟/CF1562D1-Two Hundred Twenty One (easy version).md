# Two Hundred Twenty One (easy version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that the easy version does not require you to output the numbers of the rods to be removed. You can make hacks only if all versions of the problem are solved.

Stitch likes experimenting with different machines with his friend Sparky. Today they built another machine.

The main element of this machine are $ n $ rods arranged along one straight line and numbered from $ 1 $ to $ n $ inclusive. Each of these rods must carry an electric charge quantitatively equal to either $ 1 $ or $ -1 $ (otherwise the machine will not work). Another condition for this machine to work is that the sign-variable sum of the charge on all rods must be zero.

More formally, the rods can be represented as an array of $ n $ numbers characterizing the charge: either $ 1 $ or $ -1 $ . Then the condition must hold: $ a_1 - a_2 + a_3 - a_4 + \ldots = 0 $ , or $ \sum\limits_{i=1}^n (-1)^{i-1} \cdot a_i = 0 $ .

Sparky charged all $ n $ rods with an electric current, but unfortunately it happened that the rods were not charged correctly (the sign-variable sum of the charge is not zero). The friends decided to leave only some of the rods in the machine. Sparky has $ q $ questions. In the $ i $ th question Sparky asks: if the machine consisted only of rods with numbers $ l_i $ to $ r_i $ inclusive, what minimal number of rods could be removed from the machine so that the sign-variable sum of charges on the remaining ones would be zero? Perhaps the friends got something wrong, and the sign-variable sum is already zero. In that case, you don't have to remove the rods at all.

If the number of rods is zero, we will assume that the sign-variable sum of charges is zero, that is, we can always remove all rods.

Help your friends and answer all of Sparky's questions!

## 说明/提示

In the first test case for the first query you can remove the rods numbered $ 5 $ and $ 8 $ , then the following set of rods will remain: +--+--++-++-. It is easy to see that here the sign-variable sum is zero.

In the second test case:

- For the first query, we can remove the rods numbered $ 1 $ and $ 11 $ , then the following set of rods will remain: --++---++---. It is easy to see that here the sign-variable sum is zero.
- For the second query we can remove the rod numbered $ 9 $ , then the following set of rods will remain: ---++-. It is easy to see that here the variable sum is zero.
- For the third query we can not remove the rods at all.

## 样例 #1

### 输入

```
3
14 1
+--++---++-++-
1 14
14 3
+--++---+++---
1 14
6 12
3 10
4 10
+-+-
1 1
1 2
1 3
1 4
2 2
2 3
2 4
3 3
3 4
4 4```

### 输出

```
2
2
1
0
1
2
1
2
1
2
1
1
2
1```

# 题解

## 作者：XL4453 (赞：7)

### 解题思路：

结论是这样的：对于一段区间，如果这一段区间本身就已经满足条件了，那么不需要动；否则根据区间长度判断结果，若为偶数则需要操作两次，奇数则只需要操作一次。

考虑如何证明这个结论：

首先发现，一个形如 $++$ 或 $--$ 的序列是一定不会影响最后的结果的，那么考虑将所有的这样的序列删去（这里可以感性理解为两个相同电荷碰到一起相互抵消），也就得到了形如 $+-+-+-+-...$ 这样的一个序列。

在这个序列中，若长度为奇数，则首尾相同，只需要删除正中间的哪一个节点就可以了。这样的话，两边的节点相互抵消，最后序列就“空了”，也就是得到了一个满足条件的序列。

而长度为偶数时，如果删去中间的那一个（中间靠左和中间靠右都可以），就会发现在这个序列的头或者尾（取决于删的是中间靠左的还是靠右的）上多了一个电荷，这个电荷无法消去，所以也得手动删掉。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int T,n,num[300005],q,l,r;
char c;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++){
			c=getchar();
			while(c!='+'&&c!='-')c=getchar();
			if(c=='+')num[i]=1;
			else num[i]=-1;
			if(i%2==0)num[i]*=-1;
			num[i]=num[i]+num[i-1];
		}
		for(int i=1;i<=q;i++){
			scanf("%d%d",&l,&r);
			if(num[r]-num[l-1]==0){printf("0\n");continue;}
			if((r-l)%2==0)printf("1\n");
			else printf("2\n");
		}
	}
	return 0;
}
```


---

## 作者：Echidna (赞：3)

[更好的阅读体验](https://oieraln.blog.luogu.org/CF741Div2)

$\text{update in 9.10} :$ 修改了一处笔误。在此感谢 [anaoai](https://www.luogu.com.cn/user/560814) ！

## 题意简述：

给你一个长度为 $n$ 的 $\text{1/-1}$ 序列 $a$ 和 $q$ 个询问，每次询问给你一条线段 $[l,r]$，然后让你删除线段 $[l,r]$ 中的几个数，并且要求你删除完成之后把剩下的线段的偶数位置取反之后加和为 $0$。

请问最少的删除次数是多少？

----------------

## 题目分析：

首先有一个结论：对于一个长度为奇数的序列，最多删一次就行。

证明：

先设 $b_i=a_i\cdot(-1)^{i-1},f(l,r)=\sum\limits_{i=1}^nb_i$。

如果我们删掉 $x$ 的话，它的贡献是 $-b_x$ 和让它后边的 $b$ 取反。

也就是说如果删掉 $x$ 之后满足了题目规定的条件的话，有 

$$f(1,x-1)-f(x+1,r)=0$$

不妨设 $g(x)=f(1,x-1)-f(x+1,n)$。

让我们来看一下在不同情况下 $g(x)$ 的变化：

1. 如果 $b_x\ne b_{x+1}$ ，那么 $g(x)=g(x+1)$。

因为 $b_x=-b_{x+1}$ 一定成立，所以

$$
\begin{aligned}
g(x)&=f(1,x-1)+f(x+1,n)\\
&=\sum_{i=1}^{x-1} b_i - \sum_{i=x+1}^nb_i\\
&=\sum_{i=1}^{x-1} b_i - b_{x+1} - \sum_{i=x+2}^nb_i\\
&=\sum_{i=1}^{x-1} b_i + b_{x} - \sum_{i=x+2}^nb_i\\
&=\sum_{i=1}^{x} b_i - \sum_{i=x+2}^nb_i\\
&=g(x+1)
\end{aligned}
$$

这样就证完了。

2. 如果 $b_x = b_{x+1}$，那么 $g(x)$ 和 $g(x+1)$ 最多差 $2$。

我们套用上次证明的套路，但是这次不同的是我们只有 $b_{x+1}=b_{x}$。

$$
\begin{aligned}
g(x)&=f(1,x-1)+f(x+1,n)\\
&=\sum_{i=1}^{x-1} b_i - \sum_{i=x+1}^nb_i\\
&=\sum_{i=1}^{x-1} b_i - b_{x+1} - \sum_{i=x+2}^nb_i\\
&=\sum_{i=1}^{x-1} b_i + b_{x} - 2b_{x} - \sum_{i=x+2}^nb_i\\
&=\sum_{i=1}^{x} b_i - \sum_{i=x+2}^nb_i -2b_x\\
&=g(x+1)-2b_x
\end{aligned}
$$

所以 $|g(x)-g(x+1)| = 2 $。

那么知道了这个有什么用呢？

我们要求的是一个 $x$ 满足 $g(x)=0$，也就是要求这个函数的零点。

我们容易发现 $g(1)$ 和 $g(n)$ 一定都是偶数而且互为相反数。

我们刚刚证明了 $g(x)$ 的变化一定以 $2$ 作为单位。

那么，这不就说明了 $g(x)$ 一定有零点吗？

所以，我们证明了在 $n$ 为奇数的情况下只删一次一定行。

--------------

现在我们考虑 $n$ 为偶数的情况。

我们分情况讨论：

1. 不用删，本来就行

那就直接输出 $0$ 吧。

2. 需要删。

容易发现我们必须要删偶数次才能让结果为 $0$ ，因为 $0$ 是一个偶数，所以删一次肯定不行。

那么就随便删一个，然后问题转化为 $n$ 为奇数的情况，然后再删一次就做出来了。

$\text{Code:}$

```cpp
int a[N];
int n,q;
void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        char c;cin>>c;
        a[i]=(c=='+')?1:-1;
        if(i%2==0)a[i]*=-1;
        a[i]+=a[i-1];
    }
    for(int l,r,i=1;i<=q;i++){
        cin>>l>>r;
        if((r-l+1)%2==1)cout<<"1"<<endl;
        else if(a[l-1]==a[r]) cout<<"0"<<endl;
        else cout<<"2"<<endl;
    }
}
```

---

## 作者：出自幽谷 (赞：2)

我们发现连续的两个 $++$ 或者 $--$ 并不会影响序列的值。

所以我们只需要删除某些 $+$ 或者 $-$ ，使序列能在若干次删除$++$ 和 $--$串后变为空。

那么原串在删除 $++$ 和 $--$ 过后只会有两种结果：

$1.+-+-+-......$

$2.-+-+-+......$

这两个串是相反的，我们考虑其中一种。

$1.$ 当删除后的长度为奇数时，也就是原串的值为奇数，我们只需要将最中间的一个删除。


$2.$ 当长度是偶数时，也就是原串的值为偶数，我们可以将最后一个删除和将剩下的中间的一个删除

---

## 作者：KSToki (赞：1)

# 题目大意
给定一个长为 $n$ 的仅含 $1$ 或 $-1$ 的数组 $a$，有 $q$ 次询问，问 $l$ 到 $r$ 至少要删多少个数才能使 $\sum_{i=l}^{r}(-1)^{i-l} \cdot a_i=0$，可以删完所有数。
# 题目分析
这道题的结论还是简单的，如果已经满足则输出 $0$，否则长度为奇数输出 $1$，长度为偶数输出 $2$，关键在于证明。

满足条件的长度一定为偶数，由于已经不满足条件，那么偶数长度一定至少删了两个数，那么随便删掉一个数就转化为奇数长度，所以证明的核心在于长度为奇数只需要删一个数。设原本计算出的值为 $s$，删掉的数一定对最终答案贡献为 $\pm1$，并使其后面部分所有数的贡献反转，即总贡献取相反数，那么转化为证明一定存在一个位置使左两部分原贡献相等。而每个数对答案贡献为 $\pm1$，那么贡献将会是**连续变化的**，能取到 $s$ 就一定能取到 $\frac{s}{2}$（向上取整向下取整其实问题不大，看删的数的原贡献），得证。

原贡献一个前缀和就可以搞定，在实际实现过程中不需要关心整体贡献是否反转，即开头原贡献是正还是负没有影响。代码就很简单了。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,q,x,y,sum[300001];
char s[300001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		q=read();
		scanf("%s",s+1);
		For(i,1,n)
			sum[i]=sum[i-1]+((s[i]=='+')?1:-1)*((i&1)?1:-1);
		while(q--)
		{
			x=read();
			y=read();
			if(sum[y]-sum[x-1]==0)
				puts("0");
			else
			{
				if((y-x)&1)
				{
					puts("2");
					
				}
				else
				{
					puts("1");
					
				}
			}
		}
	}
	return 0;
}

```

---

## 作者：Zxsoul (赞：0)



我们可以理解为先对总序列取反以后再询问，每次删除一个数，相当于删掉该位置，并且将后缀所有数取反。

然后发现一个性质，就是原序列中 `++` ，在取反后会变成 `+-` 或者 `-+` ，当删除某个数时，他都不会产生新的贡献，总是 $0$ 

所以对于取反后的序列，相邻符号不同的都可以直接删除（此处的删除不带取反），因为不会产生贡献。删除后发现，由于每次删除的都是偶数，那么两个原本不相邻的数相邻后，二者依旧保持一奇一偶的形式。所以我们可以接着删。

直到序列只剩下 `+++` 或者 `---` ，然后观察序列长度，当偶数时，由**相邻位删除后奇偶性不变**的结论也就是上面的话，我们可以删除（此处题目含义删除）顶端，变成 `-+-` 或者 `+-+`，此时我们再删除尾部，那么就符合条件了，即 `+-`。

奇数的时候更加显然，`+++` 删除顶端后就变成了 `-+`或者 `+-`，这一切都基于每次相邻位删除，奇偶性不变的结论。

然后就可以通过本题目了

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int sum[300009];
int a[300009];
int n,m;
char c[300009];
void solve()
{
	cin>>n>>m;
	cin>>c+1;
	for (int i=1;i<=n;i++)
	{
		if (c[i]=='+') a[i]=1;
		if (c[i]=='-') a[i]=-1;
		if (!(i&1)) a[i]=-a[i];
		sum[i]=sum[i-1]+a[i];
	}
	while (m--)
	{
		int l,r; cin>>l>>r;
		if (sum[r]-sum[l-1]==0) {printf("0\n");}
		else if ((r-l+1)&1) {printf("1\n");}
		else printf("2\n");
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>T;
	while (T--) solve();
}

```

---

## 作者：cmll02 (赞：0)

首先这个题的 $a_1-a_2+a_3\cdots$ 可以把偶数位的正负号反转一下，这样就变成求和了。

反转好之后记为 $b_i=(-1)^{i-1}a_i$。

前缀和一下。

对于每个询问三种情况：

令 $d=\sum\limits_{i=l}^rb_i$。

1. $d=0$，输出 $0$。
2. $d \bmod 2=1$。

接下来证明一次操作必然可行。

假设 $d$ 是正数。

记 $c_k=\sum\limits_{i=l}^kb_i$。

那么有 $|c_i-c_{i-1}|=1~(l<i\le r )$。

假设我们删掉的位置是 $k$。

那么新的权值就是 $c_{k-1}-(c_r-c_k)$。

如果 $b_k=1$，

有 $2c_k-1=c_r=d$。

显然当 $b_i=1$ 时 $c_i$ 可以取遍 $[0,d]$ 之间的整数，并且 $d$ 是正整数，有 $\dfrac{d+1}2\le d$。

那么我们必然能找到一个 $k$ 满足 $b_k=1$， $c_k = \dfrac{d+1}2$。

$d$ 是负数也是类似做法。

所以一次操作一定可行。

3. $d\bmod 2=0$

这个也很简单，首先根据奇偶性，一次操作完之后权值是奇数，肯定不行。

那么先把最后一个符号删掉，然后就转换成了情况 $2$。

这样两次操作就做完了。

代码太丑了，挂个 CF [链接](http://codeforces.com/contest/1562/submission/127149703)吧。

---

## 作者：Chouquet (赞：0)

~~为什么CF这么喜欢构造和结论题……~~

一看样例明显是结论题。很显然，把“+”看成 $1$，“-”看成 $-1$，然后根据题目的要求做一遍前缀和，记为 $sum_i$。

如果连续出现两个相同的符号，则和为 $0$，所以本题真正有用的是连续两个不相同的符号。如样例的第一组“+--++---++-++-”，真正对前缀和做出贡献的只有“+-+-”。所以本题变成了：在做出贡献的符号中删去最少的符号，使得剩下的符号相同且有偶数个。每次删除一个符号时，剩下的符号的系数都会变成相反数。

因此在每次询问时，记询问的那一段的和为 $ans$。则：

+ $ans = 0$ 时，不用修改。

+ $ans$ 是奇数时，只需要修改一次。

+ 否则需要修改两次。

代码：

```cpp
#include <cstdio>
int t, n, q, sum[300003];//sum是前缀和数组
char s[300003];
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%s", &n, &q, s + 1);
        for (int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + (i & 1 ? 1 : -1) * (s[i] == '+' ? 1 : -1);//处理前缀和
        while (q--) {
            int l, r, ans;
            scanf("%d%d", &l, &r);
            ans = sum[r] - sum[l - 1];//对ans的奇偶性讨论
            if (!ans)//情况1
                puts("0");
            else if (ans & 1)//情况2
                puts("1");
            else//情况3
                puts("2");
        }
    }
    return 0;
}
```

---

