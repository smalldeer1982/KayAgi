# Funny Permutation

## 题目描述

如果一个长度为 $n$ 的数列满足恰好包含 $1$ 到 $n$ 的整数各一个，则我们称之为排列。例如，$[3,1,4,2]$、$[1]$ 和 $[2,1]$ 都是排列，但是 $[1,2,1]$、$[0,1]$ 和 $[1,3,4]$ 都不是。

给你一个 $n$，你需要构造一个长度为 $n$ 的排列 $p$，使得它同时满足以下两个要求：

1. $\forall 1 \leq i \leq n$，都至少有一个邻居（$p_i$ 的邻居为 $p_{i + 1}$ 和 $p_{i - 1}$），使其值为 $p_i + 1$ 或 $p_i - 1$。

2. $\forall 1 \leq i \leq n$，都有 $p_i \ne i$。

我们称同时符合以上两个要求的排列为“有趣的排列”。

例如，当 $n = 4$ 时，$[4,3,1,2]$ 是一个“有趣的排列”，因为：

* $p_2 = p_1 - 1 = 4 - 1 = 3$；
* $p_1 = p_2 + 1 = 3 + 1 = 4$；
* $p_4 = p_3 + 1 = 1 + 1 = 2$；
* $p_3 = p_4 - 1 = 2 - 1 = 1$；
* $\forall 1 \leq i \leq n$，都有 $p_i \ne i$。

给定一个 $n$，你需要构造出一个长度为 $n$ 的“有趣的排列”，或者输出一个 $-1$ 来表明不存在长度为 $n$ 的“有趣的排列”。

## 样例 #1

### 输入

```
5
4
3
7
5
2```

### 输出

```
3 4 2 1
-1
6 7 4 5 3 2 1
5 4 1 2 3
2 1```

# 题解

## 作者：ImposterAnYu (赞：4)

# 解析
我们可以分两种情况来讨论。

## 1. $n$ 为偶数

 $n$ 为偶数时的构造方法很简单，直接倒序输出 $1$ 到 $n$ 即可。
 
 为什么这样可以呢？因为我们很容易发现，按这种方法构造排列时，$p_i = n - i + 1$，可得
 
 $$\forall 1 \leq i \leq n,p_i + i = n + 1$$
 
 而 $n$ 为偶数时，$n + 1$ 为奇数，所以不可能会出现 $p_i = i$ 的情况。
 
 而且
 
 $$\forall 2 \leq i \leq n,p_i = p_{i - 1} - 1$$
 
 $$\forall 1 \leq i < n,p_i = p_{i + 1} + 1$$
 
 所以，当 $n$ 为偶数时，倒序输出 $1$ 到 $n$ 是可以的。
 
 ## 2. $n$ 为奇数
 
 当 $n$ 为奇数时，我们刚才讲的构造方法就行不通了，因为按这种方法来构造排列时，$p_{\frac{n + 1}{2}} = \frac{n + 1}{2}$，所以我们要换种方法。
 
假设我们想到了一种构造方法：

$$4,5,6,...,n,1,2,3$$

我们如何证明它是“有趣的排列”呢？

其实很简单，我们很容易就可以看出：

$$\forall 1 \leq i \leq n - 4,p_i = i + 3 = p_{i + 1} - 1$$
$$\forall n - 2 \leq i \leq n,p_i = i - n + 3 = p_{i + 1} - 1$$
$$p_{n - 3} = n = p_{n - 4} + 1$$

所以，，当 $n$ 为奇数时，输出 $4,5,6,...,n,1,2,3$ 是可以的。

## 3. 特判
当 $n = 3$ 时，无论你如何构造，都不存在一个长度为 $n$ 的“有趣的排列”~~，不信的话你自己试试~~。所以，当 $n = 3$ 时，直接输出 $-1$ 即可。
# AC code
```c++
#include<bits/stdc++.h>
#define int1 int
#define p 11
using namespace std;
int1 t,n,i;
int1 read(){
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
	t = read();
	while(t--){
		n = read();
		if(n & 1){//如果 n 为奇数
			n -= 3;
			if(!n){//特判
				printf("-1\n");
			}else{
				for(i = 1; i <= n; i++){//先输出 4,5,6,...,n
					printf("%d ",i + 3);
				}
				printf("1 2 3\n");//最后再输出 1,2,3
			}
		}else{//如果 n 为偶数
			for(i = 1; i < n; i++){//直接倒序输出
				printf("%d ",n - i + 1);
			}
			printf("1\n");
		}
	}
	return 0;
}
```

---

## 作者：RoyWu1207 (赞：3)

~~啊，真简单！！~~

我们来看这道题。

题目说了半天，其实就两点。

- 某数两边必须有相邻的数；
- $p_i \neq i$。

于是，我们轻而易举地得到，$n = 1$ 或 $3$ 时无解！！！

接着，我们开动一下脑袋。

如果 $n$ 为偶数，直接倒序排列就好了。

奇数稍微麻烦些。

分两种。

- $n = 5$ 时，答案特殊处理，输出样例即可，具体见样例。
- 否则，在倒序数列中，将 $p_{\lceil \frac{n}{2} \rceil}$ 与 相邻位上的数互换即可。

由此便可以给出代码啦！！！

（~~投机取巧大法妙哉~~）

AC Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		if (n == 1 || n == 3)
			cout << -1 << endl;
		else if (n == 5)
			cout << "3 4 5 1 2" << endl;
		else if (n % 2 == 0) {
			for (int i = n; i >= 1; i--)
				cout << i << ' ';
			cout << endl;
		} else {
			for (int i = n; i >= n / 2 + 2; i--)
				cout << i << ' ';
			cout << n / 2 << ' ' << n / 2 + 1 << ' ';
			for (int i = n / 2 - 1; i >= 1; i--)
				cout << i << ' ';
			cout << endl;
		}
	} return 0;
}
```


---

## 作者：Dry_ice (赞：2)

已修改相关内容。

[更好的阅读体验](https://www.cnblogs.com/dry-ice/p/cf1741b.html)

题链：[cf](https://codeforces.com/contest/1741/problem/B) [lugou](https://www.luogu.com.cn/problem/CF1741B)

> 奇异构造。

## Description
构造一个 $1\sim n$ 的排列 $p$，使得 $\forall i\in\left[1, n\right]$ 满足存在邻居为 $a_i\pm 1$ 且 $a_i\not=i$。

## Analysis
构造题。分类讨论。此处的构造方式仅为个人观点，亦有其他构造可能。

1. $n$ 为偶数：直接降序输出 $n$ 到 $1$，易证满足条件。

1. $n$ 为奇数：此情况略复杂，因为直接倒序输出会导致 $a_\frac{n+1}{2}=\frac{n+1}{2}$。
考虑对序列前后**扭转**。下面再分两类：

	1. $\lfloor\frac{n}{2}\rfloor$ 为奇数，此处以 $7$ 为例，得 $7,6,4,5,3,2,1$，很容易发现在 $4,5$ 的位置发生了**局部扭转**。故得应在第 $\frac{n-1}{2}$ 和 $\frac{n+1}{2}$ 处进行扭转。
	1. $\lfloor\frac{n}{2}\rfloor$ 为奇数，此处以 $5$ 为例，得 $5,4,1,2,3$，很容易发现在 $4,1$ 的位置发生了**整体扭转**。故得应在后半部分即第 $\frac{n-1}{2}$ 到 $n$ 个数倒序。

注意：通过枚举不难发现 $n=3$ 时无解，记住特判。

## Code
```cpp
#include <stdio.h>
inline void Solve() {
	int n; scanf("%d", &n);
	if (n == 3) {puts("-1"); return;}
	if (n & 1) { //1
		if (n / 2 & 1) { //1-i
			for (int i = 1; i <= n / 2; ++i) printf("%d ", n - i + 1);
			printf("%d %d ", n - (n / 2 + 2) + 1, n - (n / 2 + 1) + 1);
			for (int i = n - (n / 2 + 2); i >= 1; --i) printf("%d ", i);
			putchar('\n');
		}
		else { //1-ii
			for (int i = 1; i <= n / 2; ++i) printf("%d ", n - i + 1);
			for (int i = 1; i < n - n / 2 + 1; ++i) printf("%d ", i);
			putchar('\n');
		}
	}
	else { //2
		for (int i = n; i >= 1; --i) printf("%d ", i);
		putchar('\n');
	}
}
int main(void) {
	int T; for (scanf("%d", &T); T--; ) Solve();
	return 0;
}
```

## The end. Thanks.

~~(路过一点~~

---

## 作者：Ferm_Tawn (赞：1)

给出一种新颖的方法。

首先，特判 $n=1 , n=3$ 的情况，不能满足要求。

接下来，有两种操作：

- 若 $n$ 为偶数，那么倒着输出即可，易证 $i \neq n - i + 1$。

- 若 $n$ 为奇数，先按上述操作来办，但是 $\lceil \frac{n}{2} \rceil = n - \lceil \frac{n}{2} \rceil + 1$，于是可以调换 $a[\lceil \frac{n}{2} \rceil] , a[\lceil \frac{n}{2} \rceil + 1]$。这样就满足要求了！

最后一个坑点：

- 当 $n = 5$ 时，按上述方法做，最后一位数不满足要求，故要把标准结果复制粘贴(~~???~~)。

核心代码：

```cpp
if(n == 1 || n == 3){
	cout << "-1\n";
	continue;
}
if(n == 5){
	cout << "3 4 5 1 2\n";
	continue;
}
for(int i = n ; i >= 1 ; i--) a[n - i + 1] = i;
if(n % 2 == 1) swap(a[(n + 1) / 2] , a[(n + 1) / 2 + 1]);
```


---

## 作者：zfx_VeXl6 (赞：1)

首先特判 $n=3$ 时不能构成符合题意的排列。

然后其他的情况依次先输出 $\frac{n}{2}+1$ 到 $n$，再输出 $1$ 到 $\frac{n}{2}$ 即可。可以证明构造的排列符合题意。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main() {
    cin>>t;
    while(t--) {
        cin>>n;
        if(n==3)
            cout<<-1<<'\n';
        else {
            for(int i=n/2+1;i<=n;i++)
                cout<<i<<' ';
            for(int i=1;i<=n/2;i++)
                cout<<i<<' ';
            cout<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：with_no_signal (赞：1)

# 题意简述

构造 $1\dots n$ 的序列 $a$，使其满足 $a_i\neq i$ 且 $|a_i-a_{i+1}|=1$  或 $|a_i-a_{i-1}|=1$。

## 思路

这是一道构造题，观察样例是否能得到一种构造方式呢？

能。

### 样例输入
```latex
5
4
3
7
5
2
```
### 样例输出
```latex
3 4 2 1
-1
6 7 4 5 3 2 1
5 4 1 2 3
2 1
```

观察一下，发现什么了没有？

先输出 $n$ 和 $n-1$ 然后按序输出 $1\dots n-2$ 也必定不为即可。

注意特例：$n=3$ 时无解。

下边进行证明：

当 $n=3$ 时，若满足 $2$ 不在 $a_2$ 上：当 $1$ 在 $a_2$ 上时， $3$ 的邻居为 $1$ 和其差不为 $1$。

对于 $n\neq 3$ 的情况：

在 $a_1,a_2$ 位置的 $n$ 和 $n-1$ 一定不为 $1,2$，且它们都有差为 $1$ 的邻居。

在 $a_3\dots a_n$ 位置的 $1\dots n-2$ 也必定不为 $a_3\dots a_n$，且它们都有邻居和本身差为 $1$。

代码实现较为简单。

赛时代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n==3)
		{
			cout<<"-1\n";
			continue;
		}
		else
		{
			cout<<n<<" "<<n-1<<" ";
			for(int i=1;i<n-1;i++)cout<<i<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：Larryyu (赞：1)

## _Description_
给定 $n$，求数列 $a$，使其满足：
- $|a|=n$
- $|a_i-a_{i-1}|=1$ 或 $|a_i-a_{i+1}|=1$
- $a_i\neq i$
- $\forall 0<i\le n$，$a$ 都包含 $i$
## _Solution_
分三种情况：
1. $2\mid n$

直接输出从 $n$ 到 $1$，可以保证任意相邻两数之差为 $1$，且偶数位放的时奇数，奇数位放的是偶数。

2. $n \equiv1\pmod{2}$

前 $n-3$ 位同上处理，后三位为 $1,2,3$ 即可（可以是其他三数，但不能是  $3,2,1$，因为 $n=5$ 时会出问题。


3. $n=3$

无解，输出 $-1$。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main(){
	t=read();
	while(t--){
		int n;
		n=read();
		if(n==2){
			printf("2 1\n");
			continue;
		}
		if(n==3){  //无解
			printf("-1\n");
			continue;
		}
		if(n%2==0){  //第一种情况
			for(int i=1;i<n;i+=2){
				printf("%d %d ",n-i/2*2,n-i/2*2-1);
			}
			printf("\n");
			continue;
		}
		for(int i=1;i<n-3;i+=2){  //第二种情况
			printf("%d %d ",n-i/2*2-1,n-i/2*2);  //这里有坑，需要注意奇偶
		}
		printf("1 2 3\n");
	}
	return 0;
}

```
#### _完结撒花！！_

---

## 作者：LeNotFound (赞：1)

### 题意简述  
输入一个整数 $n$，要求构造一个长度为 $n$ 的排列 $p$，$p_i \in [1,n]$，并同时满足以下两点要求:  

* 对于排列中的每一个元素，满足在和它相邻的元素中**至少有一个**元素和它的值相差 $1$。  
* 下标从 $1$ 开始，每个下标对应的元素不能和下标相等，形式化的，对于每一个 $i \in [1,n]$ 都必须满足 $p_i \neq i$。  

如果可以构造，输出构造的排列。  
如果不可以，输出 $-1$。  

### 题目分析  
构造题，首先考虑第一个要求，先想到的就是按顺序排列，但是为了满足各个下标对应元素不能和下标相等，再考虑顺序移动一位，后边的补到前边，但这样就会导致最前边的元素无法满足第一个要求，所以整体向后顺序移动两位，溢出的部分补到前边。  

要注意的是，顺序向后移动两位之后还要保证剩下的部分也满足第一个条件，因此这样的操作只适用于 $n \geq 4$ 的情况，那么对于 $n={1,2,3}$ 的情况我们可以特判一下。  

因此，下面代码中的 check 函数我只判断了是否满足第二个要求。  

形式化的，对于$n \geq 4$的情况，我们在要构造的排列中先放入 $n-1$ 和 $n$，然后依次放入 $1$ 到 $n-2$ 即可。  
### 代码  
```cpp
#include <bits/stdc++.h>

using namespace std;

inline long long read()
{
    long long x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

bool check(vector<ll> &v)
{
    for (ll i = 0; i < v.size(); i++)
    {
        if (v[i] == i + 1)
        {
            return false;
        }
    }
    return true;
}

void solution()
{
    ll n = 0;
    n = read();

    if (n == 1)
    {
        cout << -1 << endl;
        return;
    }
    if (n == 2)
    {
        cout << 2 << ' ' << 1 << endl;
        return;
    }
    if (n == 3)
    {
        cout << -1 << endl;
        return;
    }
    vector<ll> nums;
    nums.push_back(n - 1);
    nums.push_back(n);
    for (ll i = 1; i <= n - 2; ++i)
    {
        nums.push_back(i);
    }
    if (check(nums))
    {
        for (ll i = 0; i < nums.size(); i++)
        {
            cout << nums[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

int main()
{
    ll T = 0;
    T = read();
    for (ll i = 0; i < T; i++)
    {
        solution();
    }

    return 0;
}
```

---

## 作者：Symbolize (赞：1)

# 思路
首先我们可以发现，如果不管位置的限制，那直接顺序输出 $1$ 到 $n$ 即可。

那么加上限制后，我们只需要把 $1$ 至 $n$ 切成若干段，打乱顺序，让它们的值与下标不一样即可。

那怎么分，分成 $2$ 段肯定是最轻松的，那肯定是从中间分开，但如果两段都顺序输出，仁可能会重复，所以只要第一段倒序输出就一定不会出现问题了。
# Code
```
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
using namespace std;
int t,n;
void getans()
{
	cin>>n; 
	if(n==3) puts("-1");//特判
	else
	{
		int s=n+1;
		rep1(i,1,n>>1) cout<<--s<<' ';//第一段的倒序，从n开始递减
		rep1(i,1,s-1) cout<<i<<' ';//第二段的正序，从1开始递增
		puts("");//换行 
	}
	return;
}
signed main()
{
// 	freopen("B.in","r",stdin);
// 	freopen("B.out","w",stdout); 
	cin>>t;
	while(t--) getans();//循环要答案
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 分析
因为题目说可以输出任意一组解，所以我们要尽可能地简单一点。

根据题目，我们不难想到：$n$ 为偶数时，可以直接倒序输出；$n$ 为奇数，先输出后半段，再输出前半段即可。至于无解的情况，除了 $n≤3$ ，其他的均能够排成“有趣的排列”。

## CODE
```
#include<bits/stdc++.h>
  
using namespace std;
  
int t,n;
  
int main()
{
    cin>>t;
    while(t--) 
	{
        cin>>n;
        if(n<=3)
        {
			cout<<"-1\n";//特判
		}
		else
		{
			if(n%2==0)//偶数
			{
			    for(int i=n;i;i--) 
			    {
					cout<<i<<" ";// 倒序输出
			    }
			    cout<<endl;
			}
			else//奇数
			{
			    for(int i=n;i>=n-n/2+1;i--) 
			    {
					cout<<i<<" ";//输出后半段
			    }
			    
			    for(int i=1;i<=n/2+1;i++) 
			    {
					cout<<i<<" ";//输出前半段
			    }
			    cout<<endl;
			}
		}    
    }
    
    return 0;
}
```


---

## 作者：野生林登万 (赞：0)

[我的个人博客](http://autoac.vus.tax/index.php/2022/10/17/cf1741b/)
## 思路
题目要求任意一个数要和**最少**相邻一个数相差为 $ 1 $ ,我们可以很简单地想到构造两个序列:由 $ 1 $ 到 $ n $ 正序构造序列，和由 $ n $ 到 $ 1 $ 倒序构造序列，那么这两个序列一定符合题目中的第一个要求。正序的序列在每一个位置上都违反了第二个要求,所以我们放弃正序构造序列。

对于第二个倒序序列，由于它是倒序的，那么在大部分位置(除了最中间)，都有 $ i \not= n-i+1 $,其中他的下标为 $ i $ ,值为 $ n-i+1 $ 。因为:
- 当 $ n $ 为偶数的时候， $ 2 \times i + 1 = n $ 恒不成立，通过奇偶性可以得知。
- 当 $ n $ 为奇数的时候， $ 2 \times i + 1 = n $ 会在 $ i = (n - 1) \div 2 $ 时成立

于是，对于 $ n $ 为偶数时，我们直接输出倒序序列即可。对于 $ n $ 为奇数的时候，我们要避免在 $ i = (n - 1) \div 2 $ 的位置上填入 $ (n - 1) \div 2 $ ，于是我们将序列分为两半部分，在 $ i < (n - 1) \div 2 $ 时按照倒序的方法输出，在$ i \geq (n - 1) \div 2 $，将倒序的序列再次倒序输出，也就是说在 $ (n - 1) \div 2 $ 的位置上我们填入 $ 1 $，接下来依次填入$ 2,3,4,5 \dots $ ，因为$ i \geq (n - 1) \div 2 $ 的值已经在前面填入过了，所以一定不会出现 $ i = p_i $的情况。

但是， $ n = 3 $是一个特殊的情况，因为此时 $ i < (n - 1) \div 2 $ 的部分只有一个数，即 $ p_1 = 3$ ，他相邻的另外一个数 $ p_2 $ 只能为 $ 1 $，所以此时没有任何一种情况可以构造出一个“有趣的排列”，输出 $ -1 $。我们可以证明其他时候是不会出现构造不出来“有趣的排列”的，因为当 $ n $ 为偶数的时候可以直接输出逆序序列， $ n $ 为奇数时，除去 $ n = 3 $ 的情况， $ n \geq 5 $，那么 $ (n - 1) \div 2 \geq 2 $，前半部分至少有两个数是逆序输出的，符合第一条要求。于是输出 $ -1 $ 只需要特判 $ n $ 是否为 $ 3 $就可以了
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n == 3){
			cout<<-1<<endl;
			continue;
		}
		if(n % 2 == 0){
			for(int i = n;i >= 1;i--){
				cout<<i<<" ";
			}
			cout<<endl;
		}else{
			for(int i = n;i > (n-1)/2 + 1;i--){
				cout<<i<<" ";
			}
			for(int i = 1;i < n - (n-1)/2 + 1;i++){
				cout<<i<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：BlackPanda (赞：0)

**[problem](https://www.luogu.com.cn/problem/CF1741B)**

------------
### 题意：

有 $t$ 次询问，每次给出一个数 $n$，请你构造一个满足以下条件的序列:

- $\forall 1 \leq i \leq n$，都至少有一个邻居 （$p_{i}$ 的邻居为 $p_{i+1}$ 和 $p_{i-1})$，使其值为 $p_{i}+1$ 或 $p_{i}-1$。
- $\forall 1 \leq i \leq n$，都有 $p_{i} \neq i$。

------------
### 思路：

构造题，建议评橙或黄。

这道题可能有多组解，我们只需要找到其中一组即可。

首先，我们通过读样例可以发现，如果 $n$ 为 $3$，一定是无解的，并且如果 $n$ 为 $1$，也是无解的。

我们可以对 $n$ 进行分类讨论：

- 如果 $n$ 为偶数，可以直接倒序输出。

- 如果 $n$ 为奇数，我们可以把前半部分（$ \lceil\frac{n}{2}\rceil$）和后半部分（$\lfloor\frac{n}{2}\rfloor$）调换顺序输出。

------------
### code：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;

void solve()
{
    cin >> n;
    if (n == 1 || n == 3)
    {
        cout << "-1\n";
        return ;
    }   
    if (n % 2 == 0)
    {
        for (int i = 1; i <= n; i ++ )
            cout << n - i + 1 << " ";
    }
    else
    {
        for (int i = n; i > n / 2 + 1; i -- )
            cout << i  << ' ';
        for (int i = 1; i <= n / 2 + 1; i ++ )
            cout << i << ' ';
    }
    cout << endl;
}

int main()
{
    cin >> t;
    while (t -- )   solve();
    return 0;
}
```

---

## 作者：LeTu_Jun (赞：0)

题意很清晰，不再赘叙。

**在阅读此题解前请先思考下。**

## 思路

首先，很容易得到，本题分为三种情况：

- 当 $n$ 为偶数时：

  很简单，倒序输出序列即可。
  
- 当 $n$ 为奇数时：

  有点难度了，直接倒序输出不符合题意了：因为中间的数在倒叙输出时还在自己的位置上。 ~~一点也不有趣~~
  
  这时我的思路是把最后 2 个字符移到最前面，也就是类似于 $[n-1,n,1,2,3,4...]$ 的序列。
  
- 当 $n$ 为 $1$ 或 $3$ 时：

  特殊情况，无解。
  
----

_code_


```cpp
#include<bits/stdc++.h>
using namespace std; 
#define c continue;
#define pn putchar('\n');
#define debug printf("ans:");
int n;
int t;
int main ()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		if(n==1 || n==3)
		{
			//debug
			printf("-1");
			pn
			c
		}
		else if(n%2==0)
		{
			//debug
			for(int i=n;i;i--){
				printf("%d ",i);
			}
			pn
			c
		}
		else
		{
			//debug
			printf("%d %d ",n,n-1);
			for(int i=1;i<=n-2;i++){
				printf("%d ",i);
			}
			pn
			c
		}
	}
	return 0;
}
```


---

## 作者：aCssen (赞：0)

### Solution
首先考虑 $n$ 为偶数的情况，显然可以从 $n$ 到 $1$ 倒序输出，即 $p_i=n-i+1$。

但当 $n$ 为奇数时，$p_{\frac{n+1}{2}}=\frac{n+1}{2}$，为使 $p$ 继续满足性质，我们考虑将 $p_{\frac{n+1}{2}}$ 与 $p_{\frac{n-1}{2}}$ 交换，因为题目只要求有一个相邻的数与 $p_i$ 的差的绝对值为 $1$，所以只要 $n \ne 3$ 且 $n \ne 5$，左边的每个 $p_i$ 都有 $p_{i-1}=p_i+1$，右边的每个 $p_i$ 都有 $p_{i+1}=p_i-1$，答案合法。

明确了构造方案，判断无解就很简单了，只有当 $n=3$ 时，怎样构造都不合法，输出 $-1$。

那么，前面又为什么要求 $n \ne 5$ 呢？因为当 $n=5$ 时，原先的构造方案会导致交换后 $p_n$ 与 $p_{n-1}$ 的差不为 $1$，需要特判（~~样例真的很良心~~）。
### 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=2*1e5+5;
int num[maxn];
int main(){
	int t,n;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) num[i]=n-i+1;
		if(n&1) swap(num[n>>1],num[(n>>1)+1]);//位运算一定要加括号
		if(n==3) printf("-1");//无解
		else if(n==5) printf("5 4 1 2 3");
		else for(int i=1;i<=n;i++) printf("%d ",num[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：GI录像机 (赞：0)

## 思路：

既然题目要求说要保证 $p_i \neq i$，考虑把 $p$ 划成两半。前一半由前 $\lceil \frac{n}{2}\rceil$ 大的数组成，后一半由前 $\lfloor \frac{n}{2}\rfloor$ 小的数组成。然后将两半分别按升序排列，就满足了 $p_i=p_{i-1}$ 或 $p_{i+1}$。

注意 $n=1$ 或 $3$ 时判断无解。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int t = read();
signed main() {
	while (t--) {
		int n = read();
		if (n == 1 || n == 3) {
			puts("-1");
			continue;
		}
		for (int i = n / 2 + 1; i <= n; i++) {
			write(i);
			putchar(' ');
		}
		for (int i = 1; i <= n / 2; i++) {
			write(i);
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：YH_Eternally (赞：0)

## 题意
构造一个长度为 $n$ 的数列，满足
1. $\forall 1 \leq i \leq n$，都至少有一个邻居（$p_i$ 的邻居为 $p_{i + i}$ 和 $p_{i - 1}$），使其值为 $p_i + 1$ 或 $p_i - 1$。

2. $\forall 1 \leq i \leq n$，都有 $p_i \ne i$。

## 思路
由于解并不是唯一的，所以我们要找规律。

我们发现，只有 $n=3$ 的时候，我们不可能构造出符合题意的数组：

原因：
1. 当数列为 $[3,2,1]$ 或 $[1,3,2]$ 时，满足不了 $p_i\not=i$ 的条件。
2. 当数列为 $[2,3,1]$ 时，$p_3$ 没有一个等于 $2$ 的邻居。

当 $n=2$ 时，有一个唯一的数列 $[2,1]$。

当 $n\geq4$ 时，对于每个 $n$ 都有一个数列 $[3,4,5\cdots n,n-1,n-2\cdots 2,1]$ 是符合题意的，考虑到上述结论，可以实现代码如下。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, a[205], flag;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = 0;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return f ? x : -x;
}

int main() {
	t = read();
	while(t --) {
		n = read();
		if(n == 3) {
			printf("-1\n");
		}
		else {
			for(int i = 3; i <= n; i ++) printf("%d ", i);
			printf("2 1\n");
		}
	}
    return 0;
}
```

---

## 作者：smallpeter (赞：0)

一道非常简单的构造题。我们把 $n$ 分奇数和偶数考虑。

# 解题思路

## 若 $n$ 为偶数

不难发现当 $n$ 为偶数的时候我们可以直接构造 $n,n-1\dots 1$ ，证明如下。

在这种构造方法中第 $i$ 个数的值为 $n-i+1$。若存在某一项 $x$ 满足 $x=n-x+1$，则 $x=\frac{n+1}{2}$。显然 $x$ 不是整数，所以不存在某一项不符合要求。

## 若 $n$ 为奇数

比偶数难构造一点，我们构造 $n,n-1,1,2\dots n-2$，发现除了 $n=3$ 的情况其他大于 3 的奇数都满足，证明如下。

在这种构造方法中第 1 个数为 $n$，第 2 个数为 $n-1$，第 $k$ 个数 $(k\ge3)$ 为 $k-2$，根据题意列出以下方程。
$$\begin{cases}n\ne1\\n-1\ne2\\k\ne{k-2}\end{cases}$$

发现在题目给的 $n\ge2$ 的条件下只有 $n=3$ 这种方法构造不了。我们枚举发现~~样例不都告诉你 3 无法构造吗~~ $n=3$ 的时候无法构造，那么就弄完奇数的情况了。


综上所述，整题除了 $n=3$ 的情况，其他都能构造，构造方法如上文所述。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

LL t,n;

int main()
{
    scanf("%lld",&t);
    while(t--)
	{
        scanf("%lld",&n);
        if(n==3)
		{
            printf("-1\n");
            continue;
        }
        if(n%2==0) //实际上构造奇数的方法也能构造偶数的情况 
		{
        	for(LL i=n;i>=1;i--) printf("%lld ",i);
        	printf("\n");
        	continue;
		}
        printf("%lld %lld ",n,n-1);
        for(LL i=1;i<=n-2;i++) printf("%lld ",i);
        printf("\n");
    }
}
```


---

