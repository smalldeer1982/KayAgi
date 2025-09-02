# drink

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/8u8szw7z.png)

## 题目描述

你面前有 $n$ 个瓶子，从左到右依次编号为 $1 \sim n$，瓶子可能是空的也可能装着水。

你可以选择一对 $l,r(l \le r)$，然后把 $l\sim r$ 号瓶子中的所有水全部喝完。你想一口气把桌上剩的水全喝完，请问你最少要拿起几个瓶子？

你有可能一个瓶子都不需要拿起来。

## 说明/提示

**【样例说明】**

样例 $1$ 中，拿起 $4$ 号瓶子即可。总共拿起 $1$ 个瓶子。

样例 $2$ 中，拿起 $3\sim 6$ 号瓶子可以将所有的水喝完。总共拿起 $4$ 个瓶子。

**【数据范围】**

对于 $30\%$ 的数据，保证 $n\le 100$。

对于 $60\%$ 的数据，保证 $n\le 2000$。

对于 $100\%$ 的数据，保证 $1\le n\le 10^5$，$0\le a_i\le 1$。

## 样例 #1

### 输入

```
5
0 0 0 1 0```

### 输出

```
1```

## 样例 #2

### 输入

```
6
0 0 1 1 0 1```

### 输出

```
4```

# 题解

## 作者：wmrqwq (赞：14)

# 原题链接

[P9517 drink](https://www.luogu.com.cn/problem/P9517)

# 题目简述

给定一个只包含 $0$ 和 $1$ 的序列，求序列中第一个 $1$ 出现的位置到最后一个 $1$ 出现的位置一共有多少个数字。

# 解题思路

这道题是一道模拟题，只需要依次判断第一个 $1$ 出现的位置和最后一个 $1$ 出现的位置有几个数字即可，不过还有一些小细节，比如序列中没有 $1$ 的情况，这时只需要判断一下，即可通过此题。

# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0;
long long n,a[100010],b,c;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if(a[i]==1)
			c=i;//统计最后一个1出现的位置
	}
	for(int i=0;i<n;i++)
		if(a[i]==1)
		{
			b=i;//统计第一个1出现的位置
			break;
		}
	if(b==0 && c==0)//注意这里要特判
		cout<<0;
	else
		cout<<c-b+1;//注意这里要加上1
	QwQ;
	
}

```


---

## 作者：_H17_ (赞：14)

## 题目大意

选一段最短的区间使得每瓶水都能喝了。

## 做法

把第一瓶水的位置和最后一瓶水的位置找出，求区间长度。

**注意：当没水的时候答案是 $0$！**

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],f=2e9,l=0;//初始化
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]){
            f=min(f,i),l=max(l,i);//找第一个和最后一个
        }
    }
    if(f==(int)(2e9)&&l==0)
        l=-1,f=0;
    //特判没水
    cout<<l-f+1;
    return 0;
}
```

---

## 作者：Lemon_zqp (赞：13)

### 思路
很简单，只要找出第一个出现 $1$ 的位置，然后找出最后一个出现 $1$ 的位置，然后将两个数相减加一就可以了，记得要特判一下，如果全是 $0$ 就直接输出 $0$ 结束即可。
### 代码
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;

bool if_nz;

int main()
{
	int n, l = 0, r = 0;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		int a;
		cin >> a;
		if(a == 1)
		{
			if_nz = true;
			if(l == 0)
			{
				l = i;
			}
			r = i;
		}
	}
	if(!if_nz)
	{
		cout << 0;
	}
	else
	{
		cout << r - l + 1;
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：8)

# 题目大意

有 $n$ 个瓶子，从左到右依次编号为 $1 \sim n$，瓶子可能是空的也可能装着水，可以选择一对 $l,r(l \le r)$，然后把 $l\sim r$ 号瓶子中的所有水全部喝完。你想一口气把桌上剩的水全喝完，请问你最少要拿起几个瓶子？

**你有可能一个瓶子都不需要拿起来。**
# 题目思路：

这题思路明确，从第一个有水的瓶子开始往后搜，直到最后一个有水的瓶子，之中所搜的次数就是答案。

首先用一个 $zero$ 代表有水瓶子的个数，接着用 $jl$ 表示第一个有水的瓶子。

然后我们从 $jl$ 开始一直往后搜，碰到有水的瓶子就 $zero-1$，直到 $zero=0$，每一次搜索都要 $cnt+1$，最后直接输出。

等等，结束了吗？这样子只有九十分！因为：你有可能一个瓶子都不需要拿起来。

所以判断一下：如果瓶子全为空，那么输出零，直接结束程序。

综上，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	bool a[100050];
	cin>>n;
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	int aaa=0;
	for(int i=0;i<n;i++){
		aaa+=a[i];		
	}
	if(!aaa){
		cout<<0;
		return 0;
	}
	int ans=0,zero=0,jl;
	for(int i=0;i<n;i++){
		if(a[i]==true){
			zero++;
		}
	}
	for(int i=0;i<n;i++){
		if(a[i]==true){
			jl=i;
			break;
		}
	}
	for(int i=jl;i<n;i++){
		ans++;
		if(a[i]==true){
			zero--;
		}
		if(!zero){
			break;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：zhang_Jimmy (赞：6)

我们可以先从前往后扫描一遍序列，找到第一个 $1$ 的位置。

再从后往前扫描一遍，找到最后一个 $1$ 的位置。

然后用最后一个 $1$ 的位置减去第一个 $1$ 的位置 的差加上 $1$ 即可。

另外还要特判序列全是 $0$ 的情况。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100010],n;
int main(){
 	int i,j;
 	cin>>n;
 	for(int i=1;i<=n;i++) cin>>a[i];
 	for(i=1;i<=n;i++)
 	if(a[i]==1) break;
 	if(i==n+1) //特判序列全是0的情况
 	{
 		cout<<0;
 		return 0;
	}
 	for(j=n;j>=1;j--)
 	if(a[j]==1) break;
 	cout<<j-i+1;
	return 0;
}
```


---

## 作者：cirrationaler (赞：4)

简单题。

先用一个结构体分别表示 `first last`，然后进行查找即可，两个 `for` 循环分别计算出 `first` 和 `last`，最后计算它们的差值。~~（注意，计算差值时要加 1）~~

然后你就会发现一个问题：只有 $90$ 分。

所以我们来思考一下哪里出现了问题。

你会发现：如果全都是 $0$ 怎么办呢？

所以还要记录是不是全都是 $0$，如果是就输出 $0$ 即可得到满分。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

struct cntt
{
	int first, last;
}cnt;

int n;
int a[MAXN];
int cnttt;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		if (a[i] == 0)
		{
			cnttt++;
		}
	}
	if (cnttt == n)
	{
		printf("0");
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 1)
		{
			cnt.first = i;
			break;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if(a[i] == 1)
		{
			cnt.last = i;
		}
	}
	printf("%d", cnt.last - cnt.first + 1);
	return 0;
}
```

---

## 作者：wcop114514 (赞：3)

**题目分析**

它让我们寻找最少拿起的瓶子数。

那我们可以从左边开始找第一次出现 $1$ 的位置，右边也一样，相减 $+1$， 得出答案。

但要特判，若都为零输出 $0$。

给各位大佬奉上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,ans=0,cnt=0,num=0;int a[100005];
	cin>>n;
	for(int i=1;i<=n;i++){
	cin>>a[i];	
	if(a[i]==0)num++;
	}
	if(num==n){
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			ans=i;
			break;
		}
	}for(int i=n;i>=1;i--){
		if(a[i]==1){
			cnt=i;
			break;
		}
	}
	
	cout<<cnt-ans+1;
	return 0;
}
```

---

## 作者：Double_Light (赞：3)

# P9517 drink 题解

### 思路

很明显，由于只能拿一次瓶子，所以我们一定要将所有装满水的瓶子都拿起来。

基于以上一点，可以推断出 $l$ 小于等于左数第一个有水的瓶子的编号，$r$ 大于等于右数第一个有水的瓶子的编号。

由于拿起来的瓶子要尽可能少，也就是让 $l$ 尽可能大，$r$ 尽可能小，所以 $l$ 等于最左边有水瓶子的编号，$r$ 等于最右边有水瓶子的编号。最后拿起来的瓶子数量是 $r-l+1$。

最后注意一点，如果一个有水的瓶子都没有，那么直接输出 $0$。

### 代码

```cpp
#include<iostream>
using namespace std;
int n,l,r,a[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){//从左往右枚举l的最大值
		if(a[i]){//瓶子里有水
			l=i;
			break;
		}
	}
	for(int i=n;i>=1;i--){//从右往左枚举r的最小值
		if(a[i]){
			r=i;
			break;
		}
	}
	if(l==0&&r==0)cout<<0;//特判每个瓶子里都没水
	else cout<<r-l+1;
	return 0;
}
```


---

## 作者：_O_v_O_ (赞：3)

既然问的是**最少**要拿起几个瓶子，那就要尽可能少拿空瓶。

既然这样，$a_l$ 和 $a_r$ 肯定都是 $1$。

证明：如果 $a_l$ 为 $0$，区间 $[l,r]$ 包含了所有 $1$，那么区间 $[l+1,r]$ 一定也包含了所有 $1$，因为喝时不会喝 $a_l$。$r$ 为 $0$ 是同理。

那我们就可以得出一个结论：$l$ 为 $a$ 数组中从左往右第一个 $1$ 的下标，$r$ 为 $a$ 数组中从右往左第一个 $1$ 的下标。最后直接输出 $r-l+1$ 即可。

不过还有特判：如果 $a$ 中全部为 $0$，那么就一瓶都不选，就输出 $0$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[100005];

signed main(){
	std::ios::sync_with_stdio(0);
	cin.tie(nullptr);  //输入优化。
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	bool fg=false;  //特判：看里面是不是全是 0。
	for(int i=1;i<=n;i++){
		if(a[i]){
			fg=true;
			break;
		}
	}
	if(!fg){
		cout<<0;
		return 0;
	}
	int l,r;  //找到 l,r。
	for(int i=1;i<=n;i++){
		if(a[i]==1){
			l=i;
			break;
		}
	}
	for(int i=n;i>=1;i--){
		if(a[i]==1){
			r=i;
			break;
		}
	}
	cout<<r-l+1;
	return 0;
}
```


---

## 作者：hgwjjbl (赞：2)

找出开头和结尾就行了。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int a,b,n,sum=0,l=0,r=0;
	bool s=true;
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		if(s&x==1){//开头
			s=false;
			l=i;
		}
		if(x==1){//结尾
			r=i;
		}
	}
	if(l-r==0){//特判
	    cout<<0<<endl;
	}
	else{
	    cout<<r-l+1<<endl;
	}
	return 0;
}
```


---

## 作者：zsh_haha (赞：2)

### 思路讲解

这道题我们从第一个**有水的瓶子**开始喝，直到最后一个**有水的瓶子**。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool b[100005];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		if(b[i]){
			l=i;
			break;
		}
	}
	for(int i=n;i>=1;i--){
		if(b[i]){
			r=i;
			break;
		}
	}
	if(l==0){//注意没有有水瓶子的情况 
		cout<<0;
		return 0;
	}
	cout<<r-l+1;
	return 0;
}
```

---

## 作者：残阳如血 (赞：2)

# 思路分析
我们只需要找到左边第一个大于 $0$ 的位置 $l$ 与右边第一个大于 $0$ 的位置 $r$，输出 $r-l+1$ 即可。

但是很坑的一点是，如果 $∀i∈[1,n],a_i=0$，那么 $l$ 和 $r$ 会重合，代码会输出 $1$！所以，我们需要定义一个 $flag$ 来标记是否全部输入为 $0$。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, l, r;
bool flag = true;
int main() {
	cin >> n;
	vector<int> a(n);
	for (auto &x : a) {
		cin >> x;
		if (x != 0) flag = false; // 如果非0那么就不需要特判了
	}
	if (flag) { // 如果全部为0，那么就输出0
		cout << 0;
		return 0;
	}
	for (l = 0; l < n; l++)
		if (a[l] >= 1) break; // 从左端开始找到第一个大于0的位置
	for (r = n - 1; r >= 0; r--)
		if (a[r] >= 1) break; // 从左端开始找到第一个大于0的位置
	cout << r - l + 1; // 一定要加1，否则就把l也去掉了
	return 0;
}
```

---

## 作者：FurippuWRY (赞：1)

题意化简：给出一个数列 $\{a_n\}$，求从第一个等于 $1$ 的 $a_l$ 到最后一个等于 $1$ 的 $a_r$ 之间共有几个数 （包括 $a_l$ 与 $a_r$）。

那么可以很快可以得出结论：$[a_l, a_r]$ 间共有 $r - l + 1$ 个数。

特判：如果数列中每个数都为 $0$，那么此时答案为 $0$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 9;

int n, a[N], l, r;
bool f;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i]) f = 1;
    }
    if (!f) {
        cout << 0;
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i]) {
            l = i;
            break;
        }
    }
    for (int i = n; i; --i) {
        if (a[i]) {
            r = i;
            break;
        }
    }
    cout << r - l + 1;
    return 0;
}
```

---

## 作者：E5pe7ance_ (赞：1)

一眼题。

找一个区间，使得区间内包含序列中所有的 $1$，求区间的长度。

正反各扫一遍，分别找出第一个 $1$ 的下标 $l$ 和最后一个 $1$ 的下标 $r$。答案为 $r-l+1$。

注意当序列中没有 $1$ 时，即 $l, r$ 都为 $0$ 时，输出 $0$。

```cpp
for (int i = 1;i <= n;i++) if (a[i] == 1) {lx = i; break;}
for (int i = n;i >= 1;i--) if (a[i] == 1) {rx = i; break;}
if (!lx && !rx) cout << 0;
else cout << rx-lx+1;
```

---

## 作者：Loser_Syx (赞：1)

简单题。

由于我们需要 $l \sim r$ 个连续的瓶子，所以初始时默认是 $1 \sim n$，此时考虑缩短区间，那么 $l$ 端点就可以扩大到第一个 $1$ 的位置，$r$ 可以缩小到最后一个 $1$ 的位置，那么答案是最后的区间 $l \sim r$ 的长度。

不要忘记特判都是 $0$ 的情况，不然就会 WA 掉。

---

## 作者：fish_love_cat (赞：1)

**题意：**

给你一个 $01$ 串，请你求出包含这个串中所有 $1$ 的子串长度的最小值。

**思路：**

显然的，这个字串能少包含 $0$ 就得少包含 $0$，所以最优的子串必然是从第一个 $1$ 开始，到最后一个 $1$ 结束，那么这个子串的长度就是最后一个 $1$ 的下标减去第一个 $1$ 的下标加 $1$。所以我们只要知道两者的下标即可算出答案了。

**注意：**

在没有 $1$ 的情况下长度为 $0$。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        if(x==1){
            b=i;
            if(!a) a=i;//边读边统计
        }
    }
    cout<<b-a+(b!=0?1:0);//记得特判
    return 0;
}
```

---

## 作者：hjqhs (赞：1)

题目是求 $1$ 第一次出现的位置到最后一次出现位置的距离。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int l,r;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		if(x==1&&l==0)l=i;
		if(x==1)r=i;
	}
	if(l==0&&r==0)return cout<<0,0;
	cout<<r-l+1;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题意
给了 $n$ 个瓶子和每个瓶子有水的情况，取最左边、最右边（有水）及中间的所有瓶子（不管有没有），统计这些瓶子的数量。
## 思路
遍历输入的数组，算出最左边和最右边有水的瓶子，用 $le$ 和 $ri$ 统计，最后输出 $le-ri+1$ 即可。注意特判全没水的情况！
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	bool vis[100050];//定义
	cin>>n;
	for(int i=0;i<n;i++) cin>>vis[i];//输入
	int le=0,ri=0;
	for(int i=0;i<n;i++){
		if(vis[i]){
			le=i;
			break;
		}
	}//算最左边
	for(int i=n-1;i>=0;i--){
		if(vis[i]){
			ri=i;
			break;
		}
	}//算最右边
	if(le==0&&ri==0) cout<<0;//特判
	else cout<<ri-le+1;//输出
	return 0;
}
```

---

## 作者：fuwei123 (赞：0)

## 题意
给定 $01$ 序列 $a$，求 $a$ 中第一个 $1$ 出现的位置 $i$ 和最后一个 $1$  出现的位置 $j$，输出这两者之间有多少元素。

## 做法
从头扫一遍，找到第一个 $a_i=1$，记录下来。

然后倒过来再扫一遍，找到最后一个 $a_j=1$，也记录下来。

直接输出 $j-i+1$ 即可，注意判断全 $0$ 的情况。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[100005];
signed main(){
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 1;i <= n;i++)cin >> a[i];
	int beg = 0, ed = 0;
	for(int i = 1;i <= n;i++){
		if(a[i] == 1){
			beg = i;
			break;
		}
	}
	if(beg == 0){
		cout << 0;
		return 0;
	}
	for(int i = n;i >= 1;i--){
		if(a[i] == 1){
			ed = i;
			break;
		}
	}
	cout << ed - beg + 1;
	return 0;
}


```


---

## 作者：Terry2011 (赞：0)

# 题目分析
因为这道题目需要通过选择一对 $l$，$r$，把两瓶水之间的水全部喝完，所以，我们可以分别寻找数组两边 $0$ 的个数，最后用总数减去 $0$ 的个数即可。还有，别忘了特判！即如果全部都是 $0$，输出 $0$。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,s[100050],cnt=0,ans=0,num=0;
    cin>>a;
    for(int i=1;i<=a;i++){
        cin>>s[i];
        if(s[i]==0) num++;
    }
    if(num==a){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=a;i++){
        if(s[i]==0) cnt++;
        else break;
    }
    for(int i=a;i>=1;i--){
        if(s[i]==0) cnt++;
        else break;
    }
    cout<<a-cnt;
    return 0;
}
```

---

## 作者：Vct14 (赞：0)

### 思路

因为要一口气喝完所有水，所以区间 $[l,r]$ 中必须含有所有装着水的瓶子。

因此我们需要找到第一个装着水的瓶子出现的位置作为 $l$，最后一个装着水的瓶子出现的位置作为 $r$。最终答案为 $[l,r]$ 区间内数的个数，即 $r-l+1$。

当然，还需要特判瓶子全空的情况。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int a[100002];

int main(){
	int n;
	cin>>n;
	bool all_empty=true;
	for(int i=1; i<=n; i++){
		cin>>a[i];
		if(a[i]) all_empty=false;
	}
	if(all_empty){
		cout<<0;
		return 0;
	}
	int l,r;
	for(int i=1; i<=n; i++){
		if(a[i]){
			l=i;
			break;
		}
	}
	for(int i=n; i>=1; i--){
		if(a[i]){
			r=i;
			break;
		} 
	}
	cout<<r-l+1;
	return 0;
}
```

---

