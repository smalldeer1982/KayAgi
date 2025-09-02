# [ABC363F] Palindromic Expression

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc363/tasks/abc363_f

整数 $ N $ が与えられます。 次の条件を全て満たす文字列 $ S $ としてあり得るものを $ 1 $ 個出力してください。そのような文字列が存在しなければ `-1` を出力してください。

- $ S $ は `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9` および `*` (乗算記号) からなる長さ $ 1 $ 以上 $ 1000 $ 以下の文字列である。
- $ S $ は回文である。
- $ S $ の先頭の文字は数字である。
- $ S $ を式として評価した値が $ N $ と一致する。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{12} $
- $ N $ は整数
 
### Sample Explanation 1

$ S\ = $ `11\*3\*11` は問題文の条件を満たします。他に条件を満たす文字列として $ S= $ `363` があります。

### Sample Explanation 2

$ S $ は `0` を含んではいけない点に注意してください。

## 样例 #1

### 输入

```
363```

### 输出

```
11*3*11```

## 样例 #2

### 输入

```
101```

### 输出

```
-1```

## 样例 #3

### 输入

```
3154625100```

### 输出

```
2*57*184481*75*2```

# 题解

## 作者：Mugino_Shizuri (赞：6)

F 题放这种东西真的没关系吗？？？

省流：适合放在 D 题的暴力 dfs。

你直接搜索，在过程中暴力枚举因数，同时判断其是否有与其回文的因数和是否有 $0$，并暴力向下递归，虽然时间 $O(玄学)$ 但能过这道水题是板上钉钉的。

这里注意一些细节：

+ 过程中可能不分解到底就有解，即自己就是不含 $0$ 的回文，中途要判。
+ 数位中不能有 $0$。
+ 要同时整除该数与回文数，不是分别整除就行（被坑了）。
+ 开 long long。
+ ~~给我点赞（真的很重要)~~。

放出大常数代码，仅供参考。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define int long long

const int N=1e3+10;
int sum[N],n;;

inline bool check0(int x){
	static int t[N],top;top=0;
	while(x){t[++top]=x%10;x/=10;}
	for(int i=1;i<=top;++i) if(!t[i]) return 0;
	return 1;
}
inline bool check(int x){
	static int t[N],top;top=0;
	while(x){t[++top]=x%10;x/=10;}
	for(int i=1;i<=top;++i) if(t[i]!=t[top-i+1]) return false;
	return true;
}
inline int rever(int x){
	static int t[N],top,s;s=0;top=0;
	while(x){t[++top]=x%10;x/=10;}
	for(int i=1;i<=top;++i) s=s*10+t[i];
	return s;
}
inline void print(int cnt,int s){
	for(int i=1;i<=cnt;++i) cout<<sum[i]<<'*';
	cout<<s;for(int i=cnt;i;--i) cout<<'*'<<rever(sum[i]);
}
void dfs(int dep,int s){
	if(check(s)&&check0(s)){print(dep-1,s);exit(0);}
	for(int i=2;i*i<=s;++i){
		if((s%(i*rever(i))==0)&&check0(i)&&check0(rever(i))){
			sum[dep]=i;dfs(dep+1,s/i/rever(i));
		}
	}
}

signed main(){
	cin>>n;dfs(1,n);cout<<"-1\n";
	return 0;
}
```

---

## 作者：OIer_Hhy (赞：5)

# Part 1 前言
赛时居然没切出来……

整数转字符串要用 to_string，长记性了。

# Part 2 题意

### 题目描述

给定整数 $N$ 。请输出 $1$ 个满足以下所有条件的字符串 $S$。如果不存在这样的字符串，请输出 `-1`。

- $S$ 是由 `1`、`2`、`3`、`4`、`5`、`6`、`7`、`8`、`9` 以及 `*`（乘法符号）构成的长度 $l(1 \le l \le 1000)$ 的字符串

- $S$ 是回文。
- $S$ 开头的字符是数字。
- $S$ 作为表达式计算的值等于 $N$ 。

### 输入格式
输入以以下形式由标准输入给出。
> $ N $
### 输出格式
如果存在满足条件的字符串，则输出该字符串，否则输出 `-1`。

### 提示

### 约束条件
- $ 1 \le N \le 10^{12}$
- $N$为整数
 
#### 样例 #1 解释
$S=`11*3*11`$ 满足问题语句的条件。其他符合条件的字符串还有$S=`363`$。

#### 样例 #2 解释
请注意 $S$ 不能包含 `0`。

# Part 3 正题

这道题，一看就知道可以用递归解决。

首先，算式的结果为 $n$，肯定要用 $n$ 的几个因数乘起来才能得到 $n$。

其次，我们要判断这个因子含不含 $0$，如果含 $0$ 直接 continue。

因为是回文串，所以每一个数都有它的镜反数（即两个数数位相同且拼起来能成为一个回文数）。

枚举每一个 $n$ 的因数 $x$，当 $n$ 能被 $x$ 和 $x$ 的镜反数 $y$ 的积整除时，将 $n$ 除以 $x \times y$，继续 `dfs(n/x/y)`。

若 `ret=dfs(n/x/y)` 返回的是非空字符串，就创建一个字符串，把 `ret` 放在中间，把 $x$ 与 $y$ 放在两边，再将字符串返回。

最后再返回空字符串，代表无解。

当 dfs 的结果为空字符串时，代表无解，输出 -1。

否则输出这个字符串。

然后……你就通过了此题。

My code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(3)
#define int long long 
namespace FIO{碳硫磷考试加油！}
using namespace FIO;
bool nozero(int x){
	if(x==0) return 0;
	while(x){
		if(x%10==0) return 0;
		x/=10; 
	}
	return 1;
}
int rev(int x){
	int ans=0;
	while(x){
		ans=ans*10+x%10;
		x/=10;
	}
	return ans;
}
string dfs(int n){
	if(nozero(n)&&n==rev(n)) return to_string(n); 
	for(int x=2;x*x<=n;x++){
		if(n%x==0&&nozero(x)){
			int y=rev(x);
			string ret=dfs(n/x/y);
			if(n/x%y==0&&ret.size())
				return to_string(x)+"*"+ret+"*"+to_string(y);
		}
	}
	return "";
}
int n;
signed main(){
	readI(n);
	string ret=dfs(n);
	if(ret.size()) cout<<ret<<endl;
	else cout<<-1<<endl;
	return 0;
}

```

---

## 作者：ran_qwq (赞：0)

若只题，但赛时没调出来啊。死因：没判非 $0$。

感觉是一个另类但复杂、细节巨多的思路。

首先预处理出 $\sqrt N\le10^6$ 以内的拼出情况。我们先考虑一个子问题，把所有符合条件的二元的配对 $(i,\operatorname{rev}(i))$ 给预处理出来（这里 $\operatorname{rev}(i)$ 表示 $i$ reverse 过来形成的数）。接着枚举一个可被拼出的数 $i$，枚举它的倍数 $j$，如果 $\dfrac ji$ 可被拼出就合并，并用 vector 存储方案。

先考虑中间那个单独的回文数，枚举 $N$ 的因数去掉它。剩下就是配对的情况。

接下来递归解决问题，设当前的 $N$ 为 $n$。

+ 若 $n\le\sqrt N$ 且在预处理过程中被拼出，则直接返回方案。
+ 否则枚举 $n$ 的因数 $d$（$d\le \sqrt n$）。
    + 如果 $d$ 和 $\dfrac nd$ 本身就是一合法二元配对，则配对成功。
    + 如果 $d$ 在预处理过程中被拼出，则转化为 $\dfrac nd$ 的子问题，继续递归下去。
    + 如果所有 $d$ 都不合法，则无解。

```cpp
ll n,F[N],G[N]; pair<ll,ll> f[N]; vector<pair<ll,ll>> g[N];
bool no0(ll x) {while(x) {if(x%10==0) return 0; x/=10;} return 1;}
ll rev(ll x) {string s=to_string(x); reverse(s.begin(),s.end()); return stoll(s);}
string mg(string s,vector<pair<ll,ll>> t) {
	if(!t.size()) return "";
	string ans=to_string(t[0].fir)+"*"+to_string(t[0].sec); for(auto [x,y]:t) if(pair<ll,ll>{x,y}!=t[0]) ans=to_string(x)+"*"+ans+"*"+to_string(y);
	if(!s.size()) return ans; int len=s.size(); string l=s.substr(0,len-1>>1),r=s.substr(len-1>>1); return l+"*"+ans+r; 
}
string MG(string s,ll x) {if(!s.size()) return to_string(x); int len=s.size(); string l=s.substr(0,len-1>>1),r=s.substr(len-1>>1); return l+"*"+to_string(x)+r;}
string sol(ll x) {
	if(x==1) return "1*1"; if(x<=N-10&&G[x]) return mg("",g[x]);
	for(ll i=2;i*i<=x;i++) if(x%i==0) {
		ll j=rev(x/i); if(i==j&&no0(i)&&no0(x/i)) return to_string(i)+"*"+to_string(x/i);
		if(G[i]) {string tmp=sol(x/i); if(tmp!="-1") return mg(tmp,g[i]);}
	}
	return "-1";
}
void QwQ() {
	n=rdll(),F[1]=G[1]=1;
	for(ll i=2,x;i<=min(n,(ll)N-10);i++) if(no0(i)) {x=rev(i); if(i*x<=N-10&&!F[i*x]) F[i*x]=G[i*x]=1,f[i*x]={i,x},g[i*x].pb(f[i*x]);}
	for(ll i=2;i<=min(n,(ll)N-10);i++) for(ll j=i<<1;j<=min(n,(ll)N-10);j+=i) if(F[j]&&G[i]&&!G[j]) G[j]=1,g[j]=g[i],g[j].pb(f[j/i]);
	for(ll i=1;i*i<=n;i++) if(n%i==0) {
		if(no0(i)&&i==rev(i)) {string s=sol(n/i); if(s!="-1") cout<<MG(s,i)<<"\n",exit(0);}
		if(no0(n/i)&&n/i==rev(n/i)) {string s=sol(i); if(s!="-1") cout<<MG(s,n/i)<<"\n",exit(0);}
	}
	puts("-1");
}
```

---

## 作者：Zhao_daodao (赞：0)

#  Palindromic Expression

几天前 abc 的 F 题。

### **Description**

给你一个很大的数 $N$，求任意一种分解方式，使得这个分解方式和乘号形成一个回文串。

要求分解方式中不存在 0。$N\le 10^{12}$。

### **solution**

不明所以的抽象题目，随便写一下就过了。

大概就是照着题目模拟，每一次都枚举因数，如果正着和反着都是原来的数的因数，就把原数除掉这两个数的因子，继续下去做。

因为对于一个数 $N$，显然一个因子 $x$ 和它的反转 $rx$ 的位数是相同的，不妨假设 $x\le rx$。

所以 $x^2\le x\times rx\le N$。显然枚举只需要枚举到 $\sqrt{N}$ 级别就可以了。

显然这种符合条件的数量非常少。在每一次到达计算的时候保留答案，记忆化搜索，可以极高的降低复杂度，大概是 $O(\sqrt N\times N 的因子个数)$。因为一发现解就退出，常数非常小。


如果没有符合条件的串，返回空串，最后特判 -1 即可。



### code
其实不用记忆化搜索也可以跑得非常快。

我的代码跑了 47ms。

```cp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
bool Check(string now){//判断是否是不包含 0 的回文串
    bool flag=1;int len=now.size();
    for(int i=0;i<len;i++)flag&=((now[i]!='0')&&(now[i]==now[len-i-1]));
    return flag;
}
bool check(string now){//判断是否不包含 0
    bool flag=1;int len=now.size();
    for(int i=0;i<len;i++)flag&=((now[i]!='0'));
    return flag;
}
string rever(string now){//反转字符串
    string ano="";
    for(int i=now.size()-1;i>=0;i--)ano+=now[i];
    return ano;
}
inline int to_num(string now){//字符串到数字的转化
    int cnt=0;
    for(int i=0;i<now.size();i++)cnt=cnt*10+(now[i]-'0');
    return cnt;
}
string make_ans(int n){
    string now=to_string(n);//转成字符串
    if(Check(now))return now;//如果本身就满足条件，直接返回
    for(int i=2;i*i<=n;i++){
        if(n%i)continue;
        string cn=to_string(i);
        if(check(cn)&&((n/i)%to_num(rever(cn))==0)){
            //正着反着都行
            int lst=(n/i)/to_num(rever(cn));
            string nn=make_ans(lst);//有解就直接返回
            if(nn.size())return cn+"*"+nn+"*"+rever(cn);
        }
    }
    return "";//无解返回空串
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    int n;cin>>n;string ans=make_ans(n);
    if(ans.size()==0)cout<<"-1\n";//输出 -1
    else cout<<ans ;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

这题也是直接枚举 $N$，若 $N$ 能同时整除一个数 $x$ 和 $x$ 倒着写得到的数，则将 $x$ 加入分解式的前面，将倒着写的 $x$ 加入分解式的后面，再递归枚举除完这两个数后剩下的 $N$。若有一时刻 $N$ 本身是回文的，则将 $N$ 加入分解式，输出整个式子并结束程序即可。

注意事项：

- 分解式中不能有 $0$！数位含 $0$ 的数也不行！
- 若一开始 $N$ 是回文的，直接把 $N$ 输出也是一种合法方案。
- 似乎不用判长度超限的情况。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f(int x){//反过来的x
	int y=0;
	while(x!=0) y=y*10+x%10,x/=10;
	return y;
}
int siz(int x){//计算x的位数
	int k=0;
	while(x!=0) k++,x/=10;
	return k;
}
bool check(int x){//判断x的数位上是否含0
	while(x!=0){
		if(x%10==0) return 0;
		x/=10;
	}
	return 1;
}
int n,a[1000005],top1,b[1000005],top2;
void print(){//打印表达式
	if(top1+top2<1){
		cout<<-1;
		exit(0);
	}
	if(top2==0){
		cout<<a[1];
		exit(0);
	}
	for(int i=1;i<=top1;i++) cout<<a[i]<<"*";
	for(int i=top2;i>1;i--) cout<<b[i]<<"*";
	cout<<b[1];
	exit(0);
}
void dfs(int x){
	if(check(x)&&x==f(x)){
		a[++top1]=x;
		print();
	}
	for(int i=2;i*i<=x;i++){
		if(!(check(i))) continue;
		if(x%i==0&&(x/i)%f(i)==0){
			a[++top1]=i,b[++top2]=f(i);
			dfs(x/i/f(i));
			top1--,top2--;
		}
	}
}
signed main(){
	cin>>n;
	dfs(n);
	print();
	return 0;
}

```

---

## 作者：Crazyouth (赞：0)

## 分析
挺简单的一个 F，质量中等。

首先注意到题目要求的是一种因数分解形式，因此先分解得到的 $n$，如果存在一个它的因数 $i$（$i>1$ 且 $i$ 不含数字 $0$），使 $\frac{n}{i}$ 还能整除 $\operatorname{rev}(i)$ （$\operatorname{rev}(i)$ 指数字上把 $i$ 反过来，例如 $\operatorname{rev}(123)=321$），那么我们把这两个数除掉，就可以递归解决剩下的数。否则如果找不到在搜索时用记忆化可以减小运行时长。

特别地，如果这个数本身是回文数且不含数字 $0$，那么直接输出即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
map<int,string> mp;
int check(int k)
{
	string s=to_string(k);
	for(int i=0;i<s.size();i++) if(s[i]!=s[s.size()-1-i]) return 0;
	return 1;
}
int rev(int k)
{
	string s=to_string(k);
	reverse(s.begin(),s.end());
	int ret=0;
	for(int i=0;i<s.size();i++) ret=ret*10+s[i]-'0';
	return ret;
}
int check2(int k)
{
	string s=to_string(k);
	for(int i=0;i<s.size();i++) if(s[i]=='0') return 0;
	return 1;
}
string dfs(int n)
{
	if(mp[n]!="") return mp[n];
	if(check(n))
	{
		if(check2(n))
		{
			mp[n]='*'+to_string(n)+'*';
			return '*'+to_string(n)+'*';
		}
		else
		{
			mp[n]="-1";
			return "-1";
		}
	}
	for(int i=2;i*i<=n;i++)
	{
		if(check2(i)&&n%i==0&&(n/i)%rev(i)==0)
		{
			if(dfs(n/i/rev(i))!="-1")
			{
				mp[n]='*'+to_string(i)+dfs(n/i/rev(i))+to_string(rev(i))+'*';
				return mp[n];
			} 
		}
	}
	mp[n]="-1";
	return "-1";
}
signed main()
{
	int n;
	cin>>n;
	string s=dfs(n);
	if(s=="-1") cout<<s; 
	else for(int i=1;i<s.size()-1;i++) cout<<s[i];
}

---

## 作者：wly09 (赞：0)

感觉 ABC 质量下降了。

## 题意简述

给定 $N$，求一个回文的乘法算式，算式的结果为 $N$。算式中不能出现 `0`。

## 思路

记 $\operatorname{rev}(n)$ 是将 $n$ 翻转后的结果，如 $\operatorname{rev}(1234)=4321$。

暴力分解 $n$，如果发现 $a$ 是 $n$ 的因数，检查 $\operatorname{rev}(a)$ 是否是 $\dfrac{n}{a}$ 的因数。若是，递归分解 $\dfrac{n}{a\cdot\operatorname{rev}(a)}$，直到得到一个合法的回文数字。

很暴力是不是？

然后你发现它过了。

[记录](https://atcoder.jp/contests/abc363/submissions/55794783)

---

## 作者：__O_v_O__ (赞：0)

此题可以预处理+搜索。

首先，预处理出一个数乘上这个数翻转后的数，结果被 $n$ 整除的数个数（话很绕，可以看代码）。

然后开始搜索，假设当前考虑的数为 $x$。如果 $x$ 中没有 0 且 $x$ 是回文数，则跳出函数，输出答案。否则，枚举每个预处理的数，如果它乘上它翻转的数被 $n$ 整除，则将 $n$ 除以乘积，继续搜索。

如果搜索完了还没有答案，则输出 `-1`。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define al(v) v.begin(),v.end()
int n;struct A{int x,a,b;};
vector<pair<int,int>>an;vector<A>v;
void dfs(){
    string s=to_string(n),t=s;
	reverse(al(t));
    if(count(al(s),'0')==0&&s==t){//满足条件，可以输出答案 
        string no="";//答案 
		for(int i=0;i<an.size();i++)
			no+=to_string(an[i].first)+'*';//拼接每个数 
        cout<<no<<n,reverse(al(no)),cout<<no;//输出 
		exit(0);//直接退出整个程序 
    }for(int i=0;i<v.size();i++){
    	int x=v[i].x,a=v[i].a,b=v[i].b;
        if(n%x)continue;//如果不整除 
		n/=x,an.push_back({a,b});//存储答案，继续递归 
		dfs();
        n*=x,an.pop_back();//回溯 
    }
}signed main(){
    ios::sync_with_stdio(0),cin>>n;
    for(int i=2;i<=1000000;i++){//预处理 
        string s=to_string(i);//数转为字符串，可以翻转 
        if(count(al(s),'0'))continue;//如果有0 
        reverse(al(s));//翻转 
		int j=stoll(s);//字符串转数 
        if(n%(i*j))continue;
        v.push_back({i*j,i,j});
    }
	dfs(),cout<<-1;
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[abc363f](https://atcoder.jp/contests/abc363/tasks/abc363_f)

# 解题思路

注意到一个数的因数只有 $O(\sqrt{n})$ 个，且此题中的表达式是需要为回文的，因此我们可以先预处理出所有自身乘倒过来的这个数的乘积为 $n$ 的因数的数。

然后就是爆搜了，由于我们已经预处理过，因此直接搜索可行的数即可，注意，可行的数**数位中不含零**。

注意要特殊处理中间的回文数的情况。

时间复杂度 $O(V + \sqrt{n} \times \log n)$，其中 $V$ 为 $10^6$。

# 参考代码


```cpp
/*
Tips:
你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define rei register
#define ll long long
#define forl(i,a,b) for(rei ll i=a;i<=b;i++)
#define forr(i,a,b) for(rei ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(rei ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(rei ll i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
void Max(ll&x,ll y){
	 x=max(x,y);
}
void Min(ll&x,ll y){
	 x=min(x,y);
}
ll t;
ll n;
ll ans[1010],k;
bool _0(ll x)
{
	ll pd=0;
	while(x)
		pd|=(x%10)==0,x/=10;
	return pd;
}
bool f(ll x)
{
	if(_0(x))
		return 0;
	string s="";
	while(x)
		s+=(char)(x%10+'0'),x/=10;
	string S=s;
	reverse(S.begin(),S.end());
	return s==S;
}
string re(ll x)
{
	string s="";
	while(x)
		s+=(char)(x%10+'0'),x/=10;
	return s;
}
string rev(string x)
{
	reverse(x.begin(),x.end());
	return x;
}
ll rnum(ll x)
{
	ll ans=0;
	while(x)
		ans*=10,ans+=x%10,x/=10;
	return ans;
}
ll num[1000010],KKK;
void init()
{
	KKK=0;
	forl(i,2,1e6)
		if(n%(i*rnum(i))==0 && !_0(i))
			num[++KKK]=i;//,cout<<i<<endl;
//	cout<<"_-----\n";
}
void dfs(ll x)
{
	if(f(x))
	{
		string an="";
		forl(i,1,k)
			an+=rev(re(ans[i])),an+='*';
		an+=rev(re(x));
		an+='*';
		forr(i,k,1)
			an+=re(ans[i]),an+='*';
		forl(i,0,(ll)an.size()-2)
			cout<<an[i];
		exit(0);
	}
	forl(i,1,KKK)
		if(x%(num[i]*rnum(num[i]))==0)
		{
			ans[++k]=num[i];
			dfs(x/(num[i]*rnum(num[i])));
			k--;
		}
}
void solve()
{
	cin>>n;
	init();
	dfs(n);
	cout<<-1<<endl;
}
int main()
{
//	init();
	IOS;
	t=1;
 //	cin>>t;
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

## 作者：fydj (赞：0)

**下文中提到的数字都不包含 0，注意把含 0 的数字特判掉。**

反转指各个数位倒过来，比如 ```114514``` 反转过后就是 ```415411```。

注意到，答案一定是这样：数列 $a$ 的各个数字相乘，乘以一个回文，再把数列 $a$ 倒过来，每个数反转，再相乘。

比如：```2*57*184481*75*2```，其中的数列 $a$ 就是：```2 57```，中间的回文就是 ```184481```。

搜索，先搜两边，把一个数和把它反转后的数拼成一对，如果 $n \mod (i\times i') =0$（$i'$ 是 $i$ 反转的数），那么 $i$ 就可以被加进数列里，然后把 $n$ 除以 $i\times i'$ 继续搜索，搜索出一个合法解就退出。

由于合法的对数不会太多，所以可以预处理可能出现在答案里的对，然后暴力搜索。

时间复杂度：$O(能过)$。

```cpp
const int N=1099;
ll n,a[N]={},fan[1000099]={};
bool nozero(ll n) {
	while(n) {
		while(n%10==0)
			return false;
		n/=10;
	}
	return true;
}
bool ishui(ll n) {
	if(!nozero(n))
		return false;
	int a[20]={},i,j;
	while(n)
		a[++a[0]]=n%10,
		n/=10;
	for(i=1,j=a[0];i<j;++i,--j)
		if(a[i]!=a[j])
			return false;
	return true;
}
ll turn(ll n) {
	ll ans=0;
	while(n)
		ans=ans*10+n%10,
		n/=10;
	return ans;
}
ll g[1000099]={},leftans=0;
bool solve(ll n) {
	if(ishui(n)) {
		leftans=n;
		return true;
	}
	for(int i=2;i<=g[0]&&g[i]*fan[g[i]]<=n;++i)
		if(n%(g[i]*fan[g[i]])==0) {
			if(solve(n/(g[i]*fan[g[i]]))) {
				a[++a[0]]=g[i];
				return true;
			}
		}
	return false;
}
int main()
{
	ll i;
	read(n);
	for(i=1;i<=1e6;++i) {
		fan[i]=turn(i);
		if(i<=fan[i]&&n%i==0&&(n/i)%fan[i]==0&&nozero(i))
			g[++g[0]]=i;
	}
	if(solve(n)) {
		for(i=1;i<=a[0];++i)
			printf("%lld*",a[i]);
		printf("%lld",leftans);
		for(i=a[0];i;--i)
			printf("*%lld",fan[a[i]]);
		printf("\n");
	} else printf("-1\n");
	return 0;
}
```

---

## 作者：fire_and_sweets (赞：0)

简单搜索题。

我们先预处理 $n$ 的所有因数 $x_i$。不难发现，如果选择一个 $x_i$，那表达式的值一定会变成 $x_i\times \mathrm{rv}(x_i)$，其中 $\mathrm{rv}(x)$ 表示把 $x$ 数位反转后得到的结果，例如 $\mathrm{rv}(12345)=54321$。

然后我们就可以开始暴搜了！对于一个数 $t$，如何将他表示成题目中要求的表达式呢？我们只需要枚举一个他的因数 $x'$，如果因数合法，就把 $t$ 除以 $x'\times \mathrm{rv}(x')$，然后递归处理即可。

如此可过。实现优秀的话可以做到 $\mathcal{O}(T^2)$ 左右，其中 $T$ 表示 $n$ 的因数个数。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n; vector<int> ys, res;
bool nozero(int x) {
	string s = to_string(x);
	return s.find('0') == s.npos;
}
int reve(int x) {
	string s = to_string(x); reverse(s.begin(), s.end());
	int res = 0;
	for (char i : s) res = res * 10 + i - '0';
	return res;
}
void print(int x) {
	for (auto i : res) cout << i << "*";
	cout << x;
	if (res.size()) {
		reverse(res.begin(), res.end());
		for (int i : res) cout << "*" << reve(i);
	}
	exit(0);
}
void solve(int n) {
	for (int i = 0; i < ys.size(); i ++ ) {
		if (ys[i] == reve(ys[i]) && nozero(ys[i]) && n == ys[i]) print(n);
		if (n % (ys[i] * reve(ys[i])) == 0 && nozero(ys[i]) && ys[i] != 1)
			res.push_back(ys[i]), solve(n / ys[i] / reve(ys[i])), res.pop_back();
	}
}
signed main() {
	cin >> n; int t = sqrt(n);
	for (int i = 1; i <= t; i ++ )
		if (n % i == 0) {
			ys.push_back(i);
			if (i != n / i) ys.push_back(n / i);
		}
	sort(ys.begin(), ys.end());
	solve(n);
	cout << -1 << endl; 
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑搜索。

设当前还需要乘上 $sum$，则一个 $sum$ 的约数 $v$ 能选入答案需要满足以下条件：

- $\operatorname{rev}(v)$ 也是 $\frac{sum}{v}$ 的约数。

- $v$ 和 $\operatorname{rev}(v)$ 都不包含 $0$。

还有一种情况即 $sum$ 本身就是一个不包含 $0$ 的回文数。

时间复杂度为 $\operatorname{d}(N)^2$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=1000;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,cnt;
ll ans[N];
bool f[N];
ll rev(ll x){
	ll s=0;
	while(x){
		s=s*10ll+x%10;
		x=x/10ll;
	}
	return s;
}
bool check(ll x){
	while(x){
		if(x%10==0)
		  return 0;
		x/=10;
	}
	return 1;
}
void dfs(ll sum){
	if(sum==rev(sum)&&check(sum)){
		for(int i=1;i<=cnt;i++){
			write(ans[i]);
			putchar('*');
		}
		write(sum);
		if(cnt)
		  putchar('*');
		for(int i=cnt;i>=1;i--){
			write(rev(ans[i]));
			if(i!=1)
			   putchar('*');
		}
		exit(0);
	}
	for(ll i=2;i*i<=sum;i++){
		if(check(i)&&sum%i==0&&sum/i%rev(i)==0){
			ans[++cnt]=i;
			dfs(sum/i/rev(i));
			cnt--;
		}
	}
}
bool End;
int main(){
	n=read();
	dfs(n);
	puts("-1");
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

## 作者：Ivan422 (赞：0)

第一次见到这么水的 F 题。

考虑分治。

定义一个字符串的反向字符串为 $\operatorname{h}(s)$，则一个回文表达式为 $s\times \operatorname{h}(s)$。还有一种情况，设一个回文字符串为 $\operatorname{p}(s)$，则一个回文表达式为 $s\times \operatorname{p}(t)\times\operatorname{h}(s)$。而每一次完成的回文表达式一定也是满足条件的，于是可以得出一种做法。

对于每一个未分解完的整数，先判定这个数是不是回文数，如果是就可以直接当做这一阶段的答案。要是不是回文数，就尝试分解。枚举其因数，找到符合条件分解即可。


```cpp
//2022tysc0819
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n;
string ans;
bool pa(string t){
	for(int i=0;i<(int)t.size();i++)if(t[i]!=t[(int)t.size()-i-1])return 0;
	return 1;
}
bool h0(string t){
	for(int i=0;i<(int)t.size();i++)if(t[i]=='0')return 1;
	return 0;
}
string dp(int x){
	string sx=to_string(x);
	if(!h0(sx)&&pa(sx))return sx;
	for(int i=2;i*i<=x;i++){
		if(h0(to_string(i))||x%i!=0)continue;
		string sx=to_string(i);
		string rsx=sx;reverse(rsx.begin(),rsx.end());
		int rx=stol(rsx);
		if((x/i)%rx!=0)continue;
		if(dp(x/i/rx).size()!=0)return sx+"*"+dp(x/i/rx)+"*"+rsx;
	}
	return "";
}
signed main(){
	cin>>n;
	ans=dp(n);
	if(ans=="")cout<<"-1";
	else cout<<ans;
    return 0;
}
//note:

```

---

