# Divisor Chain

## 题目描述

You are given an integer $ x $ . Your task is to reduce $ x $ to $ 1 $ .

To do that, you can do the following operation:

- select a divisor $ d $ of $ x $ , then change $ x $ to $ x-d $ , i.e. reduce $ x $ by $ d $ . (We say that $ d $ is a divisor of $ x $ if $ d $ is an positive integer and there exists an integer $ q $ such that $ x = d \cdot q $ .)

There is an additional constraint: you cannot select the same value of $ d $ more than twice.

For example, for $ x=5 $ , the following scheme is invalid because $ 1 $ is selected more than twice: $ 5\xrightarrow{-1}4\xrightarrow{-1}3\xrightarrow{-1}2\xrightarrow{-1}1 $ . The following scheme is however a valid one: $ 5\xrightarrow{-1}4\xrightarrow{-2}2\xrightarrow{-1}1 $ .

Output any scheme which reduces $ x $ to $ 1 $ with at most $ 1000 $ operations. It can be proved that such a scheme always exists.

## 说明/提示

In the first test case, we use the following scheme: $ 3\xrightarrow{-1}2\xrightarrow{-1}1 $ .

In the second test case, we use the following scheme: $ 5\xrightarrow{-1}4\xrightarrow{-2}2\xrightarrow{-1}1 $ .

In the third test case, we use the following scheme: $ 14\xrightarrow{-2}12\xrightarrow{-6}6\xrightarrow{-3}3\xrightarrow{-1}2\xrightarrow{-1}1 $ .

## 样例 #1

### 输入

```
3
3
5
14```

### 输出

```
3
3 2 1
4
5 4 2 1
6
14 12 6 3 2 1```

# 题解

## 作者：Jerry_heng (赞：6)

（一）

可以将 $x$ 转为二进制。

考虑一个数的二进制 $(1\dots10\dots0)$。

其中，第一个省略号中有什么不确定，第二个省略号里都是 $0$。

易得，每个数都可以看成这种形式。

那么可以每次去掉最后一位的 $1$，易证减去的数是原数的因数。

最后会得到形如 $(10\dots0)$，省略号中全是 $0$。

此时从最大一位往后依次把每一位去掉即可。

（二）

AC 代码。

简洁明了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,cnt,x,a[1010];
int lowbit(int x){
	return x&-x;
}
int main(){
	cin>>t;
	while(t--){
		cin>>x,cnt=0;
		for(;x&(x-1);x-=lowbit(x))a[++cnt]=x;
		for(;x;x>>=1)a[++cnt]=x;
		cout<<cnt<<endl;
		for(int i=1;i<=cnt;i++)cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：cjh20090318 (赞：2)

## 题意

给定一个整数 $x\ (2 \le x \le 10^9)$，你每次可以选择一个 $d \mid x$，并将 $x=x-d$。

你需要做这样的操作**至多** $1000$ 次，并且**不能**使用同一个 $d$ **超过** $2$ 次。

求解将 $x$ 变为 $1$ 的操作序列。

## 分析

~~赛时找了很久规律，才发现是~~二进制拆分。

对 $x$ 进行二进制拆分，设 $x=\sum\limits_{i=1}^m2^{b_i}$， 满足 $\forall i \in [1,m) ,b_i>b_{i+1} \ge 0$。

观察可以发现：
$$
\begin{matrix}
\because a_1=x=\sum\limits_{i=1}^m2^{b_i}=2^{b_m}\sum\limits_{i=1}^m2^{b_i-b_m}\\
\therefore 2^{b_m} \mid a_1\\
\because a_2=a_1-2^{b_m}=\sum\limits_{i=1}^{m-1}2^{b_i}=2^{b_{m-1}}\sum\limits_{i=1}^{m-1}2^{b_i-b_{m-1}}\\
\therefore 2^{b_{m-1}} \mid a_2\\
\cdots\\
\therefore 2^{b_1} \mid a_m
\end{matrix}
$$
所以可以证明：
$$
\forall i\in[1,m],2^{b_{m-i+1}}\mid a_i
$$
所以我们可以从小到大依次减去 $2$ 的最低次幂，直到仅剩 $2$ 的最高次幂。

接着将 $2$ 的最高次幂依次砍半即可，易证每个减数不会使用超过 $2$ 次。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#include<vector>
void solve(){
	int x;scanf("%d",&x);
	std::vector<int> v;//操作序列。
	v.emplace_back(x);
	int y=1<<std::__lg(x);//求 x 的 2 的最高次幂。
	int z=x-y;
	for(int i=0;i<=30;i++)if(z&(1<<i))v.emplace_back(x-=(1<<i));//从小到大减去这一位。
	while(y>1)v.emplace_back(y>>=1);//每次砍半。
	printf("%zu\n",v.size());
	for(const int y:v) printf("%d ",y);
	putchar('\n');
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve(); 
	return 0;
}

```



---

## 作者：lfxxx (赞：1)

$x = 2^k$ 是好做的，每次以 $2^{k-1}$ 为因数即可。

对于其他情况，考虑每次让 $x$ 减去其二进制下最低位的 $1$ 直至变成 $2^k$。

这种策略下显然每个数只会在以上两个大步骤下取到，故每个数使用不超过 $2$ 次。

同时操作次数在 $O(\log n)$ 这个量级。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define lowbit(x) (x&-(x))
using namespace std;
//const int maxn =
map<int,int> cnt;
int w(int x){
	int res=0;
	for(int i=2;i<=sqrt(x);i++){
		if(x%i==0){
			res++;
			if(x%(x/i)==0) res++;
		}
	}
	return res;
}
int d(int x){
	int mi=x;
	for(int i=2;i<=sqrt(x);i++){
		if(x%i==0&&i>2) mi=min(mi,i);
		if(x%(x/i)==0&&(x/i)>2){
			mi=min(mi,x/i);	
		}
	}
	return mi;
}
queue<int> Out;
void solve(int x){
	Out.push(x);
	if(x==1) return ;
	if(x==lowbit(x)){
		solve(x/2);
	}	
	else solve(x-lowbit(x));
}
int T;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		int x;
		cin>>x;
		solve(x);
		cout<<Out.size()<<'\n';
		while(Out.size()>0) cout<<Out.front()<<' ',Out.pop();
		cout<<'\n';
	}

	return 0;
}
```


---

## 作者：芷陌陌吖 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/zhimomoya-blog/articles/Solution-CF1864C.html)

### 题意

给定一个整数 $x$，目标是在最多 $1000$ 次操作内把 $x$ 减到 $1$。

定义一个操作：选择一个 $x$ 的因数 $d$，把 $x$ 修改为 $x-d$。

同时还有一个额外的限制：相同的 $d$ 值不能选择超过 $2$ 次。

有 $t$ 组测试数据。

数据范围：$1\le t\le 10^3,2\le x\le 10^9$。

### 题解

观察限制条件为：$d$ 是 $x$ 的因数，相同的 $d$ 值不能选择超过 $2$ 次。显然二进制分解很容易满足这些条件。

我们把 $x\gets x-d$ 的操作转化为 $x\gets x+d$，即反过来，从 $1$ 向上加。先将 $x$ 转化为二进制数（位置从 $0$ 开始编号），假设最高位为 $k$，那么我们可以先倍增加到 $2^k$。

例如：$x=11,k=3$，那么我们操作就是 $1\to 2\to 4\to 8$。

接下来就利用二进制分解把值合并到 $x$。用上面的例子，$x=8+2+1$，我们可以从大的往小的加，证明如下：设我们上一次加的值是 $a$，这一次要加的值是 $b$，当前值是 $c$，那么一定有 $a|c$，$b|a$，则 $b|c$，同时 $b|(c+b)$，所以满足限制。

在编写代码时，我们可以选择倒序加入，使用 `lowbit` 运算更方便，详细见代码。

这样操作下来次数是 $O(\log x)$ 的级别的。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int T,x,a[N];
const int SIZE=1<<23;
char buf[SIZE],*p1=buf,*p2=buf,pbuf[SIZE],*pp=pbuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++)
#define putchar(c) (pp-pbuf==SIZE?(fwrite(pbuf,1,SIZE,stdout),pp=pbuf,*pp++=c):*pp++=c)
inline int read()
{
	int x=0;
	char c=getchar();
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x;
}
inline void write(int x)
{
	int out[20],cnt=0;
	do
	{
		out[++cnt]=(int)(x%10);
		x/=10;
	}
	while (x);
	for (int i=cnt;i>=1;i--) putchar((char)(out[i]^48));
	return;
}
inline int lowbit(int x)
{
	return x&(-x);
}
int main()
{
	T=read();
	while (T--)
	{
		x=read();
		int k=2;
		a[1]=1;
		for (;k<=1005;k++)
		{
			a[k]=a[k-1]*2;                      //倍增
			if (a[k]>x) break;
		}
		k--;
		vector <int> p;                         //倒序加入操作
		int cur=x;
		while (cur)
		{
			int w=lowbit(cur);
			cur-=w;
			if (cur!=0) p.emplace_back(cur);
		}
		int len=p.size();
		for (int i=len-2;i>=0;i--) a[++k]=p[i];        //注意这里是 len-2，相当于忽略最后一个操作，因为会和之前的倍增重复
		if (a[k]!=x) a[++k]=x;                         //注意特判一下
		write(k);
		putchar('\n');
		for (int i=k;i>=1;i--) write(a[i]),putchar(' ');   //倒序输出
		putchar('\n');
	}
	fwrite(pbuf,1,pp-pbuf,stdout);
	return 0;
}
```



---

## 作者：One_JuRuo (赞：1)

## 思路

刚拿到题，想了一些方法但都被推翻了，在这里列举出来，并给出反例：

- 每次减去最小的因数，反例：$1024$ 等形如 $a^k$ 的数，每次都会减去 $a$ 导致 $a$ 的出现次数超过 $2$ 次。

- 每次减去大于等于 $\sqrt x$ 的因子，$x$ 为目前的数，并特判指数的情况，反例：$35$ 等由两个质数相乘的数，会减去多次较大的质数，导致出现次数超 $2$ 次。

- 记忆化搜索，没反例，但是时间复杂度会超。

在经过多次尝试后，我终于想到了一点，如果 $x$ 是形如 $2^k$ 的数，可以每次减去 $\frac x 2$ 直到变为 $1$。

那么，我们尝试把给定的数变为 $2^k$ 的形式。

发现给定的数离 $2^k$ 的差距就只是二进制下除了最高位的 $1$。

所以可以先每次减去 $\operatorname{lowbit}(x)$，直到 $x$ 为 $2^k$，然后再每次减去 $\frac x 2$。

发现前半部分最多减去了一次 $2^l$ 其中 $0\le l <k$。

然后后半部分会减去 $2^m$ 其中 $0\le m <k$ 各一次。

所以不会超过 $2$ 次的限制。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int lowbit(int x){return x&(-x);}
int T,n,ans[1005],cnt,nn;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n),cnt=0,nn=n;
		while(n&(n-1))//判断是否变为2^k
		{
			ans[++cnt]=lowbit(n),n-=lowbit(n);//记录操作
		}
		while(n>1) ans[++cnt]=n/2,n/=2;//每次减去n/2
		printf("%d\n",cnt+1);//操作cnt次，共cnt+1个数
		for(int i=1;i<=cnt;++i)
		{
			printf("%d ",nn),nn-=ans[i];
		}
		printf("%d\n",nn);
	}
	return 0;
}
```

---

## 作者：白简 (赞：0)

### 题目大意
给定一个整数 $x$，目标是在最多 $1000$ 次操作内把 $x$ 减到 $1$。

定义一个操作：选择一个 $x$ 的因数 $d$，把 $x$ 修改为 $x-d$。

同时还有一个额外的限制：相同的 $d$ 值不能选择超过 $2$ 次。

（$1\le t\le 10^3,2\le x\le 10^9$）。
### 思路
可以先考虑最简单的情况，$x=2^k$。

对于这种情况，我们直接每次使其减去 $2^{k-1}$ 就可以，由于每次减完后相当于除以 $2$，所以不超过 $\log x$ 次。

那么如果 $x \neq 2^k$ 怎么办呢？把它变成 $2^k$ 的形式。

每次减去 $\operatorname{lowbit}(x)$，也是不超过 $\log x$ 次。

所以总的操作数一定符合条件。

以上两类操作中，一类中的各项操作肯定没有相同的，两类中相同的操作也不可能超过 $2$ 个，所以符合相同因数出现次数不超过 $2$ 的条件。

代码实现很简单，直接模拟就好了。

---

## 作者：Flandres (赞：0)

将整数 $x$ 拆分成二进制形式，对于因数 $d$，我们每次选取当前 $x$ 的 $\text{lowbit}$ 并减去，直到剩下最高位，再不断的从次高位开始减直到剩下 $1$。这样的方案一定是符合题意的，每个因数显然最多被选中两次。

以二进制数字 $10101$ 为例:

$10101\to 10100\to 10000\to 01000\to 00100\to 00010\to 00001$

code：

```cpp
#include<bits/stdc++.h>
int T,n;
std::queue<int> q;
int main(){
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cin>>T;
	while(T--){
		std::cin>>n;
		int cnt=__builtin_popcount(n);
		for(int i=1;i<cnt;++i){
			q.push(n);
			n-=n&-n;
		}
		for(;n;n>>=1)q.push(n);
		std::cout<<(int)q.size()<<'\n';
		while(!q.empty()){
			std::cout<<q.front()<<' ';
			q.pop();
		}
		std::cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Epoch_L (赞：0)

## Solution
对于 $x=2^k$，每次取其因数 $2^{k-1}$，即可在 $\log x$ 此内变为 $1$ ，如 $32\to 16\to 8\to 4\to 2\to 1$。

考虑推广到普遍情况，只需要将 $x$ 通过减法变成 $2^k$，我们把 $x$ 进行二进制拆分，即 $x=2^{k_1}+2^{k_2}+\cdots +2^{k_n}$，其中 $k_1< k_2 <\cdots k_n$。

很显然此时 $2^{k_1}$ 一定是 $x$ 的约数，我们把其减掉，然后重复以上操作。

上文中 $2^{k_1}$ 即为二进制下最低位的 $1$，使用树状数组中的 `lowbit` 函数即可。

总操作次数在 $\log x$ 级别，并且每一轮减的数都是唯一的，重复只有可能出现在两轮之间。

## Code
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb emplace_back
#define push emplace
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
bool Mbe;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
vector<int>ans;
int lowbit(int x){return x&-x;}
void solve(){
  int x;read(x);
  ans.clear();
  ans.pb(x);
  int t=lowbit(x);
  while(x!=t){
    x-=t;
    ans.pb(x);
    t=lowbit(x);
  }
  while(x!=1){
    x/=2;
    ans.pb(x);
  }
  printf("%d\n",(int)ans.size());
  for(int i:ans)printf("%d ",i);
  putchar('\n');
}

bool Med;
int main(){
  fprintf(stderr,"%.3lf MB\n",(&Med-&Mbe)/1048576.0);
  int T;read(T);
  while(T--)solve();
  cerr<<1e3*clock()/CLOCKS_PER_SEC<<" ms\n";
  return 0;
}
```

---

## 作者：User_Authorized (赞：0)

## 题意

给定一个整数 $x$，定义一个操作：

> 选择一个 $x$ 的因数 $d$，把 $x$ 修改为 $x-d$。

限制相同的 $d$ 值不能选择超过 $2$ 次，需要在最多 $1000$ 次操作内把 $x$ 操作至 $1$，求操作序列。

（$1 \le x \le 10^9$）。

## 题解

**[更好的阅读体验](https://www.cnblogs.com/User-Unauthorized/p/solution-CF1864C.html)**

为便于表达，下文中设 $n$ 为待操作的数字。

发现 $2$ 的正幂次数可以在相同的因子最多选择 $1$ 次的情况下操作至 $1$，操作方法如下：

$$2^x \xrightarrow{2^{x - 1}} 2^{x - 1} \xrightarrow{2^{x - 2}} 2^{x - 2} \cdots 2 \xrightarrow{1} 1$$

即对于 $n = 2^x$，选择因子 $2^{x - 1}$。

下面考虑 $n$ 不为正幂次数的情况，考虑将 $n$ 表达为 $b \cdot 2^x$，其中 $b$ 为奇数，$x$ 为非负整数。

考虑选择因子 $2^x$，那么 $n$ 变为 $\left(b - 1\right) \cdot 2^x$，此时 $b - 1$ 为偶数，可以将因子 $2$ 提出，使其变为 $n = \dfrac{b - 1}{2^y} 2^{x + y}$，其中 $2^y = \operatorname{lowbit}(b - 1)$。，可以发现因为 $b$ 为奇数，所以有 $y \ge 1$，在下次操作时选择的因子一定大于 $2^x$，所以在 $b$ 消为 $1$ 之前，每个因子最多选择一次。$b$ 消为 $1$ 之后使用上文介绍的适用于 $2$ 的正幂次数的操作即可。

综上，我们可以在 $\mathcal{O}(\log n)$ 次数内将 $n$ 操作至 $1$。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        valueType x = 0, y = 0, K = 1;

        while (N % 2 == 0) {
            ++x;

            K *= 2;

            N /= 2;
        }

        ValueVector result;

        while (N > 1) {
            result.push_back(K);

            N -= 1;

            while (N % 2 == 0) {
                ++x;

                K *= 2;

                N /= 2;
            }
        }

        while (x > 0) {
            result.push_back(K / 2);

            K /= 2;
            x -= 1;
        }

        ValueVector ans;

        ans.push_back(1);

        for (auto iter = result.rbegin(); iter != result.rend(); ++iter) {
            ans.push_back(ans.back() + *iter);
        }

        std::reverse(ans.begin(), ans.end());

        std::cout << ans.size() << '\n';

        for (auto const &iter: ans) {
            std::cout << iter << ' ';
        }

        std::cout << '\n';
    }

    std::cout << std::flush;

    return 0;
}
```

---

## 作者：Drind (赞：0)

### 题目解析
不难发现所有 $2^n$ 都可以轻松化为 $1$，而且每个数字只需要使用一遍，我们可以把问题转化为每个数字只使用一遍转化为 $2^n$。那么将这个数字二进制拆分，从最低位开始一个一个去掉即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;

int a[N],dis[N];
inline void fake_main(){
	int n,t,cnt=0,flag=0,ans=0; cin>>n; t=n;
	while(n){
		a[++cnt]=n%2;//二进制拆分
		n/=2;
	}
	dis[++ans]=t;
	for(int i=1;i<cnt;i++){
		if(a[i]==1){
			t-=pow(2,i-1);
			dis[++ans]=t;//去掉为1的位记录答案
		}
	}
	for(int i=cnt-1;i>=1;i--){
		dis[++ans]=pow(2,i-1);//2^n消到1
	}
	cout<<ans<<"\n";
	for(int i=1;i<=ans;i++) cout<<dis[i]<<" "; cout<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--) fake_main();
}


```

---

## 作者：shipeiqian (赞：0)

# CF1864C 题解

## 题意

给定一个 $n$，进行任意次操作，每次操作可以使 $n=n-p (n\mod p=0)$，且同样的 $p$ 至多使用 $2$ 次。求出将 $n$ 减至 $1$ 的操作次数（不必最小化）及过程。

## 思路

如果暴力枚举 $n$ 的因子，再进行 dfs，时间复杂度可达 $O(n\sqrt n)$，显然不行。

我们可以发现一个规律就是：如果一个数是 $2^k$，那么将它化为 $1$，只要每次除以二即可，而且这样每次使用的 $p$ 均为 $2^{k-1}$，不会出现使用多次的现象。

那么如何把一个数化为 $2^k$ 呢？可以发现，如果 $x=2^k$，那么在二进制下可以表示为 $1 \underbrace{00 \dots 00}_{k\text{ 个 }0}$，而 `lowbit` 刚好可以处理这个东西，因为其返回的是二进制下末尾 $0$ 的个数，只要这个值与原数相同就说明是 $2^k$ 了；如果不是，那只要减去 `lowbit(x)`，将末尾逐渐化为只剩下 $0$ 即可。

## Code

```cpp
//核心部分
int n;
int lowbit(int x){return x&-x;}
void solve(){
    cin >>n;
    vector<int>ans;
    while(lowbit(n)!=n){
        ans.push_back(n);
        n-=lowbit(n);
    }//化为 2^k
    while(n!=1){
        ans.push_back(n);
        n/=2;
    }//不断/2化为1
    cout <<ans.size()+1 <<"\n";
    for(auto x:ans)cout <<x <<" ";
    cout <<"1\n";
}

```









---

