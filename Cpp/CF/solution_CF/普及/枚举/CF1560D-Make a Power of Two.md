# Make a Power of Two

## 题目描述

You are given an integer $ n $ . In $ 1 $ move, you can do one of the following actions:

- erase any digit of the number (it's acceptable that the number before the operation has exactly one digit and after the operation, it is "empty");
- add one digit to the right.

The actions may be performed in any order any number of times.

Note that if, after deleting some digit from a number, it will contain leading zeroes, they will not be deleted. E.g. if you delete from the number $ 301 $ the digit $ 3 $ , the result is the number $ 01 $ (not $ 1 $ ).

You need to perform the minimum number of actions to make the number any power of $ 2 $ (i.e. there's an integer $ k $ ( $ k \ge 0 $ ) such that the resulting number is equal to $ 2^k $ ). The resulting number must not have leading zeroes.

E.g. consider $ n=1052 $ . The answer is equal to $ 2 $ . First, let's add to the right one digit $ 4 $ (the result will be $ 10524 $ ). Then let's erase the digit $ 5 $ , so the result will be $ 1024 $ which is a power of $ 2 $ .

E.g. consider $ n=8888 $ . The answer is equal to $ 3 $ . Let's erase any of the digits $ 8 $ three times. The result will be $ 8 $ which is a power of $ 2 $ .

## 说明/提示

The answer for the first test case was considered above.

The answer for the second test case was considered above.

In the third test case, it's enough to add to the right the digit $ 4 $ — the number $ 6 $ will turn into $ 64 $ .

In the fourth test case, let's add to the right the digit $ 8 $ and then erase $ 7 $ and $ 5 $ — the taken number will turn into $ 8 $ .

The numbers of the fifth and the sixth test cases are already powers of two so there's no need to make any move.

In the seventh test case, you can delete first of all the digit $ 3 $ (the result is $ 01 $ ) and then the digit $ 0 $ (the result is $ 1 $ ).

## 样例 #1

### 输入

```
12
1052
8888
6
75
128
1
301
12048
1504
6656
1000000000
687194767```

### 输出

```
2
3
1
3
0
0
2
1
3
4
9
2```

# 题解

## 作者：MikeC (赞：4)

## 分析

对数字的操作实质上就是对字符串中的字符的增删操作，所以我们就很容易地把问题转化成了对一个字符串进行增删操作，至少操作多少次能使它变成 $2$ 的次幂的字符串形式。

于是我们考虑计算原始串和目标串的“差异”（长度-最长前缀的长度），然后更新答案。需要注意的是 $2$ 的次幂的表不止需要打 $k(2^{k-1}\lt 10^9\lt 2^k)$ 大小，因为显然字符串之间的“差异”和数字之间的“差异”并不是同种概念。

时间复杂度 $O(1)$。

## 代码

``````cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
char a[51];
char str[101][51]={"1","2","4","8","16","32","64","128","256","512","1024","2048","4096","8192","16384","32768","65536","131072","262144","524288","1048576","2097152","4194304","8388608","16777216","33554432","67108864","134217728","268435456","536870912","1073741824","2147483648","4294967296","8589934592","17179869184","34359738368","68719476736","137438953472","274877906944","549755813888","1099511627776","2199023255552","4398046511104","8796093022208","17592186044416","35184372088832","70368744177664","140737488355328","281474976710656","562949953421312","1125899906842624","2251799813685248","4503599627370496","9007199254740992","18014398509481984","36028797018963968","72057594037927936","144115188075855872","288230376151711744","576460752303423488","1152921504606846976","2305843009213693952","4611686018427387904"};
inline int work(int x){
    int sum=0;
    int n=strlen(a),m=strlen(str[x]);
    for(int i=0;i<n;i++){
        if(a[i]==str[x][sum])sum++;
    }
    ans=min(ans,n+m-2*sum);
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>a;ans=0x3f3f3f3f;
        for(int i=0;i<=62;i++){
            work(i);
        }
        printf("%d\n",ans);
    }
}
``````



---

## 作者：xiaozeyu (赞：3)

**upd 8.20:去除无关注释，感谢管理提醒。**

## 题意

可以在给出的每个数中删去数字，这一操作会保留前导零，即 $301$ 删去 $3$ 后会变成 $01$ 这个数字。还有一种操作是在后面加个数字。就最少几操作可以将原数字转化成 $2$ 的自然数次幂。

## 题解

显然数据范围很小，可以暴力比对所有 $2^k (k\ge 0)$ 。对于每一次比对，都是先考虑操作一，保留下可以作为第二个串的前缀的子序列，再在该串后面加上数字使其成为第二个数字，这样就变成一道简单的判断第一个串的子序列的问题。

所有第二个串即 $2^k (k\ge 0)$ 可以暴力枚举预处理好。

## 代码

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=a;i<=b;i++)
#define Rep(i,a,b) for(register int i=a;i>=b;i--)
#define LL long long
#define ls (rt<<1)
#define rs (rt<<1|1)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
inline long long lread()
{
    char c=getchar();long long x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
const int maxn=1010;
const int maxm=100010;
int b,d,e,g[100],sum,ans;
int n,len;
char a[20],ch[100][100];
long long f[100],c;
int main()
{
	n=read();
	For(i,1,62) f[i]=pow(2,i);
	f[0]=1;
	For(i,0,62)
	{
		c=f[i];
		while(c>0)
		{
			c/=10;
			g[i]++;
		}
		c=f[i];
		Rep(j,g[i],1)
		{
			d=c%10;
			ch[i][j]=d+'0';
			c/=10;
		}
		/*
		For(j,1,g[i])
		{
			if(g[i]-j==0) d=1;
			else d=pow(10,g[i]-j);
			ch[i][j]=((int)f[i]/d)+'0';
		}	*/
	}
	//For(i,0,62)
	//{
	//	For(j,1,g[i])
	//		printf("%c",ch[i][j]);
	//	cout<<endl;
	//}
	//cout<<f[62];
	//For(i,0,30)	
	//	cout<<g[i]<<" ";
	//cout<<endl;
	while(n--)
	{
		ans=0x3f3f3f3f;
		scanf("%s",a+1);
		len=strlen(a+1);
		//cout<<len<<endl;
		For(k,0,62)
		{
			sum=0;
			int l=1,r=0;
			for(l,r;l<=len;l++)
			{
				if(a[l]==ch[k][r+1])
				{
					r++;
				}
				if(r==g[k]) break;
			}
			sum=len-r;
			if(g[k]>r) sum+=g[k]-r;
			ans=min(ans,sum);
		}
		printf("%d\n",ans);
	}
}

```


---

## 作者：Illusory_dimes (赞：1)

[还须要往下翻却仍然不一定有更好的阅读体验](https://www.cnblogs.com/Illusory-dimes/p/15169251.html)

## description

对于一个数 $a(1\leq n\leq 10^9)$ ，求在只能删去一位数字和在最右边加一位数字的情况下，最快操作几次可以写成 $2^k$ 的形式。

## solution

因为数据最大是 9 位（ $\small 10^9$ 另算），假设现在最优解是去到只剩 1 位，那么如果同样作为最优解的话，补数至多会补到 9 + (9 - 1) = 17 位。

所以产生答案的 2 的 k 次幂中， k 最大也只会达到 59 （ 60~62 都可以哟，ull可以再加上 63 但都没什么用）。

k 不大，最长 19 位，完全可以暴力枚举，又因为题目的要求，只会用到 $\small 2^k$ 的前缀，所以只要算出原串和 $\small 2^k$ 的最长公共子序列，

然后按照题目要求，答案就是原串长度 - 最长公共子序列长度 + $\small 2^k$ 的长度 - 最长公共子序列长度。

因为原串长度 - 最长公共子序列长度就是指原串里面要去掉的部分。

而 $\small 2^k$ 的长度 - 最长公共子序列长度就是指原串中缺少的部分。

加起来就是答案啦。

最后只要对所有 2 的 k 次幂算一遍答案，取个 min 就完成力！

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=1e9;
int t,ans;
inline ll read(){
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
	return s*w;
}
inline void mian(){
    std::string s;
    std::cin >> s;
    for(int i=0;i<=60;i++){
        std::string t=std::to_string(1ll<<i);
        int k=0;
        for(int j=0;j<s.size();j++){
            if(k<t.size()&&s[j]==t[k])++k;
        }
        ans=std::min(ans,int(s.size())+int(t.size())-k-k);
    }
}
 
int main(){
    t=read();
    while(t--){
        ans=INF;
		mian();
		printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：youyou2007 (赞：1)

## Description
给定一个整数 $n$，每一次操作可以去掉数的任意一位（**保留前导0**），或者在数的末尾加上一位。

求最少要多少步才能将这个数变成 $2$ 的整数次幂。
## Solution
由于数据组数不多，且 $n$ 在 int 范围内，可以考虑暴力统计操作次数。

可以先将 $2^0$ 到 $2^{63}$ 先预处理出来，然后枚举 $i$，表示 $n$ 改成 $2^i$ 最少要多少步。

对于每一次 $n$ 与 $2^i$ 的比对，由于每次加位只能从末尾加，最优的肯定是将这个数先去掉几位，再末尾添加几位。


所以每次先将 $n$ 与 $2^i$ 转换成字符串，求得它们的前缀公共子序列长度，在公共子序列中的数是可以不用动的，剩下的数都需要删去，最后把后面的位数补齐。

最后的答案就是对所有的 $i$ 所求结果取 $min$。 

举个例子：（假设现在 $2^i$ 枚举到了 $1024$）

$10523$ 位数为 $5$ 

$1024$ 位数为$4$

前缀公共子序列：$102$ 位数为 $3$

所以对于这个 $i$ 答案为 $5-3+4-3=2$。

## Code
```cpp
// by youyou2007 Aug.
#include <bits/stdc++.h>
#define int long long//由于n可能在后面加位数后会爆int，要开long long
#define REP(i, x, y) for(register int i = x; i < y; i++)
#define rep(i, x, y) for(register int i = x; i <= y; i++)
#define PER(i, x, y) for(register int i = x; i > y; i--)
#define per(i, x, y) for(register int i = x; i >= y; i--)
#define lc (k << 1)
#define rc (k << 1 | 1)
using namespace std;
int T;
int ans;
int poww[67]={1};
int calc(int x)//calc用来求出数的位数
{
	int cnt=0;
	while(x>0)
	{
		cnt++;
		x/=10;
	}
	return cnt;
}
string go(int x)//go用来将数转为字符串
{
	string temp="";
	while(x>0)
	{
		int t=x%10;
		temp=char(t+'0')+temp;
		x/=10;
	}
	return temp;
}
signed main()
{
	int n;
	cin>>T;
	rep(i,1,63)
	{
		poww[i]=poww[i-1]*2;
	}
	while(T--)
	{
		cin>>n;
		int wei1=calc(n);
		ans=wei1+1;
		string s1=go(n);
		rep(i,0,62)
		{
			string s2=go(poww[i]);
			int k=0;
			int wei2=calc(poww[i]);
			int len1=s1.length(),len2=s2.length();
			for(int i=0;i<len1;i++)//由于位数很小，求前缀公共子序列可以暴力枚举
			{
				if(s1[i]==s2[k])
				{
					k++;
				}
				if(k>len2-1)
				{
					break;
				}
			}
			ans=min(wei1-k+wei2-k,ans);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Shirο (赞：1)

### 题意
对于一个数字串，可以在尾部增加数字或者在任意位置删减数字，前导零会保留，求最少的操作次数使得原串变为 $2$ 的整数次幂。
### 做法
考虑到 $n$ 的范围比较小，可以枚举 $2$ 的次幂取一个最小的答案。接下来问题就转变为如何将一个数字变成指定数字。

现有 $2$ 数字串 $S$，$T$：

我们可以贪心地想到要最大化利用匹配的数字，利用两个指针维护两串具有的相同数字个数，记相同字符个数为$x$。
那么我们需要删除 $|S|-x$ 个数字，增添上 $|T|-x$ 个数字，故总操作个数即为$|S|+|T|-x$

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int wk(string s,string t)
{
	int tp=0,sp=0,x=0;
	while(sp<s.length() and tp<t.length())
	{
		if(s[sp]==t[tp])
			++x,++tp;
		sp++;
	}
	return s.length()+t.length()-2*x;
}
vector<string> all;//保存2的次幂数
signed main()
{
	for(int p=1;p<=(int)2e18;p*=2)
		all.push_back(to_string(p));
	int t;cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		int ans=s.length()+1;
		for(auto p : all)
			if(wk(s,p)<ans)
				cout<<p<<endl,ans=wk(s,p);
		cout<<ans<<endl;
	}
}
```


---

## 作者：Computer1828 (赞：1)

比赛时打了前三题然后很困，就瞅了一眼这题然后就关电脑睡觉，结果躺到床上五分钟想出正解……

------------

### 翻译

给你一个正整数 $n$。

你有两种操作：删掉其中一个数字（删后可以为空）、在这个数末尾添加一个数字。每种操作都可以以任意顺序进行若干次。注意，若经过删除操作后存在前导零，则前导零不会被删去。

求最小的操作次数，使得操作后的数等于 $2$ 的非负整数次幂。

### 正文

发现最多操作次数是 $n$ 的长度 $+1$，构造方法就是全删了然后添个 $1$。

所以不管怎么添数，最大得到的 $2^k$ 大约是 $10^{18}$ 量级。

于是我们就可以预处理 $2^0$ 到 $2^{60}$，然后将其视为字符串与 $n$ 比较能按顺序匹配几位，再用两个串的总长减去匹配位数两倍就是答案。

代码：C++11

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;string n;
string a[65];
inline int getans(string s,string t){
	int j = 0;
	for(int i = 0;i<s.length()&&j<t.length();++i){
		if(s[i] == t[j]) j++;
	}
	return s.length()+t.length()-j*2;
}
int main(){
	scanf("%d",&t);
	for(int i = 0;i<=60;++i) a[i] = (to_string((1ll<<i)));
	while(t--){
		cin>>n;
		int ans = n.length()+1;
		for(int i = 0;i<=60;++i) ans = min(ans,getans(n,a[i]));
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个整数 $n$。每次操作你可以做两件事情中的一件：

- 删去这个数中的一个数位（如果这个数只剩下一位，则**可以把它删空**）。
- 在这个数的**右边**添加一个数位。

你可以以任意顺序执行无限次操作。但请注意，在删去一个数位之后，这个数可能**包含前导零**（例如在删去 $301$ 中的 $3$ 这一位之后，这个数就会变成 $01$ 而不是 $1$）。

你需要执行若干次操作，使得这个数最终变成一个 $2$ 的次幂，或者说存在一个非负整数 $k$ 使得这个数最终是 $2^k$。最终答案**不能包含前导零**。请求出需要执行的操作的最小次数。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 10^4$，$1\leqslant n\leqslant 10^9$。**
## Solution
这题目讲究的就是一个枚举。由于 $2$ 的次幂是呈指数级增长的，因此在 $10^{18}$ 的范围以内的 $2$ 的次幂也只有 $59$ 个。所以我们可以直接枚举每一个 $10^{18}$ 以内的 $2$ 的次幂，求出当前数修改成每个 $2$ 的次幂需要的最小操作次数，取最小值即可。这种枚举方法在本题中亲测可过。

其次，如何求出当前数修改成 $2$ 的次幂的最小操作次数？我们不妨将数转化为字符串，然后考虑尽量多地去做第一种操作，留下 $2$ 的次幂或者 $2$ 的次幂的一个前缀，因此这可以转化为求出第一个数字串的最长前缀子序列，直接拿一个指针比对即可。设第一个数字串的长度是 $l_1$，第二个数字串的长度是 $l_2$，求出的第一个串的最长前缀子序列的长度为 $len$，那么最小修改次数就是 $l_1+l_2-2\cdot len$，因为需要 $l_1-len$ 次第一种操作将不是子序列中的数字删除，另外还需要 $l_2-len$ 次第二种操作将 $2$ 的次幂的前缀变为 $2$ 的次幂。

注意这里要枚举到 $10^{18}$，因为它可能在这个数的右边添加一个数位，所以直接枚举到 $10^9$ 显然无法枚举完整所有的情况。
## Code
```cpp
namespace Solution {
	const int N = 67;
	int cnt;
	string ans[N];
	
	inline string ll_to_str(ll x) {
		string ans = "";
		ll p = x;
		while(p) ans += (p % 10 + '0'), p /= 10;
		reverse(ans.begin(), ans.end());
		return ans; 
	}
	ii solve(string a, string b) {
		int lena = a.size(), lenb = b.size(), j = 0;
		F(int, i, 0, lenb - 1) if(b[i] == a[j]) ++j;
		return lenb + lena - 2 * j;
	}
	
	iv Main() {
		for(ll i = 1; i <= 1e18; ans[++cnt] = ll_to_str(i), i <<= 1ll);
		MT {
			string s; cin >> s;
			int res = 0x3f3f3f3f;
			F(int, i, 1, cnt) res = min(res, solve(ans[i], s));
			println(res);
		} 
		return;
	}
}
```

---

## 作者：chenwenda316 (赞：0)

本蒟蒻想不出好的方法，只能想出一个暴力的方法：

--------

思路：
设转换后的数为 $m=2^k$。
1. $2^0$ ~ $2^{63}$ 打表到一个二维数组。（`long long`范围 $19$ 位，超过 $19=9+1+9$ 位就不如全去掉再加一位变成个位数的 $m$ )
2. 读入 $n$，将 $n$ 也转换成数组。
3. 从 $1$ 到 $63$ 枚举 $k$，从而枚举 $m$。 
4. 从 $len(n)$ 到 $0$ 为匹配起始点，从高位匹配 $m$ 和 $n$，匹配后更新最小操作次数。易证此次枚举合理且能为最优匹配。
5. 输出。

----------

代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
short a[64][20];
short cnt[64];
long long llpow = 1;
int t;
long long q;
short temp[20];
int main()
{
    //打表
    cnt[0] = 1;
    a[0][1] = 1;
    
    for (int i = 1; i <= 63; i++) {
        llpow *= 2;
        long long tllpow = llpow;
        while (tllpow) {
            a[i][++cnt[i]] = tllpow % 10;
            tllpow /= 10;
        }
    }
    //打表结束
    cin >> t;
    while (t--) {
        cnt[64] = 0;
        cin >> q;
        while (q) {
            temp[++cnt[64]] = q % 10;
            q /= 10;
        }
        int ans = 0x3f3f3f;
        for (int i = 0; i <= 63; i++) {         //枚举 k
            for (int j = cnt[64]; j >= 0; j--) {//枚举匹配起始点
                int dis = cnt[64] - j;          //操作次数先加上起始点以前去掉的的数的个数
                int pi = j, pj = cnt[i];        //pi 为 n 的指针 pj 为 m 的指针
                while (pi > 0 && pj > 0) {      //依次匹配
                    if (temp[pi] != a[i][pj]) { //不匹配，pi 转到下一位，操作数++
                        dis++;
                        pi--;
                    } else {                    //匹配，两个指针转到下一位
                        pi--, pj--;
                    }
                }
                dis += (pi + pj);   //删减 n 结尾多余的数 或 增补 n 结尾不足的数
                ans = min(ans, dis);//更新答案
            }
        }
        cout << ans << endl;
    }
}
```


---

