# Flying Saucer Segments

## 题目描述

An expedition group flew from planet ACM-1 to Earth in order to study the bipedal species (its representatives don't even have antennas on their heads!).

The flying saucer, on which the brave pioneers set off, consists of three sections. These sections are connected by a chain: the 1-st section is adjacent only to the 2-nd one, the 2-nd one — to the 1-st and the 3-rd ones, the 3-rd one — only to the 2-nd one. The transitions are possible only between the adjacent sections.

The spacecraft team consists of $ n $ aliens. Each of them is given a rank — an integer from $ 1 $ to $ n $ . The ranks of all astronauts are distinct. The rules established on the Saucer, state that an alien may move from section $ a $ to section $ b $ only if it is senior in rank to all aliens who are in the segments $ a $ and $ b $ (besides, the segments $ a $ and $ b $ are of course required to be adjacent). Any alien requires exactly $ 1 $ minute to make a move. Besides, safety regulations require that no more than one alien moved at the same minute along the ship.

Alien $ A $ is senior in rank to alien $ B $ , if the number indicating rank $ A $ , is more than the corresponding number for $ B $ .

At the moment the whole saucer team is in the 3-rd segment. They all need to move to the 1-st segment. One member of the crew, the alien with the identification number CFR-140, decided to calculate the minimum time (in minutes) they will need to perform this task.

Help CFR-140, figure out the minimum time (in minutes) that all the astronauts will need to move from the 3-rd segment to the 1-st one. Since this number can be rather large, count it modulo $ m $ .

## 说明/提示

In the first sample the only crew member moves from segment 3 to segment 2, and then from segment 2 to segment 1 without any problems. Thus, the whole moving will take two minutes.

To briefly describe the movements in the second sample we will use value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/45444f2fa560c0037b27d01242b8d4bbde1358aa.png), which would correspond to an alien with rank $ i $ moving from the segment in which it is at the moment, to the segment number $ j $ . Using these values, we will describe the movements between the segments in the second sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/555702f9a61a62f33a391773ccade066ae7cb236.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/32a8caec69f00b67073f877bf4e1c3dbf2cc908d.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/ba5c75ab2dad5cb62463c51a0022dba3fcb2b02b.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/6d7099024bb756bbfa4f326bc16f9c9c0f8e6d88.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/28853c5afd49ce7652e3712ce09c29ce2a408087.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/8ccc0778d889ecf8c0b6f2f485e5f6e8eb3901e2.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/555702f9a61a62f33a391773ccade066ae7cb236.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/796a4c4f56cd809d8add74f888f9f99a061291e4.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF226A/dd83b13087f5e34700ad655de6536675af8a276a.png); In total: the aliens need 26 moves. The remainder after dividing $ 26 $ by $ 8 $ equals $ 2 $ , so the answer to this test is $ 2 $ .

## 样例 #1

### 输入

```
1 10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 8
```

### 输出

```
2
```

# 题解

## 作者：ooliver (赞：4)

~~本蒟蒻的第一篇题解，请大家多多支持~~

### 思路
看到题的第一眼，想必大家都想到了 [汉诺塔问题](https://www.luogu.com.cn/problem/P1760)，可是当再次仔细查看此题，每一次只能移动到相邻的“柱子”，所以需要重新推导一遍通项。    
先设人数为 $x$ 时，答案为 $f(x)$。   
众所周知，汉诺塔的通项为 $f(x)=2^x-1$，那么此题的通项肯定与它相关。  
怎么求呢？有两种方法。

#### $f1$: 递推大法
由题很容易可以得到 $f(x)=3 \times f(x-1)+2$（因为在汉诺塔问题中，可以得到 $f(x)=2 \times f(x-1)+1$，而此题中只能移动到相邻的飞船，也就是说系数和常数都应加一）  
那么接下来就是化简。  
由上文知：  
$$
\textstyle{f(x)+1=3 \times (f(x-1)+1)}
$$   
那么：
$$
\textstyle{\frac{f(x)+1}{f(x-1)+1}=3}
$$   

又因为：
$$
\textstyle{f(1)=2}
$$  
所以：
$$
\textstyle{f(1)+1=3,f(2)+1=9,\dots,f(x)+1=3^x}
$$  
则可以得到：
$$
\textstyle{f(x)=3^x-1}
$$
#### $f2$: 找规律大法
回到汉诺塔问题，通项为 $f(x)=2^x-1$。  
那么我们能否枚举本题中 $f(1),f(2),f(3),f(4)$ 的值并找到与 $f(x)=2^x-1$ 格式相近的通项呢？  
当然是可以的。  
通过硬算大法和不断尝试，可以得到： 
$$
\textstyle{f(1)=2}
$$
$$
\textstyle{f(2)=8}
$$
$$
\textstyle{f(3)=26}
$$
$$
\textstyle{f(4)=80}
$$
所以，我们可以“轻松”得到：
$$
\textstyle{f(x)=3^x-1}
$$
那么通过以上两种方法就可以得到我们所需要的通项了！！！

### 代码
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//命名空间
#define int long long//不开long long见祖宗
int n,m;
int mi(int x,int y){//快速幂
	int ans=1;
	while(y){
		if(y%2) ans*=x,ans%=m;
		y/=2,x=x*x%m;
	}
	return ans;
}
int32_t main(){	
	cin>>n>>m;
	cout<<(mi(3,n)-1+m)%m;//记得负数判断一下
}
```

---

## 作者：如履薄冰 (赞：3)

### 思路
这是一道**数学**题。乍一看没啥思路，所以我便抱着“数学先打表”的思路枚举找规律。我列举出来了 $1$ 至 $5$ 人的答案，把他们列成了一个数列。在这个数列里，我还是看不出来啥规律。我看了看这些数彼此相差多少，终于发现了一点点规律：它们彼此相差的数都是 $3^x \times 2$ 这种格式的。其中 $x$ 是较小的那个数对应的问题的人数。我列出了通项公式：$F_n = F_{n-1} + 3^{n-1} \times 2$。其中 $F_x$ 表示有 $x$ 人的答案。特别地，$F_1 = 2$。这样可以用线性的复杂度算出答案，但这面对 $10^9$ 的数据还是过不了。我又观察了一下五个答案的特征。发现 $F_x=3^x - 1$ 。这不就简单了吗？我们直接套用这个公式再去取模 $m$ 就行了。
### 细节
1. 这道题数据较大，我们要使用快速幂。
2. 我们有可能遇到负数的情况，所以要给答案加上一个 $m$。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int qpow(int a,int b,int p){
	if (b==0){
		return 1;
	}
	a%=p;
	int ret=qpow(a,b/2,p);
	if(b%2){
		return ret*ret%p*a%p;
	}else{
		return ret*ret%p;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	cout<<(qpow(3,n,m)-1+m)%m;
	return 0;
}
```

---

## 作者：Autumn_Dream (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF226A)

**思路：**

这题比较像汉诺塔。设 $f_i$ 为共有 $i$ 个人的答案，不难看出 $f_i=3\times f_{i-1}+2$，且 $f_0=0$。

接下来就是找规律：

$$f_1=3\times 0+2=2$$

$$f_2=3\times 2+2=8$$

$$f_3=3\times 8+2=26$$

$$f_4=3\times 26+2=80$$

$$f_5=3\times 80+2=242$$

用 $3$ 进制表示，即：

$$f_1=2=2_{(3)}$$

$$f_2=8=22_{(3)}$$

$$f_3=26=222_{(3)}$$

$$f_4=80=2222_{(3)}$$

$$f_5=242=22222_{(3)}$$

结论：$f_i={(\underbrace{2...2}_{(i\text{个}2)}})_{(3)}=3^i-1$。

用快速幂即可通过此题，记得开 `long long`。

---

## 作者：__UrFnr__ (赞：1)

**题目思路**：

这道题看起来像汉诺塔，可是有区别。

我们可以尝试递推一下，设 $i$ 个人的答案是 $f_i$，很容易得到递推式：

$$f_i=3\times f_{i-1}-2$$

也就是就是这样：

$$f_i+1=3\times(f_{i-1}+1)$$

可以得出 $f_1+1=3$。

所以第 $i$ 项 $f_i+1=3^i$。

根据我们递推出来的式子，加上一个快速幂，就差不多了。

代码如下：


```cpp
#include <bits/stdc++.h>
#define int long long//开long long 保险
using namespace std;
int n, m;
int qp (int a, int b) {//快速幂函数
	int ans = 1;
	while (b) {
		if (b & 1) 
			ans *= a, ans %= m;
		a *= a, a %= m;
		b >>= 1;
	}
	return ans % m;
}
signed main () {
	cin >> n >> m;
	cout << (qp (3, n) - 1 + m) % m;//根据递推式求出答案
	return 0;
} 
```

---

## 作者：Noby_Glds (赞：1)

挺有意思啊。
### 思路：
这个题看着像汉诺塔，但实质上有区别。

我们考虑先递推一下：假设我们要把最大编号为 $i$ 的人移过去。

那么……先把其他人移到 $2$ 机，再把其他人移到 $1$ 机，然后把 $i$ 移到 $2$ 机。

把其他人再移到 $2$ 机，移到 $3$ 机，再把 $i$ 移到 $1$ 机。

再把其他人移到 $2$ 机，$1$ 机，就完事了。

我们设 $dp_i$ 为共有 $i$ 个人时的答案，那么很容易得到：

$$dp_i=3dp_{i-1}+2$$

但如果你拿这个式子直接递推，肯定会 T。

进行整合后，可以得到通项公式：

$$dp_i=3^i-1$$

套个快速幂，这题就完成了！（记得开 long long）
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int Pow(int x,int y){
	int ans=1;
	while(y){
		if(y%2) ans=ans*x%m;
		y/=2,x=x*x%m;
	}
	return ans;
}
signed main(){
	cin>>n>>m;
	cout<<((Pow(3,n)-1)%m+m)%m;//注意处理负数，否则会在第47个点WA掉
	return 0;
}
```


---

## 作者：小杨小小杨 (赞：1)

## 题意
简洁明了
## 思路
设 $dp_i$ 是当前第 $i$ 个人的移动数量，有转移方程： $dp_i = dp_{i-1} \times 3 + 2$。
把 $dp_i$ 看做是 $3$ 进制，那么 $dp_i$ 就是在 $3$ 进制中在 $dp_{i-1}$ 的基础上在末尾加上了一个 $2$，所以有：

$dp_i = 3^0 \times 2 + 3^1 \times 2 + ... + 3^{i-1} \times 2$   
$\ \ \ \ \ \ \ =2 \times (3^0 + 3^1 + 3^2+ ... + 3^{i-1})$   
$\ \ \ \ \ \ \ =(3-1) \times (3^0 + 3^1 + 3^2+ ... + 3^{i-1})$     
$\ \ \ \ \ \ \ =3 \times (3^0 + 3^1 + 3^2+ ... + 3^{i-1}) - (3^0 + 3^1 + 3^2+ ... + 3^{i-1})$   
$\ \ \ \ \ \ \ =3^1 + 3^2+ ... + 3^i - 3^0 - 3^1 - 3^2- ... -3^{i-1}$    
$\ \ \ \ \ \ \ =3^i - 3^0$     
$\ \ \ \ \ \ \ =3^i - 1$

也就是第 $n$ 个人有 $3^n - 1$ 种情况。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,mod;
int f_pow(long long x,long long y,long long mod){
	long long tmp=1;
	while (y>0){
		if (y&1) tmp=tmp*x%mod;
		y>>=1;x=x*x%mod;
	}
	return tmp;
}
int main(){
	scanf("%d%d",&n,&mod);
	printf("%d",(f_pow(3,n,mod)-1+mod)%mod);
    return 0;
}

```


---

## 作者：Rosmarinus (赞：1)

[更好的阅读体验](https://www.cnblogs.com/XJ21/p/14673606.html)

## 思路分析

这题一看到感觉它就是汉诺塔啊！但是它和汉诺塔的不同之处在于：它每次只能相邻移动。一时间想不出思路怎么办！先看样例解释。

我们可以发现以下两点性质：

- 在船员 $t$ 要从飞船 $3$ 转移到飞船 $1$ 时：

    - 飞船 $1$ 中只有且全是编导从 $t + 1$ 到 $n$ 的船员；
    - 飞船 $2$ 为空；
    - 飞船 $3$ 中只有且全是编号从 $1$ 到 $t$ 的船员。

- 将船员 $t$ 从飞船 $3$ 转移到飞船 $1$ 时，依次进行如下操作：

    1. 将船员 $t$ 从飞船 $3$ 转移到飞船 $2$；
    2. 将船员 $t+1$ 到 $n$ 从飞船 $1$ 转移到飞船 $3$；
    3. 将船员 $t$ 从飞船 $2$ 转移到飞船 $1$；
    4. 将船员 $t+1$ 到 $n$ 从飞船 $3$ 转移到飞船 $1$。

再加上我们自己看题目可以得出的以下性质：

- 将任意船员全部从飞船 $1$ 转移到飞船 $3$ 所花费的时间与将其全部从飞船 $3$ 转移到飞船 $1$ 所花费的时间是想等的；
- 转移船员所需的世界只与船员数量有关，与编号无关。

我们便可以想到以下方法：

设 $dp_i$ 表示将 $n-i+1$ 号船员从飞船 $1$ 转移到飞船 $3$ 所需的时间，$sum_i$ 表示将 $i$ 个船员全部从飞船 $3$ 转移到飞船 $1$ 所需要的时间。

结合对样例解释的分析，我们很容易便可以写出：

$$dp_i=sum_{i-1}\times 2+2$$
$$sum_i=sum_{i-1}+dp_i$$

由于题目所求的答案即为 $sum_n$，我们可以将以上两个式子化简一下：

$$sum_i=sum_{i-1}\times 3+3$$

因此，我们只要通过以上式子求出答案即可。

## 方法解析

显然，$sum_1=2$。
考虑到 $n\le 10^9$ 的数据范围与如此表达的解析式，我们可以很快想到矩阵快速幂。

直接上代码。

## AC 代码

此代码来自于 [@ zc_Ethan 大佬](https://www.luogu.com.cn/user/292315)，在此特别感谢其帮助（因为本蒟蒻不会写矩阵快速幂……）。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define inf 1 << 30
#define INF 1ll << 60

using namespace std;
const int siz = 2;
ll MOD;

struct Node
{
    ll a[siz][siz];
};

Node mul(Node m1, Node m2)
{
	Node t;
	memset(t.a, 0, sizeof(t.a));
	for(int i=0; i < siz; i ++)
    {
		for(int k = 0; k < siz; k ++)
        {
			if(!m1.a[i][k]) continue;
			for(int j = 0; j < siz; j ++)
            {
                t.a[i][j] = (t.a[i][j] + m1.a[i][k] * m2.a[k][j] % MOD) % MOD;
            }
		}
	}return t;
}

Node Work(Node m, ll p)
{
	Node t;
	memset(t.a, 0, sizeof(t.a));
	for(int i = 0; i < siz; i ++) t.a[i][i] = 1;
	while(p)
    {
		if(p & 1) t = mul(t, m);
		m = mul(m, m); p >>= 1;
	}
    return t;
}

int main()
{
	ll n;
	scanf("%lld %lld", &n, &MOD);

	if(n == 1)
    {
		printf("%lld\n", 2ll % MOD);
		return 0;
	}

	Node sum, op;

	sum.a[0][0] = 2;
	sum.a[1][0] = 1;
	op.a[0][0] = 3; op.a[0][1] = 2;
	op.a[1][0] = 0; op.a[1][1] = 1;
	op = Work(op, n - 1);
	sum = mul(op, sum);

	printf("%lld\n", sum.a[0][0] % MOD);
}
```

------------

Written by $\operatorname{Rosmarinus}$.

希望能对您有所帮助。

---

## 作者：wandereman (赞：0)

## 思路
这题是要让我们转移船员，从而让我们想到了汉诺塔，但是题面中却只能移动到相邻的船舱，所以我们只需要把通项公式推一遍即可而不需要模拟。

汉诺塔问题中的通项公式是 $f(n) = 2 ^ n - 1$。所以我们尽量搞出一个和这跟很类似的通项公式。

我们通过枚举大法硬算可以得出以下内容： 

$f(1) = 2$。

$f(2) = 8$。

$f(3) = 26$。

所以我们很轻松的看出规律是 $f(n) = 3 ^ n - 1$。    
最后提醒一下由于数据大，所以要加快速幂，还要判断负数。
## AC code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll fastpow(ll x,ll y){
	ll res=1;
	while(y){
		if(y%2){
			res = res * x % m;
		}
		y/=2;
		x = x * x % m;
	}
	return res;
}
int main(){
	cin>>n>>m;
	cout<<((fastpow(3,n) - 1) % m + m) % m<<endl;
	return 0;
}
```
## 注意
- 要用快速幂，否则会超时。
- 最后要判断正负。

---

## 作者：huangrenheluogu (赞：0)

这个问题类似于 Hanoi 问题，类似的，设 $f_i$ 表示 $i$ 个船员从 $3\to 1$ 的最小代价。显然 $1$ 号是最难移动的，于是我们可以按照下列顺序拆解这个移动 $i$ 个船员的问题。

- 把 $2\sim i$ 号船员从 $3$ 移动到 $1$，花费 $f_{i-1}$。
- 把 $1$ 号船员从 $3$ 移动到 $2$，花费 $1$。
- 把 $2\sim i$ 号船员从 $1$ 移动到 $3$，花费 $f_{i-1}$。
- 把 $1$ 号船员从 $2$ 移动到 $1$，花费 $1$。
- 把 $2\sim i$ 号船员从 $3$ 移动到 $1$，花费 $f_{i-1}$。

于是有递推式 $f_i=3f_{i-1}+2$，边界 $f_0=0$。或者可以算出 $f_1=2$。

这个递推式是比较简单的，套路化地，写出两个方程，相减可以得到 $f_i-f_{i-1}=3(f_{i-1}-f_{i-2})$，于是 $f_i-f_{i-1}=2\times 3^{i-1}$，于是 $f_i=\sum\limits_{j=0}^{i-1}2\cdot3^{j}$，于是 $f_i=3^i-1$。

于是直接输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, ans, x = 3;
int main(){
	scanf("%d%d", &n, &m);
	ans = 1;
	while(n){
		if(n & 1) ans = 1ll * ans * x % m;
		x = 1ll * x * x % m, n >>= 1;
	}
	ans += m - 1;
	if(ans >= m) ans -= m;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：z_yq (赞：0)

## 题意
$3$ 号太空舱有 $n$ 个人，这 $n$ 个人要去 $1$ 号舱，且满足以下要求：

- 若编号为 $i$ 的船员想从飞船 $a$ 转移到飞船 $b$（$a,b$ 相邻），必须有太空舱 $a,b$ 中没有船员的编号比 $i$ 大。
- 每一个船员每次只能转移到相邻的飞船，每次转移消耗 $1$ 单位的时间。
- 同一时间只能有一名船员进行转移。

询问最短的时间，答案要对 $m$ 取模。

## 分析
因为 $i$ 号船员想从飞船 $a$ 转移到飞船 $b$ 要保证太空舱 $a,b$ 中没有船员的编号比 $i$ 大，所以可得：每次把最大的向任何一个位置移动时，别的都需要从来回移动，令：$dp_i$ 表示有 $n$ 个人在 $3$ 号舱时，需要的最小时间，可得：$dp_i = 3 \times dp_{i-1} + 2$ 又因为时间复杂度，所以需要优化，可得：$dp_i = 3^i-1$ 快速幂可解决。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll n,Mod;
int main()
{
	cin>>n>>Mod;
	ll ans=1,sum=3;
	for(;n;n>>=1)
	{
		if(n&1)
			ans*=sum;
		sum*=sum;
		sum%=Mod;
		ans%=Mod;
	}
	cout<<(ans+Mod-1)%Mod; 
	return 0;
}
```

---

## 作者：_int123_ (赞：0)

题目：

## Flying Saucer Segments

### 题意：

很像汉诺塔，但有点区别，这里多了一个条件，就是只能移动到相邻的位置上去。

题目要求将 $n$ 个船员全部转移到飞船 $1$ 所需要的最小时间。

### 思路：

先手动模拟一下，假设我们要将下标最大的一个人 $i$ 从 $3$ 号飞船移到 $1$ 号飞船上，我们可以先将除他以外的所有人经过一系列操作后移到 $1$ 号飞船上，将其移到 $2$ 号飞船上，在将其他人移到 $3$ 号飞船上，就可以将他移到 $1$ 号飞船上了。

我们设 $dp_i$ 为共有 $i$ 个人时的答案，易得：

$$dp_i=3 \times dp_{i-1}-2$$

即：

$$ \left(dp_{i}+1 \right)=3 \times \left(dp_{i-1}+1 \right)$$

可以发现，$ \left( dp_i+1 \right)$ 成等比数列，又：

$$ \left( dp_1+1 \right)=3$$

所以可得：

$$ \left( dp_{i}+1 \right)=3^i$$

即：

$$dp_i=3^i-1$$

我们便有了通项公式，再加个快速幂，本题就差不多了。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
#define int long long//不开 long long 见祖宗 
using namespace std;
int n,m;
inline int f(int a,int b)//快速幂 
{
    int s=1;
    while(b>0)
	{
        if(b&1)s=s*a%m;
    	b>>=1;
        a=(a*a)%m;
    }
	return s%m;
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>n>>m;//输入 
	cout<<(f(3,n)-1+m)%m;//有可能为负数，记得处理一下 
	return 0;
}
```

完结撒花！！！

---

## 作者：minVan (赞：0)

**解题思路**

令 $f_i$ 为 $i$ 名船员转移的最短时间。

转移方程为 $f_i=3f_{i-1}+2$。

用三进制表示为 $f_i=(\begin{matrix}\underbrace{22\cdots 2}\\\tiny i \text{个} 2\end{matrix})_3=2\times(\sum\limits_{j=0}^{i-1}3^j)=2\times\dfrac{3^i-1}{3-1}=3^i-1$。

这里需要快速幂，开 long long，减 $1$ 时记得要加一个模数。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
inline int qpow(int a, int n) {
  if(!n) {
    return 1 % m;
  }
  int tmp = qpow(a, n >> 1);
  if(n & 1) {
    return tmp * tmp % m * a % m;
  } else {
    return tmp * tmp % m;
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  cout << (qpow(3, n) - 1 + m) % m;
  return 0;
}
```

---

