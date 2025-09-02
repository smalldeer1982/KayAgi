# [ABC375D] ABA

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc375/tasks/abc375_d

英大文字からなる文字列 $ S $ が与えられます。

整数の組 $ (i,\ j,\ k) $ であって、以下の条件をともに満たすものの個数を求めてください。

- $ 1\ \leq\ i\ <\ j\ <\ k\ \leq\ |S| $
- $ S_i $, $ S_j $, $ S_k $ をこの順に結合して得られる長さ $ 3 $ の文字列が回文となる
 
ただし、$ |S| $ は文字列 $ S $ の長さ、$ S_x $ は $ S $ の $ x $ 番目の文字を指します。

## 说明/提示

### 制約

- $ S $ は長さ $ 1 $ 以上 $ 2\ \times\ 10^5 $ 以下の英大文字からなる文字列
 
### Sample Explanation 1

$ (i,\ j,\ k)\ =\ (1,\ 2,\ 4),\ (1,\ 3,\ 4),\ (3,\ 4,\ 5),\ (3,\ 4,\ 6),\ (3,\ 5,\ 6) $ が条件を満たします。

## 样例 #1

### 输入

```
ABCACC```

### 输出

```
5```

## 样例 #2

### 输入

```
OOOOOOOO```

### 输出

```
56```

## 样例 #3

### 输入

```
XYYXYYXYXXX```

### 输出

```
75```

# 题解

## 作者：Anins (赞：5)

## [ABA](https://www.luogu.com.cn/problem/AT_abc375_d)

### 题意：

给定字符串 $S$，问有多少个三元组 $(i,j,k)$ 满足 $1 \le i < j < k \le |S|$ 且 $S_i$，$S_j$，$S_k$ 顺次连接构成回文串。

### 思路：

因为长度是 $3$，所以只要首尾一样就是回文串。

- 讨论一个位置对答案的贡献
  
  设 $np$ 表示我们现在讨论的位置，$p[k][i]$ 表示字母 $k$ 在第 $i$ 次出现时所处位置下标，$c[k][np]$ 表示字母 $k$ 在 $np$ 之前出现了几次。

  那么一个字母 $k$ 对答案的贡献就是它前面与它相同的字母与它之间包含的字符个数之和（满足首尾相同，中间字符任选），形式化的表示为：$\sum\limits_{i=1}^{c[k][np]}(np-p[k][i]-1)$，化简后为：$c[k][np] \times (np-1) - \sum\limits_{i=1}^{c[k][np]}p[k][i]$。

- 推广计算

  从前向后计算每个位置贡献，可以省略表示位置的一维。另外可以通过前缀和维护，即 $sum[k]$ 表示字母 $k$ 截至现在的 $\sum\limits_{i=1}^{c[k][np]}p[k][i]$ 的值。

#### 注意：
答案超过 int 范围，需要开 long long。

#### 时间复杂度：
计算一个字母贡献为 $O(1)$，总复杂度为 $O(|S|)$。

### 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll ans, sum[27], cnt[27];
char c;
int main() {
	for(int i=1;;i++) {
		c=getchar();
		if(c<'A'||c>'Z') break; 
		ll k=c-'A';
		ans+=cnt[k]*(i-1)-sum[k];
		sum[k]+=i;
		cnt[k]++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：4)

十分简单的计数题。

容易发现所谓长度为 $3$ 的回文串其实就是要找两个相同的字符。所以我们不妨对字符串的每一位分别考虑，计算以这一位为中心的回文串的个数。

对于当前的这一位，我们枚举 $26$ 个字母，计算每个字母作为回文串两端的元素，这一位为中间的元素时对答案产生的贡献。具体的，我们对每个字母分别维护一个从前往后和从后往前的前缀和，分别设为 $sum$ 和 $rsum$。设当前为中间的这一位下标为 $i$，由乘法原理易得字母 $c$ 对 $i$ 的贡献显然就是 $sum_{c,i-1}\cdot rsum_{c,i+1}$。

累加答案即可。

[提交记录](https://atcoder.jp/contests/abc375/submissions/58691449)

---

## 作者：small_lemon_qwq (赞：2)

对于三元组 $(i,j,k)$ 只需要让 $i<j<k$ 且 $S_i=S_k$ 即可。

那么对于 $S_i=S_j$ 对答案有 $j-i-1$ 的贡献。

考虑每个 $S_j$ 的贡献：设在这之前出现了 $m$ 次和 $S_j$ 一样的字符，并且下标和为 $s$，那么 $S_j$ 的贡献就是 $m\times(j-1)-s$，动态记录即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int cnt[200],mp[200],ans;
signed main(){
	string s;
	cin>>s;
	for(int i=0;i<=s.size()-1;i++){
		ans+=cnt[s[i]]*(i-1)-mp[s[i]];
		mp[s[i]]+=i;
		cnt[s[i]]++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Liuhy2996 (赞：1)

## 思路
枚举中间的点和两边的字母，维护两边每个字母的数量。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e3+10;
int n,ans,a[N],b[N];
string s;
signed main(){
	cin>>s; n=s.size(); s=' '+s;
	for(int i=1;i<=n;++i) ++b[s[i]];
	for(int i=1;i<=n;++i){ // 枚举中间点
		++a[s[i-1]],--b[s[i]]; // 维护两边字母数量
		for(int j='A';j<='Z';++j) ans+=a[j]*b[j];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Frictional (赞：1)

## 题意
给定一个序列，求序列中长度为 3 的回文子序列个数。
## 解法
因为是长度为 3 的，所以只要保证头尾相同，中间的只要在头尾中间任选就可以了。所以问题就转换成了找每一对相同的数，并计算下标的差减一（就是中间有多少个数）然后求和。

我们来考虑序列中的一个数 $a_i$，那它的下标要加多少次呢？是不是就是 $j<i,a_j=a_i$ 的合法 $j$ 的数量。那它要减多少次呢，是不是就是 $j>i,a_j=a_i$ 的合法 $j$ 的数量，这样我们知道了这个数的下标要加多少次，减多少次，是不是就可以计算了（当然不是直接用下标乘次数，因为求和的是下标差值减一，所以还有一些细节，不细说了）。

另外，$|S|\leq 2\times 10^5$ 且只有 26 个字符，所以完全可以暴力存储在某个位置之前或之后所有字符的出现次数。
## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define db double
#define U unsigned
#define int long long
#define P pair<int,int>
#define pb push_back
#define MP make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define ROF(i,a,b) for(int i=a;i>=b;--i)
#define debug(x) cerr<<#x<<'='<<x<<endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define pcn putchar('\n')
#define pcs putchar(' ');
#define pc putchar
#define File(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
#define ClockB clock_t start,end; start = clock();
#define ClockE end = clock(); cerr<<"time = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
using namespace std;
int _=1;
inline int rd(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
inline void wr(int x){
    if(x<0) pc('-'),x=(~x)+1;
    if(x>9) wr(x/10);
    pc((x%10)^48);
}
const int N=2e5+5;
char s[N];
int cntq[N][30],cnth[N][30];
int ans;
int len;
signed main(){
    // _=rd();
    while(_--){
        scanf("%s",s+1);
        len=strlen(s+1);
        FOR(i,1,len){
            FOR(j,0,25) cntq[i][j]=cntq[i-1][j];
            cntq[i][s[i]-'A']++;
        }
        ROF(i,len,1){
            FOR(j,0,25) cnth[i][j]=cnth[i+1][j];
            cnth[i][s[i]-'A']++;
        }
        FOR(i,1,len){
            ans+=(i-1)*cntq[i-1][s[i]-'A'];
            ans-=i*cnth[i+1][s[i]-'A'];
        }
        cout<<ans;
    }
    return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 题目大意

给定一个字符串，要求你选出几个字母，让他们凑起来是一个回文串。

### 思路

首先考虑定住中间点，然后枚举 $26$ 个字母，看一下当前点左边或者右边分别有多少个这个字母，然后乘法原理相乘就行了。

至于怎么快速求出到底有多少个，可以使用前缀和处理。

时间复杂度：$\Theta(n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long mp[26][200010];
int main(){
	string s;
	cin >> s;
	s = ' ' + s;
	for (char i = 'A'; i <= 'Z'; i ++ ){
		mp[i - 'A'][0] = 0;
	}
	for (long long i = 1; i < s.size(); i ++ ){
		for (char j = 'A'; j <= 'Z'; j ++ ){
			mp[j - 'A'][i] = mp[j - 'A'][i - 1];
		}
		mp[s[i] - 'A'][i] ++ ;
	}
	long long res = 0;
	for (long long i = 1; i < s.size(); i ++ ){
		for (char j = 'A'; j <= 'Z'; j ++ ){
			long long l = mp[j - 'A'][i - 1] - mp[j - 'A'][0];
			long long r = mp[j - 'A'][s.size() - 1] - mp[j - 'A'][i];
			res += l * r;
		}
	}
	cout << res;
	return 0;
}
```

---

## 作者：__Allen_123__ (赞：0)

> 求出一个字符串 $s$ 中所有拼接起来为回文串的长度为 $3$ 的子序列的数量。

显然，中间的一个字符我们可以在前后两个字符之间随意选择，问题就转化为，求出以下式子的值：

$\sum\limits_{i=1}^{n-2} \sum\limits_{j=i+1}^{j\le n,s_i=s_j}(j-i-1)$

我们考虑枚举所有的 $i$，并预处理对于每个字符，所有等于这个字符的下标以及数量的后缀和，设它们分别为 $sum$ 和 $cnt$。

则对于每个下标，其对答案的贡献为：$sum_{i+1}-cnt_{i+1}\times (i+1)$，原因显然。

通过这种方法即可通过此题。

[AC 记录](https://atcoder.jp/contests/abc375/submissions/58691306)。

---

## 作者：201012280925LSY (赞：0)

## 题目大意
给你一个长度为 $N$ 的字符串 $S$（$N$ 是题面中的 $|S|$），求符合要求的下标三元组（$i$，$j$，$k$）的个数，使得：

- $1 \le i < j < k \le N$
- $S_i=S_k$
## 思路
注意到字符串 $S$ 是由大写字母组成的，同时 $N \le 2 \times 10^5$，所以容易想到枚举中间的 $S_j$，再计算两边的相同字母的个数。预处理出每一个字母出现次数的前缀和即可。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
long long sum[27][200010],answer;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>st;
	for(int i=0;i<st.size();i++)
	{
		sum[st[i]-64][i]++;//前缀和
		for(int j=1;j<=26;j++)
		sum[j][i]+=sum[j][i-1];
	}
	for(int i=1;i<st.size()-1;i++)
	{
		for(int j=1;j<=26;j++)//枚举两边相同的是什么字母
		{
			 answer+=sum[j][i-1]*(sum[j][st.size()-1]-sum[j][i]); 
		} 
	}	 
	cout<<answer;
	return 0;
}

```
[记录](https://atcoder.jp/contests/abc375/submissions/58803188)

---

## 作者：hzxphy (赞：0)

## Deepl 翻译
给你一个由大写英文字母组成的字符串 $S$。

求满足以下两个条件的整数三元组 $(i,j,k)$ 的个数：

1. $1\le i<j<k\le \left\vert S\right\vert$
2. 由 $S_i$、$S_j$ 和 $S_k$ 按此顺序连接而成的长度为 $3$ 的字符串是一个回文字符串。
## 思路
我们把相同的纪录成一个数组。

可知只取 $S_i,S_k$ 有 $C^{\left\vert c\right\vert}_{\left\vert c\right\vert-1}$ 种情况。（其中 $\left\vert c\right\vert$ 表示字符 $c$ 的总数）

显然，每种情况的 $S_j$ 可行数是不同的。

首先，有重复的。

其次，通过 $sum_i\gets$ 以 $i$ 结尾的总数。

可知 $sum_i=sum_{lst_i}+(i-lst_i)*(\left\vert S_i\right\vert)$。其中 $lst_i$ 表示上一个 $S_i$ 的位置。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
vector<int> c[26];
int lst[200001];
long long sum[200001];
int main(){
    cin>>s;
    int n=s.size();
    s=' '+s;
    for(int i=1;i<=n;i++){
        if(c[s[i]-'A'].size())
            lst[i]=c[s[i]-'A'][c[s[i]-'A'].size()-1],
            sum[i]=sum[lst[i]]+(i-lst[i])*((int)c[s[i]-'A'].size())-1;
        else lst[i]=0;
//        cout<<sum[i]<<"***\n";
        c[s[i]-'A'].push_back(i);
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(c[s[i]-'A'].size()&&c[s[i]-'A'][0]==i){
            for(int j=1;j<(int)c[s[i]-'A'].size();j++){
                ans+=sum[c[s[i]-'A'][j]];
            }
        }
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：liuziqin (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc375_d)

## 题目简述

给定一个字符序列 $S$ ，求出里面回文三元组的数量。

## 思路

由于三元组 $(i,j,k)$ 是回文的，所以 $S_i=S_k$ ，因此考虑枚举 $j$ ，用**乘法原理**计算出当前三元组数量。

我们预处理出每一种字符的**前缀和**和**后缀和**，最后统计答案时计算贡献即可。

## Code

```c++
#include<bits/stdc++.h>
#define int long long 
using namespace std;
string s;
int hd[30][200005],tl[30][200005];
signed main(){
	cin>>s;
	int n=s.size();
	for(int i=0;i<n;i++){
		for(int j=0;j<26;j++)hd[j][i+1]=hd[j][i];
		hd[s[i]-'A'][i+1]++;//前缀和
	}
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<26;j++)tl[j][i+1]=tl[j][i+2];
		tl[s[i]-'A'][i+1]++;//后缀和
	}
	int ans=0;
	for(int i=2;i<n;i++){
		for(int j=0;j<26;j++)ans+=hd[j][i-1]*tl[j][i+1];//计算答案
	}
	cout<<ans<<"\n";//输出
	return 0;
}
```

---

## 作者：XCDRF (赞：0)

# ABC375D ABA 题解

[原题传送门](https://www.luogu.com.cn/problem/AT_abc375_d)

[更好的阅读体验](https://www.luogu.com.cn/article/p4loflwb)

## 题目大意

给定一个由大写字母组成的字符串，求出长度为三的回文子串的个数。

## 解题思路

看到题后，首先想暴力做法。

通过一个三层的枚举来确定回文子串，然后每个判一遍回文。

复杂度 $O(n^3)$，看数据范围，显然超时。

再想一想，一个回文串，第一个和最后一个字母肯定是一样的，中间的可以任取。所以只需要对每个字母记录出现的次数和位置，如果一个字母出现了两次以上，答案就加上任意两个出现位置间的字母个数。

复杂度 $O(n^2)$，还是会超时。

如何优化？

我们把一个字母的每个出现位置看做一个序列，则我们要求的东西就是这个：

$$
S = \sum_{1 \le i < j \le n} (a_j-a_i-1)
$$

将上式进行拆分，得到：

$$
S = \sum_{1 \le i < j \le n} a_j - \sum_{1 \le i < j \le n} a_j - \sum_{1 \le i < j \le n} 1
$$

我们知道，枚举任意两个数总共需要枚举 $\frac{n (n-1)}{2}$ 次，所以要减 $\frac{n (n-1)}{2}$ 个 $1$。

所以通过进一步化简，可得：

$$
S = \sum_{j=2}^{n} (j-1) \cdot a_j - \sum_{i=1}^{n-1} (n-i) \cdot a_i - \frac{n (n-1)}{2}
$$

对于每一个字母，算出一个和，最后累加起来即可，时间复杂度来到了 $O(n)$，问题得解。

## 注意事项

1. 用前缀和每次计算完上述式子后记得把变量清零。
2. 如果一个字母的出现次数小于两次就直接跳过。
3. 如果上述式子难以理解，不妨在草稿纸上手推一下，其实非常简单。

## 参考代码

```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int N=2e5+5;
int n,sum,pre1,pre2;
string s;
int a[30][N],cnt[N];
int dig(char s){
	return s-'A';//将字母转化为数字
}
signed main(){
	cin>>s;
	n=s.size();
	for(int i=0;i<n;i++) a[dig(s[i])][++cnt[dig(s[i])]]=i;//统计每个字母出现的个数和位置
	for(int i=0;i<26;i++){
		if(cnt[i]<2) continue;
		pre1=0,pre2=0;
		for(int j=1;j<=cnt[i];j++){
			pre1+=(j-1)*a[i][j];//算第一个式子
			pre2+=(cnt[i]-j)*a[i][j];//算第二个式子
		}
		sum+=pre1-pre2-cnt[i]*(cnt[i]-1)/2;
	}
	cout<<sum;
	return 0;
}
```

感谢管理大大审核，求通过 QwQ。

最后建议这个题评黄，毕竟套了两个优化，比较困难。

---

## 作者：Binah_cyc (赞：0)

一个简单结论题，感觉应该有不少类似的题目。

直接统计每一个字母出现次数的前缀和与后缀和，然后枚举中间的字母，因为是回文串，所以左面的字母应该等于右面的字母，根据乘法原理直接相乘统计答案即可。

代码：
```c
// Problem: D - ABA
// Contest: AtCoder - Panasonic Programming Contest 2024（AtCoder Beginner Contest 375）
// URL: https://atcoder.jp/contests/abc375/tasks/abc375_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,sum[200005][35],suf[200005][35];
string s;
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>s;
	n=s.length(),s=" "+s;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<26;j++) sum[i][j]=sum[i-1][j];
		sum[i][s[i]-'A']++;
	}
	//统计前缀和
	for(int i=n;i>=1;i--)
	{
		for(int j=0;j<26;j++) suf[i][j]=suf[i+1][j];
		suf[i][s[i]-'A']++;
	}
	//统计后缀和
	int ans=0;
	for(int i=1;i<=n;i++) for(int j=0;j<26;j++) ans+=sum[i-1][j]*suf[i+1][j];//前面的*后面的
	cout<<ans;
	return 0;
}
```

---

## 作者：cjh_trailblazer (赞：0)

[at原题面](https://atcoder.jp/contests/abc375/submissions/58819183)
## 题目分析：
注意到该回文串只与第一和第三个字符有关，我们可以统计一下相同字母出现的次数。定义 $sum[i][j]$ 表示在 $i$ 位置前，$j$ 共出现了多少次，对于 $j$ 的处理，只需要让 $s[i]-A$ 即可。  
统计答案时，让答案每次加上 $sum[i-1][j]\times (sum[len][j]-sum[i][j])$ 即可。
## [Code](https://atcoder.jp/contests/abc375/submissions/58819196)

---

