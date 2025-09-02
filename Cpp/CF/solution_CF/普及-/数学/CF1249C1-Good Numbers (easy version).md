# Good Numbers (easy version)

## 题目描述

简单难度与困难难度的唯一差别是$n$的取值范围

现在给出一个定义：Good Number（下文以好数代替），好数是指可以变成$3$的**不同**次幂的加和的数

例如：

$30$ 是好数 $30=3^3+3^1$

$1$ 是好数 $1=3^0$

$12$ 是好数 $12=3^2+3^1$

$2$ 不是好数，因为$2=3^0+3^0$，不符合不同次幂的条件

$19$ 不是好数，例如$19=3^2+3^2+3^0=3^2+3^1+3^1+3^1+3^0$，不符合不同次幂的条件

$20$不是好数，同理不符合不同次幂的条件，无法把$20$分为$3$的不同次幂的加和

现在给你一些正整数$n$，对于每个$n$请你给出一个最小的$m$满足：①$m$是好数 ②$n≤m$

## 样例 #1

### 输入

```
7
1
2
6
13
14
3620
10000
```

### 输出

```
1
3
9
13
27
6561
19683
```

# 题解

## 作者：WangBng (赞：3)

这题是一道裸的 01 背包，设 $w_i=3^{i-1}$，用 01 背包求每个数的方案数，如果方案数 $>0$ 则该数符合条件。

转移方程是：$f_j=f_{j-w_i}+f_j$。

Code:

```cpp
#include<iostream>
using namespace std;
int w[15];
long long f[100005];
int main(){
	int n=11,q,x,V=100000;
	w[1]=1;
	for(int i=2;i<=n;i++){
		w[i]=w[i-1]*3;
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=V;j>=w[i];j--){
			f[j]+=f[j-w[i]];
		}
	}
	cin>>q;
	while(q--){
		cin>>x;
		for(int i=x;i<=1e5;i++){
			if(f[i]>0){
				cout<<i<<endl;
				break;
			}
		}
	}
	return 0;
} 
```


---

## 作者：Priori_Incantatem (赞：3)

hard version 正解：状态压缩 + 二分查找

看到题目中“每个 $3$ 的幂最多只能使用一次”，可以很容易想到用状态压缩来解决

对于每一个好的数（Good Number）$x$，可以将它用一个二进制数 $y$ 表示。其中，如果对应的二进制数的第 $i$ 位为 $1$，代表构成 $x$ 时使用了 $3^i$

这样，我们就将散落在区间中的好数集中了起来，二分查找大于等于 $n$ 的最小好数即可

时间复杂度：$\operatorname{O}((\log_2n)^2)$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const long long Maxn=50;
const long long n=39;
long long a[Maxn],m;
inline long long read()
{
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
long long get(long long x) // 计算二进制数x对应的好数
{
	long long ret=0;
	for(long long i=0;i<=n;++i)
	if((x>>i) & 1)ret+=a[i];
	return ret;
}
int main()
{
//	freopen("in.txt","r",stdin);
	a[0]=1;
	for(long long i=1;i<=n;++i)
	a[i]=a[i-1]*3;
	long long T=read();
	while(T--)
	{
		m=read();
		long long l=1,r=(1ll<<n)-1;
		while(l<r) // 二分
		{
			long long mid=(l+r)>>1;
			long long tmp=get(mid);
			if(tmp>=m)r=mid;
			else l=mid+1;
		}
		printf("%lld\n",get(l));
	}
	return 0;
}
```

---

## 作者：Karry5307 (赞：2)

### 题意

有$q$组询问，每组询问给定$n$，要你求出一个最小的$m$使得$m\geq n$且$m$的三进制表示下没有$2$。

$\texttt{Data Range:}1\leq q\leq 500,1\leq n\leq 10^{4}$

### 题解

贪心好题。

首先第一步我已经说了，把它表示成三进制。

假设把$n$加上$k$能得到$p$。

如果$k$不足以使$n$的三进制表示中$2$所处的位置中的最高位发生进位，那么$p$是不符合要求的，因为那个$2$还是在那里。

于是我们可以模拟进位，把这一位以及低于他的位全部改成$0$，将比这这一位高且相邻的位加以。

由于这一位是$2$所处位置的最高位，所以比它还高的位只可能是$0$和$1$，加上$1$后是$1$和$2$。

万一加上$1$后又出现一个新的$2$的为怎么办呢？没关系，我们以这个数作为$n$，再来一遍，直到没有位置有$2$。

这里用一个例子来解释一下，比如$n=(1001111121021)_3$，首先找出$2$所处的位置中的最高位，然后模拟进位，得到$(1001111200000)_3$，发现还有一个位置$2$，就重新来，得到$(1001112000000)_3$，如此往复，直到没有位置为$2$。最终我们得到答案就是$(1010000000000)_3$。

这个操作其实是将$2$所处的位置中的最高位前面的连续的$1$全部改为$0$，而这一段$1$前面的$0$改为$1$，然后就完结撒花了qwq

时间复杂度$O(q\log n)$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=2e5+51;
ll test,tot,kk,ptr,res;
ll num[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline void solve()
{
	kk=read();
	memset(num,0,sizeof(num)),tot=0,res=0;
	while(kk)
	{
		num[++tot]=kk%3,kk/=3;
	}
	for(register int i=tot;i;i--)
	{
		if(num[i]==2)
		{
			num[i]=0,ptr=i+1;
			for(register int j=i-1;j;j--)
			{
				num[j]=0;
			}
			while(num[ptr]==1)
			{
				num[ptr++]=0;
			}
			num[ptr]=1,tot=max(tot,ptr);
		}	
	} 
	for(register int i=tot;i;i--)
	{
		res=(res*3)+num[i];
	}
	printf("%lld\n",res);
}
int main()
{
	test=read();
	for(register int i=0;i<test;i++)
	{
		solve();
	}
}
```

---

## 作者：zhanghaosong (赞：1)

# CF1249C1 Good Numbers (easy version) 题解

看楼下大佬神犇们都是什么状压啊，二分啊，蒟蒻内心瑟瑟发抖，但是本蒟蒻想到直接求三进制岂不更好！

### 前置好物

[蒟蒻的AC记录](https://www.luogu.com.cn/record/120176297)|[本题 in 洛谷](https://www.luogu.com.cn/problem/CF1249C1)|[本题 in Codeforces](https://codeforces.com/problemset/problem/1249/C1)

### 解析

对于任何一个数，将其转换为一个三进制数时，它的每一位必须是 $0$ 或 $1$，才能称其为“好数”。

为什么呢？

我们记一个三进制数中第 $k$ 位中是 $2$，那么这一位化为 $10$ 进制中就是 $2\times 3^k$，立刻可以化成 $3^k+3^k$，不符合“好数”的定义。

那我们要求出 $m$，该怎么办呢？

最直接的方法：**暴力枚举**！从 $n$ 开始枚举，直到 $i$ 是“好数”是 `break` 掉就行。

### 代码

再次不贴代码了（快逃哇）

---

## 作者：zk_y (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1249C1)

这道题目其实没有那么难，我们只需要使用一个三进制来进行计算就可以了，不过最好还是记忆化一下。（怕超时）

我们发现如果这个数是一个好数，那么他的三进制数一定**只含有** $0$ 和 $1$。

我们可以给出简易的证明。

反证：如果存在一个好数不只含有 $0$ 或 $1$。（其实也就是含有 $2$）

那么，由进制的概念可以得知，这个数的一部分一定要表示为 $2\times 3^k$（也就是 $3^k+3^k$，与题目矛盾，所以好数一定是只含有 $0$ 和 $1$ 的。

那么，我们直接写一个判断三进制每一位的数值的函数就可以了，记得使用记忆化，小心超时。（虽然我也不知道会不会超时）

---

# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int num[100005];
bool change(int x){
	while(x){
		if(num[x]==1)return true;
		if(num[x]==-1)return false;
		int k=x%3;
		if(k==2){
			num[x]=-1;
			return false;
		}
		x/=3;
	}
	return num[x]=true;
}
int main(){
	int q,n;
	scanf("%d",&q);
	while(q--){
		scanf("%d",&n);
		for(int i=n;;i++){
			num[i]=change(i);
			if(change(i)){
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}

```


---

## 作者：minVan (赞：1)

**题目大意**

给定 $n$，求不小于 $n$ 的最小数 $x$，使得 $x$ 可以分解成不同的 $3$ 的幂之和。其中 $C2$ 的数据规模更大。

**解题思路**

递归、暴力。我们只需要算出 $3^0\ 3^1\ 3^2 ...$ 的前缀和 $sum_i$，然后从大到小判断是否要选 $3^i$ 作为 $x$ 的一部分，如果 已选数字之和 $ans + sum_{i-1} \le x$ 那么说明当前 $3^i$ 不用选。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF = 1e18;
long long n, ans, sum[105], a[105];
long long solve(long long x) {
	long long ans = 0;
	for(int i = 38; i >= 1; i--) {
		if(ans + sum[i - 1] >= x) {
			continue;
		} else {
			ans += a[i];
		}
	}
	if(ans < x) {
		ans += 1;
	}
	return ans;
}
int main()
{
	sum[0] = 1;
	a[0] = 1;
	long long cnt = 3;
	for(int i = 1; i <= 100 && sum[i - 1] <= INF; i++) {
		sum[i] = sum[i - 1] + cnt;
		a[i] = cnt;
		cnt *= 3;
	}
	int t;
	cin >> t;
	while(t--) {
		cin >> n;
		cout << solve(n) << "\n";
	}
	return 0;
}
```

---

## 作者：锦瑟，华年 (赞：1)

好吧，我来讲一下这题的精髓：二进制的三进制。

这是什么意思呢？意思就是，一个字符串，只能用01串，也就是二进制来表示，但转化为十进制的时候要用三进制的方法来转换。

相信你们越听越糊了，我就这么说吧，对于一个三进制数，每一位上只能为1或0，表示这位上取或不取，最后，用三进制的方法化为十进制，这个数就是我们要找的数。比如：

$(101)③=(10)⑩=3^2+3^0$


开头把这类数全都算出来，然后一个一个遍历查找输出即可。

上代码：

	#include<stdio.h>
	using namespace std;
	int a[15],b[100005];
	int main(){
		int n,i,now=1,now1=0;
		while(now<=9){
			a[1]++;//二进制的三进制
			for(i=1;a[i]>1;i++){//进位
				if(i==now)now++;
				a[i]=0;
				a[i+1]++;
			}
			int ans=0,s=1;
			for(i=1;i<=now;i++){//转十进制
				ans+=a[i]*s;
				s*=3;
			}
			b[++now1]=ans;//储存
		}
		scanf("%d",&n);
		while(n--){
			int k;
			scanf("%d",&k);//输入
			for(i=1;i<=now1;i++){//一个一个遍历查找输出，也可以用二分，不过这样也能过（主要是我懒）
				if(b[i-1]<k&&b[i]>=k){
					printf("%d\n",b[i]);break;
				}
			}
		} 
		return 0;
	}
    
好了,byebye~~~。

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

（最优解第一页）

通过样例可知，首先所有 $3^{n}$ 都是好数，同时所有 $3n+2$ 都不是好数（因为它一定有两个相同的次幂）。

那么剩下的情况为 $3n $ 和 $3n+1$ 类。

我们如何判定 $3n $ 类的数呢？因为不能有相同的次幂，所以如果它一直减去小于它的好数，看最后的差，就可以判定它为 $3n+1$ 类，$3n+2$ 类或是好数。

接下来是 $3n+1$ 类。因为 $1$ 为 $3^{0}$，所以它相当于 $3n+3^{0}$，也就是$3n $ 类。

看起来似乎陷入了死循环，但是，如果接下来除以三后的结果为 $1$ ，那么它就和前面的重复了，变成了 $3n+2$ 类。

即：$3n+1$ 类的数，只能取一次 $1$，其后必须为 $3^{n}+3^{n-k1}+3^{n-k2}+\cdots\cdots$，不能再有一个 $3n+1$ 或 $3n+2$ 的数。

如 $13$，他是 $3n+1$ 类的数，取一次 $1$ 后变成 $12$，为 $3n $ 类，减去小于它的 $3^{n}$（此处为 $9$），变为 $3$。$3$ 是好数，$3+9=12$ 是好数，$1+3+9=13$ 也是好数。

从中可以发现规律：所有好数一定能由$3^{n}+3^{n-k1}+3^{n-k2}+\cdots\cdots$ 组成

也就是说，最后的好数为 $3^{n}$ 及其子集的总和。

代码实现：

先造出所有的好数，然后一个个读入，查找就可以了。

因为它只能为 $3n $ 和 $3n+1$ 类，同时数据范围给我们要小于等于 $19683$（即 $3^{10}$）,所以我们只需要把每一个 $9$ 位的$\verb!01!$串用三进制计算为十进制的值，最后加上 $19683$ 特判就可以了。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int s[11]={0,1,3,9,27,81,243,729,2187,2187*3};
int r[1000]={};
int t[11];
int sjz(){
	int b=0;
	for(int i=1;i<10;i++){
		if(t[i]==1)b+=s[i];//本来r是存3的n次方的数组
	}
	return b;
}
int main(){
	//造数部分
    for(int i=1;i<512;i++){
    	int u=i;
		for(int j=1;j<10;j++){
			if(u%2==0){
				u=u/2;
				t[j]=0;
			}else{
				u=u/2;
			t[j]=1;
		}
	}
		r[i]=sjz();//计算长度为9的01串
	}
	r[512]=19683;//特判
   //查找部分
	int a;
	cin>>a;
	while(a--){
		int b;
		cin>>b;
		for(int i=0;;i++){
			if(r[i]>=b){
				cout<<r[i]<<endl;
				break;
			}
		}
	}
	return 0;
}

```


---

## 作者：cxy000 (赞：0)

首先发表一下自己的观点：

这样的题都是一类题，只要掌握了方法就可以做。

所以让我们看看：

实际上这是一道类似拆分的题，所以我们在初始化 $po$ 数组的情况下从大到小枚举是否小于当前所剩余的数，若满足，则给它减去。

又因为题目要求不能重复，所以一个循环枚举就可以。

记得这些事不要在输入后再做，应该在输入前就做好初始化之后再更新答案即可。

注意：答案要用一个变量存储答案更新入口。

所以这道题没有什么难度了。

上代码：

```c
#include <bits/stdc++.h>
using namespace std;
int ans[100100];
int po[11];//保险起见
int main(){
	int t;
	cin>>t;
	int k=1;
	po[0]=1;
	for(int i=1;i<=10;i++){
		po[i]=po[i-1]*3;
	}
	for(int i=1;i<=100000;i++){//同上
		int k1=i;
		for(int j=10;j>=0;j--){
			if(k1>=po[j]){
				k1-=po[j];
			}
		}
		if(k1==0){
			for(int j=k;j<=i;j++) ans[j]=i;
			k=i+1;
		}
	}
	int n;
	while(t--){
		cin>>n;
		cout<<ans[n]<<endl;
	}
	return 0;
}
```


---

## 作者：Helium_Ship (赞：0)

## 解题思路：

题目中说了**好数是指可以变成 $3$ 的不同次幂相加的和的数**，
也就是说只有有或无两种状态。

我们可以利用[这道题](https://www.luogu.com.cn/problem/P2347)的思路，模拟二进制下的状态来求出每一个好数，存入数组里，询问时再查找出一个大于或等于 $n$ 且最小的 $m$，输出即可。

## code：
```
#include<iostream>
#include<cstdio>
using namespace std;
int q,n,l;
int d[2010],t[11];
int z[11]={1,3,9,27,81,243,729,2187,6561,19683};//3的不同次幂算出来存入数组 
int main()
{
	cin>>q;
	t[1]=1;
	l=1;
	while (l<=1024)//算出前1024个好数 
	{
		for (int i=1;i<=10;i++)//求这个好数的值 
			d[l]+=t[i]*z[i-1];
		//模拟二进制的过程 
		l++;
		t[1]++;
		int k=1;
		while (t[k]>1)
		{
			t[k+1]+=t[k]/2;
			t[k]%=2;
			k++;
		}
	}
	for (int i=1;i<=q;i++)
	{
		cin>>n;
		for (int j=1;j<=1024;j++)//找第一个大于n的数，也可以使用二分优化 
			if (d[j]>=n) 
			{
				cout<<d[j]<<"\n";
				break;
			}
	}
	return 0;
 } 
```
 


---

## 作者：big_news (赞：0)

考虑 $ n\leqslant10^4 $ 的情况。我们现在要在数列 $[3^0,3^1,3^2,...,3^k](3^k>n)$ 中选出一些数，使得它们的和 $⩾n$ ，并使得这个和最小。
考虑 $k$ 的范围，此时 $k\leqslant \log_310^4≈14$ ，所以只需要 $2^k$ 枚举每个数字选不选就好了。总复杂度 $O(q·2^k)$ ，实际上已经解决了这一题。


考虑怎么跑得更快。实际上上述枚举过程可以通过枚举二进制状态来实现，即用一个数字二进制位上的 $0/1$ 来表示数列某一项选不选。

假设我们当前二进制枚举的状态码为 $S$ ，那么实际上该状态码所对应的数值是单调的；换句话说，随着 $S$ 变大，其表示的那个数字也变大。

简单的 proof ，~~请理性偷税~~。
考虑把二进制数 $0100$ 变成 $0101$ （前者表示 $3^2$ ，后者表示 $3^2+3^0$） ，即在原来状态码的基础上加一位使其变大，此时其表示的数字一定变大，因为又多了新的一项。考虑把二进制数 $0100$ 变成 $1000$ （前者表示 $3^2$ ，后者表示 $3^3$），即右移原来状态码的某一位使其变大，此时其表示的数字也一定变大，因为有一项的次数$+1$。

那么也就是说现在枚举的数值具有单调性，那么为什么不二分呢？只需要二分查找出一个 $⩾n$ 的最小位置就好了，总复杂度 $O(qk)$，其中 $k$ 为常数，它大概是 $\log_2 2^{40}=40$。

代码:

Easy Version
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
int read(){
    int s=0,ne=1; char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') ne=-1;
    for(;c>='0'&&c<='9';c=getchar()) s=(s<<1)+(s<<3)+c-'0';
    return s*ne; 
}
int q,n;
int Pow3(int x){
    int rec = 1,base = 3;
    while(x) {if(x & 1) rec *= base; base *= base; x >>= 1;}
    return rec;
}
int gen(int u){
    int g = 0;
    for(int i=0;i<14;i++) if(u & (1<<i)) g += Pow3(i);
    return g;
}
int main()
{
    q = read();
    while(q--){
        int n = read();
        for(int S = 0; S < (1<<14); S++)
            if(gen(S) >= n) {printf("%d\n",gen(S));break;}
    }
    return 0;
}
```

Hard Version
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

#define LL long long

LL read(){
    LL s=0,ne=1; char c=getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') ne=-1;
    for(;c>='0'&&c<='9';c=getchar()) s=(s<<1)+(s<<3)+c-'0';
    return s*ne; 
}

int q; LL n;

LL Pow3(int a){
    LL rec = 1,base = 3; 
    while(a) {if(a & 1) rec *= base; base *= base,a >>= 1;}
    return rec;
}
LL gen(LL u){
    LL g = 0;
    for(int i=0;i<40;i++) if(u & (1ll << i)) g += Pow3(i);
    return g;
}

int main()
{
    q = read();
    while(q--){
        n = read();
        LL l = 0,r = (1ll << 40);
        while(l < r){
            LL m = (l + r) >> 1;
            if(gen(m) >= n) r = m;
            else l = m + 1;
        }
        printf("%lld\n",gen((l + r) >> 1));
    }
    return 0;
}
```

---

