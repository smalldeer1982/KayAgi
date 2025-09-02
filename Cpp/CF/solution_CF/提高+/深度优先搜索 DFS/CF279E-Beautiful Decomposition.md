# Beautiful Decomposition

## 题目描述

给定一个长度不超过 $10^6$
  的二进制数 $s$，求至少要用几个 $2^k$ 和 $-2^k(k\ge0)$ 加起来值等于 $n$。

## 样例 #1

### 输入

```
10
```

### 输出

```
1
```

## 样例 #2

### 输入

```
111
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1101101
```

### 输出

```
4
```

# 题解

## 作者：quanjun (赞：3)


题目链接：[http://codeforces.com/problemset/problem/279/E](http://codeforces.com/problemset/problem/279/E)

### 题目大意

给定一个 $n$ 位二进制数，你需要将其表示成若干个二的幂（$2^k(k \ge 0)$）相加或相减的结果。

问：最少需要几个二的幂？

### 解题思路

首先不难观察每个二的幂最多使用一次（因为对于某个 $2^k$，如果加两次或者减两次等价于加或减一次 $2^{k+1}$，加一次并减一次相当于没操作）。  

然后我们来看二进制数的最高位，假设最高位对应的是 $2^k$。因为 $2^0 + 2^1 + \ldots 2^{k-1} \lt 2^k$，所以要想拥有 $2^k$，我们必须选择加上某个 $2^x$，其中 $x \ge k$。  
可以发现加上 $2^{k+2}$ 是不可能的，因为这样我们必须减去一个 $2^{k+1}$ —— 而 $2^{k+2} - 2^{k+1}$ 可以用 $2^{k+1}$ 代替。$\Rightarrow$ 所以此时只能选择 $2^k$ 或者 $2^{k+1}$。

- 如果我们选择加上 $2^k$，则我们面临的是是剩余的那些位；
- 如果我们选择加上 $2^{k+1}$，则我们面临的是 $m = 2^{k+1} - n$（其中 $n$ 是当前的数值，因为加上了 $2^{k+1}$，所以剩余的 $m = 2^{k+1} - n$ 就是应该减去的了，因为因为仅仅变换了一下正负号，$m$ 对应的次数是不会有变化的）—— 这里我们将 $m$ 称作 $n$ 的补码（注意：$k$ 的值是不需要定义的，因为 $k$ 就是 $n$ 的二进制表示中的最高位）

然后我们来看状态 $m$，我们需要翻转 $n$ 的所有二进制位（$1$ 变成 $0$；同时 $0$ 变成 $1$），并且结果的次数加 $1$（因为选择加上了 $2^{k+1}$）。可以发现一个很神奇的事情（**这里是我觉得很神奇的地方**，虽然说出来好像有点像废话，但是这句话最重要，能够优化很多问题，很神奇，那就是）：对于原始的 $n$ 来说，若它的补码是 $m$，则 $n$ 的任意长度的后缀和 $m$ 的同样长度的后缀之间也是补码关系。（所以一开始把 $m$ 求出来即可）  

所以在我们正式的处理过程中我们只需要处理 $n$，$m$ 以及他俩对应的所有后缀。据此得到一个dp解法：  

定义 $v[1] = n, v[2] = m$，则状态 $dp[ind][suf]$ 表示构造 $v[ind]$（其中 $1 \le ind \le 2$）的从下标 $suf$ 开始的数所需的最少操作次数。我们可以从 $dp[\ldots][n]$ 开始计算，得到答案为 $dp[1][1]$。

_具体实现时状态略有调整（我的下标从小到大来的）_

示例程序：  
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;

char s[maxn];
int n, dp[2][maxn];

int main() {
    scanf("%s", s+1);
    n = strlen(s+1);
    dp[0][1] = (s[1] == '1');
    dp[1][1] = 1;   // 一开始 2^{k+1} 边反码至少要一次
    for (int i = 2; i <= n; i++) {
        if (s[i] == '0') {
            dp[0][i] = dp[0][i-1];
            dp[1][i] = min(dp[1][i-1], dp[0][i-1]) + 1;
        }
        else {  // s[i] == '1'
            dp[1][i] = dp[1][i-1];
            dp[0][i] = min(dp[1][i-1], dp[0][i-1]) + 1;
        }
    }
    printf("%d\n", dp[0][n]);
    return 0;
}
```


---

## 作者：zsyyyy (赞：2)

# CF279E 1900 贪心

## 题意

给定一个长度不超过 $10^6$ 的二进制数 $n$，求至少要用几个 $2^k$ 或 $−$ $2^k$ $(k≤0)$ 加起来值和 $n$ 相等。

## 思路

**结论：**

如果是一个 $0$ 后面接很多个 $1$，那么答案 $+1$；（情况一）

如果是很多个 $0$ 后面接很多个 $1$，那么答案 $+2$。（情况二）

特别的，如果是一个单独的 $1$，那么答案 $+1$，并忽略这个 $1$。



**感性证明：**

情况一：$110111$ 是 $1000000-10000-1$

情况二：$1100111$ 是 $10000000-100000+10000-1$

实际上是因为隔了一个 $0$ 时可以借上一次的 $1$。



可以特判一下开头的两个数，两个数之后的 $1$ 都可以忽略了。


时间复杂度：$O(n)$


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6+10;
char a[MAXN];
int n,ans;
bool tflag,flag;
signed main()
{
	scanf("%s",(a+1));
	n=strlen(a+1);
	if(a[1]==a[2]&&a[1]=='1') //特判开头的数
	{
		ans=2;
		flag=1;
	}
	else  ans=1;
	for(int i=1;i<=n;i++)
	{
		if(!tflag&&a[i]=='1')  continue; 
        //因为特判了开头，所以之后连着的1都可以忽略
		tflag=1;
		if(a[i-1]=='0'&&a[i-2]=='0')  flag=0;
		if(a[i]=='1'&&a[i-1]=='0')
		{
			if(a[i+1]!='1')
			{
				ans++;
				i++;
			}
			else //与上一个连着的一串1隔了一个0
			{
				if(a[i-1]=='0'&&a[i-2]=='1'&&flag)  ans++;
				else
				{
					flag=1;
					ans+=2;
				}
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：hongshixiaobai (赞：0)

# CF279E Beautiful Decomposition 题解
[传送门](https://www.luogu.com.cn/problem/CF279E)
## 思路
对于连续的一段 $1$，只需至多两个数就能凑出来（开头前一位放一个 $2^i$，结尾位放一个 $-2^i$），如果和上一段连续的 $1$ 之间只有一个 $0$，那就只需要一个数就够了（把上一段结尾位的 $-2^i$ 移到当前端的结尾位，然后减掉中间 $0$ 的那位），如果有单独的一个 $1$，显然只需一个数，但是会打断前面的传递，所以后一段无论如何都需要两个数（除非也是单独的一个 $1$）。
### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000006],pre[1000006],nv,l,r,ans,lst,add,flag,cnt;
string c;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>c;
	int n=c.size();
	for(int i=1;i<=n;i++)a[i]=c[i-1]-'0',cnt+=a[i];
	int ans=0;
	nv = 0,add = 2;
	for(int i=1;i<=n+1;i++)
	{
		if(a[i]!=nv)
		{
			if(a[i])
			{
				if(a[i+1]!=a[i]&&add == 2)ans++,add = 1,l = r = i,nv = 0;
				else ans+=add,l = r = i,nv = a[i];
			}
			if(!a[i])add = 1,l = r = i,nv = a[i];
		}
		else
		{
			if(!a[i])add = 2;
			r = i;
		}
	}
	if(!ans)ans = 1+(n>1);
	cout<<ans;
	return 0;
}
```

---

## 作者：L_zaa_L (赞：0)

挺好的 DP，但是做了半天才做了出来。

## 分析
我们首先可以考虑的是，每个 $2^k$ 只会用一次。因为用了两次要么被抵消，要么可以用 $2^{k+1}$ 来代替。

所以我们可以从高位到低位进行 DP，就是我们发现，能影响决定这一位填一的只有比这位更高位的位置，如果当前这一位 $x$ 需要有一，我们只能从 $2^x$ 和 $2^{x+1}$ 进行转移，因为 $2^{x-1}$ 不能影响前面的，然后 $2^{x+2}$ 次方由于前面的我们之前填过了，所以要至少要减去一个 $2^{x+1}$ 没有直接填 $2^{x+1}$ 划算。

所以我们如果填了 $2^x$ 的话，直接往低位继续 DP 就可以了，但如果填了 $2^{x+1}$，我们就相当于要减去 $2^{x+1}-m$（$m$ 为当前剩下的），于是我们就可以用 $dp_{i,0/1}$ 来表示填到了第几位然后是需要减去还是加上，最开始预处理 $2^{|s|}-s$ 就可以了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e6+5,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
//typedef __int128_t i128;
//i128 _base=1;
//inline int mol(int x){return x-Mod*(_base*x>>64);}
//inline void Add(int &x,int y){x=mol(x+y+Mod);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int n;
char s[N],t[N];
int dp[N][2];
inline void solve(){
	scanf("%s",s+1);n=strlen(s+1);
	For(i,1,n) t[i]=(s[i]=='1'?'0':'1');
	Rof(i,n,1){
		if(t[i]=='1') t[i]='0';
		else{
			t[i]='1';
			break;
		}
	}
	dp[1][0]=(s[1]=='1');
	dp[1][1]=(s[1]=='1');
	For(i,2,n){
		if(s[i]=='0')dp[i][0]=dp[i-1][0];
		if(t[i]=='0')dp[i][1]=dp[i-1][1];
		if(s[i]=='1')dp[i][0]=min(dp[i-1][0],dp[i-1][1])+1;
		if(t[i]=='1')dp[i][1]=min(dp[i-1][0],dp[i-1][1])+1;
	}printf("%lld\n",dp[n][0]);
}
signed main(){
	//_base=(_base<<64)/Mod;
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	int T=1;
	while(T--){solve();}
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

