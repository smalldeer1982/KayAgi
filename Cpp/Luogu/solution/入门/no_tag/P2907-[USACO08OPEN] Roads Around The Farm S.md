# [USACO08OPEN] Roads Around The Farm S

## 题目描述

Farmer John 的奶牛对探索农场周围的领地产生了兴趣。最初，所有 $N$ 头奶牛（$1 \leq N \leq 10^9$）以一个大群体的形式开始沿着一条道路旅行。当遇到岔路时，群体有时会选择分成两个较小的（非空）群体，每个群体沿着一条道路继续前进。当其中一个群体到达另一个岔路时，它可能会再次分裂，依此类推。

奶牛们设计了一种特殊的分裂方式：如果它们可以分裂成两个群体，使得群体的大小正好相差 $K$（$1 \leq K \leq 1000$），那么它们就会以这种方式分裂；否则，它们就停止探索，开始安静地吃草。

假设总是会有新的岔路，计算最终安静吃草的奶牛群的数量。

## 说明/提示

有 $6$ 头奶牛，群体大小的差异是 $2$。

最终有 $3$ 个群体（分别有 $2$、$1$ 和 $3$ 头奶牛）。

```plain
  6
 / \
2   4
   / \
  1   3
```

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
6 2 
```

### 输出

```
3 
```

# 题解

## 作者：HHH恢 (赞：44)

我也是第一次发题解......选了个简单的题


------------**~~华丽丽的分割线~~**------------

1. 假设牛群有n头牛
1. 假设分成两部分的牛数恰好相差k

即:

牛多的部分:(n+k)/2头

牛少的部分:(n-k)/2头

那么牛群要可分,需要满足:
1.  (n-k)>0			//没牛分什么.....
1. (n-k)为偶数//没个两双牛还敢除二??

由此可得代码(递归):

```cpp
#include<iostream>
using namespace std;

int k;
int f(int a){		//请别吐槽这个函数名-_-||
	if(a-k>0&&(a-k)%2==0)return f((a+k)/2)+f((a-k)/2);//终于散伙咯
	else return 1;	//想分手!没门
}

int main(){
	int n;
    cin>>n>>k;
	cout<<f(n);
    return 0;
}
```

	

---

## 作者：xukuan (赞：17)

算法：搜索——>>深度优先搜索（dfs），递归

纯模拟，如果要开记忆化搜索，数组可能会炸

个人认为难度应该是普及-（入门题怎么会涉及到dfs和递归？）

代码（c++）：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
//上述均不解释

ll k,n;//谨慎起见

ll dfs(int v){//代表有v群奶牛出现时的最终群数
	if(v<=k) return 1;//如果剩下的奶牛数小于要分的数量，就不会分裂，返回1
    //不能写成if(v<k) return 1，那样在v==k的时候会死递归
	if((v-k)%2==0) return (dfs((v-k)/2)/*少的那群*/+dfs((v+k)/2/*多的那群*/));//能分裂就继续分裂
	else return 1;//不能分裂就保留
}

int main(){
	scanf("%lld%lld",&n,&k);//输入
	printf("%lld",dfs(n));//输出
	return 0;//可不写，但不能写作return 1，会RE
}
```

---

## 作者：vectorwyx (赞：16)

较为简单的递归


------------
首先，我们看一下初始状态：数量为$N$的一群奶牛。

然后，题目要求我们做什么呢？

是计算这一群奶牛最终会分裂成几群奶牛。


------------
问题来了：如何算出最终分裂的结果呢？

由题目给出的分裂方式我们得出，对于任何一群走到三岔路口的奶牛，只有两种选择：分裂或不分裂

也就是**群数+1或不变**


------------
再回到初始状态：就只有一群奶牛

模拟一下整个分裂的过程：

判断能否分裂——

能分裂，答案+1，重复这一过程，即继续递归

不能分裂，终止递归，返回


------------


不难看出：当递归结束时，**分裂的次数+1=最终奶牛群数**

那我们判断这一群奶牛能分裂几次不就可以了吗？


------------
如何判断呢？

设$x,y$分别为分裂后两群牛的数目，$a$为分裂前的数目。

则$x,y$满足$x+y=a$，$x-y=k$.

两式相加得$2x=a+k$。

由于$x,y$为正整数，所以$a+k$是偶数且0<$x,y$<$a$；
不满足就无法分裂


------------

### 代码如下：
```cpp
#include<iostream>
using namespace std;
int ans=1,n,k;
//ans为分裂次数，由于最终答案还需+1，故初始化为1直接输出
void fl(int a){//a为当前牛群所含牛的数目
	int x,y;//x，y为分裂成两群之后的所含牛的数目
	if((a+k)%2!=0){//递归终止条件
		return;
	}
	else{
		x=(a+k)/2;
		y=a-x;
		if(x<=0||x>=a){
        //一群牛的数目不可能为非正数，更不可能多出来几头
			return;
		}
		if(y<=0||y>=a){//同上
			return;
		}
		ans++;
		fl(x);//继续递归
		fl(y);
	}
}
int main(){
	cin>>n>>k;
	fl(n);
	cout<<ans;
	return 0;
}

```

------------

### The End

---

## 作者：空气树 (赞：7)

用队列做的，感觉跟dfs相比不过是换了一种数据结构。
```cpp
#include<bits/stdc++.h>
using namespace std;
queue<int>dl;
//定义队列
int main(){
	int n,k;
	unsigned int s=0;
	cin>>n>>k;
	dl.push(n);
	while(!dl.empty()){
    //只要队列里有奶牛群就继续搜索
		int x=dl.front();dl.pop();
        //出队
		if(x<=0)continue;
        //如果这群奶牛为负，说明不合法，跳过
		int y=(x+k)/2;
        //计算分法
		if(x==y){
			s++;continue;
            //如果相等就可以停了
		}
		if(y*2-k==x){
			dl.push(y);dl.push(x-y);
            //进入队列
		}
		else {
			s++;
            //分不了了则增加答案
		}
	}
	printf("%d\n",s);
    //输出
    return 0;
}
```

---

## 作者：n0000000000o (赞：4)

分析题意，只要分后两群奶牛的差为k  这群奶牛就可以分

假设**总数q**能被分为两部分，**相差为k**，那么设其中一部分为x，则这两群奶牛可分别表示为

### x1=x 
### x2=x+k
### ->   x+k + x=q 
# -->      x=(q-k)/2

有为了满足实际条件，**x1，x2都要为整数**（不可能有半只奶牛吧。。。）
这便是主要思路。。

在此附上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int num=1;
int n,k;
void apart(int q)
{
    if(q-k<=0)//这时就不能再分了，因而要返回
        return;
    
    //恩。。见上方的说明
    //如果((q-k)/2)==((q-k)/2.0)，即这个数是整数，也就是说，-----((q-k)/2)有整数解！！！
    if(((q-k)/2)==((q-k)/2.0))
    {
        num++;//奶牛多分了一列
        apart((q-k)/2);
        apart(k+(q-k)/2);//再分别递归x1和x2
    }
}
int main()
{
    cin>>n>>k;
    apart(n);
    cout<<num;//直接输出结果~~~
}
```

---

## 作者：hsfzLZH1 (赞：3)

搜索思路奉上：

我们通过深度优先搜索来求解此问题。

因为重复计算同一个数的情况少之又少，非常罕见，所以我们可以不进行记忆化。

对于每个三叉路口上的牛群，我们判断他们是否可以分为两组头数相差为k的奶牛，但是数量正好为k或小于k的情况需要特殊判断，此时直接结束dfs过程，否则会卡死。

通过主定理，我们可以轻易得出这个算法的时间复杂度为O(log N)

这里介绍一下位运算的基础知识：

x&1，如果为1则x为奇数，否则x为偶数

x>>1，相当于进行x/2操作

我们可以设计出如下代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,ans;
void dfs(int x)
{
    if(x<=k||(x-k)&1){ans++;return;}//如果不符合条件，则计数器+1（这也是一群奶牛），结束dfs过程
    dfs((x-k)>>1);//对较少的那一群奶牛执行dfs过程
    dfs((x+k)>>1); //这是较多的一群奶牛
}
int main()
{
    scanf("%d%d",&n,&k);
    dfs(n);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：dl__hh6 (赞：2)

~~刚才才发了一篇c的，现在来发一篇Pascal的，，好像没人发吧！！~~

又时候做题目要多动动笔，模仿一下，就出来了；

这道题是一道简单的搜索题，不复杂；；

上**代码：**
```pascal
var
 x,k,n,ans:longint;
 procedure dfs(x:longint);
begin
  if (x<k+2)or((x+k)mod 2=1) then 
   begin     
    inc(ans);
   end
  else 
 begin
   dfs((x-k)>>1);
   dfs(((x-k)>>1)+k);
   end;
end;
begin
  read(n,k);
 dfs(n);
writeln(ans);
end.

```

---

## 作者：himitsu (赞：2)

# C语言版@_@

刚上洛谷没几次的蒟蒻加C语言小白来一发题解~
表示题解里全是C++的题解，那我来一个C吧。    
算法刚开始学，没学过大佬们用到的深度搜索，就是一个朴素的递归，就酱 →_→AC代码如下  
（注：计算思路其实和上面的大佬们差不多，就是列方程
x + x + k = n）

```c
#include <stdio.h>
int count =1;   //用全局变量计数分裂次数更方便~
int fen(int n,int k)
{
	int n1,n2;
	if(n>k && (n+k) % 2 == 0)
	{
		count++;
		n1=(n-k) / 2;n2=n-n1;
		
		
		fen(n1, k);
		fen(n2, k);
	}
	
	return count;
}
int main(void)
{
	int n,k,count;
	scanf("%d%d", &n, &k);
	
	count = fen(n,k);
	printf("%d", count);
	
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

这个题我看好多大佬都拿dfs做的，我刚看这个题的时候就把这个数据范围高估了，以为暴搜会TLE，就吓得用了个记忆化。就是递归N，显然要分群的话是要分成（N-k）/2和（N+k）/2的群，所以N如果能分的话必须满足条件N>k且N-k为偶数，否则就成为一个安静的群，返回1。能分的话就接着递归下去，而且返回的时候把结果保存在一个map里用来记忆化搜索，下次再搜到这个N的时候直接读取map中的结果。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int tot=0;
int k;
map<int,int> mp;
int dfs(int n){
    int a=mp[n];
    if(a>0){
        return(a);
    }
    if(n-k>0){
        if((n-k)%2==0){
            int res=dfs((n-k)/2)+dfs((n+k)/2);
            mp[n]=res;
            return(res);
        }
        else{
            mp[n]=1;
            return(1);
        }
    }
    else{
        mp[n]=1;
        return(1);
    }
}
int main(){
    int n;
    cin>>n;
    cin>>k;
    cout<<dfs(n)<<endl;
    return(0);
}
```

---

## 作者：Deny_小田 (赞：1)

丝毫没有什么难度的搜索题






```cpp
#include <cstdio>
int tot = 0,n,k;
void dfs(int n){
    if( n < 2+k || (n+k)&1 ){ tot++; return ; }
    dfs( (n+k)/2 );
    dfs( (n-k)/2 );
}
int main(int argc, char const *argv[]){
    scanf("%d %d",&n,&k);
    dfs(n);
    printf("%d\n",tot);
    return 0;
}
```

---

## 作者：_Andy_Lin_ (赞：0)

[博客传送门](https://www.luogu.com.cn/blog/linguosheng/)

------------
这题范围不大，用暴力dfs即可。不过，我为了~~耍帅~~提高效率，用了一部分比加减乘除与取模更快的位运算。

------------
AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans;
void dfs(int sum){
	if(sum<=k||(sum-k)&1){
		ans++;
		return;
	}
	dfs((sum+k)>>1);
	dfs((sum-k)>>1);
}
int main()
{
	scanf("%d%d",&n,&k);
	dfs(n);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：jbc392 (赞：0)

此题一看就是dfs

让我们来分析一下样例

看图

![](https://cdn.luogu.com.cn/upload/image_hosting/pn8o6j9b.png)

很明显答案是3

接下来讲dfs

```
void dfs(long long cow)
{
	if((cow + k) / 2 >= cow || (cow + k) % 2 != 0)//这里我的判定方法与julao都不一样
	{
		ans++;//如果到头了就累加答案
		return ;
	}
	dfs((cow + k) / 2);//用和差问题求出分出的2群牛
	dfs((cow - k) / 2);
} 
```

AC code：

```
#include <bits/stdc++.h>
using namespace std;

long long n ,k ,ans;

inline long long read()//快读
{
	long long x = 0;
	char c = getchar();
	while(!isdigit(c))
	{
		c = getchar();
	}
	while(isdigit(c))
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return x;
}

void dfs(long long cow)
{
	if((cow + k) / 2 >= cow || (cow + k) % 2 != 0)
	{
		ans++;
		return ;
	}
	dfs((cow + k) / 2);
	dfs((cow - k) / 2);
} 

int main()
{
	n = read(); k = read();//输入
	dfs(n);//dfs
	cout << ans;//输出
	
	return 0;//好习惯
}
```


---

## 作者：CNF_Acceptance (赞：0)

### 来发一篇队列的题解
看了几篇都是用的递归,但是我用的是队列

每次把队头取出，如果符合要求，便分成差为k，和为x的两堆，

##### 可以利用和差问题的方法，即分为(x+k)/2和(x-k)/2。

那什么情况可以不用分呢？

1.x<=k时

2.x不能分为两堆时，即(x+k)不为2的倍数

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
queue<int> q;//定义队列
int main(){
	int n,k;
	cin>>n>>k;q.push(n);//将n入队
	while(!q.empty()){
		int x=q.front();//取出队头
		q.pop();//弹出队头
		if(x>(k+1)&&!((x+k)%2)){//如符合要求
			q.push((x-k)/2);
			q.push((x+k)/2);//分为两堆
		}else{//如不能再分,即牛群停下吃草
			ans++;//累加答案
		}
	}cout<<ans;
	return 0;
}
```


------------
谢谢欣赏!

---

## 作者：Z先森 (赞：0)

其实，一开始我看这道题的数据范围，以为不能模拟之类的，毕竟最大数量有十亿，可是后来觉得除了深搜，想不出别的办法了。就索引试一下，真的可以了。

题目大概就是：
一群牛不断分裂，我们就统计那些不能再继续分裂的情况。

用递归（深搜），就有点像不断模拟牛群的分裂情况。

上代码：
```cpp
#include<iostream>
using namespace std;
long long sum=0,n,k;
void dfs(long long a)
{
	if(a<2+k)   //牛的数量低于最小可分裂数量
	{
		sum++; return;  //统计留下来吃草的奶牛 
	}
	if((a-k)%2!=0)  //比如n==7,k==2,排除不能分裂的情况 
	{
		sum++; return;
	}
	long long t=(a-k)/2+k;   //数量多k的一群牛 
	dfs(t);  //继续递归往两个路口走的牛 
	dfs(a-t); 
	return;
}
int main()
{         
	cin>>n>>k;
	dfs(n);  //深搜 
	cout<<sum;
    return 0;
}
```


---

## 作者：不存在之人 (赞：0)

一开始我还以为是结论题。

推了半天发现根本不是。

然后就想到了递归。

没错暴力模拟递归出结果。

真的没啥好解释的啊。

能分就分，不能分就不分停下来。

上代码:
```cpp
#include<cstdio>
using namespace std;
int k,ans;
void fen(int x)//分裂
{
    if(x<=k||(x-k)%2!=0)//不能分
    {
        ans++;
        return;
    }
    fen((x-k)/2);//少的那群
    fen((x+k)/2);//多的那群
}
int main()
{
    int n;
    ans=0;
    scanf("%d%d",&n,&k);
    fen(n);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：su226 (赞：0)

嗯，大家都用DFS做的，那我就献上一枚队列做的吧
```c++
#include <iostream>
using namespace std;
int main(){
	int group[1000000];//存储每组的奶牛数量
	int head=0,tail=1,n=1;//头指针、尾指针和奶牛组数
	double k,tmp;
    //第一组恰好有n头奶牛
	cin>>group[0]>>k;
	while(head<tail){
		tmp=group[head];
        //分裂成两组，一组保留在head里，一组存到tail里（节省空间）
		group[head]=tmp/2-k/2;
		group[tail]=tmp/2+k/2;
        //判断加起来是否是原来的大小，是否相差k，且不能出现负组
		if(group[tail]>0//不能用不等于，血的教训
		&& group[head]>0//相信我，一定要用大于！！！
		&& group[tail]+group[head]==tmp
		&& group[tail]-group[head]==k){
            //如果符合条件，则多一组，同时head指针不变
			tail++;
			n++;
		}else{
            //否则head安静地吃草，head指针后移
			head++;
		}
	}
	cout<<n;
	return 0;
}

```

---

## 作者：attack (赞：0)

为什么我感觉这题完全不像入门难度的题啊。。

我的思路是这样的

对于每一个n,k

解一个方程组使得

$x-y=k$

$x+y=n$

然后对于得到的x,y分别进行类似的操作

看起来挺简单，

但是我被精度卡了QWQ。。。。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<stdlib.h>
#include<ctime>
using namespace std;
const int MAXN=0x7fffff;
const int INF=50;
inline int read()
{
    char c=getchar();int f=1,x=0;
    while(c<'0'||c>'9')    {if(c=='-')    f=-1;c=getchar();}
    while(c>='0'&&c<='9')    x=x*10+c-48,c=getchar();return x*f;
}
int ans=0;
void dfs(int n,int k)
{
    double p=(double)(n+k)/2;
    double q=(double)n-(n+k)/2;
    int o=(n+k)/2;
    double l=p-(double)o;
    if(l!=0||p>=n&&q<=0||q>=n&&p<=0)
    {
        ans++;
        return ;
    }
    dfs(p,k);dfs(q,k);
}
int main()
{
    int n=read(),k=read();
    dfs(n,k);
    printf("%d",ans);
    return 0;
}
```

---

## 作者：xfydemx (赞：0)

这道题搞不定的同学，找几组数画图试试

其实就是一般的搜索，没有什么复杂的


```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,sum;
long long n,k;
void dfs(int x)
{
    if(x-k<=0) {
    sum++;return;//这条路走到头了，结果++
    }
    if((x+k)%2==0)
    {
    dfs((x+k)/2);
    dfs(x-(x+k)/2);//继续走，分两半递归
    }
    else sum++;
}
int main()
{
    cin>>n>>k;
    dfs(n);
    cout<<sum;
}
```

---

