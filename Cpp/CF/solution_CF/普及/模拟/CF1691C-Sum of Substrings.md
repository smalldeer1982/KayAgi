# Sum of Substrings

## 题目描述

给定由 $0$ 和 $1$ 组成的长度为 $n$ 的字符串 $ s $ 。

定义一个十进制数字 $ d_i $ 十位和个位分别为 $ s_i $ 和  $ s_{i+1} $ 。 定义 $ f(s) $ 为所有合法的 $ d_i $ 的和。也就是说 $ f(s) = \sum\limits_{i=1}^{n-1} d_i $ 。

比如， 对于字符串 $ s = 1011 $ ：

- $ d_1 = 10 $ ；
- $ d_2 = 01 $ ；
- $ d_3 = 11 $ ;
- $ f(s) = 10 + 01 + 11 = 22 $ 。

在一次操作中你可以交换两个相邻的元素。 找到经过不多于 $k$ 次操作后 $ f(s) $ 的最小值。


保证所有数据中 $ n $ 的和不超过 $ 10^5 $ 。

## 说明/提示

- 对于第一组数据，不能做任何操作。$ f(s) = f(1010) = 10 + 01 + 10 = 21 $ 。
- 对于第二组数据，可以将字符串变成 $0011000$。 此时 $ f $ 的值为 $ 22 $ 。
- 对于第三组数据，可以将字符串变成 $00011$。 此时 $ f $ 的值为 $ 12 $ 。

## 样例 #1

### 输入

```
3
4 0
1010
7 1
0010100
5 2
00110```

### 输出

```
21
22
12```

# 题解

## 作者：nullqtr_pwp (赞：5)

# CF1691C 题解
赛时吃了五发罚时的题，个人认为特判挺烦的。

$f(s)$ 不妨提取出其中的定值：$\sum_{i=1}^{n}11\times a_i$（一次做十位，一次做个位），这个定值显然是有问题的，因为最两端的数并非如此。所以要减去 $a_1+10\times a_n$（$a_1$ 少了一次个位，$a_n$ 少了一次十位），综上，$f(s)=\sum_{i=1}^{n}11\times a_i-(a_1+10\times a_n)$

回到问题，要想使 $f(s)$ 最小，就让减去的这个值最少，所以**两端的数最好都是 $1$。而且中间的数的顺序不影响答案**，但是如果不能实现，先是 $a_n$ 为 $1$，其次是 $a_1$ 为 $1$。记 $cnt_1$ 为最左边的 $1$ 前面 $0$ 的个数，显然 $cnt_1$ 就是让 $a_1=1$ 的最小操作次数；类似的，记 $cnt_2$ 为最右边的 $1$ 后面 $0$ 的个数，显然 $cnt_2$ 就是让 $a_n=1$ 的最小操作次数；令 $sum=\sum_{i=1}^{n}11\times a_i$。

讨论：若两端都可以在指定次数内都变成 $1$，那么答案为 $sum-11$；若前面条件无法满足但 $a_n$ 可以是 $1$，答案为 $sum-10$；若前面条件无法满足但 $a_1$ 可以是 $1$，答案为 $sum-1$；若前面条件均无法满足，答案为 $sum$，此部分代码：（没有特判，显然 AC 不了）
```cpp
if((cnt1+cnt2)<=k) printf("%d\n",sum-11);
else if(cnt2<=k) printf("%d\n",sum-10);
else if(cnt1<=k) printf("%d\n",sum-1);
else printf("%d\n",sum);
```
只写这么点你会喜提 ```Wrong Answer on pretest #2```

**注意，有 $2$ 个特判！！！**

特判一：序列中有且仅有一个 $1$，扫一遍就行。与原来的区别是不讨论 $cnt1+cnt2$ 的情况，那么仍然是 $cnt2$ 的优先级更高，答案是 $1$，其次 $cnt1$，答案是 $10$，都无法满足答案是 $11$。
```cpp
for(int i=0;i<n;i++)if(a[i]==1)ans++;
if(ans==1){
	if(cnt2<=k)puts("1");
	else if(cnt1<=k)puts("10");
	else puts("11");
}
```

特判二：序列中全是 $0$，充要条件是 $cnt1+cnt2=2n$，直接输出 $0$。

```cpp
if((cnt1+cnt2)==2*n)puts("0");
```

赛时 AC 代码（码风别学）：


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,n,a[100005];
int main(){
	scanf("%d",&t);
	while(t--){
		int ans=0,sum=0,cnt1=0,cnt2=0;scanf("%d%d",&n,&k);
		for(int i=0;i<n;i++){char tmp;cin>>tmp;if(tmp=='0') a[i]=0;else if(tmp=='1') a[i]=1;}
		for(int i=0;i<n;i++) sum+=11*a[i];
		for(int i=0;i<n;i++){if(a[i]==1)break;cnt1++;}
		for(int i=n-1;i>=0;i--){if(a[i]==1)break;cnt2++;}
		for(int i=0;i<n;i++)if(a[i]==1)ans++;
		if(ans==1){
			if(cnt2<=k)puts("1");
			else if(cnt1<=k)puts("10");
			else puts("11");
		}
		else if((cnt1+cnt2)==2*n)puts("0");
		else if((cnt1+cnt2)<=k) printf("%d\n",sum-11);
		else if(cnt2<=k) printf("%d\n",sum-10);
		else if(cnt1<=k) printf("%d\n",sum-1);
		else printf("%d\n",sum);
	}
}
```


---

## 作者：Withers (赞：4)

[题目传送门](https://codeforces.com/contest/1691/problem/C)
# 题目大意
给出一个字符串和操作数 $k$ ，每次可以交换字符串两个相邻的字符，至多 $k$ 次，求字符串最小的 $ f(s) = \sum\limits_{i=1}^{n-1} d_i$，其中 $d_i$ 为 $s_is_{i+1}$ 的十进制表示
# 思路
~~555fst了~~

这道题我们考虑每个字符对答案的贡献，记 $a[]$ 为纯数字字符串 $s[]$ 中每个字符变为 int 的结果 

记 $g(a)=f(s)= \sum\limits_{i=0}^{n-2} a_i\cdot 10+a_{i+1}$

不难发现除了 $a_0$ 和 $a_{n-1}$ 其他的都被算了 $(10+1)=11$ 次 

即 $g(a)=a_0\cdot 10+ \sum\limits_{i=1}^{n-2} a_i\cdot 11+a_n$

所以我们只要考虑首位和末尾的变动，其他的都不影响结果

因为我们要使答案最小，所以首末尾要尽量小，我们注意到把中间的1和首位的0交换，总答案会减去 1，把中间的 1 和末尾交换，总答案会减去 10

所以我没有限考虑把末尾从 0 变为 1，然后考虑把首位从 0 变为 1，因为每次交换相邻两个，所以操作次数就位这两个数字的数组下标差的绝对值就行了


# 代码
```cpp
#include<bits/stdc++.h>
#define Withers using
#define AK namespace
#define IOI std;
Withers AK IOI;
typedef long long ll;
typedef pair<int,int> pii;
int n,m,u,v,w,x,y,z,t,l,r,minn=INT_MAX,maxx=INT_MIN,len,res,pos,id,as;
int k=0;
char s[200010];
int cal(int len)
{
	int sum=0;
	for(int i=2;i<=len-1;i++) sum+=(s[i]-'0')*11;
	sum+=(s[1]-'0')*10+(s[len]-'0');
	return sum;
}//计算一个字符串的答案
void solve()
{
	scanf("%d%d%s",&n,&k,s+1);
	int sum1=0,sum2=0;
	//do something
	len=strlen(s+1);//当时没看到 n，就求了个len（汗
	if(s[len]=='0')//最后一位为0，就想办法把他和1交换，需要他们中间的字符数操作
	{
		for(int i=len-1;i>=1;i--) 
		{
			if(s[i]=='1') 
			{sum1=n-i,x=i;break;}
		}//查找可以的最少操作，就是从后面往前面找第一个“1”
		if(sum1<=k&&sum1!=0)
		{
			k-=sum1;
			swap(s[len],s[x]);
		}//减去贡献，交换这两个数
	}
	if(s[1]=='0')//和上面同理，记住要有先后顺序
	{
		for(int i=2;i<len;i++) 
		{
			if(s[i]=='1') 
			{sum2=i-1,x=i;break;}
		}
		if(sum2<=k&&sum2!=0)
		{
			k-=sum2;
			swap(s[1],s[x]);
		}
	}
	printf("%d\n",cal(len));//输出
}
void multi()
{
	cin>>t;
	while(t--)
	{
		solve();
	}
}
int main()
{
	multi();
}
// POWERED BY WITHERS
// THINK ONCE, CODE TWICE
```


---

