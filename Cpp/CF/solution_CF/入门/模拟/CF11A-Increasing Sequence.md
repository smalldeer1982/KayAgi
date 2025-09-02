# Increasing Sequence

## 题目描述

### 题面描述

把数列中一个数加上 $d$ 算作一次操作，求最少几次操作能把这个数列变为递增数列。

## 样例 #1

### 输入

```
4 2
1 3 3 2
```

### 输出

```
3
```

# 题解

## 作者：SKTelecomT1_Faker (赞：15)

这道题一上来大家就会有一个很自然的思路：暴力模拟。

~~废话这可是一道红题...~~

先输入$n$,$s$。

对每相邻的一对数进行判断，如果后一个数比前一个数小或相等一直加$s$直到大于前一个数（注意不能是等于），用累加器$ans$（初值一定要赋为零）每加一次$ans$也加一,最后输出$ans$即可。

$Code↓$

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(void)
{
	int n,s,ans=0,a[10001];
	cin>>n>>s;
	for(register int i=1;i<=n;i++) cin>>a[i];
	for(register int i=1;i<=n-1;i++)
	{
		if(a[i]>=a[i+1])//判断是否满足
		{
			while(a[i]>=a[i+1])//如果不满足
			{
				a[i+1]+=s;
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	exit(0);
}
```


但是有一个点$TLE$了，$AC$后我看输出数据：$2000997001$

散发着恶臭的大样例...

这时一个很自然的想法是用公式递推，判断两个数的大小还是得有的，如果$a[i]$比$a[i+1]$大或相等，则直接把$(a[i]-a[i+1])/s$算出（这个值就是说后一项比前一项少了几个$s$），再向上取整并与$ans$相加，不要忘记把$a[i+1]$也加上那个值再乘上$s$，答案储存在$ans$中，最后输出$ans$即可。

$Code↓$

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(void)
{
	int n,s,ans=0,a[10001];
	cin>>n>>s;
	for(register int i=1;i<=n;i++) cin>>a[i];
	for(register int i=1;i<=n-1;i++)
	{
		if(a[i]>=a[i+1])//判断
		{
			ans+=(a[i]-a[i+1])/s+1;//套公式
			a[i+1]+=((a[i]-a[i+1])/s+1)*s;//这个值也别忘加
		}
	}
	cout<<ans<<endl;
	exit(0);
}
```

希望对大家有帮助$qwq$

---

## 作者：outis_crypt (赞：5)

这道题的思路比较简单，难点在于**容易TLE**.

思路：从第二个数开始，和前一个数比较，如果大于前一个数就不用管，否则就进行处理。

处理方法：

例如给定两个数a,b (a >= b) 一次可以加上数d. 

要加上多少次才能使得b>a ?

次数为：	**( (a - b)  /  d  +  1 )**

更新后b的值：b+(次数乘以d) 也就是 b + ( ( a - b ) / d + 1) * d

好了，到这里这道题基本上就解决了，代码如下，节省空间就不开数组了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>        
#define ll long long int
using namespace std;
int main()
{
	ll n, i, d, a, b=0, ans=0; //a指前一个数, b指后一个数,ans存次数
	cin >> n >> d;
	for (i = 0; i < n; i++)
	{
		if(i==0) 
		    cin >> a;
		else
		{
			cin >> b;
			if (b <= a)
			{
				ans += ((a - b) / d + 1);  //如果b<=a，加上要加的次数
				a = b+((a - b) / d + 1)*d;  //将b更新后的值(即b>a后b的值)赋值给a,等新的数输入
			}
			else
			{
				a = b;  //原理同上，更新
			}
			
		}
	}
	cout << ans << endl;
	return 0;
}
```





---

## 作者：览遍千秋 (赞：5)

这题一开始想到直接模拟，结果T了最后一个点。



先放一开始的代码：


```cpp
#include<iostream>
#include<cstdio>

using namespace std;
#define maxn 2007
long long n,a[maxn],ans,d;
int main()
{
    cin>>n>>d;
    for(register int i=1;i<=n;i++) cin>>a[i];
    for(register int i=2;i<=n;i++)
    {
        while(a[i]<=a[i-1])
        {
            ans++;
            a[i]+=d;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

果断想到可以直接把求加几的过程变成一个公式，就有了以下这份代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;
#define maxn 2007
long long n,a[maxn],ans,d;
int main()
{
    cin>>n>>d;
    for(register int i=1;i<=n;i++) cin>>a[i];
    for(register int i=2;i<=n;i++)
    {
        if(a[i]<=a[i-1])
        {
            ans+=(a[i-1]-a[i])/d;
            a[i]=a[i]+((a[i-1]-a[i])/d+1)*d;
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：SUNCHAOYI (赞：2)

**利用公式，O（n）算法即可**

**每次两两进行比较，若前面的数比后面的数大（a > b），则需要更新(a - b) / d + 1 次，更新完后记得把后面的数改变，改成b + ( ( a - b ) / d + 1) * d即可**

------------

## 代码如下：
```
#include <iostream>
using namespace std;
int main()
{
	int n,d,a[2005],ans = 0;
	cin>>n>>d;
	for(int i = 1;i <= n;i++) cin>>a[i];
	for(int i = 2;i <= n;i++)//从2开始 
	{
		if(a[i] <= a[i - 1])//这个数与前一个数进行比较 
        {
            ans += (a[i - 1] - a[i]) / d + 1;//利用公式 
            a[i] += ((a[i - 1] - a[i]) / d + 1) * d;//更新数字 
        }
	}
	cout<<ans<<endl; 
	return 0;
} 
```


---

## 作者：皮卡丘最萌 (赞：2)

这题由于n,m和b[i]值的特殊性，采用模拟的时间复杂度最坏会到达20亿，明显超时。

这里我们需要把时间复杂度降到O(n)，可以运用数学公式。

比如当题目中的d=3时，有两个数：

2 16

首先求差：16-2=14，
用14/3然后下取整得4，
发现2+3×4=14<16,
所以4+1得5。

#### 还有2种特殊情况：

1.比如当题目中的d=3时，有两个数：2 17

首先求差：17-2=15，
用15/3然后下取整得5，
发现2+3×5=17=17,
但此时因为序列要求严格递增，所以还得加1得6

2.有两个数：17 17

此时因为序列要求严格递增，所以累加器还得加1

看代码：
```pascal
var n,m,i,s,x:longint; a:array[0..100001] of longint;
begin
readln(n,m);
for i:=1 to n do read(a[i]);        //读入
for i:=2 to n do
  if a[i]<=a[i-1] then              //如果这个数不是递增，就累加
    begin
    x:=a[i-1]-a[i];                 //求差
    s:=s+x div m+1;                 //取整得，不管如何都+1
    a[i]:=a[i]+(x div m+1)*m;       //a[i]也要变化，否则i加1后会错
    end;
writeln(s);                         //输出累加器的值
end.
```



---

## 作者：Brian_WBY (赞：1)

### 逛了一圈题解区，发现没有Java的题解，于是本蒟蒻来氵一波

首先，拿到这道题，第一想法就是暴力模拟，放一下代码（因为是错误程序，所以没有注释）。

```java
import java.util.Scanner;
public class Main {
	public static void main(String[] args)	{
		Scanner scan=new Scanner(System.in);
		int n=scan.nextInt(),d=scan.nextInt();
		int a[]=new int[n+1];
		for (int i=1;i<=n;i++)
			a[i]=scan.nextInt();
		int ans=0;
		for (int i=2;i<=n;i++)	{
			while (a[i]<=a[i-1])	{
				ans++;
				a[i]+=d;
			}
		}
		System.out.print(ans);
	}
}
```
然后……

[TLE！！！](https://www.luogu.com.cn/record/32086879)

看来需要优化一下，我们发现如果$a_i$不大于$a_{i-1}$，那么$a_i$要加上的数就是$((a_{i-1}-a_i)/d+1)\times d$（注意要加1），所以加的次数就是$(a_{i-1}-a_i)/d+1$，那么我们利用这个结论写代码，就不会TLE了。PS:这里只是思路，具体细节见代码及代码注释

```java
import java.util.Scanner;//导入Java的Scanner模块，用于输入
public class Main {
	public static void main(String[] args)	{
		Scanner scan=new Scanner(System.in);
		int n=scan.nextInt(),d=scan.nextInt();//输入n和d
		int a[]=new int[n+1];//因为Java的数组是从0开始的，要是想从1开始，可以多开一位数组
		for (int i=1;i<=n;i++)
			a[i]=scan.nextInt();//输入n个数
		int ans=0;
		for (int i=2;i<=n;i++)	{//从第2个数开始扫一遍
			if	(a[i]<=a[i-1])	{//如果a[i]<=a[i-1]，a[i]就需要加数
				ans+=(a[i-1]-a[i])/d+1;//加上的次数，原因已经写了
				a[i]+=((a[i-1]-a[i])/d+1)*d;//加上的数
			}
		}
		System.out.print(ans);//输出答案
	}
}
```
然后我们就可以愉快的[AC](https://www.luogu.com.cn/record/32086950)了。

---

## 作者：s5_gan (赞：1)

这道题数据比较大，不能用纯模拟，否则会tle

而当中主要耗时的就是不断执行操作的过程

其实不需要循环操作，只需要列出公式计算就好

#### 这段代码和第一个题解算法基本相同，但是可以直接在输入时计算减少耗时
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,a[100005],ans=0;
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<=a[i-1]){//递增不能=
			ans+=(a[i-1]-a[i])/d+1;//精髓公式
			a[i]+=((a[i-1]-a[i])/d+1)*d;
		}
	}
	cout<<ans;
	return 0;
}
```

---

