# Creep

## 题目描述

请你构造出一个有 $a$ 个 $0$ 和 $b$ 个 $1$ 的字符串，使它的 $0$ 和 $1$ 的个数相差最多的前缀，$0$ 和 $1$ 的个数相差最少。若有多种答案，输出任意一种。多组数据。

## 说明/提示

$1\leq t\leq 1000$

$1\leq a,b\leq 100$

Translate by [庄nnnn额](https://www.luogu.com.cn/user/521592)

## 样例 #1

### 输入

```
5
1 1
1 2
5 2
4 5
3 7```

### 输出

```
10
011
0011000
101010101
0001111111```

# 题解

## 作者：良心WA题人 (赞：2)

**谨以此题解纪念长时间停打 CF 后的第一场比赛**

### 思路

因为整个串为整个串的一个前缀，所以对于整个串的任意一个排列，都一定会有一个前缀的恐惧值为 $|a-b|$。所以我们可以尽量让这个恐惧值最大。因为对于 $a>b$ 和 $a<b$ 的情况处理方法相似，所以这里以第一种为例子。

那么现在开始构造。首先，为了让任意一个前缀的恐惧值都不大于 $a-b$，那么我们可以用 $b$ 个 01 串填在前面。填完后，最大恐惧值为 $1$，整个串的恐惧值为 $0$。现在，剩下的地方全部填 $0$ 就可以保证最大恐惧值为 $a-b$ 了。

但是，对于 $a=b$ 的时候，整个串的恐惧值为 $0$。可是对于长度为 $1$ 的前缀，恐惧值为 $1$，故这种情况最大恐惧值至少为 $1$。而上述方法构造的最大恐惧值刚好为 $1$，所以这种情况仍然可以用上述方法构造。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(a<b)
		{
			for(int i=1;i<=a;i++)
				printf("01");
			for(int i=a+1;i<=b;i++)
				printf("1");
		}
		else
		{
			for(int i=1;i<=b;i++)
				printf("01");
			for(int i=b+1;i<=a;i++)
				printf("0");
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：___cjy__ (赞：1)

# CF1694A Creep 题解

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf1694a)

[题目传送门](https://www.luogu.com.cn/problem/CF1694A)

### 题目大意：

给定一个二进制字符串中 $0$ 和 $1$ 的数量 $a$ 和 $b$，使得串中的前缀 $0$ 和 $1$ 的数量差值最小。

### 思路：

显然，我们只需要让 $0$ 和 $1$ 交错出现，这样就可以使串中的前 $2 \times \min(a,b)$ 个数量差值等于 $0$。

我们可以找到 $a$ 和 $b$ 当中的最大值，先输出这个最大值对应的字符，再输出另一个字符。这样循环 $\min(a,b)$ 次，即可保证串中的前 $2 \times \min(a,b)$ 个数量差值等于 $0$。最后，将剩下的 $|a-b|$ 个剩余元素依次输出即可。

### AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T,a,b;
	cin>>T;
	while(T--){
		cin>>a>>b;
		int f=0,p=1;
		if(a<=b) f=1,p=0;
		int Max=max(a,b),Min=min(a,b);
		for(int i=1;i<=Min;i++) cout<<f<<p;//输出前2*min(a,b)个字符 
		for(int i=1;i<=Max-Min;i++) cout<<f;//输出剩余字符 
		cout<<'\n';
	}
	return 0;
} 
```

---

## 作者：xmkevin (赞：0)

### 题目大意

请你构造出一个有 $a$ 个 $0$ 和 $b$ 个 $1$ 的字符串，使它的 $0$ 和 $1$ 的个数相差最多的前缀，$0$ 和 $1$ 的个数相差最少。

### 思路

首先，我们取 $t = \min(a,b)$, 然后连续输出  $t$ 个“01”串，然后再把剩下的输出。

### 代码

```cpp
#include<iostream>
using namespace std;

int main() {
	int t, a, b;
	cin >> t;
	for(int i = 1; i <= t; i++) {
		cin >> a >> b;
		int t = min(a, b);//在a和b中取min
		for(int j = 1; j <= t; j++) {
			cout<<"01";//输出01串
		} 
		int ja = a - t, ga = b - t;//计算剩余部分
		for(int j = 1; j <= ja; j++) {
			cout<<"0";
		}
		for(int j = 1; j <= ga; j++) {
			cout<<"1";
		}
		cout<<endl;
	}		

	return 0;//华丽结束
}
```

---

## 作者：guozhetao (赞：0)

## 题意
请你构造出一个有 $a$ 个 $0$ 和 $b$ 个 $1$ 的字符串，使它的 $0$ 和 $1$ 的个数相差最多的前缀，$0$ 和 $1$ 的个数相差最少。若有多种答案，输出任意一种。多组数据。

## 思路

先输出 $\min(a,b)$ 个连续的 $0$ 和 $1$，使前缀差最小，最后再输出剩余的数字。注意有多组数据。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a;
int main() {
	scanf("%d",&a);
	while(a--) {
		int b,c;
		scanf("%d%d",&b,&c);
		int d = min(b,c);
		for(int i = 1;i <= d;i++) {
			printf("01");
		}
		b -= d;
		c -= d;
		while(b--) {
			printf("0");
		}
		while(c--) {
			printf("1");
		}
		printf("\n");
	}
}

```

[CF提交记录](https://codeforces.com/problemset/submission/1694/169384173)

2022/8/26 感谢 [lisida0820](https://www.luogu.com.cn/user/629192) 及时指出错误，将 $\max(a,b)$ 改成 $\min(a,b)$

---

## 作者：ytcccf (赞：0)

## CF1694A Creep 题解

### 题意简述

要求构造一个有 $a$ 个 `0` 和 $b$ 个 `1` 的字符串，使其 `0` 和 `1` 的相差个数最大得前缀相差个数最少，多测。

### 题目分析

题目难度：普及-。

AC code 时间复杂度为 $\Theta(T(a+b))$。

### 解题思路 

首先答案显然不小于 $|a-b|$ ,那么在构造这个字符串得时候我们利用贪心的策略，使得每个前缀 `0` 和 `1` 的相差个数都尽可能小，压到 $|a-b|$ 这个最小值上，于是我们把 `0` 和 `1` 交叉着放到字符串中，先放个数多的（其实反过来也没事，毕竟 $a$ 和 $b$ 不会变化），如果最后还多，那就统统都放在字符串的最后，最后。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int t,a,b;
	cin>>t;//多测
	while(t--)
	{
		cin>>a>>b;
		if(a>b) //0比较多的情况 
		{
			for(int i=1;i<=b;i++)
			{
				cout<<0<<1;
			}
			for(int i=1;i<=a-b;i++)
			{
				cout<<0;
			}
		}
		else //1比较多的情况 
		{
			for(int i=1;i<=a;i++)
			{
				cout<<1<<0;
			}
			for(int i=1;i<=b-a;i++)
			{
				cout<<1;
			}
		}
		cout<<endl; //一开始忘了输出换行，死得很惨 
	}
	return 0;//完结撒花~ 
}

```

---

## 作者：lovely_hyzhuo (赞：0)

本题说要让 $0$ 和 $1$ 个数相差最多的字串相差最少（这种最大值最小或最小值最大都是贪心）。

为了好写，不妨令 $a<b$

考虑贪心，如果将前面 $2a$ 个变成 $a$ 个 $01$ 串，再将后面变成 $b-a$ 个全部输出成 $1$ 即可。

在 $a>b$ 时也差不多。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int a,b;
		cin>>a>>b;
		for(int i=1;i<=min(a,b);i++)
		{
			cout<<"01";
		}
		int e=max(a,b)-min(a,b);
		for(int i=1;i<=e;i++)
		{
			if(a<b)
			{
				cout<<"1";
			}
			else
			{
				cout<<"0";
			}
		}
		cout<<endl;
	}
	return 0;
}
```



---

## 作者：hanzhang666 (赞：0)

# 题目分析
考虑贪心。我们发现如果交叉输出 $0$ 和 $1$，该子串差值为 $0$。最后输出剩余的 $0$ 或 $1$，最小差值为 $|a-b|$。此题得解。             
单次询问总时间复杂度为 $\mathcal{O}(a+b)$。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
signed main(){
	int T=read();
	while(T--){
		int a=read(),b=read();
		for(int z=1;z<=min(a,b);z++){//交叉输出1,0 
			cout<<10;
		}
		int n=max(a,b)-min(a,b);
		for(int z=1;z<=n;z++){//输出剩余的0或1 
			if(a>b)	cout<<0;
			if(a<b) cout<<1;
		}
		puts("");
	}
}
```


---

## 作者：Star_Ring (赞：0)

### 思路

很容易让人想到一种贪心思路，如果在子串中是 $0$ 和 $1$ 交错，这样可以使得在这些子串中最大差值为 $1$。那么现在还剩下了 $|a-b|$ 个 $0$ 或者 $1$，显然，只要我们将子串截取为整个串，差值必然为 $|a-b|$。所以我们可以将剩下的 $0$ 或者 $1$ 分配在任意地方即可。

总时间复杂度为 $O(t\times(a+b))$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,a,b;
	// t、a、b 变量见题意。 
	cin>>t;
	while(t--){
		cin>>a>>b;
		for(int i=1;i<=min(a,b);i++){
			cout<<"01";
			// 先尽量组成 01 交错的子串，用完所有的 0 或者 1。 
		}
		for(int i=min(a,b)+1;i<=max(a,b);i++){
			cout<<(a<b?1:0);
			// 然后将剩下的 0 或 1 输出。 
		}
		cout<<endl;
	}
	return 0;
}
```

---

