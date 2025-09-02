# Permutation Chain

## 题目描述

A permutation of length $ n $ is a sequence of integers from $ 1 $ to $ n $ such that each integer appears in it exactly once.

Let the fixedness of a permutation $ p $ be the number of fixed points in it — the number of positions $ j $ such that $ p_j = j $ , where $ p_j $ is the $ j $ -th element of the permutation $ p $ .

You are asked to build a sequence of permutations $ a_1, a_2, \dots $ , starting from the identity permutation (permutation $ a_1 = [1, 2, \dots, n] $ ). Let's call it a permutation chain. Thus, $ a_i $ is the $ i $ -th permutation of length $ n $ .

For every $ i $ from $ 2 $ onwards, the permutation $ a_i $ should be obtained from the permutation $ a_{i-1} $ by swapping any two elements in it (not necessarily neighboring). The fixedness of the permutation $ a_i $ should be strictly lower than the fixedness of the permutation $ a_{i-1} $ .

Consider some chains for $ n = 3 $ :

- $ a_1 = [1, 2, 3] $ , $ a_2 = [1, 3, 2] $ — that is a valid chain of length $ 2 $ . From $ a_1 $ to $ a_2 $ , the elements on positions $ 2 $ and $ 3 $ get swapped, the fixedness decrease from $ 3 $ to $ 1 $ .
- $ a_1 = [2, 1, 3] $ , $ a_2 = [3, 1, 2] $ — that is not a valid chain. The first permutation should always be $ [1, 2, 3] $ for $ n = 3 $ .
- $ a_1 = [1, 2, 3] $ , $ a_2 = [1, 3, 2] $ , $ a_3 = [1, 2, 3] $ — that is not a valid chain. From $ a_2 $ to $ a_3 $ , the elements on positions $ 2 $ and $ 3 $ get swapped but the fixedness increase from $ 1 $ to $ 3 $ .
- $ a_1 = [1, 2, 3] $ , $ a_2 = [3, 2, 1] $ , $ a_3 = [3, 1, 2] $ — that is a valid chain of length $ 3 $ . From $ a_1 $ to $ a_2 $ , the elements on positions $ 1 $ and $ 3 $ get swapped, the fixedness decrease from $ 3 $ to $ 1 $ . From $ a_2 $ to $ a_3 $ , the elements on positions $ 2 $ and $ 3 $ get swapped, the fixedness decrease from $ 1 $ to $ 0 $ .

Find the longest permutation chain. If there are multiple longest answers, print any of them.

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
2
1 2
2 1
3
1 2 3
3 2 1
3 1 2```

# 题解

## 作者：CodeMao (赞：5)

### 1. 简述题意

给定一个长度为 $n$ 的序列 $a_1$，每次操作可以交换序列中任意两个元素，每操作一次就生成一个新的序列 $a_i$，要求使得序列 $a_i$ 的固定性严格小于序列 $a_{i-1}$ 的固定性，且使得固定性减小最慢。

定义一个序列的固定性为序列中 $a_i=i$ 的元素的个数。

### 2. 思路

一眼题，**贪心**。

首先我们很容易知道，第一次无论交换哪两个元素，都会使得 $a_1$ 的固定性减 $2$。

既然我们想让固定性减小最慢，那么我们就要考虑：每次交换的两个元素都要有什么特点？

显然，想让固定性减小最慢，每次固定性一定只减小 $1$。

那么我们每次就可以交换一个 $a_i≠i$ 的元素和另一个 $a_i=i$ 的元素。

进一步可知，我们每次只需交换相邻的两个元素即可。

如果仍不能理解，可以看看下面举的例子。

e.g. $n = 7$

$a_1=[1,2,3,4,5,6,7]$，固定性为 $7$。

$a_2=[2,1,3,4,5,6,7]$，固定性为 $5$。

$a_3=[2,3,1,4,5,6,7]$，固定性为 $4$。

$a_4=[2,3,4,1,5,6,7]$，固定性为 $3$。

$a_5=[2,3,4,5,1,6,7]$，固定性为 $2$。

$a_6=[2,3,4,5,6,1,7]$，固定性为 $1$。

$a_7=[2,3,4,5,6,7,1]$，固定性为 $0$。

### 3. 代码

```cpp
#include <cstdio>
#define N 105
int t, n; int a[N];
inline void swap(int &a, int &b){ //使用位运算交换两个元素的值
    a ^= b ^= a ^= b;
}
int main(){
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", n);
        for (int i = 1; i <= n; ++i) { //赋值并输出原始序列
            a[i] = i;
            printf("%d ", a[i]);
        } puts("");
        for (int i = 1; i < n; ++i) { //每次交换相邻两个元素的值
            swap(a[i], a[i + 1]);
            for (int j = 1; j <= n; ++j) //输出处理过的序列
                printf("%d ", a[j]);
            puts("");
        }
    }
    return 0;
}
```

---

## 作者：Epi4any (赞：4)

一眼看穿：**构造论证**

于是我们经过一些简单的找规律可以得知：
- 第一次交换，无论换那两个，都会让它的 $fixedness-2$。
- 后来的几次交换，每一次可以让它的 $fixednese-1$。

然后就来到构造: **第一步先输出原数组**~~（我因为这个暴毙了一次）。~~
1. 交换两个数，这里我们交换前两个。
![step1](https://cdn.luogu.com.cn/upload/image_hosting/jlewxazl.png)
2. 交换第一个和第三个数，这样可以让他们都不处于原来位置上，并且只破坏一个数的位置。
![step2](https://cdn.luogu.com.cn/upload/image_hosting/xlu4qznu.png)
3. 以此类推，每一次交换第一个和第 $i$ 个数。

代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int t, n;
char s[105];

void work() {
	cout << n << endl;
	for (int i = 1; i <= n; i++) s[i] = i;

	for (int i = 1; i <= n; i++) printf("%d ", s[i]);
	printf("\n");
	for (int i = 2; i <= n; i++) {
		swap(s[1], s[i]);
		for (int j = 1; j <= n; j++) printf("%d ", s[j]);
		printf("\n");
	}
	return;
}

int main() {
	t = read();
	while (t--) {
		n = read();
		work();
	}
	return 0;
}
//结尾警告：理解思路 不抄代码
```

---

## 作者：Anomie (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1716B)

## 思路

简单的构造题。

首先，一个长度为 $ n $ 的数列链(瞎翻译的)的稳定性(还是瞎翻译的)最多只能是 $ n $ ，不能再多了，因此首先要输出 $ n $ .

接着来考虑怎么构造。最开始的数列一定是从 $ 1 $ 到 $ n $ 最优，然后题目中要求每次只能交换旧数列的相邻两个元素，然后产生新数列。这里构造的方法有很多种，我的方法是从 $ a [ n ] $ 和 $ a [ n - 1] $ 开始交换，一直递减，直到交换到 $ a [ 1 ] $ ，一共交换 $ n $ 次，每交换一次就输出新数组。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		int n,a[101],cnt;
		scanf("%d",&n);cnt=n;//cnt是用来存当前交换的元素的下标的(有点绕)，相当于指针（？）
		printf("%d\n",n);//首先输出最大稳定性：n
		for(int i=1;i<=n;i++) a[i]=i;//最初的数组
		for(int p=1;p<=n;p++){
			for(int i=1;i<=n;i++) printf("%d ",a[i]);
			swap(a[cnt],a[cnt--]);//swap(a,b)的意思是交换a和b的值
		//a[cnt--]实际上就是先--cnt，然后再返回a[cnt]
        	printf("\n");
		}
	}
	return 0;//完结撒花~
}
```


---

## 作者：Qerucy (赞：2)

这道题很简单，我们需要考虑每次固定值最少能减多少。

必然的，除了第一次固定值减 $2$ 之外，剩下的操作固定值都是减 $1$。

证明：

+ 因为刚开始序列 $a$ 中的每个元素都有 $a_i=i$，所以我们交换只好拿出两个元素交换，固定值减 $2$。

+ 接下来每次操作，我们只需要拿一个交换过的元素与未交换过的元素交换即可，固定值减 $1$。

所以也必然的，最多的操作次数为 $n-1$，再加上输出初始序列，一共是 $n$ 次。

我是拿初始序列中的 $a_1$ 来进行交换。

代码:

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
string s;
int t,n,b,c;
int a[1010];
 
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            a[i]=i;
        }
        printf("%d\n",n);
        
        for(int i=1;i<=n;i++){
            
            for(int j=1;j<=n;j++){
                printf("%d ",a[j]);
            }
            puts("");
            
            swap(a[i],a[i+1]);
        }
    }
    return 0;
}
```


---

## 作者：JZH123 (赞：1)

### 样例中 $n$ 为 $3$ 时 ——

$a[1]$ = $[1,2,3]$ , $a[2]$ = $[1,3,2]$ —— 这是一个有效的长度链 2 。 从 $a[1]$ 自 $a[2]$ ，位置上的元素 $2$ 和 $3$ 交换下，固定性从 $3$ 自 $1$.

$a[1]$ = $[2,1,3]$ , $a[2]$ = $[3,1,2]$—— 这不是一个有效的链 。第一个排列应始终为 $[1,2,3]$ ，$n$ = $3$.

$a[1]$ = $[1,2,3]$ , $a[2]$ = $[1,3,2]$ , $a[3]$ = $[1,2,3]$ —— 这不是一个有效的链。从 $a[2]$ 自 $a[3]$ ，位置上的元素 $2$ 和 $3$ 被交换，但固定性从 $1$ 自 $3$ .

$a[1]$ = $[1,2,3]$, $a[2]$ = $[3,2,1]$, $a[3]$ = $[3,1,2]$ —— 这是一个有效的长度链 3. 从 $a[1]$ 自 $a[2]$ ，位置上的元素 $1$ 和 $3$ 换下，固定性从 $3$ 自 $1$ . 从 $a[2]$ 自 $a[3]$，位置上的元素 $2$ 和 $3$ 换下，固定性从 $1$ 自 $0$ .
# 解题思路
给定一个长度为 $n$ 数列链 $a[ ]$， 最开始输出 $n$。

最开始的数列是从 $1$ ~ $n$ 最优，接下来每一次交换原数组的相邻两个元素（建议用 $\verb!swap!$ 函数），产生新的数列。

从 $a[n]$ 和 $a[n - 1]$ 开始交换，重复递减操作，直到交换到 a$[1]$ ，共交换 $n$ 次，每次都要输出新数组。
# 上代码——
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
const int N = 1e2 + 5;//定义常量，N相当于105
int t, n, a[N], count;//count表示交换元素的下标
#define f(i, j, k) for (int i = j; i <= k; i ++)//宏定义
int main()
{
	scanf("%d", &t);
	while(t --)//多组数据
	{
		scanf("%d", &n);
		count = n;
		printf("%d\n", n);//先输出n
		f(i, 1, n) 
			a[i] = i;//数组a[]初始化
		f(j, 1, n)
		{
			f(i, 1, n) 
				printf("%d ", a[i]);//输出新数组
			swap(a[count], a[count --]);//交换a[count]和a[count --]的值
        	printf("\n");//记得换行
		}
	}
	return 0;
}
```

---

## 作者：sxq9 (赞：1)

## 题目大意
有一个长度为 $n$ 的序列 $a$ 内容为 $1$ 到 $n$ ，每次交换序列中两个元素，每换一次就有了一个新的序列，要使新序列比上一个序列的稳定性小，且使得稳定性减小最慢。
## 思路
不难看出，第一次不管怎么换稳定性都只能 $-2$ ，后面每次可以 $-1$ ，然后其实就很好看出只要每次交换相邻的两个就好了，然后交换次数就直接是 $n$ 。
## 代码
```cpp
#include<bits/stdc++.h>
//#define int unsigned long long
using namespace std;
int xulie[1000];
void shuchu(int n){
	for(int i=1;i<=n;i++){
		cout<<xulie[i]<<' ';
	}
	cout<<endl;
}
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int n;
		cin>>n;
		cout<<n<<endl;//直接输出
		for(int j=1;j<=n;j++)xulie[j]=j;//赋值为下标
		for(int j=1;j<n;j++){
			shuchu(n);//先输出一遍
			swap(xulie[j],xulie[j+1]);//交换相邻的两个
		}
		shuchu(n);//别忘了这里最后要输出一次
	}
	return 0;
}
```

---

## 作者：Wings_of_liberty (赞：1)

# 题目翻译
当序列 $a$ 中的第 $i$ 个元素满足 $a[i]=i$ 时，我们说这个元素具有固定性。  
长度为 $n$ 的排列是从 $1$ 到 $n$ 的整数序列，且每个元素都具有固定性。  
对于第 $i$ 个数的操作，我们可以交换任意两个数的位置，并且要满足，每一次操作过后得到的新序列中具有固定性的点的数量变少，请构造一组数据，由序列 $n$ 经过 $x$ 次操作得到，使 $x$ 最大。  
原序列和每一次操作后得到的序列（共 $x+1$ 个序列），一起构成了置换链。
### 输入
第一行：一个整数 $t(1\leq t \leq 99)$ 表示数据的组数。  
第 $2$ 到第 $t+1$ 行，每行一个整数 $n$ 表示序列长度。
### 输出
对于每一组数据：  
第一行输出置换链中序列的个数 。  
之后每行输出置换链中的一个序列。
# 分析
首先，第一次交换，一定会使两个元素不具有固定性。  
之后的每一次交换，可以选择交换两个没有被交换过的数，也可以选择交换一个没被交换过的数和一个被交换过的数。  
前者会使两个数不具有固定性，后者会使一个数不具有固定性，然而我们要找到最多的交换次数，所以每次我们选择后者。  
通过上面的分析，我们发现，最多的交换次数就是 $n-1$ 次（ $n$ 为序列长度），那么一种可行的方案就是先交换第一个和第二个元素，之后从第 $2$ 个元素开始，每次交换第 $i$ 个数和第 $i+1$ 个数。
# 代码实现
```
#include <bits/stdc++.h>
using namespace std;
const int MAX=110;
int n,a[MAX];
int main(){
	int t;
	scanf("%d",&t);
	for(int k=1;k<=t;k++){
		scanf("%d",&n);
		printf("%d\n",n);
		for(int i=1;i<=n;i++){
			a[i]=i;
			printf("%d ",i);
		}
		printf("\n");
		for(int i=1;i<=n-1;i++){
			swap(a[i],a[i+1]);
			for(int j=1;j<=n;j++){
				printf("%d ",a[j]);
			}
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：Steve_JTH (赞：1)

# 题目翻译
由于这道题没有翻译，所以我简单翻译一下。

输入 $t$ 组数据，每组数据包含一个大于 $2$ 的正整数 $n$，
且 $a_1 = [1, 2, 3\cdots n]$，我们称之为排列链。

交换排列链的任意两个元素（不一定相邻），使得排列的固定性 $a_i$ 低于 $a_{i - 1}$。

找到最长的排列链。如果答案有多个，输出哪个都可。
# 题意分析
这道题看似很唬人，其实很简单。

由于题目说了：
```
如果答案有多个，输出哪个都可
```
所以我们只需考虑怎么交换能使固定性每次减少的最少就好了，**不需要考虑交换顺序**。

不难想出，当第一次交换时，不管怎么交换，固定性都会 $-2$。

之后的交换只要每次都与交换过的元素的数交换，那么固定性就会只 $-1$。

最后有一点不要忘记：**原数组也是排列链，所以要先输出原数组。**

# Code
```cpp
#include <cstdio>
int main(){
  int t;
  scanf("%d",&t);
  for (int i = 1; i <= t; i++){
    int n, a[101];
    scanf("%d",&n);
    printf("%d\n",n);//输出置换链长度
    for (int j = 1; j <= n; j++){
      a[j] = j;
      printf("%d ",a[j]);//输出原数组（前面解释过了）
    }
    printf("\n");
    for (int j = 1; j <= n - 1; j++){
      int t1 = a[j];
      a[j] = a[j + 1];
      a[j + 1] = t1;
      /*与交换过的元素进行交换（这里可以不是上一个元素，只要是交换过的元素均可）*/
      for (int k = 1; k <= n; k++){
        printf("%d ",a[k]);
      }
      printf("\n");
    }
  }
  return 0;
}
```



---

## 作者：Scorilon (赞：1)

因为要使求得的排列链最长，所以我们可以先思考最长是多少。

因为排列链的固定性是向下递减，所以每次固定性减 $1$ 所得的排列链肯定是最优情况。

所以我们考虑每次交换元素时令固定性只减 $1$。

那么在刚开始的操作中，要使排列链无序，那么就令任意两个元素交换其位置，为了方便后续操作，将 $1$ 和 $n$ 上面的元素进行交换。可以证明，交换这两个元素的固定性无论怎么样都是 $-2$，因此在第一次交换时，固定性一定是 $-2$，剩下的就拿 $1$ 和其余位置上的元素交换，每次固定性 $-1$，即有 $n-1$ 次交换操作，加上初始的数列，即最长为 $n$。

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int t,n,a[105];

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		printf("%d\n",n);
		for(int i=1;i<=n;i++) {//初始化
			a[i]=i;
			printf("%d ",a[i]);
		}
		printf("\n");
		int x=a[1];//交换1与n上的元素
		a[1]=a[n];
		a[n]=x;
		for(int i=1;i<=n;i++) {
			printf("%d ",a[i]);
		}
		puts(" ");
		int op=n;//记录1的位置
		for(int i=2;i<n;i++) {//2~n-1为a[i]=i的
			int x=a[i];
			a[i]=a[op];
			a[op]=x;
			op=i;//更新1的位置
			for(int j=1;j<=n;j++) printf("%d ",a[j]);
			printf("\n"); 
		}
	}
	return 0;
}
```


---

## 作者：qip101 (赞：0)

### 题意：

[ CodeForces 1716B](https://www.luogu.com.cn/problem/CF1716B)

### Solution:

贪心。

让每次操作的两个数满足一定条件（参见下面的代码）。

这样可以使得操作数最大化，因为每次只有一个位置改变了。

构造：把一与其后面的每一个数交换。

### Code：

```cpp
#include <bits/stdc++.h>
#define MAXN 100100
using namespace std;
int T,n,a[MAXN];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> T;
	while(T--)
	{
		cin >> n;
		cout << n << endl;
		for(int i=1;i<=n;i++)
		{
			cout << i << " ";
			a[i]=i;
		}
		cout << endl;
		for (int i=1;i<=n-1;i++)
		{
			swap(a[i],a[i + 1]);
			for (int j=1;j<=n;j++)
				cout << a[j] << " ";
			cout << endl;
		}
	}
	return 0;
}

```


---

## 作者：konyakest (赞：0)

为了简便叙述，定义一个排列 $a$ 的某个位置 $i$ 是“固定的”，当且仅当 $ a_i=i $

首先，我们通过 ``这些排列的 “固定性” 严格递减`` 可以得知，这个序列最多有 $n+1$ 个排列，这 $n+1$ 个排列的 “固定性” 为 $n,n-1,n-2,n-3,...,1,0$

but，我们发现，第一次交换，无论如何，都会把 “固定性” 为 $n$ 的排列变为 “固定性” 为 $n-2$ 的排列

所以，这个序列其实**不可能**有 $n+1$ 个排列，最多只能有 $n$ 个，这 $n$ 个排列的 “固定性” 为 $n,n-2,n-3,...,1,0$

接着，我们就很自然的想到构造方法：

- 在前一个排列中，找到一个 “固定的” 位置和一个 “不固定的” 位置

- 交换这两个位置

- 重复上述操作，直到找不到 “固定的” 位置

还有一个小细节，第一次是找不到“不固定的”位置的，所以要把表示 “不固定的” 位置的变量初始化为任意一个大于 $1$ 的数（因为 $1$ 是第一个“固定的”位置）

这样，这道题就做完了

AC code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i,j,k) for (signed i=signed(j);i<=signed(k);i++)
#define endl '\n'
const int maxn=105;

int t,n;
int a[maxn];

signed main() { 
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	F(_,1,t){
		cin>>n;
		cout<<n<<endl;
		F(i,1,n) a[i]=i;//初始化排列
		while(1){
			F(j,1,n) cout<<a[j]<<" ";
			cout<<endl;
			int no=n,yes=0;//细节
			F(j,1,n) if(a[j]==j){yes=j;break;}//寻找“固定的”位置
			F(j,1,n) if(a[j]!=j){no=j;break;}//寻找“不固定的”位置
			if(!yes) break;//如果找不到“固定的”位置，说明这个序列的“固定性”为0，直接退出
			swap(a[no],a[yes]);//交换
		}
	}
	return 0; 
}
```

---

## 作者：DANIEL_x_ (赞：0)

## 思路
显然，我们知道在不变化的情况下，固定值为 $n$，在第一次变化的时候，固定值只能是 $n-2$。

在下一次变化中，可以做到固定值为 $n-3$，实现思路为可以第一步交换，$(n-1,n)$，然后再交换位置在 $n-1,n-2$ 的数。

依次类推，最终可以得到答案。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=110;
int main()
{
    ll n,T,maxx,cnt=0,ans=0,t,a[maxn],k;
    cin>>T;
    while(T--)
    {
        cin>>n;
        if(n==2) cout<<"2"<<"\n"<<"1 2"<<"\n"<<"2 1"<<endl;
        if(n==3) cout<<"3"<<"\n"<<"1 2 3"<<"\n"<<"3 2 1"<<"\n"<<"3 1 2"<<endl;//这个特判不必要可以直接合并在下面
        t=n,k=n;
        for(int i=1;i<=n;i++)
            a[i]=i;
        if(n>=4)
        {
            cout<<n<<endl;
            for(int i=1;i<=k;i++) 
            {
                cout<<a[i]<<" ";
            }
            cout<<endl;
            while(t!=1)
            {
                swap(a[n],a[n-1]);
                n-=1,t-=1;
                for(int i=1;i<=k;i++) cout<<a[i]<<" ";
                cout<<endl;
            }
        }
    }    
    return 0;
}
```


---

## 作者：Gumbo (赞：0)

先来翻译一下题目的大致意思：

有 `t` 组询问，每组询问让你输出 `n` 组 `1~n` 的排列，其中错位元素的数量必须单调增，而且每一个数列都应在前一个数列的基础上交换两个元素得来。

那么我们不妨按照它说得来，因为我们最少是没有错位元素，最多则是有 `n` 个，因此我们的第一行排列的错位元素可能是 `0` 个或者 `1` 个，但是不存在有且仅有 `1` 个错位元素的排列，因此我们的第一行数列一定是 `1~n` 的一个连续数列。

然后我们再来想怎么由前一个数列得到后一个数列，由题意可知，我们要交换两个元素，并使错位对的数量增长最慢，显然我们每次操作最少会出现一个错位对（第一次操作必定两个），因此我们的一个交换元素一定是之前换走的错位元素，并且还不能换回来。

我们参照冒泡排序的思想，每次交换相邻两项，冒泡排序每次会少一个逆序对，而这里则会多一个错位元素，正好能满足我们的需求。

那么代码的思路也就很好想了，每次交换前面交换的元素以及它的后面一个元素，每次向后推进一个，正好能满足我们需要的 `n-1` 次交换。

代码就放在这里好了，不算很长：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[105];
int main()
{
    int t;
    int n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printf("%d\n", n);
        for (int i = 1; i <= n; ++i)
        {
            a[i] = i;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                printf("%d ", a[j]);
            }
            printf("\n");
            swap(a[i], a[i + 1]);
        }
    }
}
```

这边注意一个坑点，每次输出前要把 `n` 单独输出，我眼瞎没看见，罚时吃饱。


---

## 作者：qfpjm (赞：0)

# 题目大意

- 给定 $T$ 个 $n$，表示有 $T$ 个长度为 $n$ 的 $1\dots n$ 的序列。

- 你可以进行一些操作，每次操作交换序列中的两个数，要求交换后的序列比交换前的序列的 $a_i=i$ 的数量少，当不存在 $a_i=i$ 时停止。

- 求出最多的操作数。

# 题解

- 考虑贪心。

- 我们可以让每次操作的两个数 $a_i,a_j$ 满足 $a_i=i,a_j\ne j$（顺序不一定是这样）。显然可以使得操作数更多，因为只改变了一个位置。当然，第一次操作无论如何都只能改变两个位置。

- 我们考虑一种比较好构造的方法。我们可以将 $1$ 依次与其后面的一个数交换，直到其到达序列的最后一个。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n, a[105];

int main()
{
	cin >> T;
	while (T --)
	{
		cin >> n;
		cout << n << endl;
		for (int i = 1 ; i <= n ; i ++)
		{
			a[i] = i;
			cout << a[i] << " ";
		}
		cout << endl;
		for (int i = 1 ; i < n ; i ++)
		{
			swap(a[i], a[i + 1]);
			for (int j = 1 ; j <= n ; j ++)
			{
				cout << a[j] << " ";
			}
			cout << endl;
		}
	}
}
```


---

## 作者：13802919466djh (赞：0)

[更好的体验？](https://www.luogu.com.cn/blog/dujiahao123456/solution-cf1716b)

# 解法
首先，第一次交换元素，一定会使得 $a_1$ 的固定性减 $2$。

如果第二次交换元素时，我们交换了一个之前已经交换过的元素，固定性只会减 $1$。

同理，我们往后的每一次交换，都与之前交换过的元素交换，就可以求出答案了。

# 代码
**Talking is cheap,show me the code.**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){int f=1,x=0;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1; ch=getchar();}while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}return x*f;}
inline void write(int x){if (x<0){putchar('-');x=-x;}if(x>9) write(x/10);putchar(x%10+'0');}
inline void Write(int x){write(x);putchar('\n');}
const int N=105;
int t,n,a[N];
signed main(){
	t=read();
	while (t--){
		n=read();
		for (int i=1;i<n;i++)write(a[i]=i),putchar(' ');
		Write(a[n]=n);
		for (int i=1;i<n;i++){
			swap(a[i],a[i+1]);//跟上一个数交换 
			for (int j=1;j<n;j++)write(a[j]),putchar(' ');
			Write(a[n]);
		}
	}
    return 0;
}
```

---

## 作者：Clyfort (赞：0)

## 思路

理想情况下，我们希望 $\texttt{fixedness}$ 为 $n, n-1, n-2, ..., 0$。这将是一个长度为 $n+1$ 的链。

然而，在一次互换之后，不可能使得 $\texttt{fixedness} - 1$。第一次交换总是会使 $\texttt{fixedness} - 2$。

但是 $n, n-2, n-3, ..., 0$ 这样的序列总是可以实现。

例如，交换元素 $1$ 和 $2$，然后交换元素 $2$ 和 $3$，然后交换 $3$ 和 $4$，以此类推。

**时间复杂度为 $O(n^2)$。**



## python 代码
```
for i in range(int(input())):
	n = int(input())
	p = [i + 1 for i in range(n)]
	print(n)
	for i in range(n):
		print(*p)
		if i < n - 1:
			p[i], p[i + 1] = p[i + 1], p[i]
```

---

## 作者：_FJX_ (赞：0)

我们不难发现，最开始的数列一定是从 $1$ 到 $n$ 最优，然后题目中要求每次只能交换旧数列的相邻两个元素，然后产生新数列。

当第一次交换时，不管怎么交换，固定性都会 $-2$，之后的交换只要每次都与交换过的元素的数交换，那么固定性就会只 $-1$ ( 显然，想让固定性减小最慢，每次固定性一定只 $-1$ )。

所以这样我们可以得知每一次交换第一个和第 $i(2 \leq i \leq n
)$ 个数即可。

下面举了个例子:

原数组: $a = [1,2,3,4,5,6]$，固定性为 $7$。

一次交换后：$a = [2,1,3,4,5,6]$，固定性为 $5$。

两次交换后：$a = [3,1,2,4,5,6]$，固定性为 $4$。

三次交换后：$a = [4,1,2,3,5,6]$，固定性为 $3$。

四次交换后：$a = [3,1,2,4,5,6]$，固定性为 $2$。

五次交换后：$a = [3,1,2,4,5,6]$，固定性为 $1$。

六次交换后：$a = [6,1,2,4,5,3]$，固定性为 $0$。

_AC code:_

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[105];
void work()
{
	int n;
	cin >> n;
	cout << n << endl;
	for (int i = 1; i <= n; i++) 
	{
		a[i] = i;
		cout << a[i] << ' ';
	}
	cout << "\n";
	for (int i = 2; i <= n; i++) 
	{
		swap(a[1], a[i]);
		for (int j = 1; j <= n; j++) 
		{
			cout << a[j] << ' ';
		}
		cout << "\n";
	}
	return;
 } 
int main(){
    ios_base::sync_with_stdio(false);
	cin.tie (0);
	cout.tie (0);
	int T;
	cin >> T;
	while (T--)
	{
		work();//多组 
	}
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

一道构造典题。

首先得出一个结论：第一次交换时，$fixedness$ 会减去 $2$；其他时候交换，$fixedness$ 会减去 $1$。

接下来讲构造：

1. 输出原数组
2. 接下来 $n-1$ 此操作，第 $i$ 次交换 $n$ 和 $n-i$ 两个数，这样 $fixedness$ 会减去 $1$ （除了第一次操作 $fixedness$ 会减去 $2$），显然这是最优解。所以总共会经过 $n$ 次操作。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int t,n;
int a[N];
int main(){
	cin>>t;
	while(t--){//多组数据
		cin>>n;
		memset(a,0,sizeof(a));
		cout<<n<<endl;
		for(int i=1;i<=n;i++){
			a[i]=i;//不要忘了输出原数组
			cout<<i<<" ";
		}
		cout<<endl;
		int cur=n;
		while(cur>=2){
			swap(a[cur],a[cur-1]);//开始构造
			cur--;
			for(int i=1;i<=n;i++){
				cout<<a[i]<<" ";//输出每一次操作后当前数组的状态
			}
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：__KrNalty__ (赞：0)

场上被聪明的谷歌翻译搞到了，看懂题意之后应该是各位都能一眼秒掉的题目吧。

### 题意简述：

对于一个长度为 $n$ 的排列 $p$，若 $a_i=i$，则称其为“置换的不动点”。

现在给你一个整数 $n$，且 $a_1=[1,2,3,\dots,n]$，你需要构造出一个最长的序列 $a_1,a_2,a_3,\dots$ 。使得对于每一个 $2 \leq i$ 都有 $a_i$ 中“置换的不动点”的数量严格大于 $a_{i-1}$ 中“置换的不动点”的数量。如果有多种构造方案，输出任意一种。

### 思路分析：

很简单。

由于第一次交换时一定会使“置换的不动点”的数量减少两个，之后每一次操作都会使“置换的不动点”的数量减少一个，并且刚开始“置换的不动点”的数量为 $n$ ，那么想要使得最后的时候 “置换的不动点”的数量最少也就是为 $0$，最多只能进行 $n$ 次操作，每次操作交换相邻两个数字就行。

为什么如何理解每次操作交换相邻两个数字就行？

很简单，举个例子就明白了：

假设 $n=5$：

则 $a_1=[1,2,3,4,5] \ \text{fixedness}=5$

$a_2=[2,1,3,4,5] \ \text{fixedness}=3$

$a_3=[2,3,1,4,5] \ \text{fixedness}=2$

$a_4=[2,3,4,1,5] \ \text{fixedness}=1$

$a_5=[2,3,4,5,1] \ \text{fixedness}=0$

显然的，这样子就可以使第一次交换时使“置换的不动点”的数量减少两个，之后每一次操作使“置换的不动点”的数量减少一个，使序列最长。

当然，只要满足第一次交换时一定会使“置换的不动点”的数量减少两个，之后每一次操作都会使“置换的不动点”的数量减少一个，就可以使序列最长。

### 完整代码供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 105;
int n, a[maxn];
signed main() {
	int T = 1;
	cin >> T;
	while (T--) {
		cin >> n;
		cout << n << endl;
		for (int i = 1; i <= n; i++) {
			a[i] = i;
			cout << a[i] << " ";
		}
		cout << endl;
		for (int i = 1; i <= n - 1; i++) {
			swap(a[i], a[i + 1]);
			for (int j = 1; j <= n; j++) {
				cout << a[j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}
```

---

## 作者：C_Cong (赞：0)

[博客传送门](http://blog.ccongcirno.cn/2022/08/06/%E6%B4%9B%E8%B0%B7%E9%A2%98%E8%A7%A3-CF1716B-%E3%80%90Permutation%20Chain%E3%80%91/#more)

### 题意翻译

现在有一个长度为 $n$ 的数组 ${1,2,3,4,...,n}$ ，你每次操作可以交换其中任意两个数字的位置，但是要确保除了第一次交换是有两个数字不在原来的位置上外，后续每次操作之后只能增加一个不在原来位置上的数字（其实对应的就是题目中的 `longest permutation chain` ）

当所有数字都不在原来的位置时，操作结束

### 解题过程

首先根据题意，显然本题除了每组询问的 $chain$ 长度唯一外，操作过程并不唯一

题目其实就是要求我们构造一种操作使得符合上述题意

我这里采用的是先交换首位两个数字，再按照右左右左的顺序依次交换相邻两个数（因为第三组样例是）

~~貌似语言不好说明，那就举个例~~

$n$ 为奇数的例子

当 $n=5$ 时：

原始数组： $[1,2,3,4,5] \ \operatorname{fixedness}=5$

操作1： $[5,2,3,4,1] \ \operatorname{fixedness}=3$

操作2： $[5,2,3,1,4] \ \operatorname{fixedness}=2$

操作3： $[2,5,3,1,4] \ \operatorname{fixedness}=1$

操作4： $[2,5,1,3,4] \ \operatorname{fixedness}=0$

因此链长为 $5$

$n$ 为偶数的例子

$n=4$ 时：

原始数组： $[1,2,3,4] \ \operatorname{fixedness}=4$

操作1： $[4,2,3,1] \ \operatorname{fixedness}=2$

操作2： $[4,2,1,3] \ \operatorname{fixedness}=1$

操作3： $[2,4,1,3] \ \operatorname{fixedness}=0$

因此链长为 $4$

### 注意

不要漏了输出原始数组！


### 代码实现

------------

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int n,m,t,num[110],l,r; //l,r分别是目前左右操作的位置
bool pd=false;

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        l=1;
        scanf("%d",&n);
        r=n;
        pd=false;
        printf("%d\n",n);
        for(int a=1;a<=n;++a)
        {
            num[a]=a;
            printf("%d ",num[a]);
        }
        printf("\n");
        if(n%2==0) //n为偶数时
        {
            while(l!=n/2+1||r!=n/2)
            {
                if(l==1&&r==n) //第一步
                {
                    int tmp=num[l];
                    num[l]=num[r];
                    num[r]=tmp;
                    for(int a=1;a<=n;++a)
                    {
                        printf("%d ",num[a]);
                    }
                    printf("\n");
                    l++;
                    r--;
                    continue;
                }
                else
                {
                    if(pd) //左边交换
                    {
                        pd=false;
                        int tmp=num[l];
                        num[l]=num[l-1];
                        num[l-1]=tmp;
                        for(int a=1;a<=n;++a)
                        {
                            printf("%d ",num[a]);
                        }
                        printf("\n");
                        l++;
                    }
                    else //右边交换
                    {
                        pd=true;
                        int tmp=num[r];
                        num[r]=num[r+1];
                        num[r+1]=tmp;
                        for(int a=1;a<=n;++a)
                        {
                            printf("%d ",num[a]);
                        }
                        printf("\n");
                        r--;
                    }
                }
            } 
        }
        else //n为奇数时
        {
            while(r!=(n+1)/2-1)
            {
                if(l==1&&r==n) //第一步
                {
                    int tmp=num[l];
                    num[l]=num[r];
                    num[r]=tmp;
                    for(int a=1;a<=n;++a)
                    {
                        printf("%d ",num[a]);
                    }
                    printf("\n");
                    l++;
                    r--;
                    continue;
                }
                else
                {
                    if(pd) //左边交换
                    {
                        pd=false;
                        int tmp=num[l];
                        num[l]=num[l-1];
                        num[l-1]=tmp;
                        for(int a=1;a<=n;++a)
                        {
                            printf("%d ",num[a]);
                        }
                        printf("\n");
                        l++;
                    }
                    else //右边交换
                    {
                        pd=true;
                        int tmp=num[r];
                        num[r]=num[r+1];
                        num[r+1]=tmp;
                        for(int a=1;a<=n;++a)
                        {
                            printf("%d ",num[a]);
                        }
                        printf("\n");
                        r--;
                    }
                }
            }
        }
    }
    return 0;
}
```

觉得有用顶上去才能让更多人看到哦awa

---

## 作者：cachejtt (赞：0)

## 题意
给你一个数 $n$，你需要构造 $k$ 个 $n$ 的排列，满足以下性质。

我们定义一个序列的固定值为序列中 $a_i=i$ 的数字的个数。对于你构造的 $k$ 个长度为 $n$ 的序列，每一个序列的固定值必须严格小于上一个序列。并且，每一个序列与上一个序列之间，有且仅有一对数被交换了。

由于每一步交换都会使数列的固定值减小，你需要找到一个最长的操作序列来使得固定值减小最慢。

求 $k$ 的最大值，并输出这 $k$ 个排列。

## 思路
要求这个数列最长，那么显然我们应该从固定值以 $n$ 开始，以 $0$ 结束。第一步固定值会减小 $2$，只需保证后面每一步固定值都至少减小 $1$，则可实现 $n-1$ 步操作，即有 $n$ 个数列。

那么，如何做到除第一步外每一步都减小 $1$ 呢？其实，只需要每一步把一个 $a_i=i$ 的位置给移动走，就可以做到固定值减小 $1$ 了。

考虑一开始每个数都等于其下标，即 $a_1=1,a_2=2,\dots,a_n=n$，则每次交换相邻两个数即可。具体交换方式见代码注释。

## 代码
```cpp
#include<bits/stdc++.h> 
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ms(x, i) memset((x),(i),sizeof x)
#define endl "\n"
using namespace std;
int t,n,m,k,a[105];
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    rep(i,1,n)a[i]=i;
    if(n==2){
      cout<<2<<endl;
      cout<<"1 2"<<endl;
      cout<<"2 1"<<endl;
      continue;
    }
    cout<<n<<endl;
    rep(j,1,n)cout<<a[j]<<" ";//一开始输出固定值为 n 的序列
    cout<<endl;
    rep(i,1,n-1){
      swap(a[i],a[i+1]);//每次交换相邻两个，即可使得第 i+1 位失去固定性。
      rep(j,1,n)cout<<a[j]<<" ";
      cout<<endl;
    }
    
  }
  return 0;
}
```

---

