# Bear and Poker

## 题目描述

Limak is an old brown bear. He often plays poker with his friends. Today they went to a casino. There are $ n $ players (including Limak himself) and right now all of them have bids on the table. $ i $ -th of them has bid with size $ a_{i} $ dollars.

Each player can double his bid any number of times and triple his bid any number of times. The casino has a great jackpot for making all bids equal. Is it possible that Limak and his friends will win a jackpot?

## 说明/提示

In the first sample test first and third players should double their bids twice, second player should double his bid once and fourth player should both double and triple his bid.

It can be shown that in the second sample test there is no way to make all bids equal.

## 样例 #1

### 输入

```
4
75 150 75 50
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3
100 150 250
```

### 输出

```
No
```

# 题解

## 作者：Rbu_nas (赞：2)

题意：

有 $n$ 个数 $a_i$，你可以把每个数任意次 $\times2$ 或 $\times3$，问能否最终使得每个数相等。

一道不算难想的数学模拟题，对于给出的数列 $a_1,\ a_2,\ a_3\ ... \ a_n$，我们将结果视为是由数列 $b_1×k_1\ ,\ b_2×k_2\ ,\ b_3×k_3\ \ ... \ \ b_n×k_n$ 得到的，如果能通过 $\times2$ 或 $\times3$ 使 $a[]$ 数组相等，那么 $b[]$ 数组一定能通过除法使 $b_1,\ b_2,\ b_3\ ... \ b_n$ 相等。

由于 $b[]$ 中的元素的系数不同，把它视为 $2$ 与 $3$ 的倍数，若是最后 $b_1,\ b_2,\ b_3\ ... \ b_n$ 不同，那么它们通过 $\times k$ 即$\times2n$ $\times3n$ ($n>=0$) 也不能相等，这个道理并不难懂，那么代码也十分简单了。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define gcc getchar
template <typename T> inline void read(T&x)
{
    x=0; bool f=true; char ck=gcc();
    for( ; ck<'0'||ck>'9'; ck=gcc()) if(ck == '-') f=false;
    for( ; ck>='0'&&ck<='9'; ck=gcc()) x=(x<<1)+(x<<3)+(ck^48);
    x=f?x:-x; return ;
}

#define N 100003
int n, a[N];

int main(void)
{
    read(n);
    for(int i=1; i<=n; ++i) read(a[i]);
    for(int i=1; i<=n; ++i)
    {
        while(!(a[i] % 2)) a[i]/=2;
        while(!(a[i] % 3)) a[i]/=3;
        //通过不断除法使每个ai都化为无系数bi
    }
    for(int i=1; i<n; ++i)
        if(a[i] != a[i+1])
        {
            puts("No");
            //显然，如果有一个bi不等就不行
            return 0;
        }
    puts("Yes");
    return 0;
}

```

---

## 作者：Zhou_Wingay (赞：2)

### 思路：我们想，因为我们可以无限的乘2和3，所以我们可以忽略每个数中所有的因数2和3，之后再去看是否全部相等即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int zh(int x){//去除因数2和3
	while(x%2==0){x/=2;}
	while(x%3==0){x/=3;}
	return x;
}
int main(){
	int i,j;
	cin>>n;
	for(i=0;i<n;i++){
		cin>>a[i];
		a[i]=zh(a[i]);
	}
	for(i=0;i<n;i++){
		if(a[i]!=a[0]){cout<<"No";return 0;}
	}
   //判断是否全部相等
	cout<<"Yes";
	return 0;
}
```


---

## 作者：frankchenfu (赞：0)

我们的目标是每个数经过任意次$\times 2$或$\times 3$之后相等，所以我们可以把每个数除以他们的公因数，然后判断这个数是不是只由$2$和$3$的因子组成。如果是，那么他们一定可以在经过有限次的$\times 2$或$\times 3$后变得相等。代码：
```
#include<cstdio>
#include<cstring>
const int MAXN=100010;
int a[MAXN];

int gcd(int x,int y)
{
	return !y?x:gcd(y,x%y);
}

bool check(int x)
{
	while(~x&1)
		x>>=1;
	while(x%3==0)
		x/=3;
	return x==1;
}

int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int _gcd=gcd(a[1],a[2]);
	for(int i=3;i<=n;i++)
		_gcd=gcd(_gcd,a[i]);
	for(int i=1;i<=n;i++)
	{
		a[i]/=_gcd;
		if(!check(a[i]))
		{
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}
```

---

