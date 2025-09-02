# Flamingoes of Mystery

## 题目描述

This is an interactive problem. You have to use a flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout), in Java — System.out.flush(), in Pascal — flush(output) and in Python — sys.stdout.flush().

Mr. Chanek wants to buy a flamingo to accompany his chickens on his farm. Before going to the pet shop, Mr. Chanek stops at an animal festival to have fun. It turns out there is a carnival game with a flamingo as the prize.

There are $ N $ mysterious cages, which are numbered from $ 1 $ to $ N $ . Cage $ i $ has $ A_i $ $ (0 \le A_i \le 10^3) $ flamingoes inside $ (1 \le i \le N) $ . However, the game master keeps the number of flamingoes inside a secret. To win the flamingo, Mr. Chanek must guess the number of flamingoes in each cage.

Coincidentally, Mr. Chanek has $ N $ coins. Each coin can be used to ask once, what is the total number of flamingoes inside cages numbered $ L $ to $ R $ inclusive? With $ L < R $ .

## 说明/提示

In the sample input, the correct flamingoes amount is $ [1, 4, 4, 6, 7, 8] $ .

## 样例 #1

### 输入

```
6
 
5
 
15
 
10
 ```

### 输出

```
 
? 1 2
 
? 5 6
 
? 3 4
 
! 1 4 4 6 7 8```

# 题解

## 作者：RioFutaba (赞：1)

## 题意
交互题。有一个未知的正整数序列。给定序列长度 $n$，每次可以询问 $L$ 到 $R$ 的和（$L < R$），最多询问 $n$ 次。最后输出整个序列。
## 思路
设 $res_i$ 表示 $1$ 到 $i$ 的和。那么显然的，$a_i=res_i-res_{i-1}$。但因为询问的左端点不能与右端点相等，所以询问 $i$ 到 $n$ 的和（$i>1$）只可以通过此方法求出 $i>2$ 时的 $a_i$。

但是可以把最后一次询问机会用于求 $2$ 到 $n$ 的和，最后用 $res_n$ 减去这个和就可以求出 $a_1$ 了，再用 $res_2$ 减去 $a_1$ 就可以求出 $a_2$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e3+5;
int n,a[maxn],res[maxn],x;
int main(){
	cin >> n;
	for(int i=2;i<=n;i++){ 
		cout << "? 1 " << i << endl; //询问和
		cin >> res[i];//记录res
		a[i]=res[i]-res[i-1]; //求出ai，注意此时a2是1~2的和
	}
	cout << "? 2 " << n << endl; //询问2~n的和
	cin >> x;
	a[1]=res[n]-x; //求a1
	a[2]-=a[1]; //求a2
	cout << "!";
	for(int i=1;i<=n;i++) cout << " " << a[i]; //输出
	cout << endl;
	return 0;
}
```

---

## 作者：ZQIN_P (赞：1)

[在我的博客中阅读](https://zqin-blog.netlify.app/2023/08/24/cf1425f-flamingoes-of-mystery-%E9%A2%98%E8%A7%A3/)

[题目传送门](https://www.luogu.com.cn/problem/CF1425F)

## 题目大意：
这是一道交互题。通过输出 ```? a b```（$a$、$b$ 表示起始位置（含）和终止位置（含））向评测机获取该区间的和，最多可以询问 $n$ 次，要求求出数组中的所有元素并输出。

## 思路：
由于获取的是区间和，我们不难想到使用前缀和和差分的知识来求解。我们通过询问依次获得 $1 \sim 2$、$1 \sim 3$、$1 \sim 4$……$1 \sim n$ 的和，并对相邻的两个和做差分，即可求出 $3$ 至 $n$ 项的元素。最后通过询问第 $2 \sim 3$ 项元素之和，算出第 $1$、$2$ 项元素并输出。

完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int main(){
    int n,num1,num2,num;
    cin>>n;
    cout<<"? 1 2"<<endl;
    cin>>num1;
    num=num1;
    for(int i=3;i<=n;i++){
        cout<<"? 1 "<<i<<endl;
        fflush(stdout);
        cin>>num2;
        a[i]=num2-num1;
        num1=num2;
    }
    cout<<"? 2 3"<<endl;
    cin>>num2;
    a[2]=num2-a[3];
    a[1]=num-a[2];
    cout<<"!";
    for(int i=1;i<=n;i++) cout<<" "<<a[i];
    return 0;
}
```

## 总结：
本题是一道相对基础的前缀和与差分练习题，但由于是交互题，所以需要注意每次询问后用 ```fflush(stdout);``` 清空缓冲区。其他方面的难度不高，对思维、代码能力要求都不是很大，适合初学者练习。

---

## 作者：Mint_Flipped (赞：1)

这个题是一个交互题，先输入n表示你要猜几次。

打印"? 1 n"，再cin输入即可得到一个1到n总和的值。

那么这题我们只要得到1-2，1-3 ... 1-n的值，再得到2-n的值，就能算出每个的值。

代码如下：

```cpp
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first
#define sec(a) a->second
const int inf=0x3f3f3f3f;
const int maxn=1e6+5;
const int mod=1e9+7;
const double eps=1e-8;
int n;
int a[maxn];
int main()
{
    //freopen("tsin.txt","r",stdin);
    scanf("%d",&n);
    for(int i=2;i<=n;++i){
    	cout<<"? 1 "<<i<<endl;
        cin>>a[i];
    }
    cout<<"? 2 "<<n<<endl;
    cin>>a[1];
    cout<<"! "<<(a[1]=(a[n]-a[1]))<<endl;
    for(int i=2;i<=n;++i){
        cout<<' '<<a[i]-a[i-1];
    }
    cout<<endl;
    return 0;
}
```


---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1425F)

# 前置知识

[前缀和 & 差分](https://oi-wiki.org/basic/prefix-sum/)

# 解法

令 $sum_k=\sum\limits_{i=1}^{k} a_k$。考虑分别输入 $sum_2 \sim sum_n$，故可以由于差分知识得到 $a_i=sum_i-sum_{i-1}(3 \le i \le n)$，接着输入 $a_2+a_3$ 的值从而求出 $a_2=sum_3-a_3,a_1=sum_2-a_2$。

同时因为是交互题，记得清空缓冲区。 C++ 可以使用 ``fflush(stdout);`` 进行清空缓冲区。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define sort stable_sort 
#define endl '\n'
int sum[2001],a[2001];
int main()
{
    int n,i,num;
    cin>>n;
    cout<<"? 1 2"<<endl;
    fflush(stdout);
    cin>>sum[2];
    for(i=3;i<=n;i++)
    {
        cout<<"? 1 "<<i<<endl;
        fflush(stdout);
        cin>>sum[i];
        a[i]=sum[i]-sum[i-1];
    }
    cout<<"? 2 3"<<endl;
    fflush(stdout);
    cin>>num;
    a[2]=num-a[3];
    a[1]=sum[2]-a[2];
    cout<<"! ";
    for(i=1;i<=n;i++)
    {
        cout<<a[i]<<" ";
    }
    return 0;
}
```

---

## 作者：fuwei123 (赞：0)

一道练习前缀和思想的题。

前缀和：
最简单的讲，即对于某个序列 $a$，从 $a_1$ 一直加到 $a_i$，就是 $i$ 这个位置的前缀和，记作 $pre_i$。那么它在这道题里有什么作用呢？

根据定义，可知 $pre_i-pre_{i-1}=a_i$，即 
$$(a_1+a_2\dots+a_{i-1}+a_i)-(a_1+a_2\dots+a_{i-1})=a_i$$

那，我们先询问 $[1,2]$ 这段区间的和，再询问 $[1,3]$ 这段和，将它**减掉** $[1,2]$ 这段区间的和，就能得出 $a_3$ 的值。以此类推，我们只需要询问 $n-1$ 次，就可以知道除了 $a_1$ 和 $a_2$ 之外的**所有元素**的值了。

那这 $a_1$ 和 $a_2$ 的值怎么求？很简单，因为我们知道 $a_3$ 的值，只需要再询问一下 $[2,3]$ 这个区间的和，就能知道 $a_2$ 的值，然后再用 $[1,2]$ 的区间和减 $a_2$ 的值来求 $a_1$，最后输出就行。

有点绕，但很巧妙。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[1005], pre[1005];
signed main(){
	ios::sync_with_stdio(0);
	cin >> n;
	int x;
	for(int i = 2;i <= n;i++){
		cout << "? " << 1 << " " << i << endl;
		cin >> x;
		pre[i] = x;
		a[i] = pre[i] - pre[i - 1];
	}
	cout << "? 2 3" << endl;
	cin >> x;
	a[2] = x - a[3];
	a[1] = pre[2] - a[2];
	cout << "! ";
	for(int i = 1;i <= n;i++){
		cout << a[i] << " ";
	}
	return 0;
}

```


---

## 作者：charleshe (赞：0)

注意到我们可以询问的信息只有区间和，一个自然的想法就是利用前缀和的思想，以区间求差得到某个单点的值。

此处为了方便，将 $l$ 至 $r$ 的区间和记为 $s_{l,r}$，将第 $i$ 项的值记为 $a_i$。

则很明显的，有 $s_{l,r} - s_{l+1,r} = a_l$。

以原题样例为例：

1. 询问 $s_{1,6}$，得到 $30$。

1. 询问 $s_{2,6}$，得到 $29$。此时可以推出 $a_1 = 30 - 29 = 1$。

1. 询问 $s_{3,6}$，得到 $25$。此时可以推出 $a_2 = 29 - 25 = 4$。

1. 询问 $s_{4,6}$，得到 $21$。此时可以推出 $a_3 = 25 - 21 = 4$。

1. 询问 $s_{5,6}$，得到 $15$。此时可以推出 $a_4 = 21 - 15 = 6$。

1. 询问 $s_{6,6}$……

等一下，题目规定询问必须满足 $l < r$，但 $s_{6,6}$ 根本就没满足啊？

首先理清楚，我们已经用 $n-1$ 次询问求出了 $a_1$ 到 $a_{n-2}$ 里的所有数的数值，只剩下了 $a_{n-1}$ 和 $a_n$。

此处有一个技巧：可以询问 $s_{1,n-1}$，则 $a_n = s_{1,n} - s_{1,n-1}$，而 $s_{1,n}$ 和 $s_{1,n-1}$ 都被询问过了，所以可以直接计算 $a_n$，而根据刚才的过程，$s_{n-1,n}$ 已经被询问过了，因此可以直接算出 $a_{n-1} = s_{n-1,n} - a_n$。

至此，我们用了正好 $n$ 次询问求出了数列 $a$ 的每一项的值，直接输出即可。

注意事项：

- 输出询问操作前要输出一个问号，输出整体答案前要输出一个感叹号。

- 这是一道交互题，请按照正常交互操作进行询问和给出答案。

解决了这些问题，代码便很好写了。

```cpp
#include <iostream>
using namespace std;
int a[1001];
int lst,nw;//这里进行了一点优化，用lst存储上一次输入的结果，用nw存储本次输入的结果
int n;
int _1n;//存储1到n的区间和，最后要用
int main(){
	cin>>n;
	cout<<"? "<<1<<" "<<n<<endl;
	cin>>lst;
	_1n=lst;
	for(int i=2;i<n;i++){//正常操作求出前n-2项
		cout<<"? "<<i<<" "<<n<<endl;
		cin>>nw;
		a[i-1]=lst-nw;
		lst=nw;
	}
	cout<<"? "<<1<<" "<<n-1<<endl;
	cin>>nw;
	a[n]=_1n-nw;//求出最后一项
	a[n-1]=lst-a[n];//根据刚才的操作，易知存储最后两项和的变量是lst变量，根据这个求出倒数第二项
	cout<<"! ";
	for(int i=1;i<n;i++) cout<<a[i]<<" ";
	cout<<a[n]<<endl;
	return 0;
}
```


---

## 作者：yinhy09 (赞：0)

## 思路详解

既然 $n$ 次需要知道所有的数，所以就平均一次得到一个数，那么我们就想到了错位相减的办法。（询问 $L$ 到 $R$ 的和再询问 $L$ 到 $R+1$ 的和，然后相减求出 $a_R$）

所以我们可以询问 $1$ 到 $i$（$2 \le i \le n$）的和，这样可以求出 $a_3$ 至 $a_n$。要想再求出 $a_1,a_2$，只需要在询问一次 $2$ 到 $n$ 的和即可。

**别忘了 `fflush(stdout);`**

## AC CODE:

```cpp
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _rep(i,a,b) for(int i=(a);i<(b);i++)
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll read()
{
	char c;
	ll x=0;
	int f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
void write(ll x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
	return;
}
ll a[5005],n,b[5005],k;
int main(){
	n=read();
	for(int i=2;i<=n;i++)
	{
		cout<<"? 1 "<<i<<endl;
		fflush(stdout);
		b[i]=read();
		if(i>2)a[i]=b[i]-b[i-1];
	}
	cout<<"? 2 "<<n<<endl;
	fflush(stdout);
	k=read();
	a[1]=b[n]-k;
	a[2]=b[2]-a[1];
	cout<<"! ";
	for(int i=1;i<=n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	fflush(stdout);
	return 0;
}
//Author:yinhy09,luogu user-id:575320
//Date:2022.6.2
//question ID:Codeforces1425F
```
谢谢观看~

---

