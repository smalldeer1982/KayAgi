# Inferno

## 题目背景

> 我是幽灵。  
> 穿过悲惨之城，我落荒而逃。  
> 穿过永世凄苦，我远走高飞。

沿着阿尔诺河的堤岸，我夺路狂奔，气喘吁吁……左转上了卡斯特拉尼大街，一直朝北而行，始终隐蔽在乌菲兹美术馆的阴影之下。

但他们还是穷追不舍。

他们的脚步声越来越响，这些追捕者冷酷无情，不达目的绝不善罢甘休。

这么多年来，他们一直尾随着我。他们锲而不舍，是的我只能活在地下……被迫呆在炼狱之中……就像冥府的恶魔，时刻忍受地狱的煎熬。

> 我是幽灵。

如今浮生尘世，我举目北望，却看不到通往救赎的捷径——那高耸的亚平宁山脉挡住了黎明的第一缕阳光。

## 题目描述

罗伯特 · 兰登在洗下但丁死亡面具上的丙烯石膏后，在背面发现了一行字：

> 哦，有着稳固智慧的人啊，  
> 请注意这里的含义  
> 就藏在晦涩的序列面纱之下。

下面有一行由 $1,-1$ 组成的长度为 $n$ 的序列。面具经受了岁月的侵蚀，序列中有一些数已经模糊不清。幸运的是，面具下面有给出两条线索：

> 你只得往空缺的位置填 $k$ 个 $1$，其余填入 $-1$，需要最大化这个序列的最大子段和。

 > > **一个序列的最大子段和定义为，其在一段连续长度的区间内的最大和。形式化地，一个序列 $a$ 的最大子段和即为 $\max\limits_{l=1}^n\max\limits_{r=l}^n\left(\sum\limits_{i=l}^r a_i\right)$。**

罗伯特 · 兰登希望在瘟疫扩散之前找到有关的线索。于是他找到了你。

- - -

#### 【形式化题意】

给定一个只包含 $-1,0,1$ 的序列，求出往 $0$ 的位置上填 $k$ 个 $1$，其余填 $-1$ 后最大子段和的最大值。

## 说明/提示

#### 【样例解释】

一种可行的方案是填入 $\{1,1,-1\}$，最大子段和为 $2$。

#### 【数据范围】


**本题开启捆绑测试。**

| $\text{SubTask}$ | 分值 | $n,k\le $ |
| :----------: | :----------: | :----------: |
| $0$ | $4$ | $20$ | 
| $1$ | $6$ | $200$ | 
| $2$ | $10$ | $5\times 10^3$ | 
| $3$ | $30$ | $5\times 10^5$ | 
| $4$ | $50$ | $10^7$ | 


对于 $100\%$ 的数据，$1\le n,k\le10^7$，$a_i\in \{-1,0,1\}$。保证 $k\le$ 序列中 $0$ 的个数。

**本题标程使用优化后的输入输出，在 O2 优化下最大点用时约 $350$ ms，足以通过此题。如果您自认为您的程序复杂度正确，却超出时间限制，请使用更优的输入输出方式，或者优化常数。**


## 样例 #1

### 输入

```
5 2
1 0 -1 0 0```

### 输出

```
2```

# 题解

## 作者：cyffff (赞：9)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8945)

第一次 $\text{AK div.2}$，水个题解不过分吧（
## 题意
给一个仅包含 $-1,0,1$ 的序列 $a$。在为 $0$ 的位置中选 $k$ 个更改为 $1$，其余更改为 $-1$，使得最大子段和最大，求最大子段和的最大值。

$k\le n\le 10^7$。
## 思路
看数据范围像几个前缀和就做完了。

枚举左端点减一，设为 $i$。考虑右端点 $j$。

记原序列前缀和为 $pr_i$。

我们考虑定义 $c$ 表示 $[i,j]$ 中 $0$ 的数量。我们肯定尽可能填 $1$，再填 $-1$，则对 $c$ 的大小分类讨论：
- $c\le k$，这段的子段和为 $pr_j-pr_i+c$；
- $c>k$，这段的子段和为 $pr_j-pr_i+2k-c$。

我们定义 $pos_i$ 为第 $i$ 个 $0$ 的位置，$l_i$ 为 $i$ 左方（不含 $i$）的最后一个 $0$ 是第几个 $0$。则当 $j\in(i,pos_{l_i+k+1})$ 时 $c\le k$，$j\in[pos_{l_i+k+1},n]$ 时 $c>k$。

考虑将 $c$ 从式子中消掉。我们定义 $p_{-1,i}$ 表示将 $0$ 全部换为 $-1$ 后的前缀和，$p_{1,i}$ 表示将 $0$ 全部换为 $1$ 后的前缀和。则两种情况的答案分别变成了$p_{1,j}-p_{1,i}$ 和 $p_{-1,j}-p_{-1,i}+2k$。

对于后者，我们直接维护 $p_{-1,i}$ 的后缀 $\max$。对于前者，为一段区间求 $\max$，且左右端点单调不减，维护 $p_{1,j}$ 的单调队列即可。注意边界问题。

时间复杂度 $O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e7+10;
int n,k,a[N],bel[N],cnt,pos[N],ans,pm[N],sm[N],p0[N],p1[N];
struct node{
	int v,p;
}stk[N];
int hd=1,tl;
int main(){
	n=read(),k=read();
	for(int i=1,las=0;i<=n;i++){
		a[i]=read();
		bel[i]=las;
		if(a[i]){
			p0[i]=p0[i-1]+a[i];
			p1[i]=p1[i-1]+a[i];
		}else{
			p0[i]=p0[i-1]-1;
			p1[i]=p1[i-1]+1;
			pos[++cnt]=i,las=cnt;
		}
	}
	pm[n+1]=sm[n+1]=-2e9;
	for(int i=n;i>=1;i--)
		pm[i]=max(pm[i+1],p1[i]),
		sm[i]=max(sm[i+1],p0[i]);
	for(int i=0,lp=1;i<=n;i++){
		while(hd<=tl&&stk[hd].p<i) hd++;
		int id=bel[i]+k+1;
		if(id>cnt) ans=max(ans,pm[i+1]-p1[i]);
		else{
			int np=pos[id];
			for(;lp<=np-1;lp++){
				while(hd<=tl&&stk[tl].v<p1[lp]) tl--;
				stk[++tl]={p1[lp],lp};
			}
			ans=max({ans,stk[hd].v-p1[i],sm[np]-p0[i]+2*k});
		}
	}
	write(ans);
	flush();
}
```
再见 qwq~

---

## 作者：LHQing (赞：5)

#### 思路分析


先对原数列做一遍前缀和得到 $s_i$，设对空位全部填 $1$ 的前缀和序列为 $p_i$，全填 $-1$ 的前缀和为 $q_i$，$0$ 个数的前缀和为 $c_i$。

考虑枚举最大子段的开头 $l$，则若要使最大子段和最大，后面 $k$ 个空都填 $1$。则此时有两种情况：

- 若取的右端点 $r$ 在 $k$ 个 $0$ 以内，那么其最大子段和为 $s_r-s_{l-1}+c_r-c_{l-1}=p_r-p_{l-1}$。

- 若取的右端点在 $k$ 个 $0$ 以外，则其最大子段和为 $s_r-s_{l-1}+2k-c_r+c_{l-1}=q_r-q_{l-1}+2k$。

于是我们维护 $q$ 的后缀最大值，然后 $p$ 使用单调队列维护区间最大值即可。

#### 题解代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

struct ios {
    inline char read() {
        static const int inlen = 1 << 18 | 1;
        static char buf[inlen], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, inlen, stdin)), s == t ? -1 : *s++;
    }
    template<typename T> inline ios& operator>> (T &x) {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
            if (c11 == -1) return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read()) x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} fin;

struct exios {
    template<typename _CharT, typename _Traits = char_traits<_CharT>>
    struct typ {
        typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
    };

    template<typename T> friend exios &operator<<(exios &out, T num) {
        if (num < 0) putchar('-'), num = -num;
        if (num >= 10) out << num / 10;
        putchar(num % 10 + '0');
        return out;
    }

    friend exios &operator<<(exios &out, const char * s) { printf("%s", s); return out; }
    friend exios &operator<<(exios &out, string s) { cout << s; return out; }
    friend exios &operator<<(exios &out, typ<char>::end e) { puts(""); return out; }
} fout;

const int maxn = 1e7 + 10;

int n, k, ans;
int a[maxn];
int c[maxn];
int s[maxn];
int p[maxn], q[maxn];
int suf[maxn];
int que[maxn], hd = 1, tl;
int rp = 1;

signed main() {
	fin >> n >> k;
	for (int i = 1; i <= n; i++) fin >> a[i], c[i] = c[i - 1] + !!!a[i], s[i] = s[i - 1] + a[i], p[i] = p[i - 1] + (a[i] ? a[i] : 1), q[i] = q[i - 1] + (a[i] ? a[i] : -1);
	memset(suf, -0x3f, sizeof(suf));
    for (int i = n; i; i--) suf[i] = max(suf[i + 1], q[i]);
	for (int i = 1; i <= n; i++) {
		while (hd <= tl && que[hd] < i) ++hd;
		while (rp <= n && c[i - 1] + k >= c[rp]) {
			while (hd <= tl && p[que[tl]] < p[rp]) --tl;
			que[++tl] = rp++;
		}
		ans = max(ans, max(suf[rp] - q[i - 1] + (k << 1), p[que[hd]] - p[i - 1]));
	}
	fout << ans << endl;
	return 0;
}

/*
5 2
1 0 -1 0 0
*/
```

---

## 作者：Forever1507 (赞：4)

绝世好题。

时间复杂度线性。

首先显然可以发现 $k$ 个 $1$ 一定在尽量放在一起的情况下最优，那么我设 $pos$ 表示第 $i$ 为前面第 $k$ 个 $0$ 的位置。

记两个值：$sum1_i$ 表示把 $0$ 全部当成 $1$ 时的前缀和，$sum2_i$ 表示把 $0$ 全部当成 $-1$ 时的前缀和。

那么以第 $i$ 位为结尾的最大子段和要么就是在内部取 $sum1_i-\min_{x \in [pos,i]}sum1_x$，要么在填 $-1$ 的地方还要加上一点，也就是 $sum1_i-sum1_{pos-1}+sum2_{pos-1}-\min_{x \in [0,pos-1]}sum2_x$

$\min_{x \in [pos,i]}sum1_x$ 这个东西因为下标是具有单调性的，所以可以把单调队列魔改一下线性解决。（我不会尺取，但是看了官方题解我觉得单调队列胜在好写！）

$\min_{x \in [0,pos-1]}sum2_x$ 这个东西可以前缀最小值算出来！

然后你把每个 $0$ 的位置记下来，在记下每个 $i$ 前面（包括自己）的第一个 $0$ 的位置就可以了！

要小心数组越界，因为 $i$ 前面不一定有 $k$ 个 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[10000005],lst[10000005],zero[10000005],cnt;
int sum1[10000005],sum2[10000005],mini[10000005];
void find_min(){//单调队列！
	deque<pair<int,int> >dq;
	for(int i=1;i<=n;++i){
		while(!dq.empty()&&sum1[i]<=dq.front().first)dq.pop_front();
		dq.push_front(make_pair(sum1[i],i));
		while(!dq.empty()&&dq.back().second<zero[max(0,lst[i]-k+1)])dq.pop_back();
		mini[i]=dq.size()?dq.back().first:0;
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	int lstt=0;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		sum1[i]=sum1[i-1];
		sum2[i]=sum2[i-1];
		if(a[i]==0){
			sum1[i]++;
			sum2[i]--;
			zero[++cnt]=i;
			lstt=cnt;
		}
		else{
			sum1[i]+=a[i];
			sum2[i]+=a[i];
		}
		lst[i]=lstt;
	}
	find_min();
	int maxn=1,minii=0;
	lstt=0;
	for(int i=1;i<=n;++i){//套公式
		int x=max(zero[max(0,lst[i]-k+1)]-1,0);
		for(int j=lstt;j<=x;++j)minii=min(minii,sum2[j]);
		lstt=x;
		int ans=max(sum1[i]-mini[i],sum1[i]-sum1[max(0,zero[max(0,lst[i]-k+1)]-1)]+sum2[max(zero[max(0,lst[i]-k+1)]-1,0)]-minii);
		maxn=max(maxn,ans);
	}
	cout<<maxn;
	return 0;
}
```


---

## 作者：SDLTF_凌亭风 (赞：3)

这次终于看懂了题解，但我还是想自己写篇题解梳理一下思路。

首先看看我们会什么，我会贪心：如果我想让最大子段和最大，我肯定会尽可能的把一串连续的 $0$ 变为 $1$，插入一个 $-1$ 一定很劣，因为他会把一串前缀和单调增的序列变的不单调增，而你的子段和可以这样理解：画出一个前缀和的函数图像，可以认为子段和就是在函数上任取两点的函数值相减的绝对值。如果你的前缀和函数是单调增的，那最大子段和就很显然；倘若你的出现一个负数，前缀和必定会下降，把区间断成两部分，这样一定很劣。

好的那我知道了，我现在可以去枚举最大子段和的左端点，然后往右边改 $k$ 个 $0$。但又一个问题，你不一定能改到 $k$ 个 $0$ ，于是分类讨论右端点是否在这 $k$ 个 $0$ 内部。如果在的话那很简单，用单调队列维护前缀和加上前缀 $0$ 的个数；如果不在就用前缀和减去前缀 $0$ 的个数。

于是一种可能的实现是这样的（部分代码）：
```cpp
s1[n + 1] = s2[n + 1] = -0x3f3f3f3f;
for(int i = n; i >= 1; --i)	s1[i] = max(s1[i + 1], pref1[i]), s2[i] = max(s2[i + 1], pref0[i]);
for(int i = 0, lpos = 1, nowpos, id; i <= n; ++ i) {
	for(; be <= ed && sta[be].second < i; ++ be);
	id = bel[i] + k + 1;
	if(id > cnt) ans = max(ans, s1[i + 1] - pref1[i]);
	else {
		nowpos = pos[id];
		for (; lpos <= nowpos - 1; ++ lpos) {
			for(; be <= ed && sta[ed].first < pref1[lpos]; -- ed);
			sta[++ ed] = {pref1[lpos], lpos};
		}
		ans = max({ans, sta[be].first - pref1[i], s2[nowpos] - pref0[i] + 2 * k});
	}
}
```

---

## 作者：聊机 (赞：2)

考场上正解没调出来，可恶。

我的实现方式跟原有题解的实现方式可能不同，并且时间薄纱 std。


## 正解

如果没有 $ 0 $ 的存在，我们就可以线性的推出最大子段和。

我们可以想到对于以 $ i $ 为结尾的子段和中，肯定是把离 $ i $ 最近的前几个 $ 0 $ 变成 $ 1 $ 然后求最大子段和。

#### 于是就有了我考场时的错误做法：


那我们在枚举这个末尾 $ i $ 的时候，如果新进来的点是 $ 0 $ 那就直接让它变成 $ 1 $，如果当前的最大子段里已经包含了 $ k $ 个 $ 0 $，那么就把第一个 $ 0 $ 变成 $ -1 $，判断这个点到当前最大子段的开头是否大于 $ 0 $，如果小于 $ 0 $，就把这个点到开头舍弃。

这种做法会被这样的数据 hack 掉：
```
9 4
1 1 0 -1 -1 0 0 0 0 
```


我们发现，在做到前八个数字的时候它都是正常的，到了最后一个数字，程序把第一个 $ 0 $ 变成了 $ -1 $，但是我们发现 $ \texttt{1+1-1=1 } $，大于 $ 0 $，所以就留着这个点？很明显程序并没有意识到在后面 $ -1 $ 的位置，它的前缀和已经变成 $ -1 $ 了！

直到比赛结束后我看到标签“**单调队列**”时我才恍然大悟！

只需要在刚才的基础上，维护前面最大子段中第一个“**撑不住**”的点！

所谓“撑不住”就是第一个到当前最大子段的开头的和小于等于 $ 0 $ 的点。


------------

##### 如果你还不理解，那我们用刚才的样例解释一下。

首先枚举到前八个点的时候最大子段就是前八个数字，此时为了把最后一个数字变成 $ 1 $，我们把最前面的 $ 0 $ 变成了 $ -1 $，此时我们发现从第一个数字到第五个数字的和变成了 $ -1 $！于是把它们都删去。


------------

而这个第一个撑不住的点我们就可以用单调队列来维护，如果一个点前面的点比它更能“撑”，那都不用管这个点因为等它“撑不住”的时候它已经被删掉了，这个也可以用刚才的样例解释，我们发现把第一个 $ 0 $ 变成 $ -1 $ 后，第一个数字到第四个数字的和变成了 $ 0 $，但是我们别删它，后面还有一个 $ -1 $，我们应该直接把第一个数字到第五个数字删掉。所以用单调队列维护。

至此正解的思路我们已经想到了，然而实现起来还是非常恶心。

有几个需要注意的点：

1. 如果我们删掉的这个“撑不住”的点前面还有没变成 $ -1 $ 的 $ 0 $，我们要记录下来。

2. 如果当前队列中值最小的这个点之前已经没有 $0$ 可以变成 $-1$ 了，但是它依然是正的，那就把它直接踢出去。

3. 因为我们每一次把之前的 $0$ 改成 $-1$ 都会导致队列中所以的值变化，而数据范围又要求线性，所以我用了一个变量 $ \texttt{suml} $ 记录队列中的数字减了多少值，但是减去的这个值对于之后进去的点来说是不存在的，所以我们往队列中放的值应该是 $ \texttt{suml} $ 加上实际值，每次取出时再减当前的 $ \texttt{suml} $。

4. 每次从中因为前缀和而踢出去一个点的时候，要把后面的点的前缀和都减去这个值，这个我们也直接维护在 $ \texttt{suml} $ 上。

5. 对于多余 $0$ 的统计，也需要用维护额外值的方法。

也许是我的实现方式太笨了，我在写的时候感觉非常的绕。

下面是~~薄纱~~ std 的代码，用时不到 std 的一半。

（具体细节依然非常多，仔细看代码哦）

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int qr() {
	int k=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){k=(k<<1)+(k<<3)+(ch^48);ch=getchar();}
	return k;
}
inline int getnum() { 
	char ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-') {
			while(!isdigit(ch))ch=getchar();
			return -1;
		}
		ch=getchar();
	}
	return ch-'0';
}//我也不会什么超级快读？朴素getchar
const int N=1e7+5;
int n,k,a,ans=-1;
int anx,cnt;
int l[N],r[N];
int suml,sumr;
int head=1,tail;
inline void pushback() {//维护单调队列 
	while(head<=tail&&l[tail]-suml>=anx) --tail;
	l[++tail]=anx+suml,r[tail]=cnt+sumr;	
}
int main() {
//	freopen("data.in","r",stdin); 
//	freopen("data.out","w",stdout);对拍遗留物
	n=qr(),k=qr();
	for(int i=1;i<=n;i++) {
		a=getnum();
		if(~a) ans=max(ans,1);
		if(anx<=0) {
			head=++tail,anx=(a?a:1),cnt=(a?0:1);
			l[head]=anx+suml,r[head]=(a?0:1)+sumr;
			continue;
		}
		if(a) {
			anx+=a,pushback();
			ans=max(ans,anx);
			continue;
		}
		if(cnt<k) {
			++cnt,++anx;
			pushback();
			ans=max(ans,anx);
			continue;
		}
		--anx,++sumr,suml+=2;
		while(head<=tail) {
			if(r[head]-sumr<0) { ++head; continue;}//注意点2 
			if(l[head]-suml<=0) {
				cnt-=r[head]-sumr;
				sumr+=r[head]-sumr;//注意点1和5 
				anx-=l[head]-suml;
				suml+=l[head]-suml;//注意点3和4 
				++head; continue;
			}
			break;
		}
		pushback();
		ans=max(ans,anx);
	}
	printf("%d",ans);
	return 0;
}
```

upd2023.7.18： 重发半年前写的题解，希望对大家有帮助。


---

## 作者：Polaris_Australis_ (赞：2)

来写一个当时验题想到的做法。

首先，我们可以发现，在答案状态下一定存在一种填法，满足所有的 $1$ 都被放在连续的一段，得到这个结论其实就可以写最大子段和板子，期望得分 $50\text{pts}$。

之后再考虑枚举答案区间的左端点 $l$，那么所有的 $1$ 都会被放在 $l$ 之后的 $k$ 个空位上。之后考虑求 $r$ 的最大值，分为两种情况。对于 $r$ 在 $l$ 后第 $k$ 个空位左侧，考虑维护 $S_i$ 表示前面在 $i$ 前所有空位全部填 $1$（不需要考虑是否大于 $k$ 个）的前缀和，则以这部分 $r$ 为右端点的区间的子段和为 $S_r-S_{l-1}$，即求 $S_r$ 的最大值即可。另一种情况，可以考虑维护 ${S_1}_{i}$ 表示 $i$ 前空位置全部填 $-1$ 的前缀和，${S_2}_{i}$ 表示 $i$ 前空位置填 $k$ 个 $1$，其余位置填 $-1$ 的前缀和，则以这部分 $r$ 为右端点的区间子段和为 ${S_2}_{r}-{S_1}_{l-1}$，即求 ${S_2}_r$ 的最大值即可，对两部分分别维护单调队列即可通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Wilson_Inversion {
void main();
}
int main() {
	Wilson_Inversion::main();
	return 0;
}
namespace Wilson_Inversion {
const int N(10000010);
int n, k, a[N], sum1[N], sum2[N], sum3[N], q1[N], q2[N], l1, r1, l2, r2;
void main() {
	scanf("%d%d", &n, &k);
	sum3[0] = k * 2;
	for (int i(1); i <= n; ++i) {
		scanf("%d", a + i);
		if (!a[i])
			sum1[i] = sum1[i - 1] - 1, sum2[i] = sum2[i - 1] + 1,
			sum3[i] = sum3[i - 1] - 1;
		else
			sum1[i] = sum1[i - 1] + a[i], sum2[i] = sum2[i - 1] + a[i],
			sum3[i] = sum3[i - 1] + a[i];
	}
	l1 = l2 = 1;
	int now(0), sum(0), sig(0);
	for (int i(1); i <= n; ++i) {
		while (l2 <= r2 && sum3[i] >= sum3[q2[r2]]) --r2;
		q2[++r2] = i;
	}
	while (now < n) {
		if (sum == k && (!a[now + 1])) break;
		++now;
		if (!a[now]) ++sum;
		if (q2[l2] == now) ++l2;
		while (l1 <= r1 && sum2[now] >= sum2[q1[r1]]) --r1;
		q1[++r1] = now;
	}
	int ans(0);
	for (int i(1); i <= n; ++i) {
		ans = max(ans, max(sum2[q1[l1]] - sum1[i - 1] - sig * 2,
						   ((l2 > r2) ? 0 : (sum3[q2[l2]] - sum1[i - 1]))));
		if (!a[i]) {
			++sig;
			--sum;
			while (now < n) {
				if (sum == k && (!a[now + 1])) break;
				++now;
				if (!a[now]) ++sum;
				if (q2[l2] == now) ++l2;
				while (l1 <= r1 && sum2[now] >= sum2[q1[r1]]) --r1;
				q1[++r1] = now;
			}
		}
		if (q1[l1] == i) ++l1;
	}
	cout << ans;
}
}  // namespace Wilson_Inversion
```


---

## 作者：TernaryTree (赞：1)

## $4$ pts 做法

给暴力分是中华民族的传统美德。时间复杂度 $\Theta(n2^n)$。

## $10$ pts 做法

枚举最大子段和的子段。其中所有 $0$ 贪心填 $1$ 即可。时间复杂度 $\Theta(n^3)$。

## $20$ pts 做法

将 $10$ pts 做法加以前缀和优化。时间复杂度 $\Theta(n^2)$。

## $50$ pts 做法

线段树维护之。以及很多奇怪的算法。时间复杂度 $\Theta(n\log n)$。

经测试，使用超级快读的极卡常 zkw 线段树也无法 $\text{SubTask} \ 4$ 的所有数据点。

## $100$ pts 做法

枚举最大子段和的子段的起点。则需要考虑子段的终点。

终点有两种情况：

- 在 $k$ 个 $0$ 之内，相当于一个在一段范围内求前缀和的最大值

- 在 $k$ 个 $0$ 之外，相当于强硬选 $k$ 个 $1$，然后再维护一个后缀最大子段和

尺取法或者单调队列可以解决。

广告：使用 [xwp 尺取法](https://www.luogu.com.cn/blog/hmyaqwq/ben-dan-qie-ke-zhuan-zhi-pin-bo-100-fen-miao-wo-yao-diao-da-dan-diao-d)，常数小，实现简单，不用卡常！

代码就是用这种尺取法实现的：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct ios {
    inline char read() {
        static const int inlen = 1 << 18 | 1;
        static char buf[inlen], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, inlen, stdin)), s == t ? -1 : *s++;
    }
    template<typename T> inline ios& operator>> (T &x) {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
            if (c11 == -1) return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read()) x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} fin;

struct exios {
    template<typename _CharT, typename _Traits = char_traits<_CharT>>
    struct typ {
        typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
    };

    friend exios &operator<<(exios &out, int num) {
        if (num < 0) putchar('-'), num = -num;
        if (num >= 10) out << num / 10;
        putchar(num % 10 + '0');
        return out;
    }

    friend exios &operator<<(exios &out, const char * s) { printf("%s", s); return out; }
    friend exios &operator<<(exios &out, string s) { cout << s; return out; }
    friend exios &operator<<(exios &out, typ<char>::end e) { puts(""); return out; }
} fout;
int n,k;
int nxt[10000005];
int pre0[10000005];
int a[10000005];
int pre[10000005];
int suf[10000005];
int ans;
int resl[10000005];
int resr=-2e9;
int main() {
	fin>>n>>k;
	for(int i=1; i<=n; i++) {
		fin>>a[i];
		if(!a[i])pre0[i]=pre0[i-1]+1;
		else pre0[i]=pre0[i-1];
	}
	int lt=1,rt=0;
	while(lt<=n) {
		while(pre0[rt]-pre0[lt-1]<k&&rt<n)rt++;
		nxt[lt++]=rt;
	}
	for(int i=1; i<=n; ++i) {
		pre[i]=pre[i-1]+a[i];
		if(a[i]==0)++pre[i];
	}
	for(int i=n; i; --i) {
		if(!a[i])suf[i]=max(0,max(suf[i+1]-1,-1));
		else suf[i]=max(0,max(suf[i+1]+a[i],a[i]));
	}
	for(int i=1; i<=n; ++i) {
		ans=max(ans,pre[nxt[i]]-pre[i-1]+suf[nxt[i]+1]);
	}
	lt=0,rt=0;
	int mid=0;
	while(lt<n){
		++lt;
		while(rt<nxt[lt]){
			resr=max(resr,pre[++rt]);
		}
		if(lt>mid){
			mid=rt;
			int tmp=lt;
			lt=rt+1;
			resr=-2e9;
			resl[lt]=pre[lt-1];
			while(lt>tmp){
				--lt;
				resl[lt]=max(resl[lt+1],pre[lt]);
			}
		}
		ans=max(ans,max(resl[lt],resr)-pre[lt-1]);
	}
	fout<<ans;
	return 0;
}
/*

*/
```

加了超级快读。

---

## 作者：ncwzdlsd (赞：1)

前缀和。

维护三个值：

- $c0$ 表示 $0$ 的个数的前缀和。

- $c1$ 表示把所有 $0$ 的位置填上 $1$ 后的前缀和。

- $cm1$ 表示把所有 $0$ 的位置填上 $-1$ 后的前缀和。

对于一个区间，只有两种情况：

1. $0$ 的个数大于 $k$。

2. $0$ 的个数小于 $k$。

枚举右端点。

对于情况 $1$，答案为所有满足条件的区间中，$cm1_i-cm1_{j-1}+2\times k$ 最大的情况。求 $cm1_{j-1}$ 的最小值即可。可以用双指针维护。

对于情况 $2$，答案为所有满足条件的区间中，$c1_i-c1_{j-1}$ 最大的情况。求 $c1_{j-1}$ 的最小值即可。发现有区间 $0$ 的个数的限制条件，可以用单调队列维护。

时间复杂度 $O(n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

const int maxn=1e7+5;
int c0[maxn],c1[maxn],cm1[maxn],a[maxn],q[maxn],j=1,l=1,r,minn=1e9;

int main()
{
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        a[i]=read(),c0[i]=c0[i-1];
        if(a[i]==1) c1[i]=c1[i-1]+1,cm1[i]=cm1[i-1]+1;
        else if(!a[i]) c1[i]=c1[i-1]+1,cm1[i]=cm1[i-1]-1,c0[i]++;
        else c1[i]=c1[i-1]-1,cm1[i]=cm1[i-1]-1;
    }
    int ans=-1e9;
    for(int i=1;i<=n;i++)
    {
        while(l<=r&&c0[i]-c0[q[l]-1]>k) ++l;
        while(l<=r&&c1[i-1]<=c1[q[r]-1]) --r;
        q[++r]=i;
        ans=max(ans,c1[i]-c1[q[l]-1]);
        while(c0[i]-c0[j-1]>=k) minn=min(minn,cm1[j-1]),j++;
        ans=max(ans,cm1[i]-minn+2*k);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：无钩七不改名 (赞：1)

单调队列。

设 $num0_i$ 表示 $1\sim i$ 中 $0$ 的个数。

容易发现，在我们选取的段中，如果 $0$ 的数量小于等于 $K$，则一定全为 $1$。这时候我们可以设 $c_i$ 表示当 $0$ 全部填 $1$ 时的数列前缀和，答案便为 $\begin{aligned}\max_{num0_i-num0_j\le k}\{a_i-a_j\}\end{aligned}$。我们可以通过维护一个使得单调队列实现。

如果 $0$ 的数量大于 $K$，一定是有 $K$ 个位置填 $1$。这时候我们可以设 $b_i$ 表示当 $0$ 全部填 $-1$ 时的数列前缀和，那么答案便为 $\begin{aligned}\max_{num0_i-num0_j\ge k}\{b_i-b_j+2\times K\}\end{aligned}$。

综合一下就可以得到最终答案了。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=10000005;

int n,k,a[N],b[N];
int d[N],l=1,r=1,num0[N];
int ans,mn;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int main(){
	n=read();k=read();
	for(int i(1),j(1);i<=n;++i){
		int x=read();
		a[i]=a[i-1]+x+(x==0);
		b[i]=b[i-1]+x-(x==0);
		num0[i]=num0[i-1]+(x==0);
		while(l<=r&&num0[i]-num0[d[l]]>k)++l;
		while(l<=r&&a[i]<=a[d[r]])--r;
		d[++r]=i;
		ans=max(ans,a[i]-a[d[l]]);
		if(num0[i]>k){
			while(num0[i]-num0[j]>=k){
				if(b[mn]>b[j])mn=j;
				++j;
			}
			ans=max(ans,b[i]-b[mn]+2*k);
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：LiveZoom (赞：0)

## Description

[link](https://www.luogu.com.cn/problem/P8945)

## Solution

### 暴力

易知这 $k$ 个 $1$ 必定是离得越近越好，所以肯定是相邻的。

然后可以直接用线段树维护整个序列的最大子段和。

时间复杂度：$O(n\log n)$。

---

### 正解

首先把区间和转化为两个前缀和相减。

设前缀和数组为 $s$，$0$ 出现的下标数组为 $p$。

先看一下线段树维护这个序列的核心代码：

```cpp
int ans = query(1, 1, n, 1, n).data;
for (int i = 1, j = k + 1; j <= t; ++i, ++j) {
  update(1, 1, n, p[i], -1), update(1, 1, n, p[j], 1);
  ans = max(ans, query(1, 1, n, 1, n).data);
}
```

这个操作相当于把 $s_{l},s_{l+1},...,s_{r-1}$ 全部减 $2$，然后重新求一遍最大子段和，显然是浪费的。

假设最大子段和为 $s_y-s_x$，那么如果这次操作 $s_x,s_y$ 全部减 $2$ 或者不变，那么肯定对答案没有影响。如果 $s_x$ 不变，$s_y$ 减 $2$ 答案不会更优。

所以只有当 $s_x$  减 $2$，$s_y$ 不变时可能是最终答案。

相当于就是求 $\max\{s_r,s_{r+1},...,s_n\}-\min\{s_l,s_{l+1},...,s_{r-1}\}$。左边那个可以 $O(n)$ 求，而右边那个用 ST 表/线段树都要带 $\log$，显然不行。

---

设 $pos_i$ 表示下标不大于 $i$ 且为 $0$ 的最大下标。

观察一下 $s$ 的变化：
$$
\begin{aligned}
&n=10,k=2:\\
&s_1,s_2,s_3,s_4,s_5,s_6,s_7,s_8,s_9,s_{10}\\
\to &\big[s_1-2,s_2-2,s_3-2\big],s_4,s_5,s_6,s_7,s_8,s_9,s_{10}\\
\to&s_1-2,s_2-4,\big[s_3-4,s_4-2,s_5-2,s_6-2\big],s_7,s_8,s_9,s_{10}\\
\to&s_1-2,s_2-2,s_3-4,\big[s_4-4,s_5-4,s_6-4,s_7-2,s_8-2\big],s_9,s_{10}\\
\end{aligned}
$$
容易发现第 $1\sim k-1$ 次操作时，要求的区间内操作次数是相同的，并且都是当前的次数。到第 $k$ 次操作时，下标最小的操作次数为 $2k$，相同 $pos$ 的下标操作次数是相同的，且 $pos$ 加 $1$ 对应的操作次数就减 $1$。

所以对于第 $1\sim k-1$ 次操作，直接求，但是要从 $p_k-1$ 往前扫求出最小值才能做到线性。

设操作完 $1\sim k-1$ 后，第 $i$ 个数操作次数是 $c_i$，那么就是要求区间内 $s_j+2\times(pos_j-pos_l)-2\times(k-c_j)$ 的最大值。

把这个东西化简一下就是 $(s_j+2\times pos_j+2\times c_j)-2\times(pos_l+k)$，由于 $pos_l+k$ 是定值，所以只要维护左边那个括号的最小值。由于区间的左端点和右端点都是单调递增的，所以可以维护一个求 $s_j+2\times pos_j+2\times c_j$ 的单调队列即可。

时间复杂度：$O(n)$。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e7 + 5;

int n, k, t;
int a[kMaxN], b[kMaxN], p[kMaxN], sum[kMaxN], ss[kMaxN], s[kMaxN], suf[kMaxN], pos[kMaxN];
int pre1[kMaxN], suf1[kMaxN], cnt[kMaxN];
deque<int> q;

int get1() {
  int cnt = 0, maxi = 1e9, ret = 0;
  for (int i = p[k + 1] - 1; i; --i) {
    maxi = min(maxi, sum[i]);
    if (!b[i]) {
      ++cnt;
      suf1[cnt] = maxi - 2 * pos[i];
      if (pos[i] + k <= t)
        /*cerr << "???" << i << ' ' << suf1[cnt] << ' ' << maxi << ' ' << p[pos[i] + k] << ' ' << suf[8] << '\n',*/ret = max(ret, suf[p[pos[i] + k]] - suf1[cnt]);
    }
  }
  return ret;
}

int main() {
  freopen("T4.in", "r", stdin);
  freopen("T4.out", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    b[i] = a[i];
    if (!a[i]) {
      p[++t] = i;
      pos[i] = t;
      if (t <= k) a[i] = 1;
      else a[i] = -1;
    }
    pos[i] = t;
    sum[i] = sum[i - 1] + a[i];
    ss[i] = sum[i] + 2 * t;
    s[t] = max(s[t], sum[i]);
  }
  suf[n + 1] = -1e9;
  for (int i = n; i; --i)
    suf[i] = max(suf[i + 1], sum[i]);
  int mi = 0, ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans = max(ans, sum[i] - mi);
    mi = min(mi, sum[i]);
  }
  if (k == t) {
    cout << ans << '\n';
    return 0;
  }
  // cerr << sum[11] << '\n';
  // cerr << "???" << ans << '\n';
  ans = max(ans, get1());
  // cerr << "***" << get1() << '\n';
  for (int i = 1; i <= k; ++i) {
    a[p[i]] = -1, a[p[i + k]] = 1;
    ++cnt[p[i]], --cnt[p[i + k]];
  }
  cnt[0] = 0;
  for (int i = 1; i <= n; ++i)
    cnt[i] += cnt[i - 1];
  int nw = 0;
  for (int i = 1; i <= n; ++i) {
    if (!b[i]) ++nw;
    sum[i] = sum[i - 1] + a[i];
    ss[i] = sum[i] + 2 * pos[i] + 2 * cnt[i];
  }
  suf[n + 1] = -1e9;
  for (int i = n; i; --i)
    suf[i] = max(suf[i + 1], sum[i]);
  for (int i = 1; i < p[2 * k]; ++i) {
    while (!q.empty() && ss[q.back()] >= ss[i]) q.pop_back();
    q.push_back(i);
  }
  // cerr << sum[5] << '\n';
  for (int i = k + 1, j = i + k; j <= t; ++i, ++j) {
    while (!q.empty() && q.front() < p[i]) q.pop_front();
    for (int dsfsa = p[j - 1]; dsfsa < p[j]; ++dsfsa) {
      while (!q.empty() && ss[q.back()] >= ss[dsfsa]) q.pop_back();
      q.push_back(dsfsa);
    } 
    if (!q.empty()) {
      // cerr << "!!! " << i << ' ' << suf[p[j]] - (ss[q.front()] - 2 * pos[p[i]] - 2 * k) << '\n';
      int kk = sum[q.front()] - 2 * (k - cnt[q.front()]) + 2 * (pos[q.front()] - pos[p[i]]);
      ans = max(ans, suf[p[j]] - kk);
      // if (suf[p[j]] - kk == 9) {
      //   cerr << "!!!" << i << ' ' << q.front() << '\n';
      //   cerr << "fuck " << kk  << '\n';
      // }
      // cerr  << suf[p[j]] - kk << '\n';
      // ans = max(ans, suf[p[j]] - (sum[q.front()] - 2 * (k - (pos[q.front()] - pos[i]))));
    }
  }
  cout << ans << '\n';
  return 0;
}
```

---

