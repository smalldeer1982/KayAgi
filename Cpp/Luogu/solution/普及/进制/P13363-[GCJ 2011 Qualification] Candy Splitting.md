# [GCJ 2011 Qualification] Candy Splitting

## 题目描述

Sean 和 Patrick 是一对兄弟，他们刚刚从父母那里得到了一袋美味的糖果。每颗糖果都有一个正整数的价值，兄弟俩想要把糖果分成两份。首先，Sean 会把糖果分成两堆，并选择其中一堆送给 Patrick。然后 Patrick 会尝试计算每堆的价值，其中一堆的价值是该堆所有糖果价值的总和；如果他发现两堆的价值不相等，他就会开始哭泣。

不幸的是，Patrick 还很小，不太会加法。他“几乎”会用二进制加法；但每当他遇到两个 $1$ 相加时，总是忘记向下一位进位。例如，如果他想把 $12$（二进制 $1100$）和 $5$（二进制 $101$）相加，他会正确地加上最右边的两位，但在第三位时会忘记进位：

```
  1100
+ 0101
------
  1001
```

所以在加完最后一位且没有从第三位进位后，最终结果是 $9$（二进制 $1001$）。以下是 Patrick 算数能力的其他例子：

```
5 + 4 = 1
7 + 9 = 14
50 + 10 = 56
```

Sean 很擅长加法，他想在不让弟弟哭泣的前提下，尽可能多地拿到糖果。如果可能的话，他会把糖果分成两堆且都不为空，使得 Patrick 认为两堆的价值相等。给定糖果袋中所有糖果的价值，请你判断是否有可能做到；如果可能，请计算 Sean 能拿到的最大糖果价值。

## 说明/提示

**数据范围**

- $1 \leq T \leq 100$。
- $1 \leq C_i \leq 10^6$。

**小数据范围（10 分，测试点 1 - 可见）**

- $2 \leq N \leq 15$。
- 时间限制：3 秒。

**大数据范围（15 分，测试点 2 - 隐藏）**

- $2 \leq N \leq 1000$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5
1 2 3 4 5
3
3 5 6```

### 输出

```
Case #1: NO
Case #2: 11```

# 题解

## 作者：HZY1618yzh (赞：5)

题意/翻译
---
哥哥肖恩（`Sean`）和弟弟帕特里克（`Patrick`）分糖果，每个糖果都有自己的价值。帕特里克的二进制加法不会进位。请你求出一种方法，使得在帕特里克看来两人的糖果价值的和一样（如果他发现两堆的价值不相等，就会开始哭泣），并且肖恩想要自己的糖果价值最大。如果可以满足要求，就输出弟弟不会哭的最大的价值；如果弟弟一定会哭，就输出 `NO`。

思路
---
首先，本题的难点因该是帕特里克的加法。我们先打个表。

|加数|加数|和|
|:-:|:-:|:-:|
|1|1|0|
|1|0|1|
|0|1|1|
|0|0|0|

可以发现，帕特里克的加法其实就是异或运算（xor，$\oplus$，`^`）。

进一步思考，若可以分成两堆，则两堆的异或和必须是相等的（不相等会导致弟弟哭泣）。又因为两个相等的数的异或和是 $0$（每一位都相同，所以和的每一位都是 $0$），可以推导出：若可以满足要求，那么所有糖果的价值的异或和是 $0$。

可是这只是处理了是否输出 `NO` 的情况，没有计算分得糖果的最大价值。我们可以试试贪心的思想，把最小的糖果分给弟弟。因为只有两个相同的数异或，结果才为 $0$，所以最小的糖果和剩余的糖的异或和是一样的。

代码
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,c[1001];
int main() {
	cin>>t;//t组测试样例
	for(int cas=1;cas<=t;cas++) {//处理每组测试
		cin>>n;//输入
		int xors=0,sum=0;//异或和，总和
		for(int i=1;i<=n;i++){
			cin>>c[i];//输入
			xors^=c[i];//异或和
			sum+=c[i];//总和
		}
		if(xors!=0) cout<<"Case #"<<cas<<": NO\n";
//如果异或和不为0，那么怎么分都不可能让弟弟不哭
		else cout<<"Case #"<<cas<<": "<<sum-(*min_element(c+1,c+1+n))<<'\n';
//min_element是求最小值。用贪心思想，总和减去最小值（给弟弟的），剩下的最大（哥哥）
	}
	return 0;
}
```
~~要是哥哥善良一点，就不会有这题了。~~

---

## 作者：qkj_qwq (赞：3)

## 解题思路

通过读题，可发现：这不是异或吗？

所以，如果两堆价值相等，那么两堆异或起来就是 $0$（相等的两个数异或起来是 $0$）。由于两堆价值的计算方法也是异或，所以若 $N$ 个数的异或和不为 $0$，则无解，输出 `NO`。

否则，因为要让 Sean 拿到更多糖果，那就把价值最小的那一颗糖留给 Patrick，其它都给 Sean。可以证明他们的糖的价值相等。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		int n,ss=0,sum=0,minn=INT_MAX;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			ss^=x;
			sum+=x;
			minn=min(minn,x);
		}
		if(ss)cout<<"NO\n";
		else cout<<sum-minn<<'\n';
	}
	return 0;
}
```

---

## 作者：Felicita (赞：1)

## 题目描述
Sean 和 Patrick 是一对兄弟，他们想要分糖果。Patrick 会用**不进位**的二进制加法计算两堆糖果的总**价值**，如果不**相等**，他就会哭。而哥哥 Sean ~~非常邪恶~~计算技术高超，他想在弟弟 Patrick 不哭的情况下拿走**最多的糖果价值**。如果实在不行了，就输出 `NO`（注意不是 `No` 或 `no`，我被坑过）。
## 解题思路
众所周知，**不进位**的二进制加法，就相当于位运算中的**异或**（$\oplus$，在 C++ 中写作 `^`），不信的话可以自己举例。
### 弟弟会哭的情况
怎么判断弟弟会不会哭呢，我有一个思路，首先把所有的糖果价值**异或**，因为如果两堆的**异或和相等**的话，那么两堆的异或和异或答案为 $0$（因为相等的数异或和为 $0$），如若**不满足**这个条件的话，则弟弟一定会哭。
### 弟弟不会哭的情况
如若**满足**这个条件的话，那怎么保证**哥哥**拿到的糖果的**价值最大**呢，在这里，我们可以利用贪心的视角，将弟弟拿的糖果价值设为所有糖果价值中**最小的糖果价值**。

为什么？我们将弟弟的**糖果价值**设为 $X$，哥哥的总糖果价值为 $Y$，已知两堆糖果**异或和**为 $0$，则 $X \oplus Y = 0$，因为相等的数**异或和**为 $0$，所以 $X$ 一定等于 $Y$，所以我们可以放心大胆的将**最小价值的糖果**给弟弟（我们可真邪恶）。我们最终只要输出糖果的**总异或和**减去**最小价值的糖果**就可以了。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		int n;
		scanf("%d",&n);
		int myxor=0,sum=0,minx=1000005;
		for(int j=1;j<=n;j++)
		{
			int v;
			scanf("%d",&v);
			myxor^=v;//总异或和
			sum+=v;//总价值
			minx=min(minx,v);//最小价值的糖果的价值
		}
		if(myxor!=0)//如果总异或和不是0，则弟弟一定会哭，输出"NO"
		{
			printf("Case #%d: NO\n",i);
		}
		else
		{
			printf("Case #%d: %d\n",i,sum-minx);//反之输出总异或和减去最小价值的糖果的价值。
		}
	}
	return 0;
}
```
## 提醒
**亲测有效**，**请勿抄袭**！

---

## 作者：4041nofoundGeoge (赞：1)

定义所有糖果的异或总和为：$\text{totalXOR} = \bigoplus_{i=1}^{N} C_i$。如果存在分堆 $A$ 和 $B$，使得 $A \oplus B = 0$，则：$\text{totalXOR} = A \oplus B = 0$。因此，能够分堆的必要条件是 $\text{totalXOR} = 0$。

当 $\text{totalXOR} = 0$ 时，任意分堆 $A$ 和 $B$ 都满足 $A \oplus B = 0$。因为：$A \oplus B = \text{totalXOR} = 0$。

为了使 Sean 获得的价值最大，我们需要让 Patrick 获得的价值最小。因为两堆的价值在异或意义下相等，Patrick 获得的最小价值是糖果中的最小值 $\min(C_i)$。因此理想最优为：
   - 堆 $A$：包含所有糖果，总价值为 $\sum_{i=1}^{N} C_i$。
   - 堆 $B$：仅包含 $\min(C_i)$，价值为 $\min(C_i)$。

但这样 $A$ 和 $B$ 的异或不满足条件。实际上，正确的分堆方式是：

   - 堆 $A$：包含除 $\min(C_i)$ 外的所有糖果，价值为 $\sum_{i=1}^{N} C_i - \min(C_i)$。
   - 堆 $B$：仅包含 $\min(C_i)$，价值为 $\min(C_i)$。

   此时：$A \oplus B = \left( \bigoplus_{i \neq \min} C_i \right) \oplus \min(C_i) = \text{totalXOR} = 0$，因为 $\bigoplus_{i=1}^{N} C_i = 0$，所以 $\bigoplus_{i \neq \min} C_i = \min(C_i)$。

因此 Sean 的最大价值为 $S_{\text{Sean}} = \sum_{i=1}^{N} C_i - \min(C_i)$。

代码就非常好写了。

---

## 作者：xtzhangziche (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13363)

## 思路
观察题目，我们发现 Patrick 的加法就是异或。

首先，我们可以求所有数的异或和、和还有最小值，因为 $a \oplus a = 0$，可以得知：如果所有数的异或和为 $0$，则分成两堆的糖果的异或和相等，当所有数的异或不为 $0$ 时，则分成两堆的糖果的异或和不同，Patrick 会哭泣，输出 `NO`。

```cpp
for(int i=1;i<=n;i++)
    cin>>a,yh^=a,he+=a,minn=min(minn,a);
if(yh) cout<<"NO\n";
```

然后，我们刚才求的和还有最小值派上了用场，因为 $a \oplus a = 0$，所以只用给 Patrick 一颗价值最小的糖，剩余的糖给 Sean，那 Sean 拿到的糖的价值总数就是最大的，也就是所有数的和减去最小值。

```cpp
else cout<<he-minn<<'\n';
```

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,t;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--)
    {
        int n,a,yh=0,he=0,minn=1e6+5;
        cin>>n;
        cout<<"Case #"<<++t<<": ";
        for(int i=1;i<=n;i++)
            cin>>a,yh^=a,he+=a,minn=min(minn,a);
        if(yh) cout<<"NO\n";
        else cout<<he-minn<<'\n';
    }
    return 0;
}
```

---

## 作者：Doraeman (赞：0)

观察 Patrick 的“加法”计算方法，就会发现，这就是——号称“不进位加法”的，~~传说中的~~**异或**（符号为 $\oplus$）。

## 芝士
与本题有关的**异或规则**如下。

- 异或有**交换律**和**结合律**。
- 对于十进制数 $a,b$，**$a\oplus b=0$ 与 $a=b$ 等价**。

## 规则应用
循环求所有糖果的异或总值 $xor_{tot}$。 

设将所有糖果任意分成两堆，其异或值分别为 $a,b$。  
根据异或的结合律，$a\oplus b=xor_{tot}$。

- 如果 $xor_{tot}\not=0$，说明 $a\oplus b\not=0$。根据规则，$a\not=b$。  
  此时，在 Patrick 眼中两堆糖果价值不相等。无论如何分堆，他一定会哭，直接输出 ```NO```。
- 如果 $xor_{tot}=0$，说明 $a\oplus b=0$。根据规则，$a=b$。  
  此时，在 Patrick 眼中两堆糖果价值相等，不会哭。

  这种情况下考虑求 Sean 可以获得的糖果的最大价值。

## 求最大价值
在 Sean 眼中，一堆糖果的总价值是所有糖果的**价值之和**（而非异或值）。

这种情况下，可以求出所有糖果的价值之和。由于必须分给 Patrick 一个非空堆，所以可以直接给他一个价值最低的糖果（~~兄弟情义呢？塑料兄弟情？~~），剩余的 $N-1$ 颗糖果都给 Sean，这时他的糖果总价值最大。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T; cin >> T;
    for(int _=1; _<=T; _++){
        int n; cin >> n;
        int xor_tot = 0, sum = 0, mini = 1e6+5;
        for(int i=1; i<=n; i++){
            int x; cin >> x;
            xor_tot ^= x;
            sum += x;
            mini = min(x, mini);
        }
        
        cout << "Case #" << _ << ": ";
        if(!xor_tot) cout << sum - mini << '\n';
        else cout << "NO\n";
    }
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13363)

首先题目中 Patrick 的算数就是异或，即 $\text{xor}$ 或 $\oplus$。

如果有方案使得两堆糖果异或和相等，则根据 $a \oplus a=0$ 得所有糖果的总异或和为 $0$。而当异或和为 $0$ 时，无论如何分组都会使得两堆糖果异或和相等。

所以如果有解则拿走除了价值最小的糖果外的所有糖果即可。

代码：

```cpp
//copper_ingot
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
pii mkp(int x, int y){pii p; p.first = x, p.second = y; return p;}
int T, n, c[200001];
signed main(){
	scanf("%lld", &T);
	for (int t = 1; t <= T; t++){
		scanf("%lld", &n);
		int x = 0, sum = 0, minn = 0x3f3f3f3f3f3f3f3f;
		for (int i = 1; i <= n; i++){
			scanf("%lld", &c[i]);
			x ^= c[i], sum += c[i], minn = min(minn, c[i]);
		}
		if (x){printf("Case #%lld: NO\n", t); continue;}
		printf("Case #%lld: %lld\n", t, sum - minn);
	}
	return 0;
}
```

---

## 作者：chenzhuole1 (赞：0)

## 题解：P13363 [GCJ 2011 Qualification]

[题目链接](https://www.luogu.com.cn/problem/P13363)

### 题目翻译

Sean 和 Patrick 兄弟从父母那里得到了一袋糖果。每颗糖果都有一个正整数值，他们想把糖果分成两堆。首先，Sean 将糖果分成两堆，并选择一堆给 Patrick。然后，Patrick 会计算每堆糖果的价值（即堆中所有糖果值的总和）。如果他发现两堆的价值不相等，就会开始哭闹。

Patrick 还很小，不会正确的加法。他只会一种近似的二进制加法：当两个 $1$ 相加时，他会忘记进位。例如，计算 $12$，二进制$1100$ 和 $5$，二进制 $0101$ 的和时，他会这样计算：

```
  1100
+ 0101
------
  1001
```

结果得到 $9$（二进制 $1001$），因为他没有正确处理进位。其他例子：

```
5 + 4 = 1
7 + 9 = 14
50 + 10 = 56
```

Sean 擅长加法，希望在不惹哭弟弟的情况下，尽可能多地拿走糖果的价值。我们需要判断是否可以将糖果分成两堆，使得 Patrick 认为两堆的价值相等。如果可能，求出 Sean 能拿走的堆的最大价值。

输入格式

第一行是测试用例数 $T$。每个测试用例包含两行：第一行是糖果数 $N$，第二行是 $N$ 个糖果的值 $C_i$。

输出格式

对于每个测试用例，输出 "Case #x: y"，其中 $x$ 是测试用例编号。如果无法满足条件，$y$ 为 "NO"；否则，$y$ 为 Sean 能拿走的堆的最大价值。

### 思路

观察题目样例很容易发现，Patrick 的加法实际上是按位异或。因此，我们把问题转化为如何才能使得两堆的异或和相等。设总异或和为 $sum$，若 $sum$ 为 $0$，则可以将糖果分成任意两堆，否则无法满足条件。

若总异或和为 $0$，则 Sean 可以拿走任意一堆，为了保证剩下的子集的异或和与原总异或和均为 $0$，可以考虑拿走总和最大的子集，其总和为总糖果和减去最小的糖果值。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,s,c[100005];
void solve(int tas)
{
	x=0,s=0;
	memset(c,0,sizeof(c));
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		x^=c[i];
		s+=c[i];
	}
	if(x!=0)
	{
		cout<<"Case #"<<tas<<": NO\n";
		return;
	}
	int mn=1e18;
	for(int i=1;i<=n;i++) mn=min(mn,c[i]);
	cout<<"Case #"<<tas<<": "<<s-mn<<'\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int i=1;i<=t;i++) solve(i);
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13363)

### 思路

首先，通过找规律得出，弟弟的这种算法就是异或。

接着我们就可以先求出整个序列的异或和，记为 $s$。

那么我们就是要求一个数 $x$，使得 $x$ 是序列中一个非空子集的和，并且 $x$ 异或上自己为 $s$。

我们又知，一个数异或自己肯定为 $0$，所以 $s$ 肯定为 $0$，那么 $s$ 不为 $0$ 的情况就可以输出```NO```，否则因为子集非空，就直接从小到大排个序，取 $a_2$ 到 $a_n$ 的和即可，注意这里不是异或和，因为这是哥哥的正常算法，并不是弟弟的。

注意输出的格式。
### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[1005],s;
signed main(){
    cin>>t;
    for(int i=1;i<=t;i++)
    {
    	scanf("%lld",&n);
    	s=0;
    	for(int j=1;j<=n;j++)
    	{
    		scanf("%lld",&a[j]);
    		s^=a[j];
    	}
    	if(s!=0)  printf("Case #%lld: NO\n",i);
    	else
    	{
    		s=0;
    		sort(a+1,a+n+1);
    	    for(int j=2;j<=n;j++)
    	    {
    	    	s+=a[j];
    	    }
    	    printf("Case #%lld: %lld\n",i,s);
    	}
    }
    return 0;
}
```

---

