# [ARC177A] Exchange

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc177/tasks/arc177_a

日本では、$ 1 $ 円、$ 5 $ 円、$ 10 $ 円、$ 50 $ 円、$ 100 $ 円、$ 500 $ 円の $ 6 $ 種類の硬貨が流通しています。これについて、次の問いに答えてください。

> AtCoder さんの財布の中には、$ 1 $ 円硬貨 $ A $ 枚、$ 5 $ 円硬貨 $ B $ 枚、$ 10 $ 円硬貨 $ C $ 枚、$ 50 $ 円硬貨 $ D $ 枚、$ 100 $ 円硬貨 $ E $ 枚、$ 500 $ 円硬貨 $ F $ 枚が入っています。
> 
> AtCoder さんは、これから $ N $ 個の店で順番に買い物を行います。 具体的には、$ i $ 番目 $ (1\ \leq\ i\ \leq\ N) $ に訪れる店では税込 $ X_i $ 円の商品を $ 1 $ つ購入する予定です。
> 
> 釣銭の授受には時間がかかるので、彼は支払いに使う硬貨を上手く選ぶことで、すべての店で**ちょうどの金額**を支払って商品を購入したいです。 このようなことが可能か、判定してください。

## 说明/提示

### 制約

- $ 0\ \leq\ A\ \leq\ 200 $
- $ 0\ \leq\ B\ \leq\ 200 $
- $ 0\ \leq\ C\ \leq\ 200 $
- $ 0\ \leq\ D\ \leq\ 200 $
- $ 0\ \leq\ E\ \leq\ 200 $
- $ 0\ \leq\ F\ \leq\ 200 $
- $ 1\ \leq\ N\ \leq\ 10 $
- $ 1\ \leq\ X_i\ \leq\ 10000\ (1\ \leq\ i\ \leq\ N) $
- 入力はすべて整数
 
### Sample Explanation 1

たとえば以下のように支払いを行うと、$ 3 $ 店舗すべてでちょうどの支払いを行うことができます。 - $ 1 $ 番目に訪れる店：$ 100 $ 円硬貨を $ 2 $ 枚、$ 500 $ 円硬貨を $ 1 $ 枚使う。 - $ 2 $ 番目に訪れる店：$ 10 $ 円硬貨を $ 5 $ 枚、$ 100 $ 円硬貨を $ 2 $ 枚使う。 - $ 3 $ 番目に訪れる店：$ 10 $ 円硬貨を $ 1 $ 枚、$ 50 $ 円硬貨を $ 3 $ 枚使う。

### Sample Explanation 2

財布に入っている金額は $ 500 $ 円ですが、合計 $ 100+200+300=600 $ 円の支払いを行う必要があるため、すべての商品を購入することができません。

### Sample Explanation 3

財布に $ 50 $ 円以下の硬貨が入っていないため、$ 250 $ 円ちょうどを支払うことはできません。

## 样例 #1

### 输入

```
0 0 6 3 4 1
3
700 250 160```

### 输出

```
Yes```

## 样例 #2

### 输入

```
0 0 0 2 4 0
3
100 200 300```

### 输出

```
No```

## 样例 #3

### 输入

```
0 0 0 0 8 8
1
250```

### 输出

```
No```

## 样例 #4

### 输入

```
20 5 9 7 10 6
5
177 177 177 177 177```

### 输出

```
Yes```

## 样例 #5

### 输入

```
17 5 9 7 10 6
5
177 177 177 177 177```

### 输出

```
No```

# 题解

## 作者：OIerWu_829 (赞：2)

[洛谷](https://www.luogu.com.cn/problem/AT_arc177_a) / [Atcoder](https://atcoder.jp/contests/arc177/tasks/arc177_a)

**题目翻译**

在日本的硬币有 $1$ 日元、$5$ 日元、$10$ 日元、$50$ 日元、$100$ 日元和 $500$ 日元六种。对此，请回答以下问题：

AtCoder 的钱包里有 $A$ 枚 $1$ 日元硬币、$B$ 枚 $5$ 日元硬币、$C$ 枚 $10$ 日元硬币、$D$ 枚 $50$ 元硬币、$E$ 枚 $100$ 元硬币和 $F$ 枚 $500$ 元硬币。

Atcoder 将从现在开始在 $N$ 家商店依次购物。具体而言，在第 $i$ 号（$1\le i\le N$）的店铺，计划购买 $1$ 个 $X_i$ 日元的商品。

收钱需要时间，所以他想通过选择好支付的硬币，在所有商店都支付恰当的金额购买商品。请判断是否可能发生这种情况。

------------

简单贪心，肯定是优先使用大面额的，后面的钱可以用小面额凑出来。比如有 $10$ 张 $1$ 元和 $1$ 张 $10$ 元，第一个物品 $10$ 元，可以花 $1$ 张 $10$ 元，第二个物品 $7$ 元，可以花 $7$ 张 $1$ 元。如果先用小面额，那么后面就没法凑出 $7$ 元。

所以每次输入 $x$，把 $x$ 依次按照 $500,100,50,10,5,1$ 的顺序减去（如果还有这个面额的硬币），最后如果 $x\ne0$ 就可以。

```cpp
#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d, e, f, n;
    cin >> a >> b >> c >> d >> e >> f >> n;
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while (x >= 500 && f) x -= 500, f--;
        while (x >= 100 && e) x -= 100, e--;
        while (x >= 50 && d) x -= 50, d--;
        while (x >= 10 && c) x -= 10, c--;
        while (x >= 5 && b) x -= 5, b--;
        while (x >= 1 && a) x--, a--;
        if (x) flag = true;
    }
    cout << (flag ? "No" : "Yes") << endl;
    return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：2)

# AT_arc177_a [ARC177A] Exchange 题解

挺简单一道题，感觉像贪心。

### 解析

可以证明，在有大面值纸币和小面值纸币时，最好选大面值纸币。

如有 $5$ 张 $10$ 元和一张 $50$ 元，要付 $50$ 元，肯定选 $50$ 元纸币（不然下次需要付 $40$ 元怎么办）。

然后考虑贪心，时间复杂度不超过 $\mathcal O(a+b+c+d+e+f)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],n;
int pay;
int pri[]={1,5,10,50,100,500}; 
int main(){
	cin.tie(0)->sync_with_stdio(0);
	for(int i=0;i<6;i++){
		cin>>a[i];
	}
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>pay;
		for(int j=5;j>=0;j--){
			while(a[j]&&pri[j]<=pay){ //大面值还能付得起
				a[j]--,pay-=pri[j];
			}
		}
		if(pay){ //如果无论怎么支付都不能付得起
			cout<<"No"; return 0;
		}
	}
	cout<<"Yes";
return 0;
}
```

---

## 作者：_ayaka_ (赞：1)

### 思路
首先分析题面。

既然我们要付固定金额，那肯定是要尽可能先使用大面额再使用小面额，不然会有先用了小面额导致后面的店铺付款时大面额凑不出来的情况。那么思路就很清晰了。

我们可以使用贪心策略，优先使用大面额，再使用小面额。这样我们就可以尽可能的保留小金额给后面的店铺使用了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[8],num[8]={0,1,5,10,50,100,500},n,k;
signed main(){
	for(int i=1;i<=6;i++) cin>>a[i];
	cin>>n;
	while(n--){
		cin>>k;
		for(int i=6;i>=1;i--){
			if(a[i]&&k>=num[i]){
				if(a[i]*num[i]>=k){
					a[i]-=k/num[i];
					k-=k/num[i]*num[i];
				}else{
					k-=a[i]*num[i];
					a[i]=0;
				}
			}
		}
		if(k!=0){
			cout<<"No";
			return 0;
		} 
	}
	cout<<"Yes";
	return 0;
} 
```

---

## 作者：x1489631649 (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc177_a)
# 背景故事
一个杯子里，先放石头满后能放沙子，还能放水，反之则不能。
# 输入 
1.  6 个整数，代表每种货币的数量 $n(1 \le t \le 200)$。
1.  一个数 $n$ 代表支付的次数 $n(1 \le t \le 10)$。
1. $n$ 个数，代表每次支付的钱数 $n(1 \le t \le 10^4)$。
# 输出
输出 `Yes` 或者 `No`。**注意要加 `endl`！**
# 题意
如果每次支付都可以使用已有钱数支付则输出 `Yes`，否则输出 `No`。
# 分析
请仔细观看**背景故事**，根据贪心思路，选数值大的一定最优，因为数值小的可以以后用来补零钱，数值大的没法拆出来当零钱，所以先枚举数值大的货币，使用枚举一遍过。
 # Code
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,a,b,c,d,e,f;
	cin>>a>>b>>c>>d>>e>>f;//代表每种货币的数量。
	cin>>n; 
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(f>=x/500)//进行判断是否可以合理支付。
		{
			f-=x/500;
			x=x%500;
		}
		else{
			x=x-f*500;
			f=0;
		}
		if(e>=x/100)
		{
			e-=x/100;
			x=x%100;
		}
		else{
			x=x-e*100;
			e=0;
		}
		if(d>=x/50)
		{
			d-=x/50;
			x=x%50;
		}
		else{
			x=x-d*50;
			d=0;
		}
		if(c>=x/10)
		{
			c-=x/10;
			x=x%10;
		}
		else{
			x=x-c*10;
			c=0;
		}
		if(b>=x/5)
		{
			b-=x/5;
			x=x%5;
		}
		else{
			x=x-b*5;
			b=0;
		}
		if(a>=x/1)
		{
			a-=x/1;
			x=x%1;
		}
		else{
			x=x-a;
			a=0;
		}
		if(x!=0)
		{
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
}
```
**码风不好请勿见怪，毕竟以能过为主。**
# 时间复杂度
本代码仅使用二重循环，且 $n(1 \le t \le 10)$，所以极限只会跑 10 次 ，操作次数最高为 $10 \times 8$，所以可以通过。

---

## 作者：JackMerryYoung (赞：1)

# 前言

唐 A，居然代码写挂卡了好久。

# 正文

先说结论：根据同志们朴素的情感可以得出本题直接按面额从大到小贪心即可。

来解释一下贪心的正确性：感性理解一下，因为小面额价值有限又是解决付太多的神器，必然先拿大面额付，如果用大面额付多了才用小面额（有点像拿天平称量质量时先放大砝码）。

还没懂吗？举例来说：一张 $100$ 元能抵 $100$ 张 $1$ 元，当你有一张 $100$ 元能代替 $100$ 张 $1$ 元时，代替一定不劣。

（在价值上二者等价，但在付更小的钱上，不代替就相当于失去了后续支付 $[1, 100]$ 区间内任意价格的能力，而只能拥有后续支付 $100$ 元整的能力；代替不仅不失去这次支付 $100$ 元的能力，还具有后续支付 $[1, 100]$ 区间内任意价格的能力。在你不知道下一次要付多少钱吧的情况下，代替显然更优）

~~这下总算是解释清楚了。~~

# 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;

int N, cost[7] = {0, 1, 5, 10, 50, 100, 500}, amount[7];
int X[10005];

signed main()
{
	cin >> amount[1] >> amount[2] >> amount[3] >> amount[4] >> amount[5] >> amount[6] >> N;
	for(int i = 1; i <= N; ++ i) cin >> X[i];
	bool flag = true;
	for(int i = 1; i <= N; ++ i)
	{
		for(int j = 6; j >= 1; -- j)
		{
			int k = X[i] / cost[j];
			if(k > amount[j]) X[i] -= cost[j] * amount[j], amount[j] = 0;
			else X[i] -= cost[j] * k, amount[j] -= k;
		}
		
		if(X[i] != 0)
		{
			flag = false;
			break;
		}
	}
	
	if(flag) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
```

---

## 作者：a_123_a (赞：0)

### 思路
首先分析题面。


既然我们所支付的钱是已知的金额，那么我们就可以运用贪心策略尽可能先使用大面额再使用小面额，因为小面额的可以凑出大面额，但大面额的不能拆成小面额。

那么思路就很清晰了。

我们只需要优先使用大面额，然后尽可能的保留小金额给后面的店铺使用就可以了。

```c
#include<bits/stdc++.h>
using namespace std;
#define intl long long
#define For(i,a,b) for(intl i=a;i<=b;i++)
#define deo(i,a,b) for(intl i=a;i>=b;i--)
intl num[]={0,1,5,10,50,100,500};
intl a[8],n,k;
int main(){
	For(i,1,6) scanf("%lld", (a+i) );//读入 
	scanf("%lld",&n);
	while(n--){
		scanf("%lld",&k);
		deo(i,6,1){
			if(a[i] && k >= num[i]){
				if(a[i]*num[i]>=k) { //判断是不是比当前的总值大 
					intl t=k/num[i];
					a[i] -= t;//用多少减多少 
					k -= t*num[i];
				}
				else{
					k -= a[i]*num[i];
					a[i]=0;//用完清零 
				}
			}
		}
		if(k){printf("No");return 0;} //如果最后仍有剩余，输出No 
	}
	printf("Yes");
	return 0;
}
```

---

## 作者：nsty_iridescent (赞：0)

### 思路
直接根据题意模拟即可。

我们只需要从头到尾遍历一下所有的商店，再写一个函数来判断一下当前的钱是否可以支付就行了。

那么如何写这个判断函数呢？我们可以遵循以下两点来判断：

* 首先从面值最大的硬币开始尽可能地使用，直到支付的金额小于当前硬币的面值或者已经没有当前硬币了；

* 然后继续使用下一种面值的硬币，依次类推，直到支付的金额减到没有或者所有的硬币都被使用完。
### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int n,c[10],p[1005];
int vl[10]={0,1,5,10,50,100,500};
bool check(int x){
    for(int i=6;i>=1;i--){
        while(x>=vl[i]&&c[i]>0){// 当前值是否大于币值并且还有此种面值的硬币
            x-=vl[i];// 用掉一个硬币
            c[i]--;// 硬币数量减一
        }
    }
    return x==0;
}
signed main(){
    for(int i=1;i<=6;i++)cin>>c[i];
    cin>>n;
    for(int i=1;i<=n;i++)cin>>p[i];
    // 检查每个商店是否可以支付确切的金额
    bool fl=true;
    for(int i=1;i<=n;i++){
        if(!check(p[i])){
            fl=false;
            break;
        }
    }
    cout<<(fl?"Yes":"No")<<endl;   
    return 0;
}

```

---

## 作者：joe_zxq (赞：0)

# 思路

一个很容易想到的贪心：优先使用大面值的硬币，剩下零碎的钱再用小面值的钱来凑。例如有两家商店，第一家商店的商品为 $114$ 元，第二家为 $51$ 元，有 $1$ 张 $100$ 元、$2$ 张 $50$ 元、$1$ 张 $10$ 元和 $5$ 张 $1$ 元。则第一家使用 $1$ 张 $100$ 元、$1$ 张 $10$ 元和 $4$ 张 $1$ 元。若第一家使用 $2$ 张 $50$ 元代替 $1$ 张 $100$ 元的话，则第二家的钱无法支付。

遍历 $N$ 件商品，按照此贪心思路从大面值到小面值每种硬币挨个尝试，如果该种硬币用完或没付清的钱不该面值则尝试下一种硬币。若发现无法付清一件商品则答案为 `No`，否则答案为 `Yes`。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll a[7], c[7] = { 0, 1, 5, 10, 50, 100, 500 };

int main() {
    ll q, x;
    for (ll i = 1; i <= 6; i++) cin >> a[i];
    cin >> q;
    while (q--) {
        cin >> x;
        for (ll i = 6; i >= 1; i--) {
            while (x >= c[i] && a[i] > 0) {
            	x -= c[i], a[i]--;	
			}
        }
        if (x > 0) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
    return 0;
}
```

---

## 作者：linjinkun (赞：0)

### 思路：
其实这道题的主体思想就是：**如果想要拼凑一个数，那么先用面值大的**。为什么呢，因为如果你先用了小面值的，你后面想凑一个不是整的就凑不了了，所以这个思想就是正确的。那么就很容易做出来了。

### 代码（老规矩：有注释）
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10];//懒得用变量了
int mian[10] = {0,1,5,10,50,100,500};//6张硬币的面值，因为初始化得从下标0开始，所以一开始有一个0
int n;
signed main()
{
	for(int i = 1;i<=6;i++)//输入……
	{
		scanf("%d",&a[i]);
	}
	bool flag = 1;//记录是否有凑不整的，初始值为1
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		for(int i = 6;i>=1;i--)//倒着循环相当于先用面值大的
		{
			int t = min(x/mian[i],a[i]);//这个取min很重要，因为x有可能要用x/mian[i]张，但是实际没有这么多张
			x-=t*mian[i];//让x减去t张面值为mian[i]的硬币钱数
			a[i]-=t;//第i种硬币少t张
		}
		if(x!=0)//如果无法凑出x
		{
			flag = 0;//记录
		}
	}
	if(flag == 1)
	{
		printf("Yes");
	}
	else
	{
		printf("No");
	}
	return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

### **一道贪心题~~**  
来证明一下贪心，~~其他题解好像都讲了~~，因为所有大面额的货币都可以拆成面额小的，小的还可以去补空，所以先用面额大的绝对是不亏的。  
代码方面，用一个数组记录每个面额的张数，用另一个数组当做字典，打表写好面额大小，然后输入 $n$，循环 $n$ 次，每次从大面额开始试，如果无法凑完直接输出 `No` 结束程序，在末尾输出 `Yes`。  
## **Code:**
```cpp
#include <iostream>
using namespace std;
int n, x, a[7], num[7]{0, 1, 5, 10, 50, 100, 500};
int main()
{
    for (int i = 1; i <= 6; i++) cin >> a[i];
    cin >> n;
    while (n--)
    {
        cin >> x;
        for (int i = 6; i >= 1; i--)
            while (x >= num[i] && a[i])
            {
                x -= num[i];
                a[i]--;
            }
        if (x)
        {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}
```

---

## 作者：CheZiHe929 (赞：0)

比较显然的一个贪心题。

先使用大面额的，不够再使用小面额的，因为保留小面额可以使得接下来的操作有更多的选择空间。

最后只需要看每件商品能否全部买掉即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

int num[10],a[15],v[]={0,1,5,10,50,100,500};

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	for(int i=1;i<=6;i++)num[i]=read();
	int n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		for(int j=6;j>=1;j--)//先使用大面额 
			if(a[i]>=v[j]){//当前面额比缺的钱多 
				int x=std::min((a[i]/v[j]),num[j]);//取剩余钱数和购买商品所需该面额的钱数的最小值 
				a[i]=a[i]-std::min((a[i]/v[j]),num[j])*v[j];
				num[j]-=x;
			}
		if(a[i]!=0){//没法买下 
			No;
			return 0;
		}
	}
	Yes;

	return 0;
}

```

---

## 作者：ThisIsLu (赞：0)

可以用眼睛发现，这些数都满足大的面额是小的倍数。

这就意味着，有贪心性质：优先用大面额的。

对于每一次消费，不管还有没有钱，先按照贪心策略花钱。

这样当然会有一些面额的钱不够了，这时候就向比它低一级面额的借。

如果低一级面额的也不够，那就继续借。

最后看 $1$ 元面额的够不够就行了。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f;
int n;
const int N=10;
int main(){
    cin>>a>>b>>c>>d>>e>>f>>n;
    for(int i=1;i<=n;i++){
        int ai;
        cin>>ai;
        f-=ai/500;
        ai%=500;
        e-=ai/100;
        ai%=100;
        d-=ai/50;
        ai%=50;
        c-=ai/10;
        ai%=10;
        b-=ai/5;
        ai%=5;
        a-=ai;
        ai=0;
    }
    if(f<0){
        e+=f*5;
        f=0;
    }
    if(e<0){
        d+=e*2;
        e=0;
    }
    if(d<0){
        c+=d*5;
        d=0;
    }
    if(c<0){
        b+=c*2;
        c=0;
    }
    if(b<0){
        a+=b*5;
        b=0;
    }
    if(a<0){
        cout<<"No";
    }
    else cout<<"Yes";
    return 0;
}
```

---

## 作者：int_stl (赞：0)

一道签到题。

平时我们在做这类题的时候，会采用贪心策略，先支付大的面额，再支付小的，能尽量减少支付纸币的数量，在这道题中我们也能这样，模拟即可。

代码如下：
```cpp
int a, b, c, d, e, f;
int main() {
	int n;
	read(a, b, c, d, e, f), read(n);
	while (n--) {
		int mon;
		read(mon);
		while (f && mon >= 500) --f, mon -= 500;
		while (e && mon >= 100) --e, mon -= 100;
		while (d && mon >= 50) --d, mon -= 50;
		while (c && mon >= 10) --c, mon -= 10;
		while (b && mon >= 5) --b, mon -= 5;
		while (a && mon >= 1) --a, mon -= 1;
		if (mon != 0) {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
}
```

---

## 作者：wei2013 (赞：0)

## 思路：
一个贪心吧，我们注意到，这些数字是呈倍数关系的，那自然是越大的面额越难用出去，在数量足够的情况下，少的完全也可已达到相同的效果，那么贪心方案就出来了：让越大的面额尽量用的最多。
## code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    bool ok=0;
    int a,b,c,d,e,f,n;
    cin>>a>>b>>c>>d>>e>>f>>n;
    for(int i=1;i<=n;i++){
    	int x;
    	cin>>x;
    	while(x>=500 && f){
    		f--;
    		x-=500;
		}
		while(x>=100 && e){
    		e--;
    		x-=100;
		}
		while(x>=50 && d){
    		d--;
    		x-=50;
		}
		while(x>=10 && c){
    		c--;
    		x-=10;
		}
		while(x>=5 && b){
    		b--;
    		x-=5;
		}
		while(x>=1 && a){
    		a--;
    		x--;
		}
		if(x!=0){
			ok=1;
		}
	}
	if(ok){
		cout<<"No";
	}else{
		cout<<"Yes";
	}
    return 0;
}
```

---

