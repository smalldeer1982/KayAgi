# Qingshan Loves Strings 2

## 题目描述

我们称长度为 $ k $ 的01串 $ a $ 是**好的**且仅当

- $ \forall i \in \left [ 1,k  \right ], a_i \ne a_{k-i+1}$

比如，$ \texttt{10} $ , $ \texttt{1010} $ , $ \texttt{111000} $ 是好的，而 $ \texttt{11} $ , $ \texttt{101} $ , $ \texttt{001} $ , $ \texttt{001100} $ 不是好的。

现在给你一个01串 $ s $，你可以执行不多于 $ 300 $ 次以下操作使得 $ s $ 变为好的（次数可以为 $ 0 $）：

- $ \text{插入} \texttt{01} \text{到} s \text{的任意位置} $

请你判断是否有解，并在有解的情况下输出操作次数和每个操作的插入位置。

## 说明/提示

在第一组样例中，你不需要进行任何操作就可以使 $ s $ 为好的01串。

另一种方法是插入$\texttt{01}$到第 $ 1 $ 项后面，即：

1. $ \texttt{0}\underline{\texttt{01}}\texttt{1} $

最终 $ s = \texttt{0011} $，是好的01串。

在第二组样例中，没有办法使 $ s $ 变好。

在第四组样例中，你可以进行如下操作：

1. $ \texttt{001110}\underline{\texttt{01}} $
2. $ \texttt{0011100}\underline{\texttt{01}}\texttt{1} $

最终 $ s = \texttt{0011100011} $，是好的01串。

## 样例 #1

### 输入

```
6
2
01
3
000
4
1111
6
001110
10
0111001100
3
001```

### 输出

```
0

-1
-1
2
6 7
1
10
-1```

# 题解

## 作者：251Sec (赞：2)

\*1300？\*3100！

很需要观察力和想象力的题目，可惜我都没有。

---

首先无论如何 $0$ 和 $1$ 个数之差不变，所以必须 $0$ 和 $1$ 个数相等才有解，我们猜测这是充要的。考虑给出构造。

如果 $s$ 的开头结尾不相同，我们可以直接不考虑它们。那么只需考虑 $s$ 的开头结尾相同的问题，发现：

如果 $s$ 的开头为 $0$ 且结尾为 $0$，则可以在结尾添加 $01$，这等效于把开头的 $0$ 移到结尾，反之我们在开头添加 $01$，这等效于把结尾的 $1$ 移到开头。经由这样的操作，我们显然可以把整个串消完。

考察操作次数。可以发现原串的每个数最多被移动一次，所以这样的操作次数不超过 $n$，实际上我们有更紧的界：因为每次被消掉的 $0$ 和 $1$ 之中至多有一个被移动了，所以实际上操作次数不超过 $\frac{n}{2}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, n;
deque<int> a;
int del, ope[305], oC;
int c0, c1;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		a.resize(n);
		c0 = c1 = 0;
		for (int i = 0; i < n; i++) scanf("%1d", &a[i]), (a[i] == 0 ? c0 : c1)++;
		if (c0 != c1) {
			puts("-1");
			continue;
		}
		del = oC = 0;
		while (a.size()) {
			if (a.front() != a.back()) {
				a.pop_back();
				a.pop_front();
				del++;
				continue;
			}
			if (a.front() == 0) {
				ope[++oC] = a.size() + del;
				a.push_back(0);
				a.push_back(1);
			}
			else {
				ope[++oC] = del;
				a.push_front(1);
				a.push_front(0);
			}
		}
		printf("%d\n", oC);
		for (int i = 1; i <= oC; i++) printf("%d%c", ope[i], " \n"[i == oC]);
	}
	return 0;
}
```

---

## 作者：LXcjh4998 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1889A)
# 题意
我们称长度为 $k$ 的 $\texttt{01}$ 串 $a$ 是**好的**当且仅当

- $\forall i\in\left[1,k\right],a_i\ne a_{k-i+1}$

现在给你 $t$ 个 $\texttt{01}$ 串 $s$，你可以执行不多于 $300$ 次以下操作使得 $s$ 变为好的（次数可以为 $0$）：

- $\text{插入}\texttt{01}\text{到}s\text{的任意位置}$

对于每个 $\texttt{01}$ 串 $s$，若无法使它变好，则输出 $-1$；否则输出操作次数和每次插入的位置 $x_i$（当 $x_i=0$ 时表示插入到 $s$ 的开头，否则表示插入到 $s_i$ 的后面）。
# 思路
首先，一个 $\texttt{01}$ 串 $s$ 如果是好的，则它的 $0$ 和 $1$ 的个数应该相等（这是因为 $s_i$ 和 $s_{k-i+1}$ 中必须一个是 $0$，一个是 $1$）。

又因为插入 $\texttt{01}$ 不能使 $s$ 中 $0$ 和 $1$ 的个数由不相等变为相等。
因此我们可以统计 $s$ 中 $0$ 和 $1$ 的个数，若不相等则直接输出 $-1$，否则要继续寻找方案。

我们可以使用双指针 $i$ 和 $j$ 遍历字符串 $s$：

- 当 $s_i=s_j=0$ 时，我们可以将 $\texttt{01}$ 插入到 $s_j$ 的后面。
- 当 $s_i=s_j=1$ 时，我们可以将 $\texttt{01}$ 插入到 $s_i$ 的前面。
- 当 $s_i\ne s_j$ 时，则不做处理。

用一个变量记录插入的次数，用一个数组记录插入的位置，最后输出即可。

例如，对于第 $4$ 组样例，模拟的情况如下（字符串中标红的为 $i$ 和 $j$ 的位置）：

- $s=\texttt{\textcolor{red}{0}0111\textcolor{red}{0}}$，$i=1$，$j=6$，$s_i=s_j=0$，在 $s_j$ 后插入 $\texttt{01}$。

- $s=\texttt{0\textcolor{red}{0}1110\textcolor{red}{0}1}$，$i=2$，$j=7$，$s_i=s_j=0$，在 $s_j$ 后插入 $\texttt{01}$。

- $s=\texttt{00\textcolor{red}{1}1100\textcolor{red}{0}11}$，$i=3$，$j=8$，$s_i\ne s_j$，跳过。

- $s=\texttt{001\textcolor{red}{1}10\textcolor{red}{0}011}$，$i=4$，$j=7$，$s_i\ne s_j$，跳过。
- $s=\texttt{0011\textcolor{red}{1}\textcolor{red}{0}0011}$，$i=5$，$j=6$，$s_i\ne s_j$，结束。

因此输出结果为：
```
2
6 7
```
# 程序
```
#include<bits/stdc++.h>
using namespace std;
int t,len,sum0,sum1,ans,arr[300];//t为组数，len为字符串的长度，sum0、sum1分别为字符串中0、1的个数，ans为操作次数，arr[]存储插入的位置 
char str[702];//str[]存储字符串 
void solve(){
	sum0=sum1=ans=0;//初始化 
	
	scanf("%d%s",&len,str+1);//读入len和str[] 
	
	for(int i=1;i<=len;++i){//统计0和1的个数 
		if(str[i]=='0')++sum0;
		else ++sum1;
	}
	
	if(sum0!=sum1){//如果不相等，输出-1并返回 
		printf("-1\n");
		return;
	}
	
	for(int i=1,j=len;i<j;){
		if(str[i]=='0'&&str[j]=='0'){ 
			arr[ans++]=j;//记录插入位置 
			
			for(int k=len+1,l=len+3;k>j;--k,--l)str[l]=str[k];//在str[j]后插入01 
			str[j+1]='0',str[j+2]='1';
			
			len+=2,++i,++j;//增加长度，移动指针 
		}
		else if(str[i]=='1'&&str[j]=='1'){
			arr[ans++]=i-1;//记录插入位置 
			
			for(int k=len+1,l=len+3;k>=i;--k,--l)str[l]=str[k];//在str[i]前插入01，就是在str[i-1]后插入01 
			str[i]='0',str[i+1]='1';
			
			len+=2,++i,++j;//增加长度，移动指针 
		}
		else ++i,--j;//移动指针 
	}
	
	printf("%d\n",ans);//输出ans
	for(int i=0;i<ans;++i)printf("%d ",arr[i]);//输出arr[] 
	printf("\n");
}
int main(){
	scanf("%d",&t);//输入组数
	 
	for(int i=0;i<t;++i)solve();//解决问题 
	
	return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：1)

为什么没有人写题解呢？很有趣的小思维题。

**分析**

毫无疑问可以得到一个结论：$\texttt{0}$ 和 $\texttt{1}$ 的出现次数相同，否则必然无解。

接下来不妨手动模拟一些很小的情况。

**情况 A** 为 $\texttt{0110}$。首先发现首尾相同不行，因此在末尾添加 $\texttt{01}$ 变为 $\texttt{011001}$。这时符合条件。

**情况 B** 再看 $\texttt{1001}$。首尾相同不满足条件，在前面添加 $\texttt{01}$ 变为 $\texttt{011001}$。这时符合条件。

再看 $\texttt{001110}$。首尾相同不满足条件，仿照情况 A，末尾添加变为 $\texttt{00111001}$。此时首尾已经满足条件，可以忽略它们（因为对应关系是第 $i$ 个对应倒数第 $i$ 个，在中间插入不影响）。看 $\texttt{011100}$，依旧仿照 A 改为 $\texttt{01110001}$，满足条件。

从以上小情况模拟中，我们得到了一个方法。当我们试图解决区间 $[l,r]$ 时，首为 $l$，尾为 $r$，则：

- 若首尾均为 $\texttt{0}$，在末尾添加 $\texttt{01}$，变为新子问题 $[l,r+2]$；

- 若首尾均为 $\texttt{1}$，在开头添加 $\texttt{01}$，变为新子问题 $[l-2,r]$；

- 若首尾不同，则消掉首尾，变为新子问题 $[l+1,r-1]$。

注意到，**前两项之后必然伴随第三项。** 故可以简化为：

- 若首尾均为 $\texttt{0}$，变为子问题 $[l+1,r+1]$；

- 若首尾均为 $\texttt{1}$，在开头添加 $\texttt{01}$，变为新子问题 $[l-1,r-1]$；

- 若首尾不同，则消掉首尾，变为新子问题 $[l+1,r-1]$。

此时可以递归解决。

**然而，如果只出现前两个情况，递归不就无法结束了吗？**

事实上这种情况不会存在。不妨以第一种情况为例：若区间 $[l,r]$ 满足 $a_l=a_r=\texttt{0}$，则执行第一种情况，执行子问题 $[l+1,r+1]$，其中 $a_{r+1}=\texttt{0}$（因为这是我们添加的 $\texttt{01}$）。此时若 $a_{l+1}=\texttt{1}$ 则可以转为情况三；否则转为 $[l+2,r+2]$ 的子问题，$a_{r+2}=\texttt{0}$（原因同上）。若 $a_{l+2}=\texttt{1}$ 转为情况三，否则继续......发现，必然会转化为情况三，除非 $[l,r]$ 全是零。但这种情况已经被判过了。

```cpp
#include <bits/stdc++.h> 
const int DELTA=50000;
using namespace std;
int T,N;
int a[100005],b[100005];
vector<int>ans;
void Func(int l,int r,int t)
{
//	printf("(%d %d)\n",l,r);
	if(l>r) return;
	if(a[l]!=a[r])
	{
		Func(l+1,r-1,t);
		return;
	}
	if(a[l]==1)
	{
		a[l-1]=1;
		ans.push_back(t+l-1-DELTA);
		Func(l-1,r-1,t+2);
		return;
	}
	ans.push_back(t+r-DELTA);
	a[r+1]=0;
	Func(l+1,r+1,t);
	return;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++) scanf("%1d",&a[DELTA+i]);
		int cnt=0;
		for(int i=1;i<=N;i++) 
		{
			if(a[DELTA+i]==1) cnt++;
			else cnt--;
		}
		if(cnt!=0)
		{
			puts("-1");
			continue;
		}
		ans.clear();
		Func(1+DELTA,N+DELTA,0);
		if(ans.size()&&ans[0]==-1)
		{
			puts("-1");
			continue;
		}
		printf("%d\n",ans.size());
		for(int i=0;i<ans.size();i++) printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

vp 到的。

# 题目链接

[CF1889A Qingshan Loves Strings 2](https://www.luogu.com.cn/problem/CF1889A)

# 解题思路

我们考虑从头到尾依次判断情况。

维护两个指针 $l,r$ 来依次比较，直到有 $a_l = a_r$。

这种情况根据题目所述是不合法的，因此我们需要依次分讨一下两种情况：

- $a_l = a_r = 1$，这时我们只需要在 $s_l$ 前加上 $01$ 即可满足这两个字符不等的条件。

- $a_l = a_r = 0$，这时我们只需要在 $a_r$ 后加上 $01$ 即可满足这两个字符不等的条件。

容易发现每次操作要么对字符串造成至少 $1$ 的贡献，要么造成负数的贡献，也就是不合法的情况。

一直做操作直到当前字符串合法或者操作超过 $300$ 次并判断无解即可。

时间复杂度 $O(nV)$，其中 $V$ 为操作次数。

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
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);init();
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
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
/*

0011100011

我擦，不等于。。。

001110

*/
ll t;
ll n;
ll pd;
string s;
vector<ll>ans; 
string F(string s,ll x)//s0~sx-1+01+sx~s_sz 
{
//	cout<<"cg:"<<x<<endl; 
	string S="";
	ll len=s.size();
	forl(i,0,x-1)
		S+=s[i];
	S+="01";
	forl(i,x,len-1)
		S+=s[i];
//	cout<<"F:"<<S<<endl;
	return S;
}
bool check(string s)
{
//	cout<<"ck:"<<s<<endl;
	ll sz=s.size();
	forl(i,0,sz-1)
		if(s[i]==s[sz-i-1])
		{
		//	cout<<i<<' '<<sz-i<<endl;
			return 0;
		}
	return 1;
}
void f(string&s)
{
	ll L=0,R=(ll)s.size()-1;
	while(L<R)
	{
		if(s[L]!=s[R])
		{
			L++,R--;
			continue;
		}
		if(s[L]=='0')
		{
			ans.pb(R+1);
			s=F(s,R+1);
			return ;
		}
		else
		{
			ans.pb(L);
			s=F(s,L);
			return ;
		}
	}
	pd=1;
}
void _clear(){ans.clear(),n=0,s="";pd=0;}
void solve()
{
	_clear();
	cin>>n>>s;
	//s=' '+s;
	while(ans.size()<305 && !pd)
	{
		f(s);
	//	cout<<s<<endl;
	}
	if(!check(s))
	{
		cout<<-1<<endl;
		return ;
	}
	cout<<ans.size()<<endl;
	for(auto i:ans)
		cout<<i<<' ';
	cout<<endl; 
}
void init(){}
int main()
{
	IOS;
	t=1;
 	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

