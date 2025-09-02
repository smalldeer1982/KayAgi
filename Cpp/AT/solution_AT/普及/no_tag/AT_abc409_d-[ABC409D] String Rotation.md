# [ABC409D] String Rotation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc409/tasks/abc409_d

给定一个长度为 $N$ 的由小写字母组成的字符串 $S=S_1S_2\dots S_N$。你需要对 $S$ 执行恰好一次以下操作：

- 选择 $S$ 的一个长度至少为 1 的连续子串，将其向左循环移位 1 次。具体来说，选择整数 $1 \leq \ell \leq r \leq N$，将 $S$ 的第 $\ell$ 个字符插入到第 $r$ 个字符的右侧，然后删除 $S$ 的第 $\ell$ 个字符。

请找出所有可能的操作后 $S$ 中字典序最小的字符串。

共有 $T$ 个测试用例，请对每个测试用例给出答案。

## 说明/提示

### 约束条件

- $1 \leq T \leq 10^5$
- $1 \leq N \leq 10^5$
- $S$ 是由小写字母组成的长度为 $N$ 的字符串
- $T$ 和 $N$ 为整数
- 单个输入文件中所有测试用例的 $N$ 之和不超过 $10^5$

### 样例解释 1

- 对于第 1 个测试用例，选择第 2 到第 7 个字符进行循环移位，得到 `acodert` 是字典序最小的结果。
- 对于第 2 个测试用例，无论如何操作都只能得到 `x`。
- 对于第 3 个测试用例，选择第 1 到第 2 个字符进行循环移位，得到 `nsuke` 是字典序最小的结果。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
7
atcoder
1
x
5
snuke```

### 输出

```
acodert
x
nsuke```

# 题解

## 作者：heyx0201 (赞：1)

## 题意
给定一个长度为 $n$ 的字符串 $s$，你可以选择一个区间，将这个区间向左移动一位。具体来说，你可以选择两个整数 $1 \lt l \le r \le n$，然后使 $s_{l - 1} \leftarrow s_l, s_l \leftarrow s_{l + 1}, \dots, s_r \leftarrow s_{l - 1}$。

求操作后字典序最大的字符串。
## 思路
首先理清字典序的概念：两个字符串从小到大比较，遇到**第一个**不同的字符，两字符串字典序大小关系就是这两个字符的字典序大小关系。

要将一个子段向左移动一位，且字典序最大，那么 $s_l$ 的字典序一定要大于 $s_{l - 1}$ 的，这样才会更优。所以我们可以把 $l$ 定为第一个满足 $s_i > s_{i - 1}$ 的 $i$。

起点已经决定了，终点怎么求呢？看起来是 $l$ 后面满足 $s_i < s_{i - 1}$ 的第一个 $i$。但是考虑到 $s_{l - 1}$ 要换到 $s_r$ 的位置，所以同样要考虑 $s_i < s_{l - 1}$。如果两者都满足，那么 $r \ge i$ 的答案一定不会更优。

注意有可能整个字符串都选不出更优的答案，此时需要特判。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n;
string s;

void Solve() {
  cin >> n >> s;
  int l = 0, r = n - 1;
  for (int i = 1; i < n; i++) {
    bool k = s[i] < s[i - 1];
    if (k && !l) l = i;
    if (!k && l && s[i] > s[l - 1]) {
      r = i - 1;
      break;
    }
  }
  for (int i = 0; i < l - 1; i++) {
    cout << s[i];
  }
  for (int i = l; i <= r; i++) {
    cout << s[i];
  }
  if (l > 0) {
    cout << s[l - 1];
  }
  for (int i = r + 1; i < n; i++) {
    cout << s[i];
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  for (cin >> T; T--; Solve());
  return 0;
}
```

---

## 作者：fish_love_cat (赞：1)

酱油选手来写题解了。

---

翻译：

给一个字符串 $s$，你可以进行恰好一次操作：选择一个字符删掉，然后在其右侧选择一个位置（包括原位置）插回去。你需要最小化其字典序。

---

可以插原位那就不一定要改，先把不改的情况判掉。

然后因为是字典序所以从前往后冒泡就行了。

这怎么能是黄。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
    int n;
    cin>>n;
    string a;
    cin>>a;
    string b;
    b=a;
    sort(b.begin(),b.end());
    if(a==b){
        cout<<a<<'\n';
        return;
    }
    int sum=1;
    for(int i=0;i<n-1&&sum<=2;i++){
        if(sum&1){
            if(a[i]>a[i+1])sum++,swap(a[i],a[i+1]);
        }else{
            if(a[i]<a[i+1])sum++;
            else swap(a[i],a[i+1]);
        }
    }
    cout<<a<<'\n';
}
signed main(){
    int t=1;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Jerry20231029 (赞：1)

## 思路

实际上题目的操作可以简化成任意选择一个字符，然后将这个字符向后移任意位。

如果我们选择将 $S_i$ 后移，那么 $S_{i+1}$ 会补上来，如果 $S_{i+1} < S_i$，那么 $S$ 的字典序就变小了。

由于比较字典序是从前往后依次比较，所以改小 $S$ 中越前的字符，$S$ 的字典序就变得越小，所以可以用贪心做。我们从前往后遍历 $S$，把找到的第一个满足 $S_i > S_{i+1}$ 的 $S_i$ 往后移。

移到哪呢？还是贪心，从 $i+1$ 往后遍历，移到第一个 $S_i < S_j$ 的 $j$ 前面，$j-1$ 这个位置就会减少，所以移到这里。

## 代码

[AC 记录](https://atcoder.jp/contests/abc409/submissions/66606046)

```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(){
	int T,n,e;
	string s;
	for(cin>>T; T--; cout<<'\n'){
		cin>>n>>s;
		for(int i = 0; i < n-1; i++){
			if(s[i] > s[i+1]){
				e = n-1;
				for(int j = i+1; j < n; j++){
					if(s[i] < s[j]){
						e = j-1;
						break;
					}
				}
				rotate(s.begin()+i,s.begin()+i+1,s.begin()+e+1);
				break;
			}
		}
		cout<<s;
	}
	return 0;
}
```

---

## 作者：Inzaghi_Luo (赞：1)

### 分析
由于是字典序最小，因此从前往后扫，找到第一个 $s_i<s_{i+1}$ 的地方，这里就是操作的 $l$。然后继续往后扫，因为最后 $s_r$ 会变成 $s_l$，所以我们比较 $r$ 和 $r+1$ 可以发现如果 $s_{r+1} \leq s_l$ 那么右端点右移就不劣，所以每个串扫一遍就好了。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 300005;
	char ch[MAXN];
	int main(){
		int T;
		scanf("%d", &T);
		while(T--){
			int n;
			scanf("%d%s", &n, ch + 1);
			int l = 0, r = 0;
			for(int i = 1;i < n;i++){
				if(ch[i + 1] < ch[i]){
					l = i, r = i + 1;
					while(r < n){
						if(ch[r + 1] <= ch[l]) r++;
						else break;
					}
					break;
				}
			}
			char tmp = ch[l];
			for(int i = l + 1;i <= r;i++) ch[i - 1] = ch[i];
			ch[r] = tmp;
			printf("%s\n", ch + 1);
		}
		return 0;
	}
}
int main(){
	return Luo_ty::main();
}//International Milan is the best team.
```

---

## 作者：hyc1207 (赞：1)

# 题目大意
## 问题描述
给定一个长度为 $N$ 的字符串 $S$，该字符串由小写英文字母组成。您需要对 $S$ 执行以下操作**一次**：  
选择 $S$ 的一个连续子串（长度至少为 1），并将其**向左循环移动一位**。即，选择整数 $1 \le l \le r \le N$，将 $S$ 的第 $l$ 个字符插入到第 $r$ 个字符的右侧，然后删除 $S$ 的第 $l$ 个字符。  
在所有可能的操作结果中，找出**字典序最小**的字符串。  
输入包含 $T$ 个测试用例，请对每个测试用例进行求解。
## 数据范围
* $1 \le T,N \le 10^5$ 
* 在单个输入文件中，所有测试用例的 $N$ 之和最多为 $10^5$。
# 主要思路
## 贪心算法
想要使操作后得到的字符串字典序最小，只需使下标较小的字符在 ASCII 码中尽量小。  
如果我们发现某个位置 $i$ 满足 $s[i] > s[i+1]$，那么我们可以选择从 $i$ 开始的一个子串，将 $s[i]$ 移动到子串最后，使得在位置 $i$ 处出现一个比 $s[i]$ 小的字符，从而降低字典序。  
所以，我们只需找到第一个满足  $s[i] > s[i+1]$ 的字符 $s[i]$，从这个字符开始，向后找到比 $s[i]$ 小的字符，将 $s[i]$ 放在这个字符后。同时我们希望 $s[i]$ 被插入到尽可能靠后的位置，这样对前面部分顺序的影响最小。所以需要找到第一个 $i < j < n$ 满足 $s[j] > s[i]$，并处理区间 $[i,j-1]$。
```cpp
for (int i = 0; i < n-1; i++)
{
    if (s[i] > s[i+1])
    {
        int j = i+1;
        while (j < n && s[j] <= s[i]) ++j;
        return cal(s,i,j-1,n);
    }
}
```
## 字符串处理
将一个长度为 $n$ 的字符串的一个区间 $[i,j]$，进行题目中的操作后，举例可发现得到的新字符串 $p$ 的表达式如下（$s[i,j]$ 表示字符串 $s$ 中下标为 $i$ 的字符到下标为 $j$ 的字符所组成的字符串；符号 + 表示字符串的拼接）。  
$$
p = s[0,i-1] + s[i+1,j] + s[i] + s[j+1,n-1]
$$
```cpp
p = s.substr(0,(i-1)-0+1) + s.substr(i+1,j-(i+1)+1) + s[i] + s.substr(j+1,(n-1)-(j+1)+1);
//s.substr(i,j) 表示 s 从下标为 i 的字符开始组成的长度为 j 的字符串
```
化简括号内的式子并封装成函数得到：
```cpp
string cal(string s, int i, int j, int n)
{
	return s.substr(0,i) + s.substr(i+1,j-i) + s[i] + s.substr(j+1,n-1-j);
}
```

最终，每一组数据中，时间复杂度为 $O(N)$，可以通过。
# AC Code
```cpp
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
string cal(string s, int i, int j, int n)
{
	return s.substr(0,i) + s.substr(i+1,j-i) + s[i] + s.substr(j+1,n-1-j);
}
string solve(int n, string s)
{
    for (int i = 0; i < n-1; i++)
    {
        if (s[i] > s[i+1])
        {
            int j = i+1;
            while (j < n && s[j] <= s[i]) ++j;
            return cal(s,i,j-1,n);
        }
    }
	return s;  //如果 n 为 1 时，则不会进入循环，直接返回原字符串
}
int main()
{
    int t;
    cin >> t;
    while (t--)
	{
        int n;
        string s;
        cin >> n >> s;
        cout << solve(n,s) << endl;
    }
    return 0;
}
```

---

## 作者：All_Wrong_Answer (赞：1)

[AT 题目传送门](https://atcoder.jp/contests/abc409/tasks/abc409_d)

[luogu 题目传送门](https://www.luogu.com.cn/problem/AT_abc409_d)

## 题目大意：

多次询问，每次询问给出一个长度为 $N$ 字符串 $S$，要求对 $S$ 进行恰好一次操作，内容是选择 $S$ 中的一段 $[l,r]$，把 $S_{l-1}$ 插入到 $S_{r}$ 的后面。

求进行一次操作后字典序最小的情况。

## 思路：

**贪心题**，题目中**恰好**一次其实并没有意义，只要选择 $l=r$，操作后就是原字符串，所以不用考虑原字符串字典序最小的情况。

具体到贪心操作，先找到一个最小的 $j$ 使 $s_{j+1}$ 的字典序小于 $s_j$，那么显然为了使字典序小就要吧 $s_{j+1}$ 放到 $s_{j}$ 前面去，这样就确定的操作序列的左端点。接下来考虑 $s_{j}$ 可以放在哪里，是要找到一个 $k$ 满足 $S_k$ 字典序大于 $S_{j}$ 且 $k>j$，因为如果在 $S_k$ 之前放就是把一个字典序大的插在了字典序小的前面，显然是劣的，这样右端点也确定了，执行操作输出即可。

## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
char a[1000005],ls[1000005];
signed main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int g;
		cin>>g;
		cin>>a;
		int s=strlen(a);
		int flag=-114514,wz=1145141;
		for(int j=0;j<s;j++){
			if(a[j+1]>=a[j]) continue;
			for(int k=j+1;k<s;k++){
				if(a[k]>a[j]){
					wz=k;
					break;
				}
			}
			flag=j;
			break;
		}
		for(int j=0;j<s;j++){
			if(j==flag) continue;
			if(j==wz) cout<<a[flag];
			cout<<a[j];
		}
		if(wz==1145141&&flag!=-114514) cout<<a[flag];
		cout<<endl;
	} 
	return 0; 
}
```

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc409_d [ABC409D] 字符串旋转 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc409_d)

### 题目大意

给出字符串 $S$，选择一个 $S$ 的子串，将之最左侧字符移到最右侧后，将子串覆盖回原串。求可能的最小字典序字符串。

### 思路及实现

字典序满足越高位越重要，同时此时所有结果都等长，所以考虑贪心。

旋转的实质是将一段字符串向前移动一格，也可能不移动。前面位权重更大，这个操作影响到的最大的是被移动到后面，由恰好后一位者替代的那一位。

所以贪心寻找从前往后第一位后面比前面强的一位，如果没有则不移动，反之从这位开始，将这位移动到后面。

接着考虑这位放到那里，这个也会影响答案。简单的方法是把后半段字符串中每一位和移动的这位比较，把从前往后第一位不如移动位小的那一位放到移动位后面。

最后合并即可。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, N; string S;
int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		cin >> S;
		int flag = S.length() - 1;
		for (int i = 0; i < S.length() - 1; i++)
		{
			if (S[i] > S[i + 1])
			{
				flag = i;
				break;
			}
		}
		string T = S.substr(0, flag), bi = S.substr(flag + 1, S.length() - flag - 1);
		char ci = S[flag];
		flag = bi.length();
		for (int i = 0; i < bi.length(); i++)
			if (ci < bi[i])
			{
				flag = i;
				break;
			}
		T += bi.substr(0, flag);
		T += ci;
		T += bi.substr(flag, S.length() - flag);
		cout << T << endl;
	}
	return 0;
}
```

---

## 作者：cqbzhzf (赞：0)

### 题目描述
给定一个长度为 $N$ 且只由小写字母组成的字符串 $S$。其中 $1\le N\le 1\times 10^5$。

你可以进行**一次**以下操作：

- 将一个字符 $S_i$ 移动至 $S_j$ 和 $S_{j+1}$ 之间成为新的字符串。其中 $1\le i \le N$，$i+1\le j < N$。

在所有可能的操作结果中，找出字典序最小的字符串。

共有 $T$ 组测试数据（$1\le T\le 1\times 10^5$）。
### 思路
既然只能进行一次操作且要保证字典序最小，再结合数据范围，那么容易想到贪心。

考虑怎么贪才最优。

字典最小那么一定要保证越前面的字符字典序最小。所以对于开头段字典序递增的字符不作处理。

假设 $i$ 是第一个使得 $S_i$ 的字典序大于 $S_{i+1}$ 的字典序的位置（$1\le i <N$）。这时，显而易见的需要对 $i$ 进行移动。同理，由于要保证字典序最小,将 $S_i$ 移动到第一个 $j$ 使得 $S_j$ 的字典序大于 $S_i$ 的字典序的前面即可（$i< j \le N$）。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
string s;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>s;
		if(n==1)
		{
			cout<<s<<"\n";
			continue;
		}
		for(int i=0;i<n-1;i++)
		{
			if(s[i]>s[i+1])
			{
				int j;
				char tmp=s[i];
				for(j=i+1;j<n-1;j++)
				{
					if(s[i]<s[j+1])
						break;
				}
				s.erase(i,1);
				s.insert(j,1,tmp);
				break;
			}
		}
		cout<<s<<"\n";
	}
	return 0;
}
```

---

## 作者：piano_pei (赞：0)

### [题目传送门(Atcoder)](https://atcoder.jp/contests/abc409/tasks/abc409_d)

### 题意

给定小写英文字符串 $S_{[1,n]}$，你可以选择两个数 $1\leq x\leq y\leq n$，并将 $S_x$ 插入到 $S_y$ 后一位。求插入后能得到的字典序最小的 $S$，多测。

### 思路

考虑依据字典序特性贪心。假设有一个 $i$ 使得 $S_i>S_{i+1}$，我们肯定得把 $S_i$ 换掉，并且 $i$ 越小越好，因为越往前的字符对字典序的贡献越大。那么 $S_i$ 插到哪里呢？同理，找一个最小的 $j$ 使得 $S_i<S_j$，并将 $S_i$ 插入到 $S_j$ 前面。如果本来所有字符都单调不递减，不用插；如果 $i$ 后面的字符均小于等于 $S_i$，插到最后。时间复杂度 $O(\sum n)$，可以通过。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t, n;
	string s, ans;
	cin >> t;
	while(t--)
	{
		cin >> n >> s;
		ans = "";
		if(n == 1)
		{
			cout << s <<"\n";
			continue;
		}
		int id = -1;
		for(int i = 0;id == -1 && i < n - 1;++i)
			if(s[i + 1] < s[i])
				id = i;
		if(id == -1)
		{
			cout << s << "\n";
			continue;
		}
		ans = s.substr(0, id);
		int j = -1;
		for(int i = id + 1;j == -1 && i < n;++i)
		{
			if(s[i] > s[id])
			{
				j = i;
				ans += s.substr(id + 1, i - 1 - id) + s[id] + s.substr(i, s.size());
			}
		}
		if(j == -1)
		{
			ans += s.substr(id + 1, s.size());
			ans.push_back(s[id]);	
		}
		cout << ans << "\n";
	}
	return 0;
}

```

---

## 作者：Ivan422 (赞：0)

你说的对但是这题比较容易吗？感觉全场除 G 最难，没救了。

### 题意

给你一堆字符串，每个字符串可以选择一个字符移到后面去（可以移到最后面）求操作后最小字典序。当然因为你可以选择最后一个字符移到后面去，所以你可以选择什么也不做。

### 思路

万恶结论题。首先考虑找到那些可以**改变字典序**的位置。我们发现，当 $s_i>s_{i+1}$ 时，交换这两个可以改变字典序。那么我们发现交换最前面的一组字符**可以满足最小字典序**。

这对吗？显然有问题。我们**不一定是只交换一个字符**，也就是说我们可以跨过多个字符。我们发现这时候相当于给了我们**冒泡移过去**的机会，不停比对这个多的字符直到改变反而会增加字典序为止。

注意处理**没找到合法位置**的情况，输出原字符串 $s$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10;
int n;
string s;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		cin>>s;
		int i=0,j=0;
		for(i=0;i<n-1;i++){
			if(s[i]>s[i+1]){
				j=i+1;
				while(j<n&&s[j]<=s[i])++j;
				break;
			}
		}	
		if(j==0)
			cout<<s<<"\n";
		else{
			for(int p=0;p<n;p++){
				if(p==i)
					continue;
				if(p==j)
					cout<<s[i];
				cout<<s[p];
			}
			if(j==n)
				cout<<s[i];
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Ybw0731 (赞：0)

## 思路
考虑一个贪心思路。


如果发现（第一次）一个字母比前一个字母小，那么就交换，继续往后检查，发现逆序就交换（仅限连续），直到不能不能交换为止。


AC 代码：



```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define endl "\n"
using namespace std;
const int N=1e5+5;
const int INF=0x3f3f3f3f;
const double EPS=1e-6;
const int MOD=998244353;
int n;
string s;
void solve(){
	cin>>n>>s;
	if(n==1){
		cout<<s<<endl;
		return;
	}
	bool f=0;
	int l,r;
	for(int i=1;i<n;i++){
		if(s[i]>s[i-1]&&f)break;
		if(s[i]<s[i-1]&&!f)f=1;
		if(f)swap(s[i],s[i-1]);
	}
    cout<<s<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

