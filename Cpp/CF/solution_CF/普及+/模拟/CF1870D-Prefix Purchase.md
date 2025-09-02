# Prefix Purchase

## 题目描述

You have an array $ a $ of size $ n $ , initially filled with zeros ( $ a_1 = a_2 = \ldots = a_n = 0 $ ). You also have an array of integers $ c $ of size $ n $ .

Initially, you have $ k $ coins. By paying $ c_i $ coins, you can add $ 1 $ to all elements of the array $ a $ from the first to the $ i $ -th element ( $ a_j \mathrel{+}= 1 $ for all $ 1 \leq j \leq i $ ). You can buy any $ c_i $ any number of times. A purchase is only possible if $ k \geq c_i $ , meaning that at any moment $ k \geq 0 $ must hold true.

Find the lexicographically largest array $ a $ that can be obtained.

An array $ a $ is lexicographically smaller than an array $ b $ of the same length if and only if in the first position where $ a $ and $ b $ differ, the element in array $ a $ is smaller than the corresponding element in $ b $ .

## 说明/提示

In the first test case, $ a_1 $ cannot be greater than $ 5 $ , and if we buy $ c_1 $ five times, we will run out of money, so $ a = [5, 0, 0] $ .

In the second test case, $ a_1 $ cannot be greater than $ 2 $ , but we can buy $ c_1 $ and $ c_2 $ once each (buying $ c_2 $ twice is not possible), so $ a = [2, 1] $ .

## 样例 #1

### 输入

```
4
3
1 2 3
5
2
3 4
7
3
3 2 1
2
6
10 6 4 6 3 4
7```

### 输出

```
5 0 0 
2 1 
2 2 2 
2 2 2 2 2 1```

# 题解

## 作者：Creeper_l (赞：10)

## 题意

给定一个长度为 $n$ 的序列 $ans$，初始值全部为 $0$。你一共有 $k$ 个硬币，你可以选择花 $a_{i}$ 个硬币来使 $ans_{1}$ 到 $ans_{i}$ 中的所有数加一。求最终能得到的 $ans$ 序列中字典序最大的一个。

## 思路

首先我们可以发现一个很显然的性质：如果满足 $a_{i}>a_{i+1}$ 的话，那么选 $i+1$ 位置一定比选 $i$ 位置更优。所以我们就可以先将 $a_{i}$ 赋值为 $\min(a_{i},a_{i+1})$，这样就可以避免掉上面所说的这种情况了。

又因为题目要求最终序列的字典序最大（靠前的数字最大），所以我们肯定要贪心的去先选前面的，即从 $a_{1}$ 开始选。但是我们会发现选完 $a_{1}$ 之后 $k$ 还会剩下一些，如果直接不管的话肯定不是最优的。所以我们就可以用 $k$ 剩下的这些值去将一些选 $a_{1}$ 的变成选 $a_{2}$ 的，且个数不变，这样既可以保证当前的字典序不变（选 $1$ 的个数没变），还可以让后面的字典序变大（选 $2$ 的个数变多）。那么这样操作一定是更优的。那么就可以算出选 $a_{2}$ 的数量就应该是：$(k-k \div a_{1} \times a_{1}) \div (a_{2}-a_{1})$。意思是用 $k$ 剩下的值除以每一次变化需要的代价。然后对于每一个 $a_{i}$ 都进行这样的操作就可以了。

但是这里有几个点需要注意：

- 因为除数不能为 $0$，所以当 $a_{i}=a_{i+1}$ 时，直接将 $ans_{i}$ 赋值为 $ans_{i-1}$ 就可以了。

- 根据题目定义，显然 $ans_{i+1}$ 不可能大于 $ans_{i}$，所以操作的时候还需要特判一下。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
#define inf_db 127
#define ls id << 1
#define rs id << 1 | 1
#define re register
#define endl '\n'
typedef pair <int,int> pii;
const int MAXN = 2e5 + 10;
int T,n,k,mn = 1e18,a[MAXN],ans[MAXN];
signed main()
{
	cin >> T;
	while(T--)
	{
		cin >> n;
		mn = ans[0] = 1e18;
		for(int i = 1;i <= n;i++) cin >> a[i];
		for(int i = n;i >= 1;i--) mn = min(mn,a[i]),a[i] = mn; 
		cin >> k;
		for(int i = 1;i <= n;i++)
		{
			if(a[i] - a[i - 1] == 0) ans[i] = ans[i - 1];
			else ans[i] = min(k / (a[i] - a[i - 1]),ans[i - 1]);
			cout << ans[i] << " ";
			k -= (a[i] - a[i - 1]) * ans[i];
		}
		cout << endl;
		for(int i = 1;i <= n;i++) ans[i] = 0;
	}
	return 0;
} 
```






---

## 作者：Xy_top (赞：6)

一眼秒，首先根据常用套路，如果 $a_i\geq a_{i+1}$，那么直接删掉 $a_i$，最终剩下的一定是一个递增的序列，然后再来考虑怎么做。

首先全买最便宜的，然后再来考虑一个个退钱换东西就结束了。

但是注意，不能买了 $3$ 个退钱退 $5$ 个，所以还要取个 $\min$ 然后就过了，代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int T, n, k, tp = 1, t;
int a[200005], d[200005];
int tb[200005], loc[200005];
void solve () {
	tp = 1;
	cin >> n;
	For (i, 1, n) d[i] = 0;
	For (i, 1, n) cin >> a[i];
	cin >> k;
	tb[1] = a[1];
	loc[1] = 1;
	For (i, 2, n) {
		while (tp && a[i] <= tb[tp]) -- tp;
		tb[++ tp] = a[i];
		loc[tp] = i;
	}
	int ex = 0, lst = 1000000000;
	For (i, 1, tp) {
		tb[i] -= ex;
		if (k < tb[i]) break;
		if (i != 1) d[loc[i - 1] ] -= min (lst, k / tb[i]);
		d[loc[i] ] += min (lst, k / tb[i]);
		lst = min (lst, k / tb[i]);
		k -= min (lst, k / tb[i]) * tb[i];
		ex += tb[i];
	}
	foR (i, n - 1, 1) d[i] += d[i + 1];
	For (i, 1, n) cout << d[i] << ' ';
	cout << '\n';
}
signed main () {
	cin >> T;
	while (T --) solve ();
	return 0;
}
```


---

## 作者：LIUYC_C (赞：2)

[题目链接。](https://www.luogu.com.cn/problem/CF1870D)

## 大体思路：

难吗，不难，但哥们吃了 6 发罚时。

首先一眼很明显的一个贪心，肯定是最小值可以更新最多的前缀，而且最小值越远越好，这样可以更新更多的点，然后肯定难免出现无法把 $k$ 完美利用的情况，因为可能会出现余数，于是我们可以选择比最小值跟大一些的在后面的数，且总和不超过 $k$，这样明显更优，可以看样例理解。

但是哥们傻就傻在没想到取了最小值的最小值之后还有可能出现余数，于是 wa 了六发，所以我们应该一直往后找到 $k$ 为 $0$ 的时候才停止，而不是只做一次。

具体来说，我们可以让前面更新的最大值是 $k/minl$，会出现 $k\bmod minl$ 这么多余数，$minl$ 就是之前所说的最小值， 因此在最小值前的可以被更新的值已经固定，我们只是希望可以让最小值后方的数可以变大点，因此我们用 $l,r$ 来记录一下上次最小值的位置和当前最小值的位置，然后更新这段区间就好了。

更新多少呢？开个变量 $pre$ 记录一下我上一次取的最小值是啥，这样可以更新的值就是 $k/(minl-pre)$ 了，做到 $k$ 为 $0$ 的时候停止。

小清新代码，你绝对看得懂。

## 代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=401010;
#define int long long 

int n;
int ans[N];
int c[N];
int sum[N];

void solve(){
   cin>>n;
   for(int i=1;i<=n;i++){
    sum[i]=0;
   }
   for(int i=1;i<=n;i++){
    cin>>c[i];
   }
   int k;
   cin>>k;
   int num=0,r=0;
   int pre=0;//一开始设为0
   int l=1;
   while(1){
        for(int i=l;i<=n;i++){
        	//这里是为了找到最大可以更新值和位置，其实就是minl
            if(k/(c[i]-pre)>=num){
                num=k/(c[i]-pre);
                r=i;
            }
        }
        k%=c[r]-pre;//k变为余数
        for(int j=l;j<=r;j++){
            sum[j]+=num;
        }
        if(!num){
            break;
        }
        l=r+1;//更新l
        if(l>n){
            break;
        }
        pre=c[r];
        num=0;
   }
   for(int i=1;i<=n;i++){
        cout<<sum[i]<<" ";
   }cout<<endl;
}


signed main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}   
```







---

## 作者：Augury (赞：2)

# CF1870D Prefix Purchase 题解

[CnBlogs链接](https://www.cnblogs.com/Augury/p/17718078.html)

## 题意

你有一个长为 $n$ 的数组 $a$，初始全为 $0$。

初始你有 $k$ 个硬币。你可以花费 $c_i$ 个硬币让 $a$ 数组 $[1,i]$ 的前缀的值 $+1$。你要保证自己的硬币数量始终非负。

问 $a$ 数组的字典序最大是多少。

## 思路

萌新竟然能切 D 了！！！

首先考虑 dp。记 $f_i$ 表示花费 $i$ 个硬币时，$a_1$ 最大是多少。但是要最大化字典序，所以我们需要尽可能选 $i$ 较大的 $c_i$。所以我们记 $g_i$ 表示 $f_i$ 是用哪种硬币转移过来的。跑完全背包即可。复杂度 $O(nk)$。

发现这样复杂度过于炸裂。我们考虑 dp 做的是什么，就是优先选尽可能多的 $a_1$，然后尽可能多的选择 $a_2$，以此类推。

考虑如何选尽可能多的 $a_1$。肯定是选择全局最小值啊！考虑如何选尽可能多的 $a_2$。肯定是用后缀最小值替换掉上面对 $a_1$ 贡献的一些 $c$ 啊！所以我们用堆维护已经选过的 $c$，每次用 $c$ 的后缀最小值去尝试替换。

复杂度 $O(n\log n)$。

## 代码

萌新代码有点丑，大佬不要嫌弃

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int ans=0;bool op=0;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')op=1;ch=getchar();}
	while('0'<=ch&&ch<='9'){ans=(ans<<1)+(ans<<3)+(ch^48);ch=getchar();}
	if(op)return -ans;
	return ans;
}
const int maxn=2e5+10;
int n,k;
int c[maxn];
int mn[maxn];//c的后缀最小值的下标
int a[maxn];//最终形成的序列
struct node{
	int val,cnt,id;//这个c的权值、数量、编号
	bool operator < (const node &cmp)const{
		return val<cmp.val||(val==cmp.val&&id>cmp.id);
	}
};
priority_queue<node>q;
void real_main(){
	//read
	n=read();
	for(int i=1;i<=n;i++)c[i]=read();
	k=read();
	//init
	//清空
	while(!q.empty())q.pop();
	memset(a,0,sizeof(int)*(n+2));
	mn[n]=n;
	for(int i=n-1;i>=1;i--)mn[i]=c[i]<c[mn[i+1]]?i:mn[i+1];//处理后缀最小值的下标
	q.push((node){0,(int)2e9,0});//加一个0，方便处理
	//solve
	for(int i=1;i<=n;i++){
		node awa=(node){c[mn[i]],0,mn[i]};
		while(!q.empty()){
			node now=q.top();q.pop();
			int dif=c[mn[i]]-now.val;
			if(!dif){//如果不用替换，那么直接退出
				q.push(now);//拿出来的没有动，放回去
				break;
			}
			int tmp=min(k/dif,now.cnt);//计算一下可以替换掉几个
			now.cnt-=tmp;
			awa.cnt+=tmp;
			a[now.id]-=tmp;
			a[mn[i]]+=tmp;
			k-=dif*tmp;
			if(now.cnt)q.push(now);
			if(!tmp)break;//已经不能替换了，退出
		}
		if(awa.cnt)q.push(awa);
	}
	for(int i=n;i>=1;i--)a[i]=a[i+1]+a[i];//我们的a是一个后缀和，算出来
	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
	puts("");
}
signed main(){
	int T=read();//多组数据
	while(T--)real_main();
	return 0;
}s
```

---

## 作者：y_kx_b (赞：2)

赛时秒了，但是没有注意到可能会出现 $a_i<a_{i+1}$，wa2，40min 后群友指出了问题。还是太菜了。

题意：长为 $n$ 的 $a$ 初始均为 $0$，每次操作选定一个 $i$ 花费 $c_i$，然后让 $a_1\sim a_i$ 所有元素 $+1$，问花费不超过 $k$ 的情况下 $a$ 最大字典序，输出 $a$ 序列。$n\leqslant2\times10^5$，$1\leqslant c_i,k\leqslant10^9$。

首先我们做一个等价变换：$c_i\gets \min(c_{i\sim n})$，因为如果 $i$ 后面操作花费反而更少的话那么我们可以直接把 $c_i$ 扔掉了（因为不优），这个后缀 $\min$ 的作用就是让 $c_i$ 单调不降，快速算出 $a_i$ 的最大值。怎么算呢？

我们首先贪心地只考虑 $i=1$ 的操作，显然 $a_1=\lfloor\frac k{c_1}\rfloor$。那么我们让 $k\gets k-a_1\times c_1$，接着考虑 $a_2$。我们发现，只买 $i=1$ 可能是不太划算的，所以我们 **在 $a_1$ 不变的基础上** 把若干 $i=1$ 的操作变成 $i=2$ 的操作，每变一次需要多花的代价为 $c_2-c_1$，因为我们要保证 $a_1$ 不变的前提下让 $a_2$ 尽可能大，所以能变就变，$a_2=\lfloor \frac k{c_2-c_1}\rfloor$。后面的位也是同理。

如果真这样写会喜提样例 RE，发现问题是 $c_{i+1}-c_i$ 有可能是 $0$。这时显然我们需要把 $a_i$ 次操作全部从 $i$ 转移到 $i+1$，即 $a_{i+1}=a_i$。然后样例全过，但是 wa2。**问题在于，如果 $c_{i+1}-c_i$ 不为 $0$，还是有可能出现 $a_{i+1}>a_i$ 的情况：我们反悔了 $a_{i+1}$ 次操作，却没有考虑到底第 $i$ 位是否真的有这么多操作可以转移。** 解决方法很简单，只要 $a_{i+1}\gets\min(a_{i+1},a_i)$ 就好了（）。撒花！

[code](https://codeforces.com/contest/1870/submission/223900684)。

---

## 作者：BINYU (赞：2)

## 题意

有一个初始全为 $0$ 的长度为 $n$ 的数组 $a$，你可以花费 $c_i$($1 \le i\le n$)的代价让 $a_1$ 至 $a_i$ 增加 $1$，求在花费不超过 $H$ 代价的前提下得到的字典序最大的 $a$。

## 思路

~~差分维护每一次操作都能想到吧~~

首先有一个非常显然的性质：

$\forall  1 \le i \le j \le n$ 若有：

$c_i \ge c_j$

则 $c_i$ 永远不可能选，我们可以用单调栈来处理这部分，剩下来的部分一定单调递增，设剩下来的下标集合为 $s$（大小为 $|s|$）。

因为要使字典序最大，所以要让 $a_1$ 尽可能地大，又因为每次操作都能让 $a_1$ 加 $1$，所以要让每次操作的代价尽可能地小，考虑全选 $c_{s_1}$，一定能让 $a_1$ 的值取到最大，设剩下来的代价为 $h_1$，我们考虑尽量去利用它，同上面的贪心策略，考虑将尽可能多的 $c_{s_1}$ 转换为 $c_{s_2}$，一定能在**保证 $a_1$ 至 $a_{s_1}$ 取到最大的前提下**让 $a_{s_1 + 1}$ 取到最大……

以此类推，我们得到了完整的贪心策略：在总代价不超过 $H$ 的前提下，先**尽可能的**选 $c_{s_1}$，再**尽可能的**将 $c_{s_1}$ 转换为 $c_{s_2}$ （即补上代价差），直到转换到 $c_{s_{|s|}}$ 为止。

细节：每次转换的数量一定不能超过上一次转换（可以把选 $0$ 看做一种可执行无限次的操作）的个数。

---

## 作者：ivyjiao (赞：0)

来源：CF 决斗场。

先看标签：贪心，模拟，排序（这个其实没有）。

我一开始想成优先加后面了，被硬控半小时，被羞辱了，输。

考虑这个东西比较难维护，考虑把这个东西转成只维护 $ans_i$，而不是它的后缀和。

一个很经典但是我不知道的 trick：注意到 $a_i\geq a_{i+1}$，那么我们可以把它删了，这里我们将其写作 $a_i=\min_{j=i+1}^n a_j$。

此时该序列单调不增，所以直接全选 $1$，此时 $ans_1=\lfloor\dfrac{k}{a_1}\rfloor,k=k-ans_1\times a_1$，此时 $k$ 还剩一点，我们在拿 $k$ 去全选 $a_2$，此时是要拿选 $1$ 的数加上 $a_2-a_1$ 的代价来补上 $2$，所以 $ans_2=\min(ans_1,\lfloor\dfrac{k}{a_2-a_1}\rfloor),k=k-ans_2\times (a_2-a_1)$，以此类推 $ans_3=\min(ans_2,\lfloor\dfrac{k}{a_3-a_2}\rfloor),k=k-ans_3\times (a_3-a_2),ans_i=\min(ans_{i-1},\lfloor\dfrac{k}{a_i-a_{i-1}}\rfloor),k=k-ans_i\times (a_i-a_{i-1})$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+1;
int t,n,k,a[N],ans[N],minn;
signed main(){
    cin>>t;
    while(t--){
        memset(ans,0,sizeof ans);
        minn=ans[0]=1e18;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=n;i>=1;i--){
            minn=min(minn,a[i]);
            a[i]=minn;
        }
        cin>>k;
        for(int i=1;i<=n;i++){
            if(a[i]==a[i-1]) ans[i]=ans[i-1];
            else ans[i]=min(k/(a[i]-a[i-1]),ans[i-1]);
            k-=ans[i]*(a[i]-a[i-1]);
        }
        for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
        cout<<endl;
    }
}
```

---

## 作者：CountState (赞：0)

CF 决斗场 被硬控 $21$ 分 $29$ 秒。

打的时候一直想用排序后差分做，但是过不去样例。

考虑只维护 $ans_i$ 而不是维护差分数组，我们可以将 $a_i$ 转化为 $a_i$ 到 $a_n$ 的后缀最小值。易知此时 $a$ 数组代表 “给序列的第 $1\sim i$ 位 $+1$ 所消耗的最小代价”。

那么我们就可以维护 $ans$ 了，当 $i=1$ 时，即维护 $ans$ 的第一位，我们只需将手中所有的 $k$ 全部加给第一位即可，所以有 $ans_i=\lfloor\dfrac{k}{a_i}\rfloor$，剩余的 $k=k-\lfloor\dfrac{k}{a_1}\rfloor\times a_1$，即 $k=k-ans_1\times a_1$。

#### 现在考虑第 $i$ 位：

当 $a_i \neq a_{i-1}$ 时，显然有 $a_{i-1} \leq a_i$，我们可以考虑消耗 $a_i-a_{i-1}$ 代价，将$a_i$ 升级为 $a_{i-1}$。这么做之后 $ans_{i-1}$ 不变，$ans_i$ 变大，肯定更优。

当 $a_i=a_{i-1}$ 时，因为把 $k$ 给到第 $i$ 位和第 $i-1$ 位的代价是相同的，所以把 $k$ 给到第 $i$ 位，又因为它们代价相同，所以 $ans_i=ans_{i-1}$。

可以这么理解，因为我把 $k$ 给到了 $ans_i$ 而没有给 $ans_{i-1}$，所以 $ans_{i-1}$ 相当于没有产生作用，可以删掉，那么此时的第 $i$ 位就相当于原来的第 $i-1$ 位，所以有 $ans_i=ans_{i-1}$。

转移完这一位之后，剩余的 $k=k-ans_i\times a_i$，继续转移可以得出所有的 $ans_i$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T,n,k,ans[N],a[N],minn;
int main(){
    cin>>T;
    while(T--){
    	cin>>n;
    	memset(ans,0,sizeof ans);
    	ans[0]=INT_MAX;
    	minn=INT_MAX;
    	for(int i=1;i<=n;i++) cin>>a[i];
    	cin>>k;
    	for(int i=n;i>=1;i--) minn=min(minn,a[i]),a[i]=minn;
    	for(int i=1;i<=n;i++){
    		if(a[i]==a[i-1]) ans[i]=ans[i-1];
    		else ans[i]=min(k/(a[i]-a[i-1]),ans[i-1]);
    		k=k-(a[i]-a[i-1])*ans[i];
    		cout<<ans[i]<<" ";
    	}
    	cout<<"\n";
    }
    return 0; 
}
```

---

## 作者：huangrenheluogu (赞：0)

相同的价格，选后面的显然更优。

先买最便宜的，多出的部分可以换成后面的更贵的。

当然，换的数量不能太多，所以要取 $\min$。

```cpp
for(int i = 1; i <= cnt; i++){
	if((tem = f[num[i]]) < now) continue ;
	if(k < num[i] - las) break ;
	tem1 = min(k / (num[i] - las), a[now]);//*
	a[now] -= tem1;
	a[tem] += tem1;
	k -= (num[i] - las) * tem1;
	las = num[i], now = tem;
}
```

解释一下注释的地方为什么只用和前面取。

因为如果和 $i-2$ 取了，那么说明 $i-1$ 就没有用到。

可是，如果 $i-1$ 都换不掉，为什么 $i$ 会换掉，注意这里 $num_i >num_{i-1}$，和 $num_{i-2}$ 的差值是更大的，所以换不掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int T, n, c[N], num[N], cnt, k, ans, a[N], las, now, tem, tem1;
unordered_map<int, int>f;
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		f.clear();
		cnt = 0;
		for(int i = 1; i <= n; i++){
			scanf("%d", &c[i]);
			if(f[c[i]] == 0) num[++cnt] = c[i];
			f[c[i]] = i;
			a[i] = 0;
		}
		scanf("%d", &k);
		sort(num + 1, num + cnt + 1);
		las = now = 0;
		a[0] = 1e9;
		for(int i = 1; i <= cnt; i++){
			if((tem = f[num[i]]) < now) continue ;
			if(k < num[i] - las) break ;
			tem1 = min(k / (num[i] - las), a[now]);
			a[now] -= tem1;
			a[tem] += tem1;
			k -= (num[i] - las) * tem1;
			las = num[i], now = tem;
		}
		for(int i = n - 1; i >= 1; i--){
			a[i] += a[i + 1];
		}
		for(int i = 1; i <= n; i++) printf("%d ", a[i]);
		putchar('\n');
	}
	return 0;
}
```

[评测链接](https://codeforces.com/contest/1870/submission/237126616)

---

## 作者：Halberd_Cease (赞：0)

抽象细节题，人均 +3。

除了细节还是比较简单的，说一下大概的思路。

一次改动就是改从 $1$ 到 $i$ 的所有值，那么如果存在有 $i<j$ 且 $c_i>c_j$ 肯定不选 $i$，改的少还要多花钱。

如果存在有 $i>j$ 且 $c_i<c_j$，肯定选。

字典序最大就是要首位最高，所以我们应该先全部买（这里的买是计划不是实际买）价格最低的，然后把购买方案按价格从低到高，影响范围从小到大排序，由于前面的证明，第一种情况因为不满足单调所以不可能选到，第二种因为我们最开始选的是最便宜的，所以不会出现更便宜的情况，也被排除。

然后我们就将剩下的方案比较，在不影响第一位的情况下，也就是购买的总数不变，尽量多买影响范围大的，具体就是少买一个范围小的，然后换购一个范围大的，贪心下来就可以得到答案了。

由于我们记录的是买的方案，而要求输出得到的结果，用后缀和从后往前累加就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int c, id;
    friend bool operator<(Node x, Node y)
    {
        return x.c == y.c ? x.id < y.id : x.c < y.c;
    }
} a[200010];
int b[200010];
int tag[200010];
void work()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n, k;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].c;
        a[i].id = i;
        tag[i] = 0;
    }
    cin >> k;
    sort(a + 1, a + n + 1);
    tag[a[1].id] += k / a[1].c;
    k %= a[1].c;
    int la = 1;
    for (int i = 2; i <= n; i++)
    {
        if (a[i].id < a[la].id)
            continue;
        int cha = a[i].c - a[la].c;
        if(cha==0)
        {
            tag[a[i].id]+=tag[a[la].id];
            tag[a[la].id]=0;
            la=i;
            continue;
        }
        int much = k / cha;
        much=min(much,tag[a[la].id]);
        k -= cha*much;
        tag[a[la].id] -= much;
        tag[a[i].id] += much;
        la=i;
    }
    int sum = 0;
    for (int i = n; i >= 1; i--)
    {
        sum += tag[i];
        b[i] = sum;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << b[i] << ' ';
    }
    cout << endl;
}
signed main()
{
    int t;
    cin >> t;
    while (t--)
        work();
}
```

---

## 作者：qwq___qaq (赞：0)

首先肯定是让加的次数最多的，现在我们令最靠右的最小的 $c$ 的位置 $pos$，那么次数显然就是 $\lfloor\dfrac{k}{c_{pos}}\rfloor$。我们记剩下的 $k$ 为 $k'$，现在问题转化为如何将增加的指针向右移动。

首先 $pos$ 以左肯定是不可能的，因为 $a_{pos}$ 的值会变小。然后，贪心地，我们肯定是先在右边选择能让 $a_{pos+1}$加最多的位置，于是我们可以再求出 $[pos+1,n]$ 的最小的最靠右的 $c$ 的位置 $pos'$ 那么现在 $a_{pos+1}$ 的增加次数显然是 $tot=\lfloor\dfrac{k'}{c_{pos'}-c_{pos}}\rfloor$。

然后由于 $pos$ 的定义是最靠右的最小的 $c$，所以显然 $c_{pos'}-c_{pos}\ne 0$。

$\Delta$ 注意这里 $a_{pos'}$ 的增加次数必须不超过 $a_{pos}$ 的增加次数，所以 $tot\gets \min\{a_{pos},tot\}$。

然后显然 $tot=0$（不会再增加）或者 $pos=n$（整个序列都增加完了）的时候就不需要再增加了。

由于 $pos\in[1,n]$，所以 $pos$ 最多移动移动 $n$ 次，每次求 $\min$ 用 ST 表或者线段树维护都可以做到 $O(n\log n)$。

虽然但是，刚刚看了眼题解区，突然发现，因为每个区间都是 $[i,n]$ 的最小的最靠右的 $c$，所以可以用后缀 $\min$ $O(n)$ 地维护。

---

## 作者：Wf_yjqd (赞：0)

现在次次卡 D，然后比完赛也没改啥思路，重构一遍就过了。不知道咋办。

------------

将同一个位置的多次操作看成一次操作。

显然需要从前到后依次最大化每个位置上的数。

考虑枚举位置，并尝试用这个位置代替前一次操作的位置，这样就能在不影响再往前的答案的情况下，最大化后面的答案。

如果无法代替，说明前一次操作向后的影响已经最优，那就增加一次操作最大化下一个位置。

WA2 后发现一个问题：可能存在代替上一次操作的方案前出现不能代替的方案，导致误认为操作已经最优。

所以考虑去掉一定不优的情况，即将每个位置的代价改为后缀最小值。

------------

复杂度 $\operatorname{O}(n)$，也是挺好写的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,c[maxn],k,top,ans[maxn];
pair<int,int> cz[maxn];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&c[i]);
            ans[i]=0;
        }
        scanf("%d",&k);
        for(int i=n-1;i>=1;i--)
            c[i]=min(c[i],c[i+1]);
        top=1;
        cz[1]={1,k/c[1]};
        for(int i=2;i<=n&&k;i++){
            if(k/c[i]>=k/c[i-1])
                cz[top]={i,k/c[i]};
            else{
                top++;
                cz[top]={i,(k%c[cz[top-1].first])/(c[i]-c[cz[top-1].first])};
                cz[top-1].second-=cz[top].second;
                k-=cz[top-1].second*c[cz[top-1].first];
            }
        }
        for(int i=1;i<=top;i++){
            ans[1]+=cz[i].second;
            ans[cz[i].first+1]-=cz[i].second;
        }
        for(int i=1;i<=n;i++){
            ans[i]+=ans[i-1];
            printf("%d ",ans[i]);
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：2020kanade (赞：0)

离杀掉 D 最近的一次。

首先考虑字典序最优的要求：靠前的数应当尽量大。

所有可以执行的操作都是前缀加 $1$，因此第一个数每次操作一定是会被照顾到的，考虑它最大的情况：操作次数最多。显然，找到最小的 $c_i$，全买这个就可以做到。

在保证操作次数的同时，为了更优的字典序，需要把一些操作放到后面的位置上。一个显然的结论是，一个位置的花费如果比它右面的某个位置的花费还贵，那就没有必要选这个。因此，对刚才找到的最小的 $c_i$ 的位置为起点的后缀做个 $c_i$ 关于 $i$ 严格单调递增的单调栈，栈里留下来的都是决策参考点。

继续贪心。首先要明白，放到后面的操作的最大数量的优先级大于放到后面的操作的最大长度，不能理解者请反复阅读字典序定义。因此，我们从左往右进行决策，注意决策集合的费用关于位置单调，因此一定可以保证尽可能多的操作往后移。~~说句闲话，这也是标题的来源。~~

至于能移动多少个，费用怎么搞，费用直接作差算出增量，个数用整除性质算。

以及，每次移动的时候，只考虑移动上一次移动过的部分就行了，因为我们维护的是费用增量，相当于把等价的一组点里的若干个试图不断向右移。

最后统计答案怎么都行，我用的是差分之后前缀和。

语言可能比较抽象，具体思路可能代码更清晰一点：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+1;
int n,k,c[N],ti[N],t,mxti,a[N],adi[N],micpos,mic=1e9+1;
using ip=pair<int,int>;
deque<ip> q;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;q.clear();mic=1e9+2,micpos=0;
		for(int i=1;i<=n;++i) cin>>c[i],mic=min(mic,c[i]);
		cin>>k;
		for(int i=1;i<=n;++i) if(c[i]==mic) micpos=max(i,micpos);
		mxti=k/mic;
		for(int i=micpos;i<=n;++i)
		{
			
			while(!q.empty()&&q.back().first>=c[i]) q.pop_back();
			q.push_back(make_pair(c[i],i));
		}
		while(!q.empty()&&q.front().second==micpos) q.pop_front();
		int rmi=mxti,lsk=k%mic;
		ti[micpos]=mxti;int nmic=mic,nicpos=micpos;
		while(!q.empty()&&lsk>0)
		{
			int pos=q.front().second;q.pop_front();
			rmi=min(rmi,lsk/(c[pos]-nmic));
			ti[pos]=rmi,ti[nicpos]-=rmi;
			lsk-=(c[pos]-nmic)*rmi;
			nmic=c[pos],nicpos=pos;
		}
		for(int i=1;i<=n;++i) adi[1]+=ti[i],adi[i+1]-=ti[i];
		for(int i=1;i<=n;++i) a[i]=a[i-1]+adi[i];
		for(int i=1;i<=n;++i) cout<<a[i]<<" ";cout<<endl;
		for(int i=0;i<=n+1;++i) c[i]=ti[i]=adi[i]=a[i]=0;
	}
	return 0;
}
```

---

