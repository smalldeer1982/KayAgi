# Cave Painting

## 题目描述

Imp is watching a documentary about cave painting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922C/492e738c81624c946c2f042260b850d1eaf30603.png)Some numbers, carved in chaotic order, immediately attracted his attention. Imp rapidly proposed a guess that they are the remainders of division of a number $ n $ by all integers $ i $ from $ 1 $ to $ k $ . Unfortunately, there are too many integers to analyze for Imp.

Imp wants you to check whether all these remainders are distinct. Formally, he wants to check, if all ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922C/39f2e5c509199205284370aee9d1f8146afae4b5.png), $ 1<=i<=k $ , are distinct, i. e. there is no such pair $ (i,j) $ that:

- $ 1 \leq i < j \leq k $ ,
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922C/ac7c31555d5d75a7ddeca570475f6120983c1d66.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922C/a2ab7eb81b242742b5775a80b9ed4a6c9876ed81.png) is the remainder of division $ x $ by $ y $ .

## 说明/提示

In the first sample remainders modulo $ 1 $ and $ 4 $ coincide.

## 样例 #1

### 输入

```
4 4
```

### 输出

```
No
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
Yes
```

# 题解

## 作者：Composite_Function (赞：3)

# 思路

$\texttt{CF922C Cave Painting}$ 诈骗题一道。

从模的性质入手，有 $n \mod i$ 的范围一定是 $[0, i - 1]$。

又有 $n \mod 1 = 0$

推出 $n \mod 2 = 1$

推出 $n \mod 3 = 2$

以此类推，得到 $\forall i \in [1, k] ~~ n \mod i = i - 1$。

于是只需枚举 $[1, k]$。时间复杂度 $O(k)$，实际跑不到那么久。

这里给出大部分题解都没的证明：

因为如果能够循环到第 $i$ 次，则 

$$\min\left\{n\right\} = \gcd  _ {i = 1} ^ n\left\{i\right\} - 1$$

而实际的数据中 $n \in [1, 1e18]$，最多也不会超过 $50$ 次左右。

------------

# 代码

```
# include <bits/stdc++.h>
using namespace std;

# define int long long

int n, k;
bool flag = true;

signed main()
{
    cin >> n >> k;
    for (int i = 1; i <= k; ++i)
        if (n % i != i - 1) {
            flag = false;
            break;
        }
    cout << (flag? "Yes" : "No") << endl;
    return 0;
}
```

---

## 作者：_Give_up_ (赞：2)

## 题目大意
给定 $n$ 和 $k$，求 $n$ mod $1 \sim k$ 之间所有的数得出的结果，问有没有重复。

## 题目思路
根据规律可以看出：

当 $n$ mod $1$ 到 $k$ 中的所有数的结果没有重复的时候

$n $ mod $1= 0$

$n $ mod $2 = 1$

$n $ mod $3 = 2$

$n $ mod $4 = 3$

$n $ mod $5 = 4$

……

$n$ mod $i = i - 1$

所以只要 $n$ mod $i \neq i -1$，就是有重复的，输出 No，结束整个程序。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long //要开long long

using namespace std;

signed main()
{
	int n,k;
	cin >> n >> k;
	for (int i=1;i<=k;i++)
		if (n%i!=(i-1)) return cout << "No" << endl,0; //如果发现有重复的，就跳出循环。
	cout << "Yes" << endl;
	return 0; 
}
```


---

## 作者：BotDand (赞：2)

# $\text{Problems}$
给定$n,k$（$n,k\leq 10^{18}$）

回答$n \mod i,i\in [1,k]$是否都不同
# $\text{Answer}$
题目翻译成人话：给出$n$和$k$，判断$n \mod 1$到$k$每个数的余数是不是都不相同。

* $n \mod 1$ 可以为$0$
* $n \mod 1$ 可以为$0,1$，但因前面已有$0$，排除$0$，只可能为$1$。
* $n \mod 2$ 可以为$0,1,2$，但因前面已有$0,1$，排除$0,1$，只可能为$2$。
以此类推

最后的表格长这样：
| $n \mod k$ | 余数 |
| :----------: | :----------: |
| $n \mod 1$ | $0$ |
| $n \mod 2$ | $1$ |
| $n \mod 3$ | $2$ |
| $n \mod 4$ | $3$ |
| $...$ | $...$ |
| $n \mod k$ | $k-1$ |

于是判断$n \mod k$是否等于$k-1$即可。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,p=1;
int main()
{
    cin>>n>>k;
    for(long long i=1;i<=k;++i) if(n%i!=i-1) {p=0;break;}
    if(p) cout<<"Yes";else cout<<"No";
}
```


---

## 作者：Remake_ (赞：2)

这道题的上一篇题解竟然说要暴力！！！

$n,k \leq 10^{18}$看不见吗，~~是不是数据太水了~~？

但是，虽然数据很大，~~我还是认为此题是恶意评分，应该是红题~~。

为了证明此题很水，我只能用小学做法来讲了。

首先$n\%1=0$都无可否认，所以，$n\%2$不能为$0$，但是它的值只能为$0\,or\,1$，所以$n\%2=1$。同样的，因为$n\%1=0$且$n\%2=1$，所以$n\%3=2$，又因为$n\%1=0$且$n\%2=1$且$n\%3=2$，$n\%4=3$。

发现规律了么，规律便是，对于任何一个$1\leq i \leq k$，都保证$n\%i=i-1$。

ohhhhhhhh......

别着急欢呼，这时运用小学数学知识给$n$加上$1$，规律就变成对于任何一个$1\leq i \leq k$，都保证$i|n$。

然后我们发现，满足此性质的最小的数是$lcm(1,2...,k)$，然后其他满足此性质的则是$lcm(1,2...,k)$的整数倍。

## 所以，这道题的结论便是：

输出为$Yes$，**当且仅当** $lcm(1,2...,k)|n+1$。

你有可能会说，复杂度不还是$O(k)$吗？

其实不然，$lcm(1,2...,k)$增长的很快，**大概**不到$100$就会爆long long，所以如果$k>100$基本上就可以直接输出$No$了。

加点特判~~应该~~就能水过了。。。。。。

---

## 作者：Siteyava_145 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF922C)

**题目内容略（逃**

**题目分析：**

$n,k$ 在```long long```范围内。

~~你给我暴力枚举逝逝~~

所以我们要**理性**思考：

- $n\bmod 1=0$。

- $n\bmod2=0$ 或 $1$，但如果为了满足题目要求，余数不能为 $0$。于是 $n\bmod 2=1$。

- 同理 $n\bmod3=0$ 或 $1,2$。但是为了满足题目要求，余数不能为前面的 $0,1$。所以 $n\bmod 3=2$。

- 推广到 $k$。$n\bmod k$ 可能等于 $0$ 到 $k-1$ 的任意数值，但是前面的 $0$ 到 $k-2$ 都已经出现过了，所以余数就只能是 $k-1$。

- 所以我们就只需要判断 $n\bmod i$ 是否等于 $i-1(1\leq i\leq m)$。

[AC](https://www.luogu.com.cn/record/78191553) code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        if(n%i!=(i-1)){cout<<"No";return 0;}
    }
    cout<<"Yes";
}
```


---

## 作者：chaichunyang (赞：1)

# 题面
## 题目描述
输入$n$和$k$，判断$n\%1$到$k$每个数的余数是不是都不相同
## 输入格式
输入数据包含多组，每行两个数字$n$、$k$，空格隔开。 以$0 0$结束
## 输出格式
对于每行的有效数据，如果所有余数均不相同，输出$Yes$，否则输出$No$
## 一句话题面
给定$n$,$k$ （$n$,$k\leq 10^{18}$）

回答$n\ \%\  i,  i\in [1,k]$是否都不同
# 思路分析
## 暴力思路
枚举$1$~$k$，看看余数是否相同
但是`TLE`是少不了的
## 一点优化
当$N\le K$时，直接`No`
因为$N\%1=0$ $N\%N=0$
但还是`TLE`，分数也不变
~~^一分都没多讲了有什么用啊^~~
## 正解分析
### 推数据
#### 样例数据
`5 3`---`Yes`
|$5\%1=0$|
|--|
|$5\%2=1$|
|$5\%3=2$|
好像有点规律
再来一组
`5039 7`---`Yes`
|$5039\%1=0$|
|--|
|$5039\%2=1$|
|$5039\%3=2$|
|$5039\%4=3$|
|$5039\%5=4$|
|$5039\%6=5$|
|$5039\%7=6$|
好像真有规律
#### 普遍数据
`N K`---`Yes`$(N<K)$
|算式|可取余数|
|--|--|
|$N\%1=\in[0,0]$|**0**|
|$N\%2=\in[0,1]$|~~0~~,**1**|
|$N\%3=\in[0,2]$|~~0~~,~~1~~,**2**|
|$N\%4=\in[0,3]$|~~0~~,~~1~~,~~2~~,**3**|
|$……$|$……$|
|$N\%K=\in[0,K-1]$|~~0~~,~~1~~,~~2~~,$……$,~~K-2~~,**K-1**|
可以通过普遍的数据看出
如果回答是`Yes`,那么$N\%i=i-1$($i\in[1,K]$)
### 正解
当$N\%i=i-1$($i\in[1,K]$)时，输出`Yes`

当$N\%i\not=i-1$($i\in[1,K]$)时，输出`No`

# 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long N,K;
bool ans;
int main(){
	while(1){
		ans=1;
		scanf("%lld%lld",&N,&K);	
		if(N==0&&K==0)return 0;
		for(long long i=1;i<=K;i++){
			if(N%i!=i-1) {
				ans=0;
				break;
			}
		}
		if(ans)printf("Yes\n");
		else printf("No\n");
	}
}
```


---

## 作者：durex_com (赞：1)

题意很容易看懂。就是对一个区间找%不同。

~~但是特判特别坑比~~

纯暴力查询，没毛病。
```cpp
//特容易懂就不注释了。
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;
long long n,k;
int vis[3000001];
int check(long long n,long long k)
{
	for(int i=1;i<=k;i++)
	{
		long long modu=n%i;
		if (vis[modu]) return 0;
		vis[modu]=1;
	}
	return 1;
}
int main()
{
	 scanf("%lld%lld",&n,&k);
	 if (n==1&&k==1)
	 {
	 	printf("Yes");
	 	return 0;
	 }
	 if (n==1&&k==2)
	 {
	 	printf("Yes");
	 	return 0;
	 }
	 if (n<=k)
	 {
	 	printf("No");
	 	return 0;
	 }
	 if (check(n,k))
	 {
	 	printf("Yes");
	 }
	 else printf("No");
	 return 0;
}
```

---

## 作者：sto_OwenLMZ2022_orz (赞：0)

一、题意

这道题的简化题意是：给定 $n$，求 $n$ $\bmod$ $1∼k$ 的所有数的结果是否有一样的，有打印 No，没有打印 Yes。

二、思路

这道题大多数人的第一反应就是暴力枚举，但看了数据就知道一定会
TLE，所以我们要找规律。

我们来推导一下：

- $n$ $\bmod$ $1$，我们知道任何数 $\bmod$ $1$ 余数一定为 $0$，故 $n$ $\bmod$ $1$ = $0$

- $n$ $\bmod$ $2$，这个式子结果可以为 $0$ 或 $1$，但上一个式子为 $0$，故这个式子只能为 $1$。

......

- $n$ $\bmod$ $i$，这个式子结果可以为 $0$ 到 $(i-1)$，但上面的所有式子为 $0$ 到 $k$，故这个式子只能为 $i-1$。

结论：只要 $n$ $\bmod$ $i$ $\neq$ $(i-1)$
，就是有重复的，输出 No，反之输出 Yes。

三、代码实现

```cpp
#include<iostream>
using namespace std;
int main(){
    ios::sync_with_stdio (false);//加快cincout速度
	long long n,k;//看准数据范围，要开longlong
	cin>>n>>k;
	for(int i=1;i<=k;i++){
	    if (n%i!=(i-1)){
	        cout<<"No"<<endl;//记得换行
	        return 0;//要退出程序不然会打印no和yes
	    }
	}
	cout << "Yes" << endl;
	return 0; //好习惯
}
```


---

## 作者：Xdl_rp (赞：0)

## 简要题意
输入一个 $n$，一个 $k$。问在 $i,1 \le i \le k$，$n \bmod i$ 是否互相不同。

solution
------------
可以推出，当答案为 `Yes` 时：

$n \bmod 1 = 0$，$n \bmod 2 = 1$，$n \bmod 3 = 2$，$n \bmod i = i - 1$。

以此类推。

但是如果直接一个循环下去肯定会超时，有一个数据范围就值得我们注意了，$n, k \le 10 ^ {18}$，当 $k$ 超过 $100$（不知道准确到哪里，$100$ 足够了）时，$n$ 就一定大于 $10 ^ {18}$，所以之后的就不需要考虑了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	long long n, k;
	bool flag = 1;
	cin >> n >> k;
	if (k >= 100) {
		cout << "No";
		return 0;
	}
	for (long long i = 1; i <= k; i++) {
		if (n % i != i - 1) {
			flag = 0;
			break;
		}		
	}
	if (flag) cout << "Yes";
	else cout << "No";
}
```


---

## 作者：Nozebry (赞：0)

## $Problems$
输入 $n$ 和 $k$，判断 $n\bmod 1...k$ 每个数的余数是不是都不相同
## $Answer$
我们不难发现
	
    n mod 1=0
    n mod 2=1
    n mod 3=2
    ...
    n mod i=i-1
    也就是(n+1)mod i=0
所以这些数就必须是 $k!$ 的倍数 $-1$，但是 $20!$ 就已经超出了 $long long$ 的范围，所以不必再判断 $20$ 以上的数了。。。
## $Code$
```cpp
#include<bits/stdc++.h>
int main()
{
    long long n,k;
    scanf("%lld%lld",&n,&k);
    if(k>20)
	{
		printf("No");
		return 0;
	}
    for(long long i=1;i<=k;i++)
    	if(n%i!=(i-1)){printf("No");return 0;}
    printf("Yes");
}
```

---

