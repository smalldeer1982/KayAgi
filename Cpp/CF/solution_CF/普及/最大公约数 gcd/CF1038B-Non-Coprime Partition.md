# Non-Coprime Partition

## 题目描述

### 题目大意：
给定一个整数$n$，要求把$1$到$n$分别放入两个序列$s1,s2$，使得$\gcd(sum(s1),sum(s2))>1$

## 样例 #1

### 输入

```
1
```

### 输出

```
No```

## 样例 #2

### 输入

```
3
```

### 输出

```
Yes
1 2
2 1 3 
```

# 题解

## 作者：0xFF (赞：5)

#### 题目大意


------------
给定一个整数$n$，要求把$1$到$n$分别放入两个序列$s1,s2$，使得$\gcd(sum(s1),sum(s2))>1$

#### 题目分析


------------
考虑进行构造

- 当 $n$ 是奇数时，构造 $s1 = n $ 因为 $s1 + s2 = \frac{n (n+1)}{2} $ 所以 $s2 = \frac{n (n+1)}{2} - n = \frac{n(n-1)}{2}$ 设 $n = 2k+1,( k ∈Z^* )$，显然，$s1$ 与 $s2$ 有相同约数。

- 当 $n$ 是偶数时，构造 $s1 = n+1$ 仿照上述证明，所以 $s2 = \frac{n(n+1)}{2} - (n+1)  = \frac{(n-2)(n+1)}{2}$，同样设 $n = 2k,( k ∈Z^* )$，显然此时 $s1$ 与 $s2$ 也有相同的约数。

```cpp
int main(){
	int n = read();
	if(n <= 2) printf("No");
	else{
		printf("Yes\n");
		if(n&1){
			cout<<"2 1 "<<n-1<<endl;
			cout<<n - 2<<" ";
			for(int i=2;i<=n;i++){
				if(i != n-1) cout<<i<<" ";
			}
		}
		else{
			cout<<"2 1 "<<n<<endl;
			cout<<n - 2<<" ";
			for(int i=2;i<=n-1;i++){
				cout<<i<<" ";
			}
		}
	}
	return 0;
}
```


---

## 作者：Max_s_xaM (赞：3)

# CF1038B Non-Coprime Partition
### 【题目大意】

将 $1-n$ 的正整数分为 $2$ 组，使得两组数的和不互质。


### 【分析】

考虑将 $n$ 单独分为一组，剩下 $n-1$ 个数为另一组，则第一组的和为 $n$，第二组的和为 $\dfrac{n*(n-1)}{2}$。

当 $n$ 为奇数时，两个数包含公因数 $n$。

当 $n$ 为偶数时，两个数包含公因数 $n/2$。

$n\le 2$ 的情况输出 `NO` 即可。


### 【代码】

```cpp
#include<cstdio>
int main()
{
	int n;
	scanf("%d",&n);
	if (n<=2) puts("No");
	else
	{
		printf("Yes\n1 %d\n%d ",n,n-1);
		for (register int i=1;i<n;++i) printf("%d ",i);
	}
    return 0;
}
```


---

## 作者：帅到报警 (赞：3)

### 【题意描述】
我们有 1 - n 这 n 个数，将他们分为 2 组，使得两组之和的最大公约数不为 1。如果有解，那么输出这组解。

### 【分析】
~~这种题目中带 GCD 的题基本上都不用 GCD...~~那么我们就换一个角度思考。**是否存在一个数使得这个数和剩下数的和的最大公约数不为 0**。

并且我们知道这 1 - n 个数的和为 （n + 1） * n / 2；
那么就将 n 分为奇偶数的情况。
	
    当 n 为偶数时：
    	n ^ 2 与 n 都为偶数，那么 n ^ 2 / 2 与
        n / 2 都为整数，而 n ^ 2 是 n 的倍数，
        所以将所有数分出一个 n / 2 即可。

    当 n 为奇数时：
    	 分离出 n 后，剩余总和为 （n - 1） * n / 2,
         又因为 （n - 1） / 2 为整数，所以剩余
         总和为 n 的倍数，所以分离出 n 即可。

### 【核心代码】
分奇偶讨论
```cpp
if(n & 1)
{
	printf("1 %d\n%d ", n, n - 1);
	for(int i = 1; i <= n - 1; i++)
		printf("%d ", i);
}
else
{
	printf("1 %d\n%d ", n / 2, n - 1);
	for(int i = 1; i <= n; i++)
		if(i != n / 2)  printf("%d ", i);
}
```
### 【正解】
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	if(n == 1 || n == 2)
		return printf("No"), 0;
	puts("Yes");
	if(n & 1)
	{
		printf("1 %d\n%d ", n, n - 1);
		for(int i = 1; i <= n - 1; i++)
			printf("%d ", i);
	}
	else
	{
		printf("1 %d\n%d ", n / 2, n - 1);
		for(int i = 1; i <= n; i++)
			if(i != n / 2)  printf("%d ", i);
	}

	return 0;
}
```

---

## 作者：ryf_loser (赞：2)

我们可以假设一下：如果有解，我们想尽量让解最大，显然最大为 $n$。

那么我们进行大胆假设：如果第一行输出 $n$，第二行输出 $1 \sim n-1$，
显而易见，和分别为 $n$ 和 $\frac{n\times (n-1)}{2}$。

那么分情况讨论一下：

当 $n$ 为偶数时，$\gcd(n,\frac{n\times (n-1)}{2})$ 是等于 $\frac{n}{2}$ 的。

而 $n$ 为奇数时 $\gcd(n,\frac{n\times (n-1)}{2})$ 是等于 
$n$ 的。

显而易见，除了 $n\leq 2$ 是，这是都有解的。

AC CODE

```cpp
#include<stdio.h>
int n;
int main(){
 	scanf ("%d",&n);
 	if (n<3){puts("No");return 0;}
 	puts ("Yes");
 	printf("1 %d\n%d ",n,n-1);
	for(int i=1;i<n;i++)printf("%d ", i);
 	return 0;
}
```


---

## 作者：Nemonade (赞：2)

题目大意是，将从 $1$ 到 $n$ 的自然数放入两个序列当中使得两个序列之和不互质。

由于我很蒻，所以打暴力。

主要的细节是，两个串都不可以为空。

复杂度 $O(2^{n})$，似乎过不了，但是居然通过了，这是怎么回事呢？

在[这位神犇](https://www.luogu.com.cn/user/121027)的提示下原来是因为我的搜索顺序的原因。

看了[这篇题解](https://www.luogu.com.cn/blog/Max-s-xaM/cf1038b-non-coprime-partition-ti-xie)我才发现原因。

对于每一个 $n\ge2$ 的数据，都有一组解，其中一个序列为 $1,2,3......n-1$ ，而我的代码的这一行：

```cpp
//把当前数加入x串 
	x[++ctx]=step;
	dfs(step+1);
	//回溯 
	x[ctx--]=0;
```
决定了深搜会先试图把一个序列填满，发现序列 $x$ 全满不符合要求后，把最后一个数(也就是 $n$)，放在了序列 $y$ 上，这刚好符合了上述的这种可行情况，于是较快得到了答案。

而当没有答案( $n\le2$ )时，由于搜索层数极低，所以也不会超时。

全部代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=45005;
//两个序列 
int n,x[N],y[N],ctx=0,cty=0;
void dfs(int step){
	if(step==n+1){
		//两个序列都必须不为空 
		if(ctx==0||cty==0) return;
		int sx=0,sy=0;
		//统计x、y的和 
		for(register int i=1;i<=ctx;++i) sx+=x[i];
		for(register int i=1;i<=cty;++i) sy+=y[i];
		//如果最小公因数不是1，那么一定不互质 
		if(__gcd(sx,sy)>1){
			//输出 
			puts("Yes");
			cout<<ctx<<" ";		
			for(register int i=1;i<=ctx;++i) cout<<x[i]<<" ";
			cout<<endl<<cty<<" ";
			for(register int i=1;i<=cty;++i) cout<<y[i]<<" ";
			//直接结束程序 
			exit(0);
		}
		return;
	}
	//把当前数加入x串 
	x[++ctx]=step;
	dfs(step+1);
	//回溯 
	x[ctx--]=0;
	//同理 
	y[++cty]=step;
	dfs(step+1);
	y[cty--]=0;
	return;
}
int main(){
	cin>>n;
	dfs(1);
	//如果跑了一遍下来没有找到合适的串，就一定不存在 
	cout<<"No";
	return 0;
	//QWQ
}  
```

---

## 作者：liruixiong0101 (赞：1)

## P1 题意：
给出 $n$，将 $1$ 到 $n$ 这 $n$ 个数分成两个集合，且两个集合的和**不互质**，如果有解输出 `Yes` 和这两个集合，否则输出 `No`。

## P2 思路：
我们知道 $1$ 到 $n$ 的求和公式为：

$$S=\frac{n(n+1)}{2}$$

仔细观察这个式子，我们会发现这个式子的分子部分有因式 $n$ 和 $n+1$，我们可以从 $n$ 入手，也就是将 $n$ 这一个数分为一个集合，此时两个集合的和分别为：

$$S_1=n$$
$$S_2=\frac{n(n-1)}{2}$$

- 若 $n$ 为奇数：$n-1$ 为偶数，那么我们可以将 $S_2$ 中的 $n$ 保留下来，即：$S_2=n\dfrac{n-1}{2}$。这种情况 $\gcd(S_1,S_2)=n$，但是若 $n=1$，那么 $S_2=0$，不合法。

- 若 $n$ 为偶数：$n-1$ 为奇数，不可以像上述方法一样推过来，但是我们可以画个图。
![](https://s1.ax1x.com/2023/08/21/pPGWAO0.png)
如果 $n=6$，那么我们可以将前 $n-1$ 个数凑对，最后是剩下的数一定是 $\dfrac{n}{2}$，对于这个性质，我们可以算出 $\gcd(S_1,S_2)=\dfrac{n}{2}$，若 $n=2$ 时，$\dfrac{n}{2}=1$，不合法。  
~~其实一开始 $n$ 为奇数时，也可以这样做，但是本人一开始没想到。~~

## P3 代码：
代码很简单，这里只放 AC 记录了。
<https://codeforces.com/problemset/submission/1038/219779087>

---

## 作者：liupan2010 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1038B)

$\text{upd on 2023/6/23 19:25}$：

这样可以做的原因是：当 $2\le n$ 时必定有解，所以并不会因为无解然后卡满。而证明方法在其他题解已经有了。这个方法只是取巧，当个乐子看看就好。

$\text{Solution}$：

我们充分发扬人类智慧：

将数组随机打乱并随机将数组分成两段，查看是否符合要求。

再随机个 $10000$ 次再加个快读。

这样速度快的飞起，$n=10^6$ 也能在 $3$ 秒中之内跑完。

代码：

快读[在这里](https://www.luogu.com.cn/paste/5szj8hn6)。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,arr[45005];
auto seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
int rd(int l,int r){
	return uniform_int_distribution<int>(l,r)(rnd);
}
void solve(){
	shuffle(arr+1,arr+n+1,rnd);
	int pos=rd(1,n-1),sum=0;
	for(int i=1;i<=pos;i++){
		sum+=arr[i];
	}
	if(__gcd(sum,n*(n+1)/2-sum)<=1){
		return;
	}
	puts("Yes");
	write(pos),putchar(' ');
	for(int i=1;i<=pos;i++){
		write(arr[i]);
		putchar(' ');
	}
	puts("");
	write(n-pos),putchar(' ');
	for(int i=pos+1;i<=n;i++){
		write(arr[i]),putchar(' ');
	}
	exit(0);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		arr[i]=i;
	}
	int test=10000;
	if(n==1){
		puts("No");
		return 0;
	}
	while(test--){
		solve();
	}
	puts("No");
	return 0;
}
```

---

## 作者：qinshi0308 (赞：0)

首先吐槽一下（警示后人），这道题的翻译有问题，没说要在每一个分组前面输出数组长度，就说为啥没毛病还 WA。

## 一、思路
首先当 $n\le2$ 的时候一定是无解的。

先看 $n=1$ 的情况，不用说了，根本不能分成非空的两组。

在看 $n=2$，只能 $1$ 一组 $2$ 一组，二者最大公因数为 $1$，显然不符合题目要求。

那么再看 $n\gt2$ 的情况。

从样例入手：
$$\{1,2,3\}$$

可以把 $1$ 和 $3$ 分在一组，$2$ 分在另一组，此时，两组数的和的最大公因数为 $2$，符合题目要求。

继续，当 $n=5$ 时：

$$\{1,2,3,4,5\}$$

可以这样分：$\{1,2,4,5\}$，$\{3\}$，也可以满足题目要求。

我们可以发现当 $n$ 为奇数时，中间的数总为其余的数的和的因数。

继续看 $n$ 为偶数的情况，当 $n=4$ 时：

$$\{1,2,3,4\}$$

可以按以前的分法，并把多出来的数和中间数分为一组：$\{1,3\}$ 和 $\{2,4\}$。

验证一下。当 $n=6$ 时：

$$\{1,2,3,4,5,6\}$$

$\{1,2,4,5\}$ 和 $\{3,6\}$，也可以。

然后按照思路打一下代码就可以了。

## 二、代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	if(n<=2){
		cout<<"No";//n<=2时一定不可以（具体看思路） 
		return 0;
	}
	cout<<"Yes\n";//其他情况一定可以 （同上） 
	cout<<(n%2==0?n-2:n-1)<<" ";//第一行输出除中间项以外的数字，如果n为奇数，那么长度为n-1
	//如果n为偶数，那么长度为n-2（最后一个和中间项一组） 
	for(int i=1;i<(n+1)/2;i++){
		cout<<i<<" ";//输出中间项以前的数字 
	}
	for(int i=(n+1)/2+1;i<=(n%2==0?n-1:n);i++){
		cout<<i<<" ";//输出中间项以后的数字 （n为偶数时不输出最后一个） 
	}
	cout<<endl;
	cout<<(n%2==0?2:1)<<" ";//如果n为偶数，那么这一组有2个数，否则只有一个 
	cout<<(n+1)/2<<" "; 
	if(n%2==0){
		cout<<n<<" ";
	}
	return 0;
}
/*
备注： 
形如  表达式1?表达式2:表达式3  的式子是三目运算符，
意思是如果表达式1成立就返回表达式2 
否则返回表达式3
注意表达式2和表达式3的类型必须一致（比如都是int） 
*/ 
```

---

## 作者：xujunlang2011 (赞：0)

## 题意

给定一个 $n$ , 将 $1$ 到 $n$ 这 $n$ 个数分为两个集合， 并且使这两个集合的元素之和的最大公约数**不为** $1$。

## 思路

我们在小学时就知道了：

$$1+2+3+……+n=\dfrac{n(n+1)}{2}$$

所以我们可以从 $n$ 的奇偶性入手。

$\bullet$ 若 $n$ 为偶数， 则 $\dfrac{n(n+1)}{2}=\dfrac{n}{2}(n+1)$ 。 所以可以拆出 $\dfrac{n}{2}$ 给第一组， 此时两组的和包含最大公约数 $\dfrac{n}{2}$。

$\bullet$ 若 $n$ 为奇数， 则 $\dfrac{n(n+1)}{2}=\dfrac{(n+1)}{2}n$ 。 所以可以拆出 $\dfrac{(n+1)}{2}$ 给第一组， 此时两组的和包含最大公约数 $\dfrac{(n+1)}{2}$。

但是还有特殊情况， 当 $n\leq2$ 时， 显然无解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    if (n <= 2)
    {
        cout << "No\n";
        return 0;
    }
    if (n % 2 == 0)
    {
        cout << "Yes\n1 " << n / 2 << "\n" << n - 1 << " ";
        for (int i = 1;i <= n;i++)
        {
            if (i != n / 2)
            {
                cout << i << " ";
            }
        }
    }
    else
    {
        cout << "Yes\n1 " << (n + 1) / 2 << "\n" << n - 1 << " ";
        for (int i = 1;i <= n;i++)
        {
            if (i != (n + 1) / 2)
            {
                cout << i << " ";
            }
        }
    }
    return 0;
}
```


---

## 作者：flora715 (赞：0)

### 题意
将前n个正整数分成两个集合S1,S2。

要求gcd(sum(S1),sum(S2))>1。


### 分析
因为只用输出一组答案即可。

计算发现总和：
```cpp
sum=(1+n)*n/2;
```
是n或n/2的倍数。

所以，只需要特判n==1,n==2时输出no。

其他情况用奇偶数讨论即可输出。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<deque>
#include<cmath>
using namespace std;
typedef unsigned long long ll;

void reads(ll &x){ //读入优化（正负整数）
	int fx=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')fx=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	x*=fx; //正负号
}

int main(){
    ll n; reads(n); if(n==1||n==2){ puts("No"); return 0; }
    puts("Yes"); int sum=(1+n)*n/2; //总和
    if(n&1){ cout<<1<<" "<<n<<endl<<n-1<<" ";
        for(int i=1;i<=n-1;i++) cout<<i<<" ";
    } else{cout<<1<<" "<<n/2<<endl<<n-1<<" ";
        for(int i=1;i<=n;i++) if(i!=n/2) cout<<i<<" ";
    }
    return 0;
}
```

---

