# R3D3’s Summer Adventure

## 题目描述

R3D3 spent some time on an internship in MDCS. After earning enough money, he decided to go on a holiday somewhere far, far away. He enjoyed suntanning, drinking alcohol-free cocktails and going to concerts of popular local bands. While listening to "The White Buttons" and their hit song "Dacan the Baker", he met another robot for whom he was sure is the love of his life. Well, his summer, at least. Anyway, R3D3 was too shy to approach his potential soulmate, so he decided to write her a love letter. However, he stumbled upon a problem. Due to a terrorist threat, the Intergalactic Space Police was monitoring all letters sent in the area. Thus, R3D3 decided to invent his own alphabet, for which he was sure his love would be able to decipher.

There are $ n $ letters in R3D3’s alphabet, and he wants to represent each letter as a sequence of '0' and '1', so that no letter’s sequence is a prefix of another letter's sequence. Since the Intergalactic Space Communications Service has lately introduced a tax for invented alphabets, R3D3 must pay a certain amount of money for each bit in his alphabet’s code (check the sample test for clarifications). He is too lovestruck to think clearly, so he asked you for help.

Given the costs $ c_{0} $ and $ c_{1} $ for each '0' and '1' in R3D3’s alphabet, respectively, you should come up with a coding for the alphabet (with properties as above) with minimum total cost.

## 说明/提示

There are $ 4 $ letters in the alphabet. The optimal encoding is "00", "01", "10", "11". There are $ 4 $ zeroes and $ 4 $ ones used, so the total cost is $ 4·1+4·2=12 $ .

## 样例 #1

### 输入

```
4 1 2
```

### 输出

```
12
```

# 题解

## 作者：zhimao (赞：1)

CF 上好多做法都假了呢，甚至这场比赛官方题解都鸽了。

首先，$n>1$ 时不可能所有串都是 0 开头， 或是 1 开头，否则把开头的 0 或 1 删了依然合法。则 $n=2$ 时 两串必为 0 和 1 。让我们考虑把 n+1 我们应该怎么修改串，选择代价最小的，设为 s ，删掉 s ，加入 $\texttt{s1=s+'0'}$ 和 $\texttt{s2=s+'1'}$ 。这样一定是合法的，也是最优的。

然后对于代价一样的串一起处理，用 set 和 map 暴力模拟，就可以过了。这就是假做法，还非常短。放个代码帮助理解：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,b;
	long long ans;
	scanf("%d%d%d",&n,&a,&b);
	if(n==1)
	{
		printf("%d",min(a,b));
		return 0;
	}
	ans=1ll*(n-1)*(a+b);
	if(a==0||b==0)
	{
		printf("%lld",ans);
		return 0;
	}
	n-=2;
	set<long long> s;
	map<long long,long long> ma;
	++ma[a],++ma[b];
	s.insert(a),s.insert(b);
	while(n)
	{
		const long long x=*s.begin(),p=min(1ll*n,ma[x]);
		s.erase(s.begin());
		ans+=x*p;
		n-=p;
		ma[x]=0;
		s.insert(x+a);ma[x+a]+=p;
		s.insert(x+b);ma[x+b]+=p;
	}
	printf("%lld",ans);
	return 0;
}
```
100000000 1 10000000 这类数据就可以卡掉这种做法。

于是我们考虑根号分治 。

设 $a=\min(c0,c1),b=\max(c0,c1),B=\sqrt{n\times t},t$ 是一个常数，取 取值之后再说。

当 $B>\tfrac{b}{a}$ ，则直接上上面的暴力，复杂度为 $O(B\log^2n)$ 。因为对于有 x 个 0，y 个 1 的串有 $C_{x+y}^y$ 个，当 y 变大，它的增长速度很快。

当 $B<\tfrac{b}{a}$ ，我们计算代价小于 $b+b$ 的串的个数，为(除法都向下取整) $sum=\tfrac{b+b-1}{a}+(\tfrac{b-1}{a}+1)\times(\tfrac{b-1}{a}+2)/2\ge (B+3)\times(B+2)/2>n\times t/2$（注意此时 b 只用 0 或 1 次），则 $t\ge2$ 即可 。那么就~~只要把 b 用一次的串的代价和数量弄进 set 和 map 里~~按代价枚举 b 用一次的串，每次取出时判断加上 b 用零次的串的个数有没有超过 n 个即可。复杂度 $O(B)$ 。

时间复杂度 $O(\sqrt n\log^2n)$ ，带根号很涝，但总比假做法好。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,b;
	long long ans;
	scanf("%d%d%d",&n,&a,&b);
	if(n==1)
	{
		printf("%d",min(a,b));
		return 0;
	}
	ans=1ll*(n-1)*(a+b);
	if(a==0||b==0)
	{
		printf("%lld",ans);
		return 0;
	}
	n-=2;
	if(a>b) swap(a,b);
	set<long long> s;
	map<long long,long long> ma;
	if(b/a>n)
	{
		printf("%lld",ans+1ll*(1+n)*n/2*a);
		return 0;
	}
	if(sqrt(30.0*n)>(1.0*b/a))
	{
		++ma[a],++ma[b];
		s.insert(a),s.insert(b);
		while(n)
		{
			const long long x=*s.begin(),p=min(1ll*n,ma[x]);
			s.erase(s.begin());
			ans+=x*p;
			n-=p;
			ma[x]=0;
			s.insert(x+a);ma[x+a]+=p;
			s.insert(x+b);ma[x+b]+=p;
		}
	}
	else
	{
		long long p=n;
		for(long long i=b,j=1;i<=b+b&&p>0;i+=a,++j) s.insert(i),ma[i]+=j,p-=j;
		//代码中的做法为划去的做法
		while(n)
		{
			const long long x=*s.begin(),p=min(1ll*(n-x/a),ma[x]);
			s.erase(s.begin());
			if(p<=0)
			{
				ans+=1ll*(n+1)*n/2*a;
				break;
			}
			ans+=x*p;
			n-=p;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

