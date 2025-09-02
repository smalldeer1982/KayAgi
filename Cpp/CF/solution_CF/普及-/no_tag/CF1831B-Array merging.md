# Array merging

## 题目描述

给定两个长度为 $n$ 的数组 $a$ 和 $b$。

猫猫让你合并这些数组，形成另一个长度为 $2n$ 的数组 $c$。你需要找到所有 $c$ 中元素值相同的子串长度的最大值。


合并过程是：每次选择任一非空数组中的第一个元素，将其添加到 $c$ 的末尾后从原数组中删除，这样的操作进行 $2n$ 次，直到两个数组都为空为止。

## 样例 #1

### 输入

```
4
1
2
2
3
1 2 3
4 5 6
2
1 2
2 1
5
1 2 2 2 2
2 1 1 1 1```

### 输出

```
2
1
2
5```

# 题解

## 作者：Untitled10032 (赞：4)

## 题意

给定两个长度为 $n$ 的序列 $a$ 和 $b$，对于任意的将 $a$、$b$ 两序列归并成一个大序列（序列 $c$）的方案，求出最长的相等子串（即所有元素都相等的子串）的长度。

## 思路

首先可以得到几个简单的结论：

+ 如果在串 $a$ 中有两个不相邻的数，那么在所有的归并方案中，归并后的串里，它们不可能相邻。

- 在串 $a$ 中找任意一个数 $x$，在串 $b$ 中找任意一个数 $y$，必然存在一种归并方案，使归并后 $x$ 与 $y$ 相邻。

* 对于串 $a$ 中的任意子串，必然存在一种归并方案，使归并后的串 $c$ 中也存在这个子串。（串 $b$ 同理）

那么我们先考虑一个子问题：将串 $a$ 与 $b$ 归并，给定一个数 $k$，求对于所有归并方案，归并后的序列 $c$ 中，元素全部为 $k$ 的、最长的子串的长度。

对于这个问题，我们找到 $a$ 串中，元素全部为 $k$ 的、最长的子串长度 $m$，找到 $b$ 串中元素全部为 $k$ 的、最长的子串长度 $n$，则最后的答案即为 $m + n$。

那么对于所有可能得 $k$ 计算一遍，之后取最大值，就可以得到本题的答案了。

------------

所以我们可以对于 $a$ 和 $b$ 分别统计出 $ca$ 和 $cb$ 数组（桶子），$ca_i$ 表示 $a$ 串中，全部由 $i$ 组成的、最长的子串的长度。（$cb_i$ 表示 $b$ 串中，全部由 $i$ 组成的、最长的子串的长度。）

之后我们对于所有的 $i$，求出 $ca_i + cb_i$ 的最大值，即为答案。

## 代码

```cpp
#include <iostream>
#include <cstring>

using namespace std;
constexpr int N = 2e5 + 5;
int ca[N * 2], cb[N * 2];

void get(int n, int *bucket) {
    memset(bucket, 0, sizeof(int) * (n * 2 + 3));
    int last = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        if (temp == last)
            cnt++;
        else {
            bucket[last] = max(bucket[last], cnt);
            last = temp;
            cnt = 1;
        }
    }
    bucket[last] = max(bucket[last], cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        get(n, ca);
        get(n, cb);
        int ans = 0;
        for (int i = 1; i <= (n << 1); i++)
            ans = max(ans, ca[i] + cb[i]);
        cout << ans << '\n';
    }
    return 0;
}
```
- `ca` 和 `cb` 与上文思路中的含义相同。
- `get` 函数用于处理出上文中的 $ca$ 和 $cb$ 数组。需要传入序列长度与一个存放数组的桶子（`ca` 或 `cb`）。
- 多测记得清空。

---

## 作者：Moya_Rao (赞：1)

# 题目大意
两个数组合并到一个数组中，求合并后数组的最大等值长度。

# 思路

对照样例思考：由于合并数组可以任意选择顺序，所以假定 $a$ 数组中对应 $i$ 值的最长等值串长度为 $ansa_i$，$b$ 数组中对应 $i$ 值的最长等值串长度为 $ansb_i$，不难得出合并的数组 $c$ 中，对应 $i$ 值的最长等值串长度为 $ansc_i=ansa_i+ansb_i$。

然后对 $ansc_i$ 遍历求最大值即可。

但是后面再遍历一次 $ansc_i$ 数组就超时了（后面才发现 $\operatorname{memset}$ 也可以优化，详见他人题解，此就不细说了），当时想到的办法就是在 $ansb_i$ 数组生成时，就对应用一个 $maxb$ 记录下 $ansa_i+ansb_i$，那么最终在输入之后，$maxb$ 就已经生成好了，就直接输出即可。

另外几个小坑点分享：

- 进行完循环后，最后的等值字串值记得收起来。

- 有可能 $a$ 数组中存在 $b$ 数组没有的值，所以后面答案的 $max$ 初值要设定为 $ansa_i$ 数组中的最大值。

- $\operatorname{cin}$ 会超时，建议使用快读或者 $\operatorname{scanf}$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int t,n,a[maxn],b[maxn],ansa[maxn*2],ansb[maxn*2];
inline int read(){
	int k=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+c-'0';c=getchar();}
	return k*w;
}
void empty_start(){
	memset(ansa,0,sizeof(ansa));
	memset(ansb,0,sizeof(ansb));
}
int main(){
   t=read();
	while(t--){
		empty_start();
        n=read(),a[1]=read();
		int cnt=1,p=a[1],maxa=1;
		for(int i=2;i<=n;i++){
			a[i]=read();
			if(a[i]==a[i-1]){
				cnt++,maxa=max(maxa,cnt);
			}
			else{
				maxa=max(maxa,cnt);
				ansa[p]=max(ansa[p],cnt);
				cnt=1,p=a[i];
			}
		}
		ansa[p]=max(ansa[p],cnt);
		maxa=max(maxa,cnt);
		b[1]=read();
		cnt=1,p=b[1];
		int maxb=maxa;
		for(int i=2;i<=n;i++){
			b[i]=read();
			if(b[i]==b[i-1]){
				cnt++,maxb=max(maxb,ansa[p]+ansb[p]);
			}
			else{
				ansb[p]=max(ansb[p],cnt);
				maxb=max(maxb,ansa[p]+ansb[p]);
				cnt=1,p=b[i];
			}
		}
		ansb[p]=max(ansb[p],cnt);
		maxb=max(maxb,ansa[p]+ansb[p]);
        printf("%d\n",maxb);
	} 
	return 0;
}
```

---

## 作者：slzx_CPS (赞：1)

题目不难，~~但是错了三次T_T~~

我们可以发现，跨所有合并数组 $c$ 的相等值的最大子数组在原数组中也是连续的，因此我们可以在读入时计算数组 $a$ 或者 $b$ 中的最长连续的相同子数组长度，同时在处理数组 $b$ 时加上数组 $a$ 中相同的元素的最长的子数组的长度。

基本思路就是如此，但是注意以下几点：

1. 数组处理时最后一个连续子数组也要再处理一次！

2. 数组 $a$ 和 $b$ 的数值范围是 $1 \le a_i  \le 2 \cdot n$，$1 \le b_i  \le 2 \cdot n$，数组不要开太小！

3. 用 memset 清零可能超时。

下面附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//养成好习惯~
const int N=2e5+5;
int t,n,x,last,s,ans,suma[N*2],sumb[N*2];//注意*2
signed main(){
	cin>>t;
	for(int e=0;e<t;e++){
		cin>>n>>x;
		ans=1;//最小的一定是1
		s=1;last=x;//处理a[1]
		memset(suma,0,sizeof(int)*(n*2+3));//清空
		//本人第一次用(int)*(n*2+3)，不然TLE T_T
		for(int i=2;i<=n;i++){
			cin>>x;
			if(x==last)	s++;//相同就累加
			else
			 suma[last]=max(suma[last],s),//存储最长相同的连续的子串长度
			 ans=max(ans,suma[last]),//计入答案
			 s=1;//清空，但是当前情况需要加入s
			last=x;
		}
		suma[last]=max(suma[last],s),ans=max(ans,suma[last]);//处理a[n]
		//以下同上
		memset(sumb,0,sizeof(int)*(n*2+3));
		cin>>x;last=x;s=1;
		for(int i=2;i<=n;i++){
			cin>>x;
			if(x==last)	s++;
			else
			 sumb[last]=max(sumb[last],s),
			 ans=max(ans,suma[last]+sumb[last]),
			 s=1;
			last=x;
		}
		sumb[last]=max(sumb[last],s),ans=max(ans,suma[last]+sumb[last]);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：xkcdjerry (赞：1)

送分题吃了 $3$ 发罚时，难绷

不妨设数 $x$ 在 $a$ 和 $b$ 中的最长连续出现次数分别为 $f_x$ 和 $g_x$，那么在合并后的数组中最长连续出现次数为 $f_x+g_x$，证明如下。

不妨设两次连续出现分别为 $[L_a,R_a],[L_b,R_b]$，那么：

* 通过先取走 $a$ 的 $[1,L_a-1]$，$b$ 的 $[1,L_b-1]$，然后再以任意次序取走 $a$ 的 $[L_a,R_a]$ 和 $b$ 的 $[L_b,R_b]$ 就能构造出 $x$ 连续出现 $f_x+g_x$ 次的序列，即最大连续出现次数一定不小于 $f_x+g_x$。
* 假设最终数列中有 $x$ 连续出现大于 $f_x+g_x$ 次，那么由于这一段后显然一定由 $a$ 和 $b$ 中连续的元素 merge 而成，那么等于说 $a,b$ 中能各取出一段连续的 $x$ 使得长度和大于 $f_x+g_x$，与 $f_x,g_x$ 的定义矛盾，故 $x$ 的最大连续出现次数一定不大于 $f_x+g_x$。

综上所述，对于任意一个数 $x$ 都有其在所有合并方式中的最大连续长度为 $f_x+g_x$。

那么我们 $O(n)$ 扫一下 $a$ 和 $b$ 计算出 $f,g$ 然后依次更新即可，一些细节问题已在注释里说明。

代码：

```c++
#include <cstdio>
#define N 200010
//限制了ai,bi<=2n所以可以用数组
//值域开到 1e9 什么的就要离散化或者用 map 了
int n,a[N],b[N],f[2*N];
int max(int x,int y) {return x>y?x:y;}
void once()
{
    scanf("%d",&n); int ans=0;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i);

    //多测不清零，爆零两行泪
    for(int i=1;i<=2*n;i++) f[i]=0;
    //利用越界值避免特判
    a[0]=b[0]=a[n+1]=b[n+1]=0;

    for(int i=1,run=0;i<=n+1;i++)
    {
        if(a[i]!=a[i-1])
        {
            f[a[i-1]]=max(f[a[i-1]],run);
            //可能有些 a 中出现的值 b 中不会出现但是还是最大结果
            //所以这里也要更新答案，我因为这个吃了三次罚时
            ans=max(ans,run);
            run=0;
        }
        run++;
    }

    for(int i=1,run=0;i<=n+1;i++)
    {
        if(b[i]!=b[i-1])
        {
            //注意这里的实现会导致用 x=0 更新答案，上面同理
            //本题中不会有问题但是其他题中可能会影响答案需要特判掉
            ans=max(ans,run+f[b[i-1]]);
            run=0;
        }
        run++;
    }
    printf("%d\n",ans);
}
int main()
{
    int t; scanf("%d",&t); while(t--) once();
}
```

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1831B) & [CF 链接](http://codeforces.com/problemset/problem/1831/B)

## 思路分析：

我们当然可以用 $O(2^n)$ 的时间复杂度去枚举每一种可能情况，然后输出，但这并不能通过此题。

仔细观察样例我们可以发现几个性质：

1. 原数组中的不相邻元素合并后也一定不相邻。

2. 原数组中相邻的元素一定可以让它们合并后也相邻。

那我们就可以利用这两个性质，分别开两个 $2n$ 的桶去存储每个数字在两个数组中最长的连续出现次数，我们记正整数 $x$ 在 $a$ 数组中最多连续出现了 $A_x$ 次，在 $b$ 数组中最多连续出现了 $B_x$ 次。那么对于 $1\le i\le 4\times10^5$，答案就是

$$\max(A_i+B_i)$$

因此只需要 $O(n)$ 的时间复杂度即可完成这道题。$T$ 组数据别忘了清空。

## 代码：

```cpp
#include<iostream>
using namespace std;
int n,a[400003],b[400003],T,ans,maxa;//maxa表示最大的a[i]，即桶的最大下标，优化时间 
/*
我这里为了节省空间直接省去了a数组和b数组，这里的a，b相当于上面的A和B
用tmp来表示a[i-1]也就是上一个元素用来判断是否连续 
*/
void solve(){
	scanf("%d",&n);
	ans=maxa=0;
	int x,cnt=0,tmp=0;
	//多测不清空，爆零两行泪 
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		maxa=max(maxa,x);//求最大值 
		if(x!=tmp){//判断是否和上一个元素相等，求连续区间
			//如果不相等说明是一个新的连续区间 
			a[tmp]=max(a[tmp],cnt);//计算上一个区间的值 
			cnt=0;//清空 
		}
		cnt+=1;//统计 
		tmp=x;//替换tmp 
	}	
	a[tmp]=max(a[tmp],cnt);//最后一个区间也要算
	//以下代码同上面a数组 
	cnt=0,tmp=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		maxa=max(maxa,x);
		if(x!=tmp){
			b[tmp]=max(b[tmp],cnt);
			cnt=0;
		}
		cnt+=1;
		tmp=x;
	}
	b[tmp]=max(b[tmp],cnt);	
	//以上代码同上面a数组
	for(int i=1;i<=maxa;i++){
		ans=max(ans,a[i]+b[i]);//计算答案 
	}
	cout<<ans<<"\n";//输出 
	//多测不清空，爆零两行泪 
	for(int i=1;i<=maxa;i++){
		a[i]=b[i]=0;
	}
	return;
}
int main(){
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：DBL_MAX (赞：0)

# 题目
[CF1831B 传送门](https://www.luogu.com.cn/problem/CF1831B)
# 题目难度
$\color{orange} \texttt{普及-}$
# 题目简述

给定两个长度为 $n$ 的数组 $a$ 和 $b$。

猫猫让你合并这些数组，形成另一个长度为 $2n$ 的数组 $c$。你需要找到所有 $c$ 中元素值相同的子串长度的最大值。

合并过程是：每次选择任一非空数组中的第一个元素，将其添加到 $c$ 的末尾后从原数组中删除，这样的操作进行 $2 \times n$ 次，直到两个数组都为空为止。
#### 输入格式
第一行包含整数 $t$，表示测试数据的数量。
#### 输出格式
输出跨所有合并数组 $c$ 的相等值的最大子数组的长度。

# 思路
题意很好理解。

我们可以想到一个结论：我们让在 $a$ 数组中的**任意位置**接上 $b$ 数组的**任意位置**，可得到我们的贪心策略：将  $a$ 中的一段**相同**的数连上 $b$ 中数字**相同**的**一段数**，然后我们就可以统计出在 $a$ 中每一个数最长相等的长度，然后再在 $b$ 中也把它统计出来，接着我们就可以对每一个数求出 $a$ 中最长和 $b$ 中最长的长度**相加的最大值**即可。
# 代码
讲完了思路，看我的代码吧！（有注释）
```cpp
#include <bits/stdc++.h>  //万能头文件
using namespace std ; //定义命名空间
#define int long long //define
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
int t, n, a[200100], b[200100], cnt[400100], cnt2[400100];//定义

signed main() {//主函数
	cin >> t;//输入
	while (t--) {//循环
		cin >> n;//输入
		rep(i, 1, n) cin >> a[i], cnt2[a[i]] = cnt[a[i]] = 0;//输入
		int cc = 1;//定义
		cin >> b[1];//输入
		cnt[b[1]] = cnt2[b[1]] = 0;//赋值
		rep(j, 2, n) {
			cin >> b[j];//输入
			cnt[b[j]] = cnt2[b[j]] = 0;赋值
		}
		rep(j, 2, n) {
			if (b[j] == b[j - 1])//分支语句
				cc++;
			else
				cnt[b[j - 1]] = max(cc, cnt[b[j - 1]]), cc = 1;
		}
		cnt[b[n]] = max(cnt[b[n]], cc);//赋值
		cc = 1;//赋值
		rep(i, 2, n) {
			if (a[i] == a[i - 1])//分支语句
				cc++;
			else
				cnt2[a[i - 1]] = max(cnt2[a[i - 1]], cc), cc = 1;
		}
		cnt2[a[n]] = max(cnt2[a[n]], cc);//赋值
		int ans = 0;//定义+赋值
		rep(i, 1, n) ans = max(ans, max(cnt2[a[i]] + cnt[a[i]], cnt[b[i]] + cnt2[b[i]]));//赋值
		cout << ans << endl;//输出
	}
	return 0;
}
```
好了，今天的说完了，拜拜！

---

## 作者：UniGravity (赞：0)

## Solution CF1831B Array merging

[Luogu传送门](https://www.luogu.com.cn/problem/CF1831B) + [CF传送门](https://codeforces.com/problemset/problem/1831/B) 

[提交记录](https://www.luogu.com.cn/record/122288447)

### 题目分析
我们以数组 $a$ 为例分析：

可以发现，$a$ 数组中不相邻的两个数，合并后也**不可能相邻**。（因为要按顺序合并）（数组 $b$ 同理）   

我们可以先考虑，对于特定元素 $x$，求对于所有的合并方案，元素全为 $x$ 的最长子串长度。

由于原数组中不相邻的两个数一定无法相邻，我们只需分别找到 $a,b$ 数组中值为 $x$ 的最长子串长度 $m,n$，将这找到的子串合并，那么上文所说的答案即为 $m+n$。

枚举特定元素 $x$ 然后去最大值即可。

然后再讲一讲如何找到最长子串长度，我们记录 $acnt_i$ 表示子串元素全为 $i$ 的最长子串长度，$cnt$ 为连续字符长度：

```cpp
if (a[i] == a[i - 1]) {
    cnt++;
} else {
    acnt[a[i - 1]] = max(acnt[a[i - 1]], cnt);
    cnt = 1;
}
```

数组 $b$ 同样方法处理即可。

### 核心代码
```cpp
scanf("%d", &n);
memset(acnt, 0, sizeof(acnt));
memset(bcnt, 0, sizeof(bcnt));

cnt = 1;
for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    
    if (i > 1) {
        if (a[i] == a[i - 1]) {
            cnt++;
        } else {
            acnt[a[i - 1]] = max(acnt[a[i - 1]], cnt);
            cnt = 1;
        }
    }
}
acnt[a[n]] = max(acnt[a[n]], cnt);

cnt = 1;
for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
    
    if (i > 1) {
        if (b[i] == b[i - 1]) {
            cnt++;
        } else {
            bcnt[b[i - 1]] = max(bcnt[b[i - 1]], cnt);
            cnt = 1;
        }
    }
}
bcnt[b[n]] = max(bcnt[b[n]], cnt);

ans = 0;
// 枚举所有的x
for (int i = 1; i <= n; i++) {
    ans = max(ans, max(acnt[a[i]] + bcnt[a[i]], acnt[b[i]] + bcnt[b[i]]));
}
printf("%d\n", ans);
```

完结撒花~

---

## 作者：CQ_Bab (赞：0)

# 思路
首先提议很好理解，那么我们就可以想到一个结论就是我们可以让在 $a$ 数组中的任意一个位置接上 $b$ 数组的任意一个位置，那么我们的贪心策略就为将 $a$ 中的一段相同的数连上 $b$ 中数字相同的一段数，那么我们就可以统计出在 $a$ 中每一个数最长相等的长度，然后再在 $b$ 中也统计出来然后我们就对于每一个数求出 $a$ 中最长和 $b$ 中最长的长度相加的最大值即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
int t,n,a[200100],b[200100];
int cnt[400100];
int cntb[400100];
signed main() {
	cin>>t;
	while(t--) {
		cin>>n;
		rep(i,1,n) cin>>a[i],cntb[a[i]]=cnt[a[i]]=0;//初始化
		int cc=1;//用一个变量来记录现在相等的长度为多少 
		cin>>b[1];
		cnt[b[1]]=cntb[b[1]]=0;//初始化
		rep(j,2,n) {
			cin>>b[j];
			cnt[b[j]]=cntb[b[j]]=0; //初始化 
		}
		rep(j,2,n) {
			if(b[j]==b[j-1]) cc++; //若相等继续加 
			else cnt[b[j-1]]=max(cc,cnt[b[j-1]]),cc=1; //不相等取一个最大值然后以现在的为开头继续统计 
		}
		cnt[b[n]]=max(cnt[b[n]],cc); //将最后一个统计一下 
		cc=1;
		rep(i,2,n) {
			if(a[i]==a[i-1]) cc++; //同上 
			else cntb[a[i-1]]=max(cntb[a[i-1]],cc),cc=1;
		}
		cntb[a[n]]=max(cntb[a[n]],cc);
		int ans=0;
		rep(i,1,n) ans=max(ans,max(cntb[a[i]]+cnt[a[i]],cnt[b[i]]+cntb[b[i]])); //将每一个数在a数组中和b数组中的最长相等长度相加 
		cout<<ans<<endl;
	}
	return false;
}
```

---

