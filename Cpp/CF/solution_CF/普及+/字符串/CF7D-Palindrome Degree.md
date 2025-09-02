# Palindrome Degree

## 题目描述

String $ s $ of length $ n $ is called $ k $ -palindrome, if it is a palindrome itself, and its prefix and suffix of length ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF7D/f337f976991ac53405b164907ebe1f51ebb0830e.png) are $ (k-1) $ -palindromes. By definition, any string (even empty) is 0-palindrome.

Let's call the palindrome degree of string $ s $ such a maximum number $ k $ , for which $ s $ is $ k $ -palindrome. For example, "abaaba" has degree equals to $ 3 $ .

You are given a string. Your task is to find the sum of the palindrome degrees of all its prefixes.

## 样例 #1

### 输入

```
a2A
```

### 输出

```
1```

## 样例 #2

### 输入

```
abacaba
```

### 输出

```
6```

# 题解

## 作者：唐一文 (赞：24)

~~因为很久以前的膜你赛中赛时过了这题所以现在就来发题解了~~

## Description

[传送门](https://www.luogu.com.cn/problem/CF7D)

## Solution

用 $f_i$ 表示前缀 $i$ 的阶级。

~~读题后~~可以知道：

- 若 $1\sim i$ 不是回文串，那么 $f_i=0$。

- 若 $1\sim i$ 是回文串，那么 $f_i=f_{\left\lfloor\frac{i}{2}\right\rfloor}+1$。

然后就是怎么判断回文串了。

可以用 manacher 或者 哈希 解决，这里用的是 哈希。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[5000005];
int n,dp[5000005],ans,fac=1,fro,bac;
/*
fac计算base的幂
fro计算从前往后的哈希值
bac计算从后往前的哈希值
这里是直接推过去的，也可以预处理一遍
*/
int main(){
	scanf("%s",c),n=strlen(c);
	for(register int i=0;i<n;++i){
		fro=fro*13+c[i],bac=bac+fac*c[i],fac=fac*13;
		!(fro^bac)?ans+=(dp[i]=dp[i-1>>1]+1):0;
	}
	printf("%d",ans);
}
```

---

## 作者：kczno1 (赞：7)

一个字符串如果不是回文串，那么阶=0;  
否则由于前一半和后一半阶一样，其阶=前一半阶+1  
$dp$即可  
需要判断每个前缀是否是回文串，$manacher$或$hash$即可
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define mp make_pair
const int D1=998244353,D2=1e9+7,w=29;
pii operator +(const pii &pr,int x)
{
	return mp(((ll)pr.first*w+x)%D1,((ll)pr.second*w+x)%D2);
}
pii operator *(const pii &p1,const pii &p2)
{
	return mp((ll)p1.first*p2.first%D1,(ll)p1.second*p2.second%D2);
}
pii operator -(const pii &p1,const pii &p2)
{
	return mp((p1.first-p2.first+D1)%D1,(p1.second-p2.second+D2)%D2);
}
const int N=5e6+5;
int n,dp[N];
pii mi_w[N];
struct HASH
{
char a[N];
pii s[N];
void init()
{
	rep(i,1,n)s[i]=s[i-1]+a[i];
}
pii qiu(int l,int r)
{
	return s[r]-s[l-1]*mi_w[r-l+1];
}
};
HASH s,ns;

int main()
{
	freopen("1.in","r",stdin);
	scanf("%s",s.a+1);
	n=strlen(s.a+1);
	rep(i,1,n)ns.a[i]=s.a[n-i+1];
	mi_w[0]=mp(1,1);
	rep(i,1,n)mi_w[i]=mi_w[i-1]+0;
	s.init();ns.init();
	int ans=0;
	rep(i,1,n)
	{
		int j=i/2;
		if(s.qiu(1,j)==ns.qiu(n-i+1,n-(i-j+1)+1))dp[i]=dp[j]+1;
		ans+=dp[i];
	}
	cout<<ans;
}

```

---

## 作者：Gaode_Sean (赞：4)

设 $dp_i$ 表示第 $i$ 个前缀的阶级，显然 $dp_i=dp_{\lfloor \frac{i}{2} \rfloor}+1,ans=\sum_{i=1}^ndp_i$。

注意到 $n \leq 5 \times 10^6$，所以这道题我们可以用 hash 来做。我们可以算出每一个前缀从前往后的哈希，同理也可以算出从后往前的哈希。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e6+1;
char ch[maxn];
int n,dp[maxn],t=1,a,b,ans;
int main()
{
	scanf("%s",ch+1);
	n=strlen(ch+1);
	for(int i=1;i<=n;i++){
		a=a*131+ch[i],b+=ch[i]*t;
		t*=131;
		if(a==b) dp[i]=dp[i>>1]+1,ans+=dp[i];
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Fool_Fish (赞：3)

其实按照题意去模拟就行了

对于 “当且仅当它本身是一个回文串” 这一判断，我们可以用 `hash` 去判断

对于 “而且它长度为n/2（向下取整）的前缀和后缀都是k-1阶级回文串” 这一操作，我们可以考虑直接 `dp` ，$dp_i$ 表示前缀 $i$ 的阶级

如果不是回文的，那么 $dp_i$ 就等于 $0$

否则就由 $dp_{\lfloor\frac{i}{2}\rfloor}+1$ 去更新 $dp_i$

代码也很好实现的哇：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define uLL unsigned long long
const int MAXN=5000005; 
uLL Hash2[MAXN];
uLL Hash[MAXN];
int dp[MAXN];
char s[MAXN];
char ss[MAXN];
int base=133331;
int tot=0;
uLL p[MAXN];
uLL get(int l,int r){
	return Hash[r]-Hash[l-1]*p[r-l+1];
}
uLL getre(int l,int r){
	return Hash2[r]-Hash2[l-1]*p[r-l+1];
}
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		ss[i]=s[n-i+1];
	}
	p[0]=1;
	for(int i=1;i<=n;i++){
		Hash[i]=Hash[i-1]*base+(int)(s[i]);
		p[i]=p[i-1]*base;
	}
	for(int i=1;i<=n;i++){
		Hash2[i]=Hash2[i-1]*base+(int)(ss[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		uLL right=get(1,i/2);
		uLL left=getre(n-i+1,n-i+i/2);
		if(right==left){
			dp[i]=dp[i/2]+1;
		}
		ans+=dp[i];
	}
	printf("%d",ans);
return 0;
}
```

---

## 作者：2021hych (赞：1)

# 前言
CF 的水绿。
# 思路
> k 阶级回文串  
> k-1 阶级回文串

显然的子问题重叠。考虑动规。

以当前递推的位置为阶段，用 $dp_i$ 表示 $s_1,s_2,\dots,s_i$ 的阶级。那么按照题面，如果 $s_1,s_2,\dots,s_i$ 是回文串。 
$$dp_i = dp_{i/2} + 1$$ 
否则无需递推。因为是求前缀阶级和，所以只要把每一次递推到的结果累加到 ans 里就可以了。

至于判断回文，预处理出顺序字符串的 HASH 数组，以及倒序字符串的 HASH 数组。就可以了。
# AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 5000001
using namespace std;
string s;
int len,f1[MAXN],f2[MAXN],p[MAXN],dp[MAXN],ans;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	len=s.size();
	s=" "+s;
	p[0]=1;
	for(int i=1;i<=len;i++) {
		f1[i]=f1[i-1]*131+s[i];
		f2[i]=f2[i-1]*131+s[len-i+1];
		p[i]=p[i-1]*131;
	}
	for(int i=1;i<=len;i++) {
		if(f1[i/2]-f1[0]*p[i/2]==f2[len-i+i/2]-f2[len-i]*p[i/2]) {
			dp[i]=dp[i/2]+1;
			ans+=dp[i];
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

设 $dp_i$ 表示 $i$ 为中心的阶数。

如果一个字符串是回文，那么有 $dp_i=dp_{\left\lfloor\frac{i}{2}\right\rfloor}+1$，否则 $dp_i=0$。

那么问题就是如何判断一个字符串是否为回文，这里采用 manacher 预处理。

然后对于一个位置 $i$，如果满足填上无用字符后的 $f_i=i$ 则说明这是一个可行的从 $1$ 到 $i$ 的回文。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=5000005;
char c[MAXN],s[MAXN<<1],C_C_;
int f[MAXN<<1],dp[MAXN],n,len,mid,mr;
signed main(){
	C_C_=getchar();
	while(C_C_!='\n'&&C_C_!='\r'&&C_C_!=EOF){
		c[++n]=C_C_;
		C_C_=getchar();
	}
	s[1]=s[0]='#';
	for(int i=1;i<=n;i++){
		s[i*2]=c[i];
		s[i*2+1]='#';
	}
	len=n*2+1;
	for(int i=1;i<len;i++){
		if(i<mr)f[i]=min(f[(mid<<1)-i],f[mid]+mid-i);
		else f[i]=1;
		while(s[i+f[i]]==s[i-f[i]])f[i]++;
		if(i+f[i]>mr){
			mr=i+f[i];
			mid=i;
		}
	}
	for(int i=1;i<=n;i++){
		if(f[i+1]>=i)dp[i]=dp[i/2]+1;
		else dp[i]=0;
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans+=dp[i];
	printf("%I64d",ans);
	return 0;
}
```


---

## 作者：SunsetSamsara (赞：1)

## 前置知识
子串hash
## 分析
首先可以用 `dp` 维护前缀的阶级，
每一个前缀的阶级都只有两种情况：

1. 前缀是回文串

则 $dp_i = dp_{\lfloor\frac i 2 \rfloor}$

2. 前缀不是回文串

则 $dp_i = 0$


于是只需要判断前缀是不是回文串即可。

考虑将字符串两边进行顺序哈希与逆序哈希，如果顺序哈希值与逆序哈希值相等则是回文串。

最后子串的哈希值 $hash(l,r) = hash(r) - hash(l - 1) \times base ^{r - l + 1}$，用这个去判断子串是否回文。

## 代码
```cpp
#include <bits/stdc++.h>
#define lld long long
using namespace std;
char str[5000001];
unsigned lld lhsum[5000001];
unsigned lld rhsum[5000001];
unsigned lld base[5000001];
unsigned lld getlhash(int l, int r) {
	return lhsum[r] - lhsum[l - 1] * base[r - l + 1];//子串哈希 
}
unsigned lld getrhash(int l, int r) {
	return rhsum[r] - rhsum[l - 1] * base[r - l + 1];//子串哈希 
}
int dp[5000001];
int main() {
	scanf("%s", str + 1);
	int len;
	base[0] = 1;
	for(int i = 1; str[i]; ++i) {
		len = i;
		base[i] = base[i - 1] * 149;                     //预处理 base(149) 的幂 
	}
	for(int i = 1; i <= len; ++i)
		lhsum[i] = lhsum[i - 1] * 149 + str[i];          //顺序
	for(int i = 1; i <= len; ++i)
		rhsum[i] = rhsum[i - 1] * 149 + str[len - i + 1];//逆序 
	lld ans = 0;
	unsigned long long l, r;
	for(int i = 1; i <= len; ++i){
		l = getlhash(1, i >> 1);
		r = getrhash(len - i + 1, len - i + (i >> 1));
		if(l == r){
			dp[i] = dp[i >> 1] + 1;//dp 
			ans += dp[i];
		}
	}
	printf("%lld\n", ans);
}
```

---

## 作者：smqk (赞：0)

判断一个字符串是否回文，使用 hash 从后往前和从前完后值是一样则这个字符串是回文字符串。


## AC CODE:

```java
import java.io.*;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.StringTokenizer;

public class Main {

    static FastScanner cin = new FastScanner(System.in);//快读
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));//快速输出


    public static void main(String[] args) {
        // 注意，这里如果用 Scanner 的 nextLine()  会 TLE
        String s = cin.nextLine();

        int n = s.length();
        int[] dp = new int[n];

        long ans = 0;
        // forward 从前往后的哈希值
        // back 从后往前的哈希值
        // factor 13的幂
        int forward = 0, back = 0, factor = 1;
        for (int i = 0; i < n; i++) {
            forward = forward * 13 + s.charAt(i);
            back = back + s.charAt(i) * factor;
            factor *= 13;

            // 判断回文字符串
            if (forward == back) {
                // dp 状态转移 + 结果统计
                ans += (dp[i] = dp[(i - 1) / 2] + 1);
            }
        }

        out.println(ans);
        out.flush();
    }

}

class FastScanner {
    BufferedReader br;
    StringTokenizer st;

    public FastScanner(InputStream in) {
        br = new BufferedReader(new InputStreamReader(in), 16384);
        eat("");
    }

    public void eat(String s) {
        st = new StringTokenizer(s);
    }

    // 读一行
    public String nextLine() {
        try {
            return br.readLine();
        } catch (IOException e) {
            return null;
        }
    }

    public boolean hasNext() {
        while (!st.hasMoreTokens()) {
            String s = nextLine();
            if (s == null) return false;
            eat(s);
        }
        return true;
    }

    // 读取下一个元素
    public String next() {
        hasNext();
        return st.nextToken();
    }

    // 读int
    public int nextInt() {
        return Integer.parseInt(next());
    }

    // 读long
    public long nextLong() {
        return Long.parseLong(next());
    }

    // 读double
    public double nextDouble() {
        return Double.parseDouble(next());
    }

    // 读BigInteger
    public BigInteger nextBigInteger() {
        return new BigInteger(next());
    }

    // 读BigDecimal
    public BigDecimal nextBigDecimal() {
        return new BigDecimal(next());
    }
}

```


---

