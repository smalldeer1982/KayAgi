# 「GFOI Round 2」Abstract String Basic

## 题目背景

**[English statement](https://www.luogu.com.cn/problem/T533480). You must submit your code at the Chinese version of the statement.**

## 题目描述

Charlie 正在上一门叫做《抽象字符串基础》的课。

> **定义 3.1：** 对于两个长度相同的小写字母串 $S$ 和 $T$，定义它们的**相似度**为它们相同的对应位置个数。形式化地，设 $|S|=|T|=n$，则 $S$ 和 $T$ 的相似度 $\psi(S,T)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i=j][S_i=T_j]$。  
>
> **引理 3.1：** 对于任意小写字母串 $S$，存在唯一的小写字母串 $T$，使得 $\psi(S,T)$ 最大化。  
>
> **引理 3.1 的证明：**……

Charlie 逐渐开始神游，在纸上写写画画。忽然，他想到定义 $S$ 和 $T$ 的**不相似度**为有几对不同位置上的字符不同，即 $\tilde\psi(S,T)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i\neq j][S_i\neq T_j]$。这个清奇的定义让 Charlie 一下子清醒了，他想到，什么样的小写字母串 $T$ 能够最大化 $S$ 和 $T$ 的**不相似度**呢？

注：$[x]$ 的方括号为艾弗森括号，其定义为：若条件表达式 $x$ 为真则 $[x]$ 取值为 $1$，否则 $[x]$ 取值为 $0$。

## 说明/提示

#### 【样例解释 #1】

当 $T=\texttt{godfather}$ 时，$\tilde\psi(S,T)=72$，取到最大值。注意答案可能不止一种。

#### 【数据范围】

**本题采用捆绑测试。**

|子任务编号  |$n\le$  |特殊性质|分值|
| :-----------: | :-----------: |:----:|:----:|
|$0$  |$28$  | 是样例 | $0$ |
|$1$  |$4$  | 无 |$20$  |
|$2$  |$10^6$  | $S$ 中不包含字符 `z` |$20$  |
|$3$  |$10^3$  | 无 |$20$  |
|$4$  |$10^6$  | 无 |$40$  |

对于所有数据，满足：

- $1 \leq n \leq 10^6$；
- $S$ 中仅包含小写字母。

## 样例 #1

### 输入

```
9
cbbccxxxx```

### 输出

```
godfather```

## 样例 #2

### 输入

```
26
abcdefghijklmnopqrstuvwxyz```

### 输出

```
abcdefghijklmnopqrstuvwxyz```

## 样例 #3

### 输入

```
28
aabcdefghijklmnopqrstuvwxyzz```

### 输出

```
cybcdefghijklmnopqrstuvwxycy```

# 题解

## 作者：include13_fAKe (赞：6)

## 思路

很明显本题是求一个字符出现次数的最小值的加强版，具体来说是每一次删除某个字符然后再求。

### Subtask 1

直接暴力枚举即可，$26^4=456976$，稳稳地 $O(26^n)$ 通过。

### Subtask 2

直接输出 $n$ 个 `z` 即可。因为字符串中没有 `z`，所以此时的**不相似度**可以达到最大值。

### Subtask 3

直接暴力统计即可。时间复杂度 $O(n^2)$ 没有任何问题。

### Subtask 4

考虑如何快速计算。

首先算出每一种字符出现的次数，以及所有字符出现次数的最小值和出现次数的最小的字符。

令当前所在位置的字符出现的次数为 $x$，所有字符出现次数的最小值为 $y$。

因为当前出现的不纳入统计，所以当 $x-1\le y$ 时，可以填当前所在位置的字符，不然填全局出现次数的最小的字符。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
string s;
int ans[140];
int main(){
	cin>>n;
	cin>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		ans[s[i]]++;
	}
	char min1='9';
	int min2=1e9;
	for(int i='a';i<='z';i++){
		if(ans[i]<min2){
			min2=ans[i];
			min1=i;
		}
	} 
	for(int i=1;i<=n;i++){
		int now1=ans[s[i]]-1;
		if(now1<min2){
			cout<<(char)s[i];
		}
		else{
			cout<<min1;
		}
	}
	cout<<endl;
	return 0;
}//有谁能比我知道 你的温柔像羽毛
```

笑点：笔者为了防止有人和自己代码完全相同导致自己被判为作弊，在代码末尾写了一句周杰伦《你听得到》的歌词，居然还写错了，现已纠正。

---

## 作者：WsW_ (赞：4)

### 前言
简单贡献统计题。  

周六的时候还在上课，语文课上拿着同学老年机看题并口胡。另外，语文老师是年级主任。  

---
### 思路
将题目翻译成中文：给一个字符串 $S$，请求一个字符串 $T$ 使得两个字符串中位置和字母都不同的数量，即满足 $i\neq j,S_i\neq T_j$ 的 $(i,j)$，最多。  
容易发现每个 $T_j$ 互不相关，所以对每个 $T_j$ 分开考虑。  

假设已知 $T_j$ 是什么字母，我们考虑如何求出它的贡献 $\sum\limits^{n}_{i=1}[i\neq j][S_i\neq T_j]$。把式子理解之后转化一下，得 $(\sum\limits^{n}_{i=1}[S_i\neq T_j])-[S_j\neq T_j]$。  
接着想怎样快速求出 $\sum\limits^{n}_{i=1}[S_i\neq T_j]$。把这个式子转化一下，得 $n-\sum\limits^{n}_{i=1}[S_i= T_j]$。  
预处理一下，开一个桶 $cnt$ 记录 $S$ 中每个字母的数量，就可以 $O(1)$ 求出 $\sum\limits^{n}_{i=1}[S_i= T_j]=cnt_{T_j}$。  
最后我们就可以 $O(1)$ 求出一个已知 $T_j$ 的贡献 $n-cnt_{T_j}-[S_j\neq T_j]$。  

然后对于每一个 $T_j$，枚举全部的 $26$ 个字母，哪个字母产生的贡献大把 $T_j$ 设成哪个字母。  

时间复杂度为 $O(|S|n)$。其中 $|S|=26$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int cnt[30];

int g(char c,int p){//求贡献
	return n-cnt[c-'a']-(s[p]!=c);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>s;
	for(int i=0;i<n;i++)cnt[s[i]-'a']++;//预处理
	for(int i=0;i<n;i++){
		char max_c='z';//随便初始化一个字母，初始化成啥都行
		for(char c='a';c<'z';c++)//枚举放哪个字母
			if(g(c,i)>g(max_c,i))max_c=c;
		cout<<max_c;
	}
	return 0;
}
```

---

## 作者：liyunhe (赞：4)

### 题意分析
首先，在一个位置放上字母，不相似度为其他地方不是这个字母的个数。

我们可以定义新相似度为其他地方是这个字母的数量，这样的话每一个位置上的不相似度和新相似度加起来正好就是 $n-1$，所以只要最小化相似度即可。

如果暴力枚举的话。时间一定会超。所以先预处理，将每个字母的数量先统计出来。然后最小化相似度，找一个字母 $j$，使 $cnt_j$ 最小，需要小心的是如果 $j=s_i$，应该是 $cnt_j-1$，可以表示为 `cnt[j]-(j==s[i]?1:0)`。
### 代码
```cpp
#include<bits/stdc++.h>
int cnt[131];
using namespace std;
int main() {
	int n;string s;
	cin>>n>>s;
	for(int i=0;i<n;i++)cnt[s[i]]++;
	for(int i=0;i<n;i++){
		char ans=s[i];
		for(char j='a';j<='z';j+=1){
			if(cnt[j]-(j==s[i]?1:0)<cnt[ans]-(ans==s[i]?1:0)){
				ans=j;
			}
		}
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：__CJY__ (赞：3)

看没人发题解，我来发一篇题解。
## 题意简述
给定一个仅由小写字母组成的字符串 $S$，构造另一个仅由小写字母组成的字符串 $T$，使得 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i \ne j][S_i \ne T_j]$ 最大化，$1 \le n \le 10^6$。
## 思路
显然暴力不行（~~我也不知道怎么暴力~~）。

我们来推一波式子。
$$
\begin{aligned}
\tilde\psi(S,T)
&=\sum_{i=1}^n\sum_{j=1}^n[i\neq j][S_i\neq T_j]\\
&=n(n-1)-\sum_{i=1}^n\sum_{j=1}^n[i \ne j][S_i=T_j]
\end{aligned}$$
$\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i\neq j][S_i\neq T_j]$ 是 $S_i \ne T_j$ 的数量，我们用 $x$ 表示；$n(n-1)$ 是所有 $i \ne j$ 的数量，因为每行有一个 $i=j$ 的元素，共有 $n$ 行，我们用 $s$ 表示；$\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i \ne j][S_i=T_j]$ 是 $S_i=T_j$ 的数量，我们用 $t$ 表示。

由此我们可以得出：
$$x=s-t$$
要使 $x$ 最大，我们要最小化 $t$。

对于每一个 $T_i$ 的贡献，你会发现填 $S$ 中出现次数最少的字母最优。

如何快速求出 $S$ 中出现次数最少的字母呢？我们知道有个函数叫做`min_element`（只是码量减少了，实际上还是遍历了一遍数组，时间复杂度不变），想要深入了解的请点 [Link1](https://blog.csdn.net/m0_74017151/article/details/137978014) & [Link2](https://zhuanlan.zhihu.com/p/435905136?utm_id=0) & [Link3（强烈推荐）](https://blog.csdn.net/weixin_51566349/article/details/127979598)。

使用`min_element`的时间复杂度是 $\Theta(26)$，遍历一遍字符串 $S$ 的时间复杂度是 $\Theta(n)$，总时间复杂度是 $\Theta(26n)$，显然不会超时。

**此题有 $\text{Special Judge}$，答案不唯一！**
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int c[26],n;
int main(){
	cin>>n>>s;
	for(int i=0;i<n;i++) c[s[i]-'a']++;//先统计每个字符出现的次数
	for(int i=0;i<n;i++){
        c[s[i]-'a']--;//先将s[i]字符的计数器减1，因为我们要找一个与s[i]不同的字符
        cout<<(char)('a'+(min_element(c,c+26)-c));
        /*
        使用min_element(c,c+26)找到数组c中最小值的迭代器，这个最小值表示当前出现次数最少的字符
        将这个迭代器转换为对应的字符（通过加上'a'并转换为字符），并输出
        这个字符就是我们要选择的与s[i]不同的字符，因为它出现得最少，所以选择它最能增加不相似度
        */
        c[s[i]-'a']++;//将s[i]字符的计数器再加1，恢复原来的状态，以便处理下一个位置
    }
}
```

---

## 作者：Zyhx (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11279)

分析题目，可知对于一个字符串 $S$ ,要求输出一个字符串 $T$ , 求字符串 $T$ 与 字符串 $S$ 的不相似度 $ \~ψ(S,T)=\sum_{i=1}^{n}\sum_{j=1}^{n}\ [$i$ \ne $j$][S_{i} \ne T_{j}] $，$\~ψ(S,T)$ 最大，就是求 $T$ 中的第 $i$ 位的字符，除去 $S$ 的第 $i$ 位的字符，在 $S$ 其余位置中出现的次数最少。

根据题目意思，不难想到使用桶计数，先在输入时进行桶计数，接下来逐位遍历字符串 $S$ 中的每一位，因为题目不将遍历到的这一位算入不相似度，故我们在遍历到这一位时应该要让这一位的字符在桶中的计数减一，最后再扫一遍桶中字符出现次数，输出最小的即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
char S[1000005]; int n,b[100],minc=INT_MAX,mark;//minc用于比较最小值，mark用于标记最小值编号 
int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;++i){ cin>>S[i]; ++b[S[i]-'a']; }//输入字符串S，并进行桶计数 
	for(register int i=1;i<=n;++i){
		b[S[i]-'a']--; minc=INT_MAX;//初始化minc，将当前遍历到的这一项的字符出现次数减一 
		for(register int j=0;j<26;++j){
			if(b[j]<minc) minc=min(b[j],minc),mark=j;//求最小出现次数的字母 
		}cout<<(char)(mark+'a');//char强转类型，输出 
		b[S[i]-'a']++;//注意要复原回原来的状态 
	}return 0;
}
```
本蒟蒻第一次写题解，若本题解有任何问题欢迎大佬指出。

---

## 作者：sunhaozhe111022 (赞：2)

**思路：**

有三种情况：

1. 如果一开始的字符串有没有出现过的字母就直接输出那个字母。
2. 如果 $26$ 个字符全部刚刚好出现一次，就直接输出原字符串。
3. 否则的话就遍历整个 $S$，每一次去寻找一遍出现次数最少的那个字母并输出。因为自己本身和自己本身是不能称作不相似的，所以每次遍历要将当前这个字母的出现次数减少一次，在找最小值。

**代码：**
```
#include<bits/stdc++.h>
using namespace std;
long long n,mi=1e7,su,ok;
char p;
string s,t;
map<char,int>m;
int main()
{
	cin>>n>>s;
	for(int i=0;i<n;i++)
	{
		m[s[i]]++;//统计每个字母出现了几次
	}
	for(char i='a';i<='z';i++)
	{
		if(!m[i])
		{
			for(int j=1;j<=n;j++) 
			cout<<i;
			return 0;
		}
		else su+=m[i];
	}
	if(su==26)
	{
		cout<<s;
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		m[s[i]]--;
		mi=1e7;
		for(char j='a';j<='z';j++) 
		if(m[j]<mi) mi=m[j],p=j;
		cout<<p;
		m[s[i]]++;
	}	
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

这是一道典型的贪心题。  
### 具体思路
由极其简单的题意得到一个明确且可行的贪心思路：首先，遍历整个字符串，用一个数组记录每个字符出现的个数。然后，对 $26$ 个字符的出现次数进行排序。最后，再次遍历整个字符串，由于 $\tilde\psi(S,T)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i\neq j][S_i\neq T_j]$ 的 $i \ne j$，遍历到的第 $i$ 个字符不在统计范围内，所以该字符的实际个数在遍历到该字符的时候应减去一，如果它原本的字符在字符串中出现的次数与在字符串中出现次最少的字符相等，那么这个字符实际上才是使不相似度最大化的最优字符。反之，在字符串中出现次最少的字符才是使不相似度最大化的最优字符。  
### 代码实现 

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
const int N=1e6+5;
int f[30];
pair<int,char> t[30];
signed main() {
	int n;
	cin>>n;
	string x;
	cin>>x;
	for(int i=0;i<26;i++)t[i].second=i+'a';//桶先记录下26个字符 
	for(int i=0; i<x.size(); i++) {
		t[x[i]-'a'].first++;//用桶记录每个字符的出现次数 
	}
	sort(t,t+26);//排序 
	for(int i=0; i<26; i++) {
		f[t[i].second-'a']=i;//再用另一个数组记录每个字符排序后的实际下标 
	}
	for(int i=0; i<x.size(); i++) {
		int k=t[f[x[i]-'a']].first;
		if(k==t[0].first) {//如果第 i个字符的出现次数与出现次数最少的字符相同 
			cout<<x[i];//直接输出该字符 
		} else {
			cout<<t[0].second;//反之输出出现次数最少的字符 
		}
	}
	return 0;
}

```

---

## 作者：E_M_T (赞：1)

看一下这个式子：

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i\neq j][S_i\neq T_j]$$

$$=n^2-\sum\limits_{i=1}^n\sum\limits_{j=1}^n[S_i= T_j]-\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i=j]+\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i=j][S_i= T_i]$$

$$=n^2-n-\sum\limits_{i=1}^n\sum\limits_{j=1}^n[S_i= T_j]+\sum\limits_{i=1}^n[S_i= T_i]$$



到这里就可以 $O(n)$ 了。对于 $T$ 的每一位枚举 26 个字母取最大贡献即可。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=1e6+10;
int n;
char s[N];
int cnt[30];
il void solve()
{
	n=read();
	scanf("%s",s+1);
	F(i,1,n) cnt[s[i]-'a']++;
	int ans=n*n-n;
	F(i,1,n)
	{
		int mi=n+1,c;
		F(j,0,25)
		{
			if(cnt[j]-(j==(s[i]-'a'))<mi)
			{
				mi=cnt[j]-(j==(s[i]-'a'));
				c=j;
			}
		}
		sd cout<<char(c+'a');
		ans-=mi;
	}
	// put(ans);
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：zouchenjun (赞：0)

### 题意：
字符串 $A$ 和 $B$ 的不相似度为有几对不同位置上的字符不同。求出与 $S$ 不相似度最大的字符串。
### 思路
对每个位置枚举即可，但要注意相同位置的字符相同不能算入。

复杂度为 $O(n)$。


---
### 代码



```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s[10000];
char m[1000002],mxnb;
int main(){
	cin>>n>>m+1;
	for(int i=1;i<=n;i++)
		s[m[i]-'a'+1]++;//提前计算出各字符的数量
	for(int i=1;i<=n;i++){
		int minn=100000000,ans;
		s[m[i]-'a'+1]--;//注意这里要-1
		for(int j=1;j<=26;j++){
			if(minn>=s[j]){
				minn=s[j];
				ans=j;
			}
		}
		s[m[i]-'a'+1]++;
		cout<<char(ans+'a'-1);
	}
}
```

---

## 作者：emo_zkt (赞：0)

首先，这道题太简单了，但是有坑。

你要知道，输出原字符串未必最优，比如字符串为 aaaaaaaa，那你这么想就大错特错了。

废话我也不说了，你直接输入时统计各个字符出现次数。然后枚举每个位置，例如到第 $i$ 位时，把 $s_i$ 出现次数减去 1，然后统计哪个字符出现次数最少，然后输出这个字符，再把 $s_i$ 出现次数加回去，防止影响下一次统计。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[35],n;
string s;
int main(){
	cin>>n>>s;
	for(int i=0;i<s.size();i++)a[s[i]-'a'+1]++;
	for(int i=0;i<s.size();i++){
		a[s[i]-'a'+1]--;
		int fl=0;
		for(int i=1;i<=26;i++){
			if(a[i]==0){
				cout<<char(i-1+'a');
				fl=1;
				break;
			}
		}
		if(fl==0){
			int mi=0x3f3f3f3f,minn;
			for(int i=1;i<=26;i++){
				if(a[i]<mi)mi=a[i],minn=i;
			}
			cout<<char(minn-1+'a');
		}
		a[s[i]-'a'+1]++;
	}
	return 0;
}
```

---

## 作者：许多 (赞：0)

签到题。

对于每一个位置，我们可以找字符串 $S$ **除这个位置之外**哪一个字母出现次数最少，这个位置即这个字母。

这个信息我们可以用桶预处理，每次操作减去当前位置的标记即可。

## CODE


```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int n;
int p[520];
char a[5201314],MAX;
int main(){
    cin>>n>>a+1;
    for(int i=1;i<=n;i++)
        p[a[i]-'a'+1]++;
    for(int i=1;i<=n;i++){
        MAX='a';
        p[a[i]-'a'+1]--;
        for(char ch='b';ch<='z';ch++)
            if(p[ch-'a'+1]<p[MAX-'a'+1])
                MAX=ch;
        p[a[i]-'a'+1]++;
        printf("%c",MAX);
    }
    return 0;
}
```

---

## 作者：we_are_the_chuibing (赞：0)

考虑 $T$ 的每个字符对不相似度的贡献。

对于每一位，其贡献为这一位与 $S$ 上不同位置的不相同字符的个数。统计 $S$ 中每个字符出现的次数，统计出出现次数最少的所有字符，对于 $T$ 的每一位，如果 $S$ 的对应位在出现次数最少的字符里，则直接选择这个字符，反之则随便输出一个出现次数最少的字符即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long n,a[27],mc,mn=1145141919810;
int main(){
	cin>>n;
	cin>>s;
	long long l=n;
	for(int i=0;i<l;i++)a[s[i]-96]++;
	for(int i=1;i<=26;i++){
		if(a[i]<mn){
			mn=a[i];
			mc=i;
		}
	}
	for(int i=0;i<l;i++){
		if(a[s[i]-96]==mn)cout<<s[i];
		else cout<<char(mc+96);
	}
	return 0;
}
```

---

## 作者：jinfanhao (赞：0)

这道题就是一道普通贪心。\
每回要找最小的字符，所以用个桶记录下所有的，再把当前所在位置的字符给忽略掉，到新的一个位置在加回来就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,minx=INT_MAX;
char pos;
string op;
map<char,int> mp;
signed main(){
	scanf("%d",&n);
	cin >> op;
	for(int i=1; i<n; ++i)++mp[op[i]];
	for(char ch='a'; ch<='z'; ++ch){
		if(mp[ch]<minx){
			minx=mp[ch];
			pos=ch;
		}
	}
	printf("%c",pos);
	for(int i=1; i<n; ++i){
		minx=INT_MAX;
		++mp[op[i-1]];
		--mp[op[i]];
		for(char ch='a'; ch<='z'; ++ch){
			if(mp[ch]<minx){
				minx=mp[ch];
				pos=ch;
			}
		}
		printf("%c",pos);
	}
	return 0;
} 
```

---

## 作者：Stone_Xz (赞：0)

## [传送门：P11279](https://www.luogu.com.cn/problem/P11279)

## 简要题意：

> 给定一个长度为 $n$ 的字符串 $S$，需要你构造一个长度同样为 $n$ 的字符串 $T$，使得 $\tilde\psi(S,T)=\sum\limits_{i=1}^n\sum\limits_{j=1}^n[i\neq j][S_i\neq T_j]$ 最大化。

## 分析：贪心

考虑贪心。对于 $T$ 中的每个位置 $i$，假设这个位置的字符为 $c$，那么我们希望在 $S$ 中，除了 $i$ 这个位置（别漏掉 $i\neq j$ 这个条件），与 $c$ 不同的字符尽量多，即与 $c$ 相同的字符尽可能少。所以我们对于 $T$ 的每个位置 $i$，枚举 $26$ 个字母，取在 $S$ 中出现次数最少的字符即可（去掉 $S$ 中位置 $i$ 的字符）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, mini = 1e9, sum[1005];

char ans;

string s;

int main()
{
	cin >> n >> s;
	for (int i = 0; i < n; i++)
		sum[s[i]] ++;                    // 统计每个字符在 S 出现次数 
	for (char i = 'a'; i <= 'z'; i++) {
		if (sum[i] == 0) {
			for (int j = 1; j <= n; j++)
				cout << i;
			return 0;
		}
	}
	for (int i = 0; i < n; i++) {
		mini = 1e9;
		sum[s[i]] --;                     // 去掉 S 中位置 i 字符的贡献 
		for (char j = 'a'; j <= 'z'; j++) {
			if (sum[j] < mini) {
				mini = sum[j];
				ans = j;                  // 取在 S 中出现次数最少的字符 
			}
		}
		cout << ans;
		sum[s[i]] ++;                     // 加回 S 中位置 i 字符的贡献 
	}
	return 0;
}
```

---

## 作者：MnZnOIer (赞：0)

考场上想错了，卡了 45 分钟才做出来。

### 解题思路
我们可以先把整个字符串离散化，统计出现的个数最少的字符，通过观察可以发现（不是），一个字符有不同位置的相同的字符，会减少贡献，所以我们要尽量减少这样的情况，又因为相同位置的相同字符是可以计算贡献的，不会被该位置的字符减少贡献。

当一个字符能减少的贡献超过数量最少的字符的数量，就可以把他替换成出现数量最少的字符。

### 部分代码
$c_i$ 是统计数量的数组，$M$ 是出现次数最少的字符的数量，$cc$ 是出现最少的字符。下面给出该部分代码：
```cpp
for (int i = 0; i < s.size (); ++ i)
{
    int sum = c[s[i] - 'a'] - 1;//减一是因为相同位置不算贡献。
    if (sum > M)cout << cc;
    else cout << s[i];
}
```

剩下的部分实现比较简单，就不占用版面了。

---

## 作者：jiangyunuo (赞：0)

### 题目大意：

给出一个数 $n$ 和一个长度为 $n$ 的字符串 $S$，求出一个与 $S$ 长度相等且**不相似度**最大的字符串 $T$。

**不相似度**：两个字符串，不同位置上字符不同的组数。

举个例子：

$S=\texttt{aa}$ 且 $T=\texttt{ab}$。

|$S$（下边）和 $T$（右边）|$a$|$b$|
|:-:|:-:|:-:|
|$a$|不成立，是同一个位置。|成立|
|$a$|不成立，字符相同|不成立，是同一个位置|

所以 $\tilde\psi(S,T)=1$。

### 大体思路：

我们可以这样想，我们要想让不相似度最大，我们就要保证 $T$ 的某一个位置的字符要与 $S$ 的其他位置的字符相同的数量最少，注意下，同一个位置的两个数不管相不相同，都是不符合要求。

我们可以用一个数组来存储各个字符的数量，接着每一个地方输出什么字符也要判断一下，对于 $S$ 的第 $i$ 个位置，有两种情况：

1. $S$ 中出现次数最少的字符（由于可能会有多个，我们就选其中一个做标准，所以要判断）小于 $S$ 的第 $i$ 个位置的字符出现次数，那就输出出现次数最少的字符；

2. 反之，如果等于的话，就输出 $S$ 的第 $i$ 个位置的字符（因为当他们相等时，按出现次数最少的字符，当然，肯定不是此位置的字符，就算是按上面输出也没影响，就会导致比 $S$ 的第 $i$ 个位置的字符多一个不符合的，因为有一个是因为同一个位置）。

### 代码：

```cpp
#include<bits/stdc++.h>  
using namespace std;
int main(){
    int n;
    char a[1000000];
    cin>>n>>a;
    int b[27];
	for(int i=0;i<n;i++){
		b[a[i]-96]++;    //记录各个字符的出现次数。
	}
	char ans;
	int sum=999999;
	for(int i=1;i<=26;i++){
		if(b[i]<sum){sum=b[i];ans=i+96;}  //找出出现次数最少的字符。
	}
	for(int i=0;i<n;i++){
		if(b[a[i]-96]==sum)cout<<a[i];  //判断并输出。
		else cout<<ans;
	}
    return 0;
}
```

---

## 作者：Hy13_xsm (赞：0)

## 题意理解

给定一个字符串 $S$，构造一个长度相等的字符串 $T$，它们的不相似度定义是不相同且不对应的位置的个数。构造的 $T$ 需要满足不相似度最大。

## 题目分析

我使用了逆向思维。（实际上不完全是）思路是**最小化**相同**或**对应的位置个数。我们可以发现，如果 $T$ 与 $S$ 的对应字母**相同**，那么减少的个数就是长度与这个字母个数的差。反之，如果不相同，这个值还会再减去 $1$。所以我们只需要统计出 $S$ 中每个字符出现的次数，然后枚举 $26$ 个字母中哪一个字母可以与 $S$ 中的那个字母相对应。当然是取减少值最少的那个字母。

最后就可以根据 $S$ 中的字母输出对应的字母了。思路比较清晰，希望能给大家带来帮助。

## 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200];
string s;
char ans[200];
int main()
{
	cin>>n>>s;
	for(int i=0;i<n;i++)
	a[s[i]]++;//统计每个字符出现次数。
	for(int i='a';i<='z';i++)
	{
		if(!a[i]){
			for(int j=1;j<=n;j++)
			cout<<char(i);
			return 0;
		}
	}//其实是一个小小的优化。如果有一个字母一次都没有出现过，那当 T 里面全是那个字母的时候，不相似度显然最大。
	for(int i='a';i<='z';i++)
	{
		int x=a[i],y=2000000;
		char rel;
		for(int j='a';j<='z';j++)
		{
			if(y>a[j])
			{
				y=a[j];
				rel=j;
			}
		}
		if(y+1>x)rel=i;
		ans[i]=rel;//计算每个字母对应的答案。
	}
	for(int i=0;i<n;i++)
	cout<<ans[s[i]];//根据对应字母输出。
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路
这道题我们要使 $\tilde\psi$ 最大化，那就是让 $T_i$ 与除了 $S_i$ 以外的所有字母都尽可能不相同。所以每个 $T_i$ 只要找到在 $S$ 上除了 $S_i$ 外出现次数最小的字母填充到 $T_i$ 就可以了。此时我们可以构造出一个 $O(n^2)$ 的算法。

但实则，如果一个位置不取出场最小的字母，那说明一个与最小相等的字母就是 $S_i$，即两者的出场次数一致。那我们只要比较若当前位置上的 $S_i$ 出场次数等于最小字母时选择 $S_i$ 就好了。复杂度 $O(n)$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n, num[30], min1=0x3f3f3f3f, num1;
string s;
int main() {
	cin >> n >> s;
	s = ' ' + s;
	for (int i = 1; i <= n; i++) {
		num[s[i] - 'a' + 1]++;
	}
	for(int i=1;i<=26;i++){
		if(num[i]<=min1){
			min1=num[i];
			num1=i;
		}
	}
	for(int i=1;i<=n;i++){
		if(num[s[i]-'a'+1]-1<min1) cout<<s[i];
		else cout<<char(num1-1+'a');
	}
	return 1;
}
```

---

