# Game with String

## 题目描述

Vasya and Kolya play a game with a string, using the following rules. Initially, Kolya creates a string $ s $ , consisting of small English letters, and uniformly at random chooses an integer $ k $ from a segment $ [0,len(s)-1] $ . He tells Vasya this string $ s $ , and then shifts it $ k $ letters to the left, i. e. creates a new string $ t=s_{k+1}s_{k+2}...\ s_{n}s_{1}s_{2}...\ s_{k} $ . Vasya does not know the integer $ k $ nor the string $ t $ , but he wants to guess the integer $ k $ . To do this, he asks Kolya to tell him the first letter of the new string, and then, after he sees it, open one more letter on some position, which Vasya can choose.

Vasya understands, that he can't guarantee that he will win, but he wants to know the probability of winning, if he plays optimally. He wants you to compute this probability.

Note that Vasya wants to know the value of $ k $ uniquely, it means, that if there are at least two cyclic shifts of $ s $ that fit the information Vasya knowns, Vasya loses. Of course, at any moment of the game Vasya wants to maximize the probability of his win.

## 说明/提示

In the first example Vasya can always open the second letter after opening the first letter, and the cyclic shift is always determined uniquely.

In the second example if the first opened letter of $ t $ is "t" or "c", then Vasya can't guess the shift by opening only one other letter. On the other hand, if the first letter is "i" or "a", then he can open the fourth letter and determine the shift uniquely.

## 样例 #1

### 输入

```
technocup
```

### 输出

```
1.000000000000000
```

## 样例 #2

### 输入

```
tictictactac
```

### 输出

```
0.333333333333333
```

## 样例 #3

### 输入

```
bbaabaabbb
```

### 输出

```
0.100000000000000
```

# 题解

## 作者：DPair (赞：4)

题解连更计划第4篇

## 【前言】
比较有趣的一道题，但是$CF$不能用$long~double$，害的我错了两次。

## 【性质】
这道题还是不错的，但难度不算太大。

首先我们思考一下怎样才能必定猜对。

举个例子，下面有三个数：

$$101, 202, 303$$

给你一个数的百位，让你猜这个数是三个数中的哪一个？

是不是直接看$1$对应$101$，$2$对应$202$，$3$对应$303$就好了？

所以这道题我们也是要找到一个对应关系，使得**第$1$位是字母$A$（~~这是个变量~~）的所有串中第$p$位**（就你猜的那一位）**是字母$B$（~~这也是个变量~~）的有且仅有一个**

只要满足上面一个条件，就可以猜得出来。

## 【分析】
题目其实是问我们，对于每一个不同的字符串，采取怎样的策略可以使得**必定猜对**的概率最大。

先看样例。

样例是从首字母方向去考虑的，好，我们也去思考首字母。

可以发现，如果我们把首字母相同的所有字符串归为一类，显然**各类之间互不干扰**。

那就舒服了，直接对着首字母一通乱打。

于是我们就要思考对于一个特定的首字母，选哪一位查看胜率最大。

## 【注意】
这道题有一个重要信息：

**只要现有信息下，你不能必定猜中，则默认为你一定猜不中**。

举个例子，对于$aaab$与$aaba$，如果你选择猜$1,2$两位（虽然这显然不是最优解），那么你被默认为永远猜不对，而不是$50$%的概率猜对。

## 【思路】
然后开始最后一步。

我们对于每一个首字母，要想**必定猜对**，假设我们要去查看第$p$位，那么，只要某个字符串中的第$p$位于另一个字符串的第$p$位相同，那你就猜不出来了。

换句话说，我们要使必定猜出来的可能性最大，就要使第$p$位上**出现且仅出现一次的不同字母数最多**。

数据范围看一下，$O(n^2)$可以过，常数大都没关系。

那就对于每个字母，记录它出现的所有位置，以此遍历往后$p$位的所有可能性，复杂度$O(n^2)$，可以通过本题。

## 【代码】
还没看懂的，或者有些细节没想到的可以来看看代码，或者发一发讨论哟。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long double LD;

int len;

string a;
vector <int> pos[26];

LD base[26], ans;

int calc(int x, int d)
{
	int ret = 0;
	int b[26];
	memset(b, 0, sizeof(b));
	for (register int i = 0;i < pos[x].size();i ++)
	{
		int cur = a[pos[x][i] + d] - 'a';
		b[cur] ++;
	}
	for (register int i = 0;i < 26;i ++) ret += (b[i] == 1);
	return ret;
}

void work(int x)
{
	int cnt = -1;
	for (register int i = 1;i < len;i ++)
	{
		cnt = max(cnt, calc(x, i));
	}
	LD tmp1 = cnt * 1.0, tmp2 = (LD)pos[x].size() * 1.0;
	ans = ans + ((tmp1 / tmp2) * base[x]);
}

int main()
{
	cin >> a;
	len = a.size();
	if(a[len - 1] == '\n')
	{
		len --;
		a[len] = '\0';
	}
	for (register int i = 0;i < len;i ++)
	{
		pos[a[i] - 'a'].push_back(i);
		base[a[i] - 'a'] ++;
	}
	for (register int i = 0;i < 26;i ++) base[i] = base[i] / (LD)(len * 1.0);
	a = a + a;
	for (register int i = 0;i < 26;i ++)
	{
		if(base[i] != 0.0) work(i);
	}
	double FrameTQL = ans;
	printf("%.12lf\n", FrameTQL);
} 
```


---

## 作者：anonymous_Y (赞：1)

感觉思维难度没有很大但是很考验我的代码能力啊。

其实转化一下题意就可以知道，这个串如果是可以确认的，那么实际上就是在操作过后 $a_0$ 与 $a_p$ 这对组合是在所有字符串里面唯一的。举个例子

```cpp
aaaacaaaa
```
在这个串中，$a_0$ 和 $a_4$ 即 $ac$ 组成的这个组合是所有 $a_i$ 和 $a_{i+4}$ 组合里唯一的，所以我们可以确定这个字符串。

那么文中说的“最优”实际就是找到一个 $p$,使 $a_i$ 和 $a_{i+p}$ 重复的对数最少。

所以这时候我们需要进行分类，将相同的 $a_i$ 分在一组，去枚举一个 $p$ ,使得 $a_{i+p}$ 的重复数最少。

如果设 $base_x$ 代表字符 $x$ 的数量，$t1$ 是字符 $x$ 开头，互不相同的最优组合数，那么答案就应该是

$\displaystyle \sum_{i=0}^ {26}{\frac{t1\cdot base_i\cdot base_i} {len} }$

这样子就完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
vector<int> p[26];
int b[30];
long double base[maxn];
char ch[maxn];
int n;
long double ansa;
int sol(int x,int d){
	int ans=0;memset(b,0,sizeof(b));
	for(int i=0;i<p[x].size();i++){
		int cur=ch[p[x][i]+d]-'a';
		b[cur]++;
	}
	for(int i=0;i<26;i++) if(b[i]==1) ans++;
	//cout<<ans<<endl;
	return ans;
}
void work(int x){
	//if(!p[x].size()) return double(0);
	int ans=0;
	for(int i=1;i<n;i++) ans=max(ans,sol(x,i));
	long double tm1=ans*1.0,tm2=(long double)p[x].size()*1.0;
	//cout<<tm1/tm2*base[x]<<endl;
	ansa=ansa+((tm1/tm2)*base[x]);
	//cout<<"a"<<ansa<<endl;
}
int main(){
	cin>>ch;
	n=strlen(ch);
	for(int i=0;i<n;i++) p[ch[i]-'a'].push_back(i),base[ch[i]-'a']++;
	for(int i=0;i<n;i++) ch[i+n]=ch[i];
	for(int i=0;i<26;i++) base[i]=base[i]/(long double)(n*1.0);
	for(int i=0;i<26;i++) if(base[i]!=0.0)work(i);
	double aaa=ansa;
	printf("%.12lf\n", aaa);
	return 0;
}
```
完结撒花！

---

## 作者：极寒神冰 (赞：1)

考虑所有可能成为$t$开头的字母$c_1$.然后再考虑所有询问的第二个可能字母数量$d$.如果一对字母$(c_1,c_2)$仅在$d$距离出现一次，之后若$c_2$第二次出现，便可以确定$k$

我们可以遍历所有$c_1$字母开始,距离为$d$的所有字母，对于每个$c_2$,我们可以计算此类字母的数量.

这可以做到在$O(cnt(c_1))$,$cnt(c_1)$表示初始字符串中$c_1$出现次数,即存储每个$c_1$出现位置.

考虑在确定了$c_1$后暴力枚举$d$，并在每个$d$中找的独一无二的一对$(c_1,c_2)$，记最大数量为$p$，在固定$c_1$的条件下获胜概率为$\frac{p}{cnt(c_1)}$

答案为:

$$\sum \frac{p}{cnt(c_1)} \times \frac{cnt(c_1)}{n}=\frac{\sum p}{n}$$



---

## 作者：KυρωVixen (赞：0)

## CF930B 题解

闲扯一句，建议本题评绿，有点麻烦和考查概率论的字符串模拟题，但是绝对不至于蓝。

### 题面翻译

小 A、小 B 正在玩一个猜字符串游戏。

这个游戏的规则是这样的：给定一个两人都预先知道的字符串 $S$，小 A 先让 $S$ 随机“逆时针旋转”（将最后一个字符插入到字符串首）$0\sim\lvert S\rvert-1$ 次，变为字符串 $T$。随后小 B 可以查看 $T$ 的首字母，之后他可以选择一个 $i$ 并检查  $T_i$ 以唯一确定 $T$。如果他没法确定，他就输了。

求小 B 在最优行动下获胜的概率。 

保证 $\lvert S\rvert\le5000$。
### 解法
我们考虑枚举旋转的次数，处理出这些字符串并按照首字母分类，然后对于每种首字母算出对答案的贡献。

也就是说对每一种字母开头的字符串，找到一个 $i$ 使得在这些串中翻开第 $i$ 位能唯一确定的字符串最多。按照题意，这就是最优对策。

具体实现可以对每一个首字母的每一个 $i$ 扫一遍并开桶统计一下各个字母的出现次数，看看有多少出现正好一次的，统计并取最大值，然后对答案做贡献。

设 $n=\lvert S\rvert$，那么时间复杂度为 $O(n^2)$，可以轻松通过。

### 代码
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define endl '\n'
using namespace std;
int n;
double pos=0;
string s;
vector<string>v[27];
double calc(int st){
    if(v[st].empty()) return 0;
    int cnt[26],ans=-1; 
    rep(i,1,n-1){
        int tmp=0;
        memset(cnt,0,sizeof(cnt));
        rep(j,1,v[st].size()){
            cnt[v[st][j-1][i]-'a']++;
        }
        rep(i,0,25) tmp+=cnt[i]==1;
        ans=max(ans,tmp);
    }
    return 1.0*ans/n;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>s; n=s.length();
    rep(i,0,n-1){
        string s1=s.substr(i)+s.substr(0,i);
        v[s1[0]-'a'].push_back(s1);
    }
    rep(i,0,25) pos+=calc(i);
    cout<<pos<<endl;
}
```

---

