# [PA 2016] 运算 / Jedynki

## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R2 Jedynki [B] (JED)。$\texttt{1s,256M}$。


## 题目描述


给定正整数 $k$。构造一个只包含 $\texttt{1},\texttt{+},\texttt{*},\texttt{(},\texttt{)}$ 的**合法**表达式，满足：
- 不存在两个相邻的 $1$；
- $1$ 的数量最多为 $100$；
- 表达式运算结果为 $k$。

输出你构造的表达式，或者判断无解。

我们给定合法表达式的形式化定义：

- $\texttt{1}$ 是合法表达式。
- 若 $\texttt{a},\texttt{b}$ 是合法表达式，则 $\texttt{a+b},\texttt{a*b},\texttt{(a+b)},\texttt{(a*b)}$ 都是合法表达式。

## 说明/提示


- $1\le T\le 100$；
- $1\le k\le 10^9$。

## 样例 #1

### 输入

```
2
6
10```

### 输出

```
(1+1)*(1+1+1)
1+1+1+1+1+1+1+1+1+1```

# 题解

## 作者：Luogu_916767 (赞：5)

[In Luogu](https://www.luogu.com.cn/problem/P11605)

### 题目大意
多组数据，每组数据一个 $k$ 要求构造一个只包含 $\texttt{1},\texttt{+},\texttt{*},\texttt{(},\texttt{)}$ 的**合法**表达式，满足：
- 不存在两个相邻的 $1$；
- $1$ 的数量最多为 $100$；
- 表达式运算结果为 $k$。

### 思路分析
很容易想到用类似十进制转二进制的方法来构造。

若 $k$ 是奇数，则将 $k$ 变成 $(1+(1+1)*(\left \lfloor \frac{k}{2}  \right \rfloor ))$ 的形式。

若 $k$ 是偶数，则将 $k$ 变成 $((1+1)*(\frac{k}{2}))$ 的形式。

按照这种方法，直到将 $k$ 变成 $1$ 为止。

这种方式构造的表达式中 $1$ 的个数大约为 $2 \times \log_{2}{k} $，针对题目的数据来说是绝对不会超过 $100$ 的，所以不用特判。

### Code

```cpp
#include<iostream>

using namespace std;

int t;
int n;
string ans;

void work(int n){
    if(n == 1){
        ans += "1";
        return ;
    }
    if(n % 2 == 0){
        ans += "((1+1)*";
        work(n/2);
        ans += ")";
    }else{
        ans += "(1+(1+1)*";
        work(n/2);
        ans += ")";
    }
}

int main(){
    cin>>t;
    while(t -- ){
        cin>>n;
        ans = "";
        work(n);
        cout<<ans<<"\n";
    }
}
```

---

## 作者：Tachibana27 (赞：4)

如果 $1$ 的个数是足够的，那么直接用 $1$ 加出来就可以了。但是我们只有 $100$ 个 $1$，所以贪心地想：尽可能的多乘，减少使用 $1$。

一开始的思路是分解质因数，但是发现如果是一个大质数那 $1$ 是不够用的。所以直接这么做行不通。

那么进一步的，质数如何变成合数呢？容易发现大质数一定是奇数，减一后就变成偶数了。此时可以用 `*(1+1)` 表示出来。

递归处理即可，注意一下优先级的问题。

所有数都可以用这种方式表示出来，且这样最劣使用 $3\log(x)$ 个 $1$，不到 $100$，所以不存在无解。

```cpp
void sol(int x){
	if(x==1){//边界
		std::cout<<1;
		return;
	}
	if(x bitand 1){//如果为奇数
		std::cout<<"(";
		sol(x-1);//减一变成偶数
		std::cout<<"+1)";//原基础上 +1
		return;
	}
	sol(x>>1);//偶数除以二
	std::cout<<"*(1+1)";//乘二即可
	return;
}
```

---

## 作者：违规用户名^3Zj=Oha (赞：1)

## 一、思路分析
一开始我先想到的就是将 $k$ 进行分解因数，然后把每个因数表示成 $(1+1+...)$ 的形式，如下图就是第一版。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,k;
vector<int> q;
void dfs(){
	while(k>1){
		for(int i=2;i<=k;i++){
			while(k%i==0){
				k/=i;
				q.push_back(i);
			}
		}
	}
}
signed main(){
	cin>>T;
	while(T--){
		cin>>k;
		q.clear();
		dfs();
		if(q.size()==1){
			for(int i=1;i<q[0];i++) cout<<1<<"+";
			cout<<1<<endl;
		}
		else{
			for(int i=0;i<q.size();i++){
				cout<<"(";
				for(int j=1;j<q[i];j++) cout<<1<<"+";
				cout<<1<<")";
				if(i==q.size()-1) break;
				cout<<"*";
			}
		}
		cout<<endl;
	}
	return 0;
}
```

## 二、优化+代码实现
然后直接爆炸，那么我们思考如何进行优化？

很明显，我们拆分出来的因数进行表示后 $1$ 的数量可能多余 $100$，那么我们就想到了递归，把拆分出来的因数继续拆分，直到有合法的表示为止，或拆到最后也没有合法表示.


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,k;
unordered_map<int, string> ans;
string dfs(int k){
    if(k==1) return "1";
    if(ans.find(k)!=ans.end()) return ans[k];
    for(int i=2;i*i<=k;i++){
        if(k%i==0){
            string v=dfs(i),u=dfs(k/i);
            if(v!="NIE"&&u!="NIE"){
                ans[k]="("+v+"*"+u+")";
                return "("+v+"*"+u+")";
            }
        }
    }
    for(int i=1;i<=k/2;i++){
        string v=dfs(i),u=dfs(k-i);
        if(v!="NIE"&&u!="NIE"){
            ans[k]="("+v+"+"+u+")";
            return "("+v+"+"+u+")";
        }
    }
    ans[k]="NIE";
    return ans[k];
}
signed main(){
    cin>>T;
    while(T--){
        cin>>k;
        cout<<dfs(k)<<endl;
    }
    return 0;
}
```
然后就 AC 辣，美中不足的一点是这个代码不管什么情况下总会在表达式最外面套一层括号，如下形式 $(....)$。

---

## 作者：lzx111218 (赞：1)

# P11605 [PA 2016] 运算 / Jedynki
[题目传送门](https://www.luogu.com.cn/problem/P11605)
## 思路
首先，考虑如何通过乘法和加法将 $1$ 构造为更大的数。若 $k$ 可以表示为两个数的乘积 $i×j$，如果 $k$ 不能拆成两个数的乘积，则考虑构造表达式 $1 + (k-1)$，即通过加法构造。

**递归分解：**

对于每个 $k$，尝试将其分解为因数，每次分解成乘积形式 $a×b$。
如果找到了一个有效的分解，则返回该分解。
如果没有找到有效的因数分解，则尝试将 $k$ 写为 $1 + (k-1)$ 的形式。

**边界特判：**

如果 $k=1$，直接返回 $1$。
如果在递归过程中找不到有效表达式，那就说明无解，返回 `NIE`。

**时间复杂度为** $O(\sqrt k)$。

**空间复杂度为** $O(\log k + k)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace fastIO{char *p1,*p2,buf[100000];
	#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
	inline void read(int&n){int x=0,f=1;char ch=nc();while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=nc();}while(ch>=48&&ch<=57){x=(x<<3)+(x<<1)+(ch^48),ch=nc();}n=x*f;}
	inline void read(string&s){char ch=nc();while(ch==' '||ch=='\n'){ch=nc();}while(ch!=' '&&ch!='\n'){s+=ch,ch=nc();}}
	inline void read(char&ch){ch=nc();while(ch==' '||ch=='\n'){ch=nc();}}
	inline void write(int x){if(x<0){putchar('-'),x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');return;}
	inline void write(const string&s){for(register int i=0;i<(int)s.size();i++){putchar(s[i]);}}
	inline void write(const char&c){putchar(c);}
}using namespace fastIO;
string Jedynki(int k) {
    if (k == 1)  
        return "1";
    for (int i = (int)sqrt(k); i >= 2; --i) {
        if (k % i == 0) {
            string l = Jedynki(i), r = Jedynki(k / i);
            if (l != "NIE" && r != "NIE") {
                return "(" + l + "*" + r + ")";
            }
        }
    }
    string res = Jedynki(k - 1);
    if (res != "NIE") {
        return "(1+" + res + ")";
    }
    return "NIE";  
}

signed main(){
    int T;
    read(T);
    while(T--){
        int k;
        read(k);
        write(Jedynki(k));
        putchar('\n'); 
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 思路

注意到 $k$ 小于 $10 ^ {9}$，那么 $100$ 个 $1$ 一定可以达到 $10 ^ {9}$ 以上的数，故不用判断上界。

那么很容易想到直接 dfs。每次搜索考虑加 $1$ 与乘 $x$ 操作，加 $1$ 就是直接加，乘 $x$ 操作可以由另外的 dfs 得来，然后判断当前值乘上 $x$ 是否超过 $k$，超过就终止（再加或乘都不行了），没超就继续考虑加或乘，直到刚好和 $k$ 相等，此时如果使用 $1$ 的个数没有超过 $100$，就能直接输出结果了。

实现的时候要记下用过的操作，以便达到答案时输出（记得回溯）。

## 细节

没什么需要特别注意的细节，写的时候注意一下细节就好了。

---

## 作者：lzt415 (赞：0)

## 题目大意
请用 ```1```，```+```，```*```，```(```，```)``` 五种字符组成一个表达式，使其结果为 $k$。

并且 $1$ 不能连用，所以 $11$ 一类的数不能存在。
## 思路
首先，由于我们十分的拮据，穷困潦倒，家徒四壁，只有 $100$ 个 $1$，所以如果一个一个加起来，很容易出现 $1$ 不够用的情况。

所以我们会想办法让每个 $1$ 更有用，也就是说可以用像 ```*(1+1)``` 这种方法来达到 $k$ 这个值。

而这样，每次变成原来的两倍，也就用到了 $\log_{2}k$ 级别的个数的 $1$，不会出现不够用的情况。
## CODE

```cpp
void solve(int k)
{
    if(k == 1)
    {
        ans += "1";
        return ;
    }
    if(k % 2 == 0)
	{
        ans += "((1+1)*";
        work(k/2);
        ans += ")";
    }
	else
	{ 
        ans += "(1+(1+1)*";
        work(k/2);
        ans += ")";
    }
}
```
## 后记
小小说明一下，代码中的 ```k``` 指还需多少值达到目标数字，调用时直接写个 ```solve(k)``` 即可，并且 ```ans``` 是一个字符串类型，因为这样方便直接加上另一个字符串。

---

## 作者：Billhqh9 (赞：0)

在看到这题时，我们先明确一点：为了少用 $1$，要多用乘法。

首先想到的肯定是把 $k$ 的所有质因子用若干个 $1$ 的加和表示出来后相乘。

但这个思想存在一个问题：当一个数为质数时，按照题中的方法分解，并不只能分解成若干个 $1$ 的和的形式。比如，$7=1+6$，而 $6=2*3=(1+1)*(1+1+1)$，所以 $7$ 也可以这么分解：$7=1+(1+1)*(1+1+1)$。所以我们在遇到质数 $p$ 时，不妨把 $p$ 拆成 $1$ 和另外一个数的和的形式：$p=1+q$，再对 $q$ 进行分解。

想到找这里，我们就可以确定出一个递归思路：   

在分解数 $p$ 时：
- 当 $p$ 为合数：拆成两个因子的乘积的形式。
- 当 $p$ 为质数：拆成 $1$ 与另一个数的加和的形式。

另外，我们需要特殊考虑数为 $1$ 时的情况和无解的情况，代码就可以写出来啦。

### Code
```cpp
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
map<int, string>ans;
map<int, bool>sf;
map<int, int>total1;//total[k]：分解 k 时需要的 1 的数量
string get_ans(int k) {
	if (k == 1) //特判
		return "1";
	if (sf[k])//记忆化搜索
		return ans[k];
	sf[k] = 1;

  //能拆成乘积的形式最好
	for (int i = (int)sqrt(k);i >= 2;--i)
		if (k % i == 0 && get_ans(i) != "NIE" && get_ans(k / i) != "NIE" && total1[i] + total1[k / i] <= 100) {
			total1[k] = total1[i] + total1[k / i];
			return ans[k] = "(" + get_ans(i) + "*" + get_ans(k / i) + ")";//拆成两个因子的积
		}

  //如果 k 是质数
	if (get_ans(k - 1) != "NIE"&&total1[k-1]+1<=100) {
		total1[k] = 1 + total1[k - 1];
		return ans[k]="(1+" + get_ans(k - 1) + ")";//拆成 1 与另一个数的加和
	}
	return ans[k]="NIE";//实在分解不了就是无解
}
int main() {
	total1[1] = 1;
	int T;
	cin >> T;
	while (T--) {
		int k;
		cin >> k;
		cout << get_ans(k) << endl;
	}
	return 0;
}
```

---

## 作者：ztd___ (赞：0)

小清新递归 + 构造题，10min 场切。

~~唉那我早点来打是不是能抢一个首 A 啊。~~
### 题意
让你用 `1`，`+`，`*`，`(`，`)` 五种字符组成一个表达式，使其结果为 $k$。

其中 `1` 不能连着用，所以 `11` 之类的不能存在。
### 分析 & 实现
观察样例的第 2 组数据，你发现可以用一堆 `1` 的和来表示一个数。

然后你发现这个规律对于所有数都有效。你发现本题不存在无解情况。

你用瞪出来的规律迅速写出了代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int k;
		cin >> k;
		for (int i = 1;i < k;i++) cout << "1+";
		cout << "1\n";
	}
	return 0;
}
```

你提交了代码。~~（虽然我没有这么干。）~~

正当你欣喜若狂，庆祝自己即将拿到人生第一个首 A 时，屏幕上那大大的 TLE 三个字母将你从梦中敲醒。

“唉我为什么 TLE 了啊，这不对吧。”

你检查题目，看到【说明/提示】一栏：
> - $1 \le k \le 10^9$

你的算法是 $O(k)$ 的，显然无法接受。

你垂头丧气，以为本题不可做，正打算跳题时，突然看到榜上有人 A 了这题。

“唉不对啊，如果正解就是一堆 `1` 的和的话，那 `*` 和括号又有什么用呢？”

你突然警醒，发现可以将 `k` 分解因数，然后将 `k` 表示成这堆因数的积，接着将每一个因数用一堆 `1` 表示即可。

你谨慎地分析了复杂度：分解因数是 $O(\sqrt k)$，然后因数大小是根号级别，总复杂度大致就是 $O(\sqrt k)$！

不过有可能找到的因数非常极端，所以最好从根号到 $2$ 枚举。

你心情非常复杂，既有正解如此简单的欣喜，又有因失误而没能抢到首 A 的遗憾，也有山重水复疑无路，柳暗花明又一村的感慨与释然。

~~“人生，不就是这样吗？山重水复疑无路，柳暗花明又一村。在事情毫无进展的时候，我们为什么不换个角度思考呢？说不定问题会变得更加简单啊！”~~

你迅速地编写了代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int k;
		cin >> k;
		int z = sqrt(k);
		for (int i = z; i >= 2; i--) {
			if (k % i == 0) {
				cout << "(";
				for (int j = 1; j < i; j++) cout << "1+";
				cout << "1)*";
				cout << "(";
				for (int j = 1; j < k / i; j++) cout << "1+";
				cout << "1)";
				break;
			}
		}
		cout << "\n";
	}
	return 0;
}
```

好了，你潇洒地伸了个懒腰，按下了鼠标。

“AC，AC，AC……”

“哦不，怎么还是 TLE 啊！”

~~错的好像更惨了。~~

你仔细地回想了自己的思路：分解因数是 $O(\sqrt k)$ 没问题，然后因数大小是根号级别……

“唉等等，因数大小一定是根号级别吗？万一因数里有大质数呢？”

你猛然顿悟。

你又想到：“质数减 $1$ 之后肯定不是质数了，所以我可以把质数拆成一个合数与 $1$ 的和！然后合数又可以继续分解，越分解越小，递归到 $1$ 就停止。这样复杂度就是根号级别了！”

你又仔细想了想，发现没有问题，于是写下了你的代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void print(int x) {
	if (x == 1) {
		cout << "1";
		return;
	}
	cout << "(";
	int z = sqrt(x);
	for (int i = z;i >= 2;i--) {
		if (x % i == 0) {
			print(i);
			cout << "*";
			print(x / i);
			cout << ")";
			return;
		}
	}
	cout << "1+";
	print(x - 1);
	cout << ")";
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int k;
		cin >> k;
		print(k);
		cout << "\n";
	}
	return 0;
}
```

“AC！太棒了！”

你心中五味杂陈，内心中对 OI 有了更加复杂的情感，也对 OI 的题目有了更深刻的感受。

你觉得，自己经过本题的磨砺后，步入了一个全新的境界，发生了思维上的蜕变。

你发现，自己从一个懵懂无知的小朋友，变成了一个有思维能力和代码能力的 OIer。

你心中满怀对未来的向往，借助 P11605，踏上了真正的 OI 之路。你自信满满道：

“我一定会 AK IOI 的！”

---

## 作者：xuyifei0302 (赞：0)

对于这道题，我们需要把最多 $100$ 个 $1$ 组成一个式子，使得这个式子的结果为 $k$。

由于出题人很穷，只给了 $100$ 个 $1$。那么，对于 $k \le 100$ 的情况就直接用 $k$ 个 $1$ 累加起来即可。

然后，我们来考虑 $k$ 的值超过 $100$ 该如何。

因为我们可以进行乘法操作，所以我们考虑分解因数。但是，又有一个困难摆在我们面前，对于大质数我们无法处理。但是我们将大质数减一，这个大质数就会成为一个合数。这是因为质数中只有 $2$ 是偶数，其余都为奇数。

所以，用这个方法，我们可以把大质数、因数里含大质数的 $k$ 处理出来。

由于增长量是 $\log$ 级别的，所以在 $10^9$  范围之内一定能表示出所有数，所以不存在无解。

下面是代码环节：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define FIOBUFSIZ 1048576
#define NEGATIVE
struct freader {
	FILE*f;
#   ifdef ONLINE_JUDGE
	char buf[FIOBUFSIZ], *p1, *p2;
#       define fgetc(f) (p1==p2&&(p2=(p1=buf)+fread(buf,1,FIOBUFSIZ,f),p1==p2)?EOF:*p1++)
#   endif
#   ifdef BOOLTRANS
	bool neof;
#       define NEOF(c) ((c)!=EOF||(neof=0))
#   else
#       define NEOF(c) ((c)!=EOF)
#   endif
#   ifdef NOTONLYDIGIT
#       define isdigit(c) ((c)>='0'&&(c)<='9')
#       define isnotdigit(c) ((c)<'0'||(c)>'9')
#   else
#       define isdigit(c) ((c)>='0')
#       define isnotdigit(c) ((c)<'0')
#   endif
	freader(FILE*_f = stdin): f(_f) {
#       ifdef BOOLTRANS
		neof = 1;
#       endif
#       ifdef ONLINE_JUDGE
		setvbuf(f, NULL, _IONBF, 0);
		p1 = p2 = buf;
#       endif
	}
#   ifdef NOTONLYDIGIT
	void read(char&x) {
		for (x = fgetc(f); NEOF(x) && x <= ' '; x = fgetc(f));
		return;
	}
	void read(char*s) {
		for (*s = fgetc(f); NEOF(*s) && *s <= ' '; *s = fgetc(f));
		for (s++; NEOF(*s = fgetc(f)) && *s > ' '; s++);
		*s = '\0';
		return;
	}
	freader&operator>>(char*x) {
#           ifdef BOOLTRANS
		return *this ? read(x), *this : *this;
#           else
		return read(x), *this;
#           endif
	}
#   endif
	template<typename T>void read(T&x) {
		char c(fgetc(f));
#       ifdef NEGATIVE
		for (; NEOF(c) && isnotdigit(c) && c != '-'; c = fgetc(f));
		if (c == '-')
			for (c = fgetc(f), x = 0; NEOF(c) && isdigit(c); c = fgetc(f))
				x = (x << 3) + (x << 1) - (c^'0');
		else
			for (x = 0; NEOF(c) && isdigit(c); c = fgetc(f))
				x = (x << 3) + (x << 1) + (c^'0');
#       else
		for (; NEOF(c) && isnotdigit(c); c = fgetc(f));
		for (x = 0; NEOF(c) && isdigit(c); c = fgetc(f))
			x = (x << 3) + (x << 1) + (c^'0');
#       endif
		return;
	}
	void ignore() {
		char c(fgetc(f));
		for (; NEOF(c) && c <= ' '; c = fgetc(f));
		for (; NEOF(c) && c > ' '; c = fgetc(f));
		return;
	}
#   if __cplusplus>=201103
	template<typename T, typename...Args>void read(T&x, Args&...args) {
		return read(x), read(args...);
	}
#   endif
	template<typename T>freader&operator>>(T&x) {
#       ifdef BOOLTRANS
		return *this ? read(x), *this : *this;
#       else
		return read(x), *this;
#       endif
	}
#   ifdef BOOLTRANS
	operator bool() {
		return neof;
	}
#   endif
#   ifdef ONLINE_JUDGE
#       undef fgetc
#   endif
#   undef NEOF
#   undef isdigit
#   undef isnotdigit
} fin;
struct fwriter {
	FILE*f;
#   ifdef ONLINE_JUDGE
	char buf[FIOBUFSIZ], *p1;
#       define fputc(c,f) (p1==buf+FIOBUFSIZ?fwrite(buf,1,FIOBUFSIZ,f),*(p1=buf)++=(c):*p1++=(c))
#   endif
	fwriter(FILE*_f = stdout): f(_f) {
#       ifdef ONLINE_JUDGE
		setvbuf(f, NULL, _IONBF, 0);
		p1 = buf;
#       endif
	}
	~fwriter() {
		flush();
	}
	void flush() {
#       ifdef ONLINE_JUDGE
		fwrite(buf, 1, p1 - buf, f), p1 = buf;
#       else
		fflush(f);
#       endif
		return;
	}
	void write(char c) {
		fputc(c, f);
		return;
	}
	void write(char*s) {
		for (; *s; s++)
			fputc(*s, f);
		return;
	}
	void write(const char*s) {
		for (; *s; s++)
			fputc(*s, f);
		return;
	}
	template<typename T>void write(T x) {
		if (!x) {
			fputc('0', f);
			return;
		}
		if (x < 0)
			fputc('-', f), x = -x;
		char s[41];
		int l(0);
		while (x)
			s[l++] = x % 10 ^ '0', x /= 10;
		while (l--)
			fputc(s[l], f);
		return;
	}
#   if __cplusplus>=201103
	template<typename T, typename...Args>void write(T x, Args...args) {
		return write(x), write(args...);
	}
#   endif
	template<typename T>fwriter&operator<<(T x) {
		return write(x), *this;
	}
#   ifdef ONLINE_JUDGE
#       undef fputc
#   endif
} fout;
int t, k;
string ans;
void dfs(int u) {
	if (u == 1) {
//		ans += '1';
		fout << '1';
		return;
	}
//	ans += '(';
	fout << '(';
	for (int i = 2; i * i <= u; i ++) {
		if (u % i == 0) {
			dfs(i);
//			ans += '*';
			fout << '*';
			dfs(u / i);
//			ans += ')';
			fout << ')';
			return;
		}
	}
//	ans += '1';
//	ans += '+';
	fout << '1';
	fout << '+';
	dfs(u - 1);
//	ans += ')';
	fout << ')';
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	fin >> t;
	while (t --) {
		fin >> k;
		if (k <= 100) {
			for (int i = 1; i < k; i ++) {
				fout << '1';
				fout << '+';
			} 
			fout << '1';
			fout << '\n';
			continue;
		} 
		dfs(k);
//		int len = ans.size();
//		for (int i = 0; i < len; i ++) {
//			fout << ans[i];
//		}
		fout << "\n";
	}
	return 0;
}
```

---

