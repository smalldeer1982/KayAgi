# An abandoned sentiment from past

## 题目描述

A few years ago, Hitagi encountered a giant crab, who stole the whole of her body weight. Ever since, she tried to avoid contact with others, for fear that this secret might be noticed.

To get rid of the oddity and recover her weight, a special integer sequence is needed. Hitagi's sequence has been broken for a long time, but now Kaiki provides an opportunity.

Hitagi's sequence $ a $ has a length of $ n $ . Lost elements in it are denoted by zeros. Kaiki provides another sequence $ b $ , whose length $ k $ equals the number of lost elements in $ a $ (i.e. the number of zeros). Hitagi is to replace each zero in $ a $ with an element from $ b $ so that each element in $ b $ should be used exactly once. Hitagi knows, however, that, apart from $ 0 $ , no integer occurs in $ a $ and $ b $ more than once in total.

If the resulting sequence is not an increasing sequence, then it has the power to recover Hitagi from the oddity. You are to determine whether this is possible, or Kaiki's sequence is just another fake. In other words, you should detect whether it is possible to replace each zero in $ a $ with an integer from $ b $ so that each integer from $ b $ is used exactly once, and the resulting sequence is not increasing.

## 说明/提示

In the first sample:

- Sequence $ a $ is $ 11,0,0,14 $ .
- Two of the elements are lost, and the candidates in $ b $ are $ 5 $ and $ 4 $ .
- There are two possible resulting sequences: $ 11,5,4,14 $ and $ 11,4,5,14 $ , both of which fulfill the requirements. Thus the answer is "Yes".

In the second sample, the only possible resulting sequence is $ 2,3,5,8,9,10 $ , which is an increasing sequence and therefore invalid.

## 样例 #1

### 输入

```
4 2
11 0 0 14
5 4
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
6 1
2 3 0 8 9 10
5
```

### 输出

```
No
```

## 样例 #3

### 输入

```
4 1
8 94 0 4
89
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
7 7
0 0 0 0 0 0 0
1 2 3 4 5 6 7
```

### 输出

```
Yes
```

# 题解

## 作者：风中の菜鸡 (赞：4)

~~本蒟蒻~~又双叒叕来写贪心题题解了！！！

先说一个题意方面的易错点，本题要求的是序列 $b$ 中的数替换序 $a$ 中的 0 后的序列是否不为递增序列。所以如果最后是递增序列，输出 `Yes` ，否则输出 `No`。

这次介绍本题的两种方法：

一.搜索

注明：如果想练习搜索再用，并不推荐。

本题如果思考的暴力一点的话，就是把 $b$ 序列中的数填入 $a$ 序列的 $0$ 的所有情况求出来,然后在判断是否满足“不是递增序列”的条件，只要有一个不是，就输出： `yes` 。

但搜索时间复杂度会比贪心时间复杂度大很多，本题是数据小，若数据大一些就过不了，所以不建议使用。

若写搜索的话，代码请参考 [P1036 的题解](https://www.luogu.com.cn/problem/solution/P1036) ，这里就不放代码了。

 二.贪心

首先说一下本题为什么可以使用贪心吧，因为本题只需求出一种把 $b$ 序列中的数填入 $a$ 中，使 $a$ 序列不为递增序列的方案就可输出 `yes` 了。

所以我们只需在填 $0$ 的过程中从大到小填序列 $b$ 中的数字，保证尽可能让填之后的序列不为递增序列，最后记得判断被填后的序列 $a$ 是否为递增序列。

最后， 上贪心代码

code：

```
#include<bits/stdc++.h>
using namespace std;
int cmp(int x,int y){
    return x>y;
}
    int n,k,num;
    int a[110],b[210];
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=k;i++)
        cin>>b[i];
    sort(b+1,b+k+1,cmp);//从大到小排序列b 
    for(int i=1;i<=n;i++)
        if(a[i]==0)//找序列a中的0，并填入此时b中最大的数字 
            a[i]=b[++num];//num表示此时填了多少个数字了 
    for(int i=2;i<=n;i++)//循环判断序列a是否为递增序列 
        if(a[i]<a[i-1]){//如果不是递增序列 
            cout<<"Yes"; //输出Yes 
            return 0;
        }
    cout<<"No";//如果没结束说明是递增序列，就输出No 
return 0;//完结撒花！ 
}
```

---

## 作者：Lips (赞：3)

# 贪心

贪心思路已经很明显了，只要将 $b$ 数t组从大到小排序，每次遇到 $a_i=0$ 的情况时，便要将 $b$ 数组的目前最大的数赋给 $a_i$，当然，要将 $b$ 数组中那个最大的值删除掉。

**但为什么这么做呢？**

既然题目中说：要想让 $a$ 数列是否能通过操作来递增，那么我们就应当让 $b$ 数组中越大的数往前放，剩下那些较小的数与前面已经放过的较大的数就行不成递增惹。

**代码**

既然想要 $b$ 数组从大到小排序，而又可以高效地进行删除操作，当然就用 $\text{priority\_queue}$ 就珂以惹，$\text{STL}$ 真香。

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=110;
int n,k,a[MAXN],x,pos=1;
priority_queue<int,vector<int>,less<int> >q;//自动排序 
inline int read()//数据量大，用快读 
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
bool isok()//对a数组处理完后检查一遍 
{
	for(register int i=2;i<=n;i++) if(a[i]<a[i-1]) return 1;
	return 0;
}
int main()
{
	n=read(),k=read();
	for(register int i=1;i<=n;i++) a[i]=read();
	for(register int i=1;i<=k;i++) q.push(read());//读入b数列 
	for(register int i=1;i<=n;i++) if(a[i]==0) a[i]=q.top(),q.pop();//贪心 
	if(isok()) puts("Yes");//输出 
	else puts("No");
	return 0;
}
```

这是高清版：~~方便您们抄~~

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=110;
int n,k,a[MAXN],x,pos=1;
priority_queue<int,vector<int>,less<int> >q; 
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
bool isok() 
{
	for(register int i=2;i<=n;i++) if(a[i]<a[i-1]) return 1;
	return 0;
}
int main()
{
	n=read(),k=read();
	for(register int i=1;i<=n;i++) a[i]=read();
	for(register int i=1;i<=k;i++) q.push(read());
	for(register int i=1;i<=n;i++) if(a[i]==0) a[i]=q.top(),q.pop(); 
	if(isok()) puts("Yes");
	else puts("No");
	return 0;
}
```

---

## 作者：yzx72424 (赞：1)

[题意](https://blog.csdn.net/qq_34287501/article/details/72912504)

这一题：贪心？模拟

首先考虑k>1的情况，

设数列b中存在x,y
则交换x,y的先后顺序即可满足不递增

所以只需考虑k=1:

贪心？模拟。不知道。反正就一个空，遇到就塞进去，判断是否单调即可

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int a[maxn];
int b[maxn];
int vis[maxn];
int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(int i=0;i<k;i++)
        scanf("%d",&b[i]);
    if(k>1)cout<<"YES";
	else {
		 for(int i=0;i<n;i++){if(a[i]==0)a[i]=b[0]; }  
		 for(int i=1;i<n;i++)if(a[i]<=a[i-1]){cout<<"YES";return 0;}
		 cout<<"NO"; 
	}
}
```



---

## 作者：Daidly (赞：0)

考虑何时一定不能组成递增序列：

- 当 $a$ 序列除零外的数满足递增关系且序列中有且仅有一个 $0$ 并且 $b$ 序列中的唯一一个数要大于 $a$ 序列中 $0$ 的前一个数，小于 $0$ 的后一个数。

其他情况都可以构造出非递增序列。

注意把 $a$ 序列的第 $0$ 个和第 $n+1$ 个赋值为 $-1$ 和正无穷。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
int n,k,a[MAXN],b[MAXN],cnt,pre,nxt;
bool f=1;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	a[0]=-1,a[n+1]=1e9;
	for(int i=1;i<=n;++i){
		if(a[i]>a[i-1]&&a[i])cnt++;
		if(!a[i])pre=a[i-1],nxt=a[i+1];
	}
	for(int i=1;i<=k;++i){
		cin>>b[i];
	}
	if(cnt==n-k&&k==1&&b[1]<nxt&&b[1]>pre)puts("No");
	else puts("Yes");
	return 0;
}
```

---

## 作者：FR_qwq (赞：0)

我们先读一下题。
>且任一正整数在序列 $a$ 和序列 $b$ 中的出现次数的和不会超过 $1$

这句话的意思就是 $a$ 数组和 $b$ 数组中没有相同的数。题目就变得简单起来了。

我们分 2 种情况：

第一种：$k>1$。

当 $k>1$ 时，$b$ 数组中的数肯定 $>1$，且由题得，$b$ 数组中没有相同的数，所以 $b$ 数组肯定组成一个不是递增的序列，所以当把 $b$ 数组带入至 $a$ 数组中，$a$ 数组也必然可以组成一个不是递增的序列。

结论：遇到这种情况，直接输出 `Yes`。

第二种：$k=1$。

这种情况很简单，就只是把 $b$ 数组中仅有的一个数带到 $a$ 数组中值为 $0$ 的那个地方，最后判断一下是否能组成不是的递增序列就行了。

结论：遇到这种情况，只要把 $b$ 数组带到 $a$ 数组，在判断一下就行了。

所以，一串很短的 $\color{green}{\texttt{AC}}$ 代码就出来了：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cmath>
using namespace std;
int n,k,a[1000010],p,i;
inline int read(){int x=0,f=1;char ch='\0';while(ch<'0'||ch>'9')f=(ch=='-')?(0-f):f,ch=getchar();
while(ch>='0'&&ch<='9')x=x*10+(ch^'0'),ch=getchar();return x*f;}//快读，加快读取速度
int main(){
	n=read();k=read();//读入
	if(k>1)return printf("Yes\n"),0;//判断 k 是否为上文所说的第一种情况
	for(i=1;i<=n;i++)
		a[i]=read(),
		p=(a[i]==0)?i:p;//在读入 a 数组中的数的同时把 a 数组中值为 0 的存起来
	a[p]=read();//把 b 数组（就是 a 数组读完后读入的一个数）带到 a 数组中值为 0 的位置
	for(i=1;i<=n;i++)
		if(a[i]<a[i-1])
			return printf("Yes\n"),0;//判断当前 a 数组是否为一个不是递增的序列
	printf("No\n");
	return 0;//完结撒花~
}
```

P 党看这：
```pascal
var n,k,i,p,x:longint;
a:array[1..100000]of longint;
begin
readln(n,k);//读入
if(k>1)then
  begin
  writeln('Yes');
  halt;
  end;//判断 k 是否为上文所说的第一种情况
for i:=1 to n do
  begin
  read(a[i]);
  if(a[i]=0)then p:=i;
  end;//在读入的同时把 a 数组中值为 0 的数的位置存起来
read(x);//读入只有 1 个数的 b 数组
a[p]:=x;//把 b 数组带到 a 中值为 0 的数
for i:=1 to n do
  if(a[i]<a[i-1])then
    begin
    writeln('Yes');
    halt;
    end;//判断当前 a 数组是否为一个不是递增的序列
writeln('No');
end.//完结撒花~
```

---

## 作者：打表大蒟蒻 (赞：0)

这道题不难，可以用贪心来做。

贪心思路：因为把a数组的0变成b数组的元素后，要使a数组不单调递增，
所以使b数组单调递减后，
再向a数组依次插进去，一定是最优解。


------------


~~极不严谨的~~证明：

(1)k>1且k为整数

∵b数组没有重复数，

∴排序后b数组只能为单调递减。

又∵a数组中有k个数为递减，

∴a数组不可能为递增数列。

(2) k = 1

显然a数组可能为递增序列。

（贪心主要针对第一种情况，第二种情况在实现贪心时会被顺便处理）


------------

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define IO ios::sync_with_stdio(false);cin.tie(0)  //玄学加速

const int maxn = 3e2;  //个人习惯
 
int n, k, a[maxn], b[maxn], top = -1;
//定义n和k，a数组，b数组，top作后面b数组的下标
bool cmp(int x,int y){
	return x > y;
}  //从大到小sort的比较函数
int main ()
{
	IO;  //调用
    //freopen ("CF814A.in","r",stdin);
    //freopen ("CF814A.out","w",stdout);  //NOIP需要文件读写
	cin >> n >> k;
	for(int i = 0;i < n; i++)
		cin >> a[i];
	
	for(int i = 0;i < k; i++)
		cin >> b[i];
		
	sort(b, b + k, cmp);  //把b数组从大到小排序
	for(int i = 0;i < n; i++)
		if(a[i] == 0) a[i] = b[++top];  //把b数组中的每一个元素赋给a数组
	
	for(int i = 1;i < n; i++){
		if(a[i] <= a[i - 1]){
			cout << "Yes\n";
			return 0;
		}
	}  //判断是否单调递增
	cout << "No\n";
	return 0;
 } 
```


---

