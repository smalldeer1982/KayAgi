# [NWRRC 2017] Boolean Satisfiability

## 题目描述

布尔可满足性问题（SAT）在计算机科学中被认为是一个非常困难的问题。在这个问题中，给定一个布尔公式，你需要判断该公式的变量是否可以被一致地替换为真或假，使得公式的结果为真。SAT 是已知的 NP 完全问题。此外，即使在 $3-CNF$ 公式（$3-SAT$）的情况下，它也是 NP 完全的。然而，例如，对于 $2-CNF$ 公式（$2-SAT$）的 SAT 问题是在 $P$ 中的。

$#SAT$ 是 SAT 问题的扩展。在这个问题中，你需要检查是否可能，并计算赋值给变量的方式的数量。这个问题即使对于 $2-CNF$ 公式也是已知的 $#P$ 完全问题。我们要求你解决 $#1-DNF-SAT$，这是 $1-DNF$ 公式的 $#SAT$ 问题。

你被给定一个 $1-DNF$ 形式的布尔公式。这意味着它是一个或多个子句的析取（逻辑或），每个子句正好是一个文字，每个文字要么是变量，要么是它的否定（逻辑非）。

形式化地：

$\langle \text{formula} \rangle ::= \langle \text{clause} \rangle \ | \ \langle \text{formula} \rangle \lor \langle \text{clause} \rangle$

$\langle \text{clause} \rangle ::= \langle \text{literal} \rangle$

$\langle \text{literal} \rangle ::= \langle \text{variable} \rangle \ | \ 
eg \langle \text{variable} \rangle$

$\langle \text{variable} \rangle ::= A \ldots Z \ | \ a \ldots z$

你的任务是找到将所有变量替换为真和假（同一变量的所有出现应替换为相同的值）的方法的数量，使得公式的结果为真。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
a
```

### 输出

```
1
```

## 样例 #2

### 输入

```
B|~B
```

### 输出

```
2
```

## 样例 #3

### 输入

```
c|~C
```

### 输出

```
3
```

## 样例 #4

### 输入

```
i|c|p|c
```

### 输出

```
7
```

# 题解

## 作者：A_grasser (赞：3)

- 写完之后发现与一篇原有题解有些雷同，请谅解。

## 题意简化

给定一串布尔表达式，求最终结果。

## 需要注意的地方

1. 题目中有很多细节，需要考虑。

## 解法分析

这是一个技巧题，用构造可能的方案解决。

- 当一个变量 $x$ 既出现了 `|x` 又出现了 `^x`，那么不管 $x$ 取何值都能使最终结果为真，因为 `|x` 与 `^x` 相反，肯定有一个为真，或上之后就恒为真。所以变量 `x` 的取值使最终结果变为真的方案有 $2$ 种。

- 当一个变量 $x$ 只出现了 `|x` 或 `^x`，那么 $x$ 只有取一种值时才为真，所以变量 `x` 的取值使最终结果变为真的方案只有 $1$ 种。

归纳总结：假设表达式有 $n$ 个变量，那么只要表达式中的任意一个变量 $x$ 既出现了 `|x` 又出现了 `^x`，答案就为 $2^{n}$，否则就为 $2^{n}-1$。

想法有了，就开始实现。

先讲解一下每个变量的用途：

```cpp
string s;//输入字符串 
map<char,map<char,int> >mp;
//第一维：符号 (~,|)
//第二维：变量字母
//值域：状态(|x,^x是否存在) 
vector<char>operators;//变量列表 
map<char,int>used;//是否已有此变量（之后讲其作用） 
```

接着开始处理读入。

大致思路：对于第 `s[i]` 字符，如果它是大写字母或小写字母，那么 `s[i-1]` 就是它的操作符，因此要将 `mp[（操作符）][s[i]]=1`，例如操作到 `|x`，那么 `mp[...][s[i]]=1` 就表示变量 $x$ 出现了 `|` 这个操作。

同时，我们还要把这个变量抛到 `operators` 里面，但是，**要注意查重**！因为一个变量可以出现多次，那么变量数 $n$，即 `operators.size()` 就会偏大，所以用 `used` 判重，如果以前未发现此变量就抛到变量列表去（本人犯了这个错误）。

这部分代码就是这样：

```cpp
cin>>s;
for(int i=0;i<s.size();i++){
	if(/*是个变量*/(s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z')){
		if(s[i-1]=='~') mp[1][s[i]]=1;
		else mp[0][s[i]]=1;
		if(used[s[i]]==0){//查重没查到 
			operators.push_back(s[i]);//抛到变量列表 
			used[s[i]]=1;//更新查重状态 
		}
	}
}
```
最后处理答案！

思路：由于答案只有两种情况（上述结论），所以就查是否有变量 $x$ 既出现了 `|x` 又出现了 `^x`，最后输出套结论，就写完了。

```cpp
bool flag=0;//标记 
for(int i=0;i<operators.size();i++){
    if(mp[0][operators[i]]==1 && mp[1][operators[i]]==1){
     	//变量x既出现了|x又出现了^x
        flag=1;
    }
}
long long ans=pow(2,operators.size());//2的 operators.size()次方 
if(flag==0) cout<<ans-1;//没有变量x既出现了|x又出现了^x
else cout<<ans;
```

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过 
#include<bits/stdc++.h>
//万能头文件 
using namespace std;
string s;//输入字符串 
map<char,map<char,int> >mp;
//第一维：符号 (~,|)
//第二维：变量字母
//第三维：状态(|x,^x是否存在) 
vector<char>operators;//变量列表 
map<char,int>used;//是否已有此变量（之后讲其作用） 
int main(){
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(/*是个变量*/(s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z')){
			if(s[i-1]=='~') mp[1][s[i]]=1;
			else mp[0][s[i]]=1;
			if(used[s[i]]==0){//查重没查到 
				operators.push_back(s[i]);//抛到变量列表 
				used[s[i]]=1;//更新查重状态 
			}
		}
	}
	bool flag=0;//标记 
    for(int i=0;i<operators.size();i++){
        if(mp[0][operators[i]]==1 && mp[1][operators[i]]==1){
        	//变量x既出现了|x又出现了^x
            flag=1;
        }
    }
    long long ans=pow(2,operators.size());//2的 operators.size()次方 
    if(flag==0) cout<<ans-1;//没有变量x既出现了|x又出现了^x
    else cout<<ans;
	return 0;
}
```

---

## 作者：GCSG01 (赞：2)

## 题目大意
给定一个由大小写字母（变量），`|` 和 `~` 组成的布尔代数式，变量可以任意赋值为 `True` 或 `False`。求对于给定的变量，有多少种赋值方案使得给定的代数式值为 `True`。

## 思路
一个一个看，首先考虑 `|`，先假设只有 `|`，则当代数式中有一个变量为 `True` 时，代数式的值变为 `True`。因为每一个变量有两种取值，总的方案数便为 $2^n$ 个，但当所有变量都为 `False` 时，代数式值为 `False`，所以方案数要减一，为 $2^n-1$。  
再把 `~x` 加进来，若只有 `~x` 或 `x`，就相当于一个单独变量，与上面的结果相同，若既有 `~x` 又有 `x`，不妨将他们放一起变为 `~x|x`，这个式子的结果恒为 $1$，所以方案数为 $2^n$。

## 实现
用 `map` 记录变量的出现情况，若既有 `x` 又有 `~x`，结果为 $2^n$，否则为 $2^n -1$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
map<char,int>a,b,c;//a：是否有变量x，b：是否有~x，m2：是否有x 
string s;
signed main()
{
	int n=0;
	bool f=false;//是否有x|~x 
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++)
		if((s[i]<='z'&&s[i]>='a')||(s[i]<='Z' && s[i]>='A'))
		{
			if(s[i-1]!='~')c[s[i]]=1;
			else if(s[i-1]=='~')b[s[i]]=1;
			if(a[s[i]]==0)n++,a[s[i]]=1;
			if(c[s[i]]==1&&b[s[i]]==1)
				f=true;
		}
	cout<<(int)pow(2,n)-(!f);//pow的返回有坑，要转int QWQ 
	return 0;
}
```

---

## 作者：Error_Eric (赞：2)

### 题意

给定一个由大小写字母（变量），``|`` 和 ``~`` 组成的布尔代数式，求对于给定的变量，有多少种方案使得给定的代数式值为 ``True`` 。

注：

``a|b`` 表示 $a\vee b$ , 也就是 C++ 中的 ``a || b`` 。

``~a`` 表示 $\neg a$，也就是 C++ 中的 ``(!a)`` 。

变量只有可能由单个字母构成。

### 题解

$n$ 为变量数。

若 $a$ 和 $\neg a$ 同时存在则表达式恒为 True。答案为 $2^n$。

不然只有一种情况为 False，答案为 $2^n-1$

### Code

既然是 ICPC 的题目用 Python 不过分罢。

```python
s=input()
a1="{}";a2="~{}"
ans=0;mn=1
for i in range(26):
    c1=s.count(a1.format(chr(ord('a')+i)))
    c2=s.count(a2.format(chr(ord('a')+i)))
    if c1>0:
        ans=ans+1
    if c1!=c2 and c2!=0:
        mn=0
    c1=s.count(a1.format(chr(ord('A')+i)))
    c2=s.count(a2.format(chr(ord('A')+i)))
    if c1>0:
        ans=ans+1
    if c1!=c2 and c2!=0:
        mn=0
print(2**ans-mn)
```


---

## 作者：Zheng_iii (赞：1)

首先，我们需要明确一个重要的恒等式：

$$x \mid \neg a = 1$$

当 $x = 1$ 时，$x \mid \neg x = 1 \mid 0$ 的结果为 $1$。  
当 $x = 0$ 时，$x \mid \neg x = 0 \mid 1$ 的结果同样为 $1$。  
因此，我们可以得出结论，该式子的结果恒为 $1$。

接下来，我们观察到，当表达式中仅包含 $|$ 运算时，由于每个变量都有两种取值（0 或 1），所以在这种情况下，总的方案数为 $2^n - 1$（$-1$ 是因为我们需要排除所有变量均为 $0$ 的情况）。

当我们引入 $¬$ 运算时，如果 $¬x$ 或 $x$ 单独存在，我们可以将它们视为一个独立的变量。然而，当 $¬x$ 和 $x$ 同时存在时，我们可以通过交换律将它们组合在一起。根据我们之前的发现，这个组合的结果恒为 $1$。

因此，在这种情况下，不存在所有变量均为 $0$ 的情况。由此可得，总的方案数为 $2^n$。

---

## 作者：lichenxi111 (赞：1)

题意挺简洁，就不赘述了
## 思路

我们发现：

- 对于许多变量 ```||``` 的结果为 ```False```，当且仅当所有变量值都为 ```False```。

- 由上述结论，得如果表达式中出现 $a$ 与 $!a$，表达式结果必为 ```True```。

那么，设 $n$ 为表达式中不同变量的个数，则：

- 当表达式中出现 $a$ 与 $!a$，可以随便选，答案即 $2^n$。

- 其他情况就必须有一个变量为 ```True```，减去变量全为 ```False``` 的情况，答案即 $2^n-1$。

注意，可能表达式中没有 ```||```，特判即可。

---

## 作者：chl090410 (赞：1)

## The Solution to P7020 [NWRRC2017] Boolean Satisfiability

### 题目大意

给定一个由大小写字母（变量），```|``` 和 ```~``` 组成的布尔代数式，变量可以任意赋值为 ```True``` 或 ```False```。求对于给定的变量，有多少种赋值方案使得给定的代数式值为 ```True```。

### 分析

设代数式中有 $n$ 个不同的变量。

因为布尔代数式中的逻辑运算符全部为 ```|```，所以代数式中只要有一个变量的值为 ```True``` 时，代数式的值就为 ```True```。

由于变量可以任意赋值为 ```True``` 或 ```False```，每个变量都有两种选择，总共就有 $2^n$ 种不同的赋值方法。

但代数式的值要为 ```True```，所以要将会使代数式的值为 ```False``` 的赋值方法排除掉。

而会使代数式的值为 ```False``` 的赋值方法的数量，我们分两种情况讨论。

- 代数式中既出现了 ```|x``` 又出现了 ```|~x``` 时，```x``` 无论取 ```True``` 还是 ```False``` 时整个代数式的值都为 ```True```，此时不存在会使代数式的值为 ```False``` 的赋值方法，方案数为 $2^n$。

- 代数式中只出现了 ```|x``` 或 ```|~x``` 中的一种时，此时只有一种赋值方法能使该部分的值为 ```True```，若某种赋值方法恰好使代数式每一部分的值都为 ```False```，那么代数式的值也为 ```False```。此时存在 $1$ 种会使代数式的值为 ```False``` 的赋值方法，方案数为 $2^n-1$。

因为大小写字母总共只有 $52$ 个，所以方案数最多只有 $2^{52}$ 个，用 ```long long``` 就能存下，不需要高精度。

综上，若 ```|x``` 与 ```|~x``` 都出现了，方案数就为 $2^n$，否则为 $2^n-1$。

### 下面附上完整代码:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<char,int> m,m1,mm;
string s;
int n=1,ans,k=1; 
signed main(){
	cin>>s;
	int len=s.length();
	for(int i=0;i<len;i++){
		if((s[i]<='z' && s[i]>='a') || (s[i]<='Z' && s[i]>='A')){
			if(s[i-1]=='~'){
				m1[s[i]]=1;
			}
			if(s[i-1]!='~'){
				mm[s[i]]=1;
			}
			if(mm[s[i]]==1 && m1[s[i]]==1){
				k=0;
			}
			if(m[s[i]]==0){
				ans++;
			}
			m[s[i]]=1;
		}
	}
	for(int i=1;i<=ans;i++){
		n*=2;
	}
	cout<<n-k;
	return 0;
}

---

## 作者：Karry5307 (赞：1)

### 题意

给定一个只由 $n$ 个变量以及或，非组成的的布尔表达式，求有多少种变量的取值方法使得该表达式为真。

$\texttt{Data Range:}1\leq n\leq 52$

### 题解

注意到 $p\mid\neg\ p$ 这种表达式是重言式，所以只要在一个表达式中同时出现 $p$ 和 $\neg\ p$，那么无论变量怎么取值都会为真，取值方法为 $2^n$ 种。

如果 $p$ 和 $\neg\ p$ 没有同时出现的话，那么只有一种可能表达式为假，也就是所有的变量都取假。此时使得表达式为真的取值方法为 $2^n-1$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
vector<string>v;
bitset<128>pos,neg;
string s;
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
    	neg=-1;
    	ch=getchar();
	}
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline vector<string> split(string str,char ch)
{
	ll len=str.length();
	string c="";
	vector<string>res;
	for(register int i=0;i<len;i++)
	{
		str[i]==ch?res.emplace_back(c),c="":c+=str[i];
	}
	return c!=""?res.emplace_back(c):(void)1,res;
}
int main()
{
	cin>>s,v=split(s,'|');
	for(auto i:v)
	{
		i[0]=='~'?neg[i[1]]=1:pos[i[0]]=1;
	}
	printf("%lld\n",(1ll<<((neg|pos).count()))-((!!(neg&pos).count())^1));
}
```

---

## 作者：Laoda_Bryant (赞：0)

## 思路
结论题。  
设 $n$ 为表达式中不同的变量数。
### 考虑只有或运算的情况下
* 根据 `||` 运算的定义，只有当**所有**的变量的值均为 `False` 时这个表达式值才为 `False`。
* 因为每个变量都都可取值 `True` 或 `False`，根据乘法原理，将会产生 $2^{n}$ 种组合。但此时要减去值都为 `False` 的方案，得出答案为 $2^{n}-1$。
### 此时考虑包括取反运算的情况
* 当一个变量 $k$ 仅出现了 $!k$ 时，那么此时的取反操作相当于没有。因为总会有一种方案会使 $k$ 的值为 `False`，所以答案还是 $2^{n}-1$，没有变。
* 否则如果同时出现了$x$ 和 $!x$，那么表达式的值恒等为 `True`，答案为 $2^n$。
## AC code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;
int n=0,op=1,p=0;
bool var[114][2];
int main(){
	cin>>s;
	int len=s.size();
	s=" "+s+"IAKIOI";
	for(int i=1;i<=len;i++){
		if(s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z'){
			var[s[i]-'A'+1][(s[i-1]=='~')]=1;
		}
	}
	for(int i=1;i<=114;i++){
		if(var[i][0]||var[i][1]) n++;
		if(var[i][0]&&var[i][1]) op=0;
	}
	cout<<(1ll<<n)-op;
	return 0;
}
```

---

## 作者：seika27 (赞：0)

### 分析
首先明确一个概念 $a|¬a$ 这个表达式恒为真。

接下来简单分类讨论题。

第一种情况只有取反符号，这种情况显然是只有一个取反符号和只有一个变量的。那么我们只有一种选择让表达式为真，那就是让变量值为假。

第二种情况是只存在或符号，那么对于每一个变量，我们都有真和假两个选择，其中总方案数是 $2^n$，注意这里定义 $n$ 为变量数量，在后文中同样，后文不做解释。但是发现如果所有变量都是假，那么表达式值也是假，所以总方案数减一即可。

第三种是既有取反符号又有或符号，但没有形如 $a|¬a$ 这样的表达式，注意这里 $a$ 与 $ ¬a$ 之间就算相隔几个变量也可以看成 $a|¬a$。那么其实这种情况与第二种情况本质上是一样的。

第四种是既有取反符号又有或符号，有形如 $a|¬a$ 这样的表达式，注意这里 $a$ 与 $ ¬a$ 之间就算相隔几个变量也可以看成 $a|¬a$。那么这种情况，无论你的变量取何值，表达式恒为真，则方案数是 $2^n$。

---

## 作者：Amunet (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7020)

## 题意：

给定一个由布尔表达式，求对于给定的变量，有多少种方案使得给定的代数式值为 `True`。

## 思路：

`a|b` 就是 `a||b`。

`~a` 就是 `!a`。

那么当 `a|b` 与 `!a` 同时存在的话恒为 `True`，答案是 $2^n$。

否则仅有一种情况为 `False`，所以方案就是 $2^n-1$。

---

## 作者：joker_opof_qaq (赞：0)

结论数学题目。

如果同时存在 $!a$ 和 $a$ 那么其他的都随便，就是 $2^n$，其他随便选，如果不存在，就选一个让他满足，固定取值，所以答案就是 $2^{n-1}$ 次方。

---

## 作者：Flaw_Owl (赞：0)

# P7020 [NWRRC2017] Boolean Satisfiability 题解

原题链接：[P7020 [NWRRC2017] Boolean Satisfiability](https://www.luogu.com.cn/problem/P7020)

## 题目分析

题目中存在 `|` 和 `~` 两种布尔运算符。实际上可以将 `~` 和它后面的变量看作一个整体条件，我们发现**每个条件都是被 `|` 分开的**。考虑到 `|` 本身是“或”的意思，也就是说，**只要有一个条件为真，最后的语句就为真**。

正向计算比较困难，我们从反向计算：**只有所有条件为假的时候，最后的语句才为假**。考虑到每种条件具有两种状态（真和假），假设有 $n$ 种条件，那么**最后语句为真的情况应为 $2^n - 1$ 种**，即减掉唯一一种全为假的情况。

接下来我们开始计算条件总数。显然的，**字母相同的条件**不应该被重复计数。再考虑 `~` 运算符：显然，**字母不同时**，如 `A | ~B`，这两种条件 **彼此独立**，应该算作两种情况；**字母相同时**，如 `A | ~A`，我们发现 **这是一个永真式**，而它会使得最后的语句**恒为真**，也就是保留所有的状态，不用减掉哪种情况。

也就是说，**条件总数和运算符无关，仅和字母有多少种有关**。

**综上所述**，我们应该关注两个方面：

1. **统计出现过多少种不同的字母**，假设为 $n$。
1. 如果算式中某个**字母和其取反同时存在**，则最后的结果为 $2^n$；反之，最后的结果为 $2^n-1$。

## 程序设计和实现

统计有多少种不同的字母并不困难，我们的重点是**怎么判断字母和其取反是否同时存在**。我们不妨将“取反”和“不取反”分别存储。统计数量时，两者存在一种即计数加一；判断是否满足条件时，两者同时存在则为真。

我考虑使用字符串进行读入，显然过程中我们只要考虑字母和字母前是否有取反操作符。按照思路模拟即可。

## 易错点

这种**统计有多少种**的题往往要考虑数据范围。文中共有大小写共计 $52$ 种字母，极限情况下答案最大能取到 $2^{52}$，虽然不好计算，但我们知道 $2^{32}$ 大概是 $10^{10}$ 的数量级，显然要**用 `long long` 才能进行存储**。

值得注意的是，如果你像我一样将字母种类 `cnt` 设为 `int` 类型（因为考虑到只有 $52$ 种字母），那么最后的表达式 `1 << cnt` 为了保证整体是 `long long` 类型，要**记得写成 `1ll << cnt`**。

## AC 代码

代码如下：

```cpp
#include <iostream>
#include <cctype>

using namespace std;

int cnt;   // 字母的种类数量
bool flag; // 是否满足永真的条件
string s;  // 输入

bool word[2][26], Word[2][26]; // word 存储小写字母，Word 存储大写字母。第一维指示“是否取反”，第二维指示字母种类。

int main()
{
    cin >> s;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            if (s[i - 1] == '~')
                word[0][s[i] - 'a'] = true;
            else
                word[1][s[i] - 'a'] = true;
        }
        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            if (s[i - 1] == '~')
                Word[0][s[i] - 'A'] = true;
            else
                Word[1][s[i] - 'A'] = true;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (word[0][i] || word[1][i])
            cnt++;
        if (Word[0][i] || Word[1][i])
            cnt++;
        if (word[0][i] && word[1][i])
            flag = true;
        if (Word[0][i] && Word[1][i])
            flag = true;
    }
    if (flag)
        printf("%lld\n", 1ll << cnt);
    else
        printf("%lld\n", (1ll << cnt) - 1);
    return 0;
}
```

## 原题翻译

虽然题目已经有了简略版的题意翻译，但鉴于赛场上必须要从原题提取出相关信息，下面也给出原题目的完整翻译（自译，可能有错误之处），并将对解题有帮助的信息进行**加粗**显示。在赛场上只要能提炼出这些加粗的信息既可以解题。

### 题目描述

> Boolean satisfiability problem (SAT) is known to be a very hard problem in computer science. In this problem **you are given a Boolean formula**, and you need to find out if the variables of a given formula can be consistently replaced by the values true or false in such a way that **the formula evaluates to true**. SAT is known to be NP-complete problem. Moreover, it is NP-complete even in case of $3-CNF$ formula $(3-SAT).$ However, for example, SAT problem for $2-CNF$ formulae $(2-SAT)$ is in $P$ .

布尔可满足性问题（SAT）是计算机科学中的一个难题。在这个问题中，**你会得到一个布尔公式**，你需要找出给定的公式中的变量是否可以被替换成 true 或 false，**使得公式计算为 true**。SAT 是一个 NP 完全问题。即使在 3-CNF 公式（3-SAT）的情况下，它也是 NP 完全的。然而，例如，2-CNF 公式（2-SAT）的 SAT问题属于 P 类问题。

> #SAT is the extension of SAT problem. In this problem you need to check if it is possible, and **count the number of ways to assign values to variables**. This problem is known to be #P-complete even for 2-CNF formulae. We ask you to solve #1-DNF-SAT, which is #SAT problem for 1-DNF formulae.

\#SAT 是 SAT 问题的扩展。在这个问题中，您需要判断它是否有解，并且**统计使其有解的变量赋值的组合数量**。即使对于 2-CNF 公式，它也被认为是 \#P 完全问题。我们要求您解决 \#1-DNF-SAT，这是 1-DNF 公式的 \#SAT 问题。

> You are given a Boolean formula in $1-DNF$ form. It means that **it is a disjunction (logical or) of one or more clauses**, **each clause is exactly one literal**, **each literal is either variable or its negation (logical not).**

您将获得一个 1-DNF 形式的布尔公式。这意味着它**是一个或多个子句的析取（逻辑或）**，每**个子句都整好是一个字符**，**每个字符要么是变量，要么是其否定（逻辑非）。**

> Formally:
>
> $〈formula〉 ::= 〈clause〉 | 〈formula〉 ∨ 〈clause〉$
>
> $〈clause〉 ::= 〈literal〉$
>
> $〈literal〉 ::= 〈variable〉 | ¬ 〈variable〉$
>
> $〈variable〉 ::=$ A . . . $Z |$ a . . . $z$

注：

- `<formula>` 表示一个布尔代数式，可以是一个 `<clause>` 或者是 `<formula` 和 `<clause>` 的逻辑或（$\lor$）
- `<clause>` 表示一个子句，它包含一个 `<literal`。
- `<literal>` 表示一个文字，可以是一个 `<variable>` 或者是 `<variable>` 的否定（$\lnot$）
- `<variable>` 表示一个变量，它可以是大写字母或者小写字母。

### 输入格式

> The only line of the input file contains a logical formula in $1-DNF$ form (not longer than $1000$ symbols). **Logical operations are represented by $‘|'$ (disjunction) and $‘ \sim ' (negatio_n).$ The variables are $‘A'$ . . . $‘Z'$ and $‘a'$ . . . $‘z'$ (uppercase and lowercase letters are different variables).** The formula contains neither spaces nor other characters not mentioned in the grammar.

输入仅一行，包含一个 1-DNF 的逻辑公式（不超过 $1000$ 个字符）。**逻辑运算由 `|`（析取）和 `~`（否定）表示。变量为 `A` 到 `Z` 和 `a` 到 `z`（大写字母和小写字母是不同的变量）**。公式中不包含空格或文法中未提及的其他字符。

### 输出格式

> Output a single integer -- the answer for \#SAT problem for the given formula.

输入一个整数——给定公式的 \#SAT 问题的答案。

（其余部分省略）

---

## 作者：落花月朦胧 (赞：0)

设一共有 $n$ 个字母。

发现只有去反和或，考虑从总的 $2^n$ 种情况中减掉不合法的情况，发现假如在这个表达式中如果既有它本身也有它本身取反，无论怎么取都会产生一个 $1$ 即表达式的值一定是 1。

反之，如果没有这个情况，所有的字母都去反的时候算出来表达式是为 $0$ 的，所以这种情况就要减去。

综上，我们可以这样做：

判断是否至少有一个字母的正反都出现了，如果有答案就是 $2^n$，否则答案就是 $2^n - 1$。

``` cpp
// Code by 落花月朦胧. 
// blog (https://www.cnblogs.com/falling-flowers/)
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, r, l) for (int i = (r); i >= (l); i--)
#define sz(x) (int) (x.size())
using namespace std;
using i64 = long long;

// 克鲁鲁 克鲁鲁 克鲁鲁 克鲁鲁 克鲁鲁 克鲁鲁 克鲁鲁 克鲁鲁

constexpr int N = 3E6 + 10;

string s;
map<char, int> mp[2];
int main() {
    cin >> s;
    s = " " + s;

    set<char> ss;
    rep (i, 1, sz(s) - 1) {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')) {
            if (s[i - 1] == '~') {
                mp[1][s[i]] = 1;
            } else {
                mp[0][s[i]] = 1;
            }
            ss.insert(s[i]);
        }
    }

    int f = 0;
    for (auto v : ss) {
        if (mp[0][v] & mp[1][v]) {
            f = 1;
        }
    }
    i64 ans = pow(2, sz(ss));
    printf("%lld\n", ans - !f);

    return 0;
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
只有“或”运算的表达式特点是：只要其中有至少一个为真，那么表达式为真。

同时存在的 ```a``` 和 ```~a``` 必有一个为真。

所以在只有“或”运算的表达式中同时出现 ```a``` 和 ```~a``` 时，表达式必为真。

否则，当变量全为假时，表达式为否。
## 代码
```cpp
#include<bits/stdc++.h>
#include<ctime>
using namespace std;
string s;
bool a[200][2];
bool v[200];
long long g;
int main(){
	cin>>s;
	int k=0;
	for(int i=0;i<s.size();i++){
		if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')){
			v[s[i]]=1;
			a[s[i]][k]=1;
		}//当此时为数字时
		if(s[i]=='|')k=0;//或时k=0
		if(s[i]=='~')k=1;//非时k=1
	}
	long long ans;
	int t=1;//是否存在全员为否的情况
	for(int i=1;i<=190;i++){
		if(v[i]==1)g++;//有一个字符
		if(a[i][1]==1&&a[i][0]==1)t=0;//同一字符有一正一反
	}
	ans=(1ll<<g)-t;//答案
	cout<<ans;
	return 0;
}
```

---

