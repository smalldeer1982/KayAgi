# [ABC061C] Big Array

## 题目描述

## 题目翻译
有一个数组S，一开始是空的。接下来对这个数组进行N次插入操作.
第ii次操作会向数组中加入$b_i$
 个整数$a_i$
 ，然后将整个数组从小到大排一次序。
求N次操作后, 数组中的第K个数。
例如S=\{1,2,2,3,3,3\}时, 从小到大排序后第4个数是3。

## 说明/提示

*  	1≦N≦$10^5$ 
*  	1≦$a_i$ ,$b_i$ ≦$10^5$ 
*  	1≦K≦$b_1$+...+$b_n$
*	所有输入值都是整数。
------------
题目翻译者UID：370640

## 样例 #1

### 输入

```
3 4
1 1
2 2
3 3```

### 输出

```
3```

## 样例 #2

### 输入

```
10 500000
1 100000
1 100000
1 100000
1 100000
1 100000
100000 100000
100000 100000
100000 100000
100000 100000
100000 100000```

### 输出

```
1```

# 题解

## 作者：Anaxagoras (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/AT2561)

### 0x01 思路

我们可以用一个数组来存数字 $a$ 出现了几次，然后用 $k$ 减去每个数的出现次数，当 $k\le0$ 时，就输出下标。

注意：不开 long long 见祖宗（否则 WA 在第四个测试点）！

### 0x02 AC Code
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,k,a,b,num;
int t[100005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;
		t[a]+=b;
	}
	while(k>0)
	{
		++num;
		k-=t[num];
	}
	cout<<num<<'\n';
	return 0;
}
```

球球了，给个赞吧！

---

## 作者：沉石鱼惊旋 (赞：5)

### 题目翻译

$n$ 次操作，每次两个数 $a_i,b_i$，在一个初始为空的序列里插入 $b_i$ 个 $a_i$，操作结束后问第 $k$ 小是什么。

### 题目思路

类似于 [ABC247D](https://atcoder.jp/contests/abc247/tasks/abc247_d) 的写法，还是个弱化版。

我们不用真的插入 $b_i$ 个 $a_i$，只需记录 $b_i$ 有多少即可，因为很多的数都用不到。

这是很多个一添，同理，我们可以很多个一删。

所以我们用一个 `pair` 记录两个量，**数字**和**次数**。

然后按数字的大小排序，最后遍历数组，每次用 $k$ 减掉出现次数，如果此时 $k\leqslant0$，那么就输出当前数字。

注意，$k$ 最大可以为 $100000^2$，那么开好 `long long`。

我因为这个错了一次……

### AC 代码

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
vector<pair<ll,ll>>v;
int main()
{
	ll n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int a,b;
		cin>>a>>b;
		v.push_back(make_pair(a,b));//插入数字和次数
	}
	sort(v.begin(),v.end());//pair的排序默认先看first，也就是此题中的数字的大小
	for(int i=0;i<(int)v.size();i++)
	{
		k-=v[i].second;//减掉出现次数
		if(k<=0){cout<<v[i].first<<endl;return 0;}//<=0时，输出当前数字。
	}
	return 0;
}
```



---

## 作者：Grisses (赞：2)

[题面](https://www.luogu.com.cn/problem/AT2561)

我们可以用一个优先队列储存每一个区间的数值和长度，然后再求第 $k$ 位的值。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  struct node{
      long long int id,x;
      node(){}
      node(int a,int b){id=a,x=b;}
      bool operator<(const node &t)const{
          return id>t.id;
      }
  };
  priority_queue<node>q;
  long long int n,k,a,b;//不开long long见祖宗
  int main()
  {
      scanf("%lld%lld",&n,&k);
      for(int i=1;i<=n;i++)scanf("%lld%lld",&a,&b),q.push(node(a,b));
      while(k>q.top().x)k-=q.top().x,q.pop();
      printf("%lld",q.top().id);
      return 0;
  }
```

---

## 作者：Obviathy (赞：2)

## 解题思路
其实这道题思路很简单，就是将这些操作排个序，现进行插入的数字小的操作，每执行一次操作，就用 $k$ 减去插入的数字的个数，来统计距离插入第 $k$ 小的数字还差多少个数。一旦发现 $k \le 0$，说明已经插入了第 $k$ 小的数了，直接输出下标即可。
### 坑点：
- $k$ 最大是 $10^{10}$ 所以要开 long long
- AT Coder 的题目最后要输出换行
## code：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define a first 
#define b second 
const int N = 1e5+1;
pair<int,int>p[N];
long long n,k;
int main(){
	cin >> n >> k;
	for(int i = 0;i < n;i++)cin >> p[i].a >> p[i].b;
	sort(p,p+n);
	for(int i = 0;i < n;i++){
		k -= p[i].b;
		if(k <= 0){
			cout<<p[i].a<<endl;
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：MrCR7 (赞：2)

## 思路分析
这道题是一道比较简单的模拟题。

但是我们还是不能够直接去把值放到数组里再排序，不然肯定会超时。

我们可以做一个桶 $t$，然后每次不断地输入 $a$ 与 $b$，在数组 $t$ 里存放数字 $a$ 的数量，到最后再用 $k$ 去减每一个 $a$ 的数量，当 $k \leq 0$ 的时候，输出当前的下标就好啦。

注意：不开 $\texttt{long long}$ 不见宗！

## Ac Code
```cpp
#include <cstdio>
#include <cstring>
long long t[100003];//创建一个桶。
int main (){
	memset (t, 0, sizeof (t));//先把桶清零。
	long long n, k;
	scanf("%lld%lld", &n, &k);//如题意。
	for (int i=1; i<=n; i++){
		long long a,b;
		scanf ("%lld%lld", &a, &b);//读入a,b。
		t[a]+=b;//加a的数量。
	}
	long long ans=0;//最终的下标。
	while (k>0){//只要k>0。
		ans++;//因为刚开始ans是0，所以先把ans+1，后面也是一样的。
		k-=t[ans];//减掉t[ans]的值。
	}
	printf ("%lld\n", ans);//求出第k小的数，输出。
	return 0; 
}
```
完结撒花qwq~

看了这么久，点个赞再走吧~

---

## 作者：makerlife (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT2561) | [AT 原题传送门](https://atcoder.jp/contests/abc061/tasks/abc061_c)

## 思路

**桶的思想。**

用数组 $t$ 存储 $a$ 出现的次数，然后循环，用 $k$ 减每个数出现的次数，看在哪个数时满足 $k \leq 0$ 的条件，直接输出这个数的下标即可。

**注意不开 $\texttt{long long}$ 见祖宗**

## 代码

```cpp
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
ll n,k,a,b;
ll t[100010],ans=0;
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a,&b);
		t[a]+=b;//t为桶，增加a的个数
	}
	while(k>0)//当k<=0时跳出循环
	{
		k-=t[++ans];//每次k自减t[++ans]
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：wbs200 (赞：1)

此题又是一个很好的 STL 模板题，可以当做[P1097 [NOIP2007 提高组] 统计数字](https://www.luogu.com.cn/problem/P1097)的后续练习。

对于此题来讲，其实如果想直接求第 $K$ 小的数的话有些麻烦，并且很容易出错。对此我们可以采用一种桶排序的思路。我们使用 STL 中的 map，将数据全部加入 map 容器后统一使用 auto 将 map 扫一遍，将输入的 $K$ 不断减掉即可。
```cpp
#include <iostream>
#include <map>
using namespace std;

#define int long long
map<int, int> mp;

signed main()
{
    int n;
    long long k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
    	int a, b;
    	cin >> a >> b;
    	mp[a] += b;
    }
    for (auto kv: mp)
    {
    	k -= kv.second;
    	if (k <= 0)
    	{
    		cout << kv.first << endl;
    		break;
    	}
    }
    return 0;
}
```


---

## 作者：DeepWinter (赞：0)

## 题目描述

给定一个空集合 $S$，一共 $n$ 次操作，每次操作给定 $a_i$ 和 $b_i$，向集合内添加 $b_i$ 个数 $a_i$，求添加后集合 $S$ 从小到大排的第 $k$ 个数。

## 思路

#### 1. 排序

首先想到这种做法，将 $S$ 集合内的数排序后输出第 $k$ 个数，但显然不可行，因为 $\sum\limits_{i=1}^nb_i$ 可能会很大，会超时。

#### 2.桶

用一个桶来记录每个数出现了多少次，然后将桶从头开始扫一遍，每次将 $k$ 减去扫到的数出现的次数，$k\leq0$ 时结束，输出此时扫到的数即可。这种方法时可行的。

##  Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define sc scanf
#define pr printf
#define int long long//注意要开long long，每个数可能出现很多次
#define cc cin
#define ccc cout
#define fr freopen
inline void in(int &x)//快读
{
	char c=getchar(), f=1;
	while ((c<'0'||c>'9')&&c!='-')
		c=getchar();
	if (c=='-')
		c=getchar(),f=-1;
	for (x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^'0');
	x*=f;
}
ll a[100005];//桶，只需要开到100005，初值全0
signed main()
{
	int n,k;
	in(n),in(k);//读入
	for(int i=1;i<=n;i++) {
		int x,y;
		in(x),in(y);//读入
		a[x]+=y;//将桶的x项加上y，不能写=，因为不一定只加一次。
	}
	int b=1;//初始值
	while(k>0) k-=a[b++];//循环，k小于等于0时结束，每次减去桶里的值，b++。
	cout<<b-1<<endl;//输出，注意b要减1，因为之前减的时候 b++ 了，所以输出时要-1.
	return 0;//完结撒花
}

```


---

## 作者：_Kouki_ (赞：0)


**思路详见代码。**    
主要思想**桶**。
用数组 $ t $ 存储 $ a $ 出现的次数，然后循环用 $ k $ 减每个数出现的次数（$t_i$），看在哪个数时满足 $ k \leq 0 $ 的条件，就输出这个数的下标即可。
## Code:
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long n,k;//插入次数，询问元素 
long long a,b;//插入时候的a要插入b次 
long long now;//当前答案 
map<int,long long>t;//STL 就是桶
void IN()//读入 本人的一种码风吧。 
{
	scanf("%lld%lld",&n,&k);//插入次数，询问元素
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a,&b);//插入时候的a要插入b次 
		t[a]+=b;//此时a的个数加b个 
	}
} 
int main()
{
	IN(); 
	while(k>0)//满足运行 
	{
		k-=t[++now]; //k每次减去最小元素的个数 
	}
	printf("%lld\n",now);//完结撒flowers yeah!! 
	return 0;
}


```


---

