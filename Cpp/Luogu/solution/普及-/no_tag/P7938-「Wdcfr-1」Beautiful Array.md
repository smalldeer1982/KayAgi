# 「Wdcfr-1」Beautiful Array

## 题目描述

在这个问题中，我们将由 `(` 和 `)` 组成的序列定义为“括号序列”。

*正规括号序列* 的定义如下：

1. `()` 是一个正规括号序列。
2. 如果 `A` 是一个正规括号序列，那么 `(A)` 也是一个正规括号序列。
3. 如果 `A` 和 `B` 是正规括号序列，那么 `AB` 也是一个正规括号序列。

例如：`()`, `(())` 和 `()()` 都是正规括号序列，但 `)(`, `()(` 不是。

特别地，在这个问题中，空序列**不是**一个正规括号序列。

现在，~~可爱的~~ Ran 给你一个长度为 $n$ 的括号序列 $s$。她希望你构造 $2 \cdot m$ 个**严格递增**的数组。我们将它们记作 $p_1,p_2,\cdots,p_{2m}$（你可以将其中任何一个留空）。你需要确保所有从 $1\sim n$ 的整数在这些数组中**恰好出现一次**。

一个数组 $p_i=\{r_1,r_2,\cdots,r_k\}$ 是*美丽的*，如果 $\{s_{r_1},s_{r_2},\cdots,s_{r_k}\}$ 是一个正规括号序列。

Ran 想知道是否有可能构造这些数组，使得至少 $m$ 个 $2 \cdot m$ 数组是“美丽数组”。

## 说明/提示

### 解释

对于第一个测试用例，我们可以构造 $p_1=\{1,2\}$ 和 $p_2=\{\}$。所以 $p_1$ 是一个“美丽数组”。

对于第二个测试用例，很明显我们不能用两个数字构造 $99$ 个美丽数组。

### 约束

$1\le T,n,m\le 200$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
2 1
()
2 99
()```

### 输出

```
1
0```

# 题解

## 作者：Tzs_yousa (赞：9)

## 分析题意
定义 $A$ 为 $B$ 的子序列当且仅当 $A$ 能由 $B$ 在顺序不改变的前提下删除若干元素后得到。

这句话是精髓，注意不是切开是删除，那是不是说我们统计有多少组匹配的括号，我们通过括号匹配求出来的匹配的括号的数量就是最多的可以匹配的，如果这么值大于我们要比较的 $m$ ， 那么肯定是可以满足的。
### 括号匹配（栈类型）
```cpp
for (int i = 1; i <= n; i++)
		{
			if(s[i] == '(') 
			{
				st[++top] = i;//栈顶就是最新出现的左括号
			}
			else if(top)/与距离自己最近的那个括号匹配，匹配之后弹出栈就可以防止之后的影响
			{
				top--;
				ans++;
			}
		}
```
然后，随便放一下全套代码吧，虽然上面已经差不多了
```cpp
#include<bits/stdc++.h>
#define int long long
const int MAXN = 1001;
using namespace std;
int t, n, m, len, s1, s2, ans, st[MAXN];
char s[MAXN];
signed main()
{
	ios::sync_with_stdio(false);
	cin >> t;
	while(t--)
	{
		int top = 0, ans = 0;
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
		{
			cin >> s[i];
		}
		for (int i = 1; i <= n; i++)
		{
			if(s[i] == '(') 
			{
				st[++top] = i;
			}
			else if(top)
			{
				top--;
				ans++;
			}
		}
		if(ans >= m)cout << 1 << endl;
		else cout << 0 << endl;
	}
	return 0;
}

```



---

## 作者：XiongRan (赞：5)

# 题意

虽然题面没有巴拉巴拉说一大通，但我们还是可以简化一下题意。

因为可以有空子序列，所以可以直接理解成能不能构造出$m$个以上合法序列就行。

这样，题目就简化成了**括号匹配**。

# Code

括号匹配是运用栈的经典思想。

每次读入一个括号，若是左括号，则压入栈中。若是右括号，将栈顶的左括号弹出，计数器++。最后时，是空栈则匹配成功，不是反之。

下面的代码运用了这个思想，但**没有**用数组模拟栈或者用STL。
```
//核心代码，首先要理解
//并没有手敲栈
cin >> n >> m;
cin >> s;
int ans=0,cnt=0;
cin >> n >> m;
cin >> s;
for(int i=0;i<n;i++){
	if(s[i] == '('){//压入栈,计数器++。
		cnt++;
	}else{
		if(cnt){
			ans++;
			cnt--;
		}
	}
}
```

---

## 作者：StayAlone (赞：2)

### 题意  
将一个长度为 $n$ 的括号序列分成一些子序列，使得括号匹配的子序列数量至少为 $m$。可行输出 $1$，不可行输出 $0$。**子序列可为空，但空串不是合法的括号序列。**

### 思路

显然每一个子序列需要一对括号即可。所以如果一个左括号能找到一个右括号与之配对，就将其作为一个子序列。统计这样的子序列数量 $cnt$，若 $cnt \geqslant m$，输出 $1$，反之输出 $0$。

统计 $cnt$ 的具体实现比较简单：拿一个栈，从左往右遍历，遇到左括号就压入栈，遇到右括号就检查栈里面有没有左括号，若有，就弹出一个，$cnt$ 累加 $1$；若没有，就过掉。  

更加优美的实现是用 $p$ 来表示“栈”里面的左括号数量，但是不需要这个栈了。弹出栈内元素对应的是 $p = p - 1$，压入元素对应 $p = p + 1$，$p > 0$ 即栈非空。  


[AC code 记录](https://www.luogu.com.cn/record/62749167)
```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i = j; i <= int(n); ++i)
#define rep2(i, j, n) for (int i = j; i >= int(n); --i)
#define ......
using namespace std;
typedef long long ll;
typedef ......
const int MAXN = 1e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc
{
	template <typename T>
	il void read(T &x)
    
    il int read()
	
	template <typename T>
	il void write(T x)
} // 奇妙缺省源
using namespace stupid_lrc;
int T, n, m; string s;

int main()
{
	read(T);
	while (T--)
	{
		read(n); read(m); cin >> s;
		int cnt = 0, p = 0;
		rep1(i, 0, n - 1)
		{
			if (s[i] == '(') ++p;
			else if (p) --p, ++cnt;
		}
		write(cnt >= m); ptc('\n');
	}
	rout;
}
```

---

## 作者：Jerrlee✅ (赞：2)

## 题意
共 $t$ 组数据。

将一个长度为 $n$ 的括号串分为 $2m$ 个子序列（子序列可以为空，且每个字符都必须分完），使得至少 $m$ 个子序列为匹配的括号序列。**空序列不算匹配的括号序列**。无解输出 $0$，否则输出 $1$。
## 思路
先计算出有几对括号序列，将其与 $m$ 比较，小于则无法满足。
## 代码
```cpp
#include<cstdio>
int main(){
	int n,m,t;
	char c;
	scanf("%d",&t);
	while(t--){
		int to1=0,to2=0,ans=0; //tot1 是左括号数量，tot2 是右括号长度，ans 为可行的括号序列
		scanf("%d%d\n",&n,&m);
		for(int i=1;i<=n;i++){			
			c=getchar();
			if(c=='(') to1++;
			else{
				to2++;
				if(to1) to1--,to2--,ans++;
			}
		}
		if(ans<m) printf("0\n"); //小于则无法满足
		else printf("1\n"); //反之即可
	}
}
```
[AC记录](https://www.luogu.com.cn/record/62407010)

---

## 作者：Shunpower (赞：2)

## 思路

模拟。

考虑计算字符串中匹配括号的个数。因为每一个匹配括号组一定对应了一个`()`的子序列，而我们需要使得匹配的括号子序列最多，所以匹配括号的个数一定等于匹配括号子序列的最多个数。

先求一下匹配括号的个数，看看是不是 $\geqslant m$ 即可。

## 代码

非常好写。

```
void solve(){
	cin>>n>>m;
	cin>>s;
	while(!st.empty()){
		st.pop();//清栈很重要
	}
	int cnt=0;
	for(int i=0;i<s.length();i++){//计算匹配括号的数量
		if(!st.empty()&&st.top()=='('&&s[i]==')'){
			st.pop();
			cnt++;
			continue;
		}
		st.push(s[i]);
	}
	if(cnt>=m){//判断
		puts("1");
	}
	else{
		puts("0");
	}
}
```

---

## 作者：yzy1 (赞：2)

考虑到最优构造方案一定是把所有括号序列尽可能的构造成 `()`，考虑贪心，对于每一个左括号，寻找到它后面未被匹配的第一个右括号，进行匹配即可。

在整个串都匹配完成后，如果得到的 `()` 串组数 $\ge m$，则说明有合法的构造方案，否则说明没有。

至于时间复杂度，如果你是对于每个左括号，暴力寻找它右边的第一个没匹配的右括号，则复杂度为 $O(Tn^2)$。当然，你也可以使用一个 `queue` 来将复杂度优化为 $O(Tn)$，但是介于此题的数据范围，没有优化的必要。

```cpp
char s[100005];
int n, m, T;

signed main() {
  in(T);
  while(T--) {
    queue<int> q;
    in(n)(m)(s + 1);
    re (i, n)
      if (s[i] == ')') q.push(i);
    int ans = 0;
    re (i, n)
      if (s[i] == '(') {
        while (q.size() && q.front() < i) q.pop();
        if (q.size()) ++ans, q.pop();
      }
    out(ans >= m ? "1\n" : "0\n");
  }
  return 0;
}
```

---

## 作者：哈士奇憨憨 (赞：1)

## [传送门](https://www.luogu.com.cn/problem/P7938)
## 题目大意
试将一个长度为 $n$ 的括号串分为 $2m$ 个子序列，使得至少 $m$ 个子序列为匹配的括号串。空序列不算匹配的括号序列。无解请输出 `0`，否则输出 `1`。

定义 $A$ 为 $B$ 的子序列当且仅当 $A$ 能由 $B$ 在顺序不改变的前提下删除若干元素后得到。
## 思路
将字符串中的括号分成最小单位的括号 `()` ，比如 `()()` 可以分成 `()` 和 `()` ，但 `))((` 已经不能分了，因为一个子序列要在不能改变顺序的前提下删除若干元素后得到。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
char a[205];
int main(){
	cin >> t;
	while(t--){
		int ans = 0,ans1 = 0;
		cin >> n >> m >> a;
		for(int i = 0; i < n; i++){
			if(a[i] == '('){
				ans++;//如果第i位是 ( ，就是一个最小单位，还不能分。
			}else{
				if(ans > 0) {//如果第i位是 ) 且 ( 的个数大于0
					ans1++;//最小单位的括号加1
					ans--;// ( 个数减1
				}
			}
		}
		ans1 >= m ? cout << 1 << endl : cout << 0 << endl;
	}
	return 0;
} 
```

---

## 作者：user470883 (赞：1)

## 思路：
我们想要的最优解就是尽量构成一个完整的括号 `()` , 我们将这个括号细分，分成 `(` 和 `)` ，我们先在字符串里找到 `(` ,根据 `(` 去匹配 `)` 即可。

然后，我们再进行题目要求的判断：如果 `()` $≥ m$ ，输出即可。

## AC CODE:
```
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,m,t;
	char c;
	cin >> t;
	while(t--)
	{
		int a=0,b=0,ans=0;
		scanf("%d%d\n",&n,&m);//输入
		for(int i=1;i<=n;i++)
		{			
            c=getchar();
			if(c=='(')//左括号判断
			{
				a++;
			}
			else//右括号判断
			{
				b++;
				if(a)
				{
					a--;
					b--;
					ans++;
				}
			}
		}
		if(ans<m)//输出判断
		{
			cout << 0 << endl;
		}
		else
		{
			cout << 1 << endl;
		}
	}
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/62507542)

球管理通过。

---

## 作者：MattL (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/P7938)

~~这题是道语文（shui）题~~

---

**题意：**

题面：

>定义一个字符串为括号串当且仅当其仅由 ```(``` 和 ```)``` 组成。
试将一个长度为 $n$ 的括号串分为 $2m$ 个子序列，子序列可以为空，且每个字符都必须分到恰好一个子序列中。使得至少 $m$ 个子序列为匹配的括号串。**空序列不算匹配的括号序列**。无解请输出 $0$，否则输出 $1$。本题多组数据，其中数据组数为 $T$。
定义 $A$ 为 $B$ 的子序列当且仅当 $A$ 能由 $B$ 在顺序不改变的前提下删除若干元素后得到。

额……看不懂

换成某同学的理解：

>将一个长度为 $n$ 的字符串 $S$ 分为 $2m$ 个子序列 ，问是否可以做到在 $2m$ 个子序列中，有至少 $m$ 个是合法的。

还能看懂。

my理解：

>每组数据（共有 $T$ 组）给你一个长度为 $n$ 的字符串 $S$ ，求你切开后括号字符串合法的截点数（不包括最前，包括最后）是否 $\geqslant m$。

如：
```()()```

1. 我们可以从中间切：```()  切  ()```。
2. 从最后切：```()()   切  ```。

所以，这个字符串的合法截点数为 $2$。（注意，不能从最前切）

---

**解题：**

了解了题意后，我们就可以~~轻松~~地写代码啦！

1. 我们可以暴力搜索目前的前面是否合法，时间复杂度：$\Theta(Tn^2)$（辣摸简单就不写啦）
2. 我们可以用 ```queue``` 存储括号，时间复杂度：$\Theta(Tn)$（已有题解辣）
3. 我们可以用一个变量来记录目前未匹配的左括号数量，时间复杂度同上，下面是代码

---

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,cnt,ans;
string s;
int main()
{
	cin>>t;//数据组数
	while(t--)
	{
		cin>>n>>m>>s;//输入长度，对比数m，字符串
		cnt=ans=0;//cnt就是辣各记录目前未匹配的左括号数量的变量，ans是截点数
		for(int i=0;i<n;i++)
		{
			if(s[i]=='(')cnt++;
			else if(cnt)cnt--,ans++;//注意cnt不能为0
		}
		if(ans>=m)cout<<1<<endl;//判断
		else cout<<0<<endl;
	}
	return 0;
}
```

---

## 作者：heaksicn (赞：0)

## 1 题意
将一个长度为 $n$ 的字符串 $S$ 分为 $2m$ 个子序列 ，问是否可以做到在 $2m$ 个子序列中，有至少 $m$ 个是合法的。
## 2 分析
由于我们要让尽量多的子序列合法，那么可以考虑贪心。  
一个合法的括号序列最少是 $ () $ ，那么，我们就可以在字符串里寻找有多少个这样的子序列。  
可以使用类似于括号匹配的思想，每次找到一个左括号就把它压进栈里，如果遇到一个右括号并且栈是非空的，那么就找到了一个合法的 $()$ ，就将左括号出栈的同时记录答案。  
最后判断是否有大于等于 $m$ 个合法括号对即可。  
时间复杂度 $O(Tn)$ 。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,m,T;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		cin>>s;
		int ans=0,now=0;//ans记录合法括号对的个数，now记录栈中左括号的个数，
		for(int i=0;i<n;i++){
			if(s[i]=='('){//左括号就压进栈里
				now++;
			}
			if(s[i]==')'&&now){//右括号如果栈中还有左括号，就记录答案，出栈
				now--;
				ans++;
			}
		}
		if(ans>=m) cout<<1<<endl;//判断
		else cout<<0<<endl;
	}
	return 0;
} 
```


---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7938)

最优情况肯定是尽量保证所有括号序列均为 `()` 的形式，

因此贪心可以解决，对于每一个 `(`，找到离他最近的未匹配过的 `)`，最后计算对数即可。

如果对数 $\ge m$ 则输出 `1`，否则输出 `0`。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[205];//记录有没有被匹配过
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));
		int n,m;
		cin>>n>>m;
		string str;
		cin>>str;
		int tmp=0;
		for(int i=0;i<str.size();i++){
			if(str[i]=='('){
				for(int j=i+1;j<str.size();j++){
					if(str[j]==')'&&!vis[j]){
						tmp++;
						vis[j]=1;
						break;
					}
				}
			}
		}
		if(tmp<m){
			cout<<"0\n";
		}else{
			cout<<"1\n";
		}
	}
	return 0;
}
```

$Tips:$ 多测不清空，爆零两行泪！

---

## 作者：syf2008 (赞：0)

这是一道模拟题。

首先要理解：

1. 匹配的括号序列：

匹配的括号序列指：

1. ```()```

1. ```(())```

以此类推

2. 子序列：

子序列指可以跨跃取的。

比如：

$((())$

我可以取 $1$ 号位上的 $($ 和 $5$ 号位上的 $)$

3. 至少 $m$ 个：

说明括号序列的数量 $\geq m$ ，所以要尽可能的取得多。什么情况下最多呢 $?$

当然是每个子序列只有一个匹配的括号序列，就像这样： $()$ 。

所以这题简化为：

求最大括号匹配数量（允许不连续）。

时间复杂度 $O(\sum_{i=1}^Tn_i)$

```
#include <bits/stdc++.h>
using namespace std;
int t,n,m,w,zuo,you,sum;
char c;
string a;
int read()
{
	w=0;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		w=(w<<3)+(w<<1)+c-48;
		c=getchar();
	}
	return w;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		m=read();
		cin>>a;
		zuo=0;//左括号数量
		you=0;//右括号数量
		sum=0;//子序列括号匹配的数量
		for(int i=0;i<a.size();i++)
		if(a[i]=='(')//如果是左括号，左括号数量+1
		zuo++;
	else if(a[i]==')')
		{
			if(zuo>0)//如果左括号数量<0，证明无法匹配，并且右括号在后面无法用到（后面的左括号无法与前面的右括号匹配）
			{
				zuo--;
				sum++;
			}
		}
		if(sum>=m)
		printf("1\n");
	else printf("0\n");
	}
}
```

---

## 作者：tongyanmin (赞：0)

## Solution
首先注意到子序列可以为空，所以我们只需要考虑如何构造 $m$ 个以上合法序列即可。

不妨考虑如何使取出的合法序列数量最多。首先，最简单的序列一定是 `()`，且全部选 `()` 显然能使合法序列数最多。

至此，题目就被转化成了求原字符串有几对能匹配的 `(` 和 `)`。实现起来非常简单。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
string x;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		cin>>x;
		int l=x.size(),nl=0,nr=0;
		for(int i=0;i<l;i++){
			if(x[i]=='(')nl++;
			if(x[i]==')'&&nl>0){
				nr++;
				nl--;
			}//统计合法序列数目
		}
		if(m>nr)cout<<0<<endl;
		else cout<<1<<endl;
	}
}
```


---

