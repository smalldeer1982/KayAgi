# Remainder

## 题目描述

Aiming_High神仙给你一个由$n$位数字组成的数，且保证这个数字没有前导零，且每一位数字要么是$0$要么是$1$。

Aiming_High神仙需要你对这个数进行若干次操作（可能是$0$次）。每次操作中，你可以更改其中的任何数位，把这个数位上的数字从$1$变成$0$或从$0$变成$1$。操作后的数可能带有前导零，但并不影响这个问题。

Aiming_High神仙还给了你两个数字$x$，$y$。你要做的是最小化操作次数，使得操作后的数除以$10^x$的余数等于$10^y$。

## 样例 #1

### 输入

```
11 5 2
11010100101
```

### 输出

```
1
```

## 样例 #2

### 输入

```
11 5 1
11010100101
```

### 输出

```
3
```

# 题解

## 作者：封禁用户 (赞：4)

# 题目大意

有一个长度为 $n$ 的数字串，可以进行若干次操作，使得某一位把这个数位上的数字从 $1$ 变成 $0$ 或从 $0$ 变成 $1$。现在求在操作次数最少的情况下，使得操作后的数除以 $10^{x}$ 的余数刚好等于 $10^{y}$，数据保证有解。

# 题目解法

将某一位把这个数位上的数字从 $1$ 变成 $0$ 或从 $0$ 变成 $1$，其实就是取反，操作后的数除以 $10^{x}$ 的余数刚好等于 $10^{y}$，很容易发现只要求后 $x$ 位是否等于 $10^{y}$，举个栗子：$n=7$，$s=1101101$，$x=6$，那么有：

$$1101101 \bmod  1000000=101101$$

不难发现 $101101$ 刚好位数等于 $x$。

那么重点来了：如何让 $s \bmod 10^{x}\equiv 10^{y}$ 呢？

我们把样例割下来研究一下：

### 样例 #1

$n=11$，$x=5$，$y=2$，$s=11010100101$，因为只要求后 $x$ 位，所以 $s=00101$，去零得 $s=101$，因为 $10^{y}$ 等于 $100$，所以只要将 $s$ 的最后一位变成 $0$ 即可。总次数为 $1$，输出即可。

### 样例 #2

$n=11$，$x=5$，$y=1$，$s=11010100101$，因为只要求后 $x$ 位，所以 $s=00101$，去零得 $s=101$，因为 $10^{y}$ 等于 $10$，所以将 $s$ 的第一位变成 $0$ 得 $s=01$，再把第一位变成 $1$，将第二位变成 $0$，总次数为 $3$ 次，输出即可。

通过样例可以得知，做法如下：

- $i=n-y-1$ 并且 $s_{i}=0$ 时 $cnt+1$。

- $i \ne n-y-1$ 并且 $s_{i}=1$ 时 $cnt+1$。

所以代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,x,y,a[200050],cnt=0;
	char s[200050];
    cin>>n>>x>>y>>s;
    for(int i=n-x;i<n;i++){
        if(i==n-y-1&&s[i]=='0')cnt++;
        else if(i!=n-y-1&&s[i]=='1')cnt++;
    }
    cout<<cnt;
    return 0;
}
```
~~都看到这了，点个赞再关注我不过分吧~~

---

## 作者：holy_vortex (赞：1)

# 题目大意
已知有个$01$串长度为$n$，可以将任意位取反，使得 $n$ 到 $n-y+1$ 位为 $0$ ， $n-y$ 位为 $1$ ， $n-y-1$ 到 $n-x+1$ 位为 $0$ 。
# 样例1解释
原本字符串： $11010100101$

改变后字符串： $11010100100$

只改变了最后一个字符，所以答案为 $1$
# 思路
直接枚举，分三段： $n$ 到 $n-y+1$ 位； $n-y$ 位； $n-y-1$ 到 $n-x+1$ 位
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200000 + 5;//别忘加五
int n, x, y, num;
bool a[N];
char s;
int main(){
	cin >> n >> x >> y;
	for(int i = 1; i <= n; i++){
		cin >> s;//字符一个一个读入
		a[i] = s - '0';//将字符转化为数字
	}
	for(int i = n; i >= n - y + 1; i--)
		if(a[i]) num++;
	if(a[n - y] == 0) num++;
	for(int i = n - y - 1; i >= n - x + 1; i--)
		if(a[i]) num++;
	cout << num << endl;
	return 0;
}
```
## 附：
这是本蒟蒻写的第一篇题解，万望管理员通过！！！

---

## 作者：A_Big_Jiong (赞：1)

~~昨晚刚打完CF的欢乐掉分场，今天又来水题解，真的欢乐~~

------------
# 题目大意
已知有个01串长度为n，有修改操作可以将0或1取反（QAQ），求解最少需要多少次修改，原01串(int)%10^x==10^y
# 思路
作为div.3的A绝对也难不到哪去，我们就先从需要满足的条件开始
### 010101001....%10^x==10^y
- 因为一个01串对10^x取模就相当于取01串的x位（从右边为第一位）

- 而10^x就对应着只有第x位为1

- 综其上述，其实问题就转换为后x位中需要进行几次操作才可以保证除第y+1位为1外，剩余的为0

- 所以遍历后x位，若非y+1位为1,转换为0；若y+1位为0，转换为1。
- 同时，使用num纪录操作总数

具体的解释见代码注释

# 代码
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<vector>
#include<string>//请自觉无视
using namespace std;
const int maxn=200005;
int n,x,y,num;
char ch;
int a[maxn];
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++){
		cin>>ch;//将01串转换为int类型的0或1分别存储
		a[n-i+1]=ch-'0';//倒序存储
	}
	y++;//将y转换为y+1
	for(int i=1;i<=x;i++){//遍历
		if(i!=y)  if(a[i])  num++;//如果第非y位1，转换为0
		if(i==y)  if(!a[i])  num++;//如果第y位为0，转换为1
	}
	printf("%d\n",num);//输出总次数
	return 0;
}
```


---

## 作者：blsya23a2 (赞：0)

## 分析
设输入的数为 $a$。为使 $a\bmod 10^x=10^y$，$a$ 的后 $x$ 位中，第 $x-y$ 位必须为 $1$，而其他位必须为 $0$。因此，只需要遍历 $a$ 的后 $x$ 位并计算不符合规律的位数，就得出了需要操作的次数。
## 代码
```python
a,b,c = map(int,input().split())
d,e = list(input())[-b:],0
for f in range(b):
    if f+c == b-1:
        if d[f] == '0':
            e += 1
    else:
        if d[f] == '1':
            e += 1
print(e)
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1165A)

估值快掉光了，赶紧来水一发。

这题的题意其实还能再简化一下。题目要我们做的其实就只是把长度为 $n$ 的数的最后 $x$ 位都变为 $0$，但倒数第 $y+1$ 位得是 $1$。

因为一个数 $k$ 对 $10^x$ 进行取模就是取 $k$ 的最后 $x$ 位。我们再来想一下 $10^y$ 是多少。很明显，$10^y$ 等于 $1$ 后面跟着 $y$ 个 $0$，$1$ 前面有无数个前导 $0$。那么 $10^y$ 又有几位，很明显，有 $y+1$ 位，且只有第 $y+1$ 位为 $1$。

现在，我们就已经能完全读懂题意了。题目让我们把长度为 $n$ 的数字 $s$ 的后 $x$ 位只有倒数第 $y+1$ 位为 $1$，$y+1$ 的前面和后面都为 $0$，这样才能构成 $10^y$。

那么，代码就已经很好实现了。我们设 $s$ 的最后一位为第 $n-1$ 位，接着从 $s$ 的第 $n-i$ 位向后枚举到第 $n-1$ 位。如果当前这一位不为第倒数 $y+1$ 位且这一位为 $1$，那么我们需要把这一位变为 $0$，答案加一。如果当前这一位为倒数第 $y+1$ 位，且这一位为 $0$，那么我们就需要把这一位变为 $1$，答案加一。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,ans=0;
string s;
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	cin>>s;
	for(register int i=1;i<=x;i++)
		if(i==y+1&&s[n-i]=='0') ans++;
		else if(i!=y+1&&s[n-i]=='1') ans++;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Prolystic (赞：0)

## Part 0 前言

[原题目(洛谷)](https://www.luogu.com.cn/problem/CF1165A)

[原题目(CodeForces)](https://codeforces.com/contest/1165/problem/A)

## Part 1 题意简述

* 给定三个整数 $n,x,y$ 以及一个二进制数 $num$。

* 可以进行多次操作(也可以是 $0$ 次)，每次操作可以任选一位将其取反。

* 求出最少要进行多少次操作才可以使得 $num\bmod (10^x)_{2} = (10^y)_2$。

注意：

* 模数是 $(10^x)_2$ 为二进制。得数是 $(10^y)_2$ 二进制。

* 这个二进制数长度最大 $2\times 10^{5}$。

## Part 2 分析

思路如下：

二进制中模的意义依然和十进制中一样，及一个二进制数模以 $(10^x)_2$ 的意义是保留这个二进制数的最后 $x$ 位。

为了方便模拟，我们将这个字符串倒序存储，方法与高精度相同。

于是，我们可以知道，要进行操作的区间只有 $1$ 至 $x$ 位。那么，$num\bmod (10^x)_2 = (10^y)_2$ 的意义就是在 这个区间内只有第 $y$ 位为 $1$，其余位都为 $0$。

那做法就不难想到了，输入数据，依次扫描 $1$ 至 $x$ 位，把除了第 $y$ 位的数字都改成 $0$，标记操作次数即可。

注意：此处 $y$ 在倒序之后要自增 $1$，不然倒序之后会少计算一位。

此做法只需扫描 $1$ 到 $x$ 位，时间复杂度 $O(x)$，常数最大 $2\times 10^5$，属于很优秀的复杂度了。

## Part 3 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
bool arr[MAXN];
int n,x,y;
int ans;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>x>>y;
    for(int i = 1;i<=n;i++){
        char ch;
        cin>>ch;
        arr[n-i+1] = ch-'0';
    }
    y++;
    for(int i = 1;i<=x;i++){
        if(i==y){
            if(arr[i]==0){
                ans++;
            }
        }else if(i!=y){
            if(arr[i]==1){
                ans++;
            }
        }
    }
    cout<<ans;
    return 0;
}

```

## Part 4 测试信息

![](https://cdn.luogu.com.cn/upload/image_hosting/mq7cbqwy.png)

[记录](https://codeforces.com/contest/1165/submission/199637315)

创造和谐洛谷，拒绝抄袭题解。

适度刷题益脑，沉迷刷题伤身。

拒绝盗版代码，提倡自我思考。

健康学习ＯＩ，快乐美好生活。

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1165A)
## 题目大意

你一个由 $n$ 位数字组成的数由 $0,1$ 组成，改变其中的一些位，使这个数除以 $10^x$ 的余数等于 $10^y$。

## 分析

既然是要取余于 $10^x$。那么，我们只需要考虑最后 $x$ 位就行了。且想要余数等于 $10^y$ 只要让第 $y$ 位上为 $1$ 其余都为 $0$。

- 如果第 $i$ 位为 $1$ 要修改一次。

- 如果第 $y$ 位为 $0$ 要修改一次。

然后就可以了。

## 下面是 AC 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int st[200005],n,x,y,ans=0;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
	{
		char s;
		cin>>s;
		st[i]=s-'0';
	}
	for(int i=n;i>=n-x+1;i--)
	{
		if(st[i]==1&&i!=(n-y))
		{
			ans++;
		}
	}
	if(st[n-y]==0)
	{
		ans++;
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：zk_y (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1165A)

题目给定我们一个包含 $0$ 和 $1$ 的字符串，让我们计算这个数除以 $10^x$ 的余数为 $10^y$。

那么，既然是要取余于 $10^x$。那么，我们只需要考虑最后 $x$ 位就行了。（从最后一位开始数）

然后在考虑余数，我们知道要想余数为 $10^y$。那么，我们只需要让第 $i$ 位是 $1$，其余位都是 $0$ 就行了（从最后一位开始数）。注意：这里的的输入和最后的找位数需要注意。

那我们需要按照这个规律来：（需要 $i$ 在 最后 $x$ 位内）

> 如果第 $i$ 位上的数是 $1$，但是 $i\ne y$，那么我们就需要对这一位进行调整。
> 
> 如果第 $y$ 位上的数是 $0$，那么我们就需要对这一位进行调整。

最后，我们的代码就完成了。

---
# AC代码

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
const int N=2e5;
int num[N],n,x,y,t,ans;
char z;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++){
		scanf(" %c",&z);
		num[i]=int(z-'0');
	}
	for(int i=n;i>=n-x+1;i--){
		if(num[i]==1&&i!=n-y){
			ans++;
		}
	}
	if(num[n-y]==0)ans++;//特判一下
	printf("%d",ans);
    return 0;
}
```


---

## 作者：ssSSSss_sunhaojia (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/CF1165A)
# 思路：
题目要求这个数除以 $10^x$ 余数为 $10^y$，我们只用管这个数的后 $x$ 位，因为前面几位上的数并不会对余数产生影响。

因此，想要满足这个数除以 $10^x$ 余数为 $10^y$，对于这个数的后 $x$ 位，就得满足只有倒数第 $y+1$ 位为 $1$，其余均为 $0$。

我们将这个数后 $x$ 位以数组的方式记录下来，再判断每一位是否满足条件，不满足总次数加 $1$，最后输出总次数就行了。

# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL n, x, y, a[220000], ans; 
char ch; 
int main(){
	IOS;
	cin >> n >> x >> y; 
	for(re int i = 1; i <= n; i ++) {
		cin >> ch;
		if(i >= n - x + 1) a[i] = ch - 48; 	//记录成数组
	}
	for(re int i = n - x + 1; i <= n; i ++)
		if(i != n - y&& a[i] == 1 || i == n - y && a[i] == 0) ans ++; //是否满足条件
	cout << ans; //输出
	return 0;
}

```

---

## 作者：zljhenry (赞：0)

这个题上面那篇题解已经非常的详细了。

这里我将一个非常好用而快速的东西 —— 位运算。

这个东西的思想就是将一个 01 串压缩为一个二进制的变量，并对这个变量的每一个位进行修改，查询。速度非常快。

先来熟悉一下几个位运算的操作：

1. ```|``` ：按位或，将每一位比较，如果有一个是真，答案就是真，如果都是假，答案就是假。
2. ```&``` ：按位与，将每一位比较，如果都是真，答案就是真，否则就是假。
3. ```^``` ：按位异或，将每一位比较，如果不一样，答案就是真，如果一样，答案就是假。
4. ```<<``` ：左移，将这个串整体往右移，空出的是 0 ，相当于乘 2。
5. ```>>``` ：右移，将这个串整体左移，相当于除 2。



然后是一些高级的操作：

1. 把右数第 $k$ 位变成 1 ：```x = x | ( 1 << ( k - 1 ) )```
2. 把右数第 $k$ 位变成 0 ：```x = x & ! ( 1 << ( k - 1 ) )```
3. 取右数第 $k$ 位：```x = x >> ( k - 1 ) & 1```、

那么就可以写出代码了：

```cpp
for(int i=1;i<=n;i++){
	char k;
	cin>>k;
	int w=n-i+1;
	if(k=='1') f = f | (1 << (w - 1)); //将每一个数字存入
	if(k=='0') f = f | ! (1 << (w - 1));
}
for(int i=1;i<=x;i++){
	if(i!=y) if(f >> (i - 1) & 1) ans++; //进行判定
	if(i==y) if(!(f >> (i - 1) & 1)) ans++;
}
cout<<ans<<endl;
```
但这个方法只能使用 32 位所以在进行小数量极的运算是可以使用。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500005];
unsigned long long f;
int main(){
	int n,x,y;
	cin>>n>>x>>y;
	y+=1;
	int ans=0;
	if(n>=32){
		for(int i=1;i<=n;i++){
			char k;
			cin>>k;
			a[n-i+1]=k-'0';
		}
		
		for(int i=1;i<=x;i++){
			if(i!=y) if(a[i]) ans++;
			if(i==y) if(!a[i]) ans++;
		}
		cout<<ans<<endl;
	}
	else{
		for(int i=1;i<=n;i++){
			char k;
			cin>>k;
			int w=n-i+1;
			if(k=='1') f = f | (1 << (w - 1));
			if(k=='0') f = f | ! (1 << (w - 1));
		}
		for(int i=1;i<=x;i++){
			if(i!=y) if(f >> (i - 1) & 1) ans++;
			if(i==y) if(!(f >> (i - 1) & 1)) ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```



---

