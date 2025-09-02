# Password

## 题目描述

Asterix，Obelix 和他们的临时伙伴 Suffix、Prefix 已经最终找到了和谐寺。然而和谐寺大门紧闭，就连 Obelix 的运气也没好到能打开它。

不久他们发现了一个字符串 $S\ (1\leqslant\vert S\vert\leqslant1000000)$，刻在和谐寺大门下面的岩石上。Asterix 猜想那一定是打开寺庙大门的密码，于是就大声将字符串朗读了出来，然而并没有什么事发生。于是 Asterix 又猜想密码一定是字符串 $S$ 的子串 $T$。

Prefix 认为 $T$ 是 $S$ 的前缀，Suffix 认为 $T$ 是 $S$ 的后缀，Obelix 却认为 $T$ 应该是 $S$ 中的某一部分，也就是说，$T$ 既不是 $S$ 的前缀，也不是 $S$ 的后缀。

Asterix 选择子串 $T$ 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix 选择了最长的一个。当 Asterix 大声读出子串 $T$ 时，寺庙的大门开了。（也就是说，你需要找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串）

现在给你字符串 $S$，你需要找到满足上述要求的子串 $T$。

## 样例 #1

### 输入

```
fixprefixsuffix
```

### 输出

```
fix```

## 样例 #2

### 输入

```
abcdabc
```

### 输出

```
Just a legend```

# 题解

## 作者：MyukiyoMekya (赞：35)

看到题解区一堆 KMP 和 Z 函数的，

可是，**我信仰字符串哈希神教！**

首先可以发现一个性质，对于一个前缀 $T$，如果存在一个不在最左边也不在最右边的子串 $U$，那么一个比 $T$ 短的前缀也一定能找到对应的 $U'$。

所以我们先 $O(n)$ 找出所有合法的前缀 $T$ （有对应的后缀），然后二分就行了，判断是否存在 $U$ 的时候 $O(n)$ 判，总复杂度 $\mathcal O(n\log n)$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ln std::puts("")
#define pb push_back
const int base=233;
const int p=998244353;
const int MaxN=1e6+50;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
char s[MaxN];
int f[MaxN],g[MaxN],n;
inline int calc(int l,int r)
{
	return (f[r]-f[l-1]*g[r-l+1]%p+p)%p;
}
inline bool check(int len,int val)
{
	for(int i=2;i+len-1<n;++i)
		if(val==calc(i,i+len-1))
			return true;
	return false;
}
signed main(void)
{
	std::scanf("%s",s+1),n=std::strlen(s+1);
	g[0]=1;
	for(int i=1;i<=n;++i)
		g[i]=g[i-1]*base%p;
	for(int i=1;i<=n;++i)
		f[i]=(f[i-1]*base%p+s[i])%p;
	std::vector<int> dr;
	for(int i=1;i<=n-2;++i)
		if(calc(1,i)==calc(n-i+1,n))
			dr.pb(i);
	reg int l=0,r=(int)dr.size()-1,ans=0,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(dr[mid],calc(1,dr[mid])))
			ans=dr[mid],l=mid+1;
		else
			r=mid-1;
	}
	if(!ans)
		return std::puts("Just a legend"),0;
	for(int i=1;i<=ans;++i)
		std::putchar(s[i]);ln;
	return 0;
}


```



---

## 作者：Chemist (赞：26)

## 一句话题意：
给你一个字符串S（|S|<=1000000），找到既是S前缀又是S后缀又在S中间出现过（既不是S前缀又不是S后缀）的子串，如果不存在输出“Just a legend”。
## 分析：
我们可以先找到既是S前缀又是S后缀的子串，用KMP求出next数组即可实现。之后我们只需从2枚举到n-1这样可以保证既不是前缀也不是后缀，如果next[i]=next[n]那么就找到了最大的子串。我们还需要预处理一下，在求next数组时记录下max{next[1~n-1]}，那么当next[n]>max时显然不能将next[n]作为最长子串的长度（这样就会无法找到，输出“Just a legend”），所以当x=next[n]>max时，令x=next[x]，直到x<=max，注意如果这时next[x]=0还是无解。
## 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[1000010];
int next[1000010],n,maxx=0;
void cal()//求出next数组
{
    next[1]=0;
    for(int i=2,j=0;i<=n;i++){
        while(j&&a[i]!=a[j+1])j=next[j];
        if(a[i]==a[j+1])j++;
        next[i]=j;
        if(i!=n)maxx=max(next[i],maxx);
        //找到next数组的最大值
    }
}
int main()
{
    cin>>a+1;
    n=strlen(a+1);
    cal();
    int x=next[n];
    if(x==0)printf("Just a legend\n");
    else{
        while(x>maxx)x=next[x];
        //找到小于max{next[1~n-1]}的最大匹配长度
        if(x==0){
        	printf("Just a legend\n");
        	return 0;
		}
        for(int i=2;i<n;i++)
         if(x==next[i]){
            for(int j=i-next[i]+1;j<=i;j++)
         //i-next[i]+1为答案子串的左端点
             printf("%c",a[j]);
            printf("\n");
            return 0;
         }
    }
    return 0;
} 
```

---

## 作者：PrefixAMS (赞：15)

主要思路是利用kmp的nxt数组来计算相等前后缀的长度

找一个**既是S的前缀又是S的后缀同时又在S中间出现过的最长子串**

其实就是找一个从$0$开始的一个子串使得它的$nxt>=nxt[len]$

为什么呢？

因为是从$0$开始,所以这个子串的结尾其实就是要求的中间的那个子串

**为什么是$nxt[i]>=nxt[len]$而不能是小于呢？**

举个栗子

**$abcdeababc$**


它结尾为c但之间会有一个$nxt==2$,但ab并不符合条件,对从开头到$len-1$的字符串进行查询,找出最大的$nxt$,记录下值$MAXN$,再对$k$进行减，直到$k<=MAXN$得出答案

若$k==0$ 则证明没有满足的子串,输出Just a legend


```cpp
#include<bits/stdc++.h>
using namespace std;
char as[10001000];
int k,nxt[10010000];
int main() {
	cin>>as+1;
	int len=strlen(as+1);
	for(int i=2;i<=len;i++) {
		while(k!=0&&as[k+1]!=as[i]) k=nxt[k];
		if(as[k+1]==as[i]) k++;
		nxt[i]=k;
	}
	k=0;
	int maxn=0;
	for(int i=2;i<=len-1;i++) {
		maxn=max(nxt[i],maxn);
	}
	k=nxt[len];	
	while(k>maxn) k=nxt[k];
	if(k) {
		for(int i=1;i<=k;i++) cout<<as[i];
	}
	else cout<<"Just a legend";
	return 0;
}
```

end


---

## 作者：皎月半洒花 (赞：10)

发这个题解只是因为…大多数人的 Z 函数解法复杂度根本不对…

以下是这题用 Z 函数各种不对的复杂度做法：

1、枚举每一个后缀，通过 Z 可以求出与前缀的 LCP 然后去串里面暴力找子串。

2、枚举每一个中间串，通过 Z 可以求出与前缀的 LCP ，将这些长度暴力染色，遇到后缀就判一下。

……然后这两种复杂度都不对。考虑怎么优化一下。发现我们只关心最长能够匹配的前缀，因为前缀是固定的。于是记录一下这个最大值就好了。复杂度线性。

```cpp

namespace Z_F{
    int L ;
    int Q ;
    int l, r ;
    int Z[N] ;
    int Pz[N] ;
	void gao(int bg, int L){
		for (int i = bg ; i < bg + L ; ++ i) Z[i] -- ;
        Z[bg] = L ;
	}
    int get_Z(char *s, int bg, int oo = 0){
        L = strlen(s + bg) ;
        l = bg, r = 0 ; Z[bg] = 0 ;
        for (int i = bg + 1 ; i < bg + L ; ++ i){
            if (r < i) Z[i] = 1 ;
            else Z[i] = min(Z[i - l + 1], r - i + 1) ;
            while (s[Z[i]] == s[i + Z[i] - 1]) ++ Z[i] ;
            if (r < i + Z[i] - 1) r = i + Z[i] - 1, l = i ;
        }
        if (!oo) gao(bg, L) ;
		return L ;
    }
    int exKMP(char *s, int bg, char *t, int gb){
        int q = get_Z(s, bg, 1) ; s[q + 1] = '#' ;
        L = strlen(t + gb) ; l = gb, r = 0 ;
        for (int i = gb ; i < gb + L ; ++ i){
            if (r < i) Pz[i] = 1 ;
            else Pz[i] = min(Z[i - l + 1], r - i + 1) ;
            while (s[Pz[i]] == t[i + Pz[i] - 1]) ++ Pz[i] ;
            if (r < i + Pz[i] - 1) r = i + Pz[i] - 1, l = i ;
        }
        for (int i = gb ; i < gb + L ; ++ i) Pz[i] -- ;
		return L ;
    }
}

int mx ;
int res ;
int Z1[N] ;
int Z2[N] ;
int tmp[N] ;
int ans[N] ;

int n, p ;
char s[N] ;
char t[N] ;

using namespace Z_F ;

int main(){
    scanf("%s", s + 1) ;
    n = get_Z(s, 1) ; res = 0 ;
    for (int i = 2 ; i <= n ; ++ i){
        if (i + Z[i] - 1 == n && Z[i] <= mx)
            if (res < Z[i]) res = Z[i], p = i ;
        chkmax(mx, Z[i]) ;
    }
    if (!res)
        return puts("Just a legend"), 0 ;
    for (int i = p ; i <= p + res - 1 ; ++ i)
        putchar(s[i]) ; return puts(""), 0 ;
}

```

---

## 作者：Sangber (赞：8)

### 题目描述
给定一个字符串 $S$，我们规定一个字符串 $P$ 是可行解，$P$ 需要满足：

1. $P$ 是 $S$ 的前缀
2. $P$ 是 $S$ 的后缀
3. $P$ 出现在 $S$ 中既不是前缀也不是后缀的地方

题目要求出满足条件的长度最大的 $P$，若存在输出该字符串，若不存在则输出`Just a legend`  
数据范围：$1\leq |S|\leq 10^6$

----
### 解题思路
我们可以发现一个切入点：  
对于我们找到的一个满足条件的字符串 $P$，（假设它在 $S$ 中的起始和终点坐标分别为 $l,r$）  
那么我们发现（设 $|S|=n$）：

+ $P$ 既是 $S[1...r]$ 的前缀，也是 $S[1...r]$ 的后缀
+ $P$ 既是 $S[l...n]$ 的前缀，也是 $S[l...n]$ 的后缀

有没有想到什么？没错！$\text{KMP}$  
而且我们还可以发现上述性质就是 $P$ 满足条件的充要条件！  
所以我们只需要求出正反两个 $next$ 数组，然后再枚举 $l$ ，判断是否符合条件即可。  
总的复杂度是 $O(n)$ 的。

----
### 细节注意事项
+ 这题不要把 $S$ 复制两次，我们可以用 `reverse` 函数将 $S$ 反转（因为这题空间开得不大）
+ 注意字符串下标问题

----
### 参考代码
```cpp
/*--------------------------------
--Author: The Ace Bee-------------
--Blog: www.cnblogs.com/zsbzsb----
--This code is made by The Ace Bee
--------------------------------*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#define rg register
#define clr(x, y) memset(x, y, sizeof x)
using namespace std;

const int _ = 1000010;

char s[_]; int p[2][_];

int main() {
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	p[0][1] = 0;
	for (rg int j = 0, i = 1; i <= n; ++i) {
		while (s[j + 1] != s[i + 1] && j) j = p[0][j];
		if (s[j + 1] == s[i + 1]) ++j;
		p[0][i + 1] = j;
	}
	reverse(s + 1, s + n + 1);
	p[1][1] = 0;
	for (rg int j = 0, i = 1; i <= n; ++i) {
		while (s[j + 1] != s[i + 1] && j) j = p[1][j];
		if (s[j + 1] == s[i + 1]) ++j;
		p[1][i + 1] = j;
	}
	int pos = 0, mx = 0;
	for (rg int i = 1; i <= n; ++i)
		if (p[0][i] == p[1][n - i + p[0][i]])
			if (mx < p[0][i]) mx = p[0][i], pos = i;
	reverse(s + 1, s + n + 1);
	if (pos == 0) puts("Just a legend");
	else { for (rg int i = pos - mx + 1; i <= pos; ++i) putchar(s[i]); puts(""); }
	return 0;
}
```
----
**完结撒花 $qwq$**


---

## 作者：Cry_For_theMoon (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF126B)

&emsp;&emsp;~~大佬们都打什么 Z 算法，我这个蒟蒻只能用 KMP 来水一发~~

&emsp;&emsp;我们注意到"前后缀"都是可以直接用 KMP 里的 $next$ 数组求出来的。关键在于一个位于中间的字串 $T$。

&emsp;&emsp;**若在中间的字串 $T$ 结束于 $str[i]$，那么 $T$ 一定是 $str[1..i]$ 的公共前后缀**。看到公共前后缀，自然而然我们可以再次使用 KMP。

&emsp;&emsp;又因为中间的那个字串 $T$ 的结尾只可能在 $str[2] ...str[n-1]$之间，那么我们最后字串的长度就不会超过 $\max(kmp[2..n-1])$ 。我们把这个最大值记作 $maxn$

&emsp;&emsp;那么这个 $T$ 又是整体的公共前后缀，那么我们从 $kmp[n]$ 开始枚举。如果长度超过 $maxn$ 了，我们就跳转到 $kmp[kmp[n]]$；以此类推直到为 0，如果为 0 了，直接输出 ```Just a legend``` 即可。

&emsp;&emsp;当我们当前的长度 $len <= maxn$ 后，就要看中间是否存在一个 $kmp[k] = len$ 的了。在这里我认为 KMP 的题解里最后遍历 $kmp[2..n-1]$ ，看哪个等于 $len$，再直接输出的做法是不必要的。我们很容易就可以证明 $kmp[2..n-1]$ 中一定有一个的值是等于 $len$ 的，即一定存在一个位于中间的跟长度为 $len$ 的前（后）缀相同的字串 $T$。

&emsp;&emsp;原因何在？回想一下我们 $kmp$ 数组的推导过程，除了 $kmp[i] = 0$ 的情况，**所有的 $kmp[i]$，都一定是从一个比它少 1 的 $kmp$ 值 +1得来的**。举个例子，若 $kmp[1..n]$ 里有一个值为 3 的，非常显然也有一个长度为 2 的 $kmp$ 值。（你的代码里是不是有一个 "if 相等 ： j++" 的语句？）

&emsp;&emsp;那么我们就得出了一个结论：**1~maxn** 这些值都存在于 $kmp[2..n-1]$ 中。又知道这个 $len$ 一定满足 $1<=len<=maxn$，那么，$kmp[2..n-1]$ 一定有一个值为 $len$。因此我们直接输出 $str[1..j]$ 即可。

&emsp;&emsp;最后贴上AC代码，供各位 dalao 参考

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1e6+10;
char str[MAXN];
int fail[MAXN],n,maxn=0;
int main(){
	cin>>(str+1);
	n=strlen(str+1);
	fail[1]=0;
	int j=0;
	for(int i=2;i<=n;i++){
		while(j&&str[j+1]!=str[i]){
			j=fail[j];
		}
		if(str[j+1]==str[i])j++;
		fail[i]=j;
		if(i!=n){
			maxn=max(maxn,j);
		} 
	}
	j=fail[n];
	if(maxn==0 || j==0){
		printf("Just a legend");
		return 0;
	}
	while(j>maxn){
		j=fail[j];
	}
	if(j==0){
		printf("Just a legend");
		return 0; 
	}
	for(int k=1;k<=j;k++){
		printf("%c",str[k]);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：after_the_end (赞：4)

其实这题我并不觉得有紫题的难度，充其量也就是个绿题

首先简述题意：

给你一个字符串 $S$ ，找到一个最长的串，且满足其是 $S$ 的前缀、后缀和中间的一个不是前缀后缀的子串。

我们首先思考不考虑最后一个条件的情况，设 $len$ 为 $S$ 的长度，那么 $KMP$ 算法中的失配数组 $fail_{len}$ 就是答案。因为失配数组 $fail$ 的定义就是在 $1$~$i$ 的子串中，前缀和后缀长度不等于 $i$ 时相同的最长长度。

接下来加上第三个条件，我们不仅要找到一个串满足是 $S$ 的前缀后缀，还要在中间出现过。顺着刚才的思路思考下去，如果当 $i=2$~$n-1$ 时有 $fail_i$ = $fail_{len}$ 说明在中间出现了一个子串既是前缀，也是后缀。

如果中间没有出现上面这种情况，说明答案长度可能是 $2$~$len-1$ 中某点 $i$ 的 $fail_i$ 。所以接下来就是关于每个不等于 $0$ 的 $fail_i$ 判断串 $S$ 是否有一个长度为 $fail_i$ 的后缀。很明显，如果直接判断，时间复杂度是 $\Theta(len^2)$ 的，明显过不了。所以我们可以加快判断的速度，使用神器—— $hash$ 。对于每个 $i$ ，令 $hash_i=hash_{i-1} \times base+s_i$ 然后提前预处理出 $base$ 的乘方，我们就可以在 $O(1)$ 的时间内用秦九韶算法快速求出 $l$~$r$ 的 $hash$ 值：

$(hash_r-hash_{l-1}\times base^{r-l+1})\mod\ p$

那么我们就可以在 $O(n)$ 的时间复杂度里解决这个问题。

代码部分：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
typedef unsigned long long ull; //代码中的 mod p 采用的是自然溢出
string s;
ull hsh[1000010],base[1000010];
int fail[1000010],len,maxn,num;
int main(){
    cin>>s;
    s=' '+s;
    int j=0;
    base[0]=1;
    base[1]=1231;
    len=s.size()-1;
    for(re int i=2;i<=len;++i){
        base[i]=base[i-1]*base[1];
    }
    for(re int i=1;i<=len;++i){
        hsh[i]=hsh[i-1]*base[1]+s[i];
        while(j&&s[i+1]!=s[1+j])j=fail[j];
        if(s[i+1]==s[1+j])++j;
        fail[i+1]=j;
        if(i!=len)maxn=max(fail[i],maxn);
    }
    if(maxn==0){
        puts("Just a legend");
        return 0;
    }
    for(re int i=2;i<len;++i){
        if(fail[len]!=0&&fail[i]==fail[len]){
            for(re int j=1;j<=fail[len];++j){
                printf("%c",s[j]);
            }
            return 0;
        }
    }
    for(re int i=2;i<len;++i){
        if(fail[i]==0)continue;
        if(hsh[len]-hsh[len-fail[i]]*base[fail[i]]==hsh[fail[i]]){
            if(fail[i]>fail[num]){
                num=i;
            }
        }
    }
    if(num!=0){
        for(re int j=1;j<=fail[num];++j){
            printf("%c",s[j]);
        }
        return 0;
    }
    puts("Just a legend");
    return 0;
}
```

---

## 作者：xyj1 (赞：4)

# 一道KMP的题。
## 建议前往博客食用效果更佳：http://www.cnblogs.com/xyj1
### 说正题：首先想到是看文本串前缀与后缀的最长相同长度，不难，普通KMP。如果不会KMP的话，可以前往这里https://www.cnblogs.com/xyj1/p/10445843.html
#### 接下来，考虑中间串匹配。首先，得到文本串前缀与后缀的最长相同长度，设为S，
如果在串的中间找到S，直接输出。实现
```cpp
	for(int i = k + 1;i < lena;i++)
	{
		if(kmp[i] >= k)
		{
			if(k != 0)
			for(int i = 1;i <= k;i++)printf("%c",c[i]);
			return 0;
		}
	}
```
##### 如果没找到，那就是文本串的最长与后缀相同的前缀的前缀与后缀的最长相同长度（有点难理解，其实就是kmp[kmp[i]]）。为什么呢。首先：前缀的前缀等于后缀的后缀（前缀等于后缀）（KMP中的前缀与后缀，即为S），前缀的前缀等于前缀的后缀（前缀等于中间串），因其是文本串的前缀的前缀与后缀的最长相同长度，故其为最大。
 
 贴代码
 ```cpp
 #include <bits/stdc++.h>
using namespace std;
char c[3000002];
int kmp[3000002];
int lena;
int main()
{
	scanf("%s",c + 1);
	lena = strlen(c + 1);
	int j = 0;
	for(int i = 2;i <= lena;i++)
	{
		while(j && c[j + 1] != c[i])j = kmp[j];
		if(c[j + 1] == c[i])j++;
		kmp[i] = j;
	}
	int k = kmp[lena];
	if(k == 0)
	{
		printf("Just a legend");
		return 0;
	}
	for(int i = k + 1;i < lena;i++)
	{
		if(kmp[i] >= k)
		{
			if(k != 0)
			for(int i = 1;i <= k;i++)printf("%c",c[i]);
			return 0;
		}
	}
	if(kmp[k] == 0 || k == 0)
	{
      printf("Just a legend");
		return 0;
	}
	else 
	{
		for(int i = 1;i <= kmp[k];i++)printf("%c",c[i]);
		return 0;
	}
	
	return 0;
}
 ```
 注意0！！！！！

---

## 作者：1saunoya (赞：3)

- Z  算法

考虑到这个玩意是前缀，是后缀，还要在不是前缀不是后缀的位置出现过。

就可以用一个 $vis$ 数组来判断这个和前缀 LCP 有没有出现过，就没有了。

如果要用 SAM 的话，可以启发式合并 ，判断这个节点上有没有 ed 为 $len_u$ 和 $n$ 的，以及集合大小要大于等于3，就可以了

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
const int maxn = 1e6 + 61;

int main() {
	
	auto getZ = [&](char*s, int len) {
		std::vector <int> Z(len + 1, 0);
		Z[1] = len;
		for(int i = 2, l = 0, r = 0; i <= len; i++) {
			if(i < r)
				Z[i] = std::min(Z[i - l + 1], r - i + 1);
			while(i + Z[i] <= len && s[i + Z[i]] == s[1 + Z[i]])
				++Z[i];
			if(i + Z[i] - 1 > r)
				l = i, r = i + Z[i] - 1;
		}
		return Z;
	};
	
	static char s[maxn];
	static int n;
	scanf("%s", s + 1), n = strlen(s + 1);
	std::vector <int> Z = getZ(s, n), vis(n + 1, 0);
	for(int i = 2; i <= n; i++)
		if(!vis[Z[i]]) while(!vis[Z[i]]) vis[Z[i]--] = 1;
		else if(i + Z[i] - 1 == n) { int p = i; while(p <= n) putchar(s[p++]); putchar('\n'); return 0; }
	printf("Just a legend\n");
	return 0;
}
```

---

## 作者：tuzhewen (赞：2)

一句话题意：在$S$中找到一个既是前缀，又是后缀，并且还出现过至少$3$次的子串。

提到`前缀`、`后缀`这样敏感的词语，我们一定会想到那个$Z$算法，这个算法可以在线性的时间（均摊的）内递推出$z$数组，即每个位置开始的最长的与某个前缀相同的子串的长度。~~（很绕对吧？我也这么觉得……）~~

看个例子：

$S$="abaab"

显然，$z_0$就是这个串本身的长度，我们便不做讨论。$z_1$是$0$，因为$S[1]$是'b'，而$S$没有以$b$开头的前缀；$z_2$是$1$，因为$S[2]==S[0]$但是，$S[3]\ne S[1]$所以长度为$1$；$z_3$是$2$，因为$S[3]==S[0],S[4]==S[1]$，所以长度为$2$；显然，$z_4$就是$0$了。

那么我们先看代码（注释在代码里有）：

```
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
using namespace std;
const int N=1e6+5;
int z[N],n;
char s1[N];
il void get_z(char *s1){//获得串s1的z数组
	int L=0,R=0;//这个L，R最后是用来看当前开始的最大匹配长度的
	F(i,1,n-1) {
		if(i>R) {//如果i>R，那么说明这个区间的信息一点点都没有被刚刚的递推所更新到，那么怎么办呢？只能一个一个区匹配咯。
			L=i,R=i;
			while(R<n&&s1[R-L]==s1[R]) R++;//这里的一个一个匹配看上去最劣的复杂度是O(n)的，那么整个算法不就是O(n^2)了么？
            //但是你想，我们这里的递推是因为当前的点i是没有被之前的递推所覆盖到的，也就是说我们不知道这里到底是个什么情况。但是当我们此处递推了很多，那后面（看后面else的第一个if）是不是不用递推，直接O(1)获得答案了？
			z[i]=--R-L+1;//最后的R多加了一个，手动模拟就想清楚了
		}
		else {
			int k=i-L;//那么此处就是Z算法的精华了，它利用了L，R单调不减的特性求出了i这个位置一定是在哪里被求过z了的
			if(z[k]<R-i+1) z[i]=z[k];//如果i这个位置的z全部都被求过了，那么直接更新（应该是z[k]+i-1<R，这样应该更好理解）
			else {//不然就说明我们只有一部分被更新了，那么把剩下的烂摊子继续一个个匹配完即珂
				L=i;
				while(R<n&&s1[R-L]==s1[R]) R++;
				z[i]=--R-L+1;
			}
		}
	}
}
int maxn=-10,pos;//maxn是本题的另一个核心
//maxn是来看当前最大的z[i]的，如果说我们已经找到了一个后缀前缀，并且在i前面的最大的z[i]是要比n-i长的，说明在中间至少也出现了一个相同的子串（举个栗子就能懂啦！）
int main() {
	scanf("%s",s1);
	n=strlen(s1);
	get_z(s1);
	F(i,1,n-1) {
		if(z[i]+i==n&&maxn>=n-i) {//显然,z[i]+i==n就说明了这个串既是前缀又是后缀，因为i+与从i开始与总串的前缀匹配长度的最大值一旦等于了n，那么说明这个串从i开始一直接到了最后。
			pos=i;//如果符合条件就记录一下合法的位置
            //此处没有判断最大长度是因为我枚举的循环就已经保证了长度是由大向小递减的了
			break;//break;
		}
		maxn=max(maxn,z[i]);//寻找最大的z[i]
	}
	if(!pos) puts("Just a legend");//没有就输出这个
	else F(i,0,n-pos-1) printf("%c",s1[i]);//有就输出呗
	return 0;
}
```

---

## 作者：zhengrunzhe (赞：2)

提供一个sam的做法，虽然过不去但是这是一个良好的思路

首先用sam判断一个子串是否在另一个子串里出现过

用线段树合并每个节点子树的right集合

看长度为$len$的子串是不是在子串$[l,r]$中，就找到它对应的节点$p$，在其线段树上看$[+len-1,r]$的区间和是不是大于0

这样的话，对于每个前缀$i$，用$pos[i]$表示其对应节点，它同时是个后缀的话，那它就会在$[n-i+1,n]$出现过，在$pos[i]$的线段树上查有没有$[n,n]$即可

还有一个约束就是存在有一个既不是前缀也不是后缀的子串跟它一样，那就看是不是在$[2,n-1]$中出现过即可，同理

```cpp
#include<cstdio>
#include<cstring>
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
const int N=1e6+10;
int n;
char s[N];
template<int maxn>class Segment_Tree
{
	private:
		struct tree
		{
			int sum;
			tree *lson,*rson;
			inline const void pushup()
			{
				sum=lson->sum+rson->sum;
			}
		}*root[maxn],memory_pool[maxn*42],*tail,*null;
		inline const void init()
		{
			tail=memory_pool;
			null=tail++;
			null->lson=null->rson=null;
			for (int i=1;i<maxn;i++)root[i]=null;
		}
		inline tree *spawn()
		{
			tree *p=tail++;
			p->lson=p->rson=null;
			return p;
		}
		inline const void insert(tree *&p,int l,int r,int pos)
		{
			if (p==null)p=spawn();
			p->sum++;
			if (l==r)return;
			int mid=l+r>>1;
			if (pos<=mid)insert(p->lson,l,mid,pos);
			else insert(p->rson,mid+1,r,pos);
		}
		inline const int query(tree *p,int l,int r,int L,int R)
		{
			if (p==null)return 0;
			if (l>R||r<L)return 0;
			if (l>=L&&r<=R)return p->sum;
			int mid=l+r>>1;
			return query(p->lson,l,mid,L,R)+query(p->rson,mid+1,r,L,R);
		}
		inline tree *merge(tree *a,tree *b,int l,int r)
		{
			if (a==null&&b==null)return null;
			if (a==null)return b;
			if (b==null)return a;
			tree *p=spawn();
			if (l==r)return p->sum=a->sum|b->sum,p;
			int mid=l+r>>1;
			p->lson=merge(a->lson,b->lson,l,mid);
			p->rson=merge(a->rson,b->rson,mid+1,r);
			p->pushup();
			return p;
		}
	public:
		inline Segment_Tree(){init();}
		inline const void insert(int p,int k)
		{
			insert(root[p],1,n,k);
		}
		inline const int query(int p,int l,int r)
		{
			return query(root[p],1,n,l,r);
		}
		inline const void merge(int a,int b)
		{
			root[a]=merge(root[a],root[b],1,n);
		}
};
template<int maxn,int maxc>class Suffix_Automaton
{
    private:
        static const int maxs=maxn<<1;
        Segment_Tree<maxs>sgt;
        int head[maxs],edc,to[maxs],next[maxs];
        int len[maxs],last,cnt,son[maxs][maxc],pos[maxn],fa[maxs];
        inline const void addedge(int u,int v)
        {
            next[++edc]=head[u];to[head[u]=edc]=v;
        }
        inline const void extend(int id,int c)
        {
            int p=last,np=++cnt;
            sgt.insert(np,id);
            len[pos[id]=last=np]=len[p]+1;
            for (;p&&!son[p][c];p=fa[p])son[p][c]=np;
            if (!p)return fa[np]=1,void();
            int q=son[p][c];
            if (len[q]==len[p]+1)return fa[np]=q,void();
            int nq=++cnt;len[nq]=len[p]+1;
            memcpy(son[nq],son[q],sizeof(son[q]));
            fa[nq]=fa[q];fa[q]=fa[np]=nq;
            for (;son[p][c]==q;p=fa[p])son[p][c]=nq;
        }
        inline const void dfs(int p)
        {
            for (int i=head[p];i;i=next[i])dfs(to[i]),sgt.merge(p,to[i]);
        }
        inline const bool exist(int p,int l,int r)
        {
        	return sgt.query(pos[p],l+p-1,r);
        }
    public:
        inline const void build()
        {
            cnt=last=1;
            for (int i=1;i<=n;i++)extend(i,s[i]-'a');
            for (int i=2;i<=cnt;i++)addedge(fa[i],i);
            dfs(1);
        }
        inline const int query()
        {
        	for (int i=n-1;i;i--)
        		if (exist(i,n-i+1,n)&&exist(i,2,n-1))
        			return i;
        }
};
Suffix_Automaton<N,26>sam;
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	sam.build();
	int p=sam.query();
	if (!p)puts("Just a legend");
	else for (int i=1;i<=p;i++)putchar(s[i]);
	return 0;
}
}
```

---

## 作者：顾z (赞：1)

# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq


### 一句话题意

求一个给定串$s$的一个子串$T$.

满足

- $T$是$s$的前缀
- $T$是$s$的后缀
- $T$在$s$中间出现过

### ~~xjb~~分析

首先明确我们要找的是这种情况.

![](https://i.loli.net/2018/10/14/5bc3019c59b88.png)

此时,我们发现,蓝色部分好像是什么东西?

$KMP$算法中的$next$! (最长公共前后缀的长度

现在明确了我们的解题方法,$KMP$

那么现在的问题就是要找图中红色部分.

#### 如何去找红色部分?

我们发现,可以将图片看成这样.

![](https://i.loli.net/2018/10/14/5bc301d3db0e8.png)

这样又成了$KMP$算法中的$next$

那么现在我们需要知道最长的长度.

显然,中间部分的长度可能比$s$的前缀或后缀长亦可能短,但是长度最大只可能是$next[n]$.

即真实答案$ans \leq next[n]$

所以我们需要在$2 $到$n-1$中找到第一个比$next[n]$小的位置。

而,我们需要记录一下$mxx=\sum_{i=2}^{n-1}next_i$

有什么用?

> 考虑一下我们的中间部分的子串长度只可能是$\leq next[n]$的,因此我们要一直跳转$next[n]$知道某个位置小于等于中间部分最长子串的长度.

这个时候问题得以解决.

判断无解的话只需要判断跳转到的$next$是否为$0$输出$Just\ a\ legend$即可。

最后只需要枚举$i$从$2$到$n-1$去找那个$next[i]$即可.

然后直接输出即可.

``代码``

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define R register
using namespace std;
char s[1000080];
int len,nex[1000080],k,mxx,now;
inline void judge()
{
	if(!now)
	{
		puts("Just a legend");
		exit(0);
	}
}
int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);nex[1]=0;
	for(R int i=2;i<=len;i++)
	{
		while(k and s[k+1]!=s[i])k=nex[k];
		if(s[i]==s[k+1])k++;
		nex[i]=k;
		if(i!=len)mxx=max(nex[i],mxx);
	}
	now=nex[len];
	judge();while(now>mxx)now=nex[now];judge();
	for(R int i=2;i<len;i++)
		if(now==nex[i])
		{
			for(R int j=i-now+1;j<=i;j++)
				printf("%c",s[j]);
			exit(0);
		}
}
```

---

## 作者：Link_Space (赞：0)

本题的题意题目中已经说得很清楚了。

形式化地：给定一个字符串 $S$ ，找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串。

那么这道题就很水了，首先你需要明白$next$数组的含义：以当前点为终点的子串与母串的 $LCP$ 长度。知道了这一点就可以很轻松地切了这道题，为什么呢？

可以想到：其实所求子串的长度即为$Min(Max(next[1$~$n-1]),next[n])$，我们将问题分解为两步:

①找到既是 $S$ 的前缀又是 $S$ 的后缀的子串。

②找到满足条件①并且在 $S$ 中间出现过的最长子串

问题①大家都可以很轻松地做出，所求子串长度即为$next[n]$

而问题②呢？其实和①大致相同，你只需要找出$next[1$~$n-1]$中的最大值，以这个最大值为长度的子串是满足既是 $S$ 的前缀又在 $S$ 中间出现过的最长子串的条件，但是同时你还要满足它是 $S$ 的后缀，所以$Min(Max(next[1$~$n-1]),next[n])$即为所求子串的长度。以下是代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1e6 + 5;
int nxt[N];
string temp;
char s[N];
int main()
{
	int maxx = 0;
	cin >> temp;
	for (int i = 0; i < temp.size();i++)
		s[i + 1] = temp[i];
	int n = temp.size();
	for (int i = 2, j = 0; i <= n; i++)
	{
		while(j&&s[i]!=s[j+1])
			j = nxt[j];
		if(s[i]==s[j+1])
			j++;
		nxt[i] = j;
		if(i!=n)
		    maxx = max(maxx, nxt[i]);
	}
	if(!nxt[n])
	{
		puts("Just a legend");
		return 0;
	}
	int x = nxt[n];
	while(x>maxx)
		x = nxt[x];
	if(!x)
	{
		puts("Just a legend");
		return 0;
	}
	for (int i = 1; i <= x; i++)
		cout << s[i];
	puts("");
    return 0;
}
```


---

## 作者：BzhH (赞：0)

第一遍读完这道题，这不就是个裸的KMP板子吗，然后迅速打出了KMP，发现并过不了样例2，于是又仔细读了一下题，发现读漏了一个条件，即需要在中间也出现过，因为我们知道,KMP中的next数组存的是相同的前缀和后缀的长度,那么只需要找在中间出现过前缀长度,并标记一下就行了,最后在匹配的时候多判断一下。

详见代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N = 1e6 + 5;

string s;
int net[N], num[N];
bool is[N];

int main()
{
    cin >> s;
    for (int i = 1, j = 0; s[i]; i++)
    {
        while (j && s[i] != s[j])
            j = net[j - 1];
        if (s[i] == s[j])
            j++;
        net[i] = j;
    }//求next
    int len = s.length();
    for (int i = 1, j = 0; i < len - 1; i++)
    {
        while (j && s[i] != s[j])
            j = net[j - 1];
        if (s[i] == s[j])
            j++;
        is[j] = true;
    }//找出中间出现过的前缀的长度
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        while (j && s[i] != s[j])
            j = net[j - 1];
        if (s[i] == s[j])
            j++;
        while (j && !is[j])
            j = net[j - 1];//判断是否在中间出现过
    }//匹配
    if (!j)
        cout << "Just a legend";
    else
        for (int i = 0; i < j; i++)
            cout << s[i];
    return 0;
}
```


---

## 作者：Bazoka13 (赞：0)

**一个有点暴力的直白想法**

------------

先建好next数组，找一个int变量sig=next[n-1]（这里sig=0时直接输出“Just a legend”），然后从1~n-2遍历next数组，有相同的长度就输出，否则就sig=next[sig-1]找下一个更短的既是前缀又是后缀的子串长度，当sig=0时输出“Just a legend”。

------------
```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
#define ull unsigned long long
#define Pi 3.1415926535
const int MaxN =1000005;
char s[MaxN];int nxt[MaxN];
void prefix_function(char *s,int *pi) {
    int n = strlen(s);
    pi[0]=0;
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
}
int main() {
    cin>>s;
    prefix_function(s,nxt);
    int n=strlen(s);
    int sig=nxt[n-1];
    if(sig==0)cout<<"Just a legend"<<endl;
    else{
        while (sig){
            for (int i = 1; i <n-1 ; ++i) {
                if(nxt[i]==sig){
                    for (int j = 0; j <nxt[i] ; ++j) {
                        cout<<s[j];
                    }
                    return 0;
                }
            }
            sig=nxt[sig-1];
        }
        cout<<"Just a legend"<<endl;
    }
	 return 0;
}
```


---

