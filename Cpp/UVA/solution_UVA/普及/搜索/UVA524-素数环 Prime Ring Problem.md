# 素数环 Prime Ring Problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=465

[PDF](https://uva.onlinejudge.org/external/5/p524.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA524/5273edd790a23e1ad73d017fd355830ccb468915.png)

## 样例 #1

### 输入

```
6
8```

### 输出

```
Case 1:
1 4 3 2 5 6
1 6 5 2 3 4

Case 2:
1 2 3 8 5 6 7 4
1 2 5 8 3 4 7 6
1 4 7 6 5 8 3 2
1 6 7 4 3 8 5 2```

# 题解

## 作者：逆流之时 (赞：33)

这题其实可以优化很多的。~~然而还是只有100ms~~  
1.两个相邻数之和最小应是3(1和2)，所以所有要判断的质数均为奇数，两个相邻数必为一奇一偶。  
2.数据范围较小，不必用质数筛，直接打表即可。  
3.确保搜索到n+1时直接回溯。
```cpp
#include<cstdio>
int T,a[20]={0,1},n,isp[40];
bool vis[20]={0,1};
void dfs(int x,int op)
{
	if(x==n+1&&isp[a[n]+a[1]])
	{
		for(int i=1;i<n;i++)printf("%d ",a[i]);
		printf("%d\n",a[n]);
	}
	if(x==n+1)return ;
	for(int i=op;i<=n;i+=2)//只搜奇数或偶数
		if(!vis[i]&&isp[i+a[x-1]])
		{
			a[x]=i;
			vis[i]=1;
			dfs(x+1,op^3);//1^3变为2,2^3变为1，用以保证相邻两个数为一奇一偶
			vis[i]=0;
		}
}
int main()
{
	isp[2]=isp[3]=isp[5]=isp[7]=isp[11]=isp[13]=isp[17]=isp[19]=isp[23]=isp[29]=isp[31]=1;
	while(scanf("%d",&n)!=EOF)
	{
		if(T)printf("\n");
		printf("Case %d:\n",++T);
		dfs(2,2);
	}
	return 0;
}
```


---

## 作者：Raw_Aya9285 (赞：32)

**就是一道纯搜索的题目。**

**思路：** 我们只要从第一个数开始搜索，遇到可以与上一个数凑成素数的就存一下，其他部分就按照普通的dfs就出来啦！简简单单~ 简简单单~（数据还很水）

那么代码要怎么写呢？我们分四部分来讲，分别是四个函数。

**Part 0 我们要用到的变量**

```cpp
int n,output[17],cnt=1;
bool book[17];
```
就这些。output是用来储存输出的，cnt记录case xxx，book判断这个数有没有用过。

**Part 1 素数判断函数isprime**

```cpp
bool isprime(int x){
    if(x<2)return false;
    if(x==2)return true;
    for(int i=2;i<=sqrt(x);i++){
    	if(x%i==0)  return false;
    }
    return true;
}
```
就是一般的素数判断，没有什么特别的，也不会超时，就不多讲了。

**Part 2 搜索函数dfs**
```cpp
void dfs(int x){
    if(x==n&&isprime(output[n-1]+output[0])){
    	print();
    	return; 
    }
    //如果数已经够了，并且最后一个数和第一个数可以结成素数
    //那么就输出（输出函数一会儿讲）
    for(int i=2;i<=n;i++){
        if(!book[i]&&isprime(i+output[x-1])){
            output[x]=i;
            book[i]=1;
            dfs(x+1);
            book[i]=0;
        }
    }
    //往其他数字搜索，如果可以凑成素数且没有用过
    //那么就往那边搜过去
    //记得处理标记！
}
```
一般的dfs。

**Part 3 输出函数print**

```cpp
void print(){
	for(int i=0;i<n-1;i++){
		cout<<output[i]<<" ";
	}
	cout<<output[n-1]<<endl;
    //输出注意格式！
}
```
UVa有点卡格式，一定要注意！

**Part 4 主函数main**

```cpp
int main(){
    while(cin>>n){//多组数据的处理
        if(cnt>1)cout<<endl;//注意格式
        cout<<"Case "<<cnt<<":"<<endl;//Case输出
        cnt++;
        output[0]=1;
        book[1]=1;//初始化
        dfs(1);//搜索
        memset(book,false,sizeof(book));//再次初始化
    }
    return 0;//结束！
}
```
主函数就是调用以及输入的，没什么难的。

**至此，这道题的代码就写完了。**

**完整代码：（懒得写头文件就当做是反作弊吧）**
```cpp
int n,output[17],cnt=1;
bool book[17];
void dfs(int x);
void print();
bool isprime(int x);
int main(){
    while(cin>>n){
    	if(cnt>1)cout<<endl;
	cout<<"Case "<<cnt<<":"<<endl;
	cnt++;
	output[0]=1;
	book[1]=1;
	dfs(1);
	memset(book,false,sizeof(book));
    }
    return 0;
}
void dfs(int x){
    if(x==n&&isprime(output[n-1]+output[0])){
	print();
	return;
    }
    for(int i=2;i<=n;i++){
        if(!book[i]&&isprime(i+output[x-1])){
            output[x]=i;
            book[i]=1;
            dfs(x+1);
            book[i]=0;
        }
    }
}
bool isprime(int x){
    if(x<2)return false;
    if(x==2)return true;
    for(int i=2;i<=sqrt(x);i++){
	if(x%i==0)  return false;
    }
    return true;
}
void print(){
    for(int i=0;i<n-1;i++){
    	cout<<output[i]<<" ";
    }
    cout<<output[n-1]<<endl;
}
```

**感谢观看！**

---

## 作者：今A (赞：17)

按照惯例，解释一波，代码在最后面。（acm的题目输出卡的很严~）

### 1、这道题目是一道典型的深度搜索（回溯）题目，代码也是比较简单且容易理解的~（看不懂的同学回去认真看书哈，逃~~）
### 2、读取到EOF结束符使用while（cin>>x）这个来检测，意思就是说读到EOF时，就会返回一个0值。[while(cin>>n)详解](https://zhidao.baidu.com/question/368355018.html)
### 3、输出问题，每一个输出必须一行，且最后一个数字不能有空格！！！（第一个犯错的地方），代码片段如下：
```cpp
for(int i=1; i<n; i++)
{
    cout << a[i] <<" ";
}
cout << a[n] << endl;
```
### 4、输出问题2，相邻两组数据中间加上一个空行，所以，是第二组数据以后的话，我们就要先输出一个空行，用来和上一组数据分开。代码片段如下：
```cpp

int i=1;
while(cin >> n)
{
    if(i>=2)     //第二组就要开始输出换行了。。
    {
    	cout << endl;
	}
    //...
    
    i++;
}
```
至此，这道~~可恶~~题目就可以ac了~    
整道题的代码如下：    
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int a[26]={0};  //选择的数字
bool b[26]={0}; //每个数字有没有被选择
int n;          //n个数字找素数环 

bool pd(int x,int y)
{
    int s=x+y;
    int n=sqrt(s);
    for(int i=2; i<=n; i++)
    {
        if(s%i==0)
        {
        	
            return false;
        }
    }
    return true;
}

void output(void)
{
    for(int i=1; i<n; i++)
    {
        cout << a[i] <<" ";
    }
    cout << a[n] << endl;
}
void f(int step)
{
    for(int i=1; i<=n; i++)
    {
        if(b[i]==0&&pd(a[step-1],i))
        {
            a[step]=i;
            b[i]=1;
            if(step==n)
            {
                if(pd(a[n],a[1])&&a[1]==1)
                {
                    output();
                }
            }
            else
            {
                f(step+1);
            }
            b[i]=false;
        }
    }
}
int main(void)
{
    int i=1;
    while(cin >> n)
    {
    	if(i>=2)     //第二组就要开始输出换行了。。
    	{
    		cout << endl;
		}
		
        for(int i=0; i<=18; i++)
        {
            a[i]=0;
        }
        for(int i=0; i<=18; i++)
        {
            b[i]=0;
        }	
        cout << "Case "<<i<<":"<<endl;	
        f(1);
        i++;
    }
    
    return 0;
}
```

---

## 作者：algobase (赞：15)

~~题目太水~~

------------
这题的中心思想就是 深度优先搜索DFS

我们要搜索每一个位置的可能会有哪些数。如果最后搜索出来的组合合法，我们就把它直接输出。

**注意：UVa的题目格式不能有任何多余空格和换行。我提交的时候好几次是`Presentation Error`**

------------
我们一步一步来。

0. 所需变量

$n$ ：如题所述

$i$ ：用于 `Case` 输出

$a[]$ ：答案数组，用来存储答案

$vis[]$ ：用来标记是否用过

1. 主函数

- 输入

`while(scanf("%d", &n) != EOF)`

题目说了：
>直到读到EOF结束

所以我们只用判断读进来的是否是`EOF`就行了

- 初始化
```cpp
memset(a, 0, sizeof(a));
memset(vis, 0, sizeof(vis));
a[1] = 1, vis[1] = 1;
```
把答案数组和标记数组初始化就行了

为了防止重复，我们把每一个答案的第一个数都定为1，而标记数组也同样要更改。

- `\n` 符 **坑点**
```cpp
if(i > 0)
{
	printf("\n");
}
```
只有第二次以后的前面才需要换行符，如果每一次后面都跟着一个换行符到最后一行会多出一行，这时就会`Presentation Error`。

- 初始输出

如题所述，每组数据前面都要输出 `Case ……`

`printf("Case %d:\n", ++i);`

- $dfs()$

最重要的部分~~没什么好讲~~

`dfs(2);`

因为第一个数已经锁定了，直接从第二次开始就行了。

2. $dfs()$ 函数

需要一个参数 $step$ ，表示已经走到哪一步了。

- 判断

我们要先判断是否到达了 $n$ ，如果到达了并且符合要求就输出。
```cpp
if(step > n)
{
	if(prime(a[n], a[1])) // 如果头尾相加是质数
	{
		for(int i = 1; i < n; i++) // 一个坑
		{
			printf("%d ", a[i]);
		}
		printf("%d\n", a[n]); // 不想Presentation Error就得多写几个字
	}
}
```
- 否则

如果没到步数呢？我们就要继续搜索。
```cpp
else
{
	for(int i = 2; i <= n; i++) // 因为1已经被用过了，从2开始搜索
	{
		if(!vis[i] && prime(a[step - 1], i)) // 如果没用过并且符合条件
		{
			a[step] = i;
			vis[i] = 1; // 标记一下
			dfs(step + 1); // 搜索
			vis[i] = 0; // 与回溯
		}
	}
}
```
至此，我们的程序就结束了。

------------
小朋友，你是否有很多问号？

$prime()$ 是个什么东东？

~~哦，对，差点忘了~~

```cpp
bool prime(int x, int y)
{
	int s = x + y; // 求和
	if(s == 0 || s == 1) // 加一个特判（好像也没用）
	{
		return 0;
	}
	for(int i = 2; i * i <= s; i++) // 因为精度问题，老师不建议用sqrt()
	{
		if(s % i == 0) // 再说也没意思了……
		{
			return 0;
		}
	}
	return 1;
}
```
$prime()$ 函数也就结束了

整个~~程序~~题解也就结束了

~~写题解不易，大家点个赞呗~~

---

## 作者：henrytb (赞：11)

### 刘汝佳大法好！

我又来介绍刘汝佳大法了QAQ（见紫书）

对于这道题呢，我们可以使用两种方法：

1. 生成-测试法（next_permutation）

1. 搜索：回溯法

我们发现：生成-测试法的时间复杂度是$O(n!)$（因为$1\sim n$的排列共有$n!$个），在$n$比较大是已经超时。

所以我们使用回溯法。

PS：此题的输出很毒瘤，行末不能有空格&&最后没有多余回车

我就被坑了QAQ

代码如下：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
bool prime[100],used[100];
int n,a[100],now;
void dfs(int deep){
    if(deep==n+1&&prime[a[1]+a[n]]){
        rep(i,1,n){
            printf("%d",a[i]);
            if(i!=n)printf(" ");
        }
        puts("");
        return;
    }
    rep(i,2,n){
        if(prime[i+a[deep-1]]&&!used[i]){
            used[i]=true;
            a[deep]=i;
            dfs(deep+1);
            used[i]=false;
        }
    }
}
int main(){
    prime[2]=prime[3]=prime[5]=prime[7]=prime[11]=prime[13]=prime[17]=prime[19]=prime[23]=prime[29]=prime[31]=true;  //每日打表心情好
    bool isf=false;
    while(~scanf("%d",&n)){
        a[1]=1;
        if(isf)puts("");
        isf=true;
        printf("Case %d:\n",++now);
        memset(used,false,sizeof(used));
        dfs(2);
    }
    return 0;
}
```

---

## 作者：asasas (赞：5)

这题是一道经典深搜题。

深搜，即大家所说的爆搜，几乎可以解决所有问题，但时间复杂度极高，一般用于骗取小数据的部分分

而这题由于极小的数据，我们可以使用深搜(即DFS)来解决这个问题。

注意：

1.UVA对于输出格式极其严格，所以要注意你的输出。

2.当搜索搜完时，还要判断第一个数和最后一个数的和是否是质数，不要漏过这一点。

代码：

```cpp
#include <stdio.h>
inline bool prime(int a) {//判质数 
	if (a==1) return 0;
	for (int i=2;i*i<=a;i++){
		if (a%i==0) return 0;
	}
	return 1;
}
bool use[20];//判读这个数有没有用过 
int a[20],n;//a数组存方案 
inline void pr(){//输出函数 
	for (int i=1;i<=n-1;i++){
		printf("%d ",a[i]);
	}
	printf("%d\n",a[n]);//行末不能有多余空格
}
inline void dfs(int step){//最重要的DFS，step是判断现在搜到第几个数了 
	if (step==n+1&&prime(a[n]+a[1])){//判断是否搜完了，且最后一个数和第一个数的和为质数
	pr();//到条件了就输出
	return ;//退出搜索 
	 } 
	 for (int i=2;i<=n;i++){
	 	if (use[i]==0&&prime(i+a[step-1])){//判断这个数是否使用过，且和左边那个数的和为质数 
	 		a[step]=i;//将这个数存入a[step] 
			use[i]=1;//标记 
			dfs(step+1);
			use[i]=0;//递归后还原 
	 	}
	 }
}
int main(){
	int t=1;//判断是第几个方案 
while(scanf("%d",&n)!=EOF){
    if(t>1) printf("\n");//注意输出 
	printf("Case %d:\n",t++);
	a[1]=1;
	use[1]=1;
	dfs(2);//第一个数为1，所以要从第二个数开始搜
	for (int i=1;i<=20;i++) use[i]=0;//初始化数组 
    }
    return 0;
}
```


---

## 作者：MY（一名蒟蒻） (赞：5)

## UVA的题是很坑的！
坑点1：行末**不能有多余空格**。

坑点2：**换行符**个数。

坑点3：记得判断序列**首尾相加是否为质数**。

还煤油注册的童鞋点[**这里**](https://onlinejudge.org)，至于注册步骤请自己摸索吧！

~~窝就是因为没注册吃了大亏，一直觉得自己的代码有问题（不过当时确实有问题）。~~

至于网站打不打得开，就要看各位的rp了，祝各位**rp++**！

### 思路：类似加了质数判断的全排列问题。

**代码**
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
//记录数组，输出数组
int book[30],n,print[30],ans;
bool ss[50];//质数判断表，当然您打表也是可以的
void dfs(int step)//核心
{
	if(step == n)//搜索终点 
	{
		if(ss[print[1]+print[n]])//如果搜到目标状态
		{
			for(int i=1;i<n;i++) printf("%d ",print[i]);//输出
			printf("%d\n",print[n]);//防空格，窝就是被这个坑了好多次
		}
		return ;//返回
	}
	for(int i=2;i<=n;i++)//还未达到终点，继续搜索
	{
		if(ss[i+print[step]] && !book[i])//判断搜索条件
		{
			book[i]=1;//标记
			print[step+1]=i;
			dfs(step+1);//继续往下搜索
			book[i]=0;//回溯
		}
	}
	return ;//好习惯
}
int main()
{
	ss[2]=1;
	for(int i=3;i<32;i+=2)//生成质数表
	{
		bool f=true;
		for(int j=3;j<=sqrt(i);j+=2) 
			if(i%j == 0) {f=false; break;}
		if(f) ss[i]=1;
	}
	while(scanf("%d",&n) != EOF)
	{
		if(ans) puts("");//从第二个答案开始，多输出一个换行符
		ans++;
		printf("Case %d:\n",ans);
		print[1]=1;
		memset(book,0,sizeof(book));
		book[1]=1;
		dfs(1);
	}
	return 0;
}
```
### 祝大家AC愉快！

---

## 作者：_jimmywang_ (赞：3)

~~前言：$vjudge$能过的，到这里来过不了，怀疑人生$2$小时……~~
## 切入正题
### 首先，我们不要花里胡哨的，弄个什么环啊啥的。把环拆了然后扯成一串不好吗？
```
    1--4
   /    \
  6      3  ======>  1--4--3--2--5--6
   \    /
    5--2
```
现在学过$dfs$的（没学过也没事，直到全排列就行，但代码给的是$dfs$的）都应该知道怎么做了吧。

好吧可能有人还不知道。

打个$DFS$基础全排列，判断是否相邻两数之和为质数（包括第一个和最后一个）就行了对不对？

然鹅:
```
n<=16，多组数据
     -----UVA524 素数环 Prime Ring Problem
```
分析一下复杂度：$n=16$时为$O(16!)=O(20922789888000)≈O(2*10e13)$

……………

$c++$连$1e10$都受不了，一个$n=16$就炸了，别说多组数据了。

那咋啊？剪枝啊！

当前到了第$u$位，$i$从$2$到$n$循环（因为第一位必须是$1$），若这个数没用过，而且与前一位的和是质数，那就选他，然后标记，回溯，不就完事？

就是如果这个数不行就把它扔了。

就像这样：
```
ll opt[20];//表示这一位是啥
bool vis[20];//用过没
void dfs(ll u,ll n){
	if(u==n+1){
		if(is(opt[n]+opt[1])){
			cout<<opt[1];
			for(int i=2;i<=n;i++)cout<<" "<<opt[i];//格式太狠了
			cout<<endl;
		}
	}
	for(int i=2;i<=n;i++)//2~n
		if(!vis[i]){//没用过
			if(is(i+opt[u-1])){//是质数
				opt[u]=i;//用它
				vis[i]=1;//用过了
				dfs(u+1,n);//下一位
				vis[i]=0;//回溯
			}
		}
}
```
是不是很简洁明了呢？

完整$Code$：
```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll rr() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	if(c=='-')f=-1,c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rr()
bool is(ll x){
	if(x==1)return 0;
	if(x==2||x==3)return 1;
	if(x%6!=1&&x%6!=5)return 0;
	for(ll i=5;i*i<=x;i+=6)
		if(x%i==0||x%(i+2)==0)return 0;
	return 1;
}//O(√n/6)的线性筛
ll n;
ll t;
ll opt[20];
bool vis[20];
void dfs(ll u,ll n){
	if(u==n+1){
		if(is(opt[n]+opt[1])){
			cout<<opt[1];
			for(int i=2;i<=n;i++)cout<<" "<<opt[i];
			cout<<endl;
		}
	}
	for(int i=2;i<=n;i++)
		if(!vis[i]){
			if(is(i+opt[u-1])){
				opt[u]=i;
				vis[i]=1;
				dfs(u+1,n);
				vis[i]=0;
			}
		}
}
int main() {
	opt[1]=1;
    while(cin>>n){
		t++;
		if(t>1)cout<<endl;//格式太狠了
    	if(n==1){
    		cout<<"Case "<<t<<":\n";
    		continue;
		}
    	cout<<"Case "<<t<<":\n";
    	dfs(2,n);
	}
    return 0;
}
```
望对大家有帮助！！！

---

## 作者：huainan_marquis (赞：3)

忍不住想写个题解，这是刘汝佳紫书上的原题，自然有其给定的解决思路，而我则是在回溯法的基础上做了一些优化。
优化思路则是将每个数i，如果他加上j为素数，则将i，j之间连上一条边。则这个问题转变为了哈密顿回路问题，不过还是用回溯法做。贴上代码：
然后估算了一下时间复杂度，原做法是O（n!)的样子，我的做法是O（n!/e^n)的样子
当然还是没用的，测试了一下n = 18 就两秒多了。。
```cpp
#include <iostream>
#include <memory.h>
#include <cstdio>
#include <vector>

using namespace std;

int prime[350],p[350],A[160],vis[160],tot = 0,n;

vector<int>addp[350];

void get_prime(){//生成素数表，不用管那个320，我最开始测试速度多生成了一些
    memset(prime,0,sizeof(prime));
    for(int i =2;i<=320;i++){
        if(prime[i] == 0)
            p[++tot] = i;
        for(int j = 1;j<=tot && i*p[j] <=320;j++){
            prime[i*p[j]] = 1;
            if(i%p[j] == 0) break;
        }
    }
}

void dfs(int u,int cur){
    if(cur == n){
        for(int i = 0;i<addp[u].size();i++){
            if(addp[u][i] == 1){
                    printf("1");
                for(int i = 1;i<n;i++){
                    printf(" %d",A[i]);
                }
                printf("\n");
            }
        }
    }
    else for(int i = 0;i<addp[u].size();i++){
        int v = addp[u][i];
        if(!vis[v]){
            A[cur] = v;
            vis[v] = 1;
            dfs(v,cur+1);
            vis[v] = 0;
        }
    }
}

int main()
{
    get_prime();
    A[0] = 1;
    int t =0;
    while(~scanf("%d",&n)){
        if(t>0) cout<<endl;
        cout<<"Case "<<++t<<":"<<endl;
        memset(vis,0,sizeof(vis));
        vis[1] = 1;
        for(int i =1;i<=n;i++) addp[i].clear();
        for(int i = 1;i<=tot;i++){
            for(int j = 1;j<=(p[i]-1)/2;j++){
                if(p[i]-j <= n){
                    addp[j].push_back(p[i]-j);
                    addp[p[i]-j].push_back(j);
                }
            }
        }
        //cout<<addp[6].size()<<endl;
        dfs(1,1);
    }
    return 0;
}

```

---

## 作者：CCCloud (赞：2)

### 典型的搜索题  
2020.5.9 增加优化时间的方案，并且只将代码的主要部分贴上来；  


------------

~~先不管那些输出的格式~~  
我们可以确定**4**点:  
1、我们一共要填**n个格子**  
2、每个格子要填1~$n$中的一个整数  
3、不能**重复**，且**相邻**、**首尾**的数之和要为质数  
4、首数字一定要为**1**
### 然后我们就可以进行搜索  
从1开始，在循环中确保每个数字**只用一次**且相邻的都为**质数**，在填完**所有**的格子之后在确定**首尾之和**是否为**质数**  

#### 代码如下： 

```cpp
int n,a[20];
bool vis[20];//定义一个vis数组来判断是否被用过

bool zhi(int x)//判断是否是质数
{
    int y=sqrt(x);
    
    for(int i=2;i<=y;i++)
    {
        if(x%i==0) return 0;
    }
    
    return 1;
}

void dfs(int pos)//dfs大法
{
    if(pos==n+1)//如果全部填完
    {
        if(!zhi(a[1]+a[n])) return;//如果首尾不是质数，那么就返回
        for(int i=1;i<n;i++)
        {
            printf("%d ",a[i]);//输出（注意格式）
        }
        printf("%d\n");//输出（注意格式）
        return;
    }
    
    for(int i=1;i<=n;i++)
    {
        if(pos==1)//如果填的是第一个格子
        {
            if(i>1) return;//如果第一个不是1，那么就直接返回，结束dfs
        }
        if(!vis[i])//如果没有用过
        {
            vis[i]=1;//设为用过
            a[pos]=i;//记录第pos个格子填的数
            
            if(zhi(a[pos]+a[pos-1])) dfs(pos+1);//如果第pos与第pos-1个数之和为质数，那么继续
            
            vis[i]=0;//用完的设为未用过
        }
    }
    
}
```

------------

### 优化：  
怎么样优化呢？  
我们可以**边搜索，边判断**相邻的数字之和**是否为质数**，如果不是质数，那么这一条的“枝干”就肯定**都是不符合要求**的，就跳过这次循环；  
#### 代码实现：
```cpp
bool prime(int x, int y)//判断是否为质数
{
    int s=x+y;
    for(int i=2; i<=sqrt(s); i++)
        if(s%i==0) return 0;
    
    return 1;
}

void dfs(int pos)
{
    if(pos==n+1)
    {
        if(prime(a[n], a[1]) && a[1] == 1)
        {
            for(int i = 1; i < n; i++)
            {
                printf("%d ", a[i]);
            }
            printf("%d\n", a[n]); // UVa坑
        }
        return;
    }
    for(int i = 1; i <= n; i++)
    {
        if(!vis[i]&&prime(a[pos-1], i))//多增加了判断条件
        {
            a[pos]=i;
            vis[i]=1;
            dfs(pos+1);
            vis[i]=0;
        }
    }
}
```

---

## 作者：linlin (赞：2)


  众所周知，uva的题目对格式的要求一致非常宽（bian）松(tai)。行末多一个空格会wa，结束多一个回车也会wa，所以我每次做uva的题目输出都要想好久。。如果国内比赛如此严格的话（笑）
### 好了，废话不多说，开始吧。
首先分析一下题目：
  输入一个小于16的数n，然后找出n的全排列中，相邻的两个数和为素数并且最后一个数和第一个数的和也是素数的所有排列，字典序从小到大排列。
  显而易见，数据很小。但也不能直接生成所有全排列，16！不是闹着玩的。但是，用一个简单的dfs还是可以的，连剪枝都不需要。
### 关于本题有几个细节：
  ####   1. 第一个数题目规定了必须是1.
####   2. 由于是字典序从小到大，搜索的时候也一定要从小到大找。
####  3. 至关重要的一点，每两组数据输出的时候中间一定要空一行。
ok，下面上程序带解释。
```cpp

#include<iostream>
#include<algorithm>
using namespace std;
int n,f;//f用在输出，待会讲
int a[20];//记录答案
bool b[20];//记录数字是否被用过
```
定义，没啥说的。
```cpp
bool prime(int p)
{
		int i;
		for(i=2;i*i<=p;i++)
		if(p%i==0)return false;
		return true;
}
```
判断素数，也没啥好说的，数据很小不用筛选。如果想节约时间可以打个表，但是在dfs里面判断也不会超时,所以就偷个懒不想改了。
```cpp
void print(int sum)
{
	int i;
	for (i=1;i<=sum;i++)
	{
		if(i!=sum)cout<<a[i]<<" ";
		else cout<<a[i];//如果是最后一个数字不输出空格
	}
	cout<<endl;//每输出一组数据换行
	return;
}
```
打印，简单易懂。
```cpp
void dfs(int p,int sum)//p为上一次存入数组的数，sum为目前数组的元素个数
{
	int i;
	if(sum==n)//如果a中存储的数个数已经和n一样说明这是符合条件的一种全排列，可以输出了
	{
	print(sum);
	return;
	}
	for(i=2;i<=n;i++)//从2开始枚举每一个数的可能
	if (prime(i+p)&&b[i])//如果说枚举的数i加上上一个数p是个素数并且b没用过
	{
	    if(sum+1==n)//如果数组加上这个i就成为一个全排列了，这里进行加1是不是素数的特判
	    {
	    	if (prime(i+1))//如果i加1还是素数，那么可以进入下一次回溯进行输出
	    	{
	    	a[sum+1]=i;
			dfs(i,sum+1);
			a[sum+1]=0;//还原现场
			return;
		}
	    	else return;//如果i加上1不是素数就不行
		}
		b[i]=false;//把i的状态更新成用过
		a[sum+1]=i;//数组增加一个元素i
	dfs(i,sum+1);//计数器加一进行下一次搜索
	b[i]=true;//还原现场
	a[sum+1]=0;					
	}
}
```
重头戏，dfs。解释很详细了。

```cpp
int main()
{
	int i;
	while(cin>>n)//cin是一个函数，返回值是读到的n，如果输入结束读不到值的时候返回值是0,0为false，输入的循环结束
{
	for(i=1;i<=n;i++)
	b[i]=true;//初始化状态，每一个数都没用过
	   f++;//计数器，记录这是第几组数据
	   if(f>1)cout<<endl;//这和上面一行是用来判断是否需要额外输出一个回车的，题目要求
	cout<<"Case "<<f<<":"<<endl;
    b[1]=false;//1肯定用了
    a[1]=1;//第一个一定是1；
	dfs(1,1);//开始dfs
	
}
	return 0;
}
```
最后是主程序，基本上都是输入输出。
### 完整代码如下：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,f;
int a[20];
bool b[20];
bool prime(int p)
{
		int i;
		for(i=2;i*1<=p;i++)
		if(p%i==0)return false;
		return true;
	}
void print(int sum)
{
	int i;
	for (i=1;i<=sum;i++)
	{
		if(i!=sum)cout<<a[i]<<" ";
		else cout<<a[i];
	}
	cout<<endl;
	return;
}
void dfs(int p,int sum)
{
	int i;
	if(sum==n)
	{
	print(sum);
	return;
	}
	for(i=1;i<=n;i++)
	if (prime(i+p)&&b[i])
	{
	    if(sum+1==n)
	    {
	    	if (prime(i+1))
	    	{
	    	a[sum+1]=i;
			dfs(i,sum+1);
			a[sum+1]=0;
			return;
		}
	    	else return;
		}
		b[i]=false;
		a[sum+1]=i;
	dfs(i,sum+1);
	b[i]=true;
	a[sum+1]=0;					
	}
}
int main()
{
	int i;
	while(cin>>n)
{
	for(i=1;i<=n;i++)
	b[i]=true;
	   f++;
	   if(f>1)cout<<endl;
	cout<<"Case "<<f<<":"<<endl;
    b[1]=false;
    a[1]=1;
	dfs(1,1);
	
}
	return 0;
}
```
好了，就是这样。





---

## 作者：兰陵王 (赞：2)

这个题要注意第一位是1。然后，用dfs来做，枚举至n即可。不多说，上代码：
```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
bool b[21];
int a[21],n,ans;
int print(){     //输出
	if(a[1]==1){
	for(int k=1;k<=n;++k)
	cout<<a[k]<<" ";
    }
    cout<<endl;
}
int pim(int x){   //判断素数
	if(x==0||x==1)return 0;
	for(int i=2;i<=sqrt(x);++i)if(x%i==0)return 0;
	return 1;
}
int dfs(int x){    //搜索回溯
	for(int i=2;i<=n;++i)
	    if(pim(i+a[x-1])&&(!b[i])){//如果相邻是质数,且没有被使用过,记录.
			a[x]=i;
			b[i]=1;
			if(x==n){if(pim(a[n]+a[1]))print();}
			else dfs(x+1);//回溯
			b[i]=0;
	    }
}
int main(){
	int we=0;
    while(scanf("%d",&n)==1){
        ans++;
        if(we!=0)cout<<endl;
        cout<<"Case:"<<ans<<endl;
        we++;
        a[1]=1;
        dfs(2);
    }
    return 0;
}
```

---

## 作者：望眼浮云 (赞：2)

无比恶心的一道题，因为输出格式交了n遍。。。

这是一道不(hen)错(shui)的搜索题，可以先把素数预处理一下，n<=16，处理31以内的素数就好了。然后爆搜一遍，搜的时候判一下素数，最后再判一下素数。

以下是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,cnt,a[100];
int b[100],vis[100];
void dfs(int l)
{
    for(int i=2;i<=n;i++)
    if(!vis[i]&&b[a[l-1]+i])  //i没有用过，且与上一个数的和为素数
    { 
        vis[i]=1;   //标记
        a[l]=i;     //存储
        if(l==n)    //放完了n个数
        {
            if(b[i+1]) //这是一个环，所以最后一个数和第一个数相邻
            {
                for(int j=1;j<n;j++) printf("%d ",a[j]);
                printf("%d",a[n]);  //这里很恶心，行末不能有空格
                printf("\n");
            }
        }
        else dfs(l+1);
        vis[i]=0;  //回溯
    }
}
int main()
{
    b[2]=b[3]=b[5]=b[7]=b[11]=b[13]=b[17]=b[19]=b[23]=b[29]=b[31]=1;     //先处理一下素数
    int t=0;
    while(scanf("%d",&n) == 1){
        cnt++;    
        memset(vis,0,sizeof(vis)); //清空标记
        if(t!=0) cout<<endl;  //别被样例骗了，两组数据之间要换行
        printf("Case %d:\n",cnt);  
        t++;
        a[1]=1;  //第一个数是1
        dfs(2);  //从第二个数开始搜
    }
    return 0;
}


```

---

## 作者：yoyiETO (赞：1)

这题还是一个很经典的搜索题的

看完后第一个反应：枚举所有情况(全排列)。
```cpp 
#include<bits/stdc++.h>
using namespace std;
int n,sum,kase;
int ans[20];
bool vis[20];
bool prime(int n)
{
	if(n<2) return 0;
	for(int i=2;i*i<=n;i++)
		if(n%i==0) return 0;
	return 1;
}
bool judge()
{
	if(ans[1]!=1) return 0;
	for(int i=1;i<n;i++)
		if(!prime(ans[i]+ans[i+1]))
			return 0;
	if(!prime(ans[1]+ans[n]))
		return 0;
	return 1;
}
bool print()
{
	if(judge()){
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<' ';
		cout<<"\n";
	}
}
void dfs(int k)
{
	for(int i=1;i<=n;i++)
	    if(!vis[i])
		{
		    ans[k]=i,vis[i]=1;
			if(k==n) print();
			else dfs(k+1);
			vis[i]=ans[k]=0;//恢复状态 
		}
}
int main()
{
	while(cin>>n)
	{
		cout<<"Case "<<++kase<<":\n";
		dfs(1);
		cout<<"\n";
	}
	return 0; 
}
```
结果TLE了2333...

Q：为什么会TLE

A：时间复杂度为$O(n!n)（$n$为judge函数），$n=11$时大概就超了。

所以需要剪枝，把明显不可能的剪掉。

如果相邻两个数的和已经不是素数了，就```return；```,不用再往下枚举了。

这样dfs函数就可以修改为↓(换了一种更简单的模板)，同时也省略了judge函数。
```cpp
void dfs(int cur)
{
	if(cur>n&&is_pri(a[1]+a[n])) print();
	else
	for(int i=2;i<=n;i++)
		if(!vis[i]&&is_pri(a[cur-1]+i))//剪枝时注意是cur-1 
		{
			a[cur]=i,vis[i]=1;
			dfs(cur+1);
			vis[i]=0;
		}
}
```
**AC Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[17],vis[17];
void print()//输出 
{
	for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	cout<<"\n";
}
bool is_pri(int x)//判断质数 
{
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return 0;
	return 1;
}
void dfs(int cur)
{
	if(cur>n&&is_pri(a[1]+a[n])) print();//注意a[1]+a[n] 
	else
	for(int i=2;i<=n;i++)
		if(!vis[i]&&is_pri(a[cur-1]+i))//剪枝 
		{
			a[cur]=i,vis[i]=1;//保存状态 
			dfs(cur+1);//递归 
			vis[i]=0;//恢复状态 
		}
}
int main()
{
	int t=0;
	while(cin>>n)
	{
		memset(a,0,sizeof(a));//多组数据 
		memset(vis,0,sizeof(vis));
		a[1]=vis[1]=1;
		cout<<"\n"<<"Case "<<++t<<":"<<"\n";//UVA的格式... 
		dfs(2);
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Water_Cows (赞：1)

这题是我第一节课学深搜的时候做的

然后按照板子打了一下。

算了，先介绍一下深搜是什么吧。

## 深搜

就是深度优先搜索。
搜索与回溯是计算机解题中常用的算法，很多问题无法根据某种确定的计算法则来求解，可以利用搜索与回溯的技术求解。回溯是搜索算法中的一种控制策略。它的基本思想是：为了求得问题的解，先选择某一种可能情况向前探索，在探索过程中，一旦发现原来的选择是错误的，就退回一步重新选择，继续向前探索，如此反复进行，直至得到解或证明无解。

其实上面的你看不懂也没事。只要明白，深搜就是把所有
的情况用递归枚举出来（~~其实就是一个暴力枚举~~）

一般代码长这样
```cpp
int Search(int k)

{

　for (i=1;i<=算符种数;i++)

　　if (满足条件)

　　   {

　　　　保存结果

　　　　if (到目的地) 输出解;

　　　  else Search(k+1);

　　　　恢复：保存结果之前的状态{回溯一步}

　 　  }

　}
 ```
 或者是
 ```cpp
 int Search(int k)

{

　  if  (到目的地) 输出解;

　　 else

　　　　for (i=1;i<=算符种数;i++)

　　　　　if  (满足条件)

　　　　　{
     
　　　　　    保存结果;
            
              Search(k+1);
　　　　　    
              恢复：保存结果之前的状态{回溯一步}
　　　　　}

}
```
好了，步入正题

### 首先，怎么判断质数

- 因为质数都是成对出现的，所以只需枚举到$\sqrt{n}$就行了

- 代码也很简单, 直接上$code$

  ```cpp
  inline int prime(int x)
  {
      if(x<2) return 0; // 每日特判心情好
      for(int i=2; i<=sqrt(x); i++) //记住从2开始，搜到根号x就行了，能大大节省时间
      {
          if(x%i==0) return 0; //如果能被整除，就返回不是质数
      }
      return 1; //否则返回是质数
  }
  ```
  
好了，代码就这么出来了

$code$:
```cpp
#include <cstdio>
#include <cmath> //sqrt要用
using namespace std;

int n, a[19], b[19]; 
//a数组存答案，b数组表示这个数是否在排列中被用过了

inline int prime(int x)
{
    if(x<2) return 0;
    for(int i=2; i<=sqrt(x); i++) //记住从2开始，搜到根号x就行了，能大大节省时间
    {
        if(x%i==0) return 0; //如果能被整除，就返回不是质数
    }
    return 1; //否则返回是质数
}

inline void dfs(int x)
{
    if(x==n+1)
    {
        int flag=0; //标记是否是一个合法答案
        for(int i=1; i<n; i++) //判断a[1]+a[2],a[2]+a[3],a[3]+a[4].....a[n-1]+a[n]是不是质数
        {
            if(!prime(a[i]+a[i+1])) flag=1; //如果不是，打上标记
        }
        if(!flag && prime(a[1]+a[n])) //如果标记没被打过，而且这是一个环，还要判断a[1]+a[n]是不是质数
        {
            for(int i=1; i<=n; i++) printf("%d ", a[i]); // 输出答案
            puts(""); // 换行
        }
    }

    for(int i=2; i<=n; i++) // 枚举2~n可选答案 , 因为1已经固定了
    {
        if(b[i]) continue; // 如果被用过了，那么不选他
        b[i]=1; //打上用过的标记
        a[x]=i; //记录答案
        dfs(x+1); //深搜下一层
        b[i]=0; //回溯
    }
}

signed main()
{
    int cnt=0;
    while(scanf("%d", &n) != EOF) // 读入多组数据
    {
        cnt++; // 统计第几次
        printf("Case %d\n", cnt); // 题目要求
        a[1]=1; // 因为只要1开头的质数环
        dfs(2); //深搜从2开始，因为1已经固定了
    }
    return 0;
}
```

然后，恭喜你，$\color{q}{TLE}$ 了

我看了好久，最终决定发帖求助

[这里](https://www.luogu.com.cn/discuss/show/212373)

有人和我说要先筛质数，那么

### 第二，怎么筛质数呢

- 你可以打表（因为数据很小）

- 你可以写一个埃氏筛

  ```cpp
  int p[110];
  inline void doprime() //先把质数筛选出来
  {
      pr[1]=1;
      pr[2]=0; // 预处理,0表示是质数
      for(int i=2; i<=100; i++) //因为数很小，所以到100就行了
      {
          if(pr[i]) continue; // 如果标记过了不是质数，那么就跳过
          for(int j=2; i*j<=100; j++)
          {
              pr[i*j]=1; // 把是他倍数的打上标记
          }
      } 
  }
	```
- 更好的，你可以写欧拉筛

	```cpp
	memset(pd,true,sizeof(pd));
	pd[0]=pd[1]=0;// 预处理
	for(int i=2;i<=n;i++)
	{
		if(pd[i])s[++cnt]=i; // 加入答案
		for(int j=1;j<=cnt;j++)
		{
			if(s[j]*i>n)break;
			pd[s[j]*i]=false;
			if(!i%s[j])break; // 找到第一个因子就跳出，这是最关键的一步！！！
		}
	}
   ```
- $PS.$ 具体上网去查

所以，我就写了个埃氏筛

$code$:

```cpp
#include <cstdio>
#include <cmath> //sqrt要用
using namespace std;

int n, a[19], b[19]; 
//a数组存答案，b数组表示这个数是否在排列中被用过了

inline int prime(int x)
{
    if(x<2) return 0;
    for(int i=2; i<=sqrt(x); i++) //记住从2开始，搜到根号x就行了，能大大节省时间
    {
        if(x%i==0) return 0; //如果能被整除，就返回不是质数
    }
    return 1; //否则返回是质数
}

int pr[110]; // 标记数组
inline void doprime() //先把质数筛选出来
{
    pr[1]=1;
    pr[2]=0; // 预处理,0表示是质数
    for(int i=2; i<=100; i++) //因为数很小，所以到100就行了
    {
        if(pr[i]) continue; // 如果标记过了不是质数，那么就跳过
        for(int j=2; i*j<=100; j++)
        {
            pr[i*j]=1; // 把是他倍数的打上标记
        }
    } 
}

inline void dfs(int x)
{
    if(x==n+1)
    {
        int flag=0; //标记是否是一个合法答案
        for(int i=1; i<n; i++) //判断a[1]+a[2],a[2]+a[3],a[3]+a[4].....a[n-1]+a[n]是不是质数
        {
            if(pr[a[i]+a[i+1]]) flag=1; //如果不是质数，打上标记
        }
        if(!flag && !pr[a[1]+a[n]]) //如果标记没被打过，而且这是一个环，还要判断a[1]+a[n]是不是质数
        {
            for(int i=1; i<=n; i++) printf("%d ", a[i]); // 输出答案
            puts(""); // 换行
        }
    }

    for(int i=2; i<=n; i++) // 枚举2~n可选答案 , 因为1已经固定了
    {
        if(b[i]) continue; // 如果被用过了，那么不选他
        b[i]=1; //打上用过的标记
        a[x]=i; //记录答案
        dfs(x+1); //深搜下一层
        b[i]=0; //回溯
    }
}

signed main()
{
    int cnt=0;
    doprime();
    //for(int i=1; i<=100; i++) if(!pr[i]) printf("%d ", i);
    //puts("");
    while(scanf("%d", &n) != EOF) // 读入多组数据
    {
        cnt++; // 统计第几次
        printf("Case %d:\n", cnt); // 题目要求
        a[1]=1; // 因为只要1开头的质数环
        dfs(2); //深搜从2开始，因为1已经固定了
    }
    return 0;
}
```

然后，还是T了。

## 正解

在枚举排列的时候先看看有没有和前一个的引起冲突

### 注意：

- 换行和空格！！！（~~这个让我颓废了一天/kk~~）

$code$:

```cpp
#include <cstdio>
#include <cmath> //sqrt要用
using namespace std;

int n, a[19], b[19]; 
//a数组存答案，b数组表示这个数是否在排列中被用过了

inline int prime(int x)
{
    if(x<2) return 0;
    for(int i=2; i<=sqrt(x); i++) //记住从2开始，搜到根号x就行了，能大大节省时间
    {
        if(x%i==0) return 0; //如果能被整除，就返回不是质数
    }
    return 1; //否则返回是质数
}

int pr[110]; // 标记数组
inline void doprime() //先把质数筛选出来
{
    pr[1]=1;
    pr[2]=0; // 预处理,0表示是质数
    for(int i=2; i<=100; i++) //因为数很小，所以到100就行了
    {
        if(pr[i]) continue; // 如果标记过了不是质数，那么就跳过
        for(int j=2; i*j<=100; j++)
        {
            pr[i*j]=1; // 把是他倍数的打上标记
        }
    } 
}

inline void dfs(int x)
{
    if(x==n+1)
    {
        int flag=0; //标记是否是一个合法答案
        for(int i=1; i<n; i++) //判断a[1]+a[2],a[2]+a[3],a[3]+a[4].....a[n-1]+a[n]是不是质数
        {
            if(pr[a[i]+a[i+1]]) flag=1; //如果不是质数，打上标记
        }
        if(!flag && !pr[a[1]+a[n]]) //如果标记没被打过，而且这是一个环，还要判断a[1]+a[n]是不是质数
        {
            puts(""); // 先换行
            for(int i=1; i<=n; i++) if(i<n) printf("%d ", a[i]); else printf("%d", a[i]); // 输出答案
        }
    }

    for(int i=2; i<=n; i++) // 枚举2~n可选答案 , 因为1已经固定了
    {
        if(b[i]) continue; // 如果被用过了，那么不选他
        if(pr[a[x-1]+i]) continue;
        b[i]=1; //打上用过的标记
        a[x]=i; //记录答案
        dfs(x+1); //深搜下一层
        b[i]=0; //回溯
    }
}

signed main()
{
    int cnt=0;
    doprime(); // 筛质数
    while(scanf("%d", &n) != EOF) // 读入多组数据
    {
        cnt++; // 统计第几次
        if(cnt>1) puts(""); // 还是题目要求
        printf("Case %d:", cnt); // 题目要求
        a[1]=1; // 因为只要1开头的质数环
        dfs(2); //深搜从2开始，因为1已经固定了
        puts(""); // 题目要求
    }
    return 0;
}
```

只有$120ms$,快吧

~~看我写了这么多，求管理员大大通过~~

---

## 作者：stdout (赞：1)

这是本蒟蒻的第三篇题解了（~~前面的都没有通过~~）   
对于这道题，有两种思路：
1. **生成排列（next_permutation）再进行检验**
2. **回溯法搜索**

但第一种方法枚举的排列较多，速度慢（导致TLE），所以这里我们介绍回溯法。   
程序的主体就是**dfs()函数**了。由于n不是很大，所以可以用一个数组（这里取名为vis）来储存已经使用过的数。再用函数（取名为isp)判断相邻两数之和是否是素数。   
具体函数代码如下：   
**注意：Uva卡的很紧，输出时（末尾）不能有多余空格（否则PE）**
```cpp
void dfs(int cur)  //cur为当前要填数的下标
{
	if(cur==n&&isp(a[0]+a[n-1]))  //填好了，别忘了判断第一个数和最后一个数
	{
		for(register int i=0;i<n;i++)
			printf(!i?"%d":" %d",a[i]); //Uva卡的很紧，不能有多余空格
		printf("\n");  //遍历输出
		return;  //退出
	}
	for(register int i=2;i<=n;i++)
	{
		if(!vis[i]&&isp(i+a[cur-1]))  //判断相邻两数之和
		{
			a[cur]=i;  //赋值
			vis[i]=1;  //标记
			dfs(cur+1);  //递归，考虑下一个
			vis[i]=0;  //取消标记（回溯）
		}
	}
}
```
素数判断函数（isp）就比较简单了，这里使用最普通的方法，如下：
```cpp
bool isp(int n)
{
	//对于这题，特判1和0也没啥意义
	int m=floor(sqrt(n)); //在cmath库中
	for(register int i=2;i<=m;i++) 
		if(n%i==0) return false; //能被整除，返回假（不是）
	return true;  //返回真（是）
}
```
下面是主函数部分，循环输入直到读到EOF   
**注意：按题目要求输出，且空行在输出后（否则PE）**
~~我被输出格式坑了好几次了QWQ~~    
上代码：
```cpp
int main()
{
	a[0]=1; //初始化，第一个数设为1
	for(register int i=1;scanf("%d",&n)==1;i++)
	{
		if(i>=2) printf("\n");  //第二行开始就要输出空行了
		printf("Case %d:\n",i);  //计数
		dfs(1);  //搜索
	}
	return 0;  //返回0
}
```
最后上AC代码，供参考：
```cpp
#include <cstdio>
#include <cmath> //数学函数包含sqrt和floor
int n,a[18];  //生成的环
bool vis[18];  //是否使用过
bool isp(int n)
{
	//对于这题，特判1和0也没啥意义
	int m=floor(sqrt(n)); //在cmath库中
	for(register int i=2;i<=m;i++) 
		if(n%i==0) return false; //能被整除，返回假（不是）
	return true;  //返回真（是）
}
void dfs(int cur)  //cur为当前要填数的下标
{
	if(cur==n&&isp(a[0]+a[n-1]))  //填好了，别忘了判断第一个数和最后一个数
	{
		for(register int i=0;i<n;i++)
			printf(!i?"%d":" %d",a[i]); //Uva卡的很紧，不能有多余空格
		printf("\n");  //遍历输出
		return;  //退出
	}
	for(register int i=2;i<=n;i++)
	{
		if(!vis[i]&&isp(i+a[cur-1]))  //判断相邻两数之和
		{
			a[cur]=i;  //赋值
			vis[i]=1;  //标记
			dfs(cur+1);  //递归，考虑下一个
			vis[i]=0;  //取消标记（回溯）
		}
	}
}
int main()
{
	a[0]=1; //初始化，第一个数设为1
	for(register int i=1;scanf("%d",&n)==1;i++)  //一直读到EOF并计数
	{
		if(i>=2) printf("\n");  //第二行开始就要输出空行了
		printf("Case %d:\n",i);  //计数
		dfs(1);  //搜索
	}
	return 0;  //返回0
```
~~管理员大大求过QAQ~~







---

## 作者：stdtest (赞：1)

这道题还是比较简单的，关键是要理清题目中的信息。我们可以用回溯（深搜）来做，代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101],b[101],n,num=1;
int su(int a) {//判断素数的函数
	if(a==0||a==1)return 0;
	for(int i=2; i<=sqrt(a); i++)
		if(a%i==0)return 0;
	return 1;
}
void print() {//打印函数
	for(int i=1; i<=n; i++)
		cout<<a[i]<<' ';
	cout<<endl;
}
void search(int l) {//搜索函数
	for(int i=2; i<=n; i++) {
		if(b[i]==0) {//b数组是来标记该位置是否被用过
			if(su(i+a[l-1])==1) {//判断当前这个数与前一个数的和是否为素数
				a[l]=i;
				b[i]=1;
				if(l<n)search(l+1);//当l<n时，说明数还没填完，继续回溯
				else {
					if(su(a[n]+1)==1)print();//当数都填完的时候，我们需要判断最后一个数与第一个数的和是否为素数，如果是的，那么这就是一条素数环，将它打印出来
				}
				a[l]=0;
				b[i]=0;//清零，为下一次回溯做准备
			}
		}
	}
}
int main() {//主函数
	while(cin>>n) {//控制输入
		cout<<"Case "<<num<<":\n";
		a[1]=1;
		search(2);
		num++;
	}
	return 0;//养成好习惯
}
```


---

## 作者：foxdemon (赞：1)

这道题的思路和[P1706 全排列问题](https://www.luogu.org/problemnew/show/P1706)相似

从第一层开始搜索直到越界，当越界的时候来输出。

但是这题的输出问题一定要注意,从第二组开始就有换行,同时每组数据的最后没有空格

# 请勿抄袭


代码如下：


```cpp


#include<bits/stdc++.h>//万能头真好用
using namespace std ;

int t ;
int ans[20] ;//存答案
bool vis[20] ;//判断这个数有没有取过

bool prime( int x )//判断素数,会更高端写法的可跳过QAQ
{
	if ( x == 0 || x == 1 ) return 0 ; 
	for ( int i = 2 ; i <= sqrt(x) ; i++ )//一个小优化,只需要枚举到√n
	{
		if ( x % i == 0 ) return 0 ;
	}
	return 1 ;
}

void dfs( int x ) 
{
	if ( x == t + 1 && prime ( ans[t] + ans[1] ) )/*当满足条件以及开头和末尾和是素数,这里补足没有判断首尾的情况*/
	{
		for ( int i = 1 ; i <= t - 1 ; i++ )
		{
			cout << ans[i] << " " ; 
		}
		cout << ans[t] << endl ;
	}
	for ( int i = 2 ; i <= t ; i++ )//从第二层开始因为第一层是1  
	{
		if ( prime ( i + ans[x - 1] ) && vis[i] == 0 )//如果这个数加上前一层的数的和是质数,并且这个数还没有被用过 
		{
			ans[x] = i ;//把这个数放进这一层 
			vis[i] = 1 ;//把这个数标记为用过了
			dfs( x + 1 ) ;//搜索下一层 
			ans[x] = 0 ;//回溯 
			vis[i] = 0 ;
		}
	}
}
int main()
{
	//freopen("a.txt","w",stdout) ;
  	/*这行代码主要是用来在存代码的那个文件夹里生成一个a文件,将代码的输出提取到这个文件里面,用来dbug的,但是注意代码运行时是不会有输出的*/
	int m = 1 ;
	while ( cin >> t && t != EOF )
	{
		memset(ans,0,sizeof(ans)) ;
		memset(vis,0,sizeof(vis)) ;
		//清空数组好习惯
		ans[1] = 1 ;//第一层的数一定是1,所以直接放进ans数组 
		vis[1] = 1 ;//标记 
		if ( m >= 2 ) cout << endl ;//从第二组数据开始才会每一个数据之间输出换行 
		cout << "Case " << m << ":" << endl ;
		dfs(2) ;//从第二层开始搜索 
		m++ ;
	}
	
	
	return 0 ;
	
}

```


---

## 作者：田所浩二仙贝 (赞：0)

萌新在刷了入门->普及几乎所有题之后终于依靠自己的能力写出来了这个dfs， _**我相信大家如果坚持刷题最终也能独自做出了很多题**_ 。作为一个新手说说我是怎么想的：

首先是要注意的问题：

1.dfs函数中的两个变量分别为：u(表示搜到的数），cnt（表示搜了多少个数）。

2.这道题是个环，所以在dfs搜到头(cnt==n)的时候要判断一下最后的数和1的和是否为素数。

3.注意要加上判重数组已经回溯问题。

4.最后输出格式：a.最后一位不能有空格
b.输入的组数大于2时要加回车

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int path[21];//记录路径
int st[21];//判重
int ans=1;//组数
bool isPrime(int a){//判断是否为素数
    if (a==2)return true;
    if (a%2==0) return false;
    int x=sqrt(a);
    for (int i=2; i<= x; ++i){
        if (a%i==0)return false;
    }
    return true;
}
void dfs(int u,int cnt)
{
    if(cnt==n)
    {
        if(isPrime(u+1))
        {
            for(int i=1;i<n;i++)
            {
                cout<<path[i]<<" ";
            }
            cout<<path[n]<<endl;
        }
        return ;
    }
    st[u]=1;
    path[cnt]=u;
    for(int i=1;i<=n;i++)
    {
        if(!st[i])
        {
            if(isPrime(u+i))
            {
                st[i]=1;
                path[cnt+1]=i;
                dfs(i,cnt+1);
                st[i]=0;
            }
        }
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        if(ans>=2)
        {
            cout<<endl;
        }

        cout<<"Case "<<ans<<":"<<endl;
        dfs(1,1);
        ans++;
    }
    return 0;
}

```




---

## 作者：菜鸟至尊 (赞：0)

思路主要就是dfs判断数组相邻两个的和是否为素数          
最后一格的时候特判就可成环             
题目数据范围不大                        
对于素数的判定是可以用一个函数打表的                 
                
温馨提醒                                                           
1.此题对于输出要求严格  多余空格与回车将WA                         

2.读入要用while(cin>>endd) 否则一直不读入会TLE

3.不要使用万能头和奇奇怪怪的头文件 UVA编译通不过  ~~<bits/stdc++.h>~~                                                                   
                                                
代码比较简洁 用时50ms 目前是榜首           

贴上代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
bool signd[19];int endd;int ans[19];
inline void write(int x)  //快写
{  
    int num = 0; char c[15];
    while(x) c[++num] = (x%10)+48, x /= 10;
    while(num) putchar(c[num--]);
}
inline bool pass(register int x){
	if(x==3||x==5||x==7||x==11||x==13)
	return true;
	if(x==17||x==19||x==23||x==29||x==31)
	return true;
	return false;
}
void dfsd(int x,int step){signd[x]=true;ans[step]=x;
    if(endd==step){
    if(pass(ans[1]+ans[endd])){
    for(int i=1;i<endd;i++)
        write(ans[i]),putchar(' ');
        write(ans[endd]);
        putchar('\n');	
	}
    signd[x]=false;
    return;}
	for(int i=1;i<=endd;i++){
	if(!signd[i]&&pass(x+i)){dfsd(i,step+1);}}
	signd[x]=false;
	return;
}
int main(){
	for(register int i=1;cin>>endd;i++){ 
	    if(i!=1)
	    cout<<endl;
		cout<<"Case "<<i<<":"<<endl;
	    dfsd(1,1);	
	}
    return 0;
}
```

---

