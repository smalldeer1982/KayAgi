# Digit Minimization

## 题目描述

有一个用十进制表示的没有前导零的正整数 $n$ 。Alice 和 Bob 正在用这个数玩一个游戏。Alice 先手，他们轮流进行游戏。

在她的这一轮中，Alice 应该交换这个数中的任何不同位置的两位。轮到 Bob 时，他每次都会删除这个数的末一位。当这个数只剩一位时，游戏结束。

你需要找出 Alice 用最佳方法在最后找出的最小数。

## 样例 #1

### 输入

```
3
12
132
487456398```

### 输出

```
2
1
3```

# 题解

## 作者：Dream_weavers (赞：5)

## 题意

Alice 和 Bob 在玩一种游戏。给出一个十进制数 $n$，Alice 要交换 $n$ 中位置不同的两个数，Bob要删掉 $n$ 的最后一个数字，两人轮流进行，Alice 先手。问最后剩余的**最小**数是多少。

## 思路

Alice 可以任意交换两个数字，题目是为了找到剩余后的最小数，那么她可以把 $n$ 中的最大数字放在最后删除，保留 $n$ 中最小的数字到最前面，直到删去只剩一个数为止。换句话说，题目就是要找 $n$ 中的最小数字，只需从头到尾遍历找最小值即可。

### 注意

如果 $n$ 的长度**等于** $2$ 时，那么 Alice **必须**交换两个数字，剩下数是原来 $n$ 的**第二个**数字。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
string n;//用字符串会更方便一些
signed main(){
	scanf("%lld",&t);
	while(t--){//t组数据
		cin>>n;
		int len=n.size();//计算长度
		char minn='9';
		if(len==2){//特判长度等于2时
			cout<<n[1]<<endl;
		}else{
			for(int i=0;i<len;i++)minn=min(minn,n[i]);//找最小值
			cout<<minn<<endl;
		}
	}	
	return 0;
}
```

---

## 作者：Ligans (赞：3)

### 题意

[To 洛谷](https://www.luogu.com.cn/problem/CF1684A)  
[To CF](https://codeforces.com/problemset/problem/1684/A)

- 有一个整数 $n$（$10\le n\le10^9$），不含前导零。Alice（简称 A）和 Bob（简称 B）对该数轮流进行操作。
- 对于每一轮操作：A 先手，交换该数中的不同位置的两位；B 后手，删除该数的末位。
- 当该数只剩一位时，游戏结束。

给定 $n$，假设 A 运用最佳方法，找出在最后产生的最小数。

---

### 思路

设 $s$ 是 $n$ 的长度，$n_i$ 是 $n$ 的 $i$ 位（从左向右）。

- 当 $s=2$ 时，A 必交换 $n_1$ 和 $n_2$，B 删除末位（即 $n_1$）后，剩余 $n_2$。
- 当 $s\ge3$ 时，A 交换时，使 $n_2$ 是 $n$ 各个数位中的最小数。接下来操作同上，剩余 $n$ 各个数位中的最小数。

可证明上述思路最优

---

### $Code$

```cpp
//snail2956
//CF1684A
//2022.5.21 17:12

#include<cstdio>
#include<string>
#include<iostream>
using namespace std;

int t;

int main(){
    scanf("%d",&t);
    while(t--){
        string n;
        cin>>n;
        int s=n.size();
		char min='9';
        if(s==2) min=n[1];
		else for(int i=0;i<s;i++) if(n[i]<min) min=n[i];
		printf("%c\n",min);
    }
    //QwQ
    return 0;
}
```


---

## 作者：cst_123 (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF1684A)

------------

### 题意

给你一个两位几以上的正整数 $n$，让你经过若干次操作，当 $n$ 只剩个位时，输出它的最小值。

### 思路

操作有两种， 可将其看成先调换任意不同的两位，再将其删去最后一位。

在两位数时，只能调换十位和个位，再删去已经为个位的十位，所以输出个位就行了。

当超过两位数，我们就可以输出最小的一位。因为我们可以将最小的数位放到倒数第二位，删去一位时再放到倒数第二位，直到 $n$ 只剩个位。

### 代码

```cpp
	while(T--){
		cin>>a;
		len=S.size();
		ans='9';//ans为char类型
		if(len==2)
        //特判时两位数时，输出个位
			ans=a[1];
		else
        //不然找最小的
			for(int i=0;i<len;i++)
				if(a[i]<ans)
					ans=S[i];
		printf("%c\n",ans);
        //输出char类型时用%c
	}	
```


---

## 作者：DottedCalculator (赞：2)

**简要题意：**

你有一个两位或以上的正整数。每次操作你必须交换任意不相同的两位，随后删除最后一位。当数只剩一位时操作结束，求剩下数位的最小值。

**解法：**

很明显，本题是一道**贪心和策略问题**，可以试着分两种情况讨论。

当 $10 \le n \le 99$ 时，需要进行操作的数是两位数，所以唯一可能的操作是将个位与十位交换后删除修改后的个位。故答案总是原数的个位。

否则，最终的答案恒为原数中最小的数位。操作方法可以考虑每次将最小的数位交换到最后第二位，这样可以保证下一次操作其不可能留在最后一位而被删除。

举一个例子，比如输入为 $12345$ 可以按照以下方式操作：

$12345 - 42315 - 4231 - 4213 - 421 - 412 - 41 - 14 - 1$

最后附上AC的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	string s;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		if(s.length()<=2){
	    cout<<s[1]<<endl;
	    continue;
	}
		int ans=999;
		for(int j=0;j<s.length();j++)     ans=min(ans,int(s[j]));
		cout<<ans-48<<endl;
	}
	return 0;
} 
```


---

## 作者：zhicheng (赞：2)

### 分析

由于 `Alice` 先手，她必须要交换某两个数位，所以如果这个数只有两位，那么最后的答案只能为第二位上的数。否则，容易看出一定存在一种方案，可以使答案为所有数位上最小的那个数。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[10];
int main(){
	int n,minn;
	scanf("%d",&n);
	while(n--){
		minn=9;
		memset(a,0,sizeof(a));
		scanf("%s",a);
		if(strlen(a)==2){  //特殊情况
			printf("%d\n",a[1]-'0');
			continue;
		}
		for(int i=0;i<=strlen(a)-1;i++){
			minn=min(minn,a[i]-'0');  //取最小
		}
		printf("%d\n",minn);
	}
}
```

---

## 作者：云裳 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1684A)


这种题要**分情况讨论**：


------------


如果这个整数是两位数，那么显而易见，

只能先将是位于个位的数和位于十位的数交换，留下个位。


------------

如果不是，
只要先把**最小数**调到**次高位**（最后只能保留最高位）,

接着随便交换其他数字，

最后在只有数字两位的时候把最小数调到**最高位**。

以 98123 为例，这是操作过程：

- 98123
- 9182（调到次高位）
- 819
- 91
- 1



------------

于是，我们得到了结论：

**如果这个数是两位数，就输出末尾；如果不是，就输出最小的数字**。




代码：

------------
```cpp
#include<bits/stdc++.h>
#define maxn 1000010
#define INF 0x7fffffff
typedef long long ll;
using namespace std;
ll read() {//快读
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
void write(ll x) {//快输
	if(x<0) {
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int main() {
	ll t=read();
	while(t--){
		char s[maxn];
		cin>>s;//我用的字符数组，这样好找出数字里面的最小数 
		ll minn=INF;//最小值 
		ll len=strlen(s);//长度 
		if(len==2){//如果数字是两位数 
			cout<<s[len-1]<<endl;//输出末尾 
			continue;
		}
		//不然找出最小值 
		for(ll i=0;i<len;i++) minn=min(minn,ll(s[i]-'0'));
		// -'0': 将字符变成数字
		// ll: 将数字转化成 long long 类型 
		write(minn);//输出 
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：IANYEYZ (赞：1)

一道很明显的结论题。

先把结论摆出来：当 $n<100$ 时，答案为 n 的个位，否则，答案为 n 的各位中最小的数。

那这是为什么呢？~~请自己证明~~我们先来看 $n<100$ 时，很明显，由于 Alice 必须要交换，答案一定是 n 的个位。

而当 $n>100$ 时，我们先来考虑贪心，也就是第一步把最小值扔到首位，后面就乱搞，所以答案就是最小值，交上去，过了！！！

~~完结撒花~~

但这样真的对吗？

别急，我们来手玩一组数据 $n=\texttt{213}$

$213\Rightarrow12\Rightarrow2$ 

呀，不对。

为什么呢？问题就在于我们把最小值换上去之后，到了 n 只有两位时就会把最小值删去。

那么正确的策略是什么呢？其实就是最开始时把最小值换到第二位，不过答案也是一样的。

代码很简单，就不写注释了

```
#include<iostream>
#include<cstring>
using namespace std;
int t;
long long n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n/100 >= 1)
		{
			int mmin = 10;
			while(n != 0)
			{
				mmin = min(1ll*mmin,n%10);
				n/=10;
			}
			cout<<mmin<<endl;
		}
		else
		{
			cout<<n%10<<endl;
		}
	}
}
```


---

## 作者：Lyria (赞：1)

## 题目大意

$A$ 与 $B$ 在玩一种游戏。$A$ 为先手，他的任务是交换给定你的 $s$ 中的任意两个**不同位置的整数**的值，$B$ 的任务是删除 $s$ 中的最后一位，假设 $A$ 玩得足够好，求最后剩下的整数的最小值。

## 题目思路

$1.$ $s_{len}$ 为 $2$，此时因为 $A$ 是先手，必须要交换 $s_1$ 与 $s_2$，所以答案显然是 $s_2$。 

$2.$ 我们可以先看看 $s_{len}$ 为 $3$ 的情况，例如```1 2 3```，此时我们希望把 $1$ 留下，则先交换 $1$ 与 $2$，此时 $s$ 为```2 1 3```，$B$ 删除最后一位 $3$，$s$ 为```2 1```,此时就转换成了第 $1$ 种情况，答案为最小值 $1$。可以发现无论值为多少，通过 $B$ 的减，总能让最后 $s_{len}$ 等于 $3$，$A$ 就只需浪费次数（一直交换 $s_{len}$ 与 $s_{len-1}$），只要保证最小值在第一位即可将答案转化成我们希望的 $s$ 中的最小值，也就是说 $s_{len}$ 无论是多少，只要将 $s_{min}$ 交换至第一位即可，这又恰好利用了 $A$ 为先手的特点，所以答案为 $s_{min}$。

## 题目代码

```
t=int(input())
while t!=0:
    t-=1
    s=input()
    if len(s)==2:#第一种情况
        print(s[1])
    else:#第二种情况
        print(min(s))
```

---

## 作者：落花月朦胧 (赞：1)

# 题意

给出一个小于 9 位的整数。

有两个操作，可以把任意两个数字交换或者去掉最后一位数字。 求操作之后这个数的最小值。

第一次操作只能是交换两个数字。

# 题解

可以分类讨论一下。

如果这个整数的位数大于 2，那一定可以删数直到最小值，反之如果这个整数的位数是 2 位，那第一此操作就会是这个数反转，第二次操作后就只剩下了这个数的第二位。

实现的话用 `string` 比较方便。

```cpp
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int inf = INT_MAX;
constexpr i64 lnf = LONG_LONG_MAX;

void solve() {
	string a;
	cin >> a;

	int n = a.size();

	if (n <= 2) {
		cout << a[1] << '\n';
		return;
	}

	auto ans = '9';
	for (auto i : a) {
		ans = min(ans, i);
	}
	cout << ans << '\n';}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		solve();
	}

	return 0;
}
```

---

## 作者：wangyibo201026 (赞：1)

## 题目大意

Alice 和 Bob 在玩一个数列游戏，整个数列有 $n$ 个数。Alice 是先手，并且游戏是轮流制的。

到 Alice 时，她必须交换两个**不同位置**的数。到 Bob 时，他必须去掉整个数列的最后一位数。当整个数列只剩下一个数时，游戏结束。

你需要找到游戏结束时，可能剩下的最小的数。

## 题目思路

容易看出，如果想要结果尽可能小的话，就要把小的数尽量往前移，我们发现，在**普通**情况下，可以把任意一个数移到最前面，然后就不断作其余元素的交换操作。我们就可以把最小的数移到最前面，这样就可以保证答案最小！

然而 CF 是良心又良心的。我们再想一下，如果 $n = 2$ 并且最小值已经在第一个时呢？这时，我们发现，无论怎么移动，最后的结果只会是第二个数，这是唯一一种特例！（这里说良心是因为第一个样例就已经指出这个问题了！）

## 代码

```cpp
#include<bits/stdc++.h>

#define endl '\n';

using namespace std;

int t;

void Solve(){
  cin >> t;
  while(t--){     // t 组数据
    int mini = 1e9, pos;
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i++){
      if(s[i] - '0' < mini){     // 记录位置
        mini = s[i] - '0';
        pos = i;
      }
    }
    if(s.size() == 2 && pos == 0){    // 特例
      cout << s[pos + 1] << endl;
    }
    else{
      cout << mini << endl;
    }
  }
}

int main(){
  Solve();
  return 0;
}
```

---

## 作者：郑朝曦zzx (赞：0)

# 解题思路

考虑分类讨论

1. 如果这个数 $10\le n\le99$

那么按照规则必须交换，即使是很亏的，此时答案是各位数字。

2. 如果 $100\le n$

那么答案的**理论最小值**就是这个多位数最小那一位的值。

证明理论最小值一定能达成：

构造：

- 把最小值放到正数第二位上
- 然后随便移动
- 直到删得只剩两位时把最小值移动到首位

# 代码
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int t;
string str;
int main()
{
	scanf("%d", &t);
	for (int i = 1; i <= t; ++i)
	{
		cin >> str;
		if (str.length() == 2)
		{
			printf("%c\n", str[1]);
			continue;
		}
		else
		{
			int mn = str[0] - '0';
			for (int j = 1; j < str.length(); ++j)
				if (str[j] - '0' < mn) mn = str[j] - '0';
			printf("%c\n", mn + '0'); 
		}
	}
	return 0;
}
```


---

## 作者：Kevin0007 (赞：0)

分析：

如果这个数是两位数，那么输出个位的数字。因为必须交换一次，那么十位的数字一定会被删掉，而个位的数字一定会被留下。

如果这个数不是两位数，那么输出各位数字中最小的一个，因为将最小的一个交换到最前面即可让它留下。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
string s;
int main(){
  cin>>T;
  while(T--){
    int ans=10;
    cin>>s;
    if(s.size()<=2) cout<<s[s.size()-1]<<endl;
    else{
      for(int i=0;i<s.size();i++) ans=min(ans,s[i]-'0');
      cout<<ans<<endl;
    }
  }
  return 0;
}
```


---

## 作者：BlackPanda (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF1684A)**

------------
### 题意：
给出一个整数 $n$ 并进行操作，每次操作交换任意不同位置的两位，然后删除末位，当 $n$ 只剩一位时结束操作，求 $n$ 剩下最后一位的最小值。

------------
### 思路：
这道题可以进行分类讨论，先设 $x$ 等于 $n$ 的数位，可以得到：

- 当 $x = 2$ 时，设原数为 $ \overline {ab}$，只能进行一次操作，即交换十位和个位，原数变成 $ \overline {ba}$，然后删除现有的个位，变成 $ \overline b $，所以答案就是原数的个位。

- 当 $x > 2$ 时，要使得最后剩下的一位为最小值，可以在每次把最大值交换到最后，使得每次删除的数位是当前数字中数位的最大值，所以最终的答案就是原数中数位的最小值，即：$min(a_1,a_2,...,a_{n-1},a_n)$。

------------
### code：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;

int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	string st;	//为了方便取数位，可以用 string 来存 
	while(t--){
		cin>>st;
		int len=st.length();
		if(len == 2){
			cout<<st[1]<<endl;
		}
		else{
			int minn=10;
			for(int i=0;i<len;i++){
				minn=min(minn,st[i]-'0');
			}
			cout<<minn<<endl;
		}
	}
	return 0;
}


```

---

## 作者：封禁用户 (赞：0)

简单到不能再简单的贪心。

首先将数字看成字符串。

首先特判长度为 $2$ 的情况，样例 $1$ 第 $1$ 组数据说了，简单想一下就会得到需要输出最后一个字符。

然后长度为 $1$，输出唯一一个字符。

其他情况大家可以自己造样例试去，最后得到结果就是输出最小的数字。

就这么简单？？？你没看错，这只是一个第一题。

关于为什么输出最小就可以通过，我认为是每个字符都可以任意交换和删除，那这样 Alice 和 Bob 可以实现留下任何一个字符作为最终的结果，所以在这样离谱的情况下，我们输出最小的，也就是最正确的。

然后是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
string k;

int main(){
    cin>>t;
    while(t--){
        cin>>k;
        if(k.length()==2){ // 特判
            cout<<k[1]<<endl;
            continue;
        }
        else if(k.length()==1){ // Cu Up
            cout<<k[0]<<endl;
            continue;
        }
        else{
            char min=k[0]; // 将 k[0] 作为 ”擂台变量“ 的初始值。
            for(int i=1;i<k.length();i++)
                if(min>k[i])min=k[i]; // 找最小
            cout<<min<<endl;
        }
    }
    return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

我们发现，当数字的位数大于等于 $3$ 时，Alice 可以做到让任意数位留下来。因为她可以将任意数字交换到末位，而 Bob 能且只能删除末位。

因此，当位数大于等于 $3$ 时，正确答案就是这个数字中最小的数位。

而位数等于 $2$ 时，Alice 必须交换一次。因此，此时的答案是这个数字的末位（Alice 将原来的末位交换到了首位，原来的首位也就是交换后的末位被 Bob 删除）。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		if(n<100)//只有两位的情况
		{
			printf("%d\n",n%10);
			continue;
		}
		int ans=10;
		while(n)
		{
			ans=min(ans,n%10);
			n/=10;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：ZZQF5677 (赞：0)

### 解题思路
除了两位数的交换时必须交换掉一个数从而导致最小的是原来的个位数，其他的三位数及以上最后都会进入 $\tt{xyz}\to{\color{red}{xy}}{z} \to \tt{yxz} \to \tt{yx}{\color{orange}{z}} \to {yx} \to {\color{red}{yx}} \to {xy} \to {x}{\color{orange}{y}} \to {x}$ 的过程（假设 $\tt x$ 是最小值，标红色的是交换，橙色的是删除），那么我们如何证明 $\tt x$ 是最小的数呢：我们一开始就将 $\tt x$ 交换到第一位，然后你不管怎么交换怎么删除都不去动，直到只剩下 $3$ 位数时。

用以上证明，我们可以得知，两位数最小的数是原来的个位数，三位数最小的数是一开始时所有书中的最小数。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long read() {
  long long x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0', ch = getchar();
  }
  return x * f;
}
long long t, n, ans;
int main() {
  t = read();
  while (t--) {
    ans = 9;
    n = read();
    if (n >= 10 && n <= 99) {
      printf("%lld\n", n % 10);
    } else {
      while (n) {
        ans = min(ans, n % 10);
        n = n / 10;
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

$0$ 分 $4$ 秒开始。

![](bilibili:BV15U4y127QD)

### 2 思路

很明显的，如果这个数字有 $1$ 位，就不用操作；有 $2$ 位，就输出最右边的那个数字，因为 `Alice` 必须要进行交换操作。

那么，如果这个数字有 $3$ 位或更多，可以选择任意一个数留下来（当然是最小的那个），因为 `Alice` 可以每次让最小的放到倒数第 $2$ 个（如果本来就在了，就交换其他的数字）。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
char s[12];
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1684A_1.in","r",stdin);
	freopen("CF1684A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%s",s+1);
		ans=9;
		if(strlen(s+1)<=2){
			printf("%c\n",s[strlen(s+1)]);
			continue;
		}
		for(int i=1,len=strlen(s+1);i<=len;++i){
			if(s[i]-'0'<ans)ans=s[i]-'0';
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/76116110)

By **dengziyue**

---

## 作者：sickbot (赞：0)

## 题意
- 有多测

给你一个数 $n$，每次 Alice 交换不同位置的两位，Bob 删除末位，问剩的最后一位的最小值。（Alice 先手，轮流进行）
## 思路
显然，Alice 能得到的最小值为 $n$ 中最小的一位（见下文）。

注意：此性质对于 $10 \le n <100$ 不成立，因为此时必须交换两位，所以答案是 $n$ 的个位。
## 简短的证明
显然，只要 $n$ 不少于三位，Alice 就可以采取以下的方法来使最后的值最小：

- 在第一回合将最小的那位调到从前数第 2 位；
- 在接下来的几回合中调动其他位；
- 在只剩 2 位时，交换这两位的位置。

## Code
```cpp
signed temp__main()
{
    i64 n;
    cin>>n;
    if(n<100) return cout<<n%10<<endl,0;
    i64 minn=10;
    for(;n;n/=10) minn=min(n%10,minn);
    cout<<minn<<endl;
    return 0;
}
```



---

## 作者：water_three (赞：0)

### 题目大意：
Alice 和 Bob 正在玩一个游戏，现在有一个正整数 $n$。每一轮中，Alice 必须交换位于不同位置的任意两位数字，Bob 则总是删除整数的最后一位。

问在最优条件下，Alice 最后能得到的最小整数。

### 思路：
由样例我们可以猜测，最后那个剩下的数字只与一串数字中最小的或次小的有关。

### 证明：
第一次操作时，Alice 先将最小的数交换到最前面，然后随便操作。当只剩最后三个数时将最小数移到第二个位置，最后一次操作后得到的数必定是最小的数。

### 注意：
当 $n$ 为两位数时直接特判。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		int MIN=100,MIN2=100; 
		for(int i=0;i<s.size();i++){
			if(s[i]-'0'<MIN)MIN=s[i]-'0';
			else if(s[i]-'0'<MIN2)MIN2=s[i]-'0';
		}
		if(s.size()==2)cout<<s[1]-'0'<<endl;
		else cout<<MIN<<endl;
	}
} 
```


---

## 作者：Failure_Terminator (赞：0)

## Problem

有一个十进制表示形式中没有零的整数 $n$。

Alice 和 Bob 正在用这个整数玩游戏。

Alice 先开始，他们轮流玩游戏。

轮到 Alice 时，她必须交换位于整数不同位置的任意两位数字。

轮到 Bob 时，他需要去掉整数的最后一位。

当只剩下一个数字时，游戏结束。

如果 Alice 采用了最佳策略，你需要求出她最终能得到的最小整数。

## Solution

设 $len$ 为数字 $n$ 的长度。

当 $len = 1$ 时，游戏直接结束，Alice 能得到的即为 $n$ 本身。

当 $len = 2$ 时，Alice 必须将两位数交换，最后剩下的就一定是后一位。

当 $len$ $\ge$ $3$ 时，Alice 必然可以将最小的数放置到数的第一位，最后剩下的就一定是 $n$ 中最小的一位。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string n;
void solve(){
    cin>>n;
    if(n.size()==2) cout<<n[1]<<'\n';
	else cout<<*min_element(n.begin(),n.end())<<endl;
}
int main()
{	
	cin>>t;
	while(t--) solve();
    return 0; 
}
```

### 注释

```cpp
cout<<*min_element(n.begin(),n.end())<<endl;
```

这句话可能有些不好理解，但是在这里它等价于：

```cpp
char c=s[0];
	for(int i=1;i<s.size();i++)
		if(c>s[i]) c=s[i];
	cout<<c<<endl;
```

还不明白的可以看[这里](https://blog.csdn.net/weixin_38505045/article/details/88656453)。

By **haimo**

---

## 作者：TheSky233 (赞：0)

## Description

给定一个整数 $n$ 和两种操作。

1. 交换任意两个数位的值。

2. 删除最后一个数。

求出 $n$ 在若干次 $\tt 1$ 和 $\tt 2$ 操作后能取得的最小数值。

## Solution

为了方便，我们把这个整数当做**字符串**读入。

显然，如果这个最小值出现在最后一位，那么直接输出这个最小值即可。

设字符串长度为 $l$，可以想象成：

1. 它移到 $l-1$ 位。
2. 删了第 $l$ 位。

重复上述过程，最后求出的即为最小值。


------------

为了让最小值在某回合结束后在最后一位，我们可以刻意交换前面的数值，等到删除到它后面一位时，做上述操作。

- 注意特判原长 $l = 2$ 的情况，这种情况只能先交换，再删除。

## Code

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

typedef pair<int,int> pii;
#define F(i,a,b) for(int i=a;i<=(b);++i)
#define MN 300005
#define MM 600005
#define ll long long
#define mod 998244353
#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define mkp make_pair
#define fi first
#define se second

void Solve();

int main(){
	int tests=1;
	scanf("%d",&tests);
	while(tests--)
		Solve();
	return 0;
}

int n,m;
string s;

void Solve(){
	int Min=10;
	cin>>s;
	if(s.length()==2) printf("%d\n",s[1]-'0');
	else{
		for(int i=0;i<s.length();i++) Min=min(Min,s[i]-'0');
		printf("%d\n",Min);
	}
}
```

---

