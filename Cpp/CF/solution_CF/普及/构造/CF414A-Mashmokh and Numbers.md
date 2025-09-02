# Mashmokh and Numbers

## 题目描述

It's holiday. Mashmokh and his boss, Bimokh, are playing a game invented by Mashmokh.

In this game Mashmokh writes sequence of $ n $ distinct integers on the board. Then Bimokh makes several (possibly zero) moves. On the first move he removes the first and the second integer from from the board, on the second move he removes the first and the second integer of the remaining sequence from the board, and so on. Bimokh stops when the board contains less than two numbers. When Bimokh removes numbers $ x $ and $ y $ from the board, he gets $ gcd(x,y) $ points. At the beginning of the game Bimokh has zero points.

Mashmokh wants to win in the game. For this reason he wants his boss to get exactly $ k $ points in total. But the guy doesn't know how choose the initial sequence in the right way.

Please, help him. Find $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ such that his boss will score exactly $ k $ points. Also Mashmokh can't memorize too huge numbers. Therefore each of these integers must be at most $ 10^{9} $ .

## 说明/提示

 $ gcd(x,y) $ is greatest common divisor of $ x $ and $ y $ .

## 样例 #1

### 输入

```
5 2
```

### 输出

```
1 2 3 4 5
```

## 样例 #2

### 输入

```
5 3```

### 输出

```
2 4 3 7 1```

## 样例 #3

### 输入

```
7 2
```

### 输出

```
-1
```

# 题解

## 作者：RE_Prince (赞：1)

# CF414A Mashmokh and Numbers

[link](https://www.luogu.com.cn/problem/CF414A)

## Sol

$\gcd$ 数论题。

有一种很显然的思路，两个数的最大公约数只能是正数，因此我们可以将后面几对数的 $\gcd$ 都赋为 $1$，然后前两个数的 $\gcd$ 为 $1+k-\frac{n}{2}$。这样怎么说得分一定是 $n$。特判下 $\frac{n}{2}>k$ 和 $n=1$ 的情况就好了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,i,j,k;
signed main()
{
	cin>>n>>m;
	if(n/2>m||n<=1&&m) return puts("-1"),0;//无解，这里特别坑
	if(n==1) return puts("1919810"),0;//n=1,m=0
	int first=1+m-n/2,st=1;//gcd(first,first*2)=first
	cout<<first<<" "<<first*2<<" ";
	for(i=2;i<=n/2;i++)
	{
		while(st==first||st+1==first||st==first*2||st+1==first*2) st++;
		cout<<st<<" "<<st+1<<" "; //输出一对互质的数
		st+=2;
	}
	if(n&1) cout<<"114514";//最后一个数没用
    return 0;
}
```

---

## 作者：流绪 (赞：1)

n 个数，每次从最前面取两个数并求这两个数的 gcd，直到只剩小于2个数，让你构造一个数列，使这个数列能在上述操作中让 gcd 的和等于 k。

我们可以像样例一样，先让每个位置放上它本身，这时候每个 gcd 都等于1，因为每次取的两个数都是相邻的数。

每次取两个的话，一共会取 n/2 组，k 如果小于n/2那肯定构造不出来了，因为上述那样 gcd=n/2 已经是最小值了。k=n/2 就刚好了，直接输出，就像样例一。k>n/2，那么需要的值就多了 k-n/2，那么我们把第一第二项的 gcd 改成 k-n/2 就好啦，其他的还是 1，但是因为不能有相同的数，我们还需要一些小操作。

gcd=k-n/2，那我们直接让第一项等于 k-n/2，第二项是它的倍数就好啦，剩下的从第二项 +1 开始，每次 +1，最后注意这样只会输出偶数个数，如果 n 是奇数，还要在最后补输出一个 1，因为我们这样构造，只要第一项可能为 1，但是第一项为 1 的是 k=n/2 的情况，所以这里其他位置不可能出现 1。

最后有一个很坑的地方！n<2时,一定有gcd=0,这时候 k=0 才合法,否则直接输出 -1。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	int n,k;
	cin >> n >> k;
	int p=n/2;//取p组数
	if(p>k||(n<2&&k))
	{
		cout << -1;
		return 0;
	}//特判
	if(p==k)
		for(int i=1;i<=n;i++)
			cout << i << " ";//k=n/2
	else
	{	int a = k-p+1;
		cout << a << " " << a*2<<" ";
		for(int i=1;i<=2*(p-1);i++)
			cout << a*2+i << " ";从第二项+1开始输出(组数-1)*2个数
		if(n%2)
			cout << 1;//补 1
	}
	return 0; 
}  
```


---

## 作者：skyskyCCC (赞：0)

## 前言。
显然题目让我们构造一个序列，根据题意进行模拟，分类讨论即可。
## 分析。
我们把题意这么理解：构造一个序列，使得该序列要从第一个数字开始，往后每两个一组取最大公约数，直到剩下的数字数量小于 $2$ 为止。

首先我们考虑无解情况。首先如果我们能构造出的序列的最大公约数都是 $1$ 但是仍然比 $k$ 要大，显然我们不可能再变小了，所以无解。另外就是没有一个序列能给 $k$ 提供一个公约数，这些也不能构造。

然后就是构造答案了：我们可以设除了第一个数对以外的最大公约数都为 $1$ 这样我们就有了第一个数对取的公约数。显然我们只要再加上后面的数对的全部的 $1$ 让总和等于 $k$ 即可

有一个定理：最大公约数为 $1$ 则这两个数字互质，并且连续的正整数之间都是互质的。

关于上面的定理的第二个，我可以给出证明：考虑反证。我们不妨假设 $x$ 与 $x+1$ 不互质，它们则之间存在比 $1$ 大的公约数，我们令这个公约数为 $m$。则可以得到 $x=m\times b$ 同时 $x+1=m\times\left(b+\frac{1}{m}\right)=m\times b+1$ 则显然 $b+\frac{1}{k}$ 需要为整数。则此时 $k$ 只能为 $1$ 但这和我们的条件假定冲突，所以得证。其中 $b$ 为一个常数。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
using namespace std;
int n,k;
int sum,tot,cut;
bool flag=false;
int main(){
    cin>>n>>k;
    sum=n/2;
    if(n%2){
    	flag=true;
	}
    if(sum>k||sum==0&&k!=0){
        cout<<"-1\n";
        return 0;
    }
    else if(k==0&&sum==0){
    	cout<<"1 ";
        return 0;
    }
    else{
    	tot=k-sum+1;
    	cout<<tot<<" "<<tot*2<<" ";
        for(int i=200001;i<sum+200000;i++){
            while((i+cut)==tot||2*(i+cut)+1==tot||(i+cut)==2*tot){
            	cut++;
			}
			cout<<i+cut<<" "<<2*(i+cut)+1<<" ";
        }
        if(flag){
        	(tot!=1)?cout<<"1\n":cout<<"3\n";
		}
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：enyyyyyyy (赞：0)

- 思路：
	数论、构造

- 题意：
	给定两个数 $n$，$k$，构造 $a_1,a_2,a_3,a_4 \dots a_{n-1},a_n$ 使 所有满足 $i\le n$ 并且 $i=1$ 的 $\gcd(a_i,a_i+1)$ 和为 $k$。
    
- 实现：
	一顿数论下来，得出如果 $k< \frac{n}{2} ⋁ k	⋀  n=1 $，那么无解，输出 `-1`。判完以后，剩下的都是有解的，又推了一点公式，发现首项是 $(k-\frac{n}{2}+1)\times 2$,项数为 $n$,公差为 $1$。
    
- 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
inline vd print(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x >= 10)
		print(x / 10);
	putchar(x % 10 + '0');
	return;
}
ll n,k,a;
int main() {
	n=read(),k=read();
	if(k<n/2||k&&n==1){print(-1);return 0;}
	a=k-n/2+1,a*=2,n--;
	print(a/2),printf(" ");
	while(n--) print(a++),printf(" ");
	return 0;
}
```

    

---

## 作者：yingkeqian9217 (赞：0)

## 前言

这题看起来复杂，其实很简单的qwq，真不知道楼上~~脑子怎么长的~~为什么编那么长。

## 题目大意
给定两个数 $n$，$k$，要你构造一个长度为 $n$ 的序列，使它满足 $\displaystyle\displaystyle\sum_{k=1}^{2k\le n}{\gcd(a_{2k},a_{2k+1})}=k$。

## 分析
观察条件，可以发现 $\displaystyle\sum_{k=1}^{2k\le n}{\gcd(a_{2k},a_{2k+1})}$（以下简称 $f(n)$）与且仅与数对 $(a_1,a_2)$，$(a_3,a_4)$，……$(a_{2\lfloor\frac n2\rfloor-1},a_{2\lfloor\frac n2\rfloor})$ 有关，所以当 $n$ 为奇数时，最后一位在不重复的情况下可以取任意值。

而这时候其实就是要将 $k$ 表示成 $\lfloor\frac n2\rfloor$ 个非0自然数（因为 $\gcd(x,y)\ge1$）的和，所以，显然当 $k\lt\lfloor\frac n2\rfloor$，是无解的。此时问题就简单了，~~随便拆就好了~~只要首项为 $k-\lfloor\frac n2\rfloor+1$，后面都取1，就可以简简单单的收获AC了。

最终数列因为是取 $\gcd$ 的，所以可以直接翻倍。

为了保证不重复，我们可以直接从前一位+1算起，保持最终序列的单调递增。

这题还有一些特殊情况，比如 $n=1$ 的时候，要特判一下。
## AC_CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=12900001;
int n,k;
signed main(){
	scanf("%d%d",&n,&k);
	if(n==1&&k==0){//特殊情况，n=1,k恒等于0,可以任取
		printf("29");
		return 0;
	}
	if(n<2||k<n/2){//无解
		printf("-1\n");
		return 0;
	}
	printf("%d %d ",k-n/2+1,(k-n/2+1)*2);//首两位
	for(int i=2;i<=n/2;i++) printf("%d %d ",(k-n/2+1)*2+2*i-1,(k-n/2+1)*2+2*i);//相邻数，最大公因数必为1
	if(n%2) printf("%d\n",3*k+3*n+29);//注意这一位虽然可以任取，但不能重复哦
	return 0;
}
```
祝你 $\color{green}\textsf{\textbf{Accepted}}$！

---

## 作者：xiezihanAKIOI (赞：0)

题外话：隔壁大佬的题解好像有点问题，就是他输出的 `a * 2 + i` 是有可能大于题目限制 $10^9$ 的。（讲错勿喷。）

回到题目，这道题很明显，就是一道模拟。我们先从有解和无解入手。那么什么情况无解呢？

1.很明显，不管 $k$ 有多大，只需用两个数字便可填满。所以要使他无解，要使 $k$ 尽量小，就算 $n$ 个数两两互质，也会超过 $k$。

2.我们刚刚考虑了 $k$ 很小的状况，那么当 $n$ 很小，连两个数都没有，但是 $k$ 不为 0 的情况，也是无解的。

由此得出无解判断语句：`if ((n >> 1) > k  || (n < 2 && k)) cout << -1, exit (0);`

那么我们来判断有解的情况。有解依然有两种情况。

1.当 $n/2$ 刚好为 $k$ 时，这个时候，只要所有的数都互质，即可凑出 $k$，所以我们只用从 1 输到 $n$。

2.这种情况有些麻烦。我们可以先求出 $n/2$ 比 $k$ 大了多少，先将多出来的输出，后面的数只要同 1 一样，互质即可。但是要注意，输出的数不能重复。所以要用个 while 去搜索。

详情见注释。

```
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, k;

signed main() {
	ios::sync_with_stdio (false), cin.tie (0), cout.tie (0);
	cin >> n >> k;
	if ((n >> 1) > k  || (n < 2 && k)) cout << -1, exit (0); //特判无解的情况。 
	int cnt = k - (n >> 1); //求出 k 比 n/2 大了多少。 
	if (cnt == 0) { //如果相等，直接输出 1~n 即可。 
		for (int i = 1 ; i <= n ; i++) cout << i << ' ';
	} else {
		cnt++; //算出 n 比 k/2 大了多少，因为当时算的是 k - (n << 1)，所以当时算的时候这个数本为为 1，所以这位数要输出的是 n >> 1 比 k 多的数 +1。 
		cout << cnt << ' ' << (cnt << 1) << ' '; //x 和 (x * 2) 的最大公因数依然为 x。 
		int sum = (n >> 1) - 1, i = 1; //算出还要输出多少位数，这里减一是因为前面 cnt 输出过了一次。 
		while (sum) {
			if (i != cnt && i + 1 != (cnt << 1) && i != (cnt << 1) && i + 1 != cnt) { //如果这些数没有重复。 
				cout << i << ' ' << i + 1 << ' ';
				sum--;
			}
			i += 2;
		}
		if (n & 1) { //如果 n 为奇数，因为前面的 (n >> 1) 是向下取整的，可能会少取一位。 
			while (i + 1 == (cnt << 1) || i + 1 == cnt) i++;
			cout << i + 1; 
		}
	}
	return 0;
}	
```

---

