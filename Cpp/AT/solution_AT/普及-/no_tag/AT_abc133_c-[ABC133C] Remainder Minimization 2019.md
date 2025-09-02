# [ABC133C] Remainder Minimization 2019

## 题目描述

给出非负整数 $L$ 和 $R$，在这个区间里选择两个整数 $i$ 和 $j$ 满足 $L\le i < j\le R$。求 $(i\times j)\mod 2019$ 的最小值。

## 说明/提示

$ 0 \le L < R \le 2 \times 10^9$

## 样例 #1

### 输入

```
2020 2040```

### 输出

```
2```

## 样例 #2

### 输入

```
4 5```

### 输出

```
20```

# 题解

## 作者：_JF_ (赞：3)

### AT4810 [ABC133C] Remainder Minimization 2019

这题本质上考察的是**模拟**算法。


题意： 给出 $L$ 和 $R$，在其中找出 $i$ 和 $j$，使得 $i×j\;mod\;2019$ 最小。

但是其中依旧有应该注意的地方：

首先由于范围为 $10^8$,所以必须开 long long。

2.如果在其中

```cpp
if(ans==0)
	break;
```
因为 $0$ 已经是最小的，所以显而易见，我们就没有必要继续循环下去了，所以直接跳出就可以了。

~~（如果不加这里第三个点会 $T$）~~

所以代码就是这样了：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
signed main()
{
	int n,m;
	cin>>n>>m;
	int ans=1e6+10;
	for(int i=n;i<=m;i++)
	{
		for(int j=i+1;j<=m;j++)
		{
			ans=min(ans,(i*j)%2019);
			if(ans==0)
				break;
		}
		if(ans==0)
			break;
	}
	cout<<ans<<endl;
}
```



---

## 作者：Deamer (赞：0)

# 思路：

一看到这道题想到的就是暴力枚举了，但一看 $0≤L<R≤2×10^9$，$O((R-L+1)^2)$ 的时间复杂度显然是不够的。 

但我们不要被迷惑了，因为题目里说了是$\mod 2019$ 后的结果。如果当 $L$ 和 $R$ 特别大的时候，我们 $i$ 和 $j$ 最多只需分别考虑 $2019$ 个数就行了，因为 $(i×j)\mod 2019$ 的结果必然在 $0 - 2018$ 这  $2019$ 个数里。

那么，现在的时间复杂度就降成了 $O ( 2019^2 )$  ，远小于时间限制。

**~~reader : Talks are cheap , show me the code !!!~~**


```cpp
#include<bits/stdc++.h>
using namespace std;
long long L,R,ans=2019;
int main(){
	scanf("%lld%lld",&L,&R);
	for(long long i=L;i<=R;i++){
		for(long long j=i+1;j<=R;j++){
			ans=min(ans,(i*j)%2019);
			if(ans==0){					
				printf("0\n");
				return 0;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```
再说几个可能错的点吧：

- 由于 $0≤L<R≤2×10^9$ ，程序里面的一些变量记得要开 ```long long``` 。

- 由于 $L≤i<j≤R$ ，$j$ 必须从 $i+1$ 开始枚举，否则连样例都过不去。

[完结撒花！！！](https://www.luogu.com.cn/record/76595853)


---

## 作者：EthanC_ (赞：0)

### 解题思路：
第一眼看到这一道题的感觉就是枚举。但是需要注意：
- 变量得开 `long long` 。因为单个区间最大已经是 $ 10^9 $ 了，再做乘法绝对会爆 `int` ，所以我们得开 `long long`。

我们可以用 $ i $ 和 $ j $ 模拟每一个区间内的数并找出乘积 $\bmod$ (取余) $ 2019 $ 最小的两个数。并且为了不超时，我们可以特判 $ ans=0 $ 时直接跳出循环。
### 代码：
```cpp
#include<iostream>
using namespace std;
int main() {
    long long l,r;//开long long
    long long ans=2019;
    cin>>l>>r;
    for(long long i=l;i<=r;++i){
        for(long long j=i+1;j<=r;++j){
            ans=min(ans,(i*j)%2019);//判断最小值
            if(ans==0)break;//如果为0那么肯定是最小，直接跳出循环。
        }
        if(ans==0)break;//同上。
    }
    cout<<ans;//输出最小值
    return 0;
}

```



---

## 作者：heaksicn (赞：0)

## 1 题意
在 $[l,r]$ 的范围内选择两个数 $i,j(i<j)$，使得 $(i \times b)\mod 2019$ 最小。
## 2 思路
乍一看 $l,r\leq 2 \times 10^9$，$O((r-l+1)^2)$ 的时间复杂度肯定会炸。、

但是我们发现，只要我们找到 $i\mod 2019=0$ 或者 $j\mod 2019=0$，那么答案肯定就是 $0$。

所以暴力的时间复杂度就降成了 $O(2019^2)$。

直接暴力即可。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll l,r;
ll ans,now;
int main(){
	cin>>l>>r;
	ans=2022;
	for(ll i=l;i<r;i++){//枚举i
		for(ll j=i+1;j<=r;j++){//枚举j
			ans=min(ans,(i*j)%2019);//取最小值
			if(ans==0) break;//已经达到最小值
		}
		if(ans==0) break;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：makerlife (赞：0)

## 思路

直接暴力枚举。

有两点要注意：

1. 如果当前求得的最小值为0，直接输出并退出程序；~~我第一遍就是这么TLE的。~~

2. 数据范围是 $2 \times {10^9}$， 再一乘必然会爆 $\texttt{int}$，所以要开 $\texttt{long long}$。

## 上代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
ll l,r;
ll ans=2020;//ans的初始值只要小于 mod2019 也就是2018 就可以
int main()
{
	scanf("%lld%lld",&l,&r);
	for(ll i=l;i<=r;i++)
	{
		for(ll j=i+1;j<=r;j++)
		{
			ans=min(ans,(i*j)%2019);
			if(ans==0)//如果为0直接输出并退出程序，否则会超时
			{
				printf("0\n");
				return 0;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}

```

**岛国的题一定要行末换行**

---

## 作者：zjyqwq (赞：0)

### AT4810 [ABC133C] Remainder Minimization 2019题解


------------
#### 题意理解

题目的大致意思是：给定 $L-R$ 的区间，让你任意选择两个数使其乘积模 $2019$  的余数最小，输出余数。



------------
#### 解题思路

枚举。

双重循环枚举区间范围，如果当前的最小值为零，则退出循环即可。

如果区间范围超过 $2019$ ，则一定会有 $0$ 的情况，反则不会超时，所以时间复杂度是非常小的。

唯一要注意的是，区间最大会达到 $10^9$ ，这是乘起来再取模会爆 $int$ ，我们需要开 $long\ long$ 。


------------
#### 主要代码
```cpp
#include<bits/stdc++.h>
using namespace std; 
#define R register
int main(){
	R long long n,m,ans;//需要开long long。
	cin>>n>>m;
	for(R long long i=n;i<=m;i++)
	for(R long long j=i+1;j<=m;j++){
	ans=min(ans,i*j%2019);
	if(ans==0){//如果有0的情况出现，直接退出。
	    return cout<<0<<endl,0;
	}
	}
	cout<<ans;
}
```


------------
完结撒花！![qq](https://cdn.luogu.com.cn/upload/pic/62224.png)

---

## 作者：Accteped (赞：0)


## 思路
看到这题，我就想到了暴力枚举

用两个循环来模拟区间中的每一个数中的两个，来对其结果取min，为了节省时间，我还加了个特判，就是如若余数为0就不用在继续判断，直接输出然后跳出即可

用i和j模拟每一个区间内的数并找出乘积取余2019最小的两个数

### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
long long l,r;//输入的两个数，必须开long long 
long long ans=2018;//答案，因为mod2019最多为2018 
int main(){
	cin>>l>>r;
	for(long long i=l;i<=r;++i){
		for(long long j=i+1;j<=r;++j){
			//在l~r区间中模拟乘积与2019最小的两个数
			ans=min(ans,(long long)(i*j%2019));//取最小值
			if(ans==0){//如果余数已经为0，就不用再判断了，因为0已经是最小的了 
				cout<<ans;
				return 0;
			} 
		}
	}
	cout<<ans;//输出答案
	return 0;//不能忘了 
}
```


---

## 作者：锦阳2006 (赞：0)

题目大意：给你$L$,$R$两数，选择$i$,$j$满足$L \leq i,j\leq r$,$i $<$j$,求出$i \times$$j$ $mod$ $2019$ 的最小值。

思路：暴力模拟即可。    
上代码
```c
#include<bits/stdc++.h>//万能头文件
using namespace std;//命名空间
#define rd read()
#define gc getchar()
#define ll long long
#define pu puts(" ")
int read() {
	int x=0,f=1;char ch=gc;
	while(!isdigit(ch)) {
  if(ch=='-')f=-1;ch=gc;}
	while(isdigit(ch))x=x*10+ch-48,ch=gc;
	return x*f;//快读
}
void print(int x) {
	if(x>9)print(x/10);
	putchar(x%10+48);//快输
}
ll ans=2018;//不超过2019
int main() {
   ll l=rd,r=rd;//输入l,r
   for(ll i=l;i<=r;i++)//循环枚举
   {
   	for(ll j=i+1;j<=r;j++)//从i+1开始循环
   {
   		ans=min(ans,i*j%2019);//更新答案
   		if(ans==0)
   		{
   			puts("0");return 0;//特判等于0的情况，直接结束
		   }
	   }
	} 
	print(ans),pu;//输出答案
	return 0;
}
```


---

