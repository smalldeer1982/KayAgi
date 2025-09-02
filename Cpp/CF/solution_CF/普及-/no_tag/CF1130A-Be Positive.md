# Be Positive

## 题目描述

有一个包含nnn个整数的数组,你需要找到一个非零整数$d(-10^3\leq d \leq 10^3)$，使数组中的每一个数组除以d的商中至少有一半为正数(即至少有$\frac{n}{2}$个)注意:"正数"只要求商大于0,不要求一定是整数。如果有多个$d$满足条件，输出其中的任意一个,如果没有这样的$d$则输出$0$。

## 样例 #1

### 输入

```
5
10 0 -7 2 6```

### 输出

```
4```

## 样例 #2

### 输入

```
7
0 0 1 -1 0 0 2
```

### 输出

```
0```

# 题解

## 作者：pxy1118 (赞：4)

```cpp
	#include <bits/stdc++.h>
	using namespace std;
	int main(){
		int n,t,z=0,l=0;
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>t;
			if(t==0)l++;
			else if(t>0)z++;
		}
		int x=ceil(double(n/2.0));
		if(z>=x)cout<<"1\n";
		else if(n-z-l>=x)cout<<"-1\n";
		else cout<<"0\n";
		return 0;
	}
```

---

## 作者：billzd (赞：1)

## 题目

有一个包含 $n$ 个数的数组，要求找一个非零整数，使得该数组有至少一半的数除以它可以得到一个正数。
 
只需记录数组中正负数的个数，再进行判断，正数多就输 $1$ ，负数多输出 $-1$ ,否则就输出 $0$ 。

**代码如下**


------------

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a[10000];
int main(){
	ios::sync_with_stdio(false);
	int n,x,m,z=0,f=0;
	cin>>n;
	m=n;
	n=ceil(n/2.0);
	while(m--){
		cin>>x;
		if(x>0) z++;
		else if(x<0) f++;
	}
	if(z>=n) cout<<1;
	else if(f>=n) cout<<-1;
	else cout<<0;
	return 0;
}
```


---

## 作者：WsW_ (赞：0)

首先要讲的是，正数除以正数为正数，负数除以负数为正数，$0$ 除任何数都为 $0$。所以，只有符号与结果有关，做此题我们只需要用到 $-1$、$0$、$1$ 即可。
## 解法一：  
统计正数和零的个数，用 $n$ 减去正数和零的个数就可以得到负数的个数。然后看数列中正数和负数有没有到总数的一半，如果正数个数大于等于总数一半输出 $1$，负数与正数思路相同，只不过输出 $-1$。  
如果正数和负数的个数都没到总数一半，那就输出 $0$。
```
#include<bits/stdc++.h>
using namespace std;
int n,a;
int zero,sum;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		if(!a)zero++;//统计0的个数
		if(a>0)sum++;//统计正数的个数
	}
	if(sum>=n-sum)return !printf("1");//如果正数大于等于一半，输出1
	else if(n-sum-zero>=sum+zero)return !printf("-1");//负数同上
	printf("0");//否则输出0
	return 0;
}
```
## 解法二：  
因为开始说了，答案只有可能是 $-1$、$0$、$1$，所以直接暴力检查这 $-1$、$1$ 可不可以即可。  
```
#include<bits/stdc++.h>
using namespace std;
int n,a[1004];
int zero,sum;
bool check(int x){//检查
	int s=0;
	for(int i=1;i<=n;i++){
		if(double(a[i])/double(x)>0)s++;//如果大于零就可以
	}
	return (s>=n-s);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	if(check(1))return !printf("1");//依次检查1、-1
	if(check(-1))return !printf("-1");
	return !printf("0");//如果两个都不行就输出0
}
```

---

## 作者：luozhichen (赞：0)

 **题意：**
题目看起来要暴力但是还有一种更简单的方法。正数大于一半就输出 $1$ ，负数大于一半就输出 $-1$ ，否则就输出 $0$ 。为什么正数大于一半输出 $1$ 呢？其实任何数除以 $1$ 都等于其本身，所以输出 $1$ ，除以 $-1$ 等于它的相反数，所以负数多些时就输出 $-1$ ，否则输出 $0$ 。
 
**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[10001];
int zs,fs,l;
int yb;
int main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
		if(a[i] > 0){
			zs++;
		}else if(a[i] < 0){
			fs++;
		}else if(a[i] == 0){
			l++;
		}
	}
	yb = (n - 1) / 2 + 1;	
	if(yb <= zs){
		cout << "1";
	}else if(yb <= fs){
		cout << "-1";
	}else{
		cout << "0";
	}
	return 0;
}

```


---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的数组 $a_1,a_2,a_3,...,a_n$，试找出一个数 $d$，使得数组中的每个数除以 $d$ 得到的 $n$ 个结果中至少有 $\dfrac{n}{2}$ 个正数，输出任意一个 $d$ 均可，或者没有这样的 $d$。

**数据范围：$1\leqslant n\leqslant 100,-10^3\leqslant a_i\leqslant 10^3$。**
## Solution
先统计一下这里面有多少个正数和多少个负数。如果正数和负数的数量都没有到 $\left\lceil\dfrac{n}{2}\right\rceil$ 的话就不存在这样的 $d$，否则看正数和负数的数量哪个有 $\left\lceil\dfrac{n}{2}\right\rceil$，如果是正数多除数就应该是正数，否则就应该是负数，这里随便输出什么都行能得到答案就好，我的代码中正数多输出的是 $1$，负数多输出的是 $-1$。
## Code
```cpp
int n, a[100007], pos, neg; 

int main() {
	getint(n);
	_for(i, 1, n) {
		getint(a[i]);
		pos += (a[i] > 0), neg += (a[i] < 0);
	}
	if(pos >= (n % 2 ? n / 2 + 1 : n / 2))	printf("1");
	else if(neg >= (n % 2 ? n / 2 + 1 : n / 2))	printf("-1");
	else	printf("0");
	return 0;
}
```

---

## 作者：WKAHPM (赞：0)

一看数据范围：

$-10^{3}\le d \le 10^{3}$，$1 \le n \le 100$

这是让我们~~打表~~枚举的节奏啊（雾）

思路很简单，枚举每一个$d$，判断是否满足条件即可

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[110];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=-1000;i<=1000;i++)
    {
    	if(i==0) continue;//d不能为0
    	int sum=0;
    	for(int j=1;j<=n;j++)
    	{
    		if(a[j]*i>0) sum++;//a[i]/d与a[i]*d同正负
		}
		if(2*sum>=n) //满足条件
		{
			cout<<i;
			return 0;
		}
	}
	cout<<0;
	return 0;
}

```


---

## 作者：FP·荷兰猪 (赞：0)

> 题意：给你n个数，找到一个数d，使得每个数除以d后正数的个数不比负数的个数少，输出任意解。

解法：我们不难可以发现，如果这n个数中正数的个数大于等于n/2，则d=1；如果这n个数中正数的个数大于等于n/2，否则d=0;否则无解，输出0。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	int n;
	cin>>n;
	int a[n+1],i,pos,neg;//pos表示正数的个数，neg表示负数的个数
	pos=neg=0;
	for (i=1;i<=n;i++)
	{
		cin>>a[i];
		if (a[i]>0)
		{
			pos++;
		}
		if (a[i]<0)
		{
			neg++;
		}
	}
	if ((pos<n*1.0/2) && (neg<n*1.0/2))//如果正数和负数的个数均不到n/2，即无解，输出0
	{
		cout<<0<<endl;
	}
	else if (pos<neg)
	{
		cout<<-1<<endl;//负数多，则把所有数除以-1，负数就变成了正数
	}
	else
	{
		cout<<1<<endl;//同理
	}
	return 0;
}
```

---

## 作者：wuwenjiong (赞：0)

## 题意：
有一个包含 $n$ 个数的数组，要求找一个非零整数，使得该数组有至少一半的数除以它可以得到一个正数。
### 思路：
众所周知，两个非零的同号实数相除，所得的一定是正数。于是，可以分别找出该数组中正数，负数的个数。然后可分为三种情况：
1. 正数的个数大于或等于 $n$ 的一半。此时任意输出一个正数。
1. 负数的个数大于或等于 $n$ 的一半。此时任意输出一个负数。
1. 不满足上面两种情况。此时按照题意输出 $0$ 。

最后，代码实现如下：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int x,y;
int main(){
	int n,a,k;
	cin>>n;
	k=(n-1)/2+1;
	while(n--){
		cin>>a;
		if(a>0)
			x++;
		if(a<0)
			y++;
	}
	if(x>=k)
		cout<<1;
	else if(y>=k)
		cout<<-1;
	else
		cout<<0;
	return 0;
}
```
谢谢！！！

---

