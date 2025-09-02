# Micro-World

## 题目描述

You have a Petri dish with bacteria and you are preparing to dive into the harsh micro-world. But, unfortunately, you don't have any microscope nearby, so you can't watch them.

You know that you have $ n $ bacteria in the Petri dish and size of the $ i $ -th bacteria is $ a_i $ . Also you know intergalactic positive integer constant $ K $ .

The $ i $ -th bacteria can swallow the $ j $ -th bacteria if and only if $ a_i > a_j $ and $ a_i \le a_j + K $ . The $ j $ -th bacteria disappear, but the $ i $ -th bacteria doesn't change its size. The bacteria can perform multiple swallows. On each swallow operation any bacteria $ i $ can swallow any bacteria $ j $ if $ a_i > a_j $ and $ a_i \le a_j + K $ . The swallow operations go one after another.

For example, the sequence of bacteria sizes $ a=[101, 53, 42, 102, 101, 55, 54] $ and $ K=1 $ . The one of possible sequences of swallows is: $ [101, 53, 42, 102, \underline{101}, 55, 54] $ $ \to $ $ [101, \underline{53}, 42, 102, 55, 54] $ $ \to $ $ [\underline{101}, 42, 102, 55, 54] $ $ \to $ $ [42, 102, 55, \underline{54}] $ $ \to $ $ [42, 102, 55] $ . In total there are $ 3 $ bacteria remained in the Petri dish.

Since you don't have a microscope, you can only guess, what the minimal possible number of bacteria can remain in your Petri dish when you finally will find any microscope.

## 说明/提示

The first example is clarified in the problem statement.

In the second example an optimal possible sequence of swallows is: $ [20, 15, 10, 15, \underline{20}, 25] $ $ \to $ $ [20, 15, 10, \underline{15}, 25] $ $ \to $ $ [20, 15, \underline{10}, 25] $ $ \to $ $ [20, \underline{15}, 25] $ $ \to $ $ [\underline{20}, 25] $ $ \to $ $ [25] $ .

In the third example no bacteria can swallow any other bacteria.

## 样例 #1

### 输入

```
7 1
101 53 42 102 101 55 54
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 5
20 15 10 15 20 25
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7 1000000
1 1 1 1 1 1 1
```

### 输出

```
7
```

# 题解

## 作者：Mysterious_Mini (赞：12)

$\text{update on 2021-05-29：修改了码风及 \LaTeX 并删除了部分废话。}$

这是本蒟蒻的第 $1$ 篇题解。
### 思路：
这道题，用 $\texttt{vector}$ 做会很简单，执行效率也很高。

先来简单介绍一下 $\texttt{vector}$（动态数组）：

$1.$ 头文件：

```cpp
#include<vector>
```
  
$2.$ 定义：

```cpp
vector <type_name> v;
```

$\text{v}$ 可以换成其他名称，规则与定义变量一致，$\texttt{type\_name}$ 为变量类型，这里是最基本的一种定义方法
  
$3.$ 简单用法：
  
```cpp
v.empty()
```

若 $\texttt{vector}$ 非空，则返回 $\text{false}$，否则返回 $\text{true}$。


------------

```cpp
v.front()
```
返回 $\text{v}$ 的第一个元素。


------------

```cpp
v.back()
```
返回 $\text{v}$ 的最后一个元素。
 

------------

```cpp
v.clear()
```
清空 $\text{v}$ 中的元素。
  

------------

```cpp
v.push_back(n)
```
在 $\text{v}$ 的尾部插入 $n$。
 

------------

```cpp
v.pop_back()
```
删除 $\text{v}$ 的最后一个元素。
  

------------

```cpp
v.size()
```
返回 $\text{v}$ 中的元素个数。
  

------------

本题思路为先让细菌大小从小到大排序，再循环 $n$ 次。当 $\text{v}$ 非空，并且 $a_i$ 可以吞噬 $\text{v}$ 的最后一个元素时，就持续将 $\text{v}$ 的最后一个元素删除。之后每次在 $\text{v}$ 的最后插入第 $i$ 个细菌的大小。最后 $\text{v}$ 中的元素个数即为答案。
### 代码：
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector <int> v;

const int MAXN = (int)1e6 + 5;

int n, k, a[MAXN];

int main()
{
    //输入
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
                         
    //从小到大排序
    sort(a, a + n);
                         
    //核心思路
    for(int i = 0; i < n; i++)
    {
        while(!v.empty() && a[i] > v.back() && a[i] <= v.back() + k)
            v.pop_back();
        v.push_back(a[i]);
    }
                                                              
    //输出答案
    printf("%d\n", v.size());
    
    return 0;
}
```
[Accepted 记录](https://www.luogu.com.cn/record/46586341)

---

## 作者：CQ_Bab (赞：2)

# 思路
~~这道题其实很水~~，只需要用一个 $\text{vector}$ 就可以啦！如果不懂 $\text{vector}$ 的请点这里[vector（滚动数组）的解释](https://baike.baidu.com/item/vector/3330482?fr=aladdin)。然后我们可以让细菌们打擂台（切记一定先要将 $a$ 数组从小到大排序才能保证 $a_i$ 一定能将之前比它小且差值小于 $k$ 的人踢出），每次没到赢得就从队列中退出，然后将 $a_i$ 加入因为若 $a_i$ 不满足会被下一轮的人踢出去（这里用 $\text{while}$ 循环来遍历因为当 $a_x$ 不满足是它后面的也一定不满足）。最后只需要输出还在队列中的元素个数即可！

# AC代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
int n,a[200100],k;
vector<int>q;
int main() {
	cin>>n>>k;
	for(int i=1; i<=n; i++) cin>>a[i];
	sort(a+1,a+1+n); //排序 
	for(int i=1; i<=n; i++) {
		while(!q.empty()&&a[i]-q.back()<=k&&a[i]>q.back()) q.pop_back(); //判断是否满足要求，满足则将他踢出 
		q.push_back(a[i]); //加入a[i] 
	}
	cout<<q.size()<<endl; //输出个数 
	return false;
}
```


---

## 作者：Texas_the_Omertosa (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF990B)

本题考察点:

贪心、排序

思路：

我们可以把输入的数排好，然后从第二个开始扫前面的。能够删除的条件有

1. 未被删除

1. 小于当前数

1. 加上 k 大于或等于当前数

用一个 while 循环判断再注意不要越界就行。

AC CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
bool f[200005];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,k,ans=0;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=2;i<=n;i++)
	{
		int j=i-1;
		while(!f[j]&&a[i]>a[j]&&a[i]<=a[j]+k)
		{
			++ans,f[j]=1;//累加与标记
			if(j>1)--j;
			else break;//判断越界
	    }
	}
	cout<<n-ans<<'\n';//由于要输出的是剩下的，而我们累加的是删除的，所以要减
	return 0;
}
```

求大佬给赞，蟹蟹！

---

## 作者：Aya_tt (赞：1)

读完题后，我就想到题目说求最小的可能长度，其实就是再说什么时候删数到删到不能再删的时候就输出。

为了保证前后关联紧密，一个要排序。

当每个数据不能再查找的时候，我们就可以定义一个 $vis$ 数组来做个标记，表示不能再查找下去了，一定要用 $if$ 判断是否满足条件，这也是核心代码：

```
	while(a[i] <= a[j] + k && a[j] != -1 && a[i] > a[j]){ //核心判断，判断他是否满足题意
            ans++; //统计+1
            a[j] = -1;
            if(j > 1) j--;
            else break;//跳出去
        }
```
这个核心代码是只针对一个点，我们整体也要便利一遍。

总体代码：
```c
#include<bits/stdc++.h>
using namespace std;
int n,k,a[500010],ans,vis[500010];
int main()
{
    cin>>n>>k;
    for(int i = 1;i <= n;i++) {
    	cin>>a[i];
	}
    sort(a + 1, a + n + 1);//一定要排序啊
    for(int i = 2;i <= n;i++) 
    {
    	int j = i - 1;
        while(a[i] <= a[j] + k && a[j] != -1 && a[i] > a[j])
        {
            ans++;
            a[j] = -1;
            if(j > 1) j--;
            else break;
        }
    }
    cout<<n - ans<<endl;
    return 0;
}
```


---

## 作者：Qiancy1427 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF990B)

标签：排序

思维含量相对较高，但代码实现难度不大。

### 思路：

首先我们来思考一个问题：为什么标签是排序呢？

（下面的解读仅限于中文翻译，不包括英文题意）

我们仔细读一下题（当然，翻译版的已经相当简洁了），就会发现，只要满足 $a(j)< a(i)$ 和 $a(i)\le a(j)+k$ 这两个条件（$i$ 为任意数），就要将 $a(j)$ 就会被删去，最后统计有多少个 $a(j)$ 会被删去（也就是有多少个 $a(j)$ 符合条件）。

可能会有大佬说用这个那个数据结构，不过这个其实纯粹计数加标记就行，不必真的从数组中删除。

很明显，只有当 $a(i)>a(j)$ 时，$a(j)$ 和 $a(i)$ 才可能满足条件。所以我们需要把 $a$ 数组排成升序，然后从一个点往前排查，看能否删除。能删除就让答案减一。

注：降序也可以实现，不过都要反过来。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans;	//n,k如题 
int a[200005],f[200005];	//a记录数据，f标记是否走过 
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);	//cstring库里的sort函数 ，第三个参数不写默认为升序 
	ans=n;	//ans初始设为n，按题意一个一个删 
	for(int i=2;i<=n;i++){
		int j=i-1;
		while(f[j]==0&&j>=1&&a[j]<a[i]&&a[i]<=a[j]+k){	//满足3个条件的数可以删掉 
			ans--;
			f[j]=1;	//做好标记，避免重算 
			j--;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：As_Snow (赞：0)

#### [题目链接](https://www.luogu.com.cn/problem/CF990B)
#### 前置芝士：[栈](https://oi-wiki.org/ds/stack/)

### 题意
有一个长度为 $n$ 的序列 $a$ ，当 $a_i>a_j$ 且 $a_i\le a_j+k$ 时，可以把 $a_j$ 删除掉。求这个序列可能的最小长度。

### 思路
先对数组排个序，然后依次对于每一个 $a_i$ 去遍历它之前的还没有被删除的每一个 $a_j$ 看是否满足条件，然后删掉。

不难发现，这个过程可以用栈来模拟，且当一个 $a_j$ 不满足条件时，它前面的所有数都不会满足条件（感性理解一下）。
模拟的过程大致如下：

1. 遍历每一个点。

2. 对于每一个点 $a_i$ 我们去循环判断它是否能删除掉栈顶，如果可以便把栈顶弹出，否则就跳出循环。

3. 将当前元素 $a_i$ 入栈。

4. 遍历完以后输出栈内剩余元素的个数。

## Code:

对于栈，我们可以用数组来模拟，也可以用 C++ STL 里自带的 ```stack``` 容器。

### 法一：用数组模拟
```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+25;
int n,k;
int a[N];
int st[N],size;
signed main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		while(size&&st[size]<a[i]&&a[i]<=st[size]+k)size--;
		st[++size]=a[i];
	}
	printf("%d",size);
	return 0;
}
```

### 法二：用 STL 中的 stack 容器 
```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+25;
int n,k;
int a[N];
stack<int>st;
signed main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		while(st.size()&&st.top()<a[i]&&a[i]<=st.top()+k)st.pop();
		st.push(a[i]);
	}
	printf("%d",st.size());
	return 0;
}
```


---

## 作者：Symbolize (赞：0)

# 思路
## 第一步
输入。
## 第二步
将输入的数组 $a$ 从小到大进行排序。
## 第三步
定义一个栈 $sta$，循环遍历一遍数组 $a$。
## 第四步 
在遍历过程中循环判断是否可以删除栈顶元素。
判断条件：
1. 目前的栈非空；
2. $a_i$ 大于栈顶元素； 
3. $a_i$ 小于等于栈顶元素加 $k$。

如果以上三个条件都满足，那么说明我们的栈顶元素可以删掉，直接出栈。否则结束判断。
## 第五步
循环判断完是否可以删除后将当前元素入栈。
## 第六步
栈内剩余元素个数及答案，输出即可。
## Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=2e5+10;
using namespace std;
int n,k,a[N];
stack<int> sta;//栈
signed main()
{
	cin>>n>>k;
	rep1(i,1,n) cin>>a[i];
	sort(a+1,a+n+1);//排序
	rep1(i,1,n)
	{
		while(!sta.empty()&&a[i]>sta.top()&&a[i]<=sta.top()+k) sta.pop();//判断是否可删除
		sta.push(a[i]);
	}
	int ans=0;
	while(!sta.empty()) sta.pop(),++ans;//剩余元素个数
	cout<<ans<<endl;//输出
	return 0;
}
```

---

## 作者：AlicX (赞：0)

#### 前言
这道题十分的水，细心模拟就可以了。

### 具体思路
因为我们判断一个数可不可以被删除，是根据前面的数来判断的，条件是这个数首先要大于前面的这个数，且小于前面的这个数加 $k$，那么我们就可以按从小到大的顺序排序，保证了前面的数 $\leq$ 这个数，再判断一下就可以了。

具体细节看代码。

### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+10;
int n,k;
int a[N];
bool st[N];//标记数组 
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);//记住要排序 
	int cnt=0;
	for(int i=1;i<=n;i++){
		int j=i-1;//从后往前便历 
		while(j>=1&&!st[j]&&a[j]<a[i]&&a[i]<=a[j]+k){//判断一下 
			cnt++;//这个点可以被删除 
			st[j]=true;//标记 
			j--;//继续将坐标减减 
		}
	}
	cout<<n-cnt<<endl;//输出 
	return 0;//Bye~
}	 
```
$$Thanks$$

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF990B)

贪心 + 排序

# 思路：

排序后从第二个开始枚举往前扫，设当前数为 $i$ ，前面的一个数为 $j$ ,如果满足删除条件就删除

1. $i+k \ge j$
2. $i<j$
3. ( 最容易被忽略的一点 ) 未被删除（ $f[j]=0$ ）

------------

那么就上 AC 代码（含注释）吧！
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],n,k,ans=0;//a[i] 为第 i 个数，ans 记录可删除的数 
bool f[200005]={false};//f[i]=0 代表第 i 个数未被删除，否则被删除
int main(){
	cin>>n>>k;//输入 
	for(int i=1;i<=n;i++)cin>>a[i];//输入 
	sort(a+1,a+n+1);//排序（默认从小到大） 
	for(int i=2;i<=n;i++){//循环枚举 
		int j=i-1;//i 前面的数从 i-1 开始枚举 
		while(f[j]==0&&a[i]>a[j]&&a[i]<=a[j]+k){//上述的三种情况（可以删除） 
			ans++;//计数器 +1 
			f[j]=1;//已被删除 
			if(j>1)j--;//没有到第一位时，则可继续枚举 
			else break;//否则退出 
	    }
	}
	cout<<n-ans<<endl;//输出剩下的数 
	return 0;//结束程序 
}
```


---

## 作者：__cht (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF990B)
******
### 思路
从小到大排序，然后寻找捕食者。

从1到n开始扫描，**如果此时的捕食者不能吞噬掉他的前一个细菌，则说明再往前的也一定吞噬不掉（重点）**

如果可以吞噬就继续往前扫描，可以用`while`循环实现。

为了防止遇到大小相同的细菌，我们在判断是否能吞噬时不能省略掉`a[i] > a[j]`这个部分的。

最后就是如何标记被吞噬的细菌了。可以直接把他的大小变成`INT_MIN`，这样的话就不会重复扫描了。遇到`INT_MIN`的时候停止扫描就行了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200010, INF = INT_MIN;
int n, k;
int a[N];
int main()
{
    cin >> n >> k;
    for(int i = 0; i < n ;i ++) cin >> a[i];
    sort(a, a + n);
    int s = 0;
    for(int i = 1; i < n; i ++) 
    {
        int j = i - 1;
        while(a[i] <= a[j] + k && a[j] != INF && a[i] > a[j])
        {
            s ++ ;
            a[j] = INF;
            if(j > 0) j --;
            else break;
        }
    }
    cout << n - s << endl;
    return 0;
}
```

---

## 作者：帅到报警 (赞：0)

### 【题意描述】
你有一个细菌培养皿，现在要通过这个培养皿完成一些事情……培养皿中有 n 个细菌，每个细菌的大小为Ai,并给出一个常数 k 。然后他们要互相吞噬。而 i 菌能吞噬 j 菌的条件为 Ai > Aj而且Ai + k < Aj，但吞噬完成后 Ai 的大小是不变的(QwQ)。请你求出吞噬停止时培养皿中的细菌数量。

### 【分析】
这道题只要仔细分析，不难想到正解。~~（主要是英语太弱）~~既然 i 和 j 并没有相邻的要求，那么可以**将它们从小到大排序，然后扫一遍让后面一个满足条件的细菌吞噬前面一个细菌**。可是怎么处理数据中大小相同的细菌呢？因为如果直接排序两个大小相同的细菌并不能在O(n)的处理中完成。所以可以再利用一个 b[ ]数组。**b 的下标表示此细菌的大小，储存了此大小的细菌有几个的信息**。这样就像使用一个 set ，保证其中数据不重复，再排序 b[ ] 即可。

### 【核心代码】
1、读入处理 b[ ]。
```cpp
for(int i = 1; i <= n; i++)
	{
		t++;
		cin >> a[t];
		if(b[a[t]] != 0)
		{
			b[a[t]]++;
			t--;//下一个读入直接覆盖上一个多余的
		}
		else
			b[a[t]]++;//如果已经出现直接数量++
	}
```

2、O(n)扫一遍，如果满足条件就吞噬，ans减去此菌的数量
```cpp
ans = n;
for(int i = 1; i <= t - 1; i++)
	if(a[i] + k >= a[i + 1])
		ans -= b[a[i]];
```

### 【正解】
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, k, t, ans;
int a[1000010], b[1000010];
//Ai的值小于10的6次方，注意数组范围

int main()
{
	cin >> n >> k;
	ans = n;
	for(int i = 1; i <= n; i++)
	{
		t++;
		cin >> a[t];
		if(b[a[t]] != 0)
		{
//			t--;
			b[a[t]]++;
			t--;
		}
		else
			b[a[t]]++;
	}
	sort(a + 1, a + t + 1);
	
	for(int i = 1; i <= t - 1; i++)
		if(a[i] + k >= a[i + 1])
			ans -= b[a[i]];
	
	cout << ans;
	
	return 0;
}
```

---

