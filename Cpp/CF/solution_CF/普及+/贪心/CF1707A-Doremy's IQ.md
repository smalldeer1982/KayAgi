# Doremy's IQ

## 题目描述

哆来咪·苏伊特参加了 $n$ 场比赛。 比赛 $i$ 只能在第 $i$ 天进行。比赛 $i$ 的难度为 $a_i$。最初，哆来咪的 IQ 为 $q$ 。 在第 $i$ 天，哆来咪将选择是否参加比赛 i。只有当她当前的 IQ 大于 $0$ 时，她才能参加比赛。

如果哆来咪选择在第 $i$ 天参加比赛 $i$，则会发生以下情况：
- 如果 $a_i>q$，哆来咪会觉得自己不够聪明，所以 $q$ 将会减 $1$；
- 否则，什么都不会改变。

如果她选择不参加比赛，一切都不会改变。哆来咪想参加尽可能多的比赛。请给哆来咪一个解决方案。

## 说明/提示

在第一个测试用例中，哆来咪参加了唯一的比赛。她的 IQ 没有下降。

在第二个测试用例中，哆来咪参加了两个比赛。在参加比赛 $2$ 后，她的 IQ 下降了 $1$。

在第三个测试用例中，哆来咪参加了比赛 $1$ 和比赛 $2$。她的 IQ 在参加比赛 $2$ 后降至 $0$，因此她无法参加比赛 $3$。

## 样例 #1

### 输入

```
5
1 1
1
2 1
1 2
3 1
1 2 1
4 2
1 4 3 1
5 2
5 1 2 4 3```

### 输出

```
1
11
110
1110
01111```

# 题解

## 作者：happy_dengziyue (赞：19)

### 1 视频题解

![](bilibili:BV1eB4y1Y7ZV)

### 2 思路

我们可以发现，尽可能将扣智商的操作留到后面即可。

因为，如果存在一个解，使得参加一场扣智商的竞赛（设为第 $x$ 竞赛）之后有一场竞赛不参加（设为第 $y$ 竞赛）。那么不参加第 $x$ 竞赛但是参加第 $y$ 竞赛肯定是可以的。

那么我们可以设 $x(0\le x\le n)$，使得 $1$ 到 $x$ 场竞赛只做不扣之上的竞赛，$x+1$ 到 $n$ 场竞赛什么都做。然后看看智商是否够用。

二分出满足要求的最小的 $x$，然后再模拟一遍，得出答案。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100000
int t;
int n;
int q;
int a[max_n+2];
int pos;
bool ans[max_n+2];
bool check(int x){
	int w=q;
	for(int i=x+1;i<=n;++i){
		if(a[i]>w)--w;
	}
	return w>=0;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1708C_1.in","r",stdin);
	freopen("CF1708C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		for(int l=0,r=n,mid;l<=r;){//从1到mid只做好题，从mid+1到n啥题都做
			mid=(l+r)>>1;
			if(check(mid)){
				pos=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		for(int i=1;i<=pos;++i){
			if(a[i]<=q)ans[i]=true;
			else ans[i]=false;
		}
		for(int i=pos+1;i<=n;++i)ans[i]=true;
		for(int i=1;i<=n;++i)printf("%d",ans[i]);
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80119356)

By **dengziyue**

---

## 作者：tanghairong (赞：9)

## 题意

其实可以这么想（我认为简单一些）：

你有n场比赛要打，第 $i$ 场比赛的时间为 $i$，难度为 $a_i$。

你一开始智商为 $0$（~~不要惊讶~~）

每打一场你觉得难的比赛，你的智商就能加 $1$，否则就不加

你的智商的上限为 $q$，请问你最多能够打多少场比赛？

## 变量解释

$num$：目前拥有的智商（从 $0$ 开始加的）

$pos$：第一次扣智商的位置（即倒着扫扫到 $num$ 等于 $q$ 的位置）


## 思路

按照上面的题意理解的话就很明了了。

从n往1枚举，若当前比赛难度 $a_i$ 大于目前拥有的智商 $num$，则把 $num$ 加 $1$。

若 $num$ 等于 $q$ 了（达到上限了），记录下位置 $pos$，然后 $break$

最后看一看，在 $pos$ 之前（不含）的比赛只有$\leq q$ 的才参加，在 $pos$ 之后（含）的比赛全部参加，输出即可。

## 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[100005],ans[100005];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;
        memset(ans,0,sizeof(ans));
        for(int i=1;i<=n;i++)cin>>a[i];
        int num=0,pos=0;
        for(int i=n;i>0;i--){
            if(a[i]>num)num++;
            if(num==q){pos=i;break;}
        }
        for(int i=1;i<pos;i++){if(a[i]<=q)ans[i]=1;}
        for(int i=pos;i<=n;i++)ans[i]=1;
        for(int i=1;i<=n;i++)cout<<ans[i];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：wzy2021 (赞：7)

首先用一张图引出思路，

![](https://cdn.luogu.com.cn/upload/image_hosting/qklss494.png)

由上图的调整方法可以知道，存在一种最优方案，

使得在此方案中第一个让 Doremy 的 IQ 减 $1$ 的比赛 $i$，比赛 $j(i \leq j \leq n)$ 都选择了。

所以从后往前考虑，后 $i$ 个全选所需要的最小代价。

若当前考虑的 $i$ 所需要的代价等于 $q$ (Doremy 的原本 IQ)，

那么答案的组成有两部分：

1. $[i, n]$ 全选。

1. $[1, i - 1]$ 中比赛难度 $\leq q$ 都选。

~~~cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;

int a[N], vis[N];

int main() {
	int T; scanf ("%d", &T);
	while (T--){
		int n, q; scanf ("%d%d", &n, &q);
		for (int i = 1; i <= n; ++i) scanf ("%d", &a[i]);
		for (int i = 1; i <= n; ++i) vis[i] = 0;
		int t = 0, now = n;
		while (now >= 1 && t < q) {
			if (a[now] > t) ++t;
			vis[now] = 1; now --;
		}
		for (int i = now; i >= 1; --i) {
			if (a[i] <= q) vis[i] = 1;
		}
		for (int i = 1; i <= n; ++i) printf ("%d", vis[i]);
		printf ("\n");
	}
	return 0;
}
~~~

---

## 作者：Jeremiahy (赞：4)

# 分析

很容易想到一个贪心策略：优先让智商在后面扣（倒着扣智商）。因为如果在前面扣了，后面不用扣的考试可能就要扣了，而后面扣不影响前面的，所以拖得越晚越好。

所以就倒着扣智商，将能考的都考了，直到智商扣完或者考试都没了就停止，然后将前面难度小于等于 $q$ 的考试变为参加中。

具体来说，我们倒着遍历考试，设已扣的智商为 $num$，初始 $num$ 为 $0$。当 $num$ 达到 $q$ 或者没试可考就停止，接着从停止的位置向前，将难度小于等于 $q$ 的考试改为参加。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, q, num, r;//r 为遍历时所用指针 
int a[100010], v[100010];//v 数组记录每场考试是否参加 
signed main() {
	cin >> T;
	while (T--) {
		memset(v, 0, sizeof(v));//初始化为全不参加 
		cin >> n >> q;
		for (int i = 1; i <= n; i++) 
			cin >> a[i];
		for (num = 0, r = n; r >= 1 && num < q; v[r] = 1, r--)//初始化+终止条件+参加考试和指针向前 
			if (a[r] > num)//如果需要扣智商 
				num++;//那就扣 
		for (int i = r; i >= 1; i--)
			if (a[i] <= q) 
				v[i] = 1;//将小于等于 q 的考试设为参加 
		for (int i = 1; i <= n; i++) 
			cout << v[i];
		puts("");
	}
	return 0;
}
```


---

## 作者：MH_SLC (赞：2)

## 题目大意
一个人的 IQ（智商）为 $q$，有 $n$ 场比赛，第 $i$ 天只能参加第 $i$ 场比赛，如果比赛难度大于 IQ，那么 IQ 就会下降，如果 IQ 为 $0$ 就不能参加比赛了，问最多能参加多少场比赛？输入一个 $01$ 串，$0$ 表示不参加，$1$ 表示参加。
## 题目分析
这道题明显是一道贪心题，如果最后一场比赛结束的时候 IQ 刚好为 $0$，那么我们参加的比赛数是最多的，所以我们可以倒着往前推来求解（解释如下）：

若当前的 $q$ 小于 $a_i$，那么我们就让当前的 $q$ 加 $1$，那么这样子是我们后面的比赛都能参加的最优解。
 ## AC Code
 ```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int MAX = 1000010;
inline int read() {
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}
int a[MAX], vis[MAX], t = read();
int main() {
	while (t--) {
		int n = read(), q = read();
		for (int i = 0; i < n; i++)a[i] = read(), vis[i] = 0;
		int k = 0;
		for (int i = n - 1; i >= 0; i--) {
			if (k >= a[i])vis[i] = 1;
			else if (k < q) vis[i] = 1, k++;
			else if (k > q) break;
		}
		for (int i = 0; i < n; i++)cout << vis[i];
		puts("");
	}
	return 0;
}
```


---

## 作者：xyloph0nex17 (赞：1)

正着考虑发现不太好搞，考虑反推。  
设开始时智商为 $Q$，此时的智商为 $q$，答案为 $ans$，并将 $q$ 的初值设为 $0$，从后往前依次考虑：  
情况 $1$：若 $a_i < q$ 且 $q < Q$，则 $ans \leftarrow ans + 1$，$q \leftarrow q + 1$。（正向则为减智商参加的情况）。  
情况 $2$：若 $a_i > q$ 且 $q \geq Q$，则不做出改变。（正向则为选不了的情况）。  
情况 $3$：若 $a_i \geq q$，则 $ans \leftarrow ans + 1$。（正向则为不减智商参加的情况）。  
尝试验证其正确性：  
可以发现我们按照以上规则能够使：
1. 情况 $3$ 的个数尽可能多（在保证是最优解的情况下 $q$ 的增速最快）。
2. 同时确保了没有浪费 $Q$（初值为 $0$）。  
若 $q$ 最后没有达到 $Q$，则说明初值为 $q$ 时已经能够参加 $n$ 场，又因为 $Q>q$，则一定也能参加 $n$ 场，因此按以上规则反推即可。  
时间复杂度 $O(n)$。  

### code
```cpp
int T,n,q,a[N],ans[N] ;
int sum[2] ;
signed main(){
	read(T) ;
	while(T--){
		read(n),read(q) ;
		for(ri i = 1 ; i <= n ; i++)read(a[i]),ans[i]=0 ;
		int cur = 0 ;
		for(ri i = n ; i >= 1 ; i--){
			if(cur < a[i]){
				if(cur < q)cur++,ans[i]=1 ;
			}
			else ans[i] = 1 ;
		}
		for(ri i = 1 ; i <= n ; i++)cout<<ans[i] ;
		cout<<endl ;
	}
	return 0 ;
}
```

---

## 作者：wpy233 (赞：1)

注意到题目描述中有这样一句话： **如果不选比赛，什么都不会改变。** 这实际上暗示我们不必过早做出选择。

考虑到此处 IQ 的损耗对不同比赛来说相同，那么 IQ 肯定是要尽量用完并用到 $ a_i >q $ 的比赛上去的。

对于这部分损耗的 IQ ，早损耗显然不如晚损耗来得好：设想你在决定不参加一场 $a_i >q $ 的比赛之前参加了一场 $a_i >q $ 的比赛，那么把这两个决定交换一下一定是更好的选择：因为这样有更多的可能参加那些 $a_i <q$ 的比赛。

因此可以想到一个贪心思路：将所有的比赛分为两个部分。第一部分的比赛，若参加后会降 IQ 则一律不参加；从第二部分开始连续参加比赛，直到最后 IQ 恰好降为 $0$。

你也可以感性地去理解这个贪心：~~第一部分不参加降 IQ 的比赛为日后更好参与水赛奠定了基础。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int a[100005];
int main()
{
	cin>>t;//注意多组数据
	while(t--)
	{
		int n,q;
		cin>>n>>q;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);//输入a[i]
		int k=n,qq=0;
		while(k>0)
		{
			if(a[k]>qq)
				if(qq==q)
					break;
				else	
					qq++;
			k--;
		}//从后往前判断。找出能参加的第二部分比赛最大数
		int kk=k+1;
		for(int i=1;i<=k;i++)
			a[i]>q ? printf("%d",0) : printf("%d",1) ;//对第一部分做判断
		while(kk<=n)
		{
			printf("%d",1);
			kk++;
		}//第二部分比赛全部参加，因此全部输出1就好
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：0)

### $1.$ 本题算法&本题思路分析

本题是一个贪心题。乍一看好像很难。（这个蒟蒻想到了 $dp$）

考虑到如果从前往后，也就是正着考虑的话，是有后效性的。所以我们从后往前考虑就不会那么难了。

### $2.$ 具体算法实现

第一步，从后往前考虑，设扣的智商为 $k$，对于每一个考试，要扣就扣，如果不用扣就不扣，然后将所有能参加的考试的状态都改为 $1$。

第二步，将所有比 $q$ 小的数的状态都设为 $q$ 。

对于第二步的解释：因为我们是从后往前考虑的，所以需要将本来就不需要扣的状态也设为 $1$。

第三步，输出状态。

对于第三步的备注：**不要输出空格，输出完了要空行。**

###  $3.$ 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010];
int f[100010];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(f,0,sizeof(f));
		int n,q;
		cin>>n>>q;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int num=0,i=n;i>=1&&num<q;f[i]=1,i--)
		{
			if(a[i]>num)
			{
				num++;
			}
		}
		for(int i=n;i>=1;i--)
		{
			if(a[i]<=q)
			{
				f[i]=1;
			}
		}
		for(int i=1;i<=n;i++)
		{
			cout<<f[i];
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

题目传送门：[CF1707A](https://www.luogu.com.cn/problem/CF1707A)
# 思路
我们观察一下题目可以发现：这道题是有后效性的，即扣后面的智商不影响前面的比赛成绩，所以很容易想到一个贪心的策略：既然扣后面的智商不影响前面的，那我们可以先倒着遍历一遍，把能扣的智商都扣掉，直到智商小于 $q$ 或者没有比赛了就停止遍历，然后再从前面遍历，把能打的比赛都打掉，这就是本题的最优策略。
附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1000;
int a[N];
bool vis[N];
int T,n,q;
int main() {
	cin>>T;
	while(T--){//多组数据
		cin>>n>>q;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)vis[i]=false;//默认不打比赛
		int tmp=0,cur=n;
		while(cur&&tmp<q){//循环终止条件
			if(a[cur]>tmp){
				++tmp;//从后往前遍历，智商大于q时继续打（太卷了）
			}
			vis[cur]=true;//标记，表示他打了这场比赛
			cur--;//光标移动到下一场比赛
		}
		for(int i=cur;i>=1;i--){
			if(a[i]<=q)vis[i]=true;//从前面开始遍历，将能打的打掉。
		}
		for(int i=1;i<=n;i++)cout<<vis[i];//输出状态
		cout<<endl;
	}
	return 0;
}
```


---

