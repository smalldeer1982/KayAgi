# Numbers on Whiteboard

## 题目描述

Numbers $ 1, 2, 3, \dots n $ (each integer from $ 1 $ to $ n $ once) are written on a board. In one operation you can erase any two numbers $ a $ and $ b $ from the board and write one integer $ \frac{a + b}{2} $ rounded up instead.

You should perform the given operation $ n - 1 $ times and make the resulting number that will be left on the board as small as possible.

For example, if $ n = 4 $ , the following course of action is optimal:

1. choose $ a = 4 $ and $ b = 2 $ , so the new number is $ 3 $ , and the whiteboard contains $ [1, 3, 3] $ ;
2. choose $ a = 3 $ and $ b = 3 $ , so the new number is $ 3 $ , and the whiteboard contains $ [1, 3] $ ;
3. choose $ a = 1 $ and $ b = 3 $ , so the new number is $ 2 $ , and the whiteboard contains $ [2] $ .

It's easy to see that after $ n - 1 $ operations, there will be left only one number. Your goal is to minimize it.

## 样例 #1

### 输入

```
1
4```

### 输出

```
2
2 4
3 3
3 1```

# 题解

## 作者：Konnyaku_LXZ (赞：7)

显然，每次从右往左删，得到的答案都是 $2$，一定是最优的。

下面给出证明：

删除 $N$ 和 $N-1$ ，得到数 $N$；删除 $N$ 和 $N-2$ ，得到数 $N-1$ ；删除数 $N-1$ 和 $N-3$ ，得到数 $N-2$；以此类推，最后会删除数 $3$ 和 $1$ ，得到数 $2$。

为什么 $2$ 是最小答案呢？我们假设存在更小的答案，则该答案只能为 $1$，因为上取整不可能取到 $0$。然后我们发现，$1$ 只能由 $(1+1)/2$ 得到，一旦出现一个大于 $1$ 的数，合并后的结果一定也会大于 $1$，因此不存在答案为 $1$ 的情况，所以 $2$ 就是最小答案。

Code：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

int N;

void Init(){
	scanf("%d",&N);
}

void Solve(){
	
}

void Print(){
	puts("2");
	for(int i=N;i>1;--i) printf("%d %d\n",i-1,i==N?i:i+1);
}

int main()
{
	int T;
	cin>>T;
	while(T--){
		Init();
		Solve();
		Print();
	}
	return 0;
}
```

---

## 作者：_zy_ (赞：4)


## **题目大意：**
T次询问，给一个1、2、3、4...n的序列，得到n-1的操作，可以把a,b两个数合并成⌈（a+b）/2⌉，求出能化成的最小的一个数。


------------
### 几条小小的性质（或许你们都能看出来，可我还是要点一下，~~我好菜Orz~~）

1.n个数合并n-1次一定得到的是一个数（~~题目中给了~~）


2.a+b是偶数一定比a+b是奇数更优秀，因为上取整将合并的数


3这道题最重要的：

#### 最后的答案一定是2
我们不放先手玩几个数字

![1](https://cdn.luogu.com.cn/upload/image_hosting/sfi3z1qn.png)

很显而易见了吧！

如果n换个数

那么最后的结果还是2啊

从图片中看出来最优的合并的方法就是


n和n-2合并出n-1

两个n-1合并出n-1

然后n-1和n-3    n-2和n-4  n-3和n-5....

最后相减倒n-3为1了就正好是1个数也就是n-1个操作了。

----------
## **代码如下：**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
int re() {
	int p=0; char i=getchar();
	while(i<'0'||i>'9')	i=getchar();
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return p;
}
int t,n;
int main()
{
	t=re();
	while(t--)
	{
		n=re();
		printf("2\n");
		if(n==2) {printf("1 2\n");continue;}
		printf("%d %d\n",n,n-2);
		printf("%d %d\n",n-1,n-1);
		while(n>=4) {
			printf("%d %d\n",n-1,n-3);
			n--;
		}
	}
	return 0;
}

```
zzzzz



---

## 作者：_Xiuer (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1430C)

题目翻译的已经很透彻了，就是让我们求**n-1次删除之后剩余数的最小值.**  
首先我们发现我们要尽量使上取整的次数少，~~经过大量的实践，~~ 可以发现除了n=1时答案为1外，其他所有最后都可以化为**2**,下面我们尝试一下证明：  
对于一个序列$1...n$,$\frac{n-2+n}{2}=n-1$ ,$\frac{n-1+n-1}{2}=n-1$,进行这两步操作后序列里还剩下$1...n-3,n-1$，而$\frac{n-3+n-1}{2}=n-2$，序列还剩下$1...n-4,n-2$，这样一直进行下去，可得最后剩下的数为**2**。     
按照这样的规则输出即可。  
**注:特判n=1和n=2的情况**
### $Code$
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		if(n==1) {printf("1\n");continue;}
		printf("2\n");
		if(n==2) {printf("1 2\n");continue;}
		printf("%d %d\n",n,n-2);
		printf("%d %d\n",n-1,n-1);
		for(int i=n-3;i>=1;i--)
		printf("%d %d\n",i+2,i);
	}
	return 0;
}

---

## 作者：NXYorz (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1430C)

首先可以发现两个性质

- $\frac{n + n - 2}{2} = n - 1$
- $\frac{n + n}{2} = n$

根据这两个性质，可以发现对于$n,n-1,n-2$可以换成$n-1$，此时序列里仅剩下$1,2,3....n-3,n-1$，接着把$n-1,n-3$合并，序列里仅有$1,2,3....n-4,n-2$。

以此类推，最后总能剩下$1,3$，所以答案恒为$2$。

但是要注意特判$n=1$的情况。

### $Code$
```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 2e5 + 10;

int t,n;

void in(int &x)
{
	x = 0; char ee = getchar();
	while(ee < '0' || ee > '9') ee = getchar();
	while(ee >= '0' && ee <= '9') x = (x << 1) + (x << 3) + ee - '0' , ee = getchar();
}

void work()
{
	in(n);
	if(n == 1) {printf("1\n");return;}
	if(n == 2){
		printf("2\n1 2\n");return;
	}
	printf("2\n");int time = n - 1;
	printf("%d %d\n",n - 2,n);
	printf("%d %d\n",n - 1, n - 1);
	n--;time -= 2;
	for(int i = time; i >= 1; i--)
		printf("%d %d\n",n,n - 2) , n--;
	return;
}

int main()
{
	freopen("aa.in","r",stdin);
	in(t);
	while(t--)
		work();
	return 0;
}
```

---

## 作者：_byta (赞：2)

似乎没有用优先队列的题解，我来发一篇。

首先有一个显然的贪心想法，每次取最大的两个加加除二，这是就有可能导致最大的数的位置发生改变，为了防止这种情况，我们可以用大根堆维护最大值，然后贪心即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200002;
int a[N], m, n, k, p, q, ans, sum, tot, cnt, f[15][N];
inline int read()
{
    register int x = 0, f = 1;
	char ch = getchar();
    while(!isdigit(ch))
	{
		if(ch == '-') f=-1;
		ch = getchar();
	}
    while(isdigit(ch))
	{
		x=(x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
    return x * f;
}
signed main() 
{
	int T = read();
	while(T--)
	{
		priority_queue<int> q;
		n = read();
		for(int i = 1; i <= n; i++)
		{
			q.push(i);		
		}	
		cout << "2" << endl;
		while(!q.empty())
		{
			int x = q.top(); q.pop();
			if(q.empty()) break;
			int y = q.top(); q.pop();
			cout << y << " " << x << endl; 
			if((x + y) % 2 == 0)
			{
				q.push((x + y) / 2);
			}
			else q.push((x + y) / 2 + 1);
		}
	}
	return 0;
}
```


---

## 作者：黄文烽 (赞：1)

## 蒟蒻第四篇题解，写得不好，巨佬勿喷
### 样例的修改
原题的样例还可以这样子输出：

$2$

$3$ $4$

$2$ $3$

$1$ $3$

### 基础的贪心
因为题目要求每一次$/2$的结果要向上取整，所以说我们可以每一次选择相加为偶数的两个数（于是原本的样例就出现了）

伪代码：
```cpp
while(!check()){
    for(int i = n - 1; i >= 0; i--){
        if(vis[a[i]] && vis[n - a[i]]) choose(); //vis是标记存不存在此数字的bool数组
    }
}
```
$choose$函数的写法显而易见：将每一次得到的结果存入一个数组，并且更新$vis$数组，数字个数$n-1$。

那么，$check$函数该如何写呢？

最简单的写法（伪代码）:
```cpp
for(int i = 0; i < n; i++) if(vis[i]) num++;
return num == 1;
```
### 进一步的解法
我们可以发现每一次更新都会变动数组当中的两个数，所以我们只需要在每一次操作后都把新的数进行冒泡，这样的时间复杂度虽然也是$O(n)$，但是常数上更优。

部分代码如下：
```cpp
void srt(){ //每一次冒泡
    for(int i = n - 2; i >= 0; i--){
        if(a[i] < a[i - 1]) swap(a[i], a[i - 1]);
    }
}
```

然后这样$check$函数就只需要检查$a[1]$是否为$0$就好了！

**先不要兴高采烈，我们先看一下数据范围。**

$2≤n≤2*10^5 ,∑n≤2*10^5$

这样的数据范围，显然我们一开始的做法是肯定会爆空间的！ 那么如何解决？

### 更进一步的解法
当我们实验几组数据时，我们会发现结果都是$2$。

于是，我们可以做一个大胆的猜想：每一次的结果都为$2$！

由于我们每一次的操作结束后都会排序数组，所以最后一次操作前数组里肯定会留下最小的$2$个数——即$1$和$2$，那么结果肯定为$2$。

于是，我们就可以快乐地先输出二，然后边处理边输出了。

部分代码如下：
```cpp
void choose(int a, int b){
    n--;
    cout << a << ' ' << b << endl; //输出
    vis[a] = false, vis[b] = false;
    vis[up(a + b)] = true; //up为将正整数/2向上取整的自定义函数
    srt(up(a + b));
}

......

cout << "2\n";
while(!check()){
    for(int i = n - 1; i >= 0; i--){
        if(vis[a[i]] && vis[n - a[i]]) choose(a[i], (n - a[i])); 
    }
}
```

那现在是不是就完美了呢？并不是的，结果**肯定是[这样子](https://www.luogu.com.cn/record/40274877)的**（如果没有加强数据的话）

我们可以发现——其实我们爆的不仅仅是空间，还有时间。

那么AC之路，远在何方？

### 最后的解法

我们可以发现，因为每一次最后肯定要剩下$1$和$2$才能够有最优解，所以我们只需要让结果剩下$1$和$2$就可以了。

那么，我们可以想到——如果每一次都选最大的两个数，会发生什么？

因为一开始的序列为连续的正整数，所以我们每一次挑最大的两个数一定会产生最优解——因为每一次处理后的序列都已经排好序了。

这样我们就能够直接把$O(n^3)$的时间复杂度提升到$O(n)$了！

### Code:
```cpp
#include<iostream>

using namespace std;

int t, n;
int a[200005];

int up(int x){ //返回x/2向上取整的值
	if(x % 2) return (x + 1) / 2;
	else return x / 2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

	cin >> t;
	
	while(t--){
		cout << 2 << endl;
		
		cin >> n;
		
		for(int i = 1; i <= n; i++) a[i] = i; //产生序列
		
		int pos = n; //当前处理的下标
		
		while(pos > 1){
			cout << a[pos - 1] << ' ' << a[pos] << endl; //输出最大的两个数
			
			a[pos - 1] = up(a[pos] + a[pos - 1]); //当前最大数为新数
			
			pos--;
		}
	}
	
	return 0;
}
```

**最终结果：[AC](https://www.luogu.com.cn/record/40274982)**

---

## 作者：Watermatter (赞：1)

由题意我们很容易知道，当我们合并$n-2,n-1$时，因为是平均数上取整，我们会得到一个$n-2$，在将其与$n$合并，会得到一个$n-1$，之后$n-1$又可以和$n-3$合并得到$n-2$……依次类推，最后会由$3$和$1$合并为2。故第一问答案恒为2($n>=2$).

既然要我们输出每一次合并的步骤，由上文得，只需要将末尾两个数合并，再将他们的平均值插入序列，我们可以用一个双端队列来实现这一操作。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
deque<int>q;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		puts("2");
		for(int i=1;i<=n;i++)q.push_back(i);
		for(int i=1;i<=n-1;i++){
			int a=q.back();q.pop_back();
			int b=q.back();q.pop_back();
			printf("%d %d\n",b,a);
			if((a+b)%2==0)q.push_back((a+b)/2);
			else q.push_back((a+b)/2+1); //因为要向上取整平均数
		}
	}
	return 0;
}
```


---

## 作者：Jay142753869 (赞：1)

题意：给你一个 $1 \dots n$ 的序列，你可以选定序列中的两个数 $a$，$b$，删去这两个数，往序列里加上一个数$\lceil$$\frac{a+b}{2}$$\rceil$，求进行 $n-1$ 次操作后剩下的最后一个数的最小值。

通过题目我们可以发现，题目是把 $n$ 和 $n-2$ 合并成  $n-1$，之后两个 $n-1$ 变成一个 $n-1$，之后用当前的最大值 $now$ 与 $now-2$ 合并，得到 $now-1$。所以我们可以用更大的数去试一下，发现 $n-1$ 次操作之后我们都可以得到最后的数会是 $2$，所以答案是 $2$。

记得 $n=2$ 时要特判。

 _Code_
 ```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cstdio>
#define ll long long
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
int t,n,now;
int main(){
	t=read();
	while(t--){
		now=n=read();
		if(n==2){
			puts("2\n1 2");
			continue;
		}
		puts("2");
		for(int i=1;i<n;i++){
			if(i==2){printf("%d %d\n",now,now);continue;} 
			printf("%d %d\n",now-2,now),now--;
		}
	}
	return 0;
}
```


---

## 作者：zplqwq (赞：0)

先说结论：每次从右往左删，得到的答案都是 $2$ ，一定是最优的。

证明如下：

- $\frac{2\times n-2}{2}=n-1$

- $\frac{2\times n}{2}=n$

- 由上面两条可知，对于 $n,n-1,n-2$可以合并成$n-1$ 。

- 因此，我们就剩下$1,2,3...n-1$ 。

- 之后继续合并，以此类推。

- 可得最后总能剩下 $1$ 和 $3$ 。

- 因此答案永远为 $2$ 。

因此可得代码，但记得特判当 $n=1$ 时输出 $1$。



---

## 作者：Allanljx (赞：0)

## 题意
 $t$ 次询问，对于每一次询问：给定 $n$ 个数，为$1,2,3...n$ ,每次可以选择两个数 $a,b$ 并删除，然后把 $(a+b)/2$ 向上取整，加入到这些数中。
## 思路
可以证明要么剩下$2$，要么剩下$1$。证明：每次取最大的两个 $n,n-1$ 后会剩下 $n$ ，再取 $n,n-2$ 会剩 $n-1$ ，以此类推，最后会剩下$1$和$3$，再取一次就会剩下$2$。

注意：需要特判为 $n$ 为$1$的情况。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n==1)//特判
		{
			cout<<"1\n1\n";
			continue;
		}
		cout<<2<<endl;//最后剩下的数
		for(int i=n;i>=2;i--)//从大往小取
		{
			if(i==n)//取n和n-1
			{
				cout<<i-1<<' '<<i<<endl;
			}
			else cout<<i-1<<' '<<i+1<<endl;//取n和n-2
		}
	}
    return 0;
}
```


---

## 作者：gzfls_zhy (赞：0)

# CF 1430C 的题解

[题目传送门](https://www.luogu.com.cn/problem/CF1430C)

## 三种STL解法的题解

### 第一部分：题目大意
翻译蛮详细了的：

给你一堆数，从1到n，每次任取两个数，求它们的平均值（上取整），问：

1、最后剩下的数的最小值

2、依次输出构造方案

### 第二部分：解题思路

首先，让我们分析一下最小值得情况：

任取几个数据，想一下剩下的最小值的情况：


```cpp
1 2 → 2
1 2 3 → 2
1 2 3 4 → 2
1 2 3 4 5 → 2
……
1 2 3 4 … n → 2
```

由此可得，剩下数的最小值一定为2

为什么呢？

想让最小值最小，也就是说让较大的数变小

也就是说，每次选择两个最大的数，求平均值（上取整），所得的结果一定是最小的

而分析一下数据，就举从1~5的数据吧：


```cpp
1 2 3 4 5
首先取最大值：4 5，序列变成：
1 2 3 5
然后，取最大值：3 5，序列变成：
1 2 4
接着，取最大值：2 4，序列变成：
1 3
最后，1与3的平均值为2
所以结果为2
```

分析这组数据，我们能发现：

1、每次取最大值然后平均后的数，结果仍是最大值

2、这个数值介于两个最大值之间

这意味着什么？

意味着最后的结果一定是1与2或这个1与3

所以结果一定为2

总结一下：

1、最小值一定为2

2、每次取最大的两个值，取平均值就可以AC了

再看一下标题，想到什么数据结构了？

### 第三部分：三种STL的AC代码

首先是最容易想到的优先队列（priority_queue）

优先队列中的数会自动排序

#### 优先队列的AC代码

```cpp
#include <iostream>
#include <queue>
using namespace std;
int main() {
    int times;
    cin >> times;
    while(times--){
        int n;
        cin >> n;
        cout << 2 << endl;
        priority_queue<int> q; 
        for(int i = 1;i <= n;i++){
            q.push(i);
        }
        for(int i = 1;i < n;i++){   
            int a = q.top();
            q.pop();
            int b = q.top();
            q.pop();
            cout << b << " " << a << endl;
            if((a + b) % 2 == 0){ //处理上取整
                q.push((a + b) / 2);
            }else{
                q.push((a + b) / 2 + 1);
            }
        }
    }
    return 0;
}
```
根据上面的数据分析，每次取最大值然后平均后的数，结果仍是最大值

所以，先进后出，想到什么STL了？

栈（stack），对吧？

#### 栈的AC代码

```cpp
#include <iostream>
#include <stack>
using namespace std;
int main() {
    int times;
    cin >> times;
    while(times--){
        int n;
        cin >> n;
        cout << 2 << endl;
        stack<int> q;
        for(int i = 1;i <= n;i++){
            q.push(i);
        }
        for(int i = 1;i < n;i++){   
            int a = q.top();
            q.pop();
            int b = q.top();
            q.pop();
            cout << b << " " << a << endl;
            if((a + b) % 2 == 0){
                q.push((a + b) / 2);
            }else{
                q.push((a + b) / 2 + 1);
            }
        }
    }
    return 0;
}
```
还有呢？

有人想到队列，但很明显，队列是不行的，因为队列的队首保存的是最小值

那有没有方法呢？

来吧，双向队列（deque）：

双向队列可以读队尾，也就是最大值

#### 双向队列的AC代码

```cpp
#include <iostream>
#include <deque>
using namespace std;
int main() {
    int times;
    cin >> times;
    while(times--){
        int n;
        cin >> n;
        cout << 2 << endl;
        deque<int> q;
        for(int i = 1;i <= n;i++){
            q.push_back(i);
        }
        for(int i = 1;i < n;i++){   
            int a = q.back();
            q.pop_back();
            int b = q.back();
            q.pop_back();
            cout << b << " " << a << endl;
            if((a + b) % 2 == 0){
                q.push_back((a + b) / 2);
            }else{
                q.push_back((a + b) / 2 + 1);
            }
        }
    }
    return 0;
}
```

最后：

[全部AC](https://www.luogu.com.cn/record/40808249)


最后，我的洛谷AC代码仓库（持续更新中）：[传送门](https://gzflszhy.coding.net/p/cpp-AC/d/luogu.com.cn/git)

感谢您看到最后

---

## 作者：FuriousC (赞：0)

通过题目我们可以发现$n$与$n-2$可以变成$n-1$，而$n-1$与$n-1$又可以变成$n-1$，所以$n$,$n-1$,$n-2$可以换成$n-1$，这时序列里剩下$1$,$2$,$3$....$n-3$,$n-1$。

所以在消除到最后时序列里只剩下$3$与$1$，即最优解永远为$2$.

而第二问定义一个双端队列（~~或用数组代替也行~~）就可以搞定了

废话不多说，上代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,n;
deque<int>b;
int main(){
    cin>>a;
    while(a--){
        cin>>n;
        cout<<2<<endl;//先输出2
        for(ll i=1;i<=n;i++){
            b.push_back(i);
        }
        for(ll i=1;i<=n-1;i++){
            ll l=b.back();
            b.pop_back();
            ll r=b.back();
            b.pop_back();
            cout<<r<<" "<<l<<end;//找到2个数(注意要反过来写)
            b.push_back(ceil(l+r)/2);//补回新的数
        }
    }
    return 0;
}
```
内置防抄袭错误，~~你发现了吗？~~


---

## 作者：do_while_true (赞：0)

[$\text{更佳的阅读体验}$](https://www.cnblogs.com/do-while-true/p/13799080.html)

# C. Numbers on Whiteboard

### Translate

$T$ 次询问，对于每一次询问：

给定 $n$ 个数，为 $1,2,3,...,n$，每次可以选择两个数 $a,b$ 并删除，然后把 $\left\lceil\frac{a+b}{2}\right\rceil$ 加入到这些数中。最小化最后剩下的一个数，输出这个数并且输出构造方案。

$2\leq n\leq 2\cdot10^5,\sum n \leq 2\cdot10^5$

### Solution

对于 $n=2$，剩下的最小数为 $2$，方案为合并 $1,2$。

对于 $n\geq 3$，~~我也不知道该怎么想出这个方法反正就是写写画画~~构造出这样一个方案:

把 $n$ 和 $n-1$ 合并成 $n$，留下 $n$。

然后就有规律了：

$n$ 和 $n-2$ 合并，留下 $n-1$。

$n-1$ 和 $n-3$ 合并，留下 $n-2$。

$n-2$ 和 $n-4$ 合并，留下 $n-3$

$...$

最后只剩下 $1$ 和 $3$ ，合并得到 $2$。故最后得到 $2$。

证明最小的剩下的数就是 $2$：反证法，因为得到 $1$ 必须有两个 $1$ ，而最多只会有一个 $1$，故剩下的数最小为 $2$。

### Code

```cpp
int n, k;
int a[N], cnt[N];
signed main() {
	int T = read();
	while(T--) {
		n = read();
		if(n == 2) {
			printf("2\n 1 2\n");
			continue;
		}
		printf("%d\n%d %d\n", 2, n, n - 1);
		int now = n;
		for(int i = 2; i < n; ++i) {
			printf("%d %d\n", now, now - 2);
			now = now - 1;
		}
	}
	return 0;
}
```

---

## 作者：dbodb (赞：0)

### 模拟题

手动模拟就可以发现规律

5 1 2 3 4 5

1. 3     5     队列变成   1 2 4 4
2.  4    4      队列变成   1 2 4 
3. 2      4     队列变成    1   3
4.  1     3      队列变成    2，也就是答案

开一个堆维护一下

第一步，选择第$n-2$和第$n$个数,对他们取平均数，压入堆中，

第二步，压入第$n-1$个数

第三步，选择堆顶元素和次堆顶元素，分别弹出，然后求他们平均数，并压入

最后的堆顶元素就是最终的答案

### 解释

每次对两个数进行操作，取他们的平均数，并向上取整

因为是向上取整，要让最后的数最小，每次应该选择两个数的和是2的倍数的，否则肯定会变大，答案一定不优

所以每次的操作，选择的两个数的和必定要是一个偶数。

### 详细见代码

```c++
#include<bits/stdc++.h>
using namespace std;
stack<int>s;
const int N=3e5;
int a[N],b[N]; 
int main()
{
	int t;
	cin>>t;
	for(int k=1;k<=t;k++)
	{
		int n;
		cin>>n;
		if(n>2)
		{
			a[1]=n-2;
			b[1]=n;
			for(int i=1;i<=n-3;i++)
			{
				s.push(i);	
			}		
			s.push(n-1);
			s.push(n-1);
			for(int i=2;i<=n-1;i++)
			{	
				int x=s.top();
				s.pop();
				int y=s.top();
				s.pop();
				a[i]=x;//记录操作的位置
				b[i]=y;//记录操作的位置
				s.push((x+y)/2);			
			}
			cout<<s.top()<<endl;
			for(int i=1;i<=n-1;i++)
				cout<<a[i]<<' '<<b[i]<<endl;
		}
		else {//特判
			cout<<2<<endl;
			cout<<1<<' '<<2<<endl;
		}
		while(s.size())s.pop();
	}
}
```

#### 注意特判

当元素就两个的时候，直接输出

```c++
cout<<2<<endl;
cout<<1<<' '<<2<<endl;
```





---

## 作者：vectorwyx (赞：0)

这道题卡了我好久，最后发现其实很简单，但是这种题想不到就是想不到:(

我们先把 $n$ 与 $n-1$ 合并成 $n$，再把 $n-2$ 和 $n$ 合并成 $n-1$，然后把 $n-3$ 和 $n-1$ 合并成 $n-2$……以此类推，最后得到的答案一定为 $2$。至于为什么 $2$ 是最小的，考虑 $a,b,\lceil \frac{a+b}{2} \rceil(a\le b)$ 的关系，显然有 $a\le \lceil \frac{a+b}{2} \rceil\le b$。所以与 $1$ 进行操作的数一定大于等于 $2$，所以答案一定不会是 $1$ 或 $0$。证毕。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

void work(){
	int n=read(),last=n;
	printf("2\n");
	go(i,n-1,1){
		printf("%d %d\n",i,last);
		last=ceil((i+last)/2.0);
	}
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

