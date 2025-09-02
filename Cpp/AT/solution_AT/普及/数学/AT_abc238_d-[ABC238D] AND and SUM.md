# [ABC238D] AND and SUM

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc238/tasks/abc238_d

$ T $ 個のテストケースについて、以下の問題を解いてください。

> 非負整数 $ a,s $ が与えられます。以下の条件を両方とも満たす非負整数の組 $ (x,y) $ は存在しますか？
> 
> - $ x\ \text{AND}\ y=a $
> - $ x+y=s $

 $ \text{AND} $ とは 非負整数 $ n,\ m $ の bit ごとの論理積 $ n\ \text{AND}\ m $ は、以下のように定義されます。

- $ n\ \text{AND}\ m $ を二進表記した際の $ 2^k\ \,\ (k\ \geq\ 0) $ の位の数は、$ n,\ m $ を二進表記した際の $ 2^k $ の位の数のうち**両方**が $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 4\ \text{AND}\ 6\ =\ 4 $ となります（二進表記すると: $ 100\ \text{AND}\ 110\ =\ 100 $）。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10^5 $
- $ 0\ \leq\ a,s\ \lt\ 2^{60} $
- 入力はすべて整数

### Sample Explanation 1

$ 1 $ 番目のテストケースにおいては、$ (x,y)=(3,5) $ などが条件を満たします。 $ 2 $ 番目のテストケースにおいては、条件を満たす非負整数の組 $ (x,y) $ は存在しません。

## 样例 #1

### 输入

```
2
1 8
4 2```

### 输出

```
Yes
No```

## 样例 #2

### 输入

```
4
201408139683277485 381410962404666524
360288799186493714 788806911317182736
18999951915747344 451273909320288229
962424162689761932 1097438793187620758```

### 输出

```
No
Yes
Yes
No```

# 题解

## 作者：DYYqwq (赞：12)

看题解区各位大佬的解释我感觉自己被吊打了，但是还是厚着脸皮补一个可以让人感性理解的方法（

# $\texttt{Problem}$
给出两个数 $a,b$，问能否找到两个数 $x$ 和 $y$ 使得 $x\ \operatorname{and}\ y=a$ 且 $x+y=b$。

# $\texttt{Solution}$
先假设 $x \geq y$。

由于 $\operatorname{and}$ 的特性（若 $x\ \operatorname{and}\ y=a$，$x,y  \geq a$），我们发现 $y$ 最小就是 $a$，所以我们便从这里入手。

此时，无非就两种情况：

+ $y = a$ 时存在一个整数 $x$ 满足条件。
+ $y = a$ 时并不存在一个整数 $x$ 满足条件。

那么分析下上述“条件”指的是什么。

首先， $y=a$ 时 $x=b-y=b-a$，我们需要保证 $x$，也就是 $b-a$ 满足 $ \operatorname{and}\ y=a$。

接着，$x = b-a$ 要 $\leq y = a$（原假设），所以就应该是 $b-a \geq a$。

再回到两种情况身上。

+ 满足条件没啥可说的，直接找到了解决方案，输出 $\texttt{Yes}$。
+ 不满足条件，这种情况我们细聊。

$b-a < a$ 说明 $b-a = x$ 没有能力满足 $\operatorname{and}$ 起来是 $a$，因为你都 $\leq a$ 了嘛。所以肯定“不可以，总司令”。

$b-a \ \operatorname{and}\ y \ne a$，我们举个例子。

$y = a = \texttt{101010}$

$x=b-a=\texttt{101001101110}$

我们发现 $x$ 右数第 $3$ 位与 $y$ 不同。因此如果想相同的话，必须让 $x$ 从 比 $y$ 多的那几位向下借。你“拆了东墙补西墙”后，$x$ 的**后几位**终于“如愿以偿”的补成了 $y$，只可惜，正因此，$y$ 也需要增加一些东西了（因为 $x$ 是**以高位换低位**，所以 $x$ **整体** **减少**了。因此，为保证 $x+y=b$，$y$ 应该**增加**）。而增加后显然就又不能和 $x$ 相等了，因此如果 $b-a \ \operatorname{and}\ y \ne a$ 也“不可以，总司令”。

综上，我们得到了解题具体方法：
+ 若 $y = a$ 时，$b-a \ \operatorname{and}\ y=a$ 且 $b-a \geq a$，输出 $\texttt{Yes}$。
+ 反之，输出 $\texttt{No}$。

# $\texttt{Code}$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t , a , b;
signed main()
{
	scanf("%lld" , &t);
	while(t --)
	{
		scanf("%lld%lld" , &a , &b);
		int qwq = b - a;
		if((qwq >= a) && ((qwq & a) == a))
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
```

注意，`&` 的优先级是小于 `==` 的，因此 `b-a&a==a` 应写成 `(b-a&a)==a`。

______

看完后要是有不懂的地方私信问我鸭 qwq

---

## 作者：_VEGETABLE_OIer_xlc (赞：1)

[题目传送](https://www.luogu.com.cn/problem/AT_abc238_d)

### 分析

根据位运算中与的性质，如果 $x\ \operatorname{and}\ y=b$，那么 $x$ 和 $y$ 的二进制中一定包含 $b$ 的二进制。

那么我们就成功的把问题变为了 $(b-2a)\ \operatorname{and}\ a$ 的判断。如果是 $0$，那么就可以构成，否则不行。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>a>>b;
		if((b-2*a<0)||((b-2*a)&a!=0))
			cout<<"No"<<endl;
		else
			cout<<"Yes"<<endl;
		continue;
	}
	return 0;
}
```


---

## 作者：lucky_loser (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc238_d)

### 题目大意

给出 $a,b$ 两个数，求是否有两数 $x$，$y$ 使 $x+y=a$ 且 $x\operatorname{and} y=b$。

### 分析

由位运算的性质可知，若 $x\operatorname{and} y=b$，$x$ 和 $y$ 二进制位都包含 $b$。

所以直接计算 $(b-2a)\operatorname{and} a$，如果答案是 $0$，就输出 `Yes`，否则输出 `No`。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,a,b;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a>>b;
		if(b>=2*a)
		{
			if((b-2*a&a)==0)
			{
				cout<<"Yes"<<endl;
				continue;
			}
		}
		cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc238_d)

### 题目大意

求是否存在 $x$ 满足 $x\operatorname{and}(s-x)=a$。

### 题目思路

很明显，若有 $a\operatorname{and}b=c$，则 $c$ 的第 $x$ 位必然等于 $a$ 或 $b$ 的第 $x$ 位。

我们需要一个完全等于的有点困难，我们可以反着思考：构造一种不与 $c$ 的每一位匹配的。这种情况下，也就是 $d\operatorname{and}c=0$，这意味着每一位都完全不相同。但是这样是错误的，因为还有同一位 $d$ 和 $c$ 都为 $0$ 的情况，所以我们要考虑一种不会出现这种情况的 $d$，最后可以推出 $d=s-2a$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long a,s;
		cin>>a>>s;
		if(((s-2*a)&a)==0&&s>=2*a)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}  
```


---

## 作者：ABCD101 (赞：0)

## 题意简述

+ 有 $n$ 行输入, 每行两个数 $a,b$.
+ 求是否有非负整数 $x,y$ 满足 $x+y=a,x\textbf{ AND } y=b$.

## 基本思路

把 $x\textbf{ AND } y$ 的值在二进制表示下为 $1$ 的位置标号加入集合 $A$, 把 $x\textbf{ OR } y$ 为 $1$ 的位置加入集合 $B$.

可以发现, 显然有 $A\cup B=\empty$ , 进一步推出 $\sum_{x\in A}x=a$ 以及 $2(\sum_{x\in A}x)+(\sum_{y\in B}y)=b$.

也就是 $\sum_{y\in B} y = b-2a$, 于是就有 $(s-2a) \textbf{ AND } a = 0$.

还要求 $x,y\in \N$, 可以知道 $\sum_{y\in B}y\le0$ 也就是 $2a\le b$.

最后得到能构造出合法的 $x, y$ 的条件 ([艾弗森约定](https://www.ituring.com.cn/book/tupubarticle/23862)) :
$$
[2a\le b][(s-2a) \textbf{ AND } a = 0]=1
$$

## 参考代码

```cpp
int main(){
    long long unsigned _, a, b;
    cin>>_;
    while(_--){
        cin>>a>>b, a<<=1;
        cout<<(a<=b&!(b-a&a>>1)?"Yes":"No")<<'\n';
    }
}
```



 



---

## 作者：ttq012 (赞：0)

首先通过 $x\operatorname{and} y=a$ 这个条件计算出 $x$ 和 $y$ 至少有哪一些位置为 $1$。显然此时 $x=y=a$。那么如果 $2\times a>s$ 显然无解。

然后从大到小贪心枚举 $x$ 中 $0$ 的位置，将他变成 $1$。如果发现这个时候 $x+y=s$ 那么就有解。如果 $x+y>s$ 那么无解。否则继续贪心即可。

单组询问时间复杂度 $O(\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
  int T;
  cin>>T;
  while(T--){
    int a,s;
    cin>>a>>s;
    if(2*a>s)cout<<"No\n";
    else{
      int x=a,y=a;
      bool flag=false;
      for(int i=61;~i;i--){
        if(~x&(1ll<<i)){
          if((x|(1ll<<i))+y<=s){
            x|=(1ll<<i);
          }
        }
      }
      if(x+y!=s)cout<<"No\n";
      else cout<<"Yes\n";
    }
  }
  return 0;
}
```

---

## 作者：Star_Rail (赞：0)

我们知道 $a=x+y,\ b=x\ \mathrm{and}\ y$

为了简便我们可以先看一个位：

1. 当两个数的这一位都为 $1$ 时：$a=1+1=0,\ b=1\ \mathrm{and}\ 1=1$。
2. 当两个数的这一位都为 $0$ 时：$a=0+0=0,\ b=0\ \mathrm{and}\ 0=0$。
3. 当两个数的这一位一个为 $1$ 一个为 $0$ 时：$a=0+1=1,b=0\ \mathrm{and}\ 1=0$。

从以上分析中可以很明显看出，我们用 $a-b$ 就能得出来 $a-b=x\ \mathrm{or}\ y$。

然后我们判断当 $b$ 的每一位为 $1$ 时，$a-b$ 的每一位也应该是 $1$，如果成立那么存在，否则不存在。

## AC code

```cpp
#include <bits/stdc++.h>
#define int long long
#define r rd()
#define frz(a,b,c) for(int a=b;a<=c;a++)
#define frj(a,b,c) for(int a=b;a>=c;a--)
#define wh(a,b) while(a<=b)
#define wh1 while(1)
#define gc getchar()
#define pc putchar
#define pcs putchar(' ')
#define pcen putchar('\n')
using namespace std;
int rd(){
	int x=0,f=1;
	char ch=gc;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=gc;
	return x*f;
}
void wr(int x){
	if(x<0) x=-x;
	if(x>9) wr(x/10);
	pc(x%10+'0');
}
int T;
int a, b;
int aorb;
bool f(int x, int y){
	string s1,s2;
	string c1,c2;
	while (x){
		s1+=x%2+'0';
		x/=2;
	}
	while (y){
		c1+=y%2+'0';
		y/=2;
	}
	for (int i=0; i<s1.size(); i++){
		if (s1[i]=='1')
			if (c1[i]!='1') return 0;
	}
	return 1;
}

main(){
	cin>>T;
	while(T--){
		cin>>b>>a;
		aorb=a-b;
		if (f(b,aorb))
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
给你两个数 $a$ 和 $s$，求是否有满足 $x\&y=a$ 并且 $x+y=s$ 的一对**非负整数** $(x,y)$ 存在。


## 分析
由位运算的性质可知： 

要想让 $x \& y=a$，显然 $x$ 和 $y$ 的二进制位中都包含 $a$，除 $a$ 外的其他位不重合。

所以我们可以直接计算 $(s-2a) \& a$，如果为 $0$ 则符合要求。


## 代码

```cpp
#include <iostream>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long a,s;
		cin>>a>>s;
		if(s>=2*a)
		{
			if((s-2*a&a)==0) //按照思路模拟 
			{
				cout<<"Yes"<<endl;
				continue;
			}
		}
		cout<<"No"<<endl;
	}
	return 0;
}

```

---

