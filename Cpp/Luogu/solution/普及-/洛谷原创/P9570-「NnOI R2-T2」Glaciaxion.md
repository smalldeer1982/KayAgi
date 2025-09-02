# 「NnOI R2-T2」Glaciaxion

## 题目描述

冰封的世界可以看作是 $ n $ 块初始时冷冻的冰川，这些冰川被编号为 $1 \sim n$。

探测器抵达后的 $ m $ 秒，每秒都会探测到一块冰川融化。

当一块冰川第一次融化时，探测器返回 ```N```，否则返回 ```Y```。

你需要根据探测器按顺序返回的信息，给出**字典序最小**的冰川融化过程的编号序列。如果不存在这样的编号序列，请输出 ```No solution``` 报告无解。

## 说明/提示

**【样例 1 解释】**

第 1 秒，1 号冰川融化，这是其首次融化，返回 ```N```。

第 2 秒，1 号冰川融化，这不是其首次融化，因为已经在第 1 秒融化过，返回 ```Y```。

第 3 秒，2 号冰川融化，这是其首次融化，返回 ```N```。

第 4 秒，1 号冰川融化，这不是其首次融化，因为已经在第 1,2 秒融化过，返回 ```Y```。

**【数据范围】**

对于 $ 100\% $ 的数据，$ 1 \le n,m \le 10^6 $。

**提示：本题开启捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c}
\textbf{Subtask} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& n,m\le 8 & 23 \r
\textsf2& n,m\le 1000 & 25 \r
\textsf3& 探测器返回结果只有一种字符 & 15 \r
\textsf4& 保证有解 & 17 \r
\textsf5& 无特殊限制 & 20 \r
\end{array}
$$

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
| idea | 船酱魔王 |
| data | 船酱魔王 |
| check | EstasTonne |
| solution | 船酱魔王 |

## 样例 #1

### 输入

```
3 4
NYNY```

### 输出

```
1 1 2 1```

## 样例 #2

### 输入

```
5 3
YYY```

### 输出

```
No solution```

## 样例 #3

### 输入

```
5 7
NNNNNYN```

### 输出

```
No solution```

# 题解

## 作者：Thenyu (赞：4)

[原题](https://www.luogu.com.cn/problem/P9570)

[更好的阅读体验](https://www.cnblogs.com/thenyu/p/17649810.html)

直接遍历字符串，如果当前字符为 `N` ,就判断编号 $1 \sim n$ 是否有冰川没有第一次融化。如果有，就将这个冰川的编号存到记录答案的数组中；如果没有，则输出 `No solution` 并结束程序。

如果当前字符为 `Y` ，因为题目要求字典序最小，所以直接判断编号 $1$ 的冰川是否已经第一次融化，如果没有就输出 `No solution` 并结束程序，有就直接把编号为 $1$ 的冰川存到记录答案的数组中。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int n,m,a[N+5],cnt,tmp;//tmp用来记录已经融化的冰川数量
string s;
int main()
{
	scanf("%d%d",&n,&m);
	cin>>s;
	for(int i=0;i<m;++i)
	{
		if(s[i]=='N')
		{
			if(tmp==n){printf("No solution");return 0;}//如果所有冰川已经第一次融化了，那么就没有符合条件的冰川 
			a[++cnt]=++tmp;//有符合条件的冰川，存到数组a中 
		}
		else
		{
			if(cnt==0){printf("No solution");return 0;}//如果数组a中没有冰川第一次融化，那就没有符合条件的冰川 
			a[++cnt]=1;
		}
	}
	for(int i=1;i<=cnt;++i)
		printf("%d ",a[i]);
	return 0;
}
```


---

## 作者：ivyjiao (赞：3)

首先我们考虑什么时候无解：

- `N` 出现的数量大于 $n$，即融化了大于 $n$ 个冰川。
- 第一条信息是 `Y`，即第一次之前已经有冰川融化。

依题意，以上两种情况不合法。

再谈有解：

我们令第一次融化的冰川为 $1$ 号冰川，之后探测为 `Y` 的也都是 $1$ 号冰川，若探测为 `N`，融化的编号顺延。容易证明，这样可以做到字典序最小。

```
#include<iostream>
using namespace std;
int n,m,cnt;
string s;
int main(){
    cin>>n>>m;
    cin>>s;
    for(int i=0;i<s.size();i++){
		if(!i&&s[i]=='Y'){
			puts("No solution");
			return 0;
		}
		if(s[i]=='N') cnt++;
		if(cnt>n){
			puts("No solution");
			return 0;
		}
	}
	cnt=0;
	for(int i=0;i<=s.size()-1;i++){
		if(s[i]=='N'){
			cnt++;
			cout<<cnt<<" ";
		}
		else{
			cout<<1<<" ";
		}
	}
}
```

---

## 作者：zfw100 (赞：2)

由于冰川不可能还没融化就第二次融化，所以第一次返回**不可能**是 `Y`，那么如果第一次返回是 `Y` 直接输出 `No solution` 即可。

而冰川数量不可能大于 $n$，所以要先计算冰川数量，如果大于 $n$，就说明无解，直接输出 `No solution` 即可。

然后我们可以定义一个 $j$，用来记录冰川融化到几号，如果返回的是 `N`，$j$ 就增加一，然后输出 $j$ 即可。

而如果返回的是 `Y`，那么就直接输出 $1$ 即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	std::ios::sync_with_stdio(0);
	ll n,m,j=0;
	cin>>n>>m;
	string s;
	cin>>s;
	if(s[0]=='Y'){
		cout<<"No solution";
		return 0;
	}
	for(ll i=0;i<m;i++){
		if(s[i]=='N'){
			j++;
		}
		if(j>n){
			cout<<"No solution";
			return 0;
		}
	}
	j=0;
	for(ll i=0;i<m;i++){
		if(s[i]=='N'){
			j++;
			cout<<j<<" ";
		}else{
			cout<<1<<" ";
		}
	}
}


```


---

## 作者：zzx114514 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P9570)
# 题目大意
冰封的世界可以看作是 $n$ 块初始时冷冻的冰川，这些冰川被编号为 $1∼n$。
探测器抵达后的 $m$ 秒，每秒都会探测到一块冰川融化。
当一块冰川第一次融化时，探测器返回 $N$，否则返回 $Y$。
你需要根据探测器按顺序返回的信息，给出字典序最小的冰川融化过程的编号序列。如果不存在这样的编号序列，请输出 `No solution` 报告无解。
# 解题思路
对于每条报告信息，如果是第一次融化，则优先选择编号小的冰山，如果融化的数量大于冰山总数，则说明不可能。  
如果不是第一次融化，则选择第一座冰山，若第一座冰山从未融化过，说明没有冰山融化，则不可能实现。
# 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,pos;
string s;
bool flag[1000005],vis;//flag记录当前冰山是否为第一次融化，vis记录是否有冰山融化 
queue<int> q;//队列存储冰山融化的编号序列 
int main()
{
	cin>>n>>m>>s;
	for (int i=0;i<m;i++)
	{
		if (s[i]=='N')//如果是第一次融化 
		{
			if (i==0)//如果是第一座冰山 
			{
				q.push(1);//压入冰山编号 
				pos=1;//记录第一次融化中字典序最小的冰山编号 
				vis=true;
				flag[1]=true;//标记 
			}
			else//如果不是第一座 
			{
				pos++;//将融化编号后移一位 
				if (pos>n)//如果当前编号大于冰山总数 
				{
					cout<<"No solution";//说明不可能，直接返回 
					return 0; 
				}
				q.push(pos);//编号压入队列 
				flag[pos]=true;//记录 
				
			}
		} 
		else//如果不是第一次融化 
		{
			if (i==0)//如果是第一座冰山 
			{
				cout<<"No solution";//不可能实现，直接返回 
				return 0; 
			}
			if (vis) q.push(1);//如果有冰山融化过，一定是第一座，接下来的融化全部算在它头上，使得字典序最小 
			else//否则没有冰山融化过 
			{
				cout<<"No solution";//不可能实现，直接返回 
				return 0; 
			}
		}
	}
	while(!q.empty())
	{
		cout<<q.front()<<' ';//输出编号序列 
		q.pop();
	}
	return 0;//华丽的结尾 
}
```


---

## 作者：船酱魔王 (赞：2)

# Glaciaxion 官方题解

## 题意回顾

已知一个长度为 $ m $，值域为 $ [1,n] $ 的整数序列的每个位置上的数之前是否出现过一样的数，构造字典序最小的序列或报告无解。

$ 1 \le n,m \le 10^6 $。

## 分析

如果第一个数之前出现过，显然一定无解。

如果首次出现的数个数高于 $ n $，显然一定无解。

因为字典序主要取决于靠前的数，因此考虑从前往后贪心构造，第一个首次出现的数应为 $ 1 $，第二个应为 $ 2 $，以此类推。

对于之前出现过的数，显然第一个数是首次出现，因此 $ 1 $ 一定出现过，则为了让字典序最小全放 $ 1 $ 即可。

这种构造方式字典序一定最小，可以发现只要不是无解情况，这种构造方式一定有效。因此这样构造即可。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
int n, m;
string s;
int main() {
	cin >> n >> m;
	cin >> s;
	if(s[0] == 'Y') {
		cout << "No solution" << endl;
		return 0;
	}
	int ct = 0;
	for(int i = 0; i < m; i++) {
		if(s[i] == 'N') {
			ct++;
		}
	}
	if(ct > n) {
		cout << "No solution" << endl;
		return 0;
	}
	ct = 0;
	for(int i = 0; i < m; i++) {
		if(s[i] == 'N') {
			ct++;
			printf("%d", ct);
		} else {
			printf("1");
		}
		if(i != m - 1) {
			printf(" ");
		}
	}
	printf("\n");
	return 0;
}
```

---

## 作者：coderJerry (赞：1)

### 题目大意
给出 $n$ 块冰川 $m$ 秒内的融化情况，构造字典序最小的冰川编号序列，如果无解输出```No soultion```。
### 题目分析
先来考虑无解的情况。首先，当第一条记录就是```Y```时，即第一条记录的这块冰不是第一次融化时，这种情况显然不可能有解。另外，当记录中```N```的数量大于 $n$ 时，即融化的冰块数量大于总数量的话，显然也不可能有解。然后我们考虑有解的情况。如果当前记录是```N```，即有新的冰融化，那么我们就 $1$ 开始输出，每次输出都加一。如果当前记录是```Y```，说明有已经融化过的冰再次融化，那么对于这种情况，全部输出 $1$ 就可以使的字典序最小。
### AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,cnt=0,cntN=0;
string s;
int main()
{
    cin>>n>>m>>s;
    if(s[0]=='Y')
    {//第一块冰就不是第一次融化，怎么可能呢
        cout<<"No solution"<<endl;
        return 0;
    }
    for(int i=0;i<s.size();i++)
    {//求出第一次融化的冰的数量
        if(s[i]=='N') cntN++;
    }
    if(cntN>n)
    {//第一次融化的冰的数量都超过n了，怎么可能呢
        cout<<"No solution"<<endl;
        return 0;
    }
    for(int i=0;i<s.size();i++)
    {//进入到这个循环说明已经排除掉所有不可能的情况了
        if(s[i]=='N') 
        {//这是一块新的冰，要字典序最小那就从1开始加上去
            cnt++;
            cout<<cnt<<" ";
        }
        if(s[i]=='Y') cout<<"1 ";
      	//这是一块已经出现过的冰，要字典序最小那就一直输出1
    }
    return 0;
}
```

---

## 作者：zhujiangyuan (赞：1)

基础赛 T2，应该比 CSP-J T2 稍简单一些。

首先考虑无解的情况：
- 第一次融化的冰川数目大于 $n$，即 `N` 的数量大于 $n$。
- 一块冰川都没有融化时返回已经融化了，即还没有出现 `N` 时就出现 `Y`。

以上两种情况输出 `No solution` 即可。

正常情况就非常简单了。
- 对于 `N`，每次探测到“第一次融化”的冰川肯定不是同一块，用 $tot$ 表示当前是第 $tot$ 块冰川融化，每次输出 `++tot`。
- 对于 `Y`，因为要求冰川融化过程的编号序列的字典序最小，所以每次都探测到第 $1$ 块冰川就行了，输出 $1$ 即可。

代码很简单就不放了，时间复杂度 $O(n)$。

---

## 作者：IcyFoxer_XZY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9570)

这道题是一个思维题，并不难。

### 分析

我们已知 N 代表一块冰川第一次融化，否则就是 Y。那么如果字符串第一个字母就是 Y 或者字符串中 N 的数量比冰川数还多那么就可以直接结束程序了。

我们再看到题目要求，输出字典序最小的融化编号序列。那么我们只要看到 Y 就直接输出 $1$，看到 N 的话就依次输出，即第一个 N 输出 $1$，第二个 N 输出 $2$，以此类推第 $x$ 个 N 输出 $x$。能确保这是最优解。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,cnt;
char ch[1000005];
bool r;
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;++i)cin>>ch[i];
    int sum=0;
    for(int i=1;i<=m;++i)
    	if(ch[i]=='N')
    		sum++;
    if(sum>n){
    	puts("No solution");
    	return 0;
	}
    for(int i=1;i<=m;++i){
    	if(ch[i]=='Y'&&r==false){
    		puts("No solution");
    		return 0;
		}
		if(ch[i]=='N'){
			printf("%lld ",++cnt);
			r=true;
		}else printf("1 ");
	}
    return 0;
}
```
Bye！

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9570)

首先考虑字符为 `N` 的情况。由于字符为 `N` 时冰川一定是第一次融化，所以我们可以从 $1$ 或是已经融化过的冰川开始往后找，当找到尚未融化的冰川时，则将下标做记录，作为下一次从前往后找的开端。

特别地，若没有找到任何尚未融化的冰川，则报告无解并结束程序即可。

接着考虑字符为 `Y` 的情况。由于字符为 `Y` 时冰川一定不是第一次融化，所以我们可以从 $1$ 或是尚未融化过的冰川开始往后找。但是我们忽略了一个关键点，题目要求输出的序列**字典序最小**。所以在这里，我们只考虑第 $1$ 个冰川即可。

同样特别地，若当连第 $1$ 个冰川都尚未融化时，则报告无解并结束程序即可，因为按照上面的策略，后面的冰川肯定也尚未融化。

最后还需要注意一个点，就是不能在决策时就输出序列。因为如果之后出现了无解的情况，前面输出的序列便无法删除。所以我们可以将要输出的数存入答案序列里，最后输出答案序列即可。于是得代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define wtl(x) wt(x),putchar('\n')
#define kg putchar(' ')
#define hh putchar('\n')
bool a[1000001];
int ans[1000001];
signed main()
{
	int n,m;
	rd(n,m);
	string s;
	cin>>s;
	int xb1=1,xb2=1;
	for(int i=0;i<m;i++)
	{
		if(s[i]=='N')
		{
			if(a[xb1])
			{
				int flag=0;
				for(int j=xb1+1;j<=n;j++)
				{
					if(!a[j])
					{
						xb1=j;
						flag=1;
						break;
					}
				}
				if(!flag)
				{
					puts("No solution");
					return 0;
				}
			}
			a[xb1]=1;
			ans[i+1]=xb1;
		}
		else
		{
			if(!a[1])
			{
				puts("No solution");
				return 0;
			}
			else
			{
				ans[i+1]=1;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		wt(ans[i]),kg;
	}
	hh;
	return 0;
}
```

---

## 作者：__zfy__ (赞：0)

### 思路
首先判断无解情况：
1. `Y` 开头的，第一个永远是 `N`，因为 $1$ 号冰川总是第一个融化的。
2. `N` 的数量大于 $n$，因为第一次融化的一定是新的冰川。

对于有解的情况，直接把字符串每一位枚举，如果是 `N`，直接输出 $id$， 然后将 $id$ 加 $1$，代表下一次融化的新冰川。如果是 `Y`，直接输出 $1$ 就可以了，因为这样可以保证字典序最小。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
string s;
//快读
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
//  变量名=read();
//  n=read();
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(0);
	int n,m,id=1;
	cin>>n>>m;
	cin>>s;
	if(s[0]=='Y')
	{
		cout<<"No solution";
		return 0;
	}
	int temp=0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='N')
			temp++;
	}
	if(temp>n)
	{
		cout<<"No solution";
		return 0;
	}
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='N')
		{
			cout<<id<<" ";
			id++;
		}
		if(s[i]=='Y')
		{
			cout<<1<<" ";
		}
	}
	return 0;
}
```


---

## 作者：Morishima_zj_zhy (赞：0)

### 题目传送门

[P9570 Glaciaxion](https://www.luogu.com.cn/problem/P9570)

### 思路

由题面可知，我们求的是**字典序最小**的冰川融化过程的编号序列。

那我们可以想到：

- 从探测器第二次返回信息开始，但凡出现 $Y$，那融化的肯定是第 $1$ 座冰山。

- 如果出现 $N$，那一定是上一座第一次融化的冰山的编号加 $1$。

- $Y$ 的数量可以是无限个，但一定保证 $N$ 的个数小于等于 $n$。

一旦想通了这些，这个问题就解决了。

### AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int a[maxn]; // 记录编号序列。

int main() {
	int n, m;
	string s;
	cin >> n >> m >> s;
	int cnt = 0;
	int aa = 1; // 记录冰山编号（最后一座融化的冰山的后一座冰山的编号）
	if (s[0] == 'Y') { // 特判，所有冰山都有第一次融化，所以第一项一定为 N，如果不为 N 一定没有结果。
		cout << "No solution";
		return 0;
	}
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'N') {
			a[++cnt] = aa;
			aa += 1;
		}
		else if (s[i] == 'Y') {
			a[++cnt] = 1;
		}
	}
	if (aa - 1 > n) { // 因为 aa 是最后一座融化的后一座冰山的编号，所以 aa 要减 1。如果 aa 减 1 的结果大于 n，代表 N 的个数大于 n，是没有结果的。
		cout << "No solution";
		return 0;
	}
	for (int i = 1; i <= cnt; i++) { // 有结果，输出编号序列
		cout << a[i] << " ";
	}
	return 0;
}
```


---

## 作者：zhang_Jimmy (赞：0)

赛时思路：

首先我们可以发现：

- 如果 `Y` 在第一个，显然无解（因为还没有探测到任何一个冰块）。

- 如果 `N` 的数量超过 $n$，也无解（因为探测到的冰块数量超过了 $n$）。

那么如何构造出字典序最小的冰川融化过程的编号序列呢？

我们可以这样构造：

- 对于第 $i$ 个 `N`，我们可以输出 $i$。（因为要使字典序最小）

- 对于任意一个 `Y`，我们可以输出 $1$。（理由同上）

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s; 
int n, m, sum;
int main(){
// 	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	cin >> n >> m;
	cin >> s;
	if(s[0] == 'Y'){
		cout << "No solution";
		return 0;
	}
	for(int i = 0; s[i]; i ++){
		if(s[i] == 'N') sum ++;
	}
	if(sum > n){
		cout << "No solution";
		return 0;
	}
	int cnt = 0;
	for(int i = 0; s[i]; i ++){
		if(s[i] == 'N') cout << ++ cnt << ' ';
		else cout << 1 << ' ';
	}
	return 0;
}
```


---

