# [ABC345C] One Time Swap

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc345/tasks/abc345_c

文字列 $ S $ が与えられます。次の操作を **ちょうど $ 1 $ 回** 行った後の文字列としてあり得るものがいくつあるか求めてください。

- $ S $ の長さを $ N $ とする。 $ 1\leq\ i\ <\ j\leq\ N $ をみたす整数の組 $ (i,j) $ を選び、$ S $ の $ i $ 文字目と $ j $ 文字目を入れ替える。

なお、この問題の制約下で操作を必ず行うことができることが証明できます。

## 说明/提示

### 制約

- $ S $ は英小文字からなる長さ $ 2 $ 以上 $ 10^6 $ 以下の文字列

### Sample Explanation 1

$ S $ の長さは $ 3 $ であるため、$ 1\leq\ i\ <\ j\leq\ 3 $ をみたす整数の組 $ (i,j) $ としては、 $ (1,2) $, $ (1,3) $, $ (2,3) $ の $ 3 $ 通りが考えられます。 - $ S $ の $ 1 $ 文字目と $ 2 $ 文字目を入れ替えた時、$ S $ は `bac` となります。 - $ S $ の $ 1 $ 文字目と $ 3 $ 文字目を入れ替えた時、$ S $ は `cba` となります。 - $ S $ の $ 2 $ 文字目と $ 3 $ 文字目を入れ替えた時、$ S $ は `acb` となります。 よって、`abc` に対して操作を行った後の文字列としては、`bac`, `cba`, `acb` の $ 3 $ つがあり得るため、$ 3 $ を出力します。

### Sample Explanation 2

どの $ 2 $ つの文字を入れ替えても $ S $ は `aaaaa` のままです。よって、操作後の文字列としてあり得るものは $ 1 $ つです。

## 样例 #1

### 输入

```
abc```

### 输出

```
3```

## 样例 #2

### 输入

```
aaaaa```

### 输出

```
1```

# 题解

## 作者：__ATRI__ (赞：9)

首先我们观察一下，如果每个字符都不同，那么应该有 $\dfrac{n(n-1)}{2}$ 个。

但是每个字符不一定不同。

我们考虑 $\dfrac{n(n-1)}{2}$ 是如何得到的：  
对于每一位字符都可以和其他的 $n-1$ 个字符交换。由于一个字符会与前面的字符交换一次，前面的字符又会与自己交换一次，所以结果除以 $2$，得到 $\dfrac{n(n-1)}{2}$。

如果出现字符相同的情况，那么当前字符与其他字符交换会产生原字符串。例如样例2，任意一个 `a` 与另一个 `a` 交换就会产生原字符串。

虽然原字符串也应算入结果，但由于可能产生重复，不方便统计重复次数，先暂时忽略新产生的原字符串，在计算完毕后加入。

设当前字符在字符串中有 $x$ 个（包括它自己），那么当前字符串可以产生的新字符串（非原字符串）个数为 $n-x$ 个。

最后，若出现重复字符则会产生原字符串，也算入答案，所以在此答案的基础上加 $1$ 即可。

代码：
```cpp
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

using ll=long long;

ll n,ans,f;//n为长度，ans为答案，f表示标记是否出现重复字符
string s;//原字符串
map<char,ll>mp;//用于统计字符出现了多少次

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> s;
	n=s.size();
	for(int i=0;i<n;++i){
		if(++mp[s[i]]>1)f=1;//统计字符出现了多少次，同时判断是否出现重复字符。
	}
	for(int i=0;i<n;++i)ans+=n-mp[s[i]];//统计答案
	cout << ans/2+f << endl;//答案除以2，若出现重复字符意味着交换会产生原字符串，所以加1。
	return 0;
}
```

---

## 作者：kkxacj (赞：6)

#### 思路

容易想到，两个相同的字母翻转，约等于没翻转。

然后发现，对于一个字符串，只要交换的两个位置的字符不相同，一定可以产生一个新的字符串，很容易证明吧，所以答案为**总个数减去相同字符交换的个数**，总个数为任意两个数交换的方案数，设 $n$ 为字符串的长度，则总个数就是 $n$ 个数中取 $2$ 个数的方案数，然后**注意，如果字符串内存在两个相同字符，最后的答案要加一，因为交换完后的字符串算一种状态**，最后输出就可以了。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,jl;
map<char,long long>mp;
map<char,long long>mp1;
string s,s1;
int main()
{
	cin >> s;
	ans = (s.size() - 1) * s.size() / 2;
	for(int i = 0;i < s.size();i++) 
	{
		ans -= mp[s[i]];
		if(mp[s[i]]) jl = 1;
		mp[s[i]]++;
	}
	printf("%lld",ans + jl);
	return 0;
}

```

---

## 作者：封禁用户 (赞：5)

大家好，我是高贵的 55 min 过 C 人。

![](https://cdn.luogu.com.cn/upload/image_hosting/s1fam2lv.png)

首先考虑 $O(n^2)$ 暴力匹配，因为 $|S|\le 10^6$，不能通过此题。

但是我们不难发现，如果一个字母 $S_{x}\ne S_{y}(x<y)$，它们就可以组成一种新的排列。我们就可以考虑后缀和，$sum_{i,j}$ 就代表区间 $[i,|S|]$ 中字符 ascii 码为 $j$ 的字母数量。后面每次计算的时候只用加上每个后面的字符个数减去和它相同的字符个数（也就是和它不同的字符数）即可。

接下来考虑 $S_{x}= S_{y}(x<y)$，也就是两个字符相同的情况，这样就还是原来的字符串，但是这种情况只能计算一次，要不然就会重复。

后话：听培训机构的老师说，同学们对这道题讨论出了 3 种方法，~~不过我当时不在场，所以不知道。~~

upd 2024.3.19：笔误了，重新交审一遍。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1E6+5;
int sum[N][130];
signed main(){
	string s;
	bool f=0;
	cin>>s;
	int ans=0;
	int len=s.size(); 
	s=" "+s;
	for(int i=len;i>=1;--i){
		for(int j='a';j<='z';++j){
			if(s[i]==j){
				sum[i][j]=sum[i+1][j]+1;
			}else{
				sum[i][j]=sum[i+1][j];
			}
		} 
	}int ll=0;
	for(int i=len;i>=1;--i){
		if(f==0&&sum[i+1][s[i]]>0){
			ans+=1;
			f=1;
		}
		ans+=ll-sum[i+1][s[i]];
		++ll;
	}cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_KHIN (赞：4)

暴力显然不能通过此题，考虑线性做法。

对于字符串的每一位，它对当前答案的贡献显然是它前面与它不同的字符的个数，但是直接记录与它不同的字符的个数是困难的，不如直接记录与它相同的字符个数，每次将答案加上它前面的字符数，再减去前面与它相同的字符个数即可。

code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
int cnt[27],ans=0;
signed main()
{
	cin>>s;
	s=" "+s;
	for(int i=1;i<s.size();i++)
	{
		ans+=(i-1-cnt[s[i]-'a']);
		cnt[s[i]-'a']++;
	}
	for(int i=0;i<=25;i++)
	{
		if(cnt[i]>=2)
		{
			ans++;
			break;
		}
	}//注意这个细节，将两个相同的字符交换也是一种解
	cout<<ans;
    return 0;
}
```

---

## 作者：2huk (赞：2)

六级蓝勾 @[xz001](/user/674967) 没做出来。

---

给定一个长度为 $n$ 的字符串 $s$。你需要进行恰好一次操作，选择两个整数 $1 \le i < j \le n$，并交换 $s_i, s_j$ 得到 $s'$。

求能得到多少种不同的 $s'$。

---

不难发现，如果选择的 $i, j$ 满足 $s_i \ne s_j$，那么新字符串 $s'$ 一定不同于其它的字符串。

同时，如果 $s$ 中存在 $i, j$ 满足 $s_i = s_j$，那么我们也可以将 $s_i, s_j$ 交换得到 $s' = s$。那么这也是一个不同于其它字符串的方案。

所以做法就是找 $s$ 中有多少 $i, j$ 满足 $s_i \ne s_j$，然后判断是否存在一种字符的出现次数 $\ge 2$ 次即可。

```cpp
void solve() {
	string s; cin >> s;
	int n = s.size(), res = 0;
	map<char, int> mp;
	for (int i = 0; i < n; ++ i ) {
		res += i - mp[s[i]];
		++ mp[s[i]];
	}
	int mx = 0;
	for (auto c : mp) mx = max(mx, c.second);
	fout << res + (mx > 1);
	return;
}
```

---

## 作者：__AFO__ (赞：2)

## 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc345_c)

本题是一道考验字符串使用的题，将 $i$ 个字符与 $j$ 个字符互换会有多少个新的字符串。

题目中说了 $i$ $<$ $j$ 所以我们可以先算出总方案数，再将重复方案减去，而重复的方案就是 第 $i$ 个字符 $=$ 第 $j$ 个字符的时候。

然而像样例 $2$ 这种特殊值，我们可以发现，不变也是一种方案，所以只要有一个字母重复出现，就要在总方案加一。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long a[27],zs;
int main(){
    cin>>s;//输入 
    for(long long i=0;i<s.size();i++){
    	a[int(s[i])-97]++;//记录字母出现个数 
	}
	for(long long i=0;i<=26;i++){
	if(a[i]>=2){//如果有一个字母重复出现多次，如样例2 
	zs++;//方案数加一 
	break;//特别重要	
	} 
	} 
	for(long long i=s.size();i>=1;i--) zs+=i;//总方案数，因为i<j,所以是递减 
	for(long long i=0;i<s.size();i++){
		zs-=a[int(s[i])-97];//将重复的字母对方案数去掉 
		a[int(s[i])-97]--;//因为i<j,所以以后的重复字母对就不会出现他了，就将字母总数减一 
	}
	printf("%lld",zs);
	return 0;
}
```

### END

---

## 作者：Link_Cut_Y (赞：1)

题目大意大概是，给你一个数列，你**需要**做**一次**操作，操作为交换数列中的两个值。求最后可以形成多少种不同的数列。

考虑容斥。对于相同的两项，交换是没有意义的。我们需要交换不同的两项。总方案数显然是 $\dbinom{n}{2}$，减去无意义的交换即可。

不妨设 $\texttt{abc} \cdots \texttt{z}$ 各出现了 $s_1 \sim s_{26}$ 次。无意义的交换就是 $\sum_{i \le 26} \dbinom{s_i}{2}$。

因此总方案数就是 

$$\dbinom{n}{2} - \sum_{i \le 26} \dbinom{s_i}{2}$$

需要注意的是，如果存在 $s_i \ge 2$，交换这样相同的两项会形成原串，这是需要被记录的。因此该情况下答案需要加 $1$。

```cpp
char s[N]; int n, bin[N];
int C(int n) { return n * (n - 1) / 2; }
signed main() {
	scanf("%s", s + 1); n = strlen(s + 1);
	rep(i, 1, n) bin[s[i] - 'a'] ++ ;
	int ans = C(n);
	rep(i, 0, 25) ans -= C(bin[i]);
	int flg = 0; rep(i, 0, 25)
		if (bin[i] > 1) flg = 1;
	cout << ans + flg << endl; return 0;
}
```

---

## 作者：Red_river (赞：1)

# 题目大意：

给你一个字符串 $S$。求出进行一次操作能得到多少个不同的字符串。

操作：设 $N$ 是 $S$ 的长度。选择一对整数 $(i,j)$，使得 
$1\leq i<j\leq N$，$S$ 中的第 $i$ 个和第 $j$ 个字符互换。
## 分析题意

首先，我们可以这样想，一个位置的方案数是不是它之后与他不同的字符个数之和，那这样就好办了。但是之后你会发现一个问题，就是有些时候，它所求的个数会少一，其实是正常现象，因为它在有多种字符时，会漏掉一个，所以直接特判就行了。
# code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define N 1000005
#define INF 2147483647
#define f(x,k,y,z) for(int x=k;x<=y;x+=z)
using namespace std;
int n,m,k,jk,ans,sum,num;char a[N];
int cnt,tot,dis[N],vis[N],wis[N],f[N];
void read(int &x)
{
	x=0;int ff=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%s",a+1);sum=strlen(a+1);
	for(int i=sum;i>=1;i--)
	{
		f[a[i]-97]++;//存储字符个数
		if(f[a[i]-97]>jk) jk=f[a[i]-97];//为了特判做准备
	}
	for(int i=1;i<=sum;i++)//枚举位置
	{
		ans=ans+(sum-i+1)-f[a[i]-97];//加上方案数
		f[a[i]-97]--;//字符个数减一
	}
	if(jk>1) ans++;//特判
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Otue (赞：1)

如果交换的两个字符是不同的，那么就可以得到一个全新字符串。如果交换的两个字符是相同的，就是原来的串。如果存在两个字符是相同的，那么答案需要加上本身。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e6 + 5;

int n, vis[27], sum[27], res, flg;
char a[N];

signed main() {
	cin >> (a + 1);
	n = strlen(a + 1);
	for (int i = 1; i <= n; i++) vis[a[i] - 'a' + 1]++; // 统计每个字符出现次数
	for (int i = 1; i <= 26; i++) sum[i] = sum[i - 1] + vis[i], flg += (vis[i] >= 2); 
	// flg 代表能不能成为原串
	for (int i = 1; i <= 26; i++) res += vis[i] * (sum[26] - sum[i]); 
	cout << res + (flg > 0) << endl;	
}
```

复杂度 $O(n)$。

---

## 作者：zcr0202 (赞：1)

## 题目大意

给你一个字符串 $S$。设 $N$ 是 $S$ 的长度。选择一对整数$(i,j)$，

其中 $1 \le i < j \le N$ 。让 $S_i$ 与 $S_j$ 互换一次，求不同的字符串有多少个。

## 解题思路

我们首先用一个数组来存一个字符出现了多少次，然后我们使用暴力来枚举两个不同的字符，利用乘法原理算出如果交换了这两种字符可以出现多少个字符串，即用 $a$ 字符出现的次数 $\times$ $b$ 字符出现的次数。我们发现还有一个问题，就是样例二过不了，因为我们少算了一种情况，就是它自己本身，只有当它有相同的两个字符时，就有它本身的这种情况。于是我们可以高兴地打暴力了。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6 + 5;
const int inf = 9999999;
const int mod = 1e9 + 7;
char a[N];
long long l, bz[N];
long long n, ans;
signed main() {
	scanf("%s", a + 1);
	l = strlen(a + 1);
	for(int i = 1; i <= l; i++) {
		bz[a[i] - 'a' + 1]++;
	}
	for(int i = 1; i <= 26; i++) {
		for(int j = i + 1; j <= 26; j++) {
			ans += bz[i] * bz[j];
		}
	}
	int ss = 0;
	for(int i = 1; i <= 26; i++) {
		if(bz[i] > 1) ss++;
	}
	if(ss != 0) ans++;
	cout << ans;
}
```

---

## 作者：Guizy (赞：1)

考虑一个个计算贡献。

对于一个 $S_i$，它可以和前面的 $S_1\sim S_{i-1}$ 每一个交换，产生 $1$ 的贡献。要注意的是，如果有一个 $j<i$ 且 $S_i=S_j$，就不能交换（因为交换后还是和原串一样的）。设 $t_j$ 表示这样的 $j$ 的个数，则 $S_i$ 的贡献就是 $i-1-t_j$。答案就是它们的和。

至于 $t_j$ 如何计算，直接开一个桶就行。

```cpp
for(int i=0;i<s.size();i++){
	ans+=i-tong[s[i]-'a'+1];
	tong[s[i]-'a'+1]++;
}
```

但是，你会发现，这样过不了第二个样例，可以发现，我们并没有统计交换后的串等于原串的情况。这种情况也很好处理，只需要判断每一个 $t_j$ 是否大于 $1$，如果是就给答案加上 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int tong[30];

signed main(){
	
	cin>>s;
	long long ans=0,flag=0;
	for(int i=0;i<s.size();i++){
		ans+=i-tong[s[i]-'a'+1];
      //s[i]-'a'+1 表示 s[i] 是第几个字母，下同
		tong[s[i]-'a'+1]++;
		if(tong[s[i]-'a'+1]>1) flag=1;
	}
	printf("%lld",ans+flag);
}
```

---

## 作者：SiriusIV (赞：1)

# 题目简述

给出一个字符串 $S$，求交换任意两个字符得出的新字符串个数。特别提醒若得出的两个字符串相同则算作同一种方案。

# 思路简述

因为此题只交换字符串中的两个字符，所以实际上只需要记录两个不同字符的匹配情况。此字符串中出现所有相同的字符交换只记作一种方案，对答案的贡献始终为 $1$。

# 代码详解

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000001];
long long ans,t[258];//排列组合问题，数据较大，不开 long long 见祖宗。
int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		t[s[i]]++;
		ans+=i-t[s[i]];//此处只需统计在此之前的其他字符个数，防止出现重复。
	}
	int o=0;
	for(int i=1;i<=257;i++)if(t[i]!=0)o++;//此处是计算字符重量数量，方便排查是否重复。
	if(o<n)ans++;//若有重复，对答案的贡献增加 1。
	cout<<ans;
}
```

---

## 作者：zzhbpyy (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc345_c)

## 思路

这是一道简单的模拟题。当我们交换字符串中两个不同的字母时，得到的新字符串一定是与其他操作结果不同的，因为这一次操作同时更改了两个字符。所以新字符串的重复的情况一定是交换了两个完全相同字母。

记字符串的长度为 $len$ 假设没有重复字符，则答案 $ans=len\times(len-1)/2$。我们只需要统计每个字母重复出现的字数，用 $ans$ 减掉交换相同字母情况即可。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int ans,ct;
int vis[130];
char rt[130];//出现重复的情况
signed main(){
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(!vis[s[i]])rt[++ct]=s[i];
		vis[s[i]]++;
	}ans=s.length()*(s.length()-1)/2;
	int t=ans;
  for(int i=1;i<=ct;i++){
		ans-=vis[rt[i]]*(vis[rt[i]]-1)/2;
	}
	cout<<(ans==t?ans:ans+1);
}
```

---

## 作者：tanzicheng (赞：1)

## [ABC345C] One Time Swap 题解

### 题目翻译

现在给了你一个字符串 $S$，你必须执行一次交换，交换时选择两个字符进行交换。**注意，不能自己与自己换**。 问有多少种可能被变成的字符串，请输出方案总数。

### 解题思路

先来考虑一下所有字符均不相同的情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/b5keeuwa.png)

很显然，答案是 $(|S|-1)+(|S|-2)+(|S|-3)+\dots+2+1$。

再来考虑一下，有字符相同的情况，有字符相同时，需要在原先没有字符相同的方案数减掉无效的方案数，如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/xvk5p4qc.png)

可以看到，减掉了无效的方案数总共 $(2+1)+1$ 个，**最后加 $1$，因为可以两个相同的字符交换，得到原串**。

### 具体实现

可以使用一个 `map` 做一个桶，桶里保存每个字符出现了几次。

计算方案数时可以使用高斯公式，进行 $O(1)$ 计算。预处理时间复杂度 $O(|S|)$，计算方案数复杂度 $O(1)$。

[AC](https://www.luogu.com.cn/record/151275013) code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long    //养成随手开long long的好习惯

string s;
int ans=0;

map<char,int> mp;    //桶

signed main(){
    cin >>s;
    for(int i=0;i<s.size();i++){
        mp[s[i]]++;    //预处理，统计每个字符的个数
    }
    bool flag=false;    //判断是否有重复字符
    for(char i='a';i<='z';i++){    //枚举26个字母，算出不合法方案
        if(mp[i]>1){ 
            ans-=(mp[i]-1)*(mp[i])/2;    //如果有重复就减掉不合法方案，高斯公式
            flag=true;    //更新flag
        }
    }
    ans+=(s.size()-1)*(s.size())/2;    //加上没有重复字符的方案数，高斯公式
    cout <<ans+flag;    //如果有重复就加1
    return 0;
}

---

## 作者：cqbzcjh (赞：1)

## 分析
先假设答案为所有字母都不同时的答案，再减去相同字母对的个数来排除重复的答案。

我们可以发现，除非交换的两个是相同的字母，否则交换后的结果一定和原字符串和其他交换后的结果不同（可以自己试一试）。

所以要用 $n\times(n-1)\div2$ 来求长度为 $n$ 时所有字母都不同时的答案和有 $n$ 个相同字母时的相同字母对的个数。

注意相同字母交换后的结果虽然和原字符串相同，但也是一种结果，仍然加进答案里。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long h[30],l,ans;//防止溢出，也可以在计算时乘以1LL
int main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);cout.tie(NULL);
	cin>>s;
	l=s.size();
	ans=l*(l-1)/2;//所有字母不同时的答案
	for(int i=0;i<l;i++)
		h[s[i]-'a']++;//通过桶记录相同字母的个数
	int t=0;
	for(int i=0;i<26;i++){
		if(h[i]){
			ans-=h[i]*(h[i]-1)/2;//减去相同字母的对数
			if(h[i]>1)t=1;
		}
	}
	if(t)ans++;
  
	//加上结果为原字符串的情况
	cout<<ans;
	return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
这题中，个数就是 $a_i\ne a_j$ 的组数，然后这个组数就可以用总数 $\frac{n\times(n-1)}2$ 减去每种字符自我配对（$a_i=a_j$）的个数就行。另外如果有 $a_i=a_j$ 的情况，交换 $i,j$ 也算一种情况，否则没有。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, tot[26];
ll sum;
string a;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> a;
	n = a.size ();
	sum = n * (n - 1ll) / 2;
	for (int i = 0; i < n; ++ i)
		++ tot[a[i] - 'a'];
	for (int i = 0; i < 26; ++ i)
		sum -= tot[i] * (tot[i] - 1ll) / 2;
	for (int i = 0; i < 26; ++ i)
		if (tot[i] > 1) { //有重复
			++ sum;
			break ;
		}
	cout << sum;
	return 0;
}
```

---

## 作者：OIer_Tan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc345_c)

## 题意

给你一个字符串 $S$。请找出只做下面的这个操作一次能得到的的字符串数。

- 设 $N$ 是 $S$ 的长度。选择一对整数 $(i,j)$，使得 $1\leq i\le j\leq N$ 和 $S$ 的第 $i$ 个和第 $j$ 个字符互换。


## 思路

暴力的思路很简单，直接 $O(N^2)$ 枚举即可，但显然超时。

考虑换一种思路，去观察哪些情况可以形成不同的字符串。

容易想到，

+ 对于交换字符 $S_i \not = S_j$ 的情况，得到的字符串与原来不同；
+ 对于交换字符 $S_i = S_j$ 的情况，得到的字符串与原来相同。

但是，直接枚举这两种情况的复杂度仍为 $O(N^2)$，并不能通过。

我们可以用一个数组来记录每种字符出现的次数。如果 $S$ 中出现了 $cnt_1, cnt_2,\ldots, cnt_{26}$ 个 `a`、`b`、 $\ldots$ 、`z`，那么就有 $\sum^{26}_{i=1}\sum^{26}_{j=1}{cnt_i\times cnt_j}$ 对不相同的字符。所以，我们可以用总对数减去 $S_i$ 和 $S_j$ 是相同字符的字符对，从而计算为 $\frac{1}{2}\{(cnt_1+cnt_2+\cdots+cnt_{26})^2-cnt_1^2-cnt_2^2\cdots-cnt_{26}^2\}=\frac{N^2-\sum^{26}_{i=1}cnt_i^2}{2}$。

综上所述，我们可以用 $O(N)$ 的时间复杂度解决这个问题。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

string s ;

ll ans ;

bool issame ;

unordered_map <char,ll> cnt ;

int main ()
{
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> s ;
	for ( ll i = 0 ; i < s.size () ; i ++ )
	{
		cnt [s [i]] ++ ;
	}
	ans = s.size () * s.size () ;
	for ( char i = 'a' ; i <= 'z' ; i ++ )
	{
		ans -= cnt [i] * cnt [i] ;
		if ( cnt [i] > 1 )
		{
			issame = 1 ;
		}
	}
	ans /= 2 ;
	if ( issame )
	{
		ans ++ ;
	}
	cout << ans << endl ;
	return 0 ;
}
```

---

## 作者：ykzzldz (赞：1)

考虑先不管交换后两个字符串相等的情况，也就是不交换两个相同字符的情况。那么，每一对不同字符的贡献均为一。因为初始时的字符不统计入答案，所以预处理的时候判断一下是否有一个字符出现次数大于一，如果是，则在最后的答案加一。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<char,int>mp;
string s;
int ans,flag;
signed main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		mp[s[i]]++;
		if(mp[s[i]]>1)flag=1;
	}
	for(int i=0;i<s.size();i++){
		ans+=s.size()-mp[s[i]];
	}
	cout<<ans/2+flag;
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：1)

# AT_abc345_c

## 题目简述

给出一个字符串 $S$ 你**需且仅需**（你猜我为什么特别强调）执行一次:

- 交换 $S$ 中的任两个字符。

请问有多少种可能的结果？

## 解题思路

先看数据范围，$S$ 长度在 $2$ 到 $10^6$ 之间，暴力 $O(n^2)$ 枚举肯定不行了（而且也存不下那么多情况啊）。

让我们来考虑这样一个问题：在什么情况下交换两个字符会出现同样的结果呢？显然，相同的字符交换后还是相同的。

所以思路就很明显了（吗？），我们只需要记录下字母 $i$ 出现的次数 $a_i$，那么所有能产生新结果的、包含字母 $i$ 的交换的数量就是 $(a_i-|S|)\times a_i$。

还有一点细节，由于如此计算的话每组交换都计算了两次，所以输出结果的时候要除以 $2$。

这就完了吗？

别忘了，如果一个串中没有重复的，那原串自然是不能作为结果的，上文所提到的做法也不假，但是如果重复了呢？我们交换这两个重复元素，结果就是原串，这时候结果就应该加上 $1$。

code：[link](https://atcoder.jp/contests/abc345/submissions/51316062)。

---

## 作者：无名之雾 (赞：0)

~~赛时没看数据范围吃了两发罚时~~


## 思路
对于这个字符串的每一个位置，我们发现他可以和字符串中其他的任意一个字符交换位置从而形成新的字符串。

所以我们只需从前向后枚举，累加每一个位置前面的不同的字符个数即可。

* 注意：对于一个有着两个及以上相同字符个数的字符串，我们应该在结果上增加 $1$ 因为该字符串可以通过交换两个相同的字符来变成这个字符串本身。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
map<char,int>cnt;
signed main(){
	string a;
	cin>>a;
	int ans=0;
	int flag=0;
	for(int i=1;i<=a.size();i++){
		ans+=i-1-cnt[a[i-1]];
		cnt[a[i-1]]++;
		if(cnt[a[i-1]]>=2)flag=1;
	}
	cout<<ans+flag;
	return 0;
}
```

---

## 作者：Programming_Konjac (赞：0)

# 思路
~~本蒟蒻错了一次然后对了。~~

我们发现，要想实现交换后不会出现重复，那么设当前字符为 $s_i(0\le i < |S|)$，那么要找出 $s_i$ 后面的字符与 $s_i$ **不同**的字符**数量**。

如何快速求出呢？答案是桶数组！

我们先遍历一遍，把桶数组的第 $s_i$ 项加 $1$。

然后再遍历一次字符串，每次把桶数组的值累加起来（不累加桶数组的 $s_i$ 位置），然后把桶的第 $s_i$ 项减 $1$，就可以了。

**我们还需要注意一点：如果有一个字符出现的数量大于等于 $2$，那么在输出的时候需要加 $1$，因为相同的字符翻转过来还是原来的字符串，需要加 $1$，但只能加 $1$ 次。**
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll Main1(string s){
	int tong[150]={0};
	ll len=s.size(),cnt=0,flag=0;
	for(int i=0;i<len; i++){
		tong[s[i]]++;
	}
	for(int i=0;i<len; i++){
		for(int j=50; j<=140; j++){
			if(s[i]==(char)(j)){
				if(tong[j]>=2) flag=1;
				continue;
			}
			cnt+=tong[j];
		}
		tong[s[i]]--;
	}
	return cnt+flag;
}
/*ll Main2(string s){//调试时用的
	set<string> ss;
	for(int i=0;i<s.size(); i++){
		for(int j=i+1; j<s.size(); j++){
			swap(s[i],s[j]);
			ss.insert(s);
			swap(s[i],s[j]);
		}
	}
	return ss.size();
}*/
int main(){
	string s;
	cin>>s;
	cout<<Main1(s);
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc345_c)

## 思路

数据范围 $2\le |S|\le 10^6$，所以 $\mathcal{O}(|S|^2)$ 的做法显然行不通。我们考虑数学做法。

读入数据后记录每个字符出现的数量。如果有一个字符出现过两次，那么这个串就能通过一次交换变为自身，记录个数 $+1$。

我们再次循环，当前位置可交换的数量就为**这位以后的与这位字符不同**的其他字符的数量，如：``abc`` 取第一位时 $\rightarrow$ ``bac``，``cba``；取第二位时 $\rightarrow$ ``acb``。

时间复杂度为 $\mathcal{O}(|S|)$ 级别，足以通过此题。

- 结果最大为 $\sum_{i=1}^{10^6}i$，记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;
ll n,ans,ok,tom[30];
int main(){
	cin>>s;
	n=s.size();
	for(int i=0;i<n;++i){
        ++tom[s[i]-'a'];
		if(tom[s[i]-'a']>1)ok=1;
	}
	for(int i=0;i<n;++i){
		--tom[s[i]-'a'];
		for(int k=0;k<26;++k){
			if(s[i]-'a'!=k)ans+=tom[k];
		}
	}
	cout<<ans+ok;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/151231289)

---

## 作者：__Dist__ (赞：0)

#### 翻译

给你一个字符串 $s$。你可以对这个字符串进行一次操作。

- 设 $n$ 是 $s$ 的长度。选择一对整数 $(i,j)(1 \le i \lt j \le n)$，交换 $s_i, s_j$。

问有交换出来的字符串有多少个不同的。

#### 思路

暴力会 TLE。

考虑从前往后枚举 $j$，对于每个 $1\le i \lt j$，如果 $s_i \ne s_j$，那么交换 $i, j$ 就可以获得一个新字符串。

最后，如果 $s$ 中有任意 $2$ 个相同的字符，那么交换这两个字符就可以得到原字符串，答案 $+1$。

```cpp
#include <bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long
using namespace std;
const int MAXN = 1e5 + 5;
ll read() {
    ll x = 0, f = 1;char ch = gt();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1;ch = gt();}
    while (ch >= '0' && ch <= '9') {x *= 10;x += ch - '0';ch = gt();}
    return x * f;
}

char s[1000005];
ll num[250];

int main() {
    cin >> s;
    ll len = strlen(s);
    ll res = 0;
    num[s[0]]++;
    for (int i = 1; i < len; i++) {
        res += i - num[s[i]];
        num[s[i]]++;
    }
    for (int i = 'a'; i <= 'z'; i++) {
        if(num[i] >= 2) {
            ++res;
            break;
        }
    }
    cout << res << '\n';
    return 0;
}
```

---

## 作者：Kyl_in_2024 (赞：0)

### 前言

赛时 `B` 死了去调 `C`，`C` 也死了，然后 `B` 就做出来了。然后五分钟 `C` 也好了。~~队友祭天法力无边。~~

### 题目大意

给你一个字符串，求出进行一次 `swap` 操作能得到多少个不同的字符串。

### 做法

建立一个记录字母出现了多少次的数组，然后遍历字符串 $S$。因为假设 $s_{i}$ 是字符串的第 $i$ 个字母，那么它可以得到的答案肯定是在它之前与它不相同的字母数量。注意，如果在它之前有和它一样的字母，那么最终答案要 `+1`，因为不变也是一种答案，但是只能加一次。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int a[26];
signed main(){
	string s;
	cin >> s;
	long long ans=0;
	bool is=0;
	for(int i=0;i<s.size();i++){
		for(int j=0;j<26;j++){
			if(j!=s[i]-'a') ans+=a[j];
			if(a[s[i]-'a']) is=1;
		}
		a[s[i]-'a']++;
	}
	cout<<ans+is;
    return 0;
} 
```

[AC 记录](https://atcoder.jp/contests/abc345/submissions/51303551)

---

## 作者：_shine_ (赞：0)

首先可以发现，定义两个变量 $i,j\left(i<j\right)$，则在 $s_i\ne s_j$ 的情况下 $s_i$ 与 $s_j$ 交换必定会成为一种方法。

那对此不妨记录下每一个字符的出现次数 $p_i$，那么同步对于字符 $s_j$，则答案为 $j-p_{s_j}+1$（因为不能重复计算，所以只能让 $j$ 前面的跟其进行计算）。

但这显然是连样例都过不了，因为最后还有一种情况（交换两个字符一样的），加上判断即可通过。

注意开上 ```long long```。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define lx first
#define ly second
#define int long long
string s;int ans;map<char,int>p;
map<char,int>vis;bool flag=false;
signed main(){
	cin >> s;
	for(int i=0;i<s.size();++i){
		p[s[i]]++,ans+=i+1-p[s[i]];
		if(p[s[i]]>1 && flag==false)flag=true,ans++;//判断是否有两个相等的字符，但只能加一次。
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：coderJerry (赞：0)

### 题目描述：[传送门](https://www.luogu.com.cn/problem/AT_abc345_c)
### 题目分析
任选两个字符，就有 $C_n^2$ 种选择。考虑重复情况。如果每个字符都不同，那就是 $C_n^2$ 种。一旦遇到重复，我们就这样计算：设当前字符出现次数为 $x$，则显然重复了 $C_x^2$ 个。最后，别忘了加上一种（这一种是交换重复字符之后原来整个字符串不变的情况）。
### AC 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int cnt[3000010];//cnt 数组用于储存每种字符出现次数
int sol(int x){return x*(x-1)/2;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	string s;
    cin>>s;
    int n=s.size();
    int ans=sol(n);
    for(int i=1;i<=26;i++) cnt[i]=0;
    for(int i=0;i<n;i++){
        int asc=(int)(s[i]-'a')+1;
        cnt[asc]++;
    }
    bool flag=true;
    for(int i=1;i<=26;i++){
        ans-=sol(cnt[i]);
        if(cnt[i]>1) flag=false;
    }//判断是否有重复字符
    if(flag) cout<<ans<<endl;
    else cout<<ans+1<<endl;
	return 0;
}
```

---

## 作者：xxboyxx (赞：0)

### 题意

给一个字符串，交换任意两个位置，不能是同一个位置，仅能操作一次，问交换后有多少种不同的字符串。

### 思路

如果交换的两个字符是一样的话，那么将不会有变化，要满足这种情况，需要序列中有两个字符相同。

如果交换的两个字符不是一样的话，那么能与其交换的就是与其不一样的字符，为了避免重复计算，就只能计算这一位前面的。

下面是 ```aabb``` 的示意图。

![](https://cdn.luogu.com.cn/upload/image_hosting/r3dqyfzd.png)

当然还要加上交换的两个字符是一样的情况，所以答案是 $5$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int l,ans=0,flag=0;
int a[1000005];
int b[1000005];
signed main()
{
	cin>>s;
	l=s.length();
	for (int i=0;i<l;i++)
	{
		b[s[i]]++;//统计之前的这个字符存在的次数 
		a[i]=i+1-b[s[i]];//排除相同的且为之前的 
		if (b[s[i]]>1)//标记一下，判断是否能够使交换的两个字符是一样的 
			flag=1;
	}
	for (int i=0;i<l;i++)
		ans+=a[i]; 
	cout<<ans+flag;
	return 0;
}
```

---

## 作者：smart_kai (赞：0)

#### 提示
---
注意到只能交换一次，那么只有交换不同的字符才能算作不同的方案。

#### 实现方法
---
统计每个字符出现次数，然后用两次循环扫，只要两个字符不相同，那么就可以交换，计入答案，答案加上两字符各自出现次数的积。

#### 注意
___
 - 由于答案记录了两次，所以答案最终需要除以 $2$。
 - 如果有一个字符出现了至少 $2$ 次，那么交换这个字符的任意两个位置相当于**不进行交换**，答案需要加 $1$。
 
 #### 代码实现
 ___
 核心代码如下。
 ```cpp
ll ans, tmp, cnt[30];

void solve()
{
    string s;
    cin >> s;
    for (auto x : s)
        cnt[x-'a']++;
    for (int i=0; i<26; i++)
        if (cnt[i]>1) 
          tmp = 1;
    for (int i=0; i<26; i++)
        for (int j=0; j<26; j++)
            if (i!=j)
              ans += cnt[i] * cnt[j];
    cout << ans/2+tmp;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

首先交换相同字符不改变字符串形态，那么就先统计是否有相同字符。

交换不同字符容易证明不同操作后字符串各不相同。

用前缀和或后缀和维护 $i+1$ 到 $n$ 中与 $i$ 位置字符不同的数量。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char ch[1000010];
int vis[1000010][27],ans,n;
signed main(){
	scanf("%s",ch+1);
	n=strlen(ch+1);
	for(int i=1;i<=n;i++){
		memcpy(vis[i],vis[i-1],sizeof vis[i]);
		vis[i][ch[i]-'a']++;
	}
	bool op=0;
	for(int i=1;i<=n;i++){
		int pos=ch[i]-'a';
		if(vis[n][pos]>vis[i][pos])op=1;
		ans+=n-i-(vis[n][pos]-vis[i][pos]);
	}
	printf("%lld\n",ans+op);
	return 0;
}
```

---

## 作者：Escapism (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc345_c)

## 题意

给定一个字符串，问将这个字符串中的两个字符交换位置，可以得到几个不同的字符串。

## 思路

设字符串的长度为 $n$，那么一共可以交换出 $\dfrac{n(n-1)}{2}$ 个字符串。

显然，如果我们选择两个相同的字符交换，得到的结果与原字符串相同，所以我们要减去这种情况。假设在这个字符串中，某种字符有 $m$ 个，那么我们将两个这种字符交换得出的字符串有 $\dfrac{m(m-1)}{2}$ 个，我们要把它们删除。

最后，如果出现了有两个以上的相同字符的情况，那么意味着交换得出的字符串中会有一个原字符串，我们要最后加上一个。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long a[26];//记录每种字符的数量。
int main() {
	string s;
    cin>>s;
	long long n = s.size(),ans = n * (n - 1) / 2; //计算一共可以交换得到几个字符串
	for(int i = 0; i <= n - 1; i++) a[s[i] - 'a']++; //得出每种字符的数量。
	bool f =  false;
	for(int i = 0; i < 26; i++){
		if(a[i] <= 1) continue; //如果这个字符只有一个或者没有，不对结果产生影响。
		ans -= a[i] * (a[i] - 1) / 2; //减去数量
		f = true; //是否会交换产生原字符串
	}
	if(f) cout << ans + 1;
	else cout << ans;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

简单题，注意到我们只交换一次，那么只要有两个位置不同，交换之后就不会与其他重复。

所以就相当于求满足 $i < j$ 且 $s_i \ne s_j$ 的数量，开一个桶记录一下即可。

一个小细节，就是当这个字符串出现重复字符的时候，交换两个重复字符与原串是相等的，要加上这个贡献。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
string s;
ll ans,a[30];
bool f=0;
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(a[s[i]-'a'])
		  f=1;
		ans+=i-a[s[i]-'a'];
		a[s[i]-'a']++;
	}
	write(ans+f);
	return 0;
}
```

---

## 作者：Ivan422 (赞：0)

题目大意：对字符串 $S$ 任意 $2$ 个字符调换后得出的字符串总数。

思路：首先不同的字符调换得出的一定是不同的，我们可以统计出一个字符前面的出现次数，前面有 $i$ 个字符，而与 $S_i$ 相同的有 $mp_{s_i}$ 个。那可以产生出的新字符数就是 $i-mp_{s_i}$ 个。统计出这个答案后，还要判断是否有相同字符交换，即得出的新字符串等于原字符串，如果有要记录一次。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,mp[512],ans,ad,r;
string s;
signed main(){
    cin>>s;n=s.size();
    for(int i=0;i<n;i++){
        mp[(int)s[i]]++; // 记录字符个数
        ad=(i+1-mp[(int)s[i]]); // i 从 0 开始，要加 1
        ans+=ad;
        //cout<<ad<<endl;
    }
    for(int i=97;i<=122;i++){if(mp[i]>1){r=1;}} // 相同的原字符串
    cout<<ans+r;
    return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc345_c)

## 思路

- 我们首先考虑整个字符串的**所有字母都不相同**的情况，那么此时第 $i$ 个字符可以与第 $i+1$ 到最后一个的字符中，任意一个字符进行交换，也就是说当第 $i$ 个字符作为交换的左点时，一共就会产生 $n-i$ 种不一样的字符串，我们进行累加即可。

- 如果字符串中**有字母相同**的情况时，这两个字母如果进行交换，跟原来的字符串是没有区别的，但是这也算是一种情况。而因为我们只能**将这种情况当作一种**，所以我们需要**先进行处理**，同时在计算答案时**进行特判**，这样本道题就结束了。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int t[30];

int main(){
	string s;
	cin >> s;
	for(int i = 0; i < s.size(); i++)t[s[i] - 'a' + 1]++;//桶中计算每个字母出现的个数
	int cnt = 0;
	for(int i = 1; i <= 26; i++){
		if(t[i] > 1)cnt = 1;//字符串中出现了字母相同的情况
	}
	long long ans = 0;
	for(int i = 0; i < s.size(); i++){
		t[s[i] - 'a' + 1]--;//以第 i 个点为左点，只能在它的右区间中去找，因此每次需要删去当前的字母
		long long sum = 0;
		for(int j = 1; j <= 26; j++){
			if(s[i] - 'a' + 1 != j)sum += t[j];//如果字母不相同，则可以更新，否则跳过
		}
		ans += sum;
	}
	cout << ans + cnt << endl;
}
```

---

