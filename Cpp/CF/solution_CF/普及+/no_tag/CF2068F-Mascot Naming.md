# Mascot Naming

## 题目描述

在筹办大型活动时，组织者常需处理专业领域外的琐事。例如，EUC 2025 的主裁判需要为官方吉祥物命名，并满足以下条件：
- 名称必须包含特定单词作为子序列$^{\texttt{*}}$，例如活动名称和举办地。给定必须包含的 $n$ 个单词列表 $s_1, s_2, \ldots, s_n$。
- 名称不得包含去年吉祥物名称 $t$ 作为子序列$^{\texttt{*}}$。

请帮助主裁判找到有效的吉祥物名称，或判定其不存在。  
$^{\texttt{*}}$ 若字符串 $x$ 可通过删除字符串 $y$ 中若干字符（不改变剩余字符顺序）得到，则称 $x$ 是 $y$ 的子序列。例如，$\texttt{abc}$ 是 $\texttt{axbycz}$ 的子序列，但不是 $\texttt{acbxyz}$ 的子序列。

## 说明/提示

第一个样例中，必须作为子序列的单词是 $\texttt{porto}$ 和 $\texttt{euc}$，而禁止作为子序列的单词是 $\texttt{prague}$。存在多个有效名称，例如 $\texttt{poretuco}$ 或 $\texttt{xxxpppeortoucyyyy}$。

若选择 $\texttt{poretuco}$ 作为名称，可验证 $\texttt{porto}$ 和 $\texttt{euc}$ 是其子序列（例如高亮显示为 $\texttt{POReTucO}$ 和 $\texttt{porEtUCo}$），而 $\texttt{prague}$ 不是。

字符串 $\texttt{poretuc}$ 无效，因其不包含 $\texttt{porto}$ 作为子序列。字符串 $\texttt{poretucoague}$ 也无效，因其包含 $\texttt{prague}$ 作为子序列。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
porto
euc
prague```

### 输出

```
YES
poretuco```

## 样例 #2

### 输入

```
6
credit
debit
money
rich
bank
capitalism
trap```

### 输出

```
YES
moncrdebditeychankpitalism```

## 样例 #3

### 输入

```
2
axiom
choice
io```

### 输出

```
NO```

## 样例 #4

### 输入

```
4
aaa
aab
abb
bbb
ba```

### 输出

```
YES
aaabbb```

# 题解

## 作者：ARIS1_0 (赞：1)

题意不再赘述，直接讲思路

# 思路

先考虑答案为 `NO` 的情况：既然要求所有的 $s_i$ 都要成为 $ans$ 的子序列，而 $t$ 不能成为 $ans$ 的子序列，所以当 $t$ 是任意一个 $s_i$ 的子序列的时候答案即为 `NO`，因为将 $s_i$ 作为答案子序列时必定也将 $t$ 作为了答案的子序列。

剩下的情况答案肯定都是 `YES`，不过我们并不能暴力地把所有的 $s_i$ 拼在一起，这样子可能会在 $ans$ 的子序列中产生 $t$。比如说 $s=\{\texttt{a},\texttt{b}\}$，$t=\texttt{ab}$ 时，答案就为 $\texttt{ba}$，而不是暴力地拼在一起形成 $\texttt{ab}$。

我们先考虑对于两个字符串 $a,b$，我们是如何判断 $b$ 是否为 $a$ 的子序列的。我们先定义两个指针并指向 $a,b$ 最开头的字符。若指针指向的字符相等，则说明我们匹配到了一个字符，此时我们将两个指针全部后移一位，准备匹配下一个字符。若两个指针指向的字符不相等，则说明 $a$ 的这一位并没有参与子序列的构成，就把 $a$ 的指针向后移动一位，而不移动 $b$ 的指针，然后重复上述过程。如果 $a$ 的指针已经指向末尾最后一个字符的后面而 $b$ 的指针并没有指向末尾最后一个字符的后面则说明无法匹配，反之，一旦 $b$ 的指针指向了末尾最后一个字符的后面则说明匹配完成，$b$ 是 $a$ 的子序列。这样子的做法正确性很显然。时间复杂度为 $O(|a|)$。

我们可以依靠这个做法来实现第一步：答案的判断。题目保证了 $\sum |s|\le 2\times 10^5$，时间是够用的。

接下来我们就可以开始构造了，我们可以利用刚刚所提到的判断子序列的思想，我们对于每一个 $s_i$ 都定义一个指针 $pos_i$，随后对于每一个 $s_i$，若当前指针指向的字符与 $t$ 的指针指向的字符不相等，我们就直接把当前字符加入答案当中，直到当前 $s_i$ 的指针已经指向了末尾最后一个字符的后面，即 $s_i$ 已经完全匹配完成，对于每一个字符串我们都这么做。理想情况下是这样的，但是难免会遇见一种情况：当前 $s_i$ 指针所指向的字符与 $t$ 指针所指向的字符相等。那么我们先把 $s_i$ 放到一边去，先去匹配其他的 $s_i$，如果匹配不上了怎么办？也就是说现在的情况是剩下的所有的 $s_i$ 要么指针指向的字符都和 $t$ 指针指向的字符相等，要么已经匹配完成不会继续参与构造。那我们没办法，只能将全体还未匹配完成的 $s_i$ 的指针和 $t$ 的指针全部向后移动一位，并将刚刚的字符加入答案里面了。随后我们重复上述操作即可。

为什么这样子的做法是对的？我们这样做的做法建立在一个大前提的下面：对于每一个 $s_i$，我们都不能将 $t$ 与其完美匹配。对于每一个 $s_i$ 的指针，其必定是先移动到了末尾字符的后面去的。我们刚刚那样做，实际上就相当于是变换了一种判断子序列的方法。对于最开始的方法，我们是一个一个字符串慢慢去匹配的，而上述构造过程中对 $s_i$ 和 $t$ 的处理则是在考虑整体，相当于一个方法是从字符串方面去匹配，另一个方法是从字符集方面去匹配的。如果我们只考虑单独一个 $s_i$ 与 $t$，你会发现这就是我们最开始所说的判断子序列的方法。然后我们再来考虑 $ans$ 和 $s_i$，你会发现这还是判断子序列的方法，所有 $s_i$ 的指针全部指向了末尾最后一个字符的后面，所以所有的 $s_i$ 都作为了 $ans$ 的子序列。

这题就这么做完了。我的代码使用了 `set` 来装还没有匹配完成的 $s_i$ 的下标，所以时间复杂度是 $O(\sum |s|\log n)$ 的，实际可以做到线性。

# 代码


```cpp
#include<set>
#include<bits/stdc++.h>
#define ll long long
using namespace std;
mt19937 myrand(time(0));
inline ll read(){
	ll x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*w;
}
void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	static int sta[35];
	int top=0;
	do{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top)putchar(sta[--top]+'0');
}
int n;
string s[200005],t,ans;
int pos[200005],len[200005],lent;
bool check(){
	for(int i=1;i<=n;i++){
		int pos1=0,pos2=0;
		while(1){
			if(pos1>=len[i]){
				if(pos2>=lent)return 0;
				break;
			}
			if(s[i][pos1]==t[pos2])pos1++,pos2++;
			else pos1++;
		}
	}
	return 1;
}//判断子序列的函数
set<int>ss;
int del[200005];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		cin>>s[i];
		len[i]=s[i].size();
		ss.insert(i);
	}
	cin>>t;lent=t.size();
	if(!check()){puts("NO");return 0;}
	int cnt=0;puts("YES");
	while(!ss.empty()&&cnt<lent){
		bool f=1;
		int L=0;
		for(auto it=ss.begin();it!=ss.end();it++){
			int i=*it;
			if(pos[i]>=len[i])continue;
			if(s[i][pos[i]]!=t[cnt]){//优先处理掉当前字符与 t 不匹配的
				f=0;
				while(s[i][pos[i]]!=t[cnt]){
					cout<<s[i][pos[i]];
					++pos[i];
					if(pos[i]>=len[i]){//如果对答案串匹配完成就在集合里面删除这个字符串的下标
						del[++L]=i;
						break;
					}
				}
			}
		}
		if(f){//处理第二种情况，所有的未处理完的字符串都与 t 匹配上了
			cout<<t[cnt];
			for(auto it=ss.begin();it!=ss.end();it++){
				int i=*it;
				if(pos[i]>=len[i])continue;
				++pos[i];
				if(pos[i]>=len[i])del[++L]=i;
			}
			++cnt;
			if(cnt>=lent)break;//这一句实际上不会触发，换成 assert 就知道了
		}
		for(int i=1;i<=L;i++)ss.erase(ss.find(del[i]));
	}
	return 0;
}
```

[提交记录](https://codeforces.com/contest/2068/submission/308752599)。

---

