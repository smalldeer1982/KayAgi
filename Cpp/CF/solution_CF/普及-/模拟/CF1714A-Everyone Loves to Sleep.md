# Everyone Loves to Sleep

## 题目描述

Vlad和其他人一样，非常喜欢睡觉。

Vlad每天都要做 $n$ 件事，每件事在特定时间。对于这些事情中的每一件，他都定了一个闹钟，其中第 $i$ 个在 $h_i$ 时 $m_i$ 分被触发（$0\le h_i<24,0\le m_i<60）$。

Vlad使用24小时时间格式，所以12:59之后是13:00,23:59后是00:00。

Vlad在H时M分睡觉（$0 \le H < 24， 0 \le M < 60$）。

他要你回答：在下一个闹钟响之前，他能睡多久。

如果在他上床睡觉的时候有任何闹钟响起，那么他将睡0小时0分钟。

## 样例 #1

### 输入

```
3
1 6 13
8 0
3 6 0
12 30
14 45
6 0
2 23 35
20 15
10 30```

### 输出

```
1 47
0 0
10 55```

# 题解

## 作者：Jasper08 (赞：5)

本题是一道数学题。对于输入的每一个时间点 $h_i,m_i$，我们计算出 Vlad 的上床之后要多久才能第一次到时间 $h_i:m_i$，并取最小值即可。

设 Vlad 上床的时间为 $H:M$，分类讨论：

1. $h_i\ge H$ 且 $m_i\ge M$：这一类是最简单的。$h_{sleep}=h_i-H,m_{sleep}=m_i-M$。

2. $h_i>H$ 且 $m_i<M$：由于 $m_i<M$，说明第 $h_i-H$ 个小时还没有过完。此时 $h_{sleep}=h_i-H-1,m_{sleep}=m_i+60-M$。

3. $h_i=H$ 且 $m_i<M$：举个例子，从 $12:50$ 到 $12:25$ 需要多久呢？显然是 $23$ 时 $35$ 分。所以 $h_{sleep}=23,m_{sleep}=m_i+60-M$。

类比第 1 种情况和第 2 种情况，显然有：

4. $h_i<H$ 且 $m_i\ge M$：$h_{sleep}=h_i+24-H,m_{sleep}=m_i-M$。

5. $h_i<H$ 且 $m_i<M$：$h_{sleep}=h_i+24-H-1,m_{sleep}=m_i+60-M$。

代码实现中有一些小的细节需要注意：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

int t;

int main() {
	scanf("%d", &t);
	while (t -- ) {
		int n, h, m;
		scanf("%d%d%d", &n, &h, &m);
		int ansh = 24, ansm = 60;
		while (n -- ) {
			int alarmh, alarmm;
			scanf("%d%d", &alarmh, &alarmm);
			int sleeph = (24+alarmh-h) % 24; //计算小时数
			if (alarmm < m) sleeph = (sleeph > 0) ? sleeph-1 : 24-sleeph-1; //注意要特判sleeph是否大于0,不然会出现答案为-1的情况
			int sleepm = (60+alarmm-m) % 60; //计算分钟数
			if (sleeph*60+sleepm < ansh*60+ansm) ansh = sleeph, ansm = sleepm; //如果Vlad睡觉的时间更短,则将答案更新
		}
		printf("%d %d\n", ansh, ansm);
	}
	return 0;
}
```

---

## 作者：taozhiming (赞：5)

## CF1714A Everyone Loves to Sleep

## 题目描述 
[原题面](https://www.luogu.com.cn/problem/CF1714A)




## 题目分析：

我们可以把小时乘 $60$ 加上分钟，然后排序，找最小的一个，也就是然后减去给定的睡觉时间，但是结论不全对


举个棒子，我们 $8$ 点睡觉，第一个闹钟是 $6$ 点的，这样直接排序相减不就成负数了？

另外我们还要从小到大排序，那就可以很轻松的想到，**如果闹钟的小时数小于我睡觉的时间，那就用后面的小时数加上 $24$ 再减不就可以了**？

## 代码详解：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e4+5;
struct node{
	int h,fen; //这里的h是小时，fen就是分（中文多好理解）
}tim[MAXN];
bool cmp(node a,node b)
{
	if (a.h==b.h) return a.fen<b.fen; //用来排序
	return a.h<b.h;
}
int t,n,H,M;
signed main()
{
	cin>>t;
	while(t--)
	{
		int sum1,sum2;
		cin>>n>>H>>M;
		for (int i=1;i<=n;i++)
		{
			cin>>tim[i].h>>tim[i].fen;
			if (tim[i].h<H||tim[i].h==H&&tim[i].fen<M) tim[i].h+=24;			
            	//这里就是判断，如果闹钟比睡觉的时间还早，那就把小时数+24
		}
		sort(tim+1,tim+n+1,cmp); //从小到大排个序
		sum1=H*60+M;
		sum2=tim[1].h*60+tim[1].fen;
		if (sum1==sum2){
			cout<<"0 0"<<endl; //如果闹钟和睡觉的时间一致，那就不用睡觉了
			continue;
		}
		sum2-=sum1;
		if (sum2%60==0){
			cout<<sum2/60<<" 0"<<endl;
			continue; 
		}
		else{
			cout<<sum2/60<<" "<<sum2%60<<endl;
		}
	}
	return 0;
} 
```


最后吐槽（dalao跳过环节）：

~~蒻鸡在考场上打了16分钟，题面太臭了（要不是我看样例）~~

我的一个朋友一分钟一分钟跳的，我真的气死，~~想给他 $hack$ 掉，但是t只有10！！请求加强数据~~


---

## 作者：FFTotoro (赞：2)

本题考察入门的选择结构与循环结构。

很显然，我们需要找出离 Vlad 睡觉时响得最早的那个闹钟。

这是我们就需要分类讨论：

设 $H,M$ 是他上床睡觉的时间， $h_i,m_i$ 是第 $i$ 个闹钟响的时间，那么：

如果 $H=h_i$，那么就比较 $M$ 和 $m_i$，如果 $M\le m_i$，那么他就可以睡 $23:(M-m_i)$；否则他可以睡 $0:60-(M-m_i)$；

如果 $H<h_i$，那么类似的，如果 $M\le m_i$，那么他就可以睡 $(H-h_i):(M-m_i)$；否则他可以睡 $(H-h_i-1):60-(M-m_i)$；

如果 $H>h_i$，就是说他到第二天才能醒，那么如果 $M\le m_i$，那么他就可以睡 $24-(H-h_i):(M-m_i)$；否则他可以睡 $24-(H-h_i)-1:60-(M-m_i)$；

最后将所有的时间插入小根堆，取出堆顶就是答案。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> d(int h1,int m1,int h2,int m2){
    if(h1==h2)return make_pair(m1<m2?23:0,m1>m2?m1-m2:(60+m1-m2)%60);
    if(h1>h2)return make_pair(h1-h2-(m1<m2),m1>m2?m1-m2:(60+m1-m2)%60);
    return make_pair(24+h1-h2-(m1<m2),m1>m2?m1-m2:(60+m1-m2)%60);
}
int main(){
    ios::sync_with_stdio(false);
    int t; cin>>t;
    while(t--){
        int n,h0,m0; cin>>n>>h0>>m0;
        vector<pair<int,int> > a(n);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
        for(auto &[h,m]:a)cin>>h>>m,q.push(d(h,m,h0,m0));
        cout<<q.top().first<<' '<<q.top().second<<endl;
    }
    return 0;
}
```

---

## 作者：BlackPanda (赞：2)

**[题目传送门](https://www.luogu.com.cn/problem/CF1714A)**

------------
### 题意：
Vlad 有 $n$ 个闹钟，第 $i$ 个闹钟会在 $h_i$ 时 $m_i$ 分响起，Vlad 在 $H$ 时 $M$ 分开始睡觉，求出他最多可以睡多长时间。在这道题目中，所有时间均为二十四小时制。

特殊的，如果有任何闹钟在 Vlad 入睡时响起，输出 $\verb!0 0!$。

------------
### 思路：
建议评橙，稍有思维难度的模拟题。

- 这道题可以先求出大于入睡时间的最小时间的闹钟，然后求出**从入睡时间到找到的最小的闹钟**所跨的时间。

- 为了方便计算，可以把时间全部转化成以分钟为单位：$h \times 60 + m$，这里将入睡时间转化：$t1 = H \times 60 + M$。

- 对于每次输入的闹钟时间，可以先把时间单位全部转化成分钟：$t2 = h_i \times 60 + m_i$，然后让 $t2$ 和 $t1$ 做差，如果结果小于 $0$，说明 $t2$ 和 $t1$ 不在同一天，我们可以让 $t2+24 \times 60$，也就是加上一天的时间，再来做差即可。

- 在每次循环末尾，只需要将计算好的数值每次取最小值即可（同理，也可以在找到满足条件的第一个闹钟时，就结束循环）。

---

## 作者：Dregen_Yor (赞：2)

# 题目大意
 - 小 V 在每天的 $H$ 时 $M$ 分睡觉。
 - 小 V 每天订了 $n$ 个闹钟，第 $i$ 个闹钟在 $h_i$ 时 $m_i$ 分响起。
 - 闹钟响之后小 V 就醒了。
 - 如果任何闹钟在小 V 睡觉的时候响起，答案将是 $0$ $0$。
 
#  解法

枚举每个闹钟响起的时间，如果 $h_i<H$，说明闹钟在睡觉后的第二天才响。对此，如果 $h_i<H$，$h_i+24$。

如果 $m_i<M$，可以令 $h_i -1$，$m_i+60$ 之后再统计答案。

**注意，对于 $h_i=H$ 的情况要特殊处理。**

统计答案时，对于第 $i$ 个闹钟，小 V 一共能睡 $h_i-H$ 小时，$m_i-M$ 分钟。

总共 $(h_i-H)\times60+m_i-M$ 分钟，我们记录下最小的 $(h_i-H)\times60+m_i-M$ 对应的 $h_i-H$ 和 $m_i-M$，记录值即为答案。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, h, m, ansh, ansm, minx;

int main() {
	scanf("%d", &t);

	while (t--) {
		scanf("%d%d%d", &n, &h, &m);
		ansh = minx = ansm = 0x7fffffff;

		for (int i = 1; i <= n; i++) {

			int h1, m1;
			scanf("%d%d", &h1, &m1);

			if (h1 > h) {
				if (m1 < m) {
					h1--;
					m1 += 60;
				}

				int sum = (h1 - h) * 60 + m1 - m;

				if (sum < minx) {
					minx = sum;
					ansm = m1 - m;
					ansh = h1 - h;
				}
			} else if (h1 == h) {
				int sum;

				if (m1 < m) {
					sum = 24 * 60 - m + m1;

					if (sum < minx) {
						minx = sum;
						ansm = 60 - m + m1;
						ansh = 23;
					}
				} else {
					sum = m1 - m;

					if (sum < minx) {
						minx = sum;
						ansm = m1 - m;
						ansh = 0;
					}
				}
			} else {
				h1 += 24;

				if (m1 < m) {
					h1--;
					m1 += 60;
				}

				int sum = (h1 - h) * 60 + m1 - m;

				if (sum < minx) {
					minx = sum;
					ansm = m1 - m;
					ansh = h1 - h;
				}
			}
		}

		if (ansm == 60) {
			ansm = 0;
			ansh++;
		}

		printf("%d %d\n", ansh, ansm);
	}

	return 0;
}

```


---

## 作者：Jeremiahy (赞：2)

## 题意

Vald 在 $H$ 时 $M$ 分时入睡，有 $n$ 个闹钟，第 $i$ 个闹钟在 $h_i$ 时 $m_i$ 分响起。采用二十四小时制。问 Vald 能睡多长时间（可能为 $0$）？

# 分析

按照题意直接模拟即可。找出比入睡时间大的闹钟里最小的一个，如果没有，说明跨天了，就找所有闹钟里时间最早的一个，注意一些边界问题就可以。

在计算时，如果未跨天，则用找到的闹钟小时减去小时，分钟减去分钟。如果此闹钟分钟小于入睡时间的分钟，就把小时减 $1$，分钟加 $60$。如果跨天，则用 $24$ 减去 $H$ 再加上 $h_i$，分钟直接相减即可。如果 $m_i$ 小于 $M$ 同样按上述方法处理。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, H, M, h[12], m[12];
signed main () {
	cin >> t;
	while (t--) {
		int maxnh = -1, maxnm = -1, minnh = 1000, minnm = 1111;
		cin >> n >> H >> M;
		for (register int i = 1; i <= n; i++) {
			cin >> h[i] >> m[i];
			if (h[i] > H || (h[i] == H && m[i] >= M))//找一个符合要求的
				maxnh = h[i], maxnm = m[i];	
			if (h[i] < minnh || (h[i] == minnh && m[i] < minnm))//找最小的
				minnh = h[i], minnm = m[i];
		}
		if (maxnh == -1) {//跨天
			if (minnm < M)// m[i] < M
				cout << 24 - H + minnh - 1 << ' ' << minnm - M + 60 << '\n';
			else	
				cout << 24 - H + minnh << ' ' << minnm - M << '\n';
			continue;
		}
		int ch = maxnh - H, cm = maxnm - M;
		for (register int i = 1; i <= n; i++)
			if (h[i] > H || (h[i] == H && m[i] >= M))//找离 H,M 最近的
				if (h[i] - H < ch || (h[i] - H == ch && m[i] - M < cm))
					ch = h[i] - H, cm = m[i] - M;
		if (cm < 0)//同上
			ch--, cm += 60;
		cout << ch << ' ' << cm << '\n';
	}
	return 0;
}
```


---

## 作者：tian_jun_cheng (赞：1)

## 题意

给你一个基础时间，然后给你 $ n $ 个时间，请你计算基础时间和 $ n $ 个时间中离它最近的时间的差是多少。

## 思路

因为输入的时间没有顺序，所以我们对每一个时间都进行计算，然后取最小值。

计算时间就是一个减法的模拟。

如果分钟相减是正数，就记录下来。

```cpp
minute=k-m;
```

如果不够减，就借位，并 $ + 6 0 $ 计算。

```cpp
if(m>k)
    k+=60,j--;
```
然后是小时的计算。如果够减，就记录。

```cpp
hour=j-h;
```
如果不够减，就$ + 2 4 $ ，再计算，相当于过了一天。

```cpp
if(h>j)
    j+=24;
```
最后统计答案，求最小值。

```cpp
minn=min(minn,minute+hour*60);
```
注意，要把基础时间还原，否则影响后面的计算。

```cpp
h=H,m=M;
```
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,h,m;
		cin>>n>>h>>m;
		int H=h,M=m;
		int minn=2147483647;
		for(int i=1;i<=n;i++)
		{
			int j,k;
			cin>>j>>k;
			int hour=0,minute=0;
			if(m>k)
				k+=60,j--;
			minute=k-m;
			if(h>j)
				j+=24;
			hour=j-h;
			minn=min(minn,minute+hour*60);
			h=H,m=M;
		}
		cout<<minn/60<<" "<<minn-minn/60*60<<endl;
	} 
	return 0;
}
```


---

## 作者：linyihdfj (赞：1)

## A.Everyone Loves to Sleep
### 题目描述：
[原题面](https://codeforc.es/contest/1714/problem/A)

### 题目分析：

考虑闹钟的数量很少，所以直接暴力计算出睡到每一个闹钟响的时间，然后取最小值就好了。

### 代码详解：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int h,m;
	node(){}
	node(int _h,int _m){
		h = _h,m = _m;
	}
};
bool operator < (node l,node r){
	if(l.h != r.h)	return l.h < r.h;
	return l.m < r.m;
}
bool operator == (node l,node r){
	return l.h == r.h && l.m == r.m;
}
node operator - (node l,node r){
	node tmp;
	tmp.h = l.h - r.h;
	if(l.m < r.m)
		l.m += 60,tmp.h--;
	tmp.m = l.m - r.m;
	return tmp;
}
node operator + (node l,node r){
	node tmp;
	tmp.h = l.h + r.h;
	tmp.m = l.m + r.m;
	tmp.h += tmp.m / 60;
	tmp.m %= 60;
	return tmp;
} 
int main(){
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int t;
	cin>>t;
	while(t--){
		int n;
		node a;
		cin>>n;
		cin>>a.h>>a.m;
		node ans = node(100,100);
		for(int i=1; i<=n; i++){
			node tmp;
			cin>>tmp.h>>tmp.m;
			node h = node(24,0);
			if(a < tmp)	
				ans = min(ans,tmp - a);
			else if(tmp < a)
				ans = min(ans,(h - a) + tmp);
			else
				ans = node(0,0);
		}
		printf("%d %d\n",ans.h,ans.m);
	}
	return 0;
}
```

这里就是封装了一个结构体。

---

## 作者：张语诚ZYC (赞：1)

## 题目翻译

~~Vald 和其他人一样喜欢睡觉~~ （这句没用）

他会在 $H$ 时 $M$ 分睡觉（使用 24 小时制），但是有多个闹钟影响他睡觉，会给定每一个响铃时间，注意有 $t$ 组数据，并且若入睡时间与闹铃时间相同，则睡眠时间要输出零。注意闹钟可以跨天。

## 思路分析

观察此题的数据范围可知，暴力能过。

提供一个简单地思路：

1. 将小时数乘 $60$，加上分钟数，得到一天开始的分钟时间，存入数组。
2. 排序一下，对于仅学过冒泡的萌新，可以看一看下面的题外话。
3. 找出大于 Vald 入睡时间，且最接近入睡时间的闹钟，就是在他睡觉后的第一个闹钟响铃时间
4. 若找不到，则说明跨天了，输出最低的时间即可。

## 题外话

新入学的萌新大概都学过冒泡，时间复杂度为 $O(n^2)$。
建议学习试用一下平均时间复杂度为 $O(n \log n)$ 的快速排序，或者直接使用标准模板库中的 `sort` 。

$$\color{pink}{\texttt{The End by Yucheng}}$$

---

## 作者：__KrNalty__ (赞：0)

### 题意简述：

Vlad 在 $H$ 时 $M$ 分时入睡，共有 $n$ 个闹钟，第 $i$ 个闹钟在 $h_i$ 时 $m_i$ 分响起。采用二十四小时制。问 Vlad 能睡多长时间（可能为 $0$）？

### 思路分析：

场上魔怔了想到结构体排序，其实直接对每一个闹钟求出能睡多长时间，取最小值即可。但是要注意一个细节，如果 Vlad 在 $24$ 点前入睡，最早的闹钟在第二天响起，那么就得特殊判断。

### 完整代码供参考：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 5;
int n, H, M;
signed main() {
	int T = 1;
	cin >> T;
	while (T--) {
		cin >> n >> H >> M;
		int ans = 1e18, m = H * 60 + M; // 转化成分钟数方便计算
		for (int i = 1; i <= n; i++) {
			int hh, mm;
			cin >> hh >> mm;
			int nowm = hh * 60 + mm; // 转化成分钟数方便计算
			if (nowm < m) ans = min(ans, nowm + 1440 - m); // 如果闹钟在第二天那么就需要先加上一天的分钟数也就是 24 * 60 = 1440
			else ans = min(ans, nowm - m);
		}
		cout << ans / 60 << " " << ans % 60 << endl;
	}
	return 0;
}
```

---

## 作者：Think (赞：0)

## 思路
能睡多久，我们只要知道离入睡时间最近一次的闹钟什么时候响起即可。  
注意到样例第三个输出是跨天的，所以我们要对是否跨天进行处理。
## 解法
用结构体记下小时和分钟，对所有闹钟的时间进行一个排序。  
接下来寻找一天中有没有在睡着之后响起的闹钟，如果没有，闹钟肯定在明天响起，只需要将闹钟的小时加上 $24$ 即可。  
接下来只要进行时间的计算。  
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e2 + 15;
int t, H, M, n;
struct Time{
	int h;
	int m;
}alarm[N];
int cmp(Time a, Time b){
	if(a.h == b.h) return a.m < b.m;
	return a.h < b.h;
}
bool out;
int main(){
	scanf("%d", &t);
	while(t --){
		memset(alarm, 0, sizeof(alarm));
		out = true;
		scanf("%d %d %d", &n, &H, &M);
		for(int i = 1; i <= n; i ++) scanf("%d %d", &alarm[i].h, &alarm[i].m);
		sort(alarm + 1, alarm + 1 + n, cmp);//将闹钟时间进行排序 
		for(int i = 1; i <= n ; i ++) //寻找今天在睡着后有没有闹钟响起 
			if(alarm[i].h > H ||(alarm[i].h == H && alarm[i].m >= M)) out = false;
		if(out == true) for(int i = 1; i <= n; i ++) alarm[i].h += 24;
		for(int i = 1; i <= n; i ++){//时间差的计算 
			if(alarm[i].h < H) continue;
			if(alarm[i].h == H && alarm[i].m < M) continue;
			if(alarm[i].h == H && alarm[i].m >= M){
				printf("0 %d\n", alarm[i].m - M);
				break;//找到了最近响起的闹钟，退出 
			}
			if(alarm[i].m < M){
				alarm[i].h --, alarm[i].m += 60;
			}
			printf("%d %d\n", alarm[i].h - H , alarm[i].m - M);
			break;
		}
	}
	return 0;
}
```

---

## 作者：Qerucy (赞：0)

题意：给定睡觉的时间和每个闹钟响起的时间，求在闹钟响起之前能睡多少时间，可以是 $0$。

这是一道模拟题，但是这道题的模拟的方法有很多种，我来讲讲我的方法。

先把每个闹钟响的时刻转化为分钟的格式，即每天的第多少分钟响起，然后与睡觉的时刻作比较，看看睡觉的时刻是否比闹钟响起的时刻晚，如果是，就说明跨日了，我们只需要给这个闹钟响起的时刻加上一天的时间即可。然后再与睡觉的时刻相减得出睡觉时与每个闹钟的相差的时间，记录下来。

最后再从记录的时间里找出最小的，便是答案，再把得出来的答案转换为几时几分的格式输出即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
int t,n,m,h;
int b[2100];
int h1,m1;
 
int main(){
    scanf("%d",&t);
    while(t--){
        bool fg=0;
        scanf("%d%d%d",&n,&h,&m);
        
        int now=60*h+m;//把睡觉的时间转换为分钟的格式，更方便相减。
        
        for(int i=1;i<=n;i++){
            scanf("%d%d",&h1,&m1);
            
            b[i]=60*h1+m1;//转换。
            
            if(b[i]-now<0) b[i]+=24*60;//如果跨日了，就加上一天的时间。

        }

        sort(b+1,b+1+n);//简单粗暴的方法找最小值。
        
        int nowm=(b[1]-now)%60;//转换回来。
        int nowh=(b[1]-now)/60;
        
        printf("%d %d\n",nowh,nowm);
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

#### 题意

Vlad 在 $H$ 时 $M$ 分时睡觉，有 $n$ 个闹钟，求他最多能睡到什么时候。（用二十四小时计时法）


------------

我在比赛时是将读到的数据排序，然后求出最小值，和睡觉时间进行比较。但这里有两种情况,有可能最早的闹钟和睡觉的时间在同一天，也有可能在下一天。在下一天的情况直接将闹钟时间加一天时间即可。

但其实不用数组，直接在循环内判断最小值就可以，时空复杂度都会降低。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 114514
#define M 1919810
#define ll long long
ll t,n,h,m,x,y;
ll time_,tt,minn;
int main(){
	cin>>t;
	while(t--){
		minn=114514; //记得初始化最小值
		cin>>n>>h>>m;
		time_=h*60+m; //加起来更好计算
		for(int i=1;i<=n;++i){
			cin>>x>>y;
			tt=x*60+y;
			if(tt<time_) minn=min(minn,tt+24*60); //时间比它小即第二天的时间，加一天的时间
			else minn=min(minn,tt);
		}
		minn-=time_;  //记住是求差
		cout<<minn/60<<" "<<minn%60<<'\n'; 
	}
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1Qg41117Qb)

### 2 思路

我们考虑一下如何计算两个时间点之间的距离。

首先，我们将每个时间点都转化为多少分钟的形式，具体为 $n\times60+m$。

然后，闹钟的时间减去入睡的时间。

因为可能跨天，所以可能为负数，遇到这种情况，加上 $1440$ 分钟即可。

输出答案即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 10
#define inf 0x3f3f3f3f
int t;
int n;
int h;
int m;
int ans;
int askans(int x1,int y1,int x2,int y2){
	return (x2*60+y2-x1*60-y1+1440)%1440;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1714A_1.in","r",stdin);
	freopen("CF1714A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&h,&m);
		ans=inf;
		for(int i=1,x,y;i<=n;++i){
			scanf("%d%d",&x,&y);
			ans=min(ans,askans(h,m,x,y));
		}
		printf("%d %d\n",ans/60,ans%60);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82203918)

By **dengziyue**

---

## 作者：zhicheng (赞：0)

### 思路

看到 $n \leq 10$，那么我们就可以直接模拟：从睡觉开始时间往后枚举每一分钟，看一下是否与某个时间点相同即可。最后输出模拟时经过的时间即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[15],w[15];
int main(){
	int n,a,b,c,sum1,sum;
	scanf("%d",&n);
	while(n--){
		sum1=sum=0;
		scanf("%d%d%d",&a,&b,&c);
		for(int i=1;i<=a;i++){
			scanf("%d%d",&q[i],&w[i]);
		}
		while(1){
			for(int i=1;i<=a;i++){
				if(b==q[i]&&c==w[i]){  //找到最早的时间点，结束
					goto s;
				}
			}
			c++;  //分加一
			if(c==60){  //进位到小时
				c=0;
				b++;
			}
			if(b==24){  //第二天
				b=0;
			}
			sum++;
			if(sum==60){  //同上，记录过去的时间
				sum1++;
				sum=0;
			}
		}
		s:;
		printf("%d %d\n",sum1,sum);
	}
}
```
因为我们最多枚举 $1$ 天，所以稍加计算即可得知复杂度其实是可以过的。

---

## 作者：sandwave114514 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1714A)

题目大意

有一个人，他很喜欢睡觉，现在给你他的睡觉时间和他的闹钟时间，让你输出他的睡觉的时间，如果他的睡觉时间等于闹钟时间，输出 `0 0` ，注意有多组数据。

解题思路

由于有多组数据，我们要清零，由于一天有 `1440` 分钟，有可能他会睡到第二天，所以我们要加 `1440` ，并且打标记。

代码如下
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
long long t,n,h,m,a,b,ans,now;
bool p[3010];
int main(){
	t=read();
	while(t--){//多组数据 
		n=read();h=read();m=read();
		now=h*60+m;
		for(int i=0;i<=10000;i++)p[i]=false;
		for(int i=1;i<=n;i++){
			h=read();m=read();
			p[h*60+m]=true;
			p[h*60+m+1440]=true;
		}
		ans=0;
		while(1){
			if(p[now])break;
			now++;
			ans++;
		}
		cout<<ans/60<<" "<<ans%60<<endl;
	}
	return 0;//完结撒花 
}
```




---

## 作者：李宇涵 (赞：0)

## 题解：把时间转化成分钟数
这道题让我们做 $24$ 小时制的时间的比较和运算，由于时间是 $60$ 进制和 $24$ 进制的混合进制，比较麻烦，所以我们将时间转换为**距 $0$ 点的分钟数**

假设现在是 $H$ 时 $M$ 分，那么现在距离 $0$ 点的时间就是 $H$ 个小时 $+M$ 分钟，而 $1$ 小时 $=60$ 分钟，所以现在距 $0$ 点的分钟数就是 $60H+M$。

因此，我们可以把题目中的入睡时间和闹钟时间都转换成距 $0$ 点的分钟数，时间最大为 $23\times60+59=1439$，即取值范围为 $[0,1440)$。

现在开始处理闹钟时间到入睡时间的距离，分两种情况：

如果闹钟时间 $\ge$ 入睡时间：说明在闹钟时间和入睡时间在同一天内。因此，时间差 $d=$ 闹钟时间 $-$ 入睡时间

如果闹钟时间 $<$ 入睡时间：说明在闹钟时间在入睡时间的第二天。而第二天的某一时刻距离第一天的同一时刻 $1440$ 分钟，因此要把在第二天的闹钟时间 $+1440$，时间差 $d=$ 闹钟时间 $+1440-$ 入睡时间。

因此，只需算出闹钟时间 $-$ 入睡时间的值 $d_0$，如果 $d_0<0$，就记 $d$ 为 $d_0+1440$，否则记 $d$ 为 $d_0$，即得闹钟时间距离入睡时间的真实值。写成代码的形式，就是
```cpp
d=(t-m+1440)%1440;
```
这里的 $t$ 是闹钟时间，$m$ 是入睡时间。把闹钟时间先加上 $1440$，如果 $t\ge m$，则 $t-m+1440\ge1440$，对 $1440$ 取模会把加上的 $1440$ 消去，剩下 $t-m$。如果 $t<m$，则 $t-m+1440<1440$，对 $1440$ 取模会留下 $t-m+1440$ 的值，实现了分类的效果。

最后再把 $d$ 取最小值即可，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int T,n,m,h1,m1,ans;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        ans=inf;
        scanf("%d%d%d",&n,&h1,&m1);
        m=h1*60+m1;
        for(int i=1;i<=n;i++)
        {
            int th,tm,t,d;
            scanf("%d%d",&th,&tm);
            t=th*60+tm;
            d=(t-m+1440)%1440;
            ans=min(ans,d);
        }
        printf("%d %d\n",ans/60,ans%60);
    }
    return 0;
}
```

---

## 作者：cachejtt (赞：0)

## 题意
小 V有一个睡觉时刻，和 $n$ 个闹铃，当第一个闹铃响起时，他就醒了，问你他能睡多久。用二十四时表示法。

## 思路
每次存下分钟数，取最小值即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
using namespace std;
const int mnt=0x3f3f3f3f;
int t,n,h,m;
int sum1,sum2,minsum;
int hh,mm;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>h>>m;
    sum1=h*60+m;
    minsum=mnt;
    rep(i,1,n){
      cin>>hh>>mm;
      sum2=hh*60+mm;
      if(sum2>=sum1){
        minsum=min(minsum,sum2-sum1);
      }
      else minsum=min(minsum,sum2+24*60-sum1);
    }
    cout<<minsum/60<<" "<<minsum-60*(minsum/60)<<endl;
  }
  return 0;
}
```

---

## 作者：Scorilon (赞：0)

题意：给定一个时间和 $n$ 个闹钟，问可以睡几个小时几分钟。

做法：直接枚举，计算每一次可以睡得时间，取最小值。计算的时候分情况计算，当小时数小于闹钟小时数时，为 $24-h+a$；当分钟数小于闹钟分钟数时，为 $60-h+a$，小时数也要相应减一（因为借位）；其余情况直接相减即可。在最后要进位，同时判断小时数是否小于 $0$，若小于 $0$，则要加上 $24$，因为在借位减一的时候可能会出现负数。

注意：

- 时间为 $24$ 小时制。

- 当数不够减时要借位。

- 当时间小于睡觉时间时，应把它当做下一天的计算。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int t,n,h,m,a,b;

int main() {
	scanf("%d",&t);
	while(t--) {
		int ans1=1000,ans2=1000;
		scanf("%d%d%d",&n,&h,&m);
		for(int i=1;i<=n;i++) {
			scanf("%d%d",&a,&b);
			int cnt1=0,cnt2=0;
			if(a<h) {
				cnt1=24-h+a;
				if(b<m) cnt2=60-m+b,cnt1--;
				else cnt2=b-m;
			}
			else {
				cnt1=a-h;
				if(b<m) cnt2=60-m+b,cnt1--;
				else cnt2=b-m;
			}
			cnt1+=cnt2/60;//进位
			cnt2%=60;
			if(cnt1<0) cnt1+=24;//判断
			if(cnt1<ans1) ans1=cnt1,ans2=cnt2;//取更小值
			else if(cnt1==ans1&&cnt2<ans2) ans1=cnt1,ans2=cnt2;
		}
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
```


---

## 作者：YCSluogu (赞：0)

## CF1714A 题解

### 题目翻译

Vlad 喜欢睡觉，他决定在 $H$ 小时 $M$ 分钟时入睡，同时有 $n$ 个闹钟，对于第 $i$ 个闹钟会在 $h_{i}$ 小时 $m_{i}$ 分钟时响起。求他被闹钟吵醒之前能睡多久。

### 思路

首先要将每一个时间抽成分钟的形式，这样更方便我们对各个时间段进行考虑。

然后考虑 Vlad 最近一个响起闹钟的时候。不过这样要分类讨论：Vlad 下一个闹钟在今天还是在明天。

如果 Vlad 的闹钟在今天就会响起，那么只需要找的最近那个闹钟并减去时间差即可。

如果 Vlad 的闹钟在明天响起，我们可以划分为两个时间段考虑：Vlad 今天睡的时间和 Vlad 明天睡的时间。今天睡的时间显然是午夜十二点与当前时间的时间差，第二天时间为闹钟响起之时。

代码:

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e6;

int t, n, H, M, T;
int a[kMaxN];

void solve() {
  cin >> n >> H >> M;
  T = H * 60 + M;
  for (int i = 1; i <= n; i++) {
    int h, m;
    cin >> h >> m;
    a[i] = h * 60 + m;
  }
  sort(a + 1, a + 1 + n);
  // 如果下一个闹钟在明天
  if (T > a[n]) {
    T = 60 * 24 - T + a[1];
    cout << T / 60 << " " << T % 60 << endl;
    return;
  }
  for (int i = 1; i <= n; i++) {
    // 如果入睡时间刚好在两个闹钟之间
    if (a[i - 1] < T && T <= a[i]) {
      T = a[i] - T;
      cout << T / 60 << " " << T % 60 << endl;
      return;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) { solve(); }
  return (0 - 0);
}
```

### 思路2

这里提供一下我的考场思路。由于一天只有 $24$ 小时，所以一天只有 $24 \times 60 = 1440$ 分钟。这么完全可以利用更暴力的思路：不断将当前时间 +1 直到遇到一个闹钟响起。

这样的好处是无需考虑太多，只需要在当前时间等于 $1440$ 时重置为 $0$

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e6;

int  h[kMaxN];
int  m[kMaxN];
int  T[kMaxN];
bool ues[kMaxN];

void solve() {
  memset(ues, false, sizeof(ues));
  int n, H, M;
  cin >> n >> H >> M;
  int t = H * 60 + M;
  for (int i = 1; i <= n; i++) {
    cin >> h[i] >> m[i];
    T[i]      = h[i] * 60 + m[i];
    ues[T[i]] = true;
  }
  int ans = 0;
  while (!ues[t]) {
    t++;
    ans++;
    if (t == 60 * 24) { t = 0; }
  }
  cout << (ans / 60) << " " << ans % 60 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--) { solve(); }
  return (0 - 0);
}
```


---

## 作者：TheCliffSwallow (赞：0)

### 题意简述
$\texttt{Vlad}$ 要在 $H$ 时 $M$ 分开始睡觉，他定了 $n$ 个闹钟，求他能睡多长时间。
### 思路
简单排个序就行，如果有一个闹钟的时间比他开始睡觉的时间大，减去他开始睡觉的时间，如果都比他开始睡觉的时间小，就是第二天的闹钟，再特判就好了。
### AC Code
```cpp
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
#include<string>
#include<cctype>
#define ll long long
#define ull unsigned long long
using namespace std;
int t,n,H,M,Minu,ans;
bool flag;
struct clock{
	int h;
	int m;
	int minu;
}c[114514];//用结构体思路不会乱
int minutes(int h,int m){
	return 60*h+m;//将小时：分钟形式转为分钟
}
bool cmp(clock a,clock b){
	return a.minu<b.minu;//判断时间大小
}
int main(){
	ios::sync_with_stdio(false);
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n>>H>>M;
		Minu=minutes(H,M);
		for(int i=1;i<=n;i++){
			cin>>c[i].h>>c[i].m;
			c[i].minu=minutes(c[i].h,c[i].m);
		}
		sort(c+1,c+n+1,cmp);
		for(int i=1;i<=n;i++){
			if(c[i].minu>=Minu){//判断时间大小
				ans=c[i].minu-Minu;
				cout<<ans/60<<' '<<ans%60<<endl;
				flag=true;
				break;
			}
		}
		if(!flag){//特判第二天
			ans=1440-Minu+c[1].minu;
			cout<<ans/60<<' '<<ans%60<<endl;
		}
		flag=false;
	}
  	return 0;
}
```


---

