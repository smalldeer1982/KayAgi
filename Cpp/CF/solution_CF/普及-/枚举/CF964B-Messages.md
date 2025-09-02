# Messages

## 题目描述

------------

Vasya有n封信。第i封信将在ti秒之后接收。 每封信都开始都值a元，但收到消息后，消息的成本每分钟减少B元(B可能变为负数)。Vasya可以在任意时刻接收到任何消息，也可在任意时刻读取它。读完消息后，Vasya的银行账户会收到该消息的当前成本。最初，Vasya的银行账户为0。 同时,每分钟Vasya的银行账户会收到C·k元,k是收到了但未读信的数量。 Vasya非常贪婪（又一个葛朗台），正因为如此，他想让所有的信息在T分钟后被阅读，使其利益最大化。


------------

## 样例 #1

### 输入

```
4 5 5 3 5
1 5 5 4
```

### 输出

```
20
```

## 样例 #2

### 输入

```
5 3 1 1 3
2 2 2 1 1
```

### 输出

```
15
```

## 样例 #3

### 输入

```
5 5 3 4 5
1 2 3 4 5
```

### 输出

```
35
```

# 题解

## 作者：GusyNight (赞：2)

```
题意：
给你一系列消息，
这些消息在第ti分钟收到，
如果立即读这条消息可以获得a的金钱，
不然每过一分钟获得金钱减少b（从a的基础上），
但每一分钟可以获得c* k的金钱，
k为没有读的消息的个数，
求最后获得最大值的金钱

分析：
假设每到一条消息我们都把他读了，
我们将直接获得基本ans=n*a;
通过题意我们发现如果对于每一道题每过一分钟多出（或减少）的收入为c*1-b，
所以如果c-b>0说明越往后读这条信息可以使得收入越多，
如果c-b<0说明越往后读这条信息使得收入越少，
如果等于0没有影响。
所以我们只需要判断一下，
如果c-b<0,
说明每条信息我们必须收到就读才能使收入最大，
如果c-b>0那么我们尽量都拖到最后才读，
也就是拖到T时间再读，
这样每个信息需要拖的时间总和sum  = （T-ti）求和，
最后总的收入就是a*n-sum*(c-b)

``` 
**AC代码:** 
```cpp
#include<bits/stdc++.h>
#define Max 10009
using namespace std;
int main(){
	int n,a,b,c,t,ans=0,sum=0,Message[Max];
	cin>>n>>a>>b>>c>>t;
	for(int i=1;i<=n;i++){
		cin>>Message[i];
		sum+=t-Message[i];
	}
	ans=n*a;
	if(b<c){
		ans=ans+sum*(c-b);
	}
	cout<<ans;
	exit(0);
}
```
**注：exit(0); = return 0;**

---

## 作者：ChenJr (赞：2)

	解释下题意：你有n封信，每封信最开始的价值为A，第i封信要在第ti秒后才能够接收，每当一封信被接收之后，他的价值每分钟就会减少B元。而每分钟Vasya可以获得的利润是C*k k为接收了但未读的信。求出Vasya可获得的最大利润。
    分析题意：因为要求获得的最大利润，故我们不妨采用贪心的策略。因为当接收到一份信后，这封信损失的和Vasya所获得的应该是一一对应的关系，即当Vasya获得了C*k元时，同时她也会损失掉B*k的钱。
    因此，考虑到最差的情况，即当获得的利润C小于B时，我们贪心的取最初的值，即总价值为n*A。
    而当可获得的利润C大于B的时候，我们可以枚举所有的信，贪心使每一封信保存时间最长，并乘上利润，并累加，即可获得最终的答案。
    
```cpp
#include <bits/stdc++.h>
#define maxn 1005
using namespace std;
int num[maxn];
int main()
{
	int n,a,b,c,t;//有n封信，初始值为a，每分钟减少的值为b，每分钟增加的值为c，总共的时间为t
	cin>>n>>a>>b>>c>>t;
	for(int i=0;i<n;i++){
        cin>>num[i];//输入时间
	}
	int res=0;
	res+=n*a;//最差的情况，即全都在接收信后立即得到价值
	if(b<c){//如果增加的利润大于减小的利润（即答案还能更优）
        for(int i=0;i<n;i++){
            res+=(t-num[i])*(c-b);//统计答案
        }
	}
	cout<<res<<endl;
    return 0;
}

```

---

## 作者：_VEGETABLE_OIer_xlc (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF964B)

题目大致意思：有 $n$ 封信，每封信价值 $A$ 元，第 $i$ 封信收到需要 $t_i$ 分钟，但当一封信收到却没被接收时，每分钟银行增加 $C$ 元，但信的价值减少 $B$ 元，如果要在 $T$ 分钟内接收完所有信，问最多得到多少元？

这道题需要用到分类讨论和贪心的思想。

每个样例就是一种情况。

### 样例三： $C > B$

发现接收信后每一分钟得到的钱为正数，根据贪心的思想，把所有信存到 $T$ 分钟后取得到的钱最多，于是第 $i$ 封信得到的钱为：

$sum = n \times a$ $+$ $(T$ $-$ $t_i)$ $\times$ $(C$ $-$ $B)$。

### 样例二： $C = B$

发现接收信后每一分钟得到的钱为 $0$，什么时候取也无所谓了。

为了计算方便，我们在收到时就取信，于是得到的总钱数为：

$sum = n \times a$。

### 样例一： $C < B$

发现接收信后每一分钟得到的钱为负数，所以须得速速收信，于是得到的总钱数为：

$sum = n \times a$。

分析完了，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,t,sum;
int d[1010];
int main(){
	cin>>n>>a>>b>>c>>t;
	for(int i=1;i<=n;i++)
		cin>>d[i];
	if(b<=c)//减的成本比加的C小
	{ 
		sum=n*a;
		for(int i=1;i<=n;i++)
			sum=sum+(t-d[i])*(c-b);
	} 
	else//减的成本比加的C多 
	{
		 sum=n*a;
	}
	cout<<sum;
	return 0;
} 
```

---

## 作者：Marshall001 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF964B)

## 题目大意

你一共有 $n$ 封信。第 $i$ 封信将在 $a_i$ 秒之后接
收。 每封信都开始都值 $A$ 元，但收到消息后，消息的成本每分钟减少 $B$ 元。你可以在任意时刻接收到任何消息，也可在任意时刻读取它。读完消息后，你会收到该消息的当前成本。同时,每分钟你会收到 $C\times k$ 元，$k$ 是收到了但未读信的数量。 现在，你想让所有的信息在 $T$ 分钟后被阅读，使其利益最大化。

## 思路一

一封信要么收到后立马读取，要么到第 $T$ 分钟后读取，这样才能得到最优解。

从题目中可以看出来，一封信如果收到后立马读取，就可以获得  $A$ 元，如果到第 $T$ 分钟时再读取，就会获得 $(t-a_i)\times(C-B)$。因为一封信如果不接收，在一分钟内会减去 $B$ 元，然后再加上 $C$ 元。

这样，代码就出来了。

## 思路二

众所周知，一个正数乘上一个负数，结果一定是负数；一个正数乘上一个正数，结果一定大于它本身。所以，如果 $C<B$，那么答案就一定是刚刚接收就读取，否则答案就是到第 $T$ 分钟时再接收。

## 代码

思路一代码：

```cpp
#include <iostream>
using namespace std;
const int MAXN=1e3+5;
int a[MAXN],n,A,B,C,T,ans1,ans2;
int main(){
	cin>>n>>A>>B>>C>>T;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans2+=(T-a[i])*(C-B)+A;
	}
	ans1=n*A;
	cout<<max(ans1,ans2);
	return 0;
}
```

思路二代码：

```cpp
#include <iostream>
using namespace std;
const int MAXN=1e3+5;
int a[MAXN],n,A,B,C,T,ans;
int main(){
	cin>>n>>A>>B>>C>>T;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	ans=n*A;
	if(B<C){
		for(int i=1;i<=n;i++){
			ans+=(T-a[i])*(C-B);
		}
	}
	cout<<ans;
	return 0;
}
```

## THE END

---

## 作者：lidundun (赞：0)

# Messages
依题意得，每封信的价值会随着时间减少，但是自动进账的金额会随着信的数量增加，这是我们只要按照 $b$ 和 $c$ 的大小做贪心就行了。

1. $b>c$  只要把信留着就会降低收益，所以每封信都要马上读掉，所以 $s=x\times n$。
2. $b<c$  只要早一点读都会降低收益，所以每封信都要留到最后再读，所以 $s=x\times n+(T-t_i)\times (c-b)$。

# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,z,t,s,a[100010];
int main()
{
	scanf("%d%d%d%d%d",&n,&x,&y,&z,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		s+=t-a[i];
	}
	if(y>z)  printf("%d",x*n);
	else  printf("%d",x*n+s*(z-y));
	return 0;
}
```


---

## 作者：KirBytronic (赞：0)

首先先吐槽一下这题的翻译，原题面上是第 $i$ 封信将在 $t_i$ 分钟后接收，翻译后却变成了将在 $t_i$ 秒后接受，希望能够更正一下。
## 思路
这道题考虑两种情况，如果 $b>c$，说明越拖收益越少，所以最大收益就是 $a \times n$。如果 $b<c$，说明越往后阅读收益越大，所以就让每封信都在尽量晚的时间阅读。拖得时间就是 $T-t_i$，第 $i$ 封信的最大收益为 $a + (c-b) \times (T-t_i)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int ti[1001];
int main(){
    int n,a,b,c,t,ans=0;
    cin>>n>>a>>b>>c>>t;
    for(int i=0;i<n;i++){
	cin>>ti[i];
	}
    ans+=a*n;//每封信的最低收益
    if(c>b){//如果c>b，说明收益可以更大
        for(int i=0;i<n;i++){
	    ans+=(t-ti[i])*(c-b);
            }
	} 
    cout<<ans;
} 
```


---

## 作者：Federico2903 (赞：0)

## 思路
我们有 $n$ 封信，如果我们每次收到就读，那收益就是 $n \times a$ 。  
我们再来思考拖时间读的情况。  
如果不读，每分钟收益减少 $b$ ，但同时也会增加 $c \times k$ 的钱。  
那每封信每分钟的价格变化应该是加上 $c - b$ 。  
我们总共到 $t$ 要拖的时间是所有 $t - t_i$ 的和。
如果 $c > b $ 那么是可以一直拖到 $t$ 的，就相当于每分钟这封信的价格以 $c - b$ 的速度增长，这样价值最大化至 $sum(t - t_i) \times (c - b) + n \times a$ 。  
否则应该收到就读，输出 $n \times a$ 。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,t,sum;
int m[1005];
int main(){
    cin >> n >> a >> b >> c >> t;
    for(int i=0;i<n;i++)cin >> m[i],sum+=t-m[i];
    int ans=n*a;
    if(b<c){
        ans+=sum*(c-b);
    }
    cout << ans;
}
```

---

## 作者：xiaojuruo (赞：0)

## 分析:
给你 $n$ 封信，如果立刻读的话，我们的利益就是 $n \times a$ 元钱。如果不读，我们的 $a$ 每分钟就减少 $b$ 元，也会增加 $c \times k$ 元钱， $k$ 为我们没有读的封数。 那我们就贪心呗， 如果 $c$ 的值大于 $b$ 那我们就最后读即可。
## AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int num[5000],n,a,b,c,t,ans=0;
int main()
{
	scanf("%d%d%d%d%d",&n,&a,&b,&c,&t);
	for(int i=1;i<=n;i++){
        cin>>num[i];
	}
	ans=n*a;//最差情况  
	if(b<c){
        for(int i=1;i<=n;i++) ans+=(t-num[i])*(c-b);//计算 
	}
	cout<<ans;
    return 0;
}
```


---

