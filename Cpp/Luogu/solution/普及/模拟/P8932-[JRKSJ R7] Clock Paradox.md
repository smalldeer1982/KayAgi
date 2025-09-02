# [JRKSJ R7] Clock Paradox

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/47sjcgd5.png)

一分钟后的出题人阻止了这个时刻的出题人写一个有趣的题目背景。

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）

## 题目描述

给你一个字符串 $S$，设 $S=\overline{s_1s_2\dots s_n}$。

有一个字符串 $T$，初始时 $T=S$，你可以进行若干次操作，每次操作可以选取 $S$ 一个子串并插入到 $T$ 的任意位置。

你希望经过若干次操作后，$T=\overline{s_1s_1s_2s_2\dots s_ns_n}$，定义 $f(S)$ 为满足此条件所需的最少的操作次数。

此外，字符串 $S$ 还会发生一些改变。具体地，有 $q$ 次修改操作，每次修改操作会给出 $p$ 和 $\texttt{c}$，表示令 $s_p\gets \texttt{c}$。$\texttt{c}$ 表示任意一个小写字母，而并非 ASCII 为 $99$ 的字符。

你需要在最开始和每次修改后求出 $f(S)$ 的值。

## 说明/提示

Idea：cyffff，Solution：cyffff，Code：cyffff，Data：cyffff

**Clock Paradox - WyvernP (Insane12.6)**

**本题输入输出文件较大，请使用恰当的输入输出方式。**  

### 提示

称字符串 $A$ 是字符串 $S$ 的子串当且仅当存在 $1\le l\le r\le |S|$ 使得 $A=\overline{s_ls_{l+1}\dots s_{r}}$。

### 样例解释
所有修改前，$f(S)$ 的计算方法如下：

初始时，$S=T=\texttt{aabc}$。

第一次操作，选取 $S$ 的子串 $\texttt{aa}$，插入到 $T$ 的最前端，操作后 $T=\texttt{aaaabc}$。

第二次操作，选取 $S$ 的子串 $\texttt{bc}$，插入到 $T$ 的第 $5$ 个字符后，操作后 $T=\texttt{aaaabbcc}$，符合要求。

经过一次修改、两次修改后的 $S$ 分别等于 $\texttt{abbc}$ 和 $\texttt{abbb}$，这两次修改后 $f(S)$ 分别是 $2$ 和 $1$。
### 数据规模

本题采用捆绑测试。
| $\text{Subtask}$ | $\vert S\vert\le$ | $q\le$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $0$ | $10$ |
| $2$ | $10^4$ | $10^4$ | $20$ |
| $3$ | $5\times10^5$ | $0$ | $20$ |
| $4$ | $5\times10^5$ | $5\times 10^5$ | $20$ |
| $5$ | $3\times10^6$ | $3\times 10^6$ | $30$ |

对于 $100\%$ 的数据，$1\le|S|\le3\times10^6$，$0\le q\le 3\times10^6$，保证 $S$ 仅由小写字母构成，保证 $\texttt{c}$ 为单个小写字母。

## 样例 #1

### 输入

```
2
aabc
2 b
4 b```

### 输出

```
2
2
1```

# 题解

## 作者：AKPC (赞：8)

在正解前先考虑暴力。

我们不难发现，可以将字符串分为每个字符都相等的一些子串。先要算出子串的个数。从下标为 $1$ 的开始，枚举每个字符，如果后一个可以写出如下函数：

```cpp
int query(){
	int ans=0;
	for (int i=1;i<(int)s.length();i++) if (s[i]!=s[i-1]) ans++;
	return ans;    //子串个数是ans+1
}
```

而我们可以在相邻子串的中间再插入这两个子串。如此反复下去可以达到要求。不难发现，答案就是 $\lceil \dfrac{ans+1}{2} \rceil$。

暴力代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string s;
int query(){
	char ch=s[0];
	int ans=0;
	for (int i=1;i<(int)s.length();i++) if (s[i]!=ch) ans++,ch=s[i];
	return ans%2==1?(ans+1)/2:(ans+2)/2;    //等价于return ceil(ans+1);
}
int q,x;
char ch;
signed main(){
	cin>>q>>s;
	cout<<query()<<endl;
	while (q--){
		cin>>x>>ch;
		s[x-1]=ch;
		cout<<query()<<endl;
	}
	return 0;
}
```

但是这样的时间复杂度并不能通过本题。我们发现很多次枚举都重复了，没用处。其实我们只要对修改的部分进行枚举即可。

正解如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int query(int l,int r){
	int ans=0;
	for (int i=l;i<=r;i++) if (s[i]!=s[i-1]) ans++;
	return ans;
}
int n,x,ans;
char ch;
int main(){
    cin>>n>>s;
	ans=query(1,(int)s.length()-1);
    ans%2==1?cout<<(ans+1)/2<<endl:cout<<(ans+2)/2<<endl;    //等价于cout<<ceil(ans+1)<<endl;
	while (n--){
		cin>>x>>ch;x--;
		ans-=query(x,x+1);
		s[x]=ch;
		ans+=query(x,x+1);
		ans%2==1?cout<<(ans+1)/2<<endl:cout<<(ans+2)/2<<endl;    //等价于cout<<ceil(ans+1)<<endl;
	}
    return 0;
}
```

---

## 作者：EdenSky (赞：8)

# [P8932 Clock Paradox](https://www.luogu.com.cn/problem/P8932)
- [更好的阅读体验](https://www.cnblogs.com/wanguan/p/17033529.html)

## 正文

**最坏时间复杂度：$\mathcal{O}(|S|+q)$**

找规律的题。

我们先来研究三组数据：

- `abcd`，答案是 2；

- `aa`，答案是 1；

- `ccffab`，答案是 2。

以下称将一个子串按题意每个字符双倍的操作为**完成**。

第一组数据，我们把子串 `ab`、`cd` 插入原字符串即可得到 $T$，由此我们可以得知：**每两个相邻不同字母可以一次完成**。

第二组数据，我们把子串 `aa` 插入原字符串末即可得到 $T$，由此，我们得知：**多个连续相同字母可以一次完成**。

第三组数据是第一组、第二组数据的综合，我们截取子串 `ccff`、`ab` 即可，为了表达清楚，在这里先做一个定义：单个最长的由相同字母组成的子串称为一**块**（第三组数据的块有：`cc`、`ff`、`a`、`b`），然后我们就可以清晰地说明我们的发现：**每两个块（或单个块）可以一次完成**。第三组数据中有 4 个块，所以最快只要 $4\div 2=2$ 次。

由上，我们设每个 $S$ 由 $m$ 个块组成，那么答案为 $\left \lfloor m \div 2\right \rfloor + m\bmod 2$。

---

那静态问题我们解决了，剩下的 $q$ 次修改怎么办呢？

其实很好办的，比如我们将 `aacd` 的第 2 个字符修改成 `c`，即将原字符串变成 `accd`，我们可以研究一下这个字符串的块的变化：

我们设 $a$ 为原始字符串的块数，原始字符串有 3 个块（$a\leftarrow 3$），修改后我们可以发现，第二个字符和它左边的字符不再构成同一个块，我们可以 $a\leftarrow a-1$，即 C++ 中的 `a--`。我们继续分析，第二个字符改成了 `c`，和它右边的字符组成了一个块，我们可以 $a\leftarrow a+1$，或者说 `a++`。

设 $x$ 为一个字符，$S=\overline{x_1x_2x_3}$。假设我们要修改 $x_2$，我们可以总结出：**若原来的 $x_2$ 和左边的字符（$x_1$）构成块，那么 $a\leftarrow a-1$，右边的字符（$x_3$）同理。然后，若修改后的 $x_2$ 和左边的字符构成块，那么 $a\leftarrow a+1$，右边也同理**。

这样，每次修改操作我们就可以以 $\mathcal{O}(1)$ 解决，每次输出 $\left \lfloor a \div 2\right \rfloor + m\bmod 2$ 就行。

代码参上：

```cpp
#include<iostream>
#include<string>
using namespace std;
int q,a,cnt;
char c;
string s;
int main(){
	ios::sync_with_stdio(false),
	cin.tie(nullptr);
	cin>>q>>s;
	int k=0,d=s.size();
	s+="#";//方便后续操作，且能防止越界
	while(k<d){//指针法，k为指针，判断一个块，cnt记录s有多少块
		while(s[k+1]==s[k])	k++;
		k++,cnt++;
	}
	cout<<cnt/2+cnt%2<<'\n';
	s="#"+s;//方便后续操作，且能防止越界
	while(q--){//判断相邻的字符是否构成块且更改cnt（当前字符串块数）
		cin>>a>>c;
		if(s[a]==s[a-1])	cnt++;
		if(s[a]==s[a+1])	cnt++;
		s[a]=c;
		if(s[a]==s[a-1])	cnt--;
		if(s[a]==s[a+1])	cnt--;
		cout<<cnt/2+cnt%2<<'\n';
	}
}
```

[完结！！](https://www.luogu.com.cn/record/98960414)

---

## 作者：cyffff (赞：7)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8932)
## 题意
给你一个字符串 $S$，设 $S=\overline{s_1s_2\dots s_n}$。

有一个字符串 $T$，初始时 $T=S$，你可以进行若干次操作，每次操作可以选取 $S$ 一个子串并插入到 $T$ 的任意位置。

你希望经过若干次操作后，$T=\overline{s_1s_1s_2s_2\dots s_ns_n}$，定义 $f(S)$ 为满足此条件所需的最少的操作次数。

此外，字符串 $S$ 还会发生一些改变。具体地，有 $q$ 次修改操作，每次修改操作会给出 $p$ 和 $\texttt{c}$，表示令 $s_p\gets \texttt{c}$。

你需要在最开始和每次修改后求出 $f(S)$ 的值。

$|S|,q\le3\times10^6$。

## 思路
设 $S$ 的颜色段数为 $x$，一眼看上去，我们可以看出 $f(S)=\lceil\dfrac{x}{2}\rceil$，考虑证明，使用数学归纳法。

对于长度为 $1$ 的字符串，其显然成立。

向 $S$ 后面加入一个字符 $c$，令其为第 $i$ 位。

若 $c$ 等于 $S$ 的最后一个字符，则将进行的最靠右的操作后再加上一个 $c$ 即可。

如 $\texttt{abbbab}$ 最靠右的操作为选取 $\texttt{ab}$ 插入到 $\texttt{a\_b}$ 之间。则 $\texttt{abbbabb}$ 最靠右的操作为选取 $\texttt{abb}$ 插入到 $\texttt{a\_bb}$ 之间。

此类情况答案不变。

否则，若 $S$ 的最靠右的操作只含一种字符，则将进行的最靠右的操作后再加上一个 $c$ 并置于字符串末尾即可。

如 $\texttt{abccc}$ 最靠右的操作为选取 $\texttt{ccc}$ 添加到 $\texttt{ab\_ccc}$ 之间。则 $\texttt{abcccd}$ 最靠右的操作为选取 $\texttt{cccd}$ 插入到 $\texttt{ccc\_d}$ 之间。

此类情况答案不变。

否则，只能选取字符 $c$ 并插入到字符串末尾作为最新的最右端操作。

如 $\texttt{abcd}$ 最靠右的操作为选取 $\texttt{cd}$ 添加到 $\texttt{c\_d}$ 之间。则 $\texttt{abcde}$ 最靠右的操作为选取 $\texttt{e}$ 插入到 $\texttt{e}$ 后面。

如果不这样操作，则 $c$ 被加到之前的操作中，则 $T$ 的最后两个字符为 $S_{i-1}S_i$，不合题意。

此类情况答案加一。

其操作的实质是选取相邻的两个颜色段并将其插入到两段的交点间。

接下来，问题变成了单点修改，全局颜色段数。颜色段数转化为 $S_i\ne S_{i+1}$ 的位置 $i$ 的数量。

考虑修改一个位置，分类讨论新的值与两边的数的关系，旧的值与两边的数的关系，动态维护 $x$ 就好了，可以做到 $O(1)$。

时间复杂度 $O(|S|+q)$。

代码（仅供参考）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=3e6+10;
int n,q,x;
char s[N];
int main(){
	q=read();
	n=readstr(s);
	for(int i=1,j=1;i<=n;i=j+1){
		while(j+1<=n&&s[j+1]==s[i]) j++;
		x++;
	}
	write(x+1>>1),putc('\n');
	while(q--){
		int a=read();
		char c=getc();
		if(s[a-1]==s[a]&&s[a-1]!=c)
			x++;
		if(s[a+1]==s[a]&&s[a+1]!=c)
			x++;
		if(s[a-1]!=s[a]&&s[a-1]==c)
			x--;
		if(s[a+1]!=s[a]&&s[a+1]==c)
			x--;
		s[a]=c;
		write(x+1>>1),putc('\n');
	} 
	flush();
}
```
再见 qwq~

---

## 作者：1qaz234Q (赞：4)

### 题意简述
设 $S=\overline{s_1s_2\dots s_n}$，每次操作选取字符串 $S$ 一个子串，插入到字符串 T 的任意位置，经过若干次操作，使 $T=\overline{s_1s_1s_2s_2\dots s_ns_n}$。字符串 $S$ 有 $q$ 次修改操作，每次修改操作把 $S_p$ 改为 $c$，在开始和每次修改操作后求出最少的操作次数。
### 题目分析
1. 在开始用 for 循环枚举字符串的每个字符，求出连通块的个数。
2. 在相邻的连通块之间插入 $S$ 的子串，能使操作次数最小。设连通块的个数为 $cnt$，那么最少的操作次数为 $\left\lceil\dfrac{cnt}{2}\right\rceil$。
3. 对于每次修改操作，维护连通块个数，算出最少操作次数。
4. 时间复杂度为 $O(q+\left|S\right|)$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 10;
char tmp[N], s[N];
signed main()
{
    int q, cnt = 0;
    scanf("%d%s", &q, tmp);
    int len = strlen(tmp); // 字符串长度
    s[0] = '1';
    for (int i = 0; i < len; ++i)
    {
        s[i + 1] = tmp[i];
    }
    s[len + 1] = '1';
    for (int i = 1; i <= len; ++i)
    {
        if (s[i] != s[i + 1])
        {
            ++cnt;
        }
    }                        // 求出字符串连通块的个数
    int ans = (cnt + 1) / 2; // 求出最少操作次数
    printf("%d\n", ans);
    while (q--)
    {
        int p;
        scanf("%d", &p);
        char tmp2 = getchar(); // 消除回车
        char c = getchar();
        if (c != s[p])
        {
            if (c == s[p - 1] && c == s[p + 1])
            {
                cnt -= 2;
            }
            else if ((c == s[p - 1] && c != s[p + 1] || c != s[p - 1] && c == s[p + 1]) && s[p] != s[p - 1] && s[p] != s[p + 1])
            {
                --cnt;
            }
            else if (s[p] == s[p - 1] && s[p] == s[p + 1])
            {
                cnt += 2;
            }
            else if ((s[p] == s[p - 1] && s[p] != s[p + 1] || s[p] != s[p - 1] && s[p] == s[p + 1]) && c != s[p - 1] && c != s[p + 1])
            {
                ++cnt;
            }
        }                    // 更改字符串连通块个数
        s[p] = c;            // 修改字符串
        ans = (cnt + 1) / 2; // 计算出最少操作次数
        printf("%d", ans);
        putchar('\n');
    }
}
```

---

## 作者：Larryyu (赞：2)

## _Description_

给定一个字符串 $S$，现在需要通过若干次操作，使得 $S$ 中的每个字符在字符串 $T$ 中都出现两次（初始时，$T=S$）。

每次操作可以将 $S$ 中的任一字串插入 $T$ 的任意位置。

求最少操作数。

例：

- $\overline{AABBC}\rightarrow\overline{AAAABBBBCC}$

- $\overline{AGCBC}\rightarrow\overline{AAGGCCBBCC}$

## _Solution_
设原串字符数和字符段数分别为 $x,y$。

题目可以转换为，在每一个字符旁边复制一遍自身（最小操作数为 $x$）。



首先，我们可以将每个字符扩大到每个相同字母连续段（最小操作数为 $y$）。

例：
- $A\underline{A}A\underline{A}A\underline{A}\rightarrow A\underline{AAA}AA$（下划线为插入字串,上划线省去）

可见，相同字母的段可以插入原段中任意位置（此例中原段为 $\overline{AAA}$）。

进而，可以在两个相邻的字符段中插入原段。

例：
- $AA\underline{AA}B\underline{B}\rightarrow AA\underline{AAB}B$

可见，在两个字符段间可以加入原段（此例中原段为 $\overline{AAB}$）。

此时最小操作数为 $\left\lfloor\dfrac{y+1}{2}\right\rfloor$。

例:
- $AAA\underline{AAABB}BBCC\underline{CCD}D$（2次，$y=4$）
- $AA\underline{AAB}BC\underline{CDDD}DDDE\underline{E}$（3次，$y=5$）

求字符段即可。


更新时，只用判断改的字符和原来两边的字符的关系即可。

共6种：

- $AAA\rightarrow A\underline{B}A$（下划线为更改字符，上划线省略，$y=y+2$）
- $ABA\rightarrow A\underline{A}A$（$y=y-2$）
- $ABB\rightarrow A\underline{A}B$（$y=y$）
- $ABB\rightarrow A\underline{C}B$（$y=y+1$）
- $ACB\rightarrow A\underline{A}B$（$y=y-1$）
- $ACB\rightarrow A\underline{D}B$（$y=y$）

## _Code_
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n;
int sum;
int a[3003000];
char s[6000010];
int read(){  //快读
	int x,f=1;
	char ch;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int sz;
int main(){
	n=read();
	scanf("%s",s);
	sz = strlen(s);
	a[0]=0;
	for(int i=0;i<sz;i++){
		a[i+1]=s[i]-'a'+1;
		if(a[i+1]!=a[i]) sum++;  //字符段数
	}
	if(sum%2==0){
			printf("%d\n",sum/2);
		}else printf("%d\n",sum/2+1);
	while(n--){
		int i,x;
		char xx;
		scanf("%d %c",&i,&xx);
		x=xx-'a'+1;
		if(a[i]==a[i-1]&&a[i]==a[i+1]){  //第一种
			if(x!=a[i-1]) sum+=2;
		}else if(a[i-1]==a[i+1]&&a[i]!=a[i-1]){  //第二种
			if(x==a[i-1]) sum-=2;
		}else if(a[i]==a[i-1]||a[i]==a[i+1]){  //第四种
			if(x!=a[i-1]&&x!=a[i+1]) sum+=1; 
		}else if(a[i]!=a[i-1]&&a[i]!=a[i+1]){  //第五种
			if(x==a[i-1]||x==a[i+1]) sum-=1;
		}
		a[i]=x;
		if(sum%2==0){
			printf("%d\n",sum/2);
		}else printf("%d\n",sum/2+1);
	}
	return 0;
}

```
#### _完结撒花~!!_


---

## 作者：McIron233 (赞：1)

本题解中我将连号定义为：一个字符串中相同字符的子串，且子串相邻位置不再存在这个相同字符的子串。

~~赛时其他题真不会，这题开始的一个做法交上去结果假了，$30$ 分。~~

后来猜想这题跟连号个数有关联，于是可以想到：

- 两个连号经过一次操作可以满足要求，只需要将他们组成的字符串插入第一个连号的末尾即可；
- 一个连号经过一次操作即可满足要求，原因显然。

于是答案就是连号个数一半，向上取整即可。

对于修改，只需要对这个修改的位置前后判断一下连号个数就行，时间复杂度 $O(1)$。

初始判断的时间复杂度是线性的，所以整体时间复杂度 $O(|S|+q)$。

[~~码风丑，大佬轻喷。~~](https://www.luogu.com.cn/paste/j1pfyisg)

---

## 作者：hycqwq (赞：0)

别看这是道黄题，其实想清楚了还是很简单的。

## 思路

### 1. 如何算出答案

对于字符串 $S = \overline{s_1 s_2 \dots s_n}, T = S$，想让 $T = \overline{s_1 s_1 s_2 s_2 \dots s_n s_n}$，最简单的方法就是用 $n$ 次操作，这想必大家都能想到。

更进一步，我们发现连续的相同字符可以视作一个整体，只需要一次操作，就好比字符串 $\texttt{aaa}$ 只用一次操作就能解决。

对于这种连续的字符，我们称之为一个“块”。使用这种方法，我们所求的最小操作次数就应该是 $S$ 中“块”的最小个数（即不存在两个连续且字符相同的“块”），我们设其为 $x$。

同时，我们还可以把相邻的两个“块”一起处理，只需要把这两个“块”连接起来，放在中间就可以。如 $\texttt{aaabbccddd}$，我们只需要把 $\texttt{aaabb}$ 插入到最后一个 $\texttt{a}$ 的后面，把 $\texttt{ccddd}$ 插入到最后一个 $\texttt{c}$ 的后面即可。这样，最后的答案就是 $\lceil \dfrac{x}{2} \rceil$。

### 2. 如何维护

由于 $S$ 长度不短，所以每次计算答案时现找答案是行不通的。

我们一开始先遍历一遍，找出 $x$（“块”的最小个数）。然后我们在每次修改时只需要判断一下：

1. 是否和左边部分原来是一个“块”，但是修改后分成了两个“块”？如是，$x + 1$；
2. 是否和右边部分原来是一个“块”，但是修改后分成了两个“块”？如是，$x + 1$；
3. 是否和左边部分原来不是一个“块”，但是修改后合成了新的“块”？如是，$x - 1$；
4. 是否和右边部分原来不是一个“块”，但是修改后合成了新的“块”？如是，$x - 1$。

## 代码

```cpp
#include <cstdio>
#include <cmath>
#include <string>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
#define elif else if

int q;
string s;
char _s[3000005];//scanf读入快一点

int main()
{
    scanf("%d %s", &q, _s);
    s = _s;
    int cnt = 1;
    for (int i = 1; i < s.size(); i++)//先统计一下初始有多少“块”
        if (s[i] != s[i - 1])
            cnt++;
    printf("%d\n", int(ceil(cnt / 2.0)));//一定要记得转int
    int p;
    char c;
    for (int i = 1; i <= q; i++)
    {
        scanf("%d %c", &p, &c);
        p--;//下标不一样，string下标从0开始
        if (p != 0 && s[p] == s[p - 1] && c != s[p - 1])//情况1
            cnt++;
        if (p != s.size() - 1 && s[p] == s[p + 1] && c != s[p + 1])//情况2
            cnt++;
        if (p != 0 && s[p] != s[p - 1] && c == s[p - 1])//情况3
            cnt--;
        if (p != s.size() - 1 && s[p] != s[p + 1] && c == s[p + 1])//情况4
            cnt--;
        //一定要注意判断边界
        s[p] = c;
        printf("%d\n", int(ceil(cnt / 2.0)));
    }
    return 0;
}
```

提交记录：赛时 [R98904527](https://www.luogu.com.cn/record/98904527) | 赛后 [R99301657](https://www.luogu.com.cn/record/99301657)。

---

## 作者：_shy (赞：0)

## [P8932 [JRKSJ R7] Clock Paradox](https://www.luogu.com.cn/problem/P8932)
### 思路
1. 把 $S$ 划分为若干串，其中**每一串满足其中的字符相同**，即 $S=s_1s_2\dots s_r$。最朴素的想法是，在 $s_i$ 后面插入 $s_i$，显然不优。但是发现**可以一次性在 $s_i$ 与 $s_{i+1}$ 之间一次性插入 $s_is_{i+1}$**。容易证明，**一次性插入两个以上是不可行的**（可以手写一下）。故最后的答案为 $f(S)=\left[\frac{r+1}{2}\right]$。
2. 进行修改后，则需要更新 $r$。先不考虑边界的特殊情况，考虑一般情形。易得，只用考虑以修改位置为中心以及向左向右各一个单位这三个字符。他们的排列情况只有 $5$ 种，分别是 **ccc，cca，acc，cac，abc**，其中 a，b，c 是不同的字符。再考虑边界。若修改位置在字符串首或末，则只用考虑 ca，cc 两种情况。分类讨论修改字符 $ch$ 是什么就可以了，具体的讨论方法是：$ch$ 与 a（或 b 或c）相等，或全不相等时，$r$ 的改变情况。故最后的答案 $f(S)=\left[\frac{r_1 +1}2{}\right]$。不要忘记更新 $s[p-1]$。
3. 时间复杂度为 $\mathcal O(n + q)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e6 + 100;
char s[maxn], ch;
int q, p, ans;
int main ()
{
	scanf ("%d", &q);
	cin >> s;
	int len = strlen (s);
	char cur = s[0]; ans = 1;
	for (int i = 1; i < len; i++) 
	{
		if (cur == s[i]) continue;
		else ans ++, cur = s[i];
	}
	printf ("%d\n", (ans + 1) / 2);
	int curi = ans;
	while (q --) 
	{
		scanf ("%d %c", &p, &ch), p--;
		if (ch != s[p]) 
		{
			if (p == 0) 
			{
				if (s[0] == s[1]) curi ++;
				else if (s[0] != s[1] && ch == s[1]) curi --;
			} 
			else if (p == len - 1) 
			{
				if (s[len - 1] == s[len - 2]) curi ++;
				else if (s[len - 1] != s[len - 2] && ch == s[len - 2]) curi --;
			}
			else 
			{
				char l = s[p - 1], r = s[p + 1], mid = s[p];
				if (l == r && r == mid) curi += 2;
				else if (l != mid && mid != r && l != r && (ch == l || ch == r)) curi --;
				else if (l == mid && mid != r && ch != r) curi ++;
				else if (l != mid && mid == r && ch != l) curi ++;
				else if (l == r && mid != l && ch == l) curi -= 2; 
			}
		}
		s[p] = ch;
		printf ("%d\n", (curi + 1) / 2);
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

[传送门](https://www.luogu.com.cn/problem/P8932)
***
**分析**

我们定义一个联通子串是指子串包括的所有字符一样。我们会发现任意两个非空联通子串只需要一步便可以完成题目的要求，例如样例中的 aab 是由联通子串 aa 和 b 构成的，只需复制本身，插入到 aa\_b 中间的位置，变成 aaaabb。

现在，我们只需要把联通子串的间隔数算出来，加一得到联通子串的间隔数，除以二再向上取整便可，即设 $tp$ 为联通子串个数，答案便是 $(tp+2)/2$。

但是，如果对接下来的操作都算一次会 TLE，所以我们需要在后面修改时得到更优的算法。分类讨论 $s[n]$ 和 $c$ 与周围的数造成对联通子串的影响即可。

**AC代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);//快读，否则最后一个点TLE 
	int q,n,tp=0;
	char c;
	string s;
	cin>>q;
	cin>>s;
	for(int i=1;i<s.size();i++) if(s[i]!=s[i-1]) tp++;//算出第一次的联通间隔 
	cout<<(tp+2)/2<<endl;
	for(int i=1;i<=q;i++)
	{
		cin>>n>>c;
		n--;
		tp-=(n+1<s.size()&&s[n]!=s[n+1]);//如果s[n+1]不溢出且与s[n+1]不等，令c改变它会造成联通间隔减一 
		tp-=(n-1>=0&&s[n]!=s[n-1]);//如果s[n-1]不溢出且与s[n-1]不等，令c改变它也会造成联通间隔减一 
		tp+=(n+1<s.size()&&c!=s[n+1]);//如果s[n+1]不溢出且c与s[n+1]不等，赋值后造成联通间隔加一 
		tp+=(n-1>=0&&c!=s[n-1]);//如果s[n-1]不溢出且c与s[n-1]不等，赋值后造成联通间隔加一 
		s[n]=c;//赋值 
		cout<<(tp+2)/2<<endl;
	}
	return 0;
}
```


---

## 作者：pxb0801 (赞：0)

### 前言：这是一道很好的字符串~~卡常~~题。

[题目传送门](https://www.luogu.com.cn/problem/P8932)

---------------------
## 1.分析：

首先我们在看完样例后可以很快得到一个结论：如果字符串的颜色段数为 $ans$，那么 $f(S)=\lceil \dfrac{ans}{2}\rceil$。原因很简单：比如字符串 $\texttt{aab}$，我们可以把新的 $\texttt{aab}$ 插入到 $\texttt{aa}$ 与 $\texttt{b}$ 之间。于是输出的第一行就轻松解决。

接下来就是 $q$ 次修改即询问了。我们同样看样例。对于字符串 $\texttt{aabc}$，此时的 $ans=3$。第一次修改将 $S_2$ 修改为 $\texttt{b}$。我们将目光聚焦在 $S_2$。它与 $S_{2-1}$ 相同，与 $S_{2+1}$ 不相同，所以仅看 $S=\overline{S_1S_2S_3}$，颜色段数为 $2$。当把 $S_2$ 修改为 $\texttt{b}$ 时，同理可得颜色段数也为 $2$，所以 $ans$ 值在修改后仍为 $3$。

同理，对于第 $2$ 次修改，如果将 $S_4$ 的后一个位置看为与 $S_4$ 恒不同的一个字符，那么 $S=\overline{S_3S_4S_5}$ 修改前颜色段数为 $3$，修改后颜色段数为 $2$，所以 $ans$ 值变为 $2$。

算出每次的 $ans$ 后，带入公式 $f(S)=\lceil \dfrac{ans}{2}\rceil$ 计算就行啦。

-------------------
## 2.AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,ans;
char s[3000005];
int main(){
	cin>>q;
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]!=s[i-1]) ans++;//计算颜色段数
	}
	cout<<(ans+1)/2<<endl;//修改前的一次输出
	while(q--){
		int x;
		char c[2];
		scanf("%d%s",&x,c);//读单个字符也用字符串，避免getchar的bug
		ans+=(c[0]!=s[x-1])+(c[0]!=s[x+1])-((s[x]!=s[x-1])+(s[x]!=s[x+1]));//计算修改后的ans值
		s[x]=c[0];//原字符串修改
		printf("%d\n",(ans+1)/2);
	}
	return 0;
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/P8932)

先讲一下结论：我自己创了一个数据 `aabcdd`，我们先抽出 `aabc` 来看。我们想把 `aa` 变成 `aaaa` 很简单，只要把一个 `aa` 添加到原本的 `aa` 前面就行了。但是我们都知道，一次只改变一个子串明显比两个来得不划算，所以我们可以去尝试改变 `aab`。我们不难发现，只要把 `aab` 加在 `aa` 的后面，`b` 的前面，就能把原字符串 `aab` 改为 `aaaabb`。但如果想直接改变 `aabc` 是明显不行的，因为你无论如何都得花两步才能全部改变。

所以结论就是：我们把连续的相同字符的子串分成一段，每两端就让答案加一。

这一道题我赛时的第一个思路是初始状态和每一次改变与查询的答案都用一个循环来求解，但这会 TLE，只能拿 $50$ 分。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,ans=0,sum=0;
char s[3000010];
int main()
{
	scanf("%d",&q);
	cin>>s;
	n=strlen(s);
	for(register int i=0;i<n;i++)
		if(s[i]!=s[i-1])
		{
			sum++,sum%=2;
			if(sum==1) ans++;
		}
	printf("%d\n",ans);
	while(q--)
	{
		int x;
		char ch;
		ans=0,sum=0;
		scanf("%d",&x);
		cin>>ch;
		s[x-1]=ch;
		for(register int i=0;i<n;i++)
			if(s[i]!=s[i-1])
			{
				sum++,sum%=2;
				if(sum==1) ans++;
			}
		printf("%d\n",ans);
	}
	return 0;
}
```

想要不 TLE，就得把查询的过程的时间复杂度改为 $O(1)$。

我们可以先用 $O(n)$ 的时间复杂度的查询把初始状态查一遍，得到答案后我们只需要靠着每一次 $s_p$ 改变而直接改变答案就行了。

我们可以去把 $p-1$，$p$，$p+1$ 的不同情况都枚举出来。

先给个枚举的思路，我们可以假设有三个字母 `a`，`b`，`c`。

然后原本那三个字符的情况可以是这样的：`aaa`，`aba`，`aab`，`abb`，`abc`。

注：这里的字母都是虚指的，只代表字母间的关系。

这三个字符当中第二个字符是 $s_p$，将被替换成 $c$，所以我们只要观察如果 $c$ 只等于 $s_{p-1}$，$c$ 只等于 $s_{p+1}$，$c$ 既等于 $s_{p-1}$，又等于 $s_{p+1}$，$c$ 既不等于 $s_{p-1}$ 又不等于 $s_{p+1}$ 会发生什么就行了。

具体的代码我放在下面。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,ans=0,sum=0;
char s[3000010];
int main()
{
	scanf("%d\n",&q);
	cin>>s;
	n=strlen(s);
	for(register int i=0;i<n;i++)
		if(s[i]!=s[i-1])
		{
			sum++;
			if(sum%2==1) ans++;
		}
	printf("%d\n",ans);
	while(q--)
	{
		int x,flag=0;
		char ch;
		scanf("%d\n",&x);
		ch=getchar();
		x--;
		if(s[x]!=s[x-1]&&s[x]!=s[x+1])
		{
			if(ch==s[x-1]&&ch!=s[x+1]) sum--,flag=1;
			else if(ch!=s[x-1]&&ch==s[x+1]) sum--,flag=1;
			else if(ch==s[x-1]&&ch==s[x+1]) ans--,sum-=2;
		}
		if(s[x]==s[x-1]&&s[x]!=s[x+1])
			if(ch!=s[x-1]&&ch!=s[x+1]) sum++,flag=2;
		if(s[x]!=s[x-1]&&s[x]==s[x+1])
			if(ch!=s[x-1]&&ch!=s[x+1]) sum++,flag=2;
		if(s[x]==s[x-1]&&s[x]==s[x+1])
			if(ch!=s[x-1]&&ch!=s[x+1]) ans++,sum+=2;
		if(flag==1&&sum%2==0) ans--;
		if(flag==2&&sum%2==1) ans++;
		s[x]=ch;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Register_flicker (赞：0)

### 思路
要用 $S$ 的子串插入 $T$，使 $T$ 的每个字符复制一遍，可以想到如果每个字符不重复，可以两个字符同时插入，操作数就是 $\lceil |S|\div 2 \rceil$ 。

如果有重复字符可以同时修改，可以先用 $a$ 存储有多少块的重复字符块（比如 `aabc` 里就分成 `aa`、`b`、`c` ， $a=3$ ）。两个块同时插入，操作数为 $\lceil a\div 2 \rceil$ 。

每一次修改需要考虑换的数会不会组成一块或者拆掉一块，需要考虑左边和右边的，考虑几种情况：
+ 如果一边的字符和修改后的字符相同，并且与修改前的字符不同，操作数减去 $1$。
+ 如果一边的字符和修改后的字符不同，并且与修改前的字符相同，操作数加上 $1$。
+ 否则操作数不修改。

字符两边都需要单独考虑一遍，还要注意边界的判断。
### AC代码
```
#include<bits/stdc++.h>
using namespace std;
int q,p,cd,ans;
string s;
char c,ss[3000002],sy,qwq;
int main()
{
	cin>>q>>s;
	cd=s.length();
	ans=0;
	sy=' ';
	for(int i=0;i<cd;i++)
	{
		ss[i+1]=s[i];
		if(s[i]!=sy)
		{
			ans++;
			sy=s[i];
		}
	}
	if(ans%2==0)//写的时候把ceil改了
	{
		cout<<ans/2<<endl;
	}
	else
	{
		cout<<ans/2+1<<endl;
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&p);
		scanf("%c",&c);
		scanf("%c",&c);
		qwq=ss[p];
		ss[p]=c;
		if(ss[p-1]==c&&ss[p-1]!=qwq&&p!=1)
		{
			ans--;
		}
		if(ss[p+1]==c&&ss[p+1]!=qwq&&p!=cd)
		{
			ans--;
		}
		if(ss[p-1]!=c&&ss[p-1]==qwq&&p!=1)
		{
			ans++;
		}
		if(ss[p+1]!=c&&ss[p+1]==qwq&&p!=cd)
		{
			ans++;
		}
		if(ans%2==0)
		{
			printf("%d\n",ans/2);
		}
		else
		{
			printf("%d\n",ans/2+1);
		}
	}
} 
```

寄

---

## 作者：_bruh_ (赞：0)

## 题目大意
给出一个字符串 $ s $ ，求通过复制字符串的子串使这个字符串变为一个 $ \textbf{每个字符} $ 都变成两个的新字符串。
## 解题思路
~~eazy~~ 

### 部分分

很容易能想到，我们可以每一次修改计算一次，理想复杂度
$ \Theta(|s|q) $

明显超时

### 正解？

先看第一次的计算，

容易发现，在本题中字符串的插入方式可以是这样的：
$ _\text{取第一个样例，其中红色字符为插入的字符} $

$ \text{a a b c} \Rightarrow \text{a ab c} \Rightarrow \text{\red{a}aa\red{ab}b\red{c}c} $

也可以是这样的：

$ \text{a a b c} \Rightarrow \text{aab c} \Rightarrow \text{aa\red{aab}b\red{c}c} $

很显然，对于上述方法中，我们可以发现插入 $ \text{aab} $ 这一串子串的步数比插入 $ \text{ab} $ 的步数要少。 $ ( 2 < 3 ) $

那么，我们可以进一步思考，假设字符串为 $ \text{aaabc} $ 时，插入方法又该如何。

明显会是
$ \text{a a a b c} \Rightarrow \text{aaab c} \Rightarrow \text{aaa\red{aaab}b\red{c}c} $

这时可以发现规律了：

**当有连续相同字符时，应将连续字符看为一体，每两个字符凑在一起复制，复制的子串插入到两字符中间**

这下，我们就可以只在开头的时候计算出有多少对字符，在修改时判断是否能与先后并为一体即可。

时间复杂度 $ \Theta (|s|+q) $

## 喜闻乐见代码
码风奇异，求谅解
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
		//祖传火车头
#define ll long long
#define re register
#define rll re ll
inline ll read()
{
	rll x=0,c=0;
	re char a=getchar();
	for(;a<48||a>58;a=getchar())c|=a==45;
	for(;a>47&&a<59;a=getchar())x=(x<<3)+(x<<1)+(a^48);
	return c?-x:x;
}
inline void write(rll x)
{
	if(x<0)putchar(45),x=-x;
	if(x>9)write(x/10);
	putchar(x%10^48);
}
#define R read()
using namespace std;

int main()
{
	rll q=R,n;
	re string s;
	cin>>s;n=s.length();
	for(rll i=1;i<=s.length();++i)if(s[i]==s[i-1])--n;
    			//记录有多少“块”字符
	write((n>>1)+n%2);putchar(10);
    			//操作步数就是  (字符数/2)向上取整
	for(rll kkk=1;kkk<=q;++kkk)
	{
		rll x=R;re char a;cin>>a;									

		if(s[x-1]==s[x-2])++n;
		if(s[x-1]==s[x])++n;
		if(s[x-2]==a)--n;
		if(s[x]==a)--n;
        		//判断是否改变
		write((n>>1)+n%2);putchar(10);
		s[x-1]=a;
        		//注意修改
	}
	return 0;
}
```


---

## 作者：JuRuoOIer (赞：0)

# 题解 P8932 [JRKSJ R7] Clock Paradox

作为我赛时唯一做出来的题（T2 被取模骗了），来篇题解庆祝下。

### Part1 题意

[题面传送门](https://www.luogu.com.cn/problem/P8932)

定义 $f(S)$ 为使字符串 $S=\overline{s_1s_2...s_n}$ 变成 $T=\overline{s_1s_1s_2s_2...s_ns_n}$ 所需的最小操作次数，其中 $T$ 初始时与 $S$ 相同，一次操作可以把 $S$ 中连续的一段插到 $T$ 中。 

给定字符串 $S$ 和 $q$ 次修改，求开始时和每次修改后 $f(S)$ 的值。

### Part2 做法

怎么把 $S$ 中连续的一段 $\overline{s_1s_2...s_k}$ 变成 $T$ 中的 $\overline{s_1s_1s_2s_2...s_ks_k}$ 呢？

- 可以看到，每一项都可以再插一个到这一项的前面或后面，这样就可以出现两个。
- 而连续的相同项则只需要把这一整段再插一个到前面或后面。
- 由于前后都可以插，所以每两段只需要插一次即可。
- 由此，我们发现：**设 $g(S)$ 为 $S$ 中连续相同的最少段数，则把 $S$ 转换成 $T$ 所需要的最少操作次数为 $\lceil \frac{g(S)}{2} \rceil$。**

那思路就很明确了：**只需要找出每一次修改后的 $g(S)$，就可以完成本题。**

但单次求 $g(S)$ 的复杂度是 $\text{O}(|S|)$ 的，总复杂度成了 $\text{O}(|S|q)$，直接 T 飞。所以我们只能在开始的时候求一次 $g(S)$，**后面每次修改直接在原来的基础上用 $\text{O}(1)$ 的复杂度算出新的 $g(S)$**。

这里，我简单地讨论了一下：

- 如果改的字符和原来的字符一样（等于没改），直接过；
- 否则：
    1. 如果这个位置原来的字符与其左边、右边的字符都一样，则 $g(S)$ 增加 $2$（一段变成了三段）；
    2. 如果这个位置原来的字符与其左边、右边的字符都不一样，改之后都一样，则 $g(S)$ 减少 $2$（三段变成了一段）；
    3. 如果这个位置原来的字符与其左边或右边的字符一样，改之后和两边都不一样，则 $g(S)$ 增加 $1$（两段变成了三段）；
    4. 如果这个位置原来的字符与其左边和右边的字符都不一样，改之后和一边是一样的，则 $g(S)$ 减少 $1$（三段变成了两段）；
    5. 其它情况没有变化。

这样，这道题就解决啦！总复杂度 $\text{O}(|S|+q)$。

### Part3 代码

为了让 `cin` 能过，这道题的时限已经放宽到三秒了。

注释已经加好啦！

```cpp
#include<bits/stdc++.h>
/*此处省略一坨快读快输，可以去我主页找，这道题中它跑出了342ms的好成绩*/
#define ll long long
using namespace std;
ll q,p,sum,len;
char ch,s[3000010];
//本来是string，为适配快读用了char数组，len存长度 
int main(){
	cin>>q>>s;
	sum=1;//全部一样也有一段，直接算上 
	len=strlen(s);
	//计算g(S) 
	for(int i=1;i<len;i++){//注意从1开始，否则会RE 
		if(s[i]!=s[i-1]){
			sum++;
		}
	}
	cout<<(sum+1)/2<<endl;//别漏了这个 
	while(q--){
		cin>>p>>ch;
		p--;//我是从0开始的所以p减去1 
		if(s[p]!=ch){//相同等于没改，直接过 
			if(p>0&&p<len-1){//改的位置不在两头（这个判断防RE） 
				//下面的情况根据sum的改变对号入座去上面找即可，这里不再赘述 
				if(s[p-1]==s[p]&&s[p]==s[p+1]){
					sum+=2;
				}
				else if(s[p-1]==s[p]&&ch!=s[p+1]||s[p+1]==s[p]&&ch!=s[p-1]){
					sum++;
				}
				else if(s[p-1]!=s[p]&&s[p]!=s[p+1]){
					if(ch==s[p-1]||ch==s[p+1])sum--;
					if(ch==s[p-1]&&ch==s[p+1])sum--;
				}
			}
			else{//改的位置在两边 
				if(p==0&&s[p]==s[p+1]||p==len-1&&s[p]==s[p-1]){
					sum++;
				}
				if(p==0&&ch==s[p+1]||p==len-1&&ch==s[p-1]){
					sum--;
				}
			}
		}
		s[p]=ch;//别忘了改上去 
		cout<<(sum+1)/2<<endl;//输出 
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：0)

对于一个字符串 $S$，把它分成若干段，相邻的两个字母如果相同，就归为一段，设一共有 $x$ 段。如字符串 $\texttt{aabc}$ 就分为 $3$ 段：$\texttt{aa}$、$\texttt{b}$ 和 $\texttt{c}$。

如果段数为偶数，则第 $1$ 段和第 $2$ 段之间插入第 $1$ 段和第 $2$ 段，第 $3$ 段和第 $4$ 段之间插入第 $3$ 段和第 $4$ 段……最后还剩一段，则在末尾插入最后一段，一共需要 $\dfrac{x+1}{2}$ 次操作。

如果段数为奇数，则没有最后一段，需要 $\dfrac{x}{2}$ 次操作。

那对于每一次询问，怎么快速求出当前的段数呢？我们可以先 $O(n)$ 初始化出段数，对于一次询问：

- 如果原来的字符和它左边的相同，改了之后就不同了，则对答案产生 $1$ 的贡献。

- 如果原来的字符和它右边的相同，改了之后就不同了，则对答案产生 $1$ 的贡献。

- 如果原来的字符和它左边的不同，改了之后就相同了，则对答案产生 $-1$ 的贡献。

- 如果原来的字符和它右边的不同，改了之后就相同了，则对答案产生 $-1$ 的贡献。

一直维护着答案即可，总时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,INF=1e9;
//省略快读快写
int q,len;
string s;
signed main()
{
	q=read(),cin>>s,len=s.size(),s=" "+s;
	int cnt=0;
	for(int i=1;i<=len;i++)
		if(s[i]!=s[i-1])
			cnt++;
	write((cnt+1)>>1,"\n");
	while(q--)
	{
		int x=read();char ch=getchar();
		if(x!=1&&s[x]==s[x-1]&&ch!=s[x-1])
			cnt++;
		if(x!=len&&s[x]==s[x+1]&&ch!=s[x+1])
			cnt++;
		if(x!=1&&s[x]!=s[x-1]&&ch==s[x-1])
			cnt--;
		if(x!=len&&s[x]!=s[x+1]&&ch==s[x+1])
			cnt--;
		s[x]=ch;
		write((cnt+1)>>1,"\n");
	}
}
```

---

## 作者：joyslog (赞：0)

考虑一个例子：

$$\texttt{aabbbccccddeff}$$

把这个字符串按照相同段来两两分组：

$$\texttt{\color{red}{aabbb}\color{blue}{ccccdd}\color{orange}{eff}}$$

这样每一组内有且只有两种字符。

然后对于每一组分别考虑，我们选取这一组的所有字符，插入到这两种字符之间：

$$\texttt{aabbb}\to \texttt{aa aabbb bbb}{}$$

可以证明这种插入方法是最优的。操作次数就是组数。

所以若设字符相同的段数为 $\text{cnt}$，则答案为 $\lceil \frac{\text{cnt}}{2}\rceil$。

然后修改的话我们可以分类讨论看 $\text{cnt}$ 的改变情况，但是那样有点麻烦。直接暴力统计修改的位置 $i$ 附近的区间 $[i-1,i+1]$ 的段数，然后把变化加到 $\text{cnt}$ 上即可。

时间复杂度 $O(n+q)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX_N = 3e6 + 10;
char s[MAX_N];

// IO
inline ll read() {...}
inline void write(ll x) {...}
inline char gc() {...}

int cal(int l, int r) {
    int ret = 1;
    for(int i = l + 1; i <= r; i++)
        if(s[i] != s[i - 1])    ret++;
    return ret;
}

int main() {
    int q = read();
    scanf("%s", s + 1);
    int n = strlen(s + 1), cnt = cal(1, n);
    write(cnt + 1 >> 1), putchar('\n');
    while(q--) {
        int pos = read(); char c = gc();
        int old = cal(max(pos - 1, 1), min(pos + 1, n));
        s[pos] = c;
        int now = cal(max(pos - 1, 1), min(pos + 1, n));
        cnt += now - old;
        write(cnt + 1 >> 1), putchar('\n');
    }
    return 0;
}
```

---

## 作者：code_hyx (赞：0)

这道题作为第一题似乎难了点，本蒟蒻交了 $\text{7}$ 遍才过。 
首先，我们可以把字符串切分成一些子串，每一个子串都有相同字母构成。每两个子串，需要一次操作，所以只要求出要分成多少个子串就行了，答案**大致**就是子串数的一半。  
但本题还需要动态修改，每次操作都求一遍子串数显然会 $\text{TLE}$，所以只能动态维护。其实，每次修改的结果只与相邻的字符有关。  
以下分两种情况：   
1.本来和旁边一样，改了以后不一样了，划分子串数会多一个。  
2.本来和旁边不一样，改了以后一样了，划分子串数会少一个。   
左右两边都判断一次就行了，注意题目的下标是 $1$ 开始！  
代码：
```
#include<bits/stdc++.h>
using namespace std;
int t,p;
char ch;
string s; 
int getans(string s)
{
	int len=s.length(),cnt=0;
	for(int i=1;i<len;i++)
	{
		if(s[i]!=s[i-1])cnt++;
	}
	return cnt;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	cin>>s;
	int ans=getans(s);
	cout<<ans/2+1<<"\n";
	while(t--)
	{
		cin>>p>>ch;
		if((p!=1&&s[p-2]!=s[p-1]))
		{
			if(p==1||s[p-2]==ch)ans--;
		}
		if(s[p]!=s[p-1])
		{
			if(s[p]==ch)ans--;
		}
		if((p!=1&&s[p-2]==s[p-1]))
		{
			if(p==1||s[p-2]!=ch)ans++;
		}
		if(s[p]==s[p-1])
		{
			if(s[p]!=ch)ans++;
		}
		s[p-1]=ch;
		//cout<<ans<<" ";
		if(ans>=0)cout<<ans/2+1<<"\n";
		else cout<<0<<"\n";
	}
	return 0;
} 
```


---

## 作者：Convergent_Series (赞：0)

设 $S=\overline{a_1a_2\dots a_{cnt}}(a_i(1\le i \le cnt)$ 为仅含有一种字符的字符串 $)$ ，则   
$T=\begin{cases} 
\overline{a_1\textcolor{red}{a_1a_2}a_2a_3\textcolor{red}{a_3a_4}\dots \textcolor{red}{a_{cnt-1}a_{cnt}}a_{cnt}} & cnt \bmod 2=0 \\ 
\overline{a_1\textcolor{red}{a_1a_2}a_2a_3\textcolor{red}{a_3a_4}\dots \textcolor{red}{a_{cnt-2}a_{cnt-1}}a_{cnt-1} a_{cnt}\textcolor{red}{a_{cnt}}}& cnt \bmod 2=1 \\ 
\end{cases} $   
（黑色为字符串 $S$ ，红色为插入的部分）。
观察上式可得，插入段数 $ans=\lceil\frac{cnt}{2}\rceil $ 。

对于每一次询问，修改 $s_p$ 的值只会影响 $s_{p-1}\sim s_{p+1}$ 之间的关系（即是否在同一个 $a_i(1\le i \le cnt)$ 中）。可以统计修改前后 $s_{p-1}\sim s_{p+1}$ 中含有的 $a$ 型字符串的个数，修改 $cnt$ ，计算 $ans$ 即可。

## 代码：
```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
int read(){
	int a=0,f=1;
	char ch;
	ch=getchar();
	while(!((ch>='0'&&ch<='9')||ch=='-')) ch=getchar();
	if(ch=='-') f=-1,ch=getchar();
	while(ch>='0'&&ch<='9') a=a*10+ch-'0',ch=getchar();
	a*=f;
	return a;
} 
void write(int a){
	int num[100]={0},top=0;
	if(a<0) putchar('-'),a=-a;
	if(a==0){ putchar('0');return;}
	while(a) num[++top]=a%10,a/=10;
	while(top) putchar(num[top--]+'0');
}//快读快输
char s[3000100];
int ln,q,p,cnt,ans;
char c;
signed main(){
	int i;
	q=read();
	cin>>s+1;
	s[0]='A';//防止溢出
	ln=strlen(s);
	s[ln]='A';
	char tmp='A';
	for(i=1;i<ln;i++){
		if(s[i]!=tmp){
			cnt++;
			tmp=s[i];
		}
	}
	ans=cnt%2==1?(cnt+1)/2:cnt/2;
	write(ans);
	putchar('\n');
	while(q--){
		p=read();c=getchar();
		if(c==s[p]){//无需修改
			ans=cnt%2==1?(cnt+1)/2:cnt/2;
			write(ans);
			putchar('\n');
			continue;
		}
		tmp='A';
		int ts1=0,ts2=0;
		for(i=p-1;i<=p+1;i++){
			if(s[i]!=tmp){
				ts1++;
				tmp=s[i];
			}
		}//改前段数
		tmp='A';
		a[p]=c;
		for(i=p-1;i<=p+1;i++){
			if(s[i]!=tmp){
				ts2++;
				tmp=s[i];
			}
		}//改后段数
		cnt+=ts2-ts1;
		ans=cnt%2==1?(cnt+1)/2:cnt/2;
		write(ans);
		putchar('\n');
	}
	return 0;
} 

---

