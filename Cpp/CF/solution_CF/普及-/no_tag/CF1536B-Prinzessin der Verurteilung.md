# Prinzessin der Verurteilung

## 题目描述

定义一个字符串的 $MEX$ 为**在输入中不作为连续子字符串出现的最短字符串**。

如果有长度相同的 $MEX$，则取字典序最小的。

## 样例 #1

### 输入

```
3
28
qaabzwsxedcrfvtgbyhnujmiklop
13
cleanairactbd
10
aannttoonn```

### 输出

```
ac
f
b```

# 题解

## 作者：Acc_Robin (赞：7)

赛时一看就觉得有点简单，虽然过了，但不会证正确性，来一发题解：

我们发现，一个长度为 $1000$ 串的 Mex 看起来就不会太大，所以我们可以搜索解决。

按照字典序枚举每一个串，使用广搜即可。

这个方法就是空间有点大，不过好像没人 hack 掉。

代码（使用了 C++17）：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N = 1e2+10;
	string a,b;
    int n;
    void work(){
        queue<pair<string,int>>q;
        cin>>n>>a,q.push({b,0});
        while(1){
            auto[u,pos]=q.front();q.pop();
            u.resize(pos+1);
            for(int i=0;i<26;i++){
                u[pos]=(char)('a'+i);
                if(a.find(u)==string::npos)return (void)(cout<<u);
                q.push({u,pos+1});
            }
        }
    }
}
int main(){
	int T;
	for(cin>>T;T--;puts(""))Acc::work();
	return 0;
}
```

---

## 作者：YCS_GG (赞：6)

考虑长度为 $k$ 的子串在长度为 $n$ 的串中最多只有 $n-k+1$ 个

所以按字典序枚举长度小于等于 $3$ 的字符串即可，因为 $26^3 > 1000 > 26^2$

第一个找出来的当然就是 $\textrm{MEX}$ ，复杂度 $O(26^3t)$ 


```cpp
#include <bitset>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
int t;
int pos[27];
int main() {
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        memset(pos, 0, sizeof(pos));
        for (int i = 0; i < n; i++) {
            pos[s[i] - 'a'] = 1;
        }
        bool f = 0;
        for (int i = 0; i < 26; i++) {
            if (pos[i] == 0) {
                cout << (char)(i + 'a') << endl;
                f = 1;
                break;
            }
        }
        for (char i = 'a'; i <= 'z'; i++) {
            if (f == 1) {
                break;
            }
            for (char j = 'a'; j <= 'z'; j++) {
                if (f == 1) {
                    break;
                }
                string tmps = "";
                tmps += i;
                tmps += j;
                if (s.find(tmps) == s.npos) {
                    cout << tmps << endl;
                    f = 1;
                    break;
                }
            }
        }
        for (char i = 'a'; i <= 'z'; i++) {
            if (f == 1) {
                break;
            }
            for (char j = 'a'; j <= 'z'; j++) {
                if (f == 1) {
                    break;
                }
                string tmps = "";
                tmps += i;
                tmps += j;
                for (char k = 'a'; k <= 'z'; k++) {
                    if (f == 1) {
                        break;
                    }
                    string p = tmps;
                    p += k;
                    if (s.find(p) == s.npos) {
                        cout << p << endl;
                        f = 1;
                        break;
                    }
                }
            }
        }
    }
}
```

---

## 作者：HerikoDeltana (赞：6)

这道题的题面......原神玩家直接狂喜。

~~大幻梦森罗万象狂气断罪眼~~

切回正题，先来看题目是让我们求什么。

## 题意简述

实际上这个题在洛谷的翻译非常的简洁明了了，不过我在 CodeForces 做的时候就~~理解不能~~。

题目中定义了 MEX 是“**在输入中不作为连续子字符串出现的最短字符串**”。

然后每组数据给你一个字符串问你这个字符串的 MEX 是什么。

## 思路简述

首先先来理解一下什么是 MEX ，

当时我再看到这道题的时候是一脸懵的，因为这个翻译出来确实很拗口。

于是我就在下面举一个例子，里面展现出来的东西，就是我个人的理解。~~希望不要假了QaQ~~

比如给你一个字符串 abcax ，那么这里面所有**连续子字符串**其实大家都会找：

"a" , "ab" , "abc" , "abca" , "abcax" , "b" , "bc" , "bca" , "bcax" , "c" , "ca" ......

由于全列出来就太多了，于是就列出这一些吧。

那么 MEX 就是不在这里面的定义上最小的字串，也就是字典序最小的。

可能看到这里觉得这道题还有点难度？下面的一步直接让这个题的难度消失。

我们来看数据范围中说道：对于一个数据点中的所有数据 $\sum n \  \le 1000$ ，

再由题目的定义可得 MEX 一定是原字符串的字串，又因为 $26^3 \ge 1000$ 所以 MEX 的长度不会大于 3 。

由此我就想到了一个比较暴力的类似桶的方法，

用一个 bool 数组记录这个字符串有没有出现过，最后按照顺序输出即可。

## Code

这里面有关初始化和最后循环的次序还是应当仔细想一下的

```cpp
#include <bits/stdc++.h>
#define Heriko return
#define Deltana 0
#define Romano 1
#define S signed
#define U unsigned
#define LL long long
#define R register
#define I inline
#define D double
#define LD long double
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false)
using namespace std;
I void fr(LL & x)
{
    LL f = 1;
    char c = getchar();
    x = 0;
    while (c < '0' || c > '9') 
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') 
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x *= f;
}
I void fw(LL x)
{
    if(x<0) putchar('-'),x=-x;
    static LL stak[35];
    LL top=0;
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    putchar('\n');
}
char s[1005];
bool k[30][30][30];
S main()
{
    // freopen("my.in","r",stdin);
    LL t;fr(t);
    while(t--)
    {
        LL n;
        mst(k,0);
        fr(n);gets(s+1);
        for( LL i=1;i<=n;++i)
        {
            k[s[i]-'a'+1][0][0]=1;
            if(i>1) k[s[i]-'a'+1][s[i-1]-'a'+1][0]=k[s[i-1]-'a'+1][0][0]=1;
            if(i>2) k[s[i]-'a'+1][s[i-1]-'a'+1][s[i-2]-'a'+1]=k[s[i-1]-'a'+1][s[i-2]-'a'+1][0]=k[s[i-2]-'a'+1][0][0]=1;      
        }
        bool g=0;
        for( LL p=0;p<=26 and g==0;++p)
            for( LL j=min(p,1ll);j<=26 and g==0;++j)
                for( LL i=1;i<=26 and g==0;++i)
                    if(!k[i][j][p])
                    {
                        if(p) putchar(p+'a'-1);
                        if(j) putchar(j+'a'-1);
                        if(i) putchar(i+'a'-1);
                        putchar('\n');
                        g=1;
                    }
    }
    Heriko Deltana;
}
```

最后，审核大大辛苦啦~

---

## 作者：123hh2 (赞：5)

--->[传送门](https://www.luogu.com.cn/problem/CF1536B)

### 前言

前天打 CF 的时候， A 题愣是耗了我 1 个多小时，结果只过了测试点 1，B 题因为没有 LawrenceSivan 巨佬的翻译，看了会机翻就跑路了 ~~然而还拿了360分就离谱~~


------------

### 题目大意

经同机房的 XYY1411 巨佬的翻译:

给你一个字符串，长度为 $n$ ，要求找到这个字符串中**没有出现过的最小字典序的子串**，每个测试点有多个测试数据


------------

### 思路

**暴力**，虽然是多测，但是 $t≤1000$，$n≤1000$，应该可以跑的过去

我们可以考虑从 a 开始，依次枚举原字符串中的最小字典序的子串，然后使用 STL 中的 find 函数来判别该子串是否在原字符串中出现过


------------
### 代码

```cpp
#include<bits/stdc++.h>
#include<Windows.h>//我才知道CF支持这个头文件qwq 
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-') {f=-1;}ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
inline void write(int x)
{
	if(x<0) {putchar('-');x=-x;}
	if(x>9) {write(x/10);} 
	putchar (x%10+'0');
	return;
}
int main()
{
	int t=read();
	while(t--)
	{
		int n=read();
		string a="";//原子串 
		cin>>a;
		string b="a";//查找子串 
		while(1)
		{
			if(a.find(b)==string::npos)//找一下有没有子串 b 
			{
				cout<<b<<endl;
				break;
			}
			else
			{
				//这一块是用来让子串从最小字典序到最大字典序更新的 
				reverse(b.begin(),b.end());
				b[0]++;
				for(int i=0;i<b.size();i++)
				{
					if(b[i]>'z'&&i!=b.size()-1)
					{
						b[i]='a';
						b[i+1]++;
					}
					if(b[i]>'z'&&i==b.size()-1)
					{
						b[i]='a';
						b+="a";
					}
				}
				reverse(b.begin(),b.end());
			}
		}
	}
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：1)

## 题意

对于一个字符串，定义它的 `MEX` 为不作为连续子字符串出现的最短字符串。

如果有多个 `MEX`，则选择字典序最小。

现在给出一个长度为 $n$ 的字符串，输出它的 `MEX`。

## 思路

题目中对于 `MEX` 并没有解释清楚。我们举个栗子理解一下。

对于字符串 `TANAKIOI`，他的连续子串有 `T`,`TA`,`AN`,`NAKI`……。它的 `MEX` 就是不是它连续字串的长度最短，字典序最小的字符串，也就是 `B`。（似乎比原来更绕？）

那么本题的做法也十分明显了，枚举 
`a`,`b`,...,`z`,`aa`,`ab`,...，只要找到一个不是原字符串的连续子串就输出（第一个找到的肯定是最小的）。

判断它是不是原字符串的连续子串，可以用 `c++` 的自带函数 `find()` 进行判断。对于 `find()` 函数的使用方式，请[右转出门 csdn 一下](https://blog.csdn.net/weixin_34345560/article/details/90093329)。

重点是如何去进行枚举。我们可以先把枚举的字符串的最后一位加一，也就是 `st[st.size()-1]++;`，然后去进行判断。如果最后一位已经超过了 `z`，就把最后一位归 `a`，它的前一位加 $1$，如果前一位也超过了 `z`，就继续把那一位归 `a`，更前一位加 $1$。以此类推，如果一直推到第一位都超过 `z`，就需要把第一位变成 `a`，在字符串的前面加上一个 `a`，也就是 `st='a'+st`。

最后我们来考虑一下这个算法的极限时间复杂度：已知 $n\leq1000$,我们来找一下它最多可以枚举到几位 $26^1=26<1000$，$26^2+26^1=676+26=702<1000$，$6^3+26^2+26^1=17576+676+26=18278>1000$。

那么我们最多只能枚举 $3$ 位。为了方便计算，我们算它可以枚举 $18278$ 次，每次枚举 $3$ 位，就算再乘上 $T$（最大 $1000$），也只有 $54834000$，还不会超时。何况题目保证了所有的 $n$ 加起来不超过 $1000$，同时刚才我们的所有数字都估打了，实际上肯定没有那么多。综上所述，这种算法不会超时。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string st;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		cin>>st;
		string st_fd="a";
		while(1){
			if(st.find(st_fd)==-1){
				cout<<st_fd<<'\n';
				goto loop;
			}
			st_fd[st_fd.size()-1]++;
			for(int i=st_fd.size()-1;i>=0;i--)
				if(st_fd[i]>'z'){
					if(i!=0)
						st_fd[i]='a',st_fd[i-1]++;
					else st_fd[i]='a',st_fd='a'+st_fd;
				}
//			cout<<st_fd<<'\n'; 
		}
		loop:;
	}
	return 0;
}
```

## 补充

在对进行枚举的字符串操作时，其实有一种较为简便的方法，可以使用类似 $27$ 进制的方法，枚举一个十进制数，在需要使用的时候把它转成类似 $27$ 进制。在这种类似 $27$ 进制中：`A` 代表 $1$，`B` 代表 $2$,……，`AA` 代表 $27$，`AB` 代表 $28$。

---

## 作者：pyz51 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1536B)

# 题意简述
给定字符串 $s$，求 $s$ 中不存在的最短子串，并输出字典序最小的。

# 题解
1. 直接暴力枚举每个子串，光长度 $1000$ 的就有 $26^{1000}$ 个，pass。
2. 由于 $s$ 的长度很短（$n \le 1000$），可以考虑只枚举长度短的子串（不可能都包括）。  
   应该有多短呢？  
   - 长度为 $1$：$26$ 个
   - 长度为 $2$：$26^2$ 个（$676$ 个）
   - 长度为 $3$：$26^3$ 个（$17576$ 个）
     
   这时已经超了。

   **所以我们仅需枚举长度为 $1 \sim 3$ 的字串。**  
   接下来就简单多了。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,b) memset(a,b,sizeof a)
int t,n,flag;
char now[3];
string s;
int main(){
    cin>>t;
    while(t--){
    	bool vis=0;
    	cin>>n>>s;
		rep(i,0,25){
			flag=0;
			now[0]='a'+i;
			rep(r,0,s.size()){
				if(now[0]==s[r]){
					flag=1;
					break;
				}
			}
			if(!flag&&!vis) cout<<now[0]<<'\n',vis=1;
		}//长度为1
		rep(i,0,25){
			rep(j,0,25){
				flag=0;
				now[0]='a'+i,now[1]='a'+j;
				rep(r,0,s.size()-1){
					if(now[0]==s[r]&&now[1]==s[r+1]){
						flag=1;
						break;
					}
				}
				if(!flag&&!vis) cout<<now[0]<<now[1]<<'\n',vis=1;
			}
		}//长度为2
		rep(i,0,25){
			rep(j,0,25){
				rep(k,0,25){
					flag=0;
					now[0]='a'+i,now[1]='a'+j,now[2]='a'+k;
					rep(r,0,s.size()-2){
						if(now[0]==s[r]&&now[1]==s[r+1]&&now[2]==s[r+2]){
							flag=1;
							break;
						}
					}
					if(!flag&&!vis) cout<<now[0]<<now[1]<<now[2]<<'\n',vis=1;
				}
			}
		}//长度为3
	}
    return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1536B)

---

# 题目大意：

给你一串字符串，然后按字典序求第一个没在这个字符串中出现的子串，如样例 ```qaabzwsxedcrfvtgbyhnujmiklop```，$a$ 至 $z$ 都出现了，```aa``` 出现了，```ab``` 出现了，```ac``` 没出现，答案就是 ```ac```。

# 思路：

先用 set 保存出现过后的子串，然后进行判断。因为 $n \lt 1000 \lt 27+27^2+27^3$，所以子串最长长度为 $3$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
set<string>s;
int t,n;
string b;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>b;
	    s.clear();
		for(int j=1;j<=3;j++){
			for(int i=0;i<n;i++){
				string a;
				int minn=min(n, i + j);;
				for(int k=i;k<minn;k++){
					a+=b[k];
				}
				s.insert(a);
			}
		}
		string ans="a";
		while(1){
			if(!s.count(ans)){
				cout<<ans<<endl;
				break;
			}
			int len=ans.size();
			if (ans[len-1]=='z'){
				while(len>=1&&ans[len-1]=='z'){
					ans[len-1]='a';
					len--;
				}
				if(len==0){
					ans='a'+ans;
					continue;
				}
				if(ans[len-1]!='z'){
					ans[len-1]++;
				 }
			}else{
				ans[ans.size()-1]++;
			}
		}
	}
    return 0;
}
```

完结撒花~

---

## 作者：Wei_Han (赞：0)

## 题目大意
找到字符串字典序最小的 $\operatorname{mex}$，字符串的 $\operatorname{mex}$ 定义为非字符串连续子串的最短串。
## Solution
看到数据范围 $n\leq10^3$ 可以发现，就算是最极限情况，字符串的 $\operatorname{mex}$ 也不会超过四位，因为所有子串的情况为 $26^4$ ，而这个数字是肯定大于 $1000$ 的，所以我们直接枚举答案，查找在不在串中即可。

极限时间复杂度 $O(n^2)$ 左右。
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
typedef long long ll;
typedef double db;
const int N=1e6+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,a[N];
string s,tt;
inline bool check(ll x,ll n,string a){
    if(x>n){
        if(s.find(a)==string::npos){tt=a;return 1;}
        return 0;
    }
    ll maxx=0;
    fo(1,i,26){if(maxx) return 1;maxx=max(maxx,0ll+check(x+1,n,a+char(i+'a'-1)));}
    return maxx; 
}
int main(){
	read(t);
    while(t--){
        read(n);
        cin>>s;
        fo(1,i,4){if(check(1,i,"")){cout<<tt;break;}}
        pr;
    }
	return 0;
}
``````

---

## 作者：xiaoli12345678 (赞：0)

# 题目分析

数据范围中说道：

>对于一个数据点中的所有数据 $\sum n\le1000$

而 $26^3>1000>26^2$ ，于是直接枚举 $3$ 个字母，再用 ```find()``` 来查找是否在原字符串，是输出，不是接着枚举。

# 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int v[30];
int main() {
	int T;
	cin>>T;
	while(T--) {
		int len;
		string s;
		cin>>len>>s;
		for(int i=0; i<26; i++) {
			v[i]=0;
		}
		for(int i=0; i<len; i++) {
			v[s[i]-'a']=1;
		}
		bool f=0;
		for(int i=0; i<26; i++) {//枚举1个字母
			if(v[i]==0) {
				cout<<(char)(i+'a')<<endl;
				f=1;
				break;
			}
		}
		if(f){
			continue;
		}
		for(char i='a'; i<='z'; i++) {//枚举2个字母
			for(char j='a'; j<='z'; j++) {
				string str="";
				str+=i;
				str+=j;
				if(s.find(str)==s.npos) {
					cout<<str<<endl;
					f=1;
					break;
				}
			}
			if(f){
				break;
			}
		}
		if(f){
			continue;
		}
		for(char i='a'; i<='z'; i++) {//枚举3个字母
			for(char j='a'; j<='z'; j++) {
				for(char k='a'; k<='z'; k++) {
					string str="";
					str+=i;
					str+=j;
					str+=k;
					if(s.find(str)==s.npos) {
						cout<<str<<endl;
						f=1;
						break;
					}
				}
				if(f){
					break;
				}
			}
			if(f){
				break;
			}
		}
	}
	return 0;
}

```

---

## 作者：zwye (赞：0)

## 题意
对于一个字符串，定义它的 `MEX` 为不作为连续子字符串出现的最短字符串。
如果有多个 `MEX`，则选择字典序最小。
现在给出一个长度为 $n$ 的字符串，输出它的 `MEX`。

## 分析
根据题意知道，`MEX` 是指字典序最小的没出现在原字符串中的子串。
题目数据范围较小，意味着我们可以通过~~暴力~~ `DFS` 按字典序枚举子串再用 `KMP` 算法用枚举出来的子串与原字符串匹配，第一个找到在原字符串没出现过的子串就是题目所要求的。

## 代码
```c
#include<bits/stdc++.h>
using namespace std;
int t,n;
string st;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		cin>>st;
		string st_fd="a";
		while(1){
			if(st.find(st_fd)==-1){
				cout<<st_fd<<'\n';
				goto loop;
			}
			st_fd[st_fd.size()-1]++;
			for(int i=st_fd.size()-1;i>=0;i--)
				if(st_fd[i]>'z'){
					if(i!=0)
						st_fd[i]='a',st_fd[i-1]++;
					else st_fd[i]='a',st_fd='a'+st_fd;
				}
		}
		loop:;
	}
	return 0;
}
```



---

## 作者：thhxxx (赞：0)


# 分析

根据题意知道，MEX 是指字典序最小的没出现在原字符串中的子串。

题目数据范围较小 $1\leq n \leq 10^3$ ，意味着我们可以通过~~暴力乱搞~~ ```DFS``` 按字典序枚举子串再用 ```KMP``` 算法用枚举出来的子串与原字符串匹配，第一个找到在原字符串没出现过的子串就是题目所要求的。

# AC 代码

```
#include <iostream>
#include <cstring>
 
using namespace std;
 
char a[1000];//原串
char dfs_p[1010];//dfs枚举子串
int n;
 
bool check(const char arr[], const char patt[], int n_p, int m_a)
{
    bool flag=true;
    int nxt[1010];
    memset(nxt, 0, sizeof(nxt));
 
    for (int i=2, j=0;i<=n_p;i++)
    {
        while (j && patt[i]!=patt[j+1]) j=nxt[j];
        if (patt[i]==patt[j+1]) j++;
        nxt[i]=j;
    }
 
    for (int i=1, j=0;i<=m_a;i++)
    {
        while (j && arr[i]!=patt[j+1]) j=nxt[j];
        if (arr[i]==patt[j+1]) j++;
        if (j==n_p)
        {
            flag=false;
            j=nxt[j];
        }
    }
 
    return flag;
}
 
bool flag=true;
void dfs(int s, int limit)
{
    if (!flag) return;
    if (s>limit)
    {
        if (check(a, dfs_p, limit, n))
        {
            for (int i=1;i<=limit;i++) cout<<dfs_p[i];
            cout<<'\n';
            flag=false;
        }
        return;
    }
 
    for (int i=0;i<26;i++)
    {
        dfs_p[s]=(char)(i+'a');
        dfs(s+1, limit);
        if (!flag) return;//找到后直接return
    }
}
 
int main()
{
    int T;
    cin>>T;
 
    while (T--)
    {
        cin>>n;
        flag=true;
 
        for (int i=1;i<=n;i++) cin>>a[i];
 
        for (int len=1;len<=1000;len++)
        {
            dfs(1, len);
            if (!flag) break;//找到后直接break
        }
    }
    
    return 0;
}
```

---

