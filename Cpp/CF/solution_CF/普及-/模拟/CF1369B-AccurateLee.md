# AccurateLee

## 题目描述

Lee was cleaning his house for the party when he found a messy string under the carpets. Now he'd like to make it clean accurately and in a stylish way...

The string $ s $ he found is a binary string of length $ n $ (i. e. string consists only of 0-s and 1-s).

In one move he can choose two consecutive characters $ s_i $ and $ s_{i+1} $ , and if $ s_i $ is 1 and $ s_{i + 1} $ is 0, he can erase exactly one of them (he can choose which one to erase but he can't erase both characters simultaneously). The string shrinks after erasing.

Lee can make an arbitrary number of moves (possibly zero) and he'd like to make the string $ s $ as clean as possible. He thinks for two different strings $ x $ and $ y $ , the shorter string is cleaner, and if they are the same length, then the lexicographically smaller string is cleaner.

Now you should answer $ t $ test cases: for the $ i $ -th test case, print the cleanest possible string that Lee can get by doing some number of moves.

Small reminder: if we have two strings $ x $ and $ y $ of the same length then $ x $ is lexicographically smaller than $ y $ if there is a position $ i $ such that $ x_1 = y_1 $ , $ x_2 =       y_2 $ ,..., $ x_{i - 1} = y_{i - 1} $ and $ x_i < y_i $ .

## 说明/提示

In the first test case, Lee can't perform any moves.

In the second test case, Lee should erase $ s_2 $ .

In the third test case, Lee can make moves, for example, in the following order: 11001101 $ \rightarrow $ 1100101 $ \rightarrow $ 110101 $ \rightarrow $ 10101 $ \rightarrow $ 1101 $ \rightarrow $ 101 $ \rightarrow $ 01.

## 样例 #1

### 输入

```
5
10
0001111111
4
0101
8
11001101
10
1110000000
1
1```

### 输出

```
0001111111
001
01
0
1```

# 题解

## 作者：namelessgugugu (赞：5)

#### 题意
有一个长度为n的0/1字符串 $s$，若 $s_i = 1,s_{i+1} = 0$ 则可以删除其中一个字符。输出经过若干次删除后长度最短，且字典序尽可能小的字符串。

#### 思路
题目中说对于字串 `10`，可以删除其中一个字符，不难发现对于形如 `11...100...0` 和形如 `1010...10` 的字符串可以被删成 `10`。

进一步往下推，发现任何一个从1开始，以0结束的字符串都可以被删成 `10`。因为任意一个这种字符串都是由若干个连续的  `11...100...0` 组成，则该字符串，可以被删成 `1010...10`，也就可以被删成 `10`。

对于题目给定的字符串 $s$，如果我们能找到 $l$ 和 $r$ 使得 $l < r, s_l = 1, s_i = 0(i < l), s_r = 0, s_j = 1(j > r)$。我们把字串 $s_{l..r}$ 化成 `10`，再化成 `0`（这样使得字典序尽可能小），此时的字符串已经被删成 `00...011...1`，不能再删了，直接输出。

如果找不到 $l$ 和 $r$，说明该字符串已经成为 `00..011...1`，直接输出原字符串。

#### AC代码
```cpp
#include <cstdio>
#include <cstring>
const int N = 100005;
int t, n;
char str[N];
int main(void)
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%s", &n, str+1);//字符串从1开始存，方便操作
        int l = 1, r = n;
        while(str[l] == '0')
            ++l;
        while(str[r] == '1')
            --r;
        if(l > r) //如果找到的l r不满足条件，输出原字符串
            printf("%s\n", str+1);
        else//输出删除后的字符串
        {
            for(int i = 1;i < l;++i)
                putchar(str[i]);
            putchar('0');
            for(int i = r+1;i <= n;++i)
                putchar(str[i]);
            putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：hzr6767 (赞：2)

# CF1369B AccurateLee 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1369B)

## 题目大意

给你一个字符串 $s$，其中如果 $s_i = 1$ 且 $s_i + 1 = 0$，那么我们就可以删除其中一个，问经过无限次操作后字符串字典序最小的字符串。

## 题目分析

这道题是一个找规律的题目，题目中要求我们找到字符串字典序最小的字符串，也就是当我们删除的时候一定要考虑如何让字符串长度最短。

此时题目的意思就明确了许多，此时我们在对题目进行分析，我们可以得知前面的0和后面的1是无法被删除的（如“$\texttt{000110111}$”中“$\texttt{000}$”和“$\texttt{111}$”无法被删除，也就是说我们要先将这一部分进行保留（存入新的答案字符串），再对中间部分进行处理）（注：如果是“$\texttt{111000}$”，那么中间部分就为“$\texttt{111000}$”）。

在将前后部分处理之后，我们可以发现中间部分的开头一定是“$\texttt{1}$”，中间部分的结尾一定是“$\texttt{0}$”，刚好满足删除字符的情况，因为要考虑字典序最短，所以我们优先考虑删除“$\texttt{0}$”。

### 在这里模拟一下中间部分的处理情况：

假如输入的字符串为：“$\texttt{000110111}$”。

我们现需要将前面为“$\texttt{0}$”的部分和后面为“$\texttt{1}$”的部分进行保存（用一个字符串保存）。

然后我们处理中间部分：“$\texttt{110}$”。

第二个数“$\texttt{1}$”和第三个数“$\texttt{0}$”正好满足删除一个数的条件，我们将“$\texttt{1}$”进行删除。

此时中间部分变为“$\texttt{10}$”，第一个数和第二个数满足删除条件，将“$\texttt{1}$”进行删除。

最后中间处理的结果一定为“$\texttt{0}$”。（对这部分没有看明白的同学可以自己再造几组数据进行尝试）（如果中间部分什么都没有，自然就没有输出结果）。

总结：

第一步：取出前面为“$\texttt{0}$”的部分和后面为“$\texttt{1}$”的部分，用一个字符串保存。

第二步：判断中间部分有没有“$\texttt{0}$”，有则输出一个“$\texttt{0}$”。

第三步：输出第一步中保存的字符串。

然后按照题目要求进行指定次数的循环即可。

## 最后送上AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std; 
int main() {
	int t;
	cin >> t; //简单的输入
	while (t --) {//重复遍历t次
		int len;//记录当前字符串长度
		string str, cnt = "";//cnt用来记录重构后的字符串，str用来输入
		cin >> len >> str;//朴实无华的输入
		int le = 0, rig = len - 1;//分别表示字符串的头和尾，用来找出前面的0和后面的1
		while (str[le] == '0') {//找出前面的0 
			cnt += '0';//添加进答案字符串之中 
			le ++;//进行循环 
		}
		while (str[rig] == '1') {//找出后面的1 
			cnt += '1';//添加进答案字符串之中 
			rig --;//循环 
		}
		for (int i = le; i <= rig; i ++) {//再找到之前没有找到过的0（前提是非直接结尾或间接结尾的0） 
			if (str[i] == '0') {
				cout << 0;//有0则直接输出0 
				break;//退出循环
			}
		}
		cout << cnt << endl;//输出答案字符串 
	}
	return 0;
}
```

**注：为什么要先输出“$\texttt{0}$”在输出重构后的字符串呢？因为重构后的字符串前半部分为“$\texttt{0}$”，后面为“$\texttt{1}$”，所以在中间添加一个“$\texttt{0}$”的效果就等同于在开头添加一个“$\texttt{0}$”！**

## 感谢你的观看！有不对的欢迎指出！


---

## 作者：pocafup (赞：1)

~~这是一道观察题，然而窝不会观察~~

不会观察只能用一些傻一点的方法做。

可以发现，当某个字段为 $100$ 时，删去一个 0 不会让他无法继续删除。同理，$110$ 时删去 1 也不会影响结果。

所以，我们可以从后往前枚举，找到所有符合这种情况的子串，并将其暴力删除。

可证在去除前置0后前面两位得到的一定为 $10$，这时删除这个 1 一定是最优的。

由于 vector.erase 的复杂度为 $O(n)$，故我们只能用另外的办法进行删除。

这里我用到的方法类似于链式前向星。将每个数连到后一个数，记为 nxt ，后面的数连到前一个数，记为 pre。

```
for (int i=0;i<n-1;i++) nxt[i] = i+1;
nxt[n-1] = -1;
for (int i=1;i<n;i++) pre[i] = i-1;
pre[0] = -1;
```
当删除是，我们可以将后一个数连接到前一个数。若现在的数位置为 $ctr$，则删除目前位置数字的方法为：

```
nxt[pre[ctr]] = nxt[ctr];//这个数前驱的后驱变为这个数的后驱
pre[nxt[ctr]] = pre[ctr];//同理
```

最后按链式的方法从前往后输出即为答案。

```
#include <iostream>
#include <algorithm>
using namespace std;
string s;
int t,n,nxt[100005],pre[100005];

signed main(){
  cin >> t;
  while(t--){
    cin >> n >> s;
    for (int i=0;i<n-1;i++) nxt[i] = i+1;
    nxt[n-1] = -1;
    for (int i=1;i<n;i++) pre[i] = i-1;
    pre[0] = -1;//上面有讲
    int ctr = n-1;//从后往前扫
    while(ctr!=0){
      if (nxt[ctr]==-1 || s[nxt[ctr]]=='1' || s[ctr]=='0') ctr= pre[ctr];
      else if(s[pre[ctr]]=='1') nxt[pre[ctr]] = nxt[ctr],pre[nxt[ctr]] = pre[ctr],ctr= pre[ctr];
      else if (nxt[nxt[ctr]] != -1 && s[nxt[nxt[ctr]]] == '0')nxt[ctr] = nxt[nxt[ctr]], pre[nxt[ctr]] = ctr;//三种情况分别讨论
      else nxt[pre[ctr]] = nxt[ctr],pre[nxt[ctr]] = pre[ctr],ctr= pre[ctr];
      int tmp = 0;
    }
    if (s[ctr]=='1'){
      while(nxt[nxt[ctr]]!=-1 && s[nxt[nxt[ctr]]]=='0') nxt[ctr] = nxt[nxt[ctr]];
      if (nxt[ctr]!=-1 && nxt[ctr]=='0')ctr = nxt[ctr];//对删剩的10进行处理
    }
    if (nxt[ctr]!=-1 && s[ctr]=='1' && s[nxt[ctr]]=='0') ctr = nxt[ctr];
    while(ctr!=-1) {cout << s[ctr]; ctr = nxt[ctr];}//输出，是不是很像链式？
    cout << endl;
  }
}
```

---

## 作者：Berd__ (赞：0)

为了保证字典序最小，字符串要尽量的短，零在前还是一在前，还是要考虑的。

那么先是考虑长度了，首先，$10$ 的字符串，可以将前面的 $1$ 删除。那么如果是 $100$ 的字符串呢？$0$ 先删除，再删除 $1$。我们发现，只要是 $1$ 后面跟着多个 $0$ 的字符串，都可以变成 $0$，而多个上种字符串组合的字符串，也可以变成 $0$。

除了若干个 $0$ 或若干个 $1$ 形成的字符串以外，其余所有的字符串都可以变成 $0$。那么我们就可以记录下从开头以来，连续的 $0$ 的个数，与从末尾以前，连续的 $1$ 的个数，若除去上面所记录的字符串，剩下的字符串中有 $0$，就多输出一个 $0$ 就行了。
```cpp
#include<bits/stdc++.h>
#define int long long
#define T kkk
using namespace std;
signed main(){
	int T,n;
	cin>>T;
	for(int i=1;i<=T;i++){
		string s,a="";
		cin>>n>>s;
		int l=0,r=n-1;
		while(s[l]=='0')
			l++,a+='0';
		while(s[r]=='1')
			r--,a+='1';
		for(int j=l;j<=r;j++)
			if(s[j]=='0'){
				cout<<'0';
				break;
			}
		cout<<a;
	}
	return 0;
}

```

---

## 作者：oceanfish (赞：0)

## 题目
[题目传送门](https://www.luogu.com.cn/problem/CF1369B)

题目很清晰，给定一个字符串 $s$，其中如果 $s_i=1$ 并且 $s_{i+1}=0$，我们可以删除其中任意一个，求经过有限次操作后字符串字典序最小的字符串。

## 分析

为了保证字典序最小，字符串要尽量的短，至于零在前还是一在前，还是要考虑考虑的，因为这也会影响顺序。

那么就是考虑长度了，首先，形如 `10` 的字符串，可以将前面的 $1$ 给删除，长度减少。那么形如 `100` 的字符串呢？先将 $0$ 删除，再删除 $1$。我们发现，只要是 $1$ 后面跟着若干个 $0$ 的字符串，都可以通过删减变成 $0$，而多个上种字符串堆叠起来的字符串，也可以变成 $0$。

我们发现，除了若干个 $0$ 或若干个 $1$ 形成的字符串以外，其余所有的字符串都可以变成 $0$。那么我们就可以记录下从开头以来，连续的 $0$ 的个数，与从末尾以前，连续的 $1$ 的个数，若除去上面所记录的字符串，剩下的字符串中有 $0$，就多输出一个 $0$ 就行了。

## 代码

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
	int T, n;
	cin >> T;
	while (T--) {
		string s, ans = "";
		cin >> n >> s;
		int l = 0, r = n - 1;
		while (s[l] == '0')
			l++, ans += '0';
		while (s[r] == '1')
			r--, ans += '1';
		for (int i = l; i <= r; i++)
			if (s[i] == '0'){
				cout << '0';
				break;
			}
		cout << ans << '\n';
	}
	return 0;
}
```


---

## 作者：York佑佑 (赞：0)

## 题意
给你一个字符串 $s$，其中如果 $s_i=1$ 并且 $s_{i+1}=0$，我们可以删除其中一个，问经过 $\inf$ 次操作后字符串字典序最小的字符串。
## 分析
先附上样例详细解释：
```cpp
5
10
0001111111
4
0101
8
11001101
10
1110000000
1
1
```
- 第一个串没有```10```字串,无法删除。

- 第二个串含```10```字串，删除```1```，剩下```001```。
- 第三个串第六个和第七个字符为```10```字串，删去```1```，并且前面的```1```与这个字符又产生了一个```10```字串，删去```1```。再从第二个字符开始，每次删去一个```0```，直到留下一个```0```，再删去第一个字符，留下```01```。
- 第四个串每个```0```都可以与前面的```1```产生```10```串，所以可以删去所有的```0```，留下```111```。
- 第五个串没有```0```，不可删除。

不难发现，任何一个从```1```开始，从```0```结束的串都可以被删成```10```。那我们定义变量 $l$ 和 $r$，并让他们设为**从头开始所有连续```0```的个数**和**从末尾开始所有连续```1```的个数**，并添加进答案字符串中。然后在字符串 $[l,r]$ 范围中有```0```的就输出，然后输出答案字符串。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
string str,ans;
int main()
{
	cin>>t;
	while(t--)
	{
		ans="";//别忘了清空 
		cin>>n>>str;
		int l=0,r=n-1;
		while(str[l]=='0'){ans+='0';l++;}//从头开始所有连续0的个数
		while(str[r]=='1'){ans+='1';r--;}//从末尾开始所有连续1的个数
		for(int i=l;i<=r;i++)
			if(str[i]=='0')
			{
				cout<<0;break;//是0就输出 
			}
		cout<<ans<<endl;//输出答案字符串 
	}
    return 0;
}
```


---

## 作者：Arrtan_73 (赞：0)

# 题目大意
[传送门](https://www.luogu.com.cn/problem/CF1369B)
# 题目思路
典型的找规律题目（~~，毒瘤！找了整整二十分钟！~~）

首先我们可以通过 `10` 简单地推一推。可以发现例如 `1110`，`10000`，`111000` 等数串可以通过若干次操作化为 `10`，也就是形如 `11...10...00` 的数串可以化为 `10`。既然我们已经把 `10` 推广到 `11...10...00` 的形式，那么也就可以把原数串分为若干个 `11...10...00` 的子问题，最终我们可以得到形如 `1010...10` 的数串，经过处理后，也就是 `0`(很简单，想一想就明白了)。

那么原数串即可分为三部分：`00...0`+`0`+`11...1`，前后部分因为没有前导 1 与后缀 0 而不可处理。

PS 若没有中间部分，则直接输出原串。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define f(left,right) for(int i=left;i<=right;i++)
int T, n;
string s;

int main() {
	cin >> T;
	while (T--) {
		cin >> n >> s;
		int l = 0, r = s.size() - 1;
		while (s[l] == '0')//处理部分一
			l++;
		while (s[r] == '1')//处理部分三
			r--;
		if (l > r)//没有部分二，输出原串
			cout << s << endl;
		else {//
			f(0, l)cout << 0;
			f(r + 1, s.size() - 1)cout << 1;
			cout << endl;
		}
	}
	return 0;
}
```


---

## 作者：lelml (赞：0)

### 思路

通过观察，我们不难发现：只要最后的形式是 $1...10...0$ 就不能操作。因此，我们在字符串中除掉前面的 $0$ 和后面的 $1$，剩下的中间部分总能变成 $0$，输出即可。

### Talk is Cheap,Show me the code

```cpp
#include<bits/stdc++.h>
#define C int
#define P main
#define f(a,b) for(int i=a;i<=b;i++)
const int MAXN=114514; 
using namespace std;
C P(){//防伪
	int T,n; 
	cin>>T;
	char str[MAXN]; 
	while(T--){
		cin>>n;//str从1开始存
		f(1,n) cin>>str[i]; 
		int left=1;
		int right=n;
		while(str[left]=='0') left++;
		while(str[right]=='1') right--;//如果左边有0或右边有1，没有完全截掉前面的0和后面的1 
		if(left>right) f(1,n) cout<<str[i]; 
		else{
			f(1,left-1) cout<<0;
			cout<<0;//中间的部分直接处理成0 
			f(right+1,n) cout<<1;
		}
		cout<<endl; 
	}
} 
```



---

## 作者：RioBlu (赞：0)

我们发现：$\{10,110,1110,11110...\}$可以变成$0$，我们将$\{10,110,1110,11110...\}$定义为X

另外，我们发现连续多个$X$的组合可以变成$0$，如：$X_1+X_2=X_1+0=X=0$（$"+"$号表示连接如$"101"+"110"="101110"$）

这时，我们就可以把中间的东西把他删掉了

注：此代码是一个一个删的，如"1100**110**1"变成"110001"，再变成"01"
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,endd,uu;
string n;
int main()
{
	cin>>a;
	while(a--)
	{
		uu=0;
		cin>>b>>n;
		n='0'+n;//补0法，辅助作用，后面会删掉
		iii:
		for(int s=n.size()-1;s>=1;s--)
		{
			if(uu==0&&n[s]=='0')
			{
				uu=1,endd=s;
			}
			if(uu==1&&n[s]=='1')
			{
				uu=2;
			}
			if(uu==2&&n[s-1]=='0')
			{
				uu=0;
				n.replace(s, endd-s+1, "0");
				goto iii;//goto可以值得一学
			}
		}
		n.replace(0,1,"");//删掉前导0
		cout<<n<<endl;
	}
}
```

---

