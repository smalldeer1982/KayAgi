# Geometrical problem

## 题目描述

Polycarp 热爱几何级数以至于他爱好收集它们。但是，由于这类级数很少出现，他也喜欢仅仅删除一个元素就能得到几何级数的数字序列。

在这个任务中，我们定义满足任意一项ai都能表示为
$ c\cdot b^{i-1} $
的数列为几何级数的有限序列（b、c为实数）。

例如，[2, -4, 8]、 [0, 0, 0, 0]、 [199] 为几何级数而 [0, 1, 2, 3] 不是。

现在请你帮助Polycarp判断他最近找到的一个他不能马上确定是否满足上述条件的序列是否为几何级数的有限序列；如果不是，请你检查该序列是否能在删掉其中的一个元素后满足上述条件。

## 样例 #1

### 输入

```
4
3 6 12 24
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4
-8 -16 24 -32
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
0 1 2 3
```

### 输出

```
2
```

# 题解

## 作者：xiaozeyu (赞：3)

**CF 2200分中的大水题**

要求满足 $ \forall i\in N^*, a_i=c\cdot b^{i-1} , c,b\in R$, 其实就是指 $a$ 数组是满足等比数列的。

要求判断原数组最少删除几个数可以满足这个条件。

仔细看题，你会发现一个重要的条件，就是最多删 1 个。

当删到 2 个时就不合法。

我们可以先只看前几个数。

在前三个数中必定满足最多一个数字不合法。

也就是说，若成立，前三个数只可能是 $a_1,a_2$ 合法或 $a_1,a_3$ 合法或 $a_2,a_3$ 合法或都合法，这种情况与第一种合并。

这样我们就有了前两个合法数字，可以算出公比并判断后续是否合法。

---

几个注意点：

1. 要特判满足的前两项为 0 的情况。

2. 选32位的用 double 会被卡，要用 double 就选 C++ 17 等语言最保险。

---

代码

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c)) f^=!(c^45),c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=100010;
int n,cnt,ans;
int s[maxn];
double a,b,c,d;
int f(double a,double b) 
{
	if(a==0) d=0;
	else d=b/a;
	c=a;
	cnt=0;
	For(i,1,n)
	{
		if(cnt>=2) break;
		if(c==s[i])c*=d;
		else ++cnt;
	}
	return cnt;
}
int main()
{
	n=read();
	For(i,1,n) s[i]=read();
	ans=min(f(s[1],s[2]),(min(f(s[1],s[3]),f(s[2],s[3]))));
	printf("%d",ans);
}
```

---

## 作者：hgckythgcfhk (赞：2)

一看到这个题，觉得难度不到蓝，想水一下，但做了之后发现这个题主要是难在细节很多。

首先一个很简单的暴力做法是枚举子序列，由于长度固定为 $n-1$，所以只需要枚举 $n$ 次，时间复杂度 $O(n^2)$ 考虑优化这个过程，发现如果不选 $a_1$，那么 $a_2$ 一定是第 $1$ 项，且后面全 选，否则 $a_1$ 一定是第 $1$ 项，后面每次循环判断可不可以加入下一项，判断方式是判断当前的数除以上一项的结果是否等于前两项相除的结果，但我们无法确定第 $2$ 项。

我们可以确定第 $2$ 项一定是前面很少的几个，具体是哪一个不重要，反正多枚举几次只是常数的差距，这样就做出来了。

但是，现在有两个问题，数组长度不一定够，而且会有一些烦人的 $0$ 导致 RE，而且由于我最开始把整个数组除以 $a_1$ 算了一次，又除以 $a_2$ 算了一次，更加增加了难写程度。

换个思路，同时给大家一个忠告：**解决难写的最好方法是不写，不会正解的最优手段是乱搞**，考虑一个局限性比较大但足够过本题的做法，观察数据范围，发现我们可以枚举 $b$，这样可以避免一些需要很多特判的除法，等等，这个时间复杂度好像是 $O(nV)$ 的，如果你这么想，那一定是看数据范围的时候没理解值域不大的真正用处，有两个个显然的结论：我们可以在当前项的绝对值大于 $10^4$ 的时候直接判断不行，如果超过两次无法成为下一项，那一定不行。基于这两个结论，有一个显然的推论，除了 $-1$，$0$，$1$ 以外，每个 $b$ 至多循环 $\log_{\mid b \mid}{V}$ 次。

然后说一下本题的细节。

1. 特判 $n=1$ 时一定输出 $0$，避免不必要的麻烦。

2. 最好特判 $n=2$ 时 $a_1=0$ 且 $a_2 \ne 0$ 时输出 $2$ 否则输出 $0$，避免不必要的麻烦。

3. 特判 $b\ne 0$ 且 $c=0$ 的情况，因为 $c=0$ 时，结果与 $b$ 无关，防止一些玄学的错误和 TLE。

4. 不保证 $b$ 是整数。

5. 只枚举整数和整数的倒数即可，因为原题题面说：```All the elements of the given sequence are integers```

6. 单独枚举 $0$，因为会出现除 $0$ 的 RE。

```
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define void inline void
using namespace std;constexpr unsigned N=1e5+1;
double a[N];unsigned ans=1;signed n;
void chk(const int st,const register double d){if(st>n)return;int cnt=1,f=0;register signed pre=a[st];
	if(!a[st]&&d)return;
	for(int i=st+1;i<=n;++i){a[i]==pre*d?++cnt,pre=a[i]:++f;ans<cnt?ans=cnt:0;if(f>1||abs(pre*d)>1e4||(d&&!pre))return;}}
signed main(){open;cin>>n;if(n==1)return cout<<0,0;for(int i=0;i<n;cin>>a[++i]);
	for(register signed i=-1e4;i<=1e4;++i){chk(1,i),chk(2,i);if(i)chk(1,1.0/i),chk(2,1.0/i);if(ans==n)return cout<<0,0;}
	cout<<(ans==n?0:ans==n-1?1:2);
}

```
最后反思一下我为什么一开始说这个做法有局限性，首先，这个做法基于值域，即使通过一些类似离散化的思路减少一些明显不对的 $b$，也会因为这个做法的 $\log V$ 不能处理高精度。然后，这个做法不好处理输入不是整数的情况，处理方法和 long long 范围内一样，通过类似离散化的方式只枚举绝对值最小的数和其他数的商及其相反数，但这样这个做法就失去了好写的优势，甚至比正解更难写。

但是这个做法也有优点，考虑本题的一个加强版，长度不固定为 $n-1$ 或者求最长几何级数子序列，但值域很小，小到可以视为常数，发现这个做法可以处理，记录值域内每个数第一次出现的位置，枚举这些位置作为第 $1$ 项即可。

---

## 作者：XXh0919 (赞：1)

~~这题是我看了题解才A的~~

这题实际上是让我们判断**只删去一个数（注意只能删一个数）**，能否使这个序列成为**等比数列**。

我们先看前三个数 $a_1$，$a_2$，$a_3$。这三个数中至少会有一个数不合法，也就是说，若此条件成立，则合法的组合只有 $a_1,a_2$ 和 $a_1,a_3$ 和 $a_2,a_3$ 还有  $a_1,a_2,a_3$。从这我们即可得到前两个合法的数，并算出公比，推出之后的数是否合法。若不合法，就不往上乘公比，即假装删除这个数。

**注意**：

- 要特判满足的前两项为 0 的情况，否则可能会出问题。
- 选 32 位的用 double 会有问题，要用 double 就选 C++ 17 等语言最保险。

代码来啦：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l[10001],n,sum,cnt;
double c,d;

long long solve(double N,double m)
{
	cnt=0;
	if(N==0)d=0;
	else d=m/N;
	c=N;
	for(int i=1;i<=n;++i)
	{
		if(cnt>=2)break;//删了两个以上跳出
		if(c==l[i])c*=d;//合法则往上乘
		else ++cnt;
	}
	return cnt;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	   cin>>l[i];
	sum=min(solve(l[1],l[2]),min(solve(l[1],l[3]),solve(l[2],l[3])));
	cout<<sum<<endl;
	return 0;
 } 
```
管理员求过！！

---

## 作者：Ag2WO4 (赞：0)

## 前排提示：这是一篇 Python 题解！
涉及两步及两个特判：

1. 若第一次发现违反指数型规则，应当删除有疑的数;
2. 然后验证是否有第二次违反。

特判：
#### 最大的问题：零！
要么数列从第二项开始全为零，要么零不出现。优先确认零的存在。
#### 第二大问题：数列很短怎么办？
务必单独拎出来，小心运行时错误（数列长度小于三时比较是跑不起来的）。

余下的内容按照等比数列 $a_n^2=a_{n-1}\times a_{n+1}$ 的性质判定即可。
## ~~无比丑陋的~~ AC 代码
~~最近题解写多了累了就懒得美化了~~
```python
a=int(input())
if a==1:print(0);exit()
if a==2:b,c=map(int,input().split());print(1 if b==0 and c else 0);exit()
if a==3:
    b,c,d=map(int,input().split())
    if c==d==0:print(0)
    elif c and d:print(1 if b*d-c*c else 0)
    else:print(1)
    exit()
def r(i,j):
    for x in range(a-3+j):
        if i[x]*i[x+2]-i[x+1]**2:
            if j:i.pop(x+2);return r(i,0)
            else:return 2
    return 1-j
b=list(map(int,input().split()))
if all(i==0 for i in b[1:]):print(0)
elif b.count(0)>1:print(len(b)-1-b[1:].count(0)if 2>len(b)-1-b[1:].count(0)else 2)
elif 0 in b:b.remove(0);print(r(b,0))
elif b[0]*b[2]-b[1]**2:c=b[1:];d=b[:];e=b[:];d.pop(1);e.pop(2);print(min(r(c,0),r(d,0),r(e,0)))
else:print(r(b,1))
```


---

## 作者：_edge_ (赞：0)

这个题 …… 我感慨万分，~~搞了一个小时最终还是看题解 A 掉的。 (~~

来说一下我的不太对的想法，就是考虑计算每个数与它前面的数的公比以及首项，用个桶来维护一下，最后如果都相等是第一种，去掉一种然后可行的话是第二种，否则就第三种。

这个问题非常的严重，因为 double 这个类型好像 nan 和 inf 有点分的不太对，~~如果有哪个过了的神仙可以私信，来教教我。~~

事实上完全不需要这么麻烦，如果我们能够确定公比以及首项那显然，我们整一个数列都可以确定下来了。

那么我们考虑如何确定公比和首项一个比较显然的想法就是拿前三个来做，我们枚举前三个有哪两个是对的，然后钦定它是对的之后再去判断符合等比数列的有多少个数。

这样好像看看不太对，但事实上，如果他是第一种或者第二种，前三个数里面肯定只有一个存在的有问题，所以这挺对的。

还有一点小问题是，如果我们遇到不符合的，那就不往上乘公比，这样的话可以假装删掉了这个数。

然后就做完了。

```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <cmath>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
using namespace std;
const int INF=1e5+5;
int n;
double a[INF],b[INF],c[INF],cc[INF];
map <double,map<double,int> > Map[2][2],Map1[2][2];
double ksm(double x,int y) {
	double ba=x,ans=1;
	while (y) {
		if (y&1) ans=(ans*ba);
		ba*=ba;y>>=1;
	}
	return ans;
}
int check(double x,double y) {
	double d=0,c=0;
	if (x==0) d=0;
	else d=y/x;c=x;
	int cnt=0;
	for (int i=1;i<=n;i++) {
		if (cnt>=2) break;
		if (a[i]==c) c*=d;
		else cnt++;
	}
	return cnt;
}
signed main()
{
//	freopen("test.in","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	int ans=min(check(a[1],a[2]),min(check(a[2],a[3]),check(a[1],a[3])));
	cout<<ans<<"\n";
	return 0;
}
```


---

