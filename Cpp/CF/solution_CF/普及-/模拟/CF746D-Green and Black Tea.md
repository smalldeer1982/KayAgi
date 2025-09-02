# Green and Black Tea

## 题目描述

Innokentiy likes tea very much and today he wants to drink exactly $ n $ cups of tea. He would be happy to drink more but he had exactly $ n $ tea bags, $ a $ of them are green and $ b $ are black.

Innokentiy doesn't like to drink the same tea (green or black) more than $ k $ times in a row. Your task is to determine the order of brewing tea bags so that Innokentiy will be able to drink $ n $ cups of tea, without drinking the same tea more than $ k $ times in a row, or to inform that it is impossible. Each tea bag has to be used exactly once.

## 样例 #1

### 输入

```
5 1 3 2
```

### 输出

```
GBGBG
```

## 样例 #2

### 输入

```
7 2 2 5
```

### 输出

```
BBGBGBB```

## 样例 #3

### 输入

```
4 3 4 0
```

### 输出

```
NO
```

# 题解

## 作者：_Michael0727_ (赞：10)

# 题解：CF746D Green and Black Tea

[文章食用效果更佳](https://www.luogu.com.cn/article/11avv92r)

---

## 审题
[题目传送门](https://www.luogu.com.cn/problem/CF746D)

---
## 思路

一开始，由于每次可选择红茶或绿茶，所以我考虑使用深搜 DFS 进行枚举，但是无奈[超时](https://www.luogu.com.cn/record/161464638)了。

后来，我发现其实可以用贪心来做，每次如果绿茶数量大于红茶数量，则一直喝绿茶直到不能再喝了（连续喝的次数 $ \geq k $），红茶同理。

最后，有的情况是构造不了的，要进行特判。

易证，$ a + 1 < \frac{b + k - 1} {k} $ 或 $ b + 1 < \frac{a + k - 1} {k} $ 时都不可能构造出。

添加以上特判后即可通过。

---

**AC 代码**
``` cpp
# include <bits/stdc++.h>
using namespace std ;
int n , k , a , b , ai , bi ; 
int main ( )
{
	cin >> n >> k >> a >> b ;
	if ( ( a + 1 < ( b + k - 1 ) / k ) || ( b + 1 < ( a + k - 1 ) / k ) ) // 无解特判 1
	{
		cout << "NO" << endl ;
		exit ( 0 ) ;
	}
	if ( k == 0 ) // 无解特判 2
	{
		cout << "NO" << endl ;
		exit ( 0 ) ;
	}
	for ( int i = 1 ; i <= n ; i ++ )
	{
		if ( a >= b && ai < k )
		{
			bi = 0 ;
			for ( int j = ai ; j < k && a >= 1 && i <= n ; i ++ , j ++ , a -- )
			{
				cout << 'G' ;
				ai ++ ;
			}
			if ( b )
			{
				cout << 'B' ;
				ai = 0 ;
				bi = 1 ;
				b -- ;
			}
		}
		else if ( bi < k )
		{
			ai = 0 ;
			for ( int j = bi ; j < k && b >= 1 && i <= n ; i ++ , j ++ , b -- )
			{
				cout << 'B' ;
				bi ++ ;
			}
			if ( a )
			{
				cout << 'G' ;
				bi = 0 ;
				ai = 1 ;
				a -- ;
			}
		}
		else if ( bi < k && b )
		{
			cout << 'B' ;
			ai = 0 ;
			bi ++ ;
			b -- ;
		}
		else
		{
			cout << 'G' ;
			bi = 0 ;
			ai ++ ;
			a -- ;
		}
	}
	return 0 ;
}
```
---
[AC记录](https://www.luogu.com.cn/record/161469841)

---

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF746D)
# 思路
这道题可以用贪心做。

首先判断能否做到。用贪心很容易就能想到如果 $a<\lfloor \frac{b+k-1}{k}\rfloor -1$ 或者 $b<\lfloor \frac{a+k-1}{k}\rfloor -1$，那么就无法做到。如果能做到，就构造方法。仍然使用贪心法。每次都用当前数量更多的那种茶，同时考虑有没有连续使用超过 $k$ 次即可。
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,nw,a[5];//m表示k，啊a[1]表示a，a[0]表示b，nw表示当前连续用了几次 
char c='G';
int main()
{
	cin>>n>>m>>a[1]>>a[0];
	if (a[0]<(a[1]+m-1)/m-1||a[1]<(a[0]+m-1)/m-1)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++)
		if (nw<m&&a[c%2]>a[!(c%2)])//两种条件必不可少 
		{
			nw++;
			cout<<c;
			a[c%2]--;
		}
		else//换种茶 
		{
			nw=1;
			if (c=='G')
				c='B';
			else
				c='G';
			cout<<c;
			a[c%2]--;
		}
}
```

---

## 作者：cute_overmind (赞：3)

### 题目大意
[自行审题](https://www.luogu.com.cn/problem/CF746D)

### 思路
考虑贪心。

我们可以发现，这道题类似于搜索中的联通块问题，所以刚开始考虑使用 `dfs` 求解。

但是写出来发现喜提 `TLE` 一枚，所以我们应尝试贪心算法进行求解。

通过观察样例发现：当我们剩余红茶数量比绿茶多时，我们可以尽可能的去使用红茶直至红茶数量少于 $k$ 包。

如果红茶数量已经没有了或已经达到 $k$ 包，那么再去使用 $1$ 包绿茶。

### 代码
思路已经明确，代码就不贴了。

---

## 作者：_Starlit__Sky_ (赞：3)

# 洛谷 CF746D 题解

[题目传送门](https://www.luogu.com.cn/problem/CF746D)

## 题目算法

BFS 枚举

## 题目思路

使用 BFS 枚举。如果没喝过红茶；或者最后一次喝的不是红茶；或者现在连续喝红茶次数 $< k$ 就可以喝红茶，绿茶同理 。

## 代码
```python
n,k,a,b = map(int,input().split()) # 输入
bfs = [['',0]]; B = 0; G = 0 # 变量初始化
if (b + k - 1) / k > a + 1 or (a + k - 1) / k > b + 1: print('NO') # 特判（做不到的情况）
else: # 如果可以做到
    while bfs: # BFS 枚举
        if len(bfs[0][0]) == n: # 若已经把茶叶喝完了    就退出循环
            break
        # 队头出队
        head = bfs.copy()
        bfs = []
        # 可拓展路径入队
        for ele,times in head:
            # ( 没喝过红茶 或者 最后一次喝的不是红茶 ) 并且 只要还有红茶可以喝（红茶数量 > 0）    就可以喝红茶
            if ('B' not in ele or ele[-1] != 'B') and ele.count('B') < b: bfs.append([ele + 'B',1])
            # 否则只要现在连续喝红茶次数 < k 并且 还有红茶可以喝（红茶数量 > 0）    就可以喝红茶
            elif times < k and ele.count('B') < b: bfs.append([ele + 'B',times + 1])
            # ( 没喝过绿茶 或者 最后一次喝的不是绿茶 ) 并且 只要还有绿茶可以喝（绿茶数量 > 0）    就可以喝绿茶
            if ('G' not in ele or ele[-1] != 'G') and ele.count('G') < a: bfs.append([ele + 'G',1])
            # 否则只要现在连续喝绿茶次数 < k 并且 还有绿茶可以喝（绿茶数量 > 0）    就可以喝绿茶
            elif times < k and ele.count('G') < a: bfs.append([ele + 'G',times + 1])
    print(bfs[0][0]) # 输出
```


---

## 作者：peppaking8 (赞：3)

## 思路
首先，这道题是 $\text{Special Judge}$，所以对答案的要求很宽松。

然后就考虑怎么达到题目的要求。题目让每个“连通块”的大小都不超过 $k$，那么我们自然就想到了：如果“连通块”个数足够多的话，就越可能满足题目的要求。

不妨设 $a>b$。那么我们就将 $b$ 包红茶分开，中间形成了 $b+1$ 处可以放绿茶的地方。考虑放置尽量平均，所以每个地方放置 $\dfrac{a}{b+1}$ 个或者 $\dfrac{a}{b+1}+1$ 个，而 $\dfrac{a}{b+1}+1$ 的个数为 $a\ \text{mod}\  (b+1)$。

然后就是判断是否无法满足要求了。如果 $\dfrac{a}{b+1}>k$，那么显然不满足要求；

如果 $\dfrac{a}{b+1}=k$，那么还要判断 $a$ 是否被 $b+1$ 整除。如果不整除，说明存在 $\dfrac{a}{b+1}+1$，也不满足要求。

要注意的是，$a<b$ 的情况也要考虑哦！

这就是思路啦！~~激动人心的时刻到了~~

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a,b;
bool Swaped=false;
int main(){
	scanf("%d%d%d%d",&n,&k,&a,&b);
	if(a==b){//特判a=b的情况
		for(int i=1;i<=a;i++) printf("BG");//相隔输出即可
		printf("\n");
		exit(0);
	}
	if(a<b) swap(a,b),Swaped=true;
    //这里用一个较为简单的方法，就是记录是否交换过，在后面输出字母时根据Swaped的不同判断应该输出什么
	int num1=a/(b+1);
	int num2=a%(b+1);
	if(num1>k){//判断是否不满足要求
		printf("NO\n");
		exit(0);
	}
	if(num1==k&&num2){
		printf("NO\n");
		exit(0);
	}
	for(int i=1;i<=num2;i++){//前num2个是num1+1
		if(i!=1){//中间插着个数较小的字母
			if(Swaped) printf("G");
			else printf("B");
		}
		for(int j=1;j<=num1+1;j++){
			if(Swaped) printf("B");
			else printf("G");
		}
	}
	for(int i=num2+1;i<=b+1;i++){//后面的是num1
		if(i!=1){
			if(Swaped) printf("G");
			else printf("B");
		}
		for(int j=1;j<=num1;j++){
			if(Swaped) printf("B");
			else printf("G");
		}
	}
	printf("\n");
	exit(0);//记得点个赞再走呀~
}
```

---

## 作者：Chinshyo (赞：3)

# 题目分析
这道题表面上看上去挺简单，其实仔细研究一下还是值得钻研的。我本人做这道题使用的任然是$ DFS01 $背包。不过呢，与往常背包不同的是，这次递归中需要加许多参数。就数据强度来看，栈问题不大。
# 递归过程
我们使用一个栈以及两个临时栈。每次在里面$ push $当前的解。只有“G”与“B”。两个栈分别处理和红茶和和绿茶的情况。两种情况都要考虑到已经连续喝了几次某种茶。


在递归函数里，我们用到$ dep,s,g,h,last $ 这几个变量。分别代表深度、连续喝的总数、绿茶喝的总数、红茶喝的总数以及上次喝的茶是啥。$ 0 $代表绿茶，$1$代表红茶。

### 递归代码：
```cpp
void dfs(int dep,int s,int g,int h,bool last)
{
	if(dep>n)
	{
		stack<string>temp1=temp;
		while(!temp1.empty())
		{
			cout<<temp1.top();
			temp1.pop();
		}
		exit(0);
	}
	else
	{
		if(last==0)
		{
			temp.push("G");
			if(g+1<=a)dfs(dep+1,s,g+1,h,!last);
			if(s+1<=b&&s<k) dfs(dep+1,s+1,g,h+1,last);
			else
			{
				cout<<"NO"<<endl;
				exit(0);
			}
		}
		else
		{
			temp.push("B");
			if(s+1<=b)dfs(dep+1,s,g,h+1,!last);
			if(g+1<=a&&s<k) dfs(dep+1,s+1,g,h,last);
			else
			{
				cout<<"NO"<<endl;
				exit(0);
			}
		}
	}  
	if(!temp.empty()) temp.pop();
}
```
# 主函数
最后主函数的程序就简单了。像往常一样，$ dep $总是要是$ 1 $开始，其他都是$ 0 $；但是有一个问题，我们不仅要考虑第一次喝绿茶的情况，第一次还可能是红茶。所以我们在刚开始写递归函数的时候，我们需要递归两遍
### 主函数代码：
```cpp
int main()
{
	cin>>n>>k>>a>>b;
	dfs(1,0,0,0,0);
	dfs(1,0,0,0,1);
	return 0;
}
```
# 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a,b;
stack<string>temp;
void dfs(int dep,int s,int g,int h,bool last)
{
	if(dep>n)
	{
		stack<string>temp1=temp;
		while(!temp1.empty())
		{
			cout<<temp1.top();
			temp1.pop();
		}
		exit(0);
	}
	else
	{
		if(last==0)
		{
			temp.push("G");
			if(g+1<=a)dfs(dep+1,s,g+1,h,!last);
			if(s+1<=b&&s<k) dfs(dep+1,s+1,g,h+1,last);
			else
			{
				cout<<"NO"<<endl;
				exit(0);
			}
		}
		else
		{
			temp.push("B");
			if(s+1<=b)dfs(dep+1,s,g,h+1,!last);
			if(g+1<=a&&s<k) dfs(dep+1,s+1,g,h,last);
			else
			{
				cout<<"NO"<<endl;
				exit(0);
			}
		}
	}  
	if(!temp.empty()) temp.pop();
}
int main()
{
	cin>>n>>k>>a>>b;
	dfs(1,0,0,0,0);
	dfs(1,0,0,0,1);
	return 0;
}
```


---

## 作者：Wsy_flying_forever (赞：2)

### 概述  
   一道模拟的入门题  
### 思路  
   一个显然的性质，对于每次选择，我们只需考虑残余数量最多的茶叶即可  
   使用贪心算法，选取剩下数量最多的茶叶，数量累计 $k$ 次后，就更换种类  
   再继续贪心。判断是否无方案满足要求时，也不必像其他题解一样提前预判，  
   每次直接将 $a,b$ 数量减一即可，若为负数则无解，加上 $!$ 取反运算,这两点技  
   巧会使码量明显减少，无压行也就 $25$ 行。
### 代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,k,a[2];
int ans[maxn];
int now;
int main() {
	scanf("%d%d%d%d",&n,&k,&a[0],&a[1]);
	if (a[0]<a[1]) now=1;
	for (int i=1,cnt=0;i<=n;i++) {
	  if (cnt<k && a[now]>=a[!now]) {
	  	ans[i]=now;
	  	cnt++;
	  	a[now]--;
	  }
	  else cnt=1,now=!now,ans[i]=now,a[now]--;
	  if (a[now]<0) {
	    printf("NO");
	    return 0;
	  }
	}
	for (int i=1;i<=n;i++)
	    ans[i] ? printf("B") : printf("G"); 
	return 0;
}
```


---

## 作者：__bjxx0201__ (赞：1)

## 题面大意

Innokentiy 想要喝 $n$ 杯茶，他有 $a$ 杯绿茶和 $b$ 杯红茶，相同的茶不能连续喝 $k$ 次，请让我们确定合法的顺序。当不能达到时，输出 `NO`。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF746D)

我一开始想要用深搜，但是想了一下会超时，于是还是要使用贪心的思路。

当剩下的红茶数量比绿茶数量多时，尽可能的多用红茶，直到没有 $k$ 包为止，然后使用一杯绿茶。绿茶同理。

什么时候无解呢？那就是当 $\frac{a}{b+1}>k$（这时不能用喝红茶和一杯绿茶的方式喝茶） 或者 $\frac{a}{b+1}=k$ 且 $a$ 除以 $b$ 的余数为 $k$ 时（同样的，不能用和绿茶+一杯红茶的方式喝茶），输出 `NO`。

此处可展示大致的无解以及考虑红茶的代码：

```
if (a/(b+1)>k || ((a/b+1)==k && a%b==k)) {
    	cout<<"NO";
    	return 0;
	}
    if (a==b) {
        for (int i=0;i<n;i++) {
            if (i%2==0) tea+='G';
            else tea+='B';
        }
    } 
	else if (a>b) {
        if (k==0) {
            cout<<"NO";
            return 0;
        }
        for (int i=0;i<n;i++) {
            if (i%(k+1)<k) {
                tea+='G';
                a--;
            } 
			else {
                tea+='B';
                b--;
            }
        }
        while (b>0) {
            tea+='B';
            b--;
        }
    } 
    //以下判断绿茶代码同理。
```

---

## 作者：Storm_Lightning (赞：1)

# 题解：CF746D Green and Black Tea

## 思路分析

本题是考察人的贪心能力，考虑若绿茶的数量小于红茶时，则可以先喝 $k-1$ 杯红茶之后在喝一杯绿茶。反之同理。

那么我们分来讨论一下无解情况。

- 当 $a \div (b+1) > k$ 时，代表不能按照 $(k-1)$ 包绿茶加上 $1$ 包红茶的方式喝茶，所以需要输出 NO，反之同理。

- 当 $a \div (b+1)=k$ 并且 $a \bmod b > 0$ 时，同样以不能按第一种方式喝茶，输出 NO，反之同理。

---

## 作者：__hjwucj__ (赞：1)

# 洛谷 CF746D Green and Black Tea 题解

[题目传送门](https://www.luogu.com.cn/problem/CF746D)

## 算法和思路

这题可以使用贪心算法，当剩余红茶包数比剩余绿茶包数多时，则尽可能多的用红茶，直到没法到达 $k$ 包为止，即没有红茶了或已经达到了 $k$ 包了，然后再只用一包绿茶。

当然，要考虑输出 $\texttt{NO}$ 的情况。当 $a \div (b+1)>k$ 或者 $a\bmod (b+1) \neq 0$ 且 $a \div (b+1)=k$ 的时候，一定没有解，输出 $\texttt{NO}$，结束。

## 代码参考

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a,b;
bool f=false;
int main ()
{
	cin>>n>>k>>a>>b;
	if (a<b) a^=b,b^=a,a^=b,f=true; 
	int c=a/(b+1),d=a%(b+1);
	if (c>k||c==k&&d) cout<<"NO",exit (0);
	for (int i=1;i<=d;i++)
	{
		if (i!=1) cout<<(f?'G':'B');
		for (int j=1;j<=c+1;j++) cout<<(f?'B':'G');
	}	
	for (int i=d+1;i<=b+1;i++)
	{
		if (i!=1) cout<<(f?'G':'B');
		for (int j=1;j<=c;j++) cout<<(f?'B':'G');
	}
	return 0;
}
```

---

## 作者：_czy (赞：1)

# 思路
一眼构造，如何构造？

这里给出一种有点贪的思路：当剩余红茶包数比剩余绿茶包数多时，则尽可能多的用红茶，直到没法到达 $k$ 包为止，即没有红茶了或已经达到了 $k$ 包了，然后再只用一包绿茶。~~如果还有的话~~

反之，就先交换，然后把字母~~取反~~更改。

至于无解情况，就利用上面思路，自己推一下。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a,b,c,d;
bool f;
int main(){
	cin>>n>>k>>a>>b;
	if(a<b){
		swap(a,b);
		f=1;
	}
	c=a/(b+1),d=a%(b+1);
	if(c>k||c==k&&d){
		cout<<"NO";
		return 0;
	}
	for(int i=1;i<=d;i++){
		if(i!=1){
			if(f)putchar('G');
			else putchar('B');
		}
		for(int j=1;j<=c+1;j++){
			if(f)putchar('B');
			else putchar('G');
		}
	}
	for(int i=d+1;i<=b+1;i++){
		if(i!=1){
			if(f)putchar('G');
			else putchar('B');
		}
		for(int j=1;j<=c;j++){
			if(f)putchar('B');
			else putchar('G');
		}
	}
	return 0;
}
```


---

## 作者：OI_AKed_me (赞：1)

# CF746D Green and Black Tea题解 #
[原题传送门](https://www.luogu.com.cn/problem/CF746D)

## 思路 ##
这道题一共有两个难点，一个是判断能否做到，一个是如何构造 ~~（废话）~~
### 判断 ###
什么时候做不到呢？

只有 $ a+1<(b+k-1)/k $ 或 $ b+1<(a+k-1)/k $ 时才做不到，其实很好想，就是一个每次用 $ k $ 包，而令一个连每次一包都做不到，那就可以判定这是不可能做到的。
### 构造 ###
如何构造？

这题有很多种方式来进行构造，这里给出一种：当剩余红茶包数比绿茶包数多时，则尽可能多的用红茶，直到没法再加为止，即没有红茶了或已经达到了 $ k $ 包了，反之同理，不过有许多细节需要注意，详见代码区。
## 代码 ##
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ss stable_sort
#define inf INT_MAX
#define re register
#pragma GCC opitimize(3)
using namespace std;
int n,k,a,b,bigger;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>a>>b;
	if((a+1<(b+k-1)/k)||(b+1<(a+k-1)/k)){//前面讲的难点1
		cout<<"NO";
		return 0;
	}
	bigger=2;
	while(a||b){
		if(a>b){
			for(int i=1;i<=min(a,k-(bigger==0));i++) cout<<'G';//注意加(bigger==0)，我在这死了两次
			if(b){
				cout<<'B';
				b--;
			}
			a-=min(a,k-(bigger==0));//同理
			bigger=1;
		}else{
			for(int i=1;i<=min(b,k-(bigger==1));i++) cout<<'B';//同理
			if(a){
				cout<<'G';
				a--;
			}
			b-=min(b,k-(bigger==1));//同理
			bigger=0;			
		}
		
	}
	return 0;
}
```
[目前最优解](https://www.luogu.com.cn/record/list?pid=CF746D&orderBy=1&status=&page=1)

---

## 作者：GeYang (赞：0)

# 题意

某人想喝 $n$ 杯茶。他有 $a$ 包绿茶和 $b$ 包红茶,但是他不喜欢连续喝同一种茶超过 $k$ 次，求喝茶顺序。

# 思路

因为本题有特判，所以相对宽松，输出符合题意即可。当剩余的红茶数量比绿茶多时，就一直输出红茶直至红茶数量少于 $k$ 包，再输出绿茶。

# 代码

和题解区的部分代码基本相同，故仅提供思路。

---

## 作者：Tulip_ (赞：0)

### 题意

Innokentiy 要喝茶，有红茶和绿茶，要是喝的茶连续的次数不超过 $k$ 次，输出喝茶顺序。

如果不能就输出 `NO`，否则输出顺序。

### 思路

这道题应该是贪心，因为 $n,k$ 的范围都小于等于 $10^5$，用 `bfs` 会 `TLE`。

当然这道题也是单纯的 `if` 和 `for` 的一个思维练习。

首先判断能不能做到，动一动笔我们就会知道，当 $k = 0$ 或 $a+1<(b+k-1)/k$ 或 $b+1<(a+k-1)/k$ 都不能做到，因此输出 `NO`。

那我们又要分类讨论：

如果红茶多，就一直喝红茶，直到不能喝为止，那就喝绿茶。

而绿茶同理：

如果绿茶多，就一直喝绿茶，直到不能喝为止，那就喝红茶。

那这道题就解决啦！

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a,b;
int o,o2;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>n>>k>>a>>b;
    if(k==0){
    	cout<<"NO";
			return 0;
	}else if(a+1<(b+k-1)/k||b+1<(a+k-1)/k){
		cout<<"NO";
			return 0;
	}
	for (int i=1;i<=n;i++){
		if (a>=b&&o<k){
			o2=0;
			for(int j=o;j<k&&a>=1&&i<=n;i++,j++,a--){
				cout<<'G';
				o++;
			}
			if(b){
				cout<<'B';
				o=0;
				o2=1;
				b--;
			}
		}else if(o2<k){
			o=0;
			for(int j=o2;j<k&&b>=1&&i<=n;i++,j++,b--){
				cout<<'B';
				o2++;
			}
			if(a){
				cout<<'G';
				o2=0;
				o=1;
				a--;
			}
		}else if(o2<k&&b){
			cout<<'B';
			o=0;
			o2++;
			b--;
		}else{
			cout<<'G';
			o2=0;
			o++;
			a--;
		}
	}
	return 0;
}
```

[AC](https://www.luogu.com.cn/record/162081244)

###### ~~自己再去做一下吧！~~

---

## 作者：Andy_WA (赞：0)

## 分析
虽然标签没有，但也可以推测出这题开了 `Special Judge`，所以对答案的顺序要求比较宽松。

## 思路
这题总体来说有两种情况：
+ 输出 `NO`，无解。
+ 输出答案，有解。
### 无解情况
若 $\displaystyle{\frac{a}{b+1}>k}$ 或者 $\displaystyle{\frac{a}{b+1}=k}$ 并且  $\displaystyle{a \bmod b \ne k}$，则无解。
### 有解情况
很明显是构造，一共很多种，这里给出一种偏向贪心算法的：

当 $a>b$ 时，则尽可能多的用红茶，直到没法再加为止，即没有红茶了或已经达到了 
$k$ 包了，反之亦然。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,GreenTea,BlackTea;
bool flag=false;

char PrintWork(bool k){
	if(k==true) return 'B';
	else return 'G';
}

int main(){
	cin>>n>>k>>GreenTea>>BlackTea;
	if(GreenTea<BlackTea){//其实这个判断运行后是与原先等价的
		swap(GreenTea,BlackTea);
		flag=true;
	}
	if(GreenTea/(BlackTea+1)>k || GreenTea/(BlackTea+1)==k && GreenTea%(BlackTea+1)!=0){
		cout<<"NO"<<endl;
	}else{
		for(long long i=GreenTea%(BlackTea+1)+1;i<=BlackTea+1;i++){
			if(i!=1) cout<<PrintWork(!flag);
			for(long long j=1;j<=GreenTea/(BlackTea+1);j++){
				cout<<PrintWork(flag);
			}
		}
		for(long long i=1;i<=GreenTea%(BlackTea+1);i++){
			if(i!=1) cout<<PrintWork(!flag);
			for(long long j=1;j<=GreenTea/(BlackTea+1)+1;j++){
				cout<<PrintWork(!flag);
			}
		}
		cout<<endl;
	}
	return 0;
}
```

最后，送大家一句话：
$$
\textit{\textbf{莫抄袭，棕了少年名，空悲切。}}
$$

---

