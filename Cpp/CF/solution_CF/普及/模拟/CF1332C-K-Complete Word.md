# K-Complete Word

## 题目描述

Word $ s $ of length $ n $ is called $ k $ -complete if

- $ s $ is a palindrome, i.e. $ s_i=s_{n+1-i} $ for all $ 1 \le i \le n $ ;
- $ s $ has a period of $ k $ , i.e. $ s_i=s_{k+i} $ for all $ 1 \le i \le n-k $ .

For example, "abaaba" is a $ 3 $ -complete word, while "abccba" is not.

Bob is given a word $ s $ of length $ n $ consisting of only lowercase Latin letters and an integer $ k $ , such that $ n $ is divisible by $ k $ . He wants to convert $ s $ to any $ k $ -complete word.

To do this Bob can choose some $ i $ ( $ 1 \le i \le n $ ) and replace the letter at position $ i $ with some other lowercase Latin letter.

So now Bob wants to know the minimum number of letters he has to replace to convert $ s $ to any $ k $ -complete word.

Note that Bob can do zero changes if the word $ s $ is already $ k $ -complete.

You are required to answer $ t $ test cases independently.

## 说明/提示

In the first test case, one optimal solution is aaaaaa.

In the second test case, the given word itself is $ k $ -complete.

## 样例 #1

### 输入

```
4
6 2
abaaba
6 3
abaaba
36 9
hippopotomonstrosesquippedaliophobia
21 7
wudixiaoxingxingheclp```

### 输出

```
2
0
23
16```

# 题解

## 作者：一扶苏一 (赞：6)

### Description

- 给定一个长度为 $n$ 的字符串 $s$ 和一个参数 $k$，保证 $k$ 整除 $n$ 并且 $s$ 中只含小写字母。
- 请修改 $s$ 中一些字符，使得修改后的字符串满足是以 $k$ 为循环节长度的回文串。
- 以 $k$ 为循环节指对于所有的 $1 \leq i \leq n - k$，$s_i = s_{i + k}$。
- 求最少的修改次数。
- 多组数据，$n$ 之和不超过 $2 \times 10^5$，$k < n$。

### Solution

设修改后的字符串为 $t$。

首先 $t$ 是回文串，所以 $t_1 = t_{n}$。又因为 $t$ 以 $k$ 为循环节长度，所以 $t_{k} = t_n$。由此得到 $t_1 = t_k$。

类似的可以证明，$t_i = t_{k - i + 1}$，其中 $1 \leq i \leq k$。也即 $t$ 是由 $k$ 个完全相同的小回文串组成的。

不妨设 $k$ 是个偶数，那么对于 $1 \leq i \leq \frac k 2$，要令 $i, i + k, i + 2k \dots$ 以及 $n - i + 1, n - i + 1 +k, n - i + 1 + 2k \dots$ 位置的字母相同。考虑暴力遍历这些位置，找到出现次数最多的字母，将其他字母都改成该字母即可。

对于 $k$ 是奇数的情况，特殊处理一下回文对称轴即可。

时间复杂度 $O(n)$。

### Code

```cpp
const int maxt = 26;
const int maxn = 200005;

int t;
int n, k;
int a[maxt];
char s[maxn];

int main() {
  freopen("1.in", "r", stdin);
  for (qr(t); t; --t) {
    qr(n); qr(k);
    qrs(s + 1);
    int d = n / k * 2, ans = 0, mv;
    for (int i = 1, dk = (k >> 1) + (k & 1); i <= dk; ++i) {
      memset(a, 0, sizeof a);
      mv = 0;
      for (int j = i; j <= n; j += k) if (++a[s[j] - 'a'] > mv) {
        mv = a[s[j] - 'a'];
      }
      for (int j = k - i + 1; j <= n; j += k) if (++a[s[j] - 'a'] > mv) {
        mv = a[s[j] - 'a'];
      }
      ans += d - mv;
    }
    if (k & 1) ans -= (d - mv) >> 1;
    qw(ans, '\n');
  }
  return 0;
}
```



---

## 作者：iMya_nlgau (赞：4)

## CF1332C 【K-Complete Word】

首先，我们研究一下 $k$ -complete串的性质：

- $s_i=s_{n+1-i},$ $1\le i\le n$ ;
- $s_i=s_{k+i},$ $1\le i\le n-k$ ;

由第二条性质可得：$s_i=s_{pk+i},$ $\ p\in N,1\le pk+i\le n$.

在结合第一条性质可得：$s_i=s_{n+1-i}=s_{pk+n+1-i},$ $\ p\in N,1\le pk+n+1-i\le n$.

我们可以画一个字符串来直观地理解一下，这个串中 $n=24,\ k=6$，可以把它分成 $n/k=4$ 段（题目中保证 $k|n$）：

. # @ @ # .$\quad$ . # @ @ # .$\quad$ . # @ @ # .$\quad$ . # @ @ # .

其中用字符 '.' , '#' , '@' 表示的位置的字符一定相同.

程序的实现只需找到这些应该相同的位置，把需要改动的最少数量累加到答案中即可.

具体的细节请看代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=2e5+10;
char s[maxn];
int ch[200];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){     //t组输入
		int n,k,ans=0;
		scanf("%d%d",&n,&k);
		scanf("%s",s);
		for(int i=0;i<=(k-1)>>1;i++){
			for(int j=i;j<n;j+=k){  //找到应该相同的位置
				int q=j-2*i+k-1;
				ch[s[j]]++;
				if(j!=q) ch[s[q]]++;  //统计每个字符出现次数
			}
			int p=0;
			for(int i='a';i<='z';i++){  //全部改为出现最多的字符
				if(ch[i]>p) p=ch[i];
				ch[i]=0;
			}
			if(k&1&&i==k/2) ans+=n/k-p; //k是奇数
			else ans+=n/k*2-p;	//k是偶数
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：lcc17 (赞：2)

## Solution

- 考虑贪心

- 根据性质$1$和性质$2$，显然，字符串的第$i$位和第$k+1-i$位和字符串的第$i+nk$位的字母都要相等。

- 枚举位置，统计这些位置的各个相同字母的个数。

- 显然，循环节个数为n/k,所以字母的总个数为 $ n/k*2 $。

- 然后令ans+=字母总个数-这些相同字母个数的最大值$maxx$。

- 当然，如果正好循环到中间（$i==k+1-i$）的话，字母的总个数为 $n/k$且统计的相同字母个数的最大值为$maxx/2$。

- 令$ans$+=$n/k-maxx/2$。

- 快乐输出

```
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n,k,t,ans[26],maxx,cnt=0;
char c[200001];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		scanf("%s",c+1);cnt=0;
		for(int i=1;i<=k/2+(k&1);i++){
			int l=i,r=k+1-i;maxx=0;
			for(int j=l;j<=n;j+=k) ans[c[j]-'a']++;
			for(int j=r;j<=n;j+=k) ans[c[j]-'a']++;
			for(int j=0;j<=25;j++) maxx=max(maxx,ans[j]);
			if(l==r) cnt+=(n/k)-maxx/2;
			else cnt+=(n/k)*2-maxx;
			for(int j=l;j<=n;j+=k) ans[c[j]-'a']--;
			for(int j=r;j<=n;j+=k) ans[c[j]-'a']--;
		}
		printf("%d\n",cnt);
	}
	return 0;
}
```


---

## 作者：gyh20 (赞：1)

可以发现，只要让特定位置上的字母相等即可（$\bmod k$相等或回文对应），求出出现次数最大值，其他地方全部修改即可。

具体就是，对每一个$\mod k$ 的值开一个桶，然后如果一个点翻转后恰好是另一个点，就合并这两个点所在的桶，实现的时候只需要把自己加入到 $\max(i\bmod k,k-i\bmod k)$（反转的位置）。

具体代码：

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
int t,n,m,mx,ans;
char s[200002];
int v[200002][27];
signed main(){
	t=read();
	while(t--){
		n=read();m=read();
		scanf("%s",s+1);ans=0;
		for(re int j=1;j<=m;++j){
		mx=0;
		for(re int i=j;i<=n;i+=m){
			++v[min(j,m-j+1)][s[i]-'a'];//putchar(s[i]);
		}}
		for(re int j=1;j<=(m+1)/2;++j){
			mx=0;
			for(re int i=0;i<26;++i)mx=max(mx,v[j][i]);
			ans+=mx;
			memset(v[j],0,sizeof(v[j]));
		}
		printf("%d\n",n-ans);
	}
}
```

[广告](https://www.luogu.com.cn/blog/gyh20/post-di-cfat-ti-xie-ji-lie)


---

## 作者：K0stlin (赞：1)

求原字符串改为循环节为k的回文串的最小修改数。

观察到第i个位置的字符必须与所有j%k的j位置的字符相等，还要和n-i+1位置的字符相等，所以把他们全都放进一个并查集。

最后统计同一并查集中最多的字符个数，将他们保留，其他的修改成和他们一样的。

CODE:
```cpp
#include <cstdio>
#include <cstring>
typedef long long ll;
const int N=2e5+10;
int t,n,k,p,q,f[N],w[N],l[N],ss[N][30],sum[N];
char s[N];
bool vis[N];
inline int read() {
	int x=0,flag=0;char ch=getchar();
	while(ch<'0'||ch>'9'){flag|=(ch=='-');ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return flag?-x:x;
}
inline int ff(int x) {return x==f[x]?x:f[x]=ff(f[x]);}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	t=read();
	while(t--) {
		n=read();k=read();
		scanf("%s",s+1);
		w[0]=0;
		for(int i=1;i<=n;++i) {
			w[i]=0;sum[i]=0;vis[i]=0;
			memset(ss[i],0,sizeof ss[i]);
		}
		for(int i=1;i<=n;++i)//将所有i的队长设为(i-1)%k+1，即把所有i%k相同者放进同一并查集
			f[i]=(i-1)%k+1;//[1,k]的范围
		for(int i=1;i<=n;++i) {//将i与n-i+1位置的字符放进同一并查集
			p=ff(i);q=ff(n-i+1);
			f[p]=q;
		}
		for(int i=1;i<=n;++i)//ss[i][j]表示以i为队长的并查集中第j+1个字母的个数，sum[i]是以i为队长的并查集的大小
			l[i]=ff(i),++ss[l[i]][s[i]-'a'],++sum[l[i]];
		int ans=0;
		for(int i=1;i<=n;++i)//统计每个并查集
			if(!vis[l[i]]) {//每个并查集只统计一次
				vis[l[i]]=1;
				int mi=0;//求字母最多个数
				for(int j=1;j<26;++j)
					if(ss[l[i]][mi]<ss[l[i]][j])
						mi=j;
				ans=ans+sum[l[i]]-ss[l[i]][mi];
			}
		printf("%d\n",ans);
	}
	return 0;
}

```
-完-

---

## 作者：dead_X (赞：1)

## 题意简述
给出一个长度为 $n$ 的字符串和一个正整数 $k(k|n)$

求这个字符串至少需要多少改动多少字符才能成为一个QWQ字符串。

一个QWQ字符串需要满足以下要求:

* $a_{n+1-i}=a_{i}(i\in[1,n])$
* $a_{i-k}=a_{i}(k<i\leq n)$
* $a_{i}=a_{i+k}(1\leq i\leq n-k)$
## 思路简述
显然，我们只需要 $O(n)$ 的复杂度即可通过此题。

所以此题没有必要想烦，我们只需要找出所有必须相同的字符即可。

那么全部搜一遍就行了。
## 代码
```cpp
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;string s;
bool vis[1000003];
int ans=0,n,q,len;
using namespace std;
int ch[503],cnt;
void f(int k)
{
	if(!vis[n-k-1]) cnt++,ch[(int)s[n-k-1]]++,vis[n-k-1]=1,f(n-k-1);
	if(k>=q) if(!vis[k-q]) cnt++,ch[(int)s[k-q]]++,vis[k-q]=1,f(k-q);
	if(k+q<len) if(!vis[k+q]) cnt++,ch[(int)s[k+q]]++,vis[k+q]=1,f(k+q);
}
int main()
{
	int t=read();
	while(t--)
	{
		n=read(),q=read();
		ans=0;
		cin>>s;
		len=s.size();
		for(int i=0; i<len; i++) vis[i]=0;
		for(int i=0; i<len; i++) if(!vis[i]) 
		{
			f(i);
			int Max=0;
			for(int i=50; i<=150; i++) Max=max(Max,ch[i]);
			ans+=cnt-Max;
			 for(int i=50; i<=150; i++) ch[i]=0;
			 cnt=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：George1123 (赞：1)

# 题解-K-Complete Word

## [博客中阅读](https://www.cnblogs.com/Wendigo/p/12611937.html#C)

> [K-Complete Word](https://codeforces.com/contest/1332/problem/C)

> $T$ 组测试数据，给定 $n$ 和 $k$ 满足 $k|n$，给定一个长度为 $n$ 的字符串 $s$，求最少修改 $s$ 的几个字母，使得 $s$ 是回文串并且对于所有 $1\le i\le n-k$，满足 $s_i=s_{i+k}$。

> 数据范围：$1\le t\le 10^5$，$1\le k<n\le 2\times 10^5$，$\sum n\le 2\times 10^5$。 

第二个条件等价于 $s$ 的 $\frac nk$ 个 $k$ 长子段相等；因为 $s$ 是回文的，所以每个 $k$ 长子段也是回文的。

所以对于每个 $1\le i\le \lfloor\frac k2\rfloor$，满足：

$$s_i=s_{k+1-i}=s_{k+i}=s_{k+k+1-i}=\cdots=s_{(\frac nk -1)\cdot k+i}=s_{(\frac nk -1)\cdot k+k+1-i}$$

如果 $k\in \mathbb{odd}$，对于 $i=\frac {k+1}2$ 满足：

$$s_i=s_{k+i}=\cdots=s_{(\frac nk -1)\cdot k+i}$$

**所以把每群相等的字符中出现次数最多的字符留着，把别的字符改成该字符即可。**

**代码：**

```cpp
//Data
const int N=200000;
int n,k;
char s[N+7];
int cnt[30];

//Main
int main(){
	re int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d\n%s",&n,&k,s+1);
		re int ans=0;
		for(re int i=1;i<=k/2;i++){
			memset(cnt,0,sizeof cnt);
			re int tmp=0;
			for(re int j=i;j<=n;j+=k) cnt[s[j]-'a']++,tmp++;
			for(re int j=k+1-i;j<=n;j+=k) cnt[s[j]-'a']++,tmp++;
			re int mx=0;
			for(re int i=1;i<26;i++) if(cnt[i]>cnt[mx]) mx=i;
			ans+=tmp-cnt[mx];
		}
		if(k&1){ //k∈odd
			int i=(k+1)/2;
			memset(cnt,0,sizeof cnt);
			re int tmp=0;
			for(re int j=i;j<=n;j+=k) cnt[s[j]-'a']++,tmp++;
			re int mx=0;
			for(re int i=1;i<26;i++) if(cnt[i]>cnt[mx]) mx=i;
			ans+=tmp-cnt[mx];
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---
**祝大家学习愉快！**

---

## 作者：Pecco (赞：1)

已知$s$是一个周期串，设$s=pp\dots p$（$p$为$s$的子串），则由于$s$是回文串，所以$p$等于它的反转，即$p$是回文串。因此只需要$s$由若干个相同的回文串组成则符合条件。

设$p=c_1c_2\dots c_2c_1$，则有：

$\begin{aligned}s=&\color{red}c_1\color{blue}c_2\color{black}\dots \color{blue}c_2\color{red}c_1\\& \color{red}c_1\color{blue}c_2\color{black}\dots \color{blue}c_2\color{red}c_1\\&\dots \\&\color{red}c_1\color{blue}c_2\color{black}\dots \color{blue}c_2\color{red}c_1\end{aligned}$

我们对于原来的串，统计红色位置上的字符，修改这一部分的代价即为红色字符总数减去出现最多次的字符的出现次数。然后再统计蓝色字符……以此类推。特殊处理一下对称轴。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        string s;
        cin >> n >> k >> s;
        int x = n / k, tot = 0;
        for (int i = 0; i < (k + 1) / 2; ++i)
        {
            int cnt[26] = {0}, m = 0;
            for (int j = 0; j < x; ++j)
                cnt[s[k * j + i] - 'a']++, cnt[s[k * (j + 1) - i - 1] - 'a']++;
            for (int j = 0; j < 26; ++j)
                m = max(m, cnt[j]);
            tot += (x * 2 - m) / (i == k / 2 ? 2 : 1); // 特殊处理对称轴
        }
        cout << tot << endl;
    }
    return 0;
}
```

---

## 作者：songtaoran (赞：0)

注意到题目中要求最终字符串要是个**回文串**，所以只能是这样一个形式：  
$a_1a_2 \dots a_ka_1a_2 \dots a_ka_1a_2 \dots a_k \dots$  
即由 $\frac{n}{k}$ 个**相同的**回文串组成。  
考虑贪心。  
设 $f_{x, i}(x ∈ [97, 122], i ∈ [1, k])$ 表示在这个回文串里的第 $i$ 个字母中 ACSII 值为 $x$ 的字母的个数。  
我们知道，在这个回文串中，$a_i = a_{k - i + 1}$。  
所以一个位置 $a_i(i ∈ (1, \lfloor \frac{k}{2} \rfloor))$ 的贡献就是 $2 \times \frac{n}{k} - \max_{x = 97}^{122} [f_{x, i} + f_{x, k - i + 1}]$。  
对于 $k$ 是奇数的情况单独处理即可。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T, n, k, ans = 0, f[130][200010];
char c[200010];
void init(){
	for(ll i = 97; i <= 122; i++)
		for(ll j = 1; j <= k; j++) f[i][j] = 0;
	for(ll i = 1; i <= n; i++)
		f[c[i]][!(i % k) ? k : i % k]++;
}
void special(){
	if(k & 1){
		ll mx = -9e18;
		for(ll i = 97; i <= 122; i++) mx = max(mx, f[i][k / 2 + 1]);
		ans += (n / k) - mx;
	}
}
void calc(){
	for(ll i = 1; i <= k / 2; i++){
		ll mx = -9e18;
		for(ll j = 97; j <= 122; j++) mx = max(mx, f[j][i] + f[j][k - i + 1]);
		ans += 2 * (n / k) - mx;
	}
}
int main(){
	cin >> T;
	while(T--){
		scanf("%lld %lld", &n, &k);
		scanf("%s", c + 1);
		ans = 0;
		init();
		special();
		calc();
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

