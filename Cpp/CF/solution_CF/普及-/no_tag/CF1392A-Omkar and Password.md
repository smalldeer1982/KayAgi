# Omkar and Password

## 题目描述

Lord Omkar has permitted you to enter the Holy Church of Omkar! To test your worthiness, Omkar gives you a password which you must interpret!

A password is an array $ a $ of $ n $ positive integers. You apply the following operation to the array: pick any two adjacent numbers that are not equal to each other and replace them with their sum. Formally, choose an index $ i $ such that $ 1 \leq i       < n $ and $ a_{i} \neq a_{i+1} $ , delete both $ a_i $ and $ a_{i+1} $ from the array and put $ a_{i}+a_{i+1} $ in their place.

For example, for array $ [7, 4, 3, 7] $ you can choose $ i =       2 $ and the array will become $ [7, 4+3, 7] = [7, 7, 7] $ . Note that in this array you can't apply this operation anymore.

Notice that one operation will decrease the size of the password by $ 1 $ . What is the shortest possible length of the password after some number (possibly $ 0 $ ) of operations?

## 说明/提示

In the first test case, you can do the following to achieve a length of $ 1 $ :

Pick $ i=2 $ to get $ [2, 4, 1] $

Pick $ i=1 $ to get $ [6, 1] $

Pick $ i=1 $ to get $ [7] $

In the second test case, you can't perform any operations because there is no valid $ i $ that satisfies the requirements mentioned above.

## 样例 #1

### 输入

```
2
4
2 1 3 1
2
420 420```

### 输出

```
1
2```

# 题解

## 作者：_QrSn_ (赞：13)

### 分析
题意：给出一个数列，如果左右两个数不一样，就可以将其合并成一个数，问最后数列最短长度是多少

结论：当数列中所有的数都相同时，数列不可合并，长度为 $n$ ，其余情况（就算只有一个数不同）最后都可合并成一个数，长度为 $1$ 。 

例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/3u51rtgl.png)

### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n;

int main() {
	cin>>q;
	for(int j=0;j<q;j++)
	{
	    bool AC=true;
		cin>>n;
		int a,b;
	    cin>>a;
	    for(int i=1;i<n;i++)
	   {
		cin>>b;
		if(b!=a)AC=false;
		a=b; 
	   }
	   if(AC==false)cout<<1<<endl;
	   else cout<<n<<endl;
	}
	
	return 0;
}
```


---

## 作者：红黑树 (赞：5)

结论 ：
当数列中全是相同的数时，答案为 $n$，其他情况答案都为 $1$

简证 ：
如果数列里的数全部相同就无法合并。
$~~$
否则一定能找到一个方法，使得把两个数合并后，数列里的数不会全部相同。

$AC\; Code :$
```cpp
#include <iostream>

using namespace std;

signed main() {
  int t;
  cin >> t;
  while (t--) {
    int n, x;
    bool diff = 0;
    cin >> n >> x;
    for (int i = 1; i < n; ++i) {
      int y;
      cin >> y;
      if (x != y) {
        diff = 1;
      }
    }
    cout << (diff ? 1 : n) << '\n';
  }
  return 0;
}
```

---

## 作者：_Hero_ (赞：3)

# 题意
题目给出序列的个数和序列，可将序列中相邻的数合成一个数，此时序列个数减一，问序列个数最少是多少。

# 分析
序列中两个相邻的数合成后成为它们的和，那么只要序列的数不全相等，那么肯定有一种方式让序列变成一个数。那就只用判断序列数字是否全部相同就可以了。举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/pjhklkk8.png)

# 代码
```
#include <bits/stdc++.h>
using namespace std;
int t;
int main(){
cin>>t;
for(int i=0;i<t;i++)
{
	int n,a,b;
	bool x=0;//bool标记
	cin>>n;
	cin>>a;
	for(int i=1;i<n;i++)
	{
		cin>>b;
		if(a!=b)//ab比较
	      {
	      x=1;
	}
	a=b//记得数值变化;
}	
   if(x==1)cout<<1<<endl;//不完全相同
	else cout<<n<<endl;//完全相同
}
  return 0;
}
```




---

## 作者：Syamoe (赞：2)

可以说，这道题目是一道很重要的规律题。

没事闲的看犇的时候看到了这道题目，还是写一篇题解来一下吧，望通过，这样我就能橙了 qwq

首先呢，上述说过了是规律题，得到的规律应该是这样的：

当所以数相等时,数的个数就是最后数列的长度，如果并不是所有数都相等，则 $1$ 为最后的长度。

可以先设这一个为基本的猜想，我要讲的是证明：

**都相同时**

请看题目中说了

~~~~
对于两个相邻的且不相同的数，你可以将他们合并起来，即将这两个数替换成它们的和。
~~~~

因此，可以知道的是，相同的时候一个都合并不了喽 qwq

**至少一个不同**

如下面的数，可见一定是一个最不利的 qwq：

$1\ 2\ 2\ 2\ 2\ 2\ $

如果这列数中有无数多个 $2$（且假定只有开头的一个 $1$ ），那么，我们可以先将两个不同的（即 $1$ 和 $2$）进行第一次合并，接着，可以再将两个不同的数（即 $2$ 和 $3$）进行一次合并，之后我们可以发现，每一次合并之后，都会出现一个 **不同** 的数，而这个不同的数又可以继续合并……因此，最终，不论多长的数，都能化简为所有这些数的和！

上述是验证的过程，下面是全部代码 qwq:

```cpp
#include <iostream>
using namespace std;
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		bool flag = 1;
		int m;
		cin >> m;
		int flag2 = m;
		for (int i = 2; i <= n; i++) {
			int a;
			cin >> a;
			if (a != m) {
				flag = 0;
			}
		}
		if (flag == 0) {
			cout << 1 << endl;
		}
		else {
			cout << n << endl;
		}
	}
}
```


这是本题的思路，希望对您有帮助 qwq


---

## 作者：牛蛙丶丶 (赞：1)

题意：给定一个数列，当 $a_i\ne a_{i+1}$ 时，可以合并 $a_i$和$a_{i+1}$ ，求若干次操作之后的数列的最短长度

令 $p$ 为数列的最大值，所以p一定可以和两端的数合并成一个新数 $q$ ,因为所有的 $a_i$ 都是大于 1 的，可以证明 $q>p$ ，以此类推，数列最终一定会变为一个数

所以可以发现，只有数列中全部为一个数时，答案为数列原来的长度，否侧，答案则为 1

Code
```cpp
#include <iostream>
#define N 200070

using namespace std;

int n,a[N],cnt,T;

int main(){
	cin>>T;
	while(T--){
		cnt=0;
		cin>>n;
		for(int i=1;i<=n;++i)
			cin>>a[i];
		for(int i=2;i<=n;++i)
			if(a[i]==a[i-1]) cnt++;
		if(cnt==n-1) cout<<n<<endl;
		else cout<<1<<endl;
	}
}
```


---

## 作者：MrCR7 (赞：1)

## 简述题意
共有 $t$ 组数据，每个数据的第 $1$ 行一个数字 $n$，代表这个序列有多少个数字，第 $2$ 行 $n$ 个数字 $a_i$，对于两个相邻的且不相同的数，可以将它们合并起来，即将这两个数替换成它们的和。

## 阐述总结
当数列中所有数字都相同的时候，这个数列执行操作后的最多数字便是 $n$ 个。

否则，答案即为 $1$。

~~所以，这道题目在比赛的时候输出 $n$ 都可以拿到不少的分数（逃~~。
## 证明总结
当数列中所有数字都相同的时候，这时候 $n$ 个 $a_i$ 都不可能相加，因为它们全部相同，所以答案即为 $n$。

否则，每两个相邻的数字，都可以相加。即使存在 $a_i = a_{i+2}$ 的情况，由于保证 $1 \le a_i \le 2 \times 10^5$ ，所以每一个数字都不可能为 $0$，所以当 $a_i$ 和 $a_{i+2}$ 全部加上 $a_{i+1}$ 后，它们两个便是不相同的了。所有的 $a_i$ 的证明同理。
## Ac Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);//t组数据。 
	while(t--){
		int n,now,x,sum=1;//n如图，now表示序列的第一个数字，x是当前要读的数字，sum是在序列中now出现的次数。 
		scanf("%d",&n); 
		scanf("%d",&x);
		now=x;//把第一个数字赋值给now。 
		for(int i=2;i<=n;i++){
			scanf("%d",&x);//读入。 
			if(x==now) sum++;//如果相等，sum+1。 
		}
		if(sum==n) printf("%d\n",n);//如果数字全部相等，输出n。 
		else puts("1");//否则，输出1。 
	}
	return 0;
}
```
## 题后总结
这种题目如果硬做，能把人给做傻。

所以一定要找到规律。

完结撒花qwq~

---

## 作者：leoair (赞：0)

### 题意：
给定一个长度为 $n$ 的序列 $a$，每次可以进行一次操作使序列中相邻的两个不同的数合并成一个新的数，该新数为这两个数之和，原有的两个数被删除。求进行若干次操作后可以使序列的长度的最小值。

### 分析：
很显然，当所有数都相同时，是无法合并的，因此答案就为 $n$。若不都相同，则可选择序列中的最大值（若有多个则选其中一个），与相邻的不同的数进行无数次的合并，最终可以发现，可以将序列合并到只剩一个数，因此答案为 $1$。
综上，若序列中所有数相同，则答案为 $n$，否则为 $1$。

### Code：
```cpp
/*
user:leoair
time:2022.3.24
*/
#include <bits/stdc++.h>
#define int long long
#define N 200010
using namespace std;

int a[N];

inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
    for (; ch >= '0' && ch <= '9'; s = s * 10 + ch - '0', ch = getchar());
    return s * w;
}

signed main(){
    for (int _ = read(), n; _--; ){
        bool f = 0;
        n = read(), a[1] = read();
        for (int i = 2; i <= n; ++i) a[i] = read(), f = a[i] != a[i - 1] ? 1 : f;
        if (!f)  printf("%lld\n", n);
        else puts("1");
    }
    return 0;
}
```

---

## 作者：yemengzhi (赞：0)

## 题目大意
给定一个数列，当 $a_i \ne a_{i+1}$ 时，可以合并 $a_i$ 和 $a_{i+1}$ ,为两数之和 求若干次操作之后的数列的最短长度。

## 算法思想
我们的算法很简单，当所以数相等时 $n$ 就是最后数列的长度，如果并不是所有数都相等，则 1 为最后的长度。

简单证明：如果都相等，那么哪一个都不能合并起来，如果有一个或多个不同，我们就肯定有办法把所有数列合并起来。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		int x;
		int y;//y 用来保存上一轮的数
		int flag=1;//flag来确定是否都一样
		cin>>x;
		y=x;
		for(int i=2;i<=n;i++)
		{
			cin>>x;
			if(y!=x)
				flag=0;
		}
		if(!flag)
			cout<<1<<endl;
		else
			cout<<n<<endl;
	}
	
} 
```
好了就这样，拜拜。

---

## 作者：daiarineko (赞：0)

## 0. 题意简述

多组询问，每次给出一个长度为 $n$ 的序列 $a$，对于两个相邻的且不相同的数，你可以将它们合并起来，即将这两个数替换成它们的和。

每次进行一次操作后，序列长度会 $-1$，现在你可以随意进行若干次操作，问最后序列长度最短是多少。

## 1. 题目分析&主要代码

考察点：数论

题目难度：普及-

时间复杂度：$\Theta(1)$

### 题目分析

其实这题不难，通过样例分析，我们已经看出来了：如果所有项相同，则无法合并，输出 $n$ 即可；否则输出 $1$。

难点在于证明。有些人只知道结果，却不知道为何有这个结果。于是大部分证明都在这两张图里了：

![](https://cdn.luogu.com.cn/upload/image_hosting/2o251sg0.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/p7lm9rjp.png)

同时，项数为 $1$ 明显答案就是 $1$（合不合并都一样），项数为 $2$ 则只有两种可能：相同（答案为 $2$）与不相同（答案为 $1$）。项数 $>4$ 的，证明与项数 $=4$ 的相同，只需要把三项变为 $n-1$ 项即可。

于是我们得到最上面的结论。

### 主要代码

为了没人抄题解，我们使用 `Python`。~~（懒）~~

输入比较简单，可以使用 `list(map(int,input().split()))`。

判重：
```python
n=s[0] #如果后面所有d均与此相同，说明序列全部相同
for d in s:
    if d==n:
        continue
    break #说明不完全相同
else: #Python中，在for后使用else，为当循环完整执行时（未被break）进入的分支
    print(n) #从未break，说明每项均相同
    continue #多组数据，这里的continue为外层循环
print(1)
```

## 2. 完整代码

```python
l=int(input()) #数据组数
for i in range(l):
    nn=input() #输入序列长度，一会会抹掉此值
    s=list(map(int,input().split()))
    n=s[0]
    for d in s:
        if d==n:
            continue
        break
    else:
        print(nn)
        continue
    print(1)
```

## 3. 结尾

`Python` 编程很简单，但缺点也不少，比如费时间费内存![](https://cdn.luogu.com.cn/upload/image_hosting/alndkgq1.png)；并且太过于简单化的编程语言会导致我们不再想要了解底层的知识，学会的知识都是表面的，所以我并不建议经常使用 `Python`。

另外，语言之间的差异其实并不很大，本题解使用 `Python` 只是为了让大家“自己动手丰衣足食”，只要在代码上修改，逻辑不变，也能改成其他语言。

## 4. Updates

2021/01/06：感谢@xueshenwudi 的指正，目前已经将标题“结尾”的编号改为3（小修正：格式错误）

---

## 作者：aakennes (赞：0)

容易发现，答案只可能是 $1$ 或者 $n$ ，数列中的数全相等为 $n$ ，反之为 $1$

简证:

对于全相等的数列，由于一开始就无法合并，所以答案为 $n$

对于其它数列，答案不为 $1$ 当且仅当场上只有全相等的数列，如果当前场上只有全相等的数列，直接撤回此前一步，使此前一步合并的数与另一个数合并，直到不存在全相等的数列

```
		cin>>n;
		bool exist=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(i>1&&a[i]!=a[i-1])exist=1;
		}
		if(exist)puts("1");
		else cout<<n<<endl;
```

---

## 作者：happybob (赞：0)

其实这个题目要从数学角度分析：

如果输入数据全一样，直接输出n就好了

如果不一样最小的长度只有可能为1

vector代码来啦：
```cpp
#include <iostream>
#include <vector>
using namespace std;

vector <int> vec;

int main()
{
    int n, k;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        bool flag = true;
        cin >> k;
        vec.resize(k);
        for(vector <int>::iterator it = vec.begin(); it != vec.end(); it++)
        {
            cin >> *it;
        }
        for(vector <int>::iterator it = vec.begin() + 1; it != vec.end(); it++)
        {
            if(*it != vec[0])
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            cout << k << endl;
        }
        else
        {
            cout << "1\n";
        }
    }
    return 0;
}
```

arr代码也有的哦：
```cpp
#include <iostream>
#include <vector>
using namespace std;

int arr[200005];

int main()
{
    int n, k;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        bool flag = true;
        cin >> k;
        for(int i = 1; i <= k; i++)
        {
            cin >> arr[i];
        }
        for(int i = 1; i <= k; i++)
        {
            if(arr[i] != arr[1])
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            cout << k << endl;
        }
        else
        {
            cout << "1\n";
        }
    }
    return 0;
}
```

注意数组大小哦

---

## 作者：chaichunyang (赞：0)

题目翻译：

$t$组询问，每次给出一个长度为 $n$ 的序列 $a$，对于两个相邻的且不相同的数，你可以将他们合并起来，即将这两个数替换成它们的和。

注意到，你每次进行一次操作后，序列长度会 $−1$，现在你可以随意进行若干次操作，问最后序列长度最短是多少。

算法讲解：
1. 如果所有数字都一样那么就不能合并，输出n；
1. 如果最大数字只有一个，那么从最大的开始合并。合并完毕后，他还是最大的所以一定可以合并到1；
1. 如果最大数字不止一个，和第2种一样可以处理
1. 如果有其他数据可以H***(被和谐了）请评论或私信

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,N,a[1000039];
int main (){
	scanf("%d",&T);
	while(T--){
	    scanf("%d",&N);
	    for(int i=1;i<=N;i++)scanf("%d",&a[i]);
	    sort(a+1,a+1+N);
	    if(a[1]==a[N])printf("%d\n",N);
	    else printf("%d\n",1);
	}
	return 0;
}//14行不压行代码
```

---

## 作者：xiaozeyu (赞：0)

讲一下题目的大致意思

一共 $t$ 组数据

对于每组数据

给出长度为 $n$ 的一串数字

每次可以把相邻位置的两个数字合并 

比如 $a，b , c $ $\to $ $(a+b),c$ 

但是相同的数字不能合并

问最后至少剩下几个数字

其实就是问会剩下几个相同的数字



------------


最后其实只有两种可能：

1. 全部一样

2. 一个数字

**可以证明，只由原来的序列里所有数字一样的时候才会有不止一个数字剩余**

**证明：**

设开始序列并非完全相同 ,

可以每次做和最大的相加，这样的话保证可以不相同

如果安全相同则不能作任何相加



------------


代码实现如下：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register long long i=a;i<=b;i++)
#define Rep(i,a,b) for(register long long i=a;i>=b;i--)
using namespace std;
inline long long read()
{
	char c=getchar();long long x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
long long t,a[200010],n;
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		For(i,1,n)
			a[i]=read();
		sort(a+1,a+n+1);
		if(a[1]==a[n]) printf("%lld\n",n);
		else printf("1\n");
	}
}

```


---

## 作者：Chinese_zjc_ (赞：0)

### 结论题

不难发现对于一个长度为 $n$ 的序列,除了所有 $a_i$ 都相等的情况下答案为 $n$ ,其他情况下答案都为 $1$ .

下面用**反证法证明**:

​	我们假设存在一个长度为 $n$ 的序列,答案为 $x$ ( $1<x<n$ ).

​	那么它的最终状态必定为一个长度为 $x$ 的序列 $B$ ,满足 $b_i=b_j$ ( $1\leq i,j\leq x$ ).

​	它最后一次操作前的序列 $C$ 必定是一个合并 $c_k$ 和 $c_{k+1}$ ( $1\leq k\leq x$ )后就能变成 $B$ 的序列.

​	因此, $c_k+c_{k+1}=b_i$ ,又由于 $1\leq c_k,c_{k+1}\leq10^9$ ,易得 $c_k,c_{k+1}<b_i$ .

​	那么对于序列 $C$ ,至少还有另外一种操作方式,而这种操作方式就不会使 $C$ 变成 $B$ ,使序列长度更短,与假设不符,故得:

​	不存在答案为 $x$ ( $1<x<n$ )的长度为 $n$ 的序列.

​	即答案只可能为 $1$ 或 $n$ .

**证毕**.

而答案为 $n$ 的情况显然就是序列内每个元素都相等的情况.

其他情况下答案都为 $1$ .

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
#include<iostream>
#define int long long
using namespace std;
int n,t,a[500005];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        if(a[i]!=a[1])
        {
            cout<<1<<endl;
            while(i<n)
            {
                cin>>a[++i];
            }
            return;
        }
    }
    cout<<n<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：zhzzhzzzz (赞：0)

作为一道A题挺好的，难度适中，~~可我考场上想了20min~~

### 题目大意：

给定一个长度为 $n$ 的序列，你可以任意地进行操作，每次操作可以将相邻的两个**不相同的数**合并，使序列长度 $-1$。求操作完成后序列的最短长度。

可能很多人看完题目中的 $For\space example$ 部分人就已经傻了，~~没错，这是一种错误做法~~。正确的做法是从左往右排着操作就行，
$$[7,4,3,7]\longrightarrow[11,3,7]$$
$$[11,3,7]\longrightarrow[14,7]$$
$$[14,7]\longrightarrow[21]$$

再考虑一种情况： 
$$[1,2,3,3,3,3]$$

这个时候从左往右来是没用的，但是我们可以从第二个数开始，这样 $2+3\neq3$，可以合并。排着合下去最后再来管 $1$ ，最后长度也是 $1$ 。
此时你可能会想到：欸？好像操作到最后每个序列长度都可以变成 $1$ 诶，但是一看样例，$\textcolor{red}{Failed\space Sample\space Test}$ （逃。

如果一开始这个序列中的元素全部都相同呢，那没法办，所以原封不动送回去，输出 $n$ 即可。

$Code$:（太简单了不写注释了）

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    cin >> T;
    while (~--T) {
        int n;
        int last, x;
        cin >> n;
        cin >> x;
        last       = x;
        bool flag  = false;
        bool flag2 = false;
        for (int i = 1; i <= n - 1; i++) {
            cin >> x;
            if (last != x && !flag2) {
                cout << 1 << endl;
                flag  = true;
                flag2 = true;
            }
        }
        if (!flag)
            cout << n << endl;
    }
    return 0;
}
```

---

