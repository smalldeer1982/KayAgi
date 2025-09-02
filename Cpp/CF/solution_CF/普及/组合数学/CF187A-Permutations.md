# Permutations

## 题目描述

Happy PMP is freshman and he is learning about algorithmic problems. He enjoys playing algorithmic games a lot.

One of the seniors gave Happy PMP a nice game. He is given two permutations of numbers $ 1 $ through $ n $ and is asked to convert the first one to the second. In one move he can remove the last number from the permutation of numbers and inserts it back in an arbitrary position. He can either insert last number between any two consecutive numbers, or he can place it at the beginning of the permutation.

Happy PMP has an algorithm that solves the problem. But it is not fast enough. He wants to know the minimum number of moves to convert the first permutation to the second.

## 说明/提示

In the first sample, he removes number 1 from end of the list and places it at the beginning. After that he takes number 2 and places it between 1 and 3.

In the second sample, he removes number 5 and inserts it after 1.

In the third sample, the sequence of changes are like this:

- 1 5 2 3 4
- 1 4 5 2 3
- 1 3 4 5 2
- 1 2 3 4 5

 So he needs three moves.

## 样例 #1

### 输入

```
3
3 2 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1 5 2 3 4
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
1 5 2 3 4
1 2 3 4 5
```

### 输出

```
3
```

# 题解

## 作者：nightwatch.ryan (赞：2)

## 题目描述
- 给出两个长度为 $n$ 的排列。
- 每次可以把第一个排列末尾的数移到该排列中的任意位置。
- 问需要多少次操作能使两个排列相等。
- $1 \le n \le 2 \times {10}^5$。

## 分析与思路
对于这道题，我们把它的操作看成后边不断往前移动，然后直到两个排列一样为止。所以我们不断输入 $tmp$，然后和 $a_{currentIndex}$ 进行比较，若没有成功则让后一位往前移即可。
## 代码
```cpp
#include<iostream>
const int MAXN=2e5+5;
int a[MAXN],b[MAXN],n,res,currentIndex=1; 
int main(){
	std::cin>>n;
	for(register int i=1;i<=n;i++)
		std::cin>>a[i];
	int tmp;
	for(register int j=1;j<=n;j++){
		std::cin>>tmp;
		if(tmp==a[currentIndex])
			currentIndex++;
	}
	std::cout<<n-currentIndex+1;
}
```

---

## 作者：_txb_ (赞：1)

~~又是一道大水题~~

[题目传送门](https://www.luogu.com.cn/problem/CF187A)
## 题意
- 给出两个长度为 $n$ 的排列。
- 每次可以把第一个排列末尾的数移到该排列中的任意位置。
- 问需要多少次操作能使两个排列相等。
- $1 \le n \le 2 \times {10}^5$。

## 思路
我们把第一个数组当做最后排序，然后用第二个数组来跟第一个数组作比较，如果不一样就在找下一个数，如果一样 $sum$ 就加一。

贴代码
```cpp
#include<bits/stdc++.h>//头文件 
using namespace std;
int n,sum=1,a[200005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];//输入 
    for(int i=1;i<=n;i++)
    { 
        int x;
        cin>>x; 
        if(a[sum]==x) sum++;//如果一样sum+1，不一样就不用管了 
    }
    cout<<n-sum+1;//输出 
    return 0;
}
```


---

## 作者：Sammy_prime (赞：1)

[CF187A](https://www.luogu.com.cn/problem/CF187A)

# 思路

通过题意，我们可以把输入的第一组排列看作为最终的目标排列，对于第二组排列，我们可以从这组排列的末尾数依次向前移动，每次移动，就对第一组排列进行比较，一直到两个排列完全相等，才不操作。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,x,a[N],cnt=1;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
      if(a[cnt]==x) cnt++;
	}
	printf("%d\n",n-cnt+1);
	return 0;
}
```


---

## 作者：OIer6666 (赞：1)

## 题目：
- 给出两个长度为 $n$ 的排列。
- 每次可以把第一个排列末尾的数移到该排列中的任意位置。
- 问需要多少次操作能使两个排列相等。
- $1\le n\le 2\times 10^5$。

## 解题思路：
我们将第一个输入的数组（数组 $a$）作为最终目标。然后我们输入一个数，和 $a_{ans}$ 进行比较：

- 若相等，将 $ans$ 加上 $1$。
- 否则，将比较下一个数。（因为这次输入的数被移走了）

最后，输出 $n+1-ans$。

## 代码：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#define ll long long
using namespace std;
ll a[208200],n,ans;
inline ll read(){
	ll f=1,s=0;char ch=getchar();
	while(ch<'0'&&ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s*=10,s+=ch-'0',ch=getchar();
	return f*s;
}
inline void write(ll s){
	if(s>=10)write(s/10);
	putchar(s%10+'0');
}
int main(){
//	ios::sync_with_stdio(false);
	n=read();
	ans=1;
	for(ll i=1;i<=n;i++)
		a[i]=read();
	for(ll i=1;i<=n;i++){
		ll temp=read();
		if(temp==a[ans])ans++;
	}
	write(n+1-ans);
	return 0;
}
```

---

## 作者：XXh0919 (赞：1)

~~超级水的灰题~~

# 题意

给定两个长度为 $n$ 的排列，将第一个排列的末尾的数移动到排列的任意一个位置，问你要移动多少次，使得排列 $a$ 等于排列 $b$。

# 分析

我们可以将第一个排列作为基准排列，并将另一个排列的末尾数从末尾不断往前移，直到两个排列相等。所以我们可以不停输入 $temp$，并将 $a_{ans}$ 与 $temp$ 进行比较，如果相等， $ans$ 就加 $1$，进行下一位的判断，若不相等，则直接进行下一位的判断。

**注意**：如果你是从第 $n$ 位进行比较，那么 $ans$ 就得赋值为 $n$，否则会出错！！

写了“**亿**”天的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long temp,a[2522225],n,ans=1;
//开好 long long 保险
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	   cin>>a[i];
	for(int i=1;i<=n;++i)
	{
		cin>>temp;
		if(temp==a[ans])ans++;
	}
	cout<<n-ans+1;
	return 0;
 } 
```

看在我今天参加 CSP-J 的份上，管理员求过！！！！！

---

## 作者：icefake (赞：1)

# CF187A Permutations

标签（空格分隔）： 题解

---

## 先来翻译一下题意：

给出两个长度都为 $n$ 的仅由 0~9 组成的数字串 $a$ 和 $b$ ，你可以对 $b$ 中的任意一个数字做出以下操作之一：

 - 将它插入到两个数字之间
 - 将它放到末尾处
 - 将它放到开头处

问：最少要多少次操作才能使 $b$ 与 $a$ 一模一样

## 分析一下
~~这很明显是一道水题。。。~~

对于这道题，我们可以把它的这种操作看成是**后边不断往前移动数据**，然后到 $b$ 和 $a$ 一样为止。

所以，我们可以从 $a[1]$ 和 $b[1]$ 开始比较，如果未匹配成功就让后面的一位往前移。

## 代码如下
```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn = 200010;
int n, tem = 1, tmp = 1, ans = 0;
int a[maxn], b[maxn];

int read()
{
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x * w;
}

inline void write(int x)
{
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);
}

signed main()
{
    n = read();
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
    }
    for(int i = 1; i <= n; i ++) {
        b[i] = read();
    }
    while(tmp <= n && tem <= n) {
        if(a[tmp] == b[tem]) {
            tem ++;
            tmp ++;
            continue;
        }
        if(a[tmp] == -1) {
            tmp ++;
            continue;
        }
        for (int i = tmp + 1; i <= n; i ++)
        {
            if (a[i] == b[tem])
            {
                ans ++;
                a[i] = -1;
                tem ++;
                break;
            }
        }
    }
    write(ans);
    return 0;
}
```


---

## 作者：SMall_X_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/solution/CF187A)

---
## 题目大意

如题意翻译。

## 思路分析

很水的一道题目，可以将第一个排列 $a$ 看作最终排列，接下来每输入一个数，让它与 $a_m$ 进行比较，直到两个排列相同。

最后看题目范围，$1≤n≤2\times10^5$，时间复杂度 $\mathcal{O(n)}$，空间复杂度 $\mathcal{O(n)}$。


代码：
```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main() 
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m=1;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		int t;
		cin>>t;
		if(a[m]==t)
		{
			m++;
		}
	}
	cout<<n-m+1;
	return 0;
}
```

---

## 作者：Rookie_t (赞：0)

根据题意，我们可以把输入的第一个 $a$ 数组看做最终的排列，对于输入的第二组，我们可以模拟位于这组排列末尾的数向前移动，每次移动，就和第一组进行对比，知道完全相同为止。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 200010
int n,t,a[maxn],cnt = 1;
int main(){
        ios::sync_with_stdio(0);
	cin>>n;
	for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
        } 	
	for(int i = 1;i <= n;i++){
            scanf("%d",&t);
        } 
        if(a[cnt] == t){
            cnt++;
	}
        cout<<n-cnt+1;
	return 0;
}
```


---

## 作者：zhang_Jimmy (赞：0)

# 思路：

我们可以先将第一个排列作为我们最终的目标，然后对第二个排列进行操作。**以下用 $a$ 代替输入的第一个排列，$b$ 代替输入的第二个排列。**

首先考虑 $b$ 中第几个元素可以和 $a_{cnt}$ 配对（这里的 $a_{cnt}$ 是目前配对的元素），如果配对上了，就可以令 $cnt \gets cnt + 1$，开始匹配下一个元素。

由于匹配上的元素都是不用操作的，易得答案为 $n - cnt + 1$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, a[200010];

int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	int cnt = 1;
	for(int i = 1; i <= n; i ++){
		int x;
		cin >> x;
		if(x == a[cnt]) cnt ++;
	}
	cout << n - cnt + 1;
	return 0;
}

```


---

## 作者：wangjue233 (赞：0)

# Solution
[题目传送门](https://www.luogu.com.cn/problem/CF187A)
## 题目思路
这道题的关键是要找出两个排列之间的最长公共后缀的长度。"最长公共后缀"指的是从排列末尾开始，两个排列共同拥有的连续相同数列的长度。因为这部分数列已经是排序好的，所以不需要任何移动。

为了找到最长公共后缀，我们可以同时从两个排列的末尾开始比较，如果相同则继续向前比较，直到找到第一个不同的数为止。不同的数的位置就代表需要移动的操作的开始的地方。

## 代码实现

我们可以写出伪代码：
```cpp
cin >> n;
//输入第一个排列
int cnt = 1;
for i = 1 i <= n i++
    //读入 t
    //如果 t = a 的第 cnt 项 则 cnt++
    //继续输入第二个排列的下一个数
    //一旦两个排列在某个位置不同，就停止比较
//需要的最小移动次数就是 n - cnt + 1
//输出最小移动次数
```
根据上面的伪代码我们可以写出代码：
```cpp
#include<iostream>
using namespace std;
const int maxn = 2 * 1e5 + 10;
int a[maxn];
int main(){
    int n; cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int cnt = 1;
    for(int i = 1; i <= n; i++){
        int t; cin >> t;
        if(t == a[cnt]) cnt++;
        else break; //当遇到不相等的数时，停止比较
    }
    int ans = n - cnt + 1; //计算最小移动次数
    cout << ans << "\n";
    return 0;
}
```
但是很明显，这个代码连样例都过不去，那么到底是错在哪了呢？

注意，代码中有一个很明显的错误：在比较两个排列的过程中，不应该在发现第一个不匹配的数时就跳出循环。因为公共后缀的开始可能在第一个排列的**任意位置**，所以即使当前元素不匹配，也应该继续检查后续的元素是否开始匹配。代码中的 `else break;` 是错误的，应该去掉这个语句。

修改完之后，我们就可以得到正确的代码啦：
```cpp
#include<iostream>
using namespace std;
const int maxn = 2 * 1e5 + 10;
int a[maxn];

int main(){
    int n; cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int cnt = 1;
    for(int i = 1; i <= n; i++){
        int t; cin >> t;
        if(t == a[cnt]) cnt++;
    }
    int ans = n - cnt + 1; // 计算最小移动次数
    cout << ans << "\n";
    return 0;
}
```
时间复杂度为 $O(n)$，空间复杂度也为 $O(n)$。可以通过本题。

---

## 作者：Forever_LYD (赞：0)

题目好理解，也比较简单，思路就是以输入的序列为基准，将其与另一个序列进行一一比较，不相同则继续操作，相同则停止。

参考代码：[link](https://www.luogu.com.cn/paste/0fomsku3)


---

## 作者：zzx_ (赞：0)

# 题意
给定两个长度为 $n$ 的排列，将第一个排列的末尾的数移动到排列的任意一个位置，要移动多少次，使得排列 $a$ 等于排列 $b$。
# 做法
对于这道题，我们把它的操作看成末尾不断往前移动，然后直到两个排列一样。所以我们不断输入 $p$ ，然后和 $a_j$ 进行比较，若成功，则 $j$ 加一； 若没有成功，则直接进行下一位的判断。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],j=1;//要从第一位开始
int p;
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
	}
	for(int i=1; i<=n; i++) {
		cin>>p;
		if(a[j]==p) {//如果成功，j++
			j++;
		}
	}
	cout<<n-j+1;
	return 0;
}

```


---

## 作者：jasonshen_ (赞：0)

~~一道很水的题~~
### 题意
- 给出两个长度为 $n$ 的排列。
- 每次可以把第一个排列末尾的数移到该排列中的任意位置。
- 问需要多少次操作能使两个排列相等。
- $1 \le n \le 2 \times {10}^5$。

### 思路
我们可以将第一个排列作为最终排列，并将另一个队列的末尾数从末尾不断往前移，每次移动一位，然后比较。如果不相同，继续操作，直到两个排列相等。我这里用了两个循环。

### 代码
 ```cpp
#include <iostream>
using namespace std;
 
int main() {
	int n,x,i,j=0;
	cin>>n;
	int a[n];
	for(i=0;i<n;i++)cin>>a[i];
	for(i=0;i<n;i++){ cin>>x; if(a[j]==x)j++;}
	cout<<n-j;
	return 0;
}
 

 ```


---

## 作者：yingkeqian9217 (赞：0)

# 前言

~~是来水的。~~ 看远古题没什么像样的题解，所以来水一发。

# 题目描述

题目传送门：

[Codeforces](http://codeforces.com/problemset/problem/187/A)

[洛谷](https://www.luogu.com.cn/problem/CF187A)

- 给出两个长度为 $n$ 的排列。
- 每次可以把第一个排列末尾的数移到该排列中的任意位置。
- 问需要多少次操作能使两个排列相等。
- $1 \le n \le 2 \times {10}^5$。

# 分析

由于是 A 题，所以猜测是贪心。事实上，我们可以很容易使 $b$ 转化成 $1$ 至 $n$ 的顺序排列，即单调递增的序列。

观察操作，发现每次操作可以将一个末端的元素移动到前面。以我们可以在 $a$ 的开头维护一个单调递增的连续序列，每次将末端的元素，插到前面正确的位置上，操作次数即为后面剩余元素个数。

那么我们计算开头的单调递增的序列，即可算出答案。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000001],b[1000001],ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		b[x]=i;
	}
	for(int i=2;i<=n;i++)
	 if(b[a[i]]<b[a[i-1]]){
	 	ans=n-i+1;
	 	break;
	 }
	printf("%d\n",ans);
	return 0;
}
```

---

