# Tandem Repeats?

## 题目描述

给定一个由**小写字母**和**问号** `?` 组成的字符串 $s$，你可以将问号 `?` 替换为任何小写字母。

替换后，你需要找到 $s$ 中最长的**重复**子串。

一个长度为 $2n$ 的字符串 $t$ 是**重复**串，当且仅当对于所有 $1 \leq i \leq n$，有 $t_i = t_{i+n}$。

## 说明/提示

对于 $100 \%$ 的数据，保证 $1 \leq t \leq 10^3, 1 \leq |s| \leq 5 \times 10^3$​。

保证 $\sum |s| \leq 5 \times 10^3$。

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
4
zaabaabz
?????
code?????s
codeforces```

### 输出

```
6
4
10
0```

# 题解

## 作者：MaxBlazeResFire (赞：16)

来个相当有趣的做法。

定义英文字母的权值为其字母表中的编号，`?` 为 $0$。两个长度相等为 $n$ 的串 $A,B$ 匹配当且仅当 

$$\displaystyle\sum_{i=1}^n(A_i-B_i)^2A_iB_i=0$$

于是记 $f_{i,j}=(s_i-s_j)^2s_is_j$，考虑枚举答案长度 $L$，那么 $[l,l+L-1]=[l+L,l+2L-1]$ 匹配就可以刻画成

$$\displaystyle\sum_{i=l}^{i+L-1}f_{i,i+L}=0$$

以长度为视角，预处理前缀和，判定 $n^2$ 次即可。复杂度 $O(n^2)$。

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 5005

int n,a[MAXN],f[MAXN][MAXN],s[MAXN][MAXN];
char S[MAXN];

inline void solve(){
	scanf("%s",S + 1); n = strlen( S + 1 );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= n ; j ++ ) a[i] = ( S[i] == '?' ) ? 0 : ( S[i] - 'a' + 1 );
	for( int i = 1 ; i <= n ; i ++ )
		for( int j = 1 ; j <= n ; j ++ ) f[i][j] = ( a[i] - a[j] ) * ( a[i] - a[j] ) * a[i] * a[j];
	for( int len = 1 ; len <= n ; len ++ )
		for( int i = 1 ; i + len - 1 <= n ; i ++ ) s[len][i] = s[len][i - 1] + f[i][i + len];
	int Ans = 0;
	for( int len = 1 ; len <= n ; len ++ )
		for( int l = 1 ; l + 2 * len - 1 <= n ; l ++ )
			if( s[len][l + len - 1] - s[len][l - 1] == 0 ) Ans = max( Ans , len * 2 );
	printf("%d\n",Ans);
}

signed main(){
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：DFbd (赞：14)

## 思路
这道题可以直接枚举长度，从大到小枚举，只要枚举偶数，找到重复串就直接输出长度。

接着遍历字符串，不要枚举会超边界的点，如果 $s_j$ 和 $s_{j+i/2}$ 相等或其中有至少一个 `?` 就让标记加一，否则清空标记。

如果标记到了 $i/2$ 就证明找到了重复串，输出当前长度即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
    cin >> t;
    while(t--){
        cin >> s;
        for(int i=s.size()-s.size()%2;i>=0;i-=2){
            int f=0;
            for(int j=0;j+i/2<s.size();j++){
                if(f*2==i) break;
                if(s[j+i/2]==s[j]||s[j]=='?'||s[j+i/2]=='?') f++;
                else f=0;
            }
            if(f*2==i){
                cout << f*2 << "\n";
                break;
            }
        }
    }
    return 0;
} 
```

---

## 作者：Robin_kool (赞：4)

直接讲正解。单次复杂度 $O(n^2)$。

考虑从大到小枚举长度（记作 $len$，方便直接结束），然后枚举起点（设为 $i$）,判断 $s_i$ 和 $s_{i+len}$ 是否满足条件：

+ 如果其中存在至少一个问号，肯定是可以匹配的。

+ 没有问号的情况下当且仅当两个字符原来就相等。

能 $O(n)$ 处理出每个位置是否可以匹配。

然后做一个最大平台长度，就好了。

```cpp
//#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool p[5010];
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline void solve(){
	string s;
	cin >> s;
	int n = s.size(), ans = 0;
	s = "~" + s;
	for(int i = n / 2; i >= 1; -- i){
		for(int j = 1; j <= n - i + 1; ++ j){
			p[j] = (s[j] == s[j + i] || s[j] == '?' || s[j + i] == '?');
		}
		int cnt = 0, now = 0;
		for(int j = 1; j <= n - i + 1; ++ j){
			if(!p[j]) now = max(now, cnt), cnt = 0;
			else ++ cnt;
		}
		now = max(now, cnt), now = min(now, i);
		if(now == i){
			write(i * 2), putchar('\n');
			return;
		}
	}
	puts("0");
}
signed main(){
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
    int T = read();
    while(T --) solve();
	return 0;
}


```

---

## 作者：Drind (赞：4)

### 题目解析

求最长的子序列满足前半段等于后半段，原序列存在通配符。

我们乍一看就能得到一个 $O(n^3)$ 的暴力，但是没法通过这题啊。所以我们考虑优化，发现他的状态最多只有 $n^2$ 个，就是枚举起点和长度而已，所以我们考虑 dp。

设 $f_{i,j}$ 代表起点为 $i$ 和 $j$ 的最长相等子序列长度。转移就是 $s_i=s_j,f_{i+1,j+1}+1\to f_{i-1,j-1}$.

然后枚举即可，如果 $f_{i,j} \ge j-i+1$ 则合法。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10;

int dp[N][N];

inline void fake_main(){
	string s; cin>>s;
	for(int i=s.size()-1;i>=0;i--){
		for(int j=s.size()-1;j>i;j--){
			if(s[i]==s[j]||s[i]=='?'||s[j]=='?'){
				if(i==s.size()-1||j==s.size()-1) dp[i][j]=1;
				else dp[i][j]=dp[i+1][j+1]+1;
			}
			else dp[i][j]=0;
			//cout<<i<<" "<<j<<" "<<dp[i][j]<<"\n";
		}
	}
	int ans=0;
	for(int i=0;i<s.size();i++){
		for(int j=0;j<s.size();j++){
			if(dp[i][j]>=j-i) ans=max(ans,j-i);
		}
	}
	cout<<ans*2<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：hgckythgcfhk (赞：2)

一个玄学做法和关于 ```char``` 数组和 ```string``` 的对比。

枚举长度和左端点，对于每个长度和左端点 $O(n)$ 的检查，发现这个做法很难卡到上界，具体的，当且仅当一个所有字符相同，然后吧正中间往左或右偏一个位置起的连续 $3$ 个字符改成互不相同且和原串其他字符互不相同的字符才会达到一个带有严格小于 $\frac{1}{16}$ 常数的上界，所以在本题的数据范围内，最终时间严格小于 $\frac{(5000-3)^3}{16}=7798445935\le 8\times 10^9$ 看上去还是很大，但实际上，可以造这样一组数据试试，开一个变量记录循环次数，发现是严格小于 $1.5\times 10^9$ 的。时限 $2$ 秒，卡卡常能过。

但我在提交的时候遇到了一个离谱的问题，极端数据下，```char``` 数组在本地 $2.9s$，```string```本地 $16s$，手动开 O2 后 ```char``` 数组无明显变化，```string``` 本地 $11s$，但提交的时候 ```string``` 过了而 ```char``` 数组即使为了减少循环次数放弃一部分正确性还是没过，说明在 CF 测评机上就不要偷懒了，还是得乖乖的用 ```string```。

对比： [```char```](https://codeforces.com/contest/1948/submission/252401178)   [```string```](https://codeforces.com/contest/1948/submission/252410472)

---

## 作者：aeiouaoeiu (赞：1)

看到最大长度，我们直接枚举这个长度 $d$！

为了方便，我们令长度是 $2d$，这样对于 $s(l,l+2d-1)$，我们需要满足 $\forall l\le i\le l+d-1,s_i=s_{i+d}$。

考虑 $l$ 自增 $1$ 时判断情况的变化。$s_l=s_{l+d}$ 的判断被舍弃了，$s_{l+d}=s_{l+2d}$ 的判断被加进来了。

所以我们从大到小枚举 $d$，从小到大枚举 $l$。每一次处理完新加进来的判断和被舍弃的判断，就看成立的判断数量是否等于 $d$，如果是，那么此时的 $s(l,l+2d-1)$ 就是合法的，直接输出 $2d$。

时间复杂度：$\mathcal O(n^2)$。
```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=2007,ee=1000000000000000007ll;
ll n;
string s;
bool cmp(char a,char b){
	if(a=='?'||b=='?') return 1;
	return (a==b);
}
ll solve(void){
	ll cnt=0;
	for(int d=(n>>1);d>=1;d--){
		cnt=0; for(int i=1;i<=d;i++)if(cmp(s[i],s[i+d])) cnt++; if(cnt==d) return d*2;
		for(int j=2,k;j+d*2-1<=n;j++){
			k=j+d*2-1;
			if(cmp(s[j-1],s[j+d-1])) cnt--; if(cmp(s[k],s[k-d])) cnt++;
			//cout<<j<<" "<<k<<" "<<cnt<<"\n";
			if(cnt==d) return d*2;
		}
	}
	return 0;
}
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll Tccs=1;
	cin>>Tccs;
	for(int tcs=1;tcs<=Tccs;tcs++){
		cin>>s,n=s.length(),s=" "+s;
		cout<<solve()<<"\n";
	}
	return 0;
}
```

---

## 作者：Shunpower (赞：1)

不是啊我草，这玩意我是真想不到。

我是只会做 tricky 题的彩笔小哥哥呗/kel

--------

发现 `?` 很麻烦不方便我们做匹配，但是我们可以枚举一对 $(i,j)$ 并考察这对 $(i,j)$ 是否有可能匹配上。显然匹配不上当且仅当 $s_i\neq s_j$ 并且 $s_i,s_j$ 都不是问号。

你考虑这个 tandem repeat 子串的中间位置 $mid$，也就是第一段重复部分的结尾字符。可以发现 $(i,j)$ 不可能匹配上相当于对所有 $mid\in [i,j]$ 它们的 $r$（子串末尾）的选择存在一个制约：$mid-i\neq r-j$。移项为 $r-mid\neq j-i$ 之后可以发现，它相当于要求 $[i,j]$ 中的所有 $mid$，以其作为 $mid$ 的 tandem repeat 子串的一段重复部分的长度不能是 $j-i$。

那么现在相当于有若干个限制，每个限制制约一段连续区间上都不能取某个数，最后我们想查询出每个位置 $i$ 上可取的 $\leq \min(n-i,i)$ 的最大数。把这些最大数再取一次最大乘 $2$ 就是答案。这个问题显然可以先枚举 $(i,j)$ 得到限制，再把限制离线下来，维护一个桶从左到右扫一遍就行了。

总时间复杂度 $\mathcal O(n^2)$。注意离线限制的时候不能用 `vector`，不然你会像我一样 MLE on test #10 然后下大分。

代码：[link](https://codeforces.com/contest/1948/submission/251602633)

---

## 作者：haokee (赞：1)

## 思路

首先我们可以很轻松地写出一个 $\mathcal O(n^3)$，大约就是先枚举左边界，然后用两个 vector 模拟子串两边的数字，再用一个循环判断是否相等。但是这样子会超时。我们发现判断字符串相等很慢，因此可以加入一个很简单的优化：如果当前产生的答案不会更优的话就不判断。时间复杂度为 $\mathcal O(|s|^2)$。

## 代码

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int t, head, ans;
string s;
vector<int> l, r;

bool check() {
  for (int i = 0; head + i < r.size(); i++) {
    if (l[i] != r[head + i] && l[i] != '?' && r[head + i] != '?') {
      return 0;
    }
  }
  return 1;
}

int main() {
  for (cin >> t; t; t--) {
    cin >> s, ans = 0;
    for (int i = 0; i < s.size(); i++) {
      head = 0, l.clear(), r.clear();
      for (int j = i + 1; j < s.size(); j += 2) {
        r.push_back(s[j - 1]), r.push_back(s[j]);
        l.push_back(r[head]), head++;
        j - i + 1 > ans && check() && (ans = max(ans, j - i + 1));
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
若字符串 $A$ 可通过删除任意长的前、后缀（也可以不删除）变为字符串 $B$，则称 $B$ 为 $A$ 子串。

若对于字符串 $A$ 有 $A_i=A_{i+\frac{|A|}{2}}(1\le i\le\frac{|A|}{2},|A|\equiv0\pmod2)$，则称其为重复串。

给定字符串 $S$，其由小写字母及 `?` 组成，而 `?` 可被替换为任意小写字母，问 $S$ 的最长重复子串长度。
# 思路
不难想到暴力枚举重复子串，枚举子串的时间复杂度是 $O(n^2)$，然后还有判断其是否为重复串然后时间复杂度来到 $O(n^3)$。

写了一版，优化了，总体优化的思路是每次只枚举长度大于已有答案的子串。然后没过，又想到从长到短的枚举，又没过……

然后脑子堵了，看了下官方题解，发现枚举的方式还可以优化：从枚举子串的起点终点转变为枚举其长度。

这样优化的地方在于如果第一次判断了 $[l,r]$ 内 $\sum_{i=1}^{\frac{l+r}{2}}[S_i=S_{i+\frac{r-l}{2}}]$ 的数量记为 $cnt$，$cnt$ 减去 $[S_l=S_{l+\frac{r-l}{2}}]$ 加上 $[S_{l+\frac{r-l}{2}}=S_{r+1}]$ 就是比较 $[l+1,r+1]$ 时结果。

$cnt$ 的含义相信不用多说，只要 $cnt=r-l$ 即子串为重复串。而这里特殊的枚举方式让 $cnt$ 的计算变成了类似滑窗的计算方式，让时间复杂度降到了 $O(n^2)$。同时的，这种特殊的枚举方式也让我们不必再比较大小，我们可以从大到小枚举长度，输出第一次找到的重复子串的长度即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5;
int t,n,ans,cnt;
char s[N];
main(){
	scanf("%d",&t);
	while(t--){
		ans=0;
		scanf("%s",s+1);
		n=strlen(s+1);
		for(int len=n/2;len;len--){
			cnt=0;
			for(int i=1;i<=n-len;i++){
				cnt+=(s[i]==s[i+len]||s[i]=='?'||s[i+len]=='?');
				if(i>len)cnt-=(s[i]==s[i-len]||s[i]=='?'||s[i-len]=='?');
				if(i>=len&&cnt==len){
					ans=len;
					cnt=-1;
					break;
				}
			}
			if(cnt<0)break;
		}
		printf("%d\n",ans+ans);
	}
}
```

---

## 作者：liluhexuan (赞：0)

这道题其实用一个很简单的枚举就能过。

我们可以枚举重复子串长度，然后看 $s_i$ 和 $s_{i+n}$（$s$ 为字符串）是否相等 $^*$，如果相等，那就把 $a_i$（$a$ 为一个数组）设为 $1$，否则设为 $0$。然后找连续 $1$ 的个数的最大值，如果它小于刚才枚举的字符串长度，那就跳过，否则就找到最大的字符串长度（最大的 $i$）。

比如说，某个字符串为 "zaabaabz"，假如我们枚举的重复子串长度（ $i$ ）为 1 ，那么 $a$ 数组就是这样的：

`0,1,0,0,1,0,0`

而这个数组也代表：如果要找长度为 2 的重复子串，那在这个字符串中就有两个（两个 "aa"）。

因为外面枚举长度是 $O(n)$，里面处理结果又是 $O(n)$，所以这段代码的时间复杂度是 $O(n^2)$。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
char s[5010];
bool a[5010];
void slove(){
	cin>>s+1;
	int n=strlen(s+1);
	int res=0;
	for(int i=1;i<=n/2;i++){  //枚举重复子串长度
		for(int j=1;j+i<=n;j++){
			if(s[j]=='?') a[j]=1;  //判断条件
			if(s[j+i]=='?') a[j]=1;
			if(s[j]==s[j+i]) a[j]=1;
		}
		int ans=0;
		for(int j=1;j<=n;j++){ //寻找最长的连续 1
			if(!a[j]) continue;
			int sum=0;
			while(a[j]&&j<=n) sum++,j++;
			ans=max(ans,sum);
		}	
		for(int j=1;j+i<=n;j++)  //别忘了初始化
			a[j]=0;	
		if(ans<i) continue;  //这个字符串没有长度为 i 的重复子串
		else res=max(res,i);
	}
	cout<<res*2<<endl;  //别忘了乘 2
}
int main(){
	int T;  //codeforces 深爱着多组输入
	cin>>T;
	while(T--) slove();
	return 0;
}
```

$^*$ 如果 $s_i$ 为问号，或 $s_{i+n}$ 为问号，或 $s_i$ 和 $s_{i+n}$ 是同一字符 ，那我们就认为 $s_i$ 与 $s_{i+n}$ 相等。

---

## 作者：T_TLucas_Yin (赞：0)

其实这题暴力能过？

我们考虑枚举所谓“重复字符串”中**重复的那一部分**的长度 $i$。则 $i$ 最小显然为 $1$，最大即整个字符串都是重复的，此时 $i$ 为 $\lfloor \frac n 2 \rfloor$。

一个重复字符串重复的两部分总是连续的，所以对于任意 $i$，只需要遍历字符串判断每 $i$ 个字符和它后面 $i$ 个字符中对应的字母是否完全相同即可（如果某串一个位置上是 `?`，则该位置肯定相同）。

当然不是乱搞就能过的，需要增加一些小优化：

- 使用快读。
- 枚举长度时按从长到短枚举，这样一但一个长度出现了重复字符串，就能直接跳出输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
char s[5005];
int main(){
	scanf("%d",&t);
	while(t--){
		char c=' ';
		int maxn=0,n=0;
		while(!((c>='a'&&c<='z')||c=='?')) c=getchar();
		while((c>='a'&&c<='z')||c=='?') s[++n]=c,c=getchar();//以上为字符串输入 
		for(int i=n/2;i>=1;i--){//循环节长度 
			for(int j1=1,j2=1+i;j1<=n-i-(i-1);j1++,j2++){//j1为第一段字符串开头，j2为第二段字符串开头 
				bool flag=1;
				for(int k=0;k<i;k++) if(!(s[j1+k]==s[j2+k]||s[j1+k]=='?'||s[j2+k]=='?')){
					flag=0;break; }//遍历两个串看是否相同 
				if(flag){ maxn=max(maxn,i);break; }
			}
			if(maxn) break;
		}
		printf("%d\n",maxn*2);//注意答案为循环节长度*2 
	}
	return 0;
}
```

---

## 作者：truly_handsome (赞：0)

题意：给定 $T$ 组数据，每组数据包含一个字符串，你可以将其中的 `?` 替换成任意小写字母，问最长区间 $[l,r]$ 满足 $r-l+1$ 为偶且 $s_{l\dots mid} = s_{mid+1\dots r}$，其中 $mid = \frac{l+r}{2}$。

做法：首先可以枚举区间长度，然后枚举左端点，这样做的时间复杂度是 $O(n^3)$，考虑优化，发现枚举我们都要做大量的比较字符是否相等的操作，可以令 $a_i$ 代表 $s_i$ 与 $s_{i+mid}$ 是否相等，如果 $A$ 中连续出现长度大于等于 $\frac{r-l+1}{2}$ 个 $1$ 的时候就证明可以有长度为 $r-l+1$ 的区间。


```
# include <bits/stdc++.h>
using namespace std;

int n, arr[5005];

char s[5005];

void solve(){
	scanf("%s", s+1); n = strlen(s+1); int ans = 0;
	for (int ban = 1;ban*2 <= n;ban++){
		int len = ban*2, num = 0, mx = 0;
		for (int l = 1;l+ban <= n;l++){
			if (s[l] == s[l+ban] || s[l] == '?' || s[l+ban] == '?') num++;
			else num = 0;
			mx = max(mx, num);
		}
		if (mx >= ban) ans = max(ans, len);
	}	
	printf("%lld\n", ans);
}

signed main(){
	int T; scanf("%lld", &T);
	while (T--) solve(); 
	return 0;
}

```

---

## 作者：NATO (赞：0)

vp 时搞的抽象做法。

考虑我们暴力枚举查找重复串的过程。

设我们枚举的开头和 $1+n$ 分别为 $i,j(i<j)$，那么显然重复串就是要让 $s_i=s_j,s_{i+1}=s_{j+1},\dots,s_{j-1}=s_{2j-1-i}$。在这里 $=$ 既可以是真的相同，也可以是其中至少一个是问号。

于是我们想到可以用 $O(n^2)$ 的时间预处理出每两个位置是否可以匹配上，可以得到一个 $01$ 矩阵来表示匹配关系。

那么我们就把重复串的必要条件转化到了在这个 $01$ 矩阵上 $(i,j),(i+1,j+1),\dots,(j-1,2j-1-i)$ 均为 $1$，即矩阵上连续向右、向下斜着的全为 $1$ 的一段区间。

考虑按上述要求 DP 处理出以矩阵 $(i,j)$ 结尾的最长区间，转移是简单的，$(i,j)$ 为 $1$ 就 $dp_{i,j}=dp_{i-1,j-1}+1$，否则为 $0$。

最后枚举 $i,j$，若 $dp_{j-1,2j-i-1}\ge j-i$ 则说明是一组可能的重复串，取个 $\max$ 即可。

时间复杂度 $O(n^2)$。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t;
string s;
bool vis[5005][5005];
ll dp[5005][5005];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>s;
		ll n=s.size();
		for(ll i=1;i<=n;++i)
		{
			for(ll j=i+1;j<=n;++j)
				vis[i][j]=((s[i-1]==s[j-1])||(s[i-1]=='?')||(s[j-1]=='?'));
		}	
		ll maxn=0;
		for(ll i=1;i<=n;++i)
		{
			for(ll j=i+1;j<=n;++j)
			{
				if(vis[i][j])
				dp[i][j]=(dp[i-1][j-1]+1);
				else dp[i][j]=0;
			}
		}
		
		for(ll i=1;i<=n;++i)
			for(ll j=i+1;j<=n;++j)
				if(vis[i][j])
				{
					if(j+j-i-1<=n)
					if(dp[j-1][j+j-i-1]>=j-i)
					maxn=max(maxn,j-i);
				}
		cout<<maxn*2<<'\n';
	}
}
```

---

## 作者：luqyou (赞：0)

# 思路

暴力题，不妨换一种角度去思考。

我们枚举串的长度，然后从 $1$ 扫到 $n-i+1$。若有 $s_j = s_{j+i}$，则满足条件长度 $+1$，达到 $i$ 说明可行，更新答案；若 $s_j \neq s_{j+i}$ 则清空当前长度即可。

注意通配符。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5000+10;
int n,f[maxn],ans,p[maxn];
string s;
void solve(){
	ans=0;
	cin>>s;
	n=s.size(),s=" "+s;
	for(int i=1;i<=n;i++){
		int nl=0;
		for(int j=1;j+i<=n;j++){
			if(s[j]==s[j+i]||s[j]=='?'||s[j+i]=='?'){
				nl++;
			}
			else{
				nl=0;
			}
			if(nl==i){
				ans=max(ans,i);
				break;
			}
		}
	}
	cout<<ans*2<<endl;
}
signed main(){
 	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve(); 
	return 0;
}
/*
5
12 45 32 45 78
*/
```

---

## 作者：Pursuewind (赞：0)

## 题意

从 $s$ 中找出最长的一个拥有 $2$ 个循环节的字串，`?` 能当任何字符串使用。

## 解法

看到 $n \le 5000$，考虑枚举法。

枚举什么呢？

### 1. 枚举两个端点

枚举的复杂度 $O(n^2)$，判断两个字符串相等 $O(n)$，总复杂度 $O(n^3)$。

### 2. 枚举中点，再枚举长度

枚举的复杂度 $O(n^2)$，判断两个字符串相等 $O(n)$，总复杂度 $O(n^3)$。

### 3. 枚举长度，再枚举第一个端点

貌似十分可行。

因为前两种算法重复判断了许多字符之间是否相等，十分耗时。而这样的枚举算法，可以大大提高效率。

思路：

两层循环，伪代码如下：

> 首先枚举一个长度 $len$。
>
> 定义一个变量 $cnt$，当前端点为 $i$ 时表示能匹配的最大长度。
>
>> 枚举前端点 $j$。
>>> 如果 $s_j=s_{j+len}$，$cnt$ 加一。
>>>
>>> 否则 $cnt$ 清零。
>>
>> 如果有一时刻 $cnt=len$，则说明有满足要求的字串长度为 $len$，记录答案即可。

[code(by my friend - luqyou)](https://codeforces.com/contest/1948/submission/251531649)

---

## 作者：I_will_AKIOI (赞：0)

#### 前言

作者赛时使用 $n^3$ 的暴力骗分做法通过本题，由于常数极小，没有 FST，故写本篇题解表示纪念。~~其实主要是谷群里面有人说能过。~~

#### 题目大意

给你一个字符串 $s$，其中“?”表示任意字符，求一个字符串 $t$，要求 $t$ 是 $s$ 的子串，并且满足 $t$ 的前半部分等于后半部分。求 $t$ 的最大长度。

#### 赛时解法

我们想要让 $t$ 更长，我们可以把长度从大到小枚举。接下来枚举每一个区间，如果能匹配上，直接输出当前长度。

[link](https://codeforces.com/contest/1948/submission/251533085)

由于这个代码把长度从大到小枚举，所以第一个合法的长度就是答案，所以答案越大跑的越快。如果答案太小，则字符串匹配的速度会大大加快，所以答案越小跑的也越快。因此，当答案在 $2500$ 左右时，程序运行次数最多，但是可以卡过。

#### 正确解法

赛时被降智了，没能想出。

我们发现一个个匹配字符串实在太慢，我们可以直接匹配 $s_i$ 和 $s_{i+L}$，其中 $L$ 表示当前枚举的区间长度。如果匹配，那么令计数器 $+1$。否则计数器归零。这样，如果可以连续匹配 $L$ 个字符，那么说明答案合法。

```
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int solve()
{
  cin>>s;
  n=s.size();
  for(int L=n/2;L>=1;L--)//枚举长度
  {
    int len=1;
    for(int i=0;i+L-1<n;i++)
    {
      if(s[i]!='?'&&s[i+L]!='?'&&s[i]!=s[i+L]) len=0;//不合法
      len++;
      if(len==L+1) return L*2;//匹配成功
    }
  }
  return 0;
}
int main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) cout<<solve()<<"\n";
  return 0;
}
```

---

## 作者：MrPython (赞：0)

集体降智题。放普及组 t3 正合适。

根本不用字符串科技，也不用多想，`?` 只是卡掉哈希做法的。把思路画出来就一眼了：
```
zaabaabz|zaabaabz |zaabaabz  |zaabaabz   |zaabaabz     |zaabaabz
zaabaabz| zaabaabz|  zaabaabz|   zaabaabz|    zaabaabz |      zaabaabz
```
将字符串复制一份，不断向右移动，再边扫边更新就好了。时间复杂度 $O(n^2)$。

由于题目要求两个区间相邻，所以更新时需要条件：匹配的字符串长度应等于第二个字符串的偏移量。

```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
bool eq(char a,char b){return a==b||a=='?'||b=='?';}
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        string t;cin>>t;
        size_t ans=0;
        for (size_t i=0;i<t.size();++i){
            size_t d=0;
            for (size_t j=i;j<t.size();++j){
                if (eq(t[j],t[j-i])) ++d;
                else d=0;
                if (i==d) ans=max(ans,d*2);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

