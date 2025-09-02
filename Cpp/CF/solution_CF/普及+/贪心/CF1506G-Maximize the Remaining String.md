# Maximize the Remaining String

## 题目描述

给你一个由小写英文字母组成的字符串 $s$，你需要去掉一部分字符，使得操作后得到的字符串 $t$ 满足在 $s$ 中出现的字母每种只保留一个并且最大化 $t$ 的字典序。

## 样例 #1

### 输入

```
6
codeforces
aezakmi
abacaba
convexhull
swflldjgpaxs
myneeocktxpqjpz```

### 输出

```
odfrces
ezakmi
cba
convexhul
wfldjgpaxs
myneocktxqjpz```

# 题解

## 作者：liangbowen (赞：17)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1506G)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1506g)

校内考试题目。写一篇题解。

## 思路

首先记录每个字符出现了多少次，然后创建**单调栈**。

看当前字符是否入栈，如果没有入栈，就不停 `pop()`，直到：

+ 栈空了。
+ 栈顶字典序大于当前字符。
+ 栈顶元素已经被删掉了（因为栈外面用 `cnt[i]` 记录了每个数的次数）。

满足单调栈要求后，压入当前字符。

不管是不是将当前字符压入栈了，都要将**对应计数器减一**。

最后，整个栈**从下往上**就是答案了。

如果使用 STL 的 `stack`，需要反着输出，这一点自己模拟一下栈的操作，就能理解了。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
void fastio()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
}
const int N = 30;
int cnt[N];
bool instk[N];
void solve()
{
	memset(cnt, 0, sizeof(cnt)); //多测不清空，爆零两行泪！！！
	memset(instk, false, sizeof(instk));
	string s;
	cin >> s;
	int len = s.length();
	for (int i = 0; i < len; i++) cnt[s[i] - 'a']++;
	stack <int> stk; //单调栈 
	for (int i = 0; i < len; i++)
	{
		int x = s[i] - 'a';
		if (!instk[x])
		{
			while (!stk.empty() && cnt[stk.top()] && x > stk.top()) instk[stk.top()] = false, stk.pop();
		    stk.push(x), instk[x] = true; //没进栈就进栈 
		}
		cnt[x]--; //删除掉一个
	}
	string ans = "";
	while (!stk.empty()) ans += (stk.top() + 'a'), stk.pop();
	reverse(ans.begin(), ans.end());
	cout << ans << '\n';
}
int main()
{
	fastio();
	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：SpeedStar (赞：10)

#### 算法分析

本题实际上就是让我们求 $s$ 字典序最大的子序列，该子序列包含 $s$ 的所有不同字符，且只包含一次。
可以考虑贪心，从前往后扫描每个字符，在扫描的时候用另外一个字符串 $T$ 去记录下当前的答案是多少，每次去判断一下 $T$ 的最后一个字母 $T_j$，如果 $T_j < S_i$ 且 $T_j$ 这个字母可以被删掉（也就是后面还出现过）则删掉 $T_j$。

不难看出不删 $T_j$ 的方案的字典序显然不如删掉 $T_j$ 的的方案的字典序大，所以最优解一定是删掉 $T_j$ 的方案。

同时这题lc上有原题：[去除重复字母](https://leetcode-cn.com/problems/remove-duplicate-letters/submissions/)


#### C++ 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using std::cin;
using std::cout;
using std::string;
using std::map;

int main() {
	int t;
	cin >> t;

	while (t--) {
		string s, stk;
		cin >> s;
		map<char, bool> ins;
		map<char, int> last;
		for (int i = 0; i < s.size(); ++i) last[s[i]] = i;
		
		rep(i, s.size()) {
			if (ins[s[i]]) continue;
			while (stk.size() and stk.back() < s[i] and last[stk.back()] > i) {
				ins[stk.back()] = false;
				stk.pop_back();
			}
			stk += s[i];
			ins[s[i]] = true;
		}
		
		cout << stk << '\n';
	}

	return 0;
}
```

---

## 作者：EternalHeart1314 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/CF1506G)

# 题意

对于一个只包含小写字母的字符串 $s$，构造出一个字符串 $t$。保证 $t$ 是 $s$ 的子序列，在 $s$ 里出现过的字母要在 $t$ 里出现过**刚好** 1 次，并且最大化 $t$ 的字典序。

# 思路

创建一个栈和两个数组 $cnt$ 和 $flag$，$cnt_i$ 表示 $i$ 这个字母在 $s$ 里出现了多少次，$flag_i$ 表示 $i$ 这个字母在不在栈里，为 $-1$ 表示不在，为 $0$ 表示在。

遍历 $s$，设当前字符为 $c$：

- 如果 $flag_c=0$，即 $c$ 在栈里，那么删除 $c$，即 $cnt_c$ 减 $1$。

- 如果 $flag_c=-1$，即 $c$ 不在栈里，那么：

	- 设栈顶为 $s$。

		如果：栈不为空，$s$ 出现的次数大于 $1$（即 $flag_s>1$），$c$ 的字典序大于等于 $s$（即在 ASCII 码中，$c\ge s$）。那么：弹出栈顶，并继续执行。

		否则：退出。

~~这上面其实是代码数学化。~~

最后，栈从下向上输出，即为答案。

由于最后要把栈从下向上输出，所以我用了双端队列代替栈。

# Code
```
#include<bits/stdc++.h>
using namespace std;

const int N(1 << 7);
string s;
int t, cnt[N], flag[N];
deque<char> q;	//把 deque 当作 stack 

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> s;
		memset(cnt, 0, sizeof cnt);
		memset(flag, -1, sizeof flag);
		for(int i(0); s[i]; ++ i) {
			++ cnt[s[i]];
		}
		for(int i(0); s[i]; ++ i) {
			if(flag[s[i]]) {	//不在栈里 
				while(q.size() && cnt[q.front()] > 1 && s[i] >= q.front()) {
					flag[q.front()] = -1, -- cnt[q.front()], q.pop_front();
				}		//弹出栈顶时记得把 flag 和 cnt 都更改一下 
				flag[s[i]] = 0, q.push_front(s[i]);	//压入栈 
			} else {
				-- cnt[s[i]];
			}	//在栈里 
		}
		while(q.size()) {
			cout << q.back();
			q.pop_back();
		}
		cout << '\n';
	}
	return 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：OIer_ACMer (赞：1)

~~字符串题为啥要用单调队列？~~

------------
注：本题思路较为简单，所以作者不回顾多赘述证明以及原理，望周知！

------------
## 大致思路：
我们看到这个题可以先思考一下，我们如果想让**最后得到的字符串字典序最大**，那肯定要按字母**从大到小的枚举**，就比如字符串 ```bzbz```，如果要想字符串最大，那肯定要让大的字母尽量在前面，所以我们应该先删除第一个 z 前面的 b，保证在前面的字符尽量大。

为了满足这个操作，我们可以算出我们**最后得到的字符串的长度**，我们刚开始找一个空字符串，然后**就根据原字符串来给这个字符串添字母**，最后得到的字符串就是**原字符串删完以后剩下的最大字符串**。

我们进行模拟的思路就是**从大到小的枚举每一个字母**，如果这个字母出现过，而且他的前面的字母可以删除（可以删除的条件**就是后面必须也出现过这个字母**，因为题目要求每个字母**只能出现一次**），那样我们就可以把这个字母放在我们的空字符串中，因为**我们是从大到小枚举的，所以我们每次放入都是最优的**。

我们可以用一个 $sum_{i,j}$ 来判断前面的字母是否在后面也出现过。$sum_{i,j}$ 表示 $i$ 到 $n$ 中出现 $j$（是这个字符的编码）这个字母的次数。我们设 $cur$ 表示为前面 $1$ 到 $cur$ 那些字母已经被删除没有用了。$nex_{i,j}$ 表示 $i$ 到 $n$ 这些字符中，第一个 $j$ 字符出现的位置。我们可以根据 $sum_{cur,k}-sum_{nex,k}$ 的值来判断是否前面出现过这个字母，并且后面也出现过这个字母。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 2e5 + 1;
int cnt[26], nex[N][26], sum[N][26], use[N], n;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        n = s.length();
        int len = 0;
        for (int i = 0; i < n; i++)
        {
            if (!cnt[s[i] - 'a'])
            {
                len++;
                cnt[s[i] - 'a']++;
            }
        }
        for (int i = 0; i <= 25; i++)
        {
            use[i] = 0;
            cnt[i] = 0;
            nex[n][i] = 0;
            sum[n][i] = 0;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j <= 25; j++)
            {
                sum[i][j] = sum[i + 1][j];
            }
            sum[i][s[i] - 'a']++;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j <= 25; j++)
                nex[i][j] = nex[i + 1][j];
            nex[i][s[i] - 'a'] = i + 1;
        }
        int cur = 0;
        for (int i = 1; i <= len; i++)
        {
            for (int j = 25; j >= 0; j--)
            {
                if (!use[j] && nex[cur][j])
                {
                    int ne = nex[cur][j] - 1;
                    bool st = true;
                    // cout << "cur=" << cur << endl;
                    // cout << "ne=" << ne << endl;
                    for (int k = 0; k <= 25; k++)
                    {
                        if (!use[k] && k != j && sum[cur][k] - sum[ne][k])
                        {
                            if (sum[ne][k] <= 0)
                            {
                                st = false;
                            }
                        }
                    }
                    if (st)
                    {
                        cout << char(j + 'a');
                        use[j] = 1;
                        cur = ne + 1;
                        break;
                    }
                }
            }
        }
        cout << endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122735055)

---

## 作者：20111019Yu (赞：1)

### 题意

给你一个字符串，从中取一个子序列，使得子序列包含原字符串的每一种字符，且字符均只出现过一次，求最大字典序的子序列。

### 思路

我们假设已经有一个子序列 $s$，$s$ 是从 $1$ 到 $i$ 中符合要求的最大字典序子序列。

则当 $s$ 中没有当前字符时，将当前字符与 $s$ 的末尾字符进行比较，分两种情况：

1. 若当前字符比末尾字符字典序大，且末尾字符在之后还有，则将末尾字符删除，$vis$ 标记为 $0$，并重复执行该操作。

1. 若当前字符的字典序不大于 $s$ 的末尾字符字典序，或末尾字符在之后没有了，跳出循环。

若当前 $s$ 中不含该字符，就将当前字符插入 $s$ 的最后面，并将 $vis$ 标记为 $1$。

这些操作可以使用单调队列维护。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s;
map<char, int> cnt;\\记录字符的个数
map<char, bool> vis;\\记录字符是否在字符串内
deque<int> q; 

signed main(){
	cin >> n;
	while(n--){
		cin >> s;
		cnt.clear();
		vis.clear();
		for( int i = 0; i < s.size(); i++ ) cnt[s[i]]++;
		for( int i = 0; i < s.size(); i++ ){
			cnt[s[i]]--;
			while(!q.empty() && cnt[s[q.back()]] && !vis[s[i]] && s[i] > s[q.back()]){
				vis[s[q.back()]] = 0;
				q.pop_back();
			}\\删除操作
			if(!vis[s[i]]){
				q.push_back(i);
				vis[s[i]] = 1;
			}\\插入操作
		}
		while(!q.empty()){
			cout << s[q.front()];
			q.pop_front();
		}\\输出
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Helloworldwuyuze (赞：0)

# CF1506G 题解

## Des

给定字符串 $s$，删掉一些字符得到新的字符串 $t$ 使得原来在 $s$ 出现过的字符必须在 $t$ 中出现。$t$ 中的字符每个出现且仅出现一次。求最后字典序最大的字符串是什么。

## Sol

从前往后考虑一个字符串，如果当前枚举到 $i$，选择的最后一个在 $j$，那么：

- 如果 $s_i>s_j$ 且 $s_j$ 在 $i$ 以后仍在 $s$ 中出现过，那么显然将这里替换成 $s_i$ 是更优的。
- 如果 $s_i>s_j$ 但是 $s_j$ 在 $i$ 以后没有在 $s$ 中出现过，那么显然这里不能够将 $s_j$ 替换掉，而是直接把 $s_i$ 接到 $s_j$ 后面。
- 如果 $s_i < s_j$，那么显然直接把 $s_i$ 放在 $s_j$ 后面即可。
- 如果 $s_i$ 已经在放入队列里面，那么直接不管它。

这就类似于维护一个单调栈的东西，复杂度 $O(n)$。

## Code

```cpp
const int INF = 0x3f3f3f3f;
typedef pair<int,bool> PII;
typedef pair<int,PII> PIII;
const int N = 2e5 + 10;
const int M = 20 + 10;
const int MOD = 1e9 + 7;

int st[N], top, T, cnt[200];
char s[N];
bool inst[200];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>T;
	while(T--){
		cin>>s;
		int n = strlen(s); top = 0;
		for(int i=0;i<n;++i)    ++cnt[s[i]];
		for(int i=0;i<n;++i){
			--cnt[s[i]];
			if(inst[s[i]])  continue;
			while(top && cnt[s[st[top]]] && s[i] > s[st[top]])  inst[s[st[top]]] = false, --top;
			st[++top] = i, inst[s[i]] = true;
		}
		for(int i=1;i<=top;++i) cout<<s[st[i]];
		cout<<endl;
		for(int i=0;i<200;++i)  inst[i] = false, cnt[i] = 0;
	}
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：0)

### 主要做法：

维护一个栈，并依次枚举每个字符。如果当前字符不在栈里且比栈顶小，且栈顶字符后面还会出现，就弹出栈顶字符。最后将当前字符入栈。

### 具体细节：

1. 如何知道栈顶字符后面会不会出现？这里可以预处理出每个字符在字符串中出现的次数，用桶记录。如果枚举完了一个字符，就把桶这个字符的位置减一。询问某个字符以后会不会出现时，只需看桶这个字符的位置是否大于零即可。

2. 用 `stack` 的，注意输出需要反一下（不过我是手写栈，不用）。

3. 多测注意清空。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define int long long
int tt,q[200001],t,cn[201],in[201];//cn:记录出现次数的桶，in:记录是否在栈里，q:栈
string s;
signed main(){
	ios::sync_with_stdio(0),cin>>tt;
	while(tt--){
		cin>>s,memset(in,0,sizeof in),memset(cn,0,sizeof cn),t=0;//清空
		for(int i=0;i<s.size();i++)cn[s[i]]++;//记录次数
		for(int i=0;i<s.size();i++){
			if(!in[s[i]]){
				while(t>0&&s[i]>q[t]&&cn[q[t]])in[q[t]]=0,t--;//出栈
				in[s[i]]=1,q[++t]=s[i];//入栈
			}
			cn[s[i]]--;//枚举完了，自减
		}
		for(int i=1;i<=t;i++)cout<<char(q[i]);
		cout<<'\n';
	}return 0;
}
```

---

## 作者：GFyyx (赞：0)

## 解题思路

因为 $\sum_{i=1}^{n}|s_i| \le 2 \times 10^5$ 所以考虑 $\Theta(s)$ 的贪心做法。

贪心的思路是，假设我们当成统计到的删去重复字符的答案为 stk，对于每一个扫到的字符，记为 $s_i$ 记 stk 字符串最后一个字符为 ```stk.back()```。

记录一个 lp 数组，代表每次字符在字符串中最后一次出现的位置然后我们从前往后扫一遍字符串。

如果 字典序 $s_i$ 大于 ```stk.back()``` 们删去 ```stk.back()```，将 $s_i$ 加在后面可以使得字典序更大，但是如果 ```stk.back()``` 是它同种字符中最后一个了，就不能删了。

代码有些类似单调栈，详见下方代码。

## AC 代码
```cpp
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
int lp[30];bool in[30];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t; cin >> t;
	while(t--){
		string s,stk; cin >> s;
		memset(in,0,sizeof in);//多组数据 
		for(int i=0; i<s.size(); i++)
			lp[s[i]-97]=i;
		for(int i=0; i<s.size(); i++){
			if(in[s[i]-97]) continue;//s[i]在前面出现过 
			while(stk.size()&&stk.back()<s[i]&&lp[stk.back()-97]>i){
				in[stk.back()-97]=0;
				stk.pop_back();//舍去有重复且有字典序更优的字母替代 
			}
			stk+=s[i];//记录可行答案 
			in[stk.back()-97]=1;
		}
		cout << stk << endl;
	}
}
```

## 小提示
```stk.back()``` 与 ```stk.pop_back()``` 函数在 C++11 以下版本无法使用。 

---

## 作者：_zhy (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1506G)。

题目给定一个字符串，我们要把字符串中每个字符都取出来一个，按照原字符串中的顺序组成一个新的字符串，我们要找到字典序最大的字符串。

相当于我们需要把大的字母尽量在前面取出来。

那具体怎么取呢？

我们假设有两个字符，一个 $S1$，一个 $S2$，$S1 < S2$，为了使字典序最大，我们要让 $S1$ 在 $S2$ 右边。但是，若 $S2$ 右边没有 $S1$ 了，那么 $S2$ 就只能在左边。所以我们需要使用一个数组来记录每个字符的数量，再一边使用单调栈进行计算即可。

单这道题的单调栈的优先级并不是简单的大于或小于，正如上面所说的，如果当前字符右边没有栈顶字符了，这个时候也不能出栈。

最后输出站内元素即可。

### code

```cpp
#include <cstdio>
#include <cstring>
#include <stack>
#include <iostream>

using namespace std;

const int N = 2e5 + 5, M = 30;

int n, T, cnt[M];
char a[N];
bool f[M];
string ans;
stack<int> st;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf(" %s", a + 1);
		n = strlen(a + 1);
		for (int i = 1; i <= 26; i++)
			cnt[i] = 0, f[i] = false; 	//多测清空。 
		for (int i = 1; i <= n; i++)
			cnt[a[i] - 'a' + 1]++;	//记录每个字符出现次数。 
		for (int i = 1; i <= n; i++) {
			if (!f[a[i] - 'a' + 1]) {	//这里很重要，因为一个字符只能用一次，所以如果当前字符已经在栈内就不入栈了。 
				while (!st.empty() && cnt[st.top()] && st.top() < a[i] - 'a' + 1)	//栈不空，栈顶字符在当前字符之后还存在且当前字符更大就出栈。 
					f[st.top()] = false, st.pop();	//出栈前将栈顶字符的状态置为不在栈里。 
				st.push(a[i] - 'a' + 1);
				f[st.top()] = true;	//入栈。 
			}
			cnt[a[i] - 'a' + 1]--;	//遍历到下一个字符，将当前字符的数量减1。 
		}
		ans = "";
		while (!st.empty())
			ans = (char)(st.top() + 'a' - 1) + ans, st.pop(); 
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：V1mnkE (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1506G)
## 思路
题目中要求答案字符串的字典序最大，也就是说要让大的字符尽量靠前。

考虑维护一个类似于单调栈的东西，开一个数组记录每个字符在字符串中最后出现的位置。遍历字符串时，记当前字符为 $C$，栈顶字符为 $S_{top}$，在 $C$ 不在栈里时，如果 $C$ 大于 $S_{top}$ 且 $S_{top}$ 不是最后一次出现，就将它弹出，直到 $S_{top}$ 大于 $C$ 为止，然后将 $C$ 压进栈里。

冷知识：字符串支持 ``pop_back``，所以直接用字符串来模拟栈即可，最后答案就是这个字符串。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],b[1005];
int lst[1005];
bool is[1005];
string s,ans;
int main(){
	cin>>n;
	while(n--){
	    memset(is,0,sizeof(is));
		ans="";
		cin>>s;
	    for(int i=0;i<s.size();i++)lst[s[i]]=i;
	    for(int i=0;i<s.size();i++){
	        if(is[s[i]]) continue;
	        while(ans.size()>0&&ans[ans.size()-1]<s[i]&&lst[ans[ans.size()-1]]>i) {
	            is[ans[ans.size()-1]]=0;
	            ans.erase(ans.size()-1,1);
	        }
	        ans+=s[i];
	        is[s[i]]=1;
	    }
	    cout<<ans<<endl;
	}
} 
```

---

## 作者：YangXiaopei (赞：0)

## 前言：

我的题解与其他题解思路相同实现略微不同，没用 `stack`，全篇使用 `string`，不理解者谨慎食用。

## Solution:

考虑贪心。

我们用字符串 $t$ 来存最后的答案。

遍历 $s$，假设此时 $s$ 遍历到第 $i$ 位，$t$ 最后一位为 $t_x$。

* 如果 此时 $t$ 中没有字符，把 $s_i$ 加入 $t$。

* 如果 $s_i$ 在 $t$ 中出现过，退出本次循环。

* 如果 $t$ 中有字符且没有 $s_i$
	
    * **只要** $t_x < s_i$ 且 $t_x$ 在后面还有，把 $t_x$ 删掉
    把 $s_i$ 加入 $t$。
    
在此过程中，只需维护两个数组 $f, vis$，表示每个字母在还会出现几次和在 $t$ 中是否出现过即可。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int q, n, f[35], vis[35];
string s, t;
signed main(){
	cin >> q;
	while(q--){
		cin >> s;
		n = s.size();
		t = "";
		memset(f, 0, sizeof(f));
		memset(vis, 0, sizeof(vis));
		for(int i = 0; i < n; i++){
			f[s[i] - 'a']++;
		}
		for(int i = 0; i < n; i++){
			f[s[i] - 'a']--;
			if(t.size() == 0){
				t = t + s[i];
				vis[s[i] - 'a'] = 1;
			}
			else if(vis[s[i] - 'a']){
				continue;
			}
			else{
				while(t.size() > 0 && t[t.size() - 1] < s[i] && f[t[t.size() - 1] - 'a'] > 0){
					vis[t[t.size() - 1] - 'a'] = 0;
					t = t.substr(0, t.size() - 1);
				}
				t = t + s[i];
				vis[s[i] - 'a'] = 1;
			}
		}
		cout << t << "\n";
	}
	return 0;
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [Maximize the Remaining String](https://www.luogu.com.cn/problem/CF1506G)
## 思路分析
一道贪心题。

可以先记录一个 $lst$ 数组，代表每次字符在这个字符串最后出现的位置。
### 贪心思路
假设我们当前统计到的删去重复字符的答案为 $stk$，对于每一个扫到的字符，记为 $s_i$，记 $stk$ 字符串的最后一个字符为 $last$。

1. 如果 $s_i$ 的字典序大于 $last$ 的字典序，说明我们将 $last$ 并将 $s_i$ 加在答案 $stk$ 的后面可以使得答案的字典序更大。
2. 如果 $last$ 是它同种字符中的最后一个，我们就将它保留下来，否则便删去。

就像这样：
```cpp
void solve(){
    cin>>s;
    string ss;//记录答案的字符串
    int a[26];//记录每个字符最后出现的位置
    bool vis[26];//记录字符是否出现在答案中
    memset(vis,0,sizeof vis);
		for(R i=0; i<s.size(); i++)a[s[i]-'a']=i;
		for(R i=0; i<s.size(); i++){
            //如果当前字符出现在 stk 中，则必定不会比出现在前面更优，跳过
			if(vis[s[i]-'a'])continue;
            //ssl 表示当前答案字符串的最后一个字符是什么
			while(ss.size()&&ssl<s[i]&&a[ssl-'a']>i)
            //如果 s[i]>ssl 且 ssl 并不是它同种字符中的最后一个，那么删除会更优（贪心思路 1）
				vis[ssl-'a']=0,ss.pop_back();
			ss+=s[i],vis[ssl-'a']=1;
		}
		cout<<ss<<'\n';
}
```
## AC 代码
```cpp
#include<bits/stdc++.h>
#define R register int
#define ssl ss.back()
using namespace std;
int T,a[26];string s;
bool vis[26];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>s;string ss;
		memset(vis,0,sizeof vis);
		for(R i=0; i<s.size(); i++)a[s[i]-'a']=i;
		for(R i=0; i<s.size(); i++){
			if(vis[s[i]-'a'])continue;
			while(ss.size()&&ssl<s[i]&&a[ssl-'a']>i)
				vis[ssl-'a']=0,ss.pop_back();
			ss+=s[i],vis[ssl-'a']=1;
		}
		cout<<ss<<'\n';
	}
	return 0;
}

```

---

## 作者：legendgod (赞：0)

[CF1506G](luogu.com.cn/problem/CF1506G)

看到题目要求求的是字典序最大的，观察一下条件发现每一个字符都只能使用一次。所以我们考虑在保证每一个字符都可以取到的条件下，再考虑取字典序最大的。

我们可以暴力维护每一个没有被取到的字符中最靠前的位置，之后再在前面找一个最大的字符，然后比较一下两个字符的大小即可。

发现我们每一个字符只被遍历一次，我们暴力维护了一个长度为 26 的数组，所以复杂度是 $O(26 \sum |s|)$

这边考虑使用递归实现，比较简单。

```cpp
#include <bits/stdc++.h>
using namespace std;

//#define Fread

#ifdef Fread
#define getchar() ((p1 == p2 && p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin)) ? EOF : *p1 ++)
char buf[1 << 21], *p1, *p2;
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c);c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}

const int maxn = 2e5 + 5;
const int maxm = maxn << 1;
const int inf = 0x3f3f3f3f;
typedef int room[maxn];

int n, m;
int a[maxn], b[maxn];
char s[maxn];
int vis[maxn];

#define N 26
string ans;

void Solve(int dep,int yuan) {
    if(dep == 0) return printf("%s\n", ans.c_str()), void();
    int pos, mxx(inf);
    for(int i = 1; i <= N; ++ i) if(!vis[i] && a[i] != 0) if(a[i] < mxx) pos = i, mxx = a[i];
    int mx(0), ps;
    for(int i = yuan + 1; i < min(mxx, n + 1); ++ i) if(vis[b[i]] == 0) {
        if(mx < b[i]) ps = i, mx = b[i];
    }
//    printf("%c %d %c\n", pos + 'a' - 1, mxx, mx + 'a' - 1);
    if(mx >= pos) {
        vis[mx] = 1;
//        printf("%c\n", mx + 'a' - 1);
        ans += mx + 'a' - 1;
        Solve(dep - 1, ps);
    }
    else {
        vis[pos] = 1;
        ans += pos + 'a' - 1;
        Solve(dep - 1, mxx);
    }
}

signed main() {
//    freopen(".in", "r", stdin);
//    freopen("S.out", "w", stdout);
	int i, j, t;
    r1(t);
    while(t --) {
        scanf("%s", s + 1);
        ans = "";
        n = strlen(s + 1);
        int sum(0);
        for(i = 1; i <= 26; ++ i) a[i] = vis[i] = 0;
        for(i = 1; i <= n; ++ i) b[i] = s[i] - 'a' + 1;
        for(i = n; i; -- i) if(!a[b[i]]) a[b[i]] = i;
        for(i = 1; i <= N; ++ i) sum += (bool)(a[i]);
//        printf("sum = %d\n", sum);
//        for(i = 1; i <= N; ++ i) printf("%c : %d\n", i + 'a' - 1, a[i]);
//        printf("T.ask = %d\n", T.ask(1, 1, N, 1, N));
        Solve(sum, 0);
        for(i = 1; i <= n; ++ i) b[i] = 0;

    }
	return 0;
}


```


---

