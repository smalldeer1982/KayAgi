# A-B-C Sort

## 题目描述

You are given three arrays $ a $ , $ b $ and $ c $ . Initially, array $ a $ consists of $ n $ elements, arrays $ b $ and $ c $ are empty.

You are performing the following algorithm that consists of two steps:

- Step $ 1 $ : while $ a $ is not empty, you take the last element from $ a $ and move it in the middle of array $ b $ . If $ b $ currently has odd length, you can choose: place the element from $ a $ to the left or to the right of the middle element of $ b $ . As a result, $ a $ becomes empty and $ b $ consists of $ n $ elements.
- Step $ 2 $ : while $ b $ is not empty, you take the middle element from $ b $ and move it to the end of array $ c $ . If $ b $ currently has even length, you can choose which of two middle elements to take. As a result, $ b $ becomes empty and $ c $ now consists of $ n $ elements.

 Refer to the Note section for examples.Can you make array $ c $ sorted in non-decreasing order?

## 说明/提示

In the first test case, we can do the following for $ a = [3, 1, 5, 3] $ :

Step $ 1 $ :

$ a $  $ [3, 1, 5, 3] $  $ \Rightarrow $  $ [3, 1, 5] $  $ \Rightarrow $  $ [3, 1] $  $ \Rightarrow $  $ [3] $  $ \Rightarrow $  $ [] $

$ b $  $ [] $ $ \Rightarrow $ $ [\underline{3}] $ $ \Rightarrow $ $ [3, \underline{5}] $ $ \Rightarrow $ $ [3, \underline{1}, 5] $ $ \Rightarrow $ $ [3, \underline{3}, 1, 5] $
 
Step $ 2 $ :

$ b $  $ [3, 3, \underline{1}, 5] $  $ \Rightarrow $  $ [3, \underline{3}, 5] $  $ \Rightarrow $  $ [\underline{3}, 5] $  $ \Rightarrow $  $ [\underline{5}] $  $ \Rightarrow $  $ [] $

$ c $  $ [] $ $ \Rightarrow $ $ [1] $ $ \Rightarrow $ $ [1, 3] $ $ \Rightarrow $ $ [1, 3, 3] $ $ \Rightarrow $ $ [1, 3, 3, 5] $

As a result, array $ c = [1, 3, 3, 5] $ and it's sorted.

## 样例 #1

### 输入

```
3
4
3 1 5 3
3
3 2 1
1
7331```

### 输出

```
YES
NO
YES```

# 题解

## 作者：include_BM (赞：13)

不难发现 $2$ 操作其实是 $1$ 操作的逆操作，故问题变为 $c$ 数组与 $a$ 数组能否得到相同的 $b$ 数组。

由于 $b$ 中头尾两个元素一定是原数组末尾的两个元素，故依次比较 $a,c$ 末尾两个元素，判断是否能匹配即可。

```cpp
n=read(),ok=1;
for(int i=1;i<=n;++i) a[i]=c[i]=read();
sort(c+1,c+n+1);
for(int i=n;i>=2;i-=2)
    ok&=((a[i]==c[i]&&a[i-1]==c[i-1])||(a[i]==c[i-1]&&a[i-1]==c[i]));
ok?puts("YES"):puts("NO");

```

---

## 作者：Orange_qwq (赞：11)

[题目链接](https://www.luogu.com.cn/problem/CF1674D)

## 思路分析

容易看出，当 $b$ 长度为奇数时，将 $a$ 数组中的元素插入 $b$ 数组，有 $2$ 种情况，可以插在前面，也可以插在后面。

然后从 $b$ 数组中取出，放到 $c$ 数组时，与上面的情况，要么这两个数非降序，要么反之。

所以每 $2$ 个数从 $a$ 到 $c$ 时，可以贪心地想到要将这两个数非降序地排到 $c$ 数组里。

为啥是 每 $2$ 个数？因为只有 $b$ 长度为奇数时我们可以决定他的位置，当 $b$ 长度为偶数时，只能插到中间去。

接下来就容易想了，从 $a$ 数组到 $c$ 数组，最优策略就是将 $a$ 的每两个数排序放到 $c$ 里。长度大于 $2$ 的子数组是无法改变他的位置的。如果最后 $c$ 数组是升序的，输出 $\texttt{YES}$，否则输出  $\texttt{NO}$。

## $\texttt{AC Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010], n, f;
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = n; i >= (n & 1) + 1; i -= 2) // (n & 1) + 1  相当于 n % 2 + 1 如果长度为奇数
			if (a[i] < a[i - 1]) swap(a[i], a[i - 1]); // 的话就需要有一个是分为 1 组的，不交换 
		f = 1;
		for (int i = 1; i < n; ++i)
			if (a[i] > a[i + 1]) f = 0; // 判断是否非降序
		puts(f ? "YES" : "NO");
	}
}
```


---

## 作者：Chronomaly_Atlandis (赞：3)

可以发现，$b$ 的头尾元素一定是 $a$ 末尾的两个元素。所以只要从后往前依次遍历 $a$ 和 $c$ 末尾的两个元素，判断是否对的上就行。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,a[maxn],c[maxn],T;
int main(){
	cin.tie(NULL);
	cin >> T;
    while(T--){
    	bool check=1;
    	memset(a,0,sizeof(a));
    	memset(c,0,sizeof(c));
    	cin >> n;
    for(int i=1;i<=n;i++){
    cin >> a[i];
    c[i]=a[i];
}
    sort(c+1,c+n+1);
for(int i=n;i>=2;i-=2)
if(!((a[i]==c[i]&&a[i-1]==c[i-1])||(a[i]==c[i-1]&&a[i-1]==c[i]))){
	check=0;
	break;
}
if(check)cout << "YES\n";
else cout << "NO\n";
}
return 0;
}
```

---

## 作者：静谧幽蓝 (赞：3)

## 题意简述

+ 给你一个数组 $a$，要你依次从末尾取出元素放到数组 $b$ 的中间（如果长度为偶数可以放中间的两边）。
+ 再依次把数组 $b$ 的中间那个数（如果长度为偶数可以取中间的两边）放到数组 $c$ 的末尾。
+ 求有没有一种方法可以使得数组 $c$ 中的数形成 **不下降序列** 。

## 解法

对相邻的两个数分组（如果个数为单数则第一个数省略），题目就转化成可以把其中几个组翻转，有没有一种方法使得序列不下降。

首先我们用 $[1,3,2,4,5]$ 来做示范。

+ 首先分组，数组变成这样（不同颜色表示不同组）：$[1,\color{red}3,2\color{black},\color{blue}4,5\color{black}]$

+ 翻转组 $(3,2)$，数组变得不下降 $[1,\color{red}2,3\color{black},\color{blue}4,5\color{black}]$，则答案为 `YES`。

下面我们来证这个做法。

首先，题目说要把 $a$ 中元素的放到 $b$ 里面去，而在放的时候，同一组的元素肯定是放的一左一右，然后被其他的元素分开，就比如上面例子中放到 $b$ 里面去可能是这样：$[\color{blue}5\color{black},\color{red}3\color{black},\color{black}1\color{black},\color{red}2\color{black},\color{blue}4\color{black}]$

而后面的第二次操作就是把依次把各个组给取出来，因为他先取中间的数，所以在中间的数都取完时，肯定会有两个同组的数并到一起被取出，但是取的顺序可能不同，因为他只有两种结果，一个翻转，一个保持原样，所以只用判断每一个组就可以了。

## Code

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
void work()
{
    /* Code */
    int n,temp=0;
    int a[200010];
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>a[i];
    if(n%2==1)
        temp=a[1];
    for(int i=1+(int)(n%2==1); i<=n; i+=2)
    {
        if(a[i]<temp||a[i+1]<temp)
        {
            cout<<"NO"<<endl;
            return;
        }
        temp=max(a[i],a[i+1]);
    }
    cout<<"YES"<<endl;
    return;
}
 
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)
        work();
    return 0;
}
```

---

## 作者：FReQuenter (赞：1)

## 思路

我们先看第二次操作， $b$ 变成 $c$ ，相当于是把 $b$ 从中间两两分组，如下：

$$[{1},{\color{red}2},{\color{green}3},{\color{red}4},5],[{1},{\color{red}2},{\color{green}3,4},{\color{red}5},6]$$

然后按照 绿-红-黑 的顺序形成 $c$ 数组。

下面我们再看 $b$ 数组是如何得到的。

由 $a$ 数组依次插入到 $b$ 数组，相当于也是以 绿-红-黑 的顺序插入。而由于插入和取出顺序相同，能改变的只有一组中两个数的顺序。

综上，只要将 $a$ 如下所示划分：

$$[{\color{red}1},{\color{green}2},{\color{green}3},{4},{5}],[{\color{red}1},{\color{red}2},{\color{green}3},{\color{green}4},{5},{6}]$$

由于形成的 $c$ 也是 红-绿-黑 的顺序，所以只要能够交换 $a$ 中每一组组内的两个数的顺序使 $a$ 是不下降的，就一定能形成一个不下降的 $c$ 数组。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[200005];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        bool f=true;
        for(int i=1;i<=n;i++) cin>>a[i];
        if(n<=2);//一定可以组成
        else if(n&1){//若n是奇数，则第一组只有1个数
            for(int i=2;i<n;i+=2) if(a[i]>a[i+1]) swap(a[i],a[i+1]);//若组中第一个数>第二个数，则交换
            for(int i=1;i<n;i++){
                if(a[i]>a[i+1]){
                    f=false;
                    break;
                }
                //检查数列是否合法
            }
        }
        else{//若n是偶数，则每组两个数
            for(int i=1;i<n;i+=2) if(a[i]>a[i+1]) swap(a[i],a[i+1]);//若组中第一个数>第二个数，则交换
            for(int i=1;i<n;i++){
                if(a[i]>a[i+1]){
                    f=false;
                    break;
                }
                //检查数列是否合法
            }
        }
        if(f) cout<<"YES\n";
        else cout<<"NO\n";
    }
}

```

---

## 作者：CmsMartin (赞：1)

## 题目描述

建议自行阅读。

[题目传送门1](https://www.luogu.com.cn/problem/CF1674D)

[题目传送门2](http://codeforces.com/problemset/problem/1674/D)

## 思路

以不变应万变，考虑 $a$ 与 $b$ 的关系。

观察可以发现，$a$ 从后往前的每两位在 $b$ 中是前后对称的。比如说，$a_n\ a_{n-1}$ 就会对应 $b_1 \ b_n$ ，$a_{n-1}\ a_{n-2}$ 就会对应 $b_2 \ b_{n-1}$（顺序不一定），其余同理。 

再观察 $b$ 和 $c$ 的关系，发现 $b$ 对称的两个数，在 $c$ 中是相邻的，并且从中间向两边加入 $c$，那我们就可以贪心构造 $c$ 了。最后观察其是否合法。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int T;
int N;
int Num[200010];
int B[200010];


int main() {

    scanf("%d" ,&T);

    while (T--) {
        scanf("%d" ,&N);
        for(int i = 1; i <= N; i++) {
            scanf("%d" ,Num + i);
        }

        for(int i = N , j = 1 , k = N; i >= 1; i -= 2 , j++ , k--) {
            B[j] = Num[i];
            B[k] = Num[i - 1];
        }

        if(N % 2 == 1) B[N / 2 + 1] = Num[1];

        if(N % 2 == 0) {
            int Max = 0;
            for(int i = N / 2, j = N / 2 + 1; i >= 1 , j <= N; i-- , j++) {
                if(min(B[i] , B[j]) < Max) {
                    printf("NO\n");
                    goto end;
                }
                Max = max(B[i] , B[j]);
            }
        }
        else {
            int Max = 0;
            for(int i = N / 2 + 1, j = N / 2 + 1; i >= 1 , j <= N; i-- , j++) {
                if(min(B[i] , B[j]) < Max) {
                    printf("NO\n");
                    goto end;
                }
                Max = max(B[i] , B[j]);
            }
        }

        printf("YES\n");

        end:
            continue;
    }
    return 0;
}
```


---

## 作者：fast_photon (赞：1)

**Upd 2022.5.18 $\LaTeX$ 炸了一个**（描述 $b$ 的中间那里）  
**0.前言**  
写题解永远不会注重结论是什么，重头戏也不是如何推导结论，而是如何证明结论正确。  

**1.题意**  
[原题](https://www.luogu.com.cn/problem/CF1674D)  
给定一个数组 $a$ 问能否经过下列的操作使 $c$ 数组成为一个单调不减的数组。  
重复执行直到 $a$ 为空：将 $a$ 的最后一个元素取出并放入$b$ 的中间，其中 $b$ 的中间指 $b\{^{\text{ 的正中间（当}b\text{ 拥有偶数个元素）}}_{ \text{ 正中间元素的两侧之一的位置，可以自选左或右（当}b\text{ 拥有奇数个元素）}}$  
接下来，重复执行直到 $b$ 为空：将 $b$ 中间的元素（这里奇数个时指正中间，偶数个指正中间两个任选一个）拿出放入C数组的末尾。  
经过上述操作使C数组变得有序，可能则输出 `YES` 不可能输出 `NO`。  

**2.推结论**  
对于 $n=2$，$n=3$，$n=4$ 分别枚举所有情况：  
$n=2$：$\{a, b\}$ 可能变成 $\{a, b\}, \{b, a\}$  
$n=3$：$\{a, b, c\}$ 变成 $\{a, b, c\}, \{c, b, a\}$  
$n=4$：$\{a, b, c, d\}$ 变成 $\{a, b, c, d\},\{b, a, c, d\},\{a, b, d, c\},\{b, a, d, c\}$  
那么就可以进行一个初步的推测：相邻且这两个数后面有偶数个数的两个数在操作之后可能互换位置。  

**3.证结论**  
首先，我们不难发现，当 $n$ 为奇数的时候，数组第一个数被放进去时一定有偶数个数，只能放在正中间，然后就一定是最先拿出来的，放在 $c$ 数组的第一个。所以处理奇数个就等于第一个最小+去掉第一个处理偶数个。  
我们接下来只分析偶数情况。  
考虑接下来该放入 $a_{2i+1}$ 和 $a_{2i}$ 的时候。  
因为只考虑偶数情况，所以已经放入了偶数个元素。  
正中间正好有一个空位（固定的）可以放入 $a_{2i+1}$。而放入$a_{2i+1}$ 之后 $a_{2i}$ 一定在他左边或者右边（紧挨着）。  
同理可得它们之间会插入剩下的全部元素。  
最后取出的时候，它们两个一定在原来的两个位置上，但是顺序可能调换。  
对于排过序的数组，一定满足 $a_{2i}\le a_{2i+1}$。  
所以对于任意的 $a_{2i}>a_{2i+1}$ 就 $swap(a_{2i},a_{2i+1})$。  
然后判断交换完的数组是否完全等于排过序的数组（一一枚举）  
相等输出 `YES`，不等输出 `NO`。  
做完啦！放个代码（真的很简单，会了就不要看下面了）  
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>

using namespace std;

int n, a[200005], b[200005];

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		sort(b, b + n);
		int I = 0;
		if(n & 1) I++;
		for(; I < n; I += 2) {
			if(a[I] > a[I + 1]) swap(a[I], a[I + 1]);
		}
		bool flag = false;
		for(int i = 0; i < n; i++) {
			if(a[i] != b[i]) {
				printf("NO\n");
				flag = true;
				break;
			}
		}
		if(!flag) printf("YES\n");
	}
}

---

## 作者：AlephRei (赞：0)

这个题首先来看看这个转化操作，有两次，那 无论如何都会枚举一下中间的情况 （蒟蒻之言不必在意）反正就很不好写，那就把这两次转化看成一次，来~~逝世~~。

发现这个东西逆操作很明显，但是为什么c最终不是原来的样子？因为中间插入的位置随你。那我们可以看看。发现最终结果两个相邻的数结果还是相邻。那就可以贪心，只要逆序对就swap。

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 200010
int a[MAXN];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		int last=n%2+1;
		for(int i=n;i>=last;i-=2){
			if(a[i]<a[i-1]){
				swap(a[i],a[i-1]);
			}
		}
		bool flag=true;
		for(int i=1;i<n;i++){
			if(a[i]>a[i+1]){
				flag=false;
			}
		}
		if(flag){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
}
```
有些时候Ctrl-R是个好东西（特别对于洛谷上的CF） 

---

## 作者：Tx_Lcy (赞：0)

这题只需要一点点思路便可解出。

### 思路

首先我们假设原序列的长度为四，这四个数分别为 $a,b,c,d$。

那么 $b$ 序列就有下列几种可能性：

$\bullet$ $d,b,a,c$

$\bullet$ $d,a,b,c$

$\bullet$ $c,b,a,d$

$\bullet$ $c,a,b,d$

与之相对应的，$c$ 序列也有下列几种可能性：

$\bullet$ $a,b,c,d$

$\bullet$ $a,b,d,c$

$\bullet$ $b,a,c,d$

$\bullet$ $b,a,d,c$

这样，我们发现了一个有趣的规律，由 $a$ 序列变成 $b$ 序列再变成 $c$ 序列，$c$ 序列的任意相邻两个数都是在 $a$ 序列中的相邻两个数。

所以，我们从后往前枚举，若这两个数是逆序的，那么交换这两个数。最后判断一下最终序列是否合法即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=1e6+10;
int a[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;cin>>t;
    while (t--){
    	int n;cin>>n;
    	for (int i=1;i<=n;i++) cin>>a[i];
    	int k=0,tk=1;
    	if (n%2==1) tk=2;//若 n 是奇数，则不能枚举到 1
    	for (int i=n;i>=tk;i-=2)
    	    if (a[i]<a[i-1]) swap(a[i],a[i-1]);//用贪心的思想尽可能把 a 序列变得合法
        int tag=1;//标记是否合法
        for (int i=1;i<n;i++)
            if (a[i]>a[i+1]) tag=0;//如果仍存在逆序对，则原序列无法变得合法
        if (tag) cout<<"YES\n";
        else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：yzyjh (赞：0)

我们可以对 $n\le4$ 的情况进行枚举。下文中的数字均代指数组下标。

- $n=1$

原数组只能变成 [1]。因此，永远输出 YES。

- $n=2$

原数组可以变成 [1,2] 和 [2,1]。可以发现，必然有一种方法使得原数组为升序。因此，也永远输出 YES。

- $n=3$

B 数组可以变成：[3,1,2] 或 [2,1,3]。

C 数组可以变成：[1,2,3] 或 [1,3,2]。

可以发现，最中间的元素永远是被最先取出的，两边的其次。判断第一个数是否是最小的即可。但这里的证据仍不够有力，要继续枚举。

- $n=4$

B 数组可以变成：[4,1,2,3] 或 [4,2,1,3] 或 [3,2,1,4] 或 [3,1,2,4]。

可以发现，中间两个永远是前两个数，旁边两个是后两个数。

C 数组可以变成：[1,2,3,4] 或 [1,2,4,3] 或 [2,1,3,4] 或 [2,1,4,3]。

因此，只要判前两个是否是最小的两个，后两个是否是最大的两个即可。

于是得出结论：对于奇数，如果第一个是最小的且后面每两个排序后整个数组是有序的，输出 YES；偶数同理。

代码：

```cpp
// Problem: D. A-B-C Sort
// Contest: Codeforces - Codeforces Round #786 (Div. 3)
// URL: https://codeforces.com/contest/1674/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define rep(i,n) for(int i=0,_##i##__end=(n);i<_##i##__end;++i)
#define per(i,n) for(int i=(n)-1;i>=0;--i)
#define rep1(i,n) for(int i=1,_##i##__end=(n);i<=_##i##__end;++i)
#define per1(i,n) for(int i=(n);i>=1;--i)
#define pb push_back
#define mp make_pair
#define debugv(x) cout<<#x<<'='<<x<<",line "<<__LINE__<<endl
#define debug cout<<"at line "<<__LINE__<<" in function "<<__FUNCTION__<<endl
#define nextp next_permutation
#define pq priority_queue
#define fi first
#define se second
#define Yes cout<<"Yes"<<endl
#define No cout<<"No"<<endl
#define YES cout<<"YES"<<endl
#define NO cout<<"NO"<<endl
typedef long long ll;
using namespace std;
const ll mod1=998244353;
const ll mod2=1000000007;
int a[200005],b[200005];
void solve()
{
	int n;
	cin>>n;
	rep1(i,n)
	{
		cin>>a[i];
		b[i]=a[i];
	}
	if(n<=2)//小于等于2必定有解
	{
		YES;
	}
	else
	{
		sort(b+1,b+n+1);//先进行排序，方便比较
		if(n%2==0)//偶数
		{
			for(int i=1;i<=n;i+=2)//从头开始
			{
				if(a[i]>a[i+1])//不是有序的
				{
					swap(a[i],a[i+1]);
				}
				if(a[i]!=b[i]||a[i+1]!=b[i+1])//与有序的不相同
				{
					NO;//无解
					return;
				}
			}
			YES;
		}
		else
		{
			if(a[1]!=b[1])//第一个不是最小的
			{
				NO;
				return;
			}
			for(int i=2;i<=n;i+=2)//从第二个开始枚举
			{
				if(a[i]>a[i+1])//同理
				{
					swap(a[i],a[i+1]);
				}
				if(a[i]!=b[i]||a[i+1]!=b[i+1])
				{
					NO;
					return;
				}
			}
			YES;
			return;
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

