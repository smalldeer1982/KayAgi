# [ABC370C] Word Ladder

## 题目描述

有两个由小写英文字母组成的字符串 $S$ 和  $T$ 。其中保证 $S$ 和 $T$ 的长度相等。

新开一个数组 $X$ ，并重复以下操作，直到
$S$ 与 $T$ 相等：

更改 $S$ 中的一个字符，并将修改之后的 $S$ 添加到到 $X$ 的末尾。

求以这种方式获得的元素数量最少的字符串数组 $X$ 。如果有多个这样的数组，其元素数量最少，输出字典序最小的一个即可。

## 样例 #1

### 输入

```
adbe
bcbc```

### 输出

```
3
acbe
acbc
bcbc```

## 样例 #2

### 输入

```
abcde
abcde```

### 输出

```
0```

## 样例 #3

### 输入

```
afwgebrw
oarbrenq```

### 输出

```
8
aawgebrw
aargebrw
aarbebrw
aarbebnw
aarbebnq
aarbeenq
aarbrenq
oarbrenq```

# 题解

## 作者：zeroflows (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc370_c)

## 简要题意

给两个序列 $S$ 和 $T$，输出的第一个数是它能改变的总个数，后面跟着的第 $i$ 个是改变 $i$ 个数之后，字典序最小的结果。

## 思路

当 $S$ 与 $T$ 相等的话，那就无法改变了，直接输出 $0$。

---

对于总数只要 $T_i \ne S_i$ 那它就可以改，所以只要 $T_i \ne S_i$ 答案就加一。
- 要让字典序最小，那我们从前面开始枚举，只要 $T_i < S_i$ 就替换，然后输出。
- 否则如果 $T_i > S_i$ 记录位置。等枚举完后，从后往前把记录的位置也换了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000],t[1000],ss[1000];
int n,qw,h[100000000];
main()
{
	ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	cin>>s>>t;
	if(s==t)
	{
		cout<<0;
		return 0;
	}
	n=qw=strlen(s);
	for(int i=0;i<n;i++)
	ss[i]=s[i];
	int qq=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]==t[i])
			continue;
		qq++;
	}
	cout<<qq<<endl;
	qq=0; 
	for(int i=0;i<n;i++)
	{
		if(s[i]==t[i])
			continue;
		if(s[i]<t[i])
		{
			h[++qq]=i;
			continue;
		}
		s[i]=t[i];
		cout<<s<<endl;
	}
	for(int i=qq;i>=1;i--)
	{
		int j=h[i];
		s[j]=t[j];
		cout<<s<<endl;
	}
}
```

---

## 作者：linch (赞：3)

## 题意
给定两个长度相等字符串 $S,T$，每次可以在 $S$ 中修改一个字符，求出最少要修改几次让 $S$ 变为 $T$。同时，需要输出字典序最小的修改方案。

## 思路
由于每次只能修改 $S$ 中的一个字符，将 $S$ 变为 $T$ 需要修改的次数即为两个字符串中字符不同的位数。

接下来考虑字典序最小的方案。

每次修改时，都有两种情况：要么把字典序小的字母修改为字典序大的字母，要么把字典序大的字母修改为字典序小的字母。

要求字典序最小，容易发现修改第二种情况会使原单词字典序变小，第一种情况则会变大。因此，需要先修改第二种情况的字符。

在第二种情况下，可以先修改靠前的字符，这样使后面所有字符串都受到这次修改的影响，一定最优。

第一种情况则反之，要在第二中情况全部修改完成后从后往前修改。我们可以使用递归来实现这一方案。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
const int maxn=1e3+10;
bool c[maxn];
int cnt,len;
void find(int i){
	if(i>=len) return;
	if(c[i]){
		if(s[i]<t[i]){//上述第一种情况，放在后面修改。
			find(i+1);//递归返回后再修改。
			s[i]=t[i];
			cout<<s<<"\n";
		}
		else{//上述第二种情况，优先修改。
			s[i]=t[i];
			cout<<s<<"\n";
			find(i+1);//修改后继续递归。
		}
	}
	else{
		find(i+1);
	}
}
int main(){
	cin>>s>>t;
	len=s.length();
	for(int i=0;i<len;i++){
		if(s[i]!=t[i]){
			c[i]=true;
			cnt++;
		}//如果字符不同。
	}
	cout<<cnt<<"\n";
	find(0);//递归输出。
	return 0;
}
```

[赛时 AC 记录](https://atcoder.jp/contests/abc370/submissions/57531527)

---

## 作者：sz_jinzikai (赞：2)

# 思路
显然，修改偏大的数有益，所以我们要先从前往后修改偏大的数。修改偏小的数有害，所以我们要在修改完所有偏大的数后从后往前修改偏小的数。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n;
string a, b;
vector <int> v1, v2;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> a >> b, n = a.size ();
	for (int i = 0; i < n; ++ i)
		if (a[i] < b[i])
			v1.emplace_back (i);
		else if (a[i] > b[i])
			v2.emplace_back (i);
	cout << v1.size () + v2.size () << '\n';
	for (const int& i : v2)
		a[i] = b[i], cout << a << '\n';
	reverse (v1.begin (), v1.end ());
	for (const int& i : v1)
		a[i] = b[i], cout << a << '\n';
	I AK IOI
}
```

---

## 作者：fanfanhao (赞：1)

# ABC370C
这道题就是一道贪心。首先，输出串的个数一定是字符串 $S$ 和 $T$ 中不同的字符的个数。接着，我们只需从前往后遍历，如果 $S_i>T_i$ 则将 $S_i$ 变成 $T_i$ 然后输出 $S$ 。\
最后从后往前遍历，如果 $S_i<T_i$ 将 $S_i$ 变成 $T_i$ 然后输出 $S$ 即可。\
代码奉上
```cpp
#include<iostream>
using namespace std;
int main()
{
	string s, t;
	cin >> s >> t;
	bool flag = 0;
	int cnt = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != t[i]) {
			cnt++;
		}
	}
	cout << cnt << endl;
	if (cnt == 0) {
		return 0;
	}
	for (int i = 0; i < s.length(); i++) {
		if (s[i] > t[i]) {
			s[i] = t[i];
			cout << s<<"\n";
		}
	}
	for (int i = s.length() - 1; i >= 0; i--) {
		if (s[i] != t[i]) {
			s[i] = t[i];
			cout << s<<"\n";
		}
	}
}

---

## 作者：zzhbpyy (赞：1)

### [C - Word Ladder](https://atcoder.jp/contests/abc370/tasks/abc370_c)

## 分析

为使 $X$ 最短，显然只用修改 $S$ 与 $T$ 所有不同的位置。为了让 $X$ 字典序最小，可以直接找到最小的 $x$ 满足 $S_x$ 大于 $T_x$ 进行修改。若没有满足要求的 $x$，就找到尽量大的 $y$ 满足 $S_y$ 小于 $T_y$ 进行修改。如此循环操作直到 $S$ 与 $T$ 相等。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
string s,t;
signed main(){
    cin>>s>>t;int n=s.length();
	vector<string>ss;//存储每次修改后的S
	while(s!=t){
		int lst=-1;
		for(int i=0;i<s.length();i++){
			if(s[i]!=t[i]&&s[i]>t[i]){
				s[i]=t[i];//找到最小的x就跳出来
				goto A;
			}
			if(s[i]!=t[i])lst=i;
		}
		s[lst]=t[lst];//否则找尽量大的y进行修改
		A:;ss.push_back(s);
	}
	cout<<ss.size()<<'\n';
	for(auto i:ss)cout<<i<<'\n';
}
```

---

## 作者：hjyowl (赞：1)

### 题目大意

给定你两个字符串 $s$，$t$。要求把 $s$ 改为 $t$，中途可以替换 $s$ 中任意一个字母，记录 $s$ 中途所有的值，要求字典序最小，输出中途所有的值。

### 思路：

明显，我们肯定先把 $s$ 中字典序大于 $t$ 中字典序的字母优先替换（而且肯定是越在前面的越早替换），如果替换完了，那么就从后面开始把 $s$ 中字典序小于 $t$ 的给替换，从后往前因为这样可以让字典序最小。

### 时间复杂度分析：

由于每次枚举时间复杂度 $\Theta(n)$，然后还有一直替换知道两个相等，故时间复杂度 $\Theta(n^2)$。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s,t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> s >> t;
	vector<string>vec;
	do{
		if (s == t){
			break;
		}
		bool flag = 0;
		for (int i =0 ; i < s.size(); i ++ ){
			if (s[i] > t[i]){
				s[i] = t[i];
				flag = 1;
				break;
			}
		}
		if (!flag){
			for (int i = s.size() - 1; i >= 0; i -- ){
				if (s[i] < t[i]){
					s[i] = t[i];
					break;
				}
			}
		}
		vec.push_back(s);
	}while (s != t);
	cout << vec.size() << endl;
	for (int i = 0 ; i < vec.size(); i ++ ){
		cout << vec[i] << endl;
	}
	return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

# 题解：AT_abc370_c [ABC370C] Word Ladder

设字符串长度为 $n$，$x$ 为满足 $S_i \neq T_i$ 的 $i$ 的个数。

答案中操作的最小次数为 $x$，每个操作都选择一个 $S_i \neq T_i$ 并将 $S_i$ 替换为 $T_i$。

现在考虑操作的顺序。因为我们可以以任何顺序选择 $S_i \neq T_i$ 并替换 $S_i$ 为 $T_i$，所以为了得到字典序最小的结果，只需要尝试所有可能的操作并决定执行结果最小的操作即可。

数据范围极小，简单的暴力枚举就足够了。

时间复杂度为 $O(n^3)$。

---

## 作者：MLE_Automaton (赞：1)

# 题目解析
给你两个字符串 $S$ 和 $T$，让你将 $S$ 一个一个字符变为 $T$，答案要求**字典序最小**。（[不知道字典序的点这里](https://oi-wiki.org/string/basic/#%E5%AD%97%E5%85%B8%E5%BA%8F)）

我们先看大体，因为字典序要求最小，所以可以先把变小的字符变小，再把变大的字符变大。再看细节，按什么顺序呢，还是因为字典序的定义，应该把好的（变小的）放前面先做，把不好的（变大的）放后面先做。运用了贪心思想。

时间复杂度：$O(n^2)$。

# Talk is cheap, show me the code!
```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i=(a);i<=(b);i++)
#define pre(i, a, b) for(int i=(a);i>=(b);i--)
#define INF 0x3f3f3f3f
#define llINF 0x3f3f3f3f3f3f3f3f
#define bigpq(type) priority_queue<type>
#define smpq(type) priority_queue<type,vector<type>,greater<type>>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
/**********************************************************************
    test03.cpp created by Dennis2013 on 07-09-2024 周六 at 20:15:51
**********************************************************************/
int n; char s[105], t[105];
int main()
{
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1);
    int cnt = 0;
    rep(i, 1, n) if (s[i] != t[i]) cnt ++;
    printf("%d\n", cnt); //先统计变化数
    for (;;) //从这里变小
    {
        int p = 0;
        rep(i, 1, n) //正序
            if (s[i] > t[i])
            {
                p = i; break;
            }
        if (p == 0) break;
        s[p] = t[p];
        printf("%s\n", s + 1); //每次输出变化
    }
    for (;;) //从这里变大
    {
        int p = 0;
        pre(i, n, 1) //倒序
            if (s[i] < t[i])
            {
                p = i; break;
            }
        if (p == 0) break;
        s[p] = t[p];
        printf("%s\n", s + 1);
    }
    return 0;
}
```

---

## 作者：QianXiquq (赞：1)

根据题意，需要记录下字符串 $S$ 通过每次改变一个字符转换成字符串 $T$ 的过程，并且要求字典序最小。

我们贪心地考虑这个问题，可以发现需要优先处理**排在前面**且**字典序较大**的单个字符（即让排在前面的字典序大的字符出现时间尽量**短**）。

在此之后，如果 $S$ 与 $T$ 仍然不等，那么倒序处理**排在后面**的单个字符（即让排在前面的字典序小的字符出现时间尽量**长**）。

贪心正确性没有问题，代码如下：


```cpp
#include <bits/stdc++.h>

using namespace std;
string q[105];
int cnt = 0;

int main(){
	string a, b; cin >> a >> b;
	int len = a.length();

	for (int i = 0; i < len; i++){ //优先处理排在前面且字典序较大的单个字符
		if (a[i] > b[i]){
			a[i] = b[i];
			q[++cnt] = a;
		}
	}
	if (a != b){
		for (int i = len - 1; i >= 0; i--){ //倒序处理排在后面的单个字符
			if (a[i] != b[i]){
				a[i] = b[i];
				q[++cnt] = a;
			}
		}
	}

	cout << cnt << '\n';
	for (int i = 1; i <= cnt; i++)
		cout << q[i] << '\n';
	return 0;
}
```

---

## 作者：zhoumurui (赞：0)

### 题面展示

给你两个由小写英文字母组成的字符串 $S$ 和 $T$。其中，$S$ 和 $T$ 的长度相等。

设 $X$ 为空数组，重复下面的操作直到 $S$ 等于 $T$：

- 更改 $S$ 中的一个字符，并将 $S$ 追加到 $X$ 的末尾。

找出这样得到的元素个数最少的字符串数组 $X$。如果存在多个元素个数相同的数组，请找出其中字典序最小的一个。

### 题目思路

建议评橙。

先思考 $X$ 的元素个数最少是多少。其实 $X$ 的元素个数就是你将 $S$ 转化为 $T$ 所用的步数。

而我们至少要多少步呢？

显然，对于一个位置 $i$，如果 $S_i \not = T_i$，那么这位必须修改；如果 $S_i = T_i$，那么这位就根本不需要动了。

下一个问题是，如何让 $X$ 的字典序最小。

先说答案：我们找到最小的 $i$ 使得 $S_i  < T_i$，如果没有，就找到最大的 $i$ 使得 $S_i > T_i$，对这个 $i$ 进行修改。

找最小的 $i$ 使得 $S_i  < T_i$ 的原因：先考虑修改后的字符串的字典序能不能小于原字符串。在这种情况下，$i$ 越靠前，修改后的字符串的字典序越小，答案显然越优。

找最大的 $i$ 使得 $S_i > T_i$ 的原因：

因为修改后的字符串的字典序必定大于原字符串，我们想要修改后对字符串字典序的影响最小，所以在最靠后的位置修改。

复杂度为 $O(N^2)$，可以通过此题。

### 核心代码展示

```cpp
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string a,b;
    cin>>a>>b;
    int n=a.size(),m=0;
    for (int i=0;i<n;i++){
        if (a[i]!=b[i])m++;
    }
    cout<<m<<"\n";
    while (m--){
        int flag=1;
        for (int i=0;i<n;i++){
            if (a[i]>b[i]){
                flag=0;
                a[i]=b[i];
                cout<<a<<"\n";
                break;
            }
        }
        if (flag){
            for (int i=n-1;i>=0;i--){
                if (a[i]!=b[i]){
                    a[i]=b[i];
                    cout<<a<<"\n";
                    break;
                }
            }
        }
    }
	return 0;
}
```

---

## 作者：yangzimu0131 (赞：0)

显然可以发现，答案为 $S$ 和 $T$ 中 $S_i \neq T_i$ 的个数

接下来考虑操作的顺序。

当 $S_i$ 被替换为 $T_i$ 时，如果是 $S_i < T_i$，那么字符串在字典序上会变大；如果是 $S_i > T_i$，那么字符串在字典序上会变小。

因此，我们先从头到尾遍历一遍 $S$ 和 $T$，如果 $S_i > T_i$ 那么就将 $i$ 存入数组。接着，我们从尾到头遍历一次，如果 $S_i < T_i$ 那么将 $i$ 存入数组。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[20010],cnt;
signed main()
{
	string sa,sb;
	cin>>sa>>sb;
	int n=sa.length();
	for(int i=0;i<=n-1;i++)
	{
		if(sa[i]>sb[i])
			a[++cnt]=i;
	}
	for(int i=n-1;i>=0;i--)
	{
		if(sa[i]<sb[i])
			a[++cnt]=i;
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
	{
		sa[a[i]]=sb[a[i]];
		cout<<sa<<endl;
	 } 
	return 0;
}
```

---

## 作者：liluhexuan (赞：0)

~~最开始读错题了，以为是要让 $x$ 里的字母种类最少~~

先考虑 $m$。很明显，把 $s$ 修改成 $t$ 的最少次数一定是这两个字符串不同字符的个数（因为只有这些字符需要改）。所以 $m$ 等于$s$ 和 $t$ 中不同字符的个数。

接下来循环 $m$ 次，每次从前向后遍历一遍 $s$。如果一个需要修改的字符修改后变小了，那我肯定要修改它，并且跳出循环。否则就修改最靠后的那个字符。

更简单的说，每次我们修改最靠前的修改了后会变小的字符，如果没有就修改最靠后的需要修改字符。

代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
char s[105],t[105];
int main(){
	cin>>s+1>>t+1;
	int n=strlen(s+1),m=0;
	for(int i=1;i<=n;i++){
		if(s[i]!=t[i])
			m++;
	}
	cout<<m<<endl;
	for(int i=1;i<=m;i++){
		int flg=0;
		for(int j=1;j<=n;j++){
			if(s[j]==t[j]) continue;
			if(s[j]>t[j]){
				s[j]=t[j],flg=0;
				break;
			}
			flg=j;
		}
		if(flg) s[flg]=t[flg];
		cout<<s+1<<endl;
	}
	return 0;
}

```

---

## 作者：He_XY (赞：0)

### 题意

给你字符串 $S$ 和 $T$，每次操作可以更换 $S$ 中的一个字符，最终要把 $S$ 变成 $T$，要求操作步骤数量最少，输出变化过程。

当有多种答案存在时，输出 把变化过程排在一起后 **字典序** 最小的那一种

### 思路

贪心：
$$
\begin{cases}
若S[i]=T[i]，不变 \\
若S[i]<T[i]，从前往后变 \\
若S[i]>T[i]，从后往前变
\end{cases}
$$
更准确地说，先从前往后换 $S[i]<T[i]$ 的 $i$，再从后往前换 $S[i]>T[i]$ 的 $i$。

### C++ 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
vector<int> sm,bg;
vector<string> ans;
int main(){
	cin>>s>>t;
	for(int i=0;i<s.length();i++){
		if(s[i]<t[i]){
			bg.push_back(i);
		}else if(s[i]>t[i]){
			sm.push_back(i);
		}
	}
    for(int i=0;i<sm.size();i++){
        s[sm[i]]=t[sm[i]];
        ans.push_back(s);
    }
    for(int i=bg.size()-1;i>=0;i--){
        s[bg[i]]=t[bg[i]];
        ans.push_back(s);
    }
    cout<<ans.size()<<endl;
	for(string x:ans){
		cout<<x<<endl;
	}
	return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

## 解题思路：
由于要**字典序最小**，所以我们每次修改从最前面出发找到**第一个修改后字典序变小的字母**修改。如果没有，则从**最后一个字母开始找到第一个需要修改的字母**并修改即可。

注意先输出次数可以先统计不同字母个数，也可以中途计算。注意特判一下 $0$。

## CODE：

```cpp
#include <iostream>
#include <vector>
using namespace std;
int cnt, len;
string a, b;
vector <string> ans;
int main()
{
  cin >> a >> b;
  len = a.size() - 1;
  while (a != b)
  {
    int now = -1;
    for (int i = 0; i < len; i++)
    {
      if (a[i] > b[i])
      {
        now = i;
        break;
      }
    }
    if (now == -1)
    {
      for (int i = len; i >= 0; i--)
      {
        if (a[i] != b[i])
        {
          now = i;
          break;
        }
      }
    }
    a[now] = b[now];
    ans.push_back(a);
    ++cnt;
  }
  cout << cnt << '\n';
  if (cnt == 0) return 0;
  for (auto it : ans) cout << it << '\n';
  return 0;
}
```

---

## 作者：gutongxing2030 (赞：0)

## 思路
最小此时明显就是每一个位置上面不一样的位置之和。

于是我们只需要保证字典序最小就行。

考虑怎么做到字典序最小。

- 对于 $a_i>b_i$ 的操作，它一定会将字典序变小，我们一定要先执行这些操作，并按照 $i$ 从小到大执行。
- 对于 $a_i<b_i$ 的操作，它一定会将字典序变大，我们一定要后执行这些操作，并按照 $i$ 从大到小执行。

## Code

```cpp
// Problem: C - Word Ladder
// Contest: AtCoder - Toyota Programming Contest 2024#9（AtCoder Beginner Contest 370）
// URL: https://atcoder.jp/contests/abc370/tasks/abc370_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
//#define int long long
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');};
	}
	void write(int x,char y){write(x);write(y);}
	string a,b;
	vector<int> v1,v2;
	signed main(){
		cin >> a >>b;
		for(int i = 0;i<a.size();i++){
			if(a[i]==b[i]) continue;
			if(a[i]<b[i]) v2.push_back(i);
			else v1.push_back(i);
		}
		reverse(v2.begin(),v2.end());
		cout << v1.size()+v2.size() << endl;
		for(int i:v1){
			a[i] = b[i];
			cout << a << endl;
		}
		for(int i:v2){
			a[i] = b[i];
			cout << a << endl;
		}
		return 0;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
//	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

---

## 作者：ToastBread (赞：0)

开局 6 min 33 sec 切 C，赢！

## 题意简述

现有两个**长度相同**字符串 $S,E$，你每次可以更改字符串 $S$ 中的一个字符，直到该字符串变为 $E$。要求修改次数**尽可能少**，且**修改组成的字符串数组的字典序最小**。输出最小的修改次数与字典序最小修改方法。

什么是字符串数组的字典序？

首先，题目保证了修改次数尽可能少。

对于两个长度相同的字符串数组 $X_1,X_2$，考虑记两个字符串 $S_1=X_{1,1},X_{1,2},\ldots,X_{1,n}$ 和 $S_2=X_{2,1},X_{2,2},\ldots,X_{2,n}$.

显然两个字符串长度相同。此时字典序较小的字符串 $S$ 对应的字符串数组 $X$ 的字典序较小。
## 题目解法
显然最少的操作步数是两个字符串不相等的字符个数。

接着分析字典序。

要让字典序尽可能小，我们可以：
1. **从前向后**扫描，若该位置可以让字典序变小，则变换。
1. **从后向前**扫描，若该位置可以让字典序变大，则变换。

为什么？

我们希望**对字典序变化后字典序最小的操作越靠前**，根据字典序的判断得：**越靠前的字符对字典序的影响越大**，所以把字典序减小的操作要从前向后做。

增大的操作也是同样的道理。

实现较简单，具体的实现细节可以参考我的代码。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t,x; 
int n;
int main()
{
	cin>>s>>t;
	x=s;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i]!=t[i]) n++;//操作次数统计
	}
	cout<<n<<endl;//最小操作次数
	for(int i = 0; i < s.size(); i++)//从前向后
	{
		if(s[i]>t[i])//字典序减小
		{
			x[i]=t[i];
			cout<<x<<endl;
		}
	}
	for(int i = s.size()-1; i >= 0; i--)//从后向前
	{
		if(s[i]<t[i])//字典序最大
		{
			x[i]=t[i];
			cout<<x<<endl;
		}
	}
	return 0;//华丽结束
}

---

## 作者：WuMin4 (赞：0)

# [\[ABC370C\] Word Ladder](https://www.luogu.com.cn/problem/AT_abc370_c)

## 简要题意

给出两个字符串 $s,t$ 和一个空序列 $x$，每次可以更改 $s$ 中的一个字符并将 $s$ 添加到 $x$ 后面，问最少需要多少次可以将 $s$ 变成 $t$ 并且 $x$ 的字典序最小。

## 思路

最少操作次数很好求，只需要求出两个字符串相同位置不同字符的数量。现在的问题是如何让字典序最小。\
采用贪心思想，先顺序遍历字符串 $s$。如果更改一个字符后这个字符串小于原字符串（即更改的字符比原字符小），那么就优先修改这个位置。修改完后就只剩下了大于该位置的字符，因为修改这些位置后字符串会大于原字符串，所以再倒序遍历，修改剩余的字符。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string s,t;
vector<string> ans;
signed main() {
	cin>>s>>t;
	for(int i=0;i<s.length();i++)
		if(s[i]>t[i])
			s[i]=t[i],ans.push_back(s);
	for(int i=s.length()-1;i>=0;i--)
		if(s[i]<t[i])
			s[i]=t[i],ans.push_back(s);
	cout<<ans.size()<<endl;
	for(string v:ans)
		cout<<v<<endl;
	return 0; 
}
```

---

## 作者：Cosine_Func (赞：0)

给定两个字符串 $S,T$，求出将字符串 $S$ 修改为 $T$ 的字典序最小的操作序列 $X$。

首先，如果整个序列按字典序排列，那么每一步也必然是字典序最小的修改方法。对于每一步，考虑暴力枚举可能的修改方式，并求出字典序最小的一个，加入序列 $X$。时间复杂度 $O(N^2\log N)$，空间复杂度 $O(N)$，其中 $N$ 是字符串 $S$ 的长度。

核心代码如下：
```cpp
while(s!=t){
	vector<string> ss;
	for(unsigned i=0;i<s.length();i++){
	if(s[i]!=t[i]){
		string _s=s;
			_s[i]=t[i];
			ss.pb(_s);
		}
	}
	sort(ss.begin(),ss.end());
	x.pb(ss[0]);
	s=ss[0];
}
```

[参考代码](https://atcoder.jp/contests/abc370/submissions/57540707)

---

## 作者：卷王 (赞：0)

很容易想到一种贪心思路：

* 先交换每一个位置 $i$，满足 $s_i>t_i$（$i$ 从小到大交换）

* 然后交换每一个位置 $j$，满足 $s_j<t_j$（$j$ 从大到小交换）

这样就可以保证字典序最小。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
bool vis[107];
int tt[107],cnt=0,ss[107],cnt2=0;
char s[107],t[107];
inline bool cmp(int x,int y){
	return x>y;
}
signed main() {
	cin>>(s+1)>>(t+1);int ls=strlen(s+1),lt=strlen(t+1);
	ans=ls;
	for(int i=1;i<=ls;i++){
		if(s[i]>t[i])tt[++cnt]=i;
		if(s[i]==t[i])vis[i]=1,ans--;
		if(s[i]<t[i])ss[++cnt2]=i;
	}
	sort(ss+1,ss+cnt2+1,cmp);
	cout<<ans<<"\n";
	for(int i=1;i<=cnt;i++){
		s[tt[i]]=t[tt[i]];
		cout<<(s+1)<<"\n";
	}
	for(int i=1;i<=cnt2;i++){
		s[ss[i]]=t[ss[i]];
		cout<<(s+1)<<"\n";
	}
	return 0;
}
```

---

## 作者：wei2013 (赞：0)

## 思路：
模拟题，如果要使字典序最小，那么要先将前面的改为 $t_i$ 后字典序会变小的先改掉，再从后往前找不同的改成 $t_i$ 即可，因为剩下的一定是字典序会变大的。
## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
vector <string> ans;
signed main(){
	string s,t;
	cin>>s>>t;
	for(int i=0;i<s.size();i++){
		if(s[i]!=t[i] && s[i]>t[i]){//从前往后找到改后字典序会变小的
			s[i]=t[i];
			ans.push_back(s);
		}
	}
	for(int i=s.size()-1;i>=0;i--){
		if(s[i]!=t[i]){//从后往前找不同的（字典序改后会变大的）
			s[i]=t[i];
			ans.push_back(s);
		}
	}
	cout<<ans.size()<<endl;
	for(int i=0;i<ans.size();i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：天使宝贝 (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/AT_abc370_c)

### 题目大意
现有两个字符串 $S$ 和 $T$，要让 $S$ 变为 $T$，求一种变化方案，使得这种方案的字典序最小。

### 思路&分析
很明显，我们可以分两种情况看：

* 设当前所在的位置为 $i$，那么当 $S_i$ 大于 $T_i$ 时，就要改变 $S_i$，因为这样能使字典序变小。
* 当 $S_i$ 小于 $T_i$ 时，改变了就会使字典序变大，因此我们在这里需要倒着修改 $S_i$。

于是，我们就愉快的解决了此题。

### CODE

[赛时代码](https://atcoder.jp/contests/abc370/submissions/57525801)

---

## 作者：Ryzen_9_7950X (赞：0)

# 思路：
我们充分发扬人类智慧：\
将字符串 $S$ 与 $T$ 不同的地方记录下来，然后按修改后的 $S$ 排序\
根据编程直觉，在排序后，修改结果一定是按字典序的排序结果\
所以我们按排序后的数组直接修改即可\
这样速度快到飞起，在本题中都可以在 1ms 内卡过
# 代码：
我们通过以上的思路，得到以下的代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
string a,b,temp1,temp2;
bool cmp(int x,int y)
{
    temp1 = temp2 = a;
    temp1[x] = b[x];
    temp2[y] = b[y];
    return temp1 < temp2;
}
int main()
{
    cin >> a >> b;
    int ans = 0;
    vector<int> x;
    for(int i = 0;i < a.size();i++)
    {
        if(a[i] != b[i])
        {
            ans++;
            x.push_back(i);
        }
    }
    cout << ans << endl;
    sort(x.begin(),x.end(),cmp);
    for(int i = 0;i < x.size();i++)
    {
        a[x[i]] = b[x[i]];
        cout << a << endl;
    }
    return 0;
}
```

---

## 作者：crz_qwq (赞：0)

- 用一个字符串 $cur$ 存储现在的字符串，用 $nxt$ 存储可以到达的下一个字符串的集合，也就是 $cur$ 和 $T$ 中字符不同的地方可以修改，每次取 $nxt$ 中字典序最小的那个字符串更新 $cur$ 并且记录即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
vector<string>nxt,ans;
signed main()
{
	string s,t;
	cin>>s>>t;
	int n=s.size();
	s="#"+s;t="#"+t;
	string cur=s;
	while(cur!=t)
	{
		nxt.clear();
		for(int i=1;i<=n;++i)
			if(cur[i]!=t[i])
			{
				char tmp=cur[i];
				cur[i]=t[i];
				nxt.emplace_back(cur);
				cur[i]=tmp;
			}
		sort(nxt.begin(),nxt.end());
		cur=nxt[0];
		ans.emplace_back(cur);
	}
	cout<<ans.size()<<'\n';
	for(auto &e:ans)
		cout<<e.substr(1)<<'\n';
}
```

---

## 作者：zhengyi0402 (赞：0)

# ABC370 C题题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc370_c)

## 解题思路

看看数据范围：

$S$，$T$ 的长度均小于 $100$。

$S$，$T$ 的长度相等。

看到这，dfs 大佬们是不是想用 dfs 了？

我一开始也被 dfs 麻痹了，所以没通过好几次。

这次，我换了一个想法。

我们定义 $x$ 为 $S$ 的长度。

首先，统计 $S$ 和 $T$ 差了多少个字符，并记为 $num$。

之后输出 $num$，作为答案的第一行。

然后一重循环，从 $1$ 到 $num$。

之后在里面再套一重循环，从 $0$ 循环到 $x$，也就是遍历这两个字符串。

然后判断 $S_i$ 是否等于  $T_i$。

如果不相等，那就对 $S$ 进行一次假修改，并判断假修改完的字符串是否是在这一次修改中字典序最小的，并和 $ans$ 字符串打擂台。

最后输出这个字符串即可。

## 代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;
    int num = 0;
    for(int i = 0;i < s.size();++i){
    	if(s[i]!=t[i])num++;
	}
	cout<<num<<endl;
	for(int i = 1;i <= num;i++){
		string te="";
		for(int j = 0;j < s.size();j++){
			if(s[j]!=t[j]){
				char tt = s[j];
				s[j]=t[j];
				if(te>s||te==""){
					te=s;
				}
				s[j]=tt;
			}
		}
		cout<<te<<endl;
		s=te;
	}
    return 0;
}

```
[提交记录](https://atcoder.jp/contests/abc370/submissions/57540128)

**切记：不准抄袭，否则后果自负！**

---

