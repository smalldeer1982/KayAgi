# Suffix Structures

## 题目描述

Bizon the Champion 不仅是一头普通的野牛，他还是“野牛队”的明星。

在一次比赛中，“野牛队”遇到了一个问题：“给定两个不同的单词 $s$ 和 $t$，需要将单词 $s$ 转换成单词 $t$。” 队员们认为这道题很简单，因为他们对后缀数据结构非常熟悉。Bizon Senior 擅长使用后缀自动机，他可以通过这种工具每次删除字符串中的一个字符。Bizon Middle 则对后缀数组了如指掌，他可以在字符串中任意交换两个字符。他们虽然对后缀树并不了解，但后缀树能够实现更多的功能。

Bizon the Champion 想知道“野牛队”能否完成这个任务。也许答案并不需要同时使用这两种数据结构。请判断他们是否能完成任务，如果能，是如何实现的？是只需要使用后缀自动机，还是只需用后缀数组，或者是需要两者兼用呢？注意，任何一种结构都可以无限次使用，且使用顺序不受限制。

## 说明/提示

在第三个样例中，你可以先利用后缀自动机删除第一个字符，把“both”变成“oth”，然后利用后缀数组进行两次交换得到“hot”。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
automaton
tomat
```

### 输出

```
automaton
```

## 样例 #2

### 输入

```
array
arary
```

### 输出

```
array
```

## 样例 #3

### 输入

```
both
hot
```

### 输出

```
both
```

## 样例 #4

### 输入

```
need
tree
```

### 输出

```
need tree
```

# 题解

## 作者：achjuncool (赞：2)

# 题目大意

后缀自动机：可以删除某个字符串里的任意字符。

后缀数组：可以交换字符串中的任意两个字符。

给定两个字符串 $s$ 跟 $t$。

问如何将 $s$ 经过上面两个操作后变成 $t$：

1. 只用后缀自动机，输出 `automaton`。
1. 只用后缀数组，输出 `array`。
1. 两个都用，输出 `both`。
1. 上述方法都不行，输出 `need tree`。

# 思路

由于数据保证能只用后缀自动机就不能只用后缀数组（反之亦然），所以我们只需要先判断只使用后缀自动机或者只使用后缀数组能不能解决，不能就判断能不能两个都使用能不能解决，还不行就 `need tree` 了。

只用后缀自动机：判断 $s$ 是否为 $t$ 的子序列，我这里使用双指针。

只用后缀数组：判断 $s$ 是否为 $t$ 的所有字符的一种排列，我这里使用字符计数，只要所有字符的数量相等即可。

两个都用：判断 $s$ 是否为 $t$ 的某个子序列的一种排列，我这里还是用字符计数，只要所有字符在 $s$ 中的数量小于等于在 $t$ 中的数量即可。

# Code

注释的 `//` 后面加空格只是个人习惯（

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
string a, b;
ll cnta[256], cntb[256]; // 字符计数数组
int main(){
	qwq;
	cin >> a >> b;
	// 后缀数组 
	if(a.length() == b.length()){
		for(ll i = a.length() - 1; i >= 0; i--) cnta[a[i]]++;
		for(ll i = b.length() - 1; i >= 0; i--) cntb[b[i]]++;
		bool flag = true;
		for(ll i = 'a'; i <= 'z'; i++){
			if(cnta[i] != cntb[i]){
				flag = false;
				break;
			}
		}
		if(flag){
			cout << "array" << endl;
			return 0;
		}
	}
	// 后缀自动机
	if(b.length() < a.length()){
		ll apos = 0, bpos = 0, check = 0;
		for(bpos = 0; bpos < b.length(); bpos++){
			for(; apos < a.length(); apos++){
				if(a[apos] == b[bpos]){
					apos++;
					check++;
					break;
				}
			}
		}
		if(check == b.length()){
			cout << "automaton" << endl;
			return 0;
		}
	}
	// both
	for(ll i = a.length() - 1; i >= 0; i--) cnta[a[i]]++;
	for(ll i = b.length() - 1; i >= 0; i--) cntb[b[i]]++;
	bool flag = true;
	for(ll i = 'a'; i <= 'z'; i++){
		if(cnta[i] < cntb[i]){
			flag = false;
			break;
		}
	}
	if(flag){
		cout << "both" << endl;
		return 0;
	}
	// tree
	cout << "need tree" << endl;
	return 0;
}
```

---

## 作者：HadrianZhang (赞：1)

# 题意

两个字符串 $s$ 和 $t$，有两种操作，分别为删除一个字符和交换两个字符的位置。判断需要用哪一种操作，或都用，或无解。

# 思路

- 只删除字符：转化成判断 $t$ 是否为 $s$ 的子序列，数据小可以 $n^2$ 检查。

- 只交换位置：转化为判断 $s$ 和 $t$ 包含的字符是否**完全相同**，开两个桶统计即可。

- 两种操作都用：转化为 $t$ 的所有字符在 $s$ 里是否全都**出现过**，一样开桶统计。对于每个字符，判断其在 $s$ 中的数量是否大于等于在 $t$ 中的数量。

- 无解：最简单，以上三种情况都未成功。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int cnt1[205],cnt2[205];
bool check1()//检查是否为子序列
{
	int pos=0;
	for(int i=0;i<t.size();i++)
	{
		if((pos=s.find(t[i],pos))==-1) return 0;
		pos++;
	}
	return 1;
}
bool check2()//检查不考虑位置，字母是否完全相同
{
	for(int i=1;i<=200;i++)
		if(cnt1[i]!=cnt2[i]) return 0;
	return 1;
}
bool check3()//检查是否全部包含
{
	for(int i=1;i<=200;i++)
		if(cnt1[i]<cnt2[i]) return 0;
	return 1;
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>s>>t;
    //计数
	for(int i=0;i<s.size();i++)
		cnt1[s[i]]++;
	for(int i=0;i<t.size();i++)
		cnt2[t[i]]++;
	if(check1()) cout<<"automaton";
	else if(check2()) cout<<"array";
	else if(check3()) cout<<"both";
	else cout<<"need tree";
	return 0;
}

---

## 作者：Tenshi (赞：0)

## 分析

约定两个字符串分别为 $a,b$。

不妨先考察一下只需要两个操作之一的字符串的特征：

- 可以发现只需要 `automaton` 的时候其实是 $b$ 为 $a$ 的子序列，这个用双指针扫一下就行。

- 然后只需要 `array` 的时候二者一定等长，而且字符集和对应的个数的相等。

接下来看看是否为 `both`，其实就是判断一下对于每种字符是否 $a$ 串的个数都**大于等于** $b$ 串的。

否则只能 `need tree`。

```cpp
// Problem: B. Suffix Structures
// Contest: Codeforces - Codeforces Round #256 (Div. 2)
// URL: https://codeforces.com/contest/448/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
 
#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()
 
#define x first
#define y second
using pii = pair<int, int>;
using ll = long long;
 
inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

string a, b;

bool subset(map<char, int> &a, map<char, int> &b){
	for(auto [x, y]: a){
		if(b[x]<y) return false;
	}
	return true;
}

signed main(){
	cin>>a>>b;
	int n=a.size(), m=b.size();
	if(m>n){
		puts("need tree");
		return 0;
	}
	map<char, int> fir, sec;
	for(auto i: a) fir[i]++;
	for(auto i: b) sec[i]++;
	if(n==m){
		puts(fir==sec? "array": "need tree");
		return 0;
	}
	
	bool ng=false;
	int idx=0;
	for(auto i: b){
		while(idx<n && a[idx]!=i) idx++;
		if(idx==n) ng=true;
		else idx++;
	}
	if(!ng){
		puts("automaton");
		return 0;
	}
	
	puts(subset(sec, fir)? "both": "need tree");
	
	return 0;
}
```

---

