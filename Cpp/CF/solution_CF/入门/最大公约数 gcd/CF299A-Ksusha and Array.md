# Ksusha and Array

## 题目描述

输入 $N$ 个数字，你的任务是**在这些数字中**找到一个能够整除所有这些数字的数。

## 样例 #1

### 输入

```
3
2 2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
2 1 3 1 6
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
2 3 5
```

### 输出

```
-1
```

# 题解

## 作者：Tarsal (赞：3)

本蒟蒻又双叒叕被爆踩辣！

[这就是道大水题](https://www.luogu.org/problem/CF299A)

首先，题目意思：

给你n个数，要你找这些数字中找到一个能够被这些所有数字整除的数，若有多个，可任意输出其中一个，其实答案只有一个，因为在大于等于自己的数中能被自己整除的数只有它自己。

一句话题意(~~虽然好像本来就是一句话~~：

要你找到一个数$a[x]$，使: $gcd(a_1,a_2,a_3…a_n)$ $== a[x]$

是不是只要推出了这一步就没有任何问题了，是吧。

接下来，来证明一下(~~伪证~~：

窝们一样例为例

```
10
2 4 14 6 10 14 122 234 232 988
```

上面这组数据的 $gcd(a_1,a_2,a_3…a_n)$ 是不是为2.是不是$gcd(a_1,a_2,a_3…a_n)$ $== a[1]$ 成立。

```
5
122 244 366 2 488
```

还是一样的，这样是不是很好理解，你要找的数肯定是当前这些数中最小的，而且要保证gcd(a_1,a_2,a_3…a_n)$ $== a[x]$成立。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int dx[5] = {0, 1, -1, 0, 0};
const int dy[5] = {0, 0, 0, 1, -1};

//#define XRZ
#define int long long
#define maxn 100010
#define maxm
#define ll long long
#define mian main
#define inf 0x3f3f3f3f
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid (l + r >> 1)
#define debug(x) printf("now here is %d\n", x);
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout);
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(x, u) for(int i = head[u]; i ; i = e[i].nxt)

int n, a[maxn], b[maxn], c[maxn], ans;

bool cmp(int x, int y) {return x > y;}//因为要用小的序号对于大的权值，所以从大到小排序。

signed mian(){
	// file(a);
    scanf("%lld", &n);//读入
    Rep(i, 1, n){
        scanf("%lld%lld", &a[i], &b[i]);//输入每个角色的属性，好像a[],b[]并没有什么鸟用
        c[i] = a[i] - b[i];//这里是窝们求的(a[i] - b[i])，窝们只要维护它即可。
        ans += (n * b[i]) - a[i];//先加上定值。
    }
    sort(c + 1, c + n + 1, cmp);//排序。。。
    Rep(i, 1, n) ans += c[i] * i;//小的序号对于大的权值
    printf("%lld", ans);//输出
	return 0;
}
```
~~ps：请看懂再抄~~

---

## 作者：E1_de5truct0r (赞：2)

## 思路

这道题要求找最小的能被所有数整除的数。

首先如果 $a|b$ ，那么 $a \leq b$ 。那么如果一个数要被所有数整除，一定只有这个序列中的最小值。因为如果不是最小值，那么这个数一定无法整除这个序列中的最小值。

所以我们找到最小值，逐个判断是否可行即可。用打擂台法求最小值。时间复杂度 $O(n)$ ，$n \leq 10^5$ ，可以通过。

## 代码

```cpp
#include <cstdio>
inline int qmin(int a,int b){return a<b?a:b;} //求最小值的手写函数
int a[100005];
int main()
{
	int n,minn=1e9,sum=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),minn=qmin(minn,a[i]); //打擂台
	for(int i=1;i<=n;i++)
		sum+=a[i]%minn; //判断最小值是否可以整除其他所有的数。因为最小值可以被自身整除所以无需特判。
	printf("%d",((sum==0)?minn:-1)); //只有取模之和为0才能被全部整除。否则证明有没有被整除的，输出-1。
	return 0;
}
```

$$\text{------------ The End ------------}$$

---

## 作者：lsw1 (赞：0)

显然满足条件的数是数组中的最小值，否则最小值无法被比最小值大的数整除。

直接看数组中的数能否都被数组中的最小值整除即可，能则输出最小值，否则输出`-1`。

```cpp
#include <iostream>
using namespace std;
const int INF = 1e9;
const int MAXN = 1e5;
int a[MAXN + 5];
int main()
{
	int n;
	cin >> n;
	int minnum = INF;
	for(int i = 1;i <= n;i++)//找最小值
	{
		cin >> a[i];
		minnum = min(minnum,a[i]);
	}
	for(int i = 1;i <= n;i++)
	{
		if(a[i] % minnum != 0)//只要有一个不满足条件就输出-1
		{
			cout << -1;
			return 0;
		}
	}
	cout << minnum;//否则输出最小值
	return 0;
}
```

---

## 作者：songhongyi (赞：0)

我竟然天真的想着暴力能过……  
题意，对序列$S$，求一个数$S_i$，使得$\forall S_j$满足$S_i\mid S_j$。  
您可能觉得，唉，这不就是求$\gcd  $吗？对就是，那我们证明一下。结果为$S_i$，则所有数应该为$S_i\cdot k_j$，我们需要证明的就是$k$序列所有数互质，假设他们有公约数$m(m>1)$，则$S_i$应为$S_i\cdot m$，矛盾，所以$S_i$必定为$\gcd (S)$。

然后代码就呼之而出了，不要忘记如果$\gcd (S) \not \in S$，输出`-1`。
```cpp

// Problem : CF299A Ksusha and Array
// Contest : Luogu Online Judge
// URL : https://www.luogu.com.cn/problem/CF299A
// Memory Limit : 250 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
int a[ 100010 ];
int main()
{
    int n;
    cin >> n;
    for ( int i = 0; i < n; i++ )
    {
        cin >> a[ i ]; //输入
    }
    int gcd = a[ 0 ];
    for ( int i = 1; i < n; i++ )
    {
        gcd = __gcd( a[ i ], gcd );  //求gcd
    }
    for ( int i = 0; i < n; i++ )
    {
        if ( gcd ==a[i] ) //找到了
        {
            cout << a[ i ] << endl; //输出
            return 0;  // 程序结束
        }
    }
    cout << -1 << endl; // 无解，输出-1
}
```


---

## 作者：szbszb (赞：0)

首先说一句，这题目描述有错：这应该是找到一个可以整除所有数的数，而不是被整除（被整除的是求lcm了，考虑数据范围还得高精度）

所以，我首先考虑的是枚举每一个数，如果满足条件输出就行了，时间复杂度O（n2），考虑n<=1e5，是不可以的。

代码还是扔上来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100001],j,flag；
int main()
{
	scanf("%lld",&n);
	for (i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for (i=1;i<=n;i++)
	{
		flag=1;
		for (j=1;j<=n;j++)
		if (a[j]%a[i]!=1)
		{
			flag=0;
			break;
		}
		if (flag)
		{
			printf("%lld\n",a[i]);
			return 0;
		}
	}
	printf("-1");
	return 0;
}
```

然后就是两种正解了

1、求出它们的gcd，看看是否被包含于数组中。

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100001],i,g;
int main()
{
	scanf("%lld",&n);
	scanf("%lld",&a[1]);
	g=a[1];
	for (i=2;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		g=__gcd(g,a[i]);
	}
	for(i=1;i<=n;i++)
		if (a[i]==g)
		{
			printf("%lld\n",g);
			return 0;
		}
	printf("-1\n");
	return 0;
}
```
提醒：__gcd函数为NOIP/CSP-S所禁止，博主只是懒……如果不会求gcd（最大公约数）的话：

我们可以用欧几里德定理求gcd，具体的可以百度，代码很短，可以记一下：
```cpp
long long gcd(long long a,long long b)
{
	return b==0?a:gcd(b,a%b);
}
```
2、求出序列中的最小数，判断是否能整除所有数

这是为什么呢？因为如果不是最小数的话，它一定不能整除比它小的数，所以一个必要条件就是它必须是最小数。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100001],min1;
int main()
{
	scanf("%lld",&n);
	min1=1e11;
	for (i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		min1=min(min1,a[i]);//求出最小数
	}
	for (i=1;i<=n;i++)
		if (a[i]%min1!=0)//最小数不是，就直接输出-1
		{
			printf("-1");
			return 0;
		}
	printf("%lld",min1);	
	return 0;
}
```


---

## 作者：Ryan_ (赞：0)

第一道会题题解，也是通过的第一道灰题

题目大意：找出序列a中被所有数整除的数

思路非常简单，即求出所有数的最大公约数 

```
int long long GCD(int long long x,int long long y){
	if(y==0)return x;
	return GCD(y,x%y);
}
//主函数
gcd[1]=a[1];
for(int i=2;i<=n;i++)gcd=GCD(gcd,a[i]);
//这里不建议使用algorithm库里的__gcd函数，long long容易出现未知错误
                       
```



看上面的大佬求出最大公约数还穷举了gcd的因子，其实多此一举

只需要判断gcd是否在序列a中就可以了

这里给出证明（口胡）：

这里求出的gcd显然会小于等于数列a中最小的数

假设gcd存在一个因子满足条件，即这个因子出现在了数列a中，那么求得的gcd应该小于等于这个因子，矛盾

得证

csp rp--！！！~~反奶一口~~

AC code


```
#include<iostream>
using namespace std;
int n,a[1000005],gcd;
int GCD(int x,int y){
	if(y==0)return x;
	return GCD(y,x%y);
}
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    gcd=a[1];
    for(int i=2;i<=n;i++) gcd=GCD(gcd,a[i]);
    for(int i=1;i<=n;i++)
    {
        if(a[i]==gcd)
        {
            printf("%d",&a[i]);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
```


---

## 作者：　　　吾皇 (赞：0)

### 题目分析
```
不难得出，能整除序列a的所有数的那个数一定为x=gcd(a[1],a[2]...a[n])的因数，所以我们可以先求出来x的值，再暴力枚举x的所有因数判断是否在a中出现过(不会超时)，这里可以用桶装也可以用map存
```
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],x;
map<int,bool> q;
int main(){
	cin>>n;
	cin>>a[1],q[a[1]]=true,x=a[1];//这里要先将x赋值为a[1]要不然后面公约数没法求
	for(int i=2;i<=n;i++) cin>>a[i],q[a[i]]=true,x=__gcd(x,a[i]);//这里自带有最大公约数函数
	for(int i=x;i>=1;i--) if(x%i==0&&q[i]){//暴力枚举所有x的因数是否出现过，注意要枚举到1
		cout<<i;//有满足条件的就输出并停止程序
		return 0;
	}
	cout<<"-1";//如果没有输出-1
}
```


---

