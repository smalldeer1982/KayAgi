# Tokitsukaze and Duel

## 题目描述

“决斗！”

为了可爱的公主 Claris 而下注，Tokitsukaze 与 Quailty 之间的决斗开始了。

有 $n$ 张卡牌排成一行。每张卡牌有两面，其中一面有颜色。起初，这些卡牌中有些是颜色面朝上，有些是颜色面朝下。接下来他们轮流翻转卡牌，Tokitsukaze 先手。每次操作时，必须选择恰好 $k$ 张连续的卡牌，并将它们翻转到同一面，也就是说，要么让这 $k$ 张卡牌的颜色面全部朝上，要么全部朝下。如果在某人的操作后，所有 $n$ 张卡牌的颜色面都朝向同一方向，则该玩家获胜。

公主 Claris 想知道，如果 Tokitsukaze 和 Quailty 都足够聪明，不会犯错，谁会赢得这场游戏。

## 说明/提示

在第一个样例中，无论 Tokitsukaze 如何操作，她操作后都会有三张卡牌颜色面朝同一方向，Quailty 可以将最后一张卡牌翻转到该方向并获胜。

在第二个样例中，无论 Tokitsukaze 如何操作，Quailty 都可以选择相同的卡牌并翻回初始状态，这样游戏可以无限进行，最终平局。

在第三个样例中，Tokitsukaze 可以通过将最左边的五张卡牌全部翻到朝上，或将最右边的五张卡牌全部翻到朝下，从而获胜。

第四个样例的解释与第二个样例相同。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
0101
```

### 输出

```
quailty
```

## 样例 #2

### 输入

```
6 1
010101
```

### 输出

```
once again
```

## 样例 #3

### 输入

```
6 5
010101
```

### 输出

```
tokitsukaze
```

## 样例 #4

### 输入

```
4 1
0011
```

### 输出

```
once again
```

# 题解

## 作者：Kinandra (赞：6)

对于先手(tokitsukaze), 如果他不能在第一回合获胜, 那么后手(quailty)至少存在一种方案使得先手不能获胜.


具体的, 若后手一步就能获胜, 那么就走这步; 否则, 后手可以**重复先手的操作**, 局面不变, 让先手面临这个不能一步获胜的局面.

同理可得, 在先手不能一步获胜的情况下, 如果后手不能在他(她?)的第一次操作获胜, 则必定平局.

那么考虑判断**先手是否能一步获胜**, 和**是否无论先手如何操作, 后手都可以获胜**.

对于位置$i$, 定义$l_i$为一个最靠左的位置, 使得$[l_i,i]$所有的字符(牌)相同, 相似的定义$r_i$.

枚举先手选择的区间$[L, R](R=L+k-1)$，如果$l_{L-1}=1$(或$L=1$)且$r_{R+1}=n$(或$R=n$)且$s_{L-1}=s_{R+1}$(或$L=1$或$R=n$), 那么先手就可以必胜.

考虑判断后手是否获胜: 同样枚举先手选择的区间$[L,R]$, 如果存在一个区间不满足$l_{L-1}=1$(或$L=1$)且$r_{R+1}=n$(或$R=n$)， 那么后手必定不可获胜， 否则$s_{L-1}\neq s_{R+1}$且$L\neq 1$且$R\neq n$(先手不能获胜), 所以要保证两边的未被选择的区间长度都要小于$k$后手才能获胜.


```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int read();
int n, k;
char s[100005];
int l[100005], r[100005];

void init() {
    l[1] = 1, r[n] = n;
    for (int i = 2; i <= n; ++i) l[i] = s[i] == s[i - 1] ? l[i - 1] : i;
    for (int i = n - 1; i; --i) r[i] = s[i] == s[i + 1] ? r[i + 1] : i;
}

bool ch1() {
    if (n == k || l[n - k] == 1 || r[k + 1] == n) return 1;
    for (int i = 2; i <= n - k; ++i)
        if (s[i - 1] == s[i + k] && l[i - 1] == 1 && r[i + k] == n) return 1;
    return 0;
}

bool ch2() {
    if (k * 2 < n) return 0;
    for (int i = 2; i <= n - k; ++i) {
        if (l[i - 1] != 1 || r[i + k] != n) return 0;
    }
    return 1;
}

int main() {
    n = read(), k = read();
    scanf("%s", s + 1);
    init();
    if (ch1()) return puts("tokitsukaze"), 0;
    if (ch2()) return puts("quailty"), 0;
    puts("once again");
    return 0;
}
int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```



---

## 作者：rizynvu (赞：3)

[我的博客](https://www.cnblogs.com/rizynvu/p/18546824)。

考虑到两人对应的操作是相同的，于是可以从对称的角度来思考。

考虑到在先手做出操作后，后手一个较为特殊的操作是不做任何影响，也就是重复先手的操作。  
能够发现如果对于后手这不能必胜，那么他一定不会去产生影响，并又把这个局面留给先手，相当于是先后手的交换。  
对于先手又是同样的，因为两人操作相同，对于他也是不必胜的，那么他也会重复操作留给后手，那么就平局了。

于是能够知道的是，如果初始状态就能必胜，那么先手必胜。  
否则如果无论先手怎样操作，后手都能必胜的话，后手必胜。   
否则就是先手存在一种方式，使得操作后后手不能必胜，那么两人就会一直重复第一次的操作，最终平局。

对于判断，可以提前预处理好前缀同色段的长度与后缀连续段的长度。  

那么对于先手，其选择了段 $[l, r]$，那么他就只关心 $[1, l], [r, n]$ 是否同色。  
对于后手，先手选择了段 $[l, r]$ 涂成了颜色 $c$，那么只有当 $[1, l], [r, n]$ 只有一边需要重新涂色且最远颜色距离 $\le k$ 即可。

时间复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
constexpr int maxn = 1e5 + 10;
int n, k;
char s[maxn];
bool f[maxn], g[maxn];
int fmn[maxn][2], fmx[maxn][2], gmn[maxn][2], gmx[maxn][2];
int main() {
   scanf("%d%d%s", &n, &k, s + 1);
   f[0] = true;
   for (int i = 1; i <= n; i++) {
      f[i] = f[i - 1] && (s[i] == s[1]);
   }
   g[n + 1] = true;
   for (int i = n; i; i--) {
      g[i] = g[i + 1] && (s[i] == s[n]);
   }
   if (f[n - k] || g[k + 1]) {
      return puts("tokitsukaze"), 0;
   }
   for (int l = 1, r = k; r <= n; l++, r++) {
      if (f[l - 1] && g[r + 1] && s[1] == s[n]) {
         return puts("tokitsukaze"), 0;
      }
   }
   fmn[0][0] = fmn[0][1] = n + 1;
   for (int i = 1; i <= n; i++) {
      for (int op : {0, 1}) {
         fmn[i][op] = fmn[i - 1][op], fmx[i][op] = fmx[i - 1][op];
      }
      fmn[i][s[i] - '0'] = std::max(fmn[i][s[i] - '0'], i);
      fmx[i][s[i] - '0'] = i;
   }
   gmx[n + 1][0] = gmx[n + 1][1] = 0;
   for (int i = n; i; i--) {
      for (int op : {0, 1}) {
         gmn[i][op] = fmn[i + 1][op], gmx[i][op] = gmx[i + 1][op];
      }
      gmx[i][s[i] - '0'] = std::max(gmx[i][s[i] - '0'], i);
      gmn[i][s[i] - '0'] = i;
   }
   bool fl = true;
   for (int l = 1, r = k; r <= n; l++, r++) {
      for (char c : {'0', '1'}) {
         bool gl = l > 1 && (! f[l - 1] || c != s[1]);
         bool gr = r < n && (! g[r + 1] || c != s[n]);
         if ((gl && gr) || (gl && fmx[l - 1][c ^ '1'] - fmn[l - 1][c ^ '1'] + 1 > k) || 
                           (gr && gmx[r + 1][c ^ '1'] - gmn[r + 1][c ^ '1'] + 1 > k)) {
            fl = false;
            break;
         }
      }
   }
   puts(fl ? "quailty" : "once again");
   return 0;
}
```

---

## 作者：樱雪喵 (赞：2)

详细讲一下如何判定后手能否获胜。

此题的关键点在于**可以重复上一个人的操作**使局面保持不变。

考虑先手的获胜条件，由上一段可知若先手不能在第一步获胜，则后手一定可以重复先手的操作，使其回到原来的局面，从而保证自己不败。

考虑后手的获胜条件，与先手同理，若后手不能一步致胜，先手同样可以重复后手的操作。

综上所述，**当且仅当其中一人能够一步致胜时，才能获得胜利**。

----

### 先手

若先手一步致胜，则需保证**所选区间以外的数字全部相同**。

对于串中的位置 $i$，维护 $l_i$，$r_i$ 分别表示其左边及右边在字符相同时的最远位置。

枚举所选长度为 $k$ 的区间为 $[i,j]$，当 $l_i=1$，$r_j=n$ 且 $a_{i-1}=a_{j+1}$ 时，满足区间外的所有数字相同，可以获胜。

### 后手

后手获胜，需要保证**先手做出任何选择都能使后手一步致胜**。

设先手选择的区间为 $[i,j]$。把当前局面分成三部分，分别为 $[1,i-1]$，$[i,j]$，$[j+1,n]$。后手想要获胜，必须使左右两区间的所有值都与 $[i,j]$ 的值相等。而在一次操作中，后手只能操作其中的一个区间。也就是说，需要保证其中的一个区间值全部与 $[i,j]$ 相等。

当 $n>2k$ 时，$[1,i-1]$ 和 $[j+1,n]$ 必然有一个长度大于 $k$。此时后手无法获胜。

这时候我们会发现一个问题，假设 $[1,i-1]$ 的值全为 $0$，且 $[j+1,n]$ 中不全是同一个值，那么先手只要把 $[i,j]$ 全部变为 $1$，后手还是无法胜利。因此要保证无论先手填的值是什么，都有其中一个区间与之全部相等，就需要左右两个区间一个全是 $0$，一个全是 $1$。

因此，若存在 $[i,j]$ 不满足 $l_{i - 1} = 1$ 且 $r_{j+1} = n$，后手无法获胜。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,k,a[N];
int l[N],r[N];
char s[N];
int main()
{
	scanf("%d%d%s",&n,&k,s+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='0') a[i]=0;
		else a[i]=1;
	}
	l[1]=1;l[0]=1;
	for(int i=2;i<=n;i++)
	{
		if(a[i]==a[i-1]) l[i]=l[i-1];
		else l[i]=i;
	}
	r[n]=n;r[n+1]=n;
	for(int i=n-1;i;i--)
	{
		if(a[i]==a[i+1]) r[i]=r[i+1];
		else r[i]=i;
	}
	if(n==k||l[n-k]==1||r[k+1]==n) return printf("tokitsukaze"),0;
	for(int i=1;i<=n-k+1;i++)
	{
		int j=i+k-1;
		if(l[i-1]==1&&r[j+1]==n&&a[i-1]==a[j+1])
		{
			cout<<"tokitsukaze"<<endl;
			return 0;
		}
	}
	if(n>2*k)
	{
		cout<<"once again"<<endl;
		return 0;
	}
	bool flag=0;
	for(int i=2;i<=n-k;i++)
	{
		int j=i+k-1;
		if(l[i-1]!=1||r[j+1]!=n)
		{
			cout<<"once again"<<endl;
			return 0;
		}
	}
	cout<<"quailty"<<endl;
	return 0;
}
```


---

## 作者：LJ07 (赞：1)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/CF1190C)
## 思路简述

来一篇似乎不太一样的题解。

+ 如果先（后）手能赢，那么一定是第一步就赢，因为另外一个人可以跟他**反复拉扯**。
+ 那么显然我们可以先判断出第一个人能不能第一步能不能达成目标。
+ 如果不能，再判断第二个人能不能达成目标。**暴力枚举**第一个人填涂的是哪个区间，填成 $0$ 还是 $1$，然后去判断第二个人能不能达成目标。
+ 如何 $O(1)$ 判断？不妨设第一个人填涂的是 $[l,l+k-1]$ 这段区间。贪心地，我们可以认为第二个人目标是区间全部填成与第一个人填的相同的数字。那么我们进行以下的判断：

	- 如果 $[1,l]$ 和 $[l+k,n]$ 都有需要填涂的部分，那么寄。
   - 如果 $[1,l]$ 有需要填涂的部分，但是最左边和最右边的距离大于等于 $k$，那么寄。
   - 如果 $[l+k,n]$ 有需要填涂的部分，但是最左边和最右边的距离大于等于 $k$，那么寄。

+ 当且仅当上述情况都没有出现，那么后手赢。维护最左边和最右边需要填涂的位置可以使用序列自动机。

+ 如果先手和后手都不能赢，那么是平局。

## 丑陋の代码
[click here](https://www.luogu.com.cn/paste/zjqs5vea)

---

## 作者：activeO (赞：1)

## 题目大意

[题面](https://www.luogu.com.cn/problem/CF1190C)说得很清楚了，这里就不细说了。

## 思路

同学推荐做，一道不错的思维题。

然后很容易就能发现**如果先手不能第一步就取胜的话，后手一定至少能重复先手的操作**，这样至少都是平局。所以就能知道如果先手要获胜，唯一就是除了所选区间以外，别的数都相同。

接着考虑那种情况后手获胜：一个~~类似废话的~~结论**如果先手操作哪个区间后手都能取胜，后手就能取胜**。如果开始时先手选择操作区间 $ [l,r] $，那么此时整个序列划分为三段 $ [1,l-1] $，$ [l,r] $，$ [r+1,n] $。而后手最多只能操作一个区间，所以要满足除区间 $ [l,r] $ 外一个区间字符都与 $ [l,r] $ 相同，然后另一个区间需要修改的长度要在 $ k $ 以内，此时后手才能获胜。

实现其实就是枚举先手操作的区间就行了，具体看代码。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn=1e5+5;
int l[maxn],r[maxn];
char ch[maxn];

int main(){
	
	int n,k;
	
	scanf("%d %d %s",&n,&k,ch+1);
	
	l[0]=1;
	for(int i=1;i<=n;i++){
		if(ch[i]==ch[i-1]) l[i]=l[i-1];
		else l[i]=i;
	}
	r[n+1]=n;
	for(int i=n;i>=1;i--){
		if(ch[i]==ch[i+1]) r[i]=r[i+1];
		else r[i]=i;
	}
	
	if(r[1]==n){
		puts("tokitsukaze");//已经全部相同
		return 0;
	}
	
	int res=0;
	
	for(int i=1,j=k;j<=n;j++,i++){
		if(l[i-1]==1&&r[j+1]==n){//除了枚举的区间以外都是相同字符
			if(i==1||j==n||(ch[i-1]==ch[j+1])){//两边区间字符是同一个
				puts("tokitsukaze");//判先手获胜
				return 0;
			}else{
				if(i-1<=k&&n-j<=k) res++;//后手操作范围内
			}
		}else if(i==1){
			if(n-j<=k) res++;
		}else if(j==n){
			if(i-1<=k) res++;
		}
	}
	
	if(res==n-k+1) puts("quailty");//后手获胜
	else puts("once again");
	
	return 0;
}
```


---

## 作者：xukuan (赞：1)

博弈论

首先我们可以发现，如果第一轮没有结束，那么结果就是once again。因为接下来双方可以无限复制对方之前的招数来取得僵局。

那么我们来看什么样的局面会取得非平局

先手胜的局面很好考虑，主要是后手胜的局面

满足条件：

- 先手赢不了
- $2k \ge n$
- $k \ne 1$

解释：如果$k=1$，而且先手赢不了，那么先手会把局面原封不动的还给后手，后手同理也赢不了

- 有一个长度为k的字串，左右两边的两串相同

我们可以判断是否存在一种方案，使先手可以控死后手

总的来说，就是先tokitsukaze，再quailty，最后once again。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,m,sum,L[100010],R[100010];
char s[100010];

int main(){
	scanf("%lld %lld %s",&n,&m,s+1);
	L[0]=1;
	for(ll i=1; i<=n; i++){
		if(s[i]==s[i-1]) L[i]=L[i-1];
		else L[i]=i;
	}
	R[n+1]=n;
	for(ll i=n; i>=1; i--){
		if(s[i]==s[i+1]) R[i]=R[i+1];
		else R[i]=i;
	}
	if(R[1]==n) return printf("tokitsukaze\n")&0;
    for(ll l=1,r=m; r<=n; l++,r++){
        if(L[l-1]==1&&R[r+1]==n)
            if(l==1||r==n||(s[l-1]==s[r+1])) return printf("tokitsukaze\n")&0;
            else{if(l-1<=m&&n-r<=m) sum++;}
        else if(l==1){if(n-r<=m) sum++;}
		else if(r==n){if(l-1<=m) sum++;}
    }
    if(sum==n-m+1) printf("quailty\n");
    else printf("once again\n");
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

首先很容易发现只有三种可以分出胜负的情况：

+ 本来就已经全部相等了。此时先手必胜。（$1$）
+ 先手走一步就可以胜。（$2$）
+ 不管先手走哪里后手走一步就可以胜。（$3$）

其他情况下必然平局。

首先 $1$，$2$ 两种情况是简单的。直接暴力枚举一下答案区间即可。问题在于 $3$ 情况直接暴力时间复杂度十分的错误，为 $O(n^2)$ 不可通过。考虑优化。对于先手枚举的区间 $[l,r]$，后手必须要让其他元素都和 $[l,r]$ 中的元素相同。容易发现 $[l,r]$ 区间将整体区间分割为了 $[1,l-1]$、$[r+1,n]$ 两个部分。现在后手只能操作两个区间中的一个。因此此时上述两个部分至少有一个部分和 $[l,r]$ 区间中元素相同，另一个可以只通过修改一次一段长度为 $k$ 区间内的元素的操作来让其和区间 $[l,r]$ 的值相同。

显然可以用 ds 如线段树维护一段区间内 $1$ 个数以及最左、最右两个为 $1$ 的位置。但是因为是静态的所以可以直接记录 $L_i$ 表示 $i$ 左边第一个为 $1$ 的位置，$R_i$ 表示 $i$ 右边第一个为 $1$ 的位置。此时修改区间 $[l,r]$ 的值全部为 $1$ 只需要覆盖 $[R_l,L_r]$ 一段区间为 $1$ 即可，也就是判断 $[R_l,L_r]$ 一段区间的长度是否 $\le k$ 即可。将区间全部覆盖为 $0$ 的情况也同理。时间复杂度为 $O(n)$，十分好写。

---

## 作者：Hoks (赞：0)

## 前言
比较简单的博弈论题，但是我的复杂度很劣。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
因为把 $1$ 变成 $0$ 和把 $0$ 变成 $1$ 只需要把 $0,1$ 全部翻转一下重新跑一遍就行了，所以下文所有都为将 $0$ 变为 $1$。

先考虑下一步致胜怎么判断。

那么就是找出最左端的 $0$ 和最右端的 $0$，尝试下能不能一步将他们都覆盖了。

接着来考虑一步不能结束游戏的情况。

不难发现从第二步开始，我们都可以浪费步数。

也就是因为第一步走了，肯定有一段连续的 $1$ 是可以反复对这段全部变 $1$ 浪费的。

所以我们不需要考虑走到第三步的情况，如果走到第三步必胜的话后手则会选择浪费这一步，把必败的情况留给先手。

所以如果两步没能分出胜负，就是平局。

接着考虑两步怎么判断。

暴力的让第一步先走了，如果第一步不管怎么走，第二步都能赢，就是后手必胜。

这样暴力判的话是 $O(n^2)$ 的，考虑优化。

发现我们更改第一步的复杂度是 $O(1)$ 的，而计算是否可行是 $O(n)$ 的，考虑平衡复杂度。

因为只需要查询最大值和最小值，考虑使用 set，修改的时候删左边插入右边，查询的时候首尾元素拿出来即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,k,f1,f2;char s[N]; 
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
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
inline bool chk()
{
	int mx=0,mn=n;
	for(int i=1;i<=n;i++)
		if(s[i]=='0') mn=min(mn,i),mx=max(mx,i);
	return mx-mn<k;
} 
inline bool check()
{
	set<int>a;for(int i=k+1;i<=n;i++) if(s[i]=='0') a.insert(i);
	if(*(--a.end())-*a.begin()+1>k) return false;
	for(int i=k+1;i<=n;i++)
	{
		if(s[i]=='0') a.erase(i);
		if(s[i-k]=='0') a.insert(i-k);
		if(*(--a.end())-*a.begin()+1>k) return false;
	}return true;
}
inline void wtf()
{
	int mx=0,mn=n,cnt=0;
	for(int i=1;i<=n;i++) if(s[i]=='0') cnt++;
	if(cnt==n){puts("tokitsukaze");exit(0);}
	if(cnt==0){puts("tokitsukaze");exit(0);}
} 
signed main()
{
	read(),k=read();rd(s,n);wtf();int f=0;
	if(chk()){put("tokitsukaze");goto genshin;}
	if(check()) f=1;
	for(int i=1;i<=n;i++) s[i]^=1;
	if(chk()){put("tokitsukaze");goto genshin;}
	if(check()&&f){put("quailty");goto genshin;}
	put("once again");
	genshin:;flush();return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

分享一个较劣且不好写的做法。

首先我们分析各方的最优策略会是什么。当游戏轮到一方时，如果该方可以一步取胜，其必然选择此方案；如果不能一步取胜，则会尽量让对手不能在下回合取胜。

将最左、最右的 $0$ 的下标记作 $l_0,r_0$，$1$ 同理有 $l_1,r_1$。

在第一回合，若 $k$ 可以覆盖所有 $0$ 或所有 $1$，即 $\min(r_0-l_0+1,r_1-l_1+1)\le k$，则先手可以一步取胜。

否则，先手要寻找方案使后手不能一步取胜。若操作后 $l_0,r_0,l_1,r_1$ 分别变成 $l_0',r_0',l_1',r_1'$，则先手希望找到 $\min(r_0'-l_0'+1,r_1'-l_1'+1)>k$。

若先手没有找到这个方案，后手可以直接一步取胜。

若先手找到了这个方案，后手在下回合也会尽量让先手在之后不能一步取胜，这显然可以通过重复先手的方案来达成。故此时游戏会永远持续下去。

所以游戏只会 $1$ 回合分胜负，或永远持续。所以我们可以通过直接枚举（左端点，填 $0/1$）的方式来寻找第一回合先手的方案。

$l_0',r_0',l_1',r_1'$ 的查找，与所填数相同，可以直接判断；与所填数不同，可以使用 ``set`` 查找。所以这个解法带一个 $\log$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef long double db;
const ll maxn=100007,ee=1000000000000000007ll;
ll n,k,a[maxn],l0,l1,r0,r1,m0,m1;
set<ll> st0,st1;
char t;
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll Tccs=1;
	//cin>>Tccs;
	for(int tcs=1;tcs<=Tccs;tcs++){
		cin>>n>>k; l0=l1=ee,r0=r1=-ee;
		st0.insert(0),st1.insert(0),st0.insert(n+1),st1.insert(n+1);
		for(int i=1;i<=n;i++) cin>>t,a[i]=t-'0';
		for(ll i=1;i<=n;i++){
			if(a[i]) l1=min(l1,i),r1=max(r1,i),st1.insert(i);
			else l0=min(l0,i),r0=max(r0,i),st0.insert(i);
		}
		m0=r0-l0+1,m1=r1-l1+1;
		if(l0==ee||l1==ee||(min(m0,m1)<=k)) cout<<"tokitsukaze\n",exit(0);
		//cout<<l0<<" "<<r0<<" "<<l1<<" "<<r1<<"\n";
		for(ll i=1,l,r,d0,d1,e0,e1;i<=n-k+1;i++){
			l=i,r=i+k-1;
			d0=max(r0,r)-min(l,l0)+1,d1=max(r1,r)-min(l,l1)+1;
			e0=m0,e1=m1;
			if(r0<=r) e0+=-r0+*prev(st0.lower_bound(l));
			else if(l<=l0) e0+=l0-*st0.upper_bound(r);
			if(r1<=r) e1+=-r1+*prev(st1.lower_bound(l));
			else if(l<=l1) e1+=l1-*st1.upper_bound(r);
			//cout<<l<<" "<<r<<" "<<d0<<" "<<d1<<" "<<e0<<" "<<e1<<"\n";
			if(min(e0,d1)>k||min(e1,d0)>k) cout<<"once again\n",exit(0);
		}
		cout<<"quailty\n";
	}
	return 0;
}
```

---

## 作者：H2O_TX (赞：0)

## 零、题目大意

个人认为已经写的很清楚了，注意是 `Tokitsukaze` 先走。

## 一、解法

考虑游戏结束的情况：后手一直复制先手的操作就可以使游戏无限进行下去，所以先手想赢只能是一步绝杀，而后手想赢则需要无论先手怎么走他都能直接结束游戏。

- 先手能一步绝杀：一段区间左侧和右侧都是统一的一个颜色的时候。

- 后手能赢：在先手不能赢的情况下，$2k\ge n$ 且任意一段区间左侧颜色统一，右侧颜色也统一。

详细解释下后手能赢的条件：

任取一段区间 $[l_0,r_0]$ 作为先手操作的区间。

当这个区间在两侧的时候就可以直接判断剩下部分长度是否大于 $k$。

其他情况就要判断 $[1,l_0-1]$ 颜色是否一致和 $[r_0+1,n]$ 颜色是否一致，但是这两个区间不一定要颜色相同。具体想一想，满足这个条件的话在先手操作了 $[l_0,r_0]$ 之后这个区间一定会和两侧区间中的任意一个连在一起，这时只需要操作另外一个区间就可以了。

## 二、实现

问题在如何判断一个区间颜色一致，这个也很简单，可以用前缀和也可以用代码中的方法：两个数组 $lmax,rmax$ 分别表示

- 一个位置最多连续相同的颜色能到的最左侧位置

- 一个位置最多连续相同的颜色能到的最右侧位置

然后就可以 $O(1)$ 判断了，总复杂度 $O(n)$。

贴代码（附有少量注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
int n,k;
char a[N];
int lmax[N],rmax[N];

int main()
{
    cin>>n>>k;
    cin>>a+1;
    int nowmax;
    char nowv='!';
    lmax[0]=1;
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=nowv) nowv=a[i],nowmax=i;
        lmax[i]=nowmax;
    }
    nowv='!';
    for(int i=n;i;i--)
    {
        if(a[i]!=nowv) nowv=a[i],nowmax=i;
        rmax[i]=nowmax;
    }
    rmax[n+1]=n;//以上为预处理，对于[0]和[n+1]的赋值是因为不想特判
    for(int l=1;l<=n-k+1;l++)//首先先判一遍先手能不能赢
    {
        int r=l+k-1;
        if(lmax[l-1]==1&&rmax[r+1]==n&&(a[l-1]==a[r+1]||l==1||r==n))//按照题解中的判断来写就好了
        {
            cout<<"tokitsukaze";
            return 0;
        }
    }
    //再来判后手，不过也许可以合并成一个循环，留给读者思考了
    if(k*2<n)
    {
        cout<<"once again";
        return 0;
    }
    for(int l=2;l<=n-k;l++)
    {
        int r=l+k-1;
        if(lmax[l-1]!=1||rmax[r+1]!=n)
        {
            cout<<"once again";
            return 0;
        }
    }
    cout<<"quailty";
    return 0;
}

```


---

## 作者：EuphoricStar (赞：0)

一道不错的博弈论。

## 思路

此题的关键性质在于：**一方可以重复另一方上一次的操作从而使得局面不变。**

因此有结论：**先手必胜当且仅当先手第一步就取胜，后手必胜当且仅当先手无法在第一步就取胜且无论先手如何操作后手都能一步胜利。**

可以这么理解。若先手第一步无法取胜，后手下一步就有取胜策略则执行，否则**后手可以重复先手的操作，使先手面对这个无法一步取胜的局面。** 同理后手若无法在第一步取胜那么先手也可以重复后手的操作。

接下来首先要判断先手能否第一步取胜。只要存在区间 $[i,i+m-1]$ 满足 $i \ge 1,i+m-1 \le n$ 且 $[1,i-1]$ 和 $[i+m,n]$ 的值相同（或者为空）则先手能第一步取胜。实现时前缀和判断即可。

然后判断后手能否第一步取胜。枚举先手第一步选的区间 $[i,i+m-1]$，如果对于每一个 $i$ **均** 满足：

- $[1,i-1]$ 的值都相等
- $[i+m,n]$ 的值都相等且不与 $[1,i-1]$ 的值相等（如果相等就先手必胜了；两个区间内的值都要分别相等是因为后手不能预测先手选的区间，所以两个区间都有需要被染色的可能）
- $[1,i-1]$ 和 $[i+m,n]$ 的区间长度均 $\le m$（这样就保证无论先手将 $[i,i+m-1]$ 染成什么颜色，都可以完整地选出一个区间并染成先手染的颜色）

则后手就能必胜。实现时这部分仍然可以前缀和判断。注意要特判 $i=1$ 和 $i=n-m+1$ 的情况。

## 代码

[code](https://codeforces.com/contest/1190/submission/165115468)

---

