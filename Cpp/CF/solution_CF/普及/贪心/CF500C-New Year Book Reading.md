# New Year Book Reading

## 题目描述

小明非常喜欢读书。他一共有 $n$ 本书，编号为 $1\sim n$，第 $i$本书重 $w_i$。

小明计划在暑假的 $m$ 天里每天读一本书，第 $i$ 天读第 $d_i$ 本书，可能会重复读到同一本书。

因为所有的书都是堆成一摞的，所以每次读某本书之前小明都需要先将这本书上面所有的书搬开，拿出这本书，再将搬开的书按原顺序放回去，消耗体力为搬开书的重量之和，读完这本书后将其放在这摞书的最上面。

小明想知道这 $n$ 本书以怎样的初始顺序放置，所搬书消耗总体力最小。

## 样例 #1

### 输入

```
3 5
1 2 3
1 3 2 3 1
```

### 输出

```
12
```

# 题解

## 作者：一叶知秋。 (赞：7)

### 今天模拟赛第二题，感觉根本没有紫题的难度。

这题需要一些神秘的感觉

思路，**第一次看书的时间**的就是初始化序列

有同学问：没出现怎么办？

直接压在底下（反正不需要），代码中直接跳过。

证明：~~没有~~

因为每次看完的书都必须放在顶端，每一次取书都必须承受之前看过的书的质量，因此应该按照书第一次出现的顺序来摆放，假设看书的顺序是1 2书的摆放位置是2 1就需要额外承受多一次w[2]的质量。

所以是以贪心为代码思路写出的。

如何发现的：

样例：

3 5

1 2 3

1 3 2 3 1

我将样例改为

3 5

3 2 1

1 3 2 3 1

却发现答案一样。

所以，正解一定跟重量没啥关系。

最后推出。

```cpp
#include<cstdio>
inline int read(){//快读
	int r=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		r=r*10+c-'0';
		c=getchar();
	}
	return r*f;
}
inline int min(int a,int b){
	if(a<b)return a;
	return b;
}
int a[10001],b[10001],xl[500001];
bool v[10001];
int main(){
	freopen("eromanga.in","r",stdin);
	freopen("eromanga.out","w",stdout);
	int ans=0,n=read(),m=read(),i,j,k;
	for(i=1;i<=n;i++)a[i]=read();
	for(i=1;i<=m;i++)b[i]=read();
	i=0;
	k=0;
	while(i<=m){//构造序列
		i++;
		if(v[b[i]])continue;
		while(b[i]==b[i-1])i++;
		xl[++k]=b[i];
		v[b[i]]=true;
	}
	k--;
	for(i=1;i<=k/2;i++){//反着来
		int c=xl[i];
		xl[i]=xl[k-i+1];
		xl[k-i+1]=c;
	}
	for(i=1;i<=m;i++){
		int s=0;
		for(j=k;j>=1;j--){//求第i次阅读的重量
			if(b[i]==xl[j])break;
			s+=a[xl[j]];
		}
		xl[++k]=xl[j];//划重点
		xl[j]=0;//划重点
		ans+=s;
	}
	printf("%d",ans);
	return 0;
}
```

问题来了：为什么反着来？

answer：因为要放上来，所以直接反着加，并将原本位置清0

复杂度：O(n(n+m))=O(n^2)

---

## 作者：LesterYu (赞：4)

把书按照拿的顺序从上往下排，这个大家应该都想得到，关键是怎么快速求出答案。这里提供一种思维难度相对较低的解法：开四个数组，分别存储书的重量，每次取的书，书的堆放顺序和每本书的位置。每一次取书后，把取的那本书放到序列顶部，然后将答案加上上边书的总重。

代码如下——
```
#include<cstdio>
int n,m,ans;//scan&print
int w[501];//weight
int t[1001];//the book chosen each time
int d[1001];//the order
int l[501];//the location
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=m;i++){
		scanf("%d",&t[i]);
		if(!l[t[i]]){//如果之前没有被选中过，则当作它在当前序列的底部 
			for(int j=1;j<i;j++) ans+=d[j];
			//ans加上序列中所有书的重量 
			d[i]=w[t[i]],l[t[i]]=i;//放到顶部 
			continue;
		}
		for(int j=l[t[i]]+1;j<i;j++) ans+=d[j];
		//如果之前被选中过，则把它拿上来，ans加上它上面书的重量 
		d[l[t[i]]]=0,d[i]=w[t[i]],l[t[i]]=i;//放到顶部 
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Luckies (赞：2)

这一题是一道比较复杂的贪心(~~对于本蒟蒻来说~~)

假如两本书 $a$ 和 $b$，先看 $a$ 再看 $b$，那么我们开始的时候就把 $a$ 放在上面。

这样的话，我们看 $a$ 时就不需要搬动 $b$，看 $b$ 的时候会搬动 $a$。

而一开始如果把放在上面，看 $a$ 的时候需要搬动 $b$，看 $b$ 的时候需要搬动 $a$ ，就比一开始的 $a$ 放在上面多搬了。

将两本书推到更多也是同样的道理，先看的书放在上面，后看的书放下面。

看相同的书的时候，需要搬动的时两本书之间的所有书，因此需要倒序枚举之前的书。

### 最后的代码


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int n, m, w[N], a[N], ans;//n,m,w[]意义请看题目，a[]为要看的书，ans为看所有书需要的最少体力
bool vis[N];//vis数组用来标记
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> w[i];//输入每本书的重量，需要的体力
	for (int i = 1; i <= m; i++)
	{
		cin >> a[i];//输入要看的书
		memset(vis, 0, sizeof(vis));//对于每次阅读书，都要重新统计上面的所有书的总重量
		int sum = 0;
		for (int j = i - 1; j >= 1; j--)//倒序枚举之前看过的书
		{
			if (a[j] == a[i])//如果之前看过，那么a[j]前面的书就不需要搬动
				break;
			if (!vis[a[j]])//重复的书只统计一次重量
			{
				sum += w[a[j]];
				vis[a[j]] = true;//标记这本书已经统计过了，后面不计算重量
			}
		}
		ans += sum;//需要的体力加到总体力里面去
	}
	cout << ans;//输出总体力
	return 0;
}
```

---

## 作者：A_better_world (赞：1)

题目大意：

有 $n$ 本书，编号为 1 到 $n$，每一本书的重量为 $w_i$，这堆书竖直堆在一起

现在有 $m$ 天，第 $i$ 天会从中拿出编号为 $day_i$ 的书看，代价是  $day_i$ 上面的书的总重量，书一天看完，看完后放在最上面。

问题：最开始的时候你按照什么顺序放书，会让你这 $m$ 天要搬的书的总重量最小。

这道题的思路首先就应该想到是贪心。

贪心策略：

加入两本书 $a$ 和 $b$，先看 $a$ 再看 $b$，那么我们开始的时候就把 $a$ 放在上面，这样的话，我们看 $a$ 的时候就不需要搬动 $b$，看 $b$ 的时候就会搬动 $a$。而一开始的时候就把 $b$ 放在上面，看 $a$ 时要搬动 $b$，看 $b$ 时要搬动 $a$，就比开始 $a$ 放在上面多搬了。

所以我们就可以写出核心代码




```c
for(int i = 1; i <= m; i++)
{
    a[i] = read();
    memset(vis, 0, sizeof(vis)); // 清空。
    sum = 0;
    for(int j = i - 1; j >= 1; j--) // 计算前面所有数的 总重量。
     {
    	if(a[j] == a[i])
                break;
         if(vis[a[j]] == false) // 重复的数值统计一次。
         {
            sum += w[a[j]];
            vis[a[j]] = true; // 标记这本书已经统计，不再做统计。
          }
      }
     ans += sum; // 需要的体力加到总体力里去。
}
```
代码实现

```c
#include<bits/stdc++.h>
using namespace std;
int read(void) // 快读。
{
    char c = getchar();
    int x = 0, f = 1;
    while(c < '0' || c > '9'){ if(c == '-') f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int n, m, w[1005], a[1005];
bool vis[1005];
int main()
{
    n = read(), m = read();
    for(int i = 1; i <= n; i++)
    {
        w[i] = read(); // 输入一本书的重量，需要的 体力。
    }
    int sum = 0, ans = 0; // ans：看所有书需要的最少体力。
    for(int i = 1; i <= m; i++)
    {
        a[i] = read();
        memset(vis, 0, sizeof(vis)); // 清空。
        sum = 0;
        for(int j = i - 1; j >= 1; j--) // 计算前面所有数的 总重量。
        {
            if(a[j] == a[i])
                break;
            if(vis[a[j]] == false) // 重复的数值统计一次。
            {
                sum += w[a[j]];
                vis[a[j]] = true; // 标记这本书已经统计，不再做统计。
            }
        }
        ans += sum; // 需要的体力加到总体力里去。
    }
    cout << ans;
    return 0;
}

```

---

## 作者：墨舞灵纯 (赞：1)

    我的第七篇题解。（请大佬们多指教。当然，如果有看不懂的地方欢迎和我私信交流。）
    这题还没有人写题解，所以我就来写一下。这题主要思路是贪心。设当前读书序列是(x1,x2),如果摆放序列是(x1,x2),则ans=w[x1],如果摆放序列是(x2,x1),则ans=w[x1]+w[x2]，很明显前者优于后者。这个就是本题的贪心思想。这是两本书的特殊情况，推广到3,4,……n本书，其效果是一样的。下面附上代码。
```
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1005;
int n,m,a[N],b[N],ans;
bool q[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=m;i++){
		memset(q,false,sizeof(q));
		for(int j=i-1;j;j--){
			if(b[i]==b[j]) break;
			if(!q[b[j]])
				q[b[j]]=true,ans+=a[b[j]];
                //实现贪心思想的核心代码，对于某本书，我们只需累积其上面的，然后标记重复即可。
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：watermouthhang (赞：0)

原题链接：[New Year Book Reading](https://www.luogu.com.cn/problem/CF500C)
# 题目大意
一个栈 $S$ ，栈中存在 $N$ 本书，从 $S$ 中取 $M$ 次书，每次取书 $A$ 有 $3$ 部分：
1. 将栈中 $A$ 以上的书拿走,设 $i$ 为 $A$ 之上的书，则花费的价值 $sum$ 为：
$$sum\eqcirc\sum w[i] $$
2. 拿走 $A$ ，并把之前被拿走的书原样放回（无花费）。
3. 将 $A$ 重新放回栈顶（无花费）。

最后的答案
$$ans\eqcirc\sum sum$$
已知 $n$ , $m$ ,数组 $w$ ，和取书的操作数组 $d$ ，求在栈的初始排列最合理时， $ans$ 的最小值。
# 算法
我们用贪心的思路考虑。不妨设前后两本书先后为 $a$ , $b$ （且 $a$ 第一次出现要比 $b$ 第一次出现早）。
- 当 $a$ 在 $b$ 前时， $a$ 需要花费 $w[a]+q$ 的代价（ $q$ 为常数）
- 当 $a$ 在 $b$ 后时， $a$ 需要花费 $w[a]+w[b]+q$ 的代价（ $q$ 为常数）

所以，对于 $a,b$ 使得 $a$ 第一次出现要比 $b$ 第一次出现早，$a$ 应该排在 $b$ 的前面。

同时，因为任意两个数都要比对一次，造成的结果本质就是将其冒泡排序了一遍，所以直接排序即可。

用易于理解的话来说，就是按照第一次出现的顺序排序，来作为初始的栈。

对于没有在数组 $d$ 中出现的书，将其放在栈的底部，忽视即可。

在初始栈算好之后，模拟即可。
# 代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
#include <cstring>
#include <string>
#include <cmath>
#include <map>
#include <cstdint>
//头文件部分不必在意
using namespace std;

int n,m;
int w[510],d[1010];//如题
int fst[510],top=0;//记录第一次出现的位置
bool tong[510];//辅助判断
int rtans()//返回答案
{
	int ans=0;
	for(int i=1;i<=m;++i)
	{
		int tmp=114514,sum=0;//喵~
		for(int j=1;j<=top;++j)//传送带式移动
		{
			if(fst[j]==d[i])
			{
				if(j==1)//特判，防止bug
				{
					break;
				}
				fst[1]=fst[j];
				fst[j]=tmp;
				break;
			}
			else
			{
				sum+=w[fst[j]];
				swap(tmp,fst[j]);
			}
		}
		ans+=sum;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&w[i]);
	}
	for(int i=1;i<=m;++i)
	{
		scanf("%d",&d[i]);
		if(!tong[d[i]])
		{
			tong[d[i]]=1;
			fst[++top]=d[i];
		}//判断第一次出现的位置
	}
	printf("%d\n",rtans());//输出答案
	return 0;
}
```

# ~~另~~
~~这道题是橙题。这道题是橙题？震惊！~~

---

