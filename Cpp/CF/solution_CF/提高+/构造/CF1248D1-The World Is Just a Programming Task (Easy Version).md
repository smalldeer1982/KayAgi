# The World Is Just a Programming Task (Easy Version)

## 题目描述

This is an easier version of the problem. In this version, $ n \le 500 $ .

Vasya is an experienced developer of programming competitions' problems. As all great minds at some time, Vasya faced a creative crisis. To improve the situation, Petya gifted him a string consisting of opening and closing brackets only. Petya believes, that the beauty of the bracket string is a number of its cyclical shifts, which form a correct bracket sequence.

To digress from his problems, Vasya decided to select two positions of the string (not necessarily distinct) and swap characters located at this positions with each other. Vasya will apply this operation exactly once. He is curious what is the maximum possible beauty he can achieve this way. Please help him.

We remind that bracket sequence $ s $ is called correct if:

- $ s $ is empty;
- $ s $ is equal to "( $ t $ )", where $ t $ is correct bracket sequence;
- $ s $ is equal to $ t_1 t_2 $ , i.e. concatenation of $ t_1 $ and $ t_2 $ , where $ t_1 $ and $ t_2 $ are correct bracket sequences.

For example, "(()())", "()" are correct, while ")(" and "())" are not.

The cyclical shift of the string $ s $ of length $ n $ by $ k $ ( $ 0 \leq k < n $ ) is a string formed by a concatenation of the last $ k $ symbols of the string $ s $ with the first $ n - k $ symbols of string $ s $ . For example, the cyclical shift of string "(())()" by $ 2 $ equals "()(())".

Cyclical shifts $ i $ and $ j $ are considered different, if $ i \ne j $ .

## 说明/提示

In the first example, we can swap $ 7 $ -th and $ 8 $ -th character, obtaining a string "()()()()()". The cyclical shifts by $ 0, 2, 4, 6, 8 $ of this string form a correct bracket sequence.

In the second example, after swapping $ 5 $ -th and $ 10 $ -th character, we obtain a string ")(())()()(()". The cyclical shifts by $ 11, 7, 5, 3 $ of this string form a correct bracket sequence.

In the third example, swap of any two brackets results in $ 0 $ cyclical shifts being correct bracket sequences.

## 样例 #1

### 输入

```
10
()()())(()
```

### 输出

```
5
8 7
```

## 样例 #2

### 输入

```
12
)(()(()())()
```

### 输出

```
4
5 10
```

## 样例 #3

### 输入

```
6
)))(()
```

### 输出

```
0
1 1
```

# 题解

## 作者：big_news (赞：2)

n 很小，显然可以枚举方案。

剩下的问题是怎么找“循环匹配”个数。

设'('代表 1 ，')'代表 -1 ，于是我们得到一串数列。有一个结论是说“循环匹配”个数恰好等于这个数列的前缀和最小值的**数量**。

这个东西可以这么理解：

假设对于序列`)()(`，它的前缀和是`-1 0 -1 0`

当上述前缀值<0时，这个前缀序列一定是不合法的。然后考虑什么时候把括号序列的一段前缀移到后面去是合法的。

首先你需要使得移动之后，前面的括号序列合法。也就是说你得把一段“连续的极长非合法前缀”找出来（对于样例是`)`）。这个东西恰好在前缀和第一次取得最小值时取得（前缀和取`-1`）。然后实际上你还可以在这个前缀后面接上一些“本身合法”的括号序列，像这样：`)()`。后面那个合法的序列对答案没有影响，因此循环移位的数量就是前缀和最小值的数量。

然后就做完了。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

const int CN = 550;

int abs(int x) {return x > 0 ? x : -x;}

int n; char ch[CN];

int ans = 0,ansi = 1,ansj = 1;
int GetAns(){
    int cnt = 0,sum = 0,mn = 0;
    for(int i=0;i<n;i++){
        if(ch[i] == '(') cnt++;
            else cnt--;
        mn = min(mn, cnt);
    }
    for(int i=0;i<n;i++){
        if(ch[i] == '(') cnt++;
            else cnt--;
        if(cnt == mn) sum++;
    }
    return sum;
}
bool checker(){
    int a = 0,b = 0;
    for(int i=0;i<n;i++) if(ch[i] == '(') a++; else b++;
    return a == b;
}

int main()
{
    scanf("%d",&n); cin>>ch;
    
    if(!checker()) printf("0\n1 1");
    else{
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                swap(ch[i],ch[j]);
                if(GetAns() > ans) {ans = GetAns(); ansi = i+1; ansj = j+1;}
                swap(ch[j],ch[i]);
            }        
        printf("%d\n%d %d",ans,ansi,ansj);
    }
    
    return 0;
}
```

---

## 作者：123zbk (赞：1)

首先 $n\le500$，所以先用 $n^2$ 暴力交换，再用 $O(n)$ 计算答案。

括号序想到将左括号看成 $1$，右括号看成 $-1$，求一下前缀和。现在考虑将哪些位置移到最后可以变成合法序列。（合法序列的前缀和应是处处大于等于 $0$ 的）

容易想到就是当且仅当在前缀和最小时，将所有前面的移到后面时合法的。移完后的序列一定保证和都为正，反之一定会出现负数。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=505;
int n,mx,ls,rs,sum[maxn],num;
char s[maxn];
int query()
{
    int mn=0x3f3f3f3f,res=0;
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='(')
        {
            sum[i]=sum[i-1]+1;
        }
        else
        {
            sum[i]=sum[i-1]-1;
        }
        mn=min(mn,sum[i]);
    }
    for(int i=1;i<=n;i++)
    {
        if(sum[i]==mn)
        {
            res++;
        }
    }
    return res;
}
signed main()
{
    scanf("%lld%s+1",&n,s+1);
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='(')
        {
            num++;
        }
    }
    if(num!=n/2||n&1)
    {
        puts("0\n1 1");
        exit(0);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            swap(s[i],s[j]);
            int ans=query();
            if(ans>mx)
            {
                mx=ans;
                ls=i;
                rs=j;
            }
            swap(s[i],s[j]);
        }
    }
    printf("%lld\n%lld %lld",mx,ls,rs);
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
duel 到的，作为 D1 可能还是简单了点~~但我不会 D2~~。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
看到 $n$ 只有 $500$，考虑 $n^3$ 乱搞。

直接大力枚举出交换的是哪两个括号，此时复杂度已经来到 $n^2$。

接着就是要做到 $O(n)$ 数个数。

发现是括号匹配问题，考虑经典 trick。

碰到左括号就 $+1$，右括号就 $-1$，那么前缀累加一下，累加到负数的就是括号匹配不上的地方。

例如 `()(())))(`，其前缀和即为：$1,0,1,2,1,0,-1,-2,-1$。

考虑那些位置移到后面去才可能产生答案：必然是负数最大的位置。

因为合法段移来移去没有区别，所以只需考虑那一段单调的 $-1,-2,\dots,-x$。

如果我只移了这段的前面部分，那么最后面的 $-x$ 肯定消不完。

而如果我多移了一点，那么就会有一些 $+1$ 被移到最后面去，因为加的减少了，就相当于多减了一点，显然是必然会有新的数被减到负数。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510,V=1e6,INF=0x3f3f3f3f;
int n,ss,k,kk,ans,a[N];char s[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='('||c==')'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int solve()
{
	int res=0,mn=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='(') a[i]=a[i-1]+1;
		else a[i]=a[i-1]-1;
		mn=min(mn,a[i]);
	}
	for(int i=1;i<=n;i++) res+=a[i]==mn;
	return res;
}
signed main()
{
	read();rd(s,n);for(int i=1;i<=n;i++) ss+=s[i]=='(';
	if(ss!=n/2||n&1){put("0\n1 1");goto genshin;}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			swap(s[i],s[j]);ss=solve();
			if(ss>ans) ans=ss,k=i,kk=j;
			swap(s[i],s[j]);
		}
	print(ans),put('\n'),print(k),put(' '),print(kk);
	genshin:;flush();return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
题意简述：给定一个长度为 $n$ 的括号序列，若把子串 $\left[1,i\right]$ 移动到子串 $\left[i+1,n\right]$ 后面，得到的新字符串合法，即能够相互组成一个完整的左右括号，那么就认为这个 $i$ 为特殊位置。现在交换两个位置，问交换哪两个位置可使特殊位置 $i$ 最多。

这个题还是很好理解的，对于括号序列的基本结论，虽然本题用不上多少，但是默认读者已经了解。
## 分析。
发现 $n$ 最多只有 $500$ 个，所以考虑最暴力的方法。显然就是用 $n^2$ 的循环次数去没记整个字符串的位置，然后再扫一遍特殊位置的字符。那么，我们根据做字符序列题的基本做法，我们不难想到要抽象整个序列。

具体来说，为了更好地观察到整个序列1匹配情况，我们可以将左右两个括号分别用两个非 $0$ 相反数来替代，比如我们令左括号为 $1$ 则右括号为 $-1$ 这样如果两个能匹配上就会被消掉。那么，去统计是否匹配，我们考虑做前缀和。

我们设前缀和数组为 $s$。首先如果合法，必须保证左右括号数相等，即前缀和的第 $n$ 为 $0$ 否则无解。分开考虑。接下来我们根据题目要求进行交换，注意如果一次交换合法，那么前缀和区间 $\left[i+1,n\right]$ 必定要消除前缀和区间 $\left[1,i\right]$ 才能成立，即相互匹配。这就是要将在区间 $\left[i+1,n\right]$ 中的前缀和中的所有 $s$ 均减去 $s_i$。那么现在就能够把这个子串后置了，此时需要考虑整个交换对字符串整体的影响，如果后置，则后置的一部分的前缀和必定要加上前置的一部分的前缀和的影响，即前缀和区间 $\left[1,i\right]$ 中的任意一个 $s$ 必定需要加上 $s_n$。经过前面的置换操作，我们将这个前置区间内的数都减去了 $s_i$ 则 $s_n$ 现在就退化成了 $-s_i$。所以我们不妨将这个操作看做把前缀和数组中的 $\left[1,i\right]$ 区间中的所有 $s$ 均减去 $s_i$。

综上，我们发现这个交换就是把所有数都减去 $s_i$ 即可。由于括号序列合法要求所有前缀和非负，所以特殊位置只能取 $s_i$ 最小时的 $i$。可能需要稍许优化。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n;
char a[503];
int ans,l=1,r=1,s[503];
//因为即使无解也要交换一下所以初始化的l和r均为1. 
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
int totle(){
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+(a[i]=='('?1:-1);
    }//将左右括号赋值并计算前缀和。 
    if(s[n]){
	    return 0;
	}//判断合法性。 
    int mn=*min_element(s+1,s+1+n);
	int sum=0;
    for(int i=1;i<=n;i++){
        sum+=(s[i]==mn);
    }
    return sum;
}
int main(){
	read(n);
	cin>>a+1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            swap(a[i],a[j]);//暴力循环交换。 
            int res=totle();//统计一下影响。 
            if(ans<res){
			    ans=res;
				l=i;
				r=j;//确定左右区间。 
			}//特殊位置多了。 
            swap(a[i],a[j]);//换回来。 
        }
    }
    write(ans);
    printf("\n");
    write(l);
    printf(" ");
	write(r);
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_edge_ (赞：0)

本题解写法略微卡常，请注意常数优化。

我们会发现 $n$ 才只有 $500$ 级别，因此可以尝试去枚举两个点交换。

枚举两个点之后考虑如何计算贡献。

那么我们先断环为链，然后枚举每一个结尾去 check 他是否合法。

check 的时候我们不能拿栈去一个一个模拟要用点形式化的东西。

发现事实上前面不合法只有右括号失配，那么我们把左括号视为 $-1$，右括号视为 $1$，然后查询前缀最小值是否大于等于 $0$，一段前缀和是否为 $0$ 即可。

也就是说我们要求 $\min\limits _{j=i-n+1}^j{sum_j-sum_{i-n}}$ 该问题是个经典的滑动窗口问题，可以用单调队列来做到 $O(n)$ 维护。

这里注意常数小优化，就是枚举 $l,r$ 的时候强制选定 $l<r$ 这样能优化常数。

以下代码在开火车头也只是 998ms 勉强过掉，不保证在任何时候都能过掉。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=1e3+5;
int l,r,n,q[INF],sum[INF];
string s1;
int solve(string x) {
	string s2=" "+x+x;l=1;r=0;int res=0;
	for (int i=1;i<=n*2;i++)
		if (s2[i]=='(') sum[i]=sum[i-1]+1;
		else sum[i]=sum[i-1]-1;
	for (int i=1;i<n*2;i++) {
		while (l<=r && q[l]<=i-n) l++;
		while (l<=r && sum[q[r]]>=sum[i]) r--;
		q[++r]=i;
		if (i>=n && sum[q[l]]-sum[i-n]>=0 && sum[i]-sum[i-n]==0) res++;
	}
	return res;
}
signed main()
{
//	freopen("test.in","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n>>s1;int ans=0,l=0,r=0;
	for (int i=0;i<n;i++) {
		for (int j=i+1;j<n;j++) {
			swap(s1[i],s1[j]);
			int xx=solve(s1);
			if (ans<xx) ans=xx,l=i,r=j;
			swap(s1[i],s1[j]);
		}
	}
	cout<<ans<<"\n";
	cout<<l+1<<" "<<r+1<<"\n";
	return 0;
}
```


---

## 作者：Llf0703 (赞：0)

[更好的阅读体验](https://llf0703.com/p/cf-1248.html#d1theworldisjustaprogrammingtaskeasyversion)

如果字符串中 `(` 和 `)` 的个数不同，那么答案为 $0$ 。

首先 $O(n^2)$ 枚举哪两个数交换，然后 $O(n)$ 统计答案。

用 $cnt$ 表示 `(` 与 `)` 个数的差值，如对于序列 `()))((` ，$cnt$ 的序列为 $1,0,-1,-2,-1,0$ 。

可以发现从 $cnt$ 最小的 `(` 开始遍历，如上例是位置 $5$，就一定可以组成至少一个完美序列。

在遍历的过程中重新记录 $cnt$ ，如果是右括号且 $cnt=0$ ，那么从这里开始遍历也可以，答案 $+1$ 。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define mp make_pair
#define ha 1000000007
#define ui unsigned int
#define pii pair<int,int>
#define pid pair<int,double>

using namespace std;

inline int read()
{
    char ch=getchar(); int f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

int n,ans,l,r;
char s[505];

inline int work()
{
    int mn=n,mni,cnt=0;
    for (int i=1;i<=n;i++)
    {
        if (s[i]=='(') cnt++;
        else cnt--;
        if (s[i]==')') continue;
        if (cnt<mn) mn=cnt,mni=i; //mni为cnt最小的位置
    }
    cnt=0; int res=0;
    for (int i=1,j=mni;i<=n;i++,j=j==n ? 1 : j+1)
    {
        if (s[j]=='(') cnt++;
        else
        {
            cnt--;
            if (!cnt) res++;
        }
    }
    return res;
}

signed main()
{
    n=read();
    scanf("%s",s+1);
    int cnt=0;
    for (int i=1;i<=n;i++)
    {
        if (s[i]=='(') cnt++;
        else cnt--;
    }
    if (cnt) return !printf("0\n1 1"); //无解
    ans=work(); //可以不交换
    l=r=1;
    for (int i=1;i<=n;i++)
    {
        for (int j=i+1;j<=n;j++)
        {
            swap(s[i],s[j]);
            int res=work();
            if (res>ans) //更新答案
            {
                ans=res;
                l=i,r=j;
            }
            swap(s[i],s[j]);
        }
    }
    return !printf("%d\n%d %d",ans,l,r);
}
```


---

