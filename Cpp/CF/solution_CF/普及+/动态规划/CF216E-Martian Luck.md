# Martian Luck

## 题目描述

You know that the Martians use a number system with base $ k $ . Digit $ b $ ( $ 0<=b&lt;k $ ) is considered lucky, as the first contact between the Martians and the Earthlings occurred in year $ b $ (by Martian chronology).

A digital root $ d(x) $ of number $ x $ is a number that consists of a single digit, resulting after cascading summing of all digits of number $ x $ . Word "cascading" means that if the first summing gives us a number that consists of several digits, then we sum up all digits again, and again, until we get a one digit number.

For example, $ d(3504_{7})=d((3+5+0+4)_{7})=d(15_{7})=d((1+5)_{7})=d(6_{7})=6_{7} $ . In this sample the calculations are performed in the 7-base notation.

If a number's digital root equals $ b $ , the Martians also call this number lucky.

You have string $ s $ , which consists of $ n $ digits in the $ k $ -base notation system. Your task is to find, how many distinct substrings of the given string are lucky numbers. Leading zeroes are permitted in the numbers.

Note that substring $ s[i...\ j] $ of the string $ s=a_{1}a_{2}...\ a_{n} $ ( $ 1<=i<=j<=n $ ) is the string $ a_{i}a_{i+1}...\ a_{j} $ . Two substrings $ s[i_{1}...\ j_{1}] $ and $ s[i_{2}...\ j_{2}] $ of the string $ s $ are different if either $ i_{1}≠i_{2} $ or $ j_{1}≠j_{2} $ .

## 说明/提示

In the first sample the following substrings have the sought digital root: $ s[1...\ 2] $ = "3 2", $ s[1...\ 3] $ = "3 2 0", $ s[3...\ 4] $ = "0 5", $ s[4...\ 4] $ = "5" and $ s[2...\ 6] $ = "2 0 5 6 1".

## 样例 #1

### 输入

```
10 5 6
3 2 0 5 6 1
```

### 输出

```
5```

## 样例 #2

### 输入

```
7 6 4
3 5 0 4
```

### 输出

```
1```

## 样例 #3

### 输入

```
257 0 3
0 0 256
```

### 输出

```
3```

# 题解

## 作者：豆浆 (赞：3)

[题目](https://www.luogu.org/problem/CF216E)

题目大意：一个数字的数字根定义为在k进制下各位数字相加，重复若干次，得到的一位数。如果一个数字的数字根为b，那么这个数字就很lucky。给你一个数字串，问有多少个连续字串组成的数字是lucky的。

首先必须了解数字根。数字根有以下性质（跟这个题相关的）：

　　1.一个数x加9的数字根是x的数字根。比如：8+9=17，R(17)=8;12+9=21，R(21)=R(12).

　　2.一个数x乘9的数字根是9.比如：6*9=54,R(54)=9.

　　3.若A+B=C,则R(a)+R(b)=R(c).

　　　　证明：由性质(1)(2)可将每个数字分解为若干9与其数字根的和,A=9n+R(A) , B=9m+R(B) , C=9p+R(C) .

　　　　　　   则R(A)+R(B)=R(C)+9(p-m-n) .再由性质(1)(2)知9的倍数对数字根没有影响，得证。


　　由性质3，我们在这道题求解字串数字根的事时候就可以用前缀和维护。

　　由于题目允许前导0，所以在统计的时候还需要统计0对答案的影响。

　　当b=0时，答案就是选取0的方案数；b=k-1时，由于取模运算会出现0，所以要防止0被重复计算。

　　顺次统计每一位，f(sum)=(sum-b) mod (k-1)，我用了一个map记录数字根出现的次数方便查找。
  
  
### c++ code:
  
  
```cpp
#include <bits/stdc++.h>//完美的头文件
using namespace std;
map<int,int> m;//这里用map更方便
long long ans,sum;
int k,b,n,x,cnt;
int main(){
	cin>>k>>b>>n;
	if(!b){
		for(int i=0;i<n;i++){
			cin>>x;
			cnt=x?0:(cnt+1);
			ans+=cnt;
		}
	}
	else{
		k--;//csdn
		m[0]=1;
		for(int i=0;i<n;i++){
			cin>>x;
			sum+=x;
			cnt=x?0:(cnt+1);
			ans+=m[(sum-b+k)%k];
			m[sum%=k]++;
			if(b==k){
				ans-=cnt;
			} 
		}
	}
	cout<<ans<<endl;
   return 0;//完结撒花✿✿ヽ(°▽°)ノ✿
}
```



---

## 作者：_edge_ (赞：1)

感觉现在的两篇题解写的不太好，我来补充一下把。

首先看到这种题目就应该想到若 $x$ 经过那么一些数位和变换如果最终为 $b$，那么 $x \equiv b \pmod {(k-1)}$。

这个很好证，就想一下每一个 $x$ 都可以被分解为 $\sum \limits _{i=0}^m a_i \times k^{i}$ 其中 $m$ 表示位数，然后我们发现这个东西在 $\bmod {(k-1)}$ 之后是不变的，因为对于任意 $i$ 都有 $k^i \equiv 1 \pmod {(k-1)}$ 然后我们发现这样迭代下去实际上就是 $x \bmod {(k-1)}$。

有了这个结论之后，做这道题目就比较容易了，首先开一个 map 作为桶，然后记录当前 $1$ 到 $i$ 的前缀和在 $\bmod {(k-1)}$ 后是什么值。

当然，这题目还并没有想象地那么简单。

对于 $b=0$ 的情况下，除非是 $0000...0$ 的形式，否则最后就一定不会变 $0$ ，这个情况要特判一下。

还有一个地方处理要注意一点，对于 $b=k-1$ 的情况下，存在一些 $0000...0$ 的形式，可能会将其算入答案中，但显然这是不合法的，所以还要减掉他们。

如果有不懂的私聊作者，有问题的也请私聊。

```cpp
#include <iostream>
#include <cstdio>
#include <map>
#define int long long 
using namespace std;
int n,k,b,sum,ans;
map <int,int> Map;
signed main()
{
    scanf("%lld %lld %lld",&k,&b,&n);
    if (b==0) {
        for (int i=1;i<=n;i++) {
            int xx=0;scanf("%lld",&xx);
            if (xx==0) sum++;
            else sum=0;
            ans+=sum;
        }
        cout<<ans<<"\n";
    }
    else {
        Map[0]++;int cnt=0;
        for (int i=1;i<=n;i++) {
            int xx=0;scanf("%lld",&xx);
            if (xx) cnt=0;
            else cnt++;
            sum+=xx;
            ans+=Map[(sum-b+k-1)%(k-1)];
            Map[sum%(k-1)]++;
            if (b==k-1) ans-=cnt;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```


---

## 作者：ifffer_2137 (赞：0)

### 题意
给定一个长为 $n$ 的 $k$ 进制数码序列，求子段组成的 $k$ 进制数数根为 $b$ 的子段数量。
### 分析
打表可知 $k$ 进制下数根循环节为 $k-1$。

所以合法子段，即满足子段组成的 $k$ 进制数模 $k-1$ 余 $b$。

当然这里要特判掉 $0$，简单统计所有连续为 $0$ 的段的子段数即可，然后当 $b=k-1$ 时我们把 $b$ 看成 $0$ 计算，然后减去数根实际为 $0$ 的数量即可。

由于子段是个 $k$ 进制数，根据位值原理，组成的数为：
$$\sum_{i=1}^{len}k^{i-1}a_i$$
它对 $k-1$ 取模：
$$\sum_{i=1}^{len}k^{i-1}a_i \equiv \sum_{i=1}^{len}1^{i-1}a_i \pmod {k-1}$$

所以合法子段的充要条件是子段和模 $k-1$ 余 $b$。

然后考虑前缀和，拿个``` map ```当桶装一下，就可以简单计数了，时间复杂度 $O(n\log n)$。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e5+5;
int k,b,n,ans;
int a[maxn];
map<int,int> t;
signed main(){
	cin.tie(0),cout.tie(0);
	k=read(),b=read(),n=read();
	int cnt=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]) ans+=cnt*(cnt+1)/2,cnt=0;
		else cnt++;
	}
	if(cnt) ans+=cnt*(cnt+1)/2;
	if(b==0){
		cout<<ans<<endl;
		return 0;
	}else if(b==k-1){
		ans=-ans;
	}else{
		ans=0;
	}
	t[0]++;
	for(int i=1,s=0;i<=n;i++){
		s=(s+a[i])%(k-1);
		ans+=t[(s-b%(k-1)+(k-1))%(k-1)];
		t[s]++;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Yuby (赞：0)

[题面](https://www.luogu.com.cn/problem/CF216E)

点数：2000

### 第一个解法：

就是先简单的按题意写一个求数字根的函数。

```cpp
ll f(ll x)
{
	if(x<k&&x>0)return x%k;
    ll sum=0;
    while(x)
    {
        sum+=(x%k);
        x/=k;
    }
    if(sum<k)return sum%k;
    return f(sum)%k;
}
```

然后我们先 $O(n^2)$ 验证一下我们的结论。

这里注意你把一个数接到另一个数后面的数字根和你直接把两个数相加再求数字根是一样的。

（自己想（我都能想明白怎么可能有人想不明白。

```cpp
	k=read(),m=read(),n=read();
	pre[0]=0;
	for(ll i=1;i<=n;i++)
	{
		a[i]=read();
		pre[i]=pre[i-1]+a[i];
	}
	ll ans=0;
	for(ll i=1;i<=n;i++)
	{
		for(ll j=i;j<=n;j++)
		{
			bool flag=(f(pre[j]-pre[i-1])==m);
			if(flag)ans++;
		}
	}
	write(ans);
```

然后它 TLE 了！所以说结论应该是对的。现在只要改成 $O(n\log n)$ 的就行。

这个时候问题来了，怎么转 $O(n\log n)$？你可能觉得 map 存一下不就行了？

#### 但是（重点）

这个东西是不可逆的。

证明放在最后。

所以这个解法不能做到 $O(n\log n)$（我太菜了。。。

### 正解

上面的结论中是有可取之处的。

就是这个：把一个数接到另一个数后面的数字根和直接把两个数相加再求数字根是一样的。

baidu 一下得：对于任意一个 $n$ 进制数，如果各个位上的数字之和能被 $n-1$ 整除，那么这个数能被 $n-1$ 整除。

所以直接加，然后把它对 $k-1$ 取模放到一个 map 里求答案就行（这应该不用我教吧。。。

核心代码：

```cpp
const ll MAXN=1e5+7;
ll n,m,k,a[MAXN];
map<ll,ll>mp; 
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	k=read(),m=read(),n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	ll ans=0;
	if(!m)
	{
		ll cnt=0;
		for(ll i=1;i<=n;i++)
		{
			if(!a[i])cnt++;
			else cnt=0;
			ans+=cnt;
		}
	}
	else
	{
		k--;
		mp[0]=1;
		ll cnt=0,sum=0;
		for(ll i=1;i<=n;i++)
		{
			sum+=a[i];
			if(a[i])cnt=0;
			else cnt++;
			ans+=mp[(sum-m+k)%k];
			sum%=k;
			mp[sum]++;
			if(m==k)ans-=cnt;
		}
	}
	write(ans);
	return 0;
}
```

证明前面那玩意：

如他为真，即 $x+a$ 在 $k$ 进制下的数字和等于 $x$ 和 $a$ 的数字和。

（进位是不存在是吗？

所以，显然不成立。

（疑惑，这么点证明我何必放在最后呢？）


---

