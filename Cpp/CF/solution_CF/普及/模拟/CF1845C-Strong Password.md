# Strong Password

## 题目描述

Monocarp finally got the courage to register on ForceCoders. He came up with a handle but is still thinking about the password.

He wants his password to be as strong as possible, so he came up with the following criteria:

- the length of the password should be exactly $ m $ ;
- the password should only consist of digits from $ 0 $ to $ 9 $ ;
- the password should not appear in the password database (given as a string $ s $ ) as a subsequence (not necessarily contiguous).

Monocarp also came up with two strings of length $ m $ : $ l $ and $ r $ , both consisting only of digits from $ 0 $ to $ 9 $ . He wants the $ i $ -th digit of his password to be between $ l_i $ and $ r_i $ , inclusive.

Does there exist a password that fits all criteria?

## 说明/提示

In the first testcase, Monocarp can choose password "50". It doesn't appear in $ s $ as a subsequence.

In the second testcase, all combinations of three digits, each of them being from $ 1 $ to $ 4 $ , fit the criteria on $ l $ and $ r $ . However, all of them appear in $ s $ as subsequences. For example, "314" appears at positions $ [3, 5, 12] $ and "222" appears at positions $ [2, 6, 10] $ .

In the third testcase, Monocarp can choose password "4321". Actually, that is the only password that fits the criteria on $ l $ and $ r $ . Luckily, it doesn't appear in $ s $ as a subsequence.

In the fourth testcase, only "49" and "59" fit the criteria on $ l $ and $ r $ . Both of them appear in $ s $ as subsequences.

In the fifth testcase, Monocarp can choose password "11".

## 样例 #1

### 输入

```
5
88005553535123456
2
50
56
123412341234
3
111
444
1234
4
4321
4321
459
2
49
59
00010
2
10
11```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：Wf_yjqd (赞：9)

CF 少见的如此简单的 Div2.C。

------------

正难则反，所以考虑什么情况下没有符合的密码，即所有在限制内的密码都是子序列。

考虑双指针，用 $i$ 表示在原密码典中的位置，$j$ 表示最终 密码的位置。

为了让后续可选择下一位的区间尽可能小，找到第 $i$ 个位置后，$l_j\sim r_j$ 中每个数最早出现位置的最大值。

然后 $i$ 继续相后找，$j$ 枚举下一位。

如果最终 $m$ 位密码找完，并且 $i\le n$，说明满足上下限制的整体出现位置最靠后的子序列存在，意味着没有答案，输出 `NO`，否则 `YES`。

复杂度 $\operatorname{O}(T\times n)$。

------------

如有解释不清，可通过模拟样例或者看看代码解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+84,maxm=23;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int T,n,m,b,j,a[maxn],l[maxm],r[maxm];
char s[maxn];
bitset<maxm> vis;
int main(){
    T=read();
    while(T--){
        scanf("%s",s+1);
        n=strlen(s+1);
        for(int i=1;i<=n;i++)
            a[i]=s[i]-'0';
        m=read();
        for(int i=1;i<=m;i++)
            scanf("%1d",&l[i]);
        for(int i=1;i<=m;i++)
            scanf("%1d",&r[i]);
        vis.reset();
        b=1;
        j=1;
        for(int i=1;i<=n&&j<=m;i++){
            if(a[i]>=l[j]&&a[i]<=r[j])
                vis[a[i]]=1;
            if(vis.count()==r[j]-l[j]+1){
                vis.reset();
                j++;
            }
        }
        puts(j!=m+1?"Sherry YES":"Sherry NO");
    }
    return 0;
}
```


---

## 作者：_Only_this (赞：4)

### Strong Password

------------

先简述一下题意吧，给定一个字符串 $s$，两个长度为 $m$ 的限制字符串 $l$ 和 $r$。构造一个长度为 $m$ 的字符串 $t$，要求 $l_i\le t_i\le r_i$，且 $t$ 不能为 $s$ 的子序列，问能否构造出符合要求的 $t$。

这题暴力枚举显然不现实，所以这里采用一种双指针的方法。

$i$、$j$ 两个指针，$i$ 指字符串 $s$，$j$ 指字符串 $t$。

在 $i$ 遍历的同时，判断当前的 $s_i$ 是否将当前的 $t_j$ 所有可能性全都试过。如果全都试过了，代表 $l_j$ 到 $r_j$ 的所有可能性都会是字符串 $s$ 子序列的一部分，再往后看下一个 $t_j$ 即可。如果没全都试过，将当前出现的 $s_i$ 标记。

若是当前的 $j$ 超过了 $m$，说明字符串 $t$ 的所有可能性都是字符串 $s$ 的一部分，即构造不出符合要求的字符串 $t$。

代码或许更好理解，看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e1+5;
int T,n;
int cnt[maxn];
bool vis[maxn][10];
string s,l,r;
bool Check(){
	memset(cnt,0,sizeof cnt);
	memset(vis,0,sizeof vis);
	int j=0;
	for(int i=0;i<s.size();i++){
		if(cnt[j]==r[j]-l[j]+1)
			j++;
		if(j>n-1)
			return 0;
		if(s[i]>=l[j] && s[i]<=r[j] && !vis[j][s[i]-'0'])
			vis[j][s[i]-'0']=1,cnt[j]++;
	}
	return (j<n-1 || j==n-1 && cnt[j]!=r[j]-l[j]+1);
}
int main(){
	scanf("%d",&T);
	while(T--){
		cin>>s;
		scanf("%d",&n);
		cin>>l>>r;
		printf("%s\n",Check() ? "YES" : "NO");
	}
	return 0;
}
```
完结，散花(～￣▽￣)～



---

## 作者：ForgotDream_CHN (赞：3)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17516673.html)

## 思路

这场 edu 爆炸了，特此记录。

由于 $m \le 10$，因此可以直接考虑搜索。对于定义状态为 $(idx, cur)$，表示当前在填密码的第 $idx$ 位，且使用了 $s$ 中的前 $cur$ 个字符。首先注意到对于同一个数字，如果其在 $s$ 中出现了不止一次，那么出现在前边的显然比出现在后边的潜力大，即可以组成更多的子序列。于是可以写出一个很简单的搜索。对于每一个 $i \in [l_{idx + 1}, r_{idx + 1}]$，找到其在 $s[cur:]$ 中的第一个出现位置 $p$，然后将状态转移到 $(idx + 1, p)$ 即可。如果不存在这样的 $p$ 的话，则意味着一组合法解，直接退出即可。而对于查询后继位置的部分，可以提前预处理出每一个数字在 $s$ 中的出现位置，然后二分查找即可。

但是像这样直接搜的话复杂度是 $O(10 ^ m \log \operatorname{len}(s))$ 级别的。这不够好，因此需要优化。一个比较显然的优化是对 $m$ 折半搜索。具体做法就是先按上边的方式找出所有长度小于 $\frac{m}{2}$ 的子序列的**最大 $cur$ 值**，记为 $max$，然后再用类似于上边的方法处理 $(\frac{m}{2}, m]$ 的子序列，不过初始状态为 $(m - 1, n)$，即从后往前找，然后找的时候找一个数字在 $s[:cur]$ 的最后一次出现位置，这是为了保证构造出的字符串其起始位置最大，方便后边的答案处理。

在第二次搜索时，每查到一个子串，记其起始位置为 $st$，如果 $st \le max$，即存在前后字符串的重叠的话，那么意味着存在合法解。这是因为上述的搜索过程保证了第一次搜索得到的子序列结束位置最小，第二次搜索得到的子序列结束位置最大。如果这样仍然存在重叠的话，那么一定存在一种子序列的构造方案使得其无法在 $s$ 中被找到。

于是这样的时间复杂度为 $O(10 ^ {\frac{m}{2}} \log \operatorname{len}(s))$。

然后注意到每次二分出来的答案是具有单调性的，于是可以去二分化，做到 $O(10 ^ {\frac{m}{2}})$。

## 代码

[link](https://codeforc.es/contest/1845/submission/211572266)

我写的是没有去掉二分的版本。


---

## 作者：SSqwq_ (赞：3)

## 解题策略
注意到**子串**必须在原字符串 $s$ 中相对位置固定。

如 $\{21\}$ 不是 $\{1234\}$ 的子串。

既然如此，那么容易推出结论如下：

**若第 $i$ 位密码上的数字在 $s$ 中最早出现的位置为 $last$，那么 $s$ 中位置在 $last$ 之前的内容对于后续密码的推算没有贡献且应当删去。**

因此，对于每一个数字（从 $0$ 到 $9$），可以按照**在 $s$ 中出现的位置**进行排序。

于是不难想到队列。

### 预处理的代码

```cpp
void procceed()
{
	int len=s.length();
	for(int i=0;i<len;i++)
	{
		qu[s[i]-'0'].push(i);
	}
}
```

如上即可保证队列中的元素从队首到队尾单调递增。

之后便容易写出**删去对后续密码推算没有贡献的信息**的函数：

### 该部分的代码

```cpp
void Erase()
{
	for(int j=0;j<=9;j++)
	{
		while(qu[j].empty()==false)
		{
			if(qu[j].front()>last)break;
			if(qu[j].front()<=last)qu[j].pop();//无贡献部分应删去
		}
	}
}
```
接下来是贪心选取每一位密码的策略。

### 贪心证明

注意到**密码不能为 $s$ 的子串**，而字串必须满足每一位都在 $s$ 中且相对位置一致。

显然，若密码的第 $i$ 位上的数字在 $s$ 中最早出现的位置为 $k$，不妨设当前 $s$ 的长度为 $len$，则有 $len-k$ 种可能的数字会与该数字构成子串。

因此，$len-k$ 越小越好，而 $len$ 是定值，故 $k$ 应最大。

综上所述，我们应当选取的是**最早出现在当前 $s$ 中的位置排在最后**的数字。

当然，若我们能选取一个当前的 $s$ 中不存在的数字，那显然不可能让密码成为 $s$ 的子串。

若选完最后一位且密码每一位的数字都出现在 $s$ 中，则显然密码的每一个数字都出现在 $s$ 中且数字出现的位置单调递增，则密码必然是 $s$ 的子串。


## AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mod1=998244353;
const int Mod2=1000000007;
int gcd(int a,int b){return __gcd(a,b);}
int lcm(int a,int b){return a/gcd(a,b)*b;}
const int N=400005;
queue<int> qu[10];
string l,r;
string s;
void info()
{
	int len=s.length();
	for(int i=0;i<len;i++)
	{
		qu[s[i]-'0'].push(i);
	}
}
void Solve()
{
	//coding here...
	int m;
	cin>>s;
	info();
	int last=-1;
	cin>>m;
	cin>>l;
	cin>>r;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<=9;j++)
		{
			while(qu[j].empty()==false)
			{
				if(qu[j].front()>last)break;
				if(qu[j].front()<=last)qu[j].pop();
			}
		}
		int L=l[i]-'0',R=r[i]-'0';
		for(int j=L;j<=R;j++)
		{
			
			if(qu[j].empty()==true)
			{
				cout<<"YES"<<endl;
				return;
			}
			else
			{
				last=max(last,qu[j].front());
			}
		}
	}
	cout<<"NO"<<endl;
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _=1;
	cin>>_;
	while(_--)
	{
		s.clear();
		l.clear();
		r.clear();
		for(int i=0;i<=9;i++)
		{
			while(qu[i].empty()==false)qu[i].pop();
		}
		Solve();
	}
	return 0;
}
```


---

## 作者：qwq___qaq (赞：2)

记密码为 $P$，考虑记搜：

令 $\operatorname{dfs}(i,j)$ 表示当前匹配到的是 $s_i$，需要查找的是 $P_j$，那么显然可以对此进行记忆化。

考虑到子序列的性质：若 $P_j=c$，那么我们可以 $i\gets nxt_{i,c}$，其中 $i$ 表示从 $i+1$ 开始到字符串末尾出现的第一个 $c$，那么显然可以通过后缀的方式 $O(|s|)$ 求解。那么我们接下来对 $nxt_{i,c}$ 进行分类讨论：

- $nxt_{i,c}$ 不存在，那么此时因为保证 $l_x\ge r_x$，那么后面一定是存在一种密码的，并且因为选择了 $c$，此时 $P$ 一定不是 $s$ 的字序列，那么此时就是可行的。

- $nxt_{i,c}$ 存在，那么此时我们就要考虑下一位是否可以得到不是 $s$ 子序列的位置元素，于是此时就需要调用 $\operatorname{dfs}(nxt_{i,c},j+1)$。

注意：$nxt_{a,b}$ 是不包含 $a$ 的。

时间复杂度 $O(|s|)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int T,m,len,pos[maxn][10],dp[maxn][15];
string s,l,r;
bool dfs(int x,int y){
	if(y==m+1)
		return 0;
	if(~dp[x][y])
		return dp[x][y];
	for(int i=l[y]-'0';i<=r[y]-'0';++i)
		if(pos[x][i]==-1||dfs(pos[x][i],y+1))
			return dp[x][y]=1;
	return dp[x][y]=0;
}
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
    	cin>>s>>m>>l>>r;
    	len=s.size(),s=' '+s,l=' '+l,r=' '+r;
		for(int i=0;i<=len;++i)
			for(int j=1;j<=m;++j)
				dp[i][j]=-1;
		for(int i=0;i<=len;++i)
			for(int j=0;j<10;++j)
				pos[i][j]=-1;
    	for(int i=len-1;i>=0;--i){
    		for(int j=0;j<10;++j)
    			pos[i][j]=pos[i+1][j];
	   		pos[i][s[i+1]-'0']=i+1;
		}
		if(dfs(0,1))
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

贪心，贪子序列匹配的量。

我的子序列匹配方式很简单，两个指针（不一定是这种类型，也可以记下标），当匹配串和被匹配串的指针位置的值不同时，将被匹配的串的指针后移，否则两个都向后移一个。

首先，有一个显而易见的结论：假如说匹配串前面的一部分能够匹配到被匹配串的 $i$ 位置，那么任何一个只匹配到 $j<i$ 位置的情况都不可能比匹配到 $i$ 更优。毕竟后移的过程中，$i$ 会比 $j$ 少掉中间的限制，也就更有可能向后移动。

那么，在这个结论之下，贪心思路就显而易见了：每一个位置都选择能向后移动最大距离的字符。直到 $t$ 被匹配完（不可行） 或者 $s$ 被匹配完（可行）。

小细节：一定要先判 $t$ 有没有被匹配完，二者同时匹配到末尾的情况下 $t$ 也是 $s$ 的子序列。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, lp, np, ln; char s[300005], l[10005], r[10005];
signed main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> s >> n >> l >> r; 
		lp = -1; bool cn = 0; ln = strlen(s);
		for (int i = 0, tp = 0; i != n; ++i, lp = tp) {
			if (lp >= ln) {
				cn = 1; cout << "YES\n";
				break;
			}
			for (char j = l[i]; j <= r[i]; ++j) {
				np = lp + 1; while (s[np] != j && np < ln) np++;
				tp = max(tp, np);// cerr << j << " to " << np << endl;
			}
		}
		if (lp >= ln && !cn) cout << "YES\n";
		else if (!cn) cout << "NO\n";
	}
	return 0;
}
```

---

## 作者：spider_oyster (赞：0)

有同学问我为什么 C 题做这么快。

要使得库里没有此密码，贪心地想，每次选库里能找到的最远位置的字母，如果库里没有当前字母，直接输出 Yes。

用 set 维护每种字母出现的位置即可。

记上一个字母对应库里位置为 $lst$，在 set 里 upper_bound 一下就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve()
{
    string s;cin>>s;
    set<int> p[10];
    for(int i=1;i<=s.size();i++) p[s[i-1]-'0'].insert(i);
    int m,lst=0;cin>>m;
    string l,r;cin>>l>>r;
    for(int i=0;i<m;i++)
    {
        int tmp=0;
        for(int j=l[i]-'0';j<=r[i]-'0';j++)
        {
            auto it=p[j].upper_bound(lst);
            if(it==p[j].end()) {puts("YES");return;}
            tmp=max(tmp,*it);
        }
        lst=max(lst,tmp);
    }
    puts("NO");
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--) solve();
}
```

---

## 作者：EuphoricStar (赞：0)

我怎么这么多天没写题解了，快来水一篇。

考虑对 $s$ 串建子序列自动机后 dp。

设 $n = |s|$。建子序列自动机，就是求出 $nxt_{i, j}$ 为 $[i, n]$ 中第一个等于 $j$ 的位置，不存在则 $nxt_{i, j} = n + 1$。

然后我们设 $f_{i, j}$ 为填到密码的第 $i$ 位，当前匹配到 $s$ 串的第 $j$ 位是否存在。注意我们贪心匹配最前能匹配的位置。注意如果 $j = n + 1$ 说明匹配不完，即密码已经不是一个 $s$ 的子序列。

转移枚举当前位填的数位 $d$，根据子序列自动机可以求得 $[j + 1, n]$ 中第一个 $d$ 的出现位置，就能转移了。

答案是 $f_{m, n + 1}$。

[code](https://codeforces.com/contest/1845/submission/211589717)

---

