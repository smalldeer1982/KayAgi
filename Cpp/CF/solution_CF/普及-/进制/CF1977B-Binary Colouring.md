# Binary Colouring

## 题目描述

You are given a positive integer $ x $ . Find any array of integers $ a_0, a_1, \ldots, a_{n-1} $ for which the following holds:

- $ 1 \le n \le 32 $ ,
- $ a_i $ is $ 1 $ , $ 0 $ , or $ -1 $ for all $ 0 \le i \le n - 1 $ ,
- $ x = \displaystyle{\sum_{i=0}^{n - 1}{a_i \cdot 2^i}} $ ,
- There does not exist an index $ 0 \le i \le n - 2 $ such that both $ a_{i} \neq 0 $ and $ a_{i + 1} \neq 0 $ .

It can be proven that under the constraints of the problem, a valid array always exists.

## 说明/提示

In the first test case, one valid array is $ [1] $ , since $ (1) \cdot 2^0 = 1 $ .

In the second test case, one possible valid array is $ [0,-1,0,0,1] $ , since $ (0) \cdot 2^0 + (-1) \cdot 2^1 + (0) \cdot 2^2 + (0) \cdot 2^3 + (1) \cdot 2^4 = -2 + 16 = 14 $ .

## 样例 #1

### 输入

```
7
1
14
24
15
27
11
19```

### 输出

```
1
1
5
0 -1 0 0 1
6
0 0 0 -1 0 1
5
-1 0 0 0 1
6
-1 0 -1 0 0 1
5
-1 0 -1 0 1
5
-1 0 1 0 1```

# 题解

## 作者：_zqh_ (赞：9)

构造。

# Solution

考虑先将 $x$ 转成二进制的形式；

举个例子，$14$ 就转成 $0,1,1,1$（要倒着写）。

如果有两个 $1$ 相邻，就将其下一位加 $1$，将两个 $1$ 赋值为 $-1,0$；

即：
$$
2^{i} + 2^{i+1}=2^{i+2}-2^{i}
$$

若该位上的值被累加到 $2$，则将其赋值为 $0$ 并将下一位加 $1$，若下一位没有，则往末尾添加一个 $1$ 即可；

即：

$$
2^{i} \times 2=2^{i+1}
$$

举个例子，$14$ 可以被划分成：

$$
(0,1,1,1) \Rightarrow (0,-1,0,2) \Rightarrow (0, -1,0,0,1)
$$

[code](https://codeforces.com/contest/1977/submission/262773725).

---

## 作者：ikunTLE (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1977B)

### 思路

对于任意一个整数，我们可以将其转为二进制并逆转。

可以发现如果第 $A_i=A_{i+1}=1 $，即又两个 $1$ 相邻，那么就会累加到 $2$，就需要考虑进位了。

例如：$29$ 的二进制逆转后是 $1,0,1,1,1$，可以发现 $A_3=A_4=1$ 时，满足了上述的条件，可以将 $A_3$ 变成 $-1$，$A_4$ 变成 $0$，将 $A_5$ 加上 $1$。此时 $A_5=2$，需要进位。最终，整个序列变成了 $1,0,-1,0,0,1$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=32+10;
int t,n,a[N];
void solve(int x){
	int cnt=0,ans=0;
	//如果将其反转，那么a数组就是x的二进制。所以不反转刚好起到了转成二进制并反转的作用
	while(x){
		a[++cnt]=(x&1);
		x>>=1;
	}
	a[cnt+1]=0;
	for(int i=1;i<=cnt;++i){
		if(a[i]==2)//进位
			a[i]=0,++a[i+1];
		if(a[i]==1&&a[i+1]==1)//判断当有连续两个1的情况
			a[i]=-1,a[i+1]=0,++a[i+2];
	}
	for(int i=1;i<=cnt+1;++i)
		if(a[i]) ans=i;//找到最终的位数
	printf("%d\n",ans);
	for(int i=1;i<=ans;++i)
		printf("%d ",a[i]);
	printf("\n");
	return;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		solve(n);
	}
	return 0;
}
```

---

## 作者：BDFZ_hym_AK_hym_ing (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1977B)
### 题目大意
给你 $t$ 组数据，每组数据输入一个数字 $x$，并输出满足要求的数组。
算法：数学和一点点的暴力。
### 题目分析
首先分析要求 $2$ 和 $3$：$a_i$ 只能为 $1$，$0$ 或 $-1$ $(0\le i\le n-1)$，所以第一个想法是[平衡三进制](https://oi-wiki.org/math/balanced-ternary/)，但仔细看一眼，题目要求 $x=\displaystyle{\sum_{i=0}^{n-1}{a_i\cdot 2^i}}$，底数是 $2$，所以应该先转换成二进制，这时，因为 $1\le x<2^{30}$，长度最多为 $30$，同时也满足要求 $1$。  

所以，最后只要满足要求 $4$ 就行了：因为此时数字里只有 $1$ 和 $0$，$0$ 对要求没有影响，所以只要处理 $1$ 就行了。连续的 $1$，可以让他的尾部变成 $-1$，头部变成 $1$，中间变成 $0$ 就行了。还有一个易错点，**倒序输出**。  

举个例子：$14$ 的二进制是 $1110$，从后往前排查。倒数第一位是 $0$，可以跳过，剩下连续的三个 $1$ 的尾部变成 $-1$，中间都变成 $0$，头部变成 $1$，答案为 $100Z0$。  

证明：尾部变成 $-1$，头部变成 $1$ 后答案不变。首先，我们可以知道 $1Z=1$，$Z1=Z$，所以连续的 $1$ 可以看成最后一位的 $1$ 变成 $1Z$，向前面一直进位，所以中间变成 $0$，头部变成 $1$。  

注：以上的 $Z$ 替代 $-1$，尾部指连续的 $1$ 中的最后一个$1$，头部指连续的 $1$ 中第一个 $1$ 的**前面一格**。
### 代码
核心函数：
```cpp
//先转成二进制
string ans="";
while(s!=0)
{
	ans=char('0'+s%2)+ans;
	s/=2;
}
//ans长度最多为30，O（n）不会出事
ans='0'+ans;//加一个0方便操作
long long i,nl=0,sw=-1;
//以下Z代表-1 
for(i=ans.size()-1;i>=0;i--)
{
	if(ans[i]=='0')
	{
		if(nl>=2)
		{
			ans[i]='1';
			ans[sw]='Z';//这个也是代替-1
		}
		nl=0;
		sw=-1;
	}
	if(i!=0&&ans[i]=='1')//添加的那位0不用再次进位
	{
		if(nl==0)
		{
			sw=i;
		}
		else
		{
			ans[i]='0';
		}
		nl++;
	}
}
//特判
while(ans[0]=='0')//去前导0（虽然最多只有一个，but防止出事） 
{
	ans=ans.substr(1); 
}
cout<<ans.size()<<"\n";
for(i=ans.size()-1;i>=0;i--)//倒序输出
{
	if(ans[i]=='Z')
	{
		cout<<"-1 ";
	}
	else
	{
		cout<<ans[i]<<" ";
	}
}
cout<<"\n";
```

---

## 作者：_ayaka_ (赞：2)

### 题意

给一个数 $x$，求生成一个序列 $a$，长度为 $n$，满足以下条件：

- $0 \le n \le 31$；
- $a_{i}=1\lor 0\lor -1$；
- $ x = \displaystyle{\sum_{i=0}^{n }{a_i \cdot 2^i}} $；
- 不能存在 $a_{i}$ 满足 $ a_{i} \neq 0 $ 并且 $ a_{i + 1} \neq 0 $。
### 思路

首先乍一看条件三，立刻明白，可以先将 $x$ 转为二进制（如果不会可以看代码）。

同时由于条件四，我们要将两个相邻的 $1$ 进行转换。若 $ a_i = 1 $ 并且 $ a_{i + 1} = 1 $，则可以使 $a_i=-1$，$a_{i+1}=0$，$a_{i+2}+=1$。即可以将序列 $(0,1,1,0)$ 转换为 $(0,-1,0,1)$。

由于一个 $-1$ 之后必定是 $0$，所以我们无需考虑并非两个相邻的为 $1$ 以外的情况。不过需要注意进位的问题，不要忘了。


### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,x,a[35],cnt;
signed main(){
	cin>>t;
	while(t--){
		cin>>x;
		n=log2(x)+1;//位数
		a[n+1]=0;
		for(int i=1;i<=n;i++){//转二进制
			if(x%2==1) a[i]=1;
			else a[i]=0;
			x/=2;
		}
		for(int i=1;i<=n;i++){//转换并进位
			if(a[i]==2) a[i]=0,a[i+1]++;
			if(a[i]==1&&a[i+1]==1) a[i]=-1,a[i+1]=0,a[i+2]++;
		}
		for(int i=1;i<=n+1;i++) if(a[i]) cnt=i;//寻找最终位数
		cout<<cnt<<"\n";
		for(int i=1;i<=cnt;i++) cout<<a[i]<<" ";
		cout<<"\n";
	}
	return 0;
} 
```

---

## 作者：Chenyichen0420 (赞：1)

## 思路分析

题面一出来，就很容易想到先把这个数拆成二进制再处理。

我们注意到，拆出来后的不合法情况只有两个 $1$ 相邻的情况。然而，我们同时也知道，$2^i+2^{i+1}=2^{i+2}-2^i$，因此，$\texttt{0 1 1}$ 可以被替换成 $\texttt{1 0 -1}$。

此时就可以有两种思路：

1. 可以选择将连续的若干个 $1$ 替换成零，将最后一个 $1$ 替换成 $-1$，再将第一个 $1$ 前面的 $0$ 替换为 $1$。当然了，需要特判形如：$11\dots1011\dots$ 的情况。

2. 可以仅将两个连续的 $1$ 替换成 $\texttt{1 0 -1}$。这样子的话就不需要特判了，但是需要进行进位。

我采取的是第二种思路。代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, ans[32];
signed main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		memset(ans, 0, sizeof ans);
		cin >> n;
		for (int i = 0; i < 30; ++i)
			ans[i] = n & 1, n >>= 1;
		for (int i = 0; i < 30; ++i) {
			if (ans[i] == 2) ans[i + 1]++, ans[i] = 0;
			if (ans[i] == 1 && ans[i + 1] == 1)
				ans[i + 2]++, ans[i] = -1, ans[i + 1] = 0;
		}
		cout << "32\n";
		for (int i = 0; i <= 31; ++i)
			cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

# 思路

看到题目中的求和式，显然将 $x$ 拆分成二进制就能满足，但是要怎么办才能没有两个连续的 $1$ 呢？

设将 $x$ 拆分到数组 $a$，对于 $a_i=a_{i-1}=1$ 的情况，我们可以将它们变成 $0$ 并将 $a_{i+1}$ 加上 $1$，这样相当于多加了一个 $2^{i-1}$，所以我们应该把 $a_{i-1}$ 再减去 $1$，也就是设为 $-1$。注意如果 $a_i>1$ 要进位并清 $0$。

温馨提示：多测不清空，光速见祖宗。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114;
int t,n,a[N],cnt;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof a);
		cin>>n;
		cnt=0;
		while(n)
		{
			a[++cnt]=n&1;
			n>>=1;
		}
		for(int i=2;i<=cnt;i++)
		{
			if(a[i]>1)a[i+1]++,a[i]=0;
			if(a[i]&&a[i-1])a[i-1]=-1,a[i]=0,a[i+1]++;
		}
		while(a[cnt+1])cnt++;
		cout<<cnt<<"\n";
		for(int i=1;i<=cnt;i++)
		{
			cout<<a[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Alexxu2024 (赞：0)

# CF1977B 题解
## [题目传送门](https://www.luogu.com.cn/problem/CF1977B)


为了更好地分析题目，我们不妨设 $x=25$。

我们知道 $2^m+2^{m+1}=2^{m+2}-2^m$，证明如下：

$2^m+2^{m+1}$

$=2^m+2 \times 2^m$

$=(2+1) \times 2^m$

$=3 \times 2^m$

$2^{m+2}-2^m$

$=2 \times 2 \times 2^m-2^m$

$=(4-1) \times 2^m$

$=3 \times 2^m$

$\because 3 \times 2^m=3 \times 2^m$

$\therefore 2^m+2^{m+1}=2^{m+2}-2^m$

然后，将 $x$ 转为 $2$ 进制并逆序写出。

$$1\ 0\ 0\ 1\ 1$$

如果没有“不存在一个 $i$ 使得 $a_i\neq0$ 且 $a_{i+1}\neq 0$”这个约束，这个序列就是答案。如果有这个约束，那就把刚才的结论 $2^m+2^{m+1}=2^{m+2}-2^m$ 用上，如果存在一个 $i$ 使得 $a_i\neq0$ 且 $a_{i+1}\neq 0$，就把 $a_i$ 减去 $1$，把 $a_{i+2}$ 增加 $1$。

再处理一下进位等情况即可。

$x=25$ 时，数列长度最小为 $6$，数列构造为 $1\ 0\ 0\ -1\ 0\ 1$。


## 代码
```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int a[40];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		// cout << n << endl;
		for(int i=1;i<=35;i++){
			a[i]=0;//多测不清空，爆零两行泪
		}
		int cnt=1;
		while(n>0){
			a[cnt]=n%2;//n转2进制
			n/=2;
			cnt++;
		}
		cnt--;//别忘了-1
		// cout << cnt << endl;
		for(int i=1;i<=cnt;i++){
			if(a[i]>=2){//处理进位
				a[i+1]+=a[i]/2;
				a[i]%=2;
				if(i+1>cnt){
					cnt=i+1;//可能数组长度要更新
				}
			}
			if(a[i]==1&&a[i+1]==1){//处理连续的1
				a[i]=-1;
				a[i+1]=0;
				a[i+2]++;
				if(i+2>cnt){
					cnt=i+2;//可能数组长度要更新
				}
			}
		}
		cout << cnt << endl;//输出长度
		for(int i=1;i<=cnt;i++){
			cout << a[i] << " ";//输出数组
		}
		cout << endl;//要换行
	}
	return 0;
}
```

---

## 作者：WOL_GO (赞：0)

看见有形如 $2^k$ 这种结构，不难想到二进制拆分。

如果 $a_i=a_{i-1}=1$ 我们需要考虑进位，即 $2\times 2^{a_i}=2^{a_i+1}$。

举个例子：`13=1 1 0 1=1 0 -1 0 1`。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
long long t,n,x,a[maxn],cnt;
void solve(){
	cin>>x;
	n=__lg(x)+1;
	a[n+1]=0;
	for(int i=1;i<=n;i++){
		if(x&1)a[i]=1;
		else a[i]=0;
		x>>=1;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==2)a[i]=0,a[i+1]++;
		else if(a[i]==1&&a[i+1]==1){
			a[i]=-1;
			a[i+1]=0;
			a[i+2]++;
		}
	}
	for(cnt=n+1;cnt>=1;cnt--){
		if(a[cnt]!=0)break;
	}
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++)cout<<a[i]<<" ";
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)solve();
	return 0;
} 
```

---

## 作者：ttq012 (赞：0)

简单构造。

首先可以先全填写 $0$ 和 $1$。对于一段全 $1$ 的子串，手摸几组数据可以发现，将最低位填为 $-1$，其他的位置全部填为 $0$，上一位填为 $1$ 是满足条件的。一直执行这个过程直到不存在这样连续超过一个 $1$ 的子串为止。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#ifdef int
#define inf (7611257611378358090ll/2)
#else
#define inf 0x3f3f3f3f
#endif
using namespace std;
const int N = 1000100;
int a[N];
auto main() [[O3]] -> signed {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (n == 1) {
            cout << "1\n1\n";
        } else {
            F(i, 0, 100) a[i] = 0;
            F(i, 0, 30) {
                if (n >> i & 1) {
                    a[i] = 1;
                } else {
                    a[i] = 0;
                }
            }
            F(i, 0, 29) {
                if (a[i] && a[i + 1]) {
                    int p = i;
                    while (a[p]) p++;
                    // [i, p)
                    a[p] = 1;
                    a[i] = -1;
                    F(j, i + 1, p - 1) {
                        a[j] = 0;
                    }
                }
            }
            int lim = 40;
            while (!a[lim]) {
                lim--;
            }
            cout << lim + 1 << '\n';
            F(i, 0, lim) cout << a[i] << ' ';
            cout << '\n';
        }
    }
}
```

---

## 作者：sbno333 (赞：0)

我们假设没有 $-1$ 的情况，这是容易维护的，转成二进制即可。

我们这个基础上加入 $-1$，对于每个极长连续的一的子串，为了没有不重新处理前面，所以我们不妨认为只能在高位将 $0$ 变掉。

代入 $-1$ 肯定要减少，放到高位肯定不行，只放到低位也会减少，所以我们要让原来增加，我们将这个串不妨设为最低，即假设此时处理 $x=2^k-1$。

发现 $2^k-1=1\times2^k+(-1)\times2^0$，于是就是最低位变 $-1$，最高位前面的 $0$ 变 $1$，剩下的变 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[39];
void _main(){
	int x;
	cin>>x;
	memset(a,0,sizeof(a));
	for(int i=0;i<=29;i++){
		if(x&(1ll<<i))
		a[i]=1;
	}
	int z;
	z=0;
	while(z<=32){
		if(a[z]&&a[z-1]){
			a[z-1]=-1;
			while(a[z]){
				a[z]=0;
				++z;
			}
			a[z]=1;
		}
		z++;
	};
	cout<<32<<endl;
	for(int i=0;i<32;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl; 
}
signed main(){
	std::ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--){
		_main();
	} 
	return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

### 题目理解：
- 简单构造。

- 根据 $x =\sum\limits_{i=0}^{n-1}a_i2^i$,可以将题目转化为若干个二的不同幂次相加减。那么可以先设所有操作都为加，即为将 $x$ 变为二进制。

- 但题目中还有一个要求：不存在一个 $i$ 使 $a_i\neq0$ 且 $a_{i+1}\neq 0$。但二进制中不免会出现邻位与本位都为 $1$ 的情况，所以要进一步改进现在的构造。

- 分析二进制每一位特性，发现 $a_i+a_{i-1}\times2$（$a_i$ 为二进制的第 $i$ 位表示的数且 $1\le i$）。所以 $a_i2^i+a_{i+1}2^{i+1}=3a_i2^i$。同理，想让 $a_{i+1}$ 变为 $0$，就可以将 $a_i=-1,a_{i+1}+1$ 即可，这样 $a_{i+1}2^{i+1}$ 就与 $a_{i+2}2^{i+2}-2a_i2^i$ 同价了。但不免 $a_{i+2}$ 会变为 $2$，因为 $a_{i+3}2^{i+3}=2a_{i+2}2^{i+2}$ 同价，那么就可以向 $i+3$ 位进位。这样就可以避免后效性（之所以不选择 $a_i$ 替换为 $0$ 是为了避免前效性）。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum[1010];
long long k[1010];
int main()
{
	int t;
	cin>>t;
	sum[1]=1;
	for(int i=2;i<=32;i++)sum[i]=sum[i-1]*2;
	while(t--)
	{
		long long x;
		cin>>x;
		memset(k,0,sizeof(k));
		int id=0;
		for(int i=1;i<=32;i++)
		{
			if(sum[i]>=x)
			{
				id=i;
				break;
			}
		}
		long long last=x;
		queue<int>st;
		int cnt=0;
		while(last>0)
		{
			st.push(last&1ll);
			last/=2;
			cnt++;
		}
		for(int i=1;i<=cnt;i++)
		{
			k[i]=st.front();st.pop();
		}
		for(int i=1;i<=cnt;i++)
		{
			if(k[i]==2)
			{
				k[i]=0;
				k[i+1]++;
				if(i==cnt)cnt++;
			}
			if(k[i]==1 && k[i+1]==1)
			{
				k[i]=-1;
				k[i+1]=0;
				k[i+2]++;
				if(i+2>cnt) cnt=i+2;
			}
		}
		cout<<cnt<<endl;
		for(int i=1;i<=cnt;i++)
		{
			cout<<k[i]<<" ";
		}
		cout<<endl;
	}
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1977B (luogu)](https://www.luogu.com.cn/problem/CF1977B)

[CF1977B (codeforces)](http://codeforces.com/problemset/problem/1977/B)

# 解题思路

考虑通用做法。

我们发现如果直接用二进制来表示的话这个数会只包含 $0,1$ 这两个数字。

发现这时阻碍我们构造的是连续的数字 $1$。

考虑消除连续的数字 $1$。

容易发现连续的数字 $1$ 可以转化成将这一段最高位的数字 $1$ 的下一位进位，并将这一段最低位的数字 $1$ 退位的操作。

容易证明这样构造一定两两之间不会冲突。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n;
ll ans[40],k,ans2[40],sum;
void solve()
{
	cin>>n;
	sum=0,k=0;
	ll lst=n;
	while(lst)
		ans[++k]=lst%2,lst/=2;
	/*
	19:10011-> 11001  -1 0 1 0 1
	*/
	forl(i,1,k+1)
	{
		if(ans[i]==2)
			ans[i]=0,ans[i+1]++;
		if(ans[i]==1)
			sum++;
		else
		{
			if(sum>=2)
			{
				ans[i]++;
				forr(j,i-1,i-sum)
					ans[j]=0;
				ans[i-sum]=-1;
			}
			sum=ans[i]==1;
		}
	}
	k+=ans[k+1]==1;
	cout<<k<<endl;
	forl(i,1,k)
		cout<<ans[i]<<' ',ans[i]=0;
	ans[k+1]=0;
	cout<<endl;
}
int main()
{
	IOS;
	t=1;
	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：CaoSheng_zzz (赞：0)

### 思路
对于每一个数 $ n $ 我们将他转换为二进制，对于每一个二进制下连续的 $ 1 $ 我们可以将这个位置上的数变成 $ - 1 $ 对于高这个位置一位的那个数 $ + 1 $，对于连着的 $ - 1 $ 我们可以将本位变成 $ 1 $ 将高于这个位置一位的那个数 $ - 1 $ 一直这样维护下去就是正确答案。因为题目要求输出数组长度 $ \le 32 $ 而这样一直维护下去数组长度最大为 $ 31 $ 因为 $ n \le 2^{30} $ 所以此解法为正解，代码太短就不展示了。

---

