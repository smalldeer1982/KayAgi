# Longest Palindrome

## 题目描述

Returning back to problem solving, Gildong is now studying about palindromes. He learned that a palindrome is a string that is the same as its reverse. For example, strings "pop", "noon", "x", and "kkkkkk" are palindromes, while strings "moon", "tv", and "abab" are not. An empty string is also a palindrome.

Gildong loves this concept so much, so he wants to play with it. He has $ n $ distinct strings of equal length $ m $ . He wants to discard some of the strings (possibly none or all) and reorder the remaining strings so that the concatenation becomes a palindrome. He also wants the palindrome to be as long as possible. Please help him find one.

## 说明/提示

In the first example, "battab" is also a valid answer.

In the second example, there can be 4 different valid answers including the sample output. We are not going to provide any hints for what the others are.

In the third example, the empty string is the only valid palindrome string.

## 样例 #1

### 输入

```
3 3
tab
one
bat```

### 输出

```
6
tabbat```

## 样例 #2

### 输入

```
4 2
oo
ox
xo
xx```

### 输出

```
6
oxxxxo```

## 样例 #3

### 输入

```
3 5
hello
codef
orces```

### 输出

```
0```

## 样例 #4

### 输入

```
9 4
abab
baba
abcd
bcde
cdef
defg
wxyz
zyxw
ijji```

### 输出

```
20
ababwxyzijjizyxwbaba```

# 题解

## 作者：_ztyqwq (赞：5)

### Description

给定 $ n $ 个长度均为 $ m $ 的 **两两不同的** 字符串，请你删去其中的几个（可以是 $ 0 $ 个），使得剩下的字符串 **以某种顺序（不一定要输入中的顺序）** 首尾相接可以拼成一个回文字符串，且这个回文串的长度最大。

输出最大长度和这个回文串。

### Solution

首先显然 “删去若干个字符串” 相当于 “选出若干个字符串”。

因为所有字符串的长度均相同，所以在最后拼接成的回文串中，选出的第一个串与最后一个串一定是恰好 “相反” 的，第二个串与倒数第二个串也是恰好 “相反” 的。

More Formally, 设最后我们依次选出了 $ t_1, t_2, ..., t_k $ 这些字符串，那么 $ t_i = rev(t_{k + 1 - i}) $，其中 $ rev $ 代表将一个字符串翻转（即 STL 的 `reverse` 函数）。

For Example, 在第四个样例中，最终的答案 $ = \texttt{"abab" + "wxyz" + "ijji" + "zyxw" + "baba"} $（选出的五个字符串），而 $ \texttt{"abab"} = rev(\texttt{"baba"}), \texttt{"wxyz"} = rev(\texttt{"zyxw"}), \texttt{"ijji"} = rev(\texttt{"ijji"}) $。

这就启发我们，可以对于每个字符串，我们看它的翻转（`reverse`）是否在 $ n $ 个字符串中。如果在，说明这一对 “相反” 的字符串可以分别添加到答案的头和尾。

如果它的翻转不在 $ n $ 个字符串中，那么它就不可能添加到答案中。

接着我们发现，答案里 **正中间** 的一个字符串（如果有，即我们选了奇数个字符串）一定是回文的。那么我们只要找到任意一个回文的字符串，将它安置在答案的中间即可。如果没有回文串，那么就没有一个字符串可以成为答案的 “正中间”，即我们只能选出偶数个字符串（成对）。

所以总结一下，最后答案就是 **若干对互为“翻转”的字符串（在头尾） + 中间的一个回文串（如果有）**。

时间复杂度 $ O(n\log n + nm) $（每个字符串求翻转 $ O(nm) $，`map` 有一只 $ \log $）

### Code

代码中，`mp` 表示该字符串的编号，或下标（如果没有出现即为 $ 0 $）

`ans` 数组为这个字符串是 **第几对**（一头一尾） 的字符串。如果 `ans[i] = -1` 说明该字符串作为正中间的字符串。

`ind` 数组表示输出时第 `i` 对字符串为 `s[i]` 与它的翻转。`ind[0]` 为正中间字符串的标号。

因为字符串两两不同的，所以不需要考虑一些奇怪的问题。但是还是有一些细节要处理，比如同一对字符串会被找到两次，第二次要去重；最后的输出可以采用先正序输出前一半，再倒序输出后一半。

代码写得有些急，稍有些乱请见谅 QAQ

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[101];
map<string, int> mp;
string rev(string s)
{
	string ans;
	int n = s.size();
	for(int i = n - 1; i >= 0; i--)
		ans += s[i];
	return ans;
}
int ans[101], ind[101];
int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		cin >> s[i];
		mp[s[i]] = i;
	}
	int ps = 0, md = 0, tot = 0;
	for(int i = 1; i <= n; i++)
	{
		string ss = rev(s[i]);
		if(s[i] == ss)
		{
			if(!md)
			{
				md = 1;
				ans[i] = -1;
				ind[0] = i;
			}
		}
		else if(mp[ss] && !ans[mp[ss]])
		{
			ans[i] = ++tot;
			ind[tot] = i;
			ps++;
		}
	}
	printf("%d\n", (ps * 2 + md) * m);
	for(int i = 1; i <= ps; i++)
	{
		int p = ind[i];
		cout << s[p];
	}
	cout << s[ind[0]];
	for(int i = ps; i >= 1; i--)
	{
		int p = ind[i];
		cout << s[mp[rev(s[p])]];
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：123456zmy (赞：3)

题意：  
给你 $n$ 个长 $m$ 的串，问由这些串连接形成的最长回文串的长度是多少，并输出此回文串。
___
首先看每个串与哪些串连接会形成回文，然后暴力加入答案输出即可。注意如果本身就是回文串，则可以放到中间。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[101][101],an[101],ans,ansnl[51],ansnr[51];
bitset<101> used;
string s[101];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)
	{
		bool ok=1;
		for(int k=0;k<m;k++)if(s[i][k]!=s[j][m-k-1]){ok=0;break;}
		if(ok)a[i][++an[i]]=j,a[j][++an[j]]=i;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=an[i];j++)if(a[i][j]!=i&&used[i]==0&&used[a[i][j]]==0)
	{
		used[i]=used[a[i][j]]=1;
		ans+=2;
		ansnl[ans>>1]=i;
		ansnr[ans>>1]=a[i][j];
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=an[i];j++)if(a[i][j]==i&&used[i]==0)
	{
		printf("%d\n",ans*m+m);
		for(int _i=1;_i<=(ans>>1);_i++)cout<<s[ansnl[_i]];
		cout<<s[i];
		for(int _i=(ans>>1);_i>=0;_i--)cout<<s[ansnr[_i]];
		return 0;
	}
	printf("%d\n",ans*m);
	for(int _i=1;_i<=(ans>>1);_i++)cout<<s[ansnl[_i]];
	for(int _i=(ans>>1);_i>=0;_i--)cout<<s[ansnr[_i]];
	return 0;
}
```

---

## 作者：coconutt_ (赞：1)

**题意**

给定n个长度为m的字符串，选定其中几个以形成可以形成最长的回文串，先输出可组成的最长的回文串的长度，并再输出这个回文串。

**思路**

通过分析题目，我们可以发现若要列在“合格”回文串当中，必须达成以下两点中其中一点：

* 自己本身是一个回文串

* 自己并不是回文串，但是存在另一个串是自己的倒序。

* 如果自己是回文串，也存在自己倒序的另一半，那么优先选择与另一半拼在一起组成回文串。因为题目要求的是最长的。


然后就可以根据这个性质进行寻找。对每一个字符串进行匹配，寻找另一半或者是判断自己是不是回文串。然后把合格的子串全部拼在一起，并输出长度。


**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[105];
string sd[105];
string sx[105];
bool QAQ[105]={0};
bool qwq(string s1,string s2){
	string s3;
	for(int q=s1.size()-1;q>=0;q--){
		s3+=s2[q];
	}
	return s1==s3;
}
bool qaq(string s){
	for(int op=0;op<s.size()/2;op++){
		if(s[op]!=s[s.size()-1-op]){
			return false;
		}
	}
	return true;
}
int main(){
	int n,b;
	string rt="";
	bool ed=false;
	cin >> n >> b;
	int ans=0;
	int pop=0;
	for(int i=0;i<n;i++){
		cin >> s[i];
	}
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(!QAQ[i]&&!QAQ[j]&&qwq(s[i],s[j])){
				ans+=2*b;
				QAQ[i]=1;
				QAQ[j]=1;
				pop++;
				sd[pop]=s[i];
			//	cout << s[i] << endl;
				sx[pop]=s[j];
			//	cout << s[j] << endl;
			}
		}
		if(!QAQ[i]&&qaq(s[i])&&!ed){
			ans+=b;
			QAQ[i]=true;
			ed=true;
			rt=s[i];
		}
	}
	if(!QAQ[n-1]&&qaq(s[n-1])&&!ed){
		ans+=b;
		ed=true;
		rt=s[n-1];
	}
	string answ;
	cout << ans << endl;
	if(ans!=0){
		if(ed){
			for(int i=1;i<=pop;i++){
				answ+=sd[i];
			}
			answ+=rt;
			for(int i=pop;i>0;i--){
				answ+=sx[i];
			}
			cout << answ << endl;
		}else{
			for(int i=1;i<=pop;i++){
				answ+=sd[i];
			}
			for(int i=pop;i>0;i--){
				answ+=sx[i];
			}
			cout << answ << endl;
		}
	}
	return 0;
}
```


---

## 作者：fls233666 (赞：0)

我们观察一下样例输出，看看哪些字符串是可以被拼到最终的答案中。

我们可以发现，只有以下两种字符串会被拼到最终答案中：

- 字符串反转后得到的新字符串也在这 $n$ 个字符串中（可以放在首尾）。
- 字符串本身就是回文字符串（放在中间）。

对于前一种情况，可以把字符串存到一个 multiset 中进行匹配，匹配成功就从 multiset 中删除并加入答案。

对于第二种情况，因为字符串长度相同，所以找到一个回文字符串就标记即可。

对上述思想进行代码实现，得到如下代码：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<set>
#define rgt register int
using namespace std;

int n,m,lenf,lenr;
//lenf 与 lenr 分别记录左右端要拼接的字符串数量
const int mxn = 111;
string str[mxn],tmp;
string hg,fans="";
//hg 为拼在中间的回文字符串
//fans 为拼出来的最终答案
string lf[mxn],rt[mxn];
//lf 与 rt 分别存储要拼接在左/右端的字符串
multiset <string> ff;   //用于匹配字符串的 multiset
bool fmid;   //标记是否找到中间的回文字符串

inline string rever(string s){   //字符串反转函数
	string ans="";
	for(rgt i=m-1;i>=0;i--)
		ans+=s[i];
	return ans;
}

int main()
{
	cin>>n>>m;
	for(rgt i=1;i<=n;i++){
		cin>>str[i];
		tmp=rever(str[i]);
        
		if(!fmid&&tmp==str[i]){  //检查读入的字符串是否为回文字符串
			hg=str[i];
			fmid=true;
		}else{   //不是则匹配
			if(ff.find(tmp)!=ff.end()){  //匹配成功
				ff.erase(ff.find(tmp)); //删除
				lenf++;
				lenr++;
				lf[lenf]=str[i];
				rt[lenr]=tmp;//加入答案
			}else{  //匹配失败，加入 multiset
				ff.insert(str[i]);
			}
		}
        
	}
    
	if(!fmid&&lenf==0&&lenr==0){  //无解
		cout<<"0"<<endl;
		return 0;
	}else{  //拼接答案并输出
		for(rgt i=1;i<=lenf;i++)
			fans+=lf[i];
		if(fmid)	fans+=hg;
		for(rgt i=lenr;i>=1;i--)
			fans+=rt[i];
		cout<<fans.size()<<endl<<fans;
	}
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

~~因为数据不大，可以二重循环暴力。~~

重点是对于自身回文的字符串只能一个。题目中说了：

### 所有字符串都是不同的。

对于每两个串（回文）用两个数组保存。a保存前者，b保存后者。最后输出，B要反过来！
```cpp
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int (i)=0; i<(int)(n); i++)

bool ok(string s) {
	string t = s;
	reverse(t.begin(),t.end());
	return t == s;
}

string a[110];
bool used[110];
vector <string> ans1,ans2;

int main(void) {
	int N,M,ans = 0;
	string s = "%";
	cin >> N >> M;
	REP(i,N) cin >> a[i];
	REP(i,N) {
		if(ok(a[i])) {
			s = a[i];
			continue;
		}
		REP(j,N) {
			if(i == j) continue;
			string t = a[i]+a[j];
			if(ok(t) && used[i] == false && used[j] == false) {
				ans1.push_back(a[i]);
				ans2.push_back(a[j]);
				used[i] = used[j] = true;
			}
		}
	}
	ans = (ans1.size()+ans2.size());
	if(s != "%") ans++;
	cout << ans*M << endl;
	REP(i,ans1.size()) cout << ans1[i];
	if(s != "%") cout << s;
	reverse(ans2.begin(),ans2.end());
	REP(i,ans2.size()) cout << ans2[i];
	cout << endl;
	return 0;
}

```


---

## 作者：Trilliverse (赞：0)

## 字符串的构造
---
看了一下这题思路都差不多：

1. 如果本身就是回文串，直接加到**anss**(记录答案的字符串) 这里要注意只能加一个 比如样例2就有2个回文串 **但只能选一个**
---
2. 判断如果原字符串中有一对 一个加到anss的头，另一个加到anss的尾

#### 但在代码实现上方法就很多了

- 这里我用了函数构造的 不清楚的详见[reverse](https://zh.cppreference.com/w/cpp/algorithm/reverse)

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

string s[105];
map<string,int> vis;
set<string> ori;
int main() {
	int n,m;
	cin >> n >> m;
	string anss;
	bool flag = false;
	for(int i=1;i<=n;i++) {
		cin >> s[i]; 
		ori.insert(s[i]);
		string t = s[i];
		reverse(s[i].begin(),s[i].end());
		if(s[i] == t) {//判断如果反转后一样 说明本来就是回文
			if(!flag) {//因为只能选一次 所以这里我用flag标记
				flag = true;
				anss += t;
				vis[s[i]] = 1;
			}
			else vis[s[i]] = 1;
			//cout << anss << endl;
		}
	}
	//vis是来比较该字符串有没有被用来构造过
	for(int i=1;i<=n;i++) {
		if(vis[s[i]] == 0 && ori.find(s[i]) != ori.end()) {
			vis[s[i]] = 1;//这里要注意这一对(2个)回文串都要标记掉
			anss.insert(0,s[i]);
			//cout <<anss <<endl;
			int nl = anss.size();
			reverse(s[i].begin(),s[i].end());
			vis[s[i]] = 1;
			anss.insert(nl,s[i]);
			//cout <<anss <<endl;
		}
	}
	cout << anss.length() << "\n" << anss << endl;
	return 0;
}


```


---

## 作者：ShineEternal (赞：0)

[可能更佳的阅读效果](https://blog.csdn.net/kkkksc03/article/details/104338145)
。
## description：

- 给你 $n$ 个长度为 $m$ 的字符串。

- 请你判断删去其中的几个（或者不删去），能使得将剩下字符串随意排列所形成的回文串长度最大。

- 请你输出最大的长度和那个回文串。

- $1\le n\le 100$，$1\le m\le 50$。

- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution:

我们将字符串两两判断，是否有一个与另一个的倒序相等即可。

但是要注意可能可以在最中间填一个自身回文串，且最多填一个，所以还要考虑这种情况，把自身回文串找出来，如果有一个没被用过，那就填进去即可。


## code：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
char s[105][55],sx[105][55];
int mp[1005];
int a[1005];
int m;
int check(int i,int j)
{
	for(int k=0;k<m;k++)
	{
		if(s[i][k]!=s[j][m-k-1])return 0;
	}
	return 1;
}
int main()
{
	int n;
	scanf("%d%d",&n,&m);
	int tmp=-1;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]);
		
	}
	/*for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
		{
			int k=m-j-1;
			sx[i][j]=s[i][k];
		}
	}*/
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			//cout<<s[i]<<endl;
			if(check(i,j))
			{
			//	printf("%d %d\n",i,j);
				a[++cnt]=i;
				a[++cnt]=j;
				//printf("cnt=%d\n",cnt);
				//ans++;
			}
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		mp[a[i]]=1;
	}
	//printf("mp=%d\n",mp[4]);
	for(int i=1;i<=n;i++)
	{
		if(mp[i]!=1)
		{
			//printf("i=%d\n",i);
			int tag=0;
			for(int j=0;j<m;j++)
			{
				if(s[i][j]!=s[i][m-j-1])
				{
					tag=1;
					break;
				}
			}
			if(tag==0)
			{
				tmp=i;
			}
		}
	}
	//printf("tmp=%d\n",tmp);
	if(tmp!=-1)
	printf("%d\n",(cnt+1)*m);
	else
	printf("%d\n",cnt*m);
	for(int i=1;i<=cnt;i++)
	{
		if(i%2==1)
		{
			//if(a[i]==tmp)flag=1;
			printf("%s",s[a[i]]);
		}
		//cout<<s[a[i]];
	}
	if(tmp!=-1)
	{
		printf("%s",s[tmp]);
	}
	for(int i=cnt;i>=2;i--)
	{
		if(i%2==0)
		{
		//	if(a[i]==tmp)flag=1;
			printf("%s",s[a[i]]);
		}
	}
	printf("\n");
	return 0;
} 
```

---

