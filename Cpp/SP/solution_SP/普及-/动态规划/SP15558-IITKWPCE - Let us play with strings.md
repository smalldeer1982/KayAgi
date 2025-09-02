# IITKWPCE - Let us play with strings

## 题目描述

 Feluda likes palindromes very much. He is so fond of palindromes that if you give him any string, he will try to break it into continous palindromes.  
 As Feluda is a smart boy, he will do try to break the string into minimum no of such continuous palindromes. You have to help Prabhu. Find out the answer for the problem if he is given a string s.

## 样例 #1

### 输入

```
4
abacdc
ababa
ababbacababbad
abcd
```

### 输出

```
2
1
5
4
```

# 题解

## 作者：linjunye (赞：0)

考虑这种求最值的问题，可以想到 DP 求解。

那么，我们定义 $dp_i$ 表示前 $i$ 个字符能得到的最小划分，即可推出一个方程：$dp_i=dp_j+1$，这里的 $j$ 要满足什么条件呢？我们看到我们要划分的是回文串，即 $j+1$ 到 $i$ 之间的字符构成一个回文串。

接下来，我们只需做到 $O\left(1 \right)$ 处理回文串即可（否则可能会被卡），怎么求呢？

首先，我们能想到处理回文串的利器——Manacher，但这么做其实比较复杂 ~~（也许吧）~~，所以我们用字符串哈希来处理。

怎么处理？很简单，只需要能快速求出正串的哈希值与反串的哈希值即可。

正串与反串的哈希是只需要用前缀、后缀和就能 $O\left(1 \right)$ 处理，然后前后缀和的预处理是 $O\left(n \right)$。

然后这里我用的是单哈希，因为我写的双哈希、三哈希、五哈希 ~~（还有这种哈希？！）~~ 都被卡了。

这里放一下单哈希的代码：

```cpp
//禁止抄袭！
//单哈希 
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010;
const int P1=79;
const int mod=1e9+7; 
inline int ksm(int a,int b){//快速幂 
	int z=1;
	while(b){
		if(b&1)z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z;
}
inline int inv(int x){//逆元
	return ksm(x,mod-2);
}
const int inv1=inv(P1);
int n;
string s;
int dp[N];
int k1[N];
int m1[N];
int pre1[N];
int suf1[N];
void init(){
	memset(pre1,0,sizeof(pre1));memset(suf1,0,sizeof(suf1));
	for(int i=1;i<=n;i++)pre1[i]=(pre1[i-1]+(s[i]-'a')*k1[i-1])%mod;//前缀哈希值
	for(int i=n;i>=1;i--)suf1[i]=(suf1[i+1]+(s[i]-'a')*k1[n-i])%mod;//后缀哈希值
	return;
}
bool pd(int l,int r){
	int x1=((pre1[r]-pre1[l-1])*m1[l-1]%mod+mod)%mod;//求出区间正串的哈希值 
	int y1=((suf1[l]-suf1[r+1])*m1[n-r]%mod+mod)%mod;//求出区间反串的哈希值
	return (x1==y1);
}
void solve(){
	memset(dp,0x3f,sizeof(dp));
	cin>>s;
	n=s.size();
	s=" "+s;
	init();
	dp[0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
			if(pd(j+1,i))
				dp[i]=min(dp[i],dp[j]+1);
	cout<<dp[n]<<"\n";
	return;
}
signed mian(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	k1[0]=1;for(int i=1;i<=N-10;i++)k1[i]=k1[i-1]*P1%mod;//处理底数的幂 
	m1[0]=1;for(int i=1;i<=N-10;i++)m1[i]=m1[i-1]*inv1%mod;//处理底数逆元的幂
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}
```

以及仅供参考的五哈希代码：

```cpp
//禁止抄袭！
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010;
const int P1=79;
const int P2=87;
const int P3=107;
const int P4=137;
const int P5=197;
const int mod=1e9+7;
inline int ksm(int a,int b){
	int z=1;
	while(b){
		if(b&1)z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z;
}
inline int inv(int x){
	return ksm(x,mod-2);
}
const int inv1=inv(P1);
const int inv2=inv(P2);
const int inv3=inv(P3);
const int inv4=inv(P4);
const int inv5=inv(P5);
int n;
string s;
int dp[N];
int k1[N],k2[N],k3[N],k4[N],k5[N];
int m1[N],m2[N],m3[N],m4[N],m5[N];
int pre1[N],pre2[N],pre3[N],pre4[N],pre5[N];
int suf1[N],suf2[N],suf3[N],suf4[N],suf5[N];
void init(){
	memset(pre1,0,sizeof(pre1));memset(suf1,0,sizeof(suf1));
	memset(pre2,0,sizeof(pre2));memset(suf2,0,sizeof(suf2));
	memset(pre3,0,sizeof(pre3));memset(suf3,0,sizeof(suf3));
	memset(pre4,0,sizeof(pre4));memset(suf4,0,sizeof(suf4));
	memset(pre5,0,sizeof(pre5));memset(suf5,0,sizeof(suf5));
	for(int i=1;i<=n;i++)pre1[i]=(pre1[i-1]+(s[i]-'a')*k1[i-1])%mod;
	for(int i=n;i>=1;i--)suf1[i]=(suf1[i+1]+(s[i]-'a')*k1[n-i])%mod;
	for(int i=1;i<=n;i++)pre2[i]=(pre2[i-1]+(s[i]-'a')*k2[i-1])%mod;
	for(int i=n;i>=1;i--)suf2[i]=(suf2[i+1]+(s[i]-'a')*k2[n-i])%mod;
	for(int i=1;i<=n;i++)pre3[i]=(pre3[i-1]+(s[i]-'a')*k3[i-1])%mod;
	for(int i=n;i>=1;i--)suf3[i]=(suf3[i+1]+(s[i]-'a')*k3[n-i])%mod;
	for(int i=1;i<=n;i++)pre4[i]=(pre4[i-1]+(s[i]-'a')*k4[i-1])%mod;
	for(int i=n;i>=1;i--)suf4[i]=(suf4[i+1]+(s[i]-'a')*k4[n-i])%mod;
	for(int i=1;i<=n;i++)pre5[i]=(pre5[i-1]+(s[i]-'a')*k5[i-1])%mod;
	for(int i=n;i>=1;i--)suf5[i]=(suf5[i+1]+(s[i]-'a')*k5[n-i])%mod;
	return;
}
bool pd(int l,int r){
	int x1=((pre1[r]-pre1[l-1])*m1[l-1]%mod+mod)%mod;
	int y1=((suf1[l]-suf1[r+1])*m1[n-r]%mod+mod)%mod;
	int x2=((pre2[r]-pre2[l-1])*m2[l-1]%mod+mod)%mod;
	int y2=((suf2[l]-suf2[r+1])*m2[n-r]%mod+mod)%mod;
	int x3=((pre3[r]-pre3[l-1])*m3[l-1]%mod+mod)%mod;
	int y3=((suf3[l]-suf3[r+1])*m3[n-r]%mod+mod)%mod;
	int x4=((pre4[r]-pre4[l-1])*m4[l-1]%mod+mod)%mod;
	int y4=((suf4[l]-suf4[r+1])*m4[n-r]%mod+mod)%mod;
	int x5=((pre5[r]-pre5[l-1])*m5[l-1]%mod+mod)%mod;
	int y5=((suf5[l]-suf5[r+1])*m5[n-r]%mod+mod)%mod;
	return (x1==y1)&&(x2==y2)&&(x3==y3)&&(x4==y4)&&(x5==y5);
}
void solve(){
	memset(dp,0x3f,sizeof(dp));
	cin>>s;
	n=s.size();
	s=" "+s;
	init();
	dp[0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
			if(pd(j+1,i))
				dp[i]=min(dp[i],dp[j]+1);
//	for(int i=1;i<=n;i++)cout<<dp[i]<<" ";cout<<"\n";
	cout<<dp[n]<<"\n";
	return;
}
signed mian(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	k1[0]=1;for(int i=1;i<=N-10;i++)k1[i]=k1[i-1]*P1%mod;
	m1[0]=1;for(int i=1;i<=N-10;i++)m1[i]=m1[i-1]*inv1%mod;
	k2[0]=1;for(int i=1;i<=N-10;i++)k2[i]=k2[i-1]*P2%mod;
	m2[0]=1;for(int i=1;i<=N-10;i++)m2[i]=m2[i-1]*inv2%mod;
	k3[0]=1;for(int i=1;i<=N-10;i++)k3[i]=k3[i-1]*P3%mod;
	m3[0]=1;for(int i=1;i<=N-10;i++)m3[i]=m3[i-1]*inv3%mod;
	k4[0]=1;for(int i=1;i<=N-10;i++)k4[i]=k4[i-1]*P4%mod;
	m4[0]=1;for(int i=1;i<=N-10;i++)m4[i]=m4[i-1]*inv4%mod;
	k5[0]=1;for(int i=1;i<=N-10;i++)k5[i]=k5[i-1]*P5%mod;
	m5[0]=1;for(int i=1;i<=N-10;i++)m5[i]=m5[i-1]*inv5%mod;
	int T;
//	T=1;
	cin>>T;
	while(T--)solve();
	return 0;
}
```

谁说代码一定是粘上去就能 AC 的？

---

