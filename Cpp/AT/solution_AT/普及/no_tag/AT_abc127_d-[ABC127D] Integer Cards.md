# [ABC127D] Integer Cards

## 题目描述

有一个长度为 $n$ 的序列 $A_{1},A_{2},\cdots,A_{n} $

你可以对这个序列依次进行 $m$ 次操作，第 $ i$ 次操作中，你可以选择至多 $B_{i}$ 个数（可以一个都不选），然后将这些数变成 $C_{i}$

问进行这 $m$ 次操作后，这个序列所有元素之和可能的最大值是多少

## 说明/提示

$1 \le n,m \le 10^5,1 \le A_{i},C{i} \le 10^9,1 \le B_{i} \le n$

## 样例 #1

### 输入

```
3 2
5 1 4
2 3
1 5```

### 输出

```
14```

## 样例 #2

### 输入

```
10 3
1 8 5 7 100 4 52 33 13 5
3 10
4 30
1 4```

### 输出

```
338```

## 样例 #3

### 输入

```
3 2
100 100 100
3 99
3 99```

### 输出

```
300```

## 样例 #4

### 输入

```
11 3
1 1 1 1 1 1 1 1 1 1 1
3 1000000000
4 1000000000
3 1000000000```

### 输出

```
10000000001```

# 题解

## 作者：水星湖 (赞：10)

一个教练讲的很厉害的做法。

每次操作不进行实际的修改，而是看做多了 $B_i$ 个 $C_i$。排序后从大到小贪心选 $n$ 个即可。

注意不可以一张一张存，要用结构体存每一次操作。

很久前写的[代码](https://www.luogu.com.cn/paste/hwedipsl)，很丑。

---

## 作者：Rain_chr (赞：5)

### 题目分析

 **first 定理**

**将小数调大的收益必定比将大数调大的收益。**

证明：

设未知数 $a,b$ 且 $a>b$ ，同时修改后的数为 $x$

则修改 $a$ 的收益为 $x-a$ ,修改 $b$ 的收益为 $x-b$

比较 $x-a$ 和 $x-b$

$ \because a>b$

$ \therefore x-a<x-b $


**second 做法**

用堆动态排序序列 $A$ ,然后不断的取最小值，判断是否大于当前修改的值，如果大于则修改，否则就退出循环（因为后面的数都比这一个数要大，再去修改没意义）。

时间复杂度： $O(\sum b_i)$

显然过不了，考虑优化。

**third 优化**

我们可以先奖修改操作按 $c_i$ 从大到小排一边序，这样就可以保证每一个数字都只会被修改一次（除第一次外，如果有比 $a_i$ 更大的 $c_i$ ，一定在前面修改过了）。

时间复杂度： $O(n\log{n})$

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x;
struct node
{
	int count,number;
}b[100010];
bool cmp(node x,node y)
{
	return x.number>y.number; 
}
priority_queue<int,vector<int>,greater<int> > q;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		q.push(x);
	}
	for(int i=1;i<=m;i++)
		scanf("%d%d",&b[i].count,&b[i].number);
	sort(b+1,b+1+m,cmp);	
	for(int i=1;i<=m;i++)
	{
		while(b[i].count)
		{
			int x=q.top();
			if(x>=b[i].number)
				break;
			q.pop();
			q.push(b[i].number);
			b[i].count--;
		}
	}
	long long ans=0;
	while(q.size())
	{
		ans+=q.top();
		q.pop();
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：SongShouqian (赞：4)

### 一、前言
经过3天的奋斗和18次提交，我终于 AC 了！为了庆祝自己 AC，我写了这篇题解。

这篇题解是这道题的第一篇题解，也是本蒟蒻的第一篇题解，如果写得不好请见谅，谢谢！

------------

### 二、题目分析
这道题的正确解法应该是这样的：我们每次要用 $C$ 数组中**最大的数字**去尽可能地变 $A$ 数组中**小的数字**，才能使每一次数字变化的收益最大。所以，我们可以在输入后将 $A$ 数组从小到大排序，将 $BC$ 数组（后来我将 $B$ 数组和 $C$ 数组合并成了一个结构体数组。）以 $C$ 为关键字从大到小排序，然后依次进行比较、替换，并计算总和。如果不算排序，该算法的时间复杂度为 $O(n)$。
具体实现方式见下一节。

------------

### 三、代码实现
在写这篇题解之前，我比较喜欢“**STL 大法**”，所以我很快用 multiset 写出了代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int>a;
multiset<int,greater<int> >bc; 
int main()
{
	int n,m,t,b,c;
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>t;
		a.insert(t);
	}
	for(int i=0;i<m;i++)
	{
		cin>>b>>c;
		while(b--)
		{
			bc.insert(c);
		}//添加b个c。
	}
	multiset<int>::iterator f,g;
	long long sum=0;
	int len=a.size();
	for(int i=0;i<len;i++)
	{
		f=a.begin();
		g=bc.begin();
		if(*f<*g)//如果bc中的数据比原先大，就替换。
		{
			bc.erase(g);
			sum+=*g;//sum加上新数据。
		}
		else//否则加上原数据。
		{
			sum+=*f;
		}
		a.erase(f);//以后这个数据就没用了，不如删掉，也方便后面的访问。
	}
	cout<<sum;
	return 0;
}
```
然后满怀信心地交上去——#7测试点 TLE……

几天后我终于恍然大悟：原来，multiset 每添加一个新的值就要排一次序，看起来 $O(n)$，其实爆炸！

所以我放弃了 STL，把 multiset 换成了数组，在输入后只统一排序一次，并且去掉了替换数据的部分，毕竟我们要的是总和，而不是所有替换后的值。另外，如果替换不成功，就可以直接跳出循环，因为 $A$ 数组中的数会越来越大，而 $BC$ 中 $C$ 的数会越来越小；不过如果这样，那我们需要在最后将未替换的数加到总和里面。

**AC code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100010];
struct node{
	long long k,v;//此处的k就是题目中的b，v就是c。
}bc[100010];
bool cmp(node a,node b)
{
	return a.v>b.v;
}
int main()
{
	long long n,m;
	cin>>n>>m;
	for(long long i=0;i<n;i++)
	{
		cin>>a[i];
	}
	sort(a,a+n);
	for(long long i=0;i<m;i++)
	{
		cin>>bc[i].k>>bc[i].v;
	}
	sort(bc,bc+m,cmp);
	long long f=0,g=0;//f用来记录第一个不需要替换的数字在数组中的下标，g则是用来遍历bc数组的下标变量。
	long long sum=0;
	if(m)
	{
		for(long long i=0;i<n;i++)
		{
			if(a[i]<bc[g].v)//如果可以替换：
			{
				sum+=(long long)bc[g].v;//总和加上新替换的值；
				bc[g].k--;//还可替换的个数-1。
				if(bc[g].k==0)//如果不能继续替换了：
				{
					g++;//遍历bc数组的下一个值。
					if(g==m)//如果没有下一个值了：
					{
						f=i+1;
						break;//(1)记录不需替换的数字下标并跳出循环。
					}
				}
			}
			else
			{
				f=i;
				break;//同(1)。
			}
			if(i==n-1)
			{
				f=n;//为了避免重复计算，和(1)做同样的处理。
			}
		}
	}
	for(long long i=f;i<n;i++)
	{
		sum+=(long long)a[i];//将没有被替换的数加到总和里。
	}
	cout<<sum;
	return 0;
}
```

------------

### 四、结语
如果有人想对这篇题解提建议和意见，可以在其他题解中告诉我，我会努力提升我的题解质量的。

#### 谢谢大家！

---

## 作者：00001A (赞：3)

# 思路
$a$ 用数组；$b$，$c$ 用结构体。

排序：$b$，$c$ 的结构体肯定是按照权值排序的，为什么呢？我们肯定希望数组里的数以小换大，所以最大的可交换的数应该**优先交换**。但是 $a$ 数组是从大到小还是从小到大呢？所以我用了两次排序，分别记录答案，并比大小。

（当然经过我不懈的尝试，是从小到大排序）展开讲讲为什么要从小到大排序：现在有一个数组：$1,2,3,4,5,6,7,8,9,10$；然后你有一个 $100$，现在想要求一个最大和。那么将 $100$ 替换成哪个数增加的值最多呢？所以优先较小数交换。


# AC 代码
```cpp
#include<bits/stdc++.h>//万能头
#define int long long//偷懒神器
using namespace std;//必要语句

struct op{//op是随便取得名字
	int d,c;//我把题目的b改c，c改d了 
}b[10000005];//b用的更顺手
int n,m,ans=0,ans1=0,a[10000005];//n和m和a数组如题意，ans和ans1是用来记录答案的

bool cmp(const op x,const op y)//简单的cmp
{
	return x.d>y.d;//从大到小用大于，从小到大不用打cmp
}
bool cmp1(int x,int y)//同上
{
	return x>y;
}


signed main()//用signed避免int变longlong
{
	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<m;i++) cin>>b[i].c>>b[i].d;//输入
	sort(a,a+n);//第一种，从a数组从小到大
	sort(b,b+m,cmp); 
	int j=0,l=0;
	for(int i=0;i<n;i++)
	{
		if(a[i]<b[j].d)//如果a数组里的数小于替换的
		{
			ans+=b[j].d;//答案就加替换的
			l++;//这个l是用来记录这一个替换的数被加了几次
		}
		else
		ans+=a[i];
		if(l==b[j].c)
		{
			j++;
			l=0;
		}
	}
	sort(a,a+n,cmp1);//第二种，a数组从大到小
	sort(b,b+m,cmp); 
	int j=0,l=0;//清零一定要清零
	for(int i=0;i<n;i++)
	{
		if(a[i]<b[j].d)
		{
			ans1+=b[j].d;
			l++;
		}
		else 
		ans1+=a[i];
		if(l==b[j].c)
		{
			j++; 
			l=0;
		}
	}
	cout<<max(ans,ans1);
}
```




---

## 作者：DengDuck (赞：1)

思路其实非常简单，我们尽量有最大的数字替换最小的数字，使得最后答案最大。

所以我们将所有操作按照替换值的大小排个序，从大的值开始操作。

需要注意如果当前的最小值都比你大，你无法替换。

然后用一个优先队列应该不难维护了。


```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
struct node
{
    LL b,c;
}a[100005];
LL n,m,x,ans;
priority_queue<LL,vector<LL>,greater<LL> >p;
bool cmp(node x,node y)
{
    return x.c>y.c;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&x);
        p.push(x);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld",&a[i].b,&a[i].c);
    }
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;i++)
    {
        while(a[i].b&&p.top()<a[i].c)
        {
            p.pop(),p.push(a[i].c);
            a[i].b--;
        }
    }
    while(!p.empty())
    {
        ans+=p.top();
        p.pop();
    }
    printf("%lld",ans);
}
```

---

## 作者：ZHANGyutao123 (赞：1)

# [ABC127D] Integer Cards题解
## [题目传送门](https://www.luogu.com.cn/problem/AT_abc127_d)
## 题目大意

给定 $ N $ 张卡片，第 $ i $ 张卡片上写有整数 $ A_i $。

对于 $ j = 1, 2, ..., M $，执行以下操作：

操作：选择最多 $ B_j $ 张卡片，将选择的卡片上的整数替换为 $ C_j $。

在执行完 $ M $ 次操作后，求 $ N $ 张卡片上整数的最大总和。
## 过程分析
贪心思想。
 
 
将小数换成大数的变化值必定比将大数换成更大数的变化值大。

证明：

设未知数 $ a $ 与 $ b $，且新的整数值为 $ x $，且 $x > a > b$。

则 $ a $ 的变化值为 $ x - a $，修改 $ b $ 的变化值为 $ x - b $。

由于 $ a > b $，因此 $ a-x < b-x $。

证毕。
## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Operation{
    long long num_cards, new_value;
}operations[100005];
long long cards[100005], sum;
bool cmp(Operation a, Operation b){
    return a.new_value > b.new_value;
}
int main(){
    int num_cards, num_operations;
    cin >> num_cards >> num_operations;
    for(int i=0; i<num_cards; i++) {
        cin >> cards[i];
        sum += cards[i];
    }
    for(int i=0; i<num_operations; i++) {
        cin >> operations[i].num_cards >> operations[i].new_value;
    }
    sort(cards, cards + num_cards);
    sort(operations, operations + num_operations, cmp);
    int k=0;
    for(int i=0; i<num_operations; i++){
        bool flag = false;
        for(int j=0; j<operations[i].num_cards; j++){
            if(cards[k] >= operations[i].new_value || k == num_cards){
                flag = true;
                break;
            }
            sum -=(cards[k++] - operations[i].new_value);
        }
        if(flag==true) break;
    }
    cout << sum;
    return 0;
}
```



---

## 作者：flangeborg (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc127_d)

## 阅题构思

根据题意，我们应该尽量使得修改之后的数组总和越大越好，并且发现题目中对于任意一个 $b_i$ 我们可以修改任意数量的（不大于 $b_i$）、位置不限的 $a_i$，将其改为 $c_i$。我们可以使用贪心的方法来求解。

## 贪心思路

- 不难想到，在修改的时候，被修改的数字 $a_i$ 应该越小越好，改成的数字 $c_i$ 越大越好（使用 sort 进行排序），这样修改数字的收益会更大，至此，本题贪心的方法也就出来了。

- 既然要让被修改的 $a_i$ 最小，我们可以使用 STL 里的优先队列，使用小根堆来存储数据。当现在循环到第 $i$ 次修改的时候，将队头与 $c_i$ 进行比较，如果比 $c_i$ 小，队头出队，$c_i$ 入队。如果队头大于等于 $c_i$ 或者此次修改已经进行了 $b_i$ 次，就结束此次修改，最后输出时将队列中的元素求和就可以得出答案了。

## 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<queue>
#define ll long long
using namespace std;
priority_queue<ll,vector<ll>,greater<ll> >q; //使用小根堆求解 
ll n,m,ans;
struct node{ll times,val;}op[100005]; //结构体存储修改操作 
bool cmp(node a,node b){return a.val > b.val;}//对修改操作进行排序 
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i = 1; i <= n; i++)
	{
		int sum;
		scanf("%lld",&sum);
		q.push(sum);//入队 
		ans += sum;//提前求和，降低常数（但没必要） 
	}
	for(int i = 1; i <= m; i++)
		scanf("%lld%lld",&op[i].times,&op[i].val);
	sort(op + 1,op + m + 1,cmp);
	for(int i = 1; i <= m; i++)
	{
		while(op[i].times)
		{
			
			if(op[i].val <= q.top()) break;//停止修改数字的条件 
			int temp = op[i].val;
			ans += temp - q.top();//加上每次修改的收益 
			q.pop();//出队 
			q.push(temp);//修改后入队 
			op[i].times--;
		}
	}
	printf("%lld",ans);//输出 
	return 0;
}
```


---

## 作者：_Memory (赞：0)

## 一、前言

本题有很多种解法，比如贪心、排序、动规都是可以解的。我这边使用了一个贪心加俩排序，以下是解题思路。

## 二、解题
首先我们想尽可能实现利益最大化，使总和变大。那就要尽量使用有限的次数使它变大。那么就是说，里面比较大的数就千万不要换，换的一定是中小数。这边设了一个 $ B $ 和 $ C $ 的结构体，就是说用 $ C $ 数组最大的值尽可能去换 $ A $ 里面最小的。每次将 $ A $ 数组进行从小到大排序，$ C $ 数组从大到小排序，明白了这个就可以愉快的 AC 啦！
   
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, a[1000005], ii = 1;
struct mod {
    int b, c;
} d[1000005];
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> d[i].b >> d[i].c;
    sort(d + 1, d + m + 1, [](mod a, mod b) { return a.c > b.c; });
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i] < d[ii].c)
            a[i] = d[ii].c, d[ii].b--;
        if (!d[ii].b)
            ii++;
        if (ii > m)
            break;
    }
    int u = 0;
    for (int i = 1; i <= n; i++) u += a[i];
    cout << u;
}
```


---

## 作者：fish_love_cat (赞：0)

一个小小的贪心。

显然，为了使和最大，我们应该把**数组的元素往大了变**。同时，也不难发现，把**一个较小数变成大数，必然比一个较大数变成大数收益来的大**，证明放在代码后。所以，我们要把**变成大数的机会留给原数组中的小数**。基于此，那么代码便不难得出了。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct gb{
    long long sl,sz;
}b[100005];
long long a[100005],ans;//long long 需注意
bool cmp(gb a,gb b){
    return a.sz>b.sz;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>a[i],ans+=a[i];
    for(int i=0;i<m;i++) cin>>b[i].sl>>b[i].sz;
    sort(a,a+n);//从小到大
    sort(b,b+m,cmp);//把大数机会留给小数
    int k=0;
    for(int i=0;i<m;i++){
        bool f=false;
        for(int j=0;j<b[i].sl;j++){//执行数量
            if(a[k]>=b[i].sz||k==n){//如果赋值完了或者接下来赋值会变小，都得跳出
                f=true;
                break;
            }
            ans=ans-a[k++]+b[i].sz;//更改
        }
        if(f) break;
    }
    cout<<ans<<endl;//换行
	return 0;
}
//qwq
```

---

**对于小数化大比大数化大更优的证明如下：**

假设有 $a,b,x$ 三数，满足 $x>a>b$，其中 $x$ 是要变成的数。可知用 $a$ 变，收益为 $x-a$；用 $b$ 变，收益为 $x-b$。

~~通过小学知识可知~~减数越大结果越小，为了使收益增多，我们应当贪心的选择小数化大。

证毕。

---

## 作者：Bpds1110 (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/AT_abc127_d)
## 题面：
给定一个长度为 $n$ 的序列 $a$，和长度为 $M$ 的序列 $b$ 和 $c$，表示你最多可以选择 $a$ 中 $b_i$ 个数变为 $c_i$。让你求出在经过数次操作后，$A$ 序列的总和最大是多少。
## Solution:
我们首先考虑，如果有两个数 $a_i$ 和 $a_j$，并且 $a_i \le a_j$，$a_i \le a_j \le c_k$，那么最优策略是把 $a_i$ 替换成 $c_k$。因为把 $a_i$ 替换成 $c_k$，增加的值是 $c_k - a_i$，如果把 $a_j$ 替换成 $c_k$，增加的值是 $c_k - a_j$。比较 $c_k - a_i$ 和 $c_k - a_j$，因为 $a_i \le a_j$，所以 $c_k - a_i \ge c_k - a_i$。从中，我们可以发现这个贪心策略：**如果有几个数同时比可以替换的数小，那么把最小数替换成这个数增加的值最大**。有了这个结论，问题迎刃而解。我们要**让最小的数替换成最大的数，把第二小的数替换成第二大的数，把第三小的数替换成第三大的数，以此类推，直到原本的数比可以替换的数大**。这道黄题变成了纯模拟题，步骤如下。

- 用数组存放 $a$，用结构体 $f$ 数组存放 $b$ 与 $c$，之后把 $a$ 从小到大进行排序，把 $f$ 按照 $b$ 从大到小进行排序。
- 我们设 $tot$ 为**当前指向可以替换的数字在 $f$ 数组中的下标**，它最初默认指向第一个可以替换的数。
- 枚举每一个 $a_i$，如果 $a_i$ 比 $f_{tot}$ 中可以替换的值大，就直接终止循环。因为，$a$ 数组从小打大，$f$ 数组从大到小，而 $f_{tot}$ 之后的数只会越来越小，一定比 $a_i$ 大。
- 把当前的 $a_i$ 替换成 $f_{tot}$ 中替换成的值，并且把 $f_{tot}$ 中可以替换成的次数减 $1$。如果当前替换完成后，$f_{tot}$ 中可以替换的次数已经为 $0$，就把 $tot$ 指针后移一格。
- 重复执行第三步，直到枚举玩每一个 $a_i$ 或中途退出。
- 累加 $a$ 数组中总和。

思路还是有点麻烦，~~主要是太啰嗦了~~，代码更简单易懂。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 1;
int n, m;
ll a[N];
struct node{
	ll b;//可以替换成的值 
	ll c;//可以替换的次数 
}f[N];
bool cmp(node x, node y) 
{
	return x.c > y.c;//按照可以替换成的值从大到小 
}
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
	for(int i = 1; i <= m; i ++)
		cin >> f[i].b >> f[i].c;
	sort(a + 1, a + 1 + n);//a数组从小到大 
	sort(f + 1, f + 1 + m, cmp);//f数组从大到小 
	int tot = 1;//默认指向f数组中第一个位置 
	for(int i = 1; i <= n; i ++)
	{
		if(a[i] > f[tot].c) break ;
		//如果a[i]比f[tot]中可以替换的值大，直接退出 
		a[i] = f[tot].c;//替换a[i]的值 
		f[tot].b --;//当前可替换的次数-1 
		if(! f[tot].b) tot ++;
		//可以替换成当前值的次数已经用尽，指针指向下一个位置 
	}
	ll ans = 0;
	for(int i = 1; i <= n; i ++)
		ans += a[i];//累加 
	cout << ans;
	return 0;
}

```


---

## 作者：guanyf (赞：0)

题目传送门：[Luogu](https://www.luogu.com.cn/problem/AT_abc127_d)

原题传送门：[Atcoder](https://atcoder.jp/contests/abc127/tasks/abc127_d)
### 分析
首先，根据题目可以得出一个结论：为了让和尽可能的大，因此在每次操作时，我们要让**小的数尽可能变大，大的数不会变小**。对于一个已经变换的数来说，如果按照上面的结论来变换，那么它再变换是没有任何意义的。因此，对于每一个数来说，它变换一次是最优的。

实际上，当我们将一个大的数变得更大时，是没有将一个小的数变大划算的。因此，我们要尽可能的将小的数变得更大，而大的数不会变小。

### 思路
按照上述结论，我们只需要将 $A$ 从小到大排一遍序，将 $BC$ 看作一体，按照 $C$ 从大到小排一遍序。对于每个 $A_i(1 \le i \le n)$ 当它小于 $C_j(1 \le j \le m)$ 时，则将它替换成 $C_j$ 并把 $B_j$ 减一。当 $B_j$ 等于 `0` 时，则将 $j$ 加一。

### 实现
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5 + 5;
int n, m, a[MAXN], ans;
pair<int, int> b[MAXN];
signed main() {
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= m; i++) {
    cin >> b[i].second >> b[i].first;
  }
  sort(b + 1, b + 1 + m, greater<pair<int, int> >());
  for (int i = 1, j = 1; i <= n && j <= m && b[j].first > a[i]; i++) {
    a[i] = b[j].first, j += (--b[j].second == 0);
  }
  for (int i = 1; i <= n; i++) {
    ans += a[i];
  }
  cout << ans;
  return 0;
}
```

---

