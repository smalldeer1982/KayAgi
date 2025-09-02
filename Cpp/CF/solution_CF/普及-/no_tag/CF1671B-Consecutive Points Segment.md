# Consecutive Points Segment

## 题目描述

You are given $ n $ points with integer coordinates on a coordinate axis $ OX $ . The coordinate of the $ i $ -th point is $ x_i $ . All points' coordinates are distinct and given in strictly increasing order.

For each point $ i $ , you can do the following operation no more than once: take this point and move it by $ 1 $ to the left or to the right (i..e., you can change its coordinate $ x_i $ to $ x_i - 1 $ or to $ x_i + 1 $ ). In other words, for each point, you choose (separately) its new coordinate. For the $ i $ -th point, it can be either $ x_i - 1 $ , $ x_i $ or $ x_i + 1 $ .

Your task is to determine if you can move some points as described above in such a way that the new set of points forms a consecutive segment of integers, i. e. for some integer $ l $ the coordinates of points should be equal to $ l, l + 1, \ldots, l + n - 1 $ .

Note that the resulting points should have distinct coordinates.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
2
1 4
3
1 2 3
4
1 2 3 7
1
1000000
3
2 5 6```

### 输出

```
YES
YES
NO
YES
YES```

# 题解

## 作者：8atemak1r (赞：5)

## Description

给定 $n$ 个互不相同的数，每次操作可以将某一个数加 $1$ 或减 $1$，每个数最多操作一次，求能否在若干次操作之后，使这 $n$ 个数变为连续的 $n$ 个数，输入满足单调递增。

## Solution

先说结论：

当且仅当 $a_n-a_1≤n+1$，答案为能；否则答案为不能。证明如下：

我们可以反过来思考，解决**一段长度为 $n$ 的连续的数能变换成的数列一定满足什么条件**这个问题，不妨令连续的数为 $b_1 ～ b_n$，则有 $b_n-b_1=n - 1$，且变换后的数一定在 $[b_1-1,b_n+1]$ 内，即满足 $a_n-a_1≤n+1$。



## Code

```cpp
#include<iostream>
using namespace std;
const int maxn = 200005;
int t, n, a[maxn];
int main() {
    ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> t;
    while(t --) {
        cin >> n;
        for(int i = 1; i <= n; ++ i) cin >> a[i];
        if(a[n] - a[1] <= n + 1) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
```



---

## 作者：cst_123 (赞：1)

### - [题目传送门](https://www.luogu.com.cn/problem/CF1671B)

------------
### 题意

有 $n$ 个数，每次操作可将中间的 $a_i$ 加 $1$ 或减去 $1$ ，也可不变。一个数最多操作一次，问使这数列能满足单调递增吗？

### 思路

一道贪心题，这跟最大 $a_n$ 与最小 $a_1$ 的差有关。

- 如何才能满足单调递增呢？我们设一下 $a_1$ 为 $i$ ，最后 $a_n$ 就为 $i+n-1$ 。两数之差就为 $n-1$ 。而题目中数列能偏转不超过 $2$ 的，那么差就为原本的 $(a_n-a_i-2)\sim(a_n-a_i+2)$ ，并根据最大与最小的差是不小于 $n-1$ 的，自己举[几个栗子](https://www.luogu.com.cn/paste/vbttcg0r)。

这样就可证明当 $a_n-a_i\le n+1$ 时，就是可行的。

### 代码
```cpp
while(T--){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	if(a[n]-a[1]<=n+1)
		printf("YES\n");
	else printf("NO\n");
}
```

---

## 作者：Tx_Lcy (赞：1)

## 思路
从 $2$ 开始往后正序枚举，我们发现为了给后面的数留下更多的操作余地，我们尽可能地要把前面的数变大。

接下来分类讨论。

$\bullet$ 若 $a[i]-a[i-1]=1$，显然不需要更改任何数。

$\bullet$ 若 $a[i]-a[i-1]=2$，显然我们可以令 $a[i]-1$ 或令 $a[i-1]+1$，但由于我们贪心的思想，如果可以使 $a[i-1]+1$，我们就使 $a[i-1]+1$，所以我们要维护一个标记，若从 $1$ 到 $i-1$ 的序列没有任何修改，则这个标记为 $1$，否则为 $0$。

$\bullet$ 若 $a[i]-a[i-1]=3$，如果上面所说的标记为 $1$，则还可以使 $a[1]$ 到 $a[i-1]$ 都 $+1$，$a[i]-1$。而若标记为 $0$，则无解。

$\bullet$ 若 $a[i]-a[i-1] \ge 4$，则无论如何都无解。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[211100];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;cin>>t;
	while (t--){
		int n;cin>>n;
		int tag=0;//这是标记是否有解的
		for (int i=1;i<=n;i++) cin>>a[i];
		int f=1;//这是标记 1 到 i-1 是否不用修改的
		for (int i=2;i<=n;i++){
		    if (abs(a[i]-a[i-1])==2){
		    	if (!f) a[i]--;
		    	else f=0;
			}else if (abs(a[i]-a[i-1])==3){
				if (!f){tag=1;break;}
				else f=0,a[i]--;
			}else if (abs(a[i]-a[i-1])>3){tag=1;break;}
		}
	    if (tag) cout<<"NO\n";
	    else cout<<"YES\n";
	}
	return 0;
}
```


---

## 作者：幸存者 (赞：1)

- $\texttt{[2022.05.03]}$：修复了 Markdown 空行的问题。

## 思路
一个差为 $1$ 的等差数列，首项和末项的差显然为 $n-1$。

可以从给出的数列的首项和末项来考虑，因为数列严格递增，所以首项和末项的差必然 $\ge n-1$。

若首项和末项的差 $\ge n+2$，那么必然不满足条件，因为就算将首项 $+1$，末项 $-1$，差也大于 $n-1$。

若首项和末项的差 $\le n+1$，则必满足条件。我们考虑相邻两个数的差，若差 $\ge2$，则在此处把数列分开，最后显然分成了不超三个数列，每个数列均连续。

- 若分成了三个数列，显然相邻两个数列之间差最小的两个数的差均为 $1$，此时将第一个数列的数均 $+1$，第三个数列的数均 $-1$ 即可。

- 若分成了两个数列，有以下两种情况：

  - 若两个数列之间差最小的两个数的差为 $1$，则将第一个数列的数均 $+1$ 即可。
  
  - 若两个数列之间差最小的两个数的差为 $2$，则将第一个数列的数均 $+1$，第二个数列的数均 $-1$ 即可。
  
- 若只有一个数列，数列不用做任何改动就可满足条件。

综上所述，若首项和末项的差 $\le n+1$，必然满足条件。
## $\text{AC Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, minx = 1e6, maxx = 0;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            if (i == 1) minx = x;
            else if (i == n) maxx = x;
        }
        if (maxx - minx <= n + 1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
```

---

## 作者：MrCR7 (赞：1)

## 思路分析
我们可以确定 $a_1$ 的值，一共有三种，分别是 $a_1$，$a_1+1$ 和 $a_i-1$，然后再依次判断每一个 $a_i$ 能不能移到 $a_{i-1}+1$。因为给的序列是保证有序且不相等的，所以每一个 $a_i$ 都不可能移到 $a_{i-1}-1$ 的位置。

这道题的思路就出来了，如果满足一次，就输出$\texttt{YES}$，三次都不满足，则输出 $\texttt{NO}$。
## Ac Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200003];
void in(int &x){
	char c=getchar(),f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-'){
	   f=-1,
	   c=getchar();
	}
	for(x=0;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
	x*=f;
}
void work(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) in(a[i]);
	bool f1=1;
	int lst=a[0]-1;//第1个数往左移动一位。
	for(int i=1;i<n;i++){
		lst++;
		if(a[i]-1==lst||a[i]==lst||a[i]+1==lst);
		else f1=0;
	}
	if(f1){
		puts("YES");
		return ;
	} 
	f1=1;
	lst=a[0];//第一个数不动。
	for(int i=1;i<n;i++){
		lst++;
		if(a[i]-1==lst||a[i]==lst||a[i]+1==lst);
		else f1=0;
	}
	if(f1){
		puts("YES");
		return ;
	} 
	f1=1;
	lst=a[0]+1;//第一个数往右移动一位。
	for(int i=1;i<n;i++){
		lst++;
		if(a[i]-1==lst||a[i]==lst||a[i]+1==lst);
		else f1=0;
	}
	if(f1){
		puts("YES");
		return ;
	} 
	else puts("NO");
	return ;
} 
int main(){
	int t;
	scanf("%d",&t);
	while(t--) work();
	return 0;
}
```
这道题结束咯！

审核的管理员辛苦啦！

---

## 作者：_zzzzzzy_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1671B)

# 思路
这是一道贪心的题目。

$a_i$ 调整后的数值是 $a_i+1$ 或 $a_i-1$ 调整后元素的最大值是 $a_n+1$ ，元素的最小值是 $a_1-1$ ， $a_i$ 是在区间 $[a_1-1,a_n+1]$ 之中的数值。

若能成功构成序列那么最大值 $-$ 最小值 $ \leqslant n+1$ 。

判断是否满足条件即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200050];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;++i)cin>>a[i];
        if(a[n]-a[1]<=n+1)cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：sgl654321 (赞：0)

### 题目大意
- 给定一个含有 $n$ 个正整数的序列 $a$，保证 $a$ 单调递增。
- 对于每一个元素 $a_i(i\in[1,n])$，你都可以选择将其赋值为 $a_i+1$ 或 $a_i-1$，或者选择不赋值。**每一个元素只能赋值一次。**
- 请问能否通过若干次操作，使原序列变为一个连续整数段。

### 解题思路

很明显，这是一道贪心题。能否成为连续整数段，跟极差有关，即跟最大元素 $a_n$ 与最小元素 $a_1$ 的差的大小有关。

一个长度为 $n$ 的连续整数段，设第一个元素 $a_1$ 为 $k$，则序列为 $[k,k+1,k+2,\cdots,k+n-1]$。容易发现，其最大元素与最小元素的差为 $n-1$。

每一次操作，都可以将一个数变为 $a_i+1$ 或 $a_i-1$，如果一前一后一个加上 $1$，一个减去 $1$，则大小就会相差 $2$。可见，我们能改变极差的大小最大为 $2$。即，如果一个序列原先的极差为 $m$，则操作后极差可以变为 $m-2,m-1,m,m+1$ 或 $m+2$。

因为单调递增的序列的极差一定不小于 $n-1$，所以我们综合上述得出，极差 $m$ 一定要满足 $m\leq n+1$。可以证明，满足这个条件的序列都可以经过修改后变为连续整数段。

### 参考代码
本题有多组数据。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,mi,ma,x;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			if(i==1)mi=x;
			if(i==n)ma=x;
		}
		if(ma-mi<=n+1)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/76771448)

[原题传送门](https://www.luogu.com.cn/problem/CF1671B)

---

## 作者：IGJHL (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1671B)
## 题意

给定 $n$ 个数，判断能否通过修改使原序列变成一个连续整数段，也就是从 $a_1$ ∼ $a_n$ 分别为值 $1$ ∼ $n$。

## 解决方法

### 结论
每次输入完之后判断第 $a_n - a_1$ 的差是否小于等于 $n + 1$。
### 证明
连续整数段的第 $n$ 项减去第 $1$ 项的差一定是 $n - 1$。

而调整后 $a_i$ 的值肯定在区间 $[a_1 - 1, a_n + 1]$ 中，那么如果想要序列 $a$ 调整后为连续整数段，则显而易见的，$a_n - a_1$ 必须 $\leqslant$ $n + 1$。

所以直接运用这个结论，就可以每次询问 $O(1)$ 解决了。

### 代码

```cpp
#include <iostream>

using namespace std;

const int N = 2e5 + 5;

int t, n, a[N];

int main()
{
    cin.tie(0);
    cout.tie(0);
	
    cin >> t;
    
    while (t --)
    {
        cin >> n;
        
        for (int i = 1; i <= n; ++ i)
            cin >> a[i];
			
        if (a[n] - a[1] <= n + 1)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    
    return 0;
}
```
## Thanks For Reading

---

## 作者：Hisaishi_Kanade (赞：0)


**update on 2022.05.06：**

被打回后重新修改并提交。

### 正解

不要被题面劝退了，其实很简单，数据范围已经在暗示 $\Theta\left(tn\right)$ 的做法了。

结论：**只要考虑 $a_1$ 和  $a_n$即可。**

简单证明：若 $a_i-a_{i-1}=1$ 那么 $a_n-a_1=n-1$，因为每个数只能加一或减一，偏移不超过 $2$ （即最左边向右，最右边向左），所以初始输入必须 $a_n-a_1\leq n-1+2$ 即 $a_n-a_1\leq n+1$。

举几个例子：
```cpp
2
1 4
```

$4-1=3 \le 2+1$ 所以是 $\texttt{YES}$。

```cpp
4
1 2 3 7
```

$7-1=6>4+1$ 所以是 $\texttt{NO}$。

### 上代码：

```cpp
#include <iostream>
int t,n;
int a[200005];
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);std::cout.tie(0);//读入优化
	std::cin>>t;
	while(t--){
		std::cin>>n;
		for(int i=1;i<=n;i++)std::cin>>a[i];
		if(a[n]-a[1]<=n+1)std::cout<<"YES"<<std::endl;
		else std::cout<<"NO"<<std::endl;//正如以上所说，a[n]-a[1]<=n+1即为YES，反之为NO。
	}
	return(0);//结束了。
}

```

---

## 作者：CodeMao (赞：0)

简单思维题。

这里给出一个**简单易懂**而又**高效**的**思路**：

- 既然题目问我们能不能将序列 $x$ 通过将 $x_i$ 调整为 $x_i\pm1$ 从而使得序列 $x$ 变为一个连续整数列，那我们可以从**条件**这一方面来出发。

下面给出**推导**过程：

- 设序列 $x$ 已经是连续整数列，那么 $x_n-x_1=n-1$。再考虑两种调整，即将 $x_i$ 调整为 $x_i\pm1$。调整后 $x_i$ 的值的范围肯定在 $[x_n+1,\ x_1-1]$ 的范围内，易得知：
  
- 想让 $x$ 序列经过调整后成为连续整数序列， $x_n-x_1$ 必须 $\leqslant n+1$。
  

怎么样？我说明白了吗？

参考代码：

```cpp
#include <cstdio>
#define maxn 200005
int t,n;
int a[maxn];
inline void in(int &a){ //快速读入
    a=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
        a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
}
int main(){
    in(t);
    while(t--){
        in(n);
        for(int i=1;i<=n;++i) in(a[i]);
        if(a[n]-a[1]<=n+1) puts("YES"); //见上推导过程
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：ajhuhe (赞：0)

# 题目简述

给定长度为 $n$ 的单调递增序列 $a$，你每次可以选择序列的一个元素进行加 $1$、减 $1$ 或不变的操作，每个元素仅仅只可以进行 $1$ 次操作。最后要使 $a$ 序列变成差为 $1$ 的等差序列，即连续整数段。

# 题目分析

这道题纯纯简单数学题。假设有一等差序列 $b$，长度为 $n$。则有 $b_n - b_1 = n - 1$，因为每个元素都可以加 $1$、减 $1$ 或不变，所以 $a_i \in [b_1-1, b_n+1]$。此时 $a_n - a_1 ≤ n+1$，如果不是，说明 $a_i \not\in [b_1-1, b_n+1]$，无法变成连续整数段。


# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,x,y;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a;
			if(i==1)//记录a[1]与a[n]
				x=a;
			if(i==n)
				y=a;
		}
		if(y-x<=n+1)//判断
			cout<<"YES"<<endl;
		if(y-x>n+1)
			cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：Henry_C (赞：0)

# 题意
$\qquad n(1 \le n \le 2 \times 10^5)$ 个严格单调递增的数据，每个数据 $1 \le x_i \le 10^6$ 。对每个数据 $x_i$ 最多可以做一次 $+1$ 或 $-1$ 。问这些数据最终能否变成两两之间相差为1的单调递增的数？
# 解题思路
1. 两个数之间隔大于等于 $4$ 时，例如 $2 \ 6$ ，无法变成差值为1的递增序列。 

2. 通过观察，如果两个数之间相差为 $3$ 时，例如 $2\ 5\ 6$ 这样的，可以变成 $3 \ 4 \ 5$ ；再增加一个为 $3$ 或 $2$ 的间隔时，都无法变成差值为 $1$ 的递增序列了。例如 $2\ 5\ 6\ 9$ 或 $2\ 5\ 6\ 8$ 都不行。

3. 两个数之间差值为 $2$ ，最多可以有 $2$ 个这样的差值，例如 $2\ 4\ 5\ 7$ ，可以变成 $3\ 4\ 5\ 6$ ；但是继续增加相邻差值为 $2$ 的数，例如 $2\ 4\ 5\ 7\ 9$ ，则不行了。

4. 如果两两之间差值为 $1$ ，则正是题目需要的，可行。

$\qquad $综上所述，这些数中间如果最大相邻差值为 $3$ 且只有 $1$ 个差值 $3$ 、最大相邻差值为 $2$ 且不超过 $2$ 个差值 $2$ 、最大差值为 $1$，则是可行的；否则不可行。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Nmax = 2e5+5;
int t,n;
int a[Nmax];

int main() {
//    freopen("1.in","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while(t--){
        cin >> n;
        vector<int> gap;
        for(int i=1; i<=n; i++){
            cin >> a[i];
            if(i>=2){
                gap.push_back(a[i]-a[i-1]);
            }
        }

        sort(gap.begin(), gap.end());

        vector<int> cnt(10,0);
        for(int i=0; i<gap.size(); i++){
            if(gap[i]<=3)
                cnt[gap[i]]++; //记录相邻差值为1,2,3各有多少次
            else
                cnt[4]++;//相邻差值大于等于4有多少次
        }

        if((cnt[2]==0 && cnt[3]==0 && cnt[4]==0)
        ||(cnt[2]<=2 && cnt[3]==0 && cnt[4]==0)
        ||(cnt[2]==0 && cnt[3]==1 && cnt[4]==0))
            cout <<"YES"<<endl;
        else
            cout <<"NO"<<endl;
    }

    return 0;
}
```


---

## 作者：GI录像机 (赞：0)

## 大致思路：

先把数划分成 $n$ 个连续自然数块，因为每次修改为了保持为连续自然数，修改时必然加整一个块。

接着看块的数量。

### 当块数为一时

显然有解，不多赘述。

### 当块数为二时

判断一下第一个块的末尾与第二个块的开头，只要它们的差能在加二或减二以内成为一，就有解。

### 当块数为三时

先和二一样判断，只不过要贪心地更改一下第二个块的末尾。

然后再判断第三个块。

### 当块数大于三时

显然无解，不多赘述。

具体实现看代码。

## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
int t = read();
signed main() {
	while (t--) {
		int n = read(), a[int(2e5) + 10], l;
		queue<pair<int, int> >q;
		for (int i = 1; i <= n; i++) {
			a[i] = read();
			if (a[i] != a[i - 1] + 1) {
				if (i != 1)q.push(make_pair(l, i - 1));
				l = i;
			}
		}
		q.push(make_pair(l, n));
		if (q.size() > 3)puts("NO");
		else if (q.size() == 1)puts("YES");
		else if (q.size() == 2) {
			pair<int, int>p;
			p = q.front();
			q.pop();
			if (a[q.front().first] - a[p.second] < -1 || a[q.front().first] - a[p.second] > 3)puts("NO");
			else puts("YES");
		} else {
			int xgh = q.front().second;
			q.pop();
			int zy = q.front().first, zt = q.front().second;
			q.pop();
			int dxc = q.front().first;
			if (a[zy] - a[xgh] < -1 || a[zy] - a[xgh] > 3)puts("NO");
			else {
				if (a[zy] - a[xgh] == 0) {
					if (a[dxc] - a[zt] > 1)a[zt]++;
					if (a[dxc] - a[zt] + 1 == 1 ||a[dxc] - a[zt] - 1 == 1 || a[dxc] - a[zt] == 1)puts("YES");
					else puts("NO");
				} else if (a[zy] - a[xgh] == 2) {
					if (a[dxc] - a[zt] < 1)a[zt]--;
					if (a[dxc] - a[zt] + 1 == 1 || a[dxc] - a[zt] == 1||a[dxc] - a[zt] - 1 == 1)puts("YES");
					else puts("NO");
				} else if (a[zy] - a[xgh] == 3) {
					a[zt]--;
					if (a[dxc] - a[zt] == 1)puts("YES");
					else puts("NO");
				} else {
					a[zt]++;
					if (a[dxc] - a[zt] == 1)puts("YES");
					else puts("NO");
				}
			}
		}
	}
}
```


---

## 作者：ryanright (赞：0)

设原本有 $m$ 个连续整数段。我们对 $m$ 分类讨论：

- $m=1$，已经符合题目要求；
- $m=2$，令第一段的末尾为 $a$，第二段的开头为 $b$：
  - $b-a=2$，则将第一段整体右移一个单位长度；
  - $b-a=3$，则将第一段整体右移一个单位长度，第二段整体左移一个单位长度；
  - $b-a>3$，无法做到。
- $m=3$，令第一段的末尾为 $a$，第二段的开头为 $b$，第二段的末尾为 $c$，第三段的开头为 $d$。这时我们不能移动第二段：
  - $b-a=2$，则将第一段整体右移一个单位长度；
  - $d-c=2$，则将第三段整体左移一个单位长度；
  - $b-a>2$ 或 $d-c>2$，无法做到。
- $m>3$，无法做到。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, tot = 0;
		cin >> n;
		a[0] = -0x7ffff;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[i] != a[i - 1] + 1)
				tot++;
		}
		if (tot > 3)
			puts("NO");
		else if(tot == 1)
			puts("YES");
		else if(tot == 3) {
			bool flag = 1;
			for(int i = 2;i <= n; i++)
				if(a[i] - a[i - 1] > 2) {
					flag = 0;
					break;
				}
			puts(flag ? "YES" : "NO");
		} else
			for(int i = 2; i <= n; i++)
				if(a[i] != a[i - 1] + 1) {
					if(a[i - 1] + 3 >= a[i])
						puts("YES");
					else
						puts("NO");
				}
	}
	return 0;
}
```

---

## 作者：lsj2009 (赞：0)

### 题目大意
给定序列 $\{a_n\}$，对于每个 $a_i$ 你可以将他变成 $a_i-1$ 或 $a_i$ 或 $a_i+1$，是否有一种操作方法可以使该序列满足对于任意一个 $i(1<i\le n)$ 满足 $a_i=a_{i-1}+1$。
### 思路
如果我们确定了 $a_1$ 的值，则最终序列的每个 $a_i=a_1+i-1$。

则问题变成了：给定序列 $\{a_n\}$ 是否可以将每个 $a_i$ 变成 $a_1+i-1$。

显而易见，最终 $a_i$ 的值只有可能是（最初的）$a_1-1$ 或 $a_i$ 或 $a_i+1$。

则 $a_i$ 分别取 $a_i-1$ 或 $a_i$ 或 $a_i+1$，只要有一种满足条件（可以构造出题目要求的序列）即可。

### Code:
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
#define _go(i,u) for(int i=head[u];i;i=Edge[i].nxt)
using namespace std;
namespace I {
	template <typename T> void read(T& x) {
		x=0; T f=1; char ch=getchar();
		while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
		while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch&15); ch=getchar(); }
		x=x*f; return;
	}
	template <typename T,typename ...Arg> void read(T& x,Arg& ...arg) {
		read(x); read(arg...);
	}
}
namespace Math {
	template <typename T> T power(T a,T b,T MOD) {
		T ans=1; while(b) { if(b&1) ans=ans*a%MOD; a=a*a%MOD; b>>=1; } return ans%MOD;
	}
	template <typename T> T gcd(T a,T b) {
		if(b) return gcd(b,a%b); return a;
	}
	template <typename T> T lcm(T a,T b) {
		return a/gcd(a,b)*b;
	}
	template <typename T> T inv(T n,T p) {
		return power(n,p-2);
	}
	const int Test[]={0,2,3,5,7,11,13,17,19,23,29};
	template <typename T> bool is_prime(T n) {
		if(n<2) return 0;
		T t=n-1,k=0; while((t+1)&1) ++k,t>>=1;
		_for(i,1,10) {
		    if(n==Test[i]) return 1;
		    T s=power(Test[i],t,n); T tmp=s;
		    _for(j,1,k) {
		        tmp=s*s%n; if(tmp==1&&s!=1&&s!=n-1) return 0; s=tmp;
		    }
		    if(s!=1) return 0;
		}
		return 1;
	}
}
const int N=2e5+5;
int a[N],tmp[N],n,T;
bool Solve(int p) { //判断我们将a[1]设为a[1]+p时是否可行
	_for(i,1,n) a[i]=tmp[i];
	a[1]+=p;
	_for(i,2,n)
		if(a[i]-a[i-1]<0||a[i]-a[i-1]>2)
			return false;
		else
			a[i]=a[i-1]+1;
	return true;
}
signed main() {
	I::read(T);
	while(T--) {
		I::read(n);
		_for(i,1,n)
			I::read(tmp[i]);
		puts(Solve(-1)||Solve(0)||Solve(1)? "YES":"NO");
	}
	return 1;
}

```

---

## 作者：QZY2008 (赞：0)

#### 题目大意：

给定一个序列，长度为 $N (1 \le N \le 2 \times 10^5) $ ，每个元素 $ a_i$ 小于等于 $10^6$，且数列以严格递增的方式给出！！！

现在对于每个 $a_i$ 可以变为：$a_i-1,a_i,a_i+1$ 三个数字其中的的一个。

问是否可以通过有限次操作使序列成为等差数列，公差为  $1$。

#### 解题思路：

STEP 1:

两个相邻的数差为 $1 , 2 , 3$ 时可以通过操作使两数差最终为 $1$。

像 $1,2$，只要不变即可。

像 $1,3$，可以将 $1$ 变为 $2$，或者将 $3$ 变为 $2$。

像 $1,4$，可以将 $1$ 变为 $2$，并且将 $4$ 变为 $3$。

STEP 2:

如果可以通过操作使得达到题目条件，则有如下三种情况。（为了更方便展示，造了几组数据）

### 情况一：

![情况一](https://cdn.luogu.com.cn/upload/image_hosting/wr3o11uq.png)

有一个对相邻数差为 $2$。

### 情况二：

![](https://cdn.luogu.com.cn/upload/image_hosting/mkf684sd.png)

有两个对相邻数差为 $2$。

### 情况三：

![](https://cdn.luogu.com.cn/upload/image_hosting/wppi3kty.png)

有一个对相邻数差为 $3$。

此外还要特判直接符合要求的情况。

#### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

const int N=105;
const int Maxn=200005;
int n;
int num[Maxn];
int main(){
	int t;
	scanf("%d",&t);
	while (t--){
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			scanf("%d",&num[i]);
		if (n==1){
			puts("YES");
			continue;
		}//特判
		else
			if (n==2){
				int ans=0;
				if (num[2]-num[1]<=3)
					printf("YES\n");
				else
					printf("N0\n");
				continue;
			}//特判
		int tmp=0,sum=0,x=0;
		for (int i=1;i<n;i++)
			if (num[i+1]-num[i]==3)
				tmp++;
			else if (num[i+1]-num[i]==1)
				sum++;
			else if (num[i+1]-num[i]==2)
				x++;
		if (sum==n-1){
			printf("YES\n");
			continue;
		}//特判
		else
			if ((tmp==1&&x==0)/*情况3*/||(tmp==0&&x==2)/*情况2*/||(tmp==0&&x==1)/*情况1*/){
				printf("YES\n");
				continue;
			}
		printf("NO\n");//其余输出NO
	}
}
```


---

## 作者：Toorean (赞：0)

本题不难，考虑须全面，否则会像我赛时罚时七次。
## 题意
给出长度为 $n$ 的序列 $arr$，$arr_i$ 可以变为 $arr_i+1$ 或 $arr_i-1$（仅限**一次**）。判断其是否可在操作后使原序列变为一个**连续**的整数序列。
## 思路
我们须分几种情况来讨论。

1. 相邻两数差值恰为 $1$
	
    此时，无需修改，满足条件。

2. 相邻两数间差值恰为 $2$
	
     假设两数分别为 $arr_i$ 与 $arr_{i+1}$，则需使得 $arr_{i+1}-arr_i=1$ 即可。此时我们可以选择修改 $arr_{i+1}$ 或 $arr_i$。若 $arr_k (k>i)$ 同时也拥有差值为 $2$ 的相邻两数，则需修改 $arr_{i+1}$。反之，修改 $arr_i$。若两边均有相邻两数差值为 $2$，则无解。
     
3. 相邻两数间差值恰为 $3$
	
    假设两数分别为 $arr_i$ 与 $arr_{i+1}$，要使条件满足，则必须将 $arr_i\gets arr_i+1$ 并 $arr_{i+1}\gets arr_{i+1}-1$，此时才能保证其为**连续**的序列。不过，也需使 $arr_{k}+1\ (1\leq k<i)$ 与 $arr_{m}-1\ (i+1<m\leq n)$。故当仅有一对相邻两数差值为 $3$ 且无另外两数差值至少为 $2$ 时，原序列可变为**连续**的整数序列。否则，不可得。

4. 相邻两数间差值大于 $3$
	
    显然，在这种情况中，无论如何将值改变，都无法使其**连续**，故无解。


模拟综上步骤即可。

## AC Code
```cpp
bool solve () {
    
    read (n);
    ffor (i, 1, n) read (arr[i]);
    
    int counts = 0, counts2 = 0;
    rfor (i, n, 2) {
        if (arr[i] - arr[i - 1] == 2 && i > 2 && arr[i - 1] - arr[i - 2] > 2) {
            return false;
        } else if (arr[i] - arr[i - 1] == 2) ++ counts;
        if (arr[i] - arr[i - 1] == 3 && i > 2 && arr[i - 1] - arr[i - 2] >= 2) {
            return false;
        } else if (arr[i] - arr[i - 1] == 3) ++ counts2;
        if (arr[i] - arr[i - 1] > 3) {
            return false;
        }
    }
    
    return !(counts && counts2) && (!counts && counts2 <= 1 || counts <= 2 && !counts2);
}
```

---

