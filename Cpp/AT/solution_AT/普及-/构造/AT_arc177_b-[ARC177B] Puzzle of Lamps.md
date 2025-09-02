# [ARC177B] Puzzle of Lamps

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc177/tasks/arc177_b

AtCoder さんは、左から右へ一列に並べられた $ N $ 個の豆電球と、$ 2 $ 種類のスイッチ A, B で構成された装置を作りました。各豆電球は、`0` (OFF) と `1` (ON) の $ 2 $ 種類の状態をとります。各スイッチを押すと、以下のことが起こります。

- スイッチ A を押すと、`0` の状態の豆電球のうち一番左のものが `1` になる。
- スイッチ B を押すと、`1` の状態の豆電球のうち一番左のものが `0` になる。
 
なお、該当する豆電球が存在しない場合はスイッチを押せません。

最初、すべての豆電球は `0` の状態になっています。AtCoder さんは、左の豆電球から順に状態が $ S_1,\ S_2,\ \dots,\ S_N $ になっている状態にしたいです。そのためにスイッチをどの順番で何回押せばいいのかを答えてください。ここで、必ずしもスイッチを押す回数を最小化する必要はありませんが、操作を現実的な時間で終わらせるために、スイッチを押す回数は $ 10^6 $ 回以下にしてください。なお、この問題の制約下では、答えが存在することが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 30 $
- $ S_1,\ S_2,\ \dots,\ S_N $ は `0` または `1`
- $ S_1,\ S_2,\ \dots,\ S_N $ がすべて `0` であることはない
- $ N $ は整数
 
### Sample Explanation 1

この出力例で答えているのは、スイッチ A, A, A, B の順に押す操作方法です。以下の図のように、豆電球を目的の状態にすることができます。 !\[ \](https://img.atcoder.jp/arc177/76af43b23a9e1158288d5f3162174c42.png) 別の方法として、スイッチ A, A, B, A, A, B の順に押しても、豆電球を目的の状態にすることができます。これに対応する以下の出力をした場合でも正解になります。 ``` 6 AABAAB ```

## 样例 #1

### 输入

```
5
01100```

### 输出

```
4
AAAB```

# 题解

## 作者：xQWQx (赞：5)

### 前置

[题目链接](https://www.luogu.com.cn/problem/AT_arc177_b)

[AC 记录](https://www.luogu.com.cn/record/167774122)

### 思路

如果要改变序列第 $i$ 位的数字，就至少操作 $i$ 次，其正确性是显而易见的。同时，在操作 $i$ 次以后，其前面的数字也会被改变，由于前面的数都被改变了，我们又要保证与目标序列相同，所以我们可以从后往前遍历，只要找到一个与目标序列不同的数字，重复操作，就可以将前面若干个与目标序列不一样的数字“纠正”，重复直到第一个数字，我们就得到了目标序列。

### 做法

从后往前遍历，用一个变量储存当前状态，遇到不一样的数字，就压入一个队列中，最后输出。

### 代码

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n;//序列长度
char t='0';//状态变量
string s;//序列
queue<char> ans;//答案队列
int main(){
    cin>>n;//输入
    cin>>s;
    for(int i=n-1;i>=0;i--){//从后往前遍历
        if(s[i]!=t){//如果找到一个与当前状态不一样的
            for(int j=1;j<=i+1;j++){//因为要操作 i 次，所以要压入操作 i 次
                if(t=='1') ans.push('B');//如果是1变0，压入 B
                else ans.push('A');//同上
            }
            if(t=='1') t='0';//反转状态
            else t='1';//同上
        }
    }
    cout<<ans.size()<<endl;//操作次数
    while(ans.size()){//输出操作
        cout<<ans.front();
        ans.pop();
    }
    return 0;
}
```

---

## 作者：xuchuhan (赞：2)

## 思路

发现一个问题：对于样例 $\texttt{01100}$，我们无法直接到达原序列 $\texttt{00000}$ 的第 $2$ 位，将其修改成目标序列的 $\texttt{1}$。因为如果我们想到达原序列的第 $2$ 位进行修改，那么它必须是从左往右数第一位 $\texttt{0}$ 或 $\texttt{1}$，也就是说它不能与第 $1$ 位相同。但显然此时第 $1,2$ 位的元素均为 $\texttt{0}$。

那么如何修改到呢？

将第 $1$ 位的元素修改为 $\texttt{1}$，此时第 $2$ 位就变成了第一位 $\texttt{0}$，不就可以将第 $2$ 位的元素也修改为 $\texttt{1}$ 了吗？再将第 $1$ 位修改为 $\texttt{0}$，我们不就实现了将前 $2$ 位元素对应目标序列了吗？

推广至普遍情况：对于长度为 $k$ 的目标序列 $\texttt{00\dots01}$，其中最左边有 $k-1$ 个 $\texttt{0}$。想将原序列修改为目标序列，我们可以先将所有元素均修改为 $\texttt{1}$，再将前 $k-1$ 个元素修改为 $\texttt{0}$。这样就可以将原序列修改为目标序列了。

但是还有一个问题。对于序列 $\texttt{01001}$，如果我们按刚才的方法，顺序在原序列上，将在目标序列上元素为 $\texttt{1}$ 的下标对应值修改，那么会有如下一番景象：$\texttt{00000}\rightarrow\texttt{11000}\rightarrow\texttt{01000}\rightarrow\texttt{11111}\rightarrow\texttt{00001}$。

我们发现：原本已经修改好的第 $2$ 位的 $\texttt{1}$ 没了。因为在修改第 $5$ 位的 $\texttt{1}$ 时，将前 $4$ 位都变为 $\texttt{0}$ 了。

如何处理？

倒序将原序列修改不就行了。

仍然是这个例子，此时会有：$\texttt{00000}\rightarrow\texttt{11111}\rightarrow\texttt{00001}\rightarrow\texttt{11001}\rightarrow\texttt{01001}$。修改成功了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt;
string s;
vector<int>v;
vector<char>vec;
int main(){
	cin>>n>>s;
	for(int i=s.size()-1;i>=0;i--){//倒序,原因详见题解 
		if(s[i]=='0')
			continue;
		v.push_back(i+1);//得到需要修改为1的下标 
	}
	for(int i=0;i<v.size();i++){
		//对于每个下标x: 
		for(int j=1;j<=v[i];j++)
			vec.push_back('A');
		//先将前x个元素修改为1 
		for(int j=1;j<v[i];j++)
			vec.push_back('B');
		//再将前x-1个元素修改为0 
		cnt=cnt+v[i]*2-1;
		//总共修改了2x-1次,使得第x位上的1修改成功 
	}
	cout<<cnt<<"\n";
	for(int i=0;i<vec.size();i++)
		cout<<vec[i];//输出 
	cout<<"\n";
	return 0;
}
```

---

## 作者：__Toator__ (赞：1)

看见 $N \le 30$ 时便可以想到，这题是一道暴力题。于是我们便可以大胆的暴力：读题可知，将位置 $i$ 的 $0$ 修改为 $1$ 需要将前 $i$ 位都修改为 $1$ ，同理将位置 $i$ 的 $1$ 修改为 $0$ 需要将前 $i$ 位都修改为 $0$ 。所以我们可以建一个标记变量 $flag$ 来储存上一次操作的目标字符，如果当前目标字符和上一次操作的目标字符相同，那么就不做修改，不同，就循环将进行的操作加到答案 $ans$ 中，最后输出答案串的长度和答案串即可。

另外，由于每次操作都是从左往右修改，为了保证后面的操作不会影响到之前已经修改的部分，我们需要从后往前遍历字符串。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

bool flag;
int siz,cnt;
string s,ans;

int main(){
	cin>>siz>>s;
    for(int i=siz-1;i>=0;i--){
    	if(s[i]=='1'&&!flag){
    		for(int j=0;j<=i;j++)ans+="A";
    		flag=1;
		}
		if(s[i]=='0'&&flag){
			for(int j=0;j<=i;j++)ans+="B";
			flag=0;
		}
	}
	cout<<ans.size()<<endl<<ans<<endl;
	return 0;
}
```

---

## 作者：OIerWu_829 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc177_b)

从后往前遍历字符串 $S$，如果 $S_i$ 为 `1`，则进行 $i+1$ 次 A 操作和 $i$ 次 B 操作；如果 $S_i$ 为 `0` 不需要进行操作。

注意：如果是从前往后遍历，那么前边的字符串会被覆盖掉，得不到正确答案。

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    string ans = "";
    for (int i = n - 1; i >= 0; i--)
        if (s[i] == '1') {
            for (int j = 1; j <= i + 1; j++)
                ans += 'A';
            for (int j = 1; j <= i; j++)
                ans += 'B';
        }
    cout << ans.size() << "\n" << ans << "\n";
    return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

# AT_arc177_b [ARC177B] Puzzle of Lamps
## 题意概括
~~居然是道构造题，身为蒟蒻的我好帕帕。~~ 你有一个全是 $0$ 的序列，你可以进行以下两种操作：

- 操作 $A$：将最左边的 $0$ 替换为 $1$。
- 操作 $B$：将最左边的 $1$ 替换为 $0$。

给定一个序列，请你构造任意一种方案，使你手中的序列经过若干次操作后变为题目中给定的序列。
## 思路分析
瞪眼法发现，如果我们想将一个 $0$ 修改为 $1$，那么我们就需要将这个 $0$ 变为最左边的 $0$ 才可以进行修改。  
因此，如果我们要将一个 $0$ 修改为 $1$，为了让他成为最左边的 $0$，我们需要将他的左边全部变成 $1$，然后将其修改，最后再把他的左侧还原为 $0$ 即可。  
但是，问题又来了，如果我们从左往右，不断把 $0$ 修改为 $1$，那么在操作后面的 $0$ 时，会将我们前面改好的数覆盖。因此，我们需要改变一下顺序，从右往左依次修改。  
最后，温馨提示，需要特别注意下标哦！
## AC Code
代码有点丑，请谅解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[35],ai=0,ansi=0,cnt=0;
char ans[1000005]; 
string s;
int main(){
    cin>>n>>s;
    for (int i=n-1;i>=0;i--){
        if (s[i]=='1') a[ai++]=i;
    }
    for (int i=0;i<=ai-1;i++){
        for (int j=0;j<=a[i];j++) ans[ansi++]='A';
        for (int j=0;j<=a[i]-1;j++) ans[ansi++]='B';
        cnt+=(2*(a[i]+1)-1);      
    }
    cout<<cnt<<'\n';
    for (int i=0;i<ansi;i++) cout<<ans[i];
    return 0;
}
```
最后的最后，祝大家AC快乐！

---

## 作者：Fish_redflying (赞：0)

这里补充一下自己的思路。

令 $S_i$ 为目标状态串 $S$ 的第 $i$ 个字符。

考虑按位修改。

可以理解为，对于每 $i$ 个操作，都是从第 $1$ 项填充至 第 $i$ 项。（当操作范围都是 $1$ 或 $0$）

对于 $S_i$：

- 如果是零，不管。

- 如果是 1，照操作 $A$ 填充 $i$ 次 $1$ 直到第 $i$ 项。接下来再照操作 $B$ 填充 $i-1$ 次，为的是还原状态。

当然，要从后往前，要不然会导致前面处理好的又一次被打乱。

我们~~就不模拟从前往后~~模拟一下。

改变的部分使用强调字体。

令目标子串 $S$ 为 $000110001$。

1.初始为 $000000000$。

2.改变$S_9$：$000000000\to\textbf{111111111}\to\textbf{00000000}1$ 

3.改变$S_5$：$000000001\to\textbf{11111}0001\to\textbf{0000}10001$

4.改变$S_5$：$000010001\to\textbf{1111}10001\to\textbf{000}110001$

5.最后得到：$000110001$。

可以证明，当在极限数据下，$30$ 个 $1$ 所需的操作数为 $30+29+29+28+\dots+2+1+1=900$，完全小于限制 $10^6$ 次。

妥妥哒QwQ。

如有不清楚之处，欢迎指出。

~~没有代码。~~

---

## 作者：xxxalq (赞：0)

# 思路分析

因为操作数 $\le 10^6$ 并且 $n\le 30$，所以我们可以大胆的暴力 $n^2$，带一点贪心的枚举每一个数，并完成对这个位置的修改。因为每次修改会影响这个位置前面的数值，所以我们考虑倒序枚举，这样就可以做到无后效性。所以当枚举到 $i$ 时，前 $i-1$ 个数一定都是 $0$，后面的数一定符合要求。

对于每个位置 $i$ 如果目标序列的第 $i$ 个数为 $0$ 那就不需要修改，否则我们就需要把它改成 $1$，也就是把它变成最左边的 $0$，即把它的左边全部变成 $1$，接着把它也变成 $1$，然后在把前 $i-1$ 个数进行操作 $B$ 变回来。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,a[33],b[33],idx;
char ch,ans[100003];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>ch;
		a[i]=(ch=='1')?1:0;
	}
	for(int i=n;i>=1;i--){
		if(a[i]==b[i]){
			continue;
		}
		for(int j=1;j<=i;j++){
			ans[++idx]='A';
		}
		for(int j=1;j<i;j++){
			ans[++idx]='B';
		}
	}
	cout<<idx<<"\n";
	for(int i=1;i<=idx;i++){
		cout<<ans[i];
	}
	return 0;
}
```

---

## 作者：Scean_Tong (赞：0)

### AT_arc177_b [ARC177B] Puzzle of Lamps题解

两种操作都是在最左边改，所以考虑从右往左扫。

那么显然可以找到不连续的 $1$ 和 $0$，然后根据当前位置的下标来更新答案。

如果当前位置 $s_i$ 为 $1$，并且旁边是 $0$，那么就在答案后加上 $i$ 个 $A$。

如果当前位置 $s_i$ 为 $0$，并且旁边是 $1$，那么就在答案后加上 $i$ 个 $B$。

代码实现：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
char s[31];
int f;
string ans;
int32_t main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0),cout.tie(0);
	cin>>n;
	scanf("%s",s+1);
	int cnt=0;
	for(int i=n;i;i--){
		if(!f&&s[i]=='1'){
			for(int j=1;j<=i;j++)ans+='A';
			f=1;
		}
		if(f&&s[i]=='0'){
			for(int j=1;j<=i;j++) ans+='B';
			f=0;
		}
	}	
	cout<<ans.size()<<'\n';
	cout<<ans;
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：0)

### B - Puzzle of Lamps

### 思路

先考虑 ```0010``` 如何解决。

注意到一组可行解是 ```AAABB```。

看到这里可能有点感觉了，先用 ```A``` 把每个 $1$ 前面都填满 $1$，再用 ```B``` 把前面多余的 $1$ 退掉。

再考虑 ```0101``` 如何解决。

注意到一组可行解为 ```AAABBBAAB```。

发现可以先解决右边，再解决左边，这样可以把每个 $1$ 拆开做，会方便更多。

最后考虑 ```00111000011``` 如何解决。

注意到一组可行解为 ```AAAAAAAAAAABBBBBBBBBAAAAABB```。

一段 $1$，可以先用 ```A``` 把 $1$ 延申到右端点，再用 ```B``` 把左端点前的 $1$ 退掉。

从右到左解决每个区间。

这样构造出的解长度是 $n^2$ 级别的，不会超限。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, cnt;
char s[35];
struct seg {int l, r;} sg[35];
vector <char> ans;
int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1, l, r; i <= n; i ++) {
        if (s[i] == '1' && s[i - 1] != '1') l = i;
        if (s[i] == '1' && s[i + 1] != '1') r = i, sg[++ cnt] = {l, r};  
    }
    for (int i = cnt; i >= 1; i --) {
        for (int j = 1; j <= sg[i].r; j ++) ans.emplace_back('A');
        for (int j = 1; j < sg[i].l; j ++) ans.emplace_back('B');
    }
    printf("%d\n", ans.size());
    for (auto c : ans) putchar(c);
    return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

[[ARC177B] Puzzle of Lamps](https://www.luogu.com.cn/problem/AT_arc177_b)

放在 ARC 的 B 题算简单了。

大体思路：从右向左填，填到从左往右第 $i$ 位时，如果第 $i$ 位为 $1$，将 $1\sim i$ 全部置为 $1$，否则将 $1\sim i$ 全部置为 $0$。

以 $010100$ 这个情况为例，填完最右边的 $1$ 时序列为这个样子：$111100$。那么考虑如何填第 $3$ 位的 $0$，可以将第 $1\sim 3$ 位全变为 $0$。再考虑如何填第 $2$ 位的 $1$，可以将第 $1\sim 2$ 位全变为 $1$。最后考虑如何填第 $1$ 位的 $0$，直接第 $1$ 位变为 $0$ 即可。

最劣情况下时间复杂度为 $O(n^2)$，但是 $n\le 30$，随便过。我提交记录最慢的点只有 $1$ 毫秒。

描述的可能有些抽象，可参考代码实现：
```cpp
int main()
{
	scanf("%d", &n);
	scanf("%s", a + 1);
	bool flag = 0;
	for (int i = n; i >= 1; i--) {
		if (a[i] == '1') {
			if (a[i + 1] == '1') continue;
			for (int j = 1; j <= i; j++) s[++tot] = 'A';
			flag = 1;
		}
		else if (flag) {
			if (a[i + 1] == '0') continue;
			for (int j = 1; j <= i; j++) s[++tot] = 'B';
		}
	}
	printf("%d\n", tot);
	for (int i = 1; i <= tot; i++) printf("%c", s[i]);
	return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
有一个一开始全为 $0$ 的序列，有如下两种操作：
+ 操作 $A$：将最左边的 $0$ 变成 $1$。
+ 操作 $B$：将最左边的 $1$ 变成 $0$。

给你一个序列，构造任意一种方案进行若干次操作后得到这个序列。
# 题目思路
通过瞪眼大法，我们可以发现，这个家伙与前缀和有那么一丝丝的相似。

从后往前扫，每一次找到第一个不连续的 $1$ 和 $0$，按下标分别输出 $A$ 和 $B$ 即可。
# AC Code
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

//#prgama GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Os")
//#pragma GCC optimize("Ofast")

using namespace std;

inline bool input (int x) {
	x = 0;
	int f = 1;
	bool flag = 0;
	char c = getchar ();
	
	while (!isdigit(c)) {
		if (c == '-') {
			c = getchar ();
			
			if (isdigit (c)) {
				f = -1;
				break;
			}
		} else {
			c = getchar ();
		}
	}
	
	while (isdigit (c)) {
		flag = 1;
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar ();
	}
	
	x *= f;
	return flag;
}

inline bool output (int x) {
	if (x < 0) {
		putchar ('-');
		x = -x;
	}
	
	char write[25], cnt = 0;
	
	do {
		write[++ cnt] = x % 10;
		x /= 10;
	} while (x);
	
	do {
		putchar (write[cnt --] | 48);
	} while (cnt);
	
	return x;
}

const int N = 30;

void init ();

int n;
char a[N + 5];
bool flag;
string ans;

signed main () {
	init ();
	input (n);
	cin >> a + 1;
	
	for (int i = n; i; -- i) {
		if (a[i] == '1' && !flag) {
			flag = 1;
			
			for (int j = 1; j <= i; ++ j) {
				ans += "A";
			}
		}
		
		if (a[i] == '0' &&  flag) {
			flag = 0;
			
			for (int j = 1; j <= i; ++ j) {
				ans += "B";
			}
		}
	}
	
	output (ans.size ());
	puts ("");
	cout << ans;
	return 0;
}

void init () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
//	ios::sync_with_stdio (false);
//	cin.tie (0);
//	cout.tie (0);
}
```

---

## 作者：xcms (赞：0)

如果要把 $s_i$ 变成 $1$，需要将它前面的字符都变成 $1$，然后把 $s_i$ 变成 $1$，最后把前面的字符都变成 $0$。但是如果从左向右遍历，在做以上的操作时会影响到它以前的 $s_i$，所以需要从右向左遍历字符串。
```cpp
for(int i=n-1;i>=0;i--){
	if(s[i]=='1'){
		for(int j=0;j<=i;j++)t+="A";
		for(int j=0;j<i;j++)t+="B";
		cnt+=i*2+1;
	}
}
```

---

## 作者：210101zhaosicheng (赞：0)

# 题解：AT_arc177_b [ARC177B] Puzzle of Lamps

别看了，没有闲话。

## 简述题意

有一个一开始全为 $0$ 的序列，有如下两种操作：
+ 操作 $A$：将最左边的 $0$ 变成 $1$。
+ 操作 $B$：将最左边的 $1$ 变成 $0$。

给你一个目标序列，构造**任意**一种方案进行**若干次**操作后得到这个序列。

操作次数不能超过 $10^6$。

$1\le n\le 30$。

看似好像有 spj。

## 思路分析

既然有 spj，那么根本不用怕。

注意观察：只能从左边开始改，不能从右边做任何操作。

直接每一位硬改即可。

1. 如果此位是 $1$ （假设这一位是第 $x$ 位）那么直接将这 $x$ 位都改成 $1$，更改完这一位以后再将前面的 $x-1$ 位设置成 $0$。

2. 如果是 $0$ 直接放任不管，因为原数列全部都是 $0$。

因为做多只有 $\frac{n\times {(n-1)}}{2}$ 次，所以肯定 $0\le 总次数 \le 10^6$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char c[55];//输入序列
int sum;
int a[55];//是1的下标
char ans[100010];//存储答案
int num;//存储1的下标的数组的指针
int num2;//存储答案数组的指针
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		if(c[i]=='1')
		{
			num++;
			a[num]=i;//存储是1的下标
		}
	}
	for(int i=num;i>=1;i--)//从后往前遍历先修改后面的
	{
		for(int j=1;j<=a[i];j++)//将全部<=a[i]的都置为1
		{
			num2++;
			ans[num2]='A';
		}
		for(int j=1;j<=a[i]-1;j++)//将<a[i]的都置为0
		{
			num2++;
			ans[num2]='B';
		}
		sum+=a[i]*2-1;//总步数使用为 n*(n-1)/2
	}
	cout<<sum<<'\n';//记得输出总次数
	for(int i=1;i<=sum;i++)
	{
		cout<<ans[i];//输出
	}
	cout<<endl;//别的题被换行坑惨了
	return 0;	
}
```

然后就没有然后了。

![](https://cdn.luogu.com.cn/upload/image_hosting/lpd21fad.png)

---

## 作者：LZYAC (赞：0)

## 思路

对于每一次操作，找到最后一个不满足要求的数字。

代码中用一个标记作为当前位置及之前的所有元素是 $1$ 还是 $0$ 来判断。

然后将这里及之前的所有元素替换成正确的元素。

最坏次数：$O(n^2)$ 实际远远不足这个数。

而题目居然给了 $10^6$，所以可行。

[作为拓展，有兴趣的可以了解一下（同类题）](https://blog.csdn.net/AivenZhong/article/details/103653706)
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,flag;
string s,ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//这三句都是输入输出优化，加不加都可以（把cin,cout换成scanf,printf是一样的效果）
	cin>>n>>s;
	for(int i=n-1;i>=0;i--){
		if(s[i]=='1'){
			if(flag==0){
				for(int j=0;j<i+1;j++) ans=ans+'A';
 				flag=1;
			}
		}
		else{
			if(flag==1){
				for(int j=0;j<i+1;j++) ans=ans+'B';
				flag=0;
			}
		}
	}
	cout<<ans.length()<<'\n'<<ans;
	return 0;
}
```

---

## 作者：2011FYCCCTA (赞：0)

[原题](https://www.luogu.com.cn/problem/AT_arc177_b)

---
### 思路

对于每一段连续的 $1$，设其最左端编号为 $l$，最右端编号为 $r$，那么可以先使用 $r$ 次操作 $A$，再使用 $l -1$ 次操作 $B$（类似前缀和诶？）。如果从左往右依次处理会导致后面的操作覆盖前面的情况，所以只能从右往左处理。

最坏情况下需要 $\frac{n(n-1)}{2}$ 次操作。

---
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s , ans;
int main()
{
    cin >> n >> s;
    char lst = '0';
    for (int i = n - 1 ; i >= 0 ; i--)
    {
        if (lst == '0' && s[i] == '1') 
        {
            for (int j = 0 ; j <= i ; j++) ans += 'A';
            lst = '1';
        }
        if (lst == '1' && s[i] == '0') 
        {
            for (int j = 0 ; j <= i ; j++) ans += 'B';
            lst = '0';
        }
    }
    cout << ans.length() << '\n' << ans;
    return 0;
}
```

---

## 作者：code_hyx (赞：0)

应该是最简单的 arc B 吧，提供一种思路。  
最开始全是 $0$，逐个把 $1$ 按出来就行了。  
但是为了保证按出的 $1$ 不被按回去，需要从后往前按。  
按一个 $1$ 的方法是：如果这个 $1$ 在第 $k$ 个位置（不是字符串或字符数组的下标！），用 $k$ 次 A 和 $k-1$ 次 B。  
然后统计一下操作次数就行了，绝对没超过题目限制。  
代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,cnt=0,ct=0,a[50]={0};
string t;
char tt[100005],s[100005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	cin>>t;
	for(int i=0;i<n;i++)tt[i]='0';
	for(int i=0;i<n;i++)
	{
		if(t[i]=='1')a[++ct]=i;
	}
	for(int i=ct;i>=1;i--)
	{
		for(int j=0;j<=a[i];j++)
		{
			if(tt[j]=='0')
			{
				tt[j]='1';
				cnt++;
				s[cnt]='A';
			}
		}
		for(int j=0;j<a[i];j++)
		{
			if(tt[j]=='1')
			{
				tt[j]='0';
				cnt++;
				s[cnt]='B';
			}
		}
	}
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++)cout<<s[i];
	return 0;
}
```

---

## 作者：zjzx_wcj (赞：0)

# 题解：AT_arc177_b [ARC177B] Puzzle of Lamps

[题目传送门](/problem/AT_arc177_b)

## 思路

一道很简单的构造题。~~所以 $1 \le n \le 30$ 是什么鬼~~。

首先，有SPJ。所以，我们不需要最小化操作次数。然后，对于在第 $i$ 个位数的 $1$，可以通过 $i+1$ 个 $A$ 操作和 $i$ 个 $B$ 操作来得到。$(0 \le i < n)$

举个例子：

$0000\to0100$

第一步：$0000\to1000$ 操作：$\texttt {A}$

第二步：$1000\to1100$ 操作：$\texttt {AA}$

第三步：$1100\to0100$ 操作：$\texttt {AAB}$

这就验证了我们的猜想。

但还有一个问题：

比如这个：$00000\to01010$。

变化过程：$00000\to10000\to11000\to01000\to11000\to11100\to11110\to01110\to00110\to00010$。

字符串序列：$\texttt {AABAAABBB}$。

你们一定发现问题了，字符串操作序列并没有把 $00000$ 变成 $01010$。

但是，如果我们倒着来呢？

变化过程：$00000\to10000\to11000\to11100\to11110\to01110\to00110\to00010\to10010\to11010\to01010$。

操作序列：$\texttt {AAABBBAAB}$。

成功！！！

所以，倒着遍历字符串，遇到一个 $1$ 就给操作序列加上 $i+1$ 个 $\texttt {A}$ 和 $i$ 个 $\texttt {B}$。（$i$ 表示这个字符从 $0$ 开始编号的第 $i$ 个）

## 代码参考
```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define elif else if
#define fin(x) freopen (x,"r",stdin)
#define fout(x) freopen (x,"w",stdout)
#define rnt register int
#define reg(i,x,y) for (register int i=(x);i<=(y);++i)
#define Reg(i,x,y) for (register int i=(y);i>=(x);--i)
using namespace std;
namespace rwm {inline int read () {int s=0,w=0;char c=getchar ();while (!isdigit (c)){w|=(c=='-');c=getchar ();}while (isdigit (c)) {s=(s<<1)+(s<<3)+(c^48);c=getchar ();}return w?-s:s;}inline void write (int x) {if (x<0) putchar ( '-'),x=-x;if (x>9) write (x/10);putchar (x%10|48);}inline void writesp (int x) {write (x),putchar (' ');}inline void writeln (int x) {write (x),putchar ('\n');}inline int square (int x) {return x*x;}inline int floor (double x) {return x;}inline int ceil (double x) {return (int)(x+0.5);}inline int gcd (int x,int y) {int z=x%y;while (z) x=y,y=z,z=x%y;return y;}inline int lcm (int x,int y) {return x/gcd (x,y)*y;}};
using namespace rwm;
int n;
string s,s1; 
signed main ()
{
	n=read (),cin>>s;
	Reg (i,0,n-1)
		if (s[i]=='1') 
		{
			reg (j,1,i+1) s1+='A';
			reg (j,1,i) s1+='B';
		}
	writeln (s1.size ());
	cout<<s1;
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# 思路

**特别注意：不需要最小化操作次数。**

反正，你构造的操作次数不会超过 $10^6$，题目只是担心 SPJ 会超时。

我们遍历 $S$ 的每一个字符。若发现当前字符为 `1`，令 $i$ 为当前下标（从 $0$ 开始），可以进行 $i+1$ 次 `A` 操作和 $i$ 次 `B` 操作。

例如，$S$ 为 `00010`。起初，字符串为 `00000`。当 $i=3$ 时，进行 $4$ 次 `A` 操作，得 `11110`，在进行 $3$ 次 `B` 操作，得 `00010`。

我们发现，如果是正着遍历 $S$，则之前已经构造出的字符会被覆盖掉。于是，我们考虑倒着遍历，答案也便水落石出了。

时间复杂度：$O(N^2)$。所以为什么 $N$ 只有 $30$？是在给 SPJ 留时间吗？

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n;
string s;
vector<char> ans;

int main() {
    cin >> n >> s;
    for (ll i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            continue;
        }
        for (ll j = 1; j <= i + 1; j++) {
            ans.push_back('A');
        }
        for (ll j = 1; j <= i; j++) {
            ans.push_back('B');
        }
    }
    cout << ans.size() << endl;
    for (char x : ans) {
        cout << x;
    }
    return 0;
}
```

---

## 作者：wyyqwq (赞：0)

简单构造题。

每次从后找一段连续 0/1 段的右端点，设位置为 $pos$，操作其对应的 $pos + 1$ 次即可。


最劣情况下需要操作 $\frac{n(n+1)}{2}$ 次。


```c++
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
struct node {
    int a, b;
};
vector<node> v;
int main() {
    int n;
    string s;
    cin >> n >> s;
    int ans = 0;
    int pos = 0;
    for(int i = 0; i < n; i ++) {
        if(s[i] == '1') pos = i;
    }
    int cnt = 0;
    int flag = 0;
    for(int i = pos; i >= 0; i --) {
        if(flag == s[i] - '0') {
            continue;
        }
        flag = s[i] - '0';
        v.push_back({i + 1, s[i] - '0'});
        ans += i + 1;
    }
    cout << ans << endl;
    for(auto i : v) {
        if(i.b == 1) {
            for(int j = 1; j <= i.a; j ++) cout << "A";
        }
        else {
            for(int j = 1; j <= i.a; j ++) cout << "B";
        }
    }
}
```

---

## 作者：wei2013 (赞：0)

## 题目大意：
让你把一个原本全是 `0` 的序列变成题目要求序列（`01` 串），可以用两种操作：

`A`：把最左边的为 `0` 的字符，变为 `1`。

`B`：把最左边的为 `1` 的字符，变为 `0`。

输出操作。
## 思路：
设此时扫到的字符是第 $i$ 个：

如果此时扫到的字符为 `1`，我们可以使用 $i$ 个 `A` 操作和 $i-1$ 个 `B` 操作。

反之则不用改变。

此时可得出代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
	string s,ans="";
	cin>>n>>s;
	for(int i=0;i<s.size();i++){
		if(s[i]=='1'){
			for(int j=1;j<=i+1;j++){
				ans+='A';
			}
			for(int j=1;j<=i;j++){
				ans+='B';
			}
		}
	}
	cout<<ans.size()<<endl<<ans;
    return 0;
}
```

若是正序扫描会发现有一个问题，就是后面的会覆盖掉前面的，是前面的变为 `0`，也就只能让最后一个 `1` 达到效果，从而输出错解，该如何解决这种问题呢？其实倒序扫描就好了，因为后面的 `1` 是不会影响到前面的，经过这些操作，在 `1` 的前面是不会改变的，问题也就迎刃而解了。

时间复杂度：$\mathcal{O(n^2)}$。
## code:
**温馨提示：此题不需要操作数最少。**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
	string s,ans="";
	cin>>n>>s;
	for(int i=s.size()-1;i>=0;i--){
		if(s[i]=='1'){
			for(int j=1;j<=i+1;j++){
				ans+='A';
			}
			for(int j=1;j<=i;j++){
				ans+='B';
			}
		}
	}
	cout<<ans.size()<<endl<<ans;
    return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

简单构造，大概用大脑想一下就行了吧（

# 正文

发现要造成一段连续的为开状态的灯，必然是先把从整体最左端的灯开到这一段连续的为开状态的灯的结尾，然后再把从整体最左端的灯开到这一段连续的为开状态的灯的开头的**前一个**。

模拟一下：

```
Init State:
00000
After turning on [1, 3] (AAA):
11100
After turning off [1, 1] (B):
01100 (Reached target state)
```

联系别的算法以加深理解：这就好比是数位 DP，求 $[l, r]$ 的解是用 $[1, r]$ 的解减去 $[1, l - 1]$ 的解做到的。

同样，我们若想造成 $[l, r]$ 这一段的开灯状态，在只允许进行题目所述操作时，必然要先造成 $[1, r]$ 的开灯后造成 $[1, l - 1]$ 的关灯。

注意：在用这个操作达成目标状态时，由于若以先满足前面的造成一段连续的为开状态的灯的要求为策略，会造成在满足后面的造成一段连续的为开状态的灯的要求时产生后效性（直接覆盖了），因此我们考虑先满足满足后面的造成一段连续的为开状态的灯的要求。

再模拟理解一下（这里我们以 `0111011` 为目标状态）：

```
Init State:
0000000
After turning on [1, 7] (AAAAAAA):
1111111
After turning off [1, 5] (BBBBB):
0000011
After turning on [1, 4] (AAAA):
1111011
After turning off [1, 1] (B):
0111011 (Reached target state)
```

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

int N, cnt;
char S[35];
string ans;

signed main()
{
	cin >> N;
	for(int i = 1; i <= N; ++ i) 
		cin >> S[i];
	
	for(int i = N; i >= 1; -- i)
	{
		if(S[i] == '1')
		{
			int nowpos = i - 1;
			while(S[nowpos] == '1' && nowpos >= 1) nowpos --;
			for(int j = 1; j <= i; ++ j) ans += 'A', ++ cnt;
			for(int j = 1; j <= nowpos; ++ j) ans += 'B', ++ cnt;
			i = nowpos;
		}
	}

    cout << cnt << endl;
    cout << ans << endl;
	return 0;
}
```

# 后言

如果有更短构造方案请评论指出。

$\color{white}\small\text{好像是最短构造方案了吧（}$

---

## 作者：破壁人罗辑 (赞：0)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_arc177_b)/[AtCoder](https://atcoder.jp/contests/arc177/tasks/arc177_b)

## 题目大意

给出一个目标序列，初始序列全为 $0$，你每次可以把最左侧的 $0$ 变成 $1$ 或者把最左侧的 $1$ 变成 $0$，序列长度不超过 $30$，给出一个操作次数不超过 $10^6$ 的操作方案。

## 解题思路

从右往左遍历，若遇到一个目标状态与当前状态不同的数字则将它和它左边的状态全都设置成它的目标状态，记录答案。易知对于一个长度为 $n$ 的序列这种方法生成的方案的操作次数不会超过 $n^2$。时间复杂度 $O(n^2)$。

## AC 代码
### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
int Read(){
	char c=getchar();while(c<'0'||c>'9')c=getchar();
	int r=0;while(c>='0'&&c<='9'){r=r*10+(c^48);c=getchar();}
	return r;
}
int m[30];
int main(){
	int n=Read();
	for(int i=0;i<n;i++){
		m[i]=getchar()^48;
		while(m[i]!=1&&m[i]!=0)m[i]=getchar()^48;
	}
	bool on=0;
	vector<char>ans;int r=0;
	for(int i=n-1;i>=0;i--){
		if(m[i]!=on){
			r+=i+1;
			if(m[i])for(int j=0;j<=i;j++)ans.push_back('A');
			else for(int j=0;j<=i;j++)ans.push_back('B');
			on=!on;
		}
	}
	printf("%d\n",r);
	for(int i=0;i<r;i++)putchar(ans[i]);
	return 0;
}
```
### JAVA
```java
import java.io.*;
public class Main {
    private static int Read()throws IOException {
        char c=(char)System.in.read();
        while(c<'0'||c>'9')c=(char)System.in.read();
        int r=0;
        while(c>='0'&&c<='9'){r=r*10+(c^48);c=(char)System.in.read();}
        return r;
    }
    private static int max(int x,int y){
        return x>y?x:y;
    }
    public static void main(String[] args)throws IOException {
        int n=Read();
        byte[] s=new byte[40];
        System.in.read(s);
        char[] ans=new char[1600];
        int cnt=0,turn=0;
        for(int i=n-1;i>=0;i--)
            if((s[i]^48)!=turn){
                if((s[i]^48)==1){
                    for(int j=0;j<=i;j++)ans[cnt++]='A';
                    turn=1;
                }
                else{
                    for(int j=0;j<=i;j++)ans[cnt++]='B';
                    turn=0;
                }
            }
        System.out.println(cnt);
        for(int i=0;i<cnt;i++)
            System.out.print(ans[i]);
    }
}
```
### Python
```python
n=int(input())
cnt=0
ans=''
s=input()
p='0'
for i in range(n-1,-1,-1):
    if s[i]!=p:
        if s[i]=='1':
            p='1'
            cnt=cnt+i+1
            for j in range(i+1):
                ans=ans+'A'
        else:
            p='0'
            cnt=cnt+i+1
            for j in range(i+1):
                ans=ans+'B'
print(cnt)
print(ans)
```

---

## 作者：WuMin4 (赞：0)

# [[ARC177B] Puzzle of Lamps](https://www.luogu.com.cn/problem/AT_arc177_b)
# 思路
首先可以发现这题并没有限制最少操作步骤，于是逆序遍历序列，若要将位置 $i$ 的数字变成 $1$ (下标从 $0$ 开始)，则先执行 $i+1$ 次操作 $A$，再执行 $i$ 次操作 $B$，这样可以保证只将位置 $i$ 的数字变成 $1$。由于是逆序遍历，所以不会影响后面的数字。  
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt,n;
string s,res;
signed main() {
	cin>>n>>s;
	for(int i=s.length()-1;i>=0;i--)
		if(s[i]=='1'){
			cnt+=2*i+1;
			for(int j=1;j<=i+1;j++) res=res+"A";
			for(int j=1;j<=i;j++) res=res+"B";
		}
	cout<<cnt<<endl<<res;
	return 0; 
}
```

---

## 作者：x1489631649 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc177_b)
#### 个人感言
题目有点坑，比赛的时候没有看到最下方的解释，**先从前往后枚举**，浪费了3次提交次数。错误原因见下文，所以请大家 **看一下最下面的样例解释** ！
# 输入 
1. 第一行，数据组数 $n(1 \le n \le 30)$。
1. $n$ 个数据代表目标状态中每个电灯的状态 $x(0 \le x \le 1)$。
# 输出
1. 步骤总数。
1. 输出改成目标状态的方案。
# 题意
有两种改变电灯的状态
- 方案 $A$ ，将左边第一个状态为 0 的电灯状态改成 1。
- 方案 $B$ ，将左边第一个状态为 1 的电灯状态改成 0。
# 分析
从右往左查找，先改变最右边的电灯状态，因为右边的电灯状态会影响左边电灯的状态。所以将这个电灯的左边所有电灯包括本身的状态都改成 1，再将这个电灯的左边所有电灯不包括本身的状态都改成 0。
 # Code
```
#include<bits/stdc++.h>
using namespace std;
int f[1000];
int main()
{
	int l,ans=0,s=1;
	string a;
	cin>>l>>a;
	for(int i=0;i<l;i++)
	{
		if(a[i]=='1')
		{
			f[s]=i+1;//电灯状态为 1 的电灯下标。
			s++;//电灯状态为 1 的电灯数量。
		}
	}
	s--;
	for(int i=s;i>=1;i--)//倒序枚举。
	{
		ans+=2*f[i]-1;//要将 1 到这个下标的电灯进行 A 操作，然后要将 1 到这个下标减一的电灯进行 B 操作。
	}
	cout<<ans<<endl;
	for(int i=s;i>=1;i--)
	{
		for(int j=1;j<=f[i];j++)
			cout<<'A';
		for(int j=1;j<=(f[i]-1);j++)
			cout<<'B';
	}
	cout<<endl;
}
```
# 时间复杂度
本代码仅使用二重循环，且 $s$ 与 $f_i$ 的最大值为 $n(1 \le t \le 30)$，所以极限只会跑 900 次 ，操作次数最高为 $30 \times 30 \times 2$，题目中的操作限制为 $m(0 \le m \le 10^6)$，所以可以通过。

---

## 作者：Chillturtle (赞：0)

# 题意

有一个长度为 $n$ 的数串，其中 $1 \le n \le 30$。这个数串中只包含 $0$ 和 $1$，且它是由一个原为全 $0$ 的数串经过如下两种操作变过来的：

- 操作 $A$：将最左边的 $0$ 变成 $1$。

- 操作 $B$：将最左边的 $1$ 变成 $0$。

问，原数串经过多少次变化后变成现数串以及具体的操作。

# 思路

因为这道题要求操作次数小于 $10^6$ 次，所以我们可以考虑直接改。怎么改呢？分成两种情况：

- 如果当前位为 $0$：我们可以直接不管他，因为原数组就是一个全 $0$ 数组。

- 如果当前位位 $1$：我们就先将当位之前的数（含当前位）全部用 $A$ 操作改成 $1$，然后用 $B$ 操作将当前位之前（除当前位）的数全部改成 $0$。

注意，此时为防止改后面的数时影响前面已经改过的，我们从后向前改。

此处放一张图，看不懂的小珂爱可以向下翻哦。

![](https://cdn.luogu.com.cn/upload/image_hosting/9o8h1vv8.png)

同样，改第一个 $1$ 时也是类似的操作。

此时，改动次数的最大值为 $ \frac{(n - 1) \times n}{2}$，符合题目要求。

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e1+10;
int m,opt;
int one[N],b[N]={0},a[N];
char anss[35];
string s;
int main(){
	cin>>m;
	cin>>s;
	for(int i=0;i<m;i++){
		a[i]=s[i]-'0';
	}
	for(int i=0;i<m;i++){
		if(a[i]==1){
			one[++opt]=i;
		}
	}
	int ans=0;
	for(int i=1;i<=opt;i++){
		for(int j=0;j<=one[i];j++){
			if(b[j]!=1){
				ans++;
				anss[ans]='A';
				b[j]=1;
			}
		}
		for(int j=0;j<one[i];j++){
			if(a[j]==0){
				ans++;
				anss[ans]='B';
				b[j]=0;
			}
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++){
		cout<<anss[i];
	}
	cout<<endl;
return 0;
}
```

---

## 作者：ThisIsLu (赞：0)

简单构造题。

不妨将序列分为一个个 $1$ 的连续段，从右往左，考虑每一个段 $[l_i,r_i]$怎么构造。

由于当前左边都是 $0$，可以先执行 $r_i$ 次 A 操作，让 $1$ ~ $r_i$ 都是 $1$。

接下来再执行 $l_i-1$ 次 B 操作，把多余的 $1$ 去掉。

然后就没有然后了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int N=30;
char str[N+5];
int m;
char ans[1000001];
int main(){
    cin>>n>>(str+1);
    int cnt=0;
    str[0]='0';
    for(int i=n;i>=0;i--){
        if(str[i]=='1'){
            cnt++;
        }
        else if(cnt){
            for(int j=1;j<=i+cnt;j++){
                ans[++m]='A';
            }
            for(int j=1;j<=i;j++){
                ans[++m]='B';
            }
            cnt=0;
        }
    }
    cout<<m<<"\n";
    for(int i=1;i<=m;i++){
        cout<<ans[i];
    }
    return 0;
}
```

---

