# 2-3 Moves

## 题目描述

你的任务是求出从 $0$ 点到 $n$ 点的最短时间。

## 样例 #1

### 输入

```
4
1
3
4
12```

### 输出

```
2
1
2
4```

# 题解

## 作者：Moyyer_suiy (赞：12)

[原题传送门](https://www.luogu.com.cn/problem/CF1716A)
## 题意概括：
在一条直线上的点 $x$，一个单位时间可以任意向左或向右移动 $2$ 或 $3$ 格（即可以去到 $x+2$，$x+3$，$x-2$ 或 $x-3$。求从点 $0$ 到点 $n$ 最短需要多长时间。

## 解法：
贪心的思路。首先我们会发现，用无数个 $2$ 与 $3$ 可以凑出除了 $1$ 的所有正整数。例如：$4=2+2$，$7=2+2+3$，$11=2+3+3+3$。这就意味着当 $n\neq1$ 时，我们只需要不断向右走，不用调头向左走了。

其次，我们可以向右走 $2$ 或 $3$ 格，为了节省时间，我们需要尽可能的增加格数，即尽可能多的走 $3$ 格。举一个简单例子：当 $n=8$ 时，如果走 $2$ 格就是 $2+2+2+2=8$。但是最短的时间应该是 $3+3+2=8$。

此时就可以发现，当你不断的走 $3$ 步时会有三种情况：

$1.$ 正好能到达 $n$ 点。即 $n \bmod 3= 0$。

$2.$ 还需要再走一格才能到 $n$ 点。即 $n \bmod 3=1$。


$3.$ 还需要再走两格才能到 $n$ 点。即 $n \bmod 3=2$。

对于情况 $1$，此时最优解就是 $\dfrac {n}{3}$。

对于情况 $2$，我们可以想一下当 $n$ 为 $4$ 时，最优的方法是走两次两格。我们可以利用这个，让 $\dfrac {n-4}{3}+2$ ，表示让最后 $4$ 个走两次两格，其他继续都走 $3$ 格即可。

对于情况 $3$，比较容易了，就是前面 $n-2$ 格都照常按照 $3$ 格走，最后一次走一个两格即可。所以就是 $\dfrac{n}{3}+1$。

最后需要给 $n=1$ 时特判一下。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n==1) cout<<"2"<<endl;
		else
		{
			if(n%3==0) cout<<n/3<<endl;
			if(n%3==1) cout<<(n-4)/3+2<<endl;
			if(n%3==2) cout<<n/3+1<<endl;//三种情况
		}
	}
}
```
## 完

---

## 作者：Epi4any (赞：4)

> n $\leq$ $10^9
$

hmmm... 看来只能用数学的做法， dp 就算 $O(n)$ 都会 T 掉
### 思路
贪心，尽量跳三格，能不跳两格就不跳两格，尽量不往回跳。

具体实现按除三的余数分类：
1. 余 $0$ ： 这个好说，结果为 $n/3$ 。
2. 余 $1$ ： 如果 $n \geq 4$ 就可以跳两次次 $2$ 解决最后的 $4$，否则往前跳三格，往后跳两格解决最后的 $1$ 。
3. 余 $2$ ： 先跳 $n/3$ 个三格，在跳 $1$ 个两格。

代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int t, n;

void solve() {
	if (n % 3 == 0) cout << n / 3 << endl;
	else if (n % 3 == 2) cout << n / 3 + 1 << endl;
	else {
		if (n >= 4) cout << (n - 4) / 3 + 2 << endl;
		else cout << 2 << endl;
	}
}

int main() {
	t = read();
	while (t--) {
		n = read();
		solve();
	}
	return 0;
}
// 结尾警告：请勿抄袭
```

---

## 作者：cst_123 (赞：2)

### - [传送门](https://www.luogu.com.cn/problem/CF1716A)

------------

### 题意

给你 $T$ 个数，让你从 $0$ 出发，经过操作，直至到达该数。设你现在的位置为 $x$，你可以在此位置上移动到 $x-3$ , $x-2$ , $x+2$ , $x+3$ 这四者之一的位置，要你输出最少到达该数的步数。

### 思路

首先需要特判 $1$，因为 $1$ 我们虽然有先从 $0$ 到 $3$，再从 $3$ 退到 $1$。方法有很多，可不管怎么移动，最少就是两步。

之后因为最多移动 $3$ 格，我们的策略就是尽量到达该数，再进行判断，因此可将该数模 $3$。

- 若取模的值为 $0$，那么就可以输出该数除以 $3$ 的值。

- 若值是 $1$，举一个例子。
	```cpp
	7
	```
	这若按我们的思路，移动到 $x-1$ 的位置，再向 $1$ 一样，加上两步吗？

   可是这样是 $4$ 步了。但是从 $0$ 到 $3$，再从 $3$ 到 $5$，最后从 $5$ 到 $7$，只用了 $3$ 步。所以在遇上这种情况时，其实只用 $\frac{(x-1)}{3}+1$ 步。
   
   如果不理解，可以再试几个例子，如 $4$ 等等。
   
- 值是 $2$ 就简单了，因为我们可以从 $x-2$ 的位置，移动两步直接移动到 $x$，那么值是 $\frac{(x-2)}{3}+1$ 步。

### 代码

```cpp
while(T--){
	scanf("%lld",&x);
	if(x==1){
		printf("2\n");continue;
	}
	if(x%3==0)
		printf("%lld\n",x/3);
	else if(x%3==1)
		printf("%lld\n",(x-1)/3+1);
	else if(n%3==2)
		printf("%lld\n",(x-2)/3+1);
}
```


---

## 作者：TheCliffSwallow (赞：2)

### 题意简述
你在原点上，你要去点 $n$，每次你能往左或往右走 $2$ 或 $3$ 个单位，求你最少走几次能到点 $n$。
### 思路
把 $n$ 按模 $6$ 的余数讨论即可（按模 $3$ 的余数讨论也行），因为要最少，所以基本要让走 $3$ 个单位的次数最多。当 $n\bmod6=0$ 或 $3$ 时，走 $\dfrac{n}{3}$ 步，当 $n\bmod6=2$ 或 $5$ 时，再往左走 $2$ 个单位就可得到上面的情况，当 $n\bmod 6=4$ 或 $1$ 时，同理再往右走 $2$ 个单位也可得到上面的情况，所以当 $n\bmod 6=1$ 或 $2$ 或 $4$ 或 $5$ 时，走 $\dfrac n 3$ 步（向上取整）。最后不要忘记特判 $1$。
### AC Code
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string>
#include<cctype>
#define ll long long
#define ull unsigned long long
using namespace std;
ull t,n;
int main(){
	ios::sync_with_stdio(false);
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n;
		if(n==1){//特判n=1的情况
			cout<<2<<endl;
			continue;
		}
		if(n%6==0||n%6==3)	cout<<n/3<<endl;
		if(n%6==1||n%6==2||n%6==4||n%6==5)	cout<<n/3+1<<endl;
	}
  	return 0;
}

```


---

## 作者：LeNotFound (赞：2)

### 题意简述
一条坐标轴，初始位置在 $0$，每次操作可以向任意方向移动 $2$ 或 $3$ 格的距离，求到第 $n$ 个点距离的最小操作数。  

### 题目分析
首先易证 $n$ 的正负是不影响答案的，所以对于输入的 $n$ 可以直接取绝对值。  
然后我们可以手动算一些小的数据点试图找找规律。  
用数组的下标表示对应的坐标，下标对应的值为到达该点的最小操作数。  
```cpp
    nums[0]=0;
    nums[1]=2;
    nums[2]=1;
    nums[3]=1;
    nums[4]=2;	// 2,2
    nums[5]=2;	// 2,3
    nums[6]=2;	// 3,3
    nums[7]=3;	// 2,2,3
    nums[8]=3;	// 2,3,3
    nums[9]=3;	// 3,3,3
    nums[10]=4;	// 2,2,3,3
    nums[11]=4;	// 2,3,3,3
    nums[12]=4;	// 3,3,3,3
```
简单枚举了一小部分例子，可以发现，从 $4$ 开始，坐标增加 $3$ 最小操作数增加 $1$，换句话说就是**坐标值对应的最小操作数都是坐标值除以 $3$ 向上取整的结果。**  
找到规律了，可以写出如下代码。  

### 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
        {
            f=-1;
        }
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

void solution()
{
    double n=0;
    n=read();
    n=abs(n);
    if(n==0)
    {
        cout<<0<<endl;
    }
    else if(n==1)
    {
        cout<<2<<endl;
    }
    else if(n==2)
    {
        cout<<1<<endl;
    }
    else if(n==3)
    {
        cout<<1<<endl;
    }
    else
    {
        cout<<(int)ceil(n/3.0)<<endl;
    }
}

int main()
{
    int t=0;
    t=read();
    for(int i=0;i<t;i++)
    {
        solution();
    }
    return 0;
}
```

### 注意事项
* 由于计算需要向上取整，所以 $n$ 要定义为浮点数  
* 最后输出的时候要转换回整形，不能出现小数点后有零的情况

---

## 作者：_zexal_ (赞：1)

## 分析
一道分类讨论的题。无疑，如果我们能跳 $3$ 格，那么我们一定跳 $3$ 格，所以当 $n$ 为 $3$ 倍数时，我们的答案就是 $n/3$ 。如果我们跳三格还剩一格怎么办？我们就只需要在最后 $4$ 格跳 $2$ 格，前面跳 $3$ 格。如果我们跳三格剩两个，那么我们就最后 $2$ 格跳 $2$ 格，剩下全跳 $3$ 格即可。
## ACCode
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>t;
		if(t==1){// t=1的时候要特判。
		    cout<<2<<endl;
		    continue;
		}
		if(t%3==0) cout<<t/3<<endl;
		if(t%3==2) cout<<(t-2)/3+1<<endl;
		if(t%3==1) cout<<(t-4)/3+2<<endl;
	}
	return 0;
} 
```


---

## 作者：Jeremiahy (赞：0)

## 题意

初始在原点，每次可以往左或往右移动两步或三步，询问到达 $n$ 最少需要几步。

# 分析

考虑贪心，每次尽量移动三步，直到不能移动再移动其他的步数，这样我们可以按除以 $3$ 的余数来算：

被 $3$ 整除直接输出除以 $3$ 的结果，代表一直移动 $3$ 步到终点；如果余 $1$ 就输出除以 $3$ 的结果加 $2$，代表移动 $2$ 步再移动 $3$ 步来达到终点；余 $2$ 就输出除以 $3$ 的结果加 $1$，代表最后移动 $2$ 步。

但是有一种特殊情况：$n-4$ 为 $3$ 的倍数，此时 $n$ 除以 $3$ 的余数是 $1$，但是我们在 $n-4$ 的位置移动两个 $2$ 步比先移动 $3$ 步再移动 $2$ 步再移动 $3$ 步要更优，所以特判一下。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n;
signed main () {
	cin >> t;
	while (t--) {
		cin >> n;
		int cnt = n / 3, num = n % 3;
		if ((n - 4) % 3 == 0 && n - 4 >= 0)// 特殊情况
			cout << cnt + 1 << '\n';
		else {
			if (num == 0) // 3 的倍数
				cout << cnt << '\n';
			else if (num == 1) // 余 1
				cout << cnt + 2 << '\n';
			else	// 余 2
				cout << cnt + 1 << '\n';						
		}
	}
	return 0;
}
```


---

## 作者：Jasper08 (赞：0)

本来想用搜索做的，看下数据范围 $1\le n\le 10^9$ 直接炸掉了，那么对于每次询问只能用 $O(1)$ 的做法来求。

运用贪心的思路，能走 $3$ 步就尽量走 $3$ 步。

当 $n>1$ 时，分类讨论：

1. $n\bmod 3=0$，那么每一次都走 $3$ 步，最少需要 $n/3$ 次。

2. $n\bmod 3=1$，如果每一次都走 $3$ 步，那么最后会多出来 $1$。所以最后两次都应该走 $2$ 步，例如 $7=3+2+2,13=3\times 3+2+2$。总共需要走 $ (\lfloor n/3\rfloor-1)+2=\lfloor n/3\rfloor+1$ 次。

3. $n\bmod 3=2$，那么每一次都走 $3$ 步，最后一次走 $2$ 步即可。总共需要走 $\lfloor n/3\rfloor+1$ 次。

对于 $1$，我们可以先向前走 $3$ 步，再向后走 $2$ 步，一共需要 $2$ 次。

综上，答案即为：

$$
\begin{cases}
&2 &(n=1) \\
&\lceil n/3\rceil &(n>1)\\
\end{cases}
$$


完整代码：

```cpp
/**
Author: Jasper08
Quetion/Round: CF1716A. 2-3 Moves 
Date: 2022.8.4
**/

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int main() {
	int t;
	scanf("%d", &t);
	while (t -- ) {
		int n;
		scanf("%d", &n);
		int ans = (n == 1) ? 2 : (n+2)/3;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：zhicheng (赞：0)

### 思路

考虑贪心思想。肯定要先 $3$ 格 $3$ 格地向右跳。如果 $n$ 是 $3$ 的倍数，那么这样就可以了，次数为 $\dfrac{a}{3}$。如果余数是 $1$，那么我们跳到还剩 $4$ 格时停下来跳两次 $2$ 格即可。次数为 $\left\lfloor\dfrac{a}{3}\right\rfloor-1+2$，即为 $\left\lfloor\dfrac{a}{3}\right\rfloor+1$。如果余数是 $2$，那么跳到还剩 $2$ 格时停下来跳一次 $2$ 格即可，次数为 $\left\lfloor\dfrac{a}{3}\right\rfloor+1$。

还有就是要特判一下 $1$，右跳 $3$ 格，左跳 $2$ 格，共 $2$ 次。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&a);
		if(a==1){  //特判
			printf("2\n");
		}
		else if(a%3==0){  //以下分别为余数0,1,2
			printf("%d\n",a/3);
		}
		else if(a%3==1){
			printf("%d\n",a/3+1);
		}
		else{
			printf("%d\n",a/3+1);
		}
	}
}
```

---

## 作者：Failure_Terminator (赞：0)

## Problem

你的初始位置为 $0$。

你可以通过以下几种操作使位置变为 $n$：

- $x=x+2$ （即右移 $2$ 个单位长度）

- $x=x-2$ （即左移 $2$ 个单位长度）

- $x=x+3$ （即右移 $3$ 个单位长度）

- $x=x-3$ （即左移 $3$ 个单位长度）

求最少的操作次数。

## Solution

显而易见，对于 $n=1$，我们只需要右移 $3$ 个单位长度，再左移 $2$ 个单位长度即可，需 $2$ 次操作。

而对于 $n=2$ 和 $n=3$，只需 $1$ 次操作即可，原因显然。

对于 $n \ge 3$ 的情况，操作次数为 $\lceil n/3 \rceil$。

 _证明：_ 
 
当 $n \equiv 0 \pmod{3}$ 时，通过 $n/3$ 次每次增加 $3$ 单位长度的操作即可。

当 $n \equiv 1 \pmod{3}$ 时，通过 $n/3-2$ 次增加 $3$ 单位长度操作，再通过 $2$ 次增加 $2$ 单位长度操作即可。

当 $n \equiv 2 \pmod{3}$ 时，需通过 $n/3-1$ 次增加 $3$ 单位长度操作，再通过 $1$ 次增加 $2$ 单位长度操作。

不管怎么样，操作次数都为 $\lceil n/3 \rceil$。

 _证毕。_ 

对于每个询问，时间复杂度为 $O(1)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
void solve(){
    cin>>n;
    if(n<=3) cout<<1+(n==1);
    else cout<<(n+2)/3;
    cout<<endl;
} 
int main()
{
    cin>>t;
    while(t--) solve();
    return 0;
}
```

### 代码注释

知周所众，判断式为真时会返回 $1$。

`if(n<=3) cout<<1+(n==1);`

这一句话采用这一特性，等价于：

```cpp
if(n<=3){
    if(n==1) cout<<2;
    else cout<<1;
}
```
同样的，求 $\lceil n/3 \rceil$ 的操作也可以简化为 $(n+2)/3$。

Written by **haimo**

---

## 作者：luo_shen (赞：0)

**题意**  
有一条数轴，你站在数轴的原点上，你每一步可以选择向左或向右移动 $2$ 个单位长度或 $3$ 个单位长度，给定一个终点 $n(1 \le n \le 10^9)$，问最少需要几步才能到达终点。  
**分析**  
因为终点始终在数轴的正半轴上，所以我们可以贪心地考虑：每一步尽可能的向右走，即每一步向右走 $3$ 个单位长度，直到再向右走 $3$ 个单位长度就会到达终点的右侧为止，此时共走了 $\lfloor\frac{n}{3}\rfloor$ 步。  
此时就会出现 $3$ 种情况：分别为到达终点；还有 $1$ 个单位长度到达终点；还有 $2$ 个单位长度到达终点。用式子表示分别为 $\begin{cases} n \equiv 0 \pmod 3\\n \equiv 1 \pmod 3\\n\equiv 2 \pmod 3\end{cases}$。  
对于第一种情况，不需要过多的考虑，因为已经到达终点了。对于第三种情况，也不需要过多的考虑，只需下一步向右走 $2$ 个单位长度即可。唯一需要考虑的是第二种情况，不过也很容易发现，只需将最后一步的向右移动 $3$ 个单位长度变为两步向右移动$2$个单位长度即可。  
**但**有一个特殊情况：$n=1$。  
为什么说它特殊呢？因为它属于第二种情况，但在判断之前并未有过移动。我们找不到它向右移动 $3$ 个单位长度的一步，那就特殊判断 $n=1$，它只需向右走 $3$ 个单位长度，再向左走 $2$ 个单位长度，共 $2$ 步。  
最终式子如下:  
$$ ans=\lfloor\frac{n}{3}\rfloor+\begin{bmatrix}n \div 3\text{有余数}\end{bmatrix}$$  
**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n==1){//特判n=1的情况
			puts("2");
		}
		else{//其它情况
			printf("%d\n",n/3+(n%3>0));
		}
	}
	return 0;
}

```

---

## 作者：ChenLingHan (赞：0)

分五种情况考虑：

1. 当 $n=1$ 时单独考虑，单独输出答案 $2$。
2. 当 $n$ 既是 $2$ 的倍数，又是 $3$ 的倍数时，答案为 $n/3$。
3. 当 $n$ 只是 $2$ 的倍数时，答案为 $n/2$ 与 $n/3+1$ 的最小值。
4. 当 $n$ 只是 $3$ 的倍数时，答案为 $n/3$ 与 $n/2+1$ 的最小值。
5. 除以上四种情况之外，答案为 $n/3+1$ 与 $n/2+1$ 的最小值。

不需要过多解释，看我的分类大部分人就能想通为什么，故直接上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		if(n==1) cout<<2<<endl;
		else if(n%2==0&&n%3==0) cout<<n/3<<endl;
		else if(n%2==0) cout<<min(n/2,n/3+1)<<endl;
		else if(n%3==0) cout<<min(n/3,n/2+1)<<endl;
		else cout<<min(n/3+1,n/2+1)<<endl;
	}
	return 0;
}
```


---

## 作者：C_Cong (赞：0)

[博客传送门](https://blog.ccongcirno.cn/2022/08/06/%E6%B4%9B%E8%B0%B7%E9%A2%98%E8%A7%A3-CF1716A-%E3%80%902-3%20Moves%E3%80%91/#more)

### 题意翻译

现在有一条坐标轴，你现在坐标为 $0$ ，你每步可以走 $+3,+2,-3,-2$ 个单位问最少经过几步可以到达坐标为 $n$ 的点

### 解题过程

好吧，这其实是找规律题（毕竟是A题嘛）

首先就先列举出前几个坐标的情况

$n=1$ 时，最少步数为 $2 \ (+3-2)$

$n=2$ 时，最少步数为 $1 \ (+2)$

$n=3$ 时，最少步数为 $1 \ (+3)$

$n=4$ 时，最少步数为 $2 \ (+2+2)$

$n=5$ 时，最少步数为 $2 \ (+2+3)$

$n=6$ 时，最少步数为 $2 \ (+3+3)$

$n=7$ 时，最少步数为 $3 \ (+2+2+3)$

$n=8$ 时，最少步数为 $3 \ (+2+3+3)$

$n=9$ 时，最少步数为 $3 \ (+3+3+3)$

$......$

观察上面的情况，不难发现$n$每增加三个单位最少步数 $+1$（除了在 ${1,2,3}$ 这一段里 $n=1$ 时最少步数为 $1$ ）

其实如果不放心的话还可以再往下列举 ~~（比赛时我列到了15）~~

用式子表示大概就是 $\operatorname{ans} = \begin{cases} 2  \   (n=1) \\\\ n/3  \   (n \bmod \ 3 =0)\\\\ n/3+1  \   (n \bmod \ 3\neq 0)\end{cases} $

### 代码实现

------------

```cpp

#include<iostream>
#include<cstdio>
using namespace std;

int n,t,ans=0;

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        ans=0;
        scanf("%d",&n);
        if(n==1)
        {
            printf("2\n");
        }
        else
        {
            if(n%3!=0)
            {
                ans=n/3+1;
            }
            else
            {
                ans=n/3;
            }
            printf("%d\n",ans);
        }
        
    }
    scanf("%d",&n);
    return 0;
}

```

觉得有用顶上去才能让更多人看到哦awa



---

## 作者：cachejtt (赞：0)

## 题意
给你 $t$ 个数 $n$，从 $0$ 开始进行若干步操作，每一步操作可以将当前的数增加 $3$，增加 $2$，减少 $3$，或减少 $2$。问你要从 $0$ 变为 $n$ 最少需要几步。

## 思路
由于 $+3$ 肯定比 $+2$ 优，因此优先考虑 $+3$。考虑分类讨论 $n$。

1. 当 $n \bmod 3=0$ 时，步数显然为 $\dfrac{n}{3}$；

1. 当 $n \bmod 3=1$ 时，可以先通过 $\dfrac{n+2}{3}$ 步的 $+3$ 走到 $n+2$，再通过一步 $-2$ 走到 $n$，注意对 $n=1$ 特判；

1. 当 $n \bmod 3=2$ 时，可以先通过 $\dfrac{n-2}{3}$ 步的 $+3$ 走到 $n-2$，再通过一步 $+2$ 走到 $n$。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t,n;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    if(n==1)cout<<2<<endl;
    else if(n%3==0)cout<<n/3<<endl;
    else if(n%3==1)cout<<n/3+1<<endl;
    else if(n%3==2) cout<<n/3+1<<endl;
  }
  return 0;
}
```

---

