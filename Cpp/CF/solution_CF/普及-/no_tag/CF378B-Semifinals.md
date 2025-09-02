# Semifinals

## 题目描述

在跑步比赛中，两场半决赛刚刚结束。每场半决赛有 $n$ 名选手参加。一共有 $n$ 名选手能够晋级决赛。晋级规则如下：对于每场半决赛，前 $k$（$0 \le 2 k \le n$）名选手能够直接晋级决赛；对于其余选手，前 $n − 2 k$ 名选手晋级决赛。

现在 $k$ 还没有公布，每名选手都想知道他能否晋级。

## 样例 #1

### 输入

```
4
9840 9920
9860 9980
9930 10020
10040 10090
```

### 输出

```
1110
1100
```

## 样例 #2

### 输入

```
4
9900 9850
9940 9930
10000 10020
10060 10110
```

### 输出

```
1100
1100
```

# 题解

## 作者：Trimsteanima (赞：5)

题意：一共有$n$名选手，前$k$名选手能晋级，剩下的选手中$n - 2k$能晋级。要求出每名选手是否有机会晋级。

纯贪心

按照$k = 0$和$k = n / 2$两个方案选，就可以包含所有晋级的人。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, i, x, y, a[100100], b[100100];
int main() {
	cin >> n;
	for (i = 0; i < n; ++i)
		cin >> a[i] >> b[i], ++(a[x] < b[y] ? x : y);
	for (i = 0; i < n; ++i)
		cout << (i < max(x, n / 2) ? '1' : '0');
	cout << endl;
	for (i = 0; i < n; ++i)
		cout << (i < max(y, n / 2) ? '1' : '0');
	cout << endl;
	return 0;
}
```

---

## 作者：zhaohanwen (赞：1)

### 题目大意

有两场比赛，每场比赛有 $n$ 名选手，前 $k$ 名选手可以晋级，剩下的选手中 $n-2k$ 能晋级。求出每名选手能否晋级。

### 题目分析

先把每两名对应选手的成绩比较，成绩好的晋级。

然后再考虑半决赛的情况，我们可以想出此时晋级的人数为 $n/2$，所以让前 $n/2$ 的人晋级。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N][3],b[N][3];
int main()
{
	int n;
	cin>>n;
	int k=n/2;
	for(int i=1;i<=n;i++) cin>>a[i][1]>>b[i][1];
	int x=1,y=1;
	for(int i=1;i<=n;i++)
	{
		if(a[x][1]>b[y][1]) b[y][2]=1,y++;
		else a[x][2]=1,x++;
	}
	for(int i=1;i<=k;i++)
	{
		a[i][2]=b[i][2]=1;
	}
	for(int i=1;i<=n;i++) cout<<a[i][2];
	cout<<endl;
	for(int i=1;i<=n;i++) cout<<b[i][2];
	cout<<endl;
	return 0;
}
```


---

## 作者：DANIEL_x_ (赞：1)

## 思路分析：
不难发现，$k$ 的最大值为 $\frac{n}{2}$，最小值为 $0$。

所以可以按照 $k=0$，$k=\frac{n}{2}$，进行分类选出，此时可以包含所有晋级的人。

## code：
```cpp

#include<bits/stdc++.h>
using namespace std;
int main(){
	std:: ios_base::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	int n; 
    cin>>n;
	vector<pair<int,int>>v;
	for(int i{};i<n;i++){
    	int x,y; 
        cin>>x>>y;
    	v.emplace_back(make_pair(x,i));
    	v.emplace_back(make_pair(y,i+n));
	}
	sort(v.begin(),v.end());
	int a[2*n]{},k=n/2;
	for(int i{};i<k;i++)
    	a[i]=1; a[i+n]=1;
	for(int i{};i<n;i++)
        a[v[i].second]=1;
	for(int i{};i<2*n;i++){
    	cout<<a[i];
    	if(i==n-1)cout<<'\n';
	}
}
  
```


---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF378B)

先来分析一下题意。

题意：一共有 $n$ 名选手，前 $k$ 名选手能晋级，剩下的选中  $n$−$2k$ 能晋级，然后要求算出每名选手是否有机会晋级。

这道题就是纯贪心，按照 $k=0$ 和 $k=n/2$ 两个方案选，就可以包括所有晋级的人。

直接上代码。

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long n,i,x,y,a[100010],b[100010];//不开long long见祖宗 
int main() 
{
	cin >> n;
	for(long long i=0;i<n;++i)
	{
		cin>>a[i]>>b[i];
		++(a[x]<b[y]?x:y);//三目运算符	
	}
	for(long long i=0;i<n;++i)
	{
		cout<<(i<max(x,n/2)?'1':'0');	
	}
	cout<<endl;
	for(long long i=0;i<n;++i)
	{
		cout<<(i<max(y,n/2)?'1':'0');		
	}
	cout<<endl;
	return 0;//完美结束 
}
```

---

## 作者：York佑佑 (赞：0)

## 题意

两场半决赛刚刚结束。每场半决赛有 $n$ 名选手参加。晋级规则如下：对于每场半决赛，前 $k$ 名选手能够直接晋级决赛；对于所有选手，前 $n-2k$ 名选手晋级决赛。

输出每位选手是否有机会晋级。
## 分析
本题是贪心。

分析两个极端情况。

- 当 $k=\frac n2$ 时，前 $0$ 名（也就是没有）选手能进入半决赛，而每组的前 $\frac n2$ 名选手可以进入半决赛。也就是说，输出字符串的前一半都为 `1`。

- 当 $k=0$ 时，前 $n$ 名选手会进入半决赛，而每组的前 $0$ 名（也就是没有）会进入半决赛。也就是说，所有成绩为前 $n$ 名选手能进入半决赛。至于这段代码怎么写，我们给出一个简单的代码：

```cpp
for (int i = 1; i <= n; i++)
{
	cin >> a[i] >> b[i];
	++(a[x] < b[y] ? x : y);//x:第一组的前x名能进入半决赛，y:第一组的前y名能进入半决赛
	//这里的比较在a[x]和b[y]中取最大值，谁大就将比较对象谁的下一项，完美求出了x和y
}
```

- 当 $k$ 为其他任意数字时，其时判断都包含了上面的判断情况。也就是说，我们只要判断上面两种情况即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100010], b[100010], x, y;
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i] >> b[i];
		++(a[x] < b[y] ? x : y);//上面有解释，求前n/2
	}
	for (int i = 1; i <= n; i++)
		cout << (i <= n / 2 || i <= x);//输出是否在改组前一半或在前n/2
	cout << endl;
	for (int i = 1; i <= n; i++)
		cout << (i <= n / 2 || i <= y);//输出是否在改组前一半或在前n/2
	return 0;
}
```






---

## 作者：PigJokerYellow (赞：0)

## 题意


给出数组 $ a,b $ 每组 $ n $ 人在 $ 0 \le 2k \le n$ 的情况下，前 $ 2k $ 个人直接晋级，然后剩下的人中选前 $ n - 2 k $ 个人晋级。




------------

## 思路：贪心

只需要考虑两种极端情况 $ k = 0 $ 或 $ k = \tfrac{n}{2} $ 就可以遍历出所有情况。



------------


## $ Code $


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e6;
long long n,num;
struct node{
	long long team;
	long long point;
	long long idx;
};
//team表示组别， point表示分数，idx表示位置 
node players[N];
bool is_join[3][N];
//bool is_join 判断第1/2组能否能晋级 
bool cmp(node a,node b){
	return a.point<b.point;
}
//排序的cmp函数，不解释 

int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		num++;
		cin>>players[num].point;
		players[num].team=1;
		players[num].idx=i;
		num++;
		cin>>players[num].point;
		players[num].team=2;
		players[num].idx=i;
		//把所有的选手都存进结构体players中 
	}
	sort(players+1,players+num+1,cmp);
	//把players的point从小到大排序，便于之后判断前几名 
	for(long long i=1;i<=n;i++){
		is_join[players[i].team][players[i].idx]=1;
	}
	//当k=0时 
	for(long long i=1;i<=n/2;i++){
		is_join[1][i]=1;
		is_join[2][i]=1;
	}
	for(long long i=n/2*2+1;i<=n;i++){
		is_join[players[i].team][players[i].idx]=1;
	}
	//当k=n/2时 
	for(long long i=1;i<=n;i++){
		cout<<is_join[1][i];
	}
	cout<<'\n';
	for(long long i=1;i<=n;i++){
		cout<<is_join[2][i];
	}
	return 0;
}
```


---

## 作者：xiaofeng_and_xiaoyu (赞：0)

本题的思维难度可能是黄，但代码简单。

一开始的思路：用栈排序。

但是，似乎无法维护初始数组的样子？

于是我选用了结构体。

很明显，队伍的前 $\frac{n}{2}$ 名都是可以入选的。

然后是第二个条件，相当于排序后的前 $n$ 个。

因为给定了升序排序，所以只需要与对方的前 $n$ 个比。

为了简化复杂度，我们可以知道当第 $i$ 个比时，$1$ 到 $i-1$ 肯定都比完并且可能了，此时只需要跟对方 $t-i$ 号比就可以了。

代码：

```cpp
#include<iostream>
#include<stack>
using namespace std;
stack<int>s;//不知道为什么，加着这个还能变快？
struct node{
	int times;
	bool can;
}a[100005],b[100005];
int main(){
	int t;
	cin>>t;
	int z=t/2;
	for(int i=0;i<t;i++){
		cin>>a[i].times>>b[i].times;
		if(i<z){
			a[i].can=true;
			b[i].can=true;
		}else{
			a[i].can=false;
			b[i].can=false;
			if(a[i].times<b[t-i-1].times){//因为我的数组以0开始，所以就和t-i-1号比
				a[i].can=true;
			}
			if(b[i].times<a[t-i-1].times){
				b[i].can=true;
			}

		}
	}
	for(int i=0;i<t;i++){
		cout<<a[i].can;
	}
	cout<<endl;
	for(int i=0;i<t;i++){
		cout<<b[i].can;
	}
	return 0;
}
```


---

## 作者：zjhzs666 (赞：0)

# 题意
有两场比赛，每场比赛有 $n$ 名选手，前 $k$ 名选手可以晋级，剩下的选手中 $n-2k$ 能晋级。要求出每名选手能否晋级。
# 思路
进行晋级的模拟，每次将两场比赛的选手的成绩相比较，选取其中跑步时间更短的选手并让他晋级，又因为这是半决赛晋级，因此我们应该将 $n/2$ 名选手晋级，最后输出。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[100001][3],b[100001][3],aa=1,bb=1,k;
int main(){
	cin>>n;
	k=n/2;
	for(int i=1;i<=n;i++)cin>>a[i][1]>>b[i][1];
	for(int i=1;i<=n;i++){
		if(a[aa][1]>b[bb][1]){
			b[bb][2]=1;
			bb++;
		}
		else{
			a[aa][2]=1;
			aa++;
		}
	}
	for(int i=1;i<=k;i++)a[i][2]=b[i][2]=1;
	for(int i=1;i<=n;i++)cout<<a[i][2];
	cout<<endl;
	for(int i=1;i<=n;i++)cout<<b[i][2];
}
```


---

## 作者：CCDYJXZ (赞：0)

[题目：CF378B](https://www.luogu.com.cn/problem/CF378B)

题意：

在人数为 $n$ ， $k$ 为 $0 \le 2 k \le n$ 的情况下。第一种晋级方式两组选出每组前 $k$ 名晋级；第二种晋级方式是进行完第一种晋级方式后，再将剩下的人重新排名，选出前 $n - 2 k$ 名晋级。最后再将两组每个人晋级的可能情况输出，可能为 $1$，否则为 $0$。

------------
思路：

我们不难发现**暴力必会超时**，因此我们需要考虑**贪心**。因为 $0 \le 2 k \le n$，所以 $k$ 最大为 $n \div 2$ ，最小为 $0$。

第一种晋级方式 $k$ 越大，可能晋级的人越多。因为当 $k = n \div 2$ 时 $k$ 最大，所以此时从第一种方式选出的人数也就最多。而第二种晋级方式 $k$ 越小，可能晋级的人越多。因为 $k$ 最小为 $0$，所以此时第二种方式选出的人数也就最多。

所以只需列举以上两种情况就能包含两种晋级方式的所有可能晋级的人。

------------
代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int aa[100101],ss[100101];
struct ddd{
	int a,s,d;
}dd[200202];//两个组，合起来后s表示组，d表示组中的位置 
bool ff[2][101001];//每个人是否可以有机会晋级 
bool cmp(ddd a,ddd s){return a.a<s.a;}
int main(){
	int a,s,d=0,f;
	cin>>a;
	s=a/2;
	for(int i=1;i<=a;i++){
		cin>>aa[i]>>ss[i];
		dd[++d].a=aa[i];
		dd[d].s=0;
		dd[d].d=i;
		dd[++d].a=ss[i];
		dd[d].s=1;
		dd[d].d=i;
	}
	sort(dd+1,dd+d+1,cmp);
	//读入两个组，并再将它们合并统一排序 
	for(int i=1;i<=a;i++)//k=0的情况
		ff[dd[i].s][dd[i].d]=1;
	for(int i=1;i<=s;i++)//k=s/2的情况 
		ff[0][i]=ff[1][i]=1; 
	for(int i=s*2+1;i<=a;i++)
		ff[dd[i].s][dd[i].d]=1;
	for(int i=0;i<=1;i++){//最后输出 
		for(int j=1;j<=a;j++)
			cout<<ff[i][j];
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：wdgm4 (赞：0)

说真的，刚开始的时候我没看懂题，~~可能是我不了解半决赛这类的东西~~。

我来解释一下题意：有两组为 $n$ 人的选手，每组前 $k$ 名选手能晋级，剩下的选手中前 $n−2k$ 能晋级（相当于把剩下的选手合为一组再排名）。

------------

看懂题目后，我想到的最简单的方法就是暴力，时间复杂度是 $O(n^2)$，在 $1 \le n \le {10}^5$ 的范围内会超时。

每组前 $k$ 名选手普级循环一遍即可，剩下的选手中前 $n-2k$ 晋级可以用双指针的方法，每名选手是否能晋级存在 $\text{aa}$ 和 $\text{bb}$ 数组里。

## 暴力超时代码

```cpp
#include<bits/stdc++.h>
#define XD 114514

using namespace std;
int n,m;
int a[100010],b[100010];
bool aa[100010],bb[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
	}
	for(int k=0;k<=n/2;k++){
		for(int i=1;i<=k;i++){
			aa[i]=bb[i]=1;
		}
		int x=k+1,y=k+1,nem=n-2*k;
		while(nem>0){
			if(a[x]>b[y]){
				nem--;
				bb[y]=1;
				y++;
			}else{
				nem--;
				aa[x]=1;
				x++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d",aa[i]);
	}
	cout<<endl;
	for(int i=1;i<=n;i++){
		printf("%d",bb[i]);
	}
	return 0;
}


```

------------

在暴力的基础上，我们可以考虑贪心。只需考虑 $k=0$ 和 $k=n/2$ 的情况就可以包括所有的有机会晋级的选手了。

## code

```cpp
#include<bits/stdc++.h>
#define XD 114514

using namespace std;
int n,m;
int a[100010],b[100010];
bool aa[100010],bb[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
	}
	int x=1,y=1,nem=n;//k=0 的情况
	while(nem>0){
		if(a[x]>b[y]){
			nem--;
			bb[y]=1;
			y++;
		}else{
			nem--;
			aa[x]=1;
			x++;
		}
	}
	int k=n/2;//k=n/2 的情况
	for(int i=1;i<=k;i++){
		aa[i]=bb[i]=1;
	}
	for(int i=1;i<=n;i++){
		printf("%d",aa[i]);
	}
	cout<<endl;
	for(int i=1;i<=n;i++){
		printf("%d",bb[i]);
	}
	return 0;
}


```


---

