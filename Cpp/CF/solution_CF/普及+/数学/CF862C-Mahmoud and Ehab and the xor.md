# Mahmoud and Ehab and the xor

## 题目描述

Mahmoud and Ehab are on the third stage of their adventures now. As you know, Dr. Evil likes sets. This time he won't show them any set from his large collection, but will ask them to create a new set to replenish his beautiful collection of sets.

Dr. Evil has his favorite evil integer $ x $ . He asks Mahmoud and Ehab to find a set of $ n $ distinct non-negative integers such the bitwise-xor sum of the integers in it is exactly $ x $ . Dr. Evil doesn't like big numbers, so any number in the set shouldn't be greater than $ 10^{6} $ .

## 说明/提示

You can read more about the bitwise-xor operation here: [https://en.wikipedia.org/wiki/Bitwise\_operation#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

For the first sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF862C/180bb5f2e74c80f6ed89e63195bfe3b6f1ffefbe.png).

For the second sample ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF862C/f06e00f5587f7a7d8f6a75ce9483c045f97c5f8a.png).

## 样例 #1

### 输入

```
5 5
```

### 输出

```
YES
1 2 4 5 7```

## 样例 #2

### 输入

```
3 6
```

### 输出

```
YES
1 2 5```

# 题解

## 作者：Error_Eric (赞：5)

### 前言

我被困在机房了。

### 正文

一道蛮不错的构造题，但是题意讲的不是很清晰。

题目大意：给定正整数 $n,x(1\le n,x\le10^5)$ 要求输出是否存在 $n$ 个互不相等的小于 $10^6$ 的正整数，满足它们的异或和等于 $n$ 。如果存在，输出这个解。

我们回顾一下异或的性质：

- $x \oplus y=y \oplus x$

- $x\oplus(y\oplus z)=(x\oplus y)\oplus z$

-  $x \oplus 0=x$

- $x \oplus y=z \leftrightarrow z \oplus y=x$

我们可以考虑这样的构造：

输出 $1$ 到 $n-2$ 之间的所有数 ,记它们的异或和为 $sum$ .

设接下来输出 $a,b$ 可以满足题意,列出方程 $sum\oplus a \oplus b=x$.

利用性质2，性质4 得出 $a\oplus b=sum\oplus x$.

令 $u=2^{18}$(这样，可以满足 $u\le10^6$).

$a\oplus b=sum\oplus x \oplus u\oplus u=u\oplus(sum\oplus x\oplus u)$

容易证明 $a,b>n-2$ .

所以 $a=u.b=(sum\oplus x\oplus u) $ 是一种合法的构造。

然后就 WA 了。

---

为什么呢？ 我们可以发现当 $sum=x$ 时 $a=b$ 非法。

那么我么修改一下，可以得出以下构造：

输出 $1$ 到 $n-3$ 之间的所有数 ,记它们的异或和为 $sum$ .

令 $u=2^{18}$(这样，可以满足 $u\le10^6$).

如果 $sum\not=x$ 情况退化为上面讨论过的情况。输出 $0,u,(sum\oplus x\oplus u)$ .

如果 $sum=x$ 输出 $u,0.5u,u\oplus(0.5u)$ .显然三个数的异或和为 $0$.

### Code
```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int n,x,sum=0,u=(1<<18);
int main(){
	scanf("%d%d",&n,&x);
	if(n==2 and x==0)return puts("NO"),0;
	puts("YES");
	switch(n){//显然要特判
		case 1:printf("%d\n",x);break;
		case 2:printf("%d 0\n",x);break;
		default:
			for(int i=1;i<=n-3;i++)printf("%d ",i),sum=sum xor i;
			if(x==sum)printf("%d %d %d\n",u,u<<1,u+(u<<1));
			else printf("%d %d %d\n",0,u,u xor x xor sum);
			break;
	}
	return 0;
}

```

---

## 作者：Luzhuoyuan (赞：4)

被降智了。

### 题意

给定 $n,x$，构造互不相等的 $n$ 个整数 $a_i$ 使得异或和为 $x$，或报告无解。解需要满足 $a_i\le 10^6$。

- $1\le n,x\le 10^5$。

### 思路

这是一个抽象做法。

考虑对于任意非负整数 $i$，有 $(4i)\oplus(4i+1)\oplus(4i+2)\oplus(4i+3)=0$。因此考虑先处理 $n\bmod 4$ 的部分，然后其他部分用 $i$ 填充。同时考虑 $1\oplus 2\oplus 3=0$，给出以下构造：

- $n\bmod 4=0$：构造 $2^{18},2\cdot 2^{18},3\cdot 2^{18},x$；
- $n\bmod 4=1$：构造 $x$；
- $n\bmod 4=2$：构造 $x+2^{18},2^{18}$；
- $n\bmod 4=3$：构造 $x+2^{18},x+2\cdot 2^{18},x+3\cdot 2^{18}$。

之后枚举 $i$ 并将没填过的加入答案即可。

有一个特例为 $x=0,n\bmod 4=2$，此时 $x+2^{18}=2^{18}$。当 $n=2$ 时显然无解，否则考虑三个一组构造六个：$1,2,3,4,8,12$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=1e6+5;
int n,x,fl[N];
inline void w(int x){fl[x]=true,cout<<x<<' ',n--;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>x;if(n==2&&x==0)cout<<"NO\n",exit(0);
	cout<<"YES\n";
	if(x==0&&(n&3)==2)w(1),w(2),w(3),w(4),w(8),w(12);
	else{
		if((n&3)==0)w(1<<18),w(2<<18),w(3<<18),w(x);
		if((n&3)==1)w(x);
		if((n&3)==2)w(x|(1<<18)),w(1<<18);
		if((n&3)==3)w(x|(1<<18)),w(x|(2<<18)),w(x|(3<<18));
	}
	for(int i=0;n;i+=4)
		if(!fl[i]&&!fl[i+1]&&!fl[i+2]&&!fl[i+3])
			n-=4,cout<<i<<' '<<i+1<<' '<<i+2<<' '<<i+3<<' ';
	cout<<'\n';
}
```

（逃

---

## 作者：wmrqwq (赞：1)

怎么题解区里都没有随机化的题解啊 /jy。

于是就有了这篇题解。

# 题目链接

[CF862C Mahmoud and Ehab and the xor](https://www.luogu.com.cn/problem/CF862C)

# 解题思路

思路非常简单。

首先容易发现在 $n = 1$ 时，直接构造一个 $x$ 这个数即可。

其次我们考虑 $n = 2$ 的情况，由于异或的基本性质，我们可以得出当 $x = 0$ 时是一定无解的，其余情况直接构造 $x$ 和 $0$ 这两个数字即可，容易发现这两个数字一定不相等。

之后，我们就可以进行随机化了。

我们考虑先构造两个数为 $x \oplus 1$ 和 $1$ 这两个数字，然后进行大力随机化，考虑随机 $n - 3$ 个不同与之前构造过的数字，然后最后一个数字根据所有数字异或和为 $x$ 的条件，直接将之前构造出来的所有数字求出异或和，然后将这个异或和设为 $sum$，那么最后一个数字即为 $sum \oplus x$，注意，如果这个数字与之前的数字重复了，那么我们充分发扬人类智慧，运用 CF 一份 TLE 的代码会跑 $6$ 遍的机制，直接让你当前的程序 TLE 即可。

那么这样，单次错误的概率远远比 $\frac{1}{10}$ 要小，一份代码跑 $6$ 遍，错误的概率比 $\frac{1}{10^6}$ 要小，因此通过这题是完全没有问题的。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
ll _t_;
ll n,m;
void _clear(){}
map<ll,ll>mp;
long long Ss=chrono::steady_clock::now().time_since_epoch().count();
mt19937_64 Apple(Ss);
long long rand_lr(ll l,ll r){
	return Apple()%(r-l+1)+l;
}
ll sum;
void solve()
{
	mp.clear();
	_clear();
	cin>>n>>m;
	if(n==1)
	{
		cfy;
		cout<<m<<endl;
		return ;
	}
	if(n==2)
	{
		if(m!=0)
		{
			cfy;
			cout<<(m^1)<<' '<<1<<endl;
		}
		else
			cfn;
		return ;
	}
	cfy;
	cout<<(m^1)<<' ';
	mp[m^1]=1;
	sum=(m^1);
	forl(i,1,n-2)
	{
		ll rd=rand_lr(1,4e5);
		while(mp[rd])
			rd=rand_lr(1,4e5);
		mp[rd]=1;
		cout<<rd<<' ';
		sum^=rd;	
	}
	if(mp[sum^m])
	{
		cout<<"Wrong Answer.\n";
		while(1);
	}
	cout<<(sum^m)<<endl;
}
int main()
{
	IOS;
	_t_=1;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：copper_ingot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF862C)

一道比较简单的构造题。

因为最后只要让异或和为 $x$ 就可以了，所以相对比较自由，前面的 $n - 3$ 个数可以用 $1$ 到 $n - 3$ 的整数构造，只要留最后 $3$ 个数进行操作。设前面 $n - 3$ 个数的异或和为 $ans$，现在的目标是构造 $3$ 个数使得它们的异或和为 $x \oplus ans$。

现在如果有两个数 $k$ 和 $j$，那么令这三个数分别为 $x \oplus k$，$k \oplus j$，$j \oplus ans$ 就可以了。

但是这三个数不能重复，而且 $x \oplus k$ 不能等于 $j \oplus ans$。所以可以取 $k = 2 ^ {17}$，$j = 2 ^ {18}$。因为 $x$ 和 $ans$ 都在 $10^5$ 内，所以这样能保证 $x \oplus k \neq j \oplus ans$。

记得要判 $n = 2$ 的情况，如果 $x = 0$ 输出无解，否则输出 $0$ 和 $x$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, x, ans = 0;
int main(){
	scanf("%d%d", &n, &x);
	if (n == 2 && !x){puts("NO"); return 0;}
	puts("YES");
	if (n == 1) printf("%d", x);
	else if (n == 2) printf("0 %d", x);
	else{
		for (int i = 1; i <= n - 3; i++){printf("%d ", i); ans ^= i;}
		int k = 131072, j = 262144;
		printf("%d %d %d", x ^ k, k ^ j, j ^ ans);
	}
	return 0;
}
```

---

## 作者：xiaoming_king (赞：0)

**人生苦短 我用Python**

简单的思维构造题！
注意异或和是一定不相等的

```python
n, x = map(int, input().split())
ans = []
xor = 0
 
if n == 1:
	print("YES")
	print(x)
	exit()
 
if n == 2 and x == 0:
	print("NO")
	exit()
 
for i in range(1,n+1):
	ans.append(i)
	xor ^= i
to_add = xor ^ x
 
if to_add != 0:
	if to_add == 3:
		if n >= 3:
			ans[2] = 0
	else:
		ans[0] ^= 262144
		ans[1] ^= 262144 ^ to_add
 
if len(ans) == n:
    print("YES")
    print(" ".join(str(i) for i in ans))
else:
	print("NO")
```



---

