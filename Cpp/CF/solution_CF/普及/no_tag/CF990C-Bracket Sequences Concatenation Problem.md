# Bracket Sequences Concatenation Problem

## 题目描述

A bracket sequence is a string containing only characters "(" and ")".

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()()", "(())" are regular (the resulting expressions are: "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

You are given $ n $ bracket sequences $ s_1, s_2, \dots , s_n $ . Calculate the number of pairs $ i, j \, (1 \le i, j \le n) $ such that the bracket sequence $ s_i + s_j $ is a regular bracket sequence. Operation $ + $ means concatenation i.e. "()(" + ")()" = "()()()".

If $ s_i + s_j $ and $ s_j + s_i $ are regular bracket sequences and $ i \ne j $ , then both pairs $ (i, j) $ and $ (j, i) $ must be counted in the answer. Also, if $ s_i + s_i $ is a regular bracket sequence, the pair $ (i, i) $ must be counted in the answer.

## 说明/提示

In the first example, suitable pairs are $ (3, 1) $ and $ (2, 2) $ .

In the second example, any pair is suitable, namely $ (1, 1), (1, 2), (2, 1), (2, 2) $ .

## 样例 #1

### 输入

```
3
)
()
(
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
()
()
```

### 输出

```
4
```

# 题解

## 作者：yuheng_wang080904 (赞：2)

## 题意
给出 $ n $ 个字符串，保证只包含 $ ( $ 和 $ ) $ ，求从中取 2 个字符串连接后形成合法的括号序列的方案数，每个串都可以重复使用。

## 思路
我们需要连接2个字符串，假设连接 $ S_i $ 和 $ S_j $,则在 $ S_i $ 中，每个 $ ) $ 都会有一个对应的 $ ( $ 来匹配，否则拼接后肯定不合法。同样的,在 $ S_j $ 中，每个 $ ( $ 都会有一个对应的 $ ) $ 来匹配，否则拼接后肯定不合法。

对于连接在前面的 $ S_i $，我们可以用栈来维护 $ ( $ ，每当遇到 $ ) $ 时弹出，保证匹配。如果出现有 $ ) $ 无法匹配，就说明 $ S_i $ 不合法。如果 $ S_i $ 合法，则记录下它所剩下的 $ ( $ 的个数 $ l_i $。同理，对于 $ S_j $ 我们可以用另一个栈来维护 $ ) $，每当遇到 $ ( $ 时弹出，保证匹配。如果出现有 $ ( $ 无法匹配，就说明 $ S_j $ 不合法。如果 $ S_j $ 合法，则记录下它所剩下的 $ ) $ 的个数 $ r_j $。可以用 $ cnt $ 数组进行储存。

做到 $ S_i $ 和 $ S_j $ 均合法后，如果最后剩下的 $ ( $ 与 $ ) $ 能够互相匹配，即 $ l_i = r_j $ 时， $ S_i $ 和 $ S_j $ 能够组成合法括号序列。

## 代码
下面放上无注释代码！希望大家都能够学会解法，自己完成这道题。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 300005;
int cnta[MAXN], cntb[MAXN], n, m;
char str[MAXN];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		int l = strlen(str + 1), tp = 0;
		for (int j = 1; j <= l; j++) {
			if (str[j] == '(') ++tp;
			else if (tp > 0) --tp;
			else { tp = -1; break; }
		}
		if (tp >= 0) ++cnta[tp];
		m = max(m, tp);
		tp = 0;
		for (int j = l; j > 0; j--) {
			if (str[j] == ')') ++tp;
			else if (tp > 0) --tp;
			else { tp = -1; break; }
		}
		if (tp >= 0) ++cntb[tp];
		m = max(m, tp);
	}
	ll res = 0;
	for (int i = 0; i <= m; i++)
		res = res + (ll)cnta[i] * cntb[i];
	printf("%lld\n", res);
	return 0;
}
```


---

## 作者：oimaster (赞：1)

原题链接：https://codeforces.com/problemset/problem/990/C
题目翻译：

- 懒
- [在这里看翻译吧](https://www.luogu.com.cn/problem/CF990C)

若使用暴力枚举，时间复杂度为 $O(n^2)$，超时。

考虑优化，使用栈维护每个括号串，模拟匹配过程，算出每个串无法匹配的左括号、右括号个数。
若一个串有无法匹配的左括号，同时有无法匹配的右括号，那么这个串必像这样子：`)(`，无法使用。
开一个数组维护无法匹配的左括号个数，统计后最后顺推一遍算出答案，这里比较考微观，可查看我的代码。
注意！作者 `WA` 了 $8$ 次。十年 OI 一场空，不开 `long long` 见祖宗！

[OI-Master 的代码点这里。](https://www.luogu.com.cn/paste/gkqg2u8t)

---

## 作者：D_xbang (赞：0)

## 题目大意：
给出 $n$ 个只含括号字符串，求取两个字符串组成正确的括号序列的方案数，其中每个字符串可以重复使用。


---

## 思路：

通过样例可知，已匹配的括号与其他的括号链接后，不会影响结果。所以统计每个字符串左右括号的数量，用一个结构体来储存。

```cpp
struct node {
	int x, y;// x为未配备左括号的数量 y为未配备右括号的数量
	string c;// 括号
} a[N];
```
### 接下来就是分类讨论：
- 若 $$i_{x}=0$$ 且 $$i_{y}=0$$，便只有 $\texttt{((((}$ 或 $\texttt{)))))}$ 这种可以匹配，即 $$j_{x}=0$$ 或 $$j_{y}=0$$。
- 若 $$i_{x}=0$$，满足 $$j_{x}=i_{y}$$ 的字符串才能与它连接。
- 若 $$i_{y}=0$$，满足 $$j_{y}=i_{x}$$ 的字符串才能与它连接。
- 形如 $\texttt{)))(((}$ 其中 $$i_{x}>0$$，$$i_{y}>0$$，加上任何括号也匹配不了。
- 用两个桶记录左右括号每种情况的数量。
- 最后模拟即可。

---

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3 * 1e5 + 10;
struct node {
	int x, y;
	string c;
} a[N];
ll n, zkh[N], ykh[N], ans;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].c;
		string s = a[i].c;
		int l = s.size();
		for (int j = 0; j < l; j++) {
			if (s[j] == '(') a[i].x++;
			else if (!a[i].x) a[i].y++;
			else a[i].x--;
		}
		if (!a[i].x) zkh[a[i].x]++;
		if (!a[i].y) ykh[a[i].y]++;
	}
	for (int i = 1; i <= n; i++) {
		if (!a[i].x && !a[i].y) {
			ans += zkh[0];
			continue;
		}
		if (!a[i].x) ans += ykh[a[i].y];
	}
	cout << ans;
	return 0;
}

```

---

## 作者：ZettaByte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF990C)

### 解题思路

首先，我们发现 $s_i$ 中匹配的括号都可以直接消去，对与其它字符串连接没有影响。

消去后，发现 $s_i$ 肯定是形如 $\texttt{))...)((...(}$ 的形式（左括号和右括号的数量都可以为 $0$），因此我们记录 $s_i$ 中剩下的左括号和右括号的数量 $z_i,y_i$。

- 若 $y_i>0$ 且 $z_i>0$，则不会有任何一个字符串与其连接后能匹配，对答案没有贡献；
- 若 $y_i=0$ 且 $z_i=0$，则只有 $y_j=0$ 且 $z_j=0$ 的字符串 $s_j$ 会与其匹配；
- 否则 $y_i=0$ 或 $z_i=0$：
    - 当 $y_i=0$ 时，只有 $y_j=z_i$ 的 $s_j$ 能与 $s_i$ 连接；
    - 当 $z_i=0$ 时，同理。

因此用桶来记录 $y$ 和 $z$ 的数量即可。

### AC code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 300010;
ll n, y[N], z[N], t1[N], t2[N]; string s[N];
void solve()
{
	cin >> n; ll ret = 0;
	for (ll i = 1; i <= n; i++) cin >> s[i];
	for (ll i = 1; i <= n; i++)
	{
		ll sss = 0;
		for (ll j = 0; j < (ll)s[i].size(); j++)
			if (s[i][j] == '(') sss++;
			else if (!sss) y[i]++;
			else sss--;
		z[i] = sss;
	}
	for (ll i = 1; i <= n; i++)
	{
		if (!y[i]) t1[z[i]]++;
		if (!z[i]) t2[y[i]]++;
	}
//	for (ll i = 0; i <= 2; i++) printf("%lld %lld\n", t1[i], t2[i]);
	for (ll i = 1; i <= n; i++)
	{
		if (!y[i] && !z[i]) { ret += t1[0]; continue; }
		if (!y[i]) ret += t2[z[i]];
	} printf("%lld\n", ret);
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ll T = 1;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Tune_ (赞：0)

这题数据大，明显不能暴力枚举。那要怎么做呢？可以根据每个串不配对的括号个数来配对。

那怎么找不配对的个数呢？简单的比较数量是不行的，因为可能有这种序列：
```
)(
```
虽然左右括号数量相等，但并不合法。

所以我们可以考虑用栈来判断。如何判断我就不多说了，详情参考[UVA673 平衡的括号 Parentheses Balance](https://www.luogu.com.cn/problem/UVA673)。

如果一个串左右括号都不比配，就不能用。如：

```
)()(
```
如果一个串只有左括号不匹配，那对答案的贡献就是：不匹配右括号的数量和这个串不匹配左括号的数量相等的串的数量（~~好拗口~~）。如：
```
((
```
如果一个串只有右括号不匹配，那对答案的贡献就是：不匹配左括号的数量和这个串不匹配右括号的数量相等的串的数量。如：
```
))
```
如果一个串所有括号都是匹配的，那对答案的贡献就是：所有括号全匹配的串的数量。如：
```
()
```
思路大概就是这样啦~接下来附上代码：
```
#include<bits/stdc++.h>
using namespace std;
stack<char> st;//一个栈
struct data
{
	int l,r;//l是不匹配左括号数量，r是不匹配右括号数量
	string c;
}s[300005];
long long ans=0;
int n,tl[300005],tr[300005];//tl,tr是存数量的桶，tl是左括号，tr是右括号
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i].c;
		for(int j=0;j<s[i].c.size();j++)
		{
			if(s[i].c[j]=='(')//左括号进栈
				st.push('(');
			else
			{
				if(!st.empty())//出现右括号且有可以配对的左括号
					st.pop();
				else
					s[i].r++;//这个右括号是不匹配的
			}
		}
		while(!st.empty())//还有剩的左括号
		{
			st.pop();//清空栈
			s[i].l++;//这个左括号是不匹配的
		}
		if(s[i].l==0)//进桶（此处合法串在tr[0]和tl[0]都有记录）
			tr[s[i].r]++;
		if(s[i].r==0)
			tl[s[i].l]++;
	}
	for(int i=1;i<=n;i++)//加上
		if(s[i].l==0)
			ans+=tl[s[i].r];//只记一种括号，不然会重复
	cout<<ans;//输出答案
	return 0;//拜了个拜~
}

```
最后，安利一下我的洛谷博客：[一只仓鼠的小窝](https://www.luogu.com.cn/blog/lucy2008/)，dalao们给我点个赞吧~

---

## 作者：sdxjzsq (赞：0)

### 废话
参加了这场CF，算是打的为数不多的CF中最好的一次——做出了两个题（新鲜蒟蒻），这个是第三个，当时比赛的时候没想出来，现在过了好长时间重新去看，发现还是很简单的。  
### 正题
要求是计算括号序列两两匹配合法的方案数。  
经过分析括号序列，我们珂以发现，所有合法的括号序列珂以分为以下3种：  
1. 只能放在左边的括号序列，记为序列A。例如：((
2. 只能放在右边的括号序列，记为序列B。例如：))
3. 两边都珂以放的括号序列，记为序列C。例如：()  

那么我们就珂以知道，如果想要用两个括号序列拼出合法的序列，就必须让左边序列中没有配对的左括号的个数和右边序列中没有配对的右括号的个数相等。  
有点绕口，举个栗子：  
假如左边的序列是((())，这个序列中没有配对的左括号有一个，计算方法是左括号个数-右括号个数(3-2=1)  
那么右边的序列中没有配对的右括号必须只能有一个，类似于())。  
这样他们就可以拼出合法序列了，对答案的贡献是`没有配对的左右括号个数相等的序列A的个数*序列B的个数`。  
那两边都珂以放的序列呢？所有的这种序列两两之间都珂以配对。所以对答案的贡献是`序列C个数的平方`。  
然后我们的目标就很明确了，只要把所有的括号序列在读入的时候都处理一下，去除不合法序列，把每个序列分类，并且求出他没有配对的左括号或者右括号的个数，最后计算贡献即可。  
这里我用l[i]数组记录没有配对的左括号数量为i的序列A的个数，用r[i]数组记录没有配对的右括号数量为i的序列B的个数，把序列C的个数记录到l[0]里。  
最后答案就是$l[0]^2+\sum\limits _{i=1}^nl[i]*r[i],n=min(maxl,maxr)$,其中maxl和maxr分别为l[i]和r[i]中最后一个不为0的元素的下标，因为之后相乘的结果都是0。  
那么怎么判断括号序列属于哪一种呢？  
经过观察，我们发现，如果一个序列在某个位置，使得前面的右括号个数>左括号个数，记max为所有这种位置中前面的右括号个数-左括号个数的最大值，那么如果满足$max=右括号个数-左括号个数$这个括号序列一定是序列B，r[max]++记录下来，如果不满足，那么这个序列就是不合法序列。  
如果不存在上述位置，那么括号一定是序列A或C，直接l[右括号个数-左括号个数]++记录下来即可。  
### code
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3*1e5+1;
int n,rmax=0,lmax=0;
long long ans=0,l[maxn],r[maxn];
char s[maxn];
int main()
{
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    scanf("%d",&n);
    for(register int i=1;i<=n;i++)
    {
        scanf("%s",s);
        int len=strlen(s);
        int ll=0,rr=0,tag=0,maxr=0;
        //ll为左括号个数，rr为右括号个数
        //tag用来记录是否为序列B，maxr为前面说的max
        for(register int j=0;j<len;j++)
        {
            if(s[j]=='(')ll++;
            else 
            {
                rr++;
                if(rr>ll)tag=1,maxr=max(maxr,rr-ll);
            }
        }
        if(tag)
        {
            if(ll==rr-maxr)
            {
                r[rr-ll]++;
                if(rr-ll>rmax)rmax=rr-ll;
            }
        }
        else
        {
            l[ll-rr]++;
            if(ll-rr>lmax)lmax=ll-rr;
        }
    }
    lmax=min(lmax,rmax);//这个就是去求n啦~
    for(register int i=1;i<=lmax;i++)
        ans+=l[i]*r[i];
    ans+=l[0]*l[0];
    printf("%lld",ans);
    return 0;
}
```
### 后记
敲题解真是件费时间的事啊...

---

