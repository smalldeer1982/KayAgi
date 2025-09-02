# Lex String

## 题目描述

Kuznecov likes art, poetry, and music. And strings consisting of lowercase English letters.

Recently, Kuznecov has found two strings, $ a $ and $ b $ , of lengths $ n $ and $ m $ respectively. They consist of lowercase English letters and no character is contained in both strings.

Let another string $ c $ be initially empty. Kuznecov can do the following two types of operations:

- Choose any character from the string $ a $ , remove it from $ a $ , and add it to the end of $ c $ .
- Choose any character from the string $ b $ , remove it from $ b $ , and add it to the end of $ c $ .

But, he can not do more than $ k $ operations of the same type in a row. He must perform operations until either $ a $ or $ b $ becomes empty. What is the lexicographically smallest possible value of $ c $ after he finishes?

A string $ x $ is lexicographically smaller than a string $ y $ if and only if one of the following holds:

- $ x $ is a prefix of $ y $ , but $ x \neq y $ ;
- in the first position where $ x $ and $ y $ differ, the string $ x $ has a letter that appears earlier in the alphabet than the corresponding letter in $ y $ .

## 说明/提示

In the first test case, it is optimal to take two 'a's from the string $ a $ and add them to the string $ c $ . Then it is forbidden to take more characters from $ a $ , hence one character 'b' from the string $ b $ has to be taken. Following that logic, we end up with $ c $ being 'aabaabaa' when string $ a $ is emptied.

In the second test case it is optimal to take as many 'a's from string $ a $ as possible, then take as many 'b's as possible from string $ b $ . In the end, we take two 'c's from the string $ a $ emptying it.

## 样例 #1

### 输入

```
3
6 4 2
aaaaaa
bbbb
5 9 3
caaca
bedededeb
7 7 1
noskill
wxhtzdy```

### 输出

```
aabaabaa
aaabbcc
dihktlwlxnyoz```

# 题解

## 作者：sLMxf (赞：2)

思路：贪心

我们知道，肯定字典序越靠前的字符串，肯定越靠前的字母越小。

考虑每一次插入数组 $c$ 的字符，是在 $a,b$ 中没选过的最小的字母。

那么得先给 $a,b$ 数组排序。

这里可以先将 $a,b$ 转化成数字数组，更加方便以后的操作。记得输出 $c$ 数组时要用字符形式输出。

记得特判选某一个数组是否达到了 $k$ 次。如果达到了，只能选另外一个。

code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[101],b[101],c[101];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		string aa,bb;int k;bool x;int s=0;
		int len1,len2;
		cin>>len1>>len2>>k;
		cin>>aa>>bb;
		for(int i=1;i<=len1;i++) a[i]=aa[i-1];
		for(int i=1;i<=len2;i++) b[i]=bb[i-1];
		sort(a+1,a+len1+1);
		sort(b+1,b+len2+1);
		int len3=1,l1=1,l2=1;
		while(len3<=len1+len2&&l1<=len1&&l2<=len2)
		{
			if(s==k)
			{
				if(x==0) c[len3++]=b[l2++];
				else c[len3++]=a[l1++];
				x^=1,s=1;
			}
			else
			{
				if(a[l1]<b[l2])
				{
					c[len3++]=a[l1++];
					if(x==0) s++;
					else x=0,s=1;
				}
				else
				{
					c[len3++]=b[l2++];
					if(x==1) s++;
					else x=1,s=1;
				}
			}
		}
		for(int i=1;i<len3;i++) cout<<char(c[i]);
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：artalter (赞：2)

# CF1689A Lex String 题解
## 1.做法
贪心。将 $A,B$ 两个字符串按字符 ASCII 码值升序排序。若在同一个字符串中已经连续选了 $k$ 个字符，就选另一个字符串中最小的字符，否则选取两个字符串中最小的字符。当有一个字符串为空时，得到的 $C$ 就是字典序最小的 $C$。
## 2.证明
为什么这么贪是合理的

首先，题目保证两个字符串中不含有相同字符

未到达 $k$ 的限制时，如果在某一步我们选择了 ASCII 码值更大的个字符，所得到的字符串一定比按照我们贪心策略所得到的字符串字典序更大。

到达 $k$ 的限制时，我们被限了从哪个字符串中选择。我们如果么选当前字符串中最小字符，所得到的字符串一定比按照我们贪心策略所得到的字符串字典序更大。

也就是说我们证明了，如果在某一步不按照贪心策略走，所得字符串字典序一定会不可逆地增大。因此我们地贪心策略就是最优策略

## 3.代码

```cpp
#include <bits/stdc++.h>
using namespace std;

char a[1005], b[1005], c[2050];
int main()
{
	int T;
	cin >> T;
	while (T-- > 0)
	{
		int n, m, k, tot1 = 0, tot2 = 0, tail1 = 1, tail2 = 1, tot = 0;
		tot1=tot2=tot=0;tail2=tail1=1;
		cin >> n >> m >> k;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		for (int i = 1; i <= m; i++)
			cin >> b[i];
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + m);
		while (tail1 <= n && tail2 <= m)
		{
			if (tot1 == k)
			{
				c[++tot] = b[tail2++];
				tot1 = 0, tot2 = 1;
			}
			else if (tot2 == k)
			{
				c[++tot] = a[tail1++];
				tot2 = 0, tot1 = 1;
			}
			else if (a[tail1] < b[tail2])
			{
				c[++tot] = a[tail1++];
				tot1++;
				tot2=0;
			}
			else
			{
				c[++tot] = b[tail2++];
				tot2++;
				tot1=0;
			}
		}
		for (int i = 1; i <= tot; i++)
		{
			cout << c[i];
		}
		if(T!=0)cout << endl;
		for(int i=0;i<=n+m+10;i++)a[i]=b[i]=c[i]=0;
	}
	return 0;
}
```

---

## 作者：云雷心柠檬听 (赞：1)

[博客食用更佳](https://www.cnblogs.com/lemon-cyy/p/17984635)

#### 题意简述

给定字符串 $a$ 和 $b$，每次从 $a$ 串或 $b$ 串中选出一个字符加入 $c$ 串，要求 $c$ 串的字典序最小。特别地，在 $c$ 串中不能出现连续 $k$ 次来源相同的字符。

#### 思维路径

由于字符是随意选取的，易于发现每次选 $a$ 串中字典序最小的字符或者 $b$ 串中字典序最小的字符一定比其他方案更优，因此先对 $a$ 串和 $b$ 串按照字典序排序。

接下来考虑新加入 $c$ 串的字符，假设对于两个串来说分别是加入 $a_i$ 和 $b_j$，有如下两种情况。
- 若无论加入哪个串都不会出现连续 $k$ 个来源相同的字符，那么选 $a_i$ 和 $b_j$ 字典序更小的那一个。
- 若加入某个串的字符会出现连续 $k$ 个来源相同的字符，那么选另一个串的字符。

最终某一个串被选完的时候立刻结束，此时的 $c$ 串就是答案。

#### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=109;
ll T,n,m,k;
char a[N],b[N],c[N*2];
ll nw,num,cnt;

void input(){
	cin>>n>>m>>k;
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll j=1;j<=m;j++) cin>>b[j];
}

void solve(){
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	cnt=0;
	ll j=1;
	nw=0; num=0;
	for(ll i=1;i<=n;i++){
		while(num==k||(j<=m&&a[i]>b[j])){
			c[++cnt]=b[j];
			j++;
			if(nw==2){
				num++;
			}
			else{
				nw=2; num=1;
			}
			if(num==k) break;
		}
		if(j>m) break;
		c[++cnt]=a[i];
		if(nw==1){
			num++;
		}
		else{
			nw=1; num=1;
		}
	}
	for(ll i=1;i<=cnt;i++) cout<<c[i]; cout<<"\n";
}

int main(){
	cin>>T;
	while(T--){
		input();
		solve();
	} 
	return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## Solution:

**本篇题解中用 $s, t$ 代表 $a, b$。**

简单贪心。

用一句话总结：如果某个字符可以选并且它是最小的，就选它。否则选另一个字串中最小的。

具体而言就是拿两个小跟堆存两个字串，命名为 $p, q$，$p$ 存 $s$ 的字符，$q$ 存 $t$ 的字符。

每次比较两个堆顶的大小，这里不妨设 $p$ 的堆顶比 $q$ 的堆顶小，另一种情况类似。

我们记录一个 $pos, cnt$ 表示上次所选和连续次数，$pos$ 用 $1$ 表示 $p$，用 $2$ 表示 $q$。

* 上一次选的不是 $p$，那这次放心选 $p$ 中最小的，$pos$ 更新为 $1$，$cnt$ 也更新为 $1$。

* 上一次选的是 $p$ 但连续次数小于 $k$，那这次任然选 $p$ 中最小的，$cnt$ 加一。

* 上一次选的是 $p$ 且连续次数达到了 $k$，那这次就只能选 $q$ 中最小的，$pos$ 更新为 $2$，$cnt$ 更新为 $1$。

每次最后把选中的堆的堆顶弹出即可。

还有不懂看代码。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int c, n, m, k;
string s, t;
priority_queue<int, vector<int>, greater<int>> p, q;
queue<int> r;
int main(){
	cin >> c;
	while(c--){
		cin >> n >> m >> k >> s >> t;
		while(!p.empty()){
			p.pop();
		}
		while(!q.empty()){
			q.pop();
		}
		while(!r.empty()){
			q.pop();
		}
		for(int i = 0; i < s.size(); i++){
			p.push(int(s[i] - 'a'));
		}
		for(int i = 0; i < t.size(); i++){
			q.push(int(t[i] - 'a'));
		}
		int cnt = 0;
		int pos = 0;
		while(!p.empty() && !q.empty()){
			if(p.top() < q.top()){
				if(pos != 1){
					pos = 1;
					cnt = 1;
					r.push(p.top());
					p.pop();
				}
				else{
					if(cnt < k){
						cnt++;
						r.push(p.top());
						p.pop();
					}
					else{
						pos = 2;
						cnt = 1;
						r.push(q.top());
						q.pop();
					}
				}
			}
			else{
				if(pos != 2){
					pos = 2;
					cnt = 1;
					r.push(q.top());
					q.pop();
				}
				else{
					if(cnt < k){
						cnt++;
						r.push(q.top());
						q.pop();
					}
					else{
						pos = 1;
						cnt = 1;
						r.push(p.top());
						p.pop();
					}
				}
			}
		}
		while(!r.empty()){
			cout << char(r.front() + 'a');
			r.pop();
		}
		cout << "\n";
	}
	return 0;
}
```

~~不要脸地求个赞~~

---

## 作者：expecto__patronum (赞：0)

## 分析：
$a$，$b$ 两个字符串，$n$，$m$ 分别是他们的长度。每次可以从他们之中取一个字符构成新串，不能连续 $k$ 次从同一个字符串中取字符，求构成字典序最小的字符串。

字典序最小：优先字母顺序，并不是长度短的更小（碎碎念：每次遇到字典序最小都要写一遍）

用字符数组存储 $a$，$b$ 两个字符串，对两个字符串按字典序排序后，从前往后像答案字符串添加。按题意模拟出答案字符串。

（碎碎念：写代码太烂真的是我的错┭┮﹏┭┮）
## 代码：
```

#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define guanliu ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const ll maxn=2e5+10;
const ll mod=1e9+7;
const ll INF=0x3f3f3f3f;
const double pi=acos(-1);
char a[150],b[150],ans[300];
bool cmp(char a,char b)
{
	return a<b;
}
int main() 
{
	guanliu;
	int t;
	cin>>t;
	while(t--)
	{
		int n,m,k;
		int cnt=0;
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<=m;i++)
		{
			cin>>b[i];
		}
		sort(a+1,a+1+n,cmp);
		sort(b+1,b+1+m,cmp);
		int i=1,j=1;
		int tt=0;
		int op=0;
		while(n&&m)
		{
			if(tt==k)
			{
				if(op==1)
				{

	ans[++cnt]=b[j++];
					op=2;
					tt=1;
					m--;
				}
				else {ans[++cnt]=a[i++];
					op=1;
					tt=1;
					n--;
				}
			}
			else {
				if(a[i]<b[j])
				{
					n--;
				ans[++cnt]=a[i++];
					if(op==1) tt++;
					else {

						op=1;
						tt=1;
					}
				}
				else {

					m--;
		ans[++cnt]=b[j++];

			if(op==2) tt++;
					else {
						op=2;
						tt=1;
					}
				}
			}
		}
	for(int i=1;i<=cnt;i++)
		{
			cout<<ans[i];
		}
		cout<<endl;
	} 
	return 0; 
}

```


---

## 作者：sz_jinzikai (赞：0)

# 题目描述：

[题目传送门](https://www.luogu.com.cn/problem/CF1689A)

# 思路：

贪心：把两个字符串的字符都按照从小到大的顺序排列，设定两个指针，一个指针（下面均简称 $i$）用于记录第一个字符串（下面均称为字符串 $a$）中**未选出字符的起始下标**，另一个指针（下面均简称 $j$）记录第二个字符串（下面均成为字符串 $b$）中**未选出字符的起始下标**，比较 $a_i$ 与 $b_j$，哪个字符的 ASCII 码小，就存放哪个字符。如果有哪个字符串中**连续选出**的字符数量超过了 $k$，则需要“换指针”（在代码的注释中会介绍）。

## 思路为什么是正确的：

题目中有一句话是很重要的，你需要仔细审题：

> 不存在某个字符同时在两个串中都出现了

所以，在没有字符串连续选了 $k$ 个字符时，我们只要选择 $a_i$ 和 $b_j$ 中 ASCII 码小的字符，就可以满足题目中所描述的第 $2$ 点对于字符串比较大小的要求了；

而在有某个字符串已经连续选了 $k$ 个字符时，我们不得不“换指针”，选择另一个字符串中最小的字符，这是被动的。

这样一来，你还有什么理由能说明这个思路不正确吗？

# 代码环节：

```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, m, k, i, j, tota, totb;
string a, b, c;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0); //cin与cout加速
	cin >> t;
	while (t --) {
		cin >> n >> m >> k >> a >> b;
		c.clear (), i = j = 0, tota = totb = 1; //注意，所有t组数据的题都别忘了初始化！！！
		sort (a.begin (), a.end ()), sort (b.begin (), b.end ()); //别忘了排序
		while (i < n && j < m)
			if (tota > k && j < m) //判断a是否到达了k个字符
				tota = 1, totb = 2, c += b[j ++]; //这就是换指针
			else if (totb > k && i < n) //b同理
				tota = 2, totb = 1, c += a[i ++]; //这也是换指针
			else if (a[i] < b[j]) //在没到达k个字符就要贪心
				totb = 1, ++ tota, c += a[i ++];
			else
				tota = 1, ++ totb, c += b[j ++];
		cout << c << '\n'; //输出
	}
	return 0;
}
```

---

## 作者：LeTu_Jun (赞：0)

## 题意

通过给定的 $A$ 和 $B$ 两个字符串以给定的操作构造字符串 $C$，要求 $C$ 的字典序最小。

###### 前置知识
[$\tiny \text{字典序}$](https://baike.baidu.com/item/%E5%AD%97%E5%85%B8%E5%BA%8F/7786229)

## 思路

既然要字典序最小，那么就贪心，不断选 ASCII 码最小的字符不就行了？

怎么选择呢？

因为 **int 类型和 char 类型可以互相兼容**，所以可以以 int 类型存储 $A$ 和 $B$，这样存储就可以直接通过快排找出每个字符串中 ASCII 码小的字符了。

输出的时候再转换为 char 就行。

注意事项：

- 翻译没说多组数据，但事实上还是有的；

- 在选择字符时是**任选**字符。

- 建议使用 C 风格读入，可以很轻松的转换类型。

- 注意不能连续进行 $k$ 次同样的操作。

---

## 作者：legend_cn (赞：0)

# **解题思路**
## 思路
这道题不牵扯高级算法，就是一个贪心。

将 a，b 两个字符串按字符 ASCII 码值排序。

 + 若在一个字符串中已经连续选了 s 个字符，就选另一个字符串中 ASCII 码值最小的字符。
 
 + 否则选取两个字符串中最小的字符。当有一个字符串为空时，答案就是另一个非空字符串的 ASCII 码值最小的字符。

## 贪心证明

首先，题目保证两个字符串中不含有相同字符。

 + 当没有到达 s 个字符的限制时，如果在某一步我们没有选择了 ASCII 码值更小的个字符，所得到的字符串一定比我们这个方法的字符串字典序要大。
 
 + 当到达 s 个字符的限制时，我们就从被限定了的那个字符串中选择。我们如果么选当前字符串中最小字符，所得到的字符串一定比我们这个方法的字符串字典序要大。

所以如果某一步没有按照这里的贪心策略执行，就不能得到最优解。

# **AC 代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1005],b[1005],ch[2050];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(ch,0,sizeof ch);
		int n,m,k;
		cin>>n>>m>>k;
		int zb=0,zb1=0,zb2=0,tt1=1,tt2=1;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=m;i++)
			cin>>b[i];
		sort(a+1,a+1+n);
		sort(b+1,b+1+m);
		while(tt1<=n&&tt2<=m)
		{
			if(zb1==k)
			{
				ch[++zb]=b[tt2++];
				zb1=0;
				zb2=1;
			}
			else if(zb2==k)
			{
				ch[++zb]=a[tt1++];
				zb1=1;
				zb2=0;
			}
			else if(a[tt1]<b[tt2])
			{
				ch[++zb]=a[tt1++];
				zb1++;
				zb2=0;
			}
			else
			{
				ch[++zb]=b[tt2++];
				zb2++;
				zb1=0;
			}
		}
		for(int i=1;i<=zb;i++)
			cout<<ch[i];
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：linyihdfj (赞：0)

## A.Lex String ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16366229.html)
#### 题目描述 ####
[原题面](https://codeforces.com/problemset/problem/1689/A)

给定两个字符串 $a,b$，要求通过以下的两种操作构造一个新的字符串 $c$，使得 $c$ 的字典序最小，并且要求不能连续使用某一种操作超过 $k$ 次。

$1.$从 $a$ 中**任选**一个字符插入到 $c$ 的末尾。

$2.$从 $b$ 中**任选**一个字符插入到 $c$ 的末尾。

若某一个字符串为空则认为构造结束。
若字符串 $x$ 比字符串 $y$ 字典序小则必定满足**以下两种情况**之一：

$1.$ $x$ 为 $y$ 的前缀，且 $x \not= y$。

$2.$从左到右的顺序，$x$ 与 $y$ 第一个不同的位置上 $x$ 的字符的字典序比 $y$ 的字符的字典序小。

#### 题目分析 ####
我们首先可以发现一点：所谓的插入末尾与插入开头并没有任何的区别。

所以为了字典序小我们肯定每一次选择 $a,b$ 中字典序最小的字符，如果超过了 $k$ 次就选另一个字符串的，下一次再选它就好了。

需要注意这里的字典序小不包含：仅仅是字符串长度更小，所以不用考虑这样的构造出的字符串长度上的问题。

#### 代码详解 ####
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
char a[MAXN],b[MAXN];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m,k;
		cin>>n>>m>>k;
		for(int i=1; i<=n; i++){
			cin>>a[i];
		}
		for(int i=1; i<=m; i++){
			cin>>b[i];
		}
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		int l = 1,r = 1,tmp = 0;
		bool flag = false;
		while(l <= n && r <= m){
			if(a[l] < b[r]){
				if(flag){
					cout<<a[l++];
					flag = false;
					tmp = 1;
				}
				else{
					if(tmp < k){
						cout<<a[l++];
						tmp++;
					}
					else{
						cout<<b[r++];
						tmp = 1;
						flag = true;
					}
				}
			}
			else if(a[l] >= b[r]){
				if(!flag){
					cout<<b[r++];
					flag = true;
					tmp = 1;
				}
				else{
					if(tmp < k){
						cout<<b[r++];
						tmp++;
					}
					else{
						cout<<a[l++];
						tmp=1;
						flag = false;
					}
				}
			}
		}
		cout<<endl;
	}
	return 0;
}

```

其实代码有一点复杂，但是其实思路很简单。

---

