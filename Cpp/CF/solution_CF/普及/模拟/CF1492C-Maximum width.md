# Maximum width

## 题目描述

Your classmate, whom you do not like because he is boring, but whom you respect for his intellect, has two strings: $ s $ of length $ n $ and $ t $ of length $ m $ .

A sequence $ p_1, p_2, \ldots, p_m $ , where $ 1 \leq p_1 < p_2 < \ldots < p_m \leq n $ , is called beautiful, if $ s_{p_i} = t_i $ for all $ i $ from $ 1 $ to $ m $ . The width of a sequence is defined as $ \max\limits_{1 \le i < m} \left(p_{i + 1} - p_i\right) $ .

Please help your classmate to identify the beautiful sequence with the maximum width. Your classmate promised you that for the given strings $ s $ and $ t $ there is at least one beautiful sequence.

## 说明/提示

In the first example there are two beautiful sequences of width $ 3 $ : they are $ \{1, 2, 5\} $ and $ \{1, 4, 5\} $ .

In the second example the beautiful sequence with the maximum width is $ \{1, 5\} $ .

In the third example there is exactly one beautiful sequence — it is $ \{1, 2, 3, 4, 5\} $ .

In the fourth example there is exactly one beautiful sequence — it is $ \{1, 2\} $ .

## 样例 #1

### 输入

```
5 3
abbbc
abc```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2
aaaaa
aa```

### 输出

```
4```

## 样例 #3

### 输入

```
5 5
abcdf
abcdf```

### 输出

```
1```

## 样例 #4

### 输入

```
2 2
ab
ab```

### 输出

```
1```

# 题解

## 作者：HC20050615 (赞：4)

# 翻译
给两个字符串 $s$ 和 $t$，长度分别为 $n$ 和$m$，保证 $t$ 为 $s$ 的一个子串（可以不连续）。

你需要找到一个 $s$ 的子串，使其与 $t$ 相同。你要使这个字串中所有相邻两个字符的距离的最大值最大，求这个最大值。
# 题意分析
我们知道，每一个字符所在的位置都有很多种情况，我们要让距离最大值最大，就一定要让这两个距离最大的字符尽量往两边靠，前一个字符要在它能取得的第一个位置上，第二个字符要在它能取得的最后一个位置上。

因此，我们用两边，一次从前往后搜，用于统计能取得的第一个位置，一次从后往前搜；用于统计最后一个位置。然后对于任意两个相邻的数，用后一个数的最后一个位置减去前一个书的第一个位置就可以了。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
string s,t;
int first[200001];
int last[200001];
int maxs;
int main()
{
	cin>>n>>m;
	cin>>s>>t;
	s=" "+s;
	t=" "+t;
	for(int i=1,j=0;i<=m;i++)
	{
		while(s[++j]!=t[i]);
		first[i]=j;
	}
	for(int i=m,j=n+1;i>=1;i--)
	{
		while(s[--j]!=t[i]);
		last[i]=j;
	}
	for(int i=1;i<=m-1;i++)
	{
		maxs=max(maxs,last[i+1]-first[i]);
	}
	cout<<maxs<<endl;
	return 0;
}
```


---

## 作者：超级玛丽王子 (赞：3)

## 题意简述
给定两个由小写英文字母组成的字符串 $s$ 和 $t$，保证 $t$ 中的每一个字符都在 $s$ 中出现过至少一次。定义 $p_i$ 为任意一个使得 $s_{p_i}=t_i$ 成立的值，求 $p_{i+1}-p_i$ 的最大值。

## 解法描述
如果要让 $p_{i+1}-p_i$ 最大，就需要 $p_{i+1}$ 尽量大，而 $p_i$ 尽量小。故我们可以对 $t$ 中的每一个字符找出其在 $s$ 中最先出现和最后出现的位置 $fst_{t_i}$ 和 $last_{t_i}$，最后计算 $\max\limits_{1\le i \le m-1} \{last_{t_{i+1}}-fst_{t_i}\}$ 即可。

~~数组名字真优秀 怪不得赛场上差点直接 FST~~
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int last[N],fst[N],n,m,stp,cur,mx;
char s[N],t[N],ch;
int main(void) {
	scanf("%d %d %s %s",&n,&m,s,t);
	for(int i=0;i<n&&stp<m;++i) 
		if(s[i]==t[stp]) fst[stp++]=i;
	stp=m-1;
	for(int i=n-1;~i&&stp;--i) 
		if(s[i]==t[stp]) last[stp--]=i;
	for(int i=1;i<m;++i) {
		cur=last[i]-fst[i-1];
		if(cur>mx) mx=cur;
	}
	printf("%d", mx);
	return 0;
}
```

---

## 作者：白鲟 (赞：2)

## 前言
代码没压行，很短。感觉比较优雅。

## 题目分析
由于只需要让最大间隔最大，考虑枚举 $t$ 中每两个相邻的字符使其在 $s$ 中对应位置距离尽量大。

设两个相邻的位置为 $i$ 与 $i-1$，易知使 $i-1$ 对应的位置尽量靠前，$i$ 对应的位置尽量靠后即可使得其对应位置距离尽量大。每个位置对应位置的最小值和最大值可贪心地各一遍 $\operatorname{O}(n)$ 遍历解决。

## 代码
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=2e5;
int n,m,ans,pos[2][maxn+1];
char a[maxn+1],b[maxn+1];
int main()
{
	scanf("%d%d%s%s",&n,&m,a,b);
	for(int i=0,now=0;i<n&&now<m;++i)
		if(a[i]==b[now])
			pos[0][now++]=i;
	for(int i=n-1,now=m-1;~i&&~now;--i)
		if(a[i]==b[now])
			pos[1][now--]=i;
	for(int i=1;i<m;++i)
		ans=max(pos[1][i]-pos[0][i-1],ans);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：KSToki (赞：2)

纪念 fst 场。
# 题目大意
给定长为 $n$ 的仅含小写字母的串 $s$ 和长为 $m$ 的仅含小写字母的串 $t$，求出一个长为 $m$ 的单调递增的数组 $p$，其中 $s_{p_i}=t_i$，使得 $\max(p_{i+1}-p_i)$ 最大。
# 题目分析
贪心。因为保证了一定有解，求出尽量往前压和尽量往后压应该在的位置的两个数组，枚举断点取最大值即可。借助 `vector` 时间复杂度 $O(n)$。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n,m,now=-1,p[26],ans,a[200001],b[200001];
string s,t;
vector<int>pos[26];
int main()
{
	n=read();
	m=read();
	cin>>s>>t;
	for(R int i=0;i<n;++i)
		pos[s[i]-'a'].push_back(i);
	for(R int i=0;i<m;++i)
	{
		while(pos[t[i]-'a'][p[t[i]-'a']]<=now)
			++p[t[i]-'a'];
		a[i]=now=pos[t[i]-'a'][p[t[i]-'a']];
	}
	for(R int i=0;i<26;++i)
		p[i]=pos[i].size()-1;
	now=n;
	for(R int i=m-1;i>=0;--i)
	{
		while(pos[t[i]-'a'][p[t[i]-'a']]>=now)
			--p[t[i]-'a'];
		b[i]=now=pos[t[i]-'a'][p[t[i]-'a']];
	}
	for(R int i=1;i<m;++i)
		ans=max(ans,b[i]-a[i-1]);
	putint(ans);
	return 0;
}
```


---

## 作者：dalao_see_me (赞：1)

题目大意：给出两个字符串，长度分别为 $n,m$ ，设第二个字符串中的字符在第一个字符串中的出现位置为 $p_1,p_2,...,p_m$ （ $1\le p_1<p_2<...<p_m\le n$ ），求出 $\max_{1\le i<m}(p_{i+1}-p_i)$ 。

我们可以对第二个字符串中的每一个字符从前往后扫、从后往前扫，求出它们最大出现位置 $max$ 数组和最小出现位置 $min$ 数组， $\max_{1\le i<m}(max_{i+1}-min_i)$ 就是答案。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+6;
int n,m,ans;
string a,b;
int mn[N],mx[N];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>a>>b;
	a=" "+a;
	b=" "+b;
	int j=1;
	for(int i=1;i<=n;i++){
		if(a[i]!=b[j])continue;
		mn[j]=i;
		j++;
	}
	j=m;
	for(int i=n;i;i--){
		if(a[i]!=b[j])continue;
		mx[j]=i;
		j--;
	}
	for(int i=1;i<m;i++)
		ans=max(ans,mx[i+1]-mn[i]);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：mot1ve (赞：0)

题意就是求相邻两个字母之间的最大值可以是多少，这种线性距离问题，我们可以考虑双指针或者dp，我们可以记录每个字母在可以完成匹配的前提下最早出现的位置和最晚出现的位置。什么是可以完成匹配的前提下呢，就是按照序列中的顺序一个个来。这样可以确保这个位置一定是合法的。最后相邻两个字母之间的最大值就是后一个字母最晚出现减去前一个字母最早出现。 $O(n)$ 

```
#include<bits/stdc++.h>
using namespace std;
int n,m;
string s,t;
int l[200010],r[200010];
int main()
{
	cin>>n>>m;
	cin>>s>>t;
	for(int i=0,j=0;i<n&&j<m;j++)
	{
		while(s[i]!=t[j]&&i<n) i++;
		l[j]=i;
		i++; 
	}
	for(int i=n-1,j=m-1;i>=0&&j>=0;j--)
	{
		while(s[i]!=t[j]&&i>=0) i--;
		r[j]=i;
		i--; 
	}
	int ans=0; 
	for(int i=0;i<m-1;i++)
	{
		ans=max(ans,r[i+1]-l[i]);
	}
	cout<<ans;
}
```

---

## 作者：registerGen (赞：0)

# Solution

为了产生尽可能大的 $p_{t+1}-p_t$（$t$ 是给定的数），我们需要让其它的 $p_{i+1}-p_i(i\ne t)$ 尽可能小。

具体的，我们记录两个数组：$pre,suf$，$pre_i(1\le i\le m)$ 表示按照题目规则 $t_i$ 在 $s$ 中 **最早** 可能出现的位置，$suf_i$ 同理。那么答案就是 $\max\{suf_{i}-pre_{i-1}\}$。

# Code

```cpp
int n,m;
char s[N+10],t[N+10];
int pre[N+10],suf[N+10];
 
void mian(){
	n=ri(),m=ri();
	scanf("%s%s",s+1,t+1);
	int j=1;
	rep(i,1,m){
		while(j<=n&&s[j]!=t[i])j++;
		pre[i]=j;
		j++;
	}
	j=n;
	per(i,m,1){
		while(j>=1&&s[j]!=t[i])j--;
		suf[i]=j;
		j--;
	}
	int ans=0;
	rep(i,2,m)
		ans=std::max(ans,suf[i]-pre[i-1]);
	printf("%d\n",ans);
}
```

---

## 作者：xuezhe (赞：0)

考虑要使 $p_{i+1}-p_i$ 取得最大值，那么 $i$ 及之前的部分就应该尽量向前靠，$i+1$ 及之后的部分就应该尽量向后靠。

于是对于 $i \in [1,m]$，求出 $f_i$ 表示从前往后扫第一次匹配上第 $i$ 位的位置，$g_i$ 表示从后往前扫第一次匹配上第 $i$ 位的位置，直接贪心匹配就好了。

然后求 $\max_{1 \le i < m} \{ g_{i+1}-f_i \}$ 即为答案。

时间复杂度 $O(n)$。

Code:
```cpp
const int N(200005);
 
int n,m,ltr[N],rtl[N];
char s[N],t[N];
 
void fakemain(){
    Read(n),Read(m);
    Read(s+1);
    Read(t+1);
    for(int i=1,j=0;i<=n;++i)
        if(s[i]==t[j+1]){
            ++j;
            ltr[j]=i;
        }
    for(int i=n,j=m+1;i;--i)
        if(s[i]==t[j-1]){
            --j;
            rtl[j]=i;
        }
    int mx=0;
    for(int i=1;i<m;++i)
        mx=max(mx,rtl[i+1]-ltr[i]);
    Print(mx);
}
```

---

## 作者：_Anchor (赞：0)

# Solution

首先，我们可以求出每个点（在保证最后可以匹配完毕）最前面可以匹配到的位置，记为 $l[i]$。

然后我们还可以求出每个点最后面可以匹配到的位置，记为 $r[i]$

那么实际上我们的任务就是求出最大化的 $r[i+1]-l[i]$，答案也就是 $\max_{i\in [1,n)}(r[i+1]-l[i])$

# Code

那么代码也不难写出

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;bool f=false;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
const int N=2e5+5;
#define ll long long
int t,n,m;
int l[N],r[N],maxn;
char s1[N],s2[N];
int main(){
	read(n),read(m);
	scanf("%s",s1);
	scanf("%s",s2);
	for(int i=m-1,j=n-1;i>=0;i--){
		while(s1[j]!=s2[i]&&j>=0) j--;
		r[i]=j;
		j--;
	}
	for(int i=0,j=0;i<m;i++){
		while(s1[j]!=s2[i]&&j<n) j++;
		l[i]=j;
		j++;
	}
	for(int i=0;i<m-1;i++){
//		cout<<l[i]<<" "<<r[i]<<endl;
		maxn=max(maxn,r[i+1]-l[i]);
	}
	write(maxn);
    return 0;
}
```

---

## 作者：Skies (赞：0)

## 题意

设下面的字符串的每个字符在上面的出现的位置是 $p[i]$

求相邻两个字母的位置差的最大值最大是多少

## 分析

我们正向匹配一次字符串，反向匹配一次，就是求出每个字符最早和最晚出现的位置，然后答案很明显就是  $f[i]-z[i-1]$  
(两个数组分别表示**从头匹配**的位置和从**尾巴匹配**的位置)

#### 为什么呢？

因为对于每一位，我都取**这一位的尽量后面的位置和前一位的尽量前面的位置**，所得到的答案取 max 即可。

说到这里，代码就呼之欲出了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int la,lb;
string a,b;
int z[300000],f[300000];
signed main() {
	cin>>la>>lb>>a>>b;
	int pa=0,pb=0; //这两个变量有点像指针，表示已经匹配好了pa或pb位
	while(pb<lb) {
		for(int i=pa;; i++) {
			if(a[i]==b[pb]) {
				pa=i+1;

				z[pb]=i;
				pb++;
				break;
			}
		}
	}
	//反向匹配
	pa=la-1,pb=lb-1;
	while(pb>=0) {

		for(int i=pa;; i--) {
			if(a[i]==b[pb]) {
				pa=i-1;
				f[pb]=i;
				pb--;
				break;
			}
		}
	}
	int ans=0;
	for(int i=1; i<lb; i++) {
		ans=max(ans,f[i]-z[i-1]);
	}
	cout<<ans;
}
```


---

## 作者：_Clown_ (赞：0)

# 概述
|题号|难度|$AC$时间及记录|
| :----: | :----: | :----: |
|$\texttt{CF1492C}$|$\texttt{洛谷难度:暂无评定}$|[$\texttt{On 2021/02/24}$](https://www.luogu.com.cn/record/47013776)|
# 解析
这是一道简单题。

题意也比较清晰。

不难想到，

众所周知，

我们可以对第二个字符串中的每一个字符从前往后扫，

再从后往前扫。

求出它们最大出现位置 $Mx$ 数组，

以及他们最小出现位置 $Mi$ 数组，

答案就很容易得到了。
# 代码
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
int N,M;
string S,T;
int Array[200001];
int Brray[200001];
int main(void)
{
	BetterIO;
	register int i,j;
	cin>>N>>M;
	cin>>S>>T;
	register int X,Y;
	X=Y=0;
	while(Y<T.size())
	{
		if(S[X]==T[Y])
		{
			Array[Y]=X;
			Y++;
		}
		X++;
	}
	X=N-1;
	Y=M-1;
	while(Y>=0)
	{
		if(S[X]==T[Y])
		{
			Brray[Y]=X;
			Y--;
		}
		X--;
	}
	register int Mx;
	Mx=0;
	for(i=0;i<M;i++)
	{
		Mx=max(Mx,Brray[i+1]-Array[i]);
	}
	cout<<Mx<<endl;
	return 0;
}
```

---

## 作者：cmll02 (赞：0)

先求出一个满足条件的 $p$，但尽量在最右侧选（原因后面说）。

之后 $i$ 从 $1$ 到 $m-1$ 循环，每次把 $p_i$ 变得尽量小。

原因：如果最大值是 $p_{i+1}-p_i$，那就让 $p_{i+1}$ 最大，$p_i$ 最小就行。

至于找最小位置可以记录下每个字母出现的位置进行二分。细节看代码。

```cpp
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
inline int read()
{
    int num=0;char c=getchar();
    while(c<48||c>57)c=getchar();
    while(c>47&&c<58)num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num;
}
inline int max(int a,int b)
{
    return a>b?a:b;
}
char aa[200005],ba[200005];
int a[200005],b[200005];
int c[27][200005];
int t[27];
int pos[200005];
bool cmp(int a,int b)
{
    return a>b;
}
signed main()
{
//  a[0]=2,a[1]=2;
//printf("%d\n",std::lower_bound(a,a+2,2)-a);
    int n=read(),m=read(),cur=n+1;
    scanf("%s\n%s",aa,ba);
    for(int i=1;i<=n;i++)a[i]=aa[i-1]-97;
    for(int i=1;i<=m;i++)b[i]=ba[i-1]-97;
    for(int i=1;i<=n;i++)c[a[i]][t[a[i]]]=i,t[a[i]]++;
    for(int i=m;i>=1;i--)
    {
        int x=std::lower_bound(c[b[i]],c[b[i]]+t[b[i]],cur)-c[b[i]]-1;
      cur=pos[i]=c[b[i]][x];
        //for(int i=1;i<=m;i++)printf("%d ",pos[i]);puts("");
    }
    cur=0;int ans=0;
    for(int i=1;i<m;i++)
    {
        int x=std::upper_bound(c[b[i]],c[b[i]]+t[b[i]],cur)-c[b[i]];
        pos[i]=c[b[i]][x];
        ans=max(ans,pos[i+1]-pos[i]);
        cur=c[b[i]][x];
    }
    printf("%d\n",ans);
}
```

---

