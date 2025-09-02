# Divide by Three

## 题目描述

在一个黑板上写着一个正整数 _n_ 。它有不超过10^5位（~~话说黑板上是怎么写下这个数的~~） 。老师给你了一个任务，把它~~魔~~改成一个 _美丽数_ ，而且因为你很懒，你非常非常的想用最小的步数把它改成一个 _美丽数_ 。

_美丽数_ ，就是一个不含前导0，是3的倍数且位数大于零的正整数。举个~~栗子~~例子，0、99、10110都是 _美丽数_ ，但00、03、122都不是。

你决定写一个程序来帮助你的老师来完成这个无聊的任务。你的要求就是用最小的步数来完成这个任务。

如果不可能通过删数来达到 _美丽数_ ，输出-1。如果有多个最优解答案，输出任意一个即可。

## 样例 #1

### 输入

```
1033
```

### 输出

```
33
```

## 样例 #2

### 输入

```
10
```

### 输出

```
0
```

## 样例 #3

### 输入

```
11
```

### 输出

```
-1
```

# 题解

## 作者：A_zjzj (赞：5)

### 一道 dp 好(duliu)题

用 $f_{i,j}$ 表示前 $i$ 位模 $3$ 是 $j$ 最少要删掉几个数。

那么转移方程就很显然了：

$$f_{i,j}=\min\{f_{i-1,j}+1,f_{i-1,(j-c_i+3)\bmod3}\}$$

初始化：$f_{1,0}=1,f_{1,(c_1-'0')\bmod3}=0$，

注意顺序不能换，因为如果 $(c_1-'0')\bmod3=0$ 那么 $f_{1,0}$ 就变成了 $1$。

然而这道题还没完，

因为他还要输出路径，那你就记录一下路径不就完事了。

一些细节代码里看：

### 代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n;
char c[100002],ans[100002];
int f[100001][3],p[100001][3],len;
int main(){
	scanf("%s",c+1);
	memset(f,0x7f,sizeof(f));//求最小值赋值成最大值
	memset(p,-1,sizeof(p));
	n=strlen(c+1);
	if(n==1)return printf("%s",(c[1]-'0')%3==0?c+1:"-1"),0;//特判
	f[1][0]=1;f[1][(c[1]-'0')%3]=0;
	for(int i=2;i<=n;i++){
		int x=(c[i]-'0')%3;
		for(int j=0;j<3;j++){
			f[i][j]=f[i-1][j]+1;
			p[i][j]=j;
			if(c[i]=='0'&&f[i-1][j]==i-1)continue;
			if(f[i][j]>f[i-1][(j-x+3)%3]){
				f[i][j]=f[i-1][(j-x+3)%3];
				p[i][j]=(j-x+3)%3;
			}
		}
	}
	if(f[n][0]==n){
		for(int i=1;i<=n;i++)if(c[i]=='0')return printf("0"),0;
		return printf("-1"),0;
	}
	int pre;
	for(int i=n,j=0;i>=2;j=pre,i--){
		pre=p[i][j];
		if(f[i-1][pre]==f[i][j])ans[++len]=c[i];//记录要选的数
	}
	if((c[1]-'0')%3==pre)ans[++len]=c[1];//判断第一个数要不要选
	for(int i=len;i>=1;i--)printf("%c",ans[i]);
	puts("");
	return 0;
}
```

---

## 作者：lgx57 (赞：1)

一道边界条件比较多的贪心。

首先要知道如何判断一个数是不是 $3$ 的倍数是很显然的（不会有人不知道吧）。

所以我们只需要让各位数字之和为 $3$ 的倍数即可。

我们设现在的数字为 $x$。分 $3$ 种情况讨论。

1. $x \equiv 0 \pmod 3$

这种情况最简单，只需要输出 $x$ 即可。

2. $x \equiv 1 \pmod 3$

相当于要删掉 $1$ 或 $4$（因为要考虑删掉 $2$ 个 $\equiv 2 \pmod 3$ 的数）。可以提前把 $\equiv 1 \pmod 3$ 或 $\equiv 2 \pmod 3$ 的数的下标存到一个 vector 里。注意后面要 reverse，因为要考虑前导 $0$，所以尽量删靠后的数。注意两种情况去取最小。

3. $x \equiv 2 \pmod 3$

同上。

在处理的同时，请注意无解情况，具体可以看代码。

最后要处理前导 $0$，然后就做完了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pii pair<int,int>
#define endl '\n'
#define pb push_back
#define ls(p) ((p)<<1)
#define rs(p) ((p)<<1|1)
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int N=1e5+5;
bool ans[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string s;
	cin>>s;
	int n=s.size();
	s=" "+s;
	bool f=0;
	for (int i=1;i<=n;i++) ans[i]=1;
	int cnt=0;
	for (int i=1;i<=n;i++){
		if (s[i]=='0') cnt++,ans[i]=0;
		else break;
	}
	if (cnt==n) return cout<<0,0;
	vector<int> pos1,pos2;
	int sum=0;
	int pos=0;
	for (int i=1;i<=n;i++){
		if ((s[i]-'0')%3==1) pos1.pb(i);
		if ((s[i]-'0')%3==2) pos2.pb(i);
		sum=(sum+s[i]-'0')%3;
	}
	reverse(pos1.begin(),pos1.end());
	reverse(pos2.begin(),pos2.end());
	if (sum==0){
		for (int i=1;i<=n;i++) cout<<s[i];
		return 0;
	}
	else if(sum==1){
		int ans1=1e9,ans2=1e9;
		if (pos1.size()!=0){
			ans1=1;
			for (int i=1;i<=n;i++){
				if (i==pos1[0]) continue;
				if (s[i]!='0') break;
				ans1++;
			}
		}
		if (pos2.size()>=2){
			ans2=2;
			for (int i=1;i<=n;i++){
				if (i==pos2[1]||i==pos2[0]) continue;
				if (s[i]!='0') break;
				ans2++;
			}
		}
		if (pos1.size()==0&&pos2.size()<2) return cout<<-1,0;//不够删
		if (ans1<ans2) ans[pos1[0]]=0;
		else ans[pos2[0]]=ans[pos2[1]]=0;
	}
	else{
		int ans1=1e9,ans2=1e9;
		if (pos2.size()!=0){
			ans1=1;
			for (int i=1;i<=n;i++){
				if (i==pos2[0]) continue;
				if (s[i]!='0') break;
				ans1++;
			}
		}
		if (pos1.size()>=2){
			ans2=2;
			for (int i=1;i<=n;i++){
				if (i==pos1[1]||i==pos1[0]) continue;
				if (s[i]!='0') break;
				ans2++;
			}
		}
		if (pos2.size()==0&&pos1.size()<2) return cout<<-1,0;//不够删
		if (ans1<ans2) ans[pos2[0]]=0;
		else ans[pos1[0]]=ans[pos1[1]]=0;
	}
	for (int i=1;i<=n;i++){
		if (!ans[i]) continue;
		if (s[i]!='0') break;
		ans[i]=0;
	}
	f=0;
	for (int i=1;i<=n;i++){
		if (ans[i]) cout<<s[i],f=1;
	}
	if (!f){
		for (int i=1;i<=n;i++) if (s[i]=='0') return cout<<0,0;
		cout<<-1;//没有 0，但是最后全部删掉了。
	}
	return 0;
}
```

---

## 作者：dingshengyang (赞：1)

这题不需要 DP。

贪心即可。

引理：若 $a \bmod 3 = 0$，则 $a$ 的各个数位之和模三为 $0$。

证明：

以三位数为例。

设此数 $x=100a+10b+c$。


$\because 100 \bmod 3 = 1$

$\because 10 \bmod 3 = 1$

$\therefore x \equiv (a+b+c)$。

$\because x \bmod 3 = 0$

$\therefore (a+b+c) \bmod 3 = 0$

四位和其它位数的整数亦同理，此处不再赘述。

于是要删除最少数。

令 $d = $ 数位之和 $\bmod 3$。

于是当 $d = 0$ 时，不需要删（本来就是）；

当 $d = 1$ 时，可删一个 $1$ 或两个 $2$。

当 $d = 2$ 时，可删一个 $2$ 或两个 $1$。 

PS：$0,1,2$ 均指数位上的数字模三之后的数。

但是从前往后删会出现前导零，于是不难发现从后往前删最优。

然后注意从后往前添加，需要反转回去。

然后，**去前导零**。

虽然去前导零是普及组必备知识（不会还敢来做蓝题）。

但是还是给一下代码。

概要：如果这是最后一个数字，即使为零也不删；

否则有零删零；

如果遇到非零数，直接之后都不删了。

代码。

```cpp
#include<bits/stdc++.h>
using namespace std; 
int st[3],s;
string str;
string ans;
string tmp;
string a; 
void del(string& str_){
	a = str_;
	str_ = "";
	int flag = 0;
	for(int i = 0;i < a.size();i ++){
		if(i == a.size()-1){
			str_ += a[i];
		}
		else if(a[i] == '0'){
			if(flag)str_ += a[i];
			continue;
		}else{
			flag = 1;
			str_ += a[i];
		}
	}
}
int main(){
	char ch;
	bool okay = false;
	while(cin >> ch){
		str += ch;
		s = (s+ch-48)%3;
		st[(ch-48)%3] ++;
	}
	// cout << s << endl;
	if(s == 0){
		okay = true;
		tmp = str;
	}
	if(s == 1){
		int flag = 0;
		if(st[1] >= 1){
			okay = true;
			for(int i = str.size() - 1;i >= 0;i --){
				if((str[i]-'0')%3 == 1){
					flag ++;
					if(flag <= 1)continue;
				}
				tmp += str[i];
			}
		}
		flag = 0;
		if(st[2] >= 2){
			okay = true;
			for(int i = str.size() - 1;i >= 0;i --){
				if((str[i]-'0') %3 == 2){
					flag ++;
					if(flag <= 2)continue;
				}
				ans += str[i];
			}
		}
		
	}
	if(s == 2){
		int flag = 0;
		if(st[2] >= 1){
			okay = true;
			for(int i = str.size() - 1;i >= 0;i --){
				if((str[i]-'0')%3 == 2){
					flag ++;
					if(flag <= 1)continue;
				}
				tmp += str[i];
			}
		}
		flag = 0;
		if(st[1] >= 2){
			okay = true;
			for(int i = str.size() - 1;i >= 0;i --){
				if((str[i]-'0') %3 == 1){
					flag ++;
					if(flag <= 2)continue;
				}
				ans += str[i];
			}
		}
	}
	if(s){
		reverse(ans.begin(),ans.end());
		reverse(tmp.begin(),tmp.end());
	}
	// cout << ans << endl << tmp << endl;
	del(ans);
	del(tmp);
	// cout << ans << endl << tmp << endl;
	if(ans.size() == 0 && tmp.size() == 0)okay = false;
	if(!okay){
		cout << -1 << endl;
		return 0;
	}
	if(ans.size() > tmp.size())cout << ans << endl;
	else cout << tmp << endl;
	
	return 0;
}


```

---

## 作者：迟暮天复明 (赞：1)

[题面](https://codeforces.com/contest/792/problem/C)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16343800.html)

Description:

给你一个数 $n$，在其中删除尽可能少的数码，使得得到的数不含前导零且被 $3$ 整除。

$n\leq10^{10^5}$

-----
暴力分类讨论做法。

首先，我们将 $n$ 的每一位用这一位 $\bmod3$ 代替，明显的这样不会产生任何影响。

首先关于 $n\bmod3$ 可以分成三类：

1. $n\bmod3=0$，原封不动输出即可。
2. $n\bmod3=1$，那要么删除 $1$ 个 $1$，要么删除 $2$ 个 $2$。
3. $n\bmod3=2$，那要么删除 $2$ 个 $1$，要么删除 $1$ 个 $2$。

现在考虑实现一个函数 $\operatorname{del}\{a,b\}$ 返回 $n$ 删除 $a$ 个 $b$ 所得到的数。

为了减少前导零的出现，我们采取贪心的方法，从右往左删。删完预定的数字以后，再统一去除前导零。不难证明，这是最优的删数方法。

当然，还有一层特判。如果采用前面的删数方法都无解，但是 $n$ 的各个数位中本身有 $0$，那就输出单个 $0$。如果没有 $0$，那显然无解。

注意函数返回值的代码实现。个人认为用全局变量回传会好写一点。但这样别忘记数组的清零。

[代码](https://paste.ubuntu.com/p/J9HcTFc8Dy/)

---

## 作者：zhimao (赞：0)

此题其实不需要DP，贪心即可，过了CF的数据应该不会假掉吧。

我们分类讨论。

首先最高位要特殊考虑，因为删了最高位可能出现前导零 。学过小学奥数的人都知道 ，一个数能被 3 整除当且仅当它的所有数位上数字之和能被三整除。因此我们记录 $n$ 所有数位上数字之和模3 ，记为 $s$ ，和它数位上数字，模 3 为 1 , 2 的个数 。

如果 $s$ 为零直接输出。

如果有模 3 与 $s$ 相同的非最高位数 ，或最高位模 3 与 $s$ 相同且删去后无前导零 ，删去它即可。

如果有模 3 与 $s$ 不同的非最高位数至少两个 ，删去就好。

否则必然要删最高位 ，因为我们可以证明我们删去的数中不为零的至多两个 。证明如下：

枚举删去其中的三个数：
- 1 1 1 或 2 2 2 不如不删
- 1 1 2 或 1 2 2 其中的 1 2 不用删 。

则删了多余两个数的删法可以减到两个以内。

删最高位（和前导零）要特判：如果之后都是 0 ，直接输出 0 。

之后最多删一个数 ，优先考虑非当前最高位 。

那么，完了？

如果你就这样交上去 ，你将会 Wrong answer on test 29 ，Hack数据：202 。这提醒我们第一次删最高位时可以留一个 0 ，删去后面的数 。因此要加一个特判： $n$ 有零时程序最后判无解直接输 0 。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000000];
int bo[1000],n,m,ans,t,boo;
int main()
{
	scanf("%s",s);
	n=strlen(s);
	for(int i=1;i<n;i++)
	{
		++bo[s[i]%3];
		t=(t+s[i])%3;
		if(s[i]==48) ++boo;
	}
	t=(t+s[0])%3;
	if(!t)
	{
		for(int i=0;i<n;i++) printf("%c",s[i]);
		return 0;
	}
	if(bo[t])
	{
		int i=0;
		for(;i<n;i++) if(s[i]%3==t&&i>0) break; else printf("%c",s[i]);
		for(i++;i<n;i++) printf("%c",s[i]);
		return 0;
	}
	if(bo[3-t]>1&&(s[0]%3!=t||(s[0]%3==t&&s[1]=='0')))
	{
		t=3-t;
		int i=0;
		for(;i<n;i++) if(s[i]%3==t&&i>0) break; else printf("%c",s[i]);
		for(i++;i<n;i++) if(s[i]%3==t&&i>0) break; else printf("%c",s[i]);
		for(i++;i<n;i++) printf("%c",s[i]);
		return 0;
	}
	if(n==1)
	{
		puts("-1");
		return 0;
	}
	if(boo==n-1)
	{
		puts("0");
		return 0;
	}
	t=(t-s[0]+99)%3;
	m=1;ans=1;
	while(s[m]=='0') ++ans,++m;
	--bo[s[m]%3];
	if(!t)
	{
		for(int i=m;i<n;i++) printf("%c",s[i]);
		return 0;
	}
	if(bo[t])
	{
		int i=m;
		for(;i<n;i++) if(s[i]%3==t&&i>m) break; else printf("%c",s[i]);
		for(i++;i<n;i++) printf("%c",s[i]);
		return 0;
	}
	if((t-s[m]+99)%3==0&&m<n-1)
	{
		++m;++ans;
		while(s[m]=='0'&&m<n-1) ++m,++ans;
		for(int i=m;i<n;i++) printf("%c",s[i]);
		return 0;
	}
	else
	{
		if(!boo) puts("-1"); else puts("0");
		return 0;
	}
}
```


---

