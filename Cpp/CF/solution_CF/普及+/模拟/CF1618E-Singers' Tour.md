# Singers' Tour

## 题目描述

$ n $ towns are arranged in a circle sequentially. The towns are numbered from $ 1 $ to $ n $ in clockwise order. In the $ i $ -th town, there lives a singer with a repertoire of $ a_i $ minutes for each $ i \in [1, n] $ .

Each singer visited all $ n $ towns in clockwise order, starting with the town he lives in, and gave exactly one concert in each town. In addition, in each town, the $ i $ -th singer got inspired and came up with a song that lasts $ a_i $ minutes. The song was added to his repertoire so that he could perform it in the rest of the cities.

Hence, for the $ i $ -th singer, the concert in the $ i $ -th town will last $ a_i $ minutes, in the $ (i + 1) $ -th town the concert will last $ 2 \cdot a_i $ minutes, ..., in the $ ((i + k) \bmod n + 1) $ -th town the duration of the concert will be $ (k + 2) \cdot a_i $ , ..., in the town $ ((i + n - 2) \bmod n + 1) $ — $ n \cdot a_i $ minutes.

You are given an array of $ b $ integer numbers, where $ b_i $ is the total duration of concerts in the $ i $ -th town. Reconstruct any correct sequence of positive integers $ a $ or say that it is impossible.

## 说明/提示

Let's consider the $ 1 $ -st test case of the example:

1. the $ 1 $ -st singer in the $ 1 $ -st city will give a concert for $ 3 $ minutes, in the $ 2 $ -nd — for $ 6 $ minutes, in the $ 3 $ -rd — for $ 9 $ minutes;
2. the $ 2 $ -nd singer in the $ 1 $ -st city will give a concert for $ 3 $ minutes, in the $ 2 $ -nd — for $ 1 $ minute, in the $ 3 $ -rd - for $ 2 $ minutes;
3. the $ 3 $ -rd singer in the $ 1 $ -st city will give a concert for $ 6 $ minutes, in the $ 2 $ -nd — for $ 9 $ minutes, in the $ 3 $ -rd — for $ 3 $ minutes.

## 样例 #1

### 输入

```
4
3
12 16 14
1
1
3
1 2 3
6
81 75 75 93 93 87```

### 输出

```
YES
3 1 3 
YES
1 
NO
YES
5 5 4 1 4 5```

# 题解

## 作者：Bbaka (赞：9)

根据题意，我们可以得出一个线性方程组：

$$a_1+na_2+(n-1)\times a_3+\cdots+2a_n=b_1$$

$$2a_1+a_2+na_3+\cdots+3a_n=b_2$$

$$3a_1+2a_2+a_3+\cdots+4a_n=b_3$$

$$\vdots$$

$$i\times a_1+(i+1) \times a_2+(i+2)\times a_3+\cdots+a_i+\cdots+(i-1) \times a_n=b_i$$

$$\vdots$$

$$na_1+(n-1)\times a_2+(n-2)\times a_3+\cdots+a_n=b_n$$

将这 $n$ 个方程加起来可以得到：

$$\dfrac{n^2-n}{2}\sum a_i = \sum b_i$$

两边同时除以 $\dfrac{n^2-n}{2}$ 可得：

$$\sum a_i = \dfrac{2}{n^2-n}\sum b_i$$

对于第 $i-1$ 个方程和第 $i$ 个方程，将他们相减可以得到：

$$-a_1- a_2-a_3+\cdots-a_{i-1}+(n-1)\times a_i+\cdots-a_n=b_{i-1}-b_i$$

将上式加上 $\sum a_i$ 得：

$$n \times a_i = \dfrac{2}{n^2-n}\sum b_i +b_{i-1}-b_i$$

最后两边同时除以 $n$，就得到了 $a_i$ 的值。

题目还要求判断答案是否存在，因为要求 $a_i$ 满足正整数，所以说若计算结果出现了负数或分数则答案不存在；此外在计算 $\sum a_i$ 时，若计算结果不为整数，也能说明答案不存在。

最终代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long n;
long long a[50009],b[50009];
int main () {
    cin>>t;
    while (t--) {
        cin>>n;
        long long sum=0;
        for (int i = 1; i <= n;++i) {
            cin>>b[i];
            sum+=b[i];
        }
        if (sum%(((1 + n) * n / 2))!=0) {
            cout<<"NO"<<endl;
            continue;
        }
        sum/=((1+n)*n/2);
        long long S=0;
        bool check=true;
        for (int i=2;i<=n;++i) {
            if ((b[i-1]-b[i]+sum)%n!=0||(b[i-1]-b[i]+sum)<=0)
                check=false;
            a[i]=(b[i-1]-b[i]+sum)/n;
        }
        if ((b[n]-b[1]+sum)%n!=0||(b[n]-b[1]+sum)<=0)
            check=false;
        a[1]=(b[n]-b[1]+sum)/n;
        if (check==false) {
            cout<<"NO"<<endl;
            continue;
        }
        cout<<"YES"<<endl;
        for (int i=1;i<=n;++i)
            cout<<a[i]<<" ";
        cout<<endl;
    }
    return 0;
}

```


---

## 作者：Running_a_way (赞：1)

萌萌推式子题。

因为 $a$ 序列的每一项对 $b$ 序列的贡献是等差数列，我们考虑对 $b$ 求一下差分。

根据定义，有 

$$
b_i - b_{i-1} = \sum_{j=1}^n{[j\neq i]a_j} + (1-n)a_i
$$

于是要是我们再知道 $\sum_{i=1}^{n} a_i$，就可以解个方程把 $a_i$ 算出来了。

考虑将所有的 $b_i$ 相加，有： 

$$
\sum_{i=1}^n b_i = \frac{n(n+1)}{2} \cdot \sum_{i=1}^n a_i
$$
除一下就可以算出所有 $a_i$ 的和了。然后枚举一下，把每个 $a_i$ 算出来就做完了。

注意判断除法是不是整除，以及每个解是否为正数什么的。

---

## 作者：Tzs_yousa (赞：1)

## 数列
先拿着样例手画，然后可以画出来几个等式，写成普适的就是：
$$ a_1 + na_2 + (n - 1)a_3 + ... + 2a_n = b_1 $$
$$2a_1 + (2 - 1)a_2 + na_3 + ... + 3a_n = b_2 $$
$$ ...$$
$$na_1 + (n - 1)a_2 + (n - 2)a_3 + ... + a_n = b_n $$
然后我就通过累加法（高中知识）求出了以下公式：
$$ \frac{(n + 1)n}{2} Sn = Tn $$
$Sn$ 就是 $a$ 的前 $n$ 项和， $Tn$ 就是 $b$ 数组的前 $n$ 项和。

然后把系数除到右边。
$$ Sn = \frac{2}{(n + 1)n} Tn $$
但是，不能直接写出下一项，然后用 $S_n - S_{n-1} = a_n$ 来求，这样求出来不是通项。

所以，就要另辟蹊径。

用 $b_n - b_{n - 1}$ ，然后会很开心的写出来这个式子。
$$ a_i = \frac{Sn - (b_i - b_{i - 1})}  {n}$$
欸好，这个是对的，然后求就行了。
但是要注意 $i \ge 2$ 。
然后代码就比较简单，判断不成立需要注意一下然后就没什么了。
```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXN = 4e4 + 10;
using namespace std;
int t, n, a[MAXN], Tn, b[MAXN];
signed main()
{
	scanf("%lld", &t);
	while(t--)
	{
		int fl = 1;
		Tn = 0;
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%lld", &b[i]);
			Tn += b[i]; 
		}
		if((Tn * 2) % (n * n + n) != 0)
		{
			printf("NO\n");
			continue;
		}
		int Sn = Tn * 2 / (n * n + n), p = Sn;
		for (int i = 2; i <= n; i++)
		{
			if((Sn - (b[i] - b[i - 1])) % n != 0 || (Sn - (b[i] - b[i - 1])) / n <= 0) //必须是<= 
			{
				fl = 0;
				break;
			}
			a[i] = (Sn - (b[i] - b[i - 1])) / n;
			if(a[i] <= 0) fl = 0;
			p -= a[i];
		}
		a[1] = p;
		if(a[1] == 0) fl = 0;
		if(fl == 1) 
		{
			printf("YES\n");
			for (int i = 1; i <= n; i++) printf("%lld ", a[i]);
		}
		else printf("NO\n");
		printf("\n");
	}
	return 0;
}
```


---

## 作者：YangXiaopei (赞：1)

## Solution:

根据题意我们可以列出这些式子。

$$a_1 + na_2 + (n - 1)a_3 + ... + 2a_n = b_1$$

$$2a_1 + a_2 + na_3 + ... + 3a_n = b_2$$

$$\vdots$$

$$n_a1 + (n - 1)a_2 + (n - 2)a_3 + ... + a_n = b_n$$

然后我们就发现，这不是解方程吗?

长达半个多小时的解方程，最后，我们得到了一个式子。

$$a_i = \frac{[(b_1 + b_2 + b_3 + ... + b_n) \div (n \times n + n)] - (b_i - b_{i - 1})}{n}$$

不可能的情况则是 $a_i$ 不是正整数。

按这个式子去算即可。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, k, sum1, sum2, b[40005], a[40005];
signed main(){
	cin >> t;
	while(t--){
		cin >> n;
		k = sum1 = sum2 = 0;
		for(int i = 1; i <= n; i++){
			cin >> b[i];
			sum1 += b[i];
			a[i] = 0;
		}
		if(n == 1){
			cout << "YES" << "\n" << b[1] << "\n";
			continue;
		}
		if((sum1 * 2) % (n * n + n) != 0){
			cout << "NO" << "\n";
			continue;
		}
		sum2 = (sum1 * 2) / (n * n + n);
		for(int i = 2; i <= n; i++){
			a[i] = sum2 - (b[i] - b[i - 1]);
			if(a[i] <= 0 || a[i] % n){
				k = 1;
				break;
			}
			a[i] /= n;
		}
		a[1] = sum2 - (b[1] - b[n]);
		if(a[1] <= 0 || a[1] % n){
			k = 1;
		}
		a[1] /= n;
		if(k){
			cout << "NO" << "\n";
			continue;
		}
		cout << "YES" << "\n";
		for(int i = 1; i <= n; i++){
			cout << a[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：20111019Yu (赞：1)

### 思路

干瞪着眼肯定是不行的，既然是构造题，难度还是绿的，大概率只有唯一解，有唯一解就肯定能通过某种方法直接求出来。

根据题意我们能知道：

$$\begin{cases}
b_{1}=a_{1}+n\times a_{2}+(n-1)\times a_{3}\cdots+2\times a_{n}\\
b_{2}=2\times a_{1}+a_{2}+n\times a_{3}\cdots+3\times a_{n}\\
\cdots\\
b_{n}=n\times a_{1}+(n-1)\times a_{2}+(n-2)\times a_{3}\cdots+a_{n}
\end{cases}$$

高斯消元的时间复杂度太高，所以我们观察这些算式有什么特殊性。

不难发现这是一个轮换式，将这些式子相加可得：

$$\sum_{i=1}^{n}b_{i}=\sum_{i=1}^{n}\frac{n\times (n+1)}{2}\times a_{i}$$
$$\sum_{i=1}^{n}a_{i}=\frac{\sum_{i=1}^{n}b_{i}}{\frac{n\times (n+1)}{2}}$$

由 $b_{i}-b_{i-1}$ 得：

$$b_{i}-b_{i-1}=(\sum_{i=1}^{n}a_{i})-n\times a_{i}$$

两式相减得：

$$n\times a_{i}=\frac{\sum_{i=1}^{n}b_{i}}{\frac{n\times (n+1)}{2}}-(b_{i}-b_{i-1})$$
$$a_{i}=\frac{\frac{\sum_{i=1}^{n}b_{i}}{\frac{n\times (n+1)}{2}}-(b_{i}-b_{i-1})}{n}$$

因为 $b$ 数组已知，所以能求出 $a$ 数组，若中间任何地方出现了小数或 $a_{i}$ 为非正数，则构造不出符合要求 $a$ 数组 `NO`。

否则输出 `YES` 并输出 $a$ 数组。

### code
```cpp
#include <bits/stdc++.h>
#define int long long\\好习惯
using namespace std;
int t, n, a[40005], b[40005];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);\\数据量有些大
	cin >> t;
	while(t--){
		int sum = 0;
		bool vis = 0;
		cin >> n;
		for( int i = 1; i <= n; i++ ) cin >> a[i];
		for( int i = 1; i <= n; i++ ) sum += a[i];\\求初始数组的总合
		if(sum % ((n + 1) * n / 2)){
			cout << "NO" << endl;
			continue;
		}
		sum = sum / ((n + 1) * n / 2);\\计算答案数组总和
		if(sum < n){
			cout << "NO" << endl;
			continue;
		}
		for( int i = 1; i <= n; i++ ){
			int lin = a[(i - 2 + n) % n + 1] - a[i] + sum;\\懒得特判情况
			if(lin % n || lin < 1 || lin > 1e9) vis = 1;
			b[i] = lin / n;\\计算答案数组
		}
		if(vis){
			cout << "NO" << endl;
			continue;
		}
		cout << "YES" << endl;
		for( int i = 1; i <= n; i++ ) cout << b[i] << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Tachibana27 (赞：0)

比较水的推柿子

------------

手玩样例不难发现：

$$\begin{cases} b_1=a_1+na_2+(n-1)a_3+...+2a_n \\ b_2=2a_1+(2-1)a_2+na_3+...+3a_n \\ ... \\ b_n=na_1+(n-1)a_2+(n-2)a_3+...+a_n  \end{cases}$$

肯定不能高斯消元因为~~我不会~~时间复杂度到了 $O(n^3)$，考虑瞪眼法解方程。

瞪眼后将其整理不难发现：

$$\sum \limits _{i=1}^{n} {b_{i}}=\sum \limits _{i=1}^{n} \sum \limits _{j=1}^{n}{a_{i}\times {}j}=\sum \limits _{i=1}^{n} a_i\frac{(n+1)n}{2}$$

移项后可得：

$$\sum \limits _{i=1}^{n} b_i \div \frac{(n+1)n}{2}=\sum \limits _{i=1}^{n} a_i$$

对 $b$ 做差分，发现：

$$b_{i}-b_{i-1}=(\sum \limits _{i=1}^{n} a_i)-a_i\times n$$

代入并移项：

$$a_i\times n=\sum \limits _{i=1}^{n} b_i \div \frac{(n+1)n}{2}-(b_i-b_{i-1})$$


解得：

$$a_i=\frac{\sum \limits _{i=1}^{n} b_i \div \frac{(n+1)n}{2}-(b_i-b_{i-1})}{n}$$

~~啊真是一场酣畅淋漓的解方程啊~~

随后用结论计算即可。

其中输出 `NO` 仅当 $a_i<0$ 或 $a_i$ 出现小数。

code：

```cpp
%:include<bits/stdc++.h>
inline int read()<%
	int s=0;
	int w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
	for(;ch>='0' and ch<='9';ch=getchar())
		s=s*10+ch-'0';
	return s*w;
%>

void write(int x)<%
	if(x<0)<%
   		putchar('-');
   		x=-x;
	%>
	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
%>//快读快写自动掠过，考虑到数据较大建议使用

int t;
int n;
double b[40086];
double a[40086];
signed main(){
	t=read();
	while(t--){
		double sum=0;
		n=read();
		bool flag=false;
		for(int i=1;i<=n;i++){
			b[i]=read();
			sum+=b[i];//统计bi之和
		}
		a[1]=(sum/(n*(n+1.00)/2.00)-(b[1]-b[n]))/n;//特别地计算a1
		for(int i=1;i<=n;i++){
			if(i!=1)
				a[i]=(sum/(n*(n+1.00)/2.00)-(b[i]-b[i-1]))/n;//可爱的结论
			if(ceil(a[i])!=a[i] or a[i]<=0){//骚操作，若取整与它本身大小不同就出现了小数
				flag=true;//打标记输出比较方便
				break;
			}
		}
		if(flag){
			puts("NO");
			continue;
		}
		else{
			puts("YES");
			for(int i=1;i<=n;i++){
				write(a[i]);
				std::cout<<" ";
			}
			puts("");
			continue;
		}
	}
	return 0;//撒花
}
```



---

## 作者：Vistarin (赞：0)

这里给出一个使用线性代数的解法。

原题等价于求下列矩阵的一个解：

$\begin{pmatrix}
1 & n & n-1 & n-2 & \cdots & 2 & b_1 \\
2 & 1 & n & n-1 & \cdots & 3 & b_2 \\
3 & 2 & 1 & n & \cdots & 4 & b_3 \\
4 & 3 & 2 & 1 & \cdots & 5 & b_4 \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots & \vdots \\
n & n-1 & n-2 & n-3 & \cdots & 1 & b_n
\end{pmatrix}$

为了化简，我们进行以下操作：

① 把矩阵的 $2\sim n$ 行加到第 $1$ 行上，并将第 $1$ 行除以 $k=n\times(n+1)/2$，
使得矩阵第一行全为 $1$;

② 对于所有 $i\in[2, n-1]$，依次将 $i$ 行减去 $i-1$ 行。

于是，矩阵化为：

$\begin{pmatrix}
1 & 1 & 1 & 1 & \cdots & 1 & (1/k)\Sigma b  \\
-1 & -1 & n-1 & -1 & \cdots & -1 & b_2-b_3 \\
-1 & -1 & -1 & n-1 & \cdots & -1 & b_3-b_4 \\
-1 & -1 & -1 & -1 & \cdots & -1 & b_4-b_5 \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots & \vdots \\
n & n-1 & n-2 & n-3 & \cdots & 1 & b_n
\end{pmatrix}$

再将第 $1$ 行加到 $2\sim n-1$ 行，得到：

$\begin{pmatrix}
1 & 1 & 1 & 1 & \cdots & 1 & (1/k)\Sigma b  \\
0 & 0 & n & 0 & \cdots & 0 & b_2-b_3 + (1/k)\Sigma b \\
0 & 0 & 0 & n & \cdots & 0 & b_3-b_4 + (1/k)\Sigma b \\
0 & 0 & 0 & 0 & \cdots & 0 & b_4-b_5 + (1/k)\Sigma b \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots & \vdots \\
n & n-1 & n-2 & n-3 & \cdots & 1 & b_n
\end{pmatrix}$

容易发现，对于 $i\in[2, n-1]$，有 $a_i=\Large\frac{b_{i-1}-b_i + (1/k)\Sigma b}{n}$。

由于各元素地位相等，该式对 $i=1$ 和 $i=n$ 也成立（对 $i=1$ 时有特殊形式 $a_1=b_n-b_1 + (1/k)\Sigma b$）。 

综上所述，当上述 $a_i$ 为正整数时，答案为 Yes，此时代入公式计算即可；反之，答案为 No。时间复杂度为 $O(n)$。

---

## 作者：45dinо (赞：0)

要满足如下限制：

$$\begin{cases}b_1=a_1+n\cdot a_2+\dots+2\cdot a_n\\b_2=2\cdot a_1+a_2+\dots+3\cdot a_n\\b_3=3\cdot a_1+2\cdot a_2+\dots+4\cdot a_n\\\dots\\b_n=n\cdot a_1+(n-1)\cdot a_2+\dots +a_n\end{cases}$$

如果直接高斯消元是 $\Theta(n^3)$ 的，无法通过。

所以不能暴力地去解，得研究一些规律。

可以发现 $\frac 1 2(n+1)\times n\times \sum a=\sum b$，进而算出 $\sum a$。

将 $b$ 中相邻的数进行差分，发现 $b_i-b_{i-1}=\sum a-n\cdot a_i$，所以可以直接求出所有 $a$ 的值。

---

