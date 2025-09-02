# [NWRRC 2015] Hash Code Hacker

## 题目描述



According to Java standard library documentation, the hash code of String is computed as

$s[0] \times 31 ^ {n -1} + s[1] \times 31 ^ {n -2} + \cdots + s[n -1]$

Here $s[i]$ is the i-th character of the string, $n$ is the length of the string, and $^$ indicates exponentiation. Computation uses signed $32-bit$ integers in two's complement form.

Heather is going to hack the servers of Not Entirely Evil Recording Company $(NEERC).$ To perform an attack she needs $k$ distinct query strings that have equal hash codes. Unfortunately, NEERC servers accept query string containing lower- and uppercase English letters only.

Heather hired you to write a program that generates such query strings for her.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
4
```

### 输出

```
edHs
mENAGeS
fEHs
edIT
```

# 题解

## 作者：035966_L3 (赞：12)

>本题是 NWRRC 2015 Problem H。
>
>本题在 CodeForces 上有提交通道：[Gym 100801H](https://codeforces.com/gym/100801)。

------------

首先，考虑下面的字符串：
```plain
cccccccccccccccccccccccccccccccccccccccccccccccccc
```
**一共 $50$ 个 `c`。**

此处，为了表述方便，将这 $50$ 个 `c` 从左往右依次记为第 $49,48,\ldots,0$ 位。

接下来，将任意多个（$0 \sim 25$ 个）**互不重叠**的 `cc` 改为 `dD`，即可构造哈希值相等的不同字符串。限制修改次数为 $0 \sim 2$ 次，即可得到 $1178$ 个字符串，通过本题。

----------

**证明：**

设被修改的 `cc` 分别处于第 $i+1$ 位和第 $i$ 位（$i=48,47,\ldots,0$），则它们贡献的哈希值为：

$\quad 99 \times 31^{i+1}+99 \times 31^i$

$=99 \times 31 \times 31^i+99 \times 31^i$

$=(99 \times 31 +99) \times 31^i$

$=3168 \times 31^i.$

改为 `dD` 后，它们贡献的哈希值为：

$\quad 100 \times 31^{i+1}+68 \times 31^i$

$=100 \times 31 \times 31^i+68 \times 31^i$

$=(100 \times 31 +68) \times 31^i$

$=3168 \times 31^i.$

显然二者相等，因此修改后哈希值不变。

----------

**AC Code：**

```cpp
#include<iostream>
#include<string>
using namespace std;
const string stds="cccccccccccccccccccccccccccccccccccccccccccccccccc";//原字符串
const string rs="dD";//用于修改的字符串
int main()
{
	string s;
	int k,ans=1;
	cin>>k;
	cout<<stds<<'\n';//修改 0 次
	for(int i=0;i<=48;i++)//修改 1 次
	{
		if(ans==k) return 0;
		s=stds;
		s.replace(i,2,rs);
		cout<<s<<'\n';
		ans++;
	}
	for(int i=0;i<=46;i++)
		for(int j=i+2;j<=48;j++)//修改 2 次
		{
			if(ans==k) return 0;
			s=stds;
			s.replace(i,2,rs);
			s.replace(j,2,rs);
			cout<<s<<'\n';
			ans++;
		}
    return 0;
}
```

---

## 作者：Tjaweiof (赞：7)

# P7055 题解
[题目传送门](https://www.luogu.com.cn/problem/P7055)

看到这题的时候，千万不要被样例搞晕了，这题其实只需要适当的找规律。

这时我们可以考虑不要变化字符串的长度，把字符串中间的一些字串变化，得到哈希代码相同的字符串。

思考一会后，发现两个子串：`cc` 和 `dD`，`cc` 在当前位置变成 `dD` 时，字符串的哈希代码相同。

证明：

假设第一个 `c` 在字符串的第 $x$ 位。

则 `cc` 的哈希代码为：

$$

\begin{aligned}

&99\times31^{n-i-1}+99\times31^{n-(i-1)-1}\\

&=99\times31^{n-i-2}\times31+99\times31^{n-i-2}\\

&=99\times32\times31^{n-i-2}\\

&=3168\times31^{n-i-2}\\

\end{aligned}

$$

而 `dD` 的哈希代码为：

$$

\begin{aligned}

&100\times31^{n-i-1}+68\times31^{n-(i-1)-1}\\

&=100\times31^{n-i-2}\times31+68\times31^{n-i-2}\\

&=(100\times31+68)\times31^{n-i-2}\\

&=3168\times31^{n-i-2}\\

\end{aligned}

$$

至此，证明结束，结论成立。

于是我们想到可以将一个仅由 `c` 构成的字符串，将里面的 `cc` 变成 `dD`，为了方便，只变连续的一段。
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
	for (int i = 1; i <= 100; i++){
		for (int j = 1; j <= 100 - i + 1; j++){
			if (n){
				n--;
			} else {
				return 0;
			}
			for (int k = 1; k < j; k++){
				cout << "cc";
			}
			for (int k = 1; k <= i; k++){
				cout << "dD";
			}
			for (int k = j + i; k <= 100; k++){
				cout << "cc";
			}
			cout << endl;
		}
	}
    return 0;
}

```
此代码时间复杂度 $O(n)$，空间复杂度 $O(1)$，完美过关！

---

## 作者：我梦见一片焦土 (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/P7055)

------------
# 思路：
这题主要是找规律。

由于 $s[i] \times 31^{n-1-i} + s[i+1] \times 31^{n-2-i}$，故原式等于 $(s[i]+1) \times 31^{n-1-i} + (s[i+1]-31) \times 31^{n-2-i}$。

只要第 $i$ 位不是 ```z``` 或 ```Z```，且第 $i+1$ 位是一个不是 ```z``` 的小写字母，那么第 $i$ 位加一，第 $i+1$ 位变为这个小写字母对应的大写字母再加一即得到两个 ```hash``` 值相同的不同字符串，初始给 $1000$ 个位置全部赋为 $a$，每次对于不同的 $i$ 进行上述操作即可得到至多 $1000$ 个 ```hash``` 值相同的字符串。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int T;
char s[N];
signed main(){
    for(int i=0;i<1000;i++){
    	s[i]='a';
	}
    s[1000]=0;
    cin>>T;
    while(T--){
        cout<<s<<endl;
        for(int i=0;i<1000;i++){
            if(s[i]!='z'&&s[i]!='Z'&&'a'<=s[i+1]&&s[i+1]<'z'){
                s[i]++;
                s[i+1]=s[i+1]-'a'+'A'+1;
                break;
            }
        }
    }
    return 0;
}
```
完结撒花~

---

## 作者：jackzhangcn2013 (赞：2)

### P7055 题解

---

[题目传送门](https://www.luogu.com.cn/problem/P7055)

首先，我们从两个字符开始。

$$
a_1 \times 31^{2} + a_2 \times 31^{1}
$$

我们把式子稍微改一下，得：

$$
(a_1 \times 31 + a_2) \times 31
$$

也就是说，只要 $a_1 = b_1 - 1$ 与 $a_2 = b_2 + 31$，那么 $hash(a)$ 和 $hash(b)$ 肯定相等。

那么剩下的事情就好办了，只要选两个符合条件的字符串，比如我选的`fE`和`ed`，然后再使用这两个字符串组合出 $k$ 个长度一致的字符串即可。

### Code

---

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= 100; i++)
    {
        for(int j = 1; j <= 100 - i + 1; j++)
        {
            if(n)
            {
                n--;
            }
            else
            {
                system("pause");
                return 0;
            }
            for(int k = 1; k <= j - 1; k++)
            {
                cout << "fE";
            }
            for(int k = 1; k <= i; k++)
            {
                cout << "ed";
            }
            for(int k = i + j; k <= 100; k++)
            {
                cout << "fE";
            }
            cout << '\n';
        }
    }
    return 0;
}
```

---

## 作者：hhztl (赞：2)

## 题意简述
求出 $k$ 个哈希值相同的字符串。~~没错，就这么点。~~
## 算法分析
我们可以考虑在一个字符串的基础上构造其他哈希值相同的字符串。

先看下面的字符串：  
`aa`  
下面这个字符串与它的哈希值相同：  
`bB`  
~~自己应该算得出来吧~~

以此类推，一个全部由`aa`组成的字符串，应该可以将其中的`aa`改为`bB`。  
设`aa`在第 $i-1$ 位与第 $i$ 位，则哈希值为：  
$\quad 97 \times 31^{(n-i)}+97 \times 31^{(n-i-1)}$  
$=97 \times 31 \times 31^{(n-i-1)}+97 \times 31^{(n-i-1)}$  
$=(97 \times 31+97) \times 31^{(n-i-1)}$  
$=3104 \times 31^{(n-i-1)}$  
而`bB`的哈希值为：  
$\quad 98 \times 31^{(n-i)}+66 \times 31^{(n-i-1)}$  
$=98 \times 31 \times 31^{(n-i-1)}+66 \times 31^{(n-i-1)}$  
$=(98 \times 31+66) \times 31^{(n-i-1)}$  
$=3104 \times 31^{(n-i-1)}$

然后就可以快乐地打代码啦。

我们可以使用 dfs 来实现。
## 上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,s;
char a[30];
void dfs(int k){
    if(k>21){
        cout<<a<<'\n';
        if(++s>=n)exit(0);//如果个数足够就结束程序
        return;
    }a[k]=a[k+1]='a';//当前位是aa的情况
    dfs(k+2);
    a[k]='b';//当前位是bB的情况
    a[k+1]='B';
    dfs(k+2);
}int main(){
    cin>>n;
    dfs(0);
}
```
**请勿抄袭，后果自负！**

管理员辛苦啦！

---

## 作者：UniGravity (赞：2)

## Solution P7055 [NWRRC2015] Hash Code Hacker
[题目传送门](https://www.luogu.com.cn/problem/P7055)

**提供一种不同的构造思路（结尾字符串最短）。**
### 题意分析
大部分题解都是直接得出结论，我来具体讲讲：   
我们先从两个字符的情况开始枚举，可以发现满足条件的有很多：
```
Aa BB
Ab BC
Ac BD
Ad BE
Ae BF
Af BG
Ag BH
Ah BI
Ai BJ
Aj BK
...
```
这里给出枚举的代码以供参考：
```cpp
for (char i1 = 'A'; i1 <= 'z'; i1 = ((i1 == 'Z') ? 'a' : (i1 + 1))) {
    for (char i2 = 'A'; i2 <= 'z'; i2 = ((i2 == 'Z') ? 'a' : (i2 + 1))) {
            
        for (char j1 = 'A'; j1 <= 'z'; j1 = ((j1 == 'Z') ? 'a' : (j1 + 1))) {
            for (char j2 = 'A'; j2 <= 'z'; j2 = ((j2 == 'Z') ? 'a' : (j2 + 1))) {
                if (i1 == j1 && i2 == j2) continue;
                    
                if (hash1(i1, i2) == hash1(j1, j2)) {
                    printf("%c%c\n", i1, i2, j1, j2);
                    cnt++;
                    if (cnt >= k) break;
                }
            }
            if (cnt >= k) break;
        }
        if (cnt >= k) break;
        
    }
    if (cnt >= k) break;
}
```
哈希代码（只有两个值就不用循环了）：
```cpp
int hash1(char c1, char c2) {
    return c1 * 31 + c2;
}
```
------------
发现大部分题解采用的是单个修改，这样字符串长度较大，且需要特判，十分麻烦。

发现每 $2$ 位都有 $2$ 种可供选择的状态（`BB` 和 `Aa`）   
那么总共能选出 $2^{\frac{n}{2}}$ 种不同的字符串（$n$ 是字符串长度）。

发现 $2^{10}>1000$，所以我们的字符串长度就压到了 $20$ 位。

至于实现的过程，用深搜就可以了。

### 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
char s[1005];
int cnt = 0;

void dfs(int x) {
    if (cnt >= n) return;
    
    if (x > 10) {
        printf("%s\n", s);
        cnt++;
        return;
    }
    
    dfs(x + 1);
    
    s[x * 2] = 'A';
    s[x * 2 + 1] = 'a';
    dfs(x + 1);
    s[x * 2] = s[x * 2 + 1] = 'B';
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < 22; i++) {
        s[i] = 'B';
    }
    
    dfs(1);
    return 0;
}
```

---

## 作者：xiongyuhan (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P7055)

这道题表面看上去很难实际比较简单。

# 思路

首先，我们可以考虑构造出如下的字符串做基本串：

```cpp
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
```
共一百个 $\texttt{x}$。

然后我们可以将其中的任意连续的子序列 $\texttt{xx}$ 改成 $\texttt{yY}$。

# 证明

因为 $\texttt{x}$ 的值为 $120$，所以两个 $\texttt{x}$ 的贡献值总和为   $120 \times 31 + 120 \times 1 = 3840$。

而 $\texttt{y}$ 的值为 $121$，$\texttt{Y}$ 的值为 $89$ 贡献值总和为 $121 \times 31 + 89 \times 1 = 3840$。

这时我们可以发现这两个字串的贡献值居然是**一样的！！！**

所以我们可以把原字符串里任意两个连续的 $\texttt{x}$ 替换成 $\texttt{yY}$。

最后算一算最多需要改几个：

$99 \times 99 \div 2 \approx 5000$。

已经远远超过题目中 $k \le 1000$ 所以最多最多只用改两个子串。

**接下来上代码！！！**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, cnt = 1;//记录已经拥有几个满足要求的字符串
string s;
int main(){
    cin >> n;
    for(int i = 0 ; i < 100 ; i++) s += "x";//不改
    cout << s <<"\n";
    for(int i = 0 ; i < 99 ; i++){// 改一次
        s[i] = 'y';
        s[i + 1] = 'Y';
        cout << s <<"\n";
        cnt++;
        if(cnt == n) return 0;
        s[i] = 'x';
        s[i + 1] = 'x';
    }
    for(int i = 0 ; i < 99 ; i++){//两次中的第一次
        s[i] = 'y';
        s[i + 1] = 'Y';
        for(int j = i + 2 ; j < 99 ; j++){//两次中的第二次
            s[j] = 'y';
            s[j + 1] = 'Y';
            cnt++;
            cout << s <<"\n";
            if(cnt == n) return 0;
            s[j] = 'x';
            s[j + 1] = 'x';
        }
        s[i] = 'x';
        s[i + 1] = 'x';
    }
    return 0; 
}
```

---

## 作者：zibenlun (赞：2)

# 看到好多大佬都在写，我也来写一发

根据其他大佬的思路，我们可以想到用以下字符串作为基本串。


```ccccccccccccccccccccc……```

之后我们要找到一个等价于相同长度连续 $c$ 的字符串，那么首先就可以找到 $dD$。

过程：
$c$ 的值是 $99$，所以 $cc$ 的贡献是 $99×31+99×1=3168$，而我们可以通过写一个暴力代码求出与他相同的字符串：

```cpp
for(char i='a';i<='z';i++){
	for(char j='A';j<='Z';j++){
		if(i*31+j==3168){
			cout<<i<<j<<endl;
		}
	}
	for(char j='a';j<='z';j++){
		if(i*31+j==3168){
			cout<<i<<j<<endl;
		}
	}
}
for(char i='A';i<='Z';i++){
	for(char j='A';j<='Z';j++){
		if(i*31+j==3168){
			cout<<i<<j<<endl;
		}
	}
	for(char j='a';j<='z';j++){
		if(i*31+j==3168){
			cout<<i<<j<<endl;
		}
	}
}
```


之后我们就要想办法构造出每一种的字符串。可以发现总共 $n$ 的值与最长的字符串的值相同，所以我们可以按照 $n$ 的大小构造字符串的长度。然后把所有的字符串每一次选取两个字符修改为 $dD$，在输出。为了防止越界，需要把 ```n==1000``` 时字符串的长度控制在规定长度内，然后剩下的输出一个含有两个 $dD$ 的字符串即可。

# CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
string c;
int n;
int main(){
	cin>>n;
	for(int i=0;i<n+1;i++) c+="c";
	if(n==1000){
		c=c.substr(0,1000);
		printf("dDdD");
		for(int i=5;i<=1000;i++) putchar('c');
		putchar('\n');
	}
	for(int i=1;i<=999*(n==1000)+n*(n!=1000);i++){
		string s=c;
		s[i-1]='d';s[i]='D';
		cout<<s<<"\n";
	}
	return 0;
}
```


---

## 作者：hehejushi (赞：1)

# [原题传送门](https://www.luogu.com.cn/problem/P7055)
## 审题

先审题。审完题后，我们可以找到关键的突破口（即公式）：
> $$hash=s[0]×31 ^{(n−1)}+s[1]×31^{(n−2)}+⋯+s[n−1]$$
---
## 分析

考虑如下字符串：

`xxxxxxxxxxxxxxxxxxxxx`

（ 此处 `x` 指任意字母 ）。

将任意第 $i$ 和第 $i-1$ 位为 $x$ 的子串替换为 $(x+1)(x-31)$ 的 $ascii$ 值的对应字母。

原 hash 值

$ = ascii(x) \cdot 31^i + ascii(x) \cdot 31^{i-1}$ 。

新 hash 值

$= ascii(x) \cdot 31^i + 31^i + ascii(x) \cdot 31^{i-1}-31 \cdot 31^{i-1}$ 。

易说明，该式中第二项与第四项可以消除。

则两个 hash 值**相等**。

这不就是解题突破口吗？

## 方法

我们可以利用 $10$ 组 `xx`，将其中任意组 `xx` 替换为  `yY` ，达到哈希值相等的目的。

~~当然你用 mm nN 我也不拦着你。~~

## 最优效率分析

 $2^{10 }= 1024 > 1000$

所以用十组 `xx`/`yY` 就珂以完成。

## Talk is cheap. Show me your code.
```cpp
#include <iostream>
#include <string>
using namespace std;
int cnt, n;
void dfs(int dep ,string str )
{
	if(dep == 10){
		cout << str << endl;
		cnt++;
		if (cnt == n) exit(0) ;//搜到k个就结束程序 
		return ;
	}
	dfs (dep+1, str+"xx") ;
	dfs (dep+1, str+"yY") ;
}
int main()
{
	cin >> n;
	dfs(0,"");
}//no ctrl+c ctrl+v
```

---

## 作者：Flaw_Owl (赞：1)

# P7055 [NWRRC2015] Hash Code Hacker 题解

原题链接：[[NWRRC2015] Hash Code Hacker 题解](https://www.luogu.com.cn/problem/P7055)

## 写在前面

这道题的题解实际上大部分都是类似的，但是由于题目比较简单，比较少题解给出了相对完整的从拿到题到想出算法的过程。下文将从新手的角度撰写这道题的分析过程。同时，提出用二进制来生成串的一种方式。

## 题目分析

这道题虽然与进制哈希相关，但题目中已经给出了比较完整的说明，而且题意要求是输出 $k$ 个**哈希值相同**的字符串，所以不会进制哈希也完全没问题。

观察样例，发现好像看不出什么门道：字符串的长度不一，而且好像没什么规律。但观察下面两个样例输出：

```cpp
edHs
edIT
```

我们发现，除了单纯从无到有的构造，我们还可以尝试对已经有的字符串进行**改写**。这时候我们就容易想到：改变一个字母会对哈希值进行怎么样的改变？要保证一个串的哈希值不变，最少要改动几个字母？

不妨以一个两个字符的短串开始推导：

$$H = s[0] \times 31^1 + s[1] \times 31^0$$

假设我们将 $s[0]-1$，那么哈希值 $H$ 整体减少 $31$，相对的后面的部分就要增加 $31$ 以抵消这个影响，因此有：

$$H = (s[0]-1) \times 31^1 + (s[1]  - 31) \times 31^0$$

如果你对 ASCII 码足够熟练，你就会发现一个问题：相同字母的大小写之间的差值是 $32$。因此，我们有：

$$H = (s[0] - 1) \times 31^1 + (s[1]+32-1) \times 31^0$$

反映到字符串上的改变上，我们就可以认为：保证一个字符串的哈希值不变，最少只需改变两个连续的字母：第一位字母变成它的前一位；第二个字母变成其小写的前一位。举例来说，就是 `BB` 变成 `Aa`。

这样，对于一个串 `BBBB`，它至少可以变成三种形式而不改变其哈希值：`AaBB`，`BBAa`，`AaAa`。好像有点熟悉？让我们用一种更熟悉的形式：对于一个**二进制串** $00$，它可以变成 $01$，$10$，$11$。——将字符 `BB` 和 `Aa` 分别用 $0$ 和 $1$ 来表示，就可以方便地写出无数个完全不同但哈希值相同的串。

尝试分析一下可行性：题目中 $k$ 最大为 $1000$，而 $2^{10} = 1024$，只要 $10$ 位的二进制串，即长为 $20$ 的字符串就可以表示完所有的情况。

复杂度上，只要用 $k$ 个数字就可以表示完所有的情况（即 $k$ 个二进制串），每次用位运算检测最后一位，根据 $1$ 和 $0$ 的情况分别输出 `Aa` 和 `BB`。时间复杂度大概为 $O(N)$，在 $1 \leq N \leq 1000$ 的小数据量上绝对能过。

## 程序实现

```cpp
#include <iostream>
#include <cctype>
#define ll long long

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int k;

int main()
{
    k = read();
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if ((i >> j) & 1)
                printf("BB");
            else
                printf("Aa");
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：CodingOIer (赞：1)

## P7055 [NWRRC2015] Hash Code Hacker

### 题目解释

我们需要构造 $k$ 个字符串，使其在 Java 的字符串哈希构造（$s[0] \times 31 ^ {n -1} + s[1] \times 31 ^ {n -2} + \cdots + s[n -1]$）下得到的哈希值相同。

### 思路分析

使用以下的暴力枚举程序进行枚举，获取哈希相同的两位字符串：

```cpp
#include <cstdio>
int hash(char x, char y)
{
    return x * 31 + y;
}
int main()
{
    freopen("hash.txt", "w", stdout);
    for (char a : "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
    {
        for (char b : "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
        {
            for (char x : "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
            {
                for (char y : "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
                {
                    if (hash(a, b) == hash(x, y) && (a != x || b != y) && a != '\0' && b != '\0' && x != '\0' &&
                        y != '\0')
                    {
                        printf("%c%c:%c%c\n", a, b, x, y);
                    }
                }
            }
        }
    }
    return 0;
}
```

结果：[hash.txt](https://www.luogu.com.cn/paste/h75fa8tg)

我们从中挑选一位幸运观众，下面以 `bD:ac` 作为示例其他同理，下面是证明在一个任意串中，将任意个 `bD` 替换为 `ac` 得到的哈希值相同。

已知 $s_1, s_2, s_3, \dots, s_n$ 的哈希值为 $s_1 \times 32^n, s_2 \times 32^{(n-1)}, s_3 \times 32^{(n-2)}, \dots, s_n \times 32^0$。

在末尾添加一个 $s_{n + 1}$ 后哈希值为 $s_1 \times 32^n, s_2 \times 32^{(n-1)}, s_3 \times 32^{(n-2)}, \dots, s_n \times 32^1, s_{n + 1} \times 32^0$，提取公因数得 $31 \times (s_1 \times 32^n, s_2 \times 32^{(n-1)}, s_3 \times 32^{(n-2)}, \dots, s_n \times 32^0) + s_{n + 1} \times 32^0$。

以此类推得：**相同**字符串加上**哈希相同**的**不同**字符串**哈希相同**，接着加上另外一个**相同**字符串**哈希相同**。

得：在一个字符串中把任意的连续字串替换为哈希相同的字串，哈希值不变。

### 代码实现

使用二进制枚举 dfs 状态（长度为 $2 \times 20$ 的字符串有 $1048576$ 种情况，满足本题 $k \le 1000$ 的要求），`1` 输出 `db`，`2` 输出 `ac`，重复 $k$ 次，即得到 $k$ 个相同哈希的不同字符串。

```cpp
#include <cstdio>
int k;
int main()
{
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if ((i >> j) & 1)
            {
                printf("bD");
            }
            else
            {
                printf("ac");
            }
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Binah_cyc (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P7055)

其它题解好像只给出了结论，哪怕是最高赞题解也仅证明其结论的正确性，没有讲这个结论是怎么来的。

我发一篇题解来从头说说其它题解那些规律的来源。

## 题意简述
给定一个字符串 $g$，规定它的 Hash 值为：

 $$s_0 \times 31^{n-1} + s_1 \times 31^{n-2} + \dots + s_{n-1}$$ 

此处 $s$ 的下标从 $0$ 开始。

现让你求 $k$ 个字符串，使它们的哈希值一样。

## 题目分析
我们可以注意到，这个表示方法有一个很大的缺陷：如果将共计 $52$ 种大小写字母看作 $52$ 种数字，那么这就是一个每一位都有 $52$ 种数字的 $31$ 进制数（这句话感觉怪怪的）。

所以，在这个 $31$ 进制数中，低位加 $31$ 就相当于高位加 $1$，即进位。那么，如果将相邻两位中高位的字母变成它前面的一个字母（相当于减 $1$），将低位的字母变成它在 ASCII 码中向后数 $31$ 位（相当于加 $31$）值是不会变的。

## 细节
在 ASCII 码中，大写字母与小写字母之间还有 `[\]^_`\` 这 $6$ 个字符，所以一个大写字母在 ASCII 码中向后移动 $31$ 位就相当于把它变成小写后再向前推进一位，这也就是为什么其它题解中选择能将 `cc` 改成 `dD` 的原因。

## 实现方法

这个题有很多实现方法，其中最简单的方法就是先指定一个字符串作为基准，再在基准上做改动。由于两个小写字母只有两种表现形式，所以可以循环或搜索解决。

## Code

知道了原理，就很好写代码了。我是用搜索实现的。
```c
#include <bits/stdc++.h>
using namespace std;
int k,cnt;//cnt记录现在已经有多少种方案了 
bool vis[35];//vis[i]=1表示这两个字母为cc，否则为dD 
void dfs(int x) //当前已经搜到第 x 位 
{
	if(x==25) //25位时输出 (其实20为就够了) 
	{
		for(int i=1;i<=25;i++) cout<<((vis[i])?"cc":"dD"); //三目运算符 
		cout<<endl;
		cnt++;
		if(cnt==k) exit(0);  //exit(0)表示终止整个程序 
		return ;
	}
	dfs(x+1);//不选 
	vis[x]=1;
	dfs(x+1);//选 
	vis[x]=0;//回溯 
}
int main()
{
	cin>>k;
	dfs(1);
	return 0;
}

```

---

## 作者：Xssion37_XY (赞：0)

### 前情提要

[题目链接](https://www.luogu.com.cn/problem/p7055)

[更好的阅读体验](https://www.luogu.com.cn/article/9dqybz8d)

### 实际分析

经典规律题。

观察一会，想到了可以替换某些字符。

发现 ```cc``` 与 ```dD``` 的哈希码相同，很容易证明。

我们设 ```cc``` 分别在第 $n$ 和 $n+1$ 位。

```cc``` 的哈希码为：

$=99\times31^{n+1}+99\times31^n$

$=3186\times31^n$

同理，```dD``` 的哈希码为：

$=100\times31^{n+1}+68\times31^n$

$=3186\times31^n$

即：```cc``` 与 ```dD``` 的哈希码相同。

将 ```cc``` 换成 ```dD``` 即可通过此题。

### 代码部分

```
#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	int cnt = n;
	for (int i = 1; i <= 233; i ++) {
		for (int j = 1; j <= 233 - i + 1; j ++) {
			if (!cnt) {
				return 0;
			}
			cnt --;
			for (int k = 1; k <= j - 1; k ++) {
				cout << "cc";
			}
			for (int k = 1; k <= i; k ++) {
				cout << "dD";
			}
			for (int k = i + j; k <= 233; k ++) {
				cout << "cc";
			}
			cout << "\n";
		}
	}
	return 0;
}
```

完结撒花！

---

## 作者：遥遥领先 (赞：0)

# P7055 [NWRRC2015] Hash Code Hacker题解

题意：按照题目所给哈希值算法求出 $k$ 个哈希值相等的字符串并输出。

怎样构造哈希值相等的两个字符串呢？

我先用一个问题来引入。

**问题：求出一个与 `cc` 哈希值且长度相等的字符串。**

首先，我们需要算出 `cc` 的哈希值，即：

$\ \ \ \ 99\times31+99$

$=(99+1)\times31+99-31$

$=100\times31+68$

因为 $100$ 对应的字符是 `d`，并且 $68$ 对应的字符是 `D`，所以我们就能得到 `cc` 的哈希值与 `dD` 的哈希值是相等的。

那么第二个问题就是，字符串需要设置多长？

**问题：若有 $50$ 个 `c`，那么：**
- 将**一**个 `cc` 改为 `dD`，可得到多少个字符串不同，但哈希值相同的字符串?
- 将**两**个**不重合的** `cc` 改为 `dD`，可得到多少个字符串不同，但哈希值相同的字符串?

第一个问题，显而易见，从开头到结尾共有 $49$ 个 `cc`，即 $49$ 种情况；

第二个问题，有多种情况：

第一个 `cc` 为整个字符串的第一个 `cc`，第二个 `cc` 是其它的 `cc`，共 $47$ 种情况。

第一个 `cc` 为整个字符串的第二个 `cc`，第二个 `cc` 是其它的 `cc`，共 $46$ 种情况。

第一个 `cc` 为整个字符串的第三个 `cc`，第二个 `cc` 是其它的 `cc`，共 $45$ 种情况。

如此反复下去，共有 $47+46+45+\dots+1$，即 $1128$ 种情况。

所以，总共就有 $1177$ 种情况，最后再加上不改变字符串，就有 $1178$ 种字符串。

题目要求最多 $1000$ 个字符串，长度为 $50$ 的字符串肯定够了。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;

string s;

signed main()
{
	//1.将原字符串赋值为 50 个 c 
	s = "cccccccccccccccccccccccccccccccccccccccccccccccccc";
	
	//2.输入需要字符串个数
	int k;
	cin >> k;
	
	//3.改变 0 个 cc
	cout << s << '\n';
	k--;
	
	//4.改变 1 个 cc
	int pos = 0;
	while (k && pos < 50-1)
	{
	    k--;
		string t = s;
		t[pos] = 'd';
		t[pos+1] = 'D';
		cout << t << '\n'; 
		pos++;
	}
	
	//注意特判字符串数量是否已达标 
	if (k <= 0) return 0;
	
	//5.改变 2 个 cc 
	int pot = 2;
	pos = 0;
	while (k)
	{
	    k--;
		string t = s;
		t[pos] = 'd';
		t[pos+1] = 'D';
		t[pot] = 'd';
		t[pot+1] = 'D';
		cout << t << '\n';
		pot++;
		if (pot == 50-1)
		{
			pos++;
			pot = pos+2;
		}
	}
	
	return 0;
}

```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7055)

这题其实非常的简单啊。

我们可以让字符串的长度一定，仅改变里面的部分字符。

那么能不能找到两个长度相同，而内容不同的很短的字符串，使两者的哈希码相同呢？

`aa` 和 `bB` 这一对字符串符合要求。

我们只要搞一个长度为 $50$ 的全是 `a` 的字符串，然后选择 $0$ 到 $2$ 个不重叠的 `aa` 改成 `bB` 就可以了。

证明如下：

设要修改的 `aa` 在字符串从后往前数第 $i$ 和 $i + 1$ 位的位置（从 $0$ 开始数）。

那么它们的哈希值是：

$$\begin{aligned} hash(a,a) &= 97 \times 31 ^ {i + 1} + 97 \times 31 ^ i \\ &= 97 \times 31 ^ {i + 1} + 31 ^ {i + 1} + 97 \times 31 ^ i - 31 ^ {i + 1} \\ &= 98 \times 31 ^ {i + 1} + 97 \times 31 ^ i - 31 \times 31 ^ i \\ &= 98 \times 31 ^ {i + 1} + 66 \times 31 ^ i \\ &= hash(b,B) \end{aligned}$$

所以 `aa` 和 `bB` 的哈希值是相等的！

$49 \times 49 \div 2$ 已经有 $1200$ 了，而 $k \le 1000$，绝对够了。

最后放出代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
char s[50];
int k, cnt = 1;//cnt计输出了多少个字符串
int main(){
	cin >> k;
	for (int i = 0; i < 50; i++) s[i] = 'a';//原字符串
	cout << s << endl;//不修改
	if (k == 1) return 0;
	for (int i = 0; i < 49; i++){//修改一次
		s[i] = 'b', s[i + 1] = 'B';
		cout << s << endl;
		cnt++;
		if (cnt >= k) return 0;
		s[i] = 'a', s[i + 1] = 'a';
	}
	for (int i = 0; i < 49; i++){//修改两次
		s[i] = 'b', s[i + 1] = 'B';
		for (int j = i + 2; j < 49; j++){
			s[j] = 'b', s[j + 1] = 'B';
			cout << s << endl;
			cnt++;
			if (cnt >= k) return 0;
			s[j] = 'a', s[j + 1] = 'a';
		}
		s[i] = 'a', s[i + 1] = 'a';
	}
	return 0;
}
```

---

