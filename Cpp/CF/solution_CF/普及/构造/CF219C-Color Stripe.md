# Color Stripe

## 题目描述

A colored stripe is represented by a horizontal row of $ n $ square cells, each cell is pained one of $ k $ colors. Your task is to repaint the minimum number of cells so that no two neighbouring cells are of the same color. You can use any color from 1 to $ k $ to repaint the cells.

## 样例 #1

### 输入

```
6 3
ABBACC
```

### 输出

```
2
ABCACA
```

## 样例 #2

### 输入

```
3 2
BBB
```

### 输出

```
1
BAB
```

# 题解

## 作者：codeLJH114514 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF219C)

# 题目描述

给定一个 $n$ 个字符的字符串 $s$，让你替换其中的一些字符使字符串满足相邻两个字符不相等且只包含前 $k$ 个字母，求更改字符的最小次数和更改后的字符串。（只输出任意一个更改后的字符串即可。）

以上的字符均指大写字母。

# 数据范围

$1 \leq n \leq 5\times10^5$

$2 \leq k \leq 26$

$s$ 只包含前 $k$ 个大写字母

# 解题思路

可以枚举每个字符，如果当前字符不等于前一个字符，那么就替换当前字符为一个合适的字符。（合适的字符应为前 $k$ 个大写字母之一，并不是前后任意一个字符之一。）

寻找最小符合要求的字符可以使用一层 $1 \sim k$ 的循环来做。

代码如下：

```cpp
char Min(int x) {
    if (x == s.size() - 1) // 出界特判。
        return s[x - 1] == 'A' ? 'B' : 'A';
    for (int i = 1; i <= k; i++) {
        char ch = i - 1 + 'A';
        if (ch != s[x - 1] and ch != s[x + 1]) return ch; // 判断是否满足条件。
    }
    return '@'; // 如果不写这行的话会报警告。
}
```

接下来就简单了，枚举每个字符，如果不满足条件就替换次数$+1$，并在原字符串上直接替换。

这样代码也不难写出：

```cpp
#include <iostream>
using namespace std;
int n, k, ans;
string s;
char Min(int);
int main() {
    cin >> n >> k >> s;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            ans += 1; // 累加ans
            s[i] = Min(i); // 原地修改
        }
    }
    cout << ans << "\n" << s; // 原地输出
    return 0;
}
char Min(int x) {
    if (x == s.size() - 1)
        return s[x - 1] == 'A' ? 'B' : 'A';
    for (int i = 1; i <= k; i++) {
        char ch = i - 1 + 'A';
        if (ch != s[x - 1] and ch != s[x + 1]) return ch;
    }
    return '@';
}
```

提交！

然后 #$11\ \ \colorbox{#E74C3C}{\color{#fff}\texttt{WA}}$ 

这是因为我们没有特判 $k \to 2$ 的情况。

如果 $k \to 2$ 的并且形如 $\texttt{AAB}$ 话，我们的 `Min` 函数就会返回缺省的字符，因为只有 $\texttt{AB}$ 可供选择，但是都不满足条件。

那怎么办呢？

由于 $k \to 2$ 只有两种序列，即 $\texttt{ABABAB}\ \cdots$ 和 $\texttt{BABABA}\ \cdots$，所以可以在其中选出更优的解法，输出即可。

特判代码：

```cpp
if (k == 2) {
    string a, b;
    for (int i = 1; i <= n; i++) a += char('A' + (i % 2));
    for (int i = 1; i <= n; i++) b += char('A' + not (i % 2)); // 计算两种序列。
    int ca, cb;
    ca = cb = 0;
    for (int i = 0; i < n; i++) ca += a[i] != s[i];
    for (int i = 0; i < n; i++) cb += b[i] != s[i]; // 计算每种的修改字符数。
    cout << min(ca, cb) << "\n" << (ca < cb ? a : b); // 选择输出
    return 0; // 提前结束
}
```

## 完整代码

```cpp
#include <iostream>
using namespace std;
int n, k, ans;
string s;
char Min(int);
int main() {
    cin >> n >> k >> s;
    if (k == 2) {
        string a, b;
        for (int i = 1; i <= n; i++) a += char('A' + (i % 2));
        for (int i = 1; i <= n; i++) b += char('A' + not (i % 2));
        int ca, cb;
        ca = cb = 0;
        for (int i = 0; i < n; i++) ca += a[i] != s[i];
        for (int i = 0; i < n; i++) cb += b[i] != s[i];
        cout << min(ca, cb) << "\n" << (ca < cb ? a : b);
        return 0;
    }
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            ans += 1;
            s[i] = Min(i);
        }
    }
    cout << ans << "\n" << s;
    return 0;
}
char Min(int x) {
    if (x == s.size() - 1)
        return s[x - 1] == 'A' ? 'B' : 'A';
    for (int i = 1; i <= k; i++) {
        char ch = i - 1 + 'A';
        if (ch != s[x - 1] and ch != s[x + 1]) return ch;
    }
    return '@';
}
```

---

## 作者：alan1118 (赞：2)

一道比较简单的字符串模拟。

## 题意

给定一个字符串 $s$，保证 $s$ 中只存在字母表前 $k$ 个字母。请你求出至少需要梗概几个字符才能使 $s$ 中所有相邻的字符都不相同。

注意：修改后的字符串中也只能出现字母表前 $k$ 个字符。



## 思路

枚举 $s$ 中的每一位字符 $s_i$，如果和 $s_{i-1}$ 相同，就从 `A` 开始，枚举字母表前 $k$ 个字符，找到与 $s_{i-1}$ 和 $s_{i+1}$ 都不一样的字符，直接替换。这样就好了，还是很简单的。（记住这句话）

于是就有了这样的代码：

### Code

```cpp
#include <iostream>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
    int ans = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] == s[i-1])
		{
			ans++;
			for(char j = 'A'; j <= 'A'+k-1; j++)
				if(j != s[i-1] && j != s[i+1])
				{
					s[i] = j;
					break;
				}
		}
	}
	cout << ans << endl << s << endl;
    return 0;
}
```



正当我兴高采烈的提交时：`Wrong Answer on test 11`

为什么呢？因为没有特判 $k = 2$！

为什么要特判呢？我们可以举个例子：当 $s =$ `AABB` ，程序运行到 $s_1$ 时，不会做出任何改变。因为 $k = 2$，而 $s_0$ 和 $s_2$ 已经占满了字母表的前两个字符，所以直到第二重循环结束都不会再找到可替换的字符。

那么这时候就需要特判一下 $k = 2$ 的情况。

我们不难发现，当 $k=2$ 时，更改后的字符串只可能有两种形式：

1. `ABABA...`
2. `BABAB...`

所以把两种情况算出来比较一下，我们就~~终于~~轻松通过了！



下面是完整代码：

### AC Code

``` cpp
#include <iostream>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
    if(k == 2)
    {
        int cnt1 = 0, cnt2 = 0;
        for(int i = 0; i < s.size(); i++)
        {
            if(s[i] != 'A'+(i%2)) cnt1++;
            if(s[i] != 'A'+((i+1)%2)) cnt2++;
        }
        cout << min(cnt1, cnt2) << endl;
        if(cnt1 < cnt2)
            for(int i = 0; i < s.size(); i++)
                cout << char('A'+(i%2));
        else
            for(int i = 0; i < s.size(); i++)
                cout << char('A'+((i+1)%2));
        return 0;
    }
	int ans = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] == s[i-1])
		{
			ans++;
			for(char j = 'A'; j <= 'A'+k-1; j++)
				if(j != s[i-1] && j != s[i+1])
				{
					s[i] = j;
					break;
				}
		}
	}
	cout << ans << endl << s << endl;
	return 0;
}
```

---

## 作者：Edmundino (赞：1)

# 题意

```
给出一个字符串，只包含k种字符，问最少修改多少个字符（不增长新的种类）能够得到一个新的字符串，
这个字符串满足相邻的字符没有相同的。
```
就是说，我们最少可以改变多少个字符，保证得到的新字符串

相邻的的字符没有相等的。

# 分析

用字符串比较难想，

所以我们可以先把每位的字符减去$'A'+1$，

变成数字后，再开一个数组存起来。

这样比较好想，而且代码容易实现。（不要忘了输出的时候要转化回来）

接着我们继续看，

我们可以先遍历整个数组，

当当前的数字等于前一个数字时，

我们就可以循环枚举$1-k$，使枚举的数同时不等前一个数和后一个数。

但是，当$k=2$时我们就需要特判了。

那新的问题就出现了：如何特判？

首先，我们知道的是：当$k=2$时，只有$1,2$两个数字，

所以得到的结果不是$1212121……$就是$21212121……$

那我们就可以讨论这两种情况，

得到改变数字最小的来输出就行了

# 代码

**特判$k=2$的情况**

```cpp
	if(k==2)
	{
		int wa=0,wb=0;
		for(int i=1;i<=lon;i++)
		{
			if(i%2==1)
			{
				if(a[i]!=1)
				wa++;
				if(a[i]!=2)
				wb++;
				
			}
			if(i%2==0)
			{
				if(a[i]!=2)
				wa++;
				if(a[i]!=1)
				wb++;
				
			}
			
		}
		int c=min(wa,wb);
			cout<<c<<endl;
			if(c==wa)
			{
				for(int i=1;i<=lon;i++)
				{
					int we=i%2;
					if(we==1) we=0;
					else if(we==0) we=1;
					cout<<(char)('A'+we);
				}
				
			}
			else
			{
				for(int i=1;i<=lon;i++)
				{
					int we=i%2;
					cout<<(char)('A'+we);
				}
			}
	}
```

**当$k>2$的情况**

```cpp
	if(k>2)
	{
		for(int i=1;i<=lon;i++)
		{
			if(a[i]==a[i-1]&&i!=lon)
			{
				tot++;
				int we=0;
				for(we=1;we<=k;we++ )
			    {
			    	if(we!=a[i-1]&&we!=a[i+1])
			    	  a[i]=we;
			    	
				}
//				cout<<i<<" "<<a[i]<<endl;
			
			}
			if(i==lon&&a[i]==a[i-1])
			{
				tot++;
				int we=0;
				for(we=1;we<=k;we++ )
			    {
			    	if(we!=a[i-1])
			    	  a[i]=we;
			    	
				}
			}
			
		}
		cout<<tot<<endl;
		for(int i=1;i<=lon;i++)
		{
			cout<<(char)(a[i]+'A'-1);
		}
	}
```


**最后送上$AC$代码**

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath> 

using namespace std;

const int N=5e5+50;

int n,k,a[N],tot;

string s;

int main()
{
	cin>>n>>k>>s;
	int lon=s.length();
	for(int i=0;i<lon;i++)
	{
		a[i+1]=s[i]-'A'+1;
	}
	if(k==2)
	{
		int wa=0,wb=0;
		for(int i=1;i<=lon;i++)
		{
			if(i%2==1)
			{
				if(a[i]!=1)
				wa++;
				if(a[i]!=2)
				wb++;
				
			}
			if(i%2==0)
			{
				if(a[i]!=2)
				wa++;
				if(a[i]!=1)
				wb++;
				
			}
			
		}
		int c=min(wa,wb);
			cout<<c<<endl;
			if(c==wa)
			{
				for(int i=1;i<=lon;i++)
				{
					int we=i%2;
					if(we==1) we=0;
					else if(we==0) we=1;
					cout<<(char)('A'+we);
				}
				
			}
			else
			{
				for(int i=1;i<=lon;i++)
				{
					int we=i%2;
					cout<<(char)('A'+we);
				}
			}
	}
	if(k>2)
	{
		for(int i=1;i<=lon;i++)
		{
			if(a[i]==a[i-1]&&i!=lon)
			{
				tot++;
				int we=0;
				for(we=1;we<=k;we++ )
			    {
			    	if(we!=a[i-1]&&we!=a[i+1])
			    	  a[i]=we;
			    	
				}
//				cout<<i<<" "<<a[i]<<endl;
			
			}
			if(i==lon&&a[i]==a[i-1])
			{
				tot++;
				int we=0;
				for(we=1;we<=k;we++ )
			    {
			    	if(we!=a[i-1])
			    	  a[i]=we;
			    	
				}
			}
			
		}
		cout<<tot<<endl;
		for(int i=1;i<=lon;i++)
		{
			cout<<(char)(a[i]+'A'-1);
		}
	}
	return 0;
}
```


---

## 作者：Wrong_Accept (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF219C)
## 题目分析
我们要使这个字符串的**相邻字符不同**，也就是要使这个字符串的**每个字符与前一个字符不同**。  
那么，我们枚举到一个“$s_i = s_{i - 1}$”的情况，就把 $s_i$ 设为一个“最优字符”。  
所谓“最优字符”，就是能使得 $s_i$ **与前后字符都不发生冲突**的字符，也就是使 $s_{i - 1} \ne s_i \ne s_{i + 1}$。  
那么我们就能写出代码了：
```cpp
void solve()
{
    int n, k, ans = 0;
    string s;
    cin >> n >> k >> s;
    auto ch = [&](int x)
    {
        if (x == (int)s.size() - 1)
            return s[x - 1] == 'A' ? 'B' : 'A';
        if (s[x - 1] != 'A' && s[x + 1] != 'A')
            return 'A';
        if (s[x - 1] != 'B' && s[x + 1] != 'B')
            return 'B';
        else
            return 'C';
    };
    for (int i = 1; i < n; i++)
        if (s[i] == s[i - 1])
        {
            s[i] = ch(i);
            ans++;
        }
    cout << ans << '\n' << s << '\n';
    return;
}
```
然后 Wrong answer on test 11。

### 为什么呢？
如果 $k = 2$，那么夹在 `A` 字符与 `B` 字符之间的字符将会被替换为 `A` 与 `B` 之外的字符，显然不符合要求。

### 怎么办呢？
仔细思考你会发现：$k = 2$ 的情况只能改成“**AB 交接**”的形式（例如：`ABABABABA`、`BABABABAB`、`ABABABAB`）
所以只要在**特判**中枚举一遍即可。

## AC code
```cpp
void solve()
{
    int n, k, ans = 0;
    string s;
    cin >> n >> k >> s;
    if (k == 2)
    {
        for (int i = 0; i < n; i++)
            if (i % 2 && s[i] == 'B' || !(i % 2) && s[i] == 'A')
                ans++;
        if (ans < n - ans)
        {
            cout << ans << '\n';
            for (int i = 0; i < n; i++)
            {
                if (i % 2)
                    cout << 'A';
                else
                    cout << 'B';
            }
        }
        else
        {
            cout << n - ans << '\n';
            for (int i = 0; i < n; i++)
            {
                if (i % 2)
                    cout << 'B';
                else
                    cout << 'A';
            }
        }
        cout << '\n';
    }
    else
    {
        auto ch = [&](int x)
        {
            if (x == (int)s.size() - 1)
                return s[x - 1] == 'A' ? 'B' : 'A';
            if (s[x - 1] != 'A' && s[x + 1] != 'A')
                return 'A';
            if (s[x - 1] != 'B' && s[x + 1] != 'B')
                return 'B';
            else
                return 'C';
        };
        for (int i = 1; i < n; i++)
            if (s[i] == s[i - 1])
            {
                s[i] = ch(i);
                ans++;
            }
        cout << ans << '\n' << s << '\n';
    }
    return;
}
```

---

## 作者：Lan_yan (赞：0)

CF 的黄题轻轻松松。

## 思路

题目其实说的不太清楚。

有 $k$ 种字符其实就是从 A 往下推论的**大写**字符。例如 $k=2$ 就是有 A 和 B 两种字符。同时，$k$ 一定小于等于 $26$。

有的人就慌了。

这要用贪心吗？这应该怎么考虑？

不用想的那么复杂。

注意到题目只要求新字符串满足相邻字符互不相同，没有硬性规定，再顺着样例给的输入输出，我们很快能找出规律。

我们只需要从左到右查看每一个字符，如果与**左边**字符相同，那么就从**剩下**的字符中选取符合要求的覆盖就行了。

拿样例 `ABBACC` 来说明一下。

A 没有问题，跳过。

B 没有问题，跳过。

B 有问题，因为后面有 A，改为 C。

A 没有问题，跳过。

C 没有问题，跳过。

C 有问题，考虑到前面的 C，决定使用第一个适合的字符，这里用 A。

最终改了 $2$ 个字符，最终的字符串为 `ABCACA`。

考虑到 $N \le 5 \times 10^5$，所以数组要开多大大家心里清楚。

#### 非常简单是不是？但是，你以为这就完了吗？

开开心心地提交代码后，突然，一个红色的 WA 跳了出来！

我们似乎忘掉了某种特殊情况：$k=2$！

这时我们只能从 A 或 B 中选答案，可无论选哪个都不行。

考虑到 $k=2$ 时只需判断 `ABA` 式字符串或 `BAB` 式字符串的方案，所以也是一件非常简单的事。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,h[30],ans=0;
char s[500005];
int main()
{
	int i,j;
	scanf("%d%d\n",&n,&k);
	scanf("%s",s);
	if(k==2)//特判
	{
		int wer=0;
		char p1[500005],p2[500005];
		for(i=0;i<n;i++)//p1是ABA式，p2是BAB式
		{
			p1[i]='A'+i%2;
			p2[i]='A'+(i+1)%2;
		}
		for(i=0;i<n;i++)
		{
			if(s[i]!=p1[i])ans++;
			if(s[i]!=p2[i])wer++;
		}
		if(ans<wer)//p1更好时
		{
			printf("%d\n",ans);
			for(i=0;i<n;i++)printf("%c",p1[i]);
		}
		else//p2更好时
		{
			printf("%d\n",wer);
			for(i=0;i<n;i++)printf("%c",p2[i]);
		}
		return 0;//直接提前结束
	}
	for(i=1;i<n;i++)//k>2的情况
	{
		if(s[i]==s[i-1])
		{
			ans++;
			for(j=1;j<=k;j++)//从中枚举剩下符合条件的字符
			{
				if(j!=s[i-1]-'A'+1&&j!=s[i+1]-'A'+1)
				{
					s[i]=j+'A'-1;break;
				}
			}
		}
	}
	printf("%d\n",ans);
	for(i=0;i<n;i++)printf("%c",s[i]);//完美地输出
	return 0;
}
```

完结撒花！

---

## 作者：ylch (赞：0)

# [CF219C](https://www.luogu.com.cn/problem/CF219C) Color Stripe 题解

题面：给出一个字符串，只包含 $k$ 种字符，问最少修改多少个字符（不增长新的种类）能够得到一个新的字符串，这个字符串满足相邻的字符没有相同的。

## PART1. 解题思路

这道题可以用贪心的思路去做，从前往后顺序修改字符得到的修改次数一定是最小的。

修改时有几个要点：

1. 题面中说“只包含 $k$ 种字符”，所以我们修改的字符应该都是 $A \sim A$ 往后 $k$ 个字符里的。

2. 对于每个位置，如果和前一个一样，就不断枚举 $k$，找到第一个不一样的，注意前后都不同才行。

3. 交上去 $\text{\color{red}WA}$，查看样例发现是当 $k=2$ 时，且只有 $A,B$ 两种字符，这时我们枚举的 $k$ 只可能是 $A$ 或 $B$，可能不满足条件（例如 $\text{BBA}$）。仔细想，$k=2$ 时只有两种排法：$\text{ABABAB} \cdots$ 和 $\text{BABABA} \cdots$ 两种情况，分别计算花销取 $\min$ 即可。

## PART2. AC 代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

int n,k,ans;
char s[500005];

signed main()
{
	cin >> n >> k >> s;
	
	if (k == 2)	//特判
	{
		char a[500005],b[500005];
		for (int i = 1; i <= n; i++) a[i-1] = 'A' + (i % 2);
		for (int i = 1; i <= n; i++) b[i-1] = ('A' + !(i % 2)); //计算两种交叉序列
		int sa = 0, sb = 0;
		for (int i = 0; i < n; i++) sa += a[i] != s[i];
		for (int i = 0; i < n; i++) sb += b[i] != s[i]; //计算每种的修改字符数。
		cout << min(sa, sb) << "\n" << (sa<sb ? a : b); 
		return 0;
	}
	
	for (int i=1; i<n; i++)
	{
		if (s[i] == s[i-1])
		{
			ans++;
			for (int j=1; j<=k; j++)
			{
				char ch = j+'A'-1;
				if (s[i]!=ch && s[i+1]!=ch)
				{
					s[i] = ch;
					break;
				}
			}
		}
	}
	cout << ans << endl << s << endl;
	return 0;
}
```

## END

管理员大大辛苦啦~

谢谢大家！

---

## 作者：Spir1t (赞：0)

不是非常简单好想。


------------
思路呢就是遍历字符串中的每个字符。如果当前字符和前一个字符相同，说明需要进行修改。

将 $1$ 到 $k$ 中选择一个不同的字符，将当前字符修改为这个颜色，然后增加修改次数。

完成遍历后，输出修改次数和修改后的字符串。

欸？好像错了一个点？

别忘了！我们还需判断 $k=2$ 的情况！

为了使相邻字符的颜色不同，可以将字符串分为两种交替序列，即奇数位置的字符一种颜色，偶数位置的字符另一种颜色。计算两种交叉序列的修改字符数，并输出较小的那个作为最小修改次数。同时，根据最小修改次数选择相应的交叉序列作为修改后的字符串。

时间复杂度 $O(n)$，可以通过。

[CODE](https://www.luogu.com.cn/paste/14atcbz1)

---

## 作者：王熙文 (赞：0)

## 思路

我最开始看这题以为只需要输出最少改变的数……

如果是这样的一个问题，我们使用 dp 解决：

设 $dp_{i,c}$ 表示前 $i$ 个字符，将第 $i$ 个字符变成字符 $c$（代码中是 `c+'A'-1`） 的最小操作数，特别的，若 $c=0$，表示不变。

边界条件即 $dp_{1,0}=0,dp_{1,c}=1(1 \le c \le k)$。

先考虑 $dp_{i,0}$。

设原串为 $s$。

若 $s_i \not= s_{i-1}$，那么 $dp_{i,0}=\min(dp_{i,0},dp_{i-1,0})$。

然后遍历 $c$ 从 $1 \sim k$，如果 $s_i \not= c$（`c+'A'-1`），则 $dp_{i,0}=\min(dp_{i,0},dp_{i-1,c})$

接下来处理 $dp_{i,c}$。

若 $c \not= s_{i-1}$，那么 $dp_{i,c}=\min(dp_{i,c},dp_{i-1,0})$。

然后遍历 $c1$ 从 $1 \sim k$，如果 $c \not= c1$，那么 $dp_{i,c}=\min(dp_{i,c},dp_{i-1,c1})$。

最终的答案就是 $\min\{dp_{n,i}(0 \le i \le k) \}$。

接下来考虑如何求操作后的串。

我们用比较套路，记录来时的路径的方法解决：用 $from_{i,c}$ 表示当前最优情况来自 $s_{i-1}$ 变成哪个。

时间复杂度：$O(n k^2)$（3e8 能一遍过就离谱）

优化：会看遍历 $c1$ 的过程，我们对于每一个 $c$ 都要求一遍。实际上可以先记录第一小和第二小的，如果当前 $c$ 正是第一小的方案改成的字符，那就用第二小的，否则用第一小的。

时间复杂度：$O(nk)$

## 参考代码

（这个代码是 $O(nk^2)$ 的，$O(nk)$ 请读者自己实现）

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;

int dp[500010][27];

int from[500010][27];

stack<char> st;

int main()
{
	memset(dp,0x3f,sizeof(dp));
	int n,k;
	cin>>n>>k>>s;
	s=" "+s;
	dp[1][0]=0,from[1][0]=-1;
	for(int i=1; i<=k; ++i) dp[1][i]=1,from[1][i]=-1;
	for(int i=2; i<=n; ++i)
	{
		if(s[i-1]!=s[i]) dp[i][0]=dp[i-1][0],from[i][0]=0;
		for(int j=1; j<=k; ++j)
		{
			if(j+'A'-1!=s[i])
			{
				if(dp[i][0]>dp[i-1][j])
				{
					dp[i][0]=dp[i-1][j];
					from[i][0]=j;
				}
			}
		}
		for(int j=1; j<=k; ++j)
		{
			if(j+'A'-1!=s[i-1]) dp[i][j]=dp[i-1][0]+1,from[i][j]=0;
			for(int ii=1; ii<=k; ++ii)
			{
				if(ii!=j && dp[i][j]>dp[i-1][ii]+1)
				{
					dp[i][j]=dp[i-1][ii]+1;
					from[i][j]=ii;
				}
			}
		}
	}
	int ans=0x3f3f3f3f,wz;
	for(int i=0; i<=k; ++i)
	{
		if(ans>dp[n][i])
		{
			ans=dp[n][i];
			wz=i;
		}
	}
	printf("%d\n",ans);
	int now=n;
	while(from[now][wz]!=-1)
	{
		st.push(wz==0?s[now]:wz+'A'-1);
		wz=from[now][wz],--now;
	}
	st.push(wz==0?s[1]:wz+'A'-1);
	while(!st.empty()) cout<<st.top(),st.pop();
	return 0;
}
```

---

## 作者：流绪 (赞：0)

模拟！

相邻位置字母不能相同,那么我们遍历整个字符串,如果某个位置和前面那个位置相同,就去找和前一个位置、后一个位置的字母不同的字母。

但是此时就出现问题了，如果 k=2，那么上述就找不到了啊？

所以我们只要在 k>2 的情况下用上述方法。在 k=2 的时候，字符串只有两种可能 ABABA... 与 BABAB... 所以我们遍历两次字符串，分别计算出字符串变成这两个的哪一个所需次数最小就好啦。

下面是 AC 代码,细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
using namespace std;
char s[maxn];
int n,k;
int f(char a,char b)
{
	for(int i=0;i<k;i++)
		if(i+'A'!=a&&i+'A'!=b)
			return i;
}//找一个和前一个位置、后一个位置不同的字母
signed main()
{
	ios::sync_with_stdio(0);
  	cin >> n >> k;
  	cin >> (s+1);
  	if(k==2)
  	{
  		int a=0,b=0;//计数器
  		for(int i=1;i<=n;i++)
  			if(i%2&&s[i]!='A')
  				a++;
  			else if(i%2==0&&s[i]!='B')
  				a++;
  		for(int i=1;i<=n;i++)
  			if(i%2&&s[i]!='B')
  				b++;
  			else if(i%2==0&&s[i]!='A')
  				b++;
  		cout << min(a,b) << endl;
  		if(a<b)
  			for(int i=1;i<=n;i++)
  				if(i%2)
  					cout << 'A';
  				else 
  					cout << 'B';
		else
			for(int i=1;i<=n;i++)
  				if(i%2)
  					cout << 'B';
  				else 
  					cout << 'A';
  		return 0;
	}//特判 k=2
  	int cnt = 0;//计数器
  	for(int i=2;i<=n;i++)
  		if(s[i] == s[i-1])
  			if(i<n)
  			{
  				int x=f(s[i-1],s[i+1]);
		  		s[i] = x+'A',cnt++;
		  	}
		  	else//特判最后一个位置
		  		s[i] = (s[i-1]-'A'+1)%k+'A',cnt++;
	cout << cnt <<endl <<(s+1);
	return 0;
}  
```


---

