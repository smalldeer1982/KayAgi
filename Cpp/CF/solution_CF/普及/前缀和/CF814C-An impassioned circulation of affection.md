# An impassioned circulation of affection

## 题目描述

Nadeko's birthday is approaching! As she decorated the room for the party, a long garland of Dianthus-shaped paper pieces was placed on a prominent part of the wall. Brother Koyomi will like it!

Still unsatisfied with the garland, Nadeko decided to polish it again. The garland has $ n $ pieces numbered from $ 1 $ to $ n $ from left to right, and the $ i $ -th piece has a colour $ s_{i} $ , denoted by a lowercase English letter. Nadeko will repaint at most $ m $ of the pieces to give each of them an arbitrary new colour (still denoted by a lowercase English letter). After this work, she finds out all subsegments of the garland containing pieces of only colour $ c $ — Brother Koyomi's favourite one, and takes the length of the longest among them to be the Koyomity of the garland.

For instance, let's say the garland is represented by "kooomo", and Brother Koyomi's favourite colour is "o". Among all subsegments containing pieces of "o" only, "ooo" is the longest, with a length of $ 3 $ . Thus the Koyomity of this garland equals $ 3 $ .

But problem arises as Nadeko is unsure about Brother Koyomi's favourite colour, and has swaying ideas on the amount of work to do. She has $ q $ plans on this, each of which can be expressed as a pair of an integer $ m_{i} $ and a lowercase letter $ c_{i} $ , meanings of which are explained above. You are to find out the maximum Koyomity achievable after repainting the garland according to each plan.

## 说明/提示

In the first sample, there are three plans:

- In the first plan, at most $ 1 $ piece can be repainted. Repainting the "y" piece to become "o" results in "kooomi", whose Koyomity of $ 3 $ is the best achievable;
- In the second plan, at most $ 4 $ pieces can be repainted, and "oooooo" results in a Koyomity of $ 6 $ ;
- In the third plan, at most $ 4 $ pieces can be repainted, and "mmmmmi" and "kmmmmm" both result in a Koyomity of $ 5 $ .

## 样例 #1

### 输入

```
6
koyomi
3
1 o
4 o
4 m
```

### 输出

```
3
6
5
```

## 样例 #2

### 输入

```
15
yamatonadeshiko
10
1 a
2 a
3 a
4 a
5 a
1 b
2 b
3 b
4 b
5 b
```

### 输出

```
3
4
5
7
8
1
2
3
4
5
```

## 样例 #3

### 输入

```
10
aaaaaaaaaa
2
10 b
10 z
```

### 输出

```
10
10
```

# 题解

## 作者：Luo_gu_ykc (赞：4)

### 思路	
字符串子串里不等于字符 $ c $ 的字符数量要小于等于 $m$ , 然后再通过双指针来求出一个最长并符合条件的字符串子串
      
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, q, m;
char c;
string s;
int main(){
  cin >> n >> s >> q;
  while(q--){
    cin >> m >> c;
	int maxi = 0, sum = 0; 
	for(int i = 0, j = i; i < n; i++){ // 双指针
	  for(; j < n && sum < m; j++){ 
	    if(s[j] != c){ // 判断
		  sum++;
		}
	  }
	  maxi = max(maxi, j - i); // 特判
	  for(; j < n && s[j] == c; j++){//枚举子串长度
	      if(j - i + 1 > maxi){
	        maxi = j - i + 1; 
	      }
	  }
	  if(s[i] != c){ // 移动左指针时要特判
		sum--; 
	  }
	}
    printf("%d\n", maxi);
  }
  return 0;
}


---

## 作者：叶枫 (赞：4)

### $\texttt{思路}$

对于题目中的一个查询$(m,c)$,枚举子区间$[l, r](0<=l<=r<n)$.

若该区间满足其中的非$c$字符个数$x$不超过$m$，则可以将其合法转换为一个长度为$r-l+1$的全$c$子序列，可以使用动态规划以$O(n^2)$的复杂度计算.

总复杂度$O(n^2q)$还是有点不优秀。

所以我们先离线，把$26n$中情况都计算出来，再打表即可。复杂度$O(26n^2+q)$。

### 代码
$\color{white}\text{自己想吧}$

---

## 作者：Galex (赞：2)

这题不是小模拟吗？双指针？不存在的。

首先我们先算一下所有可能的答案数：$1500 \times 26 = 39000$，远小于 $q$ 的 $200000$。所以很明显我们是要预处理。

那么怎么预处理呢？

我们可以枚举所有的区间，然后枚举每个字母 $c$，算出它需要至少修改多少个字符才能全部变成 $c$，并更新答案。

这样就可以预处理出所有答案，可是时间复杂度为 $O(n^3 \times 26)$，过不了。

考虑优化一下。

首先枚举区间的前两重循环是雷打不动的，但是算出它需要修改多少个字符可以用 **前缀和** 优化的。

那么时间复杂度就降到 $O(n^2 \times 26)$ 了，顺利解决。

最后特判一下如果 $ans[i][j]$ 没有被赋值过，那么显然它修改完所有的字母变成 $j$ 后还有剩余的修改次数，那么它只需把剩下的次数都把 $c$ 改成 $c$ ，直接输出 $n$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		f = (ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

char readc(){
	char ch = getchar();
	while (ch < 'a' || ch > 'z')
		ch = getchar();
	return ch;
}

int n;

int ans[1505][26];
int s[1505][26];

signed main() {
	n = read();
	for (int i = 1; i <= n; i++){
		for (int j = 0; j < 26; j++)
			s[i][j] = s[i - 1][j];
		s[i][readc() - 'a']++;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j + i - 1 <= n; j++)
			for (int k = 0; k < 26; k++)
				ans[i - (s[j + i - 1][k] - s[j - 1][k])][k] = i;
	int q = read();
	while (q--){
		int x = ans[read()][readc() - 'a'];
		printf("%lld\n", x == 0 ? n : x);
	}
	return 0;
}
```


---

## 作者：Ninelife_Cat (赞：2)

前缀和 + 双指针。

用双指针枚举字符串的子串，如果该子串中非 $c$ 字符的个数不大于 $m$，那就可以把这整段都替换成 $c$，更新答案即可。

子串内非 $c$ 字符的个数即为该子串的长度减去子串中 $c$ 字符的个数，这个可以用前缀和做到 $O(26n)$ 预处理和 $O(1)$ 查询。

总复杂度 $O(nq)$，还是挺暴力的。

核心代码：

```cpp
const int N=2e3+10;
int n,m,x,sum[N][27];
string s;
char ch;
signed main()
{
	cin>>n>>s>>m;s=' '+s;
	for(ri int i=1;i<=n;++i)
	{
		for(ri int j=0;j<26;++j)
			sum[i][j]+=sum[i-1][j];
		++sum[i][s[i]-'a'];
	}//预处理前缀和
	for(ri int i=1;i<=m;++i)
	{
		cin>>x>>ch;ri int l=1,r=1,ans=0;
		while(r<=n)
		{
			while(sum[r][ch-'a']-sum[l-1][ch-'a']+x<r-l+1) ++l;
			ans=max(ans,r-l+1);++r;
		}//双指针操作
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：77777_1031 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF814C)

[更好的阅读体验](https://tsygoon.blog.luogu.org/solution-cf814c)

前言：~~提供三种方法~~

## Part 1 方法一：双指针
对于每个询问，暴力穷举所有可能的区间，看这些区间是否通过修改后能得到连续的相同 $c$。

例如:当前询问 $\text{query(d,m)}$。

判断: $(1,m)$ , $(1,m+1)$ ...... $(1,n)$

 $\qquad(2,m+1)$ ...... $(2,n)$ ......
   
如果 $1 \sim x$ 区间不合法，那么右端点比 $x$ 大的区间肯定也不合法。下一个区间只能 l++。

合法区间的左端点有单调性,可以用双指针解决。

## Part 2 方法二：~~还是~~双指针
还是双指针，但是对每一个询问，先预处理前缀和数组，表示某个字符的个数。

将来可以通过前缀和做减法快速判断某个区间的非 $c$ 字符个数是否已经超过限制。

从而决定双指针是 r++，还是 l++。


## Part 3 方法三：dp
这道题题目询问很多达到 $20$ 万，可以尝试预处理每个询问的答案。

最多有 $26$ 个不同字母，所以很多询问的字母相同，只是能够修改的数目不同。

所以我们可以按照字母分情况处理每个字符，枚举能够修改的数目不同的情况下的答案。$dp$ 解决。

显然，对于特定字符 $k$，要穷举以每个位置 $i$ 结尾，且修改数目为 $j$ 能够获得的最大长度。状态为 $dp(i,j,k)$。

对于位置 $i$，如果字符不等于 $k$，则必然要修改（不修改的话，得到的长度是 $0$，不是最优）。

如果字符等于 $k$，则不用消耗修改。采取顺推的方法：

$dp(i+1,j+1,k)=\max(dp(i+1,j+1,k),dp(i,j,k)+1)$

$i$ 位置不是字符 $k$。

$dp(i+1,j,k)=\max(dp(i+1,j,k),dp(i,j,k)+1)$

$i$ 位置是字符 $k$。

注意上面的状态中，表示肯定以 $i$ 结尾的最优值。我们显然要求一个最大值，所以最后还得扫描一遍。
$dp(i+1,j,k)=\max(dp(i+1,j,k),dp(i,j,k))$

by 2022.3.20 我的第六篇题解。


---

## 作者：dxrS (赞：0)

### Update

2023.1.14 按照管理的要求更改了一下时间复杂度的记法。

***

没有用任何 dp（因为我不会），在此分享一种码量也不是很大的做法。

容易发现答案具有单调性，所以想到二分，对于 `check` 函数，容易想到一种 $O(n)$ 的做法：在 `check(mid)` 的时候，从左到右遍历每个长度为 $mid$ 的子串，如果有非 $c$ 的字符的个数小于等于 $m$，字符个数可以用前缀和维护，那么这个子串就是可行的，那么 `mid` 就是可行的答案。

这个时间复杂度是 $O(qn\log n)$ 的，显然过不去，考虑优化。容易想得到询问的问题最多也就 $26n$ 种，记为 $|s|$，于是可以先把所有的答案初始化一下，就可以过了，时间复杂度 $O(|s|\log n+q)$，常数比较小。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,m,s[1505][26],ans[1505][26];
string str;
char c;
inline bool check(int a,int b,int x){
	for(int i=1;i+x-1<=n;++i)
		if(x-(s[i+x-1][b]-s[i-1][b])<=a)
			return 1;
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>str>>q;
	str=' '+str;
	for(int i=1;i<=n;++i)
		for(int j=0;j<26;++j)
			s[i][j]=s[i-1][j]+(str[i]-'a'==j);
	for(int i=1;i<=n;++i)
		for(int j=0;j<26;++j){
			int l=1,r=n;
			while(l<r){
				int mid=l+r+1>>1;
				if(check(i,j,mid))
					l=mid;
				else
					r=mid-1;
			}
			ans[i][j]=r;
		}
	while(q--){
		cin>>m>>c;
		cout<<ans[m][c-'a']<<endl;
	}
	return 0;
}
```

---

## 作者：Lyccrius (赞：0)

## 双指针

用 $sum$ 维护区间 $(i, j),~0 \le i \le n$ 内非 $c$ 字符出现次数。

对于每一个 $i$：
* 当 $sum$ 等于 $m$ 时，停止右端点更新，此时右端点 $j$ 位于第 $m$ 个非 $c$ 字符之后；
* 若 $s_j = c$，则更新右端点，重复此操作，直到 $s_j \le c$；
* 至此，$(i, j-1)$ 即为以当前 $i$ 为做端点的最长合法区间，更新 $ans$;
* 更新左端点之前，根据 $s_i$ 是否为 $c$ 修改 $sum$。

时间复杂度为 $\mathcal{O}(n^2 q)$。

```
#include <cstdio>
#include <algorithm>

const int maxn = 1500 + 10;

int n;
char s[maxn];
int q;
int m;
char c;

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%d", &q);
    while (q--) {
        scanf("%d %c", &m, &c);
        int sum = 0;
        int ans = 0;
        for (int i = 0, j = i; i < n; i++) {
            for ( ; j < n && sum < m; j++) {
                if (s[j] != c) sum++;
            }
            while (s[j] == c) j++;
            ans = std::max(ans, j - i);
            if (s[i] != c) sum--;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

## 前缀和+双指针

与前面做法类似，通过维护前缀和的方式，实现快速获取 `sum` 的大小，免去每次询问计算过程。

时间复杂度为 $\mathcal{O}(n q)$。

```
#include <cstdio>
#include <algorithm>

const int maxn = 1500 + 10;

int n;
char s[maxn];
int q;
int m;
char c;

int pre[maxn][30];

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%d", &q);
    for (int i = 0; i < n; i++) {
        for (int j = 'a'; j <= 'z'; j++) pre[i][j - 'a'] = pre[i - 1][j - 'a'];
        pre[i][s[i] - 'a']++;
    }
    while (q--) {
        scanf("%d %c", &m, &c);
        int ans = 0;
        for (int i = 0, j = i; j < n; j++) {
            while ((j - i + 1) - (pre[j][c - 'a'] - pre[i - 1][c - 'a']) > m) i++;
            ans = std::max(ans, j - i + 1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：lnwhl (赞：0)

题解区似乎都是用的 $O(nq)$ 或 $O(n\log n q)$ 的算法，蒟蒻不知道怎么过的（至少我[过不了](https://codeforces.com/contest/814/submission/150211111)），因此写一篇复杂度正确的做法。
## 题目大意
给你一个由小写字母构成的字符串.  
有 $q$ 个询问,每个询问给出数字 $m$ 和小写字母 $c$ ,你可以任意地修改字符串中的 $m$ 个字符,求最多能够使字符串中含有多少个连续相同的字母 $c$。
## 思路
用双指针枚举字符串的子串，如果该子串中非 $c$ 字符的个数小于等于 $m$，那就可以把这整段都替换成 $c$，更新答案。

易知子串内非 $c$ 字符的个数即为该子串的长度减去子串中 $c$ 字符的个数，这个可以用**前缀和**做到 $O(26n)$ 预处理和 $O(1)$ 查询。总复杂度 $O(nq)$，还是比较容易的。

但这似乎并不足以通过本题，会在 #21 TLE（本文开头的提交记录）。但不难发现虽然有很多的 $q$，但有实际意义的并不多，很多询问都是重复的，所以我们可以记忆化一下，把答案存起来，如果询问以前出现过，就直接输出答案即可。总的复杂度 $O(26n^2 + q)$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,sum[1505][30],f[1505][30];
string s;
int main()
{
	cin>>n;cin>>s;cin>>q;
	s=' '+s;
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<26;++j)sum[i][j]+=sum[i-1][j];
		++sum[i][s[i]-'a'];
	}
	while(q--)
	{
		int m;char c;cin>>m>>c;
		if(f[m][c-'a'])
		{
			cout<<f[m][c-'a']<<endl;
			continue;
		}
		int l=1,r=1,ans=0;
		while(r<=n)
		{
			while(sum[r][c-'a']-sum[l-1][c-'a']+m<r-l+1)
				++l;
			if(r-l+1>ans)ans=r-l+1;
			++r;
		}
		f[m][c-'a']=ans;
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：cbyybccbyybc (赞：0)

这道题大毒瘤..
## 题意
最多改动$m$个字符，使连续的相同字母的长度最长。

显然，假设选中的区间是$[l,r]$，那么最好的情况是$l->r$中，不同的字符只有小于等于$m$个，那么这个区间即为可选的，长度为$r-l+1$。

我们发现，长度越长，越难用$m$次实现，这是成单调性的，因此可以用二分法。

## Soluntion

二分答案，用前缀和维护改动字母的个数，查询时间为$O(1)$，二分满足情况的长度，$check$里只要判断长度为$mid$下，需要改动字母数量最少是多少，如果少于等于$m_i$则通过，继续往大的试($l=mid+1$)反之往小的试($r=mid-1$)。最后输出$mid$即为长度。

$check$部分：暴力枚举$O(n)$
```cpp
int check(int mid,int x,char ch)
{
	for(int i=1;i<=n;i++)
	{
		int kk=mid-sum[i+mid][ch-'a']+sum[i][ch-'a'];
		if(kk<=x)return 1;
	}
	return 0;
}
```
二分：$O(logn)$
```cpp
int l=x,r=n;
while(l<=r)
{
	int mid=(l+r)>>1;
	if(check(mid,x,ch)) l=mid+1;
	else r=mid-1;
}
	
```
最后一层```for i 1->q```:$O(q)$

一共$O(nlogn\times q)$

可以卡过去((

---

## 作者：fletmer (赞：0)

# 很暴力的想法，二分长度，判断是否可行（计算区间中需要修改的字母数），下面是裸的二分答案-----二分答案+记忆化（使用前缀和O（1）查询区间需修改字母数-----尺取法）

## 裸的二分答案TLE一半

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;

const int SIZE=1505;

int n,m,num;
char str[SIZE],rp[5];

inline int rin(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

inline bool chek(int x){;
	int cnt=0;
	for(int i=1;i<=n-x+1;i++){
		cnt=0;
		for(int j=i;j<=i+x-1;j++){
			if(str[j]!=rp[1]) ++cnt;
		}
		if(cnt<=num) return true;
	}
	return false;
}

int main(){
	n=rin(),scanf("%s",str+1),m=rin();
	
	for(int i=1;i<=m;i++){
		num=rin(),scanf("%s",rp+1);
		int l=0,r=n+1;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(chek(mid)) l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	
	return 0;
}
```

## 二分答案+记忆化，TLE 1个点

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;

const int SIZE=1505;

int n,m,num;
char str[SIZE],rp[5];
int pos[SIZE][30],temp[SIZE];

inline int rin(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

inline bool chek(int x){;
	for(int i=1;i<=n-x+1;i++)
		if(x-(temp[i+x-1]-temp[i-1])<=num) return true;
	return false;
}

int main(){
	n=rin(),scanf("%s",str+1),m=rin();
	for(int i=1;i<=n;i++) pos[i][str[i]-'a']++;
	
	for(int i=1;i<=m;i++){
		memset(temp,0,sizeof(temp));
		num=rin(),scanf("%s",rp+1);
		for(int j=1;j<=n;j++){
			int chara=rp[1]-'a';
			temp[j]=temp[j-1]+pos[j][chara];
		}
		
		int l=0,r=n+1;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(chek(mid)) l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	
	return 0;
}
```


## 尺取法AC
```cpp
#include<bits/stdc++.h>
#define N 2009
using namespace std;
 
char s[N];
 
int main()
{
    int n, m, q;
    char ch;
    scanf("%d", &n);
    getchar();
    gets(s);
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d %c", &m, &ch);
        int l, r; l = r = 0;
        for(int i = 0; i < n; i++)
        {
            if(m <= 0 && s[i] != ch) break;
            if(s[i] != ch) m--;
            r++;
        }
        int ans = r - l;
        for(int i = r; i < n; i++)
        {
            if(s[i] != ch)
            {
                ans = max(ans, i - l);
                while(s[l] == ch) l++;
                l++;
            }
        }
        ans = max(ans, n - l);
        printf("%d\n", ans);
    }
    return 0;
}
```

---

