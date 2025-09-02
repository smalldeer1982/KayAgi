# Andryusha and Socks

## 题目描述

Andryusha is an orderly boy and likes to keep things in their place.

Today he faced a problem to put his socks in the wardrobe. He has $ n $ distinct pairs of socks which are initially in a bag. The pairs are numbered from $ 1 $ to $ n $ . Andryusha wants to put paired socks together and put them in the wardrobe. He takes the socks one by one from the bag, and for each sock he looks whether the pair of this sock has been already took out of the bag, or not. If not (that means the pair of this sock is still in the bag), he puts the current socks on the table in front of him. Otherwise, he puts both socks from the pair to the wardrobe.

Andryusha remembers the order in which he took the socks from the bag. Can you tell him what is the maximum number of socks that were on the table at the same time?

## 说明/提示

In the first example Andryusha took a sock from the first pair and put it on the table. Then he took the next sock which is from the first pair as well, so he immediately puts both socks to the wardrobe. Thus, at most one sock was on the table at the same time.

In the second example Andryusha behaved as follows:

- Initially the table was empty, he took out a sock from pair $ 2 $ and put it on the table.
- Sock $ (2) $ was on the table. Andryusha took out a sock from pair $ 1 $ and put it on the table.
- Socks $ (1,2) $ were on the table. Andryusha took out a sock from pair $ 1 $ , and put this pair into the wardrobe.
- Sock $ (2) $ was on the table. Andryusha took out a sock from pair $ 3 $ and put it on the table.
- Socks $ (2,3) $ were on the table. Andryusha took out a sock from pair $ 2 $ , and put this pair into the wardrobe.
- Sock $ (3) $ was on the table. Andryusha took out a sock from pair $ 3 $ and put this pair into the wardrobe.

 Thus, at most two socks were on the table at the same time.

## 样例 #1

### 输入

```
1
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
2 1 1 3 2 3
```

### 输出

```
2
```

# 题解

## 作者：songxiao (赞：3)

## 法一（朴素）

按题目要求模拟。首先循环 $2\times n$
 次，读入袜子并记录后，桌子上多一只袜子。**与此同时**（但总有得有个先后）进行配对，如果配对成功放入衣柜，桌子上又少了两只袜子。上两步相当于同时，所以执行完后再统一更新答案。相当于有两种情况：
 
 1. 配对不成，桌子上多一只袜子
 2. 配对成功，桌子上多一只袜子**同时**又少掉两只
 
 至于标记袜子号码，我们发现 $x_i$ 的取值范围不会大于十万，我们就可以开一个数组 `a[100005]`，每种袜子对应一个下标。
 
**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],cnt,ans;
int main()
{
	cin>>n;
	for(int i=1;i<=2*n;i++)	//别忘了乘以2，因为n双有2*n只
	{
		int x;
		cin>>x;
		a[x]++;		//发现一只袜子，桌上就多一只相应种类的袜子
		cnt++;		//桌子上总袜子数增加（第一种）
		if(a[x]==2)	//同种袜子凑够两只，放入衣柜（第二种）
			cnt-=2;	//桌子上少掉两只
		ans=max(ans,cnt);//更新答案，取最多的
	}
	cout<<ans;
	return 0;
}

```

## 法二（简化）

法二 _貌似_ 简化了一些，把前面分析的第二种情况**多一只又少两只**改为了**少一只**，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],cnt,ans;
int main()
{
	cin>>n;
	for(int i=1;i<=2*n;i++)	//别忘了乘以2，因为n双有2*n只
	{
		int x;
		cin>>x;
		a[x]++;		//发现一只袜子，桌上就多一只相应种类的袜子
		if(a[x]==2)	//第二种
			cnt--;	//桌子上共少一只
		else
			cnt++;	//第一种
		ans=max(ans,cnt);//更新答案，取最多的
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：qhztz (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF780A)
## 思路：
用 n 记录下每种袜子出现的次数，用 ans 记录桌上袜子的个数，每次判断如果没有配对的袜子那么桌子上的袜子加 1，否则减 1，用 maxn 记录一下最大值，最后输出即可。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,b,ans,maxn,a[100001];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++){
		scanf("%d",&b);
		a[b]++;
		if(a[b]==2) maxn--;//如果成双就配对，桌上的袜子的个数减 1
		else maxn++;//否则桌子上的袜子个数加 1 
		ans=max(ans,maxn);//取最大值 
	}
	printf("%d\n",ans);//输出 
	return 0;
}
```


---

## 作者：lxgw (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/solution/CF780A)
## 题意
有 2n 只袜子，编号为 1~n ,把它们依次拿出来，如果能凑够了一双袜子，就把那一双拿走，给出拿出袜子的顺序，问桌子上最多有几只袜子。
## 思路
用一个数组 sum 来存储袜子的出现次数，其中 $sum_i$ 表示 i 号袜子出现的次数，如果 $sum_i=2$ 即编号为 i 的袜子有一双了，总数就减2（把一双拿走），否则就加1。
## 代码
```cpp
#include<iostream>
using namespace std;
int n,a,ans,cnt;//ans存储最终答案，cnt存储每一次操作后的值
int sum[100010];//存储袜子出现次数
int main()
{
	cin>>n;
	for(int i=1;i<=2*n;i++)
	{
		cin>>a,sum[a]++;//编号为a的袜子的出现次数加1
		cnt++;//最大值加1
		if(sum[a]==2) cnt-=2;//如果袜子已经凑够了一双就拿走（总数减2）
		ans=max(ans,cnt);//取一遍最大值
	}
	cout<<ans;//输出最终答案
	return 0;
}
```

完结撒花~

谢谢 qwq

---

## 作者：锦瑟，华年 (赞：1)

水题评分害死人，暴力模拟没商量！

……话说这题为什么是绿题，而且还是一道无敌暴力模拟的水题？？？

好了，废话不多说，直接开讲。对于这题，只需要进行一个for循环，边读边做，先开一个桶，表示编号为$i$的袜子目前的数量，读入，对桶中对应的地方加上1，再判断，如果刚才加的编号的袜子等于二，那么就把这两个袜子去掉。当然了，我们还要开两个变量，ans和max，ans表示的是目前桌子上的袜子数，max表示的是桌子上保存的最大袜子数，最后输出max。

好了，来一个直接点的，上代码：

	#include<stdio.h>
	using namespace std;
	int a[100005];//桶
	int main(){
		int n,i;
		scanf("%d",&n);
		int ans=0,max=0;//ans表示的是目前桌子上的袜子数，max表示的是桌子上保存的最大袜子数
		for(i=1;i<=n*2;i++){
			int k;
			scanf("%d",&k);//边读边做
			a[k]++;
			if(a[k]==2)ans--;//改变ans的数值
			else ans++;
			if(ans>max)max=ans;//更新答案
		}
		printf("%d",max);//输出
		return 0;
	}
最后我还想说一句，这妥妥的红题啊，为什么是绿题？？？
    
好了废话不多说，这篇题解到此结束，谢谢大家观看，拜拜~~（^_^）

---

## 作者：_Agave_ (赞：0)

[题目](https://www.luogu.com.cn/problem/CF780A)

这道题它让你求桌子上袜子数最多的时候。

我们可以用 $10000$ 个桶，记录每个时间第几种袜子的数量。

用  $sum$  变量记录现在桌子上袜子的数量。

用 $ans$ 记录最终答案

如果桌子上有这种袜子，就连着这一支袜子一起直接扔掉，不会先放到桌子上

否则就让对应这种袜子的数量  $+1$。

时间复杂度只有  $O(n)$。


如果我们找到一个时刻的袜子数量比 $ans$ 大，那
么就用  $sum$ 的值不断更新   $ans$。


```cpp
#include <bits/stdc++.h>
#include <vector>
#include <string>
using namespace std;
int num[100005],n,ans,sum;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++){
		int x;
		scanf("%d",&x);
		if(num[x]){
			sum--;
			num[x]--;//将袜子扔掉，此时 sum 数量减少，所以不用更新
		}else{
			num[x]++;
			sum++;//将袜子放在桌子上
			ans=max(ans,sum);//更新答案
		}
	}
	printf("%d",ans);//输出答案
	return 0;
}

```


---

## 作者：kdy20100729 (赞：0)

真不知道为啥是绿题

### 思路  
模拟。用 $vis$ 数组记录下每种袜子出现的次数，用 $maxi$ 记录桌上袜子的个数，每次判断如果没有配对的袜子那么桌子上的袜子加 $1$，否则减 $1$，用 $ans$ 记录一下最大值，最后输出 $ans$ 即可。  
注意：$vis$ 数组至少要开 $10^5+1$。

### Code:  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,ans,maxi;
bool vis[100005];
signed main()
{
    cin >> n;
    for(int i=1; i<=2*n; i++)
    {
        cin >> x;
        if (vis[x]==false)
        {
            maxi++;
            vis[x]=true;
        }
        else
            maxi--;//因为我并不是每拿一双袜子就加1，所以 maxi 减一即可
        ans=max(ans,maxi);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：shenmadongdong (赞：0)

记录下每种袜子出现的次数，如果没有配对的袜子那么桌子上的袜子加1，否则减1，记录一下最大值即可。

代码：
```
var cx,n,i,s,max:longint;
    a:array [1..100000] of longint;
begin
  read(n);
  for i:=1 to n do 
    begin
      read(cx);
      inc(a[cx]);
      if a[cx]=2 then begin a[cx]:=0; s:=s-2; end;
      inc(s);
      if s>max then max:=s;
    end;
  writeln(max);
end.
```

---

## 作者：yuangq (赞：0)

这题只需模拟即可了

详情请见代码

~~~
#include<bits/stdc++.h>
using namespace std;
int num[100005];//哈希大法 
int main()
{
	int n;
	cin>>n;
	int s=0,maxs=-1;
	for(int i=0;i<2*n;i++)
	{
		int a;//输入 
		cin>>a;
		s++;//桌上多了一张牌 
		num[a]++;//编号为a的牌多了一张 
		if(num[a]==2)//如果同样的牌有两张了 
		{
			num[a]=0;//将这两张牌去除 
			s-=2;//从桌子上拿掉了两张牌 
		}
		maxs=max(maxs,s);//每轮求最大 
	}
	cout<<maxs;
	return 0;
}

~~~

---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF780A)

~~好久没水题解了，来水一发~~

~~恶评没商量~~

# 思路

暴力模拟

记录下每种袜子出现的次数，如果没有配对的袜子那么桌子上的袜子$+1$，否则$-1$，记录一下最大值就是答案。

# 废话不多说，上代码

```cpp
#include<bits/stdc++.h>//懒人专用头文件
using namespace std;
long long t,n,ans,maxm;
/*
t为题面中的n，n为题面中的x（不要问我为什么错位了）
ans是答案
maxm是当前最大值
*/
long long a[100005];
//a数组用来记录每种袜子出现的个数
int main(){
    cin>>t;//输入
    for(int i=1;i<=2*t;i++){
        cin>>n;//输入
        a[n]++;//对应的袜子总类的数量+1
        if(a[n]==2){//当出现一双相同的袜子
            maxm--;//取走，maxm-1
        }else{//没有一双相同的袜子
            maxm++;//不动，maxm+1
        }
    ans=max(ans,maxm);//取最大值
    }
    cout<<ans<<endl;//输出
    return 0;//好习惯
}
```
代码看完了，你学废了吗？

---

## 作者：tribool4_in (赞：0)

简单模拟，用一个数组 ```t``` 来表示每类袜子目前的个数，然后实时更新当前袜子个数 ```nows``` 和最大值 ```maxs``` 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, ai, maxs, nows, t[N];
int main() {
	scanf("%d", &n); n *= 2;
	for(int i = 1; i <= n; i++){
		scanf("%d", &ai);
		t[ai]++;
		if (t[ai] == 2) nows--;
		else nows++;
		maxs = max(maxs, nows);
	}
	printf("%d\n", maxs);
	return 0;
}
```

~~最后说句闲话：这评分是哪位管理给的，给我出来~~

---

## 作者：yf最qhhh (赞：0)

一道模拟的题。

思路：边输入边拿个数组来存，如果出现了2就意味着有袜子凑齐了一对，就要放进柜子，所以 ans-- ，如果没有那桌子上又多一只袜子，ans++。最后因为要找最大值，所以用 max 统计一下答案。 

~~（好像没有需要特别注意的地方？）~~

那么上代码！
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int arr[200010];
main(void){
	int ans=0,mmax=INT_MIN,n,cmp;
	scanf("%lld",&n);
	for(int i=1;i<=2*n;i++){
		scanf("%lld",&cmp);
		++arr[cmp];
		if(arr[cmp]==2){
			ans--;//凑齐了一双就--
		}
		else{
			ans++;//没有就++
		}
		mmax=max(mmax,ans);//找最大值
	}
	printf("%lld",mmax); 
	return 0;
}

```


---

## 作者：_Scaley (赞：0)

毫无疑问这是一道模拟题

## 题目大概：

有一个长度为 n 的数列，并且其中有 n / 2 种数，

每种数在这个长度为 n 的数列出现两次，

将相同数按照顺序配对，配对成功后将两个数从扫描过的数列中去除，

问：这个按顺序扫描这个数列时，被扫描过的数列中最多有多少个数？

## 解法分析：

可以先把整个数列用数组存储下来，然后从头到尾枚举一遍，

用 js 存储当前被枚举过的数有几个，用 maxn 存储 js 的最大值，

每当被枚举的数出现第二遍的时候，js 减二，其余时候 js 加一。

用 maxn 维护 js 的最大值，最后把 maxn 输出即可。

## 代码实现：

```
#include <iostream>
#include <cstdio>
#include <map>
#define LL long long
#define MAXN 100001
#define F1(i, a, b) for (int i = a; i <= b; ++i)
#define F2(i, a ,b) for (int i = a; i >= b; --i)
using namespace std;

int a[200001]; // 用数组存储数列
int n;
map<int, int> book; // 用 map 记录数是否出现过

int main() {
	int js = 0, maxn = 0;
	scanf("%d", &n);
	F1(i, 1, 2 * n) scanf("%d", &a[i]);
	F1(i, 1, 2 * n) {
		++js; // 先对数字计数
		if (book[a[i]] == 1) js -= 2; // 如果这个数在之前出现过，js 减二
		else book[a[i]] = 1; // 否则记录此数出现过
		if (js > maxn) maxn = js; // 维护最大值
	}
	printf("%d\n", maxn); // 输出最大值
	return 0;
}

```

---

## 作者：__Unknown (赞：0)

### ~~又是暴力题解……~~
#### 嗯……我们先开一个长为n的book数组来记录每一组袜子的第一只是否已找到，没找到就book[i]++，并且桌子上的种类数++，更新ans若已经找到就种类数--，循环完2n次就可以啦
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int book[300005],sum,ans,a[300005],n;
int main()
{
	cin>>n;int iop;
	for(int i=1;i<=2*n;i++){
		cin>>iop;
		if(book[iop]){
			sum--;
			book[iop]=0;
		}
		else{
			sum++;
			book[iop]=1;
			ans=max(sum,ans);
		}
	}
	cout<<ans<<endl;
	return 0;
 } 
```


---

