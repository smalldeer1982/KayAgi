# Collective Mindsets (hard)

## 题目描述

一共有 $n$ 个僵尸，每个僵尸头上有一个 $1 \sim n$ 之间的数字（**可重复！**），每个僵尸只能看到其他 $n - 1$ 个僵尸头顶的数字，当然，他们也知道自己的编号。 要求提供一种策略，使所有僵尸只利用自己知道的信息**同时**猜自己头顶的数字，保证至少有一个僵尸猜对。

## 说明/提示

$1 \le T \le 50000$，$2 \le n \le 6$，$1 \le r \le n$。

## 样例 #1

### 输入

```
4
2 1
1
2 2
1
2 1
2
2 2
2
```

### 输出

```
1
2
2
1
```

## 样例 #2

### 输入

```
2
5 2
2 2 2 2
6 4
3 2 6 1 2
```

### 输出

```
5
2
```

# 题解

## 作者：Karry5307 (赞：12)

### 题意

有 $n$ 个人，每个人头上贴有一个介于 $1$ 与 $n$ 之间的整数。每个人只能看到别人头上的数字，并且要通过这个猜出自己头上的数字。如果至少一个人猜中了自己头上的数字那么游戏胜利否则失败。已知第 $r$ 个人看到别的人头上的数字，求他的最优策略应该是什么。

$\texttt{Data Range:}1\leq T\leq 5\times 10^4,1\leq n\leq 6$

### 题解

这套题目的 A2 和 A3 全 tm 是烧脑题，但是抢了你谷的一血还是很爽的。

考虑不直接猜自己头上的数字而是猜所有人头上的数字之和对 $n$ 取模是多少。如果能猜对这个的话，因为已经知道别人头上的数字，同时自己头上的数字介于 $1$ 与 $n$ 之间，所以可以唯一确定自己头上的数字。

那么，如果第一个人猜所有人头上的数字之和对 $n$ 取模为 $0$，第二个人猜为 $1$，直到最后一个人猜 $n-1$，那么总会有一个人猜对。通过这个方法算出第 $r$ 个人应该猜多少即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll test;
ll n,r,sum;
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
	n=read(),r=read(),sum=0;
	for(register int i=1;i<=n-1;i++)
	{
		sum+=read();
	}
	printf("%d\n",(r-sum%n+n)%n+1);
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

## 作者：Yizhixiaoyun (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/CF690A3)

## 写在前面

此题代码难度极低，但是由于思维难度颇高，因此较难。

## 题目分析

由于有 $n$ 个人，猜测 $n$ 次，所以我们在 $\mod n$ 情况下考虑，这样即使最多也只会有 $n$ 种情况。

接着我们发现，假设第一个人猜数字之和对 $\mod n$ 为 $0$，第二个人猜则为 $1$，一直猜下去，最后一个人猜 $n-1$。这样下去，一定有一个人猜对。

由此，我们就可以这样算出第 $r$ 个人应该猜多少。

## 方法

自己的编号在 $1$ 到 $n$ 之间，所以在 $\mod n$ 情况下有唯一解。只要找到了取模下的所有人编号和，即可知道自己的编号。

## 贴上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,r,x,ans;
void init(){cin>>n>>r;ans=0;}
void duel(){
	for(register long long i=1;i<n;++i){
		cin>>x;
		ans+=x;
	}
}
void print(){cout<<(r-ans%n+n)%n+1<<endl;}
int main(){
//	freopen("test.out","w",stdout);
	cin>>T;
	while(T--){
		init();
		duel();
		print();
	}
}
```

---

## 作者：linxuanrui (赞：4)

### 分析

每个僵尸如果猜自己的数，是很难保证至少有一个僵尸猜对的。

因此，我们要从别的方法猜。因为有 $n$ 个僵尸，而且每个数的范围是 $1$ ~ $n-1$，那么我们只要猜某个数模 $n$ 的值，就可以保证至少有一个僵尸猜中。而且这个数得和每个数都有关，所以我们自然而然的想到**将所有数的和加起来**，因为这样子编码难度最小，也最容易理解。

既然如此，我们可以让第$i$个僵尸猜所有数的和模 $n$ 为 $i-1$，那么第 $r$ 个僵尸猜的就是模 $n$ 为 $r-1$。

既然题目已经给出了僵尸能看到的其他僵尸头上的数字，又知道所有数的和模 $n$ 为 $r-1$，我们便可以求出剩下的那个数了。

### 注意事项

1. c++ 中 `endl` 比 `'\n'` 慢很多，所以尽量用 `'\n'`。

2. 求出了剩下的那个数以后，因为这个数是 $0$ ~ $n - 1$ 的，所以结果要加一。

### 代码



```cpp
#include<iostream>
#define endl '\n'
using namespace std;
int t,n,r,x;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		int sum = 0;
		cin >> n >> r;
		for(int i = 1;i < n;i++)cin >> x,sum += x;
		cout << (r - sum % n + n) % n + 1 << endl;
	}
}
```

---

## 作者：_Haoomff_ (赞：4)

## 思路
 $n$ 个人中至少一人猜中，那么就是 $n$ 种可能性。
 
 接下来，我们假设第一个人猜的数 $\bmod\ n$ 的结果为 $0$，第二个人猜的数 $\bmod\ n$ 的结果为 $1$，以此类推，最后一个人猜的数 $\bmod\ n$ 的结果为 $n-1$。这样一定会有一个人猜对。
 
 这样，我们就可以算出第 $r$ 个人应猜多少。
## 方法
 $r$ 在 $1$ 至 $n$ 中，只需知道取模下其他人的编号和，即可得到自己的编号。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n,r,cnt;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cnt=0;
		cin>>n>>r;
		for(int i=1;i<n;++i){
			int a;
			cin>>a;
			cnt+=a;
		}
		cout<<(r-cnt%n+n)%n+1<<"\n";//注意，为了防止负数，需要再加上一个n
	}
	return 0;
}
```


---

## 作者：断清秋 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF690A3)

神奇的构造题。

考虑 $n$ 个人中至少要有一个人猜中，那么必然是有 $n$ 种可能性，每个人猜一种。于是自然想到要猜测某个数对 $n$ 取模的结果。

对于第 $R$ 个人，不妨设其余人的数字之和为 $sum$，自己头上的数字为 $x$，则 $sum+x$ 的结果是一个定值，那么猜测 $(sum+x) \bmod n$ 的值即可。为了简便，不妨令第 $R$ 个人猜测 $(sum+x) \bmod n$ 的值为 $R-1$。

于是有 $(sum+x) \bmod n=R-1$。

然后直接 $O(n)$ 暴力找一下可能的 $x$ 即可。

时间复杂度 $O(Tn)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned ll
using namespace std;
ll read()
{
	ll x=0,f=1;
    char ch=getchar();
	while(ch<'0'||ch>'9')
    {
        if(ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
ll t,n,r,sum,a[1001]; 
int main()
{
	t=read();
	while(t--)
	{
		sum=0;
		n=read(),r=read();
		for(ri i=1;i<=n-1;i++)
		{
			a[i]=read();
			sum+=a[i];
		}	
		for(ri i=1;i<=n;i++)
			if((sum+i)%n==r-1)
			{
				cout<<i<<"\n";
				break;
			}
	}
	back 0;
}
```

---

## 作者：_maze (赞：3)

很遗憾的一件事是，无论一个人用什么策略猜，他猜对的概率不会比乱猜多哪怕一点。

因此，我们可以说，一个人无论用什么固定的策略，只要他只能获取题面里的信息，他猜对的概率就是 $\frac{1}{n}$。因此他猜对的次数也是固定的，不会多也不会少。

发现题目只要求我们猜对一个人，因此猜对两个人就浪费了一个人的猜对机会。

所以让每个情况都猜对的唯一方法就是让这 $n$ 次不与其他人重叠，这样子才能覆盖所有的情况，每种情况恰好有一个人猜对。

所以只要你构造出一种策略，让每种情况都只有一个人猜对，那么这种策略就是可行的。

之后就简单了。你可以直接遍历查找然后把对应的编号存在哈希表里，也可以根据剩下点模 $n$ 的余数与当前编号进行判断。总之是很好写的。



---

## 作者：Utopioa_iris (赞：3)

# CF690A3 Collective Mindsets (hard) 题解
[题目传送门](https://www.luogu.com.cn/problem/CF690A3)

## 有话想说：
 这是蒟蒻我首过的紫题，比较水，代码实现不难，但是需要较多的思考，楼上的各位写的都好好，所以我就贴上一个大概思路和代码。~~这也是蒟蒻我的第一篇题解，希望能过呀。~~

------------

## 题目大意
$n$ 个僵尸头上有一个 $1$ 到 $n$ 的数，每个僵尸可以看到别人头上的数，要我们构造一种猜测方法使得至少有一个僵尸猜对。

------------

## 一点分析
如果每个人都猜自己的编号，这样投机取巧不能保证一定有人猜对。

总共有 $n$ 个僵尸，猜测 $n$ 次，因此可以在模 $n$ 的情况下考虑，这样可以限制范围。

因为有 $n$ 个人，编号是 $1$ 到 $n$，在模 $n$ 的情况下，一定有唯一解。

因为这个数可以重复，并且每人自己头上的数字与所有的数都有关，所以我们可以把所有的数加起来，假设这个数字和为 $ans$。

那么我们不妨这么设计：第一个人猜 $ans \bmod n$ 为 $0$，第二个人猜 $ans \bmod n$ 为 $1$，一直到第 $n$ 个人猜测 $ans \bmod n$ 为 $n-1$。另外，要注意一点：求出了剩下的那个数以后，因为这个数是从 $0$ 到 $n - 1$ 的，所以结果要加 $1$。这样，不就一定有一个僵尸可以猜对了吗？

### 那么!问题就迎刃而解了！

------------

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,r,ans,x;
int main()
{
	cin>>t;//组数 
	while(t--)
	{
		cin>>n>>r;//n个僵尸，编号为r 
		ans=0;//计数器 
		for(int i=1;i<n;i++)
		{
			cin>>x;
			ans+=x;//数字和 
		}
		cout<<(r-ans%n+n)%n+1<<endl;//将数字和对于n取模，用r减去取模后的值得到对应的数
		//+n后再%n可以转负数为正数，+1是因为取模后的数在0~n-1然而标准答案在1~n应当+1 
	}
	return 0;
	//完结撒花！！！ 
} 
```

------------

如有错误，欢迎指出！希望过审！谢谢大家！

---

## 作者：Aw顿顿 (赞：3)

强烈推荐把 A1 A2 和 A3 都做一遍，都是好题！

-----

> $n$ 个僵尸每个人头上有一个数字，每个僵尸只能看见别人头上的数字，要求构造一种猜测方法，使得至少有一个僵尸猜对。

为了限制范围，考虑在 $\bmod\ n$ 意义下思考，因为这样，我们猜测的范围就得到了限制。

那么因为自己头上的序号在 $1\sim n$ 之间，那么在 $\bmod\ n$ 意义下一定有唯一解，那么我们只要猜对了所有人头上的编号和（在取模意义下）就能猜对自己的编号。

我们接下来说明这种方法的合理性：由于一共有 $n$ 个人，可以猜 $n$ 次，因此我们才在 $\bmod\ n$ 意义下考虑，因为这样至多有 $n$ 种情况，所以我们为了保证猜测的结果各不相同遍历所有情况，我们令他们依次猜测总和为 $0,1,2,\cdots,n-1$。

因为各个僵尸猜测的对象是相同的，不会出现各考虑自己而重复的情况，然后算出来自己的号数就行。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T;
signed main(){
	cin>>T;
	while(T--){
		int n,r,res=0;cin>>n>>r;
		for(int i=1;i<n;i++){
			int x;cin>>x;
			res+=x;
		}cout<<(r-res%n+n)%n+1<<endl;
	}return 0;
}
```

---

## 作者：FriedrichC (赞：2)

[洛谷题面](https://www.luogu.com.cn/problem/CF690A3)

[原题链接](https://codeforces.com/contest/690/problem/A3)

这是相当有趣的一道题目。

## 题意分析
我们要设计一种每个个体猜测自己头顶的数字的方案，使得一个每个个体**相互可见**的序列中能够**至少一人**猜对，然后求出执行这种方案的情况下**某个个体**所要猜的数字。

乍一看，每个人头顶的数字都是随机的，似乎没有什么猜测的头绪，

但是既然我们在**每个人**都猜一次的情况下，只需要保证有一人猜对即可，那就表明对于某一种**既定局面**，一定只有**有限的** $n$ 种猜法，并且答案是其中的一种。

既然这样，我们就需要知道如何遍历这 $n$ 种猜法。

我们思考一下，对于某种既定局面，每个个体是无法从其看到的数字排列之中得到任何信息的，但是其看到的数字的总和（记为 $res$）却是有用的信息，

因为哪怕每个个体看到的数字总和可能不同，但是一但加上自己头顶的数字（记为 $x$）便一定是**定值**，也就是所有数字的总和，记为 $sum$。

既然我们知道只有有限的 $n$ 种猜法，我们就可以考虑把这些猜法**映射**到 $sum$ 模 $n$ 的余数，因为余数的取值也正是有 $n$ 种情况，并且我们可以通过余数的结果和 $res$ 作比较而算出 $x$ 的值。

那我们要如何遍历这 $n$ 种猜法呢？

我们发现会发现一个条件，不仅 $x\in [1,n]$，而且 $r\in [1,n]$，$r$ 的序列是 $n$ 的**排列**。

因此，$\exists r_0$，使 $sum\equiv r_0-1 (\operatorname{mod} n)$

又 $sum=res+x$，则 $res+x\equiv r_0-1 (\operatorname{mod} n)$

那么 $x\equiv r_0-1-res (\operatorname{mod} n)$

在这个策略下，每个个体的猜测方案都可以由其编号计算而来，

我们借由 $r$ 来遍历所有猜法，最后在 $n$ 个个体中会至少有一人猜对。

## 附上代码 
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,r,res=0;
        cin>>n>>r;
        for(int i=1,x;i<=n-1;++i)cin>>x,res+=x;
        cout<<((r-1-res)%n+n)%n+1<<'\n';
    }
	return 0;
}
```
## 一些细节
在取模运算前有减法，为防止负数，通常会先加上模数。

最后答案加一，因为模 $n$ 的计算结果属于 $[0,n-1]$，而我们的编号是从$1$开始的。



















---

## 作者：千早爱音 (赞：1)

给出一种构造方案的证明。

首先因为需要保证至少一个人猜对，所以要使得每个人“认为”的编号总和不相同。

因为题目要求编号各不相同，不妨假设编号总和在模 $ n $ 意义下与编号 $ id $ 同余。

所以设每个人的猜测为 $ guess $，自己的编号为 $ id $，其他人头上的数字之和为 $ sum $，则有：$ sum+guess=id $

解得 $ guess=id-sum $

然后把结果对 $ n $ 取模即可，时间复杂度 $ \mathcal{O}(Tn) $ 。


代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,r,sum=0;
		cin>>n>>r;
		for(int i=1;i<=n-1;i++)
		{
		int x;
		cin>>x;
		sum+=x;
		}
		r-=sum;
		while(r<0)
		r+=n;
		r%=n;
		r++;
		cout<<r<<endl;
	}
}
```

---

