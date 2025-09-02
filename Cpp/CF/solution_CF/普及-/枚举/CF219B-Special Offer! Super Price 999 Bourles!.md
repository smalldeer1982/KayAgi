# Special Offer! Super Price 999 Bourles!

## 题目描述

Polycarpus is an amateur businessman. Recently he was surprised to find out that the market for paper scissors is completely free! Without further ado, Polycarpus decided to start producing and selling such scissors.

Polycaprus calculated that the optimal celling price for such scissors would be $ p $ bourles. However, he read somewhere that customers are attracted by prices that say something like "Special Offer! Super price 999 bourles!". So Polycarpus decided to lower the price a little if it leads to the desired effect.

Polycarpus agrees to lower the price by no more than $ d $ bourles so that the number of nines at the end of the resulting price is maximum. If there are several ways to do it, he chooses the maximum possible price.

Note, Polycarpus counts only the trailing nines in a price.

## 样例 #1

### 输入

```
1029 102
```

### 输出

```
999
```

## 样例 #2

### 输入

```
27191 17
```

### 输出

```
27189
```

# 题解

## 作者：loser_seele (赞：1)

实际上，我们只需要枚举改完后的方案末尾的 $ 9 $ 的数量即可，然后每次找到离这个数最接近的末尾有若干个 $ 9 $ 的数，如果这个数满足要求则更新答案即可。而计算最接近的数可以 $ \mathcal{O}(1) $ 计算，只需要预处理出 $ 10 $ 的次幂之后计算即可，当然对于本题这个优化是不必要的。然后在 $ p $ 后面添加若干个 $ 9 $，其实就是增加 $ 10^n-1 $，如果超过 $ p $ 再扣除一倍即可。

时间复杂度 $ \mathcal{O}(lg{p}) $，可以通过，目前最优解。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define int long long
int power[20];
signed main()
{
	int p=0,d=0;
	cin>>p>>d;
	power[0]=10;
	for(int i=1;i<=19;i++)
	power[i]=power[i-1]*10;
	int ans=p,numof9 = 0;
	for(int i=1;i<19;i++)
	{
		int p0w=power[i-1];
		int cur = p-p%p0w+p0w-1;
		if(cur > p)
		{
			int times = (cur-p)/p0w+((cur-p)%p0w != 0);
			cur -= times*p0w;
		}
		if(cur >= 0 && p-cur <= d && i > numof9)
		{
			numof9 = i;
			ans = cur;
		}
	}
	cout<<ans;
}
```


---

## 作者：wangjue233 (赞：0)

# Solution
[题目传送门](https://www.luogu.com.cn/problem/CF219B)

## 题目思路
我们可以检查每个以 $10^n$ 为基数的位置是否能够通过减去一个小于 $d$ 的数得到一个新的数，这个数以 $9$ 结尾，而且在当前位以 $0$ 结尾。

当我们找到这样一个数时，我们可以用一个变量记录下来，并继续查找是否有可能在更高的位上执行相似的操作。

当我们发现不能在更高位上执行这样的操作或操作导致减少的超过了 $d$，我们就停止寻找，跳出循环。

最后，我们输出最后一次成功构造的以 $9$ 结尾的数就可以啦。

注：这道题 $p$, $d$ 的最大值已经达到了 $10^{18}$，所以必须要开 long long。~~有些人今年的cspj第二题就因为没开 long long 丢了很多分~~
***
## Code
```cpp
#include<iostream>
#define ll long long
using namespace std;
ll p, d, m;
int main(){
    cin >> p >> d;
    if(p < 10){ //如果p小于10，那么就代表不能以9结尾，直接输出 p
        cout << p << "\n";
        return 0;
    }
    for(ll i = 10; i <= p; i *= 10){
        if(!(p % i + 1 == i)){ //检查当前的位置是否可以减去数值变成以9结尾
            if(p % i < d) m = p % i + 1; //如果可以，则记录可以减去的值使其成为以9结尾
            else break; //如果不行则直接结束循环
        }
    }
    cout << p - m << "\n";
    return 0;
}
```
时间复杂度：$O(\log_{10} p)$，可以通过本题。

---

## 作者：rain_dew (赞：0)

原题目链接：[CF219B](https://www.luogu.com.cn/problem/CF219B)

### 题意：

给定两个数 $p,d$，输出 $p-d \le X \le p$ 中末尾的 $9$ 最多的整数 $X$。

### 思路：

贪心模拟题。

先前出现大量的错误题解（暴力做法），因而这里提供一种枚举运算方法。

**枚举**每一位可能出现数字 $9$ 时需要扣除的差值 $ans$，易知 $ans$ 一定是一个被 $10$ 的倍数取模后多 $1$ 的数字（否则尾数不能出现 $9$）。如果超出规定的边界后马上退出，最后输出 $p-ans$ 后即为答案。

对于本题目数据范围，$1 \le p \le 10^{18}$，一定要开 `long long`。

有不少题解认为需要**特判**，个人认为其意义并不很大，在个位的处理方式都与十位，百位，千位等相似，可同时在一个循环中进行。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long ans;
long long p,d;
int main()
{
	scanf("%lld%lld",&p,&d);
	for (long long i=1;i<=p;i*=10)
		if (p%i+1!=i)
			if (p%i<d)
				ans=p%i+1;
			else
				break;
	printf("%lld",p-ans);
	return 0;
}
```

---

## 作者：ylch (赞：0)

# [CF219B] Special Offer! Super Price 999 Bourles! 题解

不得不说这题目名字挺吸引人的。

## PART1. 题目重述

给定两个整数 $p,d$，求出 $[p-d,p]$ 中末尾 $9$ 最多的个数。

## PART2. 解题思路

对于这个题，我们可以采用枚举法与贪心策略来解决。

对于一个末尾为 $9$ 的数字 $k$，$k+1$ 一定是整十整百一类的数。我们可以先从后往前**枚举**每一位，求出要想把这些位变成 $9$ 要减去几，如果这个减数在 $d$ 的范围之内，我们就记为一个可行答案。同时遵循**贪心**的思想，为 $9$ 的位数肯定越多越好，所以枚举直到差值大于 $d$ 或原数只剩一位时就结束循环，得出答案。

我们画表格来理解一下，此处设 $p = 1029, d = 102$。

| 当前枚举位数 $\ \ $ | 当前尾部数 $\ \ $ | 最近的尾部为 $9$ 的数字 $\ \ $ | 差值 $\ \ $ | 当前答案 $\ \ $ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $102\color{red}9$ | $1029$ | $0$ | $1029-0 = 1029$ |
| $2$ | $10\color{red}29$ | $999$ | $30$ | $1029-30 = 999$ |
| $3$ | $1\color{red}029$ | $999$ | $30$ | $1029-30 = 999$ |

所以得出最接近的是 $999$。

## PART3. AC 代码

写代码时，用取模 $10^n$ 的形式取尾部数字，用变量 $m$ 存储差值，最后输出 $p-m$ 得出答案。**当 $p$ 为一位数时，答案就是它本身。**

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

signed main()
{
	long long p, d, m = 0;
	cin >> p >> d;
	if (p < 10) //特判
	{
		cout << p << endl;
		return 0;
	}
	for (long long i = 10; i<=p; i*=10) //取模运算取尾部数字
	{
		if (p%i+1 == i){} //说明这一位本来就是9，无需记录
		else
		{
			if (p%i+1 <= d)	m = p%i + 1; //差值在范围内就记录
            //可以模拟一下是如何计算差值的
			else	break;
		}
	}
	cout << p-m << endl;
	return 0;
}
```

## End

管理员大大辛苦啦~

谢谢大家！

---

## 作者：Adchory (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF219B)

#### 思路

很明显是一道贪心题。

当一个数 $N$ 末尾有 $x$ 个 $9$ 时，那么 $N+1$ 末尾就有 $x$ 个 $0$，我们可以转而枚举 $N+1$，令 $\operatorname{lowbit(x)}$ 表示除去十进制 $x$ 中最低位非零的数得到的结果，我们可以不断对 $p$ 进行 $\operatorname{lowbit}$ 操作，不断更新 $ans$，直到 $p$ 为 $0$ 时。

当然，我们还是过不了，原因是我们没有判断 $p$ 本身，最后加个特判就可已过了。

#### 贴贴代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll p,d,k=1,ans,S,np,n;
inline ll lowbit(){return ++S,p/(k=k*10)*k;}
int main(){
	scanf("%lld%lld",&p,&d);d=p-d;ans=p;np=p;
	while(np%10==9) n++,np/=10;
	while(p){
		p=lowbit();
		if(p-1>=d) ans=S>n?n=S,p-1:ans;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：TLEWA (赞：0)

简单贪心题，但是把我 Hack 自闭了。

看到 $1 \le p \le 10^{18},0 \le d<p$ 的数据范围，可以想得到基于值域的暴力做法是无法通过的，考虑贪心。

我们枚举降价后末尾 9 的位数，可以发现，设末尾 9 的位数为 $x$，我们最小的降价代价就是 $p-(p$ $\bmod$ $10^x)-1$，因为一个一个累减的话，这是我们遇到的第一个符合要求的数。但是有个特例：这个数原本就符合要求了，你再减可能反而不如原结果，注意处理一下就行。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long p,d;
long long k=1;
long long ans;

int get(long long x) {
	int k=0;
	for(;x%10==9;x/=10) ++k;
	return k;
} 
int cnt;
int main() {
	cin >> p >> d;
	ans=p,cnt=get(p);
//	cout << cnt << endl;
	for(int i=1;i<=18;++i) {
		k*=10;
		if(p>=k&&(p%k)<d)
			if(cnt<get(p-p%k-1))ans=p-p%k-1,cnt=get(ans);
	}
	cout << ans;
	return 0;
}
```


---

## 作者：幻想繁星 (赞：0)

# 题意
给你一个 $p$ 和一个 $d$ 让 $p$ 减去尽可能小且小于 $d$ 的正整数数，使结果的末尾的 $9$ 最多。
# 思路
显然，我们可以枚举末尾的 $9$ 的个数进行贪心。由于 $p \le 10^{18}$ 所以，只需要枚举 $18$ 种情况即可。（之前题解区的题解有枚举 $d$ 的，这是显然行不通的，因为 $d \le 10^{18}$ 会 T 到飞起）（注：这里是为了避开思路误区，错误题解现已被爆破）
# 实现
## 1、枚举
让 $i$ 从 $18$ 到 $p$ 本身末尾有的 $9$ 的个数，如果找到符合的情况直接输出并结束程序，如果最终没找到那么输出 $p$ 本身即可。
```cpp
	t=p;
	while(t)
	{
		if(t%10==9)sum++;
		else break;
		t/=10;
	}//统计p本身末尾有的9的个数 
	for(int i=18;i>sum;i--)//枚举末尾9的个数 
	{
		if(check(i))//判断是否成立 
		{
			long long ans=p/(long long)pow(10,i)-1;//不是末尾9的部分 
			if(ans>0) cout<<ans;//如果有输出 
			for(int j=1;j<=i;j++)//输出末尾的9 
				cout<<9;
			return 0;
		}
	}
```

## 判断
我们先算出末尾 $9$ 的大小并算出末尾 $9$ 前面的数将其拼接并判断其是否大于 $p-d$ 且小于 $p$ 即可。
```cpp
bool check(int i)
{
	long long a=pow(10,i)-1;//末尾的9组成的数 
	long long c=p/(long long)pow(10,i)-1;//截取前面的数 
	if(c<0) c=0;//防止出锅 
	long long b=c*(long long)pow(10,i);//给9空位 
	return p-d<=b+a&&p>=b+a;//判断 
}
```

---

## 作者：Light_az (赞：0)

### 贪心

这题解区的题解怎么全是暴力，这肯定会超时的，因此我们采用贪心解法。

首先题目求的是数字末尾 $9$ 的数量最多，而不是数字总共 $9$ 的数量最多，那么我们可以从个位开始遍历，如果这一位数字本来就等于 $9$，我们就跳过，否则我们就拿 $n$ 把这一位数字补成 $9$。

但是这道题目有很多细节：

- 数字可能会有负数，需要特判退位。

- 字符串输入，颠倒字符串。

- 高位以 $0$ 开头的特殊处理。

但是最重要的是：$n$ 的进位影响。

对于第一位，$n$ 对数位的影响是 $n$。

对于第二位，$n$ 对数位的影响是 $n\div10$。

对于第三位，$n$ 对数位的影响是 $n\div100$。

发现了吗，$n$ 对第 $i$ 位的影响其实就是将 $n$ 除以 $(i-1)$ 个 $10$，也就是我们在遍历的时候，每遍历一次，$n$ 就要除以 $10$，这样就可以保证 $n$ 大于 $0$ 时可以对这一位数字做出影响。

最后因为我们颠倒了字符串，所以记得倒叙输出，下面是完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,k,ans=0,len;
string s;
ll a[20];
void f(){//退位特判 
	for(int i=1;i<len;i++){
		while(a[i]<0){
			a[i]+=10;
			a[i+1]--;
		}
	}
}
int main(){
	cin>>s>>n;
	len=s.size();
	for(int i=1;i<=len;i++){//字符串颠倒 
		a[i]=s[len-i]-'0';
	}
	for(int i=1;i<len;i++){
		f();//退位 
		if(a[i]==9){//不需要补 
			n/=10;
			continue;
		}		
		if(n>=a[i]+1){//补 
			n-=(a[i]+1);//数字减少 
			a[i]=9;
			a[i+1]--;//退位 
		}
		else{//n无法对 a[i] 做出影响，遍历停止 
			break;
		}
		n/=10;//见文字 
	}
	while(!a[len]&&len>1){//高位0特判 
		len--;
	}
	for(int i=len;i>=1;i--){//倒叙输出 
		cout<<a[i];
	}
	return 0;
}

```

最后，让我们一起膜拜 [creation_hy](https://www.luogu.com.cn/user/576378) 吧。

---

## 作者：qwasd (赞：0)

复杂度正确的，$\mathcal O(\log p)$ 的题解。  

从大到小枚举最后有几个 $9$，每次判断能不能达到。  

现在问题就是：求 $p$ 最少减去多少，可以让末尾有 $x$ 个 $9$。

首先如果 $p$ 末尾 $x$ 位本来就都是 $9$，就不用减；其他情况，从低到高第 $x+1$ 位退 $1$，后 $x$ 位全变成 $9$，没有比这更少的方案。  

实现上可以先预处理出 $10^x$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p,d;
inline ll gg(int x){
	static ll p10[20];
	if(!p10[0]){
		p10[0]=1;
		for(int i{1};i<=18;++i) p10[i]=p10[i-1]*10LL;
	}
	if(p<p10[x]-1) return -1;
	if(p%p10[x]==p10[x]-1){
		return p;
	}
	else{
		return (p/p10[x]-1LL)*p10[x]+(p10[x]-1LL); 
	}
}
signed main(){
	cin>>p>>d;
	for(int i{18};i>=0;--i){
		ll t=gg(i);
		if(p-t<=d){
			cout<<t;
			break;
		}
	}
	return 0;
}
```

---

