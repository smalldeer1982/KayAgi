# Interesting Sequence

## 题目描述

Petya and his friend, robot Petya++, like to solve exciting math problems.

One day Petya++ came up with the numbers $ n $ and $ x $ and wrote the following equality on the board: $ $$$n\ \&\ (n+1)\ \&\ \dots\ \&\ m = x, $ $  where  $ \\&amp; $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#AND">bitwise AND operation</a>. Then he suggested his friend Petya find such a minimal  $ m $  ( $ m \\ge n$$$) that the equality on the board holds.

Unfortunately, Petya couldn't solve this problem in his head and decided to ask for computer help. He quickly wrote a program and found the answer.

Can you solve this difficult problem?

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775C/3708862555546ebb5c352c2d2207eacbd490398b.png)

## 说明/提示

In the first example, $ 10\ \&\ 11 = 10 $ , but $ 10\ \&\ 11\ \&\ 12 = 8 $ , so the answer is $ 12 $ .

In the second example, $ 10 = 10 $ , so the answer is $ 10 $ .

In the third example, we can see that the required $ m $ does not exist, so we have to print $ -1 $ .

## 样例 #1

### 输入

```
5
10 8
10 10
10 42
20 16
1000000000000000000 0```

### 输出

```
12
10
-1
24
1152921504606846976```

# 题解

## 作者：BFSDFS123 (赞：10)

首先我们要了解一下 ``lowbit``。

大家都知道 ``lowbit(x)=x&(-x)``。

``lowbit(x)`` 的意义是 $x$ 的二进制位下最低为的一所代表的十进制值。

知道了这个，我们就可以来做这道题了。

----

容易发现，如果有解，则答案一定是执行若干次 ``n+=lowbit(n)`` 后的 $n$ 的结果。

为什么呢？

容易发现，如果有解，则一定有 $n\ge x$，而且当我们把 $n$ 和 $x$ 都分解为二进制时，若一相同的二进制位上，$n$ 的这个位置上的值是 $0$，而 $x$ 的是 $1$，则一定无解。

我们注意到，$0$ 对任何数执行与操作都是 $0$。

根据这一特点，我们容易发现，$x \& x+1 \& \dots\& x+\operatorname{lowbit}(x)-1=x$。

这也很容易证明，因为直到 $x+\operatorname{lowbit}(x)$ 时，只有一个原来为 $1$ 的一位变成了 $0$，此时与值才会变。

之前，尽管进行了多次加一，但是最多是将原来为 $0$ 的位进行变换，不管怎样变换，与值一直不变。

所以根据这个特点，我们就可以一直执行 ``n+=lowbit(n)``，同时，将与值不断更新，当与值等于 $x$ 的时候，就输出当前的 $n$ 。

注意，如果执行过程中出现了与值小于 $x$ 时，则无解。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
#define ull unsigned long long
#define ll long long
using namespace std;
//#define int long long
long long lowbit(long long x)
{
    return x&(-x);
}
void work()
{
    long long a,b;
    scanf("%lld%lld",&a,&b);
    long long na=a,nb=b;
    vector<long long> A,B;
    while(a)
    {
        A.push_back(a&1);
        a>>=1;
    }
    while(b)
    {
        B.push_back(b&1);
        b>>=1;
    }
    
    while(A.size()<B.size())
    {
        A.push_back(0);
    }
    while(B.size()<A.size())
    {
        B.push_back(0);
    }
    for(int i=0;i<A.size();i++)
    {
        if(A[i]!=B[i] && !A[i])
        {
            puts("-1");
            return ;
        } 
    }

    // 查询是否有相同的位上 n 为 0 且 x 为 1
    a=na;
    while(na!=nb)
    {
        a+=lowbit(a);
        na=na&a;
        
        if(na<nb)
        {
            puts("-1");
            return ;
        }
    }
    printf("%lld\n",a);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        work();
    }
    return 0;
}

```

---

## 作者：xiaomuyun (赞：9)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1775C)
- [Codeforces 题目传送门](https://codeforces.com/problemset/problem/1775/C)

Update 2023/1/11：修改了“主要算法”的表述。

Update 2023/1/11：把原版彻底删掉了。

## 思路分析

我们把 $n$ 和 $x$ 先转换成二进制来看。

### 主要算法

可以发现，能做的只有把 $n$ 的二进制表示中的一些 $1$ 改为 $0$。思考一下容易推出，将二进制位的 $1$ 改为 $0$，做法即为使这个位的左边一位（即更高一位）增加成 $1$，那么这一位在与的过程中就会出现 $0$ 了。因此需要做的就是使最高的一个满足需要从 $1$ 改为 $0$ 的位的再高一位从 $0$ 变成 $1$。但是有一些条件会导致它无解，我们再来看看。

### 无解

#### 第一个

很容易理解，如果在一个二进制位上，$n$ 是 $0$，$x$ 是 $1$，因为 $0$ 是怎么与都与不出 $1$ 的，所以无解。

#### 第二个

将我们找到的 $n$ 的二进制表示中最左边的和 $x$ 不同且 $n$ 在这一位为 $1$，$x$ 在这一位为 $0$ 的二进制位设为第 $lst$ 位（从右数起），如果第 $lst+1$ 位是 $1$ 的话，意味着不能让第 $lst$ 位的 $0$ 改为 $1$ 了，所以无解。

#### 第三个

如果在查找的时候遇到一个需要从 $1$ 改为 $0$ 的二进制位，那么 $n$ 中这个二进制位右边不能出现任何一个已经定下来的 $1$（即 $x$ 的这一位也为 $1$），因为如果需要让高位的 $0$ 变成 $1$，这一位一定是会与 $0$ 的。

## 代码实现

上面讲得可能有点不清楚，可以结合代码看一下。

```cpp
#include<string>
#include<cstdio>
#define int long long
using namespace std;
int t,n,x;
inline string Change(int a){//十进制转二进制
	string ret="";
	while(a){
		if(a&1) ret="1"+ret;
		else ret="0"+ret;
		a>>=1;
	}
	while(ret.length()<64) ret="0"+ret;
	return ret;
}
inline int rechan(string a){//二进制转十进制
	int ret=0,c=1;
	for(int i=63;i>=0;--i){
		if(a[i]=='1') ret+=c;
		c<<=1;
	}
	return ret;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&x);
		string sn=Change(n),sx=Change(x);
		bool flag=false,f=false;
		int lst=66;
		for(int i=63;i>=0;--i){
			if(sn[i]!=sx[i]&&sx[i]=='1'){//第一种无解情况
				flag=true;
				break;
			}
			if(sn[i]==sx[i]&&sx[i]=='1') f=true;//统计前面是否有定下来的1
			if(sn[i]!=sx[i]&&sx[i]=='0'){
				lst=i;
				if(f){//第三种无解情况
					flag=true;
					break;
				}
			}
		}
		if(flag||sn[lst-1]=='1') printf("-1\n");//sn[lst-1]=='1'是第二种无解情况
		else if(lst==66) printf("%lld\n",x);//如果n和x完全相等就直接输出
		else{
			string t="";
			for(int i=0;i<=lst-2;++i) t+=sn[i];
			t=t+"1";
			while(t.length()<64) t=t+"0";//补右边的0
			printf("%lld\n",rechan(t));//转十进制
		}
	}
	return 0;
}
```

讲得可能有些不清楚，可以配合楼上大大的题解一起阅读。:)

---

## 作者：not_clever_syl (赞：8)

题目大意：

- 给你两个正整数 $n,x$ 求最小的 $m \geq n$ 使得 $[n,m]$ 区间内的所有数的按位与等于 $x$。
- $n,x \leq 10^{18}$。

首先我们可以先单独对 $n,x$ 的每一位考虑：

当$n,x$ 某一位一样时，不用动那一位。

当 $n=0,x=1$ 时，显然无解，输出 $-1$。

当 $n=1,x=0$ 时，考虑如何让 $m$ 的这个二进制位变为 $0$。

我们只需要找到最小的 $m$ 即可，因为如果存在 $m'>m$ 使得 $m'$ 的那一位为 $0$，那么 $m \in [n,m']$。

所以我们可以采用树状数组里的 $\operatorname{lowbit}$ 函数。

只要 $m$ 的那一位为 $1$，就加上 $\operatorname{lowbit}(x)$，直到 $m$ 的那一位为 $0$ 为止。

此时，我们把 $n$ 重新赋值为 $n \operatorname{and} m$，

如果 $m$ 让 $n \operatorname{and} m$ 的那一位的更低位不符合条件（即把 $n$ 的更低位的 $1$ 变为了 $0$），那么这个问题也无解，否则 $n$ 最后也需要变为 $n \operatorname{and} m$。

所以可以直接把 $n$ 变为 $n \operatorname{and} m$，然后检查 $n$ 是否有一位为 $0$ 且 $x$ 的那一位为 $1$。如果存在这样的位，输出 $-1$，否则继续检查 $n$ 的更高位。

这样，我们就可以做到 $O(\operatorname{log} n)$ 处理一个询问，总时间 $O(t\operatorname{log}n)$。

参考代码：
~~~cpp
#include<iostream>
using namespace std;
long long t,n,x,y,m;
long long lowbit(long long x){
	return x&-x;
}
bool f=0;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		if((~n)&x){//n某一位为0而x的那一位为1，无解，输出-1
			cout<<-1<<endl;
			continue;
		}
		f=0;
		m=n;
		for(y=1;n!=x&&y<=n;y<<=1){
			while((n&y)&&!(x&y)&&(m&y))m+=lowbit(m);//一直加上lowbit(m)直到m的那一位为0
			n&=m;
			f=f||bool((~n)&x);//m让比它低位的1变成了0，此时无解，输出-1
			if(f)break;
		}
		if(f){
			cout<<-1<<endl;
			continue;
		}
		cout<<m<<endl;
	}
}
~~~

---

## 作者：loser_seele (赞：6)

走了一圈没找到我这个奇怪的做法。

因为 $ a \And b \leq a $，于是答案有显然的单调性，考虑二分答案。

问题转化为了如何快速求出 $ l \And (l+1) \And (l+2) \And ... \And r $ 的值。

这是个经典问题，考虑拆位算贡献，对每一个位上分类讨论出这位是 $ 0 $ 还是 $ 1 $，然后合并答案即可。

时间复杂度 $ \mathcal{O}(T\log^2{\max a_i}) $，其中一个 $ \log $ 来自二分，另一个来自拆位算贡献的过程，可以通过。注意计算过程中可能出现的溢出问题。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define LL unsigned long long
LL cnt[70],ans1,ans2;
void calc(LL x,int f)
{
	for(int i=63;i>=0;i--)
		if ((x>>i)&1ll)
        {
			cnt[i]+=f*(x%(1LL<<i)+1);
			for(int j=i-1;j>=0;j--)
			cnt[j]+=f*(1LL<<(i-1));
		}
}
void solve(LL a,LL b)
{
	memset(cnt,0,sizeof(cnt));
	calc(b,1);
	if (a>1) 
    calc(a-1,-1);
	ans1=ans2=0;
	int t1,t2;
	for(int i=63;i>=0;i--)
    {
		t1=t2=0;
		ans1<<=1;
		ans2<<=1;
		if (cnt[i]) 
        ans1++;
		if (cnt[i]==b-a+1) 
        ans2++;
	}
}
signed main()
{
	LL n,m;
	int T;
	cin>>T;
	for(int Case=1;Case<=T;Case++)
    {
		cin>>n>>m;
        unsigned long long l=n,r=5e18,ans=-5e18;
        while(l<r)
        {
        unsigned long long mid=(l+r)>>1;
		solve(n,mid);
        if(ans2>m)
        l=mid+1;
        else
        r=mid;
        }
        solve(n,l);
        if(ans2!=m)
        cout<<-1<<'\n';
        else
		cout<<l<<'\n';
	}
}
```


---

## 作者：Ray1 (赞：4)

核心是将 $n,x$ 的每个二进制位拆开，枚举每一位，然后分情况讨论。

定义两个变量 $Max,Min$ 分别表示答案的最大值和答案的最小值。

1. 如果 $x$ 此位为 $1$，$n$ 此位为 $0$，那么不可能通过 & 操作使 $n$ 的此位变成 $1$，无解输出 $-1$。  
2. 如果 $x$ 此位为 $1$，$n$ 此位为 $1$，& 操作可能将 $n$ 的此位变成 $1$，需要更新 $Max$ 为【此位为 $0$ 且大于 $n$ 的最小正整数】$-1$。  
3. 如果 $x$ 此位为 $0$，$n$ 此位为 $1$，我们需要用 & 操作将 $n$ 的此位变成 $0$，需要更新 $Min$ 为【此位为 $0$ 且大于 $n$ 的最小正整数】。  
4. 如果 $x$ 此位为 $0$，$n$ 此位为 $0$，无论多少 & 操作都不会影响 $n$ 的此位了，跳过。

【此位为 $0$ 且大于 $n$ 的最小正整数】计算方式见代码。

最后判断 $Min<Max$ 时有解，输出 $Min$；反之无解输出 $-1$。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,x;
void solve(){
	long long Max=5e18+1,Min=-1;
	for(long long i=1;i<=4e18;i<<=1){
		bool a=n&i,b=x&i;
		if(b){
			if(!a)return cout<<-1,void();
			Max=min(Max,n/i*i+i);
		}else if(a)Min=max(Min,n/i*i+i);
	}
	if(Max<=Min)cout<<-1;
	else cout<<Min;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(cin>>t;t--;)cin>>n>>x,solve(),cout<<'\n';
}
```


---

## 作者：liujy_ (赞：3)

 一看数据范围哇塞 $10^{18}$，~~这题不可做~~。  
 这么大的数字又是位运算那肯定是要考虑二进制。我们把 $n$ 和 $x$ 转换成二进制，枚举二进制的每一位，分成以下几种情况需要我们操作。   
 - 对于当前二进制下的第 $i$ 位，$x$ 为 $1$，$n$ 为 $0$。这种情况一定是无解的。  
 - 对于当前二进制下的第 $i$ 位，$x$ 为 $0$，$n$ 为 $1$。这种情况我们需要算一个数 $sum1$ 表示我们至少要从 $n$ 往后跳 $sum1$ 个数，最后的结果第 $i$ 位才会是 $0$。对于每一个此种情况的 $sum1$ 我们取一个最大值就是我们最少要跳的个数。   
 - 对于当前二进制下的第 $i$ 位，$x$ 为 $1$，$n$ 为 $1$。这种情况我们需要算一个数 $sum2$ 表示我们至多能从 $n$ 往后跳 $sum2$ 个数，最后的结果第 $i$ 位才不会是 $0$。对于每一个此种情况的 $sum2$ 我们取一个最小值就是我们最多能跳的个数。  
 
 假设我们至少跳 $mx$ 步，最多跳 $mn$ 步，如果 $mx$ 大于 $mn$ 那么无解，因为我们必须满足的两个条件相互矛盾。  
 那么我们最后要解决的事就是对于二进制下的第 $i$ 位，我们要跳几个数才能使得它变为另一个从 $0$ 变 $1$ 或从 $1$ 变 $0$。显然假设 $n$ 在二进制下前 $i-1$ 位的值为 $s$，那么要跳的个数就是 $2^i-s$。   
 具体看代码。   
 ```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const long long INF=5e18+5;
int t;long long n,x,mx,mn;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&n,&x);
		long long s=0;mx=0,mn=INF;
		bool p=0;
		for(int i=0;i<63;i++){
			if((x&(1ll<<i))&&(n&(1ll<<i))==0){
				p=1;
				printf("-1\n");
				break ;
			}
			if((x&(1ll<<i))==0&&(n&(1ll<<i)))mx=max(mx,(1ll<<i)-s);
			if((x&(1ll<<i))&&(n&(1ll<<i)))mn=min(mn,(1ll<<i)-s-1);
			s+=(n&(1ll<<i));
		} 
		if(p)continue ;
		if(mx>mn)printf("-1\n");
		else printf("%lld\n",n+mx);
	}
	return 0;
}


```




---

## 作者：World_Creater (赞：2)

我们发现当 $n$ 固定时，题目中给出的式子关于 $m$ 是单调递减的，因此考虑一个最简单的二分求出符合条件的 $m$。

问题在于，我们二分时，如何快速的 $\rm check$ 出 $n\&(n+1)\&(n+2)\cdots \&m$ 的值从而进行转移。

我们按二进制位从高到低考虑，对于某一位 $k$，如果 $n$ 的二进制位下这一位上是 $1$，**且 $m$ 此时不大于 $2^{k+1}$ 次方**，那么这一位是 $1$，此时我们令 $n=n-2^k,m=m-2^k$ 继续求解。

反之，如果 $k$ 不大于 $m$，说明这一位上**至少出现了一次进位**，即这一位上可能存在 $0$。同时，更低位也必然出现过进位，因此之后位不会产生贡献，退出求解。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf=5e18;
#define int long long
int calc(unsigned int l,unsigned int r)
{
	int res=0;
	for(signed i=63;i>=0;i--)
	{
		unsigned int k=1ull<<i;
		if((l&k)&&(r<=k*2))
		{
			res|=k;
			l-=k;
			r-=k;
		}
		else if(l>=k||r>=k) break ;
	}
	return res;
}
signed main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int a,b;
		cin>>a>>b;
		int l=a,r=5e18;
		while(l<r)
		{
			int mid=l+(r-l)/2,res=calc(a,mid);
			//cerr<<l<<" "<<r<<" "<<res<<"\n";
			if(res>b) l=mid+1;
			else r=mid;
		}
		if(calc(a,l)!=b) cout<<-1<<"\n";
		else 
		{
			while(l>a&&calc(a,l-1)==b) l--;
			cout<<l<<"\n";
		}
	}
}
```

---

## 作者：xiaruize (赞：2)

**思路**

手模一下样例一

$10 = (1010)_2$ , 发现需要将 $2^1$ 位的 $1$ 去掉

此时，就需要与一个 $2^1$ 位为 $0$ 的数, 同时其它位不能使 $10$ 改变, 且这个数 $\geq 10$

那么, 这个数的最小值显然为 $(1100)_2=12$

总结上面的过程, 得到以下这些结论

1. $n \And x=x$ , 否则是 `-1`

2. 考虑 $n - x$ 的值的二进制表示 (即 $n$ 中需要改为 $0$ 的二进制位的值), 发现所有的 $1$ 必须是 $n$ 中最低且连续的, 否则 `-1`

3. 设 $n-x$ 中最高位的 $1$ 在 $2^k$ 位上, 那么 $2^{k+1}$ 位在 $n$ 中一定为 $0$ , 否则 `-1` 

4. 否则答案为 $2^{k+1}-n+x$

**samples**

1. $n=11,m=4$
2. $n=20,m=16$
3. $n=11,m=9$

如果不能理解结论，建议手模一遍上述样例

**Code**

```cpp
/*
    Name:
    Author: xiaruize
    Date:
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define repp(i, x, y) for (int i = x; i >= y; i--)
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int N = 2e5 + 10;

// bool st;
int n, x;
int t;
// bool en;

void solve()
{
    cin >> n >> x;
    if (x > n)
    {
        cout << "-1" << endl;
        return;
    }
    if (x == n)
    {
        cout << n << endl;
        return;
    }
    int p = n - x;
    int d = p;
    for (int i = 0; i <= 61; i++)
    {
        if (p < 0)
        {
            cout << "-1" << endl;
            return;
        }
        if (p == 0 && (n & (1ll << i)))
        {
            cout << "-1" << endl;
            return;
        }
        if (p == 0)
        {
            cout << (1ll << i) - d + n << endl;
            return;
        }
        if (n & (1ll << i))
        {
            p -= (1ll << i);
        }
    }
}

signed main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // cerr<<(&en-&st)/1024.0/1024.0<<endl;
    // auto t_1=chrono::high_resolution_clock::now();
    cin >> t;
    while (t--)
        solve();
    // auto t_2=chrono::high_resolution_clock::now();
    // cout <<". Elapsed (ms): " << chrono::duration_cast<chrono::milliseconds>(t_2 - t_1).count() << endl;
    return 0;
}
```

---

## 作者：Mine_King (赞：2)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/17042849.html)

# C. Interesting Sequence

## Problem

[CF1775C Interesting Sequence](https://codeforces.com/contest/1775/problem/C)

**题目大意：**

给你两个数 $n,x$，求最小的 $m$ 使得 $n \And (n+1) \And (n+2) \And \ldots \And m = x$。无解输出 `-1`。

## Solution

手玩几个数据可以发现，一段连续的数与起来的结果一定是第一个数二进制下的一段后缀变成 $0$ 的形式。进一步可以发现当 $m$ 最小时只有 $n \And (n+1) \And (n+2) \And \ldots \And m = n \And m$。因为 $m$ 一定是最小的将 $n \oplus x$ 的最高位覆盖成 $0$ 的数，显然这个数的后面几位全为 $0$，故结论正确。

所以本题做法是先求出 $n \oplus x$ 的值，然后不断将 $n$ 的后缀推平直求出 $m$，然后判断是否合法即可。

无解的几种情况：$x > n$，$n \oplus x$ 的最高位的下一位在 $n$ 的二进制下是 $1$，$n \oplus x$ 不是 $n$ 的一段后缀。只有第二种情况需要特殊判断，因为剩下两种直接计算 $n \And m$ 一定 $\neq x$。但第二种情况直接计算得到的 $m$ 不适用于第二个结论。一个 Hack 数据是 `3 2`。

## Code

```cpp
// Think twice, code once.
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int T;
long long n,x;

int main() {
	scanf("%d",&T);
	while (T--) {
		scanf("%lld%lld",&n,&x);
		if (n==x) {printf("%lld\n",n);continue;}
		long long m=n^x;
		long long ans=1;
		long long nn=n;
		while (ans<=m) {
			if (nn&ans) nn^=ans;
			ans<<=1;
		}
		// printf("%lld %lld\n",ans,nn);
		if (n&ans) {puts("-1");continue;}
		else {
			nn|=ans;
			if ((n&nn)==x) printf("%lld\n",nn);
			else puts("-1");
		}
	}
	return 0;
}
```

---

## 作者：Gaode_Sean (赞：1)

维护两个变量 $mx,mn$，$mx$ 表示答案的上界，$mn$ 表示答案的下界。

考虑枚举 $n$ 的每一位，然后分情况讨论，我的做法只用讨论三种简单的情况。

- $n$ 的该位为 $0$，$x$ 的该位上为 $1$。此时答案无解。

- $n$ 的改位上为 $1$，$x$ 的该位上为 $0$。此时更新答案的下界。($mn$）

- $n$ 和 $x$ 该位上均为 $1$。此时更新答案的上界（$mx$）。

最后比较 $mn$ 和 $mx$ 的大小。若 $mn>mx$，则无解。否则输出 $mn$。

## [AC Code](https://codeforces.com/contest/1775/submission/188747762)

---

## 作者：honglan0301 (赞：1)

## 题意简述

给定 $n,x$, 求一个可能的 $m$, 使得 $n\And n+1\And ...\And m=x$, 或输出 $-1$。

## 题目分析

容易发现最多只有 $\log n$ 个数会影响按位与的值（每一位最多从 $1$ 变 $0$ 一次），那么我们考虑直接找出这些数，即 $n\leftarrow n+\operatorname{lowbit}(n)$, 直到按位与等于 $x$ 或 $n>5\times 10^{18}$ 为止，时间复杂度 $O(t\log n)$, 可以通过本题。

记得特判 $n=0$。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
#define lowbit(x) (x&(-x))

int t,n,x,m,nnow;

signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>x; nnow=n; int kkk=n; bool flag=0;
		if(kkk==x) {cout<<n<<endl; continue;}
		else if(n==0) {cout<<"-1"<<endl; continue;}
		while((unsigned long long)(nnow+lowbit(nnow))<=(unsigned long long)5000000000000000000)
		{
			nnow+=lowbit(nnow); kkk&=nnow;
			if(kkk==x) {cout<<nnow<<endl; flag=1; break;}
		}
		if(!flag) cout<<"-1"<<endl;
	}
}
```


---

## 作者：daiarineko (赞：0)

# 题解【CF1775C Interesting Sequence】

## 0. 题目描述

给出 $n$ 和 $x$，求出一个 $m \geq n$ 使得 $n \operatorname{and} (n+1) \operatorname{and} \dots \operatorname{and} m = x$，$\operatorname{and}$ 为按位与运算。

## 1. 思路

提供一个不那么暴力的做法。

首先观察样例，并把样例转换为二进制。

```plain
0b001010 0b001000
0b001010 0b001010
0b001010 0b101010
0b010100 0b010000

0b0110111100000101101101011001110100111011001000000000000000000
0b1000000000000000000000000000000000000000000000000000000000000
```

按位与是不可能创造出“新”位的，也就是说**如果 $n$ 中不存在这一位，$x$ 中也不能存在这一位，否则必然无解。** 参考样例 $3$。

同时，我们只有把 $n$ 中一位加“没”了，才能影响到按位与的结果。加“没”也就相当于让它进位，而进位必然是从后往前，所以必然是 $n$ 中最末尾的 $1$ 即 `lowbit(n)` 先变为 $0$。

那么**如果末尾的 $1$ 没变 $0$，而前面有 $1$ 变为 $0$ 了，就会无解。**

第三，手玩一下以下的样例：

```plain
0b1110 0b1100
```

你会发现，这也是无解的。但这并没有满足以上的无解条件啊？为什么会无解？考虑进位时，为了让最末尾的 $1$ 变成 $0$，我们只能让这一串 $1$ 都变成 $0$（`0b1110` -> `0b10000`）。

换句话说，**如果 $1$ 组成的连续段中只有一部分变成 $0$ 了，无解。**

那么，我们判断完了所有无解情况。如果没有这些情况，答案是什么呢？

以上已经提到了，这个过程相当于把 $n$ 的末位一次一次加“没”，最终变成 $x$。我们只需要判断什么时候能加没。这也就是在 $x$ 的基础上加上 `highbit(n - x) * 2`：先求出需要加“没”的最高位，再左移一位。

## 2. 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mx = 62;
int n, k;
int lowbit(int x) { return x & (-x); }
void solve()
{
    int flag = -1;
    int prea = 0, preb = 0;
    for (int i = 0; i < mx; ++i)
    {
        int a = n >> i, b = k >> i;
        a = a & 1, b = b & 1;
        if (a == 0 && b == 1)
        {
            cout << -1 << '\n';
            return;
        }
        else if (a == 1 && b == 1)
            flag = i;
        else if (flag != -1 && a == 1 && b == 0)
        {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 0; i < mx; ++i)
    {
        int a = n >> i, b = k >> i;
        a = a & 1, b = b & 1;
        if (prea == 1 && preb == 0 && a == 1 && b == 1)
        {
            cout << -1 << '\n';
            return;
        }
        prea = a, preb = b;
    }
    int ans = n - k;
    int i;
    for (i = mx; i >= 0; --i)
        if ((ans >> i) & 1ll)
            break;
    if (i < 0)
        cout << k << '\n';
    else
        cout << k + (1ll << (i + 1)) << '\n';
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        solve();
    }
    return 0;
}
```

## 3. 附注

当题目提到位运算，不妨将样例转换为二进制找找规律。

（这道题个人认为是这场 CF 最简单的一题（逃


---

