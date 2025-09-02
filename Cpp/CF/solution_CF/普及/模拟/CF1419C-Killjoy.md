# Killjoy

## 题目描述

A new agent called Killjoy invented a virus COVID-2069 that infects accounts on Codeforces. Each account has a rating, described by an integer (it can possibly be negative or very large).

Killjoy's account is already infected and has a rating equal to $ x $ . Its rating is constant. There are $ n $ accounts except hers, numbered from $ 1 $ to $ n $ . The $ i $ -th account's initial rating is $ a_i $ . Any infected account (initially the only infected account is Killjoy's) instantly infects any uninfected account if their ratings are equal. This can happen at the beginning (before any rating changes) and after each contest. If an account is infected, it can not be healed.

Contests are regularly held on Codeforces. In each contest, any of these $ n $ accounts (including infected ones) can participate. Killjoy can't participate. After each contest ratings are changed this way: each participant's rating is changed by an integer, but the sum of all changes must be equal to zero. New ratings can be any integer.

Find out the minimal number of contests needed to infect all accounts. You can choose which accounts will participate in each contest and how the ratings will change.

It can be proven that all accounts can be infected in some finite number of contests.

## 说明/提示

In the first test case it's possible to make all ratings equal to $ 69 $ . First account's rating will increase by $ 1 $ , and second account's rating will decrease by $ 1 $ , so the sum of all changes will be equal to zero.

In the second test case all accounts will be instantly infected, because all ratings (including Killjoy's account's rating) are equal to $ 4 $ .

## 样例 #1

### 输入

```
3
2 69
68 70
6 4
4 4 4 4 4 4
9 38
-21 83 50 -59 -77 15 -71 -78 20```

### 输出

```
1
0
2```

# 题解

## 作者：pigstd (赞：4)

首先，所有人的总分和是不会变的，记为$sum$

很容易得到一种只要两次的方法：首先让$n-1$个人都感染，然后让剩下的$1$个人再感染

然而，在什么情况下，是只需要$1$次或者$0$次的呢？

$0$次的情况很简单：当且仅当所有人的分数都是$x$的时候就是0次

$1$次的话，有两个情况：

1.$sum = n\times x$

这样的话，所有人都变为$x$就可以了

2.有一个人一开始的分数就是$x$

这样的话她一开始就被感染了，那么的话只要让剩下的$n-1$个人感染，然后这个人不去管她就行了

[code](https://www.luogu.com.cn/paste/omutp7mn)

---

## 作者：ql12345 (赞：3)

### 题意：

有t组数据，每组一个n，一个x，然后n个数 n:[2,1000] 数：[-4000,4000]

每次可以进行一个操作：任意选择一些数，所有的数可以任意变化，但变化后的和必须和原来的和一样

一个数可以变成已经被“感染”的数来感染，一开始只有x是被感染的

求最少次数使得所有数都被感染

### Solution：

结论题

1. 所有数都是x，显然ans1=0

1. 所有数的平均数是x，且不符合上述情况，对所有数操作即可 ans2=1

1. 有一个数是x，且不符合上述情况，对所有数操作即可 ans3=1

1. 不符合上述情况，ans4=2，证明：

	第一次操作：让第1个数变为x，第二个数减去第一个数的增量
    
   转化为情况3，所以ans4=1+ans3=2

### Code:

```
int t,n,x;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		int h,f,sum; h=f=sum=0;
		for(int i=1,a;i<=n;++i){
			cin>>a;
			h|=(x==a),f|=(x!=a),sum+=a;
		}
		printf("%d\n",n*x==sum?f:2-h);
	}
}
```

---

## 作者：SSerxhs (赞：2)

$ans$ 只有三种可能 $0,1,2$

$ans=0$: 显然此时 $\forall 1\le i\le n,a_i=x$

$ans=1$: $\exists 1\le i\le n,a_i=x \land \exists1\le j\le n,a_j\ne x$，这时只要令被感染的 $i$ 参加比赛，使其他人 rating 都变为 $x$，$i$ 补一下差值就可以了

或者一次比赛内所有数都可以调成 $x$，即 $x\times n=\sum\limits_{i=1}^na_i$

以上两种情况正确性和最优性显然

$ans=2$: 其余情况

其余情况只需第一场比赛调一个人 rating 为 $x$ 再执行 $ans=1$ 的操作就可以了

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e3+2;
int a[N];
int n,c,fh,i,t,x,tot;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(t);
	while (t--)
	{
		read(n);read(x);tot=0;
		for (i=1;i<=n;i++) read(a[i]);
		for (i=1;i<=n;i++) if (a[i]!=x) break;
		if (i>n) {puts("0");continue;}
		for (i=1;i<=n;i++) if (a[i]==x) {puts("1");break;}
		if (i<=n) continue;
		for (i=1;i<=n;i++) tot+=a[i];
		if (x*n==tot) puts("1"); else puts("2");
	}
}
```

---

## 作者：幻影星坚强 (赞：2)

如果所有人都和Killjoy数字一样那么显然在开始之前就能感染（即为0）。

如果有部分人和Killjoy一样，那么我们可以把没有感染的人在第一次比赛中设置成与Killjoy相等，已感染的人随便设置权值，这样能在第一轮就全部感染（即为1）。

如果没有人和Killjoy一样，那么我们可以在第一轮比赛将n-1个人的权值设为与Killjoy一样，然后看看最后一个人是否能够能到达Killjoy的权值，能的话就是1，不能就是2.

```
#include <iostream>
#include <cstdio>
using namespace std;
int t;
int n, x;
int main()
{
    scanf("%d", &t);
    while (t --)
    {
        scanf("%d%d", &n, &x);
        int de = 0;
        int a, ans = 0, sf = 0;
        for (int i = 1; i <= n; ++ i)
        {
            scanf("%d", &a);
            if(a != x)ans = 1;
            if(a == x)sf = 1;
            de += x - a;
        }
        if(de != 0 && sf == 0)
        ++ ans;
        printf("%d\n", ans);
    }
}

```


---

## 作者：人间凡人 (赞：0)

## 结论题。~~刚开始看成了贪心，Wa了好久~~

### 题意：略

### 思路：

首先，答案只有可能为 $0,1,2$

如果刚开始所有人的等级全部等于 $Killjoy$ 的等级,输出 $0$

如果所有人等级数的平均数等于 $Killjoy$ 的等级或者有一个人的等级与 $Killjoy$ 的等级相等,输出 $1$ 

否则，输出 $2$ 即可

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int taxi,n,x,a[1009],flag,sum,flag1;
int main()
{
	cin>>taxi;
	for(int ttt=1;ttt<=taxi;ttt++)
	{
		flag=0,sum=0,flag1=0;
		cin>>n>>x;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=x)flag=1;
			if(a[i]==x)flag1=1;
		}
		if(flag==0)
		{
			cout<<0<<endl;
			continue;
		}
		for(int i=1;i<=n;i++)sum+=a[i];
		if(sum==x*n||flag1==1)
		{
			cout<<1<<endl;
			continue;
		}
		else 
		{
			cout<<2<<endl;
			continue;
		}
	}
}
```


---

## 作者：shihoghmean (赞：0)

~~在比赛被坑了好久，结果是个结论题。（草）~~
## 题意

每一组中,有n个未感染的数，给定x，在任何时候与x或被感染的数相等的数被感染，每
一轮每个数都可以变化（变化总和不变），问几轮全部感染。

## 思路

可得几个结论：

1. 若全部数一开始等于x，输出0（显然，全部数开始前就感染）

2. n个数的总和等于n*x，输出1（第一轮时把所有数变成x，变化总和必定为0）

3. 一开始有数被感染，即有至少一个数一开始等于x，输出1（被感染的数仍可以改变，只要将其他数变成x的变化总和补足就行，比赛的时候就是被这坑的）

4. 若上面都不满足，则输出2（可以第一轮先让n−1个数满足，最后让剩下1个数满足）

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[1001]; 
int main(){
	cin>>t;
	while(t--){
		int b=0,sum=0;
		cin>>n>>x;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==x) b++;//一开始就感染的人数
			sum+=a[i];//统计总和用来判断结论2
		}
		if(b==n) printf("0\n");//全部一开始感染
		else if((b&&b!=n)||sum==n*x) printf("1\n");//结论2、3
		else printf("2\n");//剩下情况
	}
	return 0;
}
```

---

## 作者：dead_X (赞：0)

## 前言
烂题。感觉这题数据范围迷惑，难度吓唬人

建议放到 A 题，我多想 WA 了 4 发
## 题意
给定 $n$ 个没有被感染的数和一个数 $x$ ，任何时候，如果一个数等于 $x$ 或者一个数等于一个被感染的数，这个数就会被感染。

你可以进行若干次操作，每次在总和不变的情况下改变一部分数的数值，求最少操作次数。
## 思路
结论题。

* 开始时全部感染： $0$ 。

* 开始时有人感染： $1$ 。

* 所有人平均一下之后全部感染： $1$ 。

* 其余情况： $2$ 。

证明：我觉得挺显然的。

构造：

* 开始时有人感染：所有人参加同一场比赛，其余的人 Rating 全部变为 $x$ ，已经被感染的人负责保持所有人 Rating 和不变。

* $2$ 次：第一次随便找两个人并且让其中一个人感染，另外一个人维持 Rating 和不变，然后按照上面一条来一次即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1003];
int main()
{
	int T=read();
	while(T--)
	{
		int n=read(),x=read();
		long long sum=0;
		int f=1,t=0;
		for(int i=1; i<=n; i++)
		{
			a[i]=read();
			if(a[i]!=x) f=0; else ++t;
			sum+=a[i];
		}
		sort(a+1,a+n+1);
		if(f) puts("0"); else
		if(sum==1ll*x*n) puts("1");
		else if(t) puts("1");
		else puts("2");
	}
	return 0;
}
```

---

## 作者：king_xbz (赞：0)

昨天的这道CF竟然还没有题解？那我来发一发！
# 题意简述
有n个整数，每次可以任选其中的一部分通过操作使其加减任意的数，且每次操作变化的和为0.当有一个整数有任一次变为x后，该整数便已经被感染。求让整数序列均被感染的最小操作数量。
# 思路分析
这题跟[P6746](https://www.luogu.com.cn/problem/P6746)有点像，我们考虑任意一个序列，只需最多两次即可被完全感染，即让$1$ ~ $n-1$被感染，再让n被感染。那么分类讨论：

1.当整个序列都是x时，只需操作0次

2，当整个序列中每个数与x差的和为0，只需操作1次

3.当序列中有$1$ ~ $n-1$个x时，可以直接让剩下的全部感染，只需操作1次

4.其他情况，需操作两次。

# 代码实现
很容易得出代码：
```cpp
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,x;
		cin>>n>>x;
		int ans=0,sam=0;
		for(fint i=1,k=0;i<=n;i++)
		cin>>a[i],ans+=(a[i]-x),a[i]==x?sam++:k++;
		if(ans==0&&sam==n)
		puts("0");
		else
		if(ans==0||(sam>0&&sam!=n))
		puts("1");
		else
		puts("2");
	}
	return 0;
}
```
祝大家AC愉快！

---

## 作者：LRL65 (赞：0)

这题好像也坑了好多人，我第一次也没过。



------------
题意：

有 $n$ 个数，还有一个数 $x$ （初始时就已经被感染，且 $x$ 不能更改） ,一个数有两种状态：有无被感染。

如果一个数和一个被感染的数相等，那么它也被感染了。

所有数都可以变成任意的整数，但是变化的总和得为 $0$ 。

一开始和 $x$ 相等的数已经被感染，输出让所有数都感染的最小次数。

------------
思路：

总共分为4种：
1. 如果所有数都为 $x$，输出 $0$ 。
1. 如果有至少一个数为 $x$ 且 并不是所有数都为 $x$ ，输出  $1$。
1. 如果不满足 1、2 且所有数变为 $x$ 的变化值为 $0$ ，输出1。
1. 如果上面3点都不满足，就输出2。因为任何情况时，都可以使前 $n-1$ 个数变为 $x$ ，然后使剩下的那个数变为 $x$ 。所以为2。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a;
int main() {
	cin>>t;
	while(t--) {
		cin>>n>>x;
		int k=0;
		int sum=0;
		for(int i=1;i<=n;i++) {
			cin>>a;
			if(a!=x) {
				sum=sum+(a-x);
				k++;
			}
		}
		if(k==0)cout<<0<<endl;
        else if(k<n)cout<<1<<endl;
        else if(sum==0)cout<<1<<endl;
		else cout<<2<<endl;
	}
}
```



---

