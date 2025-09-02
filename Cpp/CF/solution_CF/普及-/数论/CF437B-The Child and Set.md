# The Child and Set

## 题目描述

给你两个整数 $n,m$，要求选若干个不大于 $m$ 的数，使得这几个数的 Lowbit 值和等于 $n$。

## 样例 #1

### 输入

```
5 5
```

### 输出

```
2
4 5
```

## 样例 #2

### 输入

```
4 3
```

### 输出

```
3
2 3 1
```

## 样例 #3

### 输入

```
5 1
```

### 输出

```
-1
```

# 题解

## 作者：wuzijie (赞：6)

## 题面解释：
你需要选出若干个不大于 $m$ 的正整数，使得他们的 $\operatorname{lowbit}$ 之和为 $n$。

## 思路分析：
为了做出这道题目，我们必须先知道 $\operatorname{lowbit}$ 的含义。

对于 $\operatorname{lowbit}(x)$，就是指 $x$ 在二进制表示下权值最小的 $1$ 所在的位置。

例如：
	
-  $10$ 的二进制是 $1010$ ，在从右往左数第 $2$ 位的 $1$ 权值最小，为 $2$ ，所以 $\operatorname{lowbit}(10)=2$ 。

对于 $x$ 的 $\operatorname{lowbit}$ ，可以通过
```cpp
lowbit(x)=x&(-x)
```

来求，这里是利用了计算机内部补码的存储,详见[这里](https://owk.zlext.com/ds/fenwick/)。

那么这道题就是一道简单的贪心，按 $\operatorname{lowbit}$ 从大到小排序，能取则取。

如果把能取的里面最大的几个全部拿完了，还不够，再换一种取法只会更小，那么一定不能使得他们的 $\operatorname{lowbit}$ 之和为 $n$。

所以我们从大往小取的贪心一定是正确的。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int lowbit(int x){
	return x&(-x);
}
bool cmp(int x,int y){
	return lowbit(x)>lowbit(y);
}
int n,m,a[N];
int cnt,ans[N];
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		a[i]=i;
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;i++)
		if(n>=lowbit(a[i]))
			ans[++cnt]=a[i],n-=lowbit(a[i]);
	if(n>0){
		printf("-1");
		return 0;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%d ",ans[i]);
	return 0;
}
```

谢谢！

---

## 作者：xiaoxiongbinggan (赞：4)

# CF437B The Child and Set 题解

### 题目分析

给出两个数 $n$ 和 $m$，要求求出不大于 $m$ 的若干个数的 lowbit 值的和等于 $n$。

lowbit 是什么呢？

lowbit 指这个数二进制形态下最后一个 $1$ 所出现的位置。

如：$7$ 的二进制数为 $111$,则 $7$ 的 lowbit 值为 $1$。

$12$ 的二进制数为 $1100$,则 $12$ 的lowbit 值为 $3$。

这道题应该用贪心做，那贪心算法是怎么实现的呢？

### 贪心算法实现步骤：
1：将子序列排序。

2：根据题目要求选择贪心策略，如求最值，求最佳方案。

3：根据选取的策略，逐步求取最优解。

### 结合本题：

要求求出和为 $n$ ，~~求取和为定值的题目一般都是用贪心~~，从小到大选取肯定越到后遇到的问题越多，那我们就从后往前选。

先将 $1$ 到 $m$ 的 lowbit 值求出来，再从大到小排好序，若此时的和加上当前考虑位置的数之后还小于 $n$，则选取此时考虑的数，用存储选取答案的数组存一下；否则不选，继续考虑下一个数，若到最后选取的和小于 $n$，则不能达成题目要求，直接输出 $-1$,否则能达成题目要求，输出答案。

代码如下，看不懂有注释：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define lowbit(x) (x&(-x))//求出每一个数的lowbit值
int n,m;
bool cmp(int a,int b){
	return lowbit(a)>lowbit(b);//将这些数按照lowbit值从大到小排序
}
int ans[10000000];
int cnt=0;
int a[1000000];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		a[i]=i;
	}
	int sum=n;//求和（用sum代表还差多少数到n，意思一样。
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=m;i++){
		if(sum>=lowbit(a[i])){//若此时的和小于 $n$ ，则选取此数
			ans[++cnt]=a[i];//存储答案
			sum-=lowbit(a[i]);//和加上此时考虑的数
		}
	}
	if(sum>0){//若选取的数的lowbit值的和小于n，的无法达成题目要求
		cout<<-1;
		return 0;
	}else{
		cout<<cnt<<endl;//输出选取的数的个数
		for(int i=1;i<=cnt;i++){
			cout<<ans[i]<<" ";//输出选取的数
		}
	}
	return 0;
}
```
完结撒花

---

## 作者：__Kyw666__ (赞：2)

## 题意解释
有两个整数 $n$ 和 $m$，需要选取若干个不大于 $m$ 的数，使得这若干个数的 $\operatorname{lowbit}$ 值的和等于 $n$。

## 函数解释
下面解释一下 $\operatorname{lowbit}$ 是什么意思。  
$\operatorname{lowbit}(x)$ 指 $x$ 的二进制表达式中最低位的 $1$ 所对应的值。  
* 举例解释：  
  $\operatorname{lowbit}(4)$  
  $4$ 的二进制为 $100_{(2)}$，  
  最低位的 $1$ 在第三位上，所以 $\operatorname{lowbit}(4)=3$。  
  $\operatorname{lowbit}(7)$  
  $7$ 的二进制为 $111_{(2)}$，  
  最低位的 $1$ 在第一位上，所以 $\operatorname{lowbit}(7)=1$。
  
* 函数代码：
```
int lowbit(int x)
{
	return x&(-x);
}
```
这种比较常用，运用了负整数的补码特性。

## 思路分析
把从 $1$ 到 $m$ 这 $m$ 个数的 $\operatorname{lowbit}$ 值都记下来，接下来在这些数中寻找 $\operatorname{lowbit}$ 值和为 $n$ 的若干个数，最后输出就结束了。  
* 多组解输出任意一组即可。
* 无解则输出 $-1$。

## 代码实现

```
#include<bits/stdc++.h>
using namespace std;

int n,m;
struct node{
	int lowbit;
	int num;
}f[100005];

int lowbit(int x)
{
	return x&(-x);
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		f[i].num=i;
		f[i].lowbit=lowbit(i);
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<m;j++)
			if(f[j].lowbit<f[j+1].lowbit)
				swap(f[j],f[j+1]);
	int s=0;
	for(int i=1;i<=m;i++)
	{
		s=f[i].lowbit;
		for(int j=i+1;j<=m;j++)
		{
			s+=f[j].lowbit;
			if(s==n)
			{
				cout<<j-i+1<<endl;
				cout<<f[i].num<<" ";
				for(int k=i+1;k<=j;k++)
					cout<<f[k].num<<" ";
				return 0;
			}
		}
	}
	cout<<-1;
	return 0;
 } 

```
具体解释在前面，代码中我没加注释。  

结束！

---

## 作者：lrx___ (赞：2)

**题意简述**

给定 $N,M$，请选出若干个不重复的整数，使这些整数的 $lowbit$ 值的和等于 $N$，且这些整数都不超过 $M$。如果有解，第一行输出整数的个数，第二行输出这些整数，用空格隔开。如果无解，输出 `-1`。

一个数 $x$ 的 $lowbit$ 值就等于 $x \space and-x$，其中 $and$ 表示按位与运算。

**思路**

$M$ 只有 $10^5$，所以我们可以把 $M$ 范围内的所有整数都求出它的 $lowbit$ 值来，让 $f_i$ 表示 $i$ 的 $lowbit$ 值，从 $M$ 到 $1$ 循环一遍，如果 $N$ 大于等于 $f_i$，就用 $N$ 减去 $f_i$ 并标记。最后如果 $N$ 为 $0$，就说明有解，否则就是无解。

**代码**

```pascal
var
  f:array[1..100005]of longint;
  v:array[1..100005]of boolean;
  n,m,i,s:longint;
//  f存储每个数的lowbit值，v表示这个数是否被标记，s是选出数的个数 
begin
  s:=0;
  read(n,m);
  for i:=1 to m do begin
    f[i]:=i and -i;
//    求出x的lowbit值的方法是(x and -x) 
  end;
  for i:=m downto 1 do begin
    if(n>=f[i])then begin
      n:=n-f[i];v[i]:=true;s:=s+1;
//      如果n大于等于f[i]，就选上这个数，标记出来并用n减去f[i] 
    end;
  end;
  if(n>0)then begin
    writeln(-1);
  end else begin
    writeln(s);
    for i:=1 to m do begin
      if(v[i])then begin
        write(i,' ');
      end;
    end;
  end;
end.
```

---

## 作者：syksykCCC (赞：2)

## 难度估计 

![](https://img.shields.io/badge/%E6%99%AE%E5%8F%8A+/%E6%8F%90%E9%AB%98-5eb95e.svg?longCache=true&style=flat)

## 题意

从 $1\sim limit$ 中选取若干个**互不相同**的数字，使得这些数字的 $lowbit$ 和等于 $sum$，$1\leq sum, limit\leq 10^5$ 

## 题解

因为至多选取 $10^5$ 个数字，很自然想到贪心。

贪心是基于这样一个事实：

> 任何一个数字都可以表示为 $\sum 2^x$( $x$ 不重复) 的形式

这是为什么呢，相信大家都知道每个数都有二进制的表示，例如 $1011_{(2)}$ 就显然等于 $1\times 2^0 + 1\times 2^1 + 0\times 2^2 + 1\times 2^3$，化简一下，也就是 $2^0 + 2^1 + 2^3$。

换言之，因为二进制的每一位只可能是 $0 / 1$，所以必然可以表示为如上形式。

然后 $lowbit$ 相信大家也很清楚，表示一个数字的二进制的最后一位 $1$ 的大小，例如 $lowbit(10\color{red}1\color{black}0_{(2)})= 10_{(2)}$，即 $lowbit(6)=2$，可以用 `lowbit(x) = x AND -x` 来计算，显然 $lowbit$ 必然是一个$2^{\cdots}$（不理解的同学先学习树状数组）。

我们用一个pair来记录原数和它的 $lowbit$ 值：
```cpp
for(int i = 1; i <= lim; i++)
{
	S.push_back(make_pair(i & -i, i)); // lowbit and number
}
```

然后基于上面那个结论，将pair根据 $lowbit$ 从大到小排序，依次贪心，这里的贪心结论是：**如果 $n$ 大于等于当前的 $lowbit$，必然可以选择当前的 $lowbit$ ，然后将 $n$ 减去它，继续贪心，如果最终 $n\neq 0$，则无解**。

为什么呢？

$lowbit$ 值显然是有重复的，假设当前在考虑$lowbit_i$，如果一个数可以表示为$\sum_{j\in[i+1,limit]}lowbit_j$ 的形式，那么这个数加 $lowbit_i$ 必然也可以被表示。

所以，如果 $n(n\geq lowbit_i)$ 可以被表示，则 $n-lowbit_i$ 也可以被表示。
```cpp
sort(S.rbegin(), S.rend()); // sort(big -> small)                     
for(unsigned i = 0; i < S.size(); i++)          
{                                               
	if(n >= S[i].first) // greedy                        
	{                                           
		n -= S[i].first;                        
		ans.push_back(S[i].second);              
	}                                           
}                                               
// output
if(n)                                           
{                                               
	cout << -1 << endl;                         
}                                               
else                                            
{                                               
	cout << ans.size() << endl;                 
	for(unsigned i = 0; i < ans.size(); i++)    
	{                                           
		cout << ans[i] << ' ';                  
	}                                           
}                                               
```

于是这题就可以愉快的通过了，完整代码（代码中的 $n$ 表示原题的 $sum $）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, lim;
vector<pair<int, int> > S;
vector<int> ans;
int main()
{
	cin >> n >> lim;
	for(int i = 1; i <= lim; i++)
	{
		S.push_back(make_pair(i & -i, i));
	}
	sort(S.rbegin(), S.rend());
	for(unsigned i = 0; i < S.size(); i++)
	{
		if(n >= S[i].first)
		{
			n -= S[i].first;
			ans.push_back(S[i].second);
		}
	}
	if(n)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << ans.size() << endl;
		for(unsigned i = 0; i < ans.size(); i++)
		{
			cout << ans[i] << ' ';
		}
	}
	return 0;
}

```

一句话总结：**能减就减，有余无解！**

---

## 作者：NightTide (赞：1)

## CF437B The Child and Set 题解

这题目就一个问题。

啥是 $\operatorname {lowbit}$？

$\operatorname {lowbit}(x)$ 是指 $x$ 的二进制表示中最低位的 $1$ 所表示的值。

例如 $(14)_{10} = (1110)_2$，其中最低位的 $1$ 在第二位，表示 $(2)_{10}$，即 $\operatorname {lowbit}(14)  = 2$。

接下来考虑如何选取。

一个贪心策略是按照 $\operatorname {lowbit}$ 从大到小选取，如果当前的数的 $\operatorname {lowbit}$ 小于剩余的 $n$，那么就选到这个数，并让 $n$ 减去当前数的 $\operatorname {lowbit}$。

显而易见这样取出来的总和最大。

如果取到最后还不能取完，那么就输出 `-1`。

有点类似于倍增。

至于怎么求 $\operatorname {lowbit}$，先人给我们找好了方法：

$$\operatorname {lowbit}(x) = x\; \& \;(-x)$$

这是利用计算机补码性质完成的，其中的符号 $\&$ 代表按位与。

最终代码如下：

```cpp
#include<bits/stdc++.h>
#define MAXM 100010
using namespace std;
struct node{
    int num, bit;
};
bool operator < (node a, node b){ return a.bit < b.bit; }
bool operator > (node a, node b){ return a.bit > b.bit; }
node a[MAXM];
int n, m;
vector<int> ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= m; i++) a[i] = (node){i, i & (-i)};
    sort(a + 1, a + m + 1, greater<node>());
    for(int i = 1; i <= m && n >= 0; i++){
        if(n >= a[i].bit){
            n -= a[i].bit;
            ans.push_back(a[i].num);
        }
    }
    if(n != 0) printf("-1\n");
    else{
        printf("%ld\n",ans.size());
        for(int i = 0; i < ans.size(); i++) printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Eterna (赞：1)

[题目](https://www.luogu.com.cn/problem/CF437B)。

直接看题，大多数不会树状数组的人都卡在了 lowbit 上，我来解释下。

lowbit 表示一个数的二进制表示中最低位的 $1$ 的位置。

lowbit 函数的原理可以通过以下步骤理解：

假设x最低位的 $1$ 在第 $k$ 位上。

按位取反 $n$ 会将 $n$ 的二进制的第k位取反为 $0$， $0$ 到 $k-1$ 位全部取反为 $1$。

对取反结果加 $1$ 操作，由于进位，使得 $0$ 到 $k-1$ 位全部为 $0$，第 $k$ 位为 $1$。

与原数 $n$ 进行按位与操作，结果就只剩最低位的 $1$ 以及它后面的 $0$ 构成的数了。

$k$ 以上的位数不影响答案。

在 c++ 中，计算 lowbit 有如下代码：

```cpp
int lowbit(int x)
{
    return x&(-x);
}
```

理解了这个，就简单多了。

其实就是一个很平常的贪心题，尽量取最大值就行。

排序后，算法的时间复杂度大概就是 $O(m)$，

可以通过。

### 代码
```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&(-x)//好像比直接定义函数快一点
#define N 100005 
using namespace std;
int n,m;
int tt,a[N];
struct node
{
	int l;
	int id;
}t[N]; 
bool cmp(node a,node b){return a.l>b.l;}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)t[i].id=i,t[i].l=lowbit(i);//预处理lowbit
	sort(t+1,t+m+1,cmp);//排序
	for(int i=1;i<=m;i++)if(n>=t[i].l)n-=t[i].l,a[++tt]=t[i].id;//贪心
	if(n!=0)tt=-1;//标记无解
	cout<<tt<<endl; 
	for(int i=1;i<=tt;i++)cout<<a[i]<<" ";//输出结果
	return 0;
} 
```

注：部分内容借助百度。

---

## 作者：残阳如血 (赞：0)

### $\textbf{Description}$

给定 $n$ 和 $m$，求构造一个 01 序列 $\{a_m\}$，使得
$$
\sum\limits_{i=1}^{m}\text{lowbit}(i)=n
$$
输出序列 $a$ 中值为 $1$ 的下标，或报告无解。

### $\textbf{Solution}$

从大到小考虑 $i\in[1,m]$，使用贪心策略，能取就取，最后如果 $n=0$ 那么有解，反之无解。

> #### 感性证明贪心策略
>
> 总体上 $\text{lowbit}(i)$ 与 $i$ 的大小成正相关性，所以可以先取大的使得 $n$ 变小，而越小的 $i$ 可以用于微调。

### $\textbf{Code}$

```cpp
#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))

int n, m;
std::vector<int> ans;

int main() {
  std::cin >> n >> m;
  for (int i = m; i; --i)
    if (n >= lowbit(i)) { // 能取就取
      n -= lowbit(i);
      ans.push_back(i);
    }
  std::sort(ans.begin(), ans.end()); // 要求顺序输出
  if (n) return puts("-1"), 0; // n ≠ 0 的时候无解
  std::cout << ans.size() << std::endl;
  for (auto x : ans) std::cout << x << ' ';
  std::cout << std::endl;
  return 0;
}
```

此外，该代码还可以优化到 $O(m)$，`ans` 是从大到小加入的，最后倒序输出就可以了。

---

## 作者：liangkairui (赞：0)

# [The Child and Set](https://www.luogu.com.cn/problem/solution/CF437B) 题解
## 题意简述
选若干个小于等于 $m$ 的数，让它们 $\operatorname{lowbit}$ 值之和刚好等于 $n$。
## 前置知识
我们需要知晓 $\operatorname{lowbit}$ 是什么，以及怎么求得。
含义：$\operatorname{lowbit}(x)$ 是 $x$ 在二进制表达式中最后一个 $1$ 所表示的值。

根据~~人类智慧~~手推可知 $\operatorname{lowbit}(x)$ 值由 $x$ 和它的补码取与而得。

代码如下：
```cpp
int lowbit(int x){
	return x&(-x);
}
```
## 思路解析
将 $1$ 到 $m$ 中的每个数的 $\operatorname{lowbit}$ 值进行排序，然后从最大的 $\operatorname{lowbit}$ 值开始加，能加则加。

如果最终加出来的数不等于 $n$，则无解。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;
struct node{
	int low;
	int i;
}a[N];
inline int read(int &x){
	x=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+int(c-'0');c=getchar();}
	return x*f;
}
int lowbit(int x){
	return x&(-x);
}
int cmp(node x,node y){
	return x.low>y.low;
}
int da[N],cnt=0;
int main()
{
	int n,m;
	read(n);
	read(m);
	for(int i=1;i<=m;i++){
		a[i].low=lowbit(i);
		a[i].i=i;
	}
	sort(a+1,a+m+1,cmp);
	int sum=0,ans=0;
	for(int i=1;i<=m;i++){
		if(a[i].low+sum<=n){
			sum+=a[i].low;
			da[++cnt]=a[i].i;
			ans++;
		}
	}
	if(sum<n){
		cout<<-1;
		return 0;
	}
	cout<<ans<<endl;
	for(int i=1;i<=cnt;i++){
		cout<<da[i]<<" ";
	}
	return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路
首先预处理 $1\le x \le m$，每个 $x$ 的 $\operatorname{lowbit(x)}$。然后按照从大到小排序，根据贪心策略从大到小取，最后判一下 $-1$ 的情况就行了。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optmize(3)
using namespace std;
int n,m,b[100001],t;
int lowbit(int x)
{
	return x&(-x);
}
struct st{
	int x,y;
}a[100001];
bool cmp(st a,st b)
{
	return a.y>b.y;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		a[i].x=i;
		a[i].y=lowbit(i);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=m;i++)
	{
		if(a[i].y<=n)
		{
			b[++t]=a[i].x;
			n-=a[i].y;
			if(n<=0) break;
		}
	}
	if(n>0) cout<<"-1\n";
	else{
		cout<<t<<"\n";
		for(int i=1;i<=t;i++) cout<<b[i]<<" ";
	}
	return 0;
}
```

---

## 作者：zhangzirui66 (赞：0)

一道贪心题。

先说结论，把 $m$ 以内的数列出来，算出 [$\operatorname{lowbit}$](https://blog.csdn.net/lesileqin/article/details/102418143) 值，从大到小排序（后文称该数组为 $f$ 数组），遍历每一个 $f_i$，若 $n\ge f_i$，则 $n$ 减去 $f_i$，$f_i$ 即为答案里的一个数，若到最后 $n>0$，则无解。

贪心需要证明，证明如下：

> 对于每一个数，它可以用 $2^x\text{（x不重复）}$ 的和来表示

这个又怎么证明呢？

显然，每个数都可以用二进制表示，如 $10$ 可用 $1010_{(2)}$ 表示，也等于 $0\times2^0+1\times2^1+0\times2^2+1\times2^3$，化简为 $2^1+2^3$，证毕。

而 $\operatorname{lowbit}$ 值一定是 $2$ 的整次幂，是因为它是二进制中某一位的值，所以若干个 $\operatorname{lowbit}$ 值，一定可以组成 $n$。

---
主要代码：
```cpp
int lowbit(int x){
    return (x & (-x));
}
```

```cpp
bool cmp(int x, int y){
    return lowbit(x) > lowbit(y);
}
for(int i = 1; i <= m; i ++) a[i] = i;
sort(a + 1, a + m + 1, cmp);
```

---

## 作者：louliu (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF437B)

### 分析

首先，一看就是一道贪心题，取到刚好合适的数，区间最优即可。但又发现了难点，多了一个 lowbit！实际上，lowbit 的含义如下：

```cpp
return x&(-x);//可以搜索lowbit，网上讲解更详细
```

所以我们只要开一个结构体，记录数所在的位置（因为其值会发生改变），然后再排一个序，从大到小按顺序取数即可（贪心策略）。

#### 注意，lowbit 过后的值一定要小于当下值。

否则就会出现负数情况，这是完全不可能的！

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,ans,k;
struct node{
	int a,b;
}c[100005];//结构体记录位置与值 
int d[100005];
bool cmp(node a,node b){
	return a.a<b.a;//排序 
}
int lb(int x){
	return x&(-x);//lowbit
}
int main(){
	cin>>a>>b;
	for(int i=1;i<=b;i++){
		c[i].a=lb(i);
		c[i].b=i;//lowbit处理 
	}
	sort(c+1,c+1+b,cmp);
	for(int i=b;i>=1;i--){
		if(c[i].a<=a){//判断是否小于当下值 
			a-=c[i].a;
			ans++;
			d[ans]=c[i].b;
		}
		if(a==0){
			break;//如果取完结果为零，提前跳出 
		}
	}
	if(a>0){
		cout<<-1;//没取够就输出-1 
		return 0;
	}
	cout<<ans<<"\n";
	for(int i=1;i<=ans;i++){
		cout<<d[i]<<" ";
	}
	return 0;
}
```

#### 一道模版贪心题！

---

## 作者：xxr___ (赞：0)

**思路**

从 $M$ 到 $1$ 循环一遍，如果这个数的 $lowbit$ 值不大于 $N$，就让 $N$ 减去这个数的 $lowbit$ 值。最后输出减去的所有数即可。

**代码**

```java
import java.util.Scanner;

public class Main{
  public static void main(String[]args){
    Scanner io=new Scanner(System.in);
    
    boolean[] v=new boolean[100005];
//    v[i]代表i是否被选过 
    int n,m,i,cnt=0;
    n=io.nextInt();m=io.nextInt();
    for(i=m;i>=1;i--){
      if(n>=(i&-i)){
        n-=i&-i;cnt++;v[i]=true;
//        标记i被选了 
      }
    }
    if(n==0){
//    	n=0代表有解 
      System.out.printf("%d\n",cnt);
      for(i=1;i<=m;i++){
        if(v[i]){
          System.out.printf("%d ",i);
        }
      }
    }else{
      System.out.print("-1\n");
    }
  }
}
```

---

## 作者：爬行者小郑 (赞：0)

# 我认为这道题并不是很难
难度大概在黄到绿左右

## 什么是lowbit运算？
lowbit是指一个数，将其转换为二进制之后，从最低位开始向高位，第一个不是0的位；
~~这好像有点抽象~~

举个例子：
 
		12的二进制是1100
        从最后一位开始，第一个一是第三位上面的1
lowbit运算可以通过x&(-x)来实现

## 为咩？（为什么？）

还是以1100为例

(1100)补=0100

所有0的位都取反，再加一就是要求的了

------------------------------

所以我们可以知道，一个数的lowbit一定是2的k次方的形式

并且在从1到m的区间内，不会存在中间“断开”的情况

我们知道，每个正整数都可以表示成几个互不相同的2的k次方的和


---------------------------------

## 所以，我们可以放心大胆地开始贪心了！根本不需要动归什么的

我们先按照lowbit值排序，再用n来减，如果n不是零，说明不可以，返回-1，反之输出答案。

下面是代码
```cpp
#include <iostream>//基本输入输出流 
#include <algorithm>//因为要用到sort 
using namespace std;
int n,m;
int tot,ans[100005];
struct Node
{
	int low;
	int id;
}t[100005];//由于编号要和lowbit值一起修改，所以用结构体来实现 
int lowbit(int x)//求lowbit函数 
{
	return x&(-x);//实现lowbit
}
bool cmp(Node a,Node b)//结构体排序：按照lowbit从大到小 
{
	return a.low>b.low;//将<重载（重新定义） 
}
int main()
{
	cin>>n>>m;//输入n，m 
	for(int i=1;i<=m;i++)
	{
		t[i].id=i;//记录编号 
		t[i].low=lowbit(i);//记录lowbit值 
	}
	sort(t+1,t+m+1,cmp);//按照从大到小排序 
	for(int i=1;i<=m;i++)
	{
		if(n>=t[i].low)//如果可以减 
			n-=t[i].low,ans[++tot]=t[i].id;//那么就减，并且记录编号
			 
	}
	if(n)cout<<-1<<endl;//如果还有剩余，那么输出-1 
	else
	{
		cout<<tot<<endl;//先输出个数 
		for(int i=1;i<=tot;i++)
		{
			cout<<ans[i]<<" ";//依次输出答案 
		}
	}
	return 0;//好习惯 
} 
```
谢谢大家，本蒟蒻很少写题解，写得不好请见谅

---

