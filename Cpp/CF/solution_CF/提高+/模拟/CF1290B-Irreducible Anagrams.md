# Irreducible Anagrams

## 题目描述

Let's call two strings $ s $ and $ t $ anagrams of each other if it is possible to rearrange symbols in the string $ s $ to get a string, equal to $ t $ .

Let's consider two strings $ s $ and $ t $ which are anagrams of each other. We say that $ t $ is a reducible anagram of $ s $ if there exists an integer $ k \ge 2 $ and $ 2k $ non-empty strings $ s_1, t_1, s_2, t_2, \dots, s_k, t_k $ that satisfy the following conditions:

1. If we write the strings $ s_1, s_2, \dots, s_k $ in order, the resulting string will be equal to $ s $ ;
2. If we write the strings $ t_1, t_2, \dots, t_k $ in order, the resulting string will be equal to $ t $ ;
3. For all integers $ i $ between $ 1 $ and $ k $ inclusive, $ s_i $ and $ t_i $ are anagrams of each other.

If such strings don't exist, then $ t $ is said to be an irreducible anagram of $ s $ . Note that these notions are only defined when $ s $ and $ t $ are anagrams of each other.

For example, consider the string $ s =  $ "gamegame". Then the string $ t =  $ "megamage" is a reducible anagram of $ s $ , we may choose for example $ s_1 =  $ "game", $ s_2 =  $ "gam", $ s_3 =  $ "e" and $ t_1 =  $ "mega", $ t_2 =  $ "mag", $ t_3 =  $ "e":

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290B/c163083e3bbaacf9e28f6fddff5f78534bd4ddb9.png)On the other hand, we can prove that $ t =  $ "memegaga" is an irreducible anagram of $ s $ .

You will be given a string $ s $ and $ q $ queries, represented by two integers $ 1 \le l \le r \le |s| $ (where $ |s| $ is equal to the length of the string $ s $ ). For each query, you should find if the substring of $ s $ formed by characters from the $ l $ -th to the $ r $ -th has at least one irreducible anagram.

## 说明/提示

In the first sample, in the first and third queries, the substring is "a", which has itself as an irreducible anagram since two or more non-empty strings cannot be put together to obtain "a". On the other hand, in the second query, the substring is "aaa", which has no irreducible anagrams: its only anagram is itself, and we may choose $ s_1 =  $ "a", $ s_2 =  $ "aa", $ t_1 =  $ "a", $ t_2 =  $ "aa" to show that it is a reducible anagram.

In the second query of the second sample, the substring is "abb", which has, for example, "bba" as an irreducible anagram.

## 样例 #1

### 输入

```
aaaaa
3
1 1
2 4
5 5```

### 输出

```
Yes
No
Yes```

## 样例 #2

### 输入

```
aabbbbbbc
6
1 2
2 4
2 2
1 9
5 7
3 5```

### 输出

```
No
Yes
Yes
Yes
No
No```

# 题解

## 作者：gyh20 (赞：13)

神仙结论题

第一眼看上去像倍增，但发现对于两个串 $A$ , $B$ , $A+B$是否有合法答案不能由 $A$ 和 $B$ 是否有答案来推出。

考虑一些结论。

$1.$如果 $l=r$ 那么输出 $Yes$ 。

证明略。

$2.$ 如果 $s[l] \neq s[r]$，那么输出 $Yes$。

构造方法如下:

假设 $s[l]=X,s[r]=Y$

那么将所有的 $Y$ 放在最前面，所有的 $X$ 放在最后面是一定合法的。


$3.$ 如果一个字符串包含不同字母数量达到 $3$ 个，那么一定存在一个合法方案。

构造方法如下。

假设串内存在三种字母 $X,Y,Z$ 且 $s[l]=s[r]=X$ （否则满足结论 $2$ ）

那么将所有的 $Y$ 放在最前面，所有的 $Z$ 放在最后面是一定合法的。

如果不符合以上三条结论，输出 $No$ 即可

代码使用前缀和即可(可以使用离线树状数组加速)

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;
int t,n,a[200002][26],m,k,ans,l,r;
char s[200002];
signed main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;++i){
		for(int j=0;j<=25;++j)a[i][j]=a[i-1][j];
		++a[i][s[i]-'a'];
	}
scanf("%d",&t);
while(t--){
	scanf("%d%d",&l,&r);
	if(s[l]!=s[r]||l==r)puts("Yes");
	else{
		int cnt=0;
		for(int i=0;i<=25;++i)if(a[r][i]-a[l-1][i])++cnt;
		if(cnt>2)puts("Yes");
		else puts("No");
	}
}
}

```


---

## 作者：Querainy (赞：8)

我真的只是开个VP啊，然后就遇到了这个B，想了一个小时也没想出来......有被毒瘤到/kk

我们考虑对于一个串$s$，求出它的每个前缀每个字符的出现次数，我们把这个每个字符的出现次数搞成一个数组，这个数组可以看作表示了26维空间中的一个点。

考虑每个前缀的这个点，应该是上一个前缀的点在某一维度上$+1$得到的。所以如果设$s$中各个字符出现次数分别为$a,b,c,...$，那么把每个前缀的点描出来，每个点向上一个前缀的点连线，应该可以构成从$(0,0,0,...)$到$(a,b,c,...)$的一条路径，其中每一步都是向某个正方向走了$1$单位距离。

所以我们的问题变成了，找一条从$(0,0,0,...)$到$(a,b,c,...)$的路径，满足每一步都是向某个正方向走$1$单位距离，并且它和这个串描述的路径不在这两个端点之外的地方相交。

为什么这样做呢?考虑交点的意义，如果两个串描述的路径有一个交点，我们可以以交点作为第一段的结尾，把这两个串分成两段，前一段根据定义是anagram，后一段显然也是anagram，这就说明你找的串是个reducible anagram；同时容易证明一对reducible anagram的分段处也一定是路径的交点。所以找irreducible anagram，等价于找没有交点的路径。

然后我们考虑，如果是在三维或者更高维空间中，绕路应该是很容易并且极可能可行的一件事——因为你在每个切片上都有两个自由度，不可能被逼得无路可走。所以我们可以大胆猜测，当这个空间有至少三个自由度，也就是$a,b,c,...$中至少三个不为$0$时，肯定存在方案。证明的话，可以去看其它题解的构造。

但是在二维空间中，这件事不一定能办。观察样例我们发现，如果开头结尾不同，那我们交换开头结尾，就得到了一个irreducible anagram。那么如果开头结尾相同呢?我们假设开头结尾都是字符a，另一种字符是b。考虑$s$的路径是在这个平面上走了这么一条路 : $(0,0)\rightarrow (1,0)\rightsquigarrow (a-1,b)\rightarrow (a,b)$，然后如果你要构造的话，肯定是走$(0,0)\rightarrow (0,1)\rightsquigarrow (a,b-1)\rightarrow (a,b)$(不然开头结尾就相交了)。然后你发现这两条路径是从不同方向跨过对角线$(0,0)\rightarrow (a,b)$的，那么它们不可能不相交，所以有两种字符并且开头结尾相同时是无解的。

在一维空间中，也就是只有一种字符的情况下，直接特判掉即可。

使用前缀和，复杂度$O((n+m)\Sigma)$。

```cpp
#include<stdio.h>
#include<string.h>

int n,m;
char s[200002];
int pre[200002][26];

int main()
{
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<26;j++)
			pre[i][j]+=pre[i-1][j];
		pre[i][s[i]-'a']++;
	}
	for(int i=1,l,r,cnt;i<=m;i++)
	{
		scanf("%d%d",&l,&r);
		cnt=0;
		for(int j=0;j<26;j++)
			if(pre[r][j]-pre[l-1][j]) cnt++;
		printf(cnt>=3||(cnt==1&&l==r)||(cnt==2&&s[l]!=s[r])?"YES\n":"NO\n");
	}
	return 0;
}
```

---

## 作者：Lucky_Xiang (赞：6)

# 题目

[CF1290B](https://www.luogu.com.cn/problem/CF1290B)

# 思路

首先，如果一个串可以被分割为多个可以被重排的串（下文简称“重排串”），它一定可以被分成两个重排串，因为两个重排串相连还是重排串。因此，我们构造的串只需满足它的任意前缀不是重排串即可。

### 一种字符

如果原串只有一种字符，显然长度为一就有解，否则无解。

### 两种字符

如果原串有且仅有两种字符，容易发现 $\texttt{ababa}$ 无解。假如把这种情况映射到二维平面中，从 A 点开始走到 B 点，向右走表示添加一个 $\texttt{a}$，向上走表示添加一个 $\texttt{b}$，那么构造出的串合法**当且仅当**构造出的路径与图中红线仅在 A、B 两点重合。$\texttt{ababa}$ 所对应的红线把所有路径堵住了，因此无解。所以在这种情况下，有解当且仅当原串首末字母不同。

![](https://cdn.luogu.com.cn/upload/image_hosting/p2omznvx.png)

### 多种字符

可以参考两种字符的情况，把原串映射到高维空间中。但是，在高维空间中仅靠原串的一条路径是无法挡住所有路径的，因此这种情况一定有解。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mn=200010;
char s[mn];
int n,q;
int cnt[mn][30];
int L,R;
int sum;
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<26;j++)cnt[i][j]=cnt[i-1][j];
		cnt[i][s[i]-'a']++;
	}
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%d",&L,&R);
		if(L==R)
		{
			puts("Yes");
			continue;
		}
		sum=0;
		for(int i=0;i<26;i++)if(cnt[R][i]!=cnt[L-1][i])sum++;
		if(sum==1)puts("No");
		else if(sum==2 && s[L]==s[R])puts("No");
		else puts("Yes");
	}
	return 0;
} 
```

---

## 作者：TEoS (赞：2)

某神仙：CF就是结论+简单数据结构


------------
观察样例加以分析，可以发现：

- 区间长度为1时不能分，直接输出Yes
- 区间左右端点字符不同，一定可以找到

交换两个端点，其余部分不变即可，直接输出Yes

- 上面两个情况之外，区间内字符种数超过2，一定可以找到；否则一定找不到

种数超过2的情况，设端点为a，存在两个字符b,c且b在c左边，只要交换b和右端点、交换c和左端点即可，输出Yes

种数不超过2的情况，只有1种字符显然找不到；2种字符的时候，设分别为a,b，端点均为a，任意构造一个端点均为b（有一个为a显然不可行）的字符串s2，设原字符串为s1，那么在当划分区间两个端点均为左端点时s1比s2多1个a，少1个b，而划分区间右端点每向右1位要么数量关系不变，要么s1比s2再多1个a，少1个b，要么反之；由于在右端点处s1比s2再多1个a，少1个b，并且s1和s2的a,b数相等，那么之前一定有s1和s2的a,b数相等的地方，在那里划分就不可行，输出No。

有了以上结论，那么怎么知道区间内字符种类的个数？方法很多，我基本都不会。于是有一个非常暴力的方法，区间查找可以想到线段树，但字符种类在合并时需要对左右区间判重，虽然种类总数不多，但复杂度稍微有点大，可以稍微优化一下。因为我们只要知道种数是否超过2即可，因此对于种数超过2的区间，可以不存储具体种类，也不判重，直接上传即可。在查询的时候记录总共的种类，到3即可直接回溯。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#define lson p<<1
#define rson p<<1|1
using namespace std;
const int N=2e5+100;
struct Seg
{
	int l,r,sum;
	int color[3];
	#define l(i) t[i].l
	#define r(i) t[i].r
	#define sum(i) t[i].sum
}t[N<<2];
int q,now;
int nc[3];
string s;
void build(int p,int l,int r)
{
	l(p)=l,r(p)=r;
	if(l==r)
	{
		t[p].color[sum(p)++]=(int)s[l-1];
		return ;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	if(sum(lson)>2 || sum(rson)>2)
	{
		sum(p)=3;
		return ;
	}
	for(int i=0;i<sum(lson);i++)
		t[p].color[sum(p)++]=t[lson].color[i];
	for(int i=0;i<sum(rson);i++)
	{
		bool pd=1;
		for(int j=0;j<sum(lson);j++)
			if(t[lson].color[j]==t[rson].color[i])
			{
				pd=0;
				break;
			}
		if(pd)
			t[p].color[sum(p)++]=t[rson].color[i];
	}//暴力判重
}
void ask(int p,int l,int r)
{
	if(l<=l(p) && r(p)<=r)
	{
		if(sum(p)>2)
		{
			now=3;
			return ;
		}
		for(int i=0;i<sum(p);i++)
		{
			bool pd=1;
			for(int j=0;j<now;j++)
				if(t[p].color[i]==nc[j])
				{
					pd=0;
					break;
				}
			if(pd)
				nc[now++]=t[p].color[i];
		}//暴力判重
		return ;		
	}
	int mid=(l(p)+r(p))>>1,lsum,rsum;
	if(l<=mid)
		ask(lson,l,r);
	if(now>2)
		return ;
	if(r>mid)
		ask(rson,l,r);
	return ;
}
int main()
{
	cin>>s;scanf("%d",&q);build(1,1,s.size());
	for(int i=1,x,y;i<=q;i++)
	{
		scanf("%d%d",&x,&y);
		if(x==y || s[x-1]!=s[y-1])
		{
			puts("Yes");
			continue;
		}//特判前两种
		now=0;ask(1,x,y);	
		puts(now>2?"Yes":"No");
	}
	return 0;
}
```


---

## 作者：Creeper_l (赞：1)

考虑不合法的情况（不考虑长度为 $1$ 的情况）。

- $l$ 到 $r$ 全部相同。

- $l+1$ 到 $r$ 中只有一种字符和 $a_l$ 不同，且 $a_l \ne a_r$。

	假设这两种字符分别为 $A$ 和 $B$，且 $a_l=A$。那么新构造的字符串的第 $l$ 位就必须是 $B$。这样构造到 $B$ 出现的最后一位时一定无法满足条件了。但是如果 $B$ 出现的最后一位是 $r$ 的话（也就是满足 $a_l \ne a_r$）还是满足条件的，因为这只是神奇串而不是超级神奇串。

其它情况一定可以构造出合法的字符串。

- $r-l+1=1$

	直接复制原字符串即可。

- $l+1$ 到 $r$ 中有两种及以上的字符和 $a_l$ 不同。

	假设有三种字符 $A,B,C$。

	原串为：$\text{aa{\color{Blue}b}aaba{\color{Red}c}a}$

	构造串：$\text{{\color{Red}c}aaaabaa{\color{Blue}b}}$

	构造方式为把 $C$ 的最后一个换到第一个，把 $B$ 的第一个换到最后一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5 + 10;
int sum[30][MAXN];
char a[MAXN];
int l,r,n,q;
signed main()
{
	cin >> (a + 1);
	n = strlen(a + 1);
	for(int i = 1;i <= n;i++)
		for(int j = 0;j < 26;j++)
			sum[j][i] = sum[j][i - 1] + (a[i] == char('a' + j));
	cin >> q;
	while(q--)
	{
		cin >> l >> r;
		if(r - l + 1 == 1){puts("Yes");continue;}
		int p = a[l] - 'a',k = sum[p][r] - sum[p][l],cnt = 0;
		for(int i = 0;i < 26;i++)
			if(i != p && (sum[i][r] - sum[i][l]) > 0) cnt++;
		if(k == r - l || (cnt == 1 && a[l] == a[r])) puts("No");
		else puts("Yes");
	}
	return 0;
}

```


---

