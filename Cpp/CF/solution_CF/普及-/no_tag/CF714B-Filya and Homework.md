# Filya and Homework

## 题目描述

刺猬 Filya 今天第一次去学校，由于老师给他的作业太难所有他需要你的帮助来完成：

老师给 Filya 一个仅包含正整数的数组 $a_1, a_2, \cdots,a_n $ 首先，他选择一个整数 $x$ ，然后他将 $x$ 加到数组的某些元素上（仅有一次），再从其他一些元素中减去 $x$，（每个元素仅减一次）并留一些元素不进行操作。经过这些操作以后，他希望数组内所有的元素均相等。现在，他想知道他可不可以找到这样一个 $x$ 并进行上述操作，使数组内的每一个元素相等。

## 说明/提示

在第一个样例中，应该选择第一个元素作为 $x$，添加到第一个和第五个，然后从第二个和第三个减去。

## 样例 #1

### 输入

```
5
1 3 3 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
NO
```

# 题解

## 作者：bloodstalk (赞：2)

## 题意
给定一个长度为 $n$ 的数组。

我们可以给一些数加上一个 $x$ ，也可以减去一个 $x$ ，也可以不加也不减。

问：是否存在一个数 $x$ ，使得这个数组里各个数都相等。

## 思路
### 一道思维题
- 首先考虑，在这个数组中，相同的元素，我们一定是给它做相同的操作，否则一定不相等，根据这个思想，我们先对数组进行去重。
- 其次，我们再考虑：

  如果去重后数组中元素的个数为 $1$ ，那么不用操作就能满足；

  如果个数为 $2$ ，那么我们就可以让小的数加上 $x$ ，或者让大数减去 $x$ 保证相等;

  如果个数为 $3$ ，我们不妨设 $a,b,c$ 满足 $a < b < c$ ，那么当且仅当 $b-a=c-b$ 的时候，才能保证相等；

  如果个数大于 $3$ ，那么就一定不行了，因为 $3$ 的时候满足 $b-a=c-b$，再加上几个数那肯定加 $x$ 或者减 $x$ 之后不能相等了。
- 所以只有个数等于 $3$ 的时候需要特判一下，其余的直接 `YES` 或 `NO` 就行了。

## 代码实现
```
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define next nxt;
#define re register
#define il inline
const int N=1e5+5;
using namespace std;

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

int n;
int a[N];

int main()
{
	n = read();
	for(int i=1;i<=n;i++)
		a[i] = read();
	sort(a+1,a+n+1);/*unique函数是对有序数组就行去重，所以要先进行sort操作*/
	int nn = unique(a+1,a+n+1) - a -1;/*nn就是去重后元素的个数，别忘了-1*/
	if(nn > 3) printf("NO");/*个数大于3，直接NO*/
	else if(nn == 3)/*3的时候特判是否满足b-a == c-b*/
	{
		if(a[2] - a[1] == a[3] - a[2]) printf("YES");
		else printf("NO");
	}
	else printf("YES");/*小于等于2直接YES*/
	return 0;
}


```



---

## 作者：sycqwq (赞：2)

__思路：__

设 $tot$ 为 $a$ 数组中有多少不同的元素。

有以下几种情况：

$1°$ $tot>3$

我们可以考虑，两个不同的数 ，同时加上 $x$ 或减去 $x$，它还是不相等。

此时，我们选的一些加 $x$ 的数，如果有两个数不同，显然加 $x$ 后还是不同，减 $x$ 同理。

如果我们选择的加 $x$ 或减 $x$ 的数，没有两个不同的数，那么剩下的数还是会有两种不同的数。

所以此时答案为 `NO`。

$2°$ $tot=3$

我们设这三种不同的数为 $b$，$y$，$z$。

不妨设 $b<y<z$。

此时我们如果让 $y$ 进行加 $x$ 或者减 $x$ 操作，是不行的。

因为如果让 $y$ 加，那么就不会和 $b$ 相等，减就不会和 $z$ 相等，并且加和减的操作都只能对于一些相同的数。

所以，我们只能让 $b$ 加 $x$ 并且 $z$ 减 $x$，使得都和 $y$ 相等。

这个时候，当且仅当 $y-b=z-y$，才能为 `YES`，否则为 `NO`。

$3°$ $tot=2$

只要将一种进行加或减的操作，使得和第二种相等，就行了。

答案为 `YES`。

$4°$ $tot=1$

我们可以让 $x=0$。

答案为 `YES`。

---

## 作者：FanYongchen (赞：1)

### 题意：

在一个长度为 $n$ 的数组中，给一些数加上 $x$，一些数减去 $x$，求

是否存在一个 $x$ 的值，可以使数组中全部的数相等。

### 思路

设数组中有 $m$ 个不相同的数（例如 $6,6,7,7,8$ 中 $m=3$）

1. 如果 $m=1$，一定存在满足条件的 $x$。
 
2. 如果 $m=2$，则 $x = \lvert a-b \rvert$（$a,b$ 表数组中两个不同的数）。
 
3. 如果 $m=3$，当 $b-a=c-b$ 时， $x=b-a$ 或 $x=c-b(a,b,c$ 代表数组中3个不相同的数,且 $a<b<c)$。
 
4. 如果 $m>3$ ,则不管怎样，都不存在满足条件的 $x$ (因为如果数组中有三个数分别为 $k-x,k+x,k$ , 则后面几个数就无法通过 $\pm x$ 后得到 $k$ )。

那代码怎么写呢？

我们可以用[set](https://blog.csdn.net/love20165104027/article/details/81510406)容器来储存数组中不同的数（因为它自动排序且可以去重）。

代码如下：

```cpp
#include <iostream>
#include <set>
using namespace std;
set<int> num;//保存不同的数
int main()
{
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; i++)//输入
    {
        cin >> x;
        num.insert(x);
    }
    if (num.size() > 3) cout << "NO";//有>3个的不同的数(第4点)
    else if (num.size() < 3) cout << "YES";//有<3个的不同的数(第1,2点)
    else//第3点
    {
        int a[3] = { 0 }, i = 0;
        for (set<int>::iterator it = num.begin(); it != num.end(); it++) a[i++] = *(it);//取出set容器中的每个数(set自动排序且去重)
        if (a[1] - a[0] == a[2] - a[1]) cout << "YES";//b-a==c-b时,满足
        else cout << "NO";
    }
    return 0;
}
```


---

## 作者：tanghg (赞：0)

CF 的题通常是一些比较好玩的思维题，这道也不例外。

### 思路：

看到数据范围就知道不可以直接暴力去试 $x$。

如果要把数组内元素变得相等，那不妨可以想到只要判断去重过的数组即可。

这道题目要分三种情况，我们不妨设 $num$ 为数组去重过的元素个数

#### 当 $num\leq 2$ 时:
我们把不同的其他元素都加上一个数即可，一定成立。

#### 当 $num=3$ 时，这是最复杂的情况:

先说结论，只有三个数成等差数列时才成立。
为什么呢？

设三个元素为 $a,b,c$ 且 $a<b<c$，根据题意，只有把 $b$ 留住且有一个数 $x$ 同时满足 $a+x=b$ 和 $c-x=b$ 时才可成立，也就是一个等差数列。

#### 最后一种，$num>3$:

这种情况一定不符合，因为不可能有 $x$ 让不同的 $3$ 个数以上加加减减一样。

所以我们只需要开一个不定元素数组去存去重元素即可。
但需要稍微优化一下，如果每次都在去重后在判断你会 TLE on 11，只需要加一句在循环内判断是否不同元素已经超过 $3$ 了即可。

目前这个代码是除匿名用户外的最优解，大家可放心食用。

[代码在这里](https://www.luogu.com.cn/paste/ln34wq9x)

---

## 作者：abensyl (赞：0)

## [原题传送门](https://www.luogu.com.cn/problem/CF714B)

## 思路

STL 库中的 set 可以帮助我们自动去除重复元素并且自动排序。

注明：$n$ 为不重复元素的个数，$x$ 为我们需要找的整数。

- 如果 $n=1$，令 $x=0$ 即可，故一定存在满足条件的 $x$。

- 如果 $n=2$，则 $ x = \left| a-b \right|$，故同样可以得到答案。

- 如果 $n=3$，当 $ b-a=c-b $ 时， $ x=b-a \iff x = c - b $ ( $a$,$b$,$c$ 为数组中 $3$ 个不相同的数,并且 $a\leq b \leq c$)，通过检验 $a+c=b \times 2$ 的真假性即可得到结果。

- 如果 $m \geq 4$ ，一定不存在满足条件的 $x$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	set<int> k;
	set<int>::iterator it;
	int n,a[4],z;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>z;
		k.insert(z);
	}
	int len=k.size(); //元素个数为1，直接输出 yes
	if(len<=2) puts("YES"); //元素个数为2，直接输出 yes
	else if(len>=4) puts("NO"); //元素个数大于等于4，直接输出 no
	else { //元素个数等于3
		int i=0;
		for(it=k.begin();it!=k.end();it++,++i) a[i]=*it;
		if(a[0]+a[2]==a[1]*2) { //判断
			puts("YES");
			return 0;
		}
		puts("NO");
	}
	return 0;
}
```


---

## 作者：xgwpp6710 (赞：0)

先来简化一下题目。

如果所有数都相同，显然可以。	

如果只有两种不同的数 $a,b$ ，则 $x=|a-b|$ 就行了。

如果有不少于四种数显然不行。

如果有三种数 $a,b,c$ （其中 $a<b<c$ ），则 $a+c=2b$ 才行。

接下来，我们想一下用什么算法。

`set`可以帮我们去重并且从小到大排序，这样方便我们找出一共有多少种不同的数，并且在有 $3$ 个不同的数的时候方便找出它们的大小。

于是，代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	set<int> s;
	set<int>::iterator it;//set，其中size()求出容器大小，也就是不同的数数量
	int n,a[4],in,j=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>in;
		s.insert(in);
	}
	if(s.size()<=2) cout<<"YES";
	else if(s.size()>=4) cout<<"NO";
	else
	{
		for(it=s.begin();it!=s.end();it++,j++) a[j]=*it;//存储这三种数
		if(a[0]+a[2]==a[1]*2) cout<<"YES";
		else cout<<"NO";
	}
	return 0;
}
```
[我的AC记录](/record/34795587)，请放心食用！

---

## 作者：lu_run_ting (赞：0)

题意：    

我们有一个序列，需要在其中选一个数$x$，然后一部分书加上$x$，一部分减去$x$，一部分不动。求能否把这个序列的所有元素都相等。

分析：   

数的种类，例如序列：1 2 3 3 3，就有三种数

- 当数的种类为1时，那么不用加也不用减，因为本来就是全部都一样。

- 当数的种类为2时，只要选两种数的差，给其中一种数加上，那么两种数就变成一种数了。

- 当数的种类为3时，只有形如$x-a$，$x$，$x+a$的样子的，才能成为一种数，因为这样就可以选$a$这个数，然后就可以算出来，也就是$a$，$b$，$c$，形成了一个等差数列。

- 当整个数列中的种类大于3的时候，我们不可能把它变成一个数。为什么呢？因为假如有4种数，一个数为$a$，那么一种数为$a+x$，一种数为$a-x$，而第四种数怎么操作都不可能算出$a$。

那么问题来了，如何才能算出数的种类呢？我的第一反应是桶，可是如果要开这样一个$10^9$的数组就会ME到吐血。所以说我开了一个vector数组，每遇到一种新数，就往里面压入一个数。最后用size()函数计算一下就可以了

蒟蒻的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,flag;
vector<int> a;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x; flag=1;
		for(int j=0;j<a.size();j++) 
			if(x==a[j]){
				flag=0;
				break;
			}
		if(flag==1) a.push_back(x);
		if(a.size()>3){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	if(a.size()<=2) cout<<"YES"<<endl;
	else if(a[0]+a[1]+a[2]==a[0]*3||a[0]+a[1]+a[2]==a[1]*3||a[0]+a[1]+a[2]==a[2]*3) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0; 
} 
```

---

## 作者：ricky_lin (赞：0)

# 这道题要考虑多个方面：
### 1.最多只能有3个不同的数
### 2.如果有3个不同的数则第一大的数减第二大的数等于第二大的数减第三大的数才能满足
### 3.如果有2个不同的数则一定能满足
#### 下面是代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[100010]; int b[3],to;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		bool k=0;
		scanf("%d",&a[i]);
		for(int j=0;j<to;j++)
		{
			if(b[j]==a[i]) {
				k=1;
				break;
			}
		}
		if(k==0) {if(to==3) {printf("NO");return 0;}b[to]=a[i];to++;}
	}
	sort(b,b+3);
	if(to==3){
		if(b[1]-b[0]==b[2]-b[1]) printf("YES");
		else printf("NO");
	}
	else
	{
		printf("YES");
	} 
 	return 0;
} 
```
## 总结：只要用代码实现这三个方面即可

---

