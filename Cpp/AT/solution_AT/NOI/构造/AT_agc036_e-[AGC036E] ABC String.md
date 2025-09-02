# [AGC036E] ABC String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc036/tasks/agc036_e

`A`,`B`,`C` からなる文字列 $ S $ が与えられます。

$ S $ の連続とは限らない部分列 $ x $ であって、次の条件をすべて満たすもののうち、最長のものを $ 1 $ つ求めてください。 なお、$ S $ の部分列とは、$ S $ から $ 0 $ 個以上の文字を削除して得られる文字列を意味します。

- $ x $ に含まれる `A`,`B`,`C` それぞれの個数は全て等しい。
- $ x $ の中で同じ文字は隣り合わない。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 10^6 $
- $ S $ は `A`,`B`,`C` からなる。

### Sample Explanation 1

$ S $ の部分列として、`ACBCAB` を考えると、これは条件を満たしており、またこれが最長です。 また、`ABCBCA` も条件を満たす最長の部分列です。 `ABCBCAB`, `ABBCCA` なども $ S $ の部分列ですが、これらは条件を満たしません。

### Sample Explanation 4

条件を満たす部分列が空文字列のみのこともあります。

## 样例 #1

### 输入

```
ABBCBCAB```

### 输出

```
ACBCAB```

## 样例 #2

### 输入

```
ABABABABACACACAC```

### 输出

```
BABCAC```

## 样例 #3

### 输入

```
ABCABACBCBABABACBCBCBCBCBCAB```

### 输出

```
ACABACABABACBCBCBCBCA```

## 样例 #4

### 输入

```
AAA```

### 输出

```
```

# 题解

## 作者：tyr_04 (赞：25)

[传送门](https://www.luogu.com.cn/problem/AT_agc036_e)

感谢 @[Annihilation_y](https://www.luogu.com.cn/user/549508) 的提示和帮助

鲜花：第一篇黑题题解，感觉这几天集训下来还是有不少收获的，特别是某些题的结论往往直觉上是错误的，或者说很难靠直觉感受出来，但经过一些证明后却发现是对的。

### 题意

给定一个字符串，仅包含 $A,B,C$ 三种字符，现在要求你构造出该字符串的**最长**子序列，满足：

1. $A,B,C$ 三种字符出现次数相同

2. 任意两个相邻字符不同（即不能出现相邻两个位置形如 $AA,BB,CC$ 的情况）

多解时只需输出任意一组解即可，字符串长度上界为 $10^6$。

### 思路

由于正着做非常困难（如果进行 dp 维护的信息非常多），考虑从删除的角度出发。

先把原字符串字符相同的连续段缩成一个字符，设 $s_1,s_2,s_3$ 分别表示 $A,B,C$ 三种字符出现的次数，设 $s_1 \le s_2 \le s_3$（任意一种 $s_1,s_2,s_3$ 的大小关系与 $s_1 \le s_2 \le s_3$ 是等价的，因此下文只讨论 $s_1 \le s_2 \le s_3$ 的情况）。

由于每种字符出现次数相同，子序列长度的上界即为 $3s_1$，也就是说我们希望在 $s_1 = s_2 = s_3$ 的情况下，$s_1$ 尽量大。

试证明以下四个结论：

1. 若当前子序列满足条件 2 且 $s_1 \le s_2 = s_3$，一定存在一种方式使得仅删除 $BC$ 串（这里的“$BC$ 串”泛指相邻两个字符构成 $BC$ 或 $CB$ 的形态，$AB$ 串，$AC$ 串同理）让该子序列满足条件 1,2（这种情况下，我们使子序列总长度达到了上界 $3s_1$ ，当 $s_1$ 固定时，这种删除方式一定是最优的）。

::::info[证明]
设该子序列的形态为 $\ldots A \ldots A \ldots A \ldots A \ldots$（其中除首尾外的任意一段 $\ldots$ 都是由 $B,C$ 两种字符构成的字符串），若删除任意一个 $BC$ 串都会使新的子序列不满足条件 2，当且仅当该子序列首部和尾部为 $A$，其余任何一段 $\ldots$ 都为 $BC$ 串（如果 $B$ 或 $C$ 字符出现在子序列首部或尾部，删除后一定不会使新的子序列不满足条件 2；如果存在一段 $\ldots$ 含有多个 $B$ 或 $C$，即存在一段 $\ldots$ 的长度大于等于 $3$，删除该段开头两个字符构成的 $BC$ 串都不会使新的子序列出现 $AA$），又因为此时 $s_1,s_2,s_3$ 的大小关系为 $s_1 > s_2 = s_3$，与命题矛盾，该结论得证。
::::

2. 若当前子序列满足条件 2 且 $s_1 \le s_2 < s_3$，又存在一个 $C$ 使得删除该 $C$ 后新的子序列仍满足条件 2，删除该 $C$ 一定不劣。

::::info[证明]
由于删除该 $C$ 后新的子序列仍满足条件 2，该 $C$ 要么在子序列首部或尾部，要么与之相邻的两个字符一个为 $A$，另一个为 $B$，删除该字符后不会影响其它字符的位置关系。根据我们证明的结论 1，我们要尽量使 $s_1$ 不减时 $s_2 = s_3$，而这种删法让 $s_3$ 靠近了 $s_2$ 且不影响 $s_1$，故一定不劣，该结论得证。
::::

3. 若当前子序列满足条件 2 且 $s_1 \le s_2 < s_3,s_1 \ne 0$，则**至少存在一个 $AC$ 串**。

::::info[证明]
考虑反证法，由于每个 $C$ 不会与 $A$ 相连，显然每个 $C$ 要么左右两边都是 $B$，要么 $C$ 在首部或尾部只于一个 $B$ 相邻，又因为满足条件 2 且 $s_2 < s_3$，因此只有 $CBCBC \ldots CBCBC$ 这一种情况满足条件，且此时 $s_2 + 1 = s_3$。然而我们无法在该字符串中添加任意一个 $A$ 使得子序列中不出现 $AC$ 串（如果硬要添加一个 $A$ 必须先添加一个 $B$，此时 $s_2 = s_3$，因此还要添加 $C$，但由于 $A$ 不能与 $C$ 相邻，当前所有的 $B$ 左右两边都有字符，因此添加一个 $C$ 的同时还需要一个 $B$，不能做到 $s_2 < s_3$），该结论得证。
::::

4. 若当前子序列满足条件 2 且 $s_1 \le s_2 < s_3,s_1 \ne 0$，又**不存在**一个 $C$ 使得删除该 $C$ 后新的子序列仍满足条件 2，则**删除一个 $AC$ 串一定不劣，删除一个 $BC$ 串或 $AB$ 串一定不优**。

::::info[证明]
由于我们要使 $s_3 = s_2$，本质上是想要缩小 $s_2$ 与 $s_3$ 的差距，因此删除 $AB$ 串或 $BC$ 串一定不优（删除 $AB$ 使得 $s_1$ 减小，$s_2$ 减小，$s_2$ 和 $s_3$ 的差距扩大，完全劣于删除 $AC$ 串；删除 $BC$ 串使得 $s_2$ 减小，$s_3$ 减小，$s_2$ 和 $s_3$ 的差距不变，并且删除 $BC$ 串一定不会产生新的可单独删除的 $C$，因为 $A$ 无论出现在哪边都会产生一开始就可单独删除的 $C$，可以举例手玩一下）。又因为当前子序列无法单独删掉一个 $C$ 字符，因此删除 $AC$ 串一定不劣，该结论得证。
::::

根据上文 3,4 两个结论，可知若当前子序列满足条件 2 且 $s_1 \le s_2 < s_3,s_1 \ne 0$，又不存在一个 $C$ 使得删除该 $C$ 后新的子序列仍满足条件 2，**一定存在 $AC$ 串且删除一个 $AC$ 串一定不劣**（本题目最重要的结论，单看这个结论非常反直觉，因此要分开证明，不能凭感觉）。

总结：首先，把原字符串字符相同的连续段缩成一个字符；求出 $s_1,s_2,s_3$（设 $s_1 \le s_2 \le s_3$，含义见上文）；其次，如果 $s_2 < s_3$，尽量删除能单独删除的 $C$ 直到 $s_2 = s_3$；接着，如果删除所有能单独删除的 $C$ 后仍有 $s_2 < s_3$，尽量删除 $AC$ 串直到 $s_2 = s_3$；然后，从头到尾扫一遍，将能删除的 $BC$ 串删除直到 $s_1 = s_2 = s_3$；最后，将删除后的字符串作答案输出。

使用 set 维护信息，设 $n$ 是字符串长度，总时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$，实现细节见代码。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
char zs[5];
int s1,s2,s3,bh[5];
set<pair<int,int> > ans;
set<int> st3,st13;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if((i==0||s[i]!=s[i-1])&&s[i]=='A')
		{
			s1++;
		}
		else if((i==0||s[i]!=s[i-1])&&s[i]=='B')
		{
			s2++;
		}
		else if(i==0||s[i]!=s[i-1])
		{
			s3++;
		}
	}
	if(s1<=s2&&s2<=s3)
	{
		bh[1]=1;
		bh[2]=2;
		bh[3]=3;
		zs[1]='A';
		zs[2]='B';
		zs[3]='C';
	}
	else if(s1<=s3&&s3<=s2)
	{
		bh[1]=1;
		bh[3]=2;
		bh[2]=3;
		zs[1]='A';
		zs[2]='C';
		zs[3]='B';
		swap(s2,s3);
	}
	else if(s2<=s1&&s1<=s3)
	{
		bh[2]=1;
		bh[1]=2;
		bh[3]=3;
		zs[1]='B';
		zs[2]='A';
		zs[3]='C';
		swap(s1,s2);
	}
	else if(s2<=s3&&s3<=s1)
	{
		bh[2]=1;
		bh[3]=2;
		bh[1]=3;
		zs[1]='B';
		zs[2]='C';
		zs[3]='A';
		swap(s1,s2);
		swap(s2,s3);
	}
	else if(s3<=s1&&s1<=s2)
	{
		bh[3]=1;
		bh[1]=2;
		bh[2]=3;
		zs[1]='C';
		zs[2]='A';
		zs[3]='B';
		swap(s2,s3);
		swap(s1,s2);
	}
	else if(s3<=s2&&s2<=s1)
	{
		bh[3]=1;
		bh[2]=2;
		bh[1]=3;
		zs[1]='C';
		zs[2]='B';
		zs[3]='A';
		swap(s1,s2);
		swap(s2,s3);
		swap(s1,s2);
	}
	for(int i=0;i<s.size();i++)
	{
		if((i==0||s[i]!=s[i-1])&&s[i]=='A')
		{
			ans.insert({i,bh[1]});
		}
		else if((i==0||s[i]!=s[i-1])&&s[i]=='B')
		{
			ans.insert({i,bh[2]});
		}
		else if(i==0||s[i]!=s[i-1])
		{
			ans.insert({i,bh[3]});
		}
	}
	for(auto o2=ans.begin();o2!=ans.end();o2++)
	{
		auto o1=o2,o3=o2;
		o3++;
		if(o2==ans.begin()||o3==ans.end())
		{
			pair<int,int> u=*o2;
			if(u.second==3)
			{
				st3.insert(u.first);
			}
		}
		else
		{
			o1--;
			pair<int,int> u1=*o1,u2=*o2,u3=*o3;
			if(u1.second!=u3.second&&u2.second==3)
			{
				st3.insert(u2.first);
			}
			else if(u1.second==1&&u2.second==3)
			{
				st13.insert(u2.first);
			}
			else if(u3.second==1&&u2.second==3)
			{
				st13.insert(u3.first);
			}
		}
	}
	while(s2!=s3)
	{
		if(st3.size()!=0)
		{
			auto o=st3.begin();
			auto ts=ans.lower_bound({*o,3});
			st3.erase(o);
			ans.erase(ts);
			s3--;
		}
		else
		{
			auto o=st13.begin();
			auto ts1=ans.lower_bound({*o,0}),ts2=ts1;
			ts1--;
			st13.erase(o);
			ans.erase(ts1);
			ans.erase(ts2);
			s3--;
			s1--;
		}
	}
	for(auto o1=ans.begin();o1!=ans.end();)
	{
		if(s2>s1)
		{
			auto o2=o1;
			o2++;
			if(o2==ans.end())
			{
				o1++;
				continue;
			}
			auto o3=o1;
			o3++;
			o3++;
			pair<int,int> u1=*o1,u2=*o2;
			if(o3==ans.end())
			{
				if((u1.second==2&&u2.second==3||u1.second==3&&u2.second==2))
				{
					ans.erase(o1);
					ans.erase(o2);
					o1=o3;
					s2--;
					s3--;
				}
				else
				{
					o1++;
				}
			}
			else
			{
				pair<int,int> u3=*o3;
				if((u1.second==2&&u2.second==3||u1.second==3&&u2.second==2)&&u3.second!=1)
				{
					ans.erase(o1);
					ans.erase(o2);
					o1=o3;
					s2--;
					s3--;
				}
				else
				{
					o1++;
				}
			}
		}
		else
		{
			break;
		}
	}
	for(auto o=ans.begin();o!=ans.end();o++)
	{
		pair<int,int> u=*o;
		cout<<zs[u.second];
	}
	return 0;
}
```

---

## 作者：Lates (赞：8)

首先可以把相同字母缩成一个。

设 $c_A,c_B,c_C$ 串中这仨字母的数目。

不妨设 $c_A \le c_B \le c_C$。先入为主（盯着题解）地认为 A 将字符串划分为 ..A...A...A.. 这样的结构，...为 BCBCBC 这样的串。

则答案上界为 $3c_A$，希望取等，就要限制 $c_A = c_B, c_B = c_C$。先做前一个限制显然不如先做后面那个限制来得容易。

---

可以证明 $c_A\le c_B = c_C$ 时，可以达到上界。

证明：可以一直删段中的 BC / CB，过程中得保证相邻的字母不相同依然满足。 则处于两个 A 之间的 ... 至多剩下两个，左右至多剩下一个。

则 $c_B+c_C \le 2 (c_A-1)+1+1 = 2c_A$，而一开始是不小于的。于是可知过程中存在一个时间使得 $c_A=c_B=c_C$。

---

接下来考虑如何使得 $c_B = c_C$，我们不愿意删除 A。

如果一个 ... 不是有且仅有一个 C，那么我们可以通过 ... 两边删 C，达到 BCBC...BCB（B 必然在 ... 的左右两边），先这么做做，如果成功则成功，不成功则必须删 A。

这时肯定是很多个有且仅有一个 C 的 ...，这时删一些 AC / CA 即可。

```cpp
#include <bits/stdc++.h>
#include <assert.h>
using namespace std;
typedef long long ll;
typedef double db;
#define ep emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define fin freopen("in.in","r",stdin);
#define fout freopen("out.out","w",stdout);
#define dd(x) cerr << #x" = " << x << endl;
#define wj(name) freopen(#name".in", "r", stdin); \
				freopen(#name".out", "w", stdout);
inline int read() {
	int x=0, v=1,ch=getchar();
	while('0'>ch||ch>'9') {
		if(ch=='-') v=0;
		ch=getchar();
	}while('0'<=ch&&ch<='9') {
		x=(x*10)+(ch^'0');
		ch=getchar();
	}return v?x:-x;
}
const int MAX = 1e6 + 5; 
char t[MAX];int n, m;
char s[MAX],r[MAX];
int cnt[3],id[3];
int cmp(int x,int y){return cnt[x]<cnt[y];}

int pre[MAX],p[MAX];
void del(int x,int c) {
	--cnt[c];
	pre[x]=0;
}

void getp(char *s) {
	m=0; 
	if(s[1]!='A')p[m=1]=0;
	for(int i=1;i<=n;++i) 
		if(s[i]=='A') p[++m]=i;
	if(s[n]!='A')p[++m]=n+1;
}
void get(char *s) {
	int tmp=0;
	for(int i=1;i<=n;++i) 
		if(pre[i]) t[++tmp]=s[i];
	for(int i=1;i<=tmp;++i) 
		s[i]=t[i]; 
	n=tmp;
}
void rework(char *s) {
	cnt[0]=cnt[1]=cnt[2]=0; 
	for(int i=1;i<=n;++i) ++cnt[s[i]-'A'];
}
void print(char *s) {
	for(int i=1;i<=n;++i) {
		putchar(s[i]);
	} puts("");
}
void solve(char *s) {
//	print(s);
	for(int i=1;i<=n;++i) pre[i]=1;
	if(cnt[1] != cnt[2]) {	
		// step 1 : 使得 c['b'] == c['c']
		// 删除 C 直到和 B 相等。	
		getp(s);	
		for(int t=1;t<m;++t) {
			int l=p[t]+1,r=p[t+1]-1;
			if(r-l+1==1&&l-1>=1&&r+1<=n) continue;
			while(cnt[1]!=cnt[2]&&l<=r&&s[l]=='C') {
				del(l,s[l]-'A'),++l;
			}
			while(cnt[1]!=cnt[2]&&l<=r&&s[r]=='C') {
				del(r,s[r]-'A'),--r;
			}
		}
		get(s);
	}
	if(cnt[1] != cnt[2]) {
		// 否则只能删除 "CA"
		for(int i=1;i<=n;++i) pre[i]=1;
		getp(s);
		for(int t=1;t<m;++t) {
			int l=p[t]+1,r=p[t+1]-1;
			if(cnt[1]!=cnt[2] && r-l+1==1 && s[l]=='C') {
				if(r==n) del(r,s[r]-'A'), del(r-1,s[r-1]-'A');
				else del(l,s[l]-'A'), del(l+1, s[l+1]-'A');
			}
		}
		get(s);
	}
	assert(cnt[1] == cnt[2]);
	for(int i=1;i<=n;++i) pre[i]=1;
	getp(s);
	for(int t=1;t<m;++t) {
		int l=p[t]+1,r=p[t+1]-1;
		while(cnt[0]!=cnt[1]&&((s[l]=='B'&&s[l+1]=='C')||(s[l]=='C'&&s[l+1]=='B'))&&l<=r) {
			if(r-l+1==2&&l-1>=1&&r+1<=n)break; 
			del(l,s[l]-'A'),del(l+1,s[l+1]-'A');
			l+=2;
		}
	}
	get(s);
}
signed main() {
	scanf("%s",t+1);
	n=strlen(t+1); 
	s[m=1]=t[1]; 
	for(int i=2;i<=n;++i) if(t[i] != t[i-1]) s[++m] = t[i]; n = m;
	for(int i=1;i<=n;++i) ++cnt[s[i]-'A'];
	id[0]=0,id[1]=1,id[2]=2; 
	sort(id,id+3,cmp); sort(cnt,cnt+3);
	for(int i=1;i<=n;++i) {
		int q=s[i]-'A';
		if(q==id[0]) r[i]='A';
		else if(q==id[1]) r[i]='B';
		else r[i]='C';
	}
	solve(r);
	for(int i=1;i<=n;++i) {
		printf("%c", id[r[i]-'A']+'A');
	}
	return 0;
}

```

---

## 作者：feecle6418 (赞：7)

首先把相同字母缩成一段，设 $c_a,c_b,c_c$ 分别为 $a,b,c$ 出现次数，不妨假设 $c_a\le c_b\le c_c$。

显然答案的上界是 $3c_a$，考虑如何尽量接近这一上界。

先删去连续子串 `ACB` 或 `BCA` 中的 `C` 和整个串开头结尾的 `C`，直到不存在这样的 `C` 或者 $c_c=c_b$。

假如 $c_c$ 仍然大于 $c_b$，那为了减小 $c_c-c_b$ 的值，只能不停删去 `AC` 或者 `CA`（因为其他串都不能减小 $c_c-c_b$）。可以证明，这样一定可以让 $c_b=c_c$。

现在不停删去连续的 `BC` 或者 `CB`，直到 $c_a=c_b=c_c$，就是答案。可以证明，这样一定能删到 $c_a=c_b=c_c$。

有一个细节：删去一段长度为偶数 `AC` 或者 `CA` 时，需要保证两端不都是 `B`（也即，`BACB` 中的 `AC` 是不能被删除的；`BACACB` 中只能删除一个 `AC`，不能删两个）。删去 `BC` 或者 `CB` 时也存在类似问题。

代码：https://atcoder.jp/contests/agc036/submissions/21045617

---

（其实可以证明删除 `AC` 或 `CA` 时永远不会出现以上特殊情况，但是我写代码的时候比较蠢就也判了下）

---

## 作者：lzk5627 (赞：5)

请求管理员添加题意(被禁言了)
### 简要题意
给一个由 $A,B,C$ 组成的字符串,让你求最长的一个子序列

使得相邻的字符不相同且 $A,B,C$ 的个数相同

### sol
首先考虑将两个相邻的字符变成一个

然后设 $cnt_c$ 表示字符 $c$ 的出现次数,那我们先默认 $cnt_a\le cnt_b \le cnt_c$,不和条件就交换

然后把 $A$ 看做分隔符,那么这样字符串就变成了一些 $BC$ 交替出现的串 ,$AB$ 串 和 $AC$ 串,分别设他们的数量为 $s_3,s_2,s_1$,这样答案的上界显然就是 $3cnt_a$.

我们考虑什么样的情况可以达到这个上界,目标是最终选出来的子序列满足 $cnt_a=cnt_b=cnt_c$ 那么我们可以考虑先删掉 $C$ 直到 $cnt_b=cnt_c$ 为止

考虑如何去删是最优的,我们发现如果我们删掉一个左两边分别是 $AB$ 的 $C$,这样是不影响相邻字符不相同的性质的,然后发现如果 $BC$ 交替串中 $B$ 和 $C$ 的数量相同的话,那么会贡献出来一个这样的 $C$ ,如果 $B$ 比 $C$ 小的话,会贡献出来两个这样的 $C$,那么也就是要满足 $s_1+s_2 \ge s_3$ 

然后考虑删到 $cnt_b=cnt_c$ 之后怎么构造,那么就是要删掉 $BC$ 这样的连续串,因为除去 $BC$ 交替串之外,每一个 $B$ 和 $C$ 都至少有一个 $A$ ,那么这样是肯定删的完的

那么如果 $s_1+s_2 < s_3$ 怎么办
这就说明至少要删除一些 $A$ 使得 $s_1+s_2\ge s_3$ 才行,尽量删除 $ACA$ 这种串中的 $AC$ 即可

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct each{
	int cnt;
	char ch;
}a[3];
char A,B,C,s[N],t[N];
int n,vi[N],nex[N],bfe[N];
bool com(each x,each y){
	return x.cnt<y.cnt;
}
void erase(int x){
	nex[bfe[x]]=nex[x];
	bfe[nex[x]]=bfe[x];
	vi[x]=1;
}
bool check(int i,int j,char c1,char c2){
	if(!i||!j)	return false;
	if(s[i]==c1&&s[j]==c2)	return true;
	if(s[i]==c2&&s[j]==c1)	return true;
	return false;
}
bool is(int i,int j){
	if(!i||!j)	return true;
	return s[i]!=s[j];
}
void pri(){
	for(int i=1;i<=n;i++)
		if(!vi[i]){
			for(int j=i;j;j=nex[j])
				putchar(s[j]);
			return ;
		}
}
void solve(){
	int c1=a[0].cnt,c2=a[1].cnt,c3=a[2].cnt;
	for(int i=1;i<=n&&c2<c3;i++)
		if(!vi[i]&&s[i]==C&&is(bfe[i],nex[i]))	erase(i),--c3;
	if(c2<c3){
		for(int i=1;i<=n&&c2<c3;i++)
			if(!vi[i]&&check(i,nex[i],A,C)&&is(bfe[i],nex[nex[i]]))
				erase(nex[i]),erase(i),--c1,--c3;
	}
	for(int i=1;i<=n&&c1<c2;i++)
		if(!vi[i]&&check(i,nex[i],B,C)&&is(bfe[i],nex[nex[i]]))
			erase(nex[i]),erase(i),--c2,--c3;
	for(int i=1;i<=n&&c1<c2&&c1<c3;i++)
		if(!vi[i]&&is(bfe[i],nex[i])){
			if(s[i]==B)	--c2,erase(i);
			if(s[i]==C)	--c3,erase(i);
		}
	pri();
}
int main(){
	freopen("1.out","w",stdout);
	freopen("1.in","r",stdin);
	scanf("%s",s+1),n=strlen(s+1);
	a[0].ch='A',a[1].ch='B',a[2].ch='C';
	for(int i=1;i<=n;i++){
		bfe[i]=i-1;
		if(i!=n)	nex[i]=i+1;
	}
	for(int i=1;i<=n;i++)
		if(s[i]==s[i-1])	erase(i);
	for(int i=1;i<=n;i++){
		if(vi[i])	continue;
		if(s[i]=='A')	a[0].cnt++;
		else	if(s[i]=='B')	a[1].cnt++;
		else	a[2].cnt++;
	}
	sort(a,a+3,com);
	A=a[0].ch,B=a[1].ch,C=a[2].ch,solve();
	return 0;
}

```

---

## 作者：myee (赞：2)

### 前言

对着样例随便猜了个做法就过了。

然后没有证明被 ban 了。。。补一个比较粗略的证明，但是已经足够。

### 思路

我们先把原串中相邻相同字符缩一起，统计三种字符出现次数，不妨出现次数上 $\operatorname{cnt}(\texttt A)\le\operatorname{cnt}(\texttt B)\le\operatorname{cnt}(\texttt C)$

我们先反复把 $\tt BCB$ 缩成 $\tt B$ 直至 $\operatorname{cnt}(\texttt A)=\operatorname{cnt}(\texttt B)$ 或不存在该结构。

然后反复把 $\tt XBY$ 缩成 $\tt XY$ 直至 $\operatorname{cnt}(\texttt A)=\operatorname{cnt}(\texttt B)$ 或不存在该结构。其中 $\tt X$，$\tt Y$ 可为空，但不可均为 $\tt A$。

最后反复把 $\tt CBC$ 缩成 $\tt C$ 直至 $\operatorname{cnt}(\texttt A)=\operatorname{cnt}(\texttt B)$。

然后反复把 $\tt XCY$ 缩成 $\tt XY$ 直至 $\operatorname{cnt}(\texttt B)=\operatorname{cnt}(\texttt C)$ 或不存在该结构。其中 $\tt X$，$\tt Y$ 可为空，但不可均为 $\tt A$ 或 $\tt B$。

最后反复把一对 $\tt ACA$，$\tt BCB$ 缩成一对 $\tt A$，$\tt B$ 直至 $\operatorname{cnt}(\texttt A)=\operatorname{cnt}(\texttt B)=\operatorname{cnt}(\texttt C)$。

容易发现该算法总可执行，且在前 $3$ 步中最大化已消的 $\tt C$ 及可能在第四步被消的 $\tt C$ 的总和，从而能最小化第五步执行次数。

~~严格的证明我不是很会，但这个做法毛估估就很对，一交就直接过了。~~

一个大致的证明：

注意到显然最后答案满足 $\le\operatorname{cnt}(\texttt A)$，那么在不进行最后一步时如已合法则取满这个上界；否则我们要尽可能减少最后一步进行的次数。

注意到最后一步每次会缩去 $1$ 个 $\texttt A$，$1$ 个 $\texttt B$ 和  $2$ 个 $\texttt C$，$\operatorname{cnt}(\texttt C)-\operatorname{cnt}(\texttt A)$ 每次减 $1$，所以我们最后的答案就是 $2\operatorname{cnt}(\texttt A)-\operatorname{cnt}(\texttt C)$；我们的目标就是在前几步**最小化**这个 $\operatorname{cnt}(\texttt C)$。

注意到第四步最终会把整个串变成由若干 $\texttt{ACAC\dots A}$ 和 $\texttt{BCBC\dots B}$ 交替拼起来的形态，因此我们要在前三步内**在不使 $\texttt{ACB}$ 和 $\texttt{BCA}$ 数目大量下降的情况下顺带拉走尽可能多的 $\texttt{C}$**。

然后就得到了前面的这个枚举顺序。

### Code

代码细节可能有一点，但是大部分代码是相同的。

```cpp
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    std::vector<chr>C;
    static uint Cnt[3];
    {
        chr c;
        while(~(c=getchar())&&c>='A'&&c<='C')
            if(C.empty()||c!=C.back())
                Cnt[c-'A']++,C.push_back(c);
    }
    chr Min=std::min_element(Cnt,Cnt+3)-Cnt+'A';
    chr Max=std::max_element(Cnt,Cnt+3)-Cnt+'A';
    if(Min==Max)Min='A',Max='B';
    chr Mid=Min^Max^64;
    uint cnt1=Cnt[Min-'A'],cnt2=Cnt[Mid-'A'],cnt3=Cnt[Max-'A'];
    if(cnt1<cnt2){
        std::vector<chr>User;
        for(auto c:C)
            if(cnt1<cnt2&&User.size()>=2&&User[User.size()-2]==Mid
                        &&User[User.size()-1]==Max&&c==Mid)
                User.pop_back(),cnt2--,cnt3--;
            else User.push_back(c);
        C=User;
    }
    if(cnt1<cnt2){
        std::vector<chr>User;
        for(auto c:C){
            if(cnt1<cnt2&&User.size()&&User.back()==Mid&&
                (User.size()==1||User[User.size()-2]!=c))
                    User.pop_back(),cnt2--;
            User.push_back(c);
        }
        if(cnt1<cnt2&&User.size()&&User.back()==Mid)User.pop_back(),cnt2--;
        C=User;
    }
    if(cnt1<cnt2){
        std::vector<chr>User;
        for(auto c:C)
            if(cnt1<cnt2&&User.size()>=2&&User[User.size()-2]==Max
                        &&User[User.size()-1]==Mid&&c==Max)
                User.pop_back(),cnt2--,cnt3--;
            else User.push_back(c);
        C=User;
    }
    if(cnt2<cnt3){
        std::vector<chr>User;
        for(auto c:C){
            if(cnt2<cnt3&&User.size()&&User.back()==Max&&
                (User.size()==1||User[User.size()-2]!=c))
                    User.pop_back(),cnt3--;
            User.push_back(c);
        }
        if(cnt2<cnt3&&User.size()&&User.back()==Max)User.pop_back(),cnt3--;
        C=User;
    }
    if(cnt2<cnt3){
        std::vector<chr>User;
        uint d1=cnt3-cnt2,d2=cnt3-cnt1;
        for(auto c:C)if(c==Max&&(User.back()==Min?d1:d2))
            (User.back()==Min?d1:d2)--,User.pop_back();
        else User.push_back(c);
        C=User;
    }
    for(auto s:C)putchar(s);
    return 0;
}
```



---

## 作者：RainySoul (赞：0)

丹砂 3700+，评分有点虚高。短暂成为猜结论大手子。

连续的相同字母一定不能选，直接缩起来变成一个。

我们采取**先猜后证**的方式，我们不妨设 $cnt_A\le cnt_B \le cnt_C$，不是这个顺序随便交换一下就可以了。

然后答案上界是 $3cnt_A$，考虑尽量逼近这个答案。从删数角度思考，要删到 $cnt_A=cnt_B=cnt_C$ 时使得 $cnt_A$ 尽量大，万不得已的时候你一定不希望删 $A$，所以先考虑删 $B$ 和 $C$。对着手搓的数据糊了一个很符合直觉的做法：

接下来我们文中的 $AB$ 一律指 $AB/BA$，以此类推。
1. $cnt_B<cnt_C$ 时如果能删 $C$ 一定先删 $C$；
2. $cnt_A<cnt_B=cnt_C$ 时如果能够删连在一起的 $BC$，删掉答案不劣；
3. 如果上面两个没有能够操作的话现在不得不删除某个 $A$，不过它删掉的时候一定带走一个 $B$ 和 $C$ 这很容易做到。若此时有 $cnt_B=cnt_C$ 的话由前面的条件可知现在至少存在一个能删的 $AB$，为了保证 $cnt_B \le cnt_C$ 的相对大小关系，删除一个连在一起的 $AB$ 并重复上述步骤；
4. 如果此时有 $cnt_B<cnt_C$ 的话至少存在一个能删的 $AC$，那么删掉一个并重复上述步骤。

::::warning[注意]{open}
这里“可以删除”意为删除之后不会让两个相同字符并在一起。
::::

于是你按照上面这个思路写了个近似 $O(n^2)$ 的暴力实现发现并未挂拍，交一发 T 了一半 A 了一半，那它非常对，但是好像没有什么优化前途，估计是性质找少了。

然后发现一个很有意思的事是

::::success[$cnt_A<cnt_B=cnt_C$ 时不断删 $BC$ 一定可以删到 $cnt_A=cnt_B=cnt_C$]{open}
采用反证法，如果此时不存在可以删除的 $BC$ 则有两种情况：

1. 已经没有连在一起 $BC$ 了，这种情况下只能是 $XAXAXAX$，最优情况下 $A$ 都不够用，所以这种情况不合法。
2. 部分 $B$ 和 $C$ 分散分布，剩下的组成 $ABCA$ 这样的结构。由于你要消耗尽量少的 $A$ 所以分散分布不如 $ABCA$ 优，考虑最优情况下是长这样的：$B[ABC]_nAC$，最好的构造下仍然做不到 $cnt_A<cnt_B=cnt_C$，所以这种情况仍然不合法。

所以此时总存在可以删除的 $BC$，你可以不断删除直到 $cnt_A=cnt_B=cnt_C$。
::::

这个性质相当强了，不妨考虑直接将原序列操作到 $cnt_A\le cnt_B=cnt_C$ 的状态然后通过删 $BC$ 搞出来答案。把前面做法直接搬过来，首先删 $C$，然后如果还没有 $cnt_B=cnt_C$ 删 $AC$ 直到 $cnt_B=cnt_C$。然后过了。看这个结论其实还挺自然的吧。

证明：
::::success[$cnt_A\le cnt_B <cnt_C$ 时直接删 $C$]{open}
1. 首先直接删 $C$ 对于最后删 $BC$ 的过程没有任何影响，因为我们开始证明了只要满足 $cnt_A \le cnt_B =cnt_C$ 都能删干净。

2. 对于删 $AC$ 的过程，你将现在可以单独删的 $C$ 留到 $AC$ 时候删只会让答案更劣。

没有一点问题。
::::


::::success[$cnt_A\le cnt_B < cnt_C$ 删除 $AC$ 直到 $cnt_B=cnt_C$ 不劣]{open}
首先已经把能单独删除的 $C$ 删完了，然后删 $BC$ 对于 $cnt_C$ 接近 $cnt_B$ 毛用没有。删 $A$ 对答案是负贡献，删 $AB$ 对于 $cnt_C$ 接近 $cnt_B$ 是负贡献。

所以这里你唯一能动的就是 $AC$。
:::::success[总有 $AC$ 可以删]{open}
所有的 $C$ 只能出现在 $ACA$ 和 $BCB$ 两种结构中，考虑 $C$ 最多的时候这个序列长这样：$ACACABCBCB$。

这时候你考虑最大化操作次数时是最小化 $B$，直接取 $cnt_B=cnt_A$，设 $x$ 个 $A$，则 $B$ 也 $x$ 个，$C$ 有 $2x-2$ 个，至多操作 $x-1$ 次，正好操作到 $cnt_B=cnt_C$ 了。
:::::

随便整个 `map` 维护一下，时间复杂度 $O(n \log n)$。

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct zyx{
    int cnt;
    char num;
}a[10];
string St,S;
map<int,char> s;
bool cmp(zyx a,zyx b){return a.cnt<b.cnt;}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>St;
    a[1].num='A',a[2].num='B',a[3].num='C';
    for(int i=0;i<(int)St.size();i++)
        if(St[i]!=St[i+1])S+=St[i];
    int now=0;
    for(int i=0;i<(int)S.size();i++){
        if(S[i]=='A')a[1].cnt++;
        else if(S[i]=='B')a[2].cnt++;
        else a[3].cnt++;
        s[now]=S[i],now++;
    }
    sort(a+1,a+1+3,cmp);
    if(a[3].cnt>a[2].cnt){
        for(auto it=(++s.begin());it!=s.end();){
            auto NEXT=next(it),temp1=it,temp2=it;
            temp1--,temp2++;
            if(temp2==s.end())break;
            if((*it).second==a[3].num&&(*temp1).second!=(*temp2).second){
                s.erase(it),a[3].cnt--;
                if(a[3].cnt==a[2].cnt)break;
            }
            it=NEXT;
        }
        auto temp=s.end();temp--;
        if(a[3].cnt>a[2].cnt&&(*temp).second==a[3].num)s.erase(temp),a[3].cnt--;
        temp=s.begin();
        if(a[3].cnt>a[2].cnt&&(*temp).second==a[3].num)s.erase(temp),a[3].cnt--;
    }
    if(a[3].cnt>a[2].cnt){
        for(auto it=s.begin();it!=s.end();){
            auto temp1=it;temp1++;
            if(temp1==s.end())break;
            auto NEXT=next(it);
            if(((*it).second==a[1].num&&(*temp1).second==a[3].num)||((*it).second==a[1].num&&(*temp1).second==a[3].num)){
                auto temp2=it,temp3=temp1;
                temp3++;    
                if(it==s.begin()||temp3==s.end()){
                    NEXT=next(temp1);s.erase(it);s.erase(temp1);
                    a[1].cnt--,a[3].cnt--;
                    if(a[3].cnt==a[2].cnt)break;
                }
                else{
                    temp2--;
                    if((*temp2).second!=(*temp3).second){
                        NEXT=next(temp1);s.erase(it);s.erase(temp1);
                        a[1].cnt--,a[3].cnt--;
                        if(a[3].cnt==a[2].cnt)break;
                    }
                }
            }
            it=NEXT;
        }
    }
    if(a[2].cnt>a[1].cnt){
        for(auto it=s.begin();it!=s.end();){
            auto temp1=it;
            temp1++;
            if(temp1==s.end())break;
            auto NEXT=next(it);
            if(((*it).second==a[2].num&&(*temp1).second==a[3].num)||((*it).second==a[2].num&&(*temp1).second==a[3].num)){
                auto temp2=it,temp3=temp1;
                temp3++;    
                if(it==s.begin()||temp3==s.end()){
                    NEXT=next(temp1);s.erase(it);s.erase(temp1);
                    a[2].cnt--,a[3].cnt--;
                    if(a[1].cnt==a[2].cnt)break;
                }
                else{
                    temp2--;
                    if((*temp2).second!=(*temp3).second){
                        NEXT=next(temp1);s.erase(it);s.erase(temp1);
                        a[2].cnt--,a[3].cnt--;
                        if(a[1].cnt==a[2].cnt)break;
                    }
                }
            }
            it=NEXT;
        }
    }
    if(a[1].cnt!=a[2].cnt||a[1].cnt!=a[3].cnt||a[2].cnt!=a[3].cnt)return 0;
    for(auto i=s.begin();i!=s.end();i++)cout<<(*i).second;
    return 0;
}
```

其实我认为证明部分可能会出锅，如果您发现它有问题可以私信我。

闲话：煎饼果子好吃，椰果奶茶好喝。

---

## 作者：xht (赞：0)

## [ABC String](https://atcoder.jp/contests/agc036/tasks/agc036_e)

### 题意

- 给定一个仅包含 `ABC` 的字符串 $s$。
- 要求 $s$ 的一个最长子序列，满足 `ABC` 出现次数相同，且相邻字符不同。
- $|s| \le 10^6$。

### 题解

考虑将 $s$ 中相邻的相同字符缩成一个，这显然不影响答案。

记 $s$ 中 `A,B,C` 的出现次数分别为 $c_A,c_B,c_C$，不妨设 $c_A \le c_B \le c_C$。

将 `A` 看作分隔符，则将当前串分成了 $c_A + 1$ 段，每段只有 `B,c`。记 `B,C` 都有的段数为 $c_1$，单个 `B` 的段数为 $c_2$，单个 `C` 的段数为 $c_3$，若 $c_1 + c_2 \ge c_3$，可以构造取到答案的上界 $3c_A$：

1. 每次找到一个 `C`，满足删去它之后串内相邻字符依然不相同，删去它，直到 $c_B = c_C$。
2. 每次找到相邻的 `B` 和 `C`，满足删去它们之后串内相邻字符依然不相同，删去它们，直到 $c_A = c_B = c_C$。

若 $c_1 + c_2 < c_3$，每次找到单个 `C` 段，删去 `C` 以及 $0/1$ 个 `A`（优先考虑首尾，这样不用删 `A`），直到 $c_1+c_2 \ge c_3$，然后使用上面的构造方法即可。

使用链表维护，时间复杂度 $\mathcal O(n)$；使用 `set` 维护，时间复杂度 $\mathcal O(n \log n)$。

### 代码

```cpp
const int N = 1e6 + 7;
int n, t[3];
char s[N], c[3];
set<int> p;

inline void del(int x, int c) {
	p.erase(x), --t[c];
}

int main() {
	rds(s, n);
	for (int i = 0; i < 3; i++) c[i] = 'A' + i;
	for (int i = 1; i <= n; i++)
		if (s[i] != s[i+1]) p.insert(i), ++t[s[i]-'A'];
	if (t[1] > t[2]) swap(t[1], t[2]), swap(c[1], c[2]);
	if (t[0] > t[1]) swap(t[0], t[1]), swap(c[0], c[1]);
	if (t[1] > t[2]) swap(t[1], t[2]), swap(c[1], c[2]);
	int c1 = 0, c2 = 0, c3 = 0, o1 = 0, o2 = 0;
	for (int x : p)
		if (s[x] == c[0]) {
			if (o1 && o2) ++c1;
			else if (o1) ++c2;
			else if (o2) ++c3;
			o1 = o2 = 0;
		} else if (s[x] == c[1]) o1 = 1;
		else o2 = 1;
	if (o1 && o2) ++c1;
	else if (o1) ++c2;
	else if (o2) ++c3;
	o1 = o2 = 0;
	if (c1 + c2 < c3) {
		if (s[*p.begin()] == c[2] && s[*++p.begin()] == c[0])
			del(*p.begin(), 2), --c3;
		if (c1 + c2 < c3) {
			if (s[*--p.end()] == c[2] && s[*--(--p.end())] == c[0])
				del(*--p.end(), 2), --c3;
			if (c1 + c2 < c3)
				for (int x : p)
					if (s[x] == c[0]) {
						if (o1 && o2) {
							del(o1, 0), del(o2, 2);
							o1 = x, o2 = 0;
							if (c1 + c2 == --c3) break;
						} else o1 = x, o2 = 0;
					} else if (s[x] == c[1]) o1 = 0, o2 = 0;
					else if (s[x] == c[2]) {
						if (o1 && !o2) o2 = x;
						else o1 = 0, o2 = 0;
					}
		}
	}
	if (t[1] < t[2]) {
		auto it = p.begin();
		while (it != p.end()) {
			auto itl = it, itr = it;
			if (s[*it] != c[2] || !(it == p.begin() || ++itr == p.end() || s[*--itl] != s[*itr])) {
				++it;
				continue;
			}
			del(*it++, 2);
			if (t[1] == t[2]) break;
		}
	}
	if (t[0] < t[1]) {
		auto it = p.begin();
		while (it != p.end()) {
			auto itl = it, itr = it, itrr = it;
			if (s[*it] == c[0] || ++itr == p.end() || s[*itr] == c[0] || s[*it] == s[*itr] || !(it == p.begin() || (itrr = itr, ++itrr) == p.end() || s[*--itl] != s[*itrr])) {
				++it;
				continue;
			}
			int x = s[*it] == c[1] ? 1 : 2, y = x == 1 ? 2 : 1;
			del(*it++, x), del(*it++, y);
			if (t[0] == t[1]) break;
		}
	}
	for (int x : p) printc(s[x]);
	return 0;
}
```

---

