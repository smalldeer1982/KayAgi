# [CERC2016] 自由的套娃 Free Figurines

## 题目描述

俄罗斯套娃是一些尺寸递增的木制雕像，它们可以嵌套在一起。每个套娃可以放进一个更大的套娃，也可以被放入一个更小的套娃。每个套娃内部最多只能直接嵌套一个套娃，但是那个套娃内部还可以继续嵌套。


给定n个尺寸互不相同的套娃，按尺寸从小到大依次编号为1到n。如果套娃a被直接嵌入套娃b，那么我们称b是a的父亲，如果一个套娃没有父亲，那么我们称它是自由的。一组镶嵌方案可以用每个套娃的父亲来表示。


我们可以每步可以做以下两种操作中的任意一种：


1.把一个自由的套娃直接嵌入一个更大的没有被放入东西的套娃。


2.选择一个不自由的套娃，将其从其父亲中取出。


给定初始局面，请计算达到目标局面的最小的操作步数。


## 样例 #1

### 输入

```
7
3 5 4 0 7 0 0
3 5 0 6 7 0 0
```

### 输出

```
2```

# 题解

## 作者：RiverHamster (赞：6)

这题主要要把套娃的拆开合并的方式模拟清楚，手动模拟一下会简单很多。

首先我们考虑一种**最简单**的完成任务的方法：把套娃全部拆开，然后再合并成所要求的样子，那么原来有父亲的都要拆开一次，把最后要求有父亲的都合并一次。

显然这样**不是最优解**，原来和现在状态都一样的，我们就不必拆开。一个例子：$5$个套娃连成这样的形状（套娃的关系用链表示）：（$1$最小，$5$最大）
$$1-2-3-4-5$$
假设我们要拆出$3$，其他的不变，得到如下的形状：
$$1-2-4-5\quad 3$$
那么$1-2$显然不用拆开，但$4-5$需要拆开来再装上，才能拿出$3$，那么我们的步骤就是：拆掉$5$，拆掉$4$，拆掉$3$，拼上$4$，拼上$5$，共$5$步

我们发现，在一条链中，我们**只能保留最小的一部分，其他只要有所更改，套娃更大的部分就不能保留（要拆开才能能取到里面）。因此找出每条链最小的部分就是不用拆开的部分**（如这个例子中的$1-2$），两个套娃不用拆开，就可以把原来做法的答案减$2$（拆开一次，拼上一次），就可以最优化答案了。实际操作时，找到在原始状态和目标状态中都是最小的套娃开始向大的去找，直到发现不同就可以了

时间复杂度$O(n)$

code:
```cpp
#include <cstdio>

int a[100005], b[100005];
bool ntail[100005]; //表示i不是链的结尾

int main(){
    int n, ans = 0;
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
		scanf("%d", &a[i]);
		ntail[a[i]] = true; //已经不是链的结尾（最小的套娃）了
		if(a[i] != 0) ans++; //原始做法
	}
    for(int i=1; i<=n; i++){ //同上
    	scanf("%d", &b[i]);
    	ntail[b[i]] = true;
    	if(b[i] != 0) ans++;
	}
	int p;
	for(int i=1; i<=n; i++){
		if(!ntail[i]){ //是链尾
			p = i;
			while(a[p] == b[p] && a[p] != 0 && b[p] != 0){ //一直找相同（可以不拆开的）
				ans -= 2; //避免2次操作
				p = a[p];
			}
		}
	}
    printf("%d\n", ans);
    return 0;
} 

```

思路来自:
[官方题解](http://cerc.hsin.hr/2016/tasks/cerc2016_presentation.pdf) [BlackJack_的博客](https://blog.csdn.net/BlackJack_/article/details/77939368)

---

## 作者：ModestCoder_ (赞：4)

思维题

考虑一个套路：从最差情况一步步优化到最优情况

所以本题的做法是这样的：对于每个有父亲的套娃，花费1把它取出来；对于每个将要放到某个套娃里的花费1把它放进去

发现有那么一段连续的套娃相对之间不需要移动，这是冗余操作，减掉即可

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 100010
using namespace std;
int n, a[maxn], b[maxn], tail[maxn], ans;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read();
	for (int i = 1; i <= n; ++i) tail[a[i] = read()] = 1;
	for (int i = 1; i <= n; ++i) tail[b[i] = read()] = 1;
	for (int i = 1; i <= n; ++i){
		if (a[i]) ++ans;
		if (b[i]) ++ans;
		if (!tail[i]){
			int x = i;
			while (a[x] == b[x] && a[x]) ans -= 2, x = a[x];
		}
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：zhengjinyi (赞：2)

题解区好像全都是考虑非最优做法然后优化，这里提供一种不一样的做法。\
当我们想要改变一个节点的 $p_i$ 时，显然需要操作其所有祖先。操作过一个节点后，我们可以直接将它的父亲设为 $0$，避免它再次被操作。\
由于 $p_i>i$，只需正序扫一遍进行操作即可。\
然后对于所有和 $p_i$ 不等的 $q_i$，对 $q_i$ 及其祖先进行类似操作。最后拼起来将答案加 $1$ 即可。

Code:
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define R read()
using namespace std;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}
const int INF=0x3f3f3f3f,N=100005;
int p[N],q[N],n,ans;
int main(){
	n=R;
	for(int i=1;i<=n;i++) p[i]=R;
	for(int i=1;i<=n;i++) q[i]=R;
	for(int i=1;i<=n;i++){ //拆
		if(p[i]^q[i]){
			int x=i,t;
			while(p[x])
				ans++,t=x,x=p[x],p[t]=0;
		}
	}
	for(int i=1;i<=n;i++){ //拆+拼
		if(p[i]^q[i]){
			int x=q[i],t;
			while(p[x])
				ans++,t=x,x=p[x],p[t]=0;
			ans++,p[i]=q[i];
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：_Delete_ (赞：0)

## 思路

在不考虑最小操作步数时，显然有一种必完成的方法是将所有套娃拆开再按照给定的方式拼回去。

考虑优化:如果有一段连续的套娃是和目标套娃是相同的，则可省去部分操作。每有两个套娃与目标顺序相同，则可省去一开一关两次操作。

按照上述描述进行模拟即可。

## 代码


```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 
int a[2000005],b[2000005],t[2000005];

//function 

 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	
	for(int i=1;i<=n;i++)t[a[i]]=t[b[i]]=1;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i]!=0)ans++;
		if(b[i]!=0)ans++;
		if(t[i]==0){
			int e=i;
			while(a[e]==b[e] && a[e]!=0 && b[e]!=0){
				ans-=2;
				e=a[e];
			}
		}
	}
	cout<<ans<<endl;
	
	return 0;
}
```

---

## 作者：Llx2022 (赞：0)

# 题目描述

$n$ 个互不相同的套娃，按尺寸**从小到大**依次编号为 $1$ 到 $n$。每个套娃有父亲或已经是最外层套娃。给定**初始局面**和**目标局面**，计算达到目标局面的**最小**的操作步数。

# 思路
先模拟一下，发现正常操作肯定是与目标相同的不动，不同的就进行操作。显然操作只与最外层套娃有关。所以这道题目我们可以考虑**从外往里拨开套娃**，找到最外层的套娃。最外层的套娃有可能是初始局面的自由套娃，也有可能是目标局面的自由套娃。我们可以遍历每一个套娃，**找到没有被包含在任何一个套娃中的套娃**，也就是最外层的套娃。**对于每一个最外层的套娃**，我们可以不断地拨开它的父亲，直到初始局面和目标局面的父亲不同或者拨开到了最底层。每次拨开套娃的过程中，需要进行的操作次数为 $2$，**一次是取出和一次是插入**。所以我们统计每个最外层套娃拨开的次数，**答案**就是每个最外层套娃拨开次数的总和。
# CODE
```cpp
#include <stdio.h>
template<typename T>inline int read(T &x){
	x=0;T f=1;char ch=getchar();
	while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=getchar();}
	while(ch>=48&&ch<=57){x=x*10+ch-48;ch=getchar();}
	return x*=f;
}
template<typename T>inline void write(T x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
const int N=1E5+9;
int start[N],end[N];
int in[N];
int n,ans;
int main(){
    read(n);
    for(int i=1;i<=n;i++){
        in[read(start[i])]=true;
    }
    for(int i=1;i<=n;i++){
        in[read(end[i])]=true;
    }
    for(int i=1;i<=n;i++){
        if(start[i]) ans++;
        if(end[i]) ans++;
        //找到最外层套娃,一层层拨开
        if(!in[i]){
            int x=i;
            while(start[x]==end[x]&&start[x]) ans-=2,x=start[x];
        }
    }
    write(ans);
    return 0;
}
```



---

## 作者：a326820068122c (赞：0)

### 分析
先明确一下题面内容:

>我们可以每步可以做以下两种操作中的任意一种：

>1.把一个自由的套娃直接嵌入一个更大的没有被放入东西的套娃。

>2.选择一个不自由的套娃，将其从其父亲中取出。

其实更准确说题面应该是这个意思：

>我们可以每步可以做以下两种操作中的任意一种：

>1.把一个自由的套娃直接嵌入一个更大的没有被放入东西的自由套娃。

>2.选择一个不自由的套娃，将其从其是自由套娃的父亲中取出。

（与真实的套娃差不多）

为了方便理解，分析一下这组样例：
```
5
0 3 4 0 0
2 3 4 0 0
```
最优操作步骤（$a \rightarrow b$ 表示将 $a$ 放入 $b$ 中，特别的当 $b=0$ 时为将其拿出）：
```
3->0
2->0
1->2
2->3
3->4
```
所以答案应该是 $5$。

由于 $2$ 套娃开始时不是自由的，所以不能直接将其取出。

### 解法
这题可以用 dp 求解。

可以发现如果一个套娃即其内部结构在初始和末尾状态相同，它是不用拿出来其中的套娃的。

反之，如果一个套娃如果内部结构不同，一定要拿出其中的套娃（没有则不拿）。

（这里的内部结构相同指其内部每个套娃的儿子完全相同）

如果初末结构不同的一个套娃开始内部有套娃则需要操作拿出，如果初末结构不同的一个套娃结束内部有套娃则需要操作拿入。

于是就可以现处理开始状态和结束状态每个套娃的儿子。

然后 dp 出内部结构是否相同。

最后看每个套娃是否需要拆装

### 代码
```cpp
#include <bits/stdc++.h>
#define for1(i,n) for(i=1;i<=(n);i++)
using namespace std;
const int N=100005;
int n,a[N],c[N],ans,f[N],t[N];
bool b[N];
int main(){
	int i;
	scanf("%d",&n);
	for1(i,n) scanf("%d",&a[i]),f[a[i]]=i;
	for1(i,n) scanf("%d",&c[i]),t[c[i]]=i;
	b[0]=1;
	for1(i,n){
		b[i]=f[i]==t[i]&&b[f[i]];
		if(!b[i]&&f[i]) ans++;
		if(!b[i]&&t[i]) ans++;
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：TachibanaKanade (赞：0)

思维难度题，码量很小。

考虑将这组套娃用一组链表来表示。

若 $x$ 指向 $y$，则表示套娃 $x$ 里面包含套娃 $y$。

那么这个时候看所给的两种操作：

操作 $1$ 其实就相当于这个节点放在链表的开头。

操作 $2$ 其实就相当于把链表的开头去掉。

那么很容易发现，两种操作均在链表的开头进行。换而言之，我们的思路就是从链表的尾部开始确定。

再换而言之，我们的最优策略即是保留初始局面与目标局面的尾部（即从小到大排序中靠前的部分）相同部分。

那么对于不同的部分，则必须把套娃拆开才能放到里面，这就是我们要统计的花费。

而对于尾部的相同部分无需操作，那么对于这样的两个相邻而不用拆开的套娃则直接把统计的操作步数减 $2$ 即可。

从而思路就很明显了：从初始局面和目标局面都是最小的套娃开始分别往比它更大的套娃找，相同则减去 $2$ 次操作，直到发现不同即可。

代码就不贴了。

---

## 作者：Rose_Melody (赞：0)

## Solution - P3682 自由的套娃

[题目传送门](https://www.luogu.com.cn/problem/P3682)

### 题目分析

对于这道题，我们可以手动模拟套娃的**拆开**及**合并**的方法，就能迎刃而解。

考虑从普通情况进行优化。

本题的思维是这样的：对于每个有父亲的套娃，花费 $1$ 次机会把它取出来；对于每个将要放到另外套娃里的花费 $1$ 次把它放进去。

若中间有连续的套娃不用全拆出来，对于每次这样的操作，减去即可。
### AC 代码


```cpp
//P3682 
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e5 + 10;
int a[N] , b[N]; 
bool u[N] ;
int n, ans = 0;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
        ios::sync_with_stdio(false);
        cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i ++){
		cin >> a[i];
		u[a[i]] = 1;
		if(a[i]) ans ++;
	}
	for(int i = 1;i <= n;i ++){
		cin >> b[i];
		u[b[i]] = 1;
		if(b[i]) ans ++;
	}
	int cnt ;
	for(int i = 1;i <= n;i ++){
		if(! u[i]){
			cnt = i;
			while(a[cnt] == b[cnt] && a[cnt] && b[cnt] ){ 
				ans -= 2; 
				cnt = a[cnt];
			}
		}
	}
	cout << ans ;
    return 0;
}

```

---

