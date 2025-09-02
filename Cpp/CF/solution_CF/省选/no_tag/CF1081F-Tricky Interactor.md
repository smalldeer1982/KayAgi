# Tricky Interactor

## 题目描述

这是一个交互题。

Chouti 学习累了，于是打开电脑开始玩一个解谜游戏。

很久很久以前，这个男孩发现了一个长度为 $n$ 的序列 $s_1, s_2, \ldots, s_n$，由一个狡猾的交互器保管。该序列只包含 $0$ 和 $1$，其中 $1$ 的个数为 $t$。男孩除了知道 $n$ 和 $t$ 外，对这个序列一无所知，但他可以通过与交互器进行一些查询来尝试找出这个序列。

我们定义一种操作叫做翻转。翻转 $[l,r]$（$1 \leq l \leq r \leq n$）表示对每个 $x \in [l,r]$，将 $s_x$ 变为 $1-s_x$。

在每次查询中，男孩可以给交互器两个整数 $l, r$，满足 $1 \leq l \leq r \leq n$，然后交互器会以相同的概率选择翻转 $[1,r]$ 或 $[l,n]$（所有决策均独立，详见提示部分）。每次操作后，交互器会告知当前序列中 $1$ 的个数。注意，序列在每次操作后不会恢复。

请帮助男孩在不超过 $10000$ 次交互内找出原始序列。

“奇怪的传说，愚蠢的游戏。”他这样想着。然而，尝试了几次后，他依然卡在了这里。你能帮他通关吗？

## 说明/提示

对于第一次查询 $1,1$，交互器会选择翻转 $[1,1]$ 或 $[1,4]$。假设它选择了翻转 $[1,4]$，则序列变为 1100。

第二次查询 $1,1$，交互器会再次选择翻转 $[1,1]$ 或 $[1,4]$。假设它又选择了翻转 $[1,4]$，则序列变为 0011。

第三次查询 $3,4$，交互器会选择翻转 $[1,4]$ 或 $[3,4]$。假设它选择了翻转 $[3,4]$，则序列变为 0000。

问：交互器是如何在 $[1,r]$ 和 $[l,n]$ 之间选择的？真的随机吗？

答：交互器会使用一个秘密的[伪随机数生成器](https://en.wikipedia.org/wiki/Pseudorandom_number_generator)。只有 $s$ 和你的查询会被哈希并用作种子。因此，如果你对同一个秘密字符串给出相同的查询序列，将会得到相同的结果。除此之外，你可以认为选择是完全随机的，就像抛硬币一样。你不需要（也不应该）利用具体的生成器来通过本题。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
2
2
0```

### 输出

```
? 1 1
? 1 1
? 3 4
! 0011```

# 题解

## 作者：Scintilla (赞：5)

### [CF1081F Tricky Interactor](https://codeforces.com/problemset/problem/1081/F)

**Description**

**这是一道交互题。**

有一个长度为 $n$ 的 $01$ 序列，初始时 $1$ 的个数为 $t$。定义一次操作为给定 $l, r(l \le r)$，交互库会**等概率地**从区间 $[1, r]$ 和 $[l, n]$ 中选择一个，然后翻转下标在该区间内的数（翻转即 $x \to 1 - x$），并告诉你翻转完的序列中有多少个 $1$。操作之间**不是**独立的，即对序列的修改是永久的。

你需要在 $10000$ 次操作内得出原始的序列。

$n \le 300$。

**Solution**

设这个序列为 $a$。注意到连续操作 $[i, i]$ 两次所形成的序列要么是 $a$，要么是除了 $a_i$ 都翻转的序列。我们可以多随几次，总能碰到第二种情况，然后就能知道第 $i$ 个数是 $0$ 还是 $1$ 了，然后再还原回去。当然有一个问题就是除开 $a_i$ 以外剩下的 $01$ 数量相等，这里我们可以把 $[i, i]$ 改为 $[i, i + 1]$，这样每次能得到 $a_i + a_{i + 1}$，最后再统计一下就可以了。这样我们就得到了一个期望 $8n$ 次询问的做法。

其实放 $10000$ 没有必要，完全可以开到 $3000$~~，总不至于有人这么非吧~~。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define rep(i, s, e) for (re int i = s; i <= e; ++i)
#define drep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

const int N = 300 + 10;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = false; c = getchar();}
    while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

int n, t, ans[N];

il int ask(int l, int r) {
    cout << "? " << l << ' ' << r << endl;
    fflush(stdout);
    int res; cin >> res;
    return res;
}

il int get(int l, int r) {
    int res;
    do { res = ask(l, r); res = ask(l, r); } while (res == t);
    int dis = res - (n - t);
    do { res = ask(l, r); res = ask(l, r); } while (res != t);
    return (r - l + 1 + dis) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> t;
    if (n == 2 * t + 1 || n == 2 * t - 1) {
        static int a[N];
        rep(i, 1, n - 1) a[i] = get(i, i + 1);
        a[n] = 2 * t;
        rep(i, 1, n - 1) a[n] -= a[i];
        rep(i, 1, n - 1) {
            if (i & 1) ans[n] -= a[i];
            else ans[n] += a[i];
        }
        ans[n] = (ans[n] + a[n]) / 2;
        drep(i, n - 1, 1) ans[i] = a[i] - ans[i + 1];
    }
    else rep(i, 1, n) ans[i] = get(i, i);
    cout << "! ";
    rep(i, 1, n) cout << ans[i];
    cout << endl;
    return 0;
}
```

---

## 作者：Durant_Lee (赞：1)

[欢迎来我的博客逛逛](https://blog.csdn.net/Dream_Lolita/article/details/85054884)

首先我们知道一个结论：翻转一个区间，则这个全局中[1个数的变化量]$\equiv$ 区间长度$(\text{mod}\ 2)$
证明：设一次翻转区间$[l,r]$，全局$1$的个数从$x$变成$y$，这个区间内原来有$t$个$1$则$y-x=(r-l+1)-2t$。
所以我们如果让$[1,l]$和$[r,n]$的长度不同，我们就可以知道翻转的是哪一个区间，我们也就知道了。
现在还要解决的问题是怎么样使得这个串翻转我们期望翻转的一段。实际上我们如果想单独翻转$[1,l]$这一段，我们只需要一直对$[l,r]$操作即可，期望操作次数应该是$3$次，具体证明的话也不难：
- 我们令$f_{0/1,0/1}$表示每一段翻不翻转时期望多少步能翻转到$f_{1,0}$，我们可以列出等式：$f_{0,0}=\frac {f_{0,1}+f_{1,0}} 2+1,f_{0,1}=\frac {f_{0,0}+f_{1,1}} 2+1,f_{1,1}=\frac {f_{1,0}+f_{0,1}} 2+1$. 那么$f_{0,0}=3,f_{0,1}=4,f_{1,1}=3$


综上，我们可以得到下面这个做法：我们设$s_i$表示第$i$位的数字。
- 当$n$是奇数，我们每次应当询问一个长度为偶数的区间，于是我们可以查询$(1,2),(1,2),(2,3),(3,4)\dots (n-2,n-1)$，目的是为了翻转$[2,n],[1,2],[1,3]\dots[1,n-1]$，这样我们可以知道$s_1+s_2,s_1+s_2+s_3,\dots$以及$s_2+s3+\dots+s_n$于是$s$就唯一确定了。
- 当$n$是偶数，我们每次应当询问一个长度为奇数的区间，于是我们可以查询$(1,1),(2,2),(3,3)\dots (n-1,n-1)$，目的是为了翻转$[1,1],[1,2],[1,3]\dots[1,n-1]$，这样我们可以知道$s_1,s_1+s_2,s_1+s_2+s_3,\dots $同样可以计算得到答案。

【参考代码】
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
using namespace std;

typedef pair<int,int> pii;
typedef long long ll;
const int N=1e4+10;
int n,cnt,a[N],ans[N];

int read()
{
	int ret=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
	return f?ret:-ret;
}

bool flip(int l,int r)
{
	printf("? %d %d\n",l,r);fflush(stdout);
	a[++cnt]=read();return (a[cnt]-a[cnt-1])&1;
}

int main()
{
	n=read();ans[n]=a[0]=read();
	for(int i=1;i<n;++i)
	{
		int x=a[cnt],t[2]={0,0};
		if(i==1 && n&1)
		{
			while(!t[0] || t[1]) t[flip(2,n)]^=1;
			int y=a[cnt];
			ans[i]=ans[n]-(n-1-y+x)/2;
			while(t[0] || t[1]) t[flip(2,n)]^=1;
		}
		else
		{
			while(!t[0] || t[1]) t[(flip(i-(n&1),i)^i)&1]^=1;
			int y=a[cnt];
			ans[i]=(i-y+x)/2;
			while(t[0] || t[1]) t[(flip(i-(n&1),i)^i)&1]^=1;
		}
	}
	printf("! ");
	for(int i=1;i<=n;++i) printf("%d",ans[i]-ans[i-1]);
	puts("");fflush(stdout);

	return 0;
}
```

---

## 作者：happybob (赞：0)

题意：

**这是一道交互题。**

有一个长度为 $n$ 的 $01$ 序列，初始时 $1$ 的个数为 $t$。定义一次操作为给定 $l, r(l \le r)$，交互库会**等概率地**从区间 $[1, r]$ 和 $[l, n]$ 中选择一个，然后翻转下标在该区间内的数（翻转即 $x \to 1 - x$），并告诉你翻转完的序列中有多少个 $1$。操作之间**不是**独立的，即对序列的修改是永久的。

你需要在 $10000$ 次操作内得出原始的序列。

$n \le 300$。

解法：

对于 $n$ 分奇偶讨论。

当 $n$ 为偶数时，直接考虑依次求出每个位置的值。发现对 $[i,i]$ 连续操作两次，结果要么和原序列相同，要么除了 $i$ 其他位置都 flip，概率均为 $\dfrac{1}{2}$，期望 $2$ 次可以得到第二种，于是可以确定 $i$ 的值，然后再期望 $2$ 次还原，总共期望 $4 \times 2$ 次操作。根据期望线性性，在期望 $8n$ 次操作内可以得到原序列。

$n$ 为奇数时，上述做法可能无法判定原序列与除 $i$ flip 的序列，但是我们直接暴力求出 $a_1$ 后对于每个 $i$ 操作 $[i,i+1]$，套用上述做法即可。

---

## 作者：Purslane (赞：0)

# Solution

一杯茶，一包烟，一道 `*2600` 写一天。

考虑连续对同一段进行操作。用 $\overline{A}$ 表示序列 $A$ 翻转的结果。那么会得到两种可能：

1. 原序列 $ABC$；
2. 两头取反 $\overline{A}B\overline{C}$。

且这两种事件出现的概率相等。

若 $2 \nmid |A|+|C|$，很容易分辨两种情况（奇偶性不同），顺带把 $B$ 中 $1$ 的个数计算出来。

因此，当 $n$ 是偶数的时候，令 $|B|=1$；当 $n$ 是奇数的时候，令 $n=2$。

设答案是 $a_1a_2\dots a_n$。当 $n$ 是偶数的时候，直接得到结果；当 $n$ 是奇数的时候，我们知道相邻两项的和。

你也不用高斯消元，直接枚举 $a_1$ 这样后面的都确定了，暴力计算 $a_1$ 是 $0$ 还是 $1$ 即可。

CF 不提供交互库 /ll

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=300+10;
int n,t,a[MAXN],ans[MAXN];
int main() {
	cin>>n>>t;
	if(n==1) return cout<<"! "<<t<<endl,cout.flush(),0;	
	if(n%2==0) {
		ffor(i,1,n) {
			int frog=0;
			while(1) {
				cout<<"? "<<i<<' '<<i<<endl,cout.flush();
				int rst; frog^=1,cin>>rst;
				if(frog%2==0&&rst!=t) {
					if(rst==n-t-1) a[i]=0;
					else a[i]=1;
					break ;
				}
				else continue ;
			}
			while(1) {
				cout<<"? "<<i<<' '<<i<<endl,cout.flush();
				int rst; frog^=1,cin>>rst;
				if(frog%2==0&&rst==t) break ;
				else continue ;
			}
		}
		ffor(i,1,n) ans[i]=a[i];
	}
	else {
		ffor(i,1,n-1) {
			int frog=0;
			while(1) {
				cout<<"? "<<i<<' '<<i+1<<endl,cout.flush();
				int rst; frog^=1,cin>>rst;
				if(frog%2==0&&rst!=t) {
					a[i]=(t+rst-n+2)/2;
					break ;	
				}
				else continue ;
			}
			while(1) {
				cout<<"? "<<i<<' '<<i+1<<endl,cout.flush();
				int rst; frog^=1,cin>>rst;
				if(frog%2==0&&rst==t) break ;
				else continue ;
			}
		}
		int cnt=0,lst=0;
		ffor(i,1,n-1) lst=a[i]-lst,cnt+=lst;
		if(cnt==t) {
			lst=ans[1]=0;
			ffor(i,1,n-1) lst=a[i]-lst,ans[i+1]=lst;	
		}
		else {
			lst=ans[1]=1;
			ffor(i,1,n-1) lst=a[i]-lst,ans[i+1]=lst;	
		}
	}
	cout<<"! ";
	ffor(i,1,n) cout<<ans[i];
	cout<<endl,cout.flush();
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
随机性概率翻转？期望这类的一看就是要分类随机！于是这道题的定位就是奇奇怪怪分类交互题。
## 分析。
我们考虑能不能“准确”预测翻转的位置？注意到翻转长度为奇数的区间会导致 $1$ 的个数变化量为奇数，否则个数变化量为偶数。换句话说，如果我们让 $\left[1,r\right]$ 和 $\left[l,n\right]$ 这两段长度的奇偶性不同，那么根据变换后的 $1$ 的个数就可以判断出翻转的是哪一个区间了。

但是随机的翻转使我们考虑到我们想要的是翻转固定的区间，而这个区间可以通过多次翻转包括该区间内的其它区间实现。由于是随机的，可以证明期望恰好翻转左右两个可能区间中的一个区间，期望的翻转次数是 $3$ 次。
                        
然后我们直接分离讨论 $n$ 的奇偶性即可。如果 $n$ 是偶数，则任意的 $i$ 和 $n-i+1$ 的奇偶性不同，所以我们可以通过翻转 $i$ 前面的前缀得到原来的前缀和。具体来说，我们设原来的字符串中有 $p$ 个 $1$ 且总长度为 $m$。设翻转后和翻转前 $1$ 的个数分别为 $t_2$ 和 $t_1$ 则有 $t_2=t_1-p+m-p$ 显然我们可以直接解方程。如果 $n$ 是奇数，则任意的 $i$ 和 $n-i$ 奇偶性不同。其实此时和偶数的情况类似，也可以看做翻转 $i$ 前面的前缀，但是稍有不同。就是第一个区间我们并不能确定，所以我们考虑翻转后缀，求出后缀翻转中 $1$ 的个数，然后直接判断即可。

最后注意一些小细节，比如特殊处理 $n=1$ 的情况。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdio>
using namespace std;
int n,t_1;
int ans[305],rev[305];
int ask(int l,int r){
	cout<<"? "<<l<<" "<<r<<"\n";
	fflush(stdout);
	int ask_tt;
	cin>>ask_tt;
	return ask_tt;
}
int main(){
	cin>>n>>t_1;
	int res;
	if (n==1){
		ans[1]=t_1;
	}
	else if(n&1){
		//int res=0;
		for (res=t_1;res==t_1;res=ask(1,n-1)){
			ask(1,n-1);
			//res=i;
		}
		ans[n]=res<t_1;
		rev[n]=1;
		for (int i=n-1;i>=1;i--){
			for (t_1=res;res==t_1;res=ask(i,i+1)){
				ask(i,i+1);
			}
			for (int j=1;j<=n;j++){
				rev[j]^=j<i||j>i+1;
			}
			ans[i]=(t_1+res-n)/2+1-(ans[i+1]^rev[i+1])^rev[i];
		}
	}
	else{
		for (int i=n,res=t_1;i>=1;i--){
			for (t_1=res;res==t_1;res=ask(i,i)){
				ask(i,i);
			}
			for (int j=1;j<=n;j++){
				rev[j]^=j<i||j>i;
			}
			ans[i]=(t_1+res-n+1)/2^rev[i];
		}
	}
	cout<<"! ";
	for (int i=1;i<=n;i++){
		cout<<ans[i];
	}
	fflush(stdout);
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

