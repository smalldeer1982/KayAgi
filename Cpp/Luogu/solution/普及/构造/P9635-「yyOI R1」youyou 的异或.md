# 「yyOI R1」youyou 的异或

## 题目背景

youyou 非常菜，但是他很喜欢构造奇奇怪怪的数列。

## 题目描述

本题评测方式为 **Special Judge**。

youyou 很喜欢数列，所以他想让你构造一个长度为 $n$ 的**正整数**序列 $\{a_i\}$。

youyou 很喜欢[异或](https://oi-wiki.org/math/bit/#%E4%B8%8E%E6%88%96%E5%BC%82%E6%88%96)，所以他要求构造出的序列满足 $a_1 \oplus a_2 \oplus a_3 \oplus \cdots \oplus a_{n-1} \oplus a_n = n$（记 $\oplus$ 表示异或）。

youyou 非常讨厌相同的数，所以他要求序列中所有数**互不相同**。

但 youyou 不想让这个序列的数太大，所以他要求序列中所有数的总和不超过 $n^2$，即 $\displaystyle\sum_{i=1}^n a_i \le n^2$。

现在你需要构造出一个序列从而满足 youyou 的所有要求。如果无解，输出 `-1` 。如果有多种答案，输出任意一个序列即可。

你需要回答 $T$ 组数据。

## 说明/提示

### 样例解释
对于 $n = 1$ 时，一种可行的解为 $\{1\}$。

对于 $n = 2$ 时，一种可行的解为 $\{3,1\}$。

对于 $n = 5$ 时，一种可行的解为 $\{1,4,5,3,6\}$，因为 $1 ⊕  4 ⊕ 5  ⊕ 3 ⊕ 6 = 5$，且 $1+4+5+3+6 =19\le 5^2$，序列中每个数也互不相同。


### 数据范围
对于 $5\%$ 的数据，$n \le 5$。

对于 $15\%$ 的数据，$n \le 10$。

对于 $40\%$ 的数据，$n \le 1000$。

对于 $70\%$ 的数据， $n \le 10^5$。

对于 $100\%$ 的数据，$1 \le n \le 5 × 10^5$，$1 \le T \le 10$。


## 样例 #1

### 输入

```
3
1
2
5```

### 输出

```
1
3 1
1 4 5 3 6```

# 题解

## 作者：continueOI (赞：11)

写在最前面：~~该题解不保证是正解~~，仅给广大谷友们提供写这种构造题的一种思路。

赛时做第一题，点进去看了一下，决定找规律。人工爆算后发现本人还是太蒻了，于是写了个没有任何减枝的爆搜打了个表，代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[100],flg;
int T,n;
void dfs(int x,int s,int sum2){//纯纯爆搜
	if(flg==1) return;
	if(s==n){
		int sum=0;
		for(int i=1;i<=n*n;i++){
			if(vis[i]==1){
				sum^=i;
			}
		}
		if(sum==n){
			for(int i=1;i<=n*n;i++){
				if(vis[i]==1){
					cout<<i<<' ';
				}
			}
			flg=1;
			cout<<'\n';
		}
	}
	for(int i=x+1;i<=n*n-sum2;i++){
		vis[i]=1;
		dfs(i,s+1,sum2+i);
		vis[i]=0;
	}
}
signed main(){
	for(n=1;n<=30;n++){
		flg=0;
		if(n==3){
			cout<<-1<<'\n';continue;
		}
		dfs(0,0,0);
	}
	return 0;
}
```
相信大家都会写这种爆搜，于是我们就能得到以下表：

```
1
1 3
-1
1 2 3 4
1 2 4 5 7
1 2 3 4 5 7
1 2 3 4 5 8 14
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 16 25
1 2 3 4 5 6 7 8 9 11
……省略n=10以后的内容，如想了解请自己复制代码运行打表
```

注意，以下讨论排除 $n \le 5$ 的情况。

可以发现，$n$ 能被 $4$ 整除时答案就是从 $1$ 到 $n$ 的一个数列，而 $n$ 除以 $4$ 余 $2$ 时答案前 $n-1$ 项为 $1$ 到 $n-1$，第 $n$ 项为 $n+1$。

如 $n=8$ 时答案为 `1 2 3 4 5 6 7 8`，$n=6$ 时答案为 `1 2 3 4 5 7`。

接下来棘手的便是 $n$ 除以 $4$ 余 $1$ 或 $3$ 的情况。

我们继续观察表从 $n=9$ 到 $n=28$ 的答案数列，容易发现，答案前 $n-2$ 项也是 $1$ 到 $n-2$ 的一个数列，而第 $n-1$ 项的值为不小于 $n$ 的最小的 $2$ 的 $k$ 次幂，如 $n=9$ 时答案第 $n-1$ 项为 $16$，而 $n=17$ 时为 $32$。

现在对于 $n$ 除以 $4$ 余 $1$ 或 $3$ 的情况只用求最后一项了！容易发现，当 $n$ 除以 $4$ 余 $1$ 时，最后一项为 $2^k+n$ ,当 $n$ 除以 $4$ 余 $3$ 时，最后一项为 $2^k+n-1$。

接下来我们证明一下为什么这样构造是对的。

### 前置芝士：

$a$ 为正整数。

性质一：如若 $a$ 是偶数，则 $a \oplus (a+1) = 1$。

显然 $a$ 与 $a+1$ 仅只有末位不同。

性质二：如若 $a$ 是奇数，则 $a \oplus 1 = a-1$。

显然 $a$ 的末位为 $1$，异或 $1$ 后只有末位会变成 $0$，其他位不变。

### 证明：

当 $n$ 除以 $4$ 余 $0$ 时，可以将第 $2$ 项到第 $n-1$ 项两个两个匹配成奇数组符合性质一的算式，再异或上第 $1$ 项的 $1$，即有偶数个 $1$ 异或，异或和显然为 $0$，$0 \oplus n=n$。

当 $n$ 除以 $4$ 余 $2$ 时，可以将第 $2$ 项到第 $n-1$ 项两个两个匹配成偶数组符合性质一的算式，再异或上第 $1$ 项的 $1$，即有奇数个 $1$ 异或，异或和显然为 $1$。因为 $n+1$ 为奇数，所以 $1 \oplus (n+1)=n$。

当 $n$ 除以 $4$ 余 $1$ 时，可以将第 $2$ 项到第 $n-2$ 项两个两个匹配成奇数组符合性质一的算式，再异或上第 $1$ 项的 $1$，即有偶数个 $1$ 异或，异或和显然为 $0$。而对于已有的限制条件而言，

$$2^k \oplus (2^k+n)=n$$

为什么呢？$2^k$ 的二进制形式除了首位为 $1$ 以外其他位都为 $0$，明显 $2^k+n$ 与 $2^k$ 的二进制形式不同的位与 $n$ 的二进制形式中为 $1$ 的位一一对应，所以异或结果就为 $n$。

当 $n$ 除以 $4$ 余 $3$ 时，可以将第 $2$ 项到第 $n-2$ 项两个两个匹配成偶数组符合性质一的算式，再异或上第 $1$ 项的 $1$，即有奇数个 $1$ 异或，异或和显然为 $1$。而很明显$1 \oplus 2^k = 2^k+1$，对于已有的限制条件而言，

$$(2^k+1) \oplus (2^k+n-1)=n$$

为什么呢？$2^k+1$ 的二进制形式除了首位和末位为 $1$ 以外其他位都为 $0$，明显除了末位以外 $2^k+n-1$ 与 $2^k+1$ 的二进制形式不同的位与 $n$ 的二进制形式中为 $1$ 的位一一对应。因为 $n$ 为奇数，所以 $2^k+n-1$ 末位为 $0$,$(2^k+1)$ 末位为 $1$，所以上式异或结果就为 $n$。

最后因为 $n \le 5$ 的情况比较特殊，为了书写方便，特判即可。

AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		if(n==1){cout<<1<<'\n';continue;}
		if(n==3){cout<<-1<<'\n';continue;}
		if(n==5){cout<<"1 2 4 5 7\n";continue;}
		for(int i=1;i<=n-2;i++)
			cout<<i<<' ';
		if(n%4==0)
			cout<<n-1<<' '<<n<<'\n';
		if(n%4==1){
			int sum=1;
			while(sum<n)
				sum*=2;
			cout<<sum<<' '<<sum+n<<'\n';
		}
		if(n%4==2)
			cout<<n-1<<' '<<n+1<<'\n';
		if(n%4==3){
			int sum=1;
			while(sum<n)
				sum*=2;
			cout<<sum<<' '<<sum+n-1<<'\n';
		}
	}
	return 0;
}
```

于是我们就用了普及-的思维 A 了一道绝对不是普及-难度的构造题。

写在最后：~~话说这场比赛哪一道题是普及-啊？~~

---

## 作者：youyou2007 (赞：10)

这里是出题人题解。
# Solution

## 5pts

随便手模两下即可算出 $n \le 5$ 的情况，注意 $n=3$ 无解即可得分。 

## 15pts

可以通过各种奇奇怪怪的爆搜来通过 $n \le 10$ 的数据。

##  40pts

给一些 $O(n^2)$ 的算法通过的数据，但我没有想出来怎么用这个复杂度构造。![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)

## 100pts

异或均用 $\oplus$ 代替。

**做本题前需要先明确几个比较简单的性质：**（$a$ 是正整数）

+ 性质 $1$：如果 $a$ 为偶数，那么 $a \oplus (a+1)=1$。

这个性质很好理解：$a$ 与 $a+1$ 只有最低位是不同的，所以异或以后为 $1$。

+ 性质 $2$：如果 $a$ 为正整数，那么 $a \oplus a = 0$，$a \oplus 0 = a$。

+ 性质 $3$：由第一个性质还可以得出，如果 $a$ 是偶数，那么有 $a \oplus 1 = a + 1$  ，如果 $a$ 是奇数，那么有 $a \oplus 1 = a-1$。

明确了上述性质，我们很快会有一个想法：可以考虑将一个偶数与比该偶数多 $1$ 的奇数视为一组，这样每一组的异或和为 $1$。而每两组的异或和为 $0$。

即，当 $a$ 是偶数时，$a \oplus (a+1)=1$，$a \oplus (a+1) \oplus (a+2)\oplus (a+3)=0$。

 发现两组是 $4$ 个数，根据 $n \% 4$ 的余数进行分类讨论构造：

+ #### $n \equiv 0\pmod {4}$ 时：

考虑构造序列 $\{1,2,3,4,...,n\}$。因为除 $1$ 与 $n$ 以外，剩下的数为 $4k + 2$ 个，为 $2k+1$ 组，所以除 $1$ 与 $n$ 以外的其他数异或和为 $1$ ，再有 $1 \oplus 1\oplus n = n$，所以构造成立。

例如 $n = 8$ 时可以构造序列为 $\{a\} = \{1,2,3,4,5,6,7,8\}$。

+ #### $n \equiv 1\pmod {4}$ 时：

考虑构造序列 $\{2,3...,n-2,n,n+1,n+2\}$，因为除 $n$ 以外，剩下的数为 $4k$ 个，可以分成  $2k$  组，所以异或和为 $0$，再有 $0 \oplus n = n$，所以构造成立。

例如 $n = 9$ 时可以构造序列为 $\{a\} = \{2,3,4,5,6,7,9,10,11\}$。

+ #### $n \equiv 2\pmod {4}$ 时：

考虑构造序列 $\{1,2,3,...,n-1,n+1\}$，因为除 $1$ 与 $n + 1$ 以外，剩下的数为 $4k$ 个，可以分成  $2k$  组，所以异或和为 $0$，再有 $0 \oplus 1 \oplus n+1 = n$，所以构造成立。

例如 $n = 6$ 时可以构造序列为 $\{a\} = \{1,2,3,4,5,7\}$。

+ #### $n \equiv 3\pmod {4}$ 时：

  考虑构造序列 $\{2,3...,n-2,n-1,n+1,n+2\}$，因为除 $n-1$ 以外，剩下的数为 $4k+2$ 个，可以分成  $2k+1$  组，所以异或和为 $1$，再有 $1 \oplus n-1 = n$，所以构造成立。

例如 $n = 7$ 时可以构造序列为 $\{a\} = \{2,3,4,5,6,8,9\}$。

+ #### 边界 & 无解情况（$n \le 3$ 时）

在 $n$ 很小时需要注意不能按照上述方式构造，否则可能存在问题。

当 $n = 3$ 时，通过手模可知没有构造方案满足要求，所以无解。

$n=2$ 与 $n=1$ 在样例中已经给出一组可行解，因此不再赘述。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, T;
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		if(n == 1)
		{
			puts("1");
			continue;
		}
		if(n == 3)
		{
			puts("-1");
			continue;
		}
		if(n % 4 == 0)
		{
			for(int i = 1; i <= n; i++)
			{
				printf("%d ", i);
			}
		}
		else if(n % 4 == 1)
		{
			for(int i = 2; i < n - 1; i += 2)
			{
				printf("%d %d ", i, i + 1);
			}
			printf("%d %d %d ", n, n + 1, n + 2);
		}
		else if(n % 4 == 3)
		{
			for(int i = 2; i < n - 1; i += 2)
			{
				printf("%d %d ", i, i + 1);
			}
			printf("%d %d %d ", n - 1, n + 1, n + 2);
		}
		else
		{
			for(int i = 1; i <= n - 1; i++)
			{
				printf("%d ", i);
			}	
			printf("%d ", n + 1);
		}
		puts("");
	}
	return 0; 
}
```

---

## 作者：Im_airman (赞：9)

因为本人太菜了，大佬们的题解都不懂，这里提供另一种解题思路。

观察题面给出了 $n\le10$ 的暴力分，不妨先打出暴力代码寻找规律。

```cpp
void dfs(int ne,int sum,int id,int xr){
	if(id>n||sum>n*n||ed)	return;
	if(id==n && xr==n){
		for(int i=1;i<=n;i++)	printf("%lld ",a[i]);
		cout<<endl;
		ed=1;
		return ;
	}
	for(long long i=ne+1;i<=n*n;i++){
		a[id+1]=i;
		dfs(i,sum+i,id+1,xr^i);
	}
}
```
可以发现：

当 $x=6$ 时：输出 $1$  $2$ $3$ $4$ $5$ $7$

当 $x=7$ 时：输出 $1$  $2$ $3$ $4$ $5$ $8$ $14$

当 $x=8$ 时：输出 $1$  $2$ $3$ $4$ $5$ $6$ $7$ $8$

$\dots$

当 $x=10$ 时： 输出 $1$ $2$ $3$ $4$ $5$ $6$ $7$ $8$ $9$ $11$
 
可以发现输出由一段长 $n-2$ 的有序数列和两个数组成。因此只需要枚举其中一位，再由异或和计算出另一位判断是否符合条件，即总和是否小于 $n^2$ 和去重。
时间复杂度为 $O(Tn)$。接下来只需笔算出 $n\le5$ 的情况，就可以过掉此题啦。
```cpp
#include<bits/stdc++.h>
#define int long long
inline int read(){
	int s=0,f=1;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-'?-1:1 ,ch=getchar();
	while(isdigit(ch))	s=s*10+ch-'0',ch=getchar();
	return s*f;
} 
using namespace std;
int T,n;
signed main(){
	T=read();
	while(T--){
		n=read();	
		if(n==1) cout<<"1"<<"\n";
		else if(n==2) cout<<"1 3"<<"\n";
		else if(n==3) cout<<"-1"<<"\n";
		else if(n==4) cout<<"1 2 3 4"<<"\n";
		else if(n==5) cout<<"1 3 4 5 6"<<"\n";
		else{//n大于5
			int sum=0,ans=0;
			for(int i=1;i<=n-2;i++){
				ans^=i,sum+=i;
				cout<<i<<" ";
			}
			for(int i=n-1;i<=n*n-sum;i++){//从n-2+1开始搜到使总和达到n*n的最大的i
				if(((ans^i)^n)+sum<=n*n && ((ans^i)^n)>n-2){
					cout<<i<<" "<<((ans^i)^n)<<"\n";
					break;
				}
			}
		}	
	}
} 



---

## 作者：T7_Daniel_clz_gy_dw (赞：5)

这道题打表的思路其它题解都讲的差不多了，但是看不到纯打表的代码我就不太理解了，这篇题解讲述的是纯打表的代码。

但为什么要打表呢？这道题我们看到，这道题上来就给出 $t≤10$ 的优秀数据，但是里面暗藏玄机，我们直接暴力的话只能拿到 $15$ 分，所以，打表肯定会为我们带来便利，因此，我们选择打表(程序写法各位大佬都讲的差不多了，本蒟蒻也就不啰嗦了)。

首先重新掏出暴力程序：
```
#include<bits/stdc++.h>

using namespace std;

bool vis[100],flg;

int n;

void dfs(int x,int s,int sum2) {//暴力

    if(flg==1) return;

    if(s==n) {

        int sum=0;

        for(int i=1; i<=n*n; i++)

            if(vis[i]==1)

                sum^=i;

        if(sum==n) {

            for(int i=1; i<=n*n; i++)

                if(vis[i]==1)

                    cout<<i<<' ';

            flg=1;

            cout<<'\n';

        }

    }

    for(int i=x+1; i<=n*n-sum2; i++) {

        vis[i]=1;

        dfs(i,s+1,sum2+i);

        vis[i]=0;

    }

}

int main() {

    //int t;cin>>t; 

    /*

    while(t--){

        int n;cin>>n;

        dfs(0,0,0);

    }

    */

    for(n=1;n<=10;n++) cout<<dfs(0,0,0);

    return 0;

}
```
此时我们运行一下，就会发现输出为(当然你也可以使用 freopen )：
```
1

1 3

-1

1 2 3 4

1 2 4 5 7

1 2 3 4 5 7

1 2 3 4 5 8 14

1 2 3 4 5 6 7 8

1 2 3 4 5 6 7 16 25

1 2 3 4 5 6 7 8 9 11
```
通过这个表，拿捏这道题不是轻轻松松吗？

纯打表程序附上：
```
#include<bits/stdc++.h>

using namespace std;

int main() {

    int t;cin>>t;

    while(t--){

        int n;cin>>n;

        if(n==1) cout<<"1\n";

        else if(n==2) cout<<"1 3\n";

        else if(n==3) cout<<"-1\n";

        else if(n==4) cout<<"1 2 3 4\n";

        else if(n==5) cout<<"1 2 4 5 7\n";

        else if(n==6) cout<<"1 2 3 4 5 7\n";

        else if(n==7) cout<<"1 2 3 4 5 8 14\n";

        else if(n==8) cout<<"1 2 3 4 5 6 7 8\n";

        else if(n==9) cout<<"1 2 3 4 5 6 7 16 25\n";

        else cout<<"1 2 3 4 5 6 7 8 9 11\n";

    }

    return 0;

}
```
打表是最快的呢，时间复杂度可是 $O(t) $。

---

## 作者：sbno333 (赞：2)

这道题可能有很多做法，这里只分享我的。

我们可以将答案设为 $a$ 数组。

可以先将 $1\sim n-2$，填入 $a$ 数组。
```cpp
		int x;
		x=0;
		for(int i=1;i<=n-2;i++){
			a[i]=i;
			x^=a[i];
		}
```

特别的，$x$ 表示当前**填入**的数的异或和。

由于剩两个数，因此可以任我们摆布。

然而，为了保证不与之前的数相同，我们取的数必须大于 $n-2$，当然，**确定**一个数 $a_{n-1}$（还没填入），另外一个数也确定了，答案就是 $x\oplus n\oplus a_{n-1}$。

为了保证另外一个数 $e$ 不等于的之前填入的数，不难证明必须大于这些数，我们可以让 $a_{n-1}$ 为 $n$ 的两倍，不难证明它的二进制位数一定比 $x$ 大，因为 $x$ 为小于 $n$ 的正整数异或而成，因此其位数必然小于等于 $n$ 的位数，$n$ 的两倍则一定大于 $n$ 的位数，假设 $a_{n-1}=2^{q}+d,x=2^{q-f}+h$，其中 $f>0,d<2^q,h<2^{q-f}$，$a_{n-1}\oplus x=(2^{q}+d)\oplus(2^{q-f}+h)\ge 2^q$，为了保证 $e\not=a_{n-1}$，需要保证 $x\oplus n\not=0$，特判一下，将 $a_{n-2}$ 改为 $n$ ，此时 $x\oplus n\not=0$ 一定成立即可
```cpp
if((x^n)==0){
	x^=a[n-2];//需要注意的是，我们还要改变x的值
	a[n-2]=n;
	x^=n;
}
```

最后计算，输出即可。
```cpp
int s;
s=2*n;
a[n-1]=s;
a[n]=(x^s^n);
for(int i=1;i<=n;i++){
	cout<<a[i]<<" ";
}
cout<<endl;
```
别忘了加多组测试数据。

```cpp
int T;
cin>>T;
while(T--){
	int n;
	cin>>n;
	pr(n);//每次计算答案，输出答案
}
```

于是我们获得了 $0$ 分的好成绩。

究竟是哪里错了呢？哦，数据要求总和小于等于 $n^2$，而我们构造的的数列的和最坏约为 $\cfrac{n^2+n}{2}$，对于较小的数据，我们可能超界，因此可以手写小数据。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000009];
void pr(int n){
	if(n==1){
		cout<<"1\n";
	}else if(n==2){
		cout<<"1 3\n";
	}else if(n==3){
		cout<<"-1\n";//手推发现无解
	}else if(n==4){
		cout<<"1 2 3 4\n";
	}else if(n==5){
		cout<<"1 2 4 8 10\n";
	}else if(n==8){
		cout<<"1 2 3 4 5 6 7 8\n";
	}else{
		int x;
		x=0;
		for(int i=1;i<=n-2;i++){
			a[i]=i;
			x^=a[i];
		}
		if((x^n)==0){
			x^=a[n-2];
			a[n-2]=n;
			x^=n;
		}
		int s;
		s=2*n;
		a[n-1]=s;
		a[n]=(x^s^n);
		for(int i=1;i<=n;i++){
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
	
}
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		pr(n);
	}
	return 0;
}
```



---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
题目要求我们构造一个符合条件的序列，还和异或有关，数据范围还大，很明显的一道构造题。
## 2. 题目做法
先考虑暴力，我们要注意题目的限制条件，花不了多久便能写出以下暴力代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int T,n,s,t;
int a[N],idx;
bool p;
void dfs(int x,int y,int z)
{
	if(x==n)
	{
		if(s==n)
		{
			for(int i=1;i<=n;i++)
				printf("%d ",a[i]);putchar(10);
			p=1;
		}
		return ;
	}
	for(int i=z+1;i<=t-y;i++)
	{
		a[++idx]=i;
		s^=i;
		dfs(x+1,y+i,i);
		s^=i;
		idx--;
		if(p)
			return ;
	}
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		t=n*n;
		p=0;
		dfs(0,0,0);
		if(!p)
			printf("-1\n");
	}
	return 0;
}
```
因为数据范围太大，所以这份代码只能得到一部分分。但构造题最主要的是找规律，所以我们可以通过这个暴力代码来找序列规律。  
通过暴力代码，我们可以发现，有五种情况。  
情况一，$n$ 太小，以至于不知为何，规律不成立，这部分直接暴力特判掉就行了。  
情况二，$n$ 是 $4$ 的倍数，此时我们只需要构造一个 $1$ 到 $n$ 的序列就行了。  
情况三，$n$ 除以 $4$ 余 $1$，此时我们先构造一个 $1$ 到 $n - 2$ 的序列，倒数第二项是大于 $n$ 且最小的 $2$ 的次方数，最后一项就是 $n$ 加上倒数第二项。  
情况四，$n$ 除以 $4$ 余 $2$，此时我们先构造一个 $1$ 到 $n - 1$ 的序列，最后一项是 $n + 1$。  
情况五，$n$ 除以 $4$ 余 $3$，除最后一项，其余都与情况三相同，最后一项相比情况三减去一就行了。  
如此我们便可完成此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int T,n;
int a[N],t=1;
int main()
{
	for(int i=1;i<=5e5;i++)//预处理大于n且最小的2的次方数 
	{
		if(i>t)
			t<<=1;
		a[i]=t;	
	}
	T=read();
	while(T--)
	{
		n=read();
		if(n==1)
			printf("1\n");
		else if(n==2)
			printf("1 3\n");
		else if(n==3)
			printf("-1\n");
		else if(n==4)
			printf("1 2 3 4\n");
		else if(n==5)
			printf("1 2 4 5 7\n");
		else if(n==6)
			printf("1 2 3 4 5 7\n");
		else if(n==7)
			printf("1 2 3 4 5 8 14\n");
		else
		{
			if(n%4==0)
			{
				for(int i=1;i<=n;i++)
					printf("%d ",i);
				putchar(10);
			}
			else if(n%4==1)
			{
				for(int i=1;i<=n-2;i++)
					printf("%d ",i);
				printf("%d %d\n",a[n],a[n]+n);
			}
			else if(n%4==2)
			{
				for(int i=1;i<=n-1;i++)
					printf("%d ",i);
				printf("%d\n",n+1);
			}
			else
			{
				for(int i=1;i<=n-2;i++)
					printf("%d ",i);
				printf("%d %d\n",a[n],a[n]+n-1);
			}
		}
	}
	return 0;
}
```

---

## 作者：iBaeJuhyun (赞：1)

#### 由于 $n$ 要由正整数异或得到，很自然的想到要分奇偶考虑：
## 1. 当 $n$ 为偶数时：
观察到 $n=2$ 时数列可以为 $\{1,3\}$；

由于一个数异或上它本身的结果为 $0$,且 $0$ 异或上一个数结果为这个数本身  

$\Rightarrow$  $n=4$ 时数列可以为 $\{1,3,2,4\}$；

而 $n$ 为偶数时：

有  
$$(n-1)\operatorname{xor}(n+1)=2$$

显然当 $n \bmod 4=0$ 时，有
$$n\operatorname{xor}2=n+2$$

所以 $n=6$ 时数列可以为 $\{1,3,2,4,5,7\}$；

### 由此可得通项：
####  $n \bmod 4=0$ 时：
 
 数列可以为 
 
 $\{1,2,3\dots n-2,n-1,n\}$；
 
####  $n \bmod 4=2$ 时：
 
 数列可以为
 
 $\{1,2,3\dots n-2,n-1,n+1\}$；
 
 
##  2. 当 $n$ 为奇数时：
可以从 $n$ 为偶数的情况转换：
	
####   当 $n \bmod 4=1$ 时：
 
 数列可以从 $n \bmod 4=2$ 的情况转换；

当 $n=x$ 时，取 $n=x+1$ 时的数列:

$\{1,2,3\dots x-1,x,x+2\}$；

显然 若删去数列中的 $2$，则该数列异或和减小 $2$；

将 $x+2$ 改为 $x+1$,则异或和加 $1$；

总的异或和减小 $1$,满足条件。

####   当 $n \bmod 4=3$ 时：
通过~~手模的~~数学手段

得出 $n=3$ 时无解，
当 $n>3$ 时，通过以下手段构造得到的解可以满足条件；

以 $n=7$ 为例：

取 $n=8$ 时的数列 $\{1,2,3,4,5,6,7,8\}$；

可以发现数列 $\{1,2,3,4,5,6,7\}$ 的异或和为 $0$；

故 $\{1,2,3,4,5,6\}$的异或和为 $7$；

将 $1$ 改为 $n+2$，并在数列中加入 $n+1$，显然数列的异或和不变，并通过计算可以发现该数列是满足条件的。

### 由此可得通项：
####  $n \bmod 4=3$ 时：
 
 数列可以为 
 
 $\{2,3\dots n-2,n-1,n+1,n+2\}$；
 
####  $n \bmod 4=1$ 时：
 
 数列可以为
 
 $\{1,3,4\dots n-2,n-1,n,n+1\}$；
 


------------
#### code: ( 不会有人只看这里吧）
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m,check;
inline void make(int n)
{
	if (n == 3)
	{
		cout << -1;
		return;
	}
	if (n % 2 == 0)
	{
		if (n % 4 == 0)
		{
			for (int i = 1; i <= n; ++i)  cout << i << "  ";
			return;
		}
		else
		{
			for (int i = 1; i < n; ++i) cout << i << " ";
			cout << n + 1;
			return;
		}
	}
	else
	{
		if ((n + 1) % 4 == 0)
		{
			for (int i = 2; i <= n - 1; i++)
				cout << i << " ";
			cout << n +1 << " " <<  n+2;
			return;
		}
		else
		{
			cout << 1 << " ";
			for (int i = 3; i <= n + 1; i++)
				cout << i << " ";
			return;
		}
	}
}
signed main(void)
{
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		make(n), putchar('\n');
	}
	return 0;
}
```


---

## 作者：2012_Zhang_ (赞：1)

~~哈哈哈！打表真快乐！~~  
## 思路解析
这题我一看到就浑身难受，规律非常难找。  
一个邪恶的想法冒了出来——打表（OvO）。  
~~~~
n的值|序列
1    | 1
2    | 1 3
3    | -1
4    | 1 2 3 4
5    | 1 3 4 5 6
6    | 1 2 3 4 5 7
7    | 1 2 3 4 5 8 14
8    | 1 2 3 4 5 6 7 8
9    | 1 2 3 4 5 6 7 16 25
10   | 1 2 3 4 5 6 7 8 9 11
11   | 1 2 3 4 5 6 7 8 9 16 26
12   | 1 2 3 4 5 6 7 8 9 10 11 12
13   | 1 2 3 4 5 6 7 8 9 10 11 16 29
14   | 1 2 3 4 5 6 7 8 9 10 11 12 13 15
15   | 1 2 3 4 5 6 7 8 9 10 11 12 13 16 30
~~~~
肉眼可见，从 $n\ge5$ 开始，构造出的序列就全都包含了 $1\sim n-2$。  
那么剩下两个数留下的选择不多了，直接暴力莽了。  
对于 $n\le5$ 的情况可以手算。  
时间复杂度 $O(Tn)$ 足够通过这一题。 

奉上代码：  
## AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        if(n==1)cout<<1<<endl;
        else if(n==2)cout<<1<<' '<<3<<endl;
        else if(n==3)cout<<-1<<endl;
        else if(n==4)cout<<1<<' '<<2<<' '<<3<<' '<<4<<endl;
        else if(n==5)cout<<1<<' '<<3<<' '<<4<<' '<<5<<' '<<6<<endl;
        else{
            long long x=0,s=0;
            for(int i=1;i<=n-2;i++){
                cout<<i<<' ';
                x^=i,s+=i;
            }
            for(long long i=n-1;i<=n*n-s;i++){
                if(((x^i)^n)+s<=n*n&&((x^i)^n)>n-2){
                    cout<<i<<' '<<((x^i)^n)<<endl;
                    break;
                }
            }
        }
    }
}

---

## 作者：Angelastar (赞：0)

~~太好了又是找规律。~~

---

**思路**

首先排除搜索，数据范围太大还不知道搜索区间，只能是找规律。老规矩，先打表。


```cpp
 1 | 1
 2 | 1 3
 3 | -1
 4 | 1 2 3 4
 5 | 1 2 4 5 7
 6 | 1 2 3 4 5 7
 7 | 1 2 3 4 5 8 14
 8 | 1 2 3 4 5 6 7 8
 9 | 1 2 3 4 5 6 7 16 25
10 | 1 2 3 4 5 6 7 8 9 11
```


除了前几项比较特殊以外，不难发现当 $n$ 模 $4$ 为 $0$ 时，序列就是 $1$ 到 $n$ 的所有整数，循环为 $4$。

接下来又发现余数是 $2$ 时，序列基于余数为 $0$ 时只有最后一项变为了 $n+1$。那么只剩下余数为 $1$ 和 $3$ 的情况了。

观察列出的表，又可以发现，这两种情况的前 $n-2$ 项规律一样，所以无论哪种情况，都要先输出 $1$ 到 $n-2$。

而余数为 $1$ 和余数为 $3$ 倒数第二项都是第一个大于 $n$ 的 $2$ 的 $k$ 次方，只剩下最后一项了！

通过找最后两项的关系，成功发现。当余数为 $1$ 时，最后一项为倒数第二项 $+n$。当余数为 $3$ 时，最后一项为倒数第二项 $+n-1$。



---
**code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n==1){
			cout<<1<<endl;
			continue;
		}
		if(n==3){
			cout<<-1<<endl;
			continue;
		}
		if(n==5){
			cout<<"1 4 5 3 6"<<endl;
            continue;
		}
		for(int i=1;i<=n-2;i++)cout<<i<<' ';
		if(n%4==0)cout<<n-1<<' '<<n<<endl;
		if(n%4==2)cout<<n-1<<' '<<n+1<<endl;
		if(n%4==1){
			int mul=1;
			while(mul<n){
				mul*=2;
			}
			cout<<mul<<' '<<mul+n<<endl;
		}
		if(n%4==3){
			int mul=1;
			while(mul<n){
				mul*=2;
			}
			cout<<mul<<' '<<mul+n-1<<endl;
		}
	}
	return 0;
}
```

---

麻烦管理员大大啦。

---

