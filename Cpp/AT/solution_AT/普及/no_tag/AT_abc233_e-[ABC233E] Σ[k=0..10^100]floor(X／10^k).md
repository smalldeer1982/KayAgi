# [ABC233E] Σ[k=0..10^100]floor(X／10^k)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc233/tasks/abc233_e

$ \displaystyle\ \sum_{k=0}^{10^{100}}\ \left\ \lfloor\ \frac{X}{10^k}\ \right\ \rfloor $ を求めてください。

## 说明/提示

### 注釈

$ \lfloor\ A\ \rfloor $ は、 $ A $ の小数点以下を切り捨てた値を指します。

### 制約

- $ X $ は整数
- $ 1\ \le\ X\ <\ 10^{500000} $

### Sample Explanation 1

求める値は、 $ 1225+122+12+1+0+0+\dots+0=1360 $ となります。

### Sample Explanation 2

繰り上がりに注意してください。

### Sample Explanation 3

入力される値も出力すべき値も非常に大きくなる場合があります。

## 样例 #1

### 输入

```
1225```

### 输出

```
1360```

## 样例 #2

### 输入

```
99999```

### 输出

```
111105```

## 样例 #3

### 输入

```
314159265358979323846264338327950288419716939937510```

### 输出

```
349065850398865915384738153697722542688574377708317```

# 题解

## 作者：CSPJ10pts (赞：4)

## 题意：

给出一个整数 $x$，计算 $\sum^{10^{100}}_{k=0}\lfloor \frac{x}{10^k}\rfloor$ 的值。

## 分析

其实题意是要你求 $\sum\limits_{i=1}^n\lfloor\frac{x}{10^{i-1}} \rfloor$，其中 $n$ 为 $x$ 的位数。虽然简单了一些，但还是看着觉得复杂。没事，我们列个竖式理解一下。

我们就拿样例一举例，题目要我们求：

```
 1225
  122
   12
+   1
```
即 $1360$。

这样，是不是就清晰多了呢？接下来我们来分析做法。

思路 $\tt1$：暴力算，时间复杂度 $O(n^2)$，可惜在这里会超时。

思路 $\tt2$：通过观察得到，这个竖式第 $k$ 位的数字就是 $\sum\limits_{i=1}^kx_i$（其中 $x_i$ 为 $x$ 的第 $i$ 位）然后在进位后得到的。看到这里，相信你就明白了。我们可以用前缀和来计算到第 $k$ 位的数字和，然后直接将统计前缀和的数组拿来高精进位，最后输出一下就好啦！时间复杂度只有 $O(n)$！


## 代码

```
#include <iostream>
using namespace std;
string s;
int sum[500001];
int main() {
    cin >> s;
    sum[0] = s[0] - '0'; // 统计第一位，防止后面前缀和时越界
    for (int i = 1; i < s.length(); i++) sum[i] = sum[i - 1] + s[i] - '0'; // 前缀和计算
    for (int i = s.length() - 1; i >= 1; i--) sum[i - 1] += sum[i] / 10, sum[i] %= 10; // 进位！
    for (int i = 0; i < s.length(); i++) printf("%d", sum[i]); // 输出~
    printf("\n"); // 结尾撒“花”给AT看，没这个“花”AT可能不让你过
    return 0;
}
```

[通过记录](https://www.luogu.com.cn/record/103407576)

---

## 作者：封禁用户 (赞：1)

看到这题的数据范围后，我们首先想到的是**高精度**。

高精度还是可以做的。

提交了这个代码：
```
# include <bits/stdc++.h>
using namespace std;
string x;
long long cnt;
vector<int> add(vector<int>& A, vector<int>& B){
    vector<int> C;
    int t = 0;
    for (unsigned long i = 0; i < A.size() || i < B.size(); i++) {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }

    if (t) C.push_back(1);
    return C;
}
inline void solve(vector<int>& A, vector<int>& B){
    if (cnt == x.size() + 1) {
        for (long i = A.size() - 1; i >= 0; i --) cout << A[i];
        return;
    }
    cnt++;
    vector<int> C = add(A, B);
    B.clear();
    for (long i = x.size() - cnt; i >= 0; i --) B.push_back(x[i] - '0');
    solve(C, B);
}
int main(){
    vector<int> A, B;
    cnt = 2;
    cin >> x;
    for (long i = x.size() - 1; i >= 0; i --) A.push_back(x[i] - '0');
    for (long i = x.size() - 2; i >= 0; i --) B.push_back(x[i] - '0');
    solve(A, B);
    return 0;
}
```
### But！
提交后会发现~~美丽善良可爱~~的 Time Lime Exceeded ！

所以我们得换一种思路。

* 分析一下题目，如下：

```
（假设 a 数组为最终的答案，方法从尾往前遍历）
  1  2  2  5
     1  2  2
        1  2
           1
——————————————————
  1  3  5  10 （每一列的数字和，我们就把它们存到 sum 数组里）
```


#### 注意事项：

1. $a$ 数组的每一位都是由当前位置的 列数字和与进制的和 $mod10$ ，即可写出如下代码:
```
a[ai ++] = (sum[i] + carry[i]) % 10;// ai是a的专有下标
```
2. $carry$ 数组的每一位是上一位列数字和与进制的和除以 $0$ 的商
```
if (i) carry[i - 1] = (sum[i] + carry[i]) / 10;//由于i是0的时候carry[i - 1]就会超界，需特判
```

3. 对于 `(i == 0)` 时需要的特判，如下:
```
if (carry[0] != 0 && carry[0] < 10) a[ai ++ ] = carry[0];
```
注：$a$ 数组存的时候是**倒着存**的，所以我们也要**倒着**输出。


代码：
```
# include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main(){
    string x;
    cin >> x;
    int N = x.size() + 2;
    LL sum[N], carry[N];
    memset(sum, 0, sizeof sum);
    memset(carry, 0, sizeof carry);
    for (int i = x.size(); i > 0; i -- ) x[i] = x[i - 1];
    int a[N];
    int sum1 = 0;
    for (int i = 1; i <= x.size(); i ++ ){
        sum1 += (x[i] - '0');
        sum[i] = sum1;
    }
    int ai = 0;
    for (int i = x.size(); i > 0; i -- )
    {
        a[ai ++ ] = (sum[i] + carry[i]) % 10;
        if (i) carry[i - 1] = (sum[i] + carry[i]) / 10;
    }

    if (carry[0] != 0 && carry[0] < 10) a[ai ++ ] = carry[0];
    for (int i = ai - 1; i >= 0; i -- ) cout << a[i];
    cout << endl;
    return 0;
}
```

Accepted 了。

------
上一次审核：
> 很遗憾，您上传的题解 [ABC233E] Σ[k=0..10^100]floor(X／10^k) 题解 未能通过审核。原因是 所有数学符号、常数、作为变量的字母、运算符、数学推导过程应使用 LaTeX 公式；「公式/英文/数字」与「汉字」之间应当加空格

上述问题已修正，求通过~

---

## 作者：Tooler_Yang (赞：1)

这道题目**本来**是一个朴素的高精问题，只需要把这个数不断地除以10，最后把所有的商包括它本身加在一起就可以了。

[代码](https://www.luogu.com.cn/paste/pj544le0)

但是最后却超时了。

让我们再看看数据范围：$1\le x\le 10^{100000}$

也就是说这个数一共有 $10^5$ 位，然而高精度除法的复杂度是 $O(n^2)$，所以会超时。

---
那我们来观察一下原来的式子：

$\sum^{\infty}_{k=0}\lfloor \frac{x}{10^k}\rfloor$

$=\sum^{\infty}_{k=0}\frac{x}{10^k}-\sum^{\infty}_{k=0}\frac{x\; mod\; 10^{k}}{10^k}$

$=\sum^{\infty}_{k=0}\frac{x}{10^k}-\sum_i\sum^{\infty}_{k=0}\frac{x_i}{10^k}$

$=\frac{10x}{9}-\sum_i\frac{x_i}{9}$

意思就是说我们只要求这个数的10倍再减去这个数的每一位的和，最后再除以9。

那就很简单了，~~虽然但是我是用PyPy3写的~~。

代码如下：

```PyPy3
X=input()
S=sum(int(a) for a in X)
print((int(X)*10-S)//9)
```

AC[记录](https://atcoder.jp/contests/abc233/submissions/36113012)

---

## 作者：LiJinLin_AFO (赞：1)

# AT_abc233_e 题解

这题过于~~逊~~

## 正文开始

看看数据范围，不知道大家是否被震惊到。这可是 $10^{500000}$ 啊！！！这不是一般的数据结构可以存储的。像某些蒟蒻，懒得看，直接跳过。这可不是一个好习惯。

那么......怎么办呢？

高精度！

的确是一个好主意。

存储解决了，那么怎么计算呢？显然，这么大的数据范围，一定会超时。所以，我们应当去除不必要的计算。设 $num$ 为数据位数，$other$ 为大于 $num$ 的数，$\displaystyle \lfloor \frac{x}{10^{other}} \rfloor$ 一定为 $0$，可以忽略不计。所以，直接计算 $\displaystyle \sum _ {i=1}^{num} \lfloor \frac{x}{10^i} \rfloor$ 即可。

由于 $1 < x \le 10^{500000}$，所以 $num \le 5 \times 10^5$，可以通过。

接下来的操作，可以这么理解：
```cpp
int x;
int sum=0;
while(x){
   sum+=x;
   x/=10;
}
//sum为最终结果
```
直接暴力即可。上代码：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
char s[500055];
int a[500055],sum[500055];
int main(){
	cin>>s;
	int len=strlen(s);
	sum[0]=s[0]-'0';
	for(int i=1;i<len;i++) sum[i]=sum[i-1]+s[i]-'0';
	for(int i=0;i<len;i++){
		a[len-i]=sum[i];
	}//以上为输入、存储高精度，并且初始化
	int i;
	for(i=1;;i++){
		if(i>=len&&a[i]<10) break;
		a[i+1]+=a[i]/10;
		a[i]%=10;
	}//计算结果
	for(int j=i;j>0;j--) cout<<a[j];//输出
	return 0;
}
```
注：请勿抄袭！

---

## 作者：__delta_epsilon__ (赞：0)

### 题目大意

如题目标题所说，求下式的值。

$$\sum_{k=0}^{10^{100}}\left\lfloor\dfrac{X}{10^{k}}\right\rfloor$$

### 思路分析

鉴于 $1\le X<10^{500,000}$，用普通的 `int`，`long long`，`__int128` 都是过不去的，一眼就是高精度。

我们先来看一下这个东西到底是怎么算的，以 $1225$ 为例。

$$1225+122+12+1$$

可以发现，个位上的数 $1,2,2,5$ 之和为 $10$，十位上的数 $1,2,2$ 之和为 $5$，百位上的数 $1,2$ 之和为 $3$，千位上的数 $1$ 之和为 $1$。

不难发现，$10^{k}$ 位上的数字之和为前 $K-k$ 位数之和。（从左到右，$K$ 为总位数）

这不就是前缀和吗？

不难写出求前缀和的代码：

```cpp
sum[0] = s[0] & 15;
// 第一位的数值存在 sum[0]，这样在最后输出的时候就不需要调整了。
for(int i = 1; i <= s.size(); i++)
	sum[i] = sum[i - 1] + (s[i] & 15);
```

这里 `sum[i]` 最大值为 $499,999\times 9=4,499,991$，不会炸 `int` 上限。因为 ASCII 表中数字的码值为 $(30)_{16}\sim(39)_{16}$，所以按位与 $15$ 可以取出数字部分。

接下来，我们只需要解决进位的问题即可。

```cpp
for (int i = s.size() - 1; i >= 1; i--) {
	sum[i - 1] += sum[i] / 10;
	sum[i] %= 10;
}
```

其中，$i$ 为当前判断的位，第 $i$ 位除以 $10$ 的整数部分就是所要进位的部分。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
string s;
int sum[500002];

signed main() {
	cin >> s;
	sum[0] = s[0] & 15;
	for (int i = 1; i < s.size(); i++)
		sum[i] = sum[i - 1] + (s[i] & 15);
	for (int i = s.size() - 1; i >= 1; i--) {
		sum[i - 1] += sum[i] / 10;
		sum[i] %= 10;
	}
	for (int i = 0; i < s.size(); i++)
		cout << sum[i];
	return 0;
}
```

---

## 作者：CarlosLiu (赞：0)

## 题意描述
输入一个很长的数，要你求 $\sum _ {k = 0} ^ {10 ^ {100}}\lfloor \frac{x}{10 ^ {k}} \rfloor$ 这样一个很奇怪的式子。
## 解题思路
设 $l$ 为数的长度。化简可得，前面那个式子的第 $k$ 项其实就是输入的数的前 $l-k$ 项代表的数的值。

所以就可以用一个高精度。但是如果直接这样一项一项得相加，估计得超时。所以，观察到最后结果中的从右往左第i项加过了原来的从右往左第 $i$ 到 $l$ 项，可以直接用 $sum$ 数组快速算出。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
long long a[500009],b[500009],sum[5000009];
string s;
int main() {
	cin>>s;
	int l=s.length();
	for(int i=0;i<l;i++) a[i+1]=s[l-1-i]-'0';
	for(int i=l;i>=1;i--) {
		sum[i]=sum[i+1]+a[i];
	}
	for(int i=1;i<=l;i++) {
		b[i]+=sum[i];
		b[i+1]+=b[i]/10;
		b[i]%=10;
	}
	if(b[l+1]!=0) l++;
	for(int i=l;i>=1;i--) cout<<b[i];
	return 0;
}
```


---

## 作者：asas111 (赞：0)

## 思路
这题就是要求一个非常大的数一直除以 $10$ 再相加的结果，所以要用高精度。

用暴力去一次一次相加的时间复杂度为 $O(n^2)$，显然会超时。手算样例可以发现，没有进行进位操作的结果的第 $i$ 位就等于 它的第 $i-1$ 位再加上输入的数的第 $i$ 位。所以就可以考虑用前缀和去计算，最后再进位一下就可以了。

时间复杂度为 $O(n)$，可以通过此题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[500009];
int b[500009],c[500009];
int main(){
	cin>>a;
	int n=strlen(a);
	for(int i=0;i<n;i++)b[i+1]=a[i]-48;
	for(int i=1;i<=n;i++)c[i]=c[i-1]+b[i];
	for(int i=n;i>=1;i--)if(c[i]>=10)c[i-1]+=c[i]/10,c[i]%=10;
	int q=1;
	if(c[0])q=0;
	for(int i=q;i<=n;i++)cout<<c[i];
	return 0;
}
```


---

## 作者：liuyuanpei (赞：0)

### 本题大意：
给出一个整数 $x$，求出 $\sum_{k=0}^{10^{100}}\lfloor \frac{x}{10^k} \rfloor$。

当然，这个式子很难理解。但我们可以模拟一下样例：
 
样例1：$1225 + 122 + 12 + 1 = 1360$

样例2：$99999 + 9999 + 999 + 99 + 9 = 111105$

这样式子就很好理解了。

但是，$10^{500000}$ 肯定要用字符串读入，直接暴力是 $O(n^2)$ 的时间复杂度，会超时的。

所以，可以用类似竖式的思想来写，但要注意每一项之间的进位关系。

温馨提示：AtCoder 的题目最好加换行。

CODE：
```
# include <iostream>
# include <cmath>
# include <cstring>
# include <string>
# include <algorithm>
# include <stack>
# include <queue>
# include <set>
# include <map>
using namespace std;
char s[1000005];
int sum[1000005];
int main() {
    int cnt=1;//数字位数
    cin >>s;
    sum[0]=s[0]-'0';
    for (int i=1;s[i];i++) 
		sum[i]=sum[i-1]+s[i]-'0',cnt++;
    for (int i=cnt;i>0;i--) 
		sum[i-1]+=sum[i]/10,sum[i]%=10; //进位
    for (int i=0;i<cnt;i++) 
		cout <<sum[i];
    cout <<endl;//温馨提示
    return 0;
}
```


---

## 作者：chengning0909 (赞：0)

# abc 233 e

## 题意

请你求出 

$$\sum _ {k = 0} ^ {10 ^ {100}} \lfloor \frac {X} {10 ^ k} \rfloor$$

## 思路

首先，这道题目说是向下取整，所以如果输入是 `1234`，那么输出就是 `1234 + 123 + 12 + 1 = 1370`。

那么也就可以写成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/i3dg1tm1.png)

可以发现，最终答案的每一位其实就是对 $X$ 求了一遍前缀和。

最后再处理一次进位即可。

---

## 作者：loser_seele (赞：0)

去年场上吃了一车罚时的好提。

观察题目的柿子，发现实际上那个柿子是个摆设，只需要逐位讨论贡献即可。可以发现，第 $ i $ 位上的贡献实际上是可以简单计算的，如第一个样例中第 $ 4 $ 位的贡献实际上是 $ 1111 $，最后将所有贡献相加即可。

形式化地，对于第 $ i $ 位上的数字 $ j $，最后对答案的贡献为 $ j \times \sum\limits_{k=1}^i{10^k} $，这个可以直接用前缀和计算。得到前缀和数组之后直接处理进位即可。

本来准备写暴力高精除的但因为时间复杂度过大没法通过，也许有一天有 FFT 实现的高精度能卡过去吧。

时间复杂度 $ \mathcal{O}(len) $，其中 $ len $ 为输入的字符串长度，可以通过。

考场代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
long long sum[2000020];
string s;
int main()
{
	ios::sync_with_stdio(0);
	cin>>s;
	sum[0]=s[0]-'0';
	for(int i=1;i<s.length();i++)
	sum[i]=sum[i-1]+s[i]-'0';
	int top=0;
	for(int i=s.length()-1;i>=1;i--)
	sum[i-1]+=sum[i]/10,sum[i]%=10;
	for(int i=0;i<s.length();i++)
	cout<<sum[i];
}
```


---

