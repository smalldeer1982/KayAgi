# Sign Flipping

## 题目描述

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ , where $ n $ is odd. You are allowed to flip the sign of some (possibly all or none) of them. You wish to perform these flips in such a way that the following conditions hold:

1. At least $ \frac{n - 1}{2} $ of the adjacent differences $ a_{i + 1} - a_i $ for $ i = 1, 2, \dots, n - 1 $ are greater than or equal to $ 0 $ .
2. At least $ \frac{n - 1}{2} $ of the adjacent differences $ a_{i + 1} - a_i $ for $ i = 1, 2, \dots, n - 1 $ are less than or equal to $ 0 $ .

Find any valid way to flip the signs. It can be shown that under the given constraints, there always exists at least one choice of signs to flip that satisfies the required condition. If there are several solutions, you can find any of them.

## 说明/提示

In the first test case, the difference $ (-4) - (-2) = -2 $ is non-positive, while the difference $ 3 - (-4) = 7 $ is non-negative.

In the second test case, we don't have to flip any signs. All $ 4 $ differences are equal to $ 0 $ , which is both non-positive and non-negative.

In the third test case, $ 7 - (-4) $ and $ 4 - (-6) $ are non-negative, while $ (-4) - (-2) $ and $ (-6) - 7 $ are non-positive.

## 样例 #1

### 输入

```
5
3
-2 4 3
5
1 1 1 1 1
5
-2 4 7 -6 4
9
9 7 -4 -2 1 -3 9 -4 -5
9
-4 1 9 4 8 9 5 1 -9```

### 输出

```
-2 -4 3
1 1 1 1 1
-2 -4 7 -6 4
-9 -7 -4 2 1 -3 -9 -4 -5
4 -1 -9 -4 -8 -9 -5 -1 9```

# 题解

## 作者：huayucaiji (赞：3)

本题的题意就是：我们要通过改变数的符号，来让 $\forall i\in [0,1]$， $a_{i+1}-a_i\geq 0$ 的数量等于 $a_{i+1}-a_i\leq 0$ 的数量。（尽管题目和这个不一样，当时其实本质上没有差别，可以推导）

所以我们可以用平时数学中的一个结论：

如果 $a<0,b>0$，则 $a-b<0,b-a>0$。因此我们这个题，只要让序列里的数一正一负即可。这样满足了条件。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=100;

int n,a[maxn];

signed main() {
	
	int t=read();
	while(t--) {
		n=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
			if(i&1&&a[i]>0) {
				a[i]=-a[i];
			}
			if(i%2==0&&a[i]<0) {
				a[i]=-a[i];//改变正负
			}
		}
		for(int i=1;i<=n;i++) {
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Andrewzdm (赞：2)

非常简单的一道构造题。

首先，$n$ 必定为奇数，那么 $n-1$ 必定为偶数，即相邻两数差的个数也是偶数。

题目里说了至少有 $\dfrac{n-1}{2}$ 个差为非负，也至少有 $\dfrac{n-1}{2}$ 个差为非正。

注意到相邻两数计算的方法为 $a_{i+1}-a_i$，那么不难想到我们只要让 $a_i$ 的符号按“正、负、正、负、正……”的顺序排列就可以了。这样一来，差的正负就与两数绝对值的大小关系无关了，差一定是按照“负、正、负、正、负……”的顺序排列的，满足题目要求。

尽管 $0$ 既不是正数也不是负数，但是我们不需要考虑 $0$。

上代码：
```cpp
#include<iostream>
#include<cmath>
using namespace std;

void solve()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
	    int x;
	    cin >> x;
	    if(i & 1)
	        cout << abs(x) << ' ';
	    else
	        cout << -abs(x) << ' ';
	}
	cout << endl; 
	return;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：159号程序员 (赞：1)

$update$ $20200706$  添加一组数据。

$update$ $20200711$ 添加上负数的括号。

这道题有些难度，是一道构造题。

我们可以由公式 正负数-非正数=非负数，非正数-非负数-非正数。

可以证明：$(-1) - (-3) = 2$，$0 - 4 = (-4)$。

所以，可以写出 _AC Code_

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T, n, a;
	cin >> T; //输入数据组数
	while(T--)
	{
		cin >> n;
		for(int i = 0; i < n; i++) //循环遍历
		{
			cin >> a;
			if(i % 2) //如果为奇数
			{
			    if(a > 0) //进行公式判断
			    {
			        cout << a << " ";
			    }
			    else
			    {
			        cout << -a << " ";
			    }
			}
			else //否则为偶数
			{
				if(a < 0) //进行公式判断
				{
				    cout << a << " "; //输出后面要加空格
				}
				else
				{
				    cout << -a << " ";
				}
			}
		}
		cout << endl; //记得换行！
	}
	return 0;
}
```

下面提供一组数据：

输入：

```cpp
3
1 5 -8
4 7 -1
6 -7 -2

```

输出：
```cpp
-1 5 -8
-4 7 -1
-6 7 2
```

引用区：

感谢[liqingyang](https://www.luogu.com.cn/blog/llqyy/solution-cf1375a)的题解告诉了我这个蒟蒻开头构造的公式！

---

## 作者：gyh20 (赞：1)

构造。

题目给出 $n$ 为奇数，不超过 $\dfrac{n-1}{2}$ 个大于等于或小于等于可以视为一大一小相邻，而正数一定大于负数，所以可以直接奇数位置输出正，偶数位置输出负。

1min AC

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,ans,a[1000002];
int main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)printf("%d ",(i&1)?read():-read());
		puts("");
	}
}

```


---

## 作者：Aw顿顿 (赞：0)

期末考完了，做一做简单构造题。

期末考完了，当然期末考也完了，本来希望期末考完不要完，但是期末考完还是发现就算全部写完还是完。

## 题意概述

给出一个数列，改变其中数字的符号，要有接近半数的数差是正数，接近一半的数差是负数。

这个一半准确来说是 $\dfrac{n-1}{2}$。

注意多测。

## 解法分析

显然，所以相邻的数必然满足其中之一，但是如果我们一个个去调整过于浪费时间了，所以我们可以不管。

不管是什么意思呢？也就是说，输入的数不管正负，反正我让他一正一负，这样必然有半数满足其中一个条件，另外的半数满足另一个条件。

其实这个 $\dfrac{n-1}{2}$ 的要求很有意思，差不多就是 $n\div 2$ 的下取整，因为是奇数，所以必然是分成 $a$ 和 $a+1$ 两个部分，其中 $2a+1=n$。

那么很容易就能写出代码了。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,s,b;
signed main(){
	cin>>x;
	for(register int i=0;i<x;++i){
		cin>>s;
		for(register int j=0;j<s;j++){
			cin>>b;
			b=abs(b);
			if(j&1)cout<<-b<<'\n';
			else cout<<b<<'\n';
		}
	}
}
```

[>>点击此处查看 $\rm\color{lime}AC$ 记录<<](https://www.luogu.com.cn/record/35159995)

---

## 作者：SymphonyOfEuler (赞：0)

题目大意：

给你一个数列$a$，长度为$n$，$n$为奇数，你可以反转一些符号，满足一下两点条件：

- 至少$n-1/2$个相邻差$ai+1-a_i$ $i=1,2...n-1$ 大于等于0.

- 至少$n-1/2$个相邻差$ai+1-a_i$ $i=1,2...n-1$ 小于等于0.

这题不算太难，需要知道：


- 正负数$-$非正数$=$非负数

- 非正数$-$非负数$=$非正数

验证一下：

$(-7)-(-3)=10$

$50-70=-20$

就可以推出正数，负数……这样来，差是正负数，则我们就一个非负数，一个非正数来就行。

**思路：**

```
int T；
	cin >> T; 
	while(T--){//多组数据
		cin >> n;
```


所以我们输入进来，判断非零并且奇数是一个情况，偶数一个情况，输出即可。

```
if(x%2!=0){//奇数
	if(x>0) cout<<x<<' ';
	else cout<<-1*x<<' ';
}
else {//偶数
	if(x>0) cout<<x<<' ';//反过来
	else cout<<-1*x<<' ';
}
```



---

## 作者：youngk (赞：0)

这道题目的要求是要给出一个奇数长度$n$的序列$a_{1} \ldots a_{n}$，需要让序列中所有相邻的后一项减前一项的差值$a_{i+1}-a_{i}$有$\frac{n-1}{2}$为大于等于$0$，有$\frac{n-1}{2}$为小于等于$0$，通过翻转元素(在元素前面乘$-1$)，给出一个可行解满足上诉的条件。

作为$CF$常见的构造题，我们当然希望大于等于$0$的插值和小于等于$0$的插值能够均匀分布，而且多思考一下就会发现如果$x \geq 0,y \leq 0$，那么$x - y \geq 0$，$y - x \leq 0$，因此只有将序列中奇数项全部变成$\leq 0$，偶数项变为$\geq 0$（反之也可以）,就可以满足插值分成一半$\geq 0$，一半$\leq 0$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define endl '\n'
#define lowbit(x) x & -x
#define inf 0x3f3f3f3f
#define maxn 100

int x, n, t;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> x;
            cout << (i & 1 ? -abs(x) : abs(x)) << ' ';
        }
        cout << endl;
    }
    return 0;
}
```


---

## 作者：wmy_goes_to_thu (赞：0)

比赛时的经历：

先翻译了一下，大概长这样：

一个长度为 $n$ 的数列 $a$（$n$ 是奇数），更改 $i$ 的意思是把 $a_i$ 变成 $-a_i$。定义 $a$ 的差分数列 $b$ 是一个长度为 $n-1$ 的数列，满足 $b_i=a_{i+1}-a_i$，现在你需要更改一些数，使得有 $\frac{n-1}{2}$ 个数是 $\geq 0$ 的，另外 $\frac{n-1}{2}$ 个数是 $\leq 0$ 的。

因为前面对后面没有影响，所以可以 dp!

比赛时我用的 dp 状态是这样的：

$dp_{i,j,0/1}$ 表示前面 $i$ 个数中的差分数组有 $j$ 个是 $\geq 0$ 的，第 $i$ 个数翻不翻转，我们还需要记录一个 $p$ 数组，就是在第 $i$ 个数翻不翻转的情况下第 $i-1$ 个数翻不翻转。

然后转移一下就行了，最后需要递归输出。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],dp[105][105][2],p[105][105][2];
void vist(int n,int hf,int f)
{
	if(n==1)
	{
		if(f)printf("%d",-a[1]);
		else printf("%d",a[1]);
		return;
	}
	int pf=p[n][hf][f];
	int ppf,pppf;
	if(f==0)ppf=1;
	else ppf=-1;
	if(pf==0)pppf=1;
	else pppf=-1;
	int cz=a[n]*ppf-a[n-1]*pppf;
	if(cz>=0&&dp[n-1][hf-1][pf])vist(n-1,hf-1,pf);
	else vist(n-1,hf,pf);
	if(f)printf(" %d",-a[n]);
	else printf(" %d",a[n]);
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof(a));
		memset(dp,0,sizeof(dp));
		memset(p,0,sizeof(p));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		dp[1][0][0]=dp[1][0][1]=1;
		for(int i=2;i<=n;i++)for(int j=0;j<i;j++)
		{
			if(j==0)
			{
				int cz1=a[i]-a[i-1],cz2=a[i]+a[i-1];
				if(cz1<=0&&dp[i-1][j][0])
					dp[i][j][0]=1,p[i][j][0]=0;
				else if(cz2<=0&&dp[i-1][j][1])
					dp[i][j][0]=1,p[i][j][0]=1;
				cz1=-a[i]-a[i-1],cz2=a[i-1]-a[i];
				if(cz1<=0&&dp[i-1][j][0])
					dp[i][j][1]=1,p[i][j][1]=0;
				else if(cz2<=0&&dp[i-1][j][1])
					dp[i][j][1]=1,p[i][j][1]=1;
				continue;
			}
			int cz1=a[i]-a[i-1],cz2=a[i]+a[i-1];
			if((cz1>=0&&dp[i-1][j-1][0])||(cz1<=0&&dp[i-1][j][0]))
				dp[i][j][0]=1,p[i][j][0]=0;
			else if((cz2>=0&&dp[i-1][j-1][1])||(cz2<=0&&dp[i-1][j][1]))
				dp[i][j][0]=1,p[i][j][0]=1;
			cz1=-a[i]-a[i-1],cz2=a[i-1]-a[i];
			if((cz1>=0&&dp[i-1][j-1][0])||(cz1<=0&&dp[i-1][j][0]))
				dp[i][j][1]=1,p[i][j][1]=0;
			else if((cz2>=0&&dp[i-1][j-1][1])||(cz2<=0&&dp[i-1][j][1]))
				dp[i][j][1]=1,p[i][j][1]=1;
		}
		int hf=n>>1;
		if(dp[n][hf][0])vist(n,hf,0);
		else vist(n,hf,1);
		puts("");
	}
	return 0;
}
```

---

## 作者：_cmh (赞：0)

简单的构造题。

数组都不用。

输入 $x$ ，因为要满足题目的要求，所以满足以下条件：

- 当 $i$ 为奇数时，$x>0$ 。

- 当 $i$ 为偶数时，$x<0$ 。

然后代码就很简单了，珂以边输入边判断。

上代码 ~~（气势恢宏的一句）~~：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
int T,n,x;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			if((i%2&&x<0)||(i%2==0&&x>0)) cout<<-x<<" ";
			else cout<<x<<" ";
		}
		cout<<endl;
	}
    return 0;
}
```
求赞！

---

