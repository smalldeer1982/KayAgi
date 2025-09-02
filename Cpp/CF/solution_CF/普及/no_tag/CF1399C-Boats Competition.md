# Boats Competition

## 题目描述

There are $ n $ people who want to participate in a boat competition. The weight of the $ i $ -th participant is $ w_i $ . Only teams consisting of two people can participate in this competition. As an organizer, you think that it's fair to allow only teams with the same total weight.

So, if there are $ k $ teams $ (a_1, b_1) $ , $ (a_2,       b_2) $ , $ \dots $ , $ (a_k, b_k) $ , where $ a_i $ is the weight of the first participant of the $ i $ -th team and $ b_i $ is the weight of the second participant of the $ i $ -th team, then the condition $ a_1 + b_1 = a_2 + b_2 =       \dots = a_k + b_k = s $ , where $ s $ is the total weight of each team, should be satisfied.

Your task is to choose such $ s $ that the number of teams people can create is the maximum possible. Note that each participant can be in no more than one team.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, we can reach the optimal answer for $ s=6 $ . Then the first boat is used by participants $ 1 $ and $ 5 $ and the second boat is used by participants $ 2 $ and $ 4 $ (indices are the same as weights).

In the second test case of the example, we can reach the optimal answer for $ s=12 $ . Then first $ 6 $ participants can form $ 3 $ pairs.

In the third test case of the example, we can reach the optimal answer for $ s=3 $ . The answer is $ 4 $ because we have $ 4 $ participants with weight $ 1 $ and $ 4 $ participants with weight $ 2 $ .

In the fourth test case of the example, we can reach the optimal answer for $ s=4 $ or $ s=6 $ .

In the fifth test case of the example, we can reach the optimal answer for $ s=3 $ . Note that participant with weight $ 3 $ can't use the boat because there is no suitable pair for him in the list.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
8
6 6 6 6 6 6 8 8
8
1 2 2 1 2 1 1 2
3
1 3 3
6
1 1 3 4 2 2```

### 输出

```
2
3
4
1
2```

# 题解

## 作者：Tenshi (赞：7)

# 尺取法

~~笔者胡言乱语：~~ 看到这题的时候，心想是不是要暴力枚举啊，但是要是人的质量要是很大怎么办……看了数据范围之后，我放心了~

**分析：**

既然给出的人的质量很小，那么我们可以对分组的一对人的质量和进行枚举，然后算出枚举的质量和下可以分出多少组人。

比如说：

```cpp
1 2 3 4 5
```
这组数据中，质量和枚举到了6，那么对应的组数就是2：

```cpp
(1,5) (2,4)
```
接下来的问题就是：

**如何统计相应的质量和下 分出的人的组数。**

考虑到一对人中质量有大小关系（但不严格），很自然地想到先将数组排序，然后进行统计。

直接两个for？复杂度不够优秀，于是我们采取尺取法~

**尺取法：**

“像这样反复地推进区间的开头和末尾，来求取满足条件的最小区间的方法被称为尺取法”---白书

如果需要更详尽的介绍可以百度（逃

那么如何操作呢？

举个栗子：

```
1 1 4 5 1 4
```
排序后：


```
1 1 1 4 4 5
```

分别声明两个参量s,t 反映区间的开头和末尾
```cpp
int s=1,t=n;
```

记当前分组的质量和为k

```cpp
当 val[s]+val[t]==k && s<t 的时候
```

我们将s向右移动，t向左移动（模拟分组的过程），同时记录分组数。

如下：
```cpp
while(val[s]+val[t]==k && s<t){
                    s++,t--;
                    rec++;
                }
```
类似的，我们可以写出其他两种情况s,t的相应操作。

```cpp
while(val[s]+val[t]<k && s<t){
                    s++;
                }
                while(val[s]+val[t]>k && s<t){
                    t--;
                }
```

当s>=t的时候，说明分组已经停止，结束。

```cpp
if(s>=t){
                    ans=max(ans,rec);
                    break;
                }
```

以上就是关键点。

plus：

①记得特判 n=1 的情况

②可以优化一下枚举的范围。

(如果有Hack数据请告诉我qwq)

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 55
int val[maxn];
int k;
int main(){
    int t;cin>>t;
    while (t--)
    {
        memset(val,0,sizeof(val));
        int n;cin>>n;
        for(int i=1;i<=n;i++) cin>>val[i];
        sort(val+1,val+1+n);
        if(n==1){
            cout<<0<<endl;
            continue;
        }
        int mina=val[1];
        int maxa=val[n];
        
        int ans=1;
        int rec;
        for(k=mina+1;k<=maxa*2;k++){
            int s=1,t=n;
            rec=0;
            while (1)//尺取法
            {
                while(val[s]+val[t]==k && s<t){
                    s++,t--;
                    rec++;
                }
                while(val[s]+val[t]<k && s<t){
                    s++;
                }
                while(val[s]+val[t]>k && s<t){
                    t--;
                }
                if(s>=t){
                    ans=max(ans,rec);
                    break;
                }
            }
            
        }
        cout<<ans<<endl;
    }
    
    return 0;
}
```





---

## 作者：xiaoPanda (赞：3)

### Problem
给 $n$ 个数 $a_1,a_2,...,a_n$ ，要你找到一个数 $s$ 使得从中尽可能的选出 $k$ 组 $(x_i,y_i)$ 满足 $x_1+y_1=x_2+y_2=...=x_k+y_k=s$，输出 $k$。

### Solution
注意到 $1\le a_i\le 50$，那很明显 $s=a_i+a_j\le100$ ，暴力枚举一下 $s$，然后求出 $k$。

有一个贪心策略：如果有两个数满足 $a_i+a_j=s$ ,那这两个数一定是一组，证明略。

所以可以处理出每个数出现的次数，在暴力枚举一个数，如果剩下的那个数次数大于 $0$ ，则可以配成一组，记得要将这两个数出现次数减一。

还有就是不要只判断剩下的数出现的次数，枚举的数的次数也要大于 $0$。

时间复杂度为 $O(Tn^2)$。
### Code
```cpp
void solve() 
{
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	int n, ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i], g[a[i]]++;
	for (int i = 1; i <= 100; i++) {//枚举答案
		for (int j = 1; j <= 100; j++)
			f[j] = g[j];//初始化次数
		int sum = 0;
		for (int j = 1; j <= n; j++) 
			if (i > a[j] && f[i - a[j]] > 0 && f[a[j]] > 0) {
				if (i - a[j] == a[j])if (f[a[j]] > 1)//两个数相同次数至少为2
						sum++, f[i - a[j]]--, f[a[j]]--;//次数减少1次
				if (i - a[j] != a[j])sum++, f[i - a[j]]--, f[a[j]]--;
			}
		ans = max(ans, sum);
	}
	cout << ans << endl;
}
```


---

## 作者：引领天下 (赞：3)

注意到 $1\le w_i \le n$ ，而 $1\le n\le 50$ 。

那么即使是最大的 $s$ ，也仅仅是 $50+50=100$ 而已。

那就直接枚举 $s$ ，暴力统计每个 $s$ 的答案呗。

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int t,n;
long long a[55];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
        sort(a+1,a+n+1);
        int ans=2147483648;
        for(int i=1;i<=2*n;i++){//由于单个人的质量是1~n，两个人加起来就可能到2*n了。
            int cnt=0;bool p[55]={};
            for(int j=1;j<=n;j++)if(!p[j]){//这个人还没匹配过
                bool ok=1;
                for(int k=n;k>j&&ok;k--)if(!p[k])if(a[j]+a[k]==i)p[j]=p[k]=1,ok=0;//对于每个j，暴力寻找是否存在一个k能与它配对，即：能否找到一个对应的a[k]使得a[k]+a[j]=i。
                cnt+=!ok;
            }
            ans=max(ans,cnt);//统计答案
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：wmy_goes_to_thu (赞：3)

最小的和是 $2$，最大的和是 $2 \times n$，所以我们需要枚举这个元素。

对于一个和，我们需要贪心。排序后从左到右枚举，如果该点可以选，那么一定选。因为将来都比它大了，这个就选不了了。所以可以用双指针 $l,r$ 实现。开始 $l=1,r=n$，然后看是否能匹配。依次挪动指针直到 $l>=r$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int w[55];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>w[i];
		sort(w+1,w+n+1);
		int mx=n<<1,ans=0;
		for(int s=2;s<=mx;s++)
		{
			int l=1,r=n,anss=0;
			while(l<r)
			{
				if(w[l]+w[r]>s)r--;
				else if(w[l]+w[r]<s)l++;
				else anss++,l++,r--;
			}
			ans=max(ans,anss);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Werner_Yin (赞：2)

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/solution-CF1399C.html)

# 题意

给你 $n$ 个数： $w_1,w_2,\dots,w_n$ ,从中尽可能的选出 $k$ 组，对于每一组 $(a_i,b_i)$  满足 $a_1+b_1 = a_2 + b_2 = \dots = a_k+b_k = s$ 。输出 $k$ 。

# 分析

我们可以看到数据范围

>  $n ( 1 \le n \le 50 )$ ,$w_1, w_2,       \dots, w_n(1 \le w_i \le n )$ 

也就是说，$s$ 最大为 $100$ 。我们暴力枚举 $s$ 然后找到答案就可以了。

# 代码

具体细节见注释。

```cpp
// 头文件、快读快写自行脑补
#define re(x) read(x)
#define mes(x) memset(x,0,sizeof(x))

const int MAXN = 60;
int n,a[MAXN],tong[MAXN<<1];
// a : 原数组 , tong: 记录每个元素出现次数

int work(int x){
    int res = 0;
  // res : 当前情况下可以选的个数
  //为了防止重复计算，限定枚举范围为前一半，注意对于x为奇数的枚举范围（lim）。
    int lim = x/2;
    if(x &1) lim++;
    for(int i = 1;i < lim;i++)
	if(tong[i] && tong[x-i]) res += min(tong[i],tong[x-i]);
    if( x % 2 == 0) res += tong[x/2] / 2;
    return res;
}

int main (){
	int T;
	re(T);
	while(T--){
		re(n);
		mes(tong);
      //注意清空
		int ans = 0;
		for(int i = 1;i <= n;i++) re(a[i]),tong[a[i]]++;
      //枚举 s
		for(int i = 2;i <= 2*n;i++) ans = max(ans,work(i));
		write(ans);
	}
	return 0;
}
```



---

## 作者：dead_X (赞：2)

## 题意
给定 $n$ 个数，求最多能从中选出多少**对**数，使得每一对数的和都相等。
## 思路
注意到这些数的值域很小，只有 $50$，所以我们可以考虑暴力桶排序，枚举每一对数的和，统计这个和的最大对数。
## 代码
```
#include<bits/stdc++.h>
#define qwq int T=read(); while(T--)
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[53];
int main()
{
	qwq
	{
		int n=read();
		for(int i=1; i<=50; i++) a[i]=0;
		for(int i=1; i<=n; i++) ++a[read()];
		int res=0;
		for(int i=2; i<=100; i++) 
		{
			int ans=0;
			for(int j=max(i-50,1); j<=50; j++) if(i-j<0 || j>i-j) break; else if(j==i-j) ans+=a[j]/2; else ans+=min(a[j],a[i-j]);
			res=max(res,ans);
		}
		printf("%d\n",res);
	}
    return 0;
}
//By dead_X
```


---

## 作者：Edmundino (赞：1)

# 题意

就是给你一个长度为 $n$ 的数组，

让你在这个数组中找到最多有多少个两个数的和相同。

# 分析

本题数据不大，可以考虑用 $n^2$ 的暴力。

我们首先得到一个数组 $x$,

然后让两个数一一匹配再求和记录到一个数组 $y$ 中，

就是说 $y[x_i+x_j]++$。

但是，我们会发现：如果这样运行，在相同的和下，某些数也许会出现多次，所以我们要多加一个限制。

我们先设一个数组 $o$,

$o_i,_j$ 表示第 $i$ 个数，在和为 $j$ 的情况是否出现过。

就是，每当 $y[x_i+x_j]++$ 时，

$o_i,_{x_i+x_j}=1$,$o_j,_{x_i+x_j}=1$。

下一次在执行 $y[x_i+x_j]++$ 前要满足一个条件：

$o_i,_{x_i+x_j}==0$,$o_j,_{x_i+x_j}==0$。

这样就可以保证一个数在和相同的情况只出现一遍。

# 代码

**核心部分**

```cpp
void solve()
{
	while(m--)
    {
    	cin>>n;
    	memset(o,0,sizeof(o));
    	memset(y,0,sizeof(y));
    	for(int i=1;i<=n;i++)
    	{
    		cin>>x[i];
		}
		for(int i=1;i<n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(o[i][x[i]+x[j]]==0&&o[j][x[i]+x[j]]==0)
				{
				    o[i][x[i]+x[j]]=1;
			    	o[j][x[i]+x[j]]=1;
					y[x[i]+x[j]]++;
				}
			}
		}
		int maxy=0;
		for(int i=1;i<=2*n;i++)
		{
			maxy=max(maxy,y[i]);
		}
		cout<<maxy<<endl;
		
	}
}
```



---

## 作者：鹤箩芠 (赞：1)

给一种足够暴力的做法 ， 把每两种可以组成的和 ， 记录一下 ， 最后比对一下就OK了

$vis1$$[i][j]$ 表示 i 和 j 有没有同时一起用过

$vis2[i][j]$ 表示$j$和另一个加数组成的 ， 因为考虑到一个数只能组成一次

$vis3[i]$ 表示 凑成的这个数有多少次


贴代码
```cpp

#include <bits/stdc++.h>
 
using namespace std ;
const int N = 54 ;
 
int t , n , b[N] , a[N] , vis1[N][N] , vis2[120][N] , vis3[120] ;
 
 
 
int main () {
	cin >> t ;
	while (t --) {
    memset (vis1 , 0 , sizeof vis1) ;
    memset (vis2 , 0 , sizeof vis2) ;
    memset (vis3 , 0 , sizeof vis3) ;
    cin >> n ;
    for (int i = 1 ; i <= n ; i ++) cin >> a[i] ;
    for (int i = 1 ; i <= n ; i ++) {
    	for (int j = 1 ; j <= n ; j ++) {
    		if (i == j) continue ;
    		if (vis1[i][j] == 0) {
    			vis1[i][j] = 1 ;
			}
			int sum = a[i] + a[j] ;
			if (vis2[sum][i] == 1) continue ;
			else if (vis2[sum][j] == 1) continue ;
			else if (vis2[sum][i] == 0) {
				if (!vis2[sum][j]) vis2[sum][j] = 1 ;
				vis2[sum][i] = 1 ;
				vis3[sum] ++  ;
			}
			else if (vis2[sum][j] == 0) {
				if (!vis2[sum][i]) vis2[sum][i] = 1 ;
				vis2[sum][j] = 1 ;
				vis3[sum] ++  ;
			}
		} 
	}
	int ans = 0 ;
	for (int i = 1 ; i <= n + n ; i ++) {
		ans = max (ans , vis3[i]) ;
	}
	cout << ans << endl ;
    }
 	return 0 ;
}
```


---

## 作者：Suuon_Kanderu (赞：0)

看到此题数据范围不大，我们想到暴力枚举 $s$，最后取最大值。

我们需要找到 $a_i + a_j = s$ 的数量，容易想到 two pointer 解法，但我们也可以是用更为简单的方法：

移项，得到 $s - a_i = a_j$ 。首先我们把每个数在桶 cnt 里记录。$cnt(i)$ 就表示 i 在整个序列中出现过几次。

之后统计 $a_i + a_j = s$ 的数量，从前往后扫。对于每个 i ，我们需要判断 $cnt(a(i))$ 是否至少为 1，因为可能在之前 $a(i)$ 已经用过了，肯定不符合条件。

满足 $cnt(a(i)) >0$ 后，有两种情况是满足条件的：

$$s-a(i) \not= a(i) ,cnt(s-a(i))>0 $$
$$s-a(i) = a(i),cnt(a(i))>1 $$

判断即可，满足条件后我们把 $cnt(a(i)) \gets cnt(a(i))-1,cnt(s-a(i)) \gets cnt(s-a(i))-1$,表示这两个数已经被选了。

需要注意！我们每次枚举后都需要将 cnt 数组还原。

此代码时间复杂度是 $O(Tn^2)$ 的。

```
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
int n ,  a[200] ; 
int check(int cnt[] , int t) {
	int now = 0;
	for(int j = 1; j <= n; j++) {
		if(t - a[j] < 0)continue;
		if(cnt[a[j]] && ((cnt[t - a[j]] && t - a[j] != a[j]) //情况一
		|| (t - a[j] == a[j] && cnt[a[j]] >= 2)) ) {//情况2
			now++;//记录答案
			cnt[t - a[j]]--; 
			cnt[a[j]]--;
		}	
	}
	return now;
}
int main() {
	int t;scanf("%d" , &t);
	while(t--) {
		int cnt[200] , ans = 0;//答案
		memset(cnt , 0 , sizeof(cnt));
		scanf("%d" , &n);
		for(int i = 1; i <= n; i++) {
			scanf("%d" , &a[i]);
			cnt[a[i]]++;
		}int t[200];//将 cnt 数组还原
		memcpy(t , cnt , sizeof(t));
		for(int i = 1; i <= 2*n; i++) {	
			ans = max(ans , check(cnt , i));
			memcpy(cnt , t , sizeof(cnt));	
		}

		printf("%d\n" , ans);
	}
}
```


---

## 作者：KSToki (赞：0)

题目大意是给出长为$n$的数组$w$，找出一个$s$使得在$w$中所有数只能用一次的情况下能够完成$w_i+w_j(i!=j)$的对数越多。

由于$n$很小，$w_i$都很小，所以对$w$排序，我们暴力枚举$s$（范围为$1$~$2\times w_n$），并暴力枚举第一个数$a$，在$w$中暴力找$s-a$并暴力删除数即可。时间复杂度为$O(tn^3)$，可以通过。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,w[51],ans,tmp[51];
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		    flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int main()
{
	t=read();
	while(t--)
	{
		ans=0;
		n=read();
		for(register int i=1;i<=n;++i)
		    w[i]=read();
		sort(w+1,w+n+1);
		for(register int i=1;i<=w[n]*2;++i)//暴力枚举s
		{
			memcpy(tmp,w,sizeof(tmp));//存下来
			int now=0,len=n,j=1;
			while(j<=len)//暴力枚举a
			{
				bool f=0;
				for(register int k=j+1;k<=len;++k)//暴力查找s-a
				    if(tmp[j]+tmp[k]==i)
				    {
				    	++now;
						for(register int l=k;l<len;++l)
						    tmp[l]=tmp[l+1];
						--len;
						for(register int l=j;l<len;++l)
						    tmp[l]=tmp[l+1];
						--len;
						f=1;
						break;
				    }//暴力删数
				if(f==0)
				    ++j;//没有s-a
			}
			ans=max(ans,now);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Histone (赞：0)

### 题意概要：

给你一个数组 **a**

从中选任选两个元素在一起，组成一个数对，数对的值等于两元素相加的值

你的目的就是找出一个值 **k** 

使得所有数对的值都等于 **k** 的情况下

数对的数量最多

### 思考ing：

看了看题目的数据范围，要找这个 **k** 值，我们很自然地就会想到暴力

那么，如何暴力呢？

这时候不妨手搓一套数据来看看

```cpp
1 2 2 1 2 1 1 2
```
我们统计下每个数字出现的次数

**1** 出现了 4 次 ， **2** 出现了 4 次

显然，当 **k = 3** 时，数对的数量有最大值

相信有的大佬看到这里已经懂了 ~~（大佬怎么可能来看蒟蒻的题解）~~

### 一个勉强跑过测评的解法：

我们可以暴力枚举每个 **k** 值

然后看看在每个 **k** 值下 ，能组成多少个数对

如何判断可以组成多少个数对呢？

```cpp
for(re int k=枚举起点;k<=枚举终点;++k){
	int temp = 0;//每个k值时，组成的数对数量
	num[]原数组，题目提供的数组，长度为n
	vis[]统计原数组中每个数出现的次数
	for(re int j=1;j<=n;++j){//开始暴力
		if(	k-num[j]>0&& //防止数组越界
			(vis[num[j]]>=2&&num[j]==k-num[j])||//如果选择的两个元素大小相等，那么至少要出现两次以上
			(vis[k-num[j]]>=1&&vis[num[j]]>=1&&num[j]!=k-num[j])//不相等的话，各出现一次以上就好
			)
		{
				vis[k-num[j]]--;//消耗掉该元素
				vis[num[j]]--;//消耗掉该元素
				temp++;//数对数量加一
			}
		}
	ans = max(ans,temp);//统计答案
}
```
具体细节都在伪代码里了

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;

inline int read(){
	re int ans = 0;re bool f = 1;re char ch = getchar();
	while(ch<'0'||ch>'9'){if (ch=='-')f = 0;ch = getchar();}
	while(ch>='0'&&ch<='9'){
		ans = ans*10+(ch^48);
		ch = getchar();
	}
	return f?ans:~(ans-1);
}// 垃圾快读板子，不必理会

bool cmp(int u,int v){
	return u>v;
}
signed main(void){
	int t = read();
	while(t--){
		int v[128] = {0},vis[128] = {0} ,num[128] = {0};
		int n = read(),ans = 0;
		for(re int i=1;i<=n;++i){
			num[i] = read();
			v[num[i]] = ++vis[num[i]];
		}
		sort(num+1,num+1+n);//一个简单获取枚举起点和终点的方法
		int minn = num[1]+num[2];
		int maxn = num[n-1]+num[n];
		for(re int i=minn;i<=maxn;++i){
			int temp = 0;
			for(re int j=1;j<=n;++j)
				vis[j] = v[j];//刷新vis数组，避免上次的改变影响本次结果
			for(re int j=1;j<=n;++j){
				if((vis[num[j]]>=2&&num[j]==i-num[j])||(vis[i-num[j]]>=1&&vis[num[j]]>=1&&num[j]!=i-num[j])&&i-num[j]>0){
					vis[i-num[j]]--;
					vis[num[j]]--;
					temp++;
				}
			}
			ans = max(ans,temp);	
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

时间复杂度分析不出来，但是跑起来还可以 ~~（数据水）~~

测试 [用时1.82s](https://www.luogu.com.cn/record/36459614)

---

## 作者：Doubeecat (赞：0)

## [CF1399C. Boats Competition](https://codeforc.es/contest/1399/problem/C)

> 有 $n$ 个数,每个数带有一个权值 $w_i$,如果有 $k$ 个分组$(a_i,b_i)$（其中 $a_i$ 表示第一个数的权值，$b_i$ 表示第二个数的权值）则需要满足 
> 
> $a_1 + b_1 = a_2 + b_2 = \dots = a_k + b_k = s,s$ 是每个分组的总权值。
>
> 你的任务是挑选一个 $s$ 令满足条件的分组最多。
> 
> $T \leq 1000,1 \leq w_i \leq n \leq 50$ 

### 思路

暴力题。

观察到这个 $n$ 非常小，我们可以考虑 $O(n ^ 3)$ 的算法。

题目中已经很明显告诉我们挑选 $s$,可以发现 $2 \leq s \leq 2n$。

所以我们枚举 $s$，在循环内部再枚举一遍 $a_i,b_i$ 看有没有符合的，最后在所有 $s$ 中取最大值。

时间复杂度 $O(n ^ 3)$

### 代码

```cpp
const int N = 100;
int n,a[N];
bool vis[N];

signed main() {
	int T;read(T);	
	while (T--) {
		read(n);
		int ans = 0;
		for (int i = 1;i <= n;++i) read(a[i]);
		for (int s = 1;s <= 2*n;++s) {
			int now = 0;
			memset(vis,0,sizeof vis);
			for (int i = 1;i <= n;++i) {
				for (int j = 1;j <= n;++j) {
					if (i != j && !vis[i] && !vis[j]) {
						if (a[i] + a[j] == s) {
							vis[i] = vis[j] = 1;
							++now;
						}
					}
				}
			}
			ans = max(ans,now);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

