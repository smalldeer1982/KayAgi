# Square Table

## 题目描述

While resting on the ship after the "Russian Code Cup" a boy named Misha invented an interesting game. He promised to give his quadrocopter to whoever will be the first one to make a rectangular table of size $ n×m $ , consisting of positive integers such that the sum of the squares of numbers for each row and each column was also a square.

Since checking the correctness of the table manually is difficult, Misha asks you to make each number in the table to not exceed $ 10^{8} $ .

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1```

## 样例 #2

### 输入

```
1 2
```

### 输出

```
3 4```

# 题解

## 作者：Little09 (赞：4)

直接分治。如果行是偶数，先化成两半做，上面 $\times 3$，下面 $\times 4$，拼起来就行，这样拼起来每列的平方和是 $25x^2$。

如果行是奇数，化成两半和中间一行，对每列求出该列的平方和 $x^2$。上面 $\times 2$，下面 $\times 2$，中间写 $x$，这样拼起来每列的平方和是 $9x^2$。

列同理。

---

## 作者：_3414_ (赞：3)

考虑先构造一行，设为 $a$。

当 $n=1$ 时，直接扔个平方数上去就是合法的。

当 $n=2$ 时，令 $a=[3,4]$ 即可。

否则，当 $n$ 是奇数的时候，令 $a$ 第一项为 $2$，然后 $n-2$ 项为 $1$，最后一项是 $\frac{n+1}{2}$ 即可满足要求。

当 $n$ 是偶数的时候，令 $a$ 前 $n-1$ 项为 $1$，最后一项为 $\frac{n}{2}-1$ 即可。

证明：当 $n$ 是奇数的时候，该行的和为：$(\frac{n+1}{2})^2+n+2=(\frac{n}{2}+1)^2$。

当 $n$ 是偶数的时候，该列的和为：$(\frac{n}{2}-1)^2+n-1=(\frac{n}{2})^2$。

列的构造方式同理，设为 $b$。

再考虑拓展到 $n\times m$ 的矩阵上，事实上，令 $c[i][j]=a[i]\times b[j]$ 就是符合要求的。

证明：矩阵 $c$ 第 $i$ 行的平方和为：$a[i]^2\times \sum_{j=1}^n{b[j]^2}$。因为 $b$ 的平方和是一个平方数，所以 $c$ 每一行的平方和也是平方数。列的证明方式同理。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005][1005],lc[1005],rc[1005];
int main(){
	cin>>n>>m;
	if(n==1){
		if(m==1){cout<<"1\n";return 0;}
		if(m==2){cout<<"3 4\n";return 0;}
		if(m&1^1){
			for(int i=1;i<m;++i)cout<<"1 ";
			cout<<(m-2)/2<<'\n';return 0;
		}
		else{
			cout<<"2 ";
			for(int i=2;i<m;++i)cout<<"1 ";
			cout<<((m+1)/2)<<'\n';return 0;
		}
	}
	if(m==1){
		if(n==2){cout<<"3\n4\n";return 0;}
		if(n&1^1){
			for(int i=1;i<n;++i)cout<<"1\n";
			cout<<(n-2)/2<<'\n';return 0;
		}
		else{
			cout<<"2\n";
			for(int i=2;i<n;++i)cout<<"1\n";
			cout<<((n+1)/2)<<'\n';return 0;
		}
	}
	if(n==2){lc[1]=3;lc[2]=4;}
	else if(n&1^1){
		for(int i=1;i<n;++i)lc[i]=1;
		lc[n]=(n-2)/2;
	}
	else{
		lc[1]=2;
		for(int i=2;i<n;++i)lc[i]=1;
		lc[n]=((n+1)/2);
	}
	if(m==2){rc[1]=3;rc[2]=4;}
	else if(m&1^1){
		for(int i=1;i<m;++i)rc[i]=1;
		rc[m]=(m-2)/2;
	}
	else{
		rc[1]=2;
		for(int i=2;i<m;++i)rc[i]=1;
		rc[m]=((m+1)/2);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)a[i][j]=lc[i]*rc[j];
	for(int i=1;i<=n;++i,cout<<'\n')
		for(int j=1;j<=m;++j)cout<<a[i][j]<<' ';
	cout<<'\n';
	return 0;
}
```

---

## 作者：Limit (赞：2)

来一个更朴素的构造方式，定义一个序列合法当且仅当这个序列的元素的平方和是一个完全平方数。

可以发现
$$
(n-1)(2\times 2)+(n-2)\times(n-2)=4+4(n-2)+(n-2)^2=n^2
$$
所以所有长度大于 $2$ 的序列都可以按 $n-1$ 个 $2$ 和一个 $n-2$ 来构造。（长度小于等于 $2$ 的序列的构造方式样例中给出了）

可以发现将一个合法的序列乘一个正整数后仍然是合法的，所以得到长度为 $n$ 的合法序列 $a_i$ 和长度为 $m$ 的 $b_i$ 后第 $i$ 行第 $j$ 列的结果可以用 $a_i\times b_j$ 来构造。

```cpp
#include<bits/stdc++.h>
#define REP(i,f,l) for(int i(f);i<=(l);++i)
using namespace std;
const int MAXN=105;
int n,m;
int a[MAXN],b[MAXN];
inline void Calc(const int n,int *a)
{
	if(n==1)
	{
		a[1]=1;
		return;
	}
	if(n==2)
	{
		a[1]=3;
		a[2]=4;
		return;
	}
	REP(i,1,n-1)
	{
		a[i]=2;
	}
	a[n]=n-2;
}
int main()
{
	scanf("%d%d",&n,&m);
	Calc(n,a);
	Calc(m,b);
	REP(i,1,n)
	{
		REP(j,1,m)
		{
			printf("%d ",a[i]*b[j]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：yyandy (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF417E)     

直接去构造整个矩阵看似无从下手，我们可以考虑只有一行或一列的情况。     
在官方题解中，给出了一种分类讨论再进行构造的解法，
设构造出的数组为 $A$

- $n=1$ 时 $A=[1]$。
- $n=2$ 时 $A=[3,4]$。
- $n\ge 3$ 且 $2 \nmid n$ 时 $A=[1,1,\dots,1,\tfrac{n-2}{2}]$。
- $n\ge 4$ 且 $2 \mid n$ 时 $A=[2,1,1,\dots,1,\tfrac{n+1}{2}]$。

然而我比较弱，一开始没有想到这么巧妙的构造方法，于是就开始乱搞。   
看到 $n$ 非常小，而且对构造出的数值的限制非常松，这非常适合暴力枚举。     
首先把数组里的数都赋值为 $1$，然后依次将数组里的数 $+1$，再判断平方和是否是某个整数的平方。     
虽然这样看起来非常不靠谱，但是手玩了几组没有发现问题，          
写了程序验证了一下，发现在数据范围内都没有出现数值过大的情况。       

总之构造出一行的方法非常多，这里就不一一列举了。      

我们已经会了只有一行一列的情况，$n$ 行 $m$ 列怎么做呢？      
其实我们只要构造出一个长度为 $n$ 的行和一个长度为 $m$ 的列，然后一一相乘即可。        
这样为什么是对的呢？       
考虑构造出的行为 $a$，列为 $b$，最终矩阵为 $c$，$b$ 所有数的和为 $Q^2$。     
由 $c_{i,j}=a_i\times b_j$ 可以得到第 $i$ 行的平方和 $S$ 为 $\sum_{j=1}^{m}(a_i\times b_j)^2$。        
化简一下可以得到 $S=a_i^2\times \sum_{j=1}^{m}b_j^2=a_i^2\times Q^2$。        
即 $a_i\times Q$ 的平方，列同理，所以是对的。    
Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,A[120][5];
bool isSquare(int x){
	return(sqrt(x)==int(sqrt(x)));
}
void Con(int x,int y){
	int Ans=0;
	for(int i=1;i<=x;++i)
		A[i][y]=1,Ans++;
	if(isSquare(Ans))return;
	for(int j=3;;j+=2){
		for(int i=1;i<=x;++i){
			A[i][y]+=j,Ans+=j;
			if(isSquare(Ans))return;
		}
	}				
}
int main(){
	cin>>n>>m,
	Con(n,1),Con(m,2);
	for(int i=1;i<=n;++i,puts(""))
		for(int j=1;j<=m;++j)
			cout<<int(sqrt(A[i][1]*A[j][2]))<<' ';
} 
```



---

## 作者：Inui_Sana (赞：1)

Daily problem.卡了半天是怎么回事呢？

给出个 $\max ans\le 4$ 的解法。

首先，有引理：若 $\sum a_i^2=b^2$，则 $\sum(ka_i)^2=(kb^2)$。由此可以想到，先构造每一行都相同，然后再让每一列乘上某个数。

再进一步，发现这些乘上的数也可以和前面一样算。换句话说，只需要考虑构造 $\sum a_i^2=x^2,\sum b_i^2=y^2$，则 $ans_{i,j}=a_i\times b_j$ 是可行的。

考虑怎么构造一个长度为 $n$ 的 $a$。发现很多时候只用 $1,2$ 就行。设用了 $x$ 个 $1$，则有 $x+4(n-x)=k^2$，即 $x=\dfrac{4n-k^2}{3}$。但是注意到 $k^2\bmod 3\not=2$，则如果 $n\bmod 3=2$ 要特殊处理。

怎么办呢？发现只要往后面塞一个 $3$ 就行了。此时方程变成 $x+4(n-x-1)=k^2-9$ 即 $x=\dfrac{4n+5-k^2}{3}$，有解。

暴力枚举 $k$ 然后构造即可。

需要特判 $n=1$ 或 $n=2$。

code：

```cpp
int n,m;
vector<int> solve(int n){
	vector<int> g;g.resize(n+1);
	if(n==1){
		g[1]=1;
		return g;
	}
	if(n==2){
		g[1]=3,g[2]=4;
		return g;
	}
	int x=4*n;
	if(n%3==2){
		g[n--]=3,x+=5;
	}
	rep(i,1,n){
		if((x-i*i)%3){
			continue;
		}
		int y=(x-i*i)/3;
		if(y>=1&&y<=n){
			rep(i,1,y){
				g[i]=1;
			}
			rep(i,y+1,n){
				g[i]=2;
			}
			return g;
		}
	}
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	vector<int> a=solve(n),b=solve(m);
	rep(i,1,n){
		rep(j,1,m){
			printf("%d ",a[i]*b[j]);
		}
		puts("");
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：ykzzldz (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF417E)

我们先考虑 $n=1$ 的情况，也就是说，我们希望得到一个长度为 $m$ 的序列，使得该序列的平方和为一个完全平方数，自然想到使用完全平方公式。这里需要对 $m$ 的奇偶性进行讨论：

- 当 $m$ 为偶数时，有 $ (\frac{n}{2}-1)^2+n-1=(\frac{n}{2})^2 $，所以我们可以让第一项为 $\frac{n}{2}-1$，后 $n-1$ 项为 $1$。

- 当 $m$ 为奇数时，有 $ (\frac{n+1}{2})^2+n+2=(\frac{n}{2}+1)^2 $，所以我们可以让第一项为 $(\frac{n+1}{2})^2$，第二项为 $2$，后 $n-2$ 项为 $1$。

现在，我们将这个结论推广。考虑我们先将一列和一行分别处理出来，答案就为当前位置上两个数的乘积，即：$ans_{i,j}=a_i\times b_j$，其中 $a,b$ 分别为我们处理出的序列。正确性显然，但是，我们在这里要特殊判断 $n=1,m=1,n=2,m=2$ 的情况，那么就可以愉快通过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[110],b[110];
void build1(){
	if(n%2==0){
		a[1]=n/2-1;
		for(int i=2;i<=n;i++)a[i]=1;
	}
	else{
		a[1]=(n+1)/2;
		a[2]=2;
		for(int i=3;i<=n;i++)a[i]=1;
	}
}
void build2(){
	if(m%2==0){
		b[1]=m/2-1;
		for(int i=2;i<=m;i++)b[i]=1;
	}
	else{
		b[1]=(m+1)/2;
		b[2]=2;
		for(int i=3;i<=m;i++)b[i]=1;
	}
}
int main(){
	cin>>n>>m;
	if(n==1){
		if(m==2){
			cout<<"3 4";
			return 0;
		}
		build2();
		for(int i=1;i<=m;i++){
			cout<<b[i]<<' ';
		}
		return 0;
	}
	if(m==1){
		if(n==2){
			cout<<"3\n4";
			return 0;
		}
		build1();
		for(int i=1;i<=n;i++){
			cout<<a[i]<<'\n';
		}
		return 0;
	}
	if(n==2){
		a[1]=3,a[2]=4;
	}
	else build1();
	if(m==2){
		b[1]=3,b[2]=4;
	}
	else build2();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<a[i]*b[j]<<' ';
		}
		cout<<'\n';
	}
    return 0;
}
```

---

## 作者：cmk666 (赞：0)

[题目传送门](/problem/CF417E)

怎么大家都来做这题了。

显然构造矩阵和构造一行是等价的，直接对行列分别构造然后相乘即可。

考虑一行怎么做。一个很 naive 的想法就是先塞 $n-1$ 个 $1$ 然后用最后一个调整。也就是说，我们要找到一个 $a$ 使得关于 $x$ 的方程 $n-1+a^2=x^2$ 有正整数解。

根据平方差公式容易得到 $(x+a)(x-a)=n-1$，于是构造 $\begin{cases}x+a=n-1\\x-a=1\end{cases}$，即 $\begin{cases}x=n/2+1\\a=n/2-1\end{cases}$。

但 $n$ 不一定能被 $2$ 整除，直接把这整行 $\times2$ 即可。

因为 $a$ 是正整数所以 $n\le2$ 的时候要特判，不然构造出的 $a\le0$。

时间复杂度 $O(nm)$。代码非常好写。

---

## 作者：I_am_Accepted (赞：0)

先夸赞一下官方 $[1,\dots,1,\frac{n-2}{2}]$ 和 $[2,1,\dots,1,\frac{n+1}{2}]$ 做法，这里给出一种值域 $36$（单行值域 $6$）的做法。

我们只要做出一行的答案，然后列向量乘行向量就得到答案了。

我们可以将四个相同的数 $a,a,a,a$ 合并成一个数 $2a$。

接下来的构造满足所有元素均为埃及分数，最后将他们乘上 $\text{lcm}$ 即可变为正整数。

考虑反着做，按 $n\bmod 3$ 分类：

* $0$，我们初始构造 $1/2,1,1$。

* $1$，我们初始构造 $1$。

* $2$，我们初始构造 $1/3,1/4$。

然后每次将分母最小的一个 $1/a$ 分裂成四个 $1/{2a}$ 即可，这个过程用优先队列实现即可。

最后经测试，最大值不超过 $6$。

---

## 作者：5ab_juruo (赞：0)

非常好题目，爱来自 duel bot。

先考虑一行怎么做，若 $m=4^k$，则可以直接填充任意数。否则，注意到 $m/4$ 到 $m$ 中必然有一个 $4$ 的幂次，若存在一个数，其平方可以分成 $1\sim 4$ 个数的平方和，则可以直接用这个数填充。

注意到 $85^2=84^2+13^2=84^2+12^2+5^2=84^2+12^2+4^2+3^2$，所以用 $85$ 填充到小于等于 $m$ 的最小 $4$ 的幂次即可。

对于一般情况，先分别求出一行 $n$ 列的答案 $a_1\sim a_n$，和 $m$ 列的答案 $b_1\sim b_m$。对于第 $i$ 行第 $j$ 列，输出 $a_ib_j$ 即可。

容易证明其正确性。

```cpp
const int max_n = 100;

int l[max_n], cc[max_n];

void make(int *a, int x)
{
	int c = 1 << (__lg(x) / 2) * 2;
	
	for (int i = 0; i < x; c--)
	{
		if (x - i >= c + 3)
			a[i++] = 3, a[i++] = 4, a[i++] = 12, a[i++] = 84;
		else if (x - i >= c + 2)
			a[i++] = 5, a[i++] = 12, a[i++] = 84;
		else if (x - i >= c + 1)
			a[i++] = 13, a[i++] = 84;
		else
			a[i++] = 85;
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	
	cin >> n >> m;
	make(l, n), make(cc, m);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cout << l[i] * cc[j] << " \n"[j == m - 1];
	
	return 0;
}
```

---

