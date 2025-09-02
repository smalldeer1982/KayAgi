# Chips on the Board

## 题目描述

You are given a board of size $ n \times n $ ( $ n $ rows and $ n $ colums) and two arrays of positive integers $ a $ and $ b $ of size $ n $ .

Your task is to place the chips on this board so that the following condition is satisfied for every cell $ (i, j) $ :

- there exists at least one chip in the same column or in the same row as the cell $ (i, j) $ . I. e. there exists a cell $ (x, y) $ such that there is a chip in that cell, and either $ x = i $ or $ y = j $ (or both).

The cost of putting a chip in the cell $ (i, j) $ is equal to $ a_i + b_j $ .

For example, for $ n=3 $ , $ a=[1, 4, 1] $ and $ b=[3, 2, 2] $ . One of the possible chip placements is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1879B/41f651e9026b79c2105cacdfb396235f2e97b44b.png) White squares are emptyThe total cost of that placement is $ (1+3) + (1+2) + (1+2) = 10 $ .

Calculate the minimum possible total cost of putting chips according to the rules above.

## 说明/提示

The first test case of the example is described in the statement.

## 样例 #1

### 输入

```
4
3
1 4 1
3 2 2
1
4
5
2
4 5
2 3
5
5 2 4 5 3
3 4 2 1 5```

### 输出

```
10
9
13
24```

# 题解

## 作者：Nuclear_Fish_cyq (赞：5)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1879B)

[CF原题传送门](https://codeforces.com/problemset/problem/1879/B)

[提交记录](https://www.luogu.com.cn/record/126720071)

## 题目大意

在一个 $n\times n$ 的网格里，我们设一个点 $(i,j)$ 的代价为 $a_i + b_j$，你要选出一些点，选取的点所在的横行或纵列会被填充，要求：

1.网格里的每一个点都被填充。

2.选择的点的代价之和最少。

## 做法

考虑贪心。

先上结论：选择 $n$ 个点，且选择的点要么全在同一行，要么全在同一列。

接下来简单说明一下为什么。

首先，很显然，如果选的点数量大于 $n$，那么不会是最优的。如果选的点数量小于 $n$，那么不可能覆盖网格的每一个点。

然后，我们选的点都在一行或都在一列是能够让每一个网格中的点都被填充的。这也很显然。

接着，我们重新看眼怎么样的方案能够填充整个网格：要么每一行都有格子被选，要么每一列都有格子被选。

我们先考虑每行都要有格子被选如何最优。我们可以发现，只要保持每行都有格子被选，格子想放在哪一列就放在哪一列。那就可以贪心了：我们把每一个格子都放在对应花费最小的哪一列。

对于每列都要有格子被选的情况也类似，我们直接把每一个格子都放在花费最小的行上。

那我们就可以用贪心了：分找最小行和找最小列两种方法来选择格子，在选取最优的方案。

上代码。码风可能比较奇怪，请不要太在意。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t, n, a[300000], b[300000], mina, minb, suma, sumb;

int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	for(int kk = 0; kk < t; kk++){
		suma = 0;
		sumb = 0;
		mina = INT_MAX;
		minb = INT_MAX;
		cin >> n;
		for(int i = 0; i < n; i++){
			cin >> a[i];
			suma += a[i];
			mina = min(mina, a[i]);
		}
		for(int i = 0; i < n; i++){
			cin >> b[i];
			sumb += b[i];
			minb = min(minb, b[i]);
		}
		cout << min(mina * n + sumb, minb * n + suma) << endl;
	}
	return 0;
}

```

剩下的只需要注意 `int` 可能会爆就好了。

---

## 作者：Κarrу5307 (赞：5)

发现这样一件事情：如果把 $n$ 行全部拿完，无论列如何，都满足条件；同样，如果把 $n$ 列全部拿完，无论行如何，都满足条件。

同时可以发现，任何一种满足条件的选择方案，要么选完 $n$ 行，要么选完 $n$ 列。

因此，贪心地，拿完 $n$ 行时，希望列的代价都尽量小，所以全部选择最小的 $b$，故代价是 $\sum a_i + n\times \min\{b\}$。拿完 $n$ 列同理。两种情况取较小者输出即可。

---

## 作者：CheZiHe929 (赞：1)

# CF1879B 题解

### 题目大意

有一个 $n \times n$ 的矩阵，对于一个点 $(i,j)$，你可以付出 $a_i + b_j$ 的代价将第 $i$ 行和第 $j$ 列的所有数覆盖掉，问覆盖掉整个矩阵所需要的最小代价。

### 简要思路

考虑贪心。我们无非只有两种选点的方法：选中所有的行和一个列，选中所有的列和一个行。这样我们只需要求出 $\sum a_i , \sum b_i$ 以及 $a,b$ 数组中的最小值即可，最后的答案就是这两种情况取个 `min`。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'

int T; 
int a[300005];
int b[300005];

signed main(){
	std::cin>>T;
	while(T--){
		int n;
		std::cin>>n;
		for(int i=1;i<=n;i++)std::cin>>a[i];
		for(int j=1;j<=n;j++)std::cin>>b[j];
		
		int sum_a=0,sum_b=0;
		int min_a=1e9,min_b=1e9;
		for(int i=1;i<=n;i++){
			sum_a+=a[i];
			sum_b+=b[i];
			min_a=std::min(min_a,a[i]);
			min_b=std::min(min_b,b[i]);
		}
		
		std::cout<<std::min(sum_a+min_b*n,sum_b+min_a*n)<<endl;
	}
	
	return 0;
}
```

**THE END.**

**THANK YOU.**

---

## 作者：樱雪喵 (赞：1)

被诈骗了，赛时卡 B 20min 来着。怎么能这么菜的。

## Description

给一个 $n\times n$ 的网格，你要在上面选一些点。选择点 $(i,j)$ 的代价是 $a_i+b_j$。每选择一个点，网格上与它同行或同列的点均被覆盖。求覆盖满整个网格的最小代价。

$n\le 3\times 10^5$。

## Solution

覆盖满整个棋盘等价于对于网格上的任意位置，与它同行或同列至少有一个点被选中。

发现选择方案合法的充要条件是每行都选一个点或每列都选一个点。

充分性显然，对于必要性考虑反证：若某种方案行和列均没有选满，那么必然存在某个格子行和列都没被选。这是不合法的。

而对于每行都选满的情况，行对答案的贡献是固定的 $\sum a_i$，只需贪心地把他们都选在 $b_j$ 最小的那一列即可。列的情况同理，答案即两个情况取 $\min$。

```cpp
#define int long long
const int N=3e5+5;
int T,n,a[N],b[N];
signed main()
{
    T=read();
    while(T--)
    {
        n=read();
        for(int i=1;i<=n;i++) a[i]=read();
        for(int i=1;i<=n;i++) b[i]=read();
        int mna=a[1],mnb=b[1];
        int suma=a[1],sumb=b[1];
        for(int i=2;i<=n;i++)
        {
            mna=min(mna,a[i]),mnb=min(mnb,b[i]);
            suma+=a[i],sumb+=b[i];
        }
        printf("%lld\n",min(mna*n+sumb,mnb*n+suma));
    }
    return 0;
}
```

---

## 作者：_空白_ (赞：0)

看题一段时间后发现，要么每一行各有一个芯片，要么每一列各有一个芯片，否则就会有格子影响不到，无法满足规则。

那么我们只要把所有芯片都放在代价最小的那一行（列）上，最后比较都放都放在同一行上代价小还是都放在同一列上代价小即可

$AC$ $code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int ans=0,fh=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')fh=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){ans=ans*10+ch-'0';ch=getchar();}
	return ans*fh;
}
 
int main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		long long suma=0,mina=0x7f7f7f7f,sumb=0,minb=0x7f7f7f7f;
		for(int i=1;i<=n;i++)
		{
			long long a=read();
			suma+=a;
			mina=min(a,mina);
		}
		for(int i=1;i<=n;i++)
		{
			long long b=read();
			sumb+=b;
			minb=min(b,minb);
		}
		cout<<min(suma+minb*n,sumb+mina*n)<<"\n";
	}
	return 0;
}
```


---

## 作者：Wi_Fi (赞：0)

很显然，如果每一列都有点被选中，那么不管每一行怎么样，问题都解决了；如果每一行都有点被选中，那么不管每一列怎么样，问题都解决了。

所以我们就分这两种情况来解决问题，如果我们只考虑每一列，那么我们把 $a_i$ 最小的一行的点全部选中，问题的答案是最优的；如果我们只考虑每一行，那么我们把 $b_i$ 最小的一列的点全部选中，问题的答案是最优的。

太简单了，不废话了，直接上代码吧：

```cpp
#include<bits/stdc++.h>

using namespace std;

const long long INF=1e9,N=3e5+5;
long long i,n,a[N],b[N],T,ma,mb,sa,sb;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		ma=mb=INF,sa=sb=0;
		for(i=1;i<=n;i++)cin>>a[i];
		for(i=1;i<=n;i++)cin>>b[i];
		for(i=1;i<=n;i++)ma=min(ma,a[i]),mb=min(mb,b[i]),sa+=a[i],sb+=b[i];
		cout<<min(ma*n+sb,mb*n+sa)<<"\n";
	}
	return 0;
}
```


---

## 作者：Chinshyo (赞：0)

题目要求“满足 $x = i$ 或 $y = j$ ”，由于题目求最小代价，我们可以看作是要求取的点覆盖一整个十字形，因为这样可以做到一次操作剩余的格子数更少。

![](https://z1.ax1x.com/2023/09/28/pPboDOg.png)


求最小代价，可以从行、列两个角度上来看。单看行，**我们会发现每一行至少有一个被取的格子**。否则这一行就不会被完全覆盖。从列上看也是如此，**每一行至少有一个被取的格子**。

举个例子：

![](https://z1.ax1x.com/2023/09/28/pPbogkn.png)

从行上观察这张图，红色为被取的点。下一步的最优操作一定是在第一行取一个点，因为这样就可以一步将整个画面覆盖完。而在其他地方覆盖都至少要2步。

行上观察时，为了使代价最小，又由于每一行至少有一个被取的格子，因此每一行尽量少取，即**每一行仅取列上最小的数**。列上同理。

因此得出结论：

行上观察时：将每一行的数加列上最小的数。

列上观察时：将每一列的数加行上最小的数。



最后将两者取最小值输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300005], b[300005];
int main() {
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		int mina = INT_MAX, minb = INT_MAX;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			mina = min(mina, a[i]);
		}
		for(int i = 1; i <= n; i++) {
			cin >> b[i];
			minb = min(minb, b[i]);
		}
		
		int ans1 = 0, ans2 = 0;
		for(int i = 1; i <= n; i++) {
			ans1 += a[i] + minb;
		}
		for(int i = 1; i <= n; i++) {
			ans2 += b[i] + mina;
		}	
		cout << min(ans1, ans2) << endl;
	}
	return 0;
}
```


---

## 作者：JimmyDong (赞：0)

## 思路
我们需要在每行或者每列放上筹码，如果只考虑要在每列放上筹码，那么一定会选择填满代价最少的那一行；如果只考虑要在每行放上筹码，那么一定会选择填满代价最少的那一列。

所以，只有两种情况可以是最小值：

- 每行都选满，取 $b_i$ 最小的那一列。

- 每列都选满，取 $a_i$ 最小的那一行。

算出两种情况：取最小值即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[300005],b[300005];
long long maxnum1,maxnum2,sum1,sum2;
void solvea(int x)
{
    maxnum1=min(maxnum1,a[x]);
    sum1+=a[x];
}
void solveb(int x)
{
    maxnum2=min(maxnum2,b[x]);
    sum2+=b[x];
}
int main()
{
	scanf("%lld",&t);
	for(int o=1;o<=t;o++)
    {
		maxnum1=1e9;
        maxnum2=1e9;
        sum1=0;
        sum2=0;
		cin>>n;
        //第一种
		for(int i=1;i<=n;i++)
        {
            scanf("%lld",&a[i]);
            solvea(i);
        }
        //第二种
		for(int i=1;i<=n;i++)
        {
            scanf("%lld",&b[i]);
            solveb(i);
        }
		printf("%lld\n",min(maxnum1*n+sum2,maxnum2*n+sum1));
	}
	return 0;
}
```


---

## 作者：DerrickLo (赞：0)

结论题。

可以发现最小的时候就是把 $a_i$ 最小的一行全选上或者把 $b_j$ 最小的一行全选上，因为我们需要把所有行都选上或把所有列都选上，那选择最小的另一维显然最优。两种情况的答案算出后，取最小值即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[300005],b[300005];
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		int maxa=INT_MAX,maxb=INT_MAX,sum1=0,sum2=0;
		for(int i=1;i<=n;i++)cin>>a[i],maxa=min(maxa,a[i]),sum1+=a[i];
		for(int i=1;i<=n;i++)cin>>b[i],maxb=min(maxb,b[i]),sum2+=b[i];
		cout<<min(maxa*n+sum2,maxb*n+sum1)<<"\n"; 
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

有一个 $n\times n$ 的棋盘，有两个数列 $a,b$。你要在格子里放筹码，使：

- 对于每个格子，它所在的一行或一列之中必须有一个格子放了一个筹码。

在 $(i,j)$ 放筹码的花费是 $a_i+b_j$，求最小花费。

**分析**

大诈骗。其实把题目稍微转换一下题意，就会发现，放筹码的条件不就是每行或者每列都有筹码吗？于是把每行放筹码的代价与每列的取 $\min$ 就做完了。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve()
{
	long long n,mina=1e9,minb=1e9,suma=0,sumb=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		long long tp;
		cin>>tp;
		suma+=tp;
		mina=min(mina,tp);
	}
	for(int i=1;i<=n;i++)
	{
		long long tp;
		cin>>tp;
		sumb+=tp;
		minb=min(minb,tp); 
	} 
	cout<<min(mina*n+sumb,minb*n+suma)<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}

---

## 作者：Natori (赞：0)

>[CF1879B Chips on the Board](https://www.luogu.com.cn/problem/CF1879B)

诈骗贪心题。

------------
问题的一种刻画方式是：选择若干个有序点对 $(i,j)$，每个这样的点对代价为 $a_i+b_j$，要求所有 $i$ 或所有 $j$ 的并集为 $[1,n] \cap \mathbb{N}$，最小化代价之和。

考虑把点对的贡献拆掉。由于一定会把某一个数列的数选完，所以计算出两个数列的和 $sa,sb$。然后对于剩下的 $n$ 个数，贪心地选另外一个数列的最小值即可。时间复杂度 $\mathcal{O}(n \log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
namespace Fast_In_Out{
	char buf[1<<21],*P1=buf,*P2=buf;
	#define gc (P1==P2&&(P2=(P1=buf)+fread(buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
	int read(){
		int f=1,x=0;
		char c=gc;
		while(c<'0'||c>'9'){
			if(c=='-')
			    f=-1;
			c=gc;
		}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';
			c=gc;
		}
		return f*x;
	}
	void write(int x){
		if(x<0)
			x=-x,putchar('-');
		if(x>9)
			write(x/10);
		putchar(x%10+'0');
	}
	#undef gc
}
using namespace Fast_In_Out;
const int N=3e5+8,oo=1e18+8;
int n,a[N],b[N];
void solve(){
	for(int i=1;i<=n;i++)
		a[i]=b[i]=0;
	n=read();
	int mna=oo,mnb=oo;
	int sa=0,sb=0;
	for(int i=1;i<=n;i++)
		a[i]=read(),mna=min(mna,a[i]),sa+=a[i];
	for(int i=1;i<=n;i++)
		b[i]=read(),mnb=min(mnb,b[i]),sb+=b[i];
	int ans=min(sa+mnb*n,sb+mna*n);
	write(ans),putchar('\n');
}
bool Mend;
signed main(){
//	File_Work();
	fprintf(stderr,"%.3lf MB\n\n\n",(&Mbegin-&Mend)/1048576.0);
	int testnum=read();
	while(testnum--)
		solve();
	fprintf(stderr,"\n\n\n%.0lf ms",1e3*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

