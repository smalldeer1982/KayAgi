# 素数取りゲーム

## 题目描述

# 素数取り游戏



东工大的安酱和爱酱玩了一个叫做石头取走游戏的两人游戏，但是因为知道必胜法，所以不再感兴趣了。

于是，安酱考虑了一个基于素数的石头取回游戏，并将它命名为“素数取回游戏”。

素数取回游戏的规则如下：

- 开始时有 $N$ 堆小石子，在第 $i$ 堆中有 $X_i$ 个（$X_i$ 是素数）小石子。
- 两个玩家轮流选择存在小石堆的那一堆，并从那里拿走一些石子。
- **只能同时获取素数枚石子，并且在剩余的石子数量为 $0$ 或素数枚时才能继续进行**
- 先无法拿走石头的玩家输掉比赛。

虽然这条规则新颖，但似乎安和爱仍然知道怎样获胜。

请问当安穗是先手，爱穗是后手，面对由 $X_1$，$X_2$，$\ldots$，$X_N$ 个石头组成的 $N$ 堆石头时，假设他们采取最优策略，谁将获胜？

## 样例 #1

### 输入

```
1
13```

### 输出

```
An```

## 样例 #2

### 输入

```
2
17 13```

### 输出

```
An```

## 样例 #3

### 输入

```
6
49529 868033 52361 519803 19289 386501```

### 输出

```
Ai```

# 题解

## 作者：Mortidesperatslav (赞：4)

题外话：本题建议评绿或蓝，标签数学、素数筛、进制、位运算、博弈论。

那么，本题解正式开始！

我们注意到，一堆石子只能有 $3$ 种情况：能取 $1 \sim 3$ 次。能取 $3$ 次的只有 $7$。对于一个数 $n$，能取一次还是两次取决于 $n-2$ 是否是素数。

下面给出一个不太严谨但好理解的证明。

我们不妨举几个例子：

```plain
2 1 1
```

我们知道，An 可以直接取 $2$，他就必胜。

```plain
2 2 1
```

An 可以取 $1$。

```plain
2 2 2 1
```

An 不管咋么先取都必胜。

```plain
2 2
```

Ai 必胜。


我们可以大胆猜测，当每个数的贡献异或为 $0$ 时，Ai 必胜，否则 An 必胜。并且异或为 $1$ 时，An 可以先取 $1$；为 $2$ 时 An 可以先取 $2$，为 $3$ 时有 $3$ 则取 $3$，否则把一个 $2$ 取成 $1$。

注意：如果有 $3$，取的 $1$ 和 $2$ 都要在 $3$ 里取。

这是因为，当异或为 $1$ 时多出来一个 $1$，An 先取先把 $1$ 取走，不管 Ai 怎么取，An 只要保证和 Ai 取的数量一样多。其他情况同理。

异或为 $2$ 时则多出来 $2$，异或为 $3$ 时则要么多出来一个 $2$ 和一个 $1$，要么多出来一个 $3$，An 总有必胜策略。

讲到这里其实代码很简单，难点反而是欧拉筛（埃筛似乎也可）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int prime[1145140],n,a[214514],ip[1145140],cnt=0;
bool vis[1145140];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	vis[0]=vis[1]=1;
	for(int i=2;i<=1000000;i++){//欧拉筛预处理，艾拉丝托特尼筛也可（这名字可能打错了） 
		if(!vis[i]){
			prime[cnt++]=i;
			vis[i]=1;
			ip[i]=1;
		}
		for(int j=0;j<cnt;j++){
			if(i*prime[j]>1000000)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	} 
	int res=0;
	cin>>n;
	for(register int i=0;i<n;i++){
		cin>>a[i];
		if(a[i]==7)res^=3;
		else if(ip[a[i]-2]==1)res^=2;
		else res^=1;
	}
	if(res==0)cout<<"Ai";
	else cout<<"An";
}
```

### update1（补充思路）:

这道题我们可以考虑采用 [nim 博弈](https://www.luogu.com.cn/problem/P2197) 的做法解决。nim 就是通过求每堆石子**最多能取次数的异或和**判断解的。那么很容易就能分成三种情况：

+ $n=7$，贡献为 $3$；

+ $n-2$ 是质数，贡献为 $2$；

+ 其余情况贡献为 $1$。

这里我们要加个小证明。

有人可能会问：可能存在一种情况，使得 $n-2$ 和 $n-4$ 都是质数啊？为什么可以这样判断？

我可以先说结论：**满足这个条件的数只有 $7$**。

要证明这个结论，我们先要引用一个有用的定理：

对于除 $2,3$ 以外的所有质数 $P_i$，都有 $P_i \bmod 6 =v 1$ 或 $P_i \bmod 6 = 5$。

我们来给个证明，若 $P_i \bmod 6 = 2$ 或 $P_i \bmod 6 \equiv 4$，那么 $P_i$ 必然是偶数，因为上面说明了 $P_i \not= 2$ 所以是合数。

若 $P_i \bmod 6 = 3$ 那么就一定是 $3$ 的倍数，余数为 $0$ 就更不用说了。

所以若 $n-2$ 是素数，由于保证 $n$ 是素数，所以 $n-4$ 是合数。


## update2（另一种实现）：

位运算可能不大好理解，我们考虑开两个变量实现等价。

按照上面的思路，我们把贡献 $3$ 看成 $1+2$，最后如果 $1$ 和 $2$ 的贡献都是偶数，那就是小爱赢，否则小安。也就是说我们可以用 $O(n\log_2A_i)$ 的时间复杂度实现 nim，这个 $\log_2 A_i$ 是因为要转二进制。不过这里依然可以 $O(n)$。

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int prime[1145140],n,a[214514],ip[1145140],cnt=0;
bool vis[1145140];
int g1=0,g2=0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	vis[0]=vis[1]=1;
	for(int i=2;i<=1000000;i++){//欧拉筛预处理，艾拉丝托特尼筛也可（这名字可能打错了） 
		if(!vis[i]){
			prime[cnt++]=i;
			vis[i]=1;
			ip[i]=1;
		}
		for(int j=0;j<cnt;j++){
			if(i*prime[j]>1000000)break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	} 
	cin>>n;
	for(register int i=0;i<n;i++){
		cin>>a[i];
		if(a[i]==7)g1++,g2++;//如果是nim，只要把二进制为1对应的位全部++
		else if(ip[a[i]-2]==1)g2++;
		else g1++;
	}
	if(g1%2==0&&g2%2==0)cout<<"Ai";
	else cout<<"An";
}
```

## update3

如果不想用线性筛，怎么办？如果 $a_i \leq 10^{18}$，怎么办？

当然是用 Miller-Rabin。因为 PON 那题题解去讲的很清楚了，这里不讲该算法，给一种参考实现，大题思路相同：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long p[]= {0,2,3,5,7,11,13,17},t,x,a[214514],res;
int n;
long long slowtm(long long x,long long k,long long m) {
	long long ans=0;
	while(k) {
		if(k&1)ans=(ans+x)%m;
		x=(x+x)%m;
		k>>=1;
	}
	return ans;
}
long long qpow(long long x,long long k,long long m) {
	long long ans=1;
	while(k) {
		if(k&1)ans=slowtm(ans,x,m);
		x=slowtm(x,x,m);
		k>>=1;
	}
	return ans;
}
bool Miller_Rabin(long long n,long long a) {
	long long vp=n-1,r=0,pan;
	while(!(vp&1))r++,vp>>=1;
	pan=qpow(a,vp,n);
	if(pan==1)return 1;
	for(int i=0; i<r; i++) {
		if(pan==n-1)return 1;
		pan=slowtm(pan,pan,n);
	}
	return 0;
}
bool isp(long long n) {
	if(n<2)return 0;
	for(int i=1; i<=2; i++) {
		if(n==p[i])return 1;
		if(n%p[i]==0)return 0;
		if(!Miller_Rabin(n,p[i]))return 0;
	}
	return 1;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
		res=0;
		cin>>n;
		for(int i=1; i<=n; i++) {
			cin>>a[i];
			if(a[i]==7)res^=3;
			else if(isp(a[i]-2)==1)res^=2;
			else res^=1;
		}
		if(res==0)cout<<"Ai\n";
		else cout<<"An\n";
}
```

---

## 作者：Genius_Star (赞：1)

~~怎么一个严谨证明都没有啊……~~

### 题意：

有 $n$ 堆石头，每堆有 $a_i$ 颗，且 $a_i$ 为质数。

`A` 和 `B` 交替取石子，每次可以取质数颗，并且剩余质数颗或取完。

哪一方把石子取完就获胜。

在两者都是以最优策略进行操作时，判断是 `A` 必胜还是 `B` 必胜？

### 思路：

注意到一个数最多只有三种取的情况：

- 全部取完。

- 当 $n-2$ 为质数时，取 $2$ 颗，剩余 $n-2$ 颗。

- 当 $n-2$ 为质数时，取 $n-2$ 颗，剩余 $2$ 颗。

不会存在一个 $x(x>2)$ 满足 $x$ 为质数且 $n-x(n-x>2)$ 也是质数。

这是显然的，因为 $x,n$ 都是质数且都大于 $2$，则两数都是奇数，那么 $n-x$ 肯定是偶数，不会是质数。

则得到 $SG$ 函数的转移式子：

$$SG(n) = \begin{cases} \operatorname{mex}\{SG(0)\} & (n-2) \not\in P \\ \operatorname{mex}\{SG(n-2),SG(2),SG(0)\} & (n-2) \in  P \end{cases}$$

注意到 $SG(0)=0,SG(2)=1$，故可以得到：

$$SG(x) = \begin{cases} 1 & (n-2) \not\in P \\ 2 & (n-2) \in  P \end{cases}$$

注意，当 $SG(n-2)=2$ 时 $SG(n)$ 是等于 $3$ 的，但是只有 $n=7$ 这一种情况满足，来证明一下：

- 若 $P-2,P-4$ 是质数且 $P-6$ 不是质数的话，那么 $SG(P-4)=1,SG(P-2)=2$，可以得到 $SG(P)=3$。

- 现在问题转化为证明不存在大于 $7$ 的三个数 $P,P-2,P-4$ 都为质数。

- 考虑将一个质数 $P \bmod 6$，其值只能为 $1,5$，则 $(P-2) \bmod 6$ 为 $5$ 或 $3$：

  - 当 $(P-2) \bmod 6 = 5$ 时，$(P-4) \bmod 6=3$，即 $(P-4) = 6k + 3 = 3(2k+1)$，可得 $P-4$ 不是质数。

  - 当 $(P-2) \bmod 6 = 3$ 时，同理可得 $(P-2)$ 不是质数。

- 故命题得证。

那么只有当 $n=7$ 时 $SG(7)=3$。

然后根据 SG 定理求异或和即可。

时间复杂度为 $O(N \sqrt{W})$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
mt19937 R(time(0));
inline ll Rand(ll l,ll r){
	if(l==r)
	  return l;
	return R()%(r-l+1)+l;
}
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,x,ans;
bool check(ll x){
	if(x<2)
	  return 0;
	for(int i=2;i*i<=x;i++)
	  if(x%i==0)
	    return 0;
	return 1;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		x=read();
		if(x==7)
		  ans^=3;
		else if(check(x-2))
		  ans^=2;
		else
		  ans^=1;
	}
	if(ans)
	  puts("An");
	else
	  puts("Ai");
	return 0;
}
```

---

## 作者：AC_love (赞：0)

首先考虑一堆石子最多能取几次。

设 $f(i)$ 表示石子数为 $i$ 的石子堆能取几次。

不难发现有：

$$f(i) = \max_{p \in \text{prime}, i - p \in \text{prime}} f(i - p) + 1$$

这个式子看起来很复杂，但我们发现：除了 $2$ 所有质数都是奇数。如果 $p$ 是奇数，且 $i - p \neq 2$，则 $i - p$ 不可能是质数。所以 $p$ 一定是 $2$。

为什么 $p$ 不能是 $i - 2$？因为 $p$ 是 $i - 2$ 时，$f(i) = f(2) + 1 \le f(i - 2) + 1$，这种情况一定不优，所以不用考虑。

因此我们得到了：

$f(i) = \begin{cases} f(i - 2) + 1 &{\text{if}}\ i - 2 \in \text{prime} \\ 1 &{\text{if}}\ i - 2 \not \in \text{prime} \end{cases}$

我们对于所有 $10^6$ 以下的质数暴力跑一遍，发现这样的规律：

如果 $i - 2$ 不是质数，$f(i) = 1$。

如果 $i - 2$ 是质数，$f(i) = 2$。

当且仅当 $i = 7$ 时，$f(i) = 3$。

当然，这个规律对于观察力强的同学也可以直接肉眼观察得出。

$N$ 堆石子，每堆石子可以取 $1 \sim 3$ 次，求先手是否必胜。于是这个问题被转化成了很基础的 Nim 游戏，直接异或一遍即可。

[code](https://atcoder.jp/contests/ttpc2019/submissions/59459597)

---

## 作者：MarSer020 (赞：0)

博弈论入门题。

前置知识：$\text{SG}$ 函数。

$\Large\text{Solution}$

求 $\text{SG}$ 函数先打个表：

| $x$ | $2$ | $3$ | $5$ | $7$ | $11$ | $13$ | $17$ | $19$ | $23$ | $29$ | $31$ | $37$ | $41$ | $43$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $\text{SG}(x)$ | $1$ | $1$ | $2$ | $3$ | $1$ | $2$ | $1$ | $2$ | $1$ | $1$ | $2$ | $1$ | $1$ | $2$ |

我们发现：当 $x\le 7$ 时 $\text{SG}(x)$ 如上表所示，当 $x>7$ 时满足

$$
\text{SG}(x)=
\begin{cases}
2&x-2\in \text{\{primes\}}\\1&\text{otherwise}
\end{cases}
$$

证明显然。

故当且仅当 $\bigoplus\limits_{i=1}^n\text{SG}(x_i)=0$ 时后手获胜，否则先手获胜。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sg;
bool pd(int x){
    for(int i=2;i*i<=x;i++)
        if(!(x%i))
            return 0;
    return 1;
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n;
    for(int i=1,x;i<=n;i++){
        cin>>x;
        if(x==2||x==3)
            sg^=1;
        else if(x==5)
            sg^=2;
        else if(x==7)
            sg^=3;
        else if(pd(x-2))
            sg^=2;
        else
            sg^=1;
    }
    cout<<(sg?"An\n":"Ai\n");
    return 0;
}
```

---

