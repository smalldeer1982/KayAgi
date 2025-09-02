# Patchouli's Magical Talisman

## 题目描述

> 她擅长多种魔法，而且致力于开发新魔法。——《东方求闻史纪》

帕秋莉正在制作一个魔法护身符。她现在有 $n$ 个魔法令牌，令牌上的魔力值可以用正整数数列 $a_1,a_2,\dots,a_n$ 来表示。     
帕秋莉可以对她的魔法令牌进行如下两种操作。

- 融合：帕秋莉可以选择两块令牌并且将它们移除，并且创造出一块新的令牌，其魔力值为这两块令牌的魔力值的和。
- 降低：帕秋莉可以选择一个魔力值为一个偶数 $x$ 的令牌，将其移除，创造出一块新的令牌，其魔力值变为 $\dfrac{x}{2}$。

由于当魔力值为奇数的时候这些令牌的工作效率会达到最高，所以请你帮助帕秋莉，告诉她把这些令牌的魔力值都变成奇数，所需的最小次数是多少。

## 样例 #1

### 输入

```
4
2
1 9
3
1 1 2
3
2 4 8
3
1049600 33792 1280```

### 输出

```
0
1
3
10```

# 题解

## 作者：yinhy09 (赞：2)

第一次打夜间 CF 比赛，正赶上 Wdoi 超级良心思维场。本人 CF newbie 都差点过掉 D，差点就上绿了 qwq

话不多说，开始讲题：

## 思维讲解：

本题如果有奇数，那就只要把所有的非奇数数字加到一个奇数上面去就行啦，答案就是 $n-tot$。（$tot$ 表示有多少个奇数）

如果没有奇数，那么我们就找一个最少能够变成奇数的偶数，变成奇数 后重复第一种操作。最少次数就是 $ans=\min(\log_2{\operatorname{lowbit}({a_i})})$（$a_i$ 为偶数）。用 cmath 库算一下就行了。最终答案 $n-1+ans$。

## qwq~AC CODE：

```cpp
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _rep(i,a,b) for(int i=(a);i<(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define _per(i,a,b) for(int i=(a);i>(b);i--)
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define endl printf("\n")
ll read()
{
	char c;
	ll x=0;
	int f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
void write(ll x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
ll T,n,tot;
const int maxn=2e5+5;
ll a[maxn];
ll log(ll a)
{
	ll num=0;
	while(a!=1)a>>=1,num++;
	return num;
}
int main(){
	T=read();
	while(T--)
	{
		tot=0;
		int ans=9e18;
		n=read();
		rep(i,1,n)
		{
			a[i]=read();
			ans=min(1ll*ans,log(a[i]&(-a[i])));
			tot+=(a[i]%2);
		}
		if(tot!=0)printf("%lld\n",n-tot);
		else
		{
			printf("%lld\n",n-1+ans);
		}
	}
	return 0;
}
//Author:yinhy09,luogu user-id:575320
//Date:2022.6.3
//question ID:Codeforces1688B
```


---

## 作者：BlanketRice (赞：1)

这道题是一道贪心+数学（个人认为）好的好的，我们直接讲思路。先看题面：

有 $ n $ 个整数， $ a_1,a_2,a_3...a_n $ 求将 $ n $ 个整数全变为奇数的最少步骤。现在可以进行两种操作。

融合：删除任意两个整数，加入两数之和。

降低：将一个偶数除以 $ 2 $ 。

一、有奇数：

由于奇数加偶数的结果为偶数，所以答案为偶数的个数。

二、没奇数：

没奇数的话我们就要自己制造一个奇数。由于可以将一个整数除以 $ 2 $ ，所以我们可以找含 $ 2 $ 质因数中最少的那个数，再加上整下偶数个数即可。
   
这里我们用 $ gs $ 记录偶数个数，用 $ sign $ 记录是否有奇数，用 $ find\_two (x) $ 表示含 $ 2 $ 质因数的个数。

直接看代码：
   
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int n, a[1000005];
inline int find_two (int x){
    int cnt = 0;
    while (x % 2 == 0){
        ++ cnt;
        x /= 2;
    }
    return cnt;
}
int main(){
    cin >> T;
    while (-- T){
        cin >> n;
        bool sign = 0;
        int gs = 0,minn = 1e9;
        for (int i = 1;i <= n;++ i){
            cin >> a[i];
            if (a[i] % 2 == 0) ++ gs;
            else sign = 1;
            if (minn > find_two (a[i])) minn = find_two (a[i]);
        }
        if (sign) cout << gs << endl;
        else{
            cout << gs - 1 + minn << endl;
        }
   }
   return 0;
}
```

---

## 作者：Noby_Glds (赞：1)

### 思路：
我们可以分为两种情况：

$1$，数列中有奇数。

$2$，数列中无奇数。
#### 第一种情况：
因为我们知道，奇数加偶数等于奇数。

所以我们只需随便挑一个奇数，让它加上所有的偶数就行了。

答案为偶数的个数。
#### 第二种情况：
我们按照第一种情况的做法，搞到一个奇数。

找到 lowbit 值最小的偶数，把它化成奇数，再加上所有的偶数就行了。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200010];
int lowbit(int x){return x&-x;}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		bool p=0;
		int num=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]%2) p=1;
			else num++;
		}
		if(p) cout<<num<<endl;
		else{
			int ans=INT_MAX;
			for(int i=1;i<=n;i++) ans=min(ans,(int)log2(lowbit(a[i])));
			cout<<ans+num-1<<endl;
		}
	}
	return 0;
} 
```


---

## 作者：Southern_Dynasty (赞：0)

分两种情况讨论。

这里我们令奇数的个数为 $x$，偶数的个数为 $y$（很显然其中一方等于 $n$ 减去另一方）。

如果这些数字当中有奇数，那么只需要将所有的偶数和其中一个奇数合并就行了，一共需要 $y$ 次操作。

如果没有奇数，就需要自己除二弄出一个奇数。很显然也是要选择变为奇数代价最小的偶数，打擂台即可。答案是最小代价加上**现有**偶数的个数。

至于代价怎么求，就是 $\text{log2(lowbit(x))}$。

注意要强制类型转换成 `int` ！！

代码：

```cpp
#include<bits/stdc++.h>
#define gt getchar
#define pt putchar
#define y1 y233
//#define int long long
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
const int N=2e5+5;
using namespace std;
#define endl "\n"
#define lowbit(x) x&-x
struct FastIO{
	static const int SIZE=1<<14;
	inline char gc(){
		static char buf[SIZE],*begin=buf,*end=buf;
		return begin==end&&(end=(begin=buf)+fread(buf,1,SIZE,stdin),begin==end)?EOF:*begin++;
	}
	inline int read(){
    	int x=0,f=1;char ch=gt();
    	while(!isdigit(ch)){if(ch=='-')f=-1;ch=gt();}
    	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gt();}
		return x*f;
	}
	inline void print(int x){
    	if(x<0)pt('-'),x=-x;
    	if(x>9)print(x/10);
    	pt(x%10+48);
	}
	inline void println(int x){
		print(x);
		pt('\n');
	}
}io;
#define read io.read
#define print io.print
#define println io.println
#define gc io.gc
int T,n,a[N];
signed main(){
	T=read();
	while(T--){
		n=read();
		int cnt=0;
		for(int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]&1)cnt++;
		}
		if(cnt){println(n-cnt);continue;}
		int sum=2147483647;
		for(int i=1;i<=n;++i){
			if(a[i]&1)continue;
			sum=min(sum,(int)log2(lowbit(a[i])));
		}
		println(sum+n-cnt-1);
	}
	return 0;
}
```


---

## 作者：SUNCHAOYI (赞：0)

对于一个奇数，不需要进行操作；对于一个偶数，只要有奇数存在，显然直接与奇数合并最优。因此，若序列中存在奇数，则由奇数+偶数=奇数的性质，可以将所有的偶数与其合并；若不存在奇数，则找到处理最少次数后能变为奇数的偶数，进行操作，然后将剩余的偶数与其合并。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,mx,cnt,a[MAX];
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();cnt = 0;mx = INF;
		for (int i = 1;i <= n;++i) a[i] = read ();
		for (int i = 1;i <= n;++i) 
			if (a[i] & 1) ++cnt;
		for (int i = 1;i <= n;++i)
		{
			if (a[i] & 1) continue;
			int p = 0;
			while (a[i] % 2 == 0)
			{
				a[i] /= 2;
				++p;
			}
			mx = min (mx,p);
		}
		if (cnt == n) printf ("0\n");
		else if (!cnt) printf ("%d\n",n - 1 + mx);
		else printf ("%d\n",n - cnt);
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：Daniel2020 (赞：0)

### 题目大意：

多组数据。每组数据有 $n$ 个正整数，可以执行两种操作：

1.	将两个数 $x$ 和 $y$ 合并为 $x+y$

2.	将一个偶数 $x$ 变为 $x/2$

求使所有数均为奇数的最少操作数。

### 解题思路：

奇数有一个优美的性质：

```
偶数与奇数的和为奇数。
```

利用这个性质，我们可以进行分类讨论：

1.	原数列中有奇数：

易证明将偶数与奇数合并时，处理这个偶数的花费不劣。（建议各位神犇自己证明）

最小操作数则为原数列中的偶数个数。

2.	原数列中无奇数：

考虑使一个偶数变为奇数。

选择原数列中偶素因数最少的数，对其进行操作变为奇数，再将其它数与此数合并即可。

### AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL t,n,x,odd,eve;
LL getsqt(LL x)
{
	LL cnt = 0;
	for(;!(x&1);x >>= 1) cnt++;
	return cnt;
} /*处理偶数*/
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		odd = 0; /*奇数个数*/ eve = 114514; /*偶数最少处理次数*/
		scanf("%lld",&n);
		for(int i = 1;i <= n;i++)
		{
			scanf("%lld",&x);
			x&1 ? odd++ : eve = min(eve,getsqt(x));
		}
		printf("%lld\n",odd ? n-odd : eve+n-1); /*分类讨论*/ 
	}
	return 0;
}
```


---

## 作者：linyuhuai (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/1688/B) & [前往 blog 获得更好的阅读体验](https://by505244.github.io/oi_blogs/2022/06/05/CF1688B%E9%A2%98%E8%A7%A3/)

如果给出的数组中有一个奇数，那么将其与其他的偶数相加得到奇数。不难发现相加一定是比对偶数除二更好的解决方案。

如果没有一个奇数，那么将数组中 $\text{lowbit}$ 最小的数化为奇数，再执行上面操作。



```cpp
#include<bits/stdc++.h>
#define INF 0x7fffffff
#define DEBUG puts("I AK IOI");
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a>b?b:a;}
int a[200005];
int find(int x){
    for(int i=0;i<=31;i++){
        int a=x>>i;
        if(a&1){
            return i;
        }
    }
}
void solve(){
    int n;
    scanf("%d",&n);
    int even=INF,odd=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i]&1)odd++;
        else even=min(even,find(a[i]));
    }
    if(odd>=1)printf("%d\n",n-odd);
    else printf("%d\n",even+n-1);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}
```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1688B)（资瓷 WdOI 的良心比赛）

翻译已经有了。

经过一番研究，我们发现只要有奇数，那么我们就可以用最少的次数把偶数都给合并掉，次数为偶数的个数。

那没有奇数呢？我们就找变成奇数需要的操作次数最少的偶数，然后再加上 $n-1$ 即可。

至于如何找出最少的操作次数，我们发现在每次我们将一个数除以 2 的时候他的二进制末尾会少一个 0。那么，一个数二进制末尾 0 的个数就是一个偶数变成奇数需要除以多少次 2。

我们需要用到一个叫做 $\text{lowbit}$ 的好东西，可以算出 $x$ 二进制里最右边的是 1 的一位，计算方法是 `lowbit(x)=x&(-x)`。

举个例子：

```
lowbit(1)=1(二进制:*1*)
lowbit(2)=2(二进制:*10*)
lowbit(3)=1(二进制:1*1*)
lowbit(4)=4(二进制:*100*)
lowbit(5)=1(二进制:10*1*)
lowbit(6)=2(二进制:1*10*)
lowbit(7)=1(二进制:11*1*)
lowbit(8)=8(二进制:*1000*)
```

那么，我们只需要先算出 $\text{lowbit}$ 再用 cmath 的 $\log2$ 函数就可以算出一个偶数所需的操作次数。

综合代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main(){
	int T,n;int ji,ans;
	cin>>T;
	while(T--){
		cin>>n;
		ji=0,ans=0x3f3f3f3f;//ji表示奇数个数,ans是算最小次数
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]&1) ji++;
			else ans=min(int(log2(a[i]&(-a[i]))),ans);
			//(a[i]&(-a[i]))是lowbit，
		}
		if(ji) cout<<n-ji<<endl;
		else cout<<ans+n-1<<endl;
	}
	return 0;
}
```

---

## 作者：_Andy_Lin_ (赞：0)

问题可以分类：有奇数与没有奇数。

首先想有奇数的：显然，每步至多消耗一个偶数，那么将偶数与奇数合并一定最优。

然后没有奇数：我们可以想到，首先通过第一种操作，将一个数变成奇数，变成有奇数的情况，直接处理即可。

至于将哪个数变为奇数，找出变为奇数时操作次数最少的

如果没懂，请结合代码食用：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200001
int T,n,a[N],mn,od;
int gt(int x){//求操作次数（奇数为0次）
	int num=0;
	while(!(x&1)){++num;x>>=1;}
	return num;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);mn=INT_MAX;od=0;
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);if(a[i]&1)++od;mn=min(mn,gt(a[i]));
		}
		if(od)printf("%d\n",n-od);
		else printf("%d\n",mn+n-1);
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

如果存在一个奇数，那么全部执行加操作，操作次数是 $n-1$。

否则，需要找到一个变成奇数使用的除以 $2$ 的次数最小的数，设这个数变成奇数除以 $2$ 的次数为 $x$，那么答案就是 $x + n - 1$。

```python
def solve():
    n = int(input())
    _ = input().split()
    a = []
    for i in range(0, n):
        a.append(int(_[i]))
    flag = False
    for i in range(0, n):
        if (a[i] & 1):
            flag = True
            break
    if (flag):
        cnt = 0
        for i in range(0, n):
            if (a[i] % 2 == 0):
                cnt += 1
        print(cnt)
    else:
        mi = 0x3f3f3f3f
        for i in range(0, n):
            j = a[i]
            cnt = 0
            while (j % 2 == 0):
                j //= 2
                cnt += 1
            mi = min(mi, cnt)
        print(mi + n - 1)

t = int(input())
for i in range(0, t): solve()

```


---

