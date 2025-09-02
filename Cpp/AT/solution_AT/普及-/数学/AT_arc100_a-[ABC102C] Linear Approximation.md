# [ABC102C] Linear Approximation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc102/tasks/arc100_a

すぬけ君は、長さ $ N $ の整数列 $ A $ を持っています。

すぬけ君は、整数 $ b $ を自由に選びます。 この時、$ A_i $ と $ b+i $ が離れているとすぬけ君は悲しいです。 より具体的には、すぬけ君の悲しさの値は、次の式で計算されます。 なおここで、$ abs(x) $ は $ x $ の絶対値を返す関数です。

- $ abs(A_1\ -\ (b+1))\ +\ abs(A_2\ -\ (b+2))\ +\ ...\ +\ abs(A_N\ -\ (b+N)) $

すぬけ君の悲しさの値の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

$ b=0 $ とすれば、すぬけ君の悲しさの値は、$ abs(2-(0+1))+abs(2-(0+2))+abs(3-(0+3))+abs(5-(0+4))+abs(5-(0+5))=2 $ となります。 $ b $ をどのように選んでも、すぬけ君の悲しさの値を $ 2 $ 未満にすることは出来ないので、答えは $ 2 $ になります。

## 样例 #1

### 输入

```
5
2 2 3 5 5```

### 输出

```
2```

## 样例 #2

### 输入

```
9
1 2 3 4 5 6 7 8 9```

### 输出

```
0```

## 样例 #3

### 输入

```
6
6 5 4 3 2 1```

### 输出

```
18```

## 样例 #4

### 输入

```
7
1 1 1 1 2 3 4```

### 输出

```
6```

# 题解

## 作者：Yizhixiaoyun (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT4166)
 
## 题目分析

通项公式：$|(a_i - i) - b)|$

那么我们就可以发现，如果希望式子最小，那么 $(a_i - i)$ 与 $b$ 之间的差就要尽量小。

我们可以使用另外一个数组 $q$ ，使 $q_i = a_i - i$ ，然后对其排序，排序后将 $b$ 取 $q_{(n+1)/2}$ ，即可与 $(a_i - i)$ 差值最小。

## 贴上代码

十年 $\text{oi}$ 一场空，没开 $\text{long long}$ 见祖宗！

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pf push_front
#define ass assign
#define fst first
#define sec second
#define lb lower_bound
#define ub upper_bound
#define zltAKIOI 1
using namespace std;
const int maxn=200005;
long long n,a[maxn];
long long x,ans;
void init(){
	cin>>n;
	for(register long long i=1;i<=n;++i){
		cin>>x;a[i]=x-i;
	}
}
void duel(){
	sort(a+1,a+n+1);
    for(register long long i=1;i<=n;++i) ans+=abs(a[i]-a[(i+1)>>1]);
}
void print(){
	cout<<ans<<endl;
}
int main(){
	init();
	duel();
	print();
}
```

---

## 作者：MattL (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/AT4166)&&[原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/4166)

~~为啥一道水题都没什么人写题解~~

---
进入正题


先写出通项： $\left\vert A_i-(b+i)\right\vert$

上式可以转化成： $\left\vert (A_i-i)-b\right\vert$

想要这个式子的值小，当然要让 $b$ 尽可能接近 $A_i-i$ ，所以我们先预处理出一个 $c$ 数组： $c_i=a_i-i$

然后排序， $b$ 取中位数可以使得原式最小，也就是  $c_{\left\lfloor\frac{n+1}{2}\right\rfloor}$ 

最后答案就是 
$$\sum_{i=1}^n \left\vert A_i-(b+i)\right\vert$$ 
也可以化简为 
$$\sum_{i=1}^n \left\vert c_i-b\right\vert$$

最后提一句：

**十年 OI 一场空，忘开 long long 见祖宗**

---
上代码 ~~挑战题解的最短完整代码~~：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,t,a[222222],ans;
int main()
{
    cin>>n;
    for(long long i=1;i<=n;i++)
    {
        cin>>t;//这里把a数组也省了
        a[i]=t-i;//同b[i]
    }
    sort(a+1,a+n+1);
    for(long long i=1;i<=n;i++)
        ans+=abs(a[i]-a[(i+1)/2]);
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：皎月半洒花 (赞：1)

尝试写水题题解刷贡献分.jpg

根据小学生结论，一条数轴上离每个点距离和最小的那个点就是这些点最中间那个点。证明的话用微扰法就可以发现这是个下凸函数。

nmd，一开始记成了平均数WA了两次，实际上应该是中位数啦。

```cpp
int main(){
    cin >> n ; int p ;
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%d", &base[i]), k[i] = base[i] - i ;
    sort(k + 1, k + n + 1) ;
    if (n & 1) p = k[n / 2 + 1] ;
    else p = (k[n / 2] + k[n / 2 + 1]) / 2 ;
    for (int i = 1 ; i <= n ; ++ i)
        ans += 1ll * abs(base[i] - p - i) ;
    cout << ans << endl ; return 0 ;
}
```

---

## 作者：CharlesZiy (赞：1)

### 写在前面

这道题在信息学上的难度不大，但是需要一些初一上学期的数学知识。各篇题解都大致说明了在什么时候取最小，本篇题解作为一些基础知识方面的补充，帮助某些已经遗忘了（或者还没学）这些知识的读者更好地理解其他大佬们写的题解的思路。

### 基础知识

本题主要利用了**绝对值**的**几何意义**。我们举几个例子来看一下。

方便起见，在本篇题解中，我们使用大写字母来表示数轴上的点。例如 $A$ 就表示数轴上表示数 $a$ 的点。

考虑式子 $|a - 1|$，它的几何意义是数轴上 $A$ 点和 $1$ 点之间的距离。

让我们更进一步，考虑式子 $|a - 1| + |a - 3|$，相信大家都能根据上面的情况猜出它的几何意义：数轴上 $A$ 点和 $1$ 点之间的距离加上数轴上 $A$ 点和 $3$ 点之间的距离。

让我们靠近题目的要求：求最小值。  
对于 $|a - 1| + |a - 3|$，它的最小值是什么呢？  
此处建议在草稿纸上画个数轴，想一下。很明显，当 $1 \leq a \leq 3$ 时有最小。这时，点 $A$ 落在 $1$ 和 $3$ 中间，很明显，这就是最小值了。

这是**偶数项**的情况，在奇数项的情况下，容易想到，当 $A$ 落在这一大堆数的最中间的那个数上的时候，式子就能取到最小了。  
例如 $|a - 1| + |a - 3| + |a - 5|$，此时当 $A$ 取 $3$ 时有最小。

### 正片

像很多大佬们写的一样，写出通项公式： $|A_i - (b + i)|$.  
根据这个通项公式，变形得 $|(A_i - i) - b|$.


这样，我们就将通项公式整理成为了一个易于分析的形式。根据变形后的通项公式，还原数列： $|(A_1 - 1) - b| + |(A_2 - 2) - b| + |(A_3 - 3) - b|$ $\cdots$ $|(A_N - N) - b|$.

发现没有？这样就化为了我们在基础知识一节里面讲到的形式，这样，只需要找到 $(A_1 - 1), (A_2 - 2),(A_3 - 3) \cdots (A_N - N)$ 这串数列的中位数即可。求出的中位数，就是题目中的变量 `b`。接下来，根据题意，求出式子的值就如探囊取物一般简单了。

接下来，上代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int a[200005], b[200005];
long long ans;

int main()
{
	std::ios::sync_with_stdio(false);
	
	cin >> n;
	
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		b[i] = a[i] - i;
	}
	
	sort(b + 1, b + n + 1);
	
	long long B = b[(n + 1) / 2];
	
	for (int i = 1; i <= n; i++)
	{
		ans += abs(a[i] - (B + i));
	}
	
	cout << ans << endl;
}
```

---

## 作者：atarashiTLE (赞：0)

令 $B_i=A_i-i$ ,则由函数推论知当 $b=B_{\frac{n+1}{2}}$ 时原式最小。

所以可以得出代码如下：
```cpp
#include <iostream>
#include <algorithm>
#define int long long;
using namespace std;
long long n, a[200010], b[200010];
signed main()
{
    cin >> n;
    long long i;
    for (i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i] - i;
    }
    sort(b + 1, b + 1 + n);
    long long B = b[(i + 1) / 2], ans = 0;
    for (i = 1; i <= n; i++)
        ans += abs(b[i] - B);
    cout << ans << endl;
    return 0;
}
```
注意：不开`long long`见祖宗。

---

## 作者：phigy (赞：0)

因为 $|A_i-(b+i)|=|(A_i-i)-b|$ 。

所以令 $B_i=A_i-i$ 。

将 $B_i$ 排序后就成了初一水题 。

画数轴利用图像法可得 。

当 $2|n+1$ 时 $b=B_{\frac{n+1}{2}}$ 时最小 。

当 $2|n$ 时 $B_{\frac{n}{2}}<=b<=B_{\frac{n}{2}+1}$ 时最小 。

不论怎样$b=B_{\lfloor \frac{n+1}{2} \rfloor}$ 时都最小 。

最后带入计算答案 。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
int A[200005];
int B[200005];
int b;
int ans;

int main()
{
    int i,j,k;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>A[i];
        B[i]=A[i]-i;
    }
    sort(B+1,B+n+1);
    b=B[(i+1)/2];
    for(i=1;i<=n;i++)
    {
        ans+=abs(B[i]-b);
    }
    cout<<ans;
    return 0;
}
```


---

