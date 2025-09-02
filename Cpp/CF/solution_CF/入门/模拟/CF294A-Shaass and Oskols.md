# Shaass and Oskols

## 题目描述

Shaass要打一些鸟。

有 $n$ 根水平电线彼此平行排列，电线从顶到底编号为 $1$ 到 $n$ ，每根电线上都有一些鸟彼此相邻，第 $i$ 根电线上有 $a_i$ 只鸟。

如果Shaass击中其中的一只鸟（假设这只鸟在第 $i$ 条电线上），在它左侧的鸟会跳向电线 $i$-1，在它右侧的鸟会跳向电线 $i$+1 ,如果没有这样的电线，它们就会飞走。

Shaass打了 $m$ 只鸟，告诉你每条电线上初始时鸟的个数，你的任务是计算出 $m$ 次射击后每根电线上有多少只鸟。

## 样例 #1

### 输入

```
5
10 10 10 10 10
5
2 5
3 13
2 12
1 13
4 6
```

### 输出

```
0
12
5
0
16
```

## 样例 #2

### 输入

```
3
2 4 1
1
2 2
```

### 输出

```
3
0
3
```

# 题解

## 作者：Velix (赞：3)

一道很水的模拟题，可为什么标签是紫的......

程序很简单，只需要注意一点就过了

代码如下

```cpp
#include<iostream>
using namespace std;
int a[200000];//防止数据加强
int main()
{
	int b,c,d,e,f,g,h;
	cin>>b;
	for(c=1;c<=b;c++)//注意从一开始，零开始就会RE
	cin>>a[c];//输入
	cin>>d;
	for(e=1;e<=d;e++)
	{
		cin>>f>>g;
		a[f-1]+=g-1;//左边的鸟，假设一上的鸟飞到了零
		a[f+1]+=a[f]-g;//右边的鸟
		a[f]=0;//不要忘了清空
	}
	for(h=1;h<=b;h++)cout<<a[h]<<endl;//输出
}
```


---

## 作者：RealityCreator (赞：2)

# 让我来发一篇pascal的题解（因为似乎没有）
```
var
  n,i,a,b,t:longint;
  f:array[1..101] of longint;
begin
  readln(n);
  for i:=1 to n do read(f[i]);
  readln;
  readln(t);
  for i:=1 to t do
  begin
    readln(a,b);
    if a>1 then f[a-1]:=f[a-1]+b-1;//往上一根电线飞的鸟
    if a<n then inc(f[a+1],f[a]-b);//往下一根电线飞的鸟
    f[a]:=0;//打的电线上的鸟全部飞走
  end;
  for i:=1 to n do writeln(f[i]);
end.
```

---

## 作者：_Felix (赞：2)

```
这题不是很难哦，为什么要看题解呢~
看代码：
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[105];//保存电线上有多少鸟
int main()
{
	int n;
	cin>>n;//读入
	for(int i=1;i<=n;i++)
		cin>>a[i];//读入
	int m;
	cin>>m;//读入
	while(m--)
	{
		int x,y;//定义
		cin>>x>>y；//读入
		a[x-1]+=(y-1);//飞到i-1电线
		a[x+1]+=(a[x]-y);//飞到i+1电线
		a[x]=0;//记得归零，我看了五分钟才看出来
	}
	for(int i=1;i<=n;i++)
		cout<<a[i]<<endl;//欢快输出
	return 0;//完美结束
 } 
 ```
 by 你们可爱的czy

---

## 作者：lihanyang (赞：2)

一道简单的模拟题，看看代码就懂了
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
	int a[105];//数组开大好习惯
	int t;
	cin>>t;
	for(int i=1;i<=t;i++) cin>>a[i];
	int m;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		a[x-1]+=y-1;//左边的鸟
		a[x+1]+=a[x]-y;//右边的鸟
		a[x]=0;
	}
	for(int i=1;i<=t;i++) cout<<a[i]<<endl;
}
```

---

## 作者：珂爱甲贺忍蛙 (赞：1)

$$\Huge\text{模拟}$$
这就是模拟的一道题。

我们先输入电线根数，然后每次打掉之后，统计剩下的鸟数就可以了。

首先输入：
```
cin>>n;
for(i=1;i<=n;i++)
cin>>a[i];
```
接下来，我们统计鸟的数量：
```
cin>>m;
    for(i=1;i<=m;i++)
    {
        cin>>x>>y;
        a[x-1]+=y-1;//这是左边的鸟
        a[x+1]+=a[x]-y;//这是右边的鸟
        a[x]=0;
    }
```
最后输出就完美结束啦！
在这里贴一下总代码：
```
#include <bits/stdc++.h>
using namespace std; 
int a[10010];
int main() 
{
    long long i,x,j,m,l,n,k,t=0,y,ans=1,mm=0,num=1;
    cin>>n;
    for(i=1;i<=n;i++)
    cin>>a[i];
    cin>>m;
    for(i=1;i<=m;i++)
    {
        cin>>x>>y;
        a[x-1]+=y-1;
        a[x+1]+=a[x]-y;
        a[x]=0;
    }
    for(i=1;i<=n;i++)
	cout<<a[i]<<endl;
}
```
这就完成了。

---

## 作者：YLWang (赞：1)

码风简洁。

主要讲一下num-1与num+1为什么不会越界。

由题意，我们假设$a[0]$是从$a[1]$飞走的鸟。$[n+1]$是从$a[n]$飞走的。

那么就显然了。


```
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(int i = (k); i <= (j); i++)
#define INF (1 << 30) - 1
#define ll long long
#define reaD() read()
using namespace std;
inline int read()
{
    int num = 0, flag = 1;
    char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num * flag;
}
int n;
int a[1005];
int main()
{
    n = read();
    For(i, 1, n) a[i] = read();
    int Qnum = read();
    while(Qnum--) {
    	int num = read(), pos = read();
    	a[num-1] += pos - 1;
    	a[num+1] += a[num] - pos;
    	a[num] = 0;
	}
	For(i, 1, n) cout << a[i] << endl;
    return 0;
}

```


---

## 作者：PragmaGCC (赞：0)

一道大模拟题呢~

记得在打完一只鸟之后清空整层就好啦

code
```cpp
//这是一道水水的模拟题喔
#include <bits/stdc++.h>
using namespace std;
int read()//快读
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}
int f[110];//储存每行电线鸟的个数
int main()
{
    int n = read();

    for (int i = 1; i <= n; i++)//读入初始鸟的个数
        f[i] = read();

    int m = read();

    for (int i = 1; i <= m; i++)//打鸟开始
    {

        int x = read(), y = read();//x行的第y只鸟

        f[x - 1] += y - 1;//所有左侧的鸟全部飞到下一行
        f[x + 1] += f[x] - y;//所有右侧的鸟全部飞到上一行
        //右侧鸟的个数是“这层鸟的个数 - 包括自己的左侧 y 只鸟的数量”
        f[x] = 0;//清空这层
        //这里不需要考虑飞走的鸟，因为他们可以被看做是“飞到了第 0 行”或“第 n + 1 行”
        //这也是为什么数组下标从1开始输入
    }

    for (int i = 1; i <= n; i++)
        printf("%d\n", f[i]);

    return 0;
}
```


---

## 作者：k2saki (赞：0)

### 这道题真~~难~~水，真不愧是一道~~紫~~红题

方法：和标签一样，大模拟。

这个题没什么技巧性可言，直接上代码吧:

```cpp
#include <bits/stdc++.h>
using namespace std;
int m,n,a[1000001];
int main() {
	cin>>m;
	for(int i=1;i<=m;++i)
	{
		cin>>a[i];
	}
	
	cin>>n;
	
	for(int i=1;i<=n;++i)
	{
		int x,y;
		cin>>x>>y;
		a[x-1]+=y-1;//左边的鸟飞到前一个
		a[x+1]+=a[x]-y;//右边的鸟飞到后一个
		a[x]=0;
	}
	for(int i=1;i<=m;++i)
	{
		cout<<a[i]<<endl;
	}
	
	return 0;
}

```

注意：第一根电线的鸟会飞到第0根电线，所以数组下标要从零开始，不然......

---

## 作者：yf最qhhh (赞：0)

这道题实在想不出有什么好讲的啊。。。。

根据题目要求模拟就好了。
```cpp
for(i=1;i<=m;i++){
		scanf("%lld %lld",&x,&y);
		arr[x-1]+=y-1;
		arr[x+1]+=arr[x]-y;
		arr[x]=0;
	}
```
这是核心代码。

即左边的情况，右边的情况，最后别忘了清 $0$。

---

## 作者：人间凡人 (赞：0)

这么水的模拟题呀！可居然是一道紫题！不可思议。

思路：按照题目一行一行模拟，把打到的左侧的鸟都移动到左边的电线上去，右侧的鸟都移动到右边的电线上去即可，很水的。

模拟样例：

$5$

$10\ 10\ 10\ 10\ 10$

$5$

$2\ 5$

$3\ 13$

$2\ 12$

$1\ 13$

$4\ 6$

1、$14\ 0\ 15\ 10\ 10$

2、$14\ 12\ 0\ 12\ 10$

3、$25\ 0\ 0\ 12\ 10$

4、$0\ 12\ 0\ 12\ 10$

5、$0\ 12\ 5\ 0\ 16$

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,x,y,a[105];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		a[x-1]+=y-1;	//左侧的鸟飞到了左边的电线上
		a[x+1]+=a[x]-y; //右侧的鸟飞到了右边的电线上
		a[x]=0;	//这根电线上没有鸟了
	} 
	for(int i=1;i<=n;i++)printf("%d\n",a[i]);
	return 0;
}

```


---

## 作者：lhjy666 (赞：0)

### 本题的题意就是有n跟线每根线上有a[i]只鸟现在你打了m枪每枪打了第i根线上的第j只鸟在其后的鸟会跳到i+1根线上在其前的会跳到i-1根线上请问现在每根线上有几只鸟
### ~~其实就是模拟~~
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100005],b[100005],c[100005];
int main()
{
	ll n,m;
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	scanf("%lld",&m);
	for (ll i=1;i<=m;i++)
	{
		scanf("%lld%lld",&b[i],&c[i]);
		a[b[i]+1]+=a[b[i]]-c[i];//模拟其后的鸟会跳到i+1
		a[b[i]-1]+=c[i]-1;//其前的会跳到i-1根线上
		a[b[i]]=0;//清0
	}
	for (ll i=1;i<=n;i++)
	{
		printf("%lld\n",a[i]);
	}
	return 0;
}

```

---

