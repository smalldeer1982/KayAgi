# [AGC066F] Beautiful String

## 题目描述

我们将满足以下条件的字符串称为**美丽字符串**：

- 每个字符都是 `A`、`B` 或 `C` 之一。
- 任意相邻的 $2$ 个字符都不相同。

例如，`AB`、`BCAC` 是美丽字符串，而 `BB`、`CBAAC` 不是美丽字符串。

------

给定一个美丽字符串 $S$，你可以对其反复进行如下操作：

- 操作：交换 $S$ 中相邻的 $2$ 个字符，但交换后得到的 $S$ 也必须是美丽字符串。

请你求出最终可能得到的字典序最小的字符串 $S$。

有 $T$ 个测试用例，请分别输出每个测试用例的答案。

## 说明/提示

### 限制

- $1\leq T\leq 10^5$
- $S$ 是美丽字符串。
- $1\leq |S|\leq 10^6$
- 所有测试用例中 $|S|$ 的总和不超过 $10^6$。

### 样例解释 1

对于第 $1$、$2$ 个测试用例，以下是将 $S$ 字典序最小化的一种方式：

- `CAB` → `ACB` → `ABC`
- `ACBCB` → `CABCB` → `CBACB` → `BCACB` → `BCABC` → `BACBC` → `ABCBC`

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
CAB
ACBCB
B
AC
BACBA
BABABA
ABCBCAC
CBABACABCBABABC```

### 输出

```
ABC
ABCBC
B
AC
ABABC
BABABA
ABCACBC
ABABACBCACBCBAB```

# 题解

## 作者：Rainbow_qwq (赞：6)

~~怎么又把 3 Letters trick 拿出来~~。属于是可做，但需要大量时间手玩和推细节的题。。

考虑把 `ABC` 串转为一条折线：$A\to B,B\to C,C\to A$ 则为 `+`，否则为 `-`。

则如果 swap 位置非头和尾，则体现为 `+++` 和 `---` 相互转化。

如果 swap 尾部，则为尾部 `++` 和 `--` 相互转化；如果 swap 头部，则头部字母会变化，且头部 `++` 和 `--` 相互转化，如 `A++` $\to$ `B--`。

那考虑折线的“最简形式”：首先将连着的 `+++`,`---` 消掉，它们可以插在串的任意位置；接着，当头部/尾部存在 两个相同 加 一个相反 时，可以把这三个字符消掉。如果这样转化完后，折线长度没有减少，说明这个串根本无法操作，直接返回。

接下来讨论一些 corner case 来最小化头部字母，把头部字母变成 `A`。

然后考虑贪心：

- [1] 假设原折线的下一步走到 $c_1$，反着走走到 $c_2$。如果 $c_2<c_1$ 且有可以使用的 `+++/---`，则塞一个 `+++/---` 进来改变方向，否则按原方向走。
- [2] 如果原折线没有下一步了，则贪心塞一个 `+++/---` 往更优的方向走。

但是这样的贪心只塞了一些 `+++/---`，并没有考虑改头部和改尾部。

考虑改头部的影响：`A` $\to$ `B--+` $\to$ `C--+--+` $\to$ `A--+--+--+`。发现这个方案是更劣的，可以不考虑更改头部。

考虑改尾部的影响：由于前面简化了折线，所以尾部最后一个连续段只有一个相同的 `+/-`。只有在尾部添加 `+++` 时，才可能（使用尾部操作）变成 `+--`。

再考虑贪心的整个过程：

- 在上述 [2] 时才可能在尾部添加。
- 如果在尾部添加了，则前面的串中一定不会出现 `C`，如果前面要走到 `C` 肯定在前面添加了。
- 手玩贪心，在尾部添加的最优串会形如：`A`:`(+(-(+(..)++)--)++)`，`B`:`(-(+(-(..)--)++)--)`，改末尾最多只能翻转最后两个字符。于是特判一下就行了。

写起来有点大模拟 + 细节。

[submission](https://atcoder.jp/contests/agc066/submissions/51972156)

```cpp
#include<bits/stdc++.h>

#define l first
#define x second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 1000005

int n,a[maxn];
string s;
char s0;

int up(char a,char b){
	a=a-'A',b=b-'A';
	return (a+1)%3==b?1:-1;
}
char add(char a,int b){
	a=a-'A',a=(a+(b+3))%3,a=a+'A';
	return a;
}

pii st[maxn];
int tp;
void push(int x){
	if(tp && st[tp].x==x) st[tp].l++;
	else st[++tp]=mkp(1,x);
	if(tp && st[tp].l==3) --tp;
	if(tp==2 && st[tp-1].l==2 && st[tp].l==1){
		// A++-
		// B
		s0=add(s0,st[tp-1].x);
		tp-=2;
	}
}

pii t[maxn*2];
int m;
string get(bool revs){
	m=tp;
	For(i,1,tp)t[i]=st[i];
	
	int sum=0;
	For(i,1,m)sum+=t[i].l;
	sum=(n-sum-1)/3;
	string res="A";
	reverse(t+1,t+m+1);
	bool fl=0;
	while(1){
		while(m && !t[m].l) --m;
		if(!m){
			if(!sum)break;
			if(!fl && revs) {
				--sum,fl=1;
				t[++m].l=1,t[m].x=(res.back()=='B'?-1:1);
				t[++m].l=2,t[m].x=-t[m-1].x;
				swap(t[m],t[m-1]);
				continue;
			}
			--sum,++m;
			t[m].l=3;
			t[m].x=(res.back()=='B'?-1:1);
		}
		char c1=add(res.back(),t[m].x);
		char c2=add(res.back(),-t[m].x);
		if(!sum || c1<c2) {
			res+=c1;
			--t[m].l;
		}else{
			res+=c2;
			--sum;
			t[++m].l=2;
			t[m].x=-t[m-1].x;
		}
	}
	return res;
}

void work()
{
	cin>>s;
	n=s.size();
	if(n<=2){
		sort(s.begin(),s.end());
		cout<<s<<"\n"; return;
	}
	if(n==3){
		if(s[0]==s[2])cout<<s<<"\n";
		else cout<<"ABC"<<'\n';
		return;
	}
	
	s0=s[0]; tp=0;
	For(i,1,n-1) push(up(s[i-1],s[i]));
	
	while(tp>=2 && st[tp].l==2){
		st[tp].l-=2,st[tp-1].l-=1;
		while(tp && !st[tp].l) --tp;
	}
	int sum=0;
	For(i,1,tp) sum+=st[i].l;
	if(sum==n-1){
		cout<<s<<"\n";
		return;
	}
	
	if(tp==1 && st[tp].l==2){
		// A++
		s0='A';
		st[tp]=mkp(2,1);
	}
	if(tp==1 && st[tp].l==1){
		// A+
		// B-
		char s00=add(s0,st[tp].x);
		if(s00<s0) s0=s00,st[tp].x*=-1;
	}
	if(s0=='B' || s0=='C'){
		// B---
		// A++-
		Rep(i,tp,1) st[i+2]=st[i];
		tp+=2;
		if(s0=='B') st[1]=mkp(2,1),st[2]=mkp(1,-1);
		else st[1]=mkp(2,-1),st[2]=mkp(1,1);
		s0='A';
	}
	string res=min(get(0),get(1));
	cout<<res<<"\n";
}

signed main()
{
	int T;cin>>T;
	while(T--)work();
	return 0;
}
```

---

