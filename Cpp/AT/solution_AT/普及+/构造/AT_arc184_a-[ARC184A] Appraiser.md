# [ARC184A] Appraiser

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc184/tasks/arc184_a

この問題は **インタラクティブ** な問題であり、 **ジャッジは適応的(adaptive)** です。詳しくは注意点を参照してください。  
**また、問題文中のパラメータは $ N=1000,M=10,Q=950 $ で固定されています。**

硬貨が $ N $ 枚あり、 $ 1,2,\dots,N $ の番号が付けられています。  
これらの硬貨のうち、丁度 $ M $ 枚が偽物です。

鑑定士は $ 1 $ 度の鑑定で $ 2 $ つの硬貨が同種か異種かを判定できます。厳密には、

- $ 2 $ つの硬貨が「双方とも本物」「双方とも偽物」のどちらかであれば、同種と判定する。
- そうでないとき、異種と判定する。

$ Q $ 回以下の鑑定で、全ての偽物の硬貨を特定してください。

### Input &amp; Output Format

この問題はインタラクティブな問題です。  
最初に、 $ N,M,Q $ を標準入力から受け取ってください。

> $ N $ $ M $ $ Q $

次に、以下の流れで鑑定を $ 0 $ 回以上 $ Q $ 回以下行ってください。

まず、次の形式で標準出力に出力することで、硬貨 $ x,y $ を鑑定することを表します。 (末尾に改行を入れること。)

> ? $ x $ $ y $

ここで、 $ x,y $ は $ 1 $ 以上 $ N $ 以下の相異なる整数である必要があります。

これに対するジャッジシステムの応答は、以下の $ 3 $ 通りです。

```
0
```

応答が `0` であるとき、硬貨 $ x,y $ が同種であることを表します。

```
1
```

応答が `1` であるとき、硬貨 $ x,y $ が異種であることを表します。

```
-1
```

応答が `-1` であるとき、不当な鑑定であることを表します。具体的には

- 出力した $ x,y $ が制約を満たさなかった
- $ Q $ 回を超えて鑑定が行われた

の少なくともひとつが満たされた際にこの応答を行います。  
この応答を受け取った場合、プログラムはすでに不正解とみなされています。直ちにプログラムを終了してください。

最後に、次の形式で標準出力に出力することで、硬貨 $ A_1,A_2,\dots,A_{M} $ が偽物であると解答します。 (末尾に改行を入れること。)

> ! $ A_1 $ $ A_2 $ $ \dots $ $ A_{M} $

ここで、 $ A_i $ は $ 1 $ 以上 $ N $ 以下の相異なる整数である必要があります。  
この出力の後、直ちにプログラムを終了してください。

なお、全ての出力について、出力が指定された形式を満たさなかった場合もプログラムが不正解とみなされます。 その後 `-1` が返答されるので、その場合も直ちにプログラムを終了してください。

## 说明/提示

### 制約

- $ \color{red}{N\ =\ 1000} $
- $ \color{red}{M\ =\ 10} $
- $ \color{red}{Q\ =\ 950} $

### 注意点

- **出力を行うたびに、末尾に改行を入れて標準出力を flush してください。** そうしなかった場合、ジャッジ結果が TLE や WA となる可能性があります。
- 解答を出力したら (または `-1` を受け取ったら) ただちにプログラムを終了してください。そうしない場合、ジャッジ結果は不定です。
- 余計な改行は不正なフォーマットの出力とみなされることに注意してください。
- **この問題のジャッジシステムは、適応的(adaptive)です。** つまり、ジャッジシステムは、任意のタイミングにおいて、整合性がとれる限り、偽物の硬貨として想定しているものを変更する可能性があります。詳しくは入出力例も参照してください。

### 入出力例

この入力では $ N=5,M=2,Q=10 $ であり、ジャッジシステムは最初硬貨 $ 1,2 $ が偽物であると想定しています。

なお、この例は制約を満たさないので、ジャッジには含まれないことに注意してください。

入力出力説明`5 2 10`$ N,M,Q $ が与えられます。`? 1 2`硬貨 $ 1,2 $ について鑑定を行います。`0`硬貨 $ 1,2 $ は同種だと判定します。`? 1 3`硬貨 $ 1,3 $ について鑑定を行います。`1`硬貨 $ 1,3 $ は異種だと判定します。`? 1 4`硬貨 $ 1,4 $ について鑑定を行います。`1`硬貨 $ 1,4 $ は異種だと判定します。`! 1 2`硬貨 $ 1,2 $ が偽物だと解答します。確かに硬貨 $ 1,2 $ は偽物だと想定されていますが、硬貨 $ 3,4 $ を偽物であると想定しても整合性が取れます。  
よって、ジャッジシステムは偽物の硬貨として想定しているものを硬貨 $ 3,4 $ に変更できます。  
これにより、ジャッジシステムは不正解の判定を下すこともあります。

# 题解

## 作者：wmrqwq (赞：6)

# 题目链接

[AT_arc184_a Appraiser](https://atcoder.jp/contests/arc184/tasks/arc184_a)

# 解题思路

## Q = 999：

我们考虑将第一个硬币与其余的硬币作比较，最后若交互库返回的 $1$ 更多，那么说明第 $1$ 枚硬币是假币，否则第 $1$ 枚硬币是真币，直接存动态数组最后输出即可。

操作次数容易得出为 $999$ 次。

## Q = 919：

考虑将每 $11$ 枚硬币分一个组，每次询问每组的第一个硬币和剩下的硬币，由于假币数量只有 $10$ 枚，因此如果所有硬币都相同，那么这一堆硬币**必定全是真币**，否则，这一堆硬币中**必有假币**。

这样分，我们会分成 $90$ 组硬币和剩下的 $10$ 枚硬币，由于假币的数量只有 $10$ 个，因此这 $90$ 组硬币中**至少**会有 $80$ 组全为真币，而根据前文提到的**如果所有硬币都相同，那么这一堆硬币必定全是真币**，我们必定可以确定出一个真币的位置，我们可以通过将这枚真币与最后 $10$ 枚硬币比较来确定最后 $10$ 枚硬币的真伪情况。随后我们可以再通过将这枚真币与**必定有假币的硬币堆中的一个硬币**比较，每次比较，我们就可以确定这堆硬币中的硬币真伪情况。

综上，我们可以通过这种方式找出所有硬币。

如果 $10$ 枚假币都在前面分的堆中，则操作次数为 $10 \times 90 + 10 = 910$ 次。

否则，操作次数为 $10 \times 90 + 9 + 10 = 919$ 次。

综上，操作次数最大为 $919$ 次。

# 参考代码

```cpp
/*

time:2024/9/22

contest : https://codeforces.com/contest/877

Tips:

你数组开小了吗？
你 MLE 了吗？
你觉得是贪心，是不是该想想 dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

如果你会：
 取模取了吗？
 算法对拍了吗？
 有没有保留小数据的暴力？
 有没有清空？
 精度够吗？
 时间复杂度真的正确嘛？
 会不会炸空间？
 最大数据会不会炸？
 自己造数据！

如果你不会：
 有没有想最低分的dp？ dp 也是一种暴力
 会不会写暴力分？
 暴力能否优化？
 暴力打表看看有没有非常明显的规律，有的黑题的规律就是cout<<N*N;
 能否分块暴力？
 有没有想最低分的dp？
 那个dp能否优化？
 不要往深的地方思考，想浅一点多想点

冷静冷静再冷静！

对拍对拍再对拍！

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) (1ll*(x)/__gcd(x,y)*(y))
#define Sum(x,y) (1ll*((x)+(y))*((y)-(x)+1)/2)
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
#define bug cout<<"---------------------------------------\n";
//ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}
template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}
ll _t_;
void _clear(){}
map<ll,map<ll,ll>>mp;
ll real_ans[1010];
ll spjsum;
bool f(ll x,ll y)
{
	spjsum++;
	if(spjsum>950)
	{
		cout<<"The ans is too long!\n";
		exit(-1);
	}
	return real_ans[x]!=real_ans[y];
}
ll ask(ll x,ll y)
{
	if(x<1 || y<1 || x>1000 || y>1000)
		exit(-1);
	if(mp[x][y])
		return mp[x][y]-2;
	cout<<"? "<<x<<' '<<y<<endl;
	ll z;
	cin>>z;
	mp[x][y]=z+2;
	if(z==-1)
		exit(-1);
	return z;
}
ll bl[100010];
ll K;
ll _real;
vector<ll>ans;
vector<ll>G[100010][2];
void solve()
{
//	forl(i,996,1000)
//		real_ans[i]=1;
//	forl(i,1,5)
//		real_ans[i]=1;
	_clear();
	ll x;
	cin>>x>>x>>x;
	forll(i,1,990,11)
	{
		K++;
		G[K][1].pb(i);
		forl(j,i+1,i+10)
		{
			if(!ask(i,j))
				G[K][1].pb(j);
			else
				G[K][0].pb(j),
				bl[K]=1;
		}
		if(!bl[K])
			_real=i;
	}
	forl(i,991,1000)
		if(ask(i,_real))
			ans.pb(i);
	K=0;
	forll(i,1,990,11)
		if(bl[++K])
		{
			if(ask(_real,G[K][1][0]))
				for(auto i:G[K][1])
					ans.pb(i);
			else
				for(auto i:G[K][0])
					ans.pb(i);
		}
	sort(ans.begin(),ans.end());
	cout<<"! ";
	for(auto i:ans)
		cout<<i<<' ';
	cout<<endl;
}
int main()
{
//	freopen("tst.txt","r",stdin);
//	freopen("sans.txt","w",stdout);
//	IOS;
	_t_=1;
 //	cin>>_t_;
	while(_t_--)
		solve();
	QwQ;
}
```

---

## 作者：zdd6310 (赞：4)

# [ARC184A] Appraiser

## description

有 1000 个硬币，其中恰好 10 个是假币。

每一次询问两个硬币的真假 **是否相同**。就是一真一假返回 1，否则返回 0。

你有 950 次询问，需要你在 950 次询问内找出所有的假币。

感觉不像信息题，更像数学构造题。

## solution

发现询问次数非常奇怪。连循环一遍都不行。

所以考虑分组。每 10 个硬币分成一组，一共 100 组。

因为只有 10 个假币，所以要么全部在一组，要么分散在很多组里。

所以考虑以下做法：

首先，对于每一组，取一个特殊点，将这个点跟组内其他所有点比较。一共 100 组，每个组 9 次，共 900 次。

#### 如果刚才所有的询问都是 相同

那么假币全部都在一个组里。

将所有的组两两比较，一共 50 次。在前 49 次如果有不同，说明是其中一个有假币，跟之后的随便一个组比较，就知道哪一个是假币。总共 950 次。

不然最后两组中有一组是假币，将最后一组跟第一组比较，相同就是倒数第 2 组，不然就是最后一组。总共 950 次。

#### 如果刚才所有的询问存在 不同

说明每一个不同的组存在假币，**而且其他询问完全相同的组不存在假币**。

所以只需要确定每一个组的特殊点是否是假币就可以。

所以取一个真币，跟所有的特殊点比较，就知道特殊点的真假。

因为特殊点已经跟所有点比较过，所以已经确定了所有币的真假。

因为最多 10 个组中有假币，所以一共用了 910 次。

## code

真的应该自己手模一下。

注意，要输入三个数。

要清空缓存。

~~代码就不放了~~。

---

## 作者：Register_int (赞：3)

首先有个很唐的思路：把 $1000$ 个币分成若干个长度为 $21$ 的段，段内可以用 $20$ 次操作找出两种硬币的数量。由于必然有一种硬币 $>10$ 个，就能知道这种绝对是真币，剩下的都是假币。操作次数是 $20\times46+33=953$ 次。

那他为啥唐呢？发现最后留了一个长度为 $34$ 的段，完全没法拆分。不妨按 $20$ 一段来分，最多会有一段出现 $10$ 个真币 $10$ 个假币的结果，跟其他段比一比即可，次数是 $19\times50+1=951$ 次。

那还是差一点啊？容易发现，若 $19$ 个分一段，还是只会出现一段是 $10$ 个真币 $9$ 个假币，或者 $10$ 个假币 $9$ 个真币的情况。恰好最后有一个长度为 $31$ 的大段是一定能分清谁真谁假的，拿去问就好了。次数为 $18\times51+30+1=949$ 次，恰好通过。

还能更进一步吗？能的！当段内长度 $>10$ 时，我们可以直接确定段内是否存在假币，就不用一个一个问过去了。不妨分成 $89$ 个长度为 $11$ 的段和 $1$ 个长度为 $21$ 的段，$21$ 段可以直接帮我们找到一个真币，而理论上剩下 $89$ 个段我们一个都不需要检查，直接暴力枚举哪一种是假币即可。次数为 $10\times89+20=910$ 次。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e3 + 10;

vector<int> ans; int c[MAXN], p[10], t0[10], t1[10], tp;

inline 
int ask(int x, int y) {
	cout << "? " << x << " " << y << endl;
	int ans; return cin >> ans, ans;
}

int main() {
	scanf("%*d%*d%*d");
	for (int i = 0, l, r; i < 90; i++) {
		l = i * 11 + 1, r = i * 11 + 11;
		if (i == 89) r = 1000;
		for (int j = l; j < r; j++) c[j + 1] = c[j] ^ ask(j, j + 1);
		int c0 = 0, c1 = 0;
		for (int j = l; j <= r; j++) c[j] ? ++c1 : ++c0;
		if (c1 > 10) { for (int j = l; j <= r; j++) c[j] ^= 1; swap(c0, c1); }
		if (c0 > 10) { for (int j = l; j <= r; j++) if (c[j]) ans.emplace_back(j); }
		else p[tp++] = i;
	}
	if (tp) {
		for (int i = 0; i < tp; i++) {
			int l = p[i] * 11 + 1, r = p[i] * 11 + 11;
			for (int j = l; j <= r; j++) c[j] ? ++t1[i] : ++t0[i];
		}
		for (int s = 0, x; s < 1 << tp; s++) {
			x = 0;
			for (int i = 0; i < 10; i++) x += (s >> i & 1) ? t1[i] : t0[i];
			if (x == 10 - ans.size()) {
				for (int i = 0; i < tp; i++) {
					if (s >> i & 1) continue;
					int l = p[i] * 11 + 1, r = p[i] * 11 + 11;
					for (int j = l; j <= r; j++) c[j] ^= 1;
				}
				break;
			}
		}
		for (int i = 0; i < tp; i++) {
			int l = p[i] * 11 + 1, r = p[i] * 11 + 11;
			for (int j = l; j <= r; j++) if (c[j]) ans.emplace_back(j);
		}
		sort(ans.begin(), ans.end());
	}
	cout << "! ";
	for (int x : ans) cout << x << " ";
}
```

应该是确定性理论最优了。

---

## 作者：N_z_ (赞：3)

来个 $909$。

考虑套用 $89\times11+21$ 的做法，我们分成 $90\times11+10$。当多出来 $10$ 个同色时，我们可以确定答案。

于是我们分成 $91\times10$，取一个同色的不加元素即可。

<https://atcoder.jp/contests/arc184/submissions/58045971>。

---

## 作者：2huk (赞：2)

交互题真好玩。虽然我不会做。

## 题意

有 $n = 1000$ 枚硬币，其中有 $m = 10$ 个是假币，剩下的是真币。你需要用不多于 $q = 950$ 次询问交互库任意两枚硬币的真假是否相同。最后输出哪些是假币。

## 做法

显然你可以通过 $k - 1$ 次询问得到 $k$ 个硬币的相对真假关系。每次拿它和第一个问即可。

那么我们可以通过 $10$ 次操作得到 $11$ 个硬币的相对真假关系。如果这 $11$ 个硬币全部相同，那么我们可以确定这 $11$ 个硬币都是**真币**。

所以我们考虑将 $1000$ 个硬币分成 $90$ 组，每组 $11$ 个。还剩 $10$ 个再组成一组。

显然前 $90$ 组中，我们可以通过 $90 \times 10 = 900$ 次询问得到每一组中硬币的相对真假关系。

因为只有 $10$ 个假币，所以在前 $90$ 组中，至多有 $10$ 个组存在假币。我们在剩下的 $80$ 组中随便选一个都是真币，把这个作为基准，以后要单独判断的都和这个真币比较。

那么那 $10$ 个组中，哪些是真哪些是假呢？显然我们只需要那基准和这个组中的**任意一个**比较，都能依次推出每个组所有金币的真假。

剩下的 $10$ 个未分组的金币拿基准和它单独比较即可。总次数最多 $90\times10+10+10=920$。

https://atcoder.jp/contests/arc184/submissions/58049698

---

## 作者：251Sec (赞：2)

挑战题解区最劣解。

考虑把 $1000$ 个硬币分 $50$ 组，每组 $20$ 个花 $19$ 次操作问出来每个元素是真的还是假的。但是发现如果所有假币都在同一组就挂了。不过此时所有其它的组一定都是真币，那么我们可以拿这组里的每个币和其它组的随便一个币比一下，特别地，最后一个币不需要比，只需要看前面的币里有 $9$ 个还是 $10$ 个假币就行了。

操作次数恰好 $950$。

---

## 作者：I_will_AKIOI (赞：2)

AT 新改版的 ARC 就是好，A 先喂给你一道非常 ex 的交互，过了就能上分，我这个蒟蒻居然做了出来。

首先容易想到把 $A_2\sim A_n$ 分别和 $A_1$ 放在一起询问，然后按询问结果把硬币分成两部分，由于 $M$ 很小，因此数量较小的那部分就是赝品。但是这样询问次数是 $999$ 会寄。

于是我们考虑把 $A$ 分成几个块来处理。设块长为 $len$，那么我们可以把当前块的第一个数和第 $2\sim len$ 个数分别进行询问。这样每个块只需要询问 $len-1$ 次。计算可得最少需要分成 $50$ 块。这样 $len=20$。但是会出现一个问题，如果某个块分成的两部分大小都是 $10$，那么你无法辨别那个是真，那个是假，即使你在程序前面随机打乱了数组 $A$，但是由于交互库是自适应的，你依然会寄。

既然两部分的大小为 $10$ 不能判断，那么我们将 $len$ 设为 $19$，这样两部分的大小就不会相同了。但是这时最坏情况是一部分大小为 $10$，另一部分是 $9$。由于 $M=10$，所以我们就去找有没有其他询问的一部分的大小为 $1$，有的话就说明 $9$ 的这部分全部都是赝品，否则这个 $10$ 是赝品。但 $len=19$ 不能被 $N$ 整除怎么办？我们就把最后一个散块和倒数第二个块合并即可。询问次数为 $948$。

```cpp
#include<bits/stdc++.h>
#define N 1005
#pragma GCC optimize("O3")
using namespace std;
int n,m,q,tot,pos,f[N],L[N],R[N],vis[N];
vector<int>res,v1[N],v2[N];
int main()
{
	ios::sync_with_stdio(0);
	srand(time(0));
	cin>>n>>m>>q;
	tot=(n-1)/19;
	for(int i=1;i<=tot;i++) L[i]=(i-1)*19+1,R[i]=i*19;
	R[tot]=n;//预处理块长
	for(int i=1;i<=tot;i++)
	{
		v1[i].push_back(L[i]);//v1[i]表示第i次询问和L[i]类型相同的硬币编号，v2[i]表示不同
		for(int j=L[i]+1;j<=R[i];j++)
		{
			cout<<"? "<<L[i]<<" "<<j<<endl;
			int res;
			cin>>res;
			if(res==-1) while(1);
			if(res==0) v1[i].push_back(j);
			else v2[i].push_back(j);
		}
		if(v1[i].size()==10&&v2[i].size()==9||v1[i].size()==9&&v2[i].size()==10) pos=i;//特判出现一个10，另一个是9的情况
	}
	if(pos==0)//未出现特殊情况，数量较少的部分就是赝品
	{
		for(int i=1;i<=tot;i++)
		{
			if(v1[i].size()>v2[i].size()) for(int now:v2[i]) vis[now]=1; 
			else for(int now:v1[i]) vis[now]=1; 
		}
	}
	else//出现非法情况
	{
		bool check=0;
		for(int i=1;i<=tot;i++)//找有没有出现1
		{
			if(v1[i].size()==1||v2[i].size()==1)
			{
				check=1;
				break;
			}
		}
		if(check)//找到了，说明没有9的部分是赝品
		{
			for(int i=1;i<=tot;i++)
			{
				if(v1[i].size()>v2[i].size()) for(int now:v2[i]) vis[now]=1; 
				else for(int now:v1[i]) vis[now]=1; 
			}
		}
		else//10的部分是赝品
		{
			for(int i=1;i<=tot;i++)
			{
				if(i==pos) continue;
				if(v1[i].size()>v2[i].size()) for(int now:v2[i]) vis[now]=1; 
				else for(int now:v1[i]) vis[now]=1; 
			}
			if(v1[pos].size()==10) for(int now:v1[pos]) vis[now]=1; 
			else for(int now:v2[pos]) vis[now]=1; 
		}
	}
	cout<<"! ";
	for(int i=1;i<=n;i++) if(vis[i]) cout<<i<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：WZWZWZWY (赞：2)

思路来自[官方题解](https://atcoder.jp/contests/arc184/editorial/10999)。

膜拜机房大佬赛时一遍过 orz。


---


这个问题的关键在于真币比假币多许多。

每组包含 $11$ 个币，分成 $90$ 组。最后剩下 $10$ 个币。

那么每组之内的除组头外的 $10$ 个币都与组头进行比较，只需要比 $10$ 次，就能得出组内币是否与组头相同。因为假币总共只有 $10$ 个，所以一组内 $11$ 个币不可能全是假币；若发现都相同，说明全是真币。总共 $900$ 次比较。

并且有 $90$ 组，不可能每一组中都有假币，所以一定能找到一组全是真币。那么记下一个真币，然后依次与每一个有假币的组的组头进行比较，得到每一组的组头信息，因为又知道每一组其他组员与组头的关系，所以可以用最多 $10$ 次求出所有组内币的真假。

还剩下 $10$ 个单独的币，单独与真币比较即可。花费 $10$ 次比较。

最多需要 $900+10+10=920$ 次比较。

```
#include <bits/stdc++.h>
using namespace std;

bool zs[1005]; // 记录与组头是否相同 
vector <int> un, ans; // 包含假币的组，假币的具体位置 

int main() {
	int n, m, q, x; cin >> n >> m >> q;
	
	int gr_size = 11, gr = 90, rel; // 每一组的大小，组数，rel记录一个真币 
	
	for (int i = 1; i <= gr; i++) {
		int st = gr_size * (i - 1) + 1; // 组头 
		bool t = 1; // 是否11个全相同 
		for (int j = 1; j < gr_size; j++) {
			cout << "? " << st << " " << st + j << endl;
			cin >> x;
			zs[st + j] = zs[st] ^ x;
			if (x == 1) t = 0;
		}
		if (t) rel = st; // 如果11个全相同，必定都是真币。记录一个真币 
		else un.push_back(st); // 否则一定有假币，加入un 
	}
	
	for (int i : un) {
		cout << "? " << i << " " << rel << endl;
		cin >> x;
		for (int j = 0; j < gr_size; j++) 
			if (zs[i + j] ^ x) ans.push_back(i + j);
	}
	
	int st = gr * gr_size; // 剩下的10个单独询问，st是组头 
	for (int i = 1; i <= 10; i++) {
		cout << "? " << rel << " " << st + i << endl;
		cin >> x;
		if (x) ans.push_back(st + i);
	}
	
	cout << "!";
	for (int i : ans) cout << " " << i;
	cout << endl;
}
```

好像没什么问题，有疑问的可以发在评论区。

---

## 作者：WuMin4 (赞：1)

# 题意

$1000$ 个硬币中有 $10$ 个假币，你每次可以询问两个位置的硬币类型是否相同，你需要用不超过 $950$ 次询问找出所有假币的位置。

# 思路

将前 $990$ 个硬币每 $11$ 个分一组，共 $90$ 组，余 $10$ 个单独分一组。

询问每组第 $1$ 个硬币和这组后面硬币的关系。因为只有 $10$ 个假币，所以如果含有 $11$ 个硬币的一组全部相同，那么这一组就全是真币，挑出一个真币跟含有假币的组（即含有不同硬币的一组）的第 $1$ 个硬币比较，即可判断出这一组硬币的真假情况，最多 $90\times 10+9+10=919$ 次询问，可以通过。

注意因为最后一组只有 $10$ 个，所以当每组的硬币都相同时，$10$ 个假币就都在最后一组。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,q,nst;
bool ys[1005][1005],ist[1005];
vector<int> fk;
bool cp;
signed main() {
	cin>>n>>m>>q;
	for(int i=1;i<=1000;i+=11){
		for(int x,j=i+1;j<=min(1000,i+10);j++){
			cout<<"? "<<i<<" "<<j<<endl;
			cin>>x;
			if(x==1)
				ys[i][j]=true,ist[i]=true,cp=true;
		}
		if(!ist[i])
			nst=i;
	}
	if(!cp){
		cout<<"! ";
		for(int i=991;i<=1000;i++)
			cout<<i<<" ";
		cout<<endl;
		return 0;
	}
	for(int x,i=1;i<=1000;i+=11){
		if(!ist[i]) continue;
		cout<<"? "<<nst<<" "<<i<<endl;
		cin>>x;
		if(x) fk.push_back(i);
		for(int j=i+1;j<=min(1000,i+10);j++){
			if(ys[i][j]^x)
				fk.push_back(j);
		}
	}
	cout<<"! ";
	for(int v:fk)
		cout<<v<<" ";
	cout<<endl;
	return 0; 
}
```

---

## 作者：_WRYYY_ (赞：1)

[在我的博客观看以获得不知道好不好的体验。](https://www.cnblogs.com/wryyy-233/p/18426554)

本质上还是官方题解的分组并利用 $M$ 不大的思路。

询问次数 $Q$ 离最简单的每个扫一遍就可以知道答案的做法少了 $50$ 次。我们考虑如何减少这个次数。

首先你可以发现一次询问可以覆盖到两个数，也就是说所有的数都被覆盖时只需要询问 $500$ 次。

我们考虑把不同的对拉出来，然后把它剩下相同的对留下，最坏的情况是所有都被留下了。

此时继续重复上述操作，并把每个对看成一个整体，也就是说按照 $2,4,8,...,2^n$ 的方式不断进行分组，你会发现，最坏的情况下至少在每 $4$ 个为一组时至少会查出一组大小为 $2$ 的不同类型组，因为 $M=10$。而在每 $16$ 个为一组时就可以查出所有的不同组，所以我们只要分到 $16$ 为一组时就不用再分了，这里总共使用了至多 $937$ 次询问，请自行计算。

当然这样有个问题，就是在分的时候会出现末尾每办法分进去，我们就直接将其单独提出，这样的单独最多有 $3$ 组。

最后剩下的相同组一定都是真币，所以只要单独提出其中一个然后与每个不同组比较，若不同组的前半与其不同，则前半为假币，若相同，则后半为假币，这里至多比 $5$ 次。

对于单独组，它也可能是假币，所以也要比较，但是如果相同就不做处理，这里最多会比较 $3$ 次。

最后询问次数将严格低于 $937+3+5=945$ 次。比较劣，但是可过。

还要注意不要读错题，比如说看错 $1$ 和 $0$ 的意义之类的，否则你会像我一样调一个多小时。

赛时码风，丑陋轻喷。

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define N 1010
using namespace std;
using namespace __gnu_pbds;
bool ask(int x, int y)
{
	cout << "? " << x << " " << y << "\n";
	fflush(stdout);
	bool ans;
	cin >> ans;
	return (!ans);
}
int m, cnt;
bitset<N> vis;
vector<pair<vector<int>, vector<int>>> ns;
vector<vector<int>> ss;
void solve(vector<vector<int>> a)
{
	if (cnt >= m || a.size() <= 70)
		return;
	int x, y, z, n = a.size();
	vector<vector<int>> a1;
	vector<int> vec1, vec2, vec;
	for (int i = 1; (i << 1) <= n; i++)
	{
		y = i << 1;
		x = y - 1;
		--x;
		--y;
		vec1 = a[x];
		vec2 = a[y];
		if (ask(vec1.front(), vec2.front()))
		{
			vec = vec1;
			for (auto val : vec2)
				vec.push_back(val);
			a1.push_back(vec);
		}
		else
		{
			cnt += vec1.size();
			ns.push_back(m_p(vec1, vec2));
			for (auto val : vec1)
				vis[val] = 1;
			for (auto val : vec2)
				vis[val] = 1;
		}
	}
	if (n & 1)
	{
		ss.push_back(a.back());
		for (auto val : a.back())
			vis[val] = 1;
	}
	return solve(a1);
}
signed main()
{
	int n, q, x, y, los = 1;
	cin >> n >> m >> q;
	vector<vector<int>> a;
	vector<int> vec;
	vec.resize(1);
	for (int i = 1; i <= n; i++)
	{
		vec[0] = i;
		a.push_back(vec);
	}
	solve(a);
	if (cnt == m)
	{
		for (auto vec1 : ss)
			for (auto val : vec1)
				vis[val] = 0;
		ss.clear();
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i])
		{
			los = i;
			break;
		}
	vec.clear();
	for (auto [vec1, vec2] : ns)
	{
		if (ask(los, vec1.front()))
			for (auto val : vec2)
				vec.push_back(val);
		else
			for (auto val : vec1)
				vec.push_back(val);
	}
	for (auto vec1 : ss)
		if (!ask(los, vec1.front()))
			for (auto val : vec1)
				vec.push_back(val);
	sort(vec.begin(), vec.end());
	cout << "!";
	for (auto val : vec)
		cout << " " << val;
	cout << "\n";
	fflush(stdout);
	return 0;
}
```

话说这道题真的只普及吗？

还是我菜了。

---

## 作者：MrPython (赞：1)

按 $11$ 个每块分组，共分了 $90$ 组，还余 $10$ 个之后处理。每个组内询问相邻的点对，这样一个组需要询问 $10$ 次，共 $900$ 次。

由于只有 $10$ 个坏点，那么若一组 $11$ 个全部相等则说明这 $11$ 个都是好的。我们记下已知的任意一个好点。否则，这一组内至少有一个坏点，留下备用。最多只有 $10$ 个坏点，因此最多只有 $10$ 个可疑的组。

我们知道了一组内两两间的关系，因此只需要知道组内任意一个点的属性就可以确认整组的。我们拿那个已知的好点去和每个可疑组的任意一点做询问，这样可以求出所有可疑组内所有点的情况。这样的询问最多需要 $10$ 次。

另外，还单独余下 $10$ 个点。挨个和好点做比较即可。需要 $10$ 次。

最后，总共 $920$ 次。

```cpp
#include <bits/extc++.h>
using namespace std;
namespace pbds = __gnu_pbds;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
bool ask(size_t x, size_t y) {
  fout << "? " << x + 1 << ' ' << y + 1 << endl;
  bool res;
  fin >> res;
  return res;
}
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t n, m, q;
  fin >> n >> m >> q;
  size_t target = ~0;
  vector<vector<bool>> d;
  vector<size_t> special;
  for (ui i = 0; i + m + 1 <= n; i += m + 1) {
    d.emplace_back();
    for (ui j = 0; j < m; ++j) d.back().emplace_back(ask(i + j, i + j + 1));
    if (count(d.back().begin(), d.back().end(), true))
      special.emplace_back(d.size() - 1);
    else
      target = i;
  }
  vector<size_t> ans;
  for (size_t i : special) {
    bool lst = ask(i * (m + 1), target);
    if (lst) ans.emplace_back(i * (m + 1));
    for (size_t j = 0; j < m; ++j)
      if (lst ^= d[i][j]) ans.emplace_back(i * (m + 1) + j + 1);
  }
  for (size_t i = n - n % (m + 1); i < n; ++i)
    if (ask(target, i)) ans.emplace_back(i);
  assert(ans.size() == m);
  fout << "! ";
  for (size_t i : ans) fout << i + 1 << ' ';
  return 0;
}
```

---

