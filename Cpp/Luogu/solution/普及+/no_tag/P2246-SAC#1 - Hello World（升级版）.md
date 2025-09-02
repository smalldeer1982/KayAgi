# SAC#1 - Hello World（升级版）

## 题目背景

一天，智障的 pipapi 正在看某辣鸡讲义学程序设计。

## 题目描述

在讲义的某一面，他看见了一篇文章。这篇文章由英文字母（大小写均有）、数字、和空白字符（制表/空格/回车）构成。

pipapi 想起了他最近刚刚学会写的 `Hello World` 程序。他非常好奇，这篇文章中，`Hello World` 作为子序列到底出现过多少次呢？（**忽略大小写和空格**）

两个子序列相同当且仅当它们每一个字符所在的位置都相同。


由于答案可能很大，请输出答案对 ${10}^9+7$ 取模的余数。

## 说明/提示

记 $n$ 为输入的文章的长度（字符数）。

对于 $20\%$ 的数据，$n \le 20$。

对于 $50\%$ 的数据，$n \le 500$。

对于所有的数据，$15 \le n \le 500000$。

## 样例 #1

### 输入

```
HhEeLlLlOoWwOoRrLlDd```

### 输出

```
1536```

## 样例 #2

### 输入

```
Gou Li Guo Jia Sheng Si Yi
Qi Yin Huo Fu Bi Qu Zhi
River can feed people
Also can race boats
Hall Ellen Ok Words locked ```

### 输出

```
273```

# 题解

## 作者：Mr_QwQ (赞：17)

啊啊啊，终于AC了……心好累……

这题很明显是DP，因为它满足DP的两个性质——最优子结构、无后效性。（不知道这些的请回去看看DP吧）（划掉）

状态很明显：考虑文本串前i个字符匹配模板前j个字符的匹配数。

转移也很明显：当第i个字符是文本中的第j个，dp[i][j]=dp[i-1][j]+dp[i-1][j-1]，其他dp[i][j]=dp[i-1][j]（因为这个字符对于匹配没有用嘛）

现在只差一个：边界。

//众：我倒！！！

边界是什么呢？我们知道dp[0][i]=0，但dp[i][0]是几呢？在文本中匹配一个空串？晕。。。

看看样例吧：

HhEeLlLlOoWwOoRrLlDd

现在，我们在文本前加一个奇gay的字符，比如♂【滑稽】

那么文本就变成了：

♂HhEeLlLlOoWwOoRrLlDd

让我们把♂看成模板（即“helloworld”）的第0个字符。这个时候，边界明显了吧。。。

还有一个细节：模板中有重复字符，因此要逆序循环，不然会WA（考虑一下“hhhhhhh”这个模板就明白了）

代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int mod=1000000007;
int main()
{
    long long dp[11]={1};
    char c,hello[20]="?helloworld";
    while((c=getchar())!=EOF)
    {
        for(int i=10;i>=1;i--)if(c==hello[i]||c+32==hello[i])dp[i]=(dp[i-1]+dp[i])%mod;
    }
    cout<<dp[10];
    return 0;
}
```

---

## 作者：BFSBFSBFSBFS (赞：10)

~~还是这样更暴力.~~.

题意.求**helloworld**的子序列的个数..

用**b[1] - b[10]**分别存储**h**,**he**,**hel**....**helloworl**,**helloworld**的个数.

如果这个位置上的字母出现了.对应的**b[i] += b[i-1]**.

这个很好想吧..

接近**O(n)**的效率.

Diu代码.

```cpp
program P2246;
 var
  b:array[1..10] of int64;
  i,mot:longint;
  s,c:ansistring;
 begin
  filldword(b,length(b),0);
  s:='';
  while not seekeof do
   begin
    readln(c);
    s:=s+c;
   end;
  s:=lowercase(s);
  mot:=1000000007;
  for i:=1 to length(s) do
   case s[i] of
    'h':b[1]:=(b[1]+1) mod mot;
    'e':b[2]:=(b[2]+b[1]) mod mot;
    'l':
     begin
      b[4]:=(b[4]+b[3]) mod mot;
      b[9]:=(b[9]+b[8]) mod mot;
      b[3]:=(b[3]+b[2]) mod mot;
     end;
    'o':
     begin
      b[7]:=(b[7]+b[6]) mod mot;
      b[5]:=(b[5]+b[4]) mod mot;
     end;
    'w':b[6]:=(b[6]+b[5]) mod mot;
    'r':b[8]:=(b[8]+b[7]) mod mot;
    'd':b[10]:=(b[10]+b[9]) mod mot;
   end;
  writeln(b[10]);
 end.
```
(ಡωಡ).


---

## 作者：老官童鞋gogo (赞：4)

## [传送门](https://www.luogu.com.cn/problem/P2246)

## 题目理解与强调

精简一下题意：本题给出一个字符串，在无视非字母、字母大小写的情况下，字符串 `helloword` 出现的次数。

## 题解

### 读入问题

在无其他问题的情况下，依然过不了，可以尝试我这一套读入程序。

```cpp
char c;
while((c=getchar())!=EOF){
}
```

### 解决主体问题

问题很简单，从第一个数字枚举整个字符串，先除去非字母并把统一字母大小写。使用 $ans_i$ 分别存储子序列 `h` 、 `he` 、 `hel` $\cdots$ `helloworld` 的出现次数，那么最终答案就是 $ans_{10}$。

在我们枚举序列的时候，遇到了所对应的字母，就更改以这个字符结尾的字符串出现的次数，例如，当前枚举到的字符为 `r` 以 `r` 结尾的字符串只有 `hellowor` 这一个，这个字符串出现的次数储存在 $ans_8$ 中，那么 $ans_8$ 更改为 $ans_8+ans_7$，为什么？当我们每匹配到一个字符，那么这个字符会和前面所有的已经匹配的 `o` 匹配，所以多一个匹配的字符，结果不一定只加上 $1$。

另一个问题，例如字符 `l`，它在目标字符串中出现了多次，而一个字母不可以同时使用两次，应该如何确定它的位置？解决这个问题，我们需要限制修改 $ans$ 的顺序，$ans$ 应该从**大下标修改到小下标**，这样可以避免「后效性」。

注意**取模**！

## 参考代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define inf 1000000000
using namespace Fast;//内含快读快输函数，详见文章「代码模板」
char c;
long long ans[11];
int main(){
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
	while((c=getchar())!=EOF){
		if(!((c>='A'&&c<='Z')||(c>='a'&&c<='z')))
			continue;
		c=tolower(c);
		if(c=='h')
			ans[1]++;
		if(c=='e')
			ans[2]+=ans[1];
		if(c=='l'){
			ans[9]+=ans[8];
			ans[4]+=ans[3];
			ans[3]+=ans[2];
		}
		if(c=='o'){
			ans[7]+=ans[6];
			ans[5]+=ans[4];
		}
		if(c=='w')
			ans[6]+=ans[5];
		if(c=='r')
			ans[8]+=ans[7];
		if(c=='d')
			ans[10]+=ans[9];
		for(int j=1;j<=10;j++)
			ans[j]%=inf+7;
	}
	print(ans[10]);
    return 0;
}

```

---

## 作者：Rumia (赞：4)

一维滚动DP

思路和前面那位基本一样，但是如果把转移方程稍加改动——即将其从离线做改到在线做。那么就可以简化一个维度，实质上这是改成了滚动数组。

代码：

```cpp
#include<iostream>
#include<cstring>
#define maxn 1000000007
using namespace std;
char a[500005],b[12]="-helloworld";
long long f[12],n=0;
int main(){
    while(cin>>a[++n]){
        if(a[n]>='A'&&a[n]<='Z') a[n]=a[n]-'A'+'a';
        if(a[n]=='h') f[1]++;
        for(int j=10;j>=2;j--)
            if(a[n]==b[j]) f[j]=(f[j]+f[j-1])%maxn;
    }
    cout<<f[10]%maxn;
    return 0;
}
```cpp

---

## 作者：Lynx (赞：3)

设f[i][j]表示，原字符串匹配到i，helloworld匹配到j的方案数 。

首先f[i][j]=f[i-1][j];

其次如果s[i]==t[j]，就可以转移，f[i][j]+=f[i-1][j-1];

初始化f[i][0]=1(0=<i<=l)

读入用string类型会十分方便。


```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
using namespace std;
const int N=500005;
const int mod=1000000007;
int l,f[N][15];//s匹配到i，t匹配到j的方案数 
string s,t;
int main()
{
    s="*";
    while(cin>>t)//读入 
        s+=t;
    t="*HELLOWORLD";
    l=s.length()-1;
    for(int i=1;i<=l;i++)//转换为小写 
        if(s[i]>='a')
            s[i]-=32;
    for(int i=0;i<=l;i++)
        f[i][0]=1;
    for(int i=1;i<=l;i++)
        for(int j=1;j<=10;j++)
        {
            f[i][j]=f[i-1][j];
            if(s[i]==t[j])
                f[i][j]+=f[i-1][j-1],f[i][j]%=mod;
        }
    printf("%d\n",f[l][10]);
    return 0;
}
```

---

## 作者：xh001 (赞：3)

# 题意
给定一个字符串，求有多少形如 $\verb.HelloWorld.$ 的子序列。
# 思路
由于子序列不要求连续，所以用 $f_i$ 表示在 $\verb.HelloWorld.$ 中的第 $i$ 位字母出现的次数。

当该字母只有一个时：$i$ 为该字母在 $\verb.HelloWorld.$ 中的第 $i$ 位，状态转移方程：$f_i=f_i+f_{i-1}$。

当该字母有多个时：每个 $i$ 为该字母在 $\verb.HelloWorld.$ 中的第 $i$ 位，状态转移方程：每个 $f_i=f_i+f_{i-1}$。

例如：当 $a$ 为字母 $o$ 时：

`f[5]+=f[4];`

`f[7]+=f[6];`
# 注意事项
详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//习惯性不开long long见祖宗。
const ll mod=1e9+7;//模数。
char a;
ll f[11]={1};//初始化，注意数组下标从0开始。
int main()
{
	while(a=getchar()!=EOF)
	{
		if(a>='A' && a<='Z') a+=32;
		if(a=='h')
		{
			f[1]+=f[0]; 
		}
		else if(a=='e')
		{
			f[2]+=f[1];
		}
		else if(a=='l')
		{
			f[4]+=f[3];
			f[3]+=f[2];
			/*
			注意！！不能写成
			先f[3]+=f[2];
			后f[4]+=f[3];
			先改f[3]的值会导致答案暴增一倍左右（亲身经历）。
			*/ 
			f[9]+=f[8];
		}
		else if(a=='o')
		{
			f[5]+=f[4];
			f[7]+=f[6];
		}
		else if(a=='w')
		{
			f[6]+=f[5];
		}
		else if(a=='r')
		{
			f[8]+=f[7];
		}
		else if(a=='d')
		{
			f[10]+=f[9];
		}
		for(ll i=1;i<=10;i++)//取模。
		{
			f[i]%=mod;
		}
	}
	cout<<f[10];
	return 0;
}
```


---

## 作者：littleqwq (赞：2)

# P2246 SAC#1 - Hello World（升级版）题解

### 大致意思：

就是在一串字母中找出 ```HelloWorld``` 子序列出现的次数。

### 大致思路：

- 暴力，跟据每个字母的位置及相同字母的位置，进行枚举和判断，时间 $O (n)$。

- 动态规划，因为题目提供的模板串长度比较小，所以我们可以将它存入数组，一位一位枚举。而我们知道因为是子序列，前面的情况也要包含进去，所以第 $i$ 项需要加上 $i - 1$ 项，因此得出公式 $dp_{i} = dp_{i} + dp_{i - 1}$，时间复杂度依然为 $O (n)$。

这道题我选择了第二种方法来做。

### 代码实现：

```
#include<bits/stdc++.h>
using namespace std;
int dp[20];
char s,c[20]={"helloworld"};
const long long mod=1000000007;
int main(){
    dp[0]=1;
	while(1){
		s=getchar();
		if(s==EOF){
			cout<<dp[10]<<endl;
			return 0;
		}
		char k=s+32;
		for(int i=9;i>=0;i--){
			if(k==c[i]||s==c[i]){
				dp[i+1]=(dp[i]+dp[i+1])%mod;
			}
		}
	}
	return 0;
}
```

这样这道题就完成啦！！！

---

## 作者：郑朝曦zzx (赞：2)

# 一 题意简述
在一个字符串中，忽略大小写，空格有多少个 "hello world" 的**子序列**。

**注意：是子序列不是子串，即字符可以不相连。**

# 二 思路描述

## 方法一
枚举文本串并且判断是否能接上，更新 $dp$ 的值。

时间复杂度：$O(n^2)$

期望得分：$50pts$

## 方法二
观察到本题一个性质：**模板串很短**，于是我们可以考虑枚举模板串。

令 $dp_i$ 为匹配上模板串前 $i$ 位的方案数。

枚举模板串，并且转移状态：

$dp_i = (dp_i + dp_{i-1}) \pmod{10^9+7}$

时间复杂度：$O(n)$

期望得分：$100pts$

**注意：由于模板串中有重复字母，所以要倒着枚举！**

# 三 代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
char Std[] = "@helloworld", ch;
int dp[15];
const int mod = 1e9 + 7;
int main()
{
	dp[0] = 1;
	while (cin >> ch)
	{
		for (int i = 10; i >= 1; --i)
			if (ch == Std[i] || ch - 'A' + 'a' == Std[i])
				dp[i] = (dp[i] + dp[i - 1]) % mod;
	}
	printf("%d", dp[10]); 
	return 0;
}
```


---

## 作者：int_250 (赞：2)

灰常暴力的代码
看不懂楼上大神写的DP（膜拜大神QwQ）

姑且打个递推吧！

用helloworld[1]~[10]表示h,he,hel,hell......helloworl,helloworld

仔细思考一下题目
可以得到递推式helloworld[i]=helloworld[i-1]

由于helloworld有重复字母'l''o'所以要有几个特殊判断

只有前面出现过这个字母
才能加上

详细请看代码


```cpp
#include<bits/stdc++.h>
using namespace std;
long long helloworld[13];//范围太大，用长整形 
char Char;
int main() {

	while((Char=getchar())!=EOF) {//节省时间，复杂度为 O(n)左右 
		if(Char=='H'||Char=='h')helloworld[1]++,helloworld[1]%=1000000007;//递推式 
		if(Char=='E'||Char=='e')helloworld[2]+=helloworld[1],helloworld[2]%=1000000007;
		if(Char=='L'||Char=='l') {//特殊判断 
			if(helloworld[4]>=1)helloworld[9]+=helloworld[8],helloworld[9]%=1000000007;//只有前面出现过这个字母才能加上 
			if(helloworld[3]>=1)helloworld[4]+=helloworld[3],helloworld[4]%=1000000007; 
			helloworld[3]+=helloworld[2],helloworld[3]%=1000000007;
		}
		if(Char=='O'||Char=='o') {//特殊判断 
			if(helloworld[5]>=1)helloworld[7]+=helloworld[6],helloworld[7]%=1000000007;
			helloworld[5]+=helloworld[4],helloworld[5]%=1000000007;
		}
		if(Char=='W'||Char=='w')helloworld[6]+=helloworld[5],helloworld[6]%=1000000007;
		if(Char=='R'||Char=='r')helloworld[8]+=helloworld[7],helloworld[8]%=1000000007;
		if(Char=='D'||Char=='d')helloworld[10]+=helloworld[9],helloworld[10]%=1000000007;
	}

	cout<<helloworld[10];
	return 0;
	//代码结尾 
}
```

---

## 作者：_Violet_Evergarden (赞：2)

# 简要题意
求一个序列中      $\verb!HelloWorld!$ 出现的次数，但不区分大小写。
# 警示后人

1：要对 $10^9+7$ 进行取模。

2：注意到序列中有重复的字母，所以要从后往前遍历。

3：输入完记得判断是否为 `EOF`。
# 思路
定义 dp 数组为现字符对应位置可对构造 $\verb!HelloWorld!$ 的贡献值，即这个字母可用于构造几个 $\verb!HelloWorld!$ 的前缀。

例如： $\verb|l|$ 在 $\verb!HelloWorld!$ 序列中排在第 $3, 4$ 和 $9$ 的位置。


所以此时的转移方程便是： 

`f[9]+=f[8];`

`f[4]+=f[3];`

`f[3]+=f[2];`





据此易得转移方程式：$dp_i=dp_{i-1}+dp_i$。

此处附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
long long dp[11];
char n;
//HelloWorld
int main()
{
	dp[0]=1;
	while(1){
		n=getchar();
		if(n==EOF){
			break;
		}
        //注意要从后往前遍历
		if(n>'Z'&&n<='z'){
			n-=32;
		}
		if(n=='D'){
			dp[10]+=dp[9];
		}
		if(n=='L'){
			dp[9]+=dp[8];
			dp[4]+=dp[3];
			dp[3]+=dp[2];
		}
		if(n=='R'){
			dp[8]+=dp[7];
		}
		if(n=='O'){
			dp[7]+=dp[6];
			dp[5]+=dp[4];
		}
		if(n=='W'){
			dp[6]+=dp[5];
		}
		if(n=='H'){
			dp[1]+=dp[0];
		}
		if(n=='E'){
			dp[2]+=dp[1];
		}
		for(int i=1;i<=10;i++){
			dp[i]%=mod;
		}
	}
	cout<<dp[10]<<endl;
	return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

考虑 dp。  
设状态 $f_i$ 为 `helloworld` 字符串中组成前 $i$ 个字符的方案数。

于是可以对于每个输入的字符，找到它在 `helloworld` 中的位置，进行方案累加。  
需要注意的是为了满足 dp 的无后效性，需要倒序累加方案。

```cpp
int dp[101];
const int mod = 1e9+7;
signed main() {
	dp[0] = 1;
	string s;
	while (cin >> s) {
		for (auto&i : s) {
			if (i <= 'Z') i += 32;
			if (i == 'h') dp[1] ++;
			else if (i == 'e') (dp[2] += dp[1]) %= mod;
			else if (i == 'l') {
				(dp[9] += dp[8]) %= mod;
				(dp[4] += dp[3]) %= mod;
				(dp[3] += dp[2]) %= mod;
			} else if (i == 'o') {
				(dp[5] += dp[4]) %= mod;
				(dp[7] += dp[6]) %= mod;
			} else if (i == 'w') (dp[6] += dp[5]) %= mod;
			else if (i == 'r') (dp[8] += dp[7]) %= mod;
			else if (i == 'd') (dp[10] += dp[9]) %= mod;
		}
	}
	cout << dp[10] << '\n';
	return 0;
}
```

---

## 作者：Light_az (赞：1)

这题脑子不好，$i$ 和 $j$ 写反了调了半天，其实这就是一道经典字符串的 DP 问题，首先推一下式子：和最长公共子序列有点相似，$dp[i][j]$ 表示文章第 $i$ 位在子序列第 $j$ 位的最优解，如果文章 $s[i]$ 等于子序列 $s1[j]$，$dp[i][j]=dp[i-1][j-1]$，否则 $dp[i][j]$ 是文章 $s[i-1]$ 的最优解也就是 $dp[i-1][j]$，当然，肯定是有数组边界的，$dp[i][0]$ 全部赋值为 $1$，因为我们需要它来累加。注意，为了方便文章 $s$ 我一开始多定义了空格，因此下标从 $1$ 开始，还有最好将字符全部转换成小写，方便统计。下面是完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e7+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,ans=0,t=0,l,r,len,T;
ll mini=INT_MAX,maxi=0;
string s=" ",s1,s2=" helloworld";
ll dp[N][15],a[N];
ll Mod=1e9+7; 
int main(){
	while(cin>>s1){
		s+=s1;
	}
	len=s.size()-1;
	for(int i=1;i<=len;i++){
		s[i]=tolower(s[i]);
	}
	for(int i=0;i<=len;i++){
		dp[i][0]=1;
	}
	for(int i=1;i<=len;i++){
		for(int j=1;j<=10;j++){
			dp[i][j]=dp[i-1][j];
			if(s[i]==s2[j]){
				dp[i][j]+=dp[i-1][j-1]; 
			}
			dp[i][j]%=Mod;
		}
	}
	cout<<dp[len][10]%Mod;
	return 0;
}

```


---

## 作者：MrMorning (赞：1)

这个题是一个典型的字符串dp，根据经验，我们定义f[i][j]为a字符串前i位匹配b字符串前j位，这样，我们写出状态转移方程：

f[i][j] = f[i-1][j] + f[i-1][j-1] (a[i]==b[j)

f[i][j] = f[i-1][j] (a[i] != b[j])

边界条件就是，如果a串中第x位是b[0], 那么我们令f[x][0] = 1;

下面上ac代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 500005;
const int p = 1e9+7; 
int f[2][maxn];
char s[maxn];
int pre, now = 1;
int main() {
    freopen("input.in", "r", stdin);
    char x; 
    set<int> h;
    int num = 0;
    memset(f, 0, sizeof(f));
    while((x = getchar())!=EOF) {        //输入及预处理 
        if(x!=' ' && x!='\n')s[num++] = x;
        if(isalpha(x)) s[num-1] = tolower(x);
        if(s[num-1]=='h') h.insert(num-1);
        
    }
    int len = strlen(s);
    char b[maxn] = "helloworld";
    for(int i = 0; i < len; i++) {
        swap(pre, now);
        if(h.count(i)) f[pre][0] = (f[pre][0] % p + 1) % p;
//        memset(f[now], 0, sizeof(f[now]));
        for(int j = 0; j < 10; j++) {
            if(s[i] == b[j]) f[now][j] = (f[pre][j] % p + f[pre][j-1] % p) % p;
            else f[now][j] = f[pre][j];
        }
    } 
    cout << f[now][9];
    return 0;
}
```
开始因为每次都把now数组清零，所以后五个点tle；

后来发现没有必要去清零。


---

## 作者：Daidly (赞：1)

1.关于次数的dp。

2.发现每个位置的性质除了在此处出现过多少次$hello world$外，还有其在新的$hello world$中可能的位置。

3.设$g[i][j]$为以i为终点，构成$helloworld$的前j位的方案数 例如在字符串$helloworld$中，$g[3][2]=2$。

4.于是发现$g[i][j]$和$sum[j-1]$， 
使用前缀和维护，用$sum[j-1]$更新$g[i][j]$，用$g[i][j]$更新$sum[j]$; $f[i]$表示当前位出现过多少完整的$helloworld$。

5.发现$f[i]$仅能由$g[i][10]$更新，即出现新的以$i$结尾的构成前10位（全串）的方案数，对答案贡献为$g[i][10]$。
```
 #include<bits/stdc++.h>//万能头
 using namespace std;
 const int mod=1e9+7;
 const int mxn=100010;
 char c[20]="helloworld";//定义数组
 int f[13];//定义数组
 char s[500010];//定义数组
 int main(){
     f[0]=1;
     int len;
    while(scanf("%s",s+1)!=EOF){//用while循环输入
         len=strlen(s+1);
         for(int i=1;i<=len;i++){
             char ch=tolower(s[i]);
             for(int j=10;j;j--){
                 if(c[j]==ch){
                     (f[j]+=f[j-1])%=mod;//取余
                 }
             }
         }
     }
     printf("%d\n",f[10]%mod);//输出
     return 0;//代码结尾 
 }
```

---

