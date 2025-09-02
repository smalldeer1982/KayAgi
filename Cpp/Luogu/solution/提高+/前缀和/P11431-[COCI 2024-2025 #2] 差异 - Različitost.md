# [COCI 2024/2025 #2] 差异 / Različitost

## 题目背景

译自 [COCI 2024/2025 #2](https://hsin.hr/coci/) T3。$\texttt{2s,0.5G}$。满分为 $90$。

## 题目描述


给定无限长的，周期长度为 $n$ 的非负整数序列 $a$ 的前 $n$ 项 $a_1,a_2,\cdots,a_n$。

给定无限长的，周期长度为 $m$ 的非负整数序列 $b$ 的前 $m$ 项 $b_1,b_2,\cdots,b_m$。

给定正整数 $k$，求出 $\displaystyle \left(\sum_{1\le i\le k} a_i\oplus b_i\right)\bmod \left(10^9+7\right)$。

## 说明/提示


对于 $100\%$ 的数据，保证：

- $1\le n,m\le 2\times 10^5$；    
- $1\le k\le 10^{18}$；
- $0\le a_i,b_i\le 10^{18}$。


| 子任务编号 | $k\le$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $2\times 10^5$ |    |   $ 25 $   |  
| $ 2 $    | $10^{18}$ |  A |  $ 13 $   |  
| $ 3 $    | $10^{18}$  | B | $ 19$   |
| $ 4 $    | $10^{18}$  |  | $ 43 $   |

- 特殊性质 A：$n=m$。
- 特殊性质 B：$n=1$。


## 样例 #1

### 输入

```
3 2 10
1 6 4
5 2```

### 输出

```
33```

## 样例 #2

### 输入

```
10 5 30
5 16 2 10 7 2 4 20 5 12
4 11 14 23 5```

### 输出

```
435```

# 题解

## 作者：SunburstFan (赞：7)

# [COCI 2024/2025 #2] 差异

## 题目大意

给定三个正整数 $n,m,k$，以及两个周期为 $n,m$ 的无限整数序列 $a$ 和 $b$。构造无限序列 $c$，求：

$$\sum _{i=1}^{k} c_i=a_i \oplus b_i$$

## 解题思路

读题可以发现 $c$ 的循环节长度为 $\operatorname {lcm}(n,m)$，那么就有一个 $O(\operatorname {lcm}(n,m))$ 的暴力，可以获得 57pts。

考虑优化这个暴力，不难想到拆位计算贡献，对于每一个二进制位，先求出在周期内的贡献，再求出周期外的散段的贡献。

可以手模一下计算 $c$ 的过程，不难发现，对于序列 $a$ 中的元素 $a_i$，第一个与其进行异或运算的序列 $b$ 元素一定是 $b_i$，第二个则是 $b_{(i+n) \mod m}$，以此类推。

如果将这些元素全部一一建边，**最终一定会形成一个环，且环的长度是 $\frac {m}{\gcd(n,m)}$**。

考虑将这些环一个个存下来，然后跑一下环上前缀和，就可以开始统计贡献：

计算出周期的个数 $c$ 和剩余长度 $rst$。

- 如果 **$a_i=0$**，则对应的 $b$ 序列中该位的贡献就是整个环的总和乘 $c,rst$ 的贡献可以通过前缀和相减得到。

- 如果 **$a_i=1$**，则产生的贡献就是 $b$ 序列中该位 $0$ 的个数，即将总环长减去环的总和乘 $c,rst$ 的贡献就是拿 $rst$ 减去这一段的和得到。

统计完一位的贡献后乘上 $2^{bit}$，$bit$ 为当前位数，全部加起来就是答案。

**核心代码**：

这里给出计算每一位贡献的函数 `calc`。

```cpp
vector<int> p(2e5+5,0);
int calc(vector<int> &a,vector<int> &b){
    vector<vector<int> >cir(2e5+5,vector<int>(1));
    
    int GCD=__gcd(n,m),t=m/GCD;
    for(int i=0;i<GCD;i++){
        int head=i;
        for(int j=0;j<t;j++){
            p[head]=j+1; //记录该位对应的编号
            cir[i].push_back(b[head]); //记录这个环
            head=(head+n)%m; //更新指针
        }
        for(int j=0;j<t;j++){
            cir[i].push_back(cir[i][j+1]); //将环复制一遍，方便跑前缀和
        }
        for(int j=1;j<cir[i].size();j++){
            cir[i][j]=(cir[i][j]+cir[i][j-1])%mod; //计算前缀和
        }
    }

    int res=0;
    for(int i=0;i<n;i++){
        if(i>k)break;

        int x=p[i%m]; //找到编号
        int c=(k-i)/(n*t)%mod,rst=(k-i)%(n*t);
        // 算出 c 和 rst
        rst=(rst+n-1)/n; //向上取整
        if(a[i]==0){ //计算贡献部分，可以对照解题思路
            res=(res+c*cir[i%GCD][t]%mod)%mod;
            res=(res-cir[i%GCD][x-1]+cir[i%GCD][x+rst-1]+mod)%mod;
        }
        else{
            res=(res+c*(t-cir[i%GCD][t])%mod)%mod;
            res=(res+rst+cir[i%GCD][x-1]-cir[i%GCD][x+rst-1]+mod)%mod;
        }
    }

    return res;
}
```

---

## 作者：HomuraAkemi (赞：6)

拆位是平凡的。接下来只需要考虑 $01$ 序列上的问题。

显然 $c_i=a_i\oplus b_i$ 这个序列的循环节长度为 $\operatorname{lcm}(n,m)$。对于长度为 $\operatorname{lcm}(n,m)$ 的整段是不难拆贡献后计算的，接下来只需要考虑长度 $\lt \operatorname{lcm}$ 的散段。

经典结论就是 $x\to (x+n)\bmod m$ 连边会形成若干个环，每个环长为 $m/\gcd(n,m)$（证明留作练习）。然后注意到每一个环的含义是：$a_i$ 第一次匹配的是 $b_i$，第二次是 $b_{(i+n)\bmod m}$，依此类推。那么直接计算它能取到几次，然后利用环上前缀和计算即可。

细节较多，代码实现较为繁琐。精细实现的话，时间复杂度 $\Theta((n+m)\log V)$。

Madoka 酱可爱，亲亲 Madoka 酱！

---

## 作者：kkxacj (赞：3)

有趣的题。

#### 思路

看到异或就想到拆位，也只有拆位后才能快速计算。

由于 $k$ 很大，考虑从每个值照成贡献下手，先假设 $n > m$，如果不是就把两个数组调换一下就好了，容易发现，$b$ 数组可以分解为若干循环节，每个循环节会是若干个 $a_i$ 要用到的，只不过不同的 $a_i$ 所在的循环节开始位置不同。

循环节是很好找的，具体的从左到右枚举，找到一个还没有被分配到一个循环的点，从它开始循环直到回到它就结束，这样就得到一个新的循环，这里面所有值 $\le n$ 的就是 $a$ 数组中需要这个循环的点和位置。

知道后，我们搞一个前缀和数组，然后稍微盘一下边界情况后好了，具体实现的话就看代码吧。

**code**


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 2e5+10,mod = 1e9+7;
int n,m,k,a[N],b[N],sum[N],sum1[N],v[N],v1[N],st[N],cnt1,st1[N],st2[N],cnt,o,ans,o1;
inline int solve(int x,int y)
{
	int o1 = 1+(k-y)/n;//这个数出现多少次
	//从x开始，k已经进行了y次，接下来每n个多出现一次 
	int ans = sum[cnt]*((o1/cnt)%mod)%mod;//>cnt的直接先算了 
	if(o1%cnt <= cnt-x+1) ans = (ans+sum[x+o1%cnt-1]-sum[x-1])%mod;//它的位置在x，往后延o1%cnt个，分讨一下 
	else ans = (ans+sum[cnt]-sum[x-1]+sum[o1%cnt-(cnt-x+1)])%mod;
	return ans;
}
inline int solve1(int x,int y)
{
	int o1 = 1+(k-y)/n;
	int ans = sum1[cnt]*((o1/cnt)%mod)%mod;
	if(o1%cnt <= cnt-x+1) ans = (ans+sum1[x+o1%cnt-1]-sum1[x-1])%mod;
	else ans = (ans+sum1[cnt]-sum1[x-1]+sum1[o1%cnt-(cnt-x+1)])%mod;
	return ans;
}
signed main()
{
	read(n),read(m),read(k);
	for(int i = 1;i <= n;i++) read(a[i]);
	for(int i = 1;i <= m;i++) read(b[i]);
	if(n > m)//我们需要钦定n<m 
	{
		for(int i = 1;i <= n;i++) swap(a[i],b[i]);
		swap(n,m);
	}
	for(int j = 0;j <= 63;j++)//枚举每一位 
	{
		for(int i = 1;i <= m;i++) v[i] = v1[i] = 0;
		for(int i = 1;i <= n;i++)
			if(!v1[i])
			{
				o = i,cnt = 0; cnt1 = 0;
				while(!v1[o])
				{
					v1[o] = 1,st[++cnt] = o;
					if(o <= n) st1[++cnt1] = o,st2[cnt1] = cnt;
					o = (o+n-1)%m+1;//直接去找，最多m次，复杂度可以保证 
				}
				for(int i = 1;i <= cnt;i++)	
				{
					sum[i] = sum[i-1]+((b[st[i]]&(1ll<<j))!=0);//1的 
					sum1[i] = sum1[i-1]+((b[st[i]]&(1ll<<j))==0);//0的 
				}
				for(int i = 1;i <= cnt1;i++)
				{
					o = st1[i];
					if((a[o]&(1ll<<j))) ans = (ans+solve1(st2[i],st1[i])*((1ll<<j)%mod)%mod)%mod;
					else ans = (ans+solve(st2[i],st1[i])*((1ll<<j)%mod)%mod)%mod;//计算贡献 
				}
			}
	}
	print(ans); flush();
	return 0;
}
/*
3 2 10
5 2
101 010
1 6 4
001 110 100
为了加速必须拆位，这个很显然
先假设n<m
考虑每个a_i异或的那些点第j位为0/1的分别是多少，前缀和统计一下 

1 2 1 2 1 2 1
1 2 3 1 2 3 1
*/
```

---

## 作者：Ybll_ (赞：2)

# 思路：

本题有**异或**，考虑**拆位**，设一个数为 $x$，它二进制中的第 $i$ 位可以用 `x>>i&1` 来表示，

我们先枚举这些数的二进制的每一位，每一个数的第 $i$ 位处理完后，就统一处理第 $i$ 位的贡献，

对于每一个 $a$ 中的每一个数，它在 $b$ 中对应的数是按照一个周期进行循环的，举个例子：

当 $n=6,m=4$ 时，共有两种周期，每种周期两个数，

$a_1$ 对应 $b_1$ 和 $b_3$,$a_2$ 对应 $b_2$ 和 $b_4$,

$a_3$ 对应 $b_3$ 和 $b_1$,$a_4$ 对应 $b_4$ 和 $b_2$,

$a_5$ 对应 $b_1$ 和 $b_3$,$a_6$ 对应 $b_2$ 和 $b_4$。

然后就可以发现，一共有 $\gcd(n,m)$ 种周期，每种周期有 $m\div \gcd(n,m)$ 个数，这几种周期就可以合成一个长度为 $\operatorname{lcm(n,m)}$ 的大周期。

对于第 $i$ 种周期，设第 $j$ 个数在 $b$ 中的下标为 $C_{i,j}$，那么就有：

$$$C_{i,1}=i,C_{i,j+1}=(C_{i,j}+n)\bmod m$$$

然后对于 $a_i$，它所对应的周期就是第 $i\bmod \gcd(n,m)$ 个。

为了方便后面的前缀和，我们在存周期时要多存一段周期，再做前缀和，

由于我们拆了位，所以前缀和数组中存的是每个周期拆违后 $1$ 的个数。

然后就是一个~~简单的~~周期问题了，为了计算散数的贡献，我们在处理每个周期时用 $p_i$ 记下 $b_i$ 在周期中是多久出现的，还是上面那个 $n=6,m=4$ 的例子，

两个周期，分别是：

1. $b_1$ 和 $b_3$；
2. $b_2$ 和 $b_3$。

此时就有 $p_1=1,p_2=1,p_3=2,p_4=2$。

现在就来做周期问题，

我们遍历 $a$ 中每个数的第 $j$ 位，设第 $i$ 个数 $A_i$ 表示 $a_i$ 的第 $j$ 位，$num$ 为第 $i\bmod m$ 个周期的总个数，

此时的 $p_{(i-1)\bmod m+1}$ 就是这个数所对应的周期中的那个数的位置，$num=(k-i+1)\div\operatorname{lcm(n,m)}$，

现在整个的周期的贡献可以算出来了，就需要算散出来的那几个，我们记 $rem$ 为当前剩下的数的个数，即 $rem=(k-i+1)\bmod \operatorname{lcm(n,m)}$，

但剩下的 $rem$ 个数中，有些数属于这个周期，有些数不属于，这时 $\lceil rem\div n \rceil$ 就是这个周期还剩多少个散的数了。

最后就是计算贡献，注意**异或的两种情况**和**取模**，还有最后的**二进制转十进制**（看代码）。

# 代码：

为了方便，这里的代码部分数组下标从 $0$ 开始，部分数组下标从 $1$ 开始，某些变量或数组的名称与上文不同。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define N 200005
using namespace std;
int n,m,k,A[N],B[N],ans,gcd,p[N];
vector<int>v[N];
int solve(vector<int>a,vector<int>b)
{
	int t=m/gcd,res=0;
	for(int i=0;i<gcd;i++)
	{
		v[i].clear();
		v[i].push_back(0);
		for(int j=0,k=i;j<t;j++,k=(k+n)%m)//找周期
		{
			p[k]=j+1;
			v[i].push_back(b[k]);
		}
		for(int j=0;j<t;j++)//多存一轮周期 
		{
			v[i].push_back(v[i][j+1]);
		}
		for(int j=1;j<v[i].size();j++)//前缀和
		{
			v[i][j]+=v[i][j-1];
		}
	}
	for(int i=0;i<n;i++)
	{
		int j=p[i%m],num=(k-i)/(n*m/gcd)%mod,rem=((k-i)%(n*m/gcd)+n-1)/n;
		if(i==k)break; 
		if(a[i]==0)res=((res+num*v[i%gcd][t]%mod)%mod/*整个周期*/+v[i%gcd][j+rem-1]-v[i%gcd][j-1]/*散数*/)%mod;//a[i]为0时的贡献
		else res=((res+num*(t-v[i%gcd][t])%mod)%mod/*整个周期*/+rem-v[i%gcd][j+rem-1]+v[i%gcd][j-1]/*散数*/)%mod;//a[i]为1时的贡献
	}
	return res;
}
signed main()
{
	cin>>n>>m>>k;
	for(int i=0;i<n;i++)
	{
		cin>>A[i];
	}
	for(int i=0;i<m;i++)
	{
		cin>>B[i];
	}
	gcd=__gcd(n,m);
	for(int k=0,j=1;k<62;k++,j=j*2%mod)
	{
		vector<int>a,b;
		for(int i=0;i<n;i++)
		{
			a.push_back(A[i]>>k&1);
		}
		for(int i=0;i<m;i++)
		{
			b.push_back(B[i]>>k&1);
		}
		ans=(ans+solve(a,b)*j%mod)%mod;//二进制转十进制
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：M1saka16I72 (赞：2)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-p11431)

来点不带脑子的做法，但有点卡常，在 COCI 的土豆评测机上过不去。

## 思路

不妨设 $n\leq m$，且下文的所有下标均从 $0$ 开始。

看见异或还要求和可以先拆位。

拆位后考虑对于每个 $a_i$ 求出其贡献，设 $f_{i,j}$ 为第 $i$ 个数在第 $j$ 次出现时会与谁异或，则有 $f_{i,j}=(f_{i,j-1}+n)\mod m$，初始状态为 $f_{i,0}=i$。看到这种东西可以直接倍增，设 $sum_{i,j}$ 代表 $a_i$ 第 $j$ 次出现时当前位已经累计遇到了多少个 $1$（那么 $0$ 的个数就是 $2^j$ 减去 $1$ 的个数），则有 $sum_{i,j}=sum_{i,j-1}+sum_{f_{i,j-1},j-1}$。

于是对于 $a_i$，其在最终序列中的出现次数为 $\lfloor\frac{k}{n}\rfloor+[i< (k\mod n)]$，倍增算完 $sum$ 数组后直接统计即可，复杂度是 $\mathcal{O}(n\log^2 V)$。

时限不怎么宽裕，但在 lg 评测机上压力不大。

---

