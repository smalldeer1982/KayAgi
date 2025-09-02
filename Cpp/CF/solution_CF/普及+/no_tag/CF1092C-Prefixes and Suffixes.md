# Prefixes and Suffixes

## 题目描述

Ivan挑了几个长度为$n$的小写英文字符串。

但是你不知道Ivan挑的是什么字符串。Ivan会给你这些字符串的前缀和后缀，但是你不知道哪个是前缀，哪个是后缀。

你的任务是猜出他给你的$2n-2$个字符串中哪个是前缀，哪个是后缀。猜出他挑的任意一个字符串，并且回答与之一致即可通过。

PS：在Ivan给你的某个字符串中，如果前面有一个与之相同并且你判了它为$P$，那么你只能判它为$S$。

## 样例 #1

### 输入

```
5
ba
a
abab
a
aba
baba
ab
aba
```

### 输出

```
SPPSPSPS
```

## 样例 #2

### 输入

```
3
a
aa
aa
a
```

### 输出

```
PPSS
```

## 样例 #3

### 输入

```
2
a
c
```

### 输出

```
PS
```

# 题解

## 作者：灵光一闪 (赞：10)

感觉这题好难啊难啊难啊……（此处省略2e9个``难啊``）

~~请无视上面内容~~ 灌水完毕！开始讲题！


------------

首先，我们要知道：这个单词绝对是由最长的单词拼出来的！so，我们把所有的最长的单词（叫字串更好点吧）处理到一个vector里面，然后看代码（灰肠简单的）

code：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<string>
#include<vector>
#include<map>
using namespace std;
map <string,bool> mp;
vector <string> v;
string s[233];
int maxint;
int n;
bool front(string s,string t){ //是不是前缀
    if(s.find(t)==0){
        return true;
    }
    else{
        return false;
    }
}
bool behind(string s,string t){  //是不是后缀
    for(int i=s.size()-1,j=t.size()-1;j>=0;j--,i--){
        if(s[i]!=t[j]){
            return false;
        }
    }
    return true;
}
bool checker(string str){//重要的核心
    for(int i=0;i<v.size();i++){
        bool flag=true;
        for(int j=0;j<n*2-2;j++){
            if(front(str,s[j])){
                continue;
            }
            else if(!behind(v[i],s[j])){//两个都不满足就说明这个是错的
                flag=false;//flag赋为false
                break;//终止
            }
        }
        if(flag){//对的
            return true;
        }
    }
    return false;
}
void work(string ans){//输出的一个玩意，很好理解
    for(int i=0;i<n*2-2;i++){
        if(front(ans,s[i])&&!mp[s[i]]){
            putchar('P');
        }
        else{
            putchar('S');
        }
        mp[s[i]]=true;
    }
    puts("");
    exit(0);
}
int main(){
    cin>>n;
    for(int i=0;i<n*2-2;i++){
        cin>>s[i];
        mp[s[i]]=false;
        if(s[i].size()>maxint){
            maxint=s[i].size();//记录下最长的长度
        }
    }
    for(int i=0;i<n*2-2;i++){
        if(maxint==s[i].size()){//找到一个压进去一个
            v.push_back(s[i]);
        }
    }
    for(int i=0;i<v.size();i++){
        if(checker(v[i])){//这个合法！、
            work(v[i]);//处理输出
        }
    }
}
```
~~调了我连续将近10个小时，不点个赞对得起我吗qaq~~

The End.

---

## 作者：zhoukaixiang (赞：3)

## 题目分析
这道题有这样一种思路。题意要求我们输出一个字符串为前缀还是后缀。题目猜测的字符串长度为 $n$ ，并且数据保证一定有两个长度为 $n-1$ 的字符串，那么这两个长度为 $n-1$ 的字符串肯定有一个是前缀，有一个是后缀。那么就有两种情况：

 - 若该长度为 $n-1$ 的字符串为前缀，那么它的所有从开始字符到某一位置的子串肯定是前缀；

 - 若该长度为 $n-1$的字符串为后缀，那么它的所有从某一字符到结束位置的子串肯定是后缀； 

所以我们可以先找到两个长度为 $n-1$ 的字符，若第一个字符串 $S1$ 从第二个位置到末尾子串与第二个字符串 $S2$ 从第一个位置到倒数第二个位置子串相等，则第一个字符串 $S1$ 为最长前缀子串 $P$，否则第二个字符串 $S2$ 为最长前缀子串 $P$ 。 最后再遍历所有字符串，若为最长前缀子串 $P$ 的子串，且之前未出现，则该字符串为前缀，输出 $P$ ，否则输出 $S$ 。

## 代码
```
 #include<bits/stdc++.h>
 using namespace std;
 bool vis[500];
 int n,num;
 string maxstring="",maxstring2="",p,a[500];
 int main()
 {
 	cin>>n;
    memset(vis, false, sizeof(vis));
    for(int i=1;i<=2*n-2;i++){
        cin>>a[i];
        if(a[i].size()==n-1){//保存最长前缀子串或后缀子串 
            if(maxstring=="") maxstring=a[i];
            else maxstring2=a[i];
        }
    }
    for(int i=1;i<=2*n-2;i++)
    {
    	if(maxstring.substr(0,a[i].size())==a[i]) 
        	num++;//在最长前缀子串的子串个数 
    }
    if(num>=(2*n-2)/2 && maxstring.substr(1,n-2)==maxstring2.substr(0,n-2)) 
    	p=maxstring;//p保存的是正确的最长前缀子串 
    else 
    	p=maxstring2;//否则mx2才是最长前缀子串 
    for(int i=1;i<=n*2-2;i++)
    {
    	if(a[i]==p.substr(0,a[i].size()) && vis[a[i].size()]!=true) 
        {
        	vis[a[i].size()]=true,;
            printf("P");//判断是否处于最长前缀子串中，且只能出现一次，即为前缀 
        }
        else 
        	printf("S");//否则为后缀 
    }
 }
```

---

## 作者：lyzqs (赞：1)

同步发布于[博客](https://blog.lyzqs.top/archives/250/)

很麻烦的一题

我的做法是先确定最长的两个串是前缀还是后缀

然后每个串用最长的串判断属于前缀还是后缀

如果都可以的话就均分

注意细节，特别是均分有一些细节

具体可以看看代码就懂了

比赛时我没有判断好最长的两个串是前缀还是后缀结果赛后被hack了

复杂度是$O(n^2)$

代码

```cpp
#include <bits/stdc++.h>
#define il inline
#define Max 2005
#define int long long
using namespace std;
il int read()
{
	char c=getchar();
	int x=0,f=1;
	while(c>'9'||c<'0')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
char pr[Max],sf[Max],s[Max][Max],h[Max],t[Max],l,r;
int n,len[Max],bl[Max],cnt1,cnt2,cnth[Max],cntt[Max],st[Max],tp,cnt,s1[Max],s2[Max],maxlen,a,b;
il bool check(int x,int t,int opt)
{
	if(opt==2)
	{
		for(int i=1;i<=len[x];i++)
			if(s[x][i]!=s[t][i]) return 0;
		return 1;
	}
	else if(opt==1)
	{
		for(int i=1;i<=len[x];i++)
			if(s[x][len[x]-i+1]!=s[t][len[t]-i+1]) return 0;
		return 1;
	}
	return 1;
}
signed main()
{
	cin>>n;n=2*n-2;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		len[i]=strlen(s[i]+1);
		maxlen=max(maxlen,len[i]);
	}
	for(int i=1;i<=n;i++)
		if(len[i]==maxlen)
		{
			if(!b) b=i;
			else a=i;
		}
	for(int i=1;i<=n;i++)
	{
		if((!check(i,a,2))&&(!check(i,b,1))) swap(a,b),cnt++;
	}
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(bl[i]) continue;
		if(check(i,b,1)&&!check(i,a,2)) bl[i]=2,cnt2++;
		else if(check(i,a,2)&&!check(i,b,1)) bl[i]=1,cnt1++;
		else if(check(i,b,1)&&check(i,a,2)) st[++tp]=i;
	}
	for(int i=1;i<=tp;i++)
	{
		if(cnt1<=cnt2) bl[st[i]]=1,cnt1++;
		else bl[st[i]]=2,cnt2++;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i!=j&&len[i]==len[j]&&check(i,j,2))
			{
				if(bl[i]==bl[j])
					bl[i]=3-bl[i];
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(bl[i]==1) putchar('P');
		else putchar('S');
	puts("");
}
```

---

## 作者：Zechariah (赞：1)

由题意，给出的字符串一定可以分成两组，一半是前缀一半是后缀，所以按长度排序，相邻两个长度相同的字符串一个是前缀一个是后缀，直接搜索所有情况就行了，由于满足题意的答案会很多，所以虽然复杂度显然不正确，还是可以过掉
```cpp
#include <bits/stdc++.h>
#define rg register
#define inl inline
typedef long long ll;
const int N = 3e4 + 10, mod = 998244353;
using namespace std;
namespace fast_IO {
    long long read()
    {
        rg long long num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) >= '0'&&ch <= '9')
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
string ans, ans2;
struct Node {
    string s;
    int id;
}s[N];
int n;
inl bool cmp(rg Node &s, rg Node &t) { return s.s.size() < t.s.size(); }
bool flag[N];
inl bool fin(rg string &a, rg string &b)
{
    if (a.size() < b.size())return false;
    for (rg int i = 0; i != b.size(); ++i)if (a[i] != b[i])return false;
    return true;
}
inl bool fin2(rg string &a, rg string &b)
{
    if (a.size() < b.size())return false;
    for (rg int i = 0; i != b.size(); ++i)if (a[a.size() - i - 1] != b[b.size() - i - 1])return false;
    return true;
}
inl void dfs(rg int i)
{
    if (i > n * 2 - 2)
    {
        for (rg int i = 1; i <= n * 2 - 2; ++i)putchar(flag[i] ? 'P' : 'S');
        exit(0);
    }
    rg string tmp = "", tmp2 = "";
    if (fin(s[i].s, ans) && fin2(s[i + 1].s, ans2))
    {
        tmp = ans, tmp2 = ans2;
        ans = s[i].s, flag[s[i].id] = true;
        ans2 = s[i + 1].s;
        dfs(i + 2);
        flag[s[i].id] = false;
        ans = tmp, ans2 = tmp2;
    }
    if (fin(s[i + 1].s, ans) && fin2(s[i].s, ans2))
    {
        tmp = ans, tmp2 = ans2;
        ans = s[i + 1].s, flag[s[i + 1].id] = true;
        ans2 = s[i].s;
        dfs(i + 2);
        flag[s[i + 1].id] = false;
        ans = tmp, ans2 = tmp2;
    }
}

int main()
{
    n = fast_IO::read();
    for (rg int i = 1; i <= n * 2 - 2; ++i)cin >> s[i].s, s[i].id = i;
    sort(s + 1, s + n * 2 - 1, cmp);
    dfs(1);
    return 0;
}

```

---

## 作者：jr_inf (赞：0)

对于一个字符串 $S$，我们可以 $O(n^2)$ 判断它是否是原串，考虑如何枚举 $S$。设两个长度为 $n-1$ 的串为 $a$,$b$，那么 $S$ 只会是 $a+b_{n-2}$ 或 $b+a_{n-2}$，只需枚举这两种方案即可，时间复杂度 $O(n^2)$。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100+10;
int n;
char ans[N*2];
struct node{int id;string s;}a[N*2];
bool cmp(node x,node y)
{
	if(x.s.size()!=y.s.size())return x.s.size()>y.s.size();
	return x.id<y.id;
}
void run(string s)
{
	for(int i=1;i<=n*2-2;i++)
	{
		if(a[i].s==s.substr(0,a[i].s.size()))ans[a[i].id]='P';
		else if(a[i].s==s.substr(n-a[i].s.size(),a[i].s.size()))ans[a[i].id]='S';
		else return;//不合法
		if(i>1&&a[i].s==a[i-1].s)ans[a[i].id]='S';//按题意去重
	}
	for(int i=1;i<=n*2-2;i++)cout<<ans[i];
	exit(0);
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n*2-2;i++)
	{
		a[i].id=i;
		cin>>a[i].s;
	}
	sort(a+1,a+1+n*2-2,cmp);//找最长串
	string s1=a[1].s,s2=a[2].s;
	run(s1+s2[n-2]);
	run(s2+s1[n-2]);
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1092C)

一道字符串题。

我们考虑还原字符串后再一个一个的判断。很显然，这个字符串是由一个长度为 $n-1$ 的前缀和后缀组成的。因此我们可以找到这 $2$ 个长度为 $n$ 的字符串，然后枚举哪个是前缀，哪个是后缀。

值得注意的是，当你判断一个字符串为**前缀**时，如果后面出现了同样的字符串，你只能判断它为**后缀**。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n;
bool flag;
string s1, s2, t, ans1, ans2; // t 是还原串
string s[205];
map <string, bool> mp;
bool check1(string str) { // 判断这个字符串是否是还原串的前缀
    for (int i = 0; i < str.size(); i++) {
        if (t[i] != str[i]) return 0;
    }
    return 1;
}
bool check2(string str) { // 判断这个字符串是否是还原串的后缀
    int cnt = t.size() - 1;
    for (int i = str.size() - 1; i >= 0; i--) {
        if (t[cnt--] != str[i]) return 0;
    }
    return 1;
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= 2 * n - 2; i++) cin >> s[i];
    for (int i = 1; i <= 2 * n - 2; i++) {
        if (s[i].size() == n - 1 and flag) s2 = s[i];
        if (s[i].size() == n - 1 and !flag) {
            s1 = s[i];
            flag = 1;
        }
    } 
    flag = 0;
    t = s1;
    t += s2[s2.size() - 1];
    // 如果 s1 是前缀
    for (int i = 1; i <= 2 * n - 2; i++) {
        if (!check1(s[i]) and !check2(s[i])) flag = 1; // 当 s1 是前缀时不合法
        else {
            if (check1(s[i]) and mp.find(s[i]) == mp.end()) {
                ans1 += 'P';
                mp[s[i]] = 1;
            }
            else ans1 += 'S';
        }
    }
    t = s2;
    t += s1[s1.size() - 1];
    // 如果 s1 是后缀
    mp.clear();
    for (int i = 1; i <= 2 * n - 2; i++) {
        if (check1(s[i]) and mp.find(s[i]) == mp.end()) {
            ans2 += 'P';
            mp[s[i]] = 1;
        }
        else ans2 += 'S';
    }
    if (!flag) cout << ans1; 
    else cout << ans2;
    return 0;
}
```


---

## 作者：Ouaoan (赞：0)


题目：[Prefixes and Suffixes](https://codeforces.com/contest/1092/problem/C)

---

思路：

可以知道原序列一定是由给出的最长的两个字符串拼接而成的，所以可以尝试把最长的两个字符串按两种相对位置拼接。

设一个数组b。

对于每种拼接方法——

如果一个串可以放在前缀的位置而不能放在后缀的位置，就把b[i]设为1。

如果一个串可以放在后缀的位置而不能放在前缀的位置，就把b[i]设为2。

如果一个串可以放在前缀的位置也可以放在后缀的位置，就把b[i]设为0。

如果都不能放，就说明这种情况不可行。

然后对于两个b为0的相同子串，用一个map存储，分别放在前缀和后缀就好了。

---

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define read(x) scanf("%d",&x)
#define maxn 10000

int n;
string s[maxn*2+5];

string s1,s2,s3,s4;
string a;
int b[maxn+5];

map<string,int> mp;

int main() {
	read(n);
	for(int i=1; i<=n*2-2; i++) {
		cin>>s[i];
		if(s[i].size()==n-1) {
			if(s1.size()==0) s1=s[i];
			else s2=s[i];
		}
		if(s[i].size()==1) {
			if(s3.size()==0) s3=s[i];
			else s4=s[i];
		}
	}

	if(s1+s2[s2.size()-1]==s1[0]+s2&&((s3[0]==s1[0]&&s4[0]==s2[s2.size()-1])||(s4[0]==s1[0]&&s3[0]==s2[s2.size()-1]))) {
		a=s1+s2[s2.size()-1];
	} else a=s2+s1[s1.size()-1];
	int ans1=0,ans2=0;
	
	FRT:;
	
	for(int i=1;i<=n*2-2;i++) {
		int f1=1,f2=1;
		for(int j=0;j<s[i].size();j++) {
			if(s[i][j]!=a[j]) {
				f1=false;
				break;
			}
		}
		for(int j=0;j<s[i].size();j++) {
			if(s[i][j]!=a[n-s[i].size()+j]) {
				f2=false;
				break;
			}
		}
		if(f1&&!f2) b[i]=1,ans1++;
		else if(f2&&!f1) b[i]=2,ans2++;
		else if(0==f1&&0==f2) {
			for(int x=1;x<a.size();x++)swap(a[x-1],a[x]);
			ans1=0,ans2=0;
			memset(b,0,sizeof(b));
			goto FRT;
		}
	}
	
	for(int i=1;i<=n*2-2;i++) {
		if(b[i]==1) {
			printf("P");
		} else if(b[i]==2) {
			printf("S");
		} else if(mp.count(s[i])) {
			int y=3-mp[s[i]];
			if(y==1) {
				printf("P");
				ans1++;
			} else {
				printf("S");
				ans2++;
			}
		} else {
			if(ans1<n-1) {
				printf("P");
				ans1++;
				mp[s[i]]=1;
			} else {
				printf("S");
				ans2++;
				mp[s[i]]=2;
			}
		}
	}

	return 0;
}
```

---

