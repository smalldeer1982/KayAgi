# Pride

## 题目描述

## 问题描述

你有一个长度为 $n$ 的数列 $a$，你能执行一些操作。每个操作是这样的：选择两个相邻的数 $x$ 和 $y$，把它们中的一个换为 $\gcd(x,y)$。这里的 $\gcd$ 代表[最大公约数](en.wikipedia.org/wiki/Greatest_common_divisor)。

问你把数列中的数全变成 $1$ 的最小操作次数。

## 说明/提示

在第一个例子中你可以把数都变成 $1$ 通过这 $5$ 步：

- $[2,2,3,4,6]$
- $[2,1,3,4,6]$
- $[2,1,3,1,6]$
- $[2,1,1,1,6]$
- $[1,1,1,1,6]$
- $[1,1,1,1,1]$

可以证明在这个例子中不可能用 $5$ 步以下来把所有的数都变成 $1$。

## 样例 #1

### 输入

```
5
2 2 3 4 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
2 4 6 8
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3
2 6 9
```

### 输出

```
4
```

# 题解

## 作者：Mine_King (赞：8)

首先，如果序列中本来就有一个 $1$，那么最少的次数是多少？  
显然是 $n-1$：每次把与 $1$ 相邻的数变为 $1$，需要 $n-1$ 次。可以证明这样是最优的，因为每次操作都有一个数的贡献。

于是我们就有了思路：用最少的次数变出一个 $1$。  
首先，如果我们做了一次操作使 $x$ 变化了，那么下一次操作必定是 $x$ 和与他相邻的一个数的变化。否则你这次操作相当于白费了。  
这时可能有人会说：我可以先操作其他数再和 $x$ 操作呀。但是请注意：$gcd(gcd(a,b),c)=gcd(a,gcd(b,c))$，所以先做和后做是等价的。  
然后第二点：第一次操作后一定是一直往一个方向进行。原因也是 $gcd(gcd(a,b),c)=gcd(a,gcd(b,c))$，从中间向两边扩展和直接从一端扩展是等价的。  

于是我们就可以写出代码：
枚举每个区间，如果这个区间的 $gcd$ 为 $1$，那么这个区间是可行的。在可行的区间里找一个最小的即可。最后的答案加上 $n-1$（把其他的数也变成 $1$ 需要 $n-1$ 次）。  
但是这样是 $O(n^3)$ 的呀，跑步过去。  

那么我们对他优化：  

1. 枚举左端点 $l$
2. 从 $l$ 开始向右枚举右端点 $r$
3. 每次 $r+1$ 就把现在的 $r$ 和之前的结果做 $gcd$

这样就能让求值和枚举右端点公用一个循环，时间复杂度 $O(n^2)$。

注意特判一开始就有 $1$（不一定是一个）和无解（所有数一起的 $gcd$ 不等于 $1$）的情况

**code：**
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[2006];
int one,g,mn=1e9;
int gcd(int _a,int _b){return _b==0?_a:gcd(_b,_a%_b);}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		g=gcd(g,a[i]);
		if(a[i]==1) one++;
	}
	if(one!=0){printf("%d\n",n-one);return 0;}
	if(g!=1){puts("-1");return 0;}
    //两个特判
	for(int i=1;i<=n;i++)//枚举左端点
	{
		int b=a[i];
		for(int j=i+1;j<=n;j++)//枚举右端点并求值
		{
			b=gcd(b,a[j]);
			if(b==1){mn=min(mn,j-i);break;}
            //小优化：找到1之后再往下去搜显然是不明智的，答案不会更优
		}
	}
	printf("%d\n",mn+n-1);
	return 0;
}
```

---

## 作者：_LighT_ (赞：2)

题目传送门：[CF891A](https://www.luogu.com.cn/problem/CF891A)

## 思路

1. 显然，当 $\gcd\{a_i\}\ne 1$ 时无解。

2. 当含有 $x$ 个 $1$ 时答案为 $n-x$.

3. 对于一般情况，有一个比较明显的贪心：使得出第一个 $1$ 的操作数最少，再加上 $n-1$ 即为最终答案。

   我们考虑让 $a_k$ 变为 $1$，有两种方式，一种是从左向右操作，另一种是从右向左，这两种方式本质上是一致的（只要对称一下），那么接下来以向右为基准。
   
   现在，我们需要找到最大的 $l$，使得 $\gcd\{a[l\dots k]\}=1$，随着 $l$ 的减小，$\gcd$ 单调不减，那么可以使用二分，而 $\gcd$ 可以用 ST 表和线段树维护。总时间复杂度：$O(n\log n)$.
   
加强版：[P8792](https://www.luogu.com.cn/problem/P8792)

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
const int MAXN=1E5+5;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x;
}
int Log[MAXN],st[MAXN][18];
int n;
inline int query(int x,int y){
	int s=Log[y-x+1];
	return __gcd(st[x][s],st[y-(1<<s)+1][s]);
}
inline void init(){
	for(ri j=1;j<=17;++j)
		for(ri i=1;i+(1<<j)-1<=n;++i)
			st[i][j]=__gcd(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int main(){
	n=read();
	Log[0]=-1;
	int flag=0;
	for(ri i=1;i<=n;++i){
		st[i][0]=read();
		if(st[i][0]==1) flag++;
		Log[i]=Log[i>>1]+1;//预处理log2(x)
	}
	if(flag){
		printf("%d",n-flag);
		return 0;
	}
	init();
	int l=1,ans=INT_MAX;
	if(query(1,n)!=1){
		printf("-1");
		return 0;
	}
	for(ri i=1;i<=n;++i){
		int L=l,R=i,mid;
		flag=0;
		while(L<=R){
			mid=(L+R)>>1;
			if(query(mid,i)==1)
				L=mid+1,l=mid,flag=1;
			else
				R=mid-1;
		}
		if(flag) ans=min(ans,i-l);
	}
	printf("%d",ans+n-1);
	return 0;
}
```


---

## 作者：gdf_yhm (赞：1)

[P8792](https://www.luogu.com.cn/problem/P8792)

[CF891A](https://www.luogu.com.cn/problem/CF891A)

### 思路

为了使数组只剩 $1$，需要从一个 $1$ 开始不断与傍边的数做 gcd 操作，需要 $n-cnt_1$ 次。

如果数组中没有 $1$，那么需要连续对一段数 $[l,r]$ 做 gcd 操作得出一个 $1$，再用一个 $1$ 做 $n-1$ 次操作覆盖数组。最后答案为 $n-1+r-l+1-1$。当 $[l,r]$ 区间的 gcd 为 $1$ 时，可以选择该区间。

问题转换为：求一段最短的区间使其区间 gcd 为 $1$。

有 $n^2$ 个区间，直接枚举计算复杂度是 $O(n^3)$。

由于没有修改，可以使用 ST 表 $O(n\log n)$ 预处理，$O(1)$ 得出区间的 gcd。复杂度 $O(n^2)$。

但不一定要枚举每个区间。如果最大的区间不可取，大区间下的小区间也不可取。可以用双指针弄到 $O(n)$，但比较复杂。

询问最小，考虑二分答案，$O(n\log n)$，可以接受。

CF 上的双倍经验范围较小，但有一些 hack。

### code

```cpp

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,a[maxn],st[maxn][25];
int lg[maxn],pw[25];
int gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
int query(int l,int r){
	int k=lg[r-l+1];
	return gcd(st[l][k],st[r-pw[k]+1][k]);
}
int l,r,mid,ans;
bool check(int x){
	for(int i=1;i+x-1<=n;i++){
		int j=i+x-1;
		if(query(i,j)==1)return true;
	}
	return false;
}
int cnt;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),st[i][0]=a[i],cnt+=(a[i]==1);
	if(cnt==n){
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			printf("%d\n",n-cnt);
			return 0;
		}
	}
	pw[0]=1;lg[1]=0;
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=20;i++)pw[i]=pw[i-1]<<1;
	for(int j=1;j<=lg[n];j++){
		for(int i=1;i+pw[j]-1<=n;i++){
			st[i][j]=gcd(st[i][j-1],st[i+pw[j-1]][j-1]);
		}
	}
	if(query(1,n)!=1){
		printf("-1\n");
		return 0;
	}
	l=1,r=n;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n",ans-1+n-1);
}

```



---

## 作者：Arghariza (赞：1)

贪心，如果在第 $x$ 步凑出了 $1$ ，接下来就可以直接写出答案（即 $n+x-1$ ，剩下的全部与 $1$ 操作），如果一开始就有 $1$ 了，直接输出 $n-1$的个数即可。

所以说关键还是在咋凑一个 $1$ 出来。

~~暴力枚举大法好~~

其实直接从左到右枚举每个数再从这个数开始从左向右取 $gcd$ ，直到这个数变为 $1$ ，用此时所用的次数更新最少次数就可以了。当然还得特判一下能不能取到 $1$ ，如果不能的话最后输出 $-1$ 。

最后输出 $n+$最少步数$-1$（原来那个 $1$ 不用变了） 。

注释放在代码里面了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, flag, stps = 2147483647, s[100001];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &s[i]);
		if (s[i] == 1) flag++;// 计算1的个数
	}
	if (flag) {// 如果有1的话直接输出即可
		printf("%d", n - flag);
		return 0;
	}
	for (int i = 1; i < n; i++) {// 挨个枚举，下标为n的是不行的，因为ta不为1并且他后面没有数了，不可能凑成1
		int tmp = s[i], steps = 0;// 
		for (int j = i + 1; j <= n; j++) {// 从左到右计算gcd
			steps++;// 到1的次数递加
			tmp = __gcd(tmp, s[j]);// 取gcd
			if (tmp == 1) {// 如果取到1了
				flag = 1;// 可以凑得到1
				stps = min(stps, steps);// 更新最小次数
				break;// 直接break掉，因为再继续取的话也没意义
			}
		}
	}
	if (flag) printf("%d", n + stps - 1);// 输出最少次数
	else printf("-1");// 如果凑不到1
	return 0;
}
```

---

## 作者：JACK_POT (赞：1)

很容易发现，因为 $1$ 和任何正数的 $gcd$ 都为 $1$ ，所以只要有一个 $1$ ，就可以每次从 $1$ 的两边传递出去，操作一次就能获得一个 $1$，答案为不是 $1$ 元素的数量

所以我们需要找到最快获得一个 $1$ 的方法

这里需要先发现 $gcd$ 的一个性质：几个正数共同的 $gcd$ ，满足交换律和结合律

由于是相邻的数才能操作，所以我们要最快得到 $1$ ，就要对长度最小的一段连续元素做 $gcd$ ，其中两两操作的顺序可以从左向右或从右向左传递前一步操作获得的新值

最后加上其他不是 $1$ 元素的数量 $n-1$

**注意特判：原始序列就有 $1$ 的情况。设有 $sum$ 个 $1$ ，答案就是$n-sum$**

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define PII pair<int,int>
const int M=2005;
int n,a[M],f[M][M],ans=1e9,sum; 
int gcd(int a,int b) {
	return b==0?a:gcd(b,a%b);
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		sum+=a[i]==1;
	}
	if(sum) {//特判
		printf("%d\n",n-sum);
		return 0;
	}
	for(int i=1;i<=n;i++) {
		f[i][i]=a[i];
		for(int j=i+1;j<=n;j++) 
			f[i][j]=gcd(f[i][j-1],a[j]);
            //f[i][j]为i到j的gcd
	}
	for(int i=1;i<=n;i++) 
		for(int j=i;j<=n;j++) 
			if(f[i][j]==1) ans=min(ans,j-i);
	if(ans==1e9) puts("-1");//无答案
	else printf("%d\n",ans+n-1);
	return 0;
}

```


---

## 作者：囧仙 (赞：1)

## 题目大意

给定 $n$ 个正整数。每次选择两个相邻的数 $a,b$ ，使其中一个变成 $\gcd(a,b)$ 。求使所有正整数变成 $1$ 的最少步骤。

## 题解

显然， $\gcd(1,x)=1$ 。于是，只要我们已经获得了一个 $1$ ，就能用它向两边扩展，使得任何数字都能变成 $1$ 。显然，这种贪心是最优的。

显然，假设数列中有 $c$ 个 $1$ ，我们只需要操作 $n-c$ 次就行了。

考虑如何获得一个 $1$ 。显然，若一段区间的 $\gcd$ 不为 $1$ ，那么这个区间中无论如何都不能处理出 $1$ 。因此，我们可以合并一个区间获得 $1$ ，当且仅当这个区间的 $\gcd$ 为 $1$ 。只要求出最小的这样的区间长度 $l$ 。

合并这样的区间需要 $l-1$ 次操作。合并后恰好得到一个 $1$ ，于是还需要花费 $n-1$ 次操作。

于是，该题的答案就很显然了。

$$ans=\begin{cases}n-c & c\neq 0 \cr l+n-2 & c=0 \cr -1 &  l \text{不存在}\end{cases}$$

至于寻找最小的 $l$ ，由于 $n\le 2000$ ，于是我们可以暴力计算。这样的复杂度是 $\mathcal O(n^2\log v)$ 。当然，还有一个小优化。当我们固定区间的右端点时，向左移动左端点， $\gcd$ 值只会变化最多 $30$ 次（因为一个数的质因子个数不超过 $30$ ，而每次取 $\gcd$ 要么不变，要么至少删除一个质因子）。而 $\gcd(a,b)=a$ 等价于 $a | b$ ，可以直接判断；否则暴力取 $\gcd(a,b)$ 。这样的复杂度是 $\mathcal O(n^2+n \log v)$ 。

## 参考代码

```
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN =2e3+3;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int n,A[MAXN],c,t=INF;
int main(){
	n=qread(); up(1,n,i) A[i]=qread();
	up(1,n,i){
		int s=A[i];
		dn(i,1,j){
			if(A[j]%s==0) continue; s=__gcd(s,A[j]);
			if(s==1){t=min(t,i-j+1);break;}
		}
		if(A[i]==1) ++c;
	}
    if(c) printf("%d\n",n-c); else
    if(t!=INF) printf("%d\n",n+t-2); else
    printf("-1");
    return 0;
}
```


---

## 作者：Kaizyn (赞：1)

首先特判-1

就是把所有数gcd,结果不为1

---

再看要把全部变为1

我的想法是凑出一个1

然后用这个1去gcd剩下的数,传递到所有的

凑法就是 区间dp的思想

用f[i][j]表示区间[i,j]所有数的gcd

因为gcd有~~什么鬼东西~~传递性

转移方程就是把[i,j]分成任意两段[i,k],[k+1,j]

f[i][j] = gcd(f[i,k], f[k+1,j])

假如我们按长度开始转移

那么我们找到第一个f[i][j]==1的就是最短的

为什么要找最短的区间,~~显然~~这样步数最少

当f[i][j]==1, 长度len=j-i+1,我们可以这样做

把[i,j]从左到右一直将gcd赋到右边,共需要len-1步

这样j就是1,再一直赋值到右边,右边有n-j个

再把j的1一直传递到最左边,有j-1个

所以答案就是len-1+n-j+j-1 = **n+len-2**

需要注意的是我的蒟丑代码因为没有特判一开始就有1的情况(即长度为1)

然后WA了最后一个点,情急之下写了特判,很丑,嗯很丑,~~不仅代码丑,解析也很丑~~

特判就是记录一开始1的个数,步数就是剩下不是1的个数

---

```cpp
#include <bits/stdc++.h>

using namespace std;

const int Maxn = 2e3+7;

int n;
int f[Maxn][Maxn];

int main()
{
    scanf("%d", &n);
    int num1 = 0;
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &f[i][i]);
        num1 += (f[i][i] == 1);
    }
    if(num1)
    {
        printf("%d\n", n-num1);
        return 0;
    }
    for(int len = 2; len <= n; ++len)
    {
        for(int l = 1, r; (r=l+len-1) <= n; ++l)
        {
            f[l][r] = __gcd(f[l][r-1], f[r][r]);
            if(f[l][r] == 1)
            {
                printf("%d\n", n+len-2);
                return 0;
            }
        }
    }
    puts("-1");
    return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P8792)


### Solution

显然，如果要让所有的数都变成 $1$，首先 $a$ 数组里就必须能够通过操作出现至少一个 $1$。

所以，如果已经有了 $k$ 个 $1$，我们只需将剩下的 $n-k$ 个数与 $1$ 做 $\text{gcd}$。答案即为 $n-k$。

同时，如果所有数的 $\text{gcd}$ 大于 $1$，说明不可能通过操作产生 $1$，输出 $-1$ 即可。

接下来考虑如何操作出一个 $1$。

可以知道，能够操作出一个 $1$ 的必然是一个满足 $\text{gcd}$ 为 $1$ 的区间。若区间长度为 $len$，则需要 $len-1$ 步。用线段树维护区间 $\text{gcd}$，二分找出最短区间长度。再加上剩下的 $n-1$ 个数，一共 $len_{min}+n-2$ 步。

时间复杂度为 $O(n \log^2n)$。当然，如果用双指针找最短区间，时间复杂度就可以降至 $O(n \log n)$。


------------

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
using namespace std;
const int N=1e5+5;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x*f;
}

int n,tot,a[N],s[N<<2];

int gcd(int a,int b){
	return !b ? a : gcd(b,a%b);
}

#define ls (t<<1)
#define rs (t<<1|1)
#define md ((l+r)>>1)

il void pushup(int t){
	s[t]=gcd(s[ls],s[rs]);
}

void build(int l,int r,int t){
	if(l==r){
		s[t]=a[l];
		return;
	}
	build(l,md,ls),build(md+1,r,rs);
	pushup(t);
} 

int query(int l,int r,int t,int x,int y){
	if(l>=x&&r<=y) return s[t];
	int ans=0;
	if(x<=md) ans=query(l,md,ls,x,y);
	if(y>md) !ans ? ans=query(md+1,r,rs,x,y) : ans=gcd(ans,query(md+1,r,rs,x,y));
	return ans;
}

bool check(int x){
	for(int i=1;i+x-1<=n;++i) if(query(1,n,1,i,i+x-1)==1) return 1;
	return 0;
}

main(){
	n=wrd();
	for(int i=1;i<=n;++i) tot+=(a[i]=wrd())==1;
	if(tot) return printf("%lld",n-tot),0;
	build(1,n,1);
	if(s[1]>1) return puts("-1"),0;
	
	int l=2,r=n,len=n;
	while(l<=r){
		if(check(md)) len=md,r=md-1;
		else l=md+1;
	}
	return printf("%lld",n-1+len-1),0;
}

```

---

## 作者：_Flame_ (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P8792)

## 思路

要将整个数列都变为 $1$，首先一定要有一个位置为 $1$。

于是题目转化成这样，给你一个序列，问替换出一个 $1$ 的最小次数的问题。

然后我们可以发现，因为是相邻两个数变为 $\gcd(x,y)$，所以当一段长度为 $k$ 的区间的 $\text{gcd}$ 为 $1$ 时，这一段区间肯定能在 $k-1$ 内全部变为一，所以我们只用二分一个 $k$，求出最小的 $k$ 即可求解。

注意，当序列里有 $1$ 的时候，输出 $n-cnt$ 即可，其中 $\text{cnt}$ 为 $1$ 的个数，当区间 $\text{gcd}$ 不等于 $1$ 时，无解即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=101000;
const int maxm=110;
const int mod=50;
const int inf=420444186480114514;

int n;
int a[maxn];
int f[maxn];
int pw[maxn],lg[maxn];
bool flag=0;
int ans;
int cnt;

int st[maxn][20];

int gcd(int x,int y){
	x=abs(x),y=abs(y);
	return y?gcd(y,x%y):x;
}

void init(){
	for(int i=1;i<=n;i++){
		st[i][0]=a[i];
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}

int query(int l,int r){
	int k=log2(r-l+1);
	return gcd(st[l][k],st[r-(1<<k)+1][k]);
}

bool check(int x){
	for(int i=1;i+x-1<=n;i++){
		int j=i+x-1;
		if(query(i,j)==1){
			return 1;
		}
	}
	return 0;
}

void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]==1){
			flag=1;
			cnt++;
		}
	}
	if(cnt){
		write(n-cnt);
		return ;
	}
	init();
	if(query(1,n)!=1){
		puts("-1");
		return ;
	}
	int l=1,r=n;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	write(ans+n-2);
	puts("");
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}




```


```

---

## 作者：XL4453 (赞：0)

### 解题思路：

首先判断无解的情况。显然是序列中的所有数都有某一个非一的公因数才会无解，否则一定有解。

然后考虑如何使得整个序列都为 1。假设当前已经有了一个 1，那么直接把这个 1 向两边扩展，经过至多 $n-1$ 次操作得到最终序列，否则考虑如何构造出一个 1，考虑将一整段的数进行操作，其中要求这一整段的数的最大公因数为 1，这样只要找到最短的这样的一段序列就行了。

具体的，枚举左右端点，同时在右端点向右拓展的同时维护当前序列的最大公因数，总复杂度为 $O(n^2logn)$，可以通过 $n\leqslant2000$ 的数据范围。

----
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int n,a[2005],l,r,now,tot,ans=2147483647;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]==1)tot++;
		now=gcd(now,a[i]);
	}
	if(tot!=0){
		printf("%d",n-tot);
		return 0;
	}
	if(now!=1){
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		now=0;
		now=a[i];
		for(int j=i+1;j<=n;j++){
			now=gcd(now,a[j]);
			if(now==1){
				ans=min(ans,j-i);
				break;
			}
		}
	}
	printf("%d",ans+n-1);
	return 0;
}
```


---

## 作者：happybob (赞：0)

考虑一种特殊情况：即原序列 $a$ 中存在一个 $1$，例如 $a=[3,4,5,6,1]$，显然最优的是把 $1$ 和相邻的进行操作，只需要 $n-1$ 次即可。

若有多个 $1$，令 $c = \sum \limits_{i=1}^n [a_i==1]$，即 $1$ 的个数，那么答案为 $n-c$。

但是若没有 $1$ 呢，我们肯定先尽可能凑出 $1$，显然当一个区间 $l, r$ 使得 $\gcd(a_l, a_{l+1}, \cdots, a_r) = 1$，那么我们只需要花 $r-l$ 次即可凑出 $1$。然后再花 $n-1$ 次即可。

所以题目即需要最小化 $r-l$ 使得 $\gcd(a_l, a_{l+1}, \cdots, a_r) = 1$。

本题数据范围小，可以接受 $O(n^2)$ 以上的做法，但同时可以考虑固定 $l$，显然随着 $r$ 增大的同时，$\gcd$ 的值单调不增，所以可以考虑二分 $r$，线段树/ST表维护区间 $\gcd$。时间复杂度是两只 $\log$。

当然也可以双指针维护，只有一只 $\log$。

注意特判 $0$。


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 1e5 + 5;

int n, a[N];

int gcd(int x, int y)
{
	return (y == 0 ? x : gcd(y, x % y));
}

class SegmentTree
{
public:
	struct Node
	{
		int l, r, GCD;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].GCD = gcd(tr[u << 1].GCD, tr[u << 1 | 1].GCD);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 0 };
		if (l == r)
		{
			tr[u].GCD = a[l];
			return;
		}
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	int query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].GCD;
		int mid = tr[u].l + tr[u].r >> 1, res = -1;
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid)
		{
			if (res != -1) res = gcd(res, query(u << 1 | 1, l, r));
			else res = query(u << 1 | 1, l, r);
		}
		return res;
	}
}t;

int main()
{
	int ans = 0, p = -1, flag = 0, cnt = 0;
	scanf("%d", &n);
	bool fff = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if (a[i] == 1) flag = 1;
		if (p == -1) p = a[i];
		else
		{
			p = gcd(p, a[i]);
		}
		if (a[i] != 1) fff = 1;
		cnt += a[i] == 1;
	}
	if (!fff) printf("0\n");
	else if (p != 1) printf("-1\n");
	else if (flag) printf("%d\n", n - cnt);
	else
	{
		t.build(1, 1, n);
		int ans = (int)2e9;
		for (int i = 1; i <= n; i++)
		{
			int l = i + 1, r = n;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (t.query(1, i, mid) == 1)
				{
					ans = min(ans, mid - i);
					r = mid - 1;
				}
				else l = mid + 1;
			}
		}
		printf("%d\n", ans + n - 1);
	}
	return 0;
}
```


---

## 作者：DerrickLo (赞：0)

### 思路：
我们分三种情况讨论：

$1.$ 如果原来的序列中有 $1$ 时，我们可以将所有的 $1$ 中的其中一个 $1$ 与它相邻的非 $1$ 得数进行一次操作，因为 $\gcd(1,k)=1$，所以每次都进行这样的一次操作就能使整个序列的数全变为 $1$。

$2.$ 如果原来的序列所有数有大于 $1$ 的公约数，我们无论进行多少次操作都只能使它们变成它们的最大公约数而不可能变为 $1$，因此这种情况我们输出 $-1$。

$3.$ 原序列既没有 $1$，所有数的最大公约数也为 $1$ 时，我们可以枚举每一个区间 $[l,r]$ 如果这个区间的公约数为 $1$ 时还需要 $n-1$ 次操作才能使全序列变为 $1$，那我们求出这些操作数中的最大值即可。
 ## code:
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2005],k,kk,ans=INT_MAX;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==1)k++;
		if(i==1)kk=a[i];
		else kk=__gcd(kk,a[i]);
	}
	if(k){//特判有1的情况
		cout<<n-k;
		return 0;
	}
	if(kk!=1){//特判所有数的最大公约数不为1的情况
		cout<<-1;
		return 0;
	}
	for(int i=1;i<n;i++){
		int g=a[i],st=0;
		for(int j=i+1;j<=n;j++){
			st++;//计算步数
			g=__gcd(g,a[j]);
			if(g==1){//如果最大公约数已经是1
				ans=min(ans,st+n-1);//求最小值
				break;
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

