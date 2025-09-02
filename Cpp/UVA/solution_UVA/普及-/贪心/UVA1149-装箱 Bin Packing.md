# 装箱 Bin Packing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3590

[PDF](https://uva.onlinejudge.org/external/11/p1149.pdf)

# 题解

## 作者：AgrumeStly (赞：7)

做法显然：贪心，但是怎么贪？

1. 首先从大到小或从小到大排序，窝这次是从大到小排，这样更容易理解（从小到大更方变）

2. 然后设置两个变量 `front` 和 `after` 作为前指针和后指针。

3. 循环判断：

	- 当前后两个数能放入背包时，则 `ans++` 并把两指针：

		```cpp
    	front++;
    	after--;
    	```
    - 当不能同时放入时，放进大的那个，也就是前面的那个，并且 `ans++, front++;` 
    
最后看一下code：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int NR = 1e5 + 5;
int t, n, m, v[NR], front, after, ans;
bool cmp(int x, int y)
{
	return x > y;
}
void Initialization()//每组数据前后初始化
{
	memset(v, 0, sizeof(v));//清零
	n = 0;
	m = 0;
	front = 1;
	after = 0;
	ans = 0;
}
void Cin()//每组数据的输入
{
	cin >> n >> m;
		for (int i = 1; i <= n; i++)
			cin >> v[i];
	after = n;
}
int main()
{
	cin >> t;
	Initialization();//初始化
	for (int T = 1; T <= t; T++)
	{
		Cin();//输入
		sort(v + 1, v + n + 1, cmp);//排序
		for (int i = 1; i <= n; i++)//循环n次，因为最多分配n次，不会超过n次
			if (front >= after)//如果前指针已经超过或等于后指针时说明已经结束,所以结束循环
			{
				ans++;
				cout << ans << endl;//输出答案
				Initialization();//初始化
				break;
			}
			else if (v[front] + v[after] <= m)
			{//如果前后两个物品能放下
				ans++;
				front++;//前指针向后移
				after--;//后指针向前移
			}
			else
			{//否则的话
				ans++;
				front++;//只有前指针向后移
			}
	}
	return 0;
}

```


~~求赞ฅʕ•̫͡•ʔฅ~~

---

## 作者：Altwilio (赞：5)

可以感觉到此题为裸的**贪心**，
并且本题标签为贪心，考虑贪心。

------------

首先翻译题目(输入输出格式一定要注意）：
1. 有 $n$ 个物品，将物品放入包裹中，一个包裹中只能放 $2$ 个物品，每个包裹最多只能放 $w$的重量。
1. 输入一个 $y$ 代表多组数据。
1. 输入 $n$ 和 $w$ , 是需要装入箱子中的个数。
1. 接下来输入 $n$ 行 $v$ ,代表每个物品的重量。


------------

每组数据处理的大致思路如下：
1. 将物品按大小从小到大排序。
1. 尝试第一个和最后一个物品是否能放到同一个包裹中。
1. 如果最后一个物品过大，就把最后一个物品单独放。
1. 重复执行直到处理完全部物品。


------------
实现思路：考虑双指针算法，一个从队头向后移动，一个从队尾向前移动，
前提是队列为单调的，可以实现贪心。
对此有两个题目的思路类似:
1. [P1650](https://www.luogu.com.cn/problem/P1650)
1. [P3918](https://www.luogu.com.cn/problem/P3918)

### ACcode

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t, w, n, ans;
	int i, j;							//此处 i, j 为两个指针 
    int a[100005];
    scanf("%d", &t);					//读入测试数据组数
  
    for(int k = 0; k < t; k ++){		//多组数据的读入方式
        scanf("%d%d", &n, &w);
        for(i = 0; i < n; i ++)
            scanf("%d", &a[i]);
            
  		sort(a, a + n);					//排序函数，不会可以自学 
        ans = i = 0; 
        j=n - 1;						//排序及初始化
  										
        while(i <= j){					//循环条件为两个指针不相遇 
            while(a[j] + a[i] > w && i <= j){
                ans ++; j --;   		//两个放不下就单独放
            }							//j 指针左移 
            i ++; j --; ans ++;			//i 右移，j 左移 
        }	
        								//贪心过程
        printf("%d\n", ans);
        if(k != t - 1)
            printf("\n");  				//调整输出格式
    }									//对于 UVA 的题，格式比较重要 
	return 0;
}
```
希望能过呢，卖萌！

---

## 作者：fls233666 (赞：4)

先看一道普及组中非常经典的**贪心**题：[P1094 纪念品分组](https://www.luogu.org/problemnew/show/P1094)

经过对比确认，这两题是**几乎一样**的！

唯一不同的是这题是多组数据处理，P1094是单组数据处理。

每组数据处理的大致思路如下：

1. 把物品按大小从小到大排序一遍
2. 尝试第一个和最后一个物品是否能放到同一个包裹中
3. 如果最后一个物品过大，就把最后一个物品单独放
4. 重复执行直到处理完全部物品

Q:为什么是在排序后的物品两端依次尝试？

A:**排序后两端的物品一个是最大一个是最小，如果能放进一个包裹中，一定能使包裹剩余空间最小。这就达到了贪心的目的。**

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	int test,w,n,ans,i,j;
    int p[100010];
    scanf("%d",&test);//读入测试数据组数
  
    for(int ti=0;ti<test;ti++){
        scanf("%d%d",&n,&w);
        for(i=0;i<n;i++)
            scanf("%d",&p[i]);
  //读入每组的数据
  
        ans=i=0; sort(p,p+n);
        j=n-1;
  //排序及初始化
  
        while(i<=j){
            while(p[j]+p[i]>w&&i<=j){
                ans++;   
                j--;   //两个放不下就单独放
            }
            i++;
            j--;
            ans++;
        }
        //贪心过程
                                     
        printf("%d\n",ans);
        if(ti!=test-1)
            printf("\n");  //调整输出格式
    }
	return 0;
}
```


---

## 作者：odt63 (赞：1)

看一眼~~算法标签~~就知道了是贪心

ps:文章翻译有些错误

>最后一行是包裹的容量

应该是

>第二行是包裹的容量

# 解题思路

- 对物品数组按**体积**由大往小排序

- 用两个变量当前指针和后指针

- 如果第一个和最后一个能装到箱子里，计数器 $+1$ ，前指针向后挪一位，后指针向前挪一位。否则只能装大的，计数器 $+1$ ，并且**前指针要向后挪一位**。

- 重复循环直到前指针大于或等于后指针，输出结果。

# 流程图(自己做的，有点丑)

![](https://s4.ax1x.com/2021/12/25/TU8R3t.png)

# 献上代码

核心代码

```cpp
cin>>n;
memset(V,0,sizeof(V));
p1=1,p2=n,cnt=0;
初始化
cin>>v;
for(int i=1;i<=n;i++){
    cin>>V[i];
}
数据输入
sort(V+1,V+n+1,greater<int>()); 排序
while(true){ 循环处理
    if(p1==p2||p1>p2){ 结束了
    	cnt++;  因为还有物品没装所以++
        cout<<cnt<<endl; 输出解
        break;
    }
    if(V[p1]+V[p2]<=v){ 装得下两个
        cnt++;
        p1++,p2--;
    }
    else{  只能装大的
        cnt++;
        p1++;
    }
}
```

完整代码

[这里](https://www.luogu.com.cn/paste/mvw6v972)

~~Warning:有防抄袭手段,请勿抄袭!~~

谢谢！

---

## 作者：luozhichen (赞：0)

[题目直通车](https://www.luogu.com.cn/problem/UVA1149)


## 做法:

贪心。怎么贪?(~~用手贪啊~~）

我们首先把这个数组排一下序，然后看第一个(也就是最小的)能加上后面的吗?如果可以，就看最大能装到哪个。一直到数组内数字全部被包完。这样就能保证是最优的。或者从后面开始往前面，看能加到哪个最大的就可以了。

## 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main (){
	cin >> t;
	for(int tt = 1;tt <= t;tt++){//t组数据
		int a[300005];
		int w,n;
		cin >> n >> w;
		for(int i = 0;i < n;i++){
			cin >> a[i];
		}
		sort(a,a + n);
		int b = 0,c = n - 1;
		int ans = 0;
		while(b <= c){//从最前面开始
			if(a[b] + a[c] <= w){//看最大能加到哪
				b++;
				c--;
				ans++;
			}else{
				c--;
				ans++;
			}
		}
		cout << ans << endl;//注意
		if(tt != t){
			cout << endl;//注意
		}
	}
	return 0;
}
```


---

## 作者：happybob (赞：0)

搞半天调不出来，也想不出哪错了，直到看到题解才发现原来格式……。

先说一下翻译的问题，不是最后一行是背包容量，而是第二行就是背包容量了。

贪心思路：先将 $n$ 个数从小到大排序，头尾分别设两个变量 $l, r$ 模拟，当 $a_l + a_r \le w$ 时，计数器加一， `l++`，`r--`，如果不是这样的话，我们知道 $a_l + a_r > w$，而 $a_{l+1}$ 一直到 $a_n$ 都比 $a_l$ 大，因为是排序过的，所以我们只能把 $a_r$ 自己分一组。

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while (T--)
	{
		int* a = new int[N];
		int n, cnt = 0, v;
		cin >> n >> v;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		sort(a + 1, a + n + 1);
		int l = 1, r = n;
		while (l <= r)
		{
			if (l == r)
			{
				cnt++;
				break;
			}
			else
			{
				cnt++;
				if (int s = a[l] + a[r]; s <= v) // c++17 特性，在if和switch里也可以定义变量
				{
					r--;
					l++;
				}
				else
				{
					r--;
				}
			}
		}
		// 注意下面
		cout << cnt << endl; 
		if (T)
		{
			cout << endl;
		}
		delete[] a;
	}
	return 0;
}
```


---

## 作者：Chloris (赞：0)

贪心即可

获得的长度排一个序，我们考虑贪心策略是一大一小搭配放，用头尾两个指针维护，如果超出就用两个袋子否则只用一个袋子

ps:注意输出格式

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#define INF (0x3f3f3f3f)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define REP(i, x, y)  for(int i = (int)x; i <= (int)y; i ++)
#define FOR(i, x, y)  for(int i = (int)x; i <  (int)y; i ++)
#define PER(i, x, y)  for(int i = (int)x; i >= (int)y; i --)
using namespace std;
const int N = 1e5 + 10;
int T, n, m, len[N];


void input(int &t){
	int n = 0, m = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') m = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { n = (n << 3) + (n << 1) + ch - 48; ch = getchar(); }
	t = n * m; return;
}
int main(){
	int last;
	input(T);
	while(T--){
		int cnt = 0;
		input(n), input(m);
		if(n == 1){
			printf("1");
			continue;
		}
		REP(i, 1, n) input(len[i]);
		sort(len + 1, len + n + 1);
		int head = 1, tail = n;
		while(head <= tail){
			if(head == tail){
				cnt++; break;
			}
			if(len[head] + len[tail] <= m){
				cnt++, head++, tail--; 
			}
			else{
				cnt++, tail--;
			}
		}
		printf("%d\n", cnt);
		if(T) printf("\n");
	}
	return 0;
}
```

---

