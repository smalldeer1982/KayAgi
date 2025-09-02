# [GCJ 2011 Qualification] Magicka

## 题目描述

作为一名法师，你可以召唤八种元素，这些是“基础”元素。每个基础元素是 $\{Q, W, E, R, A, S, D, F\}$ 中的一个字符。当你召唤一个元素时，它会被添加到你的元素列表的末尾。例如：如果你先召唤 $W$，再召唤 $A$（我们简称为“召唤 $WA$”），那么你的元素列表将变为 $[W, A]$。

我们会指定一些基础元素对，这些元素对可以组合成非基础元素（其余 18 个大写字母）。例如，$Q$ 和 $F$ 可以组合成 $T$。如果某一时刻，这对元素出现在元素列表的末尾，那么这两个元素会被立即移除，并用它们组合成的新元素替换。例如，如果元素列表为 $[A, Q, F]$ 或 $[A, F, Q]$，那么它会变为 $[A, T]$。

我们还会指定一些基础元素对，它们彼此“对立”。当你召唤一个元素后，如果它没有立即与其他元素组合成新元素，并且它与元素列表中的某个元素是对立的，那么你的整个元素列表会被清空。

例如，假设 $Q$ 和 $F$ 组合成 $T$，$R$ 和 $F$ 是对立的。那么依次召唤以下元素（从左到右）会有如下结果：

- $QF \rightarrow [T]$（$Q$ 和 $F$ 组合成 $T$）
- $QEF \rightarrow [Q, E, F]$（$Q$ 和 $F$ 没有同时出现在末尾，无法组合）
- $RFE \rightarrow [E]$（$F$ 和 $R$ 对立，列表被清空，然后召唤 $E$）
- $REF \rightarrow []$（$F$ 和 $R$ 对立，列表被清空）
- $RQF \rightarrow [R, T]$（$QF$ 组合成 $T$，列表不会被清空）
- $RFQ \rightarrow [Q]$（$F$ 和 $R$ 对立，列表被清空）

给定一系列要召唤的元素，最终你的元素列表中会有哪些元素？

## 说明/提示

**数据范围**

- $1 \leq T \leq 100$。
- 每对基础元素最多只会出现在一个组合中，但它们既可以组合也可以对立。
- 没有基础元素会与自身对立。
- 与游戏 Magicka 不同，元素列表长度没有限制。

**小数据集（10 分，测试点 1 - 可见）**

- $0 \leq C \leq 1$。
- $0 \leq D \leq 1$。
- $1 \leq N \leq 10$。
- 时间限制：3 秒。

**大数据集（15 分，测试点 2 - 隐藏）**

- $0 \leq C \leq 36$。
- $0 \leq D \leq 28$。
- $1 \leq N \leq 100$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
0 0 2 EA
1 QRI 0 4 RRQR
1 QFT 1 QF 7 FAQFDFQ
1 EEZ 1 QE 7 QEEEERA
0 1 QW 2 QW```

### 输出

```
Case #1: [E, A]
Case #2: [R, I, R]
Case #3: [F, D, T]
Case #4: [Z, E, R, A]
Case #5: []```

# 题解

## 作者：qkj_qwq (赞：4)

## 解题思路

模拟。

把召唤的基础元素依次压入栈中。每当栈顶的两个元素可以反应时，弹出栈顶的两个元素，压入产生的元素。

另外，还需要一个计数器，用于存储各元素的个数。反应时也要统计元素个数的变化。反应完之后，若有对立的元素，则清空栈，还要清空计数器。最后，输出栈即可。

具体看代码。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
map<pair<char,char>,char>p;
char s[110];int ss[110];
string b[110];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		p.clear();
		memset(ss,0,sizeof ss);
		int n,m,k,tp=0;
		string a;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			string a;
			cin>>a;
			p[mp(a[0],a[1])]=p[mp(a[1],a[0])]=a[2];
		}
		cin>>m;
		for(int i=1;i<=m;i++)
			cin>>b[i];
		cin>>k>>a;
		for(int i=0;i<k;i++)
		{
			s[++tp]=a[i];
			ss[a[i]]++;
			while(tp>1&&p[mp(s[tp],s[tp-1])])//反应
			{
				ss[s[tp]]--;
				ss[s[tp-1]]--;
				ss[p[mp(s[tp],s[tp-1])]]++;
				s[tp-1]=p[mp(s[tp],s[tp-1])];
				tp--;
			}
			for(int i=1;i<=m;i++)//对立
				if(ss[b[i][0]]&&ss[b[i][1]])tp=0;
			if(tp==0)memset(ss,0,sizeof ss);
		}
		cout<<'[';
		for(int i=1;i<tp;i++)
			cout<<s[i]<<", ";
		if(tp)cout<<s[tp];
		cout<<"]\n";
	}
	return 0;
}
```

---

## 作者：lmz105 (赞：0)

### 思路
首先在读入合成关系时用 ```map``` 记录下来，因为合成时不在意顺序，所以需要把两种不同顺序的情况都记录下来，后面的合成与对立对应的操作须保证合成的优先级更高，接下来按照题意模拟写出代码即可。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll T,n,m;
string s[30],str="";
int main() {
	cin >> T;
	for (ll t=1;t<=T;t++){
		map<string,char>mp;
		string ans;
		cin >> n;
		while(n--){
			string s1;
			cin >> s1;
			mp[str+s1[0]+s1[1]]=s1[2];//str不可删，需要它才能保证s1[0]+s1[1]的结果是string类型
			mp[str+s1[1]+s1[0]]=s1[2];
		}
		cin >> n;
		for (ll i=1;i<=n;i++){
			cin >> s[i];
		}
		cin >> m;
		while(m--){
			char ch;
			cin >> ch;
			ans+=ch;
			if (ans.size()>1){
				string s1=ans.substr(ans.size()-2,2);
				if (mp.find(s1)!=mp.end()){
					ans+=mp[s1];
					ans.erase(ans.size()-3,2);
				}else{
					for (ll i=1;i<=n;i++){
						if (ans.find(s[i][0])!=string::npos && ans.find(s[i][1])!=string::npos){
							ans="";
							break;
						}
					}
				}
			}
		}
		cout << "Case #" << t << ": [";
		for (ll i=0;i<ans.size();i++){
			if (i){
				cout << ", ";
			}
			cout << ans[i];
		}
		cout << "]\n";
	}
	return 0;
}
```

---

## 作者：W_C_B_H (赞：0)

从题面不难看出，这道题就是让我们模拟召唤元素和元素之间的反应，那么对于每组测试数据，我们可以在读入可组合的元素、互相对立的元素以及依次召唤的元素后，依次处理每个被召唤的元素。我们记当前的元素列表为 $a$（可以使用 STL 中的 vector 充当），并维护一个数组 $cnt$，其中 $cnt_i$ 表示从 $\verb!A!$ 往后第 $i$ 个大写字母目前在列表中有几个（用于快速检查列表中是否有互相对立的元素）。

每次召唤一个元素时，先将其插入到 $a$ 末尾并更新对应的 $cnt$ 值，随后检查该元素是否会造成反应（如果目前 $a$ 的长度小于 $2$，则可以直接跳过检察环节，因为至少需要两个元素才有可能发生反应）。注意此处应该先检查组合反应再检查互相对立的元素，因为互相对立的元素清空列表的要求是“它没有立即与其他元素组合成新元素”。

因为元素组合的要求是“这对元素出现在元素列表的末尾”，故我们只需检查列表中最后两个元素即可。记目前 $a$ 中最后两个元素为 $x,y$，枚举每一个组合关系，如果 $x,y$ 满足了它的要求，就弹出 $a$ 中最后两个元素、插入新合成的元素并更新对应的 $cnt$ 值。随后可以跳过对剩下的组合关系的检查，因为组合关系只可能是两个基础元素合成一个非基础元素，故召唤一个元素后最多进行一次组合。接下来，枚举每一对互相对立的元素，如果它们对应的 $cnt$ 值均大于 $0$，则直接将 $a$ 清空，并把所有 $cnt_i$ 赋值为 $0$，然后跳过剩下的检查（因为列表已经是空的了）。

最后输出列表中剩余的元素即可。注意输出格式。总时间复杂度 $O(T\cdot N\cdot (C+D))$，可以通过本题。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int r=0; char c=getchar(); bool f=0;
	while(c<48 || c>57){ if(c=='-'){ f=1; } c=getchar(); }
	while(c>=48 && c<=57){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return f?-r:r;
}
string readstr()
{
	string r=""; char c=getchar();
	while(c==' ' || c=='\n' || c=='\r') c=getchar();
	while(c!=' ' && c!='\n' && c!='\r' && c!=EOF){ r+=c; c=getchar(); }
	return r;
}
void write(int x)
{
	if(x<0){ putchar('-'); x=-x; }
	if(x>9){ write(x/10); }
	putchar(x%10+48);
}
void write(string x){ for(char c:x) putchar(c); }
void writeln(int x){ write(x); putchar('\n'); }
void writeln(string x){ write(x); putchar('\n'); }
int T,C,D,n,cnt[26];
string c[40],d[30],s;
vector<char>a;
signed main()
{
	T=read();
	for(int t=1;t<=T;t++)
	{
		// 初始化 
		a.clear();
		for(int i=0;i<26;i++)
		{
			cnt[i]=0;
		}
		
		// 输入 
		C=read();
		for(int i=1;i<=C;i++)
		{
			c[i]=readstr();
			c[i]=" "+c[i];	// 方便以 1 作为起始下标 
		}
		D=read();
		for(int i=1;i<=D;i++)
		{
			d[i]=readstr();
			d[i]=" "+d[i];	// 方便以 1 作为起始下标 
		}
		n=read();
		s=readstr();
		s=" "+s;	// 方便以 1 作为起始下标 
		
		// 依次处理每个被召唤的元素 
		for(int i=1;i<=n;i++)
		{
			a.push_back(s[i]);
			cnt[s[i]-'A']++;	// 维护当前每一种元素在列表中的个数 
			if(a.size()<2)
			{
				continue;
			}
			
			// 处理元素的组合 
			int p=a.size();
			char x=a[p-1], y=a[p-2];
			for(int j=1;j<=C;j++)
			{
				if((x==c[j][1] && y==c[j][2]) || (y==c[j][1] && x==c[j][2]))
				{
					a.pop_back();
					a.pop_back();
					a.push_back(c[j][3]);
					cnt[x-'A']--;
					cnt[y-'A']--;
					cnt[c[j][3]-'A']++;
					break;
				}
			}
			
			// 处理对立的元素 
			for(int j=1;j<=D;j++)
			{
				if(cnt[d[j][1]-'A']>0 && cnt[d[j][2]-'A']>0)
				{
					a.clear();
					for(int i=0;i<26;i++)
					{
						cnt[i]=0;
					}
					break;
				}
			}
		}
		
		// 输出 
		write("Case #");
		write(t);
		write(": [");
		for(int i=0;i<a.size();i++)
		{
			if(i>0)
			{
				write(", ");
			}
			putchar(a[i]);
		}
		writeln("]");
	}
	return 0;
}
```

---

