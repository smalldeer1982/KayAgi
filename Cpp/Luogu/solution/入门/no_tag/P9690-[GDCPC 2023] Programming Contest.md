# [GDCPC 2023] Programming Contest

## 题目描述

广东省是全国较早一批将程序设计竞赛引入省内大学生竞赛体系的省份之一。$2003$ 年，中山大学承办了第一届广东省大学生程序设计竞赛。此后，华南农业大学、华南理工大学、华南师范大学等省内高校也先后承办了此赛事，除 $2020$ 年因疫情停办外，每年一届。$2023$ 年，深圳技术大学将承办第二十届广东省大学生程序设计竞赛，让我们期待选手们出色的表现！

在另一个世界中，某程序设计竞赛自 $y_1$ 年起开始举办。除了 $s_1, s_2, \cdots, s_n$ 这 $n$ 年由于特殊原因无法举办之外，其他年份每年举办一次。

求 $y_2$ 年是该竞赛的第几次举办。


对于第二组样例数据，由于 $2003$ 就是该竞赛第 $1$ 次举办的年份，因此答案为 $1$。

对于第三组样例数据，由于竞赛从未停办，因此答案为 $3456 - 2345 + 1 = 1112$。

对于第四组样例数据，该竞赛前 $5$ 次举办的年份为 $3000$，$3002$，$3005$，$3006$ 与 $3007$。因此答案为 $5$。

## 样例 #1

### 输入

```
4
2003
1 2020
2023
2003
1 2020
2003
2345
0
3456
3000
4 3001 3003 3004 3008
3007```

### 输出

```
20
1
1112
5```

# 题解

## 作者：qinshi0308 (赞：8)

## 思路

首先我们知道，第 $x$ 年到第 $y$ 年一共有 $y-x+1$ 年，也就是举办了 $y-x+1$ 场比赛，不妨设这个数为 $z$。

然后我们可以按顺序枚举停办年份，每枚举到一个小于 $y$ 的停办年份，$z$（举办比赛的次数）就减一，由于题目中保证停办年份按升序给出，所以当遇到第一个大于 $y$ 的停办年份，就说明后面的停办年份都大于 $y$，对答案没有影响，就可以结束统计。

## 代码：

```cpp
# include <bits/stdc++.h>
using namespace std;
int arr[110];
int main(){
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		int x,y,n;
		cin>>x>>n;
		for(int j=0;j<n;j++){
			cin>>arr[j];
		}
		cin>>y;
		int ans=y-x+1;
		for(int j=0;j<n&&arr[j]<y;j++){
			ans--;
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：__Shine__ (赞：3)

## 题目大意

某程序设计竞赛自 $y_1$ 年起开始举办。除了 $s_1, s_2, \cdots, s_n$ 这 $n$ 年由于特殊原因无法举办之外，其他年份每年举办一次。共有 $T$ 组数据。

求 $y_2$ 年是该竞赛的第几次举办。

## 具体思路

这道题相对来说还是非常水的。

因为本题中说共有 $T$ 组数据，所以我们需要循环 $T$ 次。我们这里设停办年份 $s_i$ 在 $y_2$ 之后的个数为 $cnt$，对于每一组数据，答案就是 $y_2-y_1-n+cnt+1$。

> Q：为什么最后还要 $+1$？

> A：因为开始年份和结束年份都包括在内。因为比如 $2003$ 开始举办，询问 $2003$ 年是第几次，答案应该是 $1$ 而不是 $0$。

## 代码实现

```cpp

#include<iostream>
using namespace std;
int t,y1,n,s[1001],y2;
int main()
{
	cin>>t;
	while(t--)//有T组输入
	{
		cin>>y1>>n;
		int cnt=0;
		for(int i=1;i<=n;i++)cin>>s[i];
		cin>>y2;
		for(int i=1;i<=n;i++)//统计停办年份s_i在y_2之后的个数
			if(s[i]>y2)
				cnt++;
		cout<<y2-y1-n+cnt+1<<endl;
	}
	return 0;
}

```

创作不易，点个赞吧！

---

## 作者：2c_s (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P9690)

## 思路

一道挺好的二分查找题。

读入数据后查找 $s_1,s_2,...,s_n$ 年中在 $y_2$ 后面的第一个年份的位置，得出到 $y_2$ 为止所有不举办的年份数。之后再用 $y_1-y_2$ 得到的总年份数减去前面计算出来的所有不举办的年份数就是结果。由于首尾的两个年份也包括，所以我们再 $+2$。

- 题目中保证序列 $s$ 单调递增，所以不用排序了。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll x){//快写。
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<1)+(y<<3);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}
const int N=110;
int y,n,a[N],yy;
int main(){
	int T;
	cin>>T;
	while(T--){
		y=read(),n=read();
		for(int i=1;i<=n;++i)a[i]=read();
		yy=read();
		int p=lower_bound(a+1,a+1+n,yy)-a;
		print(yy-y-p+2);
		putchar('\n');//别忘输出回车。
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/127405472)

---

## 作者：Ice09 (赞：3)

## 题目大意

某程序设计竞赛自 $y_1$ 年起开始举办。除了 $s_1, s_2, \cdots, s_n$ 这 $n$ 年由于特殊原因无法举办之外，其他年份每年举办一次。给出 $y_2$，求 $y_2$ 年是该竞赛的第几次举办。

[题目链接](https://www.luogu.com.cn/problem/P9690)。

## 题目思路

可以见到这题数据范围明显不大。~~所以我们怎么乱搞都没事~~。

我们可以定义数组 $srr$，$srr_i$ 表示到第 $i$ 年为止，一共有几次因特殊原因没举办。那么答案就是： $y_2-y_1+1-srr_{y_2}$。其中 $y_2-y_1+1$ 表示 $y_1$ 到 $y_2$ 之间有多少年，$srr_{y_2}$ 表示到第 $y_2$ 年为止，一共有几次因特殊原因没举办。

## 代码实现

```
#include <iostream>
#include <cstring>
using namespace std;
int t;
int y1, n, s[105], y2, srr[10005];
int main() {
	cin >> t;
	while (t--) {
		cin >> y1 >> n;
		for (int i = 1; i <= n; i++) {
			cin >> s[i];
			srr[s[i]]++;//第s[i]年有一次没举办
		}
		cin >> y2;
		for (int i = 1970; i <= 9999; i++) {
			srr[i] += srr[i - 1];//进行一次前缀和操作，即可建立srr数组
		}
		cout << y2 - y1 + 1 - srr[y2] << endl;//别忘了换行
		memset(srr, 0, sizeof(srr));//别忘了srr数组归零
	}
	return 0;
}
```

---

## 作者：Zeryboy (赞：1)

原题地址：[P9690 原题题面](https://www.luogu.com.cn/problem/P9690)

阅读完题目，我们可以开始推导这道题了。

### 推导过程：

1. 我们需要知道在 `y1` 到 `y2` 之间（包括两端）竞赛已经举办了多少次。首先，我们假设每年都会举办一次竞赛，这样 `y2 - y1 + 1` 就是该时间段的年份数。

2. 接下来，我们考虑那些特殊的年份，即那些没有举办竞赛的年份。我们从 `y1` 到 `y2` 逐年检查，如果某年出现在这些特殊的年份列表中，我们就将前面计算出的年份数减一。

3. 最后，我们获得了 `y2` 年是第几次举办的结果。

满分代码：
```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
	int T; // 测试用例的数量
	cin >> T;

	// 循环处理每一个测试用例
	while (T--) {
		int y1, n, y2;
		cin >> y1;  // 竞赛第一次举办的年份

		cin >> n;  // 没有举办竞赛的年份数
		set<int> s;  // 使用set存储这些年份，方便后续检查某年是否在其中
		for (int i = 0; i < n; i++) {
			int temp;
			cin >> temp;
			s.insert(temp);  // 将没有举办竞赛的年份插入到set中
		}

		cin >> y2;  // 需要查询的年份

		// 默认假设从y1到y2的每年都举办了竞赛
		int held_count = y2 - y1 + 1;

		// 减去那些特殊的年份，即没有举办竞赛的年份
		for (int year : s) {
			// 只考虑y1到y2之间的年份
			if (year <= y2 && year >= y1) {
				held_count--;
			}
		}

		// 打印结果
		cout << held_count << endl;
	}

	return 0;
}
```


---

## 作者：Big_Dinosaur (赞：1)

只需要把停办的年份标记一下，再从 $y_1$ 枚举到 $y_2$，只需要这个年份没有被标记，就将一个 $ans$ 加 $1$。最后，输出 $ans$ 就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int r(){
int Z=1,Y=0;char T=getchar();while(T<'0'||T>'9'){if(T=='-')Z=-1;T=getchar();}
while(T>='0'&&T<='9'){Y=(Y<<3)+(Y<<1)+T-48;T=getchar();}return Z*Y;
}
int t=r(),stop[11111];
void sl(){
int y1=r(),y2,n=r(),ans=0;memset(stop,0,sizeof(stop));
for(int i=1;i<=n;++i)stop[r()]=1;y2=r();
for(int i=y1;i<=y2;++i)if(!stop[i])++ans;cout<<ans<<'\n';
}
signed main(){
while(t--)sl();
}
```

注意，多测不清空，爆零两行泪。

---

## 作者：lbh666 (赞：1)

## 题目大意
给出 $T$ 组数据，每组数据包含了竞赛首次举办的时间，还有 $n$ 个停办的年份，再给出一个年份，求这年是竞赛的第几次举办，题目数据保证最后给出的年份没有停办这个竞赛。

## 思路分析
- 把竞赛首次举办的时间和给出的年份按题目所说设为 $y_1$ 和 $y_2$。

- 我们**假设**这个竞赛没有停办过，那么第几次举办的答案就是 $y_2 - y_1 + 1$，用一个变量 $ans$ 来记录它。

- 由于题目是按递增顺序给出停办年份的，所以逐一跟 $y_2$ 比对，如果大于 $y_2$，我们就不用管了，因为后面的年份对答案没有贡献。

- 对于每次找到小于 $y_2$ 的停办年份，我们让 $ans$ 减一，让查询的下标加一即可，因为停办那年是不算进举办次数的，所以要更新 $ans$。

- 最后对于每次询问，输出 $ans$。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;

int a[105];
int cnt=0,n,t,head,ans,s;

int main(){
	cin>>t;
	while(t--){
		int tot=1;
		cin>>head; //head代表竞赛首次举办的时间 
		cin>>n;
		for(int i=1;i<=n;++i)cin>>a[++cnt]; //输入停办年份，用a数组存下 
		cin>>s; //要询问的年份 
		ans=s-head+1; //假设竞赛没有停办过 
		while(a[tot]<s && a[tot]!=0){ //逐一比对，注意：要特判后面是0的时候 
			--ans;
			++tot;
		}
		cout<<ans<<"\n"; 
		memset(a,0,sizeof(a)); //做好下次循环的初始化 
		cnt=0; 
	}
	return 0;
}
```

#### 最后，感谢管理员辛苦的审核！

---

## 作者：xiazha (赞：1)

### 思路

大水题，~~我重现赛就对这一道~~。

首先我们不考虑无法举办的年份，那么 $y_2$ 年就是第 $y_2-y_1+1$ 次举办。

然后再用一个计数变量统计 $y_1$ 到 $y_2$ 年之间没有举办的年数，将答案再减去没有举办的年数即可。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[10001],b,c,cnt;
signed main()
{
	cin>>t;
	while(t--)
	{
		cnt=0;
		cin>>b>>n;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		cin>>c;
		for(int i=1;i<=n;i++)
			if(a[i]<c) cnt++;
			else break;
		cout<<c-b+1-cnt<<"\n";
	}
	return 0;
}
```


---

## 作者：xiaoyang111 (赞：1)

# P9690 [GDCPC2023] A-Programming Contest 题解

## 前言

[题面。](https://www.luogu.com.cn/problem/P9690)

[可能更好的的阅读体验。](https://www.luogu.com.cn/blog/xiaoyang111/p9690-gdcpc2023-a-programming-contest-ti-xie)

## 讲解

### 思路

我们先形式化题面一下，方便理解下面部分。

> 给出 $y_1 , n , s_1 , s_2 , ⋯ , s_n$ 和 $y_2$，求区间 $[y_1 , y_2]$ 之间除开 $s$ 里面的每个数，除开 $s$ 里的每个数过后这个区间有多少个数。

我们分成几部分求解这个问题。

1. 拿到数据过后拿个桶来记录一下 $s_i$ 不能出现在这个区间。

2. 遍历 $[y_1,y_2]$ 区间。当遍历到数字 $i$ 的时候，判断 $i$ 能否出现在这个区间里，如果能，答案加一。

3. 输出答案。

这里我用的桶是哈希表，也就是 STL 的 unordered_map，来记录能否出现在这个区间，也可以用数组来当作桶。

时间空间充裕，可以通过此题。

### 代码

这个题要多测，每次输出过后记得要换行。

代码风格可能有些难看，敬请见谅。

```cpp
#include <iostream>
#include <unordered_map>//头文件
using namespace std;
int main(){
	int t;
	cin >> t;//多测
	for (int _=0;_<t;++_){//多测
		int y1;
		cin >> y1;//输入。
		int n;
		cin >> n;//输入。
		unordered_map<int,int> m;//桶。
		for (int i=0;i<n;++i){
			int s;
			cin >> s;//输入。
			m[s]=1;//记录。
		}
		int y2;
		cin >> y2;//输入。
		int ans=0;//答案。
		for (int i=y1;i<=y2;++i){
			ans+=!m[i];//如果不能出现在区间里就加 0 否则加 1。
		}
		cout<<ans<<endl;//输出。
	}
	return 0;
}
```

[AC 记录。](https://www.luogu.com.cn/record/127248700)

---

## 作者：skyskyCCC (赞：1)

## 前言。
一道模拟题，可以算作签到题。
## 分析。
因为题目数据范围很小，所以我们可以从 $y_1$ 开始枚举，直到 $y_2$ 终止。在此期间，如果遇见未举办年份，标记一下，然后跳过统计答案即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int t,n,s,y11,y22;//注意变量名与自带函数冲突。
int ans,vis[100005];
template <typename T> void read(T &x) {
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}//快读，可省略。
int main(){
	read(t);
	while(t--){
		ans=0;
		memset(vis,0,sizeof(vis));
		read(y11);read(n);
		for (int i=1;i<=n;i++){
			read(s);
			vis[s]=1;//标记未举办年份。
		}
		read(y22);
		for (int i=y11;i<=y22;i++){
			if(vis[i])continue;
			else ans++;
		}
		write(ans);
		printf("\n");
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：CNS_5t0_0r2 (赞：1)

因为 $s$ 数组单调递增，所以可以用 ``std::lower_bound`` 在 $O(\log n)$ 的复杂度内查询小于 $y_2$ 最后一个停赛年份的下标（因为所有停赛年份不同，所以 ``upper_bound`` 和 ``lower_bound`` 都可以），即可知在 $y_2$ 之前停了几次赛。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 109;
int t;
int n,s[N];
int main(){
	scanf("%d", &t);
	for(;t;t--){
		int y1,y2;
		scanf("%d", &y1);
		scanf("%d", &n);
		for(int i = 1;i <= n;i++)
			scanf("%d", &s[i]);
		scanf("%d", &y2);
		int pos = (lower_bound(s + 1,s + n + 1,y2) - s) - 1;
		printf("%d\n", y2 - y1 + 1 - pos);
	}
}
```


---

## 作者：Lemon_zqp (赞：0)

### 思路1
可以直接枚举，注意如果 $s_i$ 大于 $y_2$ 的话就直接跳过，不需要减次数。
### 代码1
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[105];

signed main()
{
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++){
		int b, e, ans = 0;
		cin >> b;
		int n;
		cin >> n;
		for(int j = 1; j <= n; j++){
			cin >> a[j];
		}
		cin >> e;
		for(int j = b; j <= e; j++){
			for(int k = 1; k <= n; k++){
				if(j == a[k]){
					ans -= 1;
					break;	
				}
			}
			ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
```
### 思路2
第二种思路就是一开始把 $ans$ 设为 $n$，就是假设都小于$y_2$，然后再把 $s_1$ 到 $s_n$ 枚举一遍，把大于 $y_2$ 的减去，最后再拿总年数，也就是 $(y_2 - y_1) + 1$，再减去 $ans$ 输出即可。
### 代码2
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[105];

signed main()
{
	int t;
	cin >> t;
	for(int i = 1; i <= t; i++){
		int b, e;
		cin >> b;
		int n;
		cin >> n;
		for(int j = 1; j <= n; j++){
			cin >> a[j];
		}
		cin >> e;
		int ans = n;
		for(int j = 1; j <= n; j++){
			if(a[j] > e){
				ans--;
			}
		}
		cout << (e - b + 1) - ans << endl;
	}
	return 0;
}
```


---

## 作者：Jasoncwx (赞：0)

## 题目思路
首先我们可以算出 $[y_1,y_2]$ 一共有多少个数，用 $ans$ 表示。

然后我们再枚举 $s$ 数组，当 $y_1<s<y_2$ 时，表示停办年份，那么举办的年份就应该 $-1$ 即 $ans\leftarrow ans-1$。

最后输出 $ans$ 即为答案。
## 代码
```cpp
//By Jasoncwx
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int l,r,a[105],ans;
        int n;
        cin>>l>>n;
        for(int i=0;i<n;i++)cin>>a[i];
        cin>>r;
        ans=r-l+1;
        for(int i=0;i<n;i++){
            if(a[i]>=l&&a[i]<=r)ans--;
        }
        cout<<ans<<endl;
    }
}
```


---

## 作者：metrixgo (赞：0)

一道极简模拟题，实现方法如下：

题意可以理解为输入一个左端点 $l$ 和一个右端点 $r$，然后在 $l$ 和 $r$ 之间有一些元素被剔除，要你求剩下在这个区间里的元素个数。

不难发现，如果一个元素没剔除，那么元素个数就是 $r-l+1$。所以我们只需以这个数为基准，减去在这个区间里被剔除的元素个数 $i$。最终答案就是 $r-l-i+1$。找到区间里被剔除的元素个数的方法就是从左往右搜索，因为给的是严格上升的数列，所以当搜到一个大于右端点 $r$ 的元素时，这个元素的下标即为在这个区间里被剔除的元素个数。

而且这一题基本没什么坑，不用开 $64$ 位整型，不用考虑特殊情况，可以放心做。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,k,n,m,t,a[105];
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(i=1;i<=k;i++) cin>>a[i];
        cin>>m;
        for(i=1;i<=k;i++)
        {
            if(a[i]>m) break;//该停办年份已经在询问年份之后了
        }
        cout<<m-n+1-i+1<<endl;
    }
    return 0;
}

```

---

## 作者：what_could_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9690)

简单模拟题。

我们只需要在输入时对于每一个停赛的年份打上标记，接下来直接从 $y_1$ 开始枚举年份到 $y_2$。如果中途的年份没被打上标记则次数加 $1$，最后输出次数。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int y1,n,y2,ans=0;
		bool b[10010]={0};
		scanf("%d%d",&y1,&n);
		for(register int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			b[x]=1;
		}
		scanf("%d",&y2);
		for(register int i=y1;i<=y2;i++)
		{
			if(b[i]) continue;
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

一道萌萌模拟题。把所有停办的年份打上标记，然后从 
$y_1$ 枚举到 $y_2$，如果没有被标记过就将计数器加一。最后输出计数器就做完了。注意多测清空。

```
#include <bits/stdc++.h>
using namespace std;

const int M = 1e4 + 5;
bool vis[M];

void solve() {
	memset(vis, false, sizeof vis);
	int y1, n, y2;
	cin >> y1 >> n;
	while (n--) {
		int x;
		cin >> x;
		vis[x] = true;
	}
	cin >> y2;
	int ans = 0;
	for (int i = y1; i <= y2; i++) ans += !vis[i];
	cout << ans << '\n';
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Clarinet (赞：0)

这次比赛终于有中文题面了，好耶！
# 简要题意
有 $T$ 组数据，其中每组数据给出该赛事的第一场比赛年份、当前年份和决定取消比赛的年份，求到当前年份共举行了几场比赛。
# 分析
首先从当前年份到第一场比赛的年份中间共有 $y_{2}-y_{1}+1$ 年可以举行比赛，我们再判断一下在停办了 $n$ 次的比赛中是否有在这一范围的年份。如果有，减去一即可，还是比较简单的。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,r,n,a[100010],ans;
int main(){
	cin>>t;
	while(t--){
		cin>>l>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		cin>>r;
		ans=r-l+1;
		for(int i=1;i<=n;i++){
			if(a[i]>=l&&a[i]<=r)ans--;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
感谢阅读！

---

## 作者：ccg12345 (赞：0)

签到题。

## 思路

从 $y_1$ 枚举到 $y_2$，看枚举的年份是否是停办年份，若不是则答案加一。

附代码：

```
#include <bits/stdc++.h>
using namespace std;
bool flag[10005];
void slv()
{
	memset(flag, 0, sizeof flag);
	int y1, n, y2, ans = 0;
	cin >> y1;
	cin >> n;
	for(int i = 1, k; i <= n; i++)
		cin >> k, flag[k] = 1; //用flag数组记录每个停办年份
	cin >> y2;
	for(int i = y1; i <= y2; i++)
		if(!flag[i])       //若不是停办年份则答案加一
		    ans++;
	cout << ans << endl;
}
int main()
{
	int t;
	cin >> t;
	while(t--)
		slv();
	return 0;
}
```


---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/P9690)
### 作为比赛的第一题，这道题还是相当简单的，~~连我这个蒟蒻都会~~。
我的思路很简单，每组数据用一个数组把停办年份存起来，判断在题目问的年份前有多少年停办了竞赛，再用总年数减去停办的年份数。
```cpp
#include<bits/stdc++.h>//蒟蒻只会万能头
using namespace std;
int t;//组数
int main(){
	scanf("%d",&t);//个人喜欢使用scanf和printf输入输出
	for(int i=1;i<=t;i++){
		int l,n,a[105],r,ans=0;
		scanf("%d%d",&l,&n);
		for(int j=1;j<=n;j++)scanf("%d",&a[j]);//使用数组将停赛年份存起来
		scanf("%d",&r);
		ans+=r-l+1;//总年份
		for(int j=1;j<=n;j++){
			if(a[j]>r)break;
			ans--;//减去停赛年份
		}
		printf("%d\n",ans);//输出
	}
	return 0;
}
```

---

## 作者：Srikasso (赞：0)

# 思路
计算出举办的总年数，再减掉停办的年数。

总年数为```要求的年份-第1次举办的年份+1年```

# 细节
如何求停办的年数呢？

用循环遍历挨个比对，找到比**要求的年份**小的年份，减掉。

用题目的变量来说就是
```
if(a[i] < y2){//a[i]纪录停办的年份
	ans--;//计数
}
```

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,i,n,ans,y1,y2,a[100000];
int main(){
	cin>>t;
	while(t --){
		cin>>y1;
		cin>>n;
		for(i = 1;i <= n;i ++){
			cin>>a[i];//a[i]纪录停办的年份
		}
		cin>>y2;
		ans = y1 - x + 1;//总年数 
		for(i = 1;i <= n;i ++){
			if(a[i] < y2){
				ans--;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```




---

## 作者：__Octhyccc__ (赞：0)

怎么说呢，虽然是道红题，但是细节挺多的。

在这之前，先把坑点说一说。

- 多测清空变量。

- 要是统计在 $[l,r]$ 中有多少个整数，应该是 $r-l+1$（千万别忘了 $+1$）。

思路很简单，先找到在 $y_2$ 年前最后一次停办的年份，可以统计出在 $y_2$ 年时共停办了多少次。设停办了 $x$ 次，答案就是 $y_2-y_1-x+1$。

既然说到这了，AC 代码必不可少：

```cpp
#include<cstdio>
int T,a[100],x,y,n;
int main(){
	scanf("%d",&T);
	while(T--){
		for(int i=0;i<100;i++){
			a[i]=0;
		}
		x=0,y=0,n=0;
		scanf("%d%d",&x,&n);
		for(int i=0;i<n;i++)scanf("%d",&a[i]);
		scanf("%d",&y);
		int z=0;
		for(int i=0;i<n;i++){
			if(a[i]>y){
				z=i;break;
			}
		}
		if(y<a[0]){
			printf("%d\n",y-x+1);continue;
		}
		z==0?printf("%d\n",y-n-x+1):printf("%d\n",y-z-x+1);
	}
	return 0;
}
```

---

## 作者：littleqwq (赞：0)

# P9690 题解

### 题目意思：

这题的大概意思就是程序设计比赛每年一次，其中有 $n$ 年不举办，请问从 $y _ 1$ 年到 $y _ 2$ 年一共举行了几次程序设计大赛。

### 思路：

通过计算我们会发现，想要求 $y _ 1$ 年到 $y _ 2$ 年之间有多少年，公式为 $y _ 2 - y _ 1 + 1$，其实公式在样例解释里就可以看到，接着我们把不在 $y _ 1$ 和 $y _ 2$ 区间内的时间去掉，算出有几个暂停年份在区间内，用刚才算出的总年数减去它，即可得到正确答案！

### 代码：

```
#include<bits/stdc++.h>
using namespace std;
long long t;
long long a[1000001],n,x,y; 
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
    	cin>>x;
    	cin>>n;
    	memset(a,0,sizeof a);
    	for(int j=1;j<=n;j++){
    		cin>>a[j];
		}
		cin>>y;
		int cnt=0;//计数
		for(int j=1;j<=n;j++){
			if(a[j]>y||a[j]<x){//不在区间内
				cnt++;//增加
			}
		}
		n=n-cnt;//算出在区间内的
		cout<<y-x+1-n<<endl;//输出，别忘换行
	}
    return 0;
}
```

这道题就结束啦！

---

