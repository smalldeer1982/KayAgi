# [SNCPC2019] Coolbits

## 题目描述

给定 $n$ 个区间 $[l_1, r_1], [l_2, r_2], \dots, [l_n, r_n]$，需要从每个区间中选择一个整数并计算它们的按位与值 $b$。能够得到的最大 $b$ 是多少？

## 样例 #1

### 输入

```
2
3
0 8
2 6
3 9
1
1 100
```

### 输出

```
6
100
```

# 题解

## 作者：Flaw_Owl (赞：2)

# P9649 [SNCPC2019] Coolbits 题解

题目链接：[P9649 [SNCPC2019] Coolbits](https://www.luogu.com.cn/problem/P9649)

## 题目摘要

二进制运算 + 贪心思想：第 $i$ 位置 $1$ 的贡献要比之后每一位都置 $1$ 要大。

## 题目分析

乍一看感觉是和 [P9612 [CERC2019] Light Emitting Hindenburg](https://www.luogu.com.cn/problem/P9612) 有点类似的题。都是**使得若干个数最后的按位与之和最大**，不同的是本题是给定一些区间，在区间里选数；而 P9612 则是直接给定了一些数。因此本题要稍微难一些。

如果你已经做过 P9612，你就会知道这道题的大致思想是贪心。如果我们枚举最后结果的每一位，我们会发现 `10000` 要比 `01111` 要大，即 $1$ 的数量贵精不贵多，如果高位上能置 $1$，那么这个数是必要选的。

然而现在的问题是，现在不是从 $n$ 个数选择的问题，而是从 $n$ 个区间中取一个数。——但这也没有关系，我们按照同样的思路进行分析，仍然是类似于枚举答案的思想。如果第 $i$ 位能置 $1$，就说明选择出的这 $n$ 个数的这一位都是 $1$。如果不可能，说明这一位不可能是 $1$ 了，跳过这一位；如果可以，那么区间就会被缩小，变成从最小的该位为 $1$ 的数到右端点。

具体来说，即为：

```cpp
int cal(int x, int i)
{
    if (!((x >> i) & 1))
        x = ((x >> i) | 1) << i;
    return x;
}
```

这个函数计算了对于每一个区间的左端点，如果它的第 $i$ 位为 $1$，那么区间不用改变，否则变为除了那一位为 $1$ 之外，其它位都为 $0$ 的数，即新的左端点。改变之后我们还要判断一下它会不会超过右端点（即新的区间能不能存在）。

## 一些细节

- 数据范围是 $0 \leq x \leq 10^9$，大概是 `int` 类型，即 $2^{31} - 1$。我们枚举答案的位数的时候就要从 $30$ 枚举到 $0$。
- 位运算的优先级比较容易出错，注意多加括号。

## 参考代码

```cpp
#include <iostream>
#include <cctype>
#define ll long long

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 1e5 + 5;

int T;
int n;
ll ans;
int L[maxN], R[maxN];

int cal(int x, int i)
{
    if (!((x >> i) & 1))
        x = ((x >> i) | 1) << i;
    return x;
}

int main()
{
    T = read();
    while (T--)
    {
        ans = 0;
        n = read();
        for (int i = 1; i <= n; i++)
            L[i] = read(), R[i] = read();
        for (int i = 30; i >= 0; i--)
        {
            ll d = 1ll << i;
            bool flag = false;
            for (int j = 1; j <= n; j++)
                if (cal(L[j], i) > R[j])
                {
                    flag = true;
                    break;
                }
            if (flag)
                continue;
            for (int j = 1; j <= n; j++)
                L[j] = cal(L[j], i);
            ans |= d;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Shunpower (赞：2)

注意到若答案二进制高位是 $1$，无论低位如何都不可能比目前答案更优，所以考虑从高位到低位枚举每一位，尽量使目前枚举到的这一位是 $1$。

设目前枚举到了表示 $2^i$ 的这一位，要想让这一位是 $1$，需要每个区间中都存在一个数满足 $2^i$ 位是 $1$。于是考虑找出 $\geqslant l$ 的最小的一个 $2^i$ 位是 $1$ 的数 $x$，然后判断它是否 $\leqslant r$。

如果 $l$ 的 $2^i$ 位是 $1$，那么这个数就是 $l$，否则就将 $l$ 的 $2^i$ 这一位变 $1$，然后把比 $2^i$ 低的位全部推成 $0$ 得到这个数。

若对于每个区间都存在 $x$，那么答案的 $2^i$ 位是 $1$，并且要把每个区间的 $l\gets x$，因为在后面的选择中也需要保证这一位是 $1$，才能不影响高位。

下面是核心代码：

```cpp
int upperbound(int x,int i){
    if(!((x>>i)&1)){
        x=((x>>i)|1)<<i;
    }
    return x;
}
void solve(){
    ans=0;
    cin>>n;
    fr1(i,1,n){
        cin>>l[i]>>r[i];
    }
    fr2(i,31,0){
        int d=(1ll<<i);
        bool flg=0;
        fr1(j,1,n){
            if(upperbound(l[j],i)>r[j]){
                flg=1;
            }
        }
        if(flg){
            continue;
        }
        fr1(j,1,n){
            l[j]=upperbound(l[j],i);
        }
        ans|=d;
    }
    cout<<ans<<endl;
}
```


---

## 作者：yr409892525 (赞：1)

## 题解 [P9649 [SNCPC2019] Coolbits](https://www.luogu.com.cn/problem/P9649)
如果我们直接枚举最后的答案，肯定会超时。      
我们发现如果想让答案最大，就要让最高位变为 $1$。           
不妨枚举每一位，判断这一位是都可以为 $1$。          
问题就是如何判断，我们需要求出一个大于 $r$，第 $i$ 位为 $1$ 的最小值。         
所以我们只需要把第 $i$ 为变为 $1$，后面的变为 $0$。            
前提是第 $i$ 位不为 $1$。                 
给出代码：       

```cpp
int x=l[i];
if(((x>>j)&1)==0){
   x=(((x>>j)|1)<<j);
}
```
其中 $i$ 为第 $i$ 号区间，$j$ 为第 $j$ 位。             
直接枚举 $30 \sim 0$ 位，设 $1$ 是第 $0$ 位。          
记得要从大到小。          
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int t; 
int n;
int l[N],r[N];
int check(int i,int j){
	int x=l[i];
	if(((l[i]>>j)&1)==0){
		x=(((l[i]>>j)|1)<<j);
	}
	return x;
}
void work(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>l[i]>>r[i];
	}
	int ans=0;
	for(int i=30;i>=0;i--){
		bool f=1;
		for(int j=1;j<=n;j++){
			if(check(j,i)>r[j]){
				f=0;
			}
		}
		if(f){
			ans+=(1ll<<i);
			for(int j=1;j<=n;j++){
				l[j]=check(j,i);
			}
		}
	}
	cout<<ans<<"\n";
	return ;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		work();
	}
	return 0;
}
```

---

## 作者：SDLTF_凌亭风 (赞：1)

来自某位不愿意透露姓名的队友。

---
很明显按位贪心成立。

如果这一位能够选 $1$ 那么直接选 $1$，然后把这个区间缩小。如果选不了 $1$ 的话，那么不一定所有区间一定都选 $0$，需要逐个区间去考虑。

对于可以任选的区间，这个区间肯定包含了 $\cdots 0111\cdots 1$ 和 $\cdots 1000\cdots 0$ 这两个二进制数。对于这两个二进制数来说很明显选前者不会拖最终答案的后腿。同时很容易证明选 $\cdots 0111\cdots 1$ 必然是最优的。（虽然 $\cdots 1111\cdots 1$ 也是同样优的，但是前者必然能选到）

然后从最高位做到最低位就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e5+51;
ll test,n,d,res,flg,lx,rx;
ll l[MAXN],r[MAXN],cur[MAXN];
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline ll calc(ll x)
{
	ll res=0;
	while(x)
	{
		x>>=1,res++;
	}
	return res;
}
inline void solve()
{
	n=read(),d=res=0;
	for(register int i=1;i<=n;i++)
	{
		l[i]=read(),r[i]=read(),cur[i]=0,d=max(d,calc(r[i]));
	}
	for(register int i=d;i>=0;i--)
	{
		flg=1;
		for(register int j=1;j<=n;j++)
		{
			lx=cur[j]+(1<<i),rx=lx+(1<<i)-1;
			if(rx<l[j]||lx>r[j])
			{
				flg=0;
				break;
			}
		}
		if(flg)
		{
			res|=(1<<i);
			for(register int j=1;j<=n;j++)
			{
				cur[j]|=(1<<i);
			}
			continue;
		}
		for(register int j=1;j<=n;j++)
		{
			lx=cur[j]+(1<<i),rx=lx+(1<<i)-1;
			if(lx<=r[j]&&rx>=l[j])
			{
				l[j]>lx-1?cur[j]|=(1<<i):1;	
			}
		}
	}
	printf("%d\n",res);
}
int main()
{
	test=read();
	for(register int i=1;i<=test;i++)
	{
		solve();
	}
}
```


---

## 作者：_yang_yi_bo_ (赞：0)

枚举 $i$ 并使在 $[l_i,r_i]$ 中找到二进制从后往前的第 $i$ 位为 $1$，尝试缩小范围，满足找到 $\ge l_j$ 且满足二进制从后往前的第 $i$ 位为 $1$ 的 ${l_j}^{\prime}$。

若对于所有 $j \in [1,n]$，满足 ${l_j}^{\prime} \le r_j$，则在区间选数后相与可以使得第 $i$ 位为 $1$，答案加 $2^{i-1}$，所有 $l_j$ 缩小范围变成 ${l_j}^{\prime}$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,maxi;
int x[100005],y[100005];
int bitt(int x,int i){
	if(((x>>i)&1)==0){
		x>>=i;
		x|=1;
		x<<=i;
	}return x;
}
void k(){
	int ans=0;
	for(int i=30;i>=0;i--){
		bool f=true;
		for(int j=1;j<=n;j++){
			if(bitt(x[j],i)>y[j]){
				f=false;
				break;
			}
		}if(f){
			for(int j=1;j<=n;j++){
				x[j]=bitt(x[j],i);
			}ans+=(1ll<<i);
		}
	}cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x[i]>>y[i];
		}k();
	}
	return 0;
} 
```

---

## 作者：sieve (赞：0)

# 题解：[P9649 [SNCPC2019] Coolbits](https://www.luogu.com.cn/problem/P9649)

## 思路

对于这题，我们需要知道：$a$ 按位与 $b$ 一定小于等于 $\min(a,b)$。

那么，我们就要使得选的最高位尽可能的大，就是让 $1$ 出现在尽可能高的位置。

所以，我们就枚举二进制下的每一位。

如果枚举的这一位是 $0$，把它变成 $1$，后面的全部设为 $0$。看是不是小于等于 $r_i$，就是没有越界。如果没有，这个区间的左端点就可以缩小为这个新的二进制转换为十进制的结果。

然后答案的这一位设为 $1$，最后的答案就是这个二进制的结果。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,ans;
int l[N],r[N];
int bit(int x,int i)
{
	if(((x>>i)&1)==0)
	{
		x=(x>>i)|1;
		x<<=i;
	}
	return x;
}
void solve()
{
	ans=0;
	cin>>n;
	for(int i=1;i<=n;++i) cin>>l[i]>>r[i];
	for(int i=30;i>=0;--i)
	{
		bool f=1;
		for(int j=1;j<=n;++j)
		{
			if(bit(l[j],i)>r[j])
			{
				f=0;
			}
		}
		if(!f) continue;
		for(int j=1;j<=n;++j)
		{
			l[j]=bit(l[j],i);
		}
		ans+=(1ll<<i);
	}
	cout<<ans<<endl;
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：MerlinLee (赞：0)

从大到小考虑每一位是否能填 1 进去，同时构造出每个区间选的数是什么。

设 $now_i$ 表示第 i 个区间在满足之前贪心的条件下，目前选的数是什么，现在考虑到第 k 位了，假设第 k 位是1 的话，那么 $now_i$ 会变成 $now_i|2^k$ 这个形式，之后能表达的数在区间 $[now_i+2^k,now_i+2^{k+1}-1]$ 这个范围内，如果这个区间和 $[l_i,r_i]$ 有交集，则说明第 i 个区间在满足前面位的情况下第 k 为可以是 1 这个情况，若所有区间第 k 位都可以是 1 的话，那么所有的 $now_i|2^k$ 的情况，都要考虑 $now_i$ 的第 k 位是不是 1 这个情况。

若本就不可为 1 的话自不必说，但是如果 $now_i$ 的第 k 位可以是 1 或者也可以不是 1 的话，我们可以考虑设之前说的区间为 $[nl,nr]$ 这个范围，现在我们其实并不关心第 k 位如何，是不是 1 都可以，只要能让我们在考虑之后的某位能为 1 的时候尽可能满足条件就行。

此时需要注意到，考虑 $nl-1$ 的二进制是什么样子的，应该是 $nl-1=now_i+2^k-1$ 这样的情况，也就是说，对于 $nl-1$ 的第 0 位到第 $k-1$ 位都是 1 的话，并且我们的区间 $[l_i,r_i]$ 包含了 $nl-1$ 这个情况，那么第 k 位就不需要变为 1 这个数字，否则就必须变成 1 这个数字。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e5+10;
int T,n;
int l[Maxn],r[Maxn],now[Maxn];
int read()
{
	int x=0,f=1;
    char ch=getchar();
    while(ch<'0' or ch>'9')
    {
        if(ch=='-')
          f=-1;
        ch=getchar();
    }
    while(ch>='0' and ch<='9')
      x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)
		  l[i]=read(),r[i]=read(),now[i]=0;
		int ans=0;
		for(int i=29;i>=0;i--)
		{
			bool flag=true;
			for(int j=1;j<=n and flag;j++)
			{
				int nl=now[j]|(1<<i),nr=now[j]|((2<<i)-1);
				if(nl>r[j] or nr<l[j])
				  flag=false;
			}
			if(flag)
			{
				for(int j=1;j<=n;j++)
				  now[j]|=1<<i;
				ans|=1<<i;
			}
			else
			{
				for(int j=1;j<=n;j++)
				{
					int nl=now[j]|(1<<i),nr=now[j]|((2<<i)-1);
					if(nl<=r[j] and nr>=l[j] and nl-1<=l[j])
					  now[j]|=1<<i;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

