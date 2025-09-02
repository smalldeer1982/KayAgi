# [USACO18JAN] Out of Place B

## 题目背景

本题翻译来自于 deepseek-v3。

## 题目描述

Farmer John 雄心勃勃，计划尝试一件似乎从未顺利过的事情：他想为他的整个牛群拍一张照片。

为了让照片看起来更美观，他希望奶牛们从矮到高排成一行。不幸的是，就在他让奶牛们按这种方式排好队后，总是捣乱的 Bessie 走出了队伍，并重新插入到队伍中的某个位置！

Farmer John 希望通过交换奶牛对的方式让整个牛群重新排好队。请帮助他确定为了实现这一目标，他需要进行的最少交换次数。

## 说明/提示

在这个例子中，Bessie 显然是身高为 $3$ 的奶牛。Farmer John 通过以下三次交换将奶牛们重新排序：

2 4 7 7 9 3 - 原始队伍  
2 4 7 7 3 9 - 交换最后两头奶牛  
2 4 3 7 7 9 - 交换第一个 $7$ 和 $3$  
2 3 4 7 7 9 - 交换 $4$ 和 $3$

## 样例 #1

### 输入

```
6
2
4
7
7
9
3```

### 输出

```
3```

# 题解

## 作者：ikunTLE (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P1698)

### 思路

令 $b$ 为排序后的 $a$。分为 $2$ 种情况：

- 若 $a_i=b_i$，那么无需交换。
- 若 $a_i\neq b_i$，则需要将正确答案交换到 $i$ 的位置上，即多了一次交换。

由于最后一个数交换后会回到正确的位置，所以答案需要 $-1$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=105;
int a[N],b[N];
int main(){
	int n=read();
	for(int i=1;i<=n;++i)
		a[i]=b[i]=read();
	sort(b+1,b+n+1);
	int ans=-1;
	for(int i=1;i<=n;++i)
		ans+=(a[i]!=b[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：okra_S_lotus (赞：6)

首先将原数组 $a$ 排好序，得到一个新的数组 $b$，设 $a$ 和 $b$ 对应位不同的位数为 $ans$，则最终答案为 $ans-1$。证明如下：

首先，显然有这样的策略：从第一位往后枚举，假设当前枚举到了第 $x$ 位，若 $a_x\ne b_x$，则先找到 $a$ 中的另一位 $y$ 使得 $a_y=b_y$，再交换 $a$ 数组的第 $x$ 位与第 $y$ 位，这样便可以令 $a$ 与 $b$ 对应位不同的位数不断减少，直到 $0$。当 $a,b$ 数组的前 $n-1$ 位对应相同时，最后一位自然也就相同了。所以，最终答案不会超过 $ans-1$。

其次，由于 $a$ 数组相当于是在 $b$ 数组的基础上，只将一个数字移动了，所以，除了最后一次将 $a$ 数组的两个元素交换之外，其他的交换都不会出现这样的情况：将 $a$ 数组的第 $x$ 位与第 $y$ 位交换前，$a_x=b_y,a_y=b_x$，也就是交换后，刚好让这两位都还原了。这代表着，最终答案不会低于 $ans-1$。

那么答案便为 $ans-1$。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10000000],b[10000000];
int n,ans;
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
  	cin>>a[i];
	b[i]=a[i];
  }
  sort(b+1,b+n+1);
  for(int i=1;i<=n;i++)
    ans+=(a[i]!=b[i]);
  cout<<ans-1;
}
```

---

## 作者：LookatSea (赞：5)

复制一份数组元素，排一遍序后判断与复制数组有几个不同的即可。注意答案要减一。

证明：假设有 $x$ 个与复制数组不同的数，那么选择一个数进行操作，每次需要一次操作，最后一个数交换可以使两个数回到原位，所以最后会进行 $x-1$ 个操作。

AC CODE：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[114514]={0},b[114514]={0},ans=0,n;
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];//输入
    }
    for(int i=1;i<=n;i++){
        b[i]=a[i];//复制a数组b
    }
    sort(a+1,a+n+1);//sort排序
    for(int i=1;i<=n;i++){
        if(a[i]!=b[i]){//不相等加一
            ans++;
        }
    }
    cout<<ans-1;
    return 0;
}
```

若代码有什么不足的地方欢迎指出。

---

## 作者：__UrFnr__ (赞：3)

题目分析：求几次能把一个数组重新从小到大排序（遇到相同的可以跳过）

题目思路：可以建立两个数组，一个表示原数组，另一个表示排好序的数组，找出不同的将答案累加，最后减一并输出即可（减一是因为最后一个数交换会使两个数回到原位）。

AC Code：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[110], b[110], ans;
int main () {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        b[i] = a[i];//将数组a复制
    }
    sort (a + 1, a + n + 1);//排序
    for (int i = 1; i <= n; i ++) {
        if (a[i] != b[i]) ans ++;//原数组与排序后的数组的每个元素进行判断是否不相同，不相同时累加答案。
    }
    cout << ans - 1;//将答案减一后输出
}
```

---

## 作者：dctc1494 (赞：2)

洛谷 P1698

[题目传送门](https://www.luogu.com.cn/problem/P1698)

### 题目概述

给定一个单调递增的序列，其中有一个元素改变了位置，要通过左右交换元素将序列还原。

### 思路

我们可以通过排序后的序列与原始的序列进行比较，判断是否进行过交换，若进行过交换则记录，最后计算交换次数。

### AC Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n, ans, a[N], b[N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];  // 复制
    }
    sort(b + 1, b + n + 1);  // 排序
    for (int i = 1; i <= n; ++i) {  // 比较序列
        if (a[i] != b[i]) {  // 若不一样就是进行过交换
            ++ans;
        }
    }
    cout << ans - 1 << endl;  // 输出答案，要 -1，因为 n 个数位置不同只交换过 n - 1 次
    return 0;
}
```

---

## 作者：OIratrace (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P1698)

## 题意
给定一个单调递增的序列，其中有一个元素改变了位置，要通过左右**交换**元素将序列还原。

### 注意
如果在交换时遇到**相同**元素可以直接跳过。

---

## 思路
这题可以先 $O(n)$ 遍历序列，找到破坏单调递增的元素，先记录下它的**位置**和交换**方向**。

然后可以在序列上找到这个元素原本的位置，计算出到达这个位置所需的代价。

### 优化
这里也可以通过去重构造出一个新的序列，通过**二分**在新序列中找到元素的位置，然后计算它的代价，我就不写这段代码了。

---

## 完整代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int a[105];
map<int,int>f;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}
	int h=0,dir=0;
	a[n+1]=1e9+5,a[0]=-1e9-5;//这里设置边界，以防找到边界上的数导致出错
	for (int i=1;i<n;i++){
		if (a[i]>a[i+1]){
			if (a[i+1]<a[i-1]){
				h=i+1;
				dir=0;
			}
			if (a[i]>a[i+2]){
				h=i;
				dir=1;
			}
			break;
		}
	}
	if (dir==0){
		for (int i=h-1;i>=1;i--){//暴力遍历
			if (a[i]>a[h]&&f[a[i]]==0){
				f[a[i]]=1;
				ans++;
			}
		}
	}
	else{
		for (int i=h+1;i<=n;i++){//暴力遍历
			if (a[i]<a[h]&&f[a[i]]==0){
				f[a[i]]=1;
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：qw1234321 (赞：2)

这里提供两种做法，AcWing 上亲测可过：

1. 暴力。

首先找到 bessie 的位置，记为 bessie，然后找到她需要插入的位置，记为 ins，然后看 bessie 和 ins 的大小关系，从小到大循环遍历一下，输出遍历的区间不同的数的个数即可。

贴个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1000005;
int n, a[N], bessie, buc[N], ins, vis[N];

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++){
        if ((a[i - 1] <= a[i] && a[i] > a[i + 1] && a[i - 1] <= a[i + 1]) || (a[i - 1] > a[i])){
            bessie = i;
            break;
        }
    }
    for (int i = bessie - 1; i >= 1; i--){
        if (a[i] <= a[bessie] && a[bessie] <= a[i + 1]){
            ins = i + 1;
            break;
        }
    }
    int t = ins;
    if (t == bessie){
        for (int i = bessie + 1; i <= n; i++){
            if (a[i] <= a[bessie] && a[bessie] <= a[i + 1]){
                ins = i;
                break;
            }
        }
    }
    else{
        int ans = 0;
        for (int i = ins; i <= bessie - 1; i++){
            vis[a[i]] = 1;
        }
        for (int i = 1; i <= 1000000; i++){
            ans += vis[i];
        }
        cout << ans;
        return 0;
    }
    int ans = 0;
    for (int i = bessie + 1; i <= ins; i++){
        vis[a[i]] = 1;
    }
    for (int i = 1; i <= 1000000; i++){
        ans += vis[i];
    }
    cout << ans;
    return 0;
}
```

2. 排序。

将原序列排序，直接输出和原序列对应位置的数不同的数的个数减一即可。

贴个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[100010], b[100010];

int main(){
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++){
    	cin >> a[i];
		b[i] = a[i];
	}
    sort(b + 1, b + n + 1);
    int ans = -1;
    for (int i = 1; i <= n; i++){
        if (a[i] != b[i]) ans++;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：cff_0102 (赞：2)

可以证明，此题的正确答案就是在原序列（即排序后的现序列）和现序列中对应数字不同的位置的个数再减一。

设在原序列和现序列中对应数字不同的位置的个数为 $k$，可以先证明答案不小于 $k-1$，再证明答案可以是 $k-1$，两者结合一下就能推出答案必定为 $k-1$。

证明答案不小于 $k-1$：

根据题面，可以发现，这个对原序列的改动实际上可以看成 $a$ 序列中第 $k+1$ 到第 $i$ 个（或第 $k-1$ 到第 $i+1$ 个）数全体向第 $k$ 的位置的方向平移 $1$ 格，然后将原本第 $k$ 个位置的数放到那个空缺中。也就是说，新序列被改变的数中 $a_x$ 的原位置应为 $x+1$（或 $x-1$），除非它的原位置是 $k$。那么，此时无论交换哪两个数，最多只能使一个数回到原位，到最后只剩下两个位置调换的情况可以一次操作使两个数回到原位的情况除外。那么答案就不小于 $k-1$。

证明有 $k-1$ 次对换的操作：

随便选择一个被移动的数，让它和原本它应该在的位置上的数对换（此时它应该和相邻的数交换，或者从所有被移动的数的一头一道另一头），然后再对这个被交换到这个位置的数继续进行这样的操作，每次进行操作都一定可以使得一个数回到原位，而最后一次操作能使两个数回到原位，所以这样操作的答案是 $k-1$。

因此，此题的答案必然为 $k-1$。具体实现时，只要将序列排序，然后逐位进行比较，得到不一样的位置的个数 $k$，那答案就是 $k-1$ 了。

---

## 作者：QingDeng_Star (赞：1)

## 思路
这道题其实肥肠肥肠简单，观察样例就可以知道：把原数组  $a$ 复制一个，然后把复制出来的数组 $b$ 排个序，最后一个个比对，有不同的计数器就加 $1$，特别注意，计算结束后，计数器要减 $1$。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005];
int main()
{
	int n,ans=0;
  	cin>>n;
  	for(int i=1;i<=n;i++)
  	{
	  	cin>>a[i];
		b[i]=a[i];
  	}
  	sort(b+1,b+n+1);//这里的排序，也可以是 a 数组来
  	for(int i=1;i<=n;i++)
    	if(a[i]!=b[i])
    	    ans++;
  	cout<<ans-1<<endl;//记得要减一！
  	return 0;//完结散花！
}
```

---

## 作者：Genshin_ZFYX (赞：1)

移动的数要么往左移，要么往右移。

假设原队列是这样的：
$$
1,2,3,4,5,6
$$
假设被移动的是 $3$,它往左移 $2$ 格移到了 $6$ 前面，那么队列应该是这样的：
$$
1,2,4,5,3,6
$$
它需要往左再移 $2$ 格回来，对于其他的情况也类似如此。也就是说，我们的答案就是这个数移动的步数。至于步数怎么求，那就是原队列（及现队列排完序后的队列）和现队列中对应数字不同的数的个数 $-1$。

AC 代码：

```
#include<bits/stdc++.h>
using namespace std;
int a[10005],b[10005]; 
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n,ans=0;cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)ans+=(a[i]==b[i]?0:1);
    cout<<ans-1;
	return 0;
}

```

---

## 作者：G1yu (赞：1)

# 题解 [P1698 \[USACO18JAN\] Out of Place B](https://www.luogu.com.cn/problem/P1698)

## 题意

给定一个单调递增序列 $a$，有一个元素 $a_k$ 被插入了序列头部，尾部或中间，替换掉原有元素，你可以交换 $a_i$ 与 $a_j$ 任意次，输出能让该序列重新单调递增的最少交换次数。

## 思路

这道题的思路很简单，注重排序后的 $a$ 序列和原 $a$ 序列元素中的不同值的个数即可。答案就是不同值个数加上一。

## 证明

设原 $a$ 序列与排序后的序列的不同元素有 $x$ 个。对于每次操作，我们能将一个不同元素放置至它排序后的位置。而当只有 $2$ 个元素与排序后序列不同时，一次操作就可以完成。使用答案为 $x-1$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e2+4;
int a[N],b[N]; //a序列：如题，b序列：排序后a序列
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); 
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	
	memcpy(b,a,sizeof a); //将a序列的元素复制到b序列中
	sort(b+1,b+n+1); //排序
	int ans = 0;
	for(int i=1;i<=n;i++){
		if(b[i] != a[i]) ans ++; //统计不同 
	}
	cout<<ans-1;//见证明
	return 0;
}
```

---

## 作者：Mason123456 (赞：1)

## P1698

—— 来自洛谷首 A 的题解（笑）

### 题目翻译

农场主约翰雄心勃勃，打算尝试一件似乎永远不会成功的事情：他想给他的全部牛群拍一张照片。

为了让照片看起来漂亮，他想让牛群从矮到高排成一排。不幸的是，就在他让奶牛们这样**排好队**后，总是惹麻烦的奶牛贝西却走出了队列，重新站到了队列的另一个位置上！

约翰农场主想把**几对奶牛**调换一下，让整个牛群重新排好队。请帮助他确定，为了实现这个目标，他**至少**需要调换多少**对**奶牛。

### 思路

第一眼：冒泡。

第二眼：数据错了？

第三眼：好吧，不是冒泡，但是和冒泡差不多。

我们发现，只有 Bessie 的位置是错的，也是题目直接告诉我们的。所以，如果是冒泡，即只交换相邻的话，Bessie 到她应该在的位置的距离是非常好求的。可是题面要求是交换一对，所以当有**一段数的值相同**时，我们就可以跳过了！

最终答案就是**排序后**的数组 $a$ 与**排序前**的数组 $b$ 中，$b_i \ne a_i$ 时的情况 $-1$​（减去奶牛 Bessie）。

时间复杂度：$O(n\times \log n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int a[N], b[N];
int n;
int main(){
	cin>>n;
	for(int i = 1;i <= n;i++){
		cin>>a[i];
		b[i] = a[i];
	}
	sort(a+1,a+n+1);
	int ans = -1;
	for(int i = 1;i <= n;i++){
		if(a[i] != b[i])	ans++;
	}
	if(ans == -1)	cout<<0;// Bessie太听话的情况
	
	else cout<<ans;
} 
```

---

## 作者：furina_1013 (赞：0)

### 题意解读：
有一个单调递增的数列，在任意位置插入了一个数（保证破坏单调性），问将这个数与前一位数字调换位置，
最少多少次可以维护单调性？

### 思路（推荐）：

 $fu_i$ 表示长度为 $n$ 的序列的第 $i$ 位
 
用$fu2_i$ 对照原数组，同时 $fu2_i = fu_i$
将对照数组从小到大排序。


循环 $n$ 次，找两个数组的不同（每一个不同都代表了调换一次位置），最后结果 -1 即可。

 code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int fu2[105];
int fu[105];
int ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>fu[i];
		fu2[i]=fu[i];
	}
	sort(fu2+1,fu2+n+1);
	for(int i=1;i<=n;i++)
	{
		if(fu[i]!=fu2[i])ans++;
	}
	cout<<ans-1;
	return 0;
}
/*1 3 3 2
cnt=4
cha=2
swap(fu[cnt],fu[cnt-cha])
ans=1;

1 2 3 3*/

```

### 思路二（不推荐 ）：暴力更改

创建一个桶，存储出现了多少次
用 $cnt$ 表示破坏单调性的数的位置。

每一次更改时判断：

```cpp
for(;;)
	{
		if(fu[cnt]>fu[cnt-1])break;
		int cha=tong[fu[cnt-1]];
		int furina=fu[cnt];
		fu[cnt]=fu[cnt-cha];
		fu[cnt-cha]=furina;
		cnt-=cha;
		ans++;
	}
```
输入时统计 $tong$，并找到 $cnt$ 即可。

---

## 作者：XiaoWhy (赞：0)

提供一个不同的思路

因为题目的限制，只有一个数移动了，移动的数记为 $a_{pos}$ ，可以发现 $[1,pos-1]$ 和 $[pos+1,n]$ 这两个区间都是有序的，且 $a_{pos-1} \leq a_{pos+1}$，因此 $a_{pos}$ 肯定只会朝着某一个方向交换。

交换过程中我们可以发现，如果一个连续段都是同一个数，我们肯定是直接跟端点位置交换，这样明显是最优的。因此我们首先将输入的 $a$ 数组中连续一段相同数的区间合并，看作一个数，此时我们其实就可以发现，交换次数就等于冒泡排序的交换次数。


**Code**

```cpp
#include <iostream>
using namespace std;
const int N=105;
int a[N];
int main()
{
	int n,cnt=0,m=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(x==a[m]) continue;//连续相同的一段只保留一个数
		a[++m]=x;
	}
	for(int i=1;i<=m;i++)//交换次数等于冒泡排序的交换次数
	{
		for(int j=1;j<=m;j++)
		{
			if(a[j]<a[j-1]) swap(a[j],a[j-1]),cnt++;
		}
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：wangzc2012 (赞：0)

# P1698 [USACO18JAN] Out of Place B
## 题意概括
给定一个长度为 $n$ 的序列 $a$，求经过多少次交换元素的操作后，序列变为单调递增序列。
## 思路分析、算法实现
先将序列 $a$ 复制一次，存入 $b$ 中，然后将 $b$ 进行从小到大排序，接着进行遍历，当 $a _ {i} \ne b _ {i}$ 时，意味着 $a _ {i}$ 需要被交换，所以答案加 $1$。当遍历完成后，输出答案即可。    
但是！！！不出意外的话马上就要出意外了！我们还需要特殊考虑最后一次交换的情况。在最后一次交换中，可以一次性将两个元素交换，所以事实上最后一个需要被交换位置的元素可以与它前面的元素一起被交换，因此，答案在输出前需要减 $1$！
## AC Code
代码有点丑，请谅解。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],b[105],ans;
int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    for (int i=1;i<=n;i++){
        if (a[i]!=b[i]) ans++;
    }
    if (ans==0) cout<<0;
    else cout<<ans-1;
    return 0;
}
```
最后，附上AC记录：
![](https://cdn.luogu.com.cn/upload/image_hosting/nzx1xyhm.png)

---

## 作者：AnOIer (赞：0)

## 简化题意

如果有 $m$ 个与排序后的数列不同的数，那么选择一个数进行操作，每次需要一次操作，最后一次交换可以使两个数回到原来位置，所以一共会进行 $m-1$ 个操作。

题意简化为：

输入一个数列 $a_n$，将 $a_n$ 排序后，直接输出与原来的数列对应位置不同的数的数量再减去 $1$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],b[N];
int main(){
	int n,cnt=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];//复制 
	}
	sort(a+1,a+1+n);//排序 
	for(int i=1;i<=n;i++)
		if(a[i]!=b[i]) cnt++;
	cout<<cnt-1;
	return 0;
}

```

---

## 作者：Quartz_Blocks (赞：0)

# P1698 [USACO18JAN] Out of Place B 题解

这题可以理解为**特殊的冒泡排序**，我用 $O(n)$ 的复杂度 AC 了这一题。

在此奉上我的思路（代码里也有）：

1. 找到 Bessie 的位置，存储在 pos 里。
2. 特判数组是否已经有序（Bessie 很乖的时候）。
3. 分类统计 Bessie 与他应当在的位置有多远的距离。  此处注意一点：此处需要注意的是如果寻找时发现了相同的值不需要计入，因为可以直接与更近的那个相同的值交换。


```

#include <bits/stdc++.h>
using namespace std;
int n,a[110];

int main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
	}
	int pos = -1;// -1 是为了防止 Bessie 很乖
	for (int i = 1; i <= n; i++){
		if ((a[i-1] <= a[i] && a[i] > a[i+1] && a[i-1] <= a[i+1]) || (a[i-1] > a[i])){
			pos = i;// 发现 Bessie
			break;
		}
	}
	if(pos == -1){// Bessie 真的很乖
		cout << 0;
		return 0;
	}
	if(a[pos-1] > a[pos]){// Bessie 应该在前面
		int i = pos-1;
		int cnt = 0;
		while(a[i] > a[pos]){
			if(a[i] != a[i+1]) cnt++;//防止多交换
			i--;
		}
		cout << cnt;
	}else{// Bessie 应该在后面
		int i = pos+1;
		int cnt = 0;
		while(a[i] < a[pos]){
			if(a[i] != a[i+1]) cnt++;//同上
			i++;
		}
		cout << cnt;
	}
	
	return 0;
}
```

---

## 作者：imsbNR (赞：0)

# 题解：P1698 [USACO18JAN] Out of Place B

## 思路

对于 $a$ 数列中的第 $i$ 项称为 $a_i$ 并使另一个数列 $b$ 的 $b_i = a_i$ 的处理。

将 $a$ 从小到大排序后依次比较，如果 $a_i \ne b_i$ 的话，答案加一。

最后，答案减一就可以了。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[105], b[105], ans = -1;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i], b[i] = a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		ans += (a[i] != b[i]);
	cout << ans << '\n';
	return 0;
}
```

---

