# Calendar Reform

## 题目描述

Reforms have started in Berland again! At this time, the Parliament is discussing the reform of the calendar. To make the lives of citizens of Berland more varied, it was decided to change the calendar. As more and more people are complaining that "the years fly by...", it was decided that starting from the next year the number of days per year will begin to grow. So the coming year will have exactly $ a $ days, the next after coming year will have $ a+1 $ days, the next one will have $ a+2 $ days and so on. This schedule is planned for the coming $ n $ years (in the $ n $ -th year the length of the year will be equal $ a+n-1 $ day).

No one has yet decided what will become of months. An MP Palevny made the following proposal.

- The calendar for each month is comfortable to be printed on a square sheet of paper. We are proposed to make the number of days in each month be the square of some integer. The number of days per month should be the same for each month of any year, but may be different for different years.
- The number of days in each year must be divisible by the number of days per month in this year. This rule ensures that the number of months in each year is an integer.
- The number of days per month for each year must be chosen so as to save the maximum amount of paper to print the calendars. In other words, the number of days per month should be as much as possible.

These rules provide an unambiguous method for choosing the number of days in each month for any given year length. For example, according to Palevny's proposition, a year that consists of 108 days will have three months, 36 days each. The year that consists of 99 days will have 11 months, 9 days each, and a year of 365 days will have 365 months, one day each.

The proposal provoked heated discussion in the community, the famous mathematician Perelmanov quickly calculated that if the proposal is supported, then in a period of $ n $ years, beginning with the year that has $ a $ days, the country will spend $ p $ sheets of paper to print a set of calendars for these years. Perelmanov's calculations take into account the fact that the set will contain one calendar for each year and each month will be printed on a separate sheet.

Repeat Perelmanov's achievement and print the required number $ p $ . You are given positive integers $ a $ and $ n $ . Perelmanov warns you that your program should not work longer than four seconds at the maximum test.

## 说明/提示

A note to the first sample test. A year of 25 days will consist of one month containing 25 days. A year of 26 days will consist of 26 months, one day each. A year of 27 days will have three months, 9 days each.

## 样例 #1

### 输入

```
25 3
```

### 输出

```
30
```

## 样例 #2

### 输入

```
50 5
```

### 输出

```
125
```

# 题解

## 作者：lightningZ (赞：2)

## 思路
首先因为我们到这去想，每一个数所能拆成 $a^2* b$ 并且保证 $b$ 最小（没错是最小，题意有误)的情况是唯一的，所以我们可以预处理一下数据范围内的所有数的 $b$ 的大小，然后直接计算答案输出。

代码里的计算方式因为 $i$ 可能等于一，所以不会漏，而且因为 $j$ 是从小往大枚举的，所以可以保证每个数 $j$ 一定最大。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,n,ans,num[10000005];
signed main()
{
	for(int i=1;i*i<=10000000;i++)//因为是开方所以不会T
	{
		for(int j=1;j*i*i<=10000000;j++) num[j*i*i]=j;
	}
	scanf("%lld%lld",&a,&n);
	for(int i=a;i<=a+n-1;i++) ans+=num[i]; 
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：XXh0919 (赞：1)

~~大大的水题~~

[自己看题去](https://www.luogu.com.cn/problem/CF172D)

我们可以直接枚举 $10^7$ 以内的完全平方数，然后枚举这些平方数的倍数（即 $a^2 \times b$ 的形式），若这个倍数没有被找到过，则我们就可以判定这一年每个月的天数就为这个完全平方数。

**AC Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,n;
long long ans;
int g[10000001];

int main(){
	ios::sync_with_stdio(0);
	for(int i=1;i*i<=1e7;++i){
		for(int j=1;i*i*j<=1e7;++j){
			g[i*i*j]=j;
		}
	}
	cin>>a>>n;
	for(int i=a;i<=a+n-1;++i)
	   ans+=g[i];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_Rainlzy (赞：1)

这道题的大致意思是：**第一年有 $a$天，第二年有 $a+1$ 天，...，第 $n$ 年有 $a+n-1$ 天。问你一年可以被分成几个月(一个月的天数必须为完全平方数)，且保证一年中每个月的天数相同，问这 $n$ 天中最多有几个月**

大致解题思路就是把 $a$ 至 $a+n-1$ 中的每个数拆分成完全平方数的形式（拆成 $a^2 \times b$）就好了。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int m,n,f[10000005];
long long ans=0;
int main(){
    cin>>m>>n;
    for(int i=m;i<=m+n-1;i++)
		f[i]=i;
    for(int i=2;i*i<=m+n-1;i++){//拆成完全平方数
        int t=i*i,sum=((m+t-1)/t)*t;
        for(int j=sum;j<=m+n-1;j+=t)
            while(f[j]%t==0)
				f[j]/=t;
    }
    for(int i=m;i<=m+n-1;i++)
		ans+=f[i];
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：zsyyyy (赞：0)

# CF172D 1500

## 题意

第一年有 $a$ 天，第二年有 $a+1$ 天，...，第 $n$ 年有 $a+n-1$ 天。问你一年可以被分成几个月(一个月的天数必须为完全平方数)，且保证一年中每个月的天数相同，问这 $n$ 年中最少有几个月。


## 思路

枚举所有 $10^7$ 以内的平方数，对于每一个平方数，枚举区间 $[a,a+n-1]$ 中所有该平方数的倍数，如果这个倍数还没有被找到过，那么这一年每个月的天数就为这个平方数（为了让月数最少，所以要使每个月的天数最多）。



## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e7+10;
int a,n,tmp,ans;
bool book[MAXN];
signed main()
{
	scanf("%lld%lld",&a,&n);
	for(int i=sqrt(a+n-1);i>=1;i--)
	{
		for(int j=((a+(i*i)-1)/(i*i))*(i*i);j<=a+n-1;j+=(i*i))
		{
			if(!book[j])  ans+=j/(i*i);
			book[j]=1;
		}
	}
	for(int i=a;i<=n;i++)
	{
		if(!book[i])  ans++;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Allanljx (赞：0)

## 思路
如果对于每一年都分解质因数的话会```TLE```。所以我们可以利用类似埃筛的思想：枚举每个平方数，然后枚举它的倍数（答案可能是这个自己除以平方数），用 $book$ 数组将答案储存。因为平方数从小到大枚举，所以不用取最小值。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,sum;
int ans[10000005];//存答案
signed main()
{
	cin>>n>>k;
	for(int i=1;i*i<=1e7;i++)//枚举平方数
	{
		for(int j=i*i;j<=1e7;j+=i*i)//枚举平方数的倍数
		{
			ans[j]=j/i/i;//分成几个月
		}
	}
	for(int i=n;i<=n+k-1;i++) sum+=ans[i];
	cout<<sum<<endl;
}
```


---

