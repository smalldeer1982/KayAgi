# Even-Odd XOR

## 题目描述

给定一个正整数 $n$，请你找出一个长度为 $n$ 数组 $a$，满足数组是由互不相同的非负且小于 $2^{31}$ 的整数组成，并且该数组中奇数项上元素的[异或和](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)与偶数项上元素的异或和要相等。

## 样例 #1

### 输入

```
7
8
3
4
5
6
7
9```

### 输出

```
4 2 1 5 0 6 7 3
2 1 3
2 1 3 0
2 0 4 5 3
4 1 2 12 3 8
1 2 3 4 5 6 7
8 2 3 7 4 0 5 6 9```

# 题解

## 作者：SilviaLss (赞：22)

两句话题解，不需要任何 if 语句

奇数和偶数位置异或和相等是全局异或和为 $0$ 的充要条件，那么你考虑构造出前 $n-1$ 个数，第 $n$ 个数就可以直接推出来。

第一思路是 $1,2,...,n-1,a_n$，但是这样可能会重复，所以我们可以做点手脚，具体的，别的不变，令 $a_{n-2}=2^{23},a_{n-1}=2^{24}$，就可以了。

还是加一个证明吧: 前 $n-3$ 个数显然不会重复。$a_{n-2}$ 是 $2^{23}$ 级别的。$a_{n-1}$ 是 $2^{24}$ 级别的。$a_n$ 是 $2^{23}+2^{24}$ 级别的。

```cpp
int w=0;
for(int i=1;i<=n-3;i++)cout<<i<<" ",w^=i;
cout<<(1<<23)<<" "<<(1<<24)<<" "<<(w^(1<<23)^(1<<24));
```

---

## 作者：flying_man (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF1722G)

以此记录我最后一分钟A掉G题

------------

我的思路跟大部分人都不太一样。

我不管最后异或完的结果是什么，我只管奇数项和偶数项的异或和相等即可。

所以对于奇数项，我们随便填上一些数字（准确来说也不是随便，我们要求填的数字的二进制位数相等，否则会影响接下来的操作）。如果 $n$ 是奇数，奇数项就会有一个剩余，我们填上 $0$ 即可。

接下来就是最重要的环节：填偶数项！这里文字不太好演示，我们画图说明。

![](https://cdn.luogu.com.cn/upload/image_hosting/i4pfi54a.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

假设奇数项用二进制表达为 $100$、$101$、$110$、$111$。

偶数项在对应的奇数项的最高位上再添两位，至于为什么不能是一位，稍后再说。

这样的话最高两位的 $11$ 全部抵消掉，偶数项异或和自然等于奇数项异或和。

再看如下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/bjmfphes.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

如果我们去掉 $111$，在填上偶数项时，我们会发现，最后一个数的最高两位消不掉。怎么办？

其实也好办。我们把倒数第二个数的最高两位变成 $10$，把最后一个数的最高两位变成 $01$，这样无法消的问题就迎刃而解了。

这时候我们就明白了为什么要设两位。

![](https://cdn.luogu.com.cn/upload/image_hosting/7p6tzy5l.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

如果我们添一位，遇到这种情况只能这样处理，但这样处理奇偶项的最后一个数会矛盾。

当然还有特殊情况 $n = 3$，特判即可。

构造完成，代码就好写了！

------------
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],xby;
int gs(int n){
	int cnt = 0;
	while(n){
		n >>= 1;
		cnt++;
	}
	return cnt;
}
int main(){
	cin >> t;
	while(t--){
		cin >> n;
		if(n == 3){
			cout << 2 << ' ' << 1 << ' ' << 3 << endl;
			continue;
		}
		xby = 1<<gs(n);
		for(int i = 1;i <= n-n%2;i += 2){
			a[i] = xby+i/2;
		}
		if((n-n%2)%4 == 0){
			for(int i = 2;i <= n-n%2;i += 2){
				a[i] = a[i-1]+(1<<gs(a[i-1]))+(1<<(gs(a[i-1])+1));
			}
		}
		else{
			a[n-n%2] = a[n-n%2-1]+(1<<gs(a[n-n%2-1]));
			a[n-n%2-2] = a[n-n%2-3]+(1<<(gs(a[n-n%2-1])+1)); 
			for(int i = 2;i <= n-n%2-4;i += 2){
				a[i] = a[i-1]+(1<<gs(a[i-1]))+(1<<(gs(a[i-1])+1));
			}
		}
		for(int i = 1;i <= n;i++){
			if(i == n && n%2 == 1) a[i] = 0;
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Dr_Gilbert (赞：4)

# CF1722G Even-Odd XOR

【题目大意】

给定整数 $n$，请你构造一个长为 $n$ 且每个元素都是在 $[0,2^{31})$ 范围内的整数数列，满足：

- 数列中元素互不相同。
- 数列中奇数下标的数的异或和与数列中偶数下标的数的异或和相等。

若有多组解，你可以输出任意一组。

---

注意到题目的限制非常松，意味着可能各种各样的算法都能通过。于是我们不妨考虑随机化，对前 $n-2$ 个位置的数随机赋 $[0,2^{31})$ 内的权值，赋值的同时记录奇数位置和偶数位置上的异或和，然后按照 $n$ 的奇偶性把两个异或和分别放在 $n-1$ 位置和 $n$ 位置即可。

然后考虑数列中元素互不相同的限制，只需要用 `map` 记录某个数是否出现过即可。如果当前的权值已经出现过则重新随机一个权值。如果最后奇数位置和偶数位置的异或和相等，则考虑修改第 $n-2$ 个数使异或和变得不等。如果异或和在原序列中出现过，则将两个异或和都异或上某个随机数即可。

由于数列长度只有 $n$，而值域远远大于 $n$，所以在赋值过程中出现冲突的概率很小，造成的额外计算也很少，所以时间复杂度约为 $O(n)$ ，可以稳定通过。

```cpp
// 这份代码并未考虑奇偶位上异或和相等的情况
// 具体实现与题解中略有不同
#include <bits/stdc++.h>
using namespace std;
unordered_map<int,int> mp;
const int mod=2147483647;
const int N=2e5+10;
int val[N];
int main(){
	mt19937 rnd(time(0));
    // 不建议使用 rand() 随机性较差
    // 值域也很小 远不能达到随机化的随机要求
	int t;cin>>t;
	while (t--){
		int n,val1=0,val2=0;cin>>n;
		mp.clear();
		for (int i=1;i<=n-2;i++){
			int x=rnd()%mod+1;
			while (mp[x]) x=rnd()%mod+1;
			val[i]=x;mp[x]=1;
			if (i&1) val1^=x;else val2^=x;
		}int t=0;
		while (mp[val1]||mp[val2]){
			t++;val1^=t;val2^=t;
		}
		if (n&1) val[n-1]=val2,val[n]=val1;
		else val[n-1]=val1,val[n]=val2;
		for (int i=1;i<=n;i++) cout<<val[i]<<' ';
		cout<<endl;
	}return 0;
}
```



---

## 作者：naroto2022 (赞：3)

# CF1722G 题解

### 题意

给定一个正整数 $n$，要求构造一个长度为 $n$ 的数组，使得数组的奇数项的异或和等于偶数项的异或和。

有多组数据。

### 前置知识

位运算，知道 $a\oplus a=0,0\oplus a=a$。

### 思路

注意到，题目要求每个数各不相同，于是想到可以让数组为 $1,2,3,\cdots,n-1,a_n$。前面几个为各不相同的数，最后一个简单处理下即可。

但是！这样会重复，$a_n$ 可能会和前面的数重复，所以令 $x=1\oplus2\oplus3\oplus\cdots\oplus(n-3)$，则让数组为 $1,2,3,\cdots,n-3,2^{18},2^{19},x\oplus2^{18}\oplus2^{19}$。于是，就快乐地 AC 啦~~~

等等，没结束，你还没告诉我这为啥就不重复了捏？

因为，打开计算器，发现 $2^{18}=262144,2^{18}>2\times10^5$，所以，前面的 $(n-1)$ 个数是互不相同的（因为 $n\leqslant2\times10^5$），而 $x\leqslant2\times10^5$，所以最后一个数是不等于前面的任何一个数的，而且它大于 $2^{19}$。

等等！我还有疑问，为啥这是正确的捏？

其实也非常简单，有前置知识，任意一个实数 $a$，有 $a\oplus a=0,0\oplus a=a$，而我们知道，和最后一项同奇偶的项数的异或和为 $2^{19}\oplus$ 所有数字小于 $2^{18}$ 且与最后一项异奇偶的所有数的异或和；和最后一项异奇偶的项数的异或和为 $2^{19}\oplus$ 所有数字小于 $2^{18}$ 且与最后一项异奇偶的所有数的异或和。两者相同。

再等等！我懂了结论的正确性了，但你是咋推出来的呢？

很简单，要学会偷懒！做题肯定想要特殊处理的少，那既然 $1$ 个不行，那就试试 $3$ 个呗！而异或要是两个数在二进制下有一位有且只有一个为 $1$ 的情况下，就为 $1$，而大于一个数的数一定与这个数不同，于是就考虑大于 $2\times10^5$ 的 $2$ 的指数幂，就出来啦~

哦，结束了，都懂了，上代码喽！

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long T,n,x,num=1<<18;//大于200005的第一个二次方幂。
int main(){
	scanf("%lld",&T);
	while(T--){
		x=0;//注意初始化！
		scanf("%lld",&n);
		for(int i=1; i<=n-3; i++){
			printf("%lld ",i);
			x^=i;
		}
		printf("%lld %lld %lld\n",num,num<<1,x^num^(num<<1));
	}
	return 0;
} 
```


---

## 作者：sixrc (赞：3)

提供一种基于样例的无脑构造方法。

先考虑一种普通的构造：我们知道对于 $2k$ 和 $2k+1$，它们在二进制表示下只在最后一位不同。所以在 $n$ 为 $4$ 的倍数的情况下，从 $2$ 开始输出到 $n+1$ 即可，

当 $n \bmod 4=1$ 时，最后一位输出 $0$ 即可。

但我们发现上述构造方法无法直接拓展到 $n \bmod 4=2$ 的情况。考虑稍微改变一下，从 $i=1$ 到 $i=n-6$ 都按照上述方式构造，即从 $2$ 输出到 $n-5$，因为此时 $n-6$ 一定是 $4$ 的倍数；对于最后 $6$ 位，为了保证所有数互不相同，我们输出当 $n=6$ 时一组合法的解，并把每个数加上 $2^{29}$（或者 $2^{28},2^{30}$ 都行，保证和前面的数不相同就行了）。$n=6$ 的一组合法解样例已经给出，所以直接复制样例即可（）

$n \bmod 4=3$ 的情况就还是多输出一个 $0$ 即可。

---

## 作者：RevolutionBP (赞：3)

~~晚上做完核酸太困了场上没过，写份题解警示自己一下。~~

题意就是构造一个序列满足奇数位异或和等于偶数位。

此时我们可以采用微调法，容易发现可以将前 $n-2$ 位随便填，然后记录下前面填的数的异或和，让最后两位填上一个适合的数即可。

那么前 $n-2$ 位可以直接填 $1\sim n-2$，然后把重担留给最后两位，这时候又会发现如果前面的数异或和相等，那么最后两位的数也一定相等，不符合题意。

所以不妨让第 $n-2$ 位特殊构造一下，填一个 $1919810$，然后让最后两位填上 $s1 \text{ xor } 2^{31}-1$，和 $s2 \text{ xor } 2^{31}-1$。

ps:其实你前面填的数只要不容易冲突，填啥都行。

这道题目到这里就完成了，下面再放一下代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
inline void read(T &x) {
    x = 0; char c = getchar(); int f = 0;
    for (; !isdigit(c); c = getchar()) f |= (c == '-');
    for (; isdigit(c); c=getchar()) x = x * 10 + (c ^ 48);
    if (f) x = -x;
}
template <typename T, typename ...Args>
inline void read(T &x, Args &...args) {
    read(x), read(args...);
}
template <typename T>
inline void write(T x, char ch) {
    if (x < 0) putchar('-'), x = -x;
    static short st[30], tp;
    do st[++tp] = x % 10, x /= 10; while(x);
    while (tp) putchar(st[tp--] | 48);
    putchar(ch);
}
template <typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    static short st[30], tp;
    do st[++tp] = x % 10, x /= 10; while(x);
    while(tp) putchar(st[tp--] | 48);
}
inline void write(char ch){
    putchar(ch);
}
template <typename T, typename ...Args>
inline void write(T x, char ch, Args ...args) {
    write(x, ch), write(args...);
}
#define Fr(i, a, b) for(int i = (a); (i) <= (b); ++i)
#define Rf(i, a, b) for(int i = (a); (i) >= (b); --i)
const int N = 2e5 + 5;

int n, m, T, k;
int l, r, len, res;
ll ans;
int a[N];

inline void solve() {
    int val1 = 0, val2 = 0;
    read(n);
    Fr (i, 1, n - 3) a[i] = i;
    Fr (i, 1, n - 3) {
        if (i & 1) val1 ^= a[i];
        else val2 ^= a[i];
    }
    a[n - 2] = (1 << 30) - 1919810;
    a[n - 1] = (1 << 30) - 114514;
    if ((n - 1) & 1) val1 ^= a[n - 1];
    else val2 ^= a[n - 1];
    if ((n - 2) & 1) val1 ^= a[n - 2];
    else val2 ^= a[n - 2];
    a[n] = val1 ^ val2;
    Fr (i, 1, n) write(a[i], ' ');
    cout << endl;
}
signed main(){
    srand(time(NULL));
    read(T);
    while (T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：Miraik (赞：3)

被 @Cocoly1990 点名的虚假做法。

容易发现对于一个偶数 $i$ 有 $(i \oplus (i+1)) = 1$（我们用前向星写割桥的时候就利用了这一结论）

那么有一个很好的想法就是可以 $4$ 个 $4$ 个的配对，正确性是显然的，只需要考虑 最后 $n \bmod 4$ 个怎么办。

其实也很好办，先特判一下 $n=3$，再直接把最后 $4+ (n\bmod 4)$ 个数拉出来单独处理一波。

怎么处理？不用像我这个憨憨一样手推（虽然也很好推），因为样例都把答案贴在你脸上辣！

[code](https://codeforces.ml/contest/1722/submission/170388260)

---

## 作者：ZhaoV1 (赞：1)

# Even-Odd XOR
The knowledge points in this problem are valuable !\
**XOR** means : if $A=5$, $B=7$, then check the bits in binary separately express as "$101$" and "$111$", then the answer of $A⊕B$ is $2$ , "$010$" in binary.\
（XOR：按位异或与^）

**知识点①：** 要求数组奇数位的 XOR 结果与偶数位的 XOR 结果相同，即是要达到所有位数的 XOR 结果为 $0$。举个例子：分别要求奇数位和偶数位 XOR 结果都为 $2$，由于 XOR 的特性，$2⊕2$ 的结果为 $0$，所以可以将问题转化为：构造一个使这个数组所有元素 XOR 结果为 $0$。

**知识点②：** 想要构造一个又完全不同的数字构成的数组使得其 XOR 结果为 $0$，我们只要着重于其中 $3$ 个数字的构造即可。\
举个例子：
```
9 (数字个数)
1 2 3 4 5 6 ? ? ?
```
上述数字 XOR 的结果为 $7$，在二进制中为 "$111$"，那么我们定义自 $1$ 开始逐加无法达到的数字 $2×10^5+1$ 和 $2×10^6+1$，只需要将这两个固定的数 XOR 结果，所得到的值就是最后一个数字的答案 $ans$。

我从这道题中受益良多，希望我将来能好好利用这道题知识点。（写了一点英文的原因是我马上要考四级了，练一练翻译）

Code
------------
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n;

void solve(){
	cin >> n;
	int ans = 1;
	if(n == 3){
		cout << 1 << " " << 2 << " " << 3 << '\n';
		return;
	}else cout << 1 << " ";
	
	for(int i=2;i<=n-3;i++){
		cout << i << " ";
		ans ^= i;
	}
	cout << 2e5+1 << " " << 2000001 << " ";
	ans ^= 200001; ans ^= 2000001;//前面的数字一定到达不了2e5以上。
	cout << ans << " " << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：_Mortis_ (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1722G)

# 题意

构造一个序列，满足序列中的数互不相同，并且奇数项和偶数项的异或和相等。

# 思路

一道很水的构造题。

什么奇偶项异或和相等都是骗你的，其实让所有数异或和为 $0$ 就行。

题目的限制非常松，各种填法都行，比如我们可以把前 $n-3$ 位填上 $1∼ n-3$，第 $n-2$ 位和 $n-1$ 位随便填两个大数，再记录下奇项的异或和为 $v1$，偶项的异或和为 $v2$，第 $n$ 位就是 $v1 \oplus v2$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200005],v1,v2;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>T;
    for(;T--;){
        v1=0,v2=0;
        cin>>n;
        for(int i=1;i<=n-3;i++){
            a[i]=i;
            if(i&1)v1^=i;
            else v2^=i;
        }
        a[n-2]=998244353;
        a[n-1]=1000000007;
        if((n-2)&1)v1^=a[n-2];
        else v2^=a[n-2];
        if((n-1)&1)v1^=a[n-1];
        else v2^=a[n-1];
        a[n]=v1^v2;
        for(int i=1;i<=n;i++)cout<<a[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
```


---

## 作者：yuheng_wang080904 (赞：1)

## 题意

给定一个正整数 $n$，请你找出一个长度为 $n$ 数组 $a$，满足数组是由互不相同的非负且小于 $2^{31}$ 的整数组成，并且该数组中奇数项上元素的异或和与偶数项上元素的异或和要相等。

## 思路

一开始构造时我的程序出现了一些 _小问题_ 。但是我看了 Jury 的构造后，发现了什么……

根据题意，我们知道构造出的所有数字的总异或和为 0。我们可以先将前 $n-2$ 个构造出来 $0,1,2,\cdots,n-3$。记所有数项上元素的异或和为 $x$，偶数项上元素的异或和为 $y$。如果 $x\neq y$，则我们可以设第 $n-1$ 个数为 $2^{31}-1$，则第 $n$ 个数为 $x\oplus y\oplus 2^{31}-1$，则明显的，我们可以证明这 $n$ 个数互不相等，而且明显的，异或和为 0。如果 $x=y$，那么将前 $n$ 个数改为 $1,2,3,\cdots$，那么这样就改变了 $y$ 的值，很明显现在 $x\neq y$，然后根据前面的思路构造即可。

## 代码
接下来放上我的代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        int x=0,y=0;
        for(int i=0;i<=n-3;i++){
            if(i%2==0)x^=i;
            else y^=i;
        }
        if(x==y){
            x=0,y=0;
            for(int i=1;i<=n-2;i++){
                cout<<i<<" ";
                x^=i;
            }
        }
        else for(int i=0;i<=n-3;i++)cout<<i<<" ";
        cout<<INT_MAX<<" "<<(x^y^INT_MAX)<<endl;
    }
    return 0;
}
```


---

## 作者：ScottSuperb (赞：1)

# 解法分析
赛后乱搞了一个做法 WA 了之后分析 CF 给的答案做出来的~~，调了好久~~。  
首先我们不管别的，从 $0$ 开始用连续自然数构造数列的前 $(n- 2)$ 项，边构造边记录奇数项和偶数项的异或和（用变量 $odd$ 和 $even$ 记录），然后判断二者是否相等。若相等，就不能熟视无睹了，因为这样末两个数一定是相等的，那么我们使数列从 $1$ 开始即可，记得异或和要再更新一次，因为两个异或和已相等，更新哪个都一样；若不相等，恭喜你，后面两个数不会相等，可以直接进行下一步了。  
对于数列的第 $(n- 1)$ 项，我们直接让它等于 $2147483647$，那么第 $n$ 项就是 $(2147483647\oplus odd\oplus even)$。这样它们的二进制前面会有很多 $1$，保证不会与前面的数相冲突。
# 代码
读写函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int t = read(), n, odd, even, flag, i;
	while (t--) {
		n = read();
		for (odd = even = 0, i = 0; i < n - 2; ++i)
			if (i & 1)
				even ^= i;
			else
				odd ^= i;
		if (odd == even)
			flag = 1, odd ^= i;
		else
			flag = 0;
		for (i = flag; i <= n - 2 - !flag; ++i)
			write(i);
		write(2147483647), write(2147483647 ^ odd ^ even);
		puts("");
	}
	return 0;
}
```

---

## 作者：251Sec (赞：0)

实际上就是要求所有数异或和为 $0$，当然你有一百万种直接构造的方法，但是我选择直接随。直接随机生成前 $(n-1)$ 个数，最后一个数设为前 $(n-1)$ 个数的异或和，则错误率不超过 $\frac{n-1}{V}$，非常松。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[200005], T, n;
mt19937 eng(363415);
int rnd() { return eng() % (1ll << 31); }
unordered_set<int> f;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		f.clear(), a[n] = 0;
		for (int i = 1; i < n; i++) {
			do a[i] = rnd(); while (f.count(a[i]));
			f.insert(a[i]), a[n] ^= a[i];
		}
		for (int i = 1; i <= n; i++) printf("%d%c", a[i], " \n"[i == n]);
	}
	return 0;
}
```

---

## 作者：GenesisCrystal (赞：0)

~~思路非常清奇~~

## Solution

这个算法只有当 $n > 6$ 是能够算出答案，所以我们需要打一个小小的表。

随后如果 $n$ 是奇数，那么我们可以在最前面先加上一个 $0$ 是的奇数个变成偶数个。

以下 $i$ 表示 $a$ 数组内的第 $i$ 个数（$a$ 中不包含上面输出的 $0$，故 $n$ 为偶数）。

然后我们将所有奇数位上的数字变成 $\lceil \dfrac{i}{2} \rceil$，使得一个变量 $Xor$ 变成 $\bigoplus \limits_{i=1}^{\frac{n}{2}}i$。

然后再令从 $2$ 到 $n - 6$ 之间的偶数位设成 $\dfrac{i + n}2$，变量 $Xor \gets Xor \bigoplus \limits_{i=1}^{\frac{n-6}2}\dfrac{2i+n}2$。

最后，还有 $n -4,n-2,n$ 这三个位置的数没有填，我们将 $n-4,n-2,n$ 分别添上 $2^{31}-1$（即 $2147483647$）、$10^9$、$2^{31}\oplus10^9\oplus Xor$ 。

## Code

```cpp
#include <cmath>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1;

int t, n;

int main() {
  for (cin >> t; t; t--) {
    cin >> n;
    if (n == 3) {
      cout << "2 1 3\n";
      continue;
    } else if (n == 4) {
      cout << "2 1 3 0\n";
      continue;
    } else if (n == 5) {
      cout << "2 0 4 5 3\n";
      continue;
    } else if (n == 6) {
      cout << "4 1 2 12 3 8\n";
      continue;
    }
    if (n & 1) {
      cout << "0 ";
      n--;
    }
    int ans[kMaxN], Xor = 0;
    for (int i = 1; i <= n / 2; i++) {
      ans[i * 2 - 1] = i;
      Xor ^= i;
    }
    for (int i = 1; i <= (n / 2) - 3; i++) {
      ans[i * 2] = i + n / 2;
      Xor ^= (i + n / 2);
    }
    ans[n - 4] = 2147483647;
    ans[n - 2] = 1000000000;
    ans[n] = 1147483647 ^ Xor;
    int x1 = 0, x2 = 0;
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << ' ';
      if (i & 1) {
        x1 ^= ans[i];
      } else {
        x2 ^= ans[i];
      }
    }
    cout << '\n';
  }
  return 0;
}
	 		  	 		 	 	   		   		 	  			//
```

---

## 作者：_QyGyQ_ (赞：0)

题目要求构造一个奇数位上异或和与偶数位上异或和相等，所以我们可以得知整个序列的异或和为零，并且要保证每个数字不相同。我们可以把前 $n-3$ 个数赋值成 $1,2,3,\dots,n-3$ 再把倒数第三个数赋值为 $2^{29}$，接着把倒数第二个数赋值为 $2^{30}$ 最后一个数就是前面所有数的异或和。为什么要用两个大数呢？如果不用大数结尾，可能会导致最后一个数与前数重复。如果仅仅用一个大数，若这个大数的前面几个数异或和为零，那么就会导致最后一个数与这个大数相等。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
int a[N];
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int sum=0;
		for(int i=1;i<=n-3;i++){
			cout<<i<<" ";
			sum^=i;
		}
		int a=1<<29,b=1<<30;
		cout<<a<<" "<<b<<" "<<(sum^a^b)<<"\n";
	}
	return 0;
}
```


---

## 作者：Disjoint_cat (赞：0)

## [CF1722G Even-Odd XOR](https://codeforces.com/problemset/problem/1722/G)

### 题意

- 给出 $n$，构造一个长度为 $n$ 的数列 $a$，满足

	- $0\le a_i<2^{31}$
    
    - $\forall1\le i<j\le n,a_i\ne a_j$
    
    - $\bigoplus\limits_{1\le i\le n,i\text{ is odd}}a_i=\bigoplus\limits_{1\le i\le n,i\text{ is even}}a_i$
    
- $n\le2\times10^5$

### 题解

首先想想异或的性质：$\bigoplus$ 可以任意左右移项。

然后你就会发现上面什么奇偶位置完全就是骗你的。

这个条件实际上就是所有数异或起来等于 $0$。

然后就可以开始快乐构造了。

限制非常松，有很多方式构造。

比如：

- 如果 $1\bigoplus2\bigoplus\ldots\bigoplus(n-2)\ne0$：

令 $a_i=i(1\le i\le n-2),a_{n-1}=2^{30},a_n=($前面所有数异或起来$)$。

- 如果 $1\bigoplus2\bigoplus\ldots\bigoplus(n-2)=0$：

令 $a_i=i(1\le i\le n-3),a_{n-2}=n-1,a_{n-1}=2^{30},a_n=($前面所有数异或起来$)$。

### Sample code

```cpp
int n,x;
void Solve()
{
	cin>>n;
	x=0;
	for(int i=1;i<=n-3;i++)
	{
		cout<<i<<" ";
		x^=i;
	}
	if(x!=n-2)
		cout<<n-2<<" "<<(1<<30)<<" "<<((1<<30)^(n-2)^x);
	else cout<<n-1<<" "<<(1<<30)<<" "<<((1<<30)^(n-1)^x);
	cout<<endl;
}
```

---

## 作者：Shunpower (赞：0)

## 思路

题目意思很清楚。

首先我们发现题目就是要让两个序列的异或值相等，所以我们先考虑一种大致的构造方法。容易发现一个奇数搭配一个偶数可以做到异或值为 $1$，这时我们又能发现只要我们采用奇偶搭配，最后我们的异或值一定要么是 $0$，要么是 $1$，我们再用 $0,1$ 进行调整就可以了。因此下文中所有的奇数和偶数都从 $2$ 开始定义。

这就是大致的构造思路，接下来细节会很多。

### 1. $n$ 是奇数

此时显然奇数和偶数项构成两个大小刚好相差 $1$ 的序列（大小分别为 $ \frac{n-1}{2}$ 和 $\frac{n-1}2{+1}$）。奇数会比偶数恰巧多一个数，下面继续分类。

#### 偶数项序列的项数也是偶数

例如 $n=5$。

这时候我们考虑对于偶数项序列放上 $x$ 个奇数偶数搭配，再往奇数项序列里放 $x$ 个不重样的奇数偶数搭配，这时奇数项序列和偶数项序列的异或值相同，但奇数项还差一个元素，放上一个 $0$ 即可。

#### 偶数项序列的项数是奇数

例如 $n=7$。

这时候我们考虑对于奇数项序列放上 $x$ 个奇数偶数搭配，再往偶数项序列里放 $x-1$ 个不重样的奇数偶数搭配。这时奇数项序列的异或值是偶数项序列异或值取反，但偶数项序列还差一个元素，放上一个 $1$ 即可。

这样我们就解决了 $n$ 是奇数时的构造。

### 2. $n$ 是偶数

此时显然奇数和偶数项构成两个大小相同的序列（大小都为 $\frac{n}{2}$）。下面继续分类。

#### 偶数项与奇数项序列的项数是偶数

例如 $n=8$。

显然对于两个序列都各自放上 $x$ 个奇数偶数搭配即可。

#### 偶数项与奇数项序列的项数是奇数

例如 $n=6$。

这个比较难搞。容易发现如果我们像之前那样两边各自放上 $x$ 个奇数偶数搭配的话，两边不但各自差一个元素，异或值还相同，这时后面放上什么不同的两个数都无法使得整个异或值相等。

我们不妨从两边各自拿出两个数（最后放入的两个，题目中存在保证 $n\geqslant 3$），这时两边各差三个数。然后可以发现这三个数前面的部分异或值显然相同，所以我们在两边分别构造三个数异或值相同就行。

考虑我们在奇数数列中非常 simple 地放上一对奇数偶数搭配，再放一个 $1$，此时这三个数的异或值就是 $0$，那么我们随便在偶数序列构造一个 $0$ 即可。我们考虑放一个非常巨大的数，比如 $2^{25}-1$，然后我们再放一个 $2^{25}-3$，此时它和 $2^{25}-1$ 异或之后，就可以得到 $3$，我们再放一个 $3$ 去抵消就可以了。

所以我们把奇数偶数搭配的第一项从 $4$ 开始（留出 $3$），然后在奇数偶数序列中分别少构造一个奇数偶数搭配，分别放上为其构造的三个数就可以解决这个问题。

至此我们解决了所有情况下的问题，直接分类讨论，判断和构造即可。

## 代码

代码中可能对奇数偶数序列的 `vector` 的构造和题目不一样（可能搞反了），所以仅供参考。

```
//Author:Zealous_YH / Cream_H
//Su Chanzi & Xiao Bao
//Hey Left
//Just enjoy the loneliness
//Open a personal party always stay
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
using namespace std;
const int N=1e5+10;
int T;
int n;
vector <int> odd,eve;
void solve(){
	eve.clear();
	odd.clear();
	cin>>n;
	if(n%2==1){
		int the=(n+1)/2;//偶数部分的数的个数 
		int ano=n-the;//奇数部分的数的个数
		if(the%2==1){
			int tnt=2;
			fr1(i,1,the/2){
				eve.pb(tnt);
				eve.pb(tnt+1);
				tnt+=2;
			}
			fr1(i,1,ano/2){
				odd.pb(tnt);
				odd.pb(tnt+1);
				tnt+=2;
			}
			eve.pb(0);
			if(eve.size()>odd.size()){
				swap(eve,odd);
			}
		} 
		else{
			int tnt=2;
			fr1(i,1,the/2){
				eve.pb(tnt);
				eve.pb(tnt+1);
				tnt+=2;
			}
			fr1(i,1,ano/2){
				odd.pb(tnt);
				odd.pb(tnt+1);
				tnt+=2;
			}
			odd.pb(1);
			if(eve.size()>odd.size()){
				swap(eve,odd);
			}
		}
		int l=0,r=0;
		fr1(i,1,n){
			if(i%2==1){
				cout<<odd[l]<<' '; 
				l++;
			}
			else{
				cout<<eve[r]<<' ';
				r++;
			}
		}
		cout<<endl;
	}
	else{
		int the=n/2;//偶数部分的数的个数 
		int ano=n/2;//奇数部分的数的个数
		if(the%2==1){
			int tnt=4;
			fr1(i,1,the/2-1){
				eve.pb(tnt);
				eve.pb(tnt+1);
				tnt+=2;
			}
			fr1(i,1,ano/2-1){
				odd.pb(tnt);
				odd.pb(tnt+1);
				tnt+=2;
			}
			eve.pb(tnt);
			eve.pb(tnt+1);
			eve.pb(0);
			odd.pb((1<<25)-1);
			odd.pb((1<<25)-3);
			odd.pb(3);
//			cout<<"Goodbye"<<endl;
//			continue;
//			return;
		} 
		else{
			int tnt=2;
			fr1(i,1,the/2){
				eve.pb(tnt);
				eve.pb(tnt+1);
				tnt+=2;
			}
			fr1(i,1,ano/2){
				odd.pb(tnt);
				odd.pb(tnt+1);
				tnt+=2;
			}
		}
		int l=0,r=0;
		fr1(i,1,n){
			if(i%2==1){
				cout<<odd[l]<<' '; 
				l++;
			}
			else{
				cout<<eve[r]<<' ';
				r++;
			}
		}
		cout<<endl;
	}
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
//YHX 2004.08.16
//Everything For Ji, Lin, Hao, Shun, Hang and You.
```

[AC 记录](https://www.luogu.com.cn/record/91466683)

---

