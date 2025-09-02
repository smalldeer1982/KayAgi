# 2-3-numbers

## 题目描述

A positive integer is called a 2-3-integer, if it is equal to $ 2^{x}·3^{y} $ for some non-negative integers $ x $ and $ y $ . In other words, these integers are such integers that only have $ 2 $ and $ 3 $ among their prime divisors. For example, integers $ 1 $ , $ 6 $ , $ 9 $ , $ 16 $ and $ 108 $ — are 2-3 integers, while $ 5 $ , $ 10 $ , $ 21 $ and $ 120 $ are not.

Print the number of 2-3-integers on the given segment $ [l,r] $ , i. e. the number of sich 2-3-integers $ t $ that $ l<=t<=r $ .

## 说明/提示

In the first example the 2-3-integers are $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 6 $ , $ 8 $ and $ 9 $ .

In the second example the 2-3-integers are $ 108 $ , $ 128 $ , $ 144 $ , $ 162 $ and $ 192 $ .

## 样例 #1

### 输入

```
1 10
```

### 输出

```
7
```

## 样例 #2

### 输入

```
100 200
```

### 输出

```
5
```

## 样例 #3

### 输入

```
1 2000000000
```

### 输出

```
326
```

# 题解

## 作者：Qerucy (赞：2)

这道题直接暴力枚举肯定超时。

所以我们考虑定义两个集合 $a$ 与 $b$。

然后枚举 $2$ 的幂次，把它们装进 $a$ 中。

再枚举 $3$ 的幂次，把它们装进 $b$ 中。

最后再枚举 $a$ 与 $b$ ，把 $a$ 的每个元素与 $b$ 的每个元素相乘，累计答案即可。

代码：

```cpp
#include<cstdio>
#include<map>
#include<cstring>

using namespace std;

#define int long long//注意开long long

int two[100010];
int three[100010];
int cnt2,cnt3;
int l,r;
int ans;

signed main(){
	
	scanf("%lld%lld",&l,&r);
	for(int i=1;i<=r;i*=2){
		two[++cnt2]=i;//2的幂次
	}
	for(int i=1;i<=r;i*=3){
		three[++cnt3]=i;//3的幂次
	}
	
	for(int i=1;i<=cnt2;i++){
		for(int j=1;j<=cnt3;j++){
			if(two[i]*three[j]>=l&&two[i]*three[j]<=r){
				ans++;//累计答案
			}
		}
	}
	
	printf("%lld",ans);
	
	return 0;
}
```


---

## 作者：Ninelife_Cat (赞：1)

因为 $l$ 和 $r$ 都是 $1e9$ 级别的，直接暴力枚举会超时。

所以我们换一种思路：枚举 $2$ 和 $3$ 的幂次，判断它们相乘之后的结果是否符合题意。

注意不要忘记 $0$ 次幂。

$Code$：

```cpp
#include<bits/stdc++.h>
#define int long long//个人习惯 
using namespace std;
int l,r,sum1,sum2,ans;
int a[100001];//储存2的幂次 
int b[100001];//储存3的幂次 
signed main()
{
	a[0]=1;b[0]=1;//任何数的0次幂等于1 
	for(int i=1;;i++)
	{
		sum1++;
		a[i]=a[i-1]*2;
		if(a[i]>2e9) break;
	}//预处理2的幂次
	for(int i=1;;i++)
	{
		sum2++;
		b[i]=b[i-1]*3;
		if(b[i]>2e9) break;
	}//预处理3的幂次
	cin>>l>>r;
	for(int i=0;i<=sum1;i++)
		for(int j=0;j<=sum2;j++)
			if(a[i]*b[j]>=l&&a[i]*b[j]<=r) ans++;//枚举
	cout<<ans;
	return 0;
}

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

这个题暴力显然过不了，因为 $l,r \le 10^9$，所以我们要换一种方式暴力。

既然只要 $2^x\times 3^y$，那么就有很多 $5,7,11$ 等的倍数在里面浪费时间。（$1=2^0\times3^0$ 除外）

所以我们可以预处理出所有 $2,3$ 的幂，最后在用他们组合一下得到个数。这样复杂度就降到了 $O(\log_2{r}\times\log_3{r})$，肯定能过啦 qwq。

## AC CODE：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll read()
{
	char c;
	ll x=0;
	int f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
void write(ll x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
ll a[50],b[50];
ll l,r;
ll tot,tott;
void init()
{
	for(ll i=1;i<=r;i*=2)a[tot++]=i;
	for(ll i=1;i<=r;i*=3)b[tott++]=i;
}
int main(){
	l=read(),r=read();
	init(); 
	ll ans=0;
	for(int i=0;i<tot;i++)
	{
		for(int j=0;j<tott;j++)
		{
			if(a[i]*b[j]<=r&&a[i]*b[j]>=l)ans++;
		}
	}
	printf("%lld",ans);
	return 0;
}


```


---

## 作者：封禁用户 (赞：0)

### [传送门](https://www.luogu.com.cn/problem/CF926A)

### 思路 ：

这道题 $l$ 和 $r$ 都大于 $1e8$ ,直接枚举绝对超时。

其实只要想到可以把 $2$ 和 $3$ 的幂预处理一下就很简单了。

预处理完，直接枚举即可。

大概要算 $1000$ 次，绝对不会超时。

###   AC code

```cpp


#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r,i,j,k,x,y,s,a[100100],b[100100];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>l>>r;
	for(i=1,j=1;i<=r;i*=2,j++)a[j]=i;
	for(i=1,k=1;i<=r;i*=3,k++)b[k]=i;          //预处理 
	for(x=1;x<=j;x++)
		for(y=1;y<=k;y++)                      //枚举1~~长度 
			if(a[x]*b[y]>=l&&a[x]*b[y]<=r)s++; //判断这个数在不在l~~r的范围内
											   //是则答案加 1 
	cout<<s;		                           //输出 
	return 0;
}



```

---

## 作者：　　　吾皇 (赞：0)

~~首先我并没有在洛谷上A这道题..（蜜汁UKE），但去CF官网上可以A..也不知道为什么...~~ 好吧在发出这篇题解的一瞬间不UKE了？2333...
![](https://cdn.luogu.com.cn/upload/pic/71495.png)
### 题目分析
```
因为l、r的范围最大达到2*10^9，所以1个个枚举肯定超时，由于满足条件的数只是2^x*3^y，所以我们不妨枚举2的幂和3的幂，最多40个不到，最后把每个乘起来即可，我用了set去重..
```
#### 提醒
```
由于是枚举到r，当r过大时很可能会爆int，所以不能写 for(int i=1;i<=r;i*=2)
```
### 代码
```
#include<iostream>
#include<bitset>
#include<algorithm>
#include<set>//为什么不用万能头是因为CF官网貌似不支持
using namespace std;
long long l,r,two[1001],three[1001],to,te;//这里要开long long不然会炸
set<long long> q;//用set去重
int main(){
	cin>>l>>r;
	for(long long i=1;i<=r;i*=2) two[++to]=i;
	for(long long i=1;i<=r;i*=3) three[++te]=i;//把2的幂和3的幂分别存入
	for(int i=1;i<=to;i++)
	    for(int j=1;j<=te;j++)
	        if(two[i]*three[j]>=l&&two[i]*three[j]<=r)q.insert(two[i]*three[j]);//暴力相乘枚举..还好longlong存的下，将其存入set中去重
	cout<<q.size();//直接输出set的大小即可
}
```
```
好吧其实并不用set去重..根据 唯一xxxx ，每个数都只有唯一的一种拆分方式，所以只要ans++就可以了（也不用那么多头文件了）
```

#### 这边也可以给几组数据大家自己测一下
|  input| output |
| :----------: | :----------: |
| 1088391169 1934917632 | 16 |
|  12 1999999931 | 319
 4 134217728| 250 |
 |4251526 68024450|65


---

