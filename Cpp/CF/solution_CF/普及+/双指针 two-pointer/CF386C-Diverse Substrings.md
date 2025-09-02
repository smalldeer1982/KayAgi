# Diverse Substrings

## 题目描述

给定一个字符串 $s$，定义 $d(x)$ 为字符串 $x$ 内不同的字符个数。

求有多少个 $s$ 的子串 $s1$，使得 $d(s1)$ 为给定的 $t_{i}$。

## 样例 #1

### 输入

```
abca
```

### 输出

```
3
4
3
3
```

## 样例 #2

### 输入

```
aabacaabbad
```

### 输出

```
4
14
19
28
5
```

# 题解

## 作者：Hisaishi_Kanade (赞：2)

设 $f(i)$ 表示恰好 $i$ 种字母的区间个数。发现不是很好求解。

那么不妨再设 $g(i)$ 表示不超过 $i$ 种的区间个数，则 $f(i)=g(i)-g(i-1)$。

$g(i)$ 的求解是极其简单的，可以使用尺取法。每次尺取 $O(n)$，只需要尺取 $d(s)$ 次，则复杂度为 $O(nd)$，$d\le 26$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
const int N=3e5+5, inf=2e9;
const ll illf=1e18;
int a[N];
const char lV='a', rV='z';
int qt, n, i, j, k, col, l, r;
int cnt[N]; ll t[N];
char str[N];
inline void add(int x)
{
	if(cnt[x]==0) ++col;
	++cnt[x];
}
inline void del(int x)
{
	if(cnt[x]==1) --col;
	--cnt[x];
}
inline ll solve(int x)
{
	int i; ll res; rep(i, lV, rV) cnt[i]=0;
	res=col=0; l=1; rep(r, 1, n)
	{
		add(str[r]);
		while(col>x) del(str[l++]);
		if(col<=x) res+=r-l+1;
	}
	return res;
}
int main()
{
	scanf("%s", str+1); n=strlen(str+1); rep(i, 1, n) ++cnt[str[i]];
	int tot=0; rep(i, lV, rV) if(cnt[i]) ++tot; printf("%d\n", tot);
	rep(i, 1, tot) t[i]=solve(i); req(i, tot, 1) t[i]-=t[i-1]; 
	rep(i, 1, tot) printf("%lld\n", t[i]);
}

```

---

## 作者：海之眷恋8 (赞：2)

$d(s)$为字符串$s$的字符种类个数，求$d(s)$ 的值，以及$s$的子串中，字符种类为$1,2,...,d(s)$ 的分别有多少个。

CF上的标签是`dp` 和 `two pointers`。

第二次遇到的双指针的题，上一次遇到是CF的514D。这个的双指针比514D的要稍微麻烦一些，实际上是”三指针“。

双指针主要用于，需要遍历某个区间的所有子区间 的时候，直接枚举左右边界的话时间复杂度是$O(n^2)$,用双指针的话，是$O(n)$。

对于这道题而言，对 $k =1,2,..,d(s)$  分别计算 $t(k)$。

首先枚举区间左端点$L$，$R_1$为保证$d \Big( \big[L,R\big] \Big)=k$ 的最小$R$值，$R_2$为保证$d \Big( \big[L,R\big] \Big) > k$  的最小$R$值,这样的话，以$L$为左端点的区间中，字符种数为$k$的就有$R_2-R_1$种。

双指针能简化运算就在于，$L+1$所对应的$R1$和$R_2$ 一定大于等于原先$L$对应的$R_1$和$R_2$,所以，计算新的$R_1$和$R_2$的时候，只需要从原来的$R_1$,$R_2$往后加就行了，

这样就变成了$L$,$R_1$,$R2$这三个指针的单调递增，于是总时间复杂度也就变成$O(n)$的了。

有一个例外情况，当$[L,R_1]$的字符种数小于$k$的时候，若$R_1<n$ 则$R_1++$,所以，若出现 $[L,R_1]$的字符种数小于$k$这种情况时，一定是$R_1=n$,$R_2=n+1$;

这时，由于答案不再是$R_2-R_1$种,而是$R_2-R_1-1$种，所以其实表达式应该是 `ANS+=R2-R1-(R1==n);`

 当然，`（R1==n)`等价于    ( $[L,R_1]$的字符种数小于k)     在我的代码中即为`(M1.m<k)`:
 # ~~W~~AC代码:
 ```cpp
 #include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#define maxn 300007
using namespace std;
struct Mark{//存储状态的结构体
	int cnt[26];
	int m;
	Mark(){memset(cnt,0,sizeof(cnt));m=0;}
};
string str;
int n;
long long d[27];
int getK(Mark m){
	int ANS=0;
	for(int i=0;i<26;++i) ANS+=(m.cnt[i]>0);
	return ANS;
}
void T(int k){//求 T(k) 
	int R1=1,R2=1;//[L,[R1..R2)]为以L开始的区间 
	Mark M1,M2;//区间[L,R1]和 [L,R2] 的状态 
	M1.cnt[str[0]-'a']++;M1.m=1;M2=M1;
	for(int L=1;L <=n;++L){//枚举左端点 
		//更新 M1,M2 使之对应区间 [L,R1]和[L,R2] (这里的L是新的L。而M1,M2对应的是旧L的区间)
		if(L>1){ 
			M1.cnt[str[L-2]-'a']--;if(!M1.cnt[str[L-2]-'a']) M1.m--;
			M2.cnt[str[L-2]-'a']--;if(!M2.cnt[str[L-2]-'a']) M2.m--;
		}
		//计算新的R1,R2 
		while(M1.m < k&&R1 < n){if(!M1.cnt[str[R1]-'a']) M1.m++;M1.cnt[str[R1++]-'a']++;}
		while(M2.m <=k&&R2 <=n){if(!M2.cnt[str[R2]-'a']) M2.m++;M2.cnt[str[R2++]-'a']++;}
		//累加计算结果 
		d[k]+=R2-R1-(M1.m <k);//printf("d[%d]+=%d (L=%d  R1=%d R2=%d)\n",k,R2-R1,L,R1,R2);
	}
}
int main(void)
{
	while(cin>>str){
		Mark M; 
		n=str.length();
		for(int i=0;i<n;++i) M.cnt[str[i]-'a']++;
		memset(d,0,sizeof(d));
		int D=getK(M);
		for(int i=1;i<=D;++i){T(i);}
		printf("%d\n",D);
		for(int i=1;i<=D;++i){
			cout<<d[i]<<endl;
		}
	}
return 0;
}
 ```
 > [原文](https://blog.csdn.net/zearot/article/details/43955707)

---

## 作者：_edge_ (赞：1)

[题意](https://www.luogu.com.cn/discuss/464141)

其实可以发现，我们先枚举右端点的话，对于不同的 $d$ 的值，左端点的数量仅仅有 $26$ 个。

什么意思呢？就是说，对于很多左端点来说，他们到右端点的子串 $d$ 的值是类似的。

然后我们发现这个东西它具有单调性，可以进行二分，具体的，对于以右端点 $i$ 开始的，每一段都二分一下最远的左端点，然后记录前缀和 check。

~~然而过不去。~~

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=3e5+5;
string s1;
int sum[INF][35],t[35];
int check(int l,int r) {
//	cout<<l<<" "<<r<<" "<<"bomb\n";
	int ans=0;
	for (int i=0;i<26;i++)
		if (sum[r][i]-sum[l-1][i]) ans++;
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s1;int len=s1.size();s1=" "+s1;
	for (int i=1;i<=len;i++) {
		for (int j=0;j<26;j++) 
			sum[i][j]=sum[i-1][j]+((s1[i]-'a')==j);
	}
	
	for (int i=1;i<=len;i++) {
		int j=i;
		while (j>=1) {
			int l=1,r=j,ans=-1,xx=check(j,i);
			while (l<=r) {
				int Mid=(l+r)>>1;
				if (check(Mid,i)==xx) r=(ans=Mid)-1;
				else l=Mid+1;
			}
			t[xx]+=j-ans+1;
			j=ans-1;
//			cout<<j<<" "<<ans<<" ??\n";
		}
	}
	
	cout<<check(1,len)<<"\n";
	
	for (int i=1;i<=26;i++)
		if (t[i]) cout<<t[i]<<"\n";
	return 0;
}
```

可惜，这里是 $3 \times 10^5$ ，我本地跑大约是 2.5s，CF 上的远古题时限都比较紧，所以过不去。

然后我们考虑如何优化这个过程，我们发现这个复杂度的瓶颈出在二分以及 check。

假如说我们以及知道了要记录的 $d$ 的值，似乎可以做一点？

考虑枚举这个 $d$ 的值，然后再去枚举左端点，发现这个东西仍然具有单调性，并且很好用双指针去维护。

但是这题稍微有点烦，因为它双指针需要记录相同的数量。

如果仅仅跑的最后一个相同的，然后跑回来，那肯定会 TLE 起飞。

考虑用两个双指针，一个指向第一个，另外一个指向最后一个。

和莫队的想法一样，对于新出现的字符加到一个桶里面，然后就可以很快速的查询当前区间出现字符。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=3e5+5;
string s1;
int sum[INF][35],t[35],la[35],la1[35];
int check(int l,int r) {
//	cout<<l<<" "<<r<<" "<<"bomb\n";
	int ans=0;
	for (int i=0;i<26;i++)
		if (sum[r][i]-sum[l-1][i]) ans++;
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s1;int len=s1.size();s1=" "+s1;
	for (int i=1;i<=len;i++) {
		for (int j=0;j<26;j++) 
			sum[i][j]=sum[i-1][j]+((s1[i]-'a')==j);
	}
	
	for (int i=1;i<=26;i++) {
		int j1=0,j2=0,sum1=0,sum2=0;
		for (int k=1;k<=len;k++) {
			j1=max(j1,k-1);j2=max(j2,k-1);
			while (j1+1<=len && sum1<=i) {
				if (la[s1[j1+1]-'a']==0 && sum1==i) break;
				la[s1[j1+1]-'a']++;
				if (la[s1[j1+1]-'a']==1) sum1++;
				j1++;
			}
//			if (sum1>i) 
			while (j2+1<=len && sum2<i) {
//				if (la1[s1[j2+1]-'a']==0 && sum2==i-1) break;
				la1[s1[j2+1]-'a']++;
				if (la1[s1[j2+1]-'a']==1) sum2++;
				j2++;
			}
			
//			cout<<k<<" "<<i<<" "<<j1<<" "<<j2<<" ?\n";
			
			if (sum2==i && sum1==i) t[i]+=j1-j2+1;
			la1[s1[k]-'a']--;
			if (la1[s1[k]-'a']==0) sum2--;
////			
			la[s1[k]-'a']--;
			if (la[s1[k]-'a']==0) sum1--;
		}
	}
	
	cout<<check(1,len)<<"\n";
	
	for (int i=1;i<=26;i++)
		if (t[i]) cout<<t[i]<<"\n";
	return 0;
}
```


---

## 作者：daitangchen2008 (赞：0)

## 分析  
对于每一位 $i$，我们向前枚举以它为结尾的字符串包含的字符个数。  
显然有性质：**在此过程中第一个遇到的与字符 $i$ 不同的字符会对不同字符的贡献加1。**  
于是我们令 $pos_k$ 为现在字符 $k$ 出现最近的位置。  
枚举到第 $i$ 位时，把不包含字符 $i$ 的 $pos_k$ 排序，从后往前去即可。  
时间复杂度 $O(nk\log k)$，其中 $k=26$。可以通过此题。

## 代码  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int pos[30];
int dp[300005][30];
int a[30];
int mhash[300005][30];
int sor[30];
signed main()
{
	string st;
	cin>>st;
	int len=st.size();
	int tot=0;
	for(int i=0;i<len;i++)
	{
		int x=st[i]-'a'+1;
		if(pos[x]==0)
			tot++;
		pos[x]=i+1;
		int wei=0;
		for(int j=1;j<=26;j++)
		if(j!=x)
			sor[++wei]=pos[j];
		sort(sor+1,sor+26);
		reverse(sor+1,sor+26);
		for(int j=1;j<=tot;j++)
			dp[i+1][j]=sor[j];
		for(int j=1;j<=26;j++)
			sor[j]=0;
	}
	for(int i=1;i<=len;i++)
		dp[i][0]=i;
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++)
	{
		int ans=0;
		for(int j=1;j<=len;j++)
		{
			ans+=(dp[j][i-1]-dp[j][i]);
		}
		cout<<ans<<endl;
	}

	return 0;
}
```

---

