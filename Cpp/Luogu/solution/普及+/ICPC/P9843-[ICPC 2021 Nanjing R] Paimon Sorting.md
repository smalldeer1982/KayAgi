# [ICPC 2021 Nanjing R] Paimon Sorting

## 题目描述

派蒙刚刚发明了一种新的排序算法，看起来很像“冒泡排序”，但有一些不同之处。它接受一个长度为 $n$ 的从 1 开始索引的序列 $A$ 并对其进行排序。其伪代码如下所示。

```cpp
// 排序算法
SORT(A)
  for i from 1 to n // n 是 A 中元素的数量
    for j from 1 to n
      if a[i] < a[j] // a[i] 是 A 中的第 i 个元素
        Swap a[i] and a[j]
```

如果你不相信这段算法可以对一个序列进行排序，你的任务就是证明它。无论如何，问题如下：

给定一个整数序列 $A = a_1, a_2, \cdots, a_n$，对于其每个长度为 $k$ 的前缀 $A_k$（即，对于每个 $1 \le k \le n$，考虑子序列 $A_k = a_1, a_2, \cdots, a_k$），计算调用 $\text{SORT}(A_k)$ 时执行的交换次数。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
5
2 3 2 1 5
3
1 2 3
1
1
```

### 输出

```
0 2 3 5 7
0 2 4
0
```

# 题解

## 作者：suzhikz (赞：4)

感谢喵仔牛奶的数据喵喵喵。

对于这种每次添加一个数的询问，我们先不考虑加数，仅考虑调用一次该函数。

首先，第一次循环会把整个序列中最大的数丢到最前面。

然后第一次操作的交换次数可以暴力计算。

考虑第二次以及后面的所有循环。假设我们现在是第 $i$ 次循环，显然 $1$ 到 $i-1$ 已经按照小到大排序了，然后我们会把 $i$ 前面的**每种**数和这个位置进行一次交换。这个种类个数我们用树状数组直接维护即可。

那么答案我们就可以 $O(n\log n)$ 快速计算了啊。

接下来考虑加入一个数对答案的影响。

分类讨论下，如果这个数字比前面的最大值小或者等于，那么这个数字只会在最后一个循环用到，然后贡献就是前面的比它大的数的种类个数。

如果这个数字比最大值大。假设现在序列总长度为 $n$。

那么第一次循环这个东西会被交换到最前面。操作次数加一。

然后最后一个数会变成之前的最大值。贡献就是还是一。

然后第 $2$ 到 $n-1$ 次循环需要分类讨论下，如果说 $1$ 到 $n-1$ 最大值只有一个，那么前面 $n-1$ 个数之间的相对大小并没有改变，贡献不会增加。

若最大值有两个以上，假设第二个最大值位置在 $p$，那么发现从 $p$ 到 $n-1$ 中的每个位置，循环到这个位置时，比他大是数字的种类个数会多一个，所以贡献是 $n-p$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define db double
#define il inline
using namespace std;
void read(int &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
void read(ll &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
const int N=1e5+5;
int t,n,a[N],tree[N],cnt[N];
il int lowbit(int x){
	return x&(-x);
}
bool vis[N];
int query(int x){
	int re=0;
	while(x){
		re+=tree[x];x-=lowbit(x);
	}return re;
}
void update(int x,int w){
	if((w==1&&!vis[x])||(w==-1&&vis[x]==1)){
		vis[x]=(w!=-1);
		while(x<=n){
			tree[x]+=w;x+=lowbit(x);
		}
	}
}
int maxx=0;ll ans,ma,po1,po2;
int main(){
	read(t);
	while(t--){
		read(n);for(int i=1;i<=n;i++)read(a[i]);po1=po2=0;
		ans=0;ma=a[1];update(a[1],1);cnt[a[1]]++;
		printf("0");
		for(int i=2;i<=n;i++){
			update(a[i],1);cnt[a[i]]++;
			if(a[i]>ma){
				ans++;ans+=query(n)-query(ma);
				if(po2)
				ans+=i-po2;
				ma=a[i];po1=i;po2=0;
			}else{
				ans+=query(n)-query(a[i]);if(a[i]==ma)if(po2==0)po2=i;
			}
			printf(" %lld",ans);
		}
//		cout<<query(n)<<endl;
		if(t!=0)puts("");
		for(int i=1;i<=n;i++)update(a[i],-1),cnt[i]--;
	}
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

# Solution

## Part I 

考虑对于如何计算整个序列的答案。

先模拟第一次循环，交换该交换的。

观察发现，从第二次循环开始，当外层循环枚举到 $i$ 时，$[1,i-1]$ 已经排好序了，并且 $a_{i-1}$ 是全局最大值。此时可能交换的 $j$ 一定在 $[1,i-1]$ 中，具体地，这次交换会交换 $\sum_{j=1}^{i-1}[a_j>a_i]$ 次。

因为 $j<i$，所以 $i$ 和 $j$ 交换不会影响之后的次数，树状数组维护 $\sum_{j=1}^{i-1}[a_j>a_i]$ 即可。

```cpp
REP(k, 1, n) {
	Fenwick<int> T(n); vector<int> p(n + 1), t(n + 1);
	int cnt = 0; 
	REP(i, 1, k) p[i] = a[i];
	REP(i, 1, k)
		if (p[1] < p[i]) swap(p[1], p[i]), cnt ++;
	REP(i, 1, k) {
		cnt += T.ask(n) - T.ask(p[i]);
		if (!t[p[i]]) T.upd(p[i], 1), t[p[i]] = 1;
	}
	cout << cnt << " \n"[k == n];
}
```


## Part II

考虑在原来算出答案的序列 $\{a_{n}\}$ 最后加入一个数 $k$。

我们设 $t=\max\{a_{i}\}$。

如果 $k\leq t$，那么对第一次循环没有影响，正常处理即可。

如果 $k>t$，那么第一次循环时会把原来在 $a_1$ 的 $t$ 放到最后，然后把 $a_1$ 改成 $k$。设原序列中 $t$ **第二次**出现在 $p$。对于 $[1,p-1]$ 中的数，把 $t$ 拿走又加入 $k$，交换次数不变。对于 $[p,n]$ 中的数，因为前面的 $t$ 不止一个，加入 $k$ 后 $t$ 仍然有贡献，每个位置的交换次数都会加 $1$。

简单维护即可。

```cpp
Fenwick<int> T(n);
vector<int> vis(n + 1);
LL res = 0, p = 0, cnt = 0;
REP(i, 1, n) {
	if (!vis[a[i]]) T.upd(a[i], 1), vis[a[i]] = 1;
	if (i > 1 && a[i] == a[1]) p = 1;
	if (a[1] < a[i])
		res += cnt + 1, cnt = p = 0, swap(a[1], a[i]);
	cnt += p, res += T.ask(n) - T.ask(a[i]);
	cout << res << " \n"[i == n];
}
```


---

## 作者：spider_men (赞：2)

对于序列的每一个数，都需要询问一次而且该数后面的数对结果没有影响，故考虑插入法。

若当前插入的数小于当前最大值，则到最后一轮之前该数都不会对结果有影响，最后一轮的影响则为前面比它大的数的个数，这里用两个树状数组维护即可。

如果相等，则始终不会对结果产生影响。

代码:
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e5 + 9;
int T, n, cnt, flag, maxn;
LL ans;
int a[N],c[N],vis[N];
int lowbit(int x)
{
	return x&(-x);
}
void Add(int x)
{
	while(x<=n)
	{
		c[x]++;
		x+=lowbit(x);
	}
}
int Sum(int x)
{
	int tot=0;
	while(x)
	{
		tot+=c[x];
		x-=lowbit(x);
	}
	return tot;
}
void solve()
{
	cin>>n;
	memset(c,0,sizeof(int)*(n+9));
	memset(vis,0,sizeof(int)*(n+9));
	maxn=cnt=flag=0; ans=0;
	for(int i=1;i<=n;i++)
		cin>>a[i],maxn=max(maxn,a[i]);
	cout<<ans;
	vis[a[1]]=1; Add(a[1]);
	for(int i=2;i<=n;i++)
	{
		if(!vis[a[i]]) vis[a[i]]=1,Add(a[i]);
		if(a[i]==a[1]) flag=1; cnt+=flag-(flag?a[i]>a[1]:0);
		if(a[i]>a[1]) ans+=1+cnt,swap(a[1],a[i]),cnt=flag=0;
		ans+=Sum(a[1])-Sum(a[i]);
		cout<<" "<<ans;
	}
	cout<<"\n";
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}

```

---

## 作者：CashCollectFactory (赞：2)

派蒙很可爱，所以你要帮她**排序**！？

## 题目分析
对于每个长度的第一轮循环之后，结果是将其严格单增序列相对后移（这里的相对后移指的是单增序列的相对位置），之后第 $2,3…$ 轮排序的交换次数就是前 $i$ 个比 $a[i]$ 大的个数（去重）。
因此为了获得最后的解，在扫描的时候可以直接在线处理，保证每次只获得当前长度下第一次循环的结果，当遇到 $a[i]>a[1]$ 时，就交换 $a[i]$ 和 $a[1]$ 的位置，这就是一次必要的交换，计数器增加，然后对于每个在线处理录入的 $a[i]$，统计先前比它大的个数，直接加上即可。
但是，当录入的 $a[i]$ 与 $a[1]$（当前最大值）相等（假设值为 $x$）并且后面存在比 $a[1]$ 更大的数（假设值为$y$），那么在后面的长度当中，第一轮排序会使得当前的 $a[i]$ 的值不变，而 $a[1]$ 对应的值被移到了更大的数位置上，就是这样的情况：$x,x,y \rightarrow y,x,x$，那么在插入 $y$ 之后，由于 $y$ 前移了，$y$ 对 $x$ 也有一个需要交换的贡献，举例如下，假设当前长度构造的序列为：$x,a,a,a,x,x−1,x−2,x−1$，那么插入 $y$ 之后，由于 $y$ 大于 $x$，则变为了：$y,a,a,a,x,x−1,x−2,x−1,x$。那么对于 $x,x−1,x−2,x−1$ 这几个数，都需要加上 $y$ 与 $y$ 的这个贡献，所以需要增加一个计数器，记录第二个 $x$ 到 $y$ 间有几个数，插入 $y$ 的时候结果加上计数器值即可。

接下来的分析由陈靖邦老师完成。

**序列所有元素各不相同的情况：**

首先从第一个元素开始，找到并跳到当前元素右边第一个比它大的元素。称这些元素为“特殊元素”。可以发现外层循环的第一轮会把所有特殊元素“右移”一位，此时序列中最大的元素就到了序列第一个。

从外层第二轮循环开始，对于第 $i$ 轮循环，序列前 $(i - 1)$ 个元素已经是有序的。设此时第一个比 $a_i$ 大的元素是 $a_k$ ，那么第 $i$ 轮循环将会发生 $(i-k)$ 次交换。因此，非特殊元素将会贡献“前面有几个数比它大”次交换（注意一开始特殊元素的右移对答案没有影响，因为虽然移走了一个比它大的元素，但是最大的元素移到了开头），而特殊元素将会贡献 $2$ 次交换。

**存在相同元素的情况：**

对于非特殊元素，前面比它大的，但是相同的元素只会发生一次交换，因此需要对元素去重一下再统计。另外，如果这个非特殊元素恰好等于上一个特殊元素，那么上一个特殊元素的右移会导致该非特殊元素的贡献增加 $1$。

实际解题过程中，由于暴力程序非常简单，可以考虑通过对拍发现并调整```corner case```。

## 代码实现
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,a[maxn],T,tree[maxn];
bool vis[maxn];
int lowbit(int x){
    return x&(-x);
}
void Add(int x){
    for(int i=x; i<=n; i+=lowbit(i)) tree[i]++;
}
int Sum(int x){
    int ans=0;
    for(int i=x; i; i-=lowbit(i))
        ans+=tree[i];
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        int res=0,cnt=0;
        bool flag=0;
        memset(tree,0,sizeof(tree));
        memset(vis,0,sizeof(vis)); //初始化
        
        for(int i=1; i<=n; i++) cin>>a[i]; //读入 
        cout<<0; //第一个结果
        
        vis[a[1]]=1; //代表已经访问过
        Add(a[1]); //加进来
        for(int i=2; i<=n; i++){
            if(!vis[a[i]])vis[a[i]]=1,Add(a[i]); //未访问插入
            if(a[i]==a[1])flag=1; //标记存在多个最值
            cnt+=flag-(flag?a[i]>a[1]:0); //未统计的贡献
            if(a[i]>a[1])res+=1+cnt,swap(a[1],a[i]),cnt=flag=0; //a[1]永远只存最大的数字
            res+=Sum(a[1])-Sum(a[i]); //在i之前出现的比a[i]大的数字个数
            cout <<" "<<res;
        }
        cout<<endl;
    }
    return 0;
}
```
（~~【中文标点符号】与【英文、数字、公式或汉字】之间没有添加多余空格啊QAQ~~）

---

## 作者：Frozen_Ladybug (赞：0)

### 题目大意

题目中给出了一段排序的伪代码。现对于一个长度为 $n$ 的数组，输出 $n$ 个数，第 $i$ 个代表队前 $i$ 个数用该算法排序需要执行多少次操作。

### 分析

对于题目中给的算法，对于长度为 $n$ 的数组，共执行 $n$ 次排序，其中第一次单独处理，即不需要排序输出 ```0```。

之后的每一轮，对于第 $i$ 轮就是将最大数放置在 $i$ 号位置中，且前 $i-1$ 个数呈升序排列。本质就是一个 $\max$ 序列循环右移即可。

### 解法

借助树状数组可以 $O(n\log n)$ 求出某一长度数组的交换次数。题目中要求的是 $1$ 至 $n$ 分别的交换次数，想到从长度为 $i-1$ 推 $i$。取前 $i-1$ 个数的最大值记为 $M$。

- 如果 $a_i\leq M$，那么第一轮遍历时 $a_i=M$，所以第一轮两数组操作相同，交换次数也相同。

	实际上第二轮到第 $i-1$ 轮都完全一样，差别在于长度为 $i$ 的数组还需要进行第 $i$ 轮遍历。此时前 $i-1$ 个数都已经升序排列了，需要交换的次数就是前 $i-1$ 个数中去重后大于 $a_i$ 的数个数，这个值用树状数组很容易获得。

- 若 $a_i>M$，且 $M$ 在前 $i-1$ 个数中只出现一次时，其实两数组操作不同只在第一轮和最后一轮，长度为 $i$ 的数组会在这两轮分别多一次交换操作。

- 若 $a_i>M$，且 $M$ 出现次数不止一次时，中间轮次还会遇到 $M$，在长度为 $i-1$ 的数组中此时是不计算交换的。

	其余的 $M$ 不会和前面的 $M$ 再发生交换，而长度为 $i$ 的数组中，第一轮是将比 $M$ 还大的 $a_i$ 加入了有序序列，中间轮次遇到 $M$ 的时候都会发生交换。也就是这种情况下交换次数是 $2$ 加上第二个 $M$ 后面的数个数。

代码中，将 $\text{lowbit}(x)$ 记作 $k$，则 $k=\lfloor\log_2x\rfloor$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) x&(-x)//见上面解释
using namespace std;
ll a[100005],c[100005],n,mx[100005],num[100005],pos[100005];
void adde(int pos,int val){
	for(int i=pos;i<=n;i+=lowbit(i))
		c[i]+=val;
}//从当前到所需值叠加
ll sum(int pos){
	int ans=0;
	for(int i=pos;i>=1;i-=lowbit(i)) ans+=c[i];
	return ans;
}//求1到pos的区间和
int main(){
	ll T;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) num[i]=0,pos[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			c[i]=0;
			if(i==1) mx[i]=a[i];
			else mx[i]=max(mx[i-1],a[i]);
		}//mx表示区间[1,i]的最大值
		int last=0;
		adde(a[1],1);
		printf("0");
		num[mx[1]]++;
		for(int i=2;i<=n;i++){
			if(a[i]>mx[i-1]){
				if(num[mx[i-1]]==1) last+=2;
				else last+=2+i-pos[mx[i-1]];
			}
			else last+=sum(n)-sum(a[i]);//区间[a[i],n]和
			if(sum(a[i])-sum(a[i]-1)==0) adde(a[i],1);
			if(a[i]==mx[i]){
				num[mx[i]]++;
				if(num[mx[i]]==2) pos[mx[i]]=i;
			}//a[i]是(其中一个)区间[1,i]最大
			printf(" %lld",last);
		}
		puts("");
	}
	return 0;
}
```

---

