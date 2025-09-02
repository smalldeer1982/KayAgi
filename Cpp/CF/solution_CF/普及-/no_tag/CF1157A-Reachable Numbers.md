# Reachable Numbers

## 题目描述

有一个函数$f(x)$，效果是将$x+1$后，去掉末尾所有的$0$，例如：

$f(599)=6$，因为$599+1=600→60→6$

$f(7)=8$，因为$7+1=8$

$f(9)=1$，因为$9+1=10→1$

$f(10099)=101$，因为$10099+1=10100→1010→101$

我们可以多次进行函数$f(x)$的运算，从而让一个数$x$转换为另一个数，例如$10098$可以转换为$102$，因为$f(f(f(10098)))=f(f(10099))=f(101)=102$。

你需要做的是给你一个数$n$，求出$n$经过多次函数$f(x)$的计算，能转换为几个不同的数（包括自身）？

## 样例 #1

### 输入

```
1098
```

### 输出

```
20
```

## 样例 #2

### 输入

```
10
```

### 输出

```
19
```

# 题解

## 作者：Kisaragi_77 (赞：4)

# CF1157A Reachable Numbers 题解

濒临退役的小蒟蒻第一次发题解,所以只好选择这种水题

题意大意是把一个数不断++,去除后面的所有0,统计有多少数可以被表示出来,$N<=10^9$

### 分析:

直接模拟题意即可,每次把这个数++,不断除以10去掉后导0.

因为最多加9次一定会出现10,所以最坏情况下复杂度与$lg N$ 同级

那么,什么时候停止呢

当某一个数字被重复统计时,一定会绕回去

例:

```2->3->4->5->6->7->8->9->1->2.....```

1e9开vis数组肯定是开不下的,所以我们需要用个数据结构,set,map,手写哈希表都是可以的

下面是我提交是的代码,数据很水,我就没有优化了(其实应该有很多细节的)复杂度约为$O(lgN*log(lgN))$

~~口胡的反正log同级就对了~~

```cpp
#include<cstdio>
#include<set>
#include<iostream>
using namespace std;
set <int> s;
int main(){
	int x;	cin >>x;
	s.insert(x);
	for(;;){
		x ++;	while(x%10==0) x /=10; //去掉后导0
		int sz =s.size();
		s.insert(x);
		if(sz==s.size()) {printf("%d",s.size());return 0;}
	}
}
```





---

## 作者：Zekrom (赞：2)

### 题目大意：  
对一个数+1后去0  
如1999(->2000)->2    
求能变换的数的个数  
显然在进位以后的数将比原数小  
所以可以直接循环  
### 注意 ：  
循环结束的条件：n>=10(10以内的数都能取到）  
上代码  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
int main()
{
	int n=read(),cnt=0;
	while(n>=10){
		//printf("%d ",n);		
		n=n+1;
		while(n%10==0)n/=10;
		cnt++;
	}
	cnt+=9;
	//printf("\n");
	printf("%d\n",cnt);
	return 0;
}

```


---

## 作者：water_tomato (赞：1)

作为一道 CF 的 A 题，私以为现有的题解都把这题做麻烦了或是太过于暴力了，决定提供一种其他的解法。

[题目链接](https://www.luogu.com.cn/problem/CF1157A) 题意非常明朗，不再赘述。

## 解析

作为 A 题，显然这题是可以通过数学方法解决的，因此虽然数据范围的确可以暴力过，但是我第一个想到的并不是暴力。

我们首先考虑到，如果只有一位数，显然是一定会产生 $1 \sim 9$ 这 $9$ 种情况的，那接下来每一位呢？我们从最后一位开始倒退，考虑其能执行几次运算，也就是能产生几个不同的数，我们发现，第 $i$ 位数能支持的运算次数一定为 $9-a_i$ 次（ $a_i$ 为第 $i$ 位上的数字）。因此，我们只需要把运算次数和，即除了第一位以外能够产生的不同数的数目求出来，再加上第一位的 $9$ 种情况以及该数本身的一种情况合计 $10$ 种，就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int num,a[15],cnt,ans=10;//第一位和该数本身的贡献为 10
int main(){
	scanf("%d",&num);
	while(num){
		a[++cnt]=num%10;
		num/=10;
	}
	if(cnt==1) ans--;//若该数只有一位，该数本身和第一位的贡献算重了，减去即可 
	for(int i=1;i<cnt;i++)
		ans+=9-a[i];//除了第一位以外每一位的贡献 
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：AC_Dolphin (赞：1)

div3的题，你信吗。。。

我们先把f(x)这个函数的计算规则搞出来，然后不断n=f(n);把每次f(n)的结果放到map里面，如果当前f(n)的值已经在map里面就break

~~恶意评分吧~~

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN=1e6+10;
ll cnt,n;
map<int,bool> m;
inline int read(){
    int f=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
int f(int x){
    x++;
    if(x%10!=0) return x;
    while(x%10==0){
        x/=10;
    }
    return x;
}
int main(){
    cin>>n;
    while(m[n]==false){
        n=f(n);
        m[n]=true;
        cnt++;
    }
    cout<<cnt<<endl;
    return 0;
}
```

---

## 作者：liangbob (赞：0)

### CF1157A 题解

#### 思路分析

简单周期模拟题。

首先，题目要求我们求出操作过程中会出现多少个不同的数。那么显然这个操作会有周期。

于是我们开始找周期。由于这个操作只关于被操作数本身，不依赖其他的数，所以只要出现一个前面出现过的数，就算找到周期了。

然后就很简单了，每次变化并记录一个数，出现一个前面出现过的数就停止。最后统计输出即可。

现在唯一的问题就是记录出现过的数。由于数据范围较大，不方便用布尔数组存储。所以考虑使用数据结构 map 来存储。

操作本身很简单，判断是否能被十整除，能整除就一直除，除到不能除为止。

接下来按步骤实现就可以了。

#### 关键代码

```cpp
map <int, bool> mp; //记录出现过的数的数据结构

int main()
{
	int n;
	cin >> n;
	int cnt = 0; //记录答案
	while(mp[n] == false) //如果没出现过访问过的数
	{
		cnt++;
		mp[n] = true; //记录
		n++;
		while(n % 10 == 0) n /= 10; // 加一后操作
	}
	cout << cnt << endl;
	return 0;
}
```



---

## 作者：tbdsh (赞：0)


# 题意
[题目传送门](https://www.luogu.com.cn/problem/CF1157A)

输入一个数 $x$，给这个数持续 $+1$，如果 $x$ 末尾有 $0$，那么就将 $0$ 去掉，最后输出会转换成多少个数。

**特别注意**，最开始输入的那个数也要计算在答案内。

# 分析
用 $n$ 数组存储从 $1$ 到 $9$ 数字出现的次数，用 `while` 不断执行 $f(x)$ 的操作，同时判断 $1$ 到 $9$ 的数字是否还有没出现的。有就继续循环，否则退出循环，输出答案。
# Code
```cpp
#include<iostream>

using namespace std;
long long m, ans, n[11];//定义： m 是输入的数， ans 是答案，数组 n 是判断 1 ~ 9 每个数出现的次数。
int main(){
  cin >> m;
  ans++;//因为出现过的数包括输入的数本身，所以提前将答案++。
  if (m < 10){
    n[m]++;//特判：如果 m 小于 10 的话先在退出循环条件中m的位置++；
  }
  while(n[1] == 0 || n[2] == 0 || n[3] == 0 || n[4] == 0 || n[5] == 0 || n[6] == 0 || n[7] == 0 || n[8] == 0 || n[9] == 0){//循环：当 1 ~ 9 中有一个数没有出现过就持续循环。
    m++;//每次循环 m++。
    ans++;//同时答案也++。
    while (m % 10 == 0){
      m /= 10;//去后导 0。  
    }
    if (m < 10){
      n[m]++;//m 小于 10 的话在数组 n 中 m 出现的次数++。
    }
  }
  cout << ans;//输出答案
  return 0;
}

```


---

## 作者：Frozencode (赞：0)

题意：给你一个操作和一个数，问你能对这个数不断操作后得到多少个不同的数，思路见代码注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=1e9+7;
const ll INF=2147483647;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
	{
		write(x/10);
	}
	putchar(x%10+'0');
}
ll n,cnt;
int main()
{
	cin>>n;
	if(n<10)//特判下一位的情况，只有一位答案一定是9。
	{
		cout<<9;
		return 0;
	}
	while(n>=10)
	{
		if(n%10)//这位不是0那么就有10-(n%10)个数可以被得到。
		{
			cnt+=10-(n%10);
			n+=10-(n%10);//统计完得到的数后要把n加上n%10使得可以进行下一位的统计。
		}
		else
		{
			while(n%10==0)n=n/10;//否则按操作要求不断去掉末位的0
		}
	}
	cout<<cnt+9;
	return 0;
}
```


---

