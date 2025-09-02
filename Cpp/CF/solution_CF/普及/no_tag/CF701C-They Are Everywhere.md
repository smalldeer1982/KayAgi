# They Are Everywhere

## 题目描述

Sergei B., the young coach of Pokemons, has found the big house which consists of $ n $ flats ordered in a row from left to right. It is possible to enter each flat from the street. It is possible to go out from each flat. Also, each flat is connected with the flat to the left and the flat to the right. Flat number $ 1 $ is only connected with the flat number $ 2 $ and the flat number $ n $ is only connected with the flat number $ n-1 $ .

There is exactly one Pokemon of some type in each of these flats. Sergei B. asked residents of the house to let him enter their flats in order to catch Pokemons. After consulting the residents of the house decided to let Sergei B. enter one flat from the street, visit several flats and then go out from some flat. But they won't let him visit the same flat more than once.

Sergei B. was very pleased, and now he wants to visit as few flats as possible in order to collect Pokemons of all types that appear in this house. Your task is to help him and determine this minimum number of flats he has to visit.

## 说明/提示

In the first test Sergei B. can begin, for example, from the flat number $ 1 $ and end in the flat number $ 2 $ .

In the second test Sergei B. can begin, for example, from the flat number $ 4 $ and end in the flat number $ 6 $ .

In the third test Sergei B. must begin from the flat number $ 2 $ and end in the flat number $ 6 $ .

## 样例 #1

### 输入

```
3
AaA
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
bcAAcbc
```

### 输出

```
3
```

## 样例 #3

### 输入

```
6
aaBCCe
```

### 输出

```
5
```

# 题解

## 作者：MIN__2500 (赞：5)

[原题网址](https://vjudge.net/problem/427892/origin)

CF归在尺取法，so我附上一篇尺取法的代码

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

const int N = 1e5 + 100;
char arr[N];
set<char> ss;
map<char,int> mm;
int main()
{
        int n;
        cin >> n;
        for(int i=1;i<=n;i++)
        {
                cin >> arr[i];
                ss.insert(arr[i]); //应用set去重的性质
        }
        int size = ss.size(); //set的长度为字符串中不同字符的个数
        int ans = n;
        int l = 1,r = 0; 
        int cnt = 0;
        while( l<=n && r<n )
        {
                r++;  
                if(mm[arr[r]]==0) cnt++;  //移动尺子的右端点，若为新出现的字符，cnt++
                mm[arr[r]]++;  //更新map

                while(cnt==size) //当尺子里面刚好有所有的字符，缩小尺子的区间
                {
                        ans = min(ans, r-l+1); //更新答案
                        mm[arr[l]]--;    //删除map里面的l端点
                        if(mm[arr[l]]==0) cnt--; //删除左端点后，若尺子内没有该字符，则cnt--
                        l++; //把尺子左端点右移
                }
                if( l>r ) break;
        }
        printf("%d\n",ans);
        return 0;
}
```


---

## 作者：kevin1616 (赞：3)

### 审题
在长度为 $n$ 的字符串 $S$ 中找到一个区间，使得区间包含序列中所有的字母，求该区间最短长度。
***
### 方法
+ 【暴力】我们正常情况下都会想到暴力，但是暴力在这道题并不适用。因为时间复杂度是 $O(n^2)$，故不可以使用该方法。
+ 【尺取法】那么可以看到，题目要求最短区间，可以想到使用尺取法。由于时间复杂度是 $O(n)$，故该方法可行。

***
### 思路
尺取法核心是双指针，利用两个 map 进行存储当前字母数量和初始字母数量。每次在区间右端加入一个字母，如果加入后该字母总数仅有一个，则该字母在此次判断之前未出现，故将当前字母总数 $+1$。然后在嵌套循环内，每次将左指针向左移一位，判断该字母是否仍然存在。如果存在，则统计当前长度；如果不存在，则将当前字母总数 $-1$。一直循环直到当前字母总数 $\le$ 总字母个数，即不满足题目要求时，退出嵌套循环。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a;
int x,m;
int ans = 1e9,sum;
map <char,int> mp1,mp2;
int main(){
    cin >> n >> a;
    a = " " + a;
    for(int i = 1;i <= n;i++){ //统计当前每个字母的个数和字母种类数
        if(mp1[a[i]] == 0) m++;
        mp1[a[i]] = 1;
    }
    int l = 0,r = 1; //定义左指针和右指针，并初始化
    while(r <= n){
        if(!mp2[a[r]]) sum++; //统计已有数量
        mp2[a[r]]++; //进行加入操作
        while(sum == m){ //进行删除操作
            ans = min(ans,r - l);
            l++; //出去一个字母
            mp2[a[l]]--; //统计现存数量
            if(!mp2[a[l]]) sum--;
        }
        r++; //进来一个字母
    }
    cout << ans << endl; //输出答案
    return 0; //好习惯
}
```
不抄题解，从我做起！

---

## 作者：YuntianZhao (赞：3)

# CF701C

这道题是一道比较典型的双指针。

l、r分别表示区间的左右端点，type表示区间中的种类的数量。用一个map来维护区间内不同的字符的数量。

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

map<char, int> mp;

int main() {
  int n, type = 0, ans;
  string s;
  cin >> n >> s;
  ans = n;
  int l = 0, r = 0;
  for (r = 0; r < n; r++) {
    mp[s[r]]++;
    while(mp[s[l]] > 1 && l < r) {
      mp[s[l]]--, l++;
    }
    if (mp.size() > type) type++, ans = r - l + 1;
    ans = min(ans, r - l + 1);
  }
  cout << ans;
  return 0;
}

```



---

## 作者：老彩笔 (赞：2)

感觉这道题类似于[CF660C](https://www.luogu.org/problem/CF660C)

他们的答案都有**单调性**,所以都可以用二分来实现

我们直接二分答案,可以 $O(n*m)$ 判断，显然是不行的

$m$ 是字符串里面**不同**的字符(区分大小写)个数

至于不同的字符,我们可以开一个$bool$数组记录,这样可以统计总数

我们考虑如何优化check()函数:

这就要用到滑动窗口的思想:

在长度$n$中靠滑动来枚举每一个长度$mid$

细节如下:

1. 记录$li$~$ri$中不同字母的个数,如果等于总数直接返回$true$

2. 滑动窗口时,记录每个字母的个数,那么第$li-1$位的字母个数$-1$,
$ri$位的字母个数$+1$

	如果第$li-1$位的字母个数减为$0$,那么从上一个窗口继承过来的$num$要$-1$
    
3. 不要忘记**清空**数组~~本蒟蒻就吃过亏~~

$check()$数组如下:

由于本蒟蒻太懒,没有把字符转换成数字,各位dalao勿喷

```cpp

bool check(int len)
{
	memset(vis,0,sizeof(vis));//清空
	int num=0;//记录个数
	for(int i=1;i<=len;i++)//第一个窗口
        //因为不用减去li-1的字符,所以单独写
	{
		if(!vis[(int)ch[i]])
		{
			num++;
			vis[(int)ch[i]]++;
		}
		else vis[(int)ch[i]]++;
	}
	if(num==cnt)return 1;
	for(int i=2;i<=n-len+1;i++)//剩下的窗口
	{
		int r=i+len-1;
		if(!vis[(int)ch[r]])
		{
			num++;
			vis[(int)ch[r]]++;
		}
		else vis[(int)ch[r]]++;
		vis[(int)ch[i-1]]--;//减去li-1的字符个数
		if(!vis[(int)ch[i-1]])num--;//如果减没了,num也要减1
		if(num==cnt)return 1;
	}
	return 0;
}

```

二分过程就不解释了

代码如下:

```cpp

#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
char ch[maxn],s[maxn];
int vis[maxn];
int n,cnt,ans;
bool check(int len)
{
	memset(vis,0,sizeof(vis));
	int num=0;
	for(int i=1;i<=len;i++)
	{
		if(!vis[(int)ch[i]])
		{
			num++;
			vis[(int)ch[i]]=1;
		}
		else vis[(int)ch[i]]++;
	}
	if(num==cnt)return 1;
	for(int i=2;i<=n-len+1;i++)
	{
		int r=i+len-1;
		if(!vis[(int)ch[r]])
		{
			num++;
			vis[(int)ch[r]]++;
		}
		else vis[(int)ch[r]]++;
		vis[(int)ch[i-1]]--;
		if(!vis[(int)ch[i-1]])num--;
		if(num==cnt)return 1;
	}
	return 0;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>ch[i];
		if(!vis[(int)ch[i]])
		{
			cnt++;
			vis[(int)ch[i]]=1;
		}
	}
	memset(vis,0,sizeof(vis));
	int l=1,r=n,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	cout<<ans<<'\n';
	return 0;
}

```

祝大家$CSP$考出好成绩









---

## 作者：Stars_visitor_tyw (赞：1)

## CF701C They Are Everywhere 题解
### 分析
暴力做法：

1. 预处理统计字符的种类数。

2. 枚举区间的长度和起点（也可以是终点），验证该区间内是否包含所有种类字符。

暴力代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n, cnt[135], tot;
signed main()
{
    cin>>n>>s;
    for(int i=0;i<n;i++)
    {
        cnt[s[i]]++;
        if(cnt[s[i]]==1)
        {
            tot++;
        }
    }
    for(int len=tot;len<=n;len++)
    {
        for(int i=0;i+len-1<n;i++)
        {
            int j=i+len-1, tmp=0;
            memset(cnt,0,sizeof(cnt));
            for(int k=i;k<=j;k++)
            {
                cnt[s[k]]++;
                if(cnt[s[k]]==1)
                {
                    tmp++;
                }
            }
            if(tmp==tot)
            {
                cout<<len;
                return 0;
            }
        }
    }
}
```

时间复杂度：$O(n^3)$

很显然会超时。

考虑优化：尺取法——快慢指针

1. 设置快慢指针，慢指针 $lt=0$，快指针 $rt=-1$。

2. 循环移动快指针 $rt$，$cnt[s[rt]]+1$，若 $cnt[s[rt]]=1$，则 $tmp+1$，直到 $tmp=tot$。

3. 循环移动慢指针 $lt$，$cnt[s[lt]]-1$，若 $cnt[s[lt]]=0$，则 $tmp-1,lt+1$。

4. 重复步骤 2 和步骤 3，并在 $tmp=tot$ 时维护长度 $ans=\min(ans,rt-lt+1)$。

时间复杂度：$O(n)$，原因是快慢指针最多各移动 $n$ 次。

### 正确代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n, cnt[135], tot;
signed main()
{
    cin>>n>>s;
    for(int i=0;i<n;i++)
    {
        cnt[s[i]]++;
        if(cnt[s[i]]==1)
        {
            tot++;
        }
    }
    int lt=0, rt=-1, tmp=0, ans=1e9;
    memset(cnt,0,sizeof(cnt));
    while(rt<n-1)//快指针小于终点
    {
        while(rt<n-1&&tmp<tot)
        {
            rt++;
            cnt[s[rt]]++;
            if(cnt[s[rt]]==1)
            {
                tmp++;
            }
        }
        while(tmp==tot&&lt<=rt)
        {
            ans=min(ans,rt-lt+1);//更新最短长度
            cnt[s[lt]]--;//跳过该字符，这个字符出现次数--
            if(cnt[s[lt]]==0)
            {
                tmp--;
            }
            lt++;
        }
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：Z1qqurat (赞：1)

分享两种方法，一个尺取法，一个二分答案。

### 尺取法

简单粗暴，双指针 $lt$ 和 $rt$，分别表示目前所在区间的左边界和右边界。而我们写一个 $while$ 循环，条件是右指针没有到 $n$，里面套两个小循环，分开解释。

·前一个循环为右指针右移直到目前区间包含所有字符，跳出循环，维护答案 $ans$。

·后一个循环为左指针左移直到目前的区间已经不包含所有字符，循环期间一直维护 $ans$。

一些细节看代码：

```cpp
int lt=1,rt=0,cnt=0;//左指针，右指针，cnt是目前区间内包含的字符种类数。
while(rt<n){//右指针没有超出范围。
	while(cnt<tot&&rt<n){//tot是整个序列里面包含的字符种类数。
		rt++;//右指针右移。
		if(vis[ch[rt]]==0)cnt++;//如果此字符没有出现过，目前的字符种类数+1。
		vis[ch[rt]]++;//此字符出现的次数+1。
		}
	while(cnt==tot){//目前包含所有种类字符。
		ans=min(ans,rt-lt+1);//维护ans。	
		vis[ch[lt]]--;//被删除的字符出现次数-1。
		if(vis[ch[lt]]==0)cnt--;
		lt++;	
	}
}
```

### 二分法

所有满足条件的 $ans$ 具有单调性，于是可以二分答案，只需要在写 $check$ 函数的时候采用一下滑动窗口的思想。

二分比较死板，细节少，这里不做详解：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+10;
int n,ans,vis[150],tot;
char ch[MAXN];

bool check(int len){
	memset(vis,0,sizeof(vis));
	int l=1,r=len,cnt=0;
	for(int i=l;i<=r;i++){
		if(vis[ch[i]]==0)cnt++;
		vis[ch[i]]++;
	}
	if(cnt==tot)return 1;
	while(r<n){
		r++;
		if(vis[ch[r]]==0)cnt++;
		vis[ch[r]]++;
		vis[ch[l]]--;
		if(vis[ch[l]]==0)cnt--;
		l++;
		if(cnt==tot)return 1;
	}	
	return 0;
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>ch[i];
		if(vis[ch[i]]==0)tot++;
		vis[ch[i]]++;
	}
	memset(vis,0,sizeof(vis));
	int lt=0,rt=n+1;
	while(lt+1<rt){
		int mid=(lt+rt)>>1;
		if(check(mid))rt=mid;
		else lt=mid;
	}
	printf("%d",rt);
	return 0;
} 
```

---

## 作者：shame_djj (赞：1)

从[【Hard Process】](https://www.luogu.org/problem/CF660C)过来的，那道题也是滑动窗口

~~那道题也是一遍 AC, rp ++~~

原题链接[【They Are Everywhere】](https://www.luogu.org/problem/CF701C)

我知道的滑动窗口一共有两种

一种是固定长度滑动，另一种是不固定长度滑动

有次模拟，我想到了滑动窗口，而且正解就是滑动窗口，

但是我因为想到固定长度的滑动窗口后，没有想到不固定长度的滑动窗口，

100 pts -> 70 pts

这就是我想说的一个点

通常固定长度的滑动窗口要配合二分答案来使用，时间复杂度 O (nlogn)

而不固定长度的滑动窗口则是 O (n)

但也不能仅仅就是看时间复杂度，要具体情况具体分析

还有就是一般的滑动窗口都是求最大的满足情况的区间

本题是最小的，但都差不多，稍微改点细节就好了

题意

		求出长度最小的包含序列中所有的字母的序列。

解题思路

		1.求出共有多少种不同字符

		2.滑动窗口求解

在这里我担心细节写挂，就先求出了左端点为 1 时的最小的右端点

还有就是一开始我想把所有的字符映射成一堆数，

后来想了想，直接把字符当成下标就好了，c ++ 会自己进行强制类型转换

代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;

char a[maxn], b[maxn];
int vis[1000];
int n, tot, s;

void djj_lxy () {
	scanf ("%d", &n);
	scanf ("%s", a + 1);
	for (register int i = 1; i <= n; i ++)
		if (!vis[a[i]])
			tot ++, vis[a[i]] = 1;
	memset (vis, 0, sizeof vis);
	int l = 1, r;
	for (register int i = 1; i <= n; i ++) {
		vis[a[i]] ++;
		if (vis[a[i]] == 1)
			s ++;
		if (s == tot) {
			r = i;
			break ;
		}
	}
	int ans = r;
	for (; r <= n; ) {
		if (s == tot) {
			ans = min (ans, r - l + 1);
			if (vis[a[l]] == 1)
				s --;
			vis[a[l]] --;
			l ++;
		}
		else {
			r ++;
			vis[a[r]] ++;
			if (vis[a[r]] == 1)
				s ++;
			
		}
	}
	printf ("%d\n", ans);
}

int main () {
	djj_lxy ();
}
```

那么本题就完了

我解题，捎带着说了点滑动窗口

离 CSP-S 还有几天，祝大家 rp ++

也希望自己能更努力一些，加油

---

## 作者：huangmingyi (赞：0)

### 题目分析
$10$ 分做法：
1. 利用桶标记并统计字符的种类 $tot$。
2. 枚举区间的长度 $len$，从 $tot$ 到 $n$。
3. 再枚举区间的起点 $i$，则终点 $j = i + len - 1$。
4. 枚举 $i$ 到 $j$ 之间的字符并统计种类数，若种类数等于 $tot$。   
要 $n^3$ 的时间。

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=160;
string s;
int tot[N],num,cnt[N],minn=1e18;
signed main(){
	int n;
	cin>>n;
	cin>>s;
	s='!'+s;
	for(int i=1;i<=s.size()-1;i++){
		tot[(int)(s[i])]++;
		if(tot[(int)(s[i])]==1){
			num++;
		}
	}
	for(int len=num;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1,tmp=0;
			memset(cnt,0,sizeof(cnt));
			for(int k=i;k<=j;k++){
				cnt[(int)(s[k])]++;
				if(cnt[(int)(s[k])]==1){
					tmp++;
				}
				if(tmp==num){
					minn=min(minn,j-i+1);
					break;
				}
			}
		}
	}
	cout<<minn;
	return 0;
}
```

优化方法：快慢指针
1. 设慢指针等于 $1$，快指针等于慢指针建议。
2. 循环移动快指针，快指针加加，并统计字符种类数，直到字符种类数等于 $tot$ 或者快指针等于 $n$ 停下。
2. 当字符种类数等于 $tot$ 时，循环移动慢指针 $lt$，当 $cnt_{a[lt]} = 0$ 时，字符种类数减减。
4. 重复步骤 $2$ 和 $3$，并在字符种类数等于 $tot$ 时维护最小区间长度。

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=160;
string s;
int tot[N],num,cnt[N],minn=1e18;
signed main(){
	int n;
	cin>>n;
	cin>>s;
	s='!'+s;
	for(int i=1;i<s.size();i++){
		tot[(int)(s[i])]++;
		if(tot[(int)(s[i])]==1){
			num++;
		}
	}
	int rt=0,lt=1,tmp=0;
	while(rt<n){
		while(tmp<num && rt<n){
			rt++;
			cnt[s[rt]]++;
			if(cnt[s[rt]]==1){
				tmp++;
			}
		}
		while(tmp==num && lt<=rt){
			minn=min(minn,rt-lt+1);
			cnt[s[lt]]--;
			if(cnt[s[lt]]==0){
				tmp--;
			}
			lt++;
		}
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：WaterSky (赞：0)

[每题必有的题目传送门。](https://www.luogu.com.cn/problem/CF701C)

## 题目描述：
给出一个长度为 $n$ 的序列，求出长度最小的序列 that 包含序列中所有的字母（区别大小写）。

很明显，可以使用双指针，因为是求最短的包含所有字母的子串。那么要怎么尺取呢？通过这个问题，我们可以衍生出两种做法，我会尽量仔细讲解。

## 第一种方法：双指针。
这一种做法呢，我是一开始想出来方法，但是错了，我就去看题解，发现我就错了几个空。

对于这一题，我们使用的双指针其实也就是枚举算法，但是优化过的。但是虽然是枚举，也要有枚举的方法，也有分高低级的枚举。我们就讲一下高级的枚举。由于前面说过是双指针，那么我们可以枚举右区间，然后再找到左区间。因为每一个右区间的最优区间的部分都可以是下一个最优区间的部分，所以我们不必将左区间清空。比较难理解，对吧。

```
#include<bits/stdc++.h>
using namespace std;
map<char,long long>M;
long long n,x,y,ans,t;
char a[100005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	x=1,y=1;
	for(y=1;y<=n;y++)
	{
		M[a[y]]++;
		while(M[a[x]]>1 && x<y) M[a[x]]--,x++; //找到最优的左区间。
		if(M.size()>t) ans=y-x+1,t++; //如果是目前所有区间中最优的，那么直接等于。		
        	ans=min(ans,y-x+1);//如果不是，那么比较最小值。
	}
	cout<<ans;//输出。
	return 0;
} 
```
比较难理解？可以看看第二个算法。
## 第二个算法：二分+尺取法。
二分应该不用具体讲吧？如果不懂，可以去搜索二分的算法。我们就主要讲怎么尺取。

不过在这之前，先知道一下为什么可以二分？因为满足单调性。你想一下，一个序列，比如：abba，如果序列长度为 $2$ 的可以满足需求，那么 $3$，$4$ 也一定可以。这就是满足单调性。

返回尺取法，我们的老师讲过，尺取法为什么叫尺取法，是因为这个区间就像一把尺子，位置可以变，但长度不变。我们可以二分尺子的长度，然后在能容下尺子的所有空位判断能否满足需求。

```
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,ans,t;
char a[100005];
map<char,int>b;
bool pd(long long x)//判断函数。
{
	map<char,int>B;
	for(int i=1;i<=x;i++) B[a[i]]++;//尺取法基本操作。
	if(B.size()==b.size()) return 1;//如果符合那么就返回正确。
	for(int i=2,j=x+1;j<=n;i++,j++)//尺取法。
	{
		B[a[i-1]]--,B[a[j]]++;//尺取法基本操作。
		if(B.size()==b.size()) return 1;//同上。
	} 
	return 0;//如果都不可以，那么就返回错误。
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]++;
	long long start=0,finish=n+1,mid;
	while(start+1<finish)//二分。
	{
		mid=(start+finish)/2;
		if(pd(mid)) finish=mid;
		else start=mid;
	}
	cout<<finish;
	return 0;
} 
```

---

## 作者：Luo_gu_ykc (赞：0)

## 题目大意

给定一个字符串 $s$ （只包含字母的大小写），请你求出一段包含序列里所有字符的子串的最小长度。

## 思路

使用双指针的思路，直接模拟两个双指针；

* 左右指针默认为初始值，然后移动右指针，直到左右指针包围的子串包含字符串里的所有字符，然后与最小值比较，再移动左指针，右指针以此类推 $\dots$ ；

因为两个指针是单调不减的，所以每个下标最多被遍历两次，所以时间复杂度为 $O(n)$；

（有可能比较抽象，所以拿代码演示。）

## Code

```cpp

#include<bits/stdc++.h>

using namespace std;

int n, num, sum, mini = INT_MAX; 
bool v[135];
string s;

map <char, int> cnt;

int main(){
    cin >> n >> s;
    for(int i = 0; i < s.size(); i++){
        if(!v[s[i] - 'A']){ // 如果是一个新字符
            num++; 
		}
		v[s[i] - 'A'] = 1; // 标记 
    }
    for(int i = 0, j = i; i < n; i++){ 
        for(; j < n && sum < num; j++){ // 移动右指针，满足条件就直接退出
            if(!cnt[s[j]]){ // 出现了新的字符
                sum++;
			}
            cnt[s[j]]++;
        }
        if(sum == num && (j - i) < mini){ // 满足条件
            mini = (j - i);
            l = i;
            r = j - 1;
        }
        cnt[s[i]]--; // 移动左指针
        if(!cnt[s[i]]){
            sum--;
		}
    }
    cout << mini;
    return 0;
}


```

---

## 作者：二叉苹果树 (赞：0)

### 题意简述

给出一个长度为 $n$ 的序列，求出长度最小的序列 $that$ 包含序列中所有的字母（区别大小写）.

### 样例分析

```
input:
7
bcAAcbc

output:
3
```
以样例#2为例，该序列中 共有 ```b```、```c```、```A``` 三种字母.

很显然，子序列 ```bcA``` 是最短的子序列，故输出其长度.

### 尺取法

考虑分别记录左端点 $l$ 与右端点 $r$ 以维护子序列，若当前子序列不满足题意，则将 $r$ 右移，直至子序列中每个字母均被包含. 同时，若序列中处于 $l$ 处的字母在序列中再次出现，则也将 $l$ 右移动，使当前维护的子序列最短，即使得子序列中重复的字母尽可能小.

### 实现步骤

首先，数据中已给出序列长度与序列，而无不同字母的个数，所以应先将后者进行统计. 

```cpp
    if(r[a[i]]==0)
        m++;
    r[a[i]]++;
```

这里的 $r$ 记录 $a_i$ 出现的次数，$m$ 记录字母种类总数.

接下来实现尺取法的过程.并且在满足题意时统计答案 $(r-l+1)_{min}$. 此处用 $Count$ 记录当前子序列中包含的字母种类个数.

```cpp
    while(l<=r&&r<=n)
    {
        if(s[a[r]]==0)
            Count++;
        s[a[r]]++;
        while(1)
        {
            if(s[a[l]]>=2)
                s[a[l]]--,l++;
            else
                break;
        }
        if(Count==m&&Min>r-l+1)
            Min=r-l+1;
        r++;
    }
```

以下是全部代码.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6;
int n,m,L,R;
char a[maxn];
map<char,int>s;
map<char,int>r;
int Count;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(r[a[i]]==0)
            m++;
        r[a[i]]++;
    }
    int l=1,r=1,Min=n;
    while(l<=r&&r<=n)
    {
        if(s[a[r]]==0)
            Count++;
        s[a[r]]++;
        while(1)
        {
            if(s[a[l]]>=2)
                s[a[l]]--,l++;
            else
                break;
        }
        if(Count==m&&Min>r-l+1)
        {
            Min=r-l+1;
            L=l,R=r;
        }
        r++;
    }
    if(L!=0)
        cout<<Min<<endl;
    else
        cout<<n<<endl;
    return 0;
}
```

---

## 作者：Mandel520 (赞：0)

**双指针法**

为了求得一个区间的长度, 需要知道这个区间的左右两个端点. 由于这个区间中出现的字母是所有种类的字母各自出现至少一次, 因此可以使用双指针法维护符合要求的区间

我们设左指针为`idx1`, 右指针为`idx2`. 此处使用左闭右开规则, 区间`[idx1,idx2)`即为题目中所求的 *that* 序列

考虑**贪心**策略: 当左指针固定时, 将右指针不断向右移动, 直到区间中包含所有种类的字母为止. 此处使用 `char_cnt[]` 数组记录区间内各种字母的数量, 使用变量 `total_char` 记录区间内字母的种类数

如果区间中没有包含全部的字母, 则将右指针向右移动, 把下一个字母纳入区间中, 如果下一个字母是第一次被纳入区间中, 则 `total_char++`

如果区间中包含了全部的字母, 则记录此时的区间长度. 如果此时的区间长度比之前记录的符合要求的最小区间长度更小, 则更新最小区间长度为当前长度

当区间中包含了全部字母时, 还要尝试把左指针向右移动, 不断去除最左边的字母, 使得符合要求的区间长度变小, 直到区间不符合要求(不包含所有字母)为止

**完整程序**:

```c
#include<stdio.h>
#include<string.h>

int n, m = 0;          //序列长度和字母总数  
char arr[1000005];     //储存序列
int char_cnt[10005];   //不同的字母出现次数
int total_char = 0;    //当前区间内的不同字母数
int min_len = 1000000; //区间的最短长度

int main(){
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++){ //读入序列
        scanf("%c", &arr[i]);
        if (char_cnt[arr[i]] == 0) m++; //读到不同的字母, 则增加字母种类
        char_cnt[arr[i]]++;
    }
    memset(char_cnt, 0, sizeof(char_cnt));

    int idx1 = 0, idx2 = 0; //左右指针
    while (idx2 < n){
        while(total_char < m && idx2 < n){ //移动右指针, 直到区间包含所有字母
            idx2++;
            if (char_cnt[arr[idx2]] == 0){
                total_char++;
            }
            char_cnt[arr[idx2]]++;
        }
    
        while(total_char == m && idx1 < n){ //移动左指针, 直到区间不包含所有字母
            if (idx2 - idx1 < min_len){
                min_len = idx2 - idx1; //更新最优解
            }
            idx1++;
            char_cnt[arr[idx1]]--;
            if (char_cnt[arr[idx1]] == 0){
                total_char--;
            }
        }
    }

    printf("%d\n", min_len);
    return 0;
}
```
本站的另一道题 [P1638 逛画展](https://www.luogu.com.cn/problem/P1638) 的思路与这道题也很相似

---

