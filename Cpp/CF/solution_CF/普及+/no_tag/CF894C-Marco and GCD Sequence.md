# Marco and GCD Sequence

## 题目描述

### 题目大意

有一天$Macro$做梦梦见了一位戴着黑框眼睛的长者,那位长者告诉他长生不老的密匙, $Macro$还想继续追问,但那位长者只说了四个字"无可奉告".随即他就消失在时间之风中

Macro醒来后只记得密匙是一个长度为$N$的正整数序列$a_i$,但是他事先闷声发大财,计算了所有$gcd(a_i,a_{i+1}...a_j) (1<=i<=j<=n)$并且把结果放入单重集合$S$

注意如果一个元素被多次放入集合,它只会出现一次

因为你比$Macro$不知道高到哪里去,现在$Macro$给你一个集合$S$，要求你还原出密匙序列。如果有多种解,输出任意一种.如果这个集合太$naive$,不可能还原出一个序列，那么输出"-1"(没有引号)

## 样例 #1

### 输入

```
4
2 4 6 12
```

### 输出

```
3
4 6 12```

## 样例 #2

### 输入

```
2
2 3
```

### 输出

```
-1
```

# 题解

## 作者：Lynkcat (赞：5)

一道比较有意思的构造题。

首先可以想到如果 $S$ 里有 $1$ 那直接在每个元素中间插 $1$ 就能满足条件。

然后又想到如果 $S$ 里没有 $1$ 怎么办呢？可以让所有数都除以它们的 $gcd$ 。

如果这时候还没有 $1$ 出现显然我们无法构造出一种合法的方案，否则数组里有数互质，一定会出现 $1$ 这个元素。

接下来就没有问题了，注意除以 $gcd$ 之后还得乘回来。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>

using namespace std;

inline int read(){
    int x = 0; char ch = getchar(); bool positive = 1;
    for (; !isdigit(ch); ch = getchar())	if (ch == '-')	positive = 0;
    for (; isdigit(ch); ch = getchar())	x = x * 10 + ch - '0';
    return positive ? x : -x;
}
inline void write(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writesp(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
    printf(" ");
}
inline void writeln(int a){
    if(a<0){
    	a=-a; putchar('-');
    }
    write(a); puts("");
}

int M,_gcd,a[100005],bl;
vector<int>ans;

int gcd(int x,int y) {return (y==0)?x:gcd(y,x%y);}

signed main()
{
	M=read();
	for (int i=1;i<=M;i++) a[i]=read(),_gcd=gcd(a[i],_gcd);
	for (int i=1;i<=M;i++) a[i]/=_gcd;
	for (int i=1;i<=M;i++) bl|=a[i]==1;
	if (!bl) return writeln(-1),0;
	for (int i=1;i<=M;i++) ans.push_back(_gcd),ans.push_back(a[i]*_gcd);
	writeln(ans.size());
	for (int i=0;i<ans.size();i++) writesp(ans[i]);
}
```

---

## 作者：流绪 (赞：3)

题目大概讲的是有一个序列,任意取它的一个子序列(连续),求出子序列的 gcd 然后放入一个集合 S,现在给出 S 求原来的序列

一开始没啥思路,然后看到了 n<=1000,而序列长度却有 4000,难道要构造???

然后发现 S 的最小值一定是整个序列的 gcd,如果不是的话无解,如果是的话那么把最小值和 S 中的每一个值交替出现,那么无论怎么取子序列,它的 gcd 要么是最小值,要么是 S 中的一个值,这样子答案就出来了
```cpp
#include<bits/stdc++.h>
#define ll long long
#define maxn 1000010
#define inf 0x7f7f7f7f
#define mod 1000000007
using namespace std;
int s[10000];
int main()
{
	int m;
	cin >> m ;
	for(int i=1;i<=m;i++)
		cin >> s[i];
	int sum = s[m],cnt = 1;
	for(int i=m-1;i;i--)
		sum=__gcd(sum,s[i]);
	if(sum != s[1])
	{
		cout <<"-1";
		return 0;
	}
	cout << 2*m<<endl;
	for(int i=1;i<=m;i++)
		cout << s[1] << " " << s[i]<<" ";
	return 0;
}
```


---

## 作者：fmj_123 (赞：2)

非常有趣的~~思维体操~~构造题。

显然构造出来的序列不能出现**给出序列以外的数**，但是由于要求构造的数列可以是 $4$ 倍于原序列，我们可以重复至多 $4$ 次该序列的数。

现在直接给出一个构造方法：在原序列每个数后插入第一个数。即``s[1] s[2] s[1] s[3] s[1]...s[m]``

证明其正确性：

首先，要构造出该序列，原序列**必须满足对于 $1\le i \le m$，$s_i$ 是 $s_1$ 倍数**。

因为 $s_1$ **一定**是整个序列的GCD，否则 $s_1$ 必定无法是序列中任何一段的GCD。

那么，整个序列**必定**是 $s_1$ 的倍数。若存在一个 $s_i$ 不是 $s_1$ 的倍数，则若存在这个序列，其中一段的GCD不是 $s_1$ 的倍数，根据GCD的性质，这一段数向左，向右伸展，其GCD也必然不是 $s_1$ 的倍数，那么整个序列的GCD一定不是 $s_1$。与上面矛盾，不成立。若出现这种情况，输出 ``-1`` 即可。

根据此性质，按照我们的构造方法，单一一个数的GCD是其本身，多个数由于 $s_1$ 的存在，其GCD必定为 $s_1$，符合题意。

上代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[1500];
int gcd(int x,int y)
{
	if (!y) return x;
	return gcd(y,x%y);
}
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];
		if (gcd(a[i],a[1])!=a[1]) 
		{
			cout<<"-1\n";
			return 0;
		}
	}
	cout<<2*n-1<<endl;
	cout<<a[1]<<" ";
	for (int i=2;i<=n;i++) cout<<a[i]<<" "<<a[1]<<" ";
	return 0;
}
```

---

## 作者：_6_awa (赞：1)

一道比较水的题目。

在首项等于 $1$ 的时候，我们可以在每一个位置插一个数 $1$，这样，除了自己取最大公约数之外，其余任意 $l,r$ 的计算结果都包含 $1$，就满足条件了。

但是很显然样例首项是 $2$ 也能过。为什么呢？因为所有数都能被 $2$ 整除，这样像上面那样插空，$l,r$ 的计算结果也就至少为 $2$ 了。所以，当数列里所有数都能整除第一个数时，就满足条件，直接输出插空后的数列即可。

那么没有被整除怎么办呢？很简单。因为如果不会被整除，那么它们两个的最大公约数一定小于最小的数。这时候你只能用两个较大的数的倍数去代替，但是因为质因子相同，即 $[2,3]$ 变成 $[2,6,9]$，但是不管怎样取，总有一个数不是 $2$ 的倍数。所以自然而然就无解了。

理清楚了的话，代码就很简单了。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[1005],n;
int main()
{
    cin >> n;
    for(int i = 1;i <= n;i ++)cin >> a[i];
    for(int j = 2;j <= n;j ++)
        if(__gcd(a[1],a[j]) != a[1])//如果整除不了无解
        {
            cout << -1;
            return 0;
        }
    cout << n * 2 << "\n";
    for(int i = 1;i <= n;i ++)cout << a[1] << " " << a[i] << " ";//插空并输出
}

---

## 作者：Special_Tony (赞：0)

# 思路
我们设 $g=\gcd(a_1,a_2,a_3,\dots,a_n)$，然后我们只要构造一个类似 $g,a_1,g,a_2,g,a_3,\dots,g,a_n$ 就行了，长度 $2\times n$（反正限制只有 $4000$，够用了）。另外如果 $g$ 不在 $a$ 里就是无解。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, a[1005], g;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
		cin >> a[i], g = __gcd (g, a[i]);
	for (int i = 0; i < n; ++ i)
		if (a[i] == g)
			goto there;
	cout << "-1";
	return 0;
there:
	;
	cout << n * 2 << '\n';
	for (int i = 0; i < n; ++ i)
		cout << g << ' ' << a[i] << ' ';
	return 0;
}
```

---

## 作者：Acerkaio (赞：0)

### 题意简述：

一个坤合 $S$ 是原正整数序列 $a_i$ 所有的 $\gcd(a_i, a_{i+1}, ..., a_j) (1 \le i \le j \le n)$，求原正整数序列。

### 思路

构造题，我们能发现一个简易的结论，如果有解坤合 $S$ 中的所有数的最大公坤数是序列中最小的那个数，否则无解。

那么我们就想到可以构造这样一个序列：$a_1$ 和 $a_i$ 交错输出，这样创建的 $S$ 就只能是 $a_1$ 或 $a_i$，符合题意。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
int sum, s[1000001];
signed main() {
  int m;
  cin >> m;
  for (int i = 1; i <= m; i++)
    cin >> s[i];
  sort(s + 1, s + m + 1);
  sum = s[m];
  for (int i = m - 1; i; i--) {
    sum = __gcd(sum, s[i]);
  }
  if (sum != s[1]) {
    cout << "-1\n";
    return 0;
  }
  cout << 2 * m << '\n';
  for (int i = 1;  i<= m; i++) {
    cout << s[1] << " " << s[i] << ' ';
  }
  cout << '\n';
  return 0; 
}

```


---

## 作者：XL4453 (赞：0)

### 解题思路：

由于这样的一个区间长度可以等于一，那么每一个在构造序列中出现的数都一定在最大公约数序列中出现过，否则一定会有其他的数出现在最大公约数中。

发现，这些最大公约数中最小的一个数一定是整个序列的最大公因数，也就是这个序列的每一个数都要被这个数整除。否则直接取所有的数取一个最大公约数就不符合题意了。

然后构造这样的一个序列，考虑直接在每一个数中间插一个最小的最大公约数。这样，由于每一个数都在序列中出现过，所以不会有遗漏的情况发生，而又因为每一个数中间都有一个最小数存在，也不可能出现别的数。所以这样的一种构造方法是一定可行的。

--------
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n,a[1005];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	for(int i=2;i<=n;i++){
		if(a[i]%a[1]!=0){
			printf("-1");
			return 0;
		}
	}
	printf("%d\n" ,n*2);
	for(int i=1;i<=n;i++){
		printf("%d %d ",a[i],a[1]);
	}
	printf("\n");
	return 0;
}
```


---

