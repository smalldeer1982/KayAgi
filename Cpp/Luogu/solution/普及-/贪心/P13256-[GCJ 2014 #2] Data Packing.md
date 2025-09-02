# [GCJ 2014 #2] Data Packing

## 题目描述

Adam 是个非常有条理的人，他一直热衷于整理自己的各种物品。特别是，他至今仍清晰地记得年轻时花了许多小时将电脑中的文件刻录到光盘上的情景。

在这个过程中，有两个非常重要的规则。首先，为了确保每张光盘上的标签都清晰明了，Adam 从不在同一张光盘上存放超过两个文件。其次，他绝不会将一个文件拆分到多张光盘中。当然，幸运的是，他使用的光盘容量总是足够大，能满足这两个规则。

回想往事，Adam 不禁开始思考：当时自己整理文件的方式是否最优？是否可能在不违反规则的前提下使用更少的光盘？他现在会提供一张光盘的容量（所有光盘容量相同），以及他曾经存储的文件大小列表。请你帮助 Adam 计算，遵守上述两个重要规则的前提下，最少需要多少张光盘才能存储所有文件。


## 说明/提示

## 限制条件

- $1 \leq T \leq 100$
- $1 \leq X \leq 700$
- $1 \leq S_i \leq X$

### Small 数据集（5 分）

- 时间限制：~~60~~ 3 秒。
- $1 \leq N \leq 10$

### Large 数据集（8 分）

- 时间限制：~~120~~ 5 秒。
- $1 \leq N \leq 10^4$

翻译由 ChatGPT-4o 完成

## 样例 #1

### 输入

```
3
3 100
10 20 70
4 100
30 40 60 70
5 100
10 20 30 40 60```

### 输出

```
Case #1: 2
Case #2: 2
Case #3: 3```

# 题解

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P13256)
## 前言
目前洛谷主题库最后一道橙题，水一下，顺便把这题的题解区补充一下。
## 思路
题目不难，求所有文件存进光盘至少需要多少个光盘，同时需满足以下 $2$ 个条件：
1. 不在同一张光盘上存放超过两个文件。
2. 不会将一个文件拆分到多张光盘中。

首先肯定要排序，而每张光盘内存的肯定是一个小文件加一个大文件。

双指针，分别指向排完序后的数组的头尾。操作如下：

- 若指针指向的元素相加在 $X$ 的范围内，则计数，同时让左指针右移一位，让右指针左移一位。
- 若指针指向的元素相加在 $X$ 的范围外，则右指针指向的元素需单独存在一个光盘内，则右指针左移一位，且计数。

思路理清了，可以写代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[100005];
int main(){
	scanf("%d",&t);
	for(int q=1;q<=t;q++){
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++) scanf("%d",a+i);
		sort(a+1,a+n+1);//排序
		int l=1,r=n,ans=0;
		while(l<=r){
			if(a[l]+a[r]>x) r--;//不可以则右端点缩小
			else l++,r--;//可以则两边缩小
			ans++;//计数
		}
		printf("Case #%d: %d\n",q,ans);
	}
	return 0;
}
```
~~顺便夸赞一下这题的满分分数。（$13$ 分？）~~

撒花！

---

## 作者：Fine_Dust_Z (赞：2)

### 题目大意
现有 $T$ 组数据每组数据包括 $N$ 和 $X$ 以及 $N$ 个数。

$X$ 表示容量这里我们用 $V$ 来代指，后面的 $N$ 个数表示每个物品的体积这里我们用数组 $a$ 来代指。

### 思路
我们考虑到题目中所给出的数据。
> Large 数据集（8 分）
>
>  时间限制：~~120~~ 5 秒。
>
> $1\le N \le10^4$

不难看出这道题使用 **sort** 和 **双指针** 是完全没有问题的。 
### 什么是双指针？
> 双指针顾名思义，就是同时使用两个指针，在序列、链表结构上指向的是位置，在树、图结构中指向的是节点，通过或同向移动，或相向移动来维护、统计信息。
> （以上为 [oiwiki](https://oiwiki.com/misc/two-pointer/) 中对双指针的介绍）。

通俗一点来说就是定义 $l$ 和 $r$ 分别指向数组的头部和尾部（可以理解为 **[双端队列](https://oiwiki.com/ds/queue/#%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97)**），每次在使用头（尾）指针指向的数后使头（尾）指针向后（前）移动。

### 如何实现
我们对每组数据每次定义一个头指针 $datefirst$ 和一个尾指针 $dateend$ 。

使 $datefirst$ 指向 $a[1]$ ， $dateend$ 指向 $a[n]$ (其实是赋值)。

考虑到 [贪心](https://oiwiki.com/basic/greedy/) 所以每次从最大的开始选，如果可以再选最小的就再选最小的（当然每次选了之后对头尾指针进行移动）。

由于题目并没有说 $a$ 是有序的，所以所以我们要对 $a$ 进行排序。

**注意**：每次只能选两个。
```cpp
#include<bits/stdc++.h>
// 万能头
#define ll long long
// 懒惰
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c == '-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}
//快读
const int N=1e4+50;
// 题目给出N<=10^4
ll T,a[N];
// T:T组数据 a:存储N个数
const bool cmp(int a,int b){
	return a<b;
} 
// sort排序
inline void solve(int cnt){
	ll n,v;
	read(n);
	read(v);
	for(int i=1;i<=n;i++)read(a[i]);//定义+读入
	sort(a+1,a+1+n,cmp);// 对a从小到大排序
	ll date_first=1,date_end=n;
    //date_first:头指针,date_end:尾指针
	ll ans=0;// 最小使用
	while(date_first<=date_end){//如果还有a没有被分配
		ll total1=0,total2=0;
        //total1:记录使用容量 total2:记录有多少个a被分配
		while(a[date_end]<=v-total1&&total2<=1&&date_first<=date_end){
        // 先考虑大的
			total1+=a[date_end];
			total2++;// 对a进行分配
			date_end--;// 尾指针前移
		}

		while(a[date_first]<=v-total1&&total2<=1&&date_first<=date_end){
        // 再考虑小的
			total1+=a[date_first];
			total2++;// 对a进行分配
			date_first++;// 头指针后移
		}
		ans++;// 又使用了一个空间
	}
	printf("Case #%lld: %lld\n",cnt,ans);//输出
}

int main(){
	read(T);
	ll cnt=0;// 计数器
	while(T--){
		cnt++;// 记录现在是第几组数据
		solve(cnt);// 调用
	}
	return 0;
}

```

---

## 作者：huhengrui2013 (赞：1)

### 题解：P13256 [GCJ 2014 #2] Data Packing

[传送门](https://www.luogu.com.cn/problem/P13256)

### 思路：

先将文件容量从小到大排序，由于一个光盘最多只能发两个文件，所以可以用双指针解决，每次尝试让一个光盘同时容纳头指针和尾指针；若不能，就只能容纳尾指针。最后把次数加起来即可。

### AC Code:

```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){

    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case #"<<i<<": ";
        int n,m;
        cin>>n>>m;
        int a[n+1];
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);
        int l=1,r=n,ans=0;
        while(l<=r){
            if(a[l]+a[r]<=m) l++;
            r--;
            ans++;
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：Yang_Jun (赞：1)

这是一道比较简单的贪心题。

主要思想是：每次选择两个大小不超过光盘容量 $X$ 且大小最接近 $X$ 的文件，将他们存在一张光盘上，如果没有符合条件的两个光盘，就每张光盘存一个文件。

那么我们可以使用两个指针，一个从最小文件开始（左指针），一个从最大文件开始（右指针），尝试将最大的文件和最小的文件配对放在同一张光盘上。

+ 如果两者之和 $\le X$ ，则可以配对，使用一张光盘。

+ 如果两者之和$ > X$ ，则最大的文件必须单独使用一张光盘。

### 代码
```
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;
	cin>>T;
	int t=T;//输出时需要用
	while(T--){
		int n,x;
		cin>>n>>x;
		vector<int>S(n);
		for(int i=0;i<n;i++) cin>>S[i];
		sort(S.begin(),S.end());//排序
		int i=0,j=n-1,cot=0;
		while(i<=j){
			if(S[i]+S[j]<=x){//如果能配对
				i++;
				j--;//一张光盘存两个文件
			}else{//不能的话
				j--;//一张光盘存一个文件    
			}
			cot++;
		}
		cout<<"Case #"<<(t-T)<<':'<<cot<<endl;
	}
}

---

## 作者：tujiaqi12 (赞：1)

[双倍经验](https://www.luogu.com.cn/problem/P1094)
## 思路
贪心。

第一步，将所有数据排序。

第二步，既然光盘要最少，那就要让尽量多的光盘同时装两个东西。

第三步，经排序后，原数组成为了不递减序列，为了要让尽量多的光盘同时装两个东西，我们应该让一个东西与近可能大的东西和为一组。

第四步，从前往后遍历数组，在每一次遍历中再从后往前遍历能一起放进光盘的物品的最大值。同时统计有多少光盘同时装两个东西。

如何优化?由于原数组成为了不递减序列，所以每次不需重新从最后开始遍历，而是接着上次遍历到的地方继续不利。若上次找到第一个和第五个搭配，下一次从从第四个往前找即可。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t;
ll n,x,a[10005];
int main(){
	scanf("%lld",&t);
	for(ll i = 1;i <= t;i++){
		scanf("%lld%lld",&n,&x);
		for(ll j = 1;j <= n;j++){
			scanf("%lld",&a[j]);
		}
		sort(a+1,a+n+1);
		ll l = 1,r = n,ans = n;
		while(l < r){
			while(a[l] + a[r] > x && (r-1)>l){
				r--;
			}
			if(a[l] + a[r] <= x){
				ans--;
			}
			l++;
			r--;
		}
		printf("Case #%lld: %lld\n",i,ans);
	}
	return 0;
}
```

---

## 作者：David4119 (赞：1)

[Link to the problem](https://www.luogu.com.cn/problem/P13256)

# 算法：
看了算法标签，我们立刻明确了本题需要用到两个算法：贪心和双指针。我们一个一个讲：

1. 贪心，是一个很常见的方法。对于本题，为了节约光盘，我们肯定要优先考虑占用内存大的文件。所以，我们应当先将数组 $S$ 降序排列，从大的开始分配。

2. 关于双指针：

>双指针算法是一种通过两个指针（索引或引用）协同遍历或搜索数据结构的技巧，常用于优化时间复杂度至 O(n)。‌ 其主要分为对撞指针、快慢指针、滑动窗口和同向双指针等类型，适用于数组、链表等问题场景。

本题我们需要用到的是对撞指针：

>指针分别从首尾向中间移动，用于有序数组的搜索或判断（如两数之和、回文串验证）。

在本题中，我们可以弄两个指针变量 $h$ 和 $r$,分别存储从头和从尾部遍历时，当前的元素下标。对于 $S_h$ 和 $S_r$,我们先开个新的光盘，把 $S_h$ 放进去, $h$ 指向下一个元素。如果剩下的空间 $\ge S_r$,就把 $S_h$ 也放进去，$r$ 指向前一个元素。如此重复，直到 $r<h$,就完成了遍历。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool comp(int x,int y){
    return x>y;
}//定义判断函数
int main(){
    int t;
    cin>>t;
    for(int k=1;k<=t;k++){
        int n,x,h,r,ans=0;
        cin>>n>>x;
        int s[n+1];
        for(int i=1;i<=n;i++)
            cin>>s[i];
        sort(s+1,s+n+1,comp);//贪心
        h=1,r=n;
        while(r>=h){
            ans++;
            if(x-s[h]>=s[r])
                r--;
            h++;
        }//双指针
        printf("Case #%d: %d\n",k,ans);
    }
    return 0;
}
```

---

## 作者：lby_commandBlock (赞：1)

## 思路

一道比较简单的贪心。

我们考虑第 $i$ 个文件。由于每个光盘只能装两个文件，所以考虑第 $i$ 个文件的最佳搭档文件。显然，就是装下这个文件后剩下的容量最大可装的文件。

单凭口述可能无法理解，但是代码肯定清晰许多。

## 代码

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int N = 1e4+9;

int T, n, x, a[N];

bool vis[N];

void solve() {
    cin >> n >> x;  
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vis[i] = false;
    }
    sort(a + 1, a + 1 + n); // 排序
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i])
            continue; // 这个文件已经在光盘里了
        int val = x - a[i], pos = -1;
        for (pos = n; pos >= i; pos--)
            if (a[pos] <= val && !vis[pos])
                break; // 找到了最佳搭档文件
        if (pos == -1) {
            cnt++;
            // 没有找到，可怜的文件只能单独一个光盘咯
            continue;
        }
        vis[pos] = true;
        // 找到了，给最佳搭档文件打个记号
        cnt++;
    }
    cout << cnt << endl; // 输出总共的光盘数量
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
```

---

## 作者：W_ater (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13256)

本题做法：排序 + 双指针。

## 思路
观察题目，**每张光盘最多只能存两个文件**，想到贪心处理这个问题：  
尽量将未存储的**最大文件**和未存储的**最小文件**放在同一张光盘里。  
为下文叙述方便，称**匹配**为一对能放在同一张的文件  
贪心算法成立的原因是：  
1. 若当前最大文件不能与当前最小文件匹配，那么一定不能与任何其他文件匹配。  
2. 若当前最大文件能与当前最小文件匹配，那么后续所有文件一定能与此时当前最小文件匹配，却不保证一定存在其他能与当前最大文件匹配的文件。
## 实现
所以我们只需要先**排序**。  
之后用双指针分别指向当前的最大文件和最小文件，  
若两文件和小于光盘容量左指针右移右指针左移，增加答案，表示这两个文件共占一个光盘。  
若两文件和大于光盘容量，则只移动右指针，增加答案，表示当前最大文件独占一个光盘。
最后输出即可。
## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100005];
int t,n,x,l,r;
int ans=0;
int main(){
	scanf("%d",&t);
	for(int p=1;p<=t;p++)
	{
		ans=0;
		scanf("%d%d",&n,&x);
		l=1,r=n;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);//排序 
		while(l<=r)//无需特判l==r，ans总会++ 
		{
			if(a[l]+a[r]<=x)
			{
				l++;
			}
			r--;
			ans++;//总要r-和ans+ 
		}
		printf("Case #%d: %d\n",p,ans);
	}
	return 0;
}
```
感谢阅读

---

## 作者：Yu_Yaoxuan (赞：1)

#### [题目传送门](https://www.luogu.com.cn/problem/P13256)  


---

一道比较简单的贪心题目。  
### 题意
#### 两个规则：
- 每张光盘可以存储 $1$ 或 $2$ 份文件（在不超过光盘容量的前提下）。
- 不能将一份文件拆分到两个光盘里。

输出最小使用光盘张数。  
### 思路  
考虑贪心。  
将文件大小按从大到小排序，使用双重循环遍历，如果两个文件能放入同一张光盘，那么就将这两份文件设为已完成。如果内层循环遍历结束仍未找到符合要求的文件，那么这个文件只能单独放在一张光盘，并将此文件设为已完成。可以参照代码理解。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int arr[15200]; //存储文件大小，当arr[i]==0时则为已放入 
bool cmp(int a,int b){
	return a>b; //从大到小排序 
}
int solve(int n,int x){
	int ans=0; //存储结果 
	for(int i=1;i<=n;i++) cin>>arr[i]; 
	sort(arr+1,arr+1+n,cmp); //STL里的排序 
	for(int i=1;i<=n;i++){ //遍历 
		bool f=false;
		if(arr[i]!=0){
			for(int j=i+1;j<=n;j++){
				if(arr[j]!=0 && arr[i]+arr[j]<=x){ //两个文件可以放入一张光盘里 
					ans++; //结果+1 
					arr[i]=arr[j]=0; //标记 
					f=true;
					break;
				}
			}
            if(f==false){ //只能单独放 
    			ans++; //结果+1 
    			arr[i]=0; //标记 
    		}
		}
	}
	return ans; //返回结果 
}
signed main(){
	cin.tie(0)->sync_with_stdio(0); //加快读入速度 
	int T;
	cin>>T;
	for(int i=1;i<=T;i++){
		int n,x;
		cin>>n>>x;
		cout<<"Case #"<<i<<": "<<solve(n,x)<<'\n'; //每个测试用例输出一个答案 
	} 
	return 0; //好习惯 
}
```

---

## 作者：Lagrange_NoAria (赞：0)

#### 题目部分

##### 个人评价

经典的贪心题。

##### 题意简化

用最少的光盘存文件，而文件的总数与每个文件的内存及光盘的内存均已给出。

#### 题解部分

##### 算法设计

我们可以使用贪心算法，并以相向双指针为辅助。具体来说，我们可以把所有文件的内存进行排序，之后用最大的加最小的，如果小于光盘内存就将答案加一，否则就将大的下标减一。

##### 具体实现


```cpp
#include<bits/stdc++.h>
using namespace std;
void f(int k){
    int w,n,p[10005],ans=0;
    cin>>n>>w;
    for(int i = 1; i <= n; i++){
        cin>>p[i];
    }
    sort(p+1,p+n+1);
    int l=1,r=n;
    while(l<=r){
        if(p[l]+p[r]<=w){
            l++;
            r--;
            ans++;
        }
        else{
            r--;
            ans++;
        }
    }
    cout<<"Case #"<<k<<": "<<ans<<endl;
}
int main(){
    int T;
    cin>>T;
    for(int i = 1; i <= T; i++) f(i);
    return 0;
}
```

---

## 作者：banglee (赞：0)

### P13256 [GCJ 2014 #2] Data Packing 题解
[题目传送门](https://www.luogu.com.cn/problem/P13256)

## 思路
考虑双指针。

用两个指针，一个从最小的文件开始，另一个从最大的文件开始。将最大的文件和最小的文件配对，如果它们的和不超过光盘容量，则配对成功，移动两个指针。否则，只能单独存放最大的文件，移动右指针。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	for (int c=1;c<=T;c++) {
		int n,x,a[10005];
		cin>>n>>x;
		for (int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+1+n);
		int l=1,r=n,ans=0;
		while (l<=r) {
			if (a[l]+a[r]<=x) l++,r--;
			else r--;
			ans++;
		}
		cout<<"Case #"<<c<<": "<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13256)

### 思路

首先，看到这道题中有一个很重要的条件，就是每个光盘只能最多有两个文件，那么很容易就能想到可以用双指针做。

先排序，然后我们定义两个变量 $l$ 和 $r$，分别表示左指针和右指针，每一次，我们看左指针的数加右指针的数是否超过一个光盘的容量，若是，则直接移动右指针，若否，则同时移动左右指针，最后记得统计光盘数量并输出。

注意输出的格式。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,a[10005],cnt;
signed main(){
    cin>>t;
    for(int i=1;i<=t;i++)
    {
    	scanf("%lld%lld",&n,&m);
    	for(int j=1;j<=n;j++)  scanf("%lld",&a[j]);
    	sort(a+1,a+n+1);
    	cnt=0;
    	for(int l=1,r=n;l<=r;)
    	{
    		if(a[l]+a[r]<=m)  l++,r--;
    		else  r--;
    		cnt++;
    	}
    	printf("Case #%lld: %lld\n",i,cnt);
    }
    return 0;
}
```

---

## 作者：SproutPower (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13256)
---

### 思路

先看标签，有贪心，那就想怎么贪。  
容易想到把能放的最大文件和最小文件放在同一个光盘中，可以证明这样选择最优。

### 证明

使用反证法：  
则假设不把最大和最小放在同一处更优  
不妨设 $a_1<a_2<a_3<a_4$，则根据假设得：$a_2a_4$、$a_1a_3$ 这样放在一起可能更优。  
而这样放的前提是：$a_2+a_4\leq X$，$a_1+a_3\leq X$。  
由 $a_1<a_2$、$a_2+a_4\leq X$ 得：$a_1+a_4\leq X$；  
由 $a_3<a_4$、$a_2+a_4\leq X$ 得：$a_2+a_3\leq X$；  
故也可以按照 $a_1a_4$、$a_2a_3$ 这样放。  
所以使用我们原来的贪心方法不会更劣。  
故假设不成立，所以把最大和最小放在同一处更优。  

至此，我们已经证明了我们贪心的正确性，剩下的就可以写代码了。

### 代码

```cpp
#include<bits/stdc++.h>
#define db double
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        int n,m;
        scanf("%d%d",&n,&m);
        db a[11451];
        bool vis[11451];
        int cnt=0,p=0;
        memset(vis,0,sizeof vis);
        for(int i=1;i<=n;i++)scanf("%lf",&a[i]);
        sort(a+1,a+1+n);
        for(int i=n;i>=1;i--){
            if(i<=p)break;
            if(a[i]+a[p+1]<=m)p++;
            cnt++;
        }
        printf("Case #%d: %d\n",t,cnt);
    }
    return 0;
}
```

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13256)

### 题目分析
为了最小化光盘的用量，我们需要尽可能多地将文件两个一对存放在同一张光盘上。  
我们用双指针贪心来解决。尝试将最小的和最大的文件配对放在同一张光盘上，如果这两个文件大小之和不超过光盘容量 $X$，则使用一张光盘。 如果两个文件大小之和超过 $X$，那么最大的文件单独放在一张光盘上。  

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int qt;

signed main()
{
	fst
	cin>>qt;
	for(int t=1;t<=qt;t++){
		int n,x;
		cin>>n>>x;
		int s[n+10];
		for(int i=1;i<=n;i++){
			cin>>s[i];
		}
		sort(s+1,s+n+1);//一定要排序
		int l=1,r=n;
		int ans=0;
		while(l<=r){
			if(s[l]+s[r]<=x){
				l++;
			}
			r--;
			ans++;
		}
        cout<<"Case #"<<t<<": "<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：libu2333 (赞：0)

贪心题。

因为所有光盘的容量相同且都只能装两个文件，我们可以贪心地用双指针枚举当前最大和最小的文件，如果能打包则将其打包在同一个光盘里，否则优先装大文件。

由于给定的文件数组不保证有序，所以在贪心之前要先 `sort` 一遍。

时间复杂度 $O(N \log N)$。（原比赛居然能开 $120s$ 的时限，不可思议。）

代码如下，注意输出格式。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int T;
int n,x,a[10005],ans;
int main(){
    cin>>T;
    for(int tt=1;tt<=T;tt++){ // 数据点编号
        cin>>n>>x;
        for(int i=0;i<n;i++) cin>>a[i];
        sort(a,a+n); // 按文件大小升序排列
        int i=0,j=n-1; // 双指针：i 指向最小文件，j 指向最大文件
        ans=0;
        while(i<=j){
            if(a[i]+a[j]<=x){ // 若可以一张光盘装两个文件
                i++,j--;     // 打包进一个光盘里
            }else{
                j--;         // 优先大文件用
            }
            ans++; // 每次循环都用了一张光盘
        }
        cout<<"Case #"<<tt<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：goIdie (赞：0)

## 思路

由于每个光盘最多放两个文件，我们考虑贪心策略：尽量让两个文件放在一起来节省光盘。

那么就很容易想到双指针了。先将文件按大小排序，然后将左指针指向最小文件，右指针指向最大文件。每次尝试将最小文件和最大文件配对，接下来分两种情况。

- 若两者之和不超过光盘容量 $X$，则可进行配对，消耗两个文件（左指针右移，右指针左移）。
- 若不能配对，则单独存放最大文件。因为如果此时的最大文件和此时的最小文件都不能配对，它与其他的文件同样不能配对。

每次操作后无论是否配对成功均需使用一张光盘。

当左指针大于右指针时循环结束。

时间复杂度 $O(N \log N)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,s[10001],l,r,ans;
int main(){
    cin>>T;
    for(int t=1;t<=T;t++){
        cin>>n>>x;
        memset(s,0,sizeof(s));
        for(int i=1;i<=n;i++){
            cin>>s[i];
        }
        sort(s+1,s+n+1);
        l=1,r=n,ans=0;//左右指针分别指向最小和最大文件 
        while(l<=r){
            if (l<r&&s[l]+s[r]<=x) {
                l++;//如果当前有两个文件且和不超过x，则配对
            }
            ans++;
            r--;//消耗最大文件（无论是否配对）
        }
        cout<<"Case #"<<t<<": "<<ans<<endl;
    }
    return 0;
}
```

---

