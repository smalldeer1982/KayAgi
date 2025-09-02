# 【MX-X3-T3】「RiOI-4」GCD 与 LCM 问题

## 题目背景

原题链接：<https://oier.team/problems/X3D>。

---

「既然你说你不了解她，为什么又可以断言她一定是因为……」

是呀，自己对零羽还了解的确实不够多……泠珞这样想着。

在残缺的记忆当中，她只能想起，她和零羽的最大公约数，就是「音乐」。

还缺了什么呢？泠珞不知道。她只知道，那所缺失的，和「音乐」加起来，就是她的一切。一切的总和。

**滴答，滴答**。叮咚，叮咚。如果把长短不一、断断续续的钢琴声拼接在一起，能够回忆起什么吗。

## 题目描述

给定一个正整数 $a$，请你构造三个正整数 $b,c,d$ 使得 $a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$。一个测试点内有多组数据。

由于出题人想把自己 QQ 号写题目里，你需要保证 $b,c,d\le 1\,634\,826\,193$。

**如有多种可能的答案，输出任意一个均可。**

## 说明/提示

**【样例解释】**

样例的构造为：

$1+7+9+2=19=\gcd(1,7)+\operatorname{lcm}(9,2)$  
$2+9+6+8=25=\gcd(2,9)+\operatorname{lcm}(6,8)$  
$3+5+9+2=19=\gcd(3,5)+\operatorname{lcm}(9,2)$  
$20\,120\,712+8\,065\,343+8\,750+6\,446=28\,201\,251=\gcd(20\,120\,712,8\,065\,343)+\operatorname{lcm}(8\,750,6\,446)$

容易验证均满足要求。

**【数据范围】**

|测试点|分数|$t\le$|$a\le$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$2$|$10$|$10$||
|$2$|$5$|$50$|$50$||
|$3$|$17$|$10^6$|$5\times10^8$||
|$4$|$29$|$10^6$|$10^9-1$|$a$ 为奇数|
|$5$|$47$|$2\times10^6$|$10^9$||

对于 $100\%$ 的数据，$1\le t\le2\times10^6$，$1\le a\le 10^9$。

## 样例 #1

### 输入

```
4
1
2
3
20120712```

### 输出

```
7 9 2
9 6 8
5 9 2
8065343 8750 6446```

# 题解

## 作者：Register_int (赞：44)

不难发现 $a$ 为奇数时有构造 $b=1,c=2,d=a+2$。发现等式两边同乘 $2^k$ 后仍然成立，所以令 $a=2^ka'$，构造 $b=2^k,c=2^{k+1},d=a+2^{k+1}$ 即可。

容易发现最坏情况下答案 $\le3\times2^{29}=1610612736$，可以通过。

---

## 作者：Luo_Saisei (赞：14)

## 分析

$a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$。

令 $\gcd(a,b)=p$ 则 $a=pa_0,b=pb_0$。

令 $\gcd(c,d)=q$ 则 $c=qc_0,d=qd_0$。

$a+b+c+d=pa_0+pb_0+qc_0+qd_0=p+qc_0d_0$。

考虑化简该式子。

令 $p=1$ 显然是让 $a,b$ 互质，此时显然 $\gcd(a,b)=1$。

但是 $b$ 的选择是多样的，根据有理数的定理 $a-1,a+1,...$ 等许多数都可以与 $a$ 互质。

但是考虑到 $a=pa_0 (a_0 \ge 1)$，所以 $p \le a$ 这是显而易见的。

我们提取式子中和 $a,b$ 有关的部分。

左侧为 $a+b$ 右侧为 $\gcd(a,b)=1$

我们令 $b=1$ 与右侧相消。

此时的式子变成：$a+c+d=\operatorname{lcm}(c,d)$。

这个时候我们分类讨论。

## $a$ 为奇数

$c=2,d=a+2$ 即可。

为什么呢？

此时的等式为 $a\times2+4=\operatorname{lcm}(2,a+2)$。

这不是显而易见吗 $a$ 是奇数，那么 $a+2$ 也是奇数。

一个奇数和 $2$ 的最小公倍数自然是这个奇数的两倍，证明完毕。

## $a$ 为偶数

给出这部分的核心代码。

```cpp
int cnt=0,nc=a;
while(nc%2==0) nc/=2,cnt++;
c=pow(2,cnt+1),d=a+c;
```

代码的功能我不用多说，大家想必看得出来，现在我来证明这个结论的正确性。

$\forall y\in \mathbb{N+},x=2y$，这是正偶数集合的定义，显然，根据任何一个正偶数都有至少一个因子是 $2$。

所以 $a=2^i\times y$ , $c=2^{i+1}$ , $d=a+c=2^{i+1}+2^iy$。

PS: 此处的 $y$ 为奇数。

等式变为 $2^{i+1}y+2^{i+2}=\operatorname{lcm}(2^{i+1},2^{i}(2+y))$。

其实也很好理解 根据最小公倍数的性质。

$\operatorname{lcm}(2^{i+1},2^{i}(2+y))=2^i\operatorname{lcm}(2,2+y)$。

等式最后变形一次。

$2^i(2y+4)=2^i\operatorname{lcm}(2,2+y)$。

提取公因式，$(2y+4)=\operatorname{lcm}(2,2+y)$。

而这个等式我们已经证明完毕，所以证明完毕。

## 最后给出范围证明

$a$ 最大为 $10^9<2^{30}$，所以 $i$ 最大为 $29$。
但注意到 $i=29$ 时 $a\le2^{29}$。

若 $i=29$，则 $a+2^{i+1}\le 2^{29}+2^{30}=1610612736\le1634826193$

若 $i\le29$，则 $a+2^{i+1}\le 10^9+2^{29}=1536870912\le1634826193$

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,T;
void solve()
{
	int cnt=0,nc=a;
	while(nc%2==0) nc/=2,cnt++;
	c=pow(2,cnt+1),d=a+c;
	cout<<1<<" "<<c<<" "<<d<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) cin>>a,solve();
	return 0;
}
```

---

## 作者：Down_syndrome (赞：14)

# 【MX-X3-T3】「RiOI-4」GCD 与 LCM 问题 题解

构造题好玩捏。

## 思路

哇，居然要构造三个整数，也太多了吧！我们简化一下问题，令 $b=1$，然后构造 $a+c+d=\operatorname{lcm}(c,d)$ 就行了。

诶，还要构造两个整数耶，太多了吧。那我们再简化一波，假设我们能够构造出来一对 $c,d$ 使得 $\gcd(c,d)=1$，那么我们只要构造 $a+c+d=cd$ 就行了。

化简一下，也就是 $a+1=(c-1)(d-1)$。当 $a+1$ 是偶数，也就是 $a$ 是奇数时，令 $c-1=1,d-1=a+1$，也就是 $c=2,d=a+2$ 时，因为 $a+2$ 是奇数，所以 $2$ 和 $a+2$ 互质。这样你就做完了 $a$ 是奇数的情况，拿下了 $29$ 分高分捏。

好的，那么 $a$ 是偶数时应该怎么做捏。

哎呀，$a$ 时偶数好麻烦啊，我们给它转化成奇数就行了啊。容易发现如果 $a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$ 成立，那 $ak+bk+ck+dk=\gcd(ak,bk)+\operatorname{lcm}(ck,dk)$ 也成立。哦！那我们按照以上方案构造出 $\frac{a}{\operatorname{lowbit}(a)}$，再乘上 $\operatorname{lowbit}(a)$ 就行了啊！

做完了！——吗？

还有最后一个问题，那就是为啥构造出来的数据不会超过作者的 QQ 号呢？

注意到我们构造出来的最大数是 $d$，也就是 $a+2\times \operatorname{lowbit}(a)$（化简之后的结果），只要保证这个东西不超过 $1634826193$ 就行了。打个表找一下对于 $\operatorname{lowbit}(a)$（最大为 $536870912$）不同取值时 $a$ 在 $10^9$ 下 $d$ 的值最大是多少就行了。结果就是最大值为 $1610612736$，刚好不超。

那么本题结束！！！

## code


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,k;
int lowbit(int x){
	return x&-x;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&a);
		k=lowbit(a);
		printf("%d %d %d\n",k,2*k,a+2*k);
	}
	return 0;
}
```


喜欢就留下一个赞吧！！！ヾ(ﾟ∀ﾟゞ)

---

## 作者：orangejuice (赞：14)

## 题目大意

给定 $a$，构造 $b,c,d \leq \frac{3}{2}a +O(1)$， 使得 $a+b+c+d=\gcd(a,b)+\text{lcm}(c,d)$。

## 子问题构造

先考虑如何构造 $\text{lcm}(c,d)-c-d=x$。

注意到 $3 \times 4 - 3- 4=5$，

因此若 $x \bmod 5 = 0$，取 $c=x/5 \cdot 3, d=x/5\cdot 4$ 即可。

## 原问题构造

回到原问题，此时 $x=a+b-\gcd(a,b)$。

结论：对于 $a \leq 1000$，枚举 $b \leq 20$ 发现均可以找到 $x \bmod 5 = 0$ 的解，事实上对于所有 $a$ 都能找到。 

应用此结论，只需要枚举 $b \leq 20$ 找到满足条件的 $b$ 并选取对应的 $c,d$ 即可。


## 结论证明与分析

进一步验证，事实上对于所有 $a$ 均能找到 $b\leq 20$ 且 $b=2^i3^j5^k$ 的解，所有这样的 $b$ 的 $\text{lcm}$ 为 $L=720$。

对于这样的 $b$，有 $\gcd(a,b)= \gcd (a+L,b)$，因此 $a+b-\gcd(a,b)\equiv (a+L)+b-\gcd(a+L,b) \pmod 5$。

故由 $a\leq L$ 成立可以推得所有 $a$ 成立。

如此构造满足 $b\leq 20, c,d \leq \frac{4}{5}(a+20)$.

---

## 作者：diqiuyi (赞：11)

神秘构造。

这个限制看上去比较松，所以不妨令 $b=1$。此时只要 $\operatorname{lcm}(c,d)=a+c+d$。

考虑 $a$ 为奇数如何处理，发现 $c=2$，$d=a+2$ 可以满足。

考虑 $a=4k+2$，发现 $c=4$，$d=a+4$ 可以满足。

记 $v$ 为满足 $2^v\mid a$ 的最大整数，注意到 $c=2^{v+1}$，$d=2^{v+1}+a$ 可以满足。此时 $\gcd(c,d)=\gcd(c,a)=2^v$，所以 $\operatorname{lcm}(c,d)=2^{v+2}+2a=a+c+d$，符合要求。

因为 $a\le 10^9$，所以 $v\le 29$。

若 $v\le28$，$d\le 10^9+2^{29}=1536870912
$，显然合法。

若 $v=29$，则 $a=2^{29}=536870912$，$d=1610612736
$，同样合法。

所以这么构造就是对的。

---

## 作者：SFlyer (赞：11)

求 $a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$。不妨设 $b=a$，则要求 $a+c+d=\operatorname{lcm}(c,d)$。

考虑 $\gcd(c,d)=1$ 的情况。则 $a+c+d=cd$ 即 $cd-c-d=a$ 即 $(c-1)(d-1)=a+1$。

如果 $2\nmid a$，则 $2\mid a+1$，所以 $c=2,d=a+2$ 即可。容易发现 $\gcd(2,a+2)=1$。

如果 $2\mid a$，设 $a=2^k p$，$2\nmid p$。如果 $c=2\cdot 2^k,d=(p+2)\cdot 2^k$，则 $\gcd(c,d)=2^k$，$\operatorname{lcm}(c,d)-c-d=\frac{cd}{\gcd(c,d)}-c-d=2(p+2)\cdot 2^k-(p+4)\cdot 2^k=p\cdot 2^k=a$。

设限制是 $lim$。显然 $b=a<lim,c_{\max}=2\cdot 2^k=2^{}<lim$，$d=a+2$ 时 $a+2<lim$，$d=(p+2)\cdot 2^k$ 时 $d$ 在 $a=2^{29}$ 取最大值，为 $3\cdot 2^{29}=1610612736<lim$。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin>>t;
	while (t--){
		ll a;
		cin>>a;
		ll b=a,c,d;
		ll pw=1;
		while (a%2==0){
			a/=2,pw*=2;
		}
		c=2;
		d=a+2;
		c*=pw,d*=pw;
		cout<<b<<" "<<c<<" "<<d<<"\n";
	}
	return 0;
}

```

---

## 作者：Limitless_lmw (赞：10)

注：这是一篇已经通过的题解，仅仅是对代码进行了修改，望管理员通过。

考虑简化 $\operatorname{gcd}$.

尝试让 $a,b$ 互质，先令 $b=a-1$，个人没试出来。

再尝试 $b=1$，问题简化为 $a+c+d=\operatorname{lcm}(c,d)$

即

$$\dfrac{cd}{\operatorname{gcd}(c,d)}-c-d=a$$

联想到 $xy-x-y+1=(x-1)(y-1)$ 的形式.

当 $\operatorname{gcd}(c,d)=1$ 时，有 $cd-c-d+1=a+1$ 即 $(c-1)(d-1)=a+1$，为了让 $c,d$ 互质，发现 $a$ 为奇数时即可。

再考虑 $a$ 为偶数时，此时让 $\operatorname{gcd}(c,d)=2$，有类似的式子，但是发现 $a$ 为 $4$ 的倍数时又寄了，这个时候还可以继续考虑 $\operatorname{gcd}(c,d)=4$，但是不妨直接设 $\operatorname{gcd}(c,d)=2^x$，简单推导得：

$(a,1,2^{v+1},a+2^{v+1})$ 满足条件，其中 $a$ 为 $2^v$ 的倍数且不为 $2^{v+1}$ 的倍数。

注意到有范围限制，看起来 $10^9+2^{30}(v=29)$ 时超了，但是仔细一算就会发现 $v=29$ 时 $a\le 2^{29}$，因为 $2^{31}>10^9$。

然后个人觉得这题最好玩的地方出现了：

若 $v=29$，则 $a+2^{v+1}\le2^{29}+2^{30}=1610612736<1634826193$

若 $v<29$，则 $a+2^{v+1}\le10^9+2^{29}=1536870912<1634826193$

卡得挺死的。

update：把代码里的求 $v$ 部分改成了直接用 $\operatorname{lowbit}$ 求 $2^v$。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
ll t,n;

//n=t*2^x,(n,1,2^(x+1),n+2^(x+1))

int main(){
	cin>>t;
	while(t--){
		cin>>n;
		ll x=(n&(-n));
        cout<<1<<" "<<(x<<1)<<" "<<n+(x<<1)<<'\n';
	}
	return 0;
}
```

---

## 作者：_Yonder_ (赞：6)

当时离通过就只有一步之遥啊，都怪 @\_stele_ 在那说找规律（

先把式子变成 $a+b-\gcd(a,b)=\operatorname{lcm}(c,d)-c-d$，为了寻找通解，我们可以尝试让 $b=1$，原式变成了 $a=\operatorname{lcm}(c,d)-c-d$。

考虑 $a$ 为奇数时怎么做，因为我们要求的是奇数的 $a$ 的通解，那么我们考虑让 $c$ 与 $a$ 互质，可以很快的想到 $c=2$，原式变为了 $a=\operatorname{lcm}(2,d)-2-d$。因为 $a$ 为奇数，所以 $d$ 只能是奇数，那么 $a=2d-2-d$，求出来 $d=a+2$。

偶数的情况我给弄了半天没弄出来，测试点 $3$ 让我的做题方向偏向了 $b=1,c=2a,d=3a$。

我们知道，偶数就是某个奇数乘上 $2$ 的次方得来的，然后我们发现 $a,b,c,d$ 乘上 $2$ 的次方后，等式依旧是成立的，那么我们令 $a=2^kp$，最后求出 $b=2^k,c=2^{k+1},d=a+2^{k+1}$。

关于不超过限制的证明：因为 $a\le 10^9$，所以 $a$ 所包含的 $2$ 的次方的因子最大为 $2^{29}$，发现 $a,b,c,d$ 中 $d$ 是最大的，所以以下证明只讨论 $d$。当 $a=2^{29}$ 时，$d=2^{29}+2^{29+1}=1610612736$ 没有超过限制。当 $a\not=2^{29}$ 时，$a$ 最大为 $10^9$，$k$ 最大为 $28$，那么估算 $d$ 的最大值为 $10^9+2^{28+1}=1536870912$，没有超过限制。
# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T;ll a;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&a);
        if(a&1) printf("%lld %lld %lld\n",1ll,a+2,2ll);
        else if(a*3ll<=1634826193) printf("%lld %lld %lld\n",1ll,a*2ll,a*3ll);
        else{ll u=a&-a;printf("%lld %lld %lld\n",u,u<<1,a+(u<<1));}
    }
    return 0;
}
```

---

## 作者：Louis_lxy (赞：6)

看到题面，我的第一直觉就是分奇偶，因为当 $\operatorname{lcm}(c,d)\equiv0\pmod2$。是非常容易找到一组解的。然后看特殊性质，就更加能证明与奇偶相关了。

当 $a\bmod2=1$ 时，令 $b=1,c=2$，此时存在一组解 $d=a+2$ 满足条件。具体推导方式如下：令 $b=1$，此时就变成了 $a+1+c+d=1+\operatorname{lcm}(c,d)$，假设 $\operatorname{lcm}(c,d)\bmod2=1$，则 $c,d$ 中有一个偶数和一个奇数，令 $c\bmod2=0$，此时式子变成：$a+1+c+d=1+2^k\times\operatorname{lcm}(c,\frac{d}{2^k})$。此时存在解 $d$ 的条件为 $(a+1)\bmod(2^k-1)=0$（推导条件的方式就是解方程，这个都会吧），注意到如果 $k=1$ 那么对于所有 $a$ 都存在解。

当 $a\bmod2=0$ 时就更简单了，令 $b=1$，当 $a\bmod2^k\ne0$ 时存在一组解 $c=2^k,d=a+2^k$。因为 $a\le10^9$，而此时 $k$ 最多为 $\lfloor\log_2a\rfloor+1$，而 $\lfloor\log_210^9\rfloor=29$，因此 $k$ 最大为 $29+1=30$，$d$ 最大为 $2^{29}+2^{30}=536870912+1073741824=1610612736$，小于题目中所说的 $1634826193$。具体实现可以直接枚举，时间复杂度 $O(\log V)$，也可以求 $\operatorname{lowbit}(a)$，时间复杂度 $O(1)$。

---

## 作者：_Supernova (赞：4)

### 一、简述题意。

给定整数 $a$，构造 $b$，$c$，$d$，使得：

$a+b+c+d=\gcd(a,b)+ \operatorname{lcm}(c,d)$。

### 二、思路分析。

首先，我们考虑特殊性质：当 $a$ 为奇数时。

$a$ 是奇数有什么用呢？很显然，奇数意味着与 $2$ 互质，这个时候我们就能这样进行构造了：

$a$，$a$，$a+2$，$2$。

注：从左到右依次为 $a$，$b$，$c$，$d$。

接下来，我们思考当 $a$ 为偶数时如何构造。

显然，有个很重要的性质：

$\gcd(\frac{a}{2},\frac{b}{2})=\frac{\gcd(a,b)}{2}$；

$\operatorname{lcm}(\frac{c}{2},\frac{d}{2})=\frac{\operatorname{lcm}(c,d)}{2}$。

很显然，我们需要让 $a$ 变为奇数，利用以上性质，那么我们只需要不断除以 $2$，最后余下来的数我们设为 $A$，则 $A$ 为奇数。

设对 $a$ 进行质因数分解，有 $k$ 个 $2$。

很显然，我们运用特殊性质的构造可以构造出一下数列：

$A$，$A$，$A+2$，$2$。

又因为我们除以了 $k$ 个 $2$ 才得出来的这个式子，所以这 $4$ 个数都要再乘 $k$ 个 $2$，根据之前的性质，等式仍然满足。

于是我们得出最终序列：

$a$，$a$，$(A+2)\times2^k$，$2^{k+1}$。

输出即可，单词询问复杂度 $O(1)$，总时间复杂度 $O(t)$，可以通过。

以下是代码。

### 三、代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef unsigned long long ull;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <pii, int> piii;
typedef long double ld;
ll t, a, k, tmp;
ll qpow(ll base, ll power) {
	ll res = 1;
	while (power) {
		if (power & 1) {
			res *= base;
		}
		power >>= 1;
		base *= base;
	}
	return res;
}
int main(void) {
	cin.tie(0), cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> a;
		tmp = a;
		if (a % 2 == 1) {
			cout << a << ' ' << a + 2 << ' ' << 2 << '\n';
			continue;
		}
		k = 0;
		while (a % 2 == 0) {
			++k;
			a /= 2;
		}
		cout << tmp << ' ' << (a + 2) * qpow(2, k) << ' ' << qpow(2, k + 1) << '\n';
	}
	return 0;
}
```

谢谢大家！！！

注：此题解部分想法来源于这位大佬：[One_JuRuo](https://www.luogu.com.cn/user/86507)

---

## 作者：hh弟中弟 (赞：4)

设 $\gcd(c,d)=x,c=qx,d=ex\ [\gcd(q,e)=1]$，则 $a+b-\gcd(a,b)=(qe-q-e)x$。\
考虑右边 $qe-q-e$ 的取值，当 $q=2,2\nmid e$ 时，它可以表示任意奇数。
- 当 $a$ 为奇数时，可以取 $b=1$，这样左边为 $a$，取 $q=2,e=a+2,x=1$，右边为 $a$，等式成立，此时 $b=1,c=2,d=a+2$，在合法范围中。
- 当 $a$ 为偶数时，考虑将 $a$ 转化为奇数，设 $a=2^kw$，取 $x=2^k$，此时就转化为了 $a$ 为奇数的情况，取 $b=1,q=2,e=w+2,x=2^k$，等式成立，此时 $b=1,c=2\times 2^k,d=(w+2)\times 2^k$，因为 $2^k\le536870912$，所以取值在合法范围中。

综上 $b=1,c=2\times\operatorname{lowbit}(a),d=a+2\times\operatorname{lowbit}(a)$ 时，等式成立。

---

## 作者：_hxh (赞：3)

## 前言

~~第一次在比赛时独立做出绿题（可能我还是太菜了qaq~~

## 正解

题目给我们 $a$，让我们求 $a + b + c + d = \gcd (a,b) + \operatorname{lcm} (c,d)$。**如有多种可能的答案，输出任意一个均可。**

如果可以少考虑一个变量，那么题目是否会变得更简单呢？

既然如有多种可能的答案，输出任意一个均可，那么考虑是否可以将某个变量替换为常数。这里考虑变量 $b$，如果 $b = \gcd (a,b)$，那么就可以消去 $b$ 了。当 $b = 1$ 时 $b = \gcd (a,b) = 1$，那么 $a + 1 + c + d = \gcd (a,1) + \operatorname{lcm} (c,d) = 1 + \operatorname{lcm} (c,d)$，$a + c + d = \operatorname{lcm} (c,d)$。当然，$b = a$ 也是可以的。

还能变得更简单一点吗？$\operatorname{lcm}$ 真的太烦了，还要考虑他们的公因数，索性让他们的最大公因数为 $1$ 好了！考虑 $c,d$ 互质的情况，这时 $\gcd (c,d) = 1$，$\operatorname{lcm} (c,d) = cd$。这样我们就不用讨论 $\operatorname{lcm} (c,d)$ 的大小了。

此时 $a + c + d = cd$，$c,d,cd$ 有没有让你想起什么？对了，$cd - c - d + 1 = (c - 1)(d - 1)$，所以 $a + 1 = cd - c - d + 1 = (c - 1)(d - 1)$。

接下来分奇数偶数讨论。

1. $a$ 为奇数，则 $a + 1$ 为偶数，如果 $c - 1 = 1$，$d - 1 = a + 1$ 是可行的，此时 $c = 2$，$d = a + 2$，且 $\operatorname{lcm} (c,d) = cd$，不错；
2. $a$ 为偶数，则 $a + 1$ 为奇数，按照上面的思虑可以求，这里提供一种新的思路。首先你需要知道，对于三个正整数 $x,y,p$，如果 $\gcd (x,y) = 1$，那么 $\gcd (xp,yp) = p$。那么既然 $a$ 为偶数，那么 $a$ 一定可以表示为 $2 ^ x m$，其中 $m$ 为奇数。如果 $c = 2^k \cdot 2$，$d = a + c$，此时 $\gcd (c,d) = 2^k$，$a + c + d = 2(p + 2) \cdot 2^k = \operatorname{lcm} (c,d)$。

对于答案的限制，当 $a = 2^{29}$ 时有最大答案 $3 \times 2^{29} = 1610612736 < 1634826193$。

这样这道绿题就被我们解决了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,a;
int check(int a)
{
	for (int i = 2;;i *= 2)
		if ((a - i) % (i * 2) == 0)
			return i * 2;
}
signed main()
{
	cin >> t;
	while (t--)
	{
		cin >> a;
		if (a % 2)
			cout << "1 2 " << a + 2 << endl;
		else
		{
			int c = check(a);
			cout << "1 " << c << " " << a + c << endl;
		}
	}
	return 0;
}
```

---

## 作者：Indestructible (赞：3)

一道构造题，写篇题解纪念赛时场切蓝题。

以下记 $a=a_1,b=b_1,c=c_1,d=d_1$ 为 $(a_1,b_1,c_1,d_1)$，即 $a,b,c,d$ 取值的四元组。

首先显然可以构造出 $(a,a,2a,3a)$，$24$ 分。

考虑 $a$ 为奇数的情况，令 $b=a$，则 $\gcd(a,b)=a,\operatorname{lcm}(c,d)=a+c+d$。如果令 $d=2,\operatorname{lcm}(c,2)=2c$，显然 $c=a+2$。构造 $(a,a,a+2,2)$，$29$ 分。

接下来考虑通解。写一个 $7$ 分的暴力，令 $b=a$，打表观察得四元组 $(a,a,2\operatorname{lowbit}(a),a+2\operatorname{lowbit}(a))$，而且它也满足 $24$ 分的解法。交上去，发现 AC 了。

下面证明此做法的正确性。

$$\begin{aligned}
&\text{先证 }a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)\implies\operatorname{lcm}(c,d)=a+c+d=2d\implies\gcd(c,d)=c/2,\\
&\because c=2\operatorname{lowbit}(a),d=a+c,a/\operatorname{lowbit}(a)\bmod2=1,\\
&\therefore\gcd(c,d)=\operatorname{lowbit}(a)\gcd(2,a/\operatorname{lowbit}(a)+2)=\operatorname{lowbit}(a)=c/2,\\
&\text{再证 }a,b,c,d\le1\,634\,826\,193\implies d=a+2\operatorname{lowbit}(a)\le1\,634\,826\,193,\\
&\text{显然 }2^{29}<10^9<2^{30},a+2\operatorname{lowbit}(a)\le3a\le3\times2^{29}\le1\,634\,826\,193.
\end{aligned}$$

代码如下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline void read(int& x){
	int sign=1; x=0;
	char s=getchar();
	while (s<'0'||s>'9'){
		sign=s=='-'?-1:1;
		s=getchar();
	}
	while (s>='0'&&s<='9'){
		x=x*10+s-'0';
		s=getchar();
	}
	x*=sign;
}
int t,a;
signed main(){
	read(t);
	while (t--) read(a), printf("%lld %lld %lld\n", a,
		       (a & -a) << 1, a + ((a & -a) << 1));
	return 0;
}
```

---

## 作者：canwen (赞：3)

Update：$2024.9.10$，加入为什么求出来的答案一定合法。

## 分析
通过暴力枚举，我们可以发现当我们令 $b=a$ 时，必然存在 $c,d$ 使得 $a+b+c+d = \gcd(a,b)+\operatorname{lcm}(c,d)$。因为 $\gcd(a,a)=a$，所以式子简化成 $a+c+d=\operatorname{lcm}(c,d)$。即我们只需要求出 $c,d$，并且，在其中的每一组合法答案中，存在 $d = c+a$，所以问题化解成求 $c$。

喵一眼特殊性质，$a$ 全部为奇数。然后枚举发现，在我们规定 $b=a$ 的情况下，$c=2,d=a+2$ 始终是一组在该性质下的合法答案。

接着考虑偶数，用刚刚的式子写出暴力程序。


```cpp
#include<bits/stdc++.h>
using namespace std;

int lcm(int a,int b){
	return a*b/__gcd(a,b);
}
signed main(){
	for(int i=2;i<=1000;i+=2){
		for(int c=1;c<=10000;c++){
			if((i+c+c+i)==lcm(c,c+i)){
				cout<<"i = "<<i <<" "<<" c= "<<c<<"\n";
				break;
			}
		}
	}
	return 0;
}
```

然后我们会发现 $a$ 每隔一个数是 $4$，观察这些数字的共同点，然后特判掉这些数字。


```cpp
if(i/2%2==1) continue;
```

我们会发现现在的 $a$ 每隔一个数是 $8$，后面的继续特判，依旧是这样，数字不断乘上 $2$。

那就很容易得到这样的思路，我们将答案初始设置为 $2$，设置变量 $x=2$，当 $a \bmod x=0$ 时，$x$ 翻倍，这样直到 $x$ 不能被 $a$ 整除时，$x$ 即为 $c$ 的值。

因为 $a \le 10^{9}$，所以 $x \le 29$。又 $d = x+ a$，所以 $d \le 10^{9}+29$，符合题目限制 $b,c,d \le 1634826193$，故是可行的。
## Code
赛时删掉注释的代码，肥肠简单。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int a;
		scanf("%lld",&a);
		if(a%2==1){
			printf("%lld %lld %lld\n",a,2,a+2);
		}else{
			printf("%lld ",a);
			int c;
			int now=2;
			while(a%now==0){
				now*=2;
			} 
			c=now;
			printf("%lld %lld\n",c,c+a);
		}
	}
	
	return 0;
}
```

---

## 作者：shuqiang (赞：3)

考虑如何化简式子 $a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$。

首先可以把 $\gcd$ 函数消掉，设 $b=1$，则式子可以化成 $a=\operatorname{lcm}(c,d)-c-d$，观察这个式子，还没有什么思路，所以可以打表找规律：
```cpp
#include<iostream>
#include<algorithm>

using namespace std;

int ans[1010][2];

int main(){
	for(int i = 1; i <= 1000; i++){
		for(int j = 1; j <= 1000; j++){
			int t = i*j / __gcd(i, j) - i - j;
			if(t > 0 && t <= 30 && ans[t][0] == 0) ans[t][0] = i, ans[t][1] = j;
		}
	}
	for(int i = 1; i <= 30; i++) cout << i << ' ' << ans[i][0] << ' ' << ans[i][1] << '\n';
	return 0;
}
```
输出为：
```
1 2 3
2 4 6
3 2 5
4 8 12
5 2 7
6 4 10
7 2 9
8 16 24
9 2 11
10 4 14
11 2 13
12 8 20
13 2 15
14 4 18
15 2 17
16 32 48
17 2 19
18 4 22
19 2 21
20 8 28
21 2 23
22 4 26
23 2 25
24 16 40
25 2 27
26 4 30
27 2 29
28 8 36
29 2 31
30 4 34
```

可以发现，对于正整数 $k$，当正整数 $a$ 满足 $a \bmod 2^k=2^{k-1}$，对应的 $c=2^k,d=2^k+a$。

那么因为 $a\le10^9$，所以 $\max_{a=1}^{10^9}2^k+a=1610612736$，可以保证 $b,c,d \le 1634826193$。

```cpp
#include<iostream>

using namespace std;

int read_int(){
    int x = 0; char ch = ' '; while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) {x = x * 10 + ch - '0'; ch = getchar();} return x;
}

int t, a;

int main(){
	t = read_int();
	while(t--){
		a = read_int();
		for(int k = 1; k <= 30; k++){
			if(a % (1 << k) == (1 << (k-1))){
				cout << 1 << ' ' << (1 << k) << ' ' << (1 << k)+a << '\n';
				break;
			}
		}
	}
    return 0;
}
```

---

## 作者：紊莫 (赞：3)

场上的一个极度抽象做法，可以当看个乐子。

首先，不考虑值域限制，我们可以构造出 $b = a, c = 2a, d = 3a$，获得 $24$ 分。

考虑 $a$ 为奇数的情况，发现 $b = a, c = 2, d = a + 2$ 即可。

然后来到 $a$ 为偶数的情况，设 $a = 2^k\times p$，则构造 $b = a, c = 2^{k+1}, d = a + c$ 即可（这实际上包含了奇数的情况）。

证明均直接代入即可。

---

上文所述为本人赛后精简了思路所得。

实际上赛时我的做法是这样的：

首先观察到 $\mathrm{lcm}(c, d) - c - d$ 可以表示出所有的数字，尝试用其表示一个任意的数字 $s$。

然后发现若 $c, d$ 互质的时候相当于 $cd - c - d + 1 = (c-1)(d-1)=s+1$，然后分解并判断。

笑点：$c - 1 = 1$ 的时候直接有解退出了。

然后表示偶数的时候，我发现了上面的构造后没有直接写，当时我担心 $d = a + c$ 会超出限制，然后我随机了一个 $b$，使得要表示的数字中的二的幂次不会太高，然后再用上文的做法。

---

应管理员要求，加入关于解不超过限制的解释。

方法一：采用上文所述的随机，则 $2$ 的幂次很小，显然不超过答案。

方法二：对于构造 $b = a, c = 2^{k+1}, d = a + c$ 来说，考虑 $10^9$ 以内最大的 $2$ 的幂次是 $2^{29}=536870912$，在此时答案不超过 $2^{29}+2^{30}$。

如果这个数字大于了 $2^{29}$，那么 $2$ 的幂次一定小于 $29$，最大可能是 $10^9+2^{29}$。

两个数字均在合法范围内。

---

## 作者：Happy_mouse (赞：2)

# [GCD 与 LCM 问题](https://www.luogu.com.cn/problem/P11036) 题解
[AC 证明](https://www.luogu.com.cn/record/176429327)

## 分析与解答
真是一道神奇的构造题。

首先，经过一些玄学的分析，这道题每一个询问的复杂度不应超过 $O(\log n)$，即满足要求的数中，一定可以取到一些特殊值。

这时候我们就可以开始天马行空地乱搞了（构造题是这样的）。

最特殊的，当然就是 $a=b=\gcd(a,b)$ 的情况了。

接下来就需要构造 $c$ 和 $d$。列出方程：
$$
\begin{aligned}
  a+b+c+d &= \gcd(a,b)+\operatorname{lcm}(c,d)\\
  a+c+d &= \operatorname{lcm}(c,d)\\
  a+c+d &= \frac{cd}{\gcd(c,d)}\\
  a\gcd(c,d)+c\gcd(c,d)+d\gcd(c,d)-cd &= 0\\
  a\gcd(c,d)-(c-\gcd(c,d))(d-\gcd(c,d)) &= -\gcd(c,d)^2\\
  (c-\gcd(c,d))(d-\gcd(c,d)) &= \gcd(c,d)(a+\gcd(c,d))\\
\end{aligned}
$$
继续构造特殊，令 $c-\gcd(c,d)=\gcd(c,d),d-\gcd(c,d)=a+\gcd(c,d)$，即 $c=2\gcd(c,d),d=a+2\gcd(c,d)$。

为了保证 $c=2\gcd(c,d)$，需保证 $a$ 中为 $2$ 的因子跟 $\gcd(c,d)$ 中的同样多，~~原因显而易见，~~ 多了会导致 $\gcd(c,d)=2\gcd(c,d)$ 矛盾，少了会导致 $\gcd(c,d)\nmid d$。

所以设 $a=2^kp$（$k$ 为自然数，$2\nmid p$），则 $\gcd(c,d)=2^k$。

综上：
$$
b=a\\
c=2\times 2^k\\
d=(p+2)2^k
$$

现在需要做的最后一件事，就是~~抄代码~~看答案范围啦~

易发现三个值当中最大的一个是 $d$，最劣情况为恰好是 $a=2^k$ 形式的，取值会是 $d=3\times a$。经过计算，我们非常幸运地发现：最大的满足条件的 $k$ 使得 $a$ 满足数据范围的是 $29$，对应的 $d=3\times 2^{29}=1610612736 < 1634826193$，只差一点就爆范围了。

还好还好 ~~，这个出题人和 Ta 的 QQ 号还有点良心~~。
## 代码
较为简单，不予注释。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int a;
		cin>>a;
        int b=a,k=1;
        while(!(a&1)){
            a>>=1;
            k*=2;
        }
        int c=2*k,d=(a+2)*k;
        cout<<b<<' '<<c<<' '<<d<<'\n';
	}
	return 0;
}
```
写题解不易，路过/认真看过的大佬们都给个赞呗。

---

## 作者：Dangerise (赞：2)

做得为数不多的构造题，或许从中可以窥得一些构造题的技巧。

要构造一组答案，其实并不需要这个答案是“普遍的”，我们可以构造一些具有特殊性质的答案，并且它们仍然满足题目所要求的的性质。

例如这题，为了方便构造，我们显然可以直接假设

$$\gcd(a,b) = \gcd(c,d)$$

设 $g=\gcd(a,b)=\gcd(c,d)$

$a=k_1g , b=k_2g , c=k_3g,d=k_4g$

其中 $k_1,k_2$ 互质 , $k_3,k_4$ 互质

我们对原式进行一些变化

$$a+b-\gcd(a,b)=\operatorname{lcm}(c,d)-c-d$$

$$k_1g+k_2g-g=k_3k_4g-k_3g-k_4g$$

$$k_1g+k_2g-g+g=k_3k_4g-k_3g-k_4g+g$$

$$(k_1+k_2)g=(k_3-1)(k_4-1)g$$

$$k_1+k_2=(k_3-1)(k_4-1)$$

于是我们成功将问题转化了

我们先考虑如果已知左边部分的值，如何得到互质的 $k_3,k_4$

当 $(k_3-1)(k_4-1) = x , x \mod 2 =0$

显然，一组解是 $k_3=2,k_4=x+1$，由于 $x$ 是偶数，$k_4$ 是奇数，两数显然互质。

那么，我们再回过头考虑，如何使 $k_1+k_2$ 为偶数。

只要，我们令 $k_1$ 为 $a$ 的一个奇数约数，$k_2$ 为 $1$ , 那么显然 $(k_1 + k_2) \mod 2 = 0, \gcd(k_1,k_2) = 1$

考虑到答案不能超过 $1634826193$ ,我们应该使 $g$ 尽可能小，$k_1$ 尽可能大。

Ac code 

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int qread() {
	int ans=0;
	char c=getchar();
	bool f=0;
	while(c<'0'||c>'9') {
		if(c=='-') {
			f=1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		ans=ans*10+c-'0';
		c=getchar();
	}
	if(f) {
		return -ans;
	} else {
		return ans;
	}
}

const int N=114514;
const int M=1634826193;

signed main() {
	int t=qread();

	while(t--) {
		int a=qread();
		
		int x=a;
		while(x%2==0){
			x/=2;
		}
		
		// x 为 a 的最大的奇数约数 
		
		int k1=x,g=a/x;

		int k2=1;

		int k3=2,k4=k1+k2+1;

		int b=k2*g,c=k3*g,d=k4*g;

		printf("%lld %lld %lld\n",b,c,d);
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：2)

### 思路

构造题。

先考虑暴力，直接枚举 $b,c,d$。

通过观察可以发现对于每一个 $a$，$b$ 总等于 $1$，$d$ 等于 $a+c$。

设 $2^p\Vert a$，则 $c$ 等于 $2^{p+1}$。

考虑证明其正确性，及证明：
$$
a+1+2^{p+1}+a+2^{p+1}=1+\frac{2^{p+1}\times (a+2^{p+1})}{\gcd(2^{p+1},a+2^{p+1})}
$$
整理后得：
$$
2\times a+2^{p+2}=\frac{2^{p+1}\times (a+2^{p+1})}{\gcd(2^{p+1},a+2^{p+1})}
$$
因为 $2^p\Vert a$，所以 $\gcd(2^{p+1},a+2^{p+1})=2^p$。

所以有：
$$
2\times a+2^{p+2}=2\times (a+2^{p+1})
$$
故成立。

证明 $b,c,d$ 中最大的一个数小于等于 $1634826193$。

由于 $a,b,c,d$ 均为正整数，故 $d$ 为其中最大的。$10^{9}$ 以内最大的 $2$ 的整数次方是 $2^{29}=536870912$。

当 $p\le 28$ 时，$d\le 10^9+2^{29}=1536870912$，符合条件。

当 $p=29$ 时，$d=2^{29}\times 3=1610612736$，符合条件。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll get(ll a)//得到2的p次方恰整除a的p加1
{
	int ans=1;
	while(!(a&1))//可以除以2
	{
		a/=2;
		ans<<=1;
	}
	return ans<<1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T,a;
	cin>>T;
	while(T--)
	{
		cin>>a;
		cout<<"1 "<<get(a)<<' '<<a+get(a)<<'\n';
	}
	return 0;
}
```

---

## 作者：zzx114514 (赞：2)

# 题目大意
给定正整数 $a$，找到一组正整数 $b,c,d$ 使得 $a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$。
# 解题思路
## 一、打表找规律
前四组答案可以为：
```
a b c d
1 1 2 3
2 1 4 6
3 1 2 5
4 1 8 12
```
注意到 $b=1,d=a+c$。  
要找 $a,c$ 的关系，可以转成二进制看：
```
a b c d
1 1 10 11
10 1 100 110
11 1 10 101
100 1 1000 1100
```
注意到 $c$ 等于 $a$ 的最右边的 $1$ 所代表的值 $\times2$，即 $c=\operatorname{lowbit}(a)\times2$，`lowbit(a)=a&-a`，不知道 `lowbit` 的[点这里](https://blog.csdn.net/shenglizaiwo1/article/details/133991912)。
## 二、证明
以下设 $\operatorname{lowbit}(a)=2^k$。  
$a+b+c+d=a+1+2^k\times2+2^k\times2+a=2a+2^{k+2}+1$  
$\gcd(a,b)=\gcd(a,1)=1$  
$\operatorname{lcm}(c,d)=\operatorname{lcm}(2^{k+1},2^{k+1}+a)$  


---


为了求出 $\operatorname{lcm}$，我们先计算 $\gcd$。  
由于 $k$ 是 $a$ 的最低位 $1$，则 $a$ 一定是 $2^k$ 的倍数（因为 $a$ 的后 $k-1$ 位都是 $0$）。  
同理，$a-2^k$ 一定是 $2^{k+1}$ 的倍数，因而 $a$ 一定不是 $2^{k+1}$ 的倍数。  
所以，$\gcd(2^{k+1},2^{k+1}+a)=\gcd(2\times2^k,2^k(2+m))=2^k$，其中 $m$ 为奇数。  
所以，$\operatorname{lcm}(2^{k+1},2^{k+1}+a)=\frac{2^{k+1}\cdot(2^{k+1}+a)}{\gcd(2^{k+1},2^{k+1}+a)}=\frac{2^{k+1}\cdot(2^{k+1}+a)}{2^k}=2(2^{k+1}+a)=2^{k+2}+2a$,  
$\gcd(a,b)+\operatorname{lcm}(c,d)=1+2^{k+2}+2a=a+b+c+d$，证毕。
## 补充限制证明
### 一、检验法
经检验，所有满足题目要求的 $a$ 计算得到的答案均满足题目限制，没有超限。
### 二、证明
由于 $\left \lfloor \log_210^9 \right \rfloor =29$，所以 $\operatorname{lowbit}(a)_{max}=a=2^{29}=536870912$，$d=a+2*\operatorname{lowbit}(a)_{max}=1610612736\le1634826193$；而接下来 $a$ 最多增长 $463129088$，$2*\operatorname{lowbit}(a)$ 最少减小 $2^{29}\times2-2^{28}\times2=536870912$，即使这两者同时成立，答案也一定减小，但事实上这两者不可能同时成立，答案只会更小，因此当 $a=2^{29}$ 时 $d$ 取最大值，并且 $d$ 是三者中最大的数，从而保证了答案满足题目要求。


---

 _经程序检验，$d=1610612736$ 的确是最大答案。_ 
# 完整代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t,a;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a;
		cout<<1<<' '<<((a&-a)<<1)<<' '<<(a+((a&-a)<<1))<<endl;
	}
	return 0;
}
```

---

## 作者：mahaihang1 (赞：2)

## 思路
为了简化问题，我们不妨取 $b=a$，原式简化为 $a+c+d=\operatorname{lcm}(c,d)$

观察特殊性质，发现有 $a$ 为奇数的部分分，很容易想到讨论 $a$ 的奇偶性。

### 当 $a$ 为奇数时
假设 $\gcd(c,d)=1$，则有 $a+c+d=c \times d$，因此有 $c=\frac {a+d} {d-1}$，不妨取 $d=2$，此时 $c$ 为奇数，符合要求。

一组答案为 $\begin{cases}
   b = a\\
   c = a+2\\
   d = 2
\end{cases}$

### 当 $a$ 为偶数时
发现当 $\gcd(c,d)=1$ 时原式不成立，不妨设 $k=\gcd(a,b)$ 原式化为 $a+c+d=\frac {c \times d} {k}$，则有 $c=k \times \frac {a+d} {d-k}$。

我们不妨设 $c=k \times x$，其中 $x$ 为奇数

当 $k=2$ 时，取$d=4$，有$a \equiv 2 \pmod 4$，有解。

一组答案为 $\begin{cases}
   b = a\\
   c = a+4\\
   d = 4
\end{cases}$

当 $k=4$ 时，取$d=8$，有$a \equiv 4 \pmod 8$，有解。

一组答案为 $\begin{cases}
   b = a\\
   c = a+8\\
   d = 8
\end{cases}$

经过上面的讨论答案似乎有规律，因为当 $a$ 为奇数时可以描述为：

当 $k=1$ 时，取$d=2$，有$a \equiv 1 \pmod 2$，有解。

一组答案为 $\begin{cases}
   b = a\\
   c = a+2\\
   d = 2
\end{cases}$

## 结论
对于一个 $a$ 我们找到最小的 $2$ 的正整数次幂 $x$，使得 $a \equiv\frac x 2 \pmod x$，

则有一组答案为$\begin{cases}
   b = a\\
   c = a+x\\
   d = x
\end{cases}$

同时因为 $1 \le a \le 10^9$，$c$ 最大是在 $a=2^{29}$ 时取到，为 $1610612736 <1634826193$，因此所有范围内的 $a$ 都有解。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,a,k;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>a;
		k=2;
		while(a%k==0) k*=2;
		cout<<a<<" "<<a+k<<" "<<k<<endl;
	}
	return 0;
}
```

---

## 作者：飞升的海绵bb (赞：2)

给定一个正整数 $a\le 10^9$，请你构造三个正整数 $b,c,d\le 1\,634\,826\,193$ 使得 $a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$。数据范围的限制使得一些很显见的解是不满足条件的。

$b,c,d$ 考虑起来太多了，于是令 $b=1$，原式即为 $1+a+c+d=1+\operatorname{lcm}(c,d)$，即为 $\frac {c\times d}{\gcd(c,d)}-c-d=a$。

发现求解还是有点困难，于是假使 $c,d$ 互质，则有 $c\times d-c-d=a$，对于该不定方程，显然有 $c=2,d=a+c,a\bmod 2\neq 0$ 满足条件，也即特殊性质里的“$a$ 为奇数”。

由此，我们可以继续扩展至 $a$ 为偶数的情况。此时，$\gcd(c,d)\neq 1$，于是不妨令 $\gcd(c,d)=2$，于是原式可以写成 $\frac {c\times d} 2-c-d=a$。我们考虑尽量用一个通用的规律来进行构造，于是不难发现一组不错的解 $c=4,d=a+c,a\bmod 4\neq 0$ 满足条件。这里 $a$ 又不能是 $4$ 的倍数了。

等等，欸？是不是找到规律了？归纳，可以发现若 $a= 2^r \times \prod_{i=1}^kp_i^{q_i}$（$p_i$ 为素数且 $p_i\neq2$），则 $b=1,c=2^{r+1},d=a+c$。

可以计算发现：当 $a=2^{29}$ 时 $c=2^{30},d=2^{29}+2^{30}=1\,610\,612\,736 < 1\,634\,826\,193$；当 $2^{29}< a \le 10^9$ 时 $c \le 2^{29},d<10^9+2^{29}=1\,536\,870\,912<1\,634\,826\,193$ 不会超过数据范围限制。

### AC 代码

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int a;
        cin >> a;
        int ta = a;
        int c = 2;
        while (a % 2 == 0)
        {
            c *= 2;
            a /= 2;
        }
        cout << 1 << " " << c << " " << ta + c << "\n";
    }
    return 0;
}
```

---

## 作者：A_small_WA (赞：1)

在做这题之前，你应该了解一个常识：

$$\operatorname{lcm}(m,n)=m\times n\div \gcd(m,n)$$

另外，观察发现，测试点 $4$ 有特殊性质 $a$ 为奇数，可以从这里入手。

假设 $a$ 为偶数，令 $k=\gcd(a,b)$。

我们考虑最简单的情况，即 $c,d$ 互质。此时， $\operatorname{lcm}(c,d)=c\times d$，则原式变为 $a+b+c+d=c\times d+k$。

![](https://cdn.luogu.com.cn/upload/image_hosting/vj2mdg51.png)

易知 $b,c,d\le 10^9+1$，不会超出 $1 634 826 193$。

偷懒不用 $\LaTeX$ (bushi)

另外一种情况是 $a$ 为偶数，则此时设 $\gcd(c,d)=2$，那 $\operatorname{lcm}(c,d)=c\times d\div 2$。

同样列出原式 $=a+b+c+d=c\times d\div 2+k$

![](https://cdn.luogu.com.cn/upload/image_hosting/ofq449nh.png)

这里的建议是从 $1$ 到 $100$ 枚举每一个 $b$，如果 枚举到 $i$ 时 $a+b+\gcd(a,b)\equiv2\pmod{4}$ 这样才能保证 $\operatorname{lcm}(c,d)=c\times d\div 2$。不用担心超复杂度，因为 $b$ 从 $3$ 枚举到 $100$ 就可以了。

此时 $c=4,d=a+b-k$ 满足条件。

**由于 $b\le101$，所以 $a+b-k\le 10^9+101$。即 $b,c,d\le 10^9+101$，不会超限。**

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>a;
		if(a%2==1){
			a++;
			cout<<1<<" "<<2<<" "<<a+1<<'\n';
		}else if(a%4==2){
			cout<<2<<" "<<4<<" "<<a+4<<'\n';
      //写的时候脑子抽了，其实可以直接并在一起的。
		}else{
			for(long long i=3;i<=109;i+=2){
				if(__gcd(a,i)==1&&(a+i+3)%4!=0){
					cout<<i<<" "<<4<<" "<<a+i+3<<'\n';
					break;
				}
			}
		}
	}
	return 0;
}
```
一些有趣的事

- 你知道为什么我后来会设 $\gcd(c,d)=2$ 吗？因为样例第四组数据就是这样。
- 赛时我 17:58 才 AC 的...
- 代码上面几行的粗体字是题解被打回后才加的。

这是蒟蒻的第 $13$ 篇题解，感谢观看。

---

## 作者：_H17_ (赞：1)

## 题外话

挺有意思的一个数学题。

比赛没打，没看部分分，导致觉得很难。

## 题目分析

首先，看到 $\gcd(a,b)$ 你们想到了什么？根据经验，通常这种题目有以下几个方向：

- $\gcd(a,b)\le \min(a,b)$；

- $\gcd(a,0)=a$；

- $\gcd(a,1)=1$。

注意到这道题要求是正整数，而且和大小关系不大，考虑最后一种方向。

对这道题还是比较适用的，考虑让 $b=1$。

这样方程化简为 $a+c+d=\operatorname{lcm}(c,d)$。

怎么办呢？看见数据范围中 #4 只有奇数，这暗示了这与奇偶性有关系。

### 分类讨论

若 $a\equiv 1 \pmod {2}$，显然要把这个东西带入原方程。

$1+c+d\equiv \operatorname{lcm}(c,d)\pmod{2}$。

如果 $c,d$ 奇偶性相同（对 $2$ 取余是 $k$），那么左式为 $1$，右式为 $k$，也就是 $c,d$ 同奇数即可。

若 $c,d$ 奇偶性不同，左式为 $0$，右式为 $0$。

也就是只要有一个奇数即可。

考虑 $c=1$，得到 $a+c+d=d$，显然无解。

考虑 $c=2$，得到 $a+2+d=\operatorname{lcm}(2,d)$，此时 $d$ 必为奇数，则 $d=a+2$。

此时 $b=1,c=2,d=a+2$。

考虑另一种情况：$a\equiv 0\pmod {2}$。

考虑把 $a,c,d$ 统一除以 $2$，直到 $a$ 是奇数，然后再乘回来。

若累计要除以 $2^x$（显然 $x=\operatorname{lowbit}(a)-1$），则 $c=2^{x+1},d=(a+2)\times 2^x=2^x\times a+2^{x+1}$。

显然此时 $d$ 太大了。

不过这给我们一个启发：从 $\operatorname{lowbit}(a)$ 入手，只是我们要换个方法。

我们发现 $2^x|a$，此时 $a$ 的系数仍然有 $2^x$，考虑把系数扔掉，考虑把 $d$ 改为 $a+2^{x+1}$。

假设 $a=a_0\times 2^x$，对于 $c=2^{x+1},d=a+2^{x+1}$。

方程左边是 $(a_0+2)\times 2^{x+1}$，右边是 $2^x\times \operatorname{lcm}(2,a_0+2)$

相消之后得到 $2\times (a_0+2)=2\times a_0+4$（奇偶性）。

所以最终 $a=a,b=1,c=2^{x+1},d=a+c$。

显然 $d=a+2^{x+1}$ 是最大的，带入进去 $10^9+2^{29}=1536870912$ 足以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,bit,tmp;
signed main(){
    for(cin>>T;T;--T){
        cin>>n;
        bit=1;
        for(int t=n;t&1^1;t>>=1){
            bit++;
        }
        tmp=(1ll<<bit);
        cout<<"1 "<<tmp<<' '<<n+tmp<<'\n';
    }
    return 0;
}
```

## 其他解法

$b=1,c=2\times\operatorname{lowbit}(a),d=2\times\operatorname{lowbit}(a)+a$。

至于怎么想的，我也不知道，我太菜了。

证明我还是会的：

设 $\operatorname{lowbit}(a)=x$。

则 $a+1+2\times x+(2\times x+a)=1+\operatorname{lcm}(2\times x,2\times x+a)$

即 $(2\times a+4\times x)\times\gcd(2\times x,a)=4\times x^2+2\times a\times x$

即 $(a+2\times x)\times\gcd(2\times x,a)=x\times(2\times x+a)$

即 $x=\gcd(2\times x,a)$

则 $a=k\times x,\gcd(k,2)=0$。

也就是说 $a$ 是 $x$ 的奇数倍才行

此时除去 $\operatorname{lowbit}$ 只剩下奇数了。

---

## 作者：The_foolishest_OIer (赞：1)

## 前言

一道十分明显的数学题。

本题有部分内容选自以下链接：[这篇](https://www.luogu.com.cn/article/q8ctipme)

## 打表做法

比赛时想了 $30$ 分钟就写了一个暴力得了 $7$ 分，于是我开始找起了规律。

$7$ 分代码（想出来不是很难）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,a,flag;
int gcd (int x,int y){
	if (!y) return x;
	return gcd(y,x % y);
}
int lcm (int x,int y){
	return x / gcd(x,y) * y;
}
int main(){
	cin >> t;
	while (t--){
		cin >> a;
		flag = 1;
        //枚举 b,c,d
		for (int i = 1 ; i <= 100 && flag ; i++){
		    for (int j = 1 ; j <= 100 && flag ; j++){
		        for (int k = 1 ; k <= 100 && flag ; k++){
		            if (a + i + j + k == gcd(a,i) + lcm(j,k)){
		            	printf ("%d %d %d\n",i,j,k);
		            	flag = 0;
					}
				}
			}
		}
	}
	return 0;
}
```

下列是找规律过程：

|$a$|$(b,c,d)$|
|:-:|:-:|
|$2$|$(1,4,6)$|
|$4$|$(1,8,12)$|
|$8$|$(1,16,24)$|
|$16$|$(1,32,48)$|
|$32$|$(1,64,96)$|

这个规律很明显，即 $b = 1,c = 2 \times a,d = c + a$。

当我满怀信心的提交时，获得了 $0$ 分好成绩。

那就继续找规律：

|$a$|$(b,c,d)$|
|:-:|:-:|
|$2$|$(1,4,6)$|
|$4$|$(1,8,12)$|
|$6$|$(1,4,10)$|
|$8$|$(1,16,24)$|
|$3$|$(1,2,5)$|
|$11$|$(1,2,13)$|

这个规律比较难找，但是也能看出来，即 $b = 1,c = 2^{m + 1},d = c + n$，（其中 $m$ 是这个数有多少个质因子 $2$）。

代码在后面。

## 数学做法（参考 SFlyer 大佬）

我们可以令 $b=a$，则 $a+c+d = \operatorname{lcm}(c,d)$，即 $cd - c - d = a$，则 $(c-1) \times (d-1) = a + 1$。

接下来进行分类讨论：

当 $2 \nmid n$ 时，$2 \mid n + 1$，直接让 $c=2,d=a+2$ 即可

当 $2 \mid n$ 时，设 $a=2^k \times p$（其中 $2 \nmid p$），则 $c = 2^k,d = (p+2) \times 2^k$ 时，式子成立。

接下来，考虑关于 $b,c,d$ 的限制。

因为要使 $c$ 最大，则 $a$ 最大是 $2^{29}$ 左右，$c$ 最大是 $2^{29}$，则 $d$ 最大是 $(1+2) \times 2^{29} \le 1634826193$。

代码与打表做法的类似。

## AC Code


```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long a,y,sum;
int main(){
    cin >> t;
    while (t--){
    	cin >> a;
    	y = a;
    	sum = 2;
    	while (a % 2 == 0) sum *= 2,a /= 2; //统计有多少个因子2
    	printf ("1 %lld %lld\n",sum,y + sum);
	}
	return 0;
}
```

## 总结

如果有些题不会，可以尝试先拿暴力分，再去打表找规律。

祝所有人 CSP 2024 RP++！

---

## 作者：Adolfo_North (赞：0)

给一种非常抽象的做法。

首先暴力打个表（为 $1\le a \le 50$ 时的答案）：

```cpp
1 1 2 3
2 1 4 6
3 1 2 5
4 1 8 12
5 1 2 7
6 1 4 10
7 1 2 9
8 1 16 24
9 1 2 11
10 1 4 14
11 1 2 13
12 1 8 20
13 1 2 15
14 1 4 18
15 1 2 17
16 1 32 48
17 1 2 19
18 1 4 22
19 1 2 21
20 1 8 28
21 1 2 23
22 1 4 26
23 1 2 25
24 1 16 40
25 1 2 27
26 1 4 30
27 1 2 29
28 1 8 36
29 1 2 31
30 1 4 34
31 1 2 33
32 1 64 96
33 1 2 35
34 1 4 38
35 1 2 37
36 1 8 44
37 1 2 39
38 1 4 42
39 1 2 41
40 1 16 56
41 1 2 43
42 1 4 46
43 1 2 45
44 1 8 52
45 1 2 47
46 1 4 50
47 1 2 49
48 1 32 80
49 1 2 51
50 1 4 54
```

观察到 $b$ 始终等于 $1$，且 $c$ 始终为 $2^x$ 且 $x$ 始终为自然数。另外的，始终有 $d=a+c$。

便可写出如下代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(int u){
	for(int i=1;i<=1000;i++){
		for(int j=1;j<=1000;j++){
			for(int k=1;k<=1000;k++){
				int g=__gcd(u,i)+j*k/__gcd(j,k);
				if(g==u+i+j+k){
					cout<<u<<' '<<i<<' '<<j<<' '<<k<<'\n';
					return;
				}
			}	
		}
	}
}
bool check(int a,int b,int c,int d){
	int g=__gcd(a,b)+c*d/__gcd(c,d);
	if(g==a+b+c+d){
		return 1;
	}
	return 0;
}
signed main(){
//	for(int i=1;i<=50;i++) solve(i);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int a,b=1,c=2,d;
		cin>>a;
		for(;c<=1634826193;c*=2){
			d=a+c;
			if(check(a,b,c,d)) {
				cout<<b<<' '<<c<<' '<<d<<'\n';
				break;
			}
		}
	}
	return 0;
}
```

证明也很简单（下文中 $x$ 始终为自然数）：

$a$ 为奇数，则有解 $b=1，c=2，d=a+c$。

$a$ 为偶数，则 $a=2^xa'$，构造 $b=1，c=2^{x+1}，d=a+c$ 即可。

解不超过限制的证明：

因为：$a \le 10^9$，所以 $x+1 \le 30$，$d \le 1610612736=2^{29}+2^{30}$。显然符合题意。

---

## 作者：封禁用户 (赞：0)

# P11036 【MX-X3-T3】「RiOI-4」GCD 与 LCM 问题题解

首先说一句题外话，~这道题当时我想了将近两个半小时才打出来呢~。

## 题目大意

$$a+b+c+d=\gcd(a,b)+\operatorname{lcm}(c,d)$$，已知 $a$，求 $b,c,d$。

## 思路分析

首先发现， $a$ ， $b$ 需要互质，所以我们让 $b = 1$（简化一波）。

然后发现，$a + b - \gcd(a,b) = \operatorname{lcm}(c,d) - c - d$。

所以，$\operatorname{lcm}(c,d)-c-d=a$。

那么很简单啊，$c = 2 \times a,d=3 \times a$，能够达到要求。

于是开开心心的打完代码（~~期望得分：24pts~~）

```cpp
#include<bits/stdc++.h>

using namespace std;
#define int long long


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(), cout.tie();
    int t;
    cin >> t;
    while (t--) {
        int a;
        cin >> a;
        cout << 1 << " " << 2 * a << " " << 3 * a << "\n";
    }
}
```

~~完 damn 了，MatrixGroup 无耻的卡了大小~~

那么再次思考，发现奇数可以的 $c = 2,d = a + 2$（由于不是最后公式，所以请读者自证此公式）。

好，$53pts$ 到手了。

~~完 damn 了，公式又写不出来了。~~

那么在小 X 的疯狂计算（~~红温了~~）下，终于：

$$c = 2(a \And -a),d=a+(2(a\And-a)),b=1$$

完成啦！(~~我是不会告诉你我是打完 $10$ 以内的数字的表才发现的~~)  。

那么，这个公式是怎么推导的拟？

首先，把目光放回 $\operatorname{lcm}(c,d)-c-d=a$ 上。

由于 $\operatorname{lcm}(c,d) = x \times y \times \gcd(c,d)$。那么我们就把 $\gcd(c,d)$ 当成 $z$。

发现，为了让 $gcd(c,d) = z$，则我们让 $c = 2z$（再次简化一波），$d$ 就需要是 $zq$（$q$ 为奇数），保证了 $z$ 和 $q$ 互质。

那怎么才能让 $2qz = 2z + qz + a$ 呢？

那么 $2q - q - 2 = a \div z$ ， 就是 $q - 2 = a \div z$。

啊！那就是 $(a + 2z) \div z = q$ 。

那就是 $d = a + 2z$。

（~~好开心啊~~）。

那 $z$ 是什么呢？为了让 $a \div z = q - 2$（也就是一个奇数），那就让他等于 $\operatorname{lowbit}(a)$，也就是 $a \And -a$。

（~~好开心啊~~）。

那么，这个公式对不对呢？

让我们来证明一下：

假设它是对的，则：
$$
\operatorname{lcm}(a+(2(a\And-a)),2(a\And-a)) - (a+4(a\And-a)) = a\\
\therefore (a+(2(a\And-a)) \times 2(a\And-a)) \div \gcd(a+(2(a\And-a)),2(a\And-a)) - (a+4(a\And -a))=a\\
\therefore (a+(2(a\And-a))\times 2(a\And-a)) \div (a \And -a) - (a+4(a\And -a)) = a\\
\therefore (a+(2(a\And-a))\times 2(a\And-a)) \div (a \And -a) = 2a+4(a \And -a)\\
\therefore 2(a\And -a) \cdot a + 4(a\And -a)^2\div (a \And -a) = 2a+4(a\And-a)\\
\therefore (2a + 4(a\And -a)) \cdot (a \And-a) \div (a \And -a)  = 2a+4(a\And-a)\\
\therefore 2a + 4(a\And -a) = 2a+4(a\And-a)\\
$$
证毕！

那么，取值呢？

取值的最大值 $d$ 的最大值为 $2^{29} \times 3 = 1610612736$，刚好不超。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
#define int long long


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(), cout.tie();
    int t;
    cin >> t;
    while (t--) {
        int a;
        cin >> a;
        cout << 1 << " " << (a & -a) * 2 << " " << a + (a & -a) * 2 << "\n";
    }
}
```

## 再次证明

注意到：

$$\operatorname{lcm}(a+(2(a\And-a)),2(a\And-a)) - (a+4(a\And-a)) = a$$

证毕！

~~华丽收尾。~~

---

## 作者：_Jocularly_ (赞：0)

首先观察特殊性质，打表求出当 $a$ 为奇数的时候或者瞪眼法，显然可以得到一组解 $b = 1,c = 2,d = a+2$，证明：因为 $a$ 为奇数，那么 $a + 2$ 也为奇数，那么显然 $\gcd(a+2,2)=1$，那么 $\operatorname{lcm}(c,d)=c\times d \div \gcd(c,d)=2a+4$，那么 $a+b+c+d=a+1+2+a+2=2a+5=1+2a+4=\gcd(a,b)+\operatorname{lcm}(c,d)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int a;
int lowbit(int x){
    return (x & (-x));
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> t;
    while(t--){
        cin >> a;
        cout << "1 2 " << a + 2 << endl;
    }
    return 0;
}
```

我们可以通过类比奇数的方式，得出偶数的解法。因为偶数肯定至少有一个因数 $2$，那么我们可以任意分解一个偶数 $a = u \times 2^{k}$，此时我们会发现，因为不能继续分解因数 $2$，那么 $u$ 肯定是一个奇数，那么 $u$ 的解满足上面所述的解，此时从 $u$ 变到 $a$ 乘了 $2^{k}$，此时根据等式的性质，$b$，$c$，$d$ 的值都同时乘 $2^{k}$ 依然满足条件。发现此时 $2^{k}$ 就相当于求 $\operatorname{lowbit}(a)$，即 $(a \&-a)$。单次时间复杂度 $O(1)$。

发现 $d$ 最大，当最大为 $a = 2^{29}$ 时，那么最大 $d = 3a = 1610672736 < 1634826193$，小于上限，构造正确。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int a;
int lowbit(int x){
    return (x & (-x));
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> t;
    while(t--){
        cin >> a;
        int cnt = lowbit(a);
        int u = a / cnt;
        cout << cnt << " " << cnt * 2 << " " << (u + 2)*cnt << endl;
    }
    return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# 思路
## 题目要求
求任意四个数 $a$、$b$、$c$、$d$。满足 $a + b + c + d = \gcd(a,b) + \operatorname{lcm}(c,d)$。
## 做法
可以让 $b=a$，则 $a + c + d = \operatorname{lcm}(c,d)$。

最优的方法是让 $c$ 和 $d$ 互质，可得 $a + c + d = cd$，进一步推算可得 $(c-1)(d-1) = a + 1$。

接下来 $a$ 有两种情况：

- $a$ 不能被 $2$ 整除；
- $a$ 能被 $2$ 整除。

若 $a$ 不能被 $2$ 整除，因为 $\gcd(2,a+2) = 1$，所以让 $c = 2$，$d = a + 2$ 即可。

若 $a$ 能被 $2$ 整除，设 $a = 2^k \times x$，且 $x$ 不能被 $2$ 整除。则 $c = 2 \times 2^k$，$d = (x+2) \times 2^k$，所以 $\gcd(c,d) = 2^k$，最后也可以得到 $\operatorname{lcm}(c,d) - c - d = a$。

## 为何不超过限制
因为 $a \le 10^{9}$，所以这里的 $k \le 29$。

如果 $k \le 28$，那么 $d \le 10^9 + 2^{29} = 1536870912 < 1634826193$。

如果 $k = 29$，这时 $a$ 就只能为 $2^{29}$（因为如果再乘任意一个大于 $1$ 的数就超了），那么 $d = (1+2) \times 2^{29} = 3 \times 2^{29} = 1610612736 < 1634826193$。

很显然这种构造是对的。

于是就有了以下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	int t;
	cin >>t;
	while(t--)
	{
		ll a,b,c,d;
		cin >>a;
		b=a;
		ll op=1;
		while (a%2==0)
		{
			a/=2;
			op*=2;
		}
		c=2;
		d=a+2;
		c*=op,d*=op;
		cout <<b<<" "<<c<<" "<<d<<"\n";
	}
	return 0;
}
```

---

## 作者：int08 (赞：0)

## 前言

随便看到的，那做一做。

_"Please enjoy it."_

# Solution

首先观察这个式子，第一反应是：把 $a,b$ 扔到左边，$c,d$ 扔到右边，**尽可能地让等式两边独立，很多时候都会让问题更简单。**

~~不过也不绝对，找到反例别骂我。~~

那么式子就会变成：

$$a+b-\gcd(a,b)=\text{lcm}(c,d)-c-d$$

这个式子左边有一些限制，右边完全没有，那我们先尝试搞一下右边，看看能凑出什么有趣的东西。

然后简单尝试，发现当一个奇数一个 $2$，有奇效：$c=o,d=2,\text{lcm}(c,d)-c-d=o-2$。

换句话说，**任意奇数都可以被表示出来**。

那我们能不能想办法给左边凑个奇数呢？

$a$ 为奇数时候显然可以：$b=1,a+b-\gcd(a,b)=a$，就是奇数。

$a$ 为偶数的时候不是不简单，而是压根不行，咋整？

观察到，当 $c,d$ 同时乘以 $2$，右式就乘 $2$，而任意奇数都可以被表示为 $a2^i$，其中 $a$ 为奇数。

所以任意数都可以被表示出来，左边就没有压力了，随便 $b=1$ 即可。

代码是极其简单的。

_"Am I tripping?"_

## 上界

如果你想完上面觉得很对，直接写好交上去，你就会发现你过了（）。

但是细想，我们从来没有考虑过会不会超界。

于是写一份代码暴力测试一下：~~居然只跑了 $0.9$ 秒。~~ 上界是 $1610612736$，意外的卡得紧。

~~暴力证明了卡不满也算证明吧~~
证明一下：发现 $d=2\text{lowbit}(a)$，最大 $2^{30}$ 超不掉，

$c$ 只有在 $o=3$ 时候可能爆炸，但是此时 $a=\text{lowbit}(a)$，最大就是 $c=3\times2^{29}$ 卡到上面的那个数。 

## AC Code
_"Thank you very much!"_

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		int a;cin>>a;
		int b=1;
		int q=1;
		while(a%2==0) q*=2,a/=2;
		int c=2*q,d=(a+2)*q;
		cout<<1<<" "<<c<<" "<<d<<endl;
	}
	return 0;
}
```
~~有人知道这三句斜体的话出自哪首歌吗？~~

# The End.

---

## 作者：anke2017 (赞：0)

## Something interesting

赛时半小时 A 了。

## 正文

### 题意简述

给定 $a\le 10^9$，求 $1\le b,c,d \le 1\space634\space826\space193$，使得 $a+b+c+d = \gcd{(a,b)} + \dfrac{c \cdot d}{\gcd{(c,d)}}$。（此处的展开有用）  
多测，$t \le 2\times 10^6$。

### 7 分做法（由 Frielen 提出并实现）

总司令，对于每次输出，输出 $b=5a,c=4a,d=3a$。

原理：事实上，这个解一定可以成立，只是在 $a$ 较大时不满足 $1\le b,c,d \le 1\space634\space826\space193$。

### 29 分做法

因为 $a$ 对任意的数的整除性未知，而对 $a$ 进行质因数分解（应该）会 `TLE`，所以不能使得 $\gcd{(a,b)}$ 为一定值（除了为 $1$）。  
所以要有易于构造的通解，似乎 $\gcd{(a,b)} = 1$ 是唯一的选择。此时令 $b=1$ 即可消去 $b$，从而减少一个未知数。

在这次操作过后，我们得到以下一个式子：
$$
gcd{(a,b)}\cdot a=cd-\gcd{(c,d)\cdot(c+d)}
$$
令 $\gcd{(c,d)}=1$，得到
$$
\begin{aligned}
a&=cd-c-d\\
a&=(c-1)(d-1)-1\\
a+1&=(c-1)(d-1)
\end{aligned}
$$
而 $2\mid(a+1)$，所以令 $c=2$，$d=a+2$ 可以保证 $\gcd{(c,d)=1}$。

### 100 分做法
考虑 $2\mid a$ 而 $4\nmid a$ 的情况。  
由于 $\gcd{(c,d)}=1$ 时已经无法保证存在满足要求的 $c,d$，令 $\gcd{(c,d)}=2$，解得以下式子：
$$
\begin{aligned}
2a&=cd-2c-2d\\
2a&=(c-2)(d-2)-4\\
2a+4&=(c-2)(d-2)\\
\frac{a}{2}+1&=(\frac{c}{2}-1)(\frac{d}{2}-1)
\end{aligned}
$$
（这里的 $c$，$d$ 都被 $2$ 整除，否则 $\gcd{(c,d)}$ 不为 $2$）  
可以看到，化简后像是把原来的式子全部除以 $2$！
***
对这一做法进一步推广，设 $2^i\mid a$，$2^{i+1} \nmid a$，则有
$$
\dfrac{a}{2^i}+1=(\dfrac{c}{2^i}-1)(\dfrac{d}{2^i}-1)
$$
此时，$\gcd{(c,d)}=2^i$ 是可以做到的，只需要 $c=2^{i+1}$（即第一个括号结果为 $1$），$d=a+2^{i+1}$（即第二个括号结果为 $\dfrac{a}{2^i}+1$）。

由于 $2^{i+1}\nmid a$，所以有 $2^{i+1}\nmid (a+2^{i+1})=d$。但有 $2^i \mid (a+2^{i+1})=d$，且$2^i \mid 2^{i+1}$，所以有 $\gcd{(c,d)}=2^i$。

而 $2^i\mid a$，$2^{i+1}\nmid a$，所以 $2^i=\operatorname{lowbit}{(a)}$。

证明：

由于 $b=1$ ，所以有 $\gcd{(a,b)}=1$，而且因为 $c=2\times\operatorname{lowbit}(a)$，$d=a+2\times\operatorname{lowbit}(a)$，所以 $\gcd{(c,d)}=\operatorname{lowbit}(a)$，$\operatorname{lcm{(c,d)}}=(2\times (a+2\times\operatorname{lowbit}(a)))$，符合条件。

并且因为 $a\le 10^9$，所以有 $\operatorname{lowbit}(a)\le 536\space890\space912=2^{29}$，且此时 $a=2^{29}$（如图），$d= 536\space890\space912\times3=1\space610\space612\space736<1\space634\space826\space193$。

![不会炸吧QWQ](https://cdn.luogu.com.cn/upload/image_hosting/d7w2q6vg.png)

否则，只有 $\operatorname{lowbit}(a) \le 2^{28}$。

此时 $c = 2\times\operatorname{lowbit}(a)\le 536\space890\space912<1\space634\space826\space193$，$d=a+d \le 10^9 +536\space890\space912 = 1\space536\space890\space912 <1\space634\space826\space193$。命题得证。

***
那么，如何找到 $\operatorname{lowbit}(a)$ 呢？  
直接使用 `a&(-a)` 即可。
### 代码：

```cpp
#include<cstdio>

using namespace std;

inline int find_2(int x)//返回 lowbit(x)
{
    return x&(-x);
}

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1,x,p;i<=t;i++)
    {
        scanf("%d",&x);
        p=find_2(x);
        printf("1 %d %d\n",p*2,x+p*2);
    }
    return 0;
}
```

---

## 作者：xujunlang2011 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11036)

## 思路

可以发现 $a$ 与 $1$ 的最大公约数始终等于  $1$。

此时左式等于 $a+1$，右式等于 $1$。

所以我们需要构造 $\operatorname{lcm}(c,d)=c+d+a$ 的情况。

不妨将上面的式子简化一下，变为 $c\times d=c+d+a$。

容易得出一组较小的 $c$ 与 $d$：$c=2$，$d=a+2$。很显然，$b,c,d\le 1634826193$。

这样 $a$ 为奇数时，$c$ 和 $d$ 互质，$\operatorname{lcm}(c,d)=c\times d$，原式成立。

现在的问题是 $a$ 为偶数时 $\operatorname{lcm}(2,a+2)=a+2$，原式不成立。

但是呢，我们可以发现一个奇怪的性质：在原式成立的情况下 $2a+2b+2c+2d=\gcd(2a,2b)+\operatorname{lcm}(2c,2d)$。

于是我们就可以将 $a$ 变成 $2^k\times x$，其中 $x$ 为奇数。

最终答案就是 $b=2^k$，$c=2\times2^k=2^{k+1}$，$d=(x+2)\times2^k$。

很显然，在 $b,c,d$ 中 $d$ 最大，所以我们只要证明 $d\le 1634826193$ 就行了

$2^{29}=536870912$，所以 $k\le29$，这时我们进行分类讨论。

- $k<29$ 时 $d=a+2^{k+1}\le1536870912\le1634826193$。

- $k=29$ 时 $a=536870912$，此时 $d=1610612736\le1634826193$。

所以 $b,c,d\le 1634826193$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t, n;
    cin >> t;
    for (int i = 1;i <= t;i++)
    {
        cin >> n;
        int cnt = 1;
        while (n % 2 == 0)
        {
            n /= 2;
            cnt *= 2;
        }
        cout << cnt << " " << 2 * cnt << " " << (n + 2) * cnt << "\n";
    }
    return 0;
}
```

这份代码跑得有点慢，有需要的可以关闭同步流。

~~谁家题目从橙跳到蓝啊。~~

---

## 作者：strcmp (赞：0)

看到题束手无策所以直接启动打表。

```
1 1 2 3
2 1 4 6
3 1 2 5
4 1 8 12
5 1 2 7
6 1 4 10
7 1 2 9
8 1 16 24
9 1 2 11
10 1 4 14
11 1 2 13
12 1 8 20
13 1 2 15
14 1 4 18
15 1 2 17
16 1 32 48
17 1 2 19
18 1 4 22
19 1 2 21
20 1 8 28
21 1 2 23
22 1 4 26
23 1 2 25
24 1 16 40
25 1 2 27
26 1 4 30
27 1 2 29
28 1 8 36
29 1 2 31
30 1 4 34
31 1 2 33
32 1 64 96
33 1 2 35
34 1 4 38
35 1 2 37
36 1 8 44
37 1 2 39
38 1 4 42
39 1 2 41
40 1 16 56
```

$a$ 我们钦定好了，然后我们发现 $b$ 都是 $1$，$c$ 是 $2^\text{lowbit(a) + 1}$，$d$ 是 $a + c$。

好，代码：

```cpp
#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef long long int ll;
using pli = pair<ll, int>;
constexpr int maxn = 1e6 + 10, inf = 1e9, mod = 998244353;
int T; ll a, b, c, d;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &a);
		b = 1, c = (a & -a) << 1, d = a + c;
		printf("%lld %lld %lld\n", b, c, d);
	}
    return 0;
}
```

当然直接给代码不给证明显然是坏文明。

我们要证明 $2(a + c) = \text{lcm}(c, a + c)$，也就是证明 $\dfrac{c(a + c)}{2(a + c)\gcd(c, a + c)} = 1$。也就是 $c = 2\gcd(c, a + c) = 2\gcd(a, c)$。

也就是证明 $2^\text{lowbit(a)} = \gcd(a, 2^\text{lowbit(a) + 1})$。

对 $a$ 施辗转相除，$a \mod 2^\text{lowbit(a) + 1} = 2^\text{lowbit(a)}$，$\gcd(2^\text{lowbit(a)},\,2^\text{lowbit(a) + 1}) = 2^\text{lowbit(a)}$。

证毕。

感觉这题不打表找规律，硬构造是困难的。

更新，不超过范围的证明：

如果没有这个范围，那直接 $a,\,a,\,2a,\,3a$ 就做完了。

那我们考虑一下这个东西为什么不超范围。

显然最大的是 $d = a + c$。我们是 OIer 所以可以直接写程序暴力算最大而不证明，使用程序打表可以知道 $a \le 10^9$ 时 $d$ 最大是 $1610612736$。

```cpp
#include<bits/stdc++.h>
#define X first
#define Y second
#define pb push_back
using namespace std;
typedef long long int ll;
using pii = pair<int, int>;
using iter = multiset<ll>::iterator;
int main() {
	int w = 0;
	for (int i = 1; i <= 1000000000; i++) w = max(w, i + ((i & -i) << 1));
	cout << w << "\n";
    return 0;
}
```

显然小于我们的限制，所以是能通过的。

---

