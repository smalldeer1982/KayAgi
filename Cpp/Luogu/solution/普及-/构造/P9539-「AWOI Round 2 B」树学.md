# 「AWOI Round 2 B」树学

## 题目背景

HR 刚做完一个简单而又靓丽的题目，它想来试试这道题，可是它太蒻了，不会做，您能帮帮它吗？

## 题目描述

构造一个长度为 $n$ 的小写字母串，要求和给定的长度为 $n$ 的小写字母串 $s$ 的相似度在 $[l,r]$ 范围内。

定义两个长度都为 $n$ 的字符串 $a,b$ 的相似度为 $\sum^{n}_{i=1}[a_i=b_i]$。

您需要使构造出的字符串的字典序尽量小。

## 说明/提示

**【数据规模】**


**本题使用捆绑测试。**

| 子任务编号 | $n\leqslant$ | 特殊性质 | 分值 |
| -----------: | -----------: | -----------: | -----------: |
| $1$ | $100$ | 无 | $20$ |
| $2$ | $10^6$ | A | $10$ |
| $3$ | $10^6$ | B | $10$ |
| $4$ | $10^6$ | 无 | $60$ |

特殊性质 A：$l=r=n$ 或 $l=0,r=n$。

特殊性质 B：$s$ 的每一位都为 `a` 或都不为 `a`。

对于 $100\%$ 的数据，$1 \leqslant n \leqslant 10^6$，$0 \leqslant l \leqslant r \leqslant n$，$s$ 的长度为 $n$。

**【工作人员】**
| $\text{Idea}$ | $\text{Data}$ | $\text{Check}$ | $\text{Solution}$ |
| :----------: | :----------: | :----------: | :----------: | 
| [玄学OIER荷蒻](/user/671294) | [QwQ666\_666](/user/677609) & [玄学OIER荷蒻](/user/671294) | [QwQ666\_666](/user/677609)| [玄学OIER荷蒻](/user/671294) |

## 样例 #1

### 输入

```
3 1 2
aab```

### 输出

```
aaa```

## 样例 #2

### 输入

```
4 4 4
awoi
```

### 输出

```
awoi```

# 题解

## 作者：zct_sky (赞：13)

### Description
-----
给定一个长度为 $n$ 的字符串，使其将 $x$ 位修改后的字符串字典序最小（$n-x \in [l,r]$，即 $x \in [n-r,n-l]$）。
### Solution
-----
考虑贪心。

先将该字符串非 `a` 字符替换成 `a`，优先从前往后换，若换的个数 $= n-l$ 时，退出循环。

记原字符串所有非 `a` 字符数为 $m$，若 $m<n-r$，则将**原**字符串中 $n-r-m$ 个 `a` 字符再替换为 `b`（若修改非 `a` 字符为 `b`，则有效修改数不会增加），优先从后往前换。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;
}
int n,l,r; 
string s;
bool fuck[1000007];
int main(){
	n=read();l=read();r=read();
	l=n-l;r=n-r;
	cin>>s;
	int flag=0;
	for(int i=0;i<n;i++){
	    if(flag==l)break;
		if(s[i]!='a')s[i]='a',flag++;
		else fuck[i]=1;
	}
	if(flag<r){
		for(int i=n-1;i>=0;i--){
			if(fuck[i])s[i]='b',flag++;
			if(flag==r)break;
		}
	}
	cout<<s;
	return 0;
}
```

---

## 作者：玄学OIER荷蒻 (赞：12)

考虑贪心，我们肯定是都想选 `a` 的。

我们给打算选和原本字符串相同的位置的地方打标记。

从左到右扫一遍，`a` 的位置都打，除非现在的标记数已经超过 $r$ 了，直接退出不打标记了。

如果扫完了以后标记数还不到 $l$ 个，那直接从后往前扫，只要没被标记就标记，直到标记到 $l$ 个。

输出部分：如果有标记就输出原本字符串的地方，否则：如果原本的位置那里不是 `a` 就输出 `b`，否则输出 `a`。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
bool c[1000010];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,l,r;
    cin>>n>>l>>r;
    string s;
    cin>>s;
    int cnt=0;
    for (int i=0;i<n;i++){
        if (s[i]=='a'){
            cnt++;
            c[i]=1;
            if (cnt==r) break;
        }
    }
    for (int i=n-1;i>=0;i--){
        if (cnt>=l) break;
        if (c[i]) continue;
        c[i]=1;
        cnt++;
    }
    for (int i=0;i<n;i++){
        if (s[i]=='a' && c[i]==0) cout<<'b';
        else if (c[i]==0) cout<<'a';
        else cout<<s[i];
    }
    return 0;
}
```


---

## 作者：zxh923 (赞：6)

# P9539 「AWOI Round 2 B」树学 题解

### 思路

题目中要求字典序最小，我们便可以显而易见考虑到尽可能多输出 $\texttt a$ 这个字符，并且尽可能输出在前面。

所以我们便可以从头开始，如果我们输出的 $\texttt a$ 正好与这一位相同，计数器保持原状；如果不相同则增加 $1$，当达到题目限制时，开始输出原字符串的内容。

一开始我就是这样想的，根本没有考虑题目中的上界是干什么的。

然后就是悲惨的**满江红**。

可是如果输入的字符串是 $\texttt {aaa}$ 且上下界都是 $1$ 呢？

现在我们就发现了上界的作用，它避免了我们在这种极端情况时全输出 $\texttt a$。

所以如果发现这种情况，相似度要超了，我们在后面输出 $\texttt b$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l,r,need,cnt,cntt;
char s[1000005];//大数组开全局
int main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	need=n-l;//最小相似度
	for(int i=1;i<=n;i++){
		if(s[i]=='a'&&cntt<r){
			cntt++;
			cout<<"a";//统计相似度是否会超
		}
		else if(s[i]=='a'&&cntt>=r){
			cout<<"b";//如果超了，输出b
		}
		else if(s[i]!='a'&&cnt<need){
			cnt++;//如果这一位不是a但还能继续输出a
			cout<<"a";//仍输出a
		}
		else cout<<s[i];//否则输出源字符串内容
	}
	return 0;
}
```


---

## 作者：fls233666 (赞：3)

我们还是采用贪心的策略。具体策略如下：

1. 先构造一个长度为 $n$ 全是 $\texttt{a}$ 的字符串；
2. 与输入的字符串比较，把当前的相似度记为 $\texttt{cnt}$；
3. 判断当前相似度是否在区间 $[l,r]$ 中，如果在，直接输出，否则分类讨论：
- $cnt<l$，说明相似度不够。从末尾往前扫，找到两个串不相同的字符，把它改成相同的，同时更新 $cnt$ 直到 $cnt=l$，此时输出答案。
- $cnt>r$，说明相似度太高。同样从末尾往前扫，找到两个串相同的字符，把它改成不相同的，同时更新 $cnt$ 直到 $cnt=r$。因为之前构造的是全 $\texttt{a}$ 字符串，为了保证字典序最小，把 $\texttt{a}$ 改成 $\texttt{b}$ 是最合适的。

可能还会有人问：为什么要从末尾往前扫？因为我们要保证最后构造出来的串字典序最小，那么从最后一位开始修改，对字典序的影响显然更小，最终保证了答案的字典序最小。

以上就是本题的思路讲解，下面放上代码。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#define ll long long
using namespace std;

const int mxn = 1e6+6;

int n,l,r,cnt;
string ins;
char ans[mxn];

int main(){
    cin>>n>>l>>r>>ins;
    
    for(int i=0;i<n;i++){
        ans[i]='a';
        if(ans[i]==ins[i])
            cnt++;
    }  //初步构造全 a 字符串并统计相似度

    if(cnt<l){
        for(int i=n-1;i>=0;i--){
            if(ans[i]!=ins[i]){
                ans[i]=ins[i];
                cnt++;
                if(cnt==l)
                    break;
            }
        }
    }
    if(cnt>r){
        for(int i=n-1;i>=0;i--){
            if(ans[i]==ins[i]){
                ans[i]++;
                cnt--;
                if(cnt==r)
                    break;
            }
        }
    }  //对应上述思路中的两种情况进行修改和相似度的更新
    
    for(int i=0;i<n;i++)
        putchar(ans[i]);  //输出答案
    return 0;
}
```


---

## 作者：Special_Tony (赞：3)

[题目传送门](/problem/P9539)
# 思路
这题我们有几种操作：
1. 从前往后，如果 $s_i\ne \text a$（其中 $\text a$ 是小写字母 $\text a$，下同），则将其改为 $a$，这个操作的次数要尽可能多；
1. 如果相似度还是太高了，那从后往前，将**原先**就是 $\text a$ 的字母改成 $\text b$，这个操作的次数要尽可能少。

# 代码
```cpp
# include <bits/stdc++.h> //万能头
using namespace std;
int n, l, r, now;
string a, b;
int main () {
	cin >> n >> l >> r >> a;
	l = n - l, r = n - r, swap (l, r);
	b = a; //备份
	for (int i = 0; i < n && now < r; ++ i)
		if (a[i] > 'a')
			b[i] = 'a', ++ now;
	if (now >= l) {
		cout << b;
		return 0;
	}
	for (int i = n - 1; ~ i && now < l; -- i)
		if (a[i] < 'b')
			b[i] = 'b', ++ now;
	cout << b;
	return 0;
}
```

---

## 作者：lrx___ (赞：2)

**思路**

为了使字典序最小，应该尽可能多地选 `a`。

我们用变量 $s$ 记录字符串中 `a` 的数量。先循环一遍，遇到字符 `a`，标记为不用改。最多标记 $r$ 个。

如果循环结束后 $s<l$，就需要再多标记 $l-s$ 个。因为字典序是从前往后看的，所以我们从后往前循环，如果该字符不是 `a`（如果是 `a` 并且 $s<l$，那就一定是标记过了），就标记为不用改。

最后将没标记过的字符中 `a` 改为 `b`，其他的改为 `a`。最后输出即可。

**代码**

```cpp
#include<cstdio>
const int N=1e6+5;
char a[N];
bool b[N];
/* a为原字符串，b为标记的数组 */
int main(){
	int n,l,r,i,s=0;
	/* s记录字符串中'a'的数量 */
	scanf("%d%d%d%s",&n,&l,&r,a);
	for(i=0;i<n;i++){
		if(a[i]=='a'&&s<r){
			/* 如果该字符为'a'且记录的数量小于r，就标记不用改 */
			b[i]=1;
			s++;
		}
	}
	if(s<l){
		/* 如果标记过少 */
		for(i=n-1;s<l;i--){
			if(a[i]^'a'){
				/* 如果该字符不是'a'，就标记为不用改 */
				b[i]=1;
				s++;
			}
		}
	}
	for(i=0;i<n;i++){
		if(!b[i]){
			a[i]=(a[i]=='a'?'b':'a');
			/* 最后将没标记过的字符中'a'改为'b'，其它的改为'a' */
		}
	}
	printf("%s",a);
	return 0;
}
```

---

## 作者：KidzzZip (赞：2)

## 题目大意
构造一个字符串 $s$，使得其**相似度**在 $[l,r]$ 之间，并且使得字符串 $s$ 字典序最小。

**相似度**:定义两个长度都为 $n$ 的字符串 $a,b$ 的相似度为 $\sum^{n}_{i=1}[a_i=b_i]$。


## 题目思路
题意可知是一个普通的贪心题目，对于这个题目，我们先分类讨论。

我们定义 $xxd$ 为相似度，$len$ 表示字符串长度。

当 $len=l$ 时，直接输出原字符串 $s$。

接着我们一个循环:

1. 当 $xxd<l$ ， $len-i+1>l-xxd$ 时，意思是相似度还没有进入区间并且 $s$ 字符串剩下的长度还够用。那么当 $s[i]=a$ 时，相似度 $+1$，输出 $s[i]$，否则直接输出 $a$。
2. 当 $xxd<l$ ， $len-i+1=l-xxd$ 时，意思是剩下的长度等于目前的相似度，那么直接输出 $s[i]$。
3. 当 $xxd≥l$ ， $xxd<r$时，意思是相似度处于区间内并且还不等于 $r$ 时。那么当 $s[i]=a$ 时，相似度 $+1$，输出 $s[i]$，否则直接输出 $a$。
4. 当 $xxd=r$ 时，如果 $s[i]=a$ 输出 $b$，否则输出 $a$。

这样我们就通过这个题目了！

## 代码
```cpp
#include <bits/stdc++.h>
#define N 10000001

using namespace std;
char s[N];
int xxd=0,len;
int main() {
	
	int n,l,r;
	scanf("%d%d%d",&n,&l,&r);
	
	scanf("%s",s+1);
	
	len=n;
	
	if(len==l) {
		printf("%s",s+1);
		return 0;
	}
	
	for(int i=1;i<=n;i++) {		
		if(xxd<l&&len-i+1>l-xxd) {
			if(s[i]=='a') {
				printf("%c",s[i]);
				xxd++;
			}
			else {
				printf("a");
			}
		}
		else if(xxd<l&&len-i+1==l-xxd) {
			printf("%c",s[i]);
			xxd++;
		}
		else if(xxd>=l&&xxd<r) {
			if(s[i]=='a') printf("a"),xxd++;
			else printf("a");
		}
		else if(xxd==r) {
			if(s[i]=='a') printf("b");
			else printf("a");
		}
	}
	
	return 0;
}
```


---

## 作者：zly2009 (赞：2)

部分分好骗，这里不列举了。

操作策略如下：

由于求字典序最小，所以越往前的字符需要尽可能的为 `a`。

如果字符的某一位上不为 `a`，我们让它们的相似度减一，并把这一位变成 `a`。如果相似度要比 $l$ 小了，我们再把最近一次的变化给改回来。

但是需要考虑，如果该字符串本身的字典序就已经很小，便会导致全部变成 `a` 后相似度比 $r$ 大，因此我们要从后开始，把 `a` 依次变为 `b`。

需要注意的是，如果当前字符原来不是 `a`，则我们可以把这一项跳过，最终输出字符串即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool a[1000001];
signed main()
{
	int n,l,r;
	cin>>n>>l>>r;
	string st;
	cin>>st;
	string s=st;
	int c=n;
	int id=0;
	for(int i=0;i<n;i++){
		if(st[i]!='a')c--,s[i]='a',id=i,a[i]=1;
		if(c<l){
			s[id]=st[id];
			a[i]=0;
			break;
		}
	}
	int t=n-1;
	while(c>r){
		if(!a[t])c--,s[t]='b';
		t--;
	}
	cout<<s;
}
```

---

## 作者：Tiago (赞：2)

## Solution

题目要求字典序最小，所以一定要尽可能多的 $a$，而且要尽可能靠前。

所以我们只需修改不是 $a$ 的位置为 $a$ 即可。

但若 $a$ 的个数比 $r$ 大，我们就需要将多余的 $a$ 手动改为 $b$ 并在接下来的修改中保持不变，所以定义一个 $vis_i$ 表示是否一定不能修改。

注意这里要从后往前考虑，而修改要从前往后考虑。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)

const int N=1e6+4;
int n,l,r;
bool g[N];
string st;
int main()
{
	IOS;
	cin>>n>>l>>r;
	cin>>st;
	int anum=0;
	For(i,0,n-1)if(st[i]=='a')anum++;
	if(anum>r)
	{
		l=r;
		FOR(i,n-1,0)
		{
			if(anum==r)break;
			if(st[i]=='a')g[i]=1,st[i]='b',anum--;
		}
	}
	int mnum=n-l,now=0;
	For(i,0,n-1)
		if(g[i]==0)
		{
			if(now==mnum)break;
			if(st[i]!='a')st[i]='a',now++;
		}
	cout<<st;

	return 0;
}
```


---

## 作者：kkxacj (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9539)

#### 思路

由于要使构造出的字符串的字典序尽量小，所以前面尽可能全为 `a`，但由于题目要求，所以我们如果之前有 $o$ 个位置相同了，那么要预留出至少 $l - o$ 个位置与给出的字符相同，如果 $o \ge l$，则不需要预留，如果前面有些为 `a` 的，则能为 `a` 就为 `a`，即只要没有更改超过 $r$ 次就可以，否则则选与当前字符不一样且字典序最小的字符，模拟即可。

**code**

```
#include<bits/stdc++.h>
using namespace std;
int n,l,r,o;//o为一共有几个相等
string s,s1;
int main()
{
	cin >> n >> l >> r >> s;
	for(int i = 0;i < min(s.size(),s.size() - l + o);i++)//至少要有l个相同的，提前预留出来
	{
		for(int j = 0;j < 26;j++)
		{
			if((char)(j + 'a') != s[i]) //选一个字典序最小的
			{
				cout << (char)(j + 'a');
				break;
			}
			else if(o < r)//最多有r个相同的
			{
				cout << s[i];
				o++;
				break;
			}
		}
	}
	for(int i = min(s.size(),s.size() - l + o);i < s.size();i++) cout << s[i];//至少要有l个相同的
	return 0;
}


```


---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

给定一个字符串，求满足 $l \le \sum\limits_{i = 1}^{n}[a_i = b_i] \le r$ 的字典序最小的字符串。

### 题目分析

要求字典序最小，肯定 $a$ 的字典序最小，于是目标字符串前面的字母尽可能都是 $a$。

在这之上考虑两种情况，其余情况该为填 $a$ 即可：

1. 如这一位填 $a$ 则会使这个字符串的相似度小于 $l$。这种情况应该将这一位及其后都填为原字符，否则不满足条件。判断方式为 $x + n - i = l$，$x$ 为现有相似度，$i$ 为当前位。

2. 如这一位原为 $a$，且现有相似度已为 $r$，如果这一位再填 $a$ 则相似度不满足条件，为使字典序最小，这一位应填 $b$。

总的来讲就是贪心，时间复杂度 $\mathcal O(n)$。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <stack>
#include <map>
using namespace std;
int n, l, r, x;
string s;
signed main()
{
	scanf("%d %d %d", &n, &l, &r);
	cin >> s;
	for(int i = 0;i < n;i++)
	{
		if(x + n - i == l)
		{
			cout << s[i];
			x++;
		}
		else if(x == r)
		{
			if(s[i] == 'a')
				printf("b");
			else
				printf("a");
		}
		else
		{
			printf("a");
			if(s[i] == 'a')
				x++;
		}
	}
	return 0;
}
```

---

## 作者：zwyyy (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/P9539)

~~这道题我赛事脑抽调用了 $10^{12}$ 次 `strlen` 导致痛失 $80$ 分，所以我痛定思痛，觉得写个题解。~~

## 思路
要使字符串的字典序最小我们不难想到将字符串里的每一个字符都变为 `a`。

并且如果在字符串里的字符都为 `a` 的情况下相似度太高了，我们就需要从后向前遍历，将字符设置为 `b`。

注意，我做到这里的时候由于没有记录调整后的字符所在的位置导致了一个字符从 `b` 变成了 `a` 又变成了 `b` 痛失了分数。

所以我们还需要一个数组记录我们调整了那些字符。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000005];
int a[1000005];
int main(){
	int n, l, r, xs;
	scanf("%d%d%d%s", &n, &l, &r, s);
	xs = n;
	int len = strlen(s);
	for(int i = 0; i < len; ++i){
		if(xs == l)	break;
		if(s[i] != 'a'){
			s[i] = 'a';
			--xs;
			a[i] = 1;
		}
	}
	if(xs > r){
		for(int i = len - 1; i >= 0; --i){
			if(a[i] != 1){
				s[i] = 'b';
				--xs;
			}
			if(xs == r)	break;
		}
	}
	for(int i = 0; i < len; ++i){
		printf("%c", s[i]);
	}
	return 0;
}
```

[AC](https://www.luogu.com.cn/record/121063929)

---

