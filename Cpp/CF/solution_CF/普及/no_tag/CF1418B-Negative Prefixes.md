# Negative Prefixes

## 题目描述

You are given an array $ a $ , consisting of $ n $ integers.

Each position $ i $ ( $ 1 \le i \le n $ ) of the array is either locked or unlocked. You can take the values on the unlocked positions, rearrange them in any order and place them back into the unlocked positions. You are not allowed to remove any values, add the new ones or rearrange the values on the locked positions. You are allowed to leave the values in the same order as they were.

For example, let $ a = [-1, 1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}] $ , the underlined positions are locked. You can obtain the following arrays:

- $ [-1, 1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}] $ ;
- $ [-4, -1, \underline{3}, 2, \underline{-2}, 1, 1, \underline{0}] $ ;
- $ [1, -1, \underline{3}, 2, \underline{-2}, 1, -4, \underline{0}] $ ;
- $ [1, 2, \underline{3}, -1, \underline{-2}, -4, 1, \underline{0}] $ ;
- and some others.

Let $ p $ be a sequence of prefix sums of the array $ a $ after the rearrangement. So $ p_1 = a_1 $ , $ p_2 = a_1 + a_2 $ , $ p_3 = a_1 + a_2 + a_3 $ , $ \dots $ , $ p_n = a_1 + a_2 + \dots + a_n $ .

Let $ k $ be the maximum $ j $ ( $ 1 \le j \le n $ ) such that $ p_j < 0 $ . If there are no $ j $ such that $ p_j < 0 $ , then $ k = 0 $ .

Your goal is to rearrange the values in such a way that $ k $ is minimum possible.

Output the array $ a $ after the rearrangement such that the value $ k $ for it is minimum possible. If there are multiple answers then print any of them.

## 说明/提示

In the first testcase you can rearrange all values however you want but any arrangement will result in $ k = 0 $ . For example, for an arrangement $ [1, 2, 3] $ , $ p=[1, 3, 6] $ , so there are no $ j $ such that $ p_j < 0 $ . Thus, $ k = 0 $ .

In the second testcase you are not allowed to rearrange any elements. Thus, the printed array should be exactly the same as the initial one.

In the third testcase the prefix sums for the printed array are $ p = [-8, -14, -13, -9, -5, 2, 0] $ . The maximum $ j $ is $ 5 $ , thus $ k = 5 $ . There are no arrangements such that $ k < 5 $ .

In the fourth testcase $ p = [-4, -4, -3, 3, 6] $ .

In the fifth testcase $ p = [-1, 3, 10, 2, 12, 11] $ .

## 样例 #1

### 输入

```
5
3
1 3 2
0 0 0
4
2 -3 4 -1
1 1 1 1
7
-8 4 -2 -6 4 7 1
1 0 0 0 1 1 0
5
0 1 -4 6 3
0 0 0 1 1
6
-1 7 10 4 -8 -1
1 0 0 0 0 1```

### 输出

```
1 2 3
2 -3 4 -1
-8 -6 1 4 4 7 -2
-4 0 1 6 3
-1 4 7 -8 10 -1```

# 题解

## 作者：KSToki (赞：3)

# 题目大意
现有 $n$ 个数，有的数上了锁，有的没上。将没上锁的数的位置进行重排，使得前缀和最后一次出现负数的位置最小，或不出现负数。
# 题目分析
贪心。对于没有上锁的最后一个位置，无论如何排该位置的前缀和是不会变的，所以我们贪心，用掉最小的那个。接下来重复操作即可。换个说法，就是把所有未上锁的数取出来，从大到小排序再放回去，这样一定是最优的。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[101],l[101],t[101],cnt;
bool cmp(int a1,int a2)
{
	return a1>a2;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(register int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		cnt=0;
		for(register int i=1;i<=n;++i)
		{
			scanf("%d",&l[i]);
			if(l[i]==0)
				t[++cnt]=a[i];
		}
		sort(t+1,t+cnt+1,cmp);
		for(register int i=1,j=1;i<=n;++i)
		{
			if(l[i])
				printf("%d ",a[i]);
			else
			{
				printf("%d ",t[j]);
				++j;
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Wide_Master (赞：0)

## 分析

考虑贪心。我们将所有没被上锁的数字提取出来，然后从大到小排序，在放回原数组即可。

明显发现，如果想要让 $k$ 较大，那么位置越靠前的对整体的贡献越大，所以贪心策略无误。

注意多测清空。

## 代码

```cpp
//By xiaozhou001
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+7;
int t,n,a[N],b[N],c[N],cnt;
int main()
{
    cin>>t;
    while(t--){
        cin>>n;
        cnt=0;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++){
            cin>>b[i];
            if(!b[i])c[++cnt]=a[i];
        }
        sort(c+1,c+1+cnt,greater<int>());
        cnt=0;
        for(int i=1;i<=n;i++){
            if(b[i])cout<<a[i]<<" ";
            else cout<<c[++cnt]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
``````

---

## 作者：czh___ (赞：0)

题目给定一个数列，其中有些位置是被锁定不能移动的，现在将未锁定的元素重新排列后做前缀和，定义 $k$ 是最后一个前缀和小于 $0$ 的下标（若没有前缀和小于 $0$ 则 $k=0$），为使 $k$ 尽量小，求重新排列后的数列。
### 思路：
将未锁定的部分从大到小进行排列，然后依次插入原数组。目的是使前缀和尽量大，尽可能的消除负数的影响。如果有即使放在最后还会导致负数的元素，这些元素即使放在前面也是一样，$k$ 值也是 $n$。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int a[105],b[105],c[105];
int cmp(int a,int b){ 
	return a>b; 
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(c,0,sizeof(c));
        cin>>n;
        int i=0,j=0;
        while(i<n) 
			cin>>a[i++];
        i=0;
        j=0;
        while(i<n){
            cin>>c[i];
            if(c[i]==0)
                b[j++]=a[i++];
            else
                i++;
        }
        stable_sort(b,b+j,cmp);
        i=0;
        j=0;
        while(i<n){
            if(c[i]==0)
                cout<< b[j++]<<" ";
            else
                cout<<a[i]<<" ";
            i++;
        }
        cout<<"\n";
    }
    return 0;
}
```

拜拜！

---

## 作者：FireFy (赞：0)

# CF1418B-Negative Prefixes 题解
## 思路

题目已经几乎把思路告诉你了。

上锁的数，肯定是不能动的，那么只能操作没有上锁的数了。

对于这个序列的最后一个数，无论如何前面的前缀和怎么排列都不会变（加法交换律）。

所以若要使得**最后一次**出现**负数**的位置**最大**，那么很明显就能看出其实把所有未上锁的都抽出来，**从大到小**进行排序就行啦！


## AC Code
```cpp
#include <bits/stdc++.h> 
using namespace std;
int a[1010],b[1010],p[1010];
bool lk[1010];//lock数组
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	int i,j,k,n,m,T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(i=1;i<=n;i++) cin>>a[i];
		for(i=1;i<=n;i++) cin>>lk[i];
		int k=0;
		for(i=1;i<=n;i++)
		{
			if(lk[i]==0)
			{
				b[++k]=a[i];//将未上锁的数提取到b数组里
			}
		}
		sort(b+1,b+k+1,cmp);//从大到小排序
		k=0;
		for(i=1;i<=n;i++)//输出
		{
			if(lk[i]==1) cout<<a[i]<<" ";
			else
			{
				cout<<b[++k]<<" ";
			}
		}
		cout<<endl;
	}
 } 
```


---

## 作者：L_shadow (赞：0)

这题瞄一眼，时间复杂度大概是 $\Theta(nt\log n)$。

## 思路：

这题是想要 $k$ 最大。

如果这题是想要 $k$ 最小的话，那我们只要保证在 $i\in (0,n]$ 时，所得到的前缀和是最小的。

由于上锁的位置是没有办法变动的，我们可以将能变动的数单独拉出来，形成一个新的序列，对这个序列由小到大进行排序。最后再把这个序列重新塞回原来的序列所对应的位置中。

那么，很显然，如果想要 $k$ 最大的话，我们将拉出来的新的序列由大到小再塞回去即可（不需要管前面的前缀和，只考虑最大）。

## 实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],cnt,d[105];
bool s[105];
bool cmp(int a,int b){
	return a>b;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		cnt=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>s[i];
			if(!s[i]){//没锁 。 
				d[++cnt]=a[i];//加入新的序列 。 
			}
		}
		if(cnt) sort(d+1,d+1+cnt,cmp);
		cnt=0;
		for(int i=1;i<=n;i++){
			if(s[i]) cout<<a[i]<<" ";//锁了，直接输出。 
			else{
				cout<<d[++cnt]<<" ";//把排序后的序列塞回去。 
			}
		}
		cout<<endl;
	}
}
```


---

## 作者：Coffee_zzz (赞：0)

很简单的一道题，~~感觉甚至可以评红~~。

### 分析

考虑贪心，所有被上锁的数不动，将所有未上锁的数取出并从大到小排序，最后填充到空余位置中。

因为要使前 $k$ 个数尽可能大，且位置越靠前的对整体的贡献越大，所以贪心策略无误。

注意是尽可能大而不是尽可能小，~~我就看错了~~。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;
int a[105],c[105];
bool b[105];
int main(){
	ios::sync_with_stdio(0);
	int q,cnt,n;
	cin>>q;
	for(int temp=0;temp<q;temp++){
		cin>>n;cnt=0;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			cin>>b[i];
			if(!b[i]) c[++cnt]=a[i];
		}
		sort(c+1,c+1+cnt);
		reverse(c+1,c+1+cnt);
		cnt=0;
		for(int i=1;i<=n;i++){
			if(b[i]) cout<<a[i]<<' ';
			else cout<<c[++cnt]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：icefake (赞：0)

# [CF1418B Negative Prefixes](https://www.zybuluo.com/Lovelotus/note/1742456)

本蒟蒻的[blog1](https://www.luogu.com.cn/blog/IFlyloveLH/) [blog2](https://icefake.github.io/)

---

## 首先来了解一下题意

（~~英语还是很重要啊~~$QAQ$

> 题目给出 $n$ 组数据，对于每一组数据：
> 
> 给你一个长度为 $n$ 的数组，这个数组中的每一个数都有一个状态，或者是‘0’，或者是‘1’
> 
> ‘1’代表这个数字是“锁上的”，而‘0’则代变这个可以和其他‘0’状态的数任意交换位置
>
> 现在要使得 $k$ 最大，而 $k$ 需要满足前 $k$ 个数之和小于 $0$ ,否则 $k = 0$
>
> 输出一种使 $k$ 最大的方案

## 至于分析
~~很显然~~

我们只需要把大的而未被锁上的数尽可能地放在最前面，方案就一定能使得 $k$ 尽可能的大

所以做法就是将所有未被锁上的数存在另一个数组里面，然后 $sort$ 排序一下

再从大到小插入就行啦

## 还是贴一下代码吧 $awa$

注：本人码风绝对正派，不接受任何反驳

```cpp
#include<bits/stdc++.h>
#define int long long
#define inc(i) (++ (i))
#define dec(i) (-- (i))
#define Rep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i <= i##Limit ; inc(i))
#define Dep(i, a, b) for(register int i = (a) , i##Limit = (b) ; i >= i##Limit ; dec(i))

using namespace std;

const int maxn = 300010;
int n, k = 0, m, tot = 0, ans = 0;
int num[maxn], r[maxn], tem[maxn];
bool flag = 0;

int read(){
    int x=0,w=1;char ch=0;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x*w;
}

signed main() 
{
// 	freopen("test.in", "r", stdin);
// 	freopen("test.out", "w", stdout);

	m = read();
	while(m --) {
		ans = 0; tot = 0; k = 0; flag = 0;
		n = read();
		Rep(i,1,n) num[i] = read();
		Rep(i,1,n) {
			tem[i] = read();
			if(!tem[i]) r[++ tot] = num[i];
		}
		sort(r + 1, r + tot + 1);
		k = tot + 1;
		Rep(i,1,n) {
			if(!tem[i]) printf("%lld ", r[-- k]);
			else printf("%lld ", num[i]);
		}
		printf("\n");
	}
	return 0;
} 
```
已 $AC$，但 $kuai$ 得不要过于嚣张。。。






---

