# TL

## 题目描述

Valera wanted to prepare a Codesecrof round. He's already got one problem and he wants to set a time limit (TL) on it.

Valera has written $ n $ correct solutions. For each correct solution, he knows its running time (in seconds). Valera has also wrote $ m $ wrong solutions and for each wrong solution he knows its running time (in seconds).

Let's suppose that Valera will set $ v $ seconds TL in the problem. Then we can say that a solution passes the system testing if its running time is at most $ v $ seconds. We can also say that a solution passes the system testing with some "extra" time if for its running time, $ a $ seconds, an inequality $ 2a<=v $ holds.

As a result, Valera decided to set $ v $ seconds TL, that the following conditions are met:

1. $ v $ is a positive integer;
2. all correct solutions pass the system testing;
3. at least one correct solution passes the system testing with some "extra" time;
4. all wrong solutions do not pass the system testing;
5. value $ v $ is minimum among all TLs, for which points $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ hold.

Help Valera and find the most suitable TL or else state that such TL doesn't exist.

## 样例 #1

### 输入

```
3 6
4 5 2
8 9 6 10 7 11
```

### 输出

```
5```

## 样例 #2

### 输入

```
3 1
3 4 5
6
```

### 输出

```
-1
```

# 题解

## 作者：封禁用户 (赞：3)

题目传送>>[CF350A](https://www.luogu.com.cn/problem/CF350A)  
### 题意简述：  
出题人出了一道题，她想设置一个时限 v，使得她所写的 n 个 AC 程序能 AC 和 m 个 TLE 程序会 TLE（这些程序用时已知），并且至少有一个 AC 程序的用时小于等于 $\frac{v}{2}$。求最小 v，如不能求得即输出"$-1$"。  
### 题目分析：  
对于此题，我们可以先判断其无解的情况，如果无解即直接输出“$-1$”，否则再求 v 的最小值。  
判断其是否有解，我们可以根据这个时限 v 会使得她所写的 n 个 AC 程序能 AC 和 m 个 TLE 程序会 TLE，如果她能 AC 的程序的最大用时却大于会 TLE 的程序的最小用时，那么绝对无解。除此之外，如果她能 AC 的程序的最小用时的两倍大于等于会 TLE 的程序的最小用时，那么就不能使她所写的 n 个能 AC 的程序至少有一个小于等于 $\frac{v}{2}$，此时也无解。  
如果有解，那么我们来找其最小值。题目要求至少有一个 AC 程序的用时小于等于 $\frac{v}{2}$，现要求 v 的最小值，那么我们就使其 AC 程序中用时最小的程序满足即可，我们将其最小用时乘于 $2$ 便得到可能是最小 v 的值，那么为什么是可能是呢？因为如果其最小用时的 $2$ 倍小于她能 AC 的程序的最大用时，那么就会使得她的一些原本能 AC 的程序现在不能AC，所以我们要对其最小用时的 $2$ 倍和她能 AC 的程序的最大用时进行比较，最大的那个才是最终结果。  
### Code:  
```cpp
#include <iostream>
#include<cstdio>
using namespace std;
int a[101],b[101];   //开数组存她能AC的程序的用时和会TLE的程序的用时
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int n,m;   //定义她所写的能AC的程序的数量和会TLE的程序的数量
	int acmin=100000000,acmax=-100000000,tlemin=100000000;   //定义其能AC的程序的最小用时和最大用时，会TLE的程序的最小用时，并且进行初始化，即最小值设得很大，最大值设得很小
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(acmin>a[i])   //找能AC的程序的最小用时
		{
			acmin=a[i];
		}
		if(acmax<a[i])   //找能AC的程序的最大用时
		{
			acmax=a[i];
		}
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
		if(tlemin>b[i])   //找会TLE的程序的最小用时
		{
			tlemin=b[i];
		}
	}
	if(acmax>=tlemin)   //不满足要求，无解
	{
		cout<<"-1";
	}
	else
	{
		if(2*acmin>=tlemin)   //不满足要求，无解
		{
			cout<<"-1";
		}
		else
		{
			cout<<max(acmin*2,acmax);   //比较其能AC的程序的最小用时的两倍和能AC的程序的最大用时，大值即最终结果
		}
	}
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）：  
![](https://cdn.luogu.com.cn/upload/image_hosting/s9nnmgbl.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：orange166 (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF350A)  
## 思路：  
甚至都不用开数组，求最大最小值即可。  

可以理解为：  
要求只有正解AC，且正解中的最优解运行时间不超过时间限制的 $\frac{1}{2}$ 。求时间限制的最小值。    

于是只需求出正解中的最优解 $min(AC_i)$ 、最劣解运行时间 $max(AC_i)$ ，错解中运行时间最短的解 $min(TLE_i)$ 即可。  

时间限制无解： $min(TLE_i) \le max(AC_i) \space || \space min(TLE_i) \le min(AC_i)*2$  
  
有解时，时间限制最小值为 $max( \space min(AC_i)*2, \space max(AC_i) \space)$  
~~（貌似我扫一遍求最小值还更快？）~~
## 代码：  
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int q=0x7fffffff;
int a,b,maxn=-1,minn=q,minn2=q,tmp,s; // 初始化minn,maxn值 

int main(){
	scanf("%d%d",&a,&b);
	for(register int i=1; i<=a; i++){ // AC部分,register为常数优化,可以忽略
		scanf("%d",&tmp);
		minn=min(tmp,minn);
		maxn=max(tmp,maxn);
	}
	for(register int i=1; i<=b; i++){
		scanf("%d",&tmp);
		minn2=min(tmp,minn2); // TLE部分,不需要求max(TLE_i)
	}
	if(minn2<=maxn || minn2<=minn*2){ // 无解
		printf("-1");
		return 0;
	}
	s=max(minn*2, maxn);  // 有解
	printf("%d",s);
//	for(s=maxn; s<minn2; s++) // 扫一遍
//		if(s>=minn*2)break;
//	printf("%d",s);
	return 0;
}
```
[扫一遍AC](https://www.luogu.com.cn/record/43441179)  
[正常版AC](https://www.luogu.com.cn/record/43441935)

---

## 作者：西卡洛斯 (赞：1)

# 题解 CF350A TL

~~Valera 翻译成珂朵莉可还行（~~

首先用两个数组$ a [ i ] $和$ b [ i ] $分别存$AC$的程序和$TLE$的程序。

接下来分析条件：

- 通过条件`所有正解都可以AC` 可知，$v>=a [ i ]_{max}$

- 通过条件`至少有一个正解可以获得奖励时间`可知，$v<2*b [ i ]_{min}$

- 通过条件`所有会TLE的程序都不会AC` 可知，$v_{min}=max(a[ i ]_{max},2*a[i]_{min})$

所以只要分别对$a[ i ]$和$b[ i ]$进行排序，得到最大值和最小值即可。

上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int a[1010],b[1010];
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	for(int i=a[n];i<b[1];i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[j]<=i/2) {printf("%d\n",i);return 0;}
		}
	}
	printf("-1\n"); 
	return 0;
}
```


---

## 作者：happybob (赞：1)

这么个题，数组是必须的，因为输入进去后重点要判断

“如果一个解的运行时间不超过2分之v 秒，则它就可以AC并且得到一些奖励时间。”


其实这五个条件，说实话只有一个

```
v为正整数
所有正解都可以AC
至少有一个正解可以获得奖励时间
所有会TLE的程序都不会AC
v是满足上述条件中的最小值
```
正整数这不用说了

第二全部正解AC所以我们可以存数组找最大值

第三这个奖励时间才是真正要判断的

第四会TLE全部不AC所以找到TLE的最小值

第五可以写一个for，从AC最大时间到TLE最小时间，这样既可以满足最小的v，也可以满足2,4条件，不用从1全枚举，避免了TLE的可能。

所以来看看AC代码吧
```cpp
#include <iostream>
using namespace std;

int arr[105], arr2[105];

int main()
{
    int n, m, max = -1, min = 101;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        max = arr[i] > max ? arr[i] : max;
    }
    for(int i = 1; i <= m; i++)
    {
        cin >> arr2[i];
        min = arr2[i] < min ? arr2[i] : min;
    }
    for(int x = max; x < min; x++)//注意<不是<=，为此我还WA了几次
    {
        for(int j = 1; j <= n; j++)
        {
            if(arr[j] <= x / 2)
            {
                cout << x << endl;
                return 0;
            }
        }
    }
    cout << "-1\n";
    return 0;
}
```



---

## 作者：Colead (赞：0)

简单的数组处理。

我们发现，对于题目所求的 $v$ 有三个限定范围。

**两个下限（可取等号）**：最短用时正解时间的两倍和最长用时正解。

**一个上限（不可取等号）**：超时程序中最短时间

所以就看三个不等式有没有交集，没有就输出 $-1$ ，有的话就输出解集里的最小整数。因为解集的下限是可以取到等号的，所以不存在有解集但没有整数解的情况。

```
#include<bits/stdc++.h>
using namespace std;
long long n,m,maxn=0,minn=99999999,mina=99999999;
long long a[1005],b[1005]={};
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>maxn)maxn=a[i];
		if(a[i]<mina)mina=a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
		if(b[i]<minn)minn=b[i];
	}
	if(mina*2>=minn||maxn>=minn)
	{
		cout<<"-1"<<endl;
		return 0;
	}
	else
	{
		cout<<max(maxn,mina*2)<<endl;
	}
	return 0;
}
```

应该很清楚了吧。如果不懂欢迎评论或私信。

---

## 作者：rfsfreffr (赞：0)

先了解一下v的条件:


1. v为正整数

2. 所有正解都可以AC

3. 至少有一个正解可以获得奖励时间

4. 所有会TLE的程序都不会AC

5. v是满足上述条件中的最小值

对于条件1,可以基本不用处理，将变量设为整数即可。

对于条件2,即$max(AC_i)<=v$

对于条件3,即$min(AC_i)*2<=v$

对于条件4,即$min(TLE_i)>v$

对于条件5，$v_{min}=max(max(AC_i),min(AC_i)*2)$

所以只要记录出最大和最小的AC代码时间和TLE时间即可。

# 代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int ac[1000001];
int tle[1000001];
int ac_fast=1e9,ac_last,tle_fast=1e9;
int main(){
	cin>>n>>m;
	for(int i=1; i<=n; i++) scanf("%d",&ac[i]);
	for(int j=1; j<=m; j++) scanf("%d",&tle[j]);
	for(int i=1; i<=n; i++){
		ac_fast=min(ac_fast,ac[i]);
		ac_last=max(ac_last,ac[i]);
	}
	for(int i=1; i<=m; i++){
		tle_fast=min(tle_fast,tle[i]);
	}
	ac_fast*=2;//乘二
	if(tle_fast<=ac_fast||tle_fast<=ac_last)//AC代码时间比TLE最快的代码快，果断输出-1 cout<<-1<<endl;
	else cout<<max(ac_fast,ac_last)<<endl;//否则输出max(max(AC_i),min(AC_i)*2)
	return 0;
}
```

---

