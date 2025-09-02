# Carrying Conundrum

## 题目描述

Alice has just learned addition. However, she hasn't learned the concept of "carrying" fully — instead of carrying to the next column, she carries to the column two columns to the left.

For example, the regular way to evaluate the sum $ 2039 + 2976 $ would be as shown:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/7f811803128f9de09a9d354d6ba38f6c979516bb.png)However, Alice evaluates it as shown:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/83982f3a368c4bf27357d999f4274a4bb752e11c.png)In particular, this is what she does:

- add $ 9 $ and $ 6 $ to make $ 15 $ , and carry the $ 1 $ to the column two columns to the left, i. e. to the column " $ 0 $ $ 9 $ ";
- add $ 3 $ and $ 7 $ to make $ 10 $ and carry the $ 1 $ to the column two columns to the left, i. e. to the column " $ 2 $ $ 2 $ ";
- add $ 1 $ , $ 0 $ , and $ 9 $ to make $ 10 $ and carry the $ 1 $ to the column two columns to the left, i. e. to the column above the plus sign;
- add $ 1 $ , $ 2 $ and $ 2 $ to make $ 5 $ ;
- add $ 1 $ to make $ 1 $ .

 Thus, she ends up with the incorrect result of $ 15005 $ .Alice comes up to Bob and says that she has added two numbers to get a result of $ n $ . However, Bob knows that Alice adds in her own way. Help Bob find the number of ordered pairs of positive integers such that when Alice adds them, she will get a result of $ n $ . Note that pairs $ (a, b) $ and $ (b, a) $ are considered different if $ a \ne b $ .

## 说明/提示

In the first test case, when Alice evaluates any of the sums $ 1 + 9 $ , $ 2 + 8 $ , $ 3 + 7 $ , $ 4 + 6 $ , $ 5 + 5 $ , $ 6 + 4 $ , $ 7 + 3 $ , $ 8 + 2 $ , or $ 9 + 1 $ , she will get a result of $ 100 $ . The picture below shows how Alice evaluates $ 6 + 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/b16910e4b25eab78326b49caad3574b10b90fef3.png)

## 样例 #1

### 输入

```
5
100
12
8
2021
10000```

### 输出

```
9
4
7
44
99```

# 题解

## 作者：dd_d (赞：13)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15232932.html)   
官方题解的做法根本想不到，讲一下官方题解的做法。  
### Sol  
首先可以发现一个性质，奇数位的数只会进位到奇数位。  
偶数位同理。  
我们考虑把奇数位的数和偶数位的数单独考虑。  
显然，对于一个数 $n$，分为 $2$ 个非负整数之和只有 $n+1$ 种方案。  
记奇数位上的数为 $x$，偶数位上的数为 $y$。  
那么最终的答案即为 $(x+1) \times (y+1)-2$。  
由于不能取 $0$ 所以最终的答案还要减去 $2$。  
### Code  
```cpp
signed main()
{
	T=read();
	while (T--)
	{
		scanf("%s",st+1); n=strlen(st+1);
		num1=num2=0;
		for (int i=1;i<=n;i+=2)
			num1=num1*10+(st[i]^48);
		for (int i=2;i<=n;i+=2)
			num2=num2*10+(st[i]^48);
		writeln((num1+1)*(num2+1)-2);
	}
}
```

---

## 作者：zimujun (赞：7)

> 重新定义加法运算规则：从低位到高位逐位相加，若满十则在高两位上进一。

> $t$ 组数据，每组数据给定一个正整数 $n$，求有多少有序正整数对 $(a, b)$ 满足 $a$ 和 $b$ 做这种加法运算的结果为 $n$。

> $t \le 10^3, 2 \le n \le 10^9$

下文中直接用加号 "$+$" 表示的是正常运算规则的加法运算。

显然在这种“错误的加法运算规则”下，奇数位和偶数位上的运算相互独立了，因此考虑把一开始的数拆成在奇数位上的和在偶数位上的两个数，记为 $o, e$，分别计算有多少个有序正整数对 $(a, b)$ 满足 $a + b = o, a + b = e$，得到的两个结果相乘即为答案。

先考虑 $o > 0, e > 0$ 的情况，不妨先考虑有多少个非负有序整数对满足条件，显然为 $cnt = (o + 1)(e + 1)$（如把 $o$ 拆为 $(i, o - i), 0\le i\le o$, $e$ 同理），这之中不合法的情况就是两个有序非负整数对中第一项同为 $0$ 或第二项同为 $0$ 共两种情况，故总的答案 $ans = cnt - 2$。

当 $\min\{o, e\} = 0$ 时，不为零的那个数两项都不能拆出零，因此答案 $ans = \max\{o, e\} - 1$。

---

## 作者：LaDeX (赞：6)

## 题意

把加法的进位从满十向 **前面第一位** 进一重新定义为满十向 **前面第二位** 进一。

## 解法

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/83982f3a368c4bf27357d999f4274a4bb752e11c.png)

观察样例可发现，奇数位的只向奇数位进一，偶数位只向偶数位进一。

如：
	
- 第一位 $9 + 6 = 15$ 向第三位进一，第三位 $0 + 9 +1 = 10$ 向第五位进一。

- 第二位 $3 + 7 = 10$ 向第四位进一。

那么可以奇偶分开解决。

$A,B$ 为 加数，$N$ 为 和。

只要 $A$ 的奇数位连起来的数 与 $B$ 的奇数位连起来的数 之和（正常的加法）等于 $N$ 的奇数位连起来的数 并且 偶数位也这样，那么 $A$ 与 $B$ 的 和 （Alice 的加法）就等于 $N$。

一个数 $x$ 分为两个数的和一共有 $x + 1$ 种：
$$0 + x, 1 + (x - 1),2 + (x - 2),\dots,(x - 1) + 1, x + 0 $$

最后把 奇数位的种类 乘以 偶数位的种类 再 减 $2$ 即可。

因为 题目要求是正整数，要减去 $0 + n$ 和 $n + 0$ 两种。

例如样例，一共有 $(105 + 1) \times(50 + 1) - 2$ 种。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;

void solve(){
	string N;
	cin >> N;
	LL odd = 0, even = 0;
	
	// 奇数位的数连起来的数
	for (LL i = 0; i < (LL)N.size(); i += 2){
		odd = odd * 10 + (N[i] ^ 48);
	}
	// 偶数位的数连起来的数
	for (LL i = 1; i < (LL)N.size(); i += 2){
		even = even * 10 + (N[i] ^ 48);
	}
	
	// Answer
	cout << (odd + 1) * (even + 1) - 2 << "\n";
	return ;
}

int main(){
	LL T;
	cin >> T;
	while (T --)
		solve();
	return 0;
}
```


---

## 作者：blank_space (赞：5)

## C. Carrying Conundrum

看到 CF 的题解里是给出了一个结论的, BS 表示这个结论真的不是很明白.

然后是看到题解里面给出了一个 dp 的思路, 但是... ~~英语害人~~

只是大概意会了一下题解的意思, 在这里就给一个 dp 的思路和代码吧.

---

~~其实这个题看着就很数位 dp 的说~~

读完题目, 可以发现这是一个好像与数学有关系的题, 但是又没有什么好的数学方法解决, 而 $n$ 的范围又比较大, 这时可以按位进行考虑, 也就是数位 dp 了.

先提一句: 蒟蒻的数位 dp 只会记搜, 并没有写过循环类型的, 所以下面的东西也是在记搜的基础上来的.

先说一下在这个题目里面数位 dp 是干什么的.

以题中的 $10000$ 为例, 下文中对于从左向右也就是从高位到低位的第 $i$ 位简述为第 $i$ 位.

考虑按照题目中的方法相加可以得到该数的二元组的个数, 二元组是有序的, 所以只需要考虑第一项的所有取值即可.

$10000$ 的第一位上为 $1$ , 则选取的数字中第一位上只能为 $1$ 或 $0$ , 若为 $1$ , 由于这一位是不能产生进位的, 所以选取的另一个数中这一位上只能为 $0$ , 同时这样也限制了低位上是不能出现进位的, 所以这一二元组只能为 $(10000, 0)$ , 但这一情况是不合法的(出现了 $0$), 则选取的数字第一位上只能为 $0$ , 那么这一位上的 $1$ 是由第三位进上来的, 那么不能进位的第二位也只能为 $0$ 了, 对于第三位, 所能选取的数字为 $0 \sim 9$ , 不难发现, 当第五位上的数不会进位的时候, 第三位上的数可以取 $1 \sim 9$, 此时的二元组为 $(100, 900), (200, 800), \dots, (900, 100)$. 当第五位上的数字进位的时候, 这一位上的数可以取 $0 \sim 9$, 此时对于第五位上可以取的数字为 $1 \sim 9$ , 对应二元组太多了就不再罗列了.

这样可以算出可行的方案数为 $9 + 10 \times 9 = 99$ , 而数位 dp 即是模拟了这个过程, 统计可能的方案数.

数位 dp , 首先要维护的是当前的位数, 即第 $i$ 位, 由高位向低位 dp , 在每一位上处理进位情况.

这个题目要求的是在高两位的位置上进一, 其实对 dp 并没有什么影响, 一并记录下来处理就好了.

然后说一下怎么处理

在每一位上, 维护该位是否需要由低位进位, 这里解释一下, 假设给定的数中这一位上的数字为 $x$ , 如果这一位需要由低位进位, 则二元组中这一位上的两数相加的和应为 $x - 1$ , 或者 $x + 10 - 1$ , 即是两数相加再加上由低两位的位置进上来的 $1$ , 得到要求的数字.

然后处理这一位的时候还需要考虑这一位是否需要向高两位的位置进位, 这决定了这一位需要的结果是 $x$ , 还是 $x + 10$. 由于是从高位向低位处理的, 所以处理到当前位的时候, 高两位的位置上是否需要进位这一情况在当前状态下是确定的, 那么可以在处理那一位的时候将是否进位记录下来, 方便当前位的处理, 但是跨位记录不太方便, 所以相应的记录上一位, 以及上上位是否需要进位, 这样转移也比较容易了.

那么如何判断这一位上是否需要由低位进位呢?

在当前位上枚举这一位可能的数字, 记为 $y$ , 同时对应的计算出二元组中另一个在这一位上的数字, 记为 $z$ , $y + z$ 得到的就是这一位上要求的数字了, 那么这一位需要进位即为 $y + z = x + 1$ 或 $y + z = x + 1 + 10$ , 不需要进位即为 $y + z = x$ 或 $y + z = x + 10$ , 这里不再展开了.

这样就可以枚举当前位的数字进行转移了.

当成功找到一个可行的数时记录答案就好了.

具体的细节问题看代码吧, 感觉说的比较详细了...

---

补充一下: 

考虑的二元组是有序的, 即 $(x, y)$ 与 $(y, x)$ 在 $x \ne y$ 的时候是不同的, 所以只考虑对第一项计数就好了.

dp 的过程中对于 $(0, n)$ 和 $(n, 0)$ 这两个并没有特殊判断, 所以在最后的答案中要减掉.





---

代码

```cpp
/*
  Source: CF C. Carrying Conundrum
*/
#include<cstdio>
#include<cstring>
#define pn putchar('\n')
/*----------------------------------------------------------*/
int T, n, li[20], f[12][2][2];
/*----------------------------------------------------------*/
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
void Print(int x) {if(x < 0) putchar('-'), x = -x; if(x > 9) Print(x / 10); putchar(x % 10 ^ 48);}
/*----------------------------------------------------------*/
int dfs(int i, int last2, int last1) {
	if(!i) return 1; int res = 0;
	if(~f[i][last2][last1]) return f[i][last2][last1];
	if(last2)
	{
		for(int j = 0; j ^ 10; ++j)
		{
			if(li[i] + 10 - j >= 1 && li[i] + 10 - j <= 9)
				res += dfs(i - 1, last1, 0);
			if(i > 2 && li[i] + 9 - j >= 0 && li[i] + 9 - j <= 9)
				res += dfs(i - 1, last1, 1);
		}
	}
	else
	{
		for(int j = 0; j ^ 10; ++j)
		{
			if(li[i] - j >= 0 && li[i] - j <= 9)
				res += dfs(i - 1, last1, 0);
			if(i > 2 && li[i] - j - 1 >= 0 && li[i] - j - 1 <= 9)
				res += dfs(i - 1, last1, 1);
		}
	}
	return f[i][last2][last1] = res;
}
int solve(int x) {
	int cnt = 0; memset(li, 0, sizeof li); memset(f, -1, sizeof f);
	while(x) li[++cnt] = x % 10, x /= 10;
	return dfs(cnt, 0, 0);
}
void work() {
	n = read();
	Print(solve(n) - 2); pn;
}
void Main() {
	T = read(); while(T--) work();
}
/*----------------------------------------------------------*/
signed main() {Main(); return 0;}

```



---

---

## 作者：灰鹤在此 (赞：3)

### 题目中的限制条件：$2$ 个数的加法运算规则为进位 $2$ 位，先看一看题目中给的 $2$ 个样本。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/83982f3a368c4bf27357d999f4274a4bb752e11c.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/b16910e4b25eab78326b49caad3574b10b90fef3.png)

细看一下就会发现第 $1$ 位的数进位只会影响第 $3$ 位的数，第 $3$ 位的数进位只会影响第 $5$ 位的数。第 $2$ 位的数进位只会影响第 $4$ 位的数，第 $4$ 位的数字进位只会影响第 $6$ 位的数……

我们要求的是两个数通过这样的加法规则加在一起后得到 $n$ 的总数。

例如：

$100=1+9=2+8=3+7=4+6=5+5=6+4=7+3=8+2=9+1$

$12=11+1=10+2=2+10=1+11$

$8=1+7=2+6=3+5=4+4=5+3=6+2=7+1$

所以我们可以先把奇数位偶数位的数先分开来，比如 $2021$ 可以拆分为 $22$ 和 $1$，并且 $22=22+0=21+1=……=1+21=22+0$。

由于此时的 $22$ 的加法规则是正常的加法规则，所以我们求得的两个数的偶数位有 $23$ 种搭配。又因为 $1=0+1=1+0$，即奇数位有 $2$ 种搭配。所以我们得到了当 $x,y\in N$ 时两个数的总方案数。

但是我们要求的是当 $x,y\in N^+$ 时两个数的总方案数，所以我们要将求得的方案数 $-2$。因为在求搭配时我们发现，会有两个含有 $0$ 的搭配出现，奇数位有，偶数位有，而且两个 $0$ 刚好在同一个数中组合的方案会出现两次。所以我们要减掉含有 $0$ 的方案。

还有第二种情况，那就是在奇数或偶数位上就是 $0$ 的，那么总方案数就是当 $x,y\in N$ 求得的方案数再减去含有 $0$ 的两个方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=20;
int t,n,a[MaxN],b[MaxN],ans1,ans2;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int k=n,cnt=0,cnt1=0,cnt2=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		while(k){
			cnt++;
			if(cnt%2==1){
				a[++cnt1]=k%10;
			}else{
				b[++cnt2]=k%10;
			}
			k/=10;
		}
		ans1=ans2=0;
		for(register int i=cnt1;i>=1;i--){
			ans1=ans1*10+a[i];
		}
		for(register int i=cnt2;i>=1;i--){
			ans2=ans2*10+b[i];
		}
		if(ans1==0||ans2==0){
			printf("%d\n",ans1+ans2-1);
		}else{
			printf("%d\n",(ans1+1)*(ans2+1)-2);
		}
	}
	return 0;
}
```

然后我们可以发现一种更简洁的代码，我们将 $0$ 看做成 $1$ 种方案，然后每一奇偶位方案数全都 $+1$，发现对于答案没有影响。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,ans1,ans2;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		k=ans1=ans2=1;
		while(n){
			ans1+=n%10*k;
			n/=10;
			ans2+=n%10*k;
			n/=10;
			k*=10;
		}
		printf("%d\n",ans1*ans2-2);
	}
	return 0;
}
```

---

## 作者：Firstly (赞：1)

## **题目思路：**

我们可以发现，在重新定义的加法运算规则当中，每个数位的进位都会进到前两位。即奇数位会进到奇数位，偶数位会进到偶数位。那么不妨将一个数字拆成两个数来看，例如题目中的 $15005$，我们可以将其看成 $(105,50)$。

而我们可以发现，有 $106$ 个数对可以组成 $105$，它们分别是：$(0,105)$，$(1,104)$......同样，有 $51$ 个数对可以组成 $50$。由此我们可以总结出，有 $n+1$ 个数对可以组成 $n$。

但是答案也需要剔除掉 $0$ 的两个答案，所以最终的结果为：$(a+1)(b+1)-2$（设 $a$ 为奇数位上的数字，$b$ 是偶数位上的数字）。

## **Code:**

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		string s;//可将原数字看做一个字符串，这样相对便于遍历
		cin>>s;
		int a=0,b=0;
		for(int i=0;i<s.size();i++)
			if((i+1)%2==0)a=a*10+int(s[i]-48);
			else b=b*10+int(s[i]-48);
		cout<<(a+1)*(b+1)-2<<endl;
	}return 0;
}
```


---

## 作者：云浅知处 (赞：1)

很好玩的一个题。[题目 Link](https://codeforces.com/problemset/problem/1567/C)

注意到在新的加法规则下奇数位和偶数位是相互独立的，奇数位上的进位只会影响奇数位，偶数位同理。

因此我们考虑将奇数位和偶数位上的数分别提出来，设为 $x,y$。

例如，对 $n=1\color{red}1\color{black}4\color{red}5\color{black}1\color{red}4\color{black}$，就有 $x=154,y=141$。

接下来要计算的就是：「在正常进位法则下满足 $a+b=x$ 的有序非负整数对 $(a,b)$ 的个数」，这显然就是 $x+1$。对于偶数位的 $y$ 也是同理的。

由于题目中要求是正整数，所以要减去 $(0,n)$ 和 $(n,0)$，所以最终的答案就是 $(x+1)(y+1)-2$。

场上我写了一个枚举进位的暴力，这里直接给出题解的代码。[Link](https://codeforces.com/contest/1567/submission/127991331)

---

## 作者：uid_310801 (赞：0)

### 题目简述

定义新的加法法则：两个数在竖式中相加，满十不再是在高一位上进一，而是在**高两位**上进一。

给定 $n$ ，问在新的加法法则下有多少对正整数相加等于 $n$ 。

### 题目解析

首先考虑正常的加法情况下，有多少对数相加和为n？

很明显，对于所有 $i(1\le i <n)$ 都有 $n-i$ 使他们两个相加和为 $n$，总的对数为 $n-1$ 个。

回到题目，仔细观察题目给出的竖式，我们发现在进行运算的过程中，奇数位和偶数位是相互独立，不受对方影响的。

也就是说，如果我们去掉了所有偶数位上的数字，剩下的便可以使用普通的加法法则的规律来求对数了。

设 $n$ 奇数位上的数为 $a$ ，偶数位上的数为 $b$ ，那么 $n$ 的所有**非负整数解**就有 $(a+1)(b+1)$ 个。然后去掉 $a,b$ 都为 $0$ ，或者与他们配对的两个数都为 $0$ 的两种情况，总答案数 $ans$ 便是 $(a+1)(b+1)-2$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,a,b;
char c[15];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%s",&c);
		a=b=0;
		n=strlen(c);
		for(int i=0;i<n;i+=2){
			a=a*10+c[i]-'0';
		}
		for(int i=1;i<n;i+=2){
			b=b*10+c[i]-'0';
		}
		printf("%lld\n",(a+1)*(b+1)-2);
	}
   return 0;
} 
```


---

## 作者：白鲟 (赞：0)

### 题目描述
将加法的向第 $i+1$ 位进位改为向第 $i+2$ 位进位，求两正整数之和为 $s$ 的方案数。

### 题目分析
发现奇偶位是独立的，可以拆成两个正常的加法，两方案乘起来即可。

对于每一个和为 $x$ 的正常加法，第一个加数有 $x+1$ 种情况（即 $[0,x]$），而每个第一个加数对应一种方案，故共有 $x+1$ 种方案。

于是设奇数位构成的数为 $x$，偶数位构成的为 $y$，则方案数为 $(x+1)(y+1)-2$。$-2$ 是由于此题要求正整数，故要减去第一个加数和第二个加数中有一个为 $0$ 的情况。

### 代码
挺短的吧。
```cpp
#include<bits/stdc++.h>
#define loop(i,from,to) for(int i=(from);i<=(to);++i)
using namespace std;
const int maxn=20;
int T,n,now[2];
char s[maxn+1];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1),n=strlen(s+1),now[0]=now[1]=0;
		loop(i,1,n)now[i&1]=now[i&1]*10+s[i]-'0';
		printf("%d\n",(now[0]+1)*(now[1]+1)-2);
	}
	return 0;
}
```

---

