# Two Arrays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/apc001/tasks/apc001_b

長さ $ N $ の数列 $ a_1,a_2,..,a_N $ と $ b_1,b_2,..,b_N $ が与えられます。 以下の操作を $ 0 $ 回以上好きなだけ繰り返して、数列 $ a $ と $ b $ を一致させられるか判定してください。

操作： $ 1 $ 以上 $ N $ 以下の整数 $ i,j $ (一致していてもよい)を選び、次の2つのことを**同時に**行う。

- $ a_i $ に $ 2 $ を足す
- $ b_j $ に $ 1 $ を足す

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 10,000 $
- $ 0\ <\ =\ a_i,b_i\ <\ =\ 10^9 $ ($ 1\ <\ =\ i\ <\ =\ N $)
- 入力は全て整数

### Sample Explanation 1

例えば、次のように $ 3 $ 回操作すればよいです。 - $ 1 $ 回目： $ i=1,j=2 $. これによって $ a\ =\ \{3,2,3\} $, $ b\ =\ \{5,3,2\} $ となります。 - $ 2 $ 回目： $ i=1,j=2 $. これによって $ a\ =\ \{5,2,3\} $, $ b\ =\ \{5,4,2\} $ となります。 - $ 3 $ 回目： $ i=2,j=3 $. これによって $ a\ =\ \{5,4,3\} $, $ b\ =\ \{5,4,3\} $ となります。

## 样例 #1

### 输入

```
3
1 2 3
5 2 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5
3 1 4 1 5
2 7 1 8 2```

### 输出

```
No```

## 样例 #3

### 输入

```
5
2 7 1 8 2
3 1 4 1 5```

### 输出

```
No```

# 题解

## 作者：TRZ_2007 (赞：3)

这道题目初来乍到可能会有些难看懂，于是下面给出思路。

## Solution

首先观察题目，现在有两种操作：

- 1：将$a$集合中随机的一个值加上2

- 2：将$b$集合中一个随机的值加上1

首先想到用人类的智慧：

令$x$为集合$a$的总和，$y$为集合$b$的总和。  
$\because$ 集合$a$一次性加的数比集合$b$一次性加的数多  
$\therefore$ 当$x < y$时，必定可能有一次操作能使$x = y$；反之则不然。

但是样例就否定了这种想法……

所以我们再一次仔细看题，发现：

- 1：若$a$集合中的这个值小于$b$集合中的这个值，则增加$a$集合中的数字，要使他们平等，需要加$\dfrac{a_i-b_i}{2}$次。

- 2：反着来，加$a[i] - b[i]$次。

最后模拟即可。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;

typedef long long ll;

ll a[N],b[N];
int n;
ll sum1,sum2;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",a+i);//等同于scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",b+i);
	for(int i=1;i<=n;i++) {
		if(a[i] > b[i]) sum1 += (a[i] - b[i]);
		if(a[i] < b[i]) sum2 += (b[i] - a[i])/2;
	}
	if(sum1 <= sum2) puts("Yes");
	else puts("No");
}
```

---

## 作者：zhou_ziyi (赞：1)

### 思路
看到这道题，我首先想到求到数组 $a$ 的和 $s1$，和数组 $b$ 的和 $s2$。

如果 $s1 > s2$, 那就不可能让两个数组完全相同。

但是样例就已经把这种方法否定了。

但是我们不难发现：
+ 若 $a$ 数组中的这个值小于 $b$ 数组中的这个值，则增加 $a$ 数组中的数字。如果要让他们相等的话，需要 $\frac{b_i-a_i}{2}$ 次。

+ 若 $a$ 数组中的这个值大于 $b$ 数组中的这个值，加 $a_i-b_i$ 次

我们只需要从 $1$ 到 $n$ 跑一遍即可。
### Code
```cpp
#include <cstdio>
#define int long long
const int MAXN = 1e5 + 10;
int n, s1, s2;
int a[MAXN], b[MAXN];
signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &b[i]);
	for (int i = 1; i <= n; i++) {
		if (a[i] > b[i])
			s1 += (a[i] - b[i]);
		if (a[i] < b[i])
			s2 += (b[i] - a[i]) / 2;
	}//
	if (s1 <= s2)
		printf("Yes\n");
	else
		printf("No\n");
}
```

---

## 作者：233333q (赞：1)

首先我们发现，每次操作后a序列的所有数字之和sum1加2，b序列的所有数字之和sum2加1。

因此操作次数就是sum2-sum1，若sum1>sum2则输出"No"。

那这题是不是完了？

样例二是这样的

```cpp
5
3 1 4 1 5
2 7 1 8 2
```

sum1=14

sum2=20

但结果为"No"

这是因为操作次数为sum2-sum1=6,而a[2]=1,b[2]=7,故要使a[2]=b[2]，至少要进行3次操作，同样的，要使a[4]=b[4],至少要进行4次操作，3+4>6,故不满足

因此我们把至少要操作的次数与实际操作次数比一下就好啦

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int a[10005],b[10005];
ll sum1,sum2;
ll delta,qwq;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum1+=a[i];
	for(int i=1;i<=n;i++) cin>>b[i],sum2+=b[i];
	if(sum1>sum2) {
		cout<<"No";return 0;
	}
	delta=sum2-sum1;
	for(int i=1;i<=n;i++)
	if(b[i]>a[i])
	qwq+=(b[i]+1-a[i])/2;
	if(qwq>delta) cout<<"No";
	else cout<<"Yes";
	return 0;
}
```



---

## 作者：二叉苹果树 (赞：0)

 **这道题目第一眼看上去貌似没有思路，实际上，可以两两操作每一对$a$和$b$，再进行累加次数，最后判断得到的结果是否符合题意.**

 与本题其他所有题解不同的是，本篇说明了每一步骤的做法与推导，~~而并非只给出式子~~.

对于每一对 $a_i$ 和 $b_i$ 的操作次数 $opt$ ，满足

$$opt=\begin{cases}\frac{b_i-a_i}{2},a_i<b_i\\a_i-b_i,a_i>b_i\end{cases}$$

来分析下，当 $a_i<b_i$ 时，若希望 $a_i=b_i$ ，则恰好需要 $\frac{b_i-a_i}{2}$ 次. 即每次进行 $a_i+=2,b_j+=1\,(j \not =i)$ ；若 $b_i-a_i$ 为奇数，特殊地，则只需要在某一次操作时，进行$a_i+=2,b_i+=1$ 即可.

另一方面，当 $a_i<b_i$ 时，则始终进行操作$a_i+=2,b_i+=1$，即每次操作后，$b_i$ 与 $a_i$ 的差减小 $1$ ， 则 $b_i-a_i$ 次操作后，有 $a_i=b_i$ .

容易发现，当所有$ a_i$ 和 $b_i$ 均按照上法操作一遍后，即可以判断现在的总操作数是否合法.

于是，$opt_{a_i>b_i}>=opt_{a_i<b_i}$ 时，符合题意，反之则不能满足条件.

需要注意的是，由于 $a_i$ 和 $b_i$ 的范围较大，故其之间的差也可能很大，需要 long long 进行存储操作数.

AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[10005],b[10005];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        cin>>b[i];
    long long s1=0,s2=0;
    for (int i=1;i<=n;i++) 
    {
        if(a[i]>b[i])
            s1+=a[i]-b[i];
        if(a[i]<b[i])
            s2+=(b[i]-a[i])/2;
    }
    if(s1<=s2)
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
    return 0;
}
```


 




---

## 作者：tommychen (赞：0)

### 题面
[洛谷传送门](https://www.luogu.com.cn/problem/AT3909)

题面过于简单，在这里不做太多解释。

### 思路
看懂题面得知有以下几个操作：

- 将 $a$ 数组中的任意一个值加上2。
- 将 $b$ 数组中的任意一个值加上1。

经过5 $min$ 的思考过后得出：

- $sum$ 记录当 $a_i$ $\lt$ $b_i$ 时要进行多少次操作。
	$sum+=$ $\frac{a_i + b_i}{2}$

- $ans$ 记录当 $a_i$ $\gt$ $b_i$ 时要进行多少次操作。
	$ans+=$ $a_i-b_i$
    
最后如果 $ans$ $\leqslant$ $sum$,输出Yes，反之输出No。

### 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
signed main(){
    int n;
    cin>>n;
    int a[n+1],b[n+1];
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    int sum=0,ans=0;
    for(int i=1;i<=n;i++){
        if(a[i]<b[i]){
            sum+=(b[i]-a[i])/2;
        }
        if(a[i]>b[i]){
            ans+=(a[i]-b[i]);
        }
    }
    if(ans<=sum){
        cout<<"Yes"<<endl;
        return 0;
    }
    cout<<"No"<<endl;
    return 0;
}
```



---

## 作者：happybob (赞：0)

对于 $\large a_i > b_i$，$\large sum1 += a_i - b_i$

对于 $\large a_i < b_i$，$\large sum1 += \frac{a_i - b_i}{2}$

代码：

```cpp
#include <iostream>
using namespace std;

int a[10005], b;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, sum1 = 0, sum2 = 0;
    cin >> n;
    for(register int i = 1; i <= n; i++) cin >> a[i];
    for(register int i = 1; i <= n; i++)
    {
        cin >> b;
        if(a[i] > b) sum1 += a[i] - b;
        else sum2 += (b - a[i]) >> 1;
    }
    cout << (sum1 <= sum2 ? "Yes" : "No") << endl;
    return 0;
}
```


---

## 作者：Doveqise (赞：0)

这道题可以算是模拟吧emmm  
对于a[i]<b[i]，增加a[i]；  
对于a[i]>b[i]，增加b[i]；  
最后模拟得之  
细节见下代码（勿抄）↓
```cpp
#include<bits/stdc++.h>
#define ll long long;
const int N=1e4+5;
ll a[N],b[N];
signed main(){
    int n;scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
    ll s1=0,s2=0;
    for (int i=1;i<n;i++) {
        if(a[i]>b[i])s1+=a[i]-b[i];
        if(a[i]<b[i])s2+=(b[i]-a[i])>>1;}
    puts(s1<=s2?"Yes":"No");
    return 0;
}
```


---

