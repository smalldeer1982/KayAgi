# Did We Get Everything Covered?

## 题目描述

You are given two integers $ n $ and $ k $ along with a string $ s $ .

Your task is to check whether all possible strings of length $ n $ that can be formed using the first $ k $ lowercase English alphabets occur as a subsequence of $ s $ . If the answer is NO, you also need to print a string of length $ n $ that can be formed using the first $ k $ lowercase English alphabets which does not occur as a subsequence of $ s $ .

If there are multiple answers, you may print any of them.

Note: A string $ a $ is called a subsequence of another string $ b $ if $ a $ can be obtained by deleting some (possibly zero) characters from $ b $ without changing the order of the remaining characters.

## 说明/提示

For the first test case, all possible strings (aa, ab, ba, bb) of length $ 2 $ that can be formed using the first $ 2 $ English alphabets occur as a subsequence of abba.

For the second test case, the string aa is not a subsequence of abb.

## 样例 #1

### 输入

```
3
2 2 4
abba
2 2 3
abb
3 3 10
aabbccabab```

### 输出

```
YES
NO
aa
NO
ccc```

# 题解

## 作者：wmrqwq (赞：10)

# 题目链接

[CF1925C & CF1924A Did We Get Everything Covered?](https://codeforces.com/contest/1925/problem/C)

# 解题思路

容易看出，我们可以开个桶存储当前搜索过的字母，当所有字母都有了之后就将桶清空，然后从当前搜到的位置继续存储，如果桶的清空次数小于 $k$ 次则一定有至少一个字符串无法达到要求，这时我们只需要构造桶清空时的每一个当前搜到的字符再加上最后一个桶未搜到的字符拼接的的字符串即可，否则一定包含了所有长度为 $n$ 的字符串。

# 参考代码

```cpp
/*
Tips:
你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
*/
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
ll t,a[210];
void cl(){
	forl(i,0,30)
		a[i]=0;
}
void solve()
{
	cl();
	ll n,m,k,sum=0,ans=0;
	string s,an="";
	cin>>n>>m>>k>>s;
	forl(i,0,k-1)
	{
		a[s[i]-'a']++;
		if(a[s[i]-'a']==1)
			sum++;
		if(sum==m)
		{
			sum=0,ans++;
			cl();
			an+=s[i];
			if(ans==n)
			{
				cout<<"YES\n";
				return ;
			}
		}
	}
	cout<<"NO\n";
	cout<<an;
	forl(i,0,m)
	{
		if(!a[i])
		{
			forl(j,1,n-an.size())
				cout<<char(i+'a');
			cout<<endl;
			return ;
		}
	}
}
int main()
{
	IOS;
	t=1;
	cin>>t;
	while(t--)
		solve();
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}
```


---

## 作者：apiad (赞：4)

还没有题解，来交一发。

这道题其实是一个比较巧妙的构造题。

首先，我们得判断是否合法。我们稍微转换一下题面。

我们可以理解，将长度为 $m$ 的字符串 $s$ 分割成 $n$ 段，每一段中必须包含着前 $k$ 种英文字母。

这样才能保证有效的所有构造方式。

我们需要开一个数组实时统计每一种字母的数量，如果有新加入的，我们就将 $cnt$ 加一，如果当 $cnt=k$ 的时候，就是完成了一段，我们将数组清空，$cnt$ 设为 $0$ 继续下面的操作。

但如果到后面没办法分程 $n$ 段怎么办？

很显然有一个贪心的策略，你目前取了 $t$ 段，那么答案前 $t$ 个字母便是前面每一段最后面出现的字母。我们想想正确性？很显然，我们要保证取的字符只在这个这一段中出现一次，不然就不成立了，如果是这一段前面的一些字母，有可能会有出现了多次，便不是答案所求的了。

然而后面跟着的就是最后一段中没有出现的字符，直接复制多个即可。

贪心的测率自己想一下都出来了，不知为啥赛时想假了。

代码：[link](https://codeforces.com/contest/1925/submission/243691751)。

---

## 作者：2020kanade (赞：3)

前情提要：笔者赛时想出了本题的如下极度扭曲的做法，但是滥用 ```std::map``` 加上写法本身常数大，直接寄了。事后发现这算法是个正常人都没法想出来。

题目：CF1925C/CF1924A

显然我们有一种非常粗暴的想法：询问串长度与字符集均很小，对原字符串建出[子序列自动机](https://www.luogu.com.cn/problem/P5826)，然后把若干种可能的串一个一个扔进去跑匹配，但是本题询问串的总数为 $k^n$，在本题数据规模下极限情况也就 ```__int128``` 刚好存下的样子。

根据自动机通用套路之一，我们考虑直接统计合法子序列的数量并进行比较。由子序列自动机的性质，对于每种字符为首字母的字符串，我们只需在其在原串中第一次出现的位置统计以其开头的包含指定字符集的子序列数量即可（若不明白请思考子序列自动机如何建立以及原因），此部分可以直接 DP。

具体地，$f_{u,len}$ 为位置 $u$ 开头的长度为 $len$ 的合法子序列数量，有转移 $f_{u,len}=\sum_{len\ge 1,v\in nxt_u}f_{v,len-1}$，这里的 $nxt$ 集合仅包含合法字符集中的转移，初始状态显然为 $f_{u,1}=1$。

至于不合法部分的构造，在自动机上更为显然：长度为 $p$ 的合法串显然应当有 $k^p$ 种，沿着对应合法子序列不足的边走直到走到终结状态，若长度不足 $n$ 直接补字符即可。

时间复杂度 $\Theta(m(n+k))$。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=1e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
int ssam[N][27];
i128 dp[N][27];bool vis[N][27];
i128 dfs(int u,int len)
{
	if(u<1||u>m) return 0;
	if(vis[u][len]) return dp[u][len];vis[u][len]=1;
	if(len==1) return dp[u][len]=1;
	for(int i=1;i<=k;++i) if(ssam[u][i]) dp[u][len]+=dfs(ssam[u][i],len-1);
	return dp[u][len];
}
i128 spm(i128 x,i128 y)
{
	i128 r=1;
	if(y<=0) return 1;
	for(int i=1;i<=y;++i) r*=x;
	return r;
}
void clr()
{
	for(int i=1;i<=m;++i) for(int j=1;j<=26;++j) dp[i][j]=vis[i][j]=ssam[i][j]=0;
}
void solve()
{
	cin>>n>>k>>m;const i128 fff=spm(k,n);
	string s;cin>>s;
	int lstp[27];
	for(int i=1;i<=26;++i) lstp[i]=m+1;
	for(int i=m;i;--i)
	{
		for(int j=1;j<=k;++j) ssam[i][j]=lstp[j];
		lstp[s[i-1]-'a'+1]=i;
	}
	int fcp[27];for(int i=1;i<=k;++i) fcp[i]=m+1;
	for(int i=1;i<=m;++i)
	{
		fcp[s[i-1]-'a'+1]=min(fcp[s[i-1]-'a'+1],i);
	}
	i128 ans=0;bool ok=1;
	for(int i=1;i<=k;++i)
	{
		if(fcp[i]==m+1)
		{
			ok=0;break;
		}
		ans+=dfs(fcp[i],n);
	}
	if(ok)
	{
		if(ans<spm(k,n)) ok=0;
	}
	if(ok)
	{
		cout<<"YES"<<endl;
		clr();
		return;
	}
	else
	{
		cout<<"NO"<<endl;
		string fuck;
		for(int i=1;i<=k;++i) if(dfs(fcp[i],n)<spm(k,n-1))
		{
			int u=fcp[i],l=n;fuck+=(i+'a'-1);
			while(u&&u>=1&&u<=m)
			{
				for(int j=1;j<=k;++j) 
				if((!vis[ssam[u][j]][l-1])||(dp[ssam[u][j]][l-1]<spm(k,l-2)))
				{
					--l,fuck+=(j+'a'-1),u=ssam[u][j];break;
				}
			}
			--l;
			if(l>0) while(l) fuck+='a',--l;
			cout<<fuck<<endl;clr();;return;
		}
	}
}
int main()
{
	//freopen("CF1925C.in","r",stdin);
	//freopen("CF1925C.out","w",stdout);
	syncoff();
	cin>>t;
	while(t--) solve();
	return 0;
}
/*
*/
```


---

## 作者：lfxxx (赞：3)

考虑 A 题中你是怎么做的。

笔者的做法是把串分成 $n$ 个部分，每个部分塞个长度为 $k$ 的包含 $k$ 个所需字符的字串。

充分性显然，必要性的话反证不难。

考虑每次找到最短的包含所需要的 $k$ 种字符的字串，并从它后面开始继续找，假若没找够 $n$ 次就不行。

构造方案的话，考虑将前面满足的字串的最后一个字符和任意一个不满足的字符拼起来即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5+114;
char s[maxn];
char ending[maxn];
void work(){
    int n,k,m;
    cin>>n>>k>>m;
    for(int i=1;i<=m;i++) cin>>s[i];
    int now=1;
    for(int i=1;i<=n;i++){
        int sum=0;
        for(;now<=m;now++){
            if(s[now]-'a'+1<=k){
                sum|=(1ll<<(s[now]-'a'));
            }
            if(sum==(1ll<<k)-1){
                ending[i]=s[now];
                now++;
                break;
            }
        }
        if(sum!=(1ll<<k)-1){
            cout<<"No\n";
            for(int j=1;j<i;j++) cout<<ending[j];
            for(int p=1;p<=k;p++){
                if(!((1ll<<(p-1))&sum)){
                    cout<<(char)('a'+p-1);
                    break;
                }
            }
            for(int j=i+1;j<=n;j++) cout<<'a';
            cout<<'\n';
            return ;
        }
    }
    cout<<"Yes\n";
}
signed main(){
     ios::sync_with_stdio(0);
     cin.tie(0);
     cout.tie(0);
     int T;
     cin>>T;
     while(T--) work();
     return 0;
}

```


---

## 作者：Wei_Han (赞：1)

## 题意

有 $t$ 组数据。每组给定 $n$，$k$ 和一个字符串 $s$，字符串长 $m$。判断所有长度为 $n$，由前 $k$ 种小写字母构成的字符串是否都是 $s$ 的子串。

如果不符合条件需要输出一组反例。

## Solution

抽象一下题意，

假定其中一种字符串为 $a$，从 $s$ 的开头开始，设 $s$ 中当前位置为 $w$，依次从 $a$ 中拿出字符，从 $w$ 的下一个位置开始，找到 $s$ 中这个字符**第一次**出现的位置，将 $w$ 跳到那一个位置，如果最后找不到 $a$ 中的某一个字符，那么表示 $a$ 字符串不符合条件。

为了方便，我们可以在 $s$ 的末尾添加前 $k$ 个小写字母，那么不符合条件的情况就变成 $w$ 跳过了原 $s$ 串的长度，即 $w>m$。

为了让 $w$ 尽快跳出 $s$，我们每一次选择每种字符中第一次出现最靠后的即可，途中记录跳过的字符，不符合时补齐字符输出即可。（补齐时需要补 $w$ 后未出现过的）

时间复杂度线性。

## Code

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
using namespace std;
typedef int ll;
typedef double db;
const int N=1e7+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,k,m;
string s,ss;
ll mp[30];
int main(){
	read(t);
	while(t--){
		read(n),read(k),read(m);
		s=ss;
		cin>>s;
		mem(mp,0);
		ll sum=0,start=0,m1=m;
		fo(1,i,k) s+=char('a'+i-1);
		m+=k;
		fo(0,i,m-1)
		{
			if(!mp[s[i]-'a'+1])
			{
				mp[s[i]-'a'+1]=1;
				sum++;
				if(sum==k){start=i;break;}
			}	
		}
		string s2;
		s2+=s[start];
		if(start>m1-1)
		{
			printf("NO\n");
			fo(1,i,n) cout<<s[start];
			if(t) pr;
			continue;
		}
		ll now=1,flag=0;
		sum=0;mem(mp,0);
		fo(start+1,i,m-1){
			if(now==n){
				printf("YES");
				break;
			}
			if(i>m1-1&&!mp[s[i]-'a'+1]){
				flag=1;
				printf("NO\n");
				cout<<s2;
				fo(1,j,n-s2.size()) cout<<s[i];
				break;
			}
			if(!mp[s[i]-'a'+1]) mp[s[i]-'a'+1]=1,sum++;
			if(sum==k) now++,mem(mp,0),s2+=s[i],sum=0;
		}
		if(t) pr;
	}
	return 0;
}
``````

---

## 作者：Chenyichen0420 (赞：0)

# 思路分析

我们可以以强行构造的思路来做这道题。

首先，由于子序列不要求连续的特点，因此选择更靠后的字符只会比选择更靠前的字符产生更少的选择和更少的可能性。因此，只要逼迫我们只能在更靠后的地方匹配到就行了。所以我们要构造出这么一个序列，每一个字符都是到了最后，所有与字符串不匹配的字符都存在了，最终出现我们字符串指定的字符出现。

也就是说，我们要考虑怎样才能浪费更多的字符。其实答案显然：不停地统计范围内字符出现过没有，直到所有字符都出现。这时候将最后加入的哪一个字符放到构造的字符串末尾。这样，前面的都被浪费了，达成最优。

这时候我们再不停地重复统计，直到输入完了字符串。判断一下构造字符串长度够不够。不够再补一点字符就是了（选没统计到的字符）。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, k, cnt, tar; 
char c; bool posi[26];
string tmp;
signed main(){
	ios::sync_with_stdio(0);
	cin >> t;
	while(t--) {
		cin >> n >> m >> k; tmp = "";
		tar = cnt = 0; memset(posi, 0, sizeof posi);
		while (k--) {
			cin >> c;
			cnt += (!posi[c - 'a'] && c - 'a' < m);
			posi[c - 'a'] = 1;
			if (cnt == m) {
				cnt = 0; tar++; tmp += c;
				memset(posi, 0, sizeof posi);
			}
		}
		if (tar >= n) cout << "YES\n";
		else {
			while (tar < n - 1) tmp += 'a', tar++;
			for (int i = 0;; ++i) {
				if (!posi[i]) {
					tmp += (char)(i + 'a');
					break;
				}
			}
			cout << "NO\n" << tmp << endl;
		}
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

首先构造一个字符串使他不是 $s$ 的子序列是比较困难的。我们可以考虑从 $i=0$ 开始，依次往后跳，选出这个字符串。

但是，我们得构造一个字符串尽可能的让他不为 $s$ 的子序列，我们需要使用贪心算法。从上一个枚举的点出发，跳到与该点距离最远的字母。由于我们跳的次数是固定的，跳的更远，字符的选择自然就更少，就更不可能是他的子序列了。

接下来我们就得考虑找到距离最远的字符。定义一个 $vis$ 数组，存储该字母出现的位置，同时用 $sum$ 统计有几个字母出现过了。如果 $sum<k$，说明有字母没出现，自然是无解的，这时枚举 $vis$，找到这个字母即可。最后还要把没有枚举的字母补充一下。反之，同样枚举找到距离最长的字母，跳到该点即可。一旦跳满 $n$ 次，说明有解。

这样我们会出现两重循环，复杂度是不是 $O(nmk)$ 呢？并不是。我们每次跳都只会跳一部分，下一次从该点开始跳，因此循环的范围并不会重复，复杂度是 $O(mk)$。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k;
string s;
int main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
  	cin>>n>>k>>m;
  	cin>>s;
  	int p=-1,cnt=0,flag=1;//p表示上一次跳的点，cnt表示跳的次数
  	string ans="";
  	while(1)
  	{
  	  int vis[26];
	  int sum=0;
	  for(int i=0;i<k;i++) vis[i]=-1;//全部赋值为-1，方便判断是否出现
  	  for(int i=p+1;i<m;i++)
	  {
	  	if(vis[s[i]-'a']==-1)
		{
		  sum++;
		  vis[s[i]-'a']=i;
		  if(sum==k) break;//出现k个字母，退出
		}
	  }
	  if(sum<k)
	  {
	    flag=0;
	  	for(int i=0;i<k;i++)
	    {
	  	  if(vis[i]==-1)//找到了未出现的字符
	  	  {
	  	    ans+=char(i+'a');
	  	    int len=ans.size();
	  	    for(int j=1;j<=n-len;j++) ans+='a';//补充字符
		    break;
	      }
	    }
	  	break;
	  }
	  else
	  {
	  	int x=-1,y=-1;
	    for(int i=0;i<k;i++) if(vis[i]>x) x=vis[i],y=i;//跳到距离最大的点
		p=x;
	    ans+=char(y+'a');//记录最远的字符
	    cnt++;
	  }
	  if(cnt==n) break;
	}
  	if(flag) cout<<"YES\n";
  	else cout<<"NO\n"<<ans<<"\n";
  }
  return 0;
}
```

---

## 作者：封禁用户 (赞：0)

解法：

关键结论：$s$ 对 $n$ 满足条件，当且仅当可以分割 $s=s_1+s_2$，其中 $s_1$ 对 $n-1$ 满足条件，而 $s_2$ 中 $\sum$ 中字母各至少出现一次（可以考虑如何证明）。于是可以从左向右扫描，维护当前满足条件的长度，并在每次访问完整个字符集时更新。判断长度是否小于 $n$ 即可。

答案为 ```NO``` 时，不符合条件的串的构造需要小心。给出一个显然正确的构造：每次更新长度时，记录最后一次遇到的字母，添加到答案末尾。之后向结尾不断增加（当前段）未出现的字母直至长度为 $n$。使用状态压缩技术，时间复杂度 $O(n+m)$。

```cpp
void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    string s;
    cin >> s;
    int l = 0, vis = 0;
    string ans;
    for (char c : s) {
        vis |= 1 << (c - 'a');
        if (vis == (1 << k) - 1) {
            ans += c;
            l++, vis = 0;
        }
    }
    if (l >= n) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
        int b = countr_one((unsigned)vis);
        while ((int)ans.size() < n) ans += char('a' + b);
        cout << ans << "\n";
    }
```


---

