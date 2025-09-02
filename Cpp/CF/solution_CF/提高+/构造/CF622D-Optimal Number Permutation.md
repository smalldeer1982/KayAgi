# Optimal Number Permutation

## 题目描述

You have array $ a $ that contains all integers from $ 1 $ to $ n $ twice. You can arbitrary permute any numbers in $ a $ .

Let number $ i $ be in positions $ x_{i},y_{i} $ ( $ x_{i}&lt;y_{i} $ ) in the permuted array $ a $ . Let's define the value $ d_{i}=y_{i}-x_{i} $ — the distance between the positions of the number $ i $ . Permute the numbers in array $ a $ to minimize the value of the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF622D/22b9f04219f1da8748ed3cb58a6363dd566698ed.png).

## 样例 #1

### 输入

```
2
```

### 输出

```
1 1 2 2
```

## 样例 #2

### 输入

```
1
```

### 输出

```
1 1
```

# 题解

## 作者：Loop1st (赞：3)

### CF622D Optimal Number Permutation
由于 $i \le n,n-i \ge 0$。则 $\forall i \in [1,n],
(n-i)\times |d_i+i-n| \ge 0, s \ge 0$，那么 $s$ 的最小值为 $0$，考虑构造一个 $s = 0$ 的序列，$i=n$ 时第一项为  $0$，随便放哪都行，其它时候 $d_i=n-i$，那么我们可以构建两个回文串：$1,3,5,\dots,p,\dots,5,3,1,2,4,6,\dots,k,\dots,4,2$，其中 
$$p=\begin{cases}
n-1  & \text{ if } n \text {为偶数}\\
n  & \text{ if }n \text {为奇数}
\end{cases}
,k=\begin{cases}
n  & \text{ if } n\text {为偶数}\\
n-1  & \text{ if } n\text {为奇数}
\end{cases}$$
 这样可以满足条件。

提示：遇到构造可以试试先手玩一下比较简单的情况。

时间复杂度 $O(n)$。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
int n, ans[N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= (n >> 1); i++) ans[i] = ans[n - i + 1] = (i << 1) - 1;
    for (int i = 1; i <= (n >> 1); i++) ans[n + i] = ans[(n << 1) - i] = (i << 1);
    ans[n << 1] = n;
    if (n & 1) ans[n / 2 + 1] = n;
    for (int i = 1; i <= (n << 1); i++) printf("%d ", ans[i]);
    puts("");
    return 0;
}
```

---

## 作者：zhangqiuyanAFOon2024 (赞：2)

~~这么水的蓝题赶紧水一篇题解。~~

题目很清楚。
### 思路

由于 $\lvert d_i+i-n \lvert\ge0$ 且 $n-i\ge0$，所以加起来一定大于等于零，于是最小是等于 $0$ 的情况。

考虑构造。

当 $1\le i\le n-1$ 时，$n-i>0$ 显然成立，于是，我们要 $\lvert d_i+i-n \lvert=0$。

这个好办，即 $d_i=n-i$。

举个例子，我们发现 $n=6$ 时，

可以这样放奇数：$1 3 5 5 3 1$。

这样放偶数 $2 4 ? 4 2?$。

其中，问号中的数不确定。

这个其实挺好想，数增加 $2$，空格减少 $2$。

之后，我们发现，$i=n$ 时 $n-i$ 恰好为 $0$，所以 $n$ 可以随便放，于时，问号处填 $6$ 也就是 $n$。

好了，上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int ans[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n/2;i++){
		ans[i]=i*2-1;
		ans[n-i+1]=i*2-1;//奇数
		ans[i+n]=i*2;
		ans[2*n-i]=i*2;//偶数
	}
	for(int i=1;i<=2*n;i++){
		if(ans[i]) cout<<ans[i]<<' ';
		else cout<<n<<' ';//填n
	}  
	return 0;
}

```

---

## 作者：hxhhxh (赞：2)

upd on 2024.6.5：修正了一处笔误，增加了一些额外的说明。

## 大意

已知 $n$，求构造一个长度为 $2n$ 的序列 $a$，使得其中恰好有两个 $i\;(i\leq n)$，并且 $s$ 最小，其中：

$$s =\sum_{i=1}^n(n-i)\times\lvert d_i+i-n\rvert $$

$d_i$ 表示 $i$ 在 $a$ 中两次出现的距离。

## 思路

由于 $s\geq 0$，所以如果 $s=0$ 就是最优的。

要使 $s=0$，需要对于 $1\leq i<n$，均有 $d_i+i-n=0$，即 $d_i=n-i$。$n$ 可以随便放。

可以尝试构造这个序列。先手算（或打表）出 $n=3,4,5,6$ 的情况：

$n=3$ 时 $[{\color{red}1},3,{\color{red}1},\qquad\quad{\color{green}2},{\color{green}2},3]$

$n=4$ 时 $[{\color{red}1},{\color{blue}3},{\color{blue}3},{\color{red}1},\qquad{\color{green}2},4,{\color{green}2},4]$

$n=5$ 时 $[{\color{red}1},{\color{blue}3},5,{\color{blue}3},{\color{red}1},\quad{\color{green}2},{\color{orange}4},{\color{orange}4},{\color{green}2},5]$

$n=6$ 时 $[{\color{red}1},{\color{blue}3},{\color{purple}5},{\color{purple}5},{\color{blue}3},{\color{red}1},{\color{green}2},{\color{orange}4},6,{\color{orange}4},{\color{green}2},6]$

这里把上面处了 $n$ 的数字涂色了，并进行了对齐。看起来很有规律！序列可以几乎分成两段回文的（最后多出来一个位置可以填 $n$）。

这十分的有道理：对于一个长度为 $m$ 的回文串，他内部的所有数的 $d$ 会取遍 $m-1,m-3,m-5,\dots$。只要有一个长为 $n$ 的回文串和一个长为 $n-1$ 的回文串就可以让 $d$ 取遍 $1,\dots,n-1$ 了。

总结一下规律：

+ $ a_i=2i-1,a_{n-i+1}=2i-1\quad(2i\leq n)$，这是第一段回文串；
+ $ a_{n+i}=2i,a_{2n-i}=2i\quad(2i<n)$，这是第二段回文串；
+ 剩下的地方填 $n$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000006];
int main(){
	cin>>n;
	for(int i=1;i<=n/2;i++) a[i]=a[n-i+1]=i*2-1;
	for(int i=1;i<=n/2;i++) a[i+n]=a[n*2-i]=i*2;
	for(int i=1;i<=n*2;i++){
		if(a[i]!=0) printf("%d ",a[i]);
		else printf("%d ",n);
	}
	return 0;
}
```

---

## 作者：WaterSun (赞：1)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF622D%20Optimal%20Number%20Permutation)

# 思路

首先考虑答案下界，因为 $(n - i)$ 和 $|d_i + i - n|$ 均大于等于 $0$，所以它们相乘一定大于等于 $0$。于是考虑能不能构造出结果为 $0$。

显然当 $i = n$ 时，无论 $d_i$ 的值是什么，式子的结果为 $0$。因此只需要考虑 $i \in [1,n)$ 的情况。

因为要使结果为 $0$，$n - i \neq 0$ 只能让 $|d_i + i - n| = 0$，于是就需要构造出 $d_i = n - i$。

比较容易想到构造的方式，将序列分为两个长度为 $n$ 的序列。前一个放 $n -i $ 为奇数的情况，后 $n$ 个为 $n - i$ 为偶数的情况。然后前 $n$ 个和后 $n$ 个每个数对应着放即可，剩下的两个位置就是放 $n$ 的。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e6 + 10;
int n,ans[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

int main(){
    n = read();
    for (re int i = 1;i < n;i += 2) ans[i / 2 + 1] = ans[n - i / 2] = i;
    for (re int i = 2;i < n;i += 2) ans[n + i / 2] = ans[2 * n - i / 2] = i;
    for (re int i = 1;i <= 2 * n;i++){
        if (ans[i]) printf("%d ",ans[i]);
        else printf("%d ",n);
    }
    return 0;
}
```

---

## 作者：Create_Random (赞：1)

[D. Optimal Number Permutation](https://codeforces.ml/contest/622/problem/D)

解法：

要求 $s= \sum\limits_{i=1}^n (n-i) \times \left| d_i+i-n \right|$ 的值最小，

那么仔细观察此式子可发现此式子为乘法，

那么将其中一项尽可能变为 $0$ 为最优解

则移项可得 $d_i=n-i$ ,

则 $d_1=n-1$

$d_2=n-2$

$d_3=n-3$

$\vdots$

只有 $d_n$ 可以为任意值。

此时 $s=0$ 为最优解。

~~看起来这个式子可以构造一下的样子~~

到这一步就可以发现将 $2n$ 个数分为两段，

左侧 $n$ 个分别为 $1,3,5 \cdots$ （ $d_i =n-1,n-3,n-5 \cdots$)

右侧 $n$ 个分别为 $2,4,6 \cdots$ （ $d_i =n-2,n-4,n-6 \cdots$)

最后 $n$ 随便放即可。

时间复杂度 $O(n)$.

$Code$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,flag;
int a[1000010];
int main()
{
	scanf("%d",&n);
	for(int i=1,j=1;i<=n;i+=2,j++)
	{
		a[j]=i;
		a[n-j+1]=i;
	}
	for(int i=2,j=1;i<=n;i+=2,j++)
	{
		a[j+n]=i;
		a[2*n-1-j+1]=i;
	}
	for(int i=1;i<=2*n;i++)
	{
		if(!a[i])
		{
			a[i]=n;
		}
	}
	for(int i=1;i<=2*n;i++)
	{
		printf("%d ",a[i]);
	}
}
```


---

## 作者：Vitamin_B (赞：1)

# 思路
显然，$(n-i)\times|d_i+i-n|\ge0$，当且仅当 $d_i=n-i$ 时的数取最小值 $0$（但 $i=n$ 时 $d_i$ 随便）。然后我们可以把这个答案数组劈成 $2$ 边，左边偶数，右边奇数。然后只要在 $i+n,2n-i+1$ 里填 $2i$，$i,n-i$ 里填 $2i-1$ 就行，剩下有空就填 $n$，反正 $d_n$ 是几没啥影响。

如何证明这样填是对的呢？首先，不管是奇数还是偶数，$d_x=n-x$。$(n-i)-i=n-2i=d_{2i},(2n-i+1)-(i+n)=n-(2i-1)=d_{2i-1}$，所以这个填法始终正确。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, a[1000005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n >> 1; ++ i)
		a[i] = a[n - i] = i * 2, a[i + n] = a[n * 2 + 1 - i] = 2 * i - 1;
	for (int i = 1; i <= n << 1; ++ i)
		cout << (a[i] ? a[i] : n) << ' ';
	return 0;
}
```

---

## 作者：analysis (赞：0)

一开始还看错题了，搞得我口胡了个贪心，打完发现要求最小值。

以下是正文部分。

---

比较简单的一道题。

这个式子转换以下就会变成：

$$
s = \sum_{i=1}^{n}(n-i) \times |d_i - (n - i)|
$$

然后发现 $n$ 怎么放是无所谓的。

$$
s = \sum_{i=1}^{n-1}(n-i) \times |d_i - (n - i)|
$$

上式尽可能小，很容易发现可以构造出 $d_i = n - i$。

我们把 $n - i$ 为奇数（不看 $n$）的归一类，发现可以对他们根据 $d_i$ 大小排序，顺序输出一遍逆序输出一遍。

偶数的也类似，但中间会多出个空槽。把 $n$ 放入即可，最后在偶数部分末尾再放一个 $n$ 即可。

$O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
void odd(int pos)
{
    int i;
    for(i=pos;i<n;i+=2)
    {
        cout<<i<<" ";
    }
    i -= 2;
    for(;i>=1;i-=2)
    {
        cout<<i<<" ";
    }
}
void even(int pos)
{
    int i;
    for(i=pos;i<n;i+=2)
    {
        cout<<i<<" ";
    }
    cout<<n<<" ";
    i -= 2;
    for(;i>=1;i-=2)
    {
        cout<<i<<" ";
    }
    cout<<n<<" ";
}
signed main()
{
    cin >> n;
    if(n == 1)cout<<"1 1";
    else if(n == 2)cout<<"1 1 2 2";
    else if((n - 1) & 1)
    {
        odd(1);
        even(2);
    }
    else
    {
        even(1);
        odd(2);
    }
}
```

---

## 作者：xuhanxi_dada117 (赞：0)

# CF622D Optimal Number Permutation  题解

[题目传送门](https://www.luogu.com.cn/problem/CF622D)

## 题目大意

给一个 $n$ ，现在有 $2n$ 个数，从 $1$ 到 $n$ 每个数的数量均为 $2$ 。

求使 $\sum_{i=1}^{n}{(n-i)\times (d_i-i+n)}$  最小的 $2n$ 个数的排列。

## 解法

考虑 $n$ 不论放哪里那个柿子都是 $0$ 所以让它最后补位。

让 $\sum_{i=1}^{n}{(n-i)\times (d_i-i+n)}$ 最小，肯定是让 $(d_i-i+n)=0$ 。

所以，我们给一组构造方案：

对前 $n$ 个数：让其成为 $1,3,5,...,5,3,1$ 型（山峰数列）

对后 $n$ 个数：让其成为 $2,4,6,...,6,4,2$ 型（山峰数列）

最后肯定少两个，让 $n$ 进去就可以了。

## 代码
```cpp
#include<bits/stdc++.h>  //史上超短蓝题
using namespace std;
int n,a[1000010],num=1;
int main(){
	cin>>n;
    //放奇数
	for(int i=1;num<=n;++i){a[i]=a[n-i+1]=num;num+=2;}num=2;
    //放偶数
	for(int i=1;num<=n;++i){a[i+n]=a[2*n-i+1]=num;num+=2;}
    //放 n
	for(int i=1;i<=2*n;i++) if(!a[i]) a[i]=n;
	for(int i=1;i<=2*n;i++) cout<<a[i]<<" ";
	return 0;
}
```

## AC！

---

## 作者：tZEROちゃん (赞：0)

我们来看一下题目里的这个式子：


$$s= \sum\limits_{i=1}^n (n-i) \times \left| d_i+i-n \right|$$

注意到求的和是一个积的形式，如果这个积是等于 $0$ 的，那么这个和就是最小的。

注意到 $n-i$ 不可能是 $0$，所以我们想让 $d_i+i-n=0$，那么怎么构造呢？

若 $n$ 是偶数。可以把奇数放在数组的前半部分：
- 数字 $1$ 放在第 $1$ 个，第 $n$ 个位置上。
- 数字 $3$ 放在第 $2$ 个，第 $n - 1$ 个位置上。

同样的，我们把偶数放在后半部分：
- 数字 $2$ 放在第 $n+1$ 个，第 $2n-1$ 个位置上。
- 数字 $4$ 放在第 $n+2$ 个，第 $2n - 2$ 个位置上。

然后没有被放的位置就放 $n$。

奇数情况也类似，代码十分好写，不放了。

---

## 作者：Register_int (赞：0)

简单构造。  
首先这个加和里面是个乘积形式，只要一项为 $0$，那么造成的贡献也为 $0$。这就说明 $n$ 对答案是没有贡献的（$n-i=0$），可以瞎放。  
考虑 $1\sim n-1$。只要我们让 $d_i=n-i$，就能取得最小代价。顺着安排每一个数：  
$d_1=n-1$，将 $1$ 放在 $1,n$ 位置上。  
$d_2=n-2$。此时位置冲突，因此将 $2$ 放在 $n+2,2n$ 上。  
$d_3=n-3=(n-1)-2$，放在 $2,n-1$ 上。  
$d_2=n-4=(n-1)-3$。此时位置冲突，因此将 $2$ 放在 $n+3,2n-1$ 上。  
$\vdots$  
填完后，数列会空出 $n+1$ 这一格，同时少放一个 $n$。塞进去就完事了。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;

int n, a[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 1, j = 1; i <= n; i += 2, j++) a[j] = a[n - j + 1] = i;
	for (int i = 2, j = 1; i <= n; i += 2, j++) a[n + j + 1] = a[2 * n - j + 1] = i;
	a[n + 1] = n;
	for (int i = 1; i <= n << 1; i++) printf("%d ", a[i]);
}
```

---

## 作者：WorldMachine (赞：0)

玩一下样例发现 $s$ 最小为 $0$，容易得到构造方式：将 $1\sim n-1$ 中的奇数放在左半边、偶数放在右半边构成回文，保证每个数之间距离为 $n-i$，$n$ 随便放即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
int n, a[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i += 2) a[i + 1 >> 1] = a[n - (i + 1 >> 1) + 1] = i;
	for (int i = 2; i < n; i += 2) a[n + (i >> 1)] = a[n * 2 - (i >> 1)] = i;
	for (int i = 1; i <= n * 2; i++) if (!a[i]) a[i] = n;
	for (int i = 1; i <= n * 2; i++) printf("%d ", a[i]);
}
```

---

## 作者：cmask4869 (赞：0)

## 思路
本题为贪心，易得式子为乘法，所以需要尽量使其中一项为 $0$ 用来求出 $s$ 的最小值。将式子进行处理可得 $d_i$ 可以最小。将式子分为奇数偶数分类讨论，剩下的值全填 $n$ 就可以保证 $s$ 最小。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
typedef long long ll ;
const int N=1000005 ;
int a[N] ;

int main(){
	int n ;
	cin >> n ;
	for (int i=1 ; i<=(n/2) ; i++){
		a[i]=a[n-i+1]=i*2-1 ;
		a[i+n]=a[n*2-i]=i*2 ;
	} 
	for (int i=1 ; i<=(n*2) ; i++){
		if (!a[i]) cout << n << " " ; 
		else cout << a[i] << " " ; 
	}
	return 0 ;
}
```

---

## 作者：cike_bilibili (赞：0)

我们可以把数组分成两半，我们把两个 $1$ 填到第一个和第 $n$ 个位置，然后在里面包裹奇数，把 $2$ 填到第 $n$ 个和第 $2n-1$ 的位置，中间包裹偶数，由于 $i=n$ 时 $n-i=0$，所以 $n$ 可以随便填，$s$ 的最小值为 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[1000005];
int main(){
	cin>>n;
	int now=1;
	for(int i=1;n-i+1>i;i++){
		a[i]=now,a[n-i+1]=now;
		now+=2;
	}
	now=2;
	for(int i=1;n-i>i;i++){
		a[n+i]=now;
		a[2*n-i]=now;
		now+=2;
	}
	for(int i=1;i<=2*n;i++)if(!a[i])a[i]=n;
	for(int i=1;i<=2*n;i++)cout<<a[i]<<' ';	
}
```

---

