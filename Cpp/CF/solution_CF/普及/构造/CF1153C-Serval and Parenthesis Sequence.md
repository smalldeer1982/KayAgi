# Serval and Parenthesis Sequence

## 题目描述

Serval soon said goodbye to Japari kindergarten, and began his life in Japari Primary School.

In his favorite math class, the teacher taught him the following interesting definitions.

A parenthesis sequence is a string, containing only characters "(" and ")".

A correct parenthesis sequence is a parenthesis sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, parenthesis sequences "()()", "(())" are correct (the resulting expressions are: "(1+1)+(1+1)", "((1+1)+1)"), while ")(" and ")" are not. Note that the empty string is a correct parenthesis sequence by definition.

We define that $ |s| $ as the length of string $ s $ . A strict prefix $ s[1\dots l] $ $ (1\leq l< |s|) $ of a string $ s = s_1s_2\dots s_{|s|} $ is string $ s_1s_2\dots s_l $ . Note that the empty string and the whole string are not strict prefixes of any string by the definition.

Having learned these definitions, he comes up with a new problem. He writes down a string $ s $ containing only characters "(", ")" and "?". And what he is going to do, is to replace each of the "?" in $ s $ independently by one of "(" and ")" to make all strict prefixes of the new sequence not a correct parenthesis sequence, while the new sequence should be a correct parenthesis sequence.

After all, he is just a primary school student so this problem is too hard for him to solve. As his best friend, can you help him to replace the question marks? If there are many solutions, any of them is acceptable.

## 说明/提示

It can be proved that there is no solution for the second sample, so print ":(".

## 样例 #1

### 输入

```
6
(?????
```

### 输出

```
(()())```

## 样例 #2

### 输入

```
10
(???(???(?
```

### 输出

```
:(
```

# 题解

## 作者：hsfzLZH1 (赞：7)

## 题目大意

给定一个字符串 $s$ ，其中包含三种字符 ```'(',')','?'``` ，请你将 $s$ 中的 ```'?'``` 替换为 ```'(',')'``` ，使得 $s$ 全串为一个合法的括号序列，而 $s$ 的前缀不是一个合法的括号序列。

$1\le |s|\le 3\times 10^5$

## 解题思路

令 ```'('``` 代表 $+1$ ， ```')'``` 代表 $-1$ 。

一个合法的括号序列，第一位一定是 ```'('``` 。我们要使 $s$ 之前的所有和都大于 $0$ ，而全串对应的和等于 $0$ ，那就要尽量使其前缀和尽量大。

我们在串中一定会填入 $\frac n 2$ 个 ```'('``` ，由于要使其前缀和尽量大，我们要在靠前的位置填入 ```'('``` 。填完后，扫描一遍判断是否合法即可。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=300010;
int n,cnt,nww;
char s[maxn],ss[maxn];
int main()
{
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)ss[i]=s[i];
	for(int i=1;i<=n;i++)if(ss[i]==')')nww++;
	if(nww>n/2){printf(":(\n");return 0;}
	for(int i=n;i>=1;i--)
	{
		if(nww==n/2)break;
		if(ss[i]=='?')ss[i]=')',nww++;
		if(nww==n/2)break;
	}
	for(int i=1;i<=n;i++)if(ss[i]=='?')ss[i]='(';
	//printf("%s\n",ss+1);
	for(int i=1;i<=n;i++)
	{
		if(ss[i]=='(')cnt++;
		else cnt--;
		if(cnt<0||(i!=n&&cnt==0)||(i==n&&cnt!=0)){printf(":(\n");return 0;}
	}
	printf("%s\n",ss+1);
	return 0;
}
```

---

## 作者：wangqinyan (赞：4)

这题思路与代码实现其实都很简单。

**题目思路**

这道题其实可以模拟括号序列的构成。从字符串末尾的问号开始先将其替换成右括号，在右括号替换完后，再将剩余的问号替换成左括号即可。在字符串被替换完后，要判断该字符串是否合法。因为最后要构成一个合法的括号序列，因此，左右括号数量要相等。又由题意可知，非字符整串不能是可匹配的括号序列，因此在除了最后一个位置上的其他位置上的前缀左右括号数量不能相同。这样这题就做好了，具体可见代码。

**注意点**

在模拟括号序列的构成之前，可以先对字符数量的奇偶进行判断。如果字符数量为奇数，则可以直接输出找不到方案。

**代码**
```

#include<bits/stdc++.h>
using namespace std;
long long n,x,x1,ans;
string s;
int main()
{
	cin>>n;
	cin>>s;
	for(int i=0;i<n;i++)
	if(s[i]==')')x1++;
	if(n%2==1){cout<<":("<<endl;return 0;}
		for(int i=n-1;i>=0;i--)
		if(s[i]=='?')
		{
			if(x1<n/2)s[i]=')',x1++;
			else s[i]='(';
		}
	for(int i=0;i<n;i++){
		if(s[i]=='(')ans++;
		else ans--;
		if((i!=n-1&&ans==0)||ans<0)
		{
			cout<<":("<<endl;
			return 0;
		}
	}
	if(!ans)cout<<s<<endl;
	else cout<<":("<<endl;
	return 0; 
}
 
```
感谢观看！

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1153/C)
就是将字符串 $s$ 中的所有 `?` 替换为 `(` 或 `)`，使其满足以下条件：

1. 最终的字符串是一个合法的括号序列。

2. 所有严格前缀（即长度小于 $\lvert s \rvert$ 的前缀）都不是合法的括号序列。

## 思路
问题转换一下：

一个合法的括号序列需满足：

1. 左右括号数量相等。

2. 任意前缀中左括号的数量不少于右括号的数量。

严格前缀不能是合法的括号序列，这意味着对于所有前缀（除了整个字符串），左括号的数量**不能等于**右括号的数量。

显然，当 $\lvert s \rvert \equiv 1 \pmod 2$ 时，无解。

可以将 `(` 设为 $1$，将 `)` 设为 $-1$，通过维护一个 $balance$ 值进行判断是否无解。

具体细节看代码。

## 代码

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	string s;
	cin >> n >> s;
	if (n % 2 != 0) {
		cout << ":(\n";
		return 0;
	}
	int open = 0, close = 0;
	for (char c : s) {
		if (c == '(') open++;
		else if (c == ')') close++;
	}
	int reqOp = n / 2 - open;
	int reqCl = n / 2 - close;
	if (reqOp < 0 || reqCl < 0) {
		cout << ":(\n";
		return 0;
	}
	int bal = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '?') {
			if (reqOp > 0) {
				s[i] = '(';
				reqOp--;
			} else {
				s[i] = ')';
				reqCl--;
			}
		}
		if (s[i] == '(') bal++;
		else if (s[i] == ')') bal--;
		// 检查前缀条件
		if (bal < 0 || (i < n - 1 && bal == 0)) {
			cout << ":(\n";
			return 0;
		}
	}
	if (bal != 0) {
		cout << ":(\n";
	} else {
		cout << s << '\n';
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(n) $，可以通过本题。

---

## 作者：Big_Dinosaur (赞：1)

如果 $a \equiv 1 \pmod 2$，一定无解。

构造策略：设已知字符中有 $r$ 个 `)`，则将最后 $\dfrac{n}{2}-r$ 个 `?` 改成 `)`，其他的改成 `(`。

接下来检验答案：横扫字符串，定义 $t$ 为 $0$，扫到 `(` 加一，扫到 `)` 减一，若字符串没扫完却 $t=0$ 或任意时刻 $t<0$ 或扫完了之后 $t\ne 0$，无解，否则输出字符串。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,x,y)for(int i=(x);i<=(y);++i)
using namespace std;
namespace IO{
  inline int R(){
    int z=1,y=0;char t=getchar();while(t<'0'||t>'9'){if(t=='-')z=-1;t=getchar();}
    while(t<='9'&&t>='0'){y=(y<<1)+(y<<3)+(t^48);t=getchar();}return z*y;
  }
}
using namespace IO;
namespace Dino{
  inline void _(){
    int l=0,r=0,n=R();string s;cin>>s;if(n%2)puts(":(");
    else{
      for(int i=0;i<n;++i)
      if(s[i]=='(')++l;else if(s[i]==')')++r;
      for(int i=n-1;i>=0;--i)
      if(s[i]=='?'){if(r<n/2)s[i]=')',++r;else s[i]='(';}
      int t=0;
      for(int i=0;i<n;++i){
      	if(s[i]=='(')++t;else --t;if((i!=n-1&&t==0)||t<0){
        puts(":(");return;
       }
      }
      if(t==0)cout<<s;else puts(":(");
    }
  }
}
signed main(){Dino::_();}
```

---

## 作者：老彩笔 (赞：1)

我第一眼以为这道题是到水题,然而并不是

当我写完一百多行的模拟,隔壁$dalao$已经$AC$了

下面我就说一下思路以及需要注意的地方:

思路:

不是“?”的位置直接加到答案中

统计输入序列中左括号和右括号的个数

在后面补全答案时使两种括号的个数时都不超过$n/2$

然后补全答案即可

补全答案时优先**补完**左括号,再补右括号

或者先把剩余少的补完,再补另一个

我的代码主要是后者

思路看起来挺简单的,下面是要注意的地方

注意:

1. 长度是奇数肯定找不到,直接输出 “:(”来膜神鱼

1. 第一个是“)”或者“(”的序列一定不合法

1. 在输入序列中,如果“)”或者“(”的个数大于了$n/2$,一定不合法

1. 如果输入序列全是“?”,直接输出“(((……)))”即可

1. 在补全答案时,第一个一定补“(”,第$n$个一定补“)”

1. 在补全过程中要注意左括号和右括号的个数不能相等

大概就这些吧~~说多了都是泪啊~~

我的代码有些长:

$num1$和$num2$记录剩余的左右括号个数

$n1$和$n2$记录前$i$位中左右括号的个数


代码:

```cpp
#include<bits/stdc++.h>
#define djj ":("
using namespace std;
const int maxn=300005;
char s[maxn],ans[maxn];
int num1,num2;
int n,n1,n2;
int main()
{
	cin>>n;
	if(n%2==1)
	{
		cout<<djj<<'\n';
		return 0;
	}
	num1=num2=n/2;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		if(s[1]==')'||s[n]=='(')
		{
			cout<<djj<<'\n';
			return 0;
		}
		if(s[i]=='(')
		{
			ans[i]='(';
			num1--;
		}
		else if(s[i]==')')
		{
			ans[i]=')';
			num2--;
		}
		else ans[i]=' ';
		if(num1<0||num2<0)
		{
			cout<<djj<<'\n';
			return 0;
		}
	}
	if(num1==num2&&num1==n/2)
	{
		for(int i=1;i<=num1;i++)
			cout<<'(';
		for(int i=1;i<=num1;i++)
			cout<<')';
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(ans[i]=='(')n1++;
		else if(ans[i]==')')n2++;
		else 
		{
			if(i==1)
			{
				if(num1)
				{
					ans[i]='(';
					num1--;
					n1++;
				}
				else 
				{
					cout<<djj<<'\n';
					return 0;
				}
			}
			else if(i==n)
			{
				if(num2)
				{
					ans[i]=')';
					num2--;
					n2++;
				}
				else 
				{
					cout<<djj<<'\n';
					return 0;
				}
			}
			else if(n2<n1&&num1)//右括号个数小于左括号,就补左括号 
			{
				ans[i]='(';
				num1--;
				n1++;
			}
			else if(n1<n2&&num2)//左括号个数小于右括号，就补右括号 
			{
				ans[i]=')';
				num2--;
				n2++;
			}
			else if(!num1)//如果左括号没有剩余,就补右括号 
			{
				ans[i]=')';
				num2--;
				n2++;
			}
			else if(!num2)//如果右括号没有剩余,就补左括号 
			{
				ans[i]='(';
				num1--;
				n1++;
			}
			else if(num1<num2)//如果剩下的左括号比剩下右括号少 
			{
				ans[i]='(';
				num1--;
				n1++;
			}
			else if(num2<num1)//如果剩下的右括号比剩下左括号少 
			{
				ans[i]=')';
				num2--;
				n2++;
			}
		}
		if(n1==n2&&i!=n)//如果左右括号个数相等 
		{
			cout<<djj<<'\n';
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i];
	cout<<'\n';
	return 0;
}
```

蒟蒻没有很仔细的考虑有没有丢掉的情况,欢迎$dalao$们$hack$

祝大家$CSPrp++$




---

## 作者：xht (赞：1)

题目地址：[CF1153C Serval and Parenthesis Sequence](https://www.luogu.org/problemnew/show/CF1153C)

思路：贪心

如果有解，那么 $s_0 = ($ && $s_{n-1} = )$ && $n % 2 = 0$ 。

如果有解，那么 $s_1$ ~ $s_{n-2}$ 为一个合法的括号序列。

那么已知的 $($ 和 $)$ 个数不能超过一半

接下来贪心：如果有解，那么一定有一组解是把 $?$ 中左边一部分填成 $($ ，右边一部分填成 $)$ ，且保证 $($ 和 $)$ 个数正好为一半

那么就这样填呗

填完之后扫一遍是否合法就完了

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 6;
int n, c1, c2, v[N], mn = 1e9;
string s;

int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	cin >> s;
	if (s[0] == '?') s[0] = '(';
	if (s[n-1] == '?') s[n-1] = ')';
	if (s[0] != '(' || s[n-1] != ')') {
		puts(":(");
		return 0;
	}
	if (n & 1) {
		puts(":(");
		return 0;
	}
	if (n == 2) {
		cout << s << endl;
		return 0;
	}
	for (int i = 1; i < n - 1; i++) {
		if (s[i] == '(') ++c1;
		if (s[i] == ')') ++c2;
	}
	if (c1 + 1 > n / 2 || c2 + 1 > n / 2) {
		puts(":(");
		return 0;
	}
	for (int i = 1; i < n - 1; i++) {
		if (s[i] == '?') {
			if (c1 + 1 < (n >> 1)) {
				++c1;
				s[i] = '(';
			} else {
				++c2;
				s[i] = ')';
			}
		}
	}
	int x = 0;
	for (int i = 1; i < n - 1; i++) {
		if (s[i] == '(') x++;
		else {
			x--;
			if (x < 0) {
				puts(":(");
				return 0;
			}
		}
	}
	cout << s << endl;
	return 0;
}
```

---

## 作者：The_jester_from_Lst (赞：0)

简易构造题。

容易想到，对于每一个串，我们尽量把所有左括号往左边堆，右括号往右边堆，这样就能满足严格前缀不是可匹配的括号序列了。如： $((((()))))$ 显然是一个合法的字符串，而 $(((())))()$ 显然不是。

那么我们首先预处理字符串，统计出一开始就填着的左括号，右括号数量（千万不能遍历时统计，否则会导致括号数量被动多出！~~我就这样卡了一小时~~），然后顺序遍历字符串。遍历时，对于每一个字符 $a_i$ 若它不是问号就跳过，否则我们判断，当前已经填着的左括号数量是否小于 $n$ 的一半（因为一个可以匹配的括号序列中左括号数量一定不超过字符串总长度的一半），是就填上左括号，否则填上右括号。最后判断一下这个串是否合法就行了。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define mod 1000000007
using namespace std;
il int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
il void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
il int min(int x,int y){return (x<=y)?x:y;}
il int max(int x,int y){return (x>y)?x:y;}
int n,l,lzuo,lyou;
char a[300086];
il bool manba_out(){
	for(int i=1;i<=n;++i){
		if(a[i]=='(')++l;
		else --l;
		if((i<n&&l==0)||(l<0))return 0;
	}
	return l==0?1:0;
}
namespace man{
	il void what_can_i_say(){
		n=rd();
		if(n%2==1){
			putchar(':');
			putchar('(');
			return ;
		}
		for(int i=1;i<=n;++i){
			cin>>a[i];
			if(a[i]=='(')++lzuo;
			if(a[i]==')')++lyou;
		}
		for(int i=1;i<=n;++i){
			if(a[i]!='?')continue;
			if(lzuo<n/2)a[i]='(',++lzuo;
			else if(lyou<n/2)a[i]=')',++lyou;
		}
		if(manba_out())for(int i=1;i<=n;++i)putchar(a[i]);
		else putchar(':'),putchar('(');
	}
}
signed main(){
	man::what_can_i_say();
    return 0;
}
```

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1153C) & [CF 传送门](//codeforces.com/contest/1153/problem/C)
# 思路
首先，这题中 $n\bmod2=1$ 的情况一定不合法，可以直接特判。要尽量使所有严格前缀都不合法，则只要贪心尽量把剩余需要的 `(` 往前放就行了，把 `)` 往后放就行啦。最后检查一下，如果这样放还是不合法，那只能说明它无解！
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, x, y, tot;
string a;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> a;
	if (n & 1) {
		cout << ":(";
		return 0;
	}
	x = y = n >> 1;
	for (int i = 0; i < n; ++ i)
		if (a[i] == '(')
			-- x;
		else if (a[i] == ')')
			-- y;
	for (int i = 0; i < n; ++ i)
		if (a[i] == '?')
			if (x)
				-- x, a[i] = '(';
			else
				-- y, a[i] = ')';
	for (int i = 0; i < n; ++ i)
		if (a[i] == '(')
			++ tot;
		else if (a[i] == ')')
			if (! tot || ! (-- tot) && i < n - 1) {
				cout << ":(";
				return 0;
			}
	cout << (tot ? ":(" : a);
	return 0;
}
```

---

## 作者：冒泡ioa (赞：0)

> [博客链接](http://bubbleioa.top/archives/820)

## 题解
贪心大水题，然后比赛的时候就被疯狂hack，至少现在下面的策略是能过的。

- 首先n要是偶数才有解
- 最左边是左括号，最右边是右括号（如果是问号直接变成对应的括号）
- 如果有解，肯定是左括号数目=右括号数目的，于是扫一遍字符串计数，当左括号没满足数目上限的时候一直填左括号

就这样~

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int l,r,n;

bool check(){
	int zhan=0;
	for(int i=1;i<=n-2;i++){
		if(s[i]=='(')zhan++;
		else {
			zhan--;
			if(zhan<0)return 0;
		}
	}
	if(zhan==0)return 1;
	return 0;
}

int main(){
	cin>>n;cin>>s;
	if(n%2!=0){
		printf(":(");return 0;
	}
	if(s[0]=='?')s[0]='(';
	if(s[n-1]=='?')s[n-1]=')';
	if(s[0]!='('||s[n-1]!=')'){
		printf(":(");return 0;
	}
	if(n==2){cout<<s<<endl;return 0;}
	for(int i=1;i<n-1;i++){
		if(s[i]=='(')l++;
		if(s[i]==')')r++;
	}
	if(l>=(n>>1)||r>=(n>>1)){
		printf(":(");return 0;
	}
	for(int i=1;i<=n-2;i++){
		if(s[i]=='?'){
			if(l+2<=(n>>1)){l++;s[i]='(';}
			else {r++;s[i]=')';}
		}
	}
	if(check())cout<<s<<endl;
	else printf(":(");
	return 0;
}
```

---

## 作者：StudyingFather (赞：0)

首先，假如字符串的长度是奇数，那么显然是无解的。

在排除这种情况后，有一种贪心的构造方案：将左括号填入尽可能靠左的位置。

原因其实很好想，前缀左括号多了，出现合法括号序列的前缀的机会也就少了（因为你还需要足够的右括号）。

实现的时候注意判断一下有没有右括号比左括号多的前缀，以及构造出来的串左右括号是否相等就可以啦。

```cpp
#include <cstdio>
#include <cstring>
char s[300005];
int main()
{
 int n,cnt1=0,cnt2=0;
 scanf("%d",&n);
 scanf("%s",s);
 if(n%2)
 {
  puts(":(");
  return 0;
 }
 for(int i=0;i<n;i++)
  if(s[i]=='(')cnt1++;
  else if(s[i]==')')cnt2++;
 if(cnt1>n/2||cnt2>n/2)
 {
  puts(":(");
  return 0;
 }
 for(int i=0;i<n;i++)
  if(s[i]=='?')
  {
   if(cnt1<n/2)s[i]='(',cnt1++;
   else s[i]=')',cnt2++;
  }
 cnt1=cnt2=0;
 for(int i=0;i<n;i++)
 {
  if(s[i]=='(')cnt1++;
  else if(s[i]==')')cnt2++;
  if(cnt1==cnt2&&i!=n-1)
  {
   puts(":(");
   return 0;
  }
  if(cnt1<cnt2)
  {
   puts(":(");
   return 0;
  }
 }
 puts(s);
 return 0;
}
```


---

## 作者：xukuan (赞：0)

题目的大意就是就是让你求一个序列，使它是一个匹配的括号序列，而它的每一个前缀（不包括自己和空串）不是

这题我的思路：

1. 输入，存在s中

2. 先统计给出的序列中左右括号的数量差

3. 对每一个问号进行填充，使得左右括号数趋向相等（左括号数>右括号数填‘）’，否则填‘（’），填充的存在ans中

4. 定义指针l=1，r=n，向中间逼近。如果
```
ans[l]==')'&&s[l]=='?'
ans[r]=='('&&s[r]=='?'
```
就交换ans[l],ans[r]。

5. 判断ans是否满足，是则输出，不是就输出':('

注意n==0的特判

代码：

[http://codeforces.com/problemset/submission/1153/52707829](http://codeforces.com/problemset/submission/1153/52707829)

代码说明：

11行是n==0的特判

12行是步骤1

13-17行是步骤2

18-29行是步骤3

31-38行是步骤4

40-52行是步骤5

---

## 作者：hpbl (赞：0)

这真是一道细节题，尽显我们学校那两个出题的毒瘤学长有多毒瘤

我一个0:13切前两题的人1:48才切这道题，算是死在这道题上了

回去跟一起打的老师（和我都掉分了）找学长算账

首先$n$肯定是偶数

然后首尾肯定是(和)

接下来我们把(看作1，把)看作-1，并用其组成数组$a$

我们可以先把连续的?分成一段，右端点为$p_i$

前缀和为s

那么我们的问题其实就是使得$[s_i>0]=[i \not = n]$

那么$s_{p_i} - s_{p_j} \le \sum_{j < k \le i}a_{p_k} + p_i - p_j - i + j$

又由于$s_{p_i} \ge 1$

因此$s_{p_j} \ge 1 + i - j - p_i + p_j + \sum_{j < k \le i}a_{p_k}$

所以我们就知道了每一段右端点前缀和的最小值。

然后可以得出一个贪心策略：依次处理每一段，若当前前缀和小于要求的前缀和，那么先用(填充到要求的前缀和为止；若大于，则填)；然后成对填()，如果有剩的填(

如果有一次空位不够用了就说明不行

COde:
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,tp,p[300001],nd[300001],sum[300001],cnt,nw,np;
char c[300001];
int main()
{
    scanf("%d",&n);
    if(n&1)
    {
        puts(":(");
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        scanf(" %c",&c[i]);
        if(i==n&&c[i]=='(')
        {
            puts(":(");
            return 0;
        }
        if(i==n) c[i]=')';
        if(c[i]=='(') nw++;
        if(c[i]==')') nw--;
        if(!nw&&!tp&&c[i]!='?')
        {
            if(i==n) printf("%s",c+1);
            else puts(":(");
            return 0;
        }
        if(c[i]!='?')
        {
            p[++tp]=i;
            sum[tp]=sum[tp-1];
            if(c[i]=='(') sum[tp]++;
            else sum[tp]--;
        }
    }
    nw=0;
    for(int i=tp;i;i--)
    {
        if(i==tp);
        else if(c[p[i]]=='(') cnt++;
        else if(c[p[i]]=')') cnt--;
        if(cnt>0) cnt=0;
        nd[i]=(p[i]>1?1:0)-cnt;
        cnt+=p[i]-p[i-1]-1;
        if(cnt>0) cnt=0;
    }
    for(int i=1;i<=tp;i++)
    {
        int t=p[i]-p[i-1]-1;
        if(nw<nd[i])
        {
            if(nd[i]-nw>t)
            {
                puts(":(");
                return 0;
            }
            else
            {
                for(int j=1;nd[i]>nw;j++)
                {
                    c[++np]='(';
                    t--;
                    nw++;
                }
            }
        }
        else
        {
            for(;t&&nw>nd[i];)
            {
                c[++np]=')';
                t--;
                nw--;
            }
        }
        for(int j=t/2;j;j--)
        {
            c[++np]='(';
            c[++np]=')';
        }
        if(t&1)
        {
            c[++np]='(';
            nw++;
        }
        if(c[p[i]]=='(') nw++;
        else nw--;
        np++;
    }
    if(nw) puts(":(");
    else printf("%s",c+1);
}
```


---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF1153C)

若 $n$ 为奇数，不可能（没有半个括号）。

将整个字符串第 $\frac{n}{2}$ 位到第 $n$ 位中的 ``?`` 用 ``)`` 替换，其余用 ``(`` 替换。

相当于这样：

``???()?))`` 变成了 ``(((())))``。

再搜索一遍，判断是否合法。

AC Code：

```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define itn int
#define tni int
#define tin int
#define nit int
#define nti int
#define int long long
using namespace std;
int n,ans,sum;
string a;
void Enchanted() {
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>a;
	if(n%2==1) {
		cout<<":(";//无解
		exit(0);
	}
	for(int i=0;i<n;++i)
	if(a[i]==')')++sum;
	for(int i=n-1; i>=0; --i)
		if(a[i]=='?')
			if(sum<n/2)a[i]=')',++sum;
			else a[i]='(';//替换
	for(int i=0; i<n; ++i) {
		if(a[i]=='(')++ans;
		else --ans;//判断
		if((i!=n-1&&ans==0)||ans<0) {
			cout<<":(";
			exit(0);
		}
	}
	if(!ans)cout<<a;
	else cout<<":(";//输出
}
signed main() {
	Enchanted();
}


```



---

