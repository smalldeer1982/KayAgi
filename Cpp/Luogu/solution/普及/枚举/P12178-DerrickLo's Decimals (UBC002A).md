# DerrickLo's Decimals (UBC002A)

## 题目背景

You can switch the language of the problem description.

![](https://cdn.luogu.com.cn/upload/image_hosting/96tdfgkh.png)

## 题目描述

有一个循环节长度为 $n$ 的纯循环小数，它可以表示为 $a = 0.\dot{a_1}a_2\dots\dot{a_n}$。

由于 DerrickLo 的计算机受奶龙影响产生了精度问题，它只给 DerrickLo $n$ 个数 $b_1, b_2, \dots, b_n$，其中 $b_i$ 表示将 $a$ 四舍五入到小数点后 $i$ 位后第 $i$ 位的值。

DerrickLo 请你帮忙计算出所有可能的 $a$ 的值，将它们求和后**乘以 $10^n - 1$** 输出。

注意，这里的四舍五入只看下一位的数值。令 $\text{round}$ 表示四舍五入函数，则 $\text{round}(0.5) = 1$，$\text{round}(0.49999) = 0$。形式化地，$b_i$ 可以表示为 $(\text{round}(a \times 10^i)) \bmod 10$。

## 说明/提示

## 样例解释

### 样例 $1$

令 $a = 0.\dot{0}13\dot{2}$，则有：

- $a$ 四舍五入到第一位的值为 $0.0$，第一位为 $0$。
- $a$ 四舍五入到第二位的值为 $0.01$，第二位为 $1$。
- $a$ 四舍五入到第三位的值为 $0.013$，第三位为 $3$。
- $a$ 四舍五入到第四位的值为 $0.0132$，第四位为 $2$。

因此 $a = 0.\dot{0}13\dot{2}$ 符合题目要求。

可以证明，没有其他答案，故符合条件的 $a$ 的和为 $0.\dot{0}13\dot{2}$，乘以 $10^4 - 1$ 后为 $132$，补齐前导零后为 $0132$。

### 样例 $2$

令 $a = 0.\dot{5}87\dot{6}$，则有：

- $a$ 四舍五入到第一位的值为 $0.6$，第一位为 $6$。
- $a$ 四舍五入到第二位的值为 $0.59$，第二位为 $9$。
- $a$ 四舍五入到第三位的值为 $0.588$，第三位为 $8$。
- $a$ 四舍五入到第四位的值为 $0.5877$，第四位为 $7$。

因此 $a = 0.\dot{5}87\dot{6}$ 符合题目要求。

可以证明，没有其他答案，故符合条件的 $a$ 的和为 $0.\dot{5}87\dot{6}$，乘以 $10^4 - 1$ 后为 $5876$。

## 数据范围

对于所有数据，满足 $1 \le n \le 10^6$，$0 \le b_i \le 9$。

## 样例 #1

### 输入

```
4
0 1 3 2```

### 输出

```
0132```

## 样例 #2

### 输入

```
4
6 9 8 7```

### 输出

```
5876```

# 题解

## 作者：Phoenix_2010 (赞：4)

upd 2025.4.26:改了一个小笔误

可以列出如下方程：
$$
\left\{
\begin{array}{l}
a_1=(b_1-[a_2\ge5])\bmod10\\
a_2=(b_2-[a_3\ge5])\bmod10\\
\qquad\qquad\quad\vdots\\
a_{n-1}=(b_{n-1}-[a_n\ge5])\bmod10\\
a_n=(b_n-[a_1\ge5])\bmod10
\end{array}
\right.
$$
这是由于四舍五入的定义，$(a_i+[a_{i+1}\ge5])\bmod10=b_i$。

由于这个小数是循环的，所以第 $n+1$ 位等于第一位。

乍一看这个东西不太能解的样子，但是发现只要确定一个未知数的值，可以通过 $n-1$ 组确定其他未知数，而且剩下一组用于检验。

考虑枚举 $a_1$。发现它只有两种情况：$a_1=b_1$ 或 $a_1=(b_1-1)\bmod10$。

然后就能算出 $a_n$，进而 $a_{n-1},\dots,a_2$。然后检查一下通过 $a_2$ 算出的 $a_1$ 与刚开始钦定的是否相等。

答案就是 $\sum (10^n-1)a=\sum(10^n-1)\frac{\overline{a_1a_2\dots a_n}}{10^n-1}=\sum \overline{a_1a_2\dots a_n}$，写一个简单的高精度加法即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,b[N],a[N],ans[N];
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>b[i];
    if(n==1){cout<<(b[1]<5?b[1]:0);return 0;}//n=1时a[2]不存在，要特判。注意无解代表和为0。
    //第一种情况
    a[1]=b[1];a[n]=(b[n]-(a[1]>=5)+10)%10;
    for(int i=n-1;i>1;i--) a[i]=(b[i]-(a[i+1]>=5)+10)%10;
    if(a[1]==(b[1]-(a[2]>=5)+10)%10) for(int i=1;i<=n;i++) ans[i]+=a[i];
    //第二种情况
    a[1]=(b[1]+9)%10;a[n]=(b[n]-(a[1]>=5)+10)%10;
    for(int i=n-1;i>1;i--) a[i]=(b[i]-(a[i+1]>=5)+10)%10;
    if(a[1]==(b[1]-(a[2]>=5)+10)%10) for(int i=1;i<=n;i++) ans[i]+=a[i];
    for(int i=n;i>1;i--) if(ans[i]>9) ans[i]-=10,ans[i-1]++;//保证了答案不超过n位
    for(int i=1;i<=n;i++) cout<<ans[i];
    return 0;
}
```

---

## 作者：suzhikz (赞：4)

越学越糖，黄题都切不了。

首先是循环节，所以第 $1$ 位对第 $n$ 位在四舍五入的情况下会有影响。

但是如果我们已知第 $n$ 位的话，我们就可以从后往前一位一位递推出每一位。

第 $n$ 位受到第 $1$ 位的影响，那么不妨假设原序列第 $1$ 位是大于等于五还是小于，分类成两种情况，分别递推，最后检查第 $1$ 位是否满足我们假设的情况就做完了。

递推就是检查上一位是否大于等于五，如果大于等于的话，这一位就要减去一，这一位没有数就去上面借，然后借完从这一位到借的位置的值就求出来了，不要再重复求，否则借的那一位会重复减一。

复杂度 $O(n)$。

可能有点难懂，放代码辅助理解吧。


```cpp
#include<bits/stdc++.h>//Are dreams merely lost wings in the concrete jungle？
#define il inline
#define reg register
#define ll long long
#define popcount __builtin_popcount
using namespace std;
inline void read(int &n){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}n=x*f;}
const int N=1e6+5;
int n,a[N];
int b[N],c[N],d[N];
int work(int k[],int i){
	for(int j=i;j>=1;j--){
		if(k[j]){
			k[j]--;
			return j;
		}
		else k[j]=9;
	}
	return 0;
}
int main(){
	read(n);for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)b[i]=c[i]=a[i];
	for(int i=n;i>=1;i--){
		if(b[i+1]>=5){
			i=work(b,i);
		}
	}
	work(c,n);
	for(int i=n;i>=1;i--){
		if(c[i+1]>=5){
			i=work(c,i);
		}
	}
	if(c[1]>=5){
		for(int i=n;i>=1;i--)d[i]+=c[i];
	}
	if(b[1]<5){
		for(int i=n;i>=1;i--){
			d[i]+=b[i];
			d[i-1]+=d[i]/10;d[i]%=10;
		}
	}
	for(int i=1;i<=n;i++)cout<<d[i];
	return 0;
}

```

---

## 作者：cosf (赞：3)

可以观察到，如果存在一位是 $1, 2, 3, 4, 6, 7, 8, 9$，则它前一位是否有“五入”是可以唯一确定的，这种情况可以枚举一遍得到答案。答案至多有一个。

若所有的 $b_i$ 均是 $0$ 或 $5$，则可以枚举其中一位是 $b_i$ 还是 $(b_i + 9) \bmod 10$，然后即可判断。

答案至多有两个，并且两种答案中 $a_i$ 一个为 $b_i$，一个为 $(b_i + 9) \bmod 10$，因此加起来不会进位（$0 + 9 = 5 + 4 \lt 10$）。

乘以 $10^n - 1$ 相当于取循环节。

---

当然，更简单的方法是，枚举 $a_n$ 是 $b_n$ 还是 $(b_n + 9) \bmod 10$。

```cpp
#include <iostream>
using namespace std;

#define MAXN 1000006

int n;

int v[MAXN], r[MAXN];

bool check(int l)
{
    int a = l;
    for (int i = n - 1; i; i--)
    {
        a = (v[i] + 10 - (a > 4)) % 10;
    }
    return (l + (a > 4)) % 10 == v[n];
}

void add(int l)
{
    r[n] += l;
    for (int i = n - 1; i; i--)
    {
        r[i] += l = (v[i] + 10 - (l > 4)) % 10;
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i];
        r[i] = 0;
    }
    if (check(v[n]))
    {
        add(v[n]);
    }
    if (check((v[n] + 9) % 10))
    {
        add((v[n] + 9) % 10);
    }
    for (int i = 1; i <= n; i++)
    {
        cout << r[i];
    }
    cout << endl;
    return 0;
}

```

---

## 作者：Motonic_queues (赞：2)

## 题意分析
题意说的很清楚了

## 思路分析
先抛开两个很特殊的数：$5$ 和 $0$，至于为什么一会再谈。

考虑对于**普遍的**情况进行求解：  
可以从后往前考虑，如果最后一位大于 $5$，则前一位的真实值是给出的值减一，如果小于 $5$ 不减，之后每一位根据当前真实值（即答案）一样的推，很好理解。  
推到第一位之后，根据第一位的真实值再处理最后一位，因为暂时不考虑最后一位是 $5$ 或 $0$，所以不难发现这一位加一减一其实没有影响。

如果有 $5$ 和 $0$ 呢？毕竟前者如果是进了一的，那它大于等于 $5$ 就不能去给下一位进一，后者则反之。  

先考虑不全是 $5$ 和 $0$ 的情况，这还是挺好办的：  
我管你这那的，既然是循环节，那就让它循环吧，你总得有不是 $5$ 和 $0$ 的数吧，不断循环，把一个不是 $5$ 和 $0$ 的数绕到最后一位：   
```cpp
for(int i=1;a[i]==5||a[i]==0;i++)a[n+i]=a[i],st++;
```
此处 `st` 记录第一位的位置，接下来只要按照前面的方式处理就可以了，末尾需要把答案再循环回来。  

接下来最棘手的情况登场了：只有 $5$ 和 $0$。  
先上结论：如果 $5$ 的个数是奇数则无解，否则答案是 $n$ 个 $9$。  
为什么？  

首先观察 $0$ 的影响：发现如果一个 $0$ 的真实值是 $9$，那其后面的 $0$ 的真实值也是 $9$，这样会一直传递，直到下一个 $5$，其真实值为 $4$，这和完全没有 $0$ 是等价的，**所以在答案中 $0$ 没有任何影响**。  
那 $5$ 呢？先去除所有的 $5$，会发现在真实值中 $5$ 和 $4$ 交错，这就意味着真实值中 $5$ 和 $4$ 的数量是一样的，那么只有奇数个 $5$ 自然就无解了；  
而偶数个，将所有的 $5$ 和 $4$ 互换后答案仍然合法，同时 $0$ 和 $9$ 也会翻转，两个加起来，答案就全是 $9$ 了。  

这个情况相当极端，只有无解和有双解两种可能，需要特判。  
你问通常状况有没有多解？观察一下推的过程就能发现肯定是没有的。  

## Talk is cheap,show me the code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+7;
int n,a[2*N],ans[2*N],st=1,cnt5;
int flag=1;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],cnt5+=(a[i]==5),flag&=(a[i]==5||a[i]==0);
	if(flag){
		for(int i=1;i<=n;i++)cout<<((cnt5&1)?0:9); // 特殊情况
		return 0;
	}
	for(int i=1;a[i]==5||a[i]==0;i++)a[n+i]=a[i],st++; // 循环
	a[n+st]=a[st];
	ans[n+st]=a[n+st];
	for(int i=n+st;i>st;i--){
		if(ans[i]>=5)ans[i-1]=(a[i-1]+9)%10; // 推答案
		if(ans[i]<5)ans[i-1]=a[i-1];
	}
	ans[n+st]=ans[st];
	for(int i=n+st;i>n;i--)
		ans[i-n]=ans[i]; // 循环回来
	for(int i=1;i<=n;i++)cout<<ans[i];
	return 0;
}
```

---

## 作者：corner_xiejunqi (赞：1)

## 题目分析：
### 设置数组：
令 $a$ 为原始循环小数，$b$ 为每位四舍五入后的循环小数。$ans$ 为最终答案。
### 解题思路：
首先看到题目，就会想到 $0$ 和 $5$ 两个特殊值该怎么处理，然后就会一直想不出来，卡死在这里。

我们不妨先考虑当什么时候 $a_i$ 会加 $1$，什么时候 $a_i$ 不会加 $1$。很明显当 $a_{i+1}\geq5$ 时，会加 $1$。那么该如何求出原循环小数的方法就很明了了。只需找到第一个无论它加没加 $1$，都对它的上一位没有影响的数，即不等于 $0$ 和 $5$ 的数。因为为纯循环小数，所以可以将 $a_1$ 到这个数全部移到末尾。在按照从末尾到开头的顺序走一遍即可确定原循环小数。从前面的推理也不难看出当有这个数时只有一种情况。
#### 那么没有这个数，该怎么办呢？
那么 $b$ 中就只有 $0$ 和 $5$ 两种数。当 $b_i=0$ 时，那么 $b_{i+1}$ 为 $0$ 或 $9$，且各自只能出现一次。不难看出当为连续零时，那么和为 $9$。那么当 $b_i=5$ 时，此时 $b_{i+1}$ 可能为 $4$ 或 $5$，且交替成对出现，所以这里就有两种情况且和为 $9$。因为是成对出现，所以当 $5$ 的个数为奇数时无解，输出 $n$ 个 $0$ 即可。否则输出 $n$ 个 $9$。
## 代码如下：

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,pos=1;
int b[2*N],ans[2*N];
signed main(){
	// step 1、读题、声明变量
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	// step 2、输入
	cin>>n;
	bool f=true;
	for(int i=1;i<=n;i++) cin>>b[i],f=(f&&(b[i]==0||b[i]==5));
	// step 3、处理
	if(f){
		int _5=0;
		for(int i=1;i<=n;i++) _5+=(b[i]==5);
		if(_5%2==1) for(int i=1;i<=n;i++) cout<<0;
		else for(int i=1;i<=n;i++) cout<<9;
		return 0;
	}
	for(int i=1;b[i]==0||b[i]==5;i++) b[i+n]=b[i],pos++;
	b[n+pos]=b[pos];
	ans[n+pos]=b[n+pos];
	for(int i=n+pos;i>pos;i--){
		if(ans[i]>=5) ans[i-1]=(b[i-1]+9)%10;
		else ans[i-1]=b[i-1];
	}
	// step 4、输出
	ans[n+pos]=ans[pos];
	for(int i=n+pos;i>n;i--) ans[i-n]=ans[i];
	for(int i=1;i<=n;i++) cout<<ans[i];
	//cout<<ans;
	return 0;
}
```
居然黄题都切不掉了，我还得多练啊！

---

## 作者：szh_AK_all (赞：1)

比较巧妙的一题。

首先考虑 $a_1$ 是多少，显然 $a_1$ 只可能是 $b_1$ 或者 $b_1-1$，那么不妨枚举 $a_1$ 的取值，然后由 $a_1$ 推出其他数的值。

显然由 $a_1$ 推 $a_2$ 不是很好操作，但是由 $a_1$ 推 $a_n$ 是可行的，因为 $a_n$ 是否“五入”就看 $a_1$ 的值，如果 $a_1\le 4$，则 $a_n=b_n$，否则 $a_n=b_n-1$。

确定 $a_n$ 的值后，可以用同样的方法确定 $a_{n-1},a_{n-2},\dots,a_2$ 的值，然后再看此时的 $a_1$ 是否合法即可。

注意 $9$ 在进位后是 $0$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005], b[1000005][3], c[1000005];

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	if (n == 1) {
		if (a[1] <= 4)
			cout << a[1];
		else if (a[1] == 5)
			cout << 0;
		else
			cout << a[1] - 1;
		return 0;
	}
	b[1][1] = a[1];
	if (a[1] <= 4)
		b[n][1] = a[n];
	else {
		b[n][1] = a[n] - 1;
		if (!a[n])
			b[n][1] = 9;
	}
	for (int i = n - 1; i >= 2; i--) {
		if (b[i + 1][1] >= 5) {
			b[i][1] = a[i] - 1;
			if (a[i] == 0)
				b[i][1] = 9;
		} else
			b[i][1] = a[i];
	}
	int f = 1;
	if (b[2][1] >= 5)
		f = 0;
	b[1][2] = a[1] - 1;
	if (a[1] == 0)
		b[1][2] = 9;
	if (b[1][2] <= 4)
		b[n][2] = a[n];
	else {
		b[n][2] = a[n] - 1;
		if (!a[n])
			b[n][2] = 9;
	}
	for (int i = n - 1; i >= 2; i--) {
		if (b[i + 1][2] >= 5) {
			b[i][2] = a[i] - 1;
			if (a[i] == 0)
				b[i][2] = 9;
		} else
			b[i][2] = a[i];
	}
	int g = 1;
	if (b[2][2] < 5)
		g = 0;
	for (int i = 1; i <= n; i++) {
		if (b[i][1] < 0)
			f = 0;
		if (b[i][2] < 0)
			g = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (f)
			c[i] += b[i][1];
		if (g)
			c[i] += b[i][2];
	}
	for (int i = n; i >= 1; i--) {
		if (c[i] > 9)
			c[i - 1] += c[i] / 10, c[i] %= 10;
	}
	for (int i = 1; i <= n; i++)
		cout << c[i];
}
```

---

## 作者：粥2414 (赞：1)

# 题目描述
有一个循环节长度为 $n$ 的无限循环小数，告诉你四舍五入保留 $i$ 位后第 $i$ 位上的数字，求这个无线循环小数所有可能的循环节之和。无解输出 $n$ 个 $0$。
# 思路
对于每一位分别考虑。

设当前考虑到循环节第 $i$ 位的数字。显然它只可能为 $b_i$ 或 $\begin{cases} b_i-1&b_i\neq 0\\ 9& b_i=0\end{cases}$，对应下一位是否进位。

显然若 $b_{i+1}>5$，那么一定会进位，若 $b_{i+1}<5$ 且 $b_{i+1}>0$，那么一定不会进位。

而对于 $b_{i+1}=5$ 或 $0$ 的情况，则需要进一步判断第 $i+2$ 的情况。递归即可。

注意最后一位的进位情况由第一位决定。

容易发现，只要存在一位非 $5$ 或 $0$ 的数字，那么就有唯一解，原因是可以从这一位开始推导出其他所有位是否进位。

而当所有位均为 $5$ 或 $0$ 时，此时不一定有解，且无唯一解。所以可以分别假设最后一位是否进位，然后推导出其他答案。若第一位的大小与假设的进位情况相矛盾则非法，否则将两种情况相加即可。

然后就可以愉快地 AC 啦！
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read() {
	int x = 0, f = 1;
	char ch;
	while ((ch = getchar()) < 48 || ch > 57)if (ch == '-')f = -1;
	while (ch >= 48 && ch <= 57)x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
char __sta[1009], __len;
inline void write(ll x, bool bo) {
	if (x < 0)putchar('-'), x = -x;
	do __sta[++__len] = x % 10 + 48, x /= 10;
	while (x);
	while (__len)putchar(__sta[__len--]);
	putchar(bo ? '\n' : ' ');
}
const ll N=1e6+9;
ll b[N];
ll n;
ll a[N];
ll c[N];
int solve(ll now){
	if(now>n){
		if(a[1]==-1&&(b[1]==0||b[1]==5))return -1;
		else{
			if(a[1]!=-1)return a[1];
			else return b[1];
		}
	}
	int nex=now+1;
	if(nex==n+1)nex=1;
	if(a[nex]!=-1){
		if(a[nex]>=5){
			a[now]=b[now]-1;
			if(a[now]<0)a[now]=9;
		}
		else{
			a[now]=b[now];
		}
		return a[now];
	}
	if(b[nex]<5&&b[nex]>0){
		a[now]=b[now];
		return a[now];
	}
	if(b[nex]>5){
		a[now]=b[now]-1;
		if(a[now]<0)a[now]=9;
		return a[now];
	}
//	cout<<now<<endl;
	int op=solve(now+1);
	if(op==-1)return -1;
	if(op<5&&op>=0){
		a[now]=b[now];
		return a[now];
	}
	if(op>=5){
		a[now]=b[now]-1;
		if(a[now]<0)a[now]=9;
		return a[now];
	}
}
int main(){
	memset(a,-1,sizeof(a));
	n=read();
	for(int i=1;i<=n;i++){
		b[i]=read();
	}
	ll op=0;
	for(int i=1;i<=n;i++){
		if(a[i]==-1)op=solve(i);
		if(op==-1)break;
	}
	if(op==-1){
		if(b[n]==5){
			a[n]=4;
			c[n]=5;
		}
		if(b[n]==0){
			a[n]=9;
			c[n]=0;
		}
		for(int i=n-1;i>0;i--){
			if(a[i+1]<5)a[i]=b[i];
			if(a[i+1]>=5){
				a[i]=b[i]-1;
				if(a[i]<0)a[i]=9;
			}
			if(c[i+1]<5)c[i]=b[i];
			if(c[i+1]>=5){
				c[i]=b[i]-1;
				if(c[i]<0)c[i]=9;
			}
		}
		if(a[1]==0||a[1]==4||c[1]==5||c[1]==9){
			memset(a,0,sizeof(a));
		}
		else{
			for(int i=1;i<=n;i++){
				a[i]+=c[i];
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld",a[i]);
	}
	return 0;
}
```

---

## 作者：AutumnQ (赞：1)

手玩做法：

这道题在无脑交一遍后发现不是贪心，遂打表找规律。

先枚举一个 $i$ 表示四舍五入之后的数，再枚举 $j$ 表示四舍五入前的数。

最终再进行比较，若符合就输出。

下面给出打表代码：
```cpp
int a[10],b[10];
int c[10];
int len=4;
bool chk(){
	for(int i=1;i<=len;i++){
		if(a[i]!=c[i])return 0;
	} 
	return 1;
}
signed main(){
	free();
	for(int i=0;i<=ksm(10,len)-1;i++){
		bool all=0;
		bool all50=0;
		for(int ii=1;ii<=len;ii++){
			a[ii]=i/ksm(10,len-ii)%10;
			//if(a[i]>=5)all=0;
		}
		//if(all)continue;
		cout<<i<<":";
		for(int j=0;j<=ksm(10,len)-1;j++){
			for(int ii=1;ii<=len;ii++){
				b[ii]=j/ksm(10,len-ii)%10;
			}
			for(int ii=1;ii<len;ii++){
				if(b[ii+1]>=5)c[ii]=b[ii]+1;
				else c[ii]=b[ii];
			}
			if(b[1]>=5)c[len]=b[len]+1;
			else c[len]=b[len];
			for(int ii=1;ii<=len;ii++)c[ii]%=10;
			if(chk())cout<<j<<"  ";
		}
		cout<<endl;
	}
	return 0;
}
```

打表发现：对于第 $k$ 位，若这一位大于等于 $5$ 的话，就将第 $k-1$ 位减去 $1$。最后还要通过第 $n$ 位特判一下第 $1$ 位。注意：若产生退位，即减完之后为 $-1$ 的状态，应当做 $9$ 处理。

但是有一些特殊情况：根据打表可得，这些情况为数字仅有 $5$ 和 $0$ 组成，要进行分类讨论。若所有数和为 $10$ 的倍数，则答案为 $n$ 个 $9$。否则答案为 $n$ 个 $0$。

```cpp
int a[1000100];
int n;
int t[1000100];
bool chk(int l,int r,int x){
	for(int i=l;i<=r;i++){
		if(a[i]!=x)return 0;
	}
	return 1;
}
signed main(){
//	free();
    n=read();
    bool all=1;
    bool all50=1;
    for(int i=1;i<=n;i++){
		t[i]=a[i]=read();
		if(a[i]>=5)all=0;
		if(a[i]!=5 && a[i]!=0)all50=0;
	}
	if(all){
		for(int i=1;i<=n;i++){
			print(a[i]);
		}
		exit(0);
	}
	if(all50){
		int sum=0;
		for(int i=1;i<=n;i++)sum+=a[i];
		if(sum%10==0){
			for(int i=1;i<=n;i++)print(9);
			exit(0);
		}else{
			for(int i=1;i<=n;i++)print(0);
			exit(0);
		}
	}
	if(a[1]==5 && a[2]<5){
		a[n]--;
		for(int i=n;i>=1;i--){
			if(a[i]<0){
				a[i]=9;
				a[i-1]--;
			}
		}
		for(int i=1;i<=n;i++)print(a[i]);
    	exit(0);
	}
    for(int i=n-1;i>=1;i--){
        if(a[i+1]>=5)a[i]--;
        if(a[i]==-1)a[i]+=10;
    }
    if(a[1]>=5)a[n]--;
    if(a[n]<0)a[n]+=10;
    for(int i=1;i<=n;i++)cout<<a[i];
	return 0;
}
```

---

## 作者：LG086 (赞：1)

要你求所有可能的答案的和。记答案之和为 $ans$。

因为 $a = 0.\dot{a_1}a_2\dots\dot{a_n}$，所以四舍五入到 $a_n$ 这一位时是否要进位取决于 $a_{n+1}$ 即 $a_1$ 的值。

分类讨论 $a_1$ 是否大于等于 $5$。  
情况一是 $a_1 \ge 5$，所以记 $op=1$，从 $b_n$ 遍历到 $b_1$，对于每个 $b_i$，有 $a_i=(b_i-op+10)\mod 10$，同时更新 $op$。如果 $a_i \ge 5$，则 $op=1$；否则 $op=0$。得到 $a_1$ 后，判断 $a_1$ 是否大于等于 $5$，如果是，则此时的 $a$ 是一种方案。  
情况二是 $a_1 \le 4$，所以记 $op=0$，具体操作同上。得到 $a_1$ 后判断 $a_1$ 是否小于等于 $4$，如果是，此时的 $a$ 也是一个可行方案。

求出所有可行方案并求和，将这个和输出即可。

核心代码如下。

```cpp
//op = 0
op = 0;
for(int i = n;i >= 1;i --){
 a[i]=(b[i]-op+10)%10;
 if(a[i]>=5)op=1;
 else op=0;
}
if(a[1]<=4){
 for(int i = 1;i <= n;i ++)
  ans[i]+=a[i],a[i]=0;
}
//op = 1
op = 1;
for(int i = n;i >= 1;i --){
 a[i]=(b[i]-op+10)%10;
 if(a[i]>=5)op=1;
 else op=0;
}
if(a[1]>=5){
 for(int i = 1;i <= n;i ++)
  ans[i]+=a[i],a[i]=0;
}
```

---

## 作者：lzh301 (赞：1)

# Solution
题目要求求出四舍五入前的数字，乍一看很难实现，所以先简化一下，考虑不是循环小数的话怎么做，发现只要从后往前过一遍就可以了。

```cpp
for(int i=n-1;i>=1;i--){
	if(a[i+1]>=5){
		a[i]--;
	}
}
```
接下来考虑是循环小数的话该怎么做。\
首先，每一位四舍五入后只有两种情况，加一或不变。因此可以开数组分别存两种情况，将 $a_1$ 的两种情况存到 $a_{n+1}$ 中，再分别从后往前跑一次，若 $a_1 \ne a_{n+1}$ 则这种情况不可行，否则可行，作为答案相加。最后再注意一下小于零和进位的问题即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[1000010][3];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i][0];
		a[i][1]=a[i][0];
		a[i][2]=a[i][0];
	}
	a[n+1][1]=a[1][0]-1;
	a[n+1][1]=(a[n+1][1]+10)%10;
	a[n+1][2]=a[1][0];
	for(int i=n;i>=1;i--){
		if(a[i+1][1]>=5){
			a[i][1]-=1;
			a[i][1]=(a[i][1]+10)%10;
		}
		if(a[i+1][2]>=5){
			a[i][2]-=1;
			a[i][2]=(a[i][2]+10)%10;
		}
	}
	if(a[1][1]!=a[n+1][1])for(int i=1;i<=n+1;i++)a[i][1]=0;
	if(a[1][2]!=a[n+1][2])for(int i=1;i<=n+1;i++)a[i][2]=0;
	int f=0;
	for(int i=1;i<=n;i++)if(a[i][1]!=a[i][2])f=1;
	if(!f){
		for(int i=1;i<=n;i++)cout<<a[i][1];
		return 0;
	}
	for(int i=n+1;i>=1;i--)a[i][0]=0;
	for(int i=n;i>=1;i--){
		a[i][0]+=(a[i][1]+a[i][2]);
		if(a[i][0]>=10){
			a[i-1][0]++;
			a[i][0]-=10;
		}
	}
	for(int i=1;i<=n;i++)cout<<a[i][0]; 
}
```

---

## 作者：weiyiqian (赞：0)

首先，很容易发现所有可能的 $a$ 之和乘以 $10^n-1$ 就是一个循环节上所有可能答案之和。

因为四舍五入，所以 $a_i$ 要么是 $b_i$ 要么是 $(b_i-1)\bmod10$。若确定了 $a_i$ 的值，那么它进不进位也是确定的，自然 $a_{i-1}$ 就能确定下来了。也就是说，只要确定了 $a$ 的某一位数，就能确定这个循环节的数。综上所述，答案最多只有两种。

所以我们可以枚举 $a_n=b_n$ 和 $a_n=(b_n-1)\bmod10$ 的情况，分别递推求出 $a_1$ 后看 $a_1$ 和 $a_n$ 是否满足四舍五入的关系，若满足则记录答案，最后再把两种方案加起来。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,b[N],s1[N],s2[N];
int dp(int x,int s[]){
    s[n]+=x;
    for(int i=n-1;i>=1;i--){
        x=(b[i]-(x>=5)+10)%10;
        s[i]+=x;
    }
    return x;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>b[i];
    if(dp(b[n],s1)>=5){
        for(int i=1;i<=n;i++) s1[i]=0;
    }
    if(dp((b[n]+9)%10,s2)<5){
        for(int i=1;i<=n;i++) s2[i]=0;
    }
    for(int i=1;i<=n;i++) cout<<s1[i]+s2[i];
    return 0;
}
```

---

## 作者：zhoumurui (赞：0)

### 题面展示

有一个循环节长度为 $n$ 的纯循环小数，它可以表示为 $a = 0.\dot{a_1}a_2\dots\dot{a_n}$。

给你 $n$ 个数 $b_1, b_2, \dots, b_n$，其中 $b_i$ 表示将 $a$ 四舍五入到小数点后 $i$ 位后第 $i$ 位的值。

DerrickLo 请你帮忙计算出所有可能的 $a$ 的值，将它们求和后**乘以 $10^n - 1$** 输出。

可以证明，答案的位数不超过 $n$，**若不到 $n$ 位，设答案位数为 $k$，请先输出 $n-k$ 个前导零再输出答案。**

### 前置知识

**艾弗森括号**：

令 $P$ 为一个命题，那么 $[P] = \left\{\begin{aligned} 1 \space (P \text{ 是一个真命题}) \\ 0 \space (P \text{ 是一个假命题}) \end{aligned}\right.$。

例如，如果 $x=5$，那么 $[x \ge 4] = 1$，并且 $[2 \times x - 1\le 8] = 0$。

### 解题思路

为了防止讨论，令 $a_{n+1} = a_1$，$b_{n+1} = b_1$。

考虑 $b_i$ 的定义式：

---

**定义** $b_i = (a_i + [a_{i+1} \ge 5])\bmod 10$。

---

这可以导出两个结论：

---

**命题** $1$ 下面的式子对于 $i \in {1,2,\dots,n}$ 成立：

$$b_i \in \{a_i,(a_i+1)\bmod 10\} $$

**证明** 由 $[a_{i+1} \ge 5] \in \{0,1\}$ 易证。

---

**命题** $2$ 下面的式子对于 $i \in {1,2,\dots,n}$ 成立：

$$ b_{i+1} \in \{1,2,3,4\} \to a_i = b_i$$

$$ b_{i+1} \in \{6,7,8,9\} \to a_i = (b_i+9)\bmod 10$$

**证明** 由**定义**和**命题** $1$ 不难证得。

---

那么我们只剩下满足 $b_{i+1} \in \{0,5\}$ 的 $a_i$ 还没有求得。

---

**变式** $1$ 下面的式子对于 $i \in \{1,2,\dots,n\}$ 成立：

$$a_i = (b_i - [a_{i+1} \ge 5] +10)\bmod 10$$。

**证明** 将**定义**变形一下即得。

---

利用**变式** $1$，**只要我们求得了一个 $a_i$，我们就可以求出所有的 $a_i$**。看来多数情况下答案是唯一的。

只剩下一种情况：满足 $\forall i \in {1,2,\dots,n}$，$b_i \in \{0,5\}$ 的情况。**不满足这个情况的一定有唯一解，直接输出就好了。**

---

**变式** $2$ 下面的式子对于 $i \in \{1,2,\dots,n\}$ 成立：

$$a_i \in \{b_i,(b_i+9)\bmod 10\} $$

**证明** 将**命题** $1$ 变形一下即得。

---

考虑我们刚才所说：**只要我们求得了一个 $a_i$，我们就可以求出所有的 $a_i$**。那么我们利用变式 $2$，选择一个 $i$（为图简便，我的代码中选择 $i=n$）并枚举 $a_i$ 的 $2$ 种情况，将合法的情况计入答案。

合不合法只需要用**定义**验算一遍就可以了。

---

为什么答案可能有两种或者零种？

就 $\forall i \in {1,2,\dots,n}$，$b_i \in \{0,5\}$ 的情况，**不难理解可能上述的两种方案都是可行的。**

由于 $a_1,a_2,\dots,a_n$ 与 $b_1,b_2,\dots,b_n$ 的总量都是 $10^n$，并且有 $a_1,a_2,\dots,a_n$ 可以确定唯一的 $b_1,b_2,\dots,b_n$，

所以既然有 $b_1,b_2,\dots,b_n$ 对应两个 $a_1,a_2,\dots,a_n$，那么必然有 $b_1,b_2,\dots,b_n$ 无法对应任何 $a_1,a_2,\dots,a_n$ 的可能，即无解。

打个表也可以理解这个问题。对于 $n=3$，

$$(a_1,a_2,a_3) = (4,9,5) \to (b_1,b_2,b_3) = (5,0,5)$$

$$(a_1,a_2,a_3) = (5,0,4) \to (b_1,b_2,b_3) = (5,0,5)$$

而 $(b_1,b_2,b_3) = (5,5,5) \to \text{无解}$。

### 核心代码展示

```cpp
int n,a[1000005],b[1000005],c[1000005];
signed main(){
    cin>>n;
    for (int i=1;i<=n;i++)cin>>b[i];
    //b[i]=k:a[i]=k&&a[i+1]<=4   ||   a[i]=k-1&&a[i+1]>=5
    memset(a,-1,sizeof(a));
    for (int i=1;i<=n;i++){
        if (b[i==n?1:i+1]>=1&&b[(i==n?1:i+1)]<=4)a[i]=b[i];
        else if (b[(i==n?1:i+1)]>=6)a[i]=(b[i]==0?9:b[i]-1);
    }
    for (int i=n;i>=1;i--){
        if (a[i]!=-1)continue;
        if (a[i==n?1:i+1]>=5)a[i]=(b[i]==0?9:b[i]-1);
        else if (a[i==n?1:i+1]>=0)a[i]=b[i];
    }
    for (int i=n;i>=1;i--){
        if (a[i]!=-1)continue;
        if (a[i==n?1:i+1]>=5)a[i]=(b[i]==0?9:b[i]-1);
        else if (a[i==n?1:i+1]>=0)a[i]=b[i];
    }
    int flag=0;
    for (int i=1;i<=n;i++){
        if (a[i]==-1)flag=1;
    }
    if (flag){
        a[n]=b[n];
        for (int i=n;i>=1;i--){
            if (a[i]!=-1)continue;
            if (a[i==n?1:i+1]>=5)a[i]=(b[i]==0?9:b[i]-1);
            else if (a[i==n?1:i+1]>=0)a[i]=b[i];
        }
        for (int i=n;i>=1;i--){
            if (a[i]!=-1)continue;
            if (a[i==n?1:i+1]>=5)a[i]=(b[i]==0?9:b[i]-1);
            else if (a[i==n?1:i+1]>=0)a[i]=b[i];
        }
        if (a[1]<=4){
            for (int i=1;i<=n;i++)c[i]+=a[i];
            //cout<<"\n";
        }
        memset(a,-1,sizeof(a));
        a[n]=(b[n]==0?9:b[n]-1);
        for (int i=n;i>=1;i--){
            if (a[i]!=-1)continue;
            if (a[i==n?1:i+1]>=5)a[i]=(b[i]==0?9:b[i]-1);
            else if (a[i==n?1:i+1]>=0)a[i]=b[i];
        }
        for (int i=n;i>=1;i--){
            if (a[i]!=-1)continue;
            if (a[i==n?1:i+1]>=5)a[i]=(b[i]==0?9:b[i]-1);
            else if (a[i==n?1:i+1]>=0)a[i]=b[i];
        }
        if (a[1]>=5){
            for (int i=1;i<=n;i++)c[i]+=a[i];
        }
        for (int i=1;i<=n;i++){
            cout<<c[i];
        }
        return 0;
    }
    for (int i=1;i<=n;i++){
        cout<<a[i];
    }
    return 0;
}
```

---

## 作者：ztd___ (赞：0)

提供一种超级无脑的做法。

容易发现，只要我们已经知道了**任意一位**上真实的数字是什么，我们进而就可以去推出来前面一位是否是『五入』，也就相当于知道了前面一位是什么数。从而就可以推出**一整个循环节**。

对于每一个数，虽然我们不知道它是否被『五入』了，但是考虑到它要么是『五入』，要么是『四舍』。即 $a_i = b_i$ 或 $a_i = b_i - 1$。

反正只有两种情况，分类讨论太麻烦。我们直接把两种情况试一遍！

对于每种情况，一轮推完，发现和我们一开始所钦定的并没有矛盾，就说明这种情况是对的，就把答案统计一下。

又因为我们只需要知道任意一个，所以直接取 $i = 1$，然后令 $a_1 = b_1$ 或 $a_1 = b_1 - 1$ 再推即可。

注意判断减的时候 $b_i$ 是不是 $0$，$0$ 减 $1$ 要变成 $9$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 66;
int n, p = 1, b[N], a[N], c[N];
int l(int x) { return x == 1 ? n : x - 1; }
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> b[i];
	a[p] = b[p], c[p] = (b[p] == 0 ? 9 : b[p] - 1);
	do {
		if (0 <= a[p] && a[p] <= 4) a[l(p)] = b[l(p)];
		else a[l(p)] = (b[l(p)] == 0 ? 9 : b[l(p)] - 1);
		if (0 <= c[p] && c[p] <= 4) c[l(p)] = b[l(p)];
		else c[l(p)] = (b[l(p)] == 0 ? 9 : b[l(p)] - 1);
		p = l(p);
	} while (l(p) != 1);
	int x = 0, y = 0;
	if (0 <= a[p] && a[p] <= 4) x = b[l(p)];
	else x = (b[l(p)] == 0 ? 9 : b[l(p)] - 1);
	if (0 <= c[p] && c[p] <= 4) y = b[l(p)];
	else y = (b[l(p)] == 0 ? 9 : b[l(p)] - 1);
	if (x == a[1] && y == c[1]) for (int i = 1; i <= n; i++) cout << a[i] + c[i];
	else if (x == a[1]) for (int i = 1; i <= n; i++) cout << a[i];
	else if (y == c[1]) for (int i = 1; i <= n; i++) cout << c[i];
	else for (int i = 1; i <= n; i++) cout << 0;
	return 0;
}
```

---

