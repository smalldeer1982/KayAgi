# Genius's Gambit

## 题目描述

You are given three integers $ a $ , $ b $ , $ k $ .

Find two binary integers $ x $ and $ y $ ( $ x \ge y $ ) such that

1. both $ x $ and $ y $ consist of $ a $ zeroes and $ b $ ones;
2. $ x - y $ (also written in binary form) has exactly $ k $ ones.

 You are not allowed to use leading zeros for $ x $ and $ y $ .

## 说明/提示

In the first example, $ x = 101000_2 = 2^5 + 2^3 = 40_{10} $ , $ y = 100001_2 = 2^5 + 2^0 = 33_{10} $ , $ 40_{10} - 33_{10} = 7_{10} = 2^2 + 2^1 + 2^0 = 111_{2} $ . Hence $ x-y $ has $ 3 $ ones in base-2.

In the second example, $ x = 10100_2 = 2^4 + 2^2 = 20_{10} $ , $ y = 10010_2 = 2^4 + 2^1 = 18 $ , $ x - y = 20 - 18 = 2_{10} = 10_{2} $ . This is precisely one 1.

In the third example, one may show, that it's impossible to find an answer.

## 样例 #1

### 输入

```
4 2 3```

### 输出

```
Yes
101000
100001```

## 样例 #2

### 输入

```
3 2 1```

### 输出

```
Yes
10100
10010```

## 样例 #3

### 输入

```
3 2 5```

### 输出

```
No```

# 题解

## 作者：Unordered_OIer (赞：9)

# CF1492D 题解
~~没参加的观光人来写篇题解/fad~~

## Description
给定 $a,b,k$，构造两个二进制数 $x,y$，使得 $x$ 的二进制和 $y$ 的二进制都由 $a$ 个 $1$ 和 $b$ 个 $0$ 组成，且 $x-y$ 的二进制恰好有 $k$ 个 $1$。

## Solution
下文将二进制数 $bin$ 的第 $k$ 位简写为 $bin[k]$。

貌似我的赛后思路和某位大佬的题解有些相似？

我们首先考虑构造一个最大的二进制串 $(11....1100...00)_2$ 作为 $x$。

然后我们就要考虑如何构造出 $y$。

因为要有 $k$ 个位置不同，并且二进制的减法中，只要有借位就会出现不同的 $1$。所以**考虑在 $x$ 的前面 $a$ 个 $1$ 中挑选出一个 $1$ ，将这个 $1$ 单独后移 $k$ 位即可**。

至于在挑选这个 $1$ 的时候，我们设当前枚举的位置 $pos$，首先 $x[pos]$ 必须 $=1$，且 $x[pos-k]$ 必须 $=0$，这样就可以恰好产生 $k$ 位不同，如果可以我们就继续递减这个 $pos$，直到最后一位为 $1$ 即可。

如果我们枚举完了所有的 $pos$ 以后 $pos \leq k$ 了，那么就无解。

反之则先输出 $x$，然后将 $x[pos]$ 和 $x[pos-k]$ 位对调后即为 $y$，再输出即可。

复杂度差不多就是 $\mathcal O(a+b)$，肯定是能过的。

---

## 作者：tommymio (赞：5)

手玩一下两个数 $x,y$ 其二进制表示中只存在 $1$ 位 $1$ 的情况。规定 $x\geq y$，设 $x$ 的二进制表示中 $1$ 在第 $i$ 位，$y$ 的二进制表示中 $1$ 在第 $j$ 位，那么 $x-y$ 的二进制表示中存在 $i-j$ 个 $1$。

再考虑一般情况。由于不存在前导零并且 $x\geq y$，所以 $x,y$ 的二进制表示中第 $a+b$ 位均为 $1$。我们根据上面这种特殊情况贪心构造一种方案。令 $x$ 的 $a+b-1$ 位为 $1$，$y$ 的 $a+b-k-1$ 位为 $1$。其余位 $x,y$ 按位都是相同的，并且要符合 $a$ 个 $0$，$b$ 个 $1$ 的限制，随便填填就好了。

可以证明这样贪心构造出的方案一定合法，或者不存在合法解。不合法的情况有几种：
- $a=0,k>0$
- $a>0,b=1,k>0$
- $a>0,b\neq1,k>a+b-2$

特判一下就好了。这题考试的时候写完没有交上去，呜呜呜。但机房 $\text{FST}$ 了一车面包人，就我和另一个神仙没有 $\text{FST}$（这太草了

```cpp
#include<cstdio>
int A,B;
int vis[200005],res[200005];
inline void solve(int n) {
	for(register int i=1;i<=n;++i) {
		if(B) {
			printf("1");
			--B;
		}
		else if(A) {
			printf("0");
			--A;
		}
	}
}
int main() {
	int a,b,k;
	scanf("%d%d%d",&a,&b,&k);
	if(k==0) {
		printf("Yes\n");
		for(register int i=1;i<=b;++i) printf("1");
		for(register int i=1;i<=a;++i) printf("0");
		printf("\n");
		for(register int i=1;i<=b;++i) printf("1");
		for(register int i=1;i<=a;++i) printf("0");
		return 0;
	}
	if(a==0) {printf("No\n");}
	else if(b==1) {printf("No\n");}
	else if(k>a+b-2) {printf("No\n");}
	else {
		a-=1; b-=2;
		
		A=a; B=b;
		printf("Yes\n");
		printf("1"); printf("1");
		solve(k-1); printf("0"); solve(a+b-k+1);
		printf("\n");
		
		A=a; B=b;
		printf("1"); printf("0");
		solve(k-1); printf("1"); solve(a+b-k+1);
	}
	return 0;
}
```



---

## 作者：KSToki (赞：5)

纪念 fst 场。
# 题目大意
给定 $a,b,k$，求两个二进制数 $x,y$，使得它们都有 $a$ 个 $0$，$b$ 个 $1$，并且 $x-y$ 有 $k$ 个 $1$。$x,y$ 不能有前导 $0$。
# 题目分析
本场最恶心的题目。本身不难，首先第一个位置得放一个 $1$，然后 $y$ 在最后一个位置放 $1$，$x$ 在前 $k$ 个位置处放 $1$，则 $x-y$ 一定形如 $\cdots011\cdots11$，此时已经满足有 $k$ 个 $1$，其它随便填，只要同一位置都是 $1$ 即可。判无解即为长度不够用，$a+b-1<=k$。

容易 fst 的地方就在特判了。

- $b=1$，并不是一定无解，$k=0$ 时有解。
- $a=0$，并不是一定无解，$k=0$ 时有解。
- $k=0$，注意一下填 $1$ 时的操作。

没了。
# 代码
我是怎么 fst 的？绝对没有更惨的，我特判了忘 `puts("YES")` 了。。。
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
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
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
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
int a,b,k;
int main()
{
	a=read();
	b=read();
	k=read();
	if(b==1)
	{
		if(k==0)
		{
			puts("YES");
			cout<<"1";
			for(R int i=1;i<=a;++i)
				cout<<"0";
			puts("");
			cout<<"1";
			for(R int i=1;i<=a;++i)
				cout<<"0";
			puts("");
			return 0;
		}
		else
		{
			puts("NO");
			return 0;
		}
	}
	if(a==0)
	{
		if(k==0)
		{
			puts("YES");
			for(R int i=1;i<=b;++i)
				cout<<"1";
			puts("");
			for(R int i=1;i<=b;++i)
				cout<<"1";
			puts("");
		}
		else
			puts("NO");
		return 0;
	}
	if(k<a+b-1)
	{
		puts("YES");
		int pos1=a+b,pos2=a+b-k,cnt=0;
		for(R int i=1;i<=a+b;++i)
		{
			if(i==pos2)
				cout<<1,++cnt;
			else if(cnt<b-(i<pos2))
				cout<<1,++cnt;
			else
				cout<<0;
		}
		puts("");
		cnt=0;
		for(R int i=1;i<=a+b;++i)
		{
			if(i==pos2&&pos1!=pos2)
			{
				cout<<0;
				continue;
			}
			if(i==pos1)
				cout<<1,++cnt;
			else if(cnt<b-1)
				cout<<1,++cnt;
			else
				cout<<0;
		}
		puts("");
	}
	else
		puts("NO");
    return 0;
}

```

---

## 作者：HC20050615 (赞：2)

这是我CF第一道FST的题。

# 翻译
有两个二进制数 $x$ 和 $y$，均由 $a$ 个 $0$ 和 $b$ 个 $1$ 组成（$y\le x$）。

令 $z=x-y$，使 $z$ 在二进制下表示时，有且仅有 $k$ 个 $1$。

给你 $a,b,k$，你需要构造一组 $x,y$ 满足上述条件。（注：不可以有前导零）

若无解，输出 No；若有解，先输出 Yes，然后输出 $x$ 和 $y$，以换行隔开。若有多解，输出任意一组即可。

# 题意分析
如果我们将两个数写成一样的，那么 $z$ 就会是 $0$，$1$ 的个数为 $0$。不妨设我们将其写成了 $11\cdots100\cdots0$ 的形式。很明显，由于 $y\le x$，所以在 $y$ 未变动时，$x$ 不能变动，那我们就来尝试变动 $y$：

我们变动的方式只有一种，就是将一个 $1$ 往后移，与其中的一个 $0$ 交换。我们先假设交换的是最后一个 $1$，我们会发现，这个 $1$ 每往后移动一位，就会多出一个 $1$(可以自己动手算一下，就不配具体的图了)。然后，我们再来移动倒数第二个 $1$，发现它可以比倒数第一个 $1$ 多提供一个 $1$。

我们最后可以总结出两条规律：

1. 当将一个 $1$ 向后移动 $i$ 个位置时，答案会多出 $i$ 个 $1$。
2. 当这个 $1$ 是倒数的第 $j$ 个 $1$ 时，答案会再多出 $j-1$ 个 $1$。

然后，我们就可以根据这两条规律来写代码了。但是，除了这两条以外，本题代码还有很多细节特判（~~不然我也不会 FST 了~~）

1. 当 $b=1$ 时，无解。因为唯一的一个 $1$ 要放在最前面，以防止出现前导零。
2. 当 $a=0$ 时，无解。因为没有 $0$ 来给你换。
3. 当 $k=0$ 时，即使满足条件 $1$ 或 $2$，也是有解的，只要保持原来的状态不动就行。
只有加了这三个特判才能过，不然就要 FST。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,k;
int main()
{
	cin>>a>>b>>k;
	if(k==0)
	{
		cout<<"YES"<<endl;
		for(int i=1;i<=b;i++)
		{
			cout<<1;
		}
		for(int i=1;i<=a;i++)
		{
			cout<<0;
		}
		cout<<endl;
		for(int i=1;i<=b;i++)
		{
			cout<<1;
		}
		for(int i=1;i<=a;i++)
		{
			cout<<0;
		}
		return 0;
	}
	if(a+b-1<=k||b<=1||a<1)
	{
		cout<<"NO"<<endl;
	}
	else
	{
		cout<<"YES"<<endl;
		for(int i=1;i<=b;i++)
		{
			cout<<1;
		}
		for(int i=1;i<=a;i++)
		{
			cout<<0;
		}
		cout<<endl;
		if(a>=k)
		{
			for(int i=1;i<b;i++)
			{
				cout<<1;
			}
			for(int i=1;i<=k;i++)
			{
				cout<<0;
			}
			cout<<1;
			for(int i=k+1;i<=a;i++)
			{
				cout<<0;
			}
			cout<<endl;
		}
		else
		{
			int t=k-a;
			for(int i=1;i<=b-t-1;i++)
			{
				cout<<1;
			}
			cout<<0;
			for(int i=b-t+1;i<=b;i++)
			{
				cout<<1;
			}
			for(int i=1;i<a;i++)
			{
				cout<<0;
			}
			cout<<1<<endl;
		}	
	}
	return 0;
}
```


---

## 作者：HenryHuang (赞：2)

# 「CF1492D」Genius's Gambit

~~真就人均 FST 呗~~

考虑如何得到一个二进制下的 $1$ 位。

显然有 $(10)_2-(01)_2=(1)_2$。

容易发现如果在这个数的两边增加任意多的 $1$ 或 $0$ 位不会影响答案中 $1$ 的个数，在这个数中间增加 $k$ 个 $0$ 位或 $1$ 位都会使答案中 $1$ 的个数增加 $k$。

记 $\mathrm{cnt}(x)$ 表示 $x$ 的 $1$ 位的个数，其中 $x$ 是一个二进制数。

举个例子：$\mathrm{cnt}((111010100)_2-(110010110)_2)=\mathrm{cnt}((101010)_2-(001011)_2)=5$

所以可以给出这样的一种构造方案：

首先将 $a$ 个 $1$ 和 $b$ 个 $0$ 按顺序排列为一个二进制数，如 $(11111111100000000)_2$。

设其从左至右第 $i$ 位为 $b_i$。

若 $p=0$，直接输出这个数两遍即可。

否则找到满足 $b_i=1$ 且 $b_{i+p}=0$ 的 $i(i\neq 1)$，交换 $b_i,b_{i+p}$。交换前后的两个数即为题目要求的 $x,y$。

注意这里 $i$ 不能为首位，否则 $y$ 会出现前导 $0$，不符合要求。

如果找不到即判断无解。

~~（我不知道对不对欢迎来叉）~~

```cpp
/*---Author:HenryHuang---*/
/*---Never Settle---*/
#include<bits/stdc++.h>
using namespace std;
string aa,bb;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int a,b,p;cin>>a>>b>>p;
	for(int i=1;i<=b;++i) aa+='1';
	for(int i=1;i<=a;++i) aa+='0';
	int lst=a+b-1;
	while((aa[lst-p]=='0'||aa[lst]=='1')&&lst-p>=0) --lst;
	if(lst-p<=0&&p!=0) cout<<"NO\n",exit(0);
	cout<<"YES\n";cout<<aa<<'\n';
	swap(aa[lst],aa[lst-p]);
	cout<<aa<<'\n';
	return 0;
}
```





---

## 作者：xuezhe (赞：1)

设 $n=a+b$。

先讲一下思考过程中比较模糊的思路：构造 $x$ 时应尽可能大，所以直接令其前 $b$ 位均为 $1$；而构造 $y$ 的过程中可以考虑将 $x$ 中的 $b-1$ 位给直接扣掉，剩下 $1$ 位向后拉形成一个连续的长度为 $k$ 的段。

根据上面的思路，考虑我们能构造出的最大的 $k$，可以发现即为 $n-2$。

构造方法：

+ 首先 $x$ 构造成能构造出的最大的数，即前 $b$ 位为 $1$，后 $a$ 位为 $0$。

+ 然后考虑如何构造 $y$，首先由于题目限制，$y$ 最高位只能为 $1$，故 $x-y$ 最高位必为 $0$。

+ 考虑后面的 $n-1$ 位，为了令形成的连续的 $1$ 段尽可能长，故我们保留这 $n-1$ 中的最高位，对于剩下 $b-1$ 位 $x$ 为 $1$ 的位，令 $y$ 的这 $b-1$ 位也为 $1$。

+ 扣掉前面这部分之后 $x$ 只剩下 $2^{n-2}$。再减去 $1$ 即可得到 $2^{n-2}-1$，恰有 $n-2$ 个 $1$。

可以发现这已经是一个很紧的上界了，所以不必继续优化。

事实上有了这个方法我们可以类似的推广：首先执行前三点，然后再将 $y$ 加上 $2^{n-2-k}$ 即可。

这样就做完了，处理好进位即可。

$a=0$ 和 $b=1$ 这两个边界处理清楚。

时间复杂度 $O(n)$。

Code:
```cpp
int a,b,k;
 
void fakemain(){
    Read(a),Read(b),Read(k),--b;
    if(!a){
        if(k){
            puts("No");
        }else{
            puts("Yes");
            for(int i=0;i<=b;++i)
                putchar('1');
            putchar(10);
            for(int i=0;i<=b;++i)
                putchar('1');
            putchar(10);
        }
    }else if(!b){
        if(k){
            puts("No");
        }else{
            puts("Yes");
            putchar('1');
            for(int i=0;i<a;++i)
                putchar('0');
            putchar(10);
            putchar('1');
            for(int i=0;i<a;++i)
                putchar('0');
            putchar(10);
        }
    }else{
        if(k<=a+b-1){
            puts("Yes");
            putchar('1');
            for(int i=0;i<b;++i)
                putchar('1');
            for(int i=0;i<a;++i)
                putchar('0');
            putchar(10);
            putchar('1');
            if(k<=b){
                for(int i=0;i<b-k;++i)
                    putchar('1');
                putchar('0');
                for(int i=b-k;i<b;++i)
                    putchar('1');
                for(int i=1;i<a;++i)
                    putchar('0');
            }else{
                putchar('0');
                for(int i=0;i<b-1;++i)
                    putchar('1');
                for(int i=1;i<k-b+1;++i)
                    putchar('0');
                putchar('1');
                for(int i=k-b+1;i<a;++i)
                    putchar('0');
            }
            putchar(10);
        }else{
            puts("No");
        }
    }
}
```

---

## 作者：Phartial (赞：0)

# 翻译
给定三个数$a$,$b$,$k$，求两个没有前导零的二进制数$x$,$y$使得$x$和$y$各有$a$个$0$与$b$个$1$，且$x-y$有$k$个$1$,若无解输出$-1$。
# 思路
- 由于没有前导零，所以两数第一位一定是$1$。
- 再考虑以下式子：$ 1\underbrace{110\cdots}_{x}1\underbrace{111000\cdots0}_{k}-1\underbrace{110\cdots}_{x}0\underbrace{111000\cdots1}_{k}=\underbrace{111111\cdots}_{k}$
- 我们发现只要$a+b-2\ge k$且$a\ge1$且$b\ge2$的话就一定可以构造出答案，且一定是上面的形式。
# 注意事项
- 当$k=0$时需要特殊处理。
# 小知识
- 构造函数`string(size_t n,char c)`返回长度为$n$的一个字符串，且用c填充
# Code
```cpp
#include <iostream>
using namespace std;
int a, b, k, x, y;
int main() {
  cin >> a >> b >> k;
  if (!k) { // 若k=0,则使得x=y即可
    cout << "Yes" << endl;
    string x = string(b, '1') + string(a, '0');
    cout << x << endl << x << endl;
  } else if (!a || b < 2 || a + b - 2 < k) {
    cout << "No" << endl;
  } else {
    cout << "Yes" << endl;
    for (int o = 0; o < 2; ++o) {
    int x = a + b - k - 2, c = min(b - 2, x);
    cout << "1" << string(c, '1') << string(x - c, '0') << 1 - o << string(b - 2 - c, '1') << string(a - 1 - x + c, '0') << o << endl;
    }
  }
  return 0;
}
```

##### 应该是全谷不压行的最短代码了，望通过

---

## 作者：小恐 (赞：0)

这题不得不感谢比赛时善良的样例。

根据样例，我们可以得出一个大体的构造方法，即让结果是连续 $k$ 个 $1$，即：
```
x = 1 ... 1 ... 0
y = 1 ... 0 ... 1
```

每个省略的部分 $x$ 和 $y$的对应的位置是相同的，所以上下的 $1$ 和 $0$ 的个数是相同的。

所以第二个省略的位置共有 $k-1$ 个字符。

此时 $x-y=2^k-1$，有 $k$ 个 $1$。

接下来则要考虑一些细节。

如何判断 No 呢？

首先 $k=0$ 时是一个非常特殊的情况，我们一定能构造出来，即 $x=y$。

下面考虑 $k\ne0$的情况：

当 $a=0$ 或者 $b=1$ 时，一定只能 $x=y$，这时就是 No。

当 $k\ge a+b-1$ 时，$y\ge 2^{a+b-1},x-y\ge 2^{a+b-1}-1$，则 $x\ge 2^{a+b}-1$。显然 $x$ 与 $y$ 的 $0$ 和 $1$ 的个数是不可能相同的，输出 No。

其他的情况就按开头给出的构造方法构造就可以了。

---

## 作者：registerGen (赞：0)

# Solution

先特判一下 $k=0$ 与 $a=0,b=1$ 的情况。

观察样例可知构造方法如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/b4s0jw5k.png)

方框里的数上下必须相等。例如：

```plain
11 1100 0 00
10 1100 1 00
```

这么构造最多可以使 $x-y$ 产生 $a+b-2$ 个 $1$。

所以如果 $a+b-2<k$，输出 `No`，否则输出 `Yes`。剩下的就是模拟了。

# Code

```cpp
int a,b,k;
int s[N+10],t[N+10];
void mian(){
	a=ri(),b=ri(),k=ri();
	if(k==0){
		printf("Yes\n");
		rep(i,1,b)printf("1");
		rep(i,1,a)printf("0");
		puts("");
		rep(i,1,b)printf("1");
		rep(i,1,a)printf("0");
		puts("");
		return;
	}
	if(b==1||a==0)No;
	if(a+b-2<k)No;
	printf("Yes\n");
	s[1]=1,t[1]=1;
	s[2]=1,t[2]=0;
	s[k+2]=0,t[k+2]=1;
	int tot1=b-2;
	for(int i=3;i<=k+1;i++){
		if(tot1>0)tot1--,s[i]=1,t[i]=1;
		else s[i]=0,t[i]=0;
	}
	for(int i=k+3;i<=a+b;i++){
		if(tot1>0)tot1--,s[i]=1,t[i]=1;
		else s[i]=0,t[i]=0;
	}
	rep(i,1,a+b)printf("%d",s[i]);puts("");
	rep(i,1,a+b)printf("%d",t[i]);puts("");
}
```

---

## 作者：OranJun (赞：0)

先考虑一种特殊情况。

假设你有足够的 $0$ 和 $1$，相减去凑出 $k$ 个 $1$ 怎么做

     _11000...0000

    --10000...0001
    --------------
       1111...1111
但如果你没有 $k-1$ 个 $0$ 怎么办？

把 $1$ 也拿来一起凑不就好了/jk

更进一步，就是中间凑齐 $k-1$ 个相同的，然后多余的放在末尾，就做好了。



------------
接下来是特判部分。

    1.如果k==0  两个一样输出就好了。
    2.如果k!=0&&(a==0||b==1) 无解。
    3.k>=a+b-1 这时不管怎样都拼不起来。

------------
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i=a;i<=b;++i)
#define rf(i,a,b) for(int i=a;i>=b;--i)
template<typename T>
inline void read(T &x){
	char c=getchar();x=0;bool f=0;
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	x=f?-x:x;
}
typedef long long ll;
int a,b,k,aa,bb,kk;//a是0，b是1 
const int N=4e5+5;
char s1[N],s2[N];
int len1,len2;
int main(){
	read(a),read(b),read(k);
	aa=a,bb=b;kk=k;
	if(!k){//特判的第一部分
		puts("YES");
		fr(i,1,b)printf("1");fr(i,1,a)printf("0");puts("");
		fr(i,1,b)printf("1");fr(i,1,a)printf("0");puts("");
		return 0;
	}
	if(k>=a+b-1||b==1||a==0){puts("NO");return 0;}//特判的第二部分
	
	//part1
	s1[++len1]='1',s1[++len1]='1';--b,--b,--a;//开头
	if(a>=k-1){//中间部分
		a-=(k-1);
		fr(i,1,k-1)s1[++len1]='0';
	} else{
		k-=a;
		fr(i,1,a)s1[++len1]='0';a=0;
		fr(i,1,k-1)s1[++len1]='1';
		b-=(k-1);
	}
	s1[++len1]='0';
	fr(i,1,a)s1[++len1]='0';fr(i,1,b)s1[++len1]='1';//多余的放在结尾
	
	//part2 类似part1
	s2[++len2]='1',s2[++len2]='0';--bb,--bb,--aa;
	if(aa>=kk-1){
		aa-=(kk-1);
		fr(i,1,kk-1)s2[++len2]='0';
	} else{
		kk-=aa;
		fr(i,1,aa)s2[++len2]='0';aa=0;
		fr(i,1,kk-1)s2[++len2]='1';
		bb-=(kk-1);
	}
	s2[++len2]='1';
	fr(i,1,aa)s2[++len2]='0';fr(i,1,bb)s2[++len2]='1';
	//b>1&&k!=0
	puts("YES");
	fr(i,1,len1)printf("%c",s1[i]);puts("");
	fr(i,1,len2)printf("%c",s2[i]);
	return 0;
}


---

## 作者：Ephemeroptera (赞：0)

可能更好的阅读体验：[233](https://www.cnblogs.com/jojojojojob/p/14437768.html)




魔鬼题，机房仅有一人没有被 $\texttt{FST}$。  
注意到类似于这样的一种情况，相减后总是会贡献出 $len$ 长度的 $1$：(以下为两个长度为 $len + 1$ 的字符串)  
$\texttt{1111...1100...0000}$  
$\texttt{1011...1100...0001}$  
所以我们一开始令第一个串类似于这样的结构 ： 
$\texttt{1111...1100...0000}$
这样只需找到这个序列的第 $i$ 位交换到第 $i + k$ 位即可得到第二个串。(满足 $a[i] = 1,a[i + k] = 0$)  
但是此题边界条件很多：
首先考虑构造的时候条件：  
满足 $k \ge a + b - 1$ 时无解。  
当 $a = 0$ 时，当且仅当 $k = 0$ 有解。  
当 $b = 1$ 时，当且仅当 $k = 0$ 有解。  
但还有一个特例 :  
$a = 0,b = 1,k = 0.$  
这一个特例并不满足 $k \le a + b - 2$ 但确实有解。
```cpp
#include <bits/stdc++.h>


using namespace std;
typedef long long ll;
char ans[300000];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);	
	int a,b,k;
	cin >> a >> b >> k;
	if(!a) {
		if(!k) {
			cout << "Yes" << '\n';
			for(int i = 1;i <= b;i++) {
				cout << "1" ;
			}
			cout << '\n';
			for(int i = 1;i <= b;i++) {
				cout << "1" ;
			}
		} else {
			cout << "No" << '\n';
		}
		return 0;
	}	
	if(b == 1) {
		if(!k) {
			cout << "Yes" << '\n';
			cout << '1' ;
			for(int i = 1;i <= a + b - 1;i++) {
				cout << '0';
			}
			cout << '\n';cout << '1' ;
			for(int i = 1;i <= a + b - 1;i++) {
				cout << '0';
			}
			cout << '\n';
		} else {
			cout << "No";
			return 0;
		}
		return 0;
	}
	if(k >= a + b - 1) {
		cout << "No" << '\n';
		return 0;
	}

	cout << "Yes" << '\n';
	for(int i = 1;i <= b;i++) ans[i] = '1';
	for(int i = b + 1;i <= a + b;i++) ans[i] = '0';
	for(int i = 1;i <= a + b;i++) cout << ans[i];cout << '\n';
	for(int i = 2;i <= a + b;i++) {
		if(ans[i] == '1' && ans[i + k] == '0') {
			swap(ans[i],ans[i + k]);
			break;
		}
	}
	for(int i = 1;i <= a + b;i++) {
		cout << ans[i];
	}
	return 0;
} 
```


---

