# [ARC113E] Rvom and Rsrev

## 题目描述

给定只由$a$,$b$组成的一个字符串$S$，你可以做以下操作任意次，使最终的字符串字典序最大。

- 选择$S$的两个相同的字符，将它们之间的字符串翻转，并删掉所选择的两个字符。

比如在$S$中选择两个位置$i,j(s_i=s_j,i<j)$，你可以将字符串$S$替换为$s_1\dots s_{i-1}s_{j-1}s_{j-2}\dots s_{i+2}s_{i+1}s_{j+1}s_{j+2}\dots s_{|S|}$

有$T$组数据

## 说明/提示

$
1\le T\le 2\times 10^5\\
1\le |S_i|(i=1,2\dots ,T)\\
1\le |S_1|+|S_2|+\dots +|S_T|\le 2\times 10^5
$

## 样例 #1

### 输入

```
20
abbaa
babbb
aabbabaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
bbabaaaaabbaababaaabbabbbbbaaaaa
babbbaaaabaababbbabaabaaaaababaa
bbaababababbbaaabaabababaabbabab
abaabbabaabaaaaabaaaabbaabaaaaab
aabababbabbabbabbaaaabbabbbabaab
aabababbabbbbaaaabbaaaaabbaaaabb
abbbbaabaaabababaaaababababbaabb
aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbb
aaaaaaaaaabbbbbbbbbbbbbbbbbbbbbb
abababaaababaaabbbbbaaaaaaabbbbb
aabbaaaaababaabbbbbbbbbaabaaabbb
babababbababbbababbbbbababbbabbb
bbbbababbababbbabababbabbabbbbbb
aaaaaaaaaaaaaaaaababababbbabbbbb
aabababbabbabababababababbbbabbb```

### 输出

```
bba
bba
bbba
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbaaaaaaaa
bbbbbbbbbbbbbaaaaaaa
bbbbbbbbbbbbbbbb
bbbbbbbbbb
bbbbbbbbbbbbbbbbab
bbbbbbbbbbbbbb
bbbbbbbbbbbbbabb
abbbbbbbbb
bbbbbbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbaaaaaaaaa
bbbbbbbbbbbbbbbaaaaa
bbbbbbbbbbbbbbbbbbbbbb
bbbbbbbbbbbbbbbbbbbbba
bbbbbbbbbaaaaaaaaaaaaaaa
bbbbbbbbbbbbbbbbba```

# 题解

## 作者：ran_qwq (赞：10)

~~警告：前方有巨量分讨，请谨慎进入！~~

遇到这种抽象题，先观察一下样例，发现答案无非就三种类型：

1. 全 $\texttt{a}$ 或全 $\texttt{b}$。

1. 前面一大串 $\texttt{b}$，后面一大串 $\texttt{a}$。这种情况下，$\texttt{b}$ 个数越多，字典序越大；$\texttt{b}$ 个数相同，$\texttt{a}$ 个数越多，字典序越大。

1. 一串 $\texttt{b}$ 中夹一个 $\texttt{a}$。

分七类讨论（实际上也许不用那么多）：

### 一、$S=\texttt{aaaa\dots a}$ 或 $S=\texttt{bbbb\dots b}$。

全部都是同一个字符，进行操作反而会让长度变小，即字典序变小。所以这时候我们最好不操作，原样输出。

### 二、不满足前面所有条件，但 $S$ 以 $\texttt{a}$ 结尾。

这种情况对应答案的第 $2$ 类，考虑如何把 $\texttt{a}$ 全搞到最后。

注意到如果操作的子串形如 $\texttt{aaa\dots abbb\dots ba}$，则操作后中间的 $\texttt{a}$ 连续段和 $\texttt{b}$ 连续段顺序颠倒，而左右的 $\texttt{a}$ 被删掉。我们可以利用这个性质把 $\texttt{a}$ 慢慢往后挪，最终把它们搞到最后。

- 对于长度 $\ge2$ 的 $\texttt{a}$ 连续段，把它左右两边的 $\texttt{a}$ 删掉可以把整段往后挪，也就是连续段个数少一个。

- 对于长度为 $1$ 的 $\texttt{a}$ 连续段，可以和前后的 $\texttt{a}$ 一起被删掉，连续段个数也少一个。

如果按这样算出来的最少删除个数为奇数，而删除是两个两个删的，这时候就要用字符串末尾的 $\texttt{a}$ 连续段中最左的 $\texttt{a}$ 来补充。

这样操作，$\texttt{b}$ 的个数不会改变。而设长度为 $1$ 的 $\texttt{a}$ 连续段有 $a_1$ 个，长度 $\ge2$ 的 $\texttt{a}$ 连续段有 $a_2$ 个（末尾连续段均不算）。则当 $a_1+2a_2$ 为偶数时，最少需要删除 $a_1+2a_2$ 个；当 $a_1+2a_2$ 为奇数时，最少需要删除 $a_1+2a_2+1$ 个。

### 三、不满足前面所有条件，但 $\texttt{a}$ 的总个数为偶数

这种情况也对应答案的第 $2$ 类。

还是考虑如何不删除 $\texttt{b}$，因为 $\texttt{b}$ 个数是第一关键字。

最后一个字符是 $\texttt{b}$，所以不删除最后的 $\texttt{b}$ 的话无论如何 $\texttt{a}$ 都不可能在最后。

但此时 $\texttt{a}$ 是可以两两配对的！可以操作相邻的 $\texttt{a}$，这样 $\texttt{b}$ 个数不会改变。

### 四、不满足前面所有条件，但字符串形如 $\texttt{aaa\dots abbb\dots b}$。

来到这一步，此时 $\texttt{a}$ 总个数必为奇数。

而且这种情况下，$\texttt{a}$ 个数越多，字典序越大；$\texttt{a}$ 个数相同，$\texttt{b}$ 个数越多，字典序越大。

所以我们尽量把 $\texttt{a}$ 删完，只留下一个 $\texttt{a}$，然后后面的 $\texttt{b}$ 我们不动它。

### 五、不满足前面所有条件，但字符串以 $\texttt{ab}$ 结尾。

此时 $\texttt{a}$ 总个数必为奇数。

所以抛开末尾的 $\texttt{ab}$ 不谈，前面的 $\texttt{a}$ 有偶数个，可以像类型三一样匹配。

答案的 $\texttt{b}$ 的个数没有改变，只是把一个 $\texttt{a}$ 插在倒数第二位而已。

### 六、不满足前面所有条件，但字符串以 $\texttt{abb}$ 结尾。

与类型五类似，此时 $\texttt{a}$ 总个数必为奇数。

所以抛开末尾的 $\texttt{abb}$ 不谈，前面的 $\texttt{a}$ 有偶数个，可以像类型三一样匹配。

答案的 $\texttt{b}$ 的个数没有改变，只是把一个 $\texttt{a}$ 插在倒数第三位而已。

### 七、其它情况

之所以把类型五、六单独列出来，是因为它们不用删 $\texttt{b}$，而类型七要。

容易发现，不满足前四个类型在不删 $\texttt{b}$ 的情况下的答案形如 $\texttt{bbb\dots babbb\dots b}$。

这样的话有一个漏洞：当最后一个 $\texttt{a}$ 较小时优，但较大时不一定优。

所以我们尽量通过删除一些 $\texttt{b}$ 的方式来让答案前面的 $\texttt{b}$ 段尽量长。

现在把前面的 $\texttt{b}$ 段变长一点点，无论后面的怎么变化也是值的。

我们回过头来对类型二进行一些拓展，使最少删除个数变少。

可以将某个右边挨着 $\texttt{a}$ 的 $\texttt{b}$ 和末尾的 $\texttt{b}$ 删掉，把两个 $\texttt{b}$ 中间的字符反转。显然现在右边挨着 $\texttt{a}$ 的 $\texttt{b}$ 是一定存在的。

操作后末尾的字符变成 $\texttt{a}$（不懂的自行脑补），可以进行类型二的操作。

但这样一定更优吗？而且，选哪个 $\texttt{b}$？

因为类型二的末尾 $\texttt{a}$ 连续段是不用算的，而我们进行操作将其中某段变为末尾连续段，所以最少删除个数会变少，末尾的 $\texttt{a}$ 会变多。

选 $\texttt{b}$ 就选后面 $\texttt{a}$ 连续段的最少删除个数最多的那个，其实一个连续段最多是 $2$。

有人会问：如果前面 $\texttt{a}$ 个数是奇数的话不会拿末尾的 $\texttt{a}$ 来补充吗？

答：是的，但是一个连续段最少删除个数最少是 $1$，而补充也就补充 $1$ 个，所以这样不会更劣。

这样，设 $\texttt{b}$ 的总个数为 $b$，则前面有 $b-2$ 个 $\texttt{b}$，比类型五、六以此类推的要多。

到这里，相信你也明白为什么要这里单独分出两个类型，而不是一个、三个了吧。

```cpp
void QwQ()
{
	string s;cin>>s;int n=s.size(),A=0,B=0,cnt=0,sum=0,num=0,fst=0,mx=0;
	for(int i=0;i<n;i++) A+=s[i]=='a',B+=s[i]=='b';
	for(int i=0;i<A;i++) num+=s[i]=='a';
	if(!A||!B) {cout<<s<<"\n";return;}
	if(s[n-1]=='a')
	{
		for(int i=0;i<n;i++)
			if(s[i]=='a') cnt++;
			else if(i&&s[i-1]=='a') sum+=min(cnt,2),cnt=0;
		for(int i=B;i--;) pc('b');
		for(int i=A-sum-(sum&1);i--;) pc('a');
		puts("");return;
	}
	if(!(A&1))
	{
		for(int i=B;i--;) pc('b');
		puts("");return;
	}
	if(num==A)
	{
		pc('a');
		for(int i=B;i--;) pc('b');
		puts("");return;
	}
	if(s[n-2]=='a')
	{
		for(int i=B-1;i--;) pc('b');
		pc('a'),puts("b");return;
	}
	if(s[n-3]=='a')
	{
		for(int i=B-2;i--;) pc('b');
		pc('a'),pc('b'),puts("b");return;
	}
	cnt=sum=0;
	for(int i=0;i<n;i++)
		if(s[i]=='b') {fst=i;break;}
	for(int i=0;i<n;i++)
		if(s[i]=='a') cnt++;
		else if(i&&s[i-1]=='a')
		{
			if(fst<i) mx=max(mx,min(cnt,2));
			sum+=min(cnt,2),cnt=0;
		}
	for(int i=B-2;i--;) pc('b');
	for(int i=A+mx-sum-(sum-mx&1);i--;) pc('a');
	puts("");
}
```

---

## 作者：_maojun_ (赞：5)

大分讨题，想清楚所有情况后还是比较好实现的。

---

首先全 `a` 全 `b` 或前面一段 `a` 后面一段 `b` 特判掉，然后对结尾字符分讨。

**若结尾为 `a`。**

此时把 `a` 两两全删除后只会剩下不超过 $1$ 个 `a`，且若有一定可以在最后。

也就是答案一定形如 `bb...baa...a`，这里 `b` 的数量就是原串中 `b` 的数量，所以让字典序尽量大就需要我们保留尽量多的 `a`。

每次删除两个 `a` 可以用减少两个 `a` 的代价把一段 `a` 翻到最后。

于是我们考虑这样的策略：每次选择一个长度大于 $2$ 的 `a` 的极长连续段，对它的第一个与最后一个 `b` 之后的 `a` 操作，这样就能把尽量多的 `a` 翻到后面。

而剩下夹在 `b` 中间的需要删除，这里要判断一下奇偶性，如果剩下了奇数个就要把结尾的串删掉一个。

以样例第六个串为例（`-` 为已删除字符）：

`bbabaaaaabbaababaaabbabbbbbaaaaa`

`bbab-bbbbbabbaaababaabbaaaa-aaaa`

`bbab-bbbbbabb-bbaababaa-aaa-aaaa`

`bb-b-bbbbb-bb-bbaababaa-aaa-aaaa`

`bb-b-bbbbb-bb-bb--babaa-aaa-aaaa`

`bb-b-bbbbb-bb-bb--b-b-a-aaa-aaaa`

```cpp
inline void A_end(){
	int sum=0,cb=0,del=0;
	for(int i=1,c=0;i<=n;i++){
		if(s[i]=='a')c++;
		else{int x=max(0,c-2);sum+=x;del+=c-x;c=0;cb++;}	// 找 a 的极长连续段
		if(i==n)sum+=c;
	}
	wb(cb);wa(sum-(del&1));									// 调整奇偶性
}
```

**若结尾为 `b`。**

若 `a` 的数量为偶数，则把 `a` 全部删掉一定不劣，因为 `a` 只要不在最后，存在就是减小字典序。

若 `a` 的数量为奇数，也就是最后不论如何一定会剩下至少一个，那么可以通过反转一个两端为 `b` 的串把它丢到最后，以此增大字典序。

如第二个样例：`babbb` $\to$ `bba`。

那么我们考虑这样做：先忽视最后的一段 `b`，然后用以 `a` 结尾的方法把所有 `a` 翻到尽可能后面，最后在通过删 `b` 翻到结尾。

但我们发现无脑删 `b` 不一定优，比如：`bab` $\to$ `a`，`babb` $\to$ `ba`，即若在 `a` 后的 `b` 不超过 $2$ 个就不应该换，此时策略是 `a` 能删全删，留下最靠后的一个。

以上就是我赛场上的思路，高高兴兴写完后发现错了 $11$ 个点，来看这个数据：

`baaabababbb`

我的做法这样操作：

`baaabababbb`

`b-babaa-bbb`

`b-b-b-a-bbb`

`b-b---b-ba-`

只保留了 $1$ 个 `a`。

但其实可以这样：

`baaabababbb`

`baaab-b-bbb`

`-bbbb-a-aa-`

保留了 $3$ 个 `a`。

也就是说，我们可以删掉最后的若干小块来保留一个大块。实现上记录一个最大撤消价值，最后加上这个价值即可。注意保留的前提是不在最开头，若 `a` 在最开头就要不惜一切代价消掉（由于除了这个连通块一定还有别的 `a` 所以一定是可以消掉的）。

还有注意要在撤消代价之后再判奇偶性，这里因为 `a` 的数量为奇数，所以最终也只应有奇数个 `a`。若最后算出来有偶数个 `a`，一定是某次只删了一个，给答案减一就好了。

```cpp
inline void B_end(){
	int sum=0,del=0,mx=0;bool cb=false;
	for(int i=1,c=0;i<=n;i++){
		if(s[i]=='a')c++;
		if(s[i]=='b'||i==n){
			int x=max(0,c-2);sum+=x;
			if(cb)mx=max(mx,c-x);							// 更新最大撤消获利
			c=0;cb=true;
		}
	}
	int ca=sum+mx;wa(ca-!(ca&1));							// 调整奇偶性
}
```

分讨题，最后还是放一下完整代码吧。

```cpp
#define pc putchar

inline void wa(int x){while(x--)pc('a');}
inline void wb(int x){while(x--)pc('b');}
const int N=2e5+5;
int n;char s[N],t[N];

inline void A_end();
inline void B_end();
inline void solve(){
	scanf("%s",s+1);n=strlen(s+1);
	int ca=0;for(int i=1;i<=n;i++)ca+=s[i]=='a';
	int cb=0;for(int i=1;i<=n;i++)cb+=s[i]=='b';
	if(ca==n)return wa(n);if(cb==n)return wb(n);        // 特判全 a 全 b
	bool fl=true;for(int i=1;i<=ca&&fl;i++)fl&=s[i]=='a';
	if(fl){wa(ca&1);return wb(cb);}						// 特判 aa..abb...b
	if(s[n]=='a')return A_end();    					// 以 a 结尾
	if(!(ca&1))return wb(cb);       					// 以 b 结尾，偶数个 a
	if(s[n-1]=='a'){wb(cb-1);pc('a');pc('b');return;}   // 判最后的 b 不足 3 个
	wb(cb-2);
	if(s[n-2]=='a'){pc('a');pc('b');pc('b');return;}
	B_end();                        					// 以 b 结尾，奇数个 a，删 b 翻转
}
int main(){
	int T;scanf("%d",&T);
	while(T--){solve();pc(0xa);}
	return 0;
}
```

---

## 作者：dengchengyu (赞：2)

这是一个分类讨论题。

**题意**

一个只含有 `a` 和 `b` 的字符串，可以任意次选择两个相同字符，删掉它们并且翻转它们之间的区间，最终使字典序最大。

---

首先观察样例发现，答案大致有以下几种：

* 全为 `a` 或全为 `b`。
* 形如 `b...ba...a`，即前面一串 `b`，后面一串 `a`。
* 形如 `b...bab...b`，即中间夹着一个 `a`。

---

所给串全为 `a` 或 `b` 时，

此时删去任意字符显然不优，于是答案就是原串。

---

由于要字典序最大，所以我们希望前面连续的 `b` 越多越好。

所以我们优先考虑能否让所有 `b` 都移到前面且不被删除。

**当以 `a` 结尾时**

这种情况答案应该是前面一串 `b`，后面一串 `a`。

考虑 `b` 被夹在中间时，形如 `...aaabbbaaa`。

此时我们可以删掉前面这一串 `a` 的开头和后面这一串 `a` 的开头。

即删掉括号中的：`...(a)aabbb(a)aa`。

变为  `..._bbbaa_aa`，`_` 表示被删掉后的空位。

这样就实现了：对于除最后一串的每一串 `a`，都通过删掉两个字符 `a`，把它移到后面。

但是我们发现，长度为 1 的串 `a` 可以两两删除，从而减少删除次数，以最优化答案。

所以：

设 $s_1$ 为除最后一串外，长度为 1 的连续串 `a` 的个数，

设 $s_2$ 为除最后一串外，长度大于 1 的连续串 `a` 的个数。

删掉个数为为 $2s_2+2\lceil\frac{S_1}{2}\rceil$，

即**最终答案**为：

（设 $t_a$ 为 `a` 的个数，$t_b$ 为 `b` 的个数） 

$t_b$ 个 `b`，加上 $(t_a -2s_2-2\lceil\frac{S_1}{2}\rceil )$ 个 `a`，

---

**当以 `b` 结尾时**

还是考虑最好情况让 `b` 最多，则显然此时前面的 `a` 要全部删完。

**`b` 结尾，`a` 有偶数个时**

则 `a` 可以两两全部删完。

**`b` 结尾，`a` 有奇数个时**

形如 `...bbbaaabbb`，

如果我们把 `a` 全删完，而不删 `b` 就得到 `...bbbabbb`，最后剩下了一个 `a`，

然而这样是不优的。

我们可以选择一串连续的 `a` 的前一个字符 `b` 和整个串的最后一个 `b` 而让答案更优：

`...bb(b)aaabb(b)`

`...bb_bbaaa_`

这样就实现了删掉两个 `b` 使答案更优。

我们发现此时就变成了 `a` 结尾的情况。

接下来就要考虑删掉哪串 `a` 的前一个 `b`，因为我们删掉后会使这串 `a` 移到最后，从而不参与个数统计（上文中的 $s_1$ 和 $s_2$ 是除最后一串外的）。

通过这个式子 $2s_2+2\lceil\frac{S_1}{2}\rceil$，发现我们要**优先选择长度大于 1 的 `a` 串**，使 $s_2$ 减一，才能使最后 `a` 尽可能多。

选不了就再选长度等于 1 的 `a` 串，即使 $s_1$ 减一。

若原串**以 `a` 开头**，那么这串 `a` 是**不能选**的，因为它前面没有字符 `b` 了。

设 $S=2(s_2-1)+2\lceil\frac{S_1}{2}\rceil\ or\ 2s_2+2\lceil\frac{S_1-1}{2}\rceil$，具体减在哪里如上。

则**最终答案**为 ：

$( t_b -2 )$ 个 `b`，加上 $( t_a -S )$ 个 `a`。

---

**`b` 结尾，`a` 有奇数个时的特判**

`...ab` 和 `...abb` 时，即结尾为 1 个或 2 个 `b`，此时我们直接把前面的 `a` 全删完，保留最后一个 `a`，易得这样最优。

`aa...aabb...bb` 此时也是把前面的 `a` 全部删完，保留最后一个 `a`。

---

[代码](https://atcoder.jp/contests/arc113/submissions/53451918)

---

## 作者：WRuperD (赞：2)

### 前言
今天早上 div2 模拟赛的最后一道题。本来想着早点 AK 走了，没想到看到了这道名字叫做

![](https://wruperd.github.io/post-images/1706603594368.png)

的题目。一打开一股浓浓的 ARC 大分讨的感觉瞬间溢出屏幕。

### 题解
字典序，首先我们要意识到所有的 B 要尽量在前面，而且 B 要尽量少删。然后我们开始大力手玩、分讨。

#### S 的末尾为A
对于这种情况，我们可以做到不删 B。我们考虑每次选择一个极长的 A 的连续段的段首与 S 的末尾。这样子我们发现只要这个连续段的长度大于等于二那么 S 的末尾还是 A，且其它 A 都被仍到末尾了。对于所有 A 的长度为 1 的连续段我们可以两个两个和起来删。这样子做容易发现就是最优的了。设 A 长度大于 1 的连续段个数为 $x$，长度为一的连续段个数为 $y$ 那么有操作次数为 $x + \lceil {y \over 2} \rceil$。

#### S 的末尾不为A
先考虑一些不用删 B 的情况。

##### S 中 A 的个数为偶数
把 A 全部删掉！显然这样子是最大的了。

##### S 中 A全部都在开头
没得玩了，把 A 尽可能删掉吧！

##### S 中最后一个 A 在 $n - 1$ 或 $n - 2$ 位。
首先前面已经考虑的 A 的个数为偶数的情况了。所以我们可以把除了那个 A 之外的 A 全部删光。经过一点思考发现这样子是最优的。

好吧，现在我们貌似必须要开始删 B 了。

考虑删一个 A 连续段之前的一个 B 和末尾的那个 B 会发生什么，发现变成了 S 的末尾为 A 的情况了！怎么删最优？显然我们挪一个长度大于等于 2 的 A 连续段到末尾最好了。如此操作，我们就在最多删两个 B 的情况下严格的做完了这道题。![/px](https://cdn.luogu.com.cn/upload/pic/62246.png)


[code](https://atcoder.jp/contests/arc113/submissions/49809035)



---

## 作者：Sampson_YW (赞：2)

巨大分类讨论题。

观察样例，发现答案有这几种情况：全 a/b；前面若干个 b 后面若干个 a；b 中间夹一个 a。

我们要考虑的方向是：优先让尽量多的 b 到前面；如果能够让所有 b 到前面，那么再考虑少删 a，否则要考虑多删 a 让后面的 b 往前走。

先判掉全 a/b 的情况。

1. $s$ 末尾是 a。

显然，可以不删 b 就让所有的 b 到最前面：每次选择一个 a 段的开头，和末尾段的开头做一次操作就可以减少非末尾 a 段的数量。

因此，我们要最小化操作次数。显然有一个宽的上界就是非末尾的 a 段数量。

但是如果有长度为一的 a 段，我们让它们互相抵消会更优。设有 $x$ 个长度为一的 a 段，$y$ 个长度大于一的 a 段，那么操作次数为 $\lceil\frac{x}{2}\rceil+y$。

2. $s$ 末尾是 b。

如果除开末尾段的 b，前面只有 a 了，那么肯定是不能把 b 放到前面的。不能删 b，直接删尽量多的 a。

如果末尾段的长度 $\leq 2$，那么对这一段进行一次操作不会让前面的 b 变多，而且会让整个串的字典序最小。因此这种情况也是不删 b，删尽量多的 a。

如果 a 的数量为偶数，那么也是可以不删 b 就让所有 b 到前面的。

否则就要进行一次操作让 $s$ 的末尾变成 a。可以从第一个 b 段到末尾中任选一段丢到末尾。根据末尾是 a 的情况来看，如果有长度大于一的 a 段，那肯定是将它丢到末尾才可能会让操作次数变少（因为保留长度等于一的段在非末尾）。然后就变成了末尾是 a 的情况。

[code](https://atcoder.jp/contests/arc113/submissions/48438509)

---

