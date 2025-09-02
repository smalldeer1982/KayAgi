# Candy Party (Hard Version)

## 题目描述

有 $n$ 个人，第 $i$ 个人有 $a_i$ 颗糖，在派对上，每个人 **至多会做一次下面的事情** ：

- 选一个正整数 $p\ (\ 1 \leq p \leq n\ )$ 和一个非负整数 $x$ ，然后把 $2^x$ 颗糖给第 $p$ 个人。注意任意时刻一个人手上的糖不能变成负数，并且一个人不能把糖给自己，每个人只能接受至多一个人的糖。
  

你需要回答能否在上述操作后让每个人手中的糖果数量相同。

注意本题和 Easy Version 不同的是本题可以不接受糖果，也可以不给出糖果。

## 样例 #1

### 输入

```
6
3
2 4 3
5
1 2 3 4 5
6
1 4 7 1 5 4
2
20092043 20092043
12
9 9 8 2 4 4 3 5 1 1 1 1
6
2 12 7 16 11 12```

### 输出

```
Yes
Yes
No
Yes
No
Yes```

# 题解

## 作者：Alex_Wei (赞：12)

### *[CF1868B2 Candy Party (Hard Version)](https://www.luogu.com.cn/problem/CF1868B2)

[B1 的题解](https://www.luogu.com.cn/blog/AlexWei/solution-cf1868b1)。

相较于 B1，问题在于当 $b_i = 2 ^ x$ 时有两种选择：直接给出 $2 ^ x$，或者给出 $2 ^ {x + 1}$ 收到 $2 ^ x$（对于 $b_i = -2 ^ x$ 同理）。不妨先让它选后者，记录这样的数的个数，记作 $add_x$ 和 $del_x$（$b_i = -2 ^ x$ 的数的个数）。

设 “给出 $2 ^ x$” 的人数减去 “收到 $2 ^ x$” 的人数为 $c_x$。$c_x = 0$ 显然没问题。当 $c_x < 0$ 时，“收到 $2 ^ x$” 的人太多了。每次将 “给出 $2 ^ {x + 1}$ 收到 $2 ^ x$” 调整为 “给出 $2 ^ x$”，会让 $c_x$ 加上 $2$，$c_{x + 1}$ 减去 $1$。因此，如果 $2add_x \geq -c_x$ 且 $c_x$ 为偶数，就可以调整让 $c_x$ 变成 $0$，$c_{x + 1}$ 减去原 $|c_x|$ 的一半。对于 $c_x > 0$ 同理。从小到大依次考虑所有 $x$，过程中调整方案是唯一的，因为我们只能让 $c_x = 0$。

B1 的题解证明了方案不会出现所有人都给不出糖的情况，因此合法。

注意不要写成了 `else cout << "no\n", void();`。

时间复杂度 $\mathcal{O}(n\log V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;

int n, a[N];
void mian() {
  long long sum = 0;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum += a[i];
  if(sum % n) return cout << "no\n", void();
  sum /= n;
  vector<int> cnt(31), add(31), del(31);
  for(int i = 1; i <= n; i++) {
    a[i] -= sum;
    if(!a[i]) continue;
    if(a[i] > 0) {
      int p = __lg(a[i] & -a[i]);
      if(__builtin_popcount(a[i]) == 1) add[p]++;
      a[i] += 1 << p, cnt[p]--;
      p = __lg(a[i] & -a[i]);
      a[i] -= 1 << p, cnt[p]++;
    }
    if(a[i] < 0) {
      a[i] = -a[i];
      int p = __lg(a[i] & -a[i]);
      if(__builtin_popcount(a[i]) == 1) del[p]++;
      a[i] += 1 << p, cnt[p]++;
      p = __lg(a[i] & -a[i]);
      a[i] -= 1 << p, cnt[p]--;
    }
    if(a[i]) return cout << "no\n", void();
  }
  for(int i = 0; i < 31; i++) {
    if(cnt[i] & 1) return cout << "no\n", void();
    if(cnt[i] < 0) {
      if(add[i] * 2 < -cnt[i]) return cout << "no\n", void();
      cnt[i + 1] -= -cnt[i] / 2;
    }
    if(cnt[i] > 0) {
      if(del[i] * 2 < cnt[i]) return cout << "no\n", void();
      cnt[i + 1] += cnt[i] / 2;
    }
  }
  cout << "yes\n";
}
int main() {
  int T = 1;
  cin >> T;
  while(T--) mian();
  return 0;
}
```

---

## 作者：六楼溜刘 (赞：7)

## 题意

- 有 $n$ 个人，第 $i$ 个人手上最初有 $a_i$ 颗糖
- 现在每个人可以把自己原来的糖给不多于一个（不是自己的）人，给的糖数只能是二的次方数，每个人只能接受不多于一个人的糖。
- 问能否让每个人传递糖后手上的糖数量相等。

## 题解

这道题我赛时想到问题转化成二选一，但是不知道怎么维护，后面又没看懂题解的图论意义。最后琢磨一下发现官方题解的意思就是说它可以贪心解决。

首先考虑简单版本，即每个人**恰好**送给另外**一个人**且得到另外**一个人**的糖。

首先我们可以算出每个人最后手上有多少个糖（算一下平均数即可，如果不是整数直接无解），设这个数为 $s$，那么也就可以算出每个人糖**必须**的变化量 $s-a_i$ 是多少（注意这个值显然不能多也不能少），那么情况合法当且仅当每个人糖的变化量都能写成 $2^x-2^y$ 的形式（即在二进制下所有 $1$ 连续），且可以一一对应（一个加对应一个减），对于 $a_i=s$ 的情况，我们可以参考样例 $1$ 的处理。也就是说我们对于 $k\in[0,31]$，统计一下 $+2^k,-2^k$ 的数量 $S_k,T_k$，然后判断一下是否相等即可。

然后我们考虑硬版本和简单版本的区别，容易发现，只有在 $s-a_i=\pm2^k$ 的时候，这个人的决策会有两种选择，一种是 $\pm(2^{k+1}-2^k)$，另一种是 $\pm2^k$，那么我们考虑先把 $+2^k,-2^k$ 这样的单独拎出来统计数量后面贪心解决，设 $+2^k$ 的数量为 $s_k$，$-2^k$ 为 $t_k$，为方便叙述，我们称取 $2^k$ 的为方法一，取 $2^{k+1}-2^k$ 为方法二。

具体来说，我们从高位往低位决策，那么假设我们在决策第 $i$ 位（从高往低）时，前面的位数已经全部合法了，此时我们肯定不希望这一位的影响上一位，那么这一位现在的全用方法一，但是假如这样凑不到相等就考虑在下一位取一些方法二补齐，到决策下一位时就只考虑剩余的。最后假如**中途不够**/**到最后一位不相等**就说明无解，反之有解。

考虑证明贪心，因为我们只关注对解存在与否的判定，所以只需要证明能这样构造出的解的情况是所有有解的情况。首先这样构造出来的解（若有解）显然合法（充分性），下面证明有合法的解时必定能这样构造出来（必要性）。

考虑证明逆否命题，即存在**构造不出解的情况有合法解**，考虑我们构造的过程，什么时候无法构造出解。首先，在第一位，即当前位的方法一和下一位的方法二加起来都无法凑出合法的情况，这种情况显然无解，你不可能把本来的方法一改成方法二使得 $S_1,T_1$ 的差值减小，因为前一位本来 $S,T$ 相等，你把一个 $s_1$ 取为方法二必定要把一个 $t_1$ 取为方法二。所以在第一位构造不出解得情况必然无合法解，而且第一位的构造显然唯一（只考虑 $s_1,t_1$ 转化的数量，不考虑具体谁和谁配对），那么同理可以证明后面的位数显然也正确（证明几乎一样，可以自己推一推），那么命题得证。

预处理复杂度 $O(n\log V)$，贪心复杂度 $O(\log V)$（$V$ 是值域大小），显然可以通过此题。

## code

在代码中的 `cntp` 数组中，每个 $+1$ 代表一个 $-2^k$，$-1$ 代表一个 $+2^k$，因为我写代码的时候考虑的是每个 $a_i$ 对桶的贡献，~~绝对不是因为我懒得改~~。

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(i64 i=(s);i<=(e);i++)
#define fordown(i,s,e) for(i64 i=(s);i>=(e);i--)
using namespace std;
using i64=long long;
using pii=pair<i64,i64>;
#define fi first
#define se second
#define mkp make_pair
#define gc getchar()
inline i64 read(){
    i64 x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const i64 N=2e5+5,inf=0x3f3f3f3f;
i64 t,n,a[N],sum;
pii calc(i64 x){//计算对桶的贡献
	i64 st=-1,ed=-1;
	forup(i,0,31){
		if(x&(1<<i)){
			if(st==-1) st=i;
			if(ed!=-1) return mkp(0,0);
		}else{
			if(ed==-1&&st!=-1) ed=i;
		}
	}
	return mkp(st,ed);
}
i64 cntp[35],c1[35],c2[35];
//桶，+2^k,-2^k
void solve(){
	n=read();
	sum=0;
	forup(i,1,n){
		a[i]=read();
		sum+=a[i];
	}
	if(sum%n){
		puts("No");
		return;
	}
	sum/=n;
	mem(cntp,0);mem(c1,0);mem(c2,0);//多测不清空，罚时两行泪
	forup(i,1,n){
		pii res=calc(abs(sum-a[i]));//预处理统计$T-S,s,t$
		if(res.fi==res.se&&res.fi==0){
			puts("No");
			return;
		}
		if(res.se==res.fi+1){
			if(sum>a[i]){
				c1[res.fi]++;
			}else{
				c2[res.fi]++;
			}
		}else if(res.fi!=-1){
			if(sum>a[i]){
				cntp[res.fi]++;cntp[res.se]--;	
			}else{
				cntp[res.fi]--;cntp[res.se]++;
			}
		}else{
		}
	}
	fordown(i,31,1){
		cntp[i]+=c2[i]-c1[i];
		if(cntp[i]==0) continue;
		if(cntp[i]>0){//考虑下一位的贡献
			if(c1[i-1]<cntp[i]){
				puts("No");
				return;
			}else{
				cntp[i-1]+=cntp[i];
				c1[i-1]-=cntp[i];
			}
		}else{
			cntp[i]*=-1;
			if(c2[i-1]<cntp[i]){
				puts("No");
				return;
			}else{
				cntp[i-1]-=cntp[i];
				c2[i-1]-=cntp[i];
			}
		}
	}
	if(cntp[0]+c2[0]-c1[0]!=0){//考虑最后一位是否合法
		puts("No");
	}else{
		puts("Yes");
	}
}
signed main(){
	t=read();
	while(t--){
		solve();
	}
}
```

---

## 作者：One_JuRuo (赞：5)

建议先看[简单版本](https://www.luogu.com.cn/problem/CF1868B1)以及我的[题解](https://www.luogu.com.cn/blog/AuroraWind/solution-cf1868b1)。

## 思路

可以发现困难版本比简单版本唯一不一样的地方就是可以给糖也可以不给，可以收糖也可以不收。

首先还是需要求和，如果无法平分，肯定无解，再算出平均数 $s$。

还是考虑每一个 $a_i$，如果 $|a_i-s|$ 不是二次幂，那么肯定必须同时给糖和收糖，判断有没有解还是和简单版本一样。

不一样的地方就是 $|a_i-s|$ 是二次幂了，不同于简单版本，这里可以直接给或者收 $|a_i-s|$ 这么多的糖了，而不像简单版本，必须给或者收 $2\times |a_i-s|$ 颗糖，再收或者给 $|a_i-s|$ 颗糖。

因为存在必须拆成 $2^x-2^y$ 形式的 $a_i$，所以可以考虑先把这部分和本身是二次幂的分开统计。

这里使用三个数组进行储存，如下：

需要的数组 $m_i$，$giv_i$，$rec_i$。

其中，$m_i$ 统计必须拆成两个二次幂的情况，等价于简单版本的两个 map，只不过是把原来的 $2^k$ 改成了 $k$ 方便储存，同时直接计算差值。可以简单的理解为 $m[k]=m1[2^k]-m2[2^k]$。

那么，$m_i$ 如果大于 $0$，代表还有若干个 $2^i$ 的糖果数需要给，小于 $0$，代表还有若干个 $2^i$ 的糖果数被需要。

其次，$giv_i$ 代表可以直接给 $2^i$ 个糖果的个数，这些给法也可以拆开给。

$rec_i$ 代表可以直接收 $2^i$ 个糖果，与 $giv_i$ 基本相同。

那么我们的目标就是尽可能地使用 $giv_i$ 和 $rec_i$（拆开或者不拆），来让所有的 $m_i$ 都变成 $0$。

因为对于某个可以直接给 $2^k$ 个糖果的情况，有两种方式，即给 $2^k$ 和 给 $2^{k+1}$ 收 $2^k$，都只会影响 $2^k$ 和 $2^{k+1}$，所以我们考虑从 $k$ 大的情况开始枚举。

首先对于每个的 $i$，我们都在枚举 $i+1$ 时，保证了 $m_{i+1}=0$，那么剩余的 $giv_i$ 和 $rec_i$ 统计的个数都不能拆开，那么 $m_i$ 就会变成 $m_i+giv_i-rec_i$ 表示新的需要给/收的糖果数为 $2^k$ 的个数。

如果此时新的 $m_i$ 已经为 $0$，那么就不需要去管了，如果 $m_i$ 小于 $0$，代表还需要给若干个给 $2^k$ 的糖果数，只能拆 $2^{k-1}$ 去补，那么更新 $giv_{i-1}$ 和 $m_{i-1}$，如果此时 $giv_{i-1}<0$，就代表无法使 $2^k$ 的糖果数达成平衡，一定无解，否则的话就继续枚举下一个 $i$。$m_i$ 大于 $0$ 的情况同理。

最后再看 $m_0$ 是否为 $0$ 即可。

另外，因为涉及各种数量相加，而有些 $2^k$ 可能在某些情况没有出现，所以不好再用 map 直接存数量，所以这里才转化了一下，使得可以使用数组储存。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,a[200005],sum,k,low,m[35],giv[35],rec[35];
inline long long lowbit(long long x){return x&(-x);}
inline long long get(long long x)//对于2^k，取出k
{
	long long ans=0;
	while(x%2==0) x/=2,++ans;
	return ans;
}
inline bool sol()
{
	scanf("%lld",&n),sum=0;
	for(long long i=1;i<=n;++i) scanf("%lld",&a[i]),sum+=a[i];
	sum/=n;
	for(long long i=0;i<=30;++i) m[i]=giv[i]=rec[i]=0;//多测要清空
	for(long long i=1;i<=n;++i)
	{
		a[i]-=sum;k=abs(a[i]);low=lowbit(k);
		if(k==low){if(a[i]>0) ++giv[get(k)];else if(a[i]<0) ++rec[get(k)];continue;}//如果本身就是二次幂，统计到giv或者rec
		k+=low;
		if(k!=lowbit(k)) return 1;
		if(a[i]>0) ++m[get(k)],--m[get(low)];
		else if(a[i]<0) ++m[get(low)],--m[get(k)];//统计个数
	}
	for(long long i=30;i>=0;--i)
	{
		m[i]+=(giv[i]-rec[i]),k=abs(m[i]);//i剩余的giv和rec只能用于i，不能拆开，防止更改i+1
		if(!i){if(!m[0]) return 0;else return 1;}//对于0就不能用i-1去平衡i，而是直接判断
		if(m[i]<0)//还需要收若干个2^i
		{
			giv[i-1]-=k,m[i-1]-=k;//拆2^(i-1)去补2^i
			if(giv[i-1]<0) return 1;//2^(i-1)数量不够就无解
		}
		else if(m[i]>0)//同上面一种情况
		{
			rec[i-1]-=k,m[i-1]+=k;
			if(rec[i-1]<0) return 1;
		}
	}
}
int main()
{
	scanf("%lld",&T);
	while(T--)
		if(sol()) printf("NO\n");
		else printf("YES\n");
	return 0;
}


```

---

## 作者：Creeper_l (赞：3)

原题链接：[CF1868B2](https://www.luogu.com.cn/problem/CF1868B2)，
简单版：[CF1868B1](https://www.luogu.com.cn/problem/CF1868B1)。

## 题意

有 $n$ 个人，第 $i$ 个人手上最初有 $a_{i}$ 颗糖。现在每个人可以把自己手中的糖选一些给不多于一个人，同时每个人也只能接受不多于一个人的糖，选出的糖的数量必须是二的次幂。问能否能让每个人最终手上的糖的数量相等。

## 思路

首先，这道题与简单版的区别在于：这道题可以选择不给其它人糖。换句话说，如果你需要得到 $2^{x}$ 颗糖，你除了可以选择得到 $2^{x+1}$ 颗糖，给出 $2^{x}$ 颗糖，还有了一种新的选择：直接得到 $2^{x}$ 颗糖。而简单版则只能选择前者，因为题目要求你必须给出一次糖。

然后考虑如何解决。首先平均数不是整数或者 $a_{i}-mean$ 的值在二进制表示下下 $1$ 的个数不符合题目要求的话直接判断为无解。然后我们发现上述的这两种选择的本质区别其实就是 $x$ 的个数和 $x+1$ 的个数的变化，且变化只针对相邻的两个数值，所以可以考虑贪心。我们先假设每次都先选第二种情况，最后再来调整。记录三个数组 $cnt,add,del$ 分别表示 $x$ 得到的次数（如果是负数则为给出），$x$ 最多可以再被多选几次，$x$ 最多可以再被多给出几次。

得到这三个数组之后再来调整每一个 $cnt$ 的值，判断每一个数，看 $cnt_{i}$ 的正负，奇偶性。如果为奇数的话一定无解，因为每一次操作 $x$ 的数量一定会增加或减少 $2$ 的倍数个，因为从给出 $2^{x}$ 颗糖变成了得到 $2^{x}$ 颗糖。如果为偶数的话就用 $add$ 或者 $del$ 来调整即可。如果 $add$ 或者 $del$ 出现了不够的情况时说明了无解。注意：如果 $cnt_{i}$ 加上了 $k$，那么 $cnt_{i+1}$ 就要减去 $k \div 2$，反之亦然。

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
const int MAXM = 30 + 10; 
int cnt[MAXN],T,n,a[MAXN],sum,mean,add[MAXM],del[MAXM];
inline int Lowbit(int x){return x & -x;} 
inline bool check()
{
	for(int i = 0;i <= 31;i++) add[i] = del[i] = cnt[i] = 0;
	for(int i = 1;i <= n;i++)
	{
		int now1 = Lowbit(abs(a[i] - mean));
		int now2 = abs(a[i] - mean) + now1;
		if(Lowbit(now2) != now2) return false;
		if(a[i] - mean > 0) cnt[__lg(now1)]--,cnt[__lg(now2)]++;
		if(a[i] - mean < 0) cnt[__lg(now1)]++,cnt[__lg(now2)]--;
		int tmp = __builtin_popcount(abs(a[i] - mean));
		if(a[i] - mean > 0 && tmp == 1) add[__lg(now1)]++;
		if(a[i] - mean < 0 && tmp == 1) del[__lg(now1)]++;
	}
	for(int i = 0;i <= 30;i++)
	{
		if(cnt[i] % 2 != 0) return false;
		if(cnt[i] < 0)
		{
			if(add[i] * 2 < -cnt[i]) return false;
			cnt[i + 1] -= -cnt[i] / 2;
		}
		if(cnt[i] > 0)
		{
			if(del[i] * 2 < cnt[i]) return false;
			cnt[i + 1] += cnt[i] / 2;
		}
	}
	return true;
}
signed main()
{
	cin >> T;
	while(T--)
	{
		cin >> n;sum = 0;
		for(int i = 1;i <= n;i++) cin >> a[i],sum += a[i];
		mean = sum / n;
		if(sum % n != 0){puts("No");continue;}
		if(check() == true) puts("Yes");
		else puts("No"); 
	}
	return 0;
}

```




---

## 作者：Xy_top (赞：3)

简单题，考场上做完了 D1 以为能上紫就开摆了，没想到最后 Perf 还没上紫。

D1 罚时吃饱了。

和 D1 很像，只不过当一个人想要得到 $2^x$ 时，不仅仅可以选择得到 $2^{x+1}$ 后失去 $2^x$，还可以选择直接得到，失去同理。

先不管这个，留到最后，然后从低到高扫所有 $2^x$，如果得到 $2^x$ 的人过多了，就看看有没有得到 $2^x$ 失去 $2^{x+1}$ 的，把它换成失去 $2^x$，失去同理。

然后代码我写了巨长：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, s;
int a[200005], pre[200005];
int need[200005], lose[200005];
map <int, bool> ff;
map <int, int> c, b1, b2;
int aa;
void solve () {
	s = 0;
	c.clear ();
	For (i, 0, 30) pre[i] = 1 << i;
	For(i,0,30)ff[pre[i]]=1;
	cin >> n;
	For (i, 1, n) {
		cin >> a[i];
		s += a[i];
	}
	b1.clear ();
	b2.clear ();
	if (s % n) {
		cout << "No";
		return;
	}
	s /= n;
	For (i, 1, n) {
		if (a[i] == s) continue;
		int x = abs (a[i] - s), y = -1;
		if (x == 0) continue;
		For (j, 0, 30) {
			if (ff[x + pre[j] ]) {
				y = pre[j];
				break;
			}
		}
		if (y == -1 && !ff[x]) {
			cout << "No";
			return;
		}
		if (ff[x]) {
			if (a[i] > s) {//可以只失去 x
				b1[x] ++;
			} else {//可以只得到 x
				b2[x] ++;
			}
		}
		if (y != -1) {
			int j = y;
			if (a[i] > s) {//得到 j，失去 x + j，总共失去 x
				need [i] = j;
				lose [i] = x + j;
			} else {
				need [i] = x + j;
				lose [i] = j;
			}
			c[need[i] ] ++;
			c[lose[i] ] --;
		}
	}
	for (auto p : c) {
		if (p.second < 0) {//有很多人需要给出 x，但只有一小部分需要 x
			//将那些得到 x 给出 x + 1 的转成给出 x
			//更小的就不必考虑了
			int x = p.first;
			if (p.second % 2 != 0) {
				cout << "No";
				return;
			}
			while (c[x] < 0) {
				if (b2[x]) {
					//此人原先是得到 x + 1 失去 x
					//现在改成得到 x
					b2[x] --;
					c[x] += 2;
					c[x << 1] --;
/*					need[x] = 1;
					lose[x] = 0;
					lose[x + 1] = 1;
					need[x] = 0;
					lose[x] = 1;
					lose[x + 1]
*/
				} else {
					cout << "No";
					return;
				}
			}
		} else {
			int x = p.first;
			if (p.second % 2 != 0) {
				cout << "No";
				return;
			}
			while (c[x] > 0) {//想得到的人太多了 
				if (b1[x]) {
					//此人原先是得到 x 失去 x + 1
					//现在改成失去 x
					b1[x] --;
					c[x] -= 2;
					c[x << 1] ++;
				} else {
					cout << "No";
					return;
				}
			}
		}
	}
	cout << "Yes";
}
signed main () {
	ios :: sync_with_stdio (false);
	int _ = 1;
	cin >> _;
	for (aa = 1; aa <= _; aa ++){
		solve ();
		cout << '\n';
	}
	return 0;
}

```


---

## 作者：irris (赞：1)

+ **似乎和一致的所有做法都不一样**？让我简单写一个我的思路吧。
+ 首先你应该知道所有人最后会分到 $\bar{a} = \frac 1n \sum\limits_{i=1}^n a$ 个糖果，所以每个人应该需要增加 / 减少 $\Delta a_i = \lvert a_i - \bar a \rvert$ 个糖果。发现每个人如果收到一个人的 $2^x$ 个糖果，并且给出 $2^y$ 个糖果，那么 $2^x - 2^y = \Delta a_i$（这里我们考虑 $a_i \lt \bar a$，对于小于的情况是类似的）。
+ 这里你会发现 $\Delta a_i$ 在二进制下一定形如 $\texttt{11...100...0}$ 的形式，并且此时 $x, y$ 是确定的。所以我们可以开两个 multiset $S_{in}, S_{out}$，将 $2^x$ 插入进 $S_{in}$，$2^y$ 插入进 $S_{out}$，最后判断 $S_{in}$ 是否等于 $S_{out}$。

> 很遗憾，这是错的，但是能够通过 B1（不再赘述细节问题）。

+ 错误的原因在于，如果 $\Delta a_i$ 形如 $\texttt{100...0}$，那么**还有另一种可能**，就是仅收到 $2^x = \Delta a_i$ 个糖果，而并不给出任何糖果。
+ 这里我们先转而考虑另一个问题：如何快速判定 $S_{in}$ 与 $S_{out}$ 的相等关系？
+ 注意到 $\sum S_{in} = \sum S_{out}$，所以这对应了把一个数 **拆分成若干个 $\bm{2^k}$ 的形式**。
+ **人类智慧**：记录每个 $2^k$ 出现的次数的奇偶性和集合的大小，当这 $\lceil \log V \rceil + 1$ 个量全都相等时，两个集合都是相等的。

> 虽然两个 hash 单独都是错的，**但是拼起来就是对的啦**，小编也觉得很神奇。  
> 证明：考虑最大的那个出现数量不同的 $2^k$，它每增加 / 减少了 $2$ 个，比它小的数最少要变化 $4$ 个（$2^{k-1}$），虽然奇偶性不改变，但是集合大小却改变了。

+ 然后我们就可以开始进行一些神秘操作啦！我们对「记录每个 $2^k$ 出现的次数的奇偶性」记录两个集合这样记录的异或（说人话，就是 $2^k$ 出现的奇偶性，因为 $\sum S_{in} = \sum S_{out}$，所以每个 $2^k$ 出现偶数次后，一定是可以恰好分完的），然后先把每个数强制钦定为 $2^x - 2^y$ 而不是 $2^x$。于是就变成了下面一个问题：

> 给你一个长为 $m$ 的 $\texttt{01}$ 网格，你有若干次 A 操作，每次 A 操作给定一个网格 $pos$ 翻转 $pos$ 的位置；每次 B 操作给定一个网格 $pos'$ 翻转 $pos'$ 的位置。  
> 你希望最后所有网格全 $\texttt 0$ 并且 A 操作和 B 操作使用次数相等，问是否可行。

+ 这个问题的做法是，我们对于每一个网格求出在这个网格上使用的 A 操作数 减去 使用的 B 操作数 的取值范围（为了方便阅读，加了空格）。它应当是一个公差为 $2$ 的等差数列。
+ 我们把每个等差数列的最小值加起来记为 $mn$，最大值加起来记为 $mx$，所以就要求 $mn \leq 0 \leq mx$ 且 $mn, mx$ 均为偶数，这样一定就满足条件，因为肯定存在一个符合条件的中项。

## Code

```cpp
#include <bits/stdc++.h>
 
namespace FastIO {
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= ch == '-', ch = getchar(); while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return w ? ((~x) + 1) : x; }
	template <typename T> inline void write(T x) { x && (write<T>(x / 10), putchar(x % 10 ^ '0')); }
	template <typename T> inline void print(T x) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x); }
	template <typename T> inline void print(T x, char end) { x || putchar('0'); x < 0 && (putchar('-'), x = (~x) + 1); write<T>(x), putchar(end); }
};
using namespace FastIO;
 
#define MAXN 200001
int a[MAXN];
 
const int V = 40;
bool p[V + 1];
int ca[V + 1], cb[V + 1];
 
inline int lowbit(int a) { return a & (-a); }
inline int lg(int a) { int ans = -1; while (a) a >>= 1, ++ans; return ans; }
void solve() {
	memset(p, 0, sizeof p);
	memset(ca, 0, sizeof ca);
	memset(cb, 0, sizeof cb);
	int N = read<int>(); long long tot = 0;
	for (int i = 1; i <= N; ++i) tot += a[i] = read<int>();
	if (tot % N != 0) return (void)puts("No"); tot /= N;
	for (int i = 1; i <= N; ++i) {
		bool g = a[i] < tot; int tmp = a[i];
		a[i] = std::abs(a[i] - tot);
		if (lowbit(a[i] + lowbit(a[i])) == a[i] + lowbit(a[i])) {
			p[lg(lowbit(a[i] + lowbit(a[i])))] ^= 1;
			p[lg(lowbit(a[i]))] ^= 1;
			if (a[i] == lowbit(a[i])) ++(lg(a[i]) + 1)[(g ? ca : cb)];
		} else return (void)puts("No");
	}
	long long mn = 0, mx = 0;
	for (int i = 0; i <= V; ++i) if (p[i]) {
		if (ca[i] == 0 && cb[i] == 0) return (void)puts("No");
		mx += ((ca[i] & 1) ? ca[i] : ca[i] - 1);
		mn += ((cb[i] & 1) ? -cb[i] : 1 - cb[i]);
	} else {
		mx += ((ca[i] & 1) ? ca[i] - 1 : ca[i]);
		mn += ((cb[i] & 1) ? 1 - cb[i] : -cb[i]);
	}
	puts((mx & 1) || mx < 0 || mn > 0 ? "No" : "Yes");
}
 
int main() { int T = read<int>(); while (T--) solve(); return 0; }
```

---

## 作者：xs_siqi (赞：0)

赛时做 B1 发现题读假了。然后发现读假的题刚好是 B2。

首先我觉得正确的顺序还是先做简单版。不难想到一种构造，由于题目要求给出与收到的糖果必须是 $2$ 的幂次，同时最后所有人的糖果都是一样的。

既然所有人的糖是一样的，那肯定都是平均数了。所以不能整除肯定不行。然后再考虑到一个人的糖和平均数的糖之差肯定恰好为两个 $2$ 的幂次。

记第 $i$ 个人的糖数为 $a_i$，平均数为 $p$。若 $a_i< p$，那这个人的糖与平均值的差 $k$ 肯定可以被表示为 $k=2^x-2^y(x\geq y,x,y\geq 0)$。

同理，若 $a_i> p$，那这个人的糖与平均值的差 $k$ 肯定可以被表示为 $k=2^y+2^x(x\geq y,x,y\geq 0)$。

然后对于简单版，我们直接记个桶分别记录 $2^x$ 与 $2^y$ 的个数，然后判断减掉的和加上的数量是否相同就好了。直接建 $2$ 的幂次可能空间开不下，可以考虑以指数为下标建。

然后现在困难版无非是多加了一个条件，那么我们的结论需要小改一下。

若 $a_i< p$，那这个人的糖与平均值的差 $k$，如果恰好为 $2$ 的幂次，肯定可以被表示为 $k=2^x-2^y(x\geq y,x,y\geq 0)$ 或 $k=2^y$，否则与简单版一致。$a_i>p$ 的情况同理。

主要是这个或比较烦人，我们考虑用两个去匹配这个“一个或两个”的情况的优先级是很烦人的。

正难易反，考虑倒着做，我们钦定每次如果这个 $k$ 如果能被表示为 $2$ 的幂次，就直接把他表示为 $k=2^y$ 的形式。如果有一个不匹配了，就把这个 $k=2^y$ 改回来变成 $2^x-2^y$。由于 $x\geq y$，所以这样安排是没有后效性的。又由于如果要满足，前面的必定要被安排，所以直接从前往后处理即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int t,n,sum,cs,p,fl,pow2[32],a[maxn],cnt1[32],cnt2[32],tot,chai1[32],chai2[32];
signed main(){
	scanf("%lld",&t);p=t;
	pow2[0]=1;
	for(int i=1;i<=30;i++)pow2[i]=pow2[i-1]*2;
	while(t--){
		cs++;
		for(int i=0;i<=30;i++)cnt1[i]=cnt2[i]=chai1[i]=chai2[i]=0;
		fl=0;sum=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]),sum+=a[i];
		if(sum%n!=0){
			printf("No\n");
			continue;
		}
		int inv=sum/n;
		for(int i=1;i<=n;i++){
			bool f=0,sp=0;
			if(a[i]<inv){
				for(int j=0;j<=30;j++)
					if(pow2[j]==inv-a[i])//可被表示为 2^y 形式的 
						f=1,sp=1,chai1[j]++,cnt1[j]++;//cnt1 是欠的桶 (cnt2 同理)，钦定为 2^y 
				if(!sp){//不能的 
					for(int j=0;j<=30;j++)
						for(int k=j;k<=30;k++)
							if(pow2[k]-pow2[j]==inv-a[i]){
								f=1,cnt1[k]++,cnt2[j]++;
							}			
				}				

			}
			if(a[i]>inv){//同理 
				for(int j=0;j<=30;j++)
					if(pow2[j]==a[i]-inv)
						f=1,sp=1,chai2[j]++,cnt2[j]++;
				if(!sp){
					for(int j=0;j<=30;j++)
						for(int k=j;k<=30;k++)
							if(pow2[k]-pow2[j]==a[i]-inv){
								f=1,cnt1[j]++,cnt2[k]++;
							}				
				}
			}
			if(a[i]==inv)f=1;
			if(!f){
				fl=1;break;
			}
		}
		if(fl){
			printf("No\n");
			continue;
		}
		for(int i=0;i<=30;i++){
			if(cnt1[i]>cnt2[i]){
				if((cnt1[i]-cnt2[i])&1){
					fl=1;
					break;
				}
				while(chai1[i]&&cnt1[i]!=cnt2[i]&&i!=30){//如果无法满足，再重新分配一下 
					chai1[i]--;
					cnt1[i]--,cnt2[i]++,cnt1[i+1]++;
				}
				if(cnt1[i]!=cnt2[i]){
					fl=1;
					break;
				}
			}			
			if(cnt1[i]<cnt2[i]){
				if((cnt2[i]-cnt1[i])&1){
					fl=1;
					break;
				}
				while(chai2[i]&&cnt1[i]!=cnt2[i]&&i!=30){
					chai2[i]--;
					cnt2[i]--,cnt1[i]++,cnt2[i+1]++;
				}
				if(cnt1[i]!=cnt2[i]){
					fl=1;
					break;
				}
			}
		}
		if(!fl)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
} 
/*
1
8
17 3 8 12 2 19 7 20 
*/
```


---

## 作者：Z1qqurat (赞：0)

可以先看看 B1，[这里](https://www.luogu.com.cn/blog/Ziqqurat/solution-cf1868b1)是我写的 B1 题解，两题思路上有一些共同之处。

差不多自己想到了但是有个小地方想错了，可惜。结合 B1 的思路，还是一样的处理方式，$cnt_i > 0$ 表示有 $cnt_i$ 个人需要失去 $2^i$ 个糖果，$cnt_i < 0$ 同理。但是我们会发现一个差别，就是 B2 中不强制要求每个人一定要失去糖果。这时候如果 $b_i = 2^x$（不妨设 $b_i > 0$），那么原先它必须被表示为 $b_i = 2^{x + 1} - 2^x$，也就是必须失去 $2^{x + 1}$ 个糖果再得到 $2 ^ x$ 个糖果，但是现在可以直接失去 $2 ^ x$ 个糖果。我们记 $add_i$ 表示可以通过一次调整使得失去 $2 ^ x$ 个糖果的人数加上 $add_i$ 个，那么每次调整相当于 $add_i + 2$，也就是 $cnt_i + 2, cnt_{i + 1} - 1$。而每次调整只会影响到相邻两个 $cnt$ 的值，所以方案唯一，按 B1 处理完之后直接贪心调整就可以了。

注意 $add$ 和 $del$ 的标记不可以加在同一个上面，这样子会使得可调整的次数被抵消，从而将一些可行的方案算成不可行了，我之前没意识到这个就 WA 了好久才发现。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define NO return cout << "No\n", void()
#define YES return cout << "Yes\n", void()
using namespace std;
const int N = 2e5 + 5;
int t, n, cnt[33], add[33], del[33];
ll sum, avg, a[N], b[N];

void solve() {
    cin >> n;
    sum = avg = 0;
    for (int i = 0; i <= 32; ++i) cnt[i] = opt[i] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; sum += a[i];
    }
    if(sum % n) NO; 
    avg = sum / n;
    for (int i = 1; i <= n; ++i) {
        b[i] = a[i] - avg;
        if(b[i] == 0) continue;
        ll c = abs(b[i]);
        ll x = __lg(c) + 1, y = __lg((1ll << x) - c);
        if((1ll << x) - (1ll << y) != c) NO;
        if(__builtin_popcount(c) == 1) {
            if(b[i] > 0) add[y] += 2;
            else del[y] += 2;
        }
        if(b[i] < 0) swap(x, y);
        cnt[x]++, cnt[y]--;
    }
    for (int i = 0; i < 32; ++i) {
        if(abs(cnt[i]) & 1) NO;
        if(cnt[i] == 0) continue;
        else if(cnt[i] > 0) {
            if(del[i] < cnt[i]) NO;
            cnt[i + 1] += cnt[i] / 2, cnt[i] = 0;
        }
        else {
            if(add[i] < -cnt[i]) NO;
            cnt[i + 1] += cnt[i] / 2, cnt[i] = 0;
        }
    }
    for (int i = 0; i < 32; ++i) {
        if(cnt[i] != 0) NO;
    }
    YES;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}
```

---

