# [USACO11FEB] Cow Line S

## 题目描述

The N (1 <= N <= 20) cows conveniently numbered 1...N are playing yet another one of their crazy games with Farmer John. The cows will arrange themselves in a line and ask Farmer John what their line number is. In return, Farmer John can give them a line number and the cows must rearrange themselves into that line.

A line number is assigned by numbering all the permutations of the line in lexicographic order.

Consider this example:

Farmer John has 5 cows and gives them the line number of 3.

The permutations of the line in ascending lexicographic order: 1st: 1 2 3 4 5

2nd: 1 2 3 5 4

3rd: 1 2 4 3 5

Therefore, the cows will line themselves in the cow line 1 2 4 3 5.

The cows, in return, line themselves in the configuration '1 2 5 3 4' and ask Farmer John what their line number is.

Continuing with the list:

4th : 1 2 4 5 3

5th : 1 2 5 3 4

Farmer John can see the answer here is 5

Farmer John and the cows would like your help to play their game. They have K (1 <= K <= 10,000) queries that they need help with. Query i has two parts: C\_i will be the command, which is either 'P' or 'Q'.

If C\_i is 'P', then the second part of the query will be one integer A\_i (1 <= A\_i <= N!), which is a line number. This is Farmer John challenging the cows to line up in the correct cow line.

If C\_i is 'Q', then the second part of the query will be N distinct integers B\_ij (1 <= B\_ij <= N). This will denote a cow line. These are the cows challenging Farmer John to find their line number.



## 样例 #1

### 输入

```
5 2 
P 
3 
Q 
1 2 5 3 4 
```

### 输出

```
1 2 4 3 5 
5 
```

# 题解

## 作者：YoungNeal (赞：21)

上一下原链接 [YoungNeal](http://www.cnblogs.com/YoungNeal/p/8504123.html)

我们先来科普一下康托展开
## 定义：

$X=an*(n-1)!+an-1*(n-2)!+...+ai*(i-1)!+...+a2*1!+a1*0!$

$ai$为整数，并且 $0<=ai<i$ $(1<=i<=n)$

简单点说就是，判断这个数在其各个数字全排列中从小到大排第几位。

比如 $ 1 3 2 $，在1、2、3的全排列中排第2位。
## 康托展开有啥用呢？

维基： $n$ 位（0~n-1）全排列后，其康托展开唯一且最大约为 $n!$ ，因此可以由更小的空间来储存这些排列。由公式可将 $X$ 逆推出对应的全排列。

它可以应用于哈希表中空间压缩，

而且在搜索某些类型题时，将VIS数组量压缩。比如：八数码，魔板等题
康托展开求法：

比如 $2 1 4 3$ 这个数，求其展开：

从头判断，至尾结束,

① 比 $2$（第一位数）小的数有多少个->$1$个 就是 $1$ ，$1*3!$

② 比 $1$（第二位数）小的数有多少个->$0$个 $0*2!$

③ 比 $4$（第三位数）小的数有多少个->$3$个 就是 $1,2,3$ ，但是 $1,2$ 之前已经出现，所以是 $1*1!$

将所有乘积相加=7

比该数小的数有7个，所以该数排第8的位置。

$1234$  $1243$  $1324$  $1342$  $1423$  $1432$   
$2134$  $2143$  $2314$  $2341$  $2413$  $2431$  
$3124$  $3142$  $3214$  $3241$  $3412$  $3421$  
$4123$  $4132$  $4213$  $4231$  $4312$  $4321$  

放一下程序的实现
```
int contor(int x[]){
    int p=0;
    for(int i=1;i<=n;i++){
        int t=0;
        for(int j=i+1;j<=n;j++){
            if(x[i]>x[j]) t++;
        }
        p+=t*fac[n-i];
    }
    return p+1;
}
```
## 康托展开的逆：

康托展开是一个全排列到自然数的双射，可以作为哈希函数。

所以当然也可以求逆运算了。

逆运算的方法：

假设求 $4$ 位数中第 $19$ 个位置的数字。

① 19减去1  → 18

② 18 对 $3!$ 作除法 → 得3余0

③  0对 $2!$ 作除法 → 得0余0

④  0对 $1!$ 作除法 → 得0余0

据上面的可知：

我们第一位数（最左面的数），比第一位数小的数有3个，显然 第一位数为→ 4

比第二位数小的数字有0个，所以 第二位数为→1

比第三位数小的数字有0个，因为1已经用过，所以第三位数为→2

第四位数剩下 3

该数字为  $4 1 2 3$  (正解)

 

再上代码
```
void reverse_contor(int x){
    memset(vis,0,sizeof vis);
    x--;
    int j;
    for(int i=1;i<=n;i++){
        int t=x/fac[n-i];
        for(j=1;j<=n;j++){
            if(!vis[j]){
                if(!t) break;
                t--;
            }
        }
        printf("%d ",j);
        vis[j]=1;
        x%=fac[n-i];
    }
    puts("");
}
```

## 最后上一下本题的代码
```
#include<cstdio>
#include<cstring>
#include<iostream>
#define int long long
using namespace std;

int fac[25]={1};

int n,k,x;
int val[25];
bool vis[25];

void reverse_contor(int x){
	memset(vis,0,sizeof vis);
	x--;
	int j;
	for(int i=1;i<=n;i++){
		int t=x/fac[n-i];
		for(j=1;j<=n;j++){
			if(!vis[j]){
				if(!t) break;
				t--;
			}
		}
		printf("%d ",j);
		vis[j]=1;
		x%=fac[n-i];
	}
	puts("");
}

int contor(int x[]){
	int p=0;
	for(int i=1;i<=n;i++){
		int t=0;
		for(int j=i+1;j<=n;j++){
			if(x[i]>x[j]) t++;
		}
		p+=t*fac[n-i];
	}
	return p+1;
}

signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i;
	while(k--){
		char ch;cin>>ch;
		if(ch=='P') scanf("%lld",&x),reverse_contor(x);
		else{
			for(int i=1;i<=n;i++) scanf("%lld",&val[i]);
			printf("%lld\n",contor(val));
		}
	}
	return 0;
}
```

---

## 作者：Rainybunny (赞：6)

本题是一道**Cantor展开**的模板~~水~~题, 不过网上好像并没有对康拓展开的详细证明, 那么我就替各位dalao码一码证明吧!  
以下是我一个午自习的智慧结晶x.
# Cantor展开
先甩一下原定理:  
**给定一长度为$n$严格上升数列$a$, 令初始状态$a_0=a$, 对a进行全排列, 第k次生成的数列为$a_k$, 则有Cantor展开式:**  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$k=Hash(a_k)=\sum_{i=1}^n(n-i)!\sum_{j=i+1}^n(a_{k,i}>a_{k,j})$
## 证明
构造如下Hash操作:  
&nbsp;&nbsp;&nbsp;&nbsp;**1)按顺序取出$a_{k,i}$**  
&nbsp;&nbsp;&nbsp;&nbsp;**2)取所有$a_{k,j}<a_{k,i},i<j$与$a_{k,i}$交换位置, 并对$a_{k,i+1}$至$a_{k,n}$的元素进行全排**  
现只需证, **该操作(1)仅限于, (2)不重复, (3)不遗漏地生成所有于$a_k$之前生成的数列, 即$a_1,a_2,...,a_{k-1}$.** 不妨设$a_k=S$, 操作后$a_k'=T$. 

------------
 
### 下证性质(1)
不妨设取出$S_m$与后交换,  
$\because$对于$\forall i<m,S_i=T_i$  
又$\because S_m>T_m$  
$\therefore T$一定全排生成于$S$之前, 已证.  

------------
  
### 下证性质(2)
(一) 若取$S_m$于后交换, 设多种不同交换结果$T_1,T_2,...$  
显然，$T_{1,m}\neq T_{2,m}\neq ...$.  
又在$\forall T_i$中，$T_{m+1}$至$T_n$又全排生成, 必不全等, 已证.  
  
(二) 若取$S_n,S_m$分别交换, 不妨设$n<m$,  
则取$S_m$所生成的结果$T,T_n=S_n$,  
又取$S_n$所生成的结果$T',T'\neq S_n$.  
$\therefore T\neq T'$, 已证.  
  
综上,性质(2)已证.  

------------

### 下证性质(3)
不妨任取全排数列$a_i, i\in[0,k-1]$  
$\because S$生成于$a_i$之后  
$\therefore$必先出现最小的$m$, s.t.(such that, 使得)$S_m>a_{i,m}$, 且对于$j<m,S_j=a_{i,j}$.  
$\because a_i$无重复元素  
$\therefore a_{i,m}\in\{S_n|n>m\}$  
又$\because S_m>a_{i,m}$  
$\therefore$当取$S_m$交换时, 必会s.t.一组结果$T$, $T_m=a_{i,m}$  
此时, $a_i$必由$T_{m+1}$至$T_n$的全排列生成, 已证.  

------------

故, 该操作性质已证明, 其生成的数列总数就是$k$.  
不妨设取出$S_i$与后交换, 其生成的数列总数显然为:  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$Total_i=(n-i)!\sum_{j=i+1}^n(S_i>S_j)$  

那么所有的数列总数即为:  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$k=\sum_{i=1}^nTotal_i=\sum_{i=1}^n(n-i)!\sum_{j=i+1}^n(S_i>S_j)$  

则对于$\forall a_k$, 该操作生成的数列总数为:  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$k=\sum_{i=1}^n(n-i)!\sum_{j=i+1}^n(a_{k,i}>a_{k,j})$  

故, 原命题成立, 证毕!  


------------
是不是非常简单呢? ~~滑稽~~  
毕竟是板题，直接上代码吧.  

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

namespace Optimize { // 优化模板 
	#define Eps 1e-8
	#define Inf 0x3f3f3f3f
	#define Int register int
	#define LL long long int
	#define Type template<typename _T>
	#define FileClose() fclose ( stdin ), fclose ( stdout )
	#define FileOpen( fname ) freopen ( fname".in", "r", stdin ), freopen ( fname".out", "w", stdout )
	Type inline _T Max ( const _T a, const _T b ) { return a > b ? a : b; }
	Type inline _T Min ( const _T a, const _T b ) { return a < b ? a : b; }
	Type inline _T Abs ( const _T x ) { return x < 0 ? -x : x; }
	Type inline _T rint () {
		_T x = 0; int f = 1; char s = getchar ();
		while ( s < '0' || '9' < s ) f = s == '-' ? -1 : 1, s = getchar ();
		while ( '0' <= s && s <= '9' ) x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar ();
		return x * f;
	}
	Type inline void wint ( _T x ) {
		if ( x < 0 ) putchar ( '-' ), x = ( ~ x ) + 1;
		if ( 9 < x ) wint ( x / 10 );
		putchar ( x % 10 + '0' );
	}
}

using namespace std;
using namespace Optimize;

int n, q, a[25] = {};
LL FAC[25] = { 1 }; // 阶乘答案 

inline LL Cantor ( const int* Seq ) { // Cantor展开求k 
	LL ret = 0;
	for ( Int i = 1; i <= n; ++ i ) {
		int Total = 0;
		for ( Int j = i + 1; j <= n; ++ j ) {
			Total += Seq[i] > Seq[j];
		}
		ret += Total * FAC[n - i];
	}
	return ret;
}

inline vector<int> ReCantor ( LL k ) { // 逆康拓展开求数列 
	vector<int> v, ret;
	for ( Int i = 1; i <= n; ++ i ) {
		v.push_back ( i );
	}
	for ( Int i = n; i; -- i ) {
		LL r = k % FAC[i - 1], t = k / FAC[i - 1];
		k = r;
		sort ( v.begin (), v.end () );
		ret.push_back ( v[t] );
		v.erase ( v.begin () + t );
	}
	return ret;
}

inline void Init () { // 阶乘预处理 
	for ( Int i = 1; i <= 20; ++ i ) {
		FAC[i] = FAC[i - 1] * i;
	}
}

inline void Work () {
	#define rint rint<LL>() // 声明读入LL, 注意输入的num可能非常大, 必须用LL 
	#define veciter vector<int> :: iterator // 迭代器 
	Init ();
	n = rint, q = rint;
	while ( q -- ) {
		char Cmd = getchar ();
		if ( Cmd == 'P' ) {
			LL num = rint;
			vector<int> Ans = ReCantor ( num - 1 );
			for ( veciter it = Ans.begin (); it != Ans.end (); ++ it ) {
				wint ( *it ), putchar ( ' ' );
			}
			putchar ( '\n' );
		} else if ( Cmd == 'Q' ) {
			for ( Int i = 1; i <= n; ++ i ) {
				a[i] = rint;
			}
			LL Ans = Cantor ( a );
			wint ( Ans + 1 ), putchar ( '\n' );
		}
		else ++ q; // 读到异常字符, 不计入总数 
	}
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：Boxxxxxx (赞：2)

[点击博客，救救访问量](https://blog.csdn.net/qq_43804974/article/details/103864337)
单纯讲讲怎么用怎么算，说些人话。

预备概念：
排列：对于一个数字n的排列就是含有[1,n]所有数字的序列。也就是n取3，那么123,132,213就叫做n的排列，但是112,12,13等等这种就不是排列。

什么是康托展开呢？就是把一个n的全排列表示出来并且按照字典序排出来。n取三的全排列有6种，那么就对着6种按字典序小的顺序去排比如123的序号就是1,132的序号就是2.

首先我们来讲怎么根据给出的一个排列去求出他所代表的序号是多少，比如序列
2 1 4 3的序号。他的求法是这样的，看第一个数字是2，我们去需要知道**目前还没用过的数字中2所在的位置-1**的这个数字作为temp1好了， 目前没使用过的数字是1234（从小到大），2是第二大的数字，**在减去一**，减一后就是temp1 = 1；然后我们需要另一个数字temp2，这个数字是什么呢就是n减去当前在**序列中**这个**数字的位置**，就是temp2 = 4 - 1 = 3，在对temp2求阶乘也就是temp2 = 3! = 6;把temp1 ， temp2乘起来，在用这个乘完的数字**加上**后面位数的temp1*temp2
（过程算出来的数字就是这样的）
2：temp1 = 1， temp2 = 3！ = 6，temp1 * temp2 = 6；
1：temp1 = 0(现在没使用过的数字是1,3,4)，
      temp2 = 2！ = 2，temp1 * temp2 = 0；
4  :temp1 = 1,(1,2都使用过，现在剩下3,4），    
    temp2 = 1！ = 1，temp1*temp2 = 1；
3: temp = 0(只剩下3),temp2 = 0! = 1;temp1*temp2 = 0;

那么对于2143这个序列的序号就是6+0+1+0 = 7，但是在最后的最后还要在加上1，让他变成7+1 = 8这才是正确答案，因为他的序号原本是从0开始算的，你算1234算出来就是0，我们让他从1开始算；

关于代码实现方面方面用树状数组去维护前缀和就可以知道某个数字到底现在排在第几位（没用过的时候就是1，用完就把他减成0），其实就是一个单点修改区间查询的问题。

那么现在我们再来问一个问题， 知道一个序号和n，我们怎么求他所代表的序列是哪一种序列？我们就假设n是4，序号是8，用刚才的例子.用t表示8
   是这么求的先把序号-1，（我们上面是在最后加1的记得吗）。  t = 8 - 1 = 7；
   有n个数，我们从第一个数开始算起，用i表示现在在算第几个数,
    用t去除以（n - i）的阶乘得到一个数字，这个数字是什么？这个数字表示的是**在未使用的数字里面**排在第几个，但是我们还需要再加上一（记得我们上面算序号是-1的，这里就是反过来求也就是+1）,而现在这个排名所代表的数字就是当前位置的数字，多看两遍，再看不懂我推给你看;
    
    
   i = 1
   
   int node = t / (4-i)! = 7 / 3 ! = 1;node + 1 = 2;
   
   算出node = 2就是要未使用的数字里面排第2的就是（1234里面排第二的就是2）,那么第1个数字就是2，（现在未使用的数字就是134）,**算完后t取t除（4-i）!的模数，即t变成 t = t % (4 - i)! =1；**
   
   i = 2
   
   int node = t / (4 - i)! = 1 / 2 ! = 0, node + 1 = 1;
   要求未使用的数字里面排第一的（现在未使用的数字是134,排第一个的就是1）， 在更新t，t = t % (4 - i)! = 1, 现在未使用的数字是（3,4）;
   
   i = 3
   
   int node =  t / (4 - i)! = 1 / 1! = 1,node + 1 = 2;
   
    要求未使用的数字里面排第二的（现在未使用的数字是34,排第二个的就是4），
    
    更新t ,t = t % (4 - i)! = 0;(现在未使用的数字是3)
    
    i = 4
    int node =  t / (4 - i)! = 0 / 0! = 1,node + 1 = 1;
    取未使用的数字里面排第一位，就是3.算法结束
这个就是求的过程，希望各位看懂了康托展开和逆展开是怎么算出来的。在实现逆展开方面我是选择树状数组+二分去找出现在未使用的数字的第k大，当然线段树也可以，复杂度甚至更低（树状数组是两个log，线段树一个log）。
我没怎么讲具体树状数组怎么实现因为这篇主要是来用说一说康托展开的。如果对于我代码里面树状数组部分有何不懂可以留言。
   ```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
#define RE register
using namespace std;
const long long max_ = 1530000 + 7;
const int mod = 998244353;
const int inf = 1e9;
const long long INF = 1e18;
int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch<'0' || ch>'9') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0'&&ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * f;
}
int n,value[max_];

int c[100];
int low_bit(int x) {
	return (x&(-x));
}

void change(int x, int value) {
	while (x <= n) {
		c[x] += value;
		c[x] %= mod;
		x = x + low_bit(x);
	}
}

int sum_(int x) {
	//算1到x的总和
	int ans = 0;
	while (x != 0) {
		ans += c[x];
		ans %= mod;
		x = x - low_bit(x);
	}
	return ans%mod;
}
int erfen(int L, int R, int aim) {
	if (L == R)return L;
	int mid = L + (R - L) / 2;
	if (sum_(mid) >= aim) {
		return erfen(L, mid, aim);
	}
	else
	return erfen(mid + 1, R, aim);
}
signed main() {
	int T;
	n = read(), T = read();
	value[0] = 1;
	for (int i = 1; i <= 20; i++) {
		value[i] = value[i - 1]  * i;
	}
	while (T--){
		char ch;
		cin >> ch;
		if (ch == 'P') {
			//康托逆展开
			memset(c, 0, sizeof(c));
			for (int i = 1; i <= n; i++)
				change(i, 1);
			int temp = read(); temp--;
			for (int i = 1,num = n - 1; i <= n;num--, i++) {
				int aim = temp / value[num] + 1; temp %= value[num];
				int t = erfen(1, n, aim);
				cout << t << " ";
				change(t, -1);
			}
			cout << "\n";
		}
		else {//康托展开
			memset(c, 0, sizeof(c));
			for(int i =1; i <= n ; i++)
				change(i, 1);
			int ans = 1;//要从1开始
			for (int i = 1, jiecheng = n - 1; i <= n; jiecheng--, i++) {
				int temp = read();
				ans += value[jiecheng] * sum_(temp - 1);
				change(temp, -1);
			}
			cout << ans << "\n";
		}
	}
	return 0;
}
```

   
   


---

## 作者：Mychael (赞：2)

没有题解，写一波


这题难道不是数论么？为什么会有动归的标签。。。

进入正题：


**康托展开&康托逆展开**


给定一个数列，求出其在全排列中的位置，这就是康托展开要解决的问题

这是度娘说的：

<http://baike.baidu.com/link?url=InqGcS2WgtO1yVeqhxtn7KaCswerXIRvfvZ4bff3OpEVp-Rya5BG0bo8JzkcVg7gRKvagrEOl2G-Rzsa09ze3ekhWFJPA2MqPjJn8FohC2Qgy7UgfFWXBa2GkESgK6xr>


**康拓展开**

方法：

将每个数从头开始以N，N-1，N-2......作为编号

对于编号i的数，给答案加上a[i]\*(i-1)!

其中a[i]表示比i小的数且在之前没出现过的数个数，乘以i-1的阶乘



ans=a[N]\*(N-1)!+a[N-1]\*(N-2)!+a[N-2]\*(N-3)!+......+a[1]\*0!

**康托逆展开**

给定一个数列在全排列中的位置x，求该数列

方法:

先将x=x-1\


同样从左到右编号N,N-1,N-2......


然后从左开始 i=N   -> 1

t=x/(i-1)!

t表示比该位小的没出现过的数的个数

由此可以推出该位上的数

x=x%(i-1)!

一直循环


具体还是看看度娘上有详细的例子


献上丑陋的代码：






```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#include<algorithm>
#define LL long long int
using namespace std;
const int maxn=25;
LL f[maxn];
bool vis[maxn];
LL read()                             //快速读入
{
    LL out=0;
    char c=getchar();
    while(c<48||c>57) c=getchar();
    while(c>=48&&c<=57)
    {
        out=out*10+c-48;
        c=getchar();
    }
    return out;
}
void cal(int N)                           //预处理阶乘的值
{
    f[0]=1;
    f[1]=1;
    for(int i=2;i<N;i++)
        f[i]=f[i-1]*i;
}
int getpre(int N,int x)             //求出有多少未出现的数比x小
{
    int ans=0;
    for(int i=1;i<x;i++)
        if(!vis[i]) ans++;
    vis[x]=true;
    return ans;
}
void getprint(int N,LL x)        //求出有x个比它小的未出现的数
{
    LL cnt=-1,i=0;
    while(cnt<x&&i<N)
    {
        i++;
        if(!vis[i])
            cnt++;
    }
    vis[i]=true;
    cout<<i;
}
int main()
{
    int N=read(),K=read();
    LL ans,x;
    cal(N);
    char cmd;
    while(K--)
    {
        cmd=getchar();
        while(cmd!='P'&&cmd!='Q') cmd=getchar();
        if(cmd=='Q')                       //康托展开
        {
            fill(vis,vis+maxn,false);
            ans=0;
            for(int i=N;i>0;i--)
            {
                x=read();
                ans+=getpre(N,x)*f[i-1];
            }
            cout<<ans+1<<endl;
        }
        else                                         //逆展开
        {
            fill(vis,vis+maxn,false);
            bool first=true;
            x=read()-1;
            for(int i=N;i>0;i--)
            {
                if(first) first=false;
                else printf(" ");
                getprint(N,x/f[i-1]);
                x%=f[i-1];
            }
            cout<<endl;
        }
    }
    return 0;
}

```

---

## 作者：RainFestival (赞：1)

我们可以使用一种方法[深入了解](https://baike.baidu.com/item/%E5%BA%B7%E6%89%98%E5%B1%95%E5%BC%80/7968428)

ai的值应是i的位值×ai的值

i的位值类似于阶乘

ai的值应是ai-ai前面比i小的数字总和（自己想一想）

然后就可以去做了

先预处理阶乘

其他还有很多细节

比如开long long(int64)

下面附代码：

```cpp
#include<cstdio>
#include<iostream>
bool vis[55];
long long a[55],b[55];
long long co,n,k;
char ch;
int main()
{
	scanf("%d%d",&n,&k);
	a[n]=0;
	a[n-1]=1;
	for (int i=n-2;i>=1;i--)
	    a[i]=a[i+1]*(n-i);
	for (int nn=1;nn<=k;nn++)
	{
		ch=' ';
		while (ch!='P'&&ch!='Q') scanf("%c",&ch);  
		if (ch=='P')
		{
	        scanf("%lld",&co);
	        for (int i=1;i<=n;i++)
	        {
		        vis[i]=true;
		        b[i]=0;
	        }
	        for (int i=1;i<=n-1;i++)
	        {
		        long long q=co/a[i],s=0;
		        co=co%a[i];
		        if (co==0)
		        {
		        	q=q-1;
		        	co=co+a[i];
				}
				int j=0;
		        while(s<=q)
				{
					j++;
					if (vis[j]) s++;
				}
	            vis[j]=false;
		        b[i]=j;
	        }
	        int p=0;
	        for (b[n]=1;b[n]<=n;b[n]++)
	            if (vis[b[n]]) break;
	        for (int i=1;i<=n;i++)
	            printf("%d ",b[i]);
	        printf("\n"); 
		}
		else 
		{
	        long long s=0;
	        int x;
        	for (int i=1;i<=n;i++)
	            vis[i]=true;
        	for (int i=1;i<=n;i++)
        	{
	        	int p=0;
				scanf("%d",&x);
	        	for (int j=1;j<=x-1;j++)
		            if (vis[j]) p++;
		        vis[x]=false;
		        s=s+p*a[i];
	        }
	        printf("%lld\n",s+1);
		}
	}
	return 0;
}
```

时间79ms,内存816KB,代码长度1.33KB

谢谢巨佬，大佬的观赏



---

## 作者：Honeta (赞：1)

## LUOGU P3014 SOLUTION
### 思路点拨
康托展开（**使用树状数组优化**）与逆康托展开。
### 前置知识
1. [康托展开与逆康托展开](https://blog.csdn.net/ajaxlt/article/details/86544074)    

2. [树状数组](https://blog.csdn.net/Small_Orange_glory/article/details/81290634)
### 做法详解
上面提到的两个前置知识，还不会的请自行学习。我在这里主要讲一下二者是如何联系到一起的。  

在康托展开时，需要计算每一位数字在它和它以后的所有数字中是第几大的数，在这里我使用了树状数组对算法的时间复杂度进行了优化。  
  
我们设add(x,y)是将x加上y，ask(x)是查询x的前缀和。在预处理时，我们对从1到n的每一个i都分别add(i,1),假设我们当前算到了第i位数a[i]，首先我们add(a[i],-1),这个操作就相当于把a[i]划掉，而在第i位之前出现过的数都已经被我们提前划掉了。那么ask(a[i])即为在第i位之后出现的比a[i]小的数的总个数（即：还未被划掉的比a[i]小的数的总个数）。这样，我们就巧妙地利用了树状数组的性质对康托展开进行了优化。在数据较大时，这种优化作用是极为明显的。  
  
最后提醒一下：一定要开long long！
### AC代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#define ll long long
using namespace std;
ll n,k,t2,ans,fact[21],tree[21];
bool vis[21];
char t1;
void add(ll x,ll y)
{
  for(;x<=n;x+=x&-x)tree[x]+=y;
}
ll ask(ll x)
{
  ll res=0;
  for(;x;x-=x&-x)res+=tree[x];
  return res;
}
int main()
{
  scanf("%lld%lld",&n,&k);
  fact[0]=1;
  for(ll i=1;i<n;i++)fact[i]=fact[i-1]*i;//递推求阶乘
  while(k--)
    {
      cin>>t1;
      memset(tree,0,sizeof(tree));
      memset(vis,0,sizeof(vis));
      for(ll i=1;i<=n;i++)add(i,1);//预处理树状数组
      switch(t1)
	{
	case 'Q'://康托展开（树状数组优化）
	  ans=0;
	  for(ll i=1;i<=n;i++)
	    {
	      scanf("%lld",&t2);
	      add(t2,-1);//划掉这个数
	      ans+=ask(t2)*fact[n-i];//运用树状数组求这位数字在它和它以后的所有数字中是第几大的数
	    }
	  printf("%lld\n",ans+1);//记得求出来的结果要加1
	  break;
	case 'P'://逆康托展开
	  scanf("%lld",&t2);
	  t2--;
	  for(ll i=1;i<=n;i++)
	    {
	      ll temp=t2/fact[n-i];
	      for(ll j=1;j<=n;j++)
		{
		  if(vis[j])continue;
		  if(!temp)
		    {
		      printf("%lld ",j);
		      vis[j]=1;
		      break;
		    }
		  temp--;
		}
	      t2%=fact[n-i];
	    }
	  printf("\n");
	}
    }
  return 0;
}
```


---

## 作者：tjq0630 (赞：0)

 ```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long n,m,fac[28],vst[30],a[30],x;
char op;
void init()  //初始化 
{
    for(int i=0;i<=20;i++)  // 这里到了20就已经十分大了，所以无需再往后运算 
    fac[i]=1;
}
ll contor(ll x[])  //Cantor的运算 
{
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        int tag=0;  //标记为0 
        for(int j=i+1;j<=n;j++)
        {
            if(x[i]>x[j])
            tag++;  //更新标记 
        }
        ans+=tag*fac[n-i];
    }
    return ans+1;
}
void recontor(ll x)  //Cantor的逆运算 
{
    memset(vst,0,sizeof(vst));
    x--;
    ll k;
    for(int i=1;i<=n;i++)
    {
        ll ans=x/fac[n-i];  //Cantor的实际操作1 
        for(int j=1;j<=n;j++)
        {
            if(!vst[j])
            {
                if(!ans)  //加入ans为0的话就赋值 
                {
                    k=j;
                    break;  //时间上的优化 
                }
                ans--;
            }
        }
        printf("%d ",k);
        vst[k]=1; //回溯 
        x%=fac[n-i];  //Cantor的实际操作2 
    }
    printf("\n");
}
int main()
{
    scanf("%lld%lld",&n,&m);
    init();
    for(int i=1;i<=n;i++)
    fac[i]=i*fac[i-1];  //康托展开的预处理 
    for(int i=1;i<=m;i++)
    {
        cin>>op;  //判断题目所给的标记
        if(op=='P')
        {
            scanf("%lld",&x);
            recontor(x);  //康托展开逆运算，进行加进去 
        }
        if(op=='Q')
        {
            for(int i=1;i<=n;i++)
            scanf("%lld",&a[i]);  //康托展开运算，运算 
            printf("%lld\n",contor(a));
        }
    }
    return 0;
}
```


---

## 作者：loaky (赞：0)

利用康拓展开与逆康拓展开，大佬们已经讲的听清楚的了，相当于是对一个序列加密与解密的过程，我这里讲一下怎么实现，注释在代码中
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=50;
long long  n,k,a[maxn],ans,sum[maxn],b[maxn],y;
void get(){//正向展开
	long long fj=1;//fj是阶乘之积
	long long ki=0;
	for(long long i=1;i<=n;i++){
		for(long long j=i+1;j<=n;j++){
			fj*=(n-j+1);
			if(a[i]>a[j]) ki++;//求a[i]后面有多少个比a[i]大得数
		}
		ans+=(ki*fj);//加上每一位的值
		ki=0;//清楚为初始值
		fj=1;//同上
	}
}
void get2(){//反向求
	long long ct=0;//ct表示当前以求得个数
	long long m=0;//m为所得的商
	long long p=0;//p为余数
	m=(y/sum[1]);
	p=(y%sum[1]);
	for(long long i=1;i<=n;i++){//如果有与这个商相同的就是这一位，如果不清楚为什么，看一下大佬们讲解的逆展开
		if(b[i]==m){
			a[++ct]=i;
			break;
		}
	}
	for(long long i=1;i<=n;i++){//比这个数大的所有数都少了一个比本身小的数
		if(i>=a[ct]) b[i]--;
	}
	while(ct<n-1){//开始每一位求数，求不到最后一位
		ct++;
		m=p/sum[ct];
		p=p%sum[ct];
		for(long long i=1;i<=n;i++){
			if(b[i]==m){
				a[ct]=i;
				break;
			}
		}
		for(long long i=1;i<=n;i++){
			if(i>=a[ct]) b[i]--;
		}
	}
}
int main(){
	//freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(long long i=1;i<=n;i++){
		sum[i]=1;
		b[i]=i-1;
		for(long long j=i+1;j<=n;j++){
			sum[i]*=(j-i);//sum相当是每一位的阶层，我这里没有用
		}
	}
	sum[n]=0;
	for(long long i=1;i<=k;i++){
		char opt;
		scanf("%c",&opt);
		while(opt==' '||opt=='\n') scanf("%c",&opt);
		if(opt=='P'){
			scanf("%lld",&y);
			y-=1;
			for(long long i=1;i<=n;i++){
				b[i]=i-1;
			}
			get2();
			for(long long i=1;i<=n-1;i++){
				printf("%lld ",a[i]);
			}
			for(long long i=1;i<=n;i++){//特别输出最后一位，因为之前所有的数，在b的变化中，最终的值都会为-1，只有最好用一个数的b值为0，因此，找到这个数输出来。
				if(b[i]==0){
					printf("%lld",i);
					break;
				}
			}
			cout<<endl;
		}
		else if(opt=='Q'){
			for(long long i=1;i<=n;i++){
				scanf("%lld",&a[i]);
			}
			ans=1;
			get();
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

