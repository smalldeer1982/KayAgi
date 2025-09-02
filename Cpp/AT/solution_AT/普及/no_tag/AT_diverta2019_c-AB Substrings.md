# AB Substrings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/diverta2019/tasks/diverta2019_c

すぬけ君は $ N $ 個の文字列を持っています。$ i $ 番目の文字列は $ s_i $ です。

これらの文字列を好きな順序で並べたあと、連結して $ 1 $ つの文字列を作ることを考えます。 作った文字列に `AB` という部分文字列が含まれる個数としてありうる値のうち、最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{4} $
- $ 2\ \leq\ |s_i|\ \leq\ 10 $
- $ s_i $ は英大文字のみからなる

### Sample Explanation 1

\- 例えば、`ABCA`, `BAD`, `XBAZ` の順で連結して `ABCABADXBAZ` を作ったとき、`AB` という部分文字列は $ 2 $ つ含まれます。

## 样例 #1

### 输入

```
3
ABCA
XBAZ
BAD```

### 输出

```
2```

## 样例 #2

### 输入

```
9
BEWPVCRWH
ZZNQYIJX
BAVREA
PA
HJMYITEOX
BCJHMRMNK
BP
QVFABZ
PRGKSPUNA```

### 输出

```
4```

## 样例 #3

### 输入

```
7
RABYBBE
JOZ
BMHQUVA
BPA
ISU
MCMABAOBHZ
SZMEHMA```

### 输出

```
4```

# 题解

## 作者：ISTP (赞：4)

## 引子

这是蒟蒻柒米的第二篇题解，请多关照。

随机跳转到的一道 AT 黄题，发现能做，也还没有题解，就顺便写了篇。

[更好的阅读体验](https://www.luogu.com.cn/blog/528540/solution-at-diverta2019-c)。

## 题面

[原题面：https://www.luogu.com.cn/problem/AT_diverta2019_c](https://www.luogu.com.cn/problem/AT_diverta2019_c)

题意简述：

有 $ N $ 个字符串，将它们以某种顺序连接成一个新字符串， 求这个新字符串中子串 $\texttt{AB}$ 的最大可能出现次数。

## 思路

简单分析了一下：

+ 每个字符串中间的 $\texttt{AB}$ 不因拼接而改变。可以直接统计。

+ 每个字符串结尾的 $\texttt{A}$ 字符和开头的 $\texttt{B}$ 字符可能会额外影响到最后的结果。

+ 那么可以将所有用于拼接的字符串分为四类：

  1. 以 $\texttt{A}$ 结尾；

  2. 以 $\texttt{B}$ 开头；

  3. $\texttt{A}$ 结尾，$\texttt{B}$ 开头，二者兼备；

  4. 啥也没有。

想一想，发现可以分类讨论。

- 首先，肯定是 “$\texttt{A}$ 结尾，$\texttt{B}$ 开头，二者兼备” 的字符串比较好用。只要将所有这类字符串首尾相接就行了。

- 其次，那类首尾相接的字符串，前面还可以接一个 “以 $\texttt{A}$ 结尾” 的字符串，后面也能接一个 “以 $\texttt{B}$ 开头” 的字符串。且如果有这两类字符串拼接到头尾的话，效益最大化。

- 考虑首尾相接的字符串可能出现的不同效益。设有 $\text{x}$ 个第三类字符串，如果没有第一、二类字符串与它相接，收益为 $\text{x - 1}$；如果有一种与它相接，收益为 $\text{x}$；如果头尾都接上了，收益为 $\text{x + 1}$。

- 最后，将可能剩余的 “以 $\texttt{A}$ 结尾” 和 “以 $\texttt{B}$ 开头” 的两类字符串两两配对，每对都能贡献 1 个子串。

- 那么最后可能的落单的 “以 $\texttt{A}$ 结尾” 或 “以 $\texttt{B}$ 开头” 的字符串，还有啥也没有的字符串，就不能产生额外贡献了。

假设这里已经统计出了所有字符串中间的 $\texttt{AB}$ 的数量和前三类字符串的数量，分别存储在变量 $ans$，$a$，$b$，$c$ 中。

那么按以上策略分类讨论进行拼接，我们便有了以下代码：

```cpp
if(a && b && c) cout << ans + c + 1 + min(a - 1, b - 1); //中间子串 + 贡献拉满的第三类字符串 + 一、二类组合所得
else if(a && b && !c) cout << ans + min(a, b); //由于没有第三类字符串，所以中间子串 + 一、二类组合
else if(a && !b || !a && b) cout << ans + c; //中间子串 + 由于只有一、二类字符串中的一种，所以第三类字符串只能加上接头或尾的贡献
else if(!a && !b && c) cout << ans + c - 1; //中间子串 + 由于没有一、二类字符串，所以只有第三类字符串单独的贡献
else cout << ans; //啥也没有，只有中间字符串
```

那就先把所有字符串中间的 $\texttt{AB}$ 子串和不同类别的字符串统计出来吧。

## 输入 & 统计

这里不多赘述，在输入用于拼接的字符串数量 $N$ 后，以字符串数组存储后续的输入

如上，分别用变量 $ans$，$a$，$b$，$c$ 来统计字符串中间的 $\texttt{AB}$ 子串数量和上文所述的前三种字符串的数量。

至于第四类，啥也没有的，无法作出额外贡献，就无需统计了。可以理解为将所有这类字符串随便拼到了最后面。

## 完整代码

只要补齐框架、定义和输入就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
string str[10001];
int main(){
	int n;
	cin >> n;
	int ans = 0, a = 0, b = 0, c = 0;
	for(int i = 1; i <= n; i ++){
		cin >> str[i];
		int len = str[i].size();
		for(int j = 1; j < len; j ++) //遍历一遍以统计字符串中 "AB" 的数量
			if(str[i][j - 1] == 'A' && str[i][j] == 'B') ans ++;
		if(str[i][len - 1] == 'A' && str[i][0] == 'B') c ++;
		else if(str[i][len - 1] == 'A') a ++;
		else if(str[i][0] == 'B') b ++; //这里需要注意一下判断不同类别的顺序
	}
	if(a && b && c) cout << ans + c + 1 + min(a - 1, b - 1);
	else if(a && b && !c) cout << ans + min(a, b);
	else if(a && !b || !a && b) cout << ans + c;
	else if(!a && !b && c) cout << ans + c - 1;
	else cout << ans;
	return 0;
}
```

## Ending

- Upd on 23.1.2：调整了一些变量和字符串常量的 $\LaTeX$，修改了讲解顺序，删去了一些冗余部分。

完结撒花！！

有问题或 hack 之类的要艾特柒米哦，也欢迎在评论区指出或私信我。

*22.12.28*

---

## 作者：ht__QAQ__ (赞：2)

## 大意：

排序字符串，再拼接，求```AB```的最大可能出现次数。(洛谷一开始的某种顺序没看懂是什么东西用了翻译)。


## 思路：
可以想到有一下方法可以找到```AB``` ：

- 字符串内

- 开头B 结尾A

先在字符串内判断是否有```AB```，在特判是否开头B 结尾A。然后有了以下代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    string s[10001];
    int sum=0,a=0,b=0,ab=0,ans=0;
    for(int i=0;i<n;i++){
        cin>>s[i];
        for(int j=0;j<s[i].size()-1;j++){
            if(s[i][j]=='A'&&s[i][j+1]=='B'){
            	sum++;
			}
        }
        if(s[i][s[i].size()-1]=='A'&&s[i][0]=='B'){
        	ab++;
		}
    }
	  ans=sum;
    cout<<ans+ab<<'\n';
    return 0;
}
```
但是WA了。接着想了，可能判断多了，于是又统计开头B 结尾A，就有了以下判断代码：
```cpp
if(ab!=0 and ab==a and ab==b){//判断防止出错 
   ans=sum+ab-1;//统计 
}else{
	ans=sum+min(a,b);
	}
```
紧接着AC了有了以下代码。

### 注意判断选最小！

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;//多少个 
    cin>>n;
    string s[10001];//字符串数组 
    int sum=0,a=0,b=0,ab=0,ans=0;
    for(int i=0;i<n;i++){
        cin>>s[i];//输入 
        for(int j=0;j<s[i].size()-1;j++){
            if(s[i][j]=='A'&&s[i][j+1]=='B'){//判断 
            	sum++;
			}
        }
        //特判 是否开头B 结尾A 
        if(s[i][s[i].size()-1]=='A'&&s[i][0]=='B'){
        	ab++;
		}
        if(s[i][s[i].size()-1]=='A'){
        	a++;
		}
        if(s[i][0]=='B'){
        	b++;
		}
    }
    if(ab!=0 and ab==a and ab==b){//判断防止出错 
    	ans=sum+ab-1;//统计 
	}else{
		ans=sum+min(a,b);
	}
    cout<<ans<<'\n';//AT要换行 
    return 0;
}
```
## 结尾（不看划走）：
这是本人第一次写题解，多多关照，谢谢！

管理审核辛苦了！

---

## 作者：ruanshaochuan______ (赞：0)

如果是字符串内原本就有的 $AB$ 串，直接统计就可以了，真正需要考虑的是拼接后多出来的 $AB$ 串。  
我们发现只有开头是 $B$ 和末尾是 $A$ 的字符串才能与其他字符串拼接之后产生 $AB$ 串。   
于是我们可以把字符串分为 $4$ 类：

1. 开头是 $A$ 且结尾是 $B$ 的字符串。
1. 开头是 $A$ 且结尾不是 $B$ 的字符串。
1. 开头不是 $A$ 且结尾是 $B$ 的字符串。
1. 啥都没有的字符串。                 

设第一种的数量为 $a$，第二种的数量为 $b$，第三种的数量为 $c$，原本就有的 $AB$ 串的数量为 $sum$。  
如果第一种与第一种可以首尾相接产生 $a-1$ 个 $AB$ 串，另外第二种与第三种拼接在第一种的头和尾都能产生一个 $AB$ 串。而第二种和第三种去除掉和第一种拼接掉，也可以两两配对，每一对产生一个 $AB$ 串，这样我们就可已得到以下代码：
```cpp
cout<<sum+max(0,a-1)+min(1,c*bool(a))+min(1,b*bool(a))+max(0,min(b-bool(a),c-bool(a)));
\\bool(a)是用来判断有没有第一种字符串的
```
我们就只要统计然后计算就可以了。  
 完整代码
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,sum;
string s;
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>s;
		for(int i=0;i+1<s.size();i++)
			if(s[i]=='A'&&s[i+1]=='B')
				sum++;
		if(s[0]=='B'&&s[s.size()-1]=='A')
			a++;
		else
		if(s[0]=='B')
			b++;
		else
		if(s[s.size()-1]=='A')
			c++;
	}
	cout<<sum+max(0,a-1)+min(1,c*bool(a))+min(1,b*bool(a))+max(0,min(b-bool(a),c-bool(a)));
}
```


---

## 作者：Samhu07 (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_diverta2019_c)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/diverta2019_c)

## 思路

首先分析题目发现，字符串大致可分为 $5$ 种：

1. 在中间含有 `AB`。

2. 开头含有 `B`。

3. 结尾含有 `A`。

4. 开头有 `B`， 结尾有 `A`。

5. 以上都不是（什么也没有）。

对于第 $5$ 种情况，**直接忽略**即可，我们来重点看看 $2,3,4$ 种情况。

对于情况 $2$ 可与情况 $3$ 连接构成新的 `AB`，也可以与情况 $4$ 构成新的 `AB`。

对于情况 $3$ 可也与情况 $2,4$ **相接**。

对于情况 $4$ 放在情况 $2,3$ 中间即可使其**贡献最大**。

分析完以上 $3$ 种情况的各自贡献，我们就需要分析分别拥有它们可构成的**最大贡献**（假设情况 $2,3,4$ 分别有 $x,y,z$ 个）：

- 情况 $2,3,4$ **都拥有**，那么构成的最大贡献就是充分利用 $4$ 的优势，把 $4$ 全部用掉产生 $z$ 点贡献，**接着能用 $2,3$ 就用，可产生 $\min(x - 1,y - 1)$ 点贡献**。

- 拥有情况 $2,3$，那么就让这两种字符串**充分贡献即可**，可产生 $\min(x,y)$ 点贡献。

- 拥有情况 $2,4$ 或 $3,4$，那么只能把 $4$ **首尾相接**，**产生 $z$ 点贡献**。

- 仅有情况 $4$，只能让 $4$ 首尾相接，**不过因为没有 $2,3$，所以只能产生 $z-1$ 点贡献**。

经过以上分类讨论，很容易即可写出**代码**了：

```cpp
#include<iostream>
using namespace std;

int n, ans, x, y, z;
string str;

int main(){
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		cin >> str;
		int l = str.length();
		for(int j = 0; j < l - 1; j ++) 
			if(str[j] == 'A' && str[j + 1] == 'B') ans ++; // 计算中间有 AB 子串的数量
  		// 计算 3 种情况的数量
		if(str[l - 1] == 'A' && str[0] == 'B') z ++;
		else if(str[l - 1] == 'A') x ++;
		else if(str[0] == 'B') y ++;
	}
	if(x && y && z) cout << ans + z + 1 + min(x - 1, y - 1) << endl; // 2 3 4 都拥有
	else if(x && y && !z) cout << ans + min(x, y) << endl; // 拥有 2 3，没有 4
	else if(x && !y || !x && y) cout << ans + z << endl; // 拥有 2 3 中的一种和 4
	else if(!x && !y && z) cout << ans + z - 1 << endl; // 只有 4
	else cout << ans << endl; // 啥也没有
	return 0;
}

```

$$\text{The End!}$$

---

## 作者：__Octhyccc__ (赞：0)

[AC 记录](https://www.luogu.com.cn/record/116562041)

先把用到的函数解释一下：

```cpp
int read() {
    register int x = 0,f = 1;register char ch;
    ch = getchar();
    while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
    while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}
void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9){write(x/10);putchar(x%10+'0');}
	else putchar(x+'0');
	return; 
}//快读快写，没啥用但是我愿意用。
int min2(int x,int y){
	return (x<y)?x:y;
}//返回最小值。
```
然后我看了一眼题面，果断用字符串数组来做，每个字符串中间出现的 ```AB``` 必须要记数器加 $1$，代码实现这一部分如下（$cnt$ 为计数器）：

```cpp
for(int i=0;i<n;i++){
	for(int j=1;j<s[i].length();++j){
		if(s[i][j-1]=='A'&&s[i][j]=='B')cnt++;
	}
}
```

然后就是分类讨论了，每个字符串都属于以下 $4$ 种情况之一：

- 开头是 ```B```，结尾是 ```A```，用变量 $headtail$ 储存数量。
- 只是开头是 ```B```，用变量 $head$ 存储数量。
- 只是结尾是 ```A```，用变量 $tail$ 存储数量。
- 以上情况均不符合。

以上部分可以用以下代码实现：

```cpp
for(int i=0;i<n;i++){
	if(s[i][0]=='B' && s[i][s[i].length()-1]=='A')headtail++;
	else if(s[i][0]=='B')head++;
	else if(s[i][s[i].length()-1]=='A')tail++;
}
```

我们把每个 $headtail$ 字符串首尾相接，就得到了 $headtail-1$ 个 ```AB```，为了使数量最大化，我们可以将前面拼上一个 $tail$ 字符串，在后面拼上一个 $head$ 字符串，可以这样实现：

```cpp
if(headtail>0){
	cnt+=(headtail-1);
	headtail=1;
	if(tail>0){
		cnt++;
		tail--;
	}
	if(head>0){
		cnt++;
		head--;
	}
}
```

然后计数器 $cnt$ 再加上 ```min(head,tail);``` 就得到了正确答案。

完整代码就不贴出来了，我们要养成自己写代码的好习惯。

---

## 作者：dyc2022 (赞：0)

## 简要题意

有 $n$ 个字符串，将这 $n$ 个字符串按照一定的顺序首尾相接连在一起。求连成的字符串中最多有几个 `AB` 子串。

## 做法

经过对题意的一通分析，我们知道连成字符串中一个 `AB` 子串有两种来源：

1. 这个 `AB` 是原来 $n$ 个字符串中的一个的子串。这就意味着，无论这 $n$ 个字符串以什么顺序连接，这些 `AB` 子串的数量是不变的。
2. 这个 `AB` 子串是两个字符串连接时形成的。这就必须满足前一个串的最后一个字符是 `A`，后一个串的第一个字符是 `B`。

***

对于 1，我们只需要在一开始把符合条件的 `AB` 子串数出来。

对于 2，我们就必须进行分类讨论。

设三个整型变量：$sa$、$sb$、$sab$，其中 $sab$ 表示由 `B` 结尾，由 `A` 开头的字符串的个数，$sa$ 表示不由 `B` 结尾，但以 `A` 开头的字符串的个数，$sb$ 表示由 `B` 结尾，但不由 `A` 开头的字符串的个数。

现在，我们有了 $sa$ 个 `xxA` 形式的串，$sb$ 个 `Bxx` 形式的串，$sab$ 个 `BxA` 形式的串。接下来进行如下操作：

（第一步）将所有 `BxA` 形式的串先首尾相接，连到一起，变成：

```
BxA BxAB ....A BxA
```

总共形成了 $sab - 1$ 个 `AB`。

(第二步）将一个 `xxA` 接到上面的字符串前面，再将一个 `Bxx` 接到字符串的末尾，变成：

```
xxA BxA BxAB ....A BxA Bxx
```

又多形成了 $2$ 个 `AB`。

（第三步）最后将剩余的 `xxA` 和 `Bxx` 两两配对，一个 `xxA` 和一个 `Bxx` 会形成：

```
xxA Bxx
```

最后多形成的 `AB` 串个数是 $sa-1$ 和 $sb-1$ 的最小值。

（为什么要减一？因为在第二步的时候已经有用掉了一个 `xxA` 和一个 `Bxx`）

当然，上述的操作都是对于每种串都大于等于 $1$ 个的情况。真实情况会稍微复杂一点。具体细节参见以下 AC 代码注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,sa,sb,sab,ans;
main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		char str[49];
		scanf("%s",str);
		len=strlen(str);
		if(str[0]=='B'&&str[len-1]=='A')sab++;
		else if(str[0]=='B')sb++;
		else if(str[len-1]=='A')sa++;
		for(int i=0;i<len-1;i++)if(str[i]=='A'&&str[i+1]=='B')ans++;
	}
	if(sa&&sb&&sab)ans+=sab-1+2+min(sa-1,sb-1);//可以完成第一步、第二步、第三步。
	else if(sa&&sb)ans+=min(sa,sb);//当sab==0，就无法做第一步，由于没有第一步，所以也无法完成第二步。因此这次只能完成第三步，因为第二步没有做，所以不用减一。
	else if(sa&&!sb&&sab||!sa&&sb&&sab)ans+=sab;//只能完成第一步，第二步只能做一半。
	else if(!sa&&!sb&&sab)ans+=sab-1;//只能完成第一步
	return printf("%d\n",ans),0;
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

有 $N$ 个字符串，求排序并连接后字符串中 `AB` 的数量。

## 思路

字符串中出现 `AB` 分为 $2$ 种情况：

1. 直接出现 `AB`，这里记为 $ans$；
2. 连接组成 `AB`，又有 $3$ 种情况：

	1. 以 `B` 开头，这里记为 $b$；
	2. 以 `A` 结尾，这里记为 $a$；
	3. 以 `B` 开头且以 `A` 结尾，这里记为 $ba$。

那么

-   将 $ba$ 全部连接在一起，有 $ba - 1$ 个 `AB`；
-   将连接在一起的 $ba$ 开头拼接 $a$，结尾连接 $b$，有 $2$ 个 `AB`；
-   将剩下的 $b$ 与 $a$ 两两连接。

分类讨论，得

```
if a && b && ba             ans + ba + 1 + min(a - 1, b - 1)  
else if a && b && !ba       ans + min(a, b)                   
else if a && !b || !a && b  ans + ba
else if !a && !b && ba      ans + ba - 1
else                        ans
```

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ui unsigned int
using namespace std;

int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
	int n; scanf("%d", &n); 
	int ans, a, b, ba; ans = a = b = ba = 0;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s; 
		int len = s.size();
		for(int j = 1; j < len; j++) 
			if(s[j - 1] == 'A' && s[j] == 'B') ans++;
		if(s[0] == 'B' && s[len - 1] == 'A') ba++;
		else if(s[0] == 'B') b++;
		else if(s[len - 1] == 'A') a++;
	}
	if(a && b && ba) printf("%d\n", ans + ba + 1 + min(a - 1, b - 1));
	else if(a && b && !ba) printf("%d\n", ans + min(a, b));
	else if(a && !b || !a && b) printf("%d\n", ans + ba);
	else if(!a && !b && ba) printf("%d\n", ans + ba - 1);
	else printf("%d\n", ans);
	return 0;
}
```

---

## 作者：gsc15759915601 (赞：0)


# 思路：

这题其实很水，但是坑很多，但是我们只要运用了量化的思维，将字符串的一些数据进行量化存储，并且加入一些细节的判断和计算，我们再将它们进行一定的加减就简单多了。

# 说明：

在开始我们先创建好我们常见的变量及字符串，在此题中要输入多个字符串，所以我们创建一个字符串数组 ```s``` 和一个长度变量 ```n```，并且利用 ```for``` 循环进行循环输入。

### 重点：

我们还要对输入的字符串进行判断和分类，大致可以分为三类，分别是:
- “封闭类”：开头不为 ```B``` 且结尾不为 ```A```；
- “单开类”：开头是 ```B``` 或结尾为 ```A```；
- “双开类”：开头为 ```B``` 并且结尾为 ```A```。

在“单开类”中还有两类，
- “```B``` 开头类”
- “```A``` 结尾类”。

这时我就对这几类字符串进行计数，分别用 ```a```，```b```，```ab``` 储存。

并且对所有的字符串内部的 ```AB``` 数量进行计数，用变量 ```m``` 储存。

到了最后的总结阶段。我用变量 ```h``` 进行储存总数。首先直接将 ```h``` 在字符串内部的数量算入 ```m```；其次，在判断“双开类”的字符串先于“双开类”相配对，将数量算入 ```h```，将“双开类”的多个字符串转为一个字符串，然后将最后一个“双开类”的字符串与“单开类”的相匹配，匹配完之后记入 ```h```，再将“单开类”分别减去一个字符串的数量，最后将“单开类”进行匹配计入 ```h```。

最后再输出一下，就可以了。

在此，大家可以在评论区提出建议，积极听取改进。

# Code：


```cpp
#include<bits/stdc++.h>//万能头文件，不建议！
using namespace std;
long long n,m = 0,a = 0,b = 0,ab = 0,h = 0;//所有变量，以及其初值。
string s[10002];//定义字符串数组。
int main(){
    cin>>n;//输入
    for(long long i = 1;i<=n;i++){
        cin>>s[i];//输入字符串。
        if(s[i][0]=='B'&&s[i][s[i].length()-1]=='A'){//判断是否双开。
            ab++;//双开计数
        }else if(s[i][0]=='B'){//判断单开
            b++;//单开计数
        }else if(s[i][s[i].length()-1]=='A'){//判断单开
            a++;//单开计数
        }
        for(long long j = 0;j<s[i].length();j++){
            if(s[i][j]=='A'&&s[i][j+1]=='B'){
                m++;//判断其内部的数量。
            }
        }
    }
    h += m;//算入其内部数量。
   	 if(ab>=1){//判断是否有双开
    	h += (ab-1);//计入双开与双开配对。
    	ab = 1;//将多个双开转为一个双开。
    	if(a>=1){//判断a是否能与最后一个双开配对。 
    	    h++;//数量加一。 
    	    a--;//数量减一 
    	}
    	if(b>=1){//判断是否能与b配对。 
    	    h++;//数量加一。
    	    b--;//数量减一 。 
    	} 
    }
    h += min(a,b);//计算单开的数量。 
    cout<<h;//输出。 
   return 0;
}
```


# 再次警告不要抄题解！！！

---

## 作者：volatile (赞：0)

小蒟蒻第一次写题解，不好请指出。

## 思路1
1. 找每个字符串中的 `AB` 的数量；
2. 暴力枚举两个字符串的第一个字符和最后一个字符能否组成 `AB`；

然后就是劈里啪啦敲代码。

```cpp
#include<iostream>
#include<string>
using namespace std;
struct str {//竟然还用结构体
	string s;
}a[10010];
int main()
{
	int n;
	int sum = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].s;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < a[i].s.size(); j++) {
			if (a[i].s[j] == 'A' && a[i].s[j + 1] == 'B') {
				sum++;
				a[i].s[j] = '0';
				a[i].s[j + 1] = '0';
			}
		}
		if (a[i].s[0] == 'B') {
			for (int j = 1; j <= n; j++) {
				if (j != i) {
					if (a[j].s[a[j].s.size() - 1] == 'A') {
						sum++;
						a[i].s[0] = '0';
						a[j].s[a[j].s.size() - 1] = '0';
						break;
					}
				}
			}
		}
		if (a[i].s[a[i].s.size() - 1] == 'A') {
			for (int j = 1; j <= n; j++) {
				if (j != i) {
					if (a[j].s[0] == 'A') {
						sum++;
						a[i].s[a[i].s.size() - 1] = '0';
						a[j].s[0] = '0';
						break;
					}
				}
			}
		}
	}
	cout << sum;
	return 0;
}
```

结果不出意料的错了，那么就得换一种思路了。

## 思路2
1. 一样，找每个字符串中的 `AB` 的数量，设为 $sum$；
2. 找开头不是 `B` 结尾是 `A` 的字符串数量，设为 $a$；
3. 找开头是 `B` 结尾不是 `A` 的字符串数量，设为 $b$；
4. 找开头是 `B` 结尾是 `A` 的字符串数量，设为 $ab$；
5. 判断：
	- 若 $a$ 大于 $0$ 并且 $b$ 大于 $0$、$ab$ 大于 $0$，那么把 $sum$ 先加上 $ab$ 加 $1$，因为第 $3$ 种字符串相结合再结合一个第 $1$ 和 $2$ 种字符串都会产生 $ab+1$ 个 `AB`。然后 $sum$ 再加上 $\min(a-1,b-1)$，因为要使第 $1$ 种字符串与第 $2$ 种字符串相结合，若一种不够，那么只能取最小值，至于为什么要减 $1$ ，是因为前面说到第 $1$ 或 $2$ 种字符串与第 $3$ 种字符串相结合。
   - 若 $a$ 大于 $0$ 并且 $b$ 大于 $0$ 但是 $ab$ 等于 $0$，那么把 $sum$ 加上 $\min(a,b)$，因为既然没有第 $3$ 种字符串，那么只能第 $1$ 种字符串与第 $2$ 种字符串相结合，并且不减 $1$ 取最小值。
   - 若 $a$ 大于 $0$ 并且 $ab$ 大于 $0$ 但是 $b$ 等于 $0$，那么把 $sum$ 加上 $ab$,因为要把第 $1$ 类字符串与第 $3$ 类字符串相结合，必定会浪费掉 $1$ 个 `AB`，所以不用加 $1$。
   - 若 $b$ 大于 $0$ 并且 $ab$ 大于 $0$ 但是 $a$ 等于 $0$ 与上面相同。
   - 若只有 $ab$ 大于 0，那么 $sum$ 要加上 $ab-1$，因为只有第 $3$ 类字符串相结合，必定会浪费掉 $1$ 个 `AB`。
   
## 理论存在，实践开始

代码

```cpp
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int main()
{
	int n;
	int sum = 0;
	int a = 0, b = 0, ab = 0;
	//  A结尾  B开头   A结尾以及B开头
	string s[10010];
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < s[i].size() - 1; j++) {
			if (s[i][j] == 'A' && s[i][j + 1] == 'B') {
				sum++;
				/*
				s[i][j] = '0';
				s[i][j + 1] = '0';
				不是一次性
				*/
			}
		}
		if (s[i][0] == 'B' && s[i][s[i].size() - 1] != 'A') b++;
		else if (s[i][0] != 'B' && s[i][s[i].size() - 1] == 'A') a++;
		else if (s[i][0] == 'B' && s[i][s[i].size() - 1] == 'A') ab++;
	}
	if (a > 0 && b > 0 && ab > 0) sum += ab + 1 + min(a - 1, b - 1);
	else if (a > 0 && b > 0 && ab == 0) sum += min(a, b);
	else if (a > 0 && b == 0 && ab > 0) sum += ab;
	else if (a == 0 && b > 0 && ab > 0) sum += ab;
	else if (a == 0 && b == 0 && ab > 0) sum += ab - 1;
	cout << sum;
	return 0;
}
```

---

