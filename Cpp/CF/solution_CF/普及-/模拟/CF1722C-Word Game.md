# Word Game

## 题目描述

Three guys play a game: first, each person writes down $ n $ distinct words of length $ 3 $ . Then, they total up the number of points as follows:

- if a word was written by one person — that person gets 3 points,
- if a word was written by two people — each of the two gets 1 point,
- if a word was written by all — nobody gets any points.

 In the end, how many points does each player have?

## 说明/提示

In the first test case:

- The word $ \texttt{abc} $ was written by the first and third guys — they each get $ 1 $ point.
- The word $ \texttt{def} $ was written by the second guy only — he gets $ 3 $ points.

## 样例 #1

### 输入

```
3
1
abc
def
abc
3
orz for qaq
qaq orz for
cod for ces
5
iat roc hem ica lly
bac ter iol ogi sts
bac roc lly iol iat```

### 输出

```
1 3 1 
2 2 6 
9 11 5```

# 题解

## 作者：achjuncool (赞：5)

[题面](https://www.luogu.com.cn/problem/CF1722C)

[博客](https://www.luogu.com.cn/blog/achjuncool/solution-cf1722c)

# 题目大意

有三个人，每个人都写出了 $n$ 个字符串，如果有一个字符串只有一个人写了，则这个人得 $3$ 分；如果有一个字符串有两个人写了，则两个人都得 $1$ 分；否则没人得分。

# 解法

是一个思路比较简单的模拟，做法应该有很多，~~代码肯定都比我短~~，我来说一下我的做法。

用四个键是字符串，值是布尔的 map 分别表示 A, B, C 有没有写出这个字符串（$a,b,c$）与这个字符串有没有统计过（$usd$）。

接下来进行一个数据的统计。

输入 A 的 $n$ 个字符串的时候，对于每一个字符串 $s$，都进行赋值 `a[s] = true;`，B 与 C 也同理。接着将三个人写的字符串遍历一遍，对于每个字符串 $s$，如果 $usd$ 中没有键为 $s$ 的值，则按照规则给三人加分，否则直接跳过。

# Code

~~我要成为本题第一长解！！！11~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define qwq cin.tie(0);cout.tie(0);ios::sync_with_stdio(false)
int T, n, ansa, ansb, ansc;
//ansa, ansb, ansc 分别表示三人的分数 
string A[1005], B[1005], C[1005];
//三人写的字符串  
map<string, bool> a, b, c, usd;
map<string, bool>::iterator it;
int main(){
	qwq;
	cin >> T;
	//多组数据 
	for(int i = 1; i <= T; i++){
		a.clear();
		b.clear();
		c.clear();
		usd.clear();
		ansa = 0, ansb = 0, ansc = 0;
		//我才不会说我忘记初始化调了好久呢 
		cin >> n;
		for(int j = 1; j <= n; j++){
			cin >> A[j];
			a[A[j]] = true;
		}
		for(int j = 1; j <= n; j++){
			cin >> B[j];
			b[B[j]] = true;
		}
		for(int j = 1; j <= n; j++){
			cin >> C[j];
			c[C[j]] = true;
		}
		//输入并记录 
		for(int j = 1; j <= n; j++){
			it = usd.find(A[j]);
			//如果没有统计过 A[j] 
			if(it == usd.end()){
				int tot = 0;
				usd[A[j]] = true;
				if(a[A[j]]) tot++;
				if(b[A[j]]) tot++;
				if(c[A[j]]) tot++;
				//计算写了这个字符串的总人数 
				if(tot == 1){
					if(a[A[j]]) ansa += 3;
					if(b[A[j]]) ansb += 3;
					if(c[A[j]]) ansc += 3;
				} else if(tot == 2){
					if(a[A[j]]) ansa += 1;
					if(b[A[j]]) ansb += 1;
					if(c[A[j]]) ansc += 1;
				}
				//按照规则加分 
			}
		}
		//下面两个同上 
		for(int j = 1; j <= n; j++){
			it = usd.find(B[j]);
			if(it == usd.end()){
				int tot = 0;
				usd[B[j]] = true;
				if(a[B[j]]) tot++;
				if(b[B[j]]) tot++;
				if(c[B[j]]) tot++;
				if(tot == 1){
					if(a[B[j]]) ansa += 3;
					if(b[B[j]]) ansb += 3;
					if(c[B[j]]) ansc += 3;
				} else if(tot == 2){
					if(a[B[j]]) ansa += 1;
					if(b[B[j]]) ansb += 1;
					if(c[B[j]]) ansc += 1;
				}
			}
		}
		for(int j = 1; j <= n; j++){
			it = usd.find(C[j]);
			if(it == usd.end()){
				int tot = 0;
				usd[C[j]] = true;
				if(a[C[j]]) tot++;
				if(b[C[j]]) tot++;
				if(c[C[j]]) tot++;
				if(tot == 1){
					if(a[C[j]]) ansa += 3;
					if(b[C[j]]) ansb += 3;
					if(c[C[j]]) ansc += 3;
				} else if(tot == 2){
					if(a[C[j]]) ansa += 1;
					if(b[C[j]]) ansb += 1;
					if(c[C[j]]) ansc += 1;
				}
			}
		}
		cout << ansa << " " << ansb << " " << ansc << endl;
	}
	return 0;
}
```


---

## 作者：lihanwen12 (赞：4)

题目大意：  
三个人一起玩一个游戏，首先每个人都会写出 $n$ 个互不相同的长度为 $3$ 的单词。得分规则为如果一个单词只被一个人写出来那么写出来这个单词的这个人得三分，如果一个单词只有两个人写出来那么写出来这个单词得两个人同时得一分，如果一个单词三个人都写出来了那么三个人都不得分，统计最终三个人得到了多少分。保证每个单词都由小写字母构成。  

解题思路：  
由于单词的长度为 $3$ 且只出现小写字母，我们可以将其看作一个 $3$ 位的 $26$ 进制数，字母 ```a``` 看作数字 $0$，字母 ```b``` 看作数字 $1$，依此类推。所有可能出现的单词总数为 $26^{3}=17576$，记录每个单词是否被每个人写出过，最后按照得分规则统计每个人的分数。  

代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}
void write(long long n,bool p){
	if(n<0){putchar('-');n=-n;}
	if(n==0){if(p)putchar('0');return;}
	write(n/10,0);putchar(n%10+'0');
}
long long t,n,ans1,ans2,ans3;
bool p1[20000],p2[20000],p3[20000];
string st;
int main(){
	cin>>t;
	while(t--){
		ans1=0;
		ans2=0;
		ans3=0;
		memset(p1,0,sizeof(p1));
		memset(p2,0,sizeof(p2));
		memset(p3,0,sizeof(p3));
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>st;
			p1[(st[0]-'a')*26*26+(st[1]-'a')*26+st[2]-'a']=true; 
		}
		for(int i=1;i<=n;i++){
			cin>>st;
			p2[(st[0]-'a')*26*26+(st[1]-'a')*26+st[2]-'a']=true; 
		}
		for(int i=1;i<=n;i++){
			cin>>st;
			p3[(st[0]-'a')*26*26+(st[1]-'a')*26+st[2]-'a']=true; 
		}
		for(int i=0;i<=17576;i++){
			if(p1[i] && p2[i] && p3[i])continue;
			if(p1[i] && p2[i]){
				ans1++;
				ans2++;
				continue;
			}
			if(p1[i] && p3[i]){
				ans1++;
				ans3++;
				continue;
			}
			if(p2[i] && p3[i]){
				ans2++;
				ans3++;
				continue;
			}
			if(p1[i])ans1+=3;
			if(p2[i])ans2+=3;
			if(p3[i])ans3+=3;
		}
		cout<<ans1<<" "<<ans2<<" "<<ans3<<endl;
	}
	return 0;
}

```

---

## 作者：Moyou (赞：3)

# 题意

给定三行输入，代表三个人的单词，每行 $n$ 个字符串，对于每个人，如果他写下的字符串。

- 只有他写下 — 得到三分；
- 被两人写下 — 得到一分；
- 被所有人写下 — 不得分。

统计每个人的得分。

# 思路

直接模拟，统计每种字符串出现次数，最后再遍历一遍每个人写下的字符串，对其加分即可。

这里统计字符串出现次数我们采用 unordered_map 存储，其内部实现是哈希表。

# 代码

```cpp
#include <iostream>
#include <unordered_map>
#include <cstring>
using namespace std;
unordered_map<string, int> h;
int cnt[5];
int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        h.clear();
        int n;
        cin >> n;
        memset(cnt, 0, sizeof cnt);
        string a[5][1010];
        for(int i = 1; i <= 3; i ++)
        {
            for(int j = 1; j<=n;j++)
            {
                cin >> a[i][j];
                h[a[i][j]]++; // 统计字符串出现个数
            }
        }
        for(int i = 1; i <= 3; i ++)
        {
            for(int j = 1; j <= n; j ++)
            {
                if(h[a[i][j]] >= 3) continue; // 根据规则加分
                if(h[a[i][j]] == 2) cnt[i] ++;
                else if(h[a[i][j]] == 1) cnt[i] += 3;
            }
        }
        
        cout << cnt[1] << ' ' << cnt[2] << ' ' << cnt[3] << endl; // 输出得分
    }
    return 0;
}
```

---

## 作者：Lantrol (赞：1)

### 题目描述

输入三行，每行 $n$ 个不相等的字符串。对于第 $i$ 行的第 $j$ 个字符串，
- 若其在三行中出现的次数为 $1$，则第 $i$ 行的分数增加 $3$；

- 若其在三行中出现的次数为 $2$，则第 $i$ 行的分数增加 $1$；

- 若其在三行中出现的次数为 $3$，则第 $i$ 行的分数增加 $0$。

### 思路

显然使用 `map<string,int>` 统计字符串出现的次数。然后分别扫三行字符串，统计每行的总分。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
map<string,int> mp;
void solve(){
	mp.clear();
	int n;
	string s[4][1005];
	int ans[4]={0,0,0,0};
	cin>>n;
	for(int j=1;j<=3;j++)
	for(int i=1;i<=n;i++){
		cin>>s[j][i];
		mp[s[j][i]]++;
	}
	for(int j=1;j<=3;j++){
		for(int i=1;i<=n;i++){
			if(mp[s[j][i]]==1){
				ans[j]+=3;
			}
			if(mp[s[j][i]]==2){
				ans[j]+=1;
			}
		}
	}
	cout<<ans[1]<<" "<<ans[2]<<" "<<ans[3]<<endl;
}

int main(){
	int t;
	cin>>t;
	while(t--){
	    solve();
	}
}

```


---

## 作者：Kedit2007 (赞：0)

## 题目大意

给定三组字符串，每组字符串的个数相同，每个字符串都由三个小写英文字母组成，保证每组字符串中两两不同。

一组中一个字符串的分数定义如下：

- 若**只有**该组中有这个字符串，得 $3$ 分。
- 若**有且仅有两组**中有这个字符串，得 $1$ 分。
- 若**三组都有**这个字符串，得 $0$ 分。

你需要分别输出三组字符串的分数之和。

## 思路

按照题意，先把每个字符串出现的次数记录下来。

记录完成后，遍历每组字符串，直接加分记录即可。

判断元素个数可以使用 [std::map](https://oi-wiki.org//lang/csl/associative-container/) （链接至 OI Wiki）。

## 参考代码

```cpp
vector<int> WordGame(vector<string> a, vector<string> b, vector<string> c)
{
	map<string, int> cnt;
	vector<int> ret(3, 0);
	for (auto& s : a)
		cnt[s]++;
	for (auto& s : b)
		cnt[s]++;
	for (auto& s : c)
		cnt[s]++;
	for (auto s : a)
	{
		if (cnt[s] == 1) ret[0] += 3;
		if (cnt[s] == 2) ret[0] += 1;
	}
	for (auto s : b)
	{
		if (cnt[s] == 1) ret[1] += 3;
		if (cnt[s] == 2) ret[1] += 1;
	}
	for (auto s : c)
	{
		if (cnt[s] == 1) ret[2] += 3;
		if (cnt[s] == 2) ret[2] += 1;
	}
	return ret;
}
```

---

