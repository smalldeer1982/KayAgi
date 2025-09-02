# [USACO20OPEN] Social Distancing I B

## 题目描述

一种新型疾病，COWVID-19，开始在全世界的奶牛之间传播。Farmer John 正在采取尽可能多的预防措施来防止他的牛群被感染。

Farmer John 的牛棚是一个狭长的建筑物，有一排共 $N$ 个牛栏（$2\le N\le 10^5$）。有些牛栏里目前有奶牛，有些目前空着。得知“社交距离”的重要性，Farmer John 希望使得 $D$ 尽可能大，其中 $D$ 为最近的两个有奶牛的牛栏的距离。例如，如果牛栏 $3$ 和 $8$ 是最近的有奶牛的牛栏，那么 $D=5$。

最近两头奶牛新来到 Farmer John 的牛群，他需要决定将她们分配到哪两个之前空着的牛栏。请求出他如何放置这两头新来的奶牛，使得 $D$ 仍然尽可能大。Farmer John 不能移动任何已有的奶牛；他只想要给新来的奶牛分配牛栏。 

## 说明/提示

### 样例解释 1

在这个例子中，Farmer John 可以以这样的方式加入奶牛，使得牛栏分配变为 `10x010010x0010`，其中 `x` 表示新来的奶牛。此时 $D=2$。不可能在加入奶牛之后取到更大的 $D$ 值。 

### 测试点性质

- 测试点 $2-6$ 满足 $N\le 10$。
- 测试点 $7-8$ 满足 $N\le 100$。
- 测试点 $9-11$ 满足 $N\le 5000$。
- 测试点 $12-15$ 没有额外限制。

## 样例 #1

### 输入

```
14
10001001000010```

### 输出

```
2```

# 题解

## 作者：1234567890sjx (赞：4)

看到最小值最大，所以想到二分答案。

设当前二分的 $D$ 值为 $p$，那么考虑计算出当前所有的差值，然后把两头奶牛贪心的插入到差值最大的地方即可。特殊的，有一种特殊情况是两头奶牛插入到了同一个地方，特判掉即可。

直接做即可。时间复杂度 $O(n\log n)$。

---

## 作者：fgcjd (赞：2)

来个不用二分的思路~~虽然有一点麻烦~~。

先按有牛的牛棚之间的距离排序，之后放的两头牛有以下几种情况：
- 开头放一个。
- 结尾放一个。
- 开头放两个。
- 结尾放两个。
- 间距最大的放一个。
- 间距第二大的放一个。

所以在这里面取间距第二大值即可。

特判：
- 间距最大的放两个。
- 没有一个牛栏有牛。
- 答案最多为所有牛栏之间间距最小值。

详细在代码：


```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <climits>
#include <iomanip>
#include <string>
using namespace std;
typedef long long ll;
int n;
string s;
int a[100010], m, ans, x, y;
int b[37], t;
int main(){
	cin >> n >> s;
	int cnt = 1;
	for (int i = 1; i <= n; i++){
		if (s[i - 1] == '1'){
			a[++m] = cnt;
			cnt = 1;
		}
		else cnt++;
	}
	if (a[1] == 0){ // 没有一个牛栏有牛
		cout << n - 1;
		return 0;
	}
	x = a[1], y = cnt; // 开头、结尾
	sort(a + 2, a + m + 1);
	b[++t] = x - 1; // 开头放一个
	b[++t] = y - 1; // 结尾放一个
	b[++t] = (x - 1) / 2; // 开头再放一个
	b[++t] = (y - 1) / 2; // 结尾再放一个
	b[++t] = a[m] / 2; // 间距最大放一个
	b[++t] = a[m - 1] / 2; // 间距第二大放一个
	sort(b + 1, b + t + 1);
	if (a[2] == 0) cout << max(b[t - 1], a[m] / 3); // 间距最大的放两个
	else cout << min(max(b[t - 1], a[m] / 3), a[2]/*牛栏之间间距最小值*/) << endl;
	return 0;
}

```

---

## 作者：InfiniteRobin (赞：2)

## P9952 题解  
### 思路
------------  
发现答案肯定在一个范围内，果断二分。其他的东西楼下的大佬们已经讲得很清楚了，这里我只给出另外一种 ```check``` 函数的写法。  

------------
设目前需验证的间距为 $mid$ :
-  如果碰到数字开头或结尾是 $0$ 的，要放下一头牛，则需要保证开头或结尾 $0$ 的数量 $n$ 满足：  
   $$n\ge mid.$$
	如果想放下两头，那么 $n$ 要满足：
	$$n\ge 2 \times mid.$$  
    
-  对于那些夹在 $1$ 中间的 $0$，要放下一头牛，则需要保证一段连续的 $0$ 的数量 $n$ 满足：  
   $$n\ge 2 \times mid -1.$$
	如果想放下两头，那么 $n$ 满足：
	$$n\ge 3 \times mid-1.$$  


------------
### AC CODE  
```cpp
#include<bits/stdc++.h>
using namespace std;

int a[100005];
int n;

bool check(int mid){
    int cow=0,zero=0; //牛的数量和零的数量 
    bool f=(a[1]==0),f1=1; //f记录第一个数是不是0，f1记录目前有没有碰到1 
    for(int i=1;i<=n&&cow<2;i++){
		if(a[i]==0){
        	zero++;
		}
		else{
			if(f&&f1){ //对应上面说到的第一种情况 
				if(zero>=mid){
					cow++;
					if(zero>=2*mid){ //如果放得下两头，直接结束 
						return 1;
					}
				}
				f1=0;
			}
			else{
				if(zero>=2*mid-1){ //对应上面说到的第二种情况 
					cow++;
					if(zero>=3*mid-1){ //如果放得下两头，直接结束
						return 1;
					}
				}
			}
			//clear
			zero=0; //记得清零 
		}
    }
    if(zero>=mid){ //再检验一次，以防最后一个数不是1 
		cow++;
		if(zero>=2*mid){
			return 1;
		}
	}
    if(cow<2){ //如果放不下两头 
        return 0;
    }
    return 1;
}


int main(){

    int mn=1e6,first1=0,second1=0; //分别对应二分的上限，上一个1的位置， 这一个1的位置
    bool f=0; //记录有没有一 
    cin>>n;
    for(int i=1;i<=n;i++){
        char s;
        cin>>setw(1)>>s;
        a[i]=s-'0';
		
		if(a[i]==1){
			f=1;
			first1=second1;
			second1=i;
			if(first1!=0){
				mn=min(mn,second1-first1); //改变上限的值 
			}
		}
    }
    
	if(first1==0){ //如果只有一个1 
		mn=max(n-second1,second1);
	}

    if(mn<=1){ //如果最小的间距已经为1，直接输出 
        cout<<1;
        return 0;
    }
    if(f==0){ //如果全是0 
        cout<<n-1;
        return 0;
    }

    int l=1,r=mn,mid,ans;
    while(l<=r){
        mid=(l+r)/2;
        if(check(mid)){
            l=mid+1;
            ans=mid;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans;
    return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/152534400)  


------------

### THE END

---

## 作者：dabenBbx (赞：1)

## 二分

题意：给出一个长度为 $n$ 的字符串。对于每一位如果是 $1$ 则代表有一只牛，反则代表为空。求再加入两只牛最大化最近的两只牛的距离。

分析：明显两只牛的距离是一个范围，我们直接考虑二分。二分距离，再从头到尾检查是否合法。不合法就缩小距离即可。

## **Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
bool c[100007];
int a[100007], cnt = 0;
int b[100007], bcnt;
int l = 1, r = 2e9, mid;

inline bool check(int x) {
	int num = 0; bcnt = cnt;
	for(int i = 1; i <= cnt; i++) b[i] = a[i];
	b[++bcnt] = 1 - x;
	b[++bcnt] = n + x;
	sort(b + 1, b + bcnt + 1);
	for(int i = 1; i <= bcnt; i++) {
		if(b[i] + x + x <= b[i + 1]) {
			num++;
			if(num == 1) {
				b[++bcnt] = b[i] + x;
				sort(b + 1, b + bcnt + 1);
			}
			if(num == 2) {
				return 1;
			}
		}
	}
	return 0;
}

signed main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		char ch; cin >> ch;
		c[i] = ch - '0';
		if(c[i] == 1) {
			a[++cnt] = i;
			if(cnt >= 2) r = min(r, a[cnt] - a[cnt - 1]);
		}
	}
	while(l <= r) {
		mid = (l + r) / 2;
		if(check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：卷王 (赞：1)

## 大体思路

这题的二分很一眼。感觉有些题解的代码过于复杂了。

考虑二分答案，如果可以插入两头牛则 $l=mid+1$，并更新 $ans$，否则 $r=mid-1$。

如何判定我们二分的 $mid$ 是否符合要求呢？

我们设 $a_i$ 表示第 $i$ 个已经有牛的牛栏的位置。容易发现，只要 $a_i + x+ x$ 还小于等于 $a_{i+1}$，那么在中间显然可以加一头牛。注意，两个已经有牛的牛栏之间可能可以把 $2$ 头牛都加进去，所以，安排完一头牛就直接更新 $a$ 数组。

然后注意一下把牛安排在边界的情况就可以了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
bool c[100007];
int a[100007], cnt = 0;
int b[100007], bcnt;
int l = 1, r = 2e9, mid;

inline bool check(int x) {
	int num = 0; bcnt = cnt;
	for(int i = 1; i <= cnt; i++) b[i] = a[i];
	b[++bcnt] = 1 - x;
	b[++bcnt] = n + x;
	sort(b + 1, b + bcnt + 1);
	for(int i = 1; i <= bcnt; i++) {
		if(b[i] + x + x <= b[i + 1]) {
			num++;
			if(num == 1) {
				b[++bcnt] = b[i] + x;
				sort(b + 1, b + bcnt + 1);
			}
			if(num == 2) {
				return 1;
			}
		}
	}
	return 0;
}

signed main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		char ch; cin >> ch;
		c[i] = ch - '0';
		if(c[i] == 1) {
			a[++cnt] = i;
			if(cnt >= 2) r = min(r, a[cnt] - a[cnt - 1]);
		}
	}
	while(l <= r) {
		mid = (l + r) / 2;
		if(check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：I_Love_DS (赞：1)

## 思路

看到“使得 $D$ 尽可能大”和“（$2 \le N \le 10^5$）”果断二分。

时间复杂度 $O(N \log N)$。

二分实现和写法看题解区其他人的就行，其他人已经写的很完善了。

本篇题解想介绍一种读入方法（字符串边读入边转入 `int` 类型数组，使得处理更方便）。

[这篇文章](https://blog.csdn.net/qq_15719613/article/details/120962669)把 `getchar()` 库函数讲的十分透彻。

## 读入方法

读入时间复杂度 $O(N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 50;
int N,a[MAXN];
int main(){
	scanf("%d",&N);//读入字符
	getchar();//清空缓冲区回车①
	for (int i = 1; i <= N; i++) a[i] = getchar() - 48;//读入字符串第 i 个字符，存入 a[i]（48 是 字符 0 的  ASCII 码）
	for (int i = 1; i <= N; i++) printf("%d",a[i]);//检测读入情况
	return 0;
}
```

运行结果：

![](https://cdn.luogu.com.cn/upload/image_hosting/xqashjn9.png)

【注释】①：如果删去这行，程序第 $8$ 行的读入字符串的循环当 $i = 1$ 时，会读入读入 $N$ 时留下的缓冲区里的换行符。由于换行符在 ASCII 编码里十进制为 $10$，所以会出现如下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/lh3eokgo.png)

谢谢观看，如果有疑问请在评论区留言，我会尽量看的！

---

## 作者：YNH_QAQ (赞：1)

## 分析

最小求最大，二分答案。

check 函数：

1. 对于空的牛棚，与此处前面的奶牛 $i$ 距离要大于当前的检查值 $mid$，就考虑放入这头牛。
2. 遍历到下一头牛时，检查把 $i$ 放在此处是否合法。

check时间复杂度：$O(n)$。

```cpp
bool check(int mid){
	int cnt=0,last=-1e9;
	for(int i=1;i<=n;i++){
		if(s[i]=='1'&&i-last<mid) return 0;
		if(s[i]=='1'){
			last=i;
		}
	}
	last=-1e9;
	for(int i=1;i<=n;i++){
		if(s[i]=='1'&&i-last<mid) cnt--;
		if((i-last>=mid)&&s[i]!='1'){
			last=i;
			cnt++;
		}
		if(s[i]=='1') last=i;
	}
	return cnt>=2;
}
```

二分复杂度：$O(\log n)$。
```cpp
while(l<=r){
	int mid=(l+r)/2;
	if(check(mid)){
		ans=mid;
		l=mid+1;
	}else{
		r=mid-1;
	}
}
```
谢谢观看。

---

## 作者：huangzilang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9952)

~~这道题卡了我十几次提交都没过~~

[我的提交记录](https://www.luogu.com.cn/record/list?pid=P9952&user=huangzilang&page=1)

**题目大意：**

给定一个长度为 $n$ 的字符串，也就是 $n$ 个字符，由 $n$ 和 $1$ 组成，描述牛棚里的牛栏。$0$ 表示空着的牛栏，$1$ 表示有奶牛的牛栏。插入两头奶牛，问你最近的奶牛之间的最大距离。

**思路：**

最近我一直在打二分，看到了最近的最大就确定了这是二分。先输入 $n$ 个字符，如果为 ```1``` 就记录当前的位置。然后就是二分，用一个 check 函数判断一下 $mid$ 的距离可不可行，如果可以，就把 $l$ 的值扩大；否则把 $r$ 的值缩小。

**代码：**


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[100005],t,b[100005];
int check(int x)
{
	for(int i=1;i<=t;i++)
	{
		b[i]=a[i];
	}
	int tot=t;
	b[++tot]=1-x;
	b[++tot]=n+x;
	sort(b+1,b+tot+1);
	int ans=0;
	for(int i=1;i<=tot;i++)
	{
		if(b[i]+(x*2)<=b[i+1])
		{
			ans++;	
			if(ans==2)
			{
				return 1;
			}
			else
			{
				b[++tot]=b[i]+x;
				sort(b+1,b+tot+1);
			}
		}
	}
	return 0;
}
signed main()
{
	cin>>n;
	int l=0,r=n;
	a[0]=INT_MIN;
	for(int i=1;i<=n;i++)
	{
		char ch;
		cin>>ch;
		if(ch=='1')
		{	
			a[++t]=i;
			r=min(r,a[t]-a[t-1]);
		}	
	}	
	int ans=-1; 
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))
		{
			l=mid+1;
			ans=mid;
		}
		else
		{
			r=mid-1;
		}
	}
	cout<<ans;
} 
```

---

## 作者：XiaoWhy (赞：0)

**思路**

提供一种贪心思路。

题目抽象来看就是 $01$ 字符串，让我们把两只牛插入到 $0$ 的位置，问最大的最短相邻距离，我们可以把每一段连续 $0$ 看作一个区间，又因为只有两只牛，所以我们就可以想到一个最直接的想法，可以把要么两个都在一个区间，要么两个牛在不同的区间内。

**注意点**：首尾得特殊考虑，因为我们把一头牛直接放在端点，这样可以剩下更多距离

- **放在相同区间中**

如果是首尾，那么我们肯定一个放在端点出，一个放在中间点。

因此如果是首部，$x$ 表示已有牛的位置，那么放两只牛，这个区间中最短距离就是 $(x-1)/2$。如果是尾部，$x$ 表示最后一只已经存在牛的位置,那么最短距离就是 $(n-x)/2$。

一般区间，那么我们画图感受一下，肯定就是类似三分点的位置，手画几个例子推导一下，可以得到一个公式，前后两只牛的位置如果是 $x,y$ 表示，那么放了两只牛之后，最短距离就是 $((y-x)-2)/3+1$。

* **放在相同区间中**

首先考虑一个放在首，一个放在尾，记为 $len_1,len_2$，可以交换一下，使得 $len_1＞len_2$，这样方便我们后续判断，然后我们再去考虑普通区间，此时我们得思考一下，如果我找到一个更大的区间，然后我们就应该把其中小的那个换了，因为这样可以使得两者中最小值最大。

**代码实现**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef pair<int,int> PII;
char a[N];
int pos[N];
int main(){
    int n,cnt=0;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) if(a[i]=='1') pos[++cnt]=i;
    if(!cnt){//不存在'1'
        cout<<n-1;//那么肯定就一个放1一个放n
        return 0;
    }
    int mi=1e9;//先求出没放之前已经存在的最短距离
    for(int i=2;i<=cnt;i++) mi=min(mi,pos[i]-pos[i-1]);
    //考虑在同一个区间
    int len=max((pos[1]-1)/2,(n-pos[cnt])/2);
    for(int i=2;i<=cnt;i++) len=max(len,(pos[i]-pos[i-1]-2)/3+1);
    //考虑在不同区间
    int len1=pos[1]-1,len2=n-pos[cnt];
    if(len2>len1) swap(len1,len2);//使得len1大于len2,方便下面判断
    for(int i=2;i<=cnt;i++){
        int d=(pos[i]-pos[i-1])/2;
        if(d>len2){//有上升空间
            len2=d;
            if(len2>len1) swap(len1,len2);
        }
    }
    cout<<min(mi,max({len,min(len1,len2)}));
    return 0;
}
```

---

## 作者：Cute__yhb (赞：0)

## 思路
最小值最大，考虑二分。

对于一个二分出来的 $mid$，如果某个牛栏是空的，并且此处与前面的一头奶牛的距离要大于 $mid$，就考虑把一头牛放在这里，在遍历到下一头奶牛时，在检查此处是否合法。时间复杂度 $O(n \log n)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int ans;
bool check(int mid){
	int m=0;
	int last=-1e9;
	for(int i=0;i<n;i++){
		if(s[i]=='1'&&i-last<mid) return 0;//放前就不满足条件
		if(s[i]=='1'){
			last=i;
		}
	}
	last=-1e9;//上一个
	for(int i=0;i<n;i++){
		if(s[i]=='1'&&i-last<mid) m--;//不满足条件
		if((i-last>=mid)&&s[i]!='1'){//可放
			last=i;
			m++;//计数器++
		}
		if(s[i]=='1') last=i;
	}
	return m>=2;//如果可以放两头以上，两头一定能放
}
int main(){
	cin>>n>>s;
	int l=1,r=1e5+10;
	while(l<=r){//二分
		int mid=(l+r)/2;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：Arson1st (赞：0)

## [P9952 [USACO20OPEN] Social Distancing I B](https://www.luogu.com.cn/problem/P9952) 题解

### 二分+贪心

看到“最大值最小”和 $N\le10^5$，果断二分。注意二分范围，题目中不仅要求考虑插入的两头牛与其前后的距离，还要考虑原本就存在的奶牛间的最短距离。所以二分下界是 $1$，而上界可以从 $\min \{j-i\}(j>i,pos_j=pos_i=1)$ 开始。$check$ 函数中有一个明显的贪心：一旦距离前一头牛的距离等于二分的 $mid$，就尝试在这里放上一头奶牛。如果发现这里放了奶牛会导致与下一头牛的距离小于 $mid$ 则撤销这次放置。一旦成功放置了两头奶牛就可以退出了。当然，如果开头的牛栏就为空，也应该尝试放入一头奶牛。其他小细节参考代码。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;

int n;
char str[N];

bool check(int mid) {
	int k = 0, flag = 0;
	for (int i = 1, la = 0; i <= n; i ++) {
		if (str[i] == '1') {
			if (i - la < mid && flag) k --;
			if (k == 2) return true;
			flag = 0; la = i; continue;
		}
		if (i - la >= mid || i == 1) la = i, k ++, flag = 1;
	}
	return k >= 2;
}

int main() {
	scanf("%d%s", &n, str+1);
	int r = n;
	for (int i = 1, la = 0; i <= n; i ++)
		if (str[i] == '1') {if (la) r = min(r, i-la); la = i;}
	int l = 1, res;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	printf("%d", res);
}
```

后记：我们充分发扬人类智慧，放置的两头奶牛一定要么一头位于最长的区间中间；一头位于次长的区间中间；要么两头都在最长的区间中间；要么存在首/末位为空，可以考虑放在首/末位；要么……尽管这样做是理论 $O(n)$ 的，但巨大多分讨又难想又难调，常数还巨大。实测官解的线性甚至比我的二分还慢……何况二分本来也是正解，何苦为难自己不是。

---

## 作者：Luogu_916767 (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/P9952)

最小值最大，一道典型的二分答案题。

### 题目大意

有 $n$ 个牛栏，牛栏中的某些栏中有奶牛，有些没有。我们要把新来的两头牛加进牛栏里，问加完之后最近的两头奶牛的距离最大可以是多少。

### 思路分析

二分答案。二分最大距离，对于每一个枚举出来的 $mid$，直接遍历所有牛栏，若第 $i$ 头奶牛和第 $i+1$ 头奶牛之间的距离大于 $2\times mid$，则可以插入到第 $i$ 头奶牛和第 $i+1$ 头奶牛之间。

注意，需要特判两头奶牛是否加在同一位置。

### Code

实现就看题解区其它巨佬的就好，他们已经写的很完善了，重在理解。

---

