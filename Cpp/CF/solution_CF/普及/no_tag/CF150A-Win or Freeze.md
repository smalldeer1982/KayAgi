# Win or Freeze

## 题目描述

You can't possibly imagine how cold our friends are this winter in Nvodsk! Two of them play the following game to warm up: initially a piece of paper has an integer $ q $ . During a move a player should write any integer number that is a non-trivial divisor of the last written number. Then he should run this number of circles around the hotel. Let us remind you that a number's divisor is called non-trivial if it is different from one and from the divided number itself.

The first person who can't make a move wins as he continues to lie in his warm bed under three blankets while the other one keeps running. Determine which player wins considering that both players play optimally. If the first player wins, print any winning first move.

## 说明/提示

Number $ 6 $ has only two non-trivial divisors: $ 2 $ and $ 3 $ . It is impossible to make a move after the numbers $ 2 $ and $ 3 $ are written, so both of them are winning, thus, number $ 6 $ is the losing number. A player can make a move and write number $ 6 $ after number $ 30 $ ; $ 6 $ , as we know, is a losing number. Thus, this move will bring us the victory.

## 样例 #1

### 输入

```
6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
30
```

### 输出

```
1
6
```

## 样例 #3

### 输入

```
1
```

### 输出

```
1
0
```

# 题解

## 作者：精神小伙！ (赞：3)

列举一下可能出现的几种情况：

1. $ q $ 是一个质数或者 $ q = 1 $ ，开始就无法操作，玩家一必胜，直接在第一行输出 1 ，第二行输出 2 。
1. 如果 $ q $ 不是质数，我们就可以开始找规律。

   - 如果 $ q $ 是 12 ，此时 12   的因子有 1 ， 2 ， 3 ， 4 ， 6 ， 12 ， 这时玩家一选择 3 ，玩家二只能选择 2 ，所以玩家一获胜。
   - 如果 $ q $ 是 6 ，此时 6 的因子有 1 ， 2 ， 3 ， 6 ，这时玩家一不管选择 2 还是 3 ，玩家二都无法操作，所以玩家二获胜。
   - 如果 $ q $ 是 30 ，此时 30 的因子有 1 ， 2 ， 3 ， 5 ， 6 ，   10 ， 15 ， 30 ，这时玩家一可以选择 2 或 3 或 5 ，玩家二不管怎么操作，玩家一都不能操作玩家二操作过的数，所以玩家一获胜。
   
   这时可以发现：如果一个数的因子如果能超过两个，那么玩家一获胜，否则玩家二获胜。
   
代码：


------------


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
typedef long long ll;
ll z,n;
bool ss(ll x)
{
	if(x==1) return true;
	for(ll i=2;i<=sqrt(x);++i)
	    if(x%i==0) return false;
	return true;
}
ll pd1(ll x)
{
	for(ll i=2;i*i<=x;++i)
	    if(x%i==0) return i;
	return -1;
}
ll pd2(ll x)
{
	ll z=pd1(x);
	x/=z;
	int y=pd1(x);
	if(y==-1) return -1;
	return z*y;
}
int main()
{
	cin>>n;
	if(ss(n))
	{cout<<1<<endl<<0<<endl;return 0;}
	z=pd2(n);
	if(z==-1)
	{cout<<2<<endl;return 0;}
	cout<<1<<endl;
	cout<<z<<endl;
	return 0;
}

```


---

## 作者：DinnerHunt (赞：3)

如果一个数能分解成2个以上的质数，那么则先手胜，否则后手

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
long long x,k,ans = 1;
void check(long long x)
{
    long long y = x;
    for(long long i=2;i*i<=x;i++)
    {
        //cout << i * i << endl;
        while(x%i == 0&&i*i<=x)
        {
            k++;
            ans *= i;
            x/=i; 
            //cout << i <<" ";
            if(k==2&&x!=y){ k++; return;}
        }
    }
    k += x!=y;
}
int main()
{
    // freopen("a.in","r",stdin);
    // freopen("k.out","w",stdout);
    cin >> x;
    check(x);
    //cout << k << " ";
    if(k==2) printf("2");
    else 
    {
        printf("1 ");
        if(ans==1) cout << "0";
        else cout << ans;
    }
    return 0;
}
```


---

## 作者：QWQ_123 (赞：2)

由于是因子，考虑将其化为质因数分解的形式：$a = p_1^{k_1} p_2^{k_2} ... p_n^{h_n}$。

然后每次就是取其中的一些质因子。

那么对于 $a = p$ 显然就是先手必胜，因为去不了。

那么若 $a = p_1p_2$，后手必胜。

若 $a = p_1p_2p_3\dots p_n(n\ge 3)$ 那么先手必胜，因为先手可以取一次变成 $a = p_1p_2$，然后后手怎么取都是必输，所以先手必胜。

若 $a = p_1^{k_1} p_2^{k_2} \dots p_n^{h_n}(n\ge 3)$，则先手必胜，因为去一次就可以取到和上边一样 $a = p_1p_2$。

然后判断就直接质因数分解即可。

---

## 作者：Lyw_and_Segment_Tree (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF150A)  
## 题意简述
> 给定一个整数 $q$，如果 $q$ 不是质数，则称 $q$ 是可操作的。然后我们定义操作为：将被操作数除以一个非 1 或其本身的因子。然后现在有玩家1和玩家2在玩一个游戏：两人轮流对 $q$ 进行操作，直到不能操作这个数字的玩家获胜。

> 当玩家1获胜时输出 1，否则输出 2，当且仅当玩家一获胜时，需换行输出玩家 1 能在第一次操作中选择的数。若玩家 1 一开始就不能操作，则第二行输出 0。

## 开始解题！ 
观察题目，不难发现这一题其实就是博弈论，也就是说在满足某些条件的情况下，双方有必胜策略。   
观察到题目和因数有关，并且和因数的选择有关，考虑唯一分解定理，也就是说 $q = p_1^{k_1} \times p_2^{k_2} \times \dots \times p_i^{k_i}$。然后我们记 $q$ 的质因子个数为 $x$，那么根据题意简单模拟可得当且仅当 $x = 2$ 时玩家 2 必胜。然后对于其它情况，我们进行分类讨论。  
对于 $x$ 的取值，我们分两种情况考虑。  
1. 当 $x$ 为奇数时，我们一次取掉 $x - 2$ 个因数的积这个因数即可获胜。  
2. 当 $x$ 为偶数时，我们仍然可以一次取掉 $x - 2$ 个因数的积这个因数，也可以获胜。  

那么也就是说，当 $x$ 大于 2 时玩家 1 必胜。然后我们任取两个质因子之积输出即可。需要注意的是：如果 $q$ 为质数，则玩家 1 同样获胜。综合上述结论，可得代码如下：
## AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2],t;
void isprime(int n) {
    if (n==1) return;
    for(int i=2;i<=sqrt(n);i++){
        if(n%i==0){
            a[t++]=i;
            n/=i;
            i--;
            if(t==2) return;
        }
    }
}
signed main(){
    int q;
    cin>>q;
    isprime(q);
    if(t==0){
        puts("1\n0");
    }
    else if(t==1) {
        puts("2");
    }
    else{
        puts("1");
        cout<<a[0]*a[1];
    }
    return 0;
}
```  
[AC 记录](https://www.luogu.com.cn/record/141052437)

---

## 作者：hjm777 (赞：1)

### 题解

不妨假设输入的数为 $q = p_1^{k_1} \times p_2^{k_2} \times p_3^{k_3} \times \dots \times p_n^{k_n}$。

我们讨论输入的数：

- 如果输入的数为一个质数，那么玩家做不出任何操作，所以这种情况是必赢的。

- 如果输入的数有两个质因数，且每个质因数都只出现了一次，两个质数分别为 $p_1, \ p_2$，则无论除以 $p_1$ 还是 $p_2$，得到的数都是质数，即第一种情况，所以这种情况是必输的。

- 如果输入的数有一个质因数，且这个质因数出现了两次，这个质数为 $p_1$，则只能除以 $p_1$，得到的数为 $p_1$，是个质数，即第一种情况，所以这种情况是必输的。

- 其他情况，则有 $k_1 + k_2 + k_3 + \dots + k_n > 2$，可以通过除以一个数使得 $k_1 + k_2 + k_3 + \dots + k_n = 2$ 是可行的，即第二种情况或第三种情况，所以这种情况是必赢的的。

有了以上结论，我们可以得到：

- 如果输入的数为质数时，玩家 $1$ 刚开局就会赢，不用做操作。

- 如果输入的数为有两个质因数，且每个质因数都只出现了一次，那么玩家 $2$ 必赢。

- 如果输入的数为有一个质因数，且质因数出现了两次，那么玩家 $2$ 必赢。

- 其他情况，玩家 $1$ 必赢，除以的数只要使得操作后的数的 $k_1 + k_2 + k_3 + \dots + k_n = 2$ 就行了。

**一个更小清新的结论就是：**

- 如果这个数的 $k_1 + k_2 + k_3 + \dots + k_n$ 满足 $k_1 + k_2 + k_3 + \dots + k_n = 1$ 或 $k_1 + k_2 + k_3 + \dots + k_n \ge 3$，玩家 $1$ 必胜，操作方案是好构造的。

- 如果这个数的 $k_1 + k_2 + k_3 + \dots + k_n$ 满足 $k_1 + k_2 + k_3 + \dots + k_n = 2$，玩家 $2$ 必胜。

所以我们只要计算这个数的质因数的次数之和，还有每个质因数是什么就好。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define dbg(x) cout << #x " = " << (x) << endl
#define quickio ios::sync_with_stdio(false);
#define quickin cin.tie(0);
#define quickout cout.tie(0);

using namespace std;

signed main() {
    quickio
    quickin
    quickout
    int n; cin >> n;
    int tot = 0, m = n;
    vector <int> vec;
    if(n == 1) tot = 1;
    for(int i = 2; i * i <= n; i++)
        while(n % i == 0) tot++, n /= i, vec.push_back(i);
    if(n > 1) vec.push_back(n), n = 1, tot++;
    if(tot == 1) cout << 1 << endl << 0 << endl;
    else if(tot == 2) cout << 2 << endl;
    else cout << 1 << endl << vec[0] * vec[1] << endl;
    return 0;
}
```

---

## 作者：fish_love_cat (赞：1)

**思路：**

可以发现，质数和 $1$ 是不可操作的。所以初始时先特判这两个。

接下来我们设有 $x$ 个合法的因子。

当 $x<2$ 时，先手操作完后就不可操作了，输。

当 $x\ge2$ 时，先手直接把 $x=1$，赢。

先手最后留下一个 $x=1$ 的数，所以就把 $q$ 的两个合法因子记录下来输出乘积即可。

然后就做完了。

**代码：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[2],f;
void isprime(int n){//略有改动的判断质数函数
    if(n==1)return;
    for(int j=2;j<=sqrt(n);j++){
        if(n%j==0){
            a[f++]=j;n/=j,j--;
            if(f==2)return;//只需要两个，所以有优化
        }
    }
}
signed main(){int q;cin>>q,isprime(q);
    if(!f)puts("1\n0");
    else if(f==1)puts("2");
    else puts("1"),cout<<a[0]*a[1];
    return 0;
}
```

---

## 作者：Dreamerly (赞：1)

## 题目：[CF150A](https://www.luogu.com.cn/problem/CF150A)
## 思路：
从题意中不难看出这是一道博弈论题，而获胜条件往往是此类题中的重点。

**获胜条件**：

为了推导获胜条件，我们就需要分解质因数。看数据范围，知 $O(\sqrt{q})$。但这里分解时，到底要不要包含重复质因子呢？直接给结论：需要包含重复质因子。

继续推导获胜条件。

若玩家一开局遇到的就是质数或 $1$，则无法操作而胜出。

若玩家一开局遇到的数只有两个质因子，即**先手必败合数**，无论他选择哪个质因子，都会给对方质数而胜出。而且这里有个**坑点**，比如 $9$，看上去只有质因子 $3$，但这里的 $3$ 要看作两个质因子 $3\times 3$，所以是玩家二胜出，也对应了上文的结论。

若玩家一开局遇到的数两个以上的质因子，那他就会将这个数变成只有两个质因子，即**先手必败合数**给对方。因此输出任意两个质因子之积即可。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
}
void write(int x){ 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
int pos;
int prim[1010];
signed main(){
	int n=read();
	if(n==1){
		printf("1\n0\n");
		return 0;
	}
	int tn=n;
	for(int i=2;i*i<=n;i++){
		while(tn%i==0){
			prim[++pos]=i;
			tn/=i;
		}
	}
	if(tn!=1) prim[++pos]=tn; //当前本身为质数
	
	if(pos==1)      printf("1\n0\n");
	else if(pos==2) printf("2");
	else            printf("1\n%lld",prim[1]*prim[2]); 
	return 0;
} 
```


---

## 作者：beigongbaishan (赞：0)

## 前言
这波生草翻译……
## 题意
两人进行游戏，给定一个数 $q$，两人轮流操作，每次操作可以将 $q$ 除以一个不为 $1$ 和本身的因子，直到一名玩家无法进行操作，他就获胜了。
## 思路
我们进行分类讨论：
+ 当可操作因子数为 $0$，也就是此数是 $1$ 或质数，此时先手无法操作，先手胜。
+ 当可操作因子数为 $1$，也就是此数是一个质数的平方，那么先手只能除以它的算术平方根，此时后手无法操作，后手胜。
+ 当可操作因子数为 $2$，也就是此数是两个不同质数的积，那么先手只能除以它的其中一个质因子，此时后手无法操作，后手胜。
+ 当可操作因子数 $>2$，那么先手可以将他的可操作因子变为 $1$ 或 $2$，参考前面两种情况，此时先手胜。
## 最后
明白思路后，代码就很好写了。

最后的最后：
### 十年 OI 一场空，不开 long long 见祖宗！

---

## 作者：QingDeng_Star (赞：0)

## 题目大意
给你一个整数，如果这个整数不是质数，那么就可以把这个数除以它的一个因子（不能是 $1$）。现在 $A$ 和 $B$ 在玩一个游戏：两人轮流对这个数进行操作，直到不能操作这个数的玩家获胜。
## 思路
可以发现，如果这个数是质数或者是 $1$ 是无法操作的。所以可以先特判。

接下来分情况讨论：

如果这个数的因子小于 $2$，那么 $A$ 操作完后就无法再次操作，$A$ 输。

如果这个数的因子大于等于 $2$，那么 $A$ 直接把此数变为 $1$，$A$ 赢。

然后就没有然后了，快去敲代码吧。

---

## 作者：qusia_MC (赞：0)

## 思路
先把 $p$ 分解质因数，根据唯一分解定理，$p$ 一定可以分解成且只能分解成 $q_1^{k_1}\times q_2^{k_2}\times q_3^{k_3}$ 这样的形式。不难想到下面策略：

- 若 $\sum_{i=1}^{+\infty}k_i\ge 2$ 或 $p$ 诗质数则 1 必胜。因为他可以把这个数的因数除到只剩一个，这样 2 只能操作这个，被卡死了，最后 1 获胜。

- 否则，一定是 2 获胜。因为 1 只能操作。

## code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool is_prime(int k)
{
	if(k==1||k==0)return 1;
	for(int i=2;i*i<=k;i++)
	    if(k%i==0)return 0;//判断素数
	return 1;
}
signed main()
{
	int k,ysgs=0,l=1,k2,f=1;
	cin>>k;
	if(is_prime(k)){
		cout<<"1\n0";return 0;
	}
	k2=k;
	int i=2;
	while(k!=1)
	{
		while(k%i==0&&k!=1){
		k/=i;
		ysgs++;//因数个数
		l*=i;f=0;
		}
		if(k==1)break;//除完了
		i++;
	}
	if(ysgs>2)
	{
		cout<<"1\n"<<l/i;//1获胜
	}
	else cout<<"2";
	return 0;
} 
```

---

## 作者：MuelsyseU (赞：0)

考虑无脑 SG 函数。一个数的因数个数是 $O(\sqrt{q})$ 的。这样看起来转移有 $O(q)$ 次。考虑认为 $1$ 是必胜局面值为 $0$，我们可以把因数排序后（利用性质）简单维护前缀或，每个 SG 值即为前缀或的值取反。

显然这个没有必要真的跑一遍，因为只有前面除了 $1$ 以外的值都是 $1$ 才会导致必败。这实际上只有一种情况，就是 $q$ 恰好可分解为两个质数的积。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll x, s, ans = 1;
void check(ll x) {
    ll y = x;
    for (ll i = 2; i * i <= x; i++) {
        while (x % i == 0 && i * i <= x) {
            ++s, x /= i, ans *= i;
            if (s == 2 && x != y) {
                ++s;
                return;
            }
        }
    }
    if (x != y) ++s;
}
int main() {
    cin >> x;
    check(x);
    if (s == 2)
        cout << "2";
    else {
        cout << "1 ";
        if (ans == 1)
            cout << "0";
        else
            cout << ans;
    }
    return 0;
}
```

---

