# Mere Array

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ where all $ a_i $ are integers and greater than $ 0 $ .

 In one operation, you can choose two different indices $ i $ and $ j $ ( $ 1 \le i, j \le n $ ). If $ gcd(a_i, a_j) $ is equal to the minimum element of the whole array $ a $ , you can swap $ a_i $ and $ a_j $ . $ gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

 Now you'd like to make $ a $ non-decreasing using the operation any number of times (possibly zero). Determine if you can do this.

 An array $ a $ is non-decreasing if and only if $ a_1 \le a_2       \le \ldots \le a_n $ .

## 说明/提示

In the first and third sample, the array is already non-decreasing.

 In the second sample, we can swap $ a_1 $ and $ a_3 $ first, and swap $ a_1 $ and $ a_5 $ second to make the array non-decreasing.

 In the forth sample, we cannot the array non-decreasing using the operation.

## 样例 #1

### 输入

```
4
1
8
6
4 3 6 6 2 9
4
4 5 6 7
5
7 5 2 2 4```

### 输出

```
YES
YES
YES
NO```

# 题解

## 作者：Little09 (赞：4)

这题是一道小思维题，放在 C 的话难度还是比较低的。

我看有些题解只给了做法没有给证明，所以来说一下。

题意是说如果两个数最大公约数是序列最小值就可以交换。问最小交换次数使得单调不下降。

先给结论：我们先对 $a$ 数组排序，得到最终数列。考虑每个数，如果这个数不等于最终数列的数并且不能被数列最小值整除，那么输出 `NO`。否则遍历完后输出 `YES`。

为什么呢？可以先考虑如果一个数不能被数列最小值整除，那么它肯定无法做任何交换，那么如果还不等于最终数列的数，那肯定是不行的。

如果这个数就等于最终数列的数，保留即可。

如果这个数可以整除数列最小值，那么对于两个满足此条件的数（设为 $x$ 和 $y$），可以和最小值 $z$ 进行如下操作：

```
x y z
x z y
z x y
y x z
```

可以发现，最小值的位置没有改变，而 $x$ 与 $y$ 的位置进行了交换。所以对于所有这样的数，两两可以交换（间接交换）。那么肯定可以达到目标。

其实如果这两个数里有一个数是最小值，那么直接交换即可。依旧是满足的。

所以结论成立。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],b[100001]; 
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		for (int i=1;i<=n;i++) 
		{
			cin >> a[i];
			b[i]=a[i];
		}
		sort(b+1,b+n+1);
		for (int i=1;i<=n;i++) 
		{
			if (a[i]!=b[i]&&a[i]%b[1]!=0)
			{
				cout << "NO" << endl;
				goto no;
			}
		}
		cout << "YES" << endl;
		no:;
	}
    return 0;
}
```


---

## 作者：jun头吉吉 (赞：3)

# CF1401C 【Mere Array】

## 题意

有一个数列$\{a_i\}$，你可以对数列进行如下操作：

1. 选择$i,j$且$\gcd(i,j)=\min_{i=1}^{n} a_i $
2. 交换$i,j$

求能否通过若干次操作使数列单调递增

## 题解

一道灰常好的题目

考虑`选择i,j且gcd(i,j)=min(a_i)`的条件如何使用。

我们可以先找到$\min_{i=1}^{n} a_i $，记为$x$，那么有一个简单的结论：**对于所有的$x|a_i$，那么这些$a_i$可以互换位置；如果$a_i$不是$x$的倍数，$a_i$必然无法移动**

我们来简单地证明一下：

1. 如果$a_i$是$x$的倍数，那么一定有办法通过与$x$交换到任意仍是$x$的倍数的位置。比如`2 6 4`变成`2 4 6`，可以用如下步骤：
> `2 6 4`$\to$`6 2 4`$\to$`6 4 2`$\to$`2 4 6`

2. 如果$a_i$不是$x$的倍数，那么不可能有数与他的$\gcd$为$x$，它的位置不能变

因此我们可以先得出排好序后每个数的排名，如果一个数不是$x$的倍数，且他的排名发生了变动，那么此时就不可能实现

相等的情况最好特判一下~~毕竟因$\color{red}{\texttt{Unaccepted Submission}}$掉排名可一点都不好玩~~

## 代码
```cpp
 //#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
int t,n,a[100000+10],mn;
unordered_map<int,bool>flag;
unordered_map<int,int>Rank;
vector<int>rk;
signed main(){
	in::read(t);
	while(t--){
		in::read(n);mn=2e9+10;
		flag.clear();rk.clear();
		Rank.clear();
		for(int i=1;i<=n;i++)
			in::read(a[i]),mn=min(mn,a[i]),rk.push_back(a[i]);
		sort(rk.begin(),rk.end());
		for(int i=0;i<n;i++)
			if(i==0||rk[i]!=rk[i-1])
				Rank[rk[i]]=i;
		//排在ta前面的应该有
		for(int i=1;i<=n;i++)
			if(a[i]%mn&&a[i]!=a[i-1]){
				if(flag[a[i]]){
					puts("NO");
					goto loop;
				}
				flag[a[i]]=1;
				if(Rank[a[i]]!=i-1){
					puts("NO");
					goto loop;
				}
					
			} 
		puts("YES");
		loop:;
	}
}
```

---

## 作者：_Give_up_ (赞：3)

## 题目大意
有 $t$ 组测试数据，每组数据给定 $n$ 和一个长度为 $n$ 的序列，如果这个序列的任意两个元素的最大公约数等于这个序列里最小的数，那么这两个数可以交换。求是否能将整个序列变成不降序列。

## 题目思路
我们用两个数组 $a$ 和 $b$，一个数组装原本的序列，另一个数组装要变成的不降序列。也就是说，我们要把另一个序列排序。接着我们遍历一遍数组，如果 $a[i] \neq b[i]$，就需要改变这个元素，如果这个元素 $\div$ 整个序列中最小的元素能除开，那么这个元素就可以被改，否则就不能改不了，因为没有与它的最大公约数是序列中最小元素的，就直接输出 NO，跳出循环。如果遍历完一遍了，并没有跳出循环，输出 YES。

## 代码
```cpp
#include<bits/stdc++.h>
#define N 100010

using namespace std;

int read()
{
    int x = 0,f = 1;
    char c = getchar();
    while(c<'0' || c>'9')
	{
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0' && c<='9')
	{
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
    return x*f;
}

int a[N],b[N];

int main()
{
	int t=read();
	while(t--)
	{
		int n=read();
		for (int i=1;i<=n;i++)
			b[i]=a[i]=read();
		sort(b+1,b+n+1);
		int k = b[1];
		bool flag = true;
		for (int i=1;i<=n;i++)
		{
			if (a[i]!=b[i] && a[i]%k)
			{
				cout << "NO" << endl;
				flag = false;
				break;
			}
		}
		if (flag) cout << "YES" << endl;
	}
	return 0;
}
```


---

## 作者：sto__Liyhzh__orz (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1401C)

这题其实很水的啦~~

先给结论：将数组 $a$ 排序，排序后数组为 $b$，数组最小值为 $minn$。对于每个 $i$（$1 \le i \le n$），若 $a_i \ne b_i$ 且 $a_i \bmod {minn} \ne 0$，无解。若所有 $i$ 皆满足，有解。

那是为什么呢？？？

$a_i = b_i$ 的情况就不说了。 

因为 $a_i$ 不等于 $b_i$，证明 $a_i$ 肯定要被交换走，但 $a_i$ 又不是不 $minn$ 的倍数，无法交换，所以无解。

那为什么剩下的情况就一定有解呢？

我们可以设需要交换的两个数为 $a$，$b$。

那么他可以做如下操作（大写的字母表示接下来是两个数交换）：

```
A b MINN
MINN B a
b MINN A
b a minn
```

怎么样？是不是证明了剩下的情况皆有解？

给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=100000+5;
int a[MAXN],b[MAXN],T,n;

int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        int minn=1e9;
        for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i],minn=min(a[i],minn);
        sort(b+1,b+n+1);
        bool flag=1;
        for(int i=1;i<=n;i++)
        {
            if(a[i]%minn!=0 && a[i]!=b[i]) 
            {
                flag=0;
                cout<<"NO\n";
                break;
            }
        }
        if(flag) cout<<"YES\n";
    }
    return 0;
}
```

---

## 作者：LeavingZzz (赞：2)

## $\mathsf{Solution\space For \space CF1401C}$  
~~赛时竟然WA了两发/baojin/baojin~~  
### $\mathsf{Description}$  
给出一个序列 $\{a_i\}$，你可以对其中两个下标为 $i,j$ 的元素进行交换操作当且仅当 $\gcd(a_i,a_j)=minn$（$minn$ 表示整个序列的最小值），求能不能将这个序列通过这种交换操作变成一个单调不降的序列  
### $\mathsf{Analysis}$  
首先证明一个结论：  
如果 $a_i$ 和 $a_j$ 可以交换，并且 $a_j$ 可以和 $a_k$ 进行交换，那么 $a_i$ 也能和 $a_k$ 换位置，**只不过这个换位置不一定是直接的交换**。  
如果 $\gcd(a_i,a_k)=minn$ 那自然可以交换  
如果 $\gcd(a_i,a_k)\ne minn$，步骤如下  
$$a_i,a_j,a_k$$  
$$a_i,a_k,a_j$$  
$$a_j,a_k,a_i$$  
$$a_k,a_j,a_i$$  
从而达到交换  


------------
然后还有一个很显然的事情，那就是在这个序列中任意一个是 $minn$ 整数倍的元素一定能和 $minn$ 交换，能交换的一对元素也都能和 $minn$ 交换。  

这就引导我们构建一个集合，集合内的元素是这个序列中是 $minn$ 整数倍的元素，这个集合内的元素一定能够直接或者间接的相互交换位置，而集合外的元素一定无法和任何元素交换位置（因为不是 $minn$ 的整数倍，也就不含 $minn$ 这个因子，$\gcd$ 不可能是 $minn$）  

我们先把整个序列排序，这样就是单调不降了，设排序后序列为 $\{b_i\}$  

然后枚举元素，有两种情况  
#### $1.a_i=b_i$  
这种情况下表示 $a_i$ 在他自己应该在的位置上，合法  
#### $2.a_i\ne b_i$  
这种情况下 $a_i$ 并不在自己的位置上，我们需要判断它是不是在前面提到的集合中，如果在那个集合中一定也是合法的（一定可以通过若干次交换到自己应该到的位置上），否则这个元素既不在这个位置上、也没办法交换，就没办法得到单调不减的序列了  

### $\mathsf{Code}$
```
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=100007;
int T;
int A[maxn],B[maxn],N;
void check()
{
    for(register int i=1;i<=N;i++)
    {
        if(A[i]==B[i]) continue;//在自己应该待的位置上
        if(A[i]%B[1]) {puts("NO");return ;}
        //不在自己位置上而且无法交换
    }
    puts("YES");
    return ;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(register int i=1;i<=N;i++)
            scanf("%d",&A[i]),B[i]=A[i];
        sort(B+1,B+1+N);
        check();
    }
    return 0;
}
```
~~萌新上分，越上越昏~~  
$\huge\mathcal{The\space End}$  
谢谢管理大大审核 ^_^

---

## 作者：Larry76 (赞：1)

## 题目大意：
给定一序列 $A$，定义当且仅当 $\gcd(a_i,a_j)=a_{min}$ 时，元素 $a_i$ 和 $a_j$ 可以交换。

问当前给定的序列 $A$ 能否转化为非严格单调递增的序列。

## 题目分析：
因为两个元素当且仅当其最大公因数为 $a_{min}$ 时才可以交换，故我们可以先对原序列进行排序，然后判断排序后的序列中原序列与之间的不同的元素能不能被 $a_{min}$ 整除即可，理由如下：

首先，很显然的是，原命题等价于两个命题，分别是：
1. 若排序后的序列中与原序列之间不同的元素不能被 $a_{min}$ 整除，则原序列必定无法转化为一个非严格单调递增的序列
2. 若排序后的序列中与原序列之间的每一个不同的元素能被 $a_{min}$ 整除，则原序列必定可以转化为一个非严格单调递增的序列。

现在，我们对命题 $1$ 进行证明：

因为其为排序后的序列，故其与原序列不同的元素必然是那些发生了交换的元素。

如果那些发生了交换的元素不能被最小值 $a_{min}$ 整除，则证明该元素中不完全包含 $a_{min}$ 所含有的因子，故其与其他数的最大公因数必然不是$a_{min}$，其显然无法完成交换操作，与前面相矛盾，所以无法完成转化操作。

现在，我们对命题 $2$ 进行证明：

1. 若每两个不同的元素之间的**最大公因数**为 $a_{min}$，则其能转化为目标序列是显然的，这里不多赘述。

2. 若有两个不同的元素之间的**最大公因数**不为 $a_{min}$，那么这两个数要么可以通过其他**与之最大公因数为 $\boldsymbol{a_{min}}$** 的间接交换而来，要么直接和 $a_{min}$ 间接交换而来。

综上，我们不难证明这个方法是正确的。时间复杂度取决于排序，这里我用的是快排，故时间复杂度为 $O(n\lg n)$

## 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define TIME_LIMIT (time_t)2e3
#define dbg(x) cerr<<#x<<": "<<x<<endl;
#define MAX_SIZE (int)1.1e5

signed main() {
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    time_t cs = clock();
#endif
    //========================================
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        int a[MAX_SIZE] = {};
        int bak[MAX_SIZE] = {};

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            bak[i] = a[i];
        }

        sort(a + 1, a + 1 + n);
        bool flag = 0;

        for (int i = 1; i <= n; i++) {
            if (a[i] != bak[i] && a[i] % a[1] != 0) {
                cout << "NO" << endl;
                flag = 1;
                break;
            }
        }

        if (!flag)
            cout << "YES" << endl;
    }

    //========================================
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
    time_t ce = clock();
    cerr << "Used Time: " << ce - cs << " ms." << endl;

    if (TIME_LIMIT < ce - cs)
        cerr << "Warning!! Time exceeded limit!!" << endl;

#endif
    return 0;
}
```

---

## 作者：Error_Eric (赞：1)

### 思路

定义 $m$ 为 $a$ 数组中的最小元素的值。

题目大意：给定一个长度为 $n$ 的数组 $a$ ,对于任意的 $i,j$ ,若有 $\gcd{(a_i,a_j)}=m$,那么可以将 $a_i,a_j$ 交换位置。

求：可否将数组 $a$ 变为单调不降。

------

首先，对于任意的 $i$ ,如果 $a_i$ 不恰好是 $a$ 中第 $i$ 大的，并且 $a_i\ \text{mod}\ m \not= 0$ ,那么这个数组肯定不合法，因为这个位置无法交换。

然后……这个数组就肯定合法了。

为什么呢？ 证明如下：

------

证明：对于任意 $a_i,a_j$ 如果 $a_i\ \text{mod}\ m =a_j\ \text{mod}\ m =0$ 那么$a_i$ 和 $a_j$ 可以交换。

设 $a_k$ 为 $a$ 中的最小值。

显然 $a_i,a_j\geq a_k$ 并且 $a_i\ \text{mod}\  a_k=a_j\  \text{mod}\ a_k=0$

$\because a_i\ \text{mod}\ a_k =0$

$\therefore \gcd(a_i,a_k) =\min{(a_i,a_k)} $

又$\because a_i\geq a_k$

$\therefore \gcd(a_i,a_k)=a_k=m$

$\therefore a_i$ 和 $a_k$ 可以交换。

同理 $a_j$ 和 $a_k$ 可以交换。

也就是说：

对于任意 $a_i,a_j$，如果 $a_i\ \text{mod}\ m =a_j\ \text{mod}\ m =0$

可以先将 $a_i$ 与 $a_k$ 交换。

再将 $a_j$ 与 $a_k$ 交换。

再将 $a_i$ 与 $a_k$ 交换。

等价于直接将 $a_i,a_j$ 交换。

------

既然对于任意 $a_i,a_j$ 如果 $a_i\ \text{mod}\ m =a_j\ \text{mod}\ m =0$ 那么$a_i$ 和 $a_j$ 可以交换，那么我们不妨将合法的 $a$ 数组中所有 $a_i$ 不是第 $i$ 大数的数字进行“冒泡排序”，那么排序出来肯定就是单调不减的序列了。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int in[100000*2],out[100000*2],n,t;//in存储排序前的,out存储排序后的。
const string ans[]={"NO\n","YES\n"};//答案
int solve(){//对于每一组数据
	scanf("%d",&n); //输入n
	for (int i=1;i<=n;i++)scanf("%d",&in[i]),out[i]=in[i];//输入ai,赋值。
	sort(out+1,out+n+1);//排序
	for (int i=1;i<=n;i++) //对于任意的i
		if (in[i]%out[1] and in[i]!=out[i])return 0;//如果ai不是第i大的数并且无法交换,数组不合法。
	return 1;//看来合法。
} 
int main(){
	scanf("%d",&t);//有多组数据
	while (t--)cout<<ans[solve()];//输出答案
    return 0;
}
```

时间复杂度 $\text{O}(t\times n\log n)$ ~~我不知道为什么给我卡过了qwq~~。

---

## 作者：huayucaiji (赞：1)

~~虽然比赛的时候我写挂了一次，但我还是蛮喜欢这道题的~~

这个题的思路很妙，我们先来看题目中的条件：

>In one operation, you can choose two different indices $i$ and $j$ ($1\leq i$,$j\leq n$). If $\gcd(a_i,a_j)$ is equal to the minimum element of the whole array a, you can swap $a_i$ and $a_j$

这证明我们可以先找出这个最小值，即为 $divi$（全称divisor，注意 ```div``` 在头文件中出现过，不能用！）。我们只要判断一个数 $a_i$，若 $divi\nmid a_i$，我们要判断他是否在正确的位置上，即有多少的数比它小。若不在正确位置上，直接 $\text{NO}$，否则继续判断。

~~一开始我是这样写的，但是由于写挂了，于是怀疑这个是错误的~~

其实这个怀疑很正常，因为我们认为的是两个都能被 $divi$ 整除的数可以直接交换位置，但是如果 $divi=2$，那么 $4,8$ 不能直接交换位置。这边是我一开始的疑惑。但是后来，我们可以发现，$4,8$，不能直接交换位置，我们可以**间接**交换呀。我们先把 $2,4$ 换一下，再换一下 $2,8$，最后再换一下 $2,4$ 就完成了。因此原算法正确。~~只是我写挂了而已qwq~~

**特别注意一下如果 $a_i$=$a_{i-1}$，我们的要特殊处理**

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10;

int n,a[maxn],divi,b[maxn];

signed main() {
	int T=read();
	
	while(T--) {
		n=read();
		divi=1e9+10;
		for(int i=1;i<=n;i++) {
			a[i]=read();
			b[i]=a[i];
			divi=min(divi,a[i]);
		}
		
		sort(b+1,b+n+1);//排序
		
		bool flag=1;
		int pos=0;
		for(int i=1;i<=n;i++) {
			if(a[i]%divi!=0) {
				pos=upper_bound(b+1,b+i+1,a[i])-b; 
				if(!(pos-1==i&&b[pos-1]==a[i])) {//如果 $a_i$=$a_{i-1}$，我们的要特殊处理
					printf("NO\n");
					flag=0;
					break;
				}
			}
		}
		if(flag) {
			printf("YES\n");
		}
	}
	return 0;
}

```

---

## 作者：Ryo_Yamada (赞：1)

作为 C 题这题感觉还是挺温暖的（雾

解法：先排序，如果 $a_i$ 不在原位，$a_i \!\!\mod a_1 ≠ 0$，输出 `NO`。否则输出 `YES`。

$\text{Code}$：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
int a[N];
int k[N];

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d", a + i);
			k[i] = a[i];//k数组记录a数组排序前的值
		}
		sort(a + 1, a + n + 1);
		bool flag = true;
		for(int i = 2; i <= n; i++) {
			if(a[i] != k[i] && a[i] % a[1]) {//如果不在原位
				flag = false;
				break;
			}
		}
		flag ? puts("YES") : puts("NO");
	}
	return 0;
}


```


---

## 作者：Azazеl (赞：1)

### CF1401C Mere Array

#### 题意  

> $~~~~$ 给出一个序列 $A$ ，两个元素 $a_i,a_j$ 能交换当且仅当 $gcd(a_i,a_j)=\min\{A\}$ ，求能否让这个序列变成升序排列。  

---

#### 题解  

$~~~~$ 没想到猜个东西打上去就行了，不过最后网络+手速原因 $C$ 都没交上去，今早起来直接过···

$~~~~$ 首先将 $A$ 序列创建一个副本并将这个副本升序排序。然后找到 $A,B$ 序列对应位置上的元素是否正确，如果错误能否交换。不能输出 `NO` 即可。  

$~~~~$ 简单题，但就是不敢猜···  

---

#### 代码

```cpp
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
map<int,int> ma;
int arr[100005],s[100005];
bool cnt[100005];
int main() {
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int minn=1e9,maxn=-1,tot=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&arr[i]);
			s[i]=arr[i];
			minn=min(minn,arr[i]);
			maxn=max(maxn,arr[i]);
			if(!ma[arr[i]]) ma[arr[i]]=++tot;
		}
		sort(s+1,s+1+n);
		for(int i=1;i<=n;i++) if(arr[i]%minn==0) cnt[ma[arr[i]]]=true;
		bool flag=false;
		for(int i=1;i<=n;i++)
		{
			if(s[i]!=arr[i]&&(!(cnt[ma[s[i]]]&&cnt[ma[arr[i]]])))
			{
				puts("NO");
				flag=true;
				break;
			}
		}
		if(!flag) puts("YES"); 
		for(int i=1;i<=tot;i++) cnt[i]=false;
		ma.clear();
	}
	return 0;
} 
```



---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析:   

交换数组使其变为升序，满足交互的两数 $a_i$ 与 $a_j$，$ \min\{a_i(1\le i\le n)\}|\gcd(a_i,a_j)$ 。    

简单思维题，Div.2 C 有点不太合适。   

因为数组的最小值始终不变，所以直接比较即可。      

### Solution:

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+50;

int t,n;

int a[N],b[N];

int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int minn=INT_MAX;
		for(int i=1;i<=n;++i) scanf("%d",&a[i]),b[i]=a[i],minn=min(minn,a[i]);
		sort(b+1,b+n+1);
		bool flag=1;
		for(int i=1;i<=n;++i){
			if(a[i]==b[i]) continue;
			if(__gcd(a[i],b[i])%minn!=0){
				printf("NO\n");
				flag=0;
				break;
			}
		}
		if(flag){
			printf("YES\n");
		}
	}
}
```

---

## 作者：fanfansann (赞：0)

这题妙啊。

我们发现本题是要求将给定序列排序，并给定了交换元素的条件。
问我们能否实现排序操作。

我们参考冒泡排序等排序算法，想要完成排序，那么必须可以将一些数交换。而我们想要交换$a_i,a_j$,就必须满足 $\gcd(a_i,a_j)$等于整个数组中最小的元素。
因此我们先将原序列复制后排序，如果序列里的数于排序之后的数不同，则说明该数需要变换位置。然后看该数能够被序列最小元素整除，如果可以的话可以交换，如果不行的话说明无法换位还不在正确的位置上，输出$NO$,否则输出$YES$。
如果这个数可以整除数列最小值，那么对于两个满足此条件的数 $x$ 和  $y$，可以和最小值 $z$下列操作：

```cpp
x y z
x z y
z x y
y x z
```
实现交换 $x$ 和 $y$ 的位置，$z$ 不变，完成排序里的交换操作。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 200007;

int n, m;
int t;
int a[N], b[N];
int main()
{
    scanf("%d", &t);
    while(t -- ){
        scanf("%d", &n);
        bool flag = 0;
        for(int i = 1; i <= n; ++ i)
            scanf("%d", &a[i]);
        memcpy(b, a, sizeof a);
        sort(b + 1, b + 1 + n);
        for(int i = 1; i <= n; ++ i){
            if(a[i] != b[i] && a[i] % b[1] != 0){
                puts("NO");
                flag = 1;
                break;
            }
        }
        if(!flag)puts("YES");
    }
    return 0;
}

```


---

## 作者：xuezhe (赞：0)

首先，可以通过打表证明，如果 $a,b$ 能交换，$b,c$ 能交换，则 $a,b,c$ 的所有排列都能从任意状态开始通过交换产生。

与此同时，可以发现题目可以交换的条件较为特殊，即 $\gcd(a_i,a_j)=\min{a_k}$（下面简记 $\min{a_k}$ 为 $m$）。将 $m$ 质因数分解，可以发现 $a_i$ 能与其它数交换当且仅当对于所有分解出的 $m$ 的质因数，$a_i$ 的这一质因数的次数不小于 $m$ 中这一质因数的次数，故可得出 $\gcd(m,a_i)=m$，即 $m|a_i$。

所以我们可以将所有 $m$ 的倍数提出来，根据第一段中的结论，可以进行一个比较粗劣的冒泡排序：将 $m$ 一路交换至末尾，然后不断让当前以 $m$ 为结尾的三元组变为非降序。所以最终一定可以让这些提出来的数变为非降序。

所以我们只要提出来排个序然后放回序列中，看一下最后整个序列是否是非降序的。

时间复杂度取决于排序复杂度。

Code:
```cpp
vector<int> v;
int T,n,a[100005],b[100005];

int main(){
    cin>>T;
    while(T--){
        v.clear();
        cin>>n;
        int mina(1000000000);
        for(int i=1;i<=n;++i){
            cin>>a[i];
            if(mina>a[i])
                mina=a[i];
        }
        for(int i=1;i<=n;++i)
            if(__gcd(a[i],mina)==mina){
                v.pb(a[i]);
                b[i]=1;
            }else{
                b[i]=0;
            }
        sort(v.begin(),v.end());
        for(int i=n;i;--i)
            if(b[i]){
                a[i]=v[v.size()-1];
                v.pop_back();
            }
        bool f(true);
        for(int i=1;i<n;++i)
            if(a[i]>a[i+1])
                f=false;
        if(f){
            puts("YES");
        }else{
            puts("NO");
        }
    }
    return 0;
}
```

---

## 作者：B_1168 (赞：0)

容易发现，设数组$a$的最小值为$m$，另有两个数$a_{i},a_j$，满足$m|a_i,a_j$，如果需要交换$a_{i},a_j$的位置，便可以利用$m$实现，即便$\gcd(a_i,a_j)\ne m$。

因此，对于任何数列$a$，当且仅当存在$a_i$使得$m\nmid a_i$且$a_i$需要被移动以使得$a$单调不降时，数列$a$不能被排序。

容易得到这个思路：可以整理出每个数排序后的排名，和每个数原本的排名做对比；如果出现一个数$a_i$使得$m\nmid a_i$且$a_i$需要被移动以使得$a$单调不降，便可立刻输出`NO`，否则可以输出`YES`。

特别留意，因为数字可能出现重复，必须确保两个数相等时不被交换，因此需要使用`std::stable_sort`，否则在数字重复时可能出现问题。

以下放代码：

```cpp
//Luogu-resubmission
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;

int n,t;

struct node{
	int val,inp,rk;
};

bool cmp1(node x,node y){
	return x.val<y.val;
}

bool cmp2(node x,node y){
	return x.inp<y.inp;
}

void solve(){
	scanf("%d",&n);
	int fl=1,mn=(1<<30);
	node a[maxn];
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].val);
		if(a[i].val<a[i-1].val){
			fl=0;
		}
		mn=min(mn,a[i].val);
		a[i].inp=i;
	}
	if(fl){
		printf("YES\n");
		return;
	}
	stable_sort(a+1,a+n+1,cmp1); //Note the stable_sort: without it certain data may mess it up
	for(int i=1;i<=n;i++) {
		a[i].rk=i;
	} 
	stable_sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++){
		if(a[i].rk!=a[i].inp && (a[i].val % mn !=0)){
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
}

int main(){
	scanf("%d",&t);
	while(t--){
		solve();
	}
}
```

倾情奉献：将鄙人程序卡掉的样例----

```
1
105
4 2 16 10 12 6 18 18 18 14 3 4 10 16 10 14 4 8 2 12 8 14 8 2 6 6 8 16 12 10 14 10 18 8 12 14 16 6 12 10 6 6 12 6 6 6 8 12 2 4 18 8 6 10 6 12 16 8 10 4 6 2 12 11 10 6 2 18 16 12 6 14 6 2 6 10 8 18 14 6 16 6 6 18 2 18 8 2 8 6 18 17 17 17 6 4 6 14 18 8 16 8 12 6 2
```

容鄙人给自己的rating哭三秒……

感谢管理审核，感谢大佬们阅读！

---

