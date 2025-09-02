# FN16SWAP - Swap Space

## 题目描述

你有许多电脑，它们的硬盘用不同的文件系统储存数据。你想要通过格式化来统一文件系统。格式化硬盘可能使它的容量发生变化。为了格式化，你需要买额外的硬盘。当然，你想要买容量最小的额外储存设备以便省钱。你可以按任意顺序格式化硬盘。格式化之前，你要把该硬盘上所有数据移到一个或更多的其他硬盘上（可以分割数据）。格式化后，该硬盘可以立刻开始使用。你没有必要把数据放到它原来所在的硬盘上。数据也可以被放到你额外买的硬盘上。举个例子，假设你有4个硬盘A、B、C、D，容量分别为6、1、3、3(GB)。新的文件系统下，它们的容量变为6、7、5、5(GB)。如果你只买1GB额外空间，你可以把B硬盘的数据放过去然后格式化硬盘B。现在你的B硬盘有7GB容量了，那么你就可以把A的数据放过去然后格式化A，最后把C、D的数据放到A上，再格式化C和D。

## 样例 #1

### 输入

```
4
6 6
1 7
3 5
3 5
4
2 2
3 3
5 1
5 10```

### 输出

```
1
5```

# 题解

## 作者：封禁用户 (赞：7)

### 思路：

通过对样例的手动模拟和对数据范围的观察可以猜到作贪心。

贪心思想希望我们尽可能的增加剩余容量，这样产生的额外费用最少。

一次将 $a_i$ 变为 $b_i$ 的格式化操作会产生的贡献可以记为 $b_i - a_i$。

但是 $b_i - a_i$ 的正负性却很难保证，所以要分以下两种讨论：

- $(b_i - a_i) > 0$，优先格式化，通过对 $a_i$ 从小到大排序，相当于 $b_i - a_i$ 从大到小排序。

- $(b_i - a_i) < 0$，它的意义在于减小容量，通过简单移项变为 $(a_i - b_i) > 0$，就可以用第一种情况的方法解决，即对 $b_i$ 从小到大排序。

### 细节：

- 对于 $(b_i - a_i) < 0$ 时的贪心其实是建立在剩余容量最大化的情况下的，而对 $(b_i - a_i) > 0$ 排完序后剩余容量最大，所以要按顺序并分成两列。

- 在统计答案的时候，开一个变量记录 $i$ 时的剩余容量 $s$，此时 $s-a_i$ 是将其格式化的花费。如果是负的，就是格外需要的空间。若为正，当前刚好能满足。取最小即可。

- 答案要取其绝对值。

代码写的有点丑就不放了。

---

## 作者：Randolph、 (赞：1)

[SP27102 【Swap Space】](https://www.luogu.org/problem/SP27102)

**双倍经验：[UVA1747 Swap Space](https://www.luogu.org/problem/UVA1747)**

用（a，b）表示每个硬盘的原容量和新文件系统下的容量。分两种情况考虑：a≤b和a>b

第一类a≤b格式化后能增加我们的剩余容量，所以肯定要优先格式化，按照a从小到大排序，所需空间较少，这样一来可以用较少的空间换取更多的空间；

第二类a>b会减小容量。考虑时间倒流。从后往前倒着看，容量增加，此时看作（b,a），由第一类可知容量增加时我们应当以第一个数b从小到大排序。但由于我们是倒着看，所以实际上先后顺序为b从大到小

例如原容量为7，对于（6,2），容量-4，7->3；如果从后往前反着看则是容量3->7，a，b为（2,6）。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define ll long long
struct node {
	int a,b,c;
} m[1000010],mm[1000010];
inline bool cmp1(node a,node b) {
	return a.a<b.a;
}
inline bool cmp2(node a,node b) {
	return a.b>b.b;
}
int main() {
	ll n,cnt1,cnt2,ans,s;
	while(scanf("%lld",&n)!=EOF) {
		cnt1=cnt2=ans=s=0;
		for (ll x,y; n; n--) {
			scanf("%lld%lld",&x,&y);
			if (x<=y) //分成两类存储排序
				m[++cnt1]=(node) {
				x,y,y-x
			};
			else
				mm[++cnt2]=(node) {
				x,y,y-x
			};
		}
		sort(m+1,m+cnt1+1,cmp1);
		sort(mm+1,mm+cnt2+1,cmp2);
        
        // ans存储所需的额外容量（当前的硬盘文件放满s剩余容量后还需要的额外容量，这里用负数的方式统计最多需要多少额外容量），s存储通过格式化硬盘所获得的容量
		for (int i=1; i<=cnt1; i++)
			ans=min(ans,s-m[i].a),s+=m[i].c;
		for (int i=1; i<=cnt2; i++)
			ans=min(ans,s-mm[i].a),s+=mm[i].c;
		printf("%lld\n",ans>0? ans:-ans);
	}
}
```


---

## 作者：ZPB2011 (赞：0)

# [Swap Space](https://www.luogu.com.cn/problem/SP27102)

## 思路

看完发现可以贪心。

我们可以按 $a_i$ 和 $b_i$ 来分类。

- $a_i \le b_i$ 可以按 $a_i$ 从小到大排序，这样可以尽量不让 $a_i$ 比当前剩余空间多。

- $a_i > b_i$ 可以按 $b_i$ 从大到小排序，这样可以得到尽量多的空间。

## AC code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define int long long
using namespace std;

const int N = 1e5 + 5;

struct node {
	int x, y;
};

vector<node> a, b;

bool cmp(node x, node y) {
	return x.x < y.x;
}

bool cmp2(node x, node y) {
	return x.y > y.y;
}

signed main() {
	int n;
	while(cin >> n) {
		a.clear();
		b.clear();
		for(int i = 1; i <= n; i++) {
			int x, y;
			cin >> x >> y;
			if(x <= y) {
				a.push_back({x, y});
			}
			else {
				b.push_back({x, y});
			}
		}
		sort(a.begin(), a.end(), cmp);//贪心
	    sort(b.begin(), b.end(), cmp2);
		int ans = 0, sum1 = 0, sum2 = 0;
		for(int i = 0; i < a.size(); i++) {
			int x = a[i].x, y = a[i].y;
			if(sum1 - sum2 < x) {
				int tmp = x - (sum1 - sum2);
				ans += tmp;
				sum1 += tmp;
			}
			sum2 += x;
			sum1 += y;
		}
		for(int i = 0; i < b.size(); i++) {
			int x = b[i].x, y = b[i].y;
			if(sum1 - sum2 < x) {
				int tmp = x - (sum1 - sum2);
				ans += tmp;
				sum1 += tmp;
			}
			sum2 += x;
			sum1 += y;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：elonzhang (赞：0)

# [SP27102 FN16SWAP - Swap Space](https://www.luogu.com.cn/problemSP27102)

## 思路
首先可以发现确定了格式化硬盘的顺序我们可以通过线性时间复杂度算出额外硬盘的空间。然后我们考虑贪心策略：当 $b_i\ge a_i$ 时我们要按照 $b_i$ 的大小降序排序，因为这样可以尽量减少额外硬盘所需空间；当 $b_i<a_i$ 时，则需要以 $a_i$ 升序排序，尽量不要让所需 $a_i$ 大于当前的 $ans$。

## ACcode
```cpp
#include <bits/stdc++.h>
using namespace std;
#pragma G++ optimize(2,3,"Ofast","inline")
#define freop(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout);
#define int long long
#define double long double
#define re register
#define endl '\n'
#define inf 0x7f7f7f7f7f7f7f7f
#define lowbit(x) (x&-x)
#define pii pair<int,int>
#define fir first
#define sec second
#define umap unordered_map
#define uset unordered_set
const int N=1e6+1;
int n,t,a[N],b[N],id[N],ans,sum;

bool cmp(int x,int y){
	int ax=a[x],bx=b[x],cx=b[x]-a[x],ay=a[y],by=b[y],cy=b[y]-a[y];
	return ((cx>=0)^(cy>=0)?cx>cy:(cx>=0?ax<ay:bx>by));
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
//	freop();
//↑以上为初始化↑
//------------------------------
	while(cin >> n){
      ans=sum=0;
  	  for(int i = 1;i<=n;++i) cin >> a[i] >> b[i],id[i]=i;
  	  sort(id+1,id+n+1,cmp);
  	  for(int i = 1;i<=n;++i)	ans=max(ans,a[id[i]]-sum),sum+=b[id[i]]-a[id[i]];
  	  cout << ans << endl;
  }
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

三倍经验：

[P6927 [ICPC2016 WF] Swap Space](https://www.luogu.com.cn/problem/P6927)

[UVA1747 Swap Space](https://www.luogu.com.cn/problem/UVA1747)

[SP27102 FN16SWAP - Swap Space](https://www.luogu.com.cn/problem/SP27102)

首先，一个硬盘进行格式化后，对空间的贡献显然为 $b_i-a_i$。

我们可以把这些硬盘分为两类，一类贡献为正，一类贡献不为正（第二类很多题解说“贡献为负”，其实是错的，可能出现 $a_i=b_i$）。

对于贡献为正的硬盘，我们肯定希望先格式化的硬盘 $a_i$ 越小越好。因为每次格式化后都有收益，且总收益一定，我们要先格式化代价较小的，否则后格式化的硬盘就会需要更多的空间。所以这样格式化总代价一定最小。

对于贡献不为正的硬盘，我们肯定希望先格式化的硬盘 $b_i$ 越大越好。因为每次格式化后都有损耗，且总损耗一定，我们要先格式化收益较大的，否则后格式化的硬盘就会需要更多的空间。所以这样格式化总代价一定最小。

因为先获得再失去肯定比先失去再获得更优，所以要先格式化第一类硬盘。

代码：

```
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
int n,x,y,l,r,cnt,ans;
pair<int,int>a[1000001],b[1000001];
bool cmp(pair<int,int>x,pair<int,int>y){
    return x.se>y.se;
}
signed main(){
    while(cin>>n){
        l=0;
        r=0;
        cnt=0;
        ans=0;
        for(int i=1;i<=n;i++){
            cin>>x>>y;
            if(y>x) a[++l]={x,y};
            else b[++r]={x,y};
        }
        sort(a+1,a+1+l);
        sort(b+1,b+1+r,cmp);
        for(int i=1;i<=l;i++){
            if(cnt<a[i].fi){
                ans+=a[i].fi-cnt;
                cnt+=a[i].fi-cnt;
            }
            cnt-=a[i].fi;
            cnt+=a[i].se;
        }
        for(int i=1;i<=r;i++){
            if(cnt<b[i].fi){
                ans+=b[i].fi-cnt;
                cnt+=b[i].fi-cnt;
            }
            cnt-=b[i].fi;
            cnt+=b[i].se;
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：_zexal_ (赞：0)

一道简单贪心题。考虑 $a \ge b$ 和 $a \lt b$ 的情况即可。由于要求最后的附加内存尽可能的小，所以我们一定会要求我们能拿的磁盘空间尽可能的大。当 $a \le b$ 时，格式化硬盘过后只会**增加**容量，所以我们一定会优先。当 $a \gt b$ 时，我们容量会减少，所以我们一定会放最后，并且 $b$ 越大的我们越前面。

我们在输入把硬盘分成两类对应上述情况。然后对 $a \le b$ 情况的按照 $a$ 值从小到大排序。对 $a \gt b$ 情况按 $b$ 的值从大到小排序即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int Maxn=2e6+5;
#define F(i,a,b) for(int i=a;i<=b;i++)
int n,ans,Ans;
struct node {
	int a,b;
} f[Maxn],f1[Maxn],f2[Maxn];
int tot1,tot2;
bool cmp(node a,node b) {
	return a.a<b.a;
}
bool cmb(node a,node b) {
	return a.b>b.b;
}
signed main() {
	while(cin>>n) {
		tot1=tot2=Ans=ans=0;
		F(i,1,n) {
			cin>>f[i].a>>f[i].b;
			if(f[i].a<=f[i].b) f1[++tot1]=f[i];
			else f2[++tot2]=f[i];
		}
		sort(f1+1,f1+tot1+1,cmp);
		sort(f2+1,f2+tot2+1,cmb);
		//int Ans=0;
		F(i,1,tot1) {
			if(Ans<f1[i].a) ans+=f1[i].a-Ans,Ans=f1[i].a;
			Ans=Ans-f1[i].a+f1[i].b;
		}
		F(i,1,tot2) {
			if(Ans<f2[i].a) ans+=f2[i].a-Ans,Ans=f2[i].a;
			Ans=Ans-f2[i].a+f2[i].b;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Acerkaio (赞：0)

### 题目

[Link](https://www.luogu.com.cn/problem/SP27102)

### 思路

贪心。

我们把输入的分出两类。

1. $a \le b$
1. $a > b$

我们发现第一类按照 $a$ 从小到大排序进行循环更优，每次记录这组所赚与以前所赚之和，当发现使用之前所赚之和任然无法储存一个硬盘的文件的话，就更新额外空间为该空间的容量。我们发现第二类按照 $b$ 从大到小排序进行循环更优，其循环操作与第一类处理相似。

除此之外，我们要先去循环第一类，再循环第二类。这是必须的，因为第一类可能会多出空间，我们先循环第一类再循环第二类可以就把第二类放入第一类可能多出的空间，根据贪心思想，这是成立的。

#### 关于为什么要排序会更优

因为当发现使用之前所赚之和任然无法储存一个硬盘的文件的话，就更新额外空间为该空间的容量，按照排序过后，它可能使得不排序需要购买的空间不被购买。

还是那句话：手模出真理。

### CODE

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int n = 0, m = 1;
	char a = getchar();
	while (!isdigit(a)) {
		if (a == '0')
			m = -1;
		a = getchar();
	}
	while (isdigit(a)) {
		n = (n << 3) + (n << 1) + (a ^ 48);
		a = getchar();
	}
	return n * m;
}
int n;
struct Node {
	int a, b;
};
Node sum1[1145140], sum2[1145140];
int num1, num2;
bool cmp1(Node a, Node b) {
	return a.a < b.a;
}
bool cmp2(Node a, Node b) {
	return a.b > b.b;
}
signed main() {
	while(cin >> n) {
		num1 = num2 = 0;
		for (int i = 1; i <= n; i++) {
			int a = read(), b = read();
			if (a <= b) {
				sum1[++num1].a = a;
				sum1[num1].b = b;
			} else {
				sum2[++num2].a = a;
				sum2[num2].b = b;
			}
		}
		sort(sum1 + 1, sum1 + num1 + 1, cmp1);
		sort(sum2 + 1, sum2 + num2 + 1, cmp2);
		int ans = 0, s = 0;
		for (int i = 1; i <= num1; i++) {
			ans = min(ans, s - sum1[i].a);
			//cout << sum1[i].a;
			s += (sum1[i].b - sum1[i].a);
		}
		//cout << ans << '\n';
		for (int i = 1; i <= num2; i++) {
			ans = min(ans, s - sum2[i].a);
			s += (sum2[i].b - sum2[i].a);
		}
		cout << (ans > 0?ans:-ans) << '\n';
	}
	return 0;
}
```


---

