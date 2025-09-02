# Easy Number Challenge

## 题目描述

Let's denote $ d(n) $ as the number of divisors of a positive integer $ n $ . You are given three integers $ a $ , $ b $ and $ c $ . Your task is to calculate the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF236B/6b4d9893ce96bd0459ff1289a8bf3491052ac12a.png)Find the sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 说明/提示

For the first example.

- $ d(1·1·1)=d(1)=1 $ ;
- $ d(1·1·2)=d(2)=2 $ ;
- $ d(1·2·1)=d(2)=2 $ ;
- $ d(1·2·2)=d(4)=3 $ ;
- $ d(2·1·1)=d(2)=2 $ ;
- $ d(2·1·2)=d(4)=3 $ ;
- $ d(2·2·1)=d(4)=3 $ ;
- $ d(2·2·2)=d(8)=4 $ .

So the result is $ 1+2+2+3+2+3+3+4=20 $ .

## 样例 #1

### 输入

```
2 2 2
```

### 输出

```
20
```

## 样例 #2

### 输入

```
5 6 7
```

### 输出

```
1520
```

# 题解

## 作者：Ptilopsis_w (赞：2)

# 题意
求 $∑^{a}_{i=1}∑^{b}_{j=1}∑^{c}_{k=1}d(i*j*k)$  

其中 $d(x)$ 表示 $x$ 的因子个数  
题目传送门 [CF236B](https://www.luogu.com.cn/problem/CF236B)
# 思路
1. `时间限制 2.00s` 这东西摆在这里很明显就是让你暴力求解，所以直接三层循环干就完了
2. 众所周知，每个数的因子都是成对出现的,比如 $6$ 这个数，他的因子写出来是 $1,6$ 和 $2,3$ ，但是正整数的平方这些数是有重复因子的，比如 $9$ 的因子是 $1,9$ 和 $3,3$ ，因为 $9$ 是 $3$ 的平方， 所以 $3$ 这个因子是重复的
3. 因为这是个三层循环，会乘出来很多重复的数，为了节省时间，我们可以进行一下记忆化，即把计算过的结果存储一下，下次遇到直接读取就行了

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int a, b, c, ans;
int mem[1000005];

int d(int x)
{
	if(mem[x] != 0)//之前计算过就直接return结果
		return mem[x];
	int s = 0;
	for(int i = 1; i <= sqrt(x); i++)//成对的因子以sqrt(x)为界限
									 //这个自己算一下就知道为什么了
	{
		if(x%i == 0)
			s += 2;
	}
	if(int(sqrt(x))*int(sqrt(x)) == x)//如果是完全平方数，就会有重复因子
		s--;//因子数减一
	mem[x] = s;//把结果存起来
	return s;
}

int main()
{
	scanf("%d%d%d", &a, &b, &c);
	for(int i = 1; i <= a; i++)//暴力出奇迹
		for(int j = 1; j <= b; j++)
			for(int k = 1; k <= c; k++)
			{
				ans += d(i*j*k);
				ans %= 1073741824;
			}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：iorit (赞：1)

[原题](https://www.luogu.com.cn/problem/CF236B)

此题一个暴力就可以过了。

看着别的大佬不加记忆化吸口氧就过了，而我的却死活TLE

~~可能因为我人丑常数大？~~

注意到`i*j*k`的值会出现重复，所以考虑记忆化。

时间复杂度$O(n^3\sqrt n)$，~~跑得飞快~~

### 代码

```cpp
const int N = 1e6 + 10,M = 1073741824;
int a,b,c;
int ans = 0;
int mry[N];
int d(int i , int j , int k)
{
	int n = i * j * k;
	if( !mry[n] ) // 未被记忆化过
	{
		int sum = 0;
		for(int i = 1;i * i <= n;i++) // 统计因数个数
			if(n % i == 0)
				if(i * i == n)
					++sum; // n有一个因数i
				else
					sum += 2; // n有两个因数i,n/i
		mry[n] = sum; // 记忆化
	}
	return mry[n];
}
int main()
{
	cin >> a >> b >> c;
	for(int i = 1;i <= a;i++) // 大力三重循环！
		for(int j = 1;j <= b;j++)
			for(int k = 1;k <= c;k++)
				ans = ( ans + d(i , j , k) ) % M;
	cout << ans << endl;
    return 0;
}
```


---

## 作者：liuyifan (赞：1)

## 预处理因子和就可以了

水题,个人觉得初一代数就可以解决

直接暴力加判断

code:
```cpp
#include<bits/stdc++.h>
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
ll f[1000005],vis[1000005],a,b,c,m,cnt,sum;
int main()
{
	while(scanf("%lld%lld%lld",&a,&b,&c)==3)//输入不定像数据的常用方法
	//(!=EOF)那种如果遇到死变态出题人数据末无回车会被卡
	{
		sum=0;
		memset(vis,0,sizeof(vis));
		memset(f,0,sizeof(f));//数组清空,多组数据一定小心这一点
		for(reg int i=1;i<=a;i++)
		for(reg int j=1;j<=b;j++)
		for(reg int k=1;k<=c;k++)
		{
			m=i*j*k,cnt=0;
			if(!vis[m])
			{
				vis[m]=1;
				for(reg int l=1;l<=sqrt(m);l++)
				if(!(m%l))cnt+=1+(m/l!=l);//这里可能写的有点绕
				//翻译一下就是下面这段:
					if(m%l==0)//!(m%l)在m%l为0时为真,否则为假
					if(m/l!=l)cnt+=2;
					else cnt+=1;//同理,m/l!=l在表达式成立是为1，否则为0
				//所以以后我们就可以像这样放心大胆的压行了，嘻嘻
				f[m]=cnt;
			}
			sum=(sum+f[m])%1073741824;//大数据记得取及时模
		}
		printf("%lld\n",sum);
	}
	return 0;
}
```


---

## 作者：Jsxts_ (赞：0)

# 题解 CF236B

[传送门](https://www.luogu.com.cn/problem/CF236B)

## 题意

求 
$$ \sum_{i=1}^a\sum_{j=1}^b\sum_{k=1}^cf(i\times j \times k)$$
的值，其中$f(x)$为 $x$ 的因子个数。

## 题解

由于数据范围 $1\le a,b,c \le 100$，我们可以用三重循环暴力求解。

求因子个数的代码：

```cpp
int yz(int x) {//yinzi
   int sq = sqrt(x),sum = 0;
   for (int i = 1;i <= sq;i ++ ) {
      if (x % i == 0)
         sum += 2;//分别是i与x/i
   }
   if (sq * sq == x) sum --;
   return sum;
}
```

其中注意如果 x 是完全平方数，那么 $i$ 和 $x/i$ ,要减一。

最后注意到样例解释中有很多数是相同的，所以可以用一个记忆化。

剩下细节在代码中注释。

**（别忘了取模）**

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int yz(int x) {//yinzi
	int sq = sqrt(x),sum = 0;
	for (int i = 1;i <= sq;i ++ ) {//枚举1~根号x 
		if (x % i == 0) sum += 2;//分别是i与x/i
	}
	if (sq * sq == x) sum --;
	return sum;
}
int f[1000010];//记忆化数组 
int main() {
	int a,b,c,sum = 0;
	scanf("%d%d%d",&a,&b,&c);
	for (int i = 1;i <= a;i ++ ) {
		for (int j = 1;j <= b;j ++ ) {
			for (int k = 1;k <= c;k ++ ) {//三重循环暴力枚举 
				int t = i*j*k;
				if (f[t]) sum = (sum + f[t]) % 1073741824;//如果出现过了，就直接加 
				else f[t] = yz(t),sum = (sum + f[t]) % 1073741824;//记忆化后再加 
			}
		}
	}
	printf("%d",sum); 
    return 0;
}
```


---

## 作者：to_be_continued (赞：0)

这题首先可以确定的是——它是一题恶评题。。。

思路非常的简单。

题意讲一下。

只要枚举i,j,k。然后算出他们的积，然后累加积的约数个数就emm。

~~是不是很简单~~


首先一手预处理。



两种方法

### 1 直接算每一个数的约数个数。

然后你可以发现这个方法是不行的，极限数据是100* 100* 100，1百万呢，算一下O(n* sqrt(n))大概有一亿，emm然后就萎掉了。

当然程序可以看一下

```cpp
inline int num(int x){
    int ans=0;
    for (int i=1;i<=sqrt(x);i++){
        if (x%i==0)
            ans+=2;
    }
    int y=sqrt(x);
    if (y*y==x) ans--;
    return ans;
}
```

用子程序完成，不是很棒棒吗。

### 2 枚举约数

我们发现枚举每一个数，再去枚举约数，时间是肯定不够的，因为里面重复了多次，那么我们可以直接枚举约数啊。

思路也很简单

直接放整个程序

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <cstring>

using namespace std;

#define ll long long
#define mod 1073741824

inline ll adv(int x,int y,int z){
	return x*y*z;
}

ll answer=0;
int n[1000001];//存约数的个数
int maxx;

inline int num(int x){
	for (int i=1;i<=maxx/x;i++){//找x的倍数，找到就说明x是这个数的约数。
		n[i*x]++;
	} 
}
int main(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	maxx=adv(a,b,c); 
	for (int i=1;i<=adv(a,b,c);i++){//枚举约数
		num(i);
	}
	for (int i=1;i<=a;i++){
		for (int j=1;j<=b;j++){
			for (int k=1;k<=c;k++){
				ll x=adv(i,j,k);//函数装逼(划掉
				x%=mod;
				answer+=n[x];
				answer%=mod;
			}
		}
	}
	printf("%lld",answer);
} 
```


此人为C++蒟蒻。刚转C++不过100天。
在此致敬各位C++巨爷

---

## 作者：_edge_ (赞：0)

就是暴力三重循环，然后枚举因数。

这里我 $O(n^3\sqrt n)$ 居然 T 了。。。

然后我就把计算因数的那一段程序加了一个记忆化，于是就 A 了。

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int INF=1e6+5;
int a,b,c,Mod,ans,f[INF];
int d(int x) {
        if (f[x]) return f[x];
        int sum=0;
        for (int i=1; i*i<=x; i++) {
                if (x%i==0) {
                        if (x/i==i) sum++;
                        else sum+=2;
                }
                sum%=Mod;
        }
        return f[x]=sum;
}
signed main()
{
        scanf("%lld %lld %lld",&a,&b,&c);
        Mod=(1ll<<30);
        for (int i=1; i<=a; i++)
                for (int j=1; j<=b; j++)
                        for (int k=1; k<=c; k++)
                                ans=(ans+d(i*j*k)%Mod)%Mod;
        cout<<ans<<"\n";
        return 0;
}

```


---

