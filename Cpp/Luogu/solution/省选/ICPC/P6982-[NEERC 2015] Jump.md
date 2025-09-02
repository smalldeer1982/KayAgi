# [NEERC 2015] Jump

## 题目描述

Consider a toy interactive problem ONEMAX which is defined as follows.

You know an integer $n$ and there is a hidden bit - string $S$ of length $n$. The only thing you may do is to present the system a bit - string $Q$ of length $n$, and the system will return the number $\text{ONEMAX}(Q)$ — the number of bits which coincide in $Q$ and $S$ at the corresponding positions. The name of ONEMAX problem stems from the fact that this problem and a simpler one explaining when $S = 11\ldots11$, so that the problem turns into maximization (MAX) of the number of ones (ONE).

When $n$ is even, there is a similar (but harder) interactive problem called JUMP. The simplest way to describe the JUMP is by using ONEMAX:
$$
\text{JUMP}(Q)=
\begin{cases}
\text{ONEMAX}(Q) & \text{if } \text{ONEMAX}(Q)=n \text{ or } \text{ONEMAX}(Q)=n/2; \\
0 & \text{otherwise.}
\end{cases}
$$
Basically, the only nonzero values of ONEMAX which you can see with JUMP are $n$ (which means you've found the hidden string $S$) and $n/2$.

Given an even integer $n$ — the problem size, you have to solve the JUMP problem for the hidden string $S$ by making interactive JUMP queries. Your task is to eventually make a query $Q$ such that $Q = S$.

### Interaction protocol

First, the testing system tells the length of the bit - string $n$. Then, your solution asks the queries and the system answers them as given by the JUMP definition. When a solution asks the query $Q$ such that $Q = S$, the system answers $n$ and terminates, so if your solution, after reading the answer $n$, tries reading or writing anything, it will fail.

The limit on the number of queries is $n + 500$. If your solution asks a $(n + 501)$ - th query, then you will receive the “Wrong Answer” outcome. You will also receive this outcome if your solution terminates too early.

If your query contains wrong characters (neither 0, nor 1), or has a wrong length (not equal to $n$), the system will terminate the testing and you will receive the “Presentation Error” outcome.

You will receive the “Time Limit Exceeded” outcome and other errors for the usual violations.

Finally, if everything is OK (e.g. your solution finds the hidden string) on every test, you will receive the “Accepted” outcome, in this case you will have solved the problem.

## 样例 #1

### 输入

```
2
1
0
1
2```

### 输出

```
01
11
10
00```

# 题解

## 作者：Star_Cried (赞：7)

## P6982 [NEERC2015]Jump

### 题意

给你一个未知的 01 串，每次可以输出询问一个 01 串，如果该串中正确的个数刚好等于 $n$ 或者 $n/2$ ，将会返回相应的答案，否则会返回 0 。求出这个串。（询问次数不大于 $n+500$ )

### 思路

先无视询问次数，我们来想一下确定性算法怎么做。

第一步，我们来试着找出 $n/2$ 正确的串。

首先，我们设一个全 0​ 串，每次修改最左边的 0 为 1，在这至多 $n$ 次询问中，我们一定能找到一个有 $n/2$ 位正确的串。

* 正确性证明：假设全 0 时有小于 $n/2$ 位正确，那么最糟情况，也就是变成全 1 时一定有多于 $n/2$ 位正确；反之亦然。我们每次只改变一位的正确性，也就是说每次正确的位数只会改变 1，这样在移动的过程中一定会有一个情况恰好 $n/2$ 位正确。

第二步，我们来找到正确的串。

我们固定一个位置，每次询问将该位置和其他一个位置取反。显然：若返回的答案为 $n/2$ ，那么说明固定位置和这个位置的正确性是相反的。我们这样询问固定位置和其他每一个位置，就能够得到包含所有位置的两个正确性相反的集合。然后，我们将这个得到的 01 串和取反后的串询问，找到正确的输出即可。

于是我们得到一个询问次数为 $2n$ 的确定性算法。

过不了。怎么办呢？不要伤心，不要心急！然后我们发现第一步我们随机选择的正确率是挺高的。询问499次，每次询问有 $\frac{\tbinom{\frac{n}{2}}{n}}{2^n}$ 的几率询问到 $n/2$ 正确的串，询问499次后，发现这个几率非常大，用电脑算出来是 $0.99997$ ……于是我们就做完了。

### 实现

记得清空缓冲区。下面的代码使用了阴间的`bitset`实现，常数挺大。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
#include<bitset>
#include<cstdlib>
#include<ctime>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	int n,ans;
	bitset<1002> a,b;
	inline void write(bitset<1002>& x){
		for(int i=0;i<n;i++) cout<<x[i];
		cout<<endl;
	}
	inline void work(){
		srand(time(0));
		ios::sync_with_stdio(false);
		cin>>n;
		for(int i=1;i<=499;i++){
			for(int j=0;j<n;j++) a[j]=rand()%2;
			write(a);
			cin>>ans;
			if(ans==n)return;
			else if(ans==n/2)break;
		}
		a[0]=a[0]^1;
		for(int i=1;i<n;i++){
			a[i]=a[i]^1;
			write(a);
			cin>>ans;
			b[i]=a[i]^(ans==n/2);
			a[i]=a[i]^1;
		}
		b[0]=a[0];
		write(b);
		cin>>ans;
		if(ans==n)return;
		b.flip();
		write(b);
		cin>>ans;
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：a___ (赞：4)

这是一道 IO 交互题。   

______

观察题面，发现题目要求询问不超过 $n+500$ 次。显然，这个 $500$ 别有用意。    

考虑 $500$ 次询问能干什么。每次询问求得恰 $\dfrac n 2$ 位相同的串概率为 $\dfrac {\binom n{\frac n 2}}{2^n}\geq0.025$。那么 $500$ 次操作中有一次恰 $\dfrac n 2$ 位相同的概率约为 $0.999$。可以视为通过 $500-1$ 次询问一定能得到一次。    

然后，再进行 $n-1$ 次询问，判断上述得到串每一位是否和第 $0$ 位正确性相同。具体做法为先将第 $0$ 位的数换掉，再尝试将每一位的数换掉，如果换了以后询问结果是 $\dfrac n 2$ 说明这一位和第 $0$ 位正确性相反，影响互补了；否则是相同的。这样我们就可以得到一整个与第 $0$ 位正确性相同的串。    

然后，如上所述，这个串要么全对，要么全错，$\leq2$ 次询问都试一下就好了。    

代码如下：     
```cpp
#include<iostream>
#include<cstdlib>
#include<ctime>
int n,m;std::string s,ans;
int main()
{
    int i,j;srand(time(NULL));
    std::cin>>n;s.resize(n);
    for(i=1;i<500;i++)
    {
        for(j=0;j<n;j++)s[j]=rand()%2+48;
        std::cout<<s<<std::endl;
        std::cin>>m;
        if(m==n)return 0;
        if(m==n/2)break;
    }
    ans.resize(n);ans[0]=s[0];
    for(i=1,s[0]^=1;i<n;i++)
    {
        s[i]^=1;std::cout<<s<<std::endl;
        std::cin>>m;s[i]^=1;
        if(m==n)return 0;
        ans[i]=s[i]^(m==n/2);
    }
    std::cout<<ans<<std::endl;
    std::cin>>m;if(m==n)return 0;
    for(i=0;i<n;i++)ans[i]^=1;
    std::cout<<ans<<std::endl;
    return 0;
}
```

---

## 作者：Acerkaio (赞：1)

随一个 `01` 串期望得到交互库返回 $\frac{n}{2}$ 的询问次数约 `39.64` !

```python
def pi(num):
    res = 1
    for i in range(1, num + 1):
        res *= i
    return res
print(1/(pi(1000)/pow(pi(500),2)/pow(2,1000)))
```
或者：
```cpp
#include<bits/stdc++.h>
#define reg register
#define rep(i,a,b) for(reg int i=a;i<=b;++i)
using namespace std;
const int N=1005;
mt19937 rd((unsigned long long)new char);
signed main(){
	int n=1000,ans=0,cnt=0;
	while(1){
		int res=0;++cnt;
		rep(i,1,n)if(rd()%2==1)++res;
		if(res==n/2)++ans;
		cout<<(double)cnt/ans<<'\n';
	}
    return 0;
}
```

现在我们得到了 $a_i$ 枚举相邻的两个数做一次取反，分类讨论：

1. 得到 $\frac{n}{2}$：那么其中一个是对的，另一个是错的。
2. 得到 $0$：那么两个都是是对的或两个都是是错的。

那么我们设第一个是对的，可以解出全部来，同理再设第一个是错的。

最后期望使用次数：$40+n-1+2=n+41$，限制 $n+500$ 包能过了。

```
#include<bits/stdc++.h>
#define pb push_back
#define reg register
#define rep(i,a,b) for(reg int i=a;i<=b;++i)
#define drep(i,a,b) for(reg int i=a;i>=b;--i)
using namespace std;
const int N=1005;
mt19937 rd((unsigned long long)new char);
int n;
bool a[N],col[N];
signed main(){
	// ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	while(1){
		rep(i,1,n)a[i]=rd()%2,cout<<a[i];
		cout<<endl;
		int op;cin>>op;
		if(op==n)return 0;
		if(op==n/2)break;
	}
	// a[1]=0,a[2]=1,a[3]=1,a[4]=0;

	col[1]=0;
	rep(i,1,n-1){
		rep(j,1,n){
			if(j==i||j==i+1)cout<<(a[j]^1);
			else cout<<a[j];
		}
		cout<<endl;
		int op;cin>>op;
		if(op==0)col[i+1]=col[i];
		else col[i+1]=col[i]^1;
	}
	int op;
	rep(i,1,n){
		if(col[i])cout<<(a[i]^1);
		else cout<<a[i];
	}
	cout<<endl;
	cin>>op;
	if(op==n)return 0;
	rep(i,1,n){
		if(!col[i])cout<<(a[i]^1);
		else cout<<a[i];
	}
	cout<<endl;
	cin>>op;
	if(op==n)return 0;
    return 0;
}

```

---

## 作者：dAniel_lele (赞：1)

假设我们现在已经获得了一个串 $Q'$ 使得回答为 $\frac n2$，下面该如何求。

考虑每次翻转两个位置 $i,j$，看能得到什么。

如果 $i$ 和 $j$ 两个位置在 $Q'$ 和 $S$ 中都相同/不同，那么改完了一定不会得到 $\frac n2$。如果两者中恰有一个相同，那么一定会得到 $\frac n2$。

于是，我们询问所有 $i,i+1$，即可得到哪些位置状态是相同的。设为两个集合 $V_1,V_2$，尝试两次，每次翻转其中一个集合中的位置，必有一次是正确的。

现在考虑如何得到一个串 $Q'$。

我们声称，随机大约 $400$ 次即可。

一个串的返回值是 $\frac n2$ 的概率为 $\frac{\binom n{\frac n2}}{2^n}$，在 $n=1000$ 时大约是 $0.0252$。随机 $400$ 次均为得到返回值为 $\frac n2$ 的串的概率大约为 $(1-0.0252)^{400}$ 大约是 $3\times10^{-5}$，足以通过。

当然，随机化是一个令人难受的东西，有一种 $2n$ 次询问的比较正经的做法。考虑询问在 $00\dots0$ 将一个前缀修改为 $1$ 的所有串，容易证明必有一个使得和 $S$ 有恰好 $\frac n2$ 位相同。当然，在本题中这无法通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(time(0));
int tmp[1000005];
int rel[1000005];
signed main(){
	int n; cin>>n;
	int cnt=0;
	while(1){
		for(int j=1;j<=n;j++) cout<<(tmp[j]=(rng()&1));
		cout<<endl; fflush(stdout);
		int ret; cin>>ret;
		cnt++;
		if(ret==n) exit(0);
		if(ret==n/2) break;
		if(cnt==500){
			exit(2);
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=n;j++){
			if(j==i||j==i+1) cout<<(tmp[j]^1);
			else cout<<tmp[j];
		}
		cout<<endl; fflush(stdout);
		cin>>rel[i];
		if(rel[i]==n) exit(0);
		rel[i]/=(n/2);
	}
	{
		int now=0;
		for(int i=1;i<=n;i++){
			cout<<(tmp[i]^now);
			now^=rel[i];
		}
		cout<<endl; fflush(stdout);
		int ret; cin>>ret;
		if(ret==n) exit(0);
	}
	{
		int now=1;
		for(int i=1;i<=n;i++){
			cout<<(tmp[i]^now);
			now^=rel[i];
		}
		cout<<endl; fflush(stdout);
		int ret; cin>>ret;
		if(ret==n) exit(0);
	}
	return 0;
}
```

---

## 作者：_Cheems (赞：0)

萌新做的第一道紫交互题纪念一下。

记串 $S$ 的 $k$ 为 $K(S)$，答案串为 $A$。

首先考虑怎么求一个 $k=\frac n2$ 的串。注意到将某一位取反后 $k$ 恰好加或减 $1$，那么可以一开始给出全 $0$ 串 $S_0$ 然后进行 $n$ 次调整变为全 $1$ 串 $S_1$，显然 $K(S_0)+K(S_1)=n$，可以幻想一条折线，起点为 $K(S_0)$ 终点为 $K(S_1)$ 那么 $k=\frac n2$ 的情况一定被折线经过。

于是我们在 $n+1$ 次步数内求出了 $k=\frac n2$ 的串 $P$。

现在好做了，由于将一个位取反无法得知具体信息，所以将两个位 $i,j$ 取反，记 $c_i=[A_i=P_i]$，那么若取反后 $k$ 仍为 $\frac n2$ 那么 $c_i\ne c_j$，反之 $c_i=c_j$。固定 $i$，那么原串被划分为 $c=c_i$ 和 $c\ne c_i$ 的两部分，将一部分再取反则所有的 $c$ 相等。枚举两种情况即可。

上述部分消耗了 $n+1$ 的步数，总计 $2n+2$ 无法接受。

需要请出随机化大蛇了！我们可以随机生成一个串来求出 $P$，生成出来的概率为 $\frac {n \choose {\frac n2}}{2^n}>0.025$，进行 $499$ 次仍无法得到 $P$ 的概率大概是 $3\times 10^{-6}$，非常渺小。那么总次数可以接受。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, a[N];
bool c[N]; 

inline bool get(){
	for(int i = 1; i <= n; ++i) a[i] = rand() % 2, putchar(a[i] + '0');
	putchar('\n');
	fflush(stdout);
	int k; scanf("%d", &k);
	if(k == n / 2) return true;
	return false; 
}
signed main(){
	srand(time(0));
	cin >> n;
	while(!get());
	for(int i = 2; i <= n; ++i){
		for(int j = 1; j <= n; ++j) 
			if(j == 1 || j == i) putchar((a[j] ^ 1) + '0');
			else putchar(a[j] + '0');
		putchar('\n');
		fflush(stdout);
		int k; scanf("%d", &k);
		c[i] = (k == (n / 2)); 
	}
	for(int i = 1; i <= n; ++i)
		if(!c[i]) putchar((a[i] ^ 1) + '0'); 
		else putchar(a[i] + '0');
	putchar('\n');
	fflush(stdout);
	int k; scanf("%d", &k);
	if(k == n) return 0;
	for(int i = 1; i <= n; ++i)
		if(c[i]) putchar((a[i] ^ 1) + '0');
		else putchar(a[i] + '0');
	fflush(stdout);
	return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：0)

首先问出 $\frac{n}{2}$ 之前是获取不了任何信息的，所以我们考虑怎么问出 $n/2$。

注意到 $n \choose \frac{n}{2}$ 是 $\dfrac{2^n}{\sqrt{n}}$，因此我们直接问就能在期望 $\sqrt n$ 次中问到一个 $n/2$ 串。

考虑问到 $n/2$ 串之后怎么做：我们每次 flip $s_1$ 和 $s_i$ 即可知道 $1$ 与 $i$ 正确性是否相同。

那么我们处理出可能正确也可能错误的集合 $S$ 后，问一遍 $S$ 和 $\overline S$ 即可。

期望使用 $n+\sqrt{n}$ 次询问。

---

## 作者：baka24 (赞：0)

这题看上去就不是很好下手。。。。。我们初始没有任何有用信息的情况下很难做复杂度线性的推理，于是我们先考虑一下初始有一些信息的局面如何处理。

观察题目发现一个序列只有三种情况，与 $S$ 相等，与 $S$ 相等一半，啥也不是。

先考虑一下如果有一个相等一半的序列如何推出是否与 $S$ 相等。设此序列为 $a_i$ ，你发现对于一对 $i,j$ 满足 $a_i\ne S_i,a_j= S_j$，以及 $a_i=S-i,a_j\ne S_j$，同时对 $a_i,a_j$ 取反不会导致匹配的个数改变。

于是便有一种一次询问判断两个字符关系的方式，我们对于 $2\le i\le n$ 的 $a_i$ 全部判断一遍与 $a_1$ 的关系，就可以得到两个可能的答案序列，都询问一遍即可。

那么，我们现在需要一个 $499$ 次询问得到一个与 $S$ 正好差 $\frac{n}{2}$ 个字符的解法，考虑随机化。

每次随机输出一个长度为 $n$ 的 01 串，找到为止，$499$ 次询问找到的概率接近 $99.9\%$，完全够用。

---

