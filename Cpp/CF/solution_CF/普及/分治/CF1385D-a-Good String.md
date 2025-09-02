# a-Good String

## 题目描述

You are given a string $ s[1 \dots n] $ consisting of lowercase Latin letters. It is guaranteed that $ n = 2^k $ for some integer $ k \ge 0 $ .

The string $ s[1 \dots n] $ is called  $ c $ -good if at least one of the following three conditions is satisfied:

- The length of $ s $ is $ 1 $ , and it consists of the character $ c $ (i.e. $ s_1=c $ );
- The length of $ s $ is greater than $ 1 $ , the first half of the string consists of only the character $ c $ (i.e. $ s_1=s_2=\dots=s_{\frac{n}{2}}=c $ ) and the second half of the string (i.e. the string $ s_{\frac{n}{2} + 1}s_{\frac{n}{2}         + 2} \dots s_n $ ) is a  $ (c+1) $ -good string;
- The length of $ s $ is greater than $ 1 $ , the second half of the string consists of only the character $ c $ (i.e. $ s_{\frac{n}{2} + 1}=s_{\frac{n}{2} + 2}=\dots=s_n=c $ ) and the first half of the string (i.e. the string $ s_1s_2 \dots         s_{\frac{n}{2}} $ ) is a  $ (c+1) $ -good string.

For example: "aabc" is 'a'-good, "ffgheeee" is 'e'-good.

In one move, you can choose one index $ i $ from $ 1 $ to $ n $ and replace $ s_i $ with any lowercase Latin letter (any character from 'a' to 'z').

Your task is to find the minimum number of moves required to obtain an 'a'-good string from $ s $ (i.e.  $ c $ -good string for $ c= $ 'a'). It is guaranteed that the answer always exists.

You have to answer $ t $ independent test cases.

Another example of an 'a'-good string is as follows. Consider the string $ s =  $ "cdbbaaaa". It is an 'a'-good string, because:

- the second half of the string ("aaaa") consists of only the character 'a';
- the first half of the string ("cdbb") is 'b'-good string, because: 
  - the second half of the string ("bb") consists of only the character 'b';
  - the first half of the string ("cd") is 'c'-good string, because: 
      - the first half of the string ("c") consists of only the character 'c';
      - the second half of the string ("d") is 'd'-good string.

## 样例 #1

### 输入

```
6
8
bbdcaaaa
8
asdfghjk
8
ceaaaabb
8
bbaaddcc
1
z
2
ac```

### 输出

```
0
7
4
5
1
1```

# 题解

## 作者：Werner_Yin (赞：10)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/13338718.html)

# 题意
定义：字符串```s``` 为一个```c-好串```（c 为一个字符）时，必须满足：

1. 当$|s| = 1$ ，$s = c$

2. 当$|s| > 1$, $s$ 的左半部分为全为 $c$，右半部分为一个 ```(c+1)-好串``` 或者 $s$ 的右半部分为全为 $c$，左半部分为一个 ```(c+1)-好串```

其中 $|s|$ 代表 字符串 $s$ 的长度。

举个例子：当 $s=“cdbbaaaa"$时，$s$ 是一个 ```a-好串```

现在，给你一个字符串 $s$ ( $|s| = 2^k$ ),问最少替换多少个字符，使其为一个 ```a-好串```。

# 思路
我们可以按照题意递归求解。

返回边界 ： 当前串长度为 1

每次将串分成左右两部分，分类讨论，最后取最小值作为答案。

具体见代码。
# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>

#define ll long long
using namespace std;

const int MAXN = 131075;
int n;
char s[MAXN];
// getans 代表将[l,r] 变为一个 c-好串 所需最小改动
int getans(int l,int r,char c){
	if(l==r) return s[l]!=c; // 如果该串已经符合要求，则不需要改动，返回 0
	int tot1 = 0,tot2 = 0;
	int mid = (l+r)>>1;
	for(int i = l;i <= mid;i++) if(s[i]!=c) tot1++;
	for(int i = mid+1;i <= r;i++) if(s[i]!=c) tot2++;
	tot1 += getans(mid+1,r,c+1);
	tot2 += getans(l,mid,c+1);
	return min(tot1,tot2);
// tot1 代表将左区间全变为 c， 右区间变为一个c+1 好串所需最小改动
// tot2 代表将右区间全变为 c， 左区间变为一个c+1 好串所需最小改动
}
int main (){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf("%s",s+1);
		printf("%d\n",getans(1,n,'a'));
	}
}
```

---

## 作者：feecle6418 (赞：2)

我们把一段相同字母组成的区间拿出来，按照从长到短从上往下排列，你会发现这是线段树的一部分！

因此我们建出线段树，考虑两种情况：左边全放一样的，右边从下一个字母开始放；或者右边全放一样的，左边从下一个字母开始放。在线段树建立时，我们给 Build 函数一个返回值，让他返回把这一段改成 c-good string 的最小修改次数，然后每个节点再保存区间中 a~z 各出现了多少次，就能 O(1) 转移。

总复杂度是 $O(26n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[200005];
int n,sum[800005][27];
int Build(int p,int l,int r,int ch){
	if(l==r){
		sum[p][a[l]-'a']=1;
		return ch==a[l]-'a'?0:1;
	}
	int mid=(l+r)/2;
	int lef=Build(p*2,l,mid,ch+1);
	int rht=Build(p*2+1,mid+1,r,ch+1);
	for(int i=0;i<26;i++)sum[p][i]=sum[p*2][i]+sum[p*2+1][i];
	return min(lef+r-mid-sum[p*2+1][ch],rht+mid-l+1-sum[p*2][ch]);
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n>>a+1;
		cout<<Build(1,1,n,0)<<endl;
		for(int i=0;i<=4*n;i++){
			for(int j=0;j<26;j++)sum[i][j]=0;
		}
	}
	return 0;
} 
```

---

## 作者：HoshizoraZ (赞：1)

题目说明 $n$ 是一个 $2$ 的整数次幂，那么就可以使用折半递归的分治思想来解决。

首先，从「好串」的第一个条件看，如果字符串长度仅为 1，那么是否需要修改，取决于这个字符是否达到要求。

判断单个字符是否达到要求，只需要看这个字符是否和字母表中的第 $\left((\log_2 n)+1\right)$ 个小写字母相同。如长度为 8 的字符串中选一个长度为 1 的子串，且这个子串的字符是 `d`，那么它就是「好串」。

第二个步骤，让两段字符合并，并在新串内找出最优答案。

假设总共长度为 8，那么：

- 如果子串为 `dc`，那么不需要修改，因为该串满足「好串」的**条件三**。

- 如果子串为 `cb`，那么 `c` 是满足该层条件的，而 `b` 照此想法需要放到下一层**并且修改为 `d`**，共修改 1 个字符。

- 如果子串为 `cccb`，那么此时有两种决策——
	- 把 `cc` 修改为满足条件的 `bb`，并且把 `cb` 放到下一层递归（由上可知此处需要修改 1 个字符），共修改 3 个字符；
    - 把 `cb` 修改为 `bb`，并且把 `cc` 放到下一层**并且修改为
`cd` 或 `dc`**，共修改 2 个字符。
	- 然后把 3 和 2 取最小值，就可以得到子串内的最优解。
    
还有如果我们在选择使用条件二、条件三方案的时候，还是那样逐个统计需要修改字符的数量，那还是太慢了。

所以若想要快速求出形如「`aaab` 中所有字符变成 `b`」需要修改的字符数量，可以使用二维前缀和。

具体办法就是统计每个字母在各个前缀序列中的出现次数，然后 **子串长度 - 子串包含目标字符的个数** 就是需要修改的字母数量。

时间复杂度为 $O(26\times n+n\log n)$，可以通过。

```cpp
#include <cstdio>
#define INF 1e9
#define eps 1e-6
typedef long long ll;

int t, n;
char s[200010];
int sumc[200010][26];

inline int min(int a, int b){		// 最小值函数
	return a < b ? a : b;
}

int search(int l, int r, int now){	// now 代表层数
	if(l == r){
	// 对于长度为 1 的子串，如果字母不符深度条件，那么就要修改
		if(s[l] == 'a' + now) return 0;
		return 1;
	}
	int mid = (l + r) >> 1;			// 折半
	int lc = (mid - l + 1) - (sumc[mid][now] - sumc[l - 1][now]);
	// 上一行为左半边变为规定字符串时需要修改的字符数，下一行为右半边的
	int rc = (r - mid) - (sumc[r][now] - sumc[mid][now]);
	return min(search(l, mid, now + 1) + rc, search(mid + 1, r, now + 1) + lc);	// 选择更好的方案
}

int main(){

	scanf("%d", &t);
	while(t--){
		scanf("%d%s", &n, s + 1);
		for(int i = 0; i <= 25; i++){	// 统计字符出现次数的前缀和
			sumc[0][i] = 0;
			for(int j = 1; j <= n; j++)
				sumc[j][i] = sumc[j - 1][i] + (s[j] - 'a' == i);
		}
		// 此处和代码前的说明有不同，是以第 0 层开始计数的，不要搞混
		printf("%d\n", search(1, n, 0));
	}

	return 0;
}

```

---

## 作者：y0y68 (赞：1)

## 本题算法：分治


----------

简要题意：

给出 $t$ 个长度为偶数的字符串，要求输出得到良好字符串要修改的字符的最小数量。所谓良好字符串，即字符串平均分成两份，其中一边全是字符 `a`，对于另一边再次二分，但是要求这一边的其中一边全是 `a` 的后一个字符 `b`，然后再次二分，同时字符也依次向后推，直到只剩下一个字符。

解题思路：

将字符串不断二分，一层一层的递归下去，直到分到还剩 $1$ 个字符就判断要不要修改，每层递归需要返回  $\min\{$左边全为当前字符且右边进行递归所需的修改次数 $,$ 右边全为当前字符且左边进行递归所需的修改次数$\}$，最后得到答案。

代码（字符串基本操作不会请执行百度）：

```
#include<bits/stdc++.h>
using namespace std;
int t,n;string s;
int solve(string a,char c){//当前字符串为a，字符为c所需的最少修改次数
	if(a.size()==1)return a[0]!=c;//只剩一个字符的情况
	int k=a.size()>>1;//当前字符串一半的长度
	string l=a.substr(0,k),r=a.substr(k);//截取左半边与右半边字符串
	return min(solve(l,c+1)+k-count(r.begin(),r.end(),c),solve(r,c+1)+k-count(l.begin(),l.end(),c));
	//k-count(r.begin(),r.end(),c)表示右半边全改成字符c所需的修改次数，k-count(l.begin(),l.end(),c)同理
}
int main(){
	for(cin>>t;t;t--){
		cin>>n>>s;cout<<solve(s,'a')<<endl;
	}
	return 0;
}
```

---

## 作者：iMya_nlgau (赞：1)

#### 题目大意

给你一个只包含小写字母的字符串 $s[1\dots n]$，保证存在非负整数 $k$ 使 $n=2^k$。

当以下条件至少有一个成立，我们称字符串 $s[1\dots n]$ 是 $c$ -good string：

- $s$ 的长度为 $1$，且只包含一个字符 $c$。
- $s$ 的长度大于 $1$，前半部分只包含字符 $c$，即 $s_1=s_2=\dots=s_{\frac{n}{2}}=c$，后半部分 $s[\frac{n}{2}+1\dots n]$ 是 $(c+1)$ -good string
- $s$ 的长度大于 $1$，后半部分只包含字符 $c$，即 $s_{\frac{n}{2}+1}=s_{\frac{n}{2}+2}=\dots=s_n=c$，前半部分 $s[1\dots \frac{n}{2}]$ 是 $(c+1)$ -good string

求最少改变多少个字符，使 $s$ 成为一个 $a$ -good string。

#### 思路

要想使 $s$ 成为 $c$ -good string，我们需要选择它的前半部分或后半部分全部改为 $c$，再使另一半成为 $(c+1)$ -good string。按照这个思路直接搜索即可，共产生 $O(n)$ 个分支。

$\text{dfs(l,r,now,cnt)}$ 表示当前在搜索使 $s[l\dots r-1]$ 成为 $now$ -good string，目前需要改变 $cnt$ 个字符。

```cpp
#include<cstdio>
#include<iostream>
const int maxn=131080;
char s[maxn];
int ans=maxn;
void dfs(int l,int r,char now,int cnt){
	if(cnt>=ans) return;  //一个最优性剪枝
	if(r-l==1){  //已经搜到头了，更新答案
		if(s[l]!=now) cnt++;
		ans=cnt;
		return;
	}
	int mid=(l+r)>>1;
	int temp=0;
	for(int i=l;i<mid;i++){
		if(s[i]!=now) temp++;
	}
	dfs(mid,r,now+1,cnt+temp);  //分支一：将前半部分全部改为now
	temp=0;
	for(int i=mid;i<r;i++){
		if(s[i]!=now) temp++;
	}
	dfs(l,mid,now+1,cnt+temp);//分支二：将后半部分全部改为now
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		scanf("%s",s);
		ans=n;
		dfs(0,n,'a',0);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：钓鱼王子 (赞：1)

要求很奇怪，但可以用类似倍增的东西求出。

假设当前长度为 $2^i$，要填的字母是 $c$。

那么这个区间的答案即为前半部分全部填 $c$，后半部分继续划分，，或者上面情况交换前后。

继续划分的部分其实就是那部分的 DP 值，全部填 $c$ 可以用一个前缀和来解决。长度从小到大依次计算即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[200002],ans,b[200002][27],k,len,dp[22][200002],xx;;
char s[200002];
int main(){
	t=read();
	while(t--){
		n=read();
		scanf("%s",s+1);
		for(re int i=1;i<=n;++i)a[i]=s[i]-'a'+1;
		for(re int i=1;i<=n;++i){
			for(re int j=1;j<=26;++j)b[i][j]=b[i-1][j];
			++b[i][a[i]];
		}
		k=n;while(k)++len,k>>=1;
		for(re int i=0;(1<<i)<=n;++i){xx=i;
			for(re int j=1;j<=n;j+=(1<<i)){
				if(i==0)dp[i][j]=(a[j]!=len);
				else{
					dp[i][j]=min(dp[i-1][j]+((1<<i-1)-(b[j+(1<<(i))-1][len]-b[j+(1<<(i-1))-1][len])),dp[i-1][j+(1<<i-1)]+((1<<i-1)-(b[j+(1<<i-1)-1][len]-b[j-1][len])));
				}
			}
			--len;
		}
		printf("%d\n",dp[xx][1]);
	}
}
```


---

## 作者：mot1ve (赞：1)

$ 2^k $，考虑分治。

假设现在要求我们把序列变成 a-good 。

每次都是把这个序列分成两半，要么把前一半全变成 a ，后一半变成 (a+1)-good 。

要么把前一半变成 (a+1)-good，后一半变成 a 。

```
#include<bits/stdc++.h>
using namespace std;
int T;
string str;
int work(int l,int r,char ch)
{
	if(l==r)
	return str[l]!=ch;//不是的话需要1次
	int mid=(l+r)>>1,ans1=0,ans2=0;
	for(int i=l;i<=mid;i++)
	{
		if(str[i]!=ch)
		ans1++;
	}
	for(int i=mid+1;i<=r;i++)
	{
		if(str[i]!=ch)
		ans2++; 
	}
	return min(work(l,mid,ch+1)+ans2,work(mid+1,r,ch+1)+ans1);
}
int main()
{
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n>>str;
		cout<<work(0,n-1,'a')<<endl;
	}
	return 0;
} 

---

## 作者：FutaRimeWoawaSete (赞：0)

CF $1500$ 的DP好题。  
也许并不难，但是出的好。  
在阅读题目过后发现几个性质：  
1.$|s|$为2的整数次方；  
2.有明确的状态转移方式；  
许多对线段树等数据结构比较熟悉的人这里就基本上直接想到正解了。  
我们模仿线段树的方法写DP，由于数列中的数都是小写字母所以我们只用维护当前区间有多少个字符a以及当前区间的所有 $c-好串$即可。  
具体实现时注意一下出口的赋值和DP初始化即可。  
然后不要乱开数组大小，这道题空间有点小紧……  
然后就是根据题意DP转移即可，于是我们一波结束这道题。  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int Len = 131077,Inf = 1e9;
char s[Len];
long long n,m,dp[Len << 2][28],sum[Len << 2][28];
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;} 
void DP(int p,int l,int r)
{
	for(int i = 1 ; i <= 26 ; i ++) sum[p][i] = 0,dp[p][i] = Inf;
	if(l == r)
	{
		sum[p][s[l] - 'a' + 1] = 1;
		for(int i = 1 ; i <= 26 ; i ++) dp[p][i] = 1;
		dp[p][s[l] - 'a' + 1] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	DP(ls(p) , l , mid);
	DP(rs(p) , mid + 1 , r);
	int Llen = mid - l + 1 , Rlen = r - mid;
	for(int i = 1 ; i <= 26 ; i ++)
	{
		sum[p][i] = sum[ls(p)][i] + sum[rs(p)][i];
		dp[p][i] = min(Llen - sum[ls(p)][i] + dp[rs(p)][i + 1] , Rlen - sum[rs(p)][i] + dp[ls(p)][i + 1]); 
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t --)
	{
		scanf("%lld",&n);
		scanf("%s",s + 1);
		DP(1 , 1 , n);
		printf("%lld\n",dp[1][1]);
	}
	
	return 0;
}
```

---

## 作者：JACK_POT (赞：0)

# 递归+二分
### 题意
定义一个字符串是$c-good$（$c$为一个小写字母），当且仅当三种情况

1. 该字符串长度$=1$，且该字符为$c$
2. 该字符串长度$>1$,且前一半字符串每个字符都相同为$c$，后一半字符串为$(c+1)-good$
3. 该字符串长度$>1$,且后一半字符串每个字符都相同为$c$，前一半字符串为$(c+1)-good$

有$t$组数据，每组数据第一行是一个整数，表示字符串的长度，第二行是一个字符串$s$，问至少修改几个字符才能使这个字符串成为$'a'-good(n=2^k,k\in[0,17])$

### 思路
这个$c-good$字符串明显是递归定义的，且每次递归分为左右两种情况，且左右长度相等，情况相似，因此也是一个二分

从字符串起止为$1$到$n$开始递归，一共要递归$k$层，设每一层正确字符$c$为$'a'+k-1$。

如果$st$与$nd$相等，说明正在递归的子串长度为$1$，即定义中的第一种情况，若此时这个字符不为$c$,则操作数$+1$。更新答案，结束递归。

设$mid=(st+nd)/2$,为子串中点。假设是定义中的第二种情况，前一半字符串每个字符都相同为$c$,统计$st$到$mid$不为$c$的字符个数，这些是要变为$c$的，递归并把当前操作数累加

假设是定义中的第三种情况，后一半字符串每个字符都相同为$c$,$mid+1$到$nd$的操作同上

思路还是很清晰的

### 代码
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fr(i,a,b) for(int i=a;i<=b;i++)
#define fo(i,a,b) for(int i=a;i>=b;i--)
#define PII pair<int,int>
#define il inline
int t,n,ans;	
char s[150005];
void dfs(int st,int nd,int k,int sum) {
	//st,nd为起止下标，k为当前深度，sum为当前操作数
	int mid=(st+nd)/2;
	char c=(char)('a'+k-1); 
	if(st==nd) {
		if(s[st]!=c) sum++;//若此时这个字符不为c,则操作数+1
		ans=min(ans,sum);//更新答案
		return;//结束递归
	}
    	//情况一
	int sum1=0,sum2=0;
	fr(i,st,mid) if(s[i]!=c) sum1++;//统计st到mid不为c的字符个数
	dfs(mid+1,nd,k+1,sum+sum1);//继续往下递归
   	//情况二
	fr(i,mid+1,nd) if(s[i]!=c) sum2++;
	dfs(st,mid,k+1,sum+sum2);
   	//情况三
}
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%s",&n,s+1);
		ans=n;
		dfs(1,n,1,0);//一开始从1到n，深度为1，操作数为0
		printf("%d\n",ans);
	}
    return 0;
}

```


---

## 作者：chenxia25 (赞：0)

>### [CF题目页面传送门](https://codeforces.com/contest/1385/problem/D)

>题意紫帆。

做法很显然，考虑DP，设$dp_{l,r,x}$表示子串$s_{l\sim r}$成为$x$-good string所需要的最小操作数。边界：$dp_{l,l,x}=[s_l\neq x]$，目标：$dp_{1,n,\texttt a}$，转移：$dp_{l,r,x}=\min\left(\sum\limits_{i=l}^{\frac{l+r-1}2}[s_i\neq x]+dp_{\frac{l+r-1}2+1,r,x+1},\sum\limits_{i=\frac{l+r-1}2+1}^{r}[s_i\neq x]+dp_{l,\frac{l+r-1}2,x+1}\right)$。

然而这样看起来空间是$\mathrm O\!\left(n^2\log n\right)$的，其实合法的$(l,r)$对只有$\mathrm O(n)$个，跟线段树类似，而且对于每个合法的$(l,r)$都只有一个合法的$x$对应。所以空间复杂度$\mathrm O(n)$，时间复杂度类似归并树，是$\mathrm O\!\left(\sum n\log n\right)$的。然鹅现场我没有考虑到，于是空间开了$\mathrm O(n\log n)$，清空数组的时候也花了这么多。不管了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200000,LET=20;
int n;
char a[N+5];
int dp[N<<2][LET];
int dfs(int l=1,int r=n,int c=0,int p=1){//记忆化搜索 
	if(l==r)return a[l]!='a'+c;
	if(~dp[p][c])return dp[p][c]; 
	int &res=dp[p][c],mid=l+r>>1,sum1=0,sum2=0;
	for(int i=l;i<=mid;i++)sum1+=a[i]!='a'+c;
	for(int i=mid+1;i<=r;i++)sum2+=a[i]!='a'+c;
	res=min(sum1+dfs(mid+1,r,c+1,p<<1|1),sum2+dfs(l,mid,c+1,p<<1));//转移方程 
//	printf("dp[%d][%d][%d]=%d\n",l,r,c,res);
	return res;
}
void mian(){
	cin>>n;
	scanf("%s",a+1);
	for(int i=1;i<=4*n;i++)for(int j=0;j<LET;j++)dp[i][j]=-1;//清空 
	cout<<dfs()<<"\n";
}
int main(){
	int testnum;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

[$\text{题目链接}$](https://codeforces.com/contest/1385/problem/D)

设 $num(l,r,a)$ 表示在字符串中 $l$  到 $r$ 的字符串改变成 字符 $a$ - $good$ 串的最小价值，则根据题意可得

（此处 $a$ 为字符类型的变量）

当 $l=r$ 时，若当前字符为 $a$ ，则值为 $0$，否则为 $1$。（即对应题目中条件1）

否则，值就为以下两种情况的最小值，其中 $mid=(l+r)/2$

1. 把前半部分全设置为 $a$ 的价值 $+num(mid+1,r,a+1)$（即对应题目中条件2）

1. 把后半部分全设置为 $a$ 的价值 $+num(l,mid,a+1)$ （即对应题目中条件3）

也就是采用一个分治来直接求解 $num(1,n,'a')$ 即可。

分析上述的处理过程，时间复杂度为 $\mathcal{O}(NlogN)$

### [$\mathcal{Code}$](https://codeforces.com/contest/1385/submission/87269299)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int T,n;
char ch[2000010];
int num(int l,int r,char a)
{
	if(l==r) {
		if(ch[l]==a) return 0;
		else return 1;
	} 
	int mid=l+r>>1,sum1=0,sum2=0;
	for(int i=l;i<=mid;i++)
		if(ch[i]!=a) sum1++;
	sum1+=num(mid+1,r,a+1);
	for(int i=mid+1;i<=r;i++)
		if(ch[i]!=a) sum2++;
	sum2+=num(l,mid,a+1);
	return min(sum1,sum2);
}
int main()
{scanf("%d",&T);while(T--){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		cin>>ch[i];
	if(n==1) {
		if(ch[1]=='a') puts("0");
		else puts("1");
		continue;
	}
	printf("%d\n",num(1,n,'a'));
}	
}
```


---

## 作者：registerGen (赞：0)

[更好的阅读体验](https://registergen.github.io/post/solution-cf1385d/)

没人写题解？那我就来水一发。

# Solution

考虑分治。对于一个区间 $[l,r]$，设 $mid=\dfrac{l+r}2$，且我们希望这个区间是 $c$ -good 的。

那么我们有两种方案：

1. 让 $s_l\sim s_{mid}$ 全变成 $c$，并让 $s_{mid+1}\sim s_r$ 是 $(c+1)$ -good 的。
2. 让 $s_l\sim s_{mid}$ 是 $(c+1)$ -good 的，并让 $s_{mid+1}\sim s_r$ 全变成 $c$。

设 $\operatorname{work}(l,r,c)$ 为让 $[l,r]$ 是 $c$ -good 的「代价」。显然方案 $1$ 的「代价」为

$$(mid-l+1)-\operatorname{count}(l,mid,c)+\operatorname{work}(mid+1,r,c+1)$$

方案 $2$ 的「代价」为

$$\operatorname{work}(l,mid,c+1)+(r-mid)-\operatorname{count}(mid+1,r,c)$$

其中 $\operatorname{count}(l,r,c)$ 表示 $s_l\sim s_r$ 中 $c$ 的出现次数，可以用前缀和处理。

$\operatorname{work}(1,n,\texttt{a})$ 即为最终答案。

# Code

```cpp
int n,m,a[N+10];
char s[N+10];
int sum[N+10][30];
 
int work(int l,int r,int c)
{
	if(l==r)return !(s[l]-'a'+1==c);
	int mid=(l+r)>>1;
	return std::min(((mid-l+1)-(sum[mid][c]-sum[l-1][c]))+work(mid+1,r,c+1),
			work(l,mid,c+1)+((r-mid)-(sum[r][c]-sum[mid][c])));
}
 
inline void solve()
{
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=26;j++)
		{
			sum[i][j]=sum[i-1][j]+((s[i]-'a'+1)==j);
		}
	printf("%d\n",work(1,n,1));
}
```

---

