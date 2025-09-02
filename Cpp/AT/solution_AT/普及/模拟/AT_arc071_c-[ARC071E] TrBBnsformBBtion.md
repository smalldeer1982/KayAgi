# [ARC071E] TrBBnsformBBtion

## 题目描述

考虑对一个只含 `A`，`B` 的字符串的如下操作：

1. 将一个 `A` 替换成 `BB`，或将一个 `B` 替换成 `AA`

2. 将三个连续相同的字符（`AAA` 或 `BBB`）消掉

例如说，串 `ABA` 可以通过第一个操作变成 `BBBA`，串 `BBBAAAA` 可以通过第二个操作变成 `BBBA`.

这些操作可以以任意顺序，不限次数地进行。

给出两个串 $S$ 和 $T$，以及 $q$ 次询问 $a_i, b_i, c_i, d_i$，每次询问你需要回答 $S_{a_i...b_i}$ 这一子串是否能通过这两个操作变成 $T_{c_i...d_i}$.

## 样例 #1

### 输入

```
BBBAAAABA
BBBBA
4
7 9 2 5
7 9 1 4
1 7 2 5
1 7 2 4```

### 输出

```
YES
NO
YES
NO```

## 样例 #2

### 输入

```
AAAAABBBBAAABBBBAAAA
BBBBAAABBBBBBAAAAABB
10
2 15 2 13
2 13 6 16
1 13 2 20
4 20 3 20
1 18 9 19
2 14 1 11
3 20 3 15
6 16 1 17
4 18 8 20
7 20 3 14```

### 输出

```
YES
YES
YES
YES
YES
YES
NO
NO
NO
NO```

# 题解

## 作者：bloodstalk (赞：10)

## 题目大意
有两个只包含 $A$ 和 $B$ 的字符串，给出两种操作

- `A` 可以变为 `BB` , `B` 可以变为 `A` ；
- `AAA` 可以消去， `BBB` 也可以消去。

## 思路
找规律。

这里我们以 `A` 为主，将 `B` 全部变为 `A` 。因为可以无限次操作，那么就代表如果两个字符串可以相等，那么他们就一定能够经过转化后变成同一个字符串，不会因为操作的限制导致不相等。

那么我们假设有一个串是 `AABB` ,那么他就可以转化成 `AAAAAA` 或者是 `AAA` ；相同的， `BBB` 可以转化成 `AAAAAA` 或者是 `AAA` :由此我们可以发现，在全部转化为一个字母后,如果两个串转化后可以相等，那么两个串全部转化为 `A` 后模 $3$ 同余。

既然 `A` 和 `B` 的个数已经固定，并且题目让你求的是大串中的字串是否相等，那么我们就把 `A` 的值设为 $1$ , `B` 的值设为 $2$，给一个前缀和数组来记录即可，这样我们就可以实现 $\mathcal{O(1)}$ 的查询了。

## 代码实现

```
#include<bits/stdc++.h>
const int L=1e5+5;
using namespace std;

string a,b;
int A[L],B[L],oriA[L],oriB[L];/*ori数组记录原A和B代表的值，A B数组是前缀和数组*/
int q,Al,Ar,Bl,Br;

int main()
{
	ios::sync_with_stdio(false);
	cin >> a >> b;
	for(int i=0;i<a.size();i++)
	{
		if(a[i] == 'A') oriA[i+1]=1;/*A为1，B为2*/
		else oriA[i+1]=2;
	}
	for(int i=0;i<b.size();i++)/*同理*/
	{
		if(b[i] == 'A') oriB[i+1]=1;
		else oriB[i+1]=2;
	}
	for(int i=1;i<=a.size();i++) A[i]=A[i-1]+oriA[i];
	for(int i=1;i<=b.size();i++) B[i]=B[i-1]+oriB[i];/*记录前缀和*/
	cin >> q;
	for(int i=1;i<=q;i++)
	{
		cin >> Al >> Ar >> Bl >> Br;
		if((A[Ar]-A[Al-1]) % 3 == (B[Br]-B[Bl-1]) % 3) cout << "YES" << endl;/*查询*/
		else cout <<"NO"<<endl;
	}
}
```


---

## 作者：A_R_O_N_A (赞：7)

## 前言

考试考到这道题了，我也不知道为什么 NOIP 难度的模拟赛会放一道黄题，还放在了 T2，T1 都是个紫题。这件事告诉我们**考场千万不要死磕**。

## 题意

你有两个字符串 $S,T$。其只含有 `A` 和 `B` 两种字符。支持以下两种操作：

1. 将 `A` 替换为 `BB`。

2. 将 `B` 替换为 `AA`。

3. 删除一个 `AAA` 或 `BBB`。

有 $q$ 次询问，每次询问一个 $S$ 的子串 $S_{a,b}$ 能否通过任意次操作变成 $T$ 的子串 $T_{c,d}$。

## 思路

考场上面的特殊性质倒是启发了我，所以这篇题解是从我的考场思路出发的。

- 特殊性质 A：$S$ 和 $T$ 都只含有 `A`。

- 特殊性质 B：$S$ 只含有 `A`。

首先我们可以看一下，经过多次操作，一个 `A` 字符到底能变成什么：

1. `A` 变成 `BB`。（操作一）
2. `BB` 变成 `AAAA`。（操作二）
3. `AAAA` 变成 `A`。（操作三）

也就是说这三种操作刚好构成了一个循环，而我们还可以发现，$1$ 个 `A` 字符能够变成 $4$ 个 `A` 字符。所以说，一个字符是可以**无限复制**下去的，每次复制，该字符的个数就会 $\times 4$。我将其称为复制操作。

考虑特殊性质 A：两个字符串都只含有 `A` 字符，要让其相等，只需要长度相等即可。而我们怎么去减少长度呢？那就是操作三，每次可以减少 $3$ 个字符的长度。有一个显然的结论：当 $len_{S_{a,b}}>len{T_{c,d}}$，它们的差必须为 $3$ 的倍数，否则无法相等。

再考虑 $len_{S_{a,b}}<len_{T_{c,d}}$ 的情况，此时可以通过复制字符的操作将情况转化为上述情况，随后按上述情况判断即可。为什么这样是正确的？同余方程基本定理可得，不再多说。

当然你也可以这么理解，因为 $S,T$ 的组成一样，所以你可以把它们两个倒过来看，也就是修改 $T_{c,d}$ 使其变成 $S_{a,b}$。然后就转化成了上述情况。

再考虑特殊性质 B：$S$ 只含有 `A`。

涉及到 `A` 和 `B` 之间的互相转化，根据题面显然有 $1$ 个 `A` 转化成 $2$ 个 `B` 的操作，易得当 $n$ 为偶数时，$n$ 个 `B` 可以由 $\frac{n}{2}$ 个 `A` 转化得到。接下来考虑奇数情况：

1. `B` 添加三个转化成为 `BBBB`。（操作三的逆向）
2. `BBBB` 转化为 `AA`。（操作一的逆向）

易得当 $n$ 为奇数时，$n$ 个 `B` 可以通过 $2\times n$ 个 `A` 转化得到。（转化方法不唯一，仅供参考）

结合一下可知任意数量的 `B` 都可以由 `A` 转化而来。同理，任意数量的 `A` 可以由 `B` 转化而来。如果 `A` 不够的话，复制就行了。

我们再考虑一个问题：字符的位置会对最终答案有影响吗？显然不会，我们已经证明了任意数量的 `B` 都可以由 `A` 转化而来。所以对于一个 $\texttt{BBB...BAB...BBB}$ 式的字符串，就相当于是 $\texttt{BBB......BBB}$ 式的字符串中间插了个 `A`。这个 `A` 显然可以由原串原封不动地搬过来。那么也就是说 $T_{c,d}$ 中所有含有 `B` 的子串都可以转化得到，关键点还是在于 `A` 的数量。我们把所有的 `B` 全部无视掉，这样子就只剩下 `A`，因为位置对答案无影响。然后就转化成了特殊性质 A。

两个特殊性质看完了，发现我们已经离正解很近了，关键在于 $S_{a,b}$ 里面的 `B` 如何处理。我们仿照将特殊性质 B 转化成为 A 的步骤，把一般情况转化成为特殊性质 B 即可。也就是把所有的 $n$ 个 `B` 转化成 $2\times n$ 个 `A`。

至于如何统计字符数量，简简单单前缀和即可。

思路说完了，来看代码。

## 考场代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*w;
}
string A,B;
int q,a,b,c,d,n,m;
ll sum[100005][4];//0->sumA_A,1->sumA_B,2->sumB_A,3->sumB_B
int main(){
	cin>>A>>B;
	n=A.size();
	m=B.size();
	A="#"+A;
	B="#"+B;
	for(int i=1;i<=n;i++){
		sum[i][0]=sum[i-1][0]+(A[i]=='A');
		sum[i][1]=sum[i-1][1]+(A[i]=='B');
	}
	for(int i=1;i<=m;i++){
		sum[i][2]=sum[i-1][2]+(B[i]=='A');
		sum[i][3]=sum[i-1][3]+(B[i]=='B');
	}
	q=read();
	while(q--){
		a=read();b=read();c=read();d=read();
		ll sum0=sum[b][0]-sum[a-1][0];
		ll sum1=sum[b][1]-sum[a-1][1];
		ll sum2=sum[d][2]-sum[c-1][2];
		ll sum3=sum[d][3]-sum[c-1][3];
		sum0+=sum1*2;//化 B 为 A
		if(sum3%2==1){
			while(sum0<sum3*2)sum0*=4;
		}else while(sum0<sum3/2)sum0*=4;//复制
		if(sum3%2==1)sum0-=sum3*2;
		else sum0-=sum3/2;//无视掉 B
		if(sum0==sum2)puts("YES");
		else if(abs(sum0-sum2)%3==0)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：Querainy (赞：5)

发现这个操作是可逆的!比如现在有`A`，变成`BB`，然后变成`AAAA`，还可以变回`A`。唯一的特例是空串，它不能变成任何串，不过这不重要。

既然可逆，那么我们只需要把 $s,t$ 上这两个区间变成一样的，就可以说明它们可以相互转化了。

怎么变?先全变成`A`，然后看两个区间`A`的个数模 $3$ 是否相同即可。交上去你发现过了/jy

代码不放了，就是一个前缀和（

---

## 作者：dcmfqw (赞：4)

这里是群论做法。

Soulist 聚聚发现了一个这种神仙结论题的一般解法。~~我只是一个搬运工。~~

**侵联删。**

不知道群论的可以看 [Soulist 的博客](https://www.luogu.com.cn/blog/Soulist/solution-p4980)

（到子群那个地方就和这篇题解无关了）

“不限制操作次数”意味着我们可以想到所有的字符串可以分成若干个等价类。

然后根据楼上的证明，字符串 S 能转换到 T 那么 T 肯定能转换到 S。

等价类里的字符串互相可达，而不同等价类的字符串互相不可达。

---

既然是群论，那么我们定义一下这个群的几个要素。

集合：就是这些等价类。

运算：从两个等价类中分别随便选两个字符串拼接所得到的字符串所在的等价类。

很绕口，~~建棵表达式树~~多读几遍应该读的懂。

虽然是随便选两个，但是一定在同一个等价类里。

注意这里字符串的拼接是有序的，且拼接一般不满足交换律。

有封闭性：显然。（你把两个字符串拼起来肯定还是一个字符串而不是变成一个奇奇怪怪的东西）

有结合律：显然。

存在单位元：显然是空串所在等价类。

存在逆元：考虑定义，一个元素存在逆元意味着它可以通过拼接上一个串变成单位元。

但你不可能把一个非空字符串拼成空串。

但是我们可以拼成空串所在的等价类。

在这个题中，每个等价类中肯定有一个全 A 或 B 的序列，然后再接几个 A 或 B 消一消就变成空串了。

---

直接搞这个群显然不行，我们可以考虑把它映射到我们熟悉的运算。

以这个题为例。

我们可以把它的操作翻译成下面三句话：

+ `A` 和 `BB` 在同一个等价类里。

+ `B` 和 `AA` 在同一个等价类里。

+ `AAA`、`BBB` 以及空串在同一个等价类里。

这三个等价类我们分别用 $X$、$Y$ 和 $E$ 表示，拼接运算就用 $\circ$ 表示。

根据定义 $E$ 是单位元。

然后就有：

$$X\circ X=Y$$

$$Y\circ Y=X$$

$$X\circ X\circ X=E$$

$$Y\circ Y\circ Y=E$$

显然上面的运算是满足交换律的，所以可以使用加法乘法异或之内的东西替代这个拼接运算。

接下来确定等价类个数更容易发现结论。

上面的四个式子随便带入一下就可以发现：

$$X\circ Y=E$$

即 $X$ 是 $Y$ 的逆元。

而只需 $X$ 和 $Y$ 进行运算就可以得到所有等价类。

所以每个等价类要么是单位元，要么可以只用含 $X$ 或 $Y$ 的运算就能表示。

但是两个 $X$ 进行运算就会变成 $Y$，$Y$ 也如此。

综上，**所有等价类只有 $E$、$X$ 和 $Y$**。

到这里我们就可以考虑映射了。

只有三个元素的运算是什么？

在 3 的同余系内的某个运算。

稍加带入就会发现加法符合所有条件。

把拼接映射到 3 的同余系内的加法，$E$ 映射到 0，$X$ 映射到 1，$Y$ 映射到 2。

于是乎预处理一下前缀和这题就没了。

嫌麻烦吗？

我也嫌麻烦。

但是对于某些类似神仙结论题十几个等价类还是在用人类智慧打表打出来的自动机上做转移来说。

这种方法好太多了。

代码：

~~放不放应该无所谓吧只要上面的看懂了。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _maxn = 100011;
int slen, tlen, q, pres[_maxn], pret[_maxn], a, b, c, d;
char s[_maxn], t[_maxn];
int main() {
    scanf("%s%s%d", s + 1, t + 1, &q);
    slen = strlen(s + 1);
    tlen = strlen(t + 1);
    for(int i = 1; i <= slen; ++i) {
        if(s[i] == 'A') {
            pres[i] = (pres[i - 1] + 1) % 3;
        } else {
            pres[i] = (pres[i - 1] + 2) % 3;
        }
    }
    for(int i = 1; i <= tlen; ++i) {
        if(t[i] == 'A') {
            pret[i] = (pret[i - 1] + 1) % 3;
        } else {
            pret[i] = (pret[i - 1] + 2) % 3;
        }
    }
    while(q--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if((pres[b] - pres[a - 1] + 3) % 3 == (pret[d] - pret[c - 1] + 3) % 3) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
```

---

## 作者：Size_OIer (赞：1)

我们用 $1$ 来表示 $A$，$2$ 来表示 $B$。  
我们能够发现，$1$ 能够变为 $22$，然后变为 $1111$，最后又变回了 $1$。  
这说明，对于两个由 $1$ 组成的序列，只要他们模 $3$ 的同余相同，那他们就是可以互相转化的。  
故将两个区间内的 $2$ 都变为 $1$，求前缀和，取模即可。  
## Code  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
int n, m, q;
string S, T;
int s[maxn], t[maxn];
int main () {
    cin >> S >> T;
    n = S.size ();
    m = T.size ();
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + S[i - 1] - 'A' + 1;
    for (int i = 1; i <= m; i++) t[i] = t[i - 1] + T[i - 1] - 'A' + 1;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int l, r, ll, rr;
        cin >> l >> r >> ll >> rr;
        if ((s[r] - s[l - 1]) % 3 == (t[rr] - t[ll - 1]) % 3) puts ("YES");
        else puts ("NO");
    }
    return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：1)

首先看到这个奇特的转化方式和常规的数据范围，我们不难想到一定有什么规律。

我们可以先想一个转化后的问题：每次询问的两个字符串都可以按照题目要求进行转化，问它们最后能不能转化成同一个字符串。

这个问题很简单，我们只需要把两个字符串中的 `A` 全都换成 `BB`，最后对 $3$ 取模，看看此时是否相同即可，这个可以用四个前缀和实现。

那么回到原题，相当于我们现在只需要证明这个过程是否能倒推就行了。

不妨观察字符串 `ABAB` 的转化过程：

ABA $\to$ BBBBB $\to$ BB

通过观察不难发现，这个转化完全可以逆向进行：

BB $\to$ BAA $\to$ BBBBB

那么稍加推广，不难证明所有形式的字符串都可以类似这样进行转化。

于是我们只需要按照上面转化后的问题操作就能得到正确答案了。

[提交记录](https://atcoder.jp/contests/arc071/submissions/58284142)

---

## 作者：tZEROちゃん (赞：1)

伟大的 mzx 让我不要写黄题，那我就来写绿题（x

结论：将 $\tt A$ 变成 $1$，$\tt B$ 变成 $2$，对于字符串 $s, t$，我么能将 $s$ 转化成 $t$，当且仅当 $s$ 每一位上的和与 $t$ 每一位上的和对 $3$ 取模的值相同。

那为什么呢？

我们使用将 $\tt B$ 变成 $\tt AA$ 的操作，可以让所有非空字符串变成仅含有 $\tt A$ 的字符串。

比如 $\tt BB$ 可以变成 $\tt AAB$，然后变成 $\tt AAAA$，还可以删掉 $3$ 个 $\tt A$ 变成 $\tt A$。


所以任意非空字符串都可以被转化成 $\tt A$ 或 $\tt AA$ 或 $\tt AAA$，这 $3$ 这个字符串每一位上的和模 $3$ 都是不同的，于是就很好做了，前缀和算一下就行了。

[参考代码（C++）](https://www.luogu.com.cn/paste/q13f2pqc)。

---

## 作者：ReTF (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT2395)

这道题目给了我们两种操作：
> * 将一个 A 替换成 BB，或将一个 B 替换成 AA；
> * 删除 AAA 或 BBB。

我们不妨先假设操作前的字符串含有 $x_0$ 个 A 和 $y_0$ 个 B，A 和 B 的个数之差为 $x_0-y_0$；**一次操作**后的字符串含有 $x_1$ 个 A 和 $y_1$ 个 B，则 
* 在将一个 A 替换成 BB 后，字符串含有 $x_0-1$ 个 A 和 $y_0+2$ 个 B，A 和 B 的个数之差为 $x_0-y_0-3$；
* 在将一个 B 替换成 AA 后，字符串含有 $x_0+2$ 个 A 和 $y_0-1$ 个 B，A 和 B 的个数之差为 $x_0-y_0+3$；
* 在删除 AAA 后，字符串含有 $x_0-3$ 个 A 和 $y_0$ 个 B，A 和 B 的个数之差为 $x_0-y_0-3$；
* 在删除 BBB 后，字符串含有 $x_0$ 个 A 和 $y_0-3$ 个 B，A 和 B 的个数之差为 $x_0-y_0+3$；

容易看出，在一次操作后，A 与 B 的个数之差与本次操作前 A 与 B 的个数之差模 $3$ 同余，进而引申到在若干次操作后，A 与 B 的个数之差与操作前 A 与 B 的个数之差模 $3$ 同余。

而这道题中初始状态和目标状态的字符串都是某个大串的一个子串，该大串固定不变，所以我们维护前缀和即可在 $O(1)$ 的时间范围内得出答案。

AC代码&[AC记录](https://www.luogu.com.cn/record/76617063)：
```
#include<bits/stdc++.h>
using namespace std;
#define inf 100010
int q,s[2][inf],t[2][inf];//s[0][i]存的是从0到i中A的个数，s[1][i]则是B的个数，t同理 
void inpString(int f[][inf]){ 
	string inp;cin>>inp;
	for(int i=0;i<inp.length();i++){//统计前缀和 
		f[0][i+1]=f[0][i]+(inp[i]=='A');//奇怪的写法，如果是'A',f[0][i+1]就+1 
		f[1][i+1]=f[1][i]+(inp[i]=='B');
	}
}
int Query(int lb,int rb,int f[][inf]){//返回该段A-B模3的余数 
	int at=f[0][rb]-f[0][lb-1],bt=f[1][rb]-f[1][lb-1],ret=at-bt;
	return (ret>=0?ret%3:(3-((-1*ret)%3)))%3;//后半段强制对负数取模 
}
int main(){
	inpString(s);inpString(t);cin>>q;//读入s,t,q;
	for(int i=1,l,r,l_,r_;i<=q;i++){
		cin>>l>>r>>l_>>r_;
		puts((Query(l,r,s)==Query(l_,r_,t))?"YES":"NO");//若同余，则输出 
	}
}
```

---

## 作者：cyq32ent (赞：0)

题意：对 $12$ 字符串 $s$ 进行如下操作：

- 将某个 $2$ 替换成 $11$ 或将 $1$ 替换成 $22$。
- 将某个 $111$ 或 $222$ 替换成空串。

每次询问 $s$ 的子区间 $[a,b]$ 是否能经过以上变换变成 $t$ 的子区间 $[c,d]$

注意到该变换不影响字符串的和模 3 的同余。

又注意到操作可逆（$1,22,1111,1$），那么我们只要把 $s,t$ 中全都替换成 $1$，那么只需比较模 3 意义下同余即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int s[505050],t[505050],n,m,q,a,b,c,d;
string S,T;
int main(){
	cin>>S>>T>>q;
	n=S.length(),m=T.length();
	for(int i=0;i<n;i++)s[i]=s[i-1]+S[i]-'@';
	for(int i=0;i<m;i++)t[i]=t[i-1]+T[i]-'@';
	while(q--){
		cin>>a>>b>>c>>d;
		cout<<((s[b-1]-s[a-2])%3==(t[d-1]-t[c-2])%3?"YES\n":"NO\n");
	}
}
```

---

## 作者：A1C3 (赞：0)

# [ARC071E] TrBBnsformBBtion

观察题目，可知 `A` 与 `BB` 等价，`B` 与 `AA` 等价。不妨令所有的 `B` 均为 `AA`，此时串 $S$ 和串 $T$ 均为只包含 `A` 的串。此时操作 $2$ 即可求解：计算串 $S$ 在区间 $[a, b]$ 中 `A` 的数量（一个 `B` 等价两个 `A`） 和串 $T$ 在区间 $[c, d]$ 中 `A` 的数量（一个 `B` 等价两个 `A`）模 $3$ 是否同余即可。

计算区间内 `A` 的数量可以使用前缀和数组预处理，进而 $O(1)$ 解决。

## AC Code

```cpp
#include <iostream>
using namespace std;
const int N = 1e5 + 7;
char s[N], t[N];
int sums_a[N], sumt_a[N];
bool check(int a, int b, int c, int d) {
    int s_a = sums_a[b]-sums_a[a-1];
    int t_a = sumt_a[d]-sumt_a[c-1];
    return s_a%3 == t_a%3;
}
int main() {
    scanf("%s%s", s+1, t+1);
    for (int i = 1; s[i]; ++i) {
        sums_a[i] += sums_a[i-1];
        if (s[i] == 'A') ++sums_a[i];
        else sums_a[i] += 2;
    }
    for (int i = 1; t[i]; ++i) {
        sumt_a[i] += sumt_a[i-1];
        if (t[i] == 'A') ++sumt_a[i];
        else sumt_a[i] += 2;
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if (check(a, b, c, d)) puts("YES"); // 表示对S的 [a, b] 区间和 T 的 [c, d] 区间进行判断
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：Red_river (赞：0)

## 题目大意：
给你两个字符串，而且只包含两个不同的字母。然后有如下操作：

1. `A` 可变为 `BB`，`B` 可变为 `A`。
2. `AAA` 可消去，`BBB` 也可消。

### 思路：
其实我们不难发现，这道题其实就是道贪心，而关键就在于我们如何处理了。其实对于操作一来说就是把这个字符给**复制**一次，所以主要有这个字符，我就一定可以把它消去。即只要它的规律一样，就是连续的相同区间的数量和首位一样就行了。而至于如何判断它的规律，我们可以给两个字符赋值互质的值，就可以在 $O(1)$ 的之间内判断。

总共的时间复杂度为 $O(n+m+k)$。
#### CODE
```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 200005
#define NO printf("NO\n")
#define YES printf("YES\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int f[N][3];char a[N],b[N];
void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
	x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

int val(int x,int y,int z)
{
	if(z==1) return (f[y][1]-f[x-1][1])%3;
	else return (f[y][2]-f[x-1][2])%3;
}//判断规律是怎样的

signed main()
{
	scanf("%s%s",a+1,b+1);n=strlen(a+1),m=strlen(b+1);
	f(i,1,n) if(a[i]=='A') f[i][1]=1;else f[i][1]=2;
	f(i,1,m) if(b[i]=='A') f[i][2]=1;else f[i][2]=2;
	sum=max(n,m);f(i,1,sum) f[i][1]+=f[i-1][1],f[i][2]+=f[i-1][2];
  //前缀和优化，否则直接暴力会超
	read(k);int zb,yb,l,r;
	while(k--)
	{
		read(zb),read(yb),read(l),read(r);
		if(val(zb,yb,1)==val(l,r,2)) YES;else NO;//define 具体见上面
	}
	return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

直接变换没什么头绪，考虑把两个要对比的串全部变成同一种字母。

显而易见的，如果要对比的两个串变成同一个字母后如果相等，则这两个串一定可以相互转换，因为有删除相邻的三个相同字符操作的存在，所以限制进一步放宽，只要要对比的两个串变成同一个字符后模 $3$ 的余数相同，则它们一定可以转化为相同的串。

然后问题就很简单了，对于串 $s$ 和 $t$，我们根据操作一将其变为一样的字符，假设我们把所有 $\text{B}$ 都变成 $\text{A}$，由于每个 $\text{B}$ 可以变成两个 $\text{A}$，我们可以将 $\text{B}$ 的权值设为 $2$，把 $\text{A}$ 的权值设为 $1$，对于两个串分别做前缀和，对于每次询问查询该字串的权值模 $3$ 的余数，相等则为  $\text{YES}$，不相等则为 $\text{NO}$。

### $\text{code}$

```cpp
string s,t;
int sums[maxn],sumt[maxn];

void solve(){
	cin>>s>>t;
	int n=s.size(),m=t.size();
	s=" "+s;
	t=" "+t;
	for(int i=1;i<=n;i++){
		if(s[i]=='A'){
			sums[i]=sums[i-1]+1;
		}
		else{
			sums[i]=sums[i-1]+2;
		}
	}
	for(int i=1;i<=m;i++){
		if(t[i]=='A'){
			sumt[i]=sumt[i-1]+1;
		}
		else{
			sumt[i]=sumt[i-1]+2;
		}
	}
	int q=read();
	while(q--){
		int a=read(),b=read(),c=read(),d=read();
		int u=(sums[b]-sums[a-1])%3,v=(sumt[d]-sumt[c-1])%3;
		if(u==v){
			puts("YES");
			continue ;
		}
		else{
			puts("NO");
			continue ;
		}
	}
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：Erica_N_Contina (赞：0)

# [ARC071E] TrBBnsformBBtion

## 题目描述

考虑对一个只含 `A`，`B` 的字符串的如下操作：

1. 将一个 `A` 替换成 `BB`，或将一个 `B` 替换成 `AA`。

2. 将三个连续相同的字符（`AAA` 或 `BBB`）消掉。

例如说，串 `ABA` 可以通过第一个操作变成 `BBBA`，串 `BBBAAAA` 可以通过第二个操作变成 `BBBA`。

这些操作可以以任意顺序，不限次数地进行。

给出两个串 $S$ 和 $T$，以及 $q$ 次询问 $a_i, b_i, c_i, d_i$，每次询问你需要回答 $S_{a_i...b_i}$ 这一子串是否能通过这两个操作变成 $T_{c_i...d_i}$。

输出 $q$ 行，每行包含一个询问的答案。若第 $i$ 个询问 $S_{a_i...b_i}$ 这一子串能通过这两个操作变成 $T_{c_i...d_i}$，则输出 `YES`，否则输出 `NO`.

- $1\ \leq\ |S|,\ |T|\ \leq\ 10^5$

- $1\ \leq\ q\ \leq\ 10^5$

- $1\ \leq\ a_i\ \leq\ b_i\ \leq\ |S|$

- $1\ \leq\ c_i\ \leq\ d_i\ \leq\ |T|$

## 思路

**前提**

首先明确一点：操作数量是无限的。

我们再考虑一个问题：如果字符串 $S$ 通过操作可以转化为 $T$，那么 $T$ 一定能通过操作转换为 $S$。这个很好证明，例如现在有 `A`，变成 `BB`，然后变成 `AAAA`，又可以变回 `A`。

**问题转化**

有了上面两个结论，我们就可以把问题变成：给定字符串 $S$ 和 $T$，问对两个字符串进行操作后能否将它们转化为同一个字符串。（注意我们这里把子串 $S_{ a_i... b_i}$ 和 $T_{c_i...d_i}$ 直接称呼为 $S$ 和 $T$）

转化为同一个字符串？那么最好考虑到莫过于把他们都转化为只有 `A`（或者只有 `B`）的字符串了。

那么我们就把 $S$ 和 $T$ 转化为只有字符 `B` 的字符串好了（别问我为什么怎么喜欢 `B`）

首先：如果两个字符串本来就都是 `B` 串（我们就把只有字符 `B` 的字符串叫做 `B` 串好了），那么什么情况下它们可以变成同一个字符串？（即什么情况下可以让长的那个字符串变短成短的那个字符串？）

很显然，只要字符串 $S$ 和 $T$ 的**长度在模 $3$ 下余数一样**就可以了。

我们再考虑有 `A` 的情况——我们是不是把每个 `A` 看成长度为 $2$ 的字符串 `BB` 就可以了？是啊！

**多次询问**

对于多次询问，我们发现这是个区间求和问题，所以我们前缀和即可。我们把 `B` 看成是 $1$，把 `A` 看成是 $2$（即：每个 `A` 看成长度为2的字符串 `BB`），然后前缀和，查询模 $3$ 的余数，判断相等。这样的时间复杂度为 $O(1)$。

## Code

`AC`

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;

const int N=2e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

string sa,sb;
//char sa[N],sb[N];
int n,qzh[N],qzh2[N];

signed main(){
//	scanf("%s",sa);
//	scanf("%s",sb);
	cin>>sa>>sb;
	for(int i=0;i<sa.size();i++){
		if(sa[i]=='A')qzh[i+1]=qzh[i]+2;
		else qzh[i+1]=qzh[i]+1;
	}
	for(int i=0;i<sb.size();i++){
		if(sb[i]=='A')qzh2[i+1]=qzh2[i]+2;
		else qzh2[i+1]=qzh2[i]+1;
	}
	scanf("%d",&n);
//	cin>>n;
	while(n--){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
//		cin>>a>>b>>c>>d;
		if((qzh[b]-qzh[a-1])%3==(qzh2[d]-qzh2[c-1])%3)puts("YES");
		else puts("NO");
	}
	

	return 0;
}

```





---

## 作者：I_am_sb___ (赞：0)

~~暴论：此题看似很简单，其实一点都不难~~

当没有思路时，我们不妨可以重新读一遍题：题目中讲到，每个字母都可以变为其他字母的两倍，当有三个连续的相同字母时就可以将其消去。不难发现的是，每个字母都可以变为原来的 $4$ 倍，然后再重新变回原样。

由于这题中两种字母可以互相转换来看，那么假设有一种相等情况存在，那么这种情况就一定可以被转换成只有其中一个字母的形态。

不妨试图将所有情况都转换成只有 `A` 字符的字串，这样任务就变成的判断 `A` 的个数是否相等。

枚举转换字符的可能性：$A \to BB \to AAAA \to A$，可以发现，在这所有的过程中，`A` 字符在 $num_{A_{count}} \bmod 3$ 时的个数都是相同的，即使转换了字符种类，也一定可以转换成和 $num_{A_{strart}} \bmod 3$ 相等的状态。

由此就可以得到思路：任选一字符，将其“价值”定义为 $1$，与其不同的字符“价值”定义为 $2$，这样就只需要判断 $S_{a……b}$ 的价值和是否与 $T_{c……d}$ 的价值和在对 $3$ 取模的情况下同余即可，直接用前缀和维护即可（~~当然你想用线段树也不是不行~~），在代码演示中将 `A` 字符定义为 $1$。

code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>

#define int long long
#define mp make_pair
#define PII pair<int , int>

using namespace std;

template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}

template<typename T>inline void write(T x){
	if(x<0)putchar('-'),x*=-1;
	if(x>9)write(x/10);
	putchar(x%10+48);
}

const int N = 100007;
const int inf = 1 << 31;
const int mod = 1e9 + 7;

int n , q;
int s[N] , t[N];
char a[N] , b[N];

signed main(){
	scanf("%s%s" , a + 1 , b + 1);
	read(q);
	n = strlen(a + 1);
	for(int i = 1 ; i <= n ; ++ i) s[i] = s[i - 1] + a[i] - 'A' + 1;
	n = strlen(b + 1);
	for(int i = 1 ; i <= n ; ++ i) t[i] = t[i - 1] + b[i] - 'A' + 1;
	int l , r , l_ , r_;
	for(int i = 0 ; i < q ; ++ i)
	{
		read(l);read(r);read(l_);read(r_);
		int vs = s[r] - s[l] + a[l] - 'A' + 1;
		int vt = t[r_] - t[l_] + b[l_] - 'A' + 1;
		if((vs % 3) ^ (vt % 3)) puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

## 思路

定义字符串模 $3$ 的余数为将 `A` 看成 $1$，`B` 看成 $2$ 并加和后模 $3$ 的余数。可以发现题中的操作是不改变字符串模 $3$ 的余数的。

那么就对两个字符串做一遍前缀和，判断两个子串模 $3$ 的余数是否相等即可。

## 代码

```cpp
const int maxn = 100100;

int n, m, suma[maxn], sumb[maxn];
char s[maxn], t[maxn];

void solve() {
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1);
	m = strlen(t + 1);
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'A') {
			suma[i] = suma[i - 1] + 1;
		} else {
			suma[i] = suma[i - 1] + 2;
		}
	}
	for (int i = 1; i <= m; ++i) {
		if (t[i] == 'A') {
			sumb[i] = sumb[i - 1] + 1;
		} else {
			sumb[i] = sumb[i - 1] + 2;
		}
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		puts((suma[b] - suma[a - 1]) % 3 == (sumb[d] - sumb[c - 1]) % 3 ? "YES" : "NO");
	}
}
```


---

