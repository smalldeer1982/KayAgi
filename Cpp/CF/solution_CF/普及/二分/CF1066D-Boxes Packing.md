# Boxes Packing

## 题目描述

有 $n$ 个物品，$m$ 个盒子。其中第 $i$ 个物品的大小为 $a_i$，所有盒子的大小均为 $k$。Makmis 先生想要将这些物品放入盒子中。对于每个物品，如果可以放入当前盒子中则放入当前盒子，否则换一个新的盒子放入。如果物品数量太多使得盒子装不下，可以**将先放入的物品丢弃**。求出最多能够放入多少物品。

## 说明/提示

#### 样例解释
- 在第一组样例中，可以将后 $4$ 个放入盒子。
- 在第二组样例中仅有一个盒子，故只能放入最后一个。
- 在第三组样例中有 $3$ 个大小为 $3$ 的盒子，每个盒子正好装满。
#### 数据规模与约定
保证 $1\le n,m\le2\times 10^5$，$1\le k\le10^9$，$1\le a_i\le k$。

## 样例 #1

### 输入

```
5 2 6
5 2 1 4 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 1 4
4 2 3 4 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 3 3
1 2 3 1 1
```

### 输出

```
5
```

# 题解

## 作者：Plozia (赞：7)

[博客效果更佳哦](https://blog.csdn.net/BWzhuzehao/article/details/99222471
)

**题意简化：**

有$N$个数，第i个数为$a_{i}$，你需要选出至多$M$个子序列，使得每一个子序列的和都<=k，并且这些子序列在原序列里面必须**连续且靠右**。问能选出多少个数。

## 1.暴力

我们可以枚举一个数$i$(1<=$i$<=$N$)，表示前i个数不选，选第$i+1$到第$N$个数，再利用如下的代码进行判断。如果返回true，那么输出$n-i$。时间复杂度$O({N}^{2})$。

```cpp
bool check(int i)
{
	//从第i+1个数选到第N个数
	//tmp表示当前选的数的和
	//sum表示已经选了多少个子序列 
	int tmp=0,sum=0;
	for(int j=i+1;j<=n;j++)
	{
		if(tmp+a[j]>=k)//如果当前子序列的和>=k 
		{
			sum++;//进入下一个子序列 
			tmp=a[j];//把这个子序列的初始和记为a[j] 
		}
		else tmp+=a[j];//否则，就可以选第j个数，把当前子序列的和加上a[j] 
	}
	if(sum>m) return 0;//如果子序列的个数>m，方案不可行，返回false 
	return 1;//否则返回true 
}
```

当然，一看数据范围：1<=$N$<=${2*10^{5}}$，就知道$O({N}^{2})$肯定要炸。所以我们需要一种更快的方法。

## 2.线性

这道题正着做时间复杂度要爆炸。

我们数学老师说过一句话：**“正若难，则反。”**

所以我们可以反着做。

从第$N$个数开始倒推（设当前的数为$t$），把第$t$个数加入当前这个子序列，如果第$t$个数加入后子序列>=$M$个，那么前$t$个数就是要抛弃的数。当然如果数字选完了也要退出。时间复杂度为$O(N)$，足够通过本题。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[200000+10],sum,t;
int box[200000+10];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) sum+=a[i];
	t=n;//将t初始化为$N$ 
	while(m!=0&&t!=0)//当子序列还没有用尽或者是数字还没有选完的时候 
	{
		box[m]+=a[t];//将第M个子序列的和加上a[t] 
		if(box[m]>k)//如果第M个子序列的和>k，切换到下一个子序列 
		{
			m--;//下一个子序列 
			box[m]=a[t];//初始化新子序列的和=a[t] 
		}
		t--;//指向下一个数 
	}
	if(m==0) t++;//如果子序列选完了，那么第t个数就不能加入子序列里面，需要t++，因为第t+1个数是可以放进子序列 
	printf("%d\n",n-t);//输出选择的个数 
	return 0;
}
```

---

## 作者：StudyingFather (赞：6)

因为最后放进去的一定是最右边的物品，所以我们可以从右往左直接模拟放物品的过程，一旦放不下直接输出答案即可。时间复杂度为 $ O(n) $。

~~所以为什么这题难度为蓝题啊...感觉从思维难度上最多算个绿题~~
```cpp
#include <stdio.h>
int a[200005];
int main()
{
 int n,m,k;
 scanf("%d%d%d",&n,&m,&k);
 for(int i=n;i>=1;i--)//逆序读入
  scanf("%d",&a[i]);
 int rem=m,used=0;
 for(int i=1;i<=n;i++)//直接模拟放物品的过程
 {
  if(used+a[i]>k)//用新箱子装物品
  {
   rem--,used=a[i];
   if(rem==0)//箱子用尽，输出答案
   {
   	printf("%d\n",i-1);
   	return 0;
   }
  }
  else used+=a[i];
 }
 printf("%d\n",n);
 return 0;
}
```

---

## 作者：fls233666 (赞：5)

题目要求**最多**放入盒子中的物品数量。

我们假设最终答案为 $x$ ，则显然 $x-1$，$x-2$，$x-3$...的方案也是可行的。反之，$x+1$，$x+2$，$x+3$...这些方案是不可行的。

那么可以证明，**此题的答案具有单调性**。

于是，我们开始**二分答案**。

一种简单的二分方案如下：
1. 左边界设为 $0$，右边界设为 $n$；
2. 设 $mid$ 为二分出来的答案，删掉从左边开始的 $mid$ 个物品；
3. 写一个函数用 $O(n)$ 时间算一下装下剩下的所有物品需要的箱子数量，具体可以参考下面的代码；
4. 设上一步计算得到的结果为 $cnt$，如果 $cnt>m$，缩小右边界，反之缩小左边界；
5. 最后答案即为 $n-l$

按照上述方案的代码总时间复杂度为 $O(n\log(n))$。

下面是完整代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 2e5+5;
int g[mxn],nk,m,n,l,r,md;

inline bool ck(int st){  //O(n)检查二分的答案合法性
	int cnt=1,v=0;  //cnt为需要的箱子数量，v为当前箱子已经使用的容积
	for(rgt i=st;i<=n;i++){
		if(v+g[i]>nk){  //装不下就开个新箱子
			cnt++;
			v=g[i];
		}else  //装得下就装进去
			v+=g[i];
	}
	return cnt>m;  //比较，更新二分边界
}

int main(){
	scanf("%d%d%d",&n,&m,&nk);
	for(rgt i=1;i<=n;i++)
		scanf("%d",&g[i]);
                //读入数据
	l=0;
	r=n;
        //二分边界初始化
	while(l<r){
		md=(l+r+1)>>1;
		if(ck(md))  //二分答案
			l=md;
		else
			r=md-1;
	}
    
	printf("%d",n-l);  //输出
	return 0;
}

```


---

## 作者：Xdl_rp (赞：1)

一看 $n \le 2 \times 10^5$ 就知道暴力 $O(n^2)$ 肯定会超时。

定睛一看，看看标签——这不就是二分 $+$ 贪心吗？

但是一想：

- 首先，会从中去除几个物品，让选完后的序列，每一个盒子都尽量装满，因为都尽量装满了，所以就不需要考虑选或者不选了，直接从后往前进行贪心即可。


代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, k;
int a[N];
int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
  //输入
	int x = 0;//装的容量
	for (int i = n; i >= 1; i--) {//倒序
		if (x + a[i] <= k) x += a[i];//如果能装就装
		else {//否则
			m--, x = a[i];//盒子数量减一，重置容量
			if (m == 0) {//如果没盒子了
				cout << n - i;//输出选了的数量
				return 0;//结束
			}
		}
	}
	cout << n;//因为如果全部都有选，循环中不会输出，所以在循环外面直接输出n
	return 0;
}
```


---

## 作者：37Lament (赞：1)

感觉这题挺水的
首先 ：Maksim 先生想把物品装入盒子中。对于每个物品，如果能被放入当前的盒子中，则放入当前盒子，否则换一个新的盒子放入。
其次：Maksim 先生会从左开始扔掉一部分物品

所以我们可以从右边开始遍历物品，而礼物的容量放入一个从小到大的优先队列，从右边开始，每次先判断是否能放入最小容量的礼物盒，如果可以就将容量减去这个礼物的容量并且继续放入队列，计数器 + 1；如果不能放入，直接 pop 礼物盒，此时下一个礼物盒必定是全新礼物盒（全容量）或者没有礼物盒。如果两次都放不进，必定所有礼物盒都放不进去。如果队列为空，说明没有礼物盒可装。这两种情况都直接输出计数器即可。所以代码如下


------------

```cpp
#include "bits/stdc++.h"
#define cin std::ios::sync_with_stdio(false);cin

using namespace std;

const int N=2*10e5+5;
priority_queue<int,vector<int>,greater<int>>k;
int arr[N],a[N];
int main() {
    int n,m,q;
    cin>>n>>m>>q;
    for (int i = 0; i < n; i++) {
        cin>>a[i];
    }
    for (int i = 0; i < m; i++) {
        k.push(q);
    }
    int ans=0;
    for (int i = n-1; i >=0 ; i--) {
        if(k.top()>=a[i]) {int y=k.top();k.pop();k.push(y-a[i]);ans++;}
        else {
            k.pop();if(k.top()>=a[i]){
                int y=k.top();k.pop();k.push(y-a[i]);ans++;
            } else goto gg;
        }
    }
    gg:cout<<ans<<endl;
    return 0;
}
```



---

## 作者：ztz11 (赞：1)

水题。。。

因为他挑选的规则一定,而删除的方式一定，所以，答案拥有单调性。

单调性：因为有一个最大合法点，在那之后都是合法的，所以再往后走的话，答案一定越来越小

所以我们的目的就是找这个最大合法点。

怎么找呢？

因为挑选方式一定，所以合法性可以O(n)验证。

这样的话，很显然就可以用一个东西叫二分答案

二分合法点就好了qwq

## 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rii register int i
#define rij register int j
using namespace std;
int n,m,k;
int a[200005];
bool check(int wz)
{
	int now=0,cnt=1;
	for(rii=wz;i<=n;i++)
	{
		if(a[i]>k)
		{
			return false;
		}
		if(now+a[i]>k)
		{
			now=0;
			cnt++;
		}
		now+=a[i];
	}
	if(cnt>m)
	{
		return false;
	}
	return true;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(rii=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int l=1,r=n;
	while(l<r)
	{
		if(r-l==1)
		{
			if(check(l)==true)
			{
				break;
			}
			else
			{
				if(check(r)==true)
				{
					l=r;
				}
				else
				{
					l=n+1;
				}
				break;
			}
		}
		int mid=(l+r)/2;
		if(check(mid)==true)
		{
			r=mid;
		}
		else
		{
			l=mid;
		}
	}
	printf("%d",n-l+1);
}
```

---

## 作者：AbsMatt (赞：0)

## [题目传送器](https://www.luogu.com.cn/problem/CF1066D)
# 题意
将体积为 $a_i$ 到 $a_n$ 物品放入 $m$ 个盒子，每个盒子容积为 $k$，问 $n-i$ 的最大值。
# 思路
本题使用的是**二分答案**算法，只需要二分 $i_{min}$ 使 $a_i$ 到 $a_n$ 满足情况，最后输出 $n-i$ 即可。

check 函数只要从 $i$ 到 $n$ 遍历一遍即可。
## AC Code
```cpp
#include<bits/stdc++.h>  // 开始
using namespace std;
const int maxn=2e5+10;
int n,m,k,ans=0;
int a[maxn];
bool check(int x){  // check 函数
	int now=0,cnt=1;
	for(int i=x;i<=n;i++){
		if(now+a[i]>k){  // 要新开一个盒子
			now=a[i];
			if(++cnt>m)	return 0;  // 若目前使用的盒子数已超过m就提前退出
		}
		else	now+=a[i];  // 直接在原来的盒子上加
	}
	return (cnt<=m);  // 最后也要检查
}
int main(){
	scanf("%d%d%d",&n,&m,&k);  // 输入
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
	int l=1,r=n;
	while(l<=r){  // 二分答案
		int mid=(l+r)>>1;
		if(check(mid))	r=mid-1;
		else	ans=mid,l=mid+1;
	}
	printf("%d",n-ans);   // 输出
  	return 0;  // 再见
}
```

---

## 作者：miserExist (赞：0)

一篇结合贪心和二分的题解 ~~并不是~~

那么对于这道题目，看到1e5首先出现的想法是二分可以放进盒子中的个数，然后从前往后扫贪心的放入物品。

但这样是不正确的。

因为是从前向后依次可选择地放入，实际上是可以选择不放，并不能够贪心。

那么转换一下思路，我们从后向前贪心就可以满足条件。

因为从前向后放弃放入物品，那么最坏情况下物品都会堆积在后面，从后向前贪心可以避免这种情况 (或者包含了这种最坏情况)。

但仔细一想物品会尽量的往后放这一个性质貌似可以只接贪心

所以实际上并不需要二分 ~~懒得改了~~

详细语句解释在代码中

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int N = 4e5 + 1000, inf = 0x3f3f3f3f;

int a[N];
int n,m,k;

int check(int x)
{
	int cnt = 0, nowlast = k, lastbox = m - 1;
    //cnt 当前放入的个数
    //nowlast 当前盒子剩余的体积
    //lastbox 剩余盒子 刚开始要分给nowlast 一个k的体积 所以要-1
	for(int i = n; i >= 1; i --)
	{
		if(a[i] > k) continue; //大于盒子体积的直接排除
		if(nowlast >= a[i])//目前盒子还有空位
		{
			nowlast -= a[i];
			cnt ++;
		}
		else//盒子没空位
		{
			if(lastbox == 0) return cnt <= x;//没盒子了 后面的直接放弃 加急return
			cnt ++;
			nowlast = k - a[i];//开一个新盒子并且装进去
			lastbox --;
		}
	}
	return cnt <= x;
}
signed main()
{
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	int l = 0, r = 1e9+1e5;
	int ans = 0;
	while(l <= r)
	{
		int mid = l + r >> 1;
		if(check(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	printf("%lld\n", ans);
	
	return 0;
}

```

---

## 作者：phmaprostrate (赞：0)

## 题意分析
有一个序列，选择一段序列必须是后缀，使其总和不超过 $k$ 使得选择的序列中的元素个数最多。

题目要求从左面去掉若干个物品，我们考虑将序列分割成几段用 $a[i]$ 记录第几个子段保证字段和不超过要求，然后从后往前贪心，因为这样就能保证最后贪到的是后缀，如果这样分割时要倒着从最后一个元素开始还是为了保证后缀。

关于为何要倒着分割,举个例子，假如序列最后 $3$ 个元素为 $5,4,3$ 要求一个盒子，容积为 $9$，假如 $5$ 是字段的第一个元素，那么 $3$ 会因超过容积被分到另一个字段中。选择是会选择 $3$ 答案为 $1$,显然，这时让 $3,4$ 在一个盒子里更优。所以要倒着分割。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n,m,k;
int a[N];// 记录子段的长度
int cnt,sum,num,ans;//子段个数，子段和，子段长度
int x[N];
int main(){
    cin >> n >> m >> k;
    for(int i = 1 ; i <= n ; i ++) cin >> x[i];
    //倒着分割子段
    for(int i = n ; i >= 1 ; i --){
    	if(sum + x[i] <= k) sum += x[i],num ++;
    	else a[++cnt] = num,sum = x[i],num = 1;
	}
   a[++cnt] = num;
   for(int i = 1 ; i <= m ; i ++)
     ans += a[i];
     cout << ans;

     return 0;
}
```



---

## 作者：happy_dengziyue (赞：0)

### 1 算法

本题解不需要二分算法，一个个枚举即可，并且时间够用。

### 2 思路

##### 题意

从右到左将物品一个个放进盒子里，**一个盒子里装的物品一定要是连续的，** 求最多能放多少物品。

##### 解题过程

首先，从右到左扫一遍，如果当前物品可以放进当前盒子里，就放进去，否则换一个盒子，原来那个盒子就不用了。

然后，到了没有盒子时，退出循环，当前物品和它左边所有物品都要丢掉。输出即可。

### 3 代码与记录

```cpp
#include<cstdio>
using namespace std;
const int max_n=200000;
int n,m,k;
int a[max_n+2];//物品重量
int b[max_n+2];//盒子
int c;//从右往左取到下标为c的物品
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1066D_1.in","r",stdin);
	freopen("CF1066D_1.out","w",stdout);
	#endif
	//输入
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
	}
	//特判有没有物品重量超过容量的
	for(int i=n;i>=1;--i){
		if(a[i]>k){
			printf("%d\n",n-i);
			return 0;
		}
	}
	//开始程序
	c=n;
	for(int j=1;c>=1;--c){
		if(a[c]+b[j]>k){//这个盒子装不下了
			++j;
			if(j>m){//没有盒子了
				break;//可以退出
			}
		}
		b[j]+=a[c];
	}
	printf("%d\n",n-c);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/problem/CF1066D)

By **dengziyue**

---

## 作者：北极星欧拉56 (赞：0)

```
这道题，典型二分答案
但是，如何二♂分？
我滴思路：
枚举长度
然后从没开始丢掉的部分验算
如果我所用的盒子数比规定盒子数少或等于
那么，我可以判断他是对的
反之则为错的！
如果对，枚举更长的情况
错，枚举更短的情况
然后一波二分+卡常AC
代码：
```
```
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","Os","inline")
#define rnt register int
using namespace std;
int a[200001],c[200001];
int n,m,k,l,r,mid,ans;
inline bool check(int x)
{
	int num=0,tot=1;
	for(rnt i=n-x+1;i<=n;++i)
		if(a[i]+num>k)tot++,num=a[i];
		else num+=a[i];
	if(tot<=m)return true;
	else return false;	
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(rnt i=1;i<=n;++i)scanf("%d",&a[i]);
	l=1,r=n;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid)==true)ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}

---

## 作者：Captain_Paul (赞：0)

来一发通俗易懂的二分题解

直接二分答案

要放$k$个物品就要删掉$n-k$个物品

所以对于一个答案$k$，要放的是$[n-k+1,n]$这$k$个物品

一个一个放，当前盒子能放开就放，放不开就新开一个

~~感觉代码还是比较简短的~~

```
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define reg register
using namespace std;
const int N=2e5+5;
int n,m,V,a[N];
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while (!isdigit(c)&&c!='-') c=getchar();
	if (c=='-') c=getchar(),w=-1;
	while (isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*w;
}
inline bool check(int k)
{
	int res=V,now=1;
	for (int i=n-k+1;i<=n;i++)
	{
		if (res>=a[i]) res-=a[i];
		else ++now,res=V-a[i];
	}
	return now<=m;
}
int main()
{
	n=read(),m=read(),V=read();
	for (reg int i=1;i<=n;a[i++]=read());
	int l=0,r=n,ans=0;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if (check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：star_magic_young (赞：0)

这题为什么要用二分呢?/huaji

首先可以$O(n)$预处理出从某个物品$i$开始放,只放一个盒子,能放的最后物品的位置$j$,只要用两个指针维护左右端点,每次移动一下左端点同时尽量把右端点右移救星了

然后我们要放的所有物品是原来的一个后缀,所以要从后往前放,~~但是直接贪心放是错的~~.考虑构建一棵树,根据前面对每个$i$预处理出的$j$,连$(j+1,i)$的单向边,然后从$n+1$开始dfs,记$n+1$的深度为0,那么我们不能访问深度大于$m$的点.记能访问到最小的点为$y$,答案为$n-y+1$

```cpp
#include<bits/stdc++.h>
#define LL long long
#define il inline
#define re register
#define db double
#define eps (1e-5)

using namespace std;
const int N=200000+10;
il LL rd()
{
    LL x=0,w=1;char ch=0;
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*w;
}
int to[N],nt[N],hd[N],tot=1;
il void add(int x,int y){++tot,to[tot]=y,nt[tot]=hd[x],hd[x]=tot;}
int n,m,k,a[N],ans,tt=-1;
il void dfs(int x)
{
  ++tt;
  ans=max(ans,n-x+1);
  if(tt<m) for(int i=hd[x];i;i=nt[i]) dfs(to[i]);
  --tt;
}

int main()
{
  n=rd(),m=rd(),k=rd();
  for(int i=1;i<=n;i++) a[i]=rd();
  for(int i=1,su=a[1],j=1;i<=n;i++)
    {
      while(j<n&&su+a[j+1]<=k) su+=a[++j];
      add(j+1,i),su-=a[i];
    }
  dfs(n+1);
  printf("%d\n",ans);
  return 0;
}


```



---

