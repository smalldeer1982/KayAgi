# Two Problems

## 题目描述

一个男孩珐乐菈在CF注册了一个账号叫做珐乐菈，然后做了他的第一个比赛#300。他跟他的朋友阿卡狄炫耀在他的第一个比赛里他得了$x$分。但是阿卡狄并不相信他朋友的话，然后决定去查珐乐菈能不能的这样的分数。

他知道比赛编号$300$很不寻常因为这个比赛只有两道题。这次比赛进行了$t$秒，时间是从0分开始计数。第一道题最开始有$a$分，然后每分钟这个分数就会掉$d_a$分。第二道题最开始有$b$分，然后每分钟这个分数就会掉$d_b$分。而且，一旦这道比赛的零分钟结束时，第一道题就会有$a - d_a$分，然后第二题会有$b - d_b$分。保证比赛过程中的分值全是非负数。

阿卡狄要你确认珐乐菈能不能在这个比赛中得到$x$分。你能认为珐乐菈每道题能得任意分数。你也可以认为任何问题珐乐菈只交了一次，而且，在0分钟和$t-1$分钟之间，他可能同时提交了两道题。注意：在$t$分钟时他不能提交代码。

## 样例 #1

### 输入

```
30 5 20 20 3 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
10 4 100 5 5 1
```

### 输出

```
NO
```

# 题解

## 作者：XH1111 (赞：3)

警告，警告，这道题非常的水！！！
## 思路
用两个数组去存比赛分时时变化的值，然后一个一个实验即可。
## 实现过程
先定义:
```
int x,t,a,b,c,d,s,p,f[1000],y[1000];//s、p 计数，f、y数组 
```
再用两个循环，时时用数组记录变化的值：
```
for(int i=1;i<=t;i++){
	if((a-c)>=0){//只要没小于零，就用数组记下来 
		f[i]=a;
		a-=c;
		s=i;
	}
	else{//否则跳出循环 
		break;
	}
}
for(int i=1;i<=t;i++){//与上一个循环同理 
	if((b-d)>=0){
		y[i]=b;
		b-=d;
		p=i;
	}
	else{
		break;
	}
}
```
记下数后，再用一个双重循环输出，即可通过。
```
for(int i=1;i<=s;i++){
	for(int j=1;j<=p;j++){
		if(f[i]+y[j]==x){//符合就输出YES 
			cout<<"YES"<<endl; 
			return 0;//并且结束代码 
		}
	}
}
cout<<"NO"<<endl;//否则，就输出NO 
```
## 最后代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int x,t,a,b,c,d,s,p,f[1000],y[1000];//s、p 计数，f、y数组 
	cin>>x>>t>>a>>b>>c>>d;
	for(int i=1;i<=t;i++){
		if((a-c)>=0){//只要没小于零，就用数组记下来 
			f[i]=a;
			a-=c;
			s=i;
		}
		else{//否则跳出循环 
			break;
		}
	}
	for(int i=1;i<=t;i++){//与上一个循环同理 
		if((b-d)>=0){
			y[i]=b;
			b-=d;
			p=i;
		}
		else{
			break;
		}
	}
	for(int i=1;i<=s;i++){
		for(int j=1;j<=p;j++){
			if(f[i]+y[j]==x){//符合就输出YES 
				cout<<"YES"<<endl; 
				return 0;//并且结束代码 
			}
		}
	}
	cout<<"NO"<<endl;//否则，就输出NO 
	return 0;
} 
```

---

## 作者：hanyuchen2019 (赞：1)

一个爆搜，但细节有点多。

### part 1 思路

由于数据范围很小，很容易想到爆搜枚举两题的提交时间，但需要特判有一题或全部没交的情况。

另外，有 $2$ 个坑点：

1. 提交的时间必须 $<t$，**不能在 $t$ 分钟的时候提交**，而且可以在 $0$ 分钟提交。

2. 特判的时候要注意炸出来负数的情况。

特判部分的伪代码如下：
```
if(分数为0){输出YES后结束程序;}
if(在某题中，x不超过本题总分 && 在t分钟内可以扣到这个分数){输出YES后结束程序;}
```

### part 2 代码

根据 part $1$ 的思路，可写出以下代码（可AC，后面有更快的做法）：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int x,t,a,b,da,db;
	cin>>x>>t>>a>>b>>da>>db;
	if(x==0){puts("YES");return 0;}
	if(a>=x && (a-x)%da==0 && (a-x)/da<t){puts("YES");return 0;}
	if(b>=x && (b-x)%db==0 && (b-x)/db<t){puts("YES");return 0;}
    
	for(int i=0;i<t;++i)//开始爆搜提交时间
		for(int j=0;j<t;++j)
			if(a-da*i+b-db*j==x)
			{
				puts("YES");
				return 0;
			}
	puts("NO");
	return 0;
}
```

### part 3 还能更快！

实际上，这题还有更快的写法。

我们可以把这题转化成一个解不定方程的“数学题”（注：为了描述方便，这里暂时不考虑有一题或全部没交的情况）：

给定 $x,t,a,b,d_a,d_b$，问能不能找到至少一组整数数对 $(i,j)$，

使得 $0 \le i,j < t$
，且   
 $(a-d_a \times i)+(b-d_b \times j)=x$。

那么，我们只需要爆搜 $i$ 的值，于是：

$$j=\frac{-x+a+b-d_a \times i}{d_b}$$

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int x,t,a,b,da,db;
	cin>>x>>t>>a>>b>>da>>db;
	if(x==0){puts("YES");return 0;}
	if(a>=x&&(a-x)%da==0&&(a-x)/da<t){puts("YES");return 0;}
	if(b>=x&&(b-x)%db==0&&(b-x)/db<t){puts("YES");return 0;}
	for(int i=0;i<t;++i)
	{
		int j=(-x+a+b-da*i)/db;
		if(j>=0&&j<t&&a-da*i+b-db*j==x)
		{
			puts("YES");
			return 0;
		}
	}
			
	puts("NO");
	return 0;
}
```

码字不易，点个赞吧~

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF203A)
## 思路：

按要求模拟就行了，但需要注意 $x=0$ 且 $a$ 或 $b$ 在枚举的过程中出现负数的情况。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int x,t,a,b,da,db;
	cin>>x>>t>>a>>b>>da>>db;//输入。
	if(x==0){//特判。
		puts("YES");
		return 0;
	}else{
		for(int i=0;i<=min(a/da,t-1);i++){
			for(int j=0;j<=min(b/db,t-1);j++){//枚举考试时间（可以自己想一下为什么循环条件要求最小值，答案放在最后面）。
				if(a-da*i==x||b-db*j==x||(a-da*i)+(b-db*j)==x){//判断是否当时的分数刚好为x值。
					puts("YES");//是。
					return 0;//结束程序。
				}
			}
		}
	}
	puts("NO");//没有结果。
	return 0;//结束程序。
}
```


思考题答案：
	本来这个循环就是来枚举时间的，但是最后一分钟时，如果 $a$ 或者 $b$ 的分数降到了 $0$ 或以下时，就不满足题目要求了。

---

## 作者：RainFestival (赞：0)

$\tt{Difficulty = 1200}$

考虑 $\tt{Valera}$ 可能做了的题目数量。

+ 如果他做了 $0$ 题，那么得分为 $0$。

+ 如果他做了 $1$ 题，那么得分为 $a-da\times i,0\le i\le t-1$ 或者 $b-db\times i,0\le i\le t-1$。当然还要保证每道题目不能得到负数分。

+ 如果他做了 $2$ 题，那么得分为 $a-da\times i+b-db\times i,0\le i\le t-1$。当然还要保证每道题目不能得到负数分。

由于 $t$ 很小，可以直接枚举。

时间复杂度 $O(t^2)$。

代码：

```cpp
#include<cstdio>
#include<algorithm>
int x,a,b,da,db,t;
int main()
{
	scanf("%d%d%d%d%d%d",&x,&t,&a,&b,&da,&db);
	if (x==0) return puts("YES"),0; 
	for (int i=0;i<=std::min(a/da,t-1);i++) if (x==a-da*i) return puts("YES"),0;
	for (int i=0;i<=std::min(b/db,t-1);i++) if (x==b-db*i) return puts("YES"),0;
	for (int i=0;i<=std::min(a/da,t-1);i++) for (int j=0;j<=std::min(b/db,t-1);j++) if (x==a-da*i+b-db*j) return puts("YES"),0;
	puts("NO");
}
```
代码长度 $\tt{453B}$

---

## 作者：sysong (赞：0)

# 题解CF203A Two Problems

### 题目描述

[$RT$](https://www.luogu.com.cn/problem/CF203A)

题面较长，截取主要部分如下：


**这次比赛进行了 $t$ 秒，时间是从 0 分开始计数。第一道题最开始有 $a$ 分，然后每分钟这个分数就会掉 $d_a$ 分。第二道题最开始有 $b$ 分，然后每分钟这个分数就会掉 $d_b$ 分。而且，一旦这道比赛的零分钟结束时，第一道题就会有 $a - d_a$ 分，然后第二题会有 $b - d_b$ 分。保证比赛过程中的分值全是非负数。**

**阿卡狄要你确认珐乐菈能不能在这个比赛中得到 $x$ 分。你能认为珐乐菈每道题能得任意分数。你也可以认为任何问题珐乐菈只交了一次，而且，在 0 分钟和 $t-1$ 分钟之间，他可能同时提交了两道题。注意：在 $t$ 分钟时他不能提交代码。**


### $Solution$

这道题实际不难解决，不需要数学，只要枚举即可。

为什么只要枚举呢？

由题，显然可以得到 $a - k_1 \times d_a + b - k_2 \times d_b = x$。

其中 $0 \leq k_1 , k_2 < t \leq 300$

但是，就这样吗？（细节卡了我好久）

**如果他第一题（或第二题）根本就没有提交，那么其中一题的分数可以直接去掉。**

即 $a - k_1 \times d_a = x$ 或 $b - k_2 \times d_b =x$ 或直接两题都没写—— $x = 0$。

所以直接枚举 $k_1$ 和 $k_2$ 就行了。

因为 $0 \leq k < t \leq 300$，所以时间复杂度 $O(t^2)$，完全可以通过。

### $C++ \ Code$

 ```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
using namespace std;

inline int rd(){
	R int x=0;R char c=gc();//,f=1
	while(c>'9'||c<'0')c=gc();//{if(c=='-')f=-1;
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x;//*f
}

int main(){
	R int x=rd(),t=rd(),a=rd(),b=rd(),d1=rd(),d2=rd(),f=a+b-x;
	for(R int i=0;i<t;i++)
		for(R int j=0;j<t;j++)
			if(x==0||j*d1==a-x||j*d2==b-x||i*d1+j*d2==f){
				printf("YES\n");
				return 0;
			}
	printf("NO\n");
	return 0;
}
 ```



***by jsntsys***

$2020.11.27$



---

## 作者：Fractures (赞：0)

## 给自己翻译的题目写题解的感觉真是奇妙呢

那么这道题就是一道暴力水题，直接一个一个搜索不用怕超时，~~毕竟数据太水了~~

#### 但是，弱弱的我还是一开始做错了（我好弱啊）
```cpp
#include<cstdio>
using namespace std;
int x,t,a,b,da,db;
int orz[10001],sto[100001];
int main(){
    scanf("%d%d%d%d%d%d",&x,&t,&a,&b,&da,&db);
    for(int i=0;i<t;i++){
        orz[i]=a-da*i;
        sto[i]=b-db*i;
    }
    for(int i=0;i<t;i++){
        for(int j=0;j<t;j++){
            if(orz[i]+sto[j]==x){
                printf("YES");
                return 0;
            }
        }
    }
    printf("NO");
    return 0;
} 
```
↑错误代码

##### 其实打眼一看没什么错误，但是忘了一个很重要的东西：没有考虑到他可以干脆不叫的零分

所以改了代码之后就是这个样：
```cpp
#include<cstdio>
using namespace std;
int x,t,a,b,da,db;
int orz[1000001],sto[100001];
int main(){
	scanf("%d%d%d%d%d%d",&x,&t,&a,&b,&da,&db);
	for(int i=0;i<t;i++){
		orz[i]=a-da*i;
		sto[i]=b-db*i;
	}
	orz[t]=0;
	sto[t]=0;
	for(int i=0;i<=t;i++){
		for(int j=0;j<=t;j++){
			if(orz[i]+sto[j]==x){
				printf("YES\n");
				return 0;
			}
		}
	}
	printf("NO\n");
	return 0;
} 
```
那么这道题就水过去啦2333

---

