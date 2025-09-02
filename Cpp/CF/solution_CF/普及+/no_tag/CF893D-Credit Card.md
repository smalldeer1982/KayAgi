# Credit Card

## 题目描述

Recenlty Luba got a credit card and started to use it. Let's consider $ n $ consecutive days Luba uses the card.

She starts with $ 0 $ money on her account.

In the evening of $ i $ -th day a transaction $ a_{i} $ occurs. If $ a_{i}&gt;0 $ , then $ a_{i} $ bourles are deposited to Luba's account. If $ a_{i}&lt;0 $ , then $ a_{i} $ bourles are withdrawn. And if $ a_{i}=0 $ , then the amount of money on Luba's account is checked.

In the morning of any of $ n $ days Luba can go to the bank and deposit any positive integer amount of burles to her account. But there is a limitation: the amount of money on the account can never exceed $ d $ .

It can happen that the amount of money goes greater than $ d $ by some transaction in the evening. In this case answer will be «-1».

Luba must not exceed this limit, and also she wants that every day her account is checked (the days when $ a_{i}=0 $ ) the amount of money on her account is non-negative. It takes a lot of time to go to the bank, so Luba wants to know the minimum number of days she needs to deposit some money to her account (if it is possible to meet all the requirements). Help her!

## 样例 #1

### 输入

```
5 10
-1 5 0 -5 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 4
-10 0 20
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 10
-5 0 10 -11 0
```

### 输出

```
2
```

# 题解

## 作者：流绪 (赞：3)

首先我们会发现,如果要避免冻结,那么我们充钱不能充太多,不然 a[i] 加上去之后容易超过 d ,但是要最少次充钱,那肯定每一次充的钱越多越好,怎么平衡这两个问题呢

我们可以同时进行两条路,一条是尽量少充钱,判断会不会超,另一条就是尽量充多,求最少充钱次数,我们用 sum1表示尽量少充钱时的余额,用 sum2 表示尽量多充钱时的余额

对于银行的操作,可以总结为两种:

⑴修改余额,只是符号不一样而已,然后如果此时 sum1 还是大于 d 了,那就不可能不冻结了,因为我们对 sum1 的修改已经是尽量让他小了!sum2 超过 d 了怎么办,没关系啊!我们原本策略是尽量充钱,也就是充满,那么现在超了,我们就相当于原来少充了 a[i] 。直接让 sum2=d。

⑵查询余额,查完了干嘛?充钱阿,不然钱负了就冻结了!因为对 sum1 尽量不充钱,对 sum2 充的次数尽量少,那么我们对 sum1 和 sum2 都是在今晚余额就要小于 0 被冻结了再去充钱,sum1 尽量充得少,那就刚好充到 0 就好了,sum2 当然是充满啦!

主要就像上面这样写了,贪心模拟

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010];
int main()
{
	ios::sync_with_stdio(false);
	int n,d;
	cin >> n >> d;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	int sum1,sum2,cnt;
	sum1=sum2=cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(!a[i])
		{
			if(sum1 <0)
				sum1 = 0;//不存钱变负数,那么存到剩0 
			if(sum2 <0)
				sum2 = d,cnt++;//存满钱 
		}
		else
		{
			sum1 += a[i];
			sum2 += a[i];//余额的更改 
			if(sum1 >d)
			{
				cout << -1;
				return 0; 
			}
			if(sum2 > d)
				sum2 = d;
		}
	}
	cout << cnt;
} 
```


---

## 作者：蒟酱 (赞：2)

简要题意：你有一张信用卡，$n$ 天有 $n$ 个操作，每次操作给定一个 $x$，如果 $x$ 是 $0$ 那么银行会查询信用卡里的金额，要保证金额是非负数；否则你卡里的金额会变化 $x$。每天操作前你可以在卡里存入任意多的钱，你要输出的是最小存钱次数，若无解输出 $-1$。另外，无论何时你卡里的金额不得超过 $m$。

因为前后充钱对于之后的操作并没有影响，而对于信用卡的余额是有上下界要求的，所以可以在操作的时候记录 `s1` 和 `s2` 表示当前信用卡里钱的下界和上界。  
具体来说，每次金额变化的时候把 `s1` 和 `s2` 都加上 $x$，由于 `s1` 是下界，如果下界都比 $m$ 大那肯定无解，如果上界比 $m$ 大把上界改为 $m$。如果是银行查询，下界小于 $0$ 直接修改为 $0$，上界小于 $0$ 直接修改为 $m$。  
代码：
```cpp
//不向焦虑与抑郁投降，这个世界终会有我们存在的地方。
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=1e5+1;
int n,m,a[N],ans,s1,s2;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1,x;i<=n;i++)
		if(cin>>x,x){
			if((s1+=x)>m)return cout<<"-1",0;
			if((s2+=x)>m)s2=m;
		}else{
			if(s1<0)s1=0;
			if(s2<0)s2=m,ans++;
		}
	cout<<ans;
	return 0;
}
```

---

## 作者：Chenxuhang_play (赞：0)

## 题目链接

<https://www.luogu.com.cn/problem/CF893D>

## 题目大意

你在一个银行开了一张卡。每天早上你可以往里面充钱~~而且貌似不能取钱~~，晚上银行会对你的卡进行操作。记第 $i$ 天的操作为 $a_i$，那么

+ 当 $a_i > 0$ 时，银行良心发现，将会往你的卡里充 $a_i$ 元。~~但是好像我说过钱是取不出来的。~~

+ 当 $a_i < 0$ 时，银行没钱了，将会从你的卡里取走 $|a_i|$ 元。

+ 当 $a_i = 0$ 时，银行将会检查卡的余额（不进行充钱或取钱的操作），如果你卡里的钱超过 $d$ 元将会被银行拿去充公，然后你的卡就被冻结了。如果你卡里的钱少于 $0$ 元（余额为负数），银行同样将冻结你的卡。

总结一下：

+ 当 $a_i \not= 0$ 时，银行将会充进去 $a_i$ 元。

+ 当 $a_i = 0$ 时，银行会对你卡里的余额进行判断，如果满足条件你的卡将被冻结。

~~不是这个什么奇葩银行哦~~

你想要知道，最少去充多少次钱，可以使你在接下来的 $n$ 天里信用卡不被冻结。如果无解输出 `-1`。

## 思路

设余额为 $M$，显然只要 $0\le M\le d$ 即可。

哪怕在银行取出钱后你的钱是负数，你仍然回溯到当天早上把钱充进去。根据这个 bug，我们可以总结出，只要在 $M<0$ 时的当天早晨把钱充进去就行；如果某一天达到了 $M>d$，那么显然就是无解，因为你只能把钱往里面充而不能取出来，这种情况下直接输出`-1`即可。

## 代码

大概是这样，因为写题解的时候你谷日爆了，不知道是什么 bug 不能提交，我只是凭感觉写，不保证正确。

```
#include<bits/stdc++.h>
int main()
{
	int days,d,ai,sum=0,M=0;
	scanf("%d%d",&days,&d); 
	for(int i=0;i<days;i++)
	{
		scanf("%d",&ai);//这里没写错，只需要一个ai,不用开数组 
		if(ai)
		{
			M+=ai;
			if(M>d)
			{
				printf("-1");
				return 0; 
			}
		}
		else
		{
			if(M<=0) sum++;
		}
	}
	printf("%d",sum);
	return 0;
	
 } 
```

---

## 作者：floodfill (赞：0)

# CF893D Credit Card 题解
### 题目大意
一张信用卡初始余额为 $0$，每天早上可以去充任意数量的钱。晚上，银行会对信用卡进行一次操作，操作有三种操作。 
- 若 $a_i>0$，银行会给卡充入 $a_i$ 元。
- 若 $a_i<0$，银行从卡中扣除 $a_i$ 元。
- 若 $a_i=0$，银行会查询卡里的余额（即不进行充/扣钱操作）。

信用卡的余额若超过 $d$ 元或在 $a_i=0$ 的时刻小于 $0$ 元，信用卡就冻结了。问最少去充多少次钱，可以在接下来的 $n$ 天里信用卡不被冻结。若无解输出 `-1`。

### 大致思路
定义上界 $r$，下界 $l$。

充钱是不影响后续操作的，并且只要卡里余额 $M∈[l,r]$ 就不会被冻结。当修改余额时
$$l\gets l+a_i,r\gets r+a_i$$
若 $l>d$，显然无解，因为 $l$ 是下界。若 $r>d$，即令 $r\gets d$。

查询余额时，若 $l<0$，即令 $l\gets 0$；若 $r<0$ 就得充钱，$r\gets r+d$，记得要把答案 $+1$。

##### ~~不过这是什么奇葩银行啊喂~~

---

## 作者：Crazyouth (赞：0)

**分析**

我们发现，充值并不影响后续操作，并且若你整个卡里的数在某个范围 $[low,up]$ 内就一定合法，那么就可以通过判断 $low,up$ 来判断是否有解与答案个数。对于非查询操作，先把 $low,up$ 全部加上 $a_i$，再看 $low$ 有无超过 $d$。如果超过了，那么一定没有充值方法，因为那是下界。如果 $up$ 超过了 $d$，就 $up\leftarrow d$。对于查询操作，如果 $low$ 当前小于 $0$，$low\leftarrow 0$；如果 $up$ 小于 $0$,就需要一次充值，只要充的值在 $[up,up+d]$，那就对于当前状态是合法的，所以 $up\leftarrow up+d$。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n,d,up=0,low=0,ans=0;
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(x)
		{
			up+=x;
			low+=x;
			if(low>d)
			{
				cout<<-1;
				return 0;
			}
			if(up>d) up=d;
		}
		else
		{
			if(up<0) up=d,ans++;
			if(low<0) low=0;
		}
	}
	cout<<ans;
	return 0; 
}

---

## 作者：wangyishan (赞：0)

# CF893D Credit Card 题解

## 题意 [Link](https://www.luogu.com.cn/problem/CF893D)

一张信用卡初始金额为 $0$，每天可以充任意数量的钱。银行每天也会给你充钱(或扣钱) $a_i$ 元，但银行卡钱数不能超过 $d$。银行会在 $a_i=0$ 的时间抽查看看银行卡里的钱数是否非负。问你至少需要充多少次钱，才能让银行的检查顺利过关？无论如何都不能的话输出 `-1`。

## 题解

经典 Trick：维护一个存钱区间可以转化为维护区间的左右端点（上下界）。

在这里我们定义区间下界为 $s_1$，上界为 $s_2$，于是我们发现 $0\leq s_1\leq s_2\leq d$。

修改时把它们都加上 $a_i$，若下界 $s_1>d$ 则无解；若上界 $s_2>d$ 就令 $s_2=d$。

查询时若 $s_1<0$ 就令 $s_1=0$（修改下界充的越少越好）, 若 $s_2<0$（此时需要充钱）就令 $s_2=d$（冲的次数越少越好->充的钱越多越好） 且答案要加 $1$。

Code：
```cpp
#include<iostream>
using namespace std;
long long a[100010],d;
int n,s1=0,s2=0,ans=0;
int main(){
    cin>>n>>d;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]!=0){
            s1+=a[i],s2+=a[i];
            if(s1>d){cout<<-1;return 0;}
            if(s2>d)s2=d;
        }else{
            if(s1<0)s1=0;
            if(s2<0)s2=d,ans++;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Rosent (赞：0)

[Link](https://www.luogu.com.cn/problem/CF893D)

一道贪心水绿。

题意：给定 $m$ 的额度和 $n$ 个 $i$，若 $i<0$ ，则扣除 $i$ 大小的额度；若 $i>0$，增加 $i$ 大小的额度。你可以求一种增加额度的办法，使得：

1. $m$ 始终小于等于 $d$。

2. 给出的 $i$ 为 $0$ 时 $m \ge 0$。

3. 增加次数最少。

由题意，我们发现只需要在每次 $i=0$ 且 $m<0$ 时尝试增加额度。贪心的想，每次既然增加则必定增加到可增加的上限，所以我们可以维护一个前缀和数组 $s_{i}$ 表示前 $i$ 次操作后的额度 $m$，再维护一个后缀最大值 $max_{i}$ 表示后 $i$ 个元素的操作后额度的最大值，每次增加 $d-max_{i}$ 即可。若 $i+(d-maxx_{i}) \le 0$，则证明该情况无解。

代码：
```cpp
//awa
#include <bits/stdc++.h>
#define int long long
#define maxn 100010
using namespace std;
int a[maxn],maxx[maxn],s[maxn];
signed main()
{
	int n,d;
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[i]=a[i]+s[i-1];
	}
	for(int i=1;i<=n;i++)
	{
		if(s[i]>d)
		{
			cout<<-1;
			return 0;
		}
	}
	maxx[n]=s[n];
	for(int i=n-1;i>=1;i--)
	{
		maxx[i]=max(s[i],maxx[i+1]);
	}
	int tag=0,cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]==0&&s[i]+tag<0)
		{
			cnt++;
			tag+=d-(maxx[i]+tag);
			if(s[i]+tag<0)
			{
				cout<<-1;
				return 0;
			}
		}
//		cout<<"i:"<<i<<" a[i]:"<<a[i]<<" s[i]:"<<s[i]<<" max[i]:"<<maxx[i]<<" tag:"<<tag<<endl;
	}
	cout<<cnt<<endl;
	return 0;
}
```


---

