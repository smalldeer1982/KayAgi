# Mysterious Crime

## 题目描述

Acingel is a small town. There was only one doctor here — Miss Ada. She was very friendly and nobody has ever said something bad about her, so who could've expected that Ada will be found dead in her house? Mr Gawry, world-famous detective, is appointed to find the criminal. He asked $ m $ neighbours of Ada about clients who have visited her in that unlucky day. Let's number the clients from $ 1 $ to $ n $ . Each neighbour's testimony is a permutation of these numbers, which describes the order in which clients have been seen by the asked neighbour.

However, some facts are very suspicious – how it is that, according to some of given permutations, some client has been seen in the morning, while in others he has been seen in the evening? "In the morning some of neighbours must have been sleeping!" — thinks Gawry — "and in the evening there's been too dark to see somebody's face...". Now he wants to delete some prefix and some suffix (both prefix and suffix can be empty) in each permutation, so that they'll be non-empty and equal to each other after that — some of the potential criminals may disappear, but the testimony won't stand in contradiction to each other.

In how many ways he can do it? Two ways are called different if the remaining common part is different.

## 说明/提示

In the first example, all possible common parts are $ [1] $ , $ [2] $ , $ [3] $ and $ [2, 3] $ .

In the second and third examples, you can only leave common parts of length $ 1 $ .

## 样例 #1

### 输入

```
3 2
1 2 3
2 3 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 6
1 2 3 4 5
2 3 1 4 5
3 4 5 1 2
3 5 4 2 1
2 3 5 4 1
1 2 3 4 5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 2
1 2
2 1
```

### 输出

```
2
```

# 题解

## 作者：skyskyCCC (赞：2)

## 前言。
翻了一下题解区，一个用的是 SA 另一个是找规律（貌似），都感觉很复杂，那么我们就考虑一个简单但是正确的算法：暴力枚举。

为什么它是正确的，显然最大的一个原因是 $n$ 和 $m$ 的取值范围过小，即使枚举也不会进行太大的多重循环，所以显然可以通过本题。但是因为读入量过大，需要加一个快读。
## 分析。
可能有的人开了这道题后第一时间就否定了枚举，因为如果直接枚举，需要枚举的每一个前缀和后缀的方案数达到了 $n^2$ 个，但是实际上我们并不需要枚举这么多。

我们可以发现，我们可以依次确定一个字符，比如说把第一个人的那个字符串进行暴力枚举，将它其中的某一段子串作为目标字符串，然后以这个子串的开头字母为开头，枚举 $m$ 个排列，看看最多能匹配到哪里。如果此次匹配到了第 $x$ 个位置，那么下次就可以直接从 $x+1$ 个位置开始枚举。此时显然从 $1$ 到 $s$ 的子串都满足题意，所以方案数就是 $\left(x+1\right)\times\frac{x}{2}$ 的样子。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
long long n,m,a[15][100005];
long long ans,t[15][100005];
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
int main(){
	read(n);
	read(m);
	for(long long i=1;i<=m;i++){
		for(long long j=1;j<=n;j++){
			read(a[i][j]);
			t[i][a[i][j]]=j;
		}
	}
	for (long long i=1;i<=n;i++){
		long long fangan=1;
		while(fangan<=n-i){
			long long st_str=a[1][i+fangan];
			bool flag=true;
			for (long long j=2;j<=m;j++){
				long long k=t[j][a[1][i]]+fangan;
				if(a[j][k]==st_str){
					continue;
				}
				else flag=false;
			}
			if(flag==false){
				break;
			}
			fangan++;
		}
		i+=(fangan-1);
		ans+=fangan*(fangan+1)/2;
	}
	write(ans);
	return 0;
}
```
## 后记。
洛古交不上去，在原网站上过了，跑了 $300$ 分秒左右，不错，还挺快。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：ZLCT (赞：0)

# CF1043D Mysterious Crime
## 题目翻译
给定 $m$ 个长度为 $n$ 的排列，求给所有排列删去若干前后缀后所有排列都相等的方案数。\
$m\le10$
## 排列？好性质
众所周知，排列具有非常好的性质，并且一般题目给出排列就需要从排列入手。\
具体来说，给定排列可以做到从原来下标 $\rightarrow$ 值的单向映射变成下标 $\leftrightarrow$ 值的双向映射；并且由于每个数字只出现一次，所以确定了一个排列中的一个值作为起点，其余排列的起点也一并确定了。\
接下来我们就用这两条性质做文章。
### 原始暴力想法
首先一个比较原始的想法是枚举左右端点，并在每个排列中都找到左右端点所对应下标，并一一比对是否与原区间的值相等。\
理论上若最终答案比较小，这种方法通过把长度不同的情况跳过的剪枝是可以做到一个比较优秀的期望复杂度的，但是假设所有排列均相同，那么复杂度就会被卡到 $O(n^3m)$。
### 原始的启示
根据上面的暴力，我们不仅意识到暴力不行，还警示了我们枚举每一个合法情况是一定不行的，因为合法情况最多为 $n^2$ 级别。\
于是我们就考虑如何不枚举每一种情况。\
注意到若 $[l,r+1]$ 合法，那么 $[l+1,r+1]$ 与 $[l,r]$ 也一定合法，包括所有左右端点在 $[l,r+1]$ 区间的情况都合法，这使我们转变策略，改成找一段连续区间是否合法，若一个长为 $l$ 的区间合法则对答案贡献 $\frac{l\times(l+1)}{2}$。
### 正解
还记得我们介绍的排列的第一个性质吗？\
我们对于每个排列都记录 $d_j$ 表示值为 $j$ 的下一个值是什么。\
那么我们以第一个排列为基准，假设右端点值为 $r$，那一段连续区间能扩展的充要条件就为所有 $d_r$ 都相等。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[11][112345],d[11][112345],ans;
bool check(int x){
    for(int i=2;i<=m;++i){
        if(d[i][x]!=d[1][x])return 0;
    }
    return 1;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        for(int j=1;j<=n;++j){
            cin>>a[i][j];
            d[i][a[i][j-1]]=a[i][j];
        }
    }
    int i=1,j=1;
    for(;i<=n;++i){
        for(j=i;j<=n;++j){
            if(!check(a[1][j]))break;
        }
        j=min(j,n);
        ans+=(j-i+1)*(j-i+2)/2;
        i=j;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Augury (赞：0)

# CF1043D Mysterious Crime 题解

[CnBlogs 链接](https://www.cnblogs.com/Augury/p/17700570.html)

## 题意

给定 $m$ 个长为 $n$ 的序列，问它们的公共子串的个数。

$n\le 10^5,m\le 10$。

## 已经死掉的做法

一眼广义后缀自动机。建出后缀自动机，然后在 parent tree 上面跑 dfs。正确性会在下面证明。

但是因为广义 SAM 巨大的常数，蒟蒻的代码跑了 1.5s，卡了两天常数卡不过去/kk

下面是蒟蒻的提交

![蒟蒻的提交记录](https://cdn.luogu.com.cn/upload/image_hosting/cw9ydqng.png)

## 正解

将广义 SAM 换成 SA。

首先有一个显然的性质：任何子串不会在单个串中出现两次，因为串全都是排列。

于是我们把所有串前后拼接起来，建出 SA，求出 height 数组。

然后我们考虑如何求出答案。

根据定义，一个子串要同时在所有串中出现，才是公共子串。

所以我们用一个长为 $m$ 窗口在 height 数组上扫，求区间最小值。

现在有两个问题：

1. 不会有一个串在这个窗口中出现了多次，而导致有一个串在窗口没有出现过吗？
   不会。根据上面的性质，如果有一个串的两个后缀同时在这个窗口中出现了，这两个后缀的 LCP 一定为空，对答案没有影响。
2. 会算重吗？
   不会。因为根据上面的性质，任何串都不会出现两次。

于是这道题就做完了。

## 注意事项

1. 如果 $m=1$，要特判，输出 $\frac{n(n+1)}{2}$。
2. No long long see your ancestor!!!

## 代码

```cpp
#include<bits/stdc++.h>
#define cmp(x,y) (lst[x]==lst[y]&&lst[x+b]==lst[y+b])
using namespace std;
inline int read(){
	int ans=0;bool op=0;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')op=1;ch=getchar();}
	while('0'<=ch&&ch<='9'){ans=(ans<<1)+(ans<<3)+(ch^48);ch=getchar();}
	if(op)return -ans;
	return ans;
}
const int maxn=1e6+10;
int n,m;
int len;
int lim,num;
int s[maxn];
int sa[maxn],rk[maxn],ky[maxn],lst[maxn<<1],id[maxn],cnt[maxn];
int hi[maxn];
deque<int>q;
long long ans=0;
signed main(){
	n=read(),m=read();
	if(m==1){
		cout<<((1ll*(n+1)*n)>>1);
		return 0;
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			s[j+(i-1)*n]=read();
		}
	}
	len=n*m,lim=n;
	for(int i=1;i<=len;i++)++cnt[rk[i]=s[i]];
	for(int i=1;i<=lim;i++)cnt[i]+=cnt[i-1];
	for(int i=len;i>=1;i--)sa[cnt[rk[i]]--]=i;
	for(int b=1;b<=len;b<<=1){
		num=0;
		for(int i=len;i>len-b;i--)id[++num]=i;
		for(int i=1;i<=len;i++)if(sa[i]>b)id[++num]=sa[i]-b;
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=len;i++)++cnt[ky[i]=rk[id[i]]];
		for(int i=1;i<=lim;i++)cnt[i]+=cnt[i-1];
		for(int i=len;i>=1;i--)sa[cnt[ky[i]]--]=id[i];
		memcpy(lst+1,rk+1,len*sizeof(int));
		num=0;
		for(int i=1;i<=len;i++)rk[sa[i]]=cmp(sa[i],sa[i-1])?num:++num;
		if(num==len)break;
		lim=num;
	}
	num=0;
	for(int i=1;i<=len;i++){
		if(rk[i]==1)continue;
		if(num)--num;
		while(s[i+num]==s[sa[rk[i]-1]+num])++num;
		hi[rk[i]]=num;
	}
	for(int i=1;i<=len;i++){
		while(!q.empty()&&q.front()<=i-m+1)q.pop_front();
		while(!q.empty()&&hi[q.back()]>=hi[i])q.pop_back();
		q.push_back(i);
		if(i>=m)ans+=hi[q.front()];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：liuyz11 (赞：0)

广告：[这场比赛题解的原地址](https://www.cnblogs.com/nblyz2003/p/9868480.html)

 这题是真的坑，一开始压根没思路，辛亏后来开窍了。

这题是说给你一个m*n(1≤n≤100000, 1≤m≤10)的矩阵，每行都是一个[1,n]的排列。让你每行删掉任意长度的前缀和后缀（也可以不删），使得每行剩下的序列相等。问你方案总数。其实就是有多少个序列是每行都拥有的。（然而我一开始还读了半天题）

然而我一开始读错数据，把n和m的大小读反了，main包似乎也是。然我我一开始想到了暴力+kmp，main想到了搜索。然后我就wa了一次，居然给过样例了，不可思议。

听dalao说好像是什么后缀数组（听都没听说过），然后就想到了一个很……的代码。似乎没几个人和我代码思路一样，除了tourist（然后他T了，掉下了rating榜第一名）

因为每行n个数各自只出现一次，所以说只要用s[a[1][j]].nxt记录第一行每个数字a[1][j]的下一个数字a[1][j + 1]，一个长为l序列s是每行都拥有仅当每行的s[i]都的下一个元素为s[i + 1]（1 <= i < l)。所以用s[a[1][j]].cnt记录下有多少行中a[1][j]的下一个为a[1][j + 1]即s[a[1][j]].nxt。

然后我们找到所有cnt为m - 1即所有行都出现过的相邻的数，但是如果A->B和B->C在后m-1行都出现，那么A，B，C也是一个满足每行拥有的序列。所以我们还要记录所有连续的串的长度（如A->B->C都满足就为3），答案为所有长度*（长度 + 1）/ 2的总和（为什么？这不是小学数学吗。）

还有一个单独的点长度算1，因为单独一个数也算是一个序列，且每行都有。

不过回过头来一看，上面这段话说了什么自己也看不懂，算了凑合凑合，看下代码吧：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define INF 1 << 30
#define MAXN 15
#define MAXM 100005
using namespace std;
typedef long long LL;
typedef pair<int,int> par;

struct node{
    int nxt;
    LL cnt;
}s[MAXM];
int a[MAXN][MAXM];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    rep(i, 1, m)
        rep(j, 1, n) scanf("%d", &a[i][j]);
    rep(i, 1, n - 1){
        s[a[1][i]].nxt = a[1][i + 1];
        s[a[1][i]].cnt = 1;
    }
    rep(i, 2, m)
        rep(j, 1, n - 1)
            if(s[a[i][j]].nxt == a[i][j + 1]) s[a[i][j]].cnt++;
    LL sum = 1, ans = 0;
    rep(i, 1, n - 1){
        if(s[a[1][i]].cnt != m) ans += sum * (sum + 1) / 2, sum = 1;
        else sum++;
    }
    if(sum > 0) ans += sum * (sum + 1) / 2;
    cout << ans << endl;
    return 0;
}
```

---

