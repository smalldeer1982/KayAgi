# 最大の和

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2007ho/tasks/joi2007ho_a



## 样例 #1

### 输入

```
5 3
2
5
-4
10
3```

### 输出

```
11```

# 题解

## 作者：zhangyuhan (赞：19)

前缀和水题啊！！！

这就是一个前缀和版子题。

# 神马是前缀和？

前缀和就是指一个数列从第$1$项到第$i(1≤n)$项的和。

# 怎么用前缀和解决该题？

如图，该怎么求第$i$到第$j$项的和呢？

![](https://cdn.luogu.com.cn/upload/pic/46023.png)

令$s_1=\sum_{k=1}^{i}{a_k}$,$s_2=\sum_{k=1}^{j}{a_k}$,

则该区间的和为$s_2-s_1$

这道题跟上面的做法差不多。在读入$a$数列时，用$sum$数组记录$\sum_{j=1}^{i}{a_j}$,通项公式为$sum[i]=sum[i-1]+a[i]$。

接再从$k$开始循环，用$ans$记录最大的$sum[i]-sum[i-k]$,即每个长度为$k$的区间的和。

$AC$ $code$

```cpp
#include <iostream>
using namespace std;

int sum[100010],n,a[100010],k,ans;


int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){	
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=k;i<=n;i++)
		ans=max(ans,sum[i]-sum[i-k]);
	cout<<ans<<endl;
	return 0;//完结撒花！！！
}```

---

## 作者：Hydrogen_Helium (赞：15)

# 这是什么！！
## 无修改 线段树 板子啊！！

看到题解中竟没有一片线段树题解，于是我打算来普及一发~~装一波~~

这道题仅涉及两个线段树最基本操作:

建树  以及  区间查询

代码注释很详细，这里就不过多赘述，直接上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define maxn 100005

using namespace std;
                    //优雅的空行                   
int n,k,a[maxn<<2],L[maxn<<2],R[maxn<<2],sum[maxn<<2];
//L[rt]节点rt的左区间，R[rt]节点rt的右区间，sum[rt]维护区间rt的和 

//一些人习惯写到结构体里，但还是习惯写数组

void build(int rt,int l,int r)//建l~r区间的线段树，当前编号为rt
{

	L[rt]=l,R[rt]=r;//记录rt区间的左端点与右端点
    
	if(l==r){//当区间只剩一时个点，进行赋值操作
		sum[rt]=a[l];//写成sum[rt]=a[r]等效
		return ;//然后向上回溯
	}
    
	int mid=(l+r)>>1;//注意：线段树是一颗二叉树，因此要取中点
    
	build(rt<<1,l,mid);//递归建造rt的左子树（左儿子），rt<<1 -> rt*2
    
	build(rt<<1|1,mid+1,r);//递归建造rt的右子树（右儿子）,rt<<1|1 -> rt*2+1
    
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];//向上回溯时更新sum[rt]的值
}

int query(int rt,int l,int r)//区间查询：查询l~r区间的和
{

    if(L[rt]==l&&R[rt]==r)return sum[rt];//当当前区间与所查询区间重合时，直接返回sum[rt]
    
    int mid=(L[rt]+R[rt])>>1;//同样二分，取中点
    if(r<=mid)//如果要查询的区间完全在左子树，则进入左子树
        return query(rt<<1,l,r);
        
    if(l>mid)//如果要查询的区间完全在右子树，则进入右子树
        return query(rt<<1|1,l,r);
        
    return 
    query(rt<<1,l,mid)+query(rt<<1|1,mid+1,r);//否则返回其在左区间与右区间的和		
}

int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);//调用入口 ：从节点1开始建造1~n的线段树
	int maxm=-9999;
	for(int i=1;i<=n;i++){
		int j=i+k-1;//保证区间长度为k
		if(j>n)break;
		maxm=max(maxm,query(1,i,j));//从节点1开始向下，查询i~j的和，同时用maxm记录答案
	}
	cout<<maxm<<'\n';
	return 2333;//卖一波萌
}
```
有一点不好的事：
	线段树的常数一般很大，有些题会卡这一点
    
    
此题正解应该为前缀和，大概~~就~~快一个log吧..
啊哈哈


为了代码整洁，多加了几个空行..




---

## 作者：shame_djj (赞：8)

其实我想问问这题是怎么评到绿色的

这题打眼一看其实前缀和就能水过去。（而且应该是最快的）

但是作为树状数组爱好者，（其实是不会线段树）

看到同机房dalao[Hydrogen_Helium （~~女装dalao~~）](https://www.luogu.org/space/show?uid=168322)（快%他）的线段树题解

我决定发一篇树状数组的题解

关于树状数组的优点：

1、第一点，常数小

2、第二点，代码短

因此，当我们只需要求区间和时，我们就不需要线段树这种高级做法了

但是它明显的缺点就是只能维护区间和

所以大家（也包括本蒟蒻）还是应该好好学学线段树的

代码，我的码风比较鬼畜，大家稍微压压行其实这题30行就很足够了

关于树状数组的解释在代码里面

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

int ans;

inline int read () {
	char c = getchar (); int x = 0, f = 1;
	while (c < '0' || c > '9') {if (c == '-') f = -1; c = getchar ();}
	while (c <='9' && c >='0') {x = x * 10 + c - '0'; c = getchar ();}
	return x * f;
} // 快读板子

struct Tree { // 结构体存储
	int c[100010], n, k;
	void update (int i, int x) {
		for (; i <= n; i += i & -i)
			c[i] += x;
	}//更新操作，关于（i & -i），其实就是i在二进制下的最右边的一位
    // 而我们的树状数组上的每一个数表示的是从最近的2的整数次幂到这个数的和
	int s (int i) {
		int ans = 0;
		for (; i; i -= i & -i)
			ans += c[i];
		return ans;
	}// 求和的话，其实也只需要按照二进制把二进制形势下，这一位为一时，加上这一个数为下标的和就好了
	int sum (int l, int r) {
		return s (r) - s (l - 1);
	}//前缀和思路相减思路
} t;
//码风比较鬼畜，大家使劲压行的话能压到20行
void init () {
	t.n = read (), t.k = read ();
	for (register int i = 1; i <= t.n; i ++)
		t.update(i, read ()); 
}

void solve () {
	for (register int i = 1; i + t.k - 1 <= t.n; i ++)
		ans = max (ans, t.sum(i, i + t.k - 1));
}

void print () {
	printf ("%lld\n", ans);
}

signed main () {
	init ();
	solve ();
	print ();
	return 0;
}
```
至此本题就解决了

本题解希望大家能更好地理解与运用树状数组

最后祝大家能Noip rp++

~~最好还是好好学学线段树，比树状数组有用多了~~

---

## 作者：philosopherchang (赞：6)

这道题难度的确评错了，普及减吧。

前缀和维护就可以了。

但是有个坑点，原OJ应该用的全文比较，不会省略行末空格和回车，所以一定要加$endl$，看其他题解没有我提一下，应该有人（我）被卡了。

源代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,k,a[100001],sum[100001],ans;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=k;i<=n;i++)
	{
		ans=max(ans,sum[i]-sum[i-k]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Blue_wonders (赞：6)

## 简单的模拟AC(绝对易懂)
#### 排坑：最后输出换行，不然错
#### 思路
- 先求出第一组满足的解
- 后面不断往后搜索——新加一个数，删掉最后的数
- 每次搜索后判断是否与已知的最大答案进行比对，刷新最大答案
- 输出最大答案+换行(一定记得换行！！！)
#### AC代码(附详解)
因为这道题我之前就过了，今天看提问区有问的，所以就又简化了一下代码
[AC详情](https://www.luogu.org/recordnew/show/16477864)

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,k,p=0,ans=0;
int a[100001];//用数组来存放数据 
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];//输入 
        if(i<=k)p=p+a[i];//把要求的前几个先求出一个总和 
    }
    ans=p;//这是一个答案 
    for(int i=1;i<=n-k-1;i++){
         p=p-a[i]+a[i+k];//把最前面的加进来一个，删掉最后一个，刷新答案 
        ans=max(p,ans);//判断数据，取最大值 
    }
    cout<<ans<<endl;//千万别忘了换行 
    return 0;
}
```
谢谢大家能看我写的题解~！

---

## 作者：kevin_y (赞：3)

- 这题应该是被评错分了，大概橙题难度
- 我这题只开了一个循环，时间复杂度应该较快
- 我批注挺详细，这就不过多解释了

~~绝对不会告诉你我一开始else后面两句没用大括号括起来，WA了三次~~
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main(){
	int n,k,a[100001],i,ans=0,sum=-999;//越小越好
	cin>>n>>k;
	for(i=1;i<=n;i++){
		cin>>a[i];//存入
		if(i<=k)ans+=a[i];//小于k，就继续加
		else{
			ans+=a[i]-a[i-k];//减掉最早加的，加上刚输入的
			sum=max(sum,ans);//sum存最大答案
		}
	}
	cout<<sum<<endl;//没有endl会爆（AT题都是这样）
}
```
求管理大大给过

---

## 作者：封禁用户 (赞：3)

看了一遍，没有Pascal的，就发一篇吧！

此题太水，怎么能称为绿题呢？（各人认为应该是橙题）

## 思路

### 1.输入
### 2.前缀和
### 3.暴力枚举
### 4.输出

输入不用说了吧，不过要注意不需要换行

前缀和相信大家都会吧

暴力枚举每一个点。例如枚举a[1]和a[k],a[2]和a[k+1]……之间的和（用前缀和来算），最大值用ans来表示

输出ans

接下来献上Pascal代码

```
var a:array[0..100000]of int64;
    n,m,o1,ans,i:longint;
begin
 ans:=-maxlongint;//这句必写，假如a[i]全是负数，不写会错
 read(n,m);
 for i:=1 to n do
 begin
  read(a[i]);
  a[i]:=a[i]+a[i-1];//前缀和
 end;
 readln;
 for i:=m to n do
 begin
  o1:=a[i]-a[i-m];//前缀和
  if (o1>ans) then ans:=o1;//找最大
 end;
 writeln(ans);
end.
```
实在不会前缀和的那就算了，去看别的大佬的更简洁的算法吧（我是蒟蒻）

---

## 作者：zcl1024 (赞：2)

为绿（红）题写题解，好激动  
这道就是简单的前缀和，真的很简单  
献上cpp&&pascal
代码  
```cpp
#include <iostream>  
#define FOR(i,l,r) for (i=l;i<=r;i++)//个人习惯，~~不要学我~~  
using namespace std;  
int sum[100010];  //不想memset系列
int main(){  
    int n,k;  
    cin>>n>>k;  
    int i;  
    int x;  
    FOR (i,1,n){  
        cin>>x;sum[i]=sum[i-1]+x;//前缀和处理
    }
    int ans=0;
    FOR(i,k,n) ans=max(ans,sum[i]-sum[i-k]);//找出最大的
    cout<<ans<<endl;
    return 0;
}
```
-------------------------
```pas
uses math;//人类的本质之一，懒
var i,n,k,m,ans:longint;
    sum:array[0..100000] of longint;
begin
  read(n,k);
  for i:=1 to n do
  begin
    read(m);sum[i]:=sum[i-1]+m;//前缀和
  end;
  for i:=k to n do
  ans:=max(ans,sum[i]-sum[i-k]);//如果是从第l个数加到的r个数，那么l=i,r=i-k;
  writeln(ans);
end.
```

----------
本蒟蒻码风不好，大佬勿喷，蟹蟹


---

## 作者：庄庄庄庄乜 (赞：2)

## 思路
按照我的习惯，一般先讲这道题的思路。首先需要明白，这道题是要让我们求出一段连续的长度为k的子序列之和的最大值。首先最容易想到的就是朴素算法——暴力枚举。但这道题数据范围是n<=100000，如果每次在枚举长度为k的子序列之和时，都去跑一遍k的循环，时间复杂度就为n*k，必定超时。这是就要思考优化。

## 引入概念
这道题需要用到前缀和。这里为萌新们引入前缀和的概念。我们可以用一个数组（如s[i]）存下从1到i个数的总和。而s数组的值可以通过递推得到。公式即s[i]=s[i-1]+a[i]。应该很好理解。那么这个前缀和有什么用呢？下面就是这道题的重点。举个栗子，现在我们已经得到了所有的前缀和，要算出从第a个数到第b个数的和，是不是只需要用s[b]-s[a-1]即可？因为用第1个数到第b个数的和减去到第a-1个数的和，就是第a个数到第b个数的和

## 总结
为什么前缀和可以优化这道题的时间复杂度？仔细想想，如果用朴素算法，求出每一个子序列的和需要循环k次，而加入前缀和进行预处理之后，我们可以在O(1)的时间求出这段和。这道题可以说是一道前缀和的例题。而前缀和的应用也不止这些。最主要的应用就是直接求出一段序列（或矩阵）的和，可以应用在区间dp等题目中（不知道什么是区间dp也没关系，~~反正我也不是很熟悉~~，只要坚持学下去，以后总会学到并掌握的。）

## 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,k,a[100005],s[100005],ans=-0x7fffffff/2;//s[]数组就是前缀和，a[]数组是序列，因为要打擂台，所以提前把ans赋为无穷小（说是无穷小，其实是接近int型最小，除以2是防溢出，不除也没事）
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        s[i]=s[i-1]+a[i];//前缀和公式
    }
    for(int i=k;i<=n;i++) ans=max(ans,s[i]-s[i-k]);//打擂台，ans为答案，每次求出最大值，循环枚举的是子序列
    printf("%d\n",ans);//此处一定注意加上换行，之前没加错了2次
    return 0;
}
```

---

## 作者：Delva (赞：2)

请大家不要被这道题的难度标签所欺骗，应该是入门难度。其实就是扫一遍就完了。

硬要解释就是加上新值减去旧值实现区间移动。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 100009;
int n,k,A[maxn];
int main(){
	int s=0,ans=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",&A[i]);s+=A[i];
		if(i>k){
			s-=A[i-k];
			ans=max(ans,s);
		}
	}printf("%d\n",ans);
}
```

---

## 作者：right_cat (赞：1)

## 其实这道题可以用尺取法来做

尺取法，顾名思义，就像用尺子取一段区间，用i表示区间的左端点，j表示右端点，然后不断移动区间，每次移动区间时，不断更新答案即可。

尺取法需要限定范围。这道题，已经规定区间长度为k，即**j-i+1=k**，这是一个限定范围，同时，显而易见的是**j<=n**,这便是另一个限定范围。

有了限定范围，就只需要不断移动区间更新答案了。尺取法的时间复杂度近似为O(n)，这是完全可以接受的。

具体实现详见代码。

代码实现：
```cpp
#include <cstdio>

const int MAXN = 100000;

int a[MAXN + 5];

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int i = 1, j = 1, sum = a[1], ans = 0; 
	//一开始将左右端点的值都赋为1，sum一开始为a[1]，ans记录最终答案，初值赋0 
	while(true) {
		while(j - i + 1 < k && j < n) //两个限制范围，注意不取等(因为是先判断再++) 
			sum += a[++j]; //右端点后移，注意前置的++优先级比+=高 
		if(j - i + 1 < k) break; //如果最后都无法满足条件，就直接退出 
		ans = ans > sum ? ans : sum; //更新答案 
		sum -= a[i++]; //左端点右移，则需减去a[i]，注意这里使用后置++，即先-=后++ 
	}
	printf("%d\n", ans); //最后输出答案 
}
```


---

## 作者：梦里调音 (赞：1)

提供一个新思路。

发现很多dalao都用了两个数组。

我来一个只用一个数组的：

```
#include <iostream>
#include <string>
using namespace std;
int n,k,a[100001],ans,now;
int main(){
	cin>>n>>k;//输入如题
	for(int i=1;i<=n;i++)cin>>a[i];//输入
	for(int i=1;i<=n;i++){
		now+=a[i];//now表示现在前k个数的和
		if(i>k)now-=a[i-k];//注意特判
		if(i>=k)ans=max(ans,now);//特判这里不解释了，OIer们自己想吧！但这个特判很重要
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：樱花飞舞 (赞：1)

## 许多人想到了前缀和，但没有想到树状数组
在别处大佬们已经讲得很清楚了，如果需要请点[这里](https://www.luogu.org/problemnew/solution/P3374)

树状数组的好处：

（1）用于快速求前缀和；相对楼上楼下的~~土方法~~求前缀和，树状数组可以快速单点修改，区间求和，这是~~土方法~~做不到的。

（2）好写，调试方便，比线段树好多了
```cpp
#include<cstdio>
#define lowbit(X) ((X)&(-X))
#define MAX(X,Y) ((X)>(Y)?(X):(Y))
const int INT_INF = 99999999;
int c[100001], n, m;
void change(int x, const int y)	/*单点修改，把x位置加上y值*/
{
	while (x <= n)
	{
		c[x] += y;
		x += lowbit(x);
	}
}
int get_sum(int x)	/*求1~x的总和*/
{
	int ans = 0;
	while (x > 0)
	{
		ans += c[x];
		x -= lowbit(x);
	}
	return ans;
}
int get_sum(int x, int y)	/*重载函数，求x~y的总和*/
{
	return get_sum(y) - get_sum(x - 1);
}
int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1, x; i <= n; i++)
	{
		scanf("%d", &x);
		change(i, x);
	}
	int max_num = - INT_INF;
	for (int start = 1; start <= n - m; start++)
	{
		int temp = get_sum(start, start + m - 1);
		max_num = MAX(max_num, temp);
	}
	
	printf("%d\n", max_num);	/*别忘记了换行*/
}
```
最后，祝大家编程愉快，争取在比赛中取得好成绩！

---

## 作者：TRZ_2007 (赞：1)

## 这题目难度是不是评错了？
## 最多普及/提高-  

分割

---  
## 思路
这道题目，其实也是可以用枚举的，因为$n$,$k$都是小于$10^5$的，乘起来最多是$10^{10}$。我们又知道，$AT$的题不会这么卡极端，所以时间复杂度在$O(nk)$的时候也是可以过的。

---
## 解法

首先定义一个数组$book$，开大一点，题目说十万我们就开十一万，这样就避免了$RE$。利用循环变量$i$，$j$来重复跑，利用$ans$求和，再用$max$统计最大值，先看伪代码。  
```
for i=k...n  
	for j=k...i-k+1
    	ans=sum{book[j]}
    max=max{ans}
```
再看代码
```
#include <stdio.h>
#pragma GCC optimize(3)
#define N 110000
int book[N],n,k;
int read()//快读
{
	int x=0,p=1;
	char c;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			p=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*p;
}
int main()
{
	n=read();
	k=read();
	int ans=0,max=0;
	for(register int i=1;i<=n;i++)
		book[i]=read();
	for(register int i=k;i<=n;i++)//从k跑到n
	{
		ans=0;//每次求和都要归0
		for(register int j=i;j>i-k;j--)
			ans+=book[j];//求和
		if(ans>max)//比较最大值
			max=ans;
	}
	printf("%d\n",max);//输出记得换行
}
```

---

## 作者：meyi (赞：1)

### 本题是一道一维前缀和经典题目~~（话说评绿题实在是过了吧）~~
### 思路：将一个区间的总和用数组s替代，在输入时就提前算好，区间$[1,k]$的总和为$s[k]$，区间$[x,y]$的总和为$s[y]-s[x-1]$，所以在选连续的$k$个数时，若当前位置为$i(k<=i<=n)$时，这$k$个连续的数的总和就为$s[i]-s[i-k]$，答案$ans$就应赋值为$max(ans,s[i]-s[i-k])$。
### 上代码：
```cpp
#include<cstdio>
inline int qr(){	//快读，不需要多解释
    int x=0;bool f=false;char ch=getchar();
	while(ch<48||ch>57)f|=(ch=='-'),ch=getchar();
    while(ch>47&&ch<58)x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return f?-x:x;
}
inline int max(int a,int b){return a>b?a:b;}
//没调用STL，只能自己手写max
int k,n,m,s[100001];
//n和k同题意，m相当于思路中的ans，s为思路中的前缀和数组
main(){
	n=qr(),k=qr();
	for(register int i=1;i<k;++i)s[i]=s[i-1]+qr();
    //当i<k时，不能取数，但区间的和仍然需要求出
	for(register int i=k;i<=n;++i)m=max(m,(s[i]=s[i-1]+qr())-s[i-k]);
	//此段详见思路
    printf("%d\n",m);
    //注意，这里必须要打换行，所有AtCoder的题目不打换行就会WA
}
```

---

## 作者：XXZ1234 (赞：1)



用单调队列优化DP做的
第一次用单调队列发题解，求过。


```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200001],num[200001],q[200001];
int dp[200001];
int i,j,m,n,x,head,tail,ans;
const int oo=-0x3f3f3f3f;
void DP(){
	ans=oo;
	head=1;
	tail=1;               //起始位置为1 因为插入是q[++tail]所以要初始化为0
	q[tail]=0;
	num[tail]=0;
	for(i=1;i<=n;i++){    ////每次队首的元素就是当前的答案 
		while( head <= tail && num[head] < i-m )//维护队首
			head++;
		ans=max(ans,a[i]-q[head]);
		while( head <= tail && a[i] <= q[tail] )//维护队尾
		tail--;
		num[++tail]=i;
		q[tail]=a[i];
	}
	printf("%d\n",ans);    //输出
}
int main(){
	scanf("%d%d",&n,&m);   //输入
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		a[i]=a[i-1]+x;     //前缀和
	}
	DP();                  //DP!!
	return 0;
}
```


---

## 作者：Skeleton (赞：0)

一看这道题，线段树！！！

因为蒟蒻我最近在复习线段树，所以用线段树把这个打了。

具体思路：
跑一遍循环，从k到n，每次都计算i-k+1到i这k个数的和，并用maxm记录最大和（用线段树进行区间查询）

最后输出maxm就AC了！！！

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e6+1;
int n,k,maxm;
int num[Maxn];
int sum[Maxn];//区间和，建议开4倍

void build(int rt,int l,int r)//建树
{
	if(l==r)
	{
		sum[rt]=num[l];
		return;
	}
	int mid=(l+r)>>1;
	build(rt<<1,l,mid);//递归建树
	build(rt<<1|1,mid+1,r);
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];//更新根节点的区间和
}
int asksum(int rt,int l,int r,int al,int ar)//区间查询和
{
	if(al<=l&&r<=ar)//完全包含时，这段区间内的和即为所求，直接返回
	{
		return sum[rt];
	}
	int mid=(l+r)>>1,res=0;
	if(al<=mid)
	{
		res+=asksum(rt<<1,l,mid,al,ar);//递归查询求和
	}
	if(ar>mid)
	{
		res+=asksum(rt<<1|1,mid+1,r,al,ar);
	}
	return res;
}
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
	}
	build(1,1,n);
	for(int i=k;i<=n;i++)//跑一遍循环
	{
		maxm=max(maxm,asksum(1,1,n,i-k+1,i));//每次记录和的最大值
	}
	printf("%d\n",maxm);
	return 0;
}
```
珍爱OI，远离抄袭！！！

---

## 作者：Batzz (赞：0)

  题目不难理解，给出一段数列，再给出一个不大于数列长度的区间大小，求所有区间中元素的最大和
  

  这里要强调一下题目范围（这里题目翻译不全，参考根据原址的PDF）
  

  对于100%的数据，有1≤n≤100000,1≤k≤n，对1≤i≤n有abs（ai）≤10000，那么真·最大和就是1e9，所以显然int整型即可满足题目需求，无需耗费更大空间
  

  这道题因为确实难度比较捉鸡，所以比较适合初学者，而初学者一开始做很容易遇到tle（超时，即超过1000ms）或者WA（wrong answer答案错误）的问题，在这里贴一段非常典型且兼具WA与tle的核心代码
  
```
	for (int i = 1; i <= n-k; i++)
	{
		for(int j=i;j<=i+k;j++)
        {
        
             s=s+a[j];
        }
        
        if(s>max)max=s;
	}
```
WA错误1：这段代码的思路就是将区间以数列首元素为起点开始遍历整个数列，每一次求和，打擂法求出最大和max，但是在范围上，n-k是n往前推k位，而非实际上应该取的最后一个区间起点，如果要使终起点到数列终点的区间大小为k，实际上应取【n-k+1】，才能使区间中有k个元素，而内循环的i+k也是同理，应为i+k-1（例如显然1到k有k个元素，n-k+1看作（n-k）+1，n看作（（n-k）+k），是不是好理解了？）

WA错误2：一次内循环结束后，想想s还要继续累加吗？显然每个区间都是分开来求和的，因此一次内循环结束时，应将s的值初始化为0

tle错误：可以看出此算法的时间复杂度为O（(n-k)*k）而根据题目范围，可以用基本不等式得出其最小值为≤n^2/4，此时n-k=k则n=1e5，为O（2.5*1e9），显然超时，必须进行优化

仔细观察核心代码每次都在做什么，发现每一次区间往后移一位时，都直接重新从头到尾算一遍其元素和，但实际上根据我们遍历的规律，每次移动一格，那么其中可以有大量的元素不用重新累和，而每次移动和的变化实际上是加上移动后尾部的元素，再减去移动前头部的元素，这样只需要一层循环，时间复杂度降为O（n），显然不超时，修改后的核心代码如下

```
	for(int i=1;i<=k;i++)s+=a[i];
	max=s;
	for (int i = k+1; i <= n; i++)
	{
		s+=a[i]-a[i-k];
		if(s>max)max=s;
	}
```

当然这里也可以在输入时就计算好从第一位到每一位的和并用数组存储，然后将s+=a[i]-a[i-k];改为s=sum[i]-sum[i-k];这样就无须定义a数组，直接定义sum数组，时间和空间复杂度和原解是一致的

附上完整AC代码

```
#include <cstdio>
using namespace std;
int a[100001],n,k;//开辟数组保存数列，全局变量可以直接用于函数中
int maxs()//求最大和函数
{
	int max,s=0;
	for(int i=1;i<=k;i++)s+=a[i];//i尾第一区间元素
	max=s;给max一个初值
	for (int i = k+1; i <= n; i++)//i为区间尾
	{
		s+=a[i]-a[i-k];//当前区间和
		if(s>max)max=s;//打擂
	}
	return max;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);//输入数组
	}
        printf("%d",maxs());//输出结果
	return 0;
}
```

PS:其实这里可以不用#include<cstdio>而是#include <iostream>，然后把下面的scanf改为cin，printf改为cout，本来我用的就是iostream但是原日本网站测试的时候不知道是什么bug用iostream头文件和cin/out就会WA，实际上是没有问题的。

---

## 作者：wzm2007 (赞：0)

    此题可以使用前缀和优化
    用cnt[]来储存前缀和
    每读入一个数,计算cnt[i]
    最后循环计算最大和ans
    以下为代码:

------------

	#include<bits/stdc++.h>
    using namespace std;
    int a,cnt[100005];
    int main()
    {
        int n,k,ans=0;
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a);
            cnt[i]=cnt[i-1]+a;
        }
        for(int i=k;i<=n;i++)ans=max(ans,cnt[i]-cnt[i-k]);
        cout<<ans;
        return 0;
    }

---

