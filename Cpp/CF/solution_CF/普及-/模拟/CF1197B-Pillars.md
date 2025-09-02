# Pillars

## 题目描述

**题意**

给定$n$个盘子，盘子的半径是$1$到$n$

现在的有$n$个柱子，每个柱子上有一个盘子，问时候能够把所有的盘子移动到一个柱子上

如果要把一个盘子从柱子$i$移动到柱子$j$则要求
1. 柱子$i$上只有一个盘子
2. 柱子$j$上没有盘子，或盘子的半径大于柱子$i$上的盘子
3. $i$，$j$必须相邻

## 说明/提示

$3\le n\le 2e5$

$1\le a_i\le n$

## 样例 #1

### 输入

```
4
1 3 4 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
3 1 2
```

### 输出

```
NO
```

# 题解

## 作者：pxy1118 (赞：4)

我们观察样例：

------------


### 4

### 1 3 4 2


------------

### 3

### 3 1 2


------------
样例1的输入数据是 **先递增后递减** 的（是不是像一座山）

样例2的输入数据是 **先递减后递增** 的（是不是像一个盆地）

感性理解一下，便可以提出一个大胆的猜想：

只要输入出现 **先递减后递增** 的情况一律输出**NO**

否则输出**YES**
下面是简洁的代码
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define N 200010
using namespace std;
int n;
int a[N];
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    int ok=0;
    for(int i=1;i<n;i++){
        if(a[i]<a[i-1]&&ok==0)ok=1;
        if(ok){
            if(a[i]>a[i-1]){
                printf("NO\n");
                return 0;
            }
        }
    }
    printf("YES\n");
    return 0;
}
```

---

## 作者：Eismcs (赞：3)

结论题，找一下规律即可。

明显的能看出每个圆盘要想移动，两边必须已经移动走了，或者半径为最大值，作为底座。

所以贪心，把半径越大的越先移动（必须让最终杆上的半径由下往上递减），并标记此杆已空，可以移动。

用了优先队列~~其实不用更简单~~
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
struct book{
	int x,i;
	bool friend operator <(book xx,book yy){
		return xx.x<yy.x;//重载运算
	}
};
priority_queue<book>dl;
bool b[200005];//标记数组
signed main(){
    int n=read(),u,la,w=-(1<<30);
    for(int i=1;i<=n;i++){
    	u=read();dl.push((book){u,i});
    }
    la=0;
    while(!dl.empty()){
    	book y=dl.top();dl.pop();
    	if(la==0){
    		la=y.i;w=y.x;b[la]=1;continue;
    	}
    	if(b[y.i+1]==0&&b[y.i-1]==0){//做相邻两个都比自己小，那么肯定移不了。
    		printf("No\n");return 0;
    	}
    	if(w==y.x){//相等最终无法满足严格递减
    		printf("No\n");return 0;
    	}
    	la=y.i;w=y.x;b[la]=1;//标记
    }
    printf("Yes\n");
    return 0;
}
```


---

## 作者：初雪_matt (赞：2)

## 简化题意

给定 $a$ 序列表示半径，$h$ 序列表示盘子个数，最开始 $h_i \leftarrow 1$，保证 $\forall a_i \le n$。

定义要求当 $h_i \not =0$ 时 $\left| i-j \right|=1$，$h_j=0 \texttt{ or } a_j>a_i$ 且 $h_i=1$ 即可以完成 $h_j \leftarrow h_j+1$ 的操作，求是否存在一个 $k$ 经过若干次操作后使得 $h_k=n$。

## 思路

对于要找到的 $k$，可以分左右讨论。

需要满足 $a_1<a_2<...<a_{k-1}<a_k$，因为这样才能将所有 $h_\texttt{左边区间}$ 转移到 $h_k$，否则必然不满足移动条件。

需要满足 $a_k>a_{k+1}>...>a_{n-1}>a_n$，因为这样才能将所有 $h_\texttt{右边区间}$ 转移到 $h_k$，否则必然不满足移动条件。

综上所述，需满足 $\max\{a_1,a_2,...,a_n\}=a_k$，$a_1<a_2<...<a_{k-1}<a_k$ 且 $a_k>a_{k+1}>...>a_{n-1}>a_n$，才能找到 $k$。即可以找到存在一个 $k$ 经过若干次操作后使得 $h_k=n$ 的方案。

## 代码

```py
n=int(input())
l=list(map(int,input().split()))
b=l[:l.index(max(l))]//左半边区间
c=l[l.index(max(l)):]//右半边区间
if sorted(b)==b and sorted(c,reverse=1)==c://是否满足条件
    print("YES")
else:
    print("NO")
```

---

## 作者：Waddles (赞：2)

~~思路是瞎搞~~

因为题目的限制，所以肯定要从n到1处理每个盘

每处理一个盘，看他到n的距离之间是不是只有比它大的盘，如果有小的，打NO，如果暴力判断，会T，所以开两个变量x,y存一下n左右各有多少已处理过的盘，然后一个贪心就省去一重循环了

code:

```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
template<class Read>void in(Read &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
int n,x,y,v[200005],a[200005];
int main(){
	in(n);
	for(int i=1;i<=n;i++)in(a[i]),v[a[i]]=i;
	if(abs(v[n]-v[n-1])!=1){
		puts("NO");
		return 0;
	}
	if(v[n-1]<v[n])x++;//n-1特判一下
	else y++;
	for(int i=n-2;i>=1;i--){
		if(abs(v[i]-v[n])>n-i){//如果之间距离大于处理过的数量，肯定有比它小的在其中
			puts("NO");
			return 0;
		}
		int s=v[i]>v[n]?-1:1;//看一下在n左还是右
		if(s==1){//在右
			if(x!=v[n]-v[i]-1){//必须是等于，不阔冷出现小于，因为如果小于在前面就打NO了（小于说明有大数在小数到n方向的异侧，在前面处理大数的时候显然不合法）
				puts("NO");
				return 0;
			}
		}
		else{//在左
			if(y!=v[i]-v[n]-1){
				puts("NO");
				return 0;
			}
		}
		if(s==1)x++;//统计个数
		else y++;
	}
	puts("YES");
	return 0;
}
```

---

## 作者：yizr_cnyali (赞：1)

观察数据可以得知，如果盘子的半径先递增再递减，那么把所有的盘子移动到一个柱子上就是可能的，否则不可能。    
在这里我们可以利用STL中的```max_element()```和```is_sorted()```这两个函数来判断。```max_element()```函数会返回指向输入区间中的最大值的迭代器/下标，```is_sorted()```函数默认会判断所给区间中的数是否按升序排序,是则返回```true```,否则返回```false```。
```cpp
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
 
using namespace std;
 
template <typename T> inline int Chkmax (T &a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline int Chkmin (T &a, T b) { return a > b ? a = b, 1 : 0; }
 
template <typename T> inline T read(){
    T sum = 0;
    int fl = 1,ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') fl = -1;
    for(; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + ch - '0';
    return sum * fl;
}
 
const int maxn = 200000 + 5;
 
int n,a[maxn];
 
int main(){
    n = read<int>();
    for(int i = 0; i < n ; i++){
        a[i] = read<int>();	
    }
    int len = max_element(a,a + n) - a;
    if(is_sorted(a,a + len) && is_sorted(a + len + 1, a + n,greater<int>())){
        printf("YES\n");
        return 0;
    }printf("NO\n");
    return 0;
}
```

---

## 作者：Lemonlwl (赞：0)

## CF1197B Pillars 题解
### 题意：
给定 $n$ 个柱子和 $n$ 个盘子，一开始每个柱子上都有一个盘子，你可以通过移动的方式，将一个半径为 $a_i$ 的盘子移动到柱子 $j$ 上，前提是，保证 $i$ 与 $j$ 相邻，且柱子顶端的盘子半径必须大于 $a_i$ 或柱子上无盘子，问能否将这 $n$ 个盘子移动到同一根柱子上。

------------

### 分析：
根据柱子顶端的盘子半径必须大于 $a_i$ 可知，若一个盘子其相邻的两个柱子上的盘子半径如果都大于这个盘子的半径，则与之相邻的两个盘子一定不能到达相隔 $i$ 的另一边。

因此，我们只需要判断是否有一个盘子其相邻的两个柱子上的盘子半径都大于这个盘子的半径的情况，如果是，则输出 `NO` 否则输出 `YES` 结束。

------------

附上 [AC](https://www.luogu.com.cn/record/125140767) 代码：
```cpp
#include<iostream>
using namespace std;
int n;
int a[1000005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}  //输入。
	for(int i=1;i<=n;i++){
		if(a[i]<a[i-1] && a[i]<a[i+1]){  //一个盘子其相邻的两个柱子上的盘子半径都大于这个盘子的半径。
			cout<<"NO"<<endl;  //输出。
			return 0;  //结束。
		}
	}
	cout<<"YES"<<endl;  //无上述情况，输出。
	return 0;
}
```


---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1197B)

## 题目大意

给定 $n$ 个盘子，盘子的半径是 $1$ 到 $n$。

现在的有 $n$ 个柱子，每个柱子上有一个盘子，问时候能够把所有的盘子移动到一个柱子上。

如果要把一个盘子从柱子 $i$ 移动到柱子 $j$ 则要求:

- 柱子 $i$ 上只有一个盘子

- 柱子 $j$ 上没有盘子，或盘子的半径大于柱子 $i$ 上的盘子

- $i,j$ 必须相邻

## 分析

因为把盘子移到另一个柱子上要 $i$ 的半径要比 $j$ 小。所以可以把所以的移动到一起那么那个柱子上的肯定最大。且要严格递增。

那么输出 ```YES``` 就只有 $2$ 种情况:

- 先递增然后递减。

- 一直递增。

其他情况都输出 ```NO```。

## 下面是 AC 代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	int a[200000];
	cin>>n;
	bool s1=false,s=false;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		
	}
	for(int i=1;i<n;i++)
	{
		if(a[i]<a[i-1])
		{
			s1=true;
		}
		if(s1==true)
		{
			if(a[i]>a[i-1])
			{
				cout<<"NO";
				return 0;
			}
		}
	}
	cout<<"YES";
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 题目描述

[洛谷传送门](https://www.luogu.com.cn/problem/CF1197B)

[CF 传送门](https://codeforces.com/problemset/problem/1197/B)

## 算法思路

因为盘子一定是从大到小的顺序移动到半径最大的盘子上，当一个盘子在移动到最大盘子的过程中，被一个更小的盘子挡住，就永远无法移动到最大盘子上，也就无法达到题目的要求。

所以如果盘子的半径先递增再递减，那么就能把所有的盘子移动到一个柱子上，否则不能。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
const ll N=200010;
ll n,a[N],maxx,maxxid;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>maxx)//找最大值的位置 
		{
			maxx=a[i];
			maxxid=i;
		}
	}
	for(int i=2;i<=n;i++)
	{
		if(i<=maxxid)//如果在最大值前面 
		{
			if(a[i-1]>=a[i])//如果下降 
			{
				cout<<"NO\n";//不合法 
				return 0;
			}
		}
		else//如果在最大值后面
		{
			if(a[i-1]<=a[i])//如果上升 
			{
				cout<<"NO\n";//不合法 
				return 0;
			}
		}
	}
	cout<<"YES\n";//合法 
	return 0;
}
```

---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1197B)

# 思路：找规律

如果是先递减后递增的情况，则考虑半径最小的那个盘子，他往哪边转移都不行，最终都会有叠不上去的情况，所以只需要单独判断一下这种情况就行了。


AC 代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,a[N];
int main()
{
    bool flag=0;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<=n;i++)
    {
        if(a[i-1]>a[i])flag=1;
        if(flag)
        {
            if(a[i]>a[i-1])
            {
                cout<<"NO"<<endl;
                return 0;
            }
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/113244101)

---

## 作者：lmndiscyhyzdxss (赞：0)

## 题目大意
给定 $ n $ 个盘子，盘子的半径是 $ 1 $ 到 $ n $。

现在的有 $ n $ 个柱子，每个柱子上有一个盘子，问时候能够把所有的盘子移动到一个柱子上。

如果要把一个盘子从柱子 $ i $ 移动到柱子 $ j $ 则要求：
1. 柱子 $ i $ 上只有一个盘子
2. 柱子 $ j $ 上没有盘子，或盘子的半径大于柱子 $ i $ 上的盘子
3.  $ i $，$ j $ 必须相邻
## 题目分析
因为，如果要往一个柱子上移盘子，这个盘子的半径就一定要小于柱子上盘子的半径，如果数据出现了先下降后上升的情况，那个最小盘子柱子的左右就无法往那个柱子上移动盘子，也就无法跨越它，被它挡住，不能到达最大盘子的柱子，所以，只要遇上这种情况，就不行，否则就可以。 
## AC 代码
```cpp 
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],p;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=2;i<=n;i++)
	{
        if(a[i]<a[i-1])p=1;//判断下降
        if(p==1)
		{
            if(a[i]>a[i-1]){cout<<"NO"<<endl;return 0;}//判断会升
        }
    }
   cout<<"YES"<<endl;
    return 0;
}
```

---

## 作者：Neilchenyinuo (赞：0)

#### 这是一道找规律的题。

- 易知：盘子一定是以由大到小的顺序移动到半径最大的盘子上，因此当一个盘子在移动到最大盘子的过程中，如果被一个更小的盘子挡住，就永远无法移动到最大盘子上，也就无法达到题目的要求。

## 规律：

**如果先递减后递增就输出 NO，反之输出 YES**。

## Solution

- 如果 $a_{i-1}<a_{i}$，再判断 $a_{i}<a_{i+1}$ 如果满足此条件就输出 NO，反之输出 YES。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N],n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<n;i++)
        if(a[i-1]>a[i]) 
            if(a[i]<a[i+1])
                return cout<<"NO",0;
    cout<<"YES"; 
    return 0;
}
```


---

## 作者：猜一猜我是谁 (赞：0)

找规律即可，**如果先递减后递增就输出 NO，否则输出 YES**。

至于如何判断，我们可以在任意时刻判断有没有出现 $a_{i-1}>a_i$ 的情况，如果有就判断 $a_i$ 是否小于 $a_{i+1}$，满足条件就输出 NO，如果一直不满足，最后就输出 YES。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++)
        if(a[i-1]>a[i])  //判断
            if(a[i]<a[i+1]){
                cout<<"NO";//满足条件就输出 NO
                return 0; //退出
            }
    cout<<"YES";   //一直不满足就输出 YES
}
```

---

## 作者：Th3orie (赞：0)

为了满足最后盘子的半径从下往上递减，盘子一定是以由大到小的顺序移动到半径最大的盘子上；因此当一个盘子在移动到最大盘子的过程中，如果被一个更小的盘子挡住，就永远无法移动到最大盘子上，也就无法达到题目的要求。

也就是说，设最大值是$a_k$，若$a_{k-2}>a_{k-1}$，或$a_{k+2}>a_{k+1}$，那么就永远无法达到题目要求，因为一个盘子若要移动到另一个盘子上，半径必须小于它。

那么就可以得到符合题目要求的排列：设最大值为$a_k$，那么$a_1<a_2<\cdots <a_{k-1}<a_k>a_{k+1}>\cdots >a_{n-1}>a_{n}$。因此只要找到最大值$a_k$，判断$a_1,a_2,\cdots ,a_{k-1}$是否单调递增，以及$a_{k+1},a_{k+2},\cdots ,a_n$是否单调递减即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
inline int read()
{
	int x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(!isdigit(ch));
	do{x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}while(isdigit(ch));
	return f*x;
}
int n,a[N],maxn,pos;
bool flag;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		if(a[i]>maxn)
		{
			maxn=a[i];
			pos=i;
		}
	}
	for(int i=1;i<pos-1;i++)
		if(a[i+1]<=a[i])
		{
			puts("NO");
			return 0;
		}
	for(int i=pos+1;i<n;i++)
		if(a[i+1]>=a[i])
		{
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
```





---

## 作者：Luban (赞：0)

看楼下的大佬写的代码这么短，蒟蒻我十分佩服。但我还有一个比较好理解的思路，想拿来分享一下

### 观察题目：如果要移动盘子有三个条件

1.含义：移动的两个盘子之间不能再有盘子，那么如果我们剔除所有没有盘子的柱子，就只能把盘子移动到与它相邻的柱子上了

2.含义：你取出盘子的柱子上必须只有一个盘子，取出后该柱子将没有盘子 （这意味不得使用中转的柱子，必须把所有柱子上的盘子一次性移到一个柱子上）

注：的确，你可以把空柱子用来中转，但是既然是空柱子，直接跳过就可以了，所以这完全是多此一举。（如果一个柱子为空柱子，直接剔除就可以啦）

3.含义：大盘子在下面，小盘子在上面。所以我们应该把所有盘子往有最大盘子的柱子上面移动

## 综上，我们要干以下几件事：

1.找到含有最大盘子的柱子

2.把和它相邻的柱子上最大的盘子叠上去（如果先叠了小的，大的就没法叠了，所以一定要先叠大的），如果发现柱子最上面的盘子没它相邻的柱子上最大的盘子大，输出"NO"

3.叠上去后，该柱子变为空柱子，剔除出考虑范围，如果所有柱子（除了原先还有最大盘子的柱子）都被剔除了，输出“YES”

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main()
{
	int n,i=1,maxn=-1,t;
	cin>>n;
	while(i<=n)
	{
		cin>>a[i];
		if (maxn<a[i])
		{
			maxn=a[i];
			t=i;
		}
		i++;
	}//步骤1
	int l=t-1,r=t+1,now=maxn;
	while(l>=1||r<=n)
	{
		if (l<1)
		{
			if (a[r]>=now)
			{
				cout<<"NO"<<endl;
				return 0;
			}
			now=a[r];//记录
			r++;//移动光标
		}
		else if (r>n)
		{
			if (a[l]>=now)
			{
				cout<<"NO"<<endl;
				return 0;
			}
			now=a[l];//记录
			l--;//移动光标
		}
		else
		{
			bool flag=0;
			if (a[l]>a[r]) flag=1;
			if (max(a[l],a[r])>=now)
			{
				cout<<"NO"<<endl;
				return 0;
			}
			if (flag)
			{
				now=a[l];
				l--;
			}
			else
			{
				now=a[r];
				r++;
			}//判断左右两边哪个大，再进行处理
		}
	}
	cout<<"YES"<<endl; //移动完毕，未发现问题
	return 0;
}
```


---

